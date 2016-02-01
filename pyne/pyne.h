// This file is composed of the following original files:

//   src/_atomic_data.h
//   src/data.h
//   src/nucname.h
//   src/utils.h
//   src/extra_types.h
//   src/rxname.h

//
// start of src/utils.h
//
/// \brief This is the base PyNE library.
///
/// It contains a lot of utility functions and constants that are globaly useful
/// through out the rest of the PyNE infrastructure.
///

// Header for general library file.

#ifndef PYNE_KMMHYNANYFF5BFMEYIP7TUNLHA
#define PYNE_KMMHYNANYFF5BFMEYIP7TUNLHA

//standard libraries
#include <string>
#include <string.h>
#include <sstream>
#include <cctype>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <exception>
#include <sys/stat.h>
#include <sys/types.h>
#include <cstdlib>
#include <vector>
#include <algorithm>

#if defined __APPLE__ || defined __WIN_GNUC__
#if (__GNUC__ >= 4)
  #include <cmath>
  #define isnan(x) std::isnan(x)
#else
  #include <math.h>
  #define isnan(x) __isnand((double)x)
#endif
#endif

#ifdef __WIN_MSVC__
    #define isnan(x) ((x) != (x))
#endif

#ifndef JSON_IS_AMALGAMATION
  #define JSON_IS_AMALGAMATION
#endif

/// The 'pyne' namespace all PyNE functionality is included in.
namespace pyne {

  void pyne_start (); ///< Initializes PyNE based on environment.

  /// Path to the directory containing the PyNE data.
  extern std::string PYNE_DATA;
  extern std::string NUC_DATA_PATH; ///< Path to the nuc_data.h5 file.

  // String Transformations
  /// string of digit characters
  static std::string digits = "0123456789";
  /// uppercase alphabetical characters
  static std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  /// string of all valid word characters for variable names in programing languages.
  static std::string words = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_";

  /// \name String Conversion Functions
  /// \{
  /// Converts the variables of various types to their C++ string representation.
  std::string to_str(int t);
  std::string to_str(unsigned int t);
  std::string to_str(double t);
  std::string to_str(bool t);
  /// \}

  int to_int(std::string s);  ///< Converts a string of digits to an int using atoi().

  double to_dbl(std::string s);  ///< Converts a valid string to a float using atof().

  /// Converts a string from ENDF format to a float. Only handles E-less format
  /// but is roughly 5 times faster than endftod.
  double endftod_cpp(char * s);
  double endftod_f(char * s); ///< Converts a string from ENDF format to a float.
  extern  double (*endftod)(char * s); ///< endftod function pointer. defaults to fortran

  void use_fast_endftod();/// switches endftod to fast cpp version

  /// Returns an all upper case copy of the string.
  std::string to_upper(std::string s);

  /// Returns an all lower case copy of the string.
  std::string to_lower(std::string s);

  /// Returns a capitalized copy of the string.
  std::string capitalize(std::string s);

  /// Finds and returns the first white-space delimited token of a line.
  /// \param line a character array to take the first token from.
  /// \param max_l an upper bound to the length of the token.  Must be 11 or less.
  /// \returns a the flag as a string
  std::string get_flag(char line[], int max_l);

  /// Creates a copy of \a s with all instances of \a substr taken out.
  std::string remove_substring(std::string s, std::string substr);

  /// Removes all characters in the string \a chars from \a s.
  std::string remove_characters(std::string s, std::string chars);

  /// Replaces all instance of \a substr in \a s with \a repstr.
  std::string replace_all_substrings(std::string s, std::string substr,
                                                    std::string repstr);

  /// Returns the last character in a string.
  std::string last_char(std::string s);

  /// Returns the slice of a string \a s using the negative index \a n and the
  /// length of the slice \a l.
  std::string slice_from_end(std::string s, int n=-1, int l=1);

  /// Returns true if \a a <= \a b <= \a c and flase otherwise.
  bool ternary_ge(int a, int b, int c);

  /// Returns true if \a substr is in \a s.
  bool contains_substring(std::string s, std::string substr);

  /// Calculates a version of the string \a name that is also a valid variable name.
  /// That is to say that the return value uses only word characters.
  std::string natural_naming(std::string name);

  /// Finds the slope of a line from the points (\a x1, \a y1) and (\a x2, \a y2).
  double slope (double x2, double y2, double x1, double y1);

  /// Solves the equation for the line y = mx + b, given \a x and the points that
  /// form the line: (\a x1, \a y1) and (\a x2, \a y2).
  double solve_line (double x, double x2, double y2, double x1, double y1);

  double tanh(double x);  ///< The hyperbolic tangent function.
  double coth(double x);  ///< The hyperbolic cotangent function.


  // File Helpers
  /// Returns true if the file can be found.
  bool file_exists(std::string strfilename);

  // Message Helpers
  extern bool USE_WARNINGS;
  /// Toggles warnings on and off
  bool toggle_warnings();

  /// Prints a warning message.
  void warning(std::string s);

  /// Custom exception to be thrown in the event that a required file is not able to
  /// be found.
  class FileNotFound : public std::exception
  {
  public:

    /// default constructor
    FileNotFound () {};

    /// default destructor
    ~FileNotFound () throw () {};

    /// constructor with the filename \a fname.
    FileNotFound(std::string fname)
    {
      filename = fname;
    };

    /// Creates a helpful error message.
    virtual const char* what() const throw()
    {
      std::string FNFstr ("File not found: ");
      if (!filename.empty())
        FNFstr += filename;

      return (const char *) FNFstr.c_str();
    };

  private:
    std::string filename; ///< unfindable filename.
  };


// End PyNE namespace
}

#endif  // PYNE_KMMHYNANYFF5BFMEYIP7TUNLHA
//
// end of src/utils.h
//


// PyNE amalgated header http://pyne.io/
#ifndef PYNE_52BMSKGZ3FHG3NQI566D4I2ZLY
#define PYNE_52BMSKGZ3FHG3NQI566D4I2ZLY

#define PYNE_IS_AMALGAMATED

