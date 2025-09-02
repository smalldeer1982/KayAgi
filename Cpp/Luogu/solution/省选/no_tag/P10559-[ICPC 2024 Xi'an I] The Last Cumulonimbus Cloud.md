# [ICPC 2024 Xi'an I] The Last Cumulonimbus Cloud

## 题目描述

每年四月，这座城市总是被积雨云笼罩。

这座城市由 $n$ 座建筑和 $m$ 条双向街道连接。为了方便人们出行，任何两座建筑都可以通过街道直接或间接到达。同时，没有街道连接同一座建筑，并且每对建筑之间最多有一条街道连接。

由于城市布局不太庞大，这座城市的生活节奏非常缓慢。

具体来说，如果我们将这座城市视为无向图 $G$，则保证在该图的任何非空子图中，至少有一座建筑在子图内连接了最多 10 条街道。

雨不停地下，积雨云的数量不断增加。起初，第 $i$ 座建筑上方有 $a_i$ 个积雨云，但在接下来的 $q$ 天中，每天会发生以下两种事件之一：

- $\text{1 x v}$ 表示在第 $x$ 座建筑上方增加了 $v$ 个积雨云。
- $\text{2 x}$ 表示需要报告直接连接到建筑 $x$ 的所有建筑上方的积雨云总数。

## 说明/提示

（由 ChatGPT 4o 翻译）

## 样例 #1

### 输入

```
4 6 10
2 4
2 3
4 3
3 1
4 1
2 1
0
7
1
6
2 4
2 2
1 3 3
2 1
1 1 9
2 4
2 2
1 3 6
2 4
2 2```

### 输出

```
8
7
17
20
19
26
25```

# 题解

## 作者：dlhham (赞：9)

给一个此题能过，且任意情况下都不比根号分治差的做法：

思路跟正解一样，我们给边定向。对于每次修改，我们把这个点的出边的答案更新上这个值，对于每次查询，我们用这个点的答案，加上其所有出边的答案即可。

关键是，如何定向，能使得每个点的出边个数尽量均匀？我们考虑对每一条边 $u,v$，假设其度数分别是 $deg_u,deg_v$， 那么，我们以 $\frac{deg_v}{deg_u+deg_v}$ 的概率让这条边从 $u$ 连向 $v$，反之从 $v$ 连向 $u$， 这样，每个点出边数的期望是 $D_u=\sum_{v}\frac{deg_v}{deg_u+deg_v}$。 

```cpp
#include <bits/stdc++.h>
#define maxn 1000005
#define ll int
#define mod 998244353
using namespace std;
mt19937 rnd(time(NULL)^clock());
ll rad(ll x,ll y){
	return rnd()%(y-x+1)+x;
}
int n,m,q,B;
ll V[maxn],ans[maxn],deg[maxn];
basic_string<int> edge[maxn],da[maxn];
struct IO{
    static const int S=1<<21;
    char buf[S],*p1,*p2;int st[105],Top;
    ~IO(){clear();}
    inline void clear(){fwrite(buf,1,Top,stdout);Top=0;}
    inline void pc(const char c){Top==S&&(clear(),0);buf[Top++]=c;}
    inline char gc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;}
    inline IO&operator >> (char&x){while(x=gc(),x==' '||x=='\n'||x=='\r');return *this;}
    template<typename T>inline IO&operator >> (T&x){
        x=0;bool f=0;char ch=gc();
       while(!isdigit(ch)){if(ch=='-') f^=1;ch=gc();}
        while(isdigit(ch)) x=(x<<3)+(x<<1)+ch-'0',ch=gc();
        f?x=-x:0;return *this;
    }
    inline IO&operator << (const char c){pc(c);return *this;}
    template<typename T>inline IO&operator << (T x){
        if(x<0) pc('-'),x=-x;
        do{st[++st[0]]=x%10,x/=10;}while(x);
        while(st[0]) pc('0'+st[st[0]--]);return *this;
    }
}fin,fout;
int main()
{
   fin>>n>>m>>q;
	int u,v;
	for (int i=1;i<=m;i++)
	{
	   fin>>u>>v;
	   if (u>v) swap(u,v);
		edge[u]+=v;
		deg[u]++; deg[v]++;
	}
	for (int i=1;i<=n;i++) fin>>V[i];
	for (int i=1;i<=n;i++)
	{
		for (int j:edge[i])
		{
			if (rad(1,deg[i]+deg[j])<=deg[i])//j->i 
			{
				da[j]+=i;
				ans[i]+=V[j];
			}
			else
			{
				da[i]+=j;
				ans[j]+=V[i];
			}
		}
	}
	int opt,x;
	ll y;
	while (q--)
	{
	   fin>>opt>>x;
		if (opt==2)
		{
			ll ret=ans[x];
			for (int j:da[x]) 
			{
				ret+=V[j];
			}
			fout<<ret;
			fout<<'\n';
		}
		else
		{
		   fin>>y;
			for (int j:da[x])
				ans[j]+=y;
			V[x]+=y;
		}
	}
	return 0;
}

```

