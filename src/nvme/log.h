// SPDX-License-Identifier: LGPL-2.1-or-later
/*
 * Copyright (c) 2021 Martin Wilck, SUSE LLC
 */
#ifndef _LOG_H
#define _LOG_H

#include <stdbool.h>
#include <syslog.h>

#ifndef MAX_LOGLEVEL
#  define MAX_LOGLEVEL LOG_DEBUG
#endif
#ifndef DEFAULT_LOGLEVEL
#  define DEFAULT_LOGLEVEL LOG_NOTICE
#endif

#if (LOG_FUNCNAME == 1)
#define __nvme_log_func __func__
#else
#define __nvme_log_func NULL
#endif

extern char *nvme_log_message;

void __attribute__((format(printf, 4, 5)))
__nvme_msg(nvme_root_t r, int lvl, const char *func, const char *format, ...);

#define nvme_msg(r, lvl, format, ...)					\
	do {								\
		if ((lvl) <= MAX_LOGLEVEL)				\
			__nvme_msg(r, lvl, __nvme_log_func,		\
				   format, ##__VA_ARGS__);		\
	} while (0)

/**
 * nvme_init_logging() - initialize logging
 * @r: nvme_root_t context
 * @lvl: logging level to set
 * @log_pid: boolean to enable logging of the PID
 * @log_tstamp: boolean to enable logging of the timestamp
 *
 * Sets the default logging variables for the library.
 */
void nvme_init_logging(nvme_root_t r, int lvl, bool log_pid, bool log_tstamp);

#endif /* _LOG_H */
