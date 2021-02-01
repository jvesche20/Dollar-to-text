/*-----------------------------------------------------------------------------
	This program formats a numeric dollar amount in a text format.  the value
	is read from a file as a string. it is then converted to double and the
	cent value is extracted from the string and converted to double.
	the dollars and cents amounts are formatted separate.
	the function that convert the dollar amount is a recursive one.
 ----------------------------------------------------------------------------*/

/*
Jacob Vesche
Project 2
"I have neither given nor received unauthorized aid in completing this work,
nor have I presented someone else's work as my own."
*/
#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <iomanip>
#include <math.h>
#include <stdlib.h>

using namespace std;

#define ONE      			1
#define TEN      			10
#define TWENTY   			20
#define HUNDRED  			100
#define THOUSAND 			1000
#define MILLION  	    	1000000

#define	HUNDRED_TEXT		"HUNDRED"
#define	THOUSAND_TEXT 		"THOUSAND"
#define	MILLION_TEXT		"MILLION"

#define SPACE			 	" "
#define NULL_CHARACTER  	'\0'

const char *units_text[9] = { "ONE","TWO","THREE","FOUR","FIVE","SIX","SEVEN",
							  "EIGHT","NINE" };

int intunits_text[9] = { 1,2,3,4,5,6,7,8,9 };

const char *teens_text[10] = { "TEN","ELEVEN","TWELVE","THIRTEEN","FOURTEEN",
							  "FIFTEEN","SIXTEEN","SEVENTEEN","EIGHTEEN",
							  "NINTEEN" };
int intteens_text[10] = { 10, 11,12,13,14,15,16,17,18,19 };

const char *tens_text[8] = { "TWENTY","THIRTY","FORTY","FIFTY","SIXTY","SEVENTY",
							  "EIGHTY","NINTY" };
int inttens_text[8] = { 20,30,40,50,60,70,80,90 };
int twoNine[8] = { 2,3,4,5,6,7,8,9 };

void parse_dollars(char* dollar_text, long int dollar_amount, ofstream&);
void parse_cents(char* dollar_text, int    cent_amount, ofstream&);
void extract_amount(char* string_amount, double * dollars, int * cents);

int  main(void)

{
	double   dollars;			     /* stores the dollar amount as double  */
	long int ldollars;               /* convert dollars and cents to only dollars */
	int      cents;                  /* stores the cents amount as integer  */
	char 	 strAmount[81];          /* stores the dollar amount as string  */
	char     dollar_text[256];       /* stores the dollar amount in text    */


	ifstream input_file("dollar.in", ios::in);
	ofstream output_file("text_amount.txt", ios::out);

	if (!input_file || !output_file)
	{
		cout << "File could not be opened" << endl;
		return 0;
	}

	output_file.setf(ios::showpoint);
	output_file.setf(ios::fixed, ios::floatfield);

	/* read the data from an input file */
	while (!input_file.eof())
	{
		/* get the amount from the file and store it as string */
		input_file >> strAmount;

		/* extract the dollar and cent amount */
		extract_amount(strAmount, &dollars, &cents);
		
		if (dollars < 1.0 || dollars > 999999999.99 || cents > 99)
		{
			sprintf(dollar_text, "%s", "ERROR: amount is out of range");
			output_file << "$" << setprecision(2) << setiosflags(ios::left)
				<< setw(13) << dollars << '\t';
			output_file << dollar_text << '\n';
		}
		else
		{
			dollar_text[0] = NULL_CHARACTER;
			ldollars = (long int)dollars;
			output_file << "$" << setprecision(2) << setiosflags(ios::left)
				<< setw(13) << dollars << '\t';
			output_file << dollar_text;

			parse_dollars(dollar_text, ldollars, output_file);
			parse_cents(dollar_text, cents, output_file);
		}

		
	}

	cout << "\n\n\tOutput is stored in 'text_amount.txt'" << endl;

	system("pause");
	return 0;
}
/*-----------------------------------------------------------------------------
	this function converts the numeric dollar amount to a text format.
	the cent amount is not converted here. the numeric amount is passed as a
	double.  the formatted text amount will is appended to the string whose
	address is passed as a pointer.  the function will recurse when it finds
	millions, thounsands, and hundreds.  it will not recurse for tens, teens,
	nor units.
  ---------------------------------------------------------------------------*/
