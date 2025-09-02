# [USACO22FEB] Redistributing Gifts S

## 题目描述

FJ 有 $N$ 个礼物给他的 $N$ 头奶牛，这 $N$ 个礼物和 $N$ 头奶牛都被标记为 $1 \dotsm N (1 \le N \le 500)$ 。 每头奶牛都有一个愿望单，记录着一个含有 $N$ 个礼物的排列。比起在愿望单中出现更晚的礼物，奶牛更喜欢先出现在愿望单中的礼物。

因为 FJ 太懒了，他直接把 $i$ 号礼物分配给了 $i$ 号奶牛。现在，奶牛们聚在了一起，决定重新分配礼物，以便在重新分配后，每头奶牛都能得到跟原来一样，或是它更喜欢的礼物。

对于每个 $i$ （$i$ 从 $1$ 到 $N$），计算出重新分配后， $i$ 号奶牛可能拿到的最好的礼物（这个奶牛经过重新分配后能拿到的最喜欢的礼物）。

## 说明/提示

- $2 \sim 3$ 号测试点满足 $N \le 8$
- $4 \sim 11$ 号测试点没有别的限制

由 [tzyt](https://www.luogu.com.cn/user/394488) 翻译

## 样例 #1

### 输入

```
4
1 2 3 4
1 3 2 4
1 2 3 4
1 2 3 4```

### 输出

```
1
3
2
4
```

# 题解

## 作者：Jorge_Filho (赞：20)

# USACO22FEB SILVER T1 Solution

## 题意:
现在有 $n$ 个礼物和奶牛，编号从 $1$ 到 $n$，每个奶牛都有一个 $n$ 的排列 $a_i$，表示奶牛喜欢的礼物的顺序（越在前面的奶牛越喜欢）。一开始，每一个奶牛都获得了一个与自己编号相同的礼物，现在你可以重新分配礼物，使得每一个奶牛都能获得自己更喜欢的或者原来的礼物。请在**所有**可能的分配方案中（不一定是在同一个分配方案中），找出每一个奶牛可能分配到的最喜欢的礼物。

## 解析:

对于每一个奶牛 $i$，考虑能分配到的最喜欢的礼物的编号。设在这个奶牛原先分配到的礼物在 $a_i$ 中的位置为 $pos_i$，这个奶牛能分配到的最喜欢的礼物在 $a_i$ 中的位置为 $ans_i$。那么明显有 $ans_i \leq pos_i$。因为 $pos_i$ 在输入时就可以算出，那么我们可以在 $1$ 到 $pos_i-1$ 中依次枚举 $ans_i$，判断这个位置是否可行，可行就可以直接输出 $a_{i,ans_i}$ 了（因为从小到大枚举出的第一个满足条件的值就是最小值），不可行就再判断下一个位置。若全部都不行可行，就成直接输出 $i$。

那么现在问题就是如何判断 $ans_i$ 是否可行了。如果第 $i$ 个奶牛选择了第 $ans_i$ 个礼物，那们原先选择 $a_{i,ans_i}$的奶牛就需要重新选择，重新选择后又会影响到下一个奶牛使其重新选择，下一个奶牛又影响到下下个奶牛……如果最后影响能回到第 $i$ 个奶牛（即可以形成一个环），就判断判断成功了（因为这样每一个奶牛都能够分配到一个合法的礼物）。

于是判断的做法就出来了：我们就把这些排列抽象成一个图，把每一个 $i$ 和在 $a_i$ 中的所有位置在 $pos_i$ 之前的点连一条有向边，再判断从 $pos_i$ 出发第一个经过 $ans_i$ 能否形成一个环。能就成功，否则失败。具体实现不需要使用高级算法，Dfs即可。

渐进时间复杂度：$O(n^2)$

Code：（为了各位读者我格式化了一下毒瘤码风）
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=500,M=N*N/2;
int n,a[N+5][N+5],pos[N+5],st;
int h[N+5],ne[M+5],e[M+5],idx;
bool ans,bjt[N+5][N+5];
void Read(int &x);//快读
void Add(const int &x,const int &y);//加边函数
void Dfs(const int &x);//深搜实现任意两点间能否到达从而判断环

int main() {
	Read(n);
	for(int i=1; i<=n; i++) 
		for(int j=1; j<=n; j++) {
			Read(a[i][j]);
			if(a[i][j]==i) pos[i]=j;//i在a[i][j]中的位置
		}
	memset(h,-1,sizeof(h));
	for(int i=1; i<=n; i++)
		for(int j=1; j<pos[i]; j++) Add(i,a[i][j]);//加边
	for(int i=1; i<=n; i++) {
		st=i;
		Dfs(i);//判断任意两个点之间能否到达
	}
	for(int i=1; i<=n; i++) {
		ans=1;//是否判断成功
		for(int j=1; j<pos[i]; j++)
			if(bjt[a[i][j]][i]) {//有环
				ans=0;
				printf("%d\n",a[i][j]);
				break;
			}
		if(ans) printf("%d\n",i);//判断不成功就只能输出自己了
	}
	return 0;
}

void Read(int &x) {
	char t=getchar();
	bool neg=0;
	int ress=0;
	while(t>'9'||t<'0') {
		t=getchar();
		if(t=='-') neg=1;
	}
	while(t<='9'&&t>='0') {
		ress=ress*10+t-'0';
		t=getchar();
	}
	x=neg?-ress:ress;
}

void Add(const int &x,const int &y) {
	e[idx]=y;
	ne[idx]=h[x];
	h[x]=idx++;
}

void Dfs(const int &x) {
	for(int i=h[x]; ~i; i=ne[i]) {
		int cur=e[i];
		if(bjt[st][cur]) continue;
		bjt[st][cur]=1;
		Dfs(cur);
	}
}
```
[考场代码](https://www.luogu.com.cn/record/70633656)

注：本方法是我考场时想出来的，并不是官方题解或最优解，也有很多可以优化的地方，但在考试时对于 $n \leq 500$ 的数据范围和 $2000ms$ 的限时已经完全够用了。

---

## 作者：xixike (赞：13)

## Description

[Luogu传送门](https://www.luogu.com.cn/problem/P8186)

## Solution

（感谢 @[Acestar](https://www.luogu.com.cn/user/211300) 提供的思路）

初始情况下，每头奶牛匹配一个礼物，所以我们把奶牛和礼物当作一个点。

如果奶牛 $i$ 非常不要脸的去抢奶牛 $j$ 的礼物（$i$ 向 $j$ 连单向边），而且不幸的是奶牛 $j$ 还打不过奶牛 $i$，那么 $j$ 就被迫去抢别人的礼物 qwq，所以 $j$ 就必须向它能抢到的别的奶牛连边。

因此我们这个图就建出来了，找一组解只需要跑一遍传递闭包即可，顺便拿个 $\text{bitset}$ 优化一下，时间复杂度 $O(\frac {n^3}\omega)$，跑的飞快。

## Code

@[ShuKuang](https://www.luogu.com.cn/user/168223) 已经成功卡到了目前最优解。

顺便感谢他提供的代码（

```cpp
#include <bits/stdc++.h>
using namespace std;

namespace IO {
    template <typename T>
    inline void read(T &x) {
        x = 0; T r = 1;
        char ch = getchar();
        while (!isdigit(ch)) r = ch == '-' ? -1 : 1, ch = getchar();
        while (isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
        x *= r;
    }

    template <typename T, typename ...Args>
    void read(T &x, Args &...args) {
        read(x), read(args...);
    }

    template <typename T>
    inline void write(T x) {
        if (x < 0) putchar('-'), x = -x;
        if (x > 9) write(x / 10);
        putchar(x % 10 + '0');
    }
}

using namespace IO;
bitset<511> f[511];

short n;
short a[511][511];

signed main() {
    read(n);
    for (short i = 1; i <= n; ++ i) {
        for (short j = 1; j <= n; ++ j) {
            read(a[i][j]);
        }
    }
    for (short i = 1; i <= n; ++ i) {
        for (short j = 1; j <= n; ++ j) {
            if (a[i][j - 1] == i) break;
            f[i][a[i][j]] = 1;
        }
    }
    for (short j = 1; j <= n; ++ j) {
        for (short i = 1; i <= n; ++ i) {
            if (f[i][j]) 
                f[i] |= f[j];
        }
    }
    for (short i = 1; i <= n; ++ i) {
        for (short j = 1; j <= n; ++ j) {
            if (f[i][a[i][j]] && f[a[i][j]][i]) {
                write(a[i][j]), putchar('\n');
                break;
            }
        }
    }

}
```



---

## 作者：_lmh_ (赞：9)

### P8186 Redistributing Gifts
### 1.题意简述
有 $n$ 头牛和 $n$ 个礼物，编号为 $1,2,3,...,n$，初始时每头牛都分到了与它编号相同的礼物。

奶牛们对所有礼物的喜爱程度都有一个排序，且它们想重新分配礼物。如果存在另一种分配方式，使得每头牛都能得到当前的礼物或比它更好的礼物，则它们可能会采用这种方式。

求每头牛可能得到的对它来说最好的礼物。

### 2.样例分析

首先看一组样例：
```
5
5 4 3 2 1
1 2 5 4 3
2 3 4 1 5
5 1 4 2 3
4 5 2 1 3
```
输出为：
```
5
1
2
5
4
```
用礼物的编号来表示分配方式。
如 $1,5,4,2,3$ 代表 $1$ 号牛拿到了 $1$ 号礼物，$2$ 号牛拿到了 $5$ 号礼物，以此类推。

这组样例中的合法方案有：
```
5 2 3 1 4
3 1 2 5 4
```
这两种方案就足以得出答案。方案 $1$ 中，$1,4,5$ 号牛交换了礼物，方案 $2$ 中，$1,2,3$ 号牛交换了礼物，而它们都是以**轮换**的方式交换礼物（如我的给你，你的给他，他的给我）。因此，我们就能想到一种算法，就是Floyd判环。

### 3.做法分析
该题中无需分析最短路，所以只需判环即可。

首先建图：若一头奶牛认为另一头奶牛的礼物比它的好，则该奶牛对应的点向另一头奶牛对应的点连一条**有向边**。

```cpp
for (int i=1,a;i<=n;i++) for (int j=1;j<=n;j++){
	cin>>a;
	if (a==i) {
		for (j++;j<=n;j++) cin>>a;break;
//后面的礼物没有原来的好，直接忽略
	}
	d[i][a]=1;
	to[i].push_back(a);
}
```

接下来的判环略有难度。常规的判环都是将 $d_{i,i}$ 初始化为 $0$ 后 Floyd ，最后判断 $d_{i,i}$ 是否为 $1$，然而本题中可能有多个环，为了同时判断礼物的来源，应修改为判断 $d_{i,j}$ 和 $d_{j,i}$ 同时为 $1$。

```cpp
for (int i=1,fl;i<=n;i++){
	fl=0;
	for (int j=0;j<to[i].size();j++){
		if (d[to[i][j]][i]){
			cout<<to[i][j]<<endl;fl=1;break;
//找到了环，获得新礼物
		}
	}
	if (!fl) cout<<i<<endl; //没有环，保留原来的礼物
}
```

把它们连在一起就得到了完整代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int d[507][507],n;
vector<int> to[507];
//to[i]记录比i号牛原来的礼物好的礼物
int main(){
	cin>>n;
	for (int i=1,a;i<=n;i++) for (int j=1;j<=n;j++){
		cin>>a;
		if (a==i) {
			for (j++;j<=n;j++) cin>>a;break;
//后面的礼物没有原来的好，直接忽略
		}
		d[i][a]=1;to[i].push_back(a);
	}
	for (int k=1;k<=n;k++) 
		for (int i=1;i<=n;i++)
			for (int j=1;j<=n;j++)
				d[i][j]|=(d[i][k]&&d[k][j]);
//Floyd
	for (int i=1,fl;i<=n;i++){
		fl=0;
		for (int j=0;j<to[i].size();j++){
			if (d[to[i][j]][i]){
				cout<<to[i][j]<<endl;fl=1;break;
//找到了环，获得新礼物
			}
		}
		if (!fl) cout<<i<<endl; //没有环，保留原来的礼物
	}
	return 0;
}
```

---

## 作者：duchengjun (赞：7)

~~Floyd 传递闭包模板题~~

# 定义

对与每一个 $f[i][j]$ 我们定义为奶牛 i 是否可以和奶牛 j 交换物品。

则当 $f[i][j]=true$ 时，第 i 头奶牛可以给第 j 头奶牛交换礼物；当 $f[i][j]=false$ 时，第 i 头奶牛不可以给第 j 头奶牛交换礼物。

# 建图

每一头奶牛拿到的是第 i 个礼物，所以在礼物数组 $a[i][j]=i$ 之前（包括 i 本身）的所有 $f[i][a[i][j]]$ 置为 $true$。

# Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define For(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int N=500+10;
int n;
int a[N][N];
int f[N][N];
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			cin>>a[i][j];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			f[i][a[i][j]]=true;
			if(a[i][j]==i)
				break;
		}
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				f[i][j]|=(f[i][k]&f[k][j]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(f[i][a[i][j]]&&f[a[i][j]][i]){
				cout<<a[i][j]<<endl;
				break;
			}
	return 0;
}

```


---

## 作者：expnoi (赞：6)

这题可以用 ```Floyd``` 传递闭包来做。

主要思路：

我们设 ```f[i][j]``` 表示 $i$ 是否可以和 $j$ 换。

当 ```f[i][j]=1``` 时，可以换，反之亦然。

所以， 当 ```f[i][j]=f[j][i]=1``` 时， $i$ 可以跟 $j$ 换，然后 $j$ 也可以跟 $i$ 换，也就是两个礼物可以互换。

最后求答案，我们已经预处理出了任意一对 ```f[i][j]``` ，最后统计答案即可。

大概就是这样了吧。

下面是代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[1001][1001];
bool f[1001][1001];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			cin>>a[i][j];
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			f[i][a[i][j]]=1;
			if(a[i][j]==i)
			{
				break;
			}
		}
	}
	for(int k=1;k<=n;k++)
	{
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
			{
				f[i][j]|=(f[i][k]&f[k][j]); 
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(f[i][a[i][j]]&&f[a[i][j]][i])
			{
				cout<<a[i][j]<<'\n';
				break;
			}
		}
	}
}
```

---

## 作者：ZBAA_MKC (赞：4)

### 前言

这是银组的第一道题，个人感觉难度是不小的，应该是黄~绿题的难度

### 思路分析

这题写起来代码不算复杂，但难在思维，我写了一个多小时，然后突(jiao)然(lian)想(ti)到(xing)这题要用 Floyd 来做。

一开始我是按照两两换来做的（那会没用 Floyd）但是实际上会出现 $1$ 和 $2$ 换，$2$ 和 $3$ 换，$3$ 和 $1$ 换，然后都不比原来更差的情况。看到这里，你也许会发现：如果若干个点在同一个环上（两个点也可以），那他们就可以互相交换。

那么问题又来了，我们该怎么建图呢？

考虑每一个点，把当前的每点和他想换到的点连一条**有向边**，也就是把他当前的礼物和想要换的更好的礼物连起来。

样例建出的图如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/q06v5s9p.png)

