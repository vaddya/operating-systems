#include <windows.h>
#include <winioctl.h>
#include <stdio.h>

BOOL GetDriveGeometry(HANDLE device, DISK_GEOMETRY* pdg)
{
    return DeviceIoControl(
        device,                        // device to be queried
        IOCTL_DISK_GET_DRIVE_GEOMETRY, // operation to perform
        NULL, 0,                       // no input buffer
        pdg, sizeof(*pdg),             // output buffer
        NULL,                          // # bytes returned
        NULL);                         // synchronous I/O
}

ULONGLONG DiskSizeInBytes(DISK_GEOMETRY* pdg) {
    return pdg->Cylinders.QuadPart * pdg->TracksPerCylinder * pdg->SectorsPerTrack * pdg->BytesPerSector;
}

int wmain(int argc, wchar_t* argv[])
{
    const wchar_t* driveName;
    if (argc < 2)
    {
        driveName = L"C:";
    }
    else
    {
        driveName = argv[1];
    }

    LPWSTR drive = new WCHAR[100];
    wsprintfW(drive, L"\\\\.\\%s", driveName);
    HANDLE device = CreateFileW(
        drive,                                  // drive to open
        0,                                      // no access to the drive
        FILE_SHARE_READ | FILE_SHARE_WRITE,     // share mode
        NULL,                                   // default security attributes
        OPEN_EXISTING,                          // disposition
        0,                                      // file attributes
        NULL);                                  // do not copy file attributes

    if (device == INVALID_HANDLE_VALUE)
    {
        wprintf(L"Unable to open drive: %d", GetLastError());
        return 1;
    }

    DISK_GEOMETRY pdg = { 0 }; // disk drive geometry structure
    if (!GetDriveGeometry(device, &pdg))
    {
        wprintf(L"GetDriveGeometry failed. Error %ld.\n", GetLastError());
        return 1;
    }

    wprintf(L"Drive path      = %ws\n", drive);
    wprintf(L"Cylinders       = %I64d\n", pdg.Cylinders);
    wprintf(L"Tracks/cylinder = %ld\n", (ULONG)pdg.TracksPerCylinder);
    wprintf(L"Sectors/track   = %ld\n", (ULONG)pdg.SectorsPerTrack);
    wprintf(L"Bytes/sector    = %ld\n", (ULONG)pdg.BytesPerSector);

    ULONGLONG diskSize = DiskSizeInBytes(&pdg);
    wprintf(L"Disk size       = %I64d (Bytes)\n", diskSize);
    wprintf(L"                = %.2f (Gb)\n", (double) diskSize / (1024 * 1024 * 1024));

    CloseHandle(device);

    return 0;
}
