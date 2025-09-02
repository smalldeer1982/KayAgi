# 『STA - R2』Locked

## 题目背景

GOD_hj 有一把数字密码锁，但是他陷于 whk，没时间来开锁。

## 题目描述

这把锁从左到右有 $n$ 个数，组成了一个序列 $\{a\}$。

由于 GOD_hj 的记性不好，所以只要将锁设置为输入任意单峰序列即可打开。具体为：
$$ a_1 \le \cdots \le a_i \ge a_{i+1} \ge \cdots \ge a_n\quad (1 \le i \le n) $$

GOD_hj 的锁是拨动式的，即拨一下就能换成临近的一个数（$0$ 和 $9$ 可以互换）。

求最少拨几下可以开锁。

## 说明/提示

**【样例解释】**

样例二：把第四个 $5$ 变为 $6$ 或把第三个 $6$ 变为 $5$。

**【数据范围】**

**本题采用捆绑测试。**

$$
\newcommand{\arraystretch}{1.5}
\begin{array}{c|c|c|c}\hline\hline
\textbf{Subtask} & \bm n\le &\textbf{分值}&\textbf{特殊性质} \\\hline
\textsf{1} & 5 & 5 & \textbf{无} \\\hline
\textsf{2} & 10^3 & 25 & \textbf{无} \\\hline
\textsf{3}  & 5\times 10^5 & 20 & \textbf{无} \\\hline
\textsf{4} & 5\times 10^6 & 10 & a_i\in\{0,1\} \\\hline
\textsf{5} & 5\times 10^6 & 40 & \textbf{无} \\\hline\hline
\end{array}
$$

对于全部数据，$1\le n\le 5\times 10^6$，$0\le a_i<10$。

**Upd on 2023/06/12**：新加 5 组 Hack 数据，放入 Subtask 6，不计分。

## 样例 #1

### 输入

```
3
1 2 3```

### 输出

```
0```

## 样例 #2

### 输入

```
7
1 2 6 5 6 7 2```

### 输出

```
1```

# 题解

## 作者：未来姚班zyl (赞：6)

## 题目大意

有一串由数字 $0\sim 9$ 组成的序列 ${a}$ ，每次可以花费 $1$ 的代价将一个数变为其相邻的数 （$0$ 和 $9$ 也相邻）。求将其变为某个位置为峰值的左不减右不增序列的最小代价。

## 题目分析

乍一看可能感觉这题是贪心，但仔细一想会发现操作之间是相牵连的，故放弃贪心，更换思考角度。

可以发现，单调不减和单调不增是好解决的，可以设计状态 $dp_{i,j}$ 表示前 $i$ 个数中，将最后一位变为 $j$，且前 $i$ 个数单调不减的最小代价，可以很容易得到转移方程 $dp_{i,j}=\min\limits_{0\le k\le j}{dp_{i-1,k}}+dis(a_i,j)$，其中第一项可以前缀最小值来维护，$dis(x,y)$ 表示将 $x$ 变为 $y$ 需要的代价，值为 $\min (|x-y|,10-|x-y|)$。那么反过来的处理方法也是一样了，设计状态 $f_{i,j}$ 表示第 $i\sim n$ 单调不增，第 $i$ 个数设置为 $j$ 的最小代价，，最后的答案就是 $\min\limits_{1\le i\le n,0\le j\le 9}{dp_{i,j}+f_{i,j}}$。总复杂度 $O(10 n)$，可以通过此题。

