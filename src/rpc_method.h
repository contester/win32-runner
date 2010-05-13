#pragma once

#include <boost/function.hpp>

namespace contester {
class Rpc;

typedef boost::function<void (boost::shared_ptr<Rpc>)> RpcMethod;
};
