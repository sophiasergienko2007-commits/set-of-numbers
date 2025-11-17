#include <iostream>
using namespace std;

// ===== СТРУКТУРА ВУЗЛА =====
struct Node
{
    int value;
    Node *link;
    Node(int data) : value(data), link(nullptr) {}
};

// Створення списку з масиву
Node *createList(int arr[], int size)
{
    if (size == 0)
        return nullptr;
    Node *head = new Node(arr[0]);
    Node *cur = head;
    for (int i = 1; i < size; i++)
    {
        cur->link = new Node(arr[i]);
        cur = cur->link;
    }
    return head;
}

// Видалення списку
void deleteList(Node *head)
{
    while (head)
    {
        Node *tmp = head;
        head = head->link;
        delete tmp;
    }
}

// Друк списку
void printList(Node *head)
{
    while (head)
    {
        cout << head->value << " ";
        head = head->link;
    }
    cout << endl;
}

// Пошук елемента
bool searchElement(Node *head, int val)
{
    while (head)
    {
        if (head->value == val)
            return true;
        head = head->link;
    }
    return false;
}

// Додавання у кінець
void addElement(Node *&head, int val)
{
    Node *node = new Node(val);
    if (!head)
    {
        head = node;
        return;
    }
    Node *t = head;
    while (t->link)
        t = t->link;
    t->link = node;
}

// Об’єднання (НЕ ЗМІНЮЄ оригінали)
Node *mergeLists(Node *a, Node *b)
{
    Node *res = nullptr;
    Node *tail = nullptr;

    for (Node *x = a; x; x = x->link)
    {
        Node *node = new Node(x->value);
        if (!res)
            res = tail = node;
        else
        {
            tail->link = node;
            tail = node;
        }
    }
    for (Node *x = b; x; x = x->link)
    {
        Node *node = new Node(x->value);
        tail->link = node;
        tail = node;
    }
    return res;
}

// Спільні елементи
Node *commonElements(Node *a, Node *b)
{
    Node *res = nullptr;
    Node *tail = nullptr;
    for (Node *x = a; x; x = x->link)
    {
        if (searchElement(b, x->value))
        {
            Node *node = new Node(x->value);
            if (!res)
                res = tail = node;
            else
            {
                tail->link = node;
                tail = node;
            }
        }
    }
    return res;
}

// Різниця A - B
Node *difference(Node *a, Node *b)
{
    Node *res = nullptr;
    Node *tail = nullptr;
    for (Node *x = a; x; x = x->link)
    {
        if (!searchElement(b, x->value))
        {
            Node *node = new Node(x->value);
            if (!res)
                res = tail = node;
            else
            {
                tail->link = node;
                tail = node;
            }
        }
    }
    return res;
}

// Сортування
void sortList(Node *&head)
{
    if (!head)
        return;
    for (Node *i = head; i; i = i->link)
        for (Node *j = i->link; j; j = j->link)
            if (i->value > j->value)
                swap(i->value, j->value);
}

// ===== ДОДАТКОВІ 4 ОПЕРАЦІЇ =====

// Симетрична різниця (A Δ B)
Node *symmetricDifference(Node *a, Node *b)
{
    Node *d1 = difference(a, b);
    Node *d2 = difference(b, a);
    Node *result = mergeLists(d1, d2);
    deleteList(d1);
    deleteList(d2);
    return result;
}

// Чи A підмножина B
bool isSubset(Node *A, Node *B)
{
    for (Node *x = A; x; x = x->link)
        if (!searchElement(B, x->value))
            return false;
    return true;
}

// Чи рівні множини
bool areEqual(Node *A, Node *B)
{
    return isSubset(A, B) && isSubset(B, A);
}

// Кількість унікальних елементів у списку
int uniqueCount(Node *head)
{
    int count = 0;
    for (Node *x = head; x; x = x->link)
    {
        bool first = true;
        for (Node *y = head; y != x; y = y->link)
            if (y->value == x->value)
                first = false;
        if (first)
            count++;
    }
    return count;
}

// ======== MAIN ========
int main()
{
    int n1, n2;

    cout << "Введіть кількість елементів списку 1: ";
    cin >> n1;
    int *arr1 = new int[n1];
    cout << "Введіть елементи списку 1: ";
    for (int i = 0; i < n1; i++)
        cin >> arr1[i];
    Node *list1 = createList(arr1, n1);
    delete[] arr1;

    cout << "Введіть кількість елементів списку 2: ";
    cin >> n2;
    int *arr2 = new int[n2];
    cout << "Введіть елементи списку 2: ";
    for (int i = 0; i < n2; i++)
        cin >> arr2[i];
    Node *list2 = createList(arr2, n2);
    delete[] arr2;

    cout << "\nСписок 1: ";
    printList(list1);
    cout << "Список 2: ";
    printList(list2);

    cout << "\n5. Додаємо 10 до списку 1: ";
    addElement(list1, 10);
    printList(list1);

    cout << "\n6. Об’єднання списків (копія): ";
    Node *merged = mergeLists(list1, list2);
    printList(merged);

    cout << "\n7. Спільні елементи: ";
    Node *common = commonElements(list1, list2);
    printList(common);

    cout << "\n8. Різниця (list1 - list2): ";
    Node *diff = difference(list1, list2);
    printList(diff);

    cout << "\n9. Симетрична різниця (A Δ B): ";
    Node *sym = symmetricDifference(list1, list2);
    printList(sym);

    cout << "\n10. Чи list2 є підмножиною list1?: ";
    cout << (isSubset(list2, list1) ? "Так" : "Ні") << endl;

    cout << "11. Чи множини рівні?: ";
    cout << (areEqual(list1, list2) ? "Так" : "Ні") << endl;

    cout << "12. Унікальних елементів у list1: " << uniqueCount(list1) << endl;

    cout << "\n13. Сортування list1: ";
    sortList(list1);
    printList(list1);

    cout << "14. Сортування list2: ";
    sortList(list2);
    printList(list2);

    // Видаляємо ТІЛЬКИ окремі копії
    deleteList(list1);
    deleteList(list2);
    deleteList(merged);
    deleteList(common);
    deleteList(diff);
    deleteList(sym);

    return 0;
}
