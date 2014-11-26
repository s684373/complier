#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <string>
#include <stdlib.h>
using namespace std;

void qusort(int low,int high,int a[])
{
    if(low>=high)
        return;
    int first=low;
    int last=high;
    int key=a[first];
    int keypos=first;
    for(int i=first+1;i<=last;i++)
    {
        if(a[i]<key)
        {
            keypos++;
            int tem=a[i];
            a[i]=a[keypos];
            a[keypos]=tem;
            
        }
    }
    int tem=a[first];
    a[first]=a[keypos];
    a[keypos]=tem;
    qusort(low,keypos-1,a);
    qusort(keypos+1,high,a);
}
int main()
{
    int a[5]={14,2,56,8,6};
    qusort(0,4,a);
    for(int i=0;i<5;i++)
        cout<<a[i]<<" ";
}