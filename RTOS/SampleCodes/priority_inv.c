void taskl(void *params)
{
    TickType_t timestamp;

    while(1)
    {
        printf("Task L trying to take lock ...\n");
        timestamp = xTaskGetTickCount() * portTICK_PERIOD_MS;
        xSemaphoreTake(lock, portMAX_DELAY);

        printf("Task L got lock. Spent ");
          printf("%lu", (xTaskGetTickCount() * portTICK_PERIOD_MS) - timestamp);
            printf(" ms waiting for lock. Doing some work...\n");

            // Hog the processor for a while doing nothing
            timestamp = xTaskGetTickCount() * portTICK_PERIOD_MS;
            while ( (xTaskGetTickCount() * portTICK_PERIOD_MS) - timestamp < cs_wait);

            // Release lock
            printf("Task L releasing lock.\n");
            xSemaphoreGive(lock);

            // Go to sleep
            vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

void taskm(void *parameters) {

  TickType_t timestamp;
  vTaskDelay(2 / portTICK_PERIOD_MS);

  // Do forever
  while (1) {

    // Hog the processor for a while doing nothing
    printf("Task M doing some work...\n");
    timestamp = xTaskGetTickCount() * portTICK_PERIOD_MS;
    while ( (xTaskGetTickCount() * portTICK_PERIOD_MS) - timestamp < med_wait);

    // Go to sleep
    printf("Task M done!\n");
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void taskh(void *parameters) {

  TickType_t timestamp;
  vTaskDelay(4 / portTICK_PERIOD_MS);

  // Do forever
  while (1) {

    // Take lock
    printf("Task H trying to take lock...\n");
    timestamp = xTaskGetTickCount() * portTICK_PERIOD_MS;
    xSemaphoreTake(lock, portMAX_DELAY);
    // Say how long we spend waiting for a lock
   printf("Task H got lock. Spent \n");
   printf("%lu\n", (xTaskGetTickCount() * portTICK_PERIOD_MS) - timestamp);
     printf(" ms waiting for lock. Doing some work...\n");

     // Hog the processor for a while doing nothing
     timestamp = xTaskGetTickCount() * portTICK_PERIOD_MS;
     while ( (xTaskGetTickCount() * portTICK_PERIOD_MS) - timestamp < cs_wait);

     // Release lock
     printf("Task H releasing lock.\n");
     xSemaphoreGive(lock);

     // Go to sleep
     vTaskDelay(500 / portTICK_PERIOD_MS);
   }
}

