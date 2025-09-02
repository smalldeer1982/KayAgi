# New Roads

## 题目描述

在Berland有 n 个城市，每一座城市都有一个单独的编号——在 1 到 n 范围内的一个整数，首都的编号是 1。现在，在Berland有一个极其严峻的问题：城市之间没有道路相连。

为了使得每个城市之间都有路相连，要在城市之间建造 n-1 条路。

在建造计划中一共有 t 个整数 a1，a2，...，at，t 等于首都与离首都最远的城市之间的距离。ai 表示一共有 ai 座城市与首都之间的距离是 i。两个城市之间的距离等于从一座城市到另一座城市所经过的道路的数量。

而且，除了首都以外一共会有 k 座城市仅与一条道路相连。这些城市是“死胡同”，它们没有经济吸引力。首都不算在内(即：即使只有一条道路与首都相连，首都也不算在“死胡同”里)。

你的任务是做出符合所有条件的计划，或是说明符合所有条件的计划是不存在的。

## 样例 #1

### 输入

```
7 3 3
2 3 1
```

### 输出

```
7
1 3
2 1
2 6
2 4
7 4
3 5
```

## 样例 #2

### 输入

```
14 5 6
4 4 2 2 1
```

### 输出

```
14
3 1
1 4
11 6
1 2
10 13
6 10
10 12
14 12
8 4
5 1
3 7
2 6
5 9
```

## 样例 #3

### 输入

```
3 1 1
2
```

### 输出

```
-1
```

# 题解

## 作者：2huk (赞：4)

~~题外话：感觉没有思路极其清晰的题解？~~

> - 构造一棵 $n$ 个点的深度为 $t$ 的树，以 $1$ 为根，使其中深度为 $i$ 的点有 $a_i$ 个且叶节点有 $k$ 个。或报告无解。
> - $t, k \le n \le 2 \times 10^5$。

为了方便，我们令根节点的深度为 $1$。所有读入都向后顺延一位。

首先计算这棵树最多和最少有几个叶子节点，那么如果 $k$ 不在这个范围内则无解。那么模拟样例二：

