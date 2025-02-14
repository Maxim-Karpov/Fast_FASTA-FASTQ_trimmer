#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
//using namespace std;

std::string filename;
std::string trim_mode;
int trim_len;
std::string file_type;
void print_info();
void trim(std::string fn, std::string tm, int tlen, std::string ft);
int length;
std::string out_filename;

int main(int argc, char **argv) {
  if (argc == 1){
  print_info();
  }
  for (int i =  1; i<argc; i+=2) {
      if (strcmp(argv[i],"-i")==0 && argv[i+1]) {
        filename = argv[i+1];
        std::cout << "filename: " << filename << "\n" ;
        }
      else if (strcmp(argv[i],"-t")==0 && argv[i+1]) {
        trim_mode = argv[i+1];
        std::cout << "trim_mode: " << trim_mode << "\n" ;
        }
      else if (strcmp(argv[i],"-tl")==0 && argv[i+1]) {
        trim_len = std::stoi(argv[i+1]);
        std::cout << "trim_length: " << trim_len << "\n" ;
        }
      else if (strcmp(argv[i],"-ft")==0 && argv[i+1]) {
        file_type = argv[i+1];
        std::cout << "file_type: " << file_type << "\n" ;
        }
      else {
        print_info();
      }

  }
  if (!filename.empty() && !trim_mode.empty() && trim_len>0){
    std::cout << "\ntrimming " << trim_len << " bp from " << trim_mode << " side(s)" << "of a " << file_type << " file" << "\n";
    trim(filename, trim_mode, trim_len, file_type);
  }
}

void print_info(){
      std::cout << "\n";
      std::cout << "***** Fast FASTA trimmer *****" << "\n";
      std::cout << "Input requires all 4 arguments:" << "\n";
      std::cout << "  -i    input file" << "\n";
      std::cout << "  -t    trim mode (both|left|right)" << "\n";
      std::cout << "  -tl   trim length - number of basepairs to trim from both, left, or right sides of the sequences" << "\n";
      std::cout << "  -ft file type (fasta|fastq)" << "\n";
      std::cout << "\n";
}

void trim(std::string fn, std::string tm, int tlen, std::string ft){
    std::ifstream infile(fn);
    std::string out_filename;
    if (ft == "fastq"){
        out_filename = "trimmed_output.fastq";
    }
    else if (ft == "fasta"){
        out_filename = "trimmed_output.fasta";
    }
    std::ofstream outfile(out_filename);
  
    if (!infile.is_open() || !outfile.is_open()) {
        std::cerr << "Error: Unable to open file(s)!" << std::endl;
        return;
    }
    
    std::string line;

    if (ft == "fasta"){
        
        while (std::getline(infile, line)) {
            if (!line.empty() && line[0] == '>'){
                outfile << line << "\n";
            }
            else if (tm == "both"){
                int length =  line.length();
                std::string trimmed = line.substr(tlen,length-tlen-tlen);
                outfile << trimmed << "\n";
            }
            else if (tm == "left"){
                int length =  line.length();
                std::string trimmed = line.substr(tlen-1,length-tlen);
                outfile << trimmed << "\n";
            }
            else if (tm == "right"){
                std::string trimmed = line.substr(0,length-tlen);
                outfile << trimmed << "\n";
            }
        }
  }
  
  if (ft == "fastq"){
  
          while (std::getline(infile, line)) {
          int length = line.length();
            if (!line.empty() && line[0] == '@' && length < 60){
                outfile << line << "\n";
            }
            else if (line == "+"){
                outfile << line << "\n";
            }
            else if (tm == "both"){
                int length =  line.length();
                std::string trimmed = line.substr(tlen,length-tlen-tlen);
                outfile << trimmed << "\n";
            }
            else if (tm == "left"){
                int length =  line.length();
                std::string trimmed = line.substr(tlen-1,length-tlen);
                outfile << trimmed << "\n";
            }
            else if (tm == "right"){
                std::string trimmed = line.substr(0,length-tlen);
                outfile << trimmed << "\n";
            }
        }
  
  }
    infile.close();
    outfile.close();
    return;
}
