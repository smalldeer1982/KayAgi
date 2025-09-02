# [USACO11DEC] Simplifying the Farm G

## 题目描述

Farmer John has been taking an evening algorithms course at his local university, and he has just learned about minimum spanning trees.  However, Farmer John now realizes that the design of his farm is not as efficient as it could be, and he wants to simplify the layout of his farm.

The farm is currently arranged like a graph, with vertices representing fields and edges representing pathways between these fields, each having an associated length.  Farmer John notes that for each distinct length, at most three pathways on his farm share this length.  FJ would like to remove some of the pathways on his farm so that it becomes a tree -- that is, so that there is one unique route between any pair of fields.  Moreover, Farmer John would like this to be a minimum spanning tree -- a tree having the smallest possible sum of edge lengths.

Help Farmer John compute not only the sum of edge lengths in a minimum spanning tree derived from his farm graph, but also the number of different possible minimum spanning trees he can create.

农夫约翰在一所夜校学习算法课程，他刚刚学会了最小生成树。现在约翰意识到他的农场设计得不够高效，他想简化农场的布局。


约翰的农场可以看做一个图，农田代表图中顶点，田间小路代表图中的边，每条边有一定的长度。约翰注意到，农场中最多有三条小路有着相同的长度。约翰想删除一些小路使得农场成为一棵树，使得两块农田间只有一条路径。但是约翰想把农场设计成最小生成树，也就是农场道路的总长度最短。


请帮助约翰找出最小生成树的总长度，同时请计算出总共有多少种最小生成树？


## 说明/提示

Picking both edges with length 1 and any edge with length 2 yields a minimum spanning tree of length 4.



## 样例 #1

### 输入

```
4 5 
1 2 1 
3 4 1 
1 3 2 
1 4 2 
2 3 2 
```

### 输出

```
4 3 
```

# 题解

## 作者：ShuYuMo (赞：7)

# 思路

如果没有边权相同的边，那么其实时不存在多种最小生成树的方案的。

题目中同一边权的个数不超过三个

按照`Kruskal`的建树流程进行模拟。

边权排完序后，边权相同的会聚到一起，然后在从小到大枚举的时候分类讨论即可。

# 流程
首先找到边权相同到的几条边。

这是我们需要在这些边中选出有用边。

