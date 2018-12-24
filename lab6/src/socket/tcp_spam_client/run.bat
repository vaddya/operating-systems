FOR /L %%G IN (1,1,%3) DO (
    START /B socket_tcp_spam_client.exe %1 %2 "Message from %%G" > NUL
)