如何判断几个点是否在环中呢？

因为我们建的是有向图，所以会简单一些。考虑 Floyd 求传递闭包，如果一个礼物可以到达这个奶牛原本得到的礼物，而且当前奶牛更喜欢这个礼物，那就答案+1，否则就继续，如果走到他原本得到的礼物就结束当前循环，去统计下一个奶牛。

时间复杂度为 $O(n^3)$，本题数据 $n \le 500$，可以通过。

### 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;

int a[505][505];
int pos[505];
int gift[505];
int g[505][505];

int main()
{
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			cin >> a[i][j];
			if (a[i][j] == i)
			{
				pos[i] = j;
			}
		}
		for (int j = 1; j <= pos[i]; j++)
		{
			g[i][a[i][j]] = 1;
		}
		gift[i] = i;
	}
	for (int k = 1; k <= n; k++)
	{
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				g[i][j] |= (g[i][k] && g[k][j]);
			}
		}
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j < pos[i]; j++)
		{
			if (g[a[i][j]][i])
			{
				gift[i] = a[i][j];
				break;
			}
		}
	}
	for (int i = 1; i <= n; i++)
	{
		cout << gift[i] << endl;
	}
	return 0;
}
```

---

## 作者：5ab_juruo (赞：4)

讲一个跑得飞快的 $\mathcal{O}(n^2)$ 做法。

考虑建立如下图：

- 每个奶牛的每一偏好都是一个节点；
- 每个奶牛的第 $i+1$ 偏好向第 $i$ 偏好连边；
- 对于每一偏好，向当前拥有该礼物的奶牛的对应偏好连边。

在该图上跑 Tarjan，对于每一奶牛，从第一偏好开始枚举，第一个在大小超过 $1$ 的 SCC 的偏好就是能拥有的最好礼物。

感性理解正确性大概就是每个 SCC 都会像几个环套起来，然后能换掉的一定构成一个环。

```cpp
/* name: 2022FebS_A
 * author: 5ab
 * created at: 22-02-27 08:33
 */
