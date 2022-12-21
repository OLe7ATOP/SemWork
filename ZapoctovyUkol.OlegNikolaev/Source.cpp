#include<iostream>
#include<string>
#include<fstream>

using namespace std;

using T = int;
const T Null = T{};

struct item {
	string model;
	T year;
	string color;
	item *next;
};

struct linkedlist {
	item* head;
	item* tail;
};

void listcreate(linkedlist& cl) {
	cl.head = cl.tail = new item{"", Null, "", nullptr};
}

void addtobegin(linkedlist& cl) {
	char x = 'y';
	while (x != 'n') {
		cout << endl << "Enter a model" << endl;
		string m;
		cin >> m;
		cout << "Enter a year" << endl;
		int y;
		cin >> y;
		cout << "Enter a color" << endl;
		string c;
		cin >> c;
		cl.head = new item{ m, y, c, cl.head };
		cout << "Do you want to add one more car? \n y/n:  ";
		cin >> x;
	}
}

void addtoend(linkedlist& cl) {
	char x = 'y';
	while (x != 'n') {
		cout << endl << "Enter a model" << endl;
		string m;
		cin >> m;
		cout << "Enter a year" << endl;
		int y;
		cin >> y;
		cout << "Enter a color" << endl;
		string c;
		cin >> c;
		cl.tail->model = m;
		cl.tail->color = c;
		cl.tail->year = y;
		cl.tail->next = new item{ "", Null, "", nullptr };
		cl.tail = cl.tail->next;
		cout << "Do you want to add one more car? \n y/n:  ";
		cin >> x;
	}
}

void listprint(linkedlist& cl) {
	int x = 0;
	item* hlp;
	for (hlp = cl.head; hlp != cl.tail; hlp = hlp->next) {
		x++;
		cout << x <<")  " << hlp->model << " " << hlp->year << " " << hlp->color << endl;
	}
}



void listinput(linkedlist& cl, string filestr) {
	ifstream fin;
	fin.open("Cars_from_FaF3.txt");
	if (!fin.is_open()) {
		cout << "File Open Err_";
		return;
	}
	string mod;
	int year;
	string color;
	while (fin >> mod) {
		
		fin >> year;
		fin >> color;
		cl.tail->model = mod;
		cl.tail->color = color;
		cl.tail->year = year;
		cl.tail->next = new item{ "", Null, "", nullptr };
		cl.tail = cl.tail->next;
	}
}


int carcount(linkedlist& cl) {
	int x=0;
	for (item* hlp = cl.head; hlp != cl.tail; hlp = hlp->next) {
		x++;
	}
	return x;
}

void cardelete(linkedlist& cl, int del) {
	item* hlp;
	int count = 1;
	for (hlp = cl.head; hlp != cl.tail; hlp = hlp->next) {
		if (count == del - 1) break;
		count++;
	}
	
	if (del == 1) {
		cl.head = cl.head->next;
		return;
	}
	if (del == carcount(cl)) {
		hlp->model = "";
		hlp->year = Null;
		hlp->color = "";
		hlp->next = nullptr;
		item* pom=cl.tail;
		cl.tail = hlp;
		delete pom;
		return;
	}
	

	item* trash=hlp->next;
	hlp->next = hlp->next->next;
	delete trash;
	
}

void carfind(linkedlist& cl, string mod) {
	auto hlp = cl.head;
	for (hlp; hlp != cl.tail; hlp = hlp->next) {
		if (hlp->model == mod) {
			cout << hlp->model << " " << hlp->year << " " << hlp->color << endl;
			return;
		}
	}
	cout << "List doesn't include " << mod << endl;
}

void clearlist(linkedlist& cl) {
	while (cl.head != cl.tail) {
		cl.head = cl.head->next;
	}
}

void changessave(linkedlist& cl, string fileoutput) {
	ofstream fout;
	fout.open(fileoutput);
	if (!fout.is_open()) {
		cout << "File access failed\n ERR_" << endl;
		return;
	}
	fout << "-----------------" << endl;
	for (item* hlp = cl.head; hlp != cl.tail; hlp = hlp->next) {
		fout << hlp->model << " " << hlp->year << " " << hlp->color << endl;
	}
	fout << "-------------------" << endl;
	cout << "--------DONE----------" << endl;

}


int main() {
	linkedlist cl; //cars list
	listcreate(cl);
	
	cout << "--------------------" << endl;
	listinput(cl, "Cars_from_FaF3.txt");
	cout << "--------------------" << endl;
	string i = "y";
	cout << "Functions of Programm:\n sl - show list of cars;\n find - to find car by its model\n addtt - add new car to the top;\n addtb - add new car to the bottom;\n del - delete some car;\n sc - save changes;\n dc - delete changes;\n q -quit programm;\n h - for show commands;" << endl;
	while (i != "q") {
		cout << "Command:  ";
		cin >> i;
		if (i == "sl") {
			listprint(cl);
			continue;
		}
		if (i == "addtt") {
			cout << "-----------------------------------" << endl;
			cout << "How to add\n 1) Model - if you need to place 'SPACE', put '_';\n 2)Year - Number;\n 3)Color - if you have two or more colors. put '_' as 'SPACE';" << endl;
			cout << "-----------------------------------" << endl;
			addtobegin(cl);
			continue;
		}
		if (i == "addtb") {
			cout << "-----------------------------------" << endl;
			cout << "How to add\n 1) Model - if you need to place 'SPACE', put '_';\n 2)Year - Number;\n 3)Color - if you have two or more colors. put '_' as 'SPACE';" << endl;
			cout << "-----------------------------------" << endl;
			addtoend(cl);
			continue;
		}
		if (i == "del") {
			int del;
			cout << "Enter a position of car to delete:   ";
			cin >> del;
			cardelete(cl, del);
			continue;
		}
		if (i == "find") {
			string xx;
			cout << "Enter model of car, that you want to find:  ";
			cin >> xx;
			carfind(cl, xx);
		}
		if (i == "dc") {
			clearlist(cl);
			listinput(cl, "Cars_from_FaF3.txt");
			continue;
		}
		if (i == "sc") {
			changessave(cl, "output.txt");
		}
		if (i == "h") {
			cout << "-----------------------------------" << endl;
			cout << "Functions of Programm:\n sl - show list of cars;\n find - to find car by its model\n addtt - add new car to the top;\n addtb - add new car to the bottom;\n del - delete some car;\n sc - save changes;\n dc - delete changes;\n q -quit programm;\n h - for show commands;" << endl;
			cout << "-----------------------------------" << endl;
			continue;
		
		}
	}
}