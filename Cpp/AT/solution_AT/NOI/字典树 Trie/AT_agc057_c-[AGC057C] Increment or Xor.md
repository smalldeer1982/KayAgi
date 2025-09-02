# [AGC057C] Increment or Xor

## 题目描述

给定一个正整数 $N$，以及一个长度为 $2^N$ 的数列 $A = (A_0, A_1, \ldots, A_{2^N-1})$。其中每个 $A_i$ 是 $0$ 到 $2^N-1$ 之间的整数，且对于 $i \neq j$，有 $A_i \neq A_j$。

你可以对数列 $A$ 进行以下两种操作：

- 操作 $+$：对所有 $i$，将 $A_i$ 变为 $(A_i + 1) \bmod 2^N$。
- 操作 $\oplus$：选择一个 $0$ 到 $2^N-1$ 之间的整数 $x$，对所有 $i$，将 $A_i$ 变为 $A_i \oplus x$。

这里的 $\oplus$ 表示按位异或（XOR）操作。

按位异或操作的定义如下：对于非负整数 $A, B$，$A \oplus B$ 的二进制表示中，每一位 $2^k$（$k \geq 0$）的数值，如果 $A$ 和 $B$ 的该位中只有一个为 $1$，则为 $1$，否则为 $0$。

例如，$3 \oplus 5 = 6$（二进制表示为：$011 \oplus 101 = 110$）。

你的目标是通过若干次操作，使得对于所有 $i$，都有 $A_i = i$。请判断能否达成目标。如果可以，请输出一种不超过 $10^6$ 次操作的方案。

## 说明/提示

### 约束条件

- $1 \leq N \leq 18$
- $0 \leq A_i \leq 2^N - 1$
- 对于 $i \neq j$，有 $A_i \neq A_j$

### 样例解释 1

通过输出的操作序列，数列 $A$ 的变化如下：

- 初始状态：$A = (5,0,3,6,1,4,7,2)$
- 操作 $+$：$A = (6,1,4,7,2,5,0,3)$
- 操作 $\oplus$（$x = 6$）：$A = (0,7,2,1,4,3,6,5)$
- 操作 $+$：$A = (1,0,3,2,5,4,7,6)$
- 操作 $\oplus$（$x = 1$）：$A = (0,1,2,3,4,5,6,7)$

### 样例解释 2

无论如何操作，都无法达成目标。

### 样例解释 3

