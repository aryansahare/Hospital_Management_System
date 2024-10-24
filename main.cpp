#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

void clearScreen() {
    system("cls");
}

class Person {
public:
    string name;
    int age;
    string gender;

    Person(string name, int age, string gender)
        : name(name), age(age), gender(gender) {}

    virtual void showdetails() const {
        cout << "Name: " << name << "\n" << "Age: " << age << "\n" << "Gender: " << gender << "\n";
    }

    virtual ~Person() {}  // destructor
};

class Staff : public Person {
protected:
    string staffID;
    int salary;

public:
    Staff(string name, int age, string gender, string staffID, int salary)
        : Person(name, age, gender), staffID(staffID), salary(salary) {}

    virtual ~Staff() {}  // destructor

    virtual void showdetails() const override {
        Person::showdetails();
        cout << "Staff ID: " << staffID << "\n"
             << "Salary: " << salary << "\n";
    }

    void setsalary(int newSalary) {
        salary = newSalary;
    }

    string getStaffID() const {
        return staffID;
    }
};

class Doctor : public Staff {
private:
    string specialization;
    string shiftDays;

public:
    Doctor(string name, int age, string gender, string staffID, int salary, string specialization, string shiftDays)
        : Staff(name, age, gender, staffID, salary), specialization(specialization), shiftDays(shiftDays) {}

    void showdetails() const override {
        Staff::showdetails();
        cout << "Doctor Specialization: " << specialization << "\n"
             << "Doctor Shift Days: " << shiftDays << "\n";
    }

    string getSpecialization() const {
        return specialization;
    }

    string getname() const {
        return name;
    }
};

class Nurse : public Staff {
private:
    string shifttiming;
    Doctor* assigneddoctor;

public:
    Nurse(string name, int age, string gender, string staffID, int salary, string shifttiming, Doctor* assigneddoctor)
    : Staff(name, age, gender, staffID, salary), shifttiming(shifttiming), assigneddoctor(assigneddoctor) {}

    void showdetails() const override {
        Staff::showdetails();
        cout << "Shift Timing: " << shifttiming << "\n";
        if (assigneddoctor != nullptr) {
            cout << "Assigned Doctor: " << assigneddoctor->name << "\n";
        } else {
            cout << "No doctor assigned.\n";
        }
    }

    // void assignDoctor(Doctor* doctor) {
    //     assigneddoctor = doctor;
    // }
};

class Patient : public Person {
private:
    string disease;
    string patientID;

public:
    
    Patient(string name, int age, string gender, string disease, string patientID)
        : Person(name, age, gender), disease(disease), patientID(patientID) {}

    void showdetails() const override {
        Person::showdetails();
        cout << "Disease: " << disease << "\n"
             << "Patient ID: " << patientID << "\n";
    }

    string getPatientID() const {
        return patientID;
    }

    string getPatientDisease() const {
        return disease;
    }

    void setDetails(string newName, int newAge, string newGender, string newDisease) {
        name = newName;
        age = newAge;
        gender = newGender;
        disease = newDisease;
    }
};

class HospitalManagementSystem{
private:
	string password;

public:
    Doctor* doctors[10];  // Array of doctors (max 10)
    Nurse* nurses[10];    // Array of nurses (max 10)
    Patient* patients[10]; // Array of patients (max 10)
    int Doctorcount;
    int NurseCount;
    int patientCount;
    


    HospitalManagementSystem(string initPassword)
        : Doctorcount(2), NurseCount(2), patientCount(2), password(initPassword) {}

    bool checkPassword(string inputPassword) {
        return inputPassword == password;
    }

    void Defaultdoc(void){
        doctors[0]=new Doctor("Stacy", 45, "Female", "D001", 100000, "Cancer", "Mon-Wed");
        doctors[1]=new Doctor("Ravi", 55, "Male", "D002", 50000, "Ear specialist", "Wed-fri");
    }

    void AddDoctor(Doctor* doctor) {
        if (Doctorcount < 10) {
            doctors[Doctorcount++] = doctor;
            cout << "Doctor added successfully.\n";
        } else {
            cout << "Cannot add more doctors, array is full.\n";
        }
    }

    Doctor* GetDoctorByName(string name){
        for (int i = 0; i < Doctorcount; i++) {
            if (doctors[i]->getname() == name) {
                return doctors[i];
            }
        }
        return nullptr;
    }

