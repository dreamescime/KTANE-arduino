| Module Name         | Sketched         | Codage           | Fait solo        | Fait ensemble    | N° adresse (plage) |
| ------------------- |:----------------:|:----------------:|:----------------:|:----------------:|:------------------:|
|Master horloge       |:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:| master = 0         |
|Fils simple          |:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:|  1 -  5            |
|Bouton               |:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:|  6 - 10            |
|Symboles             |:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:| 11 - 15            |
|SIMON                |:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:| 16 - 20            |
|Jeux de mots ?       |:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:| 21 - 25            |
|Memoire              |:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:| 26 - 30            |
|MORSE                |:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:| 31 - 35            |
|Fils compliqués      |:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:| 36 - 40            |
|Labyrinthe           |:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:| 41 - 45            |
|Mot de passe         |:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:| 46 - 50            |

| Module modé         | Sketched         | Codage           | Fait solo        | Fait ensemble    | N° adresse (plage) |
| ------------------- |:----------------:|:----------------:|:----------------:|:----------------:|:------------------:|
|Math emoji           |:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:| 51 - 55            |

| Module needle       | Sketched         | Codage           | Fait solo        | Fait ensemble    | N° adresse (plage) |
| ------------------- |:----------------:|:----------------:|:----------------:|:----------------:|:------------------:|
|Questions Reponses   |:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:| 106 - 110          |
|Condensateur         |:heavy_check_mark:|:heavy_check_mark:|                  |                  |  96 - 100          |
|Molette              |:heavy_check_mark:|:heavy_check_mark:|                  |                  | 101 - 105          |

| Module PORT         | Sketched         | Codage           | Fait solo        | Fait ensemble    | N° adresse (plage) |
| ------------------- |:----------------:|:----------------:|:----------------:|:----------------:|:------------------:|
|Port                 |:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:| 116 - 120          |

Modules du jeu non réalisés : **Séquences de fils** (pas de solution physique retenue). Le module **Gaz** est remplacé par Questions Reponses.

**Adresses I2C** : Mettre chaque module identique à une adresse différente.

# 0 : Module Maitre