//
// start of src/_atomic_data.h
//
/// \/file atomic_nuclear_data.h
/// \/author Andrew Davis (andrew.davis@wisc.edu)
///
/// \/brief Impliments all the fundamental atomic & nuclear data data
#include <map>

namespace pyne
{
  /// main function to be called when you whish to load the nuclide data
  /// into memory
  void _load_atomic_mass_map_memory();
  /// function to create mapping from nuclides in id form
  /// to their atomic masses

  void _insert_atomic_mass_map();

  /// function to create mapping from nuclides in id form
  /// to their natural abundances
  void _insert_abund_map();

  /// Mapping from nuclides in id form to their natural abundances
  extern std::map<int,double> natural_abund_map;

  /// Mapping from nuclides in id form to their atomic masses.
  extern std::map<int,double> atomic_mass_map;

  /// Mapping from nuclides in id form to the associated error in
  /// abdundance
  extern std::map<int,double> atomic_mass_error_map;
} // namespace pyne
//
// end of src/_atomic_data.h
//


//
// start of src/data.h
//
/// \file data.h
/// \author Anthony Scopatz (scopatz\@gmail.com)
///
/// \brief Implements basic nuclear data functions.

#ifndef PYNE_TEWK4A7VOFFLHDDXD5ZZ7KPXEQ
#define PYNE_TEWK4A7VOFFLHDDXD5ZZ7KPXEQ
#include <iostream>
#include <string>
#include <utility>
#include <map>
#include <set>
#include <limits>
#include <exception>
#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include <math.h>

#ifndef PYNE_IS_AMALGAMATED
#include "h5wrap.h"
#include "extra_types.h"
#include "utils.h"
#include "nucname.h"
#include "rxname.h"
#endif

namespace pyne
{
  /// \name Mathematical and Physical Constants
  /// \{
  extern const double pi;   ///< pi = 3.14159265359
  extern const double N_A;  ///< Avogadro's Number
  extern const double barns_per_cm2;  ///< barns per cm^2
  extern const double cm2_per_barn;   ///< cm^2 per barn
  extern const double sec_per_day;    ///< seconds per day
  extern const double MeV_per_K;    ///< MeV per Kelvin
  extern const double MeV_per_MJ;  ///< MeV per MJ
  extern const double Bq_per_Ci;   ///< Becquerel per Curie
  extern const double Ci_per_Bq;   ///< Curies per Becquerel
  /// \}

  extern std::string NUC_DATA_PATH; ///< Path to the nuc_data.h5 file.

  /// Mapping from nodes in nuc_data.h5 to hashes of nodes
  extern std::map<std::string, std::string> data_checksums;

  /// \name Atomic Mass Data
  /// \{

  /// Mapping from nuclides in id form to their atomic masses.
  extern std::map<int, double> atomic_mass_map;

  /// a struct matching the atomic_mass table in nuc_data.h5.
  typedef struct atomic_mass_data {
    int nuc;      ///< nuclide in id form
    double mass;  ///< nuclide atomic mass [amu]
    double error; ///< error in atomic mass [amu]
    double abund; ///< natural abundance of nuclide [atom fraction]
  } atomic_mass_data;

  // Loads preset dataset hashes into memory.
  std::map<std::string, std::string> get_data_checksums();

  /// Loads the atomic mass and natural abundance data from the nuc_data.h5 file
  /// into memory.
  void _load_atomic_mass_map();

  /// \brief Returns the atomic mass of a nuclide \a nuc.
  ///
  /// This function will first try to find the atomic mass data in the atomic_mass_map.
  /// If this map is empty, it will load the data from disk.  If the nuclide is in an
  /// excited state and not found in the map, it will give the value for the ground
  /// state nuclide.  If the nuclide simply cannot be found, the A number is returned.
  double atomic_mass(int nuc);
  /// Returns the atomic mass of a nuclide \a nuc.
  double atomic_mass(char * nuc);
  /// Returns the atomic mass of a nuclide \a nuc.
  double atomic_mass(std::string nuc);
  /// \}


  /// \name Natural Abundance Data
  /// \{

  /// Mapping from nuclides in id form to their natural abundances.
  extern std::map<int, double> natural_abund_map;

  /// \brief Returns the natural abundance of a nuclide \a nuc.
  ///
  /// This follows the same the basic rules for finding or computing the natural
  /// abundances as the atomic_mass() functions do.  However, if the nuclide cannot
  /// be found, the default value returned is 0.0.
  double natural_abund(int nuc);
  /// Returns the natural abundance of a nuclide \a nuc.
  double natural_abund(char * nuc);
  /// Returns the natural abundance of a nuclide \a nuc.
  double natural_abund(std::string nuc);
  /// \}
  /// \}

} // namespace pyne

#endif
//
// end of src/data.h
//


//
// start of src/nucname.h
//
/// \brief Converts between naming conventions for nuclides.

#ifndef PYNE_D35WIXV5DZAA5LLOWBY2BL2DPA
#define PYNE_D35WIXV5DZAA5LLOWBY2BL2DPA
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <exception>
#include <stdlib.h>
#include <stdio.h>

#ifndef PYNE_IS_AMALGAMATED
#include "utils.h"
#endif

namespace pyne
{
//! Nuclide naming conventions
namespace nucname
{
  typedef std::string name_t; ///< name type
  typedef int zz_t;           ///< Z number type

  typedef std::map<name_t, zz_t> name_zz_t; ///< name and Z num map type
  typedef name_zz_t::iterator name_zz_iter; ///< name and Z num iter type
  name_zz_t get_name_zz();  ///< Creates standard name to Z number mapping.
  extern name_zz_t name_zz; ///< name to Z num map

  typedef std::map<zz_t, name_t> zzname_t;  ///< Z num to name map type
  typedef zzname_t::iterator zzname_iter;   ///< Z num to name iter type
  zzname_t get_zz_name();   ///< Creates standard Z number to name mapping.
  extern zzname_t zz_name;  ///< Z num to name map

  name_zz_t get_fluka_zz();  ///< Creates standard fluka-name to nucid mapping.
  extern name_zz_t fluka_zz; ///< fluka-name to nucid map
  zzname_t get_zz_fluka();   ///< Creates standard nucid to fluka-name mapping.
  extern zzname_t zz_fluka;  ///< nucid to fluka-name map
  /******************************************/
  /*** Define useful elemental group sets ***/
  /******************************************/

