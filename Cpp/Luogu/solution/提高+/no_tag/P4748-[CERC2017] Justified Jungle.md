# [CERC2017] Justified Jungle

## 题目描述

给你一棵包含 $ N $ 个节点的树 $ (N \leq 10^6) $，求可以通过删除树上的多少条边，使得得到的森林满足其中所有的树都包含相同数量的节点。输出所有合法的删边数量。

合法的删边数量 $ k $ 指的是存在至少一种方案，删去了恰好 $ k $ 条边，得到的森林满足其中所有的树都包含相同数量的节点。

## 样例 #1

### 输入

```
8
1 2
2 3
1 4
4 5
6 7
8 3
7 3```

### 输出

```
1 3 7```

# 题解

## 作者：cyhzz (赞：11)

不错的思维题 7.5/10

假设你要切k条边，那么你会把这棵树切成k+1个连通块，每一块的大小为n/(k+1)，则k+1必定是n的约数

~~枚举约数？T了~~

任意选一个点为根，建树。假设你切掉了连接(fa[u],u)的一条边，那么u这棵子树大小必定是n/(k+1)的倍数。那我们找出满足子树大小等于n/(k+1)的倍数的点，若数量等于（k+1）那么一定可行。
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN=2010000;
int n,siz[MAXN],sum[MAXN],q[MAXN],ans;
int tot,front[MAXN],to[MAXN],nxt[MAXN];
void init(int u,int v)
{
	to[++tot]=v;
	nxt[tot]=front[u];
	front[u]=tot;
}
void dfs(int u,int father)
{
	siz[u]++;
	for(int i=front[u];i;i=nxt[i])
	{
		int v=to[i];
		if(v==father)continue;
		dfs(v,u);
		siz[u]+=siz[v];
	}
	sum[siz[u]]++;
}
bool check(int x)
{
	x++;
	if(n%x)return 0;
	int u=n/x,v=0;
	for(int i=u;i<=n;i+=u)v+=sum[i];
	return (v==x);
}
int main()
{
//	freopen("test.in","r",stdin);
	//freopen("test.out","w",stdout);
	scanf("%d",&n);
	for(int i=2,u,v;i<=n;i++)
	{
		scanf("%d%d",&u,&v);
		init(u,v);
		init(v,u);
	}
	dfs(1,0);
	for(int i=1;i<n;i++)
		if(check(i))
			q[++ans]=i;
	//printf("%d\n",ans);
	for(int i=1;i<=ans;i++)printf("%d ",q[i]);
	return 0;
}

```


---

## 作者：逆天峰王者 (赞：5)

挺好的一道思维题,首先,我们要知道一个联通块的数量一定是n的约数才有可能.
考虑一个暴力的做法,枚举每一个因子u,考虑是否可行,怎么判断是否可行呢？我们考虑一个节点x.  
1.若x的size==u,则我们直接将边(x,fa[x])断掉即可,将size[x]清零.  
2.若x的size<u.则x还不足以构成一个联通块,还需要累加上父亲.先不管.  
3.最难的若x的size>u,我们该怎么考虑,考虑经过上面两个步骤,x的所有儿子的
size一定<u,或者没有贡献(不用考虑)即所有的儿子都需要依靠父亲来构成连通块,但现在x的size已经>u,说明x的子树内一定要产生至少一个联通块.但是无论x分给哪个儿子,其他x的儿子就都断开了,且其size<u,这样出现这种情况的话,就说明u一定不合法.  
这是暴力的做法,实测70pts.  
考虑如何更快速的进行判断.通过上面的分析,我们发现,其实我们断掉的边的size都是u的倍数..因为在上面的操作中,只有size==u时我们才执行断边操作,想象一下,一个点的size==u之后,被清零了,之后其祖宗又够u进行清零了,如果我们将其size原本就累加起来的话,断边操作的判断实质就是是否是u的倍数.  
知道这个之后,我们统计下,所有不同的size的个数,对于一个连通块数量u来说,直接找出能断掉多少条边.判断是否合法即可.
代码(建议自己码):
```cpp
//不等,不问,不犹豫,不回头

