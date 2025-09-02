# [JOI 2021 Final] 地牢 3 / Dungeon 3

## 题目描述

有一栋层数为 $N+1$ 层的楼，这 $N+1$ 层编号为 $1 \sim N+1$。有 $M$ 个人，这 $M$ 个人编号为 $1 \sim M$。从第 $i$ 层移动到第 $i+1$ 层需要 $A_i$ 的能量值，并且你只能从第 $i$ 层移动到第 $i+1$ 层，不能反过来。

第 $1$ 层到第 $N$ 层都有一个商铺，第 $i$ 层的商铺可以从 $B_i$ 元使自己的能量加 $1$，可以多次使用商铺但是不能使得能量多于能量上限，其中第 $j$ 个玩家的能量上限为 $U_j$，每个人的初始能量均为 $0$。

第 $j$ 个人最开始在第 $S_j$ 层，他们要到达第 $T_j$ 层。

请回答每个人达到他们的目的地最少需要多少金币，或者指出无解。

## 说明/提示

#### 样例 1 解释

第 $1$ 个人无法到达第 $3$ 层。

第 $2$ 个人可以用如下方法到达第 $6$ 层：

- 第 $1$ 层用 $8$ 个金币让自己的能量值变为 $4$。
- 移动到第 $2$ 层能量变为 $1$。
- 第 $2$ 层用 $15$ 个金币让自己的能量值变为 $4$。
- 移动到第 $3$ 层能量变为 $0$。
- 第 $3$ 层用 $4$ 个金币让自己的能量值变为 $4$。
- 移动到第 $4$ 层能量为 $3$。
- 移动到第 $5$ 层能量为 $2$。
- 第 $5$ 层用 $2$ 个金币让自己的能量值变为 $4$。
- 移动到第 $6$ 层。

一共需要 $29$ 个金币。

#### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（11 pts）：$N,M \le 3000$。
- Subtask 2（14 pts）：$U_j$ 互相相等。
- Subtask 3（31 pts）：$T_j=N+1$。
- Subtask 4（44 pts）：无特殊限制。

对于 $100\%$ 的数据，$1 \le N,M,A_i,B_i \le 2 \times 10^5$，$1 \le S_j<T_j \le N+1$，$1 \le U_j \le 10^9$。

#### 说明

