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
void RoundR4P();
void FIFO();
void FIFO4P();
void SJF();
void SJF4P();
void copyArray();
static int numOfProcesses = 50;

int main()
{
    fillArray();
    copyArray();
    //printArray2();
    cout << "Single Processor:\n";
    RoundR();
    //printArray2();
    copyArray();
    FIFO();
    copyArray();
    //printArray2();
    SJF();
    //printArray2();
    cout << "\n4 Processors:\n";
    copyArray();
    RoundR4P();
    copyArray();
    FIFO4P();
    copyArray();
    SJF4P();
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
    /*This fills the array with a random amount of process values.*/
    
    static int offset = 500;
    int total = numOfProcesses * 6000;
    int ran;
    int newNum = numOfProcesses;
    
    for (int i = 0; i <= numOfProcesses; i++)
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
    int AWT,AWTlower=1,AWTupper=0;
    int savedTime =0;
    while (counter < 100)
    {
        if(newArrayForManipulating[spotInArray] == 0)counter++;//this makes sure the process isn't finished alredy
        if(newArrayForManipulating[spotInArray] > 0)
        {
            savedTime = totalTime;
            newArrayForManipulating[spotInArray] -= 50;
            totalTime += 10;
            totalTime += 50;
            if(newArrayForManipulating[spotInArray] == 0)
            {
                AWTupper += savedTime;
                upper += totalTime;
                lower++;
            }
            
            counter = 0;
        }
        spotInArray++;
        if(spotInArray >= 50)spotInArray = 0;
        
    }
    AWTupper -= savedTime;
    for (int i = 0; i < 49; i++)
    {
        //AWTcounter += 60;
        //AWTupper += AWTcounter;
        AWTlower++;
    }
    AWT = AWTupper/AWTlower;
    int t1 = upper/lower;
    cout << "The average number of cycles executed before each processes is completed using Round Robin is " << t1 << " cycles." << endl;
    //cout << AWT << endl << AWTupper << endl << AWTlower << endl;
    cout << "The AWT using RR is " << AWT << endl;
}
void FIFO()
{
    int upper = 0;
    int lower = 0;
    int totalCycles = 0;
    int AWT,AWTlower=1,AWTupper=0;
    totalCycles += newArrayForManipulating[0];
    upper += totalCycles;
    lower++;
    for (int i = 1; i < 50; i++)
    {
        AWTupper += totalCycles;
        totalCycles += 10;
        totalCycles += newArrayForManipulating[i];
        upper += totalCycles;
        
        AWTlower++;
        lower++;
    }
    AWT = AWTupper/AWTlower;
    int t1 = upper/lower;
    cout << "The average number of cycles executed before each processes is completed using FIFO is " << t1 << " cycles." << endl;
    //cout << AWT << endl << AWTupper << endl << AWTlower << endl;
    cout << "The AWT using FIFO is " << AWT << endl;
}
void SJF()
{
    int upper = 0;
    int lower = 0;
    int totalCycles = 0;
    int AWT,AWTlower=1,AWTupper=0;
    totalCycles += newArrayForManipulating[0];
    newArrayForManipulating[0] = 0;
    upper += totalCycles;
    lower++;
    for (int i = 1; i < 50; i++)
    {
        int smallestNumber = 11001;
        int spot = 0;
        for (int j = 1; j < 50; j++)
        {
            if(newArrayForManipulating[j] < smallestNumber && newArrayForManipulating[j] != 0)
            {
                smallestNumber = newArrayForManipulating[j];
                spot = j;
            }
        }
        AWTupper += totalCycles;
        totalCycles += 10;
        totalCycles += newArrayForManipulating[spot];
        newArrayForManipulating[spot] = 0;
        upper += totalCycles;
        lower++;
        AWTlower++;
    }
    
    AWT = AWTupper/AWTlower;
    int t1 = upper/lower;
    cout << "The average number of cycles executed before each processes is completed using SJF is " << t1 << " cycles." << endl;
    //cout << AWT << endl << AWTupper << endl << AWTlower << endl;
    cout << "The AWT using SJF is " << AWT << endl;
}
void RoundR4P()
{
    int counter = 0;
    int upper = 0;
    int lower = 0;
    int totalTime = 0;
    int spotInArray = 0;
    int AWT,AWTlower=1,AWTupper=0;
    int savedTime =0;
    int Processor = 0;
    while (counter < 100)
    {
        if(newArrayForManipulating[spotInArray] == 0)counter++;//this makes sure the process isn't finished alredy
        //cout << Processor%4 << endl;
        if(newArrayForManipulating[spotInArray] > 0 && Processor%4 == 0)
        {
            savedTime = totalTime;
            newArrayForManipulating[spotInArray] -= 50;
            totalTime += 10;
            totalTime += 50;
            if(newArrayForManipulating[spotInArray] == 0)
            {
                AWTupper += savedTime;
                upper += totalTime;
                lower++;
            }
            
            counter = 0;
        }
        Processor++;
        spotInArray++;
        if(spotInArray >= 50)spotInArray = 0;
        
    }
    AWTupper -= savedTime;
    for (int i = 0; i < 49; i++)
    {
        //AWTcounter += 60;
        //AWTupper += AWTcounter;
        AWTlower++;
    }
    AWT = AWTupper/AWTlower;
    int t1 = upper/50;
    cout << "The average number of cycles executed before each processes is completed using Round Robin is " << t1 << " cycles." << endl;
    //cout << AWT << endl << AWTupper << endl << AWTlower << endl;
    cout << "The AWT using RR is " << AWT << endl;
}
void FIFO4P()
{
    int upper = 0;
    int lower = 0;
    int totalCycles = 0;
    int Processor = 0;
    int AWT,AWTlower=1,AWTupper=0;
    int finalNum = newArrayForManipulating[49]- newArrayForManipulating[48];
    totalCycles += newArrayForManipulating[0];
    upper += totalCycles;
    lower++;
    for (int i = 1; i < 50; i++)
    {
        if (Processor%4 == 0)
        {
            AWTupper += totalCycles;
            totalCycles += 10;
            totalCycles += newArrayForManipulating[i];
            upper += totalCycles;
        
            AWTlower++;
            lower++;
        }
        Processor++;
    
    }
    if(finalNum > 0)
    {
        totalCycles += finalNum;
    }
    AWT = AWTupper/AWTlower;
    int t1 = upper/lower;
    cout << "The average number of cycles executed before each processes is completed using FIFO is " << t1 << " cycles." << endl;
    //cout << AWT << endl << AWTupper << endl << AWTlower << endl;
    cout << "The AWT using FIFO is " << AWT << endl;
}
void SJF4P()
{
    int upper = 0;
    int lower = 0;
    int totalCycles = 0;
    int Processor = 0;
    int saved48 = 0;
    int AWT,AWTlower=1,AWTupper=0;
    totalCycles += newArrayForManipulating[0];
    newArrayForManipulating[0] = 0;
    upper += totalCycles;
    lower++;
    for (int i = 1; i < 50; i++)
    {
        int smallestNumber = 11001;
        int spot = 0;
        for (int j = 1; j < 50; j++)
        {
            if(newArrayForManipulating[j] < smallestNumber && newArrayForManipulating[j] != 0)
            {
                smallestNumber = newArrayForManipulating[j];
                spot = j;
            }
        }
        AWTupper += totalCycles;
        totalCycles += 10;
        if (Processor%4 == 0)
        {
            totalCycles += newArrayForManipulating[spot];
        }
        if(i == 48)
        {
            saved48 += newArrayForManipulating[spot];
        }
        if(i == 49)
        {
            totalCycles += newArrayForManipulating[spot] - saved48;
        }
        newArrayForManipulating[spot] = 0;
        upper += totalCycles;
        lower++;
        AWTlower++;
        Processor++;
    }
    AWT = AWTupper/AWTlower;
    int t1 = upper/lower;
    cout << "The average number of cycles executed before each processes is completed using SJF is " << t1 << " cycles." << endl;
    //cout << AWT << endl << AWTupper << endl << AWTlower << endl;
    cout << "The AWT using SJF is " << AWT << endl;
}

