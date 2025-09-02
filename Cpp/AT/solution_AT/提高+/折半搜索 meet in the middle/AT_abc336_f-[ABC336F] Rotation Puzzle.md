# [ABC336F] Rotation Puzzle

## 题目描述

有一个 $H$ 行 $W$ 列的网格，最初每个格子中恰好写有一个 $1$ 到 $H\times W$ 之间的整数，且每个整数只出现一次。  
具体来说，对于 $1\leq i\leq H$，$1\leq j\leq W$，从上到下第 $i$ 行、从左到右第 $j$ 列的格子中写有 $S_{i,j}$。  
下面，将从上到下第 $i$ 行、从左到右第 $j$ 列的格子称为格子 $(i,j)$。

你可以重复进行如下操作，**最多 $20$ 次**（也可以不进行操作）：

对于任意整数对 $(i,j)$（$1\leq i\leq H,\ 1\leq j\leq W$），判断能否通过操作使得格子 $(i,j)$ 中写有 $((i-1)\times W+j)$，  
如果可以，请输出所需的最小操作次数。  
如果 $20$ 次以内无法达成（包括无论操作多少次都无法达成的情况），请输出 $-1$。

> 操作：从网格中选择一个 $(H-1)\times (W-1)$ 的矩形区域，将其旋转 $180$ 度。  
> 更严格地说，选择整数 $x,y$（$0\leq x,y\leq 1$），
> 对于所有满足 $1\leq i\leq H-1$，$1\leq j\leq W-1$ 的整数对 $(i,j)$，同时将格子 $(i+x,j+y)$ 中的整数与格子 $(H-i+x,W-j+y)$ 中的整数交换。

注意，只要格子中写有的整数满足条件即可，不需要考虑写入的方向等其它因素。

## 说明/提示

### 限制条件

- $3\leq H,W\leq 8$
- $1\leq S_{i,j}\leq H\times W$
- 若 $(i,j)\neq (i',j')$，则 $S_{i,j}\neq S_{i',j'}$
- 输入均为整数

### 样例解释 1

按照如下顺序进行操作，可以在 $2$ 次操作内满足题目条件：
- 选择左上角的矩形区域进行操作，即选择 $x=0$，$y=0$。
- 选择右下角的矩形区域进行操作，即选择 $x=1$，$y=1$。
而无法在 $1$ 次或更少操作内达成条件，因此输出 $2$。

