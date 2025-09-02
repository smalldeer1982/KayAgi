# Singer House

## 题目描述

It is known that passages in Singer house are complex and intertwined. Let's define a Singer $ k $ -house as a graph built by the following process: take complete binary tree of height $ k $ and add edges from each vertex to all its successors, if they are not yet present.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF830D/786f947e45e17a01a870bc159efd0eac65e5d884.png)Singer $ 4 $ -houseCount the number of non-empty paths in Singer $ k $ -house which do not pass the same vertex twice. Two paths are distinct if the sets or the orders of visited vertices are different. Since the answer can be large, output it modulo $ 10^{9}+7 $ .

## 说明/提示

There are $ 9 $ paths in the first example (the vertices are numbered on the picture below): 1, 2, 3, 1-2, 2-1, 1-3, 3-1, 2-1-3, 3-1-2.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF830D/ae28806f7f5a770594827dbb3352d89115c44dfa.png)Singer $ 2 $ -house

## 样例 #1

### 输入

```
2
```

### 输出

```
9
```

## 样例 #2

### 输入

```
3
```

### 输出

```
245
```

## 样例 #3

### 输入

```
20
```

### 输出

```
550384565
```

# 题解

## 作者：猪脑子 (赞：19)

首先，对于一个n，我们思考一下如何求解这个n的路径条数，不妨设其为$f_n$。

一个思路是考虑这条路径是否经过根节点，那么有几种情况：

这条路径只包含根节点；这条路径从下面某棵子树内一条路径连上来，再连接下去

乍一看似乎能做，但是我们会发现，从一棵子树中连上来的路径可能会连回同一棵子树，那么如果我们要算$f_n$，就必须算出从深度为n-1的子树内选择两条不相交的路径的方案数$g_{n-1}$。

你可能会想继续讨论$g_n$的方案数，但是你会发现，你要算$g_n$，还得算深度为n-1的树种选三条不相交路径的方案数……

既然如此，~~我们观察一下数据范围，~~ 不妨多设一维状态：

令$f_{n,k}$代表在深度为$n$的树中选择$k$条不相交路径的方案数。

看上去似乎变难了，毕竟原题只让我们求一条路径的方案数。

但是我们发现，这个“加强”版本似乎更好做了，因为转移变得十分简单：

$$f_{n,k}=\sum_{i+j=k-1}f_{n-1,i}\times f_{n-1,j}$$

$$+\sum_{i+j=k}f_{n-1,i}\times f_{n-1,j}$$

$$+\sum_{i+j=k}f_{n-1,i}\times f_{n-1,j}\times (2k)$$

$$+\sum_{i+j=k+1}f_{n-1,i}\times f_{n-1,j}\times (k+1)\times k$$

这四种情况分别是：根节点单独形成一条链、根节点不属于任何一条链、根节点与左右子树内某条链连在一起（分从链的尾端连上来和连到链的开头两种情况）、还有根节点从某条链上连上再连到另一条链上去。

边界条件也很显然，这里就不写了。

