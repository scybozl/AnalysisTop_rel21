#ifndef ConfigClass_H_
#define ConfigClass_H_

//#include "PlotFactory_13TeV/Enums.h"

#include <memory>
#include <string>
#include <vector>
#include <set>
#include <list>
#include <iostream>

#include "TString.h"

class ConfigClass {

 public:

  ConfigClass();
  virtual ~ConfigClass(){}

  void readSettingsFromConfig(TString);

  TString GetFileList(){return m_fileList;};
  std::vector<TString> Split(std::string values, char delimiter);
  std::vector<double> SplitFloat(std::string values, char delimeter);

  /* std::string GetAnalysisType(){return m_analysisType;}; */
  /* std::string GetLeptonChannel(){return m_leptonChannel;}; */

  // some of the settings are not defined by the config file but set "by hand"

  /* void SetInputFile(std::string value){m_inputFile = value;}; */
  /* void SetOutputFile(std::string value){m_outputFile = value;}; */
  /* void SetOutputTreeFile(std::string value){m_outputTreeFile = value;}; */
  /* void SetSampleType(std::string value){m_sampleType = value;}; */
  /* void SetJetBin(BINS JetBin){m_JetBin = JetBin;}; */
  /* void SetNumberOfBTags(BINS nr){m_BTagBin = nr;}; */
  /* void SetVetoJetBin(BINS JetBin){m_VetoJetBin = JetBin;}; */
  /* void SetVetoNumberOfBTags(BINS nr){m_VetoBTagBin = nr;}; */

 private:
  
  TString m_fileList;
  /* std::string m_analysisType; */
  /* std::string m_leptonChannel; */
  /* std::string m_inputFile; */
  /* std::string m_outputFile; */
  /* std::string m_outputTreeFile; */
  /* std::string m_sampleType; */

  /* BINS m_JetBin; */
  /* BINS m_BTagBin; */
  /* BINS m_VetoJetBin; */
  /* BINS m_VetoBTagBin; */


};

#endif
