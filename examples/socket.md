# Sockets

### TCP Socket
```
void tcp_example()
{
    libpsutil::network::socket* net = new libpsutil::network::socket("1.2.3.4", 1234);
    if(net->connect())
    {
        std::string send_data = "111111111111111111";
        net->send(send_data.data(), send_data.length();
        
        char recv_data[100];
        net->receive(recv_data, 100);
    }
    
    net->close();
    delete net;
}
```

### UDP Socket
```
void udp_example()
{
    libpsutil::network::socket* net = new libpsutil::network::socket("1.2.3.4", 1234, libpsutil::network::socket_type::SOCKET_TYPE_UDP);
    if(net->connect())
    {
        std::string send_data = "111111111111111111";
        net->send(send_data.data(), send_data.length();
        
        char recv_data[100];
        net->receive(recv_data, 100);
    }
    
    net->close();
    delete net;
}
```
