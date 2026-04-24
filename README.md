# Simulateur N-corps

Un simulateur gravitationnel à N corps écrit en C++ avec SDL2. Chaque corps exerce une attraction gravitationnelle sur tous les autres, et la simulation gère également les collisions par fusion.

## Aperçu

Le programme simule un ensemble de corps soumis à la gravité newtonienne dans un espace 2D. Les corps se déplacent, s'attirent mutuellement, entrent en collision et fusionnent en conservant la masse et la quantité de mouvement. L'intégration numérique utilise la **méthode de Verlet (velocity Verlet)**, plus stable que la méthode d'Euler pour les systèmes orbitaux.

## Fonctionnalités

- Calcul du champ gravitationnel pour N corps (O(N²) par pas de temps)
- Intégration numérique par la méthode de Verlet (vitesse)
- Fusion inélastique des corps lors d'une collision (conservation de la masse et de la quantité de mouvement)
- Rebonds amortis sur les bords de la fenêtre (perte d'énergie au choc)
- Coloration des corps en fonction de leur masse (dégradé bleu → rouge)
- Historique des positions pour tracer les trajectoires
- Deux scénarios d'initialisation : aléatoire pur, ou imitation d'un système solaire

## Dépendances

- Un compilateur C++ supportant C++17 (g++, clang, MSVC…)
- [SDL2](https://www.libsdl.org/) (développement)

### Installation de SDL2

**Debian / Ubuntu**
```bash
sudo apt install libsdl2-dev
```

**macOS (Homebrew)**
```bash
brew install sdl2
```

**Windows**
Télécharger les binaires de développement depuis le site officiel de SDL2 et configurer le projet (VS / MinGW) pour pointer vers les dossiers `include` et `lib`.

## Compilation

### Avec g++ (Linux / macOS / MinGW)
```bash
g++ -std=c++17 -O2 main.cpp corps.cpp maths.cpp affichage.cpp \
    -I. $(sdl2-config --cflags --libs) -o simulateur
```

Puis lancer :
```bash
./simulateur
```

### Avec Visual Studio
Ouvrir la solution et compiler normalement. Penser à ajouter `SDL2.dll` à côté de l'exécutable et à configurer les chemins include/lib de SDL2.

## Utilisation

Au lancement, une fenêtre SDL s'ouvre et la simulation démarre immédiatement.

| Touche / Action | Effet |
|-----------------|-------|
| `Q` | Quitter la simulation |
| Fermer la fenêtre | Quitter la simulation |

### Paramètres modifiables (dans `main.cpp`)

| Constante | Rôle | Valeur par défaut |
|-----------|------|-------------------|
| `LARGEUR` | Largeur de la fenêtre | 1920 |
| `HAUTEUR` | Hauteur de la fenêtre | 1080 |
| `NB_CORPS` | Nombre de corps au départ | 1000 |
| `GRAVITATIONAL_CONSTANT` | Intensité de la gravité | 500.0 |
| `dt` | Pas de temps de l'intégration | 0.0001 |

### Choisir le scénario

Dans `main.cpp`, deux blocs sont disponibles :

- **Scénario aléatoire** (activé par défaut) : N corps avec masse, rayon, position et vitesse tirés au hasard.
- **Imitation du système solaire** (commenté) : un Soleil central et quatre planètes en orbite. Pour l'activer, décommenter le bloc correspondant et commenter le bloc aléatoire.

## Architecture du code

```
.
├── main.cpp          # Point d'entrée : init SDL, boucle principale, rendu
├── vector.hpp        # Petite classe Vector 2D (x, y)
├── corps.hpp / .cpp  # Classes Corps et Tableau_de_Corps
├── maths.hpp / .cpp  # Opérations vectorielles + physique (Verlet, gravité, collision, fusion)
└── affichage.hpp / .cpp  # Rendu des corps (cercles pleins) et des trajectoires
```

### Les classes principales

- **`Vector`** — vecteur 2D minimaliste (position, vitesse, accélération).
- **`Corps`** — un corps physique : masse, rayon, position, vitesse, accélération, couleur, historique de positions.
- **`Tableau_de_Corps`** — conteneur tableau dynamique de `Corps*`, gère les fusions et le nettoyage mémoire.

### Boucle de simulation (par frame)

1. Gestion des événements SDL (quitter, etc.)
2. Détection des collisions et fusions des corps concernés
3. Mise à jour de chaque corps via Verlet (position → accélération → vitesse)
4. Effacement du rendu et dessin des corps (trajectoires optionnelles)
5. Présentation de la frame (VSync activé)

## Physique implémentée

### Méthode de Verlet (vitesse)

À chaque pas de temps `dt` :

```
x(t+dt) = x(t) + v(t)·dt + ½·a(t)·dt²
a(t+dt) = F(x(t+dt)) / m
v(t+dt) = v(t) + ½·(a(t) + a(t+dt))·dt
```

Cette méthode est d'ordre 2, symplectique dans sa formulation classique, et donne des orbites beaucoup plus stables qu'Euler explicite pour un coût identique.

### Gravitation

Pour chaque corps, l'accélération est la somme des contributions de tous les autres corps :

```
a_i = Σ G · m_j · (r_j - r_i) / |r_j - r_i|²
     j≠i
```

### Fusion

Lorsque deux corps se chevauchent (distance < somme des rayons), ils fusionnent en conservant la masse et la quantité de mouvement :

- `m = m₁ + m₂`
- `r = (m₁·r₁ + m₂·r₂) / m`
- `v = (m₁·v₁ + m₂·v₂) / m`
- Le rayon suit `r² = r₁² + r₂²` (conservation de l'aire, pas du volume — c'est une simulation 2D).

## Limitations connues

- **Complexité O(N²)** : au-delà de quelques milliers de corps, ça rame. Un Barnes-Hut / quadtree ferait passer à O(N log N).
- **Singularité à courte distance** : quand deux corps sont très proches sans avoir encore fusionné, `1/d²` explose. Le mécanisme de fusion limite en pratique l'impact, mais un *softening* `1/(d² + ε²)` serait plus propre.
- **Double boucle de fusion** : `for i, for j` parcourt chaque paire deux fois. Fonctionnel mais perfectible (il suffirait de démarrer `j` à `i+1`).
- **Pas de quadtree / spatial hashing** pour la détection de collisions.

## Auteur

Projet personnel — Yanis.