    void Defaultnurse(void){
        nurses[0]=new Nurse("Sheetal", 25, "Female", "N001", 25000, "9am-5pm", GetDoctorByName("Ravi"));
        nurses[1]=new Nurse("Gurpreet", 55, "Feale", "N002", 50000, "9am-5pm", GetDoctorByName("Ravi"));
    }
    void AddNurse(Nurse* nurse) {
        if (NurseCount < 10) {
            nurses[NurseCount++] = nurse;
            cout << "Nurse added successfully.\n";
        } else {
            cout << "Cannot add more nurses, array is full.\n";
        }
    }

    void DeleteDoctor(string staffID) {
        for (int i = 0; i < Doctorcount; i++) {
            if (doctors[i]->getStaffID() == staffID) {
                delete doctors[i];  // Free the memory
                for (int j = i; j < Doctorcount - 1; ++j) {
                    doctors[j] = doctors[j + 1];
                }
                Doctorcount--;
                cout << "Doctor deleted successfully.\n";
                return;
            }
        }
        cout << "Doctor not found.\n";
    }

    void DeleteNurse(string staffID) {
        for (int i = 0; i < NurseCount; ++i) {
            if (nurses[i]->getStaffID() == staffID) {
                delete nurses[i];  // Free the memory
                for (int j = i; j < NurseCount - 1; ++j) {
                    nurses[j] = nurses[j + 1];
                }
                NurseCount--;
                cout << "Nurse deleted successfully.\n";
                return;
            }
        }
        cout << "Nurse not found.\n";
    }

    void editStaff(string staffID) {
        for (int i = 0; i < Doctorcount; ++i) {
            if (doctors[i]->getStaffID() == staffID) {
                string newName, newGender, newSpecialization, newShiftDays;
                int newAge, newSalary;
                cout << "Enter new name: ";
                cin >> newName;
                cout << "Enter new age: ";
                cin >> newAge;
                cout << "Enter new gender: ";
                cin >> newGender;
                cout << "Enter new specialization: ";
                cin >> newSpecialization;
                cout << "Enter new shift days: ";
                cin >> newShiftDays;
                cout << "Enter new salary: ";
                cin >> newSalary;
                doctors[i] = new Doctor(newName, newAge, newGender, staffID, newSalary, newSpecialization, newShiftDays);
                cout << "Doctor details updated successfully.\n";
                return;
            }
        }
        for (int i = 0; i < NurseCount; ++i) {
            if (nurses[i]->getStaffID() == staffID) {
                string newName, newGender, newShiftTiming,docname;
                int newAge, newSalary;
                cout << "Enter new name: ";
                cin >> newName;
                cout << "Enter new age: ";
                cin >> newAge;
                cout << "Enter new gender: ";
                cin >> newGender;
                cout << "Enter new shift timing: ";
                cin >> newShiftTiming;
                cout << "Enter new salary: ";
                cin >> newSalary;
                cout << "Enter new doctor to be assigned to:";
                cin >> docname;
                nurses[i] = new Nurse(newName, newAge, newGender, staffID, newSalary, newShiftTiming , GetDoctorByName(docname));
                cout << "Nurse details updated successfully.\n";
                return;
            }
        }
        cout << "Staff not found.\n";
    }

    void showStaffDetails() const {
        cout << "\n--- Doctors ---\n";
        for (int i = 0; i < Doctorcount; ++i) {
            doctors[i]->showdetails();
            cout << "\n";
        }

        cout << "\n--- Nurses ---\n";
        for (int i = 0; i < NurseCount; i++) {
            nurses[i]->showdetails();
            cout << "\n";
        }
    }

    Doctor* GetDoctorBySpecialization(string specialization) {
        for (int i = 0; i < Doctorcount; i++) {
            if (doctors[i]->getSpecialization() == specialization) {
                return doctors[i];
            }
        }
        return nullptr;
    }



    // Patient Management
    void Defaultpatient(void){
        patients[0]=new Patient("Aryan", 20, "Male", "Cancer", "P001");
        patients[1]=new Patient("Anvesha", 18, "Female", "Lukemia", "P002");
       
    }

