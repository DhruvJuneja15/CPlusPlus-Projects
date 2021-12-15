#include <iostream>
#include <fstream>
using namespace std;

// This class stores information about patient
class patient
{
private:
    char name[60];
    unsigned long long int aadhar;
    char gender;
    unsigned int age;
    char type[20];
    char dose;
    char mobile[11];

public:
    // method declaration
    void getdetails();
    void showdetails() const; //const is used so that this method can be called on both const and non-const objects
    unsigned long long int retaadhar() const;
    char retdose() const;
    // end of class
};

void patient ::getdetails()
{
    cout << "\nEnter the name of patient : ";
    cin.ignore(); //clears input buffer
    cin.getline(name, 60);
    cout << "\nEnter aadhar number : ";
    cin >> aadhar;
    cout << "\nEnter patient's gender(M/F/O) : "; //M-Male, F-Female, O-Others
    cin >> gender;
    cout << "\nEnter patient's age : ";
    cin >> age;
    cout << "\nEnter the type of vaccine(Covaxin/Covishield) : ";
    cin >> type;
    cout << "\nEnter the dose number(1/2) : ";
    cin >> dose;
    cout << "\nEnter the mobile number(+91) : ";
    cin >> mobile;
}

void patient ::showdetails() const
{
    cout << "\nName of patient : " << name;
    cout << "\nAadhar number : " << aadhar;
    cout << "\nGender : " << gender;
    cout << "\nAge : " << age;
    cout << "\nVaccine Type : " << type;
    cout << "\nNumber of Dose : " << dose;
    cout << "\nMobile Number : " << mobile;
}

unsigned long long int patient ::retaadhar() const
{
    return aadhar;
}

char patient ::retdose() const
{
    return dose;
}

// function declaration
void createPatient();
void displayPatient(unsigned long long int);
void displayAll();
void deletePatient(unsigned long long int);
void changePatient(unsigned long long int);

// Driver function
int main()
{
    char ch;
    unsigned long long int number;
    system("cls"); // clears the screen
    cout << "\n\n\t\tWelcome to Vaccine Management System\n";
    do
    {
        cout << "\n\n\tOptions : ";
        cout << "\n\n1. Create new patient record";
        cout << "\n\n2. Search a patient's record";
        cout << "\n\n3. Display the record of all patients";
        cout << "\n\n4. Modify a patient's record";
        cout << "\n\n5. Delete a patient's record";
        cout << "\n\n6. Exit";
        cout << "\n\nEnter your choice(1/2/3/4/5/6) : ";
        cin >> ch;
        system("cls");
        switch (ch)
        {
        case '1':
            createPatient();
            break;
        case '2':
            cout << "\n\nEnter the aadhar number of patient : ";
            cin >> number;
            displayPatient(number);
            break;
        case '3':
            displayAll();
            break;
        case '4':
            cout << "\n\nEnter the aadhar number of patient : ";
            cin >> number;
            changePatient(number);
            break;
        case '5':
            cout << "\n\nEnter the aadhar number of patient : ";
            cin >> number;
            deletePatient(number);
            break;
        case '6':
            cout << "\n\n\tEnd of the program\n\tThank You!\n\n";
            exit(0); //successfully exits the program
        default:
            cout << "\n\nNo such choice availabe.\nPlease enter the right choice";
        }
    } while (ch != '6');
    return 0;
}

// functions definition :
// Option-1 : Creating a new patient
void createPatient()
{
    patient pnt;
    pnt.getdetails();
    ofstream out;
    if (pnt.retdose() == '1')
    {
        out.open("VaccineDose1.dat", ios ::binary | ios::app);      //opens the file in binary format and appends the detail of patient retaining previous content
        out.write(reinterpret_cast<char *>(&pnt), sizeof(patient)); //converts struct pointer to chae pointer and write the details of patient in file
        out.close();
    }
    ofstream out2;
    if (pnt.retdose() == '2')
    {
        out2.open("VaccineDose2.dat", ios ::binary | ios::app);      //opens the file in binary format and appends the detail of patient retaining previous content
        out2.write(reinterpret_cast<char *>(&pnt), sizeof(patient)); //converts struct pointer to chae pointer and write the details of patient in file
        out2.close();
    }
    cout << "\n\nPatient record has been created.";
    cin.ignore(); //removes input buffer like enter;
    cout << "\n\nPress any key to display Options.";
    cin.get();
    system("cls");
}

