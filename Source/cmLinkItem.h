/*============================================================================
  CMake - Cross Platform Makefile Generator
  Copyright 2004-2015 Kitware, Inc.

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file Copyright.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the License for more information.
============================================================================*/

#ifndef cmLinkItem_h
#define cmLinkItem_h

#include "cmListFileCache.h"
#include "cmSystemTools.h"

class cmGeneratorTarget;

// Basic information about each link item.
class cmLinkItem : public std::string
{
  typedef std::string std_string;

public:
  cmLinkItem()
    : std_string()
    , Target(0)
  {
  }
  cmLinkItem(const std_string& n, cmGeneratorTarget const* t)
    : std_string(n)
    , Target(t)
  {
  }
  cmLinkItem(cmLinkItem const& r)
    : std_string(r)
    , Target(r.Target)
  {
  }
  cmGeneratorTarget const* Target;
};

class cmLinkImplItem : public cmLinkItem
{
public:
  cmLinkImplItem()
    : cmLinkItem()
    , Backtrace()
    , FromGenex(false)
  {
  }
  cmLinkImplItem(std::string const& n, cmGeneratorTarget const* t,
                 cmListFileBacktrace const& bt, bool fromGenex)
    : cmLinkItem(n, t)
    , Backtrace(bt)
    , FromGenex(fromGenex)
  {
  }
  cmLinkImplItem(cmLinkImplItem const& r)
    : cmLinkItem(r)
    , Backtrace(r.Backtrace)
    , FromGenex(r.FromGenex)
  {
  }
  cmListFileBacktrace Backtrace;
  bool FromGenex;
};

/** The link implementation specifies the direct library
    dependencies needed by the object files of the target.  */
struct cmLinkImplementationLibraries
{
  // Libraries linked directly in this configuration.
  std::vector<cmLinkImplItem> Libraries;

  // Libraries linked directly in other configurations.
  // Needed only for OLD behavior of CMP0003.
  std::vector<cmLinkItem> WrongConfigLibraries;
};

struct cmLinkInterfaceLibraries
{
  // Libraries listed in the interface.
  std::vector<cmLinkItem> Libraries;
};

struct cmLinkInterface : public cmLinkInterfaceLibraries
{
  // Languages whose runtime libraries must be linked.
  std::vector<std::string> Languages;

  // Shared library dependencies needed for linking on some platforms.
  std::vector<cmLinkItem> SharedDeps;

  // Number of repetitions of a strongly connected component of two
  // or more static libraries.
  unsigned int Multiplicity;

  // Libraries listed for other configurations.
  // Needed only for OLD behavior of CMP0003.
  std::vector<cmLinkItem> WrongConfigLibraries;

  bool ImplementationIsInterface;

  cmLinkInterface()
    : Multiplicity(0)
    , ImplementationIsInterface(false)
  {
  }
};

struct cmOptionalLinkInterface : public cmLinkInterface
{
  cmOptionalLinkInterface()
    : LibrariesDone(false)
    , AllDone(false)
    , Exists(false)
    , HadHeadSensitiveCondition(false)
    , ExplicitLibraries(0)
  {
  }
  bool LibrariesDone;
  bool AllDone;
  bool Exists;
  bool HadHeadSensitiveCondition;
  const char* ExplicitLibraries;
};

struct cmHeadToLinkInterfaceMap
  : public std::map<cmGeneratorTarget const*, cmOptionalLinkInterface>
{
};

struct cmLinkImplementation : public cmLinkImplementationLibraries
{
  // Languages whose runtime libraries must be linked.
  std::vector<std::string> Languages;
};

// Cache link implementation computation from each configuration.
struct cmOptionalLinkImplementation : public cmLinkImplementation
{
  cmOptionalLinkImplementation()
    : LibrariesDone(false)
    , LanguagesDone(false)
    , HadHeadSensitiveCondition(false)
  {
  }
  bool LibrariesDone;
  bool LanguagesDone;
  bool HadHeadSensitiveCondition;
};

/** Compute the link type to use for the given configuration.  */
inline cmTargetLinkLibraryType CMP0003_ComputeLinkType(
  const std::string& config, std::vector<std::string> const& debugConfigs)
{
  // No configuration is always optimized.
  if (config.empty()) {
    return OPTIMIZED_LibraryType;
  }

  // Check if any entry in the list matches this configuration.
  std::string configUpper = cmSystemTools::UpperCase(config);
  if (std::find(debugConfigs.begin(), debugConfigs.end(), configUpper) !=
      debugConfigs.end()) {
    return DEBUG_LibraryType;
  }
  // The current configuration is not a debug configuration.
  return OPTIMIZED_LibraryType;
}

#endif
