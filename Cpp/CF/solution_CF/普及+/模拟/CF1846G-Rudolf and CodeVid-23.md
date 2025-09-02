# Rudolf and CodeVid-23

## 题目描述

A new virus called "CodeVid-23" has spread among programmers. Rudolf, being a programmer, was not able to avoid it.

There are $ n $ symptoms numbered from $ 1 $ to $ n $ that can appear when infected. Initially, Rudolf has some of them. He went to the pharmacy and bought $ m $ medicines.

For each medicine, the number of days it needs to be taken is known, and the set of symptoms it removes. Unfortunately, medicines often have side effects. Therefore, for each medicine, the set of symptoms that appear when taking it is also known.

After reading the instructions, Rudolf realized that taking more than one medicine at a time is very unhealthy.

Rudolph wants to be healed as soon as possible. Therefore, he asks you to calculate the minimum number of days to remove all symptoms, or to say that it is impossible.

## 说明/提示

In the first example, we can first apply medicine number $ 4 $ , after which the symptoms will look like "00101". After that, medicine number $ 2 $ , then all symptoms will disappear, and the number of days will be $ 5 + 3 = 8 $ . Another option is to apply the medicines in the order $ 1, 3, 2 $ . In this case, all symptoms will also disappear, but the number of days will be $ 3 + 3 + 3 = 9 $ .

In the second example, there are no symptoms initially, so the treatment will take $ 0 $ days.

In the third example, there are no options to remove all symptoms.

## 样例 #1

### 输入

```
4
5 4
10011
3
10000
00110
3
00101
00000
3
01010
00100
5
11010
00100
4 1
0000
10
1011
0100
2 2
11
2
10
01
3
01
10
2 3
11
3
01
10
3
10
00
4
10
01```

### 输出

```
8
0
-1
6```

# 题解

## 作者：tbdsh (赞：4)

# 题意简述

