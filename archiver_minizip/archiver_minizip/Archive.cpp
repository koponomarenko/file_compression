#include "Archive.h"
#include "zip.h"
#include "iowin32.h"

#include <iostream>

#define BUF_SIZE 16384

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
    //zip_discard(m_archiveHandle);
}
//#define USEWIN32IOAPI

void Archive::create()
{
#        ifdef USEWIN32IOAPI
    zlib_filefunc64_def ffunc;
    fill_win32_filefunc64A(&ffunc);
    m_archiveHandle = zipOpen2_64(m_sName.c_str(), APPEND_STATUS_CREATE, NULL, &ffunc);
#        else
     m_archiveHandle = zipOpen64(m_sName.c_str(), APPEND_STATUS_CREATE);
#        endif

     if ( !m_archiveHandle )
     {
         throw Error("Can't create the archive. Can be already created.");
     }
}

// libzip allows to use slash (/) and backslash (\) in paths
void Archive::add(string sSrcFile, string sDstFile)
{
    //////////////////////////// create a file 
    zip_fileinfo zfi;
    memset(&zfi, 0, sizeof(zfi));
    int zip64 = 1;
    int ret = zipOpenNewFileInZip64(m_archiveHandle,
        sDstFile.c_str(),
        &zfi,
        NULL,   0,
        NULL,   0,
        "my comment for this interior file",
        Z_DEFLATED,
        Z_DEFAULT_COMPRESSION,
        zip64
        );
    if ( ret != 0 )
    {
        throw Error("Can't add file to a zip archive.");
    }


    //////////////////////////// write to the file
    FILE * pFile = fopen( sSrcFile.c_str(), "rb" );
    if ( !pFile )
    {
        throw Error("Can't open target file.");
    }

    char * buf = new char[BUF_SIZE];
    int size_read = 0;
    int err;
    do
    {
        err = ZIP_OK;
        size_read = (int)fread(buf, 1, BUF_SIZE, pFile);
        if (size_read < BUF_SIZE)
            if ( feof(pFile) == 0 )
            {
                err = ZIP_ERRNO;
            }

            if (size_read > 0)
            {
                err = zipWriteInFileInZip (m_archiveHandle, buf, size_read);
            }
    } while ((err == ZIP_OK) && (size_read>0));

    delete [] buf;

    //////////////////////////// close the file 
    if ( zipCloseFileInZip(m_archiveHandle) != 0 )
    {
        throw Error("Can't close added file.");
    }
}


void Archive::close()
{
    if ( !m_archiveHandle )
        return;

    if ( zipClose(m_archiveHandle, "my comment for exterior file") != 0)
    {
        throw Error( "Can't save changes and close." );
    }

    m_archiveHandle = 0;
}

