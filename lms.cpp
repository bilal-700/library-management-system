#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

class Date
{
public:
	int year, month, day;
	Date()
	{
		reset_date();
	}
	void reset_date()
	{
		year = 0;
		month = 0;
		day = 0;
	}
	void display_date()
	{
		if (year == 0 && month == 0 && day == 0)
		{
			cout << "Book not issued yet." << endl;
		}
		else
		{
			cout << day << "." << month << "." << year << endl;
		}
	}
	void input_date()
	{
		cout << "Enter today's day: ";
		cin >> day;
		cout << "Enter the current month: ";
		cin >> month;
		cout << "Enter the current year: ";
		cin >> year;
	}
};

class Book
{
public:
	int fee = 0;
	string author;
	string name;
	int id;
	Date date;
	string issuer;

	void input_book()
	{
		cout << "Enter the book id: ";
		cin >> id;
		cout << "Enter the name of the book: ";
		std::getline(std::cin >> std::ws, name);
		cout << "Enter the name of the author: ";
		std::getline(std::cin >> std::ws, author);
	}

	void display_book()
	{
		cout << "Name: " << name << endl;
		cout << "Author: " << author << endl;
		cout << "Date Issued: "; date.display_date();
		cout << "Late Fee: " << fee << endl;
		cout << "Book id.: " << id << endl;
	}

	void issue_book()
	{
		cout << "Enter name of the issuer: ";
		std::getline(std::cin >> std::ws, issuer);
		date.input_date();
		cout << "Book issued." << endl;
	}

	void book_return()
	{
		calculate_fee();
		if (fee != 0)
		{
			cout << "Book returned late. A fee of Rs" << fee << " must be charged." << endl;
		}
		else
		{
			cout << "Book returned on time.No extra charges!" << endl;
		}
		date.reset_date();
	}

	// Late fee is charged when the book is returned after two weeks or more of the date of issue.
	// If the book is returned after a month or later, a late fee equal to the price of the book is charged.

	void calculate_fee()
	{
		int price = 1500;
		Date current_date;
		current_date.input_date();
		if (current_date.month == date.month)
		{
			if (current_date.day - date.day >= 14)
			{
				fee = current_date.day - date.day;
			}
			else
			{
				fee = 0;
			}
		}
		if (current_date.month != date.month)
		{
			if (30 - date.day + current_date.day >= 14)
			{
				fee = 30 - date.day + current_date.day;
			}
			else
			{
				fee = 0;
			}
		}
	}
};

struct node
{
	Book B;
	node* left;
	node* right;
};

class btree
{
public:
	btree();

	void insert(Book B, node* leaf);
	void insert(Book B);
	node* search(int id, node* leaf);
	node* root;
	void destroy_tree();
	void destroy_tree(node* leaf);

};
btree::btree()
{
	root = NULL;
}

void btree::destroy_tree(node* leaf)
{
	if (leaf != NULL) // until the root is reached
	{
		destroy_tree(leaf->left);
		destroy_tree(leaf->right);
		delete leaf;
	}
}

void btree::insert(Book B, node* leaf)
{
	leaf->left = NULL;
	leaf->right = NULL;

	if (B.id < leaf->B.id)
	{
		if (leaf->left != NULL)
		{
			insert(B, leaf->left);
		}
		else
		{
			leaf->left = new node; // creates a new node at the left of the leaf
			leaf->B = B;
			leaf->left->left = NULL; //sets the left leaf of the new node to null
			leaf->left->right = NULL; // sets the right leaf of the new node to null
		}
	}
	if (B.id >= leaf->B.id)
	{
		if (leaf->right != NULL)
		{
			insert(B, leaf->right);
		}
		else
		{
			leaf->right = new node;
			leaf->B = B;
			leaf->right->left = NULL;
			leaf->right->left = NULL;

		}
	}
}

node* btree::search(int id, node* leaf)
{
	if (id == leaf->B.id)
	{
		return leaf;
	}
	if (id < leaf->B.id)
	{
		return search(id, leaf->left);
	}
	else
	{
		return search(id, leaf->right);
	}
}

void btree::destroy_tree()
{
	destroy_tree(root);
}

void btree::insert(class Book B)
{
	if (root != NULL)
	{
		insert(B, root);
	}
	else
	{
		root = new node;
		root->B = B;
		root->left = NULL;
		root->right = NULL;
	}
}



// main function starts
int main()
{
	Book books;
	btree booktree;
	int choice;
	cout << "----------------------------------" << endl;
	cout << "   Library Management System" << endl;
	cout << "----------------------------------" << endl;
	do
	{
		cout << "\t  Main Menu\n";
		cout << "(1) Add book to the list\n";
		cout << "(2) Issue book\n";
		cout << "(3) Return the book\n";
		cout << "(4) Search the book using book id\n";
		cout << "(5) Quit\n";
		cout << "----------------------------------" << endl;
		cout << "Enter Choice-> ";
		cin >> choice;
		cout << "----------------------------------" << endl;

		if (1 <= choice && choice <= 5)
		{
			switch (choice)
			{
			case 1:
			{
				books.input_book();
				booktree.insert(books);
				cout << endl;
				cout << "Book/Books is/are added successfully." << endl;
			}
			break;
			case 2:
			{
				{
					int id;
					cout << "Enter Book id of the book to be issued: ";
					cin >> id;
					node* bnode = booktree.search(id, booktree.root);
					bnode->B.issue_book();
				}
			}
			break;
			case 3:
			{
				{
					int id;
					cout << "Enter Book id of the book to be returned: ";
					cin >> id;
					node* bnode = booktree.search(id, booktree.root);
					bnode->B.book_return();
				}
			}
			break;
			case 4:
			{
				{
					int id;
					cout << "Enter the Book id of the book to be displayed: ";
					cin >> id;
					node* bnode = booktree.search(id, booktree.root);
					bnode->B.display_book();
				}
			}
			break;
			case 5:
			{
				return 0;
			}
			default:
				cout << "Invalid choice.Enter again.\n\n";
				break;
			}
		}
	} while (choice != 6);
}