    void AddPatient(Patient* patient) {
        if (patientCount < 10) {
            patients[patientCount++] = patient;
            cout << "Patient added successfully.\n";
        } else {
            cout << "Cannot add more patients, array is full.\n";
        }
    }

    void DeletePatient(string patientID) {
        for (int i = 0; i < patientCount; i++) {
            if (patients[i]->getPatientID() == patientID) {
                delete patients[i];  // Free the memory
                for (int j = i; j < patientCount - 1; ++j) {
                    patients[j] = patients[j + 1];
                }
                patientCount--;
                cout << "Patient deleted successfully.\n";
                return;
            }
        }
        cout << "Patient not found.\n";
    }

    void showPatientDetails() const {
        cout << "\n--- Patients ---\n";
        for (int i = 0; i < patientCount; ++i) {
            patients[i]->showdetails();
            cout << "\n";
        }
    }

    void editPatientDetails(string patientID) {
        for (int i = 0; i < patientCount; ++i) {
            if (patients[i]->getPatientID() == patientID) {
                string newName, newGender, newDisease;
                int newAge;
                cout << "Enter new name: ";
                cin >> newName;
                cout << "Enter new age: ";
                cin >> newAge;
                cout << "Enter new gender: ";
                cin >> newGender;
                cout << "Enter new disease: ";
                cin >> newDisease;
                patients[i]->setDetails(newName, newAge, newGender, newDisease);
                cout << "Patient details updated successfully.\n";
                return;
            }
        }
        cout << "Patient not found.\n";
    }

};

