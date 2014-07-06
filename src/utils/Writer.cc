// Writer.cc

#include <sstream>

#include "Writer.h"

using std::string;


Writer::Writer()
{
    simlog.open("sim.log");
}

Writer::~Writer()
{
    simlog.close();
}

static const string comma(", ");
static const string quote("\"");

string
_fmt(const string v)
{
    // string quote = string("\"");
    string result = quote + v + quote;
    return result;
}

void
Writer::putmsg(const float tstamp, const string entity, const string catg, const string msg)
{
    std::ostringstream result;
    result << tstamp << comma << _fmt(entity) << comma << _fmt(catg);
    result << comma << _fmt(msg);
    simlog << result.str() << std::endl;
}

void
Writer::putFloatHeads(vector<string> heads)
{
    std::ostringstream result;
    for (unsigned int i=0; i < heads.size(); ++i) {
        result << comma << heads[i];   // strings
    }
    simlog << result.str() << std::endl;
}

void
Writer::putFloatValues(vector<float> values)
{
    std::ostringstream result;
    for (unsigned int i=0; i < values.size(); ++i) {
        result << comma << values[i];   // floats
    }
    simlog << result.str() << std::endl;
}

void
Writer::initLine(const float tstamp, const string entity, const string catg)
{
    std::ostringstream result;
    result << tstamp << comma << _fmt(entity) << comma << _fmt(catg);
    simlog << result.str();
}

void
Writer::putCart3Head(const string s, const string sx, const string sy, const string sz)
{
    std::ostringstream result;
    result << comma << s+sx << comma << s+sy << comma << s+sz;
    simlog << result.str();
}

void
Writer::putCart3fLine(cart3::Cart3f v)
{
    std::ostringstream result;
    result << comma << v[0] << comma << v[1] << comma << v[2];
    simlog << result.str();
}

void
Writer::finiLine()
{
    simlog << std::endl;
    simlog.flush();
}

