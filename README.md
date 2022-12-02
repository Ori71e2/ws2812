# ws2812
ws2812在stm32平台上的运行代码

# 注意事项
本代码只在stm32f103c8t6运行；
要注意堆栈溢出问题，若灯珠数量多需要在startup文件中修改Heap_Size及Stack_Size，否则程序会跑飞。