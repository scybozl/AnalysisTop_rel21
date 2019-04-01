#ifndef FIT_FUNCTIONS_C
#define FIT_FUNCTIONS_C

#include "TMath.h"

using namespace TMath;

//______________________________________________________________________________
double MC_pdf(double *x, double *par)
{

  Int_t NPARTOT = 36;
  
  double mtop   = par[NPARTOT+0];
  double jes    = par[NPARTOT+1]-1.0; 
  double bjes   = par[NPARTOT+2]-1.0; 

  int NPAR=6; // number of par, for separate fit

  // Guass  Component
  double gp0 = par[0]+par[0+NPAR]*mtop + par[0+2*NPAR]*jes + par[0+3*NPAR]*bjes;
  double gp1 = par[1]+par[1+NPAR]*mtop + par[1+2*NPAR]*jes + par[1+3*NPAR]*bjes;
  double gp2 = par[2]+par[2+NPAR]*mtop + par[2+2*NPAR]*jes + par[2+3*NPAR]*bjes;

  double gaussval = gp0*exp(-0.5*pow((x[0]-gp1)/gp2,2));

  // Landau Component
  double lp0 = par[3]+par[3+NPAR]*mtop + par[3+2*NPAR]*jes + par[3+3*NPAR]*bjes; 
  double lp1 = par[4]+par[4+NPAR]*mtop + par[4+2*NPAR]*jes + par[4+3*NPAR]*bjes; 
  double lp2 = par[5]+par[5+NPAR]*mtop + par[5+2*NPAR]*jes + par[5+3*NPAR]*bjes; 

  double landauval = lp0*(TMath::Landau(x[0], lp1, lp2)/lp2);

  double value = par[NPARTOT+3]*(gaussval+landauval);
  
  return value;


}

double MC_pdf_R(double *x, double *par)
{

  Int_t NPARTOT_R = 36;
  
  double mtop   = par[NPARTOT_R+0];
  double jes    = par[NPARTOT_R+1]-1.0; 
  double bjes   = par[NPARTOT_R+2]-1.0; 

  int NPAR=6; // number of par, for separate fit

  // Guass  Component
  double gp0 = par[0]+par[0+NPAR]*mtop + par[0+2*NPAR]*jes + par[0+3*NPAR]*bjes;
  double gp1 = par[1]+par[1+NPAR]*mtop + par[1+2*NPAR]*jes + par[1+3*NPAR]*bjes;
  double gp2 = par[2]+par[2+NPAR]*mtop + par[2+2*NPAR]*jes + par[2+3*NPAR]*bjes;

  double gaussval = gp0*exp(-0.5*pow((x[0]-gp1)/gp2,2));

  // Landau Component
  double lp0 = par[3]+par[3+NPAR]*mtop + par[3+2*NPAR]*jes + par[3+3*NPAR]*bjes; 
  double lp1 = par[4]+par[4+NPAR]*mtop + par[4+2*NPAR]*jes + par[4+3*NPAR]*bjes; 
  double lp2 = par[5]+par[5+NPAR]*mtop + par[5+2*NPAR]*jes + par[5+3*NPAR]*bjes; 

  double landauval = lp0*(TMath::Landau(x[0], lp1, lp2)/lp2);


  double value = par[NPARTOT_R+3]*(gaussval+landauval);
  
  return value;
}

