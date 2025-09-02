# [ABC353G] Merchant Takahashi

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc353/tasks/abc353_g

AtCoder 王国には町 $ 1, $ 町 $ 2,\ldots, $ 町 $ N $ の $ N $ 個の町があります。 町 $ i $ から町 $ j $ まで移動するには通行料が $ C\times|i-j| $ 円かかります。

商人である高橋君は、これから開催される $ M $ 回の市場のうち $ 0 $ 回以上に参加しようと思っています。

$ i $ 回目 $ (1\leq\ i\leq\ M) $ の市場の情報は整数の組 $ (T\ _\ i,P\ _\ i) $ で表され、$ i $ 回目の市場が町 $ T\ _\ i $ で行われ、高橋君が参加すると $ P\ _\ i $ 円が得られることを意味します。

すべての $ 1\leq\ i\lt\ M $ について、$ i $ 回目の市場が終了してから $ i+1 $ 回目の市場が開始します。 高橋君が移動するのにかかる時間は無視できるものとします。

高橋君は、はじめ $ 10\ ^\ {10\ ^\ {100}} $ 円持っており、町 $ 1 $ にいます。 参加する市場をうまく選び、うまく移動することによって高橋君が得られる儲けの最大値を求めてください。

厳密には、$ M $ 回の市場が終わったあとの所持金を最大化するように高橋君が行動した場合の最終的な高橋君の所持金を $ 10\ ^\ {10\ ^\ {100}}+X $ として、$ X $ を求めてください。

## 说明/提示

### 制約

- $ 1\leq\ N\leq2\times10\ ^\ 5 $
- $ 1\leq\ C\leq10\ ^\ 9 $
- $ 1\leq\ M\leq2\times10\ ^\ 5 $
- $ 1\leq\ T\ _\ i\leq\ N\ (1\leq\ i\leq\ M) $
- $ 1\leq\ P\ _\ i\leq10\ ^\ {13}\ (1\leq\ i\leq\ M) $
- 入力はすべて整数
 
### Sample Explanation 1

たとえば、高橋君が次のように行動することで、所持金を $ 49 $ 円増やすことができます。 - 町 $ 5 $ に移動する。所持金が $ 10\ ^\ {10\ ^\ {100}}-12 $ 円になる。 - $ 1 $ 回目の市場に参加する。所持金が $ 10\ ^\ {10\ ^\ {100}}+18 $ 円になる。 - 町 $ 4 $ に移動する。所持金が $ 10\ ^\ {10\ ^\ {100}}+15 $ 円になる。 - $ 3 $ 回目の市場に参加する。所持金が $ 10\ ^\ {10\ ^\ {100}}+40 $ 円になる。 - 町 $ 2 $ に移動する。所持金が $ 10\ ^\ {10\ ^\ {100}}+34 $ 円になる。 - $ 4 $ 回目の市場に参加する。所持金が $ 10\ ^\ {10\ ^\ {100}}+49 $ 円になる。 所持金を $ 10\ ^\ {10\ ^\ {100}}+50 $ 円以上にすることはできないため、`49` を出力してください。

### Sample Explanation 2

通行料が高すぎるので、高橋君は町 $ 1 $ から動かないのが最適です。

### Sample Explanation 4

出力すべき値が $ 32\operatorname{bit} $ 整数の範囲に収まらない場合があることに注意してください。

## 样例 #1

### 输入

```
6 3
4
5 30
2 10
4 25
2 15```

### 输出

```
49```

## 样例 #2

### 输入

```
6 1000000000
4
5 30
2 10
4 25
2 15```

### 输出

```
0```

## 样例 #3

### 输入

```
50 10
15
37 261
28 404
49 582
19 573
18 633
3 332
31 213
30 377
50 783
17 798
4 561
41 871
15 525
16 444
26 453```

### 输出

```
5000```

## 样例 #4

### 输入

```
50 1000000000
15
30 60541209756
48 49238708511
1 73787345006
24 47221018887
9 20218773368
34 40025202486
14 28286410866
24 82115648680
37 62913240066
14 92020110916
24 20965327730
32 67598565422
39 79828753874
40 52778306283
40 67894622518```

### 输出

```
606214471001```

# 题解

## 作者：elbissoPtImaerD (赞：5)

dp，$f_{i,j}$ 表示已经考虑了 $[0,i)$ 的交易，目前位于 $j$ 城市。

考虑第 $i$ 个交易 $(T,p)$ 的转移。

首先要有 $f_{i+1}=f_i$，含义是原地不动。

然后是 $f_{i+1,T}=\max\limits_{j\in[0,n)}\{f_{i,j}-|j-T|\times C\}+p$。

把绝对值拆开，变形：$f_{i+1,T}=\max\{\max\limits_{j\in[0,T)}\{f_{i,j} +jC\}-TC+p,\max\limits_{j\in[T,n)}\{f_{i,j}-jC\}+TC+p\}$。

考虑用数据结构优化转移，发现我们要做的是单点修改，求前后缀最大值，开两颗 BITS 分别维护 $f_{i,j} \pm jC$ 即可。

注意由于答案是 $\max{f_{i,j}}$，所以不能在 BITS 上查全局最大值作为答案，要把每次转移时计算出的 $f_{i+1,T}$ 取最大值作为答案。

