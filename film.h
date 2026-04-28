#pragma once
#include <stdio.h>
#include <iostream>
#include <iomanip>

class film
{
private:
    int id;
    std::string titlu;
    std::string gen;
    int durata; // minute
    double rating;
public:
    film(int id, const std::string& titlu, const std::string& gen, int durata, double rating)
        : id(id), titlu(titlu), gen(gen), durata(durata), rating(rating) {}

    int getId() const { return id; }
    std::string getTitlu() const { return titlu; }
    std::string getGen() const { return gen; }
    int getDurata() const { return durata; }
    double getRating() const { return rating; }
    void afiseaza() const {
        std::cout << std::left
            << "[ID: " << std::setw(3) << id << "] "
            << std::setw(30) << titlu
            << " | Gen: " << std::setw(15) << gen
            << " | Durata: " << std::setw(4) << durata << " min"
            << " | Rating: " << std::fixed << std::setprecision(1) << rating << "/10"
            << std::endl;
    }

};