#include<bits/stdc++.h>
#define _ 0
#define db double
#define RE register
#define ll long long
#define P 1000000007
#define INF 1000000000
#define get(x) x=read()
#define PLI pair<ll,int>
#define PII pair<int,int>
#define pb(x) push_back(x)
#define ull unsigned long long
#define put(x) printf("%d\n",x)
#define getc(a) scanf("%s",a+1)
#define putl(x) printf("%lld\n",x)
#define rep(i,x,y) for(RE int i=x;i<=y;++i)
#define fep(i,x,y) for(RE int i=x;i>=y;--i)
#define go(x) for(int i=link[x],y=a[i].y;i;y=a[i=a[i].next].y)
using namespace std;
const int N=1e6+10;
int link[N],tot,n,size[N],d[N],num,sum[N];
struct edge{int y,next;}a[N<<1];
bool fail;
inline int read()
{
	int x=0,ff=1;
	char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-') ff=-1;ch=getchar();}
	while(isdigit(ch)) {x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*ff;
}
inline void add(int x,int y)
{
	a[++tot].y=y;
	a[tot].next=link[x];
	link[x]=tot;
}
inline void dfs(int x,int fa)
{
	size[x]=1;
	go(x)
	{
		if(y==fa) continue;
		dfs(y,x);
		size[x]+=size[y];
	}
	sum[size[x]]++;
}
inline bool check(int x)//判断一个连通块的数量为x是否可行. 
{
	if(n%x) return false;
	int v=0;
	for(int i=x;i<=n;i+=x) v+=sum[i];
	return (v-1==(n/x-1)); 
}
int main()
{
	freopen("1.in","r",stdin);
	get(n);
	rep(i,1,n-1)
	{
		int get(x),get(y);
		add(x,y);add(y,x);
	}
	dfs(1,0);
	fep(i,n-1,1) if(check(i)) d[++num]=n/i-1;
	rep(i,1,num) printf("%d ",d[i]);
	return (0^_^0);
}

//吾以吾血,祭吾最后的亡魂



```


---

## 作者：Ian_NIE (赞：1)

## 0x00 前言

本人第四篇题解。

[题目传送门](https://www.luogu.com.cn/problem/P4748)

## 0x01 题目大意

给定一棵树，求合法的删边数量。

**合法的删边数量：** 删除这些边之后可以把树拆成一个森林，这个森林中，每一棵树的结点个数相同。

**森林：** 多棵树组成的结构。依照样例，题目指的森林不能只有一棵树，也就是说，必须删除至少一条边。

## 0x02 算法思路

假设删除 $k$ 条边，那么这棵树会变成有 $k + 1$ 颗树的森林，每一棵树有 $\frac{n}{k+1}$ 个结点，所以 $k+1\;|\;n$。

此时我们直接朴素枚举 $n$ 的约数，次数大约 $\sqrt{n}$，不会超时。

那么我们可以通过什么规律解决这个问题呢？考虑定义 $fa_x$ 表示点 $x$ 的父节点，那么如果删去 $fa_x$ 与 $x$ 的连边，则以 $x$ 点为根的子树的大小就一定是目标的树的大小。此时，枚举所有子树大小为当前枚举约数 $k$ 加一 $k + 1$ 的倍数的点，这些点的个数如果和目标要拆分出的树的个数 $k + 1$ 相等，那么 $k$ 就是一个合法的方案。

另外，对于子树的大小和子树大小为 $t$ 的个数，可以对树进行深度优先搜索 dfs。

## 0x03 部分代码实现

### 0x01 dfs 算法

一个板子，注意 $size_i$ 与 ```dfs()``` 的调用计算位置关系即可。

```cpp
void dfs(int x)
{
	sz[x]++;
	for(int i = head[x]; i; i = nxt[i])
	{
		int y = to[i];
		if(vis[y]) continue;
		vis[y] = true, dfs(y);
		sz[x] += sz[y];
	}
	s[sz[x]]++;
	return ;
}
...
int main(int argc, char** argv)
{
    ...
    vis[1] = true, dfs(1);
    ...
    return 0;
}
```

### 0x02 统计答案

按着思路做就好了，代码实现没有太大的难度。

```cpp
bool chk(int x)
{
	x++; // 直接该原数了，懒得每一次+1
	int cnt = 0;
	for(int i = n / x; i <= n; i += n / x)
		cnt += s[i];
	return (cnt == x);
}
...
int main(int argc, char** argv)
{
    ...
	for(int i = 1; i < n; i++)
		if(!(n % (i + 1)) && chk(i))
			cout << i << ' ';
	cout << endl;
    return 0;
}
```

## 0x04 [整体代码](https://www.luogu.me/paste/l6ym1qi2)

一个整合，好像本来也没有注释。

## 0x05 后记

书写不易，[AC 记录](https://www.luogu.com.cn/record/215031014)。

---

## 作者：zzzyyyyhhhhh (赞：1)

以下默认一个数约数个数 $O(\sqrt n)$ 个。

首先考虑判断一种删边数量是否合法，对于删边数量 $i$，一定可以将树分成 $i+1$ 个连通块，每个大小为 $\frac{n}{i+1}$。容易发现这样的划分方案一定是唯一的。

于是考虑枚举大小，然后 dfs，遇到一个大小刚好为 $\frac{n}{i+1}$ 的连通快就将它从树中删去。

发现复杂度 $O(n\sqrt n)$，无法通过。

思考如何优化，发现 dfs 时遇到的节点大多是没用的，而还有一条重要性质，如果一个节点和它子树大小为 $\frac{n}{i+1}$ 那么它与父亲连的边一定要删，因为删边方案是唯一的。所以判断时不用 dfs，只需要判断大小为 $\frac{n}{i+1}$ 的子树是否恰好 $i+1$ 个即可。

实现 $O(\sqrt n\ln n)+O(n)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e6+100;
int n;
vector<int> a[N];
int siz[N];
int b[N];
void dfs(int x,int fa)
{
	siz[x]=1;
	for(auto i:a[x])
	{
		if(i==fa)continue;
		dfs(i,x);
		siz[x]+=siz[i];
	}
	b[siz[x]]++;
}
signed main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	int x,y;
	for(int i=1;i<n;i++)
	{
		cin>>x>>y;
		a[x].push_back(y);
		a[y].push_back(x);
	}
	dfs(1,0);
	for(int i=n-1;i>=1;i--)
	{
		if(n%i)continue;
		int cnt=0;
		for(int j=i;j<=n;j+=i)
		{
			cnt+=b[j];
		}
		if(cnt==n/i)cout<<n/i-1<<' ';
	}
}
```

---

## 作者：添哥 (赞：1)

一年没写 OI 了，感觉思维变迟钝了。

写几道思维题当康复训练。

------------
给定一棵 $n$ 个点的无根树，询问有多少个 $k$，使得将这棵树删去恰好 $k$ 条边后所得的森林中所有的树都包含相同数量的节点。

首先我们发现，删去恰好 $k$ 条边后这片森林显然会包含 $k+1$ 棵树，且如果要合法，则每棵树都必然包含 $\frac{n}{k+1} $ 个节点。节点数必须是整数，所以 $k+1$ 必然是 $n$ 的约数。

另外我们发现，当你切掉了连接 $u$ 和 $fa_u$ 的边时，以 $u$ 为根的子树包含的节点必然是 $\frac{n}{k+1} $ 的倍数，这样当这棵子树中再删去若干（可以为 $0$）条边后，子树包含的节点仍然是 $\frac{n}{k+1}$ 的倍数，直到恰好为 $\frac{n}{k+1}$。因为删去 $k$ 条边后这片森林会包含 $k+1$ 棵树，因此我们只要保证整棵树中共有 $k+1$ 棵子树包含的节点数是 $\frac{n}{k+1}$ 的倍数即可。

以任意节点为根建树，预处理出所有子树的大小，然后枚举 $n$ 的约数，每次跑一遍 dfs 看看是否合法~~然后就 T 得只剩下 $10$ 分了。~~

可以开一个桶，储存大小恰好为某个值的子树个数，这样枚举约数时直接累加大小是 $\frac{n}{k+1}$ 的倍数的子树个数。

复杂度好像是 $O(\displaystyle \sum_{i=2}^{\sqrt{n}}i+\frac{n}{i})$，也许是线性的？我太菜了不会证，但我知道它肯定不劣于 $O(n\log n)$。

## code
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int fa[1000005];
int sz[1000005];
int ss[1000005];
int to[2000005],nxt[2000005],lst[1000005];//链式前向星存图
int tot;
int ans[1000];
int cnt;
void build(int now)
{
	int sum=0;
	for(int i=lst[now];i;i=nxt[i])
	{
		if(to[i]!=fa[now])
		{
			fa[to[i]]=now;
			build(to[i]);
			sum+=sz[to[i]];
		}
	}
	sz[now]=sum+1;
	ss[sz[now]]++;
}
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n-1;i++)
	{
		int u,v;
		cin>>u>>v;
		tot++;
		nxt[tot]=lst[u];
		lst[u]=tot;
		to[tot]=v;
		tot++;
		nxt[tot]=lst[v];
		lst[v]=tot;
		to[tot]=u;
	}
	fa[1]=0;
	build(1);
	for(int i=2;i*i<=n;i++)
	{
		if(n%i!=0)
		{
			continue;
		}
		int sum=0;
		for(int j=1;j<=i;j++)
		{
			sum+=ss[n/i*j];
		}
		if(sum==i)
		{
			cnt++;
			ans[cnt]=i-1;
		}
		sum=0;
		for(int j=1;j<=n/i;j++)
		{
			sum+=ss[i*j];
		}
		if(sum==n/i)
		{
			cnt++;
			ans[cnt]=n/i-1;
		}
	}
	sort(ans+1,ans+cnt+1);
	for(int i=1;i<=cnt;i++)
	{
		cout<<ans[i]<<' ';
	}
	cout<<n-1;
	return 0;
}
```


---

## 作者：chenruikai (赞：0)

### 题意
给定一棵树，求出所有合法的 $k$，使得删去 $k$ 条边后每棵子树节点数相同。
### 解
这题看上去没有头绪，从简单的想起。假设我们要判断每个子树的节点数能否均为 $m$。

对于整棵树，显然，能被均分的必要条件为节点数能被 $m$ 整除。根节点必定属于均分后的一部分，因此均分后，根节点所在部分一定为 $m$。去除根节点所在部分，剩余部分（如果有）为一些互不连通的子树。同时，剩余部分也一定为 $m$ 的倍数。

好了，现在的问题就变成在一堆子树中能不能继续均分了。如上所示，几次上述操作之后，如果可以被均分，最后一定会剩下一堆大小为 $m$ 的子树。反之一定不行。

由此我们得到了能被均分的充要条件：存在一种方案，将树的根节点划分入某个大小为 $m$ 的连通块，并对其剩余子树进行同样的操作，若干次操作后，只剩下大小为 $m$ 的连通块。

很好，但正如 $F=\frac{GMm}{r^2}$ 少了 $G$ 一样，我们还有一个问题，根节点该划分到哪个连通块，这是一个值得思考的问题。

再次从简单之处看起，对于最后一次，剩下的均为 $m$，也就是说他们肯定在那批大小为 $m$ 的子树上，将他们删去后，倒数第二次剩余的就是本来 $2m$ 的子树。

有思路了，我们只要自底向上每次删去大小为 $am$ 的节点就行了。

到这里，其实你已经解决了问题，但实现上有些许小难。再进一步想，对于不是该删子树的根结点的节点，他的大小一定不为 $m$ 的倍数。所以解决方案很是简单：统计下除根节点的所有大小为 $m$ 倍数的节点数，若与 $k$ 相等，该方案合法。

该代码时间上还有优化的空间，比如约数枚举中只要举 $\sqrt{n}$ 个~~但我比较懒~~。
### code
```cpp
#include <bits/stdc++.h>
using namespace std;

