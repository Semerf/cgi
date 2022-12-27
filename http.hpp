#ifndef __HTTP_HPP
#define __HTTP_HPP
#include <map>


typedef struct {
		std::string filename; 	// реальное имя файла
		std::string mimetype;	// MIME-тип файла
		std::string tmp_name; // временное имя файла
		int error; 	// код ошибки (0, если нет)
		int size; 	// размер загружаемого файла
	} UploadedFile;


class HTTP
{
	protected:
	std::map<std::string, std::string> escape = {
		{"\"","\\&quot;"}, {"<","&lt;"}, {">","&gt;"}
		};
    public:
	HTTP();
	HTTP(std::string name, std::string value);
	std::string httpGet(std::string name);
	std::string httpPost(std::string name);
	std::string getCookie(std::string name);
	std::string setCookie(std::string name, std::string value);

	unsigned int CtoI(char ch);
	unsigned int CCtoI(char ch1, char ch2);
	std::string getHeader(std::string name);
	// Возвращание сруктуры свойства файла загруженного файла (name)
	std::string RawURLDecode(std::string input);
	// декодирует строку из 16-ричного представления в plain-text

	UploadedFile getFile(std::string name); 
	// Перемещение загруженного файла tmpFile в директорию path
	int move_uploaded_file(UploadedFile tmpFile, std::string path); 
	// загружает файл “tmpFile” в директорию “path”
	~HTTP();

	private:
	std::map<std::string, std::string> cookie;
	std::map <std::string, std::string> headers;
	std::map <std::string, std::string> getData;
	std::map <std::string, std::string> postData;
	std::map <std::string, UploadedFile> filesData;
	bool isMultipart = false;
	// флаг множественного содержимого
	std::string boundary; // разграничитель
	
	void checkMultipart();
	// проверяет, является ли запрос multipart/form-data и если да, то заполняет boundary и isMultipart


};


#endif