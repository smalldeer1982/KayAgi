# Double Profiles

## 题目描述

You have been offered a job in a company developing a large social network. Your first task is connected with searching profiles that most probably belong to the same user.

The social network contains $ n $ registered profiles, numbered from $ 1 $ to $ n $ . Some pairs there are friends (the "friendship" relationship is mutual, that is, if $ i $ is friends with $ j $ , then $ j $ is also friends with $ i $ ). Let's say that profiles $ i $ and $ j $ ( $ i≠j $ ) are doubles, if for any profile $ k $ ( $ k≠i $ , $ k≠j $ ) one of the two statements is true: either $ k $ is friends with $ i $ and $ j $ , or $ k $ isn't friends with either of them. Also, $ i $ and $ j $ can be friends or not be friends.

Your task is to count the number of different unordered pairs ( $ i,j $ ), such that the profiles $ i $ and $ j $ are doubles. Note that the pairs are unordered, that is, pairs ( $ a,b $ ) and ( $ b,a $ ) are considered identical.

## 说明/提示

In the first and second sample any two profiles are doubles.

In the third sample the doubles are pairs of profiles $ (1,3) $ and $ (2,4) $ .

## 样例 #1

### 输入

```
3 3
1 2
2 3
1 3
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3 0
```

### 输出

```
3
```

## 样例 #3

### 输入

```
4 1
1 3
```

### 输出

```
2
```

# 题解

## 作者：IkunTeddy (赞：3)

# 题目分析
首先我们先理解题目，题目就是让我们求出边集相同（包含相邻）的点对。如果直接暴力对比两个点的出边集，那时间复杂度就是 $O(nm)$ 直接爆掉了。那怎么快速对比两个集合是否相同呢？

我们就可以用**类似于字符串 hash 的思路来进行集合 hash**。想到这这个题就直接秒了。接下来就像字符串 hash 一样给每个点赋一个值，就能够判断了！

但是需要注意一个点，有相邻边的两个点需要特判是否拥有相同集合。
# Code
```cpp
#include <bits/stdc++.h>
#define ull unsigned long long //我是使用自然溢出的hash方法
using namespace std;
const int maxn=1e6+10;
ull val[maxn],base=2906344301,s[maxn];
int u[maxn],v[maxn];
ull ans=0;
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	val[0]=1;
	for(int i=1;i<=n;i++)val[i]=val[i-1]*base;
	for(int i=1;i<=m;i++){
		scanf("%d%d",&u[i],&v[i]);
		s[u[i]]^=val[v[i]]; //通过判断异或和是否相等来判断是否拥有相同集合
		s[v[i]]^=val[u[i]];
	}
	for(int i=1;i<=m;i++){
		if((s[u[i]]^val[u[i]])==(s[v[i]]^val[v[i]]))ans++;
	}
	sort(s+1,s+1+n);
	ull cnt=0;
	for(int i=1;i<=n;i++){
		if(s[i]==s[i-1])cnt++;
		else{
			ans+=(ull)cnt*(cnt-1)/2;
			cnt=1;
		}
	}
	ans+=(ull)cnt*(cnt-1)/2;
	cout<<ans<<endl;

	return 0;
}


```

---

## 作者：XL4453 (赞：2)

### $\text{Difficulty : 2300}$
---
### 解题思路：

每一个点都是独特的，直接用哈希即可。点的数量很多，但是边相对比较稀疏，可以从边入手完成对于每一个点哈希值的计算。

我采用的是以质数 $1009$ 来计算值，然后用 $\text{unsigned long long}$ 的自然溢出来完成哈希。好像没有被卡。

注意当两点之间有边直接相连的时候这两个点不计入运算，可以通过加入该点本身来消除影响。

