#include <iostream>
#include <set>
#include <vector>


void gen_pentagonal(std::set<int> &ptg) 
{
    int i = 0;
    int pre = 1;
    int cur;
    for (i = 1; pre < 1 << 28; i++) 
    {
        cur = pre + 3*i + 1;
        ptg.insert(cur);
        pre = cur;
    }
}


int main() 
{
    std::set<int> ptg;
    gen_pentagonal(ptg);
    std::vector< std::vector<int> > ans;
    int index = 1;

    for (auto i = ptg.begin(); i != ptg.end();  i++) 
    {
       if ( ((*i << 1) + 3 * index + 1) < 0) break;
       for (auto j = i; j!=ptg.end(); j++) 
       {

           if (ptg.find(*j - *i) != ptg.end() &&
               ptg.find(*j + *i) != ptg.end())
           {
               std::vector<int> a;
               a.push_back(*i);
               a.push_back(*j);

               ans.push_back(a);
           }
       }
    }

    for(std::vector< std::vector<int> >::iterator i = ans.begin(); i != ans.end(); i++) 
    {
        std::cout << (*i)[0] << " " << (*i)[1] << std::endl;
    }

    return 0;
}


