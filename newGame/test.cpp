#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
using namespace std;

class test1
{
    private:
        string name;
    public:

        int a;

        string getName()
        {
            return name;
        }

        void setName(string name)
        {
            this->name = name;
        }

};

class test : public test1
{
    public:
        
        int x;
        int y;

        test()
        {
            setName("Arian");
            x = 0;
            y = 0;
        }

        test(string name)
        {
            setName(name);
            x = 1;
            y = 1;
        }

        void write(test &koko)
        {
            ofstream file("test.txt");

            if (!file.is_open())
            {
                cout << "error!" << endl;
            } else 
            {
                file.write((char*)&koko, sizeof(test));
            }

            file.close();
        }

        void read(test &koko)
        {
            ifstream infile("test.txt");

            if (!infile.is_open())
            {
                cout << "error!" << endl;
            } else 
            {
                infile.read((char*)&koko, sizeof(test));
            }

            infile.close();
        }
};

int main()
{
    while (true) {
        cout << "Текст выводится каждую секунду" << endl;
        this_thread::sleep_for(chrono::milliseconds(500));
    }
}