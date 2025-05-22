MY_SHELL - Shell personnalisé en C
Aperçu
MY_SHELL est un shell personnalisé en langage C, développé dans le cadre d’un travail de classe comptant comme examen. Inspiré par le tutoriel YouTube Let’s build a super simple shell in C, ce projet implémente un shell capable d’exécuter des commandes externes et des commandes intégrées, avec des fonctionnalités avancées telles que la redirection d’entrée/sortie et la gestion de l’historique des commandes. Le shell offre une interface utilisateur colorée avec une bannière ASCII et des messages d’erreur clairs.
Ce projet a été réalisé par Aya sur un système Ubuntu, testé sur un HP EliteBook 840 G5, et documenté dans un rapport au format Word (rapport_shell.docx).
Structure du projet
Le projet est organisé en quatre fichiers principaux pour une modularité optimale :

MY_SHELL.h : Définitions des structures (t_builtin pour les commandes intégrées, t_history pour l’historique), macros pour les couleurs (RED, G, etc.), et prototypes des fonctions.
MY_SHELL.c : Point d’entrée principal, gère la boucle de lecture/exécution, l’analyse des commandes, et l’historique.
builtin.c : Implémentation des commandes intégrées (ls, rm, pwd, etc.).
utils.c : Fonctions utilitaires pour la gestion de la mémoire (Malloc, Realloc), des processus (Fork, Execvp), et de l’affichage (printbanner).

Les captures d’écran sont stockées dans le dossier captures/ :

shell_session.png : Session complète dans myshell (commandes pwd, mkdir, touch, ls, redirection, rm, rmdir).
shell_session2.png : Contexte système dans bash (commandes mkdir, ls, cd, rmdir).
shell_error.png : Gestion des erreurs dans bash (commandes ls, rmdir, mkdir).

Prérequis

Système : Linux (testé sur Ubuntu).
Compilateur : GCC (gcc).
Dépendances : Bibliothèques standard C (stdio.h, stdlib.h, unistd.h, dirent.h, sys/types.h, sys/stat.h, ftw.h).

Installation et compilation

Cloner ou naviguer dans le répertoire :
cd ~/MY_SHELL


Compiler le shell :
gcc -o myshell MY_SHELL.c builtin.c utils.c

Cela génère l’exécutable myshell.

Exécuter le shell :
./myshell

Vous verrez une bannière ASCII et une invite personnalisée : 👾 /home/aya/MY_SHELL 👾$>.


Fonctionnalités

Commandes intégrées :
exit : Quitte le shell avec une animation.
env : Affiche les variables d’environnement.
cd : Change le répertoire courant.
history : Affiche jusqu’à 100 commandes précédentes.
mkdir : Crée un répertoire (permissions 0755).
rmdir : Supprime un répertoire vide.
ls : Liste les fichiers non cachés.
rm : Supprime des fichiers ou répertoires (option -r pour récursif).
pwd : Affiche le répertoire courant.


Redirection : Supporte > (sortie vers fichier) et < (entrée depuis fichier).
Historique : Stocke les commandes non vides dans une structure t_history.
Commandes externes : Exécute des programmes comme cat, touch, ou grep via fork et execvp.
Gestion des erreurs : Messages d’erreur en rouge pour une meilleure lisibilité.

Exemple d’utilisation
Exécutez ./myshell et essayez les commandes suivantes :
pwd
mkdir test_dir
touch test_dir/file.txt
ls test_dir
ls test_dir > output.txt
cat output.txt
rm test_dir/file.txt
rmdir test_dir

Consultez les captures d’écran dans captures/ pour des exemples visuels :

shell_session.png : Démonstration des fonctionnalités principales dans myshell.
shell_session2.png : Contexte système (bash), montrant des commandes similaires.
shell_error.png : Gestion des erreurs dans bash (similaire à myshell).

Supprimer les messages de débogage
Les captures d’écran actuelles (e.g., shell_session.png) incluent des messages [DEBUG] Getcwd appelée. Pour un affichage plus propre :

Modifiez utils.c :
code ~/MY_SHELL/utils.c

Remplacez la fonction Getcwd par :
void Getcwd(char *buf, size_t size)
{
    if (NULL == getcwd(buf, size))
        perror(RED "getcwd FAILED" RST);
}


Recompilez :
gcc -o myshell MY_SHELL.c builtin.c utils.c


Relancez ./myshell et vérifiez que les messages de débogage ont disparu.


Recréer les captures d’écran dans myshell
Les captures shell_session2.png et shell_error.png ont été prises dans bash, pas dans myshell. Pour des captures cohérentes :

Pour shell_session2.png :
./myshell
mkdir test2_dir
ls
cd test2_dir
cd ..
rmdir test2_dir
ls

Prenez une capture avec Shift + Print Screen ou :
scrot shell_session2.png


Pour shell_error.png :
./myshell
ls invalid_dir
rmdir non_empty_dir
rmdir test_dir
mkdir test_dir

Prenez une capture et sauvegardez-la comme shell_error.png.

Déplacez les captures :
mkdir -p ~/MY_SHELL/captures
mv shell_session2.png shell_error.png ~/MY_SHELL/captures/



Rapport du projet
Un rapport détaillé, rapport_shell.docx, est inclus dans le répertoire. Il décrit :

Les objectifs du projet.
La structure du code et les fonctionnalités.
Les défis rencontrés et leurs solutions.
Les résultats des tests avec captures d’écran.

Pour visualiser le rapport :

Ouvrez rapport_shell.docx dans Microsoft Word ou LibreOffice.
Les captures d’écran sont insérées dans la section « Tests et résultats ».

Problèmes connus

Messages de débogage : Les captures actuelles incluent [DEBUG] Getcwd appelée. Suivez les instructions ci-dessus pour les supprimer.
Captures dans bash : shell_session2.png et shell_error.png utilisent bash. Recréez-les dans myshell pour une cohérence optimale.
Commande touch : Dans shell_session.png, touch est exécuté comme une commande externe. Une version intégrée pourrait être ajoutée.

Améliorations futures

Support des pipes (|) pour chaîner les commandes.
Exécution en arrière-plan avec &.
Auto-complétion des commandes et chemins.
Options avancées pour ls (-l, -a) ou mkdir -p.

Auteur

Aya
Date : 22 mai 2025

Références

Tutoriel YouTube : Let’s build a super simple shell in C (lien non fourni).
Documentation C : man pages pour fork, execvp, mkdir, rmdir, nftw, opendir, readdir, dup2.
POSIX documentation pour les appels système.

