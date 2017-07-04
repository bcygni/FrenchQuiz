#include <iostream>
#include <fstream> //to open files
#include <string> //to use string objects
#include <vector> //to use vector objects
#include <cctype> //in order to use tolower()- convert characters to lower case
#include <ctime> //to generate a seed for random number generator
#include <cstdlib> //for random number generator

using namespace std;


//Structures that will store an English Noun, the French Noun, and the gender
struct Noun {

	string english; //English word
	string french; //French word
	char gender; //Gender of French word (m or f)

};

struct Verb {

	string english;
	string french[6];  //Will store all conjugations of the French word
	string infin; //the infinitive of the french translation

};

//Function prototypes
string input_answer(); //user inputs answer and function returns lower case of answer
int noun_quiz(Noun nouns[], int);  //quiz function for nouns -takes an array of Nouns and # of questions, returns score as an int
int verb_quiz(Verb verbs[]);  //quiz function for nouns -takes an array of Verbs and # of questions, returns score as an int
int random_int(int, int); //function to generate a random int between min and max
bool search_list(int, vector<int>); //function to search a vector of integers. Returns true if integer is in vector
vector<int> random_numbers_vector(int); //function to generate a vector of vector of random integers that do not repeat between 0 and max

int main() {

	srand(time(0)); //seed random number generator
	const int NUMBER_OF_WORDS = 15; //the max number of words in each file/array
	int score;
	string easy_nouns_file = "easy-nouns.txt", easy_verbs_file = "easy_verbs.txt";
	string answer; //placeholder for user's answer
	vector<int> random_vector; //will store random numbers in order to randomize order of questions asked


	Noun word_list[NUMBER_OF_WORDS]; //Create an empty array that will hold all the nouns

	int choice = 0; //store main menu choice

	//Welcome message
	cout << "---French Quiz!---\n"
		<< "This quiz will test your English to French translation skills!\n\n\n";

	//Loop for main selection menu
	do {

		cout << "\n\tChoose from the options below \n\n"
			<< "\t1 - Easy Nouns\n"
			<< "\t2 - Easy Verbs\n"
			<< "\t* - More coming soon!\n"
			<< "\t9 - Quit\n";

		cin >> choice;

		if (choice == 1) {


			/* This section will open the input file, read the data into struct Noun
			and save that Noun into an array with a randomized order */


			//Create a vector with random integers that do not repeat between 0 and NUMBER_OF_WORDS
			vector<int> randNumVec = random_numbers_vector(NUMBER_OF_WORDS);


			string en, fr; 
			char g; //placeholders while reading input data

			ifstream input_file(easy_nouns_file.c_str()); //need to convert to c-string object to allow opening file
			
			for (int i = 0; i < NUMBER_OF_WORDS; i++) {

				input_file >> en >> fr >> g;  //read the values of the input file into en, fr, and g (gender)
				Noun new_word = { en, fr, g }; //store the values of en, fr, g, into the Noun structure members english, french, and gender
				word_list[randNumVec[i]] = new_word; //store the new_word in the index of the value of randNumVec[i]

			}

			input_file.close();

			score = noun_quiz(word_list, NUMBER_OF_WORDS);

			cout << "\nYour score is: " << score;

		}

		else if (choice == 2) {

			cout << "Verbs not available yet.";

		}

		cin.clear(), cin.ignore(1000, '\n');

	} while (choice != 9); //End loop for main selection menu

	return 0;
}


/*Primary Quiz Functions*/


string input_answer() {  //returns a user response in all lowercase

	string response;
	cout << ": ";
	getline(cin, response);

	//changes every character in the response to lowercase
	for (unsigned int x = 0; x < response.length(); ++x) {
		response[x] = tolower(response[x]); 
	}

	return response;
}



int noun_quiz(Noun nouns[], int num_of_questions) {  //the nouns quiz which takes a list of nouns and returns a score

	string answer;
	int score = 0;

	cin.ignore(1000, '\n');

	for (int question = 0; question < num_of_questions; question++) {

		cout << endl << endl << endl;
		cout << "\nQuestion #" << question + 1 
			<< "\n\tTranslate <" << nouns[question].english << "> into French.\n";

		answer = input_answer();

		if (answer == nouns[question].french) {
			cout << "\nCorrect!\n";
			score++;
		}
		else {
			cout << "\nIncorrect.\n" << "The correct answer is <" << nouns[question].french << ">\nPress enter to continue.\n";
			cin.get();
		}
	}

	return score;
}


int verb_quiz(Verb verbs[]) {


	return 0;
}





/* The following functions are used to generate a vector of randomized integers
that do not repeat to be used to randomize the index values of the 
words array for the quiz.

First - create an empty vector called numList with the starting size of the NUMBER_OF_WORDS constant.
Then - generate a random number between 0 and the NUMBER_OF_WORDS
Next - check if the random number is in the numList vector we created earlier
	if it's not in the vector, then add the random number to numList
	if it is in the vector, then ignore and generate another random number
The end result is a vector of integers between 0 and NUMBER_OF_WORDS that do not repeat.
These random numbers will be used to place the words in a random order for the quiz
while also ensuring the words do not repeat */  //I may have made this more complicated than it needed to be...


vector<int> random_numbers_vector(int max) {

	vector<int> numList;  //create an empty vector

	for (int i = 0; i < max;) { //i will only increment if value is not in vector

		int r = random_int(0, max);  //generate a random number between min (0) and max using the random_int function

		if (!(search_list(r, numList))) {  //use search_list function to check if number 'r' is not already in vector
			numList.push_back(r); //if r is not already in vector then add to vector using push_back
			i++;
		}
	}
	//cout << "Vector successfully created." << endl;
	return numList;
}


int random_int(int min, int max) {  //generate a random integer between min and max parameters

	int x;
	x = rand() % max + min;  //add the min to ensures that the random number is above the minimum (min always = 0 for now)

	//cout << "\n\n\n**********SEARCHING FOR " << x << " ********************" << endl << endl << endl;

	return x;
}

bool search_list(int searchfor, vector<int> numbers) {  //search a vector for a specific number, returns true if found;

	bool found = false; //flag to indicate if value was found in vector, default is false
	int index = 0; //to keep track of index
	int numElems = numbers.size(); //returns the number of elements in the numbers vector

	while (index < numElems && !found) {

		if (numbers[index] == searchfor) {

			found = true;
			return found;
		}
		else {

			index++;

		}
	} //after going through each index value and if searchfor was not found then return found as false

	return found;
}
