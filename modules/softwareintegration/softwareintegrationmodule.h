/*****************************************************************************************
 *                                                                                       *
 * OpenSpace                                                                             *
 *                                                                                       *
 * Copyright (c) 2014-2020                                                               *
 *                                                                                       *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this  *
 * software and associated documentation files (the "Software"), to deal in the Software *
 * without restriction, including without limitation the rights to use, copy, modify,    *
 * merge, publish, distribute, sublicense, and/or sell copies of the Software, and to    *
 * permit persons to whom the Software is furnished to do so, subject to the following   *
 * conditions:                                                                           *
 *                                                                                       *
 * The above copyright notice and this permission notice shall be included in all copies *
 * or substantial portions of the Software.                                              *
 *                                                                                       *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,   *
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A         *
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT    *
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF  *
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE  *
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                                         *
 ****************************************************************************************/

#ifndef __OPENSPACE_MODULE_SOFTWAREINTEGRATION___SOFTWAREINTEGRATIONMODULE___H__
#define __OPENSPACE_MODULE_SOFTWAREINTEGRATION___SOFTWAREINTEGRATIONMODULE___H__

#include <openspace/util/openspacemodule.h>
#include <openspace/documentation/documentation.h>
#include <openspace/network/messagestructures.h>
#include <openspace/util/concurrentqueue.h>
#include <ghoul/io/socket/tcpsocket.h>
#include <ghoul/io/socket/tcpsocketserver.h>
#include <ghoul/misc/exception.h>
#include <atomic>
#include <string>
#include <unordered_map>
#include <vector>

namespace openspace {

class Connection {
public:
    // Connection
    enum class Status : uint32_t {
        Disconnected = 0,
        Connecting
    };

    Connection(std::unique_ptr<ghoul::io::TcpSocket> socket);

    // Connection
    bool isConnectedOrConnecting() const;
    void disconnect();
    ghoul::io::TcpSocket* socket();

private:
    // Connection
    std::unique_ptr<ghoul::io::TcpSocket> _socket;

};

class SoftwareIntegrationModule : public OpenSpaceModule {
public:
    constexpr static const char* Name = "SoftwareIntegration";

    SoftwareIntegrationModule();
    virtual ~SoftwareIntegrationModule() = default;

    // Server
    void start(int port);
    void setDefaultHostAddress(std::string defaultHostAddress);
    std::string defaultHostAddress() const;
    void stop();
    //size_t nConnections() const;

    std::vector<documentation::Documentation> documentations() const override;
    scripting::LuaLibrary luaLibrary() const override;

    static const unsigned int ProtocolVersion;
private:
    // Server
    struct Peer {
        size_t id;
        std::string name;
        Connection connection;
        Connection::Status status;
        std::thread thread;
    };

    // Server
    bool isConnected(const Peer& peer) const;
    void disconnect(Peer& peer);
    //void setName(Peer& peer, std::string name);
    //void assignHost(std::shared_ptr<Peer> newHost);
    //void handleDisconnection(std::shared_ptr<Peer> peer);
    void handleNewPeers();
    std::shared_ptr<Peer> peer(size_t id);
    //void handlePeer(size_t id);
    std::unordered_map<size_t, std::shared_ptr<Peer>> _peers;
    mutable std::mutex _peerListMutex;
    std::thread _serverThread;
    ghoul::io::TcpSocketServer _socketServer;
    size_t _nextConnectionId = 1;
    std::atomic_bool _shouldStop = false;
    std::atomic_size_t _nConnections = 0;
    std::atomic_size_t _hostPeerId = 0;
    mutable std::mutex _hostInfoMutex;
    std::string _hostName;
    std::string _defaultHostAddress;

    void internalInitialize(const ghoul::Dictionary&) override;
    void internalDeinitializeGL() override;
};

} // namespace openspace

#endif // __OPENSPACE_MODULE_SOFTWAREINTEGRATION___SOFTWAREINTEGRATIONMODULE___H__
