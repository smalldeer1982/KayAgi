# 题目信息

# Digits Sequence (Hard Edition)

## 题目描述

序列123456789101112131415161718192021222324252627282930313233343536...是无穷无尽的,现在你要输出它的第k项。

## 样例 #1

### 输入

```
7
```

### 输出

```
7
```

## 样例 #2

### 输入

```
21
```

### 输出

```
5
```

# AI分析结果

### 题目翻译
# 数字序列（困难版）

## 题目描述
序列 123456789101112131415161718192021222324252627282930313233343536... 是无穷无尽的，现在你要输出它的第 k 项。

## 样例 #1
### 输入
```
7
```
### 输出
```
7
```

## 样例 #2
### 输入
```
21
```
### 输出
```
5
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是先找出第 $k$ 个数字所在数的位数，再确定这个数具体是多少，最后找出该数中对应的第 $k$ 位数字。各题解的主要区别在于实现细节和代码风格。

### 所选题解
- **MarchKid_Joe（4星）**
    - **关键亮点**：思路清晰，代码简洁，对每一步的实现都有详细的注释和解释，便于理解。
    - **核心代码**：
```cpp
#include<cstdio>
using namespace std;
long long k,i,n,a,o;
int main()
{
    scanf("%lld",&k);
    for(n=1,i=1;k-i*n*9>=0;n++,i*=10)
    {
        a+=i*9;
        k-=i*n*9;
    }
    a+=k/n;
    if(k%n!=0)
    {
        ++a;
        o=n-(k%n);
    }
    while(o-->0) a/=10;
    printf("%lld",a%10);
    return 0;
}
```
    - **核心实现思想**：通过循环减去不同位数数字的总长度，确定第 $k$ 个数字所在数的位数 $n$，再计算出所在的数 $a$，最后通过除法和取余操作找到对应的数字。

- **Limit（4星）**
    - **关键亮点**：代码简洁，逻辑清晰，通过循环和条件判断实现了核心功能。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long N;
int main()
{
    scanf("%lld",&N);
    long long now=0;
    int len=0;
    long long _long=9,sum=1;
    while(now<N)
    {
        len+=1;
        now+=_long*len;
        _long*=10;
        sum*=10;
    }
    _long/=10;
    now-=_long*len;
    long long QAQ=(N-now)/len+sum/10;
    int rank=(N-now)%len;
    int i;
    if(!rank)
    {
        rank=len;
        QAQ--;
    }
    for(i=1;i<=len-rank;i++)QAQ/=10;
    printf("%lld",QAQ%10);
    return 0;
}
```
    - **核心实现思想**：通过循环累加不同位数数字的总长度，确定第 $k$ 个数字所在数的位数 $len$，再计算出所在的数 $QAQ$，最后通过除法操作找到对应的数字。

- **淸梣ling（4星）**
    - **关键亮点**：思路详细，对每一步的推理都有详细的说明，代码实现也较为清晰。
    - **核心代码**：
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
    long long k;
    long long i;
    long long all=0;
    long long last_len;
    long long r_to_l;
    long long l_to_r;
    long long num;
    long long len=9;

    cin>>k;
    for(i=1;;i++,len*=10)
    {
        if(all+i*len>=k)
        {
            last_len=k-all;
            r_to_l=(last_len-1)%i+1;
            l_to_r= i+1 - r_to_l;
            num=len/9-1 + (last_len+i-1)/i;
            while(l_to_r!=1)
            {
                num/=10;
                --l_to_r;
            }
            cout<<num%10;
            break;
        }
        all+=i*len;
    }
    return 0;
}
```
    - **核心实现思想**：通过循环累加不同位数数字的总长度，确定第 $k$ 个数字所在数的位数 $i$，再计算出所在的数 $num$，最后通过除法操作找到对应的数字。

### 最优关键思路或技巧
- 利用不同位数数字的个数和总长度的规律，通过循环减去或累加这些长度，快速确定第 $k$ 个数字所在数的位数。
- 对于除法取余结果为 0 的情况进行特判，避免出现错误。

### 拓展思路
同类型题目可能会改变序列的生成规则，或者要求输出多个位置的数字。类似的算法套路可以用于处理其他与数字序列、数位相关的问题，关键在于找出数字的规律并进行合理的计算。

### 推荐题目
- [P1009 阶乘之和](https://www.luogu.com.cn/problem/P1009)：涉及数字的计算和处理。
- [P1012 拼数](https://www.luogu.com.cn/problem/P1012)：与数字的组合和比较有关。
- [P1045 麦森数](https://www.luogu.com.cn/problem/P1045)：需要处理大数字和数字的位数。

### 个人心得摘录
- xh39：“好像我的代码在 cf 里用 c++11 会 wrong answer on test 33，只能用 c++14。温馨提示：记得开 long long！”，提醒了在不同编译器和数据范围下可能出现的问题。
- _Spectator_：“`to_string()` 函数是 C++11 的新函数，还在用 C++98 的读者可以使用[洛谷 IDE](https://www.luogu.com.cn/ide) 编辑程序。”，指出了代码中使用的函数的版本要求。

---
处理用时：43.69秒