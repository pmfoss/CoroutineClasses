/* Copyright (C) 2025 Martin Pietsch <@pmfoss>
   SPDX-License-Identifier: BSD-3-Clause */
   
#include <iostream>
#include <CoGenerator.h>

using namespace CoRoutines;

CoGenerator<int> sequence(int pStart, int pEnd)
{
    for(int lIdx = pStart; lIdx <= pEnd; ++lIdx)
    {
        co_yield lIdx;
    }
}

int main()
{
    for(int lValue : sequence(5,10))
    {
        std::cout << lValue << " ";
    }

    std::cout << "\n";

    return 0;
}