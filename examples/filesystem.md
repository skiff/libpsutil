#Filesystem

### Writing to a file
```
void init()
{
    std::string data = "write me to a file!";
    libpsutil::filesystem::write_file("/dev_hdd0/tmp/filename.txt", data.data(), data.length());
}
```

### Reading from a file
```
void init()
{
    char data[100];
    libpsutil::filesystem::read_file("/dev_hdd0/tmp/filename.txt", data, 100);
}
```
