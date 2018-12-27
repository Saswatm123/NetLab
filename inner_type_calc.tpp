#ifndef INNER_TYPE_CALC_H
#define INNER_TYPE_CALC_H

#include <type_traits>

/**Instantiates all types to void*/

template<typename...>
using void_t = void;

/**Hides instantiation of types with conditional typedef ::type */

template<typename T, class = void>
struct hide_type_instantiation
{
    typedef T type;
};

template<typename T>
struct hide_type_instantiation<T, void_t<typename T::type> >
{
    typedef typename T::type type;
};

/**User Interface type checker*/

class UI_type;

template<typename T>
using is_UI_type = typename std::conditional<
      std::is_base_of<UI_type, T>::value, T, std::false_type
                                             >::type;

template<typename T>
using is_UI_type_ref = typename std::conditional<
    std::is_reference       <is_UI_type<T> >::value ||
    std::is_rvalue_reference<is_UI_type<T> >::value,
                  std::true_type, std::false_type>::type;

/**Returns whether a specified type is within a specified variadic argument pack*/

template<typename...ParamList>
struct is_in : std::false_type
{};

template<typename findarg, typename firstarg, typename...ParamList>
struct is_in<findarg, firstarg, ParamList...>
: public std::conditional<
std::is_same<firstarg, findarg>::value, std::true_type, is_in<ParamList...>
                          >::type
{};

/**Turns T into const T& */

template<typename T>
using make_const_ref = typename std::add_lvalue_reference<typename std::add_const<T>::type>::type;

/**Tests whether an argument is in parameter pack of a variadic template type */

template<typename, typename>
struct is_in_variadic_typelist : std::false_type
{};

template<typename findarg, typename firstarg, typename...ParamList, template<class...> class VariadicTemplateType>
struct is_in_variadic_typelist<findarg, VariadicTemplateType<firstarg, ParamList...> >
: public std::conditional<
std::is_same<findarg, firstarg>::value, std::true_type, is_in_variadic_typelist<findarg, VariadicTemplateType<ParamList...> >
                          >::type
{};

/**Subtracts specified type from parameter list of a variadic template type<...> */

namespace detail
{
    template<typename remove_from_list, typename VarHolder>
    struct sub_from_arglist_INNER;

    template<typename remove_from_list, template<class...> class VarHolder, typename...ArgPack>
    struct sub_from_arglist_INNER<remove_from_list, VarHolder<remove_from_list, ArgPack...> >
    {
        typedef VarHolder<ArgPack...> type;
    };

    template<typename remove_from_list, template<class...> class VarHolder, typename different_type, typename...ArgPack>
    struct sub_from_arglist_INNER<remove_from_list, VarHolder<different_type, ArgPack...> >
    {
        typedef typename
        hide_type_instantiation<
        sub_from_arglist_INNER<remove_from_list, VarHolder<ArgPack..., different_type> >
                                >::type type;
    };
}

template<typename, typename>
struct sub_from_arglist;

template<typename remove_from_list, template<class...> class VarHolder, typename...ArgPack>
struct sub_from_arglist<remove_from_list, VarHolder<ArgPack...> >
{
    typedef typename std::conditional<
        is_in<remove_from_list, ArgPack...>::value,
		typename detail::sub_from_arglist_INNER<remove_from_list, VarHolder<ArgPack...> >::type,
        VarHolder<ArgPack...>
                                      >::type type;
};

#endif // INNER_TYPE_CALC_H
