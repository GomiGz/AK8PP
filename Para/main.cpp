#include <iostream>
#include <string>
#include <math.h>
#include <omp.h>

using namespace std;

#define LEN 7


void basicVersion(){
    int i,j,y,M[LEN];
    omp_set_num_threads(LEN);

    for (i=1; i<LEN+1; i++){
       M[i-1] = i;
    }

    #pragma omp parallel private(i,y) shared(M)
    {
        cout << "Thread " << omp_get_thread_num() << endl;
        #pragma omp for schedule(static)
        for (i=0; i<LEN; i++){
            y = M[i];
            cout << "Thread " << omp_get_thread_num() << " ,Y: " << y << endl;
    }
    }
    int count = std::ceil(log(LEN))-1;
    for(j=0;j < count;j++)
    {
        cout<< "[";
        for(int k = 0; k< LEN; k++)
        {
          cout << M[k]<<",";
        }
        cout<< "]" << endl;

        #pragma omp parallel for
        #pragma omp private(i,y)
        #pragma omp shared(M)
        for (i=2^j; i<LEN; i++){
            y = y + M[i-2^j];
        }

        #pragma omp parallel for
        #pragma omp private(i,y)
        #pragma omp shared(M)
        for (i=2^j; i<LEN; i++){
            M[i] = y;
        }
    }
    cout<< "[";
    for(int k = 0; k< LEN; k++)
    {
      cout << M[k]<<",";
    }
    cout<< "]" << endl;
    //system("pause");
}

bool is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(),
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

int main()
{
    bool stop = false;
    string option;
    while(!stop){
        system("cls");
        cout << "Algoritmy:" << endl;
        cout << "1) EREW PRAM" << endl;
        cout << "2) skalovatelny EREW PRAM" << endl;
        cout << "0) ukoncit" << endl;
        cout << "----------------------------------" << endl;
        cout << "Vyberte algortimus: ";
        //cin >> option;
        option = "1";

        if(!is_number(option))
            continue;

        switch(stoi(option))
        {
            case 0:
                stop = true;
            break;

            case 1:
                #pragma omp parallel
                {
                    cout << "Hello World";
                }
                stop = true;
            break;
            default:
            break;
        }
    }
    return 0;
}
