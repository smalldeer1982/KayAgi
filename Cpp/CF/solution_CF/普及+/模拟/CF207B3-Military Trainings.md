# Military Trainings

## 题目描述

### 题目大意
有 $n$ 个坦克，从1到n编号，它们要进行消息传输。

每一次传输如下，列表中第一个坦克将信息传输到列表中的某个坦克。接收到该消息的坦克将其进一步发送到列表后的某个坦克。该过程将继续进行，直到最后一个坦克收到消息。可能不是列表中的所有坦克都会收到消息，但列表中的最后一个坦克必须收到消息。

当最后一个坦克收到消息时，它将挪到第一个位置，并发送一条消息。当信息到达最后一个坦克时，该坦克移动到列的开头，并将下一条信息发送到列表的末尾，依此类推。因此，当列中的坦克返回到其原始顺序时，练习就完成了。

在两个坦克之间传输信息需要一秒钟，然而，并非总是一个坦克可以将信息传输给另一个坦克。让我们考虑列中的两个坦克，使它们中的第一个是从开始计数的列中的第i个，第二个是列中的j个，并假设第二个坦克的编号为x。然后，如果$ i<j $ and $ i>=j-a_{x} $ 则可以传输。

你会得到坦克的数量，以及所有坦克的信息接收半径。您必须帮助Smart Beaver并组织消息传输，使所有消息的总传输时间尽可能短。

## 样例 #1

### 输入

```
3
2
1
1
```

### 输出

```
5
```

## 样例 #2

### 输入

```
5
2
2
2
2
2
```

### 输出

```
10
```

# 题解

## 作者：xiaohaoaibiancheng66 (赞：3)

