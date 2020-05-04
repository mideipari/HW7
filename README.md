# Connor Deiparine
All results are on MinGW compiler which showed significantly faster speeds than visual studio. CPU is AMD 3900x OC'd to 4.4ghz.

Default:
Speed: 0.083s

Naive:
```C
unsigned int convert(const char *str){
    unsigned int value = 0;
    while(*str) {
        value = (value << 1) + (value << 3) + *(str++) - 48;
    }
    return value;
}

void convert_all(unsigned nlines, char *lines[], quote_t nums[])
{
  for (unsigned i = 0; i < nlines; i++) {
    nums[i] = convert(lines[i]);
  }
}
```
Speed: 0.01s

Next I tried unrolling the loop using switch but that was actually slower, here is the function as it may be faster on linux:
```C
unsigned int convert(char *str) {
    unsigned value = 0;
    int len = strlen(str);
    switch (len) { // handle up to 10 digits, assume we're 32-bit
        case 10:
            value += (str[len - 10] - '0') * 1000000000;
        case 9:
            value += (str[len - 9] - '0') * 100000000;
        case 8:
            value += (str[len - 8] - '0') * 10000000;
        case 7:
            value += (str[len - 7] - '0') * 1000000;
        case 6:
            value += (str[len - 6] - '0') * 100000;
        case 5:
            value += (str[len - 5] - '0') * 10000;
        case 4:
            value += (str[len - 4] - '0') * 1000;
        case 3:
            value += (str[len - 3] - '0') * 100;
        case 2:
            value += (str[len - 2] - '0') * 10;
        case 1:
            value += (str[len - 1] - '0');

    }
    return value;
}
```
Speed: 0.014s


Next I try using a lookup table, this method also turns out to be slower!
```C
static uint64_t decdigits[100] =
        {
                0U,0U,0U,0U,0U,0U,0U,0U,0U,0,
                1U,10U,100U,1000U,10000U,100000U,1000000U,10000000U,100000000U, 1000000000U,
                2U,20U,200U,2000U,20000U,200000U,2000000U,20000000U,200000000U, 2000000000U,
                3U,30U,300U,3000U,30000U,300000U,3000000U,30000000U,300000000U, 3000000000U,
                4U,40U,400U,4000U,40000U,400000U,4000000U,40000000U,400000000U, 4000000000U,
                5U,50U,500U,5000U,50000U,500000U,5000000U,50000000U,500000000U, 5000000000U,
                6U,60U,600U,6000U,60000U,600000U,6000000U,60000000U,600000000U, 6000000000U,
                7U,70U,700U,7000U,70000U,700000U,7000000U,70000000U,700000000U, 7000000000U,
                8U,80U,800U,8000U,80000U,800000U,8000000U,80000000U,800000000U, 8000000000U,
                9U,90U,900U,9000U,90000U,900000U,9000000U,90000000U,900000000U, 9000000000U,
        };

unsigned convert(const char *str)
{
    unsigned pos = strlen(str)-1;
    unsigned num = 0;
    while (*str) {
        num += decdigits[(*str++ - '0') * 10 + pos];
        pos--;
    }
    return num;
}
```
Speed: 0.018s

I tried a few different inline assembly methods but they were all slower than the naive result, it seems I am worse at assembly than the compiler. 

After that I couldn't think of anyways to improve the speed so I started googling.
I found this page which maybe of some [interest]("https://github.com/miloyip/itoa-benchmark"). There are many different ways to beat the naive method it seems but I did not want to just copy one. 


