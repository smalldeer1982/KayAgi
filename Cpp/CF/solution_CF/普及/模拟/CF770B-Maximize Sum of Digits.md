# Maximize Sum of Digits

## 题目描述

简述：给定一个整数x，你需要找到一个不超过x的a，使得它的各位数和在不超过x的整数中最大

## 样例 #1

### 输入

```
100
```

### 输出

```
99
```

## 样例 #2

### 输入

```
48
```

### 输出

```
48
```

## 样例 #3

### 输入

```
521
```

### 输出

```
499
```

# 题解

## 作者：boluo2014 (赞：1)

这道题倒不是很难！小小数学题。

### 思路

假设输入的 $x$ 有 $a$ 位，第 $i(1 \le i \le a)$ 位为 $x_{i}$。

我们现在如果要对 $x_{i}$ 进行改变：

如果 $x_{i}=9$，你为什么要改呢？

否则：

如果把 $x_{i}$ 改为 $x_{i}-1,x_{i-2} \dots 0$，那只能说太过于的愚蠢了吧。建议去学习幼儿园数学。

如果把 $x_{i}$ 改为 $x_{i}+1,x_{i+2},\dots 9$，那么都有一个共同的特点——它们都需要“退位”。什么是退位？小学就在减法算式中学过，这里就是指将 $x_{i-1}-1$，如果 $x_{i-1}=0$，那么将 $x_{i-2}-1$，如果还是 $0$，就继续往前，以此类推，直到有一个不是 $0$ 了为止。都有退位的代价，为什么不大一点，把 $x_{i}$ 变成 $9$ 呢？

知道了这些，代码写起来就特别容易了。只需要从后往前一次遍历，由于数据比较小，开 long long 就够了，也不需要字符串。但是这里要注意：如果从后往前遍历时，各个数位上数字之和相等，那么应该选择前面的，因为这样可以保证退位的少。尽管选择后面的全是 $9$，但是高位仍然变少了。所以你一旦找到 $x_{i}<9$，就输出，结束可。

### 总结

老师再见！同学再见！我是个傻子我们明天见，希望我不要被拉成一条直线！

---

## 作者：cfkk (赞：1)

思路：首先， $n$ 的大小是 $10^{18}$ ，暴力是肯定行不通的。但是，要想使总和最大，有两种可能。

1. 把每一位上的数尽量都换成 $9$ 。
2. 最大的数字和就是 $n$ 。

知道了这一点，就可以完成此题了。

代码来喽：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define min(a,b)(a<b?a:b)
#define max(a,b)(a>b?a:b)
#define mod 1000000007
#define int long long
inline int read()
{
    char ch=getchar();
    int s=0,w=1;
    while(ch<'0'||ch>'9')
    {
        if(ch=='-'){w=-1;}
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        s=(s<<1)+(s<<3)+ch-48;
        ch=getchar();
    }
    return w*s;
}
inline void out(int x)
{
    if(x<0){putchar('-'),x=-x;}
    if(x>9){out(x/10);}
    putchar(x%10+'0');
}
inline void print(int x)
{
    out(x);
    putchar('\n');
}
inline string read_char()
{
    string str="";
    while(1)
    {
        char ch=getchar();
        if(ch=='\n'){break;}
        str+=ch;
    }
    return str;
}
int p[20];//表示每一位上的数字，因为最多有18为位，所以我们要把数组开到20
void Extraction_of_digits(int x)//提取x的每一位
{
    for(int i=0;x;i++,x/=10){p[i]=x%10;}
}
int Restructuring_figures()//把每一位的数重组
{
    int cnt=0;
    for(int i=20;i--;){cnt=cnt*10+p[i];}
    return cnt;
}
int Extracts_the_sum_of_the_digits_on_each_bit()//求每一位的数字和
{
    int cnt=0;
    for(int i=0;i<20;i++){cnt+=p[i];}
    return cnt;
}
signed main()
{
    memset(p,0,sizeof(p));
    int n=read();
    int ans=n;
    Extraction_of_digits(n);
    int mx=Extracts_the_sum_of_the_digits_on_each_bit();//把最大值设为n的数字和
    for(int i=0;i<20;i++)
    {
        if(p[i])
        {
            p[i]--;
            for(int j=0;j<i;++j){p[j]=9;}
            if(Extracts_the_sum_of_the_digits_on_each_bit()>mx)
            {
                mx=Extracts_the_sum_of_the_digits_on_each_bit();
                ans=Restructuring_figures();
            }
        }
    }
    print(ans);
	return 0;
}

```


---

## 作者：zjc5 (赞：0)

[题目链接](https://www.luogu.com.cn/problem/CF770B)

**思路：**

可以把输入的 $x$ 看成 $\overline{n_1n_2...n_{len}}$。

当一个位数上的数字减一，即使比它小的位数上的数字全部变成 $9$ 也比原来的数小。

那么可以得到一组解 $\overline{(n_1-1)99...9}$。

所以输出的数的位数之和一定 $>=(n_1-1)+9*(len-1)$。

当 $n_2+n_3+...+n_{len}>=9*(len-1)-1$，直接输出 $x$。

对于不是直接输出 $x$ 的数，我们要让 $9$ 尽可能多。

那么就要找一个位数上的数字减一，使得 $a=\overline{(n_1-1)99...9}$ 或 $\overline{n_199...8...99}$。

代码时间复杂度 $O(len)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
char ch[20];
int main() {
    cin >> ch;
    int len = strlen(ch), sum = 0;
    for (int i = 1; i < len; i++)
        sum += ch[i] - '0';
    if (sum >= 9 * (len - 1) - 1)
        for (int i = 0; i < len; i++) cout << ch[i];
    else {
        int pos;
        for (int i = 1; i < len; i++)
            if (ch[i] < '9') {
                pos = i;
                break;
            }
        for (int i = 0; i <= pos - 2; i++) cout << ch[i];
        if (ch[pos - 1] > '1') cout << char(ch[pos - 1] - 1);
        for (int i = pos; i < len; i++) cout << '9';
    }
    return 0;
}
```

---

