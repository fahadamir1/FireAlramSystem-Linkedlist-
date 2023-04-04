#include <iostream>
#include <fstream>
#include <string.h>
#include<string>
#include <ctime>
#include<conio.h>
#include<dos.h>
#ifdef _WIN32
#include <Windows.h>
#include <cstdlib>
#else
#include <unistd.h>
#endif
using namespace std;
struct Node {
	int id;
	float temperature;
	int smoke;
	int flame;
	string date;
	Node* next;
};
int count1 = 1;
Node* head = NULL;
Node* tail = NULL;
void display() {
	Node* temp = head;
	while (temp != NULL) {
		cout << temp->temperature << endl;;
		cout << temp->smoke << endl;;
		cout << temp->flame << endl;;
		cout << temp->id << endl;;
		cout << temp->date << endl;;
		temp = temp->next;
	}
}
void insertNode(float temp, int smoke, int flame, int i1d, string D) { /// insertion based on index from file
	if (i1d >= count1) {
		Node* newNode = new Node;
		newNode->temperature = temp;
		newNode->smoke = smoke;
		newNode->flame = flame;
		newNode->id = i1d;
		newNode->date = D;
		newNode->next = NULL;
		if (head == NULL) {
			head = newNode;
			tail = newNode;
		}
		else {
			tail->next = newNode;
			tail = newNode;
		}
	}
}
string dateandtime() {
	time_t now = time(0);
	char* dt = ctime(&now);
	return dt;
}
void reading() {
	cout << "Wait Please.";
	Sleep(500);
	cout << ".";
	Sleep(500);
	cout << ".";
	Sleep(500);
	cout << ".";
	Sleep(500);
	cout << endl;
	cout << "Successfull" << endl;
	return;
}
void writeonclient() {
	Node* temp = head;
	ofstream newfile("ClientData.txt");
	while (temp != NULL) {
		newfile << temp->id << "," << temp->temperature << "," << temp->smoke << "," << temp->flame << "," << temp->date << endl;
		temp = temp->next;
	}
	newfile.close();
}
void searchfromflame() {
	Node* temp = head;
	while (temp != NULL) {
		if (temp->flame == 1) {
			cout << "Flame High On: " << temp->date;
			cout << "Temperature: " << temp->temperature << endl;
			cout << "Smoke: " << temp->smoke << endl;
			cout << "Flame: " << temp->flame << endl;
			cout << endl;
		}
		temp = temp->next;
	}
	return;
}
void searchfromsmoke() {
	Node* temp = head;
	while (temp != NULL) {
		if (temp->smoke == 1) {
			cout << "Smoke High On: " << temp->date;
			cout << "Temperature: " << temp->temperature << endl;
			cout << "Smoke: " << temp->smoke << endl;
			cout << "Flame: " << temp->flame << endl;
			cout << endl;
		}
		temp = temp->next;
	}
	return;
}
void Readfromserver() {
	ifstream file("ServerData.txt");
	if (file) {
		string line;
		float temp;
		int smoke, flame;
		int row = 1;
		bool flag = false;
		while (getline(file, line)) {
			if (row == 4) {
				row = 1;
				flag = false;
			}
			if (row == 1) {
				temp = stof(line);
				row++;
				continue;
			}
			if (row == 2) {
				smoke = stoi(line);
				row++;
				continue;
			}
			if (row == 3) {
				flame = stoi(line);
				row++;
				flag = true;
				if (flag) {
					string d;
					d = dateandtime();
					insertNode(temp, smoke, flame, count1, d);
					count1++;
				}
				continue;
			}

		}
		file.close();
	}
	else {
		cout << "File not found server" << endl;
	}
}
int getdate(Node* temp) {
	int num = 0;
	string det = "Mon Jan 23 01:38:12 2023";
	int j = 8;
	string update;
	char a = det[j];
	char b = det[j + 1];
	num = (((int)a) - 48) * 10 + num;
	num = (((int)b) - 48) + num;
	return num;
}
void DisplayDatatilltime(int val) {
	Node* temp = head;
	while (temp != NULL) {
		int valdate;
		valdate = getdate(temp);
		if (valdate == val) {
			cout << "Date " << temp->date;
			cout << "Temperature: " << temp->temperature << endl;
			cout << "Smoke: " << temp->smoke << endl;
			cout << "Flame: " << temp->flame << endl;
			cout << endl;
		}
		temp = temp->next;
	}

}
void searchfromtemperature(int val) {
	Node* temp = head;
	while (temp != NULL) {
		if (temp->temperature > val) {
			cout << "Temperature High On: " << temp->date;
			cout << "Temperature: " << temp->temperature << endl;
			cout << "Smoke: " << temp->smoke << endl;
			cout << "Flame: " << temp->flame << endl;
			cout << endl;
		}
		temp = temp->next;
	}
}
char menu() {
	cout << " _______________________________________" << endl;
	cout << endl;
	cout << "|                                       |" << endl;
	cout << "|           Fire Alram System           |" << endl;
	cout << "|                                       |" << endl;
	cout << " _______________________________________" << endl;
	cout << "a.Fetch Data from the Server" << endl;
	cout << "b.Search for flame" << endl;
	cout << "c.Search through Temperature" << endl;
	cout << "d.Seach through Date Range" << endl;
	cout << "e.Search through Smoke" << endl;
	cout << "f.Clear the Screen" << endl;
	cout << "g.Exit the System" << endl;
	cout << endl;
	cout << "Enter the Number B/W (a-g|| A-G):";
	return getch();
}
int main() {
	char input;
	bool flag = true;
	while (flag) {
		input = menu();
		if (input == 'a' || input == 'A') {
			Readfromserver();
			cout.flush();
			reading();
			writeonclient();
		}
		else if (input == 'b' || input == 'B') {
			reading();
			cout << endl;
			searchfromflame();
		}
		else if (input == 'c' || input == 'C') {
			reading();
			int val;
			cout << "Enter value of temperature you are looking:" << endl;
			cin >> val;
			searchfromtemperature(val);
		}
		else if (input == 'd' || input == 'D') {
			reading();
			int val1;
			cout << "Enter range of date: " << endl;
			cin >> val1;
			DisplayDatatilltime(val1);
		}
		else if (input == 'e' || input == 'E') {
			reading();
			cout.flush();
			searchfromsmoke();
		}
		else if (input == 'f' || input == 'F') {
			reading();
			cout.flush();
			system("cls");
		}
		else if (input == 'g' || input == 'G') {
			break;
		}
		else {
			cout << "invalid input" << endl;
		}
	}
	system("pause");
	return 0;
}


