// File: muerrno.h
// Author: Chad Hogg
// A library for noting and retrieving errors.
// Part of CSCI380 munix lab.

#ifndef MUERRNO_H
#define MUERRNO_H

// The global variable into which our functions will write error codes.
extern int muerrno;

#define MU_E_BAD_NAME 1
#define MU_E_DOES_NOT_EXIST 2
#define MU_E_NOT_DIR 3
#define MU_E_PERMISSION 4
#define MU_E_NOT_REG 5
#define MU_E_FULL_TABLE 6
#define MU_E_INVALID_FD 7
#define MU_E_NO_SUCH_USER 8
#define MU_E_NO_SUCH_GROUP 9
#define MU_E_NOT_MEMBER 10

#endif//MUERRNO_H