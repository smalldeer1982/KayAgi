# Summoning Minions

## 题目描述

Polycarp plays a computer game. In this game, the players summon armies of magical minions, which then fight each other.

Polycarp can summon $ n $ different minions. The initial power level of the $ i $ -th minion is $ a_i $ , and when it is summoned, all previously summoned minions' power levels are increased by $ b_i $ . The minions can be summoned in any order.

Unfortunately, Polycarp cannot have more than $ k $ minions under his control. To get rid of unwanted minions after summoning them, he may destroy them. Each minion can be summoned (and destroyed) only once.

Polycarp's goal is to summon the strongest possible army. Formally, he wants to maximize the sum of power levels of all minions under his control (those which are summoned and not destroyed).

Help Polycarp to make up a plan of actions to summon the strongest possible army!

## 说明/提示

Consider the example test.

In the first test case, Polycarp can summon the minion $ 2 $ with power level $ 7 $ , then summon the minion $ 1 $ , which will increase the power level of the previous minion by $ 3 $ , then destroy the minion $ 1 $ , and finally, summon the minion $ 5 $ . After this, Polycarp will have two minions with power levels of $ 10 $ .

In the second test case, Polycarp can control only one minion, so he should choose the strongest of them and summon it.

In the third test case, Polycarp is able to summon and control all five minions.

## 样例 #1

### 输入

```
3
5 2
5 3
7 0
5 0
4 0
10 0
2 1
10 100
50 10
5 5
1 5
2 4
3 3
4 2
5 1```

### 输出

```
4
2 1 -1 5
1
2
5
5 4 3 2 1```

# 题解

## 作者：nofind (赞：16)

## [题意](https://www.luogu.com.cn/problem/CF1354F)

贪心地想整个过程，我们必然是先选出$m-1$个，之后将$(n-m)$加入后立刻删除，对综合产生$b*(m-1)$的贡献，最后添加一个凑够$m$个。且选出的$m$个的$b$必定是递增的，于是我们可以按照$b$排序后进行$DP$。

设$f_{i,j}$表示前$i$个，选出了$j$个留到最后的最大价值。转移考虑第$i$个是否留到最后即可。

复杂度：$O(Tnm)$。

code:
```
#include<bits/stdc++.h>
using namespace std;
const int maxn=80;
int n,m;
int a[maxn],b[maxn],id[maxn];
int f[maxn][maxn],g[maxn][maxn];
bool used[maxn];
inline int read()
{
    char c=getchar();int res=0,f=1;
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9')res=res*10+c-'0',c=getchar();
    return res*f;
}
inline bool cmp(int x,int y){return b[x]<b[y];}
void dfs(int n,int m)
{
	if(!n)return;
	if(g[n][m])used[n]=1,m--;
	dfs(n-1,m);
}
inline void solve()
{
	n=read(),m=read();
	for(int i=1;i<=n;i++)a[i]=read(),b[i]=read(),id[i]=i;
	sort(id+1,id+n+1,cmp);
	memset(f,0xcf,sizeof(f));
	memset(g,0,sizeof(g));
	f[0][0]=0;
	for(int i=1;i<=n;i++)
		for(int j=0;j<=min(i,m);j++)
		{
			f[i][j]=f[i-1][j]+b[id[i]]*(m-1),g[i][j]=0;
			if(j&&f[i-1][j-1]+a[id[i]]+b[id[i]]*(j-1)>f[i][j])
				f[i][j]=f[i-1][j-1]+a[id[i]]+b[id[i]]*(j-1),g[i][j]=1;
		}
	memset(used,0,sizeof(used));
	dfs(n,m);
	printf("%d\n",m-1+(n-m)*2+1);
	int last=0;
	for(int i=1;i<=n;i++)
	{
		if(!used[i])continue;
		last++;
		if(last==m){last=id[i];break;}
		printf("%d ",id[i]);
	}
	for(int i=1;i<=n;i++)
	{
		if(used[i])continue;
		printf("%d %d ",id[i],-id[i]);
	}
	printf("%d\n",last);
}
int main()
{
	int T=read();
	while(T--)solve();
	return 0;
}
```


---

## 作者：yuzhechuan (赞：10)

提供一个效率低下，但代码好写易理解的费用流做法（好写是基于你有板子）

---

### 题解：

首先是一个贪心的想法：不管有没有贡献，每张牌肯定是要被选一次的

