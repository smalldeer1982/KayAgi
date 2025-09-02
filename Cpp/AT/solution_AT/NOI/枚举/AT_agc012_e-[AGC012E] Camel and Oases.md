# [AGC012E] Camel and Oases

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc012/tasks/agc012_e

$ N $ 箇所のオアシスが数直線上に並んでおり、左から $ i $ 番目のオアシスは座標 $ x_i $ にあります。

ラクダはこれらのオアシス全てを訪れたいです。 ラクダははじめ、体積 $ V $ のこぶを持っています。こぶの体積を $ v $ としたとき、ラクダは水を最大で $ v $ 蓄えることができます。ラクダはオアシスにいるときのみ、水を補給することができます。オアシスでは蓄えられるだけ水を補給することができ、同じオアシスで何回でも水を補給することができます。

ラクダは数直線上を歩くか、ジャンプするかのどちらかの方法で移動することができます。

- ラクダが距離 $ d $ だけ歩いたとき、蓄えている水を $ d $ だけ消費します。ただし、蓄えられた水の量が負になるようには移動できません。
- 蓄えられた水の量を $ v $ として $ v\ >\ 0 $ のとき、ラクダはジャンプをすることで数直線上の任意の地点へと移動することができます。その後、こぶの体積が $ v/2 $(小数点以下は切り捨て) となり、蓄えられた水の量が $ 0 $ になります。

ラクダが $ 1,2,3,...,N $ 番目のオアシスから出発したとき、全てのオアシスを訪れることが可能かどうかをそれぞれ判定してください。

## 说明/提示

### 制約

- $ 2\ ≦\ N,V\ ≦\ 2\ ×\ 10^5 $
- $ -10^9≦\ x_1\ <\ x_2\ <\ ...\ <\ x_N\ ≦10^9 $
- $ V,\ x_i $ はいずれも整数

### Sample Explanation 1

以下のように移動することで、$ 1 $ 番のオアシスから出発して全てのオアシスを訪れることが可能です。 - $ 1 $ 番のオアシスから $ 2 $ 番のオアシスへと歩いて移動する。蓄えられた水の量は $ 0 $ となる。 - $ 2 $ 番のオアシスで水を補給する。蓄えられた水の量は $ 2 $ となる。 - $ 2 $ 番のオアシスから $ 3 $ 番のオアシスへとジャンプして移動する。蓄えられた水の量は $ 0 $ となり、こぶの体積は $ 1 $ となる。

### Sample Explanation 2

オアシスは何度訪れても構いません。

## 样例 #1

### 输入

```
3 2
1 3 6```

### 输出

```
Possible
Possible
Possible```

## 样例 #2

### 输入

```
7 2
-10 -4 -2 0 2 4 10```

### 输出

```
Impossible
Possible
Possible
Possible
Possible
Possible
Impossible```

## 样例 #3

### 输入

```
16 19
-49 -48 -33 -30 -21 -14 0 15 19 23 44 52 80 81 82 84```

### 输出

```
Possible
Possible
Possible
Possible
Possible
Possible
Possible
Possible
Possible
Possible
Possible
Possible
Impossible
Impossible
Impossible
Impossible```

# 题解

## 作者：Ebola (赞：19)

### 疯狂吐槽

大家好，我是萌新，这道50行不到的题我调了4小时。(╯‵□′)╯︵┻━┻

一开始写二分，边界恶心了我三小时，终不成，遂放弃

后来发现直接维护跳跃指针可以省掉一个log，一小时后再次弃疗

再后来OYJason过来看了一眼，发现我的跳跃指针完全没有意义，直接右端点+1或左端点-1就行了，于是代码删去了若干行，瞬间AC

### 题解

每次跳跃会让v减半，因此最多跳跃log v次。那可以看作一棵log v层的容器，每层有若干条线段。对于第i层的一条线段，它所覆盖的点就是按跳跃i-1次后的驼峰大小来算，能直接到达的绿洲

那问题就变成了：在每层选一个线段，将整个区间完全覆盖。其中第一层选择的线段是钦定的（因为要对每个出发点求是否有解）

因为层数是log v级别的，所以可以状压dp。状态s的第i位为1，表示第i层已经选了一个线段。我们要dp出两个东西：exL\[s\]表示状态s下，从左到右能完全覆盖的最右边位置；exR\[s\]表示状态s下，从右到左能完全覆盖的最左边位置

然后为了方便dp，我们处理出每一层的所有线段，记L\[d\]\[x\]表示第d层中，x所在线段的左端点。R\[d\]\[x\]同理

转移：$exL_s=\max\limits_{t\in s}(R[t][exL_{\complement_st}+1]),\quad ;exR_s=\max\limits_{t\in s}(L[t][exR_{\complement_st}-1])$

然后枚举第一层的所有线段，对于每个线段，在所有状态里找，看有没有那个状态所对应的exL，加上它的补集对应的exR，在加上这个线段，能把区间完全覆盖。如果可以，那这个线段里的所有位置都是Possible

那枚举线段又枚举状态，复杂度会不会爆炸呢？不会。显然的，若第一层线段多于log v个，那不可能有解，在这种情况下直接全部输出Impossible即可

状态总数是O(v)的，所以总的复杂度是O((n+v) log v)

```cpp
#include<bits/stdc++.h>
#define FR first
#define SE second
using namespace std;

const int S=(1<<20)+5;
char buf[S],*H,*T;
inline char Get()
{
    if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
    if(H==T) return -1;return *H++;
}
inline int read()
{
    int x=0,fg=1;char c=Get();
    while(!isdigit(c)&&c!='-') c=Get();
    if(c=='-') fg=-1,c=Get();
    while(isdigit(c)) x=x*10+c-'0',c=Get();
    return x*fg;
}

typedef pair<int,int> pii;
const int INF=0x3f3f3f3f;
const int N=200010;
int n,V,X[N],dep=0;
int L[20][N],R[20][N];
int exL[N<<4],exR[N<<4];
pii seg[N];
bool ans[N];

int main()
{
    n=read();V=read();
    for(int i=1;i<=n;i++) X[i]=read();
    X[0]=-INF-V-1;X[n+1]=INF+V+1;
    for(int v=V;v>=0;v>>=1,dep++)
    {
        R[dep][n+1]=n+1;
        for(int i=1;i<=n;i++) L[dep][i]=(X[i]-X[i-1]<=v)?L[dep][i-1]:i;
        for(int i=n;i>=1;i--) R[dep][i]=(X[i+1]-X[i]<=v)?R[dep][i+1]:i;
        if(v==0){dep++;break;}
    }
    for(int i=1;i<=n;i++) seg[i]=pii(L[0][i],R[0][i]);
    int cnt=unique(seg+1,seg+1+n)-(seg+1);
    for(int i=0;i<(1<<dep);i++) exR[i]=n+1;
    for(int s=0;s<(1<<dep);s+=2)
        for(int i=0;i<dep;i++)
        {
            if(!(s&(1<<i))) continue;
            exL[s]=max(exL[s],R[i][exL[s^(1<<i)]+1]);
            exR[s]=min(exR[s],L[i][exR[s^(1<<i)]-1]);
        }
    if(cnt>dep) goto output;
    for(int i=1;i<=cnt;i++)
        for(int s=0;s<(1<<dep);s+=2)
            if(exL[s]>=seg[i].FR-1&&exR[(1<<dep)-1-s-1]<=seg[i].SE+1)
            {
                for(int j=seg[i].FR;j<=seg[i].SE;j++) ans[j]=1;
                break;
            }
    output: for(int i=1;i<=n;i++) puts(ans[i]?"Possible":"Impossible");
    return 0;
}
```



