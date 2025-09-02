# Edgy Trees

## 题目描述

You are given a tree (a connected undirected graph without cycles) of $ n $ vertices. Each of the $ n - 1 $ edges of the tree is colored in either black or red.

You are also given an integer $ k $ . Consider sequences of $ k $ vertices. Let's call a sequence $ [a_1, a_2, \ldots, a_k] $ good if it satisfies the following criterion:

- We will walk a path (possibly visiting same edge/vertex multiple times) on the tree, starting from $ a_1 $ and ending at $ a_k $ .
- Start at $ a_1 $ , then go to $ a_2 $ using the shortest path between $ a_1 $ and $ a_2 $ , then go to $ a_3 $ in a similar way, and so on, until you travel the shortest path between $ a_{k-1} $ and $ a_k $ .
- If you walked over at least one black edge during this process, then the sequence is good.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1139C/fceedad9154dba8252692b9078d5d0099b72c637.png)Consider the tree on the picture. If $ k=3 $ then the following sequences are good: $ [1, 4, 7] $ , $ [5, 5, 3] $ and $ [2, 3, 7] $ . The following sequences are not good: $ [1, 4, 6] $ , $ [5, 5, 5] $ , $ [3, 7, 3] $ .

There are $ n^k $ sequences of vertices, count how many of them are good. Since this number can be quite large, print it modulo $ 10^9+7 $ .

## 说明/提示

In the first example, all sequences ( $ 4^4 $ ) of length $ 4 $ except the following are good:

- $ [1, 1, 1, 1] $
- $ [2, 2, 2, 2] $
- $ [3, 3, 3, 3] $
- $ [4, 4, 4, 4] $

In the second example, all edges are red, hence there aren't any good sequences.

## 样例 #1

### 输入

```
4 4
1 2 1
2 3 1
3 4 1
```

### 输出

```
252```

## 样例 #2

### 输入

```
4 6
1 2 0
1 3 0
1 4 0
```

### 输出

```
0```

## 样例 #3

### 输入

```
3 5
1 2 1
2 3 0
```

### 输出

```
210```

# 题解

## 作者：CXY07 (赞：10)

## 题目链接: [CF1139C Edgy Trees](https://www.luogu.org/problemnew/show/CF1139C)

# ~~第一次CF修仙就遇到了这样的神题~~

行吧 ~~其实也不是很难~~

![pic1](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1139C/fceedad9154dba8252692b9078d5d0099b72c637.png)

题意大概就是让你找出一棵有$n$个点的边带色的树上，**依次**经过 $k$ 个点，并且该路径是一条好的路径的这 $k$ 个点分别有多少组，好的路径当且仅当这条路径**至少经过一条黑边**($ps$：可以重复经过同一个点 ~~甚至可以呆着不动~~)

注意，同一路径上的点不一定直接相连，但一定要联通！

~~语文不好 题意讲错了别怪我 还是去看题比较靠谱~~

这就是树的好处了，两个点之间有且只有一条简单路径

讲一下我比赛时候的思路吧（以下均用好路、坏路表示好的路径和不好的路径，“长度为 $k$ 的路径”表示经过 $k$ 个点的路径）


------------


首先，先看懂题目 ~~百度翻译~~，看到 $n <= 10^5$，瞬间慌张 ~~主要是发现不能暴力乱搞~~

然后，可以发现要保证每条路径上至少有一条黑边，很难用一些效率高的算法维护 ~~可能是我太菜了不会做~~

所以考虑反方向思考，找出所有的坏路，拿路径总数去减去坏路个数，就可以得到好路的个数了

**建议往下看之前，先把几个样例想明白**

------------

首先，很快就可以得到：路径总数 $= n^k$，因为可以随便枚举 $k$ 个点

然后就是怎么求坏路个数了

![pic1](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1139C/fceedad9154dba8252692b9078d5d0099b72c637.png)

这是原图

怎么样才能求出坏路呢？也就是如何才能使得路径上的点的整个过程中没有黑边

# ~~那就把黑边删掉~~

其实思路是对的

当我们把上面的图中所有的黑边全部去掉，会变成这个样子

