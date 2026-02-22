/* See LICENSE file for copyright and license details. */
#ifndef LIBGAMMA_FACADE_HH
#define LIBGAMMA_FACADE_HH

#include <string>
#include <vector>

#include "libgamma-native.hh"
#include "libgamma-method.hh"


#if defined(__GNUC__)
# define LIBGAMMAMM_CONST__ __attribute__((__const__))
#else
# define LIBGAMMAMM_CONST__
#endif


namespace libgamma
{
  /**
   * List available adjustment methods by their order of preference based on the environment
   * 
   * @param  operation  Allowed values:
   *                      0: Methods that the environment suggests will work, excluding fake
   *                      1: Methods that the environment suggests will work, including fake
   *                      2: All real non-fake methods
   *                      3: All real methods
   *                      4: All methods
   *                    Other values invoke undefined behaviour
   * @return            Array of methods
   */
  std::vector<int> list_methods(int operation);

  /**
   * Check whether an adjustment method is available, non-existing (invalid) methods will be
   * identified as not available under the rationale that the library may be out of date
   * 
   * @param   method  The adjustment method
   * @return          Whether the adjustment method is available
   */
  LIBGAMMAMM_CONST__ int is_method_available(int method);

  /**
   * Return the capabilities of an adjustment method
   * 
   * @param  output  The data structure to fill with the method's capabilities
   * @param  method  The adjustment method (display server and protocol)
   */
  void method_capabilities(MethodCapabilities *output, int method);

  /**
   * Return the default site for an adjustment method
   * 
   * @param   method  The adjustment method (display server and protocol)
   * @return          The default site, `nullptr` if it cannot be determined or if
   *                  multiple sites are not supported by the adjustment method
   */
  std::string *method_default_site(int method);

  /**
   * Return the default variable that determines
   * the default site for an adjustment method
   * 
   * @param   method  The adjustment method (display server and protocol)
   * @return          The environment variables that is used to determine the
   *                  default site. `nullptr` if there is none, that is, if
   *                  the method does not support multiple sites
   */
  std::string *method_default_site_variable(int method);


  /**
   * Convert a raw representation of an EDID to a lowercase hexadecimal representation
   * 
   * @param   edid    The EDID in raw representation
   * @param   length  The length of `edid`
   * @return          The EDID in lowercase hexadecimal representation
   */
  std::string behex_edid(const unsigned char *edid, size_t length);

  /**
   * Convert a raw representation of an EDID to a lowercase hexadecimal representation
   * 
   * @param   edid    The EDID in raw representation
   * @param   length  The length of `edid`
   * @return          The EDID in lowercase hexadecimal representation
   */
  std::string behex_edid_lowercase(const unsigned char *edid, size_t length);

  /**
   * Convert a raw representation of an EDID to an uppercase hexadecimal representation
   * 
   * @param   edid    The EDID in raw representation
   * @param   length  The length of `edid`
   * @return          The EDID in uppercase hexadecimal representation
   */
  std::string behex_edid_uppercase(const unsigned char *edid, size_t length);

  /**
   * Convert an hexadecimal representation of an EDID to a raw representation
   * 
   * @param   edid  The EDID in hexadecimal representation
   * @return        The EDID in raw representation, it will be half the length
   *                of `edid` (the input value)
   */
  unsigned char *unhex_edid(const std::string edid);


  /**
   * Initialise a gamma ramp in the proper way that allows all adjustment
   * methods to read from and write to it without causing segmentation violation
   * 
   * @param  ramps  The gamma ramp to initialise
   * @param  red    The size of the gamma ramp for the red channel
   * @param  green  The size of the gamma ramp for the green channel
   * @param  blue   The size of the gamma ramp for the blue channel
   */
  void gamma_ramps8_initialise(GammaRamps<uint8_t> *ramps, size_t red, size_t blue, size_t green);

  /**
   * Initialise a gamma ramp in the proper way that allows all adjustment
   * methods to read from and write to it without causing segmentation violation
   * 
   * @param  ramps  The gamma ramp to initialise
   * @param  red    The size of the gamma ramp for the red channel
   * @param  green  The size of the gamma ramp for the green channel
   * @param  blue   The size of the gamma ramp for the blue channel
   */
  void gamma_ramps16_initialise(GammaRamps<uint16_t> *ramps, size_t red, size_t blue, size_t green);

