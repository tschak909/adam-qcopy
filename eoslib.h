/**
 * A simple EOS binding library
 * 
 * @author Thomas Cherryhomes
 * @email <thom.cherryhomes@gmail.com>
 */

#ifndef EOSLIB_H
#define EOSLIB_H

#define EOS_SUCCESS 0
#define EOS_ERROR_DCB_NOT_FOUND 1
#define EOS_ERROR_DCB_BUSY 2
#define EOS_ERROR_DCB_IDLE 3
#define EOS_ERROR_NO_DATE 4
#define EOS_ERROR_NO_FILE 5
#define EOS_ERROR_FILE_EXISTS 6
#define EOS_ERROR_PRINTER_BUSY 6
#define EOS_ERROR_NO_AVAILABLE_FCB 7
#define EOS_ERROR_FILE_INCOMPATIBLE 8
#define EOS_ERROR_BAD_FILE_NUMBER 9
#define EOS_ERROR_END_OF_FILE 10
#define EOS_ERROR_FILE_TOO_BIG 11
#define EOS_ERROR_DIRECTORY_FULL 12
#define EOS_ERROR_STORAGE_MEDIA_FULL 13
#define EOS_ERROR_FILE_NUMBER 14
#define EOS_ERROR_RENAME 15
#define EOS_ERROR_DELETE 16
#define EOS_ERROR_RANGE 17
#define EOS_ERROR_BAD_MODE 17
#define EOS_ERROR_SYNC 18
#define EOS_ERROR_SYNC_2 19
#define EOS_ERROR_INCOMPATIBLE_MODE 20
#define EOS_ERROR_MEDIA_STATUS 21
#define EOS_ERROR_MEDIA_ERROR 22
#define EOS_ERROR_PROGRAM_NONEXISTANT 23
#define EOS_ERROR_DIRECTORY_INVALID 24
#define EOS_ERROR_TIMEOUT 27

/**
 * @brief Read 1 block (with retry)
 * @param buf read into this buffer address
 * @param dev The EOS device number (0-0xFF)
 * @param blockno Desired block number (0-0xFFFFFFFF)
 * @return the error code, 0=success, anything non-zero is error.
 */ 
unsigned char eos_readblock(void* buf, unsigned char dev, unsigned long blockno);

/**
 * @brief Write 1 block (with retry)
 * @param buf read into this buffer address
 * @param dev The EOS device number (0-0xFF)
 * @param blockno Desired block number (0-0xFFFFFFFF)
 * @return the error code, 0=success, anything non-zero is error.
 */ 
unsigned char eos_writeblock(void* buf, unsigned char dev, unsigned long blockno);

/**
 * @brief Request device status
 * @param dev The EOS device number (0-FF)
 * @return non-zero = error, at which point, you should get requested status
 */
unsigned char eos_requeststatus(unsigned char dev);

/**
 * @brief Returned requested device status from DCB
 * @param dev The EOS device number (0-FF)
 * @return non-zero = error, at which point, you should get requested status
 */
unsigned char eos_getrequestedstatus(unsigned char dev);

#endif
