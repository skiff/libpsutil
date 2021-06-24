# Symbols
Symbols can be used for an easy way of defining game functions/variables at an address. The TOC is resolved automatically, so only the actual address needs to be specified

```
libpsutil::symbol<void(int)> Function{ 0x12345678 };
void call()
{
    Function(0);
}
```