代码如下，我写的是记忆化搜索

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;
const int Mod=1000000007;
int f[410][410];
int F(int n,int k)
{
	if(!k)return 1;
	if(n==1){
		return k==1;
	}
	if(f[n][k]!=-1)return f[n][k];
	f[n][k]=0;
	for(int i=0;i<=k;i++)
		f[n][k]=(f[n][k]+1ll*F(n-1,i)*F(n-1,k-i))%Mod;
	for(int i=0;i<k;i++)
		f[n][k]=(f[n][k]+1ll*F(n-1,i)*F(n-1,k-i-1))%Mod;
	for(int i=0;i<=k;i++)
		f[n][k]=(f[n][k]+1ll*F(n-1,i)*F(n-1,k-i)%Mod*k*2)%Mod;
	for(int i=0;i<=k+1;i++)
		f[n][k]=(f[n][k]+1ll*F(n-1,i)*F(n-1,k+1-i)%Mod*(k+1)*k)%Mod;
	return f[n][k];
}
int main()
{
	int n;scanf("%d",&n);
	memset(f,-1,sizeof(f));
	printf("%d\n",F(n,1));
	return 0;
}
```

~~好不容易自己搞出2800的题，而且还没有别人发题解，怎么着也得水一下啊对不对~~

---

## 作者：zhoukangyang (赞：13)

[来蒟蒻的博客园里吃](https://www.cnblogs.com/zkyJuruo/p/13891855.html)

## $\texttt{Solution}$
首先考虑 $\texttt{dp}$ 维护题目要求的深度为 $i$, 每个节点最多经过一次的不同有向路径数量 $f_i$。

明显的，只维护这个东西是不对的，因为忽视了这样的情况：
![2020-10-28 16-15-48屏幕截图.png](https://i.loli.net/2020/10/28/diZ86qk4mUBxg35.png)

这样子这条路径是由原来的被蓝色圈圈包住的两个部分转移而来。

那么考虑记录 $g_i$ 为两条不相交的有向路径数量。

然后蒟蒻兴冲冲地去 [尝试了](https://www.luogu.com.cn/paste/sk149e8q), 并过了前两个样例，但是过不了第三个样例，这是为什么？

发现 $g_i$ 也有可能是由三条不相交的有向路径转移而来！

那么正解就浮出水面了：维护深度为 $i$,  $j$ 条不相交的有向路径数量 $dp_{i,j}$。

转移如果想明白了状态其实很简单。这里还是说一下。

首先用背包求出深度为 $i-1$,  和为 $j$ 条不相交的有向路径数量 : `bb[j] += dp[i - 1][k] * dp[i - 1][j - k]`

第一种转移：根结点独立，然后其他的路径让两个子树自由组合 : `dp[i][j] += bb[j - 1] + 2 * dp[i - 1][j - 1]`

第二种转移：路径不包括根结点，或根结点为路径起点或终点： `dp[i][j] += (2 * j + 1) * bb[j] + (4 * j + 2) * dp[i - 1][j]`

第三种转移：路径包括根结点，且连接两条原来在子树中是两条链： `dp[i][j] += j * (j + 1) * bb[j + 1] + 2 * j * (j + 1) * dp[i - 1][j + 1]`

时间复杂度 $O(n^3)$, 可以卷积劣化到 $O(n^2 \log n)$, 空间复杂度 $O(n^2)$, 可以滚动数组优化到 $O(n)$。


## $\texttt{Code}$

```cpp
#include<bits/stdc++.h>
#define L(i, j, k) for(int i = j; i <= k; i++) 
#define R(i, j, k) for(int i = j; i >= k; i--) 
using namespace std;
const int N = 444;
const int mod = 1e9 + 7;
int n, dp[N][N], bb[N];
int main() {
    scanf("%d", &n);
    dp[1][1] = 1;
    L(i, 2, n) {
        fill(bb, bb + n + 1, 0);
        L(j, 1, n) L(k, 0, j) (bb[j] += 1ll * dp[i - 1][k] * dp[i - 1][j - k] % mod) %= mod;
        dp[i][1] = 1;
        L(j, 1, n) {
            int t = 0;
            (dp[i][j] += (2ll * j + 1) * bb[j] % mod) %= mod;
            (dp[i][j] += (4ll * j + 2) % mod * dp[i - 1][j] % mod) %= mod;
            (dp[i][j] += 1ll * j * (j + 1) % mod * bb[j + 1] % mod) %= mod;
            (dp[i][j] += 2ll * j * (j + 1) % mod * dp[i - 1][j + 1] % mod) %= mod;
            (dp[i][j] += bb[j - 1] % mod) %= mod;
            (dp[i][j] += 2ll * dp[i - 1][j - 1] % mod) %= mod;
        }
    }
    printf("%d\n", dp[n][1]);
    return 0;
}
```

---

## 作者：Alex_Wei (赞：9)

- Update on 2022.9.25：修改表述。

> [CF830D Singer House](https://www.luogu.com.cn/problem/CF830D)

设 $f_i$ 表示有向路径的数量，考虑若干种情况。

- 不经过根，$2f_{i - 1}$。
- 恰好以根为一端，$4f_{i - 1}$。
- 完全跨过根的两个子树，$2f_{i - 1} ^ 2$。
- 根，$1$。
- 完全跨过根但在一个子树内。设 $g_i$ 表示两条不交的有向路径的数量，$2g_i$。

$$
f_i = 6f_{i - 1} + 2f_{i - 1} ^ 2 + 1 + 2g_i
$$

考虑算 $g_i$，发现当一条路径经过根又回到其子树，且另一条路径也在相同子树时，需要用到三条不交有向路径的方案数。这样下去不行，结合 $n\leq 400$ 的数据范围，我们再记录一维表示路径条数。

设 $f_{i, j}$ 表示 $i$ 树 $j$ 条有向路径的方案数，转移枚举 $j, k$ 表示左子树和右子树的原路径条数。

- 不经过根，贡献系数 $1$。
- 以根为一个端点，共有 $2(j + k)$ 个端点可以与根相接，贡献系数 $2(j + k)$。
- 新增根单点，贡献系数 $1$。
- 两条路径通过根合并成一条，枚举出点和入点，减掉成环的情况，贡献系数 $(j + k) ^ 2 - (j + k)$。

由于 $i$ 每次加 $1$ 最多消灭一条路径，所以路径条数维度只需开到 $n - i + 1$。

答案即 $f_{n, 1}$，时间复杂度 $\mathcal{O}(n ^ 3)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 400 + 5;
const int mod = 1e9 + 7;
long long n, f[N], g[N];
int main() {
  g[0] = 1, cin >> n;
  for(int i = 0; i < n; i++) {
    for(int j = 0; i + j - 1 <= n; j++) g[j] %= mod;
    swap(f, g), memset(g, 0, sizeof(g));
    for(int j = 0; i + j - 1 <= n; j++)
      for(int k = 0; i + j + k - 1 <= n; k++)
        if(f[j] && f[k]) {
          long long v = f[j] * f[k] % mod;
          g[j + k + 1] += v;
          g[j + k] += v * (2 * (j + k) + 1);
          g[j + k - 1] += v * ((j + k) * (j + k) - j - k);
        }
  }
  cout << g[1] % mod << endl;
  return 0;
}
```

