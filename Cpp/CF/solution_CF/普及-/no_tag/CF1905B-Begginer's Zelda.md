# Begginer's Zelda

## 题目描述

You are given a tree $ ^{\dagger} $ . In one zelda-operation you can do follows:

- Choose two vertices of the tree $ u $ and $ v $ ;
- Compress all the vertices on the path from $ u $ to $ v $ into one vertex. In other words, all the vertices on path from $ u $ to $ v $ will be erased from the tree, a new vertex $ w $ will be created. Then every vertex $ s $ that had an edge to some vertex on the path from $ u $ to $ v $ will have an edge to the vertex $ w $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1905B/c3222ff4e4569cd9f8a56d2650b8f98bd69be3cf.png) Illustration of a zelda-operation performed for vertices $ 1 $ and $ 5 $ .Determine the minimum number of zelda-operations required for the tree to have only one vertex.

 $ ^{\dagger} $ A tree is a connected acyclic undirected graph.

## 说明/提示

In the first test case, it's enough to perform one zelda-operation for vertices $ 2 $ and $ 4 $ .

In the second test case, we can perform the following zelda-operations:

1. $ u = 2, v = 1 $ . Let the resulting added vertex be labeled as $ w = 10 $ ;
2. $ u = 4, v = 9 $ . Let the resulting added vertex be labeled as $ w = 11 $ ;
3. $ u = 8, v = 10 $ . After this operation, the tree consists of a single vertex.

## 样例 #1

### 输入

```
4
4
1 2
1 3
3 4
9
3 1
3 5
3 2
5 6
6 7
7 8
7 9
6 4
7
1 2
1 3
2 4
4 5
3 6
2 7
6
1 2
1 3
1 4
4 5
2 6```

### 输出

```
1
3
2
2```

# 题解

## 作者：__little__Cabbage__ (赞：4)

## Solution

有一个很显然的结论：一条 $u \to v$ 的链最多只能覆盖 $2$ 个叶子结点，且当且仅当 $u,v$ 均为叶子结点时可以覆盖 $2$ 个叶子结点，设叶子结点个数为 $cnt$，所以无论如何也不可能在 $< \lceil \frac{cnt}{2} \rceil$ 步骤将整棵树缩为一个点。

所以我们考虑是否存在一个策略使得可以用 $\lceil \frac{cnt}{2} \rceil$ 的步骤将树缩为一个点。不妨采取这样的一个贪心策略：每次选取根结点的两个不同子树上分别一个叶子结点，然后将这两个点缩掉，这样一定会将这两个叶子结点消除，而且不会产生新的叶子结点。

如果叶子结点的个数为偶数，那么按照这个策略可以只用 $\frac{cnt}{2}$ 个步骤就可以完成，而且不会剩下除根结点之外的任何结点，因为以每个非叶子结点 $u$ 为根的子树中一定有一个叶子结点，在这个叶子结点被操作之后，结点 $u$ 就被一块缩掉了。

但如果叶子结点的个数为奇数，那么最后会剩下一条两端分别为根结点和一个叶子结点的链，需要再进行一次操作，总操作数为 $\lceil \frac{cnt}{2} \rceil$。

因此 $\lceil \frac{cnt}{2} \rceil$ 即为答案。

## Code

```cpp
#include<iostream>
#include<cstdio>
//#define int long long
#define il inline
using namespace std;

const int MAXN=1e5+5;
int n,deg[MAXN];

il void solve()
{
    cin>>n;
    for(int i=1;i<=n;++i) deg[i]=0;
    int _u,_v;
    for(int i=1;i<=n-1;++i) cin>>_u>>_v,++deg[_u],++deg[_v];

    int cnt=0;
    for(int i=1;i<=n;++i) if(deg[i]==1) ++cnt;

    cout<<((cnt+1)>>1)<<'\n';
}

signed main()
{
    ios::sync_with_stdio(0);
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int T;
    cin>>T;
    while(T--)
        solve();
    return 0;
}
```

---

## 作者：wmrqwq (赞：4)

# 题目链接

