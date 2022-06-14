// Infinite death loop after asking if they'd like to play again
// Clear skin after each question to not clog up the console
// Finish commenting code
// Finish renaming variables

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
char askGuess(string usedLettersStr); 
bool done = false;

int main()
{
    srand(time(0));

    // The possible words to guess
    vector<string> words; 
    words.push_back("GUESS");
    words.push_back("HANGMAN");
    words.push_back("DIFFICULT");
    words.push_back("BOOK");
    words.push_back("DIGITAL");
    words.push_back("PROGRAM");

    cout << "HANGMAN";

    while(1)
    {
        // Amount of guesses
        const int guesses = 5;  

        // Pick a random word to guess
        random_shuffle(words.begin(), words.end());
        desiredWord = words[0];           

        // Words guessed
        currentGuess = string(desiredWord.size(), '-');         
        used = "";                            

        // loop for current word
        while ((wrong < guesses) && (currentGuess != desiredWord))
        {
            cout << "\n\nYou have " << (guesses - wrong) << " guesses left.\n";
            cout << "\nYou've used the following letters:\n" << used << endl;
            cout << "\nSo far, the word is:\n" << currentGuess << endl;

            used += askGuess(used);
        } 

        if (wrong == guesses)
        {
            cout << "\nYou've been hanged!";
        }

        cout << "\nThe word was " << desiredWord << endl;

    }

    return 0;
}

inline bool match(char letter, string word)
{
    return (word.find(letter) != string::npos);
}

char askGuess(string usedLettersStr)
{
    char guess;
    cout << "\n\nEnter your guess: ";
    cin >> guess;
    guess = toupper(guess); 
    while (match(guess, used))
    {
        cout << "\nYou've already guessed " << guess << endl;
        cout << "Enter your guess: ";
        cin >> guess;
        guess = toupper(guess);
    }


    if (match(guess, desiredWord))
    {
        cout << "That's right! " << guess << " is in the word.\n";

        // update currentGuess to include newly guessed letter
        for (int i = 0; i < desiredWord.length(); i++)
            if (desiredWord[i] == guess)
                currentGuess[i] = guess;
    }
    else
    {
        cout << "Sorry, " << guess << " isn't in the word.\n";
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