# Software CRC

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=64

[PDF](https://uva.onlinejudge.org/external/1/p128.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA128/2ed0a2961b881ebefab6464e3345553e002df0c8.png)

## 样例 #1

### 输入

```
this is a test
A
#```

### 输出

```
77 FD
00 00
0C 86```

# 题解

## 作者：Erick。 (赞：1)

发现没人发题解，我赶紧发一篇。这道题其实挺容易，我的代码有点长，请见谅。


分析
实际在通迅中使用的CRC校验码要比题目中描述的复杂得多，涉及的知识点也很广，这里仅介绍与题目相关的算法，了解其它内容请参见“循环冗余校验”(维基百科)。

本题最主要的算法就是将字符串看作一个很长的整数，然后执行除法取余。简单来讲，就是要实现大数的除法。我们先来看10进制的例子，请用笔计算：2357 ÷ 6。我们只关心余数，第一次在3上面试商3，下面得余数5；用5 × 10 + 5 = 55作为第二次被除数，商9得余数1；用1 × 10 + 7 = 17作第三次被除数，商2余5。注意到每次被除数的每一位去除以除数6得到的余数都要累计到下一位（乘以10再加下一位）。只要能保证被除数中每一位都大于除数，就可以避免出现借位的情况。将笔算除法推广到n进制，即得到大数除法。设p为一个n进制整数作为被除数，q为小于n的除数（即选择的校验码生成数）：

p = a0n0 + a1n1 + ... + aknk

现在要求的是p ÷ q的余数rk，即r0 = p mod q，先从rk开始向前计算：

rk = aknk mod q
rk-1 = (rkn + ak-1nk-1) mod q
...
r0 = (r1n + a0n0) mod q

根据此递推公式就很容易处理大数的除法了。为了方便实现，在程序中可以使用216=65535进制或232=4294967295进制。这样在计算余数时，无需将上一个r乘以进制，只要左移16位或32位即可，最大限度的利用了寄存器和CPU的特性。

求得余数后，下一步就是要将余数转为校验码。设校验码为c，那么应满足：

(a0n0 + a1n1 + ... + aknk + c) mod q = 0

前面已求得：

(a0n0 + a1n1 + ... + aknk) mod q = r

显然，c的值不止一个，但最小的正值c可用如下公式来计算：

c = q - (nr mod q)

上式很容易理解，就不赘述了。至此，CRC码计算完成。这里还有一个要注意的地方，我们一般写程序和编译的机器环境（包括OJ系统运行的环境）都是x86架构的，也就意味着字节序是little-endian， 即在存储器中的所有整型数值都是高位在前低位在后。比如32位16进制数：AF045Bh，在内存中的顺序应该是：

5B 04 AF 00

如果我们直接将字符串的指针转为int型指针进行计算就会算错。必须先对每一组字节（整型变量大小的一组）先进行反转再作运算。

 
 
上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(void) {
    typedef unsigned short word;
    char Bits[1032]; //存储输入的字符串
    cin.sync_with_stdio(false); //输入的数据量很大，关闭同步以加速
    cout << setbase(16) << setiosflags(ios::uppercase) << setfill('0');
    //循环处理输入的每一行字符串
    for (string Line; getline(cin, Line) && Line[0] != '#'; cout << endl) {
        word nGen = 34943, nLen = Line.length(), *pBit = (word*)Bits;
        //将字符串转存到静态数组中。x86的CPU字节序为little-endian，
        reverse_copy(Line.begin(), Line.end(), Bits); //反转为正字节序
        *(word*)(&Bits[nLen]) = 0; //将结尾后面的一些位都清零
        nLen = nLen / 2 + (nLen % 2 != 0); //计算作为int数组的长度
        long nRem = 0;//nRem表示余数
        //循环除所有的位，累加进位的余数，生成CRC码
        for (int i = nLen - 1; i >= 0; --i) {
            nRem = ((nRem << 16) + pBit[i]) % nGen;
        }
        if (nRem != 0) {
            nRem = nGen - (nRem << 16) % nGen;
        } //下面按要求的格式输出CRC码
        unsigned char* pByte = (unsigned char*)&nRem;
        cout << setw(2) << (int)pByte[1] << ' ' << setw(2) << (int)pByte[0];
    }
    return 0;//结尾撒花\(^o^)/
}
```

---

