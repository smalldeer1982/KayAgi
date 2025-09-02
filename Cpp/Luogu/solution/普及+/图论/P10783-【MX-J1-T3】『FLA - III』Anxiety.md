# 【MX-J1-T3】『FLA - III』Anxiety

## 题目背景

原题链接：<https://oier.team/problems/J1C>。

---

I came. I saw. I had anxiety. I left.

## 题目描述

给定一棵拥有 $2^n-1$ 个节点的二叉树，节点 $i$ 的权值为 $w_i$，节点 $1$ 为根节点。对于所有非根节点 $i$ 都有一条双向边连接节点 $i$ 和节点 $\left\lfloor \frac{i}{2} \right\rfloor$。请注意 $\left\lfloor X \right\rfloor$ 表示不大于 $X$ 的最大整数。

定义节点 $u,v$ 的距离为从节点 $u$ 到节点 $v$ 最少需要经过的边数。给定 $m$ 组询问，第 $i$ 组询问给定三个正整数 $x_i,y_i,k_i$，你需要输出树上与 $x_i,y_i$ 两个节点的距离都不超过 $k_i$ 的节点的权值之和。

## 说明/提示

**「样例解释 #1」**

![example](https://cdn.luogu.com.cn/upload/image_hosting/1au4l6hm.png)

对于第一组询问，满足条件的节点有 $1,2$，权值和为 $2$。

对于第二组询问，满足条件的节点有 $1,2,3,4,5,6,7$，权值和为 $7$。

对于第三组询问，满足条件的节点有 $1,2,3$，权值和为 $3$。

**「数据范围」**

|测试点编号|$n \leq$|$m \leq$|$k_i \leq$|$w_i \leq$|
|:-:|:-:|:-:|:-:|:-:|
|$1$|$2$|$5$|$5$|$10$|
|$2 \sim 3$|$10$|$1000$|$1000$|$1000$|
|$4 \sim 5$|$18$|$2 \times 10^5$|$5$|$10^9$|
|$6 \sim 7$|$18$|$2 \times 10^5$|$10^9$|$1$|
|$8 \sim 10$|$18$|$2 \times 10^5$|$10^9$|$10^9$|

对于 $100\%$ 的数据，$2 \leq n \leq 18$，$1 \leq m \leq 2 \times 10^5$，$1 \leq x_i,y_i \leq 2^n-1$，$1 \leq k_i \leq 10^9$，$1 \leq w_i \leq 10^9$，$x_i \neq y_i$。节点的编号是从 $1$ 到 $2^n-1$ 的整数。

## 样例 #1

### 输入

```
3 3
1 1 1 1 1 1 1
3 4 2
5 4 6
3 2 2```

### 输出

```
2
7
3```

## 样例 #2

### 输入

```
4 5
3 4 10 7 1 6 10 6 16 5 3 16 6 2 9
1 4 6
4 2 1
1 14 5
6 13 3
11 15 2
```

### 输出

```
104
11
74
51
0
```

# 题解

## 作者：ScaredQiu (赞：21)

### 完美二叉树

#### 测试点 $1$

总共有 $3$ 个节点，直接分讨。

#### 测试点 $2 \sim 3$

注意到 $2^{10}=1024$，树上的节点至多 $1023$ 个。

建树，对于每个询问暴力遍历整棵树并标记哪些节点和 $x$ 的距离不超过 $k$，哪些节点和 $y$ 的距离不超过 $k$，然后枚举节点计算答案。

时间复杂度 $O(2^nm)$。

#### 测试点 $4 \sim 5$

树上节点至多有 $2^{18}-1=262143$ 个。

注意到 $k_i \leq 5$，所以**和某个节点的距离不超过 $k_i$ 的节点不会太多。**

具体有多少呢？首先对于给定节点 $x$，它自己肯定满足要求（距离为 $0$），如果 $x$ 既不是叶子节点也不是根节点，它就一定有 $3$ 个相邻节点（距离为 $1$），这 $3$ 个相邻节点既不是叶子节点也不是根节点的话，它们每个节点就也有 $3$ 个相邻节点，排除掉 $x$ 之后它们每个节点都能贡献 $2$ 个新的节点（距离为 $2$）...

可以得到满足条件的节点数量不超过 $1+3+3 \times 2+3 \times 2^2+3 \times 2^3+3 \times 2^4=94$ 个，询问时暴力遍历的效率可以接受。

对于第 $i$ 次询问，先从节点 $x_i$ 开始遍历，标记所有与 $x_i$ 距离不超过 $k_i$ 的节点；然后从节点 $y_i$ 开始遍历，遇到有标记的节点就将其计入答案。**注意清空标记时应当只清空被标记的节点，否则时间复杂度可能退化**。笔者的做法是再从 $x_i$ 遍历一次并取消被遍历到的节点的标记。

这里认为回答一次询问的时间复杂度为 $O(1)$，总体时间复杂度 $O(2^n+m)$。

这个做法能通过测试点 $1 \sim 5$ 并获得 $50$ 分，**注意答案可能超出 `int` 范围。**

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,lim,w[300'000];
vector<int> v[300'000];
bool on[300'000];
long long ans;
void dfs(int x,int las,int step,int uim,function<void(int)> fun){
    fun(x);
    if(step<uim) for(int i:v[x]) if(i!=las) dfs(i,x,step+1,uim,fun);
}
long long query(int x,int y,int k){
    ans=0ll;
    dfs(x,0,0,k,[&](int x)->void{on[x]=1;});
    dfs(y,0,0,k,[&](int x)->void{ans+=on[x]*w[x];});
    dfs(x,0,0,k,[&](int x)->void{on[x]=0;});
    return ans;
}
int main(){
    ios::sync_with_stdio(0);
    cin>>n>>m,lim=(1<<n)-1;
    for(int i=1;i<=lim;i++) cin>>w[i];
    for(int i=2;i<=lim;i++) v[i].push_back(i/2),v[i/2].push_back(i);
    for(int i=1;i<=m;i++){
        static int x,y,k;
        cin>>x>>y>>k;
        cout<<query(x,y,k)<<'\n';
    }
    return 0;
}
```

#### 测试点 $6 \sim 7$

现在尝试将问题转化，举个例子：询问和节点 $8,14$ 的距离都不超过 $5$ 的节点权值和。

**这等价于询问所有和节点 $1$ 的距离不超过 $2$ 的节点权值和。**

为啥？因为节点 $1$ 到节点 $8,14$ 的距离相等，是路径中点。对于节点 $2$ 子树中的节点，它们与节点 $14$ 的距离肯定比与节点 $8$ 的距离大，所以只要这些节点与节点 $14$ 的距离符合要求，它们就一定符合要求。节点 $3$ 子树中的节点同理，只要它们与节点 $8$ 的距离符合要求，也就一定符合要求。

又因为节点 $1$ 到节点 $8,14$ 的距离相等（$3$），所以只用计算和节点 $1$ 的距离不超过 $5-3=2$ 的节点权值和。

![](https://cdn.luogu.com.cn/upload/image_hosting/0j14ichs.png)


再来一个例子：询问和节点 $5,13$ 的距离都不超过 $4$ 的节点权值和。

这等价于询问所有和节点 $1,3$ 形成的连通块的距离不超过 $1$ 的节点权值和。转化方式同上，由于路径上的节点有偶数个计算过程会复杂一些。

现在尝试利用 $w_i=1$ 的条件，**注意到给定的树是一棵完美二叉树，所以当节点 $x$ 的子树中存在与其距离为 $k$ 的节点时，它子树内与节点 $x$ 距离不超过 $k$ 的节点权值和为 $2^k-1$。**

又因为完美二叉树的性质很好，从任意节点向上枚举到根节点的时间复杂度为 $O(n)$，可以一边向上枚举一边计算答案，具体实现见文末代码。

时间复杂度 $O(2^n+nm)$。

另外由于 $w_i=1$，本质不同的询问只有 $O(n^3)$ 个，可能存在其他的做法。

#### 测试点 $8 \sim 10$

沿用上一个做法，预处理节点 $x$ 的子树中与其距离不超过 $k$ 的节点权值和。因为完美二叉树的性质很好甚至不用把树建出来。计算答案时很可能需要当前节点兄弟的信息，因为完美二叉树的性质，节点 $x$ 的兄弟就是 $x \oplus 1$（$\oplus$ 表示异或），这是容易的。

时间复杂度 $O(n2^n+nm)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long s[20][300'000];
int n,m,lim;
void dfs(int x){//预处理节点子树权值和
    if(x*2>lim){
        for(int i=1;i<=n;i++) s[i][x]=s[0][x];
        return;
    }
    dfs(x*2),dfs(x*2+1);
    for(int i=1;i<=n;i++) s[i][x]=s[0][x]+s[i-1][x*2]+s[i-1][x*2+1];
}
long long query(int x,int y,int k){
    static int xi,yi,mid,cnt[2],a[2][40];
    static long long ret;
    xi=0,yi=1,cnt[0]=0,cnt[1]=0;
    while(x!=y){
        if(x<y) swap(x,y),swap(xi,yi);
        a[xi][++cnt[xi]]=x,x/=2;
    }
    a[xi][++cnt[xi]]=x;
    for(int i=cnt[yi];i>=1;i--) a[xi][++cnt[xi]]=a[yi][i];
    k-=cnt[xi]/2;
    if(k<0) return 0ll;
    if(cnt[xi]%2==1){//存在唯一的路径中点
        mid=a[xi][cnt[xi]/2+1];
        ret=s[min(k,n)][mid];
    }
    else{//不存在路径中点需要处理的东西更多
        mid=max(a[xi][cnt[xi]/2],a[xi][cnt[xi]/2+1]);
        ret=s[min(k,n)][mid];
        if(k>=1) ret+=s[min(k-1,n)][mid^1];
        mid/=2,ret+=s[0][mid];
    }
    for(int i=1;i<=k&&mid!=0;i++){//向上枚举
        if(k-i>=1) ret+=s[min(k-i-1,n)][mid^1];
        mid/=2,ret+=s[0][mid];
    }
    return ret;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m,lim=(1<<n)-1;
    for(int i=1;i<=lim;i++) cin>>s[0][i];
    dfs(1);
    for(int i=1;i<=m;i++){
        static int x,y,k;
        cin>>x>>y>>k;
        cout<<query(x,y,k)<<'\n';
    }
    return 0;
}
```

---

## 作者：shinzanmono (赞：10)

## Anxiety 题解

定义 $h_{u,i}$ 表示与点 $u$ 的距离 $\leq i$ 的点的权值和，很显然，可以通过换根 dp 轻易求出。

我们对 $\mathrm{dis}(u,v)$ 的奇偶性进行讨论。

**$\textrm{dis}(u,v)$ 为偶数**

我们可以直接找到路径中点 $c$，答案为 $h_{c,k-\frac{\mathrm{dis}(u,v)}{2}}$。

**$\mathrm{dis}(u,v)$ 为奇数**

此时最大的问题是：路径中点不存在。不妨设路径最中间的边为 $(\frac{c}{2},c)$。

首先定义点 $u$ 到边 $(x,y)$ 的距离为 $\max(\mathrm{dis}(u,x),\mathrm{dis}(u,y))$，那么我们要求出所有满足到 $(\frac{c}{2},c)$ 的距离 $\leq k-\frac{\mathrm{dis}(u,v)-1}{2}$。考虑容斥，可推出：
$$
ans=\sum_{i=0}^{k-\frac{\mathrm{dis}(u,v)-1}{2}-1}(-1)^{k-\frac{\mathrm{dis}(u,v)-1}{2}-i-2}(h_{\frac{c}{2},i}+h_{c,i})
$$
直接求解即可。

总复杂度 $O(2^nn+nm)$。

---

## 作者：huangrenheluogu (赞：7)

~~口胡超快，调试超久，鉴定为码力不行。~~

题目质量高于 CSP-J2023。

下面的题解中，记 $N$ 为树的大小，及 $N=2^n-1$。

由于完全二叉树的性质，树高应该是 $O(\log N)$ 的，所以可以暴力跳。

考虑记 $f_{p,0/1,d}$ 表示以 $p$ 的左/右儿子为根的子树，深度不超过 $d$ 的节点的权值之和，这个是容易预处理的，暴力跳即可。

同时，需要预处理 $x$ 的深度（其实可以用 $\log_2 x$ 表示深度）。

了解 $\mathcal{O}(1)$ 判断 $x$ 是左儿子还是右儿子，这个可以看 $x$ 二进制最后一位。

考虑把询问 $(x,y,k)$ 的答案分成几个部分，显然这个 lca 是好求的，也是暴力即可。

- 路径上的节点。

可以暴力跳一遍 $x\to y$ 的路径，挨个判断上面的点 $p$ 和 $x,y$ 的距离的 $\max$，看是否更新。

- $x/y$ 的子树内节点。

下面以 $x$ 子树内节点为例，此时需要 $x$ 不是 lca。

可以算出 $x$ 到 $y$ 的距离 $d$，那么需要 $x$ 子树内距离 $x$ 不超过 $k-d$ 的节点，就是 $x$ 子树内深度不超过 $dep_x+k-d$ 的节点，已经预处理过了。

- $x,y$ 作为 lca 的时候的另一半子树

不妨 $x$ 是 lca，此时一定是 $y$ 一直跳 fa 跳到 $x$。

暴力跳一遍就可以知道这一条 $y\to x$ 的链是左侧还是右侧，那么需要统计另外一棵子树的答案，这个和上面是类似的。

- $x,y$ 的 lca 继续向上跳。

记这个点为 $p$，显然易知 lca 到 $p$ 是走 $p$ 的左子树还是右子树，处理出 $p$ 到 $x,y$ 的最大距离，容易得出 $p$ 的该子树中深度 $\le lim$ 的权值都可以统计答案，统计答案即可。

所有部分都做完了，复杂度 $O(n2^n+mn)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ls (p << 1)
#define rs (p << 1 | 1)
#define fa (p >> 1)
using namespace std;
const int N = 1 << 18 | 5;
int n, m, w[N], f[N][2][105], dep[N], lg[N], LCA;
int x, y, k, ans, dist, d, pos;
inline void calc(int p, int d, int w){
	while(fa){
		f[fa][p & 1][d] += w;
		p = fa;
	}
}
inline void dfs(int p){
	dep[p] = lg[p];
	calc(p, dep[p], w[p]);
	if(dep[p] == n - 1) return ;
	dfs(ls), dfs(rs);
}
inline int lca(int x, int y){
	while(x ^ y){
		if(dep[x] > dep[y]) x = x >> 1;
		else y = y >> 1;
	}
	return x;
}
inline void solve(){
	ans = 0ll;
	if(max(dep[x], dep[y]) - dep[LCA] <= k) ans = w[LCA];
	for(int i = x; i != LCA; i = i >> 1){
		if(dep[i] + dep[y] - dep[LCA] * 2 <= k && dep[x] - dep[i] <= k) ans += w[i];
	}
	for(int i = y; i != LCA; i = i >> 1){
		if(dep[i] + dep[x] - dep[LCA] * 2 <= k && dep[y] - dep[i] <= k) ans += w[i];
	}
	dist = dep[y] - dep[LCA];
	d = k - dist + dep[LCA];
	d = min(d, n);
	pos = 0;
	if(x ^ LCA){
		ans += f[x][0][d] + f[x][1][d];
		for(int i = x; (i >> 1) != LCA; i = i >> 1){
			d = k - max((dep[i >> 1] + dep[y] - 2 * dep[LCA]), dep[x] - dep[i >> 1]) + dep[i >> 1];
			d = min(d, n);
			ans += f[i >> 1][i & 1 ^ 1][d];
		}
		for(int i = x; i != LCA; i >>= 1){
			if((i >> 1) == LCA) pos = i & 1;
		}
	}
	dist = dep[x] - dep[LCA];
	d = k - dist + dep[LCA];
	d = min(d, n);
	if(y ^ LCA){
		ans += f[y][0][d] + f[y][1][d];
		for(int i = y; (i >> 1) != LCA; i = i >> 1){
			d = k - max((dep[i >> 1] + dep[x] - 2 * dep[LCA]), dep[y] - dep[i >> 1]) + dep[i >> 1];
			d = min(d, n);
			ans += f[i >> 1][i & 1 ^ 1][d];
		}
		for(int i = y; i != LCA; i >>= 1){
			if((i >> 1) == LCA) pos = i & 1;
		}
	}
	if(x == LCA || y == LCA){
		d = k + dep[LCA] - max(dep[x], dep[y]) + dep[LCA];
		ans += f[LCA][pos ^ 1][min(d, n)];
	}
	d = k - max(dep[x] - dep[LCA], dep[y] - dep[LCA]) + dep[LCA] - 2;
	while(d >= 0 && LCA != 1){
		if(dep[LCA >> 1] <= d) ans += f[LCA >> 1][LCA & 1 ^ 1][min(d, n)] + w[LCA >> 1];
		LCA = LCA >> 1;
		d -= 2;
	}
	d = min(d, n);
	printf("%lld\n", ans);
}
signed main(){
//	freopen("data.in", "r", stdin);
//	freopen("code.out", "w", stdout);
	scanf("%lld%lld", &n, &m);
	for(int i = 1; i < 1 << n; i++) scanf("%lld", &w[i]);
	for(int i = 2; i < 1 << n; i++) lg[i] = lg[i >> 1] + 1;
	dfs(1);
	for(int i = 1; i < 1 << n; i++){
		for(int j = 1; j <= n; j++){
			f[i][0][j] += f[i][0][j - 1];
			f[i][1][j] += f[i][1][j - 1];
		}
	}
	while(m--){
		scanf("%lld%lld%lld", &x, &y, &k);
		LCA = lca(x, y);
		solve();
	}
	return 0;
}
```

---

## 作者：Night_sea_64 (赞：5)

介绍一种不同的方法。

第一步的思路有的题解讲到了，就是 $x$ 到 $y$ 路径上找中间点 $mid$，求出离 $mid$ 的距离不超过一个值的点的权值和。这里就不再赘述了。

但是对于 $x$ 到 $y$ 的路径上中间位置的点有两个，即 $x$ 到 $y$ 的路径长度为奇数时我没想出怎么推式子。于是我考虑了一个暴力的办法：在所有边上都添加一个权值为 $0$ 的点，即将一条边变为两条。这样查询的两个点的路径长度一定是偶数了，就可以接着执行上面的操作了。

只不过就是空间有点大，AC 记录是 400 多 MB。

```cpp
#include<iostream>
#include<vector>
using namespace std;
int n,m,a[530000],dep[530000],fa[530000][10];
long long down[530000][36],up[530000][72];
vector<int>v[530000];
bool isnew(int x)
{
    if(x<(1<<n))return 0;
    else return 1;
}
int bro_id(int x)
{
    if(!isnew(x))return x^1;
    else return ((x-(1<<n))^1)+(1<<n);
}
void dfs1(int x,int last)
{
    dep[x]=dep[last]+1,fa[x][0]=last;
    for(int i=1;i<10;i++)
        fa[x][i]=fa[fa[x][i-1]][i-1];
    for(int i=0;i<2*n;i++)down[x][i]=a[x];
    for(auto y:v[x])
    {
        dfs1(y,x);
        for(int i=1;i<2*n;i++)
            down[x][i]+=down[y][i-1];
    }
}
void dfs2(int x)
{
    for(auto y:v[x])
    {
        up[y][1]=a[x];
        for(int i=2;i<4*n;i++)
            if(isnew(y))up[y][i]=up[x][i-1]+a[x]+down[bro_id(y)][min(i-2,2*n-1)];
            else up[y][i]=up[x][i-1]+a[x];
        dfs2(y);
    }
}
int LCA(int x,int y)
{
    if(dep[x]<dep[y])swap(x,y);
    for(int i=9;i>=0;i--)
        if(dep[fa[x][i]]>=dep[y])x=fa[x][i];
    if(x==y)return x;
    for(int i=9;i>=0;i--)
        if(fa[x][i]!=fa[y][i])x=fa[x][i],y=fa[y][i];
    return fa[x][0];
}
int get_id(int x,int k)
{
    for(int i=9;i>=0;i--)
        if(k>=(1<<i))x=fa[x][i],k-=(1<<i);
    return x;
}
signed main()
{
    cin>>n>>m;
    for(int i=1;i<(1<<n);i++)cin>>a[i];
    for(int i=2;i<(1<<n);i++)
    {
        v[i/2].push_back((1<<n)+i);
        v[(1<<n)+i].push_back(i);
    }
    dfs1(1,0);
    dfs2(1);
    while(m--)
    {
        int x,y,k;
        cin>>x>>y>>k;
        k=min(k*2,4*n-1);
        int lca=LCA(x,y);
        int dis=dep[x]+dep[y]-2*dep[lca];
        int mid;
        if(dep[x]>dep[y])mid=get_id(x,dis/2);
        else mid=get_id(y,dis/2);
        if(dis/2>k)cout<<0<<endl;
        else cout<<up[mid][k-dis/2]+down[mid][min(k-dis/2,2*n-1)]<<endl;
    }
    return 0;
}
```

---

## 作者：Zhao_daodao (赞：2)

# $\mathcal{P10783~~Solution}$

## description

给你一颗深度为 $n$ 的满二叉树，点有点权，编号为 $1$ 到 $2^n-1$。有 $q$ 组询问，第 $i$ 组询问给定三个正整数 $x_i,y_i,k_i$，你需要输出树上与 $x_i,y_i$ 两个节点的距离都不超过 $k_i$ 的节点的权值之和。

## solution

### 10pts

抽象，我不知道怎么只拿 10pts。

###  30pts

对于每一个询问，暴力统计有多少个点满足条件，直接累加点权。

复杂度 $O(q2^n)$。

### 50pts

发现每一组询问问的点的距离不超过 $5$，也就是说满足一个条件的点的数量不超过 $64$。

直接预处理出每一个点距离不超过 $5$ 的点的集合，在查询时直接开一个 map，统计两个限制都满足的点的点权和即可。

复杂度 $O(n+q)$，有 $64$ 倍常数。

### 70pts

是打完正解才想到的做法。现在题目所求退化为求有多少个点满足条件。

在打 50pts 的时候大概看一下集合的形状，发现形状相当规整，同时每一个深度的点的数量都是固定的。

具体来说，如果是不超过 $k$ 的集合，**深度从浅到深的点的数量** 分别是 $1,1,2,2,4,4,\dots,2^{n-2},2^{n-2},2^{n-1},2^{n-1},2^{n}$。

具体的证明可以自己画几个图，证明非常简单。

同时每一层的所有点的编号还是一个连续段，直接处理出连续段的左端，右端。

在最后只用将每一层的连续段取交，计算交点数量就可以了。

复杂度 $O(qn)$。

### 100pts

几乎就是 70pts，因为每一层的点的编号连续，所以满足条件的点一定是两个连续段的交，肯定也是一个连续段，所以直接处理点权的前缀和，最后分层计算点权和就可以了。

复杂度 $O(qn)$。

## code

在实现的时候有一个问题：包含一个点的连续段的左右端的位置。

只需要向上跳到所有点的祖先，再预处理出祖先的两端就可以了。

```cpp
#include<bits/stdc++.h>
#define int long long
#define Pair pair<int,int>
using namespace std;
const int MAXN=1e6+5;
const int T=30;
int n,q,w[MAXN],s[MAXN];
inline int S(int l,int r){return max(0ll,s[r]-s[l-1]);}
int head[MAXN],tot;
struct node{
    int nxt,to;
}e[MAXN<<1];
inline void add(int u,int v){
    e[++tot].nxt=head[u];
    e[tot].to=v;
    head[u]=tot;
}
Pair all[MAXN][T+1];
int dep[MAXN];
#define fa(x) ((x)>>1)
#define ls(x) ((x)<<1)
#define rs(x) ((x)<<1|1)
void dfs(int x){
    dep[x]=dep[fa(x)]+1;
    all[x][0]=Pair{x,x};
    if(dep[x]<n)dfs(ls(x)),dfs(rs(x));
    for(int i=1;i<=T;i++)all[x][i]=Pair{all[ls(x)][i-1].first,all[rs(x)][i-1].second};
}
inline int LCA(int a,int b){
    if(dep[a]!=dep[b]){
        if(dep[a]<dep[b])swap(a,b);
        a>>=(dep[a]-dep[b]);
    }
    while(a!=b)a>>=1,b>>=1;
    return a;
}
Pair fir[T*2+1],sec[T*2+1];
inline Pair point(int x,int siz,int dep){
    siz=min(siz,dep-1);
    int rt=x>>siz;
    return all[rt][siz];
}
signed main(){
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);
    cin>>n>>q;
    for(int i=1;i<(1<<n);i++)cin>>w[i],s[i]=s[i-1]+w[i];
    dfs(1);
    for(int x,y,k;q--;){
        cin>>x>>y>>k;
        if(k>=2*n-2){
            cout<<S(1,(1<<n)-1)<<"\n";
            continue;
        }
        for(int i=dep[x]-k;i<=dep[x]+k;i++){
            int siz=(i-(dep[x]-k))>>1;
            int now;if(i<dep[x])now=x>>(dep[x]-i);else now=x<<(i-dep[x]);
            if(!now)continue;
            if(i>=0)fir[i]=point(now,siz,i);
        }
        for(int i=dep[y]-k;i<=dep[y]+k;i++){
            int siz=(i-(dep[y]-k))/2;
            int now;if(i<dep[y])now=y>>(dep[y]-i);else now=y<<(i-dep[y]);
            if(!now)continue;
            if(i>=0)sec[i]=point(now,siz,i);
        }
        int ans=0;
        for(int i=max(dep[x]-k,dep[y]-k);i<=min(dep[x]+k,dep[y]+k);i++){
            if(i<0)continue;
            int st=max(fir[i].first,sec[i].first);
            int ed=min(fir[i].second,sec[i].second);
            ans+=S(st,ed);
        }
        cout<<ans<<"\n";
    }
}
```

---

## 作者：I_AM_CIMOTA (赞：2)

发现深度很小，所以直接统计某个深度的答案是可行的。

于是我们记 $f(u,i)$ 表示 $u$ 往子树内在 $i$ 步内能到达的所有点的权值和，记 $g(u,i)$ 表示 $u$ 往子树外在 $i$ 步以内能到达的所有点的权值和。

对于 $f$，不难发现有转移：
$$
f(u,i)=f(ls_u,i-1)+f(rs_u,i-1)+w_u
$$
对于 $g$ 的转移稍微复杂。现在我们观察 $u$ 子树外的答案的构成，我们发现除了 $fa_u$ 子树外的答案外还需要加上 $fa_u$ 的另外一个儿子的子树内的答案，这等价于直接加上 $fa_u$ 子树内的答案再减去 $u$ 子树内的答案。（可借助下图思考）
![](https://cdn.luogu.com.cn/upload/image_hosting/5zqxi295.png)
发现 $w_{fa_u}$ 被统计了两次，所以还要额外减去一个 $w_{fa_u}$ 才行，转移如下：
$$
g(u,i)=g(fa_u,i-1)+f(fa_u,i-1)-f(u,i-2)-w_{fa_u}+w_u
$$

现在我们得到了所有点的 $f$ 和 $g$ 的值，下面考虑对于每一个询问如何得到答案。

如果 $k$ 很大，那么等价于询问所有点的权值和，这是好处理的。

否则我们找到 $u\leftrightarrow v$ 这条链，显然它的长度不会很长，我们找到链上的所有满足要求的点。除这些点外，与这些点有连接的若干个连通分量中还可能会产生贡献（下图中标红的和标绿的连通分量）：
![](https://cdn.luogu.com.cn/upload/image_hosting/fpig8vdj.png)
我们可以用 $f$ 来计算红色部分的贡献，用 $g$ 来计算绿色部分的贡献，然后这道题就做完了。

如果你还是不知道怎么实现，可以参考我的代码：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N=5e5+5;
int n,m,w[N],h[N],f[N][50],g[N][50];

void dfs1(int u){
	if(u>n)return;
	dfs1(u<<1),dfs1(u<<1|1);
	f[u][0]=w[u];
	for(int i=1;i<=40;i++){
		if((u<<1)>n)f[u][i]=w[u];//因为这个地方RE了好久
		else f[u][i]=f[u<<1][i-1]+f[u<<1|1][i-1]+w[u];
	}
}

void dfs2(int u){
	if(u>n)return;
	g[u][0]=w[u];
	if(u==1)for(int i=1;i<=40;i++)g[u][i]=w[u];
	else{
		for(int i=1;i<=40;i++){
			g[u][i]=g[u>>1][i-1]+f[u>>1][i-1]-w[u>>1]+w[u];
			if(i>=2)g[u][i]-=f[u][i-2];
		}
	}
	dfs2(u<<1),dfs2(u<<1|1);
}

signed main(){
	scanf("%lld%lld",&n,&m);
	n=(1ll<<n)-1;
	for(int i=1;i<=n;i++)scanf("%lld",&w[i]);
	for(int i=1;i<=n;i++)h[i]=h[i>>1]+1;
	dfs1(1),dfs2(1);
	while(m--){
		int u,v,k,ans=0;
		scanf("%lld%lld%lld",&u,&v,&k);
		k=min(k,40ll);
		int x=u,y=v,lasx=0,lasy=0,lca;
		while(x!=y){
			if(h[x]<h[y])swap(x,y);
			x>>=1;
		}
		lca=x;
		x=u,y=v;
		int mx;
		while(x!=y){
			if(h[x]<h[y])swap(x,y),swap(lasx,lasy),swap(u,v);
			mx=max(h[u]-h[x],h[v]+h[x]-h[lca]*2);
			if(mx<=k){
				ans+=f[x][k-mx];
				if(k>mx)ans-=f[lasx][k-mx-1];
			}
			lasx=x;
			x>>=1;
		}
		mx=max(h[u]-h[lca],h[v]-h[lca]);
		if(mx<=k){
			ans+=f[lca][k-mx]+g[lca][k-mx]-w[lca];
			if(k>mx)ans-=f[lasx][k-mx-1]+f[lasy][k-mx-1];
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：lwj54joy (赞：1)

# [传送门](https://www.luogu.con.cn/problen/P10783?contestId=181138)
## 思路
我们先找 $ x,y $ 在树上路径的中点，如果路径上点数为奇数，那么就仅存在一个中点 $ n $；否则就会存在两个中点 $ n_1,n_2 $。

**第一种情况**：易得：到 $ x,y $ 距离均不超过 $ k $，相当于到 $ n $ 距离不超过 $ k - \frac{dis - 1}{2} $（其中 $ dis $ 为路径长度）我们可以先 DFS 预处理某个点 $ i $ 子树内到它距离不超过 $ j $ 的点的权值和 $ v_{i,j} $。先将答案加上 $ v_{n,k - \frac{dis - 1}{2}} $，然后向上跳，计算子树外的权值就可以啦。

**第二种情况**：若 $ n_1 $ 是 $ n_2 $ 的儿子，则到 $ x,y $ 距离均不超过 $ k $，等价于 $ n_1 $ 子树内到 $ n_1 $ 距离不超过 $ k - \frac{dis - 2}{2} $，$ n_1 $ 子树外到 $ n_2 $ 距离不超过 $ k - \frac{dis - 2}{2} $。同样统计就可以啦～
```cpp
#include <bits/stdc++.h>

using namespace std;

const int maxn = (1 << 20) + 5;

int n, q;
long long w[maxn], val[maxn][55];

void dfs(int x) {
    if (x >= (1 << n))
        return;
    val[x][0] = w[x];
    dfs(x << 1), dfs(x << 1 | 1);
    for (int i = 1; i <= 50; i++) val[x][i] = val[x << 1][i - 1] + val[x << 1 | 1][i - 1];
}

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= (1 << n) - 1; i++) scanf("%lld", &w[i]);
    dfs(1);
    for (int i = 1; i <= (1 << n) - 1; i++) for (int j = 1; j <= 50; j++) val[i][j] += val[i][j - 1];
    while (q--) {
        int x, y, k;
        scanf("%d%d%d", &x, &y, &k);
        if (k > 50) k = 50;
        int x1 = x, y1 = y, dx = 0, dy = 0;
        while (x1) dx++, x1 /= 2;
        while (y1) dy++, y1 /= 2;
        x1 = x, y1 = y;
        if (dx > dy)for (int i = 1; i <= dx - dy; i++) x1 /= 2;
        else for (int i = 1; i <= dy - dx; i++) y1 /= 2;
        int dl = min(dx, dy);
        while (x1 != y1) x1 /= 2, y1 /= 2, dl--;
        int lca = x1, dis = dx + dy - 2 * dl + 1,mid;
        if (dx > dy) {
            mid = x;
            for (int i = 1; i <= (dis - 1) / 2; i++) mid /= 2;
        } else {
            mid = y;
            for (int i = 1; i <= (dis - 1) / 2; i++) mid /= 2;
        }
        if (dis & 1) {
            if (dis / 2 > k) {
                printf("0\n");
                continue;
            }
            k -= dis / 2;
            long long ans = val[mid][k];
            int pre = mid;
            mid /= 2;
            while (k && mid) {
                k--;
                ans += w[mid];
                if (k) 
                    if (pre == mid * 2) ans += val[mid << 1 | 1][k - 1];
                    else ans += val[mid << 1][k - 1];
                pre = mid, mid /= 2;
            }
            printf("%lld\n", ans);
        } else {
            if (dis / 2 > k) {
                printf("0\n");
                continue;
            }
            k -= dis / 2;
            long long ans = val[mid][k];
            int pre = mid;
            mid /= 2;
            while (k + 1 && mid) {
                ans += w[mid];
                if (pre == mid * 2) ans += val[mid << 1 | 1][k - 1];
                else ans += val[mid << 1][k - 1];
                k--,pre = mid, mid /= 2;
            }
            printf("%lld\n", ans);
        }
    }
}
```

---

## 作者：Moya_Rao (赞：1)

# 题目大意
给定一棵拥有 $2^n-1$ 个节点的二叉树，其中第 $i$ 个节点的权值为 $w_i$，根节点为 $1$。  
除根节点外，所有节点 $i$ 都有一条通往节点 $\lfloor \frac{i}{2} \rfloor$ 的无向边。  
定义 $road(u,v)$ 表示从节点 $u$ 到节点 $v$ 最少经过的边数。  
现给出 $m$ 组询问，每组询问由三个正整数 $x,y,k$ 组成，要你回答所有满足 $road(x,i) \le k$ 且 $road(y,i) \le k$ 的节点 $i$ 的权值之和。
# 思路
**本题考查对满二叉树的性质的利用。**  

## 满二叉树

不难发现，题目给定的这一棵树就是一棵**满二叉树**，而且符合满二叉树的特性：对于每个节点 $i$（叶子结点除外），都与节点 $i \times 2$ 和节点 $i \times 2 + 1$ 分别连有一条**无向边**。  
那么，我们就可以利用这个特性，甚至连图都不用存了。

## 转化问题

现在我们来仔仔细细分析一下题目。

先看下面这张图：
![深度为 $4$ 的满二叉树](https://cdn.luogu.com.cn/upload/image_hosting/d1jr72ur.png)

根据这张图，举个例：询问与节点 $9$ 和节点 $13$ 的距离都不超过 $5$ 的所有节点的权值之和。  
那么要怎么解决这组询问呢？

其实，这个问题可以转化成：  
**询问与节点 $1$ 的距离不超过 $2$ 的所有节点的权值之和。**

咦，为什么呢？  
因为节点 $1$ 到节点 $9$ 和节点 $13$ 的距离是一样的，即 $road(1,9)=road(1,13)$。亦可以理解为节点 $1$ 是节点 $9$ 到节点 $13$ 的路径上的中点。  
这样就会好求解很多，因为只剩下一个节点了嘛。

再举个例：询问与节点 $10$ 和节点 $6$ 的距离都不超过 $4$ 的所有节点的权值之和。

这种情况就没有一个唯一的点是它们之间路径的中点了，这次有**两个点**，或者可以理解为是一条**中边**。

那该怎么处理这条中边呢？  
这条边的两个顶点绝对是一父一子，故可以先将能连到儿子的加上，再加上父亲自己，最后一步步往上跳就可以了，没有那么复杂。

但不管怎样，最近的那条路径绝对经过了它们俩的 LCA，即最近公共祖先。所以，考虑到 $n$ 很小，可以一步步跳 LCA，并在跳的同时把路径存下来，好处理中点或者中边。

这样即可求解出答案了。

## 必不可少的“武器”

不过到了这里我们还缺少一件“武器”。  
是一件什么“武器”呢？是一个 $f$ 数组。

我们定义 $f_{u,p}$ 表示在以 $u$ 为根节点的子树中，和 $u$ 的距离不超过 $p$ 的点的权值之和。  
这个 $f$ 数组可以用一段 DFS 跑出来。

但这个 $f$ 数组有什么用哇？  
它可以帮助我们在后面处理的时候快速地处理权值，方便求解答案。  
因此，这个 $f$ 数组至关重要。

# [AC](https://www.luogu.com.cn/record/175582097) 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int Tree = 5e5+5;
int n,Q,Tsz;
long long f[Tree][50];
void DFS(int u){
    if(u*2>Tsz){//自己就是叶子结点
        for(int i=1;i<=n;i++)f[u][i]=f[u][0];
        return;
    }
    DFS(u*2);DFS(u*2+1);//先跑自己的两个儿子
    for(int i=1;i<=n;i++)
        f[u][i]=f[u][0]+f[u*2][i-1]+f[u*2+1][i-1];//迭代更新
    return;
}
long long solve(int x,int y,int k){
    int id_x=0,id_y=1,mid=0,cnt[2]={0,0},nodes[2][50];
    long long ans=0;
    memset(nodes,0,sizeof(nodes));//初始化
    while(x!=y){//一步步找最近公共祖先并记录下每个点
        if(x<y)swap(x,y),swap(id_x,id_y);//x 始终为最大的
        nodes[id_x][++cnt[id_x]]=x;//往上跳一层
        x/=2;//跳到他的父亲节点
    }
    nodes[id_x][++cnt[id_x]]=x;//最近公共祖先
    for(int i=cnt[id_y];i>=1;i--)
        nodes[id_x][++cnt[id_x]]=nodes[id_y][i];//存下 y 跑的那一段路
    k-=cnt[id_x]/2;//减掉它距离中点的长度
    if(k<0)return 0;//如果连中点都去不到，那别跑了，不可能
    if(cnt[id_x]%2==1){//如果是奇数，即存在唯一的中点
        mid=nodes[id_x][cnt[id_x]/2+1];//存下中点
        ans+=f[mid][min(k,n)];//先加上中点的
    }
    else{
        mid=max(nodes[id_x][cnt[id_x]/2],nodes[id_x][cnt[id_x]/2+1]);
        //先取中边里的那个儿子节点
        ans+=f[mid][min(k,n)];//加上它的值
        if(k>=1)ans+=f[mid^1][min(k-1,n)];//如果可以，把他的兄弟也加进去
        mid/=2;//去到父亲那儿
        ans+=f[mid][0];//把父亲也加上
    }
    for(int i=1;i<=k&&mid>0;i++){//继续往上跳
        if(k-i>=1)ans+=f[mid^1][min(k-i-1,n)];//还可以找他的兄弟
        mid/=2;//往上跳一层
        ans+=f[mid][0];//加上它的权值
    }
    return ans;
}
int main(){
    cin>>n>>Q;
    Tsz=(1<<n)-1;
    for(int i=1;i<=Tsz;i++)cin>>f[i][0];
    DFS(1);
    while(Q--){
        int x,y,k;
        cin>>x>>y>>k;
        cout<<solve(x,y,k)<<endl;
    }
    return 0;
}
```

---

## 作者：modfish_ (赞：1)

## 思路
考虑找到 $x,y$ 在树上路径的中点，若路径上点数为奇数，则存在唯一中点 $m$；否则，存在两个中点 $m_1,m_2$。

讨论第一种情况。不难发现，到 $x,y$ 距离均不超过 $k$，等价于到 $m$ 距离不超过 $k-\frac{dis-1}{2}$，其中 $dis$ 为路径长度。我们可以先 DFS 预处理某个点 $i$ 子树内到它距离不超过 $j$ 的点的权值和 $v_{i,j}$。先将答案加上 $v_{m,k-\frac{dis-1}{2}}$，然后向上跳，计算子树外的权值即可。

对于第二种情况类似。若 $m_1$ 是 $m_2$ 的儿子，则到 $x,y$ 距离均不超过 $k$，等价于 $m_1$ 子树内到 $m_1$ 距离不超过 $k-\frac{dis-2}{2}$，$m_1$ 子树外到 $m_2$ 距离不超过 $k-\frac{dis-2}{2}$。同样统计即可。复杂度 $O(n2^n+nm)$。

## 代码

```cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int maxn = (1 << 20) + 5;

int n, q;
ll w[maxn], val[maxn][55];

void dfs(int x){
	if(x >= (1 << n)) return;
	val[x][0] = w[x];
	dfs(x << 1), dfs(x << 1 | 1);
	for(int i = 1; i <= 50; i ++) val[x][i] = val[x << 1][i - 1] + val[x << 1 | 1][i - 1];
}

int main(){
	scanf("%d %d", &n, &q);
	for(int i = 1; i <= (1 << n) - 1; i ++) scanf("%lld", &w[i]);
	dfs(1);
	for(int i = 1; i <= (1 << n) - 1; i ++) for(int j = 1; j <= 50; j ++) val[i][j] += val[i][j - 1];
	while(q --){
		int x, y, k;
		scanf("%d %d %d", &x, &y, &k);
		if(k > 50) k = 50;
		int x1 = x, y1 = y, dx = 0, dy = 0;
		while(x1) dx ++, x1 /= 2;
		while(y1) dy ++, y1 /= 2;
		x1 = x, y1 = y;
		if(dx > dy) for(int i = 1; i <= dx - dy; i ++) x1 /= 2;
		else for(int i = 1; i <= dy - dx; i ++) y1 /= 2;
		int dl = min(dx, dy);
		while(x1 != y1) x1 /= 2, y1 /= 2, dl --;
		int lca = x1, dis = dx + dy - 2 * dl + 1;
		int mid;
		if(dx > dy){
			mid = x;
			for(int i = 1; i <= (dis - 1) / 2; i ++) mid /= 2;
		}else{
			mid = y;
			for(int i = 1; i <= (dis - 1) / 2; i ++) mid /= 2;
		}
		if(dis & 1){
			if(dis / 2 > k){
				printf("0\n");
				continue;
			}
			k -= dis / 2;
			ll ans = val[mid][k];
			int pre = mid;
			mid /= 2;
			while(k && mid){
				k --;
				ans += w[mid];
				if(k){
					if(pre == mid * 2) ans += val[mid << 1 | 1][k - 1];
					else ans += val[mid << 1][k - 1];
				}
				pre = mid, mid /= 2;
			}
			printf("%lld\n", ans);
		}else{
			if(dis / 2 > k){
				printf("0\n");
				continue;
			}
			k -= dis / 2;
			ll ans = val[mid][k];
			int pre = mid;
			mid /= 2;
			while(k + 1 && mid){
				ans += w[mid];
				if(pre == mid * 2) ans += val[mid << 1 | 1][k - 1];
				else ans += val[mid << 1][k - 1];
				k --;
				pre = mid, mid /= 2;
			}
			printf("%lld\n", ans);
		}
	}
	return 0;
}
```

---

## 作者：_Dolphin_ (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P10783)

## Solution

由于树上任意两点间的距离不超过 $2n-2$，非常小。

所以我们可以先预处理出 $w(x,t)$ 表示距离 $x$ 不超过 $t$ 条边的点的权值和，$0\leq t<2n-2$，$w(x,0)$ 表示当前点的权值。

则有：

$$w(x,t)=\begin{cases}val(x)&t=0\\w(x,0)+w(lson(x),0)+w(rson(x),0)&x=1,t=1\\w(x,0)+w(fa(x),0)+w(lson(x),0)+w(rson(x),0)&2\leq x\leq 2^{n-1}-1,t=1\\w(x,0)+w(fa(x),0)&2^{n-1}\leq x\leq 2^n-1,t=1\\w(lson(x),t-1)+w(rson(x),t-1)-w(x,r-2)&x=1,2\leq t<2n-2\\w(fa(x),t-1)+w(lson(x),t-1)+w(rson(x),t-1)-2\times w(x,r-2)&2\leq x\leq 2^{n-1}-1,2\leq t<2n-2\\w(fa(x),t-1)&2^{n-1}\leq x\leq 2^n-1,2\leq t<2n-2\end{cases}$$

然后对于每个询问，暴力求 LCA，求得 $x$ 到 $y$ 的距离为 $len=\log_2x+\log_2y-2\times \log_2\text{LCA}(x,y)$。

若 $len$ 为偶数，即 $x$ 到 $y$ 有偶数条边，则有一个中间点 $pos$，若 $len/2\leq k$ 答案为 $w(pos,k-len/2)$，否则答案为 $0$。

![图一](https://cdn.luogu.com.cn/upload/image_hosting/7vg8t4m3.png)

若 $len$ 为奇数，即 $x$ 到 $y$ 有奇数条边，则有两个中间点 $pos1,pos2$，若 $(len+1)/2\leq k$ 答案为 $w(pos1,k-(len+1)/2)+w(pos2,k-(len+1)/2)-w(pos1,k-(len+1)/2-1)-w(pos2,k-(len+1)/2-1)+...\pm(w(pos1,0),w(pos2,0))$，即 $\sum_{t=0}^{k-(len+1)/2}(-1)^{k-(len+1)/2-i}(w(pos1,k)+w(pos2,k))$，否则答案为 $0$。

![图二](https://cdn.luogu.com.cn/upload/image_hosting/e8qy2201.png)

### Code(100 pts):

```cpp
#include<bits/stdc++.h>
#define afor(x,y,z) for(int x=y;x<=z;x++)
#define bfor(x,y,z) for(int x=y;x>=z;x--)
#define cfor(x,y) for(int x=head[y];x;x=nxt[x])
using namespace std;
typedef long long ll;
typedef const int cint;
cint N=3e5;
ll n,m,w[N][40],lg[N];
ll calc(ll pos1,ll pos2,ll k) {
    if(k<0) return 0;
	return w[pos1][k]+w[pos2][k]-calc(pos1,pos2,k-1);
}
ll query(ll x,ll y,ll k) {
	if(k>=2*n-2) return w[1][n-1];
	if(lg[x]<lg[y]) swap(x,y);
	ll a=x,b=y;
	a>>=lg[a]-lg[b];
	while(a!=b) a>>=1,b>>=1;
	ll len=lg[x]+lg[y]-2*lg[a];
	if(len&1) {
		ll pos1=x>>len/2,pos2=x>>(len/2+1);
		if((len+1)/2<=k) return calc(pos1,pos2,k-(len+1)/2);
	}
	else {
		ll pos=x>>len/2;
		if(len/2<=k) return w[pos][k-len/2];
	}
	return 0;
}
int main() {
	scanf("%lld%lld",&n,&m);
	afor(i,2,(1<<n)-1) lg[i]=lg[i>>1]+1;
	afor(i,1,(1<<n)-1) scanf("%lld",&w[i][0]);
	w[1][1]=w[1][0]+w[2][0]+w[3][0];
	afor(i,2,(1<<(n-1))-1)
		w[i][1]=w[i][0]+w[i>>1][0]+w[i<<1][0]+w[i<<1|1][0];
	afor(i,1<<(n-1),(1<<n)-1)
		w[i][1]=w[i][0]+w[i>>1][0];
	afor(k,2,2*n-3) {
		w[1][k]=w[2][k-1]+w[3][k-1]-w[1][k-2];
		afor(i,2,(1<<(n-1))-1)
			w[i][k]=w[i>>1][k-1]+w[i<<1][k-1]+w[i<<1|1][k-1]-2*w[i][k-2];
		afor(i,1<<(n-1),(1<<n)-1)
			w[i][k]=w[i>>1][k-1];
	}
	afor(i,1,m) {
		ll x,y,k;
		scanf("%lld%lld%lld",&x,&y,&k);
		printf("%lld\n",query(x,y,k));
	}
	return 0;
}
```

---

## 作者：xixisuper (赞：1)

# P10783 【MX-J1-T3】『FLA - III』Anxiety 题解

一道不需要什么算法的题，需要的是清晰的思维。

## 思路

本题的关键在于这整个树是一棵**满二叉树**，所以任意两点之间的路径长度一定不会超过 $2n$，那么题目中给的那个 $k\le10^9$ 就是纯属唬人的了。

如果每次询问都遍历每个点然后判断是否合法显然会 T 飞，那么我们可以考虑进行这样一个优化：

定义 $f_{u,t}$ 为以 $u$ 为根节点的子树中，与点 $u$ 的距离小于等于 $t$ 的所有点的点权和（不包括点 $u$ 本身）， 然后对于每一次询问，只遍历 $x$ 到 $\text{lca}(x,y)$、$y$ 到 $\text{lca}(x,y)$、$\text{lca}(x,y)$ 到根节点三部分上的点就足够了。

假设我们现在正在遍历 $x$ 到 $\text{lca}(x,y)$ 上的某一点 $u$，$sn$ 为 $u$ 的子节点且也在 $x$ 到 $\text{lca}(x,y)$ 上，记当前点到 $x$ 的距离为 $tx$，到 $y$ 的距离为 $ty$，某个点的点权记为 $A$，则这一个点的贡献为 $A_u+A_{sn\oplus 1}+f_{sn\oplus1.k-\max(tx,ty)-1}$（省略了一些条件），其中 $\oplus$ 为二进制下的异或运算。

我们来分析一下为什么是这个数，首先如果点 $u$ 满足条件，那么对答案必然有一个 $A_u$ 的贡献。其次，如果点 $sn\oplus1$ 满足条件，对答案会有一个 $A_{sn\oplus1}$ 的贡献。最后，对于所有点 $sn\oplus1$ 的子树，满足条件的前提是距离小于等于 $k$，而点 $x,y$ 到点 $sn\oplus1$ 的距离（二者取最大）就应为 $\max(tx,ty)+1$，故所有距离点 $sn\oplus1$ 在 $k-\max(tx,ty)-1$ 以内的点都有贡献，即为 $f_{sn\oplus1.k-\max(tx,ty)-1}$。

当然，我们还需要判断当前的 $tx,ty$ 是否已经大于 $k$ 了，否则的话一定是没有贡献的。

对于 $x$ 到 $\text{lca}(x,y)$、$y$ 到 $\text{lca}(x,y)$、$\text{lca}(x,y)$ 到根节点三段上每一段都进行上述贡献计算就可以得出结果了（注意特殊处理 $\text{lca}(x,y)$ 的贡献），这样单次询问处理的时间复杂度就是 $O(n)$ 的，而 $f$ 数组我们又可以通过一次 dfs 进行求解，故总时间复杂度为 $O(2^n+mn)$。

代码小贴士：开二维 $f$ 数组时注意数组越界的情况（即 $k$ 过大时直接视为 $2n$ 量级的数就行了）。

## 代码

这题的代码是在晚上写的，脑子十分不清醒，所以实现的很丑，求轻喷。

~~也不知道为啥会写 100 多行。~~

```cpp
#include <iostream>
#define ll long long
using namespace std;
const ll N=1LL<<20LL;
ll ceng,n,m;
ll A[N],f[N][20],dep[N];
void dfs(ll u,ll fa){
	dep[u]=dep[fa]+1;
	if((u<<1)>n) return;
	dfs(u<<1,u),dfs(u<<1|1,u);
	f[u][1]=A[u<<1]+A[u<<1|1];
	for(ll i=2;i<20;i++)
		f[u][i]=f[u<<1][i-1]+f[u<<1|1][i-1]+f[u][1];
}
ll get_lca(ll u,ll v){
	if(dep[u]<dep[v]) swap(u,v);
	while(dep[u]>dep[v]) u>>=1;
	while(u!=v) u>>=1,v>>=1;
	return u;
}
inline ll jue(ll a){return a<0?-a:a;}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>ceng>>m;
	n=(1<<ceng)-1;
	for(ll i=1;i<=n;i++) cin>>A[i];
	dfs(1,0);
	ll x,y,k; 
	while(m--){
		cin>>x>>y>>k;
		if(dep[x]<dep[y]) swap(x,y);
		ll lca=get_lca(x,y);
		ll len=dep[x]+dep[y]-2*dep[lca];
		ll ans=0;
		if(lca==y){
			if(len<=k) ans+=A[x];
			if(len<k) ans+=f[x][min(19LL,k-len)];
			ll sn=x,now=x>>1,tx=1,ty=len-1;
			while(now){
				if(tx<=k&&jue(ty)<=k) ans+=A[now];
				ll mx=max(tx,jue(ty));
				if(mx<=k){
					if(mx+1<=k) ans+=A[sn^1];
					if(mx+1<k) ans+=f[sn^1][min(19LL,k-mx-1)];
				}
				sn=now,now>>=1;
				tx++,ty--;
			}
		}
		else{
			if(len<=k) ans+=A[x]+A[y];
			if(len<k) ans+=f[x][min(19LL,k-len)]+f[y][min(19LL,k-len)];
			ll sn=x,now=x>>1,tx=1,ty=len-1;
			while(dep[now]>dep[lca]){
				if(tx<=k&&jue(ty)<=k) ans+=A[now];
				ll mx=max(tx,jue(ty));
				if(mx<=k){
					if(mx+1<=k) ans+=A[sn^1];
					if(mx+1<k) ans+=f[sn^1][min(19LL,k-mx-1)];
				}
				sn=now,now>>=1;
				tx++,ty--;
			}
			sn=y,now=y>>1,ty=1,tx=len-1;
			while(dep[now]>dep[lca]){
				if(tx<=k&&jue(ty)<=k) ans+=A[now];
				ll mx=max(jue(tx),jue(ty));
				if(mx<=k){
					if(mx+1<=k) ans+=A[sn^1];
					if(mx+1<k) ans+=f[sn^1][min(19LL,k-mx-1)];
				}
				sn=now,now>>=1;
				ty++,tx--;
			}
			if(dep[x]-dep[lca]<=k&&dep[y]-dep[lca]<=k) ans+=A[lca];
			sn=lca,now=lca>>1,ty=dep[y]-dep[lca]+1,tx=dep[x]-dep[lca]+1;
			while(now){
				if(tx<=k&&jue(ty)<=k) ans+=A[now];
				ll mx=max(jue(tx),jue(ty));
				if(mx<=k){
					if(mx+1<=k) ans+=A[sn^1];
					if(mx+1<k) ans+=f[sn^1][min(19LL,k-mx-1)];
				}
				sn=now,now>>=1;
				tx++,ty++;
			}
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：min_inf (赞：1)

来个没啥细节的做法。

先只考虑 $x$ 的限制。把 $x \to 1$ 的链单独统计一下，剩余部分就是 $O(n)$ 个子树，限制为距离子树的根小于某个数。暴力预处理出每个点在每个限制下的答案，复杂度 $O(n2^n)$。

对每个子树分开考虑：

- $y$ 在子树外：限制对 $k-\operatorname{dis}(y,rt)$ 取 $\min$，时间复杂度 $O(1)$。

- $y$ 在子树内：用同样的方法拆开 $y \to rt$，直接统计即可，时间复杂度 $O(n)$。

由于子树不交所以第二种情况至多出现一次，时间复杂度 $O(n(2^n+q))$。

[code](https://oier.team/record/66939204699c296d421c1e92)

---

