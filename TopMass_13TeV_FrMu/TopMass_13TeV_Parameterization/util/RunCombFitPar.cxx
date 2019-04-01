#include "TopMass_13TeV_Parameterization/CombFitPar.h"

#include "TSystem.h"

#include <sstream>
#include <iostream>
#include <fstream>
#include <math.h>
#include <set>
#include <iomanip>
#include <string>

#include "TString.h"

using namespace std;


#include <sys/time.h>
typedef unsigned long long timestamp_t;

static timestamp_t
get_timestamp ()
{
  struct timeval now;
  gettimeofday (&now, NULL);
  return  now.tv_usec + (timestamp_t)now.tv_sec * 1000000;
}


int main(int argc, char* argv[]){
  
  timestamp_t t0 = get_timestamp();

  if(argc != 3){
    cout << "\t" << endl;
    cout << "ERROR: Number of input variables is wrong!!!   ===> " << argc << endl;
    cout << "\t" << endl;
    
    return 1;
  }


  TString histo_name = argv[1];
  TString ConfigFileName = argv[2];

  CombFitPar* myCombFitPar = new CombFitPar();
  myCombFitPar->GetFinalPars(histo_name, ConfigFileName);
  delete myCombFitPar;
    

  //Write out time to run
  timestamp_t t1 = get_timestamp();
  double secs = (t1 - t0) / 1000000.0L;
  std::cout << "TIME TO FIND FINAL PARAMETERS: " << secs << std::endl;

  return 0;
}	



