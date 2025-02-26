#pragma once

// 1xx - Positive Preliminary Replies
#define RES_RESTART_MARKER "110 Restart marker reply."
#define RES_SERVICE_READY_LATER "120 Service ready in nnn minutes."
#define RES_DATA_ALREADY_OPEN "125 Data connection already open; transfer starting."
#define RES_FILE_STATUS_OK "150 File status okay; about to open data connection."

// 2xx - Positive Completion Replies
#define RES_COMMAND_OK "200 Command okay."
#define RES_COMMAND_NOT_IMPLEMENTED "202 Command not implemented, superfluous at this site."
#define RES_SYSTEM_STATUS "211 System status, or system help reply."
#define RES_DIRECTORY_STATUS "212 Directory status."
#define RES_FILE_STATUS "213 File status."
#define RES_HELP_MESSAGE "214 Help message."
#define RES_SYSTEM_TYPE "215 NAME system type." // TODO: Replace NAME with actual system type
#define RES_SERVICE_READY "220 Service ready for new user."
#define RES_SERVICE_CLOSING "221 Service closing control connection."
#define RES_DATA_OPEN_NO_TRANSFER "225 Data connection open; no transfer in progress."
#define RES_TRANSFER_COMPLETE "226 Closing data connection. Requested file action successful."
#define RES_ENTERING_PASSIVE_MODE "227 Entering Passive Mode (h1,h2,h3,h4,p1,p2)." // TODO: Replace values dynamically
#define RES_USER_LOGGED_IN "230 User logged in, proceed."
#define RES_REQUEST_COMPLETED "250 Requested file action okay, completed."
#define RES_PATH_CREATED "257 \"PATHNAME\" created." // TODO: Replace PATHNAME dynamically

// 3xx - Positive Intermediate Replies
#define RES_USER_OK_NEED_PASSWORD "331 User name okay, need password."
#define RES_NEED_ACCOUNT "332 Need account for login."
#define RES_ACTION_PENDING "350 Requested file action pending further information."

// 4xx - Transient Negative Completion Replies
#define RES_SERVICE_UNAVAILABLE "421 Service not available, closing control connection."
#define RES_CANT_OPEN_DATA "425 Can't open data connection."
#define RES_TRANSFER_ABORTED "426 Connection closed; transfer aborted."
#define RES_FILE_UNAVAILABLE "450 Requested file action not taken."
#define RES_LOCAL_ERROR "451 Requested action aborted: local error in processing."
#define RES_INSUFFICIENT_STORAGE "452 Requested action not taken. Insufficient storage space."

// 5xx - Permanent Negative Completion Replies
#define RES_SYNTAX_ERROR "500 Syntax error, command unrecognized."
#define RES_SYNTAX_ERROR_PARAMS "501 Syntax error in parameters or arguments."
#define RES_COMMAND_NOT_SUPPORTED "502 Command not implemented."
#define RES_BAD_COMMAND_SEQUENCE "503 Bad sequence of commands."
#define RES_COMMAND_NOT_FOR_PARAM "504 Command not implemented for that parameter."
#define RES_NOT_LOGGED_IN "530 Not logged in."
#define RES_NEED_ACCOUNT_FOR_STORAGE "532 Need account for storing files."
#define RES_ACTION_NOT_TAKEN "550 Requested action not taken."
#define RES_PAGE_TYPE_UNKNOWN "551 Requested action aborted: page type unknown."
#define RES_EXCEEDED_STORAGE_ALLOCATION "552 Requested file action aborted. Exceeded storage allocation."
#define RES_INVALID_FILE_NAME "553 Requested action not taken. Invalid file name."
