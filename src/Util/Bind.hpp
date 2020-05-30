/******************************************************************************
 * Bind.hpp
 * Copyright (C) 2019  Mel McCalla <melmccalla@gmail.com>
 *
 * This file is part of GameEngine.
 *
 * GameEngine is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GameEngine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GameEngine.  If not, see <http://www.gnu.org/licenses/>.
 *****************************************************************************/
#ifndef SRC_UTIL_BIND_HPP_
#define SRC_UTIL_BIND_HPP_

namespace game_engine {
namespace util {

struct none {};

template <template <class, class, class, class, class, class, class, class,
                    class, class, class>
          class Class,
          typename Arg1, typename Arg2, typename Arg3, typename Arg4,
          typename Arg5, typename Arg6, typename Arg7, typename Arg8,
          typename Arg9, typename Arg10>
struct bind10 {
  template <class Derived>
  using zeroth = Class<Derived, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8,
                       Arg9, Arg10>;
  template <class Derived>
  using first = Class<Arg1, Derived, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8,
                      Arg9, Arg10>;
  template <class Derived>
  using second = Class<Arg1, Arg2, Derived, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8,
                       Arg9, Arg10>;
  template <class Derived>
  using third = Class<Arg1, Arg2, Arg3, Derived, Arg4, Arg5, Arg6, Arg7, Arg8,
                      Arg9, Arg10>;
  template <class Derived>
  using fourth = Class<Arg1, Arg2, Arg3, Arg4, Derived, Arg5, Arg6, Arg7, Arg8,
                       Arg9, Arg10>;
  template <class Derived>
  using fifth = Class<Arg1, Arg2, Arg3, Arg4, Arg5, Derived, Arg6, Arg7, Arg8,
                      Arg9, Arg10>;
  template <class Derived>
  using sixth = Class<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Derived, Arg7, Arg8,
                      Arg9, Arg10>;
  template <class Derived>
  using seventh = Class<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Derived, Arg8,
                        Arg9, Arg10>;
  template <class Derived>
  using eigth = Class<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Derived,
                      Arg9, Arg10>;
  template <class Derived>
  using ninth = Class<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9,
                      Derived, Arg10>;
  template <class Derived>
  using tenth = Class<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9,
                      Arg10, Derived>;
};

template <template <class, class, class, class, class, class, class, class,
                    class, class>
          class Class,
          typename Arg1, typename Arg2, typename Arg3, typename Arg4,
          typename Arg5, typename Arg6, typename Arg7, typename Arg8,
          typename Arg9>
struct bind9 {
  template <class Derived>
  using zeroth =
      Class<Derived, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9>;
  template <class Derived>
  using first =
      Class<Arg1, Derived, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9>;
  template <class Derived>
  using second =
      Class<Arg1, Arg2, Derived, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9>;
  template <class Derived>
  using third =
      Class<Arg1, Arg2, Arg3, Derived, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9>;
  template <class Derived>
  using fourth =
      Class<Arg1, Arg2, Arg3, Arg4, Derived, Arg5, Arg6, Arg7, Arg8, Arg9>;
  template <class Derived>
  using fifth =
      Class<Arg1, Arg2, Arg3, Arg4, Arg5, Derived, Arg6, Arg7, Arg8, Arg9>;
  template <class Derived>
  using sixth =
      Class<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Derived, Arg7, Arg8, Arg9>;
  template <class Derived>
  using seventh =
      Class<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Derived, Arg8, Arg9>;
  template <class Derived>
  using eigth =
      Class<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Derived, Arg9>;
  template <class Derived>
  using ninth =
      Class<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Derived>;
};

template <
    template <class, class, class, class, class, class, class, class, class>
    class Class,
    typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5,
    typename Arg6, typename Arg7, typename Arg8>
struct bind8 {
  template <class Derived>
  using zeroth = Class<Derived, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8>;
  template <class Derived>
  using first = Class<Arg1, Derived, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8>;
  template <class Derived>
  using second = Class<Arg1, Arg2, Derived, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8>;
  template <class Derived>
  using third = Class<Arg1, Arg2, Arg3, Derived, Arg4, Arg5, Arg6, Arg7, Arg8>;
  template <class Derived>
  using fourth = Class<Arg1, Arg2, Arg3, Arg4, Derived, Arg5, Arg6, Arg7, Arg8>;
  template <class Derived>
  using fifth = Class<Arg1, Arg2, Arg3, Arg4, Arg5, Derived, Arg6, Arg7, Arg8>;
  template <class Derived>
  using sixth = Class<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Derived, Arg7, Arg8>;
  template <class Derived>
  using seventh =
      Class<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Derived, Arg8>;
  template <class Derived>
  using eigth = Class<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Derived>;
};

template <template <class, class, class, class, class, class, class, class>
          class Class,
          typename Arg1, typename Arg2, typename Arg3, typename Arg4,
          typename Arg5, typename Arg6, typename Arg7>
struct bind7 {
  template <class Derived>
  using zeroth = Class<Derived, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>;
  template <class Derived>
  using first = Class<Arg1, Derived, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>;
  template <class Derived>
  using second = Class<Arg1, Arg2, Derived, Arg3, Arg4, Arg5, Arg6, Arg7>;
  template <class Derived>
  using third = Class<Arg1, Arg2, Arg3, Derived, Arg4, Arg5, Arg6, Arg7>;
  template <class Derived>
  using fourth = Class<Arg1, Arg2, Arg3, Arg4, Derived, Arg5, Arg6, Arg7>;
  template <class Derived>
  using fifth = Class<Arg1, Arg2, Arg3, Arg4, Arg5, Derived, Arg6, Arg7>;
  template <class Derived>
  using sixth = Class<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Derived, Arg7>;
  template <class Derived>
  using seventh = Class<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Derived>;
};

template <template <class, class, class, class, class, class, class>
          class Class,
          typename Arg1, typename Arg2, typename Arg3, typename Arg4,
          typename Arg5, typename Arg6>
struct bind6 {
  template <class Derived>
  using zeroth = Class<Derived, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6>;
  template <class Derived>
  using first = Class<Arg1, Derived, Arg2, Arg3, Arg4, Arg5, Arg6>;
  template <class Derived>
  using second = Class<Arg1, Arg2, Derived, Arg3, Arg4, Arg5, Arg6>;
  template <class Derived>
  using third = Class<Arg1, Arg2, Arg3, Derived, Arg4, Arg5, Arg6>;
  template <class Derived>
  using fourth = Class<Arg1, Arg2, Arg3, Arg4, Derived, Arg5, Arg6>;
  template <class Derived>
  using fifth = Class<Arg1, Arg2, Arg3, Arg4, Arg5, Derived, Arg6>;
  template <class Derived>
  using sixth = Class<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Derived>;
};

template <template <class, class, class, class, class, class> class Class,
          typename Arg1, typename Arg2, typename Arg3, typename Arg4,
          typename Arg5>
struct bind5 {
  template <class Derived>
  using zeroth = Class<Derived, Arg1, Arg2, Arg3, Arg4, Arg5>;
  template <class Derived>
  using first = Class<Arg1, Derived, Arg2, Arg3, Arg4, Arg5>;
  template <class Derived>
  using second = Class<Arg1, Arg2, Derived, Arg3, Arg4, Arg5>;
  template <class Derived>
  using third = Class<Arg1, Arg2, Arg3, Derived, Arg4, Arg5>;
  template <class Derived>
  using fourth = Class<Arg1, Arg2, Arg3, Arg4, Derived, Arg5>;
  template <class Derived>
  using fifth = Class<Arg1, Arg2, Arg3, Arg4, Arg5, Derived>;
};

template <template <class, class, class, class, class> class Class,
          typename Arg1, typename Arg2, typename Arg3, typename Arg4>
struct bind4 {
  template <class Derived>
  using zeroth = Class<Derived, Arg1, Arg2, Arg3, Arg4>;
  template <class Derived>
  using first = Class<Arg1, Derived, Arg2, Arg3, Arg4>;
  template <class Derived>
  using second = Class<Arg1, Arg2, Derived, Arg3, Arg4>;
  template <class Derived>
  using third = Class<Arg1, Arg2, Arg3, Derived, Arg4>;
  template <class Derived>
  using fourth = Class<Arg1, Arg2, Arg3, Arg4, Derived>;
};

template <template <class, class, class, class> class Class, typename Arg1,
          typename Arg2, typename Arg3>
struct bind3 {
  template <class Derived>
  using zeroth = Class<Derived, Arg1, Arg2, Arg3>;
  template <class Derived>
  using first = Class<Arg1, Derived, Arg2, Arg3>;
  template <class Derived>
  using second = Class<Arg1, Arg2, Derived, Arg3>;
  template <class Derived>
  using third = Class<Arg1, Arg2, Arg3, Derived>;
};

template <template <class, class, class> class Class, typename Arg1,
          typename Arg2>
struct bind2 {
  template <class Derived>
  using zeroth = Class<Derived, Arg1, Arg2>;
  template <class Derived>
  using first = Class<Arg1, Derived, Arg2>;
  template <class Derived>
  using second = Class<Arg1, Arg2, Derived>;
};

template <template <class, class> class Class, typename Arg1>
struct bind1 {
  template <class Derived>
  using zeroth = Class<Derived, Arg1>;
  template <class Derived>
  using first = Class<Arg1, Derived>;
};

template <template <class> class Class>
struct bind0 {
  template <class Derived>
  using zeroth = Class<Derived>;
};

template <template <class derived, typename... class_args> class Class,
          typename Arg1 = none, typename Arg2 = none, typename Arg3 = none,
          typename Arg4 = none, typename Arg5 = none, typename Arg6 = none,
          typename Arg7 = none, typename Arg8 = none, typename Arg9 = none,
          typename Arg10 = none>
struct bind : public bind10<Class, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7,
                            Arg8, Arg9, Arg10> {};

template <template <class derived, typename... class_args> class Class,
          typename Arg1, typename Arg2, typename Arg3, typename Arg4,
          typename Arg5, typename Arg6, typename Arg7, typename Arg8,
          typename Arg9>
struct bind<Class, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, none>
    : public bind9<Class, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8,
                   Arg9> {};

template <template <class derived, typename... class_args> class Class,
          typename Arg1, typename Arg2, typename Arg3, typename Arg4,
          typename Arg5, typename Arg6, typename Arg7, typename Arg8>
struct bind<Class, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, none, none>
    : public bind8<Class, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8> {};

template <template <class derived, typename... class_args> class Class,
          typename Arg1, typename Arg2, typename Arg3, typename Arg4,
          typename Arg5, typename Arg6, typename Arg7>
struct bind<Class, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, none, none, none>
    : public bind7<Class, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7> {};

template <template <class derived, typename... class_args> class Class,
          typename Arg1, typename Arg2, typename Arg3, typename Arg4,
          typename Arg5, typename Arg6>
struct bind<Class, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, none, none, none, none>
    : public bind6<Class, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6> {};

template <template <class derived, typename... class_args> class Class,
          typename Arg1, typename Arg2, typename Arg3, typename Arg4,
          typename Arg5>
struct bind<Class, Arg1, Arg2, Arg3, Arg4, Arg5, none, none, none, none, none>
    : public bind5<Class, Arg1, Arg2, Arg3, Arg4, Arg5> {};

template <template <class derived, typename... class_args> class Class,
          typename Arg1, typename Arg2, typename Arg3, typename Arg4>
struct bind<Class, Arg1, Arg2, Arg3, Arg4, none, none, none, none, none, none>
    : public bind4<Class, Arg1, Arg2, Arg3, Arg4> {};

template <template <class derived, typename... class_args> class Class,
          typename Arg1, typename Arg2, typename Arg3>
struct bind<Class, Arg1, Arg2, Arg3, none, none, none, none, none, none, none>
    : public bind3<Class, Arg1, Arg2, Arg3> {};

template <template <class derived, typename... class_args> class Class,
          typename Arg1, typename Arg2>
struct bind<Class, Arg1, Arg2, none, none, none, none, none, none, none, none>
    : public bind2<Class, Arg1, Arg2> {};

template <template <class derived, typename... class_args> class Class,
          typename Arg1>
struct bind<Class, Arg1, none, none, none, none, none, none, none, none, none>
    : public bind1<Class, Arg1> {};

template <template <class derived, typename... class_args> class Class>
struct bind<Class, none, none, none, none, none, none, none, none, none, none>
    : public bind0<Class> {};

} /* namespace util */
} /* namespace game_engine */

#endif /* SRC_UTIL_BIND_HPP_ */