  /// name grouping type (for testing containment)
  typedef std::set<name_t> name_group;
  typedef name_group::iterator name_group_iter; ///< name grouping iter type

  /// Z number grouping type (for testing containment)
  typedef std::set<zz_t> zz_group;
  typedef zz_group::iterator zz_group_iter; ///< Z number grouping iter

  /// Converts a name group to a Z number group.
  /// \param eg a grouping of nuclides by name
  /// \return a Z numbered group
  zz_group name_to_zz_group (name_group eg);

  extern name_t LAN_array[15];  ///< array of lanthanide names
  extern name_group LAN;        ///< lanthanide name group
  extern zz_group lan;          ///< lanthanide Z number group

  extern name_t ACT_array[15];  ///< array of actinide names
  extern name_group ACT;        ///< actinide name group
  extern zz_group act;          ///< actinide Z number group

  extern name_t TRU_array[22];  ///< array of transuranic names
  extern name_group TRU;        ///< transuranic name group
  extern zz_group tru;          ///< transuranic Z number group

  extern name_t MA_array[10];   ///< array of minor actinide names
  extern name_group MA;         ///< minor actinide name group
  extern zz_group ma;           ///< minor actinide Z number group

  extern name_t FP_array[88];   ///< array of fission product names
  extern name_group FP;         ///< fission product name group
  extern zz_group fp;           ///< fission product Z number group


  /******************/
  /*** Exceptions ***/
  /******************/

  /// Custom expection for declaring that a value does not follow a recognizable
  /// nuclide naming convention.
  class NotANuclide : public std::exception
  {
  public:
    /// default constructor
    NotANuclide () {};

    /// default destructor
    ~NotANuclide () throw () {};

    /// Constructor given previous and current state of nulide name
    /// \param wasptr Previous state, typically user input.
    /// \param nowptr Current state, as far as PyNE could get.
    NotANuclide(std::string wasptr, std::string nowptr)
    {
       nucwas = wasptr;
       nucnow = nowptr;
    };

    /// Constructor given previous and current state of nulide name
    /// \param wasptr Previous state, typically user input.
    /// \param nowptr Current state, as far as PyNE could get.
    NotANuclide(std::string wasptr, int nowptr)
    {
      nucwas = wasptr;
      nucnow = pyne::to_str(nowptr);
    };

    /// Constructor given previous and current state of nulide name
    /// \param wasptr Previous state, typically user input.
    /// \param nowptr Current state, as far as PyNE could get.
    NotANuclide(int wasptr, std::string nowptr)
    {
      nucwas = pyne::to_str(wasptr);
      nucnow = nowptr;
    };

    /// Constructor given previous and current state of nulide name
    /// \param wasptr Previous state, typically user input.
    /// \param nowptr Current state, as far as PyNE could get.
    NotANuclide(int wasptr, int nowptr)
    {
      nucwas = pyne::to_str(wasptr);
      nucnow = pyne::to_str(nowptr);
    };

    /// Generates an informational message for the exception
    /// \return The error string
    virtual const char* what() const throw()
    {
      std::string NaNEstr ("Not a Nuclide! ");
      if (!nucwas.empty())
        NaNEstr += nucwas;

      if (!nucnow.empty())
      {
        NaNEstr += " --> ";
        NaNEstr += nucnow;
      }
      return (const char *) NaNEstr.c_str();
    };

  private:
    std::string nucwas; ///< previous nuclide state
    std::string nucnow; ///< current nuclide state
  };

  /// Custom expection for declaring that a value represents one or more nuclides
  /// in one or more namig conventions
  class IndeterminateNuclideForm : public std::exception
  {
  public:
    /// default constructor
    IndeterminateNuclideForm () {};

    /// default destuctor
    ~IndeterminateNuclideForm () throw () {};

    /// Constructor given previous and current state of nulide name
    /// \param wasptr Previous state, typically user input.
    /// \param nowptr Current state, as far as PyNE could get.
    IndeterminateNuclideForm(std::string wasptr, std::string nowptr)
    {
       nucwas = wasptr;
       nucnow = nowptr;
    };

    /// Constructor given previous and current state of nulide name
    /// \param wasptr Previous state, typically user input.
    /// \param nowptr Current state, as far as PyNE could get.
    IndeterminateNuclideForm(std::string wasptr, int nowptr)
    {
      nucwas = wasptr;
      nucnow = pyne::to_str(nowptr);
    };

    /// Constructor given previous and current state of nulide name
    /// \param wasptr Previous state, typically user input.
    /// \param nowptr Current state, as far as PyNE could get.
    IndeterminateNuclideForm(int wasptr, std::string nowptr)
    {
      nucwas = pyne::to_str(wasptr);
      nucnow = nowptr;
    };

    /// Constructor given previous and current state of nulide name
    /// \param wasptr Previous state, typically user input.
    /// \param nowptr Current state, as far as PyNE could get.
    IndeterminateNuclideForm(int wasptr, int nowptr)
    {
      nucwas = pyne::to_str(wasptr);
      nucnow = pyne::to_str(nowptr);
    };

    /// Generates an informational message for the exception
    /// \return The error string
    virtual const char* what() const throw()
    {
      std::string INFEstr ("Indeterminate nuclide form: ");
      if (!nucwas.empty())
        INFEstr += nucwas;

      if (!nucnow.empty())
      {
        INFEstr += " --> ";
        INFEstr += nucnow;
      }
      return (const char *) INFEstr.c_str();
    }

  private:
    std::string nucwas; ///< previous nuclide state
    std::string nucnow; ///< current nuclide state
  };

  /// \name isnuclide functions
  /// \{
  /// These functions test if an input \a nuc is a valid nuclide.
  /// \param nuc a possible nuclide
  /// \return a bool
  bool isnuclide(std::string nuc);
  bool isnuclide(const char * nuc);
  bool isnuclide(int nuc);
  /// \}

  /// \name iselement functions
  /// \{
  /// These functions test if an input \a nuc is a valid element.
  /// \param nuc a possible element
  /// \return a bool
  bool iselement(std::string nuc);
  bool iselement(const char * nuc);
  bool iselement(int nuc);

