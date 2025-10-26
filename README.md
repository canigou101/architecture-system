Manipulation de tables de base de données simples

Auteurs : Elias Khnissi Gabin Gaucher--Boissier

description:

     Ce projet est développé entièrement en langage C, il a pour objectif la gestion de bases de données basiques, où les tables sont des archives, et les données sont stockées dans un fichier texte nommé data. La correspondance du type et du numéro de colonne est sauvegardée dans un autre fichier texte nommé meta.

Commandes disponibles :
    
    createTable.exe <Nom_De_Table> | elle permet de créer une table avec le nom passé en paramètre.
    
    supprimerTable.exe <Nom_De_Table> | elle permet de supprimer une table ainsi que tous ses fichiers sous-jacents.
     
    préparerTable.exe <Nom_De_Table> | elle permet de créer le fichier meta d'une table. Cette commande demande aussi le nombre de colonnes à l'utilisateur et fait remplir les types et noms de ces colonnes.
     
    réinitialiserTable.exe <Nom_De_Table> | elle permet de supprimer les fichiers data et meta d'une table /!\ Cette commande utilise la commande supprimerTable.exe, donc elle supprime tous les fichiers de la table, avant de la recréer.
 
       inserer_table.exe <Nom_De_Table> | elle remplit le fichier data d'une table donnée en paramètre. La commande est sensible au type énoncé dans le fichier meta.
      listerTable.exe <Nom_De_Table> | elle affiche toutes les lignes d'un fichier data en y précisant son type.


Technologies employées :
       langage C
       Makefile


Bibliothèques employées :
        stdlib.h
        stdio.h
        unistd.h
        sys/wait.h
        sys/stat.h


Mode d'emploi :

    necessaires:
        terminal Cygwin
        commande Make
        commande GCC


    Compilation :
                 entrer make <Le_Nom_De_La_Commande>
                 exemple:
                 make creerTable.exe
    Compiler toutes les commandes en une seule fois :
      make all        
    
    exécution d'une commande :

        Dans le terminal, entrer :

             ./<Nom_De_La_Commande> <Paramètre_De_La_Commande>
                     exemple :
                 ./creerTable.exe TableTest


    Nettoyage de l'archive :

             clean : 
                supprime uniquement les fichiers .o

             cleanEXE : 
                supprime les fichiers .exe

            cleanALL :
                supprime tous les fichiers .o et .exe