#include <iostream>
#include <cstring>
using namespace std;

typedef long long ll;
const int max_n = 500, max_nd = (max_n * max_n);

int t[max_n][max_n], tp[max_n], hd[max_nd], des[max_nd<<1], nxt[max_nd<<1], e_cnt = 0, n;
int dfn[max_nd], low[max_nd], stk[max_nd], bel[max_nd], siz[max_nd], ind = 0, stp = 0, s_cnt = 0;
bool inst[max_nd];

inline int mk(int i, int j) { return i * n + j; }
void add(int s, int t)
{
	des[e_cnt] = t;
	nxt[e_cnt] = hd[s];
	hd[s] = e_cnt++;
}

inline void chmin(int& a, int b) { if (a > b) a = b; }
void tarjan(int id)
{
	dfn[id] = low[id] = ind++;
	stk[stp++] = id, inst[id] = true;
	
	for (int p = hd[id]; p != -1; p = nxt[p])
	{
		if (dfn[des[p]] == -1)
		{
			tarjan(des[p]);
			chmin(low[id], low[des[p]]);
		}
		else if (inst[des[p]])
			chmin(low[id], dfn[des[p]]);
	}
	
	if (low[id] == dfn[id])
	{
		int tmp, lst = stp;
		do {
			tmp = stk[--stp];
			inst[tmp] = false;
			bel[tmp] = s_cnt;
		} while (tmp != id);
		siz[s_cnt++] = lst - stp;
	}
}

