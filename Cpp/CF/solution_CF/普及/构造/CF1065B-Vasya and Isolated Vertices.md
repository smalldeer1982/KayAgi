# Vasya and Isolated Vertices

## 题目描述

Vasya has got an undirected graph consisting of $ n $ vertices and $ m $ edges. This graph doesn't contain any self-loops or multiple edges. Self-loop is an edge connecting a vertex to itself. Multiple edges are a pair of edges such that they connect the same pair of vertices. Since the graph is undirected, the pair of edges $ (1, 2) $ and $ (2, 1) $ is considered to be multiple edges. Isolated vertex of the graph is a vertex such that there is no edge connecting this vertex to any other vertex.

Vasya wants to know the minimum and maximum possible number of isolated vertices in an undirected graph consisting of $ n $ vertices and $ m $ edges.

## 说明/提示

In the first example it is possible to construct a graph with $ 0 $ isolated vertices: for example, it should contain edges $ (1, 2) $ and $ (3, 4) $ . To get one isolated vertex, we may construct a graph with edges $ (1, 2) $ and $ (1, 3) $ .

In the second example the graph will always contain exactly one isolated vertex.

## 样例 #1

### 输入

```
4 2
```

### 输出

```
0 1
```

## 样例 #2

### 输入

```
3 1
```

### 输出

```
1 1
```

# 题解

## 作者：DarkShadow (赞：4)

# CF1065B（贪心）

## 题目大意：

图上有 $N$ 个点和 $M$ 条边，求没有任何连边的点的数量最大、最小值。

## 思路分析：

我们可以贪心地来连边，求最小值时，我们可以把相邻的两个点连起来，比如 $1,2$ 号点、$3,4$ 号点、$5,6$ 号点，这样最后要么所有点都有连边，要么还剩下 $N-2 \times M$ 个点没有连边。

然后考虑怎么求最大值。我们可以尝试每两个点都连一条边，尽量形成一个完全图，这样可以使剩下的点最多。

## 完整代码：

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
int n;
ll m;
int main(){
	scanf("%d%lld",&n,&m);
	printf("%d ",max(0ll,(ll)(n)-2*m));//求最小值
	for(int i=0;i<=n;i++)
		if((ll)(i)*(ll)(i-1)/2ll>=m){
			printf("%d",n-i);//求最大值
			break;
		}
	return 0;
}
```

---

## 作者：Double_Light (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1065B)

首先考虑最小值。

如果想要使“被孤立的”节点数最少，需要让尽可能多的点有边连接。对于每一条边，找到两个没有边连接的点连边，这样连边的节点数最多，$m$ 条边可以连接 $2m$ 个节点，“被孤立的”节点数最小值为 $\max(0,n-2m)$。

接着考虑最大值。

要使“被孤立的”节点数最多，可以让有边相连的节点尽可能多的连边。对于 $x$ 个节点，没有重边和自环，最多可以连 $\dfrac{x(x-1)}{2}$ 条边。直接枚举 $x$，直到 $x$ 个节点能连完 $m$ 条边。这样，最后“被孤立的”节点数为 $n-x$。

最后放 AC 代码：

```cpp
#include<iostream>
using namespace std;
long long n,m,cnt;//注意要开long long
int main(){
	cin>>n>>m;
	if(n-m*2<0)cout<<0;
	else cout<<n-m*2;
	cout<<' ';
	for(int i=1;m>0;i++){//这里我直接让m每次减i-1条边，循环条件m>0
		m-=i-1;cnt++;//cnt就是上文的x
	}
	cout<<n-cnt;
	return 0;
}
```


---

## 作者：Fire_flame (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1065B)

# 分析

首先考虑最小值，因为我们要让所有的边都利用起来，每一条边都与一个没连过的节点相连。

最大值也很简单，因为我们要让没有连上的点尽可能的多，所以要尽可能的浪费边，也就是说构造一个 $n$ 阶完全图，使得  $\dfrac{n(n-1)}{2} \le m <\dfrac{n(n+1)}{2}$。

**注意**:要开 ```long long```**！！！**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,m;
ll calc(){
    for(ll i=1;i<=m;i++){
        if(i*(i+1)/2>=m)return n-i-1;
    }
}
int main(){
    scanf("%lld%lld",&n,&m);
    ll sma=n-2*m;
    if(n<=2*m)sma=0;
    ll big=calc();
    if(m==0){
        sma=n;
        big=n;
    }
    printf("%lld %lld",sma,big);
    return 0;
}
```


---

## 作者：Aventurine_stone (赞：1)

