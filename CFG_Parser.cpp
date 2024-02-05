#include <iostream>
#include <fstream>
#include<bits/stdc++.h>
#include <windows.h>  

using namespace std;
/*							******* Productivity RULES *****
	
	S --> NP VP
	
	NP --> Pronoun | Proper-Noun | Determiner Nominal
	
	Nominal --> Noun Nominal | Noun
	
	VP --> Verb | Verb NP | Verb NP PP | Verb PP
	
	PP --> Preposition NP 							*/

void setConsoleColor(WORD c) 
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
#define length_of_queue 1000
template <typename T>
class Queue{
	private:
		T *Arr;
		int capacity, L, R, queue_length;
	public:
		Queue(){
			capacity = length_of_queue;
			Arr = new T[length_of_queue];
			
			L = -1;
			R = -1;
			queue_length = 0;
		}
		Queue(int c){
			this->capacity = abs(c);
			Arr = new T[this->capacity];	
			L = -1;
			R = -1;
			queue_length = 0;
		}	
		void enQueue(T val){
			if((L == 0 && R == capacity-1) || (R == L - 1)){
				cout<<"\nQueue Is Full.\n";
			}
			else if(L == -1 && R == -1){
				L = R = 0;
				Arr[R] = val;
				queue_length++;
			}
			else if(L != 0 && R == capacity-1){
				R = 0;
				Arr[R] = val;
				queue_length++;
			}
			else{
				R++;
				Arr[R] = val;
				queue_length++;
			}
		}
		void clearQ(){
			L = R = -1;
		}
		int getSize(){
			return queue_length;
		}
		int getCapacity(){
			return capacity;
		}
		bool Q_Empty(){
			if(L == -1 && R == -1){
				return 1;
			}
			return 0;
		}
		void displaying_queue(){
			if(L < R){
				for(int i=L; i<=R; i++)
				{
					cout<<Arr[i]<<"\n";
				}
			}
			else if(R < L){
				for(int i=0; i<=R; i++){
					cout<<Arr[i]<<endl;
				}
				for(int i=L; i<capacity; i++){
					cout<<Arr[i]<<endl;
				}
			}
			else{
				if(!Q_Empty()){
					cout<<Arr[L]<<"\n";
				}
				else{
					cout<<"\nEmpty Queue\n";
				}
			}
		}
		T deQueue(){
			T val;
			if(L == -1 && R == -1){
				cout<<"\nQueue Is Empty.\n";
			}
			else if(L == capacity - 1)	{
				val = Arr[L];
				L = 0;
				queue_length--;
			}
			else if(L == R){
				val = Arr[L];
				L = R = -1;
				queue_length--;
			}
			else{
				val = Arr[L];
				L++;
				queue_length--;
			}
			
			return val;
		}	
		T peekQ(){
			if(!Q_Empty()){
				return Arr[L];
			}
		}
		bool fullQ(){
			if((L == 0 && R == capacity-1) or (R == L - 1)){
				return 1;
			}
			return 0;
		}
};
bool _prepbool=false;
string res;
string _s = "S", _vp = "VP", _nom = "NOM", _np = "NP", _pp = "PP"; // NonTerminals
string _det = "Det",  _prep = "PreP", _noun = "Noun",_pron = "ProN", _prop = "ProP", _verb = "Verb"; // Terminals

// 									...........................decalared functions ..................
int S(string input,Queue<string> &q, Queue<string> &out);
int NP(string input, Queue<string> &q, Queue<string> &out);
int PP(string input,Queue<string> &q, Queue<string> &out);
int Nominal(string input, Queue<string> &q, Queue<string> &out);
int VP(string input, Queue<string> &q, Queue<string> &out);
bool SearchingNominal(string a);
bool Searching_preposition(string a);
bool SearchingPronoun(string a);
bool SearchingProperNoun(string a);
bool Searching_Determinant(string a);
void pushWord_inQueue(string input, Queue<string> &q);