无需任何操作即可达成目标。空行的输出与判题结果无关。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
5 0 3 6 1 4 7 2```

### 输出

```
Yes
4
-1 6 -1 1```

## 样例 #2

### 输入

```
3
2 5 4 3 6 1 0 7```

### 输出

```
No```

## 样例 #3

### 输入

```
3
0 1 2 3 4 5 6 7```

### 输出

```
Yes
0```

# 题解

## 作者：Mikazuki_Munechika (赞：9)

### AGC057C解题报告

我们设 $m=2^n$。

然后这里给个结论：合法的状态必须要满足 $a_i \equiv a_{i+\frac{m}{2}}\pmod {\frac{m}{2}}$。

这里解释一下为什么：

首先终点状态一定满足吧，然后我们讨论一下异或和加法的含义。

首先，异或，我们发现异或一个 $a \geq \frac{m}{2}$ 和异或 $a-\frac{m}{2}$ 是等价的，因为这个相当于将 $m$ 个元素两两配对，然后交换，配对 $x$ 和 $y$ 的原则是 $x\operatorname{xor}y=a$，不会改变下文所提到的两个等价类的内部元素的构成。

然后看 $ +1 $，首先看异或两个数等价的那个结论，这无疑就是说 $x$ 和 $y$ 能交换，当且仅当 $x \geq \frac{m}{2}$ 并且 $y \geq \frac{m}{2}$ 或者 $x < \frac{m}{2}$ 并且 $y < \frac{m}{2}$，那就相当于划分了两个等价类嘛其实，然后 $+1$ 只会改变两个元素的所属等价类，即 $m-1$ 和 $\frac{m}{2}-1$，其他元素的等价类都是没有变化的。

然后我们就发现，这两个操作无论如何都不会影响 $a_i \equiv a_{i+\frac{m}{2}}\pmod {\frac{m}{2}}$ 这一性质。

然后我们贪心一下，即我们要最后满足 $\forall i \in [0,\frac{m}{2}-1],a_i< \frac{m}{2}$，因为满足这个情况后，剩下的都是两个等价类的内部调整了，只需要异或就可以完成。于是先处理麻烦的部分。

然后我们就从前往后扫，从 $0$ 扫到 $\frac{m}{2}-1$，然后只要有 $a_i\geq \frac{m}{2}-1$，我们就让他跟 $m-1$ 交换，这个可以用两次异或实现，借助 $ \frac{m}{2}$ 作为跳板，先交换 $a_i$ 和 $\frac{m}{2}$，再交换 $\frac{m}{2}$ 和 $m-1$，由于异或有结合律，这两个操作可以合并。然后最后用一个整体 $+1$ 操作来使得这个 $m-1$ 变成 $0$，然后让 $a_i$ 跟 $m-1$ 交换只需要用到异或，而这个过程中我们发现实际上，只会让两个等价类内部的元素进行两两交换，并不会影响下标在 $[0,\frac{m}{2}-1]$ 之间的两种等价类的元素的数量。然后你可能有个问题，就是如果原来在 $[0,\frac{m}{2}-1]$ 有一个 $\frac{m}{2}-1$ 那 $ +1 $ 后不就增加了一个 $a_i \geq \frac{m}{2}$ 了？但是实际上并不用担心，因为保证了 $a_i \equiv a_{i+\frac{m}{2}}\pmod {\frac{m}{2}}$ 了，那么 $m-1$ 和 $\frac{m}{2}-1$ 必不可能同时在 $[0,\frac{m}{2}-1]$。

最后满足了 $\forall i \in [0,\frac{m}{2}-1],a_i< \frac{m}{2}$ 后，我们只需要对两个等价类内部进行一遍重排序就好了，由于有 $a_i \equiv a_{i+\frac{m}{2}}\pmod {\frac{m}{2}}$，我们只需要考虑一边即可。然后这个时候由于不需要改变等价类的数量了，也就是说这个时候只需要异或就够了！然后由于异或满足结合律，其实只需要异或一个数就可以了，这个数显然是 $a_0$，因为要让 $a_0$ 变成 $0$。

upd：上次没有传代码，想了想还是传上去吧，不过写的复杂度非常巨大，所以需要带火车头才能过，不过带火车头能过算是对这种新的思路的奖赏吧。
```cpp
#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
int main(){
    int N;
    cin>>N;
    int M=1<<N;
    vector<int> A(M);
    for(int i=0;i<M;i++) cin>>A[i];
    for(int i=0;i<M/2;i++){
        if(A[i]%(M/2)!=A[M/2+i]%(M/2)){
            return cout<<"No",0;
        }
    }
    vector<int> x;
    for (int i=0;i<M/2;i++){
        if (A[i]>=M/2){
            int a = (M-1)^A[i];
            x.push_back(a);
            x.push_back(-1);
            for (int j=0;j<M/2;j++){
                A[j]^=a;
                A[j]++;
            }
            A[i]=0;
        }
    }
    x.push_back(A[0]);
    for (int i=1;i<M/2;i++){
        A[i]^=A[0];
        if (A[i]!=i){
            return cout<<"No",0;
        }
    }
    int K=x.size();
    cout<<"Yes"<<endl;
    cout<<K<<endl;
    for (int i=0;i<K;i++){
      cout<<x[i]<<" ";
    }
    cout << endl;
    return 0;
}
```


---

## 作者：dehsirehC (赞：6)

考虑倒建 `01trie` ，即从低位往高位建，每个节点记录它的两个儿子代表的 $01$ 是否被反转。

由于最后一层的节点无法被反转，故接下来不考虑最后一层的节点，即去掉最后一层的节点。

发现操作一就是不断走 $1$ 的边，并反转路径上的节点，操作二则是反转若干层的节点。

容易从深到浅依次确定操作结束后每一个节点是否被反转。

发现操作一是反转从根到叶子的一条路径，即一个叶子节点因操作一被反转，则它的祖先都会被反转。

由于一个非叶子节点子树内包含的叶子节点数为偶数，故它被操作一反转次数的奇偶性也可以被确定。

这样一来，每一层节点最后被操作二反转次数的奇偶性也可以得到了（不包含最后一层）。

考虑构造，通过一次操作二可以指定任意一个叶子节点进行操作一，这样就可以任意反转叶子节点了。

至此，直接实现即可做到不超过 $2^n+1$ 次操作，总时间复杂度 $O(2^nn)$ 。

考虑是否能将操作次数的常数做得更好，设共有 $x$ 个叶子节点需要被反转。

将所有无需被反转的叶子节点通过操作一反转，最后进行一次操作二，即可让 $x$ 变为 $2^{n-1}-x$ 。

特别的，若最开始时无需进行操作二也可以指定一个我们想反转的叶子节点，则可以减少一次操作。

至此，合理选择最后一次操作二是否反转最后一层的节点即可将操作次数做到不超过 $2^{n-1}$ 次。

因为反转与不反转两种选择操作次数之和为 $2^n+1$ ，故两者的较小值必定不超过 $2^{n-1}$ 。

[代码](https://atcoder.jp/contests/agc057/submissions/50664752)

值得一提的是，我猜测这道题最坏情况下的最优操作次数就是 $2^{n-1}$ 次。

~~我已经想到了一个绝妙的证法，但是这里地方太小写不下。~~ 如果有人知道如何证明，可以教教我。

---

## 作者：Rainbow_qwq (赞：5)

首先想一想什么情况下无解，似乎不太会做。于是尝试打表，看一看等价类个数来猜什么情况有解。

通过打表发现了一个神奇的事实，如果前 $2^{n-1}$ 个数的最高位都为 $0$，那么有解当且仅当可以只用 XOR 操作来达成目标。证明不太会证。

于是目标变成把前 $2^{n-1}$ 个数最高位变成 $0$，翻转一个数的最高位可以全局 XOR 一下把这个数变成全 $1$，然后加 $1$。

于是只需要支持全局 XOR 一个数，全局加 $1$，以及查询一个位置的值。这个很经典，可以倒着建 Trie 维护，不会的话可以见[这题](https://www.luogu.com.cn/problem/P6018)，这里不赘述。

把 $2^{n-1}$ 个数翻好最高位，最后再进行一次 XOR 就行了，操作次数最多 $2^n+1$ 次。


---

## 作者：DaiRuiChen007 (赞：3)

[Problem Link](https://www.luogu.com.cn/problem/AT_agc057_c)

**题目大意**

> 给定一个 $0\sim 2^n-1$ 的排列 $p_i$，每次可以把所有数 $+1$ 后对 $2^n$ 取模或每个数异或上 $x$，构造一种操作方法，使得 $p_i=i$。
>
> 数据范围：$n\le 18$。

**思路分析**

记 $m=2^{n-1}$，那么一个排列能还原的一个必要条件是 $p_{i}\equiv p_{i+m}\pmod m$，即 $p_i$ 与 $p_{i+m}$ 的低 $n-1$ 位相同。

可以倒推证明：最终排列满足该性质，且对于两个低 $n-1$ 位相同的数，全体异或或全体 $-1$ 后低 $n-1$ 位依然相同。

那么说明原本的排列也必须满足 $p_{i}\equiv p_{i+m}\pmod m$。

假如 $p_0\sim p_{m-1}$ 的最高位都是 $0$，那么唯一的还原方法就是给每个数异或上 $p_0$，可以证明这种情况下 $+1$ 操作并没有用。

那么我们只要清空每个 $p_0\sim p_{m-1}$ 的最高位，假如 $p_i$ 最高位是 $1$，我们可以把每个数异或上 $\overline {p_i}$ 使得 $p_i=2^n-1$ 然后全体 $+1$ 即可，此时其他 $p_0\sim p_{m-1}$ 的低 $n-1$ 异或后都不可能是 $m-1$（另一个低位是 $m-1$ 的元素是 $p_{i+m}$），然后不断操作就能得到答案，操作数不超过 $2^n+1$。

只需要一个数据结构维护全局 $+1$，全局异或和单点查值，用 01-Trie 维护，全局加一相当于把一条链上的点交换左右儿子。

时间复杂度 $\mathcal O(n2^n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1<<18],n,N;
int p[1<<18],q[1<<18],tg[18]; //ds
void init() {
	for(int i=0;i<N;++i) {
		for(int k=0;k<n;++k) p[i]=(p[i]<<1)|(a[i]>>k&1);
		p[i]|=N;
	}
}
void rev(int x) { //^x
	for(int i=0;i<n;++i) if(x>>i&1) tg[i]^=1;
}
void add() { //+1
	for(int i=0,u=1;i<n;++i) q[u]^=1,u=u<<1|(tg[i]^q[u]);
}
int qry(int u) {
	int y=0,x=p[u];
	for(int i=n-1;~i;--i) {
		y|=((x&1)!=(q[x>>1]^tg[i]))<<i,x>>=1;
	}
	return y;
}
vector <int> opr;
signed main() {
	scanf("%d",&n),N=1<<n;
	int m=N/2;
	for(int i=0;i<N;++i) scanf("%d",&a[i]);
	init();
	for(int i=0;i<m;++i) if(a[i]%m!=a[i+m]%m) return puts("No"),0;
	for(int i=0;i<m;++i) {
		int x=qry(i);
		if(x&m) {
			opr.push_back((N-1)^x),opr.push_back(-1);
			rev((N-1)^x),add();
		}
	}
	opr.push_back(qry(0)),rev(qry(0));
	for(int i=0;i<N;++i) if(i!=qry(i)) return puts("No"),0;
	printf("Yes\n%d\n",(int)opr.size());
	for(int i:opr) printf("%d ",i); puts("");
	return 0;
}
```

