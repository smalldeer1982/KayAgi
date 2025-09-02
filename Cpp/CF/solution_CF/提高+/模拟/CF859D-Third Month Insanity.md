# Third Month Insanity

## 题目描述

The annual college sports-ball tournament is approaching, which for trademark reasons we'll refer to as Third Month Insanity. There are a total of $ 2^{N} $ teams participating in the tournament, numbered from $ 1 $ to $ 2^{N} $ . The tournament lasts $ N $ rounds, with each round eliminating half the teams. The first round consists of $ 2^{N-1} $ games, numbered starting from $ 1 $ . In game $ i $ , team $ 2·i-1 $ will play against team $ 2·i $ . The loser is eliminated and the winner advances to the next round (there are no ties). Each subsequent round has half as many games as the previous round, and in game $ i $ the winner of the previous round's game $ 2·i-1 $ will play against the winner of the previous round's game $ 2·i $ .

Every year the office has a pool to see who can create the best bracket. A bracket is a set of winner predictions for every game. For games in the first round you may predict either team to win, but for games in later rounds the winner you predict must also be predicted as a winner in the previous round. Note that the bracket is fully constructed before any games are actually played. Correct predictions in the first round are worth $ 1 $ point, and correct predictions in each subsequent round are worth twice as many points as the previous, so correct predictions in the final game are worth $ 2^{N-1} $ points.

For every pair of teams in the league, you have estimated the probability of each team winning if they play against each other. Now you want to construct a bracket with the maximum possible expected score.

## 说明/提示

In the first example, you should predict teams $ 1 $ and $ 4 $ to win in round $ 1 $ , and team $ 1 $ to win in round $ 2 $ . Recall that the winner you predict in round $ 2 $ must also be predicted as a winner in round $ 1 $ .

## 样例 #1

### 输入

```
2
0 40 100 100
60 0 40 40
0 60 0 45
0 60 55 0
```

### 输出

```
1.75
```

## 样例 #2

### 输入

```
3
0 0 100 0 100 0 0 0
100 0 100 0 0 0 100 100
0 0 0 100 100 0 0 0
100 100 0 0 0 0 100 100
0 100 0 100 0 0 100 0
100 100 100 100 100 0 0 0
100 0 100 0 0 100 0 0
100 0 100 0 100 100 100 0
```

### 输出

```
12
```

## 样例 #3

### 输入

```
2
0 21 41 26
79 0 97 33
59 3 0 91
74 67 9 0
```

### 输出

```
3.141592
```

# 题解

## 作者：sky_of_war (赞：7)

emm这个题貌似没人做？

容易发现这个比赛的情形可以用一棵二叉树来表示。

设$g_{i,j}$表示二叉树节点$i$(代表了一个区间)上$j$成为最终胜利者的概率，$f_{i,j}$表示上述状态下的最优收益期望值。

对于$g$，转移即枚举$j$最后和哪些人对决并胜出，也就是对于节点$u$，当前处理的子树区间为$[l,r]$，有:

$$ {g_{u,i}} \leftarrow \sum_{i = l}^{\text{mid}} \sum _ {j = \text{mid}+1}^rg_{u \times 2 ,i} \times g_{u \times 2+1,j} \times p_{i,j} + \sum_{i=\text{mid}+1}^r \sum _{j=l}^{\text{mid}}g_{u \times 2+1,i} \times g_{u \times 2,j} \times p_{i,j} $$

对于$f$，转移即枚举$j$胜出的概率乘上收益并加上所有和$j$比赛的人中之前的最优期望收益值，也就是对于节点$u$，当前处理的子树区间为$[l,r]$，有：

$$ {f_{u,i}} \leftarrow \max \left (f_{u,i},\max_{i = l}^{\text{mid}} \max _ {j = \text{mid}+1}^r \left \{\frac 12 g_{u,i} \times (r - l + 1)  + f_{2u,i} + f_{2u+1,j} \right \}, \max_{i=\text{mid}+1}^r \max _{j=l}^{\text{mid}} \left \{\frac 12 g_{u,i} \times (r - l + 1)  + f_{2u+1,i} + f_{2u,j} \right\}\right) $$

