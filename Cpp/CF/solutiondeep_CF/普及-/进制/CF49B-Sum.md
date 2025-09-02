# 题目信息

# Sum

## 题目描述

Vasya终于学会了进位制，但他经常忘记写算式的基数。有一次，他看到他的笔记本上写着a+b=？，但是没有写明基数。现在Vasya认为算式的基数为p。他知道算式在不同的基数下，会有不同的结果，甚至在有些基数下是没有意义的。算式78+87的值在十六进制下为FF，在十五进制下为110，十进制下为165，九进制下为176，更小的基数下就没有意义了。现在，Vasya想要知道算式结果的最大长度。
我们定义数字的长度为数字的字符个数，在不同的进制下，同一个数字有不同的数字长度。

## 样例 #1

### 输入

```
78 87
```

### 输出

```
3
```

## 样例 #2

### 输入

```
1 1
```

### 输出

```
2
```

# AI分析结果

### 综合分析与结论
这些题解的核心思路一致，均是先确定最小有意义的进制（即两数所有数位上最大数字加 1），再模拟该进制下的高精度加法，最后计算结果的长度。不同题解在代码实现细节上有所差异，如输入方式、存储方式、处理进位和前导零的方法等。

### 所选题解
- **花园 Serena（5 星）**
    - **关键亮点**：思路清晰，结论明确，代码简洁易读，详细阐述了为何选择最小有意义的进制进行计算。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define R register int
const int MAXN = 1e3 + 10;
int a[MAXN], b[MAXN], c[MAXN];
int main() {
    int x, y; scanf("%d%d", &x, &y);
    int cnt = 0, tot = 0, p = -1;
    while (x) {
        a[++ cnt] = x % 10;
        x /= 10; p = max(p, a[cnt]);
    }
    while(y) {
        b[++ tot] = y % 10;
        y /= 10; p = max(p, b[tot]);
    }
    int ans = max(tot, cnt);
    for(R i = 1; i <= ans; i ++) {
        c[i] += a[i] + b[i];
        if(c[i] > p) c[i + 1] ++;
    }
    if(c[ans + 1]) ans ++;
    printf("%d\n", ans);
    return 0;
}
```
    - **核心实现思想**：先将输入的两个数按位拆分并存储，同时找出所有数位中的最大值，加 1 得到最小有意义的进制。然后模拟该进制下的加法，判断是否有进位，若有则结果长度加 1。

- **liulif（4 星）**
    - **关键亮点**：思路清晰，代码注释详细，采用字符串读入，方便处理大数字。
    - **核心代码**：
```cpp
#include<iostream>
#include<string>
using namespace std;
string a1,b1;
int a[1005],b[1005],sum[1005];
int x,r,len;
int main()
{
    cin>>a1>>b1;
    r=-0x3f3f3f3f;
    for(int i=0;i<a1.length();i++) 
    {
        r=max(r,a1[i]-48);
        a[a1.length()-1-i]=a1[i]-48;
    }
    for(int i=0;i<b1.length();i++) 
    {
        r=max(r,b1[i]-48);
        b[b1.length()-1-i]=b1[i]-48;
    }
    r++;len=0;
    while(len<=a1.length()||len<=b1.length())
    {
        sum[len]=a[len]+b[len]+x;
        x=sum[len]/r;
        sum[len++]%=r;
    }
    while(!sum[len]&&len>0) len--;
    len++;
    cout<<len<<endl;
    return 0;
}
```
    - **核心实现思想**：用字符串读入两个数，按位倒序存储并找出最大数字，加 1 得到进制。模拟该进制下的加法，处理进位和前导零，最后输出结果长度。

- **MarchKid_Joe（4 星）**
    - **关键亮点**：对高精度加法的原理和实现细节讲解详细，采用倒位存储，方便处理进位。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int ans[10],a[10],b[10];
int s,la,lb;
int input(int x[10],int len=0,char k=getchar())
{
    int Length=0;
    int t[10]={};
    while(k<'0'||k>'9')	k=getchar();
    while(k>='0'&&k<='9'){t[++len]=k-'0';k=getchar();}
    while(len>0)x[++Length]=t[len--];
    return Length;
}
void get_begin(int *x,int length)
{
    for(int i=1;i<=length;i++)
        s=max(s,x[i]);
}
int length(int x)
{
    int cnt=max(la,lb)+1;
    for(int i=1;i<=cnt;i++)
    {
        ans[i]+=a[i]+b[i];
        ans[i+1]+=ans[i]/x;
        ans[i]%=x;
    }
    while(cnt>0&&!ans[cnt]) cnt--;
    return cnt;
}
int main()
{
    la=input(a);
    lb=input(b);
    get_begin(a,la);
    get_begin(b,lb);
    printf("%d",length(s+1));
    return 0;
}
```
    - **核心实现思想**：通过 `input` 函数倒位存储输入的两个数，`get_begin` 函数找出最大数字，加 1 得到进制。`length` 函数模拟该进制下的加法，处理进位和前导零，最后返回结果长度。

### 最优关键思路或技巧
- **确定最小有意义的进制**：两数所有数位上最大数字加 1 即为最小有意义的进制，在此进制下结果长度可能最长。
- **高精度加法模拟**：按位相加，处理进位，注意处理前导零。
- **倒位存储**：方便处理低位向高位的进位。

### 可拓展之处
同类型题目可能会涉及多进制下的乘法、减法等运算，或者要求计算不同进制下结果的具体值。解题思路类似，都是先确定合适的进制，再模拟相应的运算。

### 推荐题目
1. [P1601 A+B Problem（高精）](https://www.luogu.com.cn/problem/P1601)：高精度加法基础题。
2. [P2142 高精度减法](https://www.luogu.com.cn/problem/P2142)：高精度减法题目。
3. [P1303 A*B Problem](https://www.luogu.com.cn/problem/P1303)：高精度乘法题目。

### 个人心得摘录与总结
- **EDqwq**：提到易知 10 进制下的数在 1 - 9 进制下会变“大”一点，所以直接算最小进制即为答案，不必再往上枚举。同时指出要注意算出最小数码加一开始枚举、删除前导多余的 0 以及最后答案加一。总结：在处理进制问题时，要理解不同进制下数字长度的变化规律，注意细节处理。
- **_wjr_**：通过设两个基数 $x , y (x < y)$ ，解释了为什么基数最小时长度会取到最大值。总结：遇到此类问题可以通过数学推导来理解原理。 

---
处理用时：41.75秒