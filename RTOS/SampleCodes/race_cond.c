void fn2(void *param)
{
    int local_var;
    while(1)
    {
        local_var = shared_var;
        local_var++;
        vTaskDelay(600 / portTICK_PERIOD_MS);
        shared_var = local_var;
        printf("%d\n", shared_var);
    }
}

void fn4(void *param)
{
    int local_var;
    while(1)
    {
        local_var = shared_var;
        local_var++;
        vTaskDelay(300 / portTICK_PERIOD_MS);
        shared_var = local_var;
        printf("%d\n", shared_var);
    }
}

