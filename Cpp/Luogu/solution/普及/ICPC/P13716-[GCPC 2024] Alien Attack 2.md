# [GCPC 2024] Alien Attack 2

## 题目描述

外星人正在造访地球，像往常一样，他们计划绑架人类进行实验。
在过去，外星人绑架事件在地球上引起了大量媒体报道和疯狂猜测。
幸运的是，大多数人并不相信这些故事，认为外星人并不真实存在。

:::align{center}
![](https://upload.wikimedia.org/wikipedia/commons/0/0d/Rocket_USA_Battery_Operated_Tin_UFO_Mars_Explorer_Close_Up.jpg)

银河系人员捕获委员会（GCPC）代表。

图片作者：D J Shin，来源于 [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Rocket_USA_Battery_Operated_Tin_UFO_Mars_Explorer_Close_Up.jpg)

:::

为了将来保持低调，银河系人员捕获委员会（GCPC）为绑架行为制定了规则。
除了大量繁琐的文书工作，外星人还必须仔细准备绑架计划。
虽然他们可以进行多次往返（实际上，外星旅行速度极快，这根本不是限制），
但他们必须足够聪明，以免让人类发现他们的秘密。如果外星人想要绑架某个人，
他们必须同时绑架这个人的所有朋友，这样当朋友们想要聚会时，就不会发现有人失踪。
当然，地球上的友谊是双向的，也就是说，如果 Alice 是 Bob 的朋友，那么 Bob 也是 Alice 的朋友。

在准备行动时，外星人已经观察了他们的目标，并记录下了所有的友谊关系。
总共，他们必须绑架 $n$ 个人，包括他们的朋友。
现在，他们想在本地经销商处预订一艘星际飞船，并想知道需要多大的空间才能一次性绑架所有 $n$ 个人。
一艘星际飞船的储存空间以能同时运输的人数来衡量。
要绑架所有 $n$ 个人，所需的最小储存空间是多少？

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5 3
1 2
2 3
4 5```

### 输出

```
3```

## 样例 #2

### 输入

```
3 0```

### 输出

```
1```

## 样例 #3

### 输入

```
8 8
1 2
2 3
3 4
1 4
1 5
2 6
3 7
4 8```

### 输出

```
8```

# 题解

## 作者：_____Elysia_____ (赞：2)

~~P13716 之前是小粉兔用来测试的题号来着。~~
### 题目描述
外星人想要抓 $n$ 个人，抓一个人的时候必须同时抓其所有的朋友。现在给定 $n$ 个人和 $m$ 条朋友关系（朋友关系是双向的），求外星人至少需要能容下多少人的飞船才能完成任务。
### 题意转换
给定一个 $n$ 点 $m$ 边的无向图，求最大连通块的大小。
### 思路
可以使用并查集做这道题。每次连边的时候，如果两个点不在一个集合，把两个点所在的集合合并到一个集合，新集合的大小为原来两个集合大小相加的结果。时间复杂度 $O(n \alpha(n))$。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int fa[200005],siz[200005];
int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}
int main(){
    int n,m,ans=0;
    cin>>n>>m;
    for(int i=1;i<=n;i++)fa[i]=i,siz[i]=1;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        int fu=find(u),fv=find(v);
        if(fu!=fv){
            fa[fu]=fv;
            siz[fv]+=siz[fu];
            siz[fu]=0;
        }
    }
    for(int i=1;i<=n;i++)ans=max(ans,siz[i]);
    cout<<ans;
}
```

---

## 作者：FrankShix (赞：1)

## 题意
给定一张无向图，求最大连通块大小。

## Solution
并查集维护即可，每次累加连通块大小并合并。要注意一定要在原祖先上累加合并，因为可能会加重。

代码里有注释。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;

int n, m, fa[(int)2e5 + 5], ans = -INT_MAX, siz[(int)2e5 + 5];

int findd(int x) { // 查
	if (fa[x] != x) 
		fa[x] = findd(fa[x]);
	return fa[x];
}

void uni(int x, int y) { // 并
	fa[y] = x;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> n >> m;
	if (!m)  // 特判 m == 0
		return cout << 1, 0;
	for (int i = 1; i <= n; ++i) // 并查集初始化
		fa[i] = i, siz[i] = 1;
	for (int i = 1; i <= m; ++i) {
		int x, y;
		cin >> x >> y;
		int r1 = findd(x), r2 = findd(y); // 一定要在原祖先上累加合并，因为可能会加重
		if (r1 == r2) // 如果已经在同一个连通块里就 continue
			continue;
		uni(r1, r2);
		siz[r1] += siz[r2]; // 累加连通块大小
		ans = max(ans, siz[r1]); // 统计答案
	}
	cout << ans;
    return 0;
}

```

---

## 作者：Fine_Dust_Z (赞：1)

#### 本片题解适合完全不了解并查集的人食用。
### 题目大意
给出 $N$ 个点 $M$ 个边的无向图，问这个无向图中最多有多少个节点是连通的。
### 思路
并查集模板题，我们在进行并的时候计算并查集的大小即可。
#### 并查集
并查集是一种数据结构。

它包括初始化、合并、查找、统计。
##### 初始化
并查集最开始所有节点都是独立的所以 $Fa_i=i$。
##### 合并
当有一条边将 $Fa_i$ 和 $Fa_j$ 两个点相连便让 $Fa_i=Fa_j$。
##### 查找
当询问 $Fa_i$ 与 $Fa_j$ 是否存在路径可以到达。

我们可以查询 $Fa_i$ 和 $Fa_j$ 是否存在公共祖先。
##### 统计
统计的应用范围很广，如：在最小生成树 **Kruskal** 算法中来判断是否存在生成树。

也可以解决本题。

接下来我们来看代码。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
template<typename T>inline void read(T&x) {
	char c;
	int sgin = 1;
	x = 0;
	do {
		c = getchar();
		if (c == '-')sgin = -1;
	} while (!isdigit(c));
	do {
		x = x * 10 + (c - '0');
		c = getchar();
	} while (isdigit(c));
	x *= sgin;
}
int fa[200010],size[200010],n,m,ans;
inline int find(int x){//查
	return fa[x]==x?x:fa[x]=find(fa[x]);
//路径压缩：每次在查询祖先时将所有节点指向根节点
}
inline void make_bcj(){
	for(int i=1;i<=n;i++){
		fa[i]=i;
		size[i]=1;
	}
//初始化：所有节点初始都是根节点，大小都为1
	ans=1;//载人量最小为1
}
inline void marge(int x,int y){//并
	x=find(x);
	y=find(y);
//查询两个节点的根节点
	if(x!=y){//如果根节点不同进行“并”(x并y)的操作
		fa[x]=fa[y];//集
		size[y]+=size[x];//更新大小
		ans=max(ans,size[y]);//更新最大大小
		size[x]=0;//删去并查集x的大小
	}
}
int main() {
	read(n);
	read(m);
	make_bcj();
	while(m--){
		int x,y;
		read(x);
		read(y);
		marge(x,y);
	}
	printf("%d",ans);
	return 0;
}

```

---

## 作者：huhengrui2013 (赞：1)

### 题解：P13716 [GCPC 2024] Alien Attack 2

[传送门](https://www.luogu.com.cn/problem/P13716)

### 思路：

题目给出每条边，让我们求出最大连通块的大小。考虑用并查集维护每个联通块，合并的同时也将连通块大小相加，最后循环求最大值即可。

### AC Code:

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N=2e5+10;
int fa[N],son[N];
int get(int x){
    if(x==fa[x]) return x;
    return fa[x]=get(fa[x]);
}
int main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++) fa[i]=i,son[i]=1;
    for(int i=1;i<=m;i++){
        int x,y;
        cin>>x>>y;
        int fx=get(x),fy=get(y);
        if(fx!=fy){
            fa[fy]=fx;
            son[fx]+=son[fy];
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++) ans=max(ans,son[i]);
    cout<<ans;
}
```

---

## 作者：SegmentSplay (赞：1)

# 题意简述

题面很有意思，但说的不是特别清楚。

一共有 $n$ 个人需要绑架，同时有 $m$ 条朋友关系，绑走一个人的同时要把和他（她）有朋友关系的人都绑走，可以绑架多次，问绑走的人最多的一次最少绑走几个人。

# 解题思路

首先，可以把题目里的朋友关系抽象成一张有 $n$ 个点，$m$ 条边的无向图。

然后是一个显而易见的贪心思路：每一次一定是绑走一个人和他所有朋友，不抓其他人，才能保证人数最小。

好的，根据题目给出的 $m$ 条朋友关系，可以推断出一个人和他（她）的所有朋友肯定在图上的一个联通块中。

那么就得到了解题思路：找出图中所有连通块，算出每个联通块的大小，找出最大的一个。

# 具体实现

找联通块有 2 种方式：DFS 和并查集，这里采用并查集实现，在判断连通块的同时计算连通块大小。

（并查集判连通块做法：合并每条边的两个端点，两个点在同一集合中就是在一个连通块中）

其实就是并查集中的按秩合并优化，它依靠记录集合大小，让小的集合合并到大的里面以优化时间复杂度。

时间复杂度 $O(m \alpha(n))$，其中 $\alpha(n)$ 可以看作常数。

（$\alpha(n)$ 是反阿克曼函数，对于 $n \leq 10^{2^{10^{19279}}}$，有 $\alpha(n) \leq 5$）

#  AC Code

::::info[Talk is cheap,show you my code!（点击可收起）]{open}
```cpp
#include<bits/stdc++.h>
using namespace std;
int f[200005];
int sz[200005];
int find(int x)
{
	if(f[x]==x)
	{
		return f[x];
	}
	return f[x]=find(f[x]);
}
void merge(int x,int y)
{
	if(find(x)==find(y))
	{
		return;
	}
	x=find(x);
	y=find(y);
	if(sz[y]<sz[x])
	{
		swap(x,y);
	}
	sz[y]+=sz[x];
	sz[x]=0;
	f[x]=y;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n,m;
	int ans=0;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		f[i]=i;
		sz[i]=1;
	}
	for(int i=1;i<=m;i++)
	{
		int u,v;
		cin>>u>>v;
		merge(u,v);
	}
	for(int i=1;i<=n;i++)
	{
		ans=max(ans,sz[find(i)]);
	}
	cout<<ans;
	return 0;
}
```
::::

::::warning[请不要抄袭题解代码]
请不要抄袭谢谢
::::

---

## 作者：zhouxiaodong (赞：1)

# 思路
较为标准的并查集，有点像 [P1196 [NOI2002] 银河英雄传说](https://www.luogu.com.cn/problem/P1196)。

把关系图画成森林，最大的那棵树的节点数就是答案，因为要绑架的最大数量就是需要求的最少容量。
# WA Code
```cpp lines=38-40
#include<bits/stdc++.h>
#define int /*unsigned*/ long long
using namespace std;
int n,m,a[200010],ans,cnt[200010];
int find(int g)
{
	if(a[g]==g)
	{
		return g;
	}
	else
	{
		return a[g]=find(a[g]);
	}
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	if(m==0)//样例 2，特判优化
	{
		cout<<1;
		return 0;
	}
	for(int i=1;i<=n;i++)//初始化
	{
		a[i]=i;
		cnt[i]=1;
	}
	for(int i=1;i<=m;i++)
	{
		int x,y;
		cin>>x>>y;
		if(find(x)!=find(y))
		{
			a[find(y)]=find(x);
			cnt[find(x)]+=cnt[find(y)];
			ans=max(ans,cnt[find(x)]);
		}
	}
	cout<<ans;
	return 0;
}
```
这份代码是作者走过的坑，在加重区块的第一行，我们把 $y$ 的祖宗指向了 $x$ 的祖宗，第二行又累加了 $y$ 的祖宗的数量。

本来应该是 $x$ 和 $y$ 的祖宗的数量，但 $x$ 的祖宗已经是 $y$ 的祖宗了，导致会累加成 $2x$，从而答案错误。

第三行选了错误的数量，故而无法 AC。
# AC Code
```cpp lines=39-41,36-36
#include<bits/stdc++.h>
#define int /*unsigned*/ long long
using namespace std;
int n,m,a[200010],ans,cnt[200010];
int find(int g)
{
	if(a[g]==g)
	{
		return g;
	}
	else
	{
		return a[g]=find(a[g]);
	}
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	if(m==0)
	{
		cout<<1;
		return 0;
	}
	for(int i=1;i<=n;i++)
	{
		a[i]=i;
		cnt[i]=1;
	}
	for(int i=1;i<=m;i++)
	{
		int x,y;
		cin>>x>>y;
		int rx=find(x),ry=find(y);//记录祖宗
		if(rx!=ry)
		{
			a[ry]=rx;
			cnt[rx]+=cnt[ry];//在原祖宗上累加！
			ans=max(ans,cnt[rx]);
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：IkillDream (赞：1)

# P13716 题解

## 思路

首先我们可以使用并查集维护朋友关系的连通分量，然后合并输入的所有朋友关系，同时记录每个连通分量的大小，最后只需要找出所有连通分量中的最大大小即为答案 qwq。

## [AC](https://www.luogu.com.cn/record/231989299) 代码

```c++
#include <bits/stdc++.h>
using namespace std;
int fa[200005],rk[200005],sz[200005];
int main(){
    int n,m;scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)fa[i]=i,sz[i]=1;
    while(m--){
        int u,v;scanf("%d%d",&u,&v);
        int fu=u,fv=v;
        while(fu!=fa[fu])fu=fa[fu];
        while(fv!=fa[fv])fv=fa[fv];
        if(fu==fv)continue;
        if(rk[fu]<rk[fv])swap(fu,fv);
        fa[fv]=fu;
        sz[fu]+=sz[fv];
        if(rk[fu]==rk[fv])rk[fu]++;
    }
    int ans=0;
    for(int i=1;i<=n;i++)if(fa[i]==i&&sz[i]>ans)ans=sz[i];
    printf("%d",ans);
    return 0;
}
```

--------------

这里有个新知识 “`scanf`”，在你知道了时间复杂度的时候应该知道了输入输出也要消耗时间，比如 `cin,cout`，但是这里的 “`scanf`” 是不需要消耗时间的，同样的有不消耗时间的输入那应该也有不消耗时间的输出啊，没错，的确有 `printf`，相信大多数人都做过[这题](https://www.luogu.com.cn/problem/B2004)，这题其实有点恶心，相信大多数人看到后都会向我一样：

```c++
#include<bits/stdc++.h>
using namespace std;
int main(){
    int a,b,c;
    cin>>a>>b>>c;
    cout<<a<<"        "<<b<<"        "<<c;
    return 0;
}
```

结果就将[如下](https://www.luogu.com.cn/record/231992936)，全 WA，为什么呢，因为普通 `cout` 输出不会自动控制输出宽度，所以只能让我们自己来控制输出的空格比如 `setw()` 或 `printf()` 这样就能实现多重空格输出，好了讲完了，如果你觉的 `printf()` 和 `scanf()` 打起来太麻烦的话可以在代码前面加两行：

```c++
ios::sync_with_stdio(false);
cin.tie(0);
```

这样就好了。

## 后记

题解制作不容易如果觉得我的题解写的好的话可以点个赞吗 qwq。

题解可以抄，但是你要学会哦！

祝大家 CSP-J/S 初赛，会的都对，蒙的全对。

---

## 作者：Bill_luogu (赞：0)

## 题目思路：
用并查集表示朋友关系，最后统计每个点是多少个节点的祖先的数量的最大值。
## 过程：
1.将 $fa_{i}$ 初始化为 $i$；

2.每输入一对 $i,j$ 就分别找 $i$ 和 $j$ 的最远祖先，把 $i$ 的最远祖先赋值为 $j$ 的最远祖先，即 $fa_{f(x)}\gets f(y)$，其中 $f(x)$ 表示找 $x$ 的祖先；

3.答案为 $fa_i$ 出现次数最多是多少次。
## AC Code：

```cpp lines=17-17,19-22 line-numbers
#include<iostream>
using namespace std;
int n,m;
int fa[200010],sum[200010],ans;
int find(int x)
{
    return fa[x]==x?x:fa[x]=find(fa[x]);
}
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        fa[i]=i;
    for(int i=1,x,y;i<=m;i++)
    {
        cin>>x>>y;
        fa[find(x)]=find(y);//合并
    }
    //统计答案
    for(int i=1;i<=n;i++)
        fa[i]=find(fa[i]),sum[fa[i]]++;
    for(int i=1;i<=n;i++)
        ans=max(ans,sum[i]);
    cout<<ans;
    return 0;
}
```
**双倍经验：[UVA10608 Friends](https://www.luogu.com.cn/problem/UVA10608)**

---

## 作者：AnOIer (赞：0)

比较板的并查集。

答案就是结点数最多的联通块的结点数量。

我们令 $siz[i]$ 为结点 $i$ 的联通块的结点数量。在将两个联通块合并时，把两个联通块的祖宗 $r_1,r_2$ 对应的 $siz[r_1],siz[r_2]$ 相加。

此外要特别注意一个坑点，合并 $u,v$ 时如果它们**联通块的祖宗是一样的就不要合并**，否则会多算一遍。

```cpp
#include<bits/stdc++.h>
using namespace std;
int fa[200010];
int find(int x) {
	if(fa[x]==x) return x;
	return fa[x]=find(fa[x]);
}
int siz[200010];
void join(int a,int b) {
	int aa=find(a),bb=find(b);
	fa[aa]=bb;
	siz[bb]+=siz[aa];
	siz[aa]+=siz[bb]; //12,13行写一行就行，因为最后遍历点总能找到答案 
}
int main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++) {
		fa[i]=i;
		siz[i]=1;
	}
	for(int i=1;i<=m;i++) {
		int u,v;
		cin>>u>>v;
		if(find(u)!=find(v)) join(u,v);
	} 
	int ans=-1;
	for(int i=1;i<=n;i++) {
		ans=max(ans,siz[find(i)]);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Crazyouth (赞：0)

## 分析

题意就是求出最大连通块大小，虽然 dfs 也不是不行，但这里使用了码量相对较小的并查集做法。考虑在普通并查集的基础上，多开一个数组维护每个集的大小，在合并的时候跟着加上，就能统计出每个连通块的大小，最后再一起取 $\max$ 就做完了。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int sz[200010],fa[200010];
int find(int x)
{
	if(x==fa[x]) return x;
	fa[x]=find(fa[x]);
	return fa[x];
}
int main()
{
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++) fa[i]=i,sz[i]=1;
	while(m--)
	{
		int u,v;
		cin>>u>>v;
        if(find(u)==find(v)) continue;
		sz[find(v)]+=sz[find(u)];
		fa[find(u)]=find(v);
	}
	int ans=0;
	for(int i=1;i<=n;i++) ans=max(ans,sz[find(i)]);
    cout<<ans;
}

---

