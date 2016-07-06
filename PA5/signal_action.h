//Dara Diba ddiba@ucsc.edu
//Nirav Agrawal nkagrawa@ucsc.edu

#ifndef __SIGNAL_ACTION_H__
#define __SIGNAL_ACTION_H__

#include <stdexcept>
using namespace std;

#include <signal.h>
#include <vector>
class cix_exit: public exception{};

class signal_action {
   private:
      struct sigaction action;
   public:
      signal_action (int signal, void (*handler) (int));
      vector<string> split (const string& line, const
        string& delim);
};
class util{
    public:
     util() = default;
     vector<string> split (const string& line, const
        string& delim);
}; 

class signal_error: runtime_error {
   public:
      int signal;
      explicit signal_error (int signal);
};

#endif

