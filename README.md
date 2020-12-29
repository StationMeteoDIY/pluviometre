# pluviometre

Intégration d'un pluviométre à godet dans notre station météo.

# Explications
Suite de la création de notre station météo, ces deux scripts vont montrer comment récupérer les informations d'un pluviométre à godet.Le pluviométre n'étant pas un capteur, l'ESP (ou un Arduino) doit utiliser les événements, afin de déclencher à chaque fois que le godet bascule. Il doit également calculer le nombre de millimètres de pluie tombée en une heure, ainsi que dans la journée courante.
Le dossier de scripts "test_pluviometre" permet de comprendre le fonctionnement de récupération des informations, et de calcul interne. le second "Projet_station_meteo_multi" permet d'intégrer notre script dans celui de notre station météo.
Plus d'information dans la vidéo YouTube.

## Pré-requis
Il faut installer l'IDE Arduino, et y intégrer quelques configurations :

Prise en charge de la carte ESP : http://arduino.esp8266.com/stable/package_esp8266com_index.json

## Bibliothéques nécessaires, et versions utilisées dans cette exemple :
  - CircularBuffer by AgileWare v1.3.3
  
  
# Tuto vidéo
Vidéo explicative sur YouTube : https://youtu.be/y-eyop1UqPc