# 思路
本题解第一部分和[弱化版](https://www.luogu.com.cn/problem/CF207B2)一致。请先阅读[弱化版题解](https://www.luogu.com.cn/blog/xiaohao-aibiancheng/solution-cf207b2)。

对于每个 $x$ 找 $y$，目前的方法还是一个一个找。但是这样太慢了，可以通过**倍增**来优化：

对于每个 $x$，求出 $x$ 的第 $2^0,2^1\dots2^{\log n}$ 个 $y$。这样预处理复杂度 $O(n\log n)$，每次查询复杂度 $O(\log n)$，总时间复杂度 $O(n\log n)$，可以通过。
# AC code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define MAXN 1000000
 
int Log[MAXN];
int st[MAXN][30];
int a[MAXN];
int fa[MAXN][30];
 
//ST 表
void init(int n)
{
	Log[0]=Log[1]=0;
	for(int i=2;i<=n;i++)Log[i]=Log[i/2]+1;
}
 
void Build(int n)
{
	for(int i=0;i<=n;i++)st[i][0]=i;
	for(int j=1;j<=Log[n]+1;j++)
		for(int i=0;i<=n;i++) 
			st[i][j]=((a[st[i][j-1]]<=a[st[i+(1<<(j-1))][j-1]])?st[i][j-1]:st[i+(1<<(j-1))][j-1]);
}
 
inline int Query(int l,int r)
{
	int t=Log[r-l+1];
	return (a[st[l][t]]<=a[st[r-(1<<t)+1][t]])?st[l][t]:st[r-(1<<t)+1][t];
}
	
int main()
{
	int n;
	cin>>n;
	init(2*n);
	for(int i=1;i<=n;i++)cin>>a[i],a[i+n]=a[i];
	for(int i=1;i<=n+n;i++)a[i]=max(i-a[i],1);
	Build(2*n);
	//倍增
	for(int i=1;i<=n+n;i++)fa[i][0]=Query(a[i],i);
	for(int j=1;j<30;j++)
        for(int i=1;i<=n+n;i++)
            fa[i][j]=fa[fa[i][j-1]][j-1];
	long long ans=0;
	
	for(int i=1;i<=n;i++)
	{
		long long cnt=2;
		int now=i+n-1;
		//特判
		if(a[now]<=i)
		{
 			ans++;
			continue;
		}
		//查询
		for(int j=29;j>=0;j--)
		{
 			if(a[fa[now][j]]>i)cnt+=(1<<j),now=fa[now][j];
 		}
		ans+=cnt;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：tder (赞：1)

> You can view the [English version](https://www.luogu.com/article/wk2tr02m/) of this solution.

> 图片托管于 Github，若加载失败请使用加速器。

首先容易想到把序列复制一遍，破环为链，每个询问即查询子段答案。

设 $f_i$ 能从 $j=x$ 或 $j=y$ 转移而来，考虑一个贪心。

![](https://raw.githubusercontent.com/tder6/Img/refs/heads/main/Sol/CF207B3/img.png)

其中 $P(k)$ 表示 $f_k$ 能从哪些点转移而来，即 $P(k)=[k-p_k,k-1]$。

由于 $k-1\in P(k)$ 恒成立，我们无需考虑 $[i-p_i,k-1]$ 这段区间的贡献。而 $[y-p_y,i-p_i]\subseteq[x-p_x,i-p_i]$，即所有能转移到 $y$ 的点都能转移到 $x$，因此选择从 $x$ 转移而来即可。这也就是说，从 $k-p_k$ 较小的 $k$ 转移来是不劣的。用 ST 表维护之，复杂度 $\mathcal{O}(n\log n+\text{ans})$。

你交了一发，并发现这个东西在模拟赛过了。可以使用倍增预处理出跳 $2^n$ 步能跳到哪，优化成 $\mathcal{O}(n\log n)$。

---

## 作者：aaalys (赞：0)

# CF207B Military Trainings 题解

## 题目大意

[题目传送门](https://www.luogu.com.cn/problem/CF207B3)（[cf 原题](https://codeforces.com/problemset/problem/207/B3)）

有 $n$ 辆坦克，从 $1$ 到 $n$ 编号，这些坦克要进行 $n$ 次传递信息，方式如下。

编号为 $1$ 的坦克可以把信息传递给后面的一辆坦克，再传给下一辆坦克。以此类推，直到传递到第 $n$ 辆坦克。

每个坦克有一个传递半径，初始时编号为 $i$ 的坦克传递半径为 $a_i$。

编号为 $i$ 的坦克能给编号为 $j$ 的坦克传递信息当且仅当 $i < j$ 且 $i \ge j - w$，其中 $w$ 表示编号为 $j$ 的坦克传递半径。

在第 $n$ 辆坦克接收到信息之后，它会移动到这列坦克的开头，并用同样的方式传递信息给最移动后最末尾的坦克（也就是原先的第 $n-1$ 号坦克）。在信息传递到末尾的坦克后，那辆坦克移动到这列坦克的开头，并发送下一个信息到队列 a 末尾。依此类推，直到传递完 $n$ 次信息。

## 思路

首先可以先不考虑移动的情况，只考虑不移动的情况，最后加上移动。

### Step1：反向思考

如果正向考虑（从 $1$ 号传递到 $n$ 号），从 $i$ 号坦克能传递到的坦克编号不连续，不容易处理。

那就需要反向思考，考虑哪个坦克能传递到 $i$ 号坦克，这样坦克编号就会变连续，容易处理。

进一步的，可以把原题看成从 $n$ 号坦克传递信息到 $1$ 号坦克，条件从 $i$ 号坦克传递给 $j$ 号坦克变成 $j$ 号坦克传递给 $i$ 号坦克。

### Step2：贪心选择

那对于 $i$ 号坦克，他能传递给的坦克编号在 $[i-w,i-1]$ 区间内（$w$ 表示编号为 $i$ 的坦克传递半径）。

根据贪心的思路，每次传递信息一定要传递给下一次能到达最远的点。形式化来说，就是选一个点 $j\in[i-w,i-1]$，使得 $j-v$ 最小（$w$ 表示编号为 $j$ 的坦克传递半径）。

### Step3：获取答案

设从 $i$ 号坦克要到的坦克编号为 $nx_i$，那么每次查询只需要设一个变量 $now$，表示当前的坦克编号。

那只需要重复循环，每次让 $now$ 变成 $nx_{now}$，统计一下传递的次数就能得到答案。

### Step4：移动处理

上面考虑的都是没有移动的情况，如果加上移动，可以把这些坦克看成一个环，每次移动只是初始的信息来源变化而已。

遇到环，可以用破环成连的方式解决，就是把原数组复制一份频道后面，查询的时候也是用一样的方法，每次查询让 $now$ 的初始值不同即可。

### Step5：时间优化

如果按照上面的方法，贪心选择下一步的时间复杂度为 $O(n^2)$，获取答案的时间复杂度也为 $O(n^2)$，总时间复杂度为 $O(n^2)$，本题的数据范围是 $n\le 250000$，这样不可通过此题。

先看贪心选择下一步的优化，为了方便计算和列式，我们设 $b_i=i-a_i$。

这部分是区间查询最小，可以使用 st 表优化，设 $mn_{i,j}$，为 $[i,i+2^j-1]$ 区间内的最小 $b_x$ 的 $x$。

st 表类似动态规划，也有自己的转移方程，比如我这个 st 表的转移方程如下。$mn_{i,j} = \begin{cases} mn_{i,j-1} & b_{mn_{i,j-1}} \le b_{mn_{i+2^{j-1},j-1}} \\ mn_{i+2^{j-1},j-1} & b_{mn_{i,j-1}} > b_{mn_{i+2^{j-1},j-1}} \end{cases}$

初始值就是 $mn_{i,0}=i$，最终的答案 $nx_i$ 就是 $[b_i,i]$ 这段区间内最小 $b_x$ 的 $x$，用 st 表的方式查询即可。

经过 st 表的优化，这部分的时间复杂度为 $O(n \log n)$。

再看获取答案这部分的优化。

不难发现，如果把 $nx_i$ 看做父节点，向子节点 $i$ 连边，形成的图是一颗树，也可以用 st 表进行优化。

设 $f_{i,j}$ 为从 $i$ 开始，向上跳 $2^j$ 步所能跳到的节点。

转移很简短，就是 $f_{i,j}=f_{f_{i,j-1},j-1}$。

获取答案用倍增求 lca 的方法，还是需要设一个变量 $now$，表示当前的坦克编号，再从大往小枚举 $j$，让 $now$ 停在终点的前一步，统计答案时把答案加 1。

经过 st 表的优化，这部分的时间也复杂度为 $O(n \log n)$，总时间复杂度为 $O(n \log n)$，可以通过此题。

## 代码实现

### 实现细节

统计答案时要注意终点的前一步 $now$ 可以不仅可以过 $nx_{now}<need$ 停下来，而是也可以通过 $b_{now}<need$ 停下来（$need$ 为需要到达的终点）。

因为进行了破环成连，所以数组空间要开两倍，即 $5\times10^5$。

**一定要注意以下几点。**

- 每次最多从 $i$ 传递信息到 1，所以 $b_i$ 要取 $\max (1,i-a_i)$（我上面没加 max 是为了方便理解）。
- 有句俗话叫“十年 oi 一场空，不开 long long 见祖宗。”。经过计算可知，最终答案最大是 $\sum_{i=1}^{n-1}=\frac{n(n-1)}{2}$，会超过 int 类型上限，需要开 long long。
- 有的地方需要用 $2n$，有的地方需要用 $n$，注意分清。

有些小技巧，可以节省一些代码长度。

- 可以直接把 $a_i$ 赋值为成 $b_i$，后面就不用再次计算 $b_i$，$a_i$ 之后用不到。
- 进行树上 st 表的时候，可以不建树，因为我们知道父节点的编号，可以直接将 $f_{i,0}$ 设为 $nx_i$，进行 st 表的转移。

### Code（只展示关键代码）

```cpp
int a[N], lg[N] = {-1};//a数组（修改后为b数组）和求答案用的log2数组
int mn[N][M], f[N][M];//2个st表
int get(int l, int r){//l,r这段区间内最小b[x]的x
    int k = lg[r - l + 1];
    int lid = mn[l][k], rid = mn[r - (1 << k) + 1][k];
    if (a[lid] <= a[rid])return lid;
    return rid;
}
int getans(int x){//获取答案
    int need = x - n + 1, ans = 2;//加了特殊处理，ans初始值要设成2
    if (a[x] <= need)return 1;//特判一步就能到达的情况
    for (int i = lg[2 * n]; i >= 0; i--)
        if (a[f[x][i]] > need){//不一定是nx[now]，可能是b[now]
            x = f[x][i];
            ans += (1 << i);
        }
    return ans;
}
void init(){//初始化第一个st表
    for (int i = 1; i <= 2 * n; i++)a[i] = max(1, i - a[i]);//将a[i]改成b[i]
    for (int i = 1; i <= 2 * n; i++)mn[i][0] = i;//初始化st表
    for (int i = 1; i <= 2 * n; i++)lg[i] = lg[i / 2] + 1;//求log2数组
    for (int j = 1; j <= lg[2 * n]; j++)
        for (int i = 1; i + (1 << j) - 1 <= 2 * n; i++){
            //转移
            int lid = mn[i][j - 1], rid = mn[i + (1 << (j - 1))][j - 1];
            if (a[lid] <= a[rid])mn[i][j] = lid;
            else mn[i][j] = rid;
        }
}
for (int i = 2; i <= 2 * n; i++){
    int fa = get(a[i], i);//nx[i]
    f[i][0] = fa;//初始化
}
for (int j = 1; j <= lg[2 * n]; j++)
    for (int i = 1; i <= 2 * n; i++)
        f[i][j] = f[f[i][j - 1]][j - 1];//转移
ll ans = 0;//记得开long long
for (int i = 0; i < n; i++)//累加答案
    ans += getans(i + n);

```

---

