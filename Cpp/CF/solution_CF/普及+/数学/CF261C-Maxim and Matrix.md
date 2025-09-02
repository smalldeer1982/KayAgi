# Maxim and Matrix

## 题目描述

Maxim loves to fill in a matrix in a special manner. Here is a pseudocode of filling in a matrix of size $ (m+1)×(m+1) $ :

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF261C/2ee53d83c775f11a8b5c62a496d38d42095666d0.png)

Maxim asks you to count, how many numbers $ m $ $ (1<=m<=n) $ are there, such that the sum of values in the cells in the row number $ m+1 $ of the resulting matrix equals $ t $ .

Expression ( $ x $ $ xor $ $ y $ ) means applying the operation of bitwise excluding "OR" to numbers $ x $ and $ y $ . The given operation exists in all modern programming languages. For example, in languages C++ and Java it is represented by character "^", in Pascal — by "xor".

## 样例 #1

### 输入

```
1 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3 2
```

### 输出

```
1
```

## 样例 #3

### 输入

```
3 3
```

### 输出

```
0
```

## 样例 #4

### 输入

```
1000000000000 1048576
```

### 输出

```
118606527258
```

# 题解

## 作者：_edge_ (赞：1)

首先看到这种题目，就把题目中的程序给搞下来，注意这里 `equal` 是 `==`。

搞下来以后，我们暴力把 $1$~$7$ 给带入。

```
1 1 -> 1 -> 1 -> 2^{1-1}
1 2 -> 10 -> 1 -> 2^{1-1}
2 3 -> 11 -> 2 -> 2^{2-1}
1 4 -> 100 -> 1 -> 2^{1-1}
2 5 -> 101 -> 2 -> 2^{2-1}
2 6 -> 110 -> 2 ....
4 7 -> 111 -> 3 ....

```

发现了这样子的形式，为了方便观察，第二列的数为 $m+1$，我们将其转成二进制之后发现和二进制下的 $1$ 的个数有关系，设其为 $a$，那么其对应出现的在矩阵最后一行的 $1$ 的个数即为 $2^{a-1}$。

知道了这个，我们就明白假如说这个 $t$ 不是 $2$ 的次幂，答案即为 $0$，如果是的话，问题就转化成在 $1$ 到 $n$ 里面求有多少个数，使得它在二进制下 $1$ 的个数是多少多少个。

这个问题很经典，可以用数位 DP 做到 $\log n$ 的级别。

不过这里提个醒，这里 $m \ge1$ 哦，也就是说，如果统计 $t=1$ 的个数的时候，要减一哦。

这边我比较擅长记忆化搜索的数位 DP，这样看起来简洁明了，但同时换来的是 …… 很难调试。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#define int long long 
using namespace std;
const int INF=55;
int n,t,len,g[INF],f[INF][5][INF];
int DFS(int a1,int a2,int a3) {
    // if (a3>len) return 0;
    // cout<<a1<<" "<<a2<<" "<<a3<<" "<<1<<"\n";
    if (a1<=0) return a3==len;
    if (f[a1][a2][a3]!=-1) return f[a1][a2][a3];
    int Max=a2?g[a1]:1,res=0;
    for (int i=0;i<=Max;i++) {
        res+=DFS(a1-1,a2 && i==Max,a3+(i==1));
    }
    f[a1][a2][a3]=res;
    // cout<<a1<<" "<<a2<<" "<<a3<<" "<<res<<"\n";
    return res;
}
int calc(int xx) {
    memset(g,0,sizeof g);
    memset(f,255,sizeof f);
    while (xx) {
        g[++g[0]]=xx&1;
        xx>>=1;
    }
    return DFS(g[0],1,0);
}
signed main()
{
    scanf("%lld %lld",&n,&t);
    n++;
    int tt=t,fl=0;
    while (tt) {
        if (tt&1) fl++;
        tt>>=1;
        len++;
    }
    if (fl>1) {cout<<"0\n";return 0;}
    // cout<<len<<"\n";
    fl=0;if (t==1) fl=-1;
    cout<<calc(n)+fl<<"\n";
    return 0;
}
```


---

## 作者：Edmundino (赞：1)

# 题意

给出一个关于参数 $m$ 矩阵构造方法，

矩阵构造出来为 $(m+1)\times (m+1)$ 的，且都为 $0$ 或 $1$。

输入 $n$ 和 $t$ ，满足参数 $1\le m \le n$。

求 $2$ 到 $n+1$ 行中有多少行中 $1$ 的个数等于 $t$。

# 分析

首先我们先通过题目分析一个给出的矩阵，

记录每一行 $1$ 的个数得到以下：

```
1
1 2 
1 2 2 4 
1 2 2 4 2 4 4 8 
1 2 2 4 2 4 4 8 2 4 4 8 4 8 8 16 
```

可以发现，每一行的数是上一行的数乘 $2$ 并放到上一行末尾得到的。

那么我们就可以知道 $t$ 必须是一个 $2$ 的次幂的数。

如果不是，我们就要输出 $0$。

接着我们就要开始统计，

在 $n+1$ 内，所有 $2$ 的所有次幂的数出现的个数即可，

用数位动态规划即可实现。

注意：询问 $1$ 的时候将答案减一。

# 代码

**核心部分**

```cpp
n=n+1;
for(int j=60;j>=0;j--)
{
	for(int i=60;i>0;i--)
	  dp[i]+=dp[i-1];
	if ((n>>j)%2==1) ++dp[c++];
}
dp[c]++;//数位dp
for(c=0;t;t>>=1)
 c++;//记录t是2的多少次幂
if(c==1)dp[c]--;
```




---

