# [AGC004F] Namori

## 题目描述

给定一个由 $N$ 个顶点和 $M$ 条边构成的无向图。其中，$N-1 \le M \le N$，且图连通。此外，图中没有自环和重边。

顶点编号为 $1$ 到 $N$，边编号为 $1$ 到 $M$。边 $i$ 连接顶点 $a_i$ 和 $b_i$。

每个顶点可以被染成白色或黑色。初始时，所有顶点都是白色的。你需要通过进行以下操作若干次，将所有顶点变为黑色：

+ 选择一对相邻（位于同一条边的两端）的同色顶点，将它们颜色同时反转。即，若均为白色则变为黑色，若均为黑色则变为白色。

请判断是否可以将所有顶点变为黑色，如果可以，输出所需的最小操作次数；否则输出 `-1`。

## 说明/提示

### 数据范围与约定

+ $2 \le N \le 10^5$
+ $N-1 \le M \le N$
+ $1 \le a_i, b_i \le N$
+ 图中没有自环和重边。
+ 图是连通的。

### 部分分

+ 在 $1500$ 分的测试数据中，满足 $M = N-1$。

### 样例解释 #1

例如，可以按照图示的方式进行操作。

![](https://atcoder.jp/img/agc/004/gatbantar/F_1.png)

### 样例解释 #2

无法将所有顶点变为黑色。

![](https://atcoder.jp/img/agc/004/gatbantar/F_2.png)

### 样例解释 #3

此样例不被包含在部分分的测试数据中。

![](https://atcoder.jp/img/agc/004/gatbantar/F_3.png)

### 样例解释 #4

此样例不被包含在部分分的测试数据中。

![](https://atcoder.jp/img/agc/004/gatbantar/F_4.png)

## 样例 #1

### 输入

```
6 5
1 2
1 3
1 4
2 5
2 6```

### 输出

```
5```

## 样例 #2

### 输入

```
3 2
1 2
2 3```

### 输出

```
-1```

## 样例 #3

### 输入

```
4 4
1 2
2 3
3 4
4 1```

### 输出

```
2```

## 样例 #4

### 输入

```
6 6
1 2
2 3
3 1
1 4
1 5
1 6```

### 输出

```
7```

# 题解

## 作者：unputdownable (赞：42)

--------
**题目链接** 

[AT2046 (AGC004F) Namori](https://www.luogu.com.cn/problem/AT2046) (这个是luogu上的链接）

[luogu交不上去用这个](https://vjudge.net/problem/AtCoder-agc004_f) (这个是Vjudge上的链接)

--------
--------

## 一些思路

### 1.奇偶性判断

当 $n$ 为奇数时绝对无解，直接输出``-1``即可。

证明：

如果把每一个点每次黑白的变化叫做“一次变化”，
那么当有解是每个点必经过奇数次变化。
当 $n$ 为奇数时，全图所需的总变化数就为奇数。
而一次操作等于两次变化，由奇偶性易得无解。

~~这小学生都会证我写它干吗~~

当然，也不是 $n$ 为偶数就一定有解，比如这个：

![](https://cdn.luogu.com.cn/upload/image_hosting/plrb2hai.png)

--------

### 2.注意数据范围

注意到 $n-1 \leq m \leq n$，并且图是联通的，可知这张图是一棵[树](https://baike.baidu.com/item/%E6%A0%91/2699484?fr=aladdin)或者一棵[基环树](https://www.cnblogs.com/cly-none/p/9314812.html)。

所以可以轻松看出这是一道**基环树**题。

--------

### 3.转换所求内容

原题的操作为“把两个相连的同色的点的颜色转换”。

但是直接搜很难写。毕竟可能还有一对点要变1,000多次的毒瘤数据存在。

所以，需要一些技巧：

- #### 3-1 间隔染色 (适用于树和偶环基环树)

以样例为例：

![](https://cdn.luogu.com.cn/upload/image_hosting/uw330twc.png)

此时每次操作相当于将两个颜色不同的点对调。

而目标状态即黑白点对调。

由此也可看出对于二分图，有解的条件就是染色后黑白点数目相等。

- #### 3-1-1 树


先看树，考虑每颗子树：

![](https://cdn.luogu.com.cn/upload/image_hosting/wgpk14ow.png)

若有 $a$ 个黑点和 $b$ 个白点，那么目标情况就是 $b$ 个黑点和 $a$ 个白点。

假设 $a > b$，那么从子树根往上的那一条边至少要往外输出 $|\ a-b\ |$ 个黑点，所以在这条边上至少要交换 $|\ a-b\ |$ 次。

而交换了 $|\ a-b\ |$ 次以后，这棵子树内的黑子就能通过树内的互相交换达到目标状态，所以这一条边交换 $|\ a-b\ |$ 次是可以取到的。

那么将每一条边都取这个最小值，即得最小答案。

关于具体求解，令黑点为``-1``权值,白点为``1``权值，dfs跑一边求子树总权值就可以了。同时，记这个权值为 $\{a\}$。则 $ans=\sum_{i=1}^{n}|a_i|$。

- #### 3-1-2偶环基环树


再看看偶环。

![](https://cdn.luogu.com.cn/upload/image_hosting/1qt7hg0r.png)

先剪掉一条边按树处理。

接下来考虑剪掉的这条边的贡献：

![](https://cdn.luogu.com.cn/upload/image_hosting/09by9onp.png)

向上输送 $x$ 点权值后会变成这样。

而又有 $ans=\sum_{i=1}^{n}|a_i|$，所以这条边要使环上的数的绝对值总和最小。

在环上，对于这条边右边的点，$ans_{part}=\sum|a_i-x|$，对于右边的点，$ans_{part}=\sum|a_i+x|=\sum|-a_i-x|$。

为了处理，维护数组 $\{k\}$，使 $k_i=\sum_{j\in\{son\} }k_j$。然后把剪掉的边左右分别标上``1``和``-1``，就可以标记左右半环。

所以 $ans_{cycle}=\sum_{i \in \{x|k_x!=0\}}{|a_i \times k_i-x|}$。

如果把 $a_i \times k_i$ 标记到数轴上，那么就变成了一个求某一点到一堆点的距离和的问题。

![](https://cdn.luogu.com.cn/upload/image_hosting/y1gxgr5a.png)

由初中知识可得 $x$ 取中位数时 $ans_{cycle}$ 最小，$ans$ 也就最小。

最后注意 $ans=ans_{cycle}+ans_{left}+x$，不要忘记加 $x$。

这个操作可以在 $\{a_i \times k_i\ |\ k_i!=0\}$ 取中位数前加入一个``0``实现。（不会影响中位数在的区间，$|0-x|=x$） 

- #### 3-2 间隔染色-奇环基环树

一样的，先间隔染色。

![](https://cdn.luogu.com.cn/upload/image_hosting/5woyjjne.png)

发现有一条边两端的点同色（因为不是二分图）。

此时操作这条边的效果就是使黑点数量+2（全为白时）或-2（全为黑时）。

所以整张图的 $sum_a$ 值为偶数时即有解（其实这个条件是与``n为偶数``对等的）。

先预先使用这一条边操作 $\frac{sum_a}{2}$ 次去掉 $sum_a$，然后就可以不管这一条边了。

于是标记这条边后在dfs时进行特判，剪掉这条边。

发现剪掉以后就变成一棵树，和树一样处理就好（最后记得答案不要忘记加 $\frac{sum_a}{2}$）。

-----

**code:**
```
#include<bits/stdc++.h>
using namespace std;
// #define int long long
void read(int &x)
{
    int r = 0, ne = 1;
    char c;
    while (c < '0' || c > '9')
    {
        if (c == '-')
            ne = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        r = r * 10 + c - '0';
        c = getchar();
    }
    x = r * ne;
}
struct  Edge
{
    /* data */
    int i,nxt;
};
/* 链表 */
int h[100002],tot;
Edge e[200002];
inline void _add(int x,int y){
    e[++tot].i=y;
    e[tot].nxt=h[x];
    h[x]=tot;
    e[++tot].i=x;
    e[tot].nxt=h[y];
    h[y]=tot;
}
/* 输入 */
int n,m,x,y;
/* 偶环-求解 */
int s[100002],top,mid;
/* dfs */
bool odd;/* 奇环 */
int A,B;/* 环两个连接点 */
int w[100002];/* 点绿色权值(1,-1) */ /* 第二遍扫时存的是子树总权值 */
int k[100002];/* 偶环时标记多余边到LCA的点 */
int sum;/* 权值总和 */
long long ans;/* 答案 */
void dfs(int x,int fa){/* 染色 */
    for(int i=h[x];i;i=e[i].nxt){      
        int o=e[i].i;
        if(o==fa)continue;
        if(w[o]){
            if(w[o]==w[x])
                odd=true;
            A=x,B=o;
        }else{
            w[o]=-w[x];
            // sum+=w[o];
            dfs(o,x);
        }
    }
}
void Dfs(int x,int fa){/* 求解 */
    for(int i=h[x];i!=0;i=e[i].nxt){
        int o=e[i].i;
        if(o==fa||(o==A&&x==B)||(o==B&&x==A))continue;/* 排除基环树的干扰 */
        Dfs(o,x);
        w[x]+=w[o];
        k[x]+=k[o];
    }
}
signed main(){
    read(n),read(m);
    for(register int i=0;i<m;++i){
        read(x),read(y);
        _add(x,y);
    }
    if(n%2){
        puts("-1");
        return 0;
    }
    w[1]=1;
    // sum=1;
    dfs(1,0);
    for(int i=1;i<=n;++i)sum+=w[i];    
    if(m+1==n)/* 树 */{
        if(sum){
            puts("-1");
           return 0;
        }
    }else{
        if(odd)/* 奇环 */{
            //if(sum&1){
            //    puts("-1");
            //    return 0;
            //}
            ans+=abs(sum>>1);
            w[A]-=sum>>1,w[B]-=sum>>1;
        }else/* 偶环 */{
            if(sum){
                puts("-1");
                return 0;
            }else 
                k[A]=1,k[B]=-1;
        }
    }
    Dfs(1,0);
    for(register int i=1;i<=n;++i){
        if(k[i])
            s[++top]=k[i]*w[i];
        else
            ans+=abs(w[i]);
    }
    s[++top]=0;//在栈里处理最后需要加的mid(因为偶环那一条被剪掉的边用了mid次，在后面需要用特判加。
    sort(s+1,s+top+1);
    mid=s[(top+1)>>1];
    for(register int i=1;i<=top;++i)
        ans+=abs(s[i]-mid);
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：FlashHu (赞：23)

神仙思维题还是要写点东西才好。

## 树

每次操作把相邻且同色的点反色，直接这样思考会发现状态有很强的后效性，没办法考虑转移。

因为树是二分图，所以我们转化模型：在树的奇数层的所有点上都有一枚棋子，每次可以将棋子移向相邻的空位，目标状态是树的偶数层的所有点上都有棋子。

这样的互换总次数有没有一个下界呢？

我们求出$a_i$表示点$i$子树中棋子数量与空位数量之差（可以是负数），那么$i$的父边就至少要交换$|a_i|$次。

为什么呢？子树里面空位比棋子少的话，肯定要通过父边把$a_i$个棋子送出去，才能移进来$a_i$个空位。反之亦然。

于是，如果$a_{rt}$（根）不为$0$就无解，否则$\sum\limits_{i=1}^n|a_i|$就是答案下界。

然后，仔细推一下发现它就是答案。

对于一个点，它的父边和所有子边的移进移出的顺序，和其它点的顺序是互相独立的。

等于说我们总能安排一个合法的顺序，使得它们一进一出一进一出。。。这样完整地衔接起来，而不会互相矛盾。

## 基环树

### 环长为偶数

显然的想法：把整个环当做根，不在环上的点的答案照算不误。所以把多出来一条边去掉做好树形DP。

首先这还是一个二分图，因此$a_{rt}$不为$0$同样无解。

于是，似乎这条边存在的意义只有分摊一部分转移、减少总次数了。

那么接下来要做的是，确定环上每条边的移动方向和次数。

设环长为$n$，$A_i$为以$i$为根求得的$a$值，$x_i$为环上第$i$条边的移动参数（正负表示方向，绝对值表示次数）

因为进出平衡，我们可以得到一个方程组

$$\begin{cases}x_1-x_2=A_1\\x_2-x_3=A_2\\...\\x_n-x_1=A_n\end{cases}$$

这时候我们发现上面那个方程组是没有唯一解的。那到底该分摊多少呢？

不着急，我们着眼于最小化$\sum|x_i|$，再把方程组整一整

$$\begin{cases}x_1=x_1-0\\x_2=x_1-A_1\\x_3=x_1-A_1-A_2\\...\\x_n=x_1-\sum_{i=1}^{n-1}A_i\end{cases}$$

每一行的$A$都是前缀和的形式，在树形DP的时候对应的是环上的每个点的$a$。

看到这儿就豁然开朗了。这不等于说，数轴上有若干个点取值分别为每一个$a$，找到一个点$x_1$使它到所有点距离之和最小？

把所有$a$排序，$x_1$不就可以取第$\frac n 2$大的数到第$\frac n 2+1$大的数之间的任意整数么？

最后把环上的DP值改一改就OK了。

### 环长为奇数

因为不是二分图了，所以直接解方程好像做不下去。我们从更直观的意义来理解它。

仍然是去掉一条边做树形DP。这时候我们看看，在这条非树边上操作，在奇偶染色模型下等价于什么呢？

没错，两个棋子会在这里同时变成空位，两个空位会在这里同时变成棋子！

那这条边存在的意义，是把棋子或空位中多的减掉、少的补上。要操作多少次呢？$\frac{\sum A_i}{2}$，在树形DP中对应的是$\frac{a_{rt}}{2}$。

注意如果$a_{rt}$是奇数那么无解。否则环底部的$A$发生了变化，导致要把环上的$a$都减掉$\frac{a_{rt}}{2}$。

---

最后的最后扫一遍数组统计答案。代码没有任何难点。
```cpp
#include<bits/stdc++.h>
#define R register int
#define G if(++ip==ie)if(fread(ip=buf,1,SZ,stdin))
using namespace std;
const int SZ=1<<19,N=1e5+9,M=2*N;
char buf[SZ],*ie=buf+SZ,*ip=ie-1;
inline int in(){
    G;while(*ip<'-')G;
    R x=*ip&15;G;
    while(*ip>'-'){x*=10;x+=*ip&15;G;}
    return x;
}
int he[N],ne[M],to[M],f[N],a[N],b[N];
int Getf(R x){
    return x==f[x]?x:f[x]=Getf(f[x]);
}
void Dfs(R x,R op){
    a[x]=op;
    for(R y,i=he[x];i;i=ne[i])
        if((y=to[i])!=f[x])
            f[y]=x,Dfs(y,-op),a[x]+=a[y];
}
int main(){
    R n=in(),m=in(),rt=1,re=1,p=0,ans=0;
    for(R i=1;i<=n;++i)f[i]=i;
    for(R p=0,i=1;i<=m;++i){
        R x=in(),y=in();
        if(Getf(x)!=Getf(y))f[f[x]]=f[y];
        else{rt=x,re=y;continue;}//把多的边单独拿出来
        ne[++p]=he[x];to[he[x]=p]=y;
        ne[++p]=he[y];to[he[y]=p]=x;
    }
    f[rt]=0;Dfs(rt,1);
    if(n==m){//基环树
        for(R x=re;x;x=f[x])b[++p]=a[x];
        if(p&1){//奇环
            if(a[rt]&1)return puts("-1"),0;
            for(R x=re;x;x=f[x])a[x]-=a[rt]>>1;
        }
        else{//偶环
            if(a[rt])return puts("-1"),0;
            sort(b+1,b+p+1);
            for(R x=re;x;x=f[x])a[x]-=b[p>>1];
        }
    }//树
    else if(a[rt])return puts("-1"),0;
    for(R i=1;i<=n;++i)ans+=abs(a[i]);
    return cout<<ans<<endl,0;
}
```

---

## 作者：yijan (赞：18)



神仙题。

考虑一个 $n$ 个点的树的情况怎么处理。

首先进行一次转化，树是一个二分图，于是就进行一次二分图染色。不难发现新图上两端颜色不同当且仅当原图两端颜色相同，所以我们可以把操作从同色翻转变成异色反转，也就是我们进行的操作其实就是在新图上移动黑色点。抄一个官方题解的图：

![_ZJXZH7_FJJB91Y`3TKZRI0.png](https://i.loli.net/2020/11/04/eLBbSzZdhXEiluK.png)

然后问题就变成了一棵树，有一些位置是黑色点，一些位置是白色点，我们每次要移动一个黑色点到相邻的白色点，最后要让所有黑色点归位。

对于树的情况，如果黑点白点数量不同，必然无解。

这是一个经典模型，首先答案是有下界的。我们随意取一个根，对于一个子树，我们设它内部的黑点数减去白点数量为 $a$ ，那么这个子树向上的边至少会被经过 $a$ 次。我们可以证明这个下界是可以达到的。首先，如果不考虑同一个点上不能有两个黑色点，那么移动的次数相当于是一个最小权匹配。这个东西对于一条边，它被经过的次数显然可以是它一边的黑色点个数与白色点个数的差值。因为剩下的可以在内部匹配。然后考虑黑色点不能覆盖，那么对于之前的一种 $u \to v$ 的移动方案，假设中间存在第一个 $t$ 在 $u \to v$ ，那么我们可以让 $t \to v$ 并且让 $u \to t$ 。这样不断调整，一定可以达成 $u$ 上的黑点到达 $v$ 上的目的。

于是答案就是下界 $\sum |a_i|$ 。

具体做法就是，给白色点权值设为 $-1$ ，黑色点设为 $+1$ ，然后求所有位置子树和的绝对值和。

然后就是基环树。

如果环是偶环，那么环边的两侧的颜色是不同的。设环边是 $u \to v$ ， 我们假定这个边会操作 $x$ 次（如果 $x < 0$ 就说明从 $v$ 向 $u$ 操作）。于是我们考虑环中边与环的顶点分成的这两部分，一部分到父亲的边一定会多向下操作 $x$ 次，另一部分到父亲的边一定会多向上操作 $x$ 次。于是设把这条边断掉后每个点跑出的答案是 $a_i$ ，那么最后的答案就是
$$
\sum_{i \in left} |a_i - x| + \sum_{i\in right} |-a_i-x| + |-x|
$$


这个东西就是在数轴上一些点到 $x$ 的和的最小值。可以确定出 $x$ 的值。

如果环是奇环，那么环边操作一次就会让黑色点增加 $2$ 或者让黑色点减少 $2$ 。不难发现，这种情况下如果黑色点白色点的差是偶数就一定可以通过操作这个白边来让整个图有一个解，并且这种边的唯一用处就是用来增加点。

于是我们可以直接给这条基环边的两侧加上全图黑色点与白色点的差除以 $2$ ，然后跑树的做法即可。

```cpp
int n , m;
int A[MAXN];
vi G[MAXN];
int w[MAXN] , od , ev , s = 0;
int lu , lv , fa[MAXN];
void dfs( int u , int f , int wu ) {
	w[u] = wu , s += wu;
	for( int v : G[u] ) if( v != f ) {
		if( w[v] ) {
			if( w[v] * w[u] > 0 ) od = 1;
			else ev = 1;
			lu = u , lv = v;
		} else {
			fa[v] = u;
			dfs( v , u , wu * -1 );
		}
	}
}
int dep[MAXN];
void cfs( int u , int f ) {
	dep[u] = dep[f] + 1;
	for( int v : G[u] ) if( v != f ) {
		if( dep[v] ) continue;
		cfs( v , u );
		w[u] += w[v];
	}
}
int onc[MAXN];
void solve() {
	cin >> n >> m;
	rep( i , 1 , m ) {
		static int u , v;
		scanf("%d%d",&u,&v);
		G[u].pb( v ) , G[v].pb( u );
	}
	dfs( 1 , 1 , 1 );
	if( s & 1 ) return void( puts("-1") );
	ll res = 0;
	if( od ) {
		w[lu] -= s >> 1 , w[lv] -= s >> 1;
		res += abs( s >> 1 );
		s = 0;
	}
	if( s ) return void( puts("-1") );
	cfs( 1 , 1 );
	if( ev ) {
		vi ps;
		if( dep[lu] < dep[lv] ) swap( lu , lv );
		while( dep[lu] != dep[lv] ) onc[lu] = 1 , ps.pb( w[lu] ) , lu = fa[lu];
		ps.pb( 0 );
		sort( all( ps ) );
		int t = ps[ps.size() / 2];
		for( int x : ps ) res += abs( x - t );
	}
	rep( i , 1 , n ) if( !onc[i] ) res += abs( w[i] );
	printf("%lld\n",res);
}
 
signed main() {
//    int T;cin >> T;while( T-- ) solve();
    solve();
}
```



---

## 作者：Little09 (赞：10)

来个神秘做法。先考虑树。

首先我们的操作其实就是每次选一条边，给两端的点权同时 $+1$ 或同时 $-1$。任意时刻需要满足点权范围 $[0,1]$，问你一开始全 $0$ 局面能否到达全 $1$ 局面。

那我们先大手一挥扔掉“任意时刻需要满足点权范围 $[0,1]$”的条件。这个操作可以简化为：给每条边赋一个权值，要求每个点连接的边的边权和为 $1$，最小化每条边的边权的绝对值的和。剩下的问题是简单的，我们从叶子往上做就行，这样可以计算出每条边操作的权值，最后再判一下根的权值是否为 $1$ 即可。

由于我们是把条件放松了的，那么我们得到的答案肯定是最终答案是下界。然后我们构造证明一下最终答案可以取到这个。如果一条边权值为 $x$，那就把它拆成 $|x|$ 个操作。对树上的每个点考虑：我们只需要满足和这个点相关的操作以 $+1,-1,+1,...,-1,+1$ 的顺序做就行，这样这个点就满足一直在 $[0,1]$ 范围内。那我们就给这个点连接的边一个顺序，也就是操作和操作之间有一个顺序，我们发现这个顺序肯定是 DAG，因为在树上不会形成环。

那在基环树上行不行呢？其实也是可行的。我们还是和树一样做，不过由于基环树的那个环可能会形成的不是 DAG，也就是那个环上的边直接产生的环的顺序。那我们对环上的一个点调整：我们把和这个点相关的所有操作倒过来，由于还是 $+1,-1,+1,...,-1,+1$ 并不影响这个点的可行性，同时原本的环也不存在了。

至此我们证明了在树上或基环树上，我们将问题转化为：给第 $i$ 条边一个边权 $w_i$，要求和每个点相连的边满足边权为 $1$，最小化 $\sum|w_i|$。

树上从叶子向根扫就行。对基环树，我们取一个环上的边，设其权值为 $x$，对于奇环，我们可以直接解出 $x$；对于偶环，我们解不出 $x$，不过我们需要最小化一个形如 $\sum|x-x_i|$ 的式子，这个经典套路取中位数就行。

代码不难写。

---

## 作者：ezoiLZH (赞：5)

## 题解：
[这里](https://www.cnblogs.com/ezoiLZH/p/9508104.html)

分三类：树，奇环，偶环

### 1.树
我们可以吧两个相邻的两个颜色相同的点翻转转化为，我们把原树二分图染色，把两个相邻的两个不同颜色的点交换。那我们的目标就是把所有黑点变成白点，白点变为黑点

我们可以看做一个球入洞的问题，白点上都有一个球，黑点上都有一个洞。我们把每个球都放进一个洞里，问最小要移多少次才能使全部球都入洞。

那么方案可行的条件是球和洞的数量相等。

那么我们把白点权值设为1，黑点为-1，那么答案就为

$$ \sum_i sum_i $$

$sum_i$ 为子树 $i$ 的点权和（仔细想想能明白的）。

以上就是为树的解法。

### 2.奇环
奇环只不过是在树上加一条边罢了。

奇环多出来的那条边的两端肯定是同色的，所以对这条边操作一次可以使两个端点同时加上或是减少若干个球。

那我们如果图中球数和洞数不一样的话，我们可以通过操作这条边补成相等。

就像这样：
```cpp
if(sum&1)return printf("-1"),0;	//sum为球数和洞数的差
ans+=abs(sum>>1);
siz[S]-=sum>>1,siz[T]-=sum>>1;
```
奇环卒……

### 3.偶环：
偶环条的两个端点不是同一种颜色的，那我们可以从一个点运 $x$ 个球到另一个点。

那我们其中一个点到 $lca$ 的 $sum$ 都要加 $x$，另一边要减 $x$。

如图：
![这里写图片描述](https://img-blog.csdn.net/20180820205932919?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0FzdGlubGk=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

我们可以得到这些修改后的sum[i]。

我们换一下顺序全部写成 $x-k[i]*sum[i]$ 的形式。

答案就为那些不受影响到点的sum和，加上 $\sum_i |x-k[i]*sum[i]|$

这不是初中的典型数学问题吗？找到一个x使得他到他到数轴上其他n个点的距离最小，
取中位数就行了。

AC……

## COMPLETE CODE：
```cpp
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstdio>
using namespace std;

long long ans=0;
int tot=0,h[100005];
int n,m,x,y,S,T,k[100005],siz[100005];
int s[100005],top;
bool odd;
struct Edge{
	int x,next;
}e[200005];

inline void add_edge(int x,int y){
	e[++tot].x=y;
	e[tot].next=h[x],h[x]=tot;
}

void dfs1(int x,int fa){
	for(int i=h[x];i;i=e[i].next){
		if(e[i].x==fa)continue;
		if(siz[e[i].x]){
			if(siz[x]==siz[e[i].x])odd=true;
			S=x,T=e[i].x;
		}else{
			siz[e[i].x]=-siz[x];
			dfs1(e[i].x,x);
		}
	}
}

void dfs2(int x,int fa){
	for(int i=h[x];i;i=e[i].next){
		if(e[i].x==fa||(x==S&&e[i].x==T)||(x==T&&e[i].x==S))continue;
		dfs2(e[i].x,x);
		siz[x]+=siz[e[i].x];
		k[x]+=k[e[i].x];
	}
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&x,&y);
		add_edge(x,y);
		add_edge(y,x);
	}
	siz[1]=1,dfs1(1,0);
	int sum=0;
	for(int i=1;i<=n;i++)sum+=siz[i];
	if(m==n-1){
		if(sum)return printf("-1"),0;
	}else{
		if(odd){
			if(sum&1)return printf("-1"),0;
			ans+=abs(sum>>1);
			siz[S]-=sum>>1,siz[T]-=sum>>1;
		}else{
			if(sum)return printf("-1"),0;
			else k[S]=1,k[T]=-1;
		}
	}
	dfs2(1,0);
	for(int i=1;i<=n;i++){
		if(k[i])s[++top]=k[i]*siz[i];
		else ans+=abs(siz[i]);
	}
	s[++top]=0;
	sort(s+1,s+top+1);
	int mid=s[top+1>>1];
	for(int i=1;i<=top;i++)ans+=abs(s[i]-mid);
	printf("%lld",ans);
}
```

---

## 作者：User_Unauthorized (赞：3)

> Trees are always bipartite.

首先考虑树的情况。

考虑对树进行黑白染色，那么我们的操作就可以变为了每次选择一个黑点和一个白点，将这两个点染成相反的颜色。不妨将其视作给定两个点集 $S, T$ 满足 $S \cup T = V$, $S \cap T = \varnothing$，初始时在 $S$ 中的每个点上都有一个硬币，每次操作可以将一枚硬币移动一个距离，求能否使得 $T$ 的每个点上都有一个硬币。

考虑如何解决这个问题，首先可以发现硬币的总数是不变的，因此若 $\left\lvert S \right\rvert \neq \left\lvert T \right\rvert$，那么一定无解，反之一定存在一组解。对于答案的统计可以考虑每一条边的贡献，设其连接的两个连通块分别为 $G_1, G_2$，其中 $\left\lvert G_1 \cap S \right\rvert = x, \left\lvert G_2 \cap T \right\rvert = y$，那么这条边的贡献就是 $\left\lvert x - y \right\rvert$，所有边的贡献之和就是答案。

下面考虑基环树的情况，因为对图进行了黑白染色，故按环长进行分类讨论。

对于环长为偶数的情况，可以发现若去掉环上的一条边，那么剩下的图就是一棵树，因此可以直接套用树的情况，这样我们唯一需要处理的就是删去的边带来的贡献。

设 $f_i$ 表示在树的情况下点 $i$ 连向其父亲节点的边的贡献。若我们设删去的边 $\left(u, v\right)$ 的权值为 $k$，即有 $k$ 个硬币从 $u$ 移动到了 $v$，若 $k < 0$ 那么其意味着有 $-k$ 个硬币从 $v$ 移动到了 $u$，那么可以发现 $k$ 的值影响了原图中环上节点即树上被这条边覆盖的区域的边的权值，具体的，这部分的边的贡献为 

$$\sum \left\lvert f_i + k \right\rvert$$

那么我们要求的便是

$$\min \sum \left\lvert f_i + k \right\rvert$$

取 $k$ 为 $f_i$ 序列的中位数即可。

对于环长为奇数的情况，可以发现一定存在环上的一条边 $\left(u_0, v_0\right)$，满足 $u_0$ 和 $v_0$ 属于同一个集合，不妨设其均属于 $S$。那么考虑这条边上的操作，发现其等价于在推硬币的操作上增加了如下操作：

- 若 $u_0$ 和 $v_0$ 上都有硬币，那么拿走这两枚硬币
- 若 $u_0$ 和 $v_0$ 上都没有硬币，那么放上两枚硬币

不难发现通过这样的操作，我们可以调节 $\left\lvert S \right\rvert$ 的值，进而若 $\left\lvert\left\lvert S \right\rvert - \left\lvert T \right\rvert\right\rvert$ 的值为偶数，我们可以使得其有解。具体的设 $k = \left\lvert S \right\rvert - \left\lvert T \right\rvert$，那么我们可以假设在初始情况下 $u_0$ 和 $v_0$ 上均额外存在 $\frac{k}{2}$ 枚硬币，那么继续使用树的情况求解即可。若 $\left\lvert S \right\rvert < \left\lvert T \right\rvert$ 那么我们可以将 $S$ 和 $T$ 互换，然后使用上述方法求解。

时间复杂度为 $O(n)$。

---

## 作者：Leasier (赞：3)

Update on 2023.12.28：感谢 [N_z_](https://www.luogu.com.cn/user/320087)。

------------

$n$ 为奇数时显然无解。下面对 $n$ 为偶数的情况分类讨论。
### Subtask 1：$m = n - 1$ 即原图为一棵树
考虑每次删去几个黑色的叶子让树变小，最终达成目标。

若一开始全白，我们希望把 $u, v$ 变黑，手玩一下可以发现：

- 设 $u \to v$ 路径上第 $i$ 个点为 $p_i$。
- 依次操作 $(u, p_2), (p_3, p_4), \cdots, (p_{|p| - 1}, v)$，使这条路径变为全黑。
- 依次操作 $(p_2, p_3), (p_4, p_5), \cdots, (p_{|p| - 2}, p_{|p| - 1})$，使这条路径上除 $u, v$ 外的点变为全白。
- 上述改法需要满足 $|p|$ 为偶数。

当 $|p|$ 为奇数时，手玩发现确实无法做到上面这点。

$u, v$ **距离为偶数**让我们想到：若对原树黑白染色，$u, v$ 颜色不同。

于是我们得出了有解的一个充要条件：对原树红蓝染色（这里时为了区别于原题中的情况）后，红蓝点数量相同。

但是直接随便选叶子并不一定能给出一个最优解。

显然地，若在某个子树内有一红一蓝、都还需要染黑且无祖先后代关系的点 $u, v$，我们不会将其中任何一个与子树外点配对，配对路径在子树外的情况只会出现在子树内中红蓝点数量不一样的情况，于是离开子树的边的贡献为红蓝点数量之差的绝对值。
### Subtask 2：$m = n$ 即原图为基环树
当那个环是偶环时，我们仍然可以考虑红蓝染色。此时我们也要求红蓝点数量相等。

直接沿用上面的描述方式不太方便，考虑结合题目描述和二分图染色，把题意转化成：

- 一开始红蓝染色。
- 每次可以交换红点和蓝点。
- 求最少操作此时，使得红蓝点恰好完全对调。

非环上点的贡献可以直接沿用 Subtask 1 的做法。当然，利用上面的解释我们可以设 $f_u$ 表示 $u$ 子树内蓝点个数减去红点个数，则这部分的答案为 $\displaystyle\sum_i |f_i|$。

现在考虑环上的点。设 $v_i$ 表示环上第 $i$ 个点，$x_i$ 表示环上第 $i$ 条边把红点 $v_i$ 交换为蓝点 $v_{i \bmod len + 1}$ 的次数为 $x_i$ 或把蓝点交换为红点的次数为 $-x_i$。

则我们可以列出若干形如 $x_i - x_{i \bmod len + 1} = f_{v_i}$ 的方程，解得 $\displaystyle\sum_{i = 1}^{len} |x_i| = \sum_{i = 1}^{len} |x_1 - \displaystyle\sum_{j = 1}^{i - 1} a_{v_j}|$。

这个东西显然等价于到若干定点距离之和的最小值，取中位数即可。

当那个环为奇环时，考虑先删去一条环边。而在对剩下部分染色后，这条边的作用就是改变其相连的都红或都蓝的状态，而它每次可以改变两个点的状态，于是在删边后答案的基础上，若黑白点数量不同并不一定无解，而是可能可以通过再操作若干次这条边达成目标。

综上，时间复杂度视实现为 $O(n)$ 或 $O(n \log n)$。

代码：
```cpp
#include <iostream>
#include <algorithm>
#include <cstdlib>

using namespace std;

typedef long long ll;

typedef struct {
	int nxt;
	int end;
} Edge;

int cnt = 0;
int root[100007], head[100007], fa[100007], depth[100007], val[100007], bucket[100007];
ll sum[100007];
bool vis[100007], loop[100007];
Edge edge[200007];

inline void init(int n){
	for (int i = 1; i <= n; i++){
		root[i] = i;
	}
}

int get_root(int x){
	if (root[x] == x) return x;
	return root[x] = get_root(root[x]);
}

inline bool merge(int x, int y){
	int x_root = get_root(x), y_root = get_root(y);
	if (x_root == y_root) return false;
	root[x_root] = y_root;
	return true;
}

inline void add_edge(int start, int end){
	cnt++;
	edge[cnt].nxt = head[start];
	head[start] = cnt;
	edge[cnt].end = end;
}

void dfs1(int u, int father){
	fa[u] = father;
	depth[u] = depth[father] + 1;
	vis[u] = !vis[father];
	if (!vis[u]){
		val[u] = -1;
	} else {
		val[u] = 1;
	}
	for (int i = head[u]; i != 0; i = edge[i].nxt){
		int x = edge[i].end;
		if (x != father) dfs1(x, u);
	}
}

void dfs2(int u){
	sum[u] = val[u];
	for (int i = head[u]; i != 0; i = edge[i].nxt){
		int x = edge[i].end;
		if (x != fa[u]){
			dfs2(x);
			sum[u] += sum[x];
		}
	}
}

int main(){
	int n, m;
	cin >> n >> m;
	if (n % 2 == 1){
		cout << -1;
		return 0;
	}
	int loopu = -1, loopv = -1, root, sumr = 0;
	init(n);
	for (int i = 1; i <= m; i++){
		int u, v;
		cin >> u >> v;
		if (!merge(u, v)){
			loopu = u;
			loopv = v;
		} else {
			add_edge(u, v);
			add_edge(v, u);
		}
	}
	if (loopu == -1){
		root = 1;
	} else {
		root = loopu;
	}
	dfs1(root, 0);
	for (int i = 1; i <= n; i++){
		sumr += val[i];
	}
	if (sumr % 2 != 0){
		cout << -1;
		return 0;
	}
	ll ans = 0;
	if (sumr != 0){
		if (loopu != -1 && loopv != -1 && val[loopu] == val[loopv]){
			sumr /= 2;
			val[loopu] -= sumr;
			val[loopv] -= sumr;
			ans += abs(sumr);
		} else {
			cout << -1;
			return 0;
		}
	}
	dfs2(root);
	if (loopu != -1 && loopv != -1 && val[loopu] != val[loopv]){
		int cnt = 0, mid;
		bucket[++cnt] = 0;
		if (depth[loopu] < depth[loopv]) swap(loopu, loopv);
		while (depth[loopu] > depth[loopv]){
			bucket[++cnt] = sum[loopu];
			loop[loopu] = true;
			loopu = fa[loopu];
		}
		sort(bucket + 1, bucket + cnt + 1);
		mid = bucket[(cnt + 1) / 2];
		for (int i = 1; i <= cnt; i++){
			ans += abs(bucket[i] - mid);
		}
	}
	for (int i = 1; i <= n; i++){
		if (!loop[i]) ans += abs(sum[i]);
	}
	cout << ans;
	return 0;
}
```

---

## 作者：Arson1st (赞：2)

## [[AGC004F] Namori](https://www.luogu.com.cn/problem/AT_agc004_f) 题解

## 基环树DP

一种模拟赛场上想到的基环树 DP 做法：

- ### 树

	我们先发扬人类智慧，观察下面几种情况：

	![](https://cdn.luogu.com.cn/upload/image_hosting/q81adxwf.png)

	首先，点都是成对变色的，所以点数为奇时一定无解。对于图一这种链，自然是从叶子开始两两配对最优。同样地，对于图二，儿子也应且只应与父亲配对。明显点 $6,7$ 只能通过与点 $5$ 配对变色。但是点 $5,6$ 配对变色后又需要点 $4$ 先变作黑色，再与点 $5$ 一同变回白色才能让点 $5,7$ 继续配对，以此类推……可以证明这种策略一定最优，耗费的步数最少。继而我们马上会发现第二种无解情况：如果没有点 $8,9$，右图自然无解。

	我们抽象出模型，深刻剖析一下这个配对过程，可以考虑设计状态：$b_u$ 表示点 $u$ 需要被染成黑色 $b_u$ 次后合法，$w_u$ 表示点 $u$ 需要被染成白色 $w_u$ 次后合法。明显初始时 $b=1,w=0$。考虑现在搜索到了节点 $u$：

	**首先，答案应该先加上 $\displaystyle\sum_{v\in son(u)} (b_v+w_v)$。**

	因为我们要首先保证在向上回溯时子树内不能存在有不合法的点。这里先不考虑最后能否做到完成每次变色的问题，先假定我们一定有办法使当前 $u,v$ 两点变色的条件成立。

	而我们知道父子节点一定要颜色相等才能与子节点一起完成一次染色——如果 $v$ 要被染上 $b_v$ 次黑色，那么 $u$ 要相应地先被染上 $b_v$ 次白色才行，反之亦然（参考上例）。

	**所以有转移 $w_u\overset{+}{\gets} b_v,w_v\overset{+}{\gets} b_v$。**

	现在再处理点 $u$ 上堆积的 $w_u,b_u$。沿用上例，这里模拟对点 $4$ 的处理：现在 $b_4=1+w_5=2,w_4=b_8+b_9=2$。自然，根据我们的策略，它们是会相互抵消的。这里我们同时可以发现，如果在根节点能抵消为 $0$，一定可以成立。否则就属于之前说的第二种非法情况，返回 $-1$。

- ### 基环树

	有了树的基础，我们可以考虑对挂在环上的树 DP 一遍。那些点的贡献是一定的。对于环，因为转移方向不确定，我们再单独处理。
    ![](https://cdn.luogu.com.cn/upload/image_hosting/u6835s7r.png)

	为了方便，我们接下来在处理环上的点的 $b,w$ 值抵消时先求出 $a=b-w$ 以方便的用 $a$ 的正负及绝对值表示该点抵消后还需要变成黑/白色几次。并且我们先 **钦定环的起点和终点**，这样环上的点之间的转移也可以直接写为 $a_u\overset{-}{\gets}a_v(u,v\in ring)$。还剩下需统计的贡献就是 $\displaystyle\sum_{u\in ring}|a_u|$。

	- #### 偶环

		对于有解的情况（$a_1=0$），考虑加入边后的贡献：点 $ed$ 有了新的转移方向——点 $st$。那么我们设其向 $st$ 转移了 $w$（原本是 $ed,ed-1$ 组队的 $w$ 次变黑色变成 $ed,st$ 组队的 $w$ 次变黑色）。在使用了 $w$ 次变黑操作后，对于两点原来的指标，$a_{ed}\overset{-}{\gets}w,a_{st}\overset{-}{\gets}w$。所以 $a$ 的变化情况为 $a_{st}-w+w,a'-w,\cdots,a''+w,a_{ed}-w$（这里理解一下，为了帮助 $ed$ 变黑，$st$ 先要变白 $w$ 次，$a_{st}\overset{-}{\gets}w$，而后又因为减去 $a’$ 的贡献时加上了从 $ed$ 传递过来的 $w$，$a_{st}\overset{+}{\gets}w$，最后仍为 $0$ 也自证了情况有解）。为了最后式子好看，可以耍个小聪明，把应该单独加在边上的贡献 $w$ 加回 $a_{st}$：$\Delta=\displaystyle\sum_{i=1}^{i\le sz(ring)}|a_i+(-1)^{i-1}\times w|=\displaystyle\sum_{i=1}^{i\le sz(ring)}|(-1)^i\times a_i-w|$，后面这种形式是典型初中题，显然可以看出 $w$ 等于 **奇位取反** 的 $a$ 数组的中位数最优。

	- #### 奇环

		奇环有一种骚操作——当 $a_{st}\not=0$ 时，你以为一定无解了？不，仍考虑加入边的贡献 $w$ 后的 $a$ 数组： 首先依然先给 $a_{st},a_{ed}$ 的指标都减去 $w$，再计算 $a$ 的变化情况：$a_{st}-w-w,a'+w,\cdots,a''+w,a_{ed}-w$。我们惊奇地发现，要想有解（让$a_{st}-w-w=0$），$a_{st}=0$ 时这条边自然无法产生任何贡献。然而 $a_{st}$ 是偶数时，我们可以令 $w=\displaystyle\frac {a_{st}} {2}$ 从而反使方案有解，妙手回春哪。而同样地，这里也可以 **偶位取反** 从而一律计算 $-w$ 的绝对值作为贡献。

## 后记

可能略显啰嗦，但是我希望通过详尽地表述出自己的思路过程，能分享出这种进度条一点点拉满的快感:)。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5+10;

int n, m, w[N], b[N], hh, tt, f[N], a[N], s[N], aa[N], tot;
bool vis[N], flag;
long long ans;
vector<int> E[N], ring;

void dfs(int u, int fa) {
	for (int v : E[u]) {
		if (v == fa || vis[v]) continue;
		dfs(v, u);
	}
	ans += b[u] + w[u]; b[u] += 1;
	if (w[u] >= b[u]) w[u] -= b[u], b[u] = 0;
	else b[u] -= w[u], w[u] = 0;
	b[fa] += w[u]; w[fa] += b[u];
}

void find(int u, int fa) {
	if (flag) return;
	vis[u] = 1; f[u] = fa;
	for (int v : E[u]) {
		if (flag) return;
		if (v == fa) continue;
		if (vis[v]) tt = u, hh = v, flag = 1;
		else find(v, u);
	}
}

int main() {
	scanf("%d%d", &n, &m);
	if (n & 1) {printf("-1"); return 0;}
	for (int i = 1, u, v; i <= m; i ++) {
		scanf("%d%d", &u, &v);
		E[u].push_back(v); E[v].push_back(u);
	}
	if (m == n-1) {
		dfs(1, 0);
		if (b[1] != w[1]) printf("-1");
		else printf("%lld", ans);
	}
	else {
		find(1, 0); memset(vis, 0, sizeof vis);
		for (int pos = tt; pos != f[hh]; pos = f[pos])
			ring.push_back(pos), vis[pos] = 1;
		for (int i = tt, j = 0; i != f[hh]; j = i, i = f[i]) {
			dfs(i, 0); a[i] = b[i] - w[i] - a[j];
		}
		int now = 1;//固定位取反
		for (int i : ring) a[i] *= now, now *= -1, s[++ tot] = a[i];
		if ((ring.size() & 1) == 0) {
			if (a[hh]) {printf("-1"); return 0;}
			sort(s+1, s+tot+1);	int tmp = s[tot/2];
			for (int pos : ring)
				ans += abs(a[pos] - tmp);
		}
		else {
			if (a[hh] & 1) {printf("-1"); return 0;}
			int tmp = a[hh] >> 1;
			for (int pos : ring)
				ans += abs(a[pos] - tmp);
		}
		printf("%lld", ans);
	}
}
```



---

## 作者：Otomachi_Una_ (赞：2)

b. **[[AGC004F] Namori](https://atcoder.jp/contests/agc004/tasks/agc004_f)（7）**

题目中所给的操作很经典。如果原图是二分图的话，我们把左部点的颜色全部取反，那么一次操作就会变成对一条边交换两端点的颜色。

- 对于树：交换树边两端点的颜色，使其变成另一种形态。这是经典题。假设 $v_i$ 为 $i$ 子树内当前黑点数和目标黑点数的差。那么：
  - 对 $v_i\not = 0$ 无解。
  - 反之，答案是 $|v_1|+|v_2|+|v_3|+\dots+|v_n|$。
- 对于偶环的基环树：我们还是可以按上面染色，只是这次我们在原来的树上两点之间开了一个“便捷通道”。根据上面的经验，我们猜测这个便捷通道也是单向的（也就是只会执行 $\text{swap}(0,1),\text{swap}(1,0)$ 两种操作之一）。假设进行了 $x$ 次 $\text{swap}(0,1)$（如果进行 $\text{swap}(1,0)$ 那么 $x$ 是负的）。那么上面式子当中的 $v_i$ 都可以写成 $x$ 的线性表示，于是我们就变成了关于 $x$ 的多个线性函数绝对值和的最小值问题。取权值中位数即可。
- 对于奇环的基环树：那么我们先拆出来其中的一条边，对剩下的树先进行上述变换。那么拆出来的一条边的作用就是：$(1,1)\to (0,0),(0,0)\to (1,1)$。我们还是猜这玩意单向。那么这次它的使用次数是固定的了（$\dfrac{原来1个数-目标1个数}{2}$）。那么我们把它所带来的 $0$（或者 $1$）丢到它两个端电上在跑 $\sum |v_i|$ 即可。

[submission](https://atcoder.jp/contests/agc004/submissions/42203843)

---

## 作者：_Z_F_R_ (赞：2)

[更好的阅读体验？](https://www.cnblogs.com/IncludeZFR/p/18395642)

感谢 @[Oier_szc](https://www.luogu.com.cn/user/368204) 的建议。

---

以下将把某个点的颜色变为相反的颜色，称之为把颜色**取反**。
## 1 树
先看树的部分分，直接做不那么直观，因为树是二分图，可以考虑把树黑白染色，还是看官解里的图：

![](https://cdn.luogu.com.cn/upload/image_hosting/hck2n144.png)

这是转化之前样例一的染色方案。

![](https://cdn.luogu.com.cn/upload/image_hosting/omu5invb.png)

这是转化之后样例一的染色方案。简单来说，就是按二分图的染色方式，将二分图被染成黑点的点的初始颜色**取反**，变成黑色，这样目标状态中，二分图被染成黑点的点的颜色也应被**取反**，变成白色。此时，限制条件由“两个点颜色**相同**”，变成了“两个点颜色**不同**”，由于条件的转换，我们可以把“将两点颜色取反”，变为“**交换**两点的颜色”。

梳理一下转化后的题意：
- 给定一个被二分图染色后的树，每次可以交换一条边两个不同颜色的点的颜色，使得最终的树是原树中所有点的颜色被取反后形成的树，求最小操作次数。

现在我们就可以直接得到，一棵树无解的充要条件是：将这棵树二分图黑白染色后，黑白点个数不相等。

进一步的，考虑对于一棵子树，假设其白点数量为 $a$，黑点数量为 $b$，那么，因为其目标状态为，其白点数量为 $b$，黑点数量为 $a$，且一次操作最多可以是黑点与白点的差加 $2$ 或减 $2$，因此，发生在这棵子树的根连向其父亲的边上的交换操作至少为 $|a - b|$ 次。

因此答案的下界为一棵树所有子树的黑白点数量之差，我们来大致证明一下操作数能达到这个下界。

我们考虑对于一条边 $e = (u, v)$，如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/tlj609qv.png)

假设 $u$ 点一侧的子树与 $v$ 点一侧的子树，均满足黑白点数量已经与目标的黑白点数量相同，我们称此时边 $e$ 处于平衡状态。

如果黑色的 $A$ 点要按红色路径转移到白色的 $B$ 点，因为这样打破了边 $e$ 的平衡状态，必然存在黑色的 $C$ 点要按蓝色路径转移到白色的 $D$ 点。

那么这样显然劣于黑色的 $A$ 点按黄色路径转移到白色的 $D$ 点，黑色的 $C$ 点按绿色路径转移到白色的 $B$ 点。

所以，我们得到结论，若 $e$ 处于平衡状态，那么可以直接断开 $e$，将原树划分成两颗子树，递归的解决问题，因此，这种处于平衡状态的边对答案没有影响。

再考虑不处于平衡状态的边，我们发现，对于一个边 $e = (u, v)$ 上的交换操作，假设 $u$ 侧缺黑点，$v$ 侧多出了一些黑点。那么只有将黑点从 $v$ 点转移到 $u$ 才是不劣的，因此我们可以尝试对每一条边定向，表示黑点怎样转移才是优的，如下图所示（用双向边表示处于平衡状态的边）。

![](https://cdn.luogu.com.cn/upload/image_hosting/m9phuc0o.png)

我们若想达到操作次数的下界，那么一定是将黑点向箭头方向移动，直到所有边都是平衡状态。

但是，假设出现了以下两种情况（$B, C, D, ...$ 处表示的是一棵子树，而不是一个结点）：

![](https://cdn.luogu.com.cn/upload/image_hosting/wbktwhtk.png)

$A$ 处为白点，且以 $A$ 点为端点的边都不指向 $A$ 点，那么 $A$ 处的黑点就转移不出去了。

![](https://cdn.luogu.com.cn/upload/image_hosting/qzikf1vt.png)

$A$ 处为黑点，且以 $A$ 点为端点的边都指向 $A$ 点，那么从 $B, C, D, ...$ 处的黑点就转移不到其他地方了（相当于 $A$ 处的黑点把路“堵住”了）。

这样看起来都达不到下界，但是我们可以证明两种情况均是不存在的。
> 证明：第一种情况中 $B, C, D, ...$ 处都缺黑点，即黑点个数小于白点个数，而 $A$ 点为白点，如果它的目标状态是黑点，那它也可以视为缺黑点，反之它不缺点，所以整棵树缺黑点，即黑点个数小于白点个数，无解，第二种情况同理。

通过以上结论，我们可以发现，边被定向后，整棵树大致构成一个 DAG，且 DAG 的若干个源点处一定是黑点，汇点处一定是白点，所以黑点只要沿 DAG 的方向流动，操作数一定能达到下界。

因此，我们大致证明了，总存在一种合法的方案使得答案能达到下界。

对每条边进行计数即可，具体实现中，可以将黑点权值设为 $1$，白点权值设为 $-1$，再统计每个子树权值和的绝对值之和。
## 2 基环树且环为偶环
注意到图仍是二分图。所以这种情况下无解的情况与树相同。

通过上面的结论，我们也可以把所有不在环上的边定向，同时，我们对环上的点赋一个权值 $val$，表示将黑点权值设为 $1$，白点权值设为 $-1$，该子树所有结点权值和。

如果对树的做法理解透彻，你会发现每个子树的权值和，其实是由子树的根结点连向其父亲结点的边的有向权值。

这里“有向”的意思是，由子树的根结点的父亲结点连向它本身的边的有向权值，是由子树的根结点连向其父亲结点的边的有向权值的相反数，具体的，我们可以定义，由 $u$ 连向 $v$ 的有向权值 $val$，表示必须要由 $u$ 向 $v$ 输送 $val$ 个黑点（$val > 0$），或是必须要由 $v$ 向 $u$ 输送 $-val$ 个黑点（$val < 0$），才能使这条边达到平衡状态。

这样，我们可以假设，环上的点依次是 $p_1, p_2, \dots, p_k$，$p_i$ 的权值为 $a_i$，由 $p_i$ 连向 $p_{i \bmod k + 1}$ 的边的有向权值为 $y_i$。
这样，我们可以得到：
$$a_i + y_{(i - 2 + k) \bmod k + 1} - y_i = 0.$$
令 $x_i = -y_{(i - 2 + k) \bmod k + 1}$，得到：
$$a_i - x_i + x_{i + 1} = 0$$
也即：
$$\begin{cases}
x_1 - x_2 = a_1 \\
x_2 - x_3 = a_2 \\
\cdots \\
x_k - x_1 = a_k
\end{cases}$$
显然这个方程没有唯一解（例如，可以令 $x_i' = x_i + t$ 得到一组新解）。

我们的目标是最小化 $\sum_{i = 1}^k |x_i|$。注意到：
$$
\begin{cases}
x_1 = x_1 - 0 \\
x_2 = x_1 - a_1 \\
x_3 = x_2 - a_1 = x_1 - (a_1 + a_2) \\
\cdots \\
x_k = x_1 - \sum_{i = 1}^{k - 1} a_i
\end{cases}
$$
因此：
$$\sum_{i = 1}^k |x_i| = \sum_{i = 0}^{k - 1}
|x_1 - \sum_{j = 1}^i a_j|$$
问题转化为，在数轴上标出 $0$，$a_1$，$a_1 + a_2$，$\sum_{i = 0}^{k - 1} a_i$ 这 $k$ 个点，我们现在要找到一个点 $x_1$，使得 $x_1$ 到其它 $k$ 个点的距离和最短。这是一个经典问题，当 $x_1$ 取所有数的中位数时，总距离最小。

因此在求出环外各边权值的绝对值之和后，计算环上各边的权值，按上述步骤求处环上边的最小权值和即可。
## 3 基环树且环为奇环
对于奇环的情况，考虑断掉环上的一条边后，整个图变成了一棵树，我们仍然对这棵树黑白染色，则该断掉的边的两个端点同色。

因此，这一条边的作用即为，当该边的两个端点颜色**相同**时，将两个端点的颜色取反。

这样，我们可以不断生成 $2$ 个黑点或白点，这种情况下，黑点与白点的差值只会加 $2$ 或减 $2$，同时，我们的目标是让原图中所有点的颜色被取反。

所以，我们得到了这种情况下，无解的充要条件是：在断掉环上的一条边并对这棵树黑白染色后，黑白点个数奇偶性相同，当然，这与“$N$ 为偶数”这一条件是等价的。

由树的情况，我们可以证明，这一条边只能不断生成黑点或不断生成白点（具体的，考虑这种情况是答案的下界，可以先把答案加上生成次数，再在这个结点上叠若干个黑点或白点，发现叠黑点的情况可以使树中的两个结论都成立）。

因此令 $x$ 为黑点个数减白点个数，则整棵树的权值和为 $x$，先将答案加上 $\frac{|x|}{2}$，然后叠黑点或白点，即将两个点的权值减去 $\frac{x}{2}$（注意整棵基环树的权值和为 $0$ 时，我们才能恰好补齐黑点或白点并把边割掉转化为树，原因在于，注意到我们每次加黑点或者白点，不仅加上了两个被生成的点的权值，还减去了两个被替换的异色点的权值，而在原树中我们并没有减去这些被替换点的贡献，这与被生成的点的权值恰好相抵消），再跑树的做法即可。

（想不到更好的讲法，若有请告知 QwQ）
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll Read() {
	int sig = 1;
	ll num = 0;
	char c = getchar();
	while(!isdigit(c)) {
		if(c == '-') {
			sig = -1;
		}
		c = getchar();
	}
	while(isdigit(c)) {
		num = (num << 3) + (num << 1) + (c ^ 48);
		c = getchar();
	}
	return num * sig;
}
void Write(ll x) {
	if(x < 0) {
		putchar('-');
		x = -x;
	}
	if(x >= 10) {
		Write(x / 10);
	}
	putchar((x % 10) ^ 48);
}

const int N = 100005;
int n;
bool col[N];
vector<int> e[N];
ll ans = 0, val[N];
void Dfs(int u, int fa, bool pcol) {
	col[u] = !pcol;
	for(auto v : e[u]) {
		if(v == fa) {
			continue;
		}
		Dfs(v, u, col[u]);
	}
}
ll Dfs2(int u, int fa) {
	ll res = val[u];
	for(auto v : e[u]) {
		if(v == fa) {
			continue;
		}
		res += Dfs2(v, u);
	}
	ans += abs(res);
	return res;
}
vector<int> st;
bool vis[N], c[N], suc = false;
int cnt = 0;
vector<int> cir;
void Dfs3(int u, int fa) {
	st.emplace_back(u);
	vis[u] = true;
	for(auto v : e[u]) {
		if(v == fa) {
			continue;
		}
		if(vis[v]) {
			if(!suc) {
				suc = true;
				bool b = false;
				for(auto x : st) {
					if(x == v) {
						b = true;
					}
					c[x] = b, cnt += b;
					if(b) {
						cir.emplace_back(x);
					}
				}
			}
			continue;
		}
		Dfs3(v, u);
	}
	st.pop_back();
}
void Dfs4(int u, bool pcol) {
	col[u] = !pcol, vis[u] = true;
	for(auto v : e[u]) {
		if(vis[v]) {
			continue;
		}
		Dfs4(v, col[u]);
	}
}
ll Dfs5(int u, int fa) {
	ll res = col[u] ? 1 : -1;
	for(auto v : e[u]) {
		if(v == fa || c[v]) {
			continue;
		}
		res += Dfs5(v, u);
	}
	ans += abs(res);
	return res;
}
int main() {
	int i, m;
	n = Read(), m = Read();
	for(i = 1; i <= m; i++) {
		int u = Read(), v = Read();
		e[u].emplace_back(v), e[v].emplace_back(u);
	}
	if(m == n - 1) {
		Dfs(1, 0, false);
		int sum = 0, i;
		for(i = 1; i <= n; i++) {
			sum += col[i];
			val[i] = col[i] ? 1 : -1;
		}
		if(sum * 2 != n) {
			printf("-1");
			return 0;
		}
		Dfs2(1, 0);
		Write(ans);
		return 0;
	}
	Dfs3(1, 0);
	if(cnt & 1) {
		int u, v;
		for(i = 1; i <= n; i++) {
			if(c[i]) {
				u = i;
				break;
			}
		}
		for(auto x : e[u]) {
			if(c[x]) {
				v = x;
				break;
			}
		}
		for(i = 0; i < e[u].size(); i++) {
			if(e[u][i] == v) {
				break;
			}
		}
		e[u].erase(e[u].begin() + i);
		for(i = 0; i < e[v].size(); i++) {
			if(e[v][i] == u) {
				break;
			}
		}
		e[v].erase(e[v].begin() + i);
		Dfs(1, 0, false);
		int sum = 0, i;
		for(i = 1; i <= n; i++) {
			sum += col[i];
			val[i] = col[i] ? 1 : -1;
		}
		if(n & 1) {
			printf("-1");
			return 0;
		}
		ll x = n / 2 - sum;
		val[u] += x, val[v] += x;
		Dfs2(1, 0);
		Write(ans + abs(x));
	}
	else {
		memset(vis, 0, sizeof(vis));
		Dfs4(1, false);
		int sum = 0;
		for(i = 1; i <= n; i++) {
			sum += col[i];
			val[i] = col[i] ? 1 : -1;
		}
		if(sum * 2 != n) {
			printf("-1");
			return 0;
		}
		memset(vis, 0, sizeof(vis));
		vector<ll> vec;
		for(auto v : cir) {
			ll x = Dfs5(v, 0);
			vec.emplace_back(x), ans -= abs(x);
		}
		for(i = 1; i < vec.size(); i++) { // \sum val_i = 0
			vec[i] += vec[i - 1];
		}
		sort(vec.begin(), vec.end());
		ll x = vec[vec.size() / 2];
		for(auto v : vec) {
			ans += abs(x - v);
		}
		Write(ans);
	}
	return 0;
}
```

---

## 作者：Z1qqurat (赞：1)

神仙题。

首先发现 $n - 1 \le m \le n$，所以要么是树要么是基环树。一般树会好做一些，先考虑树的情况怎么做。

### 树

首先你要知道，树是一个二分图。由于每次交换颜色要求**交换两个同色棋子**，我们将其转化为一个经典模型：给树做二分图黑白染色，每个黑点上有一个球，我们每次可以将球移向一个相邻的没有球的位置，现在目标是将所有球都移到白点上面，求最少的移动次数。（这谁想得到啊？？？）

那考虑这个问题怎么做。我们设 $sum_u$ 表示 $u$ 的子树内黑点数与白点数之差，这里我们设黑点权值为 $1$，白点权值为 $-1$，那么 $sum_u$ 实际上就是一个子树求和。现在我们将移动次数拆到每一条边上来看，考虑计算 $u$ 到其父亲 $f$ 的这条边的贡献。如果我们的子树内有黑点有白点，那我们就尽量让子树内的黑白点匹配，这样它们 不需要经过 $(u, f)$，只有 $|sum_u|$ 个黑（白）点需要到 $u$ 子树外去和别的点匹配。所以我们就会有 $|sum_u|$ 个点需要经过 $(u, f)$，即边 $(u, f)$ 对移动次数的贡献就是 $|sum_u|$。于是乎，我们做一个 dfs 子树求和就可以了，最后答案是 $\sum\limits_{i = 1}^{n} |sum_i|$。

需要注意的是，如果 $sum_{root} \ne 0$，那么无解（也就相当于二分图的左右部点数不相等，那必然没有完美匹配一样）。

### 偶环

接下来就是基环树的情况了。基环树，我们就把环扯下来，子树挂在环的节点上。那么我们子树内仍然可以按照树的做法求出 $sum_u$，只是现在我们得解决一个环上的问题了。我们先把环求出来，设环顶为 $st$，环底为 $ed$，将 $st$ 作为树根。

首先考虑偶环。偶环仍然是一个二分图，所以我们考虑先**断环为链**。

![](https://pic.imgdb.cn/item/64f67427661c6c8e5485a43f.png)

考虑这条红边的贡献。我们记 $sum_i$ 为环上第 $i$ 个点的子树和，环长为 $l$。我们每次将一个点通过红边转移，因为红边两侧点颜色不同，相当于使左侧所有的 $sum_i$ 减去 $1$，右侧的所有 $sum_i$ 加上 $1$。并且操作次数 $+1$。而我们想要最小化 $\sum\limits_{i = 1}^{l} |sum_i|$，关键在于求这条红边的贡献 $w$。发现绝对值的东西相当于数轴上一些点向一个点的距离之和，于是 $w$ 取 $sum_i$ 的中位数即可。

注意当 $sum_{st} \ne 0$ 时无解。

### 奇环

奇环和偶环的不同之处就在于红边两侧的点颜色不同了，所以在红边上转移一个点相当于使得环上的黑白点数差减 $2$。那么我们为了使黑白点数量相等，给每个环上的 $sum_i$ 减去 $sum_{st}$ 的一半即可。

注意 $sum_{st}$ 为奇数的时候无解。

### 代码细节

那实现起来就没有什么难度了。先求出 $sum_i$，对于偶环求中位数并让环上所有 $sum_i$ 减去 $sum_{mid}$；对于奇环让 $sum_i$ 减去 $\frac{sum_{st}}{2}$。最后把求出 $\sum\limits_{i = 1}^{n} |sum_i|$，当然，要对每种情况进行无解的判定。由于代码写丑了所以不放出来。



---

## 作者：win114514 (赞：1)

[更好的阅读体验](https://www.cnblogs.com/Al-lA/p/17642031.html)。

这里给出一种与其他题解完全不同的实现方式。

### 思路

发现图要么是一棵树，要么是一颗基环树。

#### 树

我们首先考虑树如何操作。

我们可以 $\text{dfs}$ 这颗树。

对于每个点维护一个 $w,h$，表示这个点想要变成白色 $w$ 次，想要变成黑色 $h$ 次。

容易发现每个点最初状态都为 $w=0,h=1$。

我们一次往上合并。

对于一个点，我们合并都向它的父亲合并这个信息。

由于我们是从叶子节点往上推，所以一个点只会与他的父亲进行操作。

可以发现，若一个点想要变成黑色 $h$ 次，那么必然要它的父亲变白 $h$ 次。

同理，若一个点想要变成白色 $w$ 次，那么必然要它的父亲变黑 $w$ 次。

这样就可以往上转移。

再考虑消取一些情况。

一个点可以变黑的条件是它需要为白色。

一个点可以变白的条件是它需要为黑色。

那么这高速了我们，想要变黑色的数量可以与变白色的数量相互抵消。

抵消后，$w,h$ 只有一个变量有值，我们把他统计到答案中去。

容易得知，无解的情况便是到达了根节点 $w,h$ 还不为 $0$。

这就表示不能完全清空。

#### 基环树

考虑从树的做法拓展到基环树。

我们将环上的一条边提取出来，就又变成了一条边和一棵树。

由于我们将这条边要么染白 $k$ 次，要么染黑 $k$ 次。

那么我们可以现将其染白一次看一看是什么情况。

对应到树上就是两个点 $w=k-1,h=0$，其中若是染黑则 $k$ 为负数。

可以发现，我们若是改变两个点 $w$ 的值，最终对应到答案上要么是两个值抵消，要么是一起加在了根上。

这又启示了我们，更改 $k$ 要么是无解变为有解，要么从有解变为更优解。

1. 无解变为有解。

	我们可以将 $k=0$，与 $k=1$ 进行对比，若是根 $w,h$ 变了，那么我们只需要将 $k$ 赋为一个可以将其消为 $0$ 的值即可。
    
2. 有解变为更优解

	很容易猜测到，$k$ 的取值与答案会构成一个单峰函数，那么我们直接三分解决即可。
    
从上文可以看出，这个做法的思维含量较低，主要是通过观察答案性质解决。

无需从环的长度以及大量的数学去推导。

缺点可能是由于需要 $\text{dfs}$ 很多次，可能常数较大。

### Code

[AC记录](https://atcoder.jp/contests/agc004/submissions/44693925)。

---

## 作者：H_W_Y (赞：0)

很好的一道题啊，思路非常精妙。

（此题解参考了多篇其他的题解，笔者一直没有理解 **奇环** 的情况，豁然开朗后写了这一篇题解）。



容易发现题目中分成了两个部分，树和 **基环树**。

对于这类型的题目我们先考虑树的情况如何完成。



------------



首先，题目中每次改变相同两个点的颜色是非常不好维护的，

而对于树，本来就是一个 **二分图**，我们为什么不先黑白染色然后来做呢？

于是黑白染色之后，每一次操作就变成了 **移动一个黑点**（这里就可以把黑点看成棋子，白点看成空地）。

画个图就是这个样子：

![](https://cdn.luogu.com.cn/upload/image_hosting/riq5n38z.png?x-oss-process=image)



每一次操作我们就是交换相邻的黑白两个点（说白了就是移动黑点），

而最后的目标也是很清楚的，就是 **让所有黑点到原本白点的位置**。



于是我们就很容易得到一个条件——黑白个数一定要相等（不然你不可能达到最终的目标啊），

上图很明显就是一种 **不合法** 的情况。



------------


这样染色之后我们考虑一种类似于树形 dp 的做法。

一棵子树内（假设根为 $u$，其父亲节点为 $fa$），白点个数是一定的，那么它能在内部达到目标 **当且仅当黑点个数 = 白点个数**，

但一定存在有些子树会出现 **黑点多一点/少一点** 的情况，

而为了达成目标，我们这些 **多/少** 的黑点就要通过 $fa \to u$ 的这条边 **送出去** 或者 **运进来**，

那么其实这条边的操作次数是一定的，也就是 $|c_{白}-c_{黑}|$（其他的调整所用到的边都可以在子树内解决），

于是最后的答案就是这些贡献的和。



具体实现的时候我们令黑色是 $-1$，白色是 $1$，

那么我们只需要维护一个子树和 $a_u$ 就可以了，最后的答案就是 $a$ 数组的 **绝对值** 之和。



------------


现在来考虑基环树的情况。

对于 **偶环** 的情况，

不在环上面的点我们可以照样搞（把环看作根），

由于这还是一个二分图，如果 $a_{rt} \neq 0$，那么还是无解的，

而有解的情况相当于在环上面合理安排分配方式使得移动的次数尽可能小。



如何求得这个次数？

我们设环长为 $m$，$A_i$ 表示以 $i$ 为根，对于不在环上的那些点的 $a$ 值，$x_i$ 表示第 $i$ 个点的流量（有正负，代表方向）。

而流量一定是平衡的，所以我们可以得到这个方程组：
$$
\begin{cases}
x_1 - x_2 = A_1\\
x_2 - x_3 = A_2\\
\dots\\
x_m - x_1 = A_m
\end{cases}
$$
我们的目的是最小化 $\sum_{i=1}^m |x_i|$，所以把它整理一下就是：
$$
\begin{cases}
x_1 = x_1 - 0\\
x_2 = x_1 - A_1\\
x_3 = x_1 - A_1 - A_2 \\
\dots\\
x_m = x_1 - \sum_{i=1}^{m-1} A_i
\end{cases}
$$
而这里 $\sum A_i$ 其实就是原树上面的 $a$，

对于这个式子，就是经典的 **小学奥数** 问题，直接去这里 $a$ 的中位数就可以了，

接着我们把环上面的 $a$ 值统一减去得到的这个中位数再统计答案就可以了。

（这一部分大多数题解都是讲得比较清楚的）



------------


而最后一部分就是最难理解的一部分——**奇环**！

简单画个图可以发现这个东西实际上染色之后不是 **二分图**，而会有两个颜色相同的点。

稍微画一下图就可以发现（而且你随便让一个点为根去染色很有可能根本不会让黑白色相等，但是这样有可能依然有解！）。

![B2](https://cdn.luogu.com.cn/upload/image_hosting/3y2hxeke.png?x-oss-process=image)

强烈建议手玩这个样例！


我们发现图中一共有 $6$ 个白点但是只有 $4$ 个黑点，这直接做很明显根本无法满足条件，

那怎么办呢？（建议回到没有转化前手玩出一种方案再放到转化后来做）


发现对于这两个相邻的黑点，它的用处不小，它是可以生成黑点的！

因为我们的黑点不够，而又要填到这些位置，所以我们必须加入一些黑点来补全它（不管你加多少，初始的白点位置是不会变的，也就是目标位置）。

怎么生成的呢？

我们考虑对于相邻的那两个黑点，把它移走之后就成了这个样子。

![B3](https://cdn.luogu.com.cn/upload/image_hosting/0mvm4gz5.png?x-oss-process=image)



这个时候由于你没有黑点可以移动了，

那么再过程中这两个点就会各生成一个黑点，

就变成了这样：

![B4](https://cdn.luogu.com.cn/upload/image_hosting/7zmv3mtm.png?x-oss-process=image)

不要被现在的白点所误导，我们的目标位置还是原来的位置，就是图中红圈中的点。

而这样直接跑树的做法就可以算出答案了。



怎么实现呢？

发现其实就是让这两个点源源不断地生成黑点，

也就是加大这两个点的权值不就可以了（就是在这个点上面叠放了很多个黑点），

假设这棵树的黑白点之差是 $delta$，

那么我们把那两个黑点的权值 $+\frac{delta}{2}$ 就可以了（也可以在跑完之后再把环上面的都加上）。

这样就做完了。



------------


代码是好写的。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define pb push_back

const int N=1e5+5;
int n,m,a[N],fa[N],rt,ed,f[N],b[N],c=0,ans=0;
vector<int> g[N];

int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}

void dfs(int u,int op){
	a[u]=op;
	for(auto v:g[u]) if(v!=f[u]) f[v]=u,dfs(v,-op),a[u]+=a[v];
}

int main(){
	freopen("color.in","r",stdin);
	freopen("color.out","w",stdout);
  ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
  cin>>n>>m;rt=ed=1;
  for(int i=1;i<=n;i++) fa[i]=i;
  for(int i=1,u,v;i<=m;i++){
  	cin>>u>>v;
  	if(find(u)==find(v)) rt=u,ed=v;
  	else g[u].pb(v),g[v].pb(u),fa[find(u)]=find(v);
  }
  dfs(rt,1);
  if(n==m){
  	for(int i=ed;i;i=f[i]) b[++c]=a[i];
  	if(c&1){
  		if(a[rt]&1) cout<<"-1",exit(0);
  		for(int i=ed;i;i=f[i]) a[i]-=a[rt]>>1;
  	}else{
  		if(a[rt]) cout<<"-1",exit(0);
  		sort(b+1,b+c+1);
  		for(int i=ed;i;i=f[i]) a[i]-=b[c>>1];
  	}
  }else if(a[rt]) cout<<"-1",exit(0);
  for(int i=1;i<=n;i++) ans+=abs(a[i]);
  cout<<ans;
  return 0;
}
```



------------


我们发现当一种染色方案使得黑白的个数相等时，

基环树 **奇环** 的问题就可以被转化成普通树的问题，

是否一定存在这样一种方案呢？

我没有细想，但是如果存在，就一定可以用 $\mathcal O(n)$ 的时间直接找到这个根节点（直接维护一下每个不在环上子树的 $a$ 值就可以了），

那么就不要去考虑奇环的情况了。

~~这个东西似乎可以被出成模拟赛，但感觉难度不够。~~

---

## 作者：phigy (赞：0)

我们考虑形如 `OXXXXO` 的两个白点，可以 `OOOXXO` `XXOXXO` `XXOOOO` `XXXXOO` `XXXXXX` 的消掉。

具体的两个距离为奇数白点可以花费这个距离的代价消掉。

注意到如果中间有白点可能会认为消不了所以有顺序问题。

但是这个可以通过以下构造解决。

我们考虑树的情况（以 $1$ 为根），一个点的子树内的白点肯定是在子树内尽可能消最优，所以子树最后只会剩下一些没能消掉的点，它们以后再怎么消，路径都经过了这个点，所以到这个点的路径提前算到答案里，我们现在只要把点数作为经过这条到他父亲的边的贡献算答案里即可。

具体的我们计 $f_{u}=1-\sum f_v$，答案就是 $\sum |f|$。

注意到我们最后要全部消完，所以 $f_1=0$。

由于我们在消的时候优先消除深度高的，这样就不会有顺序问题。

我们再考虑基环树的情况，容易发现环为偶数时最优的匹配一定可以不覆盖环上的所有边，所以我们可以尝试断开环上的边再做上述事情。

具体的，我们提前求出环上面每个点不包含环的子树对答案的贡献以及自身的 $f$，我们将环上的点的 $f$ 记为 $a_1\sim a_n$ （此 $n$ 为环长）。如果 $n$ 为偶数，必须有 $\sum_{i=1}^n (-1)^ia_i=0$ 才有解，并且当我们断开 $i-1\rightarrow i$ 之间的边后，这棵树的答案就是提前算好的贡献加上 $\sum_{j=1}^n |\sum_{k=0}^{j-1} (-1)^k a_{(i+k-1)\mod n+1}|$。

我们要找到这个使这个式子最小的 $i$。

注意这个式子从 $i=p$ 到 $i=p+1$ 时的变化。

$$|a_1|+|a_1+(-a_2)|+|a_1+(-a_2)+a_3|+|a_1+(-a_2)+a_3+(-a_4)|$$

$$|(-a_2)|+|(-a_2)+a_3|+|(-a_2)+a_3+(-a_4)|+|(-a_2)+a_3+(-a_4)+a_1|$$

因为这个东西的最后一项等于 $0$，所以相当于给每一项的绝对值里面 $-a_1$。

下一次就是 $-(a_2)$ 然后是 $-a_3$ 以此类推。

我们可以直接做一棵权值线段树维护绝对值里面的值以及他们和真实值的整体偏移量即可维护绝对值和，但是过于笨重了，我们考虑转化。

这就相当于求 $\min\{|a_1-X|+|a_1+(-a_2)-X|+|a_1+(-a_2)+a_3-X|+|a_1+(-a_2)+a_3+(-a_4)-X|\}$ 的最小值，其中 $X=a_1,a_1+(-a_2),a_1+(-a_2)+a_3,a_1+(-a_2)+a_3+(-a_4)$。

这个东西就是典型的数轴上 $X$ 到一些点的距离和，而且 $X$ 只能为这些点中的一个，显然取中位数最优。

接下来我们考虑环长为奇数的情况，此时环上一定有一条边没有被经过的结论不再正确，我们考虑对 $a$ 再做一次转化。

我们现在实际上就是每次能使环上相邻的两个 $a$ 同时 $+1/-1$ 代价为 $1$，然后用最少的代价把 $a$ 均变为 $0$。

注意到这个操作是没有先后的，假如我们对 $n\rightarrow 1$ 这条边进行完操作，我们就可以将这条边断开，然后做刚刚的事情了。

注意到此时如果要有解就必须有 $\sum_{i=1}^n (-1)^ia_i=0$，只有 $n\rightarrow 1$ 这条边可以改变左式的值，所以我们看能否使这个式子成立，然后直接做即可。 
```cpp
#include <bits/stdc++.h>

#define REN 100000
#define MAXN (REN+5)
#define int long long

using namespace std;

inline int read()
{
    int x=0,f=1;char c=getchar();
    while(!isdigit(c)) {if(c=='-') {f=-1;} c=getchar();}
    while(isdigit(c))  {x=x*10+c-'0';      c=getchar();}
    return x*f;
}
void write(int x)
{
    if(x<0) {putchar('-');x=-x;}
    if(x>9) {write(x/10);}
    putchar(x%10+'0');
}

int n,m;
int ans;
/// @brief Edge
struct edge {int to,next;} e[MAXN*2];
int cnt,head[MAXN];
void add(int x,int y) {cnt++;e[cnt].to=y;e[cnt].next=head[x];head[x]=cnt;}
/// @brief Tree
int f[MAXN];
void tree(int x,int fa)
{
    f[x]=1;
    for(int i=head[x];i;i=e[i].next)
    {
        int v=e[i].to;if(v==fa) {continue;}
        tree(v,x);
        f[x]-=f[v];
    }
    if(fa) {ans+=abs(f[x]);}
}
/// @brief Circle
int st[MAXN],len;
int vis[MAXN],book[MAXN];
int p[MAXN],q;
int a[MAXN];
void findc(int x,int fa)
{
    if(vis[x]) {if(!q) {while(st[len]!=x) {p[++q]=st[len];len--;} p[++q]=x;} return ;}
    st[++len]=x;vis[x]=1;
    for(int i=head[x];i;i=e[i].next) {if(e[i].to!=fa) {findc(e[i].to,x);}}
    len--;
}
/// @brief Prefix
int odd[MAXN],eve[MAXN];
int all(int x)
{
    if(x&1) {return (odd[q]-odd[(x-2)<0?0:(x-2)])-(eve[q-1]-eve[x-1])+(eve[x-1])-odd[(x-2)<0?0:(x-2)];}
    else    {return (eve[q-1]-eve[(x-2)<0?0:(x-2)])-(odd[q]-odd[x-1])+(odd[x-1])-eve[(x-2)<0?0:(x-2)];}
}
/// @brief Abs
int pp[MAXN];
signed main()
{
    // freopen("color.in","r",stdin);
    // freopen("color.out","w",stdout);
    time_t st=clock();
    int i,j,k;
    n=read();m=read();
    for(i=1;i<=m;i++) {int x=read(),y=read();add(x,y);add(y,x);}
    if(n-1==m)
    {
        tree(1,0);
        if(!f[1]) {write(ans);}
        else      {write(-1);}
    }
    else
    {
        findc(1,0);
        for(i=1;i<=q;i++) {book[p[i]]=1;}
        for(i=1;i<=q;i++)
        {
            a[i]=1;
            for(j=head[p[i]];j;j=e[j].next)
            {
                int v=e[j].to;if(book[v]) {continue;}
                tree(v,p[i]);
                a[i]-=f[v];
            }
        }
        for(i=1;i<=q;i+=2) {odd[i]=odd[(i-2)<0?0:(i-2)]+a[i];}
        for(i=2;i<=q;i+=2) {eve[i]=eve[i-2]+a[i];}     
        if(q%2==0)
        {
            if(odd[q-1]!=eve[q]) {write(-1);}
            else
            {
                for(i=1;i<=q;i++) {pp[i]=pp[i-1]-((i&1)*2-1)*a[i];}
                sort(pp+1,pp+q+1);
                int res=0;
                for(i=1;i<=q;i++) {res+=abs(pp[i]-pp[q/2]);}
                write(ans+res);
            }
        }
        else
        {
            if(abs((odd[q]-eve[q-1])%2)==1) {write(-1);}
            else
            {
                int suit=(odd[q]-eve[q-1])/2;
                ans+=abs(suit);
                a[1]-=suit;
                a[q]-=suit;
                int sum=0;
                for(i=1;i<=q;i++)
                {
                    sum=a[i]-sum;
                    ans+=abs(sum);
                }
                write(ans);                
            }
        }
    }
    time_t ed=clock();
    double ret=double(ed-st)/CLOCKS_PER_SEC;
    cerr<<endl<<ret<<'s';
    return 0;
}

```

---

## 作者：Felix72 (赞：0)

妙妙题，代码简单，思维量偏大。

既然给了部分分，我们不妨分情况考虑一下。

#### 树

思考一棵简单的树：菊花图。我们可以轻松发现，有多个叶子的菊花图是无解的。为什么？我们把花心作为树根，发现这些叶子节点要染色，必然都要借助树根；而树根却没有父亲节点的帮助，因此无解。

收到这个例子的启发，我们似乎可以把“需要父亲节点的什么帮助”设置成递推状态，然后跑一个 dp。我们看看代码：

```cpp
inline void treedp(int now, int prt)
{
	f[now] = 1;
	for(int i = h[now]; i; i = e[i].next)
	{
		int to = e[i].to;
		if(to == prt) continue;
		treedp(to, now);
		f[now] -= f[to];
	}
	ans += abs(f[now]);
}
```

简单理解一下：$f_{now}$ 是正数时表示当前节点需要与父亲从白变黑 $f_{now}$ 次，负数则说明需要和父亲从黑变白 $-f_{now}$ 次。

显然，答案是 $f$ 数组绝对值的和。最后看看根节点是否需要帮助，若是则无解。

#### 偶环

刚才的 dp 用黑白染色的思路来理解也是说得通的。把 $f$ 看作是黑白点数量的差，能在子树内匹配就先匹配好，实际上跟刚才对 $f$ 的定义等价。

我们把换上偶数编号的 $f$ 全部取相反数（因为黑白染色后一棵子树的黑点对相邻子树来说是白点），这就变成了环形均分纸牌，用经典的找中位数做法即可，详细可以看看 [P2512 糖果传递](https://www.luogu.com.cn/problem/P2512)。

#### 奇环

对于环上面的两棵子树，如果他们内部的点要匹配，所用环上路径是固定的。

为什么？因为把这个环拆成两条路径，必然是一条奇数一条偶数，因此方案确定。

我们把环删掉一条边，就按照树那样 dp 一遍，最后检查有多少匹配经过了删去的边，算上贡献即可。

```cpp
/*Good Game, Well Play.*/
#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
int n, m, h[N], cnt; struct edge {int to, next;} e[N * 2];
inline void add(int x, int y)
{e[++cnt].to = y, e[cnt].next = h[x], h[x] = cnt;}

namespace subtask1
{
	long long f[N], ans;
	inline void treedp(int now, int prt)
	{
		f[now] = 1;
		for(int i = h[now]; i; i = e[i].next)
		{
			int to = e[i].to;
			if(to == prt) continue;
			treedp(to, now);
			f[now] -= f[to];
		}
		ans += abs(f[now]);
	}
	inline void solve()
	{
		treedp(1, 0);
		if(f[1]) cout << -1 << '\n';
		else cout << ans << '\n';
	}
}

namespace subtask2
{
	long long f[N], ans, s[N]; bool is[N];
	inline void treedp(int now, int prt)
	{
		f[now] = 1;
		for(int i = h[now]; i; i = e[i].next)
		{
			int to = e[i].to;
			if(to == prt) continue;
			if(is[now] && is[to]) continue;
			treedp(to, now);
			f[now] -= f[to];
		}
		if(prt) ans += abs(f[now]);
	}
	bool vis[N]; int sta[N], top, cir[N], cn; bool flag;
	inline void dfs(int now, int prt)
	{
		sta[++top] = now; vis[now] = true;
		for(int i = h[now]; i; i = e[i].next)
		{
			int to = e[i].to;
			if(to == prt) continue;
			if(vis[to])
			{
				if(!flag)
				{
					for(int j = top; j >= 1; --j)
					{
						cir[++cn] = sta[j]; is[sta[j]] = true;
						if(cir[cn] == to) break;
					}
					flag = true;
				}
			}
			else dfs(to, now);
		}
		--top; vis[now] = false;
	}
	inline void solve()
	{
		dfs(1, 0);
		for(int i = 1; i <= cn; ++i) treedp(cir[i], 0);
		long long tag = 0;
		for(int i = 1; i <= cn; i += 2) tag += f[cir[i]];
		for(int i = 2; i <= cn; i += 2) tag -= f[cir[i]];
		if(abs(tag) % 2 == 1 || (cn % 2 == 0 && tag != 0))
		{
			cout << -1 << '\n';
			return ;
		}
		if(cn % 2 == 0)
		{
			for(int i = 1, wd = 1; i <= cn; ++i)
			{
				s[i] = f[cir[i]] * wd;
				wd *= -1;
			}
			for(int i = 2; i <= cn; ++i) s[i] += s[i - 1];
			sort(s + 1, s + cn + 1);
			for(int i = 1; i <= cn; ++i) ans += abs(s[cn / 2] - s[i]);
			cout << ans << '\n';
		}
		else
		{
			for(int j = 1; j <= cn; ++j) s[j] = f[cir[j]] - s[j - 1];
			for(int j = 1, wd = 1; j <= cn; ++j)
			{
				ans += abs(s[j] - s[cn] / 2 * wd);
				wd *= -1;
			}
			cout << ans << '\n';
		}
	}
}

int main()
{
//	freopen("text.in", "r", stdin);
//	freopen("prog.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> m;
	for(int i = 1; i <= m; ++i)
	{
		int x, y; cin >> x >> y;
		add(x, y), add(y, x);
	}
	if(m == n - 1) subtask1::solve();
	else subtask2::solve();
	return 0;
}
/*
8 8
1 2
2 3
3 1
1 4
1 5
1 6
1 7
1 8
*/
```

---

