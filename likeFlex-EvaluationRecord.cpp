#include<iostream>
#include<fstream>
using namespace std;
class Helper
{
private:
public:
	static int stringLength(const char* string)
	{
		int length = 0;
		if (string == nullptr)
		{
			return 0;
		}
		while (*string != '\0')//derefrencing the string to get its length
		{
			length++;
			string++;
		}
		return length;
	}
	static char* StringCopy(char* string, char* tempstring)
	{//second one is being copied into first one 
		if (string != nullptr)
		{
			delete[] string;
		}
		int len = Helper::stringLength(tempstring);
		string = new char[len + 1];
		for (int i = 0; tempstring[i] != '\0'; i++)//deep copying data from one to another
		{
			string[i] = tempstring[i];
		}
		string[len] = '\0';
		return string;
	}
	static char* GetStringFromBuffer(char* buffer)
	{
		int strLen = Helper::stringLength(buffer);
		char* str = 0;
		if (strLen > 0)
		{
			str = new char[strLen + 1];
			str = StringCopy(str, buffer);
		}
		return str;
	}
};
class EvalReport
{
	friend void UpdateStatistics(EvalReport* studentlist);
private:
	static int noquizzes ;
	static int noassigments ;
	static int totalstudents ;

	char* rollNo;
	char* fname;
	char* lname;
	int* quizzes;
	int* assignments;
	int totalmarksofboth;

	static int* TOTALMARKS_QUIZZES;//work on this make it static or not
	static int* TOTALMARKS_ASSIGMENTS;
	static int* Total;
	static int* max;
	static int* min;
	static double* avg;
public:
	EvalReport();
	~EvalReport();
	void ReadEachStudentData(ifstream& fin);
	void PrintListView();
	bool wordFound(char[]);
	int findsubstring(char*, char*);

	char* getRollNo() { return rollNo; }
	char* getFName() { return fname; }
	char* getLName() { return lname; }
	void setQuizzes(int*);
	void setAssigments(int*);
	int* getQuizMarks() { return quizzes; }
	int* getAssignmentMarks() { return assignments; }
	int getTotal() { return totalmarksofboth; }

	static int GetTotalStudent() { return totalstudents; }
	static int GetQuizTotal() { return noquizzes; }
	static int GetAssigmentTotal() { return noassigments; }
	static int* GetTotal(){ return Total; }
	static int* getmax() {return max;}
	static int* getmin() { return min; }
	static double* getavg() { return avg; }

