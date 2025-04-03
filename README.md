# Projet de Jeu Mastermind

## Aperçu

Ce projet est une implémentation du jeu classique **Mastermind** en C++. Le jeu consiste pour un joueur à deviner une combinaison secrète de couleurs choisie par l'ordinateur. L'ordinateur fournit des indices sur les tentatives du joueur, et ce dernier utilise ces indices pour affiner ses suppositions jusqu'à trouver la bonne combinaison ou épuiser ses essais.

Le projet est structuré en plusieurs composants, incluant la logique du jeu, les structures de données et les tests unitaires.

---

## Structure du Projet

### 1. **Launcher**
- **Objectif** : Point d'entrée de l'application.
- **Fichier clé** : `Launcher.cpp`
- **Description** : Initialise le jeu en invoquant la classe `ConsoleMenu` pour démarrer la boucle du jeu.

### 2. **Code**
- **Objectif** : Contient la logique principale du jeu.
- **Fichiers clés** :
  - `Mastermind.cpp` / `Mastermind.h` : Implémente la logique du jeu, y compris la génération des combinaisons et la validation des tentatives.
  - `Combination.cpp` / `Combination.h` : Représente une combinaison de couleurs.
  - `Color.cpp` / `Color.h` : Représente les couleurs individuelles et leurs opérations.
  - `ConsoleMenu.cpp` / `ConsoleMenu.h` : Gère l'interface utilisateur et le déroulement du jeu.
  - `constants.h` : Définit les constantes utilisées dans tout le jeu.
  - `EmptyListException.cpp` / `EmptyListException.h` : Exception personnalisée pour gérer les scénarios de liste vide.
  - `ConsoleColor.h` : Fournit des utilitaires pour la sortie colorée dans la console.

### 3. **Structs**
- **Objectif** : Implémente des structures de données personnalisées utilisées dans le jeu.
- **Fichiers clés** :
  - `Node.h` : Représente un nœud dans une liste chaînée.
  - `LinkedList.h` : Implémente une structure de liste chaînée.
  - `Iterator.h` : Fournit un itérateur pour parcourir la liste chaînée.
  - `DataStructure.h` : Classe de base pour les structures de données.

### 4. **TestsCode**
- **Objectif** : Contient des tests unitaires pour valider les fonctionnalités du jeu et des structures de données.
- **Fichiers clés** :
  - `Book.cpp` / `Book.h` : Une classe exemple utilisée pour les tests.
  - `iterator.cpp` : Tests pour la classe `Iterator`.
  - `liste.cpp` : Placeholder pour les tests de la liste chaînée.
  - `mastermind.cpp` : Placeholder pour les tests du jeu Mastermind.

---

## Comment Exécuter

1. **Prérequis** :
   - Visual Studio 2015 ou version ultérieure.
   - Système d'exploitation Windows.

2. **Étapes** :
   - Ouvrez le fichier solution `Mastermind.sln` dans Visual Studio.
   - Compilez la solution pour construire tous les projets.
   - Définissez `Launcher` comme projet de démarrage.
   - Exécutez le projet pour démarrer le jeu.

---

## Instructions de Jeu

1. **Objectif** :
   - Devinez la combinaison secrète de 4 couleurs choisie par l'ordinateur.

2. **Étapes** :
   - Entrez une séquence de 4 couleurs en utilisant leurs numéros correspondants.
   - L'ordinateur fournira des indices :
     - **1** : Bonne couleur à la bonne position.
     - **2** : Bonne couleur à la mauvaise position.
     - **3** : Mauvaise couleur.
   - Utilisez les indices pour affiner vos suppositions.
   - Le jeu se termine lorsque vous trouvez la bonne combinaison ou que vous épuisez le nombre maximum d'essais.

---

## Fonctionnalités

- **Structures de Données Personnalisées** :
  - Implémente une liste chaînée et un itérateur pour gérer les combinaisons.
- **Sortie Colorée dans la Console** :
  - Utilise `ConsoleColor.h` pour une meilleure expérience utilisateur.
- **Tests Unitaires** :
  - Valide les fonctionnalités des composants principaux à l'aide de Microsoft CppUnitTest.

---

## Améliorations Futures

- Ajouter davantage de tests unitaires pour une couverture complète.
- Améliorer l'interface utilisateur pour une meilleure interactivité.
- Implémenter des modes de jeu ou niveaux de difficulté supplémentaires.

---

## Crédits

- **Auteur** : Don Nick Munezero
- **Licence** : Ce projet est open-source et peut être modifié ou distribué librement.

---