signed main()
{
	memset(hd, -1, sizeof hd);
	memset(dfn, -1, sizeof dfn);
	memset(bel, -1, sizeof bel);
	
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	cin >> n;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			cin >> t[i][j], t[i][j]--;
			if (t[i][j] == i)
				tp[i] = j;
		}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			add(mk(i, j), mk(t[i][j], tp[t[i][j]]));
		for (int j = 1; j < n; j++)
			add(mk(i, j), mk(i, j-1));
	}
	
	for (int i = 0; i < n * n; i++)
		if (dfn[i] == -1)
			tarjan(i);

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (t[i][j] == i || siz[bel[mk(i,j)]] > 1)
			{
				cout << t[i][j] + 1 << endl;
				break;
			}
	
	return 0;
}
/*
4
1 2 3 4
2 3 4 1
3 4 1 2
4 1 2 3
*/
```

---

## 作者：ForeverCC (赞：2)

### 题意：

第 $i$ 头牛初始拿到了第 $i$ 号礼物，给你每头牛对不同礼物的喜爱程度的排序，可以交换礼物，求每头牛能拿到的最喜欢的礼物。

### 解析：

如果对于第 $j$ 头牛的礼物 $j$，第 $i$ 头牛更喜欢，那么就建一条从 $i$ 到 $j$ 的边。然后从节点 $i$ 搜索（$i$ 从 $1$ 到 $n$），能遍历到的点的下标就为牛 $i$ 能换到的礼物的下标，最小的下标所对应的礼物即为能换到的最喜欢的礼物。

### 代码：

```cpp
#include<bits/stdc++.h>
#define N 505
using namespace std;
int n,a[N][N],id[N][N],ans[N],vis[N];
vector<int> e[N];
void dfs(int u){
    vis[u]=1;
    for (int v:e[u]) 
		if(!vis[v]) 
			dfs(v);
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++) 
		for(int j=1;j<=n;j++) 
			scanf("%d",&a[i][j]),
			id[i][a[i][j]]=j;//表示第i头牛对礼物a[i][j]的喜爱值为j。（喜爱值越小越喜欢） 
    for(int i=1;i<=n;i++) 
		for(int j=1;j<=n;j++) 
			if(id[j][i]<id[j][j]) 
				e[i].push_back(j); 
    for(int i=1;i<=n;i++) {
        memset(vis,0,sizeof(vis));
        dfs(i);
        for(int j=1;j<=n;j++)
			if(vis[a[i][j]]){ 
				ans[i]=a[i][j];
				break;
			}
    }
    for(int i=1;i<=n;i++)
		printf("%d\n",ans[i]);
    return 0;
}
```


---

## 作者：_yi_ (赞：1)

# 题意简述

题目描述的是农夫约翰有 $N$ 个标记为 $1 \dotsm N$ 的礼物，要分给 $N$ 头同样标记为 $1 \dotsm N$ 的奶牛。每头奶牛都有一个愿望单，是一个 $1 \dotsm N$ 的排列，表示奶牛对礼物的偏好顺序，越早出现的礼物越喜欢。农夫约翰懒惰地将 $i$ 号礼物直接分配给了 $i$ 号奶牛。现在奶牛们决定重新分配礼物，使得每头奶牛都能得到原礼物或更喜欢的礼物。要求计算对于每个 $i$（$1 \le i \le N$），重新分配后 $i$ 号奶牛可能得到的最好的礼物。

# 解题思路

不难想到建图，每个奶牛和可以得到的礼物连边。

考虑贪心，对于每个奶牛 $i$ 依次枚举礼物 $a _ {i,j}$，判断剩下的奶牛和礼物能不能分配成功。显然，分配成功的充要条件是剩余的奶牛和礼物是二分图的完美匹配。时间复杂度 $O(n^5)$。

注意到，使用匈牙利算法匹配左部点 $i$ 时，会依次枚举每一条与之相连的边并检查对应的右部点 $j$ 是否能和 $i$ 形成匹配，这本质上就是一个贪心的过程。所以，对于每个奶牛 $i$，只需连边时按喜欢程度从大到小依次连边，在匹配所有奶牛和礼物时最后一个匹配这个奶牛 $i$，就可以在匈牙利算法中完成贪心。时间复杂度 $O(n^4)$。

考虑优化，不难发现若对每个奶牛 $i$ 都跑一个二分图匹配，会有很多重复计算。不妨先把整个图先匹配好，枚举到奶牛 $i$ 时再将 $i$ 所对应的匹配删除，对其重新匹配。时间复杂度降为 $O(n^3)$，可以通过本题。

>显然，该二分图必然存在完美匹配，因为将所有奶牛 $i$ 和礼物 $i$ 匹配就是完美匹配。

# 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=500;
vector<int> edge[N+2];
int p[N+2],q[N+2];
bool vis[N+2];
bool match(int x){
    for(int i:edge[x]) if(!vis[i]){
        vis[i]=1;
        if(p[i]==0||match(p[i])){
            p[i]=x;
            q[x]=i;
            return 1;
        }
    }
    return 0;
}
int main(){
    // freopen("data.in","r",stdin);
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        bool flag=1;
        for(int j=1;j<=n;j++){
            int x;
            cin>>x;
            if(flag){
                edge[i].push_back(x);
            }
            if(x==i){
                flag=0;
            }
        }
    }
    //二分图匹配？
    for(int i=1;i<=n;i++){
        memset(vis,0,sizeof vis);
        match(i);
    }
    for(int i=1;i<=n;i++){
        q[i]=p[q[i]]=0;
        memset(vis,0,sizeof vis);
        match(i);
        cout<<q[i]<<"\n";
    }
    // cout<<"\n";
    return 0;
}
```

