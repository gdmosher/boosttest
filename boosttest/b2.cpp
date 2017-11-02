// just a tester to see if boost works
// this test tokenizes an example string, then prints commands
// and separators on two separate lines
// compile in c++11 (g++ -std=c++11 boosttest.cpp)

#include <boost/tokenizer.hpp>
#include <string>
#include <vector>

int main()
{
  // define tokenizer type
  typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
  // example string to tokenize
  std::string example = "cd & ls -a; vim main.cpp && || ls";
  // add ";", "&", "|" as separators (connectors)
  // don't know how to add strings as connectors
  // first parameter is required as dropped connectors, made it a random symbol
  boost::char_separator<char> sep("#",";&&||", boost::keep_empty_tokens);
  tokenizer tok{example, sep};
  // vectors for testing out separation of commands and connectors
  std::vector<std::string> command;
  std::vector<std::string> connect;
  // i is iterated in following loop
  int i = 0;
  // loop through tok and print out each token
  for(const auto &t : tok)
  {
    std::cout << "\n((" << t << "))" << "{{" << i << "}}" << '\n';
    std::cout << "[[" << t[0] << "]]" << '\n' << "....." << '\n';
    // every other entry into the tokenizer object will go into
    // command and connect respectively
    if(i % 2 == 0)
    {
        command.push_back(t);
    }
    else
    {
      connect.push_back(t);
    }
    i++;
  }
  // print out command and connect to make sure we separated them
  std::cout << "Commands:\n";
  for(int j = 0; j < command.size(); ++j)
  {
    std::cout << j + 1 << ": " << command.at(j) << "    ";
  }
  std::cout << "\nConnectors:\n";
  for(int k = 0; k < connect.size(); ++k)
  {
    std::cout << k + 1 << ": " <<  connect.at(k) << "    ";
  }
  std::cout << std::endl;
  return 0;
}
