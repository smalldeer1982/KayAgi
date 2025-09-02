# [GCJ 2010 #1B] Your Rank is Pure

## 题目描述

> Pontius：你知道吗，我喜欢这个数字 127，我也不知道为什么。  
> Woland：嗯，那是一个非常纯粹的对象。你知道质数吧。  
> Pontius：当然知道。那些是我们古代大师几百年前拥有的对象。哦，是的，为什么呢？127 的确是个质数，就像我被告知的那样。  
> Woland：不仅如此。127 是第 31 个质数；然后，31 本身也是质数，它是第 11 个；11 是第 5 个；5 是第 3 个；3，你知道，是第二个；最后 2 是第一个。  
> Pontius：呵，这确实……纯粹的质数。

这个游戏可以在任意正整数子集 $s$ 上进行。对于集合 $s$，如果一个数在 $s$ 中，从它开始，不断取它在 $s$ 中的排名，并且得到的数也在 $s$ 中，直到有限步后得到数字 1（1 不在 $s$ 中），那么这个数被称为相对于 $s$ 是纯粹的。

给定 $n$，有多少种方式可以选择 $s$，$s$ 是 $\{2, 3, ..., n\}$ 的一个子集，使得 $n$ 相对于 $s$ 是纯粹的？答案可能很大，你需要输出答案对 100003 取模的结果。

## 说明/提示

**数据范围**

- $T \leqslant 100$。

**小数据集（14 分，测试点 1 - 可见）**

- 时间限制：3 秒。
- $2 \leqslant n \leqslant 25$。

**大数据集（30 分，测试点 2 - 隐藏）**

- 时间限制：6 秒。
- $2 \leqslant n \leqslant 500$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2
5
6```

### 输出

```
Case #1: 5
Case #2: 8```

# 题解

## 作者：jsisonx (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P13395)

# 题目分析

使用动态规划。

首先，考虑纯粹数的条件：对于数 $n$，要求 $n$ **在集合 $s$ 中**，每次取 $n$ 在 $s$ 中的排名 $n'$，**$n'$ 在 $s$ 中**，并将 $n$ 变为 $n'$，经**有限步**后 $n$ 变为 $1$。标粗体的三点就是纯粹数的条件。显然第三点是没用的，因为 $n$ 的排名一定小于 $n$，所以最后一定会到 $1$。第一点也可以忽略，因此只需考虑第二点即可。用 $\left| s \right|$ 表示 $s$ 的大小。显然，初始时 $n$ 的排名为 $\left| s \right|$。因此 $\left| s \right|$ 必然在 $s$ 中，由于第一步后 $n$ 就变成了 $\left| s \right|$，因此 $\left| s \right|$ 必然也是一个纯粹数。这样，由于 $\left| s \right|<n$，我们得到了一个规模比原问题小的子问题，符合动态规划的要求。

### 定义状态

定义 $f_{i,j}$ 表示 $n=i$，$\left| s \right|=j$ 时的 $s$ 的数量。

### 状态转移方程

由上面的分析可知，我们需要枚举 $j$ 从 $1$ 到 $n-1$。由于 $j$ 也是一个纯粹数，因此 $j$ 的排名 $k$ 一定也在 $s$ 中，因此再枚举 $k$ 从 $1$ 到 $j-1$。$j$ 在 $s$ 中排名为 $k$，因此从 $2$ 到 $j$ 一共有 $k$ 个数。而我们的 $s$ 的大小为 $j$，因此还需从 $j+1$ 到 $i-1$ 中选出 $j-k-1$ 个数，共有 $C_{i-j-1}^{j-k-1}$ 种选法。根据乘法原理和加法原理可得状态转移方程：

$$f_{i,j}=\sum\limits_{k=1}^{j-1}(f_{j,k}\times C_{i-j-1}^{j-k-1})$$

可以优化一下，因为 $i-j-1\ge j-k-1$，因此 $k \ge 2j-i$，因此上述方程 $k$ 的下界可优化为 $\max(1,2j-i)$。

### 初始状态

$f_{2,1}=1$，对于任意 $i$，有 $f_{i,1}=1$。

# 代码