![](https://img.atcoder.jp/abc336/75a97e79fc11bfe9406ef4e3bef74f37.png)

### 样例解释 2

无法在 $20$ 次以内达成条件，因此输出 $-1$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 3
9 4 3
2 1 8
7 6 5```

### 输出

```
2```

## 样例 #2

### 输入

```
4 6
15 18 1 14 3 4
23 24 19 8 9 12
13 2 17 6 5 16
21 22 7 20 11 10```

### 输出

```
-1```

## 样例 #3

### 输入

```
4 6
1 4 13 16 15 18
21 20 9 12 23 10
17 14 5 6 3 2
11 22 7 24 19 8```

### 输出

```
20```

## 样例 #4

### 输入

```
4 3
1 2 3
4 5 6
7 8 9
10 11 12```

### 输出

```
0```

# 题解

## 作者：int_R (赞：6)

直接翻译。

> 次の操作を **高々 $ 20 $ 回** （$ 0 $ 回でも良い）繰り返すことで、

最多操作 $20$ 次。

> より厳密には、整数 $ x,y $ $ (0\ \leq\ x,\ y\ \leq\ 1) $ を選び、

每次操作中只有 $4$ 种选择。

$O(4^{20})$ 级别，同时初末状态都知道了，一眼折半搜索。

直接从初状态和末状态分别走 $10$ 步，将矩阵看做序列做个双模哈希记录状态（虽然这个好像没啥必要），开个哈希表记一下即可。

```cpp
#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
const int MOD1=1e9+93,MOD2=1e9+97;
int n,m,a[10][10],b[10][10],ans=101;
gp_hash_table <long long,int> h;
inline long long get()//双模哈希记录状态，不知道有没有必要
{
    long long s1=0,s2=0;
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
            s1=(s1*233+a[i][j])%MOD1,
            s2=(s2*277+a[i][j])%MOD2;
    return (s1<<32)|s2;
}
void DO(int x,int y)
{
    for(int i=1;i<n;++i)
        for(int j=1;j<m;++j)
            b[i+x][j+y]=a[n-i+x][m-j+y];
    for(int i=1;i<n;++i)
        for(int j=1;j<m;++j)
            a[i+x][j+y]=b[i+x][j+y];
    return ;
}
void dfs(int x,int k)
{
    long long now=get();
    if(h.find(now)!=h.end())
    {
        if(!k) h[now]=min(h[now],x);
        if(k) ans=min(ans,x+h[now]);
    }
    else if(!k) h[now]=x;if(x==10) return ;
    for(int i=0;i<=1;++i)
        for(int j=0;j<=1;++j)
            DO(i,j),dfs(x+1,k),DO(i,j);
}
signed main()
{
#ifdef ONLINE_JUDGE
    cin.tie(0),cout.tie(0);
    ios::sync_with_stdio(0);
#endif
    cin>>n>>m;
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
            cin>>a[i][j];
    dfs(0,0);
    for(int i=1,cnt=0;i<=n;++i)
        for(int j=1;j<=m;++j)
            a[i][j]=++cnt;
    dfs(0,1);cout<<((ans==101)?-1:ans)<<'\n';return 0;
}
```

---

## 作者：qqqaaazzz_qwq (赞：6)

首先，每一步有 $4$ 种可能的操作，又看到题目限定 $20$ 步，于是想到可以用**双向广搜**来解决。

具体操作起来，就是用两个队列来广搜，一个从起点搜，一个从终点搜，如果他们在**中间**汇合就直接输出答案，这样可以减少许多搜索量。

我使用了哈希来判断是否搜过，效率进一步提高。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,m;
struct Node
{
	int a[10][10];
};
Node st,ed;
map<int,int> c1;
map<int,int> c2;
int base = 331;
int mod = 3333333333331;

int HASH(Node x)
{
	int g = 0;
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=m;j++)
		{
			g = (g*base+x.a[i][j])%mod;
		}
	}
	return g;
}

Node Turn(Node t,int x,int y)//将矩阵旋转
{
	Node r;
	for (int i=1;i<=n-1;i++)
	{
		for (int j=1;j<=m-1;j++)
		{
			r.a[i+x][j+y] = t.a[n-i+x][m-j+y];
		}
	}
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=m;j++)
		{
			if(i-x==0||i-x==n||j-y==0||j-y==m) r.a[i][j] = t.a[i][j];
		}
	}
	return r;
}

int bfs()
{
	queue<Node> q1;//从起点搜
	queue<Node> q2;//从终点搜
	q1.push(st);
	q2.push(ed);
	c1[HASH(st)] = 0;
	c2[HASH(ed)] = 0;
	while(!q1.empty()&&!q2.empty())
	{
		Node t = q1.front();
		q1.pop();
		int q = HASH(t);
		if(c2.find(q)!=c2.end()) return c1[q]+c2[q];//在中间汇合了
		for (int x=0;x<2;x++)
		{
			for (int y=0;y<2;y++)
			{
				Node p = Turn(t,x,y);
				int k = HASH(p);
				if(c1.find(k)==c1.end()&&c1[q]+1<=10)//两边各搜10步
				{
					c1[k] = c1[q]+1;
					q1.push(p);
				}
			}
		}
		//-------------分割线-----------------
		t = q2.front();
		q2.pop();
		q = HASH(t);
		if(c1.find(q)!=c1.end()) return c1[q]+c2[q];
		for (int x=0;x<2;x++)
		{
			for (int y=0;y<2;y++)
			{
				Node p = Turn(t,x,y);
				int k = HASH(p);
				if(c2.find(k)==c2.end()&&c2[q]+1<=10)//两边各搜10步
				{
					c2[k] = c2[q]+1;
					q2.push(p);
				}
			}
		}
	}
	return -1;//20步以内无解
}

signed main()
{
	cin >> n >> m;
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=m;j++)
		{
			cin >> st.a[i][j];
			ed.a[i][j] = (i-1)*m+j;
		}
	}
	cout << bfs() << "\n";
	return 0;
}
```

---

## 作者：small_john (赞：3)

## 前言

好久没遇到这么水的 F 题了，竟然给了 $550$ 分。

## 思路

由于每次操作只有 $4$ 中可能，最多支持 $20$ 次操作，暴力枚举 $4^{20}$ 直接寄掉。

如果把操作数压倒 $10$ 呢？$4^{10}$ 是可以接受的！

观察一下，发现起点和终点是恒定不变的，那么考虑双向搜索。具体的，从起点和终点同时往中间搜，最多搜十次。用一个 map 来存一个矩阵是从哪里开始搜索的。如果有一条边连接的两个点都被搜过且起始点不同，就说明找到了答案，输出即可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

template<typename T> inline void read(T &x)
{
	x = 0;
	T f = 1;char ch = getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
		{
			f = -1,ch = getchar();
			break;
		}
		ch = getchar();
	}
	while(ch>='0'&&ch<='9')
		x = (x<<3)+(x<<1)+ch-48,ch = getchar();
	x*=f;
}
template<typename T = int> inline T read()
{
	T x;read(x);return x;
}
template<typename T> void write(T x)
{
    if(x<0) x = -x,putchar('-');
    if(x>9) write(x/10);
    putchar(x%10+48);
}
template<typename T> inline void writen(T x)
{
    write(x);
    putchar(10);
}
const int N = 10;
int n,m;
vector<vector<int> > s,t;//用二维 vector 存储一个矩阵
map<vector<vector<int> >,int > dis,vis;
void solve(vector<vector<int> > &x,int u,int d,int l,int r)//旋转矩阵
{
	auto tmp = x;
	for(int i = u;i<=d;i++)
		for(int j = l;j<=r;j++)
			x[i][j] = tmp[d-i+u][r-j+l];
}
void bfs()//双向搜索
{
	queue<vector<vector<int> > > q;
	if(s==t) return putchar(48),void();
	q.push(s),q.push(t);
	dis[s] = dis[t] = 0,vis[s] = 1,vis[t] = 2;
	while(!q.empty())
	{
		auto u = q.front();q.pop();
		if(dis[u]>=10) continue;//只搜 10 步
		vector<vector<int> > v;
		v = u;
		solve(v,0,n-2,0,m-2);
		if(vis[v]==0) q.push(v),vis[v] = vis[u],dis[v] = dis[u]+1;
		else if(vis[v]!=vis[u]) return write(dis[u]+dis[v]+1),void();
		
		v = u;
		solve(v,0,n-2,1,m-1);
		if(vis[v]==0) q.push(v),vis[v] = vis[u],dis[v] = dis[u]+1;
		else if(vis[v]!=vis[u]) return write(dis[u]+dis[v]+1),void();
		
		v = u;
		solve(v,1,n-1,0,m-2);
		if(vis[v]==0) q.push(v),vis[v] = vis[u],dis[v] = dis[u]+1;
		else if(vis[v]!=vis[u]) return write(dis[u]+dis[v]+1),void();
		
		v = u;
		solve(v,1,n-1,1,m-1);
		if(vis[v]==0) q.push(v),vis[v] = vis[u],dis[v] = dis[u]+1;
		else if(vis[v]!=vis[u]) return write(dis[u]+dis[v]+1),void();
	}
	puts("-1");//无解
} 
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(n),read(m);
	s.resize(n),t.resize(n);
	int tot = 0;
	for(int i = 0;i<n;i++)
	{
		s[i].resize(m),t[i].resize(m);
		for(int j = 0;j<m;j++)
			read(s[i][j]),t[i][j] = ++tot;
	}
	bfs();
	return 0;
}
```

---

## 作者：xz001 (赞：2)

每一个矩阵可以变成四个矩阵，由于步数限制为 $20$，直接爆搜可产生的状态数可达 $4^{20}=1099511627776$ 个，绝对超时，但是如果从输入的矩阵开始搜最多 $10$ 步，从目标矩阵开始搜索最多 $10$ 步，如果两个方向都搜到了一个矩阵，则计算两个方向分别到达它所用的步数之和，与答案取最小值即可，如果没有搜到同一个矩阵，则无解，这样总状态数就成了 $2\times 4^{10}=2097152$，可以通过。

代码如下：

[这里](https://www.luogu.com.cn/paste/0kl4mphx)

---

## 作者：_Ch1F4N_ (赞：2)

样例水的离谱，问候出题人的话就不写了。

考虑每一步最多有 $4$ 种可能，直接搜状态有点多，所以我们折半搜索，从最终状态和初始状态分别开始搜索，然后把步数用哈希记到对应的状态上，找最小值即可。

假若要求 $k$ 步内，这个做法是 $O(4^{\frac{k}{2}} \times n \times m)$ 的，卡卡可以过。

注意哈希的方式，一定要选取好，不然就会像我一样被花式 HACK，这里再次问候可爱的出题人。

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize("Ofast,unroll-loops")
#define int long long
#define mod 1000000007
#define mod2 998244353
using namespace std;
int n,m;
int rk[9][9];
int L[81];
struct mp{
	int a[9][9];
	int val;
};
int Hash(mp x){
	int s1=0,s2=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) s1+=(rk[i][j]*L[x.a[i][j]]%mod),s1%=mod,s2+=(rk[i][j]*L[x.a[i][j]]%mod2),s2%=mod2;
	return ((((s1*s2)%1000000007)+(s1^s2))%998244353*(s1+s2));
}
unordered_map<int,int> step[2];
unordered_map<int,bool> vis[2];
int ans=INT_MAX;
mp st,en;
void dfs(mp now,int h,int type){
	if(h>10) return ;
	step[type][now.val]=min(h,vis[type][now.val]==0?INT_MAX:step[type][now.val]);
	vis[type][now.val]=1;
	if(vis[type^1][now.val]!=0){
		ans=min(ans,step[type][now.val]+step[type^1][now.val]);
	}
	for(int x=0;x<=1;x++){
		for(int y=0;y<=1;y++){
			mp New;
			for(int i=1;i<=n;i++)
				for(int j=1;j<=m;j++) New.a[i][j]=now.a[i][j];
			for(int i=1;i<n;i++)
				for(int j=1;j<m;j++)
					New.a[i+x][j+y]=now.a[n-i+x][m-j+y];
			New.val=Hash(New);
			dfs(New,h+1,type);
		}
	}
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) cin>>st.a[i][j],rk[i][j]=(rand()*rand())%mod2,L[st.a[i][j]]=(rand()*rand())%mod2;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) en.a[i][j]=(i-1)*m+j;
	st.val=Hash(st);
	en.val=Hash(en);
	dfs(st,0,0);
	dfs(en,0,1);
	cout<<(ans<=20?ans:-1);
	return 0;
}

```


