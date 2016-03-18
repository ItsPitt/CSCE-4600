//
//  main.cpp
//  CSCE_4600_Project_1
//
//  Created by Michael Pittard on 3/15/16.
//  Copyright © 2016 Michael Pittard. All rights reserved.
//

#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

int p[50];
int newArrayForManipulating[50];
void fillArray();
void printArray();
void printArray2();
void RoundR();
void copyArray();
int main()
{
    fillArray();
    copyArray();
    //printArray2();
    RoundR();
    //printArray2();
}
void printArray()
{// made this function just for testing
    for (int i = 0; i < 50; i++)
    {
        cout << i << " " << p[i] << endl;
    }
}
void printArray2()
{// made this function just for testing
    for (int i = 0; i < 50; i++)
    {
        cout << i << " " << newArrayForManipulating[i] << endl;
    }
}
void fillArray()
{
    /*This fills the array with a random amount of process values.
    Change the num const if you need to change how many processes you want.*/
    
    static int num = 50;
    static int offset = 500;
    int total = num * 6000;
    int ran;
    int newNum = num;
    
    for (int i = 0; i <= num; i++)
    {
        p[i] = 0;
    }
    
    total = total/offset;
    
    srand(time(NULL));
    
    
    for (int i = 0; i <= total; i++)
    {
        ran = rand() % newNum;
        if (p[ran] < 11000)
        {
            p[ran]+= offset;
        }
    }
    
}
void copyArray()
{
    /*This functuion is just for copying all the data from the first array to the second array
     so that the original data is not lost when each process scheduling function is called*/

    for (int i = 0; i < 50; i++)
    {
        newArrayForManipulating[i] = p[i];
    }
}
void RoundR()
{
    int counter = 0;
    int upper = 0;
    int lower = 0;
    int totalTime = 0;
    int spotInArray = 0;
    while (counter < 100)
    {
        if(newArrayForManipulating[spotInArray] == 0)counter++;
        if(newArrayForManipulating[spotInArray] > 0)
        {
            newArrayForManipulating[spotInArray] -= 50;
            totalTime += 10;
            totalTime += 50;
            if(newArrayForManipulating[spotInArray] == 0)
            {
                upper += totalTime;
                lower++;
            }
            
            counter = 0;
        }
        spotInArray++;
        if(spotInArray >= 50)spotInArray = 0;
        
    }
    int t1 = upper/50;
    cout << "The average number of cycles executed before each processes is completed using Round Robin is " << t1 << " cycles." << endl;
}
