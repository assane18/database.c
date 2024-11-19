# class_db
A simple skeleton code in C for a database
                            Gestionnaire de Base de Données en C


	  Ce projet est un système de gestion de bases de données simplifié écrit en C.
	 Il permet de gérer une table en mémoire, de faire des insertions, des sélections,
		    et de sauvegarder ou charger des données depuis un fichier. 

					Fonctionnalités :
					-----------------

		  1. Insertion : Ajouter des enregistrements dans la table.
		  2. Sélection : Afficher tous les enregistrements de la table.
		  3. Sauvegarde : Enregistrer les données dans un fichier.
		  4. Chargement : Charger les données depuis un fichier.
		  5. Recherche : Recherche rapide par ID à l'aide d'un arbre binaire.
		  6. Interface REPL : Une interface en ligne de commande interactive.


					Fichiers du Projet :
					--------------------
		  - main.c       : Point d'entrée du programme, initialise et lance le REPL.
		  - repl.c       : Gère l'interface utilisateur et les commandes.
		  - table.c      : Implémente les fonctionnalités liées à la gestion de la table.
		  - btree.c      : Implémente un arbre binaire pour la recherche par ID.
		  - repl.h       : Header pour les fonctions liées au REPL.
		  - table.h      : Header pour les structures et fonctions liées à la table.
		  - btree.h      : Header pour les structures et fonctions liées à l'arbre binaire.
		  - Makefile     : Automatise la compilation et des tâches associées.


					   Les Commandes :
					   ---------------
		  - `.exit`        : Quitte le programme.
		  - `.save`        : Sauvegarde les données dans un fichier `donnees.txt`.
		  - `.load`        : Charge les données depuis un fichier `donnees.txt`.
		  - `insert`       : Insère un nouvel enregistrement. Exemple :
   		                    `insert 1 Nom Prenom 22`
		  - `select`       : Affiche tous les enregistrements de la table.
	

				       Compilation et Exécution :
				       --------------------------
		  1. Compilez le programme en tapant :
   			`make`

		  2. Lancez la bdd :
   			`./db`

		  3. Pour nettoyer les fichiers de compilation :
   			`make clean`

		  4. Pour exécuter avec Valgrind (détection des fuites mémoire) :
   			`make valgrind`


						Notes :
						-------
		  - Les données sont manipulées uniquement en mémoire à moins qu'elles ne soient sauvegardées avec `.save`.
		  - La structure binaire permet des recherches rapides par ID.


						Exemple :
						---------
       		  assane@debian:~/cc1/database.c/src$ make
		  `gcc -Wall -Wextra -std=c11 -g -c main.c -o main.o`
		  `gcc -Wall -Wextra -std=c11 -g -c repl.c -o repl.o`
		  `gcc -Wall -Wextra -std=c11 -g -c btree.c -o btree.o`
		  `gcc -Wall -Wextra -std=c11 -g -c table.c -o table.o`
		  `gcc -Wall -Wextra -std=c11 -g -o db main.o repl.o btree.o table.o`
 		  assane@debian:~/cc1/database.c/src$ ./db
 		  `Bienvenue dans le gestionnaire de base de données !
 		  db > insert 1 Assane Traore 22
		  `Insertion réussie : 1 Assane Traore 22`
  		  db > insert 2 Traore Assane 23
		  `Insertion réussie : 2 Traore Assane 23`
 		  db > select
		  `ID      Nom     Prenom  Age`
		  `1       Assane  Traore   22`
		  `2       Traore  Assane   23`
 		  db > .save
  		  `Données sauvegardées dans donnees.txt`
 		  db > .exit
  		  assane@debian:~/cc1/database.c/src$ ./db
  		  db > select
		  `ID	Nom	Prenom	Age	`
		  `double free or corruption (out)``
		  `Abandon`
  		  assane@debian:~/cc1/database.c/src$ ./db
  		  db >.load
  		  db > select
		  `ID      Nom     Prenom  Age`
		  `1       Assane  Traore   22`
		  `2       Traore  Assane   23`
  		  db >.exit
		  assane@debian:~/cc1/database.c/src$ ls
		  `btree.c  btree.o  donnees.txt  main.o    repl.c  repl.o   table.h`
		  `btree.h  db       main.c       Makefile  repl.h  table.c  table.o`
  		  assane@debian:~/cc1/database.c/src$ make clean
		  `rm -f main.o repl.o btree.o table.o db`
  		  assane@debian:~/cc1/database.c/src$ ls
		  `btree.c  btree.h  donnees.txt  main.c  Makefile  repl.c  repl.h` 
  		  `table.c  table.h`
  		  assane@debian:~/cc1/database.c/src$