---

## 作者：2huk (赞：1)

可以发现，对于每种状态，它会有 $4$ 种可以变成的状态。也就是说暴力枚举的复杂度约 $4^{20}$。显然是不行的。

但是发现这个旋转 $180 ^\circ$ 操作就很像是可以双向搜索的形式。我们令读入的矩阵为 $A$，目标矩阵（也就是 $1, 2, 3, \dots$）为 $B$。那么我们从 $A, B$ 各开始搜索 $10$ 步，然后在搜索空间中取交集，然后求变化次数的最小值即可。

复杂度约为 $2 \times 4^{10}$。

思路不难，实现略需技巧。[代码](https://atcoder.jp/contests/abc336/submissions/49388481)。

---

## 作者：robertuu (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc336_f)

（场切了这道 F，挽救了我的整个 AT rating...）

由于只需要判断 $20$ 步，棋盘又不大（甚至由于需要翻转的区域很大，每一步只有 $4$ 中可能性），很自然会想到搜索。

由于 $4^{20}$ 还是太大，因此采用折半搜索法，从初始状态和最终目标状态各出发搜索 $10$ 步，将搜索的状态数降低到 $2 \times 4^{10}$，用 `map` 存储状态（注意，由于要求最小值，不能只存第十步的状态，要保存每种状态及其对应的步数！）。

但是会发现使用结构体存储棋盘可能会 MLE，因此我采用了哈希，同时将 `map` 修改为 `unordered_map` 进行加速。提交之后会发现单哈希被卡了，使用双哈希就可以通过了。（进制数就随便打一个就行了，如果实在被卡就三哈希，使用质数作为进制数可以降低被卡的概率。）

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[9][9],b[9][9],n,m;
unordered_map<unsigned long long,int> mp1,mp2;
inline unsigned long long hhash(int a[9][9])
{
	unsigned long long h = 0;
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= m;j++)
			h = h*7654321 + a[i][j];
	return h;
}
inline unsigned long long hashh(int a[9][9])
{
	unsigned long long h = 0;
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= m;j++)
			h = h*1234567 + a[i][j];
	return h;
}
inline void rotate(int x,int y)
{
	memcpy(b,a,sizeof(a));
	for(int i = 0;i <= n-2;i++)
		for(int j = 0;j <= m-2;j++)
			b[i+x][j+y] = a[n-2-i+x][m-2-j+y];
	memcpy(a,b,sizeof(b));
}
int ans = 100;
inline void dfs1(int step)
{
	unsigned long long h1 = hhash(a),h2 = hashh(a);
	if(!mp1[h1]) mp1[h1] = step-1;
	else mp1[h1] = min(mp1[h1],step-1);
	if(!mp2[h2]) mp2[h2] = step-1;
	else mp2[h2] = min(mp2[h2],step-1);
	if(step > 10) return;
	rotate(1,1);
	dfs1(step+1);
	rotate(1,1);
	rotate(1,2);
	dfs1(step+1);
	rotate(1,2);
	rotate(2,1);
	dfs1(step+1);
	rotate(2,1);
	rotate(2,2);
	dfs1(step+1);
	rotate(2,2);
}
inline void dfs2(int step)
{
	unsigned long long h1 = hhash(a),h2 = hashh(a);
	if(mp1[h1] && mp2[h2]) ans = min(ans,mp1[h1]+step-1);
	if(step > 10) return;
	rotate(1,1);
	dfs2(step+1);
	rotate(1,1);
	rotate(1,2);
	dfs2(step+1);
	rotate(1,2);
	rotate(2,1);
	dfs2(step+1);
	rotate(2,1);
	rotate(2,2);
	dfs2(step+1);
	rotate(2,2);
}
int main()
{
	cin >> n >> m;
	bool flag = 1;
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= m;j++)
		{
			cin >> a[i][j];
			if(a[i][j] != (i-1)*m+j) flag = 0;
		}
	if(flag)
	{
		cout << 0 << endl;
		return 0;
	}
	dfs1(1);
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= m;j++)
			a[i][j] = (i-1)*m + j;
	dfs2(1);
	if(ans > 20) cout << -1;
	else cout << ans;
	return 0;
}
```

---

## 作者：Expert_Dream (赞：0)

[博客园](https://www.cnblogs.com/gsczl71/p/17880643.html)。

这一题有四种操作，直接暴力枚举的话，时间复杂度是 $O(4 ^ n)$。很显然，可以 meet in the middle 来解决。所以可以将时间复杂度的指数减半。

对于记录答案和记录是否走过的数组都可以用 vector 和 map 来匹配实现。这样会更加方便，否则你手写哈希，虽然不是不可以，但是没必要呀。

对于每一个状态会有 $4$ 种转移方式，然后我们发现了左上角是 $(i,j)$ 与 $(n-i,m-j)$，那么右上角就是 $(i,j+1)$ 与 $(n-i,m-j+1)$ 替换，由此我们由左上角延伸，四个操作都是 $x$ 轴与 $y$ 轴做了偏移量。跟方向数组类似，但其实我们发现了 $0$ 到 $3$ 二进制的特性，二进制的各个位正好可以对应偏移量。所以，我们对这个二进制进行操作就可以得到偏移量。然后在一个函数内，对这个状态进行转移。

注意，如果是奇数的行的话，还要换中间那一行的，记得判断。

代码中的实现，将每一个二维的坐标映射到了一维坐标上，这样就可以不用 vector 套 vector 那么麻烦了。

代码如下：有丰富注释！！

[link](https://atcoder.jp/contests/abc336/submissions/49378110)。

---

## 作者：s4CRIF1CbUbbL3AtIAly (赞：0)

看到不超过 $20$ 次操作，可以知道方案数是 $4^{20}$ 量级的东西，于是考虑 meet in the middle。

直接从初始状态和目标状态各搜十步。每一个状态都可以用 vector 套 vector 直接存下。

```cpp
#define qwq vector<vector<int>>

