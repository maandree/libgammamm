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
#ifndef LIBGAMMA_FACADE_HH
#define LIBGAMMA_FACADE_HH


#include <string>
#include <vector>

#include "libgamma-native.hh"
#include "libgamma-method.hh"


namespace libgamma
{
  /**
   * List available adjustment methods by their order of preference based on the environment.
   * 
   * @param  operation  Allowed values:
   *                      0: Methods that the environment suggests will work, excluding fake.
   *                      1: Methods that the environment suggests will work, including fake.
   *                      2: All real non-fake methods.
   *                      3: All real methods.
   *                      4: All methods.
   *                    Other values invoke undefined behaviour.
   * @return            Array of methods.
   */
  std::vector<int> list_methods(int operation);
  
  /**
   * Check whether an adjustment method is available, non-existing (invalid) methods will be
   * identified as not available under the rationale that the library may be out of date.
   * 
   * @param   method  The adjustment method.
   * @return          Whether the adjustment method is available.
   */
  int is_method_available(int method);
  
  /**
   * Return the capabilities of an adjustment method.
   * 
   * @param  output  The data structure to fill with the method's capabilities,
   * @param  method  The adjustment method (display server and protocol).
   */
  void method_capabilities(MethodCapabilities* output, int method);
  
  /**
   * Return the default site for an adjustment method.
   * 
   * @param   method  The adjustment method (display server and protocol.)
   * @return          The default site, `nullptr` if it cannot be determined or if
   *                  multiple sites are not supported by the adjustment method.
   */
  std::string* method_default_site(int method);
  
  /**
   * Return the default variable that determines
   * the default site for an adjustment method.
   * 
   * @param   method  The adjustment method (display server and protocol.)
   * @return          The environ variables that is used to determine the
   *                  default site. `nullptr` if there is none, that is, if
   *                  the method does not support multiple sites.
   */
  std::string* method_default_site_variable(int method);
  
  /**
   * Convert a raw representation of an EDID to a lowercase hexadecimal representation.
   * 
   * @param   edid    The EDID in raw representation.
   * @param   length  The length of `edid`.
   * @return          The EDID in lowercase hexadecimal representation.
   */
  std::string behex_edid(const unsigned char* edid, size_t length);
  
  /**
   * Convert a raw representation of an EDID to a lowercase hexadecimal representation.
   * 
   * @param   edid    The EDID in raw representation.
   * @param   length  The length of `edid`.
   * @return          The EDID in lowercase hexadecimal representation.
   */
  std::string behex_edid_lowercase(const unsigned char* edid, size_t length);
  
  /**
   * Convert a raw representation of an EDID to an uppercase hexadecimal representation.
   * 
   * @param   edid    The EDID in raw representation.
   * @param   length  The length of `edid`.
   * @return          The EDID in uppercase hexadecimal representation.
   */
  std::string behex_edid_uppercase(const unsigned char* edid, size_t length);
  
  /**
   * Convert an hexadecimal representation of an EDID to a raw representation.
   * 
   * @param   edid  The EDID in hexadecimal representation.
   * @return        The EDID in raw representation, it will be half the length
   *                of `edid` (the input value).
   */
  unsigned char* unhex_edid(const std::string edid);
  
}


#endif

