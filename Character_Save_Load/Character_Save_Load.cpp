#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>

struct character
{
    std::string name = "Unknown";
    int health = 0;
    int armor = 0;
};


void save_character(std::ofstream& file, character& person)
{
    int len = person.name.length();
    file.write((char*)&len, sizeof(len));
    file.write(person.name.c_str(), len);
    file.write((char*)&person.health, sizeof(person.health));
    file.write((char*)&person.armor, sizeof(person.armor));
}

void load_character(std::ifstream& file, character& person)
{
    int len;
    file.read((char*)&len, sizeof(len));
    person.name.resize(len);
    file.read((char*)person.name.c_str(), len);
    file.read((char*)&person.health, sizeof(person.health));
    file.read((char*)&person.armor, sizeof(person.armor));
}

void take_damage(character& person, int damage)
{
    std::cout << person.name << " took damage: -" << damage << std::endl;
    person.armor -= damage;
    if (person.armor < 0) {
        person.health += person.armor;
        person.armor = 0;
    }
}

int main()
{
    character people[10];

    // save file to bin
    //for (int i = 0; i < 10; ++i) {
    //    people[i].name = "Character #" + std::to_string(i);
    //    people[i].health = (std::rand() % 100) + 100;
    //    people[i].armor = (std::rand() % 40) + 10;
    //}

    //for (int i = 0; i < 10; ++i) {
    //    take_damage(people[i], 30);
    //}

    people[0].name = "Seba";
    
    std::ifstream file("C:\\tutorial-data\\save.bin", std::ios::binary); // load file from bin
    for (int i = 0; i < 10; ++i) {
        load_character(file, people[i]);
    }
    for (int i = 0; i < 10; ++i) {
        std::cout << people[i].name << std::endl;
    }
}

