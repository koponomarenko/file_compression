#pragma once
#include <string>
#include "zip.h"
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

    zipFile m_archiveHandle;
    int m_error;
};