  /// \}
  /// \name Identifier Form Functions
  /// \{
  /// The 'id' nuclide naming convention is the canonical form for representing
  /// nuclides in PyNE. This is termed a ZAS, or ZZZAAASSSS, representation because
  /// It stores 3 Z-number digits, 3 A-number digits, followed by 4 S-number digits
  /// which the nucleus excitation state.
  ///
  /// The id() function will always return an nuclide in id form, if successful.
  /// If the input nuclide is in id form already, then this is function does no
  /// work. For all other formats, the id() function provides a best-guess based
  /// on a heirarchy of other formats that is used to resolve ambiguities between
  /// naming conventions. For integer input the form resolution order is:
  ///   - id
  ///   - zz (elemental z-num only given)
  ///   - zzaaam
  ///   - cinder (aaazzzm)
  ///   - mcnp
  ///   - zzaaa
  /// For string (or char *) input the form resolution order is as follows:
  ///   - ZZ-LL-AAAM
  ///   - Integer form in a string representation, uses interger resolution
  ///   - NIST
  ///   - name form
  ///   - Serpent
  ///   - LL (element symbol)
  /// For well-defined situations where you know ahead of time what format the
  /// nuclide is in, you should use the various form_to_id() functions, rather
  /// than the id() function which is meant to resolve possibly ambiquous cases.
  /// \param nuc a nuclide
  /// \return nucid 32-bit integer identifier
  int id(int nuc);
  int id(const char * nuc);
  int id(std::string nuc);
  /// \}

  /// \name Name Form Functions
  /// \{
  /// The 'name' nuclide naming convention is the more common, human readable
  /// notation. The chemical symbol (one or two characters long) is first, followed
  /// by the nucleon number. Lastly if the nuclide is metastable, the letter M is
  /// concatenated to the end. For example, ‘H-1’ and ‘Am242M’ are both valid.
  /// Note that nucname will always return name form with dashes removed, the
  /// chemical symbol used for letter casing (ie 'Pu'), and a trailing upercase 'M'
  /// for a metastable flag. The name() function first converts functions to id form
  /// using the id() function. Thus the form order resolution for id() also applies
  /// here.
  /// \param nuc a nuclide
  /// \return a string nuclide identifier.
  std::string name(int nuc);
  std::string name(const char * nuc);
  std::string name(std::string nuc);
  /// \}

  /// \name Z-Number Functions
  /// \{
  /// The Z-number, or charge number, represents the number of protons in a
  /// nuclide.  This function returns that number.
  /// \param nuc a nuclide
  /// \return an integer Z-number.
  int znum(int nuc);
  int znum(const char * nuc);
  int znum(std::string nuc);
  /// \}

  /// \name A-Number Functions
  /// \{
  /// The A-number, or nucleon number, represents the number of protons and
  /// neutrons in a nuclide.  This function returns that number.
  /// \param nuc a nuclide
  /// \return an integer A-number.
  int anum(int nuc);
  int anum(const char * nuc);
  int anum(std::string nuc);
  /// \}

  /// \name S-Number Functions
  /// \{
  /// The S-number, or excitation state number, represents the excitation
  /// level of a nuclide.  Normally, this is zero.  This function returns
  /// that number.
  /// \param nuc a nuclide
  /// \return an integer A-number.
  int snum(int nuc);
  int snum(const char * nuc);
  int snum(std::string nuc);
  /// \}

  /// \name ZZAAAM Form Functions
  /// \{
  /// The ZZAAAM nuclide naming convention is the former canonical form for
  /// nuclides in PyNE. This places the charge of the nucleus out front, then has
  /// three digits for the atomic mass number, and ends with a metastable flag
  /// (0 = ground, 1 = first excited state, 2 = second excited state, etc).
  /// Uranium-235 here would be expressed as ‘922350’.
  /// \param nuc a nuclide
  /// \return an integer nuclide identifier.
  int zzaaam(int nuc);
  int zzaaam(const char * nuc);
  int zzaaam(std::string nuc);
  /// \}

  /// \name ZZAAAM Form to Identifier Form Functions
  /// \{
  /// This converts from the ZZAAAM nuclide naming convention
  /// to the id canonical form  for nuclides in PyNE.
  /// \param nuc a nuclide in ZZAAAM form.
  /// \return an integer id nuclide identifier.
  int zzaaam_to_id(int nuc);
  int zzaaam_to_id(const char * nuc);
  int zzaaam_to_id(std::string nuc);
  /// \}


  /// \name ZZZAAA Form Functions
  /// \{
  /// The ZZZAAA nuclide naming convention is a form in which the nuclides three
  ///digit ZZZ number is followed by the 3 digit AAA number.  If the ZZZ number
  ///is 2 digits, the preceding zeros are not included.
  /// Uranium-235 here would be expressed as ‘92235’.
  /// \param nuc a nuclide
  /// \return an integer nuclide identifier.
  int zzzaaa(int nuc);
  int zzzaaa(const char * nuc);
  int zzzaaa(std::string nuc);
  /// \}


  /// \name ZZZAAA Form to Identifier Form Functions
  /// \{
  /// This converts from the ZZZAAA nuclide naming convention
  /// to the id canonical form  for nuclides in PyNE.
  /// \param nuc a nuclide in ZZZAAA form.
  /// \return an integer id nuclide identifier.
  int zzzaaa_to_id(int nuc);
  int zzzaaa_to_id(const char * nuc);
  int zzzaaa_to_id(std::string nuc);
  /// \}


  /// \name ZZLLAAAM Form Functions
  /// \{
  /// The ZZLLAAAM nuclide naming convention is a form in which the nuclides
  /// AA number is followed by the redundant two LL characters, followed by
  /// the nuclides ZZZ number.  Can also be followed with a metastable flag.
  /// Uranium-235 here would be expressed as ‘92-U-235’.
  /// \param nuc a nuclide
  /// \return an integer nuclide identifier.
  std::string zzllaaam(int nuc);
  std::string zzllaaam(const char * nuc);
  std::string zzllaaam(std::string nuc);
  /// \}


