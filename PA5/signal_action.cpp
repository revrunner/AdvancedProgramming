//Dara Diba ddiba@ucsc.edu
//Nirav Agrawal nkagrawa@ucsc.edu

#include <cstring>
#include <string>
#include <unordered_map>
using namespace std;

#include "signal_action.h"

signal_action::signal_action (int signal, void (*handler) (int)) {
   action.sa_handler = handler;
   sigfillset (&action.sa_mask);
   action.sa_flags = 0;
   int rc = sigaction (signal, &action, nullptr);
   if (rc < 0) throw signal_error (signal);
}

vector<string> util::split(const string& line,
  const string& delimiter){
   vector<string> words;
   size_t ending = 0;
   for(;;){
    size_t starting = line.find_first_not_of (delimiter, ending);
   if (starting == string::npos) break;
   ending = line.find_first_of (delimiter, starting);
   words.push_back (line.substr (starting, ending - starting));
  } return words;

}

signal_error::signal_error (int signal):
              runtime_error (string ("signal_error(")
                             + strsignal (signal) + ")"),
              signal(signal) {}

