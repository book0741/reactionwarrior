#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <iomanip>
using namespace std;

string generateTarget(int maxColumn, int maxRow) {
    char column = 'a' + rand() % maxColumn;
    int row = 1 + rand() % maxRow;

    return string(1, column) + to_string(row);
}

string getRating(int score, int rounds, double averageTime) {
    if (score == rounds && averageTime < 1.0) {
        return "Unreal";
    }
    else if (score >= rounds * 0.8 && averageTime < 1.5) {
        return "Champion";
    }
    else if (score >= rounds * 0.6 && averageTime < 2.0) {
        return "Diamond";
    }
    else if (score >= rounds * 0.4 && averageTime < 2.5) {
        return "Silver";
    }
    else {
        return "Bronze";
    }
}

int main() {
    srand(time(0));

    int choice;
    int maxColumn;
    int maxRow;
    int rounds;

    cout << "===== Aim Trainer =====\n";
    cout << "Choose YOUR difficulty of choice:\n";
    cout << "1. Easy: a-e, 1-5, 5 rounds\n";
    cout << "2. Medium: a-h, 1-8, 7 rounds\n";
    cout << "3. Hard: a-j, 1-10, 10 rounds\n";
    cout << "Choice: ";
    cin >> choice;

    if (choice == 1) {
        maxColumn = 5;
        maxRow = 5;
        rounds = 5;
    }
    else if (choice == 2) {
        maxColumn = 8;
        maxRow = 8;
        rounds = 7;
    }
    else {
        maxColumn = 10;
        maxRow = 10;
        rounds = 10;
    }

    int score = 0;
    double totalTime = 0;

    cout << "\nType the target as fast as possible.\n";

    for (int i = 1; i <= rounds; i++) {
        string target = generateTarget(maxColumn, maxRow);
        string answer;

        cout << "Round " << i << endl;
        cout << "Target: " << target << endl;
        cout << "Enter target: ";

        auto start = chrono::high_resolution_clock::now();

        cin >> answer;

        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double> reactionTime = end - start;
        totalTime += reactionTime.count();

        if (answer == target) {
            score++;
            cout << "Correct! ";
        }
        else {
            cout << "Wrong! ";
        }

        cout << "Reaction time: " << fixed << setprecision(2) << reactionTime.count() << " seconds\n";
    }

    cout << "===== Results =====\n";
    cout << "Score: " << score << "/" << rounds << endl;
    cout << "Average reaction time: " << fixed << setprecision(2) << totalTime / rounds << " seconds" << endl;
    cout << "Rating: " << getRating(score, rounds, totalTime / rounds) << endl;
    return 0;
}