#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include <string>
#include <iostream>
#include <stdexcept>
#include <optional>

enum class cardState {
    DOESNT_EXISTS,
    EXISTS,
    DELETED
};

struct PlanetCard {
    std::string planetName;
    int id;
    cardState state = cardState::DOESNT_EXISTS;
};

class HashTable {
    private:
        PlanetCard* deck;
        size_t deckSize;
        size_t currentAmountOfCards;
    
    public:
        HashTable();

        HashTable(const HashTable&) = delete;
        HashTable& operator=(const HashTable&) = delete;

        size_t hash(const PlanetCard &userCard);

        void insertCard(const PlanetCard &userCard);

        void searchCard(const PlanetCard &userCard);

        void deleteCard(const PlanetCard &userCard);

        void showCurrentDeck();

        size_t currentAmount();

        void rehash();

        bool isEmpty();

        ~HashTable();
};

#endif