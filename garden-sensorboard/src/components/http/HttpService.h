#ifndef __HTTP_SERVICE__
#define __HTTP_SERVICE__

#include "WifiConnector.h"

class HttpService {
   public:
    HttpService();
    int post(int lightIntensity, int temperatureMapped, String state);
};

#endif
