/* Copyright (C) 2025 Martin Pietsch <@pmfoss>
   SPDX-License-Identifier: BSD-3-Clause */
   
#include <iostream>
#include <CoTask.h>

using namespace CoRoutines;

class DerivedCoTask : public CoTask<int, std::pair<int, bool>, void, DerivedCoTask>
{
    public:
        using base = CoTask<int, std::pair<int, bool>, void, DerivedCoTask>;
        
        using base::CoTask;
        
        DerivedCoTask(CoTask&& pOther)
            : base(std::move(pOther))
        {
        } 
        
        int run(int newVal, bool reset)
        {
            return CoTask::run({newVal, reset});
        }
};

DerivedCoTask Fun()
{
    int i = 1;
    
    while(true)
    {
        typename DerivedCoTask::AwaitType a = co_await typename DerivedCoTask::AwaitType{};
       
         i = ++a.first;
         
         if(a.second)
         {
             i = 0;
         }
         
         co_yield i;
    }
}  

int main()
{
    DerivedCoTask task = Fun();
  
    for(int x = 0; x < 10; x++)
    {
         for(int v = 0; v < x + 1; v++)
         {
            std::cout << task.run(v - 1, (v == 0) ? true : false) << " ";
         }
         
         std::cout << "\n";
    }
    
    return 0;
}