---

## 作者：win114514 (赞：7)

好好玩的题。

### 思路

对于一个图上邻域问题，我们有一个很经典的做法：根号分治。

考虑根号分治的本质是什么。

我们把点分成两类，平衡每一种点的时间，也就是度数大的与度数小的点。

所以对于这道题，我们有了更加好的做法。

发现题目给的图的性质就是一个天然的划分方案。

我们每次找到图中度数最小的点，它一定对应着小于等于 $10$ 个点。

然后我们把它删掉，循环往复的做此操作。

那么每个点都会将自己的邻居分为我对应邻居与邻居对应我。

在修改时，我们把所有对应的点的答案直接加上。

在查询时，我们也只要查这个点对应的点的答案在加上自己的答案即可。

也就是设 $sn_x$ 为 $x$ 对应的点，$a_x,b_x$ 分别为权值与累加的答案。

修改 $x$，则 $a_x\rightarrow a_x+v,i\in sn_x,b_i\rightarrow b_i+v$。

查询 $x$，回答 $b_x+\sum_{i\in sn_x} a_i$。

时间复杂度：$O(10q+n+m)$。

### Code

本题稍微有一点卡常，所以记得做常数优化。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define fro(i, x, y) for (int i = (x); i <= (y); i++)
#define pre(i, x, y) for (int i = (x); i >= (y); i--)

const int N = 300010;

int n, m, q, a[N], b[N], du[N], vs[N];

vector<int> to[N];
vector<int> sn[N];

inline int read() {
  int asd = 0; char zxc;
  while (!isdigit(zxc = getchar()));
  while (isdigit(zxc)) asd = asd * 10 + zxc - '0', zxc = getchar();
  return asd;
}

signed main() {
  n = read(), m = read(), q = read();
  fro(i, 1, m) {
    int x = read(), y = read();
    to[x].push_back(y);
    to[y].push_back(x);
    du[x]++, du[y]++;
  }
  queue<int> res;
  fro(i, 1, n) if (du[i] <= 10) res.push(i);
  while (res.empty() == 0) {
    int x = res.front(); res.pop(), vs[x] = 1;
    for (auto i : to[x]) {
      if (vs[i]) continue;
      sn[x].push_back(i);
      if (--du[i] == 10) res.push(i);
    }
  }
  fro(i, 1, n) {
    a[i] = read();
    for (auto j : sn[i]) b[j] += a[i];
  }
  fro(i, 1, q) {
    int op = read(), x, v;
    if (op == 1) {
      x = read(), v = read(), a[x] += v;
      for (auto j : sn[x]) b[j] += v;
    } else {
      x = read(); int res = b[x];
      for (auto j : sn[x]) res += a[j];
      printf("%d\n", res);
    }
  }
  return 0;
}
```

---

## 作者：honglan0301 (赞：4)

我好像秒了。

## 分析

首先显然有两种暴力做法，一种是 $O(1)$ 修改、$O(deg)$ 查询，另一种是 $O(deg)$ 修改、$O(1)$ 查询。

- 那么在一般图上，我们可以结合两种做法对点的度数进行根号分治，对度数小的点跑第一种暴力，度数大的跑第二种，时间复杂度 $O(q\sqrt m)$，无法通过本题。

考虑换一种思路。我们注意到，以上的根分本质上是在全局中对点分类，而题目中图的特殊性质启示我们也可以对每个点的邻边分类：

- 把每条边定向，使得出边用第一种暴力、入边用第二种暴力（即修改和查询时都只关心自己和出边的贡献）。

- 在一般图上，可以令每条边由度数小的点指向度数大的点，时间复杂度同样是 $O(q\sqrt m)$。

- 而在本题中，可以用类似拓扑排序的方式，不断找到一个度数 $\leq B$ 的点删去，并令每条边由较早删去的点指向较晚删去的点，那么时间复杂度为 $O(qB)$，在本题中 $B=10$ 即可，因为题目保证 "for any non empty subgraph in this graph, there is at least one building inside it that connects up to 10 streets within the subgraph"，可以通过。

## 代码

核心部分如下。

```cpp
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define int long long
int n,m,q,op,u,v,a[300005],b[300005],deg[300005],vis[300005];
vector <int> e[300005],g[300005];

