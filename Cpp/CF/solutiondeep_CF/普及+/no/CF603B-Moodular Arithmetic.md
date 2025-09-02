# 题目信息

# Moodular Arithmetic

## 题目描述

As behooves any intelligent schoolboy, Kevin Sun is studying psycowlogy, cowculus, and cryptcowgraphy at the Bovinia State University (BGU) under Farmer Ivan. During his Mathematics of Olympiads (MoO) class, Kevin was confronted with a weird functional equation and needs your help. For two fixed integers $ k $ and $ p $ , where $ p $ is an odd prime number, the functional equation states that

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF603B/ed6bc974175d6ded86ca0d36ce0ca4605575bbb9.png)for some function ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF603B/3d499b5681b890bdb5d1b1234e5b8d6e9d7e27b1.png). (This equation should hold for any integer $ x $ in the range $ 0 $ to $ p-1 $ , inclusive.)

It turns out that $ f $ can actually be many different functions. Instead of finding a solution, Kevin wants you to count the number of distinct functions $ f $ that satisfy this equation. Since the answer may be very large, you should print your result modulo $ 10^{9}+7 $ .

## 说明/提示

In the first sample, $ p=3 $ and $ k=2 $ . The following functions work:

1. $ f(0)=0 $ , $ f(1)=1 $ , $ f(2)=2 $ .
2. $ f(0)=0 $ , $ f(1)=2 $ , $ f(2)=1 $ .
3. $ f(0)=f(1)=f(2)=0 $ .

## 样例 #1

### 输入

```
3 2
```

### 输出

```
3
```

## 样例 #2

### 输入

```
5 4
```

### 输出

```
25
```

# AI分析结果

### 题目内容
# 模运算

## 题目描述
和任何聪明的学生一样，凯文·孙（Kevin Sun）在农民伊万（Farmer Ivan）的指导下，于博维尼亚州立大学（BGU）学习心理学、微积分和密码学。在他的奥林匹克数学（MoO）课上，凯文遇到了一个奇怪的函数方程，需要你的帮助。对于两个固定整数 $k$ 和 $p$，其中 $p$ 是一个奇质数，该函数方程表示为：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF603B/ed6bc974175d6ded86ca0d36ce0ca4605575bbb9.png)

对于某个函数 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF603B/3d499b5681b890bdb5d1b1234e5b8d6e9d7e27b1.png)。（此方程对于范围在 $0$ 到 $p - 1$（包括 $0$ 和 $p - 1$）内的任何整数 $x$ 都应成立。）

事实证明，$f$ 实际上可以是许多不同的函数。凯文不想找到一个解，而是希望你计算满足此方程的不同函数 $f$ 的数量。由于答案可能非常大，你应将结果对 $10^{9}+7$ 取模后输出。

## 说明/提示
在第一个样例中，$p = 3$ 且 $k = 2$。以下函数满足条件：
1. $f(0)=0$，$f(1)=1$，$f(2)=2$。
2. $f(0)=0$，$f(1)=2$，$f(2)=1$。
3. $f(0)=f(1)=f(2)=0$。

## 样例 #1
### 输入
```
3 2
```
### 输出
```
3
```

## 样例 #2
### 输入
```
5 4
```
### 输出
```
25
```

### 算法分类
数学

### 综合分析与结论
这些题解均围绕满足给定函数方程的函数 $f$ 的数量计算展开。核心思路都是通过对 $k$ 值分类讨论来求解。对于 $k = 0$ 和 $k = 1$ 的情况较易分析，$k > 1$ 时难点在于如何确定不同函数的数量。各题解主要区别在于分析 $k > 1$ 时的方法，有的通过找循环节，有的通过建图分析连通块。

### 所选的题解
- **作者：jun头吉吉（5星）**
  - **关键亮点**：思路清晰，对 $k$ 的不同取值分类讨论完整且简洁。先分析特殊情况 $k = 0$ 和 $k = 1$，对于 $k > 1$ 时，通过分析一个数 $f(x)$ 能影响的其他值构成的环，得出答案为 $p^{\frac {p - 1} {m}}$，其中 $m$ 通过暴力寻找满足 $k^m = 1 \mod p$ 的最小正整数 $m$。代码简洁高效，使用快速幂优化计算。
  - **核心代码**：
```cpp
ll fpow(ll a,ll b){
    ll ret=1;
    while(b){
        if(b&1)ret=ret*a%mod;
        a=a*a%mod;b>>=1;
    }
    return ret;
}
signed main(){
    read(p,k);
    if(k==0)write(fpow(p,p-1)),exit(0);
    if(k==1)write(fpow(p,p)),exit(0);
    int m=1;ll x=k;
    while(x!=1)
        m++,x=x*k%p;
    write(fpow(p,(p-1)/m));
}
```
  - **核心思想**：先特判 $k = 0$ 和 $k = 1$ 情况，$k > 1$ 时暴力找循环节长度 $m$，最后用快速幂计算答案。

- **作者：enyyyyyyy（4星）**
  - **关键亮点**：思路直接，提到将 $1$ 到 $p$ 分组，每组内有 $p$ 种合法方案，通过模拟快速幂找每组元素个数，最后相乘得到答案。代码实现简单明了，注意到 $k = 1$ 要特判。
  - **核心代码**：
```cpp
int main() {
    p = read(), k = read();
    do {
        op = op * k % p;
        ++cnt;
    } while (op > 1);
    for (ll i = 1; i <= (p - 1) / cnt; i++)
        ans = ans * p % 1000000007;
    if (k == 1) ans = ans * p % 1000000007;
    print(ans);
    return 0;
}
```
  - **核心思想**：模拟快速幂找每组元素个数 `cnt`，计算 $(p - 1) / cnt$ 组的方案数并考虑 $k = 1$ 特判。

- **作者：hgzxwzf（4星）**
  - **关键亮点**：同样采用分组思想，每组独立处理，每组方案数为 $p$，通过标记已处理元素避免重复计算，代码简洁，逻辑清晰。
  - **核心代码**：
```cpp
int main() {
    int p,k;
    scanf("%d%d",&p,&k);
    if(k==1) return printf("%d",ksm(p,p)),0;
    int ans=1;
    rep(i,1,p-1) {
        if(bo[i]) continue;
        for(int j=i;;) {
            if(bo[j]) break;
            bo[j]=1;
            j=1ll*j*k%p;
        }
        ans=1ll*ans*p%mod;
    }
    printf("%d",ans);
    return 0;
}
```
  - **核心思想**：特判 $k = 1$，遍历 $1$ 到 $p - 1$，对未处理元素找其所在组并计算方案数累乘。

### 最优关键思路或技巧
对于此类模运算下函数计数问题，对参数 $k$ 分类讨论是关键。在处理 $k > 1$ 时，通过找循环节或分组的方式，将问题简化为计算每组或每个循环节的方案数，最后通过幂运算得到最终答案。同时，利用快速幂优化计算过程，提高效率。

### 可拓展之处
同类型题常涉及数论中模运算、函数性质以及组合计数相关知识点。类似算法套路是遇到带有参数的函数方程，先考虑参数的特殊值情况，再分析一般情况，通过找规律、建图、分组等方式简化问题。

### 洛谷相似题目推荐
- [P1226 【模板】快速幂||取余运算](https://www.luogu.com.cn/problem/P1226)
- [P2142 高精度减法](https://www.luogu.com.cn/problem/P2142)
- [P1082 同余方程](https://www.luogu.com.cn/problem/P1082)

### 个人心得摘录
无

---
处理用时：57.43秒