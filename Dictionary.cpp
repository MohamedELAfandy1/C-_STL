#include<iostream>
using namespace std;

template<class Tkey, class Tvalue>
class Dictionary{
	class KeyValuePair{
	 	Tkey key;
	 	Tvalue value;
	 	public:
		KeyValuePair() : key(), value() {} 
	 	KeyValuePair(Tkey _key, Tvalue _value): key(_key),value(_value){}
	 	
	 	Tkey getKey() const {return key;}
	 	Tvalue getValue() const {return value;}
	 	void setValue(Tvalue newVal) {value=newVal;}
	};
	
	KeyValuePair* enteries;
 	int initialSize;
 	int length;
 	public:
 	Dictionary(int _initialSize=3){
  		enteries = new KeyValuePair[_initialSize];
		initialSize=_initialSize; 
		length=0;
			
	}
	~Dictionary(){
		delete[] enteries;
	}
//	if(length + 1 == initialSize)	resize();
	void resize(){
		int newSize = initialSize+length;
		cout<<"[RESIZE]==>	Resized From "<<initialSize<<" to "<<newSize<<endl;
		KeyValuePair* newArr = new KeyValuePair[newSize];
		for(int i=0 ; i<length ; i++){
			newArr[i] = enteries[i];	
		}
		delete[] enteries;
		initialSize = newSize;
		enteries = newArr;
	}
	
	
	int getSize() {
		return length;
	}
	
	
	void set(Tkey _key, Tvalue _value){
		for(int i=0 ; i<length ; i++){
			if(enteries[i].getKey() == _key){
				enteries[i].setValue(_value);
				return;
			}
		}
		
		KeyValuePair newPair= KeyValuePair (_key,_value);
		if(length == initialSize ){
			resize();
		}
		enteries[length] = newPair;
		++length;
	}
	
	Tvalue get(Tkey _key){
		for(int i=0 ; i<length ; i++){
			if(enteries[i].getKey() == _key){
				return enteries[i].getValue();
				
			}
		}
		return Tvalue();
		
	}
	
	void remove(Tkey _key){
		for(int i=0 ; i<length ; i++){
			if(enteries[i].getKey() == _key){
				enteries[i]=enteries[length-1];
//				delete enteries[length-1];
				--length;
				return;
				
			}
		}
	}	
	
	bool isEmpty()	{
		return length<=0;
	
	}
	
	void print(){
		if(isEmpty()) {
			cout<<"Dictionary Is Empty\n";
			return;
		}
		
		for(int i=0 ; i<length ; i++){
			cout<<i+1<<"  => "<<enteries[i].getKey()<<"  "<<enteries[i].getValue()<<endl;
		}
	}
 };


int main() {
  
  Dictionary<string, string> dic;
  dic.print();

    dic.set("Mohamed", "Mohamed@gmail.com");
    dic.set("Ali", "Ali@gmail.com");
    dic.print();
 	cout<<"Size "<<dic.getSize()<<endl;
	
	dic.set("Mohamed", "Mohamed@gmail.com");
	dic.set("Ali", "Ali2@gmail.com");
	dic.set("Ahmed", "Mohamed@gmail.com");
    dic.set("Amr", "Ali@gmail.com");
    
	dic.print();
	cout<<"Size "<<dic.getSize()<<endl; 
 
  cout << dic.get("Mohamed") << endl;

  dic.remove("Ali");
  dic.print();
	cout<<"Size "<<dic.getSize()<<endl; 

  return 0;
  }