**Obligatoire** :
* Ecran numéro de série
* [Support batterie](https://fr.aliexpress.com/item/4001116419537.html?spm=a2g0o.cart.0.0.91ad378dixEs7B&mp=1&gatewayAdapt=glo2fra)
* [Batterie (1 a 4)](https://fr.aliexpress.com/item/4000589667648.html?spm=a2g0o.cart.0.0.91ad378dixEs7B&mp=1&gatewayAdapt=glo2fra)
* Ecran port / Boitier interchangeable de port
* [Ecran 4 digit 7 segments](https://fr.aliexpress.com/item/1005003264584962.html?spm=a2g0o.productlist.main.1.67b8c33bemOQgE&algo_pvid=4b55ac04-9f25-4331-a404-64c4b2599449&algo_exp_id=4b55ac04-9f25-4331-a404-64c4b2599449-0&pdp_npi=4%40dis%21EUR%210.78%210.78%21%21%210.82%21%21%4021038ed816945911782337387eb248%2112000024920066404%21sea%21FR%210%21AS&curPageLogUid=bB1rbxYcZxTE)
* 2 croix indicateur
* Buzzer
* [cable 4 pin pour bus IIC](https://fr.aliexpress.com/item/1005004615616698.html?spm=a2g0o.productlist.main.3.9b7c21edUMRUYj&algo_pvid=5ef0370c-a8b3-4c6a-9dbc-de84275f74f6&algo_exp_id=5ef0370c-a8b3-4c6a-9dbc-de84275f74f6-1&pdp_npi=4%40dis%21EUR%213.03%210.49%21%21%213.19%21%21%4021038edf16929548244715213e3f09%2112000029927782269%21sea%21FR%210%21A&curPageLogUid=cG7Znv5CVgY8)

**Arduino ESP 32**
// E-ink : BUSY -> 4, RST -> 16, DC -> 17, CS -> SS(5), CLK -> SCK(18), DIN -> MOSI(23)

* 1	 TX
* 2	 Led RGB x2 (erreurs, PL9823)
* 3	 RX
* 4	 Busy eInk
* 5	 CS   eInk
* 12 DIN Max7219 x4 (pin de démarrage de l'ESP32 : le GPIO 19 est libre en cas de problème au boot)
* 13 CLK Max7219 x4
* 14 BP Diminue (tactile)
* 15 CS  Max7219 x4
* 16 RST eInk
* 17 DC  eInk
* 18 CLK eInk
* 19 /
* 21 SDA
* 22 SCL
* 23 DIN eInk
* 25 Son Bombe (actif à l'état bas)
* 26 Son Erreur (actif à l'état bas)
* 27 BP Augmente (tactile)
* 32 Son Victoire (actif à l'état bas)
* 33 Batterie (tension globale = nombre de piles)
* 34 BP START
* 35 /

**Fonctionnement du maître** :
* Avant la partie, il scanne le bus I2C (toutes les 400 ms) : nombre de modules et piles affichés, durée réglable de 2 à 30 min avec les deux touches tactiles.
* Si aucun module détecté, **la partie ne démarre pas** (clignotement des LEDs d'erreur). Le module port est en mermancance relié au master, sur le meme bandeau.
* Numéro de série : 6 caractères avec terminateur. Les caractères en double sont signalés aux modules (valeurs 6 à 9, voir tableau ci-dessous).
* La victoire est déclarée quand tous les modules détectés sont "finis" (les modules needle comptent comme finis quand ils dorment).

**Information IIC Master>Slave**
|valeur           |numero de série             |Batterie         |Port             |nombre erreur    |indicateur       |Temps            |
|:---------------:|:--------------------------:|:---------------:|:---------------:|:---------------:|:---------------:|:---------------:|
|0                |                            |0                |                 |0                |SND              |000 = rien       |
|1                |pair et voyelle             |1                |          HDMI   |1                |CLR              |001 = 1          |
|2                |impair et voyelle           |2                |         USB C   |2                |CAR              |010 = 4          |
|3                |pair et /voyelle            |3                |           USB   |3                |IND              |011 = 4 & 1      |
|4                |impair et /voyelle          |4                |          RJ45   |4                |FRQ              |100 = 5          |
|5                |                            |5                |          PS/2   |5                |SIG              |101 = 5 & 1      |
|6                |double et pair et voyelle   |6                |      Mono RCA   |6                |NSA              |110 = 5 & 4      |
|7                |double et impair et voyelle |7                |          Jack   |7                |MSA              |111 = 5 & 4 & 1  |
|8                |double et pair et /voyelle  |8                |                 |8                |TRN              |                 |
|9                |double et impair et /voyelle|9                |                 |9                |BOB              | START           |
|10               |                            |10               |                 |10               |FRK              |                 |

**Information IIC Slave>Master** (le module Port répond sur 3 octets : strike, module fini, port lu)
|valeur           |Strike (erreur)   |Etat du module    |Port connecté    |
|:---------------:|:----------------:|:----------------:|:---------------:|
|0                |pas d'erreur      |module arme       | Aucun           |
|1                |une erreur        |module fini       | HDMI            |
|2                |                  |                  | USB C           |
|3                |                  |                  | USB             |
|4                |                  |                  | RJ45            |
|5                |                  |                  | PS/2            |
|6                |                  |                  | Mono RCA        |
|7                |                  |                  | Jack            |
|8                |                  |                  |                 |
|9                |                  |                  |                 |
|10               |                  |                  |                 |


# 1 : Fils simple

**Obligatoire** :
* Led RGB avec support

* 6 entrée de fils droit
* 6 entrée de fil gauche

**Information à recevoir** :
* numéro de série impair

**Arduino NANO**
* D0	RX
* D1	TX
* D2	Led RGB
* D3	
* D4	
* D5	
* D6	
* D7	
* D8	
* D9	
* D10	
* D11	
* D12	
* D13	
* A0	Fil 6
* A1	Fil 5
* A2	Fil 4
* A3	Fil 3
* A4	SDA
* A5	SCL
* A6	Fil 2
* A7	Fil 1

***Faire des fils*** :

* 3 noir  33    Ohm
* 3 rouge 330   Ohm
* 3 jaune 1000  Ohm
* 3 bleu  3300  Ohm
* 3 blanc 22000 Ohm

# 2 : Bouton
**Obligatoire**:
* Led RGB avec support

* Anneau led RGB (_Bleu_, _Blanc_, _Jaune_, _Rouge_, /_autre_)
* [Texte (	_Annuler_, _Exploser_, _Maintenir_](https://fr.aliexpress.com/item/1005005034354794.html?spm=a2g0o.productlist.main.1.3e0c4d74qFsGpg&algo_pvid=e9a08e5d-dd14-4c41-8e84-e41d38caf7a9&algo_exp_id=e9a08e5d-dd14-4c41-8e84-e41d38caf7a9-0&pdp_npi=4%40dis%21EUR%213.02%212.12%21%21%213.18%21%21%40211b88ec16938577556432127e1a2d%2112000031402247718%21sea%21FR%21776324173%21&curPageLogUid=pxyBuX3BettJ)
* Bande RGB (_bleu_, _blanc_, _jaune_, /_autre_)

**Information à recevoir** :
* plus de 2 piles
* Indicateur

**Arduino NANO**
* D0	RX
* D1	TX
* D2	Led RGB
* D3	Bande Led (4)
* D4	Anneau Led (8)
* D5	
* D6	
* D7	
* D8	Reset écran
* D9	DC écran
* D10	CS écran
* D11	Data écran
* D12	
* D13	Clock écran
* A0	Bouton
* A1	
* A2	
* A3	
* A4	SDA
* A5	SCL
* A6	
* A7	

# 3 : Symboles
**Obligatoire** :
* Led RGB avec support

* 4 bouton poussoir
* [ecran ST7920 - 128x64 px](https://arduino-tutorials.net/tutorial/control-graphic-lcd-display-spi-st7920-128x64-with-arduino)

**Information à recevoir** :
* NAN
* [liste des symboles](https://ktane.fandom.com/wiki/Keypad)

|Possibilité 1           |Possibilité 2          |Possibilité 3          |Possibilité 4          |Possibilité 5          |Possibilité 6          |
|:----------------------:|:---------------------:|:---------------------:|:---------------------:|:---------------------:|:---------------------:|
|125-Balon               |115-E2points           |101-Copyright          |110-Six                |122-Fourche            |110-Six                |
|112-AT                  |125-Balon              |108-Cul                |119-Paragraph          |104-Smiley             |115-E2points           |
|126-Ytete               |121-Cgauche            |123-Infogramme         |127-BT                 |127-BT                 |124-CroixLorraine      |
|111-Nalenvers           |123-Infogramme         |105-DoubleK            |107-SquidGame          |120-Cdroit             |113-AdansE             |
|107-SquidGame           |103-EtoileBlanche      |114-Troisfondu         |105-DoubleK            |119-Paragraph          |122-Fourche            |
|109-Hvirgule            |109-Hvirgule           |126-Ytete              |118-Pointdinterogation |117-3serpent           |116-Nchapeau           |
|121-Cgauche             |118-Pointdinterogation |103-EtoileBlanche      |104-Smiley             |102-EtoileNoir         |106-Omega              |

**Arduino NANO**
* D0	RX
* D1	TX
* D2	Led RGB
* D3	
* D4	
* D5	
* D6	
* D7	
* D8	Reset écran
* D9	
* D10	CS écran
* D11	Data écran
* D12	
* D13	Clock écran
* A0	Bouton 1
* A1	Bouton 2
* A2	Bouton 3
* A3	Bouton 4
* A4	SDA
* A5	SCL
* A6	
* A7	

[Convertisseur image arduino](https://javl.github.io/image2cpp/?pseSrc=pgEcranOledArduino)

# 4 : SIMON

**Obligatoire** :
* Led RGB avec support

* 4 bouton poussoir lumineux

**Information à recevoir** :
* numéro de série [_voyelle_]

**Arduino NANO**
* D0	RX
* D1	TX
* D2	Led RGB
* D3	Lumière rouge
* D4	Lumière bleue
* D5	Lumière jaune
* D6	Lumière verte
* D7	
* D8	
* D9	
* D10	
* D11	
* D12	
* D13	
* A0	Bouton rouge
* A1	Bouton bleu
* A2	Bouton jaune
* A3	Bouton vert
* A4	SDA
* A5	SCL
* A6	
* A7	

# 5 : Jeux de mots ?
**Obligatoire** :
* Led RGB avec support

* Led niveau x3
* 6 bouton poussoir
* [Ecran SSD1306](https://passionelectronique.fr/ecran-oled-i2c-arduino/)
* [sinon ecran ST7920 - 128x64 px](https://arduino-tutorials.net/tutorial/control-graphic-lcd-display-spi-st7920-128x64-with-arduino)

**Information à recevoir** :
* NAN

**Arduino NANO**
* D0	RX
* D1	TX
* D2	Led RGB
* D3	
* D4	Bouton 6
* D5	Bouton 4
* D6	
* D7	
* D8	Reset écran
* D9	
* D10	CS écran
* D11	Data écran
* D12	
* D13	Clock écran
* A0	Bouton 1
* A1	Bouton 3
* A2	Bouton 5
* A3	Bouton 2
* A4	SDA
* A5	SCL
* A6	
* A7	

# 6 : Memoire

**Obligatoire** :
* Led RGB avec support

* MAX7219 pour le chiffre du haut
* [Afficheur 4 digit 7 segment (pas de IIC)](https://fr.aliexpress.com/item/1005004852285898.html?spm=a2g0o.cart.0.0.91ad378djBu8C8&mp=1&gatewayAdapt=glo2fra)
* Bloc de led en rampe
* 4 boutons

**Information à recevoir** :
* NAN

**Arduino NANO**
* D0	RX
* D1	TX
* D2	Led RGB
* D3	DIO TM1637
* D4	CLK TM1637
* D5	
* D6	
* D7	
* D8	
* D9	
* D10	CLK Max7219
* D11	CS Max7219
* D12	DIN Max7219
* D13	
* A0	Bouton 4
* A1	Bouton 3
* A2	Bouton 2
* A3	Bouton 1
* A4	SDA
* A5	SCL
* A6	
* A7	

# 7 : MORSE

**Obligatoire** :
* Led RGB avec support

* Led pour morse
* [Afficheur 4 digit 7 segment (pas de IIC)](https://fr.aliexpress.com/item/1005004852285898.html?spm=a2g0o.cart.0.0.91ad378djBu8C8&mp=1&gatewayAdapt=glo2fra)
* 3 bouton

**Information à recevoir** :
* NAN

**Arduino NANO**
* D0	RX
* D1	TX
* D2	Led RGB
* D3	Led Morse
* D4	DIO TM1637
* D5	CLK TM1637
* D6	
* D7	
* D8	
* D9	
* D10	
* D11	
* D12	
* D13	
* A0	Bouton fréquence -
* A1	Bouton valider
* A2	Bouton fréquence +
* A3	
* A4	SDA
* A5	SCL
* A6	
* A7	

# 8 : Fils compliqués

**Obligatoire** :
* Led RGB avec support

* 6 led etoiles
* 6 led blanches
* 6 prises hautes
* 6 prises basses

**Information à recevoir** :
* numéro de série [_Pair_]
* port USB connecté (le port « parallèle » de la notice**Arduino NANO**
* D0	RX
* D1	TX
* D2	Led RGB
* D3	Led étoile (6)
* D4	Led blanche (6)
* D5	
* D6	
* D7	
* D8	
* D9	
* D10	
* D11	
* D12	
* D13	
* A0	Fil 1
* A1	Fil 2
* A2	Fil 3
* A3	Fil 4
* A4	SDA
* A5	SCL
* A6	Fil 5
* A7	Fil 6
12	
*	13	
* A0	Fil 1
* A1	Fil 2
* A2	Fil 3
* A3	Fil 4
* A4	SDA
* A5	SCL
* A6	Fil 5
* A7	Fil 6

***Faire des fils*** :

* 3 noir           33    Ohm
* 3 rouge          330   Ohm
* 3 bleu et rouge  1000  Ohm
* 3 bleu           3300  Ohm
* 3 blanc          22000 Ohm

# 9 : Labyrinthe

**Obligatoire** :
* Led RGB avec support
* carré de 6x6 led RGB ( [ou 8x8](https://fr.aliexpress.com/item/32600043941.html?spm=a2g0o.productlist.main.15.440e23faWMR9GR&algo_pvid=6831d2f4-16e0-404c-93f2-d6c32b484f47&algo_exp_id=6831d2f4-16e0-404c-93f2-d6c32b484f47-7&pdp_npi=4%40dis%21EUR%212.78%212.25%21%21%212.95%21%21%4021038edf16927990655851540e3f17%2159101695247%21sea%21FR%210%21A&curPageLogUid=oUTrEPINmbcc))
* 4 boutons

**Information à recevoir** :
* NAN

**Arduino NANO**
* D0	RX
* D1	TX
* D2	Led RGB
* D3	Led labyrinthe (64)
* D4	
* D5	
* D6	
* D7	
* D8	
* D9	
* D10	
* D11	
* D12	
* D13	
* A0	Bouton Gauche
* A1	Bouton Bas
* A2	Bouton Droite
* A3	Bouton Haut
* A4	SDA
* A5	SCL
* A6	
* A7	

# 10 : Mot de passe

**Obligatoire** :
* Led RGB avec support
* [Ecran SSD1306](https://passionelectronique.fr/ecran-oled-i2c-arduino/)
* [sinon ecran ST7920 - 128x64 px](https://arduino-tutorials.net/tutorial/control-graphic-lcd-display-spi-st7920-128x64-with-arduino)
* 5 boutons haut
* 5 boutons bas
* 1 bouton valider

**Information à recevoir** :
* NAN

**Arduino NANO**
* D0	RX
* D1	TX
* D2	Led RGB
* D3	
* D4	
* D5	
* D6	
* D7	
* D8	Reset écran
* D9	
* D10	CS écran
* D11	Data écran
* D12	
* D13	Clock écran
* A0	
* A1	5 boutons bas (échelle de résistances)
* A2	5 boutons haut (échelle de résistances)
* A3	Bouton valider
* A4	SDA
* A5	SCL
* A6	
* A7	

Les boutons haut/bas sont lus en analogique (échelle de résistances) : 0, 225, 425, 625 et 825 environ (valeurs 0 à 1023).

# 11 : Math emoji

**Obligatoire** :
* Led RGB avec support
* Ecran ST7567 128x64
* Clavier 4x3 (chiffres, * et #)

**Information à recevoir** :
* NAN

L'écran affiche un calcul de deux nombres de deux chiffres, chaque chiffre étant un smiley (0 `:)`, 1 `=(`, 2 `(:`, 3 `)=`, 4 `:(`, 5 `):`, 6 `=)`, 7 `(=`, 8 `:|`, 9 `|:`). Le joueur tape le résultat, `*` change le signe, `#` valide.

**Arduino NANO**
* D0	RX
* D1	TX
* D2	Led RGB
* D3	Colonne 1 clavier
* D4	Colonne 2 clavier
* D5	Colonne 3 clavier
* D6	
* D7	
* D8	Reset écran
* D9	DC écran
* D10	CS écran
* D11	Data écran
* D12	
* D13	Clock écran
* A0	Ligne 1 clavier
* A1	Ligne 2 clavier
* A2	Ligne 3 clavier
* A3	Ligne 4 clavier
* A4	SDA
* A5	SCL
* A6	
* A7	

# 12 : Questions réponses (needle)

**Obligatoire** :
* Ecran ST7920 - 128x64 px (rétro-éclairage commandé)
* Afficheur 4 digit 7 segments (TM1637) pour le compte à rebours
* 2 boutons OUI / NON

**Information à recevoir** :
* nombre d'erreurs
* série avec caractères en double (numéro de série de 6 à 9)

Module needle : il dort (module "fini"), se réveille au hasard, pose une des 11 questions et laisse 20 secondes pour répondre. Mauvaise réponse ou temps écoulé : strike. Les questions 10 et 11 dépendent de la réponse précédente.

**Arduino NANO**
* D0	RX
* D1	TX
* D2	
* D3	
* D4	DIO TM1637
* D5	CLK TM1637
* D6	
* D7	
* D8	Reset écran
* D9	
* D10	CS écran
* D11	Data écran
* D12	
* D13	Clock écran
* A0	Bouton OUI
* A1	Bouton NON
* A2	
* A3	Commande de l'écran (LOW = question affichée)
* A4	SDA
* A5	SCL
* A6	
* A7	

Pas de led RGB sur ce module.

# 13 : Port

**Obligatoire** :
* Led RGB avec support
* Lecteur NFC PN532 (SPI)
* Un tag NFC par port (HDMI, USB C, USB, RJ45, PS/2, Mono RCA, Jack), le joueur en pose un sur le lecteur

**Fonctionnement** :
* **Avant la partie** : dès qu'un tag reconnu est lu, la led passe au vert et le port est transmis au maître. Tag retiré ou inconnu : rouge, et le maître refuse de démarrer.
* **Pendant la partie** : le module est "fini" (vert) tant que le port choisi au démarrage est présent. Port retiré (ou changé) : rouge, module non fini et **une erreur**. Il repasse au vert quand le bon port revient.
* Une lecture ratée ne suffit pas à déclarer le port retiré : `MANQUES_MAX` lectures de suite (2 par défaut).
* Le module répond au maître sur 3 octets : strike, module fini, port lu.

**Arduino NANO**
* D0	RX
* D1	TX
* D2	Led RGB
* D3	
* D4	
* D5	
* D6	
* D7	
* D8	
* D9	
* D10	CS PN532
* D11	MOSI PN532
* D12	MISO PN532
* D13	SCK PN532
* A0	
* A1	
* A2	
* A3	
* A4	SDA
* A5	SCL
* A6	
* A7	

# 14 : Molette (needle)

**Obligatoire** :
* Led RGB avec support
* 12 Led NeoPixel (2 rangées de 6)
* Afficheur 4 digit 7 segments (TM1637) pour le compte à rebours
* Commutateur rotatif 1 pôle 4 positions (SP4T) avec son bouton

**Information à recevoir** :
* NAN

Module needle : il dort (module "fini"), se réveille au hasard, affiche un des 8 motifs du manuel et un compte à rebours (20 s). A 0, la molette doit être sur la bonne position (haut, droite, bas, gauche), sinon strike.

Les 12 led : 0 à 5 = rangée du haut (gauche vers droite), 6 à 11 = rangée du bas.

Câblage de la molette : 3 résistances identiques (10 kOhm) en série entre 5V et GND, 4 prises (GND, entre R1 et R2, entre R2 et R3, 5V), la broche commune du commutateur sur A0. Valeurs lues : environ 0 (haut), 341 (droite), 682 (bas), 1023 (gauche). La valeur est affichée sur le moniteur série pour le réglage (`ZONE_MAX`). Si le commutateur coupe le contact entre deux positions, ajouter 100 kOhm entre A0 et GND.

**Arduino NANO**
* D0	RX
* D1	TX
* D2	Led RGB
* D3	Led motif (12)
* D4	DIO TM1637
* D5	CLK TM1637
* D6	
* D7	
* D8	
* D9	
* D10	
* D11	
* D12	
* D13	
* A0	Molette (échelle de résistances)
* A1	
* A2	
* A3	
* A4	SDA
* A5	SCL
* A6	
* A7	

# 15 : Condensateur (needle)

**Obligatoire** :
* Led RGB avec support
* 10 Led NeoPixel (jauge de charge)
* 1 levier à retour par ressort (ou bouton) à maintenir

**Information à recevoir** :
* NAN

Module needle : il dort (led verte), se réveille au hasard (led bleue). Le condensateur se charge seul : chaque led monte par paliers de 10 % d'intensité, 4,5 s par led (45 s pour les 10). Le joueur maintient le levier pour le décharger (10 s depuis plein) ; s'il lâche, la charge remonte. Jauge vide : le module se rendort. Au-dessus de 80 % la led d'état est orange. Jauge pleine : strike (rouge 600 ms) puis retour au repos.

Réglages en tête du fichier : `TEMPS_MONTEE_S`, `TEMPS_DECHARGE_S`, délais de réveil, `REACTIVER_APRES_STRIKE` (0 = comme dans le jeu, ne se réveille plus après un strike).

**Arduino NANO**
* D0	RX
* D1	TX
* D2	Led RGB
* D3	Jauge (10 led)
* D4	
* D5	
* D6	
* D7	
* D8	
* D9	
* D10	
* D11	
* D12	
* D13	
* A0	Levier (vers GND, pull-up interne)
* A1	
* A2	
* A3	
* A4	SDA
* A5	SCL
* A6	
* A7	

# Ports

* [DVI-D](https://fr.aliexpress.com/item/1005004038612277.html?spm=a2g0o.detail.1000014.11.5c4bLcgQLcgQKT&gps-id=pcDetailBottomMoreOtherSeller&scm=1007.14452.335519.0&scm_id=1007.14452.335519.0&scm-url=1007.14452.335519.0&pvid=cbab142e-5072-432f-ab52-67e4e326a50b&_t=gps-id:pcDetailBottomMoreOtherSeller,scm-url:1007.14452.335519.0,pvid:cbab142e-5072-432f-ab52-67e4e326a50b,tpp_buckets:668%232846%238114%231999&isseo=y&pdp_npi=4%40dis%21EUR%211.13%211.03%21%21%211.20%21%21%40211b440316927160483684695e2b20%2112000027821900854%21rec%21FR%21%21A&search_p4p_id=202308220754083956400115800657590558_2)
* [Parallèle](https://fr.aliexpress.com/item/4000047329316.html?spm=a2g0o.detail.1000014.4.797d6d9eOBjBeH&gps-id=pcDetailBottomMoreOtherSeller&scm=1007.40050.281175.0&scm_id=1007.40050.281175.0&scm-url=1007.40050.281175.0&pvid=9a03efd2-6013-4c83-98a1-f2d37e822c91&_t=gps-id:pcDetailBottomMoreOtherSeller,scm-url:1007.40050.281175.0,pvid:9a03efd2-6013-4c83-98a1-f2d37e822c91,tpp_buckets:668%232846%238114%231999&isseo=y&pdp_npi=4%40dis%21EUR%211.71%211.44%21%21%211.82%21%21%40211b61bb16927154830814419e390e%2110000000107114516%21rec%21FR%21%21A)
* [PS/2](https://fr.aliexpress.com/item/1005005259319987.html?spm=a2g0o.productlist.main.29.48484904nVSggT&algo_pvid=0fd09721-e976-4b37-9c78-ac32062dc17b&aem_p4p_detail=202308230649275958797922476310003256750&algo_exp_id=0fd09721-e976-4b37-9c78-ac32062dc17b-14&pdp_npi=4%40dis%21EUR%211.35%211.35%21%21%211.43%21%21%4021038edf16927985678026519e3f17%2112000032393614659%21sea%21FR%210%21A&curPageLogUid=Bx5ayIH5g9hq&search_p4p_id=202308230649275958797922476310003256750_3)
* [RJ-45](https://fr.aliexpress.com/item/1005003440343072.html?spm=a2g0o.productlist.main.57.5f5a326djM69zN&algo_pvid=6ce36167-250c-4633-beec-b0db1c915bbc&algo_exp_id=6ce36167-250c-4633-beec-b0db1c915bbc-28&pdp_npi=4%40dis%21EUR%218.89%212.22%21%21%219.47%21%21%40211b88ee16927161674517196e048a%2112000025804507239%21sea%21FR%210%21A&curPageLogUid=N1tBONFJKh4e)
* [Serie](https://fr.aliexpress.com/item/4000047329316.html?spm=a2g0o.detail.1000014.4.797d6d9eOBjBeH&gps-id=pcDetailBottomMoreOtherSeller&scm=1007.40050.281175.0&scm_id=1007.40050.281175.0&scm-url=1007.40050.281175.0&pvid=9a03efd2-6013-4c83-98a1-f2d37e822c91&_t=gps-id:pcDetailBottomMoreOtherSeller,scm-url:1007.40050.281175.0,pvid:9a03efd2-6013-4c83-98a1-f2d37e822c91,tpp_buckets:668%232846%238114%231999&isseo=y&pdp_npi=4%40dis%21EUR%211.71%211.44%21%21%211.82%21%21%40211b61bb16927154830814419e390e%2110000000107114516%21rec%21FR%21%21A)
* [Stéréo](https://fr.aliexpress.com/item/1005004497370750.html?spm=a2g0o.productlist.main.61.36cc5f496NeInI&algo_pvid=ca4c1a91-cd05-49af-ab91-b394a0351c59&algo_exp_id=ca4c1a91-cd05-49af-ab91-b394a0351c59-30&pdp_npi=4%40dis%21EUR%213.09%212.25%21%21%213.28%21%21%4021038edf16927986759581682e3f17%2112000029367206269%21sea%21FR%210%21A&curPageLogUid=VKayGXn6apSH)
* [usb A](https://fr.aliexpress.com/item/1005004627694781.html?spm=a2g0o.detail.1000014.19.4ba935077YEAB2&gps-id=pcDetailBottomMoreOtherSeller&scm=1007.40050.281175.0&scm_id=1007.40050.281175.0&scm-url=1007.40050.281175.0&pvid=ee3f6211-8b18-4ab0-ab10-822e0e92f7ec&_t=gps-id:pcDetailBottomMoreOtherSeller,scm-url:1007.40050.281175.0,pvid:ee3f6211-8b18-4ab0-ab10-822e0e92f7ec,tpp_buckets:668%232846%238114%231999&isseo=y&pdp_npi=4%40dis%21EUR%210.46%210.44%21%21%210.49%21%21%40211b446016927163931054313ef1a7%2112000029890523502%21rec%21FR%21%21A)

# Historique des corrections

* **Maître** : tampon I2C porté à 6 octets, numéro de série avec terminateur (plus de caractère nul possible), doublons du numéro de série transmis aux modules, port lu sur le module Port, démarrage refusé sans port, tableau de réception à 3 octets, réponse remise à zéro avant chaque lecture, limite de 16 modules.
* **Questions Reponses** : une mauvaise réponse aux questions 7 à 11 donne maintenant un strike.
* **Memoire** : index des étages 3 et 5 corrigés, plus de lecture hors tableau à la fin, plus d'appuis perdus.
* **Fils compliqués** : strike et module fini envoyés, tirage des fils corrigé (plus de boucle infinie), `PORT_USB` à la place du port parallèle.
* **Fils simples** : recherche du dernier fil corrigée.
* **Simon** : test de voyelle fait après la correction du numéro de série, nombre d'erreurs borné à 2.
* **Jeux de mots** : nombre de niveaux défini avant le premier affichage.
* **Emojy Math** : strike envoyé, démarrage forcé supprimé.
* **Morse** : accolades du dernier `else`.
* **Mot de passe** : un seul sketch (46), accès hors tableau corrigés.
* **Port** : nouvelle logique vert / rouge, erreur si le port est retiré en partie.
* **Tous les modules** : `Strike`, `Module_fini`, `Demmarage` en `volatile`, protection de la réception I2C.
* **Nouveaux modules** : Molette (101) et Condensateur (96).
