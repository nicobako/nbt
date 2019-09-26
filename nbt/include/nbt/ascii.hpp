#pragma once

#ifndef ascii_hpp

/// \file ascii.hpp
/// \brief This file #includes all header files in this module
///
/// By #including this file the user #includes all the files in
/// that are part of the *ascii* namespace.

/// \namespace nbt::ascii
/// \brief module for ascii character manipulation.
///
/// This module provides useful functionality for manipulating
/// ascii characters such as parsing lines, converting between
/// strings and built-in-types, etc.

/// \page ascii
/// Welcome to the ascii module.
/// The ascii module contains useful functions for performing basic ascii string
/// manipulation.
///
/// \dot
/// digraph  ex {
/// ascii -> fmt;
/// }
/// \enddot

#  include <nbt/ascii/Conversions.hpp>
#  include <nbt/ascii/Regex.hpp>

#endif // !ascii_hpp
