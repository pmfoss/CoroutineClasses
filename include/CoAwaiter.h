/* Copyright (C) 2025 Martin Pietsch <@pmfoss>
   SPDX-License-Identifier: BSD-3-Clause */
   
#ifndef CO_AWAITER_H
#define CO_AWAITER_H 1

#include <coroutine>

template <typename PromiseType, typename AwaitType>
struct CoAwaiter
{
    PromiseType&  lPromiseType;
    constexpr bool await_ready() const noexcept;
    AwaitType await_resume() const noexcept;
    void await_suspend(std::coroutine_handle<>) const noexcept;
};

/*public methods*/
template <typename PromiseType, typename AwaitType>
constexpr bool CoAwaiter<PromiseType, AwaitType>::await_ready() const noexcept
{
    return true;
}

template <typename PromiseType, typename AwaitType>
AwaitType CoAwaiter<PromiseType, AwaitType>::await_resume() const noexcept
{
    return lPromiseType.mAwaitValue;
}

template <typename PromiseType, typename AwaitType>
void CoAwaiter<PromiseType, AwaitType>::await_suspend(std::coroutine_handle<>) const noexcept
{
}

#endif /*CO_AWAITER_H*/