// Option-2 : Search for a particular patient's record
void displayPatient(unsigned long long int num)
{
    patient pnt;
    ifstream in;
    in.open("VaccineDose1.dat", ios::binary);
    bool found1 = false;
    if (!in)
    {
        cout << "\n\nFile Dose 1 could not be opened!!!\n\n";
        goto dose2;
    }
    while (in.read(reinterpret_cast<char *>(&pnt), sizeof(patient)))
    {
        if (pnt.retaadhar() == num)
        {
            pnt.showdetails();
            found1 = true;
        }
    }
    if (found1 == false)
    {
        cout << "\n\nNot in patients who have received Dose 1.\n\n";
    }
dose2:
    ifstream in2;
    in2.open("VaccineDose2.dat", ios::binary);
    if (!in2)
    {
        cout << "\n\nFile Dose 2 could not be opened!!!";
        cin.ignore();
        cout << "\n\nPress any key to display Options.";
        cin.get();
        system("cls");
        return;
    }
    // Display patient from Dose 2 file
    bool found2 = false;
    while (in2.read(reinterpret_cast<char *>(&pnt), sizeof(patient)))
    {
        if (pnt.retaadhar() == num)
        {
            pnt.showdetails();
            found2 = true;
        }
    }
    if (found2 == false)
    {
        cout << "\n\nNot in patients who have received Dose 2.\n";
    }
    cin.ignore();
    cout << "\n\nPress any key to display Options.";
    cin.get();
    system("cls");
    return;
}

//Option-3 : Display the record of all patients :
void displayAll()
{
    patient pnt;
    ifstream in;
    in.open("VaccineDose1.dat", ios::binary);
    if (!in)
    {
        cout << "\n\nFile Dose 1 could not be opened!!!\n\n";
        goto dose3;
    }
    cout << "\n\n\tHere is the record of all patients\n\n";
    cout << "\n\nPatients who have received Dose 1 : \n\n";
    while (in.read(reinterpret_cast<char *>(&pnt), sizeof(patient)))
    {
        pnt.showdetails();
        cout << "\n\n**************************************\n";
    }
    in.close();

dose3:
    ifstream in2;
    in2.open("VaccineDose2.dat", ios::binary);
    if (!in2)
    {
        cout << "\n\nFile Dose 2 could not be opened!!!\n";
        cin.ignore();
        cout << "\n\nPress any key to display Options.";
        cin.get(); //accepts input from user to exit from this option
        system("cls");
        return;
    }
    cout << "\n\nPatients who have received Dose 2 : \n\n";
    while (in2.read(reinterpret_cast<char *>(&pnt), sizeof(patient)))
    {
        pnt.showdetails();
        cout << "\n\n\t************************************************\n";
    }
    in.close();
    cin.ignore();
    cout << "\n\nPress any key to display Options. ";
    cin.get();
    system("cls");
}

