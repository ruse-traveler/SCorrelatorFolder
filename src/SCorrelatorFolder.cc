// ----------------------------------------------------------------------------
// 'SCorrelatorFolder.cc'
// Derek Anderson
// 04.30.2023
//
// A module to unfold, backfold, and/or
// perform corrections on an n-point
// energy correlation strength function.
// ----------------------------------------------------------------------------

#define SCORRELATORFOLDER_CC

// user includes
#include "SCorrelatorFolder.h"
#include "SCorrelatorFolder.io.h"
#include "SCorrelatorFolder.sys.h"
#include "SCorrelatorFolder.ana.h"

using namespace std;



// ctor/dtor ------------------------------------------------------------------

SCorrelatorFolder::SCorrelatorFolder(const string &name, const bool isComplex, const bool doDebug, const bool inBatch) : SubsysReco(name) {

  // initialize internal variables
  InitializeMembers();

  // set standalone/complex mode
  if (isComplex) {
    m_inComplexMode    = true;
    m_inStandaloneMode = false; 
  } else {
    m_inComplexMode    = false;
    m_inStandaloneMode = true;
  }

  // set verbosity in complex mode
  if (m_inComplexMode) {
    m_verbosity = Verbosity();
  }

  // set debug/batch mode & print debug statement
  m_inDebugMode = doDebug;
  m_inBatchMode = inBatch;
  if (m_inDebugMode) PrintDebug(0);

  // set module name & announce start of folding
  m_moduleName = name;
  if (m_inStandaloneMode) PrintMessage(0);

}  // end ctor(string, bool, bool)



SCorrelatorFolder::~SCorrelatorFolder() {

  // print debug statement
  if (m_inDebugMode) PrintDebug(1);

  // delete pointers to files
  if (!m_inTrueTree || !m_inRecoTree) {
    if (!m_inTrueTree) delete m_inTrueFile;
    if (!m_inRecoTree) delete m_inRecoFile;
    delete m_outFile;
  }

}  // end dtor



// F4A methods ----------------------------------------------------------------

int SCorrelatorFolder::Init(PHCompositeNode*) {

  /* TODO init will go here */
  return Fun4AllReturnCodes::EVENT_OK;

}  // end 'Init(PHCompositeNode*)'




int SCorrelatorFolder::process_event(PHCompositeNode*) {

  /* TODO event processing will go here */
  return Fun4AllReturnCodes::EVENT_OK;

}  // end 'process_event(PHCompositeNode*)'



int SCorrelatorFolder::End(PHCompositeNode*) {

  /* TODO end will go here */
  return Fun4AllReturnCodes::EVENT_OK;

}  // end 'End(PHCompositeNode*)'



// standalone-only methods ----------------------------------------------------

void SCorrelatorFolder::Init() {

  // print debug statement
  if (m_inDebugMode) PrintDebug(2);

  // make sure standalone mode is on & open files
  if (m_inComplexMode) {
    PrintError(0);
    assert(m_inStandaloneMode);
  } else {
    OpenInputFiles();
  }
  OpenOutputFile();

  // announce files
  PrintMessage(1);

  // initialize input and output
  InitializeTrees();
  return;

}  // end 'StandaloneInit()'



void SCorrelatorFolder::Analyze() {

  // print debug statement
  if (m_inDebugMode) PrintDebug(3);

  // make sure standalone mode is on
  if (m_inComplexMode) {
    PrintError(0);
    assert(m_inStandaloneMode);
  }

  // announce start of analysis
  PrintMessage(2);

  /* TODO analyzing goes here */
  return;

}  // end 'StandaloneAnalyze()'



void SCorrelatorFolder::End() {

  // print debug statement
  if (m_inDebugMode) PrintDebug(4);

  // make sure standalone mode is on & save output
  if (m_inComplexMode) {
    PrintError(0);
    assert(m_inStandaloneMode);
  } else {
    SaveOutput();
  }

  // announce end
  PrintMessage(3);
  return;

}  // end 'StandaloneEnd()'

// end ------------------------------------------------------------------------
