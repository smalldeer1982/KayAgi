# Interstellar battle

## 题目描述

A 国是一个有 $n$ 个星球的帝国，有 $(n-1)$ 条双向虫洞连接它们。虫洞对 A 国有极大的宗教重要性，一些星球认为他们是同一个地区当且仅当它们能通过虫洞互相到达。已知初始时 A 国的所有星球认为他们是同一个地区，也就是说 A 国的地图构成了一棵树。

然而，A 国遇到了强大的同样拥有通讯技术的 B 国军队。B 国每天晚上会对 A 国发起进攻，每次进攻会攻击 A 国的所有星球，使第 $i \ (0 \le i \le n-1)$ 个星球有 $p_i$ 的概率被摧毁，被摧毁的星球无法通过，这会导致 A 国被分为若干个地区。在每天早上（包括第一天），A 国会重建所有星球并改变其中**一个**星球的 $p_i$ 值。现在，A 国的国王找到了你，希望你求出在每一天的修复之后，B 国的进攻期望将他的国家分成多少个地区。

换句话说，A 国的国王希望知道每一次进攻之后他的国家期望会出现多少个连通分量。

Translated by @[Grammar_hbw](/user/856004)

## 样例 #1

### 输入

```
5
0.50 0.29 0.49 0.95 0.83
2 3
0 3
3 4
2 1
3
4 0.66
1 0.69
0 0.36
```

### 输出

```
1.68040
1.48440
1.61740
```

# 题解

## 作者：Arghariza (赞：6)

这题有一个坑点，而且很多题解没有提及（

考虑数每个联通块的顶点，一个点成为一个顶点**当且仅当其父亲消失，并且这个点未消失**，所以答案为 $\sum\limits_i p_{fa_i}(1-p_i)$。

现在我们考虑维护每个节点，对于它的儿子对答案的贡献，即 $sum_u=\sum\limits_{v\in son(u)}p_u(1-p_v)$，我们发现修改一个节点 $u$ 的 $p$ 时，我们只会修改 $fa_u$ 和 $u$ 的 $sum$ 值，具体来讲：

$$sum'_{fa_u}=\left(\frac{sum_{fa_u}}{p_{fa_u}}-(1-p_u)+(1-p'_u)\right)\times p_{fa_u}$$

$$sum'_u=\frac{sum_u}{p_u}\times p'_u$$

于是我们可以在 $O(1)$ 的时间内维护 $sum$ 数组的修改，并在 $O(1)$ 的时间内得到新的答案。

然后你开心地把你的代码交了上去，开心地发现：

