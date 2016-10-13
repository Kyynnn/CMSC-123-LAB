#include <iostream>

using namespace std;
template <class T>
class node {
    public:
        T item;
        node<T> *next, *prev;
        node();
        node(T);
};

template <class T>
node<T>::node() {

}

template <class T>
node<T>::node(T n) {
    item = n;
    next = prev = NULL;
}

template <class T>
class list {
    public:
        struct iterator {
            node<T> the_node;
            node<T>* pointer;
            iterator& operator++(int){pointer = pointer->next; return (*this);}
            T operator*(){return pointer->item;}
            bool operator!=(const iterator& it){return pointer!=it.pointer;}
        };
    private:
        int size;
        node<T> *head,*tail;
        iterator iter;
    public:
        list();
        list(const list&);
        ~list();
        bool insert(T,int);
        bool remove(int);
        T get(int);
        void set(T, int);
        int getSize(){return size;}
        iterator begin(){iter.pointer = head; return iter;}
        iterator end(){iter.pointer = tail->next; return iter;} 
};

template <class T>
list<T>::list() {
    size = 0;
    head = NULL;
    tail = NULL;
}

template <class T>
list<T>::list(const list& l) {
    size = 0;
    head = NULL;
    tail = NULL;
    node<T> *tmp = l.head;
    for (int i = 0; i < l.size; i++) {
        insert(tmp->item, i);
        tmp = tmp->next;
    }
}

template <class T>
list<T>::~list() {
    while (size != 0) {
        remove(0);
    }
}

template <class T>
bool list<T>::insert(T val, int i) {
    if (i >= 0 && i <= size) {
        node<T> *nodeNew = new node<T>(val);
        if (head == NULL && tail == NULL) { 
            head = nodeNew;
            tail = nodeNew;
        } else if (i == 0) {
            head->prev = nodeNew;
            nodeNew->prev = NULL;
            nodeNew->next = head;
            head = nodeNew;
        } else if (i == size) {
            nodeNew->prev = tail;
            tail->next = nodeNew;
            tail = nodeNew;
        } else {
            node<T> *tmp = head;
            for (int j = 0; j < i - 1; j++) {
                tmp = tmp->next;
            }
            nodeNew->next = tmp->next;
            nodeNew->prev = tmp;
            tmp->next->prev = nodeNew;
            tmp->next = nodeNew;
        }
        size++;
        return true;
    }
    return false;
}

template <class T>
bool list<T>::remove(int i) {
    if (i < size && size != 0 && i >= 0) {
        if (i == 0) {
            if (size == 1) {
                node<T> *nodeDel = head;
                head = tail = NULL;           
                delete nodeDel;
            } else {
                node<T> *nodeDel = head;
                head = head->next;
                head->prev = NULL;
                nodeDel->next = NULL;
                delete nodeDel;
            }
        } else if (i == size - 1) {
            node<T> *nodeDel = tail;
            tail = nodeDel->prev;
            tail->next = NULL;
            nodeDel->prev = NULL;
            delete nodeDel;             
        } else {
            if (i <= (size - 1) / 2){
                node<T> *tmp = head;
                for(int j = 0; j < i - 1; j++) {
                    tmp = tmp->next;
                }
                node<T> *nodeDel = tmp->next;
                tmp->next = nodeDel->next;
                nodeDel->next->prev = tmp;
                nodeDel->next = nodeDel->prev = NULL;
                delete nodeDel;  
            } else {
                node<T> *tmp = tail;
                for(int j = size - 1; j > i + 1; j--) {
                    tmp = tmp->prev;
                }
                node<T> *nodeDel = tmp->prev;
                tmp->prev = nodeDel->prev;
                nodeDel->prev->next = tmp;
                nodeDel->next = nodeDel->prev = NULL;
                delete nodeDel; 
            }       
        }   
        size--;
        return true;
    }
    return false;
}

template <class T>
T list<T>::get(int i) {
    if (i >= 0 && i < size) {
        node<T> *tmp;
        if (i <= (size - 1) / 2){
            tmp = head;
            for (int j = 0; j < i; j++) {
                tmp = tmp->next;
            }
        } else {
            tmp = tail;
            for (int j = size - 1; j > i; j--) {
                tmp = tmp->prev;
            }
        }
        return tmp->item;
    } else {
        throw 401;
    }
}

template <class T>
void list<T>::set(T x, int i) {
    if (i >= 0 && i < size) {
        node<T> *tmp;
        if (i <= (size - 1) / 2) {
            tmp = head;
            for (int j = 0; j < i; j++) {
                tmp = tmp->next;
            }
        } else {
            tmp = tail;
            for (int j = size - 1; j > i; j--) {
                tmp = tmp->prev;
            }
        }
        tmp->item = x;
    } else {
        throw 401;
    }
}

void display(list<int> l) {
    if (l.getSize() != 0) {
        for (list<int>::iterator i = l.begin(); i !=l.end(); i++){
            cout << *i << " ";
        }
    }
    cout << endl;
}


int main() {
    int cases, indx, type, val;
    cin >> cases;
    list<int> l;
    for (int i = 0; i < cases; i++) {
        cin >> type;
        if (type == 1) { 
            cin >> indx;
            cin >> val;
            l.insert(val, indx);          
            display(l); 
        } else if (type == 2) {
            cin >> indx;
            l.remove(indx);
            display(l);
        } else if (type == 3) {
            try{
                cin >> indx;
                cout << l.get(indx) << endl;
            } catch(int err) {
                if (err == 401) { 
                    cout << "POSITION OUT OF BOUNDS" << endl; 
                }
            }
        } else {
            try {
                cin >> indx;
                cin >> val;
                l.set(val, indx);
                display(l);
            } catch (int err) {
                if (err == 401) { 
                    cout << "POSITION OUT OF BOUNDS" << endl; 
                }
            }
        }
    }
    return 0;
}