double MC_pdf_R_ggl(double *x, double *par)
{

  int NPARTOT_R = 36;
  
  double mtop   = par[NPARTOT_R+0]-172.5;
  double jes    = par[NPARTOT_R+1]-1.0; 
  double bjes   = par[NPARTOT_R+2]-1.0; 

  int NPAR=9; // number of par, for separate fit

  // Gauss  Component 1
  double gp0 = par[0]+par[0+NPAR]*mtop + par[0+2*NPAR]*jes + par[0+3*NPAR]*bjes;
  double gp1 = par[1]+par[1+NPAR]*mtop + par[1+2*NPAR]*jes + par[1+3*NPAR]*bjes;
  double gp2 = par[2]+par[2+NPAR]*mtop + par[2+2*NPAR]*jes + par[2+3*NPAR]*bjes;

  double gaussval1 = gp0*exp(-0.5*pow((x[0]-gp1)/gp2,2));

  // Gauss  Component 2
  double ggp0 = par[3]+par[3+NPAR]*mtop + par[3+2*NPAR]*jes + par[3+3*NPAR]*bjes;
  double ggp1 = par[4]+par[4+NPAR]*mtop + par[4+2*NPAR]*jes + par[4+3*NPAR]*bjes;
  double ggp2 = par[5]+par[5+NPAR]*mtop + par[5+2*NPAR]*jes + par[5+3*NPAR]*bjes;

  double gaussval2 = ggp0*exp(-0.5*pow((x[0]-ggp1)/ggp2,2));

  // Landau Component
  double lp0 = par[6]+par[6+NPAR]*mtop + par[6+2*NPAR]*jes + par[6+3*NPAR]*bjes; 
  double lp1 = par[7]+par[7+NPAR]*mtop + par[7+2*NPAR]*jes + par[7+3*NPAR]*bjes; 
  double lp2 = par[8]+par[8+NPAR]*mtop + par[8+2*NPAR]*jes + par[8+3*NPAR]*bjes; 

  double landauval = lp0*(TMath::Landau(x[0], lp1, lp2)/lp2);

  double value = par[NPARTOT_R+3]*(gaussval1+gaussval2+landauval);
  
  return value;
}


double MC_pdf_gll(double *x, double *par)
{

  int NPARTOT = 36;
  
  //new parameterization for mtopreco:
  // gauss + inv.landau + landau
  double mtop   = par[NPARTOT+0]-172.5;
  double jes    = par[NPARTOT+1]-1.0; 
  double bjes   = par[NPARTOT+2]-1.0; 

  int NPAR=9; // number of par, for separate fit

  // Guass  Component
  double gp0 = par[0]+par[0+NPAR]*mtop + par[0+2*NPAR]*jes + par[0+3*NPAR]*bjes;
  double gp1 = par[1]+par[1+NPAR]*mtop + par[1+2*NPAR]*jes + par[1+3*NPAR]*bjes;
  double gp2 = par[2]+par[2+NPAR]*mtop + par[2+2*NPAR]*jes + par[2+3*NPAR]*bjes;

  double gaussval = gp0*exp(-0.5*pow((x[0]-gp1)/gp2,2));
  
  // inv. Landau Component
  double ilp0 = par[3]+par[3+NPAR]*mtop + par[3+2*NPAR]*jes + par[3+3*NPAR]*bjes; 
  double ilp1 = par[4]+par[4+NPAR]*mtop + par[4+2*NPAR]*jes + par[4+3*NPAR]*bjes; 
  double ilp2 = par[5]+par[5+NPAR]*mtop + par[5+2*NPAR]*jes + par[5+3*NPAR]*bjes; 
  
  double inv_landauval = ilp0*(TMath::Landau(2*ilp1-x[0], ilp1, ilp2)/ilp2);
  
  // Landau Component
  double lp0 = par[6]+par[6+NPAR]*mtop + par[6+2*NPAR]*jes + par[6+3*NPAR]*bjes; 
  double lp1 = par[7]+par[7+NPAR]*mtop + par[7+2*NPAR]*jes + par[7+3*NPAR]*bjes; 
  double lp2 = par[8]+par[8+NPAR]*mtop + par[8+2*NPAR]*jes + par[8+3*NPAR]*bjes; 
  
  double landauval = lp0*(TMath::Landau(x[0], lp1, lp2)/lp2);

  //  cout << lp0 << "  " << x[0] << "  " << lp1 << "  " << lp2 << "  " << Landau(x[0], lp1, lp2) << std::endl; 
  
  //  cout <<  landauval << "  " << inv_landauval << "  " << gaussval << "   " << par[NPARTOT+3] << std::endl;
  
  double value = par[NPARTOT+3]*(gaussval+inv_landauval+landauval);
  
  return value;
}			 


