#include <iostream>
#include "view.hpp"


using namespace std;
void View::BaseView()
{
    cout << "Content-Type: text/html; charset=utf-8"<<endl ;
}

void View::StandartView()
{

    cout << endl;
    cout << "<html> <head> <meta charset=\"utf-8\">";
	cout << "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
	cout << "<title>Лабораторная работа CGI</title>";
    cout << "<meta name=\"theme-color\" content=\"#cc99cc\">";
    cout << "<link href=\"https://cdn.jsdelivr.net/npm/bootstrap@5.2.2/dist/css/bootstrap.min.css\" rel=\"stylesheet\" integrity=\"sha384-Zenh87qX5JnK2Jl0vWa8Ck2rdkQ2Bzep5IDxbcnCeuOxjzrPF/et3URy9Bv1WTRi\" crossorigin=\"anonymous\">";
    cout << "</head>";
    cout << "<body>";
    cout << "<p>Запись значения (POST)</p>";
    cout << "<form action=\"/cgi-bin/test.cgi\" method=\"POST\">";
	cout <<  "<p><input name=\"key\"></p>";
    cout <<  "<p><input name=\"value\"></p>";
	cout <<  "<p><input type=\"submit\" value=\"Отправить\"></p>";
    cout << "</form>";
    cout << "<form action=\"/cgi-bin/test.cgi\" method=\"GET\">";
	cout << "<p>Получение записи по ключу (GET)</p>";
    cout <<  "<p><input name=\"key\"></p>";
	cout <<  "<p><input type=\"submit\" value=\"Получить\"></p>";
    cout << "</form>";
    cout << "<form action=\"/cgi-bin/test.cgi\" method=\"GET\">";
	cout <<  "<p><input name=\"all\"type=\"submit\" value=\"Получить все записи (GET)\"></p>";
    cout << "</form>";
    cout << "<p>Установить cookie</p>";
    cout << "<form action=\"/cgi-bin/test.cgi\" method=\"GET\">";
	cout <<  "<p><input name=\"cookie-key\"></p>";
    cout <<  "<p><input name=\"cookie-value\"></p>";
	cout <<  "<p><input type=\"submit\" value=\"Отправить\"></p>";
    cout << "</form>";
    cout << "<form action=\"/cgi-bin/test.cgi\" method=\"POST\" enctype=\"application/x-www-form-urlencoded\">";
    cout <<	"<input type=\"file\" name=\"file\">";
	cout << "<input type=\"submit\" value=\"Загрузить\">";
    cout << "</form>";
    cout << "</body></html>";
}
void View::StandartView(string key,string value)
{

    cout <<"Set-Cookie: "<<key<<"="<<value<<"; expires=Wed May 18 03:33:20 2033;"<<endl << endl;
    cout << "<html> <head> <meta charset=\"utf-8\">";
	cout << "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
	cout << "<title>Лабораторная работа CGI</title>";
    cout << "<meta name=\"theme-color\" content=\"#cc99cc\">";
    cout << "<link href=\"https://cdn.jsdelivr.net/npm/bootstrap@5.2.2/dist/css/bootstrap.min.css\" rel=\"stylesheet\" integrity=\"sha384-Zenh87qX5JnK2Jl0vWa8Ck2rdkQ2Bzep5IDxbcnCeuOxjzrPF/et3URy9Bv1WTRi\" crossorigin=\"anonymous\">";
    cout << "</head>";
    cout << "<body>";
    cout << "<p>Запись значения (POST)</p>";
    cout << "<form action=\"/cgi-bin/test.cgi\" method=\"POST\">";
	cout <<  "<p><input name=\"key\"></p>";
    cout <<  "<p><input name=\"value\"></p>";
	cout <<  "<p><input type=\"submit\" value=\"Отправить\"></p>";
    cout << "</form>";
    cout << "<form action=\"/cgi-bin/test.cgi\" method=\"GET\">";
	cout << "<p>Получение записи по ключу (GET)</p>";
    cout <<  "<p><input name=\"key\"></p>";
	cout <<  "<p><input type=\"submit\" value=\"Получить\"></p>";
    cout << "</form>";
    cout << "<form action=\"/cgi-bin/test.cgi\" method=\"GET\">";
	cout <<  "<p><input name=\"all\"type=\"submit\" value=\"Получить все записи (GET)\"></p>";
    cout << "</form>";
    cout << "<p>Установить cookie</p>";
    cout << "<form action=\"/cgi-bin/test.cgi\" method=\"GET\">";
	cout <<  "<p><input name=\"cookie-key\"></p>";
    cout <<  "<p><input name=\"cookie-value\"></p>";
	cout <<  "<p><input type=\"submit\" value=\"Отправить\"></p>";
    cout << "</form>";
    cout << "<form action=\"/cgi-bin/test.cgi\" method=\"POST\" enctype=\"application/x-www-form-urlencoded\">";
    cout <<	"<input type=\"file\" name=\"file\">";
	cout << "<input type=\"submit\" value=\"Загрузить\">";
    cout << "</form>";
    cout << "</body></html>";
}
