void func(int a, int c)
{
    int sum, i;
    int b[82];
    //sum = a + b;
    for (i = 0; i < 82; i++)
        b[i] = i++;

    //func1(sum);
    printf("sum = %d\n", b[30]);
}

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
    printf("Task %s has offended\n", pcTaskName);
}

void fn1(void *param)
{
    int stack_rem;
    //int a[50], i;

    while(1)
    {
        //for (i = 0; i < 50; i++)
            //a[i] += 9;
        stack_rem = uxTaskGetStackHighWaterMark(NULL);
        printf("stack_rem = %d\n", stack_rem);
        func(3, 4);
        stack_rem = uxTaskGetStackHighWaterMark(NULL);
        printf("stack_rem 2 = %d\n", stack_rem);
}
