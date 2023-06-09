//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file B2/B2a/src/RunAction.cc
/// \brief Implementation of the B2::RunAction class

#include "RunAction.hh"

#include "B2Analysis.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"

namespace B2 {

RunAction::RunAction() {
    // set printing event number per each 100 events
    G4RunManager::GetRunManager()->SetPrintProgress(1000);

    // Create analysis manager
    // The choice of analysis technology is done via selectin of a namespace
    // in B2Analysis.hh
    auto analysisManager = G4AnalysisManager::Instance();
    G4cout << "Using " << analysisManager->GetType() << G4endl;

    // create ntuple
    analysisManager->CreateNtuple("B2", "hit ntuple");
    analysisManager->CreateNtupleIColumn("eventID");
    analysisManager->CreateNtupleIColumn("trackID");
    analysisManager->CreateNtupleIColumn("chamberNb");
    analysisManager->CreateNtupleDColumn("x");
    analysisManager->CreateNtupleDColumn("y");
    analysisManager->CreateNtupleDColumn("z");
    analysisManager->CreateNtupleDColumn("initialMomentum");
    analysisManager->CreateNtupleDColumn("currentMomentum");
    analysisManager->CreateNtupleDColumn("PDGcode");
    analysisManager->CreateNtupleDColumn("px");
    analysisManager->CreateNtupleDColumn("py");
    analysisManager->CreateNtupleDColumn("pz");
    analysisManager->CreateNtupleDColumn("Edep");
    analysisManager->FinishNtuple();

    /*
    /vis/disable
    /run/beamOn 1000
    /vis/enable
    /vis/reviewKeptEvents
  */
}

void RunAction::BeginOfRunAction(const G4Run*) {
    // inform the runManager to save random number seed
    G4RunManager::GetRunManager()->SetRandomNumberStore(false);
    // Get analysis manager
    auto analysisManager = G4AnalysisManager::Instance();

    // Open an output file
    G4String fileName = "B2";
    analysisManager->OpenFile(fileName);
}

void RunAction::EndOfRunAction(const G4Run*) {

    // save histograms & ntuple
    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->Write();
    analysisManager->CloseFile();
}

}  // namespace B2
