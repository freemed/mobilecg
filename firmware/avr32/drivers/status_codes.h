
 #ifndef STATUS_CODES_H_INCLUDED
 #define STATUS_CODES_H_INCLUDED

 enum status_code {
     STATUS_OK       =     0,
     ERR_IO_ERROR        =    -1,
     ERR_FLUSHED     =    -2,
     ERR_TIMEOUT     =    -3,
     ERR_BAD_DATA        =    -4,
     ERR_PROTOCOL        =    -5,
     ERR_UNSUPPORTED_DEV =    -6,
     ERR_NO_MEMORY       =    -7,
     ERR_INVALID_ARG     =    -8,
     ERR_BAD_ADDRESS     =    -9,
     ERR_BUSY        =   -10,
     ERR_BAD_FORMAT          =   -11,

     OPERATION_IN_PROGRESS   = -128,
 };

 typedef enum status_code status_code_t;

 #endif /* STATUS_CODES_H_INCLUDED */