[洛谷题面传送门](https://www.luogu.com.cn/problem/cf1846g)

[CodeForces 题面传送门](http://codeforces.com/problemset/problem/1846/G)

[更好的阅读体验](https://www.luogu.com.cn/blog/tianbiandeshenghuo11/solution-cf1846g)

有 $n$ 种病，你得的病症用一串二进制数 $x$ 表示。同时有 $m$ 种药，每种药疗程为 $d_i$。这种药治好的病和吃完后会得到的病用两串二进制数 $a_i,b_i$ 表示。

必须吃完一种药才能吃另一种药。

# 分析

看到这道题，首先想到最短路。但是，这题怎么做最短路呢？

观察到症状最多 $10$ 种，且每种症状只有两种状态。总共最多 $2^{10}=1024$ 状态。由于每两种状态之间都可能相互转移，那么可以看作最多有 $2^{20}\approx10^6$ 条路径。

那么就可以使用 Dijkstra 来求解最短路了。我们把每种状态视做节点，每种药的疗程视作边权。

在读入时，把每个二进制串转为数字，然后就可以写出一个大概的 Dijkstra 了。

**注意**，本题初始化需要将 $2^n$ 个状态初始为极大值，将 $x$ 的十进制表示初始化为 $0$.

那么，就来到了本题的难点：转移。

观察一下：假如当前状态是 $\text{10101}$，吃的药能治好 $\operatorname{10001}$，吃完会得到 $01010$。

最终的理想状态是 $01110$。

吃完得到的只需要最后取位或即可。这里重点探究治好后的状态。

如果我们对 $10001$ 的每一位取反，那么就变成了 $01110$。而原状态是 $10101$。我们发现，如果对这两个值进行位与运算，那么结果 $00100$ 正是治完病后的结果！

那么，假设当前状态为 $v$，那么吃完第 $i$ 种药后的状态 $u=v\And((2^n-1)\oplus a_i)\mid b_i$。其中，$\And$ 是位与运算，$\oplus$ 是异或运算，$\mid$ 是位或运算。

然后剩下的就是最短路板子了。
# Code
```cpp
#include<bits/stdc++.h>

using namespace std;
int t;
struct Node{
  int day, z, d;
} a[1105];
int check(string s){
  int len = s.size(), cnt = 0;
  for (int i = 0; i < len; i++){
    cnt = cnt * 2 + s[i] - '0';
  }
  return cnt;
}
void Solve(){
  int n, m;
  int dis[1105];
  bool vis[1105] = {0};
  cin >> n >> m;
  for (int i = 0; i < (1 << n); i++){
    dis[i] = INT_MAX;
  }
  string tmp;
  cin >> tmp;
  dis[check(tmp)] = 0;
  for (int i = 1; i <= m; i++){
    cin >> a[i].day >> tmp;
    a[i].z = check(tmp);
    cin >> tmp;
    a[i].d = check(tmp);
  }
  while (1){
    int v = -1;
    for (int i = 0; i < (1 << n); i++){
      if (vis[i] || dis[i] == INT_MAX){
        continue;
      }
      if (v == -1 || dis[i] < dis[v]){
        v = i;
      }
    }
    if (v == -1){
      break;
    }
    vis[v] = 1;
    for (int i = 1; i <= m; i++){
      int w = a[i].day, u = (v & (((1 << n) - 1) ^ a[i].z)) | a[i].d;
      dis[u] = min(dis[u], dis[v] + w);
    }
  }
  cout << (dis[0] == INT_MAX ? -1 : dis[0]) << '\n';
}
int main(){
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> t;
  while (t--){
    Solve();
  }
  return 0;
}
```

---

## 作者：Coffee_zzz (赞：3)

### 分析

Rudolf 最多犯 $n$ 种病，每种病犯或不犯，共有 $2^n$ 种状态。

对于每种药，它相当于一种连边方式。

我们可以把所有状态和所有边都放到图上，跑一个从 $s$ 到 $0$ 的最短路即为答案。

接下来分析如何建图。

我们首先把 $s$ 和每种药的作用和副作用都从二进制转化为十进制的形式，设第 $i$ 种药的作用的状态为 $a_i$，副作用的状态为 $b_i$，状态的含义在题目的输入部分。

图中，点即 $0 \sim 2^n-1$；对于边，我们可以枚举一个端点，然后枚举每种连边方式。

考虑如何连边。我们设枚举的端点为 $u$，连边方式为 $i$。

我们先计算每种药的正作用：只有当 $u$ 在二进制表示下第 $p$ 位为 $1$ 且 $a_i$ 在二进制表示下第 $p$ 位为 $0$ 时，第 $p$ 位才是 $1$。所以我们将 $a_i$ 的每一位都取反，计算此时的 $a_i$ 与 $u$ 按位与的结果 $v$。$v$ 即在状态 $u$ 下服用第 $i$ 种药只考虑正作用得到的状态。

接下来我们计算每种药的副作用：如果 $v$ 的第 $p$ 位和 $b_i$ 的第 $p$ 位有一个不为 $0$，那么第 $p$ 位就是 $1$。那我们直接求出 $b_i$ 与 $u$ 按位或的结果 $w$。$w$ 即在状态 $u$ 下服用第 $i$ 种药得到的状态。

于是我们从 $u$ 向 $w$ 连一条长度为 $d_i$ 的边即可。

要注意如果最短路的结果是初始赋的极大值，说明不存在 $s$ 到 $0$ 的路线，输出 $-1$。同时也要注意特判 $s=0$ 的情况。

### 代码

```c++
const int M=2e3,N=1024,inf=1e9+5;
int n,m;
string S,A,B;
int s,a[M],b[M],d[M],ma[N][N],dis[N];
bool vis[N];
void solve(){
	cin>>n>>m>>S;
	int k=pow(2,n)-1;
	s=0;
	for(int j=0;j<n;j++) s=s+((S[j]-'0')<<j);
	for(int i=1;i<=m;i++){
		a[i]=b[i]=0;
		cin>>d[i]>>A>>B;
		for(int j=0;j<n;j++) a[i]=a[i]+((A[j]-'0')<<j);
		for(int j=0;j<n;j++) b[i]=b[i]+((B[j]-'0')<<j);
		a[i]=a[i]^k;
	}
	if(s==0){
		cout<<"0\n";
		return;
	}
	for(int i=0;i<=k;i++) for(int j=0;j<=k;j++) ma[i][j]=inf;
	for(int i=0;i<=k;i++){
		for(int j=1;j<=m;j++){
			ma[i][(i&a[j])|b[j]]=min(ma[i][(i&a[j])|b[j]],d[j]);
		}
	}
	for(int i=0;i<=k;i++) dis[i]=inf;
	queue <int> q;
	q.push(s);
	dis[s]=0;
	vis[s]=1;
	while(!q.empty()){
		int u=q.front();
		q.pop();
		vis[u]=0;
		for(int i=0;i<=k;i++){
			if(dis[i]>dis[u]+ma[u][i]){
				dis[i]=dis[u]+ma[u][i];
				if(!vis[i]){
					q.push(i);
					vis[i]=1;
				}
			}
		}
	}
	if(dis[0]==inf) cout<<"-1\n";
	else cout<<dis[0]<<endl;
}
```

---

## 作者：未来姚班zyl (赞：2)

## 题目大意

有 $n$ 种病和 $m$ 种药，每种药需要服用 $d_i$ 天，可以治好一些病，但也会诱发一些病，给出当前的患病情况，求完全治好需要的最短时间。

## 题目分析

~~这场 div 3 出得很不错。~~

看到那数据范围就不难想到状压，第 $i$ 位为 $1$ 表示患有第 $i$ 种病。

所以一个药物的作用就相当于先按位与，再按位或。对于每种药物，从每种状态向其会到达的状态连边，边权为天数，然后直接跑一边最短路即可。

边数为 $2^nm$，点数为 $2^n$。光是普通的 spfa 都能跑过，而且跑得飞快。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define int ll
#define L x<<1
#define R L|1
#define mid (l+r>>1)
#define lc L,l,mid
#define rc R,mid+1,r
#define OK Ll<=l&&r<=Rr
#define Root 1,1,n
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define pb push_back
#define ull unsigned ll
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
#define E(x) for(auto y:p[x])
#define Pi pair<int,int>
#define ui unsigned ll
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(ll x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
const int N =2e3+5,M=5e6+5,inf=(1LL<<31)-1;
const ll llf=1e18,mod=1e9+7;
using namespace std;
int T=read(),n,m,h[N],to[M],nxt[M],w[M],cnt,s;
inline void add(int a,int b,int c){
	to[++cnt]=b,nxt[cnt]=h[a],h[a]=cnt,w[cnt]=c;
}
char c[12];
inline int get(){
	int ans=0;
	rep(i,1,n)ans+=(c[i]-'0')<<i-1;
	return ans;
}
ll dis[N],S;
bool vis[N];
inline void spfa(){
	rep(i,0,S)dis[i]=llf,vis[i]=0;
	queue<int>q;
	q.push(s),dis[s]=0;
	while(!q.empty()){
		int x=q.front();q.pop();
		vis[x]=0;
		e(x)if(dis[y]>dis[x]+w[i]){
			dis[y]=dis[x]+w[i];
			if(!vis[y])vis[y]=1,q.push(y);
		}
	}
}
signed main(){
	while(T--){
		n=read(),m=read();
		cin >>c+1;
		S=(1<<n)-1;
		s=get();
		rep(i,1,m){
			int w=read(),state0,state1;
			cin >>c+1;
			rep(i,1,n)if(c[i]=='0')c[i]='1';
			else c[i]='0';//&
			state0=get();
			cin >>c+1;
			state1=get();//|
			rep(i,0,S){
				int nx=(i&state0)|state1;
				add(i,nx,w);
			}
		}
		spfa();
		if(dis[0]==llf)cout <<"-1\n";
		else cout <<dis[0]<<endl;
		rep(i,0,S)h[i]=0;
		cnt=0;
	}
	return 0;
}
```


---

## 作者：ldj2006 (赞：2)

# CodeForces CF1846G 题解

- [CodeForces 题目链接](https://codeforces.com/contest/1846/problem/G)
- [洛谷题目链接](https://www.luogu.com.cn/problem/CF1846G)

- 标准答案是状压之后，转化成 Dijkstra 算法跑最短路。我这里提供一个不一样的思路。


### 题意简述
主人公得了病，有部分类型的症状。所有类型症状共有 $n$ 种，用长为 $n$ 的 01 串表示是否有那种症状。共有 $m$ 种药，吃第 $i$ 种药需要花费时间 $t_i$， 能够治好症状 $a_i$， 留下后遗症 $b_i$， 其中 $a_i$、$b_i$均为长度为 $n$ 的 01 串，表示每种症状是否治好或者后遗。

主人公每次只能吃一种药。求康复需要的最少时间。

保证输入不会自相矛盾，药物能治好某种症状就不会后遗。

多组测试。

### 题目分析

#### 1. 最后吃什么？

实际上这个过程和“化学除杂”有些类似。我们考虑最后吃的药的特征，发现最后吃的药一定没有后遗症。简单的证明就是：我们考虑症状个数 $cnt$，最终目标是 $cnt = 0$，如果每种药物都有后遗症，那么即使能够治好全部症状，也至少会遗留下一种后遗症，于是 $cnt \ge 1$，矛盾。**我们暂且把这种药物成为“纯药”（无后遗症）。**

#### 2. 交换吃药顺序？

我们发现交换药物服用顺序是不行的（显然后吃“纯药”和先吃“纯药”，一个康复，一个可能不康复）。

#### 3. 一种药物吃几次？

接下来我们尝试考虑一种药物吃几次。

假设一个药物吃两次及以上，为了方便表示，我们不妨交换每种症状的相对位置，使得对于这个药物而言，是“治疗症状、保持原状、后遗症”的格式。例如原来是：

$$
\begin{array}{c}
\text{主人公症状} & \texttt{01011}\\
\text{药物的疗效} & \texttt{11010}\\
\text{药物后遗症} & \texttt{00100}\\
\end{array}
$$

交换症状相对位置之后（此处 3、4 列和 4、5 列对调）变成：

$$
\begin{array}{c}
\text{主人公症状} & \texttt{01110} \\
\text{药物的疗效} & \texttt{11100}\\
\text{药物后遗症} & \texttt{00001}\\
\end{array}
$$

我们将药物的效果压缩成一个串来表示，治疗用 $\texttt{-}$ 表示，保持不变用 $\texttt{0}$ 表示， 后遗症用 $\texttt{+}$ 表示，于是：

$$
\begin{array}{c}
\text{药物的疗效} & \texttt{11100}\\
\text{药物后遗症} & \texttt{00001}\\
\text{药物效果} & \texttt{---0+}\\
\end{array}
$$

我们将不确定的位置用 $\texttt{Q}$ 来占位表示。（下面表中的各部分串的长度仅为示意，实际上是某一特定的数值。）假如一个药物吃了两次及以上，肯定存在两次吃某一个药，于是有：

$$
\begin{array}{c}
\text{项目} & \text{可治疗} & \text{不变} & \text{后遗症} \\
\text{用药前一状态} & \texttt{QQQ} &  \texttt{QQQQ} & \texttt{QQ} \\
\text{药物效果} & \texttt{---} &  \texttt{0000} & \texttt{++} \\
\text{一次用药后状态} & \texttt{000} &  \texttt{QQQQ} & \texttt{11} \\
\text{中间若干用药} & \cdots & \cdots & \cdots \\
\text{二次用药后状态} & \texttt{000} &  \texttt{QQQQ} & \texttt{11} \\
\end{array}
$$

我们发现在两次服药中间的步骤，所起到的效果（或者说吃它们的目的），是为了改变 $\texttt{Q}$ 的值。因此我们发现，如果把第一次吃药这一步撤掉，我们的结果是：


$$
\begin{array}{c}
\text{项目} & \text{可治疗} & \text{不变} & \text{后遗症} \\
\text{用药前一状态} & \texttt{QQQ} &  \texttt{QQQQ} & \texttt{QQ} \\
\text{药物效果} & \texttt{---} &  \texttt{0000} & \texttt{++} \\
\text{中间若干用药} & \cdots & \cdots & \cdots \\
\text{原二次用药后状态} & \texttt{000} &  \texttt{QQQQ} & \texttt{11} \\
\end{array}
$$

效果没有改变。

因此一种药物吃一遍就足够了。也就是说，每种药只吃一次。

#### 4. 从最后的药物出发

所以我们找到一个“纯药”之后，根据上面的结论，这个纯药应当在最后吃，而且只在最后吃（因为每种药只吃一次）。

我们观察一下：

$$
\begin{array}{c}
\text{项目} & \text{可治疗} & \text{不变} & \text{后遗症} \\
\text{某状态} & \texttt{QQQ} &  \texttt{QQQQ} & \texttt{QQ} \\
\text{中间若干用药} & \cdots & \cdots & \cdots \\
\text{纯药效果} & \texttt{---} &  \texttt{0000} & \texttt{00} \\
\text{吃纯药后状态} & \texttt{000} &  \texttt{QQQQ} & \texttt{QQ} \\
\end{array}
$$

我们发现，吃纯药后把“可治疗”症状全部归 $\texttt{0}$，也就意味着，如果最后吃这个“纯药”，那么再考虑之前的药物时，不用考虑“可治疗”的那几个症状，因为最后都会被纯药一次性全治好。

因此，我们把纯药从所有药物中删除，所有的药物和主人公症状中，涉及到所删除纯药“可治疗”的症状全部抹去，就转化成了规模更小的问题。**我们暂时称这些位置“被覆盖了”。** 如表格所示：

$$
\begin{array}{c}
\text{项目} & \text{不变} & \text{后遗症} \\
\text{某状态} & \texttt{QQQQ} & \texttt{QQ} \\
\text{中间其他若干用药} & \cdots & \cdots \\
\end{array}
$$

于是我们重复上述过程，在剩下的位置中，找剩下药物中的“纯药”（只考虑剩下的位置来判断）。

最终我们可以求得答案。

#### 5. 具体实现的一些细节

具体实现中，我采用的是类似 SPFA 的算法（用优先队列，或者说是 BFS 也行），以及状态更新。我们令状态压缩的 01 串 $S$ 表示每一个位置（症状）是否被覆盖。令 $f_S$ 表示 $S$ 状态下的最短时间。我们在更新的时候，除了更新 $S$ 本身外，还要更新其“包含”状态的值（例如 $\texttt{11001110}$ 中间包含 $\texttt{10001010}$）：

$$
f_{S'} \gets f_{S} ,  S' \subseteq S
$$

由于使用优先队列，所以每个状态只访问一次，对应的 vis 数组记录，判断重复。

其他的位运算等细节请见代码。

记得没病要特判。

### 代码

```cpp
#include <bits/stdc++.h>

#define N (int)(12)
#define M (int)(1e3 + 5)

using namespace std;

typedef long long LL;

struct drag
{
	LL t,e,se,idx;
}d[M];

LL f[1<<N];
bool vis[1<<N];

LL T;

LL n,m;

string to_str(int x);

struct state
{
	LL e,t;
};

bool operator<(const state xx, const state yy)
{
	return xx.t > yy.t;

priority_queue<state> q;

void dfs(LL e,LL p, LL t)
{
	if(vis[e]) return;
	if(e < (1<<p))
	{
		vis[e] = true;
		f[e] = t;
		return;
	}
	if(((e>>p)&1) == 1)
	{
		dfs(e^(1<<p),p+1,t);
	}
	dfs(e,p+1,t);
}

LL ansdfs(LL e,LL p)
{
	if(e < (1<<p))
	{
		return f[e];
	}
	LL ans = 1e18;
	if(((e>>p)&1) == 0)
	{
		ans = min(ans,ansdfs(e|(1<<p),p+1));
	}
	ans = min(ans,ansdfs(e,p+1));
	return ans;
}

inline void setf(LL e,LL t)
{
	dfs(e,0,t);
}

inline LL anti(LL x)
{
	return (1<<n) - 1 - x;
}

bool check(LL e,LL se)
{
	for(LL i = 0;i < n;i++)
	{
		if((((e>>i)&1) == 0) && (((se>>i)&1) == 1))
		{
			return false;
		}
	}
	return true;
}

string to_str(int x)
{
	string str = "";
	for(int i = 0;i < n;i++)
		str += ((x>>i)&1) + '0';
	return str;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> T;
	while(T--)
	{
		memset(vis,0,sizeof(vis));
		memset(f,0x7f,sizeof(f));
		cin >> n >> m;
		string str;
		cin >> str;
		LL e0 = 0;
		for(LL j = n - 1;j >= 0;j--)
				e0 = (e0 << 1) | (str[j] - '0');
		for(LL i = 1;i <= m;i++)
		{
			cin >> d[i].t;
			d[i].idx = i;
			cin >> str;
			d[i].e = 0;
			for(LL j = n - 1;j >= 0;j--)
				d[i].e = (d[i].e << 1) | (str[j] - '0');
			cin >> str;
			d[i].se = 0;
			for(LL j = n - 1;j >= 0;j--)
			{
				d[i].se = (d[i].se << 1) | (str[j] - '0');
			}
		}
		if(e0 == 0)
		{
			cout << "0\n";
			continue;
		}
		q.push({0,0});
		while(!q.empty())
		{
			state top = q.top();
			q.pop();
			if(!vis[top.e])
			{
				setf(top.e,top.t);
				for(int i = 1;i <= m;i++)
				{
					if(check(top.e,d[i].se))
					{
						LL ne = top.e | d[i].e;
						if(!vis[ne])
						{
							q.push({ne,top.t + d[i].t});
						}
					}
				}
			}
		}
		LL ans = ansdfs(e0,0);
		if(ans >= 1e9) cout << "-1\n";
		else cout << ans << "\n";
	}
	return 0;
}
```

本人能力有限，欢迎大家来 Hack！

---

## 作者：kind_aunt (赞：1)

感觉其他题解没怎么讲清楚，我在翻看题解的时候有些看不懂，于是自己交一发吧。
## 题目大意
我们有一个集合，输入一串数 $str$，如果 $i$ 位置上为 1，就代表我们有这个元素，反之则没有。


随后又有 $m$ 种操作，每个操作会用时 $s_i$ 秒拿走其中的一些元素，如果集合中没有这个元素，那么相当于没有操作。并再给我们一些元素，同理，如果集合中有这些元素，则相当于没有操作。

求至少要经过多少秒，才能使集合为空。
## 思路
这题有些不好想到算法，不过应该可以想到 $s_i$ 可以作为比边权。那么初始状态是 $str$，结束状态是 0。咦，有些像单源最短路。状态最多也就有 $2^n$，也就是 $1024$ 种状态，两两连边是 $2^{2n}$，$10^6$ 种，跑 Dijkstra 是绝对不会超时的。

随后我们要解决一个至关重要的问题：如何 $O(1)$ 连边。不难发现，每次取走的就是两个集合的交集。例：当前状态为 `10101`，拿走 `01101`，实际取走的是 `00101`，可以用位与解决。再用异或来将取走的与目前状态处理，得到没有给我们元素前的状态。又能发现，最后状态就是当前状态与给我们元素的位或。（具体公式在一坨 `@` 哪里）

顺便一提，记得初始化！！！
## Code

```
#include<bits/stdc++.h>
#define int long long 
#define id second//我用的是 pair，方便使用
using namespace std;
int st;//起点
int T;//数据组数
int n,m;
char k;
int v,w;
const int N=1025;
struct node
{
	int gout,goin;//失去的 得到的
	int days;//用的时间
}a[N];
struct Edge
{
	int v,w;
};
vector<Edge> edge[N];//Dijkstra 连边
int dis[N];
bool vis[N];
int f[N][N];//本来想用 vector 的，发现有重边，要取最小值，但我只会用邻接矩阵判
priority_queue< pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>> > q;//Dijkstra 基操
void Dij()
{
	q.push(make_pair(0,st));
	dis[st]=0;
	while(q.size())
	{
		int u=q.top().id;
		q.pop();
		if(vis[u]) continue;
		vis[u]=1;
		for(int i=0;i<(1<<n);i++)
		{
			if(f[u][i]==0x3f3f3f) continue;
			if(dis[u]+f[u][i]<dis[i])
			{
				dis[i]=dis[u]+f[u][i];
				q.push(make_pair(dis[i],i));
			}
		}
	}
}//普通跑 Dij
signed main()
{
	cin>>T;
	while(T--)
	{
		memset(f,0x3f3f3f,sizeof f);
		memset(vis,0,sizeof vis);
		memset(dis,0x3f3f,sizeof dis);
		st=0;
		for(int i=1;i<=1024;i++) edge[i].clear();//记得初始化！！！ 
		cin>>n>>m;
		for(int i=1;i<=n;i++)
		{
			cin>>k;
			st<<=1;
			st|=k-'0';
		}//O(n) 算起点
		for(int i=1;i<=m;i++)
		{
			cin>>a[i].days;
			a[i].gout=a[i].goin=0;
			for(int j=1;j<=n;j++)
				cin>>k,a[i].gout=a[i].gout*2+k-'0';
			for(int j=1;j<=n;j++)
				cin>>k,a[i].goin=a[i].goin*2+k-'0';
		}//O(nm)
		for(int i=0;i<(1<<n);i++)
		{
			f[i][i]=0;
			for(int j=1;j<=m;j++)
			{
				int to=(i^(i&a[j].gout))|a[j].goin;//具体公式 @@@@@@@@@@@@
				f[i][to]=min(f[i][to],a[j].days);//判重边
			}
		}//O(2^n m)
		Dij();
		if(dis[0]==4557430888798830399) cout<<-1<<'\n';
		else cout<<dis[0]<<'\n';
	}
	return 0;
}
```
我个人认为这道题只有绿，没什么细节，想到如何连边就可以 A，剩下的跑朴素的 Dijkstra 就行了。

---

## 作者：Otue (赞：1)

把当前的病情状况看成点，吃药前和吃药后的病况看成一条边的两个端点，药的服用天数看成边权。那么跑最短路，从初始病情状态到最终全为 $0$ 的最短距离就是答案。

假设当前病情为 $x$，药的功效为 $y$，药的副作用为 $z$。那么吃完药后病情变为 $x⊕(x\&y)|z$。

看不懂？那补充一下了：设有两个集合 $A,B$
* 集合 $A$ 和 $B$ 的交集，即求出 $A,B$ 都有的部分，表示为 $A\&B$。
* 集合 $A$ 和 $B$ 的并集，即把 $A,B$ 合并起来，表示为 $A|B$。
* 集合 $A$ 和 $B$ 的差集，即从 $A$ 中去掉 $A,B$ 都有的部分，表示为 $A⊕(A\&B)$。

换到这题来，药的功效即为差集，药的副作用即为并集。

## 代码
```c++
#include <bits/stdc++.h>
using namespace std;

#define PII pair<int, int>
#define int long long
const int N = 12, M = 1003;

int T, n, m, d[M], use[M], unuse[M], dist[1 << N], st[1 << N];
char a[N], gd[M][N], ungd[M][N];

int en, first[1 << N];
struct edge {
	int e, d, next;
}ed[(1 << N) * M];

void add_edge(int s, int e, int d) {
	en++;
	ed[en].e = e, ed[en].d = d;
	ed[en].next = first[s];
	first[s] = en;
}

void dij(int s) {
	fill(dist, dist + (1 << N) - 4, 1e18);
	memset(st, 0, sizeof st);
	priority_queue<PII, vector<PII>, greater<PII> > q;
	q.push({0, s});
	dist[s] = 0;
	while (q.size()) {
		auto t = q.top();
		q.pop();
		int u = t.second;
		if (st[u]) continue;
		st[u] = 1;
		for (int p = first[u]; p; p = ed[p].next) {
			int e = ed[p].e, d = ed[p].d;
			if (dist[e] > dist[u] + d) {
				dist[e] = dist[u] + d;
				q.push({dist[e], e});
			} 
		}
	}
}

signed main() {
	cin >> T;
	while (T--) {
		en = 0;
		memset(first, 0, sizeof first);
		cin >> n >> m;
		cin >> a;
		int st = 0;
		for (int i = 0; i < n; i++) {
			if (a[i] == '1') st += (1 << (n - 1 - i));
		}
		for (int i = 1; i <= m; i++) {
			cin >> d[i];
			cin >> gd[i] >> ungd[i];
			use[i] = unuse[i] = 0;
		} 
		for (int i = 1; i <= m; i++) {
			for (int j = 0; j < n; j++) {
				if (gd[i][j] == '1') use[i] += (1 << (n - 1 - j));
			}
			for (int j = 0; j < n; j++) {
				if (ungd[i][j] == '1') unuse[i] += (1 << (n - 1 - j));
			}
		}
		for (int i = 0; i < (1 << n); i++) {
			int tmp = i;
			for (int j = 1; j <= m; j++) {
			    tmp = i;
				tmp = tmp ^ (tmp & use[j]);
				tmp |= unuse[j];
				add_edge(i, tmp, d[j]);
			}
		}
		dij(st);
		if (dist[0] != 1e18) cout << dist[0] << endl;
		else puts("-1");
	}
}
```

---

## 作者：HNOIRPplusplus (赞：1)

## 题意
+ 有一个人得了几种病，用一个 01 串代表他得的病。
+ 有几种药可以治病，也可能导致患病，用两个 01 串表示它们治的病和患的病。
+ 每种药都有疗程，两种药不能同时吃。
+ 求治好全部的病需要多少天。

## 思路

首先看这一眼，有累加的时间，有转移的过程，这显然是一个最短路问题。时间是正的，优先考虑 Dijkstra。

可是，我们应该如何才能把点和边建立起来呢？

看到这个 01 串，相信大家都会想到利用二进制来储存目前的患病状态。于是某些同学开始进行错误的解读：那我们可以把一个药治的病指向其患的病构建一条有向边，最终就会成为一张有向图。然而，这样是错误的。  
我们在任何时刻都能吃任何一种药，而并不一定要满足某种药的需求再吃它。

---

### 治病

现在，我们列个表看看应该如何处理这些 01 串。

|  原来的状态   | 药治的病  | 结果 |
|  ----  | ----  | ---- |
| 1  | 0 | 1 |
| 1  | 1 | 0 |
| 0  | 0 | 0 |
| 0  | 1 | 0 |

那么，我们可以推导出，只有药不治这种病且人原来患了这种病时，最后人才会患这种病。但是，在这里我们剑走偏锋：只有人的状态和药的状态不一且人患了这种病时，人最后才会患这种病。虽然这种方式很难在现实中有什么意义，但是它好些啊！所以我们可以直接拿位运算实现它。直接使用 `[原来的状态] ^ [药治的病] & [原来的状态]` 来实现其。

### 患病

患病很显然，只需要把原来的状态和药使人患的病或一下就行了。直接使用 `[原来的状态] | [药使人患的病]` 来实现其。

---

那么，一个带边权的拥有 $2^n\times k$ 条边（因为有 $n$ 种病，且每种病可以患或不患，所以一共有 $2^n$ 个节点。同时每种药会对每个节点建立一条边，故此）的正边权有向图就被我们建好了，直接使用 Dijkstra 看看从初始状态到 $0$ 状态的最短路径是多少。

## 代码

[云剪贴板传送门](https://www.luogu.com.cn/paste/i7b4i29u)

## 总结

这题其实考的不是 Dijkstra（套板子就行了），而是考如何建出一个好看的图。  
还有另外一种做法，建图按照以上的“错误”的建法，但是在算法转移到下一个点的时候多花点功夫。可以节省许多空间，还请读者尝试一下。

[AC with 31ms and 10880Kb](https://codeforces.com/contest/1846/submission/214281888)

---

## 作者：Wf_yjqd (赞：1)

就这么个最短路板子咋敢放 G 啊。。

祭第一次过 G。

------------

总共的状态最多 $2^n$ 种（$n\le10$）。

所以状态转移的方案最多 $m\times 2^n$ 种。

考虑暴力枚举每种转移建图（稠密图用邻接矩阵就行）。

状态可以直接二进制输入。

用 $j$，$a$ 和 $r$ 分别表示原状态，增加病状和减少病状。那么吃完一种药后的状态为 $\big(j\oplus(j\&r)\big)|a$。

边权为需要吃药的时间。

然后 dijkstra 求从初状态 $d$ 到 $0$ 的最短路，找不到输出 $-1$。

复杂度为 $\operatorname{O}(m\times 2^n \times\log{2^n})$。

------------

放个代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> p;
const int maxn=1e3+84;
inline int read(int base){
    int x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
            f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=x*base+c-'0';
        c=getchar();
    }
    return x*f;
}
int T,n,m,s,val,a,r,t,pw[84],e[maxn][maxn],dis[maxn];
priority_queue<p,vector<p>,greater<p> >pq;
bitset<maxn> vis;
inline void dj(){
    while(!pq.empty())
        pq.pop();
    vis.reset();
    for(int i=0;i<=pw[n];i++)
        dis[i]=0x3f3f3f3f;
    dis[s]=0;
    pq.push({0,s});
    while(!pq.empty()){
        t=pq.top().second;
        pq.pop();
        if(vis[t])
            continue;
        vis[t]=1;
        for(int i=0;i<=pw[n];i++)
            if(e[t][i]<1e9&&dis[i]>dis[t]+e[t][i]){
                dis[i]=dis[t]+e[t][i];
                pq.push({dis[i],i});
            }
    }
    return ;
}
int main(){
    T=read(10);
    pw[0]=1;
    for(int i=1;i<=10;i++)
        pw[i]=pw[i-1]<<1;
    while(T--){
        n=read(10);
        m=read(10);
        s=read(2);
        for(int i=0;i<=pw[n];i++)
            for(int j=0;j<=pw[n];j++)
                e[i][j]=0x3f3f3f3f;
        for(int i=1;i<=m;i++){
            val=read(10);
            r=read(2);
            a=read(2);
            for(int j=0;j<=pw[n];j++)
                e[j][(j^(j&r))|a]=min(e[j][(j^(j&r))|a],val);
        }
        dj();
        if(dis[0]>1e9)
            puts("Sherry");
        else
            printf("%d\n",dis[0]);
    }
    return 0;
}
```


---

## 作者：紊莫 (赞：0)

最短路好题。

看到 $n$ 很小，考虑用一个二进制数字表示某个状态，而药物的作用也就是按照一定规律改变这个状态，到达另一个状态，也就可以看成是一条有向边，由题意得边数在 $10^6$ 量级，可以直接在图上跑最短路。  

使用位运算可以减少码量。  

```cpp
const int N=200005,M=(N<<1),inf=0x3f3f3f3f,mod=1e9+7;
int n,m,a[N],b[N],c[N],d[N],v[N];
vector<Pair> G[N];
int Read(int x){
	int st = 0;
	string s;cin>>s;
	for(auto c:s){
		st=st*2;
		int p=c-'0';
		if(!x)p^=1;
		st += p;
	}
	return st;
}
struct node{
	int now,dis;
	bool operator <(node x)const{
		return dis>x.dis;
	}
};
void dij(int s){
	memset(v,0,sizeof v);
	memset(d,0x3f,sizeof d);
	priority_queue<node> q;
	d[s] = 0; q.push({s,0});
	while(q.size()){
		int f=q.top().now;q.pop();
		if(v[f]){continue;}v[f]=1;
		for(auto i:G[f]){
			int v=i.first,w=i.second;
			if(d[f] + w < d[v]){
				d[v] = d[f] + w;
				q.push({v,d[v]});
			}
		}
	}
}
void solve(){
	n=rd();m=rd();
	int st = Read(1);
	F(i,1,m){
		c[i] = rd();
		a[i] = Read(0);
		b[i] = Read(1);
	}
	for(int i=0;i<(1<<n);i++){
		F(j,1,m){
			int x=i&a[j]; x|=b[j];
			if(x>=(1<<n)) continue;
			G[i].push_back({x,c[j]});
		}
	}
	dij(st);
	for(int i=0;i<(1<<n);i++)
		G[i].clear();
	cout<<(d[0]>inf?-1:d[0])<<endl;
}
signed main() {
	int T=rd();
	while(T--) {
		solve();
	}
	return 0;
}
```


---

## 作者：引领天下 (赞：0)

题意：

一种病有 $n$ 种症状。现在有 $m$ 种药，第 $j$ 种药需要吃 $t_j$ 天，会治好 $r_j$ 的症状，同时引入 $i_j$ 的新症状。

问最少几天能治好。

做法：

闻着一股最短路味。

考虑这个过程其实非常类似位运算：治病是取反后按位与，新增是按位或。

那还有什么好说的，压位之后直接跑 dij 即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n,m;
struct Node{
    int t,r,i;
}a[1005];
string s;
signed main(){
    ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
    cin>>t;
    while(t--){
        cin>>n>>m>>s;
        a[0].i=stoll(s,NULL,2);
        for(int i=1;i<=m;i++){
            cin>>a[i].t>>s;
            for(int i=0;i<s.length();i++)s[i]=!(s[i]-'0')+'0';//对治疗的形状提前取反，方便按位与
            a[i].r=stoll(s,NULL,2);
            cin>>s;
            a[i].i=stoll(s,NULL,2);
        }
        int v[2100];bool vis[2100];memset(vis,0,sizeof(vis));
        for(int i=0;i<=(1<<n);i++)v[i]=1ll<<60;
        v[a[0].i]=0;//初始症状
        for(int i=0;i<(1<<n);i++){
            int t=-1;
            for(int j=0;j<(1<<n);j++)if(!vis[j]&&(t==-1||v[t]>v[j]))t=j;
            if(t==-1)break;
            vis[t]=1;
            for(int j=1;j<=m;j++)v[t&a[j].r|a[j].i]=min(v[t&a[j].r|a[j].i],v[t]+a[j].t);
        }
        cout<<(v[0]==1ll<<60?-1:v[0])<<endl;
    }
    return 0;
}
```

---

