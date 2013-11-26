#include <iostream>
#include <string>
#include "Archive.h"

using namespace std;

int main()
{
    int res = 0;

    try
    {
         Archive archive;
         archive.create();

         char ch = 0;
         do
         {
             cout << "Enter src file: ";
             string sSrc;
             getline(cin, sSrc);

             cout << "Enter dst file: ";
             string sDst;
             getline(cin, sDst);

             archive.add(sSrc, sDst);

             cout << "Add one more? (y/n): ";
             cin.get(ch);
         } while ( ch == 'y' );

         archive.close();
    }
    catch ( Archive::Error ex )
    {
        res = 1;
        cout << "Error: " << ex.what() << endl;
    }
    catch (...)
    {
        res = 1;
        cout << "Error: ..." << endl;
    }   
    
    cout << "Done!" << endl;

    cin.ignore(cin.rdbuf()->in_avail());
    cin.get();

    return res;
}
