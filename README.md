# simplest_weather_app C++

Une application de bureau légère et performante permettant de consulter la météo en temps réel pour n'importe quelle ville dans le monde. Développée en C++ moderne avec une interface graphique basée sur Dear ImGui.

![Aperçu de l'application](screenshot.png)

## Fonctionnalités

* **Données en temps réel :** Récupération de la température, de la vitesse du vent et du code météo (ciel dégagé, nuageux, etc.).
* **Recherche de ville :** Système de géocodage intégré permettant de rechercher une ville par son nom (ex: "Paris", "New York").
* **Interface Graphique :** GUI fluide et réactive utilisant le paradigme "Immediate Mode" (ImGui).
* **Aucune clé API requise :** Utilise les endpoints publics d'Open-Meteo.
* **Multi-plateforme :** Compatible Windows, Linux et macOS (via CMake).

## Stack Technique

Le projet repose sur des bibliothèques open-source robustes et standards dans l'industrie :

* **Langage :** C++17
* **Interface (GUI) :** [Dear ImGui](https://github.com/ocornut/imgui) (avec backend GLFW & OpenGL 3)
* **Réseau :** [libcurl](https://curl.se/libcurl/)
* **Parsing JSON :** [nlohmann/json](https://github.com/nlohmann/json)
* **Système de Build :** CMake
* **Gestionnaire de paquets :** vcpkg

## Prérequis

Avant de compiler, assurez-vous d'avoir installé :

* Un compilateur C++ compatible C++17 (MSVC, GCC ou Clang).
* [CMake](https://cmake.org/) (version 3.20 ou supérieure).
* [vcpkg](https://github.com/microsoft/vcpkg) pour la gestion des dépendances.

## Installation et Compilation

Ce projet utilise **vcpkg** pour gérer les bibliothèques.

### 1. Cloner le dépôt

```bash
git clone [https://github.com/votre-nom-utilisateur/weather-app-cpp.git](https://github.com/votre-nom-utilisateur/weather-app-cpp.git)
cd weather-app-cpp
