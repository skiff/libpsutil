# Detouring

```
libpsutil::memory::detour* function_detour_t;
void function_detour(int param1, int param2)
{
    function_detour_t->invoke<void>(param1, param2);
}

void init()
{
     function_detour_t = new libpsutil::memory::detour(0x00000000, function_detour);
}
```

#### HEN Warning
In order to use HEN you MUST call `libpsutil::memory::detour::force_stub_address(0x0)`. The address to pass to this function needs to be EMPTY, EXECUTABLE memory. This can be found by looking at the program segmentation of the game you are modding