翻译自 [The 20th Japanese Olympiad in Informatics Final Round E ダンジョン 3 的英文翻译 Dungeon 3](https://www.ioi-jp.org/joi/2020/2021-ho/2021-ho-t5-en.pdf)。

## 样例 #1

### 输入

```
5 4
3 4 1 1 4
2 5 1 2 1
1 6 3
1 6 4
3 5 1
2 5 9```

### 输出

```
-1
29
3
22```

## 样例 #2

### 输入

```
10 10
1 8 9 8 1 5 7 10 6 6
10 10 2 8 10 3 9 8 3 7
2 11 28
5 11 28
7 11 28
1 11 18
3 11 18
8 11 18
4 11 11
6 11 11
10 11 11
9 11 5```

### 输出

```
208
112
179
248
158
116
234
162
42
-1```

## 样例 #3

### 输入

```
20 20
2 3 2 11 4 6 9 15 17 14 8 17 3 12 20 4 19 8 4 5
19 3 18 2 13 7 5 19 10 1 12 8 1 15 20 1 13 2 18 6
12 15 67
7 15 18
16 17 14
9 21 97
1 19 43
3 18 31
16 20 70
7 20 28
1 16 61
3 5 69
9 10 15
2 13 134
11 19 23
16 20 14
5 21 16
15 20 11
7 11 54
7 16 16
13 17 10
3 15 135```

### 输出

```
151
591
4
284
339
517
35
581
254
58
-1
178
519
-1
-1
-1
219
-1
-1
214```

# 题解

## 作者：Miko35 (赞：14)

### 题意

$n+1$ 个加油站，第 $i$ 与 $i-1$ 个之间距离 $a_i$ 个单位长度，第 $i$ 个加油站加单位油量需要花费 $b_i$ 的代价。

车只能向右走，走 $1$ 单位长度要用 $1$ 单位油量，用完不能走。加油不能超过油量上限。

$m$ 组询问，每次给出 $l,r,x$ 表示一辆车从 $l$ 走到 $r$ 并且油量上限为 $x$ 需要花费的最小代价。

$1 \leq n,m,a_i,b_i \leq 2\times 10^5$，$1 \leq x \leq 10^9$。

### 题解

感谢 @[クトリ](https://www.luogu.com.cn/user/25251) 大师的提点 /bx

---

令油量上限为 $u$，有一个贪心：找到当前位置后第一个价格比它小的位置 $x$，加油至能走到 $x$ 为止；若到 $x$ 的距离 $\ge u$，则加满 $u$ 然后往后走一步。

考虑如何维护这个贪心：固定右端点，从右往左扫描左端点，维护价格递减的单调栈（为方便表述，令栈中元素是位置），栈顶即要找的位置。令当前位置为 $i$，$i$ 加入单调栈后，策略的变化是用 $b_i$ 替换从 $i$ 到栈顶的前 $u$ 个单位的油，不足则全部替换。原因是，我找到原单调栈中与 $i$ 距离 $\ge u$ 的第一个位置，到达此位置时我一定没油，后面策略就不变了。

但询问的 $u$ 不等，就要讨论单调栈每一段的贡献。具体而言，假设我此时弹出 $x$，弹出后的栈顶为 $y$：

- $u\leq x-i$：无事发生，当然无贡献。
- $x-i<u$：将 $\min(u+i,y)-x$ 单位油的价格由 $b_x$ 替换为 $b_i$，贡献 $(b_i-b_x)(\min(u+i,y)-x)$。

容易发现这是个关于 $u$ 的分段一次函数，线段树可以维护，这样就解决 Subtask 3 了。

对于区间 $[l,r]$ 的询问，我们找出 $[r-u,r]$ 中最小价格的位置 $k$，则 $k$ 处的决策一定是加满油到走到 $r$ 为止，这段路与「从 $k$ 走到最后」的决策完全一致，所以 $\operatorname{ans}(l,r)=\operatorname{ans}(l,+\infty)-\operatorname{ans}(k,+\infty)+b_k(r-k)$。

只需要将右端点固定为最右边就可以算出 $\operatorname{ans}(i,+\infty)$，时间复杂度 $O(n \log n)$。


```cpp
#include<bits/stdc++.h>
#define pbk emplace_back
#define Mn(x,y) (b[x]<b[y]?x:y)
#define FOR(i,a,b) for(int i=(a);i<=(b);++i)
#define ROF(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
typedef long long ll;
const int N=2e5+7,LG=18;
int n,m,l,r,k,w,u[N],C,S[N],*c=S;
struct BIT{
	ll t[N],R;
	void upd(int x,ll v){for(;x<=C;x+=x&-x)t[x]+=v;}
	ll qry(int x){for(R=0;x;x&=x-1)R+=t[x];return R;}
}K,B;
ll d[N],D,sd[N][LG+1],mx,b[N],st[N][LG+1],ans[N];
struct qry{
	int t,v,id;
	qry(int L,int V,int ID){t=L,v=V,id=ID;}
	void work(){
		int h=lower_bound(u+1,u+C,t)-u;
		ans[id]+=v*(B.qry(h)+t*K.qry(h));
	}
};
vector<qry>q[N];
void mdf(int i,ll l,ll r,int vl){
	int L=lower_bound(u+1,u+C,l=d[l]-d[i])-u,R=lower_bound(u+1,u+C,r=d[r]-d[i])-u;
	B.upd(L,-vl*l),B.upd(R,vl*r),K.upd(L,vl),K.upd(R,-vl);
}
signed main(){
	scanf("%d%d",&n,&m);
	FOR(i,2,n+1)scanf("%lld",d+i),sd[i][0]=d[i],d[i]+=d[i-1];
	FOR(i,1,n)scanf("%lld",b+i),st[i][0]=i;
	st[1+n][0]=1+n;
	FOR(w,1,LG)FOR(i,1<<w,1+n){
		st[i][w]=Mn(st[i][w-1],st[i-(1<<(w-1))][w-1]);
		sd[i][w]=max(sd[i][w-1],sd[i-(1<<(w-1))][w-1]);
	}
	FOR(i,1,m){
		scanf("%d%d%d",&l,&r,u+i),k=w=r,D=0;
		ROF(j,__lg(w),0)if(w-(1<<j)>=l)D=max(D,sd[w][j]),w-=(1<<j);
		if(D>u[i]){ans[i]=-1;continue;}
		q[l].pbk(u[i],1,i),w=r;
		ROF(j,__lg(w),0)if(w-(1<<j)>=l-1&&d[r]-d[w-(1<<j)+1]<=u[i]){
			k=Mn(k,st[w][j]),w-=(1<<j);
		}
		q[k].pbk(u[i],-1,i),ans[i]=b[k]*(d[r]-d[k]);
	}
	sort(u+1,u+m+1),C=unique(u+1,u+m+1)-u,*c=n+1;
	ROF(i,n+1,1){
		for(;c!=S&&b[i]<b[*c];--c)mdf(i,*c,c[-1],-b[*c]);
		mdf(i,i,*c,b[i]),*(++c)=i;
		for(qry k:q[i])k.work();
	}
	FOR(i,1,m)printf("%lld\n",ans[i]);
	return 0;
}
```


---

## 作者：moongazer (赞：12)

首先有显然的贪心：对于一个位置 $i$ 找到他后面第一个价格小于它的位置 $j$，二者距离为 $L$，如果 $L\le U$，那就将能量填到 $L$，否则填满。

考虑 Subtask3 ($T=N+1$) 每次找后面小于它的位置可以联想到离线询问然后倒着扫用单调栈维护价格，每次退栈（当前的价格优于之前的价格）就考虑是否能在当前位置买能量，替代后面的，当前要购买的能量是已知的，考虑要删去多少：

设当前位置到栈顶的距离为 $L$，到栈顶下一个元素的距离为 $L^\prime$，如果 $L^\prime\le U$ 删去全部 $L^\prime-L$，否则 $L^\prime-U$ 是必须的，只能删去 $L^\prime-L-(L^\prime-U)=U-L$ 于是即为 $\min(L^\prime,U)-L$。

最后栈顶还要加上 $\min(L,U)$。

考虑用数据结构维护所有 $U$ 的值，我们发现我们要加的都是一条折线（一条斜线段在加上一条平行与 $x$ 轴的线段），我们发现这是可以用树状数组简单维护的，具体来说，设 $l$ 到 $r$ 是斜线段，斜率为 $k$，截距为 $b$，平行段的 $y$ 为 $c$，我们用一个树状数组维护斜率，另一个树状数组维护截距，用差分的思想给 $l$ 斜率加上 $k$，$r+1$ 斜率减去 $k$，$l$ 截距加上 $b$，$r+1$ 截距加上 $(r+1-l)\times k$。

然后考虑满分做法：设 $f(S,T)$ 为 $S$ 到 $T$ 的答案，我们找到距离 $T$ 小于等于 $U$ 的最小价格处 $m$ 发现只要经过 $m$ 就一定会在 $m$ 处买能量的，于是 $f(S,T)=f(S,N+1)-f(m,N+1)+dis(m,T)\times b_m$ 不用担心在 $m$ 之前买的能量没有用完的问题，这笔钱在 $f(m,N+1)$ 被减去又在后面被加上，但 $f(S,N+1)$ 中在 $m$ 前买的能量是一直有贡献的，用 ST 表找一下 $m$ 即可。

时间复杂度 $\operatorname{O}(n\log n)$。

```cpp
const int N = 200005;

namespace BIT {
ll BIT1[N], BIT2[N];
void update(ll l, ll r, ll x);
ll query(int x);
}  // namespace BIT

int getid(ll x);
pii queryA(int l, int r);
pii queryB(int l, int r);

std::vector<std::tuple<int, int, int>> Q[N];
int all[N], tot;
int lg2[N];
pii stA[20][N], stB[20][N];
ll ans[N];
ll X[N];
int sta[N], top;
int A[N], B[N];
int n, m;

int main() {
  read(n), read(m);
  for (int i = 1; i <= n; ++i) {
    read(A[i]);
    X[i + 1] = X[i] + A[i];
  }
  for (int i = 1; i <= n; ++i) read(B[i]);
  lg2[1] = 0;
  for (int i = 2; i <= n; ++i) lg2[i] = lg2[i >> 1] + 1;
  for (int i = 1; i <= n; ++i) {
    stA[0][i] = pii(A[i], i);
    stB[0][i] = pii(B[i], i);
  }
  for (int k = 1; k <= lg2[n]; ++k) {
    for (int i = 1; i <= n - (1 << k) + 1; ++i) {
      stA[k][i] = std::max(stA[k - 1][i], stA[k - 1][i + (1 << (k - 1))]);
      stB[k][i] = std::min(stB[k - 1][i], stB[k - 1][i + (1 << (k - 1))]);
    }
  }
  for (int i = 1; i <= m; ++i) {
    int s, t, u;
    read(s), read(t), read(u);
    if (queryA(s, t - 1).first > u) {
      ans[i] = -1;
      continue;
    }
    all[++tot] = u;
    int mid =
        queryB(std::max(s, static_cast<int>(std::lower_bound(X + 1, X + n + 2, X[t] - u) - X)),
               t - 1)
            .second;
    ans[i] = (X[t] - X[mid]) * B[mid];
    Q[s].emplace_back(i, 1, u);
    Q[mid].emplace_back(i, -1, u);
  }
  std::sort(all + 1, all + tot + 1);
  tot = std::unique(all + 1, all + tot + 1) - all - 1;
  sta[top = 1] = n + 1;
  for (int i = n; i >= 1; --i) {
    while (B[i] < B[sta[top]]) {
      BIT::update(X[sta[top]] - X[i] + 1, X[sta[top - 1]] - X[i], -B[sta[top]]);
      --top;
    }
    BIT::update(1, X[sta[top]] - X[i], B[i]);
    sta[++top] = i;
    for (const auto &[id, k, u] : Q[i]) ans[id] += k * BIT::query(u);
  }
  for (int i = 1; i <= m; ++i) {
    write(ans[i]), EL;
  }
  return 0;
}

pii queryA(int l, int r) {
  int k = lg2[r - l + 1];
  return std::max(stA[k][l], stA[k][r - (1 << k) + 1]);
}
pii queryB(int l, int r) {
  int k = lg2[r - l + 1];
  return std::min(stB[k][l], stB[k][r - (1 << k) + 1]);
}
int getid(ll x) { return std::lower_bound(all + 1, all + tot + 1, x) - all; }

namespace BIT {
void update(ll *A, int x, ll num) {
  while (x <= n) {
    A[x] += num;
    x += x & -x;
  }
}
ll query(ll *A, int x) {
  ll ans = 0;
  while (x) {
    ans += A[x];
    x -= x & -x;
  }
  return ans;
}
void update(ll l, ll r, ll x) {
  int idl = getid(l), idr = getid(r);
  update(BIT1, idl, x);
  update(BIT1, idr, -x);
  update(BIT2, idl, -(l - 1) * x);
  update(BIT2, idr, r * x);
}
ll query(int x) {
  int id = getid(x);
  return query(BIT1, id) * x + query(BIT2, id);
}
}  // namespace BIT
```


---

## 作者：7KByte (赞：4)

贪心神题。

手算一下不难得到 $\mathcal{O}(N^2)$ 的贪心。

我们从 $S$ 点出发，每次选择与当前点距离 $\le U$ 的 $B$ 最小的点，如果这个点的 $B$  比当前点小，则将能量填充至恰好到达该点，否则就将燃料填满。

直接二分可以做到 $\mathcal{O}(N^2)$ ,离线一下可以 $\mathcal{O}(N^2)$ 。

接下来是最关键的模型转换，我们将这个过程转化为线段覆盖的模型。

对于每一层，我们看成数轴上的一个点，相邻两点的距离就是 $A$ 。我们将第 $i$ 个点的位置记作 $S_i$

对于在第 $i$ 层恢复 $j$ 的能量，相当于以 $B_i$ 的单位代价覆盖线段 $[S_i,S_i+j]$ 。

$U_i$ 的限制条件，相当于以 $B_i$ 的单位代价，只能选择覆盖线段 $[S_i,S_i+U_i]$ 。

注意上面的覆盖不一定从 $S_i$ 开始，因为开始一段可以被前面的点覆盖。

那么如果 $U$ 是定值，我们只用开一个栈维护覆盖每个区间的最小的代价。时间复杂度 $\mathcal{O}(N\log N)$ 。

接着考虑子任务 $3$ ， $T_{i}=N+1$，非常明显地提示了考虑对询问按 $S$ 从大到小排序的离线。

$U$ 会变化，考虑观察一下当 $S,T$ 固定事，随着 $U$ 的变化答案会怎么变。

随着 $U$ 的增大，答案越来越小，对于每一层，都是先慢慢覆盖后面的一段，然后停滞不前，接着被前面更优的层覆盖（如果存在更优的），最后被完全覆盖。

这四部分都是关于 $U$ 的一次函数。

第一部分是形如 $y=kx(k>0)$ 的函数，对应的区间是从 $0$ 开始一直到，第 $i$ 层在碰到后面第一个 $B_j<B_i$ 的 $j$ 层之后停止。

第二部分是形如 $y=a$ 的函数，$a$ 是常数，对应的区间是停止向后扩展，但还没有被前面更优的区间覆盖。

第三部分是形如 $y=kx+b(k<0)$ ，的函数，对应的区间是当前层正在被前面第一个 $\le B_i$ 的区间覆盖。

被完全覆盖后的贡献为 $0$ ，这一部分可以省略。

这样我们运用子任务 $2$ 的单调栈找出每一层前面和后面的更优区间。然后倒叙枚举当前区间，用树状数组维护这若干个分段函数的和。

具体操作是用两个树状数组维护每一个位置此时的斜率和截距，$U$ 的范围很大，需要离散化。

对于 $T_i$ 任意的情况，考虑转化为子任务 $3$ 。

我们发现在 $[S_i,T_i]$ 中与 $T_i$ 的距离 $\le U_i$ 且 $B$ 最小的位置 $x$ ，覆盖 $[x,N+1]$ 时在 $T_i$ 后面的覆盖方案与 $[S_i,N+1]$ 相同，在$T_i$ 前面时是连续的一段，前者是子任务 $3$ ，后者可以 $\mathcal{O(1)}$ 求得。所以我们只用先二分出对应区间，然后用 **ST表** 找出位置 $x$ 。

这里给一章官方题解的图。

![](https://cdn.luogu.com.cn/upload/image_hosting/zgqitfsb.png)

时间复杂度 $\mathcal{O}(N\log N)$ 。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 200005
#define int long long
using namespace std;
int n,m,a[N],b[N],t,lg[N],c[2][N],o[N],u[N],T,s[N],sta[N],top,pr[N],nx[N],ans[N];
struct node{int s,t,u;}q[N];
namespace st1{
	int f[N][20];
	inline int ck(int x,int y){if(b[x]<b[y])return x;return y;}
	int ask(int l,int r){int cur=lg[r-l+1];return ck(f[l][cur],f[r-(1<<cur)+1][cur]);}
	void init(){
		rep(i,1,n+1)f[i][0]=i;
		rep(j,1,t)rep(i,1,n-(1<<j)+2)f[i][j]=ck(f[i][j-1],f[i+(1<<(j-1))][j-1]);
	}
}
namespace st2{
	int f[N][20];
	inline int ck(int x,int y){if(a[x]>a[y])return x;return y;}
	int ask(int l,int r){int cur=lg[r-l+1];return ck(f[l][cur],f[r-(1<<cur)+1][cur]);}
	void init(){
		rep(i,1,n+1)f[i][0]=i;
		rep(j,1,t)rep(i,1,n-(1<<j)+2)f[i][j]=ck(f[i][j-1],f[i+(1<<(j-1))][j-1]);
	}
}
inline void add(int op,int x,int val){for(;x<=T;x+=x&-x)c[op][x]+=val;}
inline int ask(int op,int x){int sum=0;for(;x;x-=x&-x)sum+=c[op][x];return sum;}
inline void change(int op,int l,int r,int k){
	if(l>r)return;
	l=lower_bound(u+1,u+T+1,l)-u;
	r=upper_bound(u+1,u+T+1,r)-u-1;
	add(op,l,k);add(op,r+1,-k);
}
vector<node>w[N];vector<int>dl[N];
signed main(){
	scanf("%lld%lld",&n,&m);t=log2(n+1);
	lg[0]=-1;rep(i,1,n)lg[i]=lg[i>>1]+1;
	rep(i,1,n)scanf("%lld",&a[i]),s[i+1]=s[i]+a[i];
	rep(i,1,n)scanf("%lld",&b[i]);
	st1::init();st2::init();
	rep(i,1,m)scanf("%lld%lld%lld",&q[i].s,&q[i].t,&q[i].u),o[i]=q[i].u;
	sort(o+1,o+m+1);rep(i,1,m)if(o[i]!=o[i-1])u[++T]=o[i];
	//printf("aa ");rep(i,1,n+1)printf("%lld ",s[i]);putchar('\n');
	//printf("bb ");rep(i,1,T)printf("%lld ",u[i]);putchar('\n');
	rep(i,1,m){
		int l=q[i].s,r=q[i].t-1,ed=q[i].t-1;
		while(l<=r){
			int mid=(l+r)>>1;
			if(s[q[i].t]-s[mid]<=q[i].u)ed=mid,r=mid-1;
			else l=mid+1;
		}
		int cur=st1::ask(ed,q[i].t-1);
		//printf("ss %lld %lld %lld\n",i,ed,cur);
		node now;now.u=q[i].u,now.s=i,now.t=1;
		w[q[i].s].push_back(now);
		now.s=i,now.t=-1;w[cur].push_back(now);
		ans[i]+=(s[q[i].t]-s[cur])*b[cur];
	}
	pre(i,n,1){
		while(top&&b[sta[top]]>=b[i]){
			pr[sta[top]]=i;top--;
		}
		if(top)nx[i]=sta[top];
		sta[++top]=i;
	}
	rep(i,1,n)if(!nx[i])nx[i]=n+1;
	//rep(i,1,n)printf("%lld ",pr[i]);putchar('\n');
	//rep(i,1,n)printf("%lld ",nx[i]);putchar('\n');
	pre(i,n,1){
		change(0,0,s[nx[i]]-s[i],b[i]);
		change(1,s[nx[i]]-s[i]+1,0x7fffffff,b[i]*(s[nx[i]]-s[i]));
		dl[pr[i]].push_back(i);
		for(int j=0;j<(int)dl[i].size();j++){
			int x=dl[i][j];
			change(0,s[x]-s[i],s[nx[x]]-s[i],-b[x]);
			change(1,s[x]-s[i],s[nx[x]]-s[i],b[x]*(s[x]-s[i]));
			change(1,s[nx[x]]-s[i]+1,0x7fffffff,-b[x]*(s[nx[x]]-s[x]));
		}
		for(int j=0;j<(int)w[i].size();j++){
			int cur=lower_bound(u+1,u+T+1,w[i][j].u)-u;
			//cout<<"uu "<<i<<" "<<w[i][j].s<<" "<<w[i][j].t<<" "<<(w[i][j].u*ask(0,cur)+ask(1,cur))<<endl;
			ans[w[i][j].s]+=w[i][j].t*(w[i][j].u*ask(0,cur)+ask(1,cur));
		}
	}
	rep(i,1,m){
		if(q[i].u<a[st2::ask(q[i].s,q[i].t-1)])puts("-1");
		else printf("%lld\n",ans[i]);
	}
	return 0;
} 
/*
5 1
2 0 1 1 1 
4 3 5 7 4 
4 5 6
*/
```



---

## 作者：Kubic (赞：3)

先考虑 $m=1$ 怎么做。设人要从 $l$ 走到 $r$，能量上限为 $x$。

假设当前人在 $i$，设最远能走到 $j$。不妨将 $a_r$ 看作 $0$，那么：

- 如果 $\exists k\in(i,j],a_i>a_k$，那么一定是在 $i$ 处买能量使得刚好能走到 $k$。

- 否则一定是在 $i$ 处买能量到上限，并走到 $k\in (i,j]$ 时 $a_k$ 最小的位置 $k$。

如果所有询问的 $x$ 都相等，那么我们可以预处理出每个 $i$ 会走到哪个 $k$，连一条边 $i\rightarrow k$。显然这会形成一棵内向树，询问时在树上倍增即可。

考虑每个 $i$ 在 $x$ 任意取值的情况下可能对应的 $k$。从后往前跑单调栈，所有被 $i$ 弹出的位置以及 $i$ 后面第一个满足 $a_i>a_j$ 的位置 $j$ 都会在 $x$ 取在某一段区间中时作为 $i$ 的出边，并且剩下的位置一定在任何时候都不可能作为 $i$ 的出边。

对于所有的 $i$，可能的位置数量的总和是 $O(n)$ 的。因此我们可以将询问离线下来，按照 $x$ 从小到大依次处理。

一种不需要脑子的方式是直接使用 LCT 动态维护内向树。时间复杂度 $O(n\log n)$。实际上在本题中它可以极大地减少思考量，不失为一种好方法。

这里我们再来介绍一种更为精妙的做法。

考虑确定一个 $x$，分析当前的边之间有什么特殊性质。

设 $d(u,v)$ 为从 $u$ 走到 $v$ 的距离。

这里给出一些关于边之间关系的结论，证明都是 trivial 的，这里不再赘述。

结论 $1$：对于任意两条边 $u_1\rightarrow v_1,u_2\rightarrow v_2$ 满足 $u_1<u_2$，有 $v_1\ge v_2$。

结论 $2$：对于任意两条边 $u_1\rightarrow v_1,u_2\rightarrow v_2$ 满足 $u_1<u_2,a_{u_2}\le a_{v_2}$，有 $u_2\ge v_1$。

结论 $2$ 启发我们将所有边 $u\rightarrow v$ 按照 $a_u>a_v$ 是否成立分为两类。根据之前的分析可以得到，对于 $u$ 的所有可能的出边 $u\rightarrow v$ 中最多只有一条满足 $a_u>a_v$，而这也形成了一棵内向树，设为 $T$。

设 $t$ 为满足 $d(t,r)\le x$ 且 $d(t,r)$ 最大的位置。

根据结论 $1,2$ 可以得到结论 $3$：对于所有不在 $T$ 中的边 $u\rightarrow v$，它在当前询问中被经过当且仅当 $u<t$。

因此我们可以对于所有不在 $T$ 中的边，维护相邻两条之间在 $T$ 上的距离。询问时相当于在序列上求区间和。

询问时从 $l$ 开始在 $T$ 中倍增，直到 $l$ 在 $T$ 中的父边当前不是 $l$ 的出边。然后通过上面所提到的方法求出所有不在 $T$ 中的边的贡献。最后再在 $T$ 中进行倍增求出最后一段的贡献即可。

实现时细节较多。

时间复杂度 $O(n\log n)$。

参考代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 300005
#define ll long long
int n,m,tp,a[N],st[N],ps[N],L[N],R[N],mx[18][N],z[18][N];
ll s[N],ans[N],lim[18][N];struct Node {int l,r,id;ll x;}o[N*3];
struct Num
{
	ll x,y;Num(ll _x=0,ll _y=0) {x=_x;y=_y;}
	Num operator + (Num t) const {return Num(x+t.x,y+t.y);}
	Num operator - (Num t) const {return Num(x-t.x,y-t.y);}
	Num operator += (Num t) {return (*this)=(*this)+t;}
	Num operator -= (Num t) {return (*this)=(*this)-t;}
}zero,w[N];
struct BitArray
{
	Num bt[N];void upd(int x,Num vl) {for(;x<=n;x+=x&-x) bt[x]+=vl;}
	Num qSm(int x) {Num res;for(;x;x-=x&-x) res+=bt[x];return res;}
}BIT;
bool cmp(Node x,Node y) {return x.x==y.x?x.id<y.id:x.x<y.x;}
Num f(int l,int r)
{
	if(a[l]>a[r]) return Num((s[r]-s[l])*a[l],a[r]-a[l]);
	return Num((s[r]-s[l])*a[r],0);
}
Num f1(int l,int r) {return Num((s[r]-s[l])*a[l],-a[l]);}
int findRt(int u) {return u==L[u]?u:L[u]=findRt(L[u]);}
int qMx(int l,int r)
{int t=31-__builtin_clz(r-l+1);return max(mx[t][l],mx[t][r-(1<<t)+1]);}
void upd(int l,int r)
{
	int t=findRt(l),t1=t-1,t2=R[l+1];BIT.upd(l,zero-f(l,ps[l]));
	if(a[l]>a[r])
	{
		L[l+1]=t;R[t]=t2;if(t1) BIT.upd(ps[t1],w[l]-w[t2]);
		BIT.upd(ps[l],w[t2]-w[ps[l]]);
	}
	else
	{
		BIT.upd(ps[l],w[t2]-w[ps[l]]);
		BIT.upd(r,w[r]-w[t2]);BIT.upd(l,f(l,r));
	}ps[l]=r;
}
ll qry(int l,int r,ll x)
{
	if(qMx(l,r-1)>x) return -1;
	int t=lower_bound(s+1,s+n+2,s[r]-x)-s,t1;Num res=w[l];
	for(int i=17;i>=0;--i) if(z[i][l]<=r && lim[i][l]<=x) 
		l=z[i][l];res-=w[l];
	if(l<t) t1=findRt(t)-1,res+=BIT.qSm(t1)-BIT.qSm(l-1),l=ps[t1];res+=w[l];
	for(int i=17;i>=0;--i) if(z[i][l]<=r && lim[i][l]<=x)
		l=z[i][l];res+=f1(l,r)-w[l];return res.x+res.y*x;
}
int main()
{
	scanf("%d %d",&n,&m);tp=m;st[++st[0]]=n+1;
	for(int i=1;i<=n;++i) scanf("%d",&mx[0][i]),s[i+1]=s[i]+mx[0][i];
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
	for(int i=1;i<=n+1;++i) L[i]=R[i]=ps[i]=i;
	for(int i=1;i<=m;++i)
		scanf("%d %d %lld",&o[i].l,&o[i].r,&o[i].x),o[i].id=i;
	for(int i=n;i;--i)
	{
		while(st[0] && a[i]<=a[st[st[0]]])
			o[++tp]=(Node) {i,st[st[0]],0,s[st[st[0]]]-s[i]},--st[0];
		z[0][i]=st[st[0]];lim[0][i]=s[z[0][i]]-s[i];
		w[i]=w[z[0][i]]+f(i,z[0][i]);
		o[++tp]=(Node) {i,z[0][i],0,s[z[0][i]]-s[i]};st[++st[0]]=i;
	}z[0][n+1]=z[0][n+2]=n+2;
	for(int i=1;i<=n;++i) BIT.upd(i,w[i]-w[i+1]);
	for(int i=1;i<=17;++i)
	{
		for(int j=1;j+(1<<i)-1<=n;++j)
			mx[i][j]=max(mx[i-1][j],mx[i-1][j+(1<<i-1)]);
		for(int j=1;j<=n+2;++j)
		{
			z[i][j]=z[i-1][z[i-1][j]];
			lim[i][j]=max(lim[i-1][j],lim[i-1][z[i-1][j]]);
		}
	}sort(o+1,o+tp+1,cmp);
	for(int i=1;i<=tp;++i) if(o[i].id)
	{
		ans[o[i].id]=qry(o[i].l,o[i].r,o[i].x);
		if(~ans[o[i].id]) ans[o[i].id]+=o[i].x*a[o[i].l];
	}else upd(o[i].l,o[i].r);
	for(int i=1;i<=m;++i) printf("%lld\n",ans[i]);return 0;
}
```

---

## 作者：yllcm (赞：3)

原题意是不好做的，对着原题意硬做顶多得到一个基于维护凸包的单次线性做法。所以考虑转化题意。

把第 $i$ 层地牢看做数轴上位置为 $\sum_{j<i}a_j$ 的点（不妨写作 $c_i$），那么原问题等价于第 $i$ 个点可以覆盖位置为 $[c_i,c_i+u)$ 的任意位置，覆盖一个位置的代价是 $b_i$，求覆盖 $[c_{s},c_t)$ 中所有点的代价最小值。这是容易理解的，因为我们可以把加能量的过程看做是不断拓展能到达的位置的过程，而拓展位置容易理解为覆盖。

那么贪心做法就比较显然了：对于一个位置 $p$，找到 $(p-u,p]$ 中代价最小的点，然后加进去即可。

考虑怎么做原问题。因为 $u$ 会改变，所以直接维护贪心是十分不方便的，考虑进一步刻画。我们对于 $i$，找到 $i$ 的前驱 $\text{pre}_i$ 和后继 $\text{nxt}_i$，满足 $b_{\text{pre}_i}\leq b_i,b_{\text{nxt}_i}<b_i$，且分别为所有位置中最大 / 最小的（不存在分别设为 $-\infty$ 和 $\infty$）。那么对于位置 $p$，假设它被 $i$ 覆盖，那么需要满足：$p\geq c_i,p\geq c_{\text{pre}_i}+u,i<c_i+u,p<c_{\text{nxt}_i}$。说明当 $c_{\text{pre}_i}+u<c_{\text{nxt}_i}$ 的时候，$p$ 的区间是 $[\max(c_i,c_{\text{pre}_i}+u),\min(c_i+u,c_{\text{nxt}_i}))$，其长度是段数为 $\mathcal{O}(1)$，次数不超过 $1$ 的关于 $u$ 的分段函数，所以可以尝试开一个线段树，维护每个 $u$ 的贡献，支持区间加一次函数和单点求值。

考虑加上区间的限制，发现右端点并不影响，可以使用差分等技巧解决（稍后提及）。那么我们扫描线枚举左端点 $l$，分别维护每个点的贡献。注意当 $\text{pre}_i<l$ 的时候，$\text{pre}_i$ 视为不存在，所以需要在 $l=i$ 的时候加入一次 $i$，$l=\text{pre}_i$ 的时候删除前面的 $i$ 并重新加入一次带有 $\text{pre}_i$ 限制的 $i$。考虑怎么解决右端点的限制，我们找到覆盖 $c_r$ 的点，处理出它的区间 $[lp,rp]$，然后减去这段区间在 $[c_r,\infty)$ 处的贡献；之后，我们再找到覆盖 $rp+1$ 的点 $p$（如果不存在则找到 $rp$ 后第一个点），补上 $[a_p,rp]$ 的贡献，并减去 $l=p$ 时 $u$ 的答案（相当于减去了后面一整段区间的贡献）。这样我们就得到了区间 $[l,r]$ 的答案。

[code](https://loj.ac/s/1916397)

---

## 作者：jiamengtong (赞：1)

拿到这个题，我首先想到了一个贪心：在每一个位置从前面找还有剩余空间中的最小的位置，一直重复直到可以走到下一个位置。接着想发现有点困难。其实有一档 $T_j=n+1$ 可以说明，我们大概率需要设计一个从前向后的贪心。

换个思路，可以得到另一个贪心：从当前位置向后找到第一个价格比当前位置小的。如果这段区间长度（区间内 $a$ 的总和）不超过 $U$，那我们显然应该把这段区间用当前位置完全覆盖，也容易证明我们在当前位置只会买这么多次，然后跳到这个区间的右端点。否则我们一直卖直到达到上限，然后跳到下一个位置。

首先考虑 $T_j=n+1$，我们不难想到从右向左扫描的过程。由于要找后面第一个比它小的，维护单调栈。考虑弹出栈顶 $x$ 时钱数的变化。只有当 $i+u>x$ 时，钱数会变化。这个变化的值是 $(\min(i+u,nw)-x)(b_i-b_x)$，其中 $nw$ 表示新的栈顶。

不难发现，上述式子中唯一的变量为 $u$，由此每次都是将一个区间中的 $u$ 的答案加上一个等差数列，数据结构容易 $O(n\log n)$ 维护。

那怎么做最后一档呢？这个两个后缀**差分**一下直接就写脸上了。但是有一个问题：直接差分是不对的。研究一下可以发现这是由于长的后缀中与短的后缀对应的一段不一定全是在短的后缀里买的。那我们找到一个点使得从它开始的策略和长的后缀中对应的部分**完全一样**不就行了吗？容易发现 $[r-u,r]$ 中的最大值 $mx$ 就是这样的一个位置。最终答案为 $ans_l-ans_{mx}+b_{mx}(r-mx)$。

综上，我们在 $O(n\log n)$ 的时间内解决了这个问题。

---

## 作者：flyfreemrn (赞：1)

## [[JOI 2021 Final] 地牢 3](https://www.luogu.com.cn/problem/P7408)

### subtask 1

直接考虑贪心思想，从左端点向右扫，对于每个位置找到下一个花费小于他的点，这中间的路程肯定都用当前点买的能量更优，所以能买就买。

### subtask 2 + subtask 3

观察 subtask 3 给定的条件，所有查询的右端点都相同，为什么不是左端点相同而是去限制右端点？很明显可以想到走到右端点时最优的状态一定是所有能量全部花完，我们的末状态可以说是确定的，因此我们考虑从后往前倒推。

我们先将询问离线 + 排序。

考虑我们如何维护我们的贪心策略，我们每次要从后往前找第一个比他小的位置，所以想到用单调栈维护。

思考每次出栈操作的意义，说明我们可能要用当前点买的能量代替栈顶位置买的能量，因此我们记录原来上一次出栈前的栈顶 $x$ 和当前的栈顶 $y$。

记当前位置为 $st$，节点 $i$ 距离起点的位置为 $L_i$，分类讨论：
1. $L_x > L_{st} + u$，这时候我们无法用 $st$ 位置的能量代替，不会对答案产生贡献。
2. $L_y \leq L_{st} + u$，这时候直接用 $st$ 位置的能量代替整个 $L_x$ 到 $L_y$ 段中的所有能量一定是最优的。
3. $L_x \leq L_{st} + u < L_y$，这个时候用 $st$ 位置的能量代替 $L_x$ 到 $L_{st} + u$ 段的能量。

将上面的条件简化一下，一段区间 $L_x ~ L_y$ 能替代掉的能量为 $\max(0, \min(L_y, L_{st} + u) - L_x)$。直接按照这个策略从后往前预处理即可。

### subtask 3

考虑 $u$ 不相同的时候怎么处理，因为 $u$ 的值域很大，我们先将 $u$ 离散化后放在一个序列上。

考虑每一次出栈的过程，如果 $u$ 为一个序列，那么相当于在整个序列上加上一条折线。

具体来说，对于满足 $L_x \leq L_{st} + u < L_y$ 的所有 $u$，相当于加上一条关于 $u$ 的一次函数。而对于满足 $L_y \leq L_{st} + u$ 的所有位置，直接加上一条平行于 $x$ 轴的直线，可以手模一下。

因此，我们可以考虑直接使用线段树维护一次函数。

### 正解

我们已经可以处理不同的 $u$ 到达终点的最小代价，考虑这对于一次 $l$ 到 $r$ 的查询有什么用。

我们找到满足 $L_r - u + 1 \leq L_i \leq L_r$ 中 $b_i$ 最小的位置 $x$。从 $x$ 到 $L_r$ 的部分一次性在 $x$ 层买完是最优的，而对于前面位置的策略，手模一下可以发现与从一个点走到终点的策略是相同的。

因此，我们考虑用 ST 表或者线段树维护区间最小值和最小位置 $x$，将每个询问拆成两段走到结尾的询问，离线后求出答案相减并加上 $x$ 位置的贡献即是答案。

总的时间复杂度为 $O(n \log{n})$。

---

## 作者：Last_Flame (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P7408)。

# 思路

我们考虑如果一个人没有 $U$ 的限制，他的决策会是什么样的。显然他每次会买能量买到刚好能够到下一个能量价格比当前位置便宜的位置，或者到终点。那如果有 $u$ 的限制怎么办，那么这个人一定会把能量买满，然后走到他能走到的、能量最便宜的位置，然后走到比原位置能量价格更便宜的位置。

我们注意到对于两个人 $x$ 和 $y$，如果 $U_{x} > U_{y}$，$x$ 在 $p$ 处买了能量，那么 $y$ 一定也在 $p$ 处买了能量，且 $y$ 可能会在更多的地方买能量。考虑两个购买能量的位置 $p_{1}$ 和 $p_{2}$，如果我们没有在 $p_{1}$ 和 $p_{2}$ 中任何一个位置购买能量，那么我们把 $p_{1}$ 到 $p_{2}-1$ 视为一个区间，那么就会形成一个关于 $A$ 的 min tree。在 min tree 中，每个节点表示一个区间 $[l,r]$，其中位置 $l$ 的值为区间内的最小值，区间 $[l+1,r]$ 中最小值在位置 $mid$，那么它的左儿子表示区间 $[l,mid-1]$，右儿子表示 $[mid,r]$。每有一个 $mid$ 则节点数加二，故点数为 $3n$ 左右。你很可能没有听说过 min tree，因为它的名字和定义都是我现编的，但是这不重要，因为接下来我要展示一张这道题中 min tree 关于 $U$ 的二维图像。

![](https://cdn.luogu.com.cn/upload/image_hosting/m83eoyvh.png)

这是样例 $1$。

这张图中，纵坐标为选择区间需要的 $U$ 的最小值（区间包括底部不包括顶部），所以对于一个人的 $U$，我们直接在图上画一条直线 $y=U$，然后从 $S$ 开始，选择从当前位置开始的，在 $U$ 之下的最大区间，然后走到该区间结尾的后一个位置。

考虑在这道题里，我们将人按 $U$ 从大到小排序，每次删除所需能量大于 $U$ 的区间。对于每个位置，我们维护以这个位置开头的最大区间，那么它就会形成一棵树，对于位置 $p$，若以它开头的最大区间结尾在位置 $q$，那么 $fa_{p}=q+1$。那么我们就是要求从节点 $S$，到其某个祖先节点的权值和，然后再从这个祖先节点对应区间的开头位置走到终点。具体的，这个祖先节点的开头位置为能直接到达终点的位置中能量最便宜的，可以二分查找得到。

这棵树中节点的父亲会变，可以使用 LCT 维护。

然后考虑如何计算答案，考虑一个区间的贡献是什么。如果区间结尾的下一个位置的能量比区间开头的能量便宜，那么只需要买刚好能走完这个区间的能量即可；否则把能量买满。所以我们考虑拆贡献为 $val1$ 和 $val2$，其中 $val1$ 为贡献实值，$val2$ 在计算贡献的时候需要额外乘 $U$，那么有：
$$
val1=
\begin{cases}
B_{l} \times sumA_{l,r} & B_{l} \ge B_{r+1}
\\
B_{r+1} \times sumA_{l,r} & B_{l} < B_{r+1}
\end{cases}
$$

$$
val2=
\begin{cases}
0 & B_{l} \ge B_{r+1}
\\
B_{l}-B_{r+1} & B_{l} < B_{r+1}
\end{cases}
$$

然后直接使用 LCT 维护即可，时间复杂度 $O(n \log n)$。

思路比较直接，但是代码很长。我的实现用了线段树维护最小值和区间和。

# code

~~~cpp
/*
考虑贡献如何计算 
对于下一区间的价格更低的，刚好买到能到即可 
否则拉满，对后面会有一个负的贡献 -(u-suma)*b(next)，总贡献 (b-b(next))*u+suma*b(next) 
特别的，由于这道题的编号情况，LCT 中 r 为深度小的节点 
*/
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int mn=114514,inf=2147483647;
vector<int> st[2*mn];
int n,m,a[2*mn],b[2*mn];
int fa[2*mn];
ll ans[2*mn];

struct people{
	int s,t,u;
	int id;
}peo[2*mn];

struct block{
	int l,r;
	ll sum,val[2];
}blc[6*mn];

int tot;

struct seg_min{
	int val,p;
};

struct seg_tree{
	int l,r,mid;
	ll val;
	seg_min min;
}t[16*mn]; 

int pl,pr,lim;
int pw;
bool isans;

struct lct{
	int l,r,fa;
	ll val[2];
}tre[2*mn];

int read(){
	int x=0,w=1;
	char ch=getchar();
	while(ch<'0' && ch>'9'){
		if(ch=='-') w=-1;
		ch=getchar();
	}
	while(ch>='0' && ch<='9'){
		x=x*10+ch-'0';
		ch=getchar(); 
	}
	return x*w;
}

bool cmp1(people a,people b){
	return a.u>b.u;
}

bool cmp2(block a,block b){
	return a.sum<b.sum;
}

seg_min min_merge(seg_min a,seg_min b){
	if(a.val<=b.val) return a;
	else return b;
}

void merge(int p){
	t[p].min=min_merge(t[t[p].l].min,t[t[p].r].min);
	t[p].val=t[t[p].l].val+t[t[p].r].val;
	return;
}

void build(int p,int s,int e){
	if(s>=e){
		t[p].min.p=s,t[p].min.val=b[s];
		t[p].val=a[s];
		return;
	}
	
	t[p].mid=(s+e)>>1;
	t[p].l=p<<1,t[p].r=(p<<1)+1;
	build(t[p].l,s,t[p].mid);
	build(t[p].r,t[p].mid+1,e);
	
	merge(p);
	
	return;
}

seg_min getmin(int p,int s,int e){
	if(pl<=s && pr>=e) return t[p].min;
	
	seg_min pans={inf,0};
	if(pl<=t[p].mid && pr>=s) pans=getmin(t[p].l,s,t[p].mid);
	if(pl<=e && pr>t[p].mid) pans=min_merge(pans,getmin(t[p].r,t[p].mid+1,e));
	
	return pans;
}

ll getval(int p,int s,int e){
	if(pl<=s && pr>=e) return t[p].val;
	
	ll pans=0;
	if(pl<=t[p].mid && pr>=s) pans+=getval(t[p].l,s,t[p].mid);
	if(pl<=e && pr>t[p].mid) pans+=getval(t[p].r,t[p].mid+1,e);
	
	return pans;
}

ll getrange(int p,int s,int e,ll pval){
	if(s>=e){
		if(t[p].val+pval>lim) pw=e+1,isans=true;
		pval+=t[p].val;
		return pval;
	}
	
	if(t[p].mid<pr){
		if(e<=pr){
			if(t[t[p].r].val+pval<=lim) pval+=t[t[p].r].val;
			else getrange(t[p].r,t[p].mid+1,e,pval);
		}
		else pval+=getrange(t[p].r,t[p].mid+1,e,pval);
	}
	
	if(isans) return pval;
	
	if(s<=pr){
		if(t[p].mid<=pr){
			if(t[t[p].l].val+pval<=lim) pval+=t[t[p].l].val;
			else getrange(t[p].l,s,t[p].mid,pval);
		}
		else pval+=getrange(t[p].l,s,t[p].mid,pval);
	}
	
	return pval;
} 

bool isl(int p,int fa){
	return (p==tre[fa].l);
}

void rotate(int p){
	if(!tre[p].fa) return;
	
	ll pval[2]={tre[p].val[0],tre[p].val[1]};
	int fa=tre[p].fa,pfa=tre[fa].fa;
	if(isl(p,fa)){
		pval[0]-=tre[tre[p].r].val[0],pval[1]-=tre[tre[p].r].val[1];
		tre[tre[p].r].fa=fa,tre[fa].l=tre[p].r;
		tre[fa].fa=p,tre[p].r=fa; 
	} 
	else{
		pval[0]-=tre[tre[p].l].val[0],pval[1]-=tre[tre[p].l].val[1];
		tre[tre[p].l].fa=fa,tre[fa].r=tre[p].l;
		tre[fa].fa=p,tre[p].l=fa;
	}
	if(isl(fa,pfa)) tre[p].fa=pfa,tre[pfa].l=p;
	else tre[p].fa=pfa,tre[pfa].r=p;
	
	tre[p].val[0]=tre[fa].val[0],tre[fa].val[0]-=pval[0];
	tre[p].val[1]=tre[fa].val[1],tre[fa].val[1]-=pval[1];
	
	return;
}

void splay(int p){
	while(tre[p].fa){
		if(tre[tre[p].fa].fa && (isl(p,tre[p].fa)==isl(tre[p].fa,tre[tre[p].fa].fa))) rotate(tre[p].fa);
		rotate(p);
	}
	return;
}

int getfst(int p){
	while(tre[p].fa) p=tre[p].fa;
	while(tre[p].r) p=tre[p].r;
	return p;
}

void cutson(int p){
	if(tre[p].l){
		tre[p].val[0]-=tre[tre[p].l].val[0],tre[p].val[1]-=tre[tre[p].l].val[1];
		tre[tre[p].l].fa=0;
		fa[getfst(tre[p].l)]=p;
		tre[p].l=0;
	}
	return;
}

void cnctfa(int p){
	if(fa[p]){
		splay(p),splay(fa[p]);
		cutson(fa[p]);
		tre[fa[p]].val[0]+=tre[p].val[0],tre[fa[p]].val[1]+=tre[p].val[1];
		tre[fa[p]].l=p,tre[p].fa=fa[p];
		fa[p]=0;
	}
	return;
}

void access(int p){
	splay(p),cutson(p);
	p=getfst(p);
	
	while(fa[p]){
		if(st[fa[p]].empty()){
			fa[p]=0;
			break;
		}
		cnctfa(p);
		p=getfst(p);
		splay(p);
	}
	
	return;
}

ll getblock(int s,int e){
	ll psum=0;
	if(s<e){
		pl=s+1,pr=e;
		int pget=getmin(1,1,n).p;
		psum=getblock(s,pget-1)+getblock(pget,e);
	}
	
	if(s>0){
		if(s>=e) psum=a[s];
		tot++;
		blc[tot].l=s,blc[tot].r=e,blc[tot].sum=psum;
		if(e>=n || b[s]>=b[e+1]) blc[tot].val[0]=1ll*b[s]*psum,blc[tot].val[1]=0;
		else blc[tot].val[0]=1ll*psum*b[e+1],blc[tot].val[1]=b[s]-b[e+1];
	}
	
	return psum;
}

void ready(){
	sort(peo+1,peo+m+1,cmp1);
	
	build(1,1,n);
	
	getblock(0,n);
	sort(blc+1,blc+tot+1,cmp2);
	for(int i=1;i<=tot;i++) st[blc[i].l].push_back(i);
	for(int i=1;i<=n;i++) if(!st[i].empty()){
		tre[i].val[0]=blc[st[i].back()].val[0],tre[i].val[1]=blc[st[i].back()].val[1];
		fa[i]=blc[st[i].back()].r+1;
		if(fa[i]>n) fa[i]=0;
	}
	
	return;
} 

void del(int p){
	splay(p);
	if(tre[p].r){
		int pt=tre[p].r;
		while(tre[pt].l) pt=tre[pt].l;
		splay(pt);
		cutson(pt);
	}
	if(fa[p]) fa[p]=0;
	splay(p);
	cutson(p);
	
	return;
}

int geted(int p,int pp){
	if(st[p].empty()) return 0;
	while(p && (pp<p || pp>blc[st[p].back()].r)){
		if(pp<p) p=tre[p].l;
		else p=tre[p].r;
	}
	return p;
}

int main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>b[i];
	for(int i=1;i<=m;i++) cin>>peo[i].s>>peo[i].t>>peo[i].u,peo[i].t--,peo[i].id=i;
	
	ready();
	
	int p=0;
	ll pget=0;
	for(int i=1;i<=m;i++){
		while(tot && blc[tot].sum>peo[i].u){
			p=blc[tot].l;
			st[p].pop_back();
			del(p);
			
			if(!st[p].empty()){
				tre[p].val[0]=blc[st[p].back()].val[0],tre[p].val[1]=blc[st[p].back()].val[1];
				fa[p]=blc[st[p].back()].r+1;
				if(fa[p]>n) fa[p]=0;
			}
			
			access(p);
			tot--;
		}
		
		p=peo[i].s;
		if(!st[p].empty() && blc[st[p].back()].r>=peo[i].t){
			pl=peo[i].s,pr=peo[i].t;
			pget=getval(1,1,n);
			ans[peo[i].id]=1ll*b[p]*pget;
		}
		else{
			/*
			考虑我们其实需要找到可以到达终点的位置中最便宜的 
			考虑这个最便宜的是不是一定在一个区间开头 
			考虑如果不在区间开头，它所在区间开头一定比它便宜，结尾在它之后，且结尾不包含终点 
			考虑这个区间的下一个区间，其开头一定比这个位置贵，那么不成立，因为区间不可能这么划分 
			*/
			access(p),splay(p);
			if(geted(p,peo[i].t)==0){
				ans[peo[i].id]=-1;
				continue;
			}
			
			isans=false;
			pw=0;
			pl=1,pr=peo[i].t,lim=peo[i].u;
			getrange(1,1,n,0);
			if(pw<=0) pw=1;
			
			pl=max(peo[i].s,pw),pr=peo[i].t;
			p=getmin(1,1,n).p;
			splay(p);
			pl=p,pr=peo[i].t;
			pget=getval(1,1,n);
			ans[peo[i].id]=tre[tre[p].l].val[0]+1ll*peo[i].u*tre[tre[p].l].val[1]+1ll*b[p]*pget;
		}
	}
	
	for(int i=1;i<=m;i++) cout<<ans[i]<<endl;
	
	return 0;
}
~~~

---

## 作者：Dovish (赞：0)

## 前言
模拟赛的时候做到了，所有思路全部正确，但是细节/码量巨大，赛后花了 4h+ 才写出来。

## 思路

下文将题面转化为每走一单位距离花一单位油，在一个位置买一单位油需要花费一定代价。

考虑暴力贪心：我们每走到一个位置，就将油加满，如果此时还装得有更贵的油，则替换为当前的油。每次走路程的时候尽量用更便宜的油去走。

这个过程还是不好刻画成可以优化的样子，考虑更加形象化一些，考虑现在有一个长度为 $\sum a$ 的序列，并称之为路程序列，每个点 $i$ 对 $[\sum_{j<i}a_j+1,\sum_{j<i}a_j+u]$ 的位置上取 $\min$。那么询问就是询问序列上 $l,r$ 点对应的区间之和。

继续观察，我们发现：通过这个方式，从后往前扫可以维护出每个后缀的答案，但我们还有一个 $u$ 没有维护，所以我们希望只维护全局的答案。设询问的区间在路程序列上转化后的区间为 $[ql,qr]$，可以发现的是：如果 $[\sum_{j<l-1}a_{l-1}+1,\sum_{j<l-1}a_{l-1}+u]$ 和 $[ql,qr]$ 有交，则说明前面的取 $\min$ 可能影响到当前区间内的点。设有交的部分为 $[ql,x]$，容易发现的是，这段区间内的贪心，转化为了后缀取 $\min$ 区间询问。（因为每一个操作位置都可以覆盖整个询问的后缀）这部分直接从后往前扫一遍简单维护一下即可求出，这里就不作赘述了。而 $[x+1,qr]$ 的部分就不会受到之前的影响，故直接对这部分全局询问是对的。

现在考虑 $u$ 的变化怎么维护，容易想到按照 $u$ 单增去做。考虑当前序列是若干颜色的连续段。现在只考虑每一段联通的部分。现在我们让 $u\to u+1$，会发生说明？每个颜色段都尝试去覆盖末尾的下一个位置，更加形象一些，考虑将序列划分为若干段权值上升的颜色段。每个颜色段的首段长度 $+1$，末尾段长度 $-1$。

考虑定义两类连续段，称一个颜色段是 1 类颜色段当且仅当其上一段权值比其大或者是一段联通的颜色段的开头；称一个颜色段是 2 类颜色段，当且仅当其下一段权值比其小。按照定义如果一个点即是 1 类又是 2 类，我们当其不是任何特殊的颜色段。一次 $+1$ 操作不会影响到这两类之外的颜色段。而 $1$ 类颜色段长度 $+1$，$2$ 类颜色段长度 $-1$。

于是我们考虑在整个路程序列的颜色段都联通的时候维护怎么做：

即当前需要对 $u$ 的增量为 $\Delta$，此时全局最短的 $2$ 类颜色段长度为 $k$，则每次增量 $\min(\Delta,k)$ 去做。
显然我们可以对 $1$ 类颜色段打tag，$2$ 类段每次找到被删空的更新相邻位置的颜色段的所属类别。

因为每做一次至少会删掉一个颜色段或者回答一个询问，所以总共做的次数是 $O(n)$ 的。

再考虑最初 $u=0$ ，我们还需要维护颜色段之间的合并，发现不会本质影响上述操作，只需要将每次合并上的地方更新颜色段的所属类即可。为了方便实现，我们将每个 $a$ 也当作是询问的 $u$ 丢到我们需要增量的部分去。这样每次更新完之后两段都是恰好合并上的。

上述内容中，初始每个颜色段都是 $1$ 类的，$1$ 类只会转化为 $2$ 类，$2$ 类只会被删除。每次转化，找到并删除的复杂度都是 $O(\log n)$，而又知道总操作次数是 $O(n)$ 的，且删除总共只会有 $n$ 次，故均摊复杂度是 $O(n\log n)$。

然后考虑询问，注意到，由于颜色段可能开头被覆盖了一段，末尾又去覆盖了别的段。所以颜色段不一定在其对应开始的位置上，所以我们需要维护区间的颜色段长度之和，用线段树上二分找到询问的位置。但是考虑到不一定联通的情况，所以，还需要考虑当前连通块之前可能还有一些空位值没有被算到区间颜色段长度之和中。所以这里需要求出联通的颜色段的 $l$ 端点，直接并查集即可。这个部分的复杂度同样是 $O(n\log n)$。

注意常数优化，笔者写的这坨 $O(n\log n)$ 的玩意 $2\times 10^5$ 的数据跑了 $1.13s$。

正常情况下实现上述内容大概需要 8kb 上下，谨慎写代码。

## code

```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(register int i=(a);i<=(b);++i)
#define per(i,a,b) for(register int i=(a);i>=(b);--i)
#define edge(i,u) for(int i=head[u];i;i=e[i].next)
#define lc (u<<1)
#define rc (u<<1|1)
#define pii pair<int,int>
#define pdd pair<double,double>
#define mp make_pair
#define pb push_back
#define fst first
#define sed second
#define Max(a,b) (a=max(a,b))
#define Min(a,b) (a=min(a,b))
using namespace std;
const int N=2e5+10,M=1e6+10,inf=1e9,mod=1e9+7;
const double eps=1e-6;
bool MS;int used;
int n,m;
int a[N],b[N];
int st[N];//这个点对应的起始位置
int ans[N];
struct que
{
	int l,r,from,sc;
};
map<int,vector<que>>q;
vector<pii>qx[N];//询问[l,x]用的 
vector<int>lnk[N];//用于拼接序列 
set<int>upd;//用于更新 
int nxt[N],lst[N];//当前状态下的上一个和下一个位置 
int tag[N];//012类点 
namespace DSU
{
	int f[N];
	int minn[N];
	void init()
	{
		rep(i,1,n+1)
		f[i]=minn[i]=i;
	}
	int fa(int x){return f[x]==x?x:f[x]=fa(f[x]);}
	void merge(int u,int v){Min(minn[fa(v)],minn[fa(u)]);f[fa(u)]=fa(v);}
}
namespace SGT
{
	struct sx
	{
		int cnt1,cnt2,add;//12类点的这些点的个数以及addtag
		int minn;
		int sum;//段长之和
		int val;
		int b1;//1类点的b之和 
		int b2;//1类点的b之和 
	}tre[N<<2];
	void pushup(int u)
	{
		tre[u].sum=tre[lc].sum+tre[rc].sum;
		tre[u].minn=min(tre[lc].minn,tre[rc].minn);
		tre[u].cnt1=tre[lc].cnt1+tre[rc].cnt1;
		tre[u].cnt2=tre[lc].cnt2+tre[rc].cnt2;
		tre[u].val=tre[lc].val+tre[rc].val;
		tre[u].b1=tre[lc].b1+tre[rc].b1;
		tre[u].b2=tre[lc].b2+tre[rc].b2;
	}
	void update(int u,int k)//能执行这个操作，说明区间内的点都没有归零 
	{
		tre[u].add+=k;
		tre[u].sum+=tre[u].cnt1*k;
		tre[u].sum-=tre[u].cnt2*k;
		tre[u].minn-=k;
		tre[u].val+=tre[u].b1*k;
		tre[u].val-=tre[u].b2*k;
	}
	void pushdown(int u)
	{
		if(tre[u].add)
		{
			update(lc,tre[u].add);
			update(rc,tre[u].add);
			tre[u].add=0;
		}
	}
	void build(int u,int l,int r)
	{
		if(l==r)
		{
			tre[u].sum=0;
			tre[u].cnt1=1;
			tre[u].cnt2=0;
			tre[u].minn=inf;
			tre[u].add=0;
			tre[u].val=0;
			tre[u].b1=b[l];
			tre[u].b2=0;
			return;
		}
		int mid=(l+r)/2;
		build(lc,l,mid);
		build(rc,mid+1,r);
		pushup(u);
	}
	void turn(int u,int l,int r,int x,int k)
	{
		if(l==r)
		{
			if(tre[u].cnt1==1&&k==2)k=0;//考虑特殊情况的赦免 
			if(k==0)
			{
				tre[u].cnt1=0;
				tre[u].cnt2=0;
				tre[u].minn=inf;
				tre[u].b1=0;
				tre[u].b2=0;
			}
			if(k==1)
			{
				tre[u].cnt1=1;
				tre[u].cnt2=0;
				tre[u].minn=inf;
				tre[u].b1=b[l];
				tre[u].b2=0;
			}
			if(k==2)
			{
				tre[u].cnt1=0;
				tre[u].cnt2=1;
				tre[u].minn=tre[u].sum;
				tre[u].b1=0;
				tre[u].b2=b[l];
			}
			return;
		}
		int mid=(l+r)/2;
		pushdown(u);
		if(x<=mid)turn(lc,l,mid,x,k);
		else turn(rc,mid+1,r,x,k);
		pushup(u);
	}//
	void Clear(int u,int l,int r,int x)
	{
		if(l==r)
		{
			tre[u].val=tre[u].b1=tre[u].b2=tre[u].sum=tre[u].cnt1=tre[u].cnt2=0;
			tre[u].minn=inf;
			return;
		}
		int mid=(l+r)/2;
		pushdown(u);
		if(x<=mid)Clear(lc,l,mid,x);
		else Clear(rc,mid+1,r,x);
		pushup(u);
	}//
	vector<int>opr;
	void add(int u,int l,int r,int k)//这里保证了k总会 
	{
		if(u==1)opr.clear();
		if(tre[u].minn>k)//第二类点的min>k也就是说没有会被删除的数 
		{
			update(u,k);
			return;
		}
		if(l==r)//这里处理的都是第二类点为k的情况 
		{
			opr.pb(l);
			return;
		}
		int mid=(l+r)/2;
		pushdown(u);
		add(lc,l,mid,k);
		add(rc,mid+1,r,k);
		pushup(u);
		if(u==1)
		{
			for(auto i:opr)
			{
				if(b[lst[i]]>b[nxt[i]])
				turn(1,1,n,lst[i],2);
				else if(nxt[i]<=n)
				{
					if(b[nxt[i]]>b[nxt[nxt[i]]]) 
					turn(1,1,n,nxt[i],2);
					else
					turn(1,1,n,nxt[i],0);
				}
				//第一个是不会被删除的，所以只用考虑最后一个的特殊情况 
				nxt[lst[i]]=nxt[i];
				lst[nxt[i]]=lst[i];
				Clear(1,1,n,i);
			}
		}//这么写防止在最底层的时候去调用函数导致push混乱 
	}//注意第一遍的写法用于优化实现，常数问题待会再说 
	int query(int u,int l,int r,int x) 
	{
		if(l==r)
		return x*b[l];
		int mid=(l+r)/2;
		pushdown(u);
		if(tre[lc].sum<=x)
		return tre[lc].val+query(rc,mid+1,r,x-tre[lc].sum);
		else return query(lc,l,mid,x);
	}//找到presum第一个>=x的位置 
	int init_query(int u,int l,int r,int x) 
	{
		if(l==r)
		return tre[u].sum;
		int mid=(l+r)/2;
		pushdown(u);
		if(x>mid)
		return tre[lc].sum+init_query(rc,mid+1,r,x);
		else return init_query(lc,l,mid,x);
	}//前缀颜色段长度之和 
	
	int Query(int l,int r,int sc)//l,r,所属连通块 
	{
		int pos=DSU::minn[DSU::fa(sc)];
		if(pos!=1)
		{
			int delta=st[pos]-1-init_query(1,1,n,pos-1);
			l-=delta;
			r-=delta;
		}
		return query(1,1,n,r)-query(1,1,n,l-1);
	}//那么一次询问就应该改成找到上一个联通的位置，从这个位置开始算x 
}using namespace SGT;
namespace LL
{
	int tre[N<<2];
	void build(int u,int l,int r)
	{
		if(l==r)
		{
			tre[u]=a[l];
			return;
		}
		int mid=(l+r)/2;
		build(lc,l,mid);
		build(rc,mid+1,r);
		tre[u]=max(tre[lc],tre[rc]);
	}
	int query(int u,int l,int r,int x,int y)
	{
		if(x<=l&&r<=y)
		return tre[u];
		int a=0,b=0,mid=(l+r)/2;
		if(x<=mid)a=query(lc,l,mid,x,y);
		if(y>mid)b=query(rc,mid+1,r,x,y);
		return max(a,b);
	}//max 
}//特判-1用 
namespace SAMIN
{
	struct sx
	{
		int sum;//段长之和
		int val;//权值之和 
		int tag;//推平操作 
	}tre[N<<2];
	void pushup(int u)
	{
		tre[u].val=tre[lc].val+tre[rc].val;
	}
	void update(int u,int k) 
	{
		tre[u].val=tre[u].sum*k;
		tre[u].tag=k;
	}
	void pushdown(int u)
	{
		if(tre[u].tag)
		{
			update(lc,tre[u].tag);
			update(rc,tre[u].tag);
			tre[u].tag=0;
		}
	}
	void build(int u,int l,int r)
	{
		if(l==r)
		{
			tre[u].sum=a[l];
			tre[u].tag=0;
			return;
		}
		int mid=(l+r)/2;
		build(lc,l,mid);
		build(rc,mid+1,r);
		tre[u].sum=tre[lc].sum+tre[rc].sum;
		pushup(u);
	}
	void add(int u,int l,int r,int x,int y,int k)//后缀取min 
	{
		if(x<=l&&r<=y)
		{
			update(u,k);
			return;
		}
		int mid=(l+r)/2;
		pushdown(u);
		if(x<=mid)add(lc,l,mid,x,y,k);
		if(y>mid)add(rc,mid+1,r,x,y,k);
		pushup(u);
	}
	int query(int u,int l,int r,int x)
	{
		if(l==r)
		return x*tre[u].val/tre[u].sum;
		int mid=(l+r)/2;
		pushdown(u);
		if(tre[lc].sum<=x)
		return tre[lc].val+query(rc,mid+1,r,x-tre[lc].sum);
		else return query(lc,l,mid,x);
	}//找到presum第一个>=x的位置 
	struct opt
	{
		int l,r,val;
	};
	void getans()
	{
		stack<opt>stk;
		stk.push(opt{n+1,n+1,-inf});
		build(1,1,n);
		per(i,n,1)
		{
			while(stk.top().val>=b[i])
			stk.pop();
			int r=stk.top().l-1;
			stk.push(opt{i,r,b[i]});
			add(1,1,n,i,r,b[i]);
			for(auto u:qx[i])
			{
				ans[u.sed]+=query(1,1,n,u.fst)-query(1,1,n,st[i]-1);
			}
		}
	}
}
bool MT;
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	DSU::init();
	rep(i,1,n)
	cin>>a[i];
	rep(i,1,n)
	cin>>b[i];
	st[1]=1;
	rep(i,2,n+1)
	st[i]=st[i-1]+a[i-1];
	rep(i,1,n)
	{
		upd.insert(a[i]);
		tag[i]=1; 
		lnk[a[i]].pb(i);//注意到链接时这个一定没有被删除 
		lst[i]=i-1;
		nxt[i]=i+1;
	}
	b[n+1]=-inf;st[0]=-inf;
	LL::build(1,1,n);
	rep(i,1,m)
	{
		int l,r,u;
		cin>>l>>r>>u;
		if(LL::query(1,1,n,l,r-1)>u)//如果最大值比u更大，那么则说明走不了
		{
			ans[i]=-1;
			continue;
		}
		int x=max(min(st[l-1]+u,st[r]),st[l]);
		if(st[l]<=x-1)
		qx[l].pb(mp(x-1,i));//询问[l,x-1]
		l=st[l];
		int hr=r-1;
		r=st[r]-1;
		if(x<=r)
		q[u].pb({x,r,i,hr});//询问[x,r] 
		upd.insert(u);
	}
	build(1,1,n);
	int now=0;
	for(auto u:upd)
	{
		int delta=u-now;
		while(delta)
		{
			int val=min(tre[1].minn,delta);
			add(1,1,n,val);
			delta-=val;
			now+=val;
		}
		if(u<=2e5)
		for(auto i:lnk[u])
		{
			if(b[i]>b[nxt[i]])
			turn(1,1,n,i,2);
			else if(nxt[i]<=n)
			{
				if(b[nxt[i]]>b[nxt[nxt[i]]]) 
				turn(1,1,n,nxt[i],2);
				else
				turn(1,1,n,nxt[i],0);
			}
			DSU::merge(i,nxt[i]);
			//链接 
		}
		
		if(q.count(u))
		for(auto v:q[u])
		ans[v.from]+=Query(v.l,v.r,v.sc);
		//询问 
	}
	SAMIN::getans();
	rep(i,1,m)
	cout<<ans[i]<<'\n';
	cerr<<"Memory:"<<(&MS-&MT)/1048576.0<<"MB Time:"<<clock()/1000.0<<"s\n";
}
```

---

## 作者：ningago (赞：0)

考虑单组询问，一些较为明显的观察：如果没有油量的限制，那么每一条边的油，都来自于它对应油费的前缀最小值。

加上油量也差不多，对于一个点 $i$，假设在这里加油，那么加到 $b_j \leq b_i$ 的最小的 $j$ 就不会再加了，或者油量满了也不会再加了。

可以求一个前缀和 $pre_i=\sum_{j=1}^{i-1}a_j$，看做每个点在由油量构成的数轴上的位置。

那么对于每个点，可以用一个区间 $[l_i,r_i]$ 描述每个点对油量贡献了哪一段。计算方式：

- $l_i=\max(pre_i,pre_{lst_i}+U)$，$lst_i$ 表示最大的 $b_{lst_i}<b_i$ 的点，意思是要么从这个点直接开始，要么以前已经加过一些了。
- $r_i=\min(pre_i+U, pre_{nxt_i})$，$nxt_i$ 表示最小的 $b_{nxt_i}\leq b_i$ 的点，意思是要么加满，要么有更优的。

现在 $T=n+1$ 的部分分就好做了，因为每个点的 $lst,nxt$ 只会有 $O(1)$ 的变化量，所以可以直接从后往前对 $S$ 扫描线，$\sum (r_i-l_i)\times b_i$ 是一个区间加一次函数的形式，树状数组就可以了（注意 $pre_{lst_i}+U\geq pre_{nxt_i}$ 时区间是空，而不是负数）。

而对于 $T$ 任意的情况，发现 $l_i,r_i$ 只和前驱后继有关，所以找到 $[pre_T-U,pre_T]$ 内的 $b$ 最小的 $p$，此时只有 $p$ 的 $nxt$ 变化是有影响的。所以只需要差分掉 $S,p$ 的 $T=n+1$ 的答案，然后再直接加上 $b_p\times (pre_T-pre_p)$ 的贡献即可。

复杂度 $O(n\log n)$。

```cpp
#define N 200110
int n, m;
int a[N], b[N], tmp[N], hb[N];
int l_[N], r_[N], u_[N];
struct RMQ
{
	pii ST[N][20];
	void init(int *a, int op)
	{
		for(int i = 1; i <= n + 1; i++) ST[i][0] = mkp(a[i] * op, i);
		for(int j = 1; j < 20; j++) for(int i = 1; i + (1 << j) - 1 <= n + 1; i++) ST[i][j] = std::min(ST[i][j - 1], ST[i + (1 << (j - 1))][j - 1]);
	}
	pii query(int l, int r)
	{
		int b = hb[r - l + 1];
		return std::min(ST[l][b], ST[r - (1 << b) + 1][b]);
	}
}STA, STB;
struct node { int u, i, op; };
std::vector <node> qvec[N];
int ans[N], pre[N];
int nxt[N], sta[N], top;
int trk[N], trb[N];
struct Lish
{
	int sta[N], top;
	void ins(int x) { sta[++top] = x; }
	void build() { std::sort(sta + 1, sta + 1 + top); top = std::unique(sta + 1, sta + 1 + top) - sta - 1; }
	int lower(int x) { return std::lower_bound(sta + 1, sta + 1 + top, x) - sta; }
	int upper(int x) { return std::upper_bound(sta + 1, sta + 1 + top, x) - sta; }
}X;
void ins(int x, int k, int b) { for(; x <= X.top; x += x & (-x)) trk[x] += k, trb[x] += b; }
void ins(int l, int r, int k, int b) 
{ 
	l = X.lower(l); r = X.upper(r) - 1;
	if(l > r) return;
	ins(l, k, b); ins(r + 1, -k, -b);
}
int queryk(int x) { int res = 0; for(; x; x -= x & (-x)) res += trk[x]; return res; }
int queryb(int x) { int res = 0; for(; x; x -= x & (-x)) res += trb[x]; return res; }
int query(int x) { return queryk(X.lower(x)) * x + queryb(X.lower(x)); }

void solve()
{
//	memset(h, idx = -1, sizeof(h));
	n = read(), m = read();
	for(int i = 1; i <= n; i++) a[i] = read();
	for(int i = 1; i <= n; i++) b[i] = read();
	b[n + 1] = 0;
	pre[0] = -2000000000ll;
	for(int i = 2; i <= n + 1; i++) pre[i] = pre[i - 1] + a[i - 1];
	STA.init(a, -1); STB.init(b, 1);
	for(int i = 1, l, r, u; i <= m; i++) 
	{
		l = l_[i] = read(), r = r_[i] = read(), u = u_[i] = read();
		X.ins(u_[i]);
		if(-STA.query(l, r - 1).fi > u) { ans[i] = -1; continue; }
		int p = std::lower_bound(pre + 1, pre + 2 + n, pre[r] - u) - pre;
		ckmax(p, l); pii tmp = STB.query(p, r);
		p = tmp.se;
		ans[i] += tmp.fi * (pre[r] - pre[p]);
		qvec[l].push_back((node){u, i, 1});
		qvec[p].push_back((node){u, i, -1});
	}
	X.build();
	sta[++top] = n + 1; 
	for(int i = n; i >= 1; i--)
	{
		auto push = [&](int x, int y, int z, int op) -> void
		{
			int base = pre[y] - pre[x], c2 = base, c1 = pre[z] - pre[y], lim = pre[z] - pre[x] - 1;
			// base + min(c1, U) - max(c2, U)
			if(c1 <= c2)
			{
				ins(1, std::min(c1 - 1, lim), 1 * op, (base - c2) * op);
				ins(c1, std::min(c2, lim), 0, (base + c1 - c2) * op);
				ins(c2 + 1, lim, -1 * op, (base + c1) * op);
			}
			else
			{
				ins(1, std::min(c2 - 1, lim), 1 * op, (base - c2) * op);
				ins(c2, std::min(c1, lim), 0, (base) * op);
				ins(c1 + 1, lim, -1 * op, (base + c1) * op);
			}
		};
		for(; top && b[sta[top]] > b[i]; push(0, sta[top], nxt[sta[top]], -b[sta[top]]), push(i, sta[top], nxt[sta[top]], b[sta[top]]), top--);
		nxt[i] = sta[top]; push(0, i, sta[top], b[i]); sta[++top] = i;
		for(node t : qvec[i]) ans[t.i] += query(t.u) * t.op;
	}
	for(int i = 1; i <= m; i++) print(ans[i], '\n');
}

void init()
{
	int n = N - 10;
	hb[0] = -1;
	for(int i = 1; i <= n; i++) hb[i] = hb[i >> 1] + 1;
}
```

---

