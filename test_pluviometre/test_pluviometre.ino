/*
 * Pincipe :
 * - Toutes les 2 min, on envoi les données à domoticz
 * - Toutes les 2 min, on stock dans un circularBuffer les données dans "h_fifo" permettant de connaitre la hauteur en mm/h
 * Stockage toutes les 2 min dans "h_fifo", le calcul se fait sur 5 min, soit un buffer de 3
 * - Toutes les 2 min, on stock dans un circularBuffer les données dans "j_fifo" permettant de connaitre la hauteur en mm tombée en 24h
 * 
 * Bibliothéque necessaire :
 *   - CircularBuffer by AgileWare v1.3.3
 *   
 */
// CircularBuffer v1.3.3
#include <CircularBuffer.h>

#define INTERVAL 120                // Interval en secondes entre 2 envoi à Domoticz (.

CircularBuffer<float, 3> h_fifo;    // On initialise la taille du buffer pour 6 mn glissantes. (3 = 1 relevé toutes les 2 min)

const byte rainPin = D5;            // PIN de connexion de capteur.
unsigned int raincnt = 0;           // Initialisation du compteur.
unsigned long lastSend;             // Millis du dernier envoi.

void setup() {
  Serial.begin(115200);
  Serial.println("Initialisation...");
  
  // Initialisation du PIN et création de l'interruption.
  pinMode(rainPin, INPUT_PULLUP);          // Montage PullUp avec Condensateur pour éviter l'éffet rebond.
  attachInterrupt(digitalPinToInterrupt(rainPin), cntRain, FALLING); // CHANGE: Déclenche de HIGH à LOW ou de LOW à HIGH - FALLING : HIGH à LOW - RISING : LOW à HIGH.

  // On initialise lastSend à maintenant.
  lastSend = millis();
}

void loop() {
  if ( millis() - lastSend > INTERVAL*1000 ) { 
    // On a atteint l'interval souhaité, on exécute le traitement Rain.
    getSendRain();    
  }

}


ICACHE_RAM_ATTR void cntRain() {
  raincnt++;
  Serial.println("Action... ");
}

void getSendRain() {
  float h_total = 0.00;                 // Initialisation de la variable qui contiendra le nbre total d'eau tombée sur 1 heure

  Serial.println("Execution de la fonction getSendRain().");
  // On initialise lastSend à maintenant.
  lastSend = millis();

  // On calcul le niveau depuis la dernière interogation.
  float pluie = raincnt * 0.2794;       // Nombre d'impulsion multiplié par la hauteur d'eau en mm d'un godet
  raincnt = 0;                          // On réinitialise le compteur.

  // On ajoute le niveau à h_fifo
  h_fifo.push(pluie);  
  Serial.print("Pluie = "); Serial.print(String(pluie)); Serial.println(" mm ");

  // Calcul des précipitations en mm/h, On récupére la hauteur d'eau tombée sur les 6 dernières minutes.
  using index_h = decltype(h_fifo)::index_t;
  for (index_h i = 0; i < h_fifo.size(); i++) {
    h_total += h_fifo[i];
  }
  // On calcul la valeur à envoyer à Domoticz pour une heure.
  h_total = h_total * 10;


  // &svalue=RAINRATE;RAINCOUNTER
  // RAINRATE = h_total
  Serial.print("RAINRATE = "); Serial.println(String((int)(round(h_total)))); 
  
}
