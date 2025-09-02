# Tower of Hanoi

## 题目描述

汉诺塔是一种非常著名的游戏。汉诺塔包括三根柱子和一些圆盘。这些圆盘一开始按照从高到低，从小到大的顺序排列，形成圆锥状的“塔”。解题者的目标是将所有的圆盘按照一开始的顺序放到另一根柱子上。但是，移动的时候，你要遵守以下三条规则：

- 每次只能移动一个圆盘。
- 每次移动时只能拿走任意杆上最顶端的圆盘，并将它移动到另一根杆子上。
- 两个相邻的圆盘不能出现上面的圆盘比下面的圆盘要大的情况。

在只有三个圆盘的情况下，这个问题可以用 $7$ 步简单地解决。一个通用的计算方法是，如果有 $n$ 个圆盘，那么你可以用 $2^n - 1 $步来解决它。

现在，我们有了新的问题。小 Y 发明了一种汉诺塔的衍生游戏。玩汉诺塔时，你需要以最少的步数移动完成所有圆盘，但在小 Y 的游戏中，每一次移动都需要一定的费用，你要根据汉诺塔的规则来解决小 Y 的游戏，但是你需要花费最少的费用来将所有圆盘按照规定移动到第三个杆上。在开始时，所有的 $n$ 个圆盘都在第一根杆上。将圆盘从杆 $i$ 移动到杆 $j$ 需要花费 $t[i][j]$ 个金钱单位。保证 $1 \le i, j \le 3$ 。我们会给出费用数组 $t$ 以及圆盘数量 $n$，你要计算对于这次的数据，最少需要多少费用才能完成小 Y 的游戏。

## 样例 #1

### 输入

```
0 1 1
1 0 1
1 1 0
3
```

### 输出

```
7
```

## 样例 #2

### 输入

```
0 2 2
1 0 100
1 2 0
3
```

### 输出

```
19
```

## 样例 #3

### 输入

```
0 2 1
1 0 100
1 2 0
5
```

### 输出

```
87
```

# 题解

## 作者：yuzhechuan (赞：6)

