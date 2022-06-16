/*
    License
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    MIT License

    Copyright (c) 2022, Boden McHale

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.

    Future Modifications
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    - Ascii art of a stick figure

    Author
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    Twitter: @Boden_McHale https://twitter.com/Boden_McHale
    Blog: https://lostrabbitdigital.com/blog/

    Last Updated: June 16th 2022
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdlib.h>

using namespace std;

int wrongGuesses;
int numOfGuesses;

string desiredWord;
string currentGuess;
string used;

bool match(char letter, string word);

char askGuess(string usedLettersString); 

// Simple replacement for the system clear screen command
void clearScreen()
{
    system("CLS");

}

// Prompts the player to play again
int playAgain()
{
    char again;
    cout << "\nWould you like to play again? <y/n>: ";
    cin >> again;

    cin.clear();
    cin.ignore();

    again = toupper(again);

    if (again == 'Y')
    {
        clearScreen();
        wrongGuesses = 0;
        numOfGuesses = 8;
    }
    else
    {
        exit(1);
    }
}

// Uppercases only the first letter on the string passed through
void toUpper(string& str) {
    if (str.length() == 0) {
        return;
    }

    transform(str.begin(), str.end(), str.begin(), ::tolower);
    str[0] = toupper(str[0]);
}


int main()
{
    srand(time(0));

    // The words to guess
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
    words.push_back("BOOKWORM");
    words.push_back("PEEKABOO");
    words.push_back("JACKPOT");
    words.push_back("IVY");
    words.push_back("WIZARD");
    words.push_back("FISHHOOK");
    words.push_back("JOGGING");
    words.push_back("JINX");
    words.push_back("QUEUE");
    words.push_back("PSYCHE");
    words.push_back("ZODIAC");

    cout << "LostRabbitDigital.com\n" << endl;

    while(1)
    {
        // Amount of guesses
        int numOfGuesses = 8;  

        // Pick a random word to guess
        random_shuffle(words.begin(), words.end());
        desiredWord = words[0];           

        // Words guessed
        currentGuess = string(desiredWord.size(), '-');         
        used = "";                            

        // Loop for current word
        while ((wrongGuesses < numOfGuesses) && (currentGuess != desiredWord))
        {
            cout << "Guesses Left: " << (numOfGuesses - wrongGuesses) << endl;
            cout << "\nLetters Used: " << used << endl;
            cout << "\nCurrent Word: " << currentGuess << endl;

            used += askGuess(used);
        } 

        // If the player gets the word correct
        if (currentGuess == desiredWord)
        {
            clearScreen();

            toUpper(desiredWord);
            cout << "You got the word correct, It was " << desiredWord << "." << endl;
            cout << "\nLetters Used: " << used << endl;
            cout << "Guesses Left: " << (numOfGuesses - wrongGuesses) << endl;
            cout << "Word: " << desiredWord << endl;

            playAgain();

        }

        // If the player uses all of their guesses
        if (wrongGuesses == numOfGuesses)
        {
            clearScreen();
            cout << "You died.";

            playAgain();
        }

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
    cout << "\nEnter Guess: ";
    cin >> guess;
    guess = toupper(guess); 


    while (match(guess, used))
    {
        clearScreen();
        cout << "You have already guessed: " << guess << endl;
        cout << "\nLetters Used: " << used << endl;
        cout << "\nCurrent Word: " << currentGuess << endl;
        cout << "\nEnter Guess: ";
        cin >> guess;
        guess = toupper(guess);
    }


    if (match(guess, desiredWord))
    {
        clearScreen();
        cout << "Correct Guess: " << guess << "\n";

        // update currentGuess to include newly guessed letter
        for (int i = 0; i < desiredWord.length(); i++)
            if (desiredWord[i] == guess)
                currentGuess[i] = guess;
    }
    else // Letter was wrong
    {
        clearScreen();
        cout << "Incorrect Guess: " << guess << "\n";
        wrongGuesses++;
    }

    return guess;
}

