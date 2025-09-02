# 题目信息

# Yet Another Counting Problem

## 题目描述

You are given two integers $ a $ and $ b $ , and $ q $ queries. The $ i $ -th query consists of two numbers $ l_i $ and $ r_i $ , and the answer to it is the number of integers $ x $ such that $ l_i \le x \le r_i $ , and $ ((x \bmod a)       \bmod b) \ne ((x \bmod b) \bmod a) $ . Calculate the answer for each query.

Recall that $ y \bmod z $ is the remainder of the division of $ y $ by $ z $ . For example, $ 5 \bmod 3 = 2 $ , $ 7 \bmod 8       = 7 $ , $ 9 \bmod 4 = 1 $ , $ 9 \bmod 9 = 0 $ .

## 样例 #1

### 输入

```
2
4 6 5
1 1
1 3
1 5
1 7
1 9
7 10 2
7 8
100 200```

### 输出

```
0 0 0 2 4 
0 91```

# AI分析结果

### 题目翻译
## 又一个计数问题

### 题目描述
给定两个整数 $a$ 和 $b$，以及 $q$ 次询问。第 $i$ 次询问包含两个数 $l_i$ 和 $r_i$，其答案是满足 $l_i \leq x \leq r_i$ 且 $((x \bmod a) \bmod b) \ne ((x \bmod b) \bmod a)$ 的整数 $x$ 的数量。计算每次询问的答案。

回顾一下，$y \bmod z$ 是 $y$ 除以 $z$ 的余数。例如，$5 \bmod 3 = 2$，$7 \bmod 8 = 7$，$9 \bmod 4 = 1$，$9 \bmod 9 = 0$。

### 样例 #1
#### 输入
```
2
4 6 5
1 1
1 3
1 5
1 7
1 9
7 10 2
7 8
100 200
```
#### 输出
```
0 0 0 2 4 
0 91
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是利用取模运算的周期性，通过找出循环节（通常是 $lcm(a, b)$），预处理出一个周期内满足条件的数的前缀和，再根据查询区间 $[l, r]$ 中完整周期的数量和剩余部分，快速计算出答案。

不同题解的差异主要在于对周期性的推导和前缀和的处理方式。部分题解详细推导了周期性的原理，而有些题解则直接利用结论进行计算。

### 高评分题解
- **作者：无咕_ (5星)**
    - **关键亮点**：思路清晰，详细推导了取模运算的周期性，对前缀和的处理解释详细，代码可读性高。
    - **重点代码**：
```cpp
int gcd(int a,int b){//获取最大公因数
    return b==0?a:gcd(b,a%b);
}
int main(){
    scanf("%d",&t);
    while(t--){
        scanf("%lld %lld %d",&a,&b,&q);
        ll _lcmab=a*b/gcd(a,b);
        for(int i=1;i<=_lcmab;i++){
            s[i]=s[i-1];
            if(i%a%b!=i%b%a)s[i]++;
        }
        for(int i=1;i<=q;i++){
            ll l,r;
            scanf("%lld %lld",&l,&r);
            ll rx=(r/_lcmab)*s[_lcmab]+s[r%_lcmab];
            ll lx=((l-1)/_lcmab)*s[_lcmab]+s[(l-1)%_lcmab];
            printf("%lld ",rx-lx);
        }
    }
    return 0;
}
```
    - **核心实现思想**：先计算 $a$ 和 $b$ 的最小公倍数 `_lcmab`，然后预处理出 $1$ 到 `_lcmab` 中满足条件的数的前缀和数组 `s`。对于每次查询 $[l, r]$，分别计算 $1$ 到 $r$ 和 $1$ 到 $l - 1$ 中满足条件的数的数量，相减得到答案。

- **作者：一扶苏一 (4星)**
    - **关键亮点**：简洁地阐述了周期性的结论，代码结构清晰，利用命名空间封装代码。
    - **重点代码**：
```cpp
void calc() {
  t = x * y;
  for (int i = 0; i < t; ++i) if ((i % x % y) != (i % y % x)) {
    sum[i] = 1;
  } else {
    sum[i] = 0;
  }
  for (int i = 1; i < t; ++i) sum[i] += sum[i - 1];
}

ll query(ll u) {
  if (u == 0) return 0;
  ll v = u / t, ret = sum[t - 1] * v;
  u -= v * t;
  return ret + sum[u];
}
```
    - **核心实现思想**：`calc` 函数预处理出 $0$ 到 $ab - 1$ 中满足条件的数的前缀和数组 `sum`。`query` 函数根据查询的数 $u$，计算出完整周期的贡献和剩余部分的贡献，返回满足条件的数的数量。

- **作者：do_while_true (4星)**
    - **关键亮点**：直接点明循环节长度为 $lcm(a, b)$，代码简洁明了。
    - **重点代码**：
```cpp
inline int gcd(int x,int y)
{
    return y==0 ? x : gcd(y,x%y);
}
long long work(long long x)
{
    long long num=x/lcm;
    return num*1ll*sum[lcm]+1ll*sum[x-num*lcm];
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d",&a,&b,&q);
        int gccd=gcd(a,b);
        lcm=a*b/gccd;
        for(int i=1;i<=lcm;i++)
            sum[i]=sum[i-1]+(i%a%b!=i%b%a);
        while(q--)
        {
            scanf("%lld%lld",&l,&r);
            printf("%lld ",work(r)-work(l-1));
        }
    }
}
```
    - **核心实现思想**：先计算 $a$ 和 $b$ 的最小公倍数 `lcm`，然后预处理出 $1$ 到 `lcm` 中满足条件的数的前缀和数组 `sum`。`work` 函数根据查询的数 $x$，计算出完整周期的贡献和剩余部分的贡献，返回满足条件的数的数量。

### 最优关键思路或技巧
- 利用取模运算的周期性，将问题转化为一个周期内的问题，通过预处理前缀和，将每次查询的时间复杂度降低到 $O(1)$。
- 对于查询区间 $[l, r]$，采用前缀相减的方式，即 $ans(r) - ans(l - 1)$ 来计算答案。

### 可拓展之处
同类型题或类似算法套路：
- 涉及取模运算的周期性问题，如循环节的查找和利用。
- 利用前缀和优化区间查询问题。

### 推荐洛谷题目
- [P1029 [NOIP2001 普及组] 最大公约数和最小公倍数问题](https://www.luogu.com.cn/problem/P1029)
- [P1306 斐波那契公约数](https://www.luogu.com.cn/problem/P1306)
- [P2152 [SDOI2009]SuperGCD](https://www.luogu.com.cn/problem/P2152)

### 个人心得摘录与总结
- **无咕_**：提醒注意前缀和的处理，因为 $l$ 和 $r$ 可能不在同一个周期里，要将 $[1, l - 1]$ 和 $[1, r]$ 都处理出来再相减。
总结：在处理区间查询问题时，要考虑边界情况，确保计算的准确性。

---
处理用时：49.06秒