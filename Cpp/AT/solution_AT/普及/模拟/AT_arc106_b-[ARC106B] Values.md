# [ARC106B] Values

## 题目描述

有一个由 $N$ 顶点和 $M$ 边构成的简单无向图。第 $i$ 条边连接顶点 $c_i$ 和顶点 $d_i$。

开始时，顶点 $i$ 的值为 $a_i$。您希望通过执行以下操作(至少一次)，使操作后的每个顶点的值分别为 $b_1,b_2,⋯⋯,b_N$。

您每次可选 $1$ 条边。当选择的边连接顶点 $x$ 和顶点 $y$ 时，可进行以下任意一个操作。

让 $a_x-1,a_y+1$，或者让 $a_x+1,a_y-1$

确定是否有操作可以达到您的目的。

## 样例 #1

### 输入

```
3 2
1 2 3
2 2 2
1 2
2 3```

### 输出

```
Yes```

## 样例 #2

### 输入

```
1 0
5
5```

### 输出

```
Yes```

## 样例 #3

### 输入

```
2 1
1 1
2 1
1 2```

### 输出

```
No```

## 样例 #4

### 输入

```
17 9
-905371741 -999219903 969314057 -989982132 -87720225 -175700172 -993990465 929461728 895449935 -999016241 782467448 -906404298 578539175 9684413 -619191091 -952046546 125053320
-440503430 -997661446 -912471383 -995879434 932992245 -928388880 -616761933 929461728 210953513 -994677396 648190629 -530944122 578539175 9684413 595786809 -952046546 125053320
2 10
6 12
9 11
11 5
7 6
3 15
3 1
1 9
10 4```

### 输出

```
Yes```

# 题解

## 作者：lizhixun (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/AT_arc106_b)

### $\texttt{Description}$

给定一个 $n$ 个顶点 $m$ 条边的无向图，最开始顶点 $i$ 的点权为 $a_i$，你可以进行若干次操作，每次操作可以选定一条边，将这一条边连接的两个顶点的点权其中一个 $+1$，另一个 $-1$。问是否可以通过若干次操作，使得第 $i$ 个点的点权为 $b_i$，如果可以则输出 `Yes`，否则输出 `No`。

### $\texttt{Solution}$

我们实际上每条边就相当于把两个点合并，然后我们需要用到并查集寻找连通块，求出每个联通块的顶点之和，最后将数组遍历一遍判断一下即可。

