// Infinite death loop after asking if they'd like to play again

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cctype>

using namespace std;

string desiredWord;           
int wrong;
string currentGuess;
string used;

bool match(char letter, string word);
char askGuess(string usedLettersString); 
bool done = false;

int main()
{
    srand(time(0));

    // The possible words to guess (Taken from a list of difficult Hangman words)
    vector<string> words; 
    words.push_back("ABYSS");
    words.push_back("GLOWWORM");
    words.push_back("OXYGEN");
    words.push_back("JAZZ");
    words.push_back("COBWEB");
    words.push_back("STAFF");
    words.push_back("ZIPPER");
    words.push_back("WHISKEY");
    words.push_back("PUZZLING");
    words.push_back("IVORY");
    words.push_back("HAIKU");
    
    cout << "LostRabbitDigital.com" << endl;

    while(1)
    {
        // Amount of guesses
        const int guesses = 8;  

        // Pick a random word to guess
        random_shuffle(words.begin(), words.end());
        desiredWord = words[0];           

        // Words guessed
        currentGuess = string(desiredWord.size(), '-');         
        used = "";                            

        // loop for current word
        while ((wrong < guesses) && (currentGuess != desiredWord))
        {
            cout << "\nGuess Left: " << (guesses - wrong) << "";
            cout << "\nLetters Used: " << used << endl;
            cout << "\nCurrent Word: " << currentGuess << endl;

            used += askGuess(used);
        } 

        if (wrong == guesses)
        {
            system("CLS");
            cout << "\nYou died.";
        }

        cout << "\nWord: " << desiredWord << endl;

    }
    return 0;
}

inline bool match(char letter, string word)
{
    return (word.find(letter) != string::npos);
}

char askGuess(string usedLettersString)
{
    char guess;
    cout << "\n\nEnter Guess: ";
    cin >> guess;
    guess = toupper(guess); 
    while (match(guess, used))
    {
        system("CLS");
        cout << "\nAlready Guessed: " << guess << endl;
        cout << "Enter Guess: ";
        cin >> guess;
        guess = toupper(guess);
    }


    if (match(guess, desiredWord))
    {
        system("CLS");
        cout << "Correct Guess: " << guess;

        // update currentGuess to include newly guessed letter
        for (int i = 0; i < desiredWord.length(); i++)
            if (desiredWord[i] == guess)
                currentGuess[i] = guess;
    }
    else
    {
        system("CLS");
        cout << "Incorrect Guess: " << guess;
        wrong++;
    }

    return guess;
}

bool playAgain() 
{
    char again;
    cout << "\n\nWould you like to play again? <y/n>: ";
    cin >> again;

    cin.clear(); 
    cin.ignore();

    again = toupper(again);

    system("cls");

    return (again == 'Y');
}