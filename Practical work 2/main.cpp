#include <iostream>
#include <vector>

void pauseAndClear() {
    std::cout << "Press Enter to continue...\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
    std::system("cls");
}

void error() { std::cout << "Invalid input.\n"; }

struct Animal {
    int id;
    std::string type;
    std::string sex;
    std::string name;
    double price;

    Animal() {
        id = 0;
        type = "";
        sex = "";
        name = "";
        price = 0.0;
    }

    Animal(int id, std::string type, std::string sex, std::string name, double price) {
        this->id = id;
        this->type = type;
        this->sex = sex;
        this->name = name;
        this->price = price;
    }

    Animal(Animal &object) {
        this->id = object.id;
        this->type = object.type;
        this->sex = object.sex;
        this->name = object.name;
        this->price = object.price;
    }
};

class Zoomagazin {
private:
    std::vector<Animal> animals;
    std::vector<Animal> animals_bought;
public:
    int add() { return 1; }

    void addAnimals() {
        int animal_type_count;
        std::cout << "Number of animal types: ", std::cin >> animal_type_count;
        std::cout << '\n';

        for (int i = 0; i < animal_type_count; ++i) {
            std::string animal_type;
            std::cout << "Animal type: ", std::cin >> animal_type;

            int animal_count;
            std::cout << "Number of animals: ", std::cin >> animal_count;
            std::cout << '\n';

            addAnimals(animal_type, animal_count);
        }
        std::cout << "Input is complete.\n";
        pauseAndClear();
    }

    void addAnimals(std::string animal_type, int animal_count) {
        for (int i = 0; i < animal_count; ++i) {
            int id = i + 1;
            std::cout << animal_type << ' ' << id << ":\n";

            std::string sex;
            std::cout << "Sex: ", std::cin >> sex;

            std::string name;
            std::cout << "Name: ", std::cin >> name;

            double price;
            std::cout << "Price: ", std::cin >> price;

            std::cout << '\n';

            animals.push_back(Animal{id, animal_type, sex, name, price});
        }
    }

    void showAnimals() {
        std::cout << "Animals (" << animals.size() << "):\n";
        for (Animal animal : animals) {
            std::cout << "  ID:    " << animal.id << '\n'
                      << "  Type:  " << animal.type << '\n'
                      << "  Sex:   " << animal.sex << '\n'
                      << "  Name:  " << animal.name << '\n'
                      << "  Price: " << animal.price << '\n'
                      << '\n';
        }
        pauseAndClear();
    }

    void showAnimals(std::string animal_type, int buy_or_not = 0) {
        bool have = false;

        for (Animal animal : animals) {
            if (animal.type == animal_type) {
                std::cout << "  ID:    " << animal.id << '\n'
                          << "  Sex:   " << animal.sex << '\n'
                          << "  Name:  " << animal.name << '\n'
                          << "  Price: " << animal.price << '\n'
                          << '\n';
                have = true;
            }
        }
        
        if (!have) {
            std::cout << "There is no such animal.\n";
            
            if (buy_or_not == 1) {
                pauseAndClear();
                return;
            }
        }

        if (buy_or_not == 1) {
            std::cout << "How number (ID) animal you want buy?\n";

            int id;
            std::cout << "~ ", std::cin >> id;
            buyingAnimal(animal_type, id, have);
        }
        pauseAndClear();
    }

    void buyingAnimal(std::string animal_type, int id, bool have) {
        for (Animal animal : animals) {
            if (animal.type == animal_type) {
                if (!(id < 0 && id > animal.id) && animal.id == id) {
                    std::cout << "  ID:    " << animal.id << '\n'
                              << "  Sex:   " << animal.sex << '\n'
                              << "  Name:  " << animal.name << '\n'
                              << "  Price: " << animal.price << '\n'
                              << '\n';
                    std::cout << "Purchase completed.\n";
                    have = true;
                    animals_bought.push_back(Animal(id, animal_type, animal.sex, animal.name, animal.price));
                    break;
                } else { have = false; }
            }
        }

        if (!have) { error(); }
    }

    void showBoughtAnimals() {
        std::cout << "Animals boughts (" << animals_bought.size() << "):\n";
        for (Animal animal : animals_bought) {
            std::cout << "  ID:    " << animal.id << '\n'
                      << "  Type:  " << animal.type << '\n'
                      << "  Sex:   " << animal.sex << '\n'
                      << "  Name:  " << animal.name << '\n'
                      << "  Price: " << animal.price << '\n'
                      << '\n';
        }
        pauseAndClear();
    }
};

int main() {
    Zoomagazin zoomagazin;

    bool work = true;
    int number = 2;
    int buy = 2;

    while (work) {
        std::cout << "Menu:\n";
        std::cout << "1. Add animals;\n"
                  << "2. Show animals;\n"
                  << "3. Show animals of type;\n"
                  << "4. Buying an animal;\n"
                  << "5. Show boughts animals;\n"
                  << "6. Exit.\n";

        int menu;
        std::cout << "~ ", std::cin >> menu;

        if (std::cin.fail()) {
            std::system("cls");
            std::cout << "Invalid input.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        std::system("cls");
        switch (menu) {
            case 1:
                zoomagazin.addAnimals();
                number = zoomagazin.add();
                break;
            case 2:
                if (number == 1) { zoomagazin.showAnimals(); }
                else if (number == 2) { std::cout << "The table is empty.\n"; pauseAndClear(); }
                break;
            case 3: {
                if (number == 1) {
                    std::string animal_type;
                    std::cout << "Animal type: ", std::cin >> animal_type;

                    zoomagazin.showAnimals(animal_type);
                } else if (number == 2) { std::cout << "The table is empty.\n"; pauseAndClear(); }
                break;
            }
            case 4: {
                if (number == 1) {
                    std::string animal_type;
                    std::cout << "Animal type: ", std::cin >> animal_type;

                    zoomagazin.showAnimals(animal_type, 1);

                } else if (number == 2) { std::cout << "No data has been added yet.\n"; pauseAndClear(); }
                break;
            }
            case 5:
                if (number == 1) { zoomagazin.showBoughtAnimals(); }
                else if (number == 2) { std::cout << "Nothing was bought.\n"; pauseAndClear(); }
                break;
            case 6:
                work = false;
                std::cout << "The program is completed.\n";
                break;
            default:
                error();
                break;
        }
    }
    return 0;
}