如果并查集板子不会，请转 [P3367](https://www.luogu.com.cn/problem/P3367)，这里就不讲模板了。

### $\texttt{Code}$

先看 [AC 记录](https://atcoder.jp/contests/arc106/submissions/63888935)，再看代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N = 2e5 + 5;
int n, m, a[N], b[N], f[N];
int ans1[N], ans2[N];

int find(int x) {
	if (f[x] == x) return x;
	return f[x] = find(f[x]);
}

// 查找操作

void merge(int x, int y) {
	f[find(x)] = find(y);
	return;
}

// 合并操作

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	cin >> n >> m;
	
	for (int i = 1; i <= n; i++) {
		f[i] = i;
		cin >> a[i];
	}
	
	for (int i = 1; i <= n; i++) {
		cin >> b[i];
	}
	
	for (int i = 1; i <= m; i++) {
		int u, v;
		cin >> u >> v;
		merge(u, v);
	}
	
	for (int i = 1; i <= n; i++) {
		ans1[find(i)] += a[i];
		ans2[find(i)] += b[i];
	}
	
	for (int i = 1; i <= n; i++) {
		if (ans1[i] != ans2[i]) {
			cout << "No" << '\n';
			return 0;
		}
	}
	
	cout << "Yes" << '\n';
	return 0;
}
```

闲话：为什么 ATcoder 的 RMJ 也倒闭啦？呜呜呜……

---

## 作者：pioneer2000 (赞：1)

### 思路：

容易发现，由于一次操作是将边的两端一个顶点的值加一，一个顶点减一，**他的总和是不变的**，由此我们可以想到可以统计每个连通块内的顶点之和与最终要求的顶点之和比较，如果不相等则永远无法达到目的，反之，如果所有连通块内都相等的话，则可以达到目的（我们可以在连通块内通过更改与转换使得最终 $a$ 数组与 $b$ 数组相等。

这时候我们就不难想到可以运用并查集来将顶点划分为一个个连通块，最后将每个连通块求和查询即可。

### 代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define int long long
using namespace std;
const int N=2e5+5;
int n,m,a[N],c,d,p[N],b[N],ans[N],ans1[N];
int get(int a){//查找连通块的‘祖先’
	if(p[a]==a) return a;
	return p[a]=get(p[a]);
}
void unite(int a,int b){//合并两个连通块
	a=get(a);
	b=get(b);
	if(a!=b){
		p[a]=b;
	}
}
void init(){//预处理，每一个顶点最开始‘祖先’都是自己
	for(int i=1;i<=n;i++){
		p[i]=i;
	}
}
main(){
	ios::sync_with_stdio(0);//关闭输入输出流
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	init();
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>b[i];
	for(int i=1;i<=m;i++){
		cin>>c>>d;
		unite(c,d);//合并连通块
	}
	for(int i=1;i<=n;i++){//连通块求和
		ans[get(i)]+=a[i];
		ans1[get(i)]+=b[i];
	}
	for(int i=1;i<=n;i++){
		if(ans[i]!=ans1[i]){
			cout<<"No";
			return 0;
		}
	}
	cout<<"Yes";
	return 0;
}

```

---

## 作者：wang_freedom (赞：1)

### 思路：
观察到对于联通的两个点 $x$ 和 $y$，每次操作后 $a_x+a_y$ 不变，由此推论出每个连通块内的 $a$ 值之和不变。

考虑用并查集计算每个联通块中 $a$ 的值与 $b$ 的值之和，如果都相等，则可以，反之不能。

### AC code:
```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define rop(i,a,b) for(int i=a;i<b;i++)
#define per(i,a,b) for(int i=a;i>=b;i--)
#define por(i,a,b) for(int i=a;i>b;i--)
#define endl '\n'
#define pii pair<int,int>
#define fi first
#define se second
typedef long long ll;
typedef unsigned long long ull;
typedef double lf;
typedef long double ld;
using namespace std;
ll n,m,a[200005],b[200005],fa[200005],tota[200005],totb[200005],u,v;
ll find(ll x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	rep(i,1,n)
		fa[i]=i;
	rep(i,1,n)
		cin>>a[i];
	rep(i,1,n)
		cin>>b[i];
	rep(i,1,m){
		cin>>u>>v;
		fa[find(u)]=find(v);
	}
	rep(i,1,n){
		tota[find(i)]+=a[i];
		totb[find(i)]+=b[i]; 
	}
	rep(i,1,n)
		if(tota[i]!=totb[i]){
			cout<<"No";
			return 0;
		}
	cout<<"Yes";
	return 0;
}
/*

*/

```
tips: 每个连通块内的值的和有可能会爆 int，记得开 longlong。

---

## 作者：hhztl (赞：1)

## 题意简述
有一个由 $N$ 顶点和 $M$ 边构成的简单无向图，顶点 $i$ 的值是 $a_i$。设 $x,y$ 为相连的两个顶点，有两种操作：

- 使 $a_x+1,a_y-1$；
- 使 $a_x-1,a_y+1$。

求是否可以使顶点上的值成为 $b_1,b_2...b_N$。
## 算法分析
容易发现，图中每个连通块的顶点之和是不变的。通过若干次操作，在总和不变的前提下，每个顶点的值可以任意变换。因此，我们只需要判断**每个连通块的顶点之和与目标总和是否相等**就可以了。

容易想到使用**并查集**实现。

注意，输出的`Yes`和`No`都**只有开头大写，其余是小写！**~~我才不会告诉你我也被坑了呢~~
## 上代码！
```
#include<bits/stdc++.h>
using namespace std;
long long n,m,a[200010],b[200010],c,d,f[200010],s1[200010],s2[200010];
long long fd(long long x){return ((f[x]==x)?x:f[x]=fd(f[x]));}//查找
void ad(long long x,long long y){f[fd(x)]=fd(y);}//合并
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++)f[i]=i;//初始化
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=n;i++)cin>>b[i];
    for(int i=1;i<=m;i++){
        cin>>c>>d;
        ad(c,d);//合并c与b
    }for(int i=1;i<=n;i++){
        s1[fd(i)]+=a[i];
        s2[fd(i)]+=b[i];//求出每个连通块的顶点之和
    }for(int i=1;i<=n;i++)
        if(s1[i]!=s2[i]){//若不相等，即无解
            cout<<"No";
            return 0;
        }
    cout<<"Yes";//循环结束还未退出程序，证明有解
    return 0;//完结撒花!!!
}
```
**珍爱生命，远离抄袭！！！**

管理员辛苦啦！

---

## 作者：__Creeper__ (赞：0)

## 题意

有 $n$ 个顶点和 $m$ 条边，第 $i$ 个顶点的权值为 $a_{i}$。每次选择一条连接 $x,y$ 的边，让 $a_{x}+1,a_{y}-1$ 或 $a_{x}-1,a_{y}+1$，问能否通过操作让第 $i$ 个顶点的权值变为 $b_{i}$。

## 思路

经过观察不难发现，不管选择哪种操作，$a_{x} + a_{y}$ 的和不变，每个联通块也是如此。我们只要用并查集计算每个联通块中 $a_{i}$ 的总和与 $b_{i}$ 的总和，如果都相等，则输出```Yes```，否则输出```No```。

## Code

```cpp
#include <bits/stdc++.h>
#define int long long // 不开祖宗见long long
using namespace std;

const int N = 2e5 + 5;
int n, m, a[N], b[N], f[N], suma[N], sumb[N];
int find ( int x ) { return ( x == f[x] ) ? x : f[x] = find ( f[x] ); }

void solve()
{
    cin >> n >> m;
    for ( int i = 1; i <= n; i++ ) cin >> a[i], f[i] = i;
    for ( int i = 1; i <= n; i++ ) cin >> b[i];
    for ( int i = 1; i <= m; i++ )
    {
        int u, v;
        cin >> u >> v;
        f[find ( u )] = find ( v );
    }
    for ( int i = 1; i <= n; i++ )
    {
        suma[find ( i )] += a[i];
        sumb[find ( i )] += b[i];
    }
    for ( int i = 1; i <= n; i++ )
    {
        if ( suma[i] != sumb[i] )
        {
            cout << "No\n";
            return;
        }
    }
    cout << "Yes";
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
//  cin >> T;
    while ( T-- ) solve();
    return 0;
}
```

---

## 作者：yegengghost (赞：0)

笑点解析：无论怎样建边所有点权值都是不变的，所以我们直接累加点权值，判断与预期是否相等也能拿到特别高的分数：


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
const int mod=1;
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
int n,m;
int a[N],b[N];
int suma,sumb;
signed main()
{
	n=read();
	m=read();
	for(int i=1;i<=n;i++)
	{
		a[i]=read();
		suma+=a[i];
	}
	for(int i=1;i<=n;i++)
	{
		b[i]=read();
		sumb+=b[i];
	}

	if(suma==sumb)
		cout<<"Yes"<<'\n';
	else
		cout<<"No"<<'\n';
	return 0;
}

```

由于捆绑测试，我们距离正确答案就只差四个测试点了。

那你觉得后面的输入加上去后可以怎么把所有点权值累加呢？

没毛病，就是并查集！

那就直接放代码吧：


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
const int mod=1;
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
int n,m;
int a[N],b[N];
int f[N];
int suma[N],sumb[N];
int find(int x)
{
	if(f[x]==x)
		return x;
	return f[x]=find(f[x]);
}
signed main()
{
	n=read();
	m=read();
	for(int i=1;i<=n;i++)
		f[i]=i;
	for(int i=1;i<=n;i++) 
		a[i]=read();
	for(int i=1;i<=n;i++)
		b[i]=read();
	for(int i=1;i<=m;i++)
	{
		int s,e;
		s=read();
		e=read();
		//大型认父亲现场
		f[find(s)]=find(e); 
		//维护一个并查集 
	}
	//统计点权值。
	for(int i=1;i<=n;i++)
	{
		suma[find(i)]+=a[i];
		sumb[find(i)]+=b[i];
	}
	for(int i=1;i<=n;i++)
	{
		suma[find(i)]+=a[i];
		sumb[find(i)]+=b[i];
	}
	for(int i=1;i<=n;i++)
	{
		if(suma[i]!=sumb[i])
		{
			cout<<"No"<<'\n';
			return 0;
		}
	}
	cout<<"Yes"<<'\n';
	return 0;
}

```

---

## 作者：chl090410 (赞：0)

## The Solution to AT_arc106_b [ARC106B] Values

### Description

有一个由 $N$ 顶点和 $M$ 边构成的简单无向图，顶点 $i$ 的值为 $a_i$，每次可以选择一条连接 $x,y$ 的边，让 $a_x-1,a_y+1$ 或 $a_x+1,a_y-1$，问能否通过操作让第 $i$ 个顶点的值变为 $b_i$。

### Solution

我们注意到无论怎么操作，所有数字的总和一定不变，而每个连通块中也如此。一个连通块中的数字经过操作后可以为任意数，只要其和等于最初这几个数的和即可。

于是我们就可以用[并查集](https://oi-wiki.org/ds/dsu/)求出所有的连通块，再判断每个连通块中所有顶点在 $a$ 数组中的对应值之和与 $b$ 数组中对应值之和是否相等，若有一个连通块不相等，则输出 ```No```，否则输出 ```Yes```。

### 完整代码如下：

```
#include <bits/stdc++.h>
#define int long long 
using namespace std;
int n,m,a[200005],tja[200005],tjb[200005],b[200005],fa[200005],ans,cnt,k,p,x,y;
int find(int x){
	if(x!=fa[x]){
		fa[x]=find(fa[x]);
	}
	return fa[x];
} 
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		fa[i]=i;
	}
	for(int i=1;i<=n;i++){
		cin>>b[i];
	}
	for(int i=1;i<=m;i++){
		cin>>x>>y;
		fa[find(x)]=find(y);
	}
	for(int i=1;i<=n;i++){
		fa[i]=find(i);
	}
	for(int i=1;i<=n;i++){
		tja[fa[i]]+=a[i];
		tjb[fa[i]]+=b[i];
	}
	for(int i=1;i<=n;i++){
		if(tja[i]!=tjb[i]){
			cout<<"No";
			return 0;
		}
	}
	cout<<"Yes";
	return 0;
}

---

## 作者：QAQ_liu (赞：0)

### 思路：
开始以为是 DFS ~~（最近 DFS 做太多了）~~，后来认真一看，是并查集的题，我们只要先找出连通块，再判断就可以了 ~~（感觉和 DFS 一毛一样呢）~~。
### 代码实现：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5+10;
long long n,m,a[MAXN],b[MAXN],f[MAXN],tot2[MAXN],tot1[MAXN],k,t;
long long check(long long x){
	return f[x]==x?x:f[x]=check(f[x]);
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		f[i]=i;
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		cin>>b[i];
	}
	for(int i=1;i<=m;i++){
		cin>>k>>t;
		f[check(k)]=check(t);
	}
	for(int i=1;i<=n;i++){
		tot1[check(i)]+=a[i];
		tot2[check(i)]+=b[i];
	}
	for(int i=1;i<=n;i++){
		if(tot1[i]!=tot2[i]){
			cout<<"No";
			return 0;
		}
	}
	cout<<"Yes";
	return 0;
}
```
要记得开 long long 哟！

---

## 作者：xxr___ (赞：0)

### 思路：
题目本其实不能，乍一眼看可能会被坑一下，误认为是搜索，仔细读题，发现跟并查集相关，因为有两种选择，所以我们用一个数组来存，用并查集查找相连的边，然后遍历一遍判断一下就完成了。
### 代码：
```cpp
#include<bits/stdc++.h>
int n,m,b[400001],a[200001];
int fa[200001];
long long sum[200001];
int find(int x){
	return fa[x]?fa[x]=find(fa[x]):x;
}
bool vis[200001];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i^(n+1);i++)std::cin>>a[i];
	for(int i=1;i^(n+1);i++)std::cin>>b[i];
	for(int i=1,u,v;i<=m;i++){
		std::cin>>u>>v;
		u=find(u),v=find(v);
		if(u!=v)fa[u]=v;
	}
	for(int i=1;i<=n;i++)
		sum[find(i)]+=a[i]-b[i];
	for(int i=1;i<=n;i++) if(sum[i]) return puts("No")&0;
	puts("Yes");
}
```

---

