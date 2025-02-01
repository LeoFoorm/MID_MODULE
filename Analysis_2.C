
#include <fstream>
#include <string>
#include <iostream>
#include <vector>

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TLegend.h"
#include "TAxis.h"
#include "TH2.h"
#include "TStyle.h"

#include <sstream>
#include <map>
using namespace std;

void Analysis_2()
{
    //muones vs piones en caso con y sin absorber
 
    //abre los archivos
    TFile *file = TFile::Open("Output0.root", "READ"); 
    TFile *file2 = TFile::Open("Mu_No_mil.root", "READ"); 

    TFile *file3 = TFile::Open("Pi_Si_mil.root", "READ"); 
    TFile *file4 = TFile::Open("Pi_No_mil.root", "READ"); 
   
    
    
    TTree *tree = (TTree *)file->Get("Edep");
    TTree *tree2 = (TTree *)file2->Get("Edep");

    TTree *tree3 = (TTree *)file3->Get("Edep");
    TTree *tree4 = (TTree *)file4->Get("Edep");
    
    
    //------ Analisis Muones ----------------------

    //------- FILE 1 SI ABSROBER --------------------------------


    // Variables para almacenar datos
    Double_t particleMomentum = 0.0; 
    int Hit_passing_through_both_bars = 0;
    Double_t angle = 0.0;

    int total_detected_gammas = 0.0 ;

    Double_t total_energy_deposition = 0.0;


    // Vincula las ramas a las variables previamente definidas
    tree->SetBranchAddress("Particle_Momentum_GeV", &particleMomentum);  
    tree->SetBranchAddress("HIT_particle_passed_both_layers", &Hit_passing_through_both_bars);
    tree->SetBranchAddress("angle",&angle);
    tree->SetBranchAddress("Total_Photons_Detected", &total_detected_gammas);

    tree->SetBranchAddress("Total_Energy_Deposition", & total_energy_deposition);


    // Vectores y estructuras para almacenar resultados
    vector<int> momentumCounts(20, 0);                
    vector<int> HitCounts(20, 0);

    vector<int>HitCounts_angle(20,0);
    vector<int> anglesCounts(20,0);

    vector <int>GammaSum(20, 0);  
    vector<double_t> PhotonAverage(20, 0.0);    


    // Recorre los evento
    Long64_t nEntries = tree->GetEntries();


    for (Long64_t i = 0; i < nEntries; ++i) {
    tree->GetEntry(i);
    cout << "Evento " << i << ": Total_Photons_Detected = " << total_detected_gammas << endl;
    }
    cout<< ""<<endl;

    for (Long64_t i = 0; i < nEntries; ++i) {

        tree->GetEntry(i);

        // Identifica el rango del momento
        int momentumRange = static_cast<int>(particleMomentum / 0.5);

        if (momentumRange >= 0 && momentumRange < 20) {
            momentumCounts[momentumRange]++;

            GammaSum[momentumRange] += total_detected_gammas;

        }else {
            continue; 
        }

        if(momentumRange >= 0 && momentumRange <20 && Hit_passing_through_both_bars == 1){
            HitCounts[momentumRange]++;
        }


        int AngleRange = static_cast<int>(angle/0.50625); 
        if(AngleRange >=0 && AngleRange < 20){
            anglesCounts[AngleRange]++;
        }else {continue;}

        if(AngleRange >=0 && AngleRange < 20 && Hit_passing_through_both_bars == 1){
            HitCounts_angle[AngleRange]++;
        }
    }

    
    // Imprime los resultados
    cout<< "\n MUONES CON ABSORBER \n" <<endl;
    cout << "Resultados: Hits por rango de momento y angulo. Cantidad de fotones detectados.\n";

    for (size_t i = 0; i < HitCounts.size(); ++i) {
        
        int HITS = HitCounts[i];
        double_t EFF = ( static_cast<Double_t>(HITS)  /  momentumCounts[i] ) * 100;

        cout << "Rango " << i + 1 << " (" << i * 0.5 << " GeV - " << (i + 1) * 0.5
             << " GeV):     " << HitCounts[i] << " hits,        " << momentumCounts[i] << "  momentos  en el rango. " 
             << "       Eficiencia:     " << EFF << " %. " << endl;
        
    }

cout << "\n"<< endl;
                            //antes era HitCounts.size()
       for (size_t i = 0; i < GammaSum.size(); ++i) {
        if(momentumCounts[i] > 0){
        PhotonAverage[i] = static_cast<double>(GammaSum[i]) / momentumCounts[i];
      
        cout << "Rango " << i + 1  << "  "<< PhotonAverage[i] << " fotones promedio por rango "  << endl;
        } 
    }

    cout << "\n"<< endl;

    vector<Double_t> x_angles;
    vector<Double_t> y_eff_angles;
    for (size_t i = 0; i < HitCounts_angle.size(); ++i){

        Double_t ang = i * 0.50625 + 0.253125;
        x_angles.push_back(ang);

        int HITS_ANGLES = HitCounts_angle[i];
        double EFF_Angle = (static_cast<Double_t>(HITS_ANGLES)  /  anglesCounts[i]) *100;
        y_eff_angles.push_back(EFF_Angle);

        cout << "Rango " << i +1 << " (" << i * 0.50625 << "° - " << (i + 1) * 0.50625 << "°):    " 
             << HitCounts_angle[i] << " hits con angulo dentro del rango,   " << anglesCounts[i] 
             << " particulas con angulos dentro del rango. |  " << EFF_Angle << "%. Eiciencia." << endl;
    }


    //Para generar el grafico de eficiencia. 
    vector<Double_t> xValues;
    vector<Double_t> yValues;

    for (int x = 0; x < 20; ++x){
        Double_t mom = x * 0.5 + 0.25;
        xValues.push_back(mom);
    

        int Hits =  HitCounts[x];
        Double_t efficiency = (static_cast<Double_t>(Hits) / momentumCounts[x]) * 100;
        yValues.push_back(efficiency);
    }

     // -------- Grafico promedio gammas detectadas por SiPMs -----------------------
    
    TCanvas* canva_test = new TCanvas("promedio_gammas_vs_Pt", "Mean value of detected gammas vs Transverse Momentum", 1600, 1200);
    TGraph* gammas_pt = new TGraph(xValues.size(), &xValues[0], &PhotonAverage[0]);
    
    gammas_pt->SetTitle("Mean value of detected gammas vs Transverse Momentum Muones");
    gammas_pt->SetMarkerStyle(20);
    gammas_pt->SetMarkerColor(kAzure); 
    gammas_pt->GetXaxis()->SetTitle("Transverse Momentum [GeV/c]");
  
    gammas_pt->GetYaxis()->SetTitle("Mean gammas detected [gammas]");

    gammas_pt->Draw("AP");
    /*
    NoAbs->SetMarkerStyle(21);
    NoAbs->SetMarkerColor(kBlue);
    
    NoAbs->Draw("P SAME");
    */
  
    TLegend* legend_gammas = new TLegend(0.7, 0.7, 0.9, 0.9);
    legend_gammas->AddEntry(gammas_pt, "SI ABSORBER", "lp");
    //legend_gammas->AddEntry(NoAbs, "NO ABSORBER", "lp");
    legend_gammas->Draw();

    canva_test->SetGrid();
    canva_test->Update();
    

// -------- Grafico Edep y dE/dx totales -----------------------
    
//create histograms
   
    TH1D *Histo_edep_mu_si_abs = new TH1D("Histogram_edep_mu_with_absorber", "Energy Deposition [MeV] vs events ", 90, 0, 5);
    
    Histo_edep_mu_si_abs->SetTitle("TOTAL ENERGY DEPOSITION MUONS WITH ABSORBER");
    Histo_edep_mu_si_abs->SetLineColor(kMagenta); // Line color for histogram
    Histo_edep_mu_si_abs->SetFillColor(kMagenta); // Fill color for bars
    Histo_edep_mu_si_abs->SetFillStyle(3002);
    

    //tree->Draw("Total_Energy_Deposition>>Histo_edep_mu_si_abs");
    //POR QUÉ NO FUNCIONA!?
    
    Long64_t nEntries_for_hist = tree->GetEntries();
    for (Long64_t i = 0; i < nEntries_for_hist; ++i) {
        tree->GetEntry(i);
        if (total_energy_deposition > 0){
        Histo_edep_mu_si_abs->Fill(total_energy_deposition); 
        } 
    }
    
    TCanvas *canvaOverlaping = new TCanvas("canvaOverlaping","Overlaping of the histograms");
    
    Histo_edep_mu_si_abs->GetXaxis()->SetTitle("Entries");
    Histo_edep_mu_si_abs->GetYaxis()->SetTitle("Total Energy deposition");
    
    
   // Histo_edep_mu_si_abs->SetFillColorAlpha(kMagenta, 0.35);  // Fill color with transparency for mu-
    
    Histo_edep_mu_si_abs->Draw("HIST"); 

    
   
    TLegend *legend_histo = new TLegend(0.7, 0.7, 0.9, 0.9);
    legend_histo->AddEntry( Histo_edep_mu_si_abs, "Output_muon_Negative", "f");
    legend_histo->Draw();


    canvaOverlaping->SetGrid();
    canvaOverlaping->Update();



//--------  FILE 2 NO ABSORBER ---------------------------

    Double_t particleMomentum2 = 0.0; 
    int Hit_passing_through_both_bars2 = 0;
    Double_t angle2 = 0.0;


    // Vincula las ramas a las variables previamente definidas
    tree2->SetBranchAddress("Particle_Momentum_GeV", &particleMomentum2);  
    tree2->SetBranchAddress("HIT_particle_passed_both_layers", &Hit_passing_through_both_bars2);  
    tree2->SetBranchAddress("angle",&angle2);

    // Vectores y estructuras para almacenar resultados
    vector<int> momentumCounts2(20, 0); 
    vector<int> HitCounts2(20, 0);

    vector<int>HitCounts_angle2(20,0);
    vector<int> anglesCounts2(20,0);


    // Recorre los evento
    Long64_t nEntries2 = tree2->GetEntries();

    for (Long64_t j = 0; j < nEntries2; ++j) {

        tree2->GetEntry(j);

        // Identifica el rango del momento
        int momentumRange2 = static_cast<int>(particleMomentum2 / 0.5);
        if (momentumRange2 >= 0 && momentumRange2 < 20) {
            momentumCounts2[momentumRange2]++;
        }else {continue; }

        if(momentumRange2 >= 0 && momentumRange2 <20 && Hit_passing_through_both_bars2 == 1){
            HitCounts2[momentumRange2]++;
        }


        int AngleRange2 = static_cast<int>(angle2/0.50625); 
        if(AngleRange2 >=0 && AngleRange2 < 20){
            anglesCounts2[AngleRange2]++;
        }else {continue;}

        if(AngleRange2 >=0 && AngleRange2 < 20 && Hit_passing_through_both_bars2 == 1){
            HitCounts_angle2[AngleRange2]++;
        }
    }

    
    // Imprime los resultados
    cout<< "\n MUONES SIN ABSORBER\n" <<endl;
    cout << "\n Resultados (2): Hits por rango de momento\n";

    for (size_t j = 0; j < HitCounts2.size(); ++j) {
        int HITS2 = HitCounts2[j];
        double_t EFF2 = ( static_cast<Double_t>(HITS2)  /  momentumCounts2[j] ) * 100;

        cout << "Rango " << j + 1 << " (" <<j * 0.5 << " GeV - " << (j + 1) * 0.5
             << " GeV):     " << HitCounts2[j] << " hits,       " << momentumCounts2[j] << "  momentos  en el rango."
            << "       Eficiencia:      " << EFF2 << " %. " << endl;
    }


    cout << "\n";

    vector<Double_t> x_angles2;
    vector<Double_t> y_eff_angles2;

    for (size_t i = 0; i < HitCounts_angle2.size(); ++i){

        Double_t ang2 = (i * 0.50625) + 0.253125;
        x_angles2.push_back(ang2);

        int HITS_ANGLES2 = HitCounts_angle2[i];
        double EFF_Angle2 = (static_cast<Double_t>(HITS_ANGLES2)  /  anglesCounts2[i]) *100;
        y_eff_angles2.push_back(EFF_Angle2);

        cout << "Rango " << i +1 << " (" << i * 0.50625 << "° - " << (i + 1) * 0.50625 << "°):    " 
             << HitCounts_angle2[i] << " hits con angulo dentro del rango,   " << anglesCounts2[i] 
             << " particulas con angulos dentro del rango. |  " << EFF_Angle2 << "%. Eiciencia." << endl;
    }


    //Para generar el grafico de eficiencia. 
    vector<Double_t> xValues2;
    vector<Double_t> yValues2;

    for (int x = 0; x < 20; ++x){
        Double_t mom = x * 0.5 + 0.25;
        xValues2.push_back(mom);
    

        int Hits2 =  HitCounts2[x];
        Double_t efficiency2 = (static_cast<Double_t>(Hits2) / momentumCounts2[x]) * 100;
        yValues2.push_back(efficiency2);
    }


    // -------- Grafico -----------------------

    TCanvas* canvas = new TCanvas("Efficiency", "Efficiency vs Transverse Momentum", 1600, 1200);
    TGraph* SiAbs = new TGraph(xValues.size(), &xValues[0], &yValues[0]);
    TGraph* NoAbs = new TGraph(xValues2.size(), &xValues2[0], &yValues2[0]);
    SiAbs->SetTitle("Efficiency vs Transverse Momentum Muones");
    SiAbs->SetMarkerStyle(20);
    SiAbs->SetMarkerColor(kRed); 
    SiAbs->GetXaxis()->SetTitle("Transverse Momentum [GeV/c]");
  
    SiAbs->GetYaxis()->SetTitle("Efficiency [%]");

    SiAbs->Draw("AP");

    NoAbs->SetMarkerStyle(21);
    NoAbs->SetMarkerColor(kBlue);
    
    NoAbs->Draw("P SAME");

    // Añadir leyenda
    TLegend* legend = new TLegend(0.7, 0.7, 0.9, 0.9);
    legend->AddEntry(SiAbs, "SI ABSORBER", "lp");
    legend->AddEntry(NoAbs, "NO ABSORBER", "lp");
    legend->Draw();

    canvas->SetGrid();
    canvas->Update();

//...........................

    TCanvas* canva_ang_si_abs = new TCanvas("Efficiency with angles", "Efficiency vs incident angle", 1600, 1200);
    TGraph* SiAbs_ang = new TGraph(x_angles.size(), &x_angles[0], &y_eff_angles[0]);
    TGraph* NoAbs_ang = new TGraph(x_angles2.size(), &x_angles2[0], &y_eff_angles2[0]);
    SiAbs_ang->SetTitle("Efficiency vs  incident angle");
    SiAbs_ang->SetMarkerStyle(20);
    SiAbs_ang->SetMarkerColor(kMagenta); 
    SiAbs_ang->GetXaxis()->SetTitle("Angles ");
  
    SiAbs_ang->GetYaxis()->SetTitle("Efficiency [%]");

    SiAbs_ang->Draw("AP");

    NoAbs_ang->SetMarkerStyle(21);
    NoAbs_ang->SetMarkerColor(kCyan);
    
    NoAbs_ang->Draw("P SAME");

    // Añadir leyenda
    TLegend* legend_ang = new TLegend(0.7, 0.7, 0.9, 0.9);
    legend_ang->AddEntry(SiAbs_ang, "SI ABSORBER", "lp");
    legend_ang->AddEntry(NoAbs_ang, "NO ABSORBER", "lp");
    legend_ang->Draw();

    canva_ang_si_abs->SetGrid();
    canva_ang_si_abs->Update();



 //------ ANALYSIS  PIONES --------------

 //------- FILE 3 SI ABSROBER --------------------------------


    // Variables para almacenar datos
    Double_t particleMomentum3 = 0.0; 
    int Hit_passing_through_both_bars3 = 0;
    Double_t angle3 = 0.0;
    

    // Vincula las ramas a las variables previamente definidas
    tree3->SetBranchAddress("Particle_Momentum_GeV", &particleMomentum3);  
    tree3->SetBranchAddress("HIT_particle_passed_both_layers", &Hit_passing_through_both_bars3);
    tree3->SetBranchAddress("angle" ,&angle3);
        

    // Vectores y estructuras para almacenar resultados
    vector<int> momentumCounts3(20, 0); 
    vector<int> HitCounts3(20, 0);

    vector<int>HitCounts_angle3(20,0);
    vector<int> anglesCounts3(20,0);


    // Recorre los evento
    Long64_t nEntries3 = tree3->GetEntries();

    for (Long64_t i = 0; i < nEntries3; ++i) {
        tree3->GetEntry(i);

        // Identifica el rango del momento
        int momentumRange3 = static_cast<int>(particleMomentum3 / 0.5);
        if (momentumRange3 >= 0 && momentumRange3 < 20) {
            momentumCounts3[momentumRange3]++;
        }else {continue;}

        if(momentumRange3 >= 0 && momentumRange3 <20 && Hit_passing_through_both_bars3 == 1){
            HitCounts3[momentumRange3]++;
        }


        int AngleRange3 = static_cast<int>(angle3/0.50625); 
        if(AngleRange3 >=0 && AngleRange3 < 20){
            anglesCounts3[AngleRange3]++;
        }else {continue;}

        if(AngleRange3 >=0 && AngleRange3 < 20 && Hit_passing_through_both_bars3 == 1){
            HitCounts_angle3[AngleRange3]++;
        }
    }

    
    // Imprime los resultados
       cout<< "\n PIONES CON ABSORBER\n" <<endl;
    cout << " \n Resultados (3): Hits por rango de momento\n";
    
    for (size_t i = 0; i < HitCounts3.size(); ++i) {

        int HITS3 = HitCounts3[i];
        double_t EFF3 = ( static_cast<Double_t>(HITS3)  /  momentumCounts3[i] ) * 100;

        cout << "Rango " << i + 1 << " (" << i * 0.5 << " GeV - " << (i + 1) * 0.5
             << " GeV):     " << HitCounts3[i] << " hits,        " << momentumCounts3[i] << "  momentos  en el rango. " 
             << "       Eficiencia:     " << EFF3 << " %. " << endl;

        //cout << "Rango " << i + 1 << " (" << i * 0.5 << " GeV - " << (i + 1) * 0.5
            // << " GeV): " << HitCounts3[i] << " hits, " << momentumCounts3[i] << "  momentos  en el rango.\n";
    }


    cout << "\n";

    vector<Double_t> x_angles3;
    vector<Double_t> y_eff_angles3;

    for (size_t i = 0; i < HitCounts_angle3.size(); ++i){

        Double_t ang3 = (i * 0.50625) + 0.253125;
        x_angles3.push_back(ang3);

        int HITS_ANGLES3 = HitCounts_angle3[i];
        double EFF_Angle3 = (static_cast<Double_t>(HITS_ANGLES3)  /  anglesCounts3[i]) *100;
        y_eff_angles3.push_back(EFF_Angle3);

        cout << "Rango " << i +1 << " (" << i * 0.50625 << "° - " << (i + 1) * 0.50625 << "°):    " 
             << HitCounts_angle3[i] << " hits con angulo dentro del rango,   " << anglesCounts3[i] 
             << " particulas con angulos dentro del rango. |  " << EFF_Angle3 << "%. Eiciencia." << endl;
    }

        for (size_t i = 0; i < HitCounts_angle3.size(); ++i){

        Double_t ang3 = (i * 0.50625) + 0.253125;
        x_angles3.push_back(ang3);

        int HITS_ANGLES3 = HitCounts_angle3[i];
        double EFF_Angle3 = (static_cast<Double_t>(HITS_ANGLES3)  /  anglesCounts3[i]) *100;
        y_eff_angles3.push_back(EFF_Angle3);

        cout <<  " (" << (i + 1) * 0.50625 << ",   " 
           << EFF_Angle3 << "%)" << endl;
    }


    //Para generar el grafico de eficiencia. 
    vector<Double_t> xValues3;
    vector<Double_t> yValues3;

    for (int x = 0; x < 20; ++x){
        Double_t mom = x * 0.5 + 0.25;
        xValues3.push_back(mom);
    

        int Hits3 =  HitCounts3[x];
        Double_t efficiency3 = (static_cast<Double_t>(Hits3) / momentumCounts3[x]) * 100;
        yValues3.push_back(efficiency3);
    }


//--------  FILE 4 NO ABSORBER ---------------------------

    
    Double_t particleMomentum4 = 0.0; 
    int Hit_passing_through_both_bars4 = 0;
    Double_t angle4 = 0.0;



    // Vincula las ramas a las variables previamente definidas
    tree4->SetBranchAddress("Particle_Momentum_GeV", &particleMomentum4);  
    tree4->SetBranchAddress("HIT_particle_passed_both_layers", &Hit_passing_through_both_bars4); 
    tree4->SetBranchAddress("angle", &angle4);   


    // Vectores y estructuras para almacenar resultados
    vector<int> momentumCounts4(20, 0); 
    vector<int> HitCounts4(20, 0);

    vector<int>HitCounts_angle4(20,0);
    vector<int> anglesCounts4(20,0);


    // Recorre los evento
    Long64_t nEntries4 = tree4->GetEntries();

    for (Long64_t j = 0; j < nEntries4; ++j) {
        tree4->GetEntry(j);

        // Identifica el rango del momento
        int momentumRange4 = static_cast<int>(particleMomentum4 / 0.5);
        if (momentumRange4 >= 0 && momentumRange4 < 20) {
            momentumCounts4[momentumRange4]++;
        }else { continue;}

        if(momentumRange4 >= 0 && momentumRange4 <20 && Hit_passing_through_both_bars4 == 1){
            HitCounts4[momentumRange4]++;
        }


        int AngleRange4 = static_cast<int>(angle4/0.50625); 
        if(AngleRange4 >=0 && AngleRange4 < 20){
            anglesCounts4[AngleRange4]++;
        }else {continue;}

        if(AngleRange4 >=0 && AngleRange4 < 20 && Hit_passing_through_both_bars4 == 1){
            HitCounts_angle4[AngleRange4]++;
        }
    }

    
    // Imprime los resultados
    cout<< "\n PIONES SIN ABSORBER\n" <<endl;
    cout << "\n Resultados (4): Hits por rango de momento\n";

    for (size_t j = 0; j < HitCounts4.size(); ++j) {

        int HITS4 = HitCounts4[j];
        double_t EFF4 = ( static_cast<Double_t>(HITS4)  /  momentumCounts4[j] ) * 100;

        cout << "Rango " << j + 1 << " (" << j * 0.5 << " GeV - " << (j + 1) * 0.5
             << " GeV):     " << HitCounts4[j] << " hits,        " << momentumCounts4[j] << "  momentos  en el rango. " 
             << "       Eficiencia:     " << EFF4 << " %. " << endl;

        //cout << "Rango " << j + 1 << " (" <<j * 0.5 << " GeV - " << (j + 1) * 0.5
          //   << " GeV): " << HitCounts4[j] << " hits, " << momentumCounts4[j] << "  momentos  en el rango.\n";
    }


    cout << "\n";

    vector<Double_t> x_angles4;
    vector<Double_t> y_eff_angles4;

    for (size_t i = 0; i < HitCounts_angle4.size(); ++i){

        Double_t ang4 = (i * 0.50625) + 0.253125;
        x_angles4.push_back(ang4);

        int HITS_ANGLES4 = HitCounts_angle4[i];
        double EFF_Angle4 = (static_cast<Double_t>(HITS_ANGLES4)  /  anglesCounts4[i]) *100;
        y_eff_angles4.push_back(EFF_Angle4);

        cout << "Rango " << i +1 << " (" << i * 0.50625 << "° - " << (i + 1) * 0.50625 << "°):    " 
             << HitCounts_angle4[i] << " hits con angulo dentro del rango,   " << anglesCounts4[i] 
             << " particulas con angulos dentro del rango. |  " << EFF_Angle4 << "%. Eiciencia." << endl;
    }

    for (size_t i = 0; i < HitCounts_angle4.size(); ++i){

        Double_t ang4 = (i * 0.50625) + 0.253125;
        x_angles4.push_back(ang4);

        int HITS_ANGLES4 = HitCounts_angle4[i];
        double EFF_Angle4 = (static_cast<Double_t>(HITS_ANGLES4)  /  anglesCounts4[i]) *100;
        y_eff_angles4.push_back(EFF_Angle4);

        cout <<  " (" << (i + 1) * 0.50625 << ",   " 
           << EFF_Angle4 << "%)" << endl;
    }


    //Para generar el grafico de eficiencia. 
    vector<Double_t> xValues4;
    vector<Double_t> yValues4;

    for (int x = 0; x < 20; ++x){
        Double_t mom = x * 0.5 + 0.25;
        xValues4.push_back(mom);
    

        int Hits4 =  HitCounts4[x];
        Double_t efficiency4 = (static_cast<Double_t>(Hits4) / momentumCounts4[x]) * 100;
        yValues4.push_back(efficiency4);
    }


//-------- Para que aparezcan todos los puntos --------------
    double_t xMin = min(*min_element(xValues3.begin(), xValues3.end()), *min_element(xValues4.begin(), xValues4.end()));
    double_t xMax = max(*max_element(xValues3.begin(), xValues3.end()), *max_element(xValues4.begin(), xValues4.end()));

    double_t yMin = min(*min_element(yValues3.begin(), yValues3.end()), *min_element(yValues4.begin(), yValues4.end()));
    double_t yMax = max(*max_element(yValues3.begin(), yValues3.end()), *max_element(yValues4.begin(), yValues4.end()));

    xMin -= 0.1 * (xMax - xMin);
    xMax += 0.1 * (xMax - xMin);

    yMin -= 0.1 * (yMax - yMin);
    yMax += 0.1 * (yMax - yMin);
    //----------------------------------------------------------


    // -------- grafico --------------------

    TCanvas* canvas2 = new TCanvas("Efficiency_2", "Efficiency vs Transverse Momentum", 1600, 1200);
    TGraph* NoAbs_pi = new TGraph(xValues4.size(), &xValues4[0], &yValues4[0]); 
    TGraph* SiAbs_pi = new TGraph(xValues3.size(), &xValues3[0], &yValues3[0]);



    NoAbs_pi->SetTitle("Efficiency vs Transverse Momentum Piones TEST");
    NoAbs_pi->SetMarkerStyle(20);
    NoAbs_pi->SetMarkerColor(kGreen); 
    NoAbs_pi->GetXaxis()->SetTitle("Transverse Momentum [GeV/c]");
    NoAbs_pi->GetXaxis()->SetLimits(xMin, xMax);
    NoAbs_pi->GetYaxis()->SetTitle("Efficiency [%]");
    NoAbs_pi->GetYaxis()->SetLimits(yMin, yMax);
    NoAbs_pi->Draw("AP");

    SiAbs_pi->SetMarkerStyle(21);
    SiAbs_pi->SetMarkerColor(kOrange);
    
    SiAbs_pi->Draw("P SAME");

    TLegend* legend2 = new TLegend(0.7, 0.7, 0.9, 0.9);
    legend2->AddEntry(SiAbs_pi, "SI ABSORBER", "lp");
    legend2->AddEntry(NoAbs_pi, "NO ABSORBER", "lp");
    legend2->Draw();

    canvas2->SetGrid();
    canvas2->Update();

    //...........................

    // Calcular el rango de los ejes
Double_t xMinang = std::min(*std::min_element(x_angles3.begin(), x_angles3.end()),
                         *std::min_element(x_angles4.begin(), x_angles4.end()));
Double_t xMaxang = std::max(*std::max_element(x_angles3.begin(), x_angles3.end()),
                         *std::max_element(x_angles4.begin(), x_angles4.end()));
Double_t yMinang = std::min(*std::min_element(y_eff_angles3.begin(), y_eff_angles3.end()),
                         *std::min_element(y_eff_angles4.begin(), y_eff_angles4.end()));
Double_t yMaxang = std::max(*std::max_element(y_eff_angles3.begin(), y_eff_angles3.end()),
                         *std::max_element(y_eff_angles4.begin(), y_eff_angles4.end()));

// Añadir márgenes para mejor visualización
xMinang -= 0.1 * (xMaxang - xMinang);
xMaxang += 0.1 * (xMaxang - xMinang);
yMinang -= 0.1 * (yMaxang - yMinang);
yMaxang += 0.1 * (yMaxang - yMinang);



    TCanvas* canva_ang_si_abs_pi = new TCanvas("Efficiency with angles 2", "Efficiency vs incident angle", 1600, 1200);
    TGraph* SiAbs_ang_pi = new TGraph(x_angles3.size(), &x_angles3[0], &y_eff_angles3[0]);
    TGraph* NoAbs_ang_pi = new TGraph(x_angles4.size(), &x_angles4[0], &y_eff_angles4[0]);

    // Configurar el rango de los ejes manualmente
    NoAbs_ang_pi->GetXaxis()->SetLimits(xMinang, xMaxang);
    NoAbs_ang_pi->SetMinimum(yMinang);
    NoAbs_ang_pi->SetMaximum(yMaxang);

    NoAbs_ang_pi->SetTitle("Efficiency vs  incident angle");
    NoAbs_ang_pi->SetMarkerStyle(20);
    NoAbs_ang_pi->SetMarkerColor(kViolet); 
    NoAbs_ang_pi->GetXaxis()->SetTitle("Angles ");
    NoAbs_ang_pi->GetYaxis()->SetTitle("Efficiency [%]");
    NoAbs_ang_pi->Draw("AP");

    SiAbs_ang_pi->SetMarkerStyle(21);
    SiAbs_ang_pi->SetMarkerColor(kSpring);
    SiAbs_ang_pi->Draw("P SAME");

    // Añadir leyenda
    TLegend* legend_ang_pi = new TLegend(0.7, 0.7, 0.9, 0.9);
    legend_ang_pi->AddEntry(SiAbs_ang_pi, "SI ABSORBER", "lp");
    legend_ang_pi->AddEntry(NoAbs_ang_pi, "NO ABSORBER", "lp");
    legend_ang_pi->Draw();

    canva_ang_si_abs_pi->SetGrid();
    canva_ang_si_abs_pi->Update();


//------------------------------------------------------------------
//                 HISTOGRAMS OF DEPOSITED ENERGY
/*
//create histograms
    TH1D *Histo_mu_siabs = new TH1D("Histogram total energy for muons with abosrber", "Energy Deposition [MeV] vs events ",300 , 0, 45);
    Histo_mu_n->SetLineColor(kMagenta);
    Histo_mu_n->SetFillColor(kMagenta); 
    Histo_mu_n->SetFillStyle(3002); 

    TH1D *Histo_mu_noabs = new TH1D("Histogram total energy for muons without abosrber", "Energy Deposition [MeV] vs events from mu+", 300, 0, 45);
    Histo_mu_p->SetLineColor(kCyan);
    Histo_mu_p->SetFillColor(kCyan);
    Histo_mu_p->SetFillStyle(3003); 

    TH1D *Histo_pion-siabs = new TH1D("Histogram total energy for pions with abosrber", "Energy Deposition [MeV] vs events from pion", 300, 0, 45);
    Histo_pion->SetLineColor(kYellow);
    Histo_pion->SetFillColor(kYellow);
    Histo_pion->SetFillStyle(3004); 

    TH1D *Histo_pion-siabs = new TH1D("Histogram total energy for pions witouth abosrber", "Energy Deposition [MeV] vs events from pion", 300, 0, 45);
    Histo_pion->SetLineColor(kSpring);
    Histo_pion->SetFillColor(kSpring);
    Histo_pion->SetFillStyle(3005); 

    //Filling the histogram 
    Emu_n->Draw("Energy_Deposition>>Histo_mu_n");
    Emu_p->Draw("Energy_Deposition>>Histo_mu_p");
    Epion->Draw("Energy_Deposition>>Histo_pion");

    Histo_mu_n->SetFillColorAlpha(kMagenta, 0.35);  // Fill color with transparency for mu-
    Histo_mu_p->SetFillColorAlpha(kCyan, 0.35);   // Fill color with transparency for mu+
    Histo_pion->SetFillColorAlpha(kYellow, 0.35); // Fill color with transparency for pion


    //Draw the histograms
    TCanvas *canvaOverlaping = new TCanvas("canvaOverlaping","Overlaping of the histograms");

    //set colors for every histo
    //Histo_mu_n->SetLineColor(kBlue); 
    //Histo_mu_p->SetLineColor(kRed); 
    //Histo_pion->SetLineColor(kGreen);

    //Draw each histogram
    Histo_mu_n->Draw("HIST"); 
    Histo_mu_p->Draw("HIST SAME"); 
    Histo_pion->Draw("HIST SAME");

    TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9);
    legend->AddEntry(Histo_mu_n, "Output_muon_Negative", "f");
    legend->AddEntry(Histo_mu_p, "Output_muon_Positive", "f");
    legend->AddEntry(Histo_pion, "Output_Pion", "f");
    legend->Draw();

    //update the canvas to show the plots
    canvaOverlaping->Update();
    */
    


}


