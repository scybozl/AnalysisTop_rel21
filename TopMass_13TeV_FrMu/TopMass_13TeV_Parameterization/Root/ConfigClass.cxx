#include "TopMass_13TeV_Parameterization/ConfigClass.h"
#include "TopMass_13TeV_Parameterization/FitInfo.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <math.h>
#include <set>
#include <iomanip>
#include <vector>

#include "TString.h"

using namespace std;

ConfigClass::ConfigClass()                          
{
  
  // we do not define default values here on purpose, because we want to ensure that each user thinks about the settings she/he needs
  // and does not just use the default that might be meaningless to her/his analysis

}

std::vector<TString> ConfigClass::Split(std::string values, char delimeter)
{
  std::stringstream ss(values);
  std::string item;
  std::vector<TString> splittedStrings;
  while (std::getline(ss, item, delimeter))
    {
      splittedStrings.push_back(TString(item));
    }
  return splittedStrings;
}

std::vector<double> ConfigClass::SplitFloat(std::string values, char delimeter)
{
  std::stringstream ss(values);
  std::string item;
  std::vector<double> splittedStrings;
  while (std::getline(ss, item, delimeter))
    {
      splittedStrings.push_back(TString(item).Atof());
    }
  return splittedStrings;
}

void ConfigClass::readSettingsFromConfig(TString ConfigFileName)
{

  
  ifstream ConfigListFile;
  //ConfigListFile.open(ConfigFileName.c_str());
  ConfigListFile.open(ConfigFileName);

  int counter = 0;

  string fileline;
  string line;

  while (ConfigListFile.good()) {

    getline(ConfigListFile, fileline);
    std::istringstream input_line(fileline);
    
    string name;
    string value;

    input_line >> name;
    input_line >> value;

    if(name == '#' || fileline.empty())
      continue;

    //    std::cout << value.c_str() << std::endl;

    if(name == "FileList")
      m_fileList = TString(value);
    // ANDREA: FOR NOW STEERING DIFFERENTLY!
    // else if(name == "histname_mtop")
    else if(name == "xaxis_title_mtop")
      xaxis_title_mtop = TString(value);
    else if(name == "xaxis_unit_mtop")
      xaxis_unit_mtop = TString(value);
    else if(name == "fitmin_mtop")
      fitmin_mtop = TString(value).Atof();
    else if(name == "fitmax_mtop")
      fitmax_mtop = TString(value).Atof();
    else if(name == "npars_sep_mtop")
      npars_sep_mtop = TString(value).Atoi();
    else if(name == "npars_comb_mtop")
      npars_comb_mtop = TString(value).Atoi();
    // now need to split this into substrings
    else if(name == "subfunction_names_mtop") // this defines the names in the final plot
      v_mtop_subFunctionNames = this -> Split(value, ',');
    else if(name == "subfunction_types_mtop"){ // this defines which type is used
      v_mtop_subFunctionTypes = this -> Split(value, ',');

      for(int i = 0; i < v_mtop_subFunctionTypes.size(); ++i){
	
	if(v_mtop_subFunctionTypes[i] == "gauss")
	  v_mtop_subFunctions.push_back(new TF1(v_mtop_subFunctionNames[i], gauss, fitmin_mtop, fitmax_mtop, 3));
	if(v_mtop_subFunctionTypes[i] == "landau_n")
          v_mtop_subFunctions.push_back(new TF1(v_mtop_subFunctionNames[i], landau_n, fitmin_mtop, fitmax_mtop, 3));
	if(v_mtop_subFunctionTypes[i] == "landau")
	  v_mtop_subFunctions.push_back(new TF1(v_mtop_subFunctionNames[i], landau, fitmin_mtop, fitmax_mtop, 3));

      }
    }
    else if(name == "pars_init_mtop")
      pars_init_mtop = this -> SplitFloat(value, ',');
    else if(name == "pars_name_mtop")
      pars_name_mtop = this -> Split(value, ',');
    else if(name == "xaxis_title_mw")
      xaxis_title_mw = TString(value);
    else if(name == "xaxis_unit_mw")
      xaxis_unit_mw = TString(value);
    else if(name == "fitmin_mw")
      fitmin_mw = TString(value).Atof();
    else if(name == "fitmax_mw")
      fitmax_mw = TString(value).Atof();
    else if(name == "npars_sep_mw")
      npars_sep_mw = TString(value).Atoi();
    else if(name == "npars_comb_mw")
      npars_comb_mw = TString(value).Atoi();
    // now need to split this into substrings 
    else if(name == "subfunction_names_mw")
      v_mw_subFunctionNames = this -> Split(value, ',');
    else if(name == "subfunction_types_mw"){ // this defines which type is used                                                                                                                           
      v_mw_subFunctionTypes = this -> Split(value, ',');

      for(int i = 0; i < v_mw_subFunctionTypes.size(); ++i){

        if(v_mw_subFunctionTypes[i] == "gauss")
          v_mw_subFunctions.push_back(new TF1(v_mw_subFunctionNames[i], gauss, fitmin_mw, fitmax_mw, 3));
	if(v_mw_subFunctionTypes[i] == "landau_n")
          v_mw_subFunctions.push_back(new TF1(v_mw_subFunctionNames[i], landau_n, fitmin_mw, fitmax_mw, 3));
	if(v_mw_subFunctionTypes[i] == "landau")
          v_mw_subFunctions.push_back(new TF1(v_mw_subFunctionNames[i], landau, fitmin_mw, fitmax_mw, 3));

      }
    }
    else if(name == "pars_init_mw")
      pars_init_mw = this -> SplitFloat(value, ',');
    else if(name == "pars_name_mw")
      pars_name_mw = this -> Split(value, ',');
    else if(name == "xaxis_title_rbq")
      xaxis_title_rbq = TString(value);
    else if(name == "xaxis_unit_rbq")
      xaxis_unit_rbq = TString(value);
    else if(name == "fitmin_rbq")
      fitmin_rbq = TString(value).Atof();
    else if(name == "fitmax_rbq")
      fitmax_rbq = TString(value).Atof();
    else if(name == "npars_sep_rbq")
      npars_sep_rbq = TString(value).Atoi();
    else if(name == "npars_comb_rbq")
      npars_comb_rbq = TString(value).Atoi();
    // now need to split this into substrings                                                                   
    else if(name == "subfunction_names_rbq")
      v_rbq_subFunctionNames = this -> Split(value, ',');
    else if(name == "subfunction_types_rbq"){ // this defines which type is used                                                                                                                             
      v_rbq_subFunctionTypes = this -> Split(value, ',');

      for(int i = 0; i < v_rbq_subFunctionTypes.size(); ++i){

        if(v_rbq_subFunctionTypes[i] == "gauss")
          v_rbq_subFunctions.push_back(new TF1(v_rbq_subFunctionNames[i], gauss, fitmin_rbq, fitmax_rbq, 3));
        if(v_rbq_subFunctionTypes[i] == "landau_n")
          v_rbq_subFunctions.push_back(new TF1(v_rbq_subFunctionNames[i], landau_n, fitmin_rbq, fitmax_rbq, 3));
        if(v_rbq_subFunctionTypes[i] == "landau")
          v_rbq_subFunctions.push_back(new TF1(v_rbq_subFunctionNames[i], landau, fitmin_rbq, fitmax_rbq, 3));

      }
    }
    else if(name == "pars_init_rbq")
      pars_init_rbq = this -> SplitFloat(value, ',');
    else if(name == "pars_name_rbq")
      pars_name_rbq = this -> Split(value, ',');
    else{
      
      std::cout << "ERROR(ConfigClass)::The configuration setting " << name.c_str() << " is not defined!!! ===> EXIT." << std::endl;
      
      exit(0);
      
    }


  }

}