[CF1905B Begginer's Zelda](https://www.luogu.com.cn/problem/CF1905B)

# 题意简述

有一棵有 $n$ 个节点的树，对于每次操作，你可以把一条直线上的树的节点缩成一个点，求把整棵树缩成一个点的最小次数。

# 解题思路

每次我们可以贪心的将不是同一个父亲的两个叶子结点连成的直线缩成一个点，显然这样操作是最优的，因此若叶子节点的个数为 $x$，答案就为 $\frac{x+1}{2}$。

# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define map unordered_map
#define forl(i,a,b) for(register long long i=a;i<=b;i++)
#define forr(i,a,b) for(register long long i=a;i>=b;i--)
#define lc(x) x<<1
#define rc(x) x<<1|1
#define cin(x) scanf("%lld",&x)
#define cout(x) printf("%lld",x)
#define lowbit(x) x&-x
#define pb push_back
#define pf push_front
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
long long t,n,u,v,sum[1000010],ans,a[1000010];
int main()
{
	IOS;
	cin>>t;
	while(t--)
	{
		cin>>n;
		ans=0;
		forl(i,1,n)
			sum[i]=0;
		forl(i,1,n-1)
			cin>>u>>v,sum[u]++,sum[v]++,a[u]=v,a[v]=u;
		forl(i,1,n)
			if(sum[i]==1)
				ans++;
		cout<<(ans+1)/2<<endl;
	}
	QwQ;
}
```

---

## 作者：xiaoxiongbinggan (赞：2)

# CF1905B Begginer's Zelda 题解

### 题目概括：

给出一棵树，进行一种将树上一条直线上节点合并为一个节点的操作，求出几次操作后这棵树上只剩一个节点。

刚刚看到这道题：~~薄纱~~，不简单。

但它仅仅是普及减的难度，那应该就是找规律。

我们想一下，既然要求求出最少的操作步骤，那是不是就是每一次操作的价值最大，那什么时候价值最大呢?就是将两个相距最远的节点这一条直线上的所有节点合并，并且相距最远的两个节点一定是两个叶子节点，也就是说每一次合并将两个叶子节点变为了一个节点，假设叶子节点的个数为 $sum$，则答案数为 $\lceil \frac{sum}{2} \rceil$。

## Code：

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
int T;
int n;
int u,v;
int f[100000];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n;
		memset(f,0,sizeof f);
		for(int i=1;i<n;i++){
			cin>>u>>v;   
			f[u]++;
			f[v]++;
		}
		int ans=0; 
		for(int i=1;i<=n;i++){
			if(f[i]==1){
				ans++;
			}
		}
		cout<<(ans+1)/2<<endl;
	}
	return 0;
}
```

---

## 作者：lizicheng3042 (赞：2)

如题：我们要把一颗树缩成一个点。  
我们发现，对于每次操作，我们实际能将树上的一条链缩成一个节点，因此题目转化为：至少需要多少条链才能覆盖一个树上的所有点。  
然后我们发现，每条链最多可以覆盖 $2$ 个叶节点。（这是显然的，作为叶结点的点只与其他点连了一条边，因此仅能作为链的端点而非中间的某个点）  
因此，我们得到结论：链的最少条数等于叶节点数除以二并向上取整（不能完成配对的叶节点也需要一条链覆盖）  
然而这样做并没有考虑非叶节点，实际上也不需要考虑非叶节点（提醒：假设存在所有叶节点都被覆盖而有非叶节点未被覆盖，那么一定可以通过改变叶节点的配对来使所有非叶节点都被覆盖）。由此得出以下代码：
```cpp
#include<cstdio>
using namespace std;
int T,n,fir[100005],nxt[200005],to[200005],tot,f,t,fa[100005],cha[100005],ans,ver[100005],b;
void add_e(int x,int y)
{
	if(ver[x]!=b)
	{
		ver[x]=b;
		fir[x]=0;
		cha[x]=0;
	}
	if(ver[y]!=b)
	{
		ver[y]=b;
		fir[y]=0;
		cha[y]=0;
	}	
	nxt[++tot]=fir[x];to[fir[x]=tot]=y;
	nxt[++tot]=fir[y];to[fir[y]=tot]=x;
}
void dfs(int x,int fa)
{
	for(int a=fir[x];a;a=nxt[a])
	{
		if(to[a]==fa)
			continue;
		dfs(to[a],x);
		cha[x]++;
	}
//	printf("(%d,%d)",x,cha[x]);
	if(!cha[x])
		ans++;
	if(cha[x]==1&&x==1)//从一开始，也要考虑一是不是叶节点（无根树）
		ans++;
}
int main()
{
	scanf("%d",&T);
	for(b=1;b<=T;b++)
	{
		tot=0;ans=0;
		scanf("%d",&n);
		for(int c=1;c<n;c++)
		{
			scanf("%d%d",&f,&t);
			add_e(f,t);
		}
		dfs(1,0);//事实上有更优秀的算法，但是此处给出dfs的代码
		printf("%d\n",(ans+1)/2);
	}
	return 0;
}
```


---

## 作者：可爱的小棉羊 (赞：1)

**[题目传送门](https://www.luogu.com.cn/problem/CF1905B)**

理解一下题意，我们可以知道我们要用最少的链来覆盖整棵树。

如何用最少的链呢？肯定在叶子节点最好呀！这样覆盖的绝对最多。

这时我们发现对于一条链我们最多只能覆盖两个叶子节点。

那我们设共有 $x$ 个叶子节点，答案一定是 $\left \lceil \frac{x}{2} \right \rceil$。

这样我们连非叶子节点都不需要考虑了，实际上也不用考虑。

附上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int>vec[100005];
int ans;
bool book[100005];
void dfs(int u){
	if(vec[u].size()==1)ans++;
	for(int i=0;i<vec[u].size();i++){
		int v=vec[u][i];
		if(book[v])continue;
		book[v]=1;
		dfs(v);
	}
}
int main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		ans=0;
		memset(book,0,sizeof(book));
		cin>>n;
		for(int i=1;i<n;i++){
			int u,v;
			cin>>u>>v;
			vec[u].push_back(v);
			vec[v].push_back(u);
		}
		book[1]=1;
		dfs(1);
		cout<<(ans+1)/2<<endl;
		for(int i=1;i<=n;i++)vec[i].clear();
	}
} 
```

---

## 作者：a18981826590 (赞：0)

# [Begginer's Zelda](https://www.luogu.com.cn/problem/CF1905B)
## 解题思路
可以运用贪心的思想。

为了让操作次数最小，就应让每次操作覆盖的节点最多。

由于每次操作的是一条链，为了让它最长，就应让它的两端均为叶节点。

若每次操作将 $2$ 个叶节点及其间的节点缩到根节点（任意一节点均可）上，每次操作就可以减少两个节点和其间除根节点外的所有节点。

那么令叶节点个数为 $a$，答案即为 $\lceil \frac{a}{2} \rceil$。

## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100010],m,n,x,y,z;
int main(){
	ios::sync_with_stdio(0);
	cin>>m;
	while(m--){
		cin>>n;
		for(int i=1;i<=n;i++) a[i]=0;
		for(int i=1;i<n;i++){
			cin>>x>>y;
			a[x]++;
			a[y]++;
		}
		z=0;
		for(int i=1;i<=n;i++) if(a[i]==1) z++;
		cout<<ceil(z/2.0)<<'\n';
	}
	return 0;
}
```

