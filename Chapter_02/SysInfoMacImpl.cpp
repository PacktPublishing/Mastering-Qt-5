#include "SysInfoMacImpl.h"

#include <mach/vm_statistics.h>
#include <mach/mach_types.h>
#include <mach/mach_init.h>
#include <mach/mach_host.h>
#include <mach/vm_map.h>

SysInfoMacImpl::SysInfoMacImpl() :
    SysInfo()
{

}

void SysInfoMacImpl::init()
{
    mCpuLoadLastValues =  cpuRawData();
}

double SysInfoMacImpl::cpuLoadAverage()
{
    QVector<qulonglong> firstSample = mCpuLoadLastValues;
    QVector<qulonglong> secondSample = cpuRawData();
    mCpuLoadLastValues = secondSample;

    double overall = (secondSample[0] - firstSample[0])
        + (secondSample[1] - firstSample[1])
        + (secondSample[2] - firstSample[2]);

    double total = overall + (secondSample[3] - firstSample[3]);
    double percent = (overall / total) * 100.0;
    return qBound(0.0, percent, 100.0);
}

double SysInfoMacImpl::memoryUsed()
{
    vm_size_t pageSize;
    vm_statistics64_data_t vmStats;

    mach_port_t machPort = mach_host_self();
    mach_msg_type_number_t count = sizeof(vmStats) / sizeof(natural_t);
    host_page_size(machPort, &pageSize);

    host_statistics64(machPort,
                      HOST_VM_INFO,
                      (host_info64_t)&vmStats,
                      &count);

    qulonglong freeMemory = (int64_t)vmStats.free_count * (int64_t)pageSize;

    qulonglong totalMemoryUsed = ((int64_t)vmStats.active_count +
                             (int64_t)vmStats.inactive_count +
                             (int64_t)vmStats.wire_count) *  (int64_t)pageSize;

    qulonglong totalMemory = freeMemory + totalMemoryUsed;

    double percent = (double)totalMemoryUsed / (double)totalMemory * 100.0;
    return qBound(0.0, percent, 100.0);
}

QVector<qulonglong> SysInfoMacImpl::cpuRawData()
{
    host_cpu_load_info_data_t cpuInfo;
    mach_msg_type_number_t cpuCount = HOST_CPU_LOAD_INFO_COUNT;
    QVector<qulonglong> rawData;
    qulonglong totalUser = 0, totalUserNice = 0, totalSystem = 0, totalIdle = 0;
    host_statistics(mach_host_self(),
                    HOST_CPU_LOAD_INFO,
                    (host_info_t)&cpuInfo,
                    &cpuCount);

    for(unsigned int i = 0; i < cpuCount; i++) {
        unsigned int maxTicks = CPU_STATE_MAX * i;
        totalUser += cpuInfo.cpu_ticks[maxTicks + CPU_STATE_USER];
        totalUserNice += cpuInfo.cpu_ticks[maxTicks + CPU_STATE_SYSTEM];
        totalSystem += cpuInfo.cpu_ticks[maxTicks + CPU_STATE_NICE];
        totalIdle += cpuInfo.cpu_ticks[maxTicks + CPU_STATE_IDLE];
    }

    rawData.append(totalUser);
    rawData.append(totalUserNice);
    rawData.append(totalSystem);
    rawData.append(totalIdle);
    return rawData;
}
