# [ABC275F] Erase Subarrays

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc275/tasks/abc275_f

正整数列 $ A=(a_1,a_2,\ldots,a_N) $ が与えられます。  
あなたは次の操作を $ 0 $ 回以上何度でも繰り返せます。

- $ A $ から（空でない）連続する部分列を選び、削除する。

$ x=1,2,\ldots,M $ に対し、次の問題を解いてください。

- $ A $ の要素の総和をちょうど $ x $ にするために必要な操作回数の最小値を求めてください。ただし、どのように操作を行っても $ A $ の要素の総和をちょうど $ x $ にできない場合は代わりに `-1` と出力してください。

なお、$ A $ が空である時、$ A $ の要素の総和は $ 0 $ であるとします。

## 说明/提示

### 制約

- $ 1\ \leq\ N,M\ \leq\ 3000 $
- $ 1\ \leq\ a_i\ \leq\ 3000 $
- 入力はすべて整数

### Sample Explanation 1

操作回数が最小である操作の例を以下に示します。 - $ x=1 $ について、$ a_2,a_3,a_4 $ に対して操作をすることで $ A $ の要素の総和が $ x $ になります。 - $ x=2 $ について、$ a_3,a_4 $ に対して操作をした後、$ a_1 $ に対して操作をすることで $ A $ の要素の総和が $ x $ になります。 - $ x=3 $ について、$ a_3,a_4 $ に対して操作をすることで $ A $ の要素の総和が $ x $ になります。 - $ x=4 $ について、$ a_1,a_2,a_3 $ に対して操作をすることで $ A $ の要素の総和が $ x $ になります。 - $ x=5 $ について、$ a_2,a_3 $ に対して操作をすることで $ A $ の要素の総和が $ x $ になります。

## 样例 #1

### 输入

```
4 5
1 2 3 4```

### 输出

```
1
2
1
1
1```

## 样例 #2

### 输入

```
1 5
3```

### 输出

```
-1
-1
0
-1
-1```

## 样例 #3

### 输入

```
12 20
2 5 6 5 2 1 7 9 7 2 5 5```

### 输出

```
2
1
2
2
1
2
1
2
2
1
2
1
1
1
2
2
1
1
1
1```

# 题解

## 作者：Magic_World (赞：13)

## ABC_275-F

使用 DP 解决本问题。  

设 $f[i][j]$ 表示到下标 $i$ 为止，总和为 $j$ 的最小代价。  

考虑经典状态转移：  

- 保留 $a_i$ 的值：  
  $$
  f[i][j] = f[i-1][j-a[i]]
  $$

- 删除以 $a_i$ 为结尾的一段子区间：  

  设删除的区间左端点为 $k$, $(1\le k \le i)$  
  $$
  f[i][j] = \min\{f[k-1][j]\} +1
  $$  

DP 初始化：$f[0][0]=0$。  

直接转移时间复杂度 $O(n^2m)$，考虑进行优化。  

发现 $\min\{f[k-1][j]\}$ 可以边转移边记录，于是设 $g[j]=\min\limits_{k=1}^{i}\{f[k-1][j]\}$。  

初始化 $g[0]=0$。  

第一个转移式不变，第二个转移式变为：  
$$
f[i][j] = g[j]+1
$$  
转移完 $f[i][j]$ 后维护新的 $g[j]$：  
$$
g[j] = min\{g[j],f[i][j]\}
$$  
时间复杂度 $O(nm)$。  

代码：  

```cpp
#include<bits/stdc++.h>
#define rep(i,a,n) for(int i=a;i<=n;++i)
using namespace std;
const int N = 3007,M = 3007;
int f[N][M],n,m,a[N],g[M];
signed main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	rep(i,1,n) cin>>a[i];
	memset(f,0x3f,sizeof(f));
	memset(g,0x3f,sizeof(g));
	f[0][0] = 0,g[0] = 0;
	rep(i,1,n)
	{
		rep(j,0,m)
		{
			if(j>=a[i]) f[i][j] = f[i-1][j-a[i]];
			f[i][j] = min(f[i][j],g[j]+1);
			g[j] = min(g[j],f[i][j]);
		}
	}
	rep(i,1,m) 
	{
		if(f[n][i]==0x3f3f3f3f) f[n][i]=-1;
		cout<<f[n][i]<<'\n';	
	}
	return 0;
}

```



---

## 作者：weirdoX (赞：2)


## [Atcoder abc275F](https://atcoder.jp/contests/abc275/tasks/abc275_f)
题意：

