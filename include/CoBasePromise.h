/* Copyright (C) 2025 Martin Pietsch <@pmfoss>
   SPDX-License-Identifier: BSD-3-Clause */
   
#ifndef CO_BASE_PROMISE_H
#define CO_BASE_PROMISE_H 1

#include <coroutine>
#include <exception>

#include "CoAwaiter.h"
#include "CoUtility.h"

namespace CoRoutines
{
    template <typename CoRoutine, typename TypeOfYield, typename TypeOfAwait, typename TypeOfReturn, typename Derived>
    struct CoBasePromise
    {
        using AwaitType = TypeOfAwait;
        using ReturnType = TypeOfReturn;
        using YieldType = TypeOfYield;
     
        using Awaiter = CoAwaiter<CoBasePromise, AwaitType>;
        
        AwaitType mAwaitValue;
        std::exception_ptr mException;
        YieldType mYieldValue;
        
        constexpr auto await_transform(AwaitType) noexcept;
        constexpr CoRoutine get_return_object();
        constexpr std::suspend_always initial_suspend() noexcept;
        constexpr std::suspend_always final_suspend() noexcept;
        constexpr void unhandled_exception() noexcept;
        constexpr std::suspend_always yield_value(YieldType pValue) noexcept;
    };
    
    
    /*public methods*/
    template <typename CoRoutine, typename TypeOfYield, typename TypeOfAwait, typename TypeOfReturn, typename Derived>
    constexpr auto CoBasePromise<CoRoutine, TypeOfYield, TypeOfAwait, TypeOfReturn, Derived>::await_transform(AwaitType) noexcept
    {
        return Awaiter{*this};
    }
    
    template <typename CoRoutine, typename TypeOfYield, typename TypeOfAwait, typename TypeOfReturn, typename Derived>
    constexpr CoRoutine CoBasePromise<CoRoutine, TypeOfYield, TypeOfAwait, TypeOfReturn, Derived>::get_return_object()
    {
        return CoRoutine{*static_cast<Derived*>(this)};
    }
       
    template <typename CoRoutine, typename TypeOfYield, typename TypeOfAwait, typename TypeOfReturn, typename Derived>
    constexpr std::suspend_always CoBasePromise<CoRoutine, TypeOfYield, TypeOfAwait, TypeOfReturn, Derived>::initial_suspend() noexcept
    {
        return {};
    }
    
    template <typename CoRoutine, typename TypeOfYield, typename TypeOfAwait, typename TypeOfReturn, typename Derived>
    constexpr std::suspend_always CoBasePromise<CoRoutine, TypeOfYield, TypeOfAwait, TypeOfReturn, Derived>::final_suspend() noexcept
    {
        return {};
    }
    
    template <typename CoRoutine, typename TypeOfYield, typename TypeOfAwait, typename TypeOfReturn, typename Derived>
    constexpr void CoBasePromise<CoRoutine, TypeOfYield, TypeOfAwait, TypeOfReturn, Derived>::unhandled_exception() noexcept
    {
        mException = std::current_exception();
    }
    
    template <typename CoRoutine, typename TypeOfYield, typename TypeOfAwait, typename TypeOfReturn, typename Derived>
    constexpr std::suspend_always CoBasePromise<CoRoutine, TypeOfYield, TypeOfAwait, TypeOfReturn, Derived>::yield_value(YieldType pValue) noexcept
    {
        mYieldValue = pValue;
        return {};
    }
}

#endif /*CO_BASE_PROMISE_H*/