// Option - 4 : Update Patient's Information
void changePatient(unsigned long long int num)
{
    patient pnt;
    bool found1 = false;
    fstream rw; //fstream is used as we have to do both read and write operations
    rw.open("VaccineDose1.dat", ios::binary | ios::in | ios::out);
    if (!rw)
    {
        cout << "\n\nFile about Dose 1 patients cannot be opened!!!\n";
        cin.ignore();
        goto dose4;
    }
    while (!rw.eof() && found1 == false)
    {
        rw.read(reinterpret_cast<char *>(&pnt), sizeof(patient));
        if (pnt.retaadhar() == num)
        {
            cout << "\n\nThe existing details of patient in Dose 1 file are : \n\n";
            pnt.showdetails();
            cout << "\n\nEnter the new details of the patient to be enterted in Dose 1 file: \n\n";
            pnt.getdetails();
            int pos = (-1) * static_cast<int>(sizeof(pnt)); //pos contains the position where details of required patient started
            rw.seekp(pos, ios::cur);
            rw.write(reinterpret_cast<char *>(&pnt), sizeof(patient));
            cout << "\n\n\tRecord Updated in Dose 1 file.\n\n";
            found1 = true;
        }
    }
    rw.close();
    if (found1 == false)
    {
        cout << "\n\nRecord not found in Dose 1 file.";
    }

// Updation in Dose 2 File :
dose4:
    bool found2 = false;
    fstream rw2; //fstream is used as we have to do both read and write operations
    rw2.open("VaccineDose2.dat", ios::binary | ios::in | ios::out);
    if (!rw2)
    {
        cout << "\n\nFile about Dose 2 patients cannot be opened!!!\n";
        cout << "\n\nPress any key to display Options. ";
        cin.get();
        system("cls");
        return;
    }
    while (!rw2.eof() && found2 == false)
    {
        rw2.read(reinterpret_cast<char *>(&pnt), sizeof(patient));
        if (pnt.retaadhar() == num)
        {
            cout << "\n\nThe existing details of patient are in Dose 2 file are: \n\n";
            pnt.showdetails();
            cout << "\n\nEnter the new details of the patient to be entered in Dose 2 file: \n\n";
            pnt.getdetails();
            int pos = (-1) * static_cast<int>(sizeof(pnt)); //pos contains the position where details of required patient started
            rw2.seekp(pos, ios::cur);                       //seekp takes cursor from cur position to pos position
            rw2.write(reinterpret_cast<char *>(&pnt), sizeof(patient));
            cout << "\n\n\tRecord Updated in Dose 2 file.";
            found2 = true;
        }
    }
    rw2.close();
    if (found2 == false)
    {
        cout << "\n\nRecord not found in Dose 2 file.\n";
    }
    cin.ignore();
    cout << "\n\nPress any key to display Options. ";
    cin.get();
    system("cls");
}

// Option-5 Delete a patient's record
void deletePatient(unsigned long long int num)
{
    patient pnt;
    // deleting Patient's data from dose 1 file
    ifstream in;
    in.open("VaccineDose1.dat", ios::binary);
    ofstream out;
    if (!in)
    {
        cout << "\n\nFile about Dose 1 patients cannot be opened!!!\n";
        cin.ignore();
        goto dose5;
    }
    out.open("Temp1.dat", ios::out);
    in.seekg(0, ios::beg); //place cursor at beginning of the Dose1 file
    while (in.read(reinterpret_cast<char *>(&pnt), sizeof(patient)))
    {
        //Copying data from Dose 1 file to Temp file
        if (pnt.retaadhar() != num)
        {
            out.write(reinterpret_cast<char *>(&pnt), sizeof(patient));
        }
    }
    out.close();
    in.close();
    remove("VaccineDose1.dat"); //deleting Dose 1 file
    rename("Temp1.dat", "VaccineDose1.dat");
    cout << "\n\nRecord deleted from Dose 1 file.";

dose5:
    // deleting Patient's data from dose 2 file
    ifstream in2;
    in2.open("VaccineDose2.dat", ios::binary);
    if (!in2)
    {
        cout << "\n\nFile about Dose 2 patients cannot be opened!!!\n";
        cin.ignore();
        cout << "\n\nPress any key to display Options. ";
        cin.get();
        system("cls");
        return;
    }
    ofstream out2;
    out2.open("Temp2.dat", ios::out);
    in2.seekg(0, ios::beg); //place cursor at beginning of the Dose1 file
    while (in2.read(reinterpret_cast<char *>(&pnt), sizeof(patient)))
    {
        //Copying data from Dose 1 file to Temp file
        if (pnt.retaadhar() != num)
        {
            out2.write(reinterpret_cast<char *>(&pnt), sizeof(patient));
        }
    }
    out2.close();
    in2.close();
    remove("VaccineDose2.dat"); //deleting Dose 2 file
    rename("Temp2.dat", "VaccineDose2.dat");
    cout << "\n\nRecord deleted from Dose 2 file.";
    cout << "\n\nPress any key to display Options. ";
    cin.get();
    system("cls");
    return;
}
