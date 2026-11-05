//  Fitness Tracker System
//  Topics: Arrays, Enum, Struct, Functions, File Handling,
//          Pointers / References
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
using namespace std;
//  CONSTANTS  maximum sizes for fixed arrays
const int MAX_USERS = 10;
const int MAX_ACTIVITIES = 100;
const int MAX_STR = 50;
const char DATA_FILE[] = "fitness_data.txt";
//  ENUMS
// activity type
enum ActivityType {
    RUNNING = 1,
    WALKING = 2,
    CYCLING = 3,
    WORKOUT = 4
};
// intensity level
enum Intensity {
    LOW = 1,
    MEDIUM = 2,
    HIGH = 3
};
//  STRUCTS
//user's fitness targets
struct FitnessGoal {
    double targetWeight;
    double targetDistance;
    double targetDuration;
    char   description[MAX_STR];
};

// stores one logged workout session
struct Activity {
    ActivityType type;
    Intensity    intensity;
    double       duration;
    double       distance;
    double       caloriesBurned;
    char         date[MAX_STR];
};

// stores everything about one user
struct UserProfile {
    char        name[MAX_STR];
    int         age;
    double      weight;
    double      height;
    FitnessGoal goal;
    Activity    activities[MAX_ACTIVITIES];
    int         activityCount;
};
// 1)HELPER FUNCTIONS ...... convert enum to readable text
string activityName(ActivityType t) {
    switch (t) {
    case RUNNING: 
        return "Running";
    case WALKING: 
        return "Walking";
    case CYCLING: 
        return "Cycling";
    case WORKOUT: 
        return "Workout";
    default:      
        
        return "Unknown";
    }
}

