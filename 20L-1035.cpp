#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;



class Term
{
private:
	long int exponent;
	long int coef;
	Term* Next;
public:
	Term()//default contsrucotr
	{
		exponent = 0;
		coef = 0;
		Next = NULL;
	}

	Term(long int c, long int e = 0, Term* t = NULL)// constructor with default argument
	{
		exponent = e;
		coef = c;
		Next = t;
	}

	~Term()
	{

	}

	friend class Polynomial;
};

class Polynomial
{
private:
	Term* First;
	Term* Last;
public:
	Polynomial()// deafult constructor in which head is pointing to Last polynomial 
	{
		First = new Term();
		First->Next = Last;
		Last = NULL;
	}

	~Polynomial()
	{
		Term* current = First;
		Term* next;
		while (current != NULL) // deleting each node beginning from start
		{
			next = current->Next;// keep pointer track to next and delete current
			if (current)
				delete current;
			current = next;
		}
	}

	void Input()
	{
		cout << endl << "Enter the Number of Terms you'd Like to have in Polynomial:	";
		int Size;
		cin >> Size;
		long int input = 1;
		long int exp = 1;

		int i = 0;
		while (i < Size)// take input according to size entered by User
		{
			bool Place = false;
			cout << "Enter Coefficient other than 0:	";
			cin >> input;
	
			cout << "Enter Exponent >-1:	";
			cin >> exp;
			cout << endl;

			if (input != 0 && exp > -1)
			{
				if (First->Next == Last)// empty initially for placing first Term
					First->Next = new Term(input, exp, First->Next), Place = true;// bool type place to see

				if (exp > First->Next->exponent && Place == false)// place at start
					First->Next = new Term(input, exp, First->Next);

				else if (Place == false)
				{
					Term* temp = First;
					for (; temp->Next != NULL; temp = temp->Next)
						if (exp == temp->Next->exponent)// same exp check
						{
							temp->Next->coef += input;// if found add and break loop
							Place = true;
							break;
						}

					if (Place == false)
					{
						Term* Temp = First;
						for (; Temp->Next != NULL && Place == false; Temp = Temp->Next)// findind appro positoion to place in middle of two
						{
							if (Temp->exponent > exp && Temp->Next->exponent < exp)
							{
								Temp->Next = new Term(input, exp, Temp->Next);
								Place = true;
								break;
							}
						}
						if (Place == false)// else place at end
							Temp->Next = new Term(input, exp, Temp->Next);
					}
				}
				i++;// loop variable
			}
		}
	}

	void Output()
	{
		cout << endl << "Polynomial:	";
		Term* Temp = First->Next;
		for (; Temp != NULL; Temp = Temp->Next)// keep running until NULL
		{
			if (Temp->coef > 0 && First->Next != Temp)// if term is first donot output + sign
				cout << "+";

			if (Temp->exponent == 0)
				cout << Temp->coef;

			else
				cout << Temp->coef << "x^" << Temp->exponent;
		}
		cout << endl;
	}

	Polynomial(const Polynomial& rhs)// copy constructor
	{
		if (this->First)// if there is alredy existing list remove it
		{
			Term* current = First;
			Term* next;
			while (current != NULL) // deleting each node beginning from start
			{
				next = current->Next;// keep pointer track to next and delete current
				if (current)
					delete current;
				current = next;
			}
		}

		Term* temp = new Term();// new poinetr
		First = temp;
		First->Next = temp->Next = Last = NULL;
		Term* temp2 = rhs.First;

		for (; temp2 != NULL; temp = temp->Next, temp2 = temp2->Next)// deep copy
		{
			temp->coef = temp2->coef;
			temp->exponent = temp2->exponent;
			if (temp2->Next != NULL)// if end reached donot allocate more memory
				temp->Next = new Term();
		}
		temp = NULL;// set last term to null
	}

	Polynomial& operator=(const Polynomial& rhs)//Assignement operrator
	{
		if (this->First)// if there is alredy existing list remove it
		{
			Term* current = First;
			Term* next;
			while (current != NULL) // deleting each node beginning from start
			{
				next = current->Next;// keep pointer track to next and delete current
				if (current)
					delete current;
				current = next;
			}
		}

		if (this != &rhs)//avoid self assignement
		{
			Term* temp = new Term();
			First = temp;
			First->Next = temp->Next = Last = NULL;
			Term* temp2 = rhs.First;

			for (; temp2 != NULL; temp = temp->Next, temp2 = temp2->Next)// deep copy
			{
				temp->coef = temp2->coef;
				temp->exponent = temp2->exponent;
				if (temp2->Next != NULL)// if end reached donot allocate more memory
					temp->Next = new Term();
			}
			temp = NULL;
		}
		return *this;
	}

