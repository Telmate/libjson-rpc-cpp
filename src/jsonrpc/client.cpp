/*************************************************************************
 * libjson-rpc-cpp
 *************************************************************************
 * @file    client.cpp
 * @date    03.01.2013
 * @author  Peter Spiess-Knafl <peter.knafl@gmail.com>
 * @license See attached LICENSE.txt
 ************************************************************************/

#include "client.h"
#include "rpcprotocolclient.h"
#include "exception.h"


namespace jsonrpc
{
    Client::Client(AbstractClientConnector* connector)
            : connector(connector)
    {
    }

    Client::~Client()
    {
        delete this->connector;
    }

    void Client::CallMethod(const std::string &name, const Json::Value &parameter, Json::Value& result) throw(JsonRpcException)
    {
        char *additional_headers[0];
        result = CallMethod(name, parameter, additional_headers, 0);
    }
    
    Json::Value Client::CallMethod(const std::string& name,
                                   const Json::Value& parameter) throw(JsonRpcException)
    {
        Json::Value result;
        this->CallMethod(name, parameter, result);
        return result;
    }

    Json::Value Client::CallMethod(const std::string& name,
                                   const Json::Value& parameter,
                                   char *additional_headers[],
                                   int num_headers) throw(JsonRpcException)
    {
        Json::Value result;
        std::string request, response;
        protocol.BuildRequest(name, parameter, request, false);
        connector->SendMessage(request, response, additional_headers, num_headers);
        protocol.HandleResponse(response, result);
        return result;
    }
    
    void Client::CallNotification(const std::string& name, const Json::Value& parameter) throw(JsonRpcException)
    {
        std::string request, response;
        protocol.BuildRequest(name, parameter, request, true);
        connector->SendMessage(request, response);
    }

} /* namespace jsonrpc */