string intensityName(Intensity i) {
    switch (i) {
    case LOW:    
        return "Low";
    case MEDIUM: 
        return "Medium";
    case HIGH:   
        return "High";
    default:    
        return "Unknown";
    }
}
//  UTILITY FUNCTIONSزز.... stop screen
void pressEnter() {
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

void printHeader(const char title[]) {
    cout << "========================================" << endl;
    cout << "  " << title << endl;
    cout << "========================================" << endl;
}
double calcBMI(double weight, double height) {
    double heightM = height / 100.0;
    return weight / (heightM * heightM);
}

const char* bmiCategory(double bmi) {
    if (bmi < 18.5) return "Underweight";
    if (bmi < 25.0) return "Normal weight";
    if (bmi < 30.0) return "Overweight";
    return "Obese";
}

// estimate calories using MET formula:
//   calories = MET * weight(kg) * duration(hours)
double estimateCalories(ActivityType type, Intensity intensity,
    double duration, double weight) {
    double met = 1.0;

    if (type == RUNNING) {
        if (intensity == LOW)         met = 7.0;
        else if (intensity == MEDIUM) met = 9.0;
        else                          met = 12.0;
    }
    else if (type == WALKING) {
        if (intensity == LOW)         met = 2.5;
        else if (intensity == MEDIUM) met = 3.5;
        else                          met = 4.5;
    }
    else if (type == CYCLING) {
        if (intensity == LOW)         met = 4.0;
        else if (intensity == MEDIUM) met = 6.0;
        else                          met = 10.0;
    }
    else { // WORKOUT
        if (intensity == LOW)         met = 3.5;
        else if (intensity == MEDIUM) met = 5.0;
        else                          met = 7.5;
    }

    return met * weight * (duration / 60.0);
}
//  FILE I/O

void saveToFile(UserProfile users[], int userCount) {
    ofstream file(DATA_FILE);
    if (!file) {
        cout << "Error: Could not open file for saving!" << endl;
        return;
    }

    file << userCount << endl;

    for (int i = 0; i < userCount; i++) {
        file << users[i].name << endl;
        file << users[i].age << endl;
        file << users[i].weight << endl;
        file << users[i].height << endl;
        file << users[i].goal.targetWeight << endl;
        file << users[i].goal.targetDistance << endl;
        file << users[i].goal.targetDuration << endl;
        file << users[i].goal.description << endl;
        file << users[i].activityCount << endl;

        for (int j = 0; j < users[i].activityCount; j++) {
            Activity& a = users[i].activities[j];
            file << (int)a.type << endl;
            file << (int)a.intensity << endl;
            file << a.duration << endl;
            file << a.distance << endl;
            file << a.caloriesBurned << endl;
            file << a.date << endl;
        }
    }

    file.close();
    cout << "Data saved to '" << DATA_FILE << "' successfully!" << endl;
}

// userCount passed by reference - caller gets updated count
void loadFromFile(UserProfile users[], int& userCount) {
    ifstream file(DATA_FILE);
    if (!file) {
        cout << "No saved data found. Starting fresh." << endl;
        userCount = 0;
        return;
    }

    file >> userCount;
    file.ignore();

    for (int i = 0; i < userCount; i++) {
        file.getline(users[i].name, MAX_STR);
        file >> users[i].age >> users[i].weight >> users[i].height;
        file.ignore();
        file >> users[i].goal.targetWeight
            >> users[i].goal.targetDistance
            >> users[i].goal.targetDuration;
        file.ignore();
        file.getline(users[i].goal.description, MAX_STR);
        file >> users[i].activityCount;
        file.ignore();

        for (int j = 0; j < users[i].activityCount; j++) {
            int t, inten;
            file >> t >> inten;
            users[i].activities[j].type = (ActivityType)t;
            users[i].activities[j].intensity = (Intensity)inten;
            file >> users[i].activities[j].duration
                >> users[i].activities[j].distance
                >> users[i].activities[j].caloriesBurned;
            file.ignore();
            file.getline(users[i].activities[j].date, MAX_STR);
        }
    }

    file.close();
    cout << "Data loaded from '" << DATA_FILE << "' successfully!" << endl;
}
//  USER MANAGEMENT FUNCTIONS
// user passed by reference (fills the struct in place)
void createUser(UserProfile& user) {

    printHeader("CREATE NEW USER");

    cout << "Enter name   :  ";
    cin.ignore();
    cin.getline(user.name, MAX_STR);

    cout << "Enter age    :  ";
    cin >> user.age;

    cout << "Enter weight (kg):  ";
    cin >> user.weight;

    cout << "Enter height (cm):  ";
    cin >> user.height;

    cout << "\n--- Set Fitness Goals ---\n";
    cout << "Target weight (kg)         : ";
    cin >> user.goal.targetWeight;

    cout << "Target distance/week (km)  :  ";
    cin >> user.goal.targetDistance;

    cout << "Target duration/week (min) :  ";
    cin >> user.goal.targetDuration;

    cout << "Goal description           :  ";
    cin.ignore();
    cin.getline(user.goal.description, MAX_STR);

    user.activityCount = 0;   // start with empty activity list

    cout << "\nUser profile created!\n";
}

// user passed by reference( updated)
void updateGoals(UserProfile& user) {
    printHeader("UPDATE FITNESS GOALS");

    cout << "Current goals:\n";
    cout << "  Target Weight   : " << user.goal.targetWeight << " kg\n";
    cout << "  Target Distance : " << user.goal.targetDistance << " km/week\n";
    cout << "  Target Duration : " << user.goal.targetDuration << " min/week\n";
    cout << "  Description     : " << user.goal.description << "\n\n";

    double val;
    cout << "New target weight   (0 = keep): ";
    cin >> val;
    if (val != 0) user.goal.targetWeight = val;

    cout << "New target distance (0 = keep): ";
    cin >> val;
    if (val != 0) user.goal.targetDistance = val;

    cout << "New target duration (0 = keep): ";
    cin >> val;
    if (val != 0) user.goal.targetDuration = val;

    char tmp[MAX_STR];
    cout << "New description (Enter to keep): ";
    cin.ignore();
    cin.getline(tmp, MAX_STR);
    if (tmp[0] != '\0')
        strncpy(user.goal.description, tmp, MAX_STR);

    cout << "Goals updated!\n";
}

// Activity FUNCTION

void logActivity(UserProfile &user) {
    if (user.activityCount >= MAX_ACTIVITIES) {
        cout << "Error: Activity log is full!" << endl;
        return;
    }
    printHeader("log New Activity");
    Activity *newAct = &user.activities[user.activityCount];

    int choice;
    cout << "Select Activity Type:\n";
    cout << "  1. Running\n";
    cout << "  2. Walking\n";
    cout << "  3. Cycling\n";
    cout << "  4. Workout\n";
    cout << "Choose (1-4): ";
    cin >> choice;
    switch (choice) {
    case 1: newAct->type = RUNNING;
        break;
    case 2: newAct->type = WALKING;
        break;
    case 3: newAct->type = CYCLING;
        break;
    case 4: newAct->type = WORKOUT;
        break;
    default:
        cout << "Invalid choice!\n";
        return;
    }

    // enter the intensity

    int intensChoice;
    cout << "Select Intensity: " << endl;
    cout << "  1. Low\n";
    cout << "  2. Medium\n";
    cout << "  3. High\n";
    cout << "Choose (1-3): ";
    cin >> intensChoice;
    if (intensChoice < 1 || intensChoice > 3) {
        cout << "Invalid intensity! Defaulting to Medium.\n";
        intensChoice = 2;
    }
    newAct->intensity = (Intensity)intensChoice;
    // enter the distance and date and duration

    cout << "Enter Duration (minutes): ";
    cin >> newAct->duration;
    if (newAct->type != WORKOUT) {
        cout << "Enter Distance (km): ";
        cin >> newAct->distance;
    }
    else {
        newAct->distance = 0;
    }
    cout << "Enter Date (DD/MM/YYYY): ";
    cin.ignore();
    cin.getline(newAct->date, MAX_STR);

    // print the estimateCalories

    newAct->caloriesBurned = estimateCalories(newAct->type, newAct->intensity, newAct->duration, user.weight);

    // to increase the user activities

    user.activityCount++;
    cout << fixed << setprecision(1);
    cout << "Activity logged successfully!" << endl;
    cout << "Calories Burned: " << newAct->caloriesBurned << " kcal\n";
}

// display FUNCTION

void displayUserProfile(const UserProfile& user) {
    printHeader("User Progress Report");
    double bmi = calcBMI(user.weight, user.height);
    cout << fixed << setprecision(1);
    cout << "  Name    : " << user.name << endl;
    cout << "  Age     : " << user.age << " years\n";
    cout << "  Weight  : " << user.weight << " kg\n";
    cout << "  Height  : " << user.height << " cm\n";
    cout << fixed << setprecision(2);
    cout << "  BMI  :  " << bmi << " (" << bmiCategory(bmi) << " )" << endl;

    cout << "-------- Fitness Goals --------" << endl;
    cout << "  Target Weight   : " << user.goal.targetWeight << " kg\n";
    cout << "  Target Distance : " << user.goal.targetDistance << " km/week\n";
    cout << "  Target Duration : " << user.goal.targetDuration << " min/week\n";
    cout << "  Description     : " << user.goal.description << endl;


    cout << "---------- Activity Log ----------" << endl;

    if (user.activityCount == 0) {
        cout << "  No activities logged yet." << endl;
        pressEnter();
        return;
    }
    cout << left
        << setw(15) << "Date"
        << setw(12) << "Type"
        << setw(12) << "Duration"
        << setw(12) << "Distance"
        << setw(12) << "Calories"
        << setw(10) << "Intensity"
        << endl;
    cout << "-----------------------------------------------------------------------" << endl;

    double totalCalories = 0;

    for (int i = 0; i < user.activityCount; i++) {
        cout << fixed << setprecision(1);
        cout << left
            << setw(15) << user.activities[i].date
            << setw(12) << activityName(user.activities[i].type)
            << setw(12) << user.activities[i].duration
            << setw(12) << user.activities[i].distance
            << setw(12) << user.activities[i].caloriesBurned
            << setw(10) << intensityName(user.activities[i].intensity)
            << endl;
        totalCalories += user.activities[i].caloriesBurned;
    }

    cout << "-----------------------------------------------------------------------" << endl;
    cout << "Total Calories Burned: " << totalCalories << " kcal" << endl;

    pressEnter();
}

// Progress report with goal completion percentages
void displayProgress(const UserProfile& user) {
    printHeader("PROGRESS REPORT");

    double totalDuration = 0;
    double totalDistance = 0;
    double totalCalories = 0;

    for (int i = 0; i < user.activityCount; i++) {
        totalDuration += user.activities[i].duration;
        totalDistance += user.activities[i].distance;
        totalCalories += user.activities[i].caloriesBurned;
    }

    cout << fixed << setprecision(1);
    cout << " Total Activities : " << user.activityCount << endl;
    cout << " Total Duration   : " << totalDuration << " minutes\n";
    cout << "  Total Distance   : " << totalDistance << " km\n";
    cout << "  Total Calories   : " << totalCalories << " kcal\n";

    cout << "--- Goal Progress ---" << endl;

    if (user.goal.targetDuration > 0) {
        double pct = (totalDuration / user.goal.targetDuration) * 100.0;
        if (pct > 100.0)
            pct = 100.0;

        cout << "  Duration Goal : " << pct << "%" << endl;
    }
    if (user.goal.targetDistance > 0) {
        double pct = (totalDistance / user.goal.targetDistance) * 100.0;
        if (pct > 100.0)
            pct = 100.0;
        cout << "  Distance Goal : " << pct << "%" << endl;
    }
    if (user.goal.targetWeight > 0) {
        double diff = user.weight - user.goal.targetWeight;
        if (diff > 0)
            cout << "  Weight to lose: " << diff << " kg\n";
        else if (diff < 0)
            cout << "  Weight to gain: " << -diff << " kg\n";
        else
            cout << "  Weight goal ACHIEVED!" << endl;
    }

    pressEnter();
}
//MENU
int selectUser(UserProfile users[], int userCount) {
    if (userCount == 0) {
        cout << "No users found. Please create one first." << endl;
        return -1;
    }
    cout << "Select a user: " << endl;
    for (int i = 0; i < userCount; i++)
        cout << "  " << (i + 1) << ". " << users[i].name << endl;
    cout << "Choice: ";
    int choice;
    cin >> choice;
    if (choice < 1 || choice>userCount) {
        cout << "Invalid choice!" << endl;
        return -1;
    }
    return choice - 1;
}

// Sub-menu for one selected user
void userMenu(UserProfile& user) {
    int choice;
    do {
        printHeader(user.name);
        cout << "  1. View Profile & Activity Log" << endl;
        cout << "  2. Update Goals" << endl;
        cout << "  3. Log New Activity" << endl;
        cout << "  4. View Progress Report" << endl;
        cout << "  0. Back to Main Menu" << endl;
        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice) {
        case 1: displayUserProfile(user);
            break;
        case 2: updateGoals(user);  pressEnter();
            break;
        case 3: logActivity(user);  pressEnter();
            break;
        case 4: displayProgress(user);
            break;
        case 0: break;
        default: cout << "Invalid choice!" << endl; break;
        }
    } while (choice != 0);
}
UserProfile Users[MAX_USERS];
int UserCount = 0;
int main() {
   

    cout << "======================================================" << endl;
    cout << "                FITNESS TRACKER SYSTEM               " << endl;
    cout << "=======================================================" << endl;
    loadFromFile(Users, UserCount);
    pressEnter();

    int choice=0;
    do {
        printHeader("MAIN MENU");
        cout << "  1. Select User" << endl;
        cout << "  2. Create New Profile" << endl;
        cout << "  3. List All Users\n";
        cout << "  4. Save Data\n";
        cout << "  5. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;

    
        switch (choice) {
        case 1: {
            int idx = selectUser(Users, UserCount);
            if (idx >= 0) userMenu(Users[idx]);
            break;
        }
        case 2: {
            if (UserCount >= MAX_USERS) {
                cout << "Maximum number of users reached (" << MAX_USERS << ")!" << endl;
            }
            else {
                createUser(Users[UserCount]);
                UserCount++;
            }
            pressEnter();
            break;
        }
        case 3: {
            printHeader("ALL USERS");
            if (UserCount == 0) {
                cout << "No users found.\n";
            }
            else {
                for (int i = 0; i < UserCount; i++) {
                    cout << "  " << (i + 1) << ". "
                        << Users[i].name
                        << "|Age: " << Users[i].age
                        << " | Weight: " << Users[i].weight << " kg"
                        << " |Activities: " << Users[i].activityCount << endl;
                }
            }
            pressEnter();
            break;
        }
        case 4:
            saveToFile(Users, UserCount);
            pressEnter();
            break;
        case 5:

            saveToFile(Users, UserCount);
            cout << "Goodbye! Stay fit!" << endl;
            break;
        default:
            cout << "Invalid choice!\n";
            break;
        }

    } while (choice != 5);

    return 0;
}