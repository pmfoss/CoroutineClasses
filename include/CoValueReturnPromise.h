/* Copyright (C) 2025 Martin Pietsch <@pmfoss>
   SPDX-License-Identifier: BSD-3-Clause */

#ifndef CO_VALUE_RETURN_PROMISE_H
#define CO_VALUE_RETURN_PROMISE_H 1

#include "CoBasePromise.h"

namespace CoRoutines
{
    template <typename CoRoutine, typename TypeOfYield, typename TypeOfAwait, typename TypeOfReturn>
    struct CoValueReturnPromise : CoBasePromise<CoRoutine, TypeOfYield, TypeOfReturn, TypeOfAwait, CoValueReturnPromise<CoRoutine, TypeOfYield, TypeOfAwait, TypeOfReturn>>
    {
        using base = CoBasePromise<CoRoutine, TypeOfYield, TypeOfReturn, TypeOfAwait, CoValueReturnPromise<CoRoutine, TypeOfYield, TypeOfAwait, TypeOfReturn>>;
    
        base::ReturnType mReturnValue;
        
        void return_value(TypeOfReturn pValue) noexcept; 
    };
    
    /*public methods*/
    template <typename CoRoutine, typename TypeOfYield, typename TypeOfAwait, typename TypeOfReturn>
    void CoValueReturnPromise<CoRoutine, TypeOfYield, TypeOfAwait, TypeOfReturn>::return_value(TypeOfReturn pValue) noexcept
    {
        mReturnValue = pValue;
    }
}
#endif /*CO_VALUE_RETURN_PROMISE_H*/
