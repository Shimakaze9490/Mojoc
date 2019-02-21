/*
 * Copyright (c) 2012-2019 scott.cgi All Rights Reserved.
 *
 * This code and its project Mojoc are licensed under [the MIT License],
 * and the project Mojoc is a game engine hosted on github at [https://github.com/scottcgi/Mojoc],
 * and the author's personal website is [https://scottcgi.github.io],
 * and the author's email is [scott.cgi@qq.com].
 *
 * Since : 2013-08-27
 * Update: 2019-1-8
 * Author: scott.cgi
 */

 
#ifndef FILE_H
#define FILE_H


#include <stddef.h>
#include "Engine/Toolkit/HeaderUtils/Define.h"


/**
 * Related to platform directory.
 * 
 * Android: assets   files
 * IOS    : NSBundle files
 */
typedef struct File File;

/**
 * Resource File access API.
 */
struct AFile
{
    /**
     * Open a file from platform resource directory by file path.
     *
     * resourceFilePath:
     *     Android: assets
     *     IOS    : NSBundle
     */
    File*       (*Open)               (const char* resourceFilePath);

    /**
     * Open a file descriptor from platform resource directory by file path.
     * it can be used to read the file data.
     *
     * resourceFilePath:
     *     Android: assets
     *     IOS    : NSBundle
     *
     * returns < 0 if direct fd access is not possible (for example, if the file is compressed).
     */
    int         (*OpenFileDescriptor) (const char* resourceFilePath, long* outStart, long* outLength);

    /**
     * Close an opened file connection, free any related resources.
     */
    void        (*Close)              (File* file);

    /**
     * Return file length.
     */
    long        (*GetLength)          (File* file);

    /**
     * Read count bytes of data from the current offset.
     * return the number of bytes read, zero on EOF, or < 0 on error.
     */
    int         (*Read)               (File* file, void* buffer, size_t count);

    /**
     * Seek to the specified offset.
     * the whence uses the same constants (SEEK_SET, SEEK_CUR, SEEK_END) as fseek().
     *
     * return the new position on success, or -1 on error.
     */
     long       (*Seek)               (File* file, long offset, int whence);

    /**
     * The internal data path related to platform directory.
     * if outPathLength not NULL, will set the strlen(internalDataPath).
     *
     * internalDataPath:
     *     Android: internal data directory
     *     IOS    : document data directory
     */
    const char* (*GetInternalDataPath)(int* outPathLength);
};


extern struct AFile AFile[1];


#endif