int main() {
    HospitalManagementSystem hms("admin123");  // Password
    hms.Defaultdoc();
    hms.Defaultnurse();
    hms.Defaultpatient();
    int choice;
    
    while (1) {
       
        clearScreen();
        cout << "\n=== WELCOME TO HOSPITAL MANAGEMENT SYSTEM ===\n";
        cout << "What do you want to do:\n";
        cout << "1. Manage Staff\n";
        cout << "2. Manage Patients\n";
        cout << "3. Exit\n";
        cout << "================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            clearScreen();
            cout << "\n--- Staff Page ---\n";
            string inputPassword;
            cout << "Enter password to manage staff: ";
            cin >> inputPassword;

            if (hms.checkPassword(inputPassword)) {
                while (1){
                    clearScreen();
                    int staffChoice;
                    cout << "Staff Management:\n";
                    cout << "1. Add Doctor\n";
                    cout << "2. Add Nurse\n";
                    cout << "3. Delete Doctor\n";
                    cout << "4. Delete Nurse\n";
                    cout << "5. Edit Staff\n";
                    cout << "6. Show Staff Details\n";
                    cout << "7. Go back to main menu\n";
                    cout << "Enter your choice: ";
                    cin >> staffChoice;

                    if (staffChoice == 1) {
                        string name, gender, specialization, shiftDays, staffID;
                        int age, salary;
                        cout << "Enter name: ";
                        cin >> name;
                        cout << "Enter age: ";
                        cin >> age;
                        cout << "Enter gender: ";
                        cin >> gender;
                        cout << "Enter specialization: ";
                        cin >> specialization;
                        cout << "Enter shift days: ";
                        cin >> shiftDays;
                        cout << "Enter staff ID: ";
                        cin >> staffID;
                        cout << "Enter salary: ";
                        cin >> salary;

                        Doctor* doctor = new Doctor(name, age, gender, staffID, salary, specialization, shiftDays);
                        hms.AddDoctor(doctor);
                        cout << "\n Press 0 to continue:";
                        int n;
                        cin >> n;

                    } else if (staffChoice == 2) {
                        string name, gender, shifttiming, staffID,docname;
                        int age, salary;
                        cout << "Enter name: ";
                        cin >> name;
                        cout << "Enter age: ";
                        cin >> age;
                        cout << "Enter gender: ";
                        cin >> gender;
                        cout << "Enter shift timing: ";
                        cin >> shifttiming;
                        cout << "Enter staff ID: ";
                        cin >> staffID;
                        cout << "Enter salary: ";
                        cin >> salary;

                        cout << "Enter the doctor name whom you want to assign to:";
                        cin >> docname;
                        Nurse* nurse = new Nurse(name, age, gender, staffID, salary, shifttiming,hms.GetDoctorByName(docname));
                        hms.AddNurse(nurse);
                        cout << "\n Press 0 to continue:";
                        int n;
                        cin >> n;

                    } 
                    else if (staffChoice == 3) {
                        string staffID;
                        cout << "Enter Doctor Staff ID to delete: ";
                        cin >> staffID;
                        hms.DeleteDoctor(staffID);
                        cout << "\n Press 0 to continue:";
                        int n;
                        cin >> n;                    
                    } 
                    else if (staffChoice == 4) {
                        string staffID;
                        cout << "Enter Nurse Staff ID to delete: ";
                        cin >> staffID;
                        hms.DeleteNurse(staffID);
                        cout << "\n Press 0 to continue:";
                        int n;
                        cin >> n;

                    } 
                    else if (staffChoice == 5) {
                        string staffID;
                        cout << "Enter Staff ID to edit: ";
                        cin >> staffID;
                        hms.editStaff(staffID);
                        cout << "\n Press 0 to continue:";
                        int n;
                        cin >> n;                    
                    } 
                    else if (staffChoice == 6) {
                        hms.showStaffDetails();
                        cout << "\n Press 0 to continue:";
                        int n;
                        cin >> n;                    
                    } 
                    else if (staffChoice == 7) {
                        break;
                    }
                }
            } 
            else {
                cout << "Incorrect password!\n";
            }
            
        } 
        else if (choice == 2) {
            while (1){
                clearScreen();
                cout << "\n--- Patient Page ---\n";
                int PatientChoice;
                cout << "Patient Management:\n";
                cout << "1. Register Patient\n";
                cout << "2. Delete Patient\n";
                cout << "3. Show Patient Details\n";
                cout << "4. Edit Patient Details\n";
                cout << "5. Assign Doctor by Specialization\n";
                cout << "6. Go back to main menu\n";
                cout << "Enter your choice: ";
                cin >> PatientChoice;

                if (PatientChoice == 1) {
                    string name, gender, disease, patientID;
                    int age;
                    cout << "Enter name: ";
                    cin >> name;
                    cout << "Enter age: ";
                    cin >> age;
                    cout << "Enter gender: ";
                    cin >> gender;
                    cout << "Enter disease: ";
                    cin >> disease;
                    cout << "Enter patient ID: ";
                    cin >> patientID;

                    Patient* patient = new Patient(name, age, gender, disease, patientID);
                    hms.AddPatient(patient);
                    cout << "Patient registered successfully.\n";
                    cout << "\n Press 0 to continue:";
                    int n;
                    cin >> n;                
                } 
                else if (PatientChoice == 2) {
                    string patientID;
                    cout << "Enter Patient ID to delete: ";
                    cin >> patientID;
                    hms.DeletePatient(patientID);
                    cout << "\n Press 0 to continue:";
                    int n;
                    cin >> n;                                
                } 
                else if (PatientChoice == 3) {
                    
                    hms.showPatientDetails();
                    cout << "\n Press 0 to continue:";
                    int n;
                    cin >> n;
                } else if (PatientChoice == 4) {
                    string patientID;
                    cout << "Enter Patient ID to edit: ";
                    cin >> patientID;
                    hms.editPatientDetails(patientID);
                    cout << "\n Press 0 to continue:";
                    int n;
                    cin >> n;                                
                } 
                
                else if (PatientChoice == 5) {
                    string patientID;
                    cout << "Enter Patient ID to assign a doctor: ";
                    cin >> patientID;
                    
                    for (int i = 0; i < 10; ++i) {
                        if (hms.patients[i]->getPatientID() == patientID) {

                            string disease = hms.patients[i]->getPatientDisease(); 
                            //string disease = "Cancer"; 
                            Doctor* doctor = hms.GetDoctorBySpecialization(disease);
                            if (doctor) {
                                cout << "Doctor " << doctor->name << " assigned to patient " << patientID << ".\n";
                            } else {
                                cout << "No doctor available with that specialization.\n";
                            }
                            break;
                        }
                    }


                    cout << "\n Press 0 to continue:";
                    int n;
                    cin >> n;
                } 
                else if (PatientChoice == 6) {
                    break;
                }
            }
        } else if (choice == 3) {
            break;
        } else {
            cout << "Invalid choice!\n";
        }
    }

    return 0;
}