void display(string input, Queue<string> &q){
	bool inspect;
	cout<<"S\n";
	cout<<"NP VP\n";
	ifstream f1;
	f1.open("Pronouns.txt", ios::in);
	string wi=q.peekQ(),WF;
	while(f1 >> WF){
		transform(WF.begin(), WF.end(), WF.begin(), ::tolower);
		if(WF == wi){
			cout<<"Pronouns VP\n";
			_pron=WF;
			cout<<WF<<" VP\n";
			res+=_pron;
			q.deQueue();
			inspect=true;
			break;
		}
		else inspect =false;
	}
	f1.close();
	if(!inspect){
		f1.open("Proper-Nouns.txt", ios::in);
		wi=q.peekQ();
		while(f1 >> WF){
			transform(WF.begin(), WF.end(), WF.begin(), ::tolower);
			if(WF == wi){
				cout<<"Proper-Nouns VP\n";
				_prop=WF;
				res+=_prop;
				cout<<WF<<" VP\n";
				inspect=true;
				q.deQueue();
				break;
			}
			else 
			inspect =false;
		}	
		f1.close();
	}
	if(!inspect){
		f1.open("Determiners.txt", ios::in);
		wi=q.peekQ();
		while(f1 >> WF){
			transform(WF.begin(), WF.end(), WF.begin(), ::tolower);
			if(WF == wi){
				cout<<"Det Nom VP\n";
				_det=WF;
				cout<<WF<<" Nom VP\n";
				res=WF;
				inspect=true;
				q.deQueue();
				if(q.Q_Empty()){
					 break;
					}
			}
		}
				f1.close();
				if(inspect)
				while(SearchingNominal(q.peekQ())){
					cout<<res<<" Noun Nominal"<<" VP\n";
					res+= " "+ q.peekQ();
					cout<<res<<" Nominal VP\n";
					q.deQueue();
					if(q.Q_Empty())
							break;
				}
				cout<<res<<" VP\n";
	}
		f1.open("Verbs.txt", ios::in);
		 wi = q.peekQ();
		while(f1 >> WF){
			transform(WF.begin(), WF.end(), WF.begin(), ::tolower);
			if(WF == wi){
				_verb=WF;
				q.deQueue();			
				break;
			}
		}
		f1.close();
		wi = q.peekQ();
		if(SearchingPronoun(wi) || SearchingProperNoun(wi) || Searching_Determinant(wi))	{
			cout<<res<<" Verbs NP";
			if(_prepbool)
			cout<<" PP\n";
			else 
			cout<<"\n";
			res+=" "+_verb;
			cout<<res <<" NP";
			if(_prepbool)
			cout<<" PP\n";
			else cout<<"\n";
			f1.open("Pronouns.txt", ios::in);
			wi=q.peekQ();
			while(f1 >> WF){ 
			transform(WF.begin(), WF.end(), WF.begin(), ::tolower);
				if(WF == wi){
					_pron=WF;
					cout<< res<< " Pronoun ";
					res+= " "+_pron;
					if(_prepbool)
					cout<<" PP\n";
					else cout<<"\n";
					q.deQueue();
					cout<< res;
					if(_prepbool)
					cout<<" PP\n";
					else cout<<"\n";	
					inspect=true;
					break;
				}
				else inspect =false;
			}
			f1.close();
			if(!inspect){
				f1.open("Proper-Nouns.txt", ios::in);
				wi=q.peekQ();
				while(f1 >> WF){
					transform(WF.begin(), WF.end(), WF.begin(), ::tolower);
					if(WF == wi){
						_prop=WF;
						cout<< res<< " Proper_Noun ";
						res+= " "+_prop;
						if(_prepbool)
						cout<<" PP\n";
						else cout<<"\n";
						q.deQueue();
						cout<< res;
						if(_prepbool)
						cout<<" PP\n";
						else cout<<"\n";
						inspect=true;
						break;
					}
					else inspect =false;
				}	
				f1.close();
			}
			if(!inspect){
				f1.open("Determiners.txt", ios::in);
				wi=q.peekQ();
				while(f1){
					f1>> WF;
					transform(WF.begin(), WF.end(), WF.begin(), ::tolower);
					if(WF == wi){
						_det=WF;
						cout<< res<< " det Nominal";
						res+= " "+_det;
						if(_prepbool)
						cout<<" PP\n";
						else {
						cout<<endl<< res;
						}
						if(_prepbool)
						cout<<" Nominal PP\n";
						else{
						cout<<"  Nominal \n";
						inspect=true;	
						}
						q.deQueue();
					}
				}
						f1.close();
						if(inspect)
						while(SearchingNominal(q.peekQ())){
							if(!q.Q_Empty())
							cout<<res<<" Noun";
							if(_prepbool)
							cout<<" PP\n";
							else cout<<"\n";
							res+= " "+ q.peekQ();
							cout<< res;
							if(_prepbool)
							cout<<" PP\n";
							else cout<<"\n";
							q.deQueue();
							if(q.Q_Empty())
							break;
						}
			}
			if(_prepbool){
				wi=q.peekQ();
				cout<< res<< " Preposition NP\n";
				res+=" "+ wi;
				q.deQueue();
				cout<< res<<" NP\n";
			f1.open("Pronouns.txt", ios::in);
			wi=q.peekQ();
			inspect=false;
			while(f1 >> WF){
				transform(WF.begin(), WF.end(), WF.begin(), ::tolower);
				if(WF == wi){
					_pron=WF;
					cout<< res<< " Pronoun ";
					res+= " "+_pron;
					q.deQueue();
					cout<<endl<< res<<endl;
					inspect=true;
					break;
				}
				else inspect =false;
			}
			f1.close();
			if(!inspect){
				f1.open("Proper-Nouns.txt", ios::in);
				wi=q.peekQ();
				while(f1 >> WF){
					transform(WF.begin(), WF.end(), WF.begin(), ::tolower);
					if(WF == wi){
						_prop=WF;
						cout<< res<< " Proper_Noun ";
						res+= " "+_prop;
						q.deQueue();
						cout<<endl<< res<<endl;
						inspect=true;
						break;
					}
					else inspect =false;
				}	
				f1.close();
			}
			if(!inspect){
				f1.open("Determiners.txt", ios::in);
				wi=q.peekQ();
				while(f1 >> WF){
					transform(WF.begin(), WF.end(), WF.begin(), ::tolower);
					if(WF == wi){
						_det=WF;
						cout<< res<< " det Nominal ";
						res+= " "+_det;
						cout<<endl<< res<<endl;
						inspect=true;
						q.deQueue();
						if(q.Q_Empty()){
							 break;
							}
					}
				}
				f1.close();
				if(inspect)
				while(SearchingNominal(q.peekQ())){
				if(!q.Q_Empty())
							cout<<res<<" Noun Nominal\n";
							res+= " "+ q.peekQ();
							cout<< res<<endl;
							q.deQueue();
							if(q.Q_Empty())
							break;
					}
				}
			}
		}
		else{
			cout<<res<<" Verbs PP\n";
			res+=" "+_verb;
			cout<<res <<" PP\n";
			wi=q.peekQ();
			cout<< res<< " Preposition NP\n";
			res+=" "+ wi;
			q.deQueue();
			cout<< res<<" NP\n";
			f1.open("Pronouns.txt", ios::in);
			wi=q.peekQ();
			inspect=false;
			while(f1 >> WF)		{
				transform(WF.begin(), WF.end(), WF.begin(), ::tolower);
				if(WF == wi){
					_pron=WF;
					cout<< res<< " Pronoun \n";
					res+= " "+_pron;
					q.deQueue();
					cout<< res<<endl;
					inspect=true;
					break;
				}
				else inspect =false;
			}
			f1.close();
			if(!inspect){
				f1.open("Proper-Nouns.txt", ios::in);
				wi=q.peekQ();
				while(f1 >> WF){
					transform(WF.begin(), WF.end(), WF.begin(), ::tolower);
					if(WF == wi){
						_prop=WF;
						cout<< res<< " Proper_Noun \n";
						res+= " "+_prop;
						q.deQueue();
						cout<< res<<endl;
						inspect=true;
						break;
					}
					else 
					inspect =false;
				}	
				f1.close();
			}
			if(!inspect){
				f1.open("Determiners.txt", ios::in);
				wi=q.peekQ();
				while(f1 >> WF){
					transform(WF.begin(), WF.end(), WF.begin(), ::tolower);
					if(WF == wi){
						_det=WF;
						cout<< res<< " determinant Nominal \n\n";
						res+= " "+_det;
						cout<< res<<endl;
						inspect=true;
						q.deQueue();
						if(q.Q_Empty()){
							 break;
						}
					}
				}
				f1.close();
				if(inspect)
				while(SearchingNominal(q.peekQ())){
					if(!q.Q_Empty())
					cout<<res<<" Noun Nominal\n\n";
					res+= " "+ q.peekQ();
					cout<< res<<endl;
					q.deQueue();
					if(q.Q_Empty())
					break;
				}
			}
		}
}

