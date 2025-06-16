#include <TCanvas.h>
#include <TGraph2D.h>
#include <TGraph.h>
#include <TAxis.h>
#include <TLegend.h>
#include <TPad.h>
#include <TMath.h>

void curvature_radius() {
    // Create main canvas and divide it
    TCanvas *c1 = new TCanvas("Curvature Radius", "Curvature Radius Plots", 1200, 800);
   
  
  const int nPoints = 50;
    double pT[nPoints];       // Transverse momentum (GeV/c)
    double B[nPoints];        // Magnetic field (Tesla
    double radius[nPoints];
    
    // Fill the pT array (0 to 2.5 GeV/c)
    for (int i = 0; i < nPoints; i++) {
        pT[i] = 2.5 * i / (nPoints - 1);
    }
    
    // Create multi-graph to hold all curves
    TMultiGraph *mg = new TMultiGraph();
    mg->SetTitle("Transverse Momentum vs Radius;p_{T} [GeV/c];Radius [m]");
    
    // Magnetic field values and corresponding colors
    double B_values[4] = {0.5, 1.0, 1.5, 2.0}; // Tesla
    int colors[4] = {kRed, kBlue, kGreen+2, kViolet};
    
    

    for(int j = 0; j < 4; j++){
        
        TGraph *g = new TGraph();
        g->SetLineColor(colors[j]);
        g->SetLineWidth(2);
        
        for (int i = 0; i < nPoints; i++) {
            
            double  radius= pT[i] / (0.2998 * B_values[j]);
            g->SetPoint(i, pT[i], radius);
        }
    mg->Add(g);
    } 

    mg->Draw("AL");

    TLegend *leg = new TLegend(0.7, 0.7, 0.9, 0.9);
    leg->SetHeader("Magnetic Field", "C");  // Added legend header
        for (int i = 0; i < 4; i++) {
        leg->AddEntry(mg->GetListOfGraphs()->At(i), Form("%.1f T", B_values[i]), "l");
    }
    leg->Draw();
    
    c1->SetGrid();
    // Update the canvas
    c1->Update();
    //c1->Print("curvature.png");

//=============================== BETHE-BLOCH CURVE ======================================

const int N = 10000;
    double p_min = 0.1; // GeV/c
    double p_max = 3;  // GeV/c
    double step = (p_max - p_min) / N;

    // Physical constants
    const double K = 0.307075; // MeV·cm^2/mol
    const double z = 1.0;   // muon charge
    const double Z_over_A = 0.54141; // BC-404 plastic
    const double I = 6.47e-5; // MeV
    const double me = 0.510998918;  // MeV
    const double mmu = 105.6583745; // MeV
    const double rho = 1.032; // g/cm^3

    // Arrays for graph
    double x[N], y[N];

    for (int i = 0; i < N; i++) {
        double p = p_min + i * step; // GeV/c
        double p_mev = p * 1000.0;   // MeV/c

        double E = sqrt(p_mev * p_mev + mmu * mmu); // total energy in MeV
        double beta = p_mev / E;
        double gamma = E / (mmu);

        double me_over_mmu = me / mmu;
        double Tmax_num = 2 * me * beta * beta * gamma * gamma;
        double Tmax_den = 1 + 2 * gamma * me_over_mmu + me_over_mmu * me_over_mmu;
        double Tmax = Tmax_num / Tmax_den;

        // Avoid log of zero or negative
        double arg = 2 * me * beta * beta * gamma * gamma * Tmax / (I * I);
        if (arg <= 0) arg = 1e-10; // avoid log(0)

        double log_term = log(arg);
        double bracket = 0.5 * log_term - beta * beta;
        double dEdx = K * z * z * Z_over_A / (beta * beta) * bracket;

        // Multiply by density to get MeV/cm
        dEdx *= rho;
        dEdx = dEdx*2;

        x[i] = p;
        y[i] = dEdx;
    }

    TGraph* graph = new TGraph(N, x, y);
    graph->SetTitle("Muon Energy Loss in BC-404;Momentum [GeV/c];dE/dx [MeV/cm]");
    graph->SetLineColor(kBlue);
    graph->SetLineWidth(2);
    graph->Draw("AL");
}