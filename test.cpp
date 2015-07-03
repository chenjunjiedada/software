#include <iostream>
#include <map>
#include <string>

using namespace std;


class F {
    public:
       virtual  void func() {
            cout << "this is father\n";
        }
    protected:
        int a;
};

class C : public F
{
    public:
        void func() 
        {
            cout << "this is child\n";
        }
};

class S : public C
{
    public :
        void func() 
        {
            a = 5;
            cout << a << endl;
            F::func();
        }
};

int main() {

    std::map<std::string, std::string> mm;
    mm["a"] = "hello world";

    cout << mm.find("a")->second << endl;

    if (mm.end()!=mm.find("b"))
    cout << mm.find("b")->second << endl;


    F *f = new S();
    f->func();

    return 0;
}
