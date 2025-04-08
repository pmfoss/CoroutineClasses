/* Copyright (C) 2025 Martin Pietsch <@pmfoss>
   SPDX-License-Identifier: BSD-3-Clause */
   
#ifndef CO_GENERATOR_H
#define CO_GENERATOR_H 1

#include "CoTask.h"

namespace CoRoutines
{
    template <typename TypeOfYield>
    class CoGenerator : public CoTask<TypeOfYield, CoNoneType_t, void, CoGenerator<TypeOfYield>>
    {  
         public:
             using base = CoTask<TypeOfYield, CoNoneType_t, void, CoGenerator<TypeOfYield>>;   
         
             using base::CoTask;
            
             struct iterator
             {
                 bool operator==(std::default_sentinel_t) const;
                 iterator& operator++();
                 iterator& operator++(int);
                 TypeOfYield operator*() const;
    
                 CoGenerator& mGenerator;
             };
             
             CoGenerator(base&& pOther);
            
             iterator begin();
             std::default_sentinel_t end();
    };
    
    /*CoGenerator*/
    /*constructor / destructor */
    template<typename TypeOfYield>
    CoGenerator<TypeOfYield>::CoGenerator(CoGenerator<TypeOfYield>::base&& pOther)
        : base(std::move(pOther))
    {
    }
    
    /*public methods*/
    template<typename TypeOfYield>
    CoGenerator<TypeOfYield>::iterator CoGenerator<TypeOfYield>::begin()
    {
        this->resume();
    
        return iterator{*this};
    }
    
    template<typename TypeOfYield>
    std::default_sentinel_t CoGenerator<TypeOfYield>::end()
    {
        return {};
    }
    
    /*CoGenerator::iterator*/
    /*public operators*/
    template <typename TypeOfYield>
    bool CoGenerator<TypeOfYield>::iterator::operator==(std::default_sentinel_t) const
    {
        return mGenerator.done();
    }
    
    template <typename TypeOfYield>
    CoGenerator<TypeOfYield>::iterator& CoGenerator<TypeOfYield>::iterator::operator++()
    {
        mGenerator.resume();
    
        return *this;
    }
    
    template <typename TypeOfYield>
    CoGenerator<TypeOfYield>::iterator& CoGenerator<TypeOfYield>::iterator::operator++(int)
    {
        mGenerator.resume();
    
        return *this;
    }
    
    template <typename TypeOfYield>
    TypeOfYield CoGenerator<TypeOfYield>::iterator::operator*() const
    {
        return mGenerator.yieldValue();
    }
}

#endif /*CO_GENERATOR_H*/
