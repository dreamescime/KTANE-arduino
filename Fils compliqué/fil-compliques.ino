cont byte test[4] [4] = {
{0, 0, 2, 0}
{1, 3, 2, 2}
{3, 1, 2, 3}
{4, 4, 4, 1}};

for (int i = 0; i = 4; i++) {
  Led[i] = random(2);
  Etoile[i] = random(2);
}


for (int i = 0; i = 4; i++) {
  if (Led[i] == 0) {
    if (Bleu[i] == 0) ligne = 0;
    if (Bleu[i] == 1) ligne = 1;}
  if (Led[i] == 1) {
    if (Bleu[i] == 1) ligne = 2;
    if (Bleu[i] == 0) ligne = 3;}

  if (Etoile[i] == 1) {
    if (Rouge[i] == 0) colonne = 0;
    if (Rouge[i] == 1) colonne = 1;}
  if (Etoile[i] == 0) {
    if (Rouge[i] == 1) colonne = 2;
    if (Rouge[i] == 0) colonne = 3;}
  Fil_a_couper[i] = test[ligne][colonne];
}
