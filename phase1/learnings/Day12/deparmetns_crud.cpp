#include <iostream>
#include <cstring>
#define MAX_DEPTS 100

class Department 
{
    private:
        int _id;
        char _name[255];
    public:
        Department(int id = 0, const char name[] = "");
        void SetId(int id);
        int GetId();
        void SetName(const char name[]);
        char* GetName();
};

class DepartmentManager
{
    private:
        Department _departments[MAX_DEPTS];
        int _departmentCount;
    public:
        DepartmentManager();
        void Create(Department& department);
        void Update(int id, Department& department);
        void Delete(int id);
        Department* ReadAll();
        Department ReadById(int id);
        int GetDepartmentCount() const;
};

class DepartmentUI 
{
    private:
        DepartmentManager departmentManager;
    public:
        void CreateUI();
        void UpdateUI();
        void DeleteUI();
        void DisplayAll();
};

int main() 
{
    DepartmentUI ui;
    int choice;

    do 
    {
        std::cout << "\nDepartment Management System\n";
        std::cout << "1. Create Department\n";
        std::cout << "2. Update Department\n";
        std::cout << "3. Delete Department\n";
        std::cout << "4. Display All Departments\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) 
        {
            case 1: ui.CreateUI(); break;
            case 2: ui.UpdateUI(); break;
            case 3: ui.DeleteUI(); break;
            case 4: ui.DisplayAll(); break;
            case 5: std::cout << "Exiting...\n"; break;
            default: std::cout << "Invalid choice!\n";
        }
    } while (choice != 5);

    return 0;
}

// Department class member functions
Department::Department(int id, const char name[]) 
{
    _id = id;
    strcpy(_name, name);
}

void Department::SetId(int id) { _id = id; }
int Department::GetId() { return _id; }
void Department::SetName(const char name[]) { strcpy(_name, name); }
char* Department::GetName() { return _name; }

// DepartmentManager class member functions
DepartmentManager::DepartmentManager() : _departmentCount(0) {}

void DepartmentManager::Create(Department& department) 
{
    if (_departmentCount < MAX_DEPTS) 
    {
        _departments[_departmentCount++] = department;
    }
}

void DepartmentManager::Update(int id, Department& department) 
{
    for (int i = 0; i < _departmentCount; ++i) 
    {
        if (_departments[i].GetId() == id) 
        {
            _departments[i] = department;
            return;
        }
    }
}

void DepartmentManager::Delete(int id) 
{
    for (int i = 0; i < _departmentCount; ++i) 
    {
        if (_departments[i].GetId() == id) 
        {
            for (int j = i; j < _departmentCount - 1; ++j) 
            {
                _departments[j] = _departments[j + 1];
            }
            --_departmentCount;
            return;
        }
    }
}

Department* DepartmentManager::ReadAll() { return _departments; }

Department DepartmentManager::ReadById(int id) 
{
    for (int i = 0; i < _departmentCount; ++i) 
    {
        if (_departments[i].GetId() == id) 
        {
            return _departments[i];
        }
    }
    return Department(); // Return default if not found
}

int DepartmentManager::GetDepartmentCount() const { return _departmentCount; }

// DepartmentUI class member functions
void DepartmentUI::CreateUI() 
{
    int id;
    char name[255];
    std::cout << "Enter Department ID: ";
    std::cin >> id;
    std::cout << "Enter Department Name: ";
    std::cin.ignore();
    std::cin.getline(name, 255);

    Department department(id, name);
    departmentManager.Create(department);
    std::cout << "Department created successfully!\n";
}

void DepartmentUI::UpdateUI() 
{
    int id;
    char name[255];
    std::cout << "Enter Department ID to Update: ";
    std::cin >> id;

    Department existing = departmentManager.ReadById(id);
    if (existing.GetId() == 0) 
    {
        std::cout << "Department not found!\n";
        return;
    }

    std::cout << "Existing Name: " << existing.GetName() << "\n";
    std::cout << "Enter New Name: ";
    std::cin.ignore();
    std::cin.getline(name, 255);

    Department updated(id, name);
    departmentManager.Update(id, updated);
    std::cout << "Department updated successfully!\n";
}