时间复杂度$\mathcal O\left (n 4^n\right )$。
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e3 + 10;
double p[MAXN][MAXN], f[MAXN][MAXN], g[MAXN][MAXN], ans;
int k, n;
template <class T>
inline void _read(T &x)
{
	x = 0;
	char t = getchar();
	while(!isdigit(t)) t = getchar();
	while(isdigit(t))
	{
		x = x * 10 + t - '0';
		t = getchar();
	}
}
void dfs(int u, int l, int r)
{
	if(l == r)
	{
		f[u][l] = 0;
		g[u][l] = 1;
		return;
	}
	int mid = l + r >> 1;
	dfs(u << 1, l, mid);
	dfs(u << 1 | 1, mid + 1, r);
	for(int i = 1; i <= mid; ++i)
		for(int j = mid + 1; j <= n; ++j)
			g[u][i] += g[u << 1][i] * g[u << 1 | 1][j] * p[i][j];
	for(int i = mid + 1; i <= n; ++i)
		for(int j = 1; j <= mid; ++j)
			g[u][i] += g[u << 1 | 1][i] * g[u << 1][j] * p[i][j];
	for(int i = 1; i <= mid; ++i)
		for(int j = mid + 1; j <= n; ++j)
			f[u][i] = max(f[u][i], g[u][i] * (r - l + 1) / 2 + f[u << 1][i] + f[u << 1 | 1][j]);
	for (int i = mid + 1; i <= n; ++i)
		for (int j = 1; j <= mid; ++j)f[u][i] = max(f[u][i], g[u][i] * (r - l + 1) / 2 + f[u << 1 | 1][i] + f[u << 1][j]);
}
int main()
{
	_read(k);
	n = 1 << k;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			_read(p[i][j]), p[i][j] /= 100;
	dfs(1, 1, n);
	for(int i = 1; i <= n; ++i) ans = max(ans, f[1][i]);
	printf("%.10lf", ans);
	return 0;
}
```

---

## 作者：Mikazuki_Munechika (赞：1)

又水又老的题。

这里介绍一种新的写法。注意到两个队伍之间第 $ j $ 轮有可能对决，当且仅当这两个队伍编号的二进制表示下只有后 $ j $ 位可能不一样。

设 $ i $ 赢 $ j $ 的概率为 $ a_{i,j} $，那么首先可以求出来第 $ i $ 队伍在第 $ rd $ 轮获胜的概率，那么就有 $ prob_{i,rd} = prob_{i,rd - 1} \sum_j prob_{j, rd - 1}a_{i,j}  $，其中 $ j $ 满足与 $ i $ 在第 $ rd $ 轮不同组。

然后可以算前 $ rd $ 轮给 $ i $ 下注的期望得分，转移为：$dp_{i,rd} = dp_{i, rd - 1} + \max_j dp_{j, rd - 1} + 2^{rd - 1}prob_{i,rd}$

原 OJ 提交：[link](https://codeforces.com/contest/859/submission/229663093)

---

## 作者：spdarkle (赞：0)

远古老题，且让我说说我的做法。

首先，对于 $2^n$ 等敏感字眼，就可以联系到与 $2$ 的幂有关的算法，譬如倍增，分治等。

然后，在此题中，不难发现其第 $i$ 轮所对若干个区间：$[x·2^{i}+1,(x+1)·2^{i}]$。

这是完全二叉树的划分方式，这启发我们使用分治来解决这个问题。

设 $w_{i,j}$ 表示 $i$ 打败 $j$ 的概率。

先交给递归解决左右区间，现在考虑合并答案，枚举最终胜者。

期望问题，我们先求概率，设 $t_{i,s}$ 为节点 $i$ 在第 $s$ 轮取得胜利的概率。不难得到，其等价于在前 $s-1$ 轮获胜的概率，乘上打败另一半区间的人的概率之和。

也即：



$$t_{i,s}=t_{i,s-1}\sum_{j}w_{i,j}t_{j,s-1}$$



其中 $i,j$ 分属两半不同的区间。



求到了概率，现在考虑求解期望。

设 $f_{i,s}$ 为 $i$ 赢得了前 $s$ 轮的最大期望得分。首先要继承前 $s-1$ 轮的答案 $f_{i,s-1}$。

其次，我们要枚举另一半区间的点 $j$，让它为另一半区间前 $s-1$ 轮的胜者，贡献为 $f_{j,s-1}$。

最后，还有本轮胜利的得分乘概率的值 $(r-mid)t_{i,s}$。

所以，可以有：



$$f_{i,s}=f_{i-1,s}+(r-mid)t_{i,s}+\max_{j}{f_{j-1,s}}$$



最终的答案显然为 $\max f_{i,n}$。

时间复杂度 $O(n4^n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define db double
#define N 505050
db w[1<<8][1<<8],p[1<<8],q[1<<8],ans,t[1<<8][8],f[1<<8][8];
int n,v[1<<8];
void solve(int l,int r,int s){
	if(l==r){
		p[l]=1;t[l][s]=1;return ;
	}
	int mid=l+r>>1;
	solve(l,mid,s-1);solve(mid+1,r,s-1);
	for(int i=l;i<=r;i++)q[i]=0;
	for(int i=l;i<=mid;i++)for(int j=mid+1;j<=r;j++)q[i]+=w[i][j]*p[j]*p[i];
	for(int i=mid+1;i<=r;i++)for(int j=l;j<=mid;j++)q[i]+=w[i][j]*p[j]*p[i];
	for(int i=l;i<=r;i++)p[i]=t[i][s]=q[i];
	for(int i=l;i<=mid;i++){
		for(int j=mid+1;j<=r;j++){
			f[i][s]=max(f[j][s-1],f[i][s]);
		}	
		f[i][s]+=f[i][s-1]+(r-mid)*t[i][s];
	}
	for(int i=mid+1;i<=r;i++){
		for(int j=l;j<=mid;j++){
			f[i][s]=max(f[j][s-1],f[i][s]);
		}	
		f[i][s]+=f[i][s-1]+(r-mid)*t[i][s];
	}
}
int main(){
	cin>>n;
	for(int i=1;i<=(1<<n);i++)for(int j=1;j<=(1<<n);j++)cin>>w[i][j],w[i][j]/=100.0;
	solve(1,1<<n,n);for(int i=1;i<=(1<<n);i++)ans=max(ans,f[i][n]);
	printf("%.15f",ans);
}
```



---