其次是另一个贪心想法：先放好$k-1$张牌，然后在最后一个空位上对$n-k$张牌进行放置+删除，最后再把剩余的一张牌放在空位上

有了上面的两个贪心想法后，问题就转化为决定$n$张牌的摆放顺序，且一个顺序的不同位置有不同的贡献

设牌为左部点，拜访序号为右部点，这就变成了一个二分图带权最大匹配问题了，我们可以用费用流解决

对于中间的边，有三种情况：

* 右部点序号 $i\in [1,k)$ ，贡献为 $a+(i-1)*b$ ，表示自己的初值有用且对前面的造成贡献

* 右部点序号 $i\in [k,n)$ ，贡献为 $(k-1)*b$ ，自己初值无用，但对前面的有贡献

* 右部点序号 $i=n$ ，贡献为 $a+(k-1)*b$ ，同情况1

对于答案的处理，我们可以在残量网络上直接看看谁与谁匹配就行了

---

### 代码：

```cpp
#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC target("avx")
#include <bits/stdc++.h>
using namespace std;
#ifdef ONLINE_JUDGE
#define getchar gc
inline char gc(){
	static char buf[1<<16],*p1=buf,*p2=buf;
	if(p1==p2){
		p2=(p1=buf)+fread(buf,1,1<<16,stdin);
		if(p2==p1) return EOF;
	}
	return *p1++;
}
#endif
template<class t> inline t read(t &x){
    char c=getchar();bool f=0;x=0;
    while(!isdigit(c)) f|=c=='-',c=getchar();
    while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
    if(f) x=-x;return x;
}
template<class t> inline void write(t x){
    if(x<0) putchar('-'),write(-x);
    else{if(x>9) write(x/10);putchar('0'+x%10);}
}

const int N=205,M=1e4+5,P=80;
int en=1,mc,mf,h[N],dis[N],n,k,ans[P];
bool v[N];

struct edge{
	int n,v,f,w;
}e[M<<1];

struct fafafa{
	int fa,id;
}pre[N];

void add(int x,int y,int f,int w){
	e[++en]=(edge){h[x],y,f,w};
	h[x]=en;
}

bool spfa(int s,int t){
	memset(v,0,sizeof v);
	memset(pre,0,sizeof pre);
	memset(dis,0x3f,sizeof dis);
	queue<int> q;
	q.push(s);
	v[s]=1;
	dis[s]=0;
	while(!q.empty()){
		int x=q.front();
		q.pop();
		for(int i=h[x];i;i=e[i].n){
			int y=e[i].v;
			if(e[i].f&&dis[x]+e[i].w<dis[y]){
				dis[y]=dis[x]+e[i].w;
				pre[y]=(fafafa){x,i};
				if(!v[y]){
					v[y]=1;
					q.push(y);
				}
			}
		}
		v[x]=0;
	}
	return dis[t]^0x3f3f3f3f;
}

void mcmf(int s,int t){
	while(spfa(s,t)){
		int flow=INT_MAX;
		for(int i=t;i^s;i=pre[i].fa)
			flow=min(flow,e[pre[i].id].f);
		for(int i=t;i^s;i=pre[i].fa){
			e[pre[i].id].f-=flow;
			e[pre[i].id^1].f+=flow;
		}
		mf+=flow;
		mc+=flow*dis[t];
	}
}

void exadd(int x,int y,int f,int w){
	add(x,y,f,w);
	add(y,x,0,-w);
}
//上面是模板
void doit(){
	read(n);read(k);
	for(int i=1;i<=n;i++) exadd(0,i,1,0),exadd(i+n,n*2+1,1,0); //左右的边
	for(int i=1,a,b;i<=n;i++){
		read(a);read(b);
		for(int j=1,val;j<=n;j++){ //连中间的边
			if(j<k) val=a+(j-1)*b;
			else if(j<n) val=(k-1)*b;
			else val=a+(k-1)*b;
			exadd(i,j+n,1,-val);
		}
	}
	mcmf(0,n*2+1);
	write(k+(n-k)*2);puts("");
	for(int x=1;x<=n;x++)
		for(int i=h[x];i;i=e[i].n){
			int y=e[i].v;
			if(y<=n) continue;
			if(!e[i].f) ans[y-n]=x; //残量网络上看一看谁配了谁
		}
	for(int i=1;i<=n;i++){
		write(ans[i]);putchar(' ');
		if(i>=k&&i<n) write(-ans[i]),putchar(' '); //直接放了就删的
	}
	puts("");
	en=1;mc=mf=0; //重置
	for(int i=0;i<=n*2+1;i++) h[i]=0;
}

signed main(){
	int t;
	read(t);
	while(t--) doit();
}
```

