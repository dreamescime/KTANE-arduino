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
// ESP8266  BUSY -> 4, RST -> 16, DC -> 17, CS -> SS(5), CLK -> SCK(18), DIN -> MOSI(23)

* 1	 TX
* 2	 /
* 3	 RX
* 4	 Busy eInk
* 5	 CS   eInk
* 12 CLK
* 13 DIO
* 14 Led RGB
* 15 
* 16 RST eInk
* 17 DC  eInk
* 18 CLK eInk
* 19 
* 21 SDA
* 22 SCL
* 23 DIN eInk
* 25 Port 1
* 26 Port 2
* 27 Led Erreurs
* 32 Batterie 2
* 33 Batterie 1
* 34 Batterie 4
* 35 Batterie 3

**Information IIC Master>Slave**
|valeur           |numero de série   |Batterie         |Port             |nombre erreur    |indicateur       |Temps              |
|:---------------:|:----------------:|:---------------:|:---------------:|:---------------:|:---------------:|:---------------:|
|0                |                  |0                |                 |0                |SND              |000 = rien       |
|1                |pair et voyelle   |1                |0 1.......DVID   |1                |CLR              |001 = 1          |
|2                |impair et voyelle |2                |0 2..Parallele   |2                |CAR              |010 = 4          |
|3                |pair et /voyelle  |3                |1 0........PS2   |3                |IND              |100 = 5          |
|4                |impair et /voyelle|4                |1 1.......RJ45   |4                |FRQ              |011 = 4 & 1      |
|5                |                  |5                |1 2......Serie   |5                |SIG              |101 = 5 & 1      |
|6                |                  |6                |2 0.Stereo RCA   |6                |NSA              |110 = 5 & 4      |
|7                |                  |7                |2 1........USB   |7                |MSA              |111 = 5 & 4 & 1  |
|8                |                  |8                |                 |8                |TRN              |                 |
|9                |                  |9                |                 |9                |BOB              |                 |
|10               |                  |10               |                 |10               |FRK              |                 |

**Information IIC Slave>Master**
|valeur           |Strike (erreur)   |Etat du module    |
|:---------------:|:----------------:|:----------------:|
|0                |pas d'erreur      |module arme       |
|1                |une erreur        |module fini       |



# 1 : Fils simple

**Obligatoire** :
* Led RGB avec support

* 6 entrée de fils droit
* 6 entrée de fil gauche

**Information à recevoir** :
* numéro de série impair

**Arduino NANO**
* 0	RX
* 1	TX
* 2	Led RGB
* 3	
* 4	
* 5	
* 6	
* 7	
* 8	
* 9	
* 10	
* 11	
* 12	
* 13	
* A0	Fil 1
* A1	Fil 2
* A2	Fil 3
* A3	Fil 4
* A4	SDA
* A5	SCL
* A6	Fil 5
* A7	Fil 6

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
* 0	RX
* 1	TX
* 2	Led RGB
* 3	Bouton
* 4	Anneau Led
* 5	Bande LED
* 6	
* 7	
* 8	
* 9	
* 10	
* 11	
* 12	
* 13	
* A0	
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
*	0	RX
*	1	TX
*	2	Led RGB
*	3	bouton 1
*	4	bouton 2
*	5	bouton 3
*	6	bouton 4
*	7	
*	8	reset ecran
*	9	
*	10	CS ecran
*	11	data ecran
* 12	
*	13	clock ecran
*	A0	
*	A1	
*	A2	
*	A3	
*	A4	SDA
*	A5	SCL
*	A6	
*	A7	

