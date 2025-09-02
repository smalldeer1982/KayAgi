# [AGC062B] Split and Insert

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc062/tasks/agc062_b

$ 1 $ から $ N $ までの整数からなる順列 $ A=(A_1,A_2,\dots,A_N) $ があります。はじめ $ A_i=i\ (1\leq\ i\ \leq\ N) $ です。

高橋君はこの順列に対し以下のような操作を $ K $ 回行います。

- $ 0\ \leq\ k\ <\ N $ を満たす整数 $ k $ を選ぶ。$ A $ の後ろ $ k $ 項を前 $ N-k $ 項に挿入する。より正確には、$ A $ を以下の条件を満たす長さ $ N $ の好きな順列 $ A' $ で置き換える。
  - $ (A_1,A_2,\dots,A_{N-k}) $ は $ A' $ の（連続とは限らない）部分列である。
  - $ (A_{N-k+1},A_{N-k+2},\dots,A_{N}) $ は $ A' $ の（連続とは限らない）部分列である。
 
$ i $ 回目の操作で選んだ $ k $ を $ k_i $ としたとき、一連の操作にかかるコストは $ \sum_{i=1}^{K}k_iC_i $ です。

高橋君は $ K $ 回の操作の後、$ A=(P_1,P_2,\dots,P_N) $ が成り立つように操作を行いたいです。

そのように一連の操作を行うことが可能か判定してください。可能な場合、そのような一連の操作にかかるコストの最小値を求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 100 $
- $ 1\ \leq\ K\ \leq\ 100 $
- $ 1\ \leq\ C_i\ \leq\ 10^9 $
- $ (P_1,P_2,\dots,P_N) $ は $ 1 $ から $ N $ までの整数からなる順列
- 入力される値はすべて整数
 
### Sample Explanation 1

操作で $ k=2 $ とし、$ A_3=3 $ を $ A_1,A_2 $ より前に、 $ A_4=4 $ を $ A_1,A_2 $ の後に挿入することで $ A=(3,1,2,4) $ とすることができ、 $ A=(P_1,P_2,P_3,P_4) $ が成り立ちます。この操作のコストは $ 2\ \times\ C_1\ =\ 6 $ です。 操作後、 $ A=(P_1,P_2,P_3,P_4) $ が成り立つように操作するとき、コストの最小値は $ 6 $ であることが証明できます。

### Sample Explanation 2

操作後、$ A=(P_1,P_2,P_3,P_4) $ が成り立つように操作することはできません。

## 样例 #1

### 输入

```
4 1
3
3 1 2 4```

### 输出

```
6```

## 样例 #2

### 输入

```
4 1
3
4 3 2 1```

### 输出

```
-1```

## 样例 #3

### 输入

```
20 10
874735445 684260477 689935252 116941558 915603029 923404262 843759669 656978932 286318130 255195090
11 15 20 10 6 8 18 2 12 4 9 13 19 3 16 7 14 17 5 1```

### 输出

```
7372920743```

# 题解

## 作者：EuphoricStar (赞：9)

妙妙题。

像这种最优化问题，数据范围又比较小，大概率不是贪心，想 dp。

正着做不好做，因为你无法知道序列变成了什么样子，没有任何信息能记录到状态里面。

考虑逆序操作。每次相当于取出一个子序列，放到后面。最终目标是将数组排成升序。

考虑区间 dp，设 $f_{k,i,j}$ 为进行完第 $k \sim K$ 次操作，已经把数组中**值为 $i \sim j$ 的数排好序**。有转移：

- $f_{k,i,j} \gets f_{k+1,i,j}$，表示这次操作可以不动；
- $f_{k,i,j} \gets f_{k+1,i,x} + f_{k+1,x+1,j} + c_k \times (j - x), x \in [i,j)$，表示选权值在 $[x + 1, j]$ 之中的数，拎到最后面，花费是 $c_k \times (j - x)$。

初值是 $f_{m+1,i,j} = 0$，其中权值在 $[i,j]$ 之中的数已经在原排列中排好序。

答案就是 $f_{1,1,n}$。

