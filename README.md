# BoardTest

## 开发板CPU性能测试

该项目集成 `内存速度测试` 和 `coremark测试`，以及一些温度，cpu频率信息显示。

编译运行：

```sh
scons
./boardtest.elf
```

结果示例：

```sh
--BOARD TEST--
cpu cores count：4
CPU0, cur:0.48 GHz, min:0.48 GHz, max:1.51 GHz 
CPU1, cur:0.48 GHz, min:0.48 GHz, max:1.51 GHz 
CPU2, cur:0.48 GHz, min:0.48 GHz, max:1.51 GHz 
CPU3, cur:0.48 GHz, min:0.48 GHz, max:1.51 GHz 
CPU temp 51.74 'C  
GPU temp 52.31 'C  
MEM temp 52.06 'C  
VE  temp 50.77 'C  
MemTotal: 1986.29 MB
MemFree: 1016.09 MB

-memspeed start-
memcpy(): rate = 5055.29 MB/s [cost: 5064 ms]
memset(): rate = 5511.30 MB/s [cost: 4645 ms]

-coremark start-
2K performance run parameters for coremark.
CoreMark Size    : 666
Total ticks      : 17747
Total time (secs): 17.747000
Iterations/Sec   : 3380.853102
Iterations       : 60000
Compiler version : GCC11.4.0
Compiler flags   : -O2 -Os
Memory location  : Please put data memory location here
                        (e.g. code in flash, data on heap etc)
seedcrc          : 0xe9f5
[0]crclist       : 0xe714
[0]crcmatrix     : 0x1fd7
[0]crcstate      : 0x8e3a
[0]crcfinal      : 0xbd59
Correct operation validated. See README.md for run and reporting rules.
CoreMark 1.0 : 3380.853102 / GCC11.4.0 -O2 -Os / Heap
```
