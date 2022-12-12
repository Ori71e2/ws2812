# ws2812
ws2812在stm32平台上的运行代码

# 第一版
第一版主要就是实现ws2812芯片控制的LED灯，相关资料见datasheet文件夹

# 第一版注意事项
本代码只在stm32f103c8t6运行；
要注意堆栈溢出问题，若灯珠数量多需要在startup文件中修改Heap_Size及Stack_Size，否则程序会跑飞。
本电路连接，pwm信号输出为GPIOB6端口。
ws2812灯串连接时，其电源正极要单独供电，负极要和stm32板子负极共地，如若ws2812灯串无法用stm32正极带动起来。
我是用手机充电器引出正负极，正极连接灯串，负极与stm32共地。

# 第二版正在进行
1）引入DSP库。
注意：要配置宏ARM_MATH_CM3（点击魔法棒那个图标，在C/C++里加入；本项目共USE_STDPERIPH_DRIVER,ARM_MATH_CM3, ARM_MATH_MATRIX_CHECK, ARM_MATH_ROUNDING）

2）ADC + DMA + FFT实现频谱
FFT频谱
注： 存在的错误，keil空间不足，.\Objects\template.axf: Error: L6406E: No space in execution regions with .ANY selector mat ———— 修改编译优化等级为level 2(-O2)级别

# 各版本源码
1）第一版
链接：https://pan.baidu.com/s/1xwEIkTf5GDss1KvS9qHsdw?pwd=z04y 
提取码：z04y 
复制这段内容后打开百度网盘手机App，操作更方便哦

或者

见第一个release

2）第二版


# 感谢
https://github.com/Silencer2K/stm32f10x-ws2812b-lib.git
https://github.com/WangYooNestik/STM32F10X-ADC-FFT.git