	EvalReport& operator=(EvalReport&);
	static 	void PrintStatistics();
	static void DeleteStaticData();
	static void ReadStaticDataFromFile(ifstream& fin);
};
int EvalReport::noquizzes = 0;
int EvalReport::noassigments = 0;
int EvalReport::totalstudents = 0;
int* EvalReport::Total = nullptr;
int* EvalReport::max = nullptr;
int* EvalReport::min = nullptr;
double* EvalReport::avg = nullptr;
int* EvalReport::TOTALMARKS_QUIZZES = nullptr;
int* EvalReport::TOTALMARKS_ASSIGMENTS = nullptr;
EvalReport::EvalReport()
{
	quizzes = nullptr;
	assignments = nullptr;
	rollNo = nullptr;
	fname = nullptr;
	lname = nullptr;
	totalmarksofboth = 0;
}
EvalReport::~EvalReport()
{
	
	delete[] rollNo;
	delete[] fname;
	delete[] lname;
	delete[] quizzes;
	delete[] assignments;
	
}
void EvalReport::DeleteStaticData()
{
	if (TOTALMARKS_QUIZZES)		delete[] TOTALMARKS_QUIZZES;
	if (TOTALMARKS_ASSIGMENTS)		delete[] TOTALMARKS_ASSIGMENTS;
	if (Total)		delete[] Total;
	if (max)		delete[] max;
	if (min)		delete[] min;
	if (avg)		delete[] avg;

}
void EvalReport::ReadEachStudentData(ifstream& fin)
{
	int noquizzes = EvalReport::GetQuizTotal();   
	int noassignments = EvalReport::GetAssigmentTotal();
	char* temp = new char[180];
	fin >> temp;
	rollNo = Helper::GetStringFromBuffer(temp);
	fin >> temp;
	fname = Helper::GetStringFromBuffer(temp);
	fin >> temp;
	lname = Helper::GetStringFromBuffer(temp);
	quizzes = new int[noquizzes];
	for (int i = 0; i < noquizzes; i++)
	{
		fin >> quizzes[i];
		totalmarksofboth += quizzes[i];

	}
	assignments = new int[noassignments];
	for (int i = 0; i < noassignments; i++)
	{
		fin >> assignments[i];
		totalmarksofboth += assignments[i];
	}
}
void EvalReport::PrintListView()
{
	cout << rollNo << "\t" << fname << " " << lname << "\t\t";
	for (int i = 0; i < noquizzes; i++)
	{
		cout << quizzes[i] << "\t";
	}
	for (int i = 0; i < noassigments; i++)
	{
		cout << assignments[i] << "\t";
	}
	cout << totalmarksofboth;
	cout << endl;
}
void EvalReport::ReadStaticDataFromFile(ifstream& fin)
{
	fin >> totalstudents;
	fin >> noquizzes;
	fin >> noassigments;

	TOTALMARKS_QUIZZES = new int[noquizzes];
	for (int i = 0; i < noquizzes; i++)
	{
		fin >> TOTALMARKS_QUIZZES[i];
	}

	TOTALMARKS_ASSIGMENTS = new int[noassigments];
	for (int i = 0; i < noassigments; i++)
	{
		fin >> TOTALMARKS_ASSIGMENTS[i];
	}
}
EvalReport* ReadDataFromFile(const char* fileName)
{
	ifstream fin(fileName);
	if (!fin)
	{
		cout << "Error opening file\n";
		return 0;
	}
	EvalReport::ReadStaticDataFromFile( fin);
	int size = EvalReport::GetTotalStudent();
	EvalReport* studentlist = new EvalReport[size];
	for (int i = 0; i < size; i++)
	{
		studentlist[i].ReadEachStudentData(fin);
	}
	return studentlist;

}
void  PrintAll(EvalReport* studentlist)
{
	cout << "Roll No.\t Name\t\t\t";
	for (int i = 0; i < EvalReport::GetQuizTotal(); i++)
	{
		cout << "Q" << i + 1 << "\t";
	}
	for (int i = 0; i < EvalReport::GetAssigmentTotal(); i++)
	{
		cout << "A" << i + 1 << "\t";
	}
	cout << "Total\n";	for (int i = 0; i < EvalReport::GetTotalStudent(); i++)
	{
		studentlist[i].PrintListView();
	}
}
int EvalReport::findsubstring(char* cstring1, char* cstring2)
{
	int check = 0;
	int strlen1 = Helper::stringLength(cstring1);
	int strlen2 = Helper::stringLength(cstring2);
	int j;
	bool found = false;
	int index = -1;
	for (int i = 0; i < strlen1; i++)
	{
		found = true;
		for (int j = 0; j < strlen2; j++)
		{
			if (cstring1[i + j] != cstring2[j])
			{
				found = false;
				break;
			}
		}
		if (found)
		{
			index = 0;
			break;
		}
	}
	return index;
}
bool EvalReport::wordFound(char searchword[3])
{
	if ((findsubstring(rollNo, searchword) == 0) || (findsubstring(fname, searchword) == 0) || (findsubstring(lname, searchword) == 0))
	{
		return true;
	}
	return false;
}
EvalReport** SearchStudentsByKeyWord(EvalReport* studentlist,  char searchword[3], int& searchcount)
{
	searchcount = 0;
	EvalReport** searchlist = new EvalReport * [EvalReport::GetTotalStudent()];
	
	for (int i = 0; i < EvalReport::GetTotalStudent(); i++)
	{
		if (studentlist[i].wordFound(searchword))
		{
			//searchlist[searchcount] = new EvalReport;
			searchlist[searchcount] = &studentlist[i];
			searchcount++;
		}
	}
	return searchlist;
}


