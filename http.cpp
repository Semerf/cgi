//
// Created by semerf on 08.11.22.
//
#include <iostream>
#include <fstream>
#include <map>
#include "http.hpp"
#include "view.hpp"
#include <errno.h>
#include <sstream>
#include <unistd.h>
#include <cstring>
#include <iterator>


#include <cstdio>
#include <cerrno>
#include <cstdlib>



#define MAX_FILESIZE 248000
using namespace std;



int main()
{
    UploadedFile tstFile;
	HTTP mhttp;
    tstFile = mhttp.getFile("attachedFile");
	if(tstFile.error == 0)
	mhttp.move_uploaded_file(tstFile, "/home/semerf/files/"+tstFile.filename);

    return 0;
}

// удаление первого пробела
std::string leftTrim(std::string * str)
{
  if (*((*str).begin()) == ' '){
  (*str).erase((*str).begin());
  }
  if ((*((*str).end()-1) == '\n') or (*((*str).end()-1) == '\r')){
  (*str).erase((*str).end()-1);
  }
  return *str;
}

HTTP::HTTP(){
    FILE * fp = fopen("err.txt", "w");
    FILE * of; 


    auto key = std::string{};
    auto val = std::string{};
    View::BaseView();
    if (getenv("CONTENT_TYPE") != nullptr){
        //fprintf(fp,getenv("CONTENT_TYPE"));
        //fprintf(fp,"\n");
        UploadedFile upf;
        std::string boundary;
        std::stringstream strstm(getenv("CONTENT_TYPE"));
        getline(strstm, val, ';');  // Get Content-Type
        //fprintf(fp,"%s\n",val.c_str());
        if (val == "multipart/form-data"){
            std::getline(strstm, val, '=');  // skip " boundary="
            std::getline(strstm, boundary);  // get boundary
            //fprintf(fp, boundary.c_str());
            int flag = 100000; //100000 строк возможно для чтения
            int tmpfd = -1;
            std::ofstream ofile;
            std::string name;
            std::string filename;
            while (flag)
            {
                //fprintf(fp,"%d \n", flag);
                std::string ContentType[2];
                std::getline(std::cin, val);
                if(std::cin.eof()){
                    fprintf(fp,"ERROR: end of cin!!\n");
                    return;
                }
                long long int fs = 0;
                //fprintf(fp,"%s\n",val.c_str());

                if (leftTrim(&val) == ("--" + boundary)){
                    std::getline(std::cin, val, '\"');  // SKIP Content-Disposition: form-data; name="

                    std::getline(std::cin, name, '\"');  // get name

                    std::getline(std::cin, val, '\"');  // SKIP "; filename="

                    std::getline(std::cin, filename, '\"');  // get filename

                    std::getline(std::cin, val, '\n');  // skip '"\n'

                    std::getline(std::cin, val, ' ');  // skip "Content-Type: "

                    std::getline(std::cin, ContentType[0], '/');  // get content type before '/'

                    std::getline(std::cin, ContentType[1], '\n');  // get content type
                    filesData[name].mimetype = ContentType[0];
                    std::getline(std::cin, val, '\n');  // skip empty line

                    filesData[name].filename = filename;
                    filesData[name].size = 0;
                    filesData[name].error = 0;
                    // Create temp file
                    
                    // закрытие файла, если он открыт
                    if (ofile.is_open()){
                        ofile.close();
                    }
                    char tmpfilename[] = "/tmp/HTTP/HTTPtemp_XXXXXX";

                    tmpfd = mkstemp(tmpfilename);

                    fprintf(fp,"\n%s\n",tmpfilename);

                    ofile.open(tmpfilename, std::ios_base::out | std::ios_base::trunc);
                    if(!ofile){
                        fprintf(fp,"\n\n%s\n\n", strerror(errno));
                    }

                    //
                    filesData[name].tmp_name = tmpfilename;
                    // unlink(filename);              // Delete the temporary file.
                }else{
                    if (leftTrim(&val) == ("--" + boundary + "--")){  // Exit if end
                        // fprintf(fp,"e\n");
                        break;
                    }

                    ofile << val <<std::endl;
                    filesData[name].size += val.size()+1;
                    if (filesData[name].size > MAX_FILESIZE){
                        filesData[name].error = -1;
                        break;
                    }
                }
                flag--; //Stop if > 100000 lines
                if(!flag){
                    fprintf(fp,"max count!\n");
                    break;
                }
            }
        }else{
            if (val == "application/x-www-form-urlencoded"){
                // parse POST params
                std::string postData;
                std::getline(std::cin, postData, static_cast<char>(0));
                string data = httpPost(postData);
                }
            }
        }

    if (string(getenv("REQUEST_METHOD"))=="GET")
    {
        View::StandartView();
        string GetQuery = getenv("QUERY_STRING");
        string Query = RawURLDecode(GetQuery);
        cout << "<p>Значение GET-данных равно: " << Query << "</p>";
        cout << httpGet(GetQuery);
    }
    cout << getCookie("");
    cout << "<p>Значение REQUEST_METHOD равно: " << getenv("REQUEST_METHOD")<< "</p>";
    cout << "<p>Значение HTTP_COOKIE равно: " << getenv("HTTP_COOKIE")<< "</p>";
}

HTTP::HTTP(string key, string value){
    View::StandartView(key, value);
}