## 1. 题目分析
给你点数和边数，构造一个图，求最大和最小值。很简单构造题，稍微想一下就出结论了。
## 2. 题目做法
我们考虑进行分类讨论。  
先考虑特殊情况，如果 $m$ 为 $0$，那么最小和最大值都为 $n$。  
再考虑最小值，经过题目描述，我们可以得出结论，每连一条边，最多可使两个点不被孤立。所以如果 $m \times 2$ 大于等于 $n$，那么最小值就为 $0$，否则为 $n - m \times 2$。  
最后考虑最大值，也就是让不被孤立的点最少，很简单，让不被孤立的点尽量成为一个完全图就行了。  
如此便可完成此题。
## 3. 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100010;
inline long long read()
{
	long long x=0;
	char c=getchar();
	while(c<'0'||c>'9')
		c=getchar();
	while(c>='0'&&c<='9')
		x=(x<<1)+(x<<3)+c-'0',c=getchar();
	return x;
}
long long n,m,s;
int main()
{
	n=read(),m=read();
	if(!m)
	{
		printf("%lld %lld",n,n);
		return 0;
	}
	if(m*2>=n)
		printf("0 ");
	else
		printf("%lld ",n-m*2);
	for(int i=2;i<=n;i++)
	{
		s+=i-1;
		if(s>=m)
		{
			printf("%lld",n-i);
			return 0;
		}
	}
	printf("0");
	return 0; 
}
```

---

## 作者：NuoCarter (赞：1)

## CF1065B Vasya and Isolated Vertices 题解

### 题目分析

看着构造的标签进来的，~~进来前没想到这么简单~~

首先保留节点的最小值，就是让每一条边连接当前度数为 0 的两个点，这样子可以最大程度地利用每一条边。

所以 $\min=\max(0,n-2*m)$

那么保留节点的最大值，也就等价于最少的点连最多的边，很容易想到完全图，也就是点数为 $n$ 的简单图 $G$ ，最多有 $\frac{n*(n-1)}{2}$ 条边。

二分出边数 $\geq m$ ，点数最小且为 $t$ 的完全图，

则 $\max=n-t$

### Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
template <typename T>
inline void read(T &x){
    x=0;char ch=getchar();bool f=false;
    while(!isdigit(ch)) f|=ch=='-',ch=getchar();
    while(isdigit(ch))  x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    x=f?-x:x;return;
}
template <typename T>
inline void print(T x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) print(x/10);
    putchar(x%10^48);return;
}
#define ll long long
ll n,m;
int main(){
    read(n),read(m);ll minn=0,maxn=0;
    minn=max(0ll,n-2*m);print(minn),putchar(' ');
    ll l=0,r=n;
    while(l<=r){
        ll mid=(l+r)>>1;
        if(mid*(mid-1)/2>=m)    r=mid-1,maxn=mid;
        else l=mid+1;
    }
    print(n-maxn);
    return 0;
}
```

---

## 作者：I_am_Tangser (赞：0)

## 题目大意

一共有 $n$ 个点，可以连接 $m$ 条边，问与其他点没有连接的点最少是多少，最多是多少（不能有重边或自环）.

## 题目思路

### 最少

想要让这种点最少，就要让最多的点有边，也就要用最节省的办法：一个点**只**与另一个点连一条边。这样 $m$ 条边就可以让 $2 \times m$ 个点有连接，一定是最优的。但是注意判断 $2 \times m >n$ 的情况。

### 最多

