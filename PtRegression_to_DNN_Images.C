#include <iostream>
#include <iomanip>
using namespace std;
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TF1.h"
#include "TAttFill.h"
#include "TCanvas.h"
#include <vector>
#include "stdio.h"
#include <stdlib.h>
#include "math.h"
#include "TMath.h"
#include "TGraph.h"
#include "TLegend.h"
#include "TPaveStats.h"
#include "TStyle.h"
#include "THStack.h"
#include "TFitResultPtr.h"
#include <fstream>

void PtRegression_to_DNN_Images()
{
    //TString MODE[11]={"15","14","13","11","7","12","10","9","6","5","3"};
    //Double_t mode[11]={15,  14,  13,  11,  7,  12,  10,  9,  6,  5,  3};
    
    TString MODE[1]={"15"};
    Double_t mode[1] = {15};
    int MODES;//number of modes
    MODES = sizeof(MODE) / sizeof(TString);


 //loop through all modes
 // for (int i=0;i<MODES;i++){        
	TString fileName="/storage1/users/jtr6/EMTF_ML_training_results/PtRegression_Apr_2017_06_05_invPtTarg_invPtWgt_MODE_" + MODE[0] + "_bitCompr_noRPC.root";
	TString directoryName="f_MODE_"+ MODE[0]+ "_15_invPtTarg_invPtWgt_bitCompr_noRPC/TrainTree";
	TFile* myFile = new TFile(fileName);
	TTree* myTree = (TTree*) myFile->Get(directoryName);

	Float_t GEN_pt;
    Float_t EMTF_mode;
    Float_t TRK_mode;
	Float_t dPhi_12;
	Float_t dPhi_23;
	Float_t dPhi_34;
	Float_t dPhi_14;
	Float_t dPhi_13;
	Float_t dPhi_24;
	Float_t dTh_14;
	Float_t theta;
	Float_t GEN_eta;

	myTree->SetBranchAddress("GEN_pt",&GEN_pt);//GEN pT
    myTree->SetBranchAddress("EMTF_mode",&EMTF_mode);
    myTree->SetBranchAddress("TRK_mode",&TRK_mode);
	myTree->SetBranchAddress("dPhi_12",&dPhi_12);
	myTree->SetBranchAddress("dPhi_23",&dPhi_23);
	myTree->SetBranchAddress("dPhi_34",&dPhi_34);
	myTree->SetBranchAddress("dPhi_13",&dPhi_13);
	myTree->SetBranchAddress("dPhi_14",&dPhi_14);
	myTree->SetBranchAddress("dPhi_24",&dPhi_24);
	myTree->SetBranchAddress("dTh_14",&dTh_14);
	myTree->SetBranchAddress("theta",&theta);
	myTree->SetBranchAddress("GEN_eta",&GEN_eta);

    ofstream output("dPhi_14_mats.txt");
    
	Long64_t numEvents = myTree->GetEntries();//read the number of entries in myTree
    cout<<">>>>>>>>>>>>>>>>>>>>>"<<endl;
    cout<<numEvents<<" events to process..."<<endl;

	// loop over all events
	for(Long64_t iEntry = 0; iEntry <numEvents; iEntry++){
        //load the i-th event
		myTree->GetEntry(iEntry);
		
		int array[5][5] = {0};
		int col;		
		int row;	

		if(dPhi_14 < 0){
			col = 0;
		} else if (dPhi_14 >= 0 && dPhi_14 <10){
			col = 1;
		} else if (dPhi_14 >= 10 && dPhi_14 <20){
			col = 2;
		} else if (dPhi_14 >= 20 && dPhi_14 <50){
			col = 3;
		} else{
			col = 4;
		}
		
		if(dTh_14 < 0.5){
			row = 0;
		} else if (dTh_14 >=0.5 && dTh_14 < 1.5){
			row = 1;
		} else if (dTh_14 >= 1.5 && dTh_14 < 2.5){
			row = 2;
		} else if (dTh_14 >= 2.5 && dTh_14 < 3.5){
			row = 3;
		} else {
			row = 4;
		}

		array[row][col] = 5;	
		
		for (int i=0; i<5; i++){
	 	   for(int j=0; j<5; j++){
			output <<array[i][j]<< " ";
		   }
		   output << "\n";
		}
		output << endl;
	}//end loop over events
cout << "Done looping over files" << endl;
}//end pT Regression analysis