所谓有用边就是加入其中一条边，不会产生环。因为之前已经加入的边是不能再反悔的，所以如果当前等待加入的边与之前的边存在矛盾的话，当前边一定是无用的。
如下图，下图的橙色边就是无用边：
 ![1](https://s2.ax1x.com/2019/08/04/eyiZRO.png)

然后我们考虑哪些情况会使最小生成树方案增加：
 - 如过当前权值有两条边相同：
 就有这两种情况：
   - ![2](https://s2.ax1x.com/2019/08/04/eyAsYt.png)
   - ![2](https://s2.ax1x.com/2019/08/04/eyATf0.png)
 对于第一种情况，这两条边只能同时加入其中任意一条，这样就有两种建树方案。
 对于第二种情况，这两条边没有选择余地，必须都加入。

 - 如过当前权值有三条边相同：
 以下三种情况能产生多种建树方案：
   - ![eyALXF.png](https://s2.ax1x.com/2019/08/04/eyALXF.png)
   -  ![eyAq6U.png](https://s2.ax1x.com/2019/08/04/eyAq6U.png)
   - ![eyAblT.png](https://s2.ax1x.com/2019/08/04/eyAblT.png)
    这三种情况分别产生$3$（选其中一条不加入），$2$（选重复的两条中的一条），$3$（选三条中的任意一条）种生成树方案。
   

# 代码

使用`set`帮助区分三条边权相同时，第一种情况和第二种情况。

```cpp
/*!
 * FileName: luogu-3037.cpp
 * This Problem is on luogu. The ID of the problem is 3037. 
 * Copyright(c) 2019 Shu_Yu_Mo
 * MIT Licensed
 * Luogu: https://www.luogu.org/space/show?uid=44615
 * Github: https://github.com/oldsuold/
 * Gitee: https://gitee.com/Shu_Yu_Mo/
 * These words were created by an amazing tool on 2019-08-03 22:47:58 written by Shu_Yu_Mo.
 */
#include<cstdio>
#include<cstring>
#include<iostream>
#include<set>
#include<algorithm>
#define inf 0x7fffffff
using namespace std;
const int _M = 1e5 + 100;
const int _N = 4e4 + 100;
const int MOD = 1000000007;
inline int read()
{
    char c = getchar(); int sign = 1; int x = 0;
    while(c > '9' || c < '0') { if(c=='-')sign = -1; c = getchar(); } 
    while(c <= '9' && c >= '0') { x *= 10; x += c - '0'; c = getchar(); }
    return x * sign;
}
struct edges{
	int u;
	int v;
	int w;
	bool operator < (const edges & A) const {
		return w < A.w;
	}
}E[_M];
int n, m;
//Kruskal 所用的并查集   Start
int f[_N];
int find(int x){ return f[x] == x ? x : f[x] = find(f[x]); }
void initForSet()
{
	for(register int i = 1;i <= n;i++)
		f[i] = i;
}
void marge(int x, int y)
{
	x = find(x);
	y = find(y);
	if(x == y) return;
	f[x] = y;
}
bool ask(int x, int y)
{
	return find(x) == find(y);
}
//Kruskal 所用的并查集   End
int nxtIt(int now)//往下找最后一个边权相同的位置
{
	for(register int i = now;i <= m;i++)
		if(E[now].w != E[i].w)
			return i - 1;
	return m;
}
set <pair<int , int >  >  S;//
int main()
{
	n = read(), m = read();
	for(register int i = 1;i <= m;i++)
	{
		E[i].u = read();
		E[i].v = read();
		E[i].w = read(); 
	}
	initForSet();
	sort(E + 1, E + 1 + m);
	int ans1 = 0;
	int ans2 = 1;
	int nxt;
	for(register int i = 1;i <= m;)
	{
		S.clear();
		nxt = nxtIt(i);
		int totEdge = 0;
		for(register int j = i;j <= nxt;j++)
			if(!ask(E[j].u, E[j].v))
			{
				totEdge ++;
				int k1 = min(find(E[j].u), find(E[j].v));
				int k2 = max(find(E[j].u), find(E[j].v));
				S.insert(make_pair(k1, k2));
			}
		int totAdd = 0;
		for(register int j = i;j <= nxt;j++)
		{
			if(!ask(E[j].u, E[j].v))
			{
				marge(E[j].u, E[j].v);
				totAdd ++;
				ans1 = (ans1 + E[j].w) % MOD;
			}
		}
		if(totAdd == 1)
			ans2 = ans2 * 1LL * totEdge % MOD;//分别是两条边权相同时的第一种情况    和    三条边权相同时的第三种情况。
		if(totAdd == 2 && totEdge == 3)
		{
			if(S.size() == 3) ans2 = ans2 * 3LL % MOD;//三条边权相同时的第一种情况
			if(S.size() == 2) ans2 = ans2 * 2LL % MOD; //三条边权相同时的第二种情况
		}
		i = nxt + 1;
	}
	printf("%d %d\n", ans1 % MOD, ans2 % MOD);
    return 0;
}
```


---

## 作者：__233 (赞：4)

# [更好的阅读体验](https://blog.csdn.net/Zbr162/article/details/93785745)

<font size="6"> [$$[USACO11DEC]简化的农场Simplifying\ the\ Farm$$](https://www.luogu.org/problemnew/show/P3037) </font>
___
<font size="6" color=blue> $\mathcal{Description}$ </font>
农夫约翰在一所夜校学习算法课程，他刚刚学会了最小生成树。现在约翰意识到他的农场设计得不够高效，他想简化农场的布局。

约翰的农场可以看做一个图，农田代表图中顶点，田间小路代表图中的边，每条边有一定的长度。约翰注意到，农场中最多有三条小路有着相同的长度。约翰想删除一些小路使得农场成为一棵树，使得两块农田间只有一条路径。但是约翰想把农场设计成最小生成树，也就是农场道路的总长度最短。

请帮助约翰找出最小生成树的总长度，同时请计算出总共有多少种最小生成树？
___
<font size="6" coloen_arrow> $\mathcal{Solution}$ </font><br/>

<font color=white size="5"> $最初想法$ </font>

___
<font color=red size="5"> $正解部分$ </font>
按照 $Kruskal$ 构造最小生成树, 
由于题目中给出 $"最多有三条小路有着相同的长度"$ 的条件,
所以遇到 **不同** 的边有 **相同** 的边权时, 列举出所有加边时的情况进行分析 $↓$
第一张图为 $2$ 条边边权相同的情况, 第二张图为 $3$ 条.

![](https://img-blog.csdnimg.cn/20190627213957500.PNG)

$上图中 \ I.情况有2种选择,其余皆无选择余地.$

![](https://img-blog.csdnimg.cn/20190627214005161.PNG?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1picjE2Mg==,size_16,color_FFFFFF,t_70)

$上图中只有III, VI , IV, VII, 三个情况有选择余地,  \\
III有\ 2\ 种选择, \\
VI有\ 3\ 中选择, \\
IV有3种选择,\\
VII有2种选择.$

___
<font color=red size="5"> $实现部分$ </font>
在 $Kruskal$ 最小生成树算法加新的边时,
使用 $set$ 辅助判断 ~~碳碳双键,碳碳三键~~ **等价的边** 和 **环**,

>用 $set$ 维护参考了上方的题解.
___

<font size="6" color=Black> $\mathcal{Code}$ </font><br/>

```cpp
#include<bits/stdc++.h>
#define reg register

const int maxn = 100005;
const int mod = 1e9 + 7;

int N;
int M;
int F[maxn];

int Find(int x){ return F[x]==x?x:F[x]=Find(F[x]); }

struct Edge{ int u, v, w; } E[maxn];
bool cmp(Edge a, Edge b){ return a.w < b.w; }

int main(){
        freopen("a.in", "r", stdin);
        freopen("a.out", "w", stdout);
        scanf("%d%d", &N, &M);
        for(reg int i = 1; i <= M; i ++) scanf("%d%d%d", &E[i].u, &E[i].v, &E[i].w);
        for(reg int i = 1; i <= N; i ++) F[i] = i;
        std::sort(E+1, E+M+1, cmp);
        int Ans_1 = 0, Ans_2 = 1;
        for(reg int i = 1; i <= M; i ++){
                typedef std::pair <int, int> pr;
                std::set <pr> S;
                int t, x = 0, y = 0;
                for(t = i; t <= M; t ++){
                        if(E[t].w != E[i].w) break ;
                        int a = E[t].u, b = E[t].v;
                        S.insert(pr(std::min(a, b), std::max(a, b)));
                }
                x = t - i; t --;
                for(; i <= t; i ++){
                        int a = Find(E[i].u), b = Find(E[i].v);
                        if(a != b) F[b] = a, y ++, Ans_1 = (1ll*Ans_1 + E[i].w) % mod;
                }
                i --;
                if(x == 2 && y == 1) Ans_2 = 2ll*Ans_2 % mod;
                else if(x == 3){
                        if(y == 1) Ans_2 = 3ll*Ans_2 % mod;
                        else if(y == 2) Ans_2 = 2ll*Ans_2 % mod;
                }
        }
        printf("%d %d\n", Ans_1, Ans_2);
        return 0;
}

```


---

## 作者：Vocanda (赞：1)

# 题目
[题目链接](https://www.luogu.com.cn/problem/P3037)

# 分析

### 题意
相信翻译说的已经挺明白的了，就是求一个有相同边权的图上的最小生成树的整体的权值，并且求出方案数。

### 正题
最小生成树的整体的权值很好求吧，其实就是一个$Kurscal$的板子，先升序排序，按顺序用并查集求（不会$Kruscal$的应该不会来做这个题吧……这里不多赘述）这样第一问就求出来了。

那么关键的第二问来了：
首先我们考虑一下，假如有相同的边权，并且可以作为最小生成树的一条边，那么我们就让数量加一，每次只需要依次遍历相同边权的边即可。

因为最多有三条长度相同的，但是我们不能确定他们是不是一样的，所以我们就需要去重操作，而一样的条件则是连接的点相同，所以要用到$pair$和$set$，$pair$进行记录连接的两个点，而$set$存储，由于它本身就带有去重的操作，所以最后我们只需要统计他的不同的个数来进行分情况考虑就行了。

需要注意的一个地方就是要是这个边权只加入生成树一个边，那么就直接让情况数乘以上边记录的相同边权的个数，也就是$cnt$。

其次就是这个边权加入生成树两个边，因为加入三个边只有一种情况，所以考虑两个边的就行。如果上边当前权值有$3$个边，并且没有重复的（利用$set$的去重和$size$函数）那么情况数就乘以$3$，如果有三个边但是有两个是重复的，那么就乘以$2$，其他的情况都是方案不变的，这样我们就得到了答案。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 1e6+10;
const int mod = 1e9+7;
int n,m;
struct Node{
	int x,y,val;
}e[maxn<<1];
int fa[maxn];
int ans,sum=1;
int cnt[maxn];
bool cmp(Node a,Node b){
	return a.val<b.val;
}//按边权排序
int Find(int x){
	return x == fa[x] ? x : fa[x] = Find(fa[x]);
}//并查集查找
void kruscal(){
	for(int i=1;i<=n;++i){//并查集初始化
		fa[i] = i;
	}
	sort(e+1,e+m+1,cmp);//升序排序
	for(int i=1;i<=m;){
		int cnt = 0;//记录每个边权的个数
		set<pair<int,int> >s;//set用于存储并去重
		int j;
		for(j = i;j<=m && e[i].val == e[j].val;++j){//枚举相同的边，更新j
			int x = Find(e[j].x);
			int y = Find(e[j].y);
			if(x > y)swap(x,y);
			if(x != y){//记录
				cnt ++;
				s.insert(make_pair(x,y));
			}
		}
		int num = 0;
		for(;i<j;++i){//继续枚举，更新i
			int x = Find(e[i].x);
			int y = Find(e[i].y);
			if(x != y){//加边
				fa[y] = x;
				num++;
			}
		}
		ans += e[i-1].val*num;
		if(num == 1){//如果就加入一条边，那么直接乘以相同边权的数量
			sum = sum * cnt % mod
		}
		if(num == 2){//加入两条边
			if(cnt == 3 && s.size() == 2){//有两个等价的边
				sum = 2*sum%mod;
			}
			if(cnt == 3 && s.size() == 3){//没有等价的边
				sum = 3*sum%mod;
			}
		}//其他情况的话方案数都不变
	}
}
signed main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=m;++i){//存边
		scanf("%lld%lld%lld",&e[i].x,&e[i].y,&e[i].val);
	}
	kruscal();//最小生成树
	printf("%lld %lld\n",ans,sum);
}

```

---

## 作者：liyanzhi1106 (赞：1)

这道题其实并不像难度分类标的那么难。
首先，题意大家都清楚：就是给一个图，求他的最小生成树和最小生成树的个数。

按照最小生成树的做法，我们先以边权为优先级排递增序。
接着我们统计边相同的个数和要取的个数。因为题目中说了最多有三条权值相同的边所以可以分类讨论，求出取法。最后乘法原理得出最终答案。

具体细节看程序里面。

```

#include<bits/stdc++.h>

using namespace std;
int n,m;
int fa[40001];
const int mod=1e9+7;

struct Tree{
	int u;int v;int val;
}tre[1000005];

int Find(int x){
	if(fa[x]==x)return x;
	else return fa[x]=Find(fa[x]);
}//找根节点

bool cmp(Tree x,Tree y){
	return x.val<y.val;
}

int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=m;i++){
		cin>>tre[i].u>>tre[i].v>>tre[i].val;
	}
    //读入并初始化
	sort(tre+1,tre+m+1,cmp);
    
	long long sum1=0,sum2=1;
    //sum1代表最小生成树的总长度
    //sum2代表最小生成树的个数
    
	for(int i=1;i<=m;){
		int ss=0;//边权一样的个数
		set<pair<int,int> >s;
        //一个存储不等价边集合
		int j;
		for( j=i;j<=m&&tre[i].val==tre[j].val;j++){
			int x=tre[j].u,y=tre[j].v;
			x=Find(x);y=Find(y);
			if(x>y)swap(x,y);//格式
			if(x!=y){//可以加入生成树
				ss++;
				s.insert(make_pair(x,y));
			}
		}
		int num=0;//需要加入生成树的个数
		for(;i<j;i++){
			int x=Find(tre[i].u);
			int y=Find(tre[i].v);
			if(x!=y){
				fa[y]=x;
				num++;
			}
		}
		sum1+=(long long)tre[i-1].val*num;
        //因为i已经tre[i].val已经不等于原先的权值
		if(num==1){//只选一个
			if(ss==2)sum2=sum2*2%mod;
			if(ss==3)sum2=sum2*3%mod;
		}
		if(num==2){
			if(ss==3&&s.size()==3)sum2=sum2*3%mod;
            //三条边可以选且三条边不等价
			if(ss==3&&s.size()==2)sum2=sum2*2%mod;
            //三条边可以选但两条边等价
		}
	}
	cout<<sum1<<" "<<sum2<<endl;
} 
```

PS：提醒一句要开long long

---

## 作者：zbzbzzb (赞：1)

锻炼思维蛮好的一道题。

一开始不会，看了题解后恍然大悟，这篇题解就当是我的体会了（感谢 @Vocanda 的题解提供的思路）。

第一个询问并不难，直接 Kruskal 一边就行了（~~应该没有人不会 Kruskal 吧~~）。

第二个询问就是，如果有相同边且可以用到最小生成树中去，那么就会有多种最小生成树。

但是，有可能会有边权相同且起点和终点都相同（也就的完全相同的情况），这样，可以能会多算，所以，我们考虑去重。

那么，去重可以不用写自己写，用个 `set` 就行了，每次将相同的放进 `set` 中，就可以自动去重了。

解决了重复的问题后，我们就可以来统计出这个边权相同的边数和会加入生成树的边数，在过程中可以顺便将第一个询问求出，然后分类讨论：

- 如果会加入生成树的只有一条边，那么就是边权相同的所有边都有一种可能，就将答案乘上边权相同的边数。

- 如果会加入生成树的有两条边，那么还会有可能是有两条边完全相同，那么就只有两种情况，那么就将答案乘上 $2$，也有可能没有边完全相同，那么就有三种情况，那么就将答案乘上 $3$。

- 如果三条边都会加入生成树，那么只有一种生成树了，不用考虑。

那么，代码就很好写了。

AC CODE：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
struct node{
	int x,y,w;
	friend bool operator < (node a,node b){
		return a.w<b.w;
	}
}a[100010];
long long n,m,i,j,ret,cnt=1/*后面会乘，所以初始化为1*/,tmp,tmp2,f[1000010];
int getfa(int x){//并查集
	if(x==f[x]){
		return x;
	}return f[x]=getfa(f[x]);
}void merge(int x,int y){
	f[getfa(x)]=getfa(y);
}signed main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++){
		f[i]=i;
	}for(int i=1;i<=m;i++){
		scanf("%lld%lld%lld",&a[i].x,&a[i].y,&a[i].w);
	}sort(a+1,a+m+1);
	while(i<=m){
		set<pair<int,int> >s;//利用set去重
		j=i,tmp=0,tmp2=0;//tmp表示边权相同的边数，tmp2表示会加入生成树的边数
		while(j<=m&&a[i].w==a[j].w){//边权相同
			int x=min(getfa(a[j].x),getfa(a[j].y)),y=max(getfa(a[j].x),getfa(a[j].y));//保证起点小，终点大
			if(x!=y){//不相同
				tmp++;
				s.insert(make_pair(x,y));//插入
			}j++;
		}while(i<j){
			if(getfa(a[i].x)!=getfa(a[i].y)){//加入生成树
				merge(a[i].x,a[i].y);//合并
				tmp2++;//加入生成树的边数加1
			}i++;			
		}ret+=a[i-1].w*tmp2;//因为这里i=j，所以是i-1
		if(tmp2==1){//只有一条边会加入生成树
			cnt*=tmp;//都有一种可能
			cnt%=mod;
		}else if(tmp2==2){//两条边会加入生成树
			if(tmp==3&&s.size()==2){//实际上有两条边完全相同，2种情况
				cnt*=2;
				cnt%=mod;
			}else if(tmp==3&&s.size()==3){//没有边完全相同，3种情况
				cnt*=3;
				cnt%=mod;
			}
		}		
	}printf("%lld %lld",ret,cnt);
	return 0;
}
```

---

## 作者：liugh_ (赞：0)

提供一个不用分讨的做法。

## [[USACO11DEC] Simplifying the Farm G](https://www.luogu.com.cn/problem/P3037)

> $n$ 个点 $m$ 条边的无向图，至多存在 $3$ 条长度相等的边，求最小生成树的大小和个数。
>
> $n\le 4\cdot 10^4$，$m\le 10^5$。

先求出最小生成树。一条非树边 $(u,v,w)$ 能造成贡献当且仅当用其替换某条树边后还是树且边权和不变，显然可供替换的树边一定在 $u$ 到 $v$ 的路径上。**一个边权至多出现 $3$ 次，所以不会同时存在 $2$ 对能互相替换的树边和非树边**。于是，若路径上长度为 $w$ 的边有 $x\in\{0,1,2\}$ 条，这条非树边就能多造成 $x$ 的方案数。

那么开一个下标为边权的桶 $b$，对于每条树边 $(u,v,w)$，令 $b_w=1$；对于每条非树边 $(u,v,w)$，若 $u$ 到 $v$ 路径上有 $x$ 条长度为 $w$ 的边，令 $b_w\gets b_w+x$。最后扫一遍整个桶，将所有非 $0$ 位相乘即为答案。

问题转化为求路径上某一个边权的出现次数，可以用主席树实现，时间复杂度 $O(n\log n)$。

~~等下，不会有人真的敲了一遍主席树吧（~~

4e4，你想到了什么？bitset！一个边权至多出现 $3$ 次，我们可以像插头 dp 那样，用二进制维护四进制，卡一下常能过。这个做法代码就不放了 /tx。时间复杂度 $O(n^2/w)$。

```cpp
#include<iostream>
#include<algorithm>
#include<queue>
#ifdef ONLINE_JUDGE
#define getchar() (p_==q_&&(q_=(p_=b_)+fread(b_,1,s_,stdin),p_==q_)?-1:*p_++)
#define putchar(x_) ((r_-o_<s_)?(*r_++=x_):(flush(),r_=o_,*r_++=x_))
bool t_=(std::cin.tie(0),std::cout.tie(0),std::ios_base::sync_with_stdio(0));
#endif
#define flush() (fwrite(o_,r_-o_,1,stdout),fflush(stdout),0)
#define exit(_) exit(flush())
using namespace std;constexpr signed s_=1<<20;char b_[s_],o_[s_],*p_=b_,*q_=b_,*r_=o_;template<class T_>bool fr(T_&x_){x_=0;char c_=0,f_=0;do{if(c_=='-')f_=1;if((c_=getchar())==-1)return 0;}while(c_<48||c_>57);do {x_=x_*10+c_-48;if((c_=getchar())==-1)break;}while(c_>47&&c_<58);if(f_)x_=-x_;return 1;}template<class T_>void fw(T_ x_){char d_[40],l_=-1;if(x_<0)x_=-x_,putchar('-');do d_[++l_]=x_%10+48;while(x_/=10);do putchar(d_[l_]);while(~--l_);}

constexpr int maxn=4e4+5;

int n,m;
struct _E{int u,v,w,tr;}E[(int)1e5+5];

struct _eg{int pre,v,w;}eg[maxn*2];int ei=1,eh[maxn];
void ea(int u,int v,int w){eg[++ei]={eh[u],v,w};eh[u]=ei;}

struct _uni{
    int fa[maxn];void init(int len){for(int i=0;i<=len;i++)fa[i]=i;}
    int find(int x){return x==fa[x]?fa[x]:fa[x]=find(fa[x]);}
    void mer(int x,int y){x=find(x),y=find(y);fa[x]=y;}
}uni;
int kru(){
    sort(E+1,E+m+1,[](const _E& a,const _E& b){return a.w<b.w;});
    uni.init(n);int cnt=0,res=0;
    for(int i=1;i<=m;i++){
        int u=E[i].u,v=E[i].v,w=E[i].w;
        if(uni.find(u)!=uni.find(v)){
            uni.mer(u,v);
            ea(u,v,w),ea(v,u,w);
            res+=w;
            E[i].tr=1;
            if(++cnt==n-1)break;
        }
    }
    return res;
}

struct _hjt{
    int tot,rt[maxn];
    struct _nd{int ch[2],cnt;}nd[maxn*32];
    #define lc(x) nd[x].ch[0]
    #define rc(x) nd[x].ch[1]
    #define mid ((l+r)>>1)
    void ins(int x,int &y,int l,int r,int val){
        nd[y=++tot]=nd[x],nd[y].cnt++;
        if(l==r)return;
        if(val<=mid)ins(lc(x),lc(y),l,mid,val);
        else ins(rc(x),rc(y),mid+1,r,val);
    }
    int qry(int x,int y,int l,int r,int val){
        if(!y)return 0;
        if(l==r)return nd[y].cnt-nd[x].cnt;
        if(val<=mid)return qry(lc(x),lc(y),l,mid,val);
        else return qry(rc(x),rc(y),mid+1,r,val);
    }
}hjt;

int fa[maxn][17],dep[maxn];
int lca(int x,int y){
    if(dep[x]<dep[y])swap(x,y);
    for(int k=__lg(dep[x]);k>=0;k--)
        if(dep[fa[x][k]]>=dep[y])
            x=fa[x][k];
    if(x==y)return x;
    for(int k=__lg(dep[x]);k>=0;k--)
        if(fa[x][k]!=fa[y][k])
            x=fa[x][k],y=fa[y][k];
    return fa[x][0];
}
void dfs(int u,int lst,int w){
    dep[u]=dep[lst]+1,fa[u][0]=lst;
    for(int k=0;fa[u][k];k++)fa[u][k+1]=fa[fa[u][k]][k];
    hjt.ins(hjt.rt[lst],hjt.rt[u],1,1e6,w);
    for(int e=eh[u];e;e=eg[e].pre){
        int v=eg[e].v;
        if(v==lst)continue;
        dfs(v,u,eg[e].w);
    }
}

signed main(){
    fr(n),fr(m);
    for(int i=1;i<=m;i++)fr(E[i].u),fr(E[i].v),fr(E[i].w);
    fw(kru()),putchar(32);
    dfs(1,0,0);
    static int buc[(int)1e6+5];
    for(int i=1;i<=m;i++)if(E[i].tr)buc[E[i].w]=1;
    for(int i=1;i<=m;i++)if(!E[i].tr){
        int u=E[i].u,v=E[i].v,w=E[i].w;
        int lca=::lca(u,v);
        buc[w]+=hjt.qry(hjt.rt[lca],hjt.rt[u],1,1e6,w);
        buc[w]+=hjt.qry(hjt.rt[lca],hjt.rt[v],1,1e6,w);
    }
    long long ans=1;
    for(int i=1;i<=1e6;i++)if(buc[i])ans=ans*buc[i]%(int)(1e9+7);
    fw(ans);
    exit(0);
}
```

---

