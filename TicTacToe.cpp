#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <sstream>


bool thereIsWinnerOrTie(std::vector<char> userInputs, char currPlayer) {
    const std::string winChoices = "012,345,678,246,048,036,147,258";
    int winChoiceLen = winChoices.size();

    std::stringstream ss;
    for (short i = 0, j = 0; i < winChoiceLen; i++,j++) {
        ss << winChoices[i];
        int wcIndex = std::stoi(ss.str());
        if (userInputs[wcIndex] != currPlayer) {
            i += (3-j);
            j = 0;
            j--;
        } else if(j == 2) {
            return true;
        }
        ss.str("");
    }
    return false;
}

void printBoard(std::vector<char> &userInputs) {
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
        do {
            if (std::regex_search(input, numbers)) { // Ensure user entered legitimate character
                counter++;
                short tmpInt = std::stoi(input) - 1;
                userInputs[tmpInt] = currentPlayer;
                if (thereIsWinnerOrTie(userInputs, currentPlayer)) {
                    printBoard(userInputs);
                    std::cout << "That's the end of the game!! Player " << currentPlayer << " wins!\n";
                    break;
                }
                (currentPlayer == 'X') ? (currentPlayer = 'O')
                    : (currentPlayer = 'X');
            }
            printBoard(userInputs);
            std::printf(sysOutput, currentPlayer);
        } while (std::cin >> input && counter < 9);
        std::cout << "Start over? (Y/N)\n";
        std::cin >> input;
    } while (input == "Y" || input == "y");
}