int h,w,ans=30;
void clr(qwq&a){
	a.resize(h);
	for(auto&i:a)i.resize(w);
}

void rot(qwq&v,int x,int y){// 旋转
	qwq b=v;
	for(int i=0;i<h;i++)for(int j=0;j<w;j++){
		if(i>=x&&i<=h+x-2&&j>=y&&j<=w+y-2)v[i][j]=b[h+x+x-i-2][w+y+y-j-2];
	}
}

map<qwq,int>m1,m2;

void __INIT__(){ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);}
void __SOLVE__(int _case){
	cin>>h>>w;
	vector<vector<int>>v,v2;
	clr(v),clr(v2);
	for(int i=0;i<h;i++)for(int j=0;j<w;j++)cin>>v[i][j],v2[i][j]=i*w+j+1;
	queue<pair<qwq,int>>q;
	qwq tmp;
	for(q.push({v,m1[v]=0});!q.empty();){// 正搜十次
		qwq now=q.front().fi;
		int stp=q.front().se;
		q.pop();
		if(stp>9)continue;
		for(int x=0;x<=1;x++)for(int y=0;y<=1;y++){
			tmp=now;
			rot(tmp,x,y);
			if(!m1.count(tmp))q.push({tmp,m1[tmp]=stp+1});
		}
	}
	for(q.push({v2,m2[v2]=0});!q.empty();){// 倒搜十次
		qwq now=q.front().fi;
		int stp=q.front().se;
		q.pop();
		if(stp>9)continue;
		for(int x=0;x<=1;x++)for(int y=0;y<=1;y++){
			tmp=now;
			rot(tmp,x,y);
			if(!m2.count(tmp))q.push({tmp,m2[tmp]=stp+1});
		}
	}
	for(auto [v,s]:m1)if(m2.count(v))ans=min(ans,s+m2[v]);// 直接取最小值
	if(ans==30)ans=-1;
	cout<<ans<<"\n";
}
```

---

## 作者：joe_zxq (赞：0)

# Part 1 题面翻译

有一个 $H$ 行 $W$ 列的矩阵。最初，从 $1$ 到 $(H \times W)$ 的每个整数都在矩阵中出现了一次。  
对于 $1 \leq i \leq H$ 和 $1 \leq j \leq W$，从上到下第 $i$ 行和从左到右第 $j$ 列的单元格里的数是 $S_{i,j}$。  
$(i,j)$ 表示从上到下第 $i$ 行和从左到右第 $j$ 列的单元格。

判断是否有可能达到这样一种状态：对于所有整数对 $(i,j)$ $(1 \leq i \leq H, 1 \leq j \leq W)$,
单元格 $(i,j)$ 中包含整数 $((i-1) \times W + j)$，重复下面的操作**最多 $20$ 次**（可能为零次）。  
如果可能，请打印所需的最少操作次数。  
如果无法在 $20$ 次或更少的操作后达到这种状态（包括无论重复多少次操作都无法实现的情况），则打印 $-1$。

> 操作：从网格中选择一个大小为 $(H-1) \times (W-1)$ 的矩形，并将其旋转 $180$ 度。  
> 
> 形式化地说，选择整数 $x$ 和  $y$ $(0 \leq x, y \leq 1)$ 和满足 $1 \leq i \leq H-1$ 和 $1 \leq j \leq W-1$ 的所有整数对 $(i,j)$，同时将写在单元格 $(i+x,j+y)$ 中的数替换为写在单元格 $(H-i+x,W-j+y)$ 中的数。

请注意，单元格中的数只需满足条件即可，方向并不重要。

- $3 \leq H,W \leq 8$。
- $1 \leq S_{i,j} \leq H \times W$。
- 如果 $(i,j) \neq (i',j')$，则 $S_{i,j} \neq S_{i',j'}$。
- 所有输入值均为整数。

# Part 2 解法思路

考虑到每次操作有 $2 \times 2 = 4$ 种可能，故直接枚举的时间复杂度是 $4 ^ {20} = 1,099,511,627,776$，定能够 TLE 到飞起。

由于这种旋转 $180$ 度的操作是可逆的，可以使用**双向搜索**。

所谓双向搜索就是从两边分别往中间搜，都只搜一半，看能不能两边搜到中间同一种状态（就像 meet-in-the-middle 一样）。

于是我们可以枚举操作次数，用双向搜索看一下行不行。若是行的话，直接输出答案结束程序。

可以用 map 标记状态（STL 真的很好用）。

这样，我们的时间复杂度优化成 $2 \times 4 ^ {10} = 2,097,152$ 啦。

不理解的小伙伴们可以结合样例，参照下图来理解：

![](https://cdn.luogu.com.cn/upload/image_hosting/dni7a36m.png)

# Part 3 代码实现

话不多说，直接上代码。为方便理解，代码里添加了注释。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll n, m; //行数和列数 
vector<vector<ll> > a(8, vector<ll> (8, 0)); //输入的矩阵 
vector<vector<ll> > b(8, vector<ll> (8, 0)); //目标的矩阵 
bool ok = 0; 
map<vector<vector<ll> >, bool> mp; //用来标记每一种矩阵状态是否出现过 

//c 表示当前操作后矩阵的状态，t 表示剩余的操作次数 
void dfs1(vector<vector<ll> > c, ll t) {
	if (t == 0) {
		mp[c] = 1; //操作结束，将枚举到的中间状态标记 
		return;
	}
	vector<vector<ll> > d(8, vector<ll> (8, 0)); //此次操作后的状态
	//进行变化操作
	for (ll x = 0; x <= 1; x++) {
		for (ll y = 0; y <= 1; y++) {
			for (ll i = 0; i < n; i++) {
				for (ll j = 0; j < m; j++) {
					d[i][j] = c[i][j];
				}
			}
			for (ll i = 0; i < n - 1; i++) {
				for (ll j = 0; j < m - 1; j++) {
					d[i + x][j + y] = c[n - i + x - 2][m - j + y - 2];
				}
			}
			dfs1(d, t - 1); //递归到下一层 
		}
	} 
}

//c 表示当前操作后矩阵的状态，t 表示剩余的操作次数 
void dfs2(vector<vector<ll> > c, ll t) {
	if (ok) {
		return;
	} 
	if (t == 0) {
		//操作结束，看当前中间状态有没有被标记过 
		if (mp[c]) {
			ok = 1;
		}
		return;
	}
	vector<vector<ll> > d(8, vector<ll> (8, 0)); //此次操作后的状态
	//进行变化操作
	for (ll x = 0; x <= 1; x++) {
		for (ll y = 0; y <= 1; y++) {
			for (ll i = 0; i < n; i++) {
				for (ll j = 0; j < m; j++) {
					d[i][j] = c[i][j];
				}
			}
			for (ll i = 0; i < n - 1; i++) {
				for (ll j = 0; j < m - 1; j++) {
					d[i + x][j + y] = c[n - i + x - 2][m - j + y - 2];
				}
			}
			dfs2(d, t - 1); //递归到下一层 
		}
	} 
}

int main() {
	
    //从 main 函数读起是一个好习惯
	 
	cin >> n >> m;
	for (ll i = 0; i < n; i++) {
		for (ll j = 0; j < m; j++) {
			cin >> a[i][j];
			b[i][j] = i * m + j + 1; //计算目标矩阵 
		}
	}
	
	//i 枚举操作次数 
	for (ll i = 0; i <= 20; i++) {
		mp.clear(); //清空状态标记 
		dfs1(a, i / 2); //从开始往中间搜
		dfs2(b, i - i / 2); //从最后往中间搜 
		if (ok) {
			cout << i << endl;
			return 0;
		}
	}
	cout << -1 << endl; 

	return 0;
}

```



