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
#include "libgamma-facade.hh"

#include "libgamma-error.hh"

#include <cstdlib>


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
  std::vector<int> list_methods(int operation)
  {
    int* methods = (int*)malloc(LIBGAMMA_METHOD_COUNT * sizeof(int));
    size_t n, i;
    std::vector<int> rc;
    
    n = libgamma_list_methods(methods, LIBGAMMA_METHOD_COUNT, operation);
    if (n > LIBGAMMA_METHOD_COUNT)
      {
	free(methods);
	methods = (int*)malloc(n * sizeof(int));
	libgamma_list_methods(methods, n, operation);
      }
    
    for (i = 0; i < n; i++)
      rc.push_back(methods[i]);
    
    free(methods);
    return rc;
  }
  
  /**
   * Check whether an adjustment method is available, non-existing (invalid) methods will be
   * identified as not available under the rationale that the library may be out of date.
   * 
   * @param   method  The adjustment method.
   * @return          Whether the adjustment method is available.
   */
  int is_method_available(int method)
  {
    return libgamma_is_method_available(method);
  }
  
  /**
   * Return the capabilities of an adjustment method.
   * 
   * @param  output  The data structure to fill with the method's capabilities,
   * @param  method  The adjustment method (display server and protocol).
   */
  void method_capabilities(MethodCapabilities* output, int method)
  {
    libgamma_method_capabilities_t caps;
    libgamma_method_capabilities(&caps, method);
    *output = MethodCapabilities(&caps);
  }
  
  /**
   * Return the default site for an adjustment method.
   * 
   * @param   method  The adjustment method (display server and protocol.)
   * @return          The default site, `nullptr` if it cannot be determined or if
   *                  multiple sites are not supported by the adjustment method.
   */
  std::string* method_default_site(int method)
  {
    char* cstr = libgamma_method_default_site(method);
    if (cstr == nullptr)
      return nullptr;
    return new std::string(cstr);
  }
  
  /**
   * Return the default variable that determines
   * the default site for an adjustment method.
   * 
   * @param   method  The adjustment method (display server and protocol.)
   * @return          The environ variables that is used to determine the
   *                  default site. `nullptr` if there is none, that is, if
   *                  the method does not support multiple sites.
   *                  This value should not be `free`:d.
   */
  std::string* method_default_site_variable(int method)
  {
    const char* cstr = libgamma_method_default_site_variable(method);
    if (cstr == nullptr)
      return nullptr;
    return new std::string(cstr);
  }
  
  
  /**
   * Convert a raw representation of an EDID to a lowercase hexadecimal representation.
   * 
   * @param   edid    The EDID in raw representation.
   * @param   length  The length of `edid`.
   * @return          The EDID in lowercase hexadecimal representation.
   */
  std::string behex_edid(const unsigned char* edid, size_t length)
  {
    return behex_edid_lowercase(edid, length);
  }
  
  /**
   * Convert a raw representation of an EDID to a lowercase hexadecimal representation.
   * 
   * @param   edid    The EDID in raw representation.
   * @param   length  The length of `edid`.
   * @return          The EDID in lowercase hexadecimal representation.
   */
  std::string behex_edid_lowercase(const unsigned char* edid, size_t length)
  {
    char* cstr = libgamma_behex_edid_lowercase(edid, length);
    std::string rc = std::string(cstr);
    free(cstr);
    return rc;
  }
  
  /**
   * Convert a raw representation of an EDID to an uppercase hexadecimal representation.
   * 
   * @param   edid    The EDID in raw representation.
   * @param   length  The length of `edid`.
   * @return          The EDID in uppercase hexadecimal representation.
   */
  std::string behex_edid_uppercase(const unsigned char* edid, size_t length)
  {
    char* cstr = libgamma_behex_edid_uppercase(edid, length);
    std::string rc = std::string(cstr);
    free(cstr);
    return rc;
  }
  
  /**
   * Convert an hexadecimal representation of an EDID to a raw representation.
   * 
   * @param   edid  The EDID in hexadecimal representation.
   * @return        The EDID in raw representation, it will be half the length
   *                of `edid` (the input value).
   */
  unsigned char* unhex_edid(const std::string edid)
  {
    const char* cstr = edid.c_str();
    return libgamma_unhex_edid(cstr);
  }
  
  
  /**
   * Initialise a gamma ramp in the proper way that allows all adjustment
   * methods to read from and write to it without causing segmentation violation.
   * 
   * @param  ramps  The gamma ramp to initialise.
   * @param  red    The size of the gamma ramp for the red channel.
   * @param  green  The size of the gamma ramp for the green channel.
   * @param  blue   The size of the gamma ramp for the blue channel.
   */
  void gamma_ramps8_initialise(GammaRamps<uint8_t>* ramps, size_t red, size_t blue, size_t green)
  {
    libgamma_gamma_ramps8_t native;
    int r;
    native.red_size   = ramps->red.size   = red;
    native.green_size = ramps->green.size = green;
    native.blue_size  = ramps->blue.size  = blue;
    ramps->depth = 8;
    r = libgamma_gamma_ramps8_initialise(&native);
    if (r != 0)
      throw create_error(r);
    ramps->red.ramp   = native.red;
    ramps->green.ramp = native.green;
    ramps->blue.ramp  = native.blue;
  }
  
  /**
   * Initialise a gamma ramp in the proper way that allows all adjustment
   * methods to read from and write to it without causing segmentation violation.
   * 
   * @param  ramps  The gamma ramp to initialise.
   * @param  red    The size of the gamma ramp for the red channel.
   * @param  green  The size of the gamma ramp for the green channel.
   * @param  blue   The size of the gamma ramp for the blue channel.
   */
  void gamma_ramps16_initialise(GammaRamps<uint16_t>* ramps, size_t red, size_t blue, size_t green)
  {
    libgamma_gamma_ramps16_t native;
    int r;
    native.red_size   = ramps->red.size   = red;
    native.green_size = ramps->green.size = green;
    native.blue_size  = ramps->blue.size  = blue;
    ramps->depth = 16;
    r = libgamma_gamma_ramps16_initialise(&native);
    if (r != 0)
      throw create_error(r);
    ramps->red.ramp   = native.red;
    ramps->green.ramp = native.green;
    ramps->blue.ramp  = native.blue;
  }
  
  /**
   * Initialise a gamma ramp in the proper way that allows all adjustment
   * methods to read from and write to it without causing segmentation violation.
   * 
   * @param  ramps  The gamma ramp to initialise.
   * @param  red    The size of the gamma ramp for the red channel.
   * @param  green  The size of the gamma ramp for the green channel.
   * @param  blue   The size of the gamma ramp for the blue channel.
   */
  void gamma_ramps32_initialise(GammaRamps<uint32_t>* ramps, size_t red, size_t blue, size_t green)
  {
    libgamma_gamma_ramps32_t native;
    int r;
    native.red_size   = ramps->red.size   = red;
    native.green_size = ramps->green.size = green;
    native.blue_size  = ramps->blue.size  = blue;
    ramps->depth = 32;
    r = libgamma_gamma_ramps32_initialise(&native);
    if (r != 0)
      throw create_error(r);
    ramps->red.ramp   = native.red;
    ramps->green.ramp = native.green;
    ramps->blue.ramp  = native.blue;
  }
  
  /**
   * Initialise a gamma ramp in the proper way that allows all adjustment
   * methods to read from and write to it without causing segmentation violation.
   * 
   * @param  ramps  The gamma ramp to initialise.
   * @param  red    The size of the gamma ramp for the red channel.
   * @param  green  The size of the gamma ramp for the green channel.
   * @param  blue   The size of the gamma ramp for the blue channel.
   */
  void gamma_ramps64_initialise(GammaRamps<uint64_t>* ramps, size_t red, size_t blue, size_t green)
  {
    libgamma_gamma_ramps64_t native;
    int r;
    native.red_size   = ramps->red.size   = red;
    native.green_size = ramps->green.size = green;
    native.blue_size  = ramps->blue.size  = blue;
    ramps->depth = 64;
    r = libgamma_gamma_ramps64_initialise(&native);
    if (r != 0)
      throw create_error(r);
    ramps->red.ramp   = native.red;
    ramps->green.ramp = native.green;
    ramps->blue.ramp  = native.blue;
  }
  
  /**
   * Initialise a gamma ramp in the proper way that allows all adjustment
   * methods to read from and write to it without causing segmentation violation.
   * 
   * @param  ramps  The gamma ramp to initialise.
   * @param  red    The size of the gamma ramp for the red channel.
   * @param  green  The size of the gamma ramp for the green channel.
   * @param  blue   The size of the gamma ramp for the blue channel.
   */
  void gamma_rampsf_initialise(GammaRamps<float>* ramps, size_t red, size_t blue, size_t green)
  {
    libgamma_gamma_rampsf_t native;
    int r;
    native.red_size   = ramps->red.size   = red;
    native.green_size = ramps->green.size = green;
    native.blue_size  = ramps->blue.size  = blue;
    ramps->depth = -1;
    r = libgamma_gamma_rampsf_initialise(&native);
    if (r != 0)
      throw create_error(r);
    ramps->red.ramp   = native.red;
    ramps->green.ramp = native.green;
    ramps->blue.ramp  = native.blue;
  }
  
  /**
   * Initialise a gamma ramp in the proper way that allows all adjustment
   * methods to read from and write to it without causing segmentation violation.
   * 
   * @param  ramps  The gamma ramp to initialise.
   * @param  red    The size of the gamma ramp for the red channel.
   * @param  green  The size of the gamma ramp for the green channel.
   * @param  blue   The size of the gamma ramp for the blue channel.
   */
  void gamma_rampsd_initialise(GammaRamps<double>* ramps, size_t red, size_t blue, size_t green)
  {
    libgamma_gamma_rampsd_t native;
    int r;
    native.red_size   = ramps->red.size   = red;
    native.green_size = ramps->green.size = green;
    native.blue_size  = ramps->blue.size  = blue;
    ramps->depth = -2;
    r = libgamma_gamma_rampsd_initialise(&native);
    if (r != 0)
      throw create_error(r);
    ramps->red.ramp   = native.red;
    ramps->green.ramp = native.green;
    ramps->blue.ramp  = native.blue;
  }
  
  
  /**
   * Create a gamma ramp in the proper way that allows all adjustment
   * methods to read from and write to it without causing segmentation violation.
   * 
   * @param   red    The size of the gamma ramp for the red channel.
   * @param   green  The size of the gamma ramp for the green channel.
   * @param   blue   The size of the gamma ramp for the blue channel.
   * @return         The gamma ramp.
   */
  GammaRamps<uint8_t>* gamma_ramps8_create(size_t red, size_t blue, size_t green)
  {
    libgamma_gamma_ramps8_t ramps;
    int r;
    ramps.red_size = red;
    ramps.green_size = green;
    ramps.blue_size = blue;
    r = libgamma_gamma_ramps8_initialise(&ramps);
    if (r != 0)
      throw create_error(r);
    return new GammaRamps<uint8_t>(ramps.red, ramps.green, ramps.blue, red, green, blue, 8);
  }
  
  /**
   * Create a gamma ramp in the proper way that allows all adjustment
   * methods to read from and write to it without causing segmentation violation.
   * 
   * @param   red    The size of the gamma ramp for the red channel.
   * @param   green  The size of the gamma ramp for the green channel.
   * @param   blue   The size of the gamma ramp for the blue channel.
   * @return         The gamma ramp.
   */
  GammaRamps<uint16_t>* gamma_ramps16_create(size_t red, size_t blue, size_t green)
  {
    libgamma_gamma_ramps16_t ramps;
    int r;
    ramps.red_size = red;
    ramps.green_size = green;
    ramps.blue_size = blue;
    r = libgamma_gamma_ramps16_initialise(&ramps);
    if (r != 0)
      throw create_error(r);
    return new GammaRamps<uint16_t>(ramps.red, ramps.green, ramps.blue, red, green, blue, 16);
  }
  
  /**
   * Create a gamma ramp in the proper way that allows all adjustment
   * methods to read from and write to it without causing segmentation violation.
   * 
   * @param   red    The size of the gamma ramp for the red channel.
   * @param   green  The size of the gamma ramp for the green channel.
   * @param   blue   The size of the gamma ramp for the blue channel.
   * @return         The gamma ramp.
   */
  GammaRamps<uint32_t>* gamma_ramps32_create(size_t red, size_t blue, size_t green)
  {
    libgamma_gamma_ramps32_t ramps;
    int r;
    ramps.red_size = red;
    ramps.green_size = green;
    ramps.blue_size = blue;
    r = libgamma_gamma_ramps32_initialise(&ramps);
    if (r != 0)
      throw create_error(r);
    return new GammaRamps<uint32_t>(ramps.red, ramps.green, ramps.blue, red, green, blue, 32);
  }
  
  /**
   * Create a gamma ramp in the proper way that allows all adjustment
   * methods to read from and write to it without causing segmentation violation.
   * 
   * @param   red    The size of the gamma ramp for the red channel.
   * @param   green  The size of the gamma ramp for the green channel.
   * @param   blue   The size of the gamma ramp for the blue channel.
   * @return         The gamma ramp.
   */
  GammaRamps<uint64_t>* gamma_ramps64_create(size_t red, size_t blue, size_t green)
  {
    libgamma_gamma_ramps64_t ramps;
    int r;
    ramps.red_size = red;
    ramps.green_size = green;
    ramps.blue_size = blue;
    r = libgamma_gamma_ramps64_initialise(&ramps);
    if (r != 0)
      throw create_error(r);
    return new GammaRamps<uint64_t>(ramps.red, ramps.green, ramps.blue, red, green, blue, 64);
  }
  
  /**
   * Create a gamma ramp in the proper way that allows all adjustment
   * methods to read from and write to it without causing segmentation violation.
   * 
   * @param   red    The size of the gamma ramp for the red channel.
   * @param   green  The size of the gamma ramp for the green channel.
   * @param   blue   The size of the gamma ramp for the blue channel.
   * @return         The gamma ramp.
   */
  GammaRamps<float>* gamma_rampsf_create(size_t red, size_t blue, size_t green)
  {
    libgamma_gamma_rampsf_t ramps;
    int r;
    ramps.red_size = red;
    ramps.green_size = green;
    ramps.blue_size = blue;
    r = libgamma_gamma_rampsf_initialise(&ramps);
    if (r != 0)
      throw create_error(r);
    return new GammaRamps<float>(ramps.red, ramps.green, ramps.blue, red, green, blue, -1);
  }
  
  /**
   * Create a gamma ramp in the proper way that allows all adjustment
   * methods to read from and write to it without causing segmentation violation.
   * 
   * @param   red    The size of the gamma ramp for the red channel.
   * @param   green  The size of the gamma ramp for the green channel.
   * @param   blue   The size of the gamma ramp for the blue channel.
   * @return         The gamma ramp.
   */
  GammaRamps<double>* gamma_rampsd_create(size_t red, size_t blue, size_t green)
  {
    libgamma_gamma_rampsd_t ramps;
    int r;
    ramps.red_size = red;
    ramps.green_size = green;
    ramps.blue_size = blue;
    r = libgamma_gamma_rampsd_initialise(&ramps);
    if (r != 0)
      throw create_error(r);
    return new GammaRamps<double>(ramps.red, ramps.green, ramps.blue, red, green, blue, -2);
  }
  
}

