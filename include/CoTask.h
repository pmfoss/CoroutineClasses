/* Copyright (C) 2025 Martin Pietsch <@pmfoss>
   SPDX-License-Identifier: BSD-3-Clause */
   
#ifndef CO_TASK_H
#define CO_TASK_H 1

#include <coroutine>
#include <utility>

#include "CoValueReturnPromise.h"
#include "CoVoidReturnPromise.h"
#include "CoUtility.h"

namespace CoRoutines
{
    template <typename TypeOfYield, typename TypeOfAwait = CoNoneType_t, typename TypeOfReturn = void, typename Derived = CoNoneType_t>
    class CoTask 
    {
        public:
            using AwaitType = TypeOfAwait;
            using YieldType = TypeOfYield;
            using ReturnType = TypeOfReturn;
    
            using DerivedType = std::conditional<std::is_same_v<Derived, CoNoneType_t>, CoTask, Derived>::type;
    
            using promise_type = std::conditional<std::is_same_v<ReturnType, void>, 
                                          CoVoidReturnPromise<DerivedType, YieldType, AwaitType>, 
                                          CoValueReturnPromise<DerivedType, YieldType, ReturnType, AwaitType>>::type;
    
            constexpr CoTask() = default;
            constexpr CoTask(promise_type& pPromise);
            constexpr CoTask(CoTask&& pOther);
        
            virtual ~CoTask();
        
            constexpr bool done() const;
            constexpr ReturnType returnValue() const;
            constexpr YieldType run(AwaitType pAwaitValue = {});
            constexpr YieldType yieldValue() const;
    
	        constexpr operator bool() const noexcept;
        protected:
            constexpr void resume();
            
        private:
            constexpr void handlePromiseException() const;
    
            std::coroutine_handle<promise_type> mHandle{};
    };
    
    /*constructor / destructor*/
    template <typename TypeOfYield, typename TypeOfAwait, typename TypeOfReturn, typename Derived>
    constexpr CoTask<TypeOfYield, TypeOfAwait, TypeOfReturn, Derived>::CoTask(promise_type& pPromise)
        : mHandle{std::coroutine_handle<promise_type>::from_promise(pPromise)}
    {
    }
    
    template <typename TypeOfYield, typename TypeOfAwait, typename TypeOfReturn, typename Derived>
    constexpr CoTask<TypeOfYield, TypeOfAwait, TypeOfReturn, Derived>::CoTask(CoTask&& pOther)
        : mHandle{std::exchange(pOther.mHandle, nullptr)}
    {
    } 
    
    template <typename TypeOfYield, typename TypeOfAwait, typename TypeOfReturn, typename Derived>
    CoTask<TypeOfYield, TypeOfAwait, TypeOfReturn, Derived>::~CoTask()
    {
        if(mHandle) 
        { 
            mHandle.destroy();
        }
    }
    
    /*public methods*/
    template <typename TypeOfYield, typename TypeOfAwait, typename TypeOfReturn, typename Derived>
    constexpr bool CoTask<TypeOfYield, TypeOfAwait, TypeOfReturn, Derived>::done() const
    {
        return mHandle.done();
    }
    
    template <typename TypeOfYield, typename TypeOfAwait, typename TypeOfReturn, typename Derived>
    constexpr CoTask<TypeOfYield, TypeOfAwait, TypeOfReturn, Derived>::ReturnType CoTask<TypeOfYield, TypeOfAwait, TypeOfReturn, Derived>::returnValue() const
    {
        handlePromiseException();
        
        if(std::is_same_v<ReturnType, void>)
        {
            return {};
        }
        
        if(done())
        {
            return mHandle.promise().mReturnValue;
        }
    
        return {};
    }
    
    template <typename TypeOfYield, typename TypeOfAwait, typename TypeOfReturn, typename Derived>
    constexpr TypeOfYield CoTask<TypeOfYield, TypeOfAwait, TypeOfReturn, Derived>::run(TypeOfAwait pAwaitValue)
    {
        if(not done())
        {
            mHandle.promise().mAwaitValue = pAwaitValue;
            resume();
        }
                
        return yieldValue(); 
    }
    
    template <typename TypeOfYield, typename TypeOfAwait, typename TypeOfReturn, typename Derived>
    constexpr TypeOfYield CoTask<TypeOfYield, TypeOfAwait, TypeOfReturn, Derived>::yieldValue() const
    {
        return mHandle.promise().mYieldValue;
    }
    
	template <typename TypeOfYield, typename TypeOfAwait, typename TypeOfReturn, typename Derived>
	constexpr CoTask<TypeOfYield, TypeOfAwait, TypeOfReturn, Derived>::operator bool() const noexcept
	{
		return mHandle; 
	}
	
	
    /*protected methods*/
    template <typename TypeOfYield, typename TypeOfAwait, typename TypeOfReturn, typename Derived>
    constexpr void CoTask<TypeOfYield, TypeOfAwait, TypeOfReturn, Derived>::resume()
    {
        handlePromiseException();
    
        if(not done())
        {
            mHandle.resume();
        }
    }
    /*private methods*/
    template <typename TypeOfYield, typename TypeOfAwait, typename TypeOfReturn, typename Derived>
    constexpr void CoTask<TypeOfYield, TypeOfAwait, TypeOfReturn, Derived>::handlePromiseException() const
    {
        if(mHandle.promise().mException)
        {
            std::rethrow_exception(mHandle.promise().mException);
        }
    }
}
#endif /*CO_TASK_H*/
