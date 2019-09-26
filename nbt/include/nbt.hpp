#pragma once

#ifndef nbt_hpp

/// \file nbt.hpp
/// \brief This file #includes all modules of nbt.
///
/// By #including this file a user is automatically
/// including **all** of the modules of *nbt*.

/// \namespace nbt
/// \brief Root namespace.
///
/// There is nothing in namespace *nbt*.
/// All the tools are within their own namespaces.

/// \mainpage
/// # nbt
/// Welcome to the main page of **nbt** , a collection of C++ libraries.
///
///
/// Currently, these are the available *modules* in *nbt*:
///
/// | page | namespace | header file |
/// | :----: | :----: | :----: |
/// | \link ascii \endlink | nbt::ascii | ascii.hpp |
/// | \link binary \endlink | nbt::binary | binary.hpp |
///

#  include <nbt/ascii.hpp>
#  include <nbt/binary.hpp>
#  include <nbt/core.hpp>
#  include <nbt/file.hpp>
#  include <nbt/graphics.hpp>
#  include <nbt/math.hpp>

#endif // !nbt_hpp