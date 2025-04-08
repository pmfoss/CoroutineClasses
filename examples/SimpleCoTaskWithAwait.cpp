/* Copyright (C) 2025 Martin Pietsch <@pmfoss>
   SPDX-License-Identifier: BSD-3-Clause */
   
#include <iostream>
#include <CoTask.h>

using namespace CoRoutines;

CoTask<int, int> addNumber(int pStart)
{
    int lValue = pStart;

    while(true)
    {
        int lSummand = co_await int{};

        lValue += lSummand;

        co_yield lValue;
    }
}

int main()
{
    CoTask lTask = addNumber(2);

    for(int i = 0; i < 10; ++i)
    {
        std::cout << lTask.run(i) << " ";
    }

    std::cout << "\n";

    return 0;
}