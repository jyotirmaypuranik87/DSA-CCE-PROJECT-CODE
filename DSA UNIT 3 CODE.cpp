
#include <iostream>
#include <cstdlib>
using namespace std;

struct Node {
    int coeff, exp;
    Node* next;

    Node(int c, int e) {
        coeff = c;
        exp = e;
        next = nullptr;
    }
};

class Polynomial {
    Node* head;

public:
    Polynomial() {
        head = nullptr;
    }

    // Insert terms in descending order of exponent
    void insert(int coeff, int exp) {
        if (coeff == 0)
            return;

        Node *curr = head, *prev = nullptr;

        while (curr && curr->exp > exp) {
            prev = curr;
            curr = curr->next;
        }

        // Combine terms with equal exponents
        if (curr && curr->exp == exp) {
            curr->coeff += coeff;

            if (curr->coeff == 0) {
                if (prev)
                    prev->next = curr->next;
                else
                    head = curr->next;

                delete curr;
            }
            return;
        }

        Node* temp = new Node(coeff, exp);
        temp->next = curr;

        if (prev)
            prev->next = temp;
        else
            head = temp;
    }

    void input() {
        int n, c, e;

        cout << "Enter number of terms: ";
        cin >> n;

        for (int i = 0; i < n; i++) {
            cout << "Enter coefficient and exponent: ";
            cin >> c >> e;

            if (e < 0) {
                cout << "Exponent cannot be negative.\n";
                i--;
                continue;
            }

            insert(c, e);
        }
    }

    void display() const {
        if (!head) {
            cout << "0";
            return;
        }

        Node* curr = head;
        bool first = true;

        while (curr) {
            int c = curr->coeff;
            int e = curr->exp;

            if (!first)
                cout << (c > 0 ? " + " : " - ");
            else if (c < 0)
                cout << "-";

            int value = abs(c);

            if (e == 0 || value != 1)
                cout << value;

            if (e > 0) {
                cout << "x";

                if (e > 1)
                    cout << "^" << e;
            }

            first = false;
            curr = curr->next;
        }
    }

    // Addition
    Polynomial add(const Polynomial& p) const {
        Polynomial result;

        for (Node* t = head; t; t = t->next)
            result.insert(t->coeff, t->exp);

        for (Node* t = p.head; t; t = t->next)
            result.insert(t->coeff, t->exp);

        return result;
    }

    // Subtraction
    Polynomial subtract(const Polynomial& p) const {
        Polynomial result;

        for (Node* t = head; t; t = t->next)
            result.insert(t->coeff, t->exp);

        for (Node* t = p.head; t; t = t->next)
            result.insert(-t->coeff, t->exp);

        return result;
    }

    // Multiplication
    Polynomial multiply(const Polynomial& p) const {
        Polynomial result;

        for (Node* a = head; a; a = a->next) {
            for (Node* b = p.head; b; b = b->next) {
                result.insert(a->coeff * b->coeff,
                              a->exp + b->exp);
            }
        }

        return result;
    }

    // Deep copy constructor
    Polynomial(const Polynomial& p) : head(nullptr) {
        for (Node* t = p.head; t; t = t->next)
            insert(t->coeff, t->exp);
    }

    // Assignment operator
    Polynomial& operator=(const Polynomial& p) {
        if (this == &p)
            return *this;

        clear();

        for (Node* t = p.head; t; t = t->next)
            insert(t->coeff, t->exp);

        return *this;
    }

    // Clear linked list
    void clear() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Destructor
    ~Polynomial() {
        clear();
    }
};

int main() {
    Polynomial p1, p2, result;
    int choice;

    cout << "Enter first polynomial:\n";
    p1.input();

    cout << "\nEnter second polynomial:\n";
    p2.input();

    do {
        cout << "\n\n--- Polynomial Calculator ---\n";
        cout << "1. Display Polynomials\n";
        cout << "2. Addition\n";
        cout << "3. Subtraction (P1 - P2)\n";
        cout << "4. Multiplication\n";
        cout << "5. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "P1(x) = ";
                p1.display();

                cout << "\nP2(x) = ";
                p2.display();
                cout << '\n';
                break;

            case 2:
                result = p1.add(p2);
                cout << "Sum = ";
                result.display();
                cout << '\n';
                break;

            case 3:
                result = p1.subtract(p2);
                cout << "Difference = ";
                result.display();
                cout << '\n';
                break;

            case 4:
                result = p1.multiply(p2);
                cout << "Product = ";
                result.display();
                cout << '\n';
                break;

            case 5:
                cout << "Exiting calculator.\n";
                break;

            default:
                cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 5);

    return 0;
}