---

## 作者：floodfill (赞：0)

# CF1905B Begginer's Zelda 题解
### 题目大意
给一个 $n$ 个结点的树，对每次操作 $[u,v]$，把从 $u$ 到 $v$ 的路径上的结点缩成一个结点。求把整棵树缩成一个点的最小操作次数。
### 大致思路
乍一看，感觉不简单。

但这题是一道 $\color{goldenrod}{普及-}$ 的题目，于是想到找规律。

那么，我们可以发现，用贪心的思路将不是同一个父亲的叶子结点缩成一个结点，这种操作是最优解。在这种情况下，我们就能求出答案了。不妨设叶子结点的个数是 $t$，显然，答案是
$$ans=\lceil \frac{t}{2} \rceil$$

相信你已经觉得这道题不难了。

##### ~~代码不给~~

---

## 作者：我梦见一片焦土 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF1905B)

# 思路：
根据题目，每次操作可以将一条链缩为一个点。

观察发现，每条链最多可以覆盖 $2$ 个叶子结点，在这种情况下是最优的。

因此，若叶子结点的数量为 $leaf$，则答案为 $\frac{leaf+1}{2}$。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e5+10;
const int INF=0x3f3f3f3f;
int t,n,ans,a[N];
signed main(){
	cin>>t;
	while(t--){
		memset(a,0,sizeof a);
		ans=0;
		cin>>n;
		for(int i=1,x,y;i<=n-1;i++){
			cin>>x>>y;
			a[x]++;
            a[y]++;
		}
		for(int i=1;i<=n;i++){
			if(a[i]==1){
                ans++;
            }
		}
		cout<<(ans+1)/2<<endl;
	}
	return 0;
}
```

---

## 作者：Scean_Tong (赞：0)

## CF1905B Begginer's Zelda 题解

### 思路

题目要求我们用最少的链把树缩成一个点，那么就可以转化为用最少的链覆盖整棵树。考虑贪心，当链都覆盖不同祖先的叶子节点时，所需要的链最少。

那么如何判断叶子节点的数量呢？不需要 dfs，只需要在读入这棵树时统计这棵树的度，对于每个点，如果度为 $1$，那么就是叶子节点。

设叶子节点有 $sum$ 个，最后的答案显然就是 $\frac{sum+1}{2}$。

### 代码实现


```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int maxn=1e5+7;
int du[maxn];
int n,t;
int32_t main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n-1;i++){
			int u,v;
			cin>>u>>v;
			du[u]++,du[v]++;
		}
		int sum=0;
		for(int i=1;i<=n;i++){
			if(du[i]==1)sum++;
		}
		int ans=(sum+1)>>1;
		cout<<ans<<'\n';
		for(int i=1;i<=n;i++) du[i]=0;
	}
	return 0;
}