  /**
   * Initialise a gamma ramp in the proper way that allows all adjustment
   * methods to read from and write to it without causing segmentation violation
   * 
   * @param  ramps  The gamma ramp to initialise
   * @param  red    The size of the gamma ramp for the red channel
   * @param  green  The size of the gamma ramp for the green channel
   * @param  blue   The size of the gamma ramp for the blue channel
   */
  void gamma_ramps32_initialise(GammaRamps<uint32_t> *ramps, size_t red, size_t blue, size_t green);

  /**
   * Initialise a gamma ramp in the proper way that allows all adjustment
   * methods to read from and write to it without causing segmentation violation
   * 
   * @param  ramps  The gamma ramp to initialise
   * @param  red    The size of the gamma ramp for the red channel
   * @param  green  The size of the gamma ramp for the green channel
   * @param  blue   The size of the gamma ramp for the blue channel
   */
  void gamma_ramps64_initialise(GammaRamps<uint64_t> *ramps, size_t red, size_t blue, size_t green);

  /**
   * Initialise a gamma ramp in the proper way that allows all adjustment
   * methods to read from and write to it without causing segmentation violation
   * 
   * @param  ramps  The gamma ramp to initialise
   * @param  red    The size of the gamma ramp for the red channel
   * @param  green  The size of the gamma ramp for the green channel
   * @param  blue   The size of the gamma ramp for the blue channel
   */
  void gamma_rampsf_initialise(GammaRamps<float> *ramps, size_t red, size_t blue, size_t green);

  /**
   * Initialise a gamma ramp in the proper way that allows all adjustment
   * methods to read from and write to it without causing segmentation violation
   * 
   * @param  ramps  The gamma ramp to initialise
   * @param  red    The size of the gamma ramp for the red channel
   * @param  green  The size of the gamma ramp for the green channel
   * @param  blue   The size of the gamma ramp for the blue channel
   */
  void gamma_rampsd_initialise(GammaRamps<double> *ramps, size_t red, size_t blue, size_t green);


  /**
   * Create a gamma ramp in the proper way that allows all adjustment
   * methods to read from and write to it without causing segmentation violation
   * 
   * @param   red    The size of the gamma ramp for the red channel
   * @param   green  The size of the gamma ramp for the green channel
   * @param   blue   The size of the gamma ramp for the blue channel
   * @return         The gamma ramp
   */
  GammaRamps<uint8_t> *gamma_ramps8_create(size_t red, size_t blue, size_t green);

  /**
   * Create a gamma ramp in the proper way that allows all adjustment
   * methods to read from and write to it without causing segmentation violation
   * 
   * @param   red    The size of the gamma ramp for the red channel
   * @param   green  The size of the gamma ramp for the green channel
   * @param   blue   The size of the gamma ramp for the blue channel
   * @return         The gamma ramp
   */
  GammaRamps<uint16_t> *gamma_ramps16_create(size_t red, size_t blue, size_t green);

  /**
   * Create a gamma ramp in the proper way that allows all adjustment
   * methods to read from and write to it without causing segmentation violation
   * 
   * @param   red    The size of the gamma ramp for the red channel
   * @param   green  The size of the gamma ramp for the green channel
   * @param   blue   The size of the gamma ramp for the blue channel
   * @return         The gamma ramp
   */
  GammaRamps<uint32_t> *gamma_ramps32_create(size_t red, size_t blue, size_t green);

  /**
   * Create a gamma ramp in the proper way that allows all adjustment
   * methods to read from and write to it without causing segmentation violation
   * 
   * @param   red    The size of the gamma ramp for the red channel
   * @param   green  The size of the gamma ramp for the green channel
   * @param   blue   The size of the gamma ramp for the blue channel
   * @return         The gamma ramp
   */
  GammaRamps<uint64_t> *gamma_ramps64_create(size_t red, size_t blue, size_t green);

  /**
   * Create a gamma ramp in the proper way that allows all adjustment
   * methods to read from and write to it without causing segmentation violation
   * 
   * @param   red    The size of the gamma ramp for the red channel
   * @param   green  The size of the gamma ramp for the green channel
   * @param   blue   The size of the gamma ramp for the blue channel
   * @return         The gamma ramp
   */
  GammaRamps<float> *gamma_rampsf_create(size_t red, size_t blue, size_t green);

  /**
   * Create a gamma ramp in the proper way that allows all adjustment
   * methods to read from and write to it without causing segmentation violation
   * 
   * @param   red    The size of the gamma ramp for the red channel
   * @param   green  The size of the gamma ramp for the green channel
   * @param   blue   The size of the gamma ramp for the blue channel
   * @return         The gamma ramp
   */
  GammaRamps<double> *gamma_rampsd_create(size_t red, size_t blue, size_t green);
}

#endif
