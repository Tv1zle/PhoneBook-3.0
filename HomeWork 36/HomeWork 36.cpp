#include <iostream>
#include <windows.h> 


class PhoneBook
{
    char* FullName;
    long int HomePhone;
    long int WorkPhone;
    long int MobilePhone;
public:
    PhoneBook()
    {
        FullName = nullptr;
        HomePhone = 0;
        WorkPhone = 0;
        MobilePhone = 0;
    }


    PhoneBook(char* fullname, long int homephone, long int workphone, long int mobilephone)
    {
        FullName = new char[strlen(fullname) + 1];
        strcpy_s(FullName, strlen(fullname) + 1, fullname);


        FullName = fullname;
        HomePhone = homephone;
        WorkPhone = workphone;
        MobilePhone = mobilephone;
    }


    ~PhoneBook()
    {
        delete[] FullName;
    }


    void Init()
    {
        char buf[40];
        std::cout << "Your full name:";
        std::cin.getline(buf, 40);


        if (FullName != nullptr)
        {
            delete[] FullName;
        }
        FullName = new char[strlen(buf) + 1];
        strcpy_s(FullName, strlen(buf) + 1, buf);


        std::cout << "Your home phone:";
        std::cin >> HomePhone;
        std::cout << "Your work phone:";
        std::cin >> WorkPhone;
        std::cout << "Your mobile phone:";
        std::cin >> MobilePhone;
    }


    void Print()
    {
        std::cout << "Full name - " << FullName << std::endl
            << "Home phone - " << HomePhone << std::endl
            << "Work phone - " << WorkPhone << std::endl
            << "Mobile phone - " << MobilePhone << std::endl;
    }


    void AddNew()
    {
        char* info;
        char buf[40];
        std::cout << "Full name:";
        std::cin.getline(buf, 40);
        info = new char[strlen(buf) + 2];
        strcpy_s(info, strlen(buf) + 2, buf);
        info += '`';


        FILE* f;
        fopen_s(&f, "D:/C++ projects/HomeWork 32/InfoOfPhoneBook.txt", "a+");
        std::string Info = info;
        fputs(Info.c_str(), f);
        fclose(f);
    }


    void Delete()
    {
        FILE* f;
        fopen_s(&f, "D:/C++ projects/HomeWork 32/InfoOfPhoneBook.txt", "r");
        fseek(f, 0, SEEK_END); // перемещение в конец файла
        int size = ftell(f); // узнаём текущую позицию курсора (сколько символов)
        char* str = new char[size + 1]; // выделяем строку под это количество символов
        rewind(f); // переводим курсор в начало файла
        int symbols = fread(str, sizeof(char), size, f); // считываем весь файл одним куском
        fclose(f);
        str[symbols] = '\0';
        AnsiToOem(str, str);


        char* info;
        char* temp;
        char buf[40];
        std::cout << "Full name for delete:";
        std::cin.getline(buf, 40);
        info = new char[strlen(buf) + 1];
        temp = new char[strlen(buf) + 1];
        strcpy_s(info, strlen(buf) + 1, buf);


        for (int i = 0; i < symbols; i++)
        {
            if (info == temp)
            {
                fopen_s(&f, "D:/C++ projects/HomeWork 32/InfoOfPhoneBook.txt", "a");
                for (int j = strlen(buf) + 1; j != 0; j--)
                {
                    str[i--] = '`';
                }
                std::string Str = str;
                fputs(Str.c_str(), f);
                fclose(f);
                std::cout << "This person was deleted\n" << temp;
                break;
            }
            else if (i == symbols - 1)
                std::cout << "This person wasn't found\n";
            else if (str[i] == '`')
            {
                delete[] temp;
                i++;
            }
            temp += str[i];
        }
    }


    void Search()
    {
        char* info;
        char* temp;
        char buf[40];
        std::cout << "Who are you looking for (full name)?\n";
        std::cin.getline(buf, 40);
        info = new char[strlen(buf) + 1];
        temp = new char[strlen(buf) + 1];
        strcpy_s(info, strlen(buf) + 1, buf);


        FILE* f;
        fopen_s(&f, "D:/C++ projects/HomeWork 32/InfoOfPhoneBook.txt", "r");
        fseek(f, 0, SEEK_END); // перемещение в конец файла
        int size = ftell(f); // узнаём текущую позицию курсора (сколько символов)
        char* str = new char[size + 1]; // выделяем строку под это количество символов
        rewind(f); // переводим курсор в начало файла
        int symbols = fread(str, sizeof(char), size, f); // считываем весь файл одним куском
        fclose(f);
        str[symbols] = '\0';
        AnsiToOem(str, str);


        for (int i = 0; i < symbols; i++)
        {
            if (info == temp)
            {
                std::cout << "This person was found\n" << temp;
                break;
            }
            else if (i == symbols - 1)
                std::cout << "This person wasn't found\n";
            else if (str[i] == '`')
            {
                delete[] temp;
                i++;
            }
            temp += str[i];
        }
    }


    void ShowAll()
    {
        FILE* f;
        fopen_s(&f, "D:/C++ projects/HomeWork 32/InfoOfPhoneBook.txt", "r");
        fseek(f, 0, SEEK_END); // перемещение в конец файла
        int size = ftell(f); // узнаём текущую позицию курсора (сколько символов)
        char* str = new char[size + 1]; // выделяем строку под это количество символов
        rewind(f); // переводим курсор в начало файла
        int symbols = fread(str, sizeof(char), size, f); // считываем весь файл одним куском
        fclose(f);
        str[symbols] = '\0';
        AnsiToOem(str, str);


        for (int i = 0; i < symbols; i++)
        {
            if (str[i] == '`')
                std::cout << "\n";
            else
                std::cout << str[i];
        }
    }


    PhoneBook &operator= (const PhoneBook& obj)
    {
        this->FullName = obj.FullName;
        this->HomePhone = obj.HomePhone;
        this->MobilePhone = obj.MobilePhone;
        this->WorkPhone = obj.WorkPhone;
        return *this;
    }


    void operator[] (const int index)
    {
        //return [index];
        //Доступ к контакту из книги по индексу невозможен, т.к все контакты это разные обьекты
    }


    friend std::ostream& operator<< (std::ostream& out, const PhoneBook& point);
};


std::ostream& operator<< (std::ostream& out, const PhoneBook& ph)
{
    out << "Full name:" << ph.FullName << "\nHome phone:" << ph.HomePhone << "\nMobile phone:" << ph.MobilePhone << "\nWork phone:" << ph.WorkPhone << std::endl;
    return out;
}


int main()
{
    PhoneBook obj1;
    obj1.Init();
    obj1.Print();
}