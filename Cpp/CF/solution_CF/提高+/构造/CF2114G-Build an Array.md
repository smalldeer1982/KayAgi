# Build an Array

## 题目描述

昨天，Dima 发现了一个空数组，并决定向数组中添加一些整数，他可以进行无限次下述操作：

- 向数组的左端或右端添加任意一个整数。
- 添加之后，只要数组中有一对相邻的数相同，它们就会被替换为它们的和。

可以证明数组中不会同时出现两对相邻的数相同。

例如，如果当前数组是 $[3,6,4]$，我们添加 $3$ 至数组的左端，则数组将首先变为 $[3,3,6,4]$，随后左端的两个 $3$ 将会被替换为 $6$，即数组变为 $[6,6,4]$，然后进一步变为 $[12,4]$。

在进行了恰好 $k$ 次操作后，他认为自己得到了一个长度为 $n$ 的数组 $a$。然而，他不记得自己都进行了哪些操作。请判定数组 $a$ 是否能由一组 $k$ 次操作序列得到。

## 样例 #1

### 输入

```
8
3 3
2 1 4
3 7
2 1 4
2 15
2 16
3 10
256 32 1
3 289
768 96 1
3 290
768 96 1
5 7
5 1 6 3 10
4 6
6 8 5 10```

### 输出

```
YES
NO
YES
YES
YES
NO
YES
YES```

# 题解

## 作者：the_Short_Path (赞：2)

## 形式化题意
给定一个数组，每次可以向左或右添加一个整数相邻且相等数对会合并为其和，求能否在恰好 $k$ 次操作时将其变为 $a$。

设一个数为 $x$，则它的拆分过程为：
$$\frac{x}{2},\frac{x}{2};$$
$$\frac{x}{2},\frac{x}{4},\frac{x}{4};$$
$$\frac{x}{4},\frac{x}{4},\frac{x}{4},\frac{x}{4};$$
$$\dots$$
则向一个空数组内添加 $x$ 需要操作的最大值为 $x$ 在二进制下为 $1$ 的最低位，记这个值为 $\operatorname{1b}(x)$。所以答案为：
$$\sum^{n}_{i=1}\operatorname{1b}(i)$$
但还有一些特殊处理。比如：
$$[2,\dots]\Rightarrow[8,2,\dots]$$
如果按照以下操作：
$$[2,\dots]\rightarrow[{\textcolor{blue}2},2,\dots]$$
$$[2,2,\dots]\rightarrow[\textcolor{red}{4},\dots]$$
则会产生错误。正确的是如下操作：
$$[2,\dots]\rightarrow[{\textcolor{blue}4},2,\dots]$$
$$[4,2,\dots]\rightarrow[{\textcolor{blue}2},4,2,\dots]$$
$$[2,4,2,\dots]\rightarrow[{\textcolor{blue}2},2,4,2,\dots]$$
$$[2,2,4,2,\dots]\rightarrow[{\textcolor{red}4},4,2,\dots]$$
$$[4,4,2,\dots]\rightarrow[{\textcolor{red}8},2,\dots]$$
形式化地，若 
$$k=\frac{a_i}{\operatorname{1b(a_i)}}=\frac{a_{i+1}}{\operatorname{1b(a_{i+1})}}$$
且 $a_i<a_{i+1}$，则从 $a_{i+1}$ 左侧加入 $a_i$ 需要的操作数为：
$$\frac{a_i-2a_{i+1}}{k}+1$$
同理，若 
$$k=\frac{a_i}{\operatorname{1b(a_i)}}=\frac{a_{i-1}}{\operatorname{1b(a_{i-1})}}$$
且 $a_i<a_{i-1}$，则从 $a_{i-1}$ 右侧加入 $a_i$ 需要的操作数为：
$$\frac{a_i-2a_{i-1}}{k}+1$$
综上，我们可以预处理数组中每个元素从左、右侧添加时所需要的操作次数最大值并维护其前、后缀和。然后枚举 $a_i$，取其前一段的和和后一段的和以及自己本身的最大操作次数的和。