---

## 作者：zsyzsy_2012 (赞：0)

相对基础的双向搜索练习题。

读完题后，我们很容易发现每次操作只有 $4$ 种选择。如果暴力枚举，我们的最高复杂度是 $4^{20}$，不能通过本题。这时容易想到，用折半搜索的方式把复杂度降到 $4^{10}$，便能够通过此题。这里采用的是用容器存储第一次搜索结果。

下面是代码，一些注释在代码里了。

```
#include <bits/stdc++.h>
#define N 10
using namespace std ;
int n , m , a[N][N] , ans = 22 ;
map<vector<int> , int>mp ;//这里采用vector作为存储类型，注意结构体是不行的
int mk(int x , int y) {
	return (x - 1) * m + y - 1 ;//相当于对每个格子编了号，便于vector的查询
}
void dfs1(int step , vector<int> b) {
	if(mp[b] && mp[b] <= step) return ;
	mp[b] = step ;
	if(step > 10) return ;
	vector<int>c , d ;
	for(int i = 1 ; i <= n ; i++) {
		for(int j = 1 ; j <= m ; j++) {
			c.push_back(b[mk(i , j)]) ;
			d.push_back(b[mk(i , j)]) ;
		}
	}
	for(int x = 0 ; x < 2 ; x++) {
		for(int y = 0 ; y < 2 ; y++) {
			for(int i = 1 ; i < n ; i++) {
				for(int j = 1 ; j < m ; j++) {
					int t1 = i + x , t2 = j + y ;
					int k1 = n + x - i , k2 = m + y - j ;
					c[mk(t1 , t2)] = b[mk(k1 , k2)] ;
				}
			}//递归与回溯
			for(int i = 1 ; i <= n ; i++) {
				for(int j = 1 ; j <= m ; j++) {
					b[mk(i , j)] = c[mk(i , j)] ;
				}
			}
			dfs1(step + 1 , b) ;
			for(int i = 1 ; i <= n ; i++) {
				for(int j = 1 ; j <= m ; j++) {
					b[mk(i , j)] = c[mk(i , j)] = d[mk(i , j)] ;
				}
			}
		}
	}
}
void dfs2(int step , vector<int> b) {
	if(mp[b]) {
		int t1 = mp[b] - 1 , t2 = 20 - step ;
		ans = min(ans , t1 + t2) ;
	}//搜索第二遍，注意判mp[b]非0
	if(step <= 10) return ;
	vector<int> c , d ;
	for(int i = 1 ; i <= n ; i++) {
		for(int j = 1 ; j <= m ; j++) {
			c.push_back(b[mk(i , j)]) ;
			d.push_back(b[mk(i , j)]) ;
		}
	}
	for(int x = 0 ; x < 2 ; x++) {
		for(int y = 0 ; y < 2 ; y++) {
			for(int i = 1 ; i < n ; i++) {
				for(int j = 1 ; j < m ; j++) {
					int t1 = i + x , t2 = j + y ;
					int k1 = n + x - i , k2 = m + y - j ;
					c[mk(t1 , t2)] = b[mk(k1 , k2)] ;
				}
			}
			for(int i = 1 ; i <= n ; i++) {
				for(int j = 1 ; j <= m ; j++) {
					b[mk(i , j)] = c[mk(i , j)] ;
				}
			}
			dfs2(step - 1 , b) ;
			for(int i = 1 ; i <= n ; i++) {
				for(int j = 1 ; j <= m ; j++) {
					b[mk(i , j)] = c[mk(i , j)] = d[mk(i , j)] ;
				}
			}
		}
	}
}
signed main() {
	scanf("%d%d" , &n , &m) ;
	vector<int> p ;
	for(int i = 1 ; i <= n ; i++) {
		for(int j = 1 ; j <= m ; j++) {
			scanf("%d" , &a[i][j]) ;
			p.push_back(a[i][j]) ;
		}//输入+放入vector存储
	}
	dfs1(1 , p) ;
	for(int i = 1 ; i <= n ; i++) {
		for(int j = 1 ; j <= m ; j++) {
			p[mk(i , j)] = (i - 1) * m + j ;
		}//p是递归初始的vector
	}
	dfs2(20 , p) ;
	if(ans > 20) printf("-1") ;
	else printf("%d" , ans) ;//特判输出
	return 0 ;
}
```