  /// \name ZZLLAAAM Form to Identifier Form Functions
  /// \{
  /// This converts from the ZZLLAAAM nuclide naming convention
  /// to the id canonical form  for nuclides in PyNE.
  /// \param nuc a nuclide in ZZLLAAAM form.
  /// \return an integer id nuclide identifier.
  //int zzllaaam_to_id(int nuc);
  int zzllaaam_to_id(const char * nuc);
  int zzllaaam_to_id(std::string nuc);
  /// \}


  /// \name MCNP Form Functions
  /// \{
  /// This is the naming convention used by the MCNP suite of codes.
  /// The MCNP format for entering nuclides is unfortunately non-standard.
  /// In most ways it is similar to zzaaam form, except that it lacks the metastable
  /// flag. For information on how metastable isotopes are named, please consult the
  /// MCNP documentation for more information.
  /// \param nuc a nuclide
  /// \return a string nuclide identifier.
  int mcnp(int nuc);
  int mcnp(const char * nuc);
  int mcnp(std::string nuc);
  /// \}

  /// \name MCNP Form to Identifier Form Functions
  /// \{
  /// This converts from the MCNP nuclide naming convention
  /// to the id canonical form  for nuclides in PyNE.
  /// \param nuc a nuclide in MCNP form.
  /// \return an integer id nuclide identifier.
  int mcnp_to_id(int nuc);
  int mcnp_to_id(const char * nuc);
  int mcnp_to_id(std::string nuc);
  /// \}

  /// \name FLUKA Form Functions
  /// \{
  /// This is the naming convention used by the FLUKA suite of codes.
  /// The FLUKA format for entering nuclides requires some knowledge of FLUKA
  /// The nuclide in must cases should be the atomic # times 10000000.
  /// The exceptions are for FLUKA's named isotopes
  /// See the FLUKA Manual for more information.
  /// \param nuc a nuclide
  /// \return the received FLUKA name
  std::string fluka(int nuc);
  /// \}

  /// \name FLUKA Form to Identifier Form Functions
  /// \{
  /// This converts from the FLUKA name to the
  /// id canonical form  for nuclides in PyNE.
  /// \param name a fluka name
  /// \return an integer id nuclide identifier.
  int fluka_to_id(std::string name);
  int fluka_to_id(char * name);
  /// \}

  /// \name Serpent Form Functions
  /// \{
  /// This is the string-based naming convention used by the Serpent suite of codes.
  /// The serpent naming convention is similar to name form. However, only the first
  /// letter in the chemical symbol is uppercase, the dash is always present, and the
  /// the meta-stable flag is lowercase. For instance, ‘Am-242m’ is the valid serpent
  /// notation for this nuclide.
  /// \param nuc a nuclide
  /// \return a string nuclide identifier.
  std::string serpent(int nuc);
  std::string serpent(const char * nuc);
  std::string serpent(std::string nuc);
  /// \}

  /// \name Serpent Form to Identifier Form Functions
  /// \{
  /// This converts from the Serpent nuclide naming convention
  /// to the id canonical form  for nuclides in PyNE.
  /// \param nuc a nuclide in Serpent form.
  /// \return an integer id nuclide identifier.
  //int serpent_to_id(int nuc);  Should be ZAID
  int serpent_to_id(const char * nuc);
  int serpent_to_id(std::string nuc);
  /// \}

  /// \name NIST Form Functions
  /// \{
  /// This is the string-based naming convention used by NIST.
  /// The NIST naming convention is also similar to the Serpent form. However, this
  /// convention contains no metastable information. Moreover, the A-number comes
  /// before the element symbol. For example, ‘242Am’ is the valid NIST notation.
  /// \param nuc a nuclide
  /// \return a string nuclide identifier.
  std::string nist(int nuc);
  std::string nist(const char * nuc);
  std::string nist(std::string nuc);
  /// \}

  /// \name NIST Form to Identifier Form Functions
  /// \{
  /// This converts from the NIST nuclide naming convention
  /// to the id canonical form  for nuclides in PyNE.
  /// \param nuc a nuclide in NIST form.
  /// \return an integer id nuclide identifier.
  //int serpent_to_id(int nuc);  NON-EXISTANT
  int nist_to_id(const char * nuc);
  int nist_to_id(std::string nuc);
  /// \}

  /// \name CINDER Form Functions
  /// \{
  /// This is the naming convention used by the CINDER burnup library.
  /// The CINDER format is similar to zzaaam form except that the placement of the
  /// Z- and A-numbers are swapped. Therefore, this format is effectively aaazzzm.
  /// For example, ‘2420951’ is the valid cinder notation for ‘AM242M’.
  /// \param nuc a nuclide
  /// \return a string nuclide identifier.
  int cinder(int nuc);
  int cinder(const char * nuc);
  int cinder(std::string nuc);
  /// \}

  /// \name Cinder Form to Identifier Form Functions
  /// \{
  /// This converts from the Cinder nuclide naming convention
  /// to the id canonical form  for nuclides in PyNE.
  /// \param nuc a nuclide in Cinder form.
  /// \return an integer id nuclide identifier.
  int cinder_to_id(int nuc);
  int cinder_to_id(const char * nuc);
  int cinder_to_id(std::string nuc);
  /// \}

  /// \name ALARA Form Functions
  /// \{
  /// This is the format used in the ALARA activation code elements library.
  /// For elements, the form is "ll" where ll is the atomic symbol. For isotopes
  /// the form is "ll:AAA". No metastable isotope flag is used.
  /// \param nuc a nuclide
  /// \return a string nuclide identifier.
  std::string alara(int nuc);
  std::string alara(const char * nuc);
  std::string alara(std::string nuc);
  /// \}

  /// \name ALARA Form to Identifier Form Functions
  /// \{
  /// This converts from the ALARA nuclide naming convention
  /// to the id canonical form  for nuclides in PyNE.
  /// \param nuc a nuclide in ALARA form.
  /// \return an integer id nuclide identifier.
  //int alara_to_id(int nuc); NOT POSSIBLE
  int alara_to_id(const char * nuc);
  int alara_to_id(std::string nuc);
  /// \}

