# Subset Sums

## 题目描述

给定一个n个数的序列a，m个下标集合，记
$S_{k}=\{S_{k,i}\}$。
两种操作：

$1. $? k 求集合k的和，即
求集合k 所有元素做原数组下标的和

$2.$ + k w 给集合k的所有下标代表的数加w。

## 样例 #1

### 输入

```
5 3 5
5 -5 5 1 -4
2 1 2
4 2 1 4 5
2 2 5
? 2
+ 3 4
? 1
+ 2 1
? 2
```

### 输出

```
-3
4
9
```

# 题解

## 作者：Prurite (赞：9)

一年以前就闲得无聊地搓了这道题的翻译，现在来补一篇题解吧。

类似于分块的思想：**将所有的集合分为轻集合和重集合**，轻集合为其中元素数量 $\leq \sqrt n$ 的，其余集合为重集合。

这里的关键点是每个轻集合只有至多 $\sqrt n$ 个元素，同时至多只有 $\sqrt n$ 个重集合（因为限制了所有集合中的元素的数量和），这保证了时间复杂度。

显然轻集合可以直接暴力（复杂度为 $O(\sqrt n)$ ），而重集合可以先把相关信息预处理出来，并通过懒标记节省操作的时间，保证每次操作的复杂度不超过 $O(\sqrt n)$ 。具体而言，对于每个重集合预处理出其中元素的和，并对其记录一个懒标记。

为了快速地回答询问，对于每个集合（无论轻重）都记录它与每个重集合的交集大小，以便快速将这个重集合的懒标记应用到对这个集合的询问上，这可在 $O(n\sqrt n)$ 的时空复杂度内解决。为了统计交集，对于每个重集合，开一个大小为 $n$ 的布尔数组，记录哪些元素在这个集合内，以 $O(1)$ 判断一个元素是否在一个集合内。

所以我们一共要记录这些信息：每个集合包含的元素，每个重集合的懒标记，每个重集合的未包含懒标记的元素和，每个重集合与每个其他集合的交集大小。

**如果上面的几段没有看懂可以对照着下面的操作来理解。**

现在我们来考虑 $4$ 种可能的操作：

1. 对轻集合做加：遍历集合中的所有元素并且更新它们的值，然后遍历所有的重集合，并按照之前记录的相交大小更新这个重集合的元素和。时间复杂度 $O(\sqrt n)$ 
2. 对重集合做加：直接更新该集合的懒标记。时间复杂度 $O(1)$ 
3. 询问轻集合：遍历所有集合中的节点，统计答案，并遍历所有重集合，统计懒标记，按照与这个轻集合相交部分加入答案。时间复杂度 $O(\sqrt n)$ 。
4. 询问重集合：在已经记录的元素和的基础上统计自己及其他重集合的懒标记的贡献。时间复杂度 $O(\sqrt n)$ 。

一共有 $n$ 个操作，所以总时间复杂度为 $O(n\sqrt n)$ 。

代码如下：

```cpp
// Author: prurite
// Date: 2019.08.21
// RecordID: 23128664

#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <bitset>
#include <algorithm>
using namespace std;
typedef long long ll;

const int N = 1e5 + 10, M = 350;

bitset<N> digit[M];
// digit[i][j] 记录集合 i 中是否包含元素 j 
ll a[N], lazy[M], sum[M];
// a 为一开始时的数列, lazy 和 sum 是针对重集合维护的信息
int itsec[M][N];
// itsec[i][j] 表示重集合 i (重编号后的) 与集合 j (编号前的) 的交集大小
int heavy[M], pos[N];
// heavy[i] 表示第 i 个重集合的原编号
// pos[i] 表示集合 i 对应第几个重集合 (如果它不是重集合则为 0 )
vector<int> sets[N];
// sets[i] 记录集合 i 中包含哪些元素

int main( )
{
	int n, m, q;
	scanf( "%d %d %d", &n, &m, &q );
	for ( int i = 1; i <= n; i++ )
		scanf( "%lld", &a[i] );
	int bsiz = sqrt( n ), bid = 0;
	for ( int i = 1; i <= m; i++ )
	{
		int k, x;
		scanf( "%d", &k );
		for ( int j = 1; j <= k; j++ )
		{
			scanf( "%d", &x );
			sets[i].push_back( x );
		}
		if ( k > bsiz )
		{
			heavy[++bid] = i, pos[i] = bid;
			for ( auto j : sets[i] )
			{
				digit[bid][j] = 1;
				sum[bid] += a[j];
			}
		} // 预处理重集合信息
		else
			pos[i] = 0;
	}
	for ( int i = 1; i <= bid; i++ )
		for ( int j = 1; j <= m; j++ )
			for ( auto k : sets[j] )
				itsec[i][j] += (int)digit[i][k];
	// 统计集合间的相交情况
	for ( int i = 1; i <= q; i++ )
	{
		char s[10];
		int k, x;
		scanf( "%s", s );
		if ( s[0] == '?' )
		{
			scanf( "%d", &k );
			ll res = 0;
			if ( pos[k] )
			{
				res = sum[pos[k]];
				for ( int j = 1; j <= bid; j++ )
					res += lazy[j] * itsec[j][k];
			} // 询问重集合
			else
			{
				for ( auto j : sets[k] )
					res += a[j];
				for ( int j = 1; j <= bid; j++ )
					res += lazy[j] * itsec[j][k];
			} // 询问轻集合
			printf( "%lld\n", res );
		}
		else if ( s[0] == '+' )
		{
			scanf( "%d %d", &k, &x );
			if ( pos[k] )
				lazy[pos[k]] += x; // 加 重集合
			else
			{
				for ( auto j : sets[k] )
					a[j] += x;
				for ( int j = 1; j <= bid; j++ )
					sum[j] += x * itsec[j][k];
			} // 加 轻集合
		}
	}
	return 0;
}
```

