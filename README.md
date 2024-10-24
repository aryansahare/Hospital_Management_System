# Hospital-Management-System

## 1. Introduction
The Hospital Management System (HMS) is a C++ application designed to streamline hospital operations, including staff and patient management. It enables efficient handling of doctors, nurses, and patients with features for adding, deleting, and editing records.

## 2. Objectives
- **Staff Management**: Manage doctor and nurse details, roles, and assignments.
- **Patient Management**: Register, track, and update patient information.
- **User Access Control**: Password protection to secure staff management features.
- **Information Display**: View comprehensive staff and patient details.

## 3. Key Features
- **Staff Management**: Add, edit, and delete doctors and nurses; manage shifts and specializations.
- **Patient Management**: Register patients, update details, and assign doctors based on specialization.
- **Password Protection**: Secured access to prevent unauthorized changes.
- **Data Storage**: Uses dynamic memory allocation for managing data.

## 4. Technical Architecture
- **Programming Language**: C++
- **Object-Oriented Design**: Structured using classes like `Person`, `Staff`, `Doctor`, `Nurse`, `Patient`.
- **Dynamic Memory**: Managed using `new` and `delete`.

## 5. Class Structure
- **Person**: Base class with attributes like name, age, and gender.
- **Staff**: Inherits from `Person`, adds staff ID, salary.
- **Doctor/Nurse**: Specialized staff classes with additional attributes.
- **Patient**: Inherits from `Person` and adds medical history and patient ID.
- **HospitalManagementSystem**: Manages doctors, nurses, and patients.

## 6. Implementation
- **Default Data**: Initializes with default records for demonstration.
- **Interaction**: A text-based menu allows easy navigation and operation.

## 7. Future Enhancements
- **Database Integration**: Persistent storage for scalability.
- **GUI**: Add graphical interface for better usability.
- **Enhanced Security**: Role-based access control.
- **New Features**: Appointment scheduling and billing.

## 8. How to Use (Linux)
1. Clone the repository:
   ```
   git clone https://github.com/aryansahare/Hospital_Management_System

   g++ main.cpp -o main

   ./main
   ```
