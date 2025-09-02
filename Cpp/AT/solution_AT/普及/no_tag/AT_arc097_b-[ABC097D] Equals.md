# [ABC097D] Equals

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc097/tasks/arc097_b

$ 1 $ から $ N $ までの整数を並び替えた順列 $ p_1 $, $ p_2 $, .., $ p_N $ があります。 また、 $ 1 $ 以上 $ N $ 以下の整数のペアが $ M $ 個与えられます。 これらは $ (x_1,y_1) $, $ (x_2,y_2) $, .., $ (x_M,y_M) $ で表されます。 シカの AtCoDeer くんは順列 $ p $ に次の操作を好きなだけ行って、 $ p_i\ =\ i $ となる $ i $ ($ 1 $ $ <\ = $ $ i $ $ <\ = $ $ N $) の数を最大にしようと考えています。

- $ 1 $ $ <\ = $ $ j $ $ <\ = $ $ M $ なる $ j $ を選び、 $ p_{x_j} $ と $ p_{y_j} $ をスワップする

操作後の $ p_i\ =\ i $ となる $ i $ の数として考えうる最大値を求めてください。

## 说明/提示

### 制約

- $ 2 $ $ <\ = $ $ N $ $ <\ = $ $ 10^5 $
- $ 1 $ $ <\ = $ $ M $ $ <\ = $ $ 10^5 $
- $ p $ は $ 1 $ から $ N $ までの整数を並び替えた順列
- $ 1 $ $ <\ = $ $ x_j,y_j $ $ <\ = $ $ N $
- $ x_j $ $ ≠ $ $ y_j $
- $ i $ $ ≠ $ $ j $ なら、 $ \{x_i,y_i\} $ $ ≠ $ $ \{x_j,y_j\} $
- 入力は全て整数

### Sample Explanation 1

$ j=1 $ を選んで操作すると、 $ p $ は `1 3 5 4 2` となり、これがベストなので答えは $ 2 $ です。

### Sample Explanation 2

例えば $ j=1 $, $ j=2 $, $ j=1 $ の順に操作すると、 $ p $ は `1 2 3` となり明らかにこれがベストです。 同じ $ j $ を何回選んでもいいことに注意してください。

### Sample Explanation 4

操作をする必要はありません。

## 样例 #1

### 输入

```
5 2
5 3 1 4 2
1 3
5 4```

### 输出

```
2```

## 样例 #2

### 输入

```
3 2
3 2 1
1 2
2 3```

### 输出

```
3```

## 样例 #3

### 输入

```
10 8
5 3 6 8 7 10 9 1 2 4
3 1
4 1
5 9
2 5
6 5
3 5
8 9
7 9```

### 输出

```
8```

## 样例 #4

### 输入

```
5 1
1 2 3 4 5
1 5```

### 输出

```
5```

# 题解

## 作者：Malkin_Moonlight (赞：2)

挺好玩的一道思维题，我想了十几分钟。

### Solution

> 每对整数对对应一个操作，第 $i$ 对整数对对应着操作：将排列中第 $x_i$ 个数和第 $y_i$ 个数交换。