---
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
#define int long long
const int MAXN=2000005;
unsigned long long num[MAXN],p[MAXN],P=1009;
int n,m,x[MAXN],y[MAXN],ans,cnt;
signed main(){
	scanf("%I64d%I64d",&n,&m);
	p[0]=1;
	for(int i=1;i<=n;i++)p[i]=p[i-1]*P;
	for(int i=1;i<=m;i++){
		scanf("%I64d%I64d",&x[i],&y[i]);
		num[x[i]]+=p[y[i]];
		num[y[i]]+=p[x[i]];
	}
	for(int i=1;i<=m;i++)
	if(num[x[i]]+p[x[i]]==num[y[i]]+p[y[i]])
	ans++;
	sort(num+1,num+n+1);
	for(int i=1;i<=n;i++){
		if(num[i]==num[i-1]){
			cnt++;
		}
		else{
			ans+=cnt*(cnt-1)/2;
			cnt=1;
		}
	}
	ans+=cnt*(cnt-1)/2;
	printf("%I64d",ans);
	return 0;
}
```


---

## 作者：2020luke (赞：1)

# [CF154C Double Profiles](https://www.luogu.com.cn/problem/CF154C) 题解

## 思路解析

题目说的很明白，求有多少个无序点对 $(i,j)$，使得与 $i$ 直接相连的点集与直接与 $j$ 相连的点集完全相等。我们想到如果直接判断每个 $i,j$ 肯定会超时，所以我们想把每一个与任意一点直接相连的点集进行压缩，可以想到使用字符串哈希的想法压缩一个点集。如果两点的点集哈希后相等，说明两点的点集也相等。

注意，需要特判点度为 $0$ 的情况，以及需要分别讨论 $i,j$ 之间有连边和没连边的情况，最后注意这题卡 `map`。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
const ull p = 13;
const int N = 1e6 + 10;
int n, m, sz[N];
ull hs[N], pw[N];
signed main() {
	cin >> n >> m;
	pw[0] = 1; for(int i = 1; i <= n; i++) pw[i] = pw[i - 1] * p;	//预处理
	for(int i = 1, u, v; i <= m; i++) {
		cin >> u >> v;
		sz[u]++; sz[v]++;
		hs[u] += pw[v];	//字符串哈希
		hs[v] += pw[u];
	}
	vector<ull> v, v1;
	long long ans = 0;
	for(int i = 1; i <= n; i++) {
		if(sz[i] > 0) v.push_back(hs[i]);	//记得特判入度为 0
		else v.push_back(0);
		v1.push_back(hs[i] + pw[i]);
	}
	sort(v.begin(), v.end()); sort(v1.begin(), v1.end());
	for(int i = 0, j = i; i < v.size(); i = j) {
		j = i; while(j < v.size() && v[j] == v[i]) j++;
		ans += (long long)(j - i) * (long long)(j - i - 1) / 2;
	}
	for(int i = 0, j = i; i < v1.size(); i = j) {
		j = i; while(j < v1.size() && v1[j] == v1[i]) j++;
		ans += (long long)(j - i) * (long long)(j - i - 1) / 2;
	}
	cout << ans;
	return 0;
}
```

---

## 作者：Graphcity (赞：1)

集合 hash 模板题。

两个不相邻的点 $(A,B)$ 相同当且仅当它们的出点集合相同。如果相邻，那么出点集合还要加上自己。

但是，维护出点集合需要的信息太多了，考虑用一个简单的方式来比对。

考虑给每个点随机赋一个 $[0,2^{64})$ 的权值。那么，一个点的出点集合可以用出点权值的异或和来替代。那么，比较两个点的异或和是否相同就可以了。

这种方法的单哈希被卡了，建议使用双哈希。时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
typedef pair<ull,ull> Pair;
const int Maxn=1e6;

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

int n,m,ind[Maxn+5]; ll ans;
ull val[Maxn+5],num[Maxn+5];
ull val2[Maxn+5],num2[Maxn+5];
ull seed=1145140998244353661ull;
ull seed2=190331214748364703ull;
vector<int> v[Maxn+5];

map<Pair,int> mp;
inline ull Rand() {return seed=(seed<<7)^(seed<<11)^(seed>>19);}
inline ull Rand2() {return seed2=(seed2<<7)^(seed2<<11)^(seed2>>13);}

