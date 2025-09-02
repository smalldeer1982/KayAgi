# 题目信息

# p-binary

## 题目描述

### 题意简述

给定整数 $n,p$，求最小的 $x$ 使得其满足

$$\sum_{1}^{x} (2^k+p)=n$$

其中 $k$ 可以是任意自然数。

## 样例 #1

### 输入

```
24 0
```

### 输出

```
2
```

## 样例 #2

### 输入

```
24 1
```

### 输出

```
3
```

## 样例 #3

### 输入

```
24 -1
```

### 输出

```
4
```

## 样例 #4

### 输入

```
4 -7
```

### 输出

```
2
```

## 样例 #5

### 输入

```
1 1
```

### 输出

```
-1
```

# AI分析结果

### 题目分类
枚举

### 综合分析与结论
这些题解的核心思路都是通过枚举答案 $x$，将原方程变形为 $n - x\times p=\sum_{i = 1}^{x}2^{k_i}$，然后判断 $n - x\times p$ 是否能分解成 $x$ 个 $2$ 的幂之和。判断的依据是：$n - x\times p$ 的二进制表示中 $1$ 的个数 $cnt$ 应满足 $cnt\leq x\leq n - x\times p$。

各题解的区别主要在于代码实现细节和对无解情况的判断方式，但整体思路一致。

### 所选题解
- **robin12138（4星）**
    - **关键亮点**：思路清晰，代码简洁，使用 `lowbit` 运算计算二进制中 $1$ 的个数。
    - **个人心得**：无
- **Ofnoname（4星）**
    - **关键亮点**：借助 `__builtin_popcount` 库函数来计算二进制中 $1$ 的个数，代码简洁。
    - **个人心得**：比赛时没想到判断 `-1` 的方法，看了官方题解后才明白，枚举上界是 `i <= N - p * i`，超过就无解。
- **傅思维666（4星）**
    - **关键亮点**：详细解释了判断不合法的条件，代码结构清晰。
    - **个人心得**：提供了关于 `lowbit` 运算的博客链接，方便读者学习。

### 重点代码
#### robin12138 的代码
```cpp
il int cnt(int x) 
{ 
    int ret=0; 
    while(x) x-=x&-x,++ret; return ret; 
}
int main()
{
    n=read(); p=read();
    for(int i=1;i<=n-i*p;++i)
        if(i>=cnt(n-i*p))
            printf("%d\n",i),exit(0); 
    puts("-1");
    return 0;
}
```
**核心实现思想**：定义 `cnt` 函数计算二进制中 $1$ 的个数，然后从小到大枚举 $i$，判断 $i$ 是否满足 $i\geq cnt(n - i\times p)$ 且 $i\leq n - i\times p$，满足则输出 $i$，否则输出 `-1`。

#### Ofnoname 的代码
```cpp
#include <cstdio>
#define popcnt __builtin_popcount

int N, p;

int main()
{
    scanf("%d%d", &N, &p);
    for (int i = 0; i <= N - p * i; i++)
        if (i >= popcnt(N - p * i))
        { 
            printf("%d\n", i);
            return 0;
        }
    puts("-1");
}
```
**核心实现思想**：使用 `__builtin_popcount` 函数计算二进制中 $1$ 的个数，枚举 $i$，判断 $i$ 是否满足条件，满足则输出 $i$，否则输出 `-1`。

#### 傅思维666 的代码
```cpp
int lowbit(int x)
{
    int ret=0;
    while(x)
    {
        x-=x&-x;
        ret++;
    }
    return ret;
}
int main()
{
    scanf("%d%d",&n,&p);
    for(int i=1;;i++)
    {
        if(n-i*p<i)
            break;
        if(lowbit(n-i*p)>i)
            continue;
        ans=i;
        flag=1;
        break;
    }
    if(flag)
    {
        printf("%d",ans);
        return 0;
    }
    else
    {
        printf("-1");
        return 0;
    }
}
```
**核心实现思想**：定义 `lowbit` 函数计算二进制中 $1$ 的个数，枚举 $i$，判断 $n - i\times p$ 是否小于 $i$ 或 $lowbit(n - i\times p)$ 是否大于 $i$，不满足则记录答案并标记，最后根据标记输出结果。

### 最优关键思路或技巧
- 利用二进制的性质，将问题转化为判断一个数能否分解成指定个数的 $2$ 的幂之和。
- 通过枚举答案，结合二进制中 $1$ 的个数进行判断。
- 注意判断无解的条件，即 $n - x\times p < x$ 时无解。

### 拓展思路
同类型题或类似算法套路：
- 涉及二进制表示和分解的题目，如判断一个数能否由若干个特定的数相加得到。
- 枚举答案结合条件判断的题目，通过枚举找到满足条件的最小或最大解。

### 推荐洛谷题目
- [P1028 数的计算](https://www.luogu.com.cn/problem/P1028)
- [P1044 栈](https://www.luogu.com.cn/problem/P1044)
- [P1014 Cantor表](https://www.luogu.com.cn/problem/P1014)

---
处理用时：32.21秒