# Beautiful Graph

## 题目描述

You are given an undirected unweighted graph consisting of $ n $ vertices and $ m $ edges.

You have to write a number on each vertex of the graph. Each number should be $ 1 $ , $ 2 $ or $ 3 $ . The graph becomes beautiful if for each edge the sum of numbers on vertices connected by this edge is odd.

Calculate the number of possible ways to write numbers $ 1 $ , $ 2 $ and $ 3 $ on vertices so the graph becomes beautiful. Since this number may be large, print it modulo $ 998244353 $ .

Note that you have to write exactly one number on each vertex.

The graph does not have any self-loops or multiple edges.

## 说明/提示

Possible ways to distribute numbers in the first test:

1. the vertex $ 1 $ should contain $ 1 $ , and $ 2 $ should contain $ 2 $ ;
2. the vertex $ 1 $ should contain $ 3 $ , and $ 2 $ should contain $ 2 $ ;
3. the vertex $ 1 $ should contain $ 2 $ , and $ 2 $ should contain $ 1 $ ;
4. the vertex $ 1 $ should contain $ 2 $ , and $ 2 $ should contain $ 3 $ .

In the second test there is no way to distribute numbers.

## 样例 #1

### 输入

```
2
2 1
1 2
4 6
1 2
1 3
1 4
2 3
2 4
3 4
```

### 输出

```
4
0
```

# 题解

## 作者：LJC00118 (赞：4)

发现每条边的两个端点的数字的奇偶性一定不同

所以我们我们只要做一次 $ bfs $ 染色并判断是否能完成染色即可

假设黑点有 $ a $ 个，白点有 $ b $ 个

如果黑点是奇数，方案数是 $ 2^a $ 种，如果白点是奇数，方案数是 $ 2^b $ 种，总方案数是 $ 2^a + 2^b $ 种

然后发现整个图不一定联通

所以我们对每个联通块做一次 $ bfs $ 染色，然后把答案相乘即可

注意不能用 memset，不然 $ T $ 组数据每次 memset 一次肯定凉

```cpp
#include <bits/stdc++.h>
#define Fast_cin ios::sync_with_stdio(false), cin.tie();
#define rep(i, a, b) for(register int i = a; i <= b; i++)
#define per(i, a, b) for(register int i = a; i >= b; i--)
#define DEBUG(x) cerr << "DEBUG" << x << " >>> " << endl;
using namespace std;

typedef unsigned long long ull;
typedef long long ll;

template <typename _T>
inline void read(_T &f) {
    f = 0; _T fu = 1; char c = getchar();
    while(c < '0' || c > '9') { if(c == '-') fu = -1; c = getchar(); }
    while(c >= '0' && c <= '9') { f = (f << 3) + (f << 1) + (c & 15); c = getchar(); }
    f *= fu;
}

template <typename T>
void print(T x) {
    if(x < 0) putchar('-'), x = -x;
    if(x < 10) putchar(x + 48);
    else print(x / 10), putchar(x % 10 + 48);
}

template <typename T>
void print(T x, char t) {
    print(x); putchar(t);
}

const int N = 3e5 + 5, mod = 998244353;

inline int mul(int x, int y) { return (ll)x * y % mod; }

inline int add(int x, int y) {
    x += y;
    if(x >= mod) x -= mod;
    return x;
}

inline int fpow(int x, int y) {
    int ans = 1;
    while(y) {
        if(y & 1) ans = mul(ans, x);
        y >>= 1; x = mul(x, x);
    }
    return ans;
}

queue <int> q;
vector <int> adj[N];
int f[N];
int T, n, m, cnt1, cnt2, ans;

int main() {
    read(T); while(T--) {
        read(n); read(m); ans = 1;
        for(register int i = 1; i <= n; i++) f[i] = -1, adj[i].clear();
        for(register int i = 1; i <= m; i++) {
            int a, b; read(a); read(b);
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        for(register int i = 1; i <= n; i++) {
            if(~f[i]) continue;
            cnt1 = 1; cnt2 = 0; f[i] = 1; q.push(i);
            while(!q.empty()) {
                int u = q.front(); q.pop();
                for(register int j = 0; j < (int)adj[u].size(); j++) {
                    int v = adj[u][j];
                    if(f[v] == -1) {
                        f[v] = 3 - f[u];
                        if(f[v] == 1) cnt1++; else cnt2++;
                        q.push(v);
                    } else if(f[v] != 3 - f[u]) {
                        ans = 0; break;
                    }
                }
            }
            if(!ans) break;
            ans = mul(ans, add(fpow(2, cnt1), fpow(2, cnt2)));
        }
        print(ans, '\n');
    }
    return 0;
}
```

---

## 作者：fmj_123 (赞：4)

蒟蒻第一次通过CF D题~QAQ

言归正传。本题的大意是给每个点赋上$1$、$2$ 、$3$这三种点权之一，使得每条边所连的两个点的点权之和为奇数，问有多少种赋值方案。

首先，我们知道“奇数+偶数=奇数”。显然，**凡是能赋值为1的点一定能赋值为3**。所以其实我们对于每个点，只有赋值为奇数或偶数两种选择。**一旦一条边所连的一个点被赋值为奇数，那么另外一个点就要被赋值为偶数。**

那么，对于每个连通块，我们可以用染色法：选定一个起点先行染色，然后用搜索对每个点进行染色。如果染色出现了冲突，整张图的方案数就为$0$。