void init()
{
	queue <int> Q;
	for(int i=1;i<=n;i++) if(deg[i]<=10) Q.push(i);
	while(!Q.empty())
	{
		int nr=Q.front(); vis[nr]=1; Q.pop();
		for(auto i:e[nr])
		{
			if(vis[i]) continue;
			g[nr].pb(i); b[i]+=a[nr]; deg[i]--; if(deg[i]==10) Q.push(i);
		}
	}
}

signed main()
{
	cin>>n>>m>>q;
	for(int i=1;i<=m;i++) cin>>u>>v,e[u].pb(v),e[v].pb(u),deg[u]++,deg[v]++;
	for(int i=1;i<=n;i++) cin>>a[i];
	init();
	while(q--)
	{
		cin>>op;
		if(op==1)
		{
			cin>>u>>v; 
			a[u]+=v;
			for(auto i:g[u]) b[i]+=v;
		}
		else
		{
			cin>>u;
			int ans=b[u];
			for(auto i:g[u]) ans+=a[i];
			cout<<ans<<endl;
		}
	}
}
```

---

## 作者：Larunatrecy (赞：2)

不考虑题目保证的性质，本题是个经典的图上邻域问题，有众所周知的根号分治 $O(q\sqrt m)$ 做法。

考虑这个做法的本质：给每条边定向，维护每个点 $x$ 所有入边的权值和 $s_x$，这样修改时只需要修改出边连向的点的 $s_y$，查询时只需要用 $s_x$ 加上出边连向的点的权值即可。

在本题中，容易证明可以存在一种每次删掉度数不超过 $k$ 的点把图删空的方式（$k=10$），我们把边按照删除顺序定向，即可让每个点的出边不超过 $k$ 条，复杂度即为 $O(n+m+kq)$。

更进一步，我们可以离线下来，求出每个点被询问/修改的总次数，每条边定向为这个次数更小的一边，可以证明这个的操作次数是不超过 $O(kq)$ 的，这个做法更好写且常数更小。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 3e5+7;
const int M = 3e6+7;
int n,m,q;
int u[M],v[M],sum[N],cnt[N];
int a[N],qc[M],qx[M],qv[M];
vector<int> T[N];
struct IO{
    static const int S=1<<21;
    char buf[S],*p1,*p2;int st[105],Top;
    ~IO(){clear();}
    inline void clear(){fwrite(buf,1,Top,stdout);Top=0;}
    inline void pc(const char c){Top==S&&(clear(),0);buf[Top++]=c;}
    inline char gc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;}
    inline IO&operator >> (char&x){while(x=gc(),x==' '||x=='\n'||x=='\r');return *this;}
    template<typename T>inline IO&operator >> (T&x){
        x=0;bool f=0;char ch=gc();
       while(!isdigit(ch)){if(ch=='-') f^=1;ch=gc();}
        while(isdigit(ch)) x=(x<<3)+(x<<1)+ch-'0',ch=gc();
        f?x=-x:0;return *this;
    }
    inline IO&operator << (const char c){pc(c);return *this;}
    template<typename T>inline IO&operator << (T x){
        if(x<0) pc('-'),x=-x;
        do{st[++st[0]]=x%10,x/=10;}while(x);
        while(st[0]) pc('0'+st[st[0]--]);return *this;
    }
}fin,fout;
int main()
{
    fin>>n>>m>>q;
    for(int i=1;i<=m;i++)fin>>u[i]>>v[i];
    for(int i=1;i<=n;i++)fin>>a[i];
    for(int i=1;i<=q;i++)
    {
        fin>>qc[i]>>qx[i];
        if(qc[i]==1)fin>>qv[i];
        cnt[qx[i]]++;
    }
    for(int i=1;i<=m;i++)
    {
        if(cnt[u[i]]>cnt[v[i]])swap(u[i],v[i]);
        T[u[i]].push_back(v[i]);
        sum[v[i]]+=a[u[i]];
    }
    for(int i=1;i<=q;i++)
    {
        int x=qx[i];
        if(qc[i]==1)
        {
            a[x]+=qv[i];
            for(int y:T[x])sum[y]+=qv[i];
        }
        else
        {
            int res=sum[x];
            for(int y:T[x])res+=a[y];
            fout<<res;
            fout.pc('\n');
        }
    }
    return 0;
}
```

