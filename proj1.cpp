// File name: proj1.cpp
/**

proj1.cpp

*Academic Integrity Statement: I certify that, while others may have assisted me in brain
storming, debugging and validating this program, the program itself is my own work. I understand
that submitting code which is the work of other individuals is a violation of the course Academic
Integrity Policy and may result in a zero credit for the assignment, or course failure and a report to
the Academic Dishonesty Board. I also understand that if I knowingly give my original work to
another individual that it could also result in a zero credit for the assignment, or course failure and
a report to the Academic Dishonesty Board. See Academic Integrity Procedural Guidelines
(http://behrend.psu.edu/intranet/faculty-resources/academic-integrity/academic-integrity-procedural
guidelines) at:
https://psbehrend.psu.edu/intranet/faculty-resources/academic-integrity/academic-integrity-procedural-guidelines (
http://behrend.psu.edu/intranet/faculty-resources/academic-integrity/academic-integrity-procedural-guidelines

Assisted by and Assisted line numbers: None

Author: Mitchell Readinger
PSU ID: 925010227
Course Title: CMPSC 465
Due Time: Sunday 9/7/2025 at 11:59 PM
Last modified: 9/6/2025
Description:

    This program reads input from a file named lab1in.txt, processes it to determine if a given
    permutation of train coaches can be achieved using a stack, and writes the results to a file
    named lab1out.txt. The input file contains multiple blocks of data, each starting with the
    number of coaches (n) followed by permutations of those coaches. The program stops processing
    when it encounters a block starting with 0.

    **/


#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
using namespace std;

bool canRearrange(int n, const vector<int>& targetOrder) {
    stack<int> station; // The station acts as a stack
    int nextFromA = 1;   // Next coach to come from track A (1, 2, 3, ...)
    int targetIndex = 0; // Index in the target order we're trying to match
    
    while (targetIndex < n) {
        int needed = targetOrder[targetIndex];
        
        // If we need a coach that's already in the station (top of stack)
        if (!station.empty() && station.top() == needed) {
            station.pop();
            targetIndex++;
        }
        // If we need a coach that hasn't come from track A yet
        else if (nextFromA <= needed) {
            // Push coaches from track A to station until we get the one we need
            while (nextFromA <= needed) {
                station.push(nextFromA);
                nextFromA++;
            }
            // Now pop the needed coach
            if (!station.empty() && station.top() == needed) {
                station.pop();
                targetIndex++;
            }
        }
        // If we need a coach with number < nextFromA, it must be in station
        // If it's not on top, we can't get it (can't reach coaches below)
        else {
            return false;
        }
    }
    
    return true;
}

int main() {
    ifstream input("lab1in.txt");
    ofstream output("lab1out.txt");
    
    if (!input.is_open()) {
        cerr << "Error: Cannot open input file lab1in.txt" << endl;
        return 1;
    }
    
    int n;
    bool firstBlock = true;
    
    while (input >> n && n != 0) {
        if (!firstBlock) {
            output << endl; // Empty line between blocks
        }
        firstBlock = false;
        
        vector<int> targetOrder(n);
        
        // Read permutations until we get 0
        while (true) {
            // Try to read first number of a potential permutation
            int first;
            input >> first;
            
            if (first == 0) {
                break; // End of this block
            }
            
            // Read the rest of the permutation
            targetOrder[0] = first;
            for (int i = 1; i < n; i++) {
                input >> targetOrder[i];
            }
            
            // Check if this permutation is possible
            if (canRearrange(n, targetOrder)) {
                output << "Yes" << endl;
            } else {
                output << "No" << endl;
            }
        }
    }
    
    input.close();
    output.close();

    // Console poutput
    cout << "Program completed successfully. Check ../lab1out.txt for results." << endl;
    return 0;
}