> 给出一个长度为 $n$ 的数组 $A=(a_1,a_2,…,a_N)$，问是否能通过删掉一些子段使剩下的数之和为 $q$。若可以，求出最小操作次数，否则输出 −1。
> 对于所有的 $q\in[1,m]$ 回答这个问题，第 $i$ 行输出 $q=i$ 时的答案，每个问题互不影响。
> $1\leq n,m,a_i \leq 3000$

~~这题一看这范围便觉得像是 dp。~~ 

[安利一下我的博客](https://www.cnblogs.com/Vancezyx/)。

### 状态：
我们用 $f[i][j][k]$ 表示**考虑了前 $i$ 位，剩下的数字之和为 $j$， 第 $i$  位是否选择的最小分段数。**

### 转移方程：
$f[i][j][0] \leftarrow \min(f[i - 1][j][0], f[i - 1][j][1])$

这个容易想，因为当前这个数字选不选都不影响分段数，所以直接从 $i - 1$ 转移过来。

$f[i][j][1] \leftarrow \min(f[i - 1][j - a_i][0] + 1, f[i - 1][j - a_i][1])(j \geq a_i)$

因为当前的数字选择了保留，那么若上一个数字未保留，分段数加一，而 $j$ 要减去 $a_i$。

### 递推基：
$f[1][0][0] = 0$  
$\forall 0\le a_1\le m,f[1][a_1][1] = 0$

第一个数字比较特殊，若选择保留，不影响分段。**此处注意** $a_1 \leq m$。若它特别大，会越界！
### 答案：
对于所有的 $q\in[1,m]$，答案：

$$\min(f[n][q][0] + 1,f[n][q][1])$$

可能有人有疑问，这里为什么要 $+1$？
是因为最后一个数字为保留，而在前面的计算中并为加上未保留的最后这一段（也就是被删掉的）。

OK，看看无注释code。
## AcCode:
```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 3001;

int n, m;
int a[N], dp[N][N][2];

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	memset(dp, 0x3f, sizeof dp);
	if (a[1] <= m)
		dp[1][a[1]][1] = 0;
	
	dp[1][0][0] = 0;
	for (int i = 2; i <= n; i++)
		for (int j = 0; j <= m; j++) {
			dp[i][j][0] = min(dp[i - 1][j][0], dp[i - 1][j][1]);
			if (j >= a[i])
				dp[i][j][1] = min(dp[i - 1][j - a[i]][0] + 1, dp[i - 1][j - a[i]][1]);
		}
		
	for (int i = 1; i <= m; i++) {
		int ans = min(dp[n][i][0] + 1, dp[n][i][1]);
		printf("%d\n", ans == 0x3f3f3f3f ? -1 : ans);
	}
	return 0;
}
```


---

## 作者：TillTheEnd (赞：2)

空心蓝好简单。为什么我还是打不上蓝呢。

为什么我次次 debug 40+min 呢 /ll

---------------------

题意：给定数组 $a$，对每个 $i \in [1,m]$ 求最少做几次操作让剩余元素和为 $i$。

一次操作定义为：取出一个连续子区间并删去。

-------------------

首先区间不会重叠。如果重叠了可以只用一次删掉。

然后这很一眼 dp。我们来想想为了得到答案，什么是后续转移中需要关心的。

嗯留下来的数的总和需要知道。这一维是 $O(m)$ 的，存的下。

接着是段数怎么用最少的信息转移。把贡献放到被删除的第一个数上，我们只需要知道一个数和其上个数状态是否相同就能转移。那么再多 $O(1)$ 大小的一维表示是否被选的状态。

一个数只有选或不选，所以单个状态的转移是 $O(1)$ 的。

所以就结束了。空间复杂度 $O(nm)$，时间复杂度 $O(nm)$，当然你可以用滚动数组把空间做到 $O(m)$，但显然没必要。

这才能叫给 "beginner" 的 F 罢。

代码很好写也很好调。我的代码中 $1$ 是这个数不删除，$0$ 是被删除。

dp 题的重点应该是状态的设计。只要想着什么会影响答案，或者说，怎么用最少的信息量提供能用于转移的信息，就够了。

还有一个思考方向是什么样的情况可以一起转移。感觉这种经典线性 dp 小拓展很板啊。

```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
const int M = 3005;
int dp[M][M][2]; int n, a[M], m;
int main(){
    scanf("%d %d", &n, &m);
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0][1] = 0;
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        for(int j = 0; j <= m; j++) {
            dp[i][j][0] = min(dp[i][j][0], dp[i-1][j][1] + 1);
            dp[i][j][0] = min(dp[i][j][0], dp[i-1][j][0]);
        }
        for(int j = 0; j <= m-a[i]; j++) {
            dp[i][j+a[i]][1] = min(dp[i][j+a[i]][1], dp[i-1][j][1]);
            dp[i][j+a[i]][1] = min(dp[i][j+a[i]][1], dp[i-1][j][0]);
        }
    }
    for(int i = 1; i <= m; i++) {
        int ans = min(dp[n][i][0], dp[n][i][1]);
        printf("%d\n", ans == 0x3f3f3f3f ? -1 : ans);
    }
}
```

---

## 作者：szhqwq (赞：1)

## $\tt{Solution}$

考虑 dp。

定义 $dp_{i,j}$ 表示前 $i$ 个数删除若干个子段后和为 $j$ 所需要的最小操作次数。

对于 $a_i$ 进行分类讨论：

1. 选 $a_i$，当且仅当 $j \ge a_i$，有 $dp_{i,j} = \min\{dp_{i - 1,j - a_i}\}$；

2. 不选 $a_i$，证明 $a_i$ 被包含在需要删除的子段中，我们就以 $a_i$ 为删除子段右端点，去找最优的左端点，可以维护一个 $dp_{0 ,j}$ 的**前缀最小值**来进行这个操作，具体实现见代码。

[Link](https://atcoder.jp/contests/abc275/submissions/44675537)

---

## 作者：Tang_poetry_syndrome (赞：1)

## [ABC275F]
### 思路
考虑 DP 求解，设 $dp_{i,j}$ 为选到第 $i$ 个数，求得最小值为 $j$ 的最小代价。  
进行分类讨论：  
1. 选取 $a_i$，即 $dp_{i,j}=\min (dp_{i-1,j-a_i},dp_{i,j})$ 为防止越界，要求 $a_i\le j$。  
2. 不选 $a_i$，则删除 $1$ 到 $i-1$ 为左端点，$i$ 为右端点的一段区间，即 $dp_{i,j}=\min\{dp_{k-1,j}\}+1(1\le k<i)$。  
由于枚举左端点是 $O(n)$ 的，所以时间复杂度为 $O(n^2m)$。尝试对其优化。  
注意到两个点 $i,j(i<j)$ 中，$i$ 的最小代价在 $j$ 仍然适用，考虑记录每个状态的最小代价，则得出 $dp_{i,j}=res_j+1$。  
结果为 $dp_{i,j}=\begin{cases}\min(dp_{i-1,j-a_i},dp_{i,j})(a_i<j)\\\min(dp_{i,j},res_j+1)\end{cases}$，再用 $dp$ 维护 $res$ 即可。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[3003],tmp[3003];
int dp[3003][3003];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	memset(dp,127,sizeof(dp));
	memset(tmp,127,sizeof(tmp));
	dp[0][0]=0;tmp[0]=0;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=m;j++){
			if(j>=a[i]) dp[i][j]=dp[i-1][j-a[i]];
			dp[i][j]=min(dp[i][j],tmp[j]+1);
			tmp[j]=min(tmp[j],dp[i][j]);
		}
	}
	for(int i=1;i<=m;i++) 
		printf("%d\n",dp[n][i]>m?-1:dp[n][i]);
	return 0;
}
```

---

## 作者：TemplateClass (赞：0)

设 $\mathrm{dp} _ {i, j}$ 表示对于序列 $a _ 1 \sim a _ i$，删掉一些子段使剩下的数之和为 $j$ 的最小代价。

- 当 $j \ge a _ i$ 时，我们可以选择保留 $a _ i$ 的值，即 $\mathrm{dp} _ {i, j} = \mathrm{dp} _ {i - 1, j - a _ i}$。
- 任取 $j$，我们都可以选择删除以 $a _ i$ 为结尾的一段区间，即 $\mathrm{dp} _ {i, j} = \min\limits _ {1 \le k \le i} \!\left\{\mathrm{dp} _ {k - 1, j}\right\} + 1$。

注意到 $ \min\limits _ {1 \le k \le i} \!\left\{\mathrm{dp} _ {k - 1, j}\right\}$ 可以在转移的时候 $O(1)$ 维护，所以时间复杂度 $O(nm)$。

```cpp
#include<iostream>
#include<algorithm>
#include<cstring>

