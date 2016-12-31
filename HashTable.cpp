#include <iostream>
//Chase Kyle
//Simple implementation of a Hash table
using namespace std;
const int CAPACITY = 10;
void initTable(int data[]);
void printTable(int data[]);
int hash_function(int key);
void hashInsert(int data[], int key);
bool key_occurs(int data[], int search_key);

int main()
{
	int data[CAPACITY];
	initTable(data);
	hashInsert(data, 10);
	hashInsert(data, 22);
	hashInsert(data, 11);
	hashInsert(data, 31);
	hashInsert(data, 24);
	hashInsert(data, 88);
	hashInsert(data, 38);
	hashInsert(data, 21);
	printTable(data);

	cout << endl << endl << "Part 2: Checking numbers in the hash table" << endl;
	int search_key = 11;
	if (key_occurs(data, search_key))
		cout << search_key << " is found." << endl;
	else
		cout << search_key << " is not found." << endl;

	search_key = 31;
	if (key_occurs(data, search_key))
		cout << search_key << " is found." << endl;
	else
		cout << search_key << " is not found." << endl;

	search_key = 23;
	if (key_occurs(data, search_key))
		cout << search_key << " is found." << endl;
	else
		cout << search_key << " is not found." << endl;

	system("pause");
	return 0;
}
//initialize hash table
void initTable(int data[])
{
	for (int i = 0; i < CAPACITY; i++)
		data[i] = -1;
}
//print the hash table
void printTable(int data[])
{
	cout << "Part 1: Hash Table" << endl;
	for (int i = 0; i < CAPACITY; i++)
		cout << data[i] << " ";
}
int hash_function(int key)
{
	return (key%CAPACITY);
}
//insert item into hashtable
void hashInsert(int data[], int key)
{
	int tablePos = hash_function(key);
	int i = tablePos;
	while (i < CAPACITY)
	{
		if (data[i] == -1)
		{
			data[i] = key;
			break;
		}
		else
			i++;
	}
}
//boolean function to search the hash table for a key
bool key_occurs(int data[], int search_key)
{
	int posToCheck = hash_function(search_key);
	int i = posToCheck;
	while (i < CAPACITY)
	{
		if (data[i] == search_key)
			return 1;
		else
			i++;
	}
	return 0;
}