---

## 作者：向晚大魔王 (赞：3)

## 题解
考虑 $+1$ 和 $\oplus\ x$ 这两个操作，我们在数据结构题里见过他们的组合。

具体来说，就是如果我们从反向建 trie，$+1$ 等价于翻转最左边的一条链，$\oplus\ 2^k$ 等价于翻转某一层。

因此我们直接维护整棵树，这棵树下标为 $x$ 的节点代表序列上满足 $a_t=x$ 的 $t$。

然后我们发现翻转一个叶子节点一定会翻转它的所有祖先，所以只要翻转所有叶子节点然后判断能不能通过翻转若干层来归位整棵树即可。

操作次数不会超过 $2^{N+1}+1$。
## 代码
```cpp
//不回家了，我们去鸟巢！
#include<bits/stdc++.h>
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int n=read(),N=1<<n;
int val[1<<20];
int mn[1<<20],mx[1<<20];
bool rev[1<<20],tgt[1<<20],tag[20];
int arr[1<<20],R[1<<20],c;
vector<int> vec;
void build(int x,int d)
{
	if(d==n)
	{
		val[x]=arr[R[c++]],mn[x]=mx[x]=R[val[x]];
		return ;
	}
	build(x<<1,d+1),build((x<<1)+1,d+1);
	mn[x]=min(mn[x<<1],mn[(x<<1)+1]),
	mx[x]=max(mx[x<<1],mx[(x<<1)+1]);
	if(mx[x]-mn[x]+1!=(1<<(n-d))) puts("No"),exit(0);
	if(mn[x<<1]>mn[(x<<1)+1]) tgt[x]=1;
	return ;
}
void process(int x)
{
	int val=0;
	for(int d=n-1,i=x,t; d>0;)
	{
		t=i&1,i>>=1,--d;
		if(rev[i]^tag[d]^t^1)
			tag[d]^=1,val^=(1<<d);
	}
	vec.push_back(val),vec.push_back(-1);
	for(int i=1,d=0; d<n; ++d)
		rev[i]^=1,i=(i<<1)+(rev[i]^tag[d]);
	return ;
}
void dfs(int x,int d)
{
	if(d==n-1)
	{
		if((rev[x]^tag[d])!=tgt[x]) process(x);
		return ;
	}
	dfs(x<<1,d+1),dfs((x<<1)+1,d+1);
	return ;
}
int shift=0;
void adjust(int x,int d)
{
	if((rev[x]^tag[d])!=tgt[x])
		shift^=(1<<d),tag[d]^=1;
	if(d==n-1) return ;
	adjust(x<<1,d+1),adjust((x<<1)+1,d+1);
	return ;
}
bool chk(int x,int d)
{
	if(d==n) return 1;
	if(!chk(x<<1,d+1)||!chk((x<<1)+1,d+1)) return 0;
	if((rev[x]^tag[d])!=tgt[x]) return 0;
	return 1;
}
signed main()
{
	for(int i=0; i<N; ++i)
		for(int j=0; j<n; ++j)
			if((i>>j)&1) R[i]+=1<<(n-1-j);
	for(int i=0; i<N; ++i) arr[read()]=i;
	build(1,0),dfs(1,0),adjust(1,0),vec.push_back(shift);
	if(!chk(1,0)) puts("No"),exit(0);
	puts("Yes");
	assert((int)vec.size()<=1000000);
	printf("%d\n",(int)vec.size());
	for(int i:vec) printf("%d ",i);
	puts("");
	return 0;
}
```

