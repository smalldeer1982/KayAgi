# The Cake Is a Lie

## 题目描述

二维平面上有一个正 $n$ 边形，顶点用 $1$ 至 $n$ 中的正整数乱序编号。

现在给出这个 $n$ 边形的一种三角剖分的可行方案（注意：这意味着将给出 $n-2$ 个三角形的顶点信息）。你需要求出：

- 这个$n$边形顶点编号的排列顺序$p$；
- 各个三角形被切下去的顺序$q$。

如果有多解输出任意一组。

## 样例 #1

### 输入

```
3
6
3 6 5
5 2 4
5 4 6
6 3 1
6
2 5 6
2 5 1
4 1 2
1 3 5
3
1 2 3
```

### 输出

```
1 6 4 2 5 3 
4 2 3 1 
1 4 2 6 5 3 
3 4 2 1 
1 3 2 
1 
```

# 题解

## 作者：Silviasylvia (赞：3)

先解决第一问：点的顺序。

注意到原来多边形上的边在 $n-2$ 个三角形里面只会出现一次，因为切割而出来的边则会出现两次。因此拿 `std::map` 记录一下出现次数，然后连边 dfs 就解决了。

第二问：割三角形的顺序。

考虑找特殊点。我们发现第一次割下来的一定是连续三个顶点，并且中间的顶点仅出现一次（因为割完就没了，很好理解）。此时就转化成了一个 $n-1$ 边形的子问题。类似拓扑排序的去一个个删点就可以了。

时间复杂度 $O(n\log n)$，瓶颈在于第一问找重边。

