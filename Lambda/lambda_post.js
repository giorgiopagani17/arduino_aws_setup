import { IoTDataPlaneClient, PublishCommand } from "@aws-sdk/client-iot-data-plane";

const client = new IoTDataPlaneClient({ region: "us-east-1" });

export const handler = async (event) => {
  try {
    const body = JSON.parse(event.body || '{}');
    const misurazione = body.misurazione;
    const timestamp = body.timestamp;
    const user = body.user

    if (typeof misurazione === 'undefined' || typeof timestamp === 'undefined') {
      throw new Error("Chiavi 'misurazione' o 'timestamp' mancanti");
    }

    console.log("Dati ricevuti:", misurazione, timestamp);

    const payload = {
      misurazione: misurazione,
      timestamp: timestamp,
      user: user
    };

    const command = new PublishCommand({
      topic: "sdk/test/python",
      qos: 0,
      payload: Buffer.from(JSON.stringify(payload))
    });

    await client.send(command);

    return {
      statusCode: 200,
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({
        message: "Dati ricevuti e pubblicati su IoT Core",
        data: payload
      })
    };

  } catch (error) {
    console.error("Errore Lambda:", error.message);
    return {
      statusCode: 500,
      body: JSON.stringify({ error: error.message })
    };
  }
};