时间复杂度 $O(n^3k)$。

[code](https://atcoder.jp/contests/agc062/submissions/41618049)

---

## 作者：Mirage_Insane (赞：2)

读完题之后发现直接做不太好做，那么正难则反，我们可以将问题转化成：每次取一个子序列放到序列末尾，问如何让原序列变为升序。

发现 $N$ 和 $K$ 都很小，~~而且这题好像被放在区间 dp 的练习题里，~~ 考虑区间 dp。设 $dp_{k, i, j}$ 表示当前已经完成了 $k$ 次操作，并且值 $i$ 到 $j$ 已经**相对排好序**的最小花费。 由于我们是反着来的，所以第一维 $k$ 应该倒序枚举。

首先根据原序列初始化，若在原序列中，$i$ 到 $j$ 已经相对有序，那么有：$dp_{m + 1, i, j} = 0$。转移方程也很显然，有：

$$dp_{k, i, j} = \min(dp_{k + 1, i, j}, dp_{k + 1, i, mid} + dp_{k + 1, mid + 1, r} \times c_k \times (r - mid))$$

其中：$dp_{k + 1, i, j}$ 表示跳过该次操作，$c_k \times (r - mid)$ 表示将值为 $mid + 1$ 到 $r$ 放到序列末尾的花费。

答案即为 $dp_{1, 1, N}$。

### Code

```cpp
#define Vanishment return
#define This 0
#define World ; 
#include<bits/stdc++.h>
using namespace std;
#define SF scanf
#define PF printf
#define int long long
int a[105], dp[105][105][105], b[105];
signed main() {
    int n, m, x;
    SF("%lld%lld", &n, &m);
    for(int i = 1; i <= m; i++) SF("%lld", &a[i]);
    for(int i = 1; i <= n; i++) SF("%lld", &x), b[x] = i;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            for(int k = 1; k <= m + 1; k++) dp[k][i][j] = 1e18;
        }
    }
    for(int i = 1; i <= n; i++) {
        for(int j = i; j <= n;) {
            dp[m + 1][i][j] = 0;
            if(b[j + 1] > b[j]) j++;
            else break;
        }
    }
    for(int k = m; k >= 1; k--) {
        for(int len = 1; len <= n; len++) {
            for(int i = 1; i + len - 1 <= n; i++) {
                int j = i + len - 1;
                dp[k][i][j] = dp[k + 1][i][j];
                for(int mid = i; mid < j; mid++) dp[k][i][j] = min(dp[k][i][j], dp[k + 1][i][mid] + dp[k + 1][mid + 1][j] + (j - mid) * a[k]);
            }
        }
    }
    PF("%lld", dp[1][1][n] == 1e18 ? -1ll : dp[1][1][n]);
    Vanishment This World
} 
```

---

## 作者：Comentropy (赞：1)

自己做出来了 ovo！很开心，写篇题解庆祝一下。

## 题意转述

对 $[1,2,\dots,n]$ 操作，每次选择一个后缀把它插进前面，要求插完之后其内部相对位置不变。代价是每轮给定的 $c_i$，与选择后缀的长度相乘。最小化代价。

## 分析

这个操作真的很难，所以先考虑刻画。由于，每次操作之后，前后两部分内部的顺序关系完全没有改变。所以如果用 $\prec$ 表示值之间的顺序关系，$i\prec j$ 当且仅当 $i<j \wedge p_i<p_j$，其中 $p_i$ 表示 $i$ 在排列中的位置。（显然是严格偏序）。我们又称：满足 $a_1\prec a_{2} \prec \dots \prec a_k$ 的 $[a_1,a_2,\dots,a_k]$ 是一条链。

可以看出，原来的操作对应这样一个过程：从链的后缀处断开。此时，两部分不再能比较。或者说，新的两条链根本没有什么关系了。这两部分不交，且合起来可以得到一个序列，它俩为这个序列的子序列（正是题面中叙述操作的严谨版本）。现在的链集合对应所有这样的序列。

对于有多条链的情况，仍然从这些链的后缀处断开拆链。不过同一个时刻可以操作很多链。这样处理后缀为什么是对的？个人认为不难考虑，留给读者自己思考。（考虑操作之间的映射，变化前后序列的样子）

拆链不太好做（硬做也可以，不过观察起来比较反人类），我们倒过来考虑从现在序列的链集合进行合链的过程，它的最终目的是合成 $[1,2,\dots,n]$，这看起来就很不错。

但是仍然很难做啊。我们需要一些性质——这些链到底是啥。观察拆链的过程，每次都拆链的后缀，而一开始的链又是 $1$ 到 $n$ 的序列，所以拆出来的始终是—— **一段区间**。

很美妙！这样我们其实就知道怎么做了。合链的过程就是拼接两个区间的过程。于是考虑设计区间 DP：设 $f_{k,i,j}$ 表示考虑前 $k$ 轮合链，合出 $[i,j]$ 的最小代价，最终需要合到 $[1,n]$。转移比较容易。（注意合链和拆链是相反的过程，对应的，代价也需要倒过来）。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N=110;
int n,K,a[N],p[N];
LL f[N][N][N],c[N];
inline bool ckmin(LL &x,LL y){
    return (x>y)?(x=y,true):false;
}
int main(){
    memset(f,0x3f,sizeof(f));
    scanf("%d%d",&n,&K);
    for(int i=1;i<=K;i++)   scanf("%lld",&c[i]);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]),p[a[i]]=i;
    for(int i=1;i<=n;i++)
        for(int j=i;j<=n;j++){
            bool flg=true;
            for(int k=i+1;k<=j;k++)
                if(p[k]<p[k-1]){flg=false;break;}
            if(flg) f[0][i][j]=0;
        }
        // 呃！手模一下，它的花费其实是倒过来的
    /*
    HandMade:
    5 2
    3 4
    3 1 2 5 4
    */
    reverse(c+1,c+1+K); // added.
    for(int k=1;k<=K;k++){
        for(int i=1;i<=n;i++){
            for(int j=i;j<=n;j++){
                f[k][i][j]=f[k-1][i][j];
                for(int mid=i;mid<j;mid++){
                    ckmin(f[k][i][j],f[k-1][i][mid]+f[k-1][mid+1][j]+c[k]*(j-mid));
                }
            }
        }
    }
    printf("%lld\n",f[K][1][n]>1e18?-1:f[K][1][n]);
    return 0;
}
```

---

## 作者：cwfxlh (赞：1)

# [AT_agc062_b](https://www.luogu.com.cn/problem/AT_agc062_b)           

题解思路都是时光倒流，来点不一样的做法。          

考虑正着做是什么样子。           

最开始我们有一个 $n$ 个元素的序列，第一次操作可以从它末尾选 $k_1$ 个元素，将序列划成两半。         

考虑第二次操作。容易发现，取走的 $k_2$ 个元素必定是取两份序列的后缀，于是序列被划成四份。       

接下来思路就显然了！这四个序列之间是独立的，所以做第三次操作的时候可以从这四个序列中再任取几份后缀。我们把取后缀的过程看成划分，那么操作的过程如下图所示。           

![世界名画](https://cdn.luogu.com.cn/upload/image_hosting/4hois74c.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)         

于是操作变成了给当前已有的区间划分后缀，最后要求是每个区间内部都是排好序的。使用区间 dp 即可，状态 $dp_{i,l,r}$ 表示区间 $[l,r]$ 在 $[i,k]$ 的操作中变为合法的最小代价。复杂度 $O(n^3k)$。         

代码：      


```cpp
#include<bits/stdc++.h>
#define inf 1000000000000000ll
#define int long long
using namespace std;
int n,k,c[500003],p[500003],wz[500003],dp[103][103][103];
signed main(){
    ios::sync_with_stdio(false);
    cin>>n>>k;
    for(int i=1;i<=k;i++)cin>>c[i];
    for(int i=1;i<=n;i++)cin>>p[i];
    for(int i=1;i<=n;i++)wz[p[i]]=i;
    for(int i=1;i<=n;i++){
        for(int j=i,u=1;j<=n;j++){
            if(j!=i&&wz[j]<wz[j-1])u=0;
            if(u)dp[k+1][i][j]=0;
            else dp[k+1][i][j]=inf;
        }
    }
    for(int i=k;i;i--){
        for(int j=1;j<=n;j++){
            for(int u=j+1;u<=n;u++){
                dp[i][j][u]=dp[i+1][j][u];
                for(int o=j;o<u;o++)dp[i][j][u]=min(dp[i][j][u],dp[i+1][j][o]+dp[i+1][o+1][u]+(u-o)*c[i]);
            }
        }
    }
    if(dp[1][1][n]<inf/3)cout<<dp[1][1][n];
    else cout<<-1;
    return 0;
}
```

---

## 作者：_lqs_ (赞：0)

先考虑一个经典问题：给定排列 $a$，每次拉一个子序列到 $a$ 的开头/末尾，求使其变成升序的最少操作次数。

这个问题显然是贪心，把能拉出来的值域上连续的子序列全拉出来即可。

那么回归原问题，把末尾随意插进序列中是不好做的，受上面那个问题的启发，我们将问题反过来考虑：将排列 $a$ 中一个子序列拉到末尾，对应权值是 $c$ 数组的逆序，求最小代价。

加入了 $c_{i}$ 的权，那么显然是 dp，我们设 $f_{i,j,k}$ 表示已经考虑了第 $i$ 至第 $K$ 次操作，已经将序列中 $[j,k]$ 的相对位置排好序的最小代价。那么转移是简单的：

$f_{i,j,k}=f_{i+1,j,k}$

$f_{i,j,k}=\max\limits_{g=j}^{k-1}\{f_{i+1,j,g}+f_{i+1,g+1,k}+c_{i} \times (k-g)\}$

时间复杂度 $O(n^3k)$。

---

## 作者：_Cheems (赞：0)

考虑时光倒流，变为每次选取一个子序列移到末尾，要使得最终序列升序。

考虑最后一次操作，则选取的点集合和没选取的点集合此前应当是内部相对顺序不变的。那么分为两个子问题：让这两个集合内部升序的最小代价。

注意到此题的代价满足乘法分配率，又因为两个集合之间的顺序我们并不关心，所以假如一轮操作同时涉及了两个不同集合，就可以将其拆为两个操作，分别操作了两个集合。

那么两个子问题完全独立。现在简单了，对值域进行区间 dp，$f_{i,l,r}$ 表示倒流完操作 $[i,k]$，其中 $[l,r]$ 范围内的元素有序的最小花费。初始化 $f_{k+1,l,r}$ 判断下一开始 $[l,r]$ 是否有序即可，转移是朴素的不再赘述。

复杂度 $O(n^3k)$。

#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define MIN(a, b) a = min(a, b)
const int N = 1e2 + 5;
int n, m, x, a[N], c[N], f[N][N][N], inf;

signed main(){
	memset(f, 0x3f, sizeof f), inf = f[0][0][0];
	cin >> n >> m;
	for(int i = 1; i <= m; ++i) scanf("%lld", &c[i]);
	for(int i = 1; i <= n; ++i) scanf("%lld", &x), a[x] = i;
	for(int i = 1; i <= n; ++i)
		for(int j = i, lst = -1; j <= n; ++j){
			if(lst > a[j]) break;
			f[m + 1][i][j] = 0;
			lst = a[j];
		}
	for(int i = m; i; --i)
		for(int l = 1; l <= n; ++l)
			for(int r = l; r <= n; ++r){
				MIN(f[i][l][r], f[i + 1][l][r]);
				for(int k = l; k < r; ++k)
					MIN(f[i][l][r], f[i + 1][l][k] + f[i + 1][k + 1][r] + c[i] * (r - k));
			}
	if(f[1][1][n] >= inf) cout << -1;
	else cout << f[1][1][n];
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/AT_agc062_b)

**题目大意**

> 给定一个排列 $p_i=i$，第 $i$ 次操作（$1\le i\le m$）可以以 $c_i\times k$ 的代价把末尾 $k$ 个元素和前 $n-k$ 个元素以任意顺序归并。
>
> 求把这个排列变成 $a_1\sim a_n$ 的最小代价。
>
> 数据范围：$n,m\le 100$。

**思路分析**

显然可以考虑时间倒流，变成把 $a_1\sim a_n$ 中的 $k$ 个元素放到末尾。

考虑最后一次操作（倒流前的第一次操作），显然序列中 $1\sim n-k,n-k+1\sim n$ 的相对顺序必须被满足。

注意到这两个子问题是完全独立的，即只考虑这个排列 $1\sim n-k$ 的部分，和 $n-k+1\sim n$ 的部分，分别处理后每次把选择的子序列并起来即可，显然两部分相对顺序在最后一定分别被满足。

那么这就形成了子结构，$dp_{i,l,r}$ 表示进行 $i\sim m$ 次操作后，对值域 $l\sim r$ 的元素排序的最小代价，转移为：
$$
dp_{i,l,r}=\min_{x=l}^r\{dp_{i+1,l,x}+dp_{i+1,x+1,r}+c_i(r-x)\}
$$
边界条件为初始满足的 $[l,r]$ 的 $dp_{m+1,l,r}=0$。

时间复杂度 $\mathcal O(mn^3)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=105;
const ll inf=1e18;
ll c[MAXN],f[MAXN][MAXN],g[MAXN][MAXN];
int n,k,p[MAXN],q[MAXN];
signed main() {
	scanf("%d%d",&n,&k);
	for(int i=1;i<=k;++i) scanf("%lld",&c[i]);
	for(int i=1;i<=n;++i) scanf("%d",&p[i]),q[p[i]]=i;
	memset(f,0x3f,sizeof(f));
	for(int i=1;i<=n;++i) {
		f[i][i]=0;
		for(int j=i+1;j<=n&&q[j-1]<q[j];++j) f[i][j]=0;
	}
	for(int t=k;t>=1;--t) {
		memcpy(g,f,sizeof(g));
		for(int i=1;i<=n;++i) for(int j=i+1;j<=n;++j) {
			for(int x=i;x<j;++x) g[i][j]=min(g[i][j],f[i][x]+f[x+1][j]+(j-x)*c[t]);
		}
		memcpy(f,g,sizeof(f));
	}
	printf("%lld\n",f[1][n]>inf?-1ll:f[1][n]);
	return 0;
}
```

