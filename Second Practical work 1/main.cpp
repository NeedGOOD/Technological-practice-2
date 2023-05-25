#include <iostream>

template <typename T>
class List {
private:
    struct Node {
        T data;
        Node* next;
    };

    Node* head;

public:
    List() : head(nullptr) {}

    ~List() {
        clear();
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    void addToFront(const T& element) {
        Node* newNode = new Node;
        newNode->data = element;
        newNode->next = head;
        head = newNode;
    }

    void addToEnd(const T& element) {
        Node* newNode = new Node;
        newNode->data = element;
        newNode->next = nullptr;

        if (isEmpty()) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    int countOccurrences(const T& element) const {
        int count = 0;
        Node* current = head;
        while (current != nullptr) {
            if (current->data == element) {
                count++;
            }
            current = current->next;
        }
        return count;
    }

    void remove(const T& element) {
        if (isEmpty()) {
            return;
        }

        if (head->data == element) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        Node* current = head;
        while (current->next != nullptr) {
            if (current->next->data == element) {
                Node* temp = current->next;
                current->next = current->next->next;
                delete temp;
                return;
            }
            current = current->next;
        }
    }

    void clear() {
        Node* current = head;
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
        head = nullptr;
    }

    void print() const {
        Node* current = head;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};

int main() {
    // Приклад використання шаблонного класу List з цілими елементами
    List<int> intList;
    intList.addToFront(3);
    intList.addToFront(2);
    intList.addToFront(1);
    intList.addToEnd(4);
    intList.addToEnd(4);
    intList.print();  // Вивід: 1 2 3 4 4
    std::cout << "Occurrences of 4: " << intList.countOccurrences(4) << std::endl;  // Вивід: Occurrences of 4: 2
    intList.remove(2);
    intList.remove(4);
    intList.print();  // Вивід: 1 3

    // Приклад використання шаблонного класу List з рядковими елементами
    List<std::string> stringList;
    stringList.addToFront("World");
    stringList.addToFront("Hello");
    stringList.addToEnd("World");
    stringList.print();  // Вивід: Hello World World
    std::cout << "Occurrences of World: " << stringList.countOccurrences("World") << std::endl;  // Вивід: Occurrences of World: 2
    stringList.remove("Hello");
    stringList.remove("World");
    stringList.print();  // Вивід: World

    return 0;
}