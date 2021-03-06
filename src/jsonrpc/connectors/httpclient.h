/*************************************************************************
 * libjson-rpc-cpp
 *************************************************************************
 * @file    httpclient.h
 * @date    02.01.2013
 * @author  Peter Spiess-Knafl <peter.knafl@gmail.com>
 * @license See attached LICENSE.txt
 ************************************************************************/

#ifndef HTTPCLIENT_H_
#define HTTPCLIENT_H_

#include "../clientconnector.h"
#include "../exception.h"
#include <curl/curl.h>

namespace jsonrpc
{

    class HttpClient : public AbstractClientConnector
    {
        public:
            HttpClient(const std::string& url) throw (JsonRpcException);
            virtual ~HttpClient();

            virtual void SendMessage(const std::string& message, std::string& result) throw (JsonRpcException);

            virtual void SendMessage(const std::string& message, std::string& result, char *additional_headers[], int num_headers) throw (JsonRpcException);

            void SetUrl(const std::string& url);

            void SetConnectionTimeout(long timeout_secs);

            void SetTransferTimeout(long timeout_secs);

            void SetHttpsInsecure();
            
            void SetVerbose();

        private:
            std::string url;
            CURL* curl;
    };

} /* namespace jsonrpc */
#endif /* HTTPCLIENT_H_ */