---

## 作者：bluewindde (赞：1)

学长讲课讲到了，是很有意思的一道题。

这种题有一个常见的根号分治做法：设 $d$ 为度数，显然有 $O(1)$ 修改单点，$O(d)$ 查询邻域和 $O(d)$ 修改邻域，$O(1)$ 查询单点两种暴力。对度数大于 $\sqrt n$ 的点使用前者，度数小于等于 $\sqrt n$ 的点使用后者，可以做到 $O(m \sqrt n)$ 的时间复杂度。

这种做法的本质让每条边是由度数小的点向度数大的点定向，查询一个点的邻域时将入边集合（提前处理）与出边集合（查询时遍历）的答案相加。因为根号分治的特性，这出边集合的大小不超过 $O(\sqrt n)$，于是保证复杂度正确。

本题中考虑类似的定向，由于题目所给的图的特性：每个非空子图都至少有一个点的度数不超过 $10$。可以每次选取当前度数最小的点删去，直到把图删空，会得到删除点的顺序，每条边由先删除的点向后删除的点定向，可以保证每个点的出边不超过 $10$ 条，复杂度正确。

当然，也有一种“启发式定向”的策略（人类智慧）：以 $p = \dfrac {d_v} {d_u + d_v}$ 为由点 $u$ 向点 $v$ 定向的概率，随机数操作一下，就结束了。原理是出边数量一定，我们希望让度数小的节点承担更多的出边，以此得到相对均衡的时间开销。期望复杂度正确，但常数有些大。

