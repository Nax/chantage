int foo[0x1000];

void _start()
{
    foo[0x500] = 0xffff;
    return;
}
