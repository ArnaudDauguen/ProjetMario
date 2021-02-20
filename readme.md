# Projet Plateformer 2D (mario like)

## Compilation du projet
* Récupérer les sources sur le repo
* Ouvrir le projet dans VisualStudio
* Compiler en "Static Release"

## Edition du niveau
Tous les fichiers de configuration graphique du jeu se trouvent dans la solution, dans le dossier "Textures".
Vous y trouverez
* un dossier **Backgrounds** dans lequel se trouvent toutes les couches de fond d'écran. Veuillez conserver le nombre de fichiers ainsi que leur intitulé (tout changement demandera des modifications dans le code).
* Une font
* **terrain.png**. Cette image est une grille de textures.
    * Une texture est définie sur une zone de 16x16 pixels (modifiable dans Game.h)
    * Par défaut, seul les 16 premières lignes et colonnes pourront être utilisées dans le jeu (modifiable dans Game.h).


Tous les fichiers d'édition de niveaux se trouvent dans la solution, dans un dossier "save".
Vous y trouverez
* **actors.json** qui définit les tous les acteurs du niveau avec un type, une position X et Y ainsi qu'un index de texture.
    * Le Player doit avoir pour type 0, un 1 définit un Goomba et un 2 un Thwomp.
    * l'index de texture est la position de la texture souhaitée dans terrain.png
* **blocks.json** qui définit tous les blocs utiliser dans le niveau
    * chaque index se doit d'être unique
    * veuillez choisir si un bloc peut être traversé et s'il est un bloc de victoire.
    * Si un bloc est défini pour la victoire et que le player entre en contact avec, le niveau sera terminé.
* **level.json** qui définit le niveau. Il faut renseigner la longueur, la hauteur du monde et un tableau d'id de blocs