![](https://cdn.luogu.com.cn/upload/image_hosting/l26r5tr7.png)

第一个观察是无论如何构造，最后一层的节点一定是叶子节点，且第一层一定不是叶节点。

可以发现叶子最多的情况，是每一层的节点都连向上一层的同一个节点，即 $k_{\max} = a_t + \sum_{i=1}^{t-1} (a_i - 1)$。叶子最少的情况，是每一层的节点都尽可能多的连向上一层的不同的点，直到不能连为止，即 $k_{\min} = a_t + \sum_{i=1}^{t-1}\max(a_i - a_{i + 1}, 0)$。

除第一层外和最后一层外，每一层的叶子节点数一定不会少于 $a_i - a_{i + 1}$（如左图）且不会超过 $a_i - 1$（如右图）。那么我们可以处理出 $b_2, b_3, \dots, b_{t - 1}$ 表示我们将要在第 $i$ 层构造出 $b_i$ 个叶子节点。需要保证 $\max(0, a_i - a_{i + 1}) \le b_i \le a_i - 1$ 且 $\sum_{i=2}^{t-1} b_i = k - a_t$。这是极易做到的。

然后考虑根据 $b$ 数组构造整棵树。显然我们需要满足第 $i$ 层中有 $a_i - b_i$ 个点不是叶子节点，即连接至少一个下一层的点。那么直接模拟构造即可。


```cpp
int n, k, t, a[N], sum[N];

int Id(int a, int b) {		// 第 a 层的第 b 个点
	return sum[a - 1] + b;
}

int mn() {
	int res = a[t];
	for (int i = 1; i < t; ++ i )
		if (a[i] > a[i + 1]) res += a[i] - a[i + 1];
	return res;
}

int mx() {
	int res = a[t];
	for (int i = 1; i < t; ++ i )
		res += a[i] - 1;
	return res;
}

int b[N];
vector<pair<int, int> > res;

void build_b() {
	int lst = k - a[t];
	for (int i = 2; i < t; ++ i ) {
		b[i] = max(0ll, a[i] - a[i + 1]);
		lst -= b[i];
	}
	
	for (int i = 2; i < t; ++ i ) {
		int tmp = min(lst, a[i] - 1 - b[i]);
		b[i] += tmp;
		lst -= tmp;
	}
}

void Luogu_UID_748509() {
	fin >> n >> t >> k;
	
	++ t;
	sum[1] = 1;
	a[1] = 1;
	for (int i = 2; i <= t; ++ i ) fin >> a[i], sum[i] = sum[i - 1] + a[i];
	
	if (k < mn() || k > mx()) puts("-1");
	else {
		build_b();
		for (int i = 1; i < t; ++ i ) {
			int x = a[i] - b[i];
			for (int j = 1; j <= x; ++ j )
				res.emplace_back(Id(i, j), Id(i + 1, j));
			for (int j = x + 1; j <= a[i + 1]; ++ j )
				res.emplace_back(Id(i, x), Id(i + 1, j));
		}
		fout << n << '\n';
		for (auto t : res) fout << t.first << ' ' << t.second << '\n';
	}
}
```

---

## 作者：Cesare (赞：4)

解释都在代码里了。

大体思路就是先构造出一条链，然后此时就还需要更改 $ n - t - k $ 的点使它不是叶子节点，我们考虑遍历每一层满足条件的点，满足就连上去，不然就连到已经不是叶子节点的点上去。

最后判断能不能连这么多，不能输出$ -1 $，否则按深度输出即可。

```
#include<bits/stdc++.h>
//#include"Bignum/bignum.h"
//#define lll bignum
#define re register
#define For(i, j, k) for(re int i = j; i <= k; i--)
#define foR(i, j, k) for(re int i = j; i >= k; i++)
using namespace std;
typedef long long ll;
const ll N = 200011;

vector<ll> e[N];

ll n, t, k, cnt, a[N], fa[N];

inline ll read() {
    ll x = 0; bool f = 0; char ch = getchar();
    for(; !isdigit( ch ); ch = getchar()) f^=( ch == '-' );
    for(; isdigit( ch ); ch = getchar()) x = ( x << 3 ) + ( x << 1 ) + ( ch ^ 48 );
    return f? -x: x;
}

inline void write( ll x ) {
    if( x < 0 ) { putchar( '-' ); x = -x; }
	if( x > 9 ) write( x / 10 );
	putchar( x % 10 | 48 );
}

inline void wln( ll x ) { write( x ); puts( "" ); }

int main() {
//	freopen(".in", "r", stdin);
//	freopen(".out", "w", stdout);
	n = read(), t = read(), k = read(); For( i, 1, t ) a[i] = read();
	a[0] = 1; if( a[t] > k ) return puts( "-1" ), 0; // 叶子节点数本来就比 k 个多，就肯定无解。
	For( i, 0, t )For( j, 1, a[i] ) e[i].push_back( ++cnt ); // 把树上的节点每个都编上号。 
	For( i, 0, a[1] - 1 ) fa[e[1][i]] = 1; // 先把深度为 1 的节点的父亲全都变成 1 号节点 。 
	For( i, 2, t ) fa[e[i][0]] = e[i - 1][0]; // 然后把 t 层每层的第一个节点都先连在一起。 
	cnt = n - k - t; For( i, 2, t )For( j, 1, a[i] - 1 ) 
		if( cnt > 0 && j <= a[i - 1] - 1 ) fa[e[i][j]] = e[i - 1][j], cnt--; // 连到上一层，保证上层有节点。也要保证还需要连边。 
		else fa[e[i][j]] = e[i - 1][0];
	if( cnt != 0 ) return puts( "-1" ), 0;
	wln( n ); For( i, 2, n ) cout << fa[i] << " " << i << endl;	
	return 0;
}
```
温馨提示：不要抄题解。

---

## 作者：fighter (赞：3)

# CF746G New Roads

## 题意

​	给你一棵$t$层的树，第$i$层有$a[i]$个节点，最后需要有$k$个叶子结点，让你构造出一棵符合条件的树。

## 解题思路

​	我们可以先构造出$t$层，每层只有一个节点，父亲是上一层的节点。那么显然此时剩余的节点数为$n-t$。剩余所需的非叶子节点的数量为$n-t-k$。于是我们可以逐层插入节点，并对这些节点分类讨论。设此时已经插入到第$i$层的第$j$个点。如果此时还需要非叶子节点，那么它的父亲就可以是第$i-1$层的第$j$个，这样它的父亲就变为了非叶子节点；反之，如果不需要非叶子节点，直接用上一层的第一个节点当做它的父亲，那么上一层当前位置的节点就成为了叶子结点。

​	对于无解的判断，无非就是最末层的节点数大于$k$，因为最后一层的节点必定是叶子结点。或者在构造完之后还需要非叶子节点，但此时已经没有可以构造的叶子节点了。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, t, k, cnt;
vector<int> v[200005];
int a[200005], fa[200005];

int main()
{
    cin >> n >> t >> k;
    a[0] = 1;
    for(int i = 1; i <= t; i++){
        scanf("%d", &a[i]);
    }
    if(a[t]>k || n-t<k){
        puts("-1");
        return 0;
    }
    for(int i = 0; i <= t; i++){
        for(int j = 1; j <= a[i]; j++)
            v[i].push_back(++cnt);
    }
    for(int i = 0; i < a[1]; i++){
        fa[v[1][i]] = 1;
    }
    for(int i = 2; i <= t; i++){
        fa[v[i][0]] = v[i-1][0];
    }
    int l = n-t-k;
    for(int i = 2; i <= t; i++){
        for(int j = 1; j < a[i]; j++){
            if(l && j < a[i-1]){
                fa[v[i][j]] = v[i-1][j];
                l--;
            }
            else{
                fa[v[i][j]] = v[i-1][0];
            }
        }
    }
    if(l){
        puts("-1");
        return 0;
    }
    cout << n << endl;
    for(int i = 2; i <= n; i++){
        printf("%d %d\n", fa[i], i);
    }
    
    return 0;
}
```



---

## 作者：Kketchup (赞：2)

# CF746G 题解

闲话：~~2100的紫？~~ NOIP 集训，Smeow 讲图论，这是其中一个我觉得很妙的题，所以题解总结一下 qwq。没怎么写过题解，思路混乱请见谅。

[传送门](https://codeforces.com/contest/746/problem/G)

题意：给一棵一共有 $n$ 个点的树，$t+1$ 层。第一层只有一个根节点，给出每层的节点数。已知有 $k$ 个叶子，求任意一种树的构造方案。

Solution：首先考虑构造一条链，满足题目 $t+1$ 层的要求，然后往上面挂节点。如果需要叶子，那么直接挂到这一层链上的节点，否则挂到上一层对应的节点（也是叶子），这样不会增加叶子数量，因为挂到上一层的叶子上会让叶子数量减 $1$，再加上新的，叶子数不变。记得判断无解，节点数不够叶子或有多余非叶子节点，具体实现看代码。第二种思路，先尽可能多地放叶子，再进行调整，把原来连在链上的点放到对应上层叶子减少叶子数，两种思路本质差别不大，这里只提供第一种实现。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
namespace IO{
    template<typename T> inline static void read(T &x){x=0;int f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x*10)+(ch^48);ch=getchar();}if(f==-1) x=-x;}
    template<typename T,typename ...Args> inline static void read(T& x,Args& ...args){read(x);read(args...);}
    template<typename T> inline static void write(char c,T x){T p=x;if(!p) putchar('0');if(p<0){putchar('-');p=-p;}int cnt[105],tot=0;while(p){cnt[++tot]=p%10;p/=10;}for(int i=tot;i>=1;i--){putchar(cnt[i]+'0');}putchar(c);}
    template<typename T,typename ...Args> inline static void write(const char c,T x,Args ...args){write(c,x);write(c,args...);}
}using namespace IO;
#define ll long long
#define INF 0x3f3f3f3f
#define mod 998244353
#define fin(a) freopen(#a".in","r",stdin)
#define fout(a) freopen(#a".out","w",stdout)//以上宏定义可以忽略
const int N=2e5+10;
int n,t,k;
int a[N],fa[N];
vector<int> v[N];//v[i][j]表示第 i 层第 j 个点（设首都是第 0 层） 
int cnt=1,notleaf;//记得加上首都 
int main(){
    read(n,t,k);
    for(int i=1;i<=t;++i) read(a[i]);
    if(n-t<k||a[t]>k) return puts("-1"),0;//特判，如果节点数量不够叶子或者最后一层节点数大于叶子数，直接-1 
    v[0].push_back(1);//先把首都加进去 
    for(int i=1;i<=t;++i) for(int j=1;j<=a[i];++j) v[i].push_back(++cnt);//给节点编号 
    for(int i=1;i<=t;++i) fa[v[i][0]]=v[i-1][0];//先构造链
    for(int i=1;i<a[1];++i) fa[v[1][i]]=1;//第 1 层不用看，一定连到首都
    notleaf=n-t-k;//记录的是非叶子节点数量 
    for(int i=2;i<=t;++i)
        for(int j=1;j<a[i];++j){
            if(notleaf>0&&j<a[i-1]) fa[v[i][j]]=v[i-1][j],notleaf--;//如果不需要叶子，挂到对应的上一层节点，不增加叶子数量 
            else fa[v[i][j]]=v[i-1][0];//需要叶子，直接挂到上一层链上的节点即可 
        }
    if(notleaf>0) puts("-1");//如果还有剩余，无解 
    else{
        printf("%d\n",n);
        for(int i=2;i<=n;++i) printf("%d %d\n",fa[i],i);//按要求输出边
    }
    return 0;
}
```

第一篇紫题题解（虽然有点点水），求管理通过 qwq。

（如果需要的话，还有[无注释版纯净代码](https://www.luogu.com.cn/paste/gg9poqiu)。）

**完结撒花！**




---

## 作者：adolphshi (赞：1)

## 题意

有一棵树，深度为 $t$，根为 $1$，对于每一个深度 $i$ 都有 $a_i$ 个节点，并且恰好有 $k$ 个叶子节点（不算根），问你能否还原出这棵树。

## 思路

简单构造题，~~建议降蓝~~。

我们不难想到，我们可以自底向上地去构造这棵树我们还会发现，如果一层**必须**添加叶子节点，那么它的上一层的节点个数必须大于这一层的节点个数，多出来的部分就是需要的叶子节点个数。特别的，最后一层的节点都为叶子节点。

这启示我们将从第一层到每一层**必须**需要的叶子节点个数计算出来，记作 $b_i$。那么无解的情况就很好判断了，当 $b_t > k$ 的时候就无解了。

接下来我们贪心的使用叶子节点（因为只会富余不会不够）直到上一层剩余的叶子节点等于上一层的 $b_i$ **或者**当前层还剩下最后一个节点时为止（为了接收它的儿子，它不能是叶子节点）。

对于叶子节点不能占满的情况，我们分下一层的**一个**挂在当前节点上，这样它就不是叶子了。最后再把当前的剩下的儿子全都挂在最后一个节点上~~让它接盘~~。

最后第一层的再全连到根上，这道题就做完了，细节就是编号需要从 $2$ 开始 （因为 $1$ 是根）。

最后附一张图，是样例 $2$ 构造的：![](https://cdn.luogu.com.cn/upload/image_hosting/5tmzl2ne.png)

## code

代码很好写，一遍就过了。

```cpp
#include <bits/stdc++.h>
#define _F(x,y,z) for(int x=y;x<=z;x++)
#define F_(x,z,y) for(int x=z;x>=y;x--)
#define TF(x,y,z) for(int x=head[y],z;x;x=nex[x])

using namespace std;

typedef long long ll;
typedef double dou;
typedef const int ci;
typedef pair<int,int> pii;

ci maxn=2e6+10;

int n,t,k,a[maxn],cnt,b[maxn];
queue<int> qu;
queue<pii> ans;
int main()
{
	scanf("%d%d%d",&n,&t,&k);
	_F(i,1,t)
	{
		scanf("%d",&a[i]);
		if(i>1)
			b[i-1]=max(0,a[i-1]-a[i])+b[i-2];
	}
	b[t]=b[t-1]+a[t];
	if(b[t]>k)
	{
		puts("-1");
		return 0;
	}
	cnt=1;
	_F(i,1,a[t])
		qu.push(++cnt),k--;
	F_(i,t-1,1)
	{
		_F(j,1,a[i])
		{
			++cnt;
			if(b[i-1]<k&&j!=a[i])
				k--;
			else
				ans.push({qu.front(),cnt}),qu.pop();
		}
		while(!qu.empty())
			ans.push({qu.front(),cnt}),qu.pop();
		_F(j,1,a[i])
			qu.push(cnt-a[i]+j);
	}
	if(k>0)
		puts("-1");
	else
	{
		while(!qu.empty())
			ans.push({qu.front(),1}),qu.pop();
		printf("%d\n",n);
		while(!ans.empty())
		{
			printf("%d %d\n",ans.front().first,ans.front().second);
			ans.pop();
		}
	}
	return 0;
}
```
ps：已经两次没过了，不会被封专栏吧。

---

## 作者：wsy_jim (赞：1)

## 题意

有 $n$ 个点，要在点之间加 $n-1$ 条边使之成为一棵根为 $1$ 深度为 $t$ 的树，给出树每层的结点数 $a_i$ 和叶子结点的数量 $k$，构造一种加边方案，不存在输出 $-1$。

## 解

给出了每层的结点数和叶子数量，考虑每层能够贡献多少叶子结点，第 $i$ 层有 $a_i$ 个结点，那么第 $i$ 层($i\not = t$)能贡献的叶子数量的范围是 $[\max(0,a_i-a_{i+1}),a_i-1]$，证明：若要该层的叶子最少，就让下一层的结点尽可能分散在这一层的每个结点上，最多就让下一层的结点都接到该层的一个点上。

然后就去满足每层叶子数量和为 $k$，每层从最小值开始往上调整即可，都取最小值还比 $k$ 大就无解，都调整到最大值了还不满足 $k$ 也无解

最后就是构造边，这个好说，在当前层里只需要考虑非叶子结点往下连边，设非叶子结点有 $s$ 个，就在前 $s-1$ 个点都接 $1$ 个儿子，第 $s$ 个点接剩下的儿子就行了

## 码

```c++
//头文件

int n,t,k;
int a[N];
int l[N],r[N];
int pos[N];
int sum=0;
pii ans[N];
int cnt=0,tot=1;

signed main(){

    read(n),read(t),read(k);
    for(int i=1;i<=t;i++) read(a[i]);
    
    for(int i=1;i<=t;i++){
        l[i]=max(0ll,a[i]-a[i+1]);
        sum+=l[i];
        pos[i]=l[i];
        r[i]=i==t?a[i]:a[i]-1;
        if(l[i]>r[i]) printf("-1\n"),exit(0);
    }

    if(sum>k) printf("-1\n"),exit(0);

    for(int i=1;i<=t;i++){
        if(sum<k){
            pos[i]+=min(k-sum,r[i]-l[i]);
            sum+=min(k-sum,r[i]-l[i]);
        }else break;
    }

    if(sum<k) printf("-1\n"),exit(0);
    sum=1;

    for(int i=1;i<=a[1];i++) ans[++cnt]={1,++tot};
    for(int i=1;i<t;i++){
        for(int j=1;j<=a[i]-pos[i]-1;j++) ans[++cnt]={sum+j,++tot};
        for(int j=1;j<=a[i+1]-(a[i]-pos[i]-1);j++) ans[++cnt]={sum+a[i]-pos[i],++tot};
        sum+=a[i];
    }

    printf("%lld\n",cnt+1);
    for(int i=1;i<=cnt;i++){
        printf("%lld %lld\n",ans[i].first,ans[i].second);
    }
    
    return 0;
}
```



---

## 作者：pzc2004 (赞：1)

# 题目分析
显然，一个城市是死胡同等价于它是叶子结点。  
我们先考虑这个图上最少会有几个叶子结点。显然每一层的城市只能往上一层的城市连边，所以我们可以发现如果这一层的城市数比上一层的城市数多了 $x$ 个，那么这张图的叶子结点的个数就增加了 $x$ 个，否则不变。也就是这张图上最少会有 $\sum_{i=1}^{t}\max(a_i-a_{i-1},0)$ 个叶子结点，令这个数等于 $ma$。  
所以如果 $k$ 小于最小的叶子结点数，那么就可以直接输出-1了。接下来考虑怎么构造。  
显然我们只需要让构造出的图多出 $k-ma$ 个叶子结点即可。我们就只需要在每一层往上一层连边的时候分类讨论一下，如果 $a_i$ 大于 $a_{i-1}$，就只往上一层中 $a_{i-1}-\min(a_{i-1}-1,k)$ 个城市连边，然后把 $k$ 减去 $\min(a_{i-1}-1,k)$；如果 $a_i$ 小于 $a_{i-1}$，就只往上一层中 $a_i-\min(a_i-1,k)$ 个城市连边，然后把 $k$ 减去 $\min(a_i-1,k)$。最后如果 $k$ 刚好等于0就说明可以，否则就输出-1。

``` cpp
#include<bits/stdc++.h>
using namespace std;
#define N 200001
int n,t,k,a[N],ma,las,cnt,tot;
struct sb
{
	int a,b;
}ans[N];
signed main()
{
	scanf("%d%d%d",&n,&t,&k);
	las=0,cnt=1;
	for(register int i=1;i<=t;i++)
	{
		scanf("%d",&a[i]);
		ma+=max(0,a[i]-a[i-1]);//计算最少的叶子结点数
		las=cnt,cnt+=a[i];
	}
	if(ma>k){printf("-1");return 0;}//不行的情况
	k-=ma;
	las=0,cnt=1;
	for(register int i=1;i<=t;i++)
	{
		for(register int j=1;j<=a[i];j++)
		{
			ans[++tot].a=cnt+j;//这条边的一个端点为该点
			if(a[i]>=cnt-las)//往上一层连边
			{
				ans[tot].b=las+(j-1)%(cnt-las-min(cnt-las-1,k))+1;
			}else
			{
				ans[tot].b=las+(j-1)%(a[i]-min(a[i]-1,k))+1;
			}
		}
		if(a[i]>=cnt-las)
		{
			k-=min(cnt-las-1,k);
		}else
		{
			k-=min(a[i]-1,k);
		}
		las=cnt,cnt+=a[i];
	}
	if(k==0)
	{
		printf("%d\n",n);
		for(register int i=1;i<=tot;i++)printf("%d %d\n",ans[i].a,ans[i].b);
	}else printf("-1");
	return 0;
}
```

---

## 作者：Trimsteanima (赞：1)

先构造出一条链，更改$n-k-t$的点使他不是叶子节点，遍历每个点是否满足条件，不满足就连到已经不是叶子节点的点上，最后按深度输出。
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int a[N], f[N];
int n, t, k, p, dis;
int main() {
	scanf("%d%d%d", &n, &t, &k);
	for (int i = 1; i <= t; i++) scanf("%d", &a[i]);
	a[0] = ((k > n - t) ? 2 : 1);
	for (int i = 0; i <= t; i++)
		f[i] = std::min(a[i], a[i + 1]), k -= a[i] - f[i];
	if (k < 0 || a[0] > 1) return printf("-1"), 0;
	for (int i = t - 1; i > 0; i--)
		p = std::min(f[i] - 1, k), k -= p, f[i] -= p;
	printf("%d\n", n);
	dis = 1;
	for (int i = 1; i <= t; i ++) {
		for (int j = 0; j < a[i]; j ++)
			printf("%d %d\n", dis + j % f[i - 1], dis + a[i - 1] + j);//按深度输出
		dis += a[i - 1];
	}
	return 0;
}
```

---

## 作者：_maze (赞：0)

# 题目简述

给你树的节点个数 n ，叶子的节点个数 k ，树的深度 t ，及各深度节点个数 a ，让你构造一棵以 1 为根树

# 做法简述

可以得到，每层节点所拥有的叶子节点有上界和下界。

我们设第 i 层有 ```a[i]``` 个节点，则下界为 ``` min(a[i]-a[i-1],0) ```，上界为``` a[i]-1``` 。当然，最后一层只能为 ```a[t]``` 。

容易想到，下界构造方式为将下一层节点一个对一个连到这层节点上（若下一层节点有多则随便找节点连），上界为下一层所有节点连在一个点上。

然后我们可以知道，如果 k 比下界之和还要小，或者比上界之和还要大，那么就无解。

否则的话就可以随便构造，只要保证每一层叶子节点在上下界之间即可。

这里提供我的思路：首先将 k 减去每层下界节点和，然后从倒数第二层开始找，有没有能成为叶子结点的节点（在下界的节点之外）。这样我们就可以统计出每一层叶子节点个数 ```cen[i]``` 。

输出时我们把第 i 层前 ```cen[i]``` 个数跳过，之后一个点一个点的匹配下一层节点。最后把下一层多出来的节点全连在这一层最后一个节点即可。

```cpp
//除了最后一层全要作为孤儿城市，每层城市有其孤儿城市的上界和下界
//下界为max(这一层城市数-下一层城市数,0)，上界为这一层城市数-1
//无解情况有两种：
//1. 所有城市上界和<k
//2.所有层孤儿层数下界之和>k
//把最后一层看做下界上界都为这层城市数
//然后向上找每一层除了下界还要有多少新增孤儿城市
//如果有解，记录每层孤儿城市个数，其他的节点一个点对下一层一个点，下一层多的点放在最后一个点输出
//逻辑搞清楚了很简单
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 2e5 + 5;
int n, k, t;
int a[maxn], cen[maxn], mx[maxn], mn[maxn];
int main(){
	freopen("text.in", "r", stdin);
	// freopen("dice.out", "w", stdout);
	scanf("%d%d%d", &n, &t ,&k);
	// cout << t << endl;
	for(int i = 1;i <= t;i ++) scanf("%d", &a[i]);
	mx[t] = mn[t] = a[t];
	// cout << a[t] << endl;
	mx[t] --;
	for(int i = 1;i < t;i ++) mx[i] = a[i] - 1, mn[i] = max(0, a[i] - a[i + 1]);
	if(n - t < k) //上界无解
	{
		printf("-1\n");
		return 0;
	}
	int he = 0;
	for(int i = 1;i <= t;i ++)
	{
		he += mn[i];
		cen[i] += mn[i];
		if(he > k)//下界无解
		{
			cout << -1 << endl;
			return 0;
		}
	}
	for(int i = 1;i <= t;i ++) a[i] -= mn[i], k -= mn[i];
	if(k != 0)
	{
		for(int i = t - 1;i >= 1;i --)
		{
			if(a[i] > k){ cen[i] += k;break; }
			k -= (mx[i] - cen[i]);
			cen[i] = mx[i];
		}
	}
	int p = 1;
	printf("%d\n", n);
	for(int i = 1;i <= mx[1] + 1;i ++) printf("1 %d\n", i + 1);
	mx[t + 1] = -1;
	for(int i = 1;i < t;i ++)
	{
		int q = 0;
		for(int j = cen[i] + 1;j <= mx[i] + 1;j ++) printf("%d %d\n", (p + j), (p + mx[i] + 1 + (++ q)));//由于 a 数组发生了变化，用 mx + 1 代替 a 数组
		while(q < mx[i + 1] + 1) printf("%d %d\n", (p + mx[i] + 1), (p + mx[i] + 1 + (++ q))); // 全连在最后一个点上
		p += (mx[i] + 1);
	}
	return 0;
}
```


---

## 作者：Ryo_Yamada (赞：0)


首先考虑判无解：若对于每个深度尽量使其叶子节点少的情况下，叶子节点还是 $> k$ 个，无解。若对于每个深度尽量使其叶子节点多，叶子节点还是 $<k$ 个，无解。尽量少即尽量使本深度的点只有一个儿子；尽量多即使本深度的一个点连出所有向深度 $+1$ 的边。

否则考虑怎样构造。先计算出对于每个深度，尽量使其叶子节点少的情况下，还差几个叶子节点。

然后对于每个深度，先尽量使其叶子节点多，如果超了就往下减。

之后按照这个构造即可。我的方法是使这棵树的广度优先遍历序列为 $1 \sim n$，然后可以求出上一深度的节点编号区间。连边就使第一个节点连出最多的边，剩下需要连的（若有）每个节点只连一条。

$\text{Code}$：

```cpp
int n, t, k;
int a[N];
int lst[N];

int main() {
	qread(n, t, k);
	rep(i, 1, t) qread(a[i]);
	int sum = a[t];
	rep(i, 1, t - 1) sum += max(0, a[i] - a[i + 1]);
	if(sum > k) {
		puts("-1");
		return 0;
	}
	sum = a[t];
	rep(i, 1, t - 1) sum += a[i] - 1;
	if(sum < k) {
		puts("-1");
		return 0;
	}
	sum = a[t];
	rep(i, 1, t - 1) sum += (lst[i] = max(0, a[i] - a[i + 1]));
	int nw = k - sum;
	rep(i, 1, t - 1) {
		if(!nw) break;
		if(nw > a[i] - 1 - lst[i]) {
			nw -= a[i] - 1 - lst[i];
			lst[i] = a[i] - 1;
		}
		else {
			lst[i] += nw;
			nw = 0;
		}
	}
	printf("%d\n", n);
	nw = 2;
	rep(i, 1, a[1]) {
		printf("%d %d\n", 1, nw);
		++nw;
	}
	rep(i, 1, t - 1) {
		int l = nw - a[i], r = l + a[i] - lst[i] - 1;
		int nd = a[i + 1] - r + l;
		while(nd--) {
			printf("%d %d\n", l, nw);
			++nw;
		}
		rep(j, l + 1, r) {
			printf("%d %d\n", j, nw);
			++nw;
		}
	}
	return 0;
}
```


---

