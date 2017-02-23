// Executable size report utility.
// Aras Pranckevicius, http://aras-p.info/projSizer.html
// Based on code by Fabian "ryg" Giesen, http://farbrausch.com/~fg/
// Public domain.

#ifndef __DEBUGINFO_HPP__
#define __DEBUGINFO_HPP__

#include "types.hpp"
#include <unordered_map>

using std::string;

// tsafin - we do not care about functions stats and namespaces stats. For a while
#undef  ENABLE_FUNCTIONS
#define ENABLE_MODULES
#undef  ENABLE_TEMPLATES
#undef  ENABLE_NAMESPACES

/****************************************************************************/

#define DIC_END     0
#define DIC_CODE    1
#define DIC_DATA    2
#define DIC_BSS	    3 // uninitialized data
#define DIC_UNKNOWN 4

struct DISymFile // File
{
  sInt	fileName;
  sU32	codeSize;
  sU32	dataSize;
};

struct DISymNameSp // Namespace
{
  sInt	name;
  sU32	codeSize;
  sU32	dataSize;
};

struct DISymbol
{
  sInt name;
  sInt mangledName;
#ifdef ENABLE_NAMESPACE
  sInt NameSpNum;
#endif
#ifdef ENABLE_MODULES
  sInt objFileNum;
#endif
  sU32 VA;
  sU32 Size;
  sInt Class;
};

struct TemplateSymbol
{
  string  name;
  sU32	size;
  sU32	count;
};

class DebugInfo
{
  std::vector<string> m_StringByIndex;
  std::unordered_map<string, sInt>  m_IndexByString;
  sU32 BaseAddress;

  sU32 CountSizeInClass(sInt type) const;

public:
  std::vector<DISymbol>  Symbols;
#ifdef ENABLE_TEMPLATES
  std::vector<TemplateSymbol>  Templates;
#endif
#ifdef ENABLE_MODULES
  std::vector<DISymFile> m_Files;
#endif
#ifdef ENABLE_NAMESPACE
  std::vector<DISymNameSp> NameSps;
#endif

  void Init();
  void Exit();

  // only use those before reading is finished!!
  sInt MakeString(sChar *s);
  const char* GetStringPrep( sInt index ) const { return m_StringByIndex[index].c_str(); }
  void SetBaseAddress(sU32 base)            { BaseAddress = base; }

  void FinishedReading();

#ifdef ENABLE_MODULES
  sInt GetFile( sInt fileName );
  sInt GetFileByName( sChar *objName );
#endif

#ifdef ENABLE_NAMESPACE
  sInt GetNameSpace(sInt name);
  sInt GetNameSpaceByName(sChar *name);
#endif
  
  void StartAnalyze();
  void FinishAnalyze();
#if 0
  sBool FindSymbol(sU32 VA,DISymbol **sym);
#endif

  std::string WriteReport();
};

class DebugInfoReader
{
public:
  virtual sBool ReadDebugInfo(sChar *fileName,DebugInfo &to) = 0;
};


#endif
