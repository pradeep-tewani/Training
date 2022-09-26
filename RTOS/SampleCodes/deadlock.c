void fn1(void *param)
{
    while(1)
    {
        xSemaphoreTake(mutex_1, portMAX_DELAY);
        printf("Task A Took Mutex 1\n");
        vTaskDelay(1 / portTICK_PERIOD_MS);

        //xSemaphoreTake(mutex_2, portMAX_DELAY);
#if 0
        if (xSemaphoreTake(mutex_2, 10 / portTICK_RATE_MS) != pdTRUE)
        {
            printf("Task A Giving up the mutex1\n");
            xSemaphoreGive(mutex_1);
            vTaskDelay(100 / portTICK_PERIOD_MS);
            continue;
        }
#endif
        printf("Task A Took Mutex 2\n");
        vTaskDelay(1 / portTICK_PERIOD_MS);

        printf("Task A Doing some work\n");
        vTaskDelay(500 / portTICK_PERIOD_MS);

        xSemaphoreGive(mutex_1);
        xSemaphoreGive(mutex_2);

        printf("Task A going to sleep\n");
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

void fn2(void *param)
{
    while(1)
    {
        xSemaphoreTake(mutex_2, portMAX_DELAY);
        printf("Task B Took Mutex 2\n");
        vTaskDelay(1 / portTICK_PERIOD_MS);

        xSemaphoreTake(mutex_1, portMAX_DELAY);
        printf("Task B Took Mutex 2\n");
        vTaskDelay(1 / portTICK_PERIOD_MS);

        printf("Task B Doing some work\n");
        vTaskDelay(500 / portTICK_PERIOD_MS);

        xSemaphoreGive(mutex_2);
        xSemaphoreGive(mutex_1);

        printf("Task B going to sleep\n");
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

