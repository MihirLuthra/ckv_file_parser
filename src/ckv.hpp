#ifndef __CKV_HPP__
#define __CKV_HPP__

/** \file */

/// \cond HEADERS
#include <cstring>
#include <exception>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <ckv_config.hpp>
/// \endcond

namespace ckv {

/**
 * This class acts on a single ckv file that is accociated to
 * it by constructor.
 */
class ConfigFile {
private:
	std::ifstream file_reader; /**< ifstream object associated with file_path */
	std::string file_path;     /**< Current file name as set by the constructor */
	unsigned int err_line_no;  /**< Error line number of the most recently read ckv file */

	void open_file();
	void print_key_val(std::ostream &out, std::string key, std::string value);
	std::string out_block_parse();
	std::string in_block_parse();

public:
	/**
	 * This constructor accepts a file path to accociate
	 * it with the current ConfigFile object. After this
	 * all methods, when called, will perform actions on this file.
	 *
	 * \param file_path
	 * Path to the file.
	 */
	ConfigFile(std::string file_path) : file_path(file_path){}

	/**
	 * Returns the current error line number of the ConfigFile object.
	 *
	 * Error line number may be set after calling any function that reads the ckv file.
	 * If an error occurs while reading the ckv file, its line number is stored.
	 *
	 * \returns Error line number of recently read ckv file.
	 */
	unsigned int get_err_line() {
		return err_line_no;
	}

	/**
	 * \returns file name associated with current ConfigFile object.
	 */
	std::string get_file_path() {
		return file_path;
	}

	void set_value_for_key(std::string key, std::string new_value, std::ostream &out);
	std::string get_value_for_key(std::string key);
	void remove_key(std::string key, std::ostream &out);
	std::unordered_map<std::string, std::string> import_to_map();

	void set_value_for_key(std::string key, std::string new_value);
	void remove_key(std::string key);
};

/**
 * This exception is thrown when an equal to sign is
 * found in the ckv file witout a key name before it.
 */
class EqualToWithoutAKey : public std::exception {
public:
	/// \cond WHAT
	const char *what() const noexcept {
		return "Found '=' without a key";
	}
	/// \endcond
};

/**
 * This exception is thrown when ckv file fails to
 * open.
 */
class FileOpenFailed : public std::exception {
	std::string file_path;
	mutable char *ret_str = nullptr;
public:
	/**
	 * \param file_path
	 * The file path that failed to open.
	 */
	FileOpenFailed(std::string file_path) : file_path(file_path) {}

	~FileOpenFailed() {
		if (ret_str != nullptr) {
			delete ret_str;
		}
	}

	/// \cond WHAT
	const char *what() const noexcept {
		std::ostringstream ret;
		ret << "Failed to open file " << file_path;
		ret_str = strdup(ret.str().c_str());
		return ret_str;
	}
	/// \endcond
};

/**
 * This exception is thrown when a character which is
 * not valid in ckv file is found while reading it.
 */
class InvalidCharacter : public std::exception {
private:
	char c;
	mutable char *ret_str = nullptr;
public:
	/**
	 * \param c
	 * Invalid character
	 */
	InvalidCharacter(char c) : c(c) {}

	~InvalidCharacter() {
		if (ret_str != nullptr) {
			delete ret_str;
		}
	}

	/// \cond WHAT
	const char *what() const noexcept {
		std::ostringstream ret;
		ret << "Invalid character " << this->c;
		ret_str = strdup(ret.str().c_str());
		return ret_str;
	}
	/// \endcond
};

/**
 * This exception is thrown when output stream is invalid
 * to write on.
 */
class InvalidOutputStream : public std::exception {
public:
	/// \cond WHAT
	const char *what() const noexcept {
		return "Invalid output stream";
	}
	/// \endcond
};

/**
 * Exception for key not found.
 */
class KeyNotFound : public std::exception {
private:
	std::string key;
	mutable char *ret_str = nullptr;
public:
	/**
	 * \param key
	 * Key which was being searched and not found.
	 */
	KeyNotFound(std::string key) : key(key) {}

	~KeyNotFound() {
		if(ret_str != nullptr) {
			delete ret_str;
		}
	}