[$\color{green}{\checkmark}$](https://atcoder.jp/contests/abc353/submissions/53382203)

---

## 作者：yemuzhe (赞：3)

首先考虑暴力 DP。

设最后一步走到编号 $i$  的城镇的方案的最大收益为 $f _ i$，则每次集市相当于是 $f _ {T _ i} \leftarrow f _ j - C |T _ i - j| + P _ i$（$1 \le j \le n$）。

这样每次可以通过枚举 $j$ 来转移，这样总时间复杂度是 $O (nm)$ 的，无法通过。

考虑优化 DP，先拆绝对值，把转移分为以下两类：

- $f _ {T _ i} \leftarrow f _ j - C (T _ i - j) + P _ i$（$1 \le j \le T _ i$），即 $f _ {T _ i} \leftarrow (f _ j + C \cdot j) + (- C \cdot T _ i + P _ i)$。

  注意到后面部分是定值而前面部分与 $i$ 无关，$j$ 的取值范围又是一段前缀，所以我们用树状数组维护 $f _ j + C \cdot j$ 的前缀最大值。

- $f _ {T _ i} \leftarrow f _ j - C (j - T _ i) + P _ i$（$T _ i \le j \le n$），即 $f _ {T _ i} \leftarrow (f _ j - C \cdot j) + (C \cdot T _ i + P _ i)$。

  同理我们用树状数组维护 $f _ j - C \cdot j$ 的后缀最大值。怎样用树状数组维护后缀信息？只需交换两个循环循序即可。

然后我们把 $f _ {T _ i}$ 插入到树状数组的 $T _ i$ 位置去。

初始状态为 $f _ 1 = 0$，最后答案为 $\max \limits _ {1 \le i \le m} \{f _ {T _ i}\}$。注意代码中的 $f _ i$ 表示的是上文的 $f _ {T _ i}$。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 200005
using namespace std;

const long long inf = 0x3f3f3f3f3f3f3f3f;

int n, m, c;
long long y, ans, tr1[N], tr2[N], f[N];

void get_mx1 (int p, long long c)
{
    for (; p <= n; p += p & -p) tr1[p] = max (tr1[p], c);
    return ;
}

long long ask1 (int p)
{
    long long res = -inf;
    for (; p; p &= p - 1) res = max (res, tr1[p]);
    return res;
}

void get_mx2 (int p, long long c)
{
    for (; p; p &= p - 1) tr2[p] = max (tr2[p], c);
    return ;
}

long long ask2 (int p)
{
    long long res = -inf;
    for (; p <= n; p += p & -p) res = max (res, tr2[p]);
    return res;
}

int main ()
{
    scanf ("%d%d%d", &n, &c, &m);
    memset (tr1, 0xc0, sizeof tr1);
    memset (tr2, 0xc0, sizeof tr2);
    f[0] = 0, get_mx1 (1, c);
    get_mx2 (1, -c);
    for (int i = 1, x; i <= m; i ++)
    {
        scanf ("%d%lld", &x, &y);
        long long t1 = ask1 (x) - (long long) x * c;
        long long t2 = ask2 (x) + (long long) x * c;
        f[i] = max (t1, t2) + y, ans = max (ans, f[i]);
        get_mx1 (x, f[i] + (long long) x * c);
        get_mx2 (x, f[i] - (long long) x * c);
    }
    printf ("%lld", ans);
    return 0;
}
```

---

## 作者：sunkuangzheng (赞：3)

$\textbf{ABC353G}$

容易设计出一个简单的 DP：设 $f_{i,j}$ 表示 $i$ 活动进行完，位置在 $j$ 的最大收益，考虑转移。

- 对于活动举办的位置 $t$，有 $f_{i,t} = \max\limits_{j=1}^n \{f_{i-1,j} - c \cdot |t - j|\} + p$。
- 否则，$f_{i,j} = f_{i-1,j}$。

注意到 $f_i$ 只与 $f_{i-1}$ 有关，因此可以把第一维滚掉。

考虑把第一种转移拆贡献：

- 对于 $j \le t$，$f_t = \max \{f_j + c \cdot j\} - c \cdot t + p$。
- 对于 $j > t$，$f_t = \max \{f_j - c \cdot j\} + c \cdot t + p$。

因此我们的第一种转移其实就是一个求前后缀 $\max$ 的过程，且对于每一个活动只会造成一个单点修改。使用线段树维护 $f_i+c \cdot i,f_i - c \cdot i$ 的最值即可。

推荐使用 Atcoder Library（使用方法 [link](https://www.cnblogs.com/sunkuangzheng/p/18032630)），代码非常短。

```cpp
#include<bits/stdc++.h>
using ll = long long;
using namespace std;
int T,n,c,m,x; ll p;
#include <atcoder/segtree>
ll e(){return -1e18;}
ll op(ll a,ll b){return max(a,b);}
int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    cin >> n >> c >> m;
    atcoder::segtree<ll,op,e> t1(n + 1),t2(n + 1);
    t1.set(1,c),t2.set(1,-c);
    for(int i = 1;i <= m;i ++){
        cin >> x >> p;
        ll d1 = t1.prod(1,x+1),d2 = t2.prod(x,n + 1);
        ll f = max(d1 - 1ll * c * x,d2 + 1ll * c * x) + p;
        t1.set(x,max(t1.get(x),f + 1ll * c * x)),
        t2.set(x,max(t2.get(x),f - 1ll * c * x));
    }ll ans = 0;
    for(int i = 1;i <= n;i ++) ans = max(ans,t1.get(i) - 1ll * c * i);
    cout << ans;
}
```

---

## 作者：cjh20090318 (赞：2)

没打这次比赛，赛后来看题发现相较于其他场的 G 较简单。

## 题意

有 $N$ 个小镇和 $M$ 次市场，从小镇 $i$ 移动到小镇 $j$ 需花费 $C \times \vert i-j \vert$ 元。

每次交易依次举行，第 $i$ 次交易在小镇 $T_i$ 举行，可获得 $P_i$ 元。

你需要从小镇 $1$ 出发，选择参加一些交易活动，来获取最多的钱。**过程中无需保证钱非负。**

## 分析

贪心无从下手，考虑动态规划。

### 状态设计

设 $f_i$ 表示结束点在小镇 $i$ 可以获取到的最多钱数。

### 初始状态

$$
f_i = \begin{cases}0 & i=1 \\ -\infty & \text{otherwise}\end{cases}
$$

### 转移方程

设某次交易在小镇 $T$ 举行，可获得 $P$ 元。
$$
f_T = \max\limits^{1 \le i \le n \land i \neq T}{(f_i + C \times \vert T - i\vert)} + P
$$
可以用线段树优化，将绝对值拆开。

对于 $i < T$ 的点维护 $f_i  - C \times i$ 的最大值，对于 $i > T$ 的点维护 $f_i  + C \times i$ 的最大值，然后分别处理即可。

## 代码

```cpp
//the code is from chenjh
#include<cstdio>
#include<algorithm>
#define MAXN 200002
using namespace std;
typedef long long LL;
const LL infll=0x3f3f3f3f3f3f3f3fll;
using ci=const int;
int n,c,m;
struct SEG{//线段树。
	#define lson (rt<<1)
	#define rson (rt<<1|1)
	LL mx[MAXN<<2];
	void build(ci rt,ci l,ci r){
		if(l==r){mx[rt]=-infll;return;}//初始化为极小值。
		int mid=(l+r)>>1;
		build(lson,l,mid),build(rson,mid+1,r);
		mx[rt]=max(mx[lson],mx[rson]);
	}
	void update(ci rt,ci l,ci r,ci pos,const LL&val){
		if(l==r){mx[rt]=max(mx[rt],val);return;}//对于每次交易取最大值。
		int mid=(l+r)>>1;
		pos<=mid?update(lson,l,mid,pos,val):update(rson,mid+1,r,pos,val);
		mx[rt]=max(mx[lson],mx[rson]);
	}
	LL query(ci rt,ci l,ci r,ci L,ci R){
		if(L<=l && r<=R) return mx[rt];
		int mid=(l+r)>>1;
		LL ret=-infll;
		if(L<=mid) ret=max(ret,query(lson,l,mid,L,R));
		if(mid<R) ret=max(ret,query(rson,mid+1,r,L,R));
		return ret;
	}
};
SEG s1,s2;
int main(){
	scanf("%d%d%d",&n,&c,&m);
	s1.build(1,1,n),s2.build(1,1,n);
	s1.update(1,1,n,1,c),s2.update(1,1,n,1,-c);//s1 维护绝对值加的部分，s2 维护绝对值减的部分。
	int t;LL p;
	for(int i=1;i<=m;i++){
		scanf("%d%lld",&t,&p);
		LL s=max(s1.query(1,1,n,1,t)-(LL)c*t,s2.query(1,1,n,t,n)+(LL)c*t)+p;//左边和右边分别取最大值。
		s1.update(1,1,n,t,s+(LL)c*t),s2.update(1,1,n,t,s-(LL)c*t);//更新当前点最大值。
	}
	LL ans=0;
	for(int i=1;i<=n;i++) ans=max({ans,s1.query(1,1,n,i,i)-(LL)c*i,s2.query(1,1,n,i,i)+(LL)c*i});//把扣减的距离加回来，取答案最大值。
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：kkxacj (赞：2)

首先考虑 $m^2$ 暴力怎么打，很容易得到以下代码：

```cpp
t[0] = 1;
for(int i = 1;i <= m;i++)
{
	for(int j = 0;j < i;j++)
		f[i] = max(f[i],f[j] - c * abs(t[i] - t[j]) + p[i]);
	ans = max(ans,f[i]);
}
```

$f_i$ 表示参加第 $i$ 场获得的最大收益为多少，但显然这样过不了题，可以发现，对于第 $i$ 场，他的最大收益为所有满足 $t_j \le t_i$ 的 $j$ 的最大值和所有满足 $t_j \ge t_i$ 的 $j$ 的最大值之中的最大值，考虑开两颗线段树维护这两种情况下的最大值是多少，然后就可以了。

**code**
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
namespace IO
{
	template<typename T>
	void read(T &_x){_x=0;int _f=1;char ch=getchar();while(!isdigit(ch)) _f=(ch=='-'?-1:_f),ch=getchar();while(isdigit(ch)) _x=_x*10+(ch^48),ch=getchar();_x*=_f;}
	template<typename T,typename... Args>
	void read(T &_x,Args&...others){Read(_x);Read(others...);}
	const int BUF=20000000;char buf[BUF],top,stk[32];int plen;
	#define pc(x) buf[plen++]=x
	#define flush(); fwrite(buf,1,plen,stdout),plen=0;
	template<typename T>inline void print(T x){if(!x){pc(48);return;}if(x<0) x=-x,pc('-');for(;x;x/=10) stk[++top]=48+x%10;while(top) pc(stk[top--]);}
}
using namespace IO;
int n,c,m,t[200010],p[200010],f[200010],ans,bj;
struct w
{
	int l,r,ma,bj;
}b[800010][2];
void build(int p,int l,int r,int id)
{
	b[p][id].l = l,b[p][id].r = r;b[p][id].bj = -1e18; b[p][id].ma = -1e18;
	if(l == r) return;
	int mid = (l + r) / 2;
	build(p * 2,l,mid,id),build(p * 2 + 1,mid + 1,r,id);
}
inline void push(int p,int id)
{
	b[p*2][id].ma = max(b[p*2][id].ma,b[p][id].bj);
	b[p*2+1][id].ma = max(b[p*2+1][id].ma,b[p][id].bj);
	b[p*2][id].bj = max(b[p*2][id].bj,b[p][id].bj);
	b[p*2+1][id].bj = max(b[p*2+1][id].bj,b[p][id].bj);
	b[p][id].bj = -1e18;
}
void change(int p,int l,int r,int k,int id)
{
	if(l <= b[p][id].l && b[p][id].r <= r) 
	{
		b[p][id].ma = max(b[p][id].ma,k);
		b[p][id].bj = k;
		return;
	}
	if(b[p][id].bj != -1e18) push(p,id);
	int mid = (b[p][id].l + b[p][id].r) / 2;
	if(l <= mid) change(p * 2,l,r,k,id);
	if(mid < r) change(p * 2 + 1,l,r,k,id);
	b[p][id].ma = max(b[p*2][id].ma,b[p*2+1][id].ma);
}
void ask(int p,int l,int r,int id)
{
	if(l <= b[p][id].l && b[p][id].r <= r) 
	{
		ans = max(ans,b[p][id].ma);
		return;
	}
	if(b[p][id].bj != -1e18) push(p,id);
	int mid = (b[p][id].l + b[p][id].r) / 2;
	if(l <= mid) ask(p * 2,l,r,id);
	if(mid < r) ask(p * 2 + 1,l,r,id);
}
signed main()
{
	read(n),read(c),read(m);
	build(1,1,n,0); build(1,1,n,1);
	for(int i = 1;i <= m;i++) f[i] = -1e18,read(t[i]),read(p[i]);
	t[0] = 1;
	change(1,t[0],n,c*t[0],0);//t[j]<t[i]
	change(1,1,t[0],-c*t[0],1);//t[j]>t[i]
 	for(int i = 1;i <= m;i++)
	{
		ans = -1e18,ask(1,1,t[i],0);
		f[i] = max(f[i],ans - c*t[i] + p[i]);
		
		ans = -1e18,ask(1,t[i],n,1);
		f[i] = max(f[i],ans + c*t[i] + p[i]);
		change(1,t[i],t[i],f[i] + c*t[i],0);//t[j]<=t[i]
		change(1,t[i],t[i],f[i] - c*t[i],1);//t[j]>=t[i]
		bj = max(bj,f[i]);
	}
	print(bj);
	flush();
	return 0;
}

```

---

## 作者：__Floze3__ (赞：2)

## 思路简介

~~建议交换 F 与 G 题位置~~

我们一条一条地处理每一次集市。假设第 $i$ 次集市发生在 $x$ 点，我们令 $f_x$ 走到 $x$ 这一节点时能够得到的最大代价。根据题目描述，我们不难列出这样的式子：$f_x = p_i + \max_{1 \le y \le N} \lbrace f_y - C \times \lvert x - y \rvert \rbrace$。我们考虑对于绝对值进行拆分，则有：
$$
\begin{aligned}
    f_x &= p_i + \max_{1 \le y \le N} \lbrace f_y - C \times \lvert x - y \rvert \rbrace \\
        &= p_i + \max \lbrace \max_{1 \le y \le x} \lbrace f_y - C \times (x - y)  \rbrace, \max_{x \le y \le N} \lbrace f_y - C \times (y - x) \rbrace \rbrace \\
        &= p_i + \max \lbrace \max_{1 \le y \le x} \lbrace f_y + C \times y \rbrace - C \times x, \max_{x \le y \le N} \lbrace f_y - C \times y\rbrace + C\times x \rbrace
\end{aligned}
$$

再翻译一下题目的条件：不就是单点修改，区间查询最大值吗？那么事情一下就简单了，我们可以用两棵线段树，一棵维护 $f_i + C \times i$ 的最大值，一棵维护 $f_i - C \times i$ 的最大值。每处理一次集会将结果与答案取最大值即可。代码很好写，这里不给了。

---

## 作者：WorldMachine (赞：1)

## ABC353G 题解

没去成 THUSC，成消愁了

### 题目大意

有 $n$ 个城市和 $m$ 次集市，集市依次举行，第 $i$ 次集市在城市 $T_i$ 举行，参与它可以获得 $P_i$ 元，也可以不参与。从城市 $i$ 移动到城市 $j$ 需要花费 $C\cdot|i-j|$ 元。初始时位于城市 $1$，钱足够多。求 $m$ 次集市举行后的最大收益。

### Solution

设 $f_i$ 表示前 $i$ 次集市举行后的最大收益。递推式为：
$$
f_i=\max_{j=0}^{i-1}\{f_j-C\cdot|T_i-T_j|\}+P_j
$$
初始值为 $f_0=0$。

暴力显然过不了，考虑优化。由于我太蒻了没学过这样那样的优化，我选择了使用 **线段树**。

具体地说，答案分两部分：$T_j\leq T_i$ 的答案，与 $T_j>T_i$ 的答案。两者取最大值即可。

当 $T_j\leq T_i$ 时，递推式变为：
$$
f_i=\max_{j=0}^{i-1}\{f_j-C\cdot T_i+C\cdot T_j\}+P_i=\max_{j=0}^{i-1}\{f_j+C\cdot T_j\}-C\cdot T_i+P_i
$$
同理，当 $T_j>T_i$ 时，递推式变为：
$$
f_i=\max_{j=0}^{i-1}\{f_j+C\cdot T_i-C\cdot T_j\}+P_i=\max_{j=0}^{i-1}\{f_j-C\cdot T_j\}+C\cdot T_i+P_i
$$
用两棵下标为 $T_j$ 的线段树，分别维护 $f_j+C\cdot T_j$ 和 $f_j-C\cdot T_j$ 的区间最大值即可。注意除了 $f_0$ 以外要初始化成 $-\infty$。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
void read(int &a) { a = 0; char c = getchar(); while (c < '0' || c > '9') c = getchar(); while (c >= '0' && c <= '9') a = a * 10 - '0' + c, c = getchar(); }
const int N = 200005, INF = 0x8080808080808080ll;
int n, C, m, t[N], p[N], c[N * 4][2], dp[N];
void update(int p, int l, int r, int x, int d, int t) {
	if (l == r) return c[p][t] = d, void();
	int mid = l + r >> 1;
	if (x <= mid) update(p * 2, l, mid, x, d, t);
	else update(p * 2 + 1, mid + 1, r, x, d, t);
	c[p][t] = max(c[p * 2][t], c[p * 2 + 1][t]);
}
int query(int p, int l, int r, int s, int e, int t) {
	if (l > r) return INF;
	if (s <= l && r <= e) return c[p][t];
	int mid = l + r >> 1, ans = INF;
	if (s <= mid) ans = max(ans, query(p * 2, l, mid, s, e, t));
	if (e > mid) ans = max(ans, query(p * 2 + 1, mid + 1, r, s, e, t));
	return ans;
}
signed main() {
	read(n), read(C), read(m);
	for (int i = 1; i <= m; i++) read(t[i]), read(p[i]);
	memset(c, 0x80, sizeof(c));
	update(1, 1, n, 1, C, 0);
	update(1, 1, n, 1, -C, 1);
	for (int i = 1, dp0, dp1; i <= m; i++) {
		dp0 = query(1, 1, n, 1, t[i], 0) - C * t[i] + p[i];
		dp1 = query(1, 1, n, t[i] + 1, n, 1) + C * t[i] + p[i];
		dp[i] = max(dp0, dp1);
		update(1, 1, n, t[i], dp[i] + C * t[i], 0);
		update(1, 1, n, t[i], dp[i] - C * t[i], 1);
	}
	int ans = 0;
	for (int i = 1; i <= m; i++) ans = max(ans, dp[i]);
	printf("%lld", ans);
}
```

---

## 作者：_Yonder_ (赞：1)

~~调了半天结果是没开 long long。~~

首先暴力代码不难写吧：
```
rep(i,1,m){
    f[i]=-(t[i]-1)*c;
    rep(j,1,i-1){
        f[i]=max(f[i],f[j]-abs(t[j]-t[i])*c);
    }Max=max(Max,f[i]+=p[i]);
}
```
我们注意到，$t_i$ 的值可以改成 $t_i×c$，$\left\vert t_j-t_i\right\vert$ 可以分类讨论：
```
rep(i,1,m){
    f[i]=-t[i]+c;
    rep(j,1,i-1)
        if(t[j]<=t[i]) f[i]=max(f[i],f[j]+t[j]-t[i]);
        else f[i]=max(f[i],f[j]-t[j]+t[i]);
    Max=max(Max,f[i]+=p[i]);
}
```
到这里状态转移的含 $i$ 量只有 $t_i$ 了，但这个其实也可以放到循环外面，于是我们要维护的只有 $\max\{f_j+t_j\}$ 和 $\max\{f_j-t_j\}$ 了，两个线段树即可。
# Code
```
#include<bits/stdc++.h>
#define ll long long
#define rep(i,l,r) for(ll i=l;i<=r;i++)
#define per(i,l,r) for(ll i=l;i>=r;i--)
using namespace std;
template<typename P>inline void read(P&x){bool f=0;x=0;char c=getchar();while(!isdigit(c)) f|=c=='-',c=getchar();while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=getchar();x=f?~(x-1):x;}
template<typename P>inline void write(P x){if(x<0) putchar('-'),x=-x;if(x>9) write(x/10);putchar((x%10)^48);}
const int N=2e5+5;
struct node{
    ll tr[N<<2]={};
    void add(int ind,ll c,int p,int pl,int pr){
        if(pl==pr){tr[p]=c;return;}int mid=pl+pr>>1;
        if(ind<=mid) add(ind,c,p<<1,pl,mid);
        else add(ind,c,p<<1|1,mid+1,pr);
        tr[p]=max(tr[p<<1],tr[p<<1|1]);
    }ll ask(int l,int r,int p,int pl,int pr){
        if(l<=pl&&pr<=r) return tr[p];int mid=pl+pr>>1;ll ans=-1e15;
        if(l<=mid) ans=ask(l,r,p<<1,pl,mid);
        if(r>mid) ans=max(ans,ask(l,r,p<<1|1,mid+1,pr));
        return ans;
    }
}T[2];
ll n,m,c,t[N],p[N],f[N],Max,sum;int T2[N];
int main(){
    std::ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    cin>>n>>c>>m;rep(i,1,m) cin>>T2[i]>>p[i],t[i]=T2[i]*1ll*c;
    memset(T[0].tr,-0x3f,sizeof(T[0].tr));
    memset(T[1].tr,-0x3f,sizeof(T[1].tr));
    rep(i,1,m){
        f[i]=-t[i]+c;
        if(i>1)
            f[i]=max({f[i],T[0].ask(0,T2[i],1,0,n+1)-t[i],
            T[1].ask(T2[i]+1,n+1,1,0,n+1)+t[i]});
        f[i]+=p[i];
        T[0].add(T2[i],f[i]+t[i],1,0,n+1);
        T[1].add(T2[i],f[i]-t[i],1,0,n+1);
        Max=max(Max,f[i]);
    }cout<<Max;
	return 0;
}
```

---

## 作者：Elysian_Realme (赞：0)

# AT_abc353_G

## 解题思路

这题很显然是一道 dp，思考一下状态定义。

考虑以每一座城市为状态，那么第 $i$ 次集会的转移方程为 $dp_{T_i}=\max\limits_{j=1}^{j\le n}\{dp_j-|i-j|\times c+P_i\}$。

但是如果直接这样转移的话复杂度是 $O(nm)$ 的。

观察到这是一个 RMQ 问题，虽然其中有 $i$ 的参与，但是我们可以通过分类讨论的方式把他提出来。

原转移方程就可以转化为：
$dp_{T_i}=\max\{\max\limits_{j=1}^{T_i}\{dp_j-i\times c+j\times c\},\max\limits_{j=T_i}^n\{dp_j+i\times c-j\times c\}\}+P_i$ 即 
$dp_{T_i}=\max\{\max\limits_{j=1}^{T_i}\{dp_j+j\times c\}-i\times c,\max\limits_{j=T_i}^n\{dp_j-j\times c\}+i\times c\}+P_i$。

这样一来，我们只需要用线段树维护一下 $dp_j-j\times c$ 和 $dp_j+j\times c$ 就可以了。

code：

```cpp
// Problem: G - Merchant Takahashi
// Contest: AtCoder - AtCoder Beginner Contest 353
// URL: https://atcoder.jp/contests/abc353/tasks/abc353_g
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// By：lmq
// AC Time：2024-05-13 20:01:40

#include <bits/stdc++.h>
#define int long long
#define lc (i<<1)
#define rc (i<<1|1)
using namespace std;
const int N=2e5+5;
const int INF=1e18;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
struct node{
	int l,r,mx[2];
}tree[N*4];
int n,m,c;
int dp[N];
void push_up(int i){
	tree[i].mx[0]=max(tree[lc].mx[0],tree[rc].mx[0]);
	tree[i].mx[1]=max(tree[lc].mx[1],tree[rc].mx[1]);
}
void build(int i,int l,int r){
	tree[i].l=l,tree[i].r=r;
	if(l==r){
		tree[i].mx[0]=dp[l]+l*c;
		tree[i].mx[1]=dp[l]-l*c;
		return;
	}
	int mid=(tree[i].l+tree[i].r)>>1;
	build(lc,l,mid);
	build(rc,mid+1,r);
	push_up(i);
}
void upd(int i,int p){
	if(tree[i].l==p&&tree[i].r==p){
		tree[i].mx[0]=dp[p]+p*c;
		tree[i].mx[1]=dp[p]-p*c;
		return;
	}
	int mid=(tree[i].l+tree[i].r)>>1;
	if(p<=mid)
		upd(lc,p);
	else
		upd(rc,p);
	push_up(i);
}
int qry_max(int i,int l,int r,int k){
	if(tree[i].l>=l&&tree[i].r<=r)
		return tree[i].mx[k];
	int ret=-INF,mid=(tree[i].l+tree[i].r)>>1;
	if(l<=mid)
		ret=max(ret,qry_max(lc,l,r,k));
	if(r>mid)
		ret=max(ret,qry_max(rc,l,r,k));
	return ret;
}
signed main(){
	cin>>n>>c>>m;
	for(int i=2;i<=n;i++)
		dp[i]=-INF;
	build(1,1,n);
	for(int i=1;i<=m;i++){
		int t,p;t=read(),p=read();
		dp[t]=max(dp[t],qry_max(1,1,t,0)-t*c);
		dp[t]=max(dp[t],qry_max(1,t,n,1)+t*c);
		dp[t]+=p;
		upd(1,t);
	}
	int ans=0;
	for(int i=1;i<=n;i++)
		ans=max(ans,dp[i]);
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：2020kanade (赞：0)

[Atcoder link,ABC353G.](https://atcoder.jp/contests/abc353/submissions/53402293)

首先有个结论：每次走动必定是一次走到集市举办点，因为走回头路一定不优，且多次沿一个方向走等于走一次。

考虑动态规划：$f_{i,j}$ 表示举办第 $i$ 次集市时高桥在位置 $j$ 时的最大 $X$ 值， $j=T_i$ 即第 $i$ 次举办集市在当前位置时有 
$$f_{i,T_i}=\max_{j\in[1,n]}\{f_{i-1,j} - \mid j-T_i \mid\times C\}+P_i$$
否则由于每次走动必定是一次性地走到集市举办点，唯一的决策是不动，即 
$$f_{i,j}=f_{i-1,j},j\neq T_i$$

根据天波老师所言，二维状态直接没救了，但是第一维可以直接滚掉，第二维每次只有一个点需要转移（其他点直接继承状态），实现上想必没人会把转移是直接继承的状态多复制一遍，因此总转移次数是 $\Theta(m)$ 的。

考虑优化转移，拆掉绝对值号：

$$f_{i,T_i}=\max\{f_{i-1,j}+T_{i}\times C-j\times C\}+P_{i},j\ge T_i$$
$$f_{i,T_i}=\max\{f_{i-1,j}+j\times C-T_i\times C\}+P_i,j\lt T_i$$

把 $T_i\times C$ 这一项提出去，要找的最优前继变成：

$$\max\{f_{i-1,j}-j\times C\},j\ge T_i$$
$$\max\{f_{i-1,j}+j\times C\},j\lt T_i$$

想必这里大家已经轻车熟路了：线段树维护 $f_{i,j}-j\times C$ 和 $f_{i,j}+j\times C$，转移时先分别全体 $+T_{i}\times C$ 或 $-T_{i}\times C$ 后取最大值，二者根据 $T_i$ 分别取一个前缀和一个后缀，取其中最大值后加上 $P_i$ 更新到当前状态即可。

维护带区间加，查询区间 $\max$ 的线段树，最后一步我的实现直接单写了一个单点修改，可能有其他写法。

另：根据 tbls 的宝贵经验，如果一颗线段树不知道怎么维护考虑开两颗，如果觉得不优雅可以参考下面的 code。

时间复杂度 $\Theta(n+m+m\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=5e5+11;
int ls[N*2],rs[N*2],cnt,rt;
ll val[N*2],val2[N*2],tag[N*2];
void down(int x)
{
	if(tag[x])
	{
		tag[ls[x]]+=tag[x],val[ls[x]]+=tag[x],val2[ls[x]]-=tag[x];
		tag[rs[x]]+=tag[x],val[rs[x]]+=tag[x],val2[rs[x]]-=tag[x];
		tag[x]=0;
	}
}
void up(int x)
{
	val[x]=max(val[ls[x]],val[rs[x]]);
	val2[x]=max(val2[ls[x]],val2[rs[x]]);
}
void add(int x,int l,int r,int al,int ar,ll v)
{
	if(al<=l&&r<=ar) return val[x]+=v,val2[x]-=v,tag[x]+=v,void();
	down(x);int mid=(l+r)>>1;
	if(al<=mid) add(ls[x],l,mid,al,ar,v);
	if(mid+1<=ar) add(rs[x],mid+1,r,al,ar,v);up(x);
}
ll ask(int x,int l,int r,int ql,int qr)
{
	if(ql<=l&&r<=qr) return val[x];
	down(x);int mid=(l+r)>>1;
	if(ql<=mid&&mid+1<=qr) return max(ask(ls[x],l,mid,ql,qr),ask(rs[x],mid+1,r,ql,qr));
	else if(ql<=mid) return ask(ls[x],l,mid,ql,qr);
	else return ask(rs[x],mid+1,r,ql,qr);
}
ll ask2(int x,int l,int r,int ql,int qr)
{
	if(ql<=l&&r<=qr) return val2[x];
	down(x);int mid=(l+r)>>1;
	if(ql<=mid&&mid+1<=qr) return max(ask2(ls[x],l,mid,ql,qr),ask2(rs[x],mid+1,r,ql,qr));
	else if(ql<=mid) return ask2(ls[x],l,mid,ql,qr);
	else return ask2(rs[x],mid+1,r,ql,qr);
}
ll A[N];
void change(int x,int l,int r,int q,ll v)
{
	if(l==r) return val[x]=v-A[l],val2[x]=v+A[l],void();
	down(x);int mid=(l+r)>>1;
	if(q<=mid) change(ls[x],l,mid,q,v);
	else change(rs[x],mid+1,r,q,v);up(x);
}
void c0nst(int &x,int l,int r,ll *A2)
{
	if(!x) x=++cnt;
	if(l==r) return val[x]=A2[l]-A[l],val2[x]=A2[l]+A[l],void();
	int mid=(l+r)>>1;
	c0nst(ls[x],l,mid,A2),c0nst(rs[x],mid+1,r,A2);
	return up(x);
}
int ops[N],n,m;ll C,pval[N],Ap[N];
//val:rt val2:le
//f[i][ops[i]]=val[i]+\max f[i-1][j]-abs(j-ops[i])*C
int main()
{
	cin>>n>>C;
	for(int i=1;i<=n;++i) A[i]=1ll*i*C,Ap[i]=-1ll*(i-1)*C;
	c0nst(rt,1,n,Ap);
	cin>>m;
	for(int i=1;i<=m;++i) cin>>ops[i]>>pval[i];
	for(int i=1;i<=m;++i)
	{
		add(rt,1,n,1,n,1ll*ops[i]*C);
		ll rps=ask(rt,1,n,ops[i],n),lps=-1e18;
		if(ops[i]>1) lps=ask2(rt,1,n,1,ops[i]-1);
		ll prod=max(lps,rps)+pval[i];
		add(rt,1,n,1,n,-1ll*ops[i]*C);change(rt,1,n,ops[i],prod);
	}
	ll ans=0;
	for(int i=1;i<=n;++i) ans=max(ans,ask(rt,1,n,i,i)+1ll*C*i);
	cout<<ans;return 0;
}
```

---

## 作者：JuRuoOIer (赞：0)

# 题解 ABC353G - Merchant Takahashi

~~考了个期中脑子废了，这题甚至没独立想出来~~

本题解为**线段树**（当然树状数组一样，只不过我比较愿意写线段树）做法。

### 题意

有 $n$ 个村庄，分别为 $1,2,3\dots n$。从第 $i$ 个村庄到第 $j$ 个村庄所需代价为 $c\times|i-j|$。

在这些村庄中先后要赶 $m$ 次集。每次赶集用一个二元组 $(t_i,p_i)$ 表示，其中 $t_i$ 是赶集的地点，$p_i$ 是高桥去了能赚到的钱。

高桥移动的时间忽略不计，初始钱数为 $0$ 且钱数可以为负。求最终**赚到钱**的最大值。

数据范围：$1 \le n,m \le 2\times10^5,1 \le t_i \le n,1 \le c \le 10^9,1 \le p_i \le 10^{13}$。

### 做法

首先一个比较简单的 $n^2$ dp 做法：
- 在某个时刻，设 $dp_i$ 为当前时刻之后留在 $i$ 位置的最大收益，
- 然后每个时刻把赶集那个村庄的更新一下就行。方程为（假设赶集的位置是 $i$）：

$$
dp_i=\max\left\{\max_{1 \le j \le i}\left\{p_i+dp_j-c(i-j)\right\},\max_{i < j \le n}\left\{p_i+dp_j-c(j-i)\right\}\right\}
$$

注意到这里我们每个时刻只需更新一个位置，所以考虑拿个数据结构维护 $dp$ 的值。

容易想到用两棵线段树分别维护两部分，然后就变成单点修改区间求 $\max$ 了。

### 注意

由于人初始在 $1$ 号点，所以开始时线段树中只有 $1$ 号点给初始值，其他点给 $-\infin$（**注意要够小**）。

```cpp
//省略头文件
#define ll long long
#define ull unsigned long long
#define lf double
#define ld long double
using namespace std;
ll n,c,m,p[200010],t[200010],dp[200010],ans;
struct SGT_1_2{
	//注意虽然开的静态数组，但写法类似于动态开点 
	ll mx[800010],ls[800010],rs[800010],p;//四倍空间 
	SGT_1_2(){
		p=1;//注意 0 是根节点，也会存东西 
	}
	void build(ll now,ll l,ll r){//建树 
		if(l==r){
			mx[now]=dp[l];//这里为了方便，直接用 dp 数组给初始值 
			return ;
		}
		ll mid=(l+r)>>1;
		ls[now]=p;
		p++;
		build(p-1,l,mid);//建左儿子 
		rs[now]=p;
		p++;
		build(p-1,mid+1,r);//建右儿子 
		mx[now]=max(mx[ls[now]],mx[rs[now]]);
	}
	void upd(ll now,ll l,ll r,ll x,ll y){//单点修改 
		if(l==r){
			mx[now]=y;
			return ;
		}
		ll mid=(l+r)>>1;
		if(x<=mid){
			upd(ls[now],l,mid,x,y);
		}
		else{
			upd(rs[now],mid+1,r,x,y);
		}
		mx[now]=max(mx[ls[now]],mx[rs[now]]);//记得更新 max 
	}
	ll getmx(ll now,ll l,ll r,ll l2,ll r2){
		if(l2>r2)return -9223372036854775807;//判一下 
		if(l2==l&&r2==r){
			return mx[now];
		}
		ll mid=(l+r)>>1;
		if(r2<=mid){
			return getmx(ls[now],l,mid,l2,r2);
		}
		else if(l2>mid){
			return getmx(rs[now],mid+1,r,l2,r2);
		}
		else{
			return max(getmx(ls[now],l,mid,l2,mid),getmx(rs[now],mid+1,r,mid+1,r2));
		}
	}
};
SGT_1_2 dp1,dp2;
int main(){
	cin>>n>>c>>m;
	dp[1]=c;
	for(int i=2;i<=n;i++){
		dp[i]=-9223372036854775807;//其它点在线段树里的值一定要够小 
	}
	dp1.build(0,1,n);
	dp[1]=-c;
	dp2.build(0,1,n);
	dp[1]=0;
	for(int i=0;i<m;i++){
		cin>>t[i]>>p[i];
		dp[t[i]]=max(dp1.getmx(0,1,n,1,t[i])+p[i]-c*t[i],dp2.getmx(0,1,n,t[i]+1,n)+p[i]+c*t[i]);
		ans=max(ans,dp[t[i]]);//更新答案 
		dp1.upd(0,1,n,t[i],dp[t[i]]+c*t[i]);//更新该点在线段树中的值 
		dp2.upd(0,1,n,t[i],dp[t[i]]-c*t[i]);
	}
	cout<<ans<<endl;
	return 0;
}

```

---

## 作者：DGH_Didi (赞：0)

### 题目大意

一共 $N$ 个城市，和 $M$ 场活动，按时间顺序进行，参加某个活动可以获得 $P_i$ 元，从 $x$ 到 $y$ 地需要消耗 $\left\vert x-y\right\vert \times C$ 元，初始有无限的钱，求最大能获得的价值。

- $1 \leq N \leq 2 \times 10^5$
- $1 \leq C \leq 10^9$
- $1 \leq M \leq 2 \times 10^5$
- $1 \leq P_i \leq 10^{13}$

### 解题思路
考虑动态规划。设 $dp_i$ 表示参加了第 $i$ 场活动所能获得的最大价值，则有以下转移：
$$dp_i = \max_{j<i}(dp_j-C\times \left\vert i-j\right\vert ) +p_i$$
分类得：
$$dp_i = \begin{cases}\max(dp_j+C\times j)-C\times i+p_i &j\leq i\\\max(dp_j-C\times j)+C\times i+p_i & j>i\\\end{cases}$$
因此我们开两个支持单点修改，区间取最大值的线段树进行转移即可。时间复杂度 $O(n\log n)$。

### 参考代码 
[完整代码点这里](https://atcoder.jp/contests/abc353/submissions/53382306)
```
signed main() {
    ios::sync_with_stdio(false), cin.tie(0);
    cin >> n >> c >> m;
    for (int i = 1; i <= m; i++) {
        cin >> t[i] >> p[i];
    }

    memset(dp, -0x3f, sizeof dp);
    dp[0] = 0, t[0] = 1;
    SegmentTree<Info> sl(n + 1), sr(n + 1);
    sl.modify(1, {c}), sr.modify(1, {-c});

    for (int i = 1; i <= m; i++) {
        dp[i] = max(sl.rangeQuery(1, t[i]).val - c * t[i], sr.rangeQuery(t[i], n).val + c * t[i]) + p[i];
        sl.modify(t[i], {dp[i] + c * t[i]}), sr.modify(t[i], {dp[i] - c * t[i]});
    }
    
    cout << *max_element(dp, dp + m + 1) << endl;
    return 0;
}
```

### 后记
赛时考虑到了分类处理和使用线段树维护，最后也没能想到能开两棵线段树，在此希望下次分类后可以考虑用多个数据结构同时处理问题。

---

## 作者：KSCD_ (赞：0)

### 题意
有 $n$ 个城市，$m$ 个依次进行的活动，初始有无穷多的钱且位于城市 $1$。在 $T_i$ 城市参加第 $i$ 个活动可以获得 $P_i$ 的钱，而从 $i$ 城市移动到 $j$ 城市需要花费 $C\times\left|i-j\right|$ 的钱，求最多能净赚多少钱。
### 思路
考虑动态规划解决。

设 $f_i$ 为最终停在第 $i$ 个城市能赚的最大钱数，有初值 $f_1=0$。由于要取最大值，将所有 $i\neq 1$ 的 $f_i$ 赋为负无穷。

接着需要依次处理每个活动，每次有转移式
$f_{T_i}=\max(f_{T_i},P_i+\max\limits_{j=1}^{n}(f_j-C\times\left|T_i-j\right|))$，其中要保证 $f_j$ 不为负无穷，否则没有意义。

如果每次转移时暴力地遍历整个 $f$ 数组，时间复杂度为 $O(mn)$，必然超时，需要更快速地求出转移式的第二项。

考虑使用数据结构优化时间复杂度，发现如果能把第二项中含 $j$ 的部分看成整体，就能用线段树维护最大值来解决。

那么需要通过分讨拆掉绝对值，因此化简得：
- 当 $j\leq T_i$ 时，$f_j-C\times\left|T_i-j\right|=-C\times T_i+f_j+C\times j$。
- 当 $j\geq T_i$ 时，$f_j-C\times\left|T_i-j\right|=C\times T_i+f_j-C\times j$。

发现两个式子中含 $i$ 的部分在每次转移时都是定值，因此当含 $j$ 的部分最大时，整个式子也最大。

因此可以用线段树分别维护 $f_j+C\times j$ 和 $f_j-C\times j$ 的区间最大值，每次转移时分别求 $\left[ 1,T_i\right]$ 和 $\left[T_i,n\right]$ 的最大值，再进行更新。

形式化地，先求 $k=\max(-C\times T_i+\max\limits_{j=1}^{T_i}(f_j+C\times j),C\times T_i+\max\limits_{j=T_i}^{n}(f_j-C\times j))$，再更新$f_{T_i}=\max(f_{T_i},P_i+k)$。

时间复杂度为 $O(m \log n)$。
### 代码
```cpp
#include<iostream>
#define int long long
using namespace std;
const int N=2e5+10;
const int inf=1e18;
int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') { if(ch=='-') w=-1;  ch=getchar();}
	while(ch>='0'&&ch<='9') { s=s*10+ch-'0',ch=getchar();}
	return s*w;
}
int n,c,m,ans,ct=1,f[N];
struct nod
{
	int l,r,w[2];
}a[N*2];
void pushup(nod &u,nod lc,nod rc)
{
	u.w[0]=max(lc.w[0],rc.w[0]),u.w[1]=max(lc.w[1],rc.w[1]);
}
void build(int u,int l,int r)
{
	if(l==r)
	{
		if(l==1) a[u].w[0]=c,a[u].w[1]=-c;
		else a[u].w[0]=a[u].w[1]=-inf;
		return;
	}
	int mid=(l+r)/2;
	a[u].l=++ct,build(ct,l,mid);
	a[u].r=++ct,build(ct,mid+1,r);
	pushup(a[u],a[a[u].l],a[a[u].r]);
}
void change(int u,int l,int r,int p)
{
	if(l==r)
	{
		a[u].w[0]=f[l]+l*c,a[u].w[1]=f[l]-l*c;
		return;
	}
	int mid=(l+r)/2;
	if(p<=mid) change(a[u].l,l,mid,p);
	else change(a[u].r,mid+1,r,p);
	pushup(a[u],a[a[u].l],a[a[u].r]); 
}
nod query(int u,int l,int r,int ll,int rr)
{
	if(l>=ll&&r<=rr) return a[u];
	int mid=(l+r)/2;
	if(rr<=mid) return query(a[u].l,l,mid,ll,rr);
	if(ll>mid) return query(a[u].r,mid+1,r,ll,rr);
	nod res;
	pushup(res,query(a[u].l,l,mid,ll,rr),query(a[u].r,mid+1,r,ll,rr));
	return res;
}
signed main()
{
	n=read(),c=read(),m=read();
	for(int i=2;i<=n;i++) f[i]=-inf;
	build(1,1,n);
	for(int i=1;i<=m;i++)
	{
		int x=read(),w=read();
		int ta=query(1,1,n,1,x).w[0],tb=query(1,1,n,x,n).w[1];
		if(ta!=-inf) ta-=x*c;
		if(tb!=-inf) tb+=x*c;
		int ts=w+max(ta,tb);
		if(ts>f[x]) f[x]=ts,change(1,1,n,x);
	}
	for(int i=1;i<=n;i++) ans=max(ans,f[i]);
	cout<<ans;
	return 0;
}
```

---

## 作者：aCssen (赞：0)

### Solution
首先题目中那个巨大的数字是为了保证你想怎么走都有钱的。

设 $f_i$ 表示考虑了前 $i$ 个活动，其中一定去第 $i$ 个活动的最大收益，这样涵盖了所有可能的情况。

那么转移就是 $f_i=\max_{0 \le j<i}\lbrace f_j+C \times |T_i-T_j| \rbrace+P_i$。

在这里，$T_0=1,f_0=0$。

最终答案即为 $\max_{i=0}^n \lbrace f_i\rbrace$。

考虑优化这个做法，注意到这个绝对值不好处理，于是把它拆开:
$$f_i=\max(\max_{0 \le j<i,T_j \le T_i}\lbrace f_j-C\times T_j \rbrace+P_i+ C\times T_i,$$

$$\max_{0 \le j<i,T_j \ge T_i}\lbrace f_j+C\times T_j \rbrace+P_i-C\times T_i)$$

从 $1 \sim n$ 计算 $f$ 时，已经保证了 $0 \le j <i$，可以以 $T_i$ 为下标，分别查询 $\le T_i$ 和 $\ge T_i$ 的最大 $f_j$ 值，用它们来更新 $f_i$。

那么这样就只有一维限制了，注意到每次查询都是前后缀，且修改是单点的，值域也不大。那么，树状数组是最好的选择。

时间复杂度 $\mathcal{O}(m \log m)$。

### Code
```cpp
#include<bits/stdc++.h>
#define lowbit(x) x&(-x)
using namespace std;
typedef long long ll;
const int maxn=2e5+5;
ll t1[maxn],t2[maxn],f[maxn],p[maxn],ans;
int t[maxn],n,m,c;
ll Abs(ll x){
	return x<0?-x:x;
}
void add1(int x,ll k){
	for(;x<=n;x+=lowbit(x)) t1[x]=max(t1[x],k);
}
void add2(int x,ll k){
	for(;x;x-=lowbit(x)) t2[x]=max(t2[x],k);
}
ll query1(int x){
	ll ans=0xcfcfcfcfcfcfcfcf;
	for(;x;x-=lowbit(x)) ans=max(ans,t1[x]);
	return ans;
}
ll query2(int x){
	ll ans=0xcfcfcfcfcfcfcfcf;
	for(;x<=n;x+=lowbit(x)) ans=max(ans,t2[x]);
	return ans;
}
int main(){
	memset(f,0xcf,sizeof(f));
	memset(t1,0xcf,sizeof(t1));
	memset(t2,0xcf,sizeof(t2));
	scanf("%d%d%d",&n,&c,&m);
	for(int i=1;i<=m;i++)
		scanf("%d%lld",&t[i],&p[i]);
	f[0]=0,t[0]=1;
	for(int i=1;i<=m;i++){
		ll w1=query1(t[i]),w2=query2(t[i]);
		f[i]=max(f[i],-1ll*c*Abs(t[i]-t[0])+p[i]);
		f[i]=max(f[i],w1+p[i]-1ll*c*t[i]);
		f[i]=max(f[i],w2+p[i]+1ll*c*t[i]);
		add1(t[i],f[i]+1ll*c*t[i]);
		add2(t[i],f[i]-1ll*c*t[i]);
	}
	for(int i=1;i<=m;i++)
		ans=max(ans,f[i]);
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Linge_Zzzz (赞：0)

# 题意简述

在一个数轴上有 $n$ 个点 $1,2,3,\cdots,n$。一个人初始在 $1$ 号点。给定一个常数 $c$。

接下来会有 $m$ 个活动 $(t_i,p_i)$ 依次举行。具体地，第 $i$ 个活动会在地点 $t_i$ 举办，参加这个活动可以获得 $p_i$ 单位的钱。

这个人如果要参加活动 $i$，则必须先从当前位置 $a$ 移动到 $t_i$，这会花费 $|a-t_i|\times c$ 单位的钱。

假设在每个活动开始前，这个人有充足的时间移动到他想移动到的地方。这个人初始时有无限多的钱，最大化钱的变化量。

# 题解

设 $f_i$ 为参加前 $i$ 项活动且参加第 $i$ 项的钱的最大变化量，则有：

$$ f_i=\max\{f_j-|t_i-t_j|\times c\} $$

暴力转移显然超时，考虑优化。

尝试通过讨论来拆掉绝对值。

当 $t_i>t_j$ 时，$ f_i=\max\{f_j-(t_i-t_j)\times c\} $。

拆项，提出常数项，有 $f_i=\max\{f_j+t_j\times c\}-t_i\times c$。

此时我们发现大括号内的值只和 $j$ 有关，求这个最大值就是所有满足 $t_j<t_i$ 的 $f_j+t_j\times c$ 的最大值。

这可以使用线段树来维护。具体地，我们建立一棵下标为 $[1,n]$ 的线段树，下标为 $i$ 的叶子表示所有满足 $t_j=i$ 的 $f_j+t_j\times c$ 的最大值。则我们转移 $f_i$ 时，查询 $[1,t_i-1]$ 的最大值，就是大括号中的值。

同理，对于 $t_i\leq t_j$ 时，有 $f_i=\max\{f_j-t_j\times c\}+t_i\times c$。另开一棵线段树按照同样的方法维护即可。

求出 $f_i$ 后，按照上面所说的，把 $f_i+t_i\times c$ 更新到第 $1$ 棵线段树的 $t_i$ 上，再把 $f_i-t_i\times c$ 更新到第 $2$ 棵线段树的 $t_i$ 上。

按照这种方式把 $f_1,f_2,f_3,\cdots,f_n$ 求出来，则答案为 $\max\{\max\{f_i\},0\}$，因为可以一个活动都不去。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+10,INF=0x3f3f3f3f3f3f3f3f,mod=1e9+7;
int n,c,m;
int a[N],p[N];
int t1[N*4],t2[N*4];
void update(int *t,int p,int l,int r,int pos,int val){
	if(l==r){
		t[p]=max(t[p],val);
		return;
	}
	int m=(l+r)>>1;
	if(pos<=m)update(t,p*2,l,m,pos,val);
	else update(t,p*2+1,m+1,r,pos,val);
	t[p]=max(t[p*2],t[p*2+1]);
}
int query(int *t,int p,int l,int r,int L,int R){
	if(L<=l&&r<=R)return t[p];
	int m=(l+r)>>1,ans=-INF;
	if(L<=m)ans=max(ans,query(t,p*2,l,m,L,R));
	if(R>m)ans=max(ans,query(t,p*2+1,m+1,r,L,R));
	return ans;
}
int f[N];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>c>>m;
	for(int i=1;i<=m;i++)cin>>a[i]>>p[i];
	memset(t1,-0x3f,sizeof(t1));
	memset(t2,-0x3f,sizeof(t2));
	update(t1,1,1,n,1,+c);
	update(t2,1,1,n,1,-c);
	int ans=0;
	for(int i=1;i<=m;i++){
		int lmx=query(t1,1,1,n,1,a[i])-c*a[i];
		int rmx=query(t2,1,1,n,a[i],n)+c*a[i];
		f[i]=max(lmx,rmx)+p[i];
		update(t1,1,1,n,a[i],f[i]+c*a[i]);
		update(t2,1,1,n,a[i],f[i]-c*a[i]);
		ans=max(ans,f[i]);
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：GI录像机 (赞：0)

## 思路：

设 $ans_i$ 表示人在第 $i$ 个集市的情况下最多能赚多少。朴素的做法是枚举 $ans_1$ 到 $ans_{i-1}$，取从这些集市来到 $i$ 集市中赚钱的最大值，即：

$$ans_i=P_i+\max^{i-1}_{j=1} ans_j-C\times|T_i-T_j|$$

考虑用数据结构维护最值。发现 $T_i$ 随时在变动，阻碍了我们的维护，于是考虑把 $T_i$ 提出来。

当 $T_i \le T_j$ 时，原式等价于：

$$ans_i=P_i+C\times T_i+\max^{i-1}_{j=1} ans_j-C\times T_j$$

当 $T_i > T_j$ 时，原式等价于：

$$ans_i=P_i-C\times T_i+\max^{i-1}_{j=1} ans_j+C\times T_j$$

这两者都很好维护。于是建两个大小为 $n$ 的线段树，第 $i$ 个叶子节点存储 $T_j=i$ 时 $ans_j\pm C\times T_j$ 的最大值，维护单点修改和区间查询即可。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int read() {
	int f = 1, x = 0;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-')f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0';
		c = getchar();
	}
	return f * x;
}
void write(int x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x > 9)write(x / 10);
	putchar(x % 10 + '0');
}
const int N = 2e5 + 10, MOD = 1e9 + 7, INF = 0x3f3f3f3f;
int n = read(), c = read(), m = read(), t[N], p[N], maxn1[N << 2], maxn2[N << 2], tmp, ans;
void pushup(int pos) {
	maxn1[pos] = max(maxn1[pos << 1], maxn1[pos << 1 | 1]);
	maxn2[pos] = max(maxn2[pos << 1], maxn2[pos << 1 | 1]);
}
void build(int pos, int l, int r) {
	if (l == r) {
		if(l == 1)maxn1[pos] = c, maxn2[pos] = -c;
		else maxn1[pos] = maxn2[pos] = -1e18;
		return;
	}
	int mid = (l + r) >> 1;
	build(pos << 1, l, mid);
	build(pos << 1 | 1, mid + 1, r);
	pushup(pos);
}
void change(int pos, int l, int r, int L, int k) {
	if (l == r) {
		maxn1[pos] = max(maxn1[pos], k + L * c);
		maxn2[pos] = max(maxn2[pos], k - L * c);
		return;
	}
	int mid = (l + r) >> 1;
	if (mid >= L)change(pos << 1, l, mid, L, k);
	else change(pos << 1 | 1, mid + 1, r, L, k);
	pushup(pos);
}
int query1(int pos, int l, int r, int L, int R) {
	if (L <= l && r <= R)return maxn1[pos];
	int mid = (l + r) >> 1, res = -1e18;
	if (mid >= L)res = max(res, query1(pos << 1, l, mid, L, R));
	if (mid + 1 <= R)res = max(res, query1(pos << 1 | 1, mid + 1, r, L, R));
	return res;
}
int query2(int pos, int l, int r, int L, int R) {
	if (L <= l && r <= R)return maxn2[pos];
	int mid = (l + r) >> 1, res = -1e18;
	if (mid >= L)res = max(res, query2(pos << 1, l, mid, L, R));
	if (mid + 1 <= R)res = max(res, query2(pos << 1 | 1, mid + 1, r, L, R));
	return res;
}
signed main() {
	//freopen(".in", "r", stdin);
	//freopen(".out", "w", stdout);
	build(1, 1, n);
	for (int i = 1; i <= m; i++) {
		t[i] = read(), p[i] = read();
		tmp = max(query1(1, 1, n, 1, t[i]) - t[i] * c, query2(1, 1, n, t[i], n) + t[i] * c) + p[i];
		ans = max(ans, tmp);
		change(1, 1, n, t[i], tmp);
	}
	write(ans);
	return 0;
}
```

---

## 作者：InQueue (赞：0)

$10^{10^{100}}$ 直接看做正无穷，即不用考虑中间过程收益为负的情况。

不难发现可以 dp。

设 $dp_i$ 表示已经决策完是否去第 $1\sim i$ 个市场，且去第 $i$ 个市场，所能产生的最大收益。

初始 $dp_0 = 0,t_0 = 1$，对于 $1\le i\le n$，根据上一个去的市场分类，列出转移方程：

$$dp_i = \max_{0\le j < i}(dp_j - C\left | t_i - t_j \right | ) + p_i$$

此时暴力递推，是 $O(n^2)$ 的。

把绝对值拆开：

$$\begin{aligned}

dp_i

&= \max(\max_{t_i\ge t_j}(dp_j - C(t_i - t_j)), \max_{t_i < t_j}(dp_j - C(t_j - t_i))) + p_i

\\ &= \max(\max_{t_i\ge t_j}(dp_j + Ct_j) - Ct_i, \max_{t_i < t_j}(dp_j - Ct_j) + Ct_i) + p_i

\end{aligned}$$

内层 $\max$ 里就只和 $j$ 有关了，两个树状数组 $/$ 线段树维护一下就行（把对应值记在 $t_i$ 位置）。

BIT 维护后缀还得反一下感觉有点麻烦，赛时直接拍了个线段树模板上去。

[AT 提交记录。](https://atcoder.jp/contests/abc353/submissions/53361412)

---

## 作者：Genius_Star (赞：0)

### 思路：

考虑动态规划算法，定义 $dp_{i,0/1}$ 表示是否完成第 $i$ 个任务的最大值，可得状态转移方程为：

$$dp_{i,0} = \max(dp_{i-1,0},dp_{i-1,1})$$

$$dp_{i,1} = \max\limits_{j=0}^{i-1} dp_{j,1} - C \times |T_i - T_j| + P_i$$

考虑拆掉绝对值，然后就是线段树维护区间最大值即可。

时间复杂度为 $O(N \log N)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef __int128 ll;
typedef double db;
const ll N=2e5+10;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll MAX[N<<2][2];
ll n,c,m,cnt;
ll a[N],b[N],h[N],d[N];
ll dp[N][2];
void pushup(ll k){
	MAX[k][0]=max(MAX[k<<1][0],MAX[k<<1|1][0]);
	MAX[k][1]=max(MAX[k<<1][1],MAX[k<<1|1][1]);
}
void add(ll k,ll l,ll r,ll i,ll v,ll t){
	if(l==i&&i==r){
		MAX[k][0]=max(MAX[k][0],v+c*t);
		MAX[k][1]=max(MAX[k][1],v-c*t);
		return ;
	}
	ll mid=(l+r)>>1;
	if(i<=mid)
	  add(k<<1,l,mid,i,v,t);
	else
	  add(k<<1|1,mid+1,r,i,v,t);
	pushup(k);
}
ll query(ll k,ll l,ll r,ll L,ll R,bool f){
	if(L>R)
	  return -1e18;
	if(l==L&&R==r)
	  return MAX[k][f];
	ll mid=(l+r)>>1;
	if(R<=mid)
	  return query(k<<1,l,mid,L,R,f);
	else if(L>mid)
	  return query(k<<1|1,mid+1,r,L,R,f);
	else
	  return max(query(k<<1,l,mid,L,mid,f),query(k<<1|1,mid+1,r,mid+1,R,f));
}
ll Abs(ll x){
	if(x<0)
	  return -x;
	return x;
}
int main(){
	memset(MAX,-0x7f,sizeof(MAX));
	n=read(),c=read(),m=read();
	for(int i=1;i<=m;i++){
		a[i]=read();
		b[i]=read();
		h[++cnt]=a[i];
	}
	sort(h+1,h+cnt+1);
	cnt=unique(h+1,h+cnt+1)-(h+1);
	for(int i=1;i<=m;i++)
	  d[i]=lower_bound(h+1,h+cnt+1,a[i])-h;
	dp[1][1]=b[1]-c*Abs(a[1]-1);
	add(1,1,cnt,d[1],dp[1][1],a[1]);
	for(int i=2;i<=m;i++){
		dp[i][0]=max(dp[i-1][0],dp[i-1][1]);
		dp[i][1]=b[i]-c*Abs(a[i]-1);
		ll t1=query(1,1,cnt,1,d[i],0)-c*a[i]+b[i],t2=query(1,1,cnt,d[i]+1,cnt,1)+c*a[i]+b[i];
//		cerr<<t1<<' '<<t2<<'\n';
		dp[i][1]=max({dp[i][1],t1,t2});
		add(1,1,cnt,d[i],dp[i][1],a[i]);
//		cerr<<dp[i][1]<<'\n';
	}
	write(max(dp[m][0],dp[m][1]));
	return 0;
}
```

---

## 作者：zrl123456 (赞：0)

[题目](https://www.luogu.com.cn/problem/AT_abc353_g)  

考察：树状数组，线段树，动态规划。  
题意简述：  
有 $n+1$ 个城市，编号为 $[0,n]$，你接到了 $m$ 个关于一个活动的消息：$t_i,p_i$。  
$t_i$ 表示该活动在第 $t_i$ 个城市举办，$p_i$ 表示参加活动可以获得的钱数，但是每经过一个城市，你要花费 $c$ 元的路费。  
你一开始在 $0$ 号城市，每个活动你可以参加，也可以不参加，但必须按顺序参加，求获得的钱数的最大值。  
数据范围：
- $1\le n,m\le 2\times 10^5$
- $1\le c\le 10^9$
- $1\le t_i\le n$
- $1\le p_i\le 10^{13}$

------------
我们可以看出明显是一道 dp 题，然后 $f_i$ 肯定跟 $f_j\ \ (0\le j<i)$ 有关，很容易推出状态转移方程：  
$$f_i=\max_{j=0}^{i-1}(f_j-c\times|x_i-x_j|+p_i)$$
但是这样转移是 $O(m^2)$ 的，无法通过 $m\le 2\times 10^5$ 的数据，考虑优化。  

每个点造成的贡献是 $f_j-c\times|x_i-x_j|+p_i$，其中 $p_i$ 是固定的，那么在 $f_j-c\times|x_i-x_j|$ 中，我们考虑如何拆掉绝对值符号，我们分类讨论 $|x_i-x_j|$：
- 当 $x_i\ge x_j$ 时：  
$$\begin{aligned}c\times|x_i-x_j|&=c\times(x_i-x_j)\\&=c\times x_i-c\times x_j\end{aligned}$$
$c\times x_i$ 是固定的，那么我们只需要找出 $-c\times x_j$ 的最大值即可。  
- 当 $x_i<x_j$ 时：
$$\begin{aligned}c\times|x_i-x_j|&=c\times(x_j-x_i)\\&=c\times x_j-c\times x_i\end{aligned}$$
$-c\times x_i$ 是固定的，那么我们只需要找出 $c\times x_j$ 的最大值即可。  

那么我们可以用树状数组或线段树维护 $f_{x_j}\ (x_j\le x_i)$ 的前缀最大值，$f_{x_j}\ (x_j>x_i)$ 的后缀最大值（由于树状数组只能维护前缀最大值，所以我们将 $f_{x_j}$ 变为 $f_{n-x_j}$）  
我们定义两个树状数组，$f$ 是维护 $x_j\le x_i$ 的最大值，查询的结果是 $fmax$，$g$ 是维护 $x_j>x_i$ 的最大值，查询的结果是 $gmax$，那么 $f_i$ 就等于：
$$f_i=\max(fmax+c\times x_i,gmax-c\times x_i)+p_i$$
然后我们在修改 $f,g$ 中的值即可。  

这样我们就可以在 $O(m\log_2n)$ 的复杂度内完成本题。  

代码：  
```cpp
#include<bits/stdc++.h>
#define int long long
#define inl inline
#define rep(i,x,y) for(int i=x;i<=y;++i)
#define per(i,x,y) for(int i=x;i>=y;--i)
#define fst; ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define endl '\n'
#define fi first
#define se second
#define INF LLONG_MAX
using namespace std;
const int N=2e5+5;
int n,c,m,t,p,num,ans; 
struct BIT{
	int a[N];
	inl BIT(){
		memset(a,-0x3f,sizeof(a));
	}
	inl int lowbit(int x){
		return x&(-x);
	}
	inl void add(int x,int k){
		while(x<=n){
			a[x]=max(a[x],k);
			x+=lowbit(x);
		}
		return;
	}
	inl int getmax(int x){
		int mx=-INF;
		while(x){
			mx=max(mx,a[x]);
			x-=lowbit(x);
		}
		return mx;
	}
}t1,t2;
signed main(){
	fst; 
	cin>>n>>c>>m;
	t1.add(1,c);
	t2.add(n,-c);
	rep(i,1,m){
		cin>>t>>p;
		num=max(t1.getmax(t)-c*t,t2.getmax(n-t)+c*t)+p;
		ans=max(ans,num);
		t1.add(t,num+c*t);
		t2.add(n-t+1,num-c*t);
	}
	cout<<ans;
	return 0;
}
```

---