![pic2](https://cdn.luogu.com.cn/upload/pic/56565.png )

不难发现这棵树变成了几个联通块，并且块内不存在黑边和环

那么，很快就能够发现设一个联通块内的点数为 $x$ 的时候，长度为 $k$ 的路径一共 $x^k$ 个，并且这些路径，全部都是坏路！（因为整个联通块中间没有黑边，所以在联通块中无论如何选择，路径上都不可能有黑边 ~~太显然了~~）

所以，我们的思路就确定啦，分别求出所有路径个数和每个红边联通块中的路径个数，相减即可

那么，怎么维护红联通块内点的个数呢

### 显然是 ~~冰茶几~~ 并查集

最后再乱搞，加一个快速幂

复杂度不会算，应该还是比较快的 ~~我太弱了~~

## Code ：
```cpp
//Code By CXY
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 10;
const int mod = 1e9 + 7;

#define ll long long//记得开long long！！

ll n,k,ans;
ll cnt[MAXN];
ll f[MAXN];

ll find(ll x) {
	if(x == f[x]) return x;
	return f[x] = find(f[x]);
} //简单并查集，没啥解释的

void unity(int x,int y) {
	if(find(x) != find(y))
		f[find(x)] = find(y);
} //并查集合并操作

ll qpow(ll a,ll b) {
    ll res = 1,base = a;
    while(b) {
        if(b & 1) (res *= base) %= mod;
        (base *= base) %= mod;
        b >>= 1;
    }
    return res;
} // 快速幂

int main () {
	cin >> n >> k;
	for(int i = 1;i <= n; ++i)
		f[i] = i; //并查集初始化
	for(int i = 1,x,y,col;i < n; ++i) {
		cin >> x >> y >> col;
		if(col == 0) unity(x,y);//如果是红边，就合并，就可以得到红联通块 
	}
	for(int i = 1;i <= n; ++i)
		cnt[find(i)]++; //每一个并查集中间祖先的cnt中记录整个联通块中点的个数
	for(int i = 1;i <= n; ++i)
		if(f[i] == i) (ans += qpow(cnt[i],k)) %= mod;//如果这是一个新的联通块，就加上cnt[i]^k
	cout << (qpow(n,k) + mod - ans) % mod << endl; //最后用总数减去所有联通块内路径的和，记得取模！！还有注意负数的情况
	return 0; //华丽地结束
}
```

初二的$OIer$，请多关照

---

## 作者：xht (赞：4)

题目地址：[CF1139C Edgy Trees](https://www.luogu.org/problemnew/show/CF1139C)

~~红黑树~~

$ans$ 应该等于总数（$n^k$）减去不含黑色边的序列数量

不含黑色边就意味着一个序列只能在一个红色联通块中

一个红色联通块中的序列数量应该是点数的 $k$ 次方

求联通块用dfs用并查集都可以

然后快速幂一下再一减就是 $ans$

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e5 + 6, P = 1e9 + 7;
int n, k, v[N], cnt;
vector<int> e[N];

inline int ksm(int a, int b) {
    int c = 1;
    while (b) {
        if (b & 1) c = (ll)c * a % P;
        a = (ll)a * a % P;
        b >>= 1;
    }
    return c;
}

void dfs(int x) {
    v[x] = 1;
    ++cnt;
    for (unsigned int i = 0; i < e[x].size(); i++) {
        int y = e[x][i];
        if (v[y]) continue;
        dfs(y);
    }
}

int main() {
    cin >> n >> k;
    for (int i = 1; i < n; i++) {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        if (z) continue;
        e[x].push_back(y);
        e[y].push_back(x);
    }
    int ans = ksm(n, k);
    for (int i = 1; i <= n; i++)
        if (!v[i]) {
            cnt = 0;
            dfs(i);
            ans = (ans - ksm(cnt, k) + P) % P;
        }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：Silence_water (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF1139C)

$update:$ 将 $size[i]^k$ 误打成 $size[i]\times k$，麻烦管理员重新审核，谢谢！

---

$Analyse$

题目中要求求出至少包含 $1$ 条黑边的路径总数。如果直接暴搜枚举每条路径，一共 $n^k$ 条，必定超时。

正难则反。至少包含 $1$ 条黑边的路径的反面就是不包含黑边的路径，即只包含红边的路径。

由于树上两点之间仅有一条简单路径，考虑删去所有黑边。那么就剩下了一些只包含红边的树。若不同树的两颗节点要有路径连接，那么必然经过一条黑边。所以我们只需要将每棵树的路径总数求出即可，第 $i$ 颗树的路径总和即为 $size[i]^k$。

----

$Code$

总体来说代码难度并不大，注意开 `long long` 就好。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod=1e9+7;
const int M=2e5+5;
int n,k,cnt,sum[M];
vector<int> e[M];
bool mark[M];
ll ans=1;
void dfs(int u)
{
	mark[u]=true;
	sum[cnt]++;
	for(int i=0;i<e[u].size();i++)
		if(!mark[e[u][i]])dfs(e[u][i]);
}
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<n;i++)
	{
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		if(w==1)continue;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	for(int i=1;i<=n;i++)
		if(!mark[i])cnt++,dfs(i);
	for(int i=1;i<=k;i++)
		ans=(ans*n)%mod;
	for(int i=1;i<=cnt;i++)
	{
		ll tmp=1;
		for(int j=1;j<=k;j++)
			tmp=(tmp*sum[i])%mod;
		ans=(ans-tmp+mod)%mod;
	}
	printf("%lld",ans);
    return 0;
}
```

---

$The~end$

客官看完别忘了点个赞哦~

---

## 作者：TernaryTree (赞：1)

把所有黑边删掉，设 $t_i$ 表示每个连通块的大小，答案就呼之欲出了：

$$\textrm{ans}=n^k-\sum t_i^k$$

直接并查集 + 快速幂即可。复杂度 $\Theta(n(\alpha(n)+\log k))$。


---

## 作者：SuperCowHorse (赞：1)

### 题目大意
树上有 $n$ 个节点，每个节点是红或黑。定义一个标准序列是长度为 $k$ 的至少有一个红点的树上序列。求标准序列总数。
### 题目分析
~~顾名思义这是一道红黑树模板题。~~

其实这也就是一道水题。

先考虑暴力。

题目要求计算标准序列，$k$ 的值大了搜索次数也会大。看看范围，$k\leq100$，暴力时间复杂度 $O(2^n)$，看来暴力不可能。

那么我们就反其道而行。

题目要求求出标准序列，我们拿路径总数减去不标准序列（全黑序列）不就好了吗？

读入一个节点，红的就不作处理，计算每个联通块中的不标准序列组合个数。也就一个排列组合。刚才说了 $k\leq100$，暴力 $O(n)$ 计算组合数，也不会超。~~用不着什么 Lucas 定理。~~

每次 dfs 查询联通块节点个数 $co$，根据组合数的基本知识，计算 $C_{co}^k$ 就好了。

还有：别忘了模 $10^9+7$。
``` cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1e5+5;
const int mod=1e9+7;
int n,k,size;
int head[maxn],cnt,tot,co[maxn],ans=1;
bool vis[maxn];
struct node{
	int u,v,next;
}e[2*maxn];
void dfs(int x){//求联通块节点个数
	++co[tot];
	vis[x]=1;
	for(int i=head[x];i;i=e[i].next)
		if(!vis[e[i].v])
			dfs(e[i].v);
}
void add(int u,int v){//链式前向星存图
	++cnt;
	e[cnt].u=u;
	e[cnt].v=v;
	e[cnt].next=head[u];
	head[u]=cnt;
}
signed main(){
	scanf("%lld%lld",&n,&k);
	for(int i=1,u,v,w;i<n;++i){
		scanf("%lld%lld%lld",&u,&v,&w);
		if(w==0) add(u,v),add(v,u);
	}
	for(int i=1;i<=k;i++)//计算路径总数
		ans=(ans*n)%mod;
	for(int i=1;i<=n;++i){
		if(!vis[i]){
			++tot;
			dfs(i);
		}
	}
	for(int i=1;i<=tot;++i)
	{
		int t=1;
		for(int j=1;j<=k;++j)//计算每个联通块路径总数
			t=(t*co[i])%mod;
		ans=(ans-t+mod)%mod;//减去不标准序列
	}
	printf("%lld",ans);
	return 0;//完美结束
}
```

---

## 作者：SakurajiamaMai (赞：0)

下面介绍两种做法，一种是**并查集和幂计算**，另一种是  **dfs** 和**幂计算**，想更快点就用快速幂。思路简单来说就是正难则反，反着来，找到红色连通块的所有个数，然后用总个数减去就可以了。最后不要忘记，如果是负数要加上  mod 才行。

**第一种 搜索 :**

```cpp
// dfs 解法
//用 dfs 记录下来一个连通块的节点数，然后用幂运算算出不合法的方案数。
#include<bits/stdc++.h>
#define ll long long 
using namespace std;
const int N=1e5+10,mod=1e9+7;
int n,k,idx;
ll res,num;
vector<int>mp[N];
bool vis[N];
//快速幂
// ll qpow(ll x,ll y){
//     ll ba=x,ans=1;
//     while(y){
//         if(y&1) ans=(ans*ba)%mod;
//         ba=(ba*ba)%mod;
//         y>>=1;
//     }
//     return ans;
// }

//普通幂
ll qpow(int x,int cc)
{
    ll ans=1;
    for(int i=0;i<cc;i++) ans=(ans*x)%mod;
    return ans;
}
void dfs(int x)
{
    vis[x]=true;
    ++idx;
    for(auto i:mp[x]) if(!vis[i]) dfs(i);
}
int main()
{
    std::ios::sync_with_stdio(false);
    cin>>n>>k;
    for(int i=1;i<n;i++){
        int a,b,c;
        cin>>a>>b>>c;
        if(c==0) mp[a].push_back(b), mp[b].push_back(a);
    }
    res=qpow(n%mod,k)%mod;
    for(int i=1;i<=n;i++)
        if(!vis[i]){
            idx=0;
            dfs(i);
            num=(num+qpow(idx,k))%mod;
        }
    cout<<(res-num+mod)%mod;
    return 0;
}
```

**下面是并查集 :**

```cpp
//并查集解法:
//用并查集来维护是否合法。
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e5+10,mod=1e9+7;
int p[N],n,k,vis[N],cnt,idx,mp[N];
bool st[N];
ll res,num;
int find(int x)
{
    if(p[x]!=x) p[x]=find(p[x]);
    return p[x];
}
ll qpow(int x)
{
    ll ans=1;
    for(int i=0;i<k;i++) ans=(ans*x)%mod;
    return ans;
}
int main()
{
    std::ios::sync_with_stdio(false);
    cin>>n>>k;
    for(int i=1;i<=n;i++) p[i]=i;
    for(int i=1;i<=n;i++){
        int a,b,c;
        cin>>a>>b>>c;
        if(c==0) p[find(a)]=find(b);//如果是红的就加进去。
    }
    res=qpow(n%mod);
    for(int i=1;i<=n;i++) mp[find(i)]++;//新方法注意，如何找出这个点的连通块数量?
    //很明显是这样找得到啦，建立一个桶。
    for(int i=1;i<=n;i++) num=(num+qpow(mp[i]))%mod;
    cout<<(res-num+mod)%mod<<endl;
    return 0;
}

```



---

## 作者：两年打铁 (赞：0)

各位神仙都想到了用冰茶几，蒟蒻太菜，就打了一发树形DP。

合法方案很难，我们考虑不合法的方案。

首先，如果自下而上没有遇到过黑边，那么这个节点的贡献是$sz[x]^k$ 

然后我们考虑遇到红边，那么自红边以上都不能向下走。

此时与红边相连的节点就不能合并，那么我们再开一个数组，记录被红边截断以下的节点产生的贡献，那么答案就是$n^k-f[1]-sum[1]$

注意转移sum的时候要把所有子节点的sum都转移过来，遇到红边再加上节点的贡献，但是f数组的转移不是累加的，而是单个算的。

```cpp
/*
 * @Author: CSJ1 
 * @Date: 2019-06-04 13:13:29 
 * @Last Modified by:   CSJ1 
 * @Last Modified time: 2019-06-04 13:13:29 
 */

#include<bits/stdc++.h>
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)
#define int long long 
const int big=0x7fffffff;
using namespace std;
inline void read(int &x)
{
    x=0;char ch=getchar();int pd=1;
    while(ch<'0'||ch>'9'){if(ch=='-')pd=-pd;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    x*=pd;
}
inline void write(const int &x)
{
    char ggg[10001];int s=0;int tmp=x;
    if(tmp==0){putchar('0');return;}
    if(tmp<0){tmp=-tmp;putchar('-');}
    while(tmp>0){ggg[s++]=tmp%10+'0';tmp/=10;}
    while(s>0){putchar(ggg[--s]);}
}
const int N=2e5+233;
const int mod=1e9+7;

int t,h[N],sz[N],f[N];
int sum[N];
int n,k;

inline int ksm(int x,int y)
{
	int ans=1;
	while(y)
	{
		if(y&1)
		{
			ans=(ans*x)%mod;
		}
		x=(x*x)%mod;
		y>>=1;
	}
	return ans%mod;
}

struct dd
{
    int end,nt,s;
}e[N<<2];
inline void add(int begin,int end,int s)
{
	++t;
	e[t].s=s;
	e[t].end=end;
	e[t].nt=h[begin];
	h[begin]=t;
}


void dfs(int x,int fa)
{
	sz[x]=1;
    for(register int i=h[x];i;i=e[i].nt)
    {
    	
        int u=e[i].end;
        if(u==fa)continue;
        dfs(u,x);
		if(e[i].s==1)
		{
			sum[x]+=f[u]+sum[u];
			sum[x]%=mod;
		}
		else 
		{
			sz[x]+=sz[u];
			sum[x]+=sum[u];
			sum[x]%=mod;
		}
    }
    f[x]=ksm(sz[x],k);
    f[x]%=mod;
}

signed main()
{
    read(n);
    read(k);
    for(register int i=1;i<=n-1;++i)
    {
        int xx,yy,kk;
        read(xx);
        read(yy);
        read(kk);
        add(xx,yy,kk);
        add(yy,xx,kk);
    }
    dfs(1,0);
    int ans=((ksm(n,k)-f[1]-sum[1])+mod+mod)%mod;
    write(ans);
    return 0;
}// ck ak ioi ddjxd
```


---

## 作者：da32s1da (赞：0)

考虑计算总的方案数$n^k$，减去所有红边的联通块的方案数$size^k$，用并查集维护大小即可。

这里还有几个优化没加。。

1. 这里的快速幂可以线筛
2. 可以考虑最后计算红边联通块的方案数

~~但是不加也能过啦~~

```cpp
#include<cstdio>
const int N=2e5+50;
const int mod=1e9+7;
int n,k,x,y,z,Ans;
int fa[N],siz[N];
int ksm(int u,int v){
	int res=1;
	for(;v;v>>=1,u=1ll*u*u%mod)
	if(v&1)res=1ll*res*u%mod;
	return res;
}
int get(int u){return u==fa[u]?u:fa[u]=get(fa[u]);}
void merge(int u,int v){
	int r=get(u),s=get(v);
	fa[r]=s;
	Ans=(Ans-ksm(siz[r],k)+mod)%mod;
	Ans=(Ans-ksm(siz[s],k)+mod)%mod;
	siz[s]+=siz[r];
	Ans=(Ans+ksm(siz[s],k))%mod;
}
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)fa[i]=i,siz[i]=1;//初始化父亲，大小
	Ans=n;//初始化答案
	for(int i=1;i<n;i++){
		scanf("%d%d%d",&x,&y,&z);
		if(z==0)merge(x,y);//合并两个红边联通块
	}
	Ans=(ksm(n,k)-Ans+mod)%mod;//用总的方案数减去
	printf("%d\n",Ans);
}
```

---