	/// \cond WHAT
	const char *what() const noexcept {
		std::ostringstream ret;
		ret << "\"" << this->key << "\"" << ": key not found";
		ret_str = strdup(ret.str().c_str());
		return ret_str;
	}
	/// \endcond
};

/**
 * Exception thrown when key name is not followed by
 * an equal to sign.
 */
class MissingEqualTo : public std::exception {
public:
	/// \cond WHAT
	const char *what() const noexcept {
		return "Key should be followed by a '='";
	}
	/// \endcond
};

/**
 * Exception thrown when there is no value
 * corresponding to the key.
 */
class NoValueFoundForKey : public std::exception {
private:
	std::string key;
	mutable char *ret_str = nullptr;
public:
	/**
	 * \param key
	 * Key being searched
	 */
	NoValueFoundForKey(std::string key) : key(key) {}

	~NoValueFoundForKey() {
		if(ret_str != nullptr) {
			delete ret_str;
		}
	}

	/// \cond WHAT
	const char *what() const noexcept {
		std::ostringstream ret;
		ret << "\"" << this->key << "\"" << ": No value found for key.";
		ret_str = strdup(ret.str().c_str());
		return ret_str;
	}
	/// \endcond
};

/**
 * Exception for trailing characters after equal to ('=') sign.
 */
class TrailingCharsAfterEqualTo : public std::exception {
public:
	/// \cond WHAT
	const char *what() const noexcept {
		return "Trailing characters after '='";
	}
	/// \endcond
};

/**
 * Exception for value found without a key.
 * Means tabbed contents present in the file without a
 * preceding key.
 */
class ValueWithoutAKey : public std::exception {
public:
	/// \cond WHAT
	const char *what() const noexcept {
		return "Tab found with no preceding key";
	}
	/// \endcond
};

}

/// \cond PRIVATE_MACROS
#define __CKV_BOLD_ON  "[1m"
#define __CKV_BOLD_OFF "[0m"

#define __CKV_P_ERR(fmt, ...) \
	fprintf(stderr, __CKV_BOLD_ON "%s: Line %d: " __CKV_BOLD_OFF fmt "\n", __FILE__, __LINE__, __VA_ARGS__)
/// \endcond

/**
 * \def CKV_EXCEPTION(obj, fmt, e, ...)
 * Prints exception containing ckv file name, error line number and e.what.
 *
 * \a obj
 * ConfigFile object
 *
 * \a fmt
 * fmt like in printf
 *
 * \a e
 * exception
 */
#define CKV_EXCEPTION(obj, fmt, e, ...) \
do {                                    \
    if (obj.get_err_line() != 0) {      \
        __CKV_P_ERR("%s: Line %d: %s" fmt, obj.get_file_path().c_str(), obj.get_err_line(), e.what(), __VA_ARGS__); \
    } else {                            \
        __CKV_P_ERR("%s: %s", obj.get_file_path().c_str(), e.what()); \
    }                                   \
}while (0);

/**
 * \def CKV_EXCEPTION_NA(obj, fmt, e)
 *
 * Same as #CKV_EXCEPTION(obj, fmt, e, ...) but without var args.
 * \__VA_OPT__ can be used here but is still new so avoiding it for portability.
 */
#define CKV_EXCEPTION_NA(obj, fmt, e) \
do {                                  \
    if (obj.get_err_line() != 0) {    \
        __CKV_P_ERR("%s: Line %d: %s" fmt, obj.get_file_path().c_str(), obj.get_err_line(), e.what()); \
    } else {                          \
        __CKV_P_ERR("%s: %s", obj.get_file_path().c_str(), e.what()); \
    }                                 \
}while (0);

/**
 * \def CKV_EXCEPTION_NM(obj, e)
 *
 * Same as #CKV_EXCEPTION(obj, fmt, e, ...) but without fmt and var args.
 */
#define CKV_EXCEPTION_NM(obj, e)     \
do {                                 \
    if (obj.get_err_line() != 0) {   \
        __CKV_P_ERR("%s: Line %d: %s", obj.get_file_path().c_str(), obj.get_err_line(), e.what()); \
    } else {                         \
        __CKV_P_ERR("%s: %s", obj.get_file_path().c_str(), e.what()); \
    }                                \
}while (0);

#endif /* __CKV_HPP__ */
