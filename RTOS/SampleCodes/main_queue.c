void fn1(void *param)
{
    int i = 0;
    while(1)
    {
        xQueueReceive( xQueue1, &xReceivedFromQueue1, portMAX_DELAY);
        printf("Value from Queue1 is %u\n", xReceivedFromQueue1);
        i++;
	}
}

void fn2(void *param)
{
    uint32_t num = 0;
    while(1)
    {
        printf("Sending Data on Queue1\n");
        xQueueSend(xQueue1, (void *)&num, portMAX_DELAY);
        //vTaskDelay(500);
        num++;
	}
}

static QueueHandle_t xQueue1;
xQueue1 = xQueueCreate(10, sizeof(uint32_t));

