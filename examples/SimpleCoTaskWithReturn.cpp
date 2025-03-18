/* Copyright (C) 2025 Martin Pietsch <@pmfoss>
   SPDX-License-Identifier: BSD-3-Clause */
   
#include <iostream>
#include <CoTask.h>

CoTask<int, int, int> addPositivNumbers(int pStart, int pMax)
{
    if(pStart < 0)
    {
        co_return -1;
    }

    if(pStart >= pMax)
    {
        co_return -2;
    }

    int lValue = pStart;

    while(true)
    {
        int lSummand = co_await int{};

        if(lSummand < 0)
        {
            co_return -3;
        }

        lValue += lSummand;

        if(lValue > pMax)
        {
            co_return 0;
        }

        co_yield lValue;
    }
}

void printTaskReturnCode(CoTask<int, int, int>& pTask)
{
    std::cout << "return code of task: ";
    if(pTask.done())
    {
        std::cout << pTask.returnValue() << "\n";
    }
    else
    {
        std::cout << "The task is still running.\n";
    }
}

int main()
{
    /*sucessful task execution*/
    CoTask lTask1 = addPositivNumbers(2,40);

    for(int i = 0; i < 10; ++i)
    {
        int lValue = lTask1.run(i);

        if(lTask1.done())
        {
            break;
        }

        std::cout << lValue << " ";
    }

    std::cout << "\n";

    printTaskReturnCode(lTask1);

    /*failed task execution with a negativ starting value*/
    CoTask lTask2 = addPositivNumbers(-2,40);

    lTask2.run(2);

    printTaskReturnCode(lTask2);

    /*failed task execution with a start value that is too large*/
    CoTask lTask3 = addPositivNumbers(40,2);
    
    lTask3.run(2);
    
    printTaskReturnCode(lTask3);

    /*failed task execution with a negativ running value*/
    CoTask lTask4 = addPositivNumbers(2,40);

    lTask4.run(-2);

    printTaskReturnCode(lTask4);

    return 0;
}