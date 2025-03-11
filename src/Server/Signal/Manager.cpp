#include "Server/Server.hpp"
#include "Server/Signal/Manager.hpp"
#include "Server/Signal/Handlers/Term.hpp"
#include "Server/Signal/Handlers/Int.hpp"

#include <csignal>

namespace ftp::server::sig
{
    Manager* Manager::instance = nullptr;
}

ftp::server::sig::Manager::Manager
(
    Server *parent
)
    : _parent(parent)
{
    instance = this;

    this->registerHandlers();
    this->setupListener();
}

void
ftp::server::sig::Manager::registerHandlers()
{
    this->registerHandler(std::make_unique<Term>());
    this->registerHandler(std::make_unique<Int>());
}

void
ftp::server::sig::Manager::registerHandler
(
    std::unique_ptr<IHandler> handler
)
{
    this->_handlers.insert(std::make_pair(
        handler->getSignalNumber(),
        std::move(handler)
    ));
}

void
ftp::server::sig::Manager::setupListener
()
{
    for (const auto &[signalNumber, handler] : this->_handlers) {
        signal(
            signalNumber,
            [](const int signum) { Manager::dispatchHandler(signum); }
        );
    }
}

void
ftp::server::sig::Manager::dispatchHandler
(
    const int signum
)
{
    const auto it = instance->_handlers.find(signum);

    if (it != instance->_handlers.end()) {
        it->second->handle(instance->_parent);
    }
}