  /// \name SZA Form Functions
  /// \{
  /// This is the new format for ACE data tables in the form SSSZZZAAA.
  /// The first three digits represent the excited state (000 = ground,
  /// 001 = first excited state, 002 = second excited state, etc).
  /// The second three digits are the atomic number and the last three
  /// digits are the atomic mass. Prepending zeros can be omitted, making
  /// the SZA form equal to the MCNP form for non-excited nuclides.
  /// \param nuc a nuclide
  /// \return a string nuclide identifier.
  int sza(int nuc);
  int sza(const char * nuc);
  int sza(std::string nuc);
  /// \}

  /// \name SZA Form to Identifier Form Functions
  /// \{
  /// This converts from the SZA nuclide naming convention
  /// to the id canonical form  for nuclides in PyNE.
  /// \param nuc a nuclide in SZA form.
  /// \return an integer id nuclide identifier.
  int sza_to_id(int nuc);
  int sza_to_id(const char * nuc);
  int sza_to_id(std::string nuc);
  /// \}

  /// \name Ground State Form Functions
  /// \{
  /// This form stores the nuclide in id form, but removes
  /// the state information about the nuclide.  I is in the same
  /// form as ID, but the four last digits are all zeros.
  /// \param nuc a nuclide
  /// \return a integer groundstate id
  inline int groundstate(int nuc) {return (id(nuc) / 10000 ) * 10000;}
  inline int groundstate(std::string nuc) {return groundstate(id(nuc));}
  inline int groundstate(const char * nuc) {return groundstate(std::string(nuc));}
  /// \}

  /// \name State Map functions
  /// \{
  /// These convert from/to decay state ids (used in decay data)
  /// to metastable ids (the PyNE default)
  void _load_state_map();
  int state_id_to_id(int state);
  int id_to_state_id(int nuc_id);
  extern std::map<int, int> state_id_map;
  /// \}

  /// \name ENSDF Form Functions
  /// \{
  /// This converts id's stored using standard ensdf syntax to nuc_id's
  /// \param ensdf nuc string
  /// \return PyNE nuc_id
  int ensdf_to_id(const char * nuc);
  int ensdf_to_id(std::string nuc);
  /// \}

}
}

#endif  // PYNE_D35WIXV5DZAA5LLOWBY2BL2DPA
//
// end of src/nucname.h
//



//
// start of src/extra_types.h
//
/// \file extra_types.h
/// \author Anthony Scopatz (scopatz\@gmail.com)
///
/// Provides some extra types that may be generally useful

#if !defined(_XDRESS_EXTRA_TYPES_)
#define _XDRESS_EXTRA_TYPES_

#if defined(__cplusplus)
namespace extra_types
{
  /// complex type struct, matching PyTables definition
//  typedef struct {
//    double re;  ///< real part
//    double im;  ///< imaginary part
//  } complex_t;

  /// Chivalrously handles C++ memory issues that Cython does
  /// not yet have a syntax for.  This is a template class,
  /// rather than three template functions, because Cython does
  /// not yet support template function wrapping.
  template <class T>
  class MemoryKnight
  {
    public:
      MemoryKnight(){};   ///< Default constructor
      ~MemoryKnight(){};  ///< Default Destructor

      /// Creates a new instance of type T on the heap using
      /// its default constructor.
      /// \return T *
      T * defnew(){return new T();};

      /// Creates a new instance of type T, using T's default
      /// constructor, at a given location.
      /// \param void * ptr, location to create T instance
      /// \return value of ptr recast as T *
      T * renew(void * ptr){return new (ptr) T();};

      /// Deallocates a location in memory using delete.
      /// \param T * ptr, location to remove
      void deall(T * ptr){delete ptr;};
  };

// End namespace extra_types
}

#elif defined(__STDC__)

// de nada

#endif


/// complex type struct, matching PyTables definition
typedef struct {
  double re;  ///< real part
  double im;  ///< imaginary part
} xd_complex_t;

#endif

//
// end of src/extra_types.h
//


//
// start of src/rxname.h
//
/// \brief Converts between naming conventions for reaction channels.

#ifndef PYNE_7DOEB2PKSBEFFIA3Q2NARI3KFY
#define PYNE_7DOEB2PKSBEFFIA3Q2NARI3KFY
#include <utility>
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <exception>
#include <stdlib.h>
#include <stdio.h>

#ifndef PYNE_IS_AMALGAMATED
#include "utils.h"
#include "nucname.h"
#endif

/// Number of reactions supported by default.
#define NUM_RX_NAMES 572

namespace pyne
{
//! Converts between naming conventions for reaction channels.
namespace rxname
{
  extern std::string _names[NUM_RX_NAMES];  ///< Raw array of reaction names
  /// Set of reaction names, must be valid variable names.
  extern std::set<std::string> names;
  /// Mapping from reaction ids to reaction names.
  extern std::map<unsigned int, std::string> id_name;
  /// Mapping from reaction names to reaction ids.
  extern std::map<std::string, unsigned int> name_id;
  /// Mapping between alternative names for reactions and the reaction id.
  extern std::map<std::string, unsigned int> altnames;
  /// Mapping from reaction ids to MT numbers.
  extern std::map<unsigned int, unsigned int> id_mt;
  /// Mapping from MT numbers to reaction names.
  extern std::map<unsigned int, unsigned int> mt_id;
  /// Mapping from reaction ids to labels (short descriptions).
  extern std::map<unsigned int, std::string> labels;
  /// Mapping from reaction ids to documentation strings (long descriptions).
  extern std::map<unsigned int, std::string> docs;
  /// Mapping from particle type and offset pairs to reaction ids.
  /// Particle flags are 'n', 'p', 'd', 't', 'He3', 'a', 'gamma', and 'decay'.
  extern std::map<std::pair<std::string, int>, unsigned int> offset_id;
  /// Mapping from particle type and reaction ids to offsets.
  /// Particle flags are 'n', 'p', 'd', 't', 'He3', 'a', 'gamma', and 'decay'.
  extern std::map<std::pair<std::string, unsigned int>, int> id_offset;

  /// A helper function to set the contents of the variables in this library.
  void * _fill_maps();
  extern void * _;  ///< A dummy variable used when calling #_fill_maps().