想要让这种点最多，就要让最少的点有边，也就要用最奢侈的办法：对于一个集合，每两个点之间都要连一条边，这个我们可以用循环来计算。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,ans;
int main(){
	cin>>n>>m;
	while(ans*(ans-1)/2<m)ans++;
	cout<<max((long long)0,n-m*2)<<" "<<n-ans;
	return 0;
}
```

---

## 作者：Wrong_Accept (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1065B)

## 前置知识
完全图：一个有 $n$ 个节点的无向图是完全图，当且仅当图中有 $\frac {n (n - 1)} {2}$ 条边，且每个节点的度为 $n - 1$。

## 题目分析
求最大：

我们要使“被孤立的”节点尽量多，就要**连尽可能多的“无用边”**。  
例如在节点 $1$ 与节点 $2$ 之间有边，在节点 $2$ 与节点 $3$ 之间有边的情况下，再连一条边从节点 $1$ 到节点 $3$。

不难想出，我们**用已有的边创造一个完全图**，多的边可以把**剩余任意一个节点**与完全图的节点**一一相连**，从而使“被孤立的”节点最多。

求最小：

我们要使“被孤立的”节点尽量少，就要**节约用边**，使一条边发挥它的最大价值——**连接两个“被孤立的”节点**。  
就是在节点 $1$ 与节点 $2$ 之间连边，在节点 $3$ 与节点 $4$ 之间连边，在节点 $n$ 与节点 $n + 1$ 之间连边。

多的边则可以浪费，但值得注意的是：“被孤立的”节点**数量不可能为负数**。

放代码之前，提醒大家：  
**不开 long long 见祖宗！**

### AC code
```cpp
void solve()
{
    ll n, m, ans;
    cin >> n >> m;
    if (!m)
    {
        cout << n << ' ' << n << '\n';
        return;
    }
    if (m * 2 >= n)
        cout << "0";
    else
        cout << n - m * 2;
    for (ans = 0; ans * (ans + 1) / 2 < m; ans++)
        ;
    cout << ' ' << n - ans - 1 << '\n';
    return;
}
```

---

## 作者：jiangjiangQwQ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1065B)
### 前置知识点
首先我们知道一个有 $n$ 个顶点的完全图边数为 $n\times(n-1)$。
这有利于我们之后求解“被孤立的”节点的最大值。
### 思路
对于最小化的“被孤立节点数”，就是要用**尽量少的边连尽量多的点**。
![](https://cdn.luogu.com.cn/upload/image_hosting/sy4j4esn.png)

那么从图中可以发现就是一条边两个点连是符合我刚才所述的最小化“被孤立节点数”的方法。也就是说 $m$ 条边最多连 $m\times2$ 个点。所以最小值 $=\max(n-m\times2,0)$。然后最大值就是仿照完全图的连法，就可能是**一点多边**，最大化“被孤立节点数”。所以可以用二分“被孤立节点数”，判断剩下的点按照完全图来连是否 $\leq m$ 就可以了。

### 代码实现
```cpp
#include<iostream>
using namespace std;
#define dy; ios::sync_with_stdio(false),cin.tie(),cout.tie();
#define int long long
#define re register
#define For(i,l,r) for(re int i=l;i<=r;i++)
const int N=1e5+5;
int n,m;bool check(int k){
	int num=n-k;
	return m<=num*(num-1)/2;
}
signed main() {
	dy;cin>>n>>m;int t=n-m*2;
	if(t<0) cout<<0;
	else cout<<t;
	int L=0,R=n,ans;
	while(L<=R){
		int mid=(L+R)>>1;
		if(check(mid)) L=mid+1,ans=mid;
		else R=mid-1;
	} cout<<' '<<ans;
	return 0;
}

```

---

## 作者：Zhddd_ (赞：0)

## 题目分析

对于最小值，一条边可以连接两个节点，所以能减少两个“孤立点”，但注意减到 $0$ 以后不会再减，所以答案为 $\max(n - 2m, 0)$。

对于最大值，我们要尽可能地多浪费边在几个点上，使得剩下的孤立点最多。

在没有重边与自环的情况下，$n$ 个点之间最多连接 $\dfrac{n(n - 1)}{2}$ 条边，所以我们枚举这个 $n$ 的最小值，再用 $n$ 减去即可。

**注意特判 $m = 0$ 的情况**

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
typedef long long LL;
LL n, m;
LL minn, maxn;
int main() {
	scanf("%lld%lld", &n, &m);
	minn = max(n - 2 * m, 0ll); //注意这里的 0 要转换为 long long
	printf("%lld ", minn);
	for (LL i = -1; ; i++) { //把 i 的初值设为 -1 就可以特判 m = 0 的情况
		if (i * (i + 1) / 2 >= m) {
			printf("%lld", n - i - 1);
			break;
		}
	}
	return 0;
}
```

---

## 作者：_zexal_ (赞：0)

## 题意
给你 $n$ 个点和 $m$ 个边。让你输出最多和最少有哪些点没有其他边相连。
## 思路
我们先考虑最小的情况，我们用一种贪心策略，既然要我们被孤立的点最小，那么每一次我们优先连接两个还没有建立边的点即可，这样我们被孤立的点最少就为 $max(0,n-(m \times 2))$ 。接着我们考虑最大，我们只需要在不重边的情况下浪费每一条边即可，所以我们尽可能构造点多的一个**完全图**即可，这里我们可以用枚举或二分来算出他的顶点的数量。这里顺便讲一下完全图，就是每个点相互之间都有一条边相连，有 $n$ 个顶点，有 $n\times(n+1)/2$ 条边。
#### 二分的正确性
这里讲一下为什么二分是正确的，因为我们假设把 $ n \times (n+1)/2$ 这个式子看成一个函数，那么无疑，他是单调上升的，所以我们可以通过二分来枚举顶点数量。
## 坑点
注意 $n \leq 10^5$ 还有特判 $m=0$ 的时候(~~让我调了半个小时~~)。
## ACCode
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m; 
int main(){
	scanf("%lld%lld",&n,&m);
	cout<<max(n-m*2,0ll)<<" ";
	for(long long i=1;i<=n;i++){
		if(i*(i+1)/2>=m){//枚举我们至少要用多少点
			cout<<n-i-1;
			break;
		}
	} 
	return 0;
}
```


---

## 作者：XL4453 (赞：0)

### 解题思路：

简单构造。

考虑让孤立点最小，显然先让两个都没有边的点连边，这样一次就少了两个孤立点，不可能存在比这个更优的方案。

然后考虑让孤立点最多，由于不能有重边和自环，所以一定是构成一个完全图之后再加几条边到一个点达到总边数条件独立点最多。（边尽可能密集地分布在某一些点上）

知道了这些，代码就好写了，可以用二分实现后者，也可以数学算出（但好像没有二分简单）。

---
### 代码（二分实现）：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
long long n,m,l,r,mid;
int main(){
	scanf("%I64d%I64d",&n,&m);
	printf("%I64d ",max(0ll,n-2*m));
	r=n+m;
	long long ans=0;
	while(l<=r){//二分出一个边数超过 m 的最小完全图，然后用 n 去减，就得到了孤立点的个数
		mid=l+r>>1;
		if((mid-1)*mid<2*m)l=mid+1,ans=l;
		else r=mid-1;
	}
	printf("%I64d",n-ans);
	return 0;
}
```