---

## 作者：Lgx_Q (赞：0)

由于有 $+1$ 操作，考虑反着建立 01-trie，即以最低位作为第一个分支。这样 $+1$ 操作相当于对最右边的一条链上每个点执行左右儿子交换。

考虑 trie 树上每个叶子挂着对应数值在 $A$ 中的位置，我们的目标状态为：每个叶子挂着的数等于对应数值。

不管是异或还是 $+1$ 操作，都只能交换左右儿子，所以无解的判定是容易的：进行一次 DFS，判断当前点 $u$ 与目标状态的 $v$ 子树是否合法，每次判断 $u$ 的子树中最左边的叶子在 $v$ 的左子树还是右子树，然后递归判定。

这样一遍 DFS 我们还能顺便求出 $t_u=0/1$ 表示为了到达目标状态，点 $u$ 是否需要交换左右儿子。

为了方便表述，我们以“$t_u$ 的改变”来代替点 $u$ 交换左右儿子的操作。那么，我们的目标是把所有点的 $t$ 变为 $0$。

我们现在有两种方法：

+ 异或一个数，使得同一层内的点 $t$ 值全部取反，或全都不改变。

+  $+1$，使得最右边一条链上所有点的 $t$ 值全部取反。

注意到对于一条链，如果我们通过异或操作把它“旋转”到最右边，进行一次 $+1$ 操作，再旋转回来，等价于我们可以令这条链上的 $t$ 值全部取反。

