#include "cpuinfo.h"
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include "fcntl.h"

int get_cores_count(void)
{
    char * cpu_dir = "/sys/devices/system/cpu/"; // 目录路径
    char * tar_char = "cpu";    // 目标字符

    DIR *dir = opendir(cpu_dir);
    if (dir == NULL) {
        printf("open /sys/devices/system/cpu/ failed\n");
        return 1;
    }

    int count = 0; // 计数器

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strlen(entry->d_name) == 4 && strstr(entry->d_name, tar_char) != NULL) {
            count++;
            //printf("%s\n", entry->d_name);
        }
    }

    closedir(dir);
    return count;
}

double get_cpu_freq_ghz(int cpuIndex, const char* str_name)
{
    char path[128];
    sprintf(path, "/sys/devices/system/cpu/cpu%d/cpufreq/scaling_%s_freq", cpuIndex, str_name);
    int fb = open(path, O_RDONLY);
    if(fb >= 0)
    {
        char content[128];
        read(fb, content, 1024);
        close(fb);
        int cpuFreq = 0;
        sscanf(content, "%d", &cpuFreq);
        double cpuFreqGHz = cpuFreq / 1000000.0;
        return cpuFreqGHz;
    }
    return -1;
}

int cpuinfo_main(void) {

    int core_count = get_cores_count(); // 计数器

    printf("cpu cores count：%d\n", core_count);

    for(int i = 0; i<core_count; i++)
    {
        double cur_freq = get_cpu_freq_ghz(i, "cur");
        double min_freq = get_cpu_freq_ghz(i, "min");
        double max_freq = get_cpu_freq_ghz(i, "max");
        printf("CPU%d, cur:%.2lf GHz, min:%.2lf GHz, max:%.2lf GHz \n", i, cur_freq, min_freq, max_freq);
    }

    return 0;
}
