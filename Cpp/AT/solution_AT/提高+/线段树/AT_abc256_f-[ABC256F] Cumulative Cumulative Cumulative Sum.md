# [ABC256F] Cumulative Cumulative Cumulative Sum

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc256/tasks/abc256_f

$ N,Q $ および $ A=(A_1,\ldots,A_N) $ が与えられます。  
 以下のクエリを $ Q $ 個処理してください。クエリは次の $ 2 $ 種類のいずれかです。

- `1 x v` : $ A_x $ を $ v $ に更新する。
- `2 x` : $ B_i=\sum_{j=1}^{i}A_j $、$ C_i=\sum_{j=1}^{i}B_j $、$ D_i=\sum_{j=1}^{i}C_j $ としたときの $ D_x $ を $ \bmod\ 998244353 $ で出力する。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\times10^5 $
- $ 1\ \leq\ Q\ \leq\ 2\times10^5 $
- $ 0\ \leq\ A_i\ \leq\ 10^9 $
- $ 1\ \leq\ x\ \leq\ N $
- $ 0\ \leq\ v\ \leq\ 10^9 $
- 入力に含まれる値は全て整数である

### Sample Explanation 1

$ 1 $ 番目のクエリの時点で $ A=(1,2,3) $ であるため、$ B=(1,3,6) $、$ C=(1,4,10) $、$ D=(1,5,15) $ となり、$ D_3=15 $ です。 $ 3 $ 番目のクエリの時点で $ A=(1,0,3) $ であるため、$ B=(1,1,4) $、$ C=(1,2,6) $、$ D=(1,3,9) $ となり、$ D_3=9 $ です。

## 样例 #1

### 输入

```
3 3
1 2 3
2 3
1 2 0
2 3```

### 输出

```
15
9```

## 样例 #2

### 输入

```
2 1
998244353 998244353
2 1```

### 输出

```
0```

# 题解

## 作者：liangbowen (赞：10)

## 前言