---

## 作者：cppcppcpp3 (赞：0)

[Luogu Link](https://www.luogu.com.cn/problem/AT_abc336_f)

[AtCoder Link](https://atcoder.jp/contests/abc336/tasks/abc336_f)

数据范围 $H,W\le 8$，操作次数 $T \le 20$，一眼搜索。最暴力的想法当然是从 $S$ 开始搜，最大深度为 $20$，看一下是否搜到过所求矩阵 $A$。然而每次旋转有 $4$ 种，状态数达到了 $4^{20}$ 的级别，不可接受。

但是我们起始和终止状态都知道，就可以考虑双向搜索，即分别从 $S,A$ 开始搜索，每边最大深度为 $10$，用 map 记录下经过的所有状态。最后枚举 $S$ 到的每个状态，如果也被 $A$ 搜到过，就更新最小步数。这样状态数降到 $2\times 4^{10} \approx2\times 10^6$ 级别，足以通过此题。

实现上通过 vector 记录矩阵的状态，使用的是 DFS，最慢点跑了不到 3s。

[Submission](https://atcoder.jp/contests/abc336/submissions/49357316)

```cpp
// Problem: F - Rotation Puzzle
// Contest: AtCoder - AtCoder Beginner Contest 336
// URL: https://atcoder.jp/contests/abc336/tasks/abc336_f
// Memory Limit: 1024 MB
// Time Limit: 5000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
typedef vector<int> vi;

int n,m,as=21;
vi a,b;
map<vi,int> mp[2];
map<vi,bool> bk;

int tr(int x,int y){
	return (x-1)*m+y-1;
}

vi rev(vi v,int o){ // o=00/01/10/11 记录 x,y 偏移量
	for(int i=1;i<=(n-1)/2;++i){
		for(int j=1;j<m;++j){
			swap(v[tr(i+(o&1),j+((o>>1)&1))],v[tr(n-i+(o&1),m-j+((o>>1)&1))]);
		}
	}
	if(n>=3 && (n-1)&1){
		int x=(n+1)/2;
		for(int j=1;j<=(m-1)/2;++j){
			swap(v[tr(x+(o&1),j+((o>>1)&1))],v[tr(n-x+(o&1),m-j+((o>>1)&1))]);
		}
	}
	return v;
}

void dfs(int u,vi v,bool o){
	if(!bk[v]) mp[o][v]=u,bk[v]=1;
	else mp[o][v]=min(mp[o][v],u);
	if(u==10) return;
	for(int i=0;i<4;++i) dfs(u+1,rev(v,i),o);
}

signed main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n*m;++i){
		int x; scanf("%d",&x);
		a.push_back(x),b.push_back(i);
	}
	dfs(0,a,0),bk.clear(),dfs(0,b,1);
	
	for(auto x:mp[0]) if(bk[x.first]) as=min(as,x.second+mp[1][x.first]);
	return printf("%d",as>20 ? -1 : as),0;
}
```

---