```cpp
#include<bits/stdc++.h>
#define N 505
#define P 100003
using namespace std;
long long f[N][N];
long long jc[N],c[N][N];
inline void initc(long long n){
    c[0][0]=1;
    c[1][0]=c[1][1]=1;
    for(int i=2;i<=n;i++){
        c[i][0]=c[i][i]=1;
    }
    for(int i=2;i<=n;i++){
        for(int j=1;j<i;j++){
            c[i][j]=(c[i-1][j]+c[i-1][j-1])%P;
        }
    }
    return;
}
int main(){
    int t;
    cin>>t;
    for(int o=1;o<=t;o++){
        printf("Case #%d: ",o);
        int n;
        scanf("%d",&n);
        initc(n);
        f[2][1]=1;
        for(int i=3;i<=n;i++){
            f[i][1]=1;
            for(int j=2;j<=i-1;j++){
                f[i][j]=0;
                for(int k=max(1,2*j-i);k<=j-1;k++){
                    f[i][j]=(f[i][j]+(f[j][k]%P)*(c[i-j-1][j-k-1]%P))%P;
                }
            }
        }
        long long ans=0;
        for(int i=1;i<=n-1;i++){
            ans=(ans+f[n][i])%P;
        }
        cout<<ans%P<<endl;
    }
    return 0;
}
```

---

## 作者：EternalLight (赞：0)

既然从 $n$ 不断取排名能到达 $1$，从 $1$ 不断取排名为当前数的数（例如在 $2,3,5,7,11$ 中，$2\to3\to11$）也能到达 $n$。

为了方便，我们称 $s$ 中第 $i$ 小的元素为“第 $i$ 个数”。

设 $dp_{i,j}$ 表示在从 $1$ 往后跳转时，**能跳到**第 $i$ 个数且第 $i$ 个数恰好为 $j(j>i)$ 的 $s$ 的数量。则显然 $dp_{1,i}=1(2\le i\le n)$。

设我们是由 $k$ **直接**跳到 $i$ 的（即第 $k$ 个数为 $i$），则第 $k+1,k+2,\ldots,i-1$ 个数（共 $i-k-1$ 个）可以取 $i+1,i+2,\ldots,j-1$ 这 $j-i-1$ 个值，共有 $C^{j-i-1}_{i-k-1}$ 种取法。同时要注意，为了使 $C^{j-i-1}_{i-k-1}$ 有定义，应满足 $j-i-1\ge i-k-1$，即 $k\ge 2i-j$。故由加法原理和乘法原理可以得到转移方程：

$$dp_{i,j}=\sum_{k=\max(1,2i-j)}^{i-1}dp_{k,i}\times C^{j-i-1}_{i-k-1}$$

显然答案即为 $\sum^{n-1}_{i=1}dp_{i,n}$。做法是 $n^3$ 的，但是常数较小，可以通过，当然也可以打个表~~抢最优解~~确保不被卡掉。

打表代码如下。非打表做法只要改成输入 $n$ 的值，最后输出 $ans_n$ 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define f(a,b,c) for(int a=b;a<=c;++a)
#define F(a,b,c) for(int a=b;a>=c;--a)
int rd(){
	int ans=0,f=1;char c=getchar();
	while(c<48 or c>57){if(c=='-')f=-1;c=getchar();}
	while(c>47 and c<58)ans=(ans<<3)+(ans<<1)+(c^48),c=getchar();
	return ans*f;
}
#define N 555
#define mod 100003
int C[567][567],dp[567][567],ans[567];
int main(){
    // 计算组合数
	f(i,0,N)C[i][i]=C[i][0]=1;
	f(i,1,N)f(j,1,i-1)C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
    // 初始化；我是在这里提前把dp的值计入答案的，当然最后累加也可以
	f(i,2,N)dp[1][i]=1,++ans[i];
    // 转移
	f(i,2,N)f(j,i+1,N){
		f(k,max(1,i+i-j),i-1)
            // 乘法可能超出int范围，先强转long long计算再取模
            dp[i][j]=(dp[i][j]+1ll*dp[k][i]*C[j-i-1][i-k-1]%mod)%mod;
        // 同上，提前将dp值计入答案
		ans[j]=(ans[j]+dp[i][j])%mod;
	}
    // 打表
	printf("int ans[567]={1545,"); // 从1开始，先在ans[0]处随便赋一个值
	f(i,1,N-1)printf("%d,",ans[i]);
	printf("%d};",ans[N]);
	return 0;
}
```

---

