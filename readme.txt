Modes of operation.

1. Start and connect to socket. Read request, write response. If connection fails, die.

2. Start and listen on socket. On connection, read requests & write responses.
Doing 2. Concurrency... not a big deal.