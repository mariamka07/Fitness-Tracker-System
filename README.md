# 🏋️ Fitness Tracker System

A console-based Fitness Tracker System developed in C++ as part of the Problem Solving course. The application allows users to manage their fitness profiles, track workout activities, set fitness goals, and monitor their progress.

## 📌 Project Overview

The Fitness Tracker System helps users keep track of their physical activities and fitness goals. It supports multiple user profiles and automatically saves fitness data to a text file, allowing users to continue from their previous sessions.

## ✨ Features

- Create and manage personal fitness profiles.
- Record fitness activities such as Running, Walking, Cycling, and Workout.
- Choose activity intensity: Low, Medium, or High.
- Set and update fitness goals.
- Calculate Body Mass Index (BMI) and determine BMI categories.
- Estimate calories burned during activities.
- Display user profiles and activity history.
- Generate fitness progress reports.
- Calculate goal completion percentages.
- Automatically save and load user data using file handling.

## 🛠️ Technologies & Concepts

This project was developed using C++ and focuses on the fundamental concepts covered in the Problem Solving course.

- **Arrays:** Store user profiles and fitness activities.
- **Enums:** Define activity types and intensity levels.
- **Structs:** Organize fitness goals, activities, and user profiles.
- **Functions:** Divide the program into modular and reusable components.
- **Pointers:** Access activity records directly.
- **References:** Modify user profiles without unnecessary copying.
- **File Handling:** Save and load data using `ifstream` and `ofstream`.

## 🔥 Supported Activities

| Activity | Description |
|---|---|
| Running | Track running sessions and distance. |
| Walking | Record walking activities. |
| Cycling | Track cycling sessions. |
| Workout | Record general workout sessions. |

Each activity includes its duration, intensity, date, and estimated calories burned.

## 📊 Fitness Calculations

### Body Mass Index (BMI)

The system calculates BMI using the user's weight and height.

### Calories Burned

Calories burned are estimated using the MET (Metabolic Equivalent of Task) formula:

`Calories = MET × Weight (kg) × Duration (hours)`

The MET value depends on the activity type and intensity.

## 💾 Data Storage

The application uses file handling to store and retrieve user information.

- **Data File:** `fitness_data.txt`
- User profiles, fitness goals, and activity records are saved automatically.
- Existing data is loaded when the application starts.
- Data is saved when the application exits.

## 🚀 How to Run

1. Clone or download this repository.
2. Open `fitness_tracker.cpp` in Visual Studio.
3. Build and run the project using `Ctrl + F5`.
4. Follow the instructions displayed in the console.

The `fitness_data.txt` file is created automatically when the application saves data for the first time.

## 👥 Project Team

- **Mariam Mohamed Ali Mohamed El Kasaby** 
- **Jana Ibrahim** 
  

## 📚 Course Information

- **Course:** Problem Solving
- **Project Number:** 18
- **Programming Language:** C++

---

*Developed as a Problem Solving course project.*
