#ifndef _ERRORS_H_
#define _ERRORS_H_

namespace CentralHeating{
    enum Error {
        OK,
        FIRING_UP_TIMEOUT,
        STABILIZATION_TIMEOUT,
        FUMES_TEMPERATURE_TOO_HIGH
    };
};

#endif