---

## 作者：45dinо (赞：4)

一个挺诡异的题目，但比想象中的简单一点。

~~CF怎么这么喜欢出和游戏有关的题目，以前是MC现在是炉石，不过CF本来就是游戏（雾~~

很快能看出最优的情况：前 k-1 张牌一开始就放，保留到最后，中间 n-k 张牌用了就扔，只触发战吼，最后一张牌直接放。

然后就有两类牌：一类是留到最后的，对答案的贡献为 $a_i+b_i\times q$，另一类就是用了就扔的，对最后的贡献为 $b_i\times (k-1)$。

（q 指的是放这张牌时，场上有 q 个随从，q 的取值为 0~k-1 。）

然后发现有两类牌，一类只和战吼有关，另一类和原等级，战吼都有关，还有参数。~~所以果断放弃，重新找一场比赛，接着水签到题~~

发现一个可以化简的机会：先将每一张牌的 $b_i\times (k-1)$ 加入最后，发现用了就扔的牌已经算过了，剩下的只有留到最后的，代价是 $a_i-b_i\times (k-q-1)$ ，发现 k-q-1 正好也是 0~k-1，于是就把两个很棘手的问题便乘了一个更棘手的问题。

此时发现如果确定了 k 张留到最后的牌，要使贡献最大，肯定是让 $b_i$ 较大的牌对应较大的 q。

所以把 $b_i$ 从大到小排序，令 $f_{i,j}$ 表示处理到第 i 个，先前有 j 张牌已经保留。

可以推出状态转移方程：
$$f_{i,j}=\max(f_{i-1,j},f_{i-1,j-1}+a_i-b_i\times (j-1))$$

但注意最后求的是方案，所以在转移的同时还要记录转移路径。

说句闲话：如果这道题再复杂一点，比如再加亡语之类的机制，或许可以成为下一个《猪国杀》——《金色传说！》

---

## 作者：皎月半洒花 (赞：4)

upd: 改了错别字

旁白：这个 F 怎么也这么签啊？

____

~~盲猜这个游戏是炉石~~

赛场上一眼背包，发现大概是 $O(\max\{a_i,b_i\}\cdot nk^2)$ 的就弃掉了。然后考虑贪心。考虑这么一个比较自然的想法，就是先找出前 $k-1$ 个来，然后 $n-k$ 个加一个删一个，最后再把 $1$ 个加进来。不难知道这样一定可以做出最优的决策。

那么考虑怎么搞这三部分。

第一部分可以背包，$f_{i,j}$ 表示前 $i$ 个随从找出了 $j$ 个放进第一个部分的最大价值。注意这个地方有一个代价提前计算的思想。就是说考虑如果把随从 $z$ 在前 $k-1$ 个里的第 $j$ 位召唤出来，那么放到后面应该是产生 $(k-1)\cdot b_z$ 的贡献，现在就只有 $(j-1)\cdot b_z$ 的贡献，于是有

$$
f_{i,j}=\max\left\{f_{i-1,j-1}-(k-j)\cdot b_i+a_i,f_{i-1,j}\right\}
$$

然后一个小细节就是显然必须要按照 $a_i$ 降序且 $b_i$ 升序来进行排序，同时由于是对 $a_i$ 来 $dp$，所以应该让 $b_i$ 为第一关键字。 

第二、三部分考虑合起来做。即考虑枚举最后一个随从，那么剩下的元素就一定是按照 $b_z$ 升序排序，因为他们加入就会被立即删掉。

但这样会发现 `WA ON 2`。冷静一下就会发现最后一个元素由于也要计算其 $a_i$ ，所以应该和前面的 $k-1$ 个等价，换言之最后在剩下的元素里贪出最后一个位置放的随从是不对的。观察数据范围很小，于是可以枚举最后一个位置放哪个随从，对于不同的最后一个位置分别做前两部分。不难知道这样是对的。

这样最后复杂度 $O(T\cdot n^2k)$，可以通过本题。

瞎扯1：

这么看来这个复杂度还是很合理的？$75^4$ 大概在 $3e7$ 左右。

瞎扯2：