int qread()
{
    int res = 0;char ch = getchar();
    for(;(ch < '0' || ch > '9') && ch != EOF;ch = getchar());
    for(;ch >= '0' && ch <= '9';ch = getchar())res = res * 10 + ch - '0';
    return res;
}
struct cell{int fapos;vector <int> con;int wei;};
cell point[1000006];
int pointnum;
void addedge(int pos1 , int pos2)
{
    point[pos1].con.push_back(pos2);
    point[pos2].con.push_back(pos1);
}
void work(int pos)
{
    point[pos].wei = 1;
    for(int nextpos : point[pos].con)
    {
        if(nextpos == point[pos].fapos)continue;
        point[nextpos].fapos = pos;
        work(nextpos);
        point[pos].wei += point[nextpos].wei;
    }
}
int main()
{
    pointnum = qread();
    int pos1 , pos2;
    for(int i = 0;i < pointnum - 1;i++)
    {
        pos1 = qread() - 1;pos2 = qread() - 1;
        addedge(pos1 , pos2);
    }
    point[0].fapos = -1;
    work(0);
    for(int i = 1;i < pointnum;i++)
    {
        if(pointnum % (i + 1))continue;
        pos1 = pointnum / (i + 1) , pos2 = 0;
        for(int i = 1;i < pointnum;i++)
            if(!(point[i].wei % pos1))pos2++;
        if(pos2 == i)printf("%d " , i);
    }
    return 0;
}
```
玥玥月月如今朝。

---

## 作者：Misophiliac (赞：0)

### 前言

目前唯一一个总时卡进 1s 的，写篇题解纪念一下。

### 题目分析

题意：给出一棵 $n$ 个节点的树，求所有能使原树删去 $k$ 条边后，剩余的每个连通块有相同的节点数的 $k$。

首先容易想到 $(k+1)|n$。

考虑删去边 $(u,fa[u])$，则 $u$ 的子树一定成为一个连通块，其点数应为 $\dfrac n{k+1}$，而所有这样的 $u$ 应有 $k+1$ 个，所以只需记录每一种子树大小的个数，然后枚举 $k$ 并判断即可。

关于复杂度：

$O(\displaystyle\sum_{d|n}d)=O(n\log\log n)$，参看不认识的大佬的[这篇博客](https://www.luogu.com.cn/blog/llqyy/sigma)。

### 代码

码风比较阴间，仅供辅助理解。

```c
#include <stdio.h>
int read() {
    int x = 0; char c = getchar(); for (; c < '0' || c > '9'; c = getchar());
    for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 3) + (x << 1) + (c ^ '0');
    return x;
} int write(int x) { x >= 10 && write(x / 10); return putchar(x % 10 ^ '0'); }
#define N 1000005
int nxt[N<<1], to[N<<1], hd[N], sz[N], cnt[N], tot;
#define ade(u, v) nxt[++tot] = hd[u], to[tot] = v, hd[u] = tot
void dfs(int u, int fa) {
    sz[u] = 1; for (int i = hd[u], v; i && (v = to[i]); i = nxt[i]) v != fa &&
        (dfs(v, u), sz[u] += sz[v]); cnt[sz[u]]++;
}
int main() {
    int n = read(); for (int i = 1, u, v; i < n; i++)
        u = read(), v = read(), ade(u, v), ade(v, u);
    dfs(1, 0); for (int i = 2, s, d, j; i <= n; i++) if (n % i == 0) {
        for (s = 0, d = n / i, j = d; s < i && j <= n; j += d) s += cnt[j];
        (s == i) && (write(i - 1), putchar(' '));
    }
    return 0;
}

