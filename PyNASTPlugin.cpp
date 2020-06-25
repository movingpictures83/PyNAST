#include "PluginManager.h"
#include <stdio.h>
#include <stdlib.h>
#include "PyNASTPlugin.h"

void PyNASTPlugin::input(std::string file) {
 inputfile = file;
 std::ifstream ifile(inputfile.c_str(), std::ios::in);
 while (!ifile.eof()) {
   std::string key, value;
   ifile >> key;
   ifile >> value;
   parameters[key] = value;
   }
 }
 
void PyNASTPlugin::run() {
}

void PyNASTPlugin::output(std::string file) {
std::string command = "export OLDPATH=${PYTHONPATH}; export PYTHONPATH=${PYTHON2_DIST_PACKAGES}:${PYTHON2_SITE_PACKAGES}:${PYTHONPATH};";
//align_seqs.py -i HMP_MOCK.v35.fasta -m muscle -o output
command += "align_seqs.py -i "+inputfile+" -o "+file+"; cp "+file+"/*_aligned.fasta "+PluginManager::prefix();
command += "; export PYTHONPATH=OLDPATH" ;
 system(command.c_str());
}

PluginProxy<PyNASTPlugin> PyNASTPluginProxy = PluginProxy<PyNASTPlugin>("PyNAST", PluginManager::getInstance());
