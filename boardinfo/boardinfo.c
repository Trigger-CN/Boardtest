#include "boardinfo.h"
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include "fcntl.h"

char* gpu_dir = "/sys/class/hwmon/hwmon0/temp1_input";
char* ve_dir = "/sys/class/hwmon/hwmon1/temp1_input";
char* cpu_dir = "/sys/class/hwmon/hwmon2/temp1_input";
char* ddr_dir = "/sys/class/hwmon/hwmon3/temp1_input";

double get_hwmon_temp(char* temp_dir)
{
    int f = open(temp_dir, O_RDONLY);
    if(f >= 0)
    {
        char content[128];
        read(f, content, 1024);
        close(f);
        int temp = 0;
        sscanf(content, "%d", &temp);
        return (double)temp / 1000.0;
    }
    return -10000;
}

void print_all_temp(void)
{
    double gpu_temp = get_hwmon_temp(gpu_dir);
    double ve_temp = get_hwmon_temp(ve_dir);
    double cpu_temp = get_hwmon_temp(cpu_dir);
    double ddr_temp = get_hwmon_temp(ddr_dir);
    printf("CPU temp %5.2lf \'C  \nGPU temp %5.2lf \'C  \nMEM temp %5.2lf \'C  \nVE  temp %5.2lf \'C  \n",
    cpu_temp,gpu_temp,ddr_temp,ve_temp);
}

void get_mem_free(int *total, int *free)
{
    FILE *file;
    char line[128];
    int memTotal = 0, memFree = 0;

    // 打开/proc/meminfo文件
    file = fopen("/proc/meminfo", "r");
    if (file == NULL) {
        printf("无法打开/proc/meminfo文件\n");
    }

    // 逐行读取文件内容
    while (fgets(line, sizeof(line), file)) {
        // 查找包含"MemTotal"的行
        if (strstr(line, "MemTotal")) {
            // 解析行中的数值
            sscanf(line, "%*s %u", &memTotal);
        }
        // 查找包含"MemFree"的行
        if (strstr(line, "MemFree")) {
            // 解析行中的数值
            sscanf(line, "%*s %u", &memFree);
        }

        // 如果已经找到了所需的值，则退出循环
        if (memTotal > 0 && memFree > 0) {
            *total = memTotal;
            *free = memFree;
            break;
        }
    }

    // 关闭文件
    fclose(file);
}

void print_mem_free(void)
{
    int memTotal = 0, memFree = 0;
    get_mem_free(&memTotal, &memFree);
    printf("MemTotal: %.2f MB\n", (float)memTotal / 1024);
    printf("MemFree: %.2f MB\n", (float)memFree / 1024);
}
