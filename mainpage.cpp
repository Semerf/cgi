#include <iostream>

using namespace std;


int main()
{
    cout << "Content-Type: text/html; charset=utf-8" << endl << endl;
    cout << "<html> <head> <meta charset=\"utf-8\">";
	cout << "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
	cout << "<title>Лабораторная работа CGI</title>";
    cout << "<meta name=\"theme-color\" content=\"#cc99cc\">";
    cout << "<link href=\"https://cdn.jsdelivr.net/npm/bootstrap@5.2.2/dist/css/bootstrap.min.css\" rel=\"stylesheet\" integrity=\"sha384-Zenh87qX5JnK2Jl0vWa8Ck2rdkQ2Bzep5IDxbcnCeuOxjzrPF/et3URy9Bv1WTRi\" crossorigin=\"anonymous\">";
    cout << "</head>";
    cout << "<body>";
    cout << "<p>Первая лабораторная работа</p>";
    cout << "<form action=\"/cgi-bin/test.cgi\" method=\"GET\">";
	cout <<  "<p><input type=\"submit\" value=\"Перейти\"></p>";
    cout << "</form>";
    cout << "</body></html>";
}