//______________________________________________________________________________
double MC_BKG_pdf(double *x, double *par)
{

  int NPARTOTBKG = 12;

  double mtop   = par[NPARTOTBKG+0];
  double jes    = par[NPARTOTBKG+1]-1.0; 
  double bjes   = par[NPARTOTBKG+2]-1.0; 

  int NPAR=3; // number of par, for separate fit

  // Landau Component
  double lp0 = par[0]+par[0+NPAR]*mtop + par[0+2*NPAR]*jes + par[0+3*NPAR]*bjes;
  double lp1 = par[1]+par[1+NPAR]*mtop + par[1+2*NPAR]*jes + par[1+3*NPAR]*bjes;
  double lp2 = par[2]+par[2+NPAR]*mtop + par[2+2*NPAR]*jes + par[2+3*NPAR]*bjes;

  double landauval = lp0*(TMath::Landau(x[0], lp1, lp2)/lp2);


  double value = par[NPARTOTBKG+3]*(landauval);
  
  return value;


}

//______________________________________________________________________________
double MC_SUM_pdf(double *x, double *par)
// sum of the above functions for a total of NPARTOT+4+NPARTOTBKG+4 par
{
  Int_t NPARTOT = 36;

  //return MC_pdf(x,par) + MC_BKG_pdf(x,&par[NPARTOT+4]); 
  return MC_pdf_gll(x,par) + MC_BKG_pdf(x,&par[NPARTOT+4]); 
}

// This are function to draw
//______________________________________________________________________________
double MC_pdf_mW(double *x, double *par)
{

  int NPARTOT_W = 12;
  
  double jes    = par[NPARTOT_W]-1.0; 

  int NPAR=6; // number of par, for separate fit

  // Guass  Component
  double gp0 = par[0]+par[0+NPAR]*jes;
  double gp1 = par[1]+par[1+NPAR]*jes;
  double gp2 = par[2]+par[2+NPAR]*jes;
  double gaussval = gp0*exp(-0.5*pow((x[0]-gp1)/gp2,2));

  // Gauss2 Component
  double lp0 =  par[3]+par[3+NPAR]*jes;
  double lp1 =  par[4]+par[4+NPAR]*jes;
  double lp2 =  par[5]+par[5+NPAR]*jes;
  double gaussval2 = lp0*exp(-0.5*pow((x[0]-lp1)/lp2,2));

  double value = par[NPARTOT_W+1]*(gaussval+gaussval2);

  return value;


}
//______________________________________________________________________________
double MC_SUM_pdf_mW(double *x, double *par)
// sum of the above functions for a total of 2*NPARTOT_W+2 par
{

  Int_t NPARTOT_W = 12;
  
  return MC_pdf_mW(x,par) + MC_pdf_mW(x,&par[NPARTOT_W+2]); 

}

//______________________________________________________________________________
double MC_BKG_Rlb(double *x, double *par)
{

 
  int NPARTOTBKG_R = 12;
  
  double bjes    = par[NPARTOTBKG_R]-1.0; 

  int NPAR=6; // number of par, for separate fit

  // Guass  Component
  double gp0 = par[0]+par[0+NPAR]*bjes;
  double gp1 = par[1]+par[1+NPAR]*bjes;
  double gp2 = par[2]+par[2+NPAR]*bjes;
  double gaussval = gp0*exp(-0.5*pow((x[0]-gp1)/gp2,2));

  // Gauss2 Component
  double lp0 =  par[3]+par[3+NPAR]*bjes;
  double lp1 =  par[4]+par[4+NPAR]*bjes;
  double lp2 =  par[5]+par[5+NPAR]*bjes;
  double gaussval2 = lp0*exp(-0.5*pow((x[0]-lp1)/lp2,2));

  double value = par[NPARTOTBKG_R+1]*(gaussval+gaussval2);

  return value;


}

