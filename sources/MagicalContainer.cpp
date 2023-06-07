#include <stdexcept>
#include "MagicalContainer.hpp"


bool MagicalContainer::isPrime(int number) {
    if (number < 2) {
        return false;
    }
    double sqrtNum = std::sqrt(number);
    for (int i = 2; i <= sqrtNum; ++i) {
        if (number % i == 0) {
            return false;
        }
    }
    return true;
}

void MagicalContainer::sortSideCrossElements() {
    size_t vectorSize = size();

    for (size_t i = 0; i < vectorSize; i++) {
        if (i % 2 == 0) {
            sideCrossElements[i] = &(elements[i / 2]);
        } else {
            sideCrossElements[i] = &(elements[vectorSize - (i / 2) - 1]);
        }
    }
}

// Default constructor
MagicalContainer::MagicalContainer() {
    elements = {};
    primeElements = {};
    sideCrossElements = {};
}

// Destructor
MagicalContainer::~MagicalContainer() {
    // Delete the dynamically allocated primeElements
    for (int *element: primeElements) {
        delete element;
    }
    
}

// Copy constructor
MagicalContainer::MagicalContainer(const MagicalContainer &other)
        : elements(other.elements), primeElements(), sideCrossElements() {
    // Copy primeElements
    for (int *element: other.primeElements) {
        int *newElement = new int(*element);
        primeElements.push_back(newElement);
    }

    // Copy sideCrossElements
    for (int *element: other.sideCrossElements) {
        int *newElement = new int(*element);
        sideCrossElements.push_back(newElement);
    }
}

// Assignment operator
MagicalContainer &MagicalContainer::operator=(const MagicalContainer &other) {
    if (this != &other) {
        // Delete the current primeElements
        for (int *element: primeElements) {
            delete element;
        }
        primeElements.clear();

        // Delete the current sideCrossElements
        for (int *element: sideCrossElements) {
            delete element;
        }
        sideCrossElements.clear();

        // Copy elements
        elements = other.elements;

        // Copy primeElements
        for (int *element: other.primeElements) {
            int *newElement = new int(*element);
            primeElements.push_back(newElement);
        }

        // Copy sideCrossElements
        for (int *element: other.sideCrossElements) {
            int *newElement = new int(*element);
            sideCrossElements.push_back(newElement);
        }
    }
    return *this;
}


void MagicalContainer::addElement(int element) {

    elements.push_back(element);
    std::sort(elements.begin(), elements.end());

    if (isPrime(element)) {
        primeElements.emplace_back(new int(element));
        std::sort(primeElements.begin(), primeElements.end(), [](const int *a, const int *b) {
            return (*a) < (*b);
        });
    }
    sideCrossElements.emplace_back(&element);
    sortSideCrossElements();
}

void MagicalContainer::removeElement(int element) {
    if (isPrime(element)) {
        auto it1 = std::find(primeElements.begin(), primeElements.end(), &element);
        if (it1 != primeElements.end()) {
            delete *it1;
            primeElements.erase(it1);
        }
    }

    auto it2 = std::find(sideCrossElements.begin(), sideCrossElements.end(), &element);
    if (it2 != sideCrossElements.end()) {
        delete *it2;
        sideCrossElements.erase(it2);
        sortSideCrossElements();
    }

    auto it3 = std::find(elements.begin(), elements.end(), element);
    if (it3 != elements.end()) {
        elements.erase(it3);
        std::sort(elements.begin(), elements.end());
    } else {
        throw std::runtime_error("Element not found in the container.");
    }
}


size_t MagicalContainer::size() const {
    return elements.size();
}

// AscendingIterator

// Default constructor
MagicalContainer::AscendingIterator::AscendingIterator(const MagicalContainer &cont)
        : container(cont), currentIndex(0) {}

// Copy constructor
MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator &other)
        : container(other.container), currentIndex(other.currentIndex) {}

// Assignment operator
MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator=(const AscendingIterator &other) {
    if (this != &other) {
        throw std::runtime_error("Iterators are pointing at different containers");
    }
    return *this;
}

