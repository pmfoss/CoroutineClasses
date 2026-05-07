/* Copyright (C) 2025 Martin Pietsch <@pmfoss>
   SPDX-License-Identifier: BSD-3-Clause */
   
#ifndef CO_AWAITER_H
#define CO_AWAITER_H 1

#include <coroutine>

namespace CoRoutines
{
    template <typename PromiseType, typename AwaitType>
    struct CoAwaiter
    {
        PromiseType&  lPromiseType;
        constexpr bool await_ready() const noexcept;
        constexpr AwaitType await_resume() const noexcept;
        constexpr void await_suspend(std::coroutine_handle<>) const noexcept;
    };
    
    /*public methods*/
    template <typename PromiseType, typename AwaitType>
    constexpr bool CoAwaiter<PromiseType, AwaitType>::await_ready() const noexcept
    {
        return true;
    }
    
    template <typename PromiseType, typename AwaitType>
    constexpr AwaitType CoAwaiter<PromiseType, AwaitType>::await_resume() const noexcept
    {
        return lPromiseType.mAwaitValue;
    }
    
    template <typename PromiseType, typename AwaitType>
    constexpr void CoAwaiter<PromiseType, AwaitType>::await_suspend(std::coroutine_handle<>) const noexcept
    {
    }
}

#endif /*CO_AWAITER_H*/
