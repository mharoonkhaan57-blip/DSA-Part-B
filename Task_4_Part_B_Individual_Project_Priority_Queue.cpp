/*
  Name: M.Haroon-Ur-Rasheed Khan   Reg. No: Ai-9
  Subject: DSA                    Section: A
  Lab 04 - Part B: Priority Queue in Library Management System

  Situation: Book reservation requests have different urgency levels.
  Priority 1 = exam, Priority 2 = assignment/project, Priority 3 = normal.
  The request with the smallest priority number must be served first.
*/

#include <iostream>
#include <string>
using namespace std;

struct ReservationNode {
    int memberID, priority;
    string memberName, bookTitle;
    ReservationNode* next;
    ReservationNode(int id, string name, string book, int p)
        : memberID(id), priority(p), memberName(name),
          bookTitle(book), next(nullptr) {}
};

class ReservationQueue {
    ReservationNode* front;
    ReservationNode* rear;
    int count;

    void clear() { while (front) delete Remove(); count = 0; }
    void copyFrom(const ReservationQueue& q) {
        for (ReservationNode* p = q.front; p; p = p->next)
            Add(new ReservationNode(p->memberID, p->memberName,
                                    p->bookTitle, p->priority));
    }

public:
    ReservationQueue() : front(nullptr), rear(nullptr), count(0) {}
    ReservationQueue(const ReservationQueue& q)
        : front(nullptr), rear(nullptr), count(0) { copyFrom(q); }

    ReservationQueue& operator=(const ReservationQueue& q) {
        if (this != &q) { clear(); copyFrom(q); }
        return *this;
    }

    ~ReservationQueue() { clear(); }

    void Add(ReservationNode* request) {
        if (!request) return;
        request->next = nullptr;
        if (!front) front = rear = request;
        else if (request->priority < front->priority) {
            request->next = front; front = request;
        }
        else {
            ReservationNode* p = front;
            while (p->next && p->next->priority <= request->priority)
                p = p->next;
            request->next = p->next; p->next = request;
            if (!request->next) rear = request;
        }
        ++count;
    }

    ReservationNode* Remove() {
        if (IsEmpty()) return nullptr;
        ReservationNode* p = front;
        front = front->next;
        if (!front) rear = nullptr;
        p->next = nullptr; --count;
        return p;
    }

    bool IsEmpty() const { return front == nullptr; }
    bool IsNotEmpty() const { return front != nullptr; }

    void PrintQueue() const {
        cout << "\nReservations (Priority Order):\n";
        for (ReservationNode* p = front; p; p = p->next)
            cout << p->memberID << " | " << p->memberName
                 << " | " << p->bookTitle
                 << " | Priority: " << p->priority << '\n';
        cout << "Total: " << count << '\n';
    }
};

int main() {
    ReservationQueue reservations;
    cout << "LIBRARY MANAGEMENT - PRIORITY RESERVATIONS\n";

    reservations.Add(new ReservationNode(101, "Ali", "Database Systems", 3));
    reservations.Add(new ReservationNode(102, "Sara", "Operating Systems", 1));
    reservations.Add(new ReservationNode(103, "Ahmed", "Artificial Intelligence", 2));
    reservations.Add(new ReservationNode(104, "Bilal", "Computer Networks", 1));
    reservations.PrintQueue();

    ReservationNode* served = reservations.Remove();
    if (served) {
        cout << "\nProcessed first: " << served->memberName
             << " - " << served->bookTitle
             << " (Priority " << served->priority << ")\n";
        delete served;
    }

    cout << "IsEmpty: " << (reservations.IsEmpty() ? "Yes" : "No") << '\n';
    cout << "IsNotEmpty: " << (reservations.IsNotEmpty() ? "Yes" : "No") << '\n';

    ReservationQueue copy(reservations);       
    ReservationQueue assigned; assigned = reservations; 
    cout << "\nCopied queue:"; copy.PrintQueue();
    cout << "\nAssigned queue:"; assigned.PrintQueue();
    return 0;
}