设此连通块中有$n$个点，$c1$个点被赋值成了奇数，根据乘法原理，这个连通块中赋值方案为$2^{c1}+2^{n-c1}$。（$2^{n-c1}$是因为将每个点取反依然可行）同样根据乘法原理，整张图的染色方案是每个联通块的方案数相乘之积。

对于求$2^x$，我们可以用快速幂去求。

上代码
```
#include<bits/stdc++.h>
using namespace std;
const long long mod=998244353;
int cc,to[900000],net[900000],fr[900000],q[900000],color[900000],ttt,n,m,u,v,h,t;
long long ans,cnt1;
bool vis[900000];
void addedge(int u,int v)
{
    cc++;
    to[cc]=v;net[cc]=fr[u];fr[u]=cc;
}
long long p(int x)
{
//快速幂求2^x
    long long ans=1,kk=2;
    while (x)
    {
        if (x&1) 
        {
            ans*=kk;
            ans%=mod;
        }
        kk*=kk;
        kk%=mod;
        x>>=1;
    }
    return ans;
}
int main()
{
    scanf("%d",&ttt);
    for (int tt=1;tt<=ttt;tt++)
    { 
      scanf("%d%d",&n,&m);
      for (int i=1;i<=m;i++)
      {
      	 scanf("%d%d",&u,&v);
      	 addedge(u,v);
      	 addedge(v,u);
      }
      int bb=1;ans=1;
      while (1)
      {
      	 h=1;t=1;q[1]=bb;vis[bb]=1;color[bb]=1;cnt1=1;
      	 while (h<=t)
      	 {
      	 	 for (int i=fr[q[h]];i;i=net[i])
      	 	 {
      	 	 	int y=to[i];
      	 	 	if (!vis[y])
      	 	 	{
      	 	 		color[y]=3-color[q[h]];
      	 	 		if (color[y]==1) cnt1++; 
      	 	 		q[++t]=to[i];
      	 	 		vis[y]=1;
      	 	 	}
      	 	 	else
      	 	 	{
      	 	 		if (color[y]!=3-color[q[h]]) ans=0;
      	 	 	}
      	 	 }
      	 	 h++;
      	 }
      	 ans*=(p(cnt1)%mod+p(t-cnt1)%mod)%mod;
      	 ans%=mod;
      	 for (int i=bb+1;i<=n;i++)
      	 {
      	 	 if (!vis[i]) {bb=i;break;}//寻找仍未被遍历的点
      	 }
      	 if (bb==q[1]) break;
      }
      for (int i=1;i<=n;i++)
        fr[i]=0,vis[i]=false,color[i]=0;
      cc=0;
      //多组数据，记得初始化。
      printf("%d\n",ans%mod);
    }
    return 0;
}
```

---

## 作者：轻绘 (赞：2)

# 算法

二分图染色。（跟模板差不多）

