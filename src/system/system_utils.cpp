
/////////////////////////////////
//                             //
// Copyright (c) 2022 Selenika //
//                             //
/////////////////////////////////

#include <syslog.h>

#include <stdexcept>
#include <sstream>

#include <boost/asio.hpp>

#include "logging/logging.h"

#include "./definitions.h"
#include "./system_utils.h"

namespace {

const char* formatErrorMessage(const char* error) {
    std::stringstream ss;
    ss << kErrorRunAsServiceFailed << " " << error << std::endl;
    return ss.str().c_str();
}

}

void runAsService(boost::asio::io_context &ioc, boost::asio::signal_set& signals, const char *output) {
    SLNK_LOG_DEBUG() << "Becoming a daemon...";

    // Register signal handlers so that the daemon may be shut down. You may
    // also want to register for other signals, such as SIGHUP to trigger a
    // re-read of a configuration file.
    // boost::asio::signal_set signals(ioc, SIGINT, SIGTERM);
    signals.async_wait(
        [&](boost::system::error_code /*ec*/, int /*signo*/) {
            ioc.stop();
        });

    SLNK_LOG_DEBUG() << "First fork...";

    // Inform the io_context that we are about to become a daemon. The
    // io_context cleans up any internal resources, such as threads, that may
    // interfere with forking.
    ioc.notify_fork(boost::asio::io_context::fork_prepare);

    // Fork the process and have the parent exit. If the process was started
    // from a shell, this returns control to the user. Forking a new process is
    // also a prerequisite for the subsequent call to setsid().
    if (pid_t pid = fork()) {
        if (pid > 0) {
            // We're in the parent process and need to exit.
            //
            // When the exit() function is used, the program terminates without
            // invoking local variables' destructors. Only global variables are
            // destroyed. As the io_context object is a local variable, this means
            // we do not have to call:
            //
            //   io_context.notify_fork(boost::asio::io_context::fork_parent);
            //
            // However, this line should be added before each call to exit() if
            // using a global io_context object. An additional call:
            //
            //   io_context.notify_fork(boost::asio::io_context::fork_prepare);
            //
            // should also precede the second fork().
            exit(0);
        } else {
            // TODO(qqq): define error strings
            syslog(LOG_ERR | LOG_USER, "First fork failed: %m");
            SLNK_LOG_ERROR() << "First fork failed";
            throw std::runtime_error(formatErrorMessage("First fork failed"));
        }
    }

    // Make the process a new session leader. This detaches it from the
    // terminal.
    setsid();

    // A process inherits its working directory from its parent. This could be
    // on a mounted filesystem, which means that the running daemon would
    // prevent this filesystem from being unmounted. Changing to the root
    // directory avoids this problem.
    chdir("/");

    // The file mode creation mask is also inherited from the parent process.
    // We don't want to restrict the permissions on files created by the
    // daemon, so the mask is cleared.
    umask(0);

    SLNK_LOG_DEBUG() << "Second fork...";
    // A second fork ensures the process cannot acquire a controlling terminal.
    if (pid_t pid = fork()) {
        if (pid > 0) {
            exit(0);
        } else {
            syslog(LOG_ERR | LOG_USER, "Second fork failed: %m");
            SLNK_LOG_ERROR() << "Second fork failed";
            throw std::runtime_error(formatErrorMessage("Second fork failed"));
        }
    }

    // Close the standard streams. This decouples the daemon from the terminal
    // that started it.
    close(0);
    close(1);
    close(2);

    // We don't want the daemon to have any standard input.

    SLNK_LOG_DEBUG() << "Detauch standard input";
    if (open("/dev/null", O_RDONLY) < 0) {
        syslog(LOG_ERR | LOG_USER, "Unable to open /dev/null: %m");
        SLNK_LOG_ERROR() << "Unable to open /dev/null";
        throw std::runtime_error(formatErrorMessage("Unable to open /dev/null"));
    }

    // Send standard output to a log file.
    SLNK_LOG_DEBUG() << "Send standard output to a log file";
    //  const char *output = clo.GetPathLog().c_str();
    const int flags = O_WRONLY | O_CREAT | O_APPEND;
    const mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    if (open(output, flags, mode) < 0) {
        syslog(LOG_ERR | LOG_USER, "Unable to open output file %s: %m", output);
        throw std::runtime_error(formatErrorMessage("Unable to open output file"));
    }

    // Also send standard error to the same log file.
    if (dup(1) < 0) {
        syslog(LOG_ERR | LOG_USER, "Unable to dup output descriptor: %m");
        SLNK_LOG_ERROR() << "Unable to dup output descriptor";
        throw std::runtime_error(formatErrorMessage("Unable to dup output descriptor"));
    }

    // Inform the io_context that we have finished becoming a daemon. The
    // io_context uses this opportunity to create any internal file descriptors
    // that need to be private to the new process.
    ioc.notify_fork(boost::asio::io_context::fork_child);

    // The io_context can now be used normally.
    syslog(LOG_INFO | LOG_USER, "Peer server daemon is ready");
}
