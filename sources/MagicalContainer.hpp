#ifndef MAGICALCONTAINER_H
#define MAGICALCONTAINER_H

#include <vector>
#include <cmath>
#include <algorithm>

namespace ariel {}

class MagicalContainer {
private:
    std::vector<int> elements;
    std::vector<int*> primeElements;
    std::vector<int*> sideCrossElements;

    void sortSideCrossElements();
    bool isPrime(int number);

public:
    MagicalContainer();
    ~MagicalContainer();
    MagicalContainer(const MagicalContainer& other);
    MagicalContainer& operator=(const MagicalContainer& other);

    void addElement(int element);
    void removeElement(int element);
    [[nodiscard]] size_t size() const;

    class AscendingIterator;
    class SideCrossIterator;
    class PrimeIterator;

};

class MagicalContainer::AscendingIterator {

private:
    const MagicalContainer& container;
    size_t currentIndex;

public:
    AscendingIterator(const MagicalContainer& cont);
    AscendingIterator(const AscendingIterator& other);
    ~AscendingIterator();
    [[nodiscard]] AscendingIterator begin() const;
    [[nodiscard]] AscendingIterator end() const;

    AscendingIterator& operator=(const AscendingIterator& other);
    AscendingIterator& operator++();
    int operator*() const;
    bool operator==(const AscendingIterator& other) const;
    bool operator!=(const AscendingIterator& other) const;
    bool operator>(const AscendingIterator& other) const;
    bool operator<(const AscendingIterator& other) const;
};

class MagicalContainer::SideCrossIterator {

private:
    const MagicalContainer& container;
    size_t currentIndex;

public:
    SideCrossIterator(const MagicalContainer& cont);
    SideCrossIterator(const SideCrossIterator& other);
    ~SideCrossIterator();

    SideCrossIterator& operator=(const SideCrossIterator& other);

    SideCrossIterator& operator++();
    int operator*() const;

    bool operator==(const SideCrossIterator& other) const;
    bool operator!=(const SideCrossIterator& other) const;
    bool operator>(const SideCrossIterator& other) const;
    bool operator<(const SideCrossIterator& other) const;

    SideCrossIterator begin() const;

    SideCrossIterator end() const;
};

class MagicalContainer::PrimeIterator {

private:
    const MagicalContainer& container;
    size_t currentIndex;

public:
    PrimeIterator(const MagicalContainer& cont);
    PrimeIterator(const PrimeIterator& other);
    ~PrimeIterator();

    PrimeIterator& operator=(const PrimeIterator& other);

    PrimeIterator& operator++();
    int operator*() const;

    bool operator==(const PrimeIterator& other) const;
    bool operator!=(const PrimeIterator& other) const;
    bool operator>(const PrimeIterator& other) const;
    bool operator<(const PrimeIterator& other) const;

    PrimeIterator begin() const;

    PrimeIterator end() const;
};





#endif  // MAGICALCONTAINER_H