实际上场上写的时候并没有细想第一部分到底该怎么排序，那反正就是要么 $a_i$ 做第一关键字要么 $b_i$ 做第一关键字。看着当时似乎没多少人过 F 就选择 $2!$ 枚举了一下这两种排法（

瞎扯3:

为什么这场比较正常的题 (E 以及 E 之后) 都这么无聊但是代码这么麻烦？反正我写的挺麻烦的。

```cpp

int T ;
struct minion{
    int a, b, id ;
}base[N], tmp[N] ;
int n, k ;
int cnt ;
int ans ;
int lst ;
int ud[N] ;
int fin[N] ;
int quq[N] ;
int qaq[N] ;
int qwq[N] ;
int f[N][N] ;
int pre[N][N] ;

bool comp(minion x, minion y){
    return x.b == y.b ? x.a > y.a : x.b < y.b ;
}
bool cop(minion x, minion y){ return x.b < y.b ; }
int main(){
    cin >> T ;
    while (T --){
        cin >> n >> k ; ans = 0 ;
        for (int i = 1 ; i <= n ; ++ i)
            base[i].a = qr(), base[i].id = i, base[i].b = qr() ;
        sort(base + 1, base + n + 1, comp) ;
        fill(fin, fin + n + 1, 0) ;
        for (int z = 1 ; z <= n ; ++ z){
            memset(f, -63, sizeof(f)) ;
            fill(ud, ud + n + 1, 0) ;
            f[0][0] = 0 ; cnt = 0 ;
            for (int i = 1 ; i <= n ; ++ i){
                for (int j = 0 ; j <= k - 1 ; ++ j){
                    int tmp = base[i].b * (j - k)  ;
                    if (!j || i == z)
                        f[i][j] = f[i - 1][j], pre[i][j] = 0 ;
                    else {
// cout << i << " " << j << " " << f[i - 1][j] << " " << f[i - 1][j - 1] + base[i].a + tmp << '\n' ;
                        if (f[i - 1][j] > f[i - 1][j - 1] + base[i].a + tmp)
                            f[i][j] = f[i - 1][j], pre[i][j] = 0 ;
                        else f[i][j] = f[i - 1][j - 1] + base[i].a + tmp, pre[i][j] = 1 ;
                    }
                }
            }
            int p = n, q = k - 1 ;
            while (p && q){
                if (!pre[p][q]) -- p ;
                else qaq[q] = p, ud[base[p].id] = 1, -- q, -- p ;
            }
//            debug(q) ;
            debug(ud, 1, n) ;
            for (int i = 1 ; i <= n ; ++ i)
                if (!ud[base[i].id] && i != z) qwq[++ cnt] = i ;
            int res = 0, gz = 0 ;
            for (int j = 1 ; j <= cnt ; ++ j) tmp[++ gz] = base[qwq[j]] ;
            sort(tmp + 1, tmp + gz + 1, cop) ;
            for (int j = 1 ; j <= gz ; ++ j) res += (k - 1) * tmp[j].b ;
            for (int j = 1 ; j <= k - 1 ; ++ j)
                res += base[qaq[j]].a + (j - 1) * base[qaq[j]].b ;
            res += base[z].a + base[z].b * (k - 1) ;
            debug(res) ;
//            for (int j = 1 ; j <= k - 1 ; ++ j)
//                cout << base[qaq[j]].id << " \n"[j == k - 1] ;
            if (res >= ans) {
                ans = res, lst = z ;
                for (int i = 1 ; i <= k - 1 ; ++ i) quq[i] = qaq[i] ;
                for (int i = 1 ; i <= cnt ; ++ i) fin[i] = qwq[i] ;
            }
        }
//        debug(ans) ;
//        debug(cnt) ;
        cout << k + 2 * cnt << '\n' ;
        for (int i = 1 ; i <= k - 1 ; ++ i)
            cout << base[quq[i]].id << ' ' ;
        for (int i = 1 ; i <= cnt ; ++ i)
            cout << base[fin[i]].id << ' ' << -base[fin[i]].id << ' ' ;
        cout << base[lst].id << "\n" ;
    }
    return 0 ;
}/*
1
5 2
3538 43176
24258 77210
92123 70606
44495 37855
65913 67119
291273
8
3 4 -4 2 -2 1 -1 5
4 2 -2 5 -5 1 -1 3
*/
```

---

## 作者：Suiseiseki (赞：2)

