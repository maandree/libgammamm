/**
 * libgammamm -- C++ wrapper for libgamma
 * Copyright (C) 2014  Mattias Andrée (maandree@member.fsf.org)
 * 
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef LIBGAMMA_ERROR_HH
#define LIBGAMMA_ERROR_HH


#include <string>
#include <exception>

#include "libgamma-native.hh"


#ifndef __GCC__
# define __attribute__(X) /* emtpy */
#endif


#ifndef __WIN32__
# define libgamma_gid_t  gid_t
#else
# define libgamma_gid_t  short
#endif



namespace libgamma
{
  /**
   * Class for `group_gid`.
   */
  class GroupGid;
  
  /**
   * Class for `group_name`.
   */
  class GroupName;
  
  
  /**
   * Prints an error to stderr in a `perror` fashion,
   * however this function will not translate the `libgamma`
   * errors into human-readable strings, it will simply
   * print the name of the error. If the value `error_code`
   * is the value of `LIBGAMMA_ERRNO_SET`, `perror` will be
   * used to print the current error stored in `errno`.
   * If `error_code` is non-negative (an `errno` value`), that
   * value will be stored in `errno` and `perror` will be
   * used to print it. Additionally, if the `error_code` is
   * the value of `LIBGAMMA_DEVICE_REQUIRE_GROUP` the
   * required group will be printed with its numerical value
   * and, if known, its name.
   * 
   * @param  name   The text to add at the beginning.
   * @param  value  The error code, may be an `errno` value.
   */
  void perror(const std::string name, int error_code);
  
  /**
   * Returns the name of the definition associated with a `nullptr` error code.
   * 
   * @param   value  The error code.
   * @return         The name of the definition associated with the error code,
   *                 `nullptr` if the error code does not exist.
   */
  std::string* name_of_error(int value);
  
  /**
   * Return the value of a `libgamma` error definition refered to by name.
   * 
   * @param   name  The name of the definition associated with the error code.
   * @return        The error code, zero if the name is `nullptr`
   *                or does not refer to a `libgamma` error.
   */
  int value_of_error(const std::string* name) __attribute__((pure));
  
  
  /**
   * Class for `group_gid`.
   */
  class GroupGid
  {
  public:
    const GroupGid& operator =(const libgamma_gid_t& value) const
    {
      libgamma_group_gid = value;
      return *this;
    }
    
    operator libgamma_gid_t() const
    {
      return libgamma_group_gid;
    }
  };
  
  /**
   * Group that the user needs to be a member of if
   * `LIBGAMMA_DEVICE_REQUIRE_GROUP` is returned.
   */
  extern GroupGid group_gid;
  
  
  /**
   * Class for `group_name`.
   */
  class GroupName
  {
  public:
    const GroupName& operator =(const char* value) const
    {
      libgamma_group_name = value;
      return *this;
    }
    
    operator const char*() const
    {
      return libgamma_group_name;
    }
  };
  
  /**
   * Group that the user needs to be a member of if
   * `LIBGAMMA_DEVICE_REQUIRE_GROUP` is returned,
   * `nullptr` if the name of the group
   * `libgamma::group_gid` cannot be determined.
   */
  extern GroupName group_name;
  
  
  /**
   * Libgamma exception class.
   */
  class LibgammaException : public std::exception
  {
  public:
    /**
     * Constructor.
     * 
     * @param  error_code  The error code.
     */
    LibgammaException(int error_code) throw();
    
    /**
     * Destructor.
     */
    virtual ~LibgammaException() throw();
    
    /**
     * Get the error as a string.
     */
    virtual const char* what() const throw();
    
    /**
     * The error code.
     */
    int error_code;
    
  };
  
  
  /**
   * Create an exception from an error code
   * that may come from `errno.h` or be a
   * `libgamma` error code.
   * 
   * @param   error_code  The error code.
   * @return              The error object.
   */
  LibgammaException create_error(int error_code);
  
}


#ifndef __GCC__
# undef __attribute__
#endif

#endif