[我的博客园](https://www.cnblogs.com/think-twice/p/11237621.html)

[我的CSDN](https://blog.csdn.net/qq_45404210/article/details/97124002)

---
[CF392B](https://www.luogu.org/problemnew/show/CF392B)

---

记搜好题

---

### 预处理

题目给出了将一个盘从x移到y的代价（代码中为a[][]），当我们知道这并不是最优的

就像最短路floyd一样松弛操作预处理得到两柱之间最优值b[][]
```cpp
for(int i=1;i<=3;i++)
	for(int j=1;j<=3;j++)
		scanf("%lld",&a[i][j]),b[i][j]=a[i][j];
for(int i=1;i<=3;i++)
	for(int j=1;j<=3;j++) if(i!=j)
		for(int k=1;k<=3;k++) if(k!=i&&k!=j)
			b[i][j]=min(b[i][j],b[i][k]+b[k][j]);
```
---

### 记搜主体
冷静分析，每次搬n个盘子都有两种搬法：

1. 方法一
![](https://imgconvert.csdnimg.cn/aHR0cHM6Ly93d3cuY25ibG9ncy5jb20vaW1hZ2VzL2NuYmxvZ3NfY29tL3RoaW5rLXR3aWNlLzE1MDU0MTcvb19oYW5vaTEucG5n)
2. 方法二
![](https://imgconvert.csdnimg.cn/aHR0cHM6Ly93d3cuY25ibG9ncy5jb20vaW1hZ2VzL2NuYmxvZ3NfY29tL3RoaW5rLXR3aWNlLzE1MDU0MTcvb19oYW5vaS5wbmc)

我们知道每次最大盘的代价直接就是a[][]，而其余n-1个是可以由递归记搜得到的

当递归到只剩一个盘时，只需要用预处理出的最优解b[][]即可
```cpp
int dfs(int l,int r,int n){
	if(f[l][r][n]) return f[l][r][n]; //已经走过，直接返回
	if(n==1) return b[l][r]; //递归边界，只剩一个盘
	int x=6-l-r; //表示中介盘，因为三个盘编号之和为6
	int an1=dfs(l,x,n-1)+dfs(x,r,n-1)+a[l][r]; //方法一
	int an2=(dfs(l,r,n-1)<<1)+dfs(r,l,n-1)+a[l][x]+a[x][r]; //方法二
	return f[l][r][n]=min(an1,an2); //取个最优值
}
```
dfs(l,r,n)表示将n个盘从l移到r的方案数

所以答案就是`dfs(1,3,n)`

---

**注意这题还会爆int**

---

## 作者：封禁用户 (赞：2)

考虑移动的过程。假设移动 $i$，那么移出和移入的两个塔都不能有 $1,2,...,i-1$ 的所有数，所以 $1,2,...,i-1$ 必然在剩余的那个塔上。

把 $1,2,...,i-1$ 视为一个整体，有：

$$
\begin{aligned}
1,2,...,i-1 \to z\\
i \to y\\
1,2,...,i-1 \to y
\end{aligned}
$$
和

$$
\begin{aligned}
1,2,...,i-1 \to y\\
i \to z\\
1,2,...,i-1 \to x\\
i \to y\\
1,2,...,i-1 \to y
\end{aligned}
$$
两种转移，复杂度 $\mathcal O(n)$。

---

## 作者：Lynkcat (赞：2)

考虑 $dp$ ，我们可以用 $f_{i,j,k}$ 表示把前 $k$ 个盘子从 $i$ 号柱移动到 $j$ 号柱上的最少花费。

因为答案是最小花费而不是最小步数，所以我们有两种决策，直接移与分两次移。

于是我们可以得到这样一个方程：

$f_{i,j,k}=\min(f_{i,6-i-j,k-1}+a_{i,j}+f_{6-i-j,j,k-1},f_{i,j,k-1} \times 2+a_{i,6-i-j}+f_{j,i,k-1}+a_{6-i-j,j})$

另外的，我们可以用搜索确定 $dp$ 的更新顺序。

代码：
```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T[4][4],n,f[100][4][4];
int dfs(int k,int s,int t)
{
	if (s==t) return 0;	
	if (f[k][s][t]) return f[k][s][t];
	if (k==n)
	  return min(T[s][t],T[s][6-s-t]+T[6-s-t][t]);
	return f[k][s][t]=min(dfs(k+1,s,6-s-t)+T[s][t]+dfs(k+1,6-s-t,t),(dfs(k+1,s,t)*2)+dfs(k+1,t,s)+T[s][6-s-t]+T[6-s-t][t]);
}
signed main()
{
	for (int i=1;i<=3;i++)
	  for (int j=1;j<=3;j++) 
	    cin>>T[i][j];
	cin>>n;
	cout<<dfs(1,1,3);
}
```

---

## 作者：Xiao_Xiao_Yu (赞：1)

# CF392B Tower of Hanoi 题解

## 题意

给定一个带有 $n$ 个圆盘的汉诺塔，移动规则与普通的汉诺塔相同，但是增加了【将圆盘从第 $i$ 根柱子移动到第 $j$ 根柱子需要花费 $t_{i,j}$ 的代价】的条件，求完成全部圆盘移动的最小代价。

如果你不知道普通的汉诺塔的移动规则，请返回查看题目描述或前往 [P1760](https://www.luogu.com.cn/problem/P1760)。

## 分析

我们从普通的汉诺塔问题开始分析再迁移到本题，在下文中我们对圆盘从上到下（从小到大）按 $1$ 到 $n$ 进行编号。

普通的汉诺塔求最小移动步数问题可以通过**递归**与**记忆化搜索**解决（虽然实际上可以推导出最小移动步数为 $2^n-1$ 步并直接计算，其中 $n$ 为圆盘个数）。由于游戏规则的限制，容易确定以下的策略：

> 在第 $i$ 个圆盘上面叠满了圆盘时，若想将它和其上所有圆盘从第 $j$ 根柱子移动到第 $k$ 根柱子上且移动次数最少，先将其上的所有圆盘移动到第 $(6-j-k)$ 根柱子（即除了 $j,k$ 之外的第三根），再将该圆盘移动至第 $k$ 根柱子，最后将先前移动的圆盘移动到第 $k$ 根柱子上。

设 $f_{i,j,k}$ 表示上述问题的答案，则有如下的递归式子（为方便，记 $w=6-j-k$）：

$$f_{i,j,k}=\begin{cases}
1 & i = 1\\
f_{i-1,j,w}+1+f_{i-1,w,k} & i > 1
\end{cases}$$

迁移到本题，我们只需要将上述递归式中的 $1$ 替换为对应的 $t_{j,k}$，并对一些其他情况进行讨论即可。

由于可能出现这种情况：将圆盘直接从 $j$ 移到 $k$ 需要花费极大的代价，而其他的移动方式代价却很小。因此我们还需要考虑另一种移动方式——通过第三根柱子进行中转，即先移动到第三根柱子再移动到目标柱子。这种情况下的移动步骤略微复杂，具体如下：

1. 将上方的圆盘移动到 $k$；
2. 将自己移动到 $(6-j-k)$；
3. 将上方的圆盘移回 $j$；
4. 将自己移动到 $k$；
5. 将上方的圆盘移动到 $k$。

于是本题的递归式如下：

$$g_{i,j,k}=\begin{cases}
\min\{{t_{j,k},t_{j,w}+t_{w,k}\}} & i = 1\\
\min\begin{cases}
g_{i-1,j,w}+t_{j,k}+g_{i-1,w,k}\\
g_{i-1,j,k}+t_{j,w}+g_{i-1,k,j}+t_{w,j}+g_{i-1,j,k}
\end{cases}& i > 1
\end{cases}$$

在递归过程中使用数组记录已经计算过的结果，避免大量重复递归计算即可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int t[5][5], n;
ll f[45][5][5];

ll move(int i, int j, int k) {
	if (f[i][j][k]) return f[i][j][k];
	int w = 6 - j - k;
	if (i == 1) return f[i][j][k] = min(t[j][k], t[j][w] + t[w][k]);
	ll ans1 = move(i - 1, j, w) + t[j][k] + move(i - 1, w, k);
	ll ans2 = move(i - 1, j, k) + t[j][w] + move(i - 1, k, j) + t[w][k] + move(i - 1, j, k);
	return f[i][j][k] = min(ans1, ans2);
}

int main() {
	for (int i = 1; i <= 3; ++i)
		for (int j = 1; j <= 3; ++j) scanf("%d", &t[i][j]);
	scanf("%d", &n);
	printf("%lld\n", move(n, 1, 3));
	return 0;
}
```

---

## 作者：李尚儒 (赞：1)

解题思路：$dp[l][r][n]$，表示的是从l移动n个碟子到r的最小花费，然后总共有两种移动方式：

$ans1 = solve(l, x, n-1) + solve(x, r, n-1) + val[l][r];$

$ans2 = solve(l, r, n-1)*2 + solve(r,l, n-1) + val[l][x] + val[x][r];$

然后
$ans=min(ans1,ans2)$。

需要注意的是最小的碟子移动时，比如最小的碟子要从$1$移动$3$需要$100$，移动到$2$再移动到$3$的花费是$10，10$.

~~latex大法好~~
```cpp
#include <stdio.h>
#include <string.h>
#include <iostream>
#define min(a,b) (a)<(b)?(a):(b)

using namespace std;
typedef long long ll;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int N = 5;

bool v[N][N][50];
ll val[N][N], best[N][N], dp[N][N][50];

void init () {
    memset(v, 0, sizeof(v));
    for (int i = 1; i <= 3; i++)
        for (int j = 1; j <= 3; j++) {
            cin >> val[i][j];
            best[i][j] = val[i][j];
        }

    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) {
            if (i == j) continue;
            for (int k = 1; k <= 3; k++) if (k != i && k != j) {
                best[i][j] = min(best[i][j], best[i][k] + best[k][j]);
            }
        }
    }
}

ll solve(int l, int r, int n) {
    if (v[l][r][n]) return dp[l][r][n];

    v[l][r][n] = 1;
    ll& ans = dp[l][r][n];
    int x = 6 - l - r;

    if (n == 1) return ans = best[l][r];
    ans = solve(l, x, n-1) + solve(x, r, n-1) + val[l][r];
    ll k = solve(l, r, n-1) * 2 + solve(r, l, n-1) + val[l][x]+ val[x][r];
    ans = min(ans, k);
    return ans;
}

int main () {
    init();
    int n;
    scanf("%d", &n);
    cout << solve(1, 3, n) << endl;
    return 0;
}

---

## 作者：XL4453 (赞：0)

### 解题思路：

汉诺塔问题的一个拓展问题，将原本全都为 $1$ 的移动权值改成可变的权值，但是思想还是一样的。

原本的汉诺塔问题是通过不断递归缩小问题来求解的。那么同样，考虑将每一个盘子的状态分解成移动上面的若干个盘子和最下面的一个盘子，然后通过在这一步解决上面的若干盘子和最下面的盘子的移动，并将上面若干个盘子的移动通过递归函数求解。

所以下一步，也是核心的一步就是讨论当前的如何移动。由于不同柱子移动的代价不同，所以通过另一个柱子中转一下并不一定不优，这一点和最短路很相似。那么这里就有了两种不同的转移方式，为了方便记述，记上面的若干柱子为 $A$，最下面的一个柱子为 $B$，现在要从 $1$ 号柱子移动到 $3$ 号。

1. $A$ 从 $1$ 移动到 $2$，$B$ 从 $1$ 移动到 $3$，$A$ 从 $2$ 移动到 $3$。

2. $A$ 从 $1$ 移动到 $3$，$B$ 从 $1$ 移动到 $2$，$A$ 从 $3$ 移动到 $1$，$B$ 从 $2$ 移动到 $3$，$A$ 从 $1$ 移动到 $3$。

其中第二种方案虽然看起来用的步骤多，但是避免了上面的大量盘子通过 $2$ 的移动，所以当通过 $2$ 移动的代价较大时，这一种移动方式可能反而是更优的。

注意这里的 $A$ 可以为空，这样想的话，也就避免了其他题解中的对于单个盘子移动的讨论。

具体实现的时候可以采用记忆化搜索的方式。

---
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
#define int long long
int n,dis[5][5],f[5][5][50];
int dfs(int x,int y,int num){
	if(f[x][y][num])return f[x][y][num];
	int mid=6-x-y;
	if(num==0)return 0;
	return f[x][y][num]=min(dfs(x,mid,num-1)+dfs(mid,y,num-1)+dis[x][y],
	dfs(x,y,num-1)+dfs(y,x,num-1)+dfs(x,y,num-1)+dis[x][mid]+dis[mid][y]);
}
signed main(){
	for(int i=1;i<=3;i++)
	for(int j=1;j<=3;j++)
	scanf("%I64d",&dis[i][j]);
	scanf("%I64d",&n);
	printf("%I64d",dfs(1,3,n));
	return 0;
}
```


---

## 作者：SUNCHAOYI (赞：0)

不妨设 $dp[i][j][k]$ 表示 $i$ 个圆盘从第 $j$ 杆移动到第 $k$ 杆的最小花费。现在要求 $n$ 个在第 $1$ 杆的圆盘移动到第 $3$ 杆上，因此最终的答案就是 $dp[n][1][3]$。

根据一般汉诺塔的移动方法，想要移动 $i$ 个圆盘，就需要先解决顶上 $i - 1$ 个圆盘的移动问题。又因为汉诺塔只有 $3$ 根柱子，所以我们也可以根据这个思路取设计转移方程。假设现在有 $n$ 个圆盘在第 $1$ 杆上，需要移动到 第 $3$ 杆上，因不同的路径的花费不同，所以我们可以先将顶上 $i - 1$ 个盘子移动到第 $2$ 根或第 $3$ 根杆上，计算哪一个花费最小，如图所示：   

![图](https://cdn.luogu.com.cn/upload/image_hosting/q1cyhwh0.png)
现在设 $dis[i][j]$ 表示将圆盘从杆 $i$ 移动到杆 $j$ 需要花费的金钱数。
根据手绘的~~垃圾~~图：
- 第一种移动方式的花费为 $n - 1$ 个盘子从 $1$ 移到 $2$ 的最小花费加上将底部的圆盘从 $1$ 移动到 $2$ 所需的花费，即 $dp[i - 1][1][2] + dis[1][2]$。
- 第一种移动方式分成三部分：  
① $i - 1$ 个盘子从 $1$ 移到 $3$，底部的圆盘从 $1$ 移动到 $2$；  
② $i - 1$ 个盘子从 $3$ 移到 $1$，底部的圆盘从 $2$ 移动到 $3$；  
③ $i - 1$ 个盘子从 $1$ 移到 $3$。   
把所有的花费合并起来就是：$dp[i - 1][1][3] + dis[1][2] + dp[i - 1][3][1] + dis[2][3] + dp[i - 1][1][3]$。

最后，我们把这两种不同的花费取最小值就是 $dp[i][j][k]$ 的答案。总结一下，转移方程就是：$dp[i][j][k] = \min (dp[i - 1][j][l] + dp[i - 1][l][k] + dis[j][k],dp[i - 1][j][k] + dis[j][l] + dp[i - 1][k][j] + dis[l][k] + dp[i - 1][j][k])$($j ≠k$)。($l$ 想必就是中间的一个媒介盘了)

----

有了转移方程，代码也就好写了，时间复杂度为 $O(9 \times n)$。

```
#include <iostream>
#include <cstdio>
#define ll long long
#define l 6-j-k
using namespace std;
const int MAX = 45;
ll dis[4][4],dp[MAX][4][4];
int main ()
{
	//dp[i][j][k] i 个盘子从 j 移动到 k 的最小成本
	int n;
	for (int i = 1;i <= 3;++i)
		for (int j = 1;j <= 3;++j) scanf ("%lld",&dis[i][j]);
	scanf ("%d",&n);
	for (int i = 1;i <= n;++i)
	{
		for (int j = 1;j <= 3;++j)
		{
			for (int k = 1;k <= 3;++k)
			{
				if (j == k) continue;
				ll da = dp[i - 1][j][l] + dp[i - 1][l][k] + dis[j][k];//移最顶上的2个到中间 
				ll db = dp[i - 1][j][k] + dis[j][l] + dp[i - 1][k][j] + dis[l][k] + dp[i - 1][j][k];//移最顶上的2个到第3根 
				dp[i][j][k] = min (da,db); 
			}
		}
	}
	printf ("%lld\n",dp[n][1][3]);
	return 0;
}
```

---

