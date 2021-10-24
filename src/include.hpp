#pragma once

#include <string>
#include <cstring>
#include <sstream>
#include <array>
#include <iostream>
#include <vector>
#include <memory>
#include <chrono>
#include <thread>
#include <map>
#include <functional>
#include <random>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "util/clock.hpp"
#include "util/singleton.hpp"
#include "util/logger.hpp"
#include "util/common_util.hpp"

#include "streams/base_stream.hpp"
#include "streams/bank.hpp"

#include "udp/udp_socket.hpp"
#include "udp/udp_stream.hpp"

#include "../config.hpp"

#define MP_VER "1.0.5.2"
#define CL_VER 2

#include "server/requests/requests.hpp"
#include "server/haven.hpp"