void DepartmentUI::DeleteUI() 
{
    int id;
    std::cout << "Enter Department ID to Delete: ";
    std::cin >> id;

    Department existing = departmentManager.ReadById(id);
    if (existing.GetId() == 0) 
    {
        std::cout << "Department not found!\n";
        return;
    }

    std::cout << "Are you sure you want to delete '" << existing.GetName() << "'? (y/n): ";
    char confirm;
    std::cin >> confirm;

    if (confirm == 'y' || confirm == 'Y') 
    {
        departmentManager.Delete(id);
        std::cout << "Department deleted successfully!\n";
    }
}

void DepartmentUI::DisplayAll() 
{
    Department* departments = departmentManager.ReadAll();
    int count = departmentManager.GetDepartmentCount();

    std::cout << "Departments:\n";
    for (int i = 0; i < count; ++i) 
    {
        std::cout << "ID: " << departments[i].GetId()
                  << ", Name: " << departments[i].GetName() << "\n";
    }
}


/*
Output::

Department Management System
1. Create Department
2. Update Department
3. Delete Department
4. Display All Departments
5. Exit
Enter your choice: 1
Enter Department ID: 10
Enter Department Name: Alpha
Department created successfully!

Department Management System
1. Create Department
2. Update Department
3. Delete Department
4. Display All Departments
5. Exit
Enter your choice: 1
Enter Department ID: 20
Enter Department Name: Beta
Department created successfully!

Department Management System
1. Create Department
2. Update Department
3. Delete Department
4. Display All Departments
5. Exit
Enter your choice: 3 1
Enter Department ID: 30
Enter Department Name: GAmma     Gamma
Department created successfully!

Department Management System
1. Create Department
2. Update Department
3. Delete Department
4. Display All Departments
5. Exit
Enter your choice: 4
Departments:
ID: 10, Name: Alpha
ID: 20, Name: Beta
ID: 30, Name: Gamma

Department Management System
1. Create Department
2. Update Department
3. Delete Department
4. Display All Departments
5. Exit
Enter your choice: 2
Enter Department ID to Update: 1 20
Existing Name: Beta
Enter New Name: Beta Plus
Department updated successfully!

Department Management System
1. Create Department
2. Update Department
3. Delete Department
4. Display All Departments
5. Exit
Enter your choice: 3
Enter Department ID to Delete: 40
Department not found!

Department Management System
1. Create Department
2. Update Department
3. Delete Department
4. Display All Departments
5. Exit
Enter your choice: 3
Enter Department ID to Delete: 50
Department not found!

Department Management System
1. Create Department
2. Update Department
3. Delete Department
4. Display All Departments
5. Exit
Enter your choice: 1
Enter Department ID: 40
Enter Department Name: H
Department created successfully!

Department Management System
1. Create Department
2. Update Department
3. Delete Department
4. Display All Departments
5. Exit
Enter your choice: 3 4
Departments:
ID: 10, Name: Alpha
ID: 20, Name: Beta Plus
ID: 30, Name: Gamma
ID: 40, Name: H

Department Management System
1. Create Department
2. Update Department
3. Delete Department
4. Display All Departments
5. Exit
Enter your choice: 3
Enter Department ID to Delete: 40
Are you sure you want to delete 'H'? (y/n): y
Department deleted successfully!

Department Management System
1. Create Department
2. Update Department
3. Delete Department
4. Display All Departments
5. Exit
Enter your choice: 4
Departments:
ID: 10, Name: Alpha
ID: 20, Name: Beta Plus
ID: 30, Name: Gamma

Department Management System
1. Create Department
2. Update Department
3. Delete Department
4. Display All Departments
5. Exit
Enter your choice: 5

 */