我们来想一个例子。比如说有 $2$ 对整数对，分别是 $(A,B)$ 和 $(B,C)$。那么 $(P_A,P_B)$ 就可以互换，$(P_B,P_C)$ 也可以互换，这说明 $P_A,P_B,P_C$ 这三个数可以互相交换。看到这里你想到了什么？对了，就是用并查集维护（如果不知道并查集可以去看[这篇文章](https://www.luogu.com.cn/article/89urr16u)）。

我们把每次操作看成一条边，这样处理后能互相交换的数就在一个集合里。这样，我们可以从 $1$ 到 $N$ 循环，如果 $i$ 所在的集合里有 $P_i$，说明一定能通过交换，使得 $i$ 的位置上是 $P_i$，那么 $ans$ 加 $1$。循环结束，输出 $ans$。

### Code


```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define pb emplace_back
const ll maxn = 1e5 + 5;
ll n, m, x, y;
ll p[maxn], father[maxn];

//初始化 
void init() {
	for (ll i = 1; i <= n; i++) {
		father[i] = i;
	}
}

//查找函数 
ll find(ll x) {
	if (father[x] == x) return x;
	return father[x] = find(father[x]);
}

//合并函数 
void merge(ll x, ll y) {
	father[find(x)] = find(y);
}

int main() {
	cin >> n >> m;
	init();
	for (ll i = 1; i <= n; i++) {
		cin >> p[i];
	}
	for (ll i = 1; i <= m; i++) {
		cin >> x >> y;
		merge(x, y);
	}
	ll ans = 0;
	for (ll i = 1; i <= n; i++) {
		if (find(i) == find(p[i])) {
			ans++;
		}
	}
	cout << ans << endl;
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/200247511)。

---

## 作者：zhoujunchen (赞：2)

做题思路
--

并查集板子。把 $m$ 次操作看成 $m$ 条边，在一个集合里就能随便换，用并查集维护。

code：


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,a[100005],fa[100005],ans;
int find(int x){//查询 
	if(fa[x]!=x)return fa[x]=find(fa[x]);
	return x;
}
void hb(int x,int y){//合并 
	if(x!=y)fa[y]=x;
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i],fa[i]=i;
	while(m--){
		int x,y;
		cin>>x>>y;
		hb(find(x),find(y));
	}
	for(int i=1;i<=n;i++)if(find(i)==find(a[i]))ans++;
	cout<<ans;
	return 0;
}
```

---

## 作者：Nightingale_OI (赞：2)

### 大意

你有一个长度为 $ n $ 的排列数组 $ p $ 和 $ m $ 种操作。

每种操作为一个数对 $ (x_i,y_i) $ ，表示交换 $ p_{x_i} $ 和 $ p_{y_i} $ 。

你可以执行任意次操作，求最终 $ p $ 数组有最多多少位置满足 $ p_i = i $ 。

### 思路

由于操作可以执行任意次，把操作看成一条边，如果两个点在同一连通块内就可以无其他影响地互换。

贪心地互换，使用并查集维护即可。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,s,l;
#define f(i,j,k) for(register int i=j;i<=k;++i)
#define g(i,j,k) for(register int i=j;i>=k;--i)
int a[101010];
int b[101010];
int fa[101010];
int fifa(int x){return x==fa[x]?x:fa[x]=fifa(fa[x]);}
int main(){
    cin>>n>>m;
    f(i,1,n)scanf("%d",&a[i]);
    f(i,1,n)fa[i]=b[a[i]]=i;
    f(i,1,m){
        scanf("%d %d",&s,&l);
        fa[fifa(s)]=fifa(l);
    }
    m=0;
    f(i,1,n)m+=(fifa(i)==fifa(b[i]));
    printf("%d\n",m);
    return 0;
}
```

---

## 作者：_hxh (赞：1)

### 题意

有一个长度为 $n$ 的整数序列 $p$ 和 $m$ 对整数对（$x_i$,$y_i$），其中 $1 \le i \le m$，$1 \le x_i,y_i \le n$。可以执行任意次交换操作，每次交换 $p_{x_i}$ 和 $p_{y_i}$，$1 \le i \le m$，求最多能使多少 $p_i = i$。

### 分析

看起来很复杂的样子。举个简单的例子。如果只有两组整数对（$a,b$）和（$b,c$），那么易知 $p_a,p_b,p_c$ 之间是可以相互交换的。说明什么？**如果 $x \in A$，则对于所有 $p_x$，它们之间可以相互交换。即在同一个集合内的点之间可以随意交换**。想到了什么？这可以用**并查集**来维护。

### Code1

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int n,m,f[N],pos[N],p,x,y,ans;
int find(int k)
{
	if (f[k] == k)
		return f[k];
	return f[k] = find(f[k]);
}
int main()
{
	cin >> n >> m;
	for (int i = 1;i <= n;i++)
	{
		cin >> p;
		f[i] = pos[p] = i;//pos记录下标 
	}
	for (int i = 1;i <= m;i++)
	{
		cin >> x >> y;
		f[find(x)] = find(y);
	}
	for (int i = 1;i <= n;i++)
		if (find(i) == find(pos[i]))//如果 i 和 pi 在同一个连通块内 
			ans++;
	cout << ans << endl;
	return 0;
}
```

### Code2

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int n,m,f[N],p[N],x,y,ans;
int find(int k)
{
	if (f[k] == k)
		return f[k];
	return f[k] = find(f[k]);
}
int main()
{
	cin >> n >> m;
	for (int i = 1;i <= n;i++)
	{
		cin >> p[i];
		f[i] = i;
	}
	for (int i = 1;i <= m;i++)
	{
		cin >> x >> y;
		f[find(x)] = find(y);
	}
	for (int i = 1;i <= n;i++)
		if (find(i) == find(p[i]))
			ans++;
	cout << ans << endl;
	return 0;
}
```

---

## 作者：__hjwucj__ (赞：1)

# 题解：AT_arc097_b [ABC097D] Equals

[题目传送门](/problem/AT_arc097_b)

## 思路

我们把每次操作都看作一条边，如果两个点在同一集合内就可以无其他影响地互换。

这里的集合可以使用[并查集](https://baike.baidu.com/item/%E5%B9%B6%E6%9F%A5%E9%9B%86/9388442?fr=ge_ala)来维护，它是一种树形结构。

## 代码参考

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,m,f[100001],a[100001],b[100001]; 
inline int find (int x) {if (f[x]==x) return x;else return f[x]=find (f[x]);}//并查集部分
signed main ()
{
	cin>>n>>m;
	for (int i=1;i<=n;i++) cin>>a[i];
	for (int i=1;i<=n;i++) f[i]=b[a[i]]=i;
	for (int i=1;i<=m;i++)
	{
		int x,y;
		cin>>x>>y;
		f[find (x)]=find (y);//合并
	}
	int ans=0;
	for (int i=1;i<=n;i++) ans+=(find (i)==find (b[i]));
	cout<<ans;
	return 0;
}			
```

---

## 作者：Never_care (赞：0)

### 思路
题意为通过交换让排列中的元素尽可能多回归到位置。交换操作是将两个位置的元素互换，分析可知多次交换可能形成连通分量。连通分量相信大家不陌生，连通分量也可以用于求移动多少次能达到有序状态，也和题意相符。

如何实现连通分量？首先根据题目可以看到进行一次交换操作可以认为合并到同一集合，从而达到快速判断集合的目的。这种方式符合并查集的思想。可以利用并查集连接分量并查询，从而判断每个元素能否通过交换操作归位。  

### code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define INF 0x3f3f3f3f 
using namespace std;
const int N=1e5+5;
int n,m;
int fa[N];
int a[N],p[N];//p为映射数组 
int find(int x){
    if(fa[x]!=x){
        fa[x]=find(fa[x]);
    }
    return fa[x];
}
int main(){
	cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        p[a[i]]=i;
    }
    for(int i=1;i<=n;i++){
        fa[i]=i;//每个初始量为一个集合 
    }
    for(int i=1;i<=m;i++){
        int x,y;
        cin>>x>>y;
        x=find(x),y=find(y);//合并 x,y 
        if(x==y) continue;
        fa[y]=x;
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        if(find(i)==find(p[i])){//查询 i和 p[i] 是否连通 
            ans++;
        }
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：__Creeper__ (赞：0)

### 思路

非常简单的一道并查集。我们把每次操作都看作一条边，如果两个点在同一集合内就可以任意互换。

这里的集合可以使用并查集来维护求出所有的连通块，再贪心地对每个连通块中的数排序，使得 $p_{i}=i$ 的数量最多即可。

总时间复杂度 $O(n\times\log m)$，可以通过本题。

### Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e5 + 5;
int n, m;
int f[N], a[N], idx[N]; 

int find ( int x ) 
{
	if ( f[x] == x ) return x;
	else return f[x] = find ( f[x] );
}

signed main()
{
	cin >> n >> m;
	for ( int i = 1; i <= n; i++ ) cin >> a[i];
	for ( int i = 1; i <= n; i++ ) f[i] = idx[a[i]] = i;
	for ( int i = 1; i <= m; i++ )
	{
		int x, y;
		cin >> x >> y;
		f[find( x )] = find( y );
	}
	int ans = 0;
	for ( int i = 1; i <= n; i++ ) ans += ( find ( i ) == find ( idx[i] ) );
	cout << ans;
	return 0;
}	
```

---

## 作者：skyskyCCC (赞：0)

## 前言。
显然就是对一个排列进行操作，找到一个可能的操作顺序使得 $p_i=i$ 的数量尽可能多。这个题的主要思路是并查集。
## 分析。
我们发现，我们如果直接暴力枚举肯定是不可行的，但是我们可以从交换这个操作上考虑。我们不妨将排列中的每一个数看做是一个点，然后每次的操作就是将两个点互换，我们看做是两个点连起来，这样，在不同的方案下，构成的图也不同。

注意到可以进行任意次操作，所以如果构成了一个连通块，那么该连通块中的点就可以任意互换，所以我们只要找到连通块即可，那么我们不难想到用并查集去查询和合并。然后再对每一个连通块中的数进行交换，然后找到最大值即可。那么，我们之间用并查集维护这个排列的连通性，看看这个数交换的位置在不在一个连通块里即可。

代码如下，仅供参考：
```
#include<iostream>
using namespace std;
int n,m,x,y,a[100005];
int ans,t[100005],fa[100005];
int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
int main(){
	cin>>n>>m;
	for (int i=1;i<=n;i++){
		fa[i]=i;
	}
	for(int i=1;i<=n;i++){
		cin>>a[i];
		t[a[i]]=i;
	}
	for(int i=1;i<=m;i++){
		cin>>x>>y;
		fa[find(x)]=find(y);
	}
	for(int i=1;i<=n;i++){
		if(find(i)==find(t[i])){
			ans++;
		}
	}
	cout<<ans<<"\n";
	return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：chl090410 (赞：0)

## The Solution to AT_arc097_b [ABC097D] Equals

### Description

[题目传送门](https://www.luogu.com.cn/problem/AT_arc097_b)

### Solution

我们把每一个操作看成一条边，每个数字看成一个点，因为可以无限次操作，所以一个连通块中的点就可以任意互换。

我们可以使用[并查集](https://oi-wiki.org/ds/dsu/)求出所有的连通块，再贪心地对每个连通块中的数重排，使得 $p_i=i$ 的数量最多即可。

具体方法：判断 $x$ 与第 $x$ 位的元素是否在同一个连通块中，是则将统计变量加 $1$。

总时间复杂度 $O(n\times \log m)$，能通过本题。

### AC code 如下：

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,ans,a[100005],x,y,fa[100005],yw[100005];
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
		yw[a[i]]=i;
		fa[i]=i;
	}
	for(int i=1;i<=m;i++){
		cin>>x>>y;
		fa[find(x)]=find(y);
	}
	for(int i=1;i<=n;i++){
		if(find(i)==find(yw[i])){
			ans++;
		}
	}
	cout<<ans;
	return 0;
}

---

## 作者：JAMES__KING (赞：0)

在打模拟赛时遇到这题，现在再来回忆一下思路。

### 前置知识：并查集

并查集是一种树型的数据结构，用于处理一些不交集的合并及查询问题，其支持两种不同的操作。

- 查询（Find）：查询某个元素所属集合，亦可判断一些元素是否属于同一集合。实现：

```cpp
int x,y;//要查询的两个元素
cin>>x>>y;
int u=getf(x);
int v=getf(y);//查询
cout<<u<<" "<<v<<"\n";
if(u==v) cout<<"属于同一集合";
else cout<<"不属于同一集合";//判断是否处于同一集合
```

- 合并（Union）：合并两个元素所属集合（对应的树）。实现：

```cpp
int x,y;
cin>>x>>y;
int u=getf(x);
int v=getf(y);//查询
f[u]=v;//合并两棵树的根节点
```

并查集的核心代码：

```cpp
int getf(int x)
{
   if(x!=f[x]) return f[x]=getf(f[x]);//继续回溯，顺带更新该位置所在树的根节点
   return f[x];
}
```

显然，本题是一题裸的并查集，只有一些小改动。

### 模拟赛 CODE：

```cpp
#include<bits/stdc++.h>
#define int long long//防止见祖宗
using namespace std;
int a[100005],f[100005],ans;
bool flag[100005];
vector<int> ve[100005];
void read(int &x)//防TLE
{
   x=0;
   char ch;
   while(!isdigit(ch=getchar()));
   for(;isdigit(ch);ch=getchar())
   x=(x<<1)+(x<<3)+ch-'0';
}
int getf(int x)
{
   if(f[x]!=x) f[x]=getf(f[x]);
   return f[x];
}
signed main()
{
   //freopen("pos.in","r",stdin);
   //freopen("pos.out","w",stdout);
   int n,m;
   scanf("%lld%lld",&n,&m);
   for(int i=1;i<=n;i++) read(a[i]);
   for(int i=1;i<=n;i++) f[i]=i;
   for(int i=1;i<=m;i++)
   {
      int x,y;
      read(x),read(y);
      int u=getf(x),v=getf(y);
      f[u]=v;//合并
   }
   for(int i=1;i<=n;i++)
   {
      int u=getf(i);
      ve[u].push_back(i);//压入动态数组
      f[u]==1;
   }
   for(int i=1;i<=n;i++)
   {
      if(!f[i]) continue;
      int sum=0;
      memset(flag,0,sizeof flag);
      for(auto v:ve[i]) flag[v]=1;
      for(auto v:ve[i]) if(flag[a[v]]) sum++;
      ans+=sum;//计算
   }
   printf("%lld",ans);
   return 0;
}
```

核心思想：并查集与动态数组。

结果被老师怒斥小题大做，~~她~~（他）说只要计算出 $a_i = i$ 的数量即可。一试，果真如此。（~~我真是太蒻了~~）

简化CODE：

```cpp
#include<bits/stdc++.h>
#define int long long//防止见祖宗
using namespace std;
int a[100005],f[100005],ans;
bool flag[100005];
vector<int> ve[100005];
void read(int &x)//防TLE
{
   x=0;
   char ch;
   while(!isdigit(ch=getchar()));
   for(;isdigit(ch);ch=getchar())
   x=(x<<1)+(x<<3)+ch-'0';
}
int getf(int x)
{
   if(f[x]!=x) f[x]=getf(f[x]);
   return f[x];
}
signed main()
{
   //freopen("pos.in","r",stdin);
   //freopen("pos.out","w",stdout);
   int n,m;
   scanf("%lld%lld",&n,&m);
   for(int i=1;i<=n;i++) read(a[i]);
   for(int i=1;i<=n;i++) f[i]=i;
   for(int i=1;i<=m;i++)
   {
      int x,y;
      read(x),read(y);
      int u=getf(x),v=getf(y);
      f[u]=v;//合并
   }
   for(int i=1;i<=n;i++)
      if(getf(i)==getf(a[i])) ans++;//统计
   printf("%lld",ans);
   return 0;
}
```

的确AC。

---

## 作者：Rainbow_Sky (赞：0)

## 思路

### 前置知识

并查集是一种用于管理元素所属集合的数据结构，实现为一个森林，其中每棵树表示一个集合，树中的节点表示对应集合中的元素。

顾名思义，并查集支持两种操作：

- 合并（Union）：合并两个元素所属集合（合并对应的树）。

- 查询（Find）：查询某个元素所属集合（查询对应的树的根节点），这可以用于判断两个元素是否属于同一集合。

并查集在经过修改后可以支持单个元素的删除、移动；使用动态开点线段树还可以实现可持久化并查集。

以上来自 OI wiki。

### 做法

本题可以视为并查集的板子。

对于几次次操作，如果它们有一个公共的点作为桥梁，我们就能使用并查集快速判断出来。

所以我们只要每次将两个数并在一起，即可。

## AC code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxm=1e5+10;
const int maxn=1e3+10;
const int mod=1e9+7;
inline int read(){
	int x=0,y=1;char c=getchar();
	for(;c<'0'||c>'9';c=getchar())if(c=='-')y=-1;
	for(;c>='0'&&c<='9';c=getchar())x=(x<<1)+(x<<3)+(c^48);
	return x*y;
}
int a[maxm],f[maxm],ans;
int getf(int x)
{
	if(f[x]!=x) f[x]=getf(f[x]);
	return f[x];
}
signed main()
{
//	freopen("pos.in","r",stdin);
//	freopen("pos.out","w",stdout);
	int n=read();
	int m=read();
	for(int i=1;i<=n;i++) f[i]=i;
	for(int i=1;i<=n;i++)
	{
		a[i]=read();
	}
	for(int i=1;i<=m;i++)
	{
		int x=read();
		int y=read();
		f[getf(x)]=getf(y);
	}
	for(int i=1;i<=n;i++)
	{
		if(getf(i)==getf(a[i]))
		{
			ans++;
		}
	}
	cout<<ans;
	return 0;
}

```

---

## 作者：Star_Wind (赞：0)

ps:洛谷上神奇的提交不了，真正的评测记录在[这里](https://abc097.contest.atcoder.jp/submissions/11172080)

## **转载自cnblog**

### 题目大意

给出可交换的两个位置，和一个排列，求最后能达成$p_i = i$的位置

### 题解

直接用并查集维护连通性，判一下这个位置上的数和该到的位置和初始位置在不在一个连通块

ACcode

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define MAXN 100005
#define eps 1e-8
#define pb push_back
using namespace std;
typedef long long int64;
typedef double db;
int N,M;
int P[MAXN],fa[MAXN];
int getfa(int x) {
    return fa[x] == x ? x : fa[x] = getfa(fa[x]);
}
int main() {
#ifdef ivorysi
    freopen("f1.in","r",stdin);
#endif
    scanf("%d%d",&N,&M);
    for(int i = 1 ; i <= N ; ++i) scanf("%d",&P[i]);
    for(int i = 1 ; i <= N ; ++i) fa[i] = i;
    int x,y;
    for(int i = 1 ; i <= M ; ++i) {
    	scanf("%d%d",&x,&y);
    	fa[getfa(x)] = getfa(y);
    }
    int cnt = 0;
    for(int i = 1 ; i <= N ; ++i) {
    	if(getfa(P[i]) == getfa(i)) ++cnt;
    }
    printf("%d\n",cnt);
}
```


---

## 作者：wenjunyi (赞：0)

## 题目大意
你有一个长度为 $n$ 的整数排列 $p$，和 $m$ 个操作。

对于每一种操作为数对 $\lparen x_i $，$y_i \rparen$，视为交换两个下标为 $x_i$ 和 $y_i$ 的 $p$ 值。

可以执行任意次操作，求数列 $p$ 中最多有多少个位置 $p_i = i$。

## 思路
可把 $m$ 种操作看成 $m$ 条边，只要在同一个连通块里就可以互换。

用并查集即可。

## 代码
~~~cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long//不开long long,见...
int n,m,p[100005],fa[100005],x,y,cnt;
int find(int x){//递归查看x的祖先 
	if(x==fa[x]){
		return x;
	}
	return fa[x]=find(fa[x]);
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++){
    	cin>>p[i];
    	fa[i]=i;
	}
	for(int i=1;i<=m;i++){
		cin>>x>>y;
		fa[find(x)]=find(y);//放在一个集里 
	}
	for(int i=1;i<=n;i++){
		if(find(i)==find(p[i])){//如果在一个集里,
			cnt++;
		}
	} 
	cout<<cnt;
	return 0;
}
~~~

---

