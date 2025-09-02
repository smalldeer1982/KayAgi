# [ABC136F] Enclosed Points

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc136/tasks/abc136_f

$ 2 $ 次元平面上の $ N $ 個の点からなる集合 $ S $ があり、$ i $ 番目の点の座標は $ (x_i,\ y_i) $ です。$ N $ 個の点の $ x $ 座標、$ y $ 座標はそれぞれ相異なります。

$ S $ の空でない部分集合 $ T $ に対して $ f(T) $ を、各辺が座標軸と平行であって $ T $ の点を全て含むような最小の長方形に含まれる点の個数として定義します。より正確には、

- $ f(T)\ :=\ T $ に含まれる点について $ x $ 座標の最小値と最大値を それぞれ $ a,\ b $, そして $ y $ 座標の最小値と最大値をそれぞれ $ c,\ d $ としたとき、$ a\ \leq\ x_i\ \leq\ b $ かつ $ c\ \leq\ y_i\ \leq\ d $ を満たす $ 1\ \leq\ i\ \leq\ N $ の個数

$ S $ の空でない全ての部分集合 $ T $ についての $ f(T) $ の和を計算してください。答えは非常に大きくなることがあるので、$ 998244353 $ で割った余りを出力してください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ -10^9\ \leq\ x_i,\ y_i\ \leq\ 10^9 $
- $ x_i\ \neq\ x_j\ (i\ \neq\ j) $
- $ y_i\ \neq\ y_j\ (i\ \neq\ j) $
- 入力は全て整数である

### Sample Explanation 1

$ 1,\ 2,\ 3 $ 番目の点をそれぞれ $ P_1,\ P_2,\ P_3 $ とします。$ S\ =\ \{P_1,\ P_2,\ P_3\} $ の空でない部分集合は $ 7 $ 個あり、それぞれに対する $ f $ の値は次の通りです。 - $ f(\{P_1\})\ =\ 1 $ - $ f(\{P_2\})\ =\ 1 $ - $ f(\{P_3\})\ =\ 1 $ - $ f(\{P_1,\ P_2\})\ =\ 2 $ - $ f(\{P_2,\ P_3\})\ =\ 2 $ - $ f(\{P_3,\ P_1\})\ =\ 3 $ - $ f(\{P_1,\ P_2,\ P_3\})\ =\ 3 $ これらの和は $ 13 $ です。

### Sample Explanation 3

和を $ 998244353 $ で割った余りを出力することに注意してください。

## 样例 #1

### 输入

```
3
-1 3
2 1
3 -2```

### 输出

```
13```

## 样例 #2

### 输入

```
4
1 4
2 1
3 3
4 2```

### 输出

```
34```

## 样例 #3

### 输入

```
10
19 -11
-3 -12
5 3
3 -15
8 -14
-9 -20
10 -9
0 2
-7 17
6 -6```

### 输出

```
7222```

# 题解

## 作者：chenxia25 (赞：10)

首先感觉无从下手？考虑换一个对答案的贡献体（这是个惯用套路）（一开始是点的集合，后来我又想换成矩形，发现仍然不可做，就偏偏没有想到换成点）。

显然，点对答案的贡献就是有多少个集合生成的矩形包含这个点。知道了这个就并不是很难了。我们考虑以该点为原点建立平面直角坐标系，然后集合有两种情况：
1. 包含该点，此时矩形显然一定包含该点，则贡献是 $2^{n-1}$；
1. 不包含该点。那么显然，该点被矩形包含当且仅当一、三象限都有点或二、四象限都有点。然后四个象限的点数是个二维数点问题，这是个静态的，于是可以对一维排序来降维，从而使用 BIT 1log 解决。然后你如果把两种都算上去的话，那会有一二三四象限都有点的重复情况，那这是个简单容斥，减一下即可。

也就是，设四个象限的点数分别为 $I,II,III,IV$ 的话，那么贡献是：

$$\begin{aligned}&2^{n-1}+\\&\!\left(2^{II}-1\right)\!\left(2^{IV}-1\right)\!2^{I}2^{III}+\\&\!\left(2^{I}-1\right)\!\left(2^{III}-1\right)\!2^{II}2^{IV}-\\&\!\left(2^{II}-1\right)\!\left(2^{IV}-1\right)\!\left(2^{I}-1\right)\!\left(2^{III}-1\right)\end{aligned}$$

然后就做完了，复杂度线性对数。