```

---

## 作者：Tiankun2010 (赞：0)

# 题意

在给定的树上删去 $k$ 条边，使剩下的森林中的所有树大小相同，问所有合法的 $k$。

# 思路

如果删去了 $k$ 条边，那么原树会变成 $k+1$ 棵树。

所以只需要在 $n \div (k+1)$ 为整数时判断。

如何判断？

如果以 $u$ 为根的子树的大小是 $n \div (k+1)$ 的倍数，那么就需要将 $eg(u,fa[u])$ 删去。

所以直接统计一下这种子树的数量，判断是否等于 $k+1$ 就可以了。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace AC{
    const int maxn=1e6+5;
    
    int n;
    int sz[maxn];
    
    struct edge{int nxt,to;}eg[maxn*2];
    int h[maxn],cnt;
    void in(int u,int v){
        eg[++cnt]={h[u],v};
        h[u]=cnt;
    }//前向星
    
    void dfs_sz(int u,int fa){
        sz[u]=1;
        for(int i=h[u];i;i=eg[i].nxt){
            int v=eg[i].to;
            if(v==fa)continue;
            dfs_sz(v,u);
            sz[u]+=sz[v];
        }
    }//计算sz
    
    bool check(int x){
        if(n%(x+1)!=0)return 0;
        
        int z=0;
        for(int i=1;i<=n;i++)
            if(sz[i]%(n/(x+1))==0)z++;
            
        return z==x+1;
    }//判断删除x条边是否可行
    int main(){
        int u,v;
        scanf("%d",&n);
        for(int i=1;i<n;i++){
            scanf("%d%d",&u,&v);
            in(u,v);
            in(v,u);
        }//输入，建树
        
        dfs_sz(1,0);
        //计算sz
        
        for(int k=1;k<n;k++)
            if(check(k))
                cout<<k<<' ';
        return 0;
    }
}
int main(){return AC::main();}
```


