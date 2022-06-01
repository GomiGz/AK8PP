#include <iostream>
#include <string>
#include <cmath>
#include <omp.h>
#include <vector>

using namespace std;
int y;

#define LEN 7
#define procNum 0
#pragma omp threadprivate(y)

void basicVersion(int size){
    size = min(size,32);
    int i,j;
    vector<int> M(size);
    omp_set_num_threads(size);

    #pragma omp parallel for private(i) shared(M)
    for (i=1; i<size+1; i++){
       M[i-1] = i;
       y = M[i-1];
       /*if(omp_get_thread_num() == procNum){
           cout << "INITIALIZED: i: " << i-1 << ", y: " << M[i-1] << endl;
       }*/
    }


    int count = std::ceil(log2(size))-1;
    //cout << "Count:" << count << endl;

    for(j=0;j <= count;j++)
    {
        cout<< "[";
        for(int k = 0; k< size; k++)
        {
            if(k != size-1){
              cout << M[k]<<",";
            }else
            {
              cout << M[k];
            }
        }
        cout<< "]" << endl;


        #pragma omp parallel shared(M)
        {
            #pragma omp for private(i)
            for (i=0; i<size; i++){
                if(omp_get_thread_num() < pow(2,j) ){
                    continue;
                }

                /*if(omp_get_thread_num() == procNum){
                    cout << "BEFORE: i: " << i << ", j: " << j << ", y: " << y << endl;
                    cout << "Adding M[i-2^j]: " << M[i-(int)pow(2,j)]<< " "  << i-(int)pow(2,j) << " " <<(int)pow(2,j)<< endl;
                }*/
                y = y + M[i- (int)pow(2,j)];

                /*if(omp_get_thread_num() == procNum){
                    cout << "AFTER: i: " << i << ", j: " << j << ", y: " << y << endl;
                }*/
            }

            #pragma omp for private(i)
            for (i=0; i<size; i++){
                if(omp_get_thread_num() < pow(2,j) ){
                    continue;
                }
                M[i] = y;
                /*if(omp_get_thread_num() == procNum){
                    cout << "SAVING TO: i: " << i <<", y: " << y <<endl;
                }*/
            }
        }
    }

    cout<< "[";
    for(int k = 0; k< size; k++)
    {
      if(k != size-1){
        cout << M[k]<<",";
      }else
      {
        cout << M[k];
      }
    }
    cout<< "]" << endl;
    system("pause");
}


void scaledVersion(int size,int threadCount)
{
    cout << endl;
    threadCount = min(threadCount,32);
    omp_set_num_threads(threadCount);

    vector<int> X(size);
    vector<int> Z(threadCount);
    int q = (int)size/threadCount;

    int i,j;

    cout << "Thread count:" << threadCount << endl;
    cout << "Size:" << size << endl;
    cout << "Q:" << q << endl;


    #pragma omp parallel for private(i) shared(X)
    for (i=0; i<size; i++){
       X[i] = i+1;
    }

    #pragma omp parallel private(i) shared(X,Z) // prvni cast
    {
        #pragma omp for
        for(i=0;i<threadCount;i++){
            for(int j = 0; j < q; j++){
                if(j == 0 ){
                    X[i*q+j] = X[i*q + j];
                }else{
                    X[i*q+j] = X[i*q + j] +  X[i*q+j -1];
                }
            }
            Z[i] = X[i*q+q-1];
        }
    }

    cout<< "First step: [";
    for(int k = 0; k < size; k++)
    {
      if(k != size-1){
        cout << X[k]<<",";
      }else
      {
        cout << X[k];
      }
    }
    cout<< "]" << endl;

    /*cout<< "[";
    for(int k = 0; k < threadCount; k++)
    {
      if(k != threadCount-1){
        cout << Z[k]<<",";
      }else
      {
        cout << Z[k];
      }
    }
    cout<< "]" << endl;*/


    #pragma omp parallel for private(i) shared(X) //druha cast
    for (i=0; i<threadCount; i++){
       y = Z[i];
    }

    int count = std::ceil(log2(threadCount))-1;

    for(j=0;j <= count;j++)
    {
        #pragma omp parallel shared(Z,X)
        {
            #pragma omp for private(i)
            for (i=0; i<threadCount; i++){
                if(omp_get_thread_num() < pow(2,j) ){
                    continue;
                }

                y = y + Z[i- (int)pow(2,j)];
            }

            #pragma omp for private(i)
            for (i=0; i<threadCount; i++){
                if(omp_get_thread_num() < pow(2,j) ){
                    continue;
                }
                Z[i] = y;
            }
        }
    }

    cout<< "Z: [";
    for(int k = 0; k < threadCount; k++)
    {
      if(k != threadCount-1){
        cout << Z[k]<<",";
      }else
      {
        cout << Z[k];
      }
    }
    cout<< "]" << endl;

    #pragma omp parallel for private(i,j) shared (X,Z) //treti cast
    for(i = 1; i < threadCount; i++){
        for(j = 0; j < q-1; j++){            
            X[i*q+j] = X[i*q+j]+Z[i-1];
        }
        X[i*q+q-1] = Z[i];
    }

    cout<< "Final: [";
    for(int k = 0; k < size; k++)
    {
      if(k != size-1){
        cout << X[k]<<",";
      }else
      {
        cout << X[k];
      }
    }
    cout<< "]" << endl;
    system("pause");
}
bool is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(),
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

int main()
{
    bool stop = false;
    bool cont = false;
    string length = "";
    string option;
    string threadCount = "";
    while(!stop){
        system("cls");
        cout << "Algoritmy:" << endl;
        cout << "1) EREW PRAM" << endl;
        cout << "2) skalovatelny EREW PRAM" << endl;
        cout << "0) ukoncit" << endl;
        cout << "----------------------------------" << endl;
        cout << "Vyberte algortimus: ";
        cin >> option;
        //option = "2";

        if(!is_number(option))
            continue;

        switch(stoi(option))
        {
            case 0:
                stop = true;
            break;

            case 1:
                cout << "Zadejte delku pole: ";
                cin >> length;

                if(!is_number(length) || stoi(length) == 0){
                    cout << "Byla zadana chybna delka pole" << endl;
                    system("pause");
                    continue;
                }
                basicVersion(stoi(length));
            break;

            case 2:
                cont = false;
                while(!cont){
                    cout << "Zadejte delku pole: ";
                    cin >> length;

                    cout << "Zadejte pocet vlaken: ";
                    cin >> threadCount;

                    if(!is_number(length) || stoi(length) == 0){
                        cout << "Byla zadana chybna delka pole" << endl;
                        continue;
                    }

                    if(!is_number(threadCount) || stoi(threadCount) < 1){
                        cout << "Byl zadan chybny pocet vlaken" << endl;
                        continue;
                    }

                    if(stoi(length) <= stoi(threadCount))
                    {
                        cout << "Delka musi by vetsi nez pocet vlaken" << endl;
                        continue;
                    }

                    if(stoi(length) % stoi(threadCount) != 0)
                    {
                        cout << "Delka musi by celociselnym nasobkem poctu vlaken" << endl;
                        continue;
                    }
                    cont = true;
                }

                /*length = "9";
                threadCount = "3";*/

                scaledVersion(stoi(length),stoi(threadCount));
                //stop = true;
            break;

            default:
            break;
        }
    }
    return 0;
}