#### update：这里要注意，计算答案时由于 $dp_{i,j}$ 和 $f_{i,j}$ 都计算了一次 $dis_{a_i,j}$，所以还得减去一次 $dis_{a_i,j}$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define L x<<1
#define R x<<1|1
#define mid (l+r>>1)
#define lc L,l,mid
#define rc R,mid+1,r
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
using namespace std;
const int N=5e6+5;
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57) s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(ll x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
int n,a[N],f[N][10],g[N][10],ff[10],ans=2147000000;
inline int dis(int x,int y){
	return min(abs(x-y),10-abs(x-y));
}
int main(){
	n=read();
	rep(i,1,n)a[i]=read();
	rep(i,0,9)f[1][i]=dis(a[1],i),g[n][i]=dis(a[n],i);
	ff[0]=f[1][0];
	rep(i,1,9)ff[i]=min(ff[i-1],f[1][i]);
	rep(i,2,n){
		f[i][0]=ff[0]+dis(a[i],0);
		ff[0]=f[i][0];
		rep(j,1,9)f[i][j]=ff[j]+dis(a[i],j),ff[j]=min(ff[j-1],f[i][j]);
	}
	ff[0]=g[n][0];
	rep(i,1,9)ff[i]=min(ff[i-1],g[n][i]);
	for(int i=n-1;i>=1;i--){
		g[i][0]=ff[0]+dis(a[i],0);
		ff[0]=g[i][0];
		rep(j,1,9)g[i][j]=ff[j]+dis(a[i],j),ff[j]=min(ff[j-1],g[i][j]);
	}
	rep(i,1,n)rep(j,0,9){
		ans=min(ans,f[i][j]+g[i][j]-dis(a[i],j));
	}
	cout <<ans;
	return 0;
}
```


---

## 作者：Pengzt (赞：4)

[P9408](https://www.luogu.com.cn/problem/P9408)

建议降黄。

这里只讲不降序列的做法，不升序列同理。

容易想到枚举最大值，令 $f_{i, j}$ 表示前 $i$ 个数变为不降序列且第 $i$ 个数为 $j$ 的最小操作次数。

先考虑暴力转移：$f_{i,j} = f_{i - 1, k} + \text{chg}(a_i, j)$，其中 $\text{chg}(i, j)$ 表示 $i$ 到 $j$ 的最少操作次数。这样是 $\mathcal{O}(nV^2)$ 的，但能过，应该是因为有一个 $\frac{1}{2}$ 的常数。

考虑优化。

发现 $\text{chg}(a_i, j)$ 是不变的，处理出 $lst_j$ 表示第 $i - 1$ 个小于等于 $j$ 时，操作的最少次数，这样就可以 $\mathcal{O}(1)$ 转移了。

应该要加读入优化，但 ios 也能过。

[评测记录](https://www.luogu.com.cn/record/112579570)

感觉部分分没什么用？

---

## 作者：lailai0916 (赞：3)

## 原题链接

- [洛谷 P9408 『STA - R2』Locked](https://www.luogu.com.cn/problem/P9408)

## 解题思路

1. 设 $f(x,y)$ 为将 $x$ 变成 $y$ 的拨动次数，不难写出 $f(x,y)$ 的通式：

$$
f(x,y)=\min(\lvert(x-y+10)\bmod 10\rvert,\lvert(y-x+10)\bmod 10\rvert)
$$

2. 考虑使用 DP 解决。设 $f1_{i,j}$ 表示前 $i$ 个位置单调不减且以 $j$ 结尾的序列最小拨动次数，显然前一项不能比后一项大，所以后一项只能由小于等于前一项的结果中取最小值，得出 DP 递推方程：

$$
f1_{i,j}=\min_{k=1}^j f1_{i-1,k}+f(a_i,j)
$$

3. 同理，设 $f2_{i,j}$ 表示后 $i$ 个位置单调不减且以 $j$ 开头的序列最小拨动次数，得出 DP 递推方程：

$$
f2_{i,j}=\min_{k=1}^j f1_{i+1,k}+f(a_i,j)
$$

4. 枚举所有的 $i,j$，表示以 $i$ 为峰顶，以 $j$ 为峰值的拨动次数，峰顶会被重复计算 $1$ 次，所以要减去 $f(a_i,j)$ 再取最小值：

$$
ans=\min_{i=1}^n \min_{j=0}^9 f1_{i,j}+f2_{i,j}-f(a_i,j)
$$

## 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int inf=0x3f3f3f3f;
const int N=5000005;
int a[N],f1[N][10],f2[N][10];
int f(int x,int y)
{
	return min(abs((x-y+10)%10),abs((y-x+10)%10));
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<10;j++)
		{
			f1[i][j]=inf;
			f2[i][j]=inf;
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<10;j++)
		{
			for(int k=0;k<=j;k++)
			{
				f1[i][j]=min(f1[i][j],f1[i-1][k]+min(abs((a[i]-j+10)%10),abs((j-a[i]+10)%10)));
			}
		}
	}
	for(int i=n;i>=1;i--)
	{
		for(int j=0;j<10;j++)
		{
			for(int k=0;k<=j;k++)
			{
				f2[i][j]=min(f2[i][j],f2[i+1][k]+min(abs((a[i]-j+10)%10),abs((j-a[i]+10)%10)));
			}
		}
	}
	int ans=inf;
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<10;j++)
		{
			ans=min(ans,f1[i][j]+f2[i][j]-min(abs((a[i]-j+10)%10),abs((j-a[i]+10)%10)));
		}
	}
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：jijidawang (赞：3)

考虑枚举转折点 $k$ 使得 $a_1 \le \cdots \le a_k \ge a_{k+1} \ge \cdots > a_n$ .

然后答案就是前面的最小答案加后面的最小答案 .

于是只需要处理前缀修改成不下降序列的最小操作次数和后缀修改成不上升序列的最小操作次数，这两个是等价的，以下就以前缀修改成不下降序列为例 .

考虑 DP，令 $dp_{i,j}$ 表示将 $a_{1\dots i}$ 改为不下降且最后 $a_i=j$ 需要的最小步数，则考虑枚举 $a_{i-1}$ 可得转移为
$$dp_{i,j}=\min_{0\le k\le j}\{dp_{i-1,k}+f(a_i,j)\}$$
其中 $f(x,y)$ 表示将 $x$ 改为 $y$ 需要的最小操作次数 .

这样维护一个前缀 $\min$ 即可 $\Theta(V)$ 转移 .

于是时间复杂度为 $\Theta(nV)$，$V$ 是值域 .

可以滚动数组优化空间复杂度到 $\Theta(V)$，不过卡空间不好所以不滚也是可以过的 .

---

## 作者：Nuyoah_awa (赞：2)

### 题目大意

给一个数组，求最少改变多少次使其变成一个单峰序列。

### 题目分析

首先来想暴力，我们枚举最终答案的“峰”在哪，然后左右扫一遍，使其单调不增，这个地方可以用 dp 维护，于是我们就得到了一个 $\mathcal O(n^2)$ 的做法，但是只有 $30$ pts。

上面想到了 dp，但是每回枚举“峰”会很慢，于是我们来想如何优化 dp。

因为是一个单峰序列，我们可以从“峰”分开，分两部分算。

首先，我们可以令 $f_{i, j}$ 表示到第 $i$ 个数为止将第 $i$ 个数改为 $j$ 的最少次数。我们可以枚举前一个点改为 $k$ 来更新 $f_{i, j}$（$k \le j$）。于是，转移方程为：

$$f_{i, j} = \min \limits_{k = 1}^{k \le j}f_{i-1,k} + dist(a_i, j)$$

其中，$dist(a_i, j)$ 表示将 $a_i$ 拨到 $j$ 所需要的次数。

同理，我们可以倒着求单峰序列的另一边，我们令 $g_{i, j}$ 表示从右开始，到第 $i$ 个数为止将第 $i$ 个数改为 $j$ 的最少次数。同理，转移方程为：

$$g_{i, j} = \min\limits_{k = j}^{k\le n} g_{i-1, k} + dist(a_i, j)$$

对于答案，我们只需要枚举最终答案的“峰”在哪和“峰”的“高度”。

$$ans = \min\limits_{i = 1}^{i \le n} \min\limits_{j = 0}^{j \le 9} f_{i, j} + g_{i, j}$$

所以最终的时间复杂度就是计算 $f$ 和 $g$ 的时间复杂度，就是 $\mathcal O(n \times k ^ 2)$（$k$ 表示密码的值域，本题即为 $10$）。

### code
```cpp
#include <iostream> 
#include <cstdio>
#include <vector>

using namespace std;

const int N = 5e6 + 5, INF = 1e9;
int n, a[N], f[N][10], g[N][10], ans = INF;

inline int dist(int u, int v)
{
	if(u > v)
		swap(u, v);
	int ans = v - u;
	int tmp = u - v + 10;
	return min(ans, tmp);
}

signed main()
{
    scanf("%d", &n);
    for(register int i = 1;i <= n;i++)
    	for(register int j = 0;j <= 9;j++)
    		f[i][j] = g[i][j] = INF;
    for(register int i = 0;i <= 9;i++)
    	f[0][i] = f[n+1][i] = 0;
    for(register int i = 1;i <= n;i++)
    {
    	scanf("%d", &a[i]);
    	for(register int j = 0;j <= 9;j++)
    		for(register int k = 0;k <= j;k++)
    			f[i][j] = min(f[i][j], f[i-1][k] + dist(a[i], j));
	}
	for(register int i = n;i >= 0;i--)
		for(register int j = 0;j <= 9;j++)
			for(register int k = 0;k <= j;k++)
				g[i][j] = min(g[i][j], g[i+1][k] + dist(a[i], j));
	for(register int i = 1;i <= n;i++)
		for(register int j = 1;j <= 9;j++)
			ans = min(ans, f[i][j] + g[i][j]);
	printf("%d", ans);
    return 0;
}
```

---

## 作者：programmer2048 (赞：1)

### 题意简介

给定一个由 $0∼9$ 组成的序列 $g$，每次操作可以用 $1$ 的代价将其中的一个数变为其相邻的数（$0$ 与 $9$ 也视为相邻）。

求将序列变为一个单峰序列（以某点为端点，左为单调不减序列，右为单调不增序列）所需的最小代价。

### 思路分析

此处给出一个暴力思路。

设 $f_{i,j,0}$ 表示将序列的第 $i$ 个值变为 $j$，且未过峰值时的最小代价。

相应的，$f_{i,j,1}$ 表示将序列的第 $i$ 个值变为 $j$，且已过峰值的最小代价。

由题意得：将第 $i$ 个值更改为 $j$ 的最终代价为 $\min\{ \mid j-g_i \mid,10-|j-g_i|\}$，设为 $C_{i,j}$。

故转移方程为：

$f_{i,j,0}=\min \limits_{k≤j} \{f_{i-1,k,0}+C_{i,j}\}$

$f_{i,j,1}=\min \limits_{k≥j} \{f_{i-1,k,0}+C_{i,j},f_{i-1,k,1}+C_{i,j}\}$

### AC 代码
```
#include<algorithm>
#include<iostream>
#include<cstring>
#include<math.h>
using namespace std;
const int N = 5000010;
int n,g[N],ans=0x3f3f3f3f;
int f[N][10][2];
int main()
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;++i)cin>>g[i];
    memset(f,0x3f,sizeof f);
    for(int i=0;i<=9;++i)f[0][i][0]=f[0][i][1]=0;
    for(int i=1;i<=n;++i)for(int j=0;j<=9;++j)for(int k=0;k<=9;++k)
    {
        int c=min(abs(j-g[i]),10-abs(j-g[i]));
        if(k<=j)f[i][j][0]=min(f[i][j][0],f[i-1][k][0]+c);
        if(k>=j)f[i][j][1]=min({f[i][j][1],f[i-1][k][0]+c,f[i-1][k][1]+c});
    }
    for(int i=0;i<=9;++i)ans=min({ans,f[n][i][0],f[n][i][1]});
    cout<<ans;
    return 0;
}
```

---

## 作者：TernaryTree (赞：1)

比较没意思的 dp。

考虑将前 $i$ 个数变成不降序列，将后 $i$ 个数变成不增序列。

记 $i$ 滑动到 $j$ 的距离是 $d_{i,j}$。设 $p_{i,j}$ 表示前 $i$ 个变为不降，最后一个数是 $j$ 的最少花费。则有：

$$p_{i,j}=\min_{k=0}^j p_{i-1,k}+d_{a_i,k}$$

$q$ 同理。于是 dp 完就可以枚举峰值然后统计了。

这里做到了 $\Theta(nv^2)$。非常显然可以前缀 $\min$ 优化。但是我懒得优化，$5\times 10^8$ 只要足够自信就能冲过去。甚至使用循环展开跑的和优化后的 $\Theta(nv)$ 几乎一样。

代码太长，我扔云剪贴板吧：[link](https://www.luogu.com.cn/paste/mg4dvog1)。

---

## 作者：船酱魔王 (赞：1)

# P9408 『STA - R2』Locked 题解

## 题意回顾

拨圈密码锁上共计 $ n $ 个环，每个环有 $ 0 \sim 9 $ 这些数字，初始时 $ a_i $ 为第 $ i $ 个拨圈的数字，你要通过最少的拨动使得密码锁形成单峰序列。求出最少拨动次数。

$ n \le 5 \times 10^6 $。

## 分析

一眼 DP。

单峰序列不好处理，考虑枚举峰值，则问题转化为前 $ i $ 个变成递增需要多少次加上后面变成递减需要多少次（注意减去重复的部分，即峰值本身）。

我们预处理出 $ d_{i,j} $ 表示 $ i $ 拨到 $ j $ 的最少次数。

定义前 $ i $ 个变成递增，且第 $ i $ 个改为 $ j $ 的最少次数为 $ pre_{i,j} $，则显然有：

$$ pre_{i,j}=\min_{k\le j}\{pre_{i-1,k}+d_{a_i,j}\} $$

定义第 $ i $ 个后变成递减，且第 $ i $ 个改为 $ j $ 的最少次数为 $ suf_{i,j} $，则显然有：

$$ suf_{i,j}=\min_{k\le j}\{suf_{i+1,k}+d_{a_i,j}\} $$

则第 $ i $ 个变成 $ j $ 且为峰值的答案为 $ pre_{i,j}+suf_{i,j}-d_{a_i,j} $。

时间复杂度为 $ O(nV^2) $，$ V $ 是值域，实现较好的话可以过，运算次数大约在 $ 5 \times 10^8 $ 左右。

需要快读。

## AC 代码

```
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 5e6 + 5;
const int inf = 1e9 + 5;
int n;
int a[N];
int read() {
	int f = 0;
	char ch = '#';
	while(ch < '0' || ch > '9') {
		ch = getchar();
	}
	while('0' <= ch && ch <= '9') {
		f *= 10;
		f += ch - '0';
		ch = getchar();
	}
	return f;
}
int abso(int x) {
	return max(x, -x);
}
int d[10][10];
int pre[N][10];
int suf[N][10];
int main() {
	n = read();
	for(int i = 1; i <= n; i++) {
		a[i] = read();
	}
	for(int i = 0; i < 10; i++) {
		for(int j = 0; j < 10; j++) {
			d[i][j] = min(abso(i - j), 10 - abso(i - j));
		}
	}
	for(int i = 1; i <= n; i++) {
		for(int j = 0; j < 10; j++) {
			pre[i][j] = inf;
			for(int k = 0; k <= j; k++) {
				pre[i][j] = min(pre[i][j], pre[i - 1][k] + d[a[i]][j]);
			}
		}
	}
	for(int i = n; i >= 1; i--) {
		for(int j = 0; j < 10; j++) {
			suf[i][j] = inf;
			for(int k = 0; k <= j; k++) {
				suf[i][j] = min(suf[i][j], suf[i + 1][k] + d[a[i]][j]);
			}
		}
	}
	int ans = inf;
	for(int i = 1; i <= n; i++) {
		for(int j = 0; j < 10; j++) {
			ans = min(ans, pre[i][j] + suf[i][j] - d[a[i]][j]);
		}
	}
	printf("%d\n", ans);
	return 0;
} 
```

---

## 作者：ethan0328 (赞：0)

## 闲话

~~赛时题目看错让我花了1小时~~。

## 思路

观察到 $a$ 最大只有 $10$，于是先预处理 $f_{i,j}$ 表示前 $i$ 位不下降且都 $\le j$ 的情况数。

### $f_{i,j}=\min (f_{i,j-1},f_{i-1,j}+d_{a_i,j})$

其中 $d_{i,j}$ 表示从 $i$ 变到 $j$ 所需的最小操作数。

同时，你用 $g_{i,j}$ 表示后 $i$ 位不上升且都 $\le j$ 的情况数。

最后，取最小的 $f_{i-1,j}+g_{i+1,j}+d_{a_i,j}$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e6+10;
int n,ans=2e9,a[N],f1[N][10],f2[N][10];
int to(int x,int y)
{
	return min(abs(x-y),10-abs(x-y));
}
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(int i=0;i<a[1];i++)
	{
		f1[1][i]=to(a[1],i);
	}
	for(int i=2;i<=n;i++)
	{
		f1[i][0]=f1[i-1][0]+to(a[i],0);
		for(int j=1;j<10;j++)
		{
			f1[i][j]=min(f1[i][j-1],f1[i-1][j]+to(a[i],j));
		}
	}
	for(int i=0;i<a[n];i++)
	{
		f2[n][i]=to(a[n],i);
	}
	for(int i=n-1;i;i--)
	{
		f2[i][0]=f2[i+1][0]+to(a[i],0);
		for(int j=1;j<10;j++)
		{
			f2[i][j]=min(f2[i][j-1],f2[i+1][j]+to(a[i],j));
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<10;j++)
		{
			ans=min(ans,f1[i-1][j]+to(a[i],j)+f2[i+1][j]);
		}
	}
	cout<<ans;
}
```