**_[code](https://www.luogu.com.cn/paste/wl0p4qw3)_**

---

## 作者：_Kamisato_Ayaka_ (赞：4)

[传送门](https://www.luogu.com.cn/problem/AT_abc136_f)

## Solution

对于一个点 $i$，我们将其与其它点匹配，故有 $2^{n }- 1$ 的方案数，这是答案的初始。

对于每个点 $(x_i,y_i)$ 再建系，四个象限都可能会有点，我们此时考虑四个象限的点如何匹配，才能使 $(x_i,y_i)$ 包含其中，稍微手玩一下就可以发现，对于一四象限、二三象限的点匹配，是无法包含 $(x_i,y_i)$ 的，但是一三象限、二四象限就可以，考虑统计答案。

分别假设四个象限各有 $cnt_1,cnt_2,cnt_3,cnt_4$ 个点：

- 一三象限的答案：
  $$
  (2^{cnt_1} - 1) \times (2^{cnt_3} - 1)
  $$
- 二四象限的答案：
  $$
  (2^{cnt_2} - 1) \times (2^{cnt_4} - 1)
  $$

然而这样是在其余两个象限都没有点存在的情况下，对于其余象限的所有点，任意选择或不选择都对答案不影响，故：

- 一三象限的答案：
  $$
  (2^{cnt_1} - 1) \times (2^{cnt_3} - 1) \times 2^{cnt_2 + cnt_4}
  $$
- 二四象限的答案：
  $$
  (2^{cnt_2} - 1) \times (2^{cnt_4} - 1) \times 2^{cnt_1 + cnt_3}
  $$

显然的，这样计算肯定会算重某些情况，考虑容斥。

我们对选择一三象限作限制，钦定其只能同时再选二或四象限，这样一来，选择二四象限时，可以任意选一三象限：

- 一三象限的答案：
  $$
  (2^{cnt_1} - 1) \times (2^{cnt_3} - 1) \times 2^{cnt_2} + (2^{cnt_1} - 1) \times (2^{cnt_3} - 1) \times 2^{cnt_4}
  $$
- 二四象限的答案：
  $$
  (2^{cnt_2} - 1) \times (2^{cnt_4} - 1) \times 2^{cnt_1 + cnt_3}
  $$

这样就可以避免选重的情况，现在考虑如何维护这个东西。

这里选用线段树维护，分别维护当前点左侧、右侧点数，总复杂度 $O(n \log n)$。

## Code

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;
namespace FASTIO {
    inline int read() {
        int res = 0, f = 1;
        char ch = getchar();
        while (!isdigit (ch)) f = ch == '-' ? -1 : 1, ch = getchar();
        while (isdigit (ch)) res = (res << 1) + (res << 3) + (ch ^ 48), ch = getchar();
        return res * f;
    }
    inline void write (int x) {
        int st[33], top = 0;
        do { st[top ++] = x % 10, x /= 10; } while (x);
        while (top) putchar (st[-- top] + '0');
    }
};
using namespace FASTIO;
const int MAXN = 2e5 + 10, MOD = 998244353;
int n, cpy[MAXN], Answer, pw2[MAXN];
struct Ayaka { int x, y; } pt[MAXN];
inline bool Cmp (Ayaka s1, Ayaka s2) { return s1.x < s2.x; }
struct Segmentree { int l, r, appTim; } seg[2][MAXN << 2]; /* appTim 表示点出现的次数，即象限内点数 */

/* seg[0] 的一维维护当前点左侧点数，seg[1] 的一维维护右侧 */

inline void pushup (int rt, int p) { seg[p][rt].appTim = seg[p][rt << 1].appTim + seg[p][rt << 1 | 1].appTim; }

void Build (int l, int r, int rt, int p) {
    seg[p][rt].l = l, seg[p][rt].r = r, seg[p][rt].appTim = 0;
    if (l == r) return;
    int mid = l + r >> 1;
    Build (l, mid, rt << 1, p), Build (mid + 1, r, rt << 1 | 1, p);
    pushup (rt, p);
}

void update (int rt, int p, int pos, int k) {
    int l = seg[p][rt].l, r = seg[p][rt].r;
    if (l == r) {
        seg[p][rt].appTim += k;
        return;
    }
    int mid = l + r >> 1;
    if (pos <= mid)
        update (rt << 1, p, pos, k);
    else
        update (rt << 1 | 1, p, pos, k);
    pushup (rt, p);
}

int query (int ql, int qr, int rt, int p) {
    int l = seg[p][rt].l, r = seg[p][rt].r;
    if (ql <= l && qr >= r)
        return seg[p][rt].appTim;
    int mid = l + r >> 1, tmpAns = 0;
    if (ql <= mid)
        tmpAns = (tmpAns + query (ql, qr, rt << 1, p)) % MOD;
    if (qr > mid)
        tmpAns = (tmpAns + query (ql, qr, rt << 1 | 1, p)) % MOD;
    return tmpAns;
}

inline void Getpw2() {
    pw2[0] = 1;
    for (int i = 1; i < MAXN; i ++)
        pw2[i] = (pw2[i - 1] << 1) % MOD;
    return;
}

signed main() {
    n = read(), Getpw2();
    for (int i = 1; i <= n; i ++)
        pt[i].x = read(), pt[i].y = read(), cpy[i] = pt[i].y;
    sort (cpy + 1, cpy + n + 1), sort (pt + 1, pt + n + 1, Cmp);
    /* 将点按照 x 坐标排序 */
    Build (1, MAXN - 1, 1, 0), Build (1, MAXN - 1, 1, 1);
    for (int i = 1; i <= n; i ++) {
        int ptr = lower_bound (cpy + 1, cpy + n + 1, pt[i].y) - cpy;
        update (1, 1, ptr, 1);
        /* 先将所有点插入到当前点右侧 */
    }
    for (int i = 1; i <= n; i ++) {
        int ptr = lower_bound (cpy + 1, cpy + n + 1, pt[i].y) - cpy;
        update (1, 1, ptr, -1);
        /* 从右侧删除当前点 */
        int upL = query (1, ptr - 1, 1, 0), downL = query (1, ptr - 1, 1, 1); 
        /* 左下左上的点数 */
        int upR = query (ptr + 1, MAXN - 1, 1, 0), downR = query (ptr + 1, MAXN - 1, 1, 1);
        /* 右下右上的点数 */
        int tmpAnsL = (pw2[upL] - 1) * (pw2[downR] - 1) % MOD, tmpAnsR = (pw2[downL] - 1) * (pw2[upR] - 1) % MOD;
        Answer = ((Answer + tmpAnsL) % MOD + tmpAnsR) % MOD;
        if (downL) Answer = (Answer + tmpAnsL * (pw2[downL] - 1) % MOD) % MOD;
        /* 若左下存在点，新增答案 */
        if (upR) Answer = (Answer + tmpAnsL * (pw2[upR] - 1) % MOD) % MOD;
        /* 若右上存在点，新增答案 */
        Answer = (Answer + tmpAnsR * (pw2[upL + downR] - 1) % MOD) % MOD;
        /* 对于无限制的左上右下再次新增答案 */
        Answer = (Answer + pw2[n - 1]) % MOD;
        /* 一开始任意匹配的答案 */
        update (1, 0, ptr, 1);
        /* 向左侧插入当前点 */
    }
    write (Answer), putchar ('\n');
    return 0;
}
```

---

## 作者：KazamaRuri (赞：3)

## 题意

给定 $1 \sim n$ 的排列 $a$。

定义一个子序列 $S$ 的权值，该子序列元素形如 $\{i,a_i\}$ 的二元组，记 $l=\min_{\{i,a_i\} \in S}\ i\ ,\ r=\max\ i\ ,\ u=\min a_i,v=\max a_i$，权值即为 $\sum_{i=l}^r\ [u \le a_i \le v]$。要求出所有子序列的权值和。

## 闲话

1.19 去华附考试，上午文化课一坨，下午把含这题的简单场 AK 了（没有大样例还是有可能挂分的 55），也算找回点面子。场上切掉之后以为这题应该是个下位蓝的水准，感觉紫可能有点虚高。

## 分析

考虑每个数什么时候会被计算贡献。

把每一个数是否在子序列中表示为一个长 $n$ 的 01 字符串，那么每一个 $1$ 都有基础贡献，总贡献是 $n2^{n-1}$。简单证明：某一位是 $1$ 时剩下 $n-1$ 位任意的方案数是 $2^{n-1}$，$n$ 位加起来就是 $n2^{n-1}$。

除去上面这部分的答案，剩下的答案都是没有被选进子序列，但是“间接”被包含了。这种情况分两种：

-  左边带了至少一个比该数小的，剩下任意，右边带了至少一个比该数大的，剩下任意。
-  左大右小，剩下任意

对于方案数的统计，任意是简单的，形如 $2^k$。至少一个，就是所有情况再去掉空集，形如 $2^k-1$。记 $x$ 表示左小的数量，$y$ 表示右小，$u$ 左大，$v$ 右大，贡献即为

$$$
+(2^x-1)2^u \cdot 2^y(2^v-1) \\
+2^x(2^u-1) \cdot (2^y-1)2^v
$$$

但是这样答案偏大。仔细思考，发现两种情况都统计了，左右两边都有带大和带小的情况，容斥这掉这部分的贡献:

$$$
-(2^x-1)(2^u-1)(2^y-1)(2^v-1)
$$$

直接把上面几个式子求和即为答案。对于 $x,y,u,v$，可以用一个树状数组解决，总时间复杂度 $O(n \log n)$。

## 代码

复刻版代码，运行速度很接近最优解。

希望考场上没有因为取模什么的挂分吧，不给大样例的比赛也是挺罕见了。

```cpp
#include <bits/stdc++.h>
#define lb(x) (x&-x)
using namespace std;
using ll =long long;
const int N=2e5+5,mod=998244353;
int n,h[N],cnt,t[N],a[N]; ll pw[N],ans;
struct node{
	int x,y;
	bool operator<(const node &o)const{
		return x<o.x;
	}
}p[N];
void upd(int x,int k){ for(;x<=n;x+=lb(x)) t[x]+=k; }
int ask(int x){ int res=0; for(;x;x-=lb(x)) res+=t[x]; return res; }
int main(){
	scanf("%d",&n),pw[0]=1;
	for(int i=1;i<=n;i++)
		scanf("%d%d",&p[i].x,&p[i].y),
		pw[i]=pw[i-1]*2%mod,h[++cnt]=p[i].y;
	sort(h+1,h+1+n),sort(p+1,p+1+n);
	for(int i=1;i<=n;i++) a[i]=lower_bound(h+1,h+1+n,p[i].y)-h;
	ans=n*pw[n-1]%mod;
	for(int i=1;i<=n;i++){
		int x=ask(a[i]),y=a[i]-x-1,u=i-x-1,v=n-a[i]-u; upd(a[i],1);
		(ans+=(pw[x]-1)*pw[y]%mod*pw[u]%mod*(pw[v]-1)%mod)%=mod;
		(ans+=pw[x]*(pw[y]-1)%mod*(pw[u]-1)%mod*pw[v]%mod)%=mod;
		(ans-=(pw[x]-1)*(pw[y]-1)%mod*(pw[u]-1)%mod*(pw[v]-1)%mod)%=mod;
	}
	return printf("%lld",(ans+mod)%mod)&0;
}
```

---

## 作者：HD0X (赞：3)

没想到容斥，只会神经做法，**拿下最劣解**。

题意略。

考虑 dp ~~然鹅不用~~，先将点按横坐标排序，设 $f_i$ 表示只考虑前 $i$ 个点的答案，显然有：
$$
f_i=2f_{i-1} + 2^{i-1} + 额外贡献
$$
解释一下，就是一份 $f_{i-1}$ 本身，一份所有 $2^{i-1}$ 的方案带上 $i$ 号点和额外附带点数。

一个点会被额外计算，只有左上-右下和右上-左下，所以到 $i$ 点考虑分开计算比它高的和比它低的，离散化后开权值线段树即可。我们只举例左上-右下的。

具体来说，对于 $j$ 号点，在它前面比它高的点数记为 $x$，则此时它所做的额外贡献为 $(\text{2}^{x}-\text{1}) \times \text{2}^{i-x-\text{2}}$。所以再开一棵线段树，走一步对于全局乘 $\text{2}$，在 $i$ 号点加入 $i-\text{1}$ 号点的贡献，加上比 $i$ 号点高的贡献和即可。

然后错飞。

因为你会发现，有一些组合已经计算了某些点的额外贡献了，就是在 $j$ 之后比它低的点和前面的 $x$ 个点的组合，所以每一次只在$\text{1}$ ~ $y_i$ 间乘 $\text{2}$，比它低的就不会对它造成影响。

[依旧错飞，一个点都过不了。](https://atcoder.jp/contests/abc136/submissions/61679182)

~~给张图~~给组数据

```cpp
10
1 4
2 8
3 10
4 5
5 9
6 7
7 6
8 2
9 1
10 3
```
在前 $\text{7}$ 个点内，答案是 $\text{552}$ 没有问题，但是第 $\text{8}$ 个点处答案应是 $\text{1355} $，而程序跑出来是 $\text{1376}$。

经手模可以发现第 $\text{4}$ 个点做出了 $\text{48}$ 的贡献，而实际上只有 $\text{27}$ 的贡献，哪里算多了捏？

实际上是第 $\text{1}$ 个点和第 $\text{5,6,7}$ 个点的组合算重了，它们属于右上-左下的情况！算重的本质是 $j$ 号点之前比它低的和它之后比它高的不能搭在一起，所以前面那一部分再开一棵线段树维护，区间乘只对后面的部分操作，即可 [AC](https://atcoder.jp/contests/abc136/submissions/61679263) 本题，四棵线段树喜提最劣解。

代码在记录里。

---

## 作者：xtx1092515503 (赞：2)

容斥一般题。

我们考虑对于一个点，它何时能够被包含在一个矩形中：

我们以该点为原点，建立平面直角坐标系。则显然，没有在坐标轴上的点（因为题目保证了 $x,y$ 坐标互不相同）。则，只要 $\text{I},\text{III}$ 象限中各至少有一个点，该点就会被包含在矩形当中；同理，只要 $\text{II},\text{IV}$ 象限中各至少有一个点，该点仍会被包含在矩形当中。同时，我们需要容斥一下，减掉四个象限中都有点的情形。

同时，以上所有情形都是在该点未出现在集合内的情况下才能被考虑的；当该点本身就在集合内时，它必定存在于矩形内。

于是，我们设 $\text{I},\text{II},\text{III},\text{IV}$ 分别表示 $2^{\text{各象限内的节点数}}$，则有该节点共在

$$(\text{I}-1)\text{II}(\text{III}-1)\text{IV}+\text{I}(\text{II}-1)\text{III}(\text{IV}-1)-(\text{I}-1)(\text{II}-1)(\text{III}-1)(\text{IV}-1)+2^{n-1}$$

个集合内出现了。

于是我们就二维数点一下求出每个节点四个象限内的节点数即可。时间复杂度 $O(n\log n)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;
int n,a[200100][4],s[200100],t[200100],ord[200100],bin[200100],res;
pair<int,int>p[200100];
void ADD(int x){
	for(int i=x;i;i-=i&-i)s[i]++;
	for(int i=x;i<=n;i+=i&-i)t[i]++;
}
int SS(int x){int ret=0;while(x<=n)ret+=s[x],x+=x&-x;return ret;}
int TT(int x){int ret=0;while(x)ret+=t[x],x-=x&-x;return ret;}
int main(){
	scanf("%d",&n),bin[0]=1;
	for(int i=1;i<=n;i++)scanf("%d%d",&p[i].first,&p[i].second),ord[i]=i,bin[i]=(bin[i-1]<<1)%mod;
	sort(ord+1,ord+n+1,[](int u,int v){return p[u].first<p[v].first;});
	for(int i=1;i<=n;i++)p[ord[i]].first=i;
	sort(ord+1,ord+n+1,[](int u,int v){return p[u].second<p[v].second;});
//	for(int i=1;i<=n;i++)printf("%d %d\n",p[i].first,p[i].second);
	memset(s,0,sizeof(s)),memset(t,0,sizeof(t));
	for(int i=1;i<=n;i++)a[ord[i]][0]=SS(p[ord[i]].first),a[ord[i]][1]=TT(p[ord[i]].first),ADD(p[ord[i]].first);
	memset(s,0,sizeof(s)),memset(t,0,sizeof(t));
	for(int i=n;i>=1;i--)a[ord[i]][2]=SS(p[ord[i]].first),a[ord[i]][3]=TT(p[ord[i]].first),ADD(p[ord[i]].first);
	for(int i=1;i<=n;i++){
		for(int j=0;j<4;j++)a[i][j]=bin[a[i][j]];
		(res+=1ll*(a[i][0]-1)%mod*(a[i][3]-1)%mod*a[i][1]%mod*a[i][2]%mod)%=mod;
		(res+=1ll*(a[i][1]-1)%mod*(a[i][2]-1)%mod*a[i][0]%mod*a[i][3]%mod)%=mod;
		(res+=mod-1ll*(a[i][0]-1)%mod*(a[i][1]-1)%mod*(a[i][2]-1)%mod*(a[i][3]-1)%mod)%=mod;
		(res+=bin[n-1])%=mod;
	}
	printf("%d\n",res);
	return 0;
}
```

---

## 作者：Composite_Function (赞：1)

这类难以枚举的题直接考虑拆贡献，考虑每个点单独的贡献。

首先如果 $P$ 在 $T$ 中出现，那么 $P$ 肯定计入贡献。对每个 $P$ 这样的 $T$ 有 $2^{n-1}$ 个。

其次就是 $P$ 不在 $T$ 中出现但被计入贡献，这一定是关于 $P$ 为原点的坐标系上 $T$ 中的点有出现在一三或二四象限。各个象限的点可以用二位数点的各种套路计算。那么经过简单容斥即可。

---

```cpp
#include <bits/stdc++.h>
using namespace std;

struct FastIO {
	inline FastIO& operator >> (short& x) {
		x = 0;
		char f = 0, ch = getchar();
		while (ch > '9' || ch < '0') f |= (ch == '-'), ch = getchar();
		while (ch <= '9' && ch >= '0') x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
		return x = (f ? -x : x), *this;
	}
	inline FastIO& operator >> (int& x) {
		x = 0;
		char f = 0, ch = getchar();
		while (ch > '9' || ch < '0') f |= (ch == '-'), ch = getchar();
		while (ch <= '9' && ch >= '0') x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
		return x = (f ? -x : x), *this;
	}
	inline FastIO& operator >> (long long& x) {
		x = 0;
		char f = 0, ch = getchar();
		while (ch > '9' || ch < '0') f |= (ch == '-'), ch = getchar();
		while (ch <= '9' && ch >= '0') x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
		return x = (f ? -x : x), *this;
	}
	inline FastIO& operator >> (double& x) {
		x = 0;
		char f = 0, ch = getchar();
		double d = 0.1;
		while (ch > '9' || ch < '0') f |= (ch == '-'), ch = getchar();
		while (ch <= '9' && ch >= '0') x = x * 10 + (ch ^ 48), ch = getchar();
		if (ch == '.') {
			ch = getchar();
			while (ch <= '9' && ch >= '0') x += d * (ch ^ 48), d *= 0.1, ch = getchar();
		}
		return x = (f ? -x : x), *this;
	}
} rin;

#define ll long long
#define uint unsigned int
#define reg register
#define ld long double
#define uint unsigned int
#define ull unsigned long long
#define qint const int&
#define qll const ll&
#define quint cosnt uint&
#define qull const ull&
#define endl "\n"

inline void qmod(int& x, const int& mod) {
	x = x >= mod? x - mod : x;
}

const int N = 2e5 + 10, mod = 998244353;
int n, x[N], y[N], lshx[N], lshy[N], pw[N];
int *topx, *topy;
int id[N], bit1[N], bit2[N];
inline bool comp(int idx, int idy) {
	return x[idx] < x[idy];
}
inline void add(int *bit, int x) {
	while (x <= n) ++bit[x], x += x & (-x);
}
inline void del(int *bit, int x) {
	while (x <= n) --bit[x], x += x & (-x);
}
inline int ask(int *bit, int x) {
	int res = 0;
	while (x) res += bit[x], x -= x & (-x);
	return res;
}

signed main() {
	rin >> n, pw[0] = 1;
	for (int i = 1; i <= n; ++i) {
		rin >> x[i] >> y[i], id[i] = i;
		lshx[i] = x[i], lshy[i] = y[i];
		pw[i] = pw[i - 1] << 1;
		if (pw[i] >= mod) pw[i] -= mod;
	}
	sort(lshx + 1, lshx + n + 1);
	topx = unique(lshx + 1, lshx + n + 1);
	sort(lshy + 1, lshy + n + 1);
	topy = unique(lshy + 1, lshy + n + 1);
	for (int i = 1; i <= n; ++i) {
		x[i] = lower_bound(lshx + 1, topx, x[i]) - lshx;
		y[i] = lower_bound(lshy + 1, topy, y[i]) - lshy;
		add(bit2, y[i]);
	}
	sort(id + 1, id + n + 1, comp);
	int res = 0;
	for (int I = 1; I <= n; ++I) {
		int i = id[I];
		int i1 = ask(bit1, y[i]);
		int i2 = I - 1 - i1;
		int i4 = ask(bit2, y[i]) - 1;
		int i3 = n - I - i4;
		res += pw[n - 1];
		res = (res + 1ll * (pw[i1] - 1) * pw[i2] % mod * (pw[i3] - 1) % mod * pw[i4]) % mod;
		res = (res + 1ll * pw[i1] * (pw[i2] - 1) % mod * pw[i3] % mod * (pw[i4] - 1)) % mod;
		res = (res - 1ll * (pw[i1] - 1) * (pw[i2] - 1) % mod * (pw[i3] - 1) % mod * (pw[i4] - 1) % mod) % mod;
		if (res < 0) res += mod;
		add(bit1, y[i]), del(bit2, y[i]);
	}
	cout << res << endl;
	return 0;
}
```

---

## 作者：KMYC (赞：1)

很好的思维题 这题看上去很难~~实际一点都不简单~~。

首先，我们肯定不能枚举点集，因为很显然时间复杂度太高了。

既然不能看点集，那可以看点，可以看这个点被多少个集合生成的矩形所包含。

用 LD,RD,LU,RU 四个数组表示以该点为原点所建立的平面直角坐标系的四个象限，当四个象限都有点时可以组成矩形。

但是本身包含该点的点集所组成的矩形也要算，但是与上面那种情况有冲突，所以要用容斥处理一下。

难点在于计算 LD,RD,LU,RU，这点可以树状数组解决。

AC 代码

```c++
#include<iostream>
#include<algorithm>
using i64=long long;
const i64 mod=998244353;
const int maxn=200001;
int n;
int x[maxn],y[maxn],LD[maxn],RD[maxn],LU[maxn],RU[maxn];
i64 pw[maxn];
struct point{ int x,y,id; }a[maxn];
bool by_x(point lhs,point rhs){ return lhs.x<rhs.x; }
bool by_y(point lhs,point rhs){ return lhs.y<rhs.y; }
int t[maxn];
void add(int k){
   while(k<=n) t[k]++,k+=k&-k;
}
int sum(int k){
   int s=0;
   while(k>0) s+=t[k],k-=k&-k;
   return s;
}
int q[maxn];
void solve(int c[]){
   for(int i=0;i<n;i++) q[x[i]]=i;
   for(int i=1;i<=n;i++) t[i]=0;
   for(int r=0;r<n;++r){
      	int i=q[r];
      	c[i]=sum(y[i]);
      	add(y[i]+1);
   }
} 
int main(){
	std::cin>>n;
    for(int i=0;i<n;i++) std::cin>>x[i]>>y[i],a[i].id=i,a[i].x=x[i],a[i].y=y[i];
    std::sort(a,a+n,by_x);
    for(int rank=0;rank<n;++rank) x[a[rank].id]=rank;
    std::sort(a,a+n,by_y);
    for(int rank=0;rank<n;++rank) y[a[rank].id]=rank;
    solve(LD);
    for(int i=0;i<n;i++) x[i]=n-1-x[i];
    solve(RD);
    for(int i=0;i<n;i++) y[i]=n-1-y[i];
    solve(RU);
    for(int i=0;i<n;i++) x[i]=n-1-x[i];
    solve(LU);
    for(int i=0;i<n;i++) y[i]=n-1-y[i];
    pw[0]=1;
    for(int i=1;i<=n;i++) pw[i]=2*pw[i-1]%mod;
    i64 sum=0;
    for(int i=0;i<n;i++){
        sum+=pw[n];
        sum-=pw[RU[i]+LU[i]];
        sum-=pw[RD[i]+LD[i]];
        sum-=pw[RD[i]+RU[i]];
        sum-=pw[LD[i]+LU[i]];
		sum-=1;
        sum+=pw[RU[i]];
        sum+=pw[LU[i]];
        sum+=pw[RD[i]];
        sum+=pw[LD[i]];
        sum%=mod;
    }
    std::cout<<(sum+mod)%mod<<"\n";
	return 0;
}
```

---

## 作者：AAA404 (赞：0)

拿到这个题，第一想法是变换主体。

不可能去枚举点集，因为这样状态数是 $O(2^n)$ 的，所以要枚举点，考虑一个点会被哪些矩形包含，这样状态数才是 $O(n)$。

（以下记右上，左上，左下，右下方点个数为：$c_1,c_2,c_3,c_4$。）

先写一个~~显然~~的前置结论：在一个大小为 $n$ 的点集中至少选一个的方案数为 $2^n-1$：所有状态数为 $2^n$，减去全部不选的一个。

画个图分类讨论（当然我没画，脑补一下就好）：

- 平凡类型：选这个点，其他点选或不选均可，对答案贡献是 $2^{n-1}$。

- A 类：在左上角和右下角各选一个，左下和右上选或不选均可，方案数为 $(2^{c_2}-1)(2^{c_4}-1)2^{c_1}2^{c_3}$。

- B 类：类比 A 类，在右上角和左下角各选一个，右下和左上选或不选均可，方案数为 $(2^{c_1}-1)(2^{c_3}-1)2^{c_2}2^{c_4}$。

- C 类：考虑在 A,B 两类中，选或不选的点全部选上，这一部分的答案在 A 和 B 中都被计算，实际上只应计算一次，故减去这一部分为 $(2^{c_1}-1)(2^{c_2}-1)(2^{c_3}-1)(2^{c_4}-1)$。

那么单个点的贡献就是 $2^{n-1}+A+B-C$。

计算出每个点对应四个方向上的点的个数即可，题目保证 $x,y$ 互不相同，省去了很多麻烦，这是简单的二维数点（偏序）问题，排序后 BIT 可以做到 $O(n\log n)$。

代码不放了，相当好写，放在 F 题是水了一点。

---

## 作者：Leaper_lyc (赞：0)

经典套路。

考虑每个点能被多少个矩形覆盖。

以该点为原点，建立平面直角坐标系。那么其他点就被分成了四类。

![](https://cdn.luogu.com.cn/upload/image_hosting/uwpdpvvb.png)

接下来分为两种情况：

- 第一种，选出的点集里包含原点 $O$，那么 $O$ 必选，其他点可选可不选，总共为 $2^{n-1}$ 种方案。
- 第二种，选出的点集里不包括原点 $O$，那么符合要求的矩形一定是下图所示的模样，即跨过了点 $O$。

![](https://cdn.luogu.com.cn/upload/image_hosting/r6qb5kr9.png)

那么这个矩形怎么找呢？

记四个象限内的点的数量分别为 $c_1,c_2,c_3,c_4$。

显然，在一三象限里分别**至少**选出一个点，就一定能保证选出的矩形合法（因为这样一定会覆盖原点），这样另外两个象限里的点可选可不选，总方案就是 $A=(2^{c_1}-1)(2^{c_3}-1)2^{c_2+c_4}$。

二四象限内分别至少选出一个点的方案同理，为 $B=(2^{c_2}-1)(2^{c_4}-1)2^{c_1+c_3}$。

但是这样会重复计算，还需要一个最简单的容斥，还要减去四个象限都有选点的情况：$C=(2^{c_1}-1)(2^{c_2}-1)(2^{c_3}-1)(2^{c_4}-1)$。

所以对于单个点的答案就是 $2^{n-1}+(A+B-C)$。

可以用两个树状数组高效维护出 $c_1,c_2,c_3,c_4$ 的值，先将 $y$ 离散化，第一个树状数组里存储所有横坐标小于 $x_i$ 的点，第二个树状数组里存储所有横坐标大于 $x_i$ 的点，那么从小到大扫一遍就行了。

具体看代码：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define int long long
const int N = 2e5 + 10;
const int mod = 998244353;
int n, m, ans;
int b[N], pw[N];
struct node {
    int x, y;
    bool operator<(const node &ert) const {
        return x < ert.x;
    }
} p[N];
struct BIT {
    int c[N];
    inline void add(int x, int v) {
        for (; x <= m; x += x & (-x)) c[x] += v;
    }
    inline int qry(int x) {
        int res = 0;
        for (; x; x -= x & (-x)) res += c[x];
        return res;
    }
} T1, T2;
signed main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> p[i].x >> p[i].y, b[i] = p[i].y;
    pw[0] = 1;
    for (int i = 1; i <= n; i++) pw[i] = pw[i - 1] * 2ll % mod;
    sort(b + 1, b + n + 1);
    m = unique(b + 1, b + n + 1) - b - 1;
    for (int i = 1; i <= n; i++)
        p[i].y = lower_bound(b + 1, b + m + 1, p[i].y) - b;
    sort(p + 1, p + m + 1);
    for (int i = 1; i <= n; i++) T2.add(p[i].y, 1); // 注意，最开始要把所有数都先加到第二个 BIT 里；因为我是从小到大扫一遍的。
    ans = n * pw[n - 1];
    for (int i = 1; i <= n; i++) {
        T2.add(p[i].y, -1);
        int c1 = (n - i) - T2.qry(p[i].y);
        int c2 = (i - 1) - T1.qry(p[i].y);
        int c3 = T1.qry(p[i].y - 1);
        int c4 = T2.qry(p[i].y - 1);
        T1.add(p[i].y, 1);
        int A = (pw[c1] - 1) * (pw[c3] - 1) % mod * pw[c2 + c4] % mod;
        int B = (pw[c2] - 1) * (pw[c4] - 1) % mod * pw[c1 + c3] % mod;
        int C = (pw[c1] - 1) * (pw[c2] - 1) % mod * (pw[c3] - 1) % mod * (pw[c4] - 1) % mod;
        ans += (A + B - C + mod) % mod;
        ans %= mod;
        // cout << A + B - C << '\n';
    }
    cout << ans;
}
```

---

## 作者：Link_Cut_Y (赞：0)

题意经过转化后变成：对于每个点，其贡献为包含该点的矩形个数。求每个点的贡献和。

考虑对于当前点 $p$，以该点为坐标原点，做出笛卡尔坐标系。四个象限内的点数分别为 $\mathrm{I, II, III, IV}$。由于每个点的横纵坐标都不相同，不存在位于轴线上的点。

分情况进行考虑。若选择了 $p$ 点，则矩形一定包含 $p$ 点，方案数 $2 ^ {n - 1}$。对于不选择 $p$ 的方案数，如果同时选择了对角的两个象限，则剩下两个象限可以随便选择。方案数 $\mathrm{2 ^ I 2 ^ {III} (2 ^ {II} - 1)(2 ^ {IV} - 1) + 2 ^ {II} 2 ^ {IV} (2 ^ {III} - 1) (2 ^ {I} - 1)}$。最后发现四个顶点位于四个不同象限的方案重复计算了，因此减去，抠掉的方案数一共是 $\mathrm{(2 ^ I - 1)(2 ^ {II} - 1) (2 ^ {III} - 1) (2 ^ {IV} - 1)}$。

对于四个象限内点的计数，考虑将点按照横坐标排序，从左到右扫描线，二位数点即可计算。时间复杂度 $O(n \log n)$，瓶颈在于树状数组。

代码略微压行。

```cpp
scanf("%lld", &n);
rep(i, 1, n) scanf("%lld%lld", &p[i].x, &p[i].y), p[i].id = i; 
rep(i, 1, n) px.push_back(p[i].x), py.push_back(p[i].y);
sort(px.begin(), px.end()); sort(py.begin(), py.end());
auto find = [&](const vector<int> &p, int x) -> int {
	return lower_bound(p.begin(), p.end(), x) - p.begin() + 1;
}; rep(i, 1, n) p[i].x = find(px, p[i].x), p[i].y = find(py, p[i].y);
sort(p + 1, p + n + 1, [&](node a, node b) { return a.x < b.x; });
auto add = [&](int x) { for (int i = x; i <= n; i += (i & -i)) s[i] ++ ; };
auto Ask = [&](int x) { int ans = 0; for (int i = x; i; i -= (i & -i)) ans += s[i]; return ans; };
auto ask = [&](int l, int r) { return Ask(r) - Ask(l - 1); };
auto clear = [&]() { memset(s, 0, sizeof s); return; };
rep(i, 1, n) III[p[i].id] = ask(1, p[i].y), II[p[i].id] = ask(p[i].y, n), add(p[i].y); clear();
dep(i, n, 1) IV[p[i].id] = ask(1, p[i].y), I[p[i].id] = ask(p[i].y, n), add(p[i].y); clear();
pw[0] = 1; rep(i, 1, n) pw[i] = (pw[i - 1] * 2ll) % mod;
rep(i, 1, n) I[i] = pw[I[i]], II[i] = pw[II[i]], III[i] = pw[III[i]], IV[i] = pw[IV[i]];
rep(i, 1, n) ans = (ans - (I[i] - 1) * (II[i] - 1) % mod * (III[i] - 1) % mod * (IV[i] - 1) % mod) % mod,
			 ans = (ans + (I[i] - 1) * (III[i] - 1) % mod * II[i] % mod * IV[i] % mod) % mod,
			 ans = (ans + (II[i] - 1) * (IV[i] - 1) % mod * I[i] % mod * III[i] % mod) % mod,
			 ans = (ans + pw[n - 1] + mod) % mod;
printf("%lld\n", ans); return 0;
```

---