---

## 作者：_Felix (赞：6)

update: 2021/9/26 感觉之前写的太奇怪了修改一下

看的 [zzd](https://www.cnblogs.com/zhouzhendong/p/CF830D.html) 的博客，大家可以自己看。

设 $f_{i,j}$ 为高度为 $i$ 的二叉树中能够选出多少组 “一组 不相交的 $j$ 条路径”
。

每次把两个高度为 $i-1$ 的二叉树合并为高度为 $i$ 的二叉树。

然后会有四种情况
- 什么也不干
- 增加一条路径，即根节点
- 将根节点和一条路径合并
- 将根节点和两条路径合并

第一次做的时候被 “根节点与两条路径合并困扰过”，我就写一下这个。

下面这个是我的写法。（当然和周指导的`Add(f[i][j + k - 1], 2ll * C(j+k,2) % mod * t % mod); 
`也没有本质区别）

```
void Add(int &x, int y){
	x = (x + y) % mod;
} 
Add(f[i][j + k - 1], 1ll * (j + k) * (j + k - 1) % mod * t % mod); 
```

考虑选出一个有序路径对 $(A-B,C-D)$ ，

那么与根合并后产生的那条路径就是 $A-B-root-C-D$ 。

这样能够不重复，不遗漏。

```cpp
const int mod = 1e9 + 7, N = 410;
int n, f[N][N];
void Add(int &x, int y){
	x = (x + y) % mod;
} 
int main(){
	scanf("%d", &n); 
	f[1][0] = f[1][1] = 1;
	for(int i = 2; i <= n; i++)
		for(int j = 0; j <= n; j++)
			for(int k = 0; j + k <= n; k++){
				int t = 1ll * f[i - 1][j] * f[i - 1][k] % mod;
				Add(f[i][j + k], t); //不合并 
				Add(f[i][j + k + 1], t); //加入根节点 
				Add(f[i][j + k], 2ll * (j + k) % mod * t % mod); //选一条路径与根合并
				Add(f[i][j + k - 1], 1ll * (j + k) * (j + k - 1) % mod * t % mod); //选两条路径与根合并。
			}
	printf("%d\n", f[n][1]);
	return 0;
}
```
        

---

## 作者：serverkiller (赞：3)

前言:如果公式挂了请去博客页面食用

## 题意

一个$n$层的满二叉树上的父亲向子树内每个结点连,使得最后有且仅有1条边.

在最后的图上,求取1条不重复经过结点的有向路径的方案数

## solution

~~想了整整一个晚上~~

发现直接按照层数$dp$的话很难转移

我们考虑一个题目的加强版:

$dp_{i,j}$表示从前$i$层选出$j$条不相交路径的方案数

我们发现这个$dp$非常好合并,只需要在合并时讨论父亲和孩子的关系,即是否被包括在了同一条路径,或者是另外取了一条路径,或者是完全没有取这个点

这样我们就有了一个大力的$dp$转移的式子:
$$
\text{suppose }x=dp_{i-1,j}\times dp_{i-1,k}\\
dp_{i,j+k}+=x+2\times x\times (j+k)\\
dp_{i,j+k-1}+=x \times (j + k) \times (j + k - 1)\\
dp_{i,j+k}+=x
$$
但是这样的话这个$j$的状态数就到达了$2^n$的级别了

我们注意到我们需要的答案是$dp_{n,1}$而在最后能转移到这个状态的一定在$n$以内,所以我们只需要保留$n$以内的条数就可以了

复杂度:$O(n^3)$ 即$O(\text{能过})$

代码:

```cpp
#include<bits/stdc++.h>
#define N 1005
#define int long long
using namespace std;

template <typename T>

void read(T &a)
{
	T x = 0,f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9')
	{
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	a = x * f;
}

template <typename T,typename... Args> void read(T &t,Args &... args) {read(t); read(args...); }

const int mod = 1e9 + 7;
int n,dp[N][N];

int ksm(int a,int b)
{
	int res = 1;
	while (b)
	{
		if (b & 1) res = res * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return res;
}

signed main()
{
	read(n);
	dp[1][0] = dp[1][1] = 1;
	for (int i = 2; i <= n; i++)
	{
		for (int j = 0; j <= n; j++)
		{
			for (int k = 0; k <= n - j; k++)
			{
				int tmp = dp[i - 1][j] * dp[i - 1][k] % mod;
				dp[i][j + k] = (dp[i][j + k] + tmp + tmp * (j + k) % mod * 2 % mod) % mod;
				dp[i][j + k - 1] = (dp[i][j + k - 1] + tmp * (j + k) % mod * (j + k - 1) % mod) % mod;
				dp[i][j + k + 1] = (dp[i][j + k + 1] + tmp) % mod;
			}
		}
	}
	printf("%lld\n",dp[n][1]);
	return 0;
}
```



---

## 作者：lfxxx (赞：1)

考虑依靠树的结构拆解问题，从一个 $u-1$ 层的二叉树到 $u$ 层的二叉树，有向路径在两棵子树间的合并是简单的，唯一困难的一点是对于一条有向路径可能被从中间拆开，在根处中转一下，这要怎么处理？记录下长度为 $i$ 的路径数量？不仅状态多，最后还要求解多个状态的答案和，考虑设计 $dp_{u,i}$ 表示深度为 $u$ 的二叉树，无序地选出 $i$ 条不交的有向路径的方案，从中间拆开就变成了把原来的两条路径加上根拼起来，虽然状态数还是很多，但是最后只要求 $dp_{k,1}$，我们来写一下转移，转移形如不管根，对两棵子树直接做背包合并后看要不要把根作为单独的一条路径加入，以及在合并的时候给一条路径前后加上根，在合并的时候在两棵子树中各选出一条路径拼起来，在一棵子树中选两条不交路径拼起来，也就是 $dp_{u,i} = (\sum_{j=0}^i dp_{u-1,j} \times dp_{u-1,i-j})+(\sum_{j=0}^i 2 \times dp_{u-1,j+1} \times (j+1) \times j \times dp_{u-1,i-j})+(\sum_{j=0}^i 2 \times dp_{u-1,j} \times dp_{u-1,i-j} \times 2 \times j)+(\sum_{j=0}^{i-1} dp_{u-1,j} \times dp_{u-1,i-j-1})+(\sum_{j=0}^{i+1} 2 \times dp_{u-1,j} \times dp_{u-1,i+1-j} \times (i+1-j) \times j)$。

注意到最后只要 $dp_{k,1}$，而 $dp_{i,j}$ 在每一轮 dp 中第二维最多向下影响一位，所以我们将第二维限制在 $k$ 以内即可，时间复杂度 $O(k^3)$。


```cpp
#include<bits/stdc++.h>
const int mod = 1e9+7;
using namespace std;
const int maxn = 450;
int dp[maxn][maxn];
int k;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>k;
    dp[1][0]=1,dp[1][1]=1;
    for(int u=2;u<=k;u++){
        for(int i=0;i<=k;i++){
            //dp[u][i]
            for(int j=0;j<=i;j++){
                dp[u][i]=(dp[u][i]+1ll*dp[u-1][j]*dp[u-1][i-j]%mod)%mod;
                dp[u][i]=(dp[u][i]+1ll*2*dp[u-1][j+1]%mod*(j+1)%mod*j%mod*dp[u-1][i-j]%mod)%mod;
                dp[u][i]=(dp[u][i]+1ll*2*dp[u-1][j]%mod*dp[u-1][i-j]%mod*2%mod*j%mod)%mod;
            }
            for(int j=0;j<i;j++) dp[u][i]=(dp[u][i]+1ll*dp[u-1][j]*dp[u-1][i-1-j]%mod)%mod;
            for(int j=0;j<=i+1;j++) dp[u][i]=(dp[u][i]+1ll*2*dp[u-1][j]%mod*dp[u-1][i+1-j]%mod*(i+1-j)%mod*j%mod)%mod;
        }
    }
    cout<<dp[k][1]<<'\n';
    return 0;
}
```

---

## 作者：MiniLong (赞：0)

[题目链接](https://www.luogu.com.cn/problem/CF830D)

观察到一个深度为 $u$ 的子树（简称子树 $u$）对答案的贡献是从外面进来转一圈出去，然后又进来转出去......所以考虑设 $dp_{u,i}$ 为进入 $u$ 的子树 $i$ 次游走出去的方案数。节点 $u$ 的贡献有几种。
1. 外面 $\to u \to$ 左/右子树，这个转移是 $\sum\limits_{i=0}^{siz_{ls}} \sum\limits_{j=0}^{siz_{rs}} \binom{i+j}{i} (i+j)dp_{u-1,i}dp_{u-1,j} \to dp_{u,i+j}$。

2. 外面 $\to$ 左/右子树 $\to u \to $ 外面，这个转移也是  $\sum\limits_{i=0}^{siz_{ls}} \sum\limits_{j=0}^{siz_{rs}} \binom{i+j}{i} (i+j) dp_{u-1,i}dp_{u-1,j} \to dp_{u,i+j}$。

3. 外面 $\to$ 左/右子树 $\to u \to$ 左/右子树 $\to$ 外面，这个的方案是 $\sum\limits_{i=2}^{siz_{ls}} \sum\limits_{j=0}^{siz_{rs}} \binom{i+j-1}{i-1} (i-1) dp_{u-1,i}dp_{u-1,j} \to dp_{u,i+j-1}$，$\sum\limits_{i=0}^{siz_{ls}} \sum\limits_{j=2}^{siz_{rs}} \binom{i+j-1}{j-1}(j-1)dp_{u-1,i}dp_{u-1,j} \to dp_{u,i+j-1}$，$\sum\limits_{i=1}^{siz_{ls}} \sum\limits_{j=1}^{siz_{rs}} \binom{i+j-1}{i}idp_{u-1,i}dp_{u-1,j}\to dp_{u,i+j-1}$，$\sum\limits_{i=1}^{siz_{ls}} \sum\limits_{j=1}^{siz_{rs}} \binom{i+j-1}{j}jdp_{u-1,i}dp_{u-1,j}\to dp_{u,i+j-1}$。

4. 外面 $\to$ 左/右子树 $\to$ 外面，方案数为 $\sum\limits_{i=0}^{siz_{ls}} \sum\limits_{j=0}^{siz_{rs}} \binom{i+j}{i} dp_{u-1,i} dp_{u-1,j} \to dp_{u,i+j}$。

5. 外面 $\to u \to$ 外面，方案为 $\sum\limits_{i=0}^{siz_{ls}} \sum\limits_{j=0}^{siz_{rs}} \binom{i+j}{i} (i+j+1)dp_{u-1,i} dp_{u-1,j} \to dp_{u,i+j+1}$。

注意到进入一个子树最多 $\Theta(n)$ 次，所以不用枚举到 $siz$ 那么大啦~

答案就是 $dp_{n,1}$。

复杂度 $\Theta(n^3)$。

---

## 作者：Komomo (赞：0)

发现 $k=i$ 与 $k=i-1$ 是关联的，令 $f_i$ 表示 $k=i$ 的答案，但是这种状态对于合并路径转移信息不足，于是新增一维。

令 $f_{i,j}$ 表示当 $k=i$ 时选出 $j$ 条有向链的方案数。枚举左右子树的选链数 $j,k$，组合方案数为 $t=f_{i-1,j}f_{i-1,k}$。

- 不加入点：$f_{i,j+k}\leftarrow t$。
- 根单独成链：$f_{i,j+k+1}\leftarrow t$。
- 选一条路径与根组合：$f_{i,j+k}\leftarrow 2(j+k)t$，即把根放到链头或链尾。
- 两条路径一起与根组合：$f_{i,j+k-1}\leftarrow 2\dbinom{j+k}{2}t$，选两条路径 $A\leadsto B$ 与 $C\leadsto D$，则有 $A\leadsto B\rightarrow rt\rightarrow C\leadsto D$ 和 $C\leadsto D\rightarrow rt\rightarrow A\leadsto B$ 两种选法。

时间复杂度 $\mathcal O(n^3)$。

---

## 作者：daniEl_lElE (赞：0)

考虑 $dp_{i,j}$ 表示一个深度为 $i$ 的子树中选出 $j$ 条无序链的方案。

* 当根节点单独成链时：$dp_{i,j}\times dp_{i,k}\to dp_{i+1,j+k+1}$；
* 当根节点连在某条链的前或后时：$dp_{i,j}\times dp_{i,k}\times2(j+k)\to dp_{i+1,j+k}$；
* 当根节点连了两条链时：$dp_{i,j}\times dp_{i,k}\times(j+k)(j+k-1)\to dp_{i+1,j+k-1}$；
* 当根节点不在链上：$dp_{i,j}\times dp_{i,k}\to dp_{i+1,j+k}$。

复杂度 $O(n^3)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
const int mod=1e9+7;
//Combinatorics
int qp(int a,int b){
	if(b<0){
		return qp(qp(a,mod-2),-b);
	}
	int ans=1;
	while(b){
		if(b&1) (ans*=a)%=mod;
		(a*=a)%=mod;
		b>>=1;
	}
	return ans;
}
int fac[3000005],inv[3000005];
void init(){
	fac[0]=1; for(int i=1;i<=3000000;i++) fac[i]=fac[i-1]*i%mod;
	inv[3000000]=qp(fac[3000000],mod-2); for(int i=2999999;i>=0;i--) inv[i]=inv[i+1]*(i+1)%mod;
}
int C(int i,int j){
	if(i<0||j<0||i<j) return 0;
	return fac[i]*inv[j]%mod*inv[i-j]%mod;
}
int dp[405][405],pw[405];
signed main(){
	pw[0]=1; for(int i=1;i<=400;i++) pw[i]=pw[i-2]*2%mod;
	int n,ans=0; cin>>n;
	dp[1][0]=dp[1][1]=1;
	for(int i=2;i<=n;i++){
		for(int j=0;j<=n;j++){
			for(int k=0;k<=n;k++){
				if(j+k+1<=n) (dp[i][j+k+1]+=dp[i-1][j]*dp[i-1][k])%=mod;
				if(j+k<=n) (dp[i][j+k]+=dp[i-1][j]*dp[i-1][k]%mod*2*(j+k)+dp[i-1][j]*dp[i-1][k])%=mod;
				if(j+k-1<=n&&j+k-1>=1) (dp[i][j+k-1]+=dp[i-1][j]*dp[i-1][k]%mod*(j+k)*(j+k-1))%=mod;
			}
		}
	}
	cout<<dp[n][1];
	return 0;
}

```

---

