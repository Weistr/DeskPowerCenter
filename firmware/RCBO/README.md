# mcu_arm_temp
mcu template project

# tms320 config(ccs)
ccs选择CCSWORKSPACE,从Target/TMS320Fxx导入project


# ccs新增芯片
 ccs创建新project,选择路径为target/xxxx
添加文件夹：File->new->Folder->advance->linkFolder
添加头文件：project->build->c2000compiler->include options

# gd32e230配置
选择c_cpp_properties.json, 右下角选择gd32e230, 在includePath头文件选择自己电脑编译器路径

编译方法：
根目录：
cmake --preset GD32E230初始化
cmake --build --preset GD32E230构建
cmake --build --preset GD32E230 --clean-first
旧方法：进入build文件夹执行：cmake -G 'MinGW Makefiles' ..\..\..   再执行mingw32-make

GD32e23x时钟选择：见rcu.h
下面是旧方法
在system_gd32e23x.c:
/* select a system clock by uncommenting the following line */
//#define __SYSTEM_CLOCK_8M_HXTAL              (__HXTAL)
//#define __SYSTEM_CLOCK_8M_IRC8M              (__IRC8M)
#define __SYSTEM_CLOCK_72M_PLL_HXTAL         (uint32_t)(72000000)
//#define __SYSTEM_CLOCK_72M_PLL_IRC8M_DIV2    (uint32_t)(72000000)
可选择时钟源
晶振频率选择 在gd32e23x.h，有定义#define HXTAL_VALUE    ((uint32_t)12000000)
最后在system_gd32e23x.c设置PLL   
 /* PLL = HXTAL * 9 = 72 MHz */
    RCU_CFG0 &= ~(RCU_CFG0_PLLSEL | RCU_CFG0_PLLMF | RCU_CFG0_PLLDV);
    RCU_CFG0 |= (RCU_PLLSRC_HXTAL | RCU_PLL_MUL6);