![asev.png](https://s2.loli.net/2022/07/19/nYGXfskaZBIuRgF.png)

为啥呢？你回去仔细看了一眼没有翻译的题面：

> The next line contains $N$ different real numbers in the interval $[0,1]$ , specified with 2 digits after the decimal point, denoting the probabilities that the corresponding planet will fall.

也就是说 $p_u$ 有可能取 $0$，你不能使用 $p$ 去除。

于是我们换一下 $sum_u$ 的定义：

$$sum_u=\sum\limits_{v\in son(u)}\left(1-p_v\right)$$

然后考虑修改对答案和 $sum_{fa_u}$ 的贡献即可，也是 $O(1)$ 解决。

复杂度 $O(n+q)$。

[评测记录 & 代码](https://codeforces.com/contest/1045/submission/164831162)

---

## 作者：EuphoricStar (赞：6)

## 题意

给一棵树和每个结点消失的概率 $p_i$，有 $q$ 组询问，每组询问要求：

1. 将 $p_u$ 修改为 $x$
2. 查询森林的期望连通块数量

## 思路

题中给出的是每个结点消失的概率，那不妨先 $p_i \gets 1 - p_i$ 将 $p_i$ 转化为每个结点出现的概率。

众所周知，森林连通块数量 $=$ 点数 $-$ 边数，因此期望连通块数量为 $\sum\limits_{u=1}^n p_u - \sum\limits_{(u,v) \in E} p_up_v$。考虑维护这个答案。

令 $1$ 为根，再维护一个 $sum_u = \sum\limits_{v \in son_u} p_v$，每次修改就减去原来的 $p_u$ 和 $p_u \times sum_u$ 的贡献再加上新的 $p_u$ 和 $p_u \times sum_u$ 的贡献。对于父结点单独处理。注意还要修改父结点的 $sum$。

时间复杂度 $O(n + q)$。

## 代码

[code](https://codeforces.com/contest/1045/submission/164830464)

---

## 作者：ax_by_c (赞：5)

连通块的个数这个东西很麻烦，我们将其改写为没被删去且父亲被删去的点的个数。

随便定一个根，那么每个点的贡献就是 $(1-p_u)p_{fa}$。特别的，根节点的贡献是 $1-p_{root}$。

然而在改动时，这样的贡献形式与每个儿子都有关，所以我们再次改写，得到 $1-p_{root}+\sum p_u\sum (1-p_{son})$。

于是维护 $sum_u=\sum (1-p_{son})$，以及 $1-p_{root}+\sum p_u sum_u$ 即可，时间复杂度 $O(n+q)$。

---

## 作者：LiftingTheElephant (赞：5)


给定一棵树，每个点消失的概率，求联通块个数的数学期望。 

先了解一下树上的连通块的一个常用套路：       
考虑用每个连通块的顶点来标记这个连通块   

考虑每个点对答案的贡献，一个点对答案有贡献当且仅当该节点的父节点消失了且自己没有消失 

然后处理修改，一个点u的概率被修改后，首先O(1)的修改自己的贡献

然后还要修改u的所有儿子节点的贡献，u的所有子节点贡献之和为

$sum_{i=1}^{v} (1-p_v)×p_u$

所以只要存每个节点u的子节点的贡献之和即可，即可O(1)完成所有的修改

最后上代码：
```
#include <iostream>
#include <cstdio>
#define MAXN 100005
using namespace std;
int n,q,fa[MAXN],u,v;// fa[i]代表i的父亲 
double ans,pb[MAXN],sum[MAXN];//pb[i]代表第i个点消失的概率，sum[i]代表第i个点的儿子的贡献和 
struct tree{
	int v;
	tree *next;
}*h[MAXN],pool[MAXN<<1],*tot=pool;
inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<3)+(x<<1)+ch-'0';
		ch=getchar();
	}
	return x*f;
}
inline void addedge(int u,int v)//增加边 
{
	tree *p=tot++;
	p->v=v;
	p->next=h[u];
	h[u]=p; 
}
void dfs(int u,int f)//统计 
{
	fa[u]=f;
	ans+=pb[fa[u]]*(1-pb[u]);
	for(tree *p=h[u];p;p=p->next)
		if(p->v!=f)
		{
			dfs(p->v,u);
			sum[u]+=(1-pb[p->v]);
		}
}
int main()
{
	n=read();
	for(int i=1;i<=n;i++)
		scanf("%lf",&pb[i]);
	for(int i=1;i<n;i++)
	{
		u=read();
		v=read();
		u++;
		v++;
		addedge(u,v);
		addedge(v,u);
	}
	pb[0]=1;
	dfs(1,0);
	q=read();
	for(int i=1;i<=q;i++)
	{
		double del;
		u=read();
		scanf("%lf",&del);
		u++;
		ans+=pb[fa[u]]*(1-del)-pb[fa[u]]*(1-pb[u]);
		ans+=del*sum[u]-pb[u]*sum[u];
		sum[fa[u]]+=-del+pb[u];
		pb[u]=del;
		printf("%.5lf\n",ans);
	}
	return 0;
}
```

---

## 作者：shadowice1984 (赞：1)

~~数据范围才1e5根号算法暴搞了事~~
____________

# 本题题解

我们可以很显然的得出一个结论是剩下的联通块个数=幸存点数-两端点都幸存的边数目,显然这个式子两端同时取期望还是成立的

换句话说我们如果设$w_{i}=1-p_{i}$也就是i这个点存在的概率

那么我们要维护的式子就是

$$\sum_{i=1}^{n}w_{i}-\sum_{i=1}^{n-1}w_{u_{i}}w_{v_{i}}$$

其中$u_{i},v_{i}$表示第$i$条边连接的两个点

那么$\sum_{i=1}^{n}w_{i}$维护起来相当容易

关键是维护所有边的权值之和

那么我们考虑修改一个点u的时候,只有端点为u的边的权值会发生变化

而且更进一步的讲，如果我们知道了所有和u相连的点的权值之和的话,我们就可以处理答案了,假设所有和u相连的点的权值之和是sum的话,我们让答案减去旧的$w_{u}×sum$加上新的$w_{u}×sum$就行了

那么我们怎么求所有和u相连的点的权值之和呢？

显然不能每次粗暴的大力for一下，这样我们碰到菊花图就炸飞了

这张图是一个树，所以我们似乎有一些精妙的做法可以过掉这题？

好烦啊不想推式子……不如根号暴搞一发？

我们对于每条边$(u,v)$分类讨论,如果u的度数大于v就将这条边定向为u指向v，反之则令v指向u

那么现在我们在这张重定向的图中统计和一个点相连的所有点的点权和的时候
我们分为u指向的点和指向u的点这两种点进行计算

为了保证复杂度我们记$sum_{u}$表示所有指向u的点的点权和

那么我们此时查询所有和u相连的点权之和的时候就变得异常简单了我们先直接读取$sum_{u}$得到指向u的点的点权之和,之后大力for一遍出边计算u指向的点的点权

当我们修改u的点权的时候for一遍出边修改u指向点的sum值就行了

容易看出我们修改和查询的复杂度都是O(一个点的出度)的,我们可以证明的是这样建图每个点度数最坏是$O(\sqrt{m})$级别的,因此我们的算法复杂度就是$O(Q\sqrt{N})$的

~~实际情况下非构造数据基本跑不满~~

上代码~

```C
#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;const int N=1e5+10;typedef long long ll;typedef double db;
db p[N];vector <int> v[N];db sum[N];int d[N];int eu[N];int ev[N];int n;db ans;int q;
int main()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++)scanf("%lf",&p[i]),p[i]=1-p[i],ans+=p[i];
	for(int i=1;i<n;i++)
		scanf("%d%d",&eu[i],&ev[i]),d[eu[i]]++,d[ev[i]]++;
	for(int i=1;i<n;i++)//定向 
		if(d[eu[i]]<d[ev[i]])v[eu[i]].push_back(ev[i]),sum[ev[i]]+=p[eu[i]];
		else v[ev[i]].push_back(eu[i]),sum[eu[i]]+=p[ev[i]];
	for(int i=1;i<n;i++)ans-=p[eu[i]]*p[ev[i]];
	scanf("%d",&q);vector <int> :: iterator it;
	for(int i=1,u;i<=q;i++)//暴力 
	{
		db del=0;scanf("%d",&u);del=sum[u];
		for(it=v[u].begin();it!=v[u].end();++it)del+=p[*it],sum[*it]-=p[u];
		ans+=p[u]*del;ans-=p[u];scanf("%lf",&p[u]);p[u]=1-p[u];ans-=p[u]*del;ans+=p[u];
		for(it=v[u].begin();it!=v[u].end();++it)sum[*it]+=p[u];
		printf("%lf\n",ans);
	}return 0;
}
```



---

## 作者：songzhihan2010 (赞：0)

## CF1045D
如果直接对连通块下手会发现很难做，很难不发现图中给的图是一棵树，那么切断的边必然是一个结点和其父亲的连边，所以要是这个点没删去，但是他父亲被删去了，那么就会形成一个新的连通块。

很容易会发现一个结点的贡献就是 $p_{fa_u}\times(1-p_u)$ 当然，由于根节点也会产生贡献，所以 $p_{fa_{root}}=1$。

那么我们不妨钦定 0 号节点就是这棵树的根节点，随后就可以得出当前这棵树的答案就是 $1-p_0+\sum_{u\in V}{p_i}\sum_{v\in son_u}{(1-p_v)}$

然后就会发现对于节点 u，$\sum_{v\in son_u}{(1-p_v)}$ 是可以通过 dfs 记录的，那我们就维护 $sum_u=\sum_{v\in son_u}{(1-p_v)}$，在修改中不断更新答案。

再结合式子就会发现 $p_u$ 改变时会影响 $sum_{fa_u}$ ，那我们可以先将 $p_u$ 之前产生的贡献减去，然后加上新的贡献就可以维护答案了，对于 $p_u\sum_{v\in son_u}{(1-p_v)}$ 也可以同样处理出来。最后，记得修改根节点时 $1-p_{root}$ 时要手动更新下

---

### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll read() {
	ll x=0,f=1;
	char ch=getchar();
	while (ch<'0'||ch>'9') {
		if (ch=='-') f=-1;
		ch=getchar();
	}
	while (ch>='0'&&ch<='9') {
		x=x*10+ch-48;
		ch=getchar();
	}
	return x*f;
}
vector<ll> e[100010];
ll fa[100010];
double sum[100010];
double p[100010],x;
ll n;
ll u,v;
double ans;
void dfs(ll t,ll f) {
	fa[t]=f;
	for (int i=0; i<e[t].size(); i++) {
		if(e[t][i]==f) continue;
		dfs(e[t][i],t);
		sum[t]+=(1.0-p[e[t][i]]);
	}
}
signed main() {
	n=read();
	for (int i=0; i<n; i++) {
		scanf("%lf",&p[i]);
	}
	for (int i=1; i<n; i++) {
		u=read();
		v=read();
		e[u].push_back(v);
		e[v].push_back(u);
	}
	ans=1-p[0];
	dfs(0,0);
	for (int i=0; i<n; i++) {
		ans+=p[i]*sum[i];
	}
	ll _;
	_=read();
	while(_--) {
		u=read();
		scanf("%lf",&x);
		if(u==0) {//修改根节点时父亲的贡献记得单独算
			ans-=1-p[0];
			ans+=1-x;
			ans-=p[0]*sum[0];
			ans+=x*sum[0];
			p[0]=x;
		} else {
			ans-=p[fa[u]]*sum[fa[u]];//减去贡献
			sum[fa[u]]-=1.0-p[u];//更新sum
			sum[fa[u]]+=1.0-x;
			ans+=p[fa[u]]*sum[fa[u]];
			ans-=p[u]*sum[u];
			ans+=x*sum[u];
			p[u]=x;
		}
		printf("%.5lf\n",ans);
	}
}
```

---

## 作者：Hoks (赞：0)

## 前言
早上比赛里打到的，看了个提示才切掉，还是太菜了。

摘自 [杂题选做](https://www.luogu.com.cn/training/499842)。
## 思路分析
重点思路即为一句话：**考虑每个点是连通块的根的概率**。

根据这个转化，我们只需对每个点考虑他和他父亲的关系。

一个点成为连通块的根**当且仅当他父亲节点被摧毁而他自己不被摧毁**。

设点 $i$ 被摧毁的概率为 $p_i$，父亲节点为 $f_i$。

因为 $0$ 号节点不存在，所以 $p_i$ 被摧毁的概率为 $1$。

而点 $i$ 成为根的概率即为 $(1-p_i)\times p_{f_i}$。

修改直接考虑暴力修改每个儿子算出来的值，得到 $O(n^2)$ 算法。

接着考虑优化。

显然对于一个点 $i$ 来讲和他可能有关的贡献可以分为两种：
1. $i$ 与 $f_i$，贡献为 $(1-p_i)\times p_{f_i}$。
2. $i$ 与 $son_i$，贡献为 $p_i\times\sum p_{son_i}$。

注意到修改 $p_i$ 时，$\sum p_{son_i}$ 是不变的，可以直接预处理出来算下 $p_i$ 的 $\Delta$ 改下就行。

记得修改 $\sum p_{son_{f_i}}$。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10,INF=0x3f3f3f3f3f3f3f3f,mod=1e9+7;
int n,m,f[N];vector<int>e[N];double p[N],ans,s[N];
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    // #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
inline void dfs(int u,int ff){f[u]=ff;for(auto v:e[u]) if(v!=ff) dfs(v,u);}
signed main()
{
    n=read();for(int i=1;i<=n;i++) scanf("%lf",&p[i]);
    for(int i=1,u,v;i<n;i++) u=read()+1,v=read()+1,e[u].emplace_back(v),e[v].emplace_back(u);
    dfs(1,0);p[0]=1;for(int i=1;i<=n;i++) ans+=p[f[i]]*(1-p[i]),s[f[i]]+=1-p[i];m=read();
    for(int i=1,x;i<=m;i++)
    {
        x=read()+1;ans-=s[f[x]]*p[f[x]];ans-=s[x]*p[x];s[f[x]]-=1-p[x];
        scanf("%lf",&p[x]);s[f[x]]+=1-p[x];ans+=s[f[x]]*p[f[x]];ans+=s[x]*p[x];
        printf("%.5lf\n",ans);
    }
    genshin:;flush();return 0;
}
```

---

## 作者：zzw4257 (赞：0)

inf计划的第一题,评分`2200`,**未**看题解
>给定一棵树与每个点**不存在的概率**，支持
>- 动态修改一个点不存在概率
>- 求树上联通块个数期望

看起来是个动态$dp$,那就先真$dp$

其实树上联通块个数期望就是相邻两点不同时存在边数期望

然后我就卡了一会儿，因为改一个点是一定要改完所有出边的

然后突然发现可以让这条边有方向，从父亲到儿子

也就是说我们考虑一个联通块顶端被断掉（父亲不选，我选，这样和无方向的考虑有区别）情况

初始情况就是$\sum\limits_{x}p_{fa_x}(1-p_{x})$

每次修改可以算出答案变化(新来的是$p_x$)$(p_x-p_x')(\sum\limits_{y}(1-p_y)-p_{fa_x})$

发现对每个$p_x$贡献只依赖与父亲的$p_{fa_x}$和儿子的$(1-p_y)$**之和**$s_x$而非每一个

于是现在可以$\mathcal O(1)$更改$ans,s_{fa_x},p_x$即可

```cpp
#include<bits/stdc++.h>
#define N 100001
using namespace std;
int n,fa[N],m;
double p[N],s[N],ans;
vector<int>g[N];
inline void dfs(int x){ans+=p[fa[x]]*(1.-p[x]);for(int y:g[x])if(y^fa[x])fa[y]=x,dfs(y),s[x]+=(1.-p[y]);}
signed main(void){
	int i,x;double y;scanf("%d",&n);
	for(*p=i=1;i<=n;++i)scanf("%lf",p+i);
	for(i=1;i<n;++i)scanf("%d%lf",&x,&y),++x,y+=1,g[x].push_back(y),g[(int)y].push_back(x);
	dfs(1);scanf("%d",&m);
	while(m--){
		scanf("%d%lf",&x,&y);++x;
		ans=ans+(p[fa[x]]-s[x])*(p[x]-y),s[fa[x]]-=y-p[x],p[x]=y;
		printf("%.4lf\n",ans);
	}
	return 0;
}

```

---