int main(){
	system("Color 0B");

	Queue<string> q;
	Queue<string> out;	
	string input;
	
	cout<<"Enter A Sentence :: ";
	getline(cin, input);
	setConsoleColor(FOREGROUND_RED  );	
	transform(input.begin(), input.end(), input.begin(), ::tolower);
	
	if(!input.length()){
		cout<<"\n\nInvalid Structure.\n";
		return 0;
	}
	pushWord_inQueue(input, q);
	if(!S(input, q, out)){
		cout<<"\n\nInvalid Structure.\n";
	}
	else{
		pushWord_inQueue(input, q);
		display(input,q);
	}
	setConsoleColor(7);
	return 0;
}
int S(string input, Queue<string> &q, Queue<string> &out){
	//								**********************S --> NP VP**************
	if(NP(input, q, out)){	
		return VP(input, q, out);
	}
		return 0;	
}
int NP(string input, Queue<string> &q, Queue<string> &out){
//	***********************************NP --> Pronoun | Proper-Noun | Determiner Nominal******************	
	if(q.Q_Empty()){
		return 0;
	}
	ifstream f[3];
	f[0].open("Pronouns.txt", ios::in);
	f[1].open("Proper-Nouns.txt", ios::in);
	f[2].open("Determiners.txt", ios::in);
	string wi = q.peekQ() , WF;	
	while(f[0]>> WF){
		transform(WF.begin(), WF.end(), WF.begin(), ::tolower);
		if(WF == wi){
			q.deQueue();
			return 1;
		}
	}
	while(f[1] >> WF){
		transform(WF.begin(), WF.end(), WF.begin(), ::tolower);
		if(WF == wi){
			q.deQueue();
			return 1;
		}
	}
	while(f[2] >> WF){
		transform(WF.begin(), WF.end(), WF.begin(), ::tolower);
		if(WF == wi){
			q.deQueue();
			return Nominal(input, q, out);
		}
	}
}