---

## 作者：蒻蒟IOOI蒟蒻 (赞：1)

## Description
共有 $n$ 头奶牛来分 $n$ 个礼物，一开始时第 $i$ 头奶牛得到第 $i$ 个礼物。

每个牛有自己的礼物偏好列表，$a_{i,j}$ 表示第 $i$ 头牛的第 $j$ 喜欢的礼物的编号。

然后进行一次重新分配，使得每头牛得到的礼物都不劣于之前的礼物。在所有方案中，问每头牛可能得到的最优的礼物是什么。

数据范围：$n \le 500$

## Analysis
我们定义 $dp_{i,j}$ 为第 $i$ 头牛和第 $j$ 头奶牛交换礼物后，第 $j$ 头牛是否能够通过保留第 $i$ 个礼物或和别的奶牛交换礼物来保证自己得到的不劣于重新分配之前的礼物，注意不能让礼物的交换关系形成环。 

我们通过记忆化搜索来处理 $dp_{i,j}$ 的值，然后我们扫描第 $i$ 头牛第 $j$ 喜欢的礼物，输出第一个 $dp_{a_{i,j}, i}$ 值为真的礼物。

于是我们就愉快地通过了本题。

## Code
```cpp
#include <iostream>
#include <cstring>
using namespace std;
#define int long long
const int N = 505;
int n, a[N][N], b[N][N], dp[N][N];
int f(int x, int y) {
    if (dp[x][y] >= 0) return dp[x][y];
    if (b[x][y] <= b[x][x]) return dp[x][y] = true;
    dp[x][y] = 0;
    for (int i = 1; i < b[x][x]; i++) {
        if (a[x][i] != x && f(a[x][i], y)) return dp[x][y] = true; 
    } 
    return dp[x][y] = false;
}
signed main() {
    cin >> n;
    memset(dp, -1, sizeof(dp));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
            b[i][a[i][j]] = j;
        }   
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= b[i][i]; j++) {
            if (f(a[i][j], i)) {
                cout << a[i][j] << endl; 
                break;
            }
        }
    }
    return 0;
}
```

