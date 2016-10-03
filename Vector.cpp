#include <iostream>

using namespace std;

template <class T>
class vector{
private:
	int size,max;
   	T *items;
	void expand();
public:
	vector();
	vector(const vector<T>&);
	~vector();
	int getSize();
	T at(int);
	T& operator[](int);
	bool insert(T,int);
	bool remove(int);

};

void removeDuplicates(vector<int>&);
bool isSortedIncreasing(vector<int>);
void removeDuplicates(vector<string>&);

bool isSortedIncreasing(vector<string>);
    
template <class T>
void display(vector<T>);

void removeDuplicates(vector<int>& a){
	for(int i=0; i<a.getSize()-1; i++){
		for(int j=i+1; j<a.getSize();){
			if(a[i]==a[j])
				a.remove(j);
			else
				j++;
		}
	}
}

bool isSortedIncreasing(vector<int> v){
    for (int i = 0; i < v.getSize() - 1; i++){
        if (v[i] > v[i + 1]){
            return false;
        }
    }
    if(v[0] == v[v.getSize() - 1]){
        return false;
    } else {
        return true;
    }
    
}

void removeDuplicates(vector<string>& a){
	for(int i=0; i<a.getSize()-1; i++){
		for(int j=i+1; j<a.getSize();){
			if(a[i].compare(a[j]) == 0)
				a.remove(j);
			else
				j++;
		}
	}
}

bool isSortedIncreasing(vector<string> v){
    for (int i = 0; i < v.getSize() - 1; i++){
        if (v[i].compare(v[i + 1]) < 0) {
            return false;
        }
    }
    if(v[0].compare(v[v.getSize() - 1]) == 0){
        return false;
    } else {
        return true;
    }
}

template <class T>
void display(vector<T> a){
	for(int i=0; i<a.getSize();i++)
		cout<<a[i]<<" ";	
	cout<<endl;
}

template <class T>
vector<T>::vector(){
	size = 0;
	max = 5;
	items = new T[max];
}
 
template <class T>
vector<T>::vector(const vector<T>& v){
	size = v.size;
	max = v.max;
	items = new T[max];

    copy(v.items,v.items+size,items);
}

template <class T>
vector<T>::~vector(){
	delete[] items;
}

template <class T>
void vector<T>::expand(){
	T *copy = new T[size];
	for(int i=0; i<size; i++)
		copy[i] = items[i];
	delete[] items;
	max = max + 5;
	items = new T[max];
	for(int i=0; i<size; i++)
		items[i] = copy[i];
	delete[]copy;
}

template <class T>
int vector<T>::getSize(){
	return size;
}

template <class T>
T vector<T>::at(int i){
	return items[i];	
}

template <class T>
T& vector<T>::operator[](int i){
	return items[i];	
}

template <class T>
bool vector<T>::insert(T x, int p){
	if(p < 0 || p>size) 
		return false;
	else
	if(size == max)
		expand();
	
	for(int i=size;i>p;i--)
		items[i] = items[i-1];
	items[p] = x;
	size++;
	return true;	
}

template <class T>
bool vector<T>::remove(int p){
	if(p < 0 || p > size)
		return false;
	else{		
		for(int i=p;i<size-1;i++)
			items[i] = items[i+1];
		size--;
		return true;
	}
}

template <class T>
ostream& operator<<(ostream& out, vector<T> v){
    for (int i = 0; i < v.getSize(); i++){
        out << v[i] << " ";
    }
    return out;
}
int main() {
    int n, num;
    string word;
    cin >> n;
    
    for (int i = 0; i < n; i++){
        cin >> num;
        if (num == 1){
            vector<int> v;
            for (int j = 0; j < 10; j++){
                cin >> num;
                v.insert(num, j);
            }
            if (isSortedIncreasing(v)){
                cout << "YES"<< endl;
            } else {
                cout << "NO" << endl;
            }
            removeDuplicates(v);
            cout<< v << endl;      
        } else {
            vector<string> v;
            for (int j = 0; j < 10; j++){
                cin >> word;
                v.insert(word, j);
            }
            if (isSortedIncreasing(v)){
                cout << "YES"<< endl;
            } else {
                cout << "NO" << endl;
            }
            removeDuplicates(v);
            cout<< v << endl;        
        }
    }
    return 0;
}
