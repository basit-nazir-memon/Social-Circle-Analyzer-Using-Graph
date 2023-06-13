#include <iostream>
#include <fstream>
#include <string>
using namespace std;


class node {
public:
	int data;
	node* next;
};

class list {
public:
	node* head;
	list* next;
	bool visited;
	list() {
		head = NULL;
		next = NULL;
		visited = false;
	}
	void insert(int data) {
		node* newNode = new node;
		newNode->data = data;
		newNode->next = NULL;

		if (!head) {
			head = newNode;
			return;
		}

		node* temp = head;
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = newNode;
		return;
	}
};

class table {
public:
	list* head;
	table() {
		head = NULL;
	}

	void createList(int data) {
		list* newList = new list;
		newList->insert(data);
		if (!head) {
			head = newList;
			return;
		}
		list* temp = head;
		bool flag = true;
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = newList;
		return;
	}

	void createList() {
		list* newList = new list;
		if (!head) {
			head = newList;
			return;
		}
		list* temp = head;
		bool flag = true;
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = new list;
		temp->next = newList;
		return;
	}
};

class queue {
	node* head;
	node* tail;
	int size;
public:
	queue() {
		head = NULL;
		tail = NULL;
		size = 0;
	}

	bool haveCommonNode(queue& q) {
		node* temp1 = q.head;
		node* temp2 = head;
		for (int i = 0; i < q.size; i++) {
			temp2 = head;
			for (int j = 0; j < size; j++) {
				if (temp1->data == temp2->data) {
					return true;
				}
				temp2 = temp2->next;
			}
			temp1 = temp1->next;
		}
		return false;
	}

	bool contains(int data) {
		node* temp = head;
		while (temp) {
			if (temp->data == data) {
				return true;
			}
			temp = temp->next;
		}
		return false;
	}

	queue findCommon(queue& q2) {
		queue q3;
		node* temp1 = head, *temp2;
		for (int i = 0; i < Size(); i++) {
			temp2 = q2.head;
			for (int j = 0; j < q2.Size(); j++) {
				if (temp1->data == temp2->data) {
					q3.enqueue(temp1->data);
					break;
				}
			}
			temp1 = temp1->next;
		}
		return q3;
	}

	void enqueue(int data) {
		node* temp = head;
		while (temp) {
			if (temp->data == data) {
				return;
			}
			temp = temp->next;
		}
		node* newNode = new node;
		newNode->data = data;
		newNode->next = NULL;
		if (!tail) {
			tail = newNode;
			head = tail;
			return;
		}
		tail->next = newNode;
		tail = tail->next;
		size++;
	}

	int dequeue() {
		if (!head) {
			cout << "No data in Queue\n";
			return -1;
		}
		int data = head->data;
		node* temp = head;
		head = head->next;
		delete temp;
		size--;
		return data;
	}

	void print() {
		node* temp = head;
		while (temp) {
			cout << temp->data << ", ";
			temp = temp->next;
		}
	}

	int Size() { return size; }
};

class graph {
	list* friends;
	int nodes;
public:
	graph() {
		nodes = 0;
		friends = new list[500];
		insertData();
		/*nodes = 0;
		friends = new table;
		string person;
		ifstream file;
		file.open("./friends.txt");
		int count = 0;
		while (!file.eof()) {
			getline(file, person);
			friends->createList();
			for (int i = 6; i + 4 < person.length(); i += 5) {
				list* temp = friends->head;
				for (int j = 0; j < count; j++) {
					temp = temp->next;
				}
				temp->insert(stoi(person.substr(i,4)));
			}
			cout << endl;
			count++;
		}
		file.close();*/
	}

	void add(int person, queue& q, bool flag, int curr) {
		node* temp = friends[person - 2001].head;
		while (temp) {
			if (temp->data != curr) {
				q.enqueue(temp->data);
			}
			temp = temp->next;
		}
		if (flag) {
			temp = friends[person - 2001].head;
			while (temp) {

				add(temp->data, q, false, curr);
				temp = temp->next;
			}
		}
	}

	queue findSocialCircle(int person) {
		queue socialCircle;
		add(person, socialCircle, true, person);
		return socialCircle;
	}

	void findBiggestSocialCircle() {
		queue circles[500];
		for (int i = 0; i < 500; i++) {
			circles[i] = findSocialCircle(i + 2001);
		}
		int big = 0;
		for (int i = 1; i < 500; i++) {
			if (circles[big].Size() < circles[i].Size()) {
				big = i;
			}
		}
		cout << "The Biggest Social Circle is of " << big + 2001 << " person\n";
	}

	void printNotIntersectableSocialCircle() {
		queue p, q;
		bool flag = true;
		for (int i = 0; i < 500; i++) {
			cout << "I : " << i << endl;
			p = findSocialCircle(i+2001);
			for (int j = 0; j < 500; j++) {
				if (i!=j && (!p.contains(j + 2001))) {
					q = findSocialCircle(j + 2001);
					if (!q.haveCommonNode(p)) {
						cout << i + 2001 << " and " << j + 2001 << endl;
						flag = false;
					}
				}
			}	
		}
		if (flag) {
			cout << "No Socail Circle Pair Found Un Intersectable\n";
		}
	}

	void distance(int p1, int p2, queue& links, int& dist) {
		friends[p1 - 2001].visited = true;
		node* temp = friends[p1 - 2001].head;
		while (temp) {
			//cout << "Temp Data: " << temp->data << endl;
			if (temp->data && temp->data== p2) {
				return;
			}
			if (friends[temp->data-2001].visited == false) {
				//links.enqueue(temp->data);
				distance(temp->data, p2, links, ++dist);
			}
			temp = temp->next;
		}
		return;
	}

	int socialDistance(int p1, int p2) {
		queue links;
		int dist = 0;
		links.enqueue(p1);
		distance(links.dequeue(), p2, links, dist);
		return dist;
	}

	

	void printCommonProfiles(int p1, int p2) {
		queue q1 = findSocialCircle(p1);
		queue q2 = findSocialCircle(p2);
		q1.print();
		cout << endl;
		q2.print();

		queue common = q1.findCommon(q2);
		common.print();
	}
	void insertData() {
		string person;
		ifstream file;
		file.open("./friends.txt");
		int curr_Index = 0;
		
		while (!file.eof()) {
			getline(file, person);
			for (int i = 6; i + 4 < person.length(); i += 5) {
				friends[curr_Index].insert(stoi(person.substr(i, 4)));
				//friends[stoi(person.substr(i, 4))-2001].insert(curr_Index+2001);
				//cout << i << " ";
			}
			//cout << endl;
			curr_Index++;
		}
		file.close();
	}

	void print() {
		node* temp = friends[0].head;
		while (temp) {
			cout << temp->data << " -> ";
			temp = temp->next;
		}
		cout << endl;
	}

};


int main() {
	graph friends;
	friends.insertData();
	cout << "Social Circle Using Graphs\n";

	cout << "-- Printing Friends -- ";
	friends.print();

	cout << "\n-- Finding Social Circle of 2001\n";
	friends.findSocialCircle(2001).print();

	cout << "\n-- Finding Biggest Social Circle\n";
	friends.findBiggestSocialCircle();

	cout << "\n-- Finding Common Profiles of 2002 and 2029\n";
	friends.printCommonProfiles(2002, 2029);

	cout << "\n-- Finding Social Distance Between 2001 and 2154\n";
	cout << "Distance : " << friends.socialDistance(2001, 2154);

	cout << "\n-- Finding Non Intersectable Social Circle\n";
	friends.printNotIntersectableSocialCircle();
	return 0;
}