---

## 作者：do_while_true (赞：4)

默认 $n,m,q,\sum |S|$ 同阶。

大小 $<\sqrt n$ 的称为小集合，$>\sqrt n$  的称为大集合，其中大集合的个数不超过 $\sqrt n$ 个。

可以提前 $\mathcal{O}(n\sqrt n)$ 地预处理出与其他所有集合之间有多少重复的元素，开个桶就可以。

对于每个大集合，直接记录 $w$ 为集合内所有数的和，记录一个 $v$ 代表 $2$ 操作给这个集合加了多少。

对于大集合的修改：$\mathcal{O}(\sqrt n)$ 复杂度内给其他每个大集合记录下产生贡献（通过预处理已经可以 $\mathcal{O}(1)$ 算出 $w$ 应该增长多少）。

对于小集合的修改：给原数组对应处的位置加上数，然后也是将 $\mathcal{O}(\sqrt n)$ 个大集合的 $w$ 加上某个数。

对于大集合的询问：大集合和小集合的修改都已经修改到了 $w$ 上，所以答案就是对应的 $w$．

对于小集合的询问：首先 $\mathcal{O}(\sqrt n)$ 遍历原数组对应处位置，能知道小集合的修改对其的贡献；然后遍历 $\mathcal{O}(\sqrt n)$ 个大集合，根据预处理和 $v$ 的记录能够 $\mathcal{O}(1)$ 算出大集合的修改对其的贡献。

