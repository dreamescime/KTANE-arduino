# 0 : Module Maitre

**Obligatoire** :
* Ecran numéro de série
* Ecran port / Boitier interchangeable de port
* Ecran 4 digit 7 segments
* 2 croix indicateur
* Buzzer

**Arduino ESP 32**
// ESP8266 SS=15,SCL(SCK)=14,SDA(MOSI)=13,BUSY=16,RST=5,DC=4
* 0	 /
* 1	 TX
* 2	 /
* 3	 RX
* 4	 RST eInk
* 5	 DC  eInk
* 6	 /
* 7	 /
* 8	 /
* 9	 /
* 10 /
* 11 /
* 12 /
* 13 
* 14 
* 15 
* 16 
* 17 
* 18 
* 19 
* 20 
* 21 SDA
* 22 SCL
* 23 
* 24 
* 25 
* 26 
* 27 
* 28 
* 29 
* 30 
* 31 
* 32 
* 33 
* 34 
* 35 
* 36 input
* 37 input
* 38 input
* 39 input



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
* Texte (	_Annuler_, _Exploser_, _Maintenir_
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
* [Ecran SSD1306](https://passionelectronique.fr/ecran-oled-i2c-arduino/)
* [sinon ecran ST7920 - 128x64 px](https://arduino-tutorials.net/tutorial/control-graphic-lcd-display-spi-st7920-128x64-with-arduino)

**Information à recevoir** :
* NAN

* [liste des symboles](https://ktane.fandom.com/wiki/Keypad)
|Possibilité 1        |Possibilité 2       |Possibilité 3       |Possibilité 4       |Possibilité 5       |Possibilité 6       |
|:-------------------:|:------------------:|:------------------:|:------------------:|:------------------:|:------------------:|
|Qbite                |E2points            |Cedansrond          |6trais              |Fourchette          |6trais              |
|Abite                |Qbite               |Wvage               |Pligne              |Tirelangue          |E2points            |
|Ytete                |Cpoint              |Infogramme          |BdansT              |BdansT              |CroixLorraine       |
|Nalenvers            |Infogramme          |DoubleK             |Htriangle           |Cpoint              |AdansE              |
|Htriangle            |EtoileBlanche       |3bite               |DoubleK             |Pligne              |Fourchette          |
|Hbite                |Hbite               |Ytete               |Pointdinterogation  |3serpent            |Nbite               |
|Cpoint               |Pointdinterogation  |EtoileBlanche       |Tirelangue          |EtoileNoir          |Ohm                 |

**Arduino NANO** 
*	0	RX
*	1	TX
*	2	Led RGB
*	3	bouton 1
*	4	bouton 2
*	5	bouton 3
*	6	bouton 4
*	7	
*	8	
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


# 5 : Qui est le premier ?
**Obligatoire** :
* Led RGB avec support

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
* [potentiometre](https://fr.aliexpress.com/item/4000288962865.html?spm=a2g0o.productlist.main.77.6d5914f4v5NPLG&algo_pvid=d71fb403-f40d-4cc7-a875-13c06d929c08&algo_exp_id=d71fb403-f40d-4cc7-a875-13c06d929c08-38&pdp_npi=4%40dis%21EUR%211.01%210.86%21%21%211.07%21%21%40211b88f116927819246263528e020d%2110000001196337664%21sea%21FR%210%21A&curPageLogUid=roWasiHeoYNX)
* 1 bouton

**Information à recevoir** :
* NAN

**Arduino NANO** 
*	0	RX
*	1	TX
*	2	Led RGB
*	3	bouton
*	4	
*	5	
*	6	
*	7	
*	8	
*	9	
*	10	
*	11	
*	12	
*	13	
*	A0	potentiometre
*	A1	
*	A2	
*	A3	
*	A4	SDA
*	A5	SCL
*	A6	
*	A7	

# 7 : Fils compliqués

**Obligatoire** :
* Led RGB avec support

* 6 led etoiles
* 6 led blanches
* 6 prises hautes
* 6 prises basses

**Information à recevoir** :
* NAN

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

# 8 : Labyrinthe

**Obligatoire** :
* Led RGB avec support

* carré de 6x6 led RGB (ou 8x8)
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

# 9 : Mot de passe

**Obligatoire** :
* Led RGB avec support

* Ecran SSD1306
* [https://passionelectronique.fr/ecran-oled-i2c-arduino/]

* sinon ecran ST7920 - 128x64 px
* [https://arduino-tutorials.net/tutorial/control-graphic-lcd-display-spi-st7920-128x64-with-arduino]

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
* [PS/2]
* [RJ-45](https://fr.aliexpress.com/item/1005003440343072.html?spm=a2g0o.productlist.main.57.5f5a326djM69zN&algo_pvid=6ce36167-250c-4633-beec-b0db1c915bbc&algo_exp_id=6ce36167-250c-4633-beec-b0db1c915bbc-28&pdp_npi=4%40dis%21EUR%218.89%212.22%21%21%219.47%21%21%40211b88ee16927161674517196e048a%2112000025804507239%21sea%21FR%210%21A&curPageLogUid=N1tBONFJKh4e)
* [Serie](https://fr.aliexpress.com/item/4000047329316.html?spm=a2g0o.detail.1000014.4.797d6d9eOBjBeH&gps-id=pcDetailBottomMoreOtherSeller&scm=1007.40050.281175.0&scm_id=1007.40050.281175.0&scm-url=1007.40050.281175.0&pvid=9a03efd2-6013-4c83-98a1-f2d37e822c91&_t=gps-id:pcDetailBottomMoreOtherSeller,scm-url:1007.40050.281175.0,pvid:9a03efd2-6013-4c83-98a1-f2d37e822c91,tpp_buckets:668%232846%238114%231999&isseo=y&pdp_npi=4%40dis%21EUR%211.71%211.44%21%21%211.82%21%21%40211b61bb16927154830814419e390e%2110000000107114516%21rec%21FR%21%21A)
* [Stéréo]
* [usb A](https://fr.aliexpress.com/item/1005004627694781.html?spm=a2g0o.detail.1000014.19.4ba935077YEAB2&gps-id=pcDetailBottomMoreOtherSeller&scm=1007.40050.281175.0&scm_id=1007.40050.281175.0&scm-url=1007.40050.281175.0&pvid=ee3f6211-8b18-4ab0-ab10-822e0e92f7ec&_t=gps-id:pcDetailBottomMoreOtherSeller,scm-url:1007.40050.281175.0,pvid:ee3f6211-8b18-4ab0-ab10-822e0e92f7ec,tpp_buckets:668%232846%238114%231999&isseo=y&pdp_npi=4%40dis%21EUR%210.46%210.44%21%21%210.49%21%21%40211b446016927163931054313ef1a7%2112000029890523502%21rec%21FR%21%21A)