[Convertisseur image arduino](https://javl.github.io/image2cpp/?pseSrc=pgEcranOledArduino)

# 4 : SIMON

**Obligatoire** :
* Led RGB avec support

* 4 bouton poussoir lumineux

**Information à recevoir** :
* numéro de série [_voyelle_]

**Arduino NANO** 
*	0	RX
*	1	TX
*	2	Led RGB
*	3	bouton 1
*	4	bouton 2
*	5	bouton 3
*	6	bouton 4
*	7	lumiere 1
*	8	lumiere 2
*	9	lumiere 3
*	10	lumiere 4
*	11	
*	12	
*	13	
*	A0	
*	A1	
*	A2	
*	A3	
*	A4	SDA
*	A5	SCL
*	A6	
*	A7	


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
*	0	RX
*	1	TX
*	2	Led RGB
*	3	bouton 1
*	4	bouton 2
*	5	bouton 3
*	6	bouton 4
*	7	bouton 5
*	8	bouton 6
*	9	
*	10	
*	11	
* 12	
*	13	
*	A0	
*	A1	
*	A2	
*	A3	
*	A4	SDA
*	A5	SCL
*	A6	
*	A7	

# 6 : Memoire

**Obligatoire** :
* Led RGB avec support

* Afficheur 7 segments a cabler
* [Afficheur 4 digit 7 segment (pas de IIC)](https://fr.aliexpress.com/item/1005004852285898.html?spm=a2g0o.cart.0.0.91ad378djBu8C8&mp=1&gatewayAdapt=glo2fra)
* Bloc de led en rampe
* 4 boutons

**Information à recevoir** :
* NAN

**Arduino NANO** 
*	0	RX
*	1	TX
*	2	Led RGB
*	3	Segment A
*	4	Segment B
*	5	Segment C
*	6	Segment D
*	7	Segment E
*	8	Segment F
*	9	Segment G
*	10	Bouton 1
*	11	Bouton 2
*	12	Bouton 3
*	13	Bouton 4
*	A0	Led 1
*	A1	Led 2
*	A2	Led 3
*	A3	Led 4
*	A4	SDA
*	A5	SCL
*	A6	
*	A7	


# 7 : MORSE

**Obligatoire** :
* Led RGB avec support

* Led pour morse
* [Afficheur 4 digit 7 segment (pas de IIC)](https://fr.aliexpress.com/item/1005004852285898.html?spm=a2g0o.cart.0.0.91ad378djBu8C8&mp=1&gatewayAdapt=glo2fra)
* 3 bouton

**Information à recevoir** :
* NAN

**Arduino NANO** 
*	0	RX
*	1	TX
*	2	Led RGB
*	3	bouton -
*	4	bouton +
*	5	bouton valid
*	6	
*	7	
*	8	
*	9
*	10	
*	11	
*	12	
*	13	
*	A0  
*	A1	
*	A2	
*	A3	
*	A4	SDA
*	A5	SCL
*	A6	
*	A7	

# 8 : Fils compliqués

**Obligatoire** :
* Led RGB avec support

* 6 led etoiles
* 6 led blanches
* 6 prises hautes
* 6 prises basses

**Information à recevoir** :
* numéro de série [_Pair_]
* presence port parrallele
* presence de + de 2 piles

**Arduino NANO** 
*	0	RX
*	1	TX
*	2	Led RGB
*	3	Led blanche
*	4	Led etoile
*	5	
*	6	
*	7	
*	8	
*	9	
*	10	
*	11	
*	12	
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
*	0	RX
*	1	TX
*	2	Led RGB
*	3	Bouton Haut
*	4	Bouton Bas
*	5	Bouton Droit
*	6	Bouton Gauche
*	7	
*	8	
*	9	
*	10	
*	11	
*	12	
*	13	
*	A0	
*	A1	
*	A2	
*	A3	
*	A4	SDA
*	A5	SCL
*	A6	
*	A7	

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
*	0	RX
*	1	TX
*	2	Led RGB
*	3	Bouton H1
*	4	Bouton H2
*	5	Bouton H3
*	6	Bouton H4
*	7	Bouton H5
*	8	Bouton B1
*	9	Bouton B2
*	10	CS
*	11	Data
*	12	Bouton valide
*	13	Clock
*	A0	Bouton B3
*	A1	Bouton B4
*	A2	Bouton B5
*	A3	
*	A4	SDA
*	A5	SCL
*	A6	
*	A7


# Ports

* [DVI-D](https://fr.aliexpress.com/item/1005004038612277.html?spm=a2g0o.detail.1000014.11.5c4bLcgQLcgQKT&gps-id=pcDetailBottomMoreOtherSeller&scm=1007.14452.335519.0&scm_id=1007.14452.335519.0&scm-url=1007.14452.335519.0&pvid=cbab142e-5072-432f-ab52-67e4e326a50b&_t=gps-id:pcDetailBottomMoreOtherSeller,scm-url:1007.14452.335519.0,pvid:cbab142e-5072-432f-ab52-67e4e326a50b,tpp_buckets:668%232846%238114%231999&isseo=y&pdp_npi=4%40dis%21EUR%211.13%211.03%21%21%211.20%21%21%40211b440316927160483684695e2b20%2112000027821900854%21rec%21FR%21%21A&search_p4p_id=202308220754083956400115800657590558_2)
* [Parallèle](https://fr.aliexpress.com/item/4000047329316.html?spm=a2g0o.detail.1000014.4.797d6d9eOBjBeH&gps-id=pcDetailBottomMoreOtherSeller&scm=1007.40050.281175.0&scm_id=1007.40050.281175.0&scm-url=1007.40050.281175.0&pvid=9a03efd2-6013-4c83-98a1-f2d37e822c91&_t=gps-id:pcDetailBottomMoreOtherSeller,scm-url:1007.40050.281175.0,pvid:9a03efd2-6013-4c83-98a1-f2d37e822c91,tpp_buckets:668%232846%238114%231999&isseo=y&pdp_npi=4%40dis%21EUR%211.71%211.44%21%21%211.82%21%21%40211b61bb16927154830814419e390e%2110000000107114516%21rec%21FR%21%21A)
* [PS/2](https://fr.aliexpress.com/item/1005005259319987.html?spm=a2g0o.productlist.main.29.48484904nVSggT&algo_pvid=0fd09721-e976-4b37-9c78-ac32062dc17b&aem_p4p_detail=202308230649275958797922476310003256750&algo_exp_id=0fd09721-e976-4b37-9c78-ac32062dc17b-14&pdp_npi=4%40dis%21EUR%211.35%211.35%21%21%211.43%21%21%4021038edf16927985678026519e3f17%2112000032393614659%21sea%21FR%210%21A&curPageLogUid=Bx5ayIH5g9hq&search_p4p_id=202308230649275958797922476310003256750_3)
* [RJ-45](https://fr.aliexpress.com/item/1005003440343072.html?spm=a2g0o.productlist.main.57.5f5a326djM69zN&algo_pvid=6ce36167-250c-4633-beec-b0db1c915bbc&algo_exp_id=6ce36167-250c-4633-beec-b0db1c915bbc-28&pdp_npi=4%40dis%21EUR%218.89%212.22%21%21%219.47%21%21%40211b88ee16927161674517196e048a%2112000025804507239%21sea%21FR%210%21A&curPageLogUid=N1tBONFJKh4e)
* [Serie](https://fr.aliexpress.com/item/4000047329316.html?spm=a2g0o.detail.1000014.4.797d6d9eOBjBeH&gps-id=pcDetailBottomMoreOtherSeller&scm=1007.40050.281175.0&scm_id=1007.40050.281175.0&scm-url=1007.40050.281175.0&pvid=9a03efd2-6013-4c83-98a1-f2d37e822c91&_t=gps-id:pcDetailBottomMoreOtherSeller,scm-url:1007.40050.281175.0,pvid:9a03efd2-6013-4c83-98a1-f2d37e822c91,tpp_buckets:668%232846%238114%231999&isseo=y&pdp_npi=4%40dis%21EUR%211.71%211.44%21%21%211.82%21%21%40211b61bb16927154830814419e390e%2110000000107114516%21rec%21FR%21%21A)
* [Stéréo](https://fr.aliexpress.com/item/1005004497370750.html?spm=a2g0o.productlist.main.61.36cc5f496NeInI&algo_pvid=ca4c1a91-cd05-49af-ab91-b394a0351c59&algo_exp_id=ca4c1a91-cd05-49af-ab91-b394a0351c59-30&pdp_npi=4%40dis%21EUR%213.09%212.25%21%21%213.28%21%21%4021038edf16927986759581682e3f17%2112000029367206269%21sea%21FR%210%21A&curPageLogUid=VKayGXn6apSH)
* [usb A](https://fr.aliexpress.com/item/1005004627694781.html?spm=a2g0o.detail.1000014.19.4ba935077YEAB2&gps-id=pcDetailBottomMoreOtherSeller&scm=1007.40050.281175.0&scm_id=1007.40050.281175.0&scm-url=1007.40050.281175.0&pvid=ee3f6211-8b18-4ab0-ab10-822e0e92f7ec&_t=gps-id:pcDetailBottomMoreOtherSeller,scm-url:1007.40050.281175.0,pvid:ee3f6211-8b18-4ab0-ab10-822e0e92f7ec,tpp_buckets:668%232846%238114%231999&isseo=y&pdp_npi=4%40dis%21EUR%210.46%210.44%21%21%210.49%21%21%40211b446016927163931054313ef1a7%2112000029890523502%21rec%21FR%21%21A)