综上所述，复杂度为 $\mathcal{O}(n\sqrt n)$．

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<unordered_map>
#define pb emplace_back
#define mp std::make_pair
#define fi first
#define se second
typedef long long ll;
typedef std::pair<int, int> pii;
typedef std::pair<ll, int> pli;
typedef std::pair<ll, ll> pll;
typedef std::vector<int> vi;
typedef std::vector<ll> vll;
const ll mod = 998244353;
ll Add(ll x, ll y) { return (x+y>=mod) ? (x+y-mod) : (x+y); }
ll Mul(ll x, ll y) { return x * y % mod; }
ll Mod(ll x) { return x < 0 ? (x + mod) : (x >= mod ? (x-mod) : x); }
ll cadd(ll &x, ll y) { return x = (x+y>=mod) ? (x+y-mod) : (x+y); }
template <typename T> T Max(T x, T y) { return x > y ? x : y; }
template <typename T> T Min(T x, T y) { return x < y ? x : y; }
template <typename T>
T &read(T &r) {
	r = 0; bool w = 0; char ch = getchar();
	while(ch < '0' || ch > '9') w = ch == '-' ? 1 : 0, ch = getchar();
	while(ch >= '0' && ch <= '9') r = r * 10 + (ch ^ 48), ch = getchar();
	return r = w ? -r : r;
}
const int N = 100010;
const int B = 316;
int n, m, q;
int siz[N];
vi s[N];
ll w[N], v[N], a[N];
int vis[N], cnt[B+10][N], pos[N], rk[N], pct;
void calc(int p) {
	for(auto x : s[p]) vis[x] = 1, w[p] += a[x];
	for(int i = 1; i <= m; ++i)
		for(auto x : s[i])
			if(vis[x])
				++cnt[pos[p]][i];
	for(auto x : s[p]) vis[x] = 0;
}
signed main() {
	read(n); read(m); read(q);
	for(int i = 1; i <= n; ++i) read(a[i]);
	for(int i = 1; i <= m; ++i) {
		read(siz[i]);
		for(int j = 1, x; j <= siz[i]; ++j) read(x), s[i].pb(x);
	}
	for(int i = 1; i <= m; ++i)
		if(siz[i] > B)
			pos[i] = ++pct, rk[pct] = i, calc(i);
	for(int o = 1; o <= q; ++o) {
		char ch = getchar(); int k, x;
		while(ch != '?' && ch != '+') ch = getchar();
		if(ch == '+') {
			read(k); read(x);
			if(siz[k] > B) {
				v[k] += x;
				for(int i = 1; i <= pct; ++i)
					w[rk[i]] += 1ll * cnt[i][k] * x;
			}
			else {
				for(auto i : s[k]) a[i] += x;
				for(int i = 1; i <= pct; ++i)
					w[rk[i]] += 1ll * cnt[i][k] * x;
			}
		}
		else {
			read(k);
			if(siz[k] > B) printf("%lld\n", w[k]);
			else {
				ll ans = 0;
				for(auto i : s[k]) ans += a[i];
				for(int i = 1; i <= pct; ++i)
					ans += v[rk[i]] * cnt[i][k];
				printf("%lld\n", ans);
			}
		}
	}
	return 0;
}
```

---

## 作者：chenxia25 (赞：4)

一眼根分，我们来考虑考虑这类根分问题该如何理清杂乱无章的操作。

我们考虑一开始令操作集合为空，然后慢慢把四种操作依次加入，看需要增添哪些动作。

一开始：【】

加入「小查」：那显然直接跑是根号的。于是：

1. 小查：直接跑。

加入「小修」：那显然直接跑是根号的。于是：

1. 小查：直接跑；
1. 小修：直接跑。

加入「大查」：大集合需要依赖小集合修改对它的贡献（目前还没有大修），而不能自己跑。于是在每次小修的时候对每个大集合贡献一波即可，贡献的值显然是增加的值乘以它们之间重合的数量，复杂度根号。所有集合与所有大集合重合的数量显然可以线根预处理，要用 `int` 存不然空间开不下。于是：

1. 小查：直接跑；
1. 小修：直接跑 + 对大集合贡献；
1. 大查：原来的和 + 小修对大集合的贡献；

加入「大修」：它自己什么都做不了，只能打个标记，然后让别的操作（小查、大查）来枚举大集合打下的标记。枚举到的时候的贡献显然是当前大集合的标记乘以重合数量，这个预处理过了。

于是：

1. 小查：直接跑 + 大修的标记；
1. 小修：直接跑 + 对大集合贡献；
1. 大查：原来的和 + 小修对大集合的贡献 + 大修的标记；
1. 大修：打标记。

直接做就可以了，复杂度线根。

---

## 作者：lilong (赞：2)

关键性质：大小超过 $\sqrt{n}$ 的集合数量不超过 $\sqrt{n}$ 个，其余集合大小不超过 $\sqrt{n}$。考虑根号分治，对于大小超过 $\sqrt{n}$ 的集合，由于这样的集合数量较少，因此修改时可以直接维护对每个这样的集合的总贡献（集合的交集大小可以预处理）。查询时如果是小集合就把大集合的标记下放给它，最后再回收。具体如下：

- 修改时如果是小集合，那么先暴力修改每个对应的元素，再更新每个大集合的总和（小对大）；如果是大集合，则打上标记，并更新每个大集合的总和（大对大）。
- 查询时如果是小集合，先暴力累加对应元素的和（小对小），再加上每个大集合的标记乘上交集的大小（大对小）；如果是大集合，直接输出即可。时间复杂度 $O((n+m+q)\sqrt{n})$。


```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#define B 1010
#define ll long long
#define N 100010
using namespace std;
vector<int>G[N+10],H[N+10];
int n,m,q,k,len;
ll a[N+10];
int cnt1[N+10][N/B+10],cnt2[N/B+10][N/B+10];
int id1[N+10],id2[N+10],tot1,tot2,id[N];
ll sum[N],lzy[N];
int ls1[N+10],ls2[N+10],t1,t2;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    ll x,y;
    cin>>n>>m>>q;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    for(int i=1;i<=m;i++){
        cin>>len;
        while(len--){
            cin>>x;
            G[i].push_back(x);
            H[x].push_back(i);
            sum[i]+=a[x];
        }
        if(G[i].size()<=B)id1[++tot1]=i,id[i]=tot1;
        else id2[++tot2]=i,id[i]=tot2;
    }
    for(int i=1;i<=n;i++){
        a[i]=0;
        t1=t2=0;
        for(auto j:H[i]){
            if(G[j].size()<=B)ls1[++t1]=id[j];
            else ls2[++t2]=id[j];
        }
        for(int j=1;j<=t1;j++)
            for(int k=1;k<=t2;k++)
                cnt1[ls1[j]][ls2[k]]++;
        for(int j=1;j<=t2;j++)
            for(int k=1;k<=t2;k++){
                if(j==k)continue;
                cnt2[ls2[j]][ls2[k]]++;
            }
    }
    char op;
    while(q--){
        cin>>op;
        if(op=='+'){
            cin>>x>>y;
            if(G[x].size()<=B){
                for(auto i:G[x])
                    a[i]+=y;
                // sum[x]+=G[x].size()*y;
                for(int i=1;i<=tot2;i++)
                    sum[id2[i]]+=1ll*cnt1[id[x]][id[id2[i]]]*y;
            }
            else{
                sum[x]+=1ll*G[x].size()*y;
                lzy[x]+=y;
                for(int i=1;i<=tot2;i++){
                    if(id2[i]==x)continue;
                    sum[id2[i]]+=1ll*cnt2[id[x]][id[id2[i]]]*y;
                }
            }
        }
        if(op=='?'){
            cin>>x;
            if(G[x].size()<=B){
                for(auto i:G[x])
                    sum[x]+=a[i];
                for(int i=1;i<=tot2;i++)
                    sum[x]+=1ll*lzy[id2[i]]*cnt1[id[x]][id[id2[i]]];
                cout<<sum[x]<<'\n';
                for(auto i:G[x])
                    sum[x]-=a[i];
                for(int i=1;i<=tot2;i++)
                    sum[x]-=1ll*lzy[id2[i]]*cnt1[id[x]][id[id2[i]]];
            }
            else{
                cout<<sum[x]<<'\n';
            }
        }
    }
    return 0;
}
```

---

## 作者：Feyn (赞：2)

[link](https://www.luogu.com.cn/problem/CF348C) & [my blog](https://feynn.github.io/)

一道还算不错的根号分治题目。

为啥是根号分治呢，看它比较简洁的要求，看它 $10^5$ 的数据范围和 $3$ 秒的时限，再加上它每个组分得毫无规律，多半是根号分治。然后套路地把所有集合划分成大集合和小集合，然后套路地让别人去更新大集合，然后小集合去更新别人。接下来是展开来说具体做法。

首先是大集合。大集合的答案显然来自于两个个方面：原来数列中的数以及后来更新的数。前者不多说，后者可以看成是这样的：假设 $add_x$ 代表这个集合已经加上的数的和，当前集合是 $y$，那么第二部分的答案应该是 $\sum\limits_{x}add_x\times|x\cap y|$。于是要维护的东西就比较显然了，只需要维护每个集合和每个大集合的交集大小，在更新的时候遍历所有大集合，更新当前加的值乘上交集大小即可。该部分显然是 $O(\sqrt N)$ 的。

然后是小集合。由于大集合不会去更新小集合的答案（不然复杂度爆炸），小集合的答案来自于三个方面：原来的数、小集合更新的数、大集合更新的数。第一个不说，第二个，由于小集合元素少，可以每次更新小集合的时候都遍历集合元素并把变化量累加到每个位置上，查询的时候也是遍历元素查询即可。至于第三个，可以用相似的方法，遍历这个集合和所有大集合的交集，算上大集合的变化量即可。

细节不是很多，放一下代码：

```cpp
#include<bits/stdc++.h>
//#define feyn
#define int long long
#define ptt pair<int,int>
#define mp make_pair
using namespace std;
const int N=100010;
const int P=1000;
inline void read(int &wh){
    wh=0;int f=1;char w=getchar();
    while(w<'0'||w>'9'){if(w=='-')f=-1;w=getchar();}
    while(w<='9'&&w>='0'){wh=wh*10+w-'0';w=getchar();}
    wh*=f;return;
}