---

## 作者：king_xbz (赞：0)

比较裸的构造题，但我和其他几篇题解判断最大孤立点的方法不太一样，故发一篇题解。

本题需要求被孤立的点可能的最大值和最小值。

首先比较好考虑的是最小，我们将每两个点就连上一条边，这样就最大化的利用每条边(将两个孤立点转化为不被孤立的点)

那么$n>2*m$时会有$n-2*m$个孤立点

否则没有孤立点(默认数据不会导致重边)

接下来考虑最大值

我们尽可能的重复配对去把边用完

比如两个点就$1-2$，三个点就$1-2,1-3,2-3$，四个点就是$1-2,2-3,3-4,1-3,1-4,2-4$这样连，直到把$m$条边用完。我们可以发现，能让$i$个点相连需要的最多边是$\frac{i*(i-1)}2$，我们不断按照这个规则匹配直到边超过$m$即可

注意特判：$m=0,cout<<n<<" "<<n$;

$n=1,cout<<1<<" "<<1$

$m=1,cout<<n-2<<" "<<n-2$

干就完了.

代码：

```cpp
signed main()
{
	int n,m;
	cin>>n>>m;
	if(n==1)
	{
		cout<<1<<" "<<1;
		return 0;
	}
	if(m==0)
	{
	    cout<<n<<" "<<n;
	    return 0;
	}
	if(m==1&&n>=2)
	{
		cout<<n-2<<" "<<n-2;
		return 0;
	}
	if(n-m*2>0)
	cout<<n-m*2<<" ";
	else
	cout<<0<<" ";
	int now=-1;
	for(fint i=2;i<=n;i++)
	if(i*(i-1)/2>=m)
	{
		now=i;
		break;
	}
	now==-1?cout<<0:cout<<n-now;
	return 0;
} 
```



---

## 作者：花里心爱 (赞：0)

### CF1065B 题解
不得不说这题细节还是挺多的……

题目中定义了无向图上“被孤立的”节点为和其他节点之间都没有连边的节点，问图中“被孤立的”节点的可能的最小值和最大值。

考虑如何构造图才可以使“被孤立的”节点最小。根据定义，我们只需要将一个点连一条边，就可以使该节点不是被孤立的。最大限度地利用$m$条边的方法就是将图中的每2个节点连一条边（当然如果有剩余的边就可以随便加了）。

再考虑如何构造图才可以使“被孤立的”节点最大。我们首先选出一个点作为不是被孤立的。每当有剩余的边时，新加一个节点作为不是被孤立的，然后将这个点向所有已经不是被孤立的点连边（此时消耗的边数最大，为已经不是被孤立的点的数量）。

当然有两点需要注意：

当$\ m=0\ $时，所有的点都不可能连通，最小值和最大值均为$n$。

当$\ m=1\ $时，一定有2个点连通，最小值和最大值均为$n-2$。

下面是AC代码：
```
#include<cstdio>
#include<cctype>
#define ll long long
using namespace std;
inline ll read(){
    ll d=0;char ch=getchar();while(!isdigit(ch))ch=getchar();
    while(isdigit(ch)){d=d*10+ch-48;ch=getchar();}return d;
}
ll n,m;
ll mx,mn;
int main(){
	n=read(),m=read();
	if(m==0){  //特判m=0的情况
		printf("%lld %lld",n,n);
		return 0;
	}
	if(m==1){  //特判m=1的情况
		printf("%lld %lld",n-2,n-2);
		return 0;
	}
	mn=n-(m<<1);
	if(mn<0)mn=0;
	for(mx=2;mx<=n;++mx){//当还有剩余的边时，新加节点到不是被孤立的点的集合中
		m-=(mx-1);
		if(m<=0)break;
	}
	printf("%lld %lld",mn,n-mx);//最大值为总的数量减不是被孤立的点的数量
    return 0;
}
```

---

