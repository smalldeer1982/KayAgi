# 题目信息

# TediousLee

## 题目描述

首先，我们定义 `RDB` 为一棵具有特殊性质的树，它有一个级别 $level$。  

一个级别为 $1$ 的 `RDB` 是一个单独的节点。

接着，对于所有 $i>1$，级别为 $i$ 的 `RDB` 的构成方法如下。  

先求出级别为 $i-1$ 的 `RDB`，然后对于该 `RDB` 中的每个节点 $x$。  



- 如果 $x$ 没有孩子，那么给他加上一个孩子。  

- 如果 $x$ 只有一个孩子，那么给他加上两个孩子。  

- 如果 $x$ 已经有了超过一个孩子，那么我们跳过节点 $x$。  



以下是 $1\le n \le 3$ 的所有 `RDB`



![](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9jZG4ubHVvZ3UuY29tLmNuL3VwbG9hZC92anVkZ2VfcGljL0NGMTM2OUQvNjRjNjY3Zjg4YjBiYTNiNThhNDU4MWU4ZjcyNmQ0ODQ3ZDk3N2E2Yy5wbmc?x-oss-process=image/format,png)



接下来，我们定义一个 `claw`  （见下图），它也是一棵具有特殊性质的树，并且将节点 $1$ 称为这个 `claw` 的中心，其他的称为底部节点。



![](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9jZG4ubHVvZ3UuY29tLmNuL3VwbG9hZC92anVkZ2VfcGljL0NGMTM2OUQvNDE0MmRhNTE0NDVmNGNmY2UxNmVhNjhkOTY4MzJjYWFiZjE3YWNjZS5wbmc?x-oss-process=image/format,png)



现在，给出一个级别为 $n$ 的 `RDB`，初始时他上面的所有节点都为绿色，你可以进行一些操作。  

对于每次操作，你需要在给出的 `RDB` 中找到一个 `claw`，满足所有底部节点在 `RDB` 中都是中心节点的儿子，且这四个节点在 `RDB` 中都是绿色。然后将这四个节点染为黄色。  

问最多可以将多少个节点染成黄色。

## 说明/提示

$1\le T\le 10^4$  

$1\le n \le 2\cdot 10^6$



