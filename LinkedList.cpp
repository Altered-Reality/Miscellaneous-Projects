
#include <iostream>
#include <string>
#include <vector>

#include <stdexcept>
using namespace std;

template<typename T>
class Node {

    public:
        // node data
        T data;

        // node linking
        Node* next;
        Node* prev;

        Node(const T& info) {

            next = nullptr;
            prev = nullptr;

            data = info;
        }
};

template<typename T>
class DoublyCircularLinkedList {

    Node<T>* head;
    Node<T>* tail;

    int size;
    Node<T>* nodeAt(int i) const {

        if(i<0||i>=size) return nullptr;

        Node<T>* p = head;

        if(i <= size/2){
            for(int k=0;k<i;++k) p=p->next;
        } 
        
        else {
            p = tail;
            for(int k=size-1;k>i;--k) p=p->prev;
        }
        
        return p;
    }

public:

    DoublyCircularLinkedList() {

        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    ~DoublyCircularLinkedList(){ 

        for (int i = 0; i < size; i++) {
            pop_front();
        }


    }

    bool isEmpty() const {

         return size == 0;
    }

    int getSize() const { 
        return size; 
    }

    T front() const { 
        return head->data; 
    }

    T back() const { 
        return tail->data; 
    }

    void push_front(const T& x){

        Node<T>* n=new Node<T>(x);

        if(size==0){ 
            head=tail=n; n->next=n->prev=n; 
        }
        else { 
            n->next=head; n->prev=tail; head->prev=n; tail->next=n; head=n; 
        }
        ++size;
    }

    void push_back(const T& x){
        Node<T>* n=new Node<T>(x);
        if(size==0){ 
            head=tail=n; n->next=n->prev=n; 
        }
        else { 
            n->prev=tail; n->next=head; tail->next=n; head->prev=n; tail=n; 
        }

        ++size;
    }
    
    void insertAt(int index,const T& x){

        if(index<0||index>size) throw runtime_error("out of bounds");

        if(index==0){ push_front(x); return; }
        if(index==size){ push_back(x); return; }

        Node<T>* after = nodeAt(index);
        Node<T>* before = after->prev;
        Node<T>* n=new Node<T>(x);

        n->next=after; n->prev=before; before->next=n; after->prev=n;
        ++size;
    }

    void pop_front(){

        if(size==0) return;
        if(size==1){ 
            delete head; head=tail=nullptr; size=0; return;
        }

        Node<T>* old=head;

        head=head->next;
        head->prev=tail;
        tail->next=head;

        delete old;
        --size;
    }

    void pop_back(){
        if(size==0) return;
        if(size==1){ 
            delete tail; head=tail=nullptr; size=0; return; 
        }

        Node<T>* old=tail;

        tail=tail->prev;
        tail->next=head;
        head->prev=tail;

        delete old;
        --size;
    }

    void removeAt(int index
    ){

        if(index
            <0||index
            >=size) throw runtime_error("out of bounds");

        if(index
            ==0){ pop_front(); return; }
        if(index
            ==size-1){ pop_back(); return; }

        Node<T>* cur=nodeAt(index
        );
        Node<T>* a=cur->prev; 
        Node<T>* b=cur->next;

        a->next=b; b->prev=a;

        delete cur; 
        --size;
    }

    T getAt(int index
    ) const { 
        Node<T>* n=nodeAt(index
        ); 

        return n->data; 
    }

    void setAt(int index
        ,const T& x){ 

        Node<T>* n=nodeAt(index
        );
        n->data = x; 
    }

    int indexOf(const T& x) const {
        Node<T>* p=head;

        for(int i=0;i<size;++i){

            if(p->data==x) {
                return i;
            }

            p=p->next;
        }

        return -1;
    }

    void printForward(int index) const {

        if(size==0){ 
            cout<<"\n"; 
            return; 
        }

        Node<T>* p = nodeAt(index);
        for(int i=0;i<size;++i) { 
            cout<<p->data; 
            if(i+1<size) cout<<" "; 
            p=p->next; 
        }

        cout<<"\n";
    }

    void printBackward(int index) const {

        if(size==0){ 
            cout<<"\n";
             return; 
        }

        Node<T>* p = nodeAt(index);
        for(int i=0;i<size;++i){ 
            cout<<p->data; 
            if(i+1<size) cout<<" "; 
            p=p->prev; }
            
        cout<<"\n";
    }

    // Traversal printing using a provided print function
    template<typename PrintFunc>
    void traverseForwardFrom(int index, PrintFunc printer) const {
        if (size == 0) return;
        Node<T>* p = nodeAt(index);
        for (int i = 0; i < size; ++i) {
            printer(p->data);
            p = p->next;
        }
    }

    template<typename PrintFunc>
    void traverseBackwardFrom(int index, PrintFunc printer) const {
        if (size == 0) return;
        Node<T>* p = nodeAt(index);
        for (int i = 0; i < size; ++i) {
            printer(p->data);
            p = p->prev;
        }
    }

};


// Helper functions specific to Contact and the list

struct Contact {
    string name;
    string phone;
};

bool operator == (const Contact& a, const Contact& b) {
    return a.name == b.name && a.phone == b.phone;
}


// Compare contacts by phone (phone assumed unique)
bool samePhone(const Contact& a, const string& phone) {
    return a.phone == phone;
}

// Compare contacts by name
bool sameName(const Contact& a, const string& name) {
    return a.name == name;
}

// Find index of first contact with given phone, or -1
int findIndexByPhone(const DoublyCircularLinkedList<Contact>& list, const string& phone) {
    int n = list.getSize();
    for (int i = 0; i < n; ++i) {
        Contact c = list.getAt(i);
        if (samePhone(c, phone)) return i;
    }
    return -1;
}

// Collect indices of contacts with given name
void findAllIndicesByName(const DoublyCircularLinkedList<Contact>& list, const string& name, vector<int>& out) {
    out.clear();
    int n = list.getSize();
    for (int i = 0; i < n; ++i) {
        Contact c = list.getAt(i);
        if (sameName(c, name)) out.push_back(i);
    }
}

// Print a contact in the required format
void printContact(const Contact& c) {
    cout << "Name: " << c.name << " Phone: " << c.phone << "\n";
}


int main() {
    DoublyCircularLinkedList<Contact> contacts;
    while (true) {
        cout << "\nContact Manager Menu\n";
        cout << "1. Insert a new person (name, phone)\n";
        cout << "2. Delete a person by name or phone\n";
        cout << "3. Search by name or phone\n";
        cout << "4. Display all people (start phone and direction)\n";
        cout << "5. Size\n";
        cout << "6. Quit\n";
        cout << "Choose an option: ";
        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            string dummy;
            getline(cin, dummy);
            cout << "Invalid input. Try again.\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1) {
            Contact c;
            cout << "Enter name: ";
            getline(cin, c.name);
            cout << "Enter phone: ";
            getline(cin, c.phone);
            // Insert at back
            contacts.push_back(c);
            cout << "Inserted.\n";
        }
        else if (choice == 2) {
            cout << "Delete by Name or Phone? ";
            char opt; cin >> opt; cin.ignore();
            if (opt == 'N' || opt == 'n') {
                cout << "Enter name to delete (all matches will be removed): ";
                string name; getline(cin, name);
                vector<int> indexes
                ;
                findAllIndicesByName(contacts, name, indexes
                );
                if (indexes
                    .empty()) {
                    cout << "No entries with that name.\n";
                } else {
                    // Remove from highest index to lowest to keep indices valid
                    for (int i = (int)indexes
                    .size() - 1; i >= 0; --i) {
                        contacts.removeAt(indexes
                            [i]);
                    }
                    cout << "Deleted " << indexes
                    .size() << " entries.\n";
                }
            } else {
                cout << "Enter phone to delete: ";
                string phone; getline(cin, phone);
                int index
                 = findIndexByPhone(contacts, phone);
                if (index
                     == -1) {
                    cout << "No entry with that phone.\n";
                } else {
                    contacts.removeAt(index
                    );
                    cout << "Deleted entry with phone " << phone << ".\n";
                }
            }
        }
        else if (choice == 3) {
            cout << "Search by (N)ame or (P)hone? ";
            char opt; cin >> opt; cin.ignore();
            if (opt == 'N' || opt == 'n') {
                cout << "Enter name to search: ";
                string name; getline(cin, name);
                vector<int> indexes
                ;
                findAllIndicesByName(contacts, name, indexes
                );
                if (indexes
                    .empty()) {
                    cout << "No matches.\n";
                } else {
                    cout << "Matches:\n";
                    for (int index
                         : indexes
                        ) printContact(contacts.getAt(index
                    ));
                }
            } else {
                cout << "Enter phone to search: ";
                string phone; getline(cin, phone);
                int index
                 = findIndexByPhone(contacts, phone);
                if (index
                     == -1) {
                    cout << "No match.\n";
                } else {
                    cout << "Found:\n";
                    printContact(contacts.getAt(index
                    ));
                }
            }
        }
        else if (choice == 4) {
            if (contacts.isEmpty()) {
                cout << "List is empty.\n";
                continue;
            }
            cout << "Enter starting phone number: ";
            string startPhone; getline(cin, startPhone);
            int startIdx = findIndexByPhone(contacts, startPhone);
            if (startIdx == -1) {
                cout << "Starting phone not found. Starting from head.\n";
                startIdx = 0;
            }
            cout << "Traverse (F)orward or (B)ackward? ";
            char dir; cin >> dir; cin.ignore();
            if (dir == 'B' || dir == 'b') {
                contacts.traverseBackwardFrom(startIdx, [](const Contact& c){ printContact(c); });
            } else {
                contacts.traverseForwardFrom(startIdx, [](const Contact& c){ printContact(c); });
            }
        }
        else if (choice == 5) {
            cout << "Size: " << contacts.getSize() << "\n";
        }
        else if (choice == 6) {
            cout << "Quitting.\n";
            break;
        }
        else {
            cout << "Unknown option. Try again.\n";
        }
    

    // return 0;
}
}