```

---

## 作者：yegengghost (赞：0)

对于该题，我们可以看出只需将叶子结点找出来即可知道结果。因为一条链最多覆盖两个节点。答案即为 $⌈\frac{ans}{2}⌉$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=114514;
int mod;
int t;
int n;
int d[N];
int ksm(int x,int k)
{
    int ans=1,base=x;
    while(k)
    {
        if(k&1) ans=1ll*ans*base%mod;
        base=1ll*base*base%mod; k>>=1;
    }
    return ans;
}
int read()
{
    int f=1,x=0;char ch;
    do{ch=getchar();if(ch=='-')f=-1;}while(ch<'0'||ch>'9');
    do{x=x*10+ch-'0';ch=getchar();}while(ch>='0'&&ch<='9');
    return f*x;
}
signed main()
{
	//不用存图，只需看度即可。 
	t=read();
	while(t--)
	{
		n=read();
		memset(d,0,sizeof(d));//多测不清空，（*****） 
		for(int i=1;i<n;i++)
		{
			int s,e;
			s=read();
			e=read();
			d[s]++;
			d[e]++;
		}
		int ans=0;
		for(int i=1;i<=n;i++)
			if(d[i]==1)
				ans++;
		cout<<(ans+1)/2<<'\n';
	}
	return 0;
}
```

---

## 作者：Miracle_1024 (赞：0)

## 思路：
根据题目分析可得，合并操作必会将两个叶子结点合并到一起，这样就会减少两个叶子结点，所以我们只需要算出叶子结点有多少个，然后求出 $\lceil \frac{cnt}{2} \rceil$。