// Pre-increment operator
MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++() {
    if (currentIndex == container.size()) throw std::runtime_error("Iterator is pointing at the end of the container.");
    else {
        ++currentIndex;
        return *this;
    }
}

// Dereference operator
int MagicalContainer::AscendingIterator::operator*() const {
    if (currentIndex >= container.elements.size()) {
        throw std::out_of_range("Iterator out of range.");
    }
    return container.elements[currentIndex];
}

// Equality comparison (operator==)
bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator &other) const {
    return currentIndex == other.currentIndex;
}

// Inequality comparison (operator!=)
bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator &other) const {
    return currentIndex != other.currentIndex;
}

// GT comparison (operator>)
bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator &other) const {
    return currentIndex > other.currentIndex;
}

// LT comparison (operator<)
bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator &other) const {
    return currentIndex < other.currentIndex;
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin() const {
    return {container};
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end() const {
    MagicalContainer::AscendingIterator a(container);
    a.currentIndex = container.size();
    return a;
}

// SideCrossIterator

// Default constructor
MagicalContainer::SideCrossIterator::SideCrossIterator(const MagicalContainer &cont)
        : container(cont), currentIndex(0) {}

// Copy constructor
MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator &other)
        : container(other.container), currentIndex(other.currentIndex) {}

// Assignment operator
MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator &other) {
    if (this != &other) {
        throw std::runtime_error("Iterators are pointing at different containers");
    }
    return *this;
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin() const {
    return {container};
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end() const {
    MagicalContainer::SideCrossIterator a(container);
    a.currentIndex = container.size();
    return a;
}

// Pre-increment operator
MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++() {
    if (currentIndex == container.size()) throw std::runtime_error("Iterator is pointing at the end of the container.");
    else {
        ++currentIndex;
        return *this;
    }
}

// Dereference operator
int MagicalContainer::SideCrossIterator::operator*() const {
    if (currentIndex >= container.sideCrossElements.size()) {
        throw std::out_of_range("Iterator out of range.");
    }
    return *(container.sideCrossElements[currentIndex]);
}

// Equality comparison (operator==)
bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator &other) const {
    return currentIndex == other.currentIndex;
}

// Inequality comparison (operator!=)
bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator &other) const {
    return currentIndex != other.currentIndex;
}

// GT comparison (operator>)
bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator &other) const {
    return currentIndex > other.currentIndex;
}

// LT comparison (operator<)
bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator &other) const {
    return currentIndex < other.currentIndex;
}

// Prime Iterator

// Default constructor
MagicalContainer::PrimeIterator::PrimeIterator(const MagicalContainer &cont)
        : container(cont), currentIndex(0) {}

// Copy constructor
MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator &other)
        : container(other.container), currentIndex(other.currentIndex) {}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() const {
    return {container};
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() const {
    MagicalContainer::PrimeIterator a(container);
    a.currentIndex = container.primeElements.size();
    return a;
}

// Assignment operator
MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator=(const PrimeIterator &other) {
    if (this != &other) {
        throw std::runtime_error("Iterators are pointing at different containers");
    }
    return *this;
}

// Pre-increment operator
MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++() {
    if (currentIndex == container.primeElements.size()) throw std::runtime_error("Iterator is pointing at the end of the container.");
    else {
        ++currentIndex;
        return *this;
    }
}

// Dereference operator
int MagicalContainer::PrimeIterator::operator*() const {
    if (currentIndex >= container.primeElements.size()) {
        throw std::out_of_range("Iterator out of range.");
    }
    return *(container.primeElements[currentIndex]);
}

// Equality comparison (operator==)
bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator &other) const {
    return currentIndex == other.currentIndex;
}

// Inequality comparison (operator!=)
bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator &other) const {
    return currentIndex != other.currentIndex;
}

// GT comparison (operator>)
bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator &other) const {
    return currentIndex > other.currentIndex;
}

// LT comparison (operator<)
bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator &other) const {
    return currentIndex < other.currentIndex;
}