---

## 作者：JohnJoeZhu (赞：13)

[题面传送门](https://www.luogu.com.cn/problem/AT2365)

第一篇黒题题解，希望能够用清晰明了的语言来讲这道~~毒瘤~~黒题
## 1.解法探索
#### 1.1 时间复杂度
由$2e5$可知复杂度约为$O(n)$或$O(nlogn)$
#### 1.2 初步暴力
如果我们进行暴力的话，我们会发现V的变化是$V,V/2,V/4,...,2,1,0$

也就是可以跳跃$logV$次

而且，在每个点，如果不进行跳跃，相应水量可以走的距离是固定的且连续的

那么可以尝试预处理在每个点，以相应的水量可以走到的最左和最右

（可以结合样例理解）
#### 1.3 推理思考
那么我们知道每个点可以走的范围是否有用呢？

首先我们的目标，是知道在一个点是否可以遍历所有点

也就是从一个点，使用若干个V，向左与向右走，是否可以到达1号点与n号点

那么应不应该强制只能够连续走呢？

设想在一个点，如果向左连续用了$V,V/2,V/4,V/8$的水，方案会最优吗？

显然不会

那么在上面的例子中，跳跃一直是向左的

那我们是不是也可以向左，向右，向左，向右……

只要最终不重复地使用了若干个连续的$V,V/2,V/4,V/8,...$即满足我们的要求

可是我们又如何知道向左与向右跳用了哪一些V呢？

考虑V的范围，能不能够把V记录下来

可以！！！

那就状压没跑了

那又回到原来的问题：应不应该强制只能够连续走呢？

如果连续走，并不能走到1或n号点，那跳跃起来走，也不可能达到要求

所以判断就变成了这样：

- 从一个点，使用若干个V，向左与向右连续走，是否可以到达1号点与n号点

换个角度，我们要求每个点到1与n，复杂度不小

那是不是可以直接在1与n计算即可

也就是求从1号点与n号点，向左或向右连续跳，使用若干个V，能够到达的最右和最左的距离

运用上述思路，使用状压是一个好选择，且复杂度不会过高

那么最后如何利用已知求出答案？

如果1可以到达i，n可以到达j，且$i>=j$，我们是不是就可以判断j到i这个区间是可行的？

如图

![](https://cdn.luogu.com.cn/upload/image_hosting/4ozjdkls.png)

在这里留一个点：控制V在两个线段的交集处使用

#### 1.4 整理思路
我们解题的顺序是什么呢？

- 求出所有的V

- 使用递推，求出每个点在每一个V时所能够走的范围

- 使用状压+dp，求出在点1与点n所能够向左与向右走最远的距离

- 判断交集，求出每个点是否能够遍历每一个点，得到答案

那么求解的部分就结束了，接下来是每一个部分的代码实现了

## 2.代码片段（详细注释）
#### 2.1 求出所有的V
```cpp
//一行搞定qwq
int V=m;while(V){V>>=1;v[cnt++]=V;}v[cnt]=m;
//注意这里要保证最后一个V是最大的V，才能够为1.3留下的问题的解决提供条件
```
#### 2.2 求出每个点在每一个V时所能够走的范围
```cpp
	for(int i=0;i<=cnt;i++)
	{
		l[i][1]=1;//向左，预处理是显然的
		r[i][n]=n;//向右
		for(int j=2;j<=n;j++) l[i][j]=(a[j]-a[j-1]<=v[i])?l[i][j-1]:j;//如果我们能够走到左边的点，那就可以走到左边的点所能够走到的最左，向右同理
		for(int j=n-1;j>=1;j--) r[i][j]=(a[j+1]-a[j]<=v[i])?r[i][j+1]:j;
	}
```
#### 2.3 求出在点1与点n所能够向左与向右走最远的距离
```cpp
	for(int i=0;i<(1<<cnt);i++) R[i]=n+1;//为了取min，先赋初值
	for(int i=0;i<(1<<cnt);i++)
		for(int j=0;j<=cnt;j++)
			if(((1<<j)&i)==0)//状压常规操作
				L[(1<<j)|i]=max(L[(1<<j)|i],r[j][L[i]+1]),
				R[(1<<j)|i]=min(R[(1<<j)|i],l[j][R[i]-1]);//由于我们要求连续走，那么我们就在现在的极限向左或右跳一步，然后再走即可
```
#### 2.4 得到答案
```cpp
	for(int i=1;i<=n;i++)//这里i是跳跃的，所以随机下是走不满的
	{
		bool flag=0;
		for(int j=0;j<(1<<cnt);j++)
		{
			int ss=((1<<cnt)-1)^j;//求补集，因为我们在1点用的V和在n点用的V不应该重复，那两个集合的并集就是V的全集，交集为空
            		//注意我们可能不需要用某一个V，这个时候你是可以浪费它的，比如跳两次等
			if(L[j]>=i-1&&R[ss]<=r[cnt][i]+1){flag=1;break;}//如果线段交集满足要求，注意这里我们是保证第一步从V开始跳，当然如果你不要也可以浪费掉，总之一点V不能够在别的地方出现
		}
		for(int j=i;j<=r[cnt][i];j++) ans[j]=flag;
		i=r[cnt][i];
	}
```
## 3.代码时间（无注释版）
时间复杂度约为$O(VlogV)$
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=2e5+5;
int n,m,a[N],l[25][N],r[25][N],v[25],cnt=0,L[1<<25],R[1<<25],ans[N];
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	int V=m;
	while(V){V>>=1;v[cnt++]=V;}v[cnt]=m;
	for(int i=0;i<=cnt;i++)
	{
		l[i][1]=1;
		r[i][n]=n;
		for(int j=2;j<=n;j++) l[i][j]=(a[j]-a[j-1]<=v[i])?l[i][j-1]:j;
		for(int j=n-1;j>=1;j--) r[i][j]=(a[j+1]-a[j]<=v[i])?r[i][j+1]:j;
	}
	for(int i=0;i<(1<<cnt);i++) R[i]=n+1;
	for(int i=0;i<(1<<cnt);i++)
		for(int j=0;j<=cnt;j++)
			if(((1<<j)&i)==0)
				L[(1<<j)|i]=max(L[(1<<j)|i],r[j][L[i]+1]),
				R[(1<<j)|i]=min(R[(1<<j)|i],l[j][R[i]-1]);
	for(int i=1;i<=n;i++)
	{
		bool flag=0;
		for(int j=0;j<(1<<cnt);j++)
		{
			int ss=((1<<cnt)-1)^j;
			if(L[j]>=i-1&&R[ss]<=r[cnt][i]+1){flag=1;break;}
		}
		for(int j=i;j<=r[cnt][i];j++) ans[j]=flag;
		i=r[cnt][i];
	}
	for(int i=1;i<=n;i++) puts(ans[i]==0?"Impossible":"Possible");
	return 0;
}
```
**完结撒花！！！**

---

## 作者：Spasmodic (赞：7)

这题是真的仙 我第一反应是拆点分层图 然后发现图建立不下 然后发现它的联通分支很有性质 然后就可以做了。

我们观察到最朴素的做法是每个点拆 $\log$ 层，第 $i$ 层的 $p$ 点表示我在 $p$ 处，然后已经跳跃了 $i$ 下，能一次到达连边。但是这样边数已经起飞了，我们不能这么做。 

我们先把每一层单独考虑其连通分支 那么每一层可以分为若干个区间 每个区间是互相联通的 这个非常容易预处理出来 然后层与层之间是可以乱跳的。

那么我们现在就变成了：有 $k=\log n$ 层，每层你得选个线段，第一层固定，要求覆盖。

那我们跑个状压是不是就完了，维护选层状态为 $S$ 情况下，线段并集为前缀时的最大右端点和线段并集为后缀时的最小左端点，这个转移显然可以在区间上跑二分来解决，复杂度是 $O(2^kk\log n)=O(n\log^2 n)$。

求答案直接枚举子集，复杂度是 $O(2^k)=O(n)$ 的。

但是查询 $n$ 次，复杂度又变成了 $O(n^2)$，怎么办？

这个时候我们就需要观察性质。首先，我们发现第一层在同一线段上的点答案一致，可以省去；其次，我们发现对任意线段我们都可以找到第一层中对应的线段，那么我们可以直接对应成 $k$ 个区间，于是我们可以得出结论：第一层如果区间个数大于 $k$，答案一定都是 Impossible！

所以我们就把复杂度优化到了 $O(nk)=O(n\log n)$，同时 dp 复杂度也变成了 $O(n\log n\log\log n)$（因为那个二分对线段做，个数为 $O(\log n)$）。

P.S. 预处理一手可以把最后这个 $\log\log$ 给省掉，不过我懒了。

代码不放了。

---

## 作者：Sin_Watt (赞：5)

2025/7/11，图炸了，还是用洛谷图床

---

你见过非官解、思路极简、没有大量剪枝、还没有毒瘤卡常的黑题暴搜吗。

我们照抄 @Ebola 大佬题解里的题目转化：
> 每次跳跃会让 $V$ 减半，因此最多跳跃 $\log V$ 次。那可以看作一棵 $\log V$ 层的容器，每层有若干条线段。对于第 $i$ 层的一条线段，它所覆盖的点就是按跳跃 $i-1$ 次后的驼峰大小来算，能直接到达的绿洲。
> 
> 那问题就变成了：在每层选一个线段，将整个区间完全覆盖。其中第一层选择的线段是钦定的（因为要对每个出发点求是否有解）。
> 
> _（添加了 $\KaTeX$、空格和句号以满足题解审核要求）_


画个图就很直观：

![一个很直观的图.png](https://cdn.luogu.com.cn/upload/image_hosting/mieyu42g.png)

然后考虑暴搜，考虑当前已经填了前 $k-1$ 层，还没有被覆盖的点集为 $S$。关于这个 $S$，我们直接用 $\operatorname{vector}$ 套 $\operatorname{pair}$ 来记录，每个 $\operatorname{pair}$ 记录一个第 $k$ 层的线段（参考上图中的方框）。

然后是一个很显然的小剪枝：如果剩下的操作次数（$\log V - k$）小于第 $k$ 层未被覆盖的线段数，就直接退出。

然后是记搜。我选择直接暴力地上 $\operatorname{map}$。

就这样。我大概写的是 $O(V\log^2V+n\log V)$（复杂度 ~~证明不了~~ 在后面）。精细实现 $O(V\log V+n\log V)$。

[提交记录](https://atcoder.jp/contests/agc012/submissions/64178087)（我代码的变量可能比较迷惑）。

### 复杂度感性理解

瓶颈在于状态数和记录状态的代价。

要把状态数卡满，必然是不存在可行解的。每一层的待选项的数量卡满，在最后一层炸掉。大概如下图：

![12.png](https://cdn.luogu.com.cn/upload/image_hosting/3vm8n86r.png)

如果不记搜，显然是层数的阶乘级别。但记搜下来是 $O(2^{\log V})$，即 $O(V)$。因为 $V=0$ 和 $V=1$ 也算一层，所以带最多 $4$ 倍常数。

用 $\operatorname{map}$ 套 $\operatorname{vector}$ 就是 $O(\log^2 V)$ 的。如果哈希并且精细实现 $\operatorname{vector}$ 的转移，应该甚至可以均摊 $O(1)$（纯口胡）。

---

## 作者：Soulist (赞：5)

好像做麻烦了...

首先每次的 $V$ 都除以了 $2$，意味着递归处理最多只有 $O(\log v)$ 层，对于每层互达的点我们可以缩在一起，问题变成，给定 $\log v$ 层线段，每层可能有多个线段，然后每层你可以选一个，问是否能够铺满 $1,n$ 

然后你排个序，状压$dp$即可，就是从右往左走，令 $f[S]$ 表示使用了状态 $S$ 时，右端点最远可以延长至那里。

然后由于最上面那一层是固定的，所以这意味着我们需要强制限定最上面的线段是谁，我们额外记一个维度表示最上面那一层选择了 $j$ 即可，这样就可以应付查询了。

然后由于最上面一层的线段数不能比 $O(\log V)$ 大，否则肯定无解，所以特判一下即可...不过我的复杂度是$O(V\log^2 V)$ 的，貌似可以通过，大概 $\rm 500ms$ 左右。

$Code:$

```cpp
#include<bits/stdc++.h>
using namespace std ;
#define rep( i, s, t ) for( register int i = s; i <= t; ++ i )
#define re register
int gi() {
	char cc = getchar() ; int cn = 0, flus = 1 ;
	while( cc < '0' || cc > '9' ) {  if( cc == '-' ) flus = - flus ; cc = getchar() ; }
	while( cc >= '0' && cc <= '9' )  cn = cn * 10 + cc - '0', cc = getchar() ;
	return cn * flus ;
}
const int N = 2e5 + 5 ; 
const int M = 15 + 5 ; 
int n, m, w[M], cnt, a[N], st[N], top, Go[M][N], dp[1 << M][M], W[N] ; 
signed main()
{
	n = gi(), m = gi() ; rep( i, 1, n ) a[i] = gi() ; 
	while( m ) w[++ cnt] = m, m = m / 2 ; 
	w[++ cnt] = 0 ; int r = 1 ; 
	for( re int k = 1; k <= cnt; ++ k ) {
		r = 1 ; int befr = 0 ; 
		for( re int i = 1; i <= n; ++ i ) {
			r = max( r, i ) ; 
			while( r < n && a[r + 1] - a[max( i, r )] <= w[k] ) ++ r ;  
			Go[k][i] = r ;
			if( ( k == 1 ) && ( r != befr ) ) st[++ top] = r, W[r] = top, befr = r ;
		}
	}
	if( top > cnt ) { rep( i, 1, n ) puts("Impossible") ; exit(0) ; }
	int maxn = ( 1 << cnt ) - 1 ; dp[0][0] = 0 ;
	rep( i, 1, cnt ) Go[i][n + 1] = n ;
	for( re int i = 0; i < maxn; ++ i ) rep( t, 0, top )
		for( re int j = 1; j <= cnt; ++ j ) {
			int k = ( 1 << ( j - 1 ) ) ;
			if( ( i & k ) ) continue ;  
			if( j == 1 && t == 0 )
				dp[i ^ k][W[Go[j][dp[i][t] + 1]]] = max( dp[i ^ k][W[Go[j][dp[i][t] + 1]]], Go[j][dp[i][t] + 1] ) ;
			else if( j != 1 ) dp[i ^ k][t] = max( dp[i ^ k][t], Go[j][dp[i][t] + 1] ) ;
		}
	rep( i, 1, n ) {
		if( dp[maxn][W[Go[1][i]]] >= n ) puts("Possible") ;
		else puts("Impossible") ;
	}
	return 0 ;
}
```

---

## 作者：Lucky_Xiang (赞：2)

# 题目

[AGC012E](https://www.luogu.com.cn/problem/AT_agc012_e)

# 分析

首先，因为每次跳跃都会使 $V$ 减半，所以 $V$ 的取值只有 $k=\lceil\log N\rceil$ 个。

而贪心的，每次跳跃以后都会尽可能地向左右两边扩展，直至不能再扩展，再进行下一次跳跃。因此可以先预处理出对于每一次跳跃以后的 $V'$，从所有点开始能扩展到的左右端点。

那么题目就被转化为了从 $k$ 层区间中每一层选一个区间，使其覆盖 $1\sim N$。

发现层数很少，所以可以采用状压 dp。把每一层是否选过记为状态 $S$，则 $S$ 的取值只有 $O(2^k)=O(N)$ 个。

因为要求出以每个点为起点时的答案，所以还需要记录一维  $id$ 表示 $V$ 那一层选择的区间。为了防止状态数过多，可以将 $V$ 那一层区间数大于 $k$ 的情况先特判掉，因为一定无解。此时状态数为 $O(N\log N)$ 个。

而状态 $f_{S,id}$ 表示的内容是当每层的选择情况为 $S$，且 $V$ 那一层选择了第 $id$ 个区间时能够从 $1$ 开始覆盖的最大右端点。转移时只需选择 dp 值最小的一个进行转移即可。

时间复杂度 $O(N\log^2 N)$。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int mn=200010;
const LL inf=1e18;
int n,V[mn];
int tot;
LL a[mn];
int nxt[20][mn];
int id[mn];
int N;
int f[mn*3][20];
struct state
{
    int s;
    int id;
};
vector<state>vec[mn];
int x,y;
bool st[mn];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin>>n>>V[0];
    for(int i=1;i<=n;i++)cin>>a[i];
    while(1)
    {
        tot++;
        V[tot]=V[tot-1]/2;
        if(!V[tot])break;
    }
    a[n+1]=inf;
    for(int j=0;j<=tot;j++)
    {
        for(int i=n;i>=1;i--)
        {
            if(a[i+1]-a[i]>V[j])nxt[j][i]=i;
            else nxt[j][i]=nxt[j][i+1];
        }
    }
    id[1]=1;
    for(int i=2;i<=n;i++)
    {
        if(nxt[0][i-1]==i-1)id[i]=id[i-1]+1;
        else id[i]=id[i-1];
    }
    if(id[n]>tot+1)
    {
        for(int i=1;i<=n;i++)cout<<"Impossible\n";
        return 0;
    }
    N=1<<(tot+1);
    f[0][0]=0;
    vec[0].push_back({0,0});
    for(int i=0;i<n;i++)
    {
        for(auto k:vec[i])
        {
            if(f[k.s][k.id]!=i)continue;
            for(int j=0;j<=tot;j++)
            {
                if(~(k.s>>j)&1)
                {
                    x=k.s|(1<<j); y=k.id;
                    if(j==0)y=id[i+1];
                    if(f[x][y]<nxt[j][i+1])
                    {
                        f[x][y]=nxt[j][i+1];
                        vec[f[x][y]].push_back({x,y});
                    }
                }
            }
        }
    }
    for(int i=0;i<N;i++)
    {
        for(int j=1;j<=id[n];j++)
        {
            if(f[i][j]==n)st[j]=1;
        }
    }
    for(int i=1;i<=n;i++)
    {
        cout<<(st[id[i]]?"Possible":"Impossible")<<'\n';
    }
    return 0;
}
```

---

## 作者：RainWetPeopleStart (赞：1)

现在题解区还没满，水一发。

## 题解

### 性质1

最多跳跃 $\log V$ 次。

### 性质2

如果不考虑遍历所有绿洲这一条件，每次跳跃后的走路过程可以认为只和当前的 $V$ 有关。

### 分析

由性质2，考虑对固定的 $V$ 进行考虑。

此时，如果两点 $u,v$（$u<v$）可达，那么一定不存在 $i$ 满足 $u\le i<v$ 且 $x_{i-1}-x_i>V$。

因此，可以把原序列划分为若干**极长**段，段内相邻两点距离不大于 $V$。（即两两可达）

这里记分出的段数为 $d_V$。

### 性质3 

对 $u>v$，有 $d_u<d_v$。

感性理解一下，$V$ 越小，能走到的段就越短。

### 做法

现在就可以做了。

假设在初始状态之前还有一次跳跃。

令“一轮”表示两次跳跃之间的走路过程。

由性质 2，问题可以抽象为每一轮选一个段，问能否覆盖整个序列，其中，第一次选的段是给定的。

由性质 1，最多有 $\log V$ 轮。

我们把对序列删掉给定的段，这样就变成了一段前缀和一段后缀。

直接枚举用哪些段覆盖前缀，那些段覆盖后缀，chk 可以使用状态压缩 DP。

具体的，记 $f_S$ 表示考虑了 $S$ 里面轮数所对的段所能覆盖到的前缀的最右端点，$g_S$ 表示考虑了 $S$ 里面轮数所对的段所能覆盖到的后缀的最左端点。

转移直接枚举加入哪个段即可。

复杂度 $O(d_V2^{\log V}+2^{\log V}\log V)=O(V\log V+Vd_V)$。

发现 $d_V$ 很大时会寄。

不过这可以解决，当 $d_V>\log V$ 时，由性质 3，不可能覆盖整个序列，输出无解即可。

复杂度 $O(V\log V)$。

实在看不懂就看代码吧。

## 代码


```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define fi first
#define se second
#define pii pair<int,int>
#define mk make_pair
#define Int __int128_t
using namespace std;
const int N=2e5+10,S=1.2e6;
int n,V;
int x[N];
int d[N];
int c=0;
int fa[N];
int fd(int x){return (x==fa[x])?x:fa[x]=fd(fa[x]);}
int bel[N][22];
pii Q[N<<5];
int f1[S],f2[S];
bool ok[N];
int main(){
	cin>>n>>V;
	for(int i=1;i<=n;i++) cin>>x[i];
	while(V!=0){
		d[++c]=V;V/=2;
	}d[++c]=0;
	int cnt=1;
	for(int i=2;i<=n;i++){
		if(x[i]-x[i-1]>d[1]) cnt++;
	}if(cnt>20){
		for(int i=1;i<=n;i++) cout<<"Impossible"<<endl;
		return 0;
	}
	int tot=0;
	for(int j=1;j<=c;j++){
		++tot;Q[tot].fi=1;
		bel[1][j]=tot;
		for(int i=2;i<=n;i++){
			if(x[i]-x[i-1]>d[j]) Q[tot].se=i-1,Q[++tot].fi=i;
			bel[i][j]=tot;//cout<<i<<' '<<j<<' '<<bel[i][j]<<endl;
		}Q[tot].se=n;
	}
	memset(f1,0xc0,sizeof(f1));
	memset(f2,0x3f,sizeof(f2));
	f1[0]=0;f2[0]=n+1;
	for(int i=1;i<(1<<c);i++){
		for(int j=1;j<=c;j++){
			if(!((i>>(j-1))&1)) continue;
			int st=i^(1<<(j-1));
			f1[i]=max(f1[i],Q[bel[f1[st]+1][j]].se);
			f2[i]=min(f2[i],Q[bel[f2[st]-1][j]].fi);
		}
	}for(int i=1;i<=n;i++){
		if(bel[i][1]!=bel[i-1][1]){
			int o=bel[i][1];
			int L=Q[o].fi,R=Q[o].se;
			int U=((1<<c)-1)^1;
			bool fl=0;
			for(int j=0;j<(1<<c);j++){
				if(j&1) continue;
				int s1=j,s2=U^j;
				if(f1[s1]>=L-1&&f2[s2]<=R+1) fl=1;
			}ok[o]=fl;
		}
		if(ok[bel[i][1]]){
			cout<<"Possible"<<endl;
		}else{
			cout<<"Impossible"<<endl;
		}
	}
	return 0;
}
```

---

## 作者：ZM____ML (赞：1)

感觉是一道很牛牛的题，第一反应是建图跑路，反应过来可以拆成 $\log$ 层维护就会了。

因为每次跳跃操作会将我背包容量的上限 $V$ 变成 $\frac{V}{2}$，所以不难发现我至多进行 $\log V$ 次跳跃操作，我的容量上限也只会发生 $\log V$ 次变化，所以我们可以考虑对于每一个 $V$ 进行维护。

具体的，我们可以简单递推出当我处在第 $i$ 个绿洲，当前的背包容量上限为 $V$ 时能够通过**走路**操作到达的最左端点以及最右端点。

同样我们可以处理出来设当前选择的层集合，向左边延申可以到达的最远的位置，同理也可以处理出来向右边延申可以到达的最远的位置，可以简单状压 dp。最终状态合法就是存在一个集合，其补集和本身刚好能够填满两边。

时间复杂度 $O((n + v) \log n)$。

---

## 作者：EuphoricStar (赞：1)

容易发现跳跃次数为 $O(\log V)$。考虑对于跳跃 $k$ 次后的限制 $\left\lfloor\frac{V}{2^k}\right\rfloor$，对每个点预处理出不再跳跃能到达的最左和最右的点 $[l_{k, i}, r_{k, i}]$。

于是问题变成了，从第 $i$ 个区间集选择一个区间 $[a_i, b_i]$，若这些区间的并集是 $[1, n]$，那么这种方案会使得 $[a_0, b_0]$ 能够到达全部点。

$[a_0, b_0]$ 看起来比较烦。先把第 $0$ 个区间集扔掉。设当前的区间集的集合为 $U$，$f_S$ 为从 $S$ 中的每个区间集选出一个区间能覆盖的最大前缀右端点，同时设 $g_S$ 为能覆盖的最大后缀的左端点。$f_S, g_S$ 可以状压 dp 求出。枚举覆盖了一段前缀的集合 $S$，设 $T = U \setminus S$，那么 $T$ 覆盖了一段后缀。

若 $f_S + 1 \ge g_T$，那么 $U$ 满足从每个区间集选出一个区间能覆盖 $[1, n]$，此时就是全部 `Possible`；否则需要满足 $[f_S + 1, g_T - 1] \subseteq [a_0, b_0] = [l_{0, f_S + 1}, r_{0, f_S + 1}]$。若 $r_{0, f_S + 1} + 1 \ge g_T$ 那么 $[l_{0, f_S + 1}, r_{0, f_S + 1}]$ 就能到达全部点。

时间复杂度 $O((n + V) \log V)$。

[code](https://atcoder.jp/contests/agc012/submissions/50288837)

---

## 作者：Aigony (赞：1)

简单题。

发现只能跳 $\log V$ 次，每一层可以分成若干个只靠走路就能到达的区间。然后让你在每层至多选一个区间，问它们的并集能否覆盖所有位置。  
对第一层的每种选取方式分别求出答案。

首先第一层有超过 $\log V$ 个区间肯定寄了，可以直接特判掉。

层数足够少，预处理每一层的所有区间。令 $f_{s,i}$ 表示选了集合 $s$ 里的层，第一层选的区间是 $i$，最远能延伸到的位置。

注意到第二维只有 $\log V$ 种取值，总复杂度是 $\mathcal{O}(V\log^2 V)$。

---

## 作者：Zhddd_ (赞：1)

一道很好玩的状压 DP。

[AtCoder 题面](https://atcoder.jp/contests/agc012/tasks/agc012_e)

由于容积 $V$ 每次减少一半，所以其实不同的容积只有最多 $\log V + 2$ 个。

因此，可以预处理出容积为 $v$ 时，从第 $i$ 个绿洲能走到的最左端绿洲的编号 $l_i$，最右端绿洲的编号 $r_i$。

然后，根据所求的 $l_i$ 和 $r_i$，想象一个这样的分层图（样例 $1$）。

![](https://cdn.luogu.com.cn/upload/image_hosting/aqz55e38.png)

一条线段表示容量为对应值时，畅通无阻的绿洲。如 $v=2$ 时，可以在第 $1$ 个和第 $2$ 个绿洲随便乱走。

所以题目就转化成了每一行选一条线段，最终覆盖整片区域。

现在，我们定义状态 $L_i$ 和 $R_i$，如果 $i$ 某一个二进制位是 $1$，表示使用了这一位的线段，否则表示没有使用。

$L_i$ 表示在使用了 $i$ 这些线段后，能从第 $n$ 个绿洲走到的最左端绿洲的编号。$R_i$ 同理。状态转移：

$$L_i=\min\limits_{j\in i}(l_{L_{(i\backslash j)}-1},L_i)$$

$$R_i=\max\limits_{j\in i}(r_{R_{(i\backslash j)}+1},R_i)$$

其中 $i\backslash j$ 表示差集，下同。

初始状态：$R_i=0,L_i=n+1$。在求解状态的时候，只求 $i$ 的最低位为 $0$ 的状态（即不选第一行的线段的状态）。

最后，只需要枚举第一行的线段 $t$，得到对应线段的左端点 $l_t$ 和右端点 $r_t$，再枚举所有状态，如果存在一个状态 $i$ 满足 $(R_i\ge l_t-1)\wedge (L_{(U\backslash i)\backslash 1}\le r_t+1)$，（其中 $U$ 表示所有线段全选的状态，$(U\backslash i)\backslash 1$ 表示除了 $i$ 选的线段和第一条线段，其他的线段全选的状态），表示整片区域都被覆盖，那么整条线段所有的绿洲都是 `Possible` 的。

这样就做完了。时间复杂度分析：状态转移枚举 $O(V\log V)$ 次，最后第一行的线段不超过 $O(\log V)$ 条（否则无解），对于每条选段要枚举 $O(V)$ 个状态，所以总时间复杂度是 $O(V\log V)$。

---

## 作者：Sol1 (赞：1)

神仙题哇~

首先有两个 observation：

- 至多跳跃 $\log n$ 次。
- 从一个点走路能够到达的所有点形成一个连续区间。

然后就可以对于每一种可能的 $v$，将这些连续区间处理出来。问题变为：

现在有 $\log n$ 层，每层都有若干线段，从每一层取出 $\leq 1$ 个线段，强制第一层选的线段，问能否覆盖所有点。

现在可以状压 DP。设 $f_i$ 代表选线段的层的状态为 $i$ 时能够覆盖的最长前缀的右端点，$g_i$ 代表能够覆盖的最长后缀的左端点。

转移 $f$ 的时候，加入当前层的线段，由于要接上原来那个前缀，所以选当前层最小的一个 $>f_i$ 的右端点。

同理，转移 $g$ 的时候，选最大的一个 $<g_i$ 的左端点。

这样设层数为 $m$，这部分 DP 的复杂度就是 $O(2^mm\log n)=O(n\log^2n)$。

求答案的时候，对于每一个点，枚举子集，看能不能接上。

但是这样做的复杂度是 $O(n2^m)=O(n^2)$ 的，不能接受。

不必担心，因为我们还有第三个 observation：

- 显然因为每一层 $v$ 都会减小，所以线段长度一定也只会减小。
- 因此，如果原问题有解，那么所有线段都在第一层选一定还是有解。
- 但是，我们最多只能选 $\log v$ 个线段。
- **所以，如果第一层有超过 $\log v$ 个线段，则必然 $[1,n]$ 中所有点都无解。**

所以判掉这种情况，复杂度就下降到了 $O(n\log^2n)$，可以通过本题。

```cpp
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1 << 21], *p1 = buf, *p2 = buf;

inline int qread() {
	register char c = getchar();
	register int x = 0, f = 1;
	while (c < '0' || c > '9') {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = (x << 3) + (x << 1) + c - 48;
		c = getchar();
	}
	return x * f;
}

inline int Abs(const int& x) {return (x > 0 ? x : -x);}
inline int Max(const int& x, const int& y) {return (x > y ? x : y);}
inline int Min(const int& x, const int& y) {return (x < y ? x : y);}

int n, v, a[200005], dpl[1 << 20], dpr[1 << 20];
vector <int> vl, segl[25], segr[25];

inline void Read() {
	n = qread(); v = qread();
	for (int i = 1;i <= n;i++) a[i] = qread();
}

inline void Prefix() {
	int tmp = v;
	while (tmp) {
		for (int i = 1;i <= n;i++) {
			int l = i;
			while (i < n && a[i + 1] - a[i] <= tmp) i++;
			segl[vl.size()].push_back(l);
			segr[vl.size()].push_back(i);
		}
		vl.push_back(tmp);
		tmp >>= 1;
	}
	for (int i = 1;i <= n;i++) {
		int l = i;
		while (i < n && a[i + 1] - a[i] <= tmp) i++;
		segl[vl.size()].push_back(l);
		segr[vl.size()].push_back(i);
	}
	vl.push_back(tmp);
	// printf("%d\n", vl.size());
}

inline int LinkL(int lv, int len) {
	int idx = upper_bound(segr[lv].begin(), segr[lv].end(), len) - segr[lv].begin();
	return segr[lv][idx];
}

inline int LinkR(int lv, int len) {
	if (len == 1) return 1;
	int idx = lower_bound(segl[lv].begin(), segl[lv].end(), len) - segl[lv].begin() - 1;
	return segl[lv][idx];
}

inline void Solve() {
	if (segl[0].size() > vl.size()) {
		for (int i = 1;i <= n;i++) puts("Impossible");
		return;
	}
	memset(dpr, 0x3f, sizeof(dpr));
	for (int i = 0;i < (1 << vl.size());i++) {
		for (int j = 1;j < vl.size();j++) {
			if ((i >> j) & 1) continue;
			dpl[i | (1 << j)] = max(dpl[i | (1 << j)], LinkL(j, dpl[i]));
			dpr[i | (1 << j)] = min(dpr[i | (1 << j)], LinkR(j, dpr[i]));
		}
	}
	// for (int i = 0;i < (1 << vl.size());i++) printf("%d ", dpl[i]);
	// puts("");
	// for (int i = 0;i < (1 << vl.size());i++) printf("%d ", dpr[i]);
	// puts("");
	int all = (1 << vl.size()) - 1;
	for (int i = 0;i < segl[0].size();i++) {
		int l = segl[0][i], r = segr[0][i];
		// printf("l=%d r=%d\n", l, r);
		bool flag = 0;
		for (int j = 0;j < (1 << vl.size());j++) {
			if (dpl[j] >= dpr[all ^ j] || (dpl[j] >= l - 1 && dpr[all ^ j] <= r + 1)) {
				flag = 1;
				break;
			}
			if (l == 1 && dpr[all ^ j] <= r + 1) {flag = 1; break;}
			if (r == n && dpl[j] >= l - 1) {flag = 1; break;}
		}
		for (int j = l;j <= r;j++) puts((flag ? "Possible" : "Impossible"));
	}
}

int main() {
	Read();
	Prefix();
	Solve();
	#ifndef ONLINE_JUDGE
	while (1);
	#endif
	return 0;
}
```

---

## 作者：biyi_mouse (赞：0)

你会发现只能任意跳 $\log v$ 次，并且再仔细分析一下会发现每次跳都会把所有能拓展的都拓展，即拓展一条区间。然后由于你可以任意跳结点，那么就相当于选 $\log v$ 条线段使得它们覆盖 $1 \sim n$。

考虑对于一个 $i$ 处理出 $F_s$ 表示当这 $\log v$ 个长度的选取情况为 $s$ 时，往左最远能到哪里，$G_s$ 为向右。这么做太慢了，考虑我们只关心能不能到达 $1$ 和 $n$，所以只需处理 $1$ 往右到的最远点和 $n$ 往左能到的最远点即可。

判定考虑如果 $F_s$ 能覆盖 $[1, i - 1]$，$G_s$ 能覆盖 $[r + 1, n]$ 就合法，其中 $r$ 是 $i$ 用 $v$ 的容量能到的最远点。

暴力判断还是 $\Theta(nv)$ 的，但是你注意到最初始 $v$ 分出了若干个连通块，块内的答案都一样，一个个块处理即可。由于我们只能随便跳 $\log v$ 次，所以合法情况下块数一定小于等于 $\log v$。复杂度就是 $\Theta(v\log v)$。

---

## 作者：Hoks (赞：0)

## 前言
第一次切这种题，纪念下。

看深进看到的练习题，没想到是黑（）

笑话是卡了好久最后发现不会分析复杂度（），对的东西给分析成错的了（）。

摘自 [杂题选做](https://www.luogu.com.cn/training/660942)。
## 思路分析
题意可以比较简单的化简出来。

显然的，如果不在一个绿洲起跳是没有意义的，肯定是在绿洲起跳更优。

所以现在就相当于是可以跳 $\lfloor\log v\rfloor$ 步，跳了 $k$ 步时最大行走距离可以是 $\lfloor\frac{v}{2^{k-1}}\rfloor$，然后对每个点球能不能拼成整一段。

再抽象一点，因为跳跃的步数 $k$ 是 $\log$ 级别的，所以很容易启发我们直接暴力地对每一步进行处理。

具体的，当我们限制了步数时，我们能走的最远的距离也是固定的，那么整一段就被划分为了若干条线段。

那么我们现在就是要找出 $\lfloor\log v\rfloor$ 条线段使得并集是整段。

而题目限制的出发点也就是限制了没跳跃的第一条线段的选择。

然后尝试刻画一个 dp 来解决这个东西。

那现在要考虑的就是，中间已经有一段有了，我们要拿剩下可能的线段拼出左右两段长段。

考虑到同一种步数的只能取一次和步数总种类数只有 $\log$，我们直接状压处理。

状压把左右两头的先预处理出来就行了，这步转移可以用高维前缀和优化枚举子集做到 $O(V\log V)$。

有了这个之后回答答案就很简单了，扫一遍所有可能的线段，然后尝试每种状态组合，也就是状态 $j$ 的线段全部用在左边，剩下的全部用在右边能不能拼出来就行了。

这样的复杂度就是 $O(sV)$，其中 $s$ 是我们要扫的全部可能的线段数。

~~然后我就分析错复杂度了~~。

显然的我们知道最多只能跳 $\lfloor\log v\rfloor$ 步，所以最多只能有 $\lfloor\log v\rfloor$ 条不同的线段，这样 $s=\lfloor\log v\rfloor$，复杂度显然是对的。

实现上也很简单，不知道为什么第一篇题解用了 pair 和 unique。

线段之间显然不会重，扫左端点判一遍就做完了。

貌似也没啥细节。
## 代码

```cpp
#include <bits/stdc++.h>
#define ls (p<<1)
#define rs (ls|1)
#define mid ((l+r)>>1)
#define int long long
using namespace std;
const int N=2e5+10,V=8e5,M=20,mod=998244353,INF=2e9,lim=19;
int n,v,d,cnt,a[N],l[M][N],r[M][N],f[V],g[V],tag[N];
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(long long x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c=='#'||c=='.'||c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'||c=='+'||c=='-'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
inline void solve()
{
    n=read(),v=read();for(int i=1;i<=n;i++) a[i]=read();a[0]=-INF;a[n+1]=INF;
    for(int w=v;w>=0;w>>=1,d++)
    {
        r[d][n+1]=n+1;
        for(int i=1;i<=n;i++) l[d][i]=(a[i]-a[i-1]<=w)?l[d][i-1]:i;
        for(int i=n;i>=1;i--) r[d][i]=(a[i+1]-a[i]<=w)?r[d][i+1]:i;
        if(w==0){d++;break;}
    }for(int i=1,j;i<=n;){j=i+1;while(l[0][j]==l[0][i]) j++;i=j;cnt++;}
    if(cnt>d) goto play;for(int i=0;i<(1<<d);i++) g[i]=n+1;
    for(int j=0;j<(1<<d);j+=2) for(int i=1;i<d;i++)
    {
        if(!(j&(1<<i))) continue;
        f[j]=max(f[j],r[i][f[j^(1<<i)]+1]);
        g[j]=min(g[j],l[i][g[j^(1<<i)]-1]);
    }for(int i=1;i<=n;i++) if(l[0][i]!=l[0][i-1]) for(int j=0;j<(1<<d);j+=2)
        if(f[j]>=l[0][i]-1&&g[(1<<d)-1-j-1]<=r[0][i]+1) tag[l[0][i]]=1;play:;
    for(int i=1;i<=n;i++) put(tag[l[0][i]]?"Possible\n":"Impossible\n");
}
signed main()
{
    int T=1;
    // T=read();
    while(T--) solve();
    flush();return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/AT_agc012_e)

**题目大意**

> 数轴上有 $n$ 个点 $a_1\sim a_n$，当前移动距离上限为 $x$，每次操作可以移动到距离当前点 $\le x$ 的 $a_i$ 上，或者令 $x\gets \lfloor x/2\rfloor$ 后移动到任意一点上，对每个 $a_i$ 求从当前点出发能否遍历所有点。
>
> 数据范围：$n,x\le 2\times 10^5$。

**思路分析**

容易发现瞬移操作最多进行 $\mathcal O(\log V)$ 次。

并且每次瞬移后会把当前点左侧和右侧距离 $\le x$ 的点全部遍历，相当于覆盖一个区间的点。

那么我们需要在 $\log V$ 个线段集合中各选择一个，覆盖 $[1,n]$ 中的所有点。

可以用 dp 解决，$f_S$ 表示在 $S$ 对应的集合中选过线段，覆盖的前缀长度最大值，有解要求 $f_U=n$。

要对每个起点求答案，相当于钦定了第一个集合中选择的线段，那么我们分别计算 $f_S,g_S$ 表示用 $S$ 中线段覆盖的前缀、后缀长度最大值。

求答案时枚举 $S$ 即可，但此时要枚举 $\mathcal O(n)$ 次，不可接受，但我们发现同一条线段内的只需要枚举一次，并且初始线段个数 $>\log V$ 时一定无解，因此只要枚举 $\mathcal O(\log V)$ 次。

时间复杂度 $\mathcal O((n+V)\log V)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5+5;
int n,m,K,V[20],a[MAXN],lp[20][MAXN],rp[20][MAXN],f[1<<20],g[1<<20],t[MAXN];
signed main() {
	scanf("%d%d",&n,&K);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
	for(int i=K;i;i>>=1) V[m++]=i;
	V[m++]=0;
	for(int k=0;k<m;++k) {
		lp[k][1]=1,rp[k][n]=n;
		for(int i=2;i<=n;++i) lp[k][i]=(a[i]-a[i-1]>V[k])?i:lp[k][i-1];
		for(int i=n-1;i;--i) rp[k][i]=(a[i+1]-a[i]>V[k])?i:rp[k][i+1];
	}
	for(int s=0;s<(1<<m);++s) {
		f[s]=0,g[s]=n+1;
		for(int i=0;i<m;++i) if(s>>i&1) {
			f[s]=max(f[s],rp[i][f[s^(1<<i)]+1]);
			g[s]=min(g[s],lp[i][g[s^(1<<i)]-1]);
		}
	}
	int q=0;
	for(int i=1;i<=n;++i) if(i==n||a[i+1]-a[i]>K) t[++q]=i;
	if(q>m) {
		for(int i=1;i<=n;++i) puts("Impossible");
		return 0;
	}
	for(int i=1;i<=q;++i) {
		int U=(1<<m)-2; bool ok=0;
		for(int s=0;s<(1<<m);++s) if(!(s&1)&&t[i-1]<=f[s]&&g[U^s]<=t[i]+1) {
			ok=1; break;
		}
		for(int j=t[i];j>t[i-1];--j) puts(ok?"Possible":"Impossible");
	}
	return 0;
}
```

---

## 作者：happybob (赞：0)

跳到任意一个位置是奇怪的，不容易刻画。但是简单观察一下就会发现走过的轨迹必然是形如初始和每次跳跃后走完一段极大区间，然后跳到没走过的区间外一个点，继续走区间，跳跃。

所以问题转化为对于每个 $i$，先按照上限为 $V$ 走完对应极大区间，问剩下的能否分为若干区间。这里每个区间都对应一种新的上限，分别是 $\lfloor \dfrac{V}{2} \rfloor,\lfloor \dfrac{V}{4} \rfloor,\cdots$。

这些上限的个数是 $O(\log V)$ 级别的。于是考虑状压 DP，记 $f_{S}$ 和 $g_{S}$ 表示用 $S$ 这个集合中的上限能覆盖的最长连续前缀和后缀。转移可以通过预处理每种上限的连续段做到 $O(1)$。问题在于怎么判定。

判定等价与找到 $S$ 使得 $f_S \geq l_i - 1$ 且 $g_{\bar{S}} \leq r_i+1$。这显然是一个二维数点的问题，离线下来扫描线即可。总复杂度 $O(n \log n)$。

代码：


```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <cassert>
#include <array>
using namespace std;

const int N = 2e5 + 5, M = 21;

int n, v;
array<int, N> x;
array<int, 1 << M> f, g;
vector<int> seq;
array<array<int, M>, N> pr, pl;

vector<int> yx[N];

vector<int> qry[N];
array<bool, N> ans;
array<int, N> L, R;

class Bit
{
public:
	array<int, N> tr;
	void update(int x, int v)
	{
		x++;
		while (x < N) tr[x] += v, x += x & -x;
	}
	int query(int x)
	{
		x++;
		int res = 0;
		while (x) res += tr[x], x -= x & -x;
		return res;
	}
}bt;

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> v;
	for (int i = 1; i <= n; i++) cin >> x[i];
	int rv = v / 2;
	while (rv >= 0)
	{
		seq.emplace_back(rv);
		if (!rv) break;
		rv >>= 1;
	}
	assert(seq.size() < M);
	sort(seq.begin(), seq.end());
	for (int j = 0; j < seq.size(); j++)
	{
		int len = seq[j];
		for (int i = 1; i <= n; i++)
		{
			for (int k = i + 1; k <= n + 1; k++)
			{
				if (k == n + 1 || x[k] - x[k - 1] > len)
				{
					for (int y = i; y < k; y++) pr[y][j] = k - 1;
					i = k - 1;
					break;
				}
			}
		}
		for (int i = n; i >= 1; i--)
		{
			for (int k = i - 1; k >= 0; k--)
			{
				if (k == 0 || x[k + 1] - x[k] > len)
				{
					for (int y = i; y > k; y--) pl[y][j] = k + 1;
					i = k + 1;
					break;
				}
			}
		}
	}
	for (int S = 0; S < (1 << (int)seq.size()); S++)
	{
		for (int lst = 0; lst < seq.size(); lst++)
		{
			if ((S >> lst) & 1)
			{
				f[S] = max(f[S], pr[f[S ^ (1 << lst)] + 1][lst]);
				if (f[S ^ (1 << lst)] == n) f[S] = n;
			}
		}
	}
	g.fill(n + 1);
	for (int S = 0; S < (1 << (int)seq.size()); S++)
	{
		for (int lst = 0; lst < seq.size(); lst++)
		{
			if ((S >> lst) & 1)
			{
				g[S] = min(g[S], pl[g[S ^ (1 << lst)] - 1][lst]);
				if (g[S ^ (1 << lst)] == 1) g[S] = 1;
			}
		}
	}
	for (int S = 0; S < (1 << (int)seq.size()); S++)
	{
		int x = f[S], y = g[(1 << (int)seq.size()) - S - 1];
		yx[x].emplace_back(y);
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = i + 1; j <= n + 1; j++)
		{
			if (j == n + 1 || x[j] - x[j - 1] > v)
			{
				for (int k = i; k < j; k++) R[k] = j - 1;
				i = j - 1;
				break;
			}
		}
	}
	for (int i = n; i >= 1; i--)
	{
		for (int j = i - 1; j >= 0; j--)
		{
			if (j == 0 || x[j + 1] - x[j] > v)
			{
				for (int k = j + 1; k <= i; k++) L[k] = j + 1;
				i = j + 1;
				break;
			}
		}
	}
	for (int i = 1; i <= n; i++)
	{
		qry[L[i] - 1].emplace_back(i);
	}
	for (int i = n + 1; i >= 0; i--)
	{
		for (auto& y : yx[i])
		{
			bt.update(y, 1);
		}
		for (auto& id : qry[i])
		{
			if (bt.query(R[id] + 1)) ans[id] = 1;
			else ans[id] = 0;
		}
	}
	for (int i = 1; i <= n; i++)
	{
		if (ans[i]) cout << "Possible\n";
		else cout << "Impossible\n";
	}
	return 0;
}
```

---

## 作者：lgswdn_SA (赞：0)

首先注意到每次跳 $V$ 减半所以不会跳超过 $k=\log V$ 次。

考虑 $V\le 2\times 10^5$ 这个很奇怪的范围，可以猜测做法大概会用到 $O(2^k)$ 的状压，即记录下已经用过了哪些 $v$。

一开始对整个序列建深度为 $k$ 的树形结构然后想树上 DP，但是发现根本无法合并。

于是考虑更简洁的直接从左到右 DP，$f_{s,x,i}$ 表示考虑目前已经用过的 $v$ 的集合是 $s$，目前的 $v=x$，能否到达 $i$。

显然 $f_{s,x,i}$ 的合法是一段前缀，直接记录 $f_{s,x}$ 表示能到达的最远的 $i$ 即可。转移是容易的。（实际上这个 $x$ 没什么用，可以直接省略掉，DP 的复杂度 $O(2^kk)$）。

考虑如何求出每一个点的答案。先求出同样的后缀的 DP 数组 $g_{s}$，那么对于一个点 $i$，其合法当且仅当存在一个 $S$ 不包含初始的 $V$ 且（令全集为 $T$） $f_{S\cup \{V\}}\ge i$ 且 $g_{T-S}\le i$。

那么我们直接枚举 $S$，那么可贡献到的 $i$ 一定是一段区间，直接差分即可。

复杂度 $O(2^kk)$。

（代码写丑了，多了个 $k$）

https://atcoder.jp/contests/agc012/submissions/55360949

---

## 作者：Sky_Maths (赞：0)

考虑状压 DP，一种不劣的最终方案是先从 $i$ 出发，向左向右分别走到 $v$ 能走到的最远处，然后因为存在左右反复跳，所以假设左边分别是 $\{\frac{v}{2^{d}}| d\in S\}$ 的区间的并集。

枚举 $S$，而对于每个 $S$ 可以覆盖的最大区间是一定的。

于是枚举左边区间占用的 $S$，设此时最多并到 $l - 1$，而其补集从右向左最多并到 $r + 1$，若从 $l$ 不跳，容量为 $v$ 可以到达 $r$，则从 $l$ 出发，不跳，容量为 $v$ 可以到达的所有点出发都是可全达的。

枚举的时候考虑恰好枚举到左边占用的集合，代码如下。

```cpp
rep (s, 0, all) {
	int l = f[s] + 1;
	int r = g[all ^ s] - 1;
	if (R[l][m] >= r) {
		++sum[l];
		--sum[R[l][m] + 1];
	}
}
rep (i, 1, n) {
	sum[i] += sum[i - 1];
	if (sum[i]) printf("Possible\n");
	else printf("Impossible\n");
}
```

---