#### Solution 1
暴力枚举全排列，时间复杂度$O(T \cdot n!)$。
#### Solution 2
由贪心很容易知道桌上肯定放满$k$张卡牌时最优，考虑如果固定了桌上最后的$k$卡牌，求出最大方案。可以将这$k$张卡牌的$b_i$值从小到大排序，然后先取前$k-1$张挨个放在桌上，再将剩下的$n-k$张不是最后在桌上的卡牌放一个销毁一个，再将最后一张卡牌放在桌上。若枚举最后的$k$张卡牌，时间复杂度$O(T\cdot n\binom{n}{k})$。
#### Solution 3
因为我们发现对于固定任意$k$张卡牌操作顺序是不变的，所以可以建立二分图模型，左侧是卡牌，右侧是位置，然后中间连上边，边权给什么值很简单，这里就不列了。用 Dinic 算法来求解，时间复杂度$O(\text{不可过})$。
#### Solution 4
对于 Solution 3 的求解过程采用 KM 算法，时间复杂度$O(T\cdot n^3)$。
#### Solution 5
考虑动态规划，先将$b_i$从小到大排序，这样的话 DP 在桌上的卡片时就可以决定它的位置了。设$f_{i,j}$表示当前决策到第$i$个位置，桌上已经确定了$j$张卡牌的最大价值，转移方程显然，然后构造方案输出即可，时间复杂度$O(T\cdot n^2)$。