int main()
{
    n=read(),m=read();
    For(i,1,n) val[i]=Rand(),val2[i]=Rand2();
    For(i,1,m)
    {
        int a=read(),b=read();
        num[a]^=val[b],num[b]^=val[a];
        num2[a]^=val2[b],num2[b]^=val2[a];
        ind[a]++,ind[b]++;
    }
    For(i,1,n) v[ind[i]].push_back(i);
    For(i,0,n) if(v[i].size()>1)
    {
        for(auto j:v[i])
        {
            Pair pr=make_pair(num[j],num2[j]);
            ans+=mp[pr],mp[pr]++;
        }
        mp.clear();
        for(auto j:v[i])
        {
            Pair pr=make_pair(num[j]^val[j],num2[j]^val2[j]);
            ans+=mp[pr],mp[pr]++;
        }
        mp.clear();
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：huangwux (赞：1)

给一张无向图,问有多少点对(A,B)的边完全相同. N,M ≤ 100000

A,B出边相同，当且仅当A连接的每一条边的另一个端点也和B直接相连 B连接的每一条边的另一个端点也和A相连

若A,B直接相连，不妨碍以上性质




# Hash



总感觉这道题如果有了翻译之后最多是道蓝题

读懂题后就很好做了

首先给每个点一个Hash值

然后读入每一条边，对每个点加上另一个端点的Hash值

然后先遍历每两个相连的点（即遍历每一条边） 这时候需要给两个点的Hash分别加上本身的Hash值（否则会认为他们的边不一样）

之后遍历不相邻的两个点

当且仅当他们的Hash值相同，这两个点的边相同

```cpp
#include <iostream>
#include <algorithm>
using namespace std;
const int maxn=100000007;

int ha[maxn];
int p=1313;
int e[maxn][2];
void init()              //hash每个点
{
    ha[0]=1;
    for(int i=1;i<maxn;i++)
        ha[i]=ha[i-1]*p;
}
long long a[maxn];
int main()
{
    std::ios::sync_with_stdio(false);
    int n,m;
    cin>>n>>m;
    init();
    for(int i=1;i<=m;i++)
    {
        int u,v;
        cin>>u>>v;
        a[u]+=ha[v];                 
        a[v]+=ha[u];
        e[i][0]=u;
        e[i][1]=v;
    }
    long long ans=0;
    for(int i=1;i<=m;i++)             
    {
        int u=e[i][0],v=e[i][1];
        long long hu=a[u]+ha[u],hv=a[v]+ha[v];
        if(hu==hv) ans++;
    }
    sort(a+1,a+n+1);
    int i=2;
    int cnt=1;
    while(i<=n)                     
    {
        if(a[i]==a[i-1])
        {
            cnt++;
        }
        else
        {
            ans+=(cnt*(cnt-1))/2;         
            cnt=1;
        }
        i++;
    }
    ans+=(cnt*(cnt-1))/2;
    cout<<ans<<endl;
    return 0;
}

```



---

## 作者：RuntimeErr (赞：0)

询问两个集合是否相等，有经典的哈希的 trick。

考虑给每个点随机一个 $[0,2^{64})$ 的权值，然后对于每个点再维护一个其出点的权值和，用 map 维护答案即可。不过对于相邻两个点要单独判断，通过加上自身来满足性质。

```cpp
//这里用的是 xor 哈希的写法
#include<bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
const int N=1e6+10;

mt19937_64 rnd(time(NULL));

int n,m;long long ans=0;
int u[N],v[N];
ull val[N],out[N];
map<ull,int> mp;

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)out[i]=0,val[i]=rnd();
	for(int i=1;i<=m;++i){
		scanf("%d%d",&u[i],&v[i]);
		out[u[i]]^=val[v[i]],out[v[i]]^=val[u[i]];
	}
	for(int i=1;i<=m;++i)if((out[u[i]]^val[u[i]])==(out[v[i]]^val[v[i]]))++ans;
	for(int i=1;i<=n;++i){
		ans+=mp[out[i]];
		++mp[out[i]];
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：BlankAo (赞：0)

因为一对点 $(A,B)$ 合法，当且仅当与 $A$ 连边的点的集合和与 $B$ 连边的点的集合相等。

所以对于每个点，把这个点放进 **和它连边的点的集合** 中，最后将集合相等的点放在一组，对于每一组，如果有 $siz$ 个点，它的贡献就是 $\Large\binom{siz}{2}$。

但是有 $n=10^6$ 个点，开 $10^6$ 个集合显然是不现实的。我们用哈希去做即可。我给每个点随机了一个数值 $num_i$，并维护两个值 $a_i,b_i$，代表与 $i$ 号点相连的点的 $num$ 的平方和、异或和。

遍历每个点，给和它连边的点更新 $a_i,b_i$ 即可。

但是会被卡，所以我的实际代码中是随机了两个数值 $num_i$，$a_i,b_i$ 也各维护了两个。

```c++
#include<bits/stdc++.h>
#define rep(i,x,y) for(int i=x;i<=y;++i)
#define mar(o) for(int E=fst[o];E;E=e[E].nxt)
#define v e[E].to
#define lon long long
using namespace std;
const int n7=1012345,m7=n7*2;
struct dino{int to,nxt;}e[m7],e0[m7];
struct kite{lon a,b;}val1[n7],val2[n7];
struct pond{lon a,b,c,d;}val[n7];
int n,m,dcnt,ecnt,fst[n7];lon ans,num1[n7],num2[n7];

int rd(){
	int shu=0;bool fu=0;char ch=getchar();
	while( !isdigit(ch) ){if(ch=='-')fu=1;ch=getchar();}
	while( isdigit(ch) )shu=(shu<<1)+(shu<<3)+ch-'0',ch=getchar();
	return fu?-shu:shu;
}

void edge(int p,int q){
	ecnt++;
	e[ecnt]=(dino){q,fst[p]};
	fst[p]=ecnt;
}

bool cmp(pond p,pond q){
	if(p.a!=q.a)return p.a<q.a;
	if(p.b!=q.b)return p.b<q.b;
	if(p.c!=q.c)return p.c<q.c;
	return p.d<q.d;
}

int main(){
	n=dcnt=rd(),m=rd();
	rep(i,1,m){
		int p=rd(),q=rd();
		e0[i]=(dino){p,q};
		edge(p,q),edge(q,p);
	}
	srand(time(0));
	rep(i,1,n)num1[i]=1ll*rand()*rand()*i,num2[i]=1ll*rand()*rand()*(n-i+1);
	rep(o,1,n){
		mar(o){
			val1[v].a=val1[v].a+num1[o]*num1[o];
			val1[v].b=val1[v].b^num1[o];
			val2[v].a=val2[v].a+num2[o]*num2[o];
			val2[v].b=val2[v].b^num2[o];
		}
	}
	rep(i,1,m){
		int p=e0[i].to,q=e0[i].nxt;
		if(val1[p].a+num1[p]*num1[p]==val1[q].a+num1[q]*num1[q]&&val1[p].b^num1[p]==val1[q].b^num1[q]){
			if(val2[p].a+num2[p]*num2[p]==val2[q].a+num2[q]*num2[q]&&val2[p].b^num2[p]==val2[q].b^num2[q])ans++;
		}
	}
	rep(i,1,n)val[i]=(pond){val1[i].a,val1[i].b,val2[i].a,val2[i].b};
	sort(val+1,val+n+1,cmp);
	int l=1,r=1;
	rep(i,2,n){
		if(val[i].a==val[i-1].a&&val[i].b==val[i-1].b&&val[i].c==val[i-1].c&&val[i].d==val[i-1].d)r++;
		else ans=ans+1ll*(r-l+1)*(r-l)/2,l=r=i;
	}
	ans=ans+1ll*(r-l+1)*(r-l)/2;
	printf("%lld",ans);
	return 0;
}
```

---

