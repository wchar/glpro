//
//  Variant.h
//  glpro
//
//  Created by PatGame on 15/7/27.
//  Copyright (c) 2015年 wcchan. All rights reserved.
//

#ifndef __UTILS_VARIANT_H__
#define __UTILS_VARIANT_H__

#include <typeindex>
#include <iostream>
#include <type_traits>

namespace utils
{
    template <typename T, typename... Args>
    struct MaxType
        : std::integral_constant<int, (sizeof(T) > MaxType<Args...>::value ? sizeof(T) : MaxType<Args...>::value)>
    {
    };

    template <typename T>
    struct MaxType<T> : std::integral_constant<int, sizeof(T)>
    {
    };

    template <typename T, typename... List>
    struct Contains : std::true_type
    {
    };

    template <typename T, typename Head, typename... Rest>
    struct Contains<T, Head, Rest...>
        : std::conditional<std::is_same<T, Head>::value, std::true_type, Contains<T, Rest...>>::type
    {
    };

    template <typename T>
    struct Contains<T> : std::false_type
    {
    };

    template <typename... Args>
    struct VariantHelper;

    template <typename T, typename... Args>
    struct VariantHelper<T, Args...>
    {
        inline static void destroy(std::type_index id, void* data)
        {
            if (id == std::type_index(typeid(T)))
            {
                ((T*)(data))->~T();
            }
            else
            {
                VariantHelper<Args...>::destroy(id, data);
            }
        }
    };

    template <>
    struct VariantHelper<>
    {
        inline static void destroy(std::type_index id, void* data)
        {
        }
    };

    template <typename... Types>
    class Variant
    {
        typedef VariantHelper<Types...> Helper;

    public:
        Variant(void) : _typeIndex(typeid(void))
        {
            memset(_data, 0, sizeof(_data));
        }

        ~Variant()
        {
            Helper::destroy(_typeIndex, &_data);
        }

        template <typename T>
        bool is()
        {
            return (_typeIndex == std::type_index(typeid(T)));
        }

        template <typename T>
        T& get()
        {
            if (!is<T>())
            {
                std::cout << typeid(T).name() << " is not defined. "
                          << "current type is " << _typeIndex.name() << std::endl;
                throw std::bad_cast();
            }
            return *(T*)(&_data);
        }

        template <class T, class = typename std::enable_if<Contains<typename std::remove_reference<T>::type, Types...>::value>::type>
        Variant(T&& value)
            : _typeIndex(std::type_index(typeid(T)))
        {
            Helper::destroy(_typeIndex, &_data);
            typedef typename std::remove_reference<T>::type U;
            new (_data) U(std::forward<T>(value));
        }

    private:
        char _data[MaxType<Types...>::value];
        std::type_index _typeIndex;
    };
}
#endif
