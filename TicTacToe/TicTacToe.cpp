#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <sstream>

bool isWinner(std::vector<char> userInputs, char currentPlayer) {
    std::string winPossibilities = "012,345,678,048,246,036,147,258";
    short len = winPossibilities.size();
    std::stringstream ss;
    for (int i = 0,j = 0; i < len; i++) {
        ss << winPossibilities[i];
        short index = std::stoi(ss.str());
        ss.str("");
        if (userInputs[index] != currentPlayer) {
            i += 3 - j; 
            j = 0;
            continue;
        }
        j++;
        if (j >= 3) {
            return true;
        }
        
    }
    return false;
}

void printBoard(std::vector<char> userInputs) {
    const char* line = " %c | %c | %c \n";
    const std::string underscores = "-----------\n";
    for (int i = 0, j = 0; i < 3; i++) {
        char slot1{ userInputs[j++] };
        char slot2{ userInputs[j++] };
        char slot3{ userInputs[j++] };
        std::printf(line, slot1, slot2, slot3);
        if (i < 2) {
            std::cout << underscores;
        }
    }
}

int main()
{
    std::vector<char> userInputs{ '1','2', '3', '4', '5', '6', '7', '8', '9' };
    char currentPlayer = 'X';
    std::string input = "";
    const char* sysOutput = "Player %c please enter your next move: ";
    std::regex numbers("[1-9]");
    int counter = 0;
    do {
        if (std::regex_search(input, numbers)) { // Ensure user entered legitimate character
            counter++;
            short tmpInt = std::stoi(input) - 1;
            userInputs[tmpInt] = currentPlayer;
            if (isWinner(userInputs, currentPlayer)) {
                printBoard(userInputs);
                std::cout << "Player " << currentPlayer << " is the winner!" << std::endl;
                break;
            }
            (currentPlayer == 'X') ? (currentPlayer = 'O')
                : (currentPlayer = 'X');
        }
        printBoard(userInputs);
        std::printf(sysOutput, currentPlayer);
    } while (std::cin >> input && counter < 9);
}