void parse_dollars(char* dollar_text, long int amount, ofstream& out)
{
	long int	residual_amount = 0;    /* holds amount of weight .i.e 999 million,
									   in 999,999,999.00 */
	long int	dollar_amount;      /* holds dollar amount to be formatted */
//	int			index;              /* holds index of text string array    */
	
	dollar_amount = amount;         /* copy original amount */
	cout << dollar_amount;
	//cout << setw(13);
	cout << "\t";
	//out << "\t";

	if (dollar_amount >= MILLION)
	{
		/* the amount has millions */
		residual_amount = dollar_amount / MILLION;

		
		// Make a loop not if statement. BC if number is 999 then it will only run once. keep looping till its 1-9. 
		
		int temp = residual_amount;

		int temp1;
		if (temp < 10) {
			cout << units_text[temp - 1] << " "<< MILLION_TEXT << " ";
			out << units_text[temp - 1] << " "<< MILLION_TEXT << " ";
		}
		while (temp > 10) {
			temp1 = temp;
			if (temp > 100) {
				if (temp % 100 < 10 && temp % 100 != 0) {// less than 10 but not 0
					cout << units_text[(temp1 / 100) - 1] << " " << HUNDRED_TEXT << " ";
					out << units_text[(temp1 / 100) - 1] << " " << HUNDRED_TEXT << " ";
					temp1 = temp1 % 100;

					cout << units_text[(temp1 - 1)] << " " << MILLION_TEXT<< " ";
					out << units_text[(temp1 - 1)] << " " << MILLION_TEXT<< " ";
					//temp1 = temp1 % 10;
				}

				else if (temp % 100 < 20 && temp % 100 > 9) {
					// 10-19
					cout << units_text[(temp1 / 100) - 1] << " " << HUNDRED_TEXT << " ";
					out << units_text[(temp1 / 100) - 1] << " " << HUNDRED_TEXT << " ";
					temp1 = temp1 % 10;

					for (int i = 0; i < 10; i++) {
						if (temp1 == intteens_text[i]) {
							temp1 = i;
							break;
						}
					}

					cout << teens_text[temp1] << " "<< MILLION_TEXT << " ";
					out << teens_text[temp1] << " "<< MILLION_TEXT << " ";
				}
				else if(temp % 100 == 0){
					cout << units_text[(temp1 / 100) - 1] << " "<< HUNDRED_TEXT << " " << MILLION_TEXT << " ";
					out << units_text[(temp1 / 100) - 1] << " "<< HUNDRED_TEXT << " " << MILLION_TEXT << " ";
				}
				
				else { // everything else
					cout << units_text[(temp1 / 100) - 1] << " " << HUNDRED_TEXT << " ";
					out << units_text[(temp1 / 100) - 1] << " " << HUNDRED_TEXT << " ";
					temp1 = temp1 % 100;

					cout << tens_text[(temp1 / 10) - 2] << " ";
					out << tens_text[(temp1 / 10) - 2] << " ";
					temp1 = temp1 % 10;

					if (temp1 != 0) {
						cout << units_text[temp1 - 1] << " " << MILLION_TEXT << " ";
						out << units_text[temp1 - 1] << " " << MILLION_TEXT << " ";
					}
					else {
						cout << MILLION_TEXT << " ";
						out << MILLION_TEXT << " ";
					}
				}
			}
			else if (temp > 10) {


					// 99-20 but not 0
				int tenTho, mod;
				tenTho = temp / 10;
				mod = temp % 10;
				if (temp <100  && temp > 19) {
					if (mod != 0) {
						cout << tens_text[tenTho - 2] << " " << units_text[mod - 1] << " "<< MILLION_TEXT<< " ";
						out << tens_text[tenTho - 2] << " " << units_text[mod - 1] << " "<< MILLION_TEXT << " ";
					}
					else {
						cout << tens_text[tenTho - 2] << " " << MILLION_TEXT<< " ";
						out << tens_text[tenTho - 2] << " " << MILLION_TEXT<< " " ;

					}
					
				}

			}

			temp = temp / 10;
			//cout << endl;
		}
		
		/*
		.------------------------------------------------------------------ -
			.parse 1, 2, or 3 digits // find out how many millions  
			// find out how many digits there are. 
			.
			.parse 1, 2, or 3 digits for the millions
			.nine hundred ninty nine million, or ninty nine million, etc...
			.
			--------------------------------------------------------------------
			*/
			strcat(dollar_text, SPACE);                   // append space after
			/* subtract the formatted portion */
		dollar_amount -= residual_amount * MILLION;   // 999,999,999 - 999, 000, 000
													  // = 999, 999,next parse thousands below
	}
	
	if (dollar_amount >= THOUSAND)
	{
		residual_amount = dollar_amount / THOUSAND;


		// Make a loop not if statement. BC if number is 999 then it will only run once. keep looping till its 1-9. 

		int temp = residual_amount;

		int temp1;
		if (temp < 10) {
			cout << units_text[temp - 1] << " " << THOUSAND_TEXT << " ";
			out << units_text[temp - 1] << " " << THOUSAND_TEXT << " ";
		}
		while (temp > 10) {
			temp1 = temp;
			if (temp > 100) {
				if (temp % 100 < 10 && temp % 100 != 0) {// less than 10 but not 0
					cout << units_text[(temp1 / 100) - 1] << " " << HUNDRED_TEXT << " ";
					out << units_text[(temp1 / 100) - 1] << " " << HUNDRED_TEXT << " ";
					temp1 = temp1 % 100;

					cout << units_text[(temp1 - 1)] << " " << THOUSAND_TEXT<< " ";
					out << units_text[(temp1 - 1)] << " " << THOUSAND_TEXT<< " ";
					//temp1 = temp1 % 10;
				}

				else if (temp % 100 < 20 && temp % 100 > 9) {
					// 10-19
					cout << units_text[(temp1 / 100) - 1] << " " << HUNDRED_TEXT << " ";
					out << units_text[(temp1 / 100) - 1] << " " << HUNDRED_TEXT << " ";
					temp1 = temp1 % 10;

					for (int i = 0; i < 10; i++) {
						if (temp1 == intteens_text[i]) {
							temp1 = i;
							break;
						}
					}

					cout << teens_text[temp1] << " "<<THOUSAND_TEXT<< " ";
					out << teens_text[temp1] << " "<< THOUSAND_TEXT<< " ";
				}
				else if (temp % 100 == 0) { // 0
					cout << units_text[(temp1 / 100) - 1] << " "<< HUNDRED_TEXT << " " << THOUSAND_TEXT<< " ";
					out << units_text[(temp1 / 100) - 1] << " "<< HUNDRED_TEXT << " " << THOUSAND_TEXT << " ";
				}

				else { // everything else
					cout << units_text[(temp1 / 100) - 1] << " " << HUNDRED_TEXT << " ";
					out << units_text[(temp1 / 100) - 1] << " " << HUNDRED_TEXT << " ";
					temp1 = temp1 % 100;

					cout << tens_text[(temp1 / 10) - 2] << " ";
					out << tens_text[(temp1 / 10) - 2] << " ";
					temp1 = temp1 % 10;

					if (temp1 != 0) {
						cout << units_text[temp1 - 1] << " " << THOUSAND_TEXT << " ";
						out << units_text[temp1 - 1] << " " << THOUSAND_TEXT << " ";
					}
					else {
						cout << THOUSAND_TEXT<< " ";
						out << THOUSAND_TEXT<< " ";
					}
				}
			}
			else if (temp > 10) {


				// 99-20 but not 0
				int tenTho, mod;
				tenTho = temp / 10;
				mod = temp % 10;
				if (temp < 100 && temp > 19) {
					if (mod != 0) {
						cout << tens_text[tenTho - 2] << " " << units_text[mod - 1] << " " << THOUSAND_TEXT << " ";
						out << tens_text[tenTho - 2] << " " << units_text[mod - 1] << " " << THOUSAND_TEXT << " ";
					}
					else {
						cout << tens_text[tenTho - 2] << " " << THOUSAND_TEXT << " ";
						out << tens_text[tenTho - 2] << " " << THOUSAND_TEXT<< " " ;

					}

				}

			}
			temp = temp / 10;
			//cout << endl;
		}

		
		dollar_amount -= residual_amount * THOUSAND;
	}

	if (dollar_amount >= HUNDRED)
	{
		residual_amount = dollar_amount / HUNDRED;


		// Make a loop not if statement. BC if number is 999 then it will only run once. keep looping till its 1-9. 

		int temp = residual_amount;

		
		if (temp < 10) {
			cout << units_text[temp - 1] << " " << HUNDRED_TEXT << " ";
			out << units_text[temp - 1] << " " << HUNDRED_TEXT << " ";
		}
		

		dollar_amount -= residual_amount * HUNDRED;
	}
	if (dollar_amount >= TWENTY)
	{
		residual_amount = dollar_amount / TEN;

		int temp = residual_amount;

		
		
		/* here the amount is between 20 & 99 */
		for (int i = 0; i < 9; i++) {
			if (temp == twoNine[i]) {
				cout << tens_text[i] << " ";
				out << tens_text[i] << " ";

			}
		}
		dollar_amount -= residual_amount * TEN;
	}

	if (dollar_amount >= TEN)
	{
		/* the amount is between 10 & 19 */
		/* get the text array index */
		for (int i = 0; i < 9; i++) {
			if (dollar_amount == intteens_text[i]) {
				cout << teens_text[i] << " ";
				out << teens_text[i] << " ";

			}
		}
		dollar_amount -= residual_amount * TEN;
	}

	if (dollar_amount >= ONE)
	{
		for (int i = 0; i < 9; i++) {
			if (dollar_amount == intunits_text[i]) {
				cout << units_text[i] << " ";
				out << units_text[i] << " ";

			}
		}
	}
	//if (dollar_amount == 0) {
		//cout << " ";
		//out << " ";
	//}
	
	
	return;
}