constexpr int N = 3000 + 5;
constexpr int INF = 0x3f3f3f3f;

int n, m, a[N], dp[N][N], min[N];

int main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(0), std::cout.tie(0);
	
	std::cin >> n >> m;
	for(int i = 1; i <= n; ++i) {
		std::cin >> a[i];
	}
	
	std::memset(dp, INF, sizeof dp);
	std::memset(min, INF, sizeof min);
	dp[0][0] = 0, min[0] = 0;
	
	for(int i = 1; i <= n; ++i) {
		for(int j = 0; j <= m; ++j) {
			if(j >= a[i]) dp[i][j] = dp[i - 1][j - a[i]];
			dp[i][j] = std::min(dp[i][j], min[j] + 1);
			min[j] = std::min(min[j], dp[i][j]);
		}
	}
	
	for(int i = 1; i <= m; ++i) {
		if(dp[n][i] == INF) std::cout << "-1\n";
		else std::cout << dp[n][i] << "\n";
	}
	
	return 0;
}
```

---

## 作者：highkj (赞：0)

# 思路
一眼 Dp，我们定义 $f_{i,j}$ 为前 $i$ 个数组成的和为 $j$ 的最小代价，这里在转移时明显需要分类讨论。

- 若选 $a_i$ 且 $j>a_i$ 那么 $f_{i,j}=f_{i-1,j-a_i}$。
- 否则，$f_{i,j}=f_{k,j}+1$，这里 $k$ 需要从 $1\sim i-1$ 枚举，其实就是删除的这一段左端点。

而这样的时间复杂度显然过不去，所以我们可以把不选的情况优化一下，我们可以用 $minn_j$ 来存下凑出 $j$ 的最少方案数，初始化 $minn_0=0$。
# 代码
```cpp
#include <bits/stdc++.h>
#define int long long
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define rep1(i,x,y) for(int i=x;i>=y;--i)
using namespace std ;
const int N=3100;
int f[N][N],n;
int minn[N];
int a[N],m,s[N];
signed main() {
	cin>>n>>m;
	rep(i,1,n) cin>>a[i],s[i]=s[i-1]+a[i];
	memset(f,0x3f,sizeof f);
	memset(minn,0x3f,sizeof minn);
	minn[0]=0;
	f[0][0]=0;
	rep(i,1,n) {
		rep(j,0,min(s[i],m)) {
			if(j>=a[i]) f[i][j]=min(f[i][j],f[i-1][j-a[i]]);
			f[i][j]=min(f[i][j],minn[j]+1);
			minn[j]=min(minn[j],f[i][j]);
		}
	}
	rep(i,1,m) {
		if(f[n][i]<=0x3f3f3f3f/2) cout<<f[n][i]<<endl;
		else puts("-1");
	}
	return false;
}
```

---

## 作者：Ivan422 (赞：0)

题目大意：给出长度 $n$ 的数组 $a$，给出 $m$ 个问题，求最少删除多少子段以达到剩余和为 $q$，要是不能满足输出 $-1$。其中 $q\in[1,m]$。

思路分析：考虑动态规划。

状态设计：$f_{i,j,k}$ 表示第 $i$ 个数的选择情况，当前和为 $j$。要是 $k$ 为 $1$ 则删，为 $0$ 则不删。记录的是当前子段编号。

初始化：求最小值，自然直接初始化为最大值。可以发现当第 $i=0$，为第 $0$ 个子段，子段编号就为 $0$。即 $f_{0,0,0}=0$。

状态转移不删第 $i$ 个数：如果选这个数，就必须记录和，即 $f_{i,j+a_i,0}$。当这个和是有意义的，即 $j+a_i\leq m$，就可以转移了。不管上一个选还是不选，都可以转移，即 $f_{i-1,j,0}$ 和 $f_{i-1,j,1}$。

状态转移删第 $i$ 个数：删了，子段编号就会变动。要是上一个也跟着删了，子段编号不变，直接转移，即 $f_{i-1,j,1}$，要是没删，编号变动，再转移，即 $f_{i-1,j,0}+1$。

答案：完成动态规划后，可以直接输出答案。对于 $q$，只需要在最后一个数的选与不选上判断即可。为 $f_{n,q,0}$ 和 $f_{n,q,1}$ 中的最小值。

```cpp
#include<bits/stdc++.h>
using namespace std;
//#define int long long
//#define double long double
//#define map unordered_map
//#pragma GCC optimize(2,3,"Ofast","inline")
const int N=3010,M=1010,P=998244353,MOD=998244353;
const double PI=3.1415926,EPS=0.00001;
int n,m,a[N],f[N][N][2];
signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>a[i];
    memset(f,0x7f,sizeof(f));
    f[0][0][0]=0;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=m;j++){
            if(j+a[i]<=m)f[i][j+a[i]][0]=min(f[i][j+a[i]][0],f[i-1][j][0]);
            f[i][j][1]=min(f[i][j][1],f[i-1][j][0]+1);
            if(j+a[i]<=m)f[i][j+a[i]][0]=min(f[i][j+a[i]][0],f[i-1][j][1]);
            f[i][j][1]=min(f[i][j][1],f[i-1][j][1]);
        }
    }
    for(int q=1;q<=m;q++){
        if(min(f[n][q][0],f[n][q][1])>n)cout<<"-1\n";
        else cout<<min(f[n][q][0],f[n][q][1])<<'\n';
    }
    return 0;
}
```

---

