Tutorial: Rilevazione Luminosità con Arduino, Invio Dati su AWS e Visualizzazione su Grafana
Descrizione
Questo tutorial guida passo passo nella configurazione di un sistema completo per:

Rilevare la luminosità ambientale tramite una fotoresistenza collegata ad Arduino.

Inviare i dati raccolti ad AWS per memorizzazione e analisi.

Visualizzare i dati in tempo reale tramite una dashboard Grafana.

Componenti del progetto
Arduino con sensore fotoresistenza

AWS IoT / Lambda / Athena / DynamoDB / S3 (a seconda dell'architettura usata)

Grafana per la visualizzazione dei dati

Cosa imparerai
Come leggere valori analogici dalla fotoresistenza con Arduino.

Come inviare dati da Arduino ad AWS (tramite MQTT, HTTP o API Gateway).

Come salvare e interrogare i dati su AWS (ad esempio usando Athena o DynamoDB).

Come creare una dashboard Grafana collegata ai dati AWS per monitorare la luminosità.

Struttura del tutorial
Configurazione hardware Arduino e sensore fotoresistenza

Scrittura del codice Arduino per rilevazione e invio dati

Setup su AWS per ricevere e salvare i dati

Creazione e configurazione della dashboard Grafana

Requisiti
Arduino IDE

Account AWS attivo

Accesso a Grafana (locale o cloud)

~ Giorgio Pagani