形式化地，记 $\operatorname{pre}(a_i)$ 为到 $a_i$ 的前缀和，$\operatorname{suf}(a_i)$ 为到 $a_i$ 的后缀和。求是否存在 $a_i$ 满足：
$$\operatorname{pre}(a_{i})+\operatorname{suf}(a_{i})+\frac{a_i}{\operatorname{1b}(a_{i})}\ge k$$
# 正解
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int a[100005], b[100005], pre[100005], suf[100005]; // b 数组指 1b() 操作的值
void solve() {
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i], b[i] = a[i] / (a[i] & -a[i]); // x & -x 表示 x 取二进制下的为 $1$ 最低位
    memset(pre, 0, sizeof(pre)); // 记得初始化！
    memset(suf, 0, sizeof(suf));
    for (int i = 1; i < n; i++) {
        int x = a[i] / b[i];// 一般处理
        if (b[i] == b[i + 1] && a[i] > a[i + 1]) x = (a[i] - 2 * a[i + 1]) / b[i] + 1; // 特殊处理见上
        pre[i + 1] = pre[i] + x;
    }
    for (int i = n; i > 1; i--) { // 同上
        int x = a[i] / b[i];
        if (b[i] == b[i - 1] && a[i] > a[i - 1]) x = (a[i] - 2 * a[i - 1]) / b[i] + 1;
        suf[i - 1] = suf[i] + x;
    }
    for (int i = 1; i <= n; i++) {
        if (pre[i] + suf[i] + a[i] / b[i] >= k) {
            puts("YES");
            return;
        }
    }
    puts("NO");
}
signed main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0); // 输入输出优化
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}
```

---

## 作者：Zrnstnsr (赞：2)

非常有趣的题目，~~但是 pretest 弱的亲人都不认识了，赛时完全写错了还能过所有 pretest 也是绝了~~。

先考虑如何向数组中添加一个数，我们以 $12$ 为例，可以发现我们有如下的添加方法：

- $12$
- $6,6$
- $6,3,3$
- $3,3,3,3$

而 $3$ 是无法被分解的，因为不能用一个 $2$ 和一个 $1$ 合成一个 $3$。

我们按照树状数组的定义，定义 $\text{lb}(x)$ 为非负整数 $x$ 在二进制表示下最低位的 $1$ 所对应的值，也即 $x$ 的质因数分解中 $2$ 的贡献，比如 $\text{lb}(12)=4$，那么 $\text{lb}(x)$ 就代表着向**空数组**（注意这个限制）添加一个元素 $x$ 时，所需要操作次数的最大值。

那么答案是否就是 $k \le \sum_{i=1}^{n}\text{lb}(a_i)$ 呢？并不是。这是因为我们在数组的两端添加新元素时，会受到额外的限制。

举例来说，如果当前的数组是 $[6,\dots]$，要在左端添加一个 $48$。那么，左侧就不能再出现一个 $6$，否则数组就会变成 $[12,\dots]$。

因此，为了使得操作次数最大，我们必须在 $6$ 的左侧放一个 $12$ 把 $6$ 挡住：$[12,6,\dots]$，然后再补上剩下 $\frac{48-12}{3}=12$ 个 $3$。这一共需要 $12+1=13$ 次操作。

形式化地说，如果 $f:=\frac{a_i}{\text{lb}(a_i)} = \frac{a_{i+1}}{\text{lb}(a_{i+1})}$，并且 $a_i>a_{i+1}$，则向 $a_{i+1}$ 左侧添加 $a_i$ 至多需要 $\frac{a_i-2a_{i+1}}{f}+1$ 次操作。

类似地，如果 $f:=\frac{a_i}{\text{lb}(a_i)} = \frac{a_{i-1}}{\text{lb}(a_{i-1})}$，并且 $a_i>a_{i-1}$，则向 $a_{i-1}$ 右侧添加 $a_i$ 至多需要 $\frac{a_i-2a_{i-1}}{f}+1$ 次操作。

我们可以枚举最开始添加的数 $a_i$，那么就还有一个前缀 $[a_1,a_2,\dots,a_{i-1}]$ 和后缀 $[a_{i+1},a_{i+2},\dots,a_{n}]$ 需要添加到数组中，其中前缀必须向左端添加，后缀必须向右端添加。我们可以预处理数组中每个元素在左端、右端添加时所需要的操作次数最大值，然后用前缀和 $O(1)$ 地回答每个前缀、后缀的操作次数最大值之和。这样，我们就得到了一个 $O(n)$ 的算法。

代码：[321739196](https://codeforces.com/contest/2114/submission/321739196)

---

## 作者：未来姚班zyl (赞：1)

emm 只有左边加和右边加，可以直接这样：

枚举第一个形成的数，以其为分界点，所有都是类似将元素插入一个栈顶的操作（这样就没那么复杂）。

所以一个数 $x$ 的形成可能是直接形成，或靠着旁边已经形成完的数 $z$。

如果旁边没数，形成 $x$ 就一定是把 $x$ 的 $2$ 因子剃光，得到 $y$，不断加入 $y$，最终合并为 $x$。因为合并操作必须形如一个数 $k$ 不断乘 $2$。

否则旁边有一个 $z$，则合并的过程中靠着 $z$ 的位置不能为 $z$，如果过程中本来就没 $z$ 就不管了，否则靠着 $z$ 的部分必须从 $2z$ 开始，其余是一样的。

这样可以 $O(\log V)$ 模拟这个过程求出 $a_i$ 单独最多多少次操作，在 $a_{i-1}$ 后最多多少次操作，在 $a_{i+1}$ 后最多多少次操作。

我们是可以从最多次操作一步一步调整到一次操作的，这类似一个二叉树合并两个儿子，比如 $1+1=2$，那么干脆直接放一个 $2$，次数就 $-1$，从小到大依次这么做就可以成功调整。

枚举分界点后前缀和即可 $O(n)$ 计算答案。

找到 $x$ 的最大 $2$ 次幂因子可以直接用 $\operatorname{lowbit}(x)$ 做到 $O(1)$，从而使整个算法做到 $O(n)$（我懒得改代码了直接贴单 $\log V$）。


```cpp
#include<bits/stdc++.h>
#define ll long long
#define int ll
#define L x<<1
#define R x<<1|1
#define mid ((l+r)>>1)
#define lc L,l,mid
#define rc R,mid+1,r
#define Root 1,1,n
#define OK Ll<=l&&r<=Rr
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define repn(x) rep(x,1,n)
#define repm(x) rep(x,1,m)
#define pb push_back
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
#define E(x) for(auto y:p[x])
#define Pi pair<int,int>
#define ui unsigned ll
#define YY puts("Yes"),exit(0)
#define NN puts("No"),exit(0)
#define yy return puts("Yes"),void()
#define nn return puts("No"),void()
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(int x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
using namespace std;
const int N=1e6+5,M=1e6+5,inf=(1LL<<30)-1,mod=1e9+7;
const ll llf=1e18;
inline void add(int &a,int b){((a+=b)>=mod) and (a-=mod);}
inline int Add(int a,int b){return add(a,b),a;}
inline int mul(int a,int b){return 1LL*a*b%mod;}
inline void Mul(int &a,int b){a=mul(a,b);}
inline void red(int &a,int b){add(a,mod-b);}
inline int Red(int a,int b){return red(a,b),a;}
inline int qp(int a,ll b){if(!b)return 1;int c=qp(a,b>>1LL);Mul(c,c);if(b&1)Mul(c,a);return c;}
inline int INV(int x){return qp(x,mod-2);}
int n,a[N],k,le[N],re[N],pl[N],pr[N],c[N];
inline void Main(){
	n=read(),k=read();
	int S=0;
	repn(i)a[i]=read(),S+=a[i];
//	if(k==n)yy;
//	if(S<k)nn;
	repn(i){
		le[i]=re[i]=c[i]=1;
		int x=a[i];
		while(x%2==0)c[i]*=2,x/=2;
		x=a[i];
		while(x%2==0&&(i==1||x/2!=a[i-1]))le[i]*=2,x/=2;
		int res=a[i]-x,resc=le[i]-1;
		le[i]-=resc;
		while(x&&x%2==0)x/=2,resc*=2;
		le[i]+=resc;
		x=a[i];
		while(x%2==0&&(i==n||x/2!=a[i+1]))re[i]*=2,x/=2;
		res=a[i]-x,resc=re[i]-1;
		re[i]-=resc;
		while(x&&x%2==0)x/=2,resc*=2;
		re[i]+=resc;
		pl[i]=pl[i-1]+le[i],pr[i]=pr[i-1]+re[i];
	}
	int Mx=0;
	repn(x)Mx=max(Mx,c[x]+pr[x-1]+pl[n]-pl[x]);
	if(Mx>=k)yy;
	nn;
}
signed main(){
	int T=read();
	while(T--)Main();
	return 0;
}
```

---

## 作者：3a51_ (赞：1)

题外话：倒序开题花了将近 1h 没调出来 G，因为第二天还要二模就滚去睡觉了。第二天一早瞅了一眼直接把我的弱智错误瞪出来了。

---

对于 $a$ 的每一个数 $a_i$ 将其表示为 $b_i\times 2^{p_i}$，不难发现构造 $a_i$ 的每次操作加入的数一定是 $b_i\times 2^q$ 的形式，否则无法合并。

考虑答案的上界。每次至少加入 $b_i$，所以最多 $m=\sum 2^{p_i}$ 次操作。同时也发现，$\forall k<m$，都存在一种加入方式使得操作次数为 $k$。证明是简单的。

唯一的问题就是加入下一次的 $b_i$ 可能会和上一个已经构造完的数合并。考虑出现这种情况的充要条件：$\forall i$，如果 $b_i=b_{i-1}$ 且 $p_i>p_{i-1}$，那么构造 $p_i$ 的时候有可能和 $p_{i-1}$ 合并。为了避免这种情况，第一次加入至少需要加入 $b_i\times 2^{p_{i-1}+1}$。

剩下就不难了。枚举最开始构造的位置，由于一定按照顺序构造，可以直接前缀和后缀和维护左边、右边的贡献，取最大值与 $k$ 比较即可。

[Submission](https://codeforces.com/contest/2114/submission/321583567)。

---

## 作者：goodnever (赞：0)

## 题解：CF2114G Build an Array

很有趣的题。不过不排除是我今天刚开始复健才会想那么久。

有一个（我认为）重要的贪心条件在官方题解中没有给出证明，该贪心条件为：

> 若存在长度为 $k$ 的操作序列能合成目标数组，那么一定存在长度为 $k$ 的操作序列在能合成目标数组的同时，首先合成了长度为 $1$ 的子数组 $[a_i]$，然后逐步向外扩展并最终合成目标数组。

显然并非所有合法操作序列都满足后一个条件，很容易找到一个反例：$[]->[\red{2}]->[\red{1},2]->[1,2,\red{2}]->[1,\red{4}]$，在这个例子里，操作过程中并未先合成子数组 $[1]$ 或 $[4]$。

以下给出证明。

若存在长度为 $k$ 的操作序列能合成 $[a_1,a_2,\dots,a_{n-1},a_n]$，由于向左端添加数字的操作和向右端添加数字的操作互不影响（除非操作后数组合并至只剩一个元素），一定可以通过调换操作顺序（不改变操作总数），在过程中先合成子数组 $[a_2,\dots,a_{n-1},a_n]$ 或 $[a_1,a_2,\dots,a_{n-1}]$。

即，若存在长度为 $k$ 的操作序列能合成长度为 $n (n>1)$的数组 $a$，则一定存在长度为 $k$ 的操作序列能先合成长度为 $n-1$ 的数组 $b$（$b$ 是 $a$ 的子数组）再合成数组 $a$。

长度为 $1$ 的数组显然满足上述贪心条件。通过类似数学归纳法的思想，不难证明贪心条件成立。

---