既然说到了均衡开销，[这篇题解](https://www.luogu.com.cn/article/29aq2kgc)给出了一个美妙的做法：记录每个点被操作的次数，由次数小的向次数大的定向。复杂度非常正确，常数非常小。

---

## 作者：fish_love_cat (赞：0)

暴力是好做的。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct fish{
    int id,x,siz;
};
vector<fish>ve[300005];
int a[300005];
int n,m,q;
signed main(){
    cin>>n>>m>>q;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        ve[u].push_back({v,0,ve[v].size()});
        ve[v].push_back({u,0,ve[u].size()-1});
    }
    for(int i=1;i<=n;i++){
        cin>>a[i];
        for(int j=0;j<ve[i].size();j++)
        ve[ve[i][j].id][ve[i][j].siz].x=a[i];
    }
    while(q--){
        int op;
        cin>>op;
        if(op==1){
            int x,v;
            cin>>x>>v,a[x]+=v;
            for(int i=0;i<ve[x].size();i++)
            ve[ve[x][i].id][ve[x][i].siz].x=a[x];
        }else{
            int ans=0,x;
            cin>>x;
            for(int i=0;i<ve[x].size();i++)
            ans+=ve[x][i].x;
            cout<<ans<<endl;
        }
    }
    return 0;
}
```

但最坏可以卡到 $O(qm)$，稳稳过不了。

---

发现查询或修改的点度数太多时会挂，考虑优化。

可以给边定向，让边尽可能的均匀，这样会快很多。

于是我们从度数小的点连到度数大的点，然后每个修改对于出边进行预处理，查询在预处理的基础上再处理出边，然后速度飞起过了。

尝试构造 hack，发现最坏情况下单点出边数量也应该是少于 $\sqrt m$ 的。

假定我要使某一个点定向后的边很多，那么它连出去的点必然也有比它更多的度，所以至多所连边数不超过 $\sqrt m$ 条。

所以应该是 $O(q\sqrt m)$ 的复杂度，实际跑不满。

```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int>ve[300005];
int a[300005],f[300005],u[3000005],v[3000005],anss[300005],op,x,vv,ans;
int n,m,q;
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>n>>m>>q;
    for(int i=1;i<=m;i++){
        cin>>u[i]>>v[i];
        f[u[i]]++,f[v[i]]++;
    }
    for(int i=1;i<=m;i++){
        if(f[u[i]]<f[v[i]])ve[u[i]].push_back(v[i]);
        else ve[v[i]].push_back(u[i]);
    }
    for(int i=1;i<=n;i++){
        cin>>a[i];
        for(int j=0;j<ve[i].size();j++)
        anss[ve[i][j]]+=a[i];
    }
    while(q--){
        cin>>op;
        if(op==1){
            cin>>x>>vv,a[x]+=vv;
            for(int i=0;i<ve[x].size();i++)
            anss[ve[x][i]]+=vv;
        }else{
            cin>>x;
            ans=anss[x];
            for(int i=0;i<ve[x].size();i++)
            ans+=a[ve[x][i]];
            cout<<ans<<'\n';
        }
    }
    return 0;
}
```

这个时候你看一眼数据范围，$O(q\sqrt m)$ 的复杂度，可是 $q\le2\times10^6,m\le3\times 10^6$ 啊？

虽然能过但并不是正确的复杂度，还需优化。

或者说理论复杂度比这个小，我算错了所以其实是正确的？如果是这样的拜托教教我 /kel

---

题目中有一个性质没有用到：

> 每个非空子图都至少有一个点的度数不超过 $10$。

于是有了这么一个做法，用类似于求拓扑序的方式，把度小于 $k$ 的点先加入队列，然后建边把对应点的度减掉，然后满足条件再加入队列。

由于有性质保证，所以 $k=10$ 时是可以保证把所有边定向的。

此时时间复杂度就转化为了 $O(qk)$，绝对能过了。

```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int>ev[300005];
vector<int>ve[300005];
int a[300005],f[300005],u[3000005],v[3000005],anss[300005],op,x,vv,ans;
int n,m,q,k=10;
int vis[300005];
int read(){
    int sum=0,fish=1;
    char c=getchar_unlocked();
    while((c<'0'||c>'9')&&c!='-')c=getchar_unlocked();
    if(c=='-')fish=-1,c=getchar_unlocked();
    while(c>='0'&&c<='9')sum=sum*10+(c-'0'),c=getchar_unlocked();
    return sum*fish;
}
void print(int x){
    if(x<0)putchar('-'),x=-x;
    if(x<10)putchar(x+'0');
    else print(x/10),putchar(x%10+'0');
}
signed main(){
    n=read(),m=read(),q=read();
    for(int i=1;i<=m;i++){
        u[i]=read(),v[i]=read();
        f[u[i]]++,f[v[i]]++;
        ev[u[i]].push_back(v[i]);
        ev[v[i]].push_back(u[i]);
    }
    queue<int>qu;
    for(int i=1;i<=n;i++)
    if(f[i]<=k)qu.push(i),vis[i]=1;
    while(!qu.empty()){
        int flc=qu.front();
        vis[flc]=2;
        qu.pop();
        for(int i=0;i<ev[flc].size();i++){
            if(vis[ev[flc][i]]==2)continue;
            ve[flc].push_back(ev[flc][i]);
            f[ev[flc][i]]--;
            if(vis[ev[flc][i]]==1)continue;
            if(f[ev[flc][i]]<=k)
            vis[ev[flc][i]]=1,qu.push(ev[flc][i]);
        }
    }
    for(int i=1;i<=n;i++){
        a[i]=read();
        // cout<<i<<": ";
        for(int j=0;j<ve[i].size();j++)
        anss[ve[i][j]]+=a[i];//,cout<<ve[i][j]<<' ';
        // cout<<'\n';
    }
    while(q--){
        op=read();
        if(op==1){
            x=read(),vv=read(),a[x]+=vv;
            for(int i=0;i<ve[x].size();i++)
            anss[ve[x][i]]+=vv;
        }else{
            x=read();
            ans=anss[x];
            for(int i=0;i<ve[x].size();i++)
            ans+=a[ve[x][i]];
            print(ans),puts("");
        }
    }
    return 0;
}
```

但是怎么跑的比 $O(q\sqrt m)$ 还慢啊，加了快读才过 /jy

---

