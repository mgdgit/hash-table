#include "hash_table.h"

HashTable::HashTable() {
    deckSize = 12;
    currentAmountOfCards = 0;

    deck = new PlanetCard[deckSize];
}

size_t HashTable::hash(const PlanetCard &userCard) {
    size_t index = 0;
    size_t cardNameLength = userCard.planetName.length();

    for (size_t i = 0; i < cardNameLength; i++) {
        index = (index * 31 + static_cast<unsigned char>(userCard.planetName[i]));
    }

    index = index % deckSize;

    return index;
}

void HashTable::insertCard(const PlanetCard &userCard) {
    size_t currentIndex = hash(userCard);
    size_t startPoint = currentIndex;
    std::optional<size_t> indexWithDeletedState;

    while (deck[currentIndex].state != cardState::DOESNT_EXISTS) {
        if (deck[currentIndex].state == cardState::EXISTS && deck[currentIndex].planetName == userCard.planetName) {
            throw std::runtime_error("That card already exists.");
        }

        if (deck[currentIndex].state == cardState::DELETED) {
            if (!indexWithDeletedState.has_value()) {
                indexWithDeletedState = currentIndex;
            } 
        }

        currentIndex = (currentIndex + 1) % deckSize;


        if (currentIndex == startPoint) {
            if (indexWithDeletedState.has_value()) break;
            throw std::runtime_error("The deck is already full.");
        }
    }

    if (indexWithDeletedState.has_value()) {
        deck[*indexWithDeletedState].planetName = userCard.planetName;
        deck[*indexWithDeletedState].id = userCard.id;
        deck[*indexWithDeletedState].state = cardState::EXISTS;
        ++currentAmountOfCards;
        std::cout << userCard.planetName << " card was inserted correctly." << std::endl;
    }
    else {
        deck[currentIndex].planetName = userCard.planetName;
        deck[currentIndex].id = userCard.id;
        deck[currentIndex].state = cardState::EXISTS;
        ++currentAmountOfCards;
        std::cout << userCard.planetName << " card was inserted correctly." << std::endl;
    }

    float loadFactor = static_cast<float>(currentAmountOfCards) / deckSize;
    if (loadFactor > 0.7) {
        rehash();
    }
}

void HashTable::searchCard(const PlanetCard &userCard) {
    if (currentAmountOfCards == 0) {
        throw std::length_error("You can't use this option with the deck empty.");
    }

    size_t currentIndex = hash(userCard);
    size_t startPoint = currentIndex;

    while (deck[currentIndex].state != cardState::DOESNT_EXISTS) {
        if (deck[currentIndex].state == cardState::EXISTS && deck[currentIndex].planetName == userCard.planetName) {
            std::cout << "That card exists and has an ID of " + std::to_string(deck[currentIndex].id) + "." << std::endl;
            return;
        }

        currentIndex = (currentIndex + 1) % deckSize;

        if (currentIndex == startPoint) {
            throw std::runtime_error("That card doesn't exists.");
        }
    }
}

void HashTable::deleteCard(const PlanetCard &userCard) {
    if (currentAmountOfCards == 0) {
        throw std::length_error("You can't use this option with the deck empty.");
    }

    size_t currentIndex = hash(userCard);
    size_t startPoint = currentIndex;

    while (deck[currentIndex].state != cardState::DOESNT_EXISTS) {
        if (deck[currentIndex].state == cardState::EXISTS && deck[currentIndex].planetName == userCard.planetName) {
            deck[currentIndex].state = cardState::DELETED;
            std::cout << "That card has been successfully deleted." << std::endl;
            --currentAmountOfCards;
            return;
        }

        currentIndex = (currentIndex + 1) % deckSize;

        if (currentIndex == startPoint) {
            throw std::runtime_error("That card doesn't exists.");
        }
    }
}

void HashTable::showCurrentDeck() {
    for (size_t i = 0; i < deckSize; i++) {
        if (deck[i].state == cardState::EXISTS) {
            std::cout << "Card Name: " << deck[i].planetName << ", ID: " << deck[i].id << "." << std::endl;
        }
    }
}

size_t HashTable::currentAmount() {
    return currentAmountOfCards;
}

void HashTable::rehash() {

    std::cout << "------------------------------------------------------------------------" << std::endl;

    std::cout << "To maintain insert and search performance, we will double the deck size." << std::endl;

    std::cout << "------------------------------------------------------------------------" << std::endl;

    PlanetCard *oldDeck = deck;
    size_t oldDeckSize = deckSize;

    deckSize *= 2;
    deck = new PlanetCard[deckSize];
    currentAmountOfCards = 0;
    
    for (size_t i = 0; i < oldDeckSize; i++) {
        if (oldDeck[i].state == cardState::EXISTS) {
            insertCard(oldDeck[i]);
        }
    }

    delete[] oldDeck;

}

bool HashTable::isEmpty() {
    if (currentAmountOfCards == 0) {
        return true;
    }
    else {
        return false;
    }
}

HashTable::~HashTable() {
    delete[] deck;
}