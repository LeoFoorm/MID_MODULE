#include <TCanvas.h>
#include <TGraph2D.h>
#include <TGraph.h>
#include <TAxis.h>
#include <TLegend.h>
#include <TPad.h>
#include <TMath.h>

void calculus() {
    double p_min = 0.1; // GeV/c
    double p_max = 2.5;  // GeV/c

    const double K = 0.307075; // MeV·cm^2/mol
    const double z = 1.0;   // muon charge
    const double Z_over_A = 0.54141; // BC-404 plastic
    const double I = 6.47e-5; // MeV
    const double me = 0.510998918;  // MeV
    const double mmu = 105.6583745; // MeV
    const double rho = 1.032; // g/cm^3

    // ======== BETA AND GAMMA ==============
    double E = sqrt(p_min * p_min  + mmu*0.001 * mmu*0.001 ); // total energy in MeV
        double beta = p_min / E;
        double gamma = E / (mmu*0.001);
    cout<<"beta: " << beta << endl;
    cout<<"gamma: " << gamma << endl;

    // ======== MASSES RATIO AND Tmax ==============
    double me_over_mmu = me / mmu;
    cout<<"masses: " <<  me_over_mmu << endl;

        double Tmax_num = 2 * me * beta * beta * gamma * gamma;

        double Tmax_den = 1 + 2 * gamma * me_over_mmu + me_over_mmu * me_over_mmu;
     double Tmax = Tmax_num / Tmax_den;
    cout<<"T-max: " << Tmax << endl;

    //======== LOGARTIM ARGUMENT ========
     double arg =(2 * me * beta * beta * gamma * gamma * Tmax) / (I * I);
       // if (arg <= 0) arg = 1e-10; // avoid log(0)
    cout<<"argument log: " << arg << endl;
    //======== LOGARITM CALCULUS ========
    double log_term = log(arg);

    //======== BRACKET =====================
     double bracket = 0.5 * log_term - beta * beta;
    cout<<"bracket: " << bracket  << endl;
    // ====== ENERGY LOSS ==================
     double dEdx = K * z * z * Z_over_A *(1/ (beta * beta)) * bracket;
     cout<<"first term: " <<  K * z * z * Z_over_A *(1/ (beta * beta))  << endl;
     double result = dEdx*rho ;

     double two_bars = result*2;
cout << "" << endl;
cout << "dE/dx = " << result << endl;
cout << "for two bars = " << two_bars << endl;
}