//
// Created by semerf on 08.11.22.
//
#include <iostream>
#include <fstream>
#include <map>
#include "http.hpp"
#include "view.hpp"
#include <errno.h>
#include "db.hpp"

using namespace std;



int main()
{
    string postData;
    cin >> postData;

    HTTP mhttp;

    if (string(getenv("REQUEST_METHOD"))=="POST")
    {

        string data = mhttp.httpPost(postData);
        //cout << "<p>Значение POST-данных равно: " << data << "</p>";

    }
    else {
        View::StandartView();
        string GetQuery = getenv("QUERY_STRING");
        string Query = mhttp.RawURLDecode(GetQuery);
        cout << "<p>Значение GET-данных равно: " << Query << "</p>";
        cout << mhttp.httpGet(GetQuery);
    }
    cout << mhttp.getCookie("");
    cout << "<p>Значение REQUEST_METHOD равно: " << getenv("REQUEST_METHOD")<< "</p>";
    cout << "<p>Значение HTTP_COOKIE равно: " << getenv("HTTP_COOKIE")<< "</p>";
    return 0;
}

HTTP::HTTP(){
    View::BaseView();
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
string HTTP::httpGetAll() {

    return "";
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