## 代码：
双倍经验：开始用了 memset 归零，因为 $N$ 开太大一直 TLE。
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e6+10;
const int INF=0x3f3f3f3f;
inline int read(){int x=0,f=1;char ch=getchar();while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}return x*f;}
int t,n,s[N],cnt,u,v;
int main(){
	cin>>t;
	while(t--){
		cnt=0;
		cin>>n;
		for(int i=1;i<=n;i++)s[i]=0;
   		for(int i=1;i<n;i++){
   			cin>>u>>v;
   			s[u]++,s[v]++;
		}
    	for(int i=1;i<=n;i++)if(s[i]==1)cnt++;
    	cout<<(cnt+1)/2<<endl;
	}
}
```

---

## 作者：__hjwucj__ (赞：0)

# 题解：CF1905B Begginer's Zelda

[题目传送门](/problem/CF1905B)

## 思路

很容易发现，只要把不是同一个父节点的叶节点缩成一点，答案一定是最优的。而叶节点可以通过统计每个点在边中出现的次数为 $1$ 的节点数来确定。答案为 $(\text {叶节点数} + 1) \div 2$。

## 代码

为了防止 ctj，代码只给出关键部分。

```cpp
int t = read ();
	while (t--)
	{
		n = read ();
		vector<int> a;
		a.resize (n + 1);
		int u, v, ans = 0;
		reg (i, 2, n) u = read (), v = read (), ++a[u], ++a[v];
		reg (i, 1, n)
			if (a[i] == 1)
				++ans;
		ans = (ans + 1) / 2;
		write_ (ans, '\n'); 
	}
```

---

## 作者：xujingyu (赞：0)

## 题意

输入一棵树，输出最少需要多少次将一段路径合并可以把这棵树弄成一个点。

## 解答

如何才能合并最长的一段路径？

![树](https://cdn.luogu.com.cn/upload/image_hosting/swkuf0zu.png)

这是一颗以 $1$ 为根的树，可以发现，最长的一段路径一定是从叶子开始，叶子结束的。

所以每次选择叶子开始叶子结束的路径，合并，弄完所有的叶子，这棵树也就没了。

那么统计叶子数量（度数为 $1$ 的节点）设为 $x$，答案就是 $\dfrac{x}{2}$？

其实如果 $x\bmod2=1$，那么最后还会剩下一个叶子，所以要再加一。

所以答案就是 $\left\lceil\dfrac{x}{2}\right\rceil$。

```cpp
#include <bits/stdc++.h>
using namespace std;

int t,n,d[100001],cnt;