int m,n,q,a[N],addTag[N],sum[N];

vector<int>s[N],pl[N];
vector<ptt>f[N];

int iNum,ins[N],insId[N];
bitset<N>vis[P];

signed main(){
	
	#ifdef feyn
	freopen("in.txt","r",stdin);
	#endif
	
	read(m);read(n);read(q);
	for(int i=1;i<=m;i++)read(a[i]);
	for(int i=1;i<=n;i++){
		int nowNum,nowData;read(nowNum);
		while(nowNum--)read(nowData),s[i].push_back(nowData);
		if(s[i].size()>P){
			ins[++iNum]=i;insId[i]=iNum;
			for(int Data:s[i]){
				pl[Data].push_back(i);
				vis[iNum].set(Data);
				sum[i]+=a[Data];
			}
		}
	}
	for(int x=1;x<=n;x++){
		if(s[x].size()<=P)continue;
		int xx=insId[x];
		for(int y=1;y<=n;y++){
			int nowNum=0;
			if(s[y].size()<=P)for(int Data:s[y])nowNum+=vis[xx][Data];
			else nowNum=(vis[xx]&vis[insId[y]]).count();
			f[y].push_back(mp(x,nowNum));
		}
	}
	while(q--){
		char op;int x,y;cin>>op;read(x);
		if(op=='?'){
			if(s[x].size()<=P){
				int nowAn=0;
				for(int Data:s[x])nowAn+=a[Data];
				for(ptt Data:f[x])nowAn+=addTag[Data.first]*Data.second;
				printf("%I64d\n",nowAn);continue;
			}
			printf("%I64d\n",sum[x]);continue;
		}
		read(y);addTag[x]+=y;
		if(s[x].size()<=P)for(int nowPl:s[x])a[nowPl]+=y;
		for(ptt Data:f[x])sum[Data.first]+=Data.second*y;
	}
	
	return 0;
}
```



---

## 作者：tzc_wk (赞：2)

[题面传送门](https://codeforces.ml/contest/348/problem/C)

对于这类不好直接维护的数据结构，第一眼应该想到……

根号分治！

我们考虑记【大集合】为大小 $\geq\sqrt{n}$ 的集合，【小集合】为大小 $<\sqrt{n}$ 的集合。

显然，查询/修改小集合的时候，直接暴力跑一遍不会出问题，时间复杂度 $\mathcal O(n\sqrt{n})$。

关键在于怎样处理【大集合】：

- 修改大集合的时候，暴力一个一个元素修改显然不行，于是考虑整体打一个 $+v$ 的标记 $tag_x$
- 查询大集合的时候我们也不能遍历一遍集合求和，于是可以维护一个数组 $ans_x$ 表示大集合 $x$ 的答案，查询的时候直接输出 $ans_x$。

这样又有一个问题了，怎样将大集合的贡献累加入答案中。

注意到大集合有一个性质，那就是大集合的个数不会超过 $\sqrt{n}$。

故每一次集合整体加值的时候，**暴力修改每个大集合的 $ans_x$**；询问小集合的时候，**将每个大集合的 $tag_x$ 累加进答案中**。

至于怎样计算大集合的贡献，可以维护一个 $same_{i,j}$ 表示第 $i$ 个大集合与第 $j$ 个集合有多少个公共的元素。那么你对某个大集合 $x$ 做一次 $+v$ 的操作，它对另一个集合 $y$ 的贡献应为 $same_{x,y}\times v$。

总结下来，就是：

1. 修改小集合 $x$，暴力修改 $a_i$，并且对于所有大集合 $y$，令 $ans_y$ 假设 $same_{y,x}\times v$。
2. 修改大集合 $x$，令 $tag_x$ 加上 $v$，并且对于所有大集合 $y$，令 $ans_y$ 假设 $same_{y,x}\times v$。
3. 查询小集合 $x$，暴力遍历一遍集合求出 $a_i$ 的和，并枚举所有大集合 $y$，令答案加上 $same_{y,x}\times tag_y$。
4. 查询大集合 $x$，直接输出 $ans_x$ 就行了。

时空复杂度均为 $n\sqrt{n}$

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fz(i,a,b) for(int i=a;i<=b;i++)
#define fd(i,a,b) for(int i=a;i>=b;i--)
#define ffe(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
template<typename T1,typename T2> void chkmin(T1 &x,T2 y){if(x>y) x=y;}
template<typename T1,typename T2> void chkmax(T1 &x,T2 y){if(x<y) x=y;}
typedef pair<int,int> pii;
typedef long long ll;
template<typename T> void read(T &x){
	x=0;char c=getchar();T neg=1;
	while(!isdigit(c)){if(c=='-') neg=-1;c=getchar();}
	while(isdigit(c)) x=x*10+c-'0',c=getchar();
	x*=neg;
}
const int MAXN=1e5;
const int SQRT=316;
int n,m,qu;ll a[MAXN+5];
vector<int> s[MAXN+5];
int bg[SQRT+5],bgnum=0,same[MAXN+5][SQRT+5];
bitset<MAXN+5> vis[SQRT+5];
ll anss[MAXN+5],add[MAXN+5];
int main(){
	scanf("%d%d%d",&n,&m,&qu);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	for(int i=1;i<=m;i++){
		int len;scanf("%d",&len);
		for(int j=1;j<=len;j++){
			int x;scanf("%d",&x);s[i].pb(x);
			anss[i]+=a[x];
		}
		if(len>=SQRT){
			bg[++bgnum]=i;
			for(int j=0;j<s[i].size();j++){
				vis[bgnum][s[i][j]]=1;
			}
		}
	}
	for(int i=1;i<=m;i++)
		for(int j=0;j<s[i].size();j++)
			for(int k=1;k<=bgnum;k++)
				if(vis[k][s[i][j]]) same[i][k]++;
	while(qu--){
		static char opt[3];scanf("%s",opt+1);
		if(opt[1]=='?'){
			int x;scanf("%d",&x);
			ll ans=0;
			if(s[x].size()<SQRT){
				for(int j=0;j<s[x].size();j++) ans+=a[s[x][j]];
				for(int j=1;j<=bgnum;j++) ans+=1ll*add[bg[j]]*same[x][j];
				printf("%lld\n",ans);
			} else printf("%lld\n",anss[x]);
		} else {
			int x,y;scanf("%d%d",&x,&y);
			if(s[x].size()<SQRT){
				for(int j=0;j<s[x].size();j++) a[s[x][j]]+=y;
				for(int j=1;j<=bgnum;j++) anss[bg[j]]+=1ll*y*same[x][j];
			} else {
				for(int j=1;j<=bgnum;j++) anss[bg[j]]+=1ll*y*same[x][j];
				add[x]+=y;
			}
		}
	}
	return 0;
}
```