/*-----------------------------------------------------------------------------
	this function converts the numeric cents amount to a text format.
	the cent amount is passed as an integer parameter. the text format
	is appended to the string whose pointer is als passed as a parameter
 ----------------------------------------------------------------------------*/
void parse_cents(char* dollar_text, int cent_amt, ofstream& out)
{
	
	

	char	cent_text[16];

	cout << "and "<< cent_amt << "/100" << endl;
	out << "and "<< cent_amt << "/100" << endl;

	//sprintf(cent_text, " and %02d/100", cent_amt);
	strcat(dollar_text, cent_text);

		return;
}

/*-----------------------------------------------------------------------------
	this function converts the string to a dollar amount. and extracts the
	the cent amount from the string and stores both numbers in the variables
	whose addresses are passed through the function call.
  ---------------------------------------------------------------------------*/
void extract_amount(char * string_amount, double * dollars, int * cents)
{
	char * strCentsStartMarker;

	/* convert string to double */
	*dollars = atof(string_amount);
	
	
	//look for the decimal point 
	strCentsStartMarker = strchr(string_amount, '.');
	int j, k, newCents;
	
	j = (strCentsStartMarker - string_amount + 1);
	k = strCentsStartMarker - string_amount + 2;

	//cout << string_amount[j] << string_amount[k];
	
	//char * dot;
//	*dot = '.';
	//int torf;
	//torf = strcmp(dot, strCentsStartMarker);
	//cout << torf;
	string test, test2;
	char test3;
	//if (strCentsStartMarker != dot) {
	if (j < 0 || k < 0) {
		test = '\0';
		test2 = '\0';
		test3 = '\0';

	}
	else {
		test = string_amount[j];
		test3 = string_amount[j];
		test2 = string_amount[k];
		test = test + test2;
	}
	//}

	

	

	//cout << newCents;
	
	//cout << string_amount[5] << string_amount[6];
	

	

	//cout << &strCentsStartMarker[j];
	

	//cout << strCentsStartMarker;
	
	if (strCentsStartMarker == NULL || strCentsStartMarker == "." || test == "" || (test3 == '\0')) {
		
		*cents = 0;
	}
	else {
		//j = strCentsStartMarker - string_amount + 1;


		*cents = stoi(test);

	}
	
		return;
}



