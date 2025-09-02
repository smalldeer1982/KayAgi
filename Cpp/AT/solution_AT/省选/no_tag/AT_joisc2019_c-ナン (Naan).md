# ナン (Naan)

## 题目描述

**题目译自 [JOISC 2019](https://www.ioi-jp.org/camp/2019/2019-sp-tasks/index.html) Day1 T3「[ナン](https://www.ioi-jp.org/camp/2019/2019-sp-tasks/day1/naan.pdf) / [Naan](https://www.ioi-jp.org/camp/2019/2019-sp-tasks/day1/naan-en.pdf)」**

JOI 咖喱店以提供很长（？）的馕而闻名。它提供的馕有 $L$ 种口味，编号从 $1$ 到 $L$。「JOI 特色馕」是店内最受欢迎的一道菜。馕的总长度为 $L$ 厘米。我们定义「点 $X$」为馕上距离馕左端 $X$ 厘米处的点。对于 $1 \le j \le L$，点 $j-1$ 和点 $j$ 间的一段馕是第 $j$ 种口味的。

有 $N$ 个人来到了 JOI 咖喱店，他们每个人的偏好都不同，具体的说，第 $i$ 个人每吃一厘米的风味 $j$ 的馕，就会获得 $V_{i,j}$ 的快乐度。

他们只买了一个 JOI 特色馕，他们将用下面的方式分享馕：

1. 选择 $N-1$ 个分数 $X_1, \ldots, X_{N-1}$，满足 $0 < X_1 < X_2 < \ldots < X_{N-1} < L$。
2. 选择 $N$ 的一个排列 $P_1, \ldots P_N$。
3. 对于每一个 $k (1 \le k \le N-1)$，在点 $X_k$ 的位置切一刀，然后馕将被切成 $N$ 个部分。
4. 第 $k (1 \le k \le N)$ 个部分的左端点为 $X_{k-1}$，右端点为 $X_{k}$，这里我们认为 $X_0=0, X_N=L$。
5. 第 $P_i$ 个人将吃掉第 $i$ 个部分。

现在他们想公平的分配馕，他们认为一种分配方法是公平的，当且仅当每个人获得的快乐度都不小于他们独吞整个馕所获得的快乐度的 $\frac{1}{N}$。

现在给你 $N$ 个人的信息，你需要判断是否存在一种公平的分配方式，如果存在，输出一组分配方案。

## 说明/提示

### 样例解释 1

在这组样例中，第一个人如果吃掉整个馕，会得到 $2+7+1+8+2=20​$ 的快乐度，第二个人如果吃掉整个馕，会获得 $3+1+4+1+5=14​$ 的快乐度。因此，如果第一个人获得不小于 $\frac{20}{2}=10​$ 的快乐度，且第二个人获得不小于 $\frac{14}{2}=7​$ 的快乐度，就是一组合法的解。

如果在点 $\frac{14}{5}$ 的位置切一刀，第一个人会获得 $1 \times \frac{1}{5} + 8 + 2 = \frac{51}{5}$ 的快乐度，第二个人会获得 $3+1+4 \times \frac{4}{5} = \frac{36}{5}$ 的快乐度。因此这是一组合法的解。

### 样例解释 2

在这组样例中，馕只有一种风味。只要把馕七等分，就是合法的方案，与 $P_1, ..., P_N$ 无关。

### 样例解释 3

注意 $A_i, B_i (1 \le i \le N)$ 不必互质。

### 数据范围

|Subtask #|分值| 数据规模 |
|-|-|-|
|1|5| $N = 2$ |
|2|24|$N \le 6,V_{i,j} \le 10 (1 \le i \le N,1 \le j \le L)$|
|3|71| 无特殊限制 |

对于所有输入数据，有 $1 \le N \le 2000,1 \le L \le 2000, 1 \le V_{i,j} \le 10^5 (1 \le i \le N,1 \le j \le L)$。

翻译来自于 [LibreOJ](https://loj.ac/p/3032)。

## 样例 #1

### 输入

```
2 5
2 7 1 8 2
3 1 4 1 5```

### 输出

```
14 5
2 1```

## 样例 #2

### 输入

```
7 1
1
2
3
4
5
6
7```

### 输出

```
1 7
2 7
3 7
4 7
5 7
6 7
3 1 4 2 7 6 5```

## 样例 #3

### 输入

```
5 3
2 3 1
1 1 1
2 2 1
1 2 2
1 2 1```

### 输出

```
15 28
35 28
50 28
70 28
3 1 5 2 4```

# 题解

## 作者：EuphoricStar (赞：4)

考虑贪心。发现第 $i$ 个人获得的愉悦度越接近 $\frac{\sum\limits_{j=1}^L v_{i,j}}{n}$ 越好，因为给其他人的空间就越多。因此先预处理出每个人将将整个馕划分为 $n$ 段愉悦值相同部分的端点 $d_{i,1},d_{i,2},...,d_{i,n-1}$。

构造第 $j$ 段时考虑每次取最小的 $d_{i,j}$ 作为断点并把这一段分给第 $i$ 个人。因为上一个断点 $\le d_{i,j-1}$（每次取最小），所以很神奇地满足了条件。

[code](https://loj.ac/s/1720115)

---

## 作者：DaiRuiChen007 (赞：1)

# JOISC2019C 题解

[Problem Link](https://www.luogu.com.cn/problem/AT_joisc2019_c)

**题目大意**

> 有一个 $m$ 厘米的线段，第 $[i-1,i)$ 厘米的部分被染上了颜色 $i$。
>
> 另有 $n$ 个人，每个人对每个颜色有一个喜好程度 $v_{i,j}$，现在要将线段分割成连续的 $n$ 段，每段给一个人。
>
> 每个人得到一段线段的开心值是线段上每个颜色对应的喜好程度乘上长度。最终的方案要满足第 $i$ 个人的开心值大于等于 $\dfrac 1n\sum_j v_{i,j}$。
>
> 给出方案或报告无解，输出分数，要求分母 $\le 10^9$。
>
> $n,m\le 2000$，$a_i\le 10^5$。
>

**思路分析**

对于每个人 $i$，处理出 $P_{i,1}\sim P_{i,n}$，$P_{i,k}$ 表示取到 $\dfrac kn\sum_j v_{i,j} $ 的位置。

然后第一段就取 $\min {P_{i,1}}$ 做右端点，然后分给对应的人 $x$，第二段就在剩下的人中取 $\min P_{i,2}$ 做右端点，然后分给对应的人 $y$。

由于 $P_{x,1}=\min P_{i,1}$，因此 $P_{y,1}\ge P_{x,1}$，因此线段 $[P_{y,1},P_{y,2}]\subseteq[P_{x,1},P_{y,2}]$，第二段权值一定也合法，后面同理。

时间复杂度 $\mathcal O(n(n+m))$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
#define LL __int128
using namespace std;
const int MAXN=2005;
struct frac {
	ll x,y;
	inline bool friend operator <(const frac &u,const frac &v) {
		return (LL)u.x*v.y<(LL)v.x*u.y;
	}
}	pos[MAXN][MAXN];
int n,m,bel[MAXN];
bool vis[MAXN];
ll a[MAXN][MAXN],tar[MAXN],tmp[MAXN];
signed main() {
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i) {
		for(int j=1;j<=m;++j) {
			scanf("%lld",&a[i][j]);
			tar[i]+=a[i][j];
		}
	}
	for(int i=1;i<=n;++i) {
		for(int j=1;j<=m;++j) tmp[j]=a[i][j]*n;
		for(int j=1,p=1;j<n;++j) {
			ll rem=tar[i];
			while(rem>tmp[p]) rem-=tmp[p++];
			tmp[p]-=rem;
			pos[i][j].y=n*a[i][p];
			pos[i][j].x=p*pos[i][j].y-tmp[p];
		}
	}
	for(int i=1;i<n;++i) {
		int p=0;
		for(int j=1;j<=n;++j) {
			if(!vis[j]&&(!p||pos[j][i]<pos[p][i])) p=j;
		}
		bel[i]=p,vis[p]=true;
		printf("%lld %lld\n",pos[p][i].x,pos[p][i].y);
	}
	for(int i=1;i<=n;++i) if(!vis[i]) bel[n]=i;
	for(int i=1;i<=n;++i) printf("%d ",bel[i]); puts("");
	return 0;
}
```



---