HTTP::~HTTP(){
    return;
}
string HTTP::httpPost(string post) {
    string buff = "";
    string key;
    string out;
    int condition=0;
    for(int i = 0; i <= post.length(); ++i)
    {
        if (post[i]=='='){
            if(buff=="key") condition = 1;
            if(buff=="value") condition = 2;
            if(buff=="file") condition=3;
            buff = "";
        } else if((post[i]=='&') || i == post.length()){
            
            if(condition==1){
                fstream file("/home/semerf/site/cgi/data.csv", ios_base::out | ios_base::app);
                key = buff;
                out+=buff+",";
                buff="";
                file << out;
                out = "";
                file.close();
            } else if(condition==2){
                fstream file("/home/semerf/site/cgi/data.csv", ios_base::out | ios_base::app);
                cout << setCookie(key, buff);
                out+=buff+"\n";
                buff="";
                file << out;
                out = "";
                file.close();
            } else if (condition == 3)
            {
                out = buff;
            }
            condition=0;
        } else{
            buff +=post[i];
        };
    };

    return out;
}
string HTTP::httpGet(string instr) {
    fstream file("/home/semerf/site/cgi/data.csv", ios_base::in);
    map<string, string> filedata;
    map<string, string>::iterator it, itEnd;
    
    char key[20], value[20];
    while(1)
    {
         file.getline(key,20,',');
         file.getline(value,20);
         if(file.eof()) break;
         filedata[key]=value;
    }
    file.close();
    it=filedata.begin();
    itEnd=filedata.end();

    
    string method = "";
    string buff = "";
    for(int i = 0; i <= instr.length(); ++i)
    {
        if (instr[i]=='=') break;
        else method +=instr[i];
    }
    if(method=="all"){
        cout <<"<table border=\"1px\">";
        while(it != itEnd)
        {
            cout <<"<form action=\"/cgi-bin/test.cgi\" method=\"GET\"><tr><td>" <<it->first<< "</td><td>"<< it->second<<"</td><td><b>Нажмите на кнопку для удаления записи</b><input name=\"del\" value=\""<<it->first<<"\" type=\"submit\" value=\"Удалить\"></td></form>";
            it++;
        }
        cout <<"</table>";
        return "All read";
    }
    if(method=="key"){
        for(int i = 0; i < instr.length(); ++i)
        {
            if (instr[i]=='=') buff="";
            else buff +=instr[i];
        }
        it = filedata.find(buff);
        if(it==filedata.end()){
            cout<<"<p>По данному ключу нет данных</p>"<<buff;
            return "key error read";
        }            
        cout <<"<table border=\"1px\">";
        cout <<"<form action=\"/cgi-bin/test.cgi\" method=\"GET\"><tr><td>" <<it->first<< "</td><td>"<< it->second<<"</td><td><b>Нажмите на кнопку для удаления записи</b><input name=\"del\" value=\""<<it->first<<"\" type=\"submit\" value=\"Удалить\"></td></form>";
        cout <<"</table>";
        return "Key read";
    }
    if(method=="del"){
        for(int i = 0; i < instr.length(); ++i)
        {
            if (instr[i]=='=') buff="";
            else buff +=instr[i];
        }
        it = filedata.find(buff);
        if(it==filedata.end()){
            cout<<"<p>По данному ключу нет данных, невозможно удалить</p>"<<buff;
            return "key error del";
        }   
        filedata.erase(it);
        fstream file("/home/semerf/site/cgi/data.csv", ios_base::out | ios_base::trunc);
        it = filedata.begin();
        while(it != filedata.end())
        {
            cout << "<p>"<<it->first <<","<<it->second<<"</p>";
            file << it->first <<","<<it->second<<"\n";
            it++;
        }
        file.close();
        return "success del";
    }

    return "is not a request";

}
string HTTP::setCookie(string key, string value){
    View::StandartView(key, value);
    return "cookie set";
}
string HTTP::getCookie(string){
    return getenv("HTTP_COOKIE");
}

string HTTP::RawURLDecode(string input){

  std::string res = "";
  for (int i = 0; i < input.length (); i++)
    {
        if (input[i] == '+')
        {
            res.append(1, ' ');
        }
        if (input[i] != '%')
        {
            res.append(1, input[i]);
        }
        if (input[i] == '%')
        {
            i++;  // skip '%'
            res.append(1, CCtoI(input[i], input[i + 1]));
            i++;  // skip one hex (other hex will be skiped by i++ in for)
            continue;
        }
    }
  return res;
}
unsigned int HTTP::CtoI(char ch){
    if (ch >= 'A'){
	      return ch - 'A' + 10;
	  }else{
	      return ch - '0';
	  }
}

unsigned int HTTP::CCtoI(char ch1, char ch2){
    return (CtoI(ch1) << 4) + CtoI(ch2);
}
int HTTP::move_uploaded_file(UploadedFile tmpFile, std::string path){
    std::ifstream  src(tmpFile.tmp_name, std::ios::binary);
    std::ofstream  dst(path,   std::ios::binary);
    if (!src.is_open()){
        return -1;
    }
    if (!dst.is_open()){
        return -2;
    }
    dst << src.rdbuf();
    unlink(tmpFile.tmp_name.c_str());
    return 0;
}

UploadedFile HTTP::getFile(std::string name)
{
    return filesData[name];
}