[代码](https://codeforces.com/contest/1282/submission/181273829)

---

## 作者：_Lamiris_ (赞：2)

## 题目链接

- [CF1282E The Cake Is a Lie](https://www.luogu.com.cn/problem/CF1282E)
- [CF 原题链接](https://codeforces.com/problemset/problem/1282/E)

## 简要题意

有一个正 $n$ 边形，将其分割为 $n-2$ 个以原多边形顶点为顶点的三角形（任意两个三角形不重叠）。给定这 $n-2$ 个三角形，按顺序输出这个正 $n$ 边形的顶点，以及给定的 $n-2$ 个三角形的一种分割方式。

## 解题思路

注意到，对于每一次分割的边，其都会成为两个三角形的边；而正 $n$ 边形的边只会成为一个三角形的边。

那么我们考虑对于输入的每个三角形的三边，我们进行处理。如果有一条边出现了两次，那么这条边是切割的边；如果有一条边只出现了一次，那么这条边是原正 $n$ 边形的边。考虑用 `std::map` 维护。

我们在上述过程中存两张图，一张图维护原正 $n$ 边形的边和顶点，另一张图维护切割的边和每个三角形。

- 对于第一张图，我们取任意一个点跑 dfs，将经过的点输出，知道回到这个点，便得到了按顺序输出的正 $n$ 边形的顶点。
- 对于第二张图，我们考虑跑一个拓扑排序，如果一个三角形的度数是 $1$，那么就将它加入队列。在队列每次 pop 的时候输出，就得到了一种切割三角形的顺序。

当 $n=3$ 的时候要特判，因为只有一个三角形，这个时候它的度数为 $0$。 

具体实现详见代码。

## 参考代码


```cpp
#include<bits/stdc++.h>
using namespace std;
namespace YunLuo
{
    namespace IO
    {
        const int MAX_SIZE=1<<20;
        char buf[MAX_SIZE],*p1,*p2;
        #define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,MAX_SIZE,stdin),p1==p2)?EOF:*p1++)
        char pbuf[MAX_SIZE],*pp=pbuf;
        inline void push(const char ch){if(pp-pbuf==MAX_SIZE) fwrite(pbuf,1,MAX_SIZE,stdout),pp=pbuf;*pp++=ch;}
        #define putchar(x) push(x)
        inline void flush(){fwrite(pbuf,1,pp-pbuf,stdout);pp=pbuf;}
        
        inline char read(char& x){for(x=getchar();x<'!';x=getchar());return x;}
        template<typename T> inline T read(T& x)
        {
            static char ch=getchar();x=0;
            while(!isdigit(ch)) ch=getchar();
            while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
            return x;
        }
        inline void print(const char x){putchar(x);}
        template<typename T> inline void print(T x)
        {
            static short stk[20],top=0;
            do stk[top++]=x%10,x/=10;while(x);
            while(top) putchar(stk[--top]^48);
        }
        
        template<typename T,typename... Args>inline T read(T& x,Args&...args){read(x);read(args...);return x;}
        template<typename T>inline void print(const T x,const char ch){print(x);putchar(ch);}

    #undef getchar
    #undef putchar
    }using IO::read;using IO::print;
    #define rg register
    
    const int N=1e5+5;
    int n;

    struct EDGE
    {
        struct edge{int to,nxt;}e[N<<1];int head[N],cnt;
        inline void addedge(const int u,const int v){e[++cnt]={v,head[u]};head[u]=cnt;}
        inline void add(const int u,const int v){addedge(u,v);addedge(v,u);}
        inline void clear(const int k){for(int i=1;i<=k;++i) head[i]=0;cnt=0;}
    }E,S;

    void dfs(const int u,const int fa)
    {
        if(u==1&&fa) return ;
        print(u,' ');
        for(int i=S.head[u],v;i;i=S.e[i].nxt)
        {
            v=S.e[i].to;if(v==fa) continue;
            dfs(v,u);break;
        }
    }

    int du[N];
    map<pair<int,int>,int>mp;
    inline void check(const pair<int,int> x,const int u)
    {
        if(mp.count(x)) E.add(mp[x],u),++du[mp[x]],++du[u],mp.erase(x);
        else mp[x]=u;
    }
    queue<int>q;
    inline void topo()
    {
        for(int i=1;i<=n-2;++i) if(du[i]==1) q.push(i);
        int u;
        while(!q.empty())
        {
            print(u=q.front(),' ');q.pop();
            for(int i=E.head[u],v;i;i=E.e[i].nxt)
            {
                v=E.e[i].to;
                if((--du[v])==1) q.push(v);
            }
        }
    }
    inline void solve()
    {
        int T;read(T);
        while(T--)
        {
            read(n);
            if(n==3)
            {
                int a,b,c;read(a,b,c);
                print(1,' '),print(2,' '),print(3,'\n');
                print(1,'\n');
                continue;
            }

            for(int i=1,a,b,c;i<=n-2;++i)
            {
                read(a,b,c);
                check({min(a,b),max(a,b)},i);
                check({min(a,c),max(a,c)},i);
                check({min(b,c),max(b,c)},i);
            }

            for(map<pair<int,int>,int>::iterator it=mp.begin();it!=mp.end();++it)
                S.add(it->first.first,it->first.second);
            mp.clear();

            dfs(1,0),print('\n');
            topo(),print('\n');
            E.clear(n-2);S.clear(n);
        }
        IO::flush();
    }
}

int main()
{
    #ifndef ONLINE_JUDGE
    freopen("awa.in","r",stdin);
    freopen("awa.out","w",stdout);
    #endif

    YunLuo::solve();
    return 0;
}
```

---

## 作者：Mortidesperatslav (赞：2)

打 duel 10min 秒了做法，花了 1h 把这题调过了（可能是因为刚开始插件挂掉看错题了），于是来写个题解。

一个显然的性质是，一条切割产生的边会同时出现在两个三角形里，而一条原多边形上的边不会。

于是我们可以统计多边形上的边，写一个 dfs 找环即可。

第二问略微困难一些，我们继续找性质。

显然一定有一个三角形满足其中一个顶点只出现一次，只有这样的三角形才能成为第一个切割的。

仔细想一想，这不就是一个拓扑排序吗？

于是对于每个三角形跑拓扑排序，不停删度数，统计度数为 $1$ 的点就好了。

下面是可可爱爱的代码喵：

```cpp
#include<bits/stdc++.h>
using namespace std;
int T, n, cnt, cir[100005], deg[100005], tar, u[100005], v[100005], w[100005];
vector<pair<int, int> > vec;
vector<int> G[100005], G2[100005], tri[100005];
map<pair<int, int>, int> mp;
vector<int> ans;
queue<int> q;
bool vis[100005];
void pins(int x, int y){
	vec.emplace_back(make_pair(x, y));
	vec.emplace_back(make_pair(y, x));
}
void genmp(int x, int y){
	mp[make_pair(x, y)]++;
	mp[make_pair(y, x)]++;
	G2[x].emplace_back(y);
	G2[y].emplace_back(x);
}
void gcirc(int u, int fa){
	if (cnt == n)
		return;
	cir[++cnt] = u;
	for (auto v : G[u])
		if (v != fa)
			gcirc(v, u);
}
void ddel(int u){
	deg[u]--;
	if (deg[u] == 1){
		int fnd = 0;
		for (auto v : tri[u]){
			if (!vis[v]){
				fnd = v;
				break;
			}
		}
		if (fnd){
			q.push(fnd);
			vis[fnd] = 1;
		}
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> T;
	while (T--){
		cnt = 0;
		mp.clear();
		vec.clear();
		cin >> n;
		for (int i = 1; i <= n; i++){
			G[i].clear();
			G2[i].clear();
			vis[i] = 0;
			deg[i] = 0;
			tri[i].clear();
			cir[i] = 0;
		}
		tar = 0;
		for (int i = 1; i <= n - 2; i++){
			cin >> u[i] >> v[i] >> w[i];
			tri[u[i]].emplace_back(i);
			tri[v[i]].emplace_back(i);
			tri[w[i]].emplace_back(i);
			deg[u[i]]++;
			deg[v[i]]++;
			deg[w[i]]++;
			if (!mp[make_pair(u[i], v[i])])
				pins(u[i], v[i]);
			if (!mp[make_pair(v[i], w[i])])
				pins(v[i], w[i]);
			if (!mp[make_pair(u[i], w[i])])
				pins(u[i], w[i]);
			genmp(u[i], v[i]);
			genmp(v[i], w[i]);
			genmp(u[i], w[i]);
		}
		for (auto tmp : vec)
			if (mp[tmp] == 1){
				G[tmp.first].emplace_back(tmp.second);
				G[tmp.second].emplace_back(tmp.first);
			}
		gcirc(1, G[1][0]);
		for (int i = 1; i <= n; i++)
			cout << cir[i] << " ";
		cout << "\n";
		for (int i = 1; i <= n; i++)
			if (deg[i] == 1 && ! vis[tri[i][0]]){
				tar = i;
				q.push(tri[i][0]);
				vis[tri[i][0]] = 1;
			}
		while (!q.empty()){
			int U = q.front();
			q.pop();
			cout << U << " ";
			ddel(u[U]);
			ddel(v[U]);
			ddel(w[U]);
		}
		cout << "\n";
		while (!q.empty())
			q.pop();
		ans.clear();
	}
	return 0; 
}
```

后记：被 @[luogu_gza](https://www.luogu.com.cn/user/301255) 带飞了，gza 我爱你/qq

---

## 作者：George1123 (赞：2)


更木棒的体验 $\to $ [`George1123`](https://www.cnblogs.com/George1123/p/13695150.html)

---
## 题面

> [CF1282E The Cake Is a Lie](https://www.luogu.com.cn/problem/CF1282E)

> $T$ 组测试数据。每次给一个 $n$ 边形的三角剖分，求节点顺序和剖分顺序。

> 数据范围：$3\le n\le 10^5$，$\sum n\le 10^5$。

---
## 蒟蒻解

这题在炫酷的代码和外表下是一个大水题。

对于每一个剖下来的三角形的边，要么是原多边形的边，要么是割的边。

多边形的边在所有三角形的边中出现 $1$ 次，割边在所有三角形中出现 $2$ 次。

所以用 `map` 记录每条边的出现次数。

然后从一个三角形出发，然后用 `dfs` 合并上出现 $2$ 次的边的三角形即可。

对于第一个询问可以用一个环状链表，第二个可以回溯加 `vector`。

为了~~不~~方便，代码中从一个有两条原多边形的边的三角形开始，这样每次就最多有两边要合并三角形了。

---
## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

//Start
typedef long long ll;
typedef double db;
#define mp(a,b) make_pair((a),(b))
#define x first
#define y second
#define be(a) (a).begin()
#define en(a) (a).end()
#define sz(a) int((a).size())
#define pb(a) push_back(a)
#define R(i,a,b) for(int i=(a),I=(b);i<I;i++)
#define L(i,a,b) for(int i=(b)-1,I=(a)-1;i>I;i--)
const int iinf=0x3f3f3f3f;
const ll linf=0x3f3f3f3f3f3f3f3f;

//Data
const int N=1e5;
int n,nex[N],ea[N-2],eb[N-2],ec[N-2];
bool vis[N]; vector<int> ans;
map<pair<int,int>,vector<pair<int,int>>> mp;
#define pa(x,y) mp(min(x,y),max(x,y))
#define an(x,y) mp[pa(x,y)]

//Main
void solve(pair<int,int> e){
	if(nex[e.y]==e.x) swap(e.x,e.y); 
	vector<pair<int,int>> tv=an(e.x,e.y);
	int ez=vis[tv[0].x]?tv[1].x:tv[0].x; 
	int et=vis[tv[0].x]?tv[1].y:tv[0].y;
	vis[ez]=true,nex[e.x]=ez,nex[ez]=e.y;
	if(sz(an(e.x,ez))>=2) solve(mp(e.x,ez));
	if(sz(an(e.y,ez))>=2) solve(mp(e.y,ez));
	ans.pb(et);
}
void Main(){
	cin>>n,ans.clear();
	fill(nex,nex+n,-1);
	fill(vis,vis+n,false);
	if(n==3){
		cin>>ea[0]>>eb[0]>>ec[0];
		cout<<"1 2 3\n1\n";
		return;
	}
	mp.clear();
	R(i,0,n-2){
		cin>>ea[i]>>eb[i]>>ec[i];
		--ea[i],--eb[i],--ec[i];
		an(ea[i],eb[i]).pb(mp(ec[i],i));
		an(ea[i],ec[i]).pb(mp(eb[i],i));
		an(eb[i],ec[i]).pb(mp(ea[i],i));
	}
	int s=-1; pair<int,int> e(-1,-1);
	R(i,0,n-2){
		int cnt=0;
		if(sz(an(ea[i],eb[i]))==2) cnt++,e=pa(ea[i],eb[i]);
		if(sz(an(ea[i],ec[i]))==2) cnt++,e=pa(ea[i],ec[i]);
		if(sz(an(eb[i],ec[i]))==2) cnt++,e=pa(eb[i],ec[i]);
		if(cnt==1){s=i;break;}
	}
	nex[ea[s]]=eb[s],nex[eb[s]]=ec[s],nex[ec[s]]=ea[s];
	vis[ea[s]]=vis[eb[s]]=vis[ec[s]]=true,ans.pb(s);
	solve(e);
	int now=0;
	R(i,0,n) cout<<now+1<<' ',now=nex[now];cout<<'\n';
	for(int x:ans) cout<<x+1<<' ';cout<<'\n';
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int tn; cin>>tn;
	R(ta,0,tn) Main();
	return 0;
}
```

---
**祝大家学习愉快！**

---

## 作者：HPXXZYY (赞：1)

$\color{blue}{\texttt{[Solution]}}$

我们把三角形的边分成两种：一种是原来的多边形的边（称为原边），一种是因为分割而多出来的新边（称为新边）。

我们发现，在三角形的所有的边中，原边只会出现一次，新边会且只会出现两次。这是解题的关键之一。

利用这个性质，我们可以轻易地求出 $p$。我们可以通过边出现的次数轻易地确定哪些边是原边。原边确定了，整个图形不就确定了吗？按照你喜欢的顺序，输出就可以了嘛。

解题的关键之二是，三角形的所有顶点里，一定有且只有两个点，它们只出现了一次。它们中必然会有一个是第一次割的三角形的顶点之一。

所以求 $q$ 就很简单了。我们把从只出现了一次的顶点开始，不断确定三角形的切割顺序。这个过程，很像拓扑排序（其实跟拓扑排序没什么区别，看代码就恍然大悟了，语言反而不好讲清楚）。

但是还是那句话，口头 AC 不等于代码 AC。这道题还是有很多细节的。具体地，看代码就好了。

但是还是有一点要说的，像 CF 这种极多测的题目，最好不要用 `memset` 清空，否则容易 T。

$\color{blue}{\texttt{[code]}}$

```cpp
const int N=1e5+100;

vector<int> tarnum[N];
int n,ans[N],connect[N][2];
pair<int,int> edge[N*3];
int cnt,k[N],ind[N],a[N],b[N],c[N];
bool vis[N],out[N];

void outputp(int u){
	printf("%d ",u);
	out[u]=false;
	if (out[connect[u][0]])
		outputp(connect[u][0]);
	if (out[connect[u][1]])
		outputp(connect[u][1]);
}//输出 p 数组

void outputq(){
	for(int i=1;i<n-2;i++)
		printf("%d ",ans[i]);
	for(int i=1;i<=n-2;i++)
		if (vis[i]) printf("%d",i);
}//输出 q 数组

int main(){
	for(int T=1,Q=read();T<=Q;T++){
		n=read();cnt=0;
		
		for(int i=1;i<=n;i++)
			tarnum[i].clear();
		for(int i=1;i<=n;i++)
			ind[i]=ans[i]=0;
		
		for(int i=1;i<=n-2;i++){
			int x=read(),y=read(),z=read();
			
			if (x>y) swap(x,y);
			if (x>z) swap(x,z);
			if (y>z) swap(y,z);//方便确定是否是一样的边
			
			tarnum[x].push_back(i);
			tarnum[y].push_back(i);
			tarnum[z].push_back(i);
			
			edge[++cnt]=make_pair(x,y);
			edge[++cnt]=make_pair(x,z);
			edge[++cnt]=make_pair(y,z);
			
			++ind[x];++ind[y];++ind[z];
			
			a[i]=x;b[i]=y;c[i]=z;
		}
		
		sort(edge+1,edge+cnt+1);
		edge[0]=edge[cnt+1]=make_pair(0,0);//注意这里，否则你会在 Test 2 WA
		
		memset(k,0,sizeof(k));
		for(int i=1;i<=cnt;i++)
			if (edge[i]!=edge[i-1]&&edge[i]!=edge[i+1]){
				int u=edge[i].first,v=edge[i].second;
				connect[u][k[u]++]=v;
				connect[v][k[v]++]=u;
			}
		
		register int tot=0;
		
		queue<int> q;
		for(int i=1;i<=n;i++)
			if (ind[i]==1) q.push(i);
		for(int i=1;i<=n;i++)
			vis[i]=out[i]=true;
		for(int i=1;i<n-2;i++){
			int u=q.front();q.pop();
			for(int i=0;i<(int)tarnum[u].size();i++)
				if (vis[tarnum[u][i]]){
					int t=tarnum[u][i];
					ans[++tot]=t;vis[t]=false;
					
					if (a[t]!=u&&(--ind[a[t]])==1) q.push(a[t]);
					if (b[t]!=u&&(--ind[b[t]])==1) q.push(b[t]);
					if (c[t]!=u&&(--ind[c[t]])==1) q.push(c[t]);
					
					break;
				}
		}//拓扑排序，应该是比较好理解的
		
		outputp(1);
		printf("\n");
		outputq();
		printf("\n");
	}
	
	return 0;
}
```

>> 打代码，一定要注意细节。
>> 
>> 口头 AC 真的不等于代码 AC！

---

## 作者：chenxia25 (赞：1)

在机房和 Alex_Wei 无聊做 2500 的题，做不动然后做这个 2400 的题。然后吊打他了，他到 8:00 下课还没做出来，而我则在 8:01 AC 了。吊打 2512 GM，爽（

学校 407 机房电脑上竟然没有 devc++，于是代码是在 CF 上的 custom test 里写的/kk

---

**[Portal](https://www.luogu.com.cn/problem/CF1282E)**

注意到，对于任意一种三角剖分方法，一定有一个三角形是连接相邻三个顶点的，这是异常显然的。考虑从这个三角形入手，显然这个三角形连接的三个点中间那个只会在共 $3(n-2)$ 个数中出现一遍。于是我们可以找到这个出现一遍的点（如果有多个则选择任意一个），将这个三角形删掉，这样得到了一个大小为 $n-1$ 的多边形，咦，可以顺着这个思路归纳下去了。

就一直删直到大小为 $3$ 为止。那么剖分顺序显然就是删除顺序。至于顶点顺序，考虑若 $n-1$ 的答案是序列 $a$，然后删掉的那个三角形从左到右分别是 $x,y,z$。那么显然在 $a$ 中 $x,z$ 是（环形）相邻的，那么只需要将 $y$ 插入它们两个之间就可以得到 $n$ 的顶点顺序。

接下来考虑实现。难点在于如何每次快速找到仅出现一次的点，和如何快速在两个数中间插入一个数。

- 如何每次快速找到仅出现一次的点：考虑类似拓扑排序的流程，维护一个队列，里面装当前没被处理过的仅出现一次的点。然后用当前点去更新别人出现次数，如果有被减成 $1$ 的就压入。由于保证有解，所以肯定能进行到最后。
- 如何快速在两个数中间插入一个数：考虑暴力平衡树（大雾）。考虑链表。但是链表不支持随机访问啊，没关系，你会发现就算支持随机访问你也不会做。注意到你不需要根据下标访问，你只需要根据值来访问（你需要找到 $x$ 和 $z$），而值所对应地址显然是不会变的，于是每插入一个值就存下它的地址就好了。

线性。

（发现缩进是空鸽哦）

```cpp
#include<bits/stdc++.h>
using namespace std;
#define mp make_pair
#define X first
#define Y second
#define pb push_back
const int N=100000;
int n;
int a[N+1],b[N+1],c[N+1];
vector<int> hav[N+1];
bool del[N+1];
int cnt[N+1];
vector<pair<int,pair<int,int> > > v;
list<int>::iterator it[N+1];
list<int>::iterator operator+(list<int>::iterator x,int){return ++x;}
void mian(){
    cin>>n;
    //clear
    for(int i=1;i<=n;i++)hav[i].clear();
    memset(del,0,sizeof(del)),memset(cnt,0,sizeof(cnt));
    v.clear();
    for(int i=1;i<=n-2;i++)
        scanf("%d%d%d",a+i,b+i,c+i),
        cnt[a[i]]++,cnt[b[i]]++,cnt[c[i]]++,
        hav[a[i]].pb(i),hav[b[i]].pb(i),hav[c[i]].pb(i);
    queue<int> q;
    for(int i=1;i<=n;i++)if(cnt[i]==1)q.push(i);
    vector<int> ans2;
    for(int i=1;i<n-2;i++){
        int x=q.front();
        q.pop();
        for(int i=0;i<hav[x].size();i++)if(!del[hav[x][i]]){
            int fd=hav[x][i];
            ans2.pb(fd);
            if(b[fd]==x)swap(a[fd],b[fd]);
            else if(c[fd]==x)swap(a[fd],c[fd]);
            v.pb(mp(x,mp(b[fd],c[fd])));
            del[fd]=true;
            if(--cnt[b[fd]]==1)q.push(b[fd]);
            if(--cnt[c[fd]]==1)q.push(c[fd]);
            break;
        }
    }
    list<int> lis;
    for(int i=1;i<=n-2;i++)if(!del[i]){
        ans2.pb(i);
        lis.pb(a[i]),it[a[i]]=--lis.end();
        lis.pb(b[i]),it[b[i]]=--lis.end();
        lis.pb(c[i]),it[c[i]]=--lis.end();
    }
    for(int i=n-4;~i;i--){
        int x=v[i].X,l=v[i].Y.X,r=v[i].Y.Y;
        if(it[l]+1==it[r]||it[l]==--lis.end()&&it[r]==lis.begin())
            lis.insert(it[l]+1,x),it[x]=it[l]+1;
        else lis.insert(it[r]+1,x),it[x]=it[r]+1;
    }
    for(list<int>::iterator i=lis.begin();i!=lis.end();i++)printf("%d ",*i);puts("");
    for(int i=0;i<ans2.size();i++)printf("%d ",ans2[i]);puts("");
}
int main(){
    int testnum;
    cin>>testnum;
    while(testnum--)mian();
    return 0;
}
```

---