[题目](https://www.luogu.com.cn/problem/CF1093D)

[个人博客](https://www.luogu.com.cn/blog/yanhangyn/)

# 思路

根据题意，相邻点之间点权奇偶不同（相邻指有边之间相连），并且每个点的点权只有 $ 1,2,3 $ 三种情况。

**显然题目就是要我们计算满足二分图性质的图的个数。** 

[关于二分图性质](https://www.luogu.com.cn/problem/solution/P3386)

先不考虑点上点权具体情况，只将其分为奇偶进行讨论。就是一个典型的二分图染色，并记录染色种类数即可。

根据二分图染色问题，建一个队列，从任意点出发，将与其相邻的点染成与自己不同的颜色，并将他们扔入队列，一直到所有点都进入过一次队列，并且队列已经空。（若中间出现染色矛盾，即一个点在同一种情况中被染两次不同色，就是不成立的情况）

因为奇偶可以互换，成为另一种情况， $1,3$ 可以互换，有 $2^k$ 种情况。（$k$ 为点权为奇的点个数）

因此最后统计一下就可以了。不懂的可以自己手模样例。

# 代码

```
#include<bits/stdc++.h>
#define int long long
const int MAX=900000;
const int p=998244353;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-')	f=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar(); 
	}
	return x*f;
}
int h[MAX],nex[MAX],v[MAX],tot;
inline void add(int x,int y){
	nex[++tot]=h[x],h[x]=tot,v[tot]=y;
}
using namespace std;
int n,m,ans=1,t,k,all; 
int num[MAX];
bool f;
bool used[MAX];
inline void dfs(int now,int fa){
	for(int i=h[now];i;i=nex[i]){
		if(v[i]==fa)	continue;
		if(num[v[i]]==num[now]){
			f=1,k=0;
			return;
		}
		if(used[v[i]])	continue;
		used[v[i]]=1,++all;
		if(num[now]==1)	num[v[i]]=2;
		else	num[v[i]]=1,++k; 
		dfs(v[i],now);
		if(f)	return;
	}
}
int pu,w;
inline int pw(int a,int b){
	pu=1,w=a;
	while(b){
		if(b&1)	pu=(pu%p*w%p)%p;
		w=(w*w)%p;
		b>>=1;
	}
	return pu%p;
}
signed main(){
	t=read();
	//cout<<pw(2,10);
	while(t--){
		n=read(),m=read();
		for(int i=1;i<=m;++i){
			int x=read(),y=read();
			add(x,y),add(y,x);
		}
		for(int i=1;i<=n;++i){
			if(used[i])	continue;
			k=1,f=0,all=1;
			used[i]=1,num[i]=1;
			dfs(i,i);
			if(k)
				k=(pw(2,k)%p+pw(2,all-k)%p)%p;
			k=k%p;
			ans=(k%p*ans%p)%p;
		}
		for(int i=1;i<=tot;++i)
			nex[i]=0,v[i]=0;
		for(int i=1;i<=n;++i)
			h[i]=0,num[i]=0,used[i]=0;
		tot=0;
		printf("%lld\n",ans%p);
		ans=1;
	}	
	return 0;
} 
```


---

## 作者：小菜鸟111 (赞：1)

本题和[P1330](https://www.luogu.org/problemnew/show/P1330)较为相似，主要思路是染色。

对于每个联通块，记录奇数点a和偶数点b的个数，这个联通块的方案数是$a^2$+$b^2$。（每个奇数点可取1、3，奇数与偶数点可互换）

注意，图不一定联通，所以最后把每个联通块的方案数乘起来就行了。

在dfs时，若一个点被访问过且颜色和正在处理的点颜色相同，有连边则方案数为0，直接输出即可。

ps.开long long QAQ

---

## 作者：Buried_Dream (赞：0)

当一个位置涂上奇数时，与他联通的图的每个点的奇偶性都确定了。

所以可以从一个未被遍历过的连通子图开始，随便找一个点，染成白色, 那与他相连的只能是黑色了，如果遍历到一个点，与他相连的已经有了颜色，这个颜色只能是与他相反的颜色，如果相同就是无法完成题目的要求。

如果涂完色之后的白色点为 $cnt_1$ 个，黑色点为 $cnt_2$ 个。

则答案为 $2^{cnt_1} +2^{cnt_2}$。

因为一个地方涂完奇数统计完答案之后还可以再涂偶数统计答案。

这个题有个坑点就是，图不一定连通，要乘法原理把每个连通图的答案乘起来。

```cpp
/**
 *	author: TLE_Automation
 *	creater: 2022.10.20
 **/
#include<cmath>
#include<queue>
#include<cstdio>
#include<vector>
#include<bitset>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<functional>
#define int ll
#define gc getchar
using namespace std;
typedef long long ll;
const int N = 1e6 + 10;
const int mod = 998244353;
const ll inf = 0x3f3f3f3f3f3f3f3f;
#define debug cout << "i ak ioi" << "\n"
inline void print(int x) {if (x < 0) putchar('-'), x = -x; if(x > 9) print(x / 10); putchar(x % 10 + '0');}
inline char readchar() {static char buf[100000], *p1 = buf, *p2 = buf; return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;}
inline int read() { int res = 0, f = 0; char ch = gc();for (; !isdigit(ch); ch = gc()) f |= (ch == '-'); for (; isdigit(ch); ch = gc()) res = (res << 1) + (res << 3) + (ch ^ '0'); return f ? -res : res;}

int cnt1, cnt2, vis[N], f = 0;
std::vector <int> E[N];

inline int ksm (int a, int b) {
		int base = a, res = 1;
		while(b) {
			if(b & 1) res = (res * base) % mod;
			base = (base * base) % mod, b >>= 1;
		}
		return res % mod;
}

inline void dfs(int u, int fa) {
	if(f) return;
	vis[u] == 1 ? cnt1++ : cnt2++;
	for(int v : E[u]) {
		if(v == fa) continue;
		if(!vis[v]) {
			vis[v] = (vis[u] == 1) + 1;
			dfs(v, u);
		}
		else {
			if(vis[v] == vis[u]) return f = 1, void();	
			if(f) return;
		}
	}
}

void Solve() {
	
	int n = read(), m = read();
	f = 0; cnt1 = 0, cnt2 = 0;
	for(int i = 1; i <= n; i++) E[i].clear(), vis[i] = 0;
	for(int i = 1; i <= m; i++)	{
		int u = read(), v = read();
		E[u].push_back(v), E[v].push_back(u);
	}
	ll ans = 1;
	for(int i = 1; i <= n; i++) {
		if(!vis[i]) {
			cnt1 = 0, cnt2 = 0;
			vis[i] = 1;
			dfs(i, 0);
			ans = (ans * (ksm(2, cnt1) + ksm(2, cnt2)) % mod) % mod;
		}
	}
	if(f) ans = 0;
	if(!m) ans = (ksm(3, n)) % mod;
	cout << ans << "\n";
}

signed main()
{
	int T = read();
	while(T--) Solve();
	return (0 - 0);
}
```

---

## 作者：huangxianghui (赞：0)

首先二分图染色没有任何问题，正常染就完事了。

但这里有一个坑点：这个图不连通的。所以我们在染色的时候要记得染每个连通块（由于多组数据，千万不要直接全部初始化，否则TLE无理由）。

另外，因为每个点点的点权有三种（1，2，3），而一边连接的两点的点权奇偶性不同，所以二分图的一部分中（奇数）每个点都有两种选择（1，3），总数为 $2^{v_1}$（~~另一部分就一个2可以选，你想怎么干？~~）。同样的,另一部分也可以使用奇数点权，总数为 $2^{v_2}$ ，总和为 $2^{v_1}+2^{v_2}$ 
，再使用乘法原理将几个连通块的答案相乘即可（注意开头的 ans 初始化为1）。

上代码：
```
#include<bits/stdc++.h>
#define ll long long
#define f(i,a,b) for (ll i=a;i<=b;i++)
#define fx(i,a,b) for (ll i=a;i>=b;i--)
#define HgS 998244353
using namespace std;
const int maxn=3e5+10;
int t,n,m;
int l[maxn];
ll ans;
queue<int> q;
vector<int> v[maxn];
inline ll read()
{
	ll l=0,f=1;
	char c;
	while (!isdigit(c=getchar())) if (c=='-') f=-1;
	while (isdigit(c)) l=(l<<3)+(l<<1)+(c^48),c=getchar();
	return l*f;
}
ll ks(int x,int num)
{
	if (num==1) return x;
	ll sum=ks(x,num/2)%HgS;
	if (num%2) return sum*sum%HgS*x%HgS;
	else return sum*sum%HgS;
}//快速幂，记得模数和long long
void clear()
{
	queue<int> o;
	swap(q,o);
}//快速清空队列（加速+释放空间）
signed main()
{
	t=read();
	while (t--)
	{
		n=read(),m=read(),ans=1;//开头乘0WA到你欲哭无泪
		bool p=1;
		f(i,1,n) l[i]=0;
		f(i,1,n) vector<int> ().swap(v[i]);//快速清空vector（同样加速+释放空间）
      		//这里谁敢用memset？
		f(i,1,m)
		{
			int a1=read(),a2=read();
			v[a1].push_back(a2),v[a2].push_back(a1);
		}
		for (int i=1;i<=n && p;i++)
		{
			if (l[i]) continue;
			else
			{
				int v1=1,v2=0;
				clear(),q.push(i),l[i]=1;
				while (p && !q.empty())
				{
					int x=q.front();
					q.pop();
					if (v[x].size()!=0)
					{
						f(j,0,v[x].size()-1)
						{
							if (l[x]==l[v[x][j]])
							{
								p=0,printf("0\n");
								break;
							}//如果不满足二分图性质直接弹出
							if (!l[v[x][j]])
							{
								l[v[x][j]]=((l[x]==1)?2:1),q.push(v[x][j]);
								if (l[x]==1) v2++;
								else v1++;
							}
						}
					}
				}
				if (v1+v2==1) ans=ans*3%HgS;//连通块大小为1的时候特判
				else ans=ans*((ks(2,v1)+ks(2,v2))%HgS)%HgS;
			}
		}
		if (p) printf("%d\n",ans);
	}
	return 0;
}
```


---

## 作者：juju527 (赞：0)

### 二分图判定

只有三种点权，奇奇偶，要求每条边相连的点奇偶性不一样

显然只有当该图为二分图时满足，有奇环就一定不能分配出奇偶不一致

我们首先跑二分图的判定

我们考虑对于一个二分图，可能其中有很多连通块

所有连通块之间互不影响，故方案数应相乘

对于其中一个连通块，我们可以钦定左边是2右边是1或3

或者反过来

设左边点数为k1,右边k2

这一个连通块答案应该是
$$
2^{k_1}+2^{k_2}
$$
左边每个点1，3任选一次和右边每一个点1，3任选一次

这个题目恶心的地方在于如果你每次memset可能吃不消

他第22个点是300000组数据，每个数据1个点

我们就每次只清1~n的数组就好了

然后就是sb题了

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=300005,maxm=300005;
const int mod=998244353;
struct Edge{
	int to,nxt;
}e[2*maxm];
int cnt;
int head[maxm];
long long pw[maxn];
int c[maxn];
int num[2];
int read(){
	int x=0,y=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')y=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return x*y;
}
void add(int u,int v){
	e[cnt].to=v;
	e[cnt].nxt=head[u];
	head[u]=cnt++;
	return ;
}
bool dfs(int x,int co){
	num[co-2]++;
	c[x]=co;
	for(int i=head[x];i!=-1;i=e[i].nxt){
		int tmp=e[i].to;
		if(c[tmp]==co)return 1;
		if(c[tmp]==(co^1))continue;
		if(dfs(tmp,co^1))return 1;
	}
	return 0;
}
void trash(int n){
	cnt=0;
	for(int i=1;i<=n;i++)head[i]=-1;
	for(int i=1;i<=n;i++)c[i]=0;
	return ;
}
int main(){
	int tim,mxn=0;
	tim=read();
	pw[0]=1;
	memset(head,-1,sizeof(head));
	while(tim--){
		int n,m;
		long long ans=1;
		n=read();m=read();
		for(int i=mxn+1;i<=n;i++)pw[i]=pw[i-1]*2%mod;
		mxn=max(mxn,n);
		for(int i=1;i<=m;i++){
			int u,v;
			u=read();v=read();
			add(u,v);
			add(v,u);
		}
		bool flag=0;
		for(int i=1;i<=n;i++){
			if(c[i])continue;
			num[0]=num[1]=0;
			flag=dfs(i,2);
			ans=(ans*(pw[num[0]]+pw[num[1]])%mod)%mod;
			if(flag)break;
		}
		if(flag){printf("0\n");trash(n);continue;}
		printf("%d\n",ans);
		trash(n);
	}
	return 0;
}

```



---

## 作者：Lily_White (赞：0)

本题是CF EDU的D题，难度算是这个位置比较低的（哪儿有紫啊），不过还是有一些坑点在的。

注意到题目中允许你用的数字是$1,2$和$3$。而要使方案满足要求，有边相连的点权值和应该是奇数，那就只有可能是$1+2$或者$2+3$。

这样的话，如果只要给出**一种**方案，那么$1$和$3$就是等价的。问题也就转化为了把一张图红$(1,3)$，蓝$(2)$染色，使得任意两个有边连接的点颜色不同，这就是个**二分图判定**的板子了。

然后，我们需要算出所有的方案数。既然是二分图，那么对于这个无向图$G(V,E)$，$\exists A,B \subseteq V,A\cup B = V, A \cap B = \varnothing$，且对于$\forall e \in E, e.u \in A, e.v \in B$。给集合$A$中的点全部染上红色，有$2^{|A|}$种方案（因为可以填$1$或者$3$），而既可以给$A$染红，也可以给$B$染红，所以合计一共有$2^{|A|}+2^{|B|}$种方案。

题目并没有说图是连通的，因此，我们需要对每个连通分量做这种计算，并算出答案的**积**（积是因为可以把这个看作**分步计数原理**的模型，也就是说填每个连通分量是**一步**，每一步都做完才是结果）。

实现时，可以预处理出对$\forall 1 \leq i \leq 300000, i\in \mathbb{Z},  2^i$的值。

代码如下，其中变量```red```和```cerulean```（这是天蓝的意思）记录了每个连通分量的染色计数。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define LL long long
#define lsh(i) (1 << (i))
#define lshll(i) (1LL << (i))
#define repn(i, n) for (int (i) = 1; (i) <= n; (i)++)
#define rep(i, n) for (int (i) = 0; (i) < n; (i)++)
const int INF = 0x3f3f3f3f;
const int MOD = 998244353;
const long double EPS = 1e-6;
long long qread() {
	char c;
	int neg = 1;
	long long val = 0;
	while (c != '-' && !isdigit(c)) c = getchar();
	if (c == '-') c = getchar(), neg = -1;
	while (isdigit(c)) val = (val << 3) + (val << 1) + c - '0', c = getchar();
	return neg * val;
}
const int N = 300030;
int col[N], n, m, red, cerulean;bool flg = 1;
vector <int> G[N];
void dfs(int u, int nowcol) {
	col[u] = nowcol;
	if (nowcol == 0) red++;
	else if (nowcol == 1) cerulean++;
	for (auto v:G[u]) {
		if (col[v] < 0) dfs(v, nowcol ^ 1);
		else if (col[v] == nowcol) {
			flg = false;
			return;
		}
	} 
}
LL pw[N];
int main() {
	int T = qread();
	pw[0] = 1;
	repn(i, 300010) pw[i] = (pw[i - 1] << 1) % MOD;
	while (T--)  {
		n = qread(), m = qread();
		rep(i, n + 10) col[i] = -1, G[i].clear(); flg = true;
		rep(i, m) {
			int u, v;
			u = qread(); v = qread();
			--u; --v;
			G[u].pb(v);
			G[v].pb(u);
		}
		LL ans = 1;
		rep(i, n) {
			if (col[i] == -1) {
				red = cerulean = 0;
				dfs(i, 0);
				if (!flg) {
					ans = 0;
					break;
				}
				ans = ans * (pw[red] + pw[cerulean]) % MOD;
			}
		}
		cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：灵光一闪 (赞：0)

~~哇，这题终于过惹！！！~~

~~不容易啊！！！~~

~~其实是我犯得zz错误太多惹qaq~~

这题主要看如何计算方案数

先给公式:$2^{black}$+$2^{white}$

这个就是一个联通块的染色方案数（Tip：无法染色直接就是0）

black是染的奇数色，white是偶数色

接下来主要讲解一下如何推出来

根据乘法原理，每一个奇数都可能是1或者3，所以有$2^{black}$种

然后奇偶颠倒，偶数变成了奇数，就又有了$2^{white}$种。

两种相加就是这个**联通块**的和辣！

然后就是我犯的第一个zz错误：以为这张图是一张联通图！

在调了II天后，我突然发现了这个的可能性。

所以说，**每一个联通块相乘的积才是答案！**

然后就是我犯的第二个zz错误：ans初值为0

在我测试出错开始……

A few moments later……

……………………………

我脑子瓦特了？？？

**所以当全是0的时候先检查一下初始值！！**

然后我就敲出来了下面这个代码，但是还是发现了有问题，某些值一直偏大
```
//请思考这个代码的问题所在，非常zz的qaq
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<cstdio>

#include<vector>
using namespace std;
const int mod=998244353;
vector<int> v[300005];
bool vis[300005];
int color[300005];
int n,m;
int black,white;
long long ans=1;
bool dfs(int a,int c){
	vis[a]=true;
	if(c==2){
		white++;
		color[a]=2;
		c=1;
	}
	else{
		black++;
		color[a]=1;
		c=2;
	}
	for(int i=0;i<v[a].size();i++){
		if(color[v[a][i]]==color[a]&&color[a]!=0){
/*
cout<<"DEBUG:";
for(int debug=0;debug<n;debug++){
	cout<<color[debug]<<" ";
}
*/
			puts("0");
			return false;
		}
		else{
			if(!vis[v[a][i]]){
				if(!dfs(v[a][i],c)){
					return false;
				}
			}
		}
	}
	return true;
}
long long Fast(int a,int b){
	long long sum=1;
	for(int i=0;i<b;i++){
		sum*=a;
		sum%=mod;
	}
	return sum%mod;
}
int main(){
	int T;
	cin>>T;
	while(T--){
		black=white=0;
		for(int i=1;i<=n;i++){
			v[i].clear();
			color[i]=0;
			vis[i]=false;
		}
		cin>>n>>m;
		for(int i=0;i<m;i++){
			int x,y;
			cin>>x>>y;
			v[x].push_back(y);
			v[y].push_back(x);
		}
//cout<<"answer:";
/*
		if(m==0){
			cout<<Fast(3,n)%mod<<endl;
			continue;
		}
*/
//cout<<"ANSWER ";
		for(int i=1;i<=n;i++){
			if(!vis[i]){
//				cout<<"dfs in"<<i<<" ";
				if(!dfs(i,1)){
					goto END;
				}
//cout<<ans<<" ";
//cout<<white<<" "<<black<<" ";
				ans*=(Fast(2,white)+Fast(2,black));
				ans%=mod;
				white=0;
				black=0;
			}
		}
//		black--;
		cout<<ans<<endl;
		ans=1;
END:{}
	}
	return 0;
}
```
A few days later……

我发现了这个玩意
```
		ans=1;
END:{}
```
那么如果当上一幅图跑了几个联通块时发现矛盾，直接跳到END的话……

## 那么ans不就相当于没初始化吗？？？？？？

~~wzbl~~

接下来就是完整的代码解析惹！
```
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<cstdio>

#include<vector>
using namespace std;
const int mod=998244353;
vector<int> v[300005];
bool vis[300005];
int color[300005];
int n,m;
int black,white;
long long ans=1;
bool dfs(int a,int c){//dfs
	vis[a]=true;
	if(c==2){//染色
		white++;
		color[a]=2;
		c=1;
	}
	else{
		black++;
		color[a]=1;
		c=2;
	}
	for(int i=0;i<v[a].size();i++){
		if(color[v[a][i]]==color[a]&&color[a]!=0){//发现矛盾！
/*
cout<<"DEBUG:";
for(int debug=0;debug<n;debug++){
	cout<<color[debug]<<" ";
}
*/
			puts("0");
			return false;//表示这张图有问题
		}
		else{
			if(!vis[v[a][i]]){
				if(!dfs(v[a][i],c)){//如果发现问题就说明这张图无法染色
					return false;//继续返回ing
				}
			}
		}
	}
	return true;
}
long long Fast(int a,int b){//n^m的运算
	long long sum=1;
	for(int i=0;i<b;i++){
		sum*=a;
		sum%=mod;
	}
	return sum%mod;
}
int main(){
	int T;
	cin>>T;
	while(T--){//T组询问
		black=white=0;
		for(int i=1;i<=n;i++){//初始化
			v[i].clear();
			color[i]=0;
			vis[i]=false;
		}
		cin>>n>>m;
		for(int i=0;i<m;i++){//读入
			int x,y;
			cin>>x>>y;
			v[x].push_back(y);
			v[y].push_back(x);
		}
//cout<<"answer:";
/*
		if(m==0){
			cout<<Fast(3,n)%mod<<endl;
			continue;
		}
*/
//cout<<"ANSWER ";
		for(int i=1;i<=n;i++){//枚举DFS
			if(!vis[i]){
//				cout<<"dfs in"<<i<<" ";
				if(!dfs(i,1)){
					goto END;
				}
//cout<<ans<<" ";
//cout<<white<<" "<<black<<" ";
				ans*=(Fast(2,white)+Fast(2,black));
				ans%=mod;//要边*边%
				white=0;//初始化
				black=0;
			}
		}
//		black--;
		cout<<ans<<endl;
END:{}
		ans=1;//这里千万千万要把赋值放在END后面！切记！
	}
	return 0;
}
```

The End.

---

## 作者：Zechariah (赞：0)

这是一个计数问题，首先我们分两类：单个的点和与其他点相连的点，为什么要这样分呢？  

单个的点是没有任何限制的，也就是说单个的点每个点都有三种取值，乘法原理可得方案数是 3^(单个点的总数)。  

而对于与其他点相连的点，我们可以对这个点所在的联通图进行黑白染色，染色过程中出现矛盾直接判Impossible，就可以得到黑点的个数和白点的个数，此时再分两类：黑点为奇白点为偶和黑点为偶白点为奇，然后根据奇数可以取1、3，偶数只能是2，可以得出这部分答案其实是 2^(黑点数)+2^(白点数)。  

所以我们只需要先找出所有游离的点的个数得到一个结果，然后对每一个联通的子图做黑白染色得到一个结果，最后结果就是这些结果的乘积  
```cpp
#include <bits/stdc++.h>
#define rg register
#define inl inline
typedef long long ll;
const int N = 6e5 + 10, mod = 998244353;
using namespace std;
namespace fast_IO {
	long long read()
	{
		rg long long num = 0;
		rg char ch;
		rg bool flag = false;
		while ((ch = getchar()) == ' ' || ch == '\n' || ch == '\r');
		if (ch == EOF)return ch; if (ch == '-')flag = true; else num = ch ^ 48;
		while ((ch = getchar()) >= '0'&&ch <= '9')
			num = (num << 1) + (num << 3) + (ch ^ 48);
		if (flag)return -num; return num;
	}
	ll max(rg ll a, rg ll b) { if (a > b)return a; return b; }
	ll min(rg ll a, rg ll b) { if (a < b)return a; return b; }
	void write(rg ll x) { if (x < 0)putchar('-'), x = -x; if (x >= 10)write(x / 10); putchar(x % 10 ^ 48); }
	inl ll ksm(rg ll a, rg ll b)
	{
		rg ll ans = 1;
		while (b)
		{
			if (b & 1)(ans *= a) %= mod;
			(a *= a) %= mod;
			b >>= 1;
		}
		return ans;
	}
};
int nt[N], p[N], b[N], num, q[N], du[N], tot;
int flag[N];
inl void add(rg int x, rg int y)
{
	b[++num] = y; nt[num] = p[x]; p[x] = num; ++du[x];
	b[++num] = x; nt[num] = p[y]; p[y] = num; ++du[y];
}
inl int bfs(rg int x)
{
	rg int head = 1, tail = 0, ans = 0;
	q[0] = x; flag[x] = 1; ans = 1;
	tot = 1;
	while (head != tail)
	{
		rg int k = q[tail++]; if (tail == N)tail = 0;
		for (rg int e = p[k]; e; e = nt[e])
		{
			if (flag[b[e]] == flag[k])return 0;
			if (flag[b[e]])continue;
			++tot;
			q[head++] = b[e]; if (head == N)head = 0;
			if (flag[k] == 1)flag[b[e]] = 2;
			else flag[b[e]] = 1, ++ans;
		}
	}
	return ans;
}

int main()
{
	rg int t = fast_IO::read();
	while (t--)
	{
		num = 0;
		rg int n = fast_IO::read(), m = fast_IO::read(), ans = 0, sum = 0;
		rg ll answer = 1;
		rg bool f = false;
		for (rg int i = 1; i <= n; ++i)flag[i] = p[i] = 0, du[i] = 0;
		while (m--)add(fast_IO::read(), fast_IO::read());
		for (rg int i = 1; i <= n; ++i)
			if (!du[i])++sum;
			else if (!flag[i])
			{
				tot = 0;
				rg int num = bfs(i);
				if (!num) { f = true; break; }
				(answer *= (fast_IO::ksm(2, num) + fast_IO::ksm(2, tot - num)) % mod) %= mod;
			}
		(answer *= fast_IO::ksm(3, sum)) %= mod;
		if (f) { puts("0"); continue; }
		fast_IO::write(answer);
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：Sooke (赞：0)

### 解题思路

首先，按照小学数学姿势：

```
奇数 + 奇数 = 偶数
偶数 + 偶数 = 偶数
奇数 + 偶数 = 奇数
偶数 + 奇数 = 奇数
```

点权范围 $\{1,\ 2,\ 3\}$ 的具体值是没有卵用的，我们只关心其奇偶性，即点权可以赋两个奇数之一，或一个偶数。

其次要发现，在一个连通块内，一旦确定了一个点权的奇偶性，我们即锁定了其他点权的奇偶性。

所谓奇偶性，其实在暗示这就是一个二分图的模型，因此我们给每个连通块黑白染色，设黑点 $x$ 个，白点 $y$ 个，如果黑点为奇数，则该连通块有 $2^x$ 种方案，反之有 $2^y$ 种方案。

由于每个连通块贡献独立，结算答案将每个连通块的 $2^x + 2^y$ 相乘。

### 代码实现

记得多组数据不要全局 $memset$！本蒟蒻因此惨遭 $fst$！

```cpp
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>

inline int read() {
    char c = getchar(); int n = 0; bool f = false;
    while (c < '0' || c > '9') { if (c == '-') { f = true; } c = getchar(); }
    while (c >= '0' && c <= '9') { n = (n << 1) + (n << 3) + (c & 15); c = getchar(); }
    return f ? -n : n;
}

const int maxN = 300005, maxE = maxN << 1, p = 998244353;

inline int power(int x, int y) { int res = 1; for (; y; y >>= 1, x = 1ll * x * x % p) { if (y & 1) { res = 1ll * res * x % p; } } return res; }

int n, m, vis[maxN];
long long x, y;
bool flag;

struct List {
    int len, fst[maxN], nxt[maxE], v[maxE];
    
    inline void reset() { len = 0; memset(fst, -1, sizeof(int) * (n + 1)); }
    inline void insert(int u, int vv) { v[len] = vv, nxt[len] = fst[u], fst[u] = len++; }
    inline void connect(int u, int vv) { insert(u, vv), insert(vv, u); }
} ls;

void dfs(int u, int col) {
    if (vis[u] == -1) { vis[u] = col; } else {
        if (vis[u] != col) { flag = true; } return;
    }
    if (col) { x++; } else { y++; }
    for (int i = ls.fst[u]; ~i; i = ls.nxt[i]) { dfs(ls.v[i], !col); }
}

int solve() {
    long long ans = 1;
    memset(vis, -1, sizeof(int) * (n + 1)); // 就是这里! 必须局部.
    for (int i = 1; i <= n; i++) {
        if (vis[i] == -1) {
            flag = false; x = 0; y = 0; dfs(i, 0);
            if (flag) { return 0; }
            ans = ans * (power(2, x) + power(2, y)) % p;
        }
    }
    return ans;
}

int main() {
    for (int tn = read(); tn; tn--) {
        n = read(); m = read(); ls.reset();
        for (int i = 1; i <= m; i++) { ls.connect(read(), read()); }
        printf("%d\n", solve());
    }
    return 0;
}
```

---

## 作者：MorsLin (赞：0)

当时并不会做，看题解后恍然大悟。

因为只能标$1,2,3$三个数，且相连的两个点加起来必须为奇数，那么只有这两种情况$1-2\;,\;3-2$。我们可以发现，当这个图中存在一个长度为奇数的环的时候是肯定无解的，换句话说，**当且仅当这张图是一张二分图的时候有解**。  


这就启发我们了，当有解的时候，我们还可以发现，当一个点 点权为$2$且每有一条出边的时候，当前的方案数是要$\times 2$的，因为$2$可以连$1$或$3$；反之，方案数不变，因为$1,3$只能去连$2$。  


到这里，思路就很清晰了，对于每一个连通块，我们跑一遍二分图染色，记录下两部分的点的个数，分别计为$s_1,s_2$，那么这个连通块的方案数为$2^{s_1}+2^{s_2}$(因为起始点既可以标$1$或$3$，也可以标$2$，这两种方案会导致标$2$的点发生变化，所以要将方案数相加)，再将每个连通块的方案数相乘就好了(乘法原理)

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define mod 998244353
#define LL long long
using namespace std;
struct zzz{
    int t,nex;
}e[300010<<1]; int head[300010],tot;
inline void add(int x,int y){
    e[++tot].t=y;
    e[tot].nex=head[x];
    head[x]=tot;
}
int vis[300010];
LL sum[5],ans;
bool dfs(int x){
    for(int i=head[x];i;i=e[i].nex){
        if(vis[e[i].t]==-1){
            vis[e[i].t]=(vis[x]^1);
            if(!dfs(e[i].t)) return 0;;
        }
        else{
            if(vis[e[i].t]==vis[x])
              return 0;
        }
    }
    sum[vis[x]]++;
    return 1;
}
LL qpow(LL b,LL p){
    LL ans=1;
    while(p){
        if(p&1) ans=(ans*b)%mod; 
        b=(b*b)%mod;
        p>>=1;
    }
    return ans;
}
inline int read(){
    int k=0,f=1; char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-') f=-1;
        c=getchar();	
    }
    while(c>='0'&&c<='9')
      k=k*10+c-48,c=getchar();
    return k*f;
}
int main(){
    int t=read();
    qwq:
    while(t--){
        bool flag=0;
        ans=1; tot=0;
        int n=read(),m=read();
        for(int i=0;i<=n;i++) vis[i]=-1,head[i]=0;
        for(int i=1;i<=m;i++){
            int x=read(),y=read();
            add(x,y); add(y,x);
        }
        for(int i=1;i<=n;i++){
            sum[0]=sum[1]=0;
            if(vis[i]==-1){
                vis[i]=1;
                if(!dfs(i)){
                    flag=1; printf("0\n"); goto qwq;
                }
                else
                  ans=(ans*(((qpow(2,sum[0]))%mod+qpow(2,sum[1]))%mod))%mod;
            }
        }
        if(!flag) printf("%lld\n",ans);
    }
    
    
    return 0;
}
```

---

## 作者：ouuan (赞：0)

考虑每个联通块，对块内进行[黑白染色](https://www.cnblogs.com/zhangjiuding/p/7710811.html)。

若无解（不是二分图），直接输出 $0$，不用继续判断其它联通块；

若有解，统计黑点个数 $b$，白点个数 $w$。我们可以把黑点设成奇数，白点设成偶数，此时方案数为 $2^b$，反之则为 $2^w$。（为奇数时 $1,3$ 任选，为偶数时只能选 $2$）

将每个联通块的方案数相乘即是答案。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int N=300010;
const int M=998244353;

void add(int u,int v);
void dfs(int u);

int head[N],nxt[N<<1],to[N<<1],cnt;
int t,n,m,c[N],tot[2],ans,two[N];
bool flag;

int main()
{
	int i,u,v;
	
	two[0]=1; //预处理2的次幂
	for (i=1;i<N;++i)
	{
		two[i]=two[i-1]*2%M;
	}
	
	scanf("%d",&t);
	
	while (t--)
	{
		scanf("%d%d",&n,&m);
		memset(head,0,sizeof(int)*(n+1)); //如果memset整个数组可能被卡到O(maxn*t)
		memset(c,-1,sizeof(int)*(n+1));
		cnt=0;
		ans=1;
		flag=false;
		for (i=0;i<m;++i)
		{
			scanf("%d%d",&u,&v);
			add(u,v);
			add(v,u);
		}
		for (i=1;i<=n&&!flag;++i)
		{
			if (c[i]==-1)
			{
				tot[0]=tot[1]=c[i]=0;
				dfs(i);
				ans=1ll*ans*(two[tot[0]]+two[tot[1]])%M;
			}
		}
		if (flag)
		{
			puts("0");
		}
		else
		{
			printf("%d\n",ans);
		}
	}
	
	return 0;
}

void dfs(int u)
{
	++tot[c[u]];
	int i,v;
	for (i=head[u];i;i=nxt[i])
	{
		v=to[i];
		if (c[v]==-1)
		{
			c[v]=c[u]^1;
			dfs(v);
			if (flag)
			{
				return;
			}
		}
		else if (c[v]==c[u])
		{
			flag=true;
			return;
		}
	}
}

void add(int u,int v)
{
	nxt[++cnt]=head[u];
	head[u]=cnt;
	to[cnt]=v;
}
```

---

