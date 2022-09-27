void fn1(void *param)
{
    size_t xBytesSent;
    uint8_t ucArrayToSend[] = { 0, 1, 2, 3 };
    char *pcStringToSend = "Hello World\n";
    const TickType_t x100ms = pdMS_TO_TICKS( 100 );

    while(1)
    {
        printf("Sending String\n");
        xBytesSent = xStreamBufferSend( xStreamBuffer,
                                            ( void * ) pcStringToSend,
                                            strlen( pcStringToSend ), 0 );

        if( xBytesSent != strlen( pcStringToSend ) )
        {
            printf("Sent %d bytes of string\n", xBytesSent);
        }
        vTaskDelay(500);
  }
}

void fn2(void *param)
{
    while(1)
    {
        char ucRxData[ 20 ];
        size_t xReceivedBytes;
        const TickType_t xBlockTime = pdMS_TO_TICKS( 100 );

        /* Receive up to another sizeof( ucRxData ) bytes from the stream buffer.
        Wait in the Blocked state (so not using any CPU processing time) for a
        maximum of 100ms for the full sizeof( ucRxData ) number of bytes to be
        available. */
        xReceivedBytes = xStreamBufferReceive( xStreamBuffer,
                                               ( void * ) ucRxData,
                                               sizeof( ucRxData ) - 1,
                                               xBlockTime );

        if( xReceivedBytes > 0 )
        {
            ucRxData[xReceivedBytes] = '\0';
            printf("Received %s\n", ucRxData);
        }
        //vTaskDelay()
    }
}

static StreamBufferHandle_t xStreamBuffer;
xStreamBuffer = xStreamBufferCreate( 100, 1 );
