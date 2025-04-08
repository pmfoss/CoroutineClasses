/* Copyright (C) 2025 Martin Pietsch <@pmfoss>
   SPDX-License-Identifier: BSD-3-Clause */

#ifndef CO_VOID_RETURN_PROMISE_H
#define CO_VOID_RETURN_PROMISE_H 1

#include "CoBasePromise.h"

namespace CoRoutines
{
    template <typename CoRoutine, typename TypeOfYield, typename TypeOfAwait>
    struct CoVoidReturnPromise : CoBasePromise<CoRoutine, TypeOfYield, TypeOfAwait, void, CoVoidReturnPromise<CoRoutine, TypeOfYield, TypeOfAwait>>
    {
        void return_void() noexcept;
    };
    
    /*public methods*/
    template <typename CoRoutine, typename TypeOfYield, typename TypeOfAwait>
    void CoVoidReturnPromise<CoRoutine, TypeOfYield, TypeOfAwait>::return_void() noexcept
    {
    }
}

#endif /*CO_VOID_RETURN_PROMISE_H*/
