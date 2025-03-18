/* Copyright (C) 2025 Martin Pietsch <@pmfoss>
   SPDX-License-Identifier: BSD-3-Clause */
   
#include <iostream>
#include <CoTask.h>

CoTask<int> sequence(int pStart, int pEnd)
{
    for(int lIdx = pStart; lIdx < pEnd; ++lIdx)
    {
        co_yield lIdx;
    }

    co_return;
}

int main()
{
    CoTask lTask = sequence(5,10);

    while(not lTask.done())
    {
        int lValue = lTask.run();

        if(not lTask.done())
        {
            std::cout << lValue << " ";
        }
    }

    std::cout << "\n";

    return 0;
}