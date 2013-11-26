#pragma once
#include <string>
using namespace std;

class Archive
{
public:
    class Error : public std::exception 
    {
    public:
        Error(string what) : exception(what.c_str()) {} 
    };


public:
    Archive();
    Archive(string & sArchivePath);
	Archive(string & sArchivePath, string & sArchiveName);
	virtual ~Archive(void);

    // useful methods >_<
    void create();
    void add(string sSrcFile, string sDstFile);
    void close();

private:
    string m_sPath;
    string m_sName;

    struct zip * m_archiveHandle;
    FILE * fp;
    struct zip_source * zs;
    int m_error;
};

