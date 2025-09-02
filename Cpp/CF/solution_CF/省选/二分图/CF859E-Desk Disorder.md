# Desk Disorder

## 题目描述

A new set of desks just arrived, and it's about time! Things were getting quite cramped in the office. You've been put in charge of creating a new seating chart for the engineers. The desks are numbered, and you sent out a survey to the engineering team asking each engineer the number of the desk they currently sit at, and the number of the desk they would like to sit at (which may be the same as their current desk). Each engineer must either remain where they sit, or move to the desired seat they indicated in the survey. No two engineers currently sit at the same desk, nor may any two engineers sit at the same desk in the new seating arrangement.

How many seating arrangements can you create that meet the specified requirements? The answer may be very large, so compute it modulo $ 1000000007=10^{9}+7 $ .

## 说明/提示

These are the possible assignments for the first example:

- 1 5 3 7
- 1 2 3 7
- 5 2 3 7
- 1 5 7 3
- 1 2 7 3
- 5 2 7 3

## 样例 #1

### 输入

```
4
1 5
5 2
3 7
7 3
```

### 输出

```
6
```

## 样例 #2

### 输入

```
5
1 10
2 10
3 10
4 10
5 5
```

### 输出

```
5
```

# 题解

## 作者：是个汉子 (赞：10)

 [洛谷传送门](https://www.luogu.com.cn/problem/CF859E)	[CF传送门](http://codeforces.com/problemset/problem/859/E)

今天[ChPu437](https://www.luogu.com.cn/user/283885)大神讲了这个题，我也来写篇[题解](https://chpu437.gitee.io/2020/10/24/solution/codeforces/CF859E/)加深理解。

### Solution

看题，什么又是方案数？~~我反手就是一个计数DP~~

我们转化题意，可以将一个人旧的座位和新的座位**假装**建一条边

那么这就是一张图，并且可能有多个连通块

因为每个连通块之间是互不影响的，所以我们可以分开考虑然后用乘法原理统计

so，这张图上会出现什么连通块呢

发现每个点的**出度**只能为 $0$ 或 $1$ ，分别对应着题中没人的座位和有人的座位

那连通块只有四种：1.树（即有一个出度为 $0$ 的点）2.环（无出度为 $0$ 的点）3.基环树（和2差不多）4.自环

---

开始考虑这几种情况

#### 1.树

我们就以出度为 $0$ 的点为根

考虑对于树上的每一个点，如果它想到它父亲的位置，它的父亲就也得往前，那么它到根这条路径上的点都得往前挪

什么？根怎么办？它又没有父亲，被占就被占了呗（。＾▽＾）

每个点都可以这样，所以方案数为树的 $siz$ （注意，此时根的方案就是每个点都不动）

#### 2.环和基环树

对于一个环，要么都往前，要么不动，方案数是 $2$ 

对于基环树的**环上的**每一个点，入度都为 $2$ ，所以基环树的**树上的**点一个都不能动，不然环上的点会被两次占用

那么我们就可以将环和基环树一起考虑

所以基环树也是 $2$ 

#### 3.自环

不能动，就是 $1$ 

---

情况讨论完了，怎么判环呢

我刚刚说的是**假**建图，所以并不是用dfs

那么什么东西可以查询两点之间的关系并且修改+记录呢——并查集登场了

这个题的做法就讲完捏♪(^∇^*)

### Code

```c++
#include<bits/stdc++.h>
#define ll long long

using namespace std;
const int N=2e5+10,mod=1e9+7;
int f[N],siz[N],n;
ll ans=1;
bool sf_cir[N],cir[N];

inline int find(int x){
    return f[x]==x?x:f[x]=find(f[x]);
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=2*n;i++){
        f[i]=i;
        siz[i]=1;
    }
    for(int i=1,x,y;i<=n;i++){
        scanf("%d%d",&x,&y);
        if(x==y) sf_cir[x]=1;
        int fx=find(x),fy=find(y);
        if(fx!=fy){
            f[fx]=fy;
            sf_cir[fy]|=sf_cir[fx];
            siz[fy]+=siz[fx];
            siz[fx]=0;
        }
        else cir[fx]=1;
    }
    for(int i=1;i<=2*n;i++){
        if(find(i)==i&&!sf_cir[i]){
            if(cir[i]) ans=ans*2%mod;
            else ans=ans*siz[i]%mod;
        }
    }
    printf("%lld\n",ans);
    return 0;
}
```



---

## 作者：yuhaocheng (赞：2)

## 分析

我们不妨把这些座位看作是一张图中的节点，把每个人的诉求作为一条边（由【原座位】指向【想去的座位】）

比如，对于样例#1，我们就可以得到这样一张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/jtijv9fb.png)

显然，我们有可能会得到多个连通图（比如上面这张）

因为每个座位上的人都只有一个想去的座位，所以每个点的出度就是 $0$（可能只有其他的点指向它） 或 $1$，整每个连通图的边数就是 $n$ （点的个数）或者 $n - 1$ 个

当边数等于 $n$ 时，显然这是一个**环**或者一棵**基环树**（定义见[这里](https://blog.csdn.net/weixin_45697774/article/details/108948457)）

我们以这组数据举例：


```
7
1 2
2 4
3 2
4 1
5 3
6 3
7 6
```

~~手画一下~~复制到[Graph Editor](https://csacademy.com/app/graph_editor/)，可以得到这张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/chufrqa7.png)

试着移动每一个点，容易发现：移动r任意环外点（比如这里的 $3$、$5$、$6$、$7$），环上的点肯定就没位置了。 

**证明（~~废话~~）** ：点 $2$ 唯一的一条出边已经用在环上了，所以 $2$ 和任意环外点之间的边一定是指向 $2$ 的，以此类推，我们可以发现：$3$、$5$、$6$、$7$ 对应的边都是指向 $2$ 的。于是，只要移动必定会移到 $2$ 的位置

于是我们就可以得到结论：如果这是一棵基环树或者一个环，那么它的答案为 $2$（环内的点移/不移，两种情况）

当边数等于 $n$ 时，显然这是一棵**树**

我们拿它????举例：

![](https://cdn.luogu.com.cn/upload/image_hosting/4qmktzjh.png)

每个节点的出度都为 $1$ 或 $0$（只可能有一个点出度为 $0$，这个座位一开始就空着），所以我们可以将唯一的那个出度为 $0$ 的点（如这张图中的点 $0$）作为树根。

显然，我们移动任意一个点，都会导致一种确定且不重复的情况（它到根节点的链上的每一个点都往上移），所以其答案为 $n$，即点数

于是，最终的答案就是将每个连通图的答案乘起来。

## HowTo

我们现在需要一种方法，可以判环、可以记录每个连通图的大小。

显然，`并查集`很合适。

每输入一个人的要求，我们就把这两个点所在的集合（连通图）合并（merge函数），同时记录集合大小（sz数组）。如果合并前这两个点已经在同一个集合中，那么，这一定是一个环（两点之间有不止一条路径），做一下标记。

最后，统计答案即可。

**你以为结束了？**

还有一个坑。。。

出现自环时，不能向上面那样考虑，因为这一个点移动后还在原来的位置，所以答案是 $1$（最终ans不变）

## 细节请看代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long // 好习惯：随时开long long

#define MAXN 200005
#define MOD 1000000007 // 记得取模

int n;
int fa[MAXN]; // 并查集 - 父节点
int sz[MAXN]; // 并查集 - 集合大小
bool ish[MAXN]; // is环（记录此集合是否有环）
bool iszh[MAXN]; // is自环

void init(int x) { // 并查集 - 初始化
    for (int i = 1; i <= x; i++) {
        fa[i] = i;
        sz[i] = 1; // 初始大小都是1
    }
}

int find(int x) { // 并查集 - 查找
    if (fa[x] == x) {
        return x;
    } else {
        return fa[x] = find(fa[x]);
    }
}

void merge(int x, int y) { // 并查集 - 合并
    int fx = find(x);
    int fy = find(y);
    if (fx == fy) { // 已经在同一个集合
        return;
    }
    iszh[fy] |= iszh[fx]; // 合并自环信息
    sz[fy] += sz[fx]; // 合并大小
    fa[fx] = fy;
}

signed main() {
    cin >> n;
    init(n * 2); // 初始化
    for (int i = 1; i <= n; i++) {
        int a, b;
        cin >> a >> b;
        if (a == b) {
            iszh[find(a)] = 1; // 标记当前集合含有自环
        }
        if (find(a) == find(b)) { // 已经在同一个集合了
            ish[find(a)] = 1; // 标记当前集合含有环
        }
        merge(a, b); // 连接这两个座位
    }
    int ans = 1;
    for (int i = 1; i <= n * 2; i++) {
        if (find(i) == i) { // i是一个集合的代表
            if (ish[i]) { // 含有环
                if (iszh[i]) { // 自环，答案不变
                    continue;
                }
                ans *= 2;
                ans %= MOD;
            } else { // 不含有环
                ans *= sz[i];
                ans %= MOD;
            }
        }
    }
    cout << ans << endl;
}
```

## AC

---

## 作者：chengni (赞：2)

首先我们先读一遍题，每个椅子有两个选择，本身的位置和另一个位置，这个形状我们怎么处理呢？ ~~二分图匹配~~

但看起来并搞不出来啊(也许是我太菜了)

我们理性分析一下，把每个联通块分类，其实这也就三种情况。

第一种，这是一个没有环的图，或者说是一棵树。相当于有 $x-1$ 个椅子和 $x$ 个点，共有 $x$ 种情况。

第二种，这是一个正常的有环图(无自环)，因为他首尾相连，所以牵一发而动全身，只有两种情况。

第三种，出现了自环，那么只有一种可能了。

好我们统计联通块的种类再乘起来就可以了

统计环用冰茶姬就可以了，然后再顺便判一手自环，这样就能处理这三种情况了

```cpp
#include<bits/stdc++.h>

using namespace std;

inline int read(){
	char ch=getchar();int x=0,f=1;
    while(ch<'0' || ch>'9') {
       if(ch=='-') f=-1;
	  	  ch=getchar();
	}
    while(ch<='9' && ch>='0') {
	   x=x*10+ch-'0';
	   ch=getchar();
	}
    return x*f;
}

int f[202002];
int loop[202020];//自环
int size[202002];//环的大小
int c[200202];//环

int find(int x){//冰茶姬
	if(x==f[x]) return x;
	else return f[x]=find(f[x]);
}

int main(){
	int n=read();
	for(int i=1;i<=2*n;i++){//要搞到2n啊
		f[i]=i;
		size[i]=1;
	}
	for(int i=1;i<=n;i++){
		int x=read(),y=read();
		if(x==y) loop[x]=1;
		int fx=find(x),fy=find(y);
		if(fx!=fy){
			f[fx]=fy;
			loop[fy]|=loop[fx];//是否有自环
			size[fy]+=size[fx];
			size[fx]=0;
		}
		else c[fx]=1;
	}
	long long ans=1;//根据乘法原理，我们把每个情况乘起来
	for(int i=1;i<=2*n;i++){//方案数跟前面说的一样
		if(find(i)==i && loop[i]==0){
			if(c[i]!=0){
				ans=ans*2;
			}
			else ans=ans*size[i];
		}
		ans%=1000000007;
	}
	cout<<ans;
	return 0;
}
```












---

## 作者：gyyyyx (赞：1)

[题面](https://www.luogu.com.cn/problem/CF859E)

~~氺~~

明显，如果将某同学新旧座位相连，那一定可以变成多个连通图。

而节点数只能为人数或人数加一（至多有一个人想要坐某位置且没有人坐），边数定为人数（每一个人只可能将新旧座位相连）。

因此对于每一个连通图就可以分两种情况：

1. 是一棵树（边数等于点数减一）：这种情况一定有**一个**人的新座位没人坐，我们以此节点为根，建立有根树。

	那么就会建成类似这样的树：

	![](https://cdn.luogu.com.cn/upload/image_hosting/lqx3o882.png)

	即所有除根节点以外的节点一定是某人的旧座位，而它的父亲节点一定是此人新座位，简单算一下就知道有**方案数等于节点数**。

2. 是一棵基环树（边数等于点数）：显然，基环树唯一的一个环可以让环里面所有人都移动到新座位，但环外面的人如果移动了，那一定会让环内某个人没有位置可以替换。

	类似这样：

	![](https://cdn.luogu.com.cn/upload/image_hosting/fpgx18zi.png)

	![](https://cdn.luogu.com.cn/upload/image_hosting/oszlt9fl.png)

	![](https://cdn.luogu.com.cn/upload/image_hosting/g30109sw.png)

	所以，**方案数一定等于二**（环里面移动和不移动）。

但普通建树过于麻烦，所以有没有更简单的方法呢？

并查集！！！

问题就搞定了？

还有一个坑点——自环。

因为在自环的情况下边数等于点数，所以其它地方是不能动的，也不可能出现另一个环（包括另一个自环）。

而存在自环的那个节点是不能动的，所有这个基环树也是不可能移动的，**方案数为一**。

那就开个数组搞个特判解决。

代码：

```cpp
#include<bits/stdc++.h>
#define p 1000000007
#define N 200005
using namespace std;
int n,fa[N],sz[N],e[N];
bool slf[N];
int Find(int x){return fa[x]==x?x:fa[x]=Find(fa[x]);}
long long ans(1);
int main(){
    scanf("%d",&n);
    for(int i(1);i<=(n<<1);++i)
        fa[i]=i;
    for(int i(1);i<=n;++i){
        int u,v;scanf("%d%d",&u,&v);
        if(u==v) slf[u]=1;//特判自环
        int fu(Find(u)),fv(Find(v));
        fa[fu]=fv;++e[fu];
    }
    for(int i(1);i<=(n<<1);++i){
        int fi(Find(i));++sz[fi];
        if(fi^i) e[fi]+=e[i];
        slf[fi]|=slf[i];//连通图是否存在自环
    }
    for(int i(1);i<=(n<<1);++i)
        if(Find(i)==i&&!slf[Find(i)]){
            if(sz[i]==e[i]) (ans<<=1ll)%=p;//基环树
            else (ans*=sz[i])%=p;//数
        }
    cout<<ans<<endl;
    return 0;
}
```

完结撒花~~~

---

## 作者：约瑟夫用脑玩 (赞：1)

艹，做个水题还大意，当做对自己的警醒吧。。。

只考虑人，由有人的位置向它想坐的位置连边，如果不是空位置的话这就是个显然的基环树森林。

嗯。。。还是个内向的。

考虑空位置可能带来的影响，如果有些人想坐的是个空位置，看上去就是棵以空位置为根的内向树。

如果有个人想动那么到根链都得动，并且把其他人的位置卡住，所以方案数应该是这棵树的 $size$。（大意了

再考虑内向基环树的贡献，发现就环可以轮换一次，方案数为 $2$。

细节：

- 特判自环。

- 数组开两倍。

- 内向树不好遍历，把边倒过来变成外向树即可。

- 内向基环树随便判，外向基环树和内向基环树的判法不变，并查集什么的纯属多余，其他题解感觉是~~nt~~学艺不精。

代码：

```
inline int DFS(int x)
{
	int i,to;
	sz[x]=vst[x]=1;
	for(i=h[x];i;i=nxt[i])
	{
		if(vst[to=tto[i]])
		{
			if(vst[to]==1&&x^to)ans=Ad(ans<<1);
			sz[x]+=sz[to];
			continue;
		}
		sz[x]+=DFS(to);
	}
	vst[x]=2;
	return sz[x];
}
signed main()
{
	#ifndef ONLINE_JUDGE
	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	#endif
	int i,x;
	n=read();
	for(i=1;i<=n;i++)
	{
		x=read();ade(read(),x);
	}
	for(ans=i=1;i<=n<<1;i++)
	{
		if(!vst[i])
		{
			DFS(i);
		}
	}
	for(i=1;i<=n<<1;i++)
	{
		if(!du[i])
		{
			Mul(ans,sz[i]);
		}
	}
	writenum(ans,10);
	return output;
}
```

---

## 作者：_maze (赞：0)

# 题意简述

翻译很清楚了

# 题目解法

如果一个人想去的位置上原来坐着人，那么他要坐到这个位置上，就要把原来的人赶走。

原来的人被赶走了，就只能去想去的位置。如果那个位置上有人，又要把那个人赶走。

我们发现，如果将每个人原来的位置连一条单向边到想要的位置上，那么这种关系似乎是一棵树。每一个人能换，当且仅当他的父亲能换

这种关系会在什么时候结束呢？第一种情况，到了一个没人坐的节点。这种情况当然皆大欢喜，树上任何一个人，只要他想换，都能换成功（但最多只能成功一个人，因为另一个人如果也想换，就必定会有一个位置上挤着两个想要换的人）。

第二种情况，到了树上一个节点。那么这时就不是树了，这是一棵基环树。对于一棵基环树，我们只有全换和全不换两种情况。同时，树上不属于环的节点肯定都不能换。因为如果换了，那么环上节点必须要换，因为根节点换了。此时必定不会合法。

如果是自环呢？那么这个节点相当于不能换。不能换，也就不能被赶走。这棵树只有一种情况，就是都不换。

这个题就变成了简单的乘法原理。

注意，位置是人的两倍，输入的第一个数是人数

我们可以用并查集查找根节点。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll mod = 1e9 + 7;
const ll maxn = 2e5 + 5;
ll n;
ll fa[maxn], si[maxn], a[maxn];
bool ton[maxn];
ll find(ll u){ return (fa[u] == u) ? fa[u] : fa[u] = find(fa[u]); }
signed main(){
	freopen("text.in", "r", stdin);
	scanf("%lld", &n);
	for(ll i = 1;i <= 2 * n;i ++) fa[i] = i, si[i] = 1;
	ll u, v;
	for(ll i = 1;i <= n;i ++)
	{
		scanf("%lld%lld", &u, &v);
		a[u] = v;	
		if(u == v) continue;
		ll U = find(u), V = find(v);
		// cout << u << ' ' << v << ' ' << U << ' ' << V << endl;
		if(U == V)
		{
			si[V] = -1;
		}
		else
		{
			fa[U] = V;
			if(si[V] != -1) si[V] += si[U];//每一个人开始的位置是不同的，所以只有根节点可能形成环
		}
	}
	ll ans = 1;
	for(ll i = 1;i <= 2 * n;i ++)
	{
		ll zu = find(i);
		if(ton[zu] == 1 || (a[zu] == zu) || si[zu] == -2) continue;
		ton[zu] = 1;
		if(si[zu] == -1) si[zu] = 2;
		ans *= si[zu];
		ans %= mod;
	}
	printf("%lld\n", ans);
	return 0;
}
```


---

