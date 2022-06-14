#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Car {
    string carNumber;
    string model;
    int type;

    union {
        struct {
            int passengerCount;
        } passengerCar;
        struct {
            int weightLimit;
        } truck;
    };
    string owner;
};

Car createCarFromKeyboard() {
    Car newCar;

    cout << "����� ���: " << endl;
    cin >> newCar.carNumber;
    cout << "��ઠ ���: " << endl;
    cin >> newCar.model;

    cout << "��⮬����� ���� ������� ��� ��㧮��? (0 - �������� ��� 1 - ��㧮���): " << endl;
    cin >> newCar.type;

    if (newCar.type == 0) {
        cout << "������ ���ᨬ��쭮� ���-�� ���ᠦ�஢: " << endl;
        cin >> newCar.passengerCar.passengerCount;
    } else {
        cout << "������ ���ᨬ���� ��� ��㧠: " << endl;
        cin >> newCar.truck.weightLimit;
    }

    cout << "������ ��� �������� ��⮬�����: " << endl;
    cin >> newCar.owner;

    return newCar;
}

void printCar(Car car) {
    cout << "����� ���: " << car.carNumber << endl;
    cout << "��ઠ ���: " << car.model << endl;

    if (car.type == 0) {
        cout << "���: �������� ��⮬�����" << endl;
        cout << "���ᨬ��쭮� ������⢮ ���ᠦ�஢" << car.passengerCar.passengerCount << endl;
    } else {
        cout << "���: ��㧮��� ��⮬�����: " << endl;
        cout << "���ᨬ���� ��� ��㧠: " << endl;
    }

    cout << "�������� ��⮬�����: " << car.owner << endl;
}

struct Node {
    Car value;
    Node *next;

    Node(Car x) : value(x), next(nullptr) {}

    Car getValue() {
        return this->value;
    }

    void setValue(Car newValue) {
        this->value = newValue;
    }
};

struct LinkedList {
    Node *first;
    int size = 0;

    LinkedList() : first(nullptr) {
    }

    int getSize() {
        return size;
    }

    void addFirst(Node *n) {
        n->next = first;
        first = n;
        size++;
    }

    void addLast(Node *n) {
        if (first == nullptr) {
            first = n;
            return;
        }
        Node *t = first;
        while (t->next != nullptr) {
            t = t->next;
        }
        t->next = n;
        size++;
    }

    void addByIndex(Node *n, int index) {
        if (index < 0 || index > size - 1) {
            cout << "index not correct" << endl;
            return;
        }
        if (index == 0) {
            addFirst(n);
            return;
        }
        if (index == size - 1) {
            addLast(n);
            return;
        }
        int cnt = 0;
        Node *curr = first;
        Node *temp;
        size++;

        while (true) {
            if (cnt == index - 1) {
                temp = curr->next;
                curr->next = n;
                n->next = temp;
                return;
            }

            curr = curr->next;
            cnt++;
        }
    }

    void deleteFirst() {
        Node *old_head = first;
        first = first->next;
        delete old_head;
        size--;
    }

    void deleteByIndex(int index) {
        if (index < 0 || index > size - 1) {
            cout << "index not correct" << endl;
            return;
        }

        Node *curr = first;
        int cnt = 0;
        while (cnt != index - 2) {
            curr = curr->next;
            cnt++;
        }
        Node *nodeToDel = curr->next;
        curr->next = curr->next->next;
        delete nodeToDel;
        size--;
    }

    Car get(int index) {
        Node *t = first;
        int current = 0;

        while (current != index) {
            current++;
            t = t->next;
        }

        return t->getValue();
    }
};

int main() {
    LinkedList *list = new LinkedList();

    Car toyota;
    toyota.carNumber = "�123��";
    toyota.model = "Toyota";
    toyota.type = 0;
    toyota.passengerCar.passengerCount = 4;
    toyota.owner = "����ᥩ";

    Car kamaz;
    toyota.carNumber = "�348��";
    toyota.model = "�����";
    toyota.type = 1;
    toyota.truck.weightLimit = 20000;
    toyota.owner = "�������";

    Car honda;
    toyota.carNumber = "�453��";
    toyota.model = "Honda";
    toyota.type = 0;
    toyota.passengerCar.passengerCount = 4;
    toyota.owner = "�������";

    list->addLast(new Node(toyota));
    list->addLast(new Node(kamaz));
    list->addLast(new Node(honda));


    while (true) {
        cout << "0 - �������� �����" << "\n";
        cout << "1 - ������� �����" << "\n";
        cout << "2 - �뢥�� �����" << "\n";
        cout << "3 - �뢥�� ������⢮ ����⮢" << "\n";
        cout << "4 - �������� �ணࠬ��" << "\n\n";

        int choose = -1;

        cout << "�롥�� ����⢨�: ";
        cin >> choose;

        switch (choose) {
            case 0: {
                list->addLast(new Node(createCarFromKeyboard()));
                break;
            }
            case 1: {
                int index = -1;
                cout << "������ ����� ����� ��� 㤠�����: ";
                cin >> index;
                index--;

                if (index > list->getSize() - 1 || index < 0) {
                    cout << "������� ����� ��� � ᯨ᪥\n";
                    break;
                }

                if (list->getSize() == 0) {
                    cout << "���᮪ ��ꥪ⮢ ����\n";
                    break;
                }

                list->deleteByIndex(index);
                break;
            }
            case 2: {
                int index = -1;
                cout << "������ ����� �����: ";
                cin >> index;
                index--;

                if (index > list->getSize() - 1 || index < 0) {
                    cout << "������� ����� ��� � ᯨ᪥\n";
                    break;
                }

                if (list->getSize() == 0) {
                    cout << "���᮪ ��ꥪ⮢ ����\n";
                    break;
                }

                printCar(list->get(index));
                break;
            }
            case 3: {
                cout << "������⢮ ����⮢: " << list->size << "\n";
                break;
            }
            case 4: {
                return 0;
            }
            default: {
                cout << "�� ����� �����४⭮� �᫮, ������ ������";
            }
        }

        cout << "\n";
    }
}