---

## 作者：EXODUS (赞：1)

# Part 1：前言

一道比较经典的根号分治题目，在处理大集合对小集合的贡献的时候想了 10min，所以来记一下。

# Part 2：正文

这种修改的格式是难以直接套数据结构维护的，因此考虑根号分治，将每个集合以 $B$ 为阈值按照大小分为大集合和小集合，令 $lim=\sum\limits_{i=1}^m \vert S_i\vert$，按照根号分治的思想，套路考虑修改时大集合和小集合应当如何处理。

对于小集合，其修改时可以直接修改对应位置的值，对于大集合，其修改时可以直接在集合上面打标记，现在的问题是如何统计询问的答案。对于小集合，每次暴力查询对应位置的数，现在的问题是大集合对其的贡献。显然不能枚举每个位置计算有哪些包含它的大集合，我们不妨转换角度，枚举每一个大集合，考虑其上标记对于小集合的贡献，那么应该是大集合和小集合的交集大小乘上标记，我们直接预处理出来每个大集合和小集合的交集即可。由于大集合的个数是 $O(\dfrac{lim}{B})$ 个，每次处理时枚举每一个大集合的每一个位置，将覆盖该位置的小集合的对应重合位置加一。而小集合的总元素个数不超过 $O(lim)$ 个，所以预处理部分的复杂度是 $O(\dfrac{lim}{B}(n+lim))$ 的，单次询问复杂度是 $O(\dfrac{lim}{B})$，单次修改小集合复杂度 $O(B+\frac{lim}{B})$，单次修改大集合复杂度 $O(1)$。

然后考虑大集合怎么做，首先处理出初始的答案，然后我们将其贡献分为两部分，分别为小集合的贡献和大集合的贡献。小集合可以在每次修改后枚举每个大集合和其交集大小，将其贡献到答案中去。大集合的贡献我们可以仿照大集合对小集合的贡献，同样处理出大集合之间的交集，然后根据其标记贡献即可，单次查询复杂度 $O(\frac{lim}{B})$。

整理一下，总时间复杂度 $O(\dfrac{lim}{B}(n+lim)+q(B+\dfrac{lim}{B}))$，视 $n,lim,q$ 同阶，取 $B=\sqrt{n}$ 即可得到复杂度 $O(n\sqrt{n})$。


# Part 3：代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i,l,r) for(int i(l);i<=(r);++i)
#define per(i,r,l) for(int i(r);i>=(l);--i)
#define eb emplace_back
#define Debug(...) fprintf(stderr,__VA_ARGS__)
template<typename T>
void read(T &x){
	x=0;T flg=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')flg=-1;ch=getchar();}
	while(isdigit(ch))x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	x*=flg;
}
template<typename T,typename... Args>
void read(T &x,Args &...args){read(x),read(args...);}


