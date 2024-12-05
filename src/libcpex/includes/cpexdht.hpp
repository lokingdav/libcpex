#ifndef CPEX_DHT
#define CPEX_DHT

#include "base.hpp"

namespace libcpex {
    struct CpexNode {
        string id;
        string ipAddress;
        string baseUrl;
        bool isHealthy = false;
    };

    typedef vector<CpexNode> CpexNodes;

    class CpexDHT {
        private:
            vector<CpexNode> nodes;

        public:
            CpexDHT();
            CpexDHT(vector<CpexNode> nodes);
            vector<CpexNode> FindNodes(string key, int replication_params = 3);
            vector<CpexNode> FindNodes(vector<uint8_t>key, int replication_params = 3);
            CpexNode Ping(string key);
            CpexNode Ping(vector<uint8_t>key);
    };
}

#endif // CPEX_DHT
