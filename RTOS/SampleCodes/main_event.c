EventGroupHandle_t xEventGroup;

void vEventSettingTask(void *param)
{
    while(1)
    {
          EventBits_t uxBits;
          printf("Setting the Task 1 Bit\n");
          /* Set bit 0 and bit 4 in xEventGroup. */   
          uxBits = xEventGroupSetBits(xEventGroup,    /* The event group being updated. */
                                        TASK1_BIT);
          vTaskDelay(500);
    }
}

void vEventReadingTask(void *param)
{
    EventBits_t uxBits;
    const TickType_t xTicksToWait = 100 / portTICK_PERIOD_MS;
    while(1)
    {
        printf("Waiting for the Event Bits to be set\n");
          /* Wait a maximum of 100ms for either bit 0 or bit 4 to be set within
          the event group.  Clear the bits before exiting. */
          uxBits = xEventGroupWaitBits(
                    xEventGroup,   /* The event group being tested. */
                    TASK1_BIT,     /* The bits within the event group to wait for. */
                    pdTRUE,        /* TASK1_BIT should be cleared before returning. */
                    pdFALSE,       /* An bit will do. */
                    xTicksToWait );/* Wait a maximum of 100ms for either bit to be set. */
          if (uxBits != 0)
          {
              printf("Event Bit is set\n");
          }
	}
}

  xEventGroup = xEventGroupCreate();

  xTaskCreate(vEventSettingTask, "bitsetter", 100, NULL, 1, NULL);
  xTaskCreate(vEventReadingTask, "bitreader", 100, NULL, 1, NULL);
//  configASSERT(status == pdPASS);
  vTaskStartScheduler();

