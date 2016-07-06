//
//PA3
//Dara Diba ddiba
//NiravAgrawal nkagrawa
//

#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>
#include <unistd.h>
#include <fstream>

using namespace std;

#include "listmap.h"
#include "xpair.h"
#include "util.h"

typedef xpair<string,string> str_str_pair;
typedef listmap<string,string> str_str_map;


void scan_options (int argc, char** argv) {

   opterr = 0;
   for (;;) {
      int option = getopt (argc, argv, "@:");
      if (option == -1) break;
      switch (option) {
         case '@':
            traceflags::setflags (optarg);
            break;
         default:
            complain() << "-" << (char) optopt << ": invalid option"
                       << endl;
            break;
      }
   }
}


void trim(string *line)
{
    size_t foundSpace = line->find_first_of(" ");
    size_t index = 0;
    if(foundSpace==0)
    {
        while(line->at(index)==' ')
        {
            line->erase(index, 1);
            index++;
        }
    }

    size_t foundEquals = line->find_first_of("=");

    if(foundEquals==0 && line->size()==1)
    {
        //dont do anything if there's just the equal sign.
    }
    else if(foundEquals!=std::string::npos)
    {
        index=foundEquals-1;
        if(foundEquals!=0)
        {
            while(line->at(index)==' ')
            {
                cout << "index=" << index << endl;
                line->erase(index, 1);
                --index;
            }
        }


        index=foundEquals+1;
        if(index<line->size())
        {
            while(index<line->size() && line->at(index)==' ')
            {
                cout << "index=" << index << endl;

                line->erase(index, 1);
                if(index+1 >= line->size())
                    break;
                else
                    ++index;
            }
        }
    }

    foundSpace = line->find_last_not_of(" ");
    if (foundSpace!=std::string::npos)
        line->erase(foundSpace+1);
}

int main (int argc, char** argv) {
    sys_info::set_execname (argv[0]);
    scan_options (argc, argv);
    str_str_map *the_map = new str_str_map();
    for (int argi = 1; argi < argc; ++argi)
    {

        string line;
        ifstream inputFile;

        string filename = argv[argi];

        inputFile.open(filename);

        if (inputFile.is_open())
        {
            int line_num = 0;

            while ( getline (inputFile,line) )
            {
                line_num++;
                cout << filename << ": " << line_num
                    << ": " << line << endl;

                if(line[0]=='#' || line.size() == 0)
                    continue;

                trim(&line);

                if(line.size() == 0)
                    continue;

                if(line[0]=='=' && line.size()==1 && !the_map->empty())
                {
                    for(auto itor = the_map->begin();
                            itor!=the_map->end();++itor)
                    {
                        cout << itor->first << " = "
                                    << itor->second << endl;
                    }
                    continue;
                }

                if(line[0] == '=' && line.size()>1
                                    && !the_map->empty())
                {
                    string value = line.substr(1);
                    for(auto itor = the_map->begin();
                                    itor!=the_map->end();++itor)
                    {
                        if (value == itor->second)
                            cout << itor->first << " = " <<
                                                itor->second << endl;
                    }
                    continue;
                }

                size_t firstFind = line.find_first_of("=");

                if(firstFind == std::string::npos && !the_map->empty())
                {
                    auto itor=the_map->find(line);
                    if(line == itor->first)
                        cout << itor->first << " = " << itor->second
                                                            << endl;
                    else
                        cout << line << ": key not found" << endl;

                    continue;
                }

                if(firstFind == std::string::npos && the_map->empty())
                {
                    cout << line << ": key not found" << endl;
                    continue;
                }


                string key = line.substr(0,firstFind);

                if(firstFind == line.size()-1 && key != ""
                                    && !the_map->empty())
                {
                    auto itor=the_map->find(key);
                    if(key == itor->first)
                        itor.erase();
                    else
                        cout << key << ": key not found" << endl;

                    continue;
                }


                string value = line.substr(firstFind+1);

                str_str_pair *insert_pair =
                                        new str_str_pair(key, value);
                the_map->insert (*insert_pair);

            }

            inputFile.close();
      }
      else
      {
            cout << "Unable to open file" << endl;
            return EXIT_FAILURE;
      }

   }

   return EXIT_SUCCESS;
}