---

## 作者：Larunatrecy (赞：0)

VP 时的思路。

首先考虑倒着，每次选择一个子序列放到最后，方便起见我们把操作序列也 reverse 一下。

这样，我们发现，如果设 $S_i$ 为覆盖了 $i$ 的操作集合（我们把 $S_i$ 默认为降序排列），那么最终 $S_i$ 相同的一定是在一起的，这样会形成若干个区间，并且这些区间的 $S_i$ 按照字典序从小到达排列。

此时唯一的限制就是：每个 $S_i$ 相同的区间内的数在 $p$ 中的位置递增。

设 $M$ 为不同的 $S_i$ 个数，考虑 dp，设 $f_{i,j}$ 表示考虑了前 $i$ 个位置，当前位置的操作集合是 **按字典序排序的** 第 $j$ 个的最小代价，转移时可以维护前缀 $\min$ 做到 $O(nM)$。

但是我们发现 $M=2^k$ 根本开不下，考虑优化一下。

注意到最终用到的只有 $O(n)$ 个区间，那么我们考虑贪心的保留权值和最小的 $n$ 个 $S_i$，这个可以用类似超级钢琴的思路求出来。

然后叫了一下发现 WA 了，再想想发现有可能一段长度很长的区间，我们想要让他取到尽可能小的权值和，但是有字典序的限制所以有可能取不到这个数，此时应该在前面 “垫” 一些段，故不一定是最小的 $n$ 个有用。

此时我们充分发挥人类智慧，保留最小的 $pn$ 个 $S_i$，实测 $p=3$ 能过。

复杂度 $O(n^2m+nm)$，跑的飞快。

~~虽然是个假做法但是复杂度比题解要优~~。

---

