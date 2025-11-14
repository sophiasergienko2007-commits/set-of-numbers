#include <iostream>
using namespace std;

//Оголошення структури вузла списку
struct Node {
    int value;
    Node* link;
    Node(int data) : value(data), link(nullptr) {}
};

// 1. Створення та заповнення списку
Node* createList(int arr[], int size) {
    if (size == 0) return nullptr;
    Node* list = new Node(arr[0]);
    Node* current = list;
    for (int i = 1; i < size; ++i) {
        current->link = new Node(arr[i]);
        current = current->link;
    }
    return list;
}

// 2. Видалення списку
void deleteList(Node*& list) {
    while (list!=nullptr) {
        Node* victim = list;
        list = list->link;
        delete victim;
    }
}

// 3. Вивід на екран
void printList(Node* head) {
    while (head!=nullptr) {
        cout << head->value << " ";
        head = head->link;
    }
    cout << endl;
}

// 4. Пошук елемента
bool searchElement(Node* head, int value) {
    while (head!=nullptr) {
        if (head->value == value)
            return true;
        head = head->link;
    }
    return false;
}

// 5. Додавання елемента в кінець списку
void addElement(Node*& head, int value) {
    Node* newNode = new Node(value);
    if (!head) {
        head = newNode;
        return;
    }
    Node* temp = head;
    while (temp->link) temp = temp->link;
    temp->link = newNode;
}

// 6. Об’єднання двох списків
Node* mergeLists(Node* list1, Node* list2) {
    if (!list1) return list2;
    Node* temp = list1;
    while (temp->link) temp = temp->link;
    temp->link = list2;
    return list1;
}

// 7. Виведення спільних елементів двох списків
Node* commonElements(Node* list1, Node* list2) {
    Node* result = nullptr;
    Node* tail = nullptr;
    for (Node* i = list1; i != nullptr; i = i->link) {
        if (searchElement(list2, i->value)) {
            Node* newNode = new Node(i->value);
            if (!result)
                result = tail = newNode;
            else {
                tail->link = newNode;
                tail = tail->link;
            }
        }
    }
    return result;
}

// 8. Різниця списків (елементи з list1, яких немає у list2)
Node* difference(Node* list1, Node* list2) {
    Node* result = nullptr;
    Node* tail = nullptr;
    for (Node* i = list1; i != nullptr; i = i->link) {
        if (!searchElement(list2, i->value)) {
            Node* newNode = new Node(i->value);
            if (!result)
                result = tail = newNode;
            else {
                tail->link = newNode;
                tail = tail->link;
            }
        }
    }
    return result;
}

// 9. Додати до списку різницю елементів
void addDifference(Node*& list1, Node* list2) {
    Node* diff = difference(list2, list1);
    list1 = mergeLists(list1, diff);
}

// 10. Сортування списку (просте сортування обміном)
void sortList(Node*& head) {
    if (!head) return;
    for (Node* i = head; i->link != nullptr; i = i->link) {
        for (Node* j = i->link; j != nullptr; j = j->link) {
            if (i->value > j->value) {
                swap(i->value, j->value);
            }
        }
    }
}

int main() {
    int arr1[] = {20, 30, 40, 10};
    int arr2[] = {30, 50, 10, 60};

    Node* list1 = createList(arr1, 4);
    Node* list2 = createList(arr2, 4);

    cout << "Список 1: ";
    printList(list1);
    cout << "Список 2: ";
    printList(list2);

    cout << "\n4. Пошук 30 у списку 1: ";
    cout << (searchElement(list1, 30) ? "є" : "немає") << endl;

    cout << "\n5. Додамо 25 у список 1: ";
    addElement(list1, 25);
    printList(list1);

    cout << "\n6. Об’єднання двох списків: ";
    Node* merged = mergeLists(list1, list2);
    printList(merged);

    cout << "\n7. Спільні елементи: ";
    Node* common = commonElements(list1, list2);
    printList(common);

    cout << "\n8. Різниця (list1 - list2): ";
    Node* diff = difference(list1, list2);
    printList(diff);

    cout << "\n9. Додамо до list1 різницю (list2 - list1): ";
    addDifference(list1, list2);
    printList(list1);

    cout << "\n10. Сортування list1: ";
    sortList(list1);
    printList(list1);

    cout << "\n11. Видалення списків: ";
    // Очистимо пам'ять видаливши наші ініціалізовані списки
    deleteList(list1);
    deleteList(list2);
    deleteList(common);
    deleteList(diff);

}