int main(){
	int n,m,q,cnt=0;
	read(n,m,q);
	vector<ll>a(n);
	vector<int>mrk(m);
	vector<ll>tag(m);
	vector<vector<int>>inc(n);
	vector<vector<int>>pos(m);
	vector<int>idx;
	vector<ll>ans(m);
	const int B=sqrt(n);
	for(auto &x:a)read(x);
	rep(i,0,m-1){
		int len;read(len);pos[i].resize(len);
		for(auto &x:pos[i])read(x),--x,ans[i]+=a[x];
		for(auto x:pos[i])inc[x].eb(i);
		if(len>B)mrk[i]=1,++cnt,idx.eb(i);
	}
	vector<vector<int>>coe(cnt,vector<int>(m));
	rep(i,0,cnt-1)for(auto p:pos[idx[i]])for(auto j:inc[p])coe[i][j]++;
	
	// for(auto p:idx)Debug("%d ",p);Debug("\n");
	
	while(q--){
		char opt;int sid;
		scanf("%c%d",&opt,&sid);--sid;
		// Debug("%c %d\n",opt,sid);
		if(opt=='?'){
			getchar();
			if(mrk[sid]){
				ll res=ans[sid];
				rep(j,0,cnt-1)res+=(ll)coe[j][sid]*tag[idx[j]];
				printf("%lld\n",res);
			}else{
				ll res=0;
				for(auto x:pos[sid])res+=a[x];
				rep(j,0,cnt-1)res+=(ll)coe[j][sid]*tag[idx[j]];
				printf("%lld\n",res);
			}
		}else{
			int v;scanf("%d",&v);
			getchar();
			if(mrk[sid])tag[sid]+=v;
			else{
				for(auto x:pos[sid])a[x]+=v;
				rep(j,0,cnt-1)ans[idx[j]]+=(ll)coe[j][sid]*v;
			}
		}
	}
	return 0;
}
```



---

## 作者：WeLikeStudying (赞：1)

- 此题为开摆计划 T6。

**[题目](https://www.luogu.com.cn/problem/CF348C)**
- 给一些集合，计算子集加，子集求和。

**分析**
- 一直觉得这个问题的出法不优美。咱们考虑这个问题更加本质的做法，然后延伸出一系列简单的问题，或许更能获益？
- 下面的问题在一个 $m$ 条边静态图上，范围加：将与一个点直接相邻的点加上某个定值，范围查询：查询与某个点直接相邻的点的权值和，一共 $q$ 次修改查询。
- 单点加，单点查询？按题意模拟即可 $O(m+q)$。
- 范围加，单点查询？按 $\sqrt m$ 分为大度点和小度点：小度点暴力更新，然后查询某个点时暴力看大度点有没有更新自己，复杂度 $O(m+q\sqrt m)$。
- 单点加，范围查询？按 $\sqrt m$ 分为大度点和小度点：每个点只保存周围小度点的权值和，查询的时候暴力查大度点，修改小度点的时候需要暴力更新周围的点 $O(m+q\sqrt m)$。
- 范围加，范围查询？我们拥有的方法：
- 暴力范围加；暴力范围查询；记录一些点直接连边的点集的交，然后就可以快速更新一些范围加对一些范围查询的贡献。
- 因此我们可以：
- 小度点修改：快速更新周围的小度点，然后对于周围的大度点的答案贡献可以直接先计算。
- 大度点修改：先咕掉，作为未完成的询问先躺在大度点里。
- 小度点查询：快速查询周围的小度点，而大度点躺在历史里的修改暴力计算贡献。
- 大度点查询：被小度点贡献的已经计算，而大度点躺在历史里的修改暴力计算贡献。
- 时间复杂度 $O((m+q)\sqrt m)$，空间复杂度 $O(m\sqrt m)$，[代码](https://www.luogu.com.cn/paste/pjw5grqb)。

---

## 作者：Shunpower (赞：0)

一眼根号分治，然后发现各种问题置换根本理不清楚。这也是我在想这道题的时候遭遇的最大的困难。

---------------

显然的想法：我们设置输入的集合总大小是 $\Sigma$，那么我们肯定按照 $B=\sqrt \Sigma$ 根号分治：大小大于等于 $B$ 的集合只有至多 $B$ 个。

为了方便，我们称呼大小小于 $B$ 的集合是**小集合**，大小大于等于 $B$ 的集合是**大集合**。

我们抛开代码难度不谈，我们总是可以把贡献划分成四块：

- 小集合修改，贡献给小集合。显然这可以暴力维护原序列 $\Delta_i$，两边都是 $\mathcal O(B)$ 的。
- 小集合修改，贡献给大集合。
- 大集合修改，贡献给小集合。
- 大集合修改，贡献给大集合。

不妨考虑最后一个怎么做，因为最后一个的操作指南比较固定（无论是修改还是询问都不能扫描集合）。为了保证单次复杂度 $\mathcal O(B)$，可以想到：如果我们能修改的时候 $\mathcal O(B)$ 地扫一遍大集合，并计算修改的集合对每个大集合的贡献就好了。

然后可以发现这是容易的，并且显然可以扩展到任意集合对大集合的贡献。只要我们能算出一张表 $c_{i,j}$，表示每个大集合 $i$ 和每个大集合 $j$ 的交即可。

算出 $c$ 是简单的。显然我们可以维护每个下标所在的大集合，由于所有集合总共只有 $\mathcal O(\Sigma)$ 个数，每个数产生的贡献是 $\mathcal O(B)$ 的，所以复杂度正确。

剩下只用考虑大集合修改，贡献给小集合怎么做。由于我们已经会小集合修改，贡献给大集合了，所以我们只需转置问题，反过来在询问处扫描大集合加入贡献即可。

----------

确实有点绕。但代码还挺好写。

```cpp
int n,m,q;
int B;
int t;
int org[N];
int id[N];
int big[N];
pair<int,vector<int>> a[N];
vector <int> in[N];
int cnt[N][320];
ll sum[N];
ll del[N],add[N];
int main(){
#ifdef Shun
	freopen(".in","r",stdin);
	freopen(".out","w",stdout);
#endif
	ios::sync_with_stdio(false);
	cin>>n>>m>>q;
	fr1(i,1,n) cin>>org[i];
	B=sqrt(100000);
	fr1(i,1,m){
		int k;
		cin>>k;
		a[i].se.resize(k);
		fr1(j,0,k-1) cin>>a[i].se[j],sum[i]+=org[a[i].se[j]];
		if(k>=B){
			t++;
			big[t]=i,id[i]=t;
			for(auto j:a[i].se) in[j].pb(t);
		}
	}
	fr1(i,1,m){
		for(auto j:a[i].se){
			for(auto k:in[j]) cnt[i][k]++; 
		}
	}
	while(q--){
		char c;
		int k,x;
		cin>>c>>k;
		if(c=='?'){
			if(a[k].se.size()>=B) cout<<sum[k]<<'\n';
			else{
				ll ans=sum[k];
				for(auto j:a[k].se) ans+=del[j];
				fr1(j,1,t) ans+=1ll*cnt[k][j]*add[j];
				cout<<ans<<'\n';
			}
		}
		else{
			cin>>x;
			if(a[k].se.size()>=B) add[id[k]]+=x;
			else for(auto j:a[k].se) del[j]+=x;
			fr1(j,1,t) sum[big[j]]+=1ll*cnt[k][j]*x;
		}
	}
	ET;
}
//ALL FOR Zhang Junhao.
```

---

## 作者：liujiaxi123456 (赞：0)

## 关键词：根号分治，详细具体实现。
### 思路：
**集合总大小保证**，考虑根号分治。

把集合按照大小分治，小的暴力，大的标记。
- 改小的：
	+ 修改 a 数组。
   + 枚举每个大的，修改大的的答案。
- 改大的：
	+ 打标记。
   + 枚举每个大的，修改大的的答案。
- 查小的：
	+ 收集 a 数组信息。
   + 枚举每个大的，收集大的的标记的影响。
- 查大的：
	+ 直接输出答案。
### 实现：
- 预处理：
  + 大的的初始答案。
  + 每个集合（无论大小）与每个大集合的交集大小。
    - 元素总大小保证，大集合数量保证。
    - 时间复杂度为 $O(N\sqrt N)$。
- 修改/收集集合间的影响：
  + 通过交集大小乘标记得到。
### 时空复杂度：
- 时间：$O(N\sqrt{N})$。
  + 小集合暴力 $O(\sqrt N)$，大集合数量 $O(\sqrt N)$。
- 空间：$O(N\sqrt{N})$。
  + 同理。
### Code:
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int Maxn = 1e5+5, limit = 320, Sqrt = 505;

namespace Josh_zmf {
	
	int MemoryPool[Maxn*2], *_NowPointer_ = MemoryPool; // 注意 size+1 存贮，需要开两倍
	int N, M, Q, size[Maxn], id[Maxn], tot, *s[Maxn], both[Sqrt][Maxn];
	ll a[Maxn], sum[Maxn], add[Maxn]; bool chk[Maxn];

	inline int main() {
		cin>> N>> M>> Q;
		for(int i=1; i<=N; i++)	cin>> a[i]; // a 数组
		for(int i=1; i<=M; i++) {
			cin>> size[i], s[i] = _NowPointer_, _NowPointer_ += size[i]+1; // 指针数组，不用管，当二维数组理解就行了
			if(size[i] >= limit)	id[++tot] = i; // 大集合
			for(int j=1; j<=size[i]; j++)	cin>> s[i][j], sum[i] += a[s[i][j]]; // 大集合答案
		}
		for(int i=1; i<=tot; i++) { // 枚举每个大集合
			for(int k=1; k<=size[id[i]]; k++)	chk[s[id[i]][k]] = 1; // 方便后面检验
			for(int j=1; j<=M; j++) { // 枚举每个集合（无论大小）
				for(int k=1; k<=size[j]; k++)	both[i][j] += chk[s[j][k]]; // 维护集合并集大小
			}
			for(int k=1; k<=size[id[i]]; k++)	chk[s[id[i]][k]] = 0; // 清空
		}
		ll res; char opt;
		for(int k, x; Q--; ) {
			cin>> opt>> k;
			switch(opt) {
				case '?':
					if(size[k] >= limit) {
						cout<< sum[k]<< '\n'; // 大集合答案
					} else {
						res = 0;
						for(int i=1; i<=size[k]; i++)	res += a[s[k][i]]; // 收集 a 数组
						for(int i=1; i<=tot; i++)	res += 1ll*both[i][k]*add[id[i]]; // 收集大集合答案
						cout<< res<< '\n';
					}
					break;
				default:
					cin>> x;
					if(size[k] >= limit) {
						add[k] += x; // 打标记
						for(int i=1; i<=tot; i++)	sum[id[i]] += 1ll*both[i][k]*x; // 修改所有大集合（包括自己）
					} else {
						for(int i=1; i<=size[k]; i++)	a[s[k][i]] += x; // 修改 a 数组
						for(int i=1; i<=tot; i++)	sum[id[i]] += 1ll*both[i][k]*x; // 修改所有大集合
					}
			}
		}
		return 0;
	}

}

int main() {
	Josh_zmf::main();
	return 0;
}
```
### 结语：
点个赞再走吧。: )