  /// A helper function to compute nuclide id offsets from z-, a-, and s- deltas
  inline int offset(int dz, int da, int ds=0) {return dz*10000000 + da*10000 + ds;}

  /// \name Hash Functions
  /// \{
  /// Custom hash function for reaction name to reaction ids.
  /// This functions will not return a value less than 1000, effectively reserving
  /// space for the MT numbers.
  unsigned int hash(std::string s);
  unsigned int hash(const char * s);
  /// \}

  /// \name Name Functions
  /// \{
  /// Returns the canonical name of a reaction channel.
  /// \param n Integer input of possible reaction, nominally an id or MT number.
  /// \param s String input of possible reaction, often a reaction or alternate name.
  /// \param from_nuc Initial target nuclide prior to reaction.  When \a from_nuc is
  ///                 an integer it must be in id form.
  /// \param to_nuc Target nuclide after reaction occurs.  When \a to_nuc is
  ///               an integer it must be in id form.
  /// \param z Flag for incident particle type.
  ///          Particle flags are 'n', 'p', 'd', 't', 'He3', 'a', 'gamma', and 'decay'.
  std::string name(int n);
  std::string name(unsigned int n);
  std::string name(char * s);
  std::string name(std::string s);
  std::string name(int from_nuc, int to_nuc, std::string z="n");
  std::string name(int from_nuc, std::string to_nuc, std::string z="n");
  std::string name(std::string from_nuc, int to_nuc, std::string z="n");
  std::string name(std::string from_nuc, std::string to_nuc, std::string z="n");
  /// \}

  /// \name ID Functions
  /// \{
  /// Returns the recation id of a reaction channel.  This id has been precomputed
  /// from the hash of the name.
  /// \param x Input reaction specification, may be a reaction name, alternate name,
  ///          an id, or an MT number.
  /// \param from_nuc Initial target nuclide prior to reaction.  When \a from_nuc is
  ///                 an integer it must be in id form.
  /// \param to_nuc Target nuclide after reaction occurs.  When \a to_nuc is
  ///               an integer it must be in id form.
  /// \param z Flag for incident particle type.
  ///          Particle flags are 'n', 'p', 'd', 't', 'He3', 'a', 'gamma', and 'decay'.
  unsigned int id(int x);
  unsigned int id(unsigned int x);
  unsigned int id(const char * x);
  unsigned int id(std::string x);
  unsigned int id(int from_nuc, int to_nuc, std::string z="n");
  unsigned int id(int from_nuc, std::string to_nuc, std::string z="n");
  unsigned int id(std::string from_nuc, int to_nuc, std::string z="n");
  unsigned int id(std::string from_nuc, std::string to_nuc, std::string z="n");
  /// \}

  /// \name MT Number Functions
  /// \{
  /// Returns the MT number of a reaction channel, if available.
  /// \param x Input reaction specification, may be a reaction name, alternate name,
  ///          an id, or an MT number.
  /// \param from_nuc Initial target nuclide prior to reaction.  When \a from_nuc is
  ///                 an integer it must be in id form.
  /// \param to_nuc Target nuclide after reaction occurs.  When \a to_nuc is
  ///               an integer it must be in id form.
  /// \param z Flag for incident particle type.
  ///          Particle flags are 'n', 'p', 'd', 't', 'He3', 'a', 'gamma', and 'decay'.
  unsigned int mt(int x);
  unsigned int mt(unsigned int x);
  unsigned int mt(char * x);
  unsigned int mt(std::string x);
  unsigned int mt(int from_nuc, int to_nuc, std::string z="n");
  unsigned int mt(int from_nuc, std::string to_nuc, std::string z="n");
  unsigned int mt(std::string from_nuc, int to_nuc, std::string z="n");
  unsigned int mt(std::string from_nuc, std::string to_nuc, std::string z="n");
  /// \}

  //// \name Label Functions
  /// \{
  /// Returns a short description of a reaction channel.
  /// \param x Input reaction specification, may be a reaction name, alternate name,
  ///          an id, or an MT number.
  /// \param from_nuc Initial target nuclide prior to reaction.  When \a from_nuc is
  ///                 an integer it must be in id form.
  /// \param to_nuc Target nuclide after reaction occurs.  When \a to_nuc is
  ///               an integer it must be in id form.
  /// \param z Flag for incident particle type.
  ///          Particle flags are 'n', 'p', 'd', 't', 'He3', 'a', 'gamma', and 'decay'.
  std::string label(int x);
  std::string label(unsigned int x);
  std::string label(char * x);
  std::string label(std::string x);
  std::string label(int from_nuc, int to_nuc, std::string z="n");
  std::string label(int from_nuc, std::string to_nuc, std::string z="n");
  std::string label(std::string from_nuc, int to_nuc, std::string z="n");
  std::string label(std::string from_nuc, std::string to_nuc, std::string z="n");
  /// \}

  /// \name Documentation Functions
  /// \{
  /// Returns a short description of a reaction channel.
  /// \param x Input reaction specification, may be a reaction name, alternate name,
  ///          an id, or an MT number.
  /// \param from_nuc Initial target nuclide prior to reaction.  When \a from_nuc is
  ///                 an integer it must be in id form.
  /// \param to_nuc Target nuclide after reaction occurs.  When \a to_nuc is
  ///               an integer it must be in id form.
  /// \param z Flag for incident particle type.
  ///          Particle flags are 'n', 'p', 'd', 't', 'He3', 'a', 'gamma', and 'decay'.
  std::string doc(int x);
  std::string doc(unsigned int x);
  std::string doc(char * x);
  std::string doc(std::string x);
  std::string doc(int from_nuc, int to_nuc, std::string z="n");
  std::string doc(int from_nuc, std::string to_nuc, std::string z="n");
  std::string doc(std::string from_nuc, int to_nuc, std::string z="n");
  std::string doc(std::string from_nuc, std::string to_nuc, std::string z="n");
  /// \}