void EvalReport::setQuizzes(int* quizzes)
{
	if (this->quizzes != nullptr)
	{
		delete[] this->quizzes;
	}
	this->quizzes = new int[noquizzes];
	for (int i = 0; i < noquizzes; i++)
	{
		this->quizzes[i] = quizzes[i];
	}
}
void EvalReport::setAssigments(int* assignments)
{
	if (this->assignments != nullptr)
	{
		delete[] this->assignments;
	}
	this->assignments = new int[noassigments];
	for (int i = 0; i < noassigments; i++)
	{
		this->assignments[i] = assignments[i];
	}
}
EvalReport& EvalReport::operator=(EvalReport& other)
{

	this->rollNo = Helper::StringCopy(this->rollNo, other.rollNo);
	this->fname = Helper::StringCopy(this->fname, other.fname);
	this->lname = Helper::StringCopy(this->lname, other.lname);
	this->totalmarksofboth = other.totalmarksofboth;
	if (other.quizzes != nullptr)
	{
		quizzes = new int[noquizzes];
		for (int i = 0; i < noquizzes; i++)
		{
			quizzes[i] = other.quizzes[i];
		}
	}
	else{	quizzes = nullptr;	}
	if (other.assignments != nullptr)
	{
		assignments = new int[noassigments];
		for (int i = 0; i < noassigments; i++)
		{
			assignments[i] = other.assignments[i];
		}
	}
	else{	assignments = nullptr;	}
	return *this;
}
void SortListByTotal(EvalReport* studentlist)
{
	int totalstudents = EvalReport::GetTotalStudent();
	for (int i = 0; i < totalstudents; i++)
	{
		for (int j = 0; j < totalstudents - 1; j++)
		{
			if (studentlist[j].getTotal() > studentlist[j + 1].getTotal())
			{
				EvalReport temp;
				temp = studentlist[j];
				studentlist[j] = studentlist[j + 1];
				studentlist[j + 1] = temp;
			}
		}
	}
}
int compareStrings(const char* str1, const char* str2)
{
	int check = 0;
	int strlen1 = Helper::stringLength(str1);
	int strlen2 = Helper::stringLength(str2);
	int j;
	for (j = 0; str1[j] != '\0' && str2[j] != '\0'; j++)
	{
		if (str1[j] < str2[j] || str1[j] > str2[j])
		{
			return -1;
		}
	}
	if (str1[j] == str2[j])
	{
		return 0;
	}
	return 1;
	/*while (*str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	return (*str1 == '\0' && *str2 == '\0');*/
}
void GetStudentInformationByRollNo(EvalReport* studentlist, const char* rollNo)
{
	int totalstudents = EvalReport::GetTotalStudent();
	bool found = false;
	for (int i = 0; i < totalstudents; i++)
	{
		if (compareStrings(studentlist[i].getRollNo(), rollNo) == 0)
		{
			cout << "Student Information:\n\n";
			cout << "Roll No:\t\t" << studentlist[i].getRollNo() << endl;
			cout << "Name:\t\t" << studentlist[i].getFName() << " " << studentlist[i].getLName() << endl;
			cout << "Quizzes Marks:\n";
			for (int j = 0; j < EvalReport::GetQuizTotal(); j++)
			{
				cout << "\tQ" << j + 1 << ":\t\t" << studentlist[i].getQuizMarks()[j] << "/10" << endl;
			}
			cout << "Assignment Marks:\n";
			for (int j = 0; j < EvalReport::GetAssigmentTotal(); j++)
			{
				cout << "\tA" << j + 1 << ":\t\t" << studentlist[i].getAssignmentMarks()[j] << "/10" << endl;
			}
			cout << "Total:\t\t\t" << studentlist[i].getTotal() << "/100" << endl;
			found = true;
			break;
		}
	}
	if (!found)
	{
		cout << "Student with roll number " << rollNo << " not found." << endl;
	}
}
void  PrintStudents(EvalReport** searchlist, const int searchcount)
{

	cout << "Roll No.\t Name\t\t";
	for (int i = 0; i < EvalReport::GetQuizTotal(); i++)
	{
		cout << "Q" << i + 1 << "\t";
	}
	for (int i = 0; i < EvalReport::GetAssigmentTotal(); i++)
	{
		cout << "A" << i + 1 << "\t";
	}
	cout << "Total\n";
	for (int i = 0; i < searchcount; i++)
	{
		searchlist[i]->PrintListView();
	}
}
void UpdateStatistics(EvalReport* studentlist)
{// we should use setters here
	if (!EvalReport::Total) { EvalReport::Total = new int[EvalReport::GetQuizTotal() + EvalReport::GetAssigmentTotal()]; };
	if (!EvalReport::max) EvalReport::max = new int[EvalReport::GetQuizTotal() + EvalReport::GetAssigmentTotal()]();
	if (!EvalReport::min) EvalReport::min = new int[EvalReport::GetQuizTotal() + EvalReport::GetAssigmentTotal()]();
	if (!EvalReport::avg) EvalReport::avg = new double[EvalReport::GetQuizTotal() + EvalReport::GetAssigmentTotal()]();

	for (int i = 0; i < EvalReport::GetQuizTotal(); i++) 
	{
		double sum = 0;
		EvalReport::getmax()[i] = 0;
		EvalReport::getmin()[i] = 10;
		for (int j = 0; j < EvalReport::GetTotalStudent(); j++)
		{
			int score = studentlist[j].getQuizMarks()[i];
			sum += score;
			if (score > EvalReport::getmax()[i])
				EvalReport::getmax()[i] = score;
			if (score < EvalReport::getmax()[i])
				EvalReport::getmin()[i] = score;
		}
		EvalReport::GetTotal()[i] = sum;
		EvalReport::getavg()[i] = sum / EvalReport::GetTotalStudent();
	}

	for (int i = 0; i < EvalReport::GetAssigmentTotal(); i++)
	{
		double sum = 0;
		EvalReport::getmax()[EvalReport::GetQuizTotal() + i] = 0;
		EvalReport::getmin()[EvalReport::GetQuizTotal() + i] = 10;
		for (int j = 0; j < EvalReport::GetTotalStudent(); j++) {
			int score = studentlist[j].getAssignmentMarks()[i];
			sum += score;
			if (score > EvalReport::getmax()[EvalReport::GetQuizTotal() + i])
				EvalReport::getmax()[EvalReport::GetQuizTotal() + i] = score;
			if (score < EvalReport::getmin()[EvalReport::GetQuizTotal() + i])
				EvalReport::getmin()[EvalReport::GetQuizTotal() + i] = score;
		}
		EvalReport::GetTotal()[EvalReport::GetQuizTotal() + i] = sum;
		EvalReport::getavg()[EvalReport::GetQuizTotal() + i] = sum / EvalReport::GetTotalStudent();
	}

}
 void EvalReport::PrintStatistics()
{
	 cout << "\t\t";
	 for (int i = 0; i < noquizzes; i++)
	 {
		 cout << "Q" << i + 1 << "\t";
	 }
	 for (int i = 0; i < noquizzes; i++)
	 {
		 cout << "A" << i + 1 << "\t";
	 }
	 cout << "\nTotal:\t\t";
	 for (int i = 0; i < noquizzes; i++)
	 {
		 cout << TOTALMARKS_QUIZZES[i] << "\t";

	 }
	 for (int i = 0; i < noassigments; i++)
	 {
		 cout << TOTALMARKS_ASSIGMENTS[i] << "\t";
	 }
	 cout << "\nMaximum:\t";
	 for (int i = 0; i < noquizzes + noassigments; i++)
	 {
		 cout << max[i] << "\t";
	 }
	 cout << "\nMinimum:\t";
	 for (int i = 0; i < noquizzes + noassigments; i++) {
		 cout << min[i] << "\t";
	 }
	 cout << "\nAverage:\t";
	 for (int i = 0; i < noquizzes + noassigments; i++) {
		 cout << EvalReport::avg[i] << "\t";
	 }
	 cout << endl;
	 cout << endl;

}
int main()
{
	EvalReport* studentlist = ReadDataFromFile("gradesheet.txt");
	if (studentlist)
	{
		UpdateStatistics(studentlist);
		EvalReport::PrintStatistics();
		PrintAll(studentlist);

		char searchword[3] = "43";
		int searchcount = 0;
		EvalReport** searchlist = SearchStudentsByKeyWord(studentlist, searchword, searchcount);

		cout << "\tThe data after seacrching word " << searchword << " is this:\n";
		PrintStudents(searchlist, searchcount);

		cout << "\n\t\tFunction after sorting is :\n";
		SortListByTotal(studentlist);
		PrintAll(studentlist);

		const char* rollNotofind = "15L-4221"; // Hardcoded roll number
		GetStudentInformationByRollNo(studentlist,  rollNotofind);

		studentlist->DeleteStaticData();

		delete[] studentlist;
		/*for (int i = 0; i < searchcount; i++)
		{
			delete searchlist[i];
		}*/
		delete[] searchlist;
	}
	cout << "Memory:" << _CrtDumpMemoryLeaks();
	return 0;
}