---

## 作者：mklzc (赞：0)

将一颗树切成 `x` 个大小相同的连通块（$x\mid n$），每块大小 $SIZE=\frac{n}{x}$。

考虑到枚举 `n` 的约数 `x` (`x` 表示连通块的个数)，然后判断是否存在删去 $\frac{n}{x}$ 边方案使得 `x` 成立。

**`x` 的存在性判断方法：**

删去任意一条边，都会使得整棵树分成两部分，设这两部分的大小分别为 $p_1$ 和 $p_2$。

那么有 $SIZE\mid p_1$ 且 $SIZE\mid p_2$。（显然只用满足其中一个条件，另一个必然成立）

可以考虑固定一个点为根，预处理出所有点的子树的大小即可。

如果有 `x` 个点的子树大小满足 $SIZE\mid p_1$，那么可以证明存在一种方案，使得树能分成 `x` 个连通块（不为 `x-1` 的原因：根节点必然满足，且没有父亲节点）。


```cpp
#include <bits/stdc++.h>
struct Node
{
    static const int N = 10000005;
    int sz[N], cnt[N], n;
    std::vector<int> ans;
    std::vector<int> G[N];
    void init(int x, int fa)
    {
        sz[x] = 1;
        for (int y : G[x])
            if (y != fa) init(y, x), sz[x] += sz[y];
        cnt[sz[x]]++;
    }
    bool check(int div)
    {
        // div 块，大小为 SIZE
        int SIZE = n / div, sum = 0;
        for (int i = SIZE; i <= n; i += SIZE)
            sum = sum + cnt[i];
        return div == sum;
    }
    void run()
    {
        for (int i = 1; i * i <= n; i++)
            if (n % i == 0)
            {
                if (i != 1 && check(i))
                    ans.push_back(i - 1);
                if (i != n / i && check(n / i))
                    ans.push_back(n / i - 1);
            }
        std::sort(ans.begin(), ans.end());
        for (int x : ans)
            printf("%d ", x);
    }
    void rai()
    {
        scanf("%d", &n);
        int a, b;
        for (int i = 1; i <= n - 1; i++)
        {
            scanf("%d %d", &a, &b);
            G[a].push_back(b);
            G[b].push_back(a);
        }
        init(1, 0);
    }
} work;
int main()
{
    work.rai();
    work.run();
    return 0;
}
```

---