---

## 作者：PassName (赞：1)

# P8186 题解

[题目传送门 P8186](https://www.luogu.com.cn/problem/P8186)

## 题目分析
此题可以用动态规划做。我们用 `dp[i][j]` 来表示除了小麦 `i` 和奶牛 `j`。

分析时匹配的小麦集中任意一个小麦，可以在奶牛集中找到能吃它的。当然，也可以反过来，得到匹配是指，匹配的奶牛集中任意一个奶牛，可以在奶牛小麦集中找到能被吃的。

然后进行三种不同的特判情况:

- 奶牛可以吃到小麦；

- 不在 $j$ 中且奶牛可以吃小麦 $k$；

- 奶牛可以和小麦匹配；

求完每个 `ans[mask]` 时，更新对应的 dp 状态。

## 代码实现思路
输入 $n$，再通过一个循环嵌套来输入 $x$，在此过程中，加一个 $flag$ 进行特判，每一维循环中只有一个 `g[i]` 可以存储所有奶牛 $i$ ，可以吃的小麦数。输入操作结束后进行初始化操作。随后三次循环嵌套，先过滤不在当前集合的奶牛，然后再套一个循环，进行上面所述的特判，计算完 `ans` 更新 dp。

---

## 作者：滑蒻稽 (赞：1)

## Des

有 $n$ 个礼物分给 $n$ 头奶牛。最开始是把第 $i$ 号礼物分给了第 $i$ 号奶牛。

每头奶牛有一个偏好列表。表示了想要的礼物的排名。可以任意重排礼物的分配方式，使得每头奶牛拿到的礼物在该奶牛的偏好列表里的排名不低于最开始拿到的礼物的排名。

问每头奶牛**可能**拿到的排名最高的礼物是什么。

$n\le 500$。

## Sol

考虑对于每头奶牛 BFS 拓展能拿到的礼物。每次用队首的礼物去尝试交换其他牛的，如果可以交换并且没有拿到过那头牛的礼物，就存进队列里。

交换给对方的礼物必须满足对方的要求（不低于初始的排名），但自己拿到的礼物可以暂时不满足要求。

可以证明一种合法的安排礼物的方式必然能由上面的过程得到，所以这个做法是对的。

时间复杂度 $O(n^3)$。

## My Code

```cpp
#include <bits/stdc++.h>

using namespace std;
const int N = 505;
int n, a[N][N], rk[N][N];
bitset<N> ok[N];
queue<int> q;

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	cin >> n;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			cin >> a[i][j], rk[i][a[i][j]] = j;
	for(int i = 1; i <= n; i++) {
		ok[i][i] = true, q.push(i);
		while(!q.empty()) {
			int u = q.front();
			q.pop();
			for(int j = 1; j <= n; j++) {
				if(!ok[i][j] && rk[j][u] <= rk[j][j]) {
					ok[i][j] = true;
					q.push(j);
				}
			}
		}
		int ans = n + 1;
		for(int j = 1; j <= n; j++)
			if(ok[i][j] && rk[i][j] < ans) ans = rk[i][j];
		cout << a[i][ans] << '\n';
	}

	return 0;
}
```

---

## 作者：liuxy1234 (赞：0)

初始情况下，每头奶牛匹配一个礼物，所以我们把奶牛和礼物当作一个点。

对于每只奶牛，我们可以将它与它想换的礼物连一条有向边。

如果奶牛 $i$ 和奶牛 $j$ （$i$ 向 $j$ 连单向边）在一个环上，那么他们就可以互相交换礼物。

因此我们这个图就建出来了，在这里我用的是邻接矩阵来存的，找一组解只需要跑一遍传递闭包即可 ( $\text{dfs} $ 也行 )，时间复杂度 $O(n^3)$ ，$n \le 500$，肯定能过。

接下来不多说了，直接上代码。

```cpp
#include <bits/stdc++.h>
using namespace std;

int a[510][510];
int p[510];
int g[510];
int f[510][510];

int main()
{
	int n;
	cin >> n;
	for (int i = 1;i <= n;i++)
	{
		for (int j = 1;j <= n;j++)
		{
			cin >> a[i][j];
			if (a[i][j] == i)
			{
				p[i] = j;
			}
		}
		for (int j = 1;j <= p[i];j++)
		{
			f[i][a[i][j]] = 1
		}
		g[i] = i;
	}
	for (int k = 1;k <= n;k++)
	{
		for (int i = 1;i <= n;i++)
		{
			for (int j = 1;j <= n;j++)
			{
				f[i][j] |= (f[i][k] && f[k][j]);
			}
		}
	}
	for (int i = 1;i <= n;i++)
	{
		for (int j = 1;j < p[i];j++)
		{
			if (f[a[i][j]][i])
			{
				g[i] = a[i][j];
				break;
			}
		}
	}
	for (int i = 1;i <= n;i++)
	{
		cout << g[i] << endl;
	}
	return 0;
}
```


---

