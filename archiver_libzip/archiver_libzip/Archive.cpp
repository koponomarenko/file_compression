#include "Archive.h"

#include <zip.h>
#include <iostream>

Archive::Archive()
{
    m_sName = "test.zip";
    m_archiveHandle = 0;
}


Archive::Archive(string & sArchivePath) : m_sPath(sArchivePath)
{
    m_sName = "test.zip";
    m_archiveHandle = 0;
}


Archive::Archive(string & sArchivePath, string & sArchiveName) : m_sPath(sArchivePath), m_sName(sArchiveName)
{
    m_archiveHandle = 0;
}


Archive::~Archive(void)
{
    //close zip archive and discard changes
    zip_discard(m_archiveHandle);
}


void Archive::create()
{
    m_archiveHandle = zip_open(m_sName.c_str(), ZIP_CREATE | ZIP_EXCL, & m_error);
    if ( !m_archiveHandle )
    {
       throw Error("Can't create the archive. Can be already created.");
    }
}

// libzip allows to use slash (/) and backslash (\) in paths
void Archive::add(string sSrcFile, string sDstFile)
{
    fp = fopen(sSrcFile.c_str(), "rb"); // rb flags

    zs = 0;
    zs = zip_source_filep(m_archiveHandle, fp, 0, 0);
    //zs = zip_source_file(m_archiveHandle, sSrcFile.c_str(), 0, 0);
    if ( !zs )
    {
        throw Error("zip_source_filep()");
    }

    zip_int64_t fileIndex = 0;
    fileIndex = zip_add(m_archiveHandle,sDstFile.c_str(), zs);
    if ( fileIndex < 0 )
    {
        zip_source_free( zs );
        throw Error("zip_add");
    }

    ////////////////////////////////////////////////////////////////////////////
    //struct zip_stat zinfo;
    //if ( zip_stat_index(m_archiveHandle, fileIndex, 0, &zinfo) < 0 )
    //{
    //    throw Error("zip_stat_index - 1");
    //}
    //cout << "comp_method: " << zinfo.comp_method << endl;

    //if ( zip_set_file_compression(m_archiveHandle, fileIndex, ZIP_CM_DEFLATE, 0) < 0 )
    //{
    //    throw Error( "zip_set_file_compression : " + string(zip_strerror(m_archiveHandle)) );
    //}

    //if ( zip_stat_index(m_archiveHandle, fileIndex, 0, &zinfo) < 0 )
    //{
    //    throw Error("zip_stat_index - 2");
    //}
    //cout << "comp_method: " << zinfo.comp_method << endl;
}


void Archive::close()
{
    if ( !m_archiveHandle )
        return;

    if ( zip_close(m_archiveHandle) < 0)
    {
        throw Error( "Can't save changes and close: " + string(zip_strerror(m_archiveHandle)) );
    }
    fclose(fp);

    m_archiveHandle = 0;
}

