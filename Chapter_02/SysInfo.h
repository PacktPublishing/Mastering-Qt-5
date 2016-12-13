#ifndef SYSINFO_H
#define SYSINFO_H


class SysInfo
{
public:
    static SysInfo& instance();
    virtual ~SysInfo();

    virtual void init() = 0;
    virtual double cpuLoadAverage() = 0;
    virtual double memoryUsed() = 0;

protected:
    explicit SysInfo();

private:
    SysInfo(const SysInfo& rhs);
    SysInfo& operator=(const SysInfo& rhs);
};

#endif // SYSINFO_H
