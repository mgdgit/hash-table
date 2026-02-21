#include "hash_table.h"
#include <iostream>

using namespace std;

// README and comments pending.

int readInt(const string& prompt);

int main() {
    HashTable deck;
    PlanetCard userCard;
    int userOption = 0;
    size_t deckCurrentAmount;

    cout << endl;
    cout << "==========================================================" << endl;
    cout << "                      PLANET CARDS                        " << endl;
    cout << "==========================================================" << endl;
    cout << endl << "The deck starts with a size of 12 cards." << endl;
    cout << endl << "Options: " << endl << endl;
    cout << "1. Current amount of cards in the deck." << endl;
    cout << "2. Show all the cards that are currently in the deck." << endl;
    cout << "3. Search a card." << endl;
    cout << "4. Insert a card." << endl;
    cout << "5. Delete a card." << endl;
    cout << "6. Exit." << endl << endl;

    while (userOption != 6) {

        cout << "----------------------------------------------------------" << endl;
        userOption = readInt("Select an option: ");
        cout << endl;

        try {

            switch (userOption)
            {
            case 1:
                deckCurrentAmount = deck.currentAmount();
                cout << "Currently there are " << deckCurrentAmount << " cards in the deck." << endl;
                break;
            case 2:
                deck.showCurrentDeck();
                break;
            case 3:
                cout << "Write the name of the card: ";
                cin >> userCard.planetName;
                cout << endl;
                deck.searchCard(userCard);
                break;
            case 4:
                cout << "Write the name of the new card: ";
                cin >> userCard.planetName;
                userCard.id = readInt("Write the ID: ");
                cout << endl;
                deck.insertCard(userCard);
                break;
            case 5:
                cout << "Write the name of the card: ";
                cin >> userCard.planetName;
                cout << endl;
                deck.deleteCard(userCard);
                break;
            case 6:
                break;
            default:
                cout << "Write a valid option." << endl;
            }

        }
        catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }

    }

    return 0;
}

int readInt(const string& prompt) {
    int value;
    
    while (true) {
        cout << prompt;
        if (cin >> value) {
            return value;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << endl << "Write a number.\n";
        cout << "----------------------------------------------------------" << endl;
    }
}