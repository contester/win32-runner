#pragma once

#include <boost/function.hpp>
#include "rpc_object.h"

namespace contester {


typedef boost::function<void (boost::shared_ptr<Rpc>)> RpcMethod;


};