  /// \name Child Functions
  /// \{
  /// Returns the child nuclide comming from a parent for a reaction channel.
  /// \param nuc Nuclide after reaction occurs.  When \a nuc is
  ///               an integer it must be in id form.
  /// \param rx Input reaction specification, may be a reaction name, alternate name,
  ///           an id, or an MT number.
  /// \param z Flag for incident particle type.
  ///          Particle flags are 'n', 'p', 'd', 't', 'He3', 'a', 'gamma', and 'decay'.
  int parent(int nuc, unsigned int rx, std::string z="n");
  int parent(int nuc, std::string rx, std::string z="n");
  int parent(std::string nuc, unsigned int rx, std::string z="n");
  int parent(std::string nuc, std::string rx, std::string z="n");
  /// \}

  /// \name Parent Functions
  /// \{
  /// Returns the parent nuclide comming for a child and a given reaction channel.
  /// \param nuc Initial target nuclide prior to reaction.  When \a nuc is
  ///            an integer it must be in id form.
  /// \param rx Input reaction specification, may be a reaction name, alternate name,
  ///           an id, or an MT number.
  /// \param z Flag for incident particle type.
  ///          Particle flags are 'n', 'p', 'd', 't', 'He3', 'a', 'gamma', and 'decay'.
  int child(int nuc, unsigned int rx, std::string z="n");
  int child(int nuc, std::string rx, std::string z="n");
  int child(std::string nuc, unsigned int rx, std::string z="n");
  int child(std::string nuc, std::string rx, std::string z="n");
  /// \}

  /// Custom exception for declaring a value not to be a valid reaction.
  class NotAReaction : public std::exception
  {
  public:

    /// default constructor
    NotAReaction () {};

    /// default destructor
    ~NotAReaction () throw () {};

    /// Constructor using original reaction (\a wasptr) and the eventual state
    /// that PyNE calculated (\a nowptr).
    NotAReaction(std::string wasptr, std::string nowptr)
    {
       rxwas = wasptr;
       rxnow = nowptr;
    };

    /// Constructor using original reaction (\a wasptr) and the eventual state
    /// that PyNE calculated (\a nowptr).
    NotAReaction(std::string wasptr, int nowptr)
    {
      rxwas = wasptr;
      rxnow = pyne::to_str(nowptr);
    };

    /// Constructor using original reaction (\a wasptr) and the eventual state
    /// that PyNE calculated (\a nowptr).
    NotAReaction(int wasptr, std::string nowptr)
    {
      rxwas = pyne::to_str(wasptr);
      rxnow = nowptr;
    };

    /// Constructor using original reaction (\a wasptr) and the eventual state
    /// that PyNE calculated (\a nowptr).
    NotAReaction(int wasptr, int nowptr)
    {
      rxwas = pyne::to_str(wasptr);
      rxnow = pyne::to_str(nowptr);
    };

    /// Constructor using original reaction (\a wasptr) and the eventual state
    /// that PyNE calculated (\a nowptr).
    NotAReaction(std::string wasptr, unsigned int nowptr)
    {
      rxwas = wasptr;
      rxnow = pyne::to_str(nowptr);
    };

    /// Constructor using original reaction (\a wasptr) and the eventual state
    /// that PyNE calculated (\a nowptr).
    NotAReaction(unsigned int wasptr, std::string nowptr)
    {
      rxwas = pyne::to_str(wasptr);
      rxnow = nowptr;
    };

    /// Constructor using original reaction (\a wasptr) and the eventual state
    /// that PyNE calculated (\a nowptr).
    NotAReaction(unsigned int wasptr, unsigned int nowptr)
    {
      rxwas = pyne::to_str(wasptr);
      rxnow = pyne::to_str(nowptr);
    };

    /// Returns a helpful error message containing prior and current reaction state.
    virtual const char* what() const throw()
    {
      std::string narxstr ("Not a reaction! ");
      if (!rxwas.empty())
        narxstr += rxwas;

      if (!rxnow.empty())
      {
        narxstr += " --> ";
        narxstr += rxnow;
      }
      return (const char *) narxstr.c_str();
    };

  private:
    std::string rxwas;  ///< previous reaction state
    std::string rxnow;  ///< current reaction state
  };



  /// Custom exception for declaring a value not to be of ambiquous reaction form.
  class IndeterminateReactionForm : public std::exception
  {
  public:

    /// default constructor
    IndeterminateReactionForm () {};

    /// default destructor
    ~IndeterminateReactionForm () throw () {};

    /// Constructor using original reaction (\a wasptr) and the eventual state
    /// that PyNE calculated (\a nowptr).
    IndeterminateReactionForm(std::string wasptr, std::string nowptr)
    {
       rxwas = wasptr;
       rxnow = nowptr;
    };

    /// Constructor using original reaction (\a wasptr) and the eventual state
    /// that PyNE calculated (\a nowptr).
    IndeterminateReactionForm(std::string wasptr, int nowptr)
    {
      rxwas = wasptr;
      rxnow = pyne::to_str(nowptr);
    };

    /// Constructor using original reaction (\a wasptr) and the eventual state
    /// that PyNE calculated (\a nowptr).
    IndeterminateReactionForm(int wasptr, std::string nowptr)
    {
      rxwas = pyne::to_str(wasptr);
      rxnow = nowptr;
    };

    /// Constructor using original reaction (\a wasptr) and the eventual state
    /// that PyNE calculated (\a nowptr).
    IndeterminateReactionForm(int wasptr, int nowptr)
    {
      rxwas = pyne::to_str(wasptr);
      rxnow = pyne::to_str(nowptr);
    };

    /// Returns a helpful error message containing prior and current reaction state.
    virtual const char* what() const throw()
    {
      std::string INFEstr ("Indeterminate reaction form: ");
      if (!rxwas.empty())
        INFEstr += rxwas;

      if (!rxnow.empty())
      {
        INFEstr += " --> ";
        INFEstr += rxnow;
      }
      return (const char *) INFEstr.c_str();
    }

  private:
    std::string rxwas;  ///< previous reaction state
    std::string rxnow;  ///< current reaction state
  };
}
}

#endif  // PYNE_7DOEB2PKSBEFFIA3Q2NARI3KFY
//
// end of src/rxname.h
//



#endif  // PYNE_52BMSKGZ3FHG3NQI566D4I2ZLY

