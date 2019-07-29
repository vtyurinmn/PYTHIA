// main20.cc is a part of the PYTHIA event generator.
// Copyright (C) 2017 Torbjorn Sjostrand.
// PYTHIA is licenced under the GNU GPL version 2, see COPYING for details.
// Please respect the MCnet Guidelines, see GUIDELINES for details.

// This is a simple test program. It shows how PYTHIA 8 can write
// a Les Houches Event File based on its process-level events.

#include "Pythia8/Pythia.h"
#include <iostream>

using namespace std;
using namespace Pythia8;
//using namespace std::chrono;
int main() {
    

    // Generator.
    Pythia pythia;
    Event& event = pythia.event;
    
    // Read in commands from external file.
    // pythia.readFile("pythia8_Jpsi.cmnd");
    // pythia.readFile("pythia8_Charm.txt");
    pythia.readFile("pythia8_Jpsi_DPS.txt");
    //pythia.readFile("pythia_double_jpsi_nuclear.txt");
    
    pythia.readString("SecondHard:generate = on");
    
    // Switch off generation of steps subsequent to the process level one.
    // (These will not be stored anyway, so only steal time.)
    //pythia.readString("PartonLevel:all = on");
    
    // Create an LHAup object that can access relevant information in pythia.
    LHAupFromPYTHIA8 myLHA(&pythia.process, &pythia.info);
    
    // Open a file on which LHEF events should be stored, and write header.
    myLHA.openLHEF("Double_Jpsi_DPS.lhe");
//    myLHA.openLHEF(filename);
    
    // LHC 8 TeV initialization.
    pythia.init();
    pythia.next();
    
    // Store initialization info in the LHAup object.
    myLHA.setInit();
    
    // Write out this initialization info on the file.
    myLHA.initLHEF();
    
    // Loop over events.
    int counter = 0;

    while (counter < 1000) {
        // Generate an event.
        pythia.next();

        // Store event info in the LHAup object.
        myLHA.setEvent();

        // Write out this event info on the file.
        // With optional argument (verbose =) false the file is smaller.
        //myLHA.eventLHEF();

        if (event[5].id() == 443 && event[9].id() == 443) {
            myLHA.eventLHEF();
            counter++;}

    }
    
//      for (int i = 0; i < 100; ++i) {
//
//          if (i % 500 == 0 ) {cout << "Events have been processed:\t" << i << endl;}
//
//        // Generate an event.
//        pythia.next();
//
//        // Store event info in the LHAup object.
//        myLHA.setEvent();
//
//        // Write out this event info on the file.
//        // With optional argument (verbose =) false the file is smaller.
//        myLHA.eventLHEF();
//
//      }
    
    // Statistics: full printout.
    pythia.stat();
    
    // Update the cross section info based on Monte Carlo integration during run.
    myLHA.updateSigma();
    
    // Write endtag. Overwrite initialization info with new cross sections.
    myLHA.closeLHEF(true);
    
    // Done.
    return 0;
}