signed main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		cnt = 0;
		memset(d,0,sizeof(d));
		for(int i = 1;i < n;i++)
		{
			int u,v;
			scanf("%d%d",&u,&v);
			d[u]++;//统计度数
			d[v]++;
		}
		for(int i = 1;i <= n;i++)
		{
			if(d[i] == 1) cnt++;//统计叶子数量
		}
		printf("%d\n",(cnt + 1) / 2);//上取整
	}
	return 0;
}
```

---

## 作者：Beacon_wolf (赞：0)

## 题目思路
根据题目，每次操作可以将一条链缩为一个点。

观察发现，每条链最多可以覆盖 $2$ 个叶子结点，在这种情况下是最优的。

因此，若叶子结点的数量为 $x$，则答案为 $\frac{x+1}{2}$。

## AC 代码
```cpp
#include<bits/stdc++.h> 
using namespace std;
typedef long long ll;
ll t,n,u,v,a[100010],ans;
int main()
{
	cin >> t;
	while(t--){
		memset(a, 0, sizeof(a));
		ans = 0;
		cin >> n;
		for(int i = 1;i <= n - 1;i++){
			cin >> u >> v;
			a[u]++,a[v]++;
		}
		for(int i = 1;i <= n;i++){
			if(a[i] == 1) ans++;
		}
		cout << (ans + 1) / 2 << endl;
	}
	return 0;
}
```


---

## 作者：梦应归于何处 (赞：0)

### 题目大意
给一个有 $n$ 个节点的树，每次操作你可以把树上一条直线上的所有点缩成一个点，问最少几次才能把整棵树缩成一个点。

### 思路

这道题实际上就是去最小化叶子数，然后假设当前最小化后有 $cnt$ 个叶子，那么答案就是 $\frac{cnt+1}{2}$。

那么怎么最小化叶子呢，我们记录每个点的入度，如果这个点的入度为 $1$ 就把他当成叶子，这样就最小化了叶子数。

### 代码

~~~cpp
#include <bits/stdc++.h>
#define db double
#define ll long long
#define ex exit(0)
#define endl "\n"
#define inl inline
#define null NULL
#define pll pair<ll,ll>
#define mkp(a,b) make_pair(a,b)
using namespace std;
ll in[100005];
int main() {
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ll t;
	cin >> t;
	while (t--) {
		ll n;
		cin >> n;
		memset(in, 0, sizeof(in));
		for (int i = 1; i < n; i++) {
			ll u, v;
			scanf("%lld%lld", &u, &v);
			in[v]++;
			in[u]++;
		}
		ll ans = 1;
		for (int i = 1; i <= n; i++) {
			if (in[i] == 1) {
				ans++;
			}
		}
		printf("%lld\n", ans / 2);
	}
	return 0;
}
~~~

---

## 作者：abensyl (赞：0)

原题：[CF1905B Begginer's Zelda](https://www.luogu.com.cn/problem/CF1905B)。

## 思路

对于每次操作，最好的效果就是合并两条完整的链，假设链数为 $k$，那么就是 $\lceil \frac k 2 \rceil$。

在这里，判链的方式是找链头，每找到一个度数为 $1$ 的点就记作发现了一个链。

大致代码如下：
```
void solve() {
	int n,res=0;
	cin>>n;
	for(int i=1;i<=n;++i) du[i]=0;
	for(int i=1;i<n;++i) {
		int u,v;
		cin>>u>>v;
		du[u]++,du[v]++;
	}
	for(int i=1;i<=n;++i) {
		if(du[i]==1) res++;
	} cout<<(res+1)/2<<'\n';
}
```

---

## 作者：Luzhuoyuan (赞：0)

闲话：比赛结束前 $7\text{min}$ 猜到结论，乱写一通结果过了（？

### 题目链接

[[to Codeforces]](https://codeforces.com/contest/1905/problem/B) [[to Luogu]](https://www.luogu.com.cn/problem/CF1905B)

### 题意简述

给定一棵 $n$ 点的树，你可以对其进行操作，每次操作将树上一条链合并成一个点，并令所有与原链有边相连的点与新点连边，求将树变成一个点的最小操作次数。

每个测试点 $t$ 组测试用例。

$$1\le t\le 10^4,2\le n\le 10^5,\sum n\le 10^5$$

### 做法

观察样例发现，答案好像与度为 $1$ 的点数有关。口胡一个证明：考虑在每次操作中消掉从一个度为 $1$ 的点到另一个度为 $1$ 的点的链，那么一次就能减少 $2$ 个度为 $1$ 的点，同时链中间的点度数会减少 $2$。

那度为 $1$ 的点数会不会增加呢？如果现在有多个度大于等于 $3$ 的点，那么我们总能有一种方法使我们的链经过多个这样的点（这样合并后的新点度数一定大于 $1$）。如果消到最后只剩下一个这样的点，我们继续消会使它的度下降为 $1$ 或 $2$，若为 $2$ 则把它放在链上消了即可，否则相当于增加了一个度为 $1$ 的点，这也是整个过程中唯一一次可能使度为 $1$ 的点数增加的机会。由于之前消的度为 $1$ 的点都是两两配对的，所以发生这种情况当且仅当开始时度为 $1$ 的点数 $n_1$ 为奇数。故：

$$ans=\begin{cases}\frac{n_1}{2}&2|n_1\\\frac{n_1+1}{2}&\text{Otherwise}\end{cases}$$

也即：$ans=\lceil\frac{n_1}{2}\rceil$。简单处理即可，复杂度 $O(n)$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,d[100005],x,y;
inline int read(){
    int x=0;
    char c=getchar();
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return x;
}
signed main(){
    T=read();
    while(T--){
        n=read();
        for(int i=1;i<n;i++)
            x=read(),y=read(),d[x]++,d[y]++;
        int ans=0;//这里的 ans 是上面的 n1
        for(int i=1;i<=n;i++)if(d[i]==1)ans++;
        printf("%d\n",(ans+1)/2);
        for(int i=1;i<=n;i++)d[i]=0;
    }
    return 0;
}
```
（逃

---