	Polynomial operator+(Polynomial& List)//add
	{
		if (First->Next == NULL)
			return List;
		if (List.First->Next == NULL)
			return *this;

		Polynomial add;
		long int Sum;

		Term* lhs = First->Next;// pointers to point at all three polynomials
		Term* rhs = List.First->Next;
		Term* New = add.First;

		// check if they are null
		while (lhs != NULL && rhs != NULL)// keep adding until one reach null
		{
			if (lhs->exponent == rhs->exponent)// if both have equal exp
			{
				Sum = lhs->coef + rhs->coef;
				New->Next = new Term(Sum, lhs->exponent, New->Next);

				lhs = lhs->Next;
				rhs = rhs->Next;
				New = New->Next;
			}
			else if (lhs->exponent > rhs->exponent)// if calling obj has node with bigger exp
			{
				New->Next = new Term(lhs->coef, lhs->exponent, New->Next);
				lhs = lhs->Next;
				New = New->Next;
			}
			else if (lhs->exponent < rhs->exponent)
			{
				New->Next = new Term(rhs->coef, rhs->exponent, New->Next);
				rhs = rhs->Next;
				New = New->Next;
			}
		}

		if (lhs != NULL)// place the remaining of larger polynomials
		{
			while (lhs != NULL)
			{
				New->Next = new Term(lhs->coef, lhs->exponent, New->Next);
				lhs = lhs->Next;
				New = New->Next;
			}
		}
		else if (rhs != NULL)
		{
			while (rhs != NULL)
			{
				New->Next = new Term(rhs->coef, rhs->exponent, New->Next);
				rhs = rhs->Next;
				New = New->Next;
			}
		}
		return add;
	}

	Polynomial operator*(Polynomial& List)
	{
		if (First->Next == NULL)
			return List;
		if (List.First->Next == NULL)
			return *this;

		Polynomial pro;
		long int c;
		long int e;

		Term* lhs = First->Next;//pointers for all three polynomials
		Term* rhs = List.First->Next;
		Term* renew = List.First->Next;

		if (lhs->exponent < rhs->exponent)
		{
			rhs = First->Next;
			lhs = List.First->Next;
			renew = First->Next;
		}

		Term* AddNew = pro.First;

		for (; lhs != NULL; lhs = lhs->Next)// runs unti; end of first one
		{
			for (; rhs != NULL; rhs = rhs->Next)// runs again for each value of lhs works for unsorted too can omit if already sorted
			{
				c = lhs->coef * rhs->coef;
				e = lhs->exponent + rhs->exponent;

				Term* New = pro.First->Next;
				bool Place = false;

				while (New != NULL)// search to see if there is term some with same exp
				{
					if (e == New->exponent)
					{
						New->coef += c;
						Place = true;
						break;
					}
					New = New->Next;
				}

				if (Place == false)// else create a new Term and store
				{
					AddNew->Next = new Term(c, e, AddNew->Next);
					AddNew = AddNew->Next;
				}
			}
			rhs = renew;
		}
		return pro;
	}

	long int Evaluate(int x)
	{
		long int ans = 0;
		Term* temp = First;
		for (; temp != NULL; temp = temp->Next)
			ans += temp->coef * (pow(x, temp->exponent));// calculates power and keep adding until end
		return ans;
	}
};
int main()
{
	system("color 0B");
	Polynomial P1;
	P1.Input();
	P1.Output();

	Polynomial P2;
	P2.Input();
	P2.Output();

	cout << endl << "...SUM	";
	Polynomial P3 = P1 + P2;
	P3.Output();

	cout << endl << "...Product	";
	Polynomial P4 = P1 * P2;
	P4.Output();

	cout << endl << "...Evaluation	" << endl;
	int input = 0;
	cout << "Enter Value to evaluate Polynomial:	";
	cin >> input;
	cout << "Value of Polynomial At " << input << "  is:	" << P1.Evaluate(input) << endl << endl;

	return 0;
}
