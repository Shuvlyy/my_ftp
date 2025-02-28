#pragma once

// 1xx - Positive Preliminary Replies
#define RES_FILE_STATUS_OK "150 File status okay; opening data connection."

// 2xx - Positive Completion Replies
#define RES_COMMAND_OK "200 {} okay."
#define RES_HELP "214 Help"
#define RES_SERVICE_READY "220 Service ready for new user."
#define RES_SERVICE_CLOSING "221 Logged out."
#define RES_TRANSFER_COMPLETE "226 Closing data connection."
#define RES_ENTERING_PASSIVE_MODE "227 Entering Passive Mode ({},{},{},{},{},{})."
#define RES_USER_LOGGED_IN "230 User logged in, proceed."
#define RES_FILE_ACTION_REQ "250 Requested file action okay, completed."
#define RES_PATH_CREATED "257 \"{}\""

// 3xx - Positive Intermediate Replies
#define RES_USER_OK_NEED_PASSWORD "331 User name okay, need password."
#define RES_NEED_ACCOUNT "332 Need account for login."
#define RES_CANT_OPEN_DATA "425 Can't open data connection."
#define RES_TRANSFER_ABORTED "426 Connection closed; transfer aborted."

// 5xx - Permanent Negative Completion Replies
#define RES_SYNTAX_ERROR "500 Syntax error, command unrecognized."
#define RES_SYNTAX_ERROR_PARAMS "501 Syntax error in parameters or arguments."
#define RES_BAD_COMMAND_SEQUENCE "503 Bad sequence of commands."
#define RES_NOT_LOGGED_IN "530 Not logged in."
#define RES_ACTION_NOT_TAKEN "550 Requested action not taken."