---

## 作者：ran_qwq (赞：0)

本来想到[这道题](https://www.luogu.com.cn/problem/P4597)，但发现卡 $O(n\log n)$ 的做法。但马上注意到 $a_i$ 范围非常小，考虑 dp。

定义 $f_{i,j}$ 为把前 $i$ 位变为单调递增，且第 $i$ 位为 $j$ 的最小步数。则第 $i-1$ 位就可以在 $[0,j]$ 范围内。状态转移方程就是 $f_{i,j}=\min_{k=0}^jf_{i-1,k}+b_{j,a_i}$。其中 $b_{i,j}$ 表示把 $i$ 变为 $j$ 所需要的操作数，先预处理出来减少重复计算。

类似的，定义 $g_{i,j}$ 为把后 $i$ 位变为单调递减，且第 $i$ 位为 $j$ 的最小步数。则第 $i+1$ 位就可以在 $[0,j]$ 范围内。状态转移方程就是 $g_{i,j}=\min_{k=0}^jg_{i+1,k}+b_{j,a_i}$。

初始状态就是 $f_{0,i}=0(0\le i<10)$，其他设为无穷大；$g_{n+1,i}=0(0\leq i<10)$，其他也设为无穷大。

答案就是枚举从单调递增转为单调递减的转折点 $i$（即前 $i$ 位单调递增，后 $i+1$ 位单调递减）。第 $i$ 位和第 $i+1$ 位都可以是任意数字。所以答案就是 $\min_{i=1}^n\min_{j=0}^9\min_{k=0}^9(f_{i,j}+g_{i+1,k})$。

洛谷评测机真神奇，$O(nv^2)$ 居然才跑到 $600$ 毫秒（$v$ 为 $a_i$ 的范围，即为 $10$）。其实可以 $O(nv)$ 的，但赛时懒得写。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e6+10,INF=0x3f3f3f3f;
int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
void Write(int x){if(x<0){putchar('-'),Write(-x);return;}if(x<10){putchar(x+'0');return;}Write(x/10),putchar(x%10+'0');}
void write(int x,char *s){Write(x),printf("%s",s);}
int n,ans=INF,a[N],b[10][10],f[N][10],g[N][10];
void solve()
{
	n=read();for(int i=1;i<=n;i++) a[i]=read();
	memset(f,0x3f,sizeof f),memset(g,0x3f,sizeof g);for(int i=0;i<10;i++) f[0][i]=g[n+1][i]=0;
	for(int i=0;i<10;i++) for(int j=0;j<10;j++) b[i][j]=min(abs(i-j),10-abs(i-j));
	for(int i=1;i<=n;i++)
		for(int j=0;j<10;j++)
			for(int k=0;k<=j;k++) f[i][j]=min(f[i][j],f[i-1][k]+b[a[i]][j]);
	for(int i=n;i;i--)
		for(int j=0;j<10;j++)
			for(int k=0;k<=j;k++) g[i][j]=min(g[i][j],g[i+1][k]+b[a[i]][j]);
	for(int i=1;i<=n;i++)
		for(int j=0;j<10;j++)
			for(int k=0;k<10;k++) ans=min(ans,f[i][j]+g[i+1][k]);
	write(ans,"");
}
signed main()
{
	int T=1;
	while(T--) solve();
}
```

---

## 作者：Link_Cut_Y (赞：0)

赛时唯一做出来的题。

注意下面的**递增**均指**非严格单调递增**。递减同理。

设 $f_{i, j}$ 为前 $i$ 个数递增的最小操作次数，则有如下转移：

$$f_{i, j} = \min\{f_{i - 1, k}\} + \operatorname{calc(j, a_i)}$$

其中 $k \le j$，$\operatorname{calc(a, b)}$ 指从 $a$ 转到 $b$ 的最小操作次数。

同样的，设 $g_{i, j}$ 为后 $i$ 个数递减的最小操作次数。倒着跑 dp 即可。

代码可以看这里：[暴力 dp 解法](https://www.luogu.com.cn/paste/6sc6fpr8)。

这样的时间复杂度为 $O(100 \times n)$。虽然这个 $100$ 放在里面不严谨，但是我实在不知道该怎么放了。当 $n$ 达到 $5 \times 10 ^ 6$ 时，$100 \times 5 \times 10 ^ 6 = 5 \times 10 ^ 8$。虽然你谷机子跑的很快，但是还是跑不过。

接下来考虑优化。求 $\min\{f_{i - 1, k}\}$ 这部分显然可以优化。可以在循环的时候顺便更新，也可以单独再开一个前缀 min 数组单独存着。这样复杂度降为 $O(10 \times n)$。可以通过。

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

const int N = 5000010;

int f[N][10], g[N][10];
int n, a[N];
int minf[10], ming[10];

int get(int x, int y) {
	if (x > y) swap(x, y);
	return min(abs(x - y), x + 10 - y);
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i ++ )
		scanf("%d", &a[i]);
	memset(f, 0x3f, sizeof f);
	for (int i = 0; i <= 9; i ++ )
		f[1][i] = get(i, a[1]);
	minf[0] = f[1][0]; for (int i = 1; i <= 9; i ++ ) minf[i] = min(minf[i - 1], f[1][i]);
	for (int i = 2; i <= n; i ++ ) {
		for (int j = 0; j <= 9; j ++ ) {
			f[i][j] = minf[j] + get(j, a[i]);
		}
		minf[0] = f[i][0];
		for (int j = 1; j <= 9; j ++ )
			minf[j] = min(minf[j - 1], f[i][j]);
	}
	
	memset(g, 0x3f, sizeof g);
	for (int i = 0; i <= 9; i ++ )
		g[n][i] = get(i, a[n]);
	ming[0] = g[n][0]; for (int i = 1; i <= 9; i ++ ) ming[i] = min(ming[i - 1], g[n][i]);
	for (int i = n - 1; i >= 1; i -- ) {
		for (int j = 0; j <= 9; j ++ ) {
			g[i][j] = ming[j] + get(j, a[i]);
		}
		ming[0] = g[i][0];
		for (int j = 1; j <= 9; j ++ )
			ming[j] = min(ming[j - 1], g[i][j]);
	}
	
	int ans = 2e9;
	for (int i = 1; i <= n; i ++ ) {
		for (int j = 0; j <= 9; j ++ ) {
			ans = min(ans, f[i][j] + g[i][j] - get(a[i], j));
		}
	}
	
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：无钩七不改名 (赞：0)

先预处理出每个数变为另一个数需要的最少次数。

因为“$0$ 和 $9$ 可以互换”，所以我们可以把数字 $x(0\le x\le 9)$ 都看成 $x$ 和 $10+x$。所以 $x(0\le x\le 9)$ 变成 $y(0\le y\le 9)$ 所需要的次数便是 $\min(\operatorname{abs}(x-y),\operatorname{abs}(\min(x,y)+10-\max(x,y)))$。

很容易想到 dp。

令 $dp_{i,j,0}$ 表示单调上升时把第 $i$ 个数变成 $j$ 时所需要的最小代价。$dp_{i,j,1}$ 表示单调下降把第 $i$ 个数变成 $j$ 时所需要的最小代价。

很容易得到状态转移方程式：

$$
dp_{i,j,0}=\min\limits_{0\le k\le j\le 9}(dp_{i-1,k,0}+ \min(\operatorname{abs}(a_i-j),\operatorname{abs}(\min(a_i,j)+10-\max(a_i,j)))
$$

$$
dp_{i,j,1}=\min\limits_{0\le j\le k\le 9}(dp_{i,j,0},\min(dp_{i-1,k,0}+ \min(\operatorname{abs}(a_i-j),\operatorname{abs}(min(a_i,j)+10-\max(a_i,j))))
$$

可以直接把第一维通过转移的顺序优化掉。

代码如下：


```cpp
#include<bits/stdc++.h>
using namespace std; 

int n,a[5000005],b[10][10];
int ans[10][2],res=1<<30;

int main(){
	scanf("%d",&n);
	for(int i(0);i<=9;i++)
		for(int j(0);j<=9;j++){
			b[i][j]=min(abs(i-j),abs(min(i,j)+10-max(j,i)));
			//cout<<i<<" "<<j<<" "<<b[i][j]<<endl;
		}
			
	for(int i(1);i<=n;i++){
		scanf("%d",a+i);
		for(int j(0);j<9;j++){
			for(int k(j+1);k<=9;k++)
				ans[j][1]=min(ans[k][1],ans[j][1]);
			ans[j][1]=ans[j][1]+b[j][a[i]];
		}
		ans[9][1]+=b[9][a[i]];
		//cout<<"***"<<i<<endl;
		for(int j(9);j;j--){
			for(int k(0);k<j;k++)
				ans[j][0]=min(ans[k][0],ans[j][0]);
			ans[j][0]+=b[j][a[i]]; 
			ans[j][1]=min(ans[j][1],ans[j][0]);
			//cout<<j<<":"<<ans[j][0]<<" "<<ans[j][1]<<endl;
		}
		ans[0][0]+=b[0][a[i]];
	}
	for(int i(0);i<=9;i++){
		res=min(res,min(ans[i][0],ans[i][1]));
	}
	printf("%d",res);
	return 0;
}
```


---

