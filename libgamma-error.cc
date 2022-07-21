/* See LICENSE file for copyright and license details. */
#include "libgamma-error.hh"
#include <cstring>
#include <iostream>


namespace libgamma
{
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
	 * @param  name   The text to add at the beginning
	 * @param  value  The error code, may be an `errno` value
	 */
	void
	perror(const std::string name, int error_code)
	{
		libgamma_perror(name.c_str(), error_code);
	}

	/**
	 * Returns the name of the definition associated with a `nullptr` error code
	 * 
	 * @param   value  The error code
	 * @return         The name of the definition associated with the error code,
	 *                 `nullptr` if the error code does not exist
	 */
	std::string *
	name_of_error(int value)
	{
		const char *cstr = libgamma_name_of_error(value);
		if (cstr == nullptr)
			return nullptr;
		return new std::string(cstr);
	}

	/**
	 * Return the value of a `libgamma` error definition refered to by name
	 * 
	 * @param   name  The name of the definition associated with the error code
	 * @return        The error code, zero if the name is `nullptr`
	 *                or does not refer to a `libgamma` error
	 */
	int
	value_of_error(const std::string* name)
	{
		const char *cstr = nullptr;
		if (name != nullptr)
			cstr = name->c_str();
		return libgamma_value_of_error(cstr);
	}


#if defined(__GNUC__)
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wshadow"
#endif

	/**
	 * Constructor
	 * 
	 * @param  error_code  The error code
	 */
	LibgammaException::LibgammaException(int error_code) throw() : error_code(error_code)
	{
		/* do nothing */
	}

	/**
	 * Destructor
	 */
	LibgammaException::~LibgammaException() throw()
	{
		/* do nothing */
	}

	/**
	 * Get the error as a string
	 */
	const char *
	LibgammaException::what() const throw()
	{
		if (this->error_code < 0)
			return libgamma_name_of_error(this->error_code);
		else
			return strerror(this->error_code);
	}

#if defined(__GNUC__)
# pragma GCC diagnostic pop
#endif


	/**
	 * Create an exception from an error code
	 * that may come from `errno.h` or be a
	 * `libgamma` error code
	 * 
	 * @param   error_code  The error code
	 * @return              The error object
	 */
	LibgammaException create_error(int error_code)
	{
		if (error_code == LIBGAMMA_ERRNO_SET)
			error_code = errno;
		return LibgammaException(error_code);
	}


	/**
	 * Group that the user needs to be a member of if
	 * `LIBGAMMA_DEVICE_REQUIRE_GROUP` is returned
	 */
	GroupGid group_gid;

	/**
	 * Group that the user needs to be a member of if
	 * `LIBGAMMA_DEVICE_REQUIRE_GROUP` is returned,
	 * `nullptr` if the name of the group
	 * `libgamma::group_gid` cannot be determined
	 */
	GroupName group_name;
}
