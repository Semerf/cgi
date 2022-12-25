#ifndef __HTTP_HPP
#define __HTTP_HPP
#include <map>
class HTTP
{
    public:
	HTTP();
	std::string httpGet(std::string name);
	std::string httpGetAll();
	std::string httpPost(std::string name);
	std::string getCookie(std::string name);
	std::string setCookie(std::string name, std::string value);
	~HTTP();
	private:
	 std::map<std::string, std::string> cookie;
	 std::map<std::string, std::string> getParam;
	 std::map<std::string, std::string> postParam;
};


#endif