所以我们思考操作若干条链来达成目标。

但是不一定有解。在操作之前，我们可以先异或一个值 $v$，使得一些层的 $t$ 值取反。

具体的，枚举最后一层（不是叶子，是叶子上面的一层）是否先提前取反，然后依次往上枚举每一层。

设 $d_u$ 表示被链覆盖的次数的奇偶性，有 $d_u = d_{lson(u)}\operatorname{xor} d_{rson(u)}$，合法的条件为 $d_u\operatorname{xor} t_u = 0$。

如果该层全部点都满足 $d_u\operatorname{xor} t_u = 1$，那么先提前把这一层所有 $t$ 取反。

然后这题就做完了，操作次数显然远远小于 $10^6$。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned ll
#define fi first
#define se second
#define pir pair <ll, ll>
#define mkp make_pair
#define pb push_back
using namespace std;
const ll maxn = 3e5 + 10, mod = 1e9 + 7;
ll n, a[maxn], b[maxn], ans[maxn << 2], len;
ll trie[maxn * 18][2], tot = 1, t[maxn * 18], fa[maxn * 18];
vector <ll> vec[20];
void dfs(ll bit, ll u, ll v, ll uw, ll vw) {
	if(bit == n) {
		if(b[uw] != vw) {
			puts("No");
			exit(0);
		} return;
	}
	if(b[uw] & (1 << bit)) {
		dfs(bit + 1, trie[u][0], trie[v][1], uw, vw | (1 << bit));
		dfs(bit + 1, trie[u][1], trie[v][0], uw | (1 << bit), vw);
		t[u] = 1;
	} else {
		dfs(bit + 1, trie[u][0], trie[v][0], uw, vw);
		dfs(bit + 1, trie[u][1], trie[v][1], uw | (1 << bit), vw | (1 << bit));
	}
}
ll tag;
ll query(ll u) {
	ll val = 0;
	for(ll i = n - 2; ~i; i--) {
		val |= (trie[fa[u]][1 ^ ((tag >> i) & 1)] == u) << i;
		u = fa[u];
	} return val;
}
void add1() {
	ll p = 1;
	for(ll i = 0; i < n; i++) {
		swap(trie[p][0], trie[p][1]);
		p = trie[p][(tag >> i) & 1];
	}
}
ll msk, d[maxn * 18], ok;
int main() {
	scanf("%lld", &n); vec[0].pb(1);
	for(ll i = 0; i < (1 << n); i++) {
		scanf("%lld", a + i); b[a[i]] = i;
		ll p = 1;
		for(ll j = 0; j < n; j++) {
			ll c = (a[i] >> j) & 1;
			if(!trie[p][c]) {
				trie[p][c] = ++tot;
				vec[j + 1].pb(tot);
				fa[tot] = p;
			}
			p = trie[p][c];
		}
	}
	dfs(0, 1, 1, 0, 0);
	for(ll i = 0; i < 2; i++) {
		msk = (i << n - 1), ok = 1;
		for(ll j: vec[n - 1]) d[j] = t[j] ^ i;
		for(ll j = n - 2; ~j; j--) {
			ll x = 0, gd = 0;
			for(ll k: vec[j]) {
				d[k] = t[k] ^ x;
				if(d[k] ^ d[trie[k][0]] ^ d[trie[k][1]]) {
					if(gd) {
						ok = 0;
						break;
					}
					x = 1, d[k] ^= 1;
				}
				gd = 1;
			}
			msk |= (x << j);
			if(!ok) break;
		}
		if(!ok) continue;
		ans[++len] = tag = msk;
		for(ll j: vec[n - 1])
			if(d[j]) {
				ll val = query(j);
				val ^= (1 << n - 1) - 1;
				ans[++len] = val, tag ^= val;
				add1(), ans[++len] = -1;
			}
		ans[++len] = tag ^ msk;
		puts("Yes");
		printf("%lld\n", len);
		for(ll i = 1; i <= len; i++)
			printf("%lld ", ans[i]);
		return 0;
	}
	puts("No");
	return 0;
}
```

---