---

## 作者：small_john (赞：0)

## 思路

注意到集合长度之和小于等于 $10^5$，设这个值为 $M$。考虑根号分治。

设一个阈值 $B=\sqrt M$，大小大于 $B$ 的为大集合，否则就是小集合。

很明显，大集合最多有 $B$ 个。

对于大集合，考虑预处理出大集合的答案，更改的时候直接加上懒标记。统计的时候直接算预处理出的答案加上懒标记。

小集合加上一个数，可以直接遍历集合内的元素，暴力修改。而询问小集合时也一样，直接遍历集合内的元素，统计答案。时间复杂度 $O(\sqrt n)$

但是按照上述的做法会有一个漏洞，就是集合之间会互相影响。

而修改小集合会对大集合产生影响，遍历每个大集合，他们的答案会加上两个集合的交乘上修改量。修改大集合回对所有集合产生影响，所以在统计答案的时候去遍历每个大集合，返回值加上两个集合的交乘上大集合的懒标记。

因此，我们预处理大集合和每个集合的交，这个可以 $O(MB)=O(M\sqrt M)$ 做到。

总时间复杂度是根号的，可以通过本题。

## 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e5+5,B = 350;
int n,m,q,id[N],cnt,w[B][N];
ll sum[B],tag[B],a[N];
vector<int> v[N];
bitset<N> s[B];
inline void add(int x,ll y)
{
	if(!id[x])
	{
		for(auto i:v[x])
			a[i]+=y;
		for(int i = 1;i<=cnt;i++) sum[i]+=y*w[i][x];
	}
	else tag[id[x]]+=y;
}
inline ll ask(int x)
{
	if(!id[x])
	{
		ll res = 0;
		for(auto i:v[x]) res+=a[i];
		for(int i = 1;i<=cnt;i++)
			res+=tag[i]*w[i][x];
		return res;
	}
	else
	{
		ll res = sum[id[x]];
		for(int i = 1;i<=cnt;i++)
			res+=tag[i]*w[i][x];
		return res;
	}
}
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m>>q;
	for(int i = 1;i<=n;i++)
		cin>>a[i];
	for(int i = 1,l;i<=m;i++)
	{
		cin>>l;
		for(int j = 1,x;j<=l;j++)
			cin>>x,v[i].push_back(x); 
		if(l>=B)
		{
			id[i] = ++cnt;
			for(auto j:v[i]) s[cnt][j] = 1,sum[cnt]+=a[j];
		}
	}
	for(int i = 1;i<=cnt;i++)
		for(int j = 1;j<=m;j++)
			for(auto k:v[j])
				w[i][j]+=s[i][k];
	while(q--)
	{
		string op;int x,y;
		cin>>op>>x;
		if(op[0]=='+') cin>>y,add(x,y);
		else cout<<ask(x)<<'\n';
	}
	return 0;
}
```

---

## 作者：npqenqpve (赞：0)

根分好题，考虑按集合大小根分，称大小小于 $\sqrt n$ 的为小集合，否则为大集合；

当查询集合 $S$ 是小集合时，小集合给到的贡献是可以直接统计的，在小集合修改时暴力修改，查询时暴力统计；大集合打标记记录修改的量，给到的贡献就是 $S$ 和任意大集合 $T$ 的交集大小乘以 $tag_T$，在修改大集合时直接更新标记；

大集合给大集合的贡献和上面第二类贡献的统计方式一样；

只需要解决小集合给大集合的贡献，这个好搞，修改小集合时枚举所有大集合，对大集合 $T$ 的贡献就是交集大小乘以改变量。

---

## 作者：intel_core (赞：0)

首先看到集合数量虽然多，但是集合里的数最多只有 $10^5$ 个，这启示我们可以根号分治，将大小 $< \sqrt{n}$ 和大小 $\ge \sqrt{n}$ 的集合分开处理。

（以下称大小 $<\sqrt{n}$ 的集合为小集合，反之则为大集合。

由于大集合最多只有 $\sqrt{n}$ 个，我们的重点自然是怎么快速更新大集合中的信息。

先处理每个集合和每个大集合交集的大小，这步可以 $O(n\sqrt{n})$ 预处理；在给一个小集合中的数加上 $x$ 的时候，就可以 $O(1)$ 计算每个大集合答案的增量。

因为小集合中的数比较少，我们可以在询问的时候直接枚举每个数算和；当修改大集合中的数时，显然我们直接不能直接修改，这时候我们使用懒标记，询问的时候枚举大集合上的 $\text{tag}$ 看对答案的贡献。

具体来说：

* 修改小集合中的数，枚举大集合，计算答案增量；在原数组中把对应的数 $+x$。

* 修改大集合中的数，直接打懒标记。

* 询问小集合，先枚举对应的数算和，再枚举大集合把对应的贡献加进答案。

* 询问大集合，直接输出存好的答案即可。

总复杂度 $O(n \sqrt{n})$。

---