感谢 @[_Wolverine](https://www.luogu.com.cn/user/120362) 提供的翻译

## 样例 #1

### 输入

```
7
1
2
3
4
5
100
2000000```

### 输出

```
0
0
4
4
12
990998587
804665184```

# AI分析结果

### 题目已为中文，无需翻译

### 算法分类
动态规划

### 综合分析与结论
这些题解的核心思路都是通过寻找 `RDB` 树的结构规律，利用动态规划或递推的方法来求解最多可染成黄色的节点数。大部分题解都发现了对于 $n(n \ge 3)$ 阶的 `RBD` 树，其根结点有两个 $n - 2$ 阶子树和一个 $n - 1$ 阶子树的规律。主要区别在于状态定义和转移方程的处理方式，部分题解考虑根节点染色和不染色两种情况分别递推，部分题解则根据 $n$ 是否为 $3$ 的倍数来调整转移方程。

### 所选题解
- **wflengxuenong（4星）**
  - 关键亮点：思路清晰，直接根据 $n$ 是否为 $3$ 的倍数得到递推方程，代码简洁易懂。
  - 核心代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e6+9 ;
typedef long long ll;
const ll mod=1e9+7;
ll a[N],f[N],t,x,n;

int main() {
    cin>>t;
    for(int i=1;i<=t;i++){
        scanf("%lld",&a[i]) ;
        n=max(n,a[i]);
    }
    f[0]=f[1]=f[2]=0,f[3]=4;
    for(int i=4;i<=n;i++){
        f[i]=(f[i-1]+2*f[i-2]%mod)%mod;
        if(i%3==0)f[i]=(f[i]+4)%mod;
    }
    for(int i=1;i<=t;i++)printf("%lld\n",f[a[i]]);
}
```
  - 核心实现思想：先读取所有询问的 $n$ 值，找到最大的 $n$。初始化 $f[0]=f[1]=f[2]=0,f[3]=4$，然后从 $i = 4$ 开始递推，当 $i$ 不是 $3$ 的倍数时，$f[i]=f[i - 1]+2*f[i - 2]$；当 $i$ 是 $3$ 的倍数时，$f[i]=f[i - 1]+2*f[i - 2]+4$。最后根据询问输出对应的 $f$ 值。

- **vectorwyx（4星）**
  - 关键亮点：详细地对根节点染色和不染色两种情况进行分类讨论，逻辑严谨。
  - 核心代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define ll long long
#define fo(i,x,y) for(register int i=x;i<=y;++i)
#define go(i,x,y) for(register int i=x;i>=y;--i)
using namespace std;

const int syk=1e9+7,maxn=2e6+5;
ll dp[maxn][2];

void solve(int n){
    dp[1][1]=dp[1][0]=dp[2][1]=dp[2][0]=0;
    dp[3][0]=0;dp[3][1]=4;
    fo(i,4,n){
        dp[i][0]=(1ll*max(dp[i-2][1],dp[i-2][0])*2+max(dp[i-1][1],dp[i-1][0]))%syk;
        dp[i][1]=(4+1ll*dp[i-2][0]*2+dp[i-1][0])%syk;
    }
}

void work(){
    int n=read();
    printf("%d\n",max(dp[n][0],dp[n][1]));
}
int main(){
    int T=read();
    solve(maxn-5);
    while(T--){
        work();
    }
    return 0;
}
```
  - 核心实现思想：`solve` 函数预处理答案，`dp[i][0]` 表示 $i$ 阶的树根结点不染黄色所能达到的最大黄色点数，`dp[i][1]` 表示染黄色的情况。根据根节点染色与否分别递推，最后取最大值。`work` 函数处理单个询问，输出结果。

- **Special_Tony（4星）**
  - 关键亮点：思路简洁明了，直接给出状态转移方程，代码实现简单。
  - 核心代码：
```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
const int mod = 1e9 + 7;
int n = 2000003, t, dp[2000005];
int main () {
    ios::sync_with_stdio (0);
    cin.tie (0);
    cout.tie (0);
    for (int i = 3; i < n; ++ i)
        dp[i] = (dp[i - 1] + dp[i - 2] * 2 % mod + (! (i % 3)) * 4) % mod;
    cin >> t;
    while (t --)
        cin >> n, cout << dp[n] << '\n';
    return 0;
}
```
  - 核心实现思想：先根据状态转移方程 $dp_i=\begin{cases} dp_{i - 1}+2\times dp_{i - 2} & i\bmod3\ne0\\ dp_{i - 1}+2\times dp_{i - 2}+4 & i\bmod3=0 \end{cases}$ 预处理 $dp$ 数组，然后根据询问输出对应的 $dp$ 值。

### 最优关键思路或技巧
- 通过画图找规律，发现 `RDB` 树的结构特点，即 $n(n \ge 3)$ 阶的 `RBD` 树的根结点有两个 $n - 2$ 阶子树和一个 $n - 1$ 阶子树。
- 考虑根节点染色和不染色两种情况，或者根据 $n$ 是否为 $3$ 的倍数来调整转移方程，从而正确递推。

### 拓展思路
同类型题可能会有不同的树结构定义和操作规则，但核心思路都是通过分析树的结构规律，利用动态规划或递推来求解最优解。类似算法套路可以应用在其他树形结构的问题中，如树的最大独立集、树的最小覆盖等问题。

### 推荐题目
- [P1352 没有上司的舞会](https://www.luogu.com.cn/problem/P1352)：树的最大独立集问题，与本题思路有相似之处。
- [P2016 战略游戏](https://www.luogu.com.cn/problem/P2016)：树的最小覆盖问题，也可以用树形 DP 解决。
- [P2015 二叉苹果树](https://www.luogu.com.cn/problem/P2015)：树上的背包问题，需要对树的结构进行分析和动态规划。

### 个人心得摘录与总结
- **vectorwyx**：蒟蒻第一次 A 掉 div2 的 D 题，赶紧发篇题解纪念一下。总结：做出有一定难度的题目是值得纪念和总结的，这可以增强自己的信心和能力。
- **Priori_Incantatem**：由于本题的取模会影响最大值的判断，本题解并非正解，仅在不取模的情况下才能保证答案正确，但因为数据太水，本方法还是可以 AC。总结：在处理取模问题时要特别注意，取模可能会影响一些判断，不能仅仅依赖数据通过来判断解法的正确性。 

---
处理用时：53.19秒