int VP(string input, Queue<string> &q, Queue<string> &out)
{
//	************8VP --> Verb | Verb NP | Verb NP PP | Verb PP***************	
	if(q.Q_Empty()){
		return 0;
	}
	ifstream f1;
	f1.open("Verbs.txt", ios::in);
	string wi = q.peekQ() , WF;
	bool inspectV = 0;
	while(f1 >> WF){
		transform(WF.begin(), WF.end(), WF.begin(), ::tolower);
		if(WF == wi){
			q.deQueue();
			inspectV = 1;
			break;
		}
	}
	if(!inspectV){
		return 0;
	}
	// AT THIS POINT THERE IS A VERB......
	if(NP(input, q, out)){
		if (q.Q_Empty()){		
			return 1;
		}
		else{
			return  PP(input, q, out);
		}
		return 1;
	}
	else if(PP(input, q, out)){
		return 1;
	}
	return 1;
}
int PP(string input, Queue<string> &q, Queue<string> &out){
//	PP --> Preposition NP
	if(q.Q_Empty()){
		return 0;
	}
	ifstream f1;
	f1.open("Prepositions.txt", ios::in);
	string wi = q.peekQ() , WF;
	bool inspectP = 0;
	while(f1>>WF){
		transform(WF.begin(), WF.end(), WF.begin(), ::tolower);
		if(WF == wi){
			_prepbool=true;
			q.deQueue();
			inspectP = 1;
			break;
		}
	}
	if(!inspectP){
		return 0;
	}
	else{
		return NP(input, q, out);
	}
}
int Nominal(string input, Queue<string> &q, Queue<string> &out){
//	**************************************Nominal --> Noun Nominal | Noun
	if(q.Q_Empty()){
		return 0;
	}
	ifstream f1;
	f1.open("Nouns.txt", ios::in);
	string wi = q.peekQ() , WF;
	bool inspectN = 0;
	while(f1 >> WF)	{
		transform(WF.begin(), WF.end(), WF.begin(), ::tolower);
		if(WF == wi){
			_nom = wi;	
			q.deQueue();
			inspectN = 1;
			break;
		}
	}
	if(!inspectN){
		return 0;
	}
	else{
		Nominal(input, q, out);
		return 1;
	}
}
bool SearchingNominal(string a){
	ifstream f1;
	f1.open("Nouns.txt", ios::in);
	string WF;
	while(f1 >> WF){
		transform(WF.begin(), WF.end(), WF.begin(), ::tolower);
		if(WF == a){
			f1.close();
			return true;
		}
	}
	f1.close();
	return false;
}
bool SearchingPronoun(string a){
	ifstream f1;
	f1.open("Pronouns.txt", ios::in);
	string WF;
	while(f1 >> WF){
		transform(WF.begin(), WF.end(), WF.begin(), ::tolower);
		if(WF == a){
			f1.close();
			return true;
		}
	}
	f1.close();
	return false;
}
bool Searching_preposition(string a){
	ifstream f1;
	f1.open("Prepositions.txt", ios::in);
	string WF;
	while(f1 >> WF){
		transform(WF.begin(), WF.end(), WF.begin(), ::tolower);
		if(WF == a){
			f1.close();
			return true;
		}
	}
	f1.close();
	return false;
}
bool SearchingProperNoun(string a){
	ifstream f1;
	f1.open("Proper-Nouns.txt", ios::in);
	string WF;
	while(f1 >> WF){
		transform(WF.begin(), WF.end(), WF.begin(), ::tolower);
		if(WF == a){
			f1.close();
			return true;
		}
	}
	f1.close();
	return false;
}
bool Searching_Determinant(string a){
	ifstream f1;
	f1.open("Determiners.txt", ios::in);
	string WF;
	while(f1 >> WF){
		transform(WF.begin(), WF.end(), WF.begin(), ::tolower);
		if(WF == a){
			f1.close();
			return true;
		}
	}
	f1.close();
	return false;
}
void pushWord_inQueue(string input, Queue<string> &q){
	int i = 0;
	string words;
	while(i != input.length()){
		if(input[i] == '.' || input[i] == '!' ||input[i] == ' ' ||  input[i] == '?' || input[i]=='\n'){
			q.enQueue(words);
			words.clear();
		}
		else{
			words = words + input[i];
		}
		i++;
	}
	q.enQueue(words);
}