Solution 3~5 的代码可以去我的博客查看：[Codeforces 1354F. Summoning Minions 题解](https://www.cnblogs.com/withhope/p/12913892.html)

---

## 作者：luogubot (赞：1)

特殊考虑最后一张卡一定是在只有一个坑的时候填进来，是特殊的，先忽视它。

假设已经知道了保留的另外 $k-1$ 张卡的集合 $S$，没放入的卡集合为 $T$，那么它们为了吃到最多的 $b_i$ 的加成肯定最先放入，并且它们内部的顺序一定是按照 $b$ 从小到大加入的，这样大的能给更多留下来的卡加成，再考虑最后一张的额外贡献只有一个 $a$，那么贪心选择最大的即可，则答案为：
$$
\sum_{i\in S}a_i+\sum_{i\in S}b_i\times (i-1)+(k-1)\sum_{j\in T}b_j+\max_{j\in T}\{a_j\}
$$
其中 $S$ 中按照 $b$ 从小到大的顺序排列。

唯一影响 dp 顺序的点在于 $b_i$ 的系数是 $i-1$，其中 $i$ 是它在 $S$ 中的排名，那么我们初始就把所有 $(a_i,b_i)$ 按照 $b$ 从小到大排序，第 $j$ 个加入 $S$ 的贡献就是 $a_i+b_i\times (j-1)$，不加入的贡献是 $(k-1)b_i$，另外再把不加入的最大的 $a$ 的下标 $k$ 压入状态，即状态为 $f_{i,j,k}$ 表示前 $i$ 个数中选了 $j$ 个放入 $S$，当前 $T$ 中最大的是 $a_k$，直接 dp 并记录前驱即可，复杂度 $O(Tn^2k)$。

虽然能过，但是 $k$ 一维可以从记录下标改为 $0/1$ 表示是否确定了放在最后一个位置的 $a_j$，这样对于同样的 $T$，选择 $T$ 中的最大值的方案会在转移中替代掉更劣的选择非最大值的方案，可以证明也是对的，这样复杂度就是 $O(Tnk)$。

代码没写。

---

## 作者：SegT (赞：0)

## 前言

能不能降黄啊。不懂为什么是 2500* 啊。

题面是炉石传说吗。

## 解题思路

由于 $a_i,b_i\geq 0$，显然不选满 $m$ 个随从一定不优。

考虑对于一个已经确定的选择留到最后的 $m$ 个随从的情况，确定一个部署时刻顺序。不难发现如果只考虑这 $m$ 个随从，第 $i$ 个随从的最终贡献为 $a_i+(i-1)b_i$，显然按照 $b$ 升序的顺序部署随从一定最优。

接下来考虑剩余 $(n-m)$ 个未被选择的随从，不难发现，其在加入 $(m-1)$ 个随从后被部署然后销毁会对最终答案产生 $(m-1)b_i$ 的贡献。

考虑 DP。先将所有随从按照 $b$ 升序排序。

记 $f_{i,j}$ 表示考虑到第 $i$ 个随从，已经选择了 $j$ 个随从的最大答案。

转移显然为 $f_{i,j}=\max(f_{i-1,j}+b_i(m-1),f_{i-1,j-1}+a_i+b_i(j-1))$。

记录转移路径就可以得到最优解中哪些随从被选择，模拟操作即可。

时间复杂度 $O(Tn^2)$。

---

## 作者：happybob (赞：0)

我是无脑费用流选手。

贪心地，我们必然会先选择 $k-1$ 个 $i$，按照 $b$ 小到大排序依次插入。然后还剩 $n-k+1$ 个数，每个数加入进来然后立马删除都有 $(k-1)b_i$ 的贡献，最后一个数还会多出 $a_i$ 的贡献。

考虑建立网络，左侧源点 $S$ 连到 $1\sim n$，容量为 $1$ 费用为 $0$，每个点 $i$ 连到右侧每个 $n+1\sim 2n$，容量为 $1$，费用是关于 $k$ 的式子。具体地，设右侧点为 $j$，左侧点为 $i$。若 $i \leq k$，贡献为 $(i-1)b_j+a_j$，否则贡献为 $(k-1)b_j$。然后右侧每个点连到汇点，容量为 $1$，费用为 $0$ 即可。跑最大费用最大流或者使用 KM 求最大权完美匹配即可。

[Submission Link.](https://codeforces.com/problemset/submission/1354/261310971)

---

## 作者：TernaryTree (赞：0)

很帅的题，但是做完一想好像又是很 trivial 的题。可能是不会贪心导致的！加训贪心。

---

首先，一定存在一种最优情况，是我们把这些牌全部加进去一次（可能中途拿出）。证明：$b_i\ge 0$，所以在能加牌的情况下加入一张牌不会有负收益。

其次，加一张牌，显然我们要让它底下的牌尽可能多，这样我们就可以用一个尽可能多的系数，即底下的牌数，去乘上当前这张牌的 $b_i$，算到答案里面。

假设我们 $k$ 足够大，那么根据排序不等式，我们要让 $b_i$ 较大的晚一点加入牌堆里，我们按 $b_i$ 排序，则此时的最优方案一定是按 $b_i$ 从小到大依次加入。

然而，$k$ 无法容下所有的牌。这种情况怎么办呢？我们考虑从 $n$ 张牌里面找出 $k$ 张牌，先把这 $k$ 张牌按 $b_i$ 从小到大排序，将前 $k-1$ 个加入牌堆；随后，将没被选中的 $n-k$ 张牌依次进行“加入”“取出”的操作，这样对底下至多的 $k-1$ 张牌都产生了 $b_i$ 的贡献，一定比牌堆还没达到 $k-1$ 时就进行这种操作来的优。最后，将选中 $k$ 张牌中最后的唯一一张放进牌堆，实际贡献与那 $k-1$ 张相同。

这些牌按 $b_i$ 升序加入的顺序，指引我们去做一个 dp 算最优情况。具体地，首先按 $b_i$ 排序，$f_{i,j}$ 表示前 $i$ 张牌里面，我们选了 $j$ 张，作为首先加入牌堆的 $k$ 张的前 $j$ 张。则我们有

$$

f_{i,j}=\max(
\mathop{f_{i-1,j-1}+a_i+b_i(j-1)}\limits_{\text{选 }i \text{，对答案有自己本身权值 }a_i\text{ 和对底下 } j - 1 \text{ 张牌的贡献}},
\mathop{f_{i-1,j}+b_i(k-1)}\limits_{\text{不选 }i\text{，对底下 } k-1 \text{ 张牌都有贡献}}
)

$$

嗯做一个这样的转移，然后从 $f_{n,k}$ 倒着推回去判断哪些选了哪些没选，再根据上文的贪心思路复原操作序列即可。

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int maxn = 1e2 + 10;

struct card {
	int a, b, id;
	card() = default;
};

int T, n, k;
card w[maxn];
int f[maxn][maxn];
vector<int> c, d, op;

void dfs(int i, int j) {
	if (!i) return;
	if (f[i][j] == f[i - 1][j - 1] + w[i].a + (j - 1) * w[i].b) {
		dfs(i - 1, j - 1);
		c.push_back(w[i].id);
	} else {
		dfs(i - 1, j); 
		d.push_back(w[i].id);
	}
}

signed main() {
	cin >> T;
	while (T--) {
		cin >> n >> k;
		for (int i = 1; i <= n; i++) {
			cin >> w[i].a >> w[i].b;
			w[i].id = i;
		}
		sort(w + 1, w + 1 + n, [] (card x, card y) {
			return x.b < y.b;
		});
		memset(f, -0x3f, sizeof(f));
		f[0][0] = 0;
		for (int i = 1; i <= n; i++) {
			for (int j = 0; j <= min(k, i); j++) {
				if (j) f[i][j] = max(f[i][j], f[i - 1][j - 1] + w[i].a + (j - 1) * w[i].b);
				f[i][j] = max(f[i][j], f[i - 1][j] + (k - 1) * w[i].b);
			}
		}
		c.clear(), d.clear();
		dfs(n, k);
		op.clear();
		for (int i = 0; i + 1 < c.size(); i++) op.push_back(c[i]);
		for (int i : d) op.push_back(i), op.push_back(-i);
		op.push_back(c.back());
		cout << op.size() << endl;
		for (int i : op) cout << i << " ";
		cout << endl;
	}
	return 0;
}

```

---

## 作者：XL4453 (赞：0)

### $\text{Difficulty : 2500}$
---
### 解题思路：

考虑放牌的过程，由于所有的 $b_i\ge 0$，一定是先放入 $k-1$ 个进行保留，在将剩下的若干个不需要在最后保留的召唤并立即删除，最后召唤一个进行保留。

对于这个过程考虑每一个位置上的牌对于最后的答案的贡献，一开始的第 $i$ 个产生 $a+(i-1)\times b$ 的贡献，接下来的不保留的产生 $(k-1)\times b$ 的贡献，最后一个产生 $a+(k-1)\times b$ 的贡献。

然后发现，这本质上就是决定一个出牌的排列，每一个位置上对于 $a$ 和 $b$ 有不同的权值，要求最后的总合最大。

---

进一步探究位置与权值的关系，发现本质不同的位置只有两种，一种是产生 $(k-1)\times b$ 的位置的，还有一种是 $a+(i-1)\times b,i\in[1,k]$。

发现如果直接将这样的位置设计进状态并不好表示，主要的麻烦在于后者并不是完全一样的。可以强制令一开始选择的 $i$ 递减，这样将 $b$ 较大的优先选择一定更优，换言之，就是将所有的牌按照 $b$ 从大到小排序。

更具体地，设 $f_{i,j}$ 表示考虑到第 $i$ 张牌，已经放置了 $j$ 张第二类的牌能达到的最大价值。转移就直接分为种类进行就好了。

注意记录路径。


---
### 代码：

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define int long long
struct str{
	int a,b,id;
	bool operator < (str x)const{
		return b>x.b;
	}
}c[100];
int T,n,k,f[105][105],fr[105][105],now1,now2,v[105];
signed main(){
	scanf("%lld",&T);
	while(T--){
		scanf("%lld%lld",&n,&k);
		for(int i=1;i<=n;i++){
			scanf("%lld%lld",&c[i].a,&c[i].b);
			c[i].id=i;
		}
		sort(c+1,c+n+1);
		memset(f,0,sizeof(f));
		for(int i=1;i<=n;i++){
			f[i][0]=f[i-1][0]+(k-1)*c[i].b;
			fr[i][0]=0;
			for(int j=1;j<=min(i,k);j++){
				if(f[i][j]<f[i-1][j]+(k-1)*c[i].b){
					f[i][j]=f[i-1][j]+(k-1)*c[i].b;
					fr[i][j]=0;
				}
				if(f[i][j]<f[i-1][j-1]+c[i].a+(k-j)*c[i].b){
					f[i][j]=f[i-1][j-1]+c[i].a+(k-j)*c[i].b;
					fr[i][j]=1;
				}
			}
		}
		printf("%lld\n",2*n-k);
		now1=n;now2=k;
		while(now1>0){
			if(fr[now1][now2]==0)v[c[now1].id]=-1;
			else v[c[now1].id]=now2,now2=now2-1;
			now1--;
		}
		for(int i=k;i>=2;i--){
			for(int j=1;j<=n;j++)
			if(v[j]==i)printf("%lld ",j);
		}
		for(int i=1;i<=n;i++)
		if(v[i]==-1)
		printf("%lld %lld ",i,-i);
		for(int i=1;i<=n;i++)
		if(v[i]==1)
		printf("%lld\n",i);
	}
	return 0;
}
/*
1
5 4
7218 14839
86672 371
27951 29919
45367 11927
25534 52009

*/
```



---

