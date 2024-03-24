#include <iostream>
#include <fstream>
#include <string>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

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

        void save(const string& filename) {
            ofstream file(filename);
            boost::archive::text_oarchive oa(file);
            oa << *this;
        }

        void load(const string& filename) {
            ifstream file(filename);
            boost::archive::text_iarchive ia(file);
            ia >> *this;
        }
};

int main()
{
    test koko;
            ifstream infile("test.txt");

            if (!infile.is_open())
            {
                cout << "error!" << endl;
            } else 
            {
                infile.read((char*)&koko, sizeof(test));
            }

            infile.close();

            cout << koko.getName();


}