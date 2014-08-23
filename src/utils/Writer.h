// ================================================================
//  class Writer
/*  Output writer for vehicle and trajectory state
 *  Currently writes in CSV style.
 */
// ================================================================

#ifndef _Writer_h_
#define _Writer_h_

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "math/Cart3f.h"

using std::string;
using std::vector;


// ==== Data description ====

struct DatumDesc {      // datum descriptor
    string name;
    string format;
    int nElems;
};

struct DataLineDesc {   // data line descriptor
    string name;        // data line short name
    string desc;        // one-line description
    vector<DatumDesc>   datalist;
    // add function reader-converter ??
};

// ==== CSV headers and values ====

struct CSVHeaders {
  public:
    string tstamp;
    string statename;
    vector <string> headers;
};

struct CSVData {
  public:
    string tstamp;
    string statename;
    vector <string> values;
};

// ==== manipulators ====

class Writer {
  private:
      std::ofstream simlog;    // simulation log -- sequence of CSV lines

  public:
    // data
    CSVHeaders headers;
    DataLineDesc datadesc;

    CSVData values;

  public:
    Writer(const char* logname="sim.log");
    ~Writer();
    // message lines start with time stamp, entity name, and data category
    void putmsg(const float tstamp, const string entity, const string catg, const string msg);
    void putFloatHeads(vector<string>);
    void putFloatValues(vector<float>);
    void initLine(const float tstamp, const string entity, const string catg);
    void putCart3Head(const string s, const string sx, const string sy, const string sz);
    void putCart3fLine(cart3::Cart3f v);
    void finiLine();
};



#endif // _Writer_h_