//______________________________________________________________________________
double MC_SUM_pdf_Rlb3d(double *x, double *par)
// sum of the above functions for a total of NPARTOT_R+4 + NPARTOT_R+2 par
{

  Int_t NPARTOT_R = 36;
  
  return MC_pdf_R_ggl(x,par) + MC_BKG_Rlb(x,&par[NPARTOT_R+4]); 
}

//______________________________________________________________________________
double MC_pdf_dilepton_langauss(double *x, double *par)
{
  int NPAR=6; // number of par, for separate fit
  double mtop = par[2*NPAR+0];
  // Gauss  Component
  double gp0 = par[0]+par[0+NPAR]*mtop;
  double gp1 = par[1]+par[1+NPAR]*mtop;
  double gp2 = par[2]+par[2+NPAR]*mtop;
  double gaussval = gp0*exp(-0.5*pow((x[0]-gp1)/gp2,2));
  // Landau Component
  double lp0 = par[3]+par[3+NPAR]*mtop;
  double lp1 = par[4]+par[4+NPAR]*mtop;
  double lp2 = par[5]+par[5+NPAR]*mtop;
  double landauval = lp0*(TMath::Landau(x[0], lp1, lp2)/lp2);
  //sum
  double value = par[2*NPAR+1]*(gaussval+landauval);
  return value;
}
//______________________________________________________________________________
double MC_pdf_dilepton_doublegauss(double *x, double *par)
{
  int NPAR=6; // number of par, for separate fit
  double mtop = par[2*NPAR+0];
  // Gauss  Component
  double gp0 = par[0]+par[0+NPAR]*mtop;
  double gp1 = par[1]+par[1+NPAR]*mtop;
  double gp2 = par[2]+par[2+NPAR]*mtop;
  double gaussval1 = gp0*exp(-0.5*pow((x[0]-gp1)/gp2,2));
  // Gauss  Component
  double gp3 = par[3]+par[3+NPAR]*mtop;
  double gp4 = par[4]+par[4+NPAR]*mtop;
  double gp5 = par[5]+par[5+NPAR]*mtop;
  double gaussval2 = gp3*exp(-0.5*pow((x[0]-gp4)/gp5,2));
  //sum
  double value = par[2*NPAR+1]*(gaussval1+gaussval2);
  return value;
}
//______________________________________________________________________________
Double_t MC_pdf_dilepton_hinklan(Double_t *x, Double_t *par)
{
  // two additional pars: mtop, and overall normalization
  int NPAR=9; // number of par, for separate fit
  double mtop = par[2*NPAR+0];


  // hinkley
  double z= x[0];
  double norm= par[0]+par[0+NPAR]*mtop;
  double mx=   par[1]+par[1+NPAR]*mtop;
  double sx=   par[2]+par[2+NPAR]*mtop; // can cause problems when getting too small
  double my=   par[3]+par[3+NPAR]*mtop;
  double sy=   par[4]+par[4+NPAR]*mtop; // can cause problems when getting too small
  double rho=  par[5]+par[5+NPAR]*mtop;
  double onemr2= 1.0-pow(rho,2);
  double sonemr2= sqrt( onemr2 );
  double a= sqrt( pow(z/sx,2) - 2.0*rho*z/(sx*sy) + 1.0/pow(sy,2));
  double b= mx*z/pow(sx,2) - rho*(mx+my*z)/(sx*sy) + my/pow(sy,2);
  double c= pow(mx/sx,2) - 2.0*rho*mx*my/(sx*sy) + pow(my/sy,2);
  double d= exp( (pow(b,2)-c*pow(a,2))/(2.0*onemr2*pow(a,2)) );
  double pi= TMath::Pi();
  double hinkley= norm*( b*d/(pow(a,3)*sqrt(2.0*pi)*sx*sy)*TMath::Erf( b/(sonemr2*a) )
			 + sonemr2/(pow(a,2)*pi*sx*sy)
			 *exp(-c/(2.0*onemr2)) );
  // Laundau
  double p0 = par[6]+par[6+NPAR]*mtop;
  double p1 = par[7]+par[7+NPAR]*mtop;
  double p2 = par[8]+par[8+NPAR]*mtop;
  double landau= p0*(TMath::Landau(x[0], p1, p2)/p2);
  //sum
  double value = par[2*NPAR+1]*(hinkley+landau);
  return value;

}
//______________________________________________________________________________
double MC_pdf_dilepton_cryballlandau(double *x, double *par)
{
  // two additional pars: mtop, and overall normalization
  int NPAR=8; // number of par, for separate fit
  double mtop = par[2*NPAR+0]; 
  // Crystal Ball function
  // Gaussian: N = normalisation, m = mean, s = sigma
  // Tail:     a = boundary in sigma between gaussian and tail, n = relative hight of tail
  double z = -x[0];
  double N = par[0]+par[0+NPAR]*mtop;
  double m = -(par[1]+par[1+NPAR]*mtop);
  double s = par[2]+par[2+NPAR]*mtop;
  double a = par[3]+par[3+NPAR]*mtop;
  double n = par[4]+par[4+NPAR]*mtop;
  double A = pow(n/fabs(a),n)*exp(-pow(a,2)/2);
  double B = n/fabs(a)-fabs(a);
  double cryresult = 0;
  if ((z-m)/s > -a) cryresult = N*exp(-pow(z-m,2)/(2*pow(s,2)));
  else              cryresult = N*A*pow(B-(z-m)/s,-n);
  //landau
  double p0 = par[5]+par[5+NPAR]*mtop;
  double p1 = par[6]+par[6+NPAR]*mtop;
  double p2 = par[7]+par[7+NPAR]*mtop;
  double lanresult= p0*(TMath::Landau(x[0], p1, p2)/p2);
  //sum
  double value = par[2*NPAR+1]*(cryresult + lanresult);  
  return value;

}
//______________________________________________________________________________
double MC_pdf_dilepton_cryballgauss(double *x, double *par)
{
  // two additional pars: mtop, and overall normalization
  int NPAR=8; // number of par, for separate fit
  double mtop = par[2*NPAR+0]; 
  // Crystal Ball function
  // Gaussian: N = normalisation, m = mean, s = sigma
  // Tail:     a = boundary in sigma between gaussian and tail, n = relative hight of tail
  double z = -x[0];
  double N = par[0]+par[0+NPAR]*mtop;
  double m = -(par[1]+par[1+NPAR]*mtop);
  double s = par[2]+par[2+NPAR]*mtop;
  double a = par[3]+par[3+NPAR]*mtop;
  double n = par[4]+par[4+NPAR]*mtop;
  double A = pow(n/fabs(a),n)*exp(-pow(a,2)/2);
  double B = n/fabs(a)-fabs(a);
  double cryresult = 0;
  if ((z-m)/s > -a) cryresult = N*exp(-pow(z-m,2)/(2*pow(s,2)));
  else              cryresult = N*A*pow(B-(z-m)/s,-n);
  // Gaussian function
  double N_gauss = par[5]+par[5+NPAR]*mtop;
  double m_gauss = par[6]+par[6+NPAR]*mtop;
  double s_gauss = par[7]+par[7+NPAR]*mtop;
  double gauss_result = N_gauss * TMath::Gaus( x[0], m_gauss, s_gauss );
  //sum
  double value = par[2*NPAR+1]*(cryresult + gauss_result);  
  return value;
}
//______________________________________________________________________________
double MC_pdf_dilepton_cryball(double *x, double *par)
{
  // two additional pars: mtop, and overall normalization
  int NPAR=5; // number of par, for separate fit
  double mtop = par[2*NPAR+0]; 
  // Crystal Ball function
  // Gaussian: N = normalisation, m = mean, s = sigma
  // Tail:     a = boundary in sigma between gaussian and tail, n = relative hight of tail
  double z = -x[0];
  double N = par[0]+par[0+NPAR]*mtop;
  double m = -(par[1]+par[1+NPAR]*mtop);
  double s = par[2]+par[2+NPAR]*mtop;
  double a = par[3]+par[3+NPAR]*mtop;
  double n = par[4]+par[4+NPAR]*mtop;
  double A = pow(n/fabs(a),n)*exp(-pow(a,2)/2);
  double B = n/fabs(a)-fabs(a);
  double result = 0;
  if ((z-m)/s > -a) result = N*exp(-pow(z-m,2)/(2*pow(s,2)));
  else              result = N*A*pow(B-(z-m)/s,-n);
  double value = par[2*NPAR+1]*result;
  return value;
}
//______________________________________________________________________________
double MC_pdf_dilepton_gauss(double *x, double *par)
{
  int NPAR=3; // number of par, for separate fit
  double mtop = par[2*NPAR+0];
  double gp0 = par[0]+par[0+NPAR]*mtop;
  double gp1 = par[1]+par[1+NPAR]*mtop;
  double gp2 = par[2]+par[2+NPAR]*mtop;
  double gaussval1 = gp0*exp(-0.5*pow((x[0]-gp1)/gp2,2));
  double value = par[2*NPAR+1]*(gaussval1);
  return value;
}
//______________________________________________________________________________
double MC_pdf_dilepton_landau(double *x, double *par)
{
  int NPAR=3; // number of par, for separate fit
  double mtop = par[2*NPAR+0];
  double gp0 = par[0]+par[0+NPAR]*mtop;
  double gp1 = par[1]+par[1+NPAR]*mtop;
  double gp2 = par[2]+par[2+NPAR]*mtop;
  double val1 = gp0*(TMath::Landau(x[0], gp1, gp2)/gp2);
  double value = par[2*NPAR+1]*(val1);
  return value;
}
//______________________________________________________________________________
double MC_pdf_dilepton_asymmgauss(double *x, double *par)
{
  int NPAR=4; // number of par, for separate fit
  double mtop = par[2*NPAR+0];
  // Asymmetric Gaussian function
  double X = x[0];
  double N          = par[0]+par[0+NPAR]*mtop;
  double Mean       = par[1]+par[1+NPAR]*mtop;
  double SigmaLeft  = par[2]+par[2+NPAR]*mtop;
  double SigmaRight = par[3]+par[3+NPAR]*mtop;
  double Sigma = ( Mean < X )? SigmaLeft : SigmaRight;
  return par[2*NPAR+1]* N * TMath::Gaus( X, Mean, Sigma );
} 
//______________________________________________________________________________
double MC_pdf_dilepton_gaussasymmgauss(double *x, double *par)
{
  int NPAR=7; // number of par, for separate fit
  double mtop = par[2*NPAR+0];
  double X = x[0];
  // Gaussian function
  double gp0 = par[0]+par[0+NPAR]*mtop;
  double gp1 = par[1]+par[1+NPAR]*mtop;
  double gp2 = par[2]+par[2+NPAR]*mtop;
  double gaussval = gp0*exp(-0.5*pow((X-gp1)/gp2,2));
  // Asymmetric Gaussian function
  double N          = par[3]+par[3+NPAR]*mtop;
  double Mean       = par[4]+par[4+NPAR]*mtop;
  double SigmaLeft  = par[5]+par[5+NPAR]*mtop;
  double SigmaRight = par[6]+par[6+NPAR]*mtop;
  double Sigma = ( Mean < X )? SigmaLeft : SigmaRight;
  double asymmgaussval = N * TMath::Gaus( X, Mean, Sigma );
  return par[2*NPAR+1] * (gaussval + asymmgaussval);
}
//______________________________________________________________________________
double MC_pdf_dilepton_lanasymmgauss(double *x, double *par)
{
  int NPAR=7; // number of par, for separate fit
  double mtop = par[2*NPAR+0];
  double X = x[0];
  // Landau function
  double lp0 =  par[0]+par[0+NPAR]*mtop;
  double lp1 =  par[1]+par[1+NPAR]*mtop;
  double lp2 =  par[2]+par[2+NPAR]*mtop;
  double landauval = lp0*(TMath::Landau(X, lp1, lp2)/lp2);
  // Asymmetric Gaussian function
  double N          = par[3]+par[3+NPAR]*mtop;
  double Mean       = par[4]+par[4+NPAR]*mtop;
  double SigmaLeft  = par[5]+par[5+NPAR]*mtop;
  double SigmaRight = par[6]+par[6+NPAR]*mtop;
  double Sigma = ( Mean < X )? SigmaLeft : SigmaRight;
  double asymmgaussval = N * TMath::Gaus( X, Mean, Sigma );
  return par[2*NPAR+1] * (landauval + asymmgaussval);
} 
//______________________________________________________________________________
double MC_pdf_dilepton_gammagauss(double *x, double *par)
{
  int NPAR=7; // number of par, for separate fit
  double mtop = par[2*NPAR+0];
  // gamma distribution
  double N     = par[0]+par[0+NPAR]*mtop;
  double gamma = par[1]+par[1+NPAR]*mtop;
  double mu    = par[2]+par[2+NPAR]*mtop;
  double beta  = par[3]+par[3+NPAR]*mtop;
  double gamma_result = 0;
  if (gamma < 0 || x[0] < mu || beta < 0) gamma_result = 0; 
  else gamma_result = N*TMath::GammaDist(x[0],gamma,mu,beta);
  // Gaussian function
  double N_gauss = par[4]+par[4+NPAR]*mtop;
  double m       = par[5]+par[5+NPAR]*mtop;
  double s       = par[6]+par[6+NPAR]*mtop;
  double gauss_result = N_gauss * TMath::Gaus( x[0], m, s );
  return par[2*NPAR+1] * (gamma_result + gauss_result);
} 
//______________________________________________________________________________
double MC_pdf_dilepton_gamma(double *x, double *par)
{
  int NPAR=4; // number of par, for separate fit
  double mtop = par[2*NPAR+0];
  // gamma distribution
  double N     = par[0]+par[0+NPAR]*mtop;
  double gamma = par[1]+par[1+NPAR]*mtop;
  double mu    = par[2]+par[2+NPAR]*mtop;
  double beta  = par[3]+par[3+NPAR]*mtop;
  double gamma_result = 0;
  if (gamma < 0 || x[0] < mu || beta < 0) gamma_result = 0; 
  else gamma_result = N*TMath::GammaDist(x[0],gamma,mu,beta);
  return par[2*NPAR+1] * gamma_result;
}
//______________________________________________________________________________
double MC_pdf_dilepton_weibull(double *x, double *par)
{
  int NPAR=4; // number of par, for separate fit
  double mtop=par[2*NPAR+0];
  // weibull distribution
  double N       = par[0]+par[0+NPAR]*mtop;
  double xoffset = par[1]+par[1+NPAR]*mtop;
  double xscale  = par[2]+par[2+NPAR]*mtop;
  double k       = par[3]+par[3+NPAR]*mtop;
  double X       = (xscale>0 && x[0] > xoffset)?(x[0]-xoffset)/xscale:0;
  double weibull_result=N*pow(X,k-1)*exp(-pow(X,k));
  return par[2*NPAR+1] * weibull_result;
} 
//______________________________________________________________________________
double MC_pdf_dilepton_weibullgauss(double *x, double *par)
{
  int NPAR=7; // number of par, for separate fit
  double mtop=par[2*NPAR+0];
  // weibull distribution
  double N       = par[0]+par[0+NPAR]*mtop;
  double xoffset = par[1]+par[1+NPAR]*mtop;
  double xscale  = par[2]+par[2+NPAR]*mtop;
  double k       = par[3]+par[3+NPAR]*mtop;
  double X       = (xscale>0 && x[0] > xoffset)?(x[0]-xoffset)/xscale:0;
  double weibull_result=N*pow(X,k-1)*exp(-pow(X,k));
  // Gaussian function
  double N_gauss = par[4]+par[4+NPAR]*mtop;
  double m       = par[5]+par[5+NPAR]*mtop;
  double s       = par[6]+par[6+NPAR]*mtop;
  double gauss_result = N_gauss * TMath::Gaus( x[0], m, s );
  return par[2*NPAR+1] * (weibull_result + gauss_result);
} 


#endif