[题目传送门！](https://www.luogu.com.cn/problem/AT_abc256_f)

[更好的阅读体验？](https://www.cnblogs.com/liangbowen/p/17392003.html)

trick：将 $D_x$ 用 $A_x$ 来表示。

## 思路

首先 $B_x = \sum\limits_{i=1}^x A_i$。接着算 $C_x$，这个并不困难：

$$
C_x = \sum\limits_{i=1}^xB_i = \sum\limits_{i=1}^x\sum\limits_{j=1}^i A_j
$$

掏一个表格记录它。

![](https://cdn.luogu.com.cn/upload/image_hosting/o5gzjvqo.png)

即 $C_x = \sum\limits_{i=1}^x (x-i+1)A_x$。

类似地，对于 $D_x$，将式子拆开再组合回来，化简：

$$
\begin{aligned}
D_x
& = \sum\limits_{i=1}^x C_i \\
& = \sum\limits_{i=1}^x \sum\limits_{j=1}^x (x-j+1)A_j \\
& = \sum\limits_{i=1}^x\cdot A_1 + \sum\limits_{i=1}^{x-1} A_2 + \sum\limits_{i=1}^{x-2} A_3 + \cdots + A_x \\
& = \dfrac{x(x+1)}2 \cdot A_1 + \dfrac{(x-1)x}2 \cdot A_2 + \dfrac{(x-2)(x-1)}2 \cdot A_3 + \cdots + A_x \\
& = \sum\limits_{i=1}^x A_i \cdot \dfrac{(x-i+1)(x-i+2)}2 \\
& = \sum\limits_{i=1}^x A_i \cdot \dfrac{x^2 - 2xi + i^2 - 3i + 3x + 2}2 \\
& = \sum\limits_{i=1}^x \dfrac{\color{red}(i^2 - 3i) A_i\color{black} - 2x \cdot \color{red}i\cdot A_i \color{black} + (x^2 + 3x + 2) \cdot \color{red} A_i}2 
\end{aligned}
$$

标黑的很容易 $O(1)$ 计算，也就是用数据结构维护红色部分即可（这些部分含有 $i$ 或者 $A_i$）。

维护三个数据结构，分别维护 $\sum (i^2 - 3i) A_i$、$\sum i\cdot A_i$、$\sum A_i$。同时还支持单点更新。

显然用三个树状数组即可拿下。抄一下公式就做完了。

注意 $\dfrac 12$ 用逆元实现，以及取模比较恶心，推荐在可能溢出的地方都无脑 `long long`。

## 代码

自认为打得很好看 qwq。

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int N = 2e5 + 5, mod = 998244353, inv2 = 499122177; //inv2 即：除以2
int n, q, a[N];
struct BIT { //树状数组板子
	int idx[N];
	int lowbit(int x) {return x & -x;}
	void update(int i, int k) {for (; i <= n; i += lowbit(i)) (idx[i] += k) %= mod;}
	int query(int i) {int ans = 0; for (; i; i -= lowbit(i)) (ans += idx[i]) %= mod; return ans;}
} bit0, bit1, bit2;

typedef long long ll;
void upd0(ll i, ll val) {bit0.update(i, ((i * i - 3 * i + mod) % mod) * val % mod);} //(i^2 - 3i) * Ai
void upd1(ll i, ll val) {bit1.update(i, i * val % mod);} //i * Ai
void upd2(ll i, ll val) {bit2.update(i, val);} //Ai
void upds(ll i, ll val) {upd0(i, val), upd1(i, val), upd2(i, val);}
int main()
{
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]), upds(i, a[i]);
	while (q--)
	{
		int op; ll x, val;
		scanf("%d", &op);
		if (op == 1)
			scanf("%lld%lld", &x, &val),
			upds(x, (-a[x] + val + mod) % mod), a[x] = val; //a[x]=val 就是 a[x]+=(-a[x]+val)，还是很显然的吧
		else
			scanf("%lld", &x), //抄公式即可。注意算完可能变成负数，加一下 mod 来保证答案是正数
			printf("%lld\n", (( 
				+ bit0.query(x)
				- (2 * x) % mod * bit1.query(x) % mod
				+ (x * x + 3 * x + 2) % mod * bit2.query(x) % mod
			) + mod) % mod * inv2 % mod);
	}
	return 0;
}
```

希望能帮助到大家！

---

## 作者：0xFF (赞：6)

这个题其实是 [LG4868](https://www.luogu.com.cn/problem/P4868) 的加强版，主要的解决思想有两种，一种是直接推式子推出 $D_i$ 只关于 $A_i$ 的式子然后对于每个部分分别维护，另一种是同时维护这几种前缀和转化求值。

$$B_i=\sum_{j=1}^{i}A_j,C_i=\sum_{j=1}^{i}B_j,D_i=\sum_{j=1}^{i}C_j$$

从 $C_i$ 入手

$$C_i=\sum_{j=1}^{i}B_j=\sum_{j=1}^{i}\sum_{k=1}^{j}A_k$$

交换求和顺序

$$C_i=\sum_{k=1}^{i}\sum_{j=k}^{i}A_k=\sum_{k=1}^{i}A_k\sum_{j=k}^{i}1=\sum_{k=1}^{i}(i-k+1)A_k$$

$$D_i=\sum_{j=1}^{i}C_j=\sum_{j=1}^{i}\sum_{k=1}^{j}(j-k+1)A_k$$

重复上面处理 $C_i$ 的操作，交换求和顺序

$$D_i=\sum_{k=1}^{i}A_k\sum_{j=k}^{i}(j-k+1)=\sum_{k=1}^{i}\dfrac{(i-k+1)(i-k+2)}{2}A_k$$

现在 $D_i$ 就只与 $A_i$ 有关了，直接展开表达式

$D_i=\sum_{k=1}^{i}\dfrac{(i-k+1)(i-k+2)}{2}A_k=\dfrac{1}{2}k^2A_k-\dfrac{3+2i}{2}kA_k+\frac{(i+1)(i+2)}{2}A_k$

用数据结构维护 $k^2A_k,kA_k,A_k$ 的区间和即可。

---

## 作者：wallace_QwQ (赞：3)

怎么题解区都是用线段树的？

这不是带修莫队吗？
******
显然，对于每个询问，左端点固定为 1，每次只需移动右端点和时间。

所以我们的莫队只移动两维，那么复杂度为 $O(n\sqrt n)$，可以通过本题。

具体的，我们分别维护三个数：$now_b$，$now_c$，$now_d$，分别表示当前 $B_r$，$C_r$，$D_r$ 的值。

显然每次答案均为 $now_d$。

#### 考虑如何修改：

移动右端点时，维护以上三个数是容易的。

移动时间时，我们令 $d=p[x].val-a[p[x].pos]$，表示**修改前后两个值相差了多少**，再令 $len=r-p[x].pos+1$，表示**所修改值的位置到右端点的长度**。

1. $now_b\gets now_b+d$
2. $now_c\gets now_c+d\times len$
3. $now_d\gets now_d+d\times \frac{len\times(len+1)}{2}$

#### 几个值得注意的点：
1. 有除法，要预处理出逆元。
2. 不要对负数取模。

代码已经过可读性修改：
```cpp
#include <bits/stdc++.h>
#define for1(i,a,b) for(int (i)=(a); (i)<=(b); ++(i))
#define for2(i,a,b) for(int (i)=(a); (i)>=(b); --(i))
using namespace std;
#define int long long
const int mod = 998244353,inv2 = 499122177;
const int N = 2e5+5;
void madd(auto& x, auto y) {
	x+=y;
	if(x>0) x%=mod;
	else x=(((-x)/mod+1)*mod+x)%mod;
}
int n,m,B,r,t;
int a[N];
struct node{
	int r,t,id;
}q[N]; int cntq;
struct up{
	int pos,val;
}p[N]; int tim;
int b[N];
int ans[N],nowb,nowc,nowd; 
void add(int x){
	madd(nowb,a[x]);
	madd(nowc,nowb);
	madd(nowd,nowc);
}
void del(int x){
	madd(nowd,-nowc);
	madd(nowc,-nowb);
	madd(nowb,-a[x]);
}
void upd(int x){
	if(p[x].pos<=r){
		int d=p[x].val-a[p[x].pos],len=r-p[x].pos+1;
		madd(nowb,d);
		madd(nowc,d*len);
		madd(nowd,d*(((len)*(len+1)%mod)*inv2%mod));
	}
	swap(a[p[x].pos],p[x].val);
}
signed main(){
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin>>n>>m; B=pow(n,0.666);
	for1(i,1,n) cin>>a[i];
	for1(i,1,m){
		int opt;
		cin>>opt;
		if(opt==1){
			tim++;
			cin>>p[tim].pos>>p[tim].val;
		}else{
			cntq++;
			cin>>q[cntq].r;
			q[cntq].id=cntq,q[cntq].t=tim;
		}
	}
	sort(q+1,q+1+cntq,[&](node a,node b){
		return (a.r/B==b.r/B)?(((a.r/B)&1)?a.t<b.t:a.t>b.t):a.r/B<b.r/B;
	});
	for1(i,1,cntq){
		while(r<q[i].r) add(++r);
		while(r>q[i].r) del(r--);
		while(t<q[i].t) upd(++t);
		while(t>q[i].t) upd(t--);
		ans[q[i].id]=nowd;
	}
	for1(i,1,cntq) cout<<ans[i]<<"\n";
    return 0;
}
```

---

## 作者：Shunpower (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc256_f)

## 思路

很明显这种三次前缀和的东西不可能直接维护，我们考虑拆式子，把询问的 $D$ 用 $A$ 表示出来。

$$
\begin{aligned}
D_x&=\sum\limits_{i=1}^{x} C_{i}\\
&=\sum\limits_{i=1}^x\sum\limits_{j=1}^{i}B_j
\end{aligned}
$$

这个时候很容易想到统计每个 $B_i$ 的出现次数，重新表示这个和式。举例子之后容易发现 $B_1$ 会计入 $x$ 次，$B_2$ 会计入 $x-1$ 次，$B_3$ 会计入 $x-2$ 次，以此类推。于是可以继续写下去：

$$
\begin{aligned}
D_x&=\sum\limits_{i=1}^x\sum\limits_{j=1}^{i}B_j\\
&=\sum\limits_{i=1}^x (x-i+1)B_i\\
&=\sum\limits_{i=1}^x (x-i+1)\sum\limits_{j-1}^{i}A_j
\end{aligned}
$$

这个时候我们类似地，继续统计每个 $A_j$ 对答案的贡献。注意这里不再是出现次数，因为带上了系数。下表展现了每个 $A_j$ 在每个 $i$ 的系数：

![](https://cdn.luogu.com.cn/upload/image_hosting/mn7b3zkm.png)

观察每一列，可以发现对于 $A_i$，其总的系数为 $\sum\limits_{j=1}^{x-i+1} j$，这很明显是等差数列求和，$A_i$ 的系数为 $\frac{(x-i+1)(x-i+2)}{2}$。

于是我们得到：

$$
\begin{aligned}
D_x&=\sum\limits_{i=1}^x (x-i+1)\sum\limits_{j-1}^{i}A_j\\
&=\sum\limits_{i=1}^x\frac{(x-i+1)(x-i+2)}{2}A_i
\end{aligned}
$$

在得到这个式子之后可以发现不好直接用 $\log$ 数据结构维护，容易想到考虑根号。发现在有这个式子之后计算一条操作对一条询问的贡献已经可以 $\mathcal O(1)$ 维护了，且重构 $A,D$ 数组可以做到 $\mathcal O(n)$，于是考虑操作分块。

对于每一块，枚举询问（假设询问下标 $i$），先将答案设为 $D_i$，再枚举询问前的每个操作 $(v,x)$ 表示 $A_v\gets x$，很明显对于每个操作只需要在答案中将 $A_v$ 原先对 $D_i$ 的贡献 $\frac{(i-v+1)(i-v+2)}{2}A_v$ 减掉，再给答案加上新的贡献 $\frac{(i-v+1)(i-v+2)}{2}x$ 即可。

注意在枚举操作的过程中仍然需要动态维护 $A$，否则无法正确计算减掉的贡献。又为了保证后面询问的正确性，我们不能直接覆盖 $A$ 所以再开一个数组 $t$ 先对于所有操作 $(v,x)$ 进行 $t_v\gets A_v$，然后动态维护 $t$。

每块结束之后再次枚举所有操作，$\mathcal O(n)$ 重构 $A,D$ 数组保证下一块的正确性。

设块长为 $B$，总复杂度即为 $\mathcal O(\frac{qn}{B}+qB)$，取 $B=\sqrt n$ 即可做到 $\mathcal O(q\sqrt n)$，可以通过。

实现时需要注意 `long long` 等问题。注意到 $(x-i+1),(x-i+2)$ 各自都不用取模并且一奇一偶，所以一定可以被 $2$ 整除，于是可以不使用乘法逆元维护。

## 代码

下面是每一块处理的部分的代码。

```
void solve(int x){
    vector <pll> work;
    fr1(i,las,x){//las是这一块的块头，x是这一块的块尾
        if(p[i].opt==2){//枚举询问
            ll ans=d[p[i].x]%M;//获得初始答案，注意也要取模
            work.clear();
            fr1(j,las,i-1){
                if(p[j].opt==1&&p[j].v<=p[i].x){
                    work.pb(mp(p[j].v,p[j].x));
                    pre[p[j].v]=a[p[j].v];//枚举前面的操作，并且初始化代替A被动态维护的数组
                }
            }
            for(auto j:work){
                ans=ans-1ll*(p[i].x-j.fi+1)*(p[i].x-j.fi+2)/2%M*pre[j.fi]%M;//计算减少的贡献
                ans=ans+1ll*(p[i].x-j.fi+1)*(p[i].x-j.fi+2)/2%M*j.se%M;//计算增加的贡献
                ans=(ans+M)%M;
                pre[j.fi]=j.se;//动态维护
            }
            cout<<ans<<'\n';
        }
    }
    fr1(i,las,x){
        if(p[i].opt==1){
            a[p[i].v]=p[i].x;
        }
    }
    fr1(i,1,n){
        d[i]=a[i];
    }
    fr1(i,1,3){
        fr1(j,1,n){
            d[j]=d[j-1]+d[j];
            d[j]%=M;
        }
    }//这一部分重构了A和D数组，保证下一块使用的数组是维护好的
}
```

[AC 记录](https://www.luogu.com.cn/record/125427124)

---

## 作者：under_the_time (赞：1)

> 给定一个长度为 $n$ 的序列 $a$，$Q$ 次操作：
>
> - 给定 $x,v$，令 $a_x\gets v$；
> - 令 $b_i=\sum_{j=1}^ia_j$，$c_i=\sum^i_{j=1}b_j$，求 $\sum_{i=1}^xc_i$。
>
> $1\le n,Q\le 2\times 10^5$，$0\le a_i,v\le 10^9$，对 $998244353$ 取模。

首先令 $v'=v-a_x$，那么 $a_x\gets v$ 相当于 $a_x\gets a_x+v'$，把单点改变成单点加。假设现在令 $a_x\gets a_x+v$，可以发现在 $b$ 中把 $[x,n]$ 区间加 $v$，在 $c$ 中把 $[x,n]$ 区间加了一个首项、公差均为 $v$ 的等差数列。我们考虑用线段树维护 $c$ 数组，做区间加等差数列、区间求和即可。

怎么维护区间加等差数列？对于线段树节点 $i$，维护首项 $st_i$、公差 $k_i$ 两个懒标记，假设现在在 $i$ 上加了一个首项为 $x$、公差为 $y$ 的等差数列，直接令 $st_i\gets st_i+x$、$k_i\gets k_i+y$ 即可合并懒标记。下传懒标记给右儿子时注意首项会改变，同样在修改时每个区间加到的等差数列首项也是不同的。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define mk make_pair
#define open(x) freopen(#x".in", "r", stdin), freopen(#x".out", "w", stdout)
#define abs(x) (((x) > (0)) ? (x) : (-(x)))
#define lowbit(x) ((x) & (-(x)))
#define lson l, mid, rt << 1
#define rson mid + 1, r, rt << 1 | 1
#define BCNT __builtin_popcount
#define cost_time (1e3 * clock() / CLOCKS_PER_SEC)
const int inf = 0x3f3f3f3f; 
mt19937 rnd(time(0));
const int maxn = 2e5 + 5, P = 998244353;
int n, Q, a[maxn], b[maxn], c[maxn];
namespace ModOptions_normal {
    int add(int x, int y) { return (x + y) % P; } 
    void addto(int &x, int y) { (x += y) %= P; }
    int mul(int x, int y) { return 1ll * x * y % P; } 
    void multo(int &x, int y) { x = mul(x, y); }
    int qp(int x, int y) {
        int res = 1; for (; y; y >>= 1, multo(x, x))
            if (y & 1) multo(res, x);
        return res;
    } int divv(int x, int y) { return 1ll * x * qp(y, P - 2) % P; } 
    void divto(int &x, int y) { x = divv(x, y); } 
    int sub(int x, int y) { return (x + P - y) % P; } 
    void subto(int &x, int y) { x = sub(x, y); }
} using namespace ModOptions_normal;
int sum[maxn << 2], col_st[maxn << 2], col_k[maxn << 2];
void update(int rt) { sum[rt] = add(sum[rt << 1], sum[rt << 1 | 1]); }
void build(int l, int r, int rt) {
    if (l == r) return sum[rt] = c[l], void(0);
    int mid = (l + r) >> 1;
    build(lson), build(rson), update(rt);
} void color(int l, int r, int rt, int st, int k) {
    int len = r - l; 
    addto(sum[rt], divv(mul(add(st, add(st, mul(len, k))), len + 1), 2));
    addto(col_st[rt], st), addto(col_k[rt], k);
} void pushcol(int l, int r, int rt) {
    if (col_st[rt] == 0 && col_k[rt] == 0) return;
    int mid = (l + r) >> 1;
    color(lson, col_st[rt], col_k[rt]); 
    color(rson, add(col_st[rt], mul(mid - l + 1, col_k[rt])), col_k[rt]); // 右儿子下传时要更改首项
    col_st[rt] = col_k[rt] = 0;
} int query(int l, int r, int rt, int nowl, int nowr) {
    if (nowl <= l && r <= nowr) return sum[rt];
    int mid = (l + r) >> 1, res = 0; pushcol(l, r, rt);
    if (nowl <= mid) addto(res, query(lson, nowl, nowr));
    if (mid < nowr) addto(res, query(rson, nowl, nowr));
    return res;
} void modify(int l, int r, int rt, int nowl, int nowr, int k) {
    if (nowl <= l && r <= nowr) return color(l, r, rt, mul(k, l - nowl + 1), k);
    int mid = (l + r) >> 1; pushcol(l, r, rt);
    if (nowl <= mid) modify(lson, nowl, nowr, k);
    if (mid < nowr) modify(rson, nowl, nowr, k);
    update(rt);
}
int main() {
    scanf("%d %d", &n, &Q);
    for (int i = 1; i <= n; i ++) scanf("%d", &a[i]), a[i] %= P;
    for (int i = 1; i <= n; i ++) b[i] = add(b[i - 1], a[i]);
    for (int i = 1; i <= n; i ++) c[i] = add(c[i - 1], b[i]);
    build(1, n, 1); 
    for (int i = 1, op, x, v; i <= Q; i ++) {
        scanf("%d", &op);
        if (op == 1) {
            scanf("%d %d", &x, &v), v %= P; 
            int tmp = sub(v, a[x]); a[x] = v;
            modify(1, n, 1, x, n, tmp);
        } else scanf("%d", &x), printf("%d\n", query(1, n, 1, 1, x));
    }
    return 0;
}
```

---

## 作者：Super_Cube (赞：1)

# Solution

$$
B_i=\sum_{j=1}^iA_j
\\
C_i=\sum_{j=1}^iB_j=\sum_{j=1}^i\sum_{k=1}^jA_k=\sum_{j=1}^i(i-j+1)A_j
\\
D_i=\sum_{j=1}^iC_j=\sum_{j=1}^i\sum_{k=1}^j(j-k+1)A_k=\sum_{j=1}^i\frac{(i-j+1)(i-j+2)}{2}A_j
\\
D_i=\frac{1}{2}\sum_{j=1}^ij^2a_j-\frac{2i+3}{2}\sum_{j=1}^ija_j+\frac{(i+1)(i+2)}{2}\sum_{j=1}^ia_j
$$

树状数组维护 $\displaystyle\sum_{j=1}^ij^2a_j,\sum_{j=1}^ija_j,\sum_{j=1}^ia_j$。

时间复杂度：$O((n+q)\log n)$。

注意取模。

---

## 作者：linxuanrui (赞：1)

### 前言

膜拜 @[liangbob](/user/430133) 大佬！

感谢他帮我调出了这题！

### 思路

直接暴力求的话，明显是不可做的。

考虑从从简单的开始算起。

对于求 B 数组（一重前缀和），就是简单的树状数组模板。

对于求 C 数组，可以考虑每一个 $A_i$ 对答案的贡献，由此对公式化简：

$$
\begin{aligned}
C_x&=\sum\limits_{i=1}^xB_i\\
&=\sum\limits_{i=1}^x\sum\limits_{j=1}^iA_j\\
&=\sum\limits_{i=1}^xA_i\times(x-i+1)\\
&=(x+1)\times\color{red}\sum\limits_{i=1}^xA_i\color{black}-\color{red}\sum\limits_{i=1}^xA_i\times i
\end{aligned}
$$

用两个树状数组维护 $A_i$ 和 $A_i\times i$ 即可。

有了求 C 数组的经验，求 D 数组不算是太难了吧。（然而卡了我好久……）

还是考虑每个数 $A_i$ 对答案的贡献。

$$
\begin{aligned}
D_x&=\sum\limits_{i=1}^xC_i\\
&=\sum\limits_{i=1}^x\sum\limits_{j=1}^xA_j\times(x-j+1)\\
&=\sum\limits_{i=1}^xA_i\times\sum\limits_{j=i}^x(x-j+1)\\
&=\sum\limits_{i=1}^xA_i\times\frac{(x-i+1)\times(x-i+2)}{2}\\
&=\sum\limits_{i=1}^xA_i\times\frac{x^2+3x-2ix-i^2+2-3i}{2}\\
&=\sum\limits_{i=1}^x\frac{(x^2+3x+2)\color{red}A_i\color{black}-2x\times(\color{red}i\times A_i\color{black})-\color{red}(i^2+3i)\times A_i}{2}
\end{aligned}
$$

这时用三个树状数组维护 $A_i$，$i\times A_i$ 和 $(i^2+3i)\times A_i$ 即可。

### 代码

在给出代码之前，给出几个小建议：

1. 本题需要注意取模。

2. 如果你不想太麻烦的话，得用 `long long`。

3. 操作一是**修改**为 $v$，并不是加上 $v$。

4. 除以 $2$ 在模 $998244353$ 下是乘上 $2$ 的逆元 $499122177$。

5. 最后统计时可能会是负数，因此要加上 $998244353$ 后再取模。

```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define int long long
using namespace std;
const int N = 2e5 + 5,mod = 998244353;
int n,q,a[N],opt,x,v;
int lowbit(int x){return x & (-x);}
struct node{
	int tree[N];
	node(){memset(tree,0,sizeof(tree));} 
	void update(int pos,int x){for(int i = pos;i <= n;i += lowbit(i))tree[i] += x,tree[i] %= mod;}
	int sum(int pos){int ans = 0;for(int i = pos;i >= 1;i -= lowbit(i))ans = (ans + tree[i]) % mod;return ans % mod;}
}tree1,tree2,tree3;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> q;
	for(int i = 1;i <= n;i++)cin >> a[i],a[i] %= mod,tree1.update(i,a[i] * (i * i % mod - 3 * i) % mod),tree2.update(i,a[i] * i % mod),tree3.update(i,a[i]);
	while(q--){
		cin >> opt >> x;
		if(opt == 1){
			cin >> v;
			int add = (v - a[x]) % mod;
			tree1.update(x,add * (x * x % mod - 3 * x) % mod);
			tree2.update(x,add * x % mod);
			tree3.update(x,add);
			a[x] = v % mod;
		}else cout << ((tree3.sum(x) * (x * x % mod + 3 * x + 2) % mod - 2 * x % mod * tree2.sum(x) % mod + tree1.sum(x)) % mod + mod) % mod * 499122177ll % mod << endl; 
	}
}
```

---

## 作者：liangbob (赞：1)

### AT_abc256_f 题解

#### 思路分析

推式子加数据结构题。

先来推 $C_i$。

$$\begin{aligned}C_i & = A_1+(A_1+A_2)+(A_1+A_2+A_3)+\ldots+(A_1+A_2+A_3+\ldots+A_i) \\ & =iA_1+(i-1)A_2+\ldots+A_i \\ & = (i-1+1)A_1+(i-2+1)A_2+\ldots+(i-k+1)A_k+\ldots+(i-i+1)A_i \end{aligned}$$

然后 $C_i$ 推出来了就去推 $D_i$。

这里我们为了方便统计就只考虑 $A_k$ 的系数：

- 在 $C_k$ 中，为 $(k-k+1)A_k = 1A_k$（根据上面推出来的式子）
- 在 $C_{k+1}$ 中，为 $(k+1-k+1)A_k=2A_k$。
- 在 $C_{k+2}$ 中，为 $(k + 2-k+1)A_k = 3A_k$。
- 在 $C_{l}$ 中（$k\le l \le i$），为 $(l-k+1)A_k$。
- 在 $C_{i}$ 中，为 $(i-k+1)A_k$。

然后发现对于 $A_k$，它的系数为 $1+2+3+\ldots+(i-k+1)$，也就是 $\dfrac{(i-k+2)(i-k+1)}{2}$。

于是我们有：

$$D_i = \dfrac{(i-1+2)(i-1+1)}{2}A_1 + \dfrac{(i-2+2)(i-2+1)}{2}A_2 + \ldots + \dfrac{(i-k+2)(i-k+1)}{2}A_k +\ldots+ \dfrac{(i-i+2)(i-i+1)}{2}A_i$$

然后拆开来看看，把 $A_k$ 乘上去：

$D_i=\dfrac{(1^2-3\times1)A_1-2i\cdot 1 \cdot A_1+(i^2+3i+2)A_1}{2}+\ldots+\dfrac{(k^2-3k)A_k-2i\cdot k \cdot A_k+(i^2+3i+2)A_k}{2}+\ldots+\dfrac{(i^2-3i)A_i-2i\cdot i \cdot A_i+(i^2+3i+2)A_i}{2}$


把如下含 $k$ 的使用树状数组维护之：

- $(k^2-3k)A_k$

- $k \cdot A_k$

- $A_k$

无脑更新，无脑查询，无脑取模！

然后做完！


#### 代码

```cpp
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstring>
#define lowbit(x) x&(-x)
#define endl '\n'
#define int long long
using namespace std;
const int N = 3e5 + 10;
const int mod = 998244353;
const int half = 499122177; //二分之一的逆元 

template <typename T>
class FkTree //树状数组模板 
{
	public:
		FkTree(int _n = 0)
		{
			n = _n;
			memset(c, 0x0, sizeof(c));
		}
		T query(int x)
		{
			T sum = 0;
			while(x > 0)
			{
				sum = _add(sum, c[x]);
				x -= lowbit(x);
			}
			return sum % mod; //一定要取模！我在此处调了1.5h，警钟敲烂
		}
		
		void update(int x, T p)
		{
			while(x <= n)
			{
				c[x] = _add(c[x], p);
				x += lowbit(x);
			}
		}
	private:
		T c[N];
		T n;
		T _add(T a, T b)
		{
			return (a + b) % mod;
		}
};

//三个树状数组 
FkTree <int> x(N);
FkTree <int> y(N);
FkTree <int> z(N); 
int e[N]; //原数组

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
	int n, q;
	cin >> n >> q;
	for(int i = 1;i <= n;i++)
	{
		int t;
		cin >> t;
		e[i] = t;
		//三个用树状数组维护的值 
		x.update(i, ((i % mod * i % mod - 3 * i % mod + mod) % mod) * t % mod);
		y.update(i, i % mod * t % mod);
		z.update(i, t % mod);
	}
	for(int i = 1;i <= q;i++)
	{
		int op;
		cin >> op;
		if(op == 1)
		{
			int a, w;
			cin >> a >> w;
			//无脑更新，注意update是加法
			//因此我们就要求一下要加多少 
			int b = (w - e[a] + mod) % mod;
			x.update(a, ((a % mod * a % mod - 3 * a % mod + mod) % mod) * b % mod);
			y.update(a, (a % mod * b % mod) % mod);
			z.update(a, b % mod);
			e[a] = w; //更新原来的
		}
		else
		{
			int g;
			cin >> g;
            //无脑查询，并根据式子计算
			cout << half * (((x.query(g) % mod - (((2 * g) % mod) * (y.query(g) % mod)) % mod + mod) % mod + ((g % mod * g % mod + 3 * g % mod + 2) % mod) % mod * z.query(g) % mod) % mod) % mod << endl;
		}
	}
    return 0;
}
```


---

## 作者：OldDriverTree (赞：1)

# Solution
先推一波式子。

$$
\begin{aligned}
D_x&=\sum_{i=1}^x C_i\\
&=\sum_{i=1}^x\sum_{j=1}^x B_j\\
&=\sum_{i=1}^x\sum_{j=1}^i\sum_{k=1}^jA_k\\
&=\sum_{k=1}^x\sum_{j=k}^x\sum_{i=j}^x A_k\text{（调换求和符号顺序）}\\
&=\sum_{k=1}^x\sum_{j=k}^x(x-j+1) A_k\\
&=\sum_{k=1}^x\dfrac{(x-k+2)(x-k+1)}2A_k\text{(等差数列求和)}\\
&=\dfrac12\sum_{k=1}^x ((x^2+3x+2)-(2x+3)k+k^2)A_k\text{(拆括号)}
\end{aligned}
$$

分别对 $A_k$ 的和，$kA_k$ 的和，$k^2A_k$ 的和各开一个树状数组维护即可。

时间复杂度 $O((n+q)\log n)$。

# Code
```c++
#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;
const int N=2e5+1;
int n,m,a[N];

int read() {
	int x=0; char c=0; while (!isdigit(c) ) c=getchar();
	while (isdigit(c) ) x=(x<<3)+(x<<1)+(c&15),c=getchar();
	return x;
}
struct BIT {
	int T[N]; void update(int x,int y) { while (x<=n) T[x]=(T[x]+y)%mod,x+=x&-x; }
	int query(int x,int sum=0) { while (x) sum=(sum+T[x])%mod,x-=x&-x; return sum; }
}T1,T2,T3;

int main()
{
	n=read(),m=read(); for (int i=1;i<=n;i++) a[i]=read()%mod,
	T1.update(i,a[i]),T2.update(i,1ll*i*a[i]%mod),T3.update(i,1ll*i*i%mod*a[i]%mod);
	while (m--) {
		int op=read(),x=read(),y,t;
		if (op&1) {
			y=read()%mod,t=(y-a[x]+mod)%mod,a[x]=y;
			T1.update(x,t),T2.update(x,1ll*x*t%mod);
			T3.update(x,1ll*x*x%mod*t%mod);
		}
		else {
			int ans=1ll*(1ll*x*x%mod+3*x+2)%mod*T1.query(x)%mod;
			ans=(ans-1ll*(2*x+3)%mod*T2.query(x)%mod+mod)%mod;
			ans=(ans+T3.query(x) )%mod,printf("%d\n",1ll*(mod+1)/2*ans%mod);
		}
	}
	return 0;
}
```

---

## 作者：Tang_poetry_syndrome (赞：1)

## [ABC256F] Cumulative Cumulative Cumulative Sum

[洛谷题面](https://www.luogu.com.cn/problem/AT_abc256_f) [Atcoder 题面](https://atcoder.jp/contests/abc256/tasks/abc256_f)

### 题目大意

给定一个长度为 $N$ 的序列 $A$，设 $B_i=\sum\limits_{j=1}^iA_j,C_i=\sum\limits_{j=1}^iB_j,D_i=\sum\limits_{j=1}^iC_j$，进行 $Q$ 次操作，所有操作为以下两种之一： 

1. `1 x v`：将 $A_x$ 改为 $v$  

2. `2 x`：求 $D_x \bmod 998244353$

### 思路

先来拆柿子：  
$\because B_i=\sum\limits_{j=1}^iA_j \And C_i=\sum\limits_{j=1}^iB_j$  
$\therefore C_i=\sum\limits_{j=1}^i\sum\limits_{k=1}^jA_k=\sum\limits_{j=1}^i(i-k+1)A_j$
且 $D_i=\sum\limits_{j=1}^iC_j$  
即 $D_i=\sum\limits_{j=1}^i\sum\limits_{k=1}^j\sum\limits_{l=1}^kA_l=\sum\limits_{j=1}^iA_j\times\sum\limits_{k=j}^i(k-j+1)=\sum\limits_{j=1}^i\dfrac{(i-j+1)\times(i-j+2)}{2}A_j=\dfrac{1}{2}j^2A_j-\dfrac{3+2 \times i}{2}jA_j+\dfrac{(i+1)\times(i+2)}{2}A_j$  
考虑用三个树状数组维护 $j^2A_j,jA_j,A_j$，更新 $A_x$ 时，树状数组减原来的 $A_x$ 再加现在的 $A_x$ 即可，详见代码。

### 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=2e5+5,MOD=998244353,inv2=499122177;
int t[3][maxn];
int a[maxn];
int n,q;
int lowbit(int x){return x&(-x);}
void add(int x,int k,int p){	for(;x<=n;x+=lowbit(x))t[p][x]=(t[p][x]+k);}
int query(int x,int p)
{
	int res=0;
	for(;x;x-=lowbit(x))
		res=(res+t[p][x])%MOD;
	return res;
}
signed main()
{
	scanf("%lld%lld",&n,&q);
	for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	for(int i=1;i<=n;i++)
		add(i,a[i]*i%MOD*i%MOD,2),add(i,a[i]*i%MOD,1),add(i,a[i],0);
	for(int i=1;i<=q;i++)
	{
		int op,x,y;
		scanf("%lld%lld",&op,&x);
		if(op==1)
		{
			scanf("%lld",&y);
			add(x,-a[x]*x%MOD*x%MOD,2);
			add(x,-a[x]*x%MOD,1);
			add(x,-a[x],0);
			a[x]=y;
			add(x,a[x]*x%MOD*x%MOD,2);
			add(x,a[x]*x%MOD,1);
			add(x,a[x],0);
		}
		else
			printf("%lld\n",(query(x,0)*((x*x%MOD+3*x%MOD+2)%MOD)%MOD-query(x,1)*((2*x%MOD+3)%MOD)%MOD+query(x,2)+MOD)%MOD*inv2%MOD);
	}
	return 0;
}
```

---

## 作者：Union_Find (赞：0)

有点唐的数据结构题。本题解提供两种做法。

在看题解前，请确保你会 [P3372 线段树1](https://www.luogu.com.cn/problem/P3372) 的树状数组做法。

## 树状数组

看到这道题，会想到 [P3372 线段树1](https://www.luogu.com.cn/problem/P3372) 的树状数组做法。考虑拆式子维护。

首先，容易发现的是，$C_i = \sum_{j=1}^i (i-j+1)a_j$。这一点比较明显。接下来考虑拆式子。

$$D_x = \sum_{i=1}^x C_i$$
$$=\sum_{i=1}^x \sum_{j=1}^i (i-j+1)a_j$$
$$=\sum_{i=1}^x\frac{(x-i+1)(x-i+2)}{2}a_i$$
$$=\sum_{i=1}^x\frac{(x-i)^2+3(x-i)+2}{2}a_i$$
$$=\sum_{i=1}^x\frac{x^2-2xi+i^2+3x-3i+2}{2}a_i$$
$$=\sum_{i=1}^x\frac{(i^2-3i)a_i-2x(i\times a_i)+(x^2+3x+2)a_i}{2}$$
$$=\sum_{i=1}^x\frac{(i^2-3i)a_i}{2}-x\sum_{i-=1}^xia_i+\frac{(x^2+3x+2)}{2}\sum_{i=1}^xa_i$$

这些式子是正常的化简。值得注意的是，第三行的转化仍然需要再拆一次贡献。

接下来注意到 $\frac{(i^2-3i)a_i}{2},ia_i,a_i$ 这三项不能 $O(1)$ 直接计算，所以考虑用数据结构维护。因为是单点修改，区间查询，考虑使用树状数组。直接维护即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define il inline
#define N 200005
#define c1(i, a) (((i * i % P - 3 * i % P) % P + P) % P * a % P)
#define c2(i, a) (i * a % P)
#define c3(i, a) (a)
il ll rd(){
	ll s = 0, w = 1;
	char ch = getchar();
	for (;ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') w = -1;
	for (;ch >= '0' && ch <= '9'; ch = getchar()) s = ((s << 1) + (s << 3) + ch - '0');
	return s * w;
}const ll P = 998244353, inv2 = 499122177;
ll n, T, a[N], op, x, v;
il void pl(ll &x, ll y){x = ((x + y) % P + P) % P;}
struct BT{
	ll tr[N];
	il void add(ll x, ll k){for (int i = x; i <= n; i += (i & (-i))) pl(tr[i], k);}
	il ll ask(ll x){ll ans = 0;for (int i = x; i >= 1; i -= (i & (-i))) pl(ans, tr[i]);return ans;}
}t1, t2, t3;
il void add(ll x, ll k){t1.add(x, c1(x, k)), t2.add(x, c2(x, k)), t3.add(x, c3(x, k));}
int main(){
	n = rd(), T = rd();
	for (int i = 1; i <= n; i++) a[i] = rd(), add(i, a[i]);
	for (; T--;){
		op = rd(), x = rd();
		if (op & 1) v = rd(), add(x, (v - a[x] + P) % P), a[x] = v;
		else{
			ll p1 = t1.ask(x), p2 = t2.ask(x), p3 = t3.ask(x);
			ll ans = p1 * inv2 % P - x * p2 % P + (x * x % P + 3 * x % P + 2) % P * inv2 % P * p3 % P;
			printf ("%lld\n", (ans % P + P) % P);
		}
	}
	return 0;
}

```

## 线段树

线段树就比较简单了。我们注意到，$B_i$ 就是 $A$ 的前缀和。所以 $A_i$ 的单点修改在 $B_i$ 上就是区间修改。而我们知道，$D_x = \sum_{i=1}^x C_i = \sum_{i=1}^x \sum_{j=1}^i B_j = \sum_{i=1}^x (x-i+1)B_i = (x+1)\sum_{i=1}^x B_i - \sum_{i=1}^xiB_i$，直接用线段树维护 $B_i,iB_i$ 的区间和即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define il inline
#define N 200005
#define calc(l, r) (r - l + 1) * (l + r) % P * inv2 % P
il ll rd(){
	ll s = 0, w = 1;
	char ch = getchar();
	for (;ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') w = -1;
	for (;ch >= '0' && ch <= '9'; ch = getchar()) s = ((s << 1) + (s << 3) + ch - '0');
	return s * w;
}const ll P = 998244353, inv2 = 499122177;
ll n, T, a[N], s[N], tag[N << 2], op, x, v;
struct ST{
	ll a, b;
}tr[N << 2];
ST operator + (const ST &a, const ST &b){return ST{(a.a + b.a) % P, (a.b + b.b) % P};}
il void pl(ll &x, ll y){x = ((x + y) % P + P) % P;}
il void init(ll p, ll k, ll l, ll r){pl(tr[p].a, (r - l + 1) * k % P), pl(tr[p].b, calc(l, r) * k % P), pl(tag[p], k);}
il void pd(ll p, ll l, ll r, ll mid){init(p << 1, tag[p], l, mid), init(p << 1 | 1, tag[p], mid + 1, r), tag[p] = 0;}
void build(ll p, ll l, ll r){
	if (l == r) return tr[p] = ST{s[l], l * s[l] % P}, void(0);
	ll mid = (l + r) >> 1;
	build(p << 1, l, mid), build(p << 1 | 1, mid + 1, r);
	tr[p] = tr[p << 1] + tr[p << 1 | 1];
}void add(ll p, ll l, ll r, ll nl, ll nr, ll k){
	if (nl <= l && r <= nr) return init(p, k, l, r), void(0);
	ll mid = (l + r) >> 1;pd(p, l, r, mid);
	if (nl <= mid) add(p << 1, l, mid, nl, nr, k);
	if (nr > mid) add(p << 1 | 1, mid + 1, r, nl, nr, k);
	tr[p] = tr[p << 1] + tr[p << 1 | 1];
}ST ask(ll p, ll l, ll r, ll nl, ll nr){
	if (nl <= l && r <= nr) return tr[p];
	ll mid = (l + r) >> 1;pd(p, l, r, mid);
	if (nl <= mid && nr > mid) return ask(p << 1, l, mid, nl, nr) + ask(p << 1 | 1, mid + 1, r, nl, nr);
	if (nl <= mid) return ask(p << 1, l, mid, nl, nr);
	if (nr > mid) return ask(p << 1 | 1, mid + 1, r, nl, nr);
}
int main(){
	n = rd(), T = rd();
	for (int i = 1; i <= n; i++) a[i] = rd(), s[i] = (s[i - 1] + a[i]) % P;
	build(1, 1, n);
	for (; T--;){
		op = rd(), x = rd();
		if (op & 1) v = rd(), add(1, 1, n, x, n, v - a[x]), a[x] = v;
		else{
			ST ans = ask(1, 1, n, 1, x);
//			cout << ans.a << " " << ans.b << "\n";
			printf ("%lld\n", ((ans.a * (x + 1) % P - ans.b) % P + P) % P);
		}
	}
	return 0;
}

```

---

## 作者：Tsawke (赞：0)

# [[ABC256F] Cumulative Cumulative Cumulative Sum](https://www.luogu.com.cn/problem/AT_abc256_f) Solution

[TOC]

## [更好的阅读体验戳此进入](http://blog.tsawke.com?t=ABC256F)

## 题面

给定序列 $ A_n $，定义 $ B_i = \sum_{j = 1}^j A_j, C_i = \sum_{j = 1}^i B_j, D_i = \sum_{j = 1}^i C_j $。存在两种操作：

`1 x v`：$ A_x \leftarrow v $。

`2 x`：查询 $ D_x \bmod{998244353} $。

## Solution

就是维护一个高维前缀和，也是经典套路，无脑推式子：

| $ \textbf{A} $ | $ a_1 $ |    $ a_2 $     |        $ a_3 $        | $ \cdots $ |                           $ a_i $                            |
| :------------: | :-----: | :------------: | :-------------------: | :--------: | :----------------------------------------------------------: |
| $ \textbf{B} $ | $ a_1 $ | $ a_1 + a_2 $  |  $ a_1 + a_2 + a_3 $  | $ \cdots $ |                 $ a_1 + a_2 + \cdots + a_i $                 |
| $ \textbf{C} $ | $ a_1 $ | $ 2a_1 + a_2 $ | $ 3a_1 + 2a_2 + a_3 $ | $ \cdots $ |             $ ia_1 + (i - 1)a_2 + \cdots + a_i $             |
| $ \textbf{D} $ | $ a_1 $ | $ 3a_1 + a_2 $ | $ 6a_1 + 3a_2 + a_3 $ | $ \cdots $ | $ (1 + 2 + \cdots + i)a_1 + (1 + 2 + \cdots + (i - 1))a_2 + \cdots + a_i $ |

于是可以将 $ D_x $ 通过等差数列求和表示为：
$$
D_x= \sum_{i = 1}^x \dfrac{1}{2}(1 + x - (i - 1)) \times (x - (i - 1))a_i
$$
然后我们可以考虑将 $ (1 + x - (i - 1)) \times (x - (i - 1))a_i $ 化简，似乎就是尽量将与询问有关的 $ x $ 和前缀和抽离开，这样才可以便于用数据结构维护。即：
$$
\begin{aligned}
	& (1 + x - (i - 1)) \times (x - (i - 1))a_i \\
	=& (x - i + 2) \times (x - i + 1)a_i \\
	=& (x^2 -ix +2x - ix + i^2 -2i + x - i + 2)a_i \\
	=& (x^2 -2ix + 3x + i^2 - 3i + 2)a_i \\
	=& (x^2 + 3x + 2)a_i - 2x(ia_i) + (i^2 - 3i)a_i
\end{aligned}
$$
此时我们发现，对于每次询问 $ x $ 已知，只需要用数据结构维护 $ a_i $，$ ia_i $，$ (i^2 - 3i)a_i $ 的前缀和即可 $ O(\log n) $ 查询，并且支持单点修改。记得查询之后乘个 $ 2 $ 的逆元。最终复杂度 $ O((n + q) \log n) $，可以通过。

## Code

```cpp
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

#define PI M_PI
#define E M_E
#define npt nullptr
#define SON i->to
#define OPNEW void* operator new(size_t)
#define ROPNEW(arr) void* Edge::operator new(size_t){static Edge* P = arr; return P++;}

using namespace std;

mt19937 rnd(random_device{}());
int rndd(int l, int r){return rnd() % (r - l + 1) + l;}
bool rnddd(int x){return rndd(1, 100) <= x;}

typedef unsigned int uint;
typedef unsigned long long unll;
typedef long long ll;
typedef long double ld;

#define MOD (998244353ll)

template < typename T = int >
inline T read(void);

int N, Q;
ll A[210000];

ll qpow(ll a, ll b){
    ll ret(1), mul(a);
    while(b){
        if(b & 1)ret = ret * mul % MOD;
        b >>= 1;
        mul = mul * mul % MOD;
    }return ret;
}

class BIT{
private:
    ll tr[210000];
public:
    int lowbit(int x){return x & -x;}
    void Modify(int x, ll v){while(x <= N)(tr[x] += v + MOD) %= MOD, x += lowbit(x);}
    ll Query(int x){ll ret(0); while(x)(ret += tr[x]) %= MOD, x -= lowbit(x); return ret;}
}bit1, bit2, bit3;

int main(){
    const ll inv2 = qpow(2, MOD - 2);
    N = read(), Q = read();
    for(int i = 1; i <= N; ++i)
        A[i] = read(),
        bit1.Modify(i, A[i]),
        bit2.Modify(i, i * A[i] % MOD),
        bit3.Modify(i, ((ll)i * i % MOD - 3ll * i % MOD + MOD) % MOD * A[i] % MOD);
    while(Q--){
        int opt = read();
        if(opt == 1){
            int x = read(); ll v = read();
            bit1.Modify(x, (v - A[x] + MOD) % MOD),
            bit2.Modify(x, x * ((v - A[x] + MOD) % MOD) % MOD),
            bit3.Modify(x, ((ll)x * x % MOD - 3ll * x % MOD + MOD) % MOD * ((v - A[x] + MOD) % MOD) % MOD);
            A[x] = v;
        }else{
            ll x = read();
            ll ret = (x * x % MOD + 3ll * x % MOD + 2) % MOD * bit1.Query(x) % MOD;
            (ret += (-2ll * x + MOD) % MOD * bit2.Query(x) % MOD) %= MOD;
            (ret += bit3.Query(x)) %= MOD;
            printf("%lld\n", ret * inv2 % MOD);
        }
    }
    fprintf(stderr, "Time: %.6lf\n", (double)clock() / CLOCKS_PER_SEC);
    return 0;
}

template < typename T >
inline T read(void){
    T ret(0);
    int flag(1);
    char c = getchar();
    while(c != '-' && !isdigit(c))c = getchar();
    if(c == '-')flag = -1, c = getchar();
    while(isdigit(c)){
        ret *= 10;
        ret += int(c - '0');
        c = getchar();
    }
    ret *= flag;
    return ret;
}
```

## UPD

update-2022_12_08 初稿

---

