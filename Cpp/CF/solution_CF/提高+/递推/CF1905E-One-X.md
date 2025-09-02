# One-X

## 题目描述

In this sad world full of imperfections, ugly segment trees exist.

A segment tree is a tree where each node represents a segment and has its number. A segment tree for an array of $ n $ elements can be built in a recursive manner. Let's say function $ \operatorname{build}(v,l,r) $ builds the segment tree rooted in the node with number $ v $ and it corresponds to the segment $ [l,r] $ .

Now let's define $ \operatorname{build}(v,l,r) $ :

- If $ l=r $ , this node $ v $ is a leaf so we stop adding more edges
- Else, we add the edges $ (v, 2v) $ and $ (v, 2v+1) $ . Let $ m=\lfloor \frac{l+r}{2} \rfloor $ . Then we call $ \operatorname{build}(2v,l,m) $ and $ \operatorname{build}(2v+1,m+1,r) $ .

So, the whole tree is built by calling $ \operatorname{build}(1,1,n) $ .

Now Ibti will construct a segment tree for an array with $ n $ elements. He wants to find the sum of $ \operatorname{lca}^\dagger(S) $ , where $ S $ is a non-empty subset of leaves. Notice that there are exactly $ 2^n - 1 $ possible subsets. Since this sum can be very large, output it modulo $ 998\,244\,353 $ .

 $ ^\dagger\operatorname{lca}(S) $ is the number of the least common ancestor for the nodes that are in $ S $ .

## 说明/提示

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1905E/fbb65ae036ad668eae2530f36a15f5bf19bb463d.png)In the first test case:

Let's look at all subsets of leaves.

- $ \operatorname{lca}(\{2\})=2 $ ;
- $ \operatorname{lca}(\{3\})=3 $ ;
- $ \operatorname{lca}(\{2,3\})=1 $ .

Thus, the answer is $ 2+3+1=6 $ .

In the second test case:

Let's look at all subsets of leaves.

- $ \operatorname{lca}(\{4\})=4 $ ;
- $ \operatorname{lca}(\{5\})=5 $ ;
- $ \operatorname{lca}(\{3\})=3 $ ;
- $ \operatorname{lca}(\{4,5\})=2 $ ;
- $ \operatorname{lca}(\{4,3\})=1 $ ;
- $ \operatorname{lca}(\{5,3\})=1 $ ;
- $ \operatorname{lca}(\{4,5,3\})=1 $ ;

Thus, the answer is $ 4+5+3+2+1+1+1=17 $ .

## 样例 #1

### 输入

```
5
2
3
4
5
53278```

### 输出

```
6
17
36
69
593324855```

# 题解

## 作者：xlpg0713 (赞：8)

哎呀我靠这题。

自己第一道赛时做出来的 E。

以下题解中；$mid$ 指 $\lfloor \frac{l+r}{2}\rfloor$ 左儿子对应的区间是 $[l,mid]$，右儿子是 $[mid+1,r]$。

## 题意：
对 $[1,n]$ 建一棵线段树，左儿子编号为 $p\times 2$，右儿子是 $p\times 2+1$。定义一个非空点集 $S$ 的价值是线段树上 $S$ 对应的所有叶子节点的 $lca$ 的编号。求出所有可能的点集的价值和。
## 题解：
考虑线段树上一个节点成为答案的条件。设其对应区间 $[l,r]$，显然，当且仅当区间 $[l,mid]$ 和 $[mid+1,r]$ 中至少一个被选，其余的一个不被选，证明显然，感性理解即可。因此方案数 $f(l,r)$ 为 $(2^{mid-l+1}-1)\times(2^{r-mid}-1)$。

来证明一个结论：线段树上深度相同的一层区间长度最多有两种。

显然长为 $len$ 的区间左右儿子长度为 $\lceil \frac{len}{2} \rceil$ 与 $\lfloor \frac{len}{2} \rfloor$ 在根节点上，这两个值最多不相差 $1$。又显然：前者除二上取整与后者除二下取整不超过一。归纳可证结论成立。

结论已证，考虑这个问题的贡献形式。点权为 $p$ 长度为 $o$ 的区间，价值是 $p\times f(o)$ 后者只和长度有关，在这个上面搞点小计谋。维护一层上，长为 $o$ 的区间的标号和与区间数量，答案是易于统计的。

至于转移，显然到下一层，左儿子的区间和是当前标号和乘二，右儿子是当前标号和乘二加上区间数，显然正确。	

因为已证一层最多两种长度，因此复杂度正确 $O(\log^2n)$ 两只一只来自线段树有 $\log$ 层，一只是算幂次的快速幂。

图方便用了 $map$，但是 $\log_22=1$ 当常数了。

取模要取干净，两发罚时警示后人。

```cpp
#include<iostream>
#include<map>
#include<cmath>
#define int long long
int n, t, p = 998244353;
std::map<int, std::pair<int, int>>mp[100];
inline int qp(int a, int b){int r = 1;
    for(; b; b >>= 1, a = a * a % p)
        b & 1 ? r = a * r % p : 0; return r;
}
signed main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);std::cout.tie(0);
    std::cin >> t;
    while(t--){
        int rs = 0;
        std::cin >> n; int lg = std::__lg(n) + 3;
        for(int i = 1; i <= lg; i++) mp[i].clear();
        mp[1][n] = std::make_pair(1, 1);
        for(int i = 1; i <= lg; i++)
        for(auto [v, o]:mp[i]){
            auto [sm, ct] = o;
            if(v == 1){(rs += sm) %= p; continue;}
            int l = (v + 1) / 2, r = v - l;
            (rs += sm * (qp(2, l) - 1) % p * (qp(2, r) - 1) % p) %= p;
            (mp[i + 1][l].first += sm * 2) %= p; (mp[i + 1][l].second += ct) %= p;
            (mp[i + 1][r].first += sm * 2 + ct) %= p; (mp[i + 1][r].second += ct) %= p;
        }
        std::cout << rs << '\n';
    }
}
```

---

## 作者：Exp10re (赞：3)

在翻名字带线段树的题目的时候发现的题。

这道题目给出的线段树实现方法和我的一模一样。

## 解题思路

考虑一个编号为 $u$ 的节点，控制的区间为 $[l,r]$，记 $len=r-l+1$（以下简记为节点长度），其对答案的贡献为：

$$u\times (2^{\frac {len+1} {2}}-1)\times (2^{\frac {len} {2}}-1)$$

原理是在该区间 $[l,r]$ 的左区间 $[l,mid]$ 以及右区间 $[mid+1,r]$ 中各取至少一个，其 $\operatorname{lca}$ 即为 $u$。

特殊的，若 $len=1$，其贡献就是 $u$。

注意到 $len$ 一定时 $(2^{\frac {len+1} {2}}-1)\times (2^{\frac {len} {2}}-1)$ 一定，那么考虑求出所有长度为 $len$ 的节点编号和，记为 $val_{len}$，那么 $val_{len}\times (2^{\frac {len+1} {2}}-1)\times(2^{\frac {len} {2}}-1)$ 即为长度为 $len$ 的所有节点对答案的贡献。

再注意到线段树建树后节点的不同区间长度个数规模是 $O(\log n)$ 的，那么枚举不同长度递推即可。

具体而言：统计长度为 $len$ 的节点编号和 $val_{len}$，长度为 $len$ 的节点数量 $cnt_{len}$，那么长度为 $len$ 的节点递归产生长度更小的节点贡献如下：

$$\begin{aligned}cnt_{\frac {len+1} {2}}&\leftarrow cnt_{len} \\
cnt_{\frac {len} {2}}&\leftarrow cnt_{len} \\
val_{\frac {len+1} {2}}&\leftarrow val_{len}\times 2 \\
val_{\frac {len} {2}}&\leftarrow val_{len}\times 2+cnt_{len} \\
\end{aligned}$$

原理是对于一个节点的左儿子编号为 $u\times 2$，右儿子编号为 $u\times 2 +1$。

用 multiset 进行递推即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long Moder_=998244353;
priority_queue<long long> dn;
map<long long,long long> cnt,val,vis;
long long mult(long long ta,long long tb,long long tc)
{
	ta=((ta%Moder_)*(tb%Moder_))%Moder_;
	ta=(ta*(tc%Moder_))%Moder_;
	return ta;
}
long long poww(long long ta,long long tb)
{
	long long ans=1;
	while(tb>0)
	{
		if(tb&1)
		{
			ans=(ans*ta)%Moder_;
		}
		ta=(ta*ta)%Moder_;
		tb/=2;
	}
	return ans;
}
void work()
{
	while(!dn.empty())
	{
		dn.pop();
	}
	cnt.clear();
	val.clear();
	vis.clear();
	long long n,ans=0,t,l,r;
	scanf("%lld",&n);
	dn.push(n);
	cnt[n]=1;
	val[n]=1;
	vis[n]=1;
	while(!dn.empty())
	{
		t=dn.top();
		vis[t]=0;
		dn.pop();
		l=(t+1)/2;
		r=t/2;
		if(t==1)
		{
			ans=(ans+val[t])%Moder_;
		}
		else
		{
			ans=(ans+mult(val[t],poww(2,l)-1,poww(2,r)-1))%Moder_;
		}
		cnt[l]=(cnt[l]+cnt[t])%Moder_;
		val[l]=(val[l]+val[t]*2)%Moder_;
		cnt[r]=(cnt[r]+cnt[t])%Moder_;
		val[r]=(val[r]+val[t]*2+cnt[t])%Moder_;
		if(vis[l]!=1&&t!=1)
		{
			dn.push(l);
			vis[l]=1;
		}
		if(vis[r]!=1&&t!=1)
		{
			dn.push(r);
			vis[r]=1;
		}
	}
	printf("%lld\n",ans);
	return;
}
int main()
{
	long long T;
	scanf("%lld",&T);
	while(T--)
	{
		work();
	}
}
```

---

## 作者：MiniLong (赞：3)

简单计数题。

先考虑暴力做法，对于每个点统计。

记 $num_u$ 为长度为 $u$ 的节点所在子树的叶子个数，对于点 $x$，$ls,rs$ 为左右儿子，那么点 $x$ 的贡献就是 $(2^{num_{len_{x}}} - 2^{num_{len_{ls}}} - 2^{num_{len_{rs}}} +1) \times x$。

考虑到线段树结构有很多重复，那么直接来记搜。

对于每个相同的长度 $len$，所对应的树的结构相同，但是节点编号不同。但由于线段树的节点编号有依赖性，即儿子节点都是 $2\times x,2\times x+1$，所以只需管根节点的编号。我们记 $f(x,len)$ 为根节点为 $x$ 且区间长度为 $len$ 的线段树答案。

- $len$ 不是第一次出现时，那么我现在已经知道 $f(y,len),y\neq x$ 了，只需把所有节点编号的贡献更换。在以 $x$ 为根的子树内的点编号为 $2x,2x+1,4x,4x+1,4x+2,4x+3$ 等等，都可以表示为 $t \cdot x +b$ 的形式，且 $t$ 为这个节点在 $x$ 为根子树内的深度。那么就很好处理了，一棵 $y$ 子树答案是 $\sum (t \cdot y +b) \times (2^{num_{len_{t \cdot y +b}}} - 2^{num_{len_{ls}}} - 2^{num_{len_{rs}}} +1)$，后面那一坨先令它为 $p_{t \cdot y + b}$。令 $k = x-y$，那么 $f(x,len)=\sum (t\cdot(y+k)+b)\cdot p_{t \cdot (y+k)+b}$，由于 $p_y$ 之和长度有关，和节点编号无关，所以 $f(x,len)=\sum (t\cdot y+b)\cdot p_{t \cdot y +b} + k \cdot p_{t\cdot y +b} \cdot t = f(y,len)+k \times \sum t \cdot p_{t \cdot y + b}$。后面那个东西很好求，也之和长度有关，令它为 $g(y)$，那么 $f(x,len)=f(x,len)+g(y)\times (x-y)$。


- $len$ 第一次出现时，$ f(x,len)=f(ls_x,len_{ls})+f(rs_x,len_{rs})+(2^{num_x} - 2^{num_{ls}} - 2^{num_{rs}} +1) \times x $，$g(x)=2\times(g(ls)+g(rs)) + (2^{num_{len_{x}}} - 2^{num_{len_{ls}}} - 2^{num_{len_{rs}}} +1)$。


---

## 作者：Lu_xZ (赞：3)

考虑在 $n$ 个节点的树中，树根作为 $lca$ 对答案的贡献，显然就是在左子树的叶子中选出一个非空集的方案乘上右子树的方案。
$$
w(n, id) = id \cdot (2 ^ {L\_Leaf} - 1) \cdot (2 ^ {R\_Leaf} - 1)
$$
进而得到一个 $O(N)$ 的 $dp$，其中 $ls =  \lceil \dfrac{n}{2} \rceil$，$rs = \lfloor \dfrac{n}{2} \rfloor$。
$$
dp(n, id) = w(n, id) + dp(ls, 2\cdot id) +  dp(rs, 2\cdot id + 1)
$$
观察状态参数，可以发现在一次求解中 $id$ 有 $O(N)$ 个，而 $n$ 只有 $O(\log N)$ 个，一个直观的想法是把 $id$ 从状态方程中剥离出去。

不妨手玩一下这个式子。
$$
\begin{aligned}
dp(n, id) &= w(n, id) + dp(ls, 2\cdot id) +  dp(rs, 2\cdot id + 1) \\
           &= t(n) \cdot id + dp(ls, 2\cdot id) +  dp(rs, 2\cdot id + 1)  \\
           &= t(n) \cdot id + t(ls) \cdot 2\cdot id  +  t(rs) \cdot (2\cdot id + 1) + (dp \ldots)  \\
           &= (t(n) + 2 \cdot t(ls) +  2 \cdot t(rs) + 4 \cdot \ldots) \cdot id + (t(rs) + \ldots)
\end{aligned}
$$
能够得到整个状态方程为 $id$ 的一次函数，只需维护 $k(n)$ 和 $b(n)$ 就好了。

即
$$dp(n, id) = k(n) \cdot id + b(n)$$

由于
$$
\begin{aligned}
dp(n, id)  &= t(n) \cdot id + dp(ls, 2\cdot id) +  dp(rs, 2\cdot id + 1)  \\
           &= t(n) \cdot id + k(ls) \cdot 2\cdot id  + b(ls)  + k(rs) \cdot (2\cdot id + 1) + b(rd)
\end{aligned}
$$
所以

$$k(n) = t(n) + 2 \cdot k(ls) + 2 \cdot k(rs)$$
$$b(n) = b(ls) + k(rs) + b(rs)$$

```c++
map<ll, pll> mp;

pll calc(ll n) {
	if(mp.find(n) != mp.end()) return mp[n];
	auto [lk, lb] = calc((n + 1) / 2); 
	auto [rk, rb] = calc(n / 2);
	ll t = (q_pow(2, (n + 1) / 2) - 1) * (q_pow(2, n / 2) - 1) % P;
	ll k = (t + 2 * lk + 2 * rk) % P;
	ll b = (lb + rk + rb) % P;
	/*
	  f[n][id] = t * id + f[ls][lsid] + f[rs][rsid]
	 */
	return mp[n] = {k % P, b % P};
}

void solve() {
	ll n;
	cin >> n;
	auto [k, b] = calc(n);
	cout << (k + b) % P << '\n';
}

int main() {
	int T; cin >> T;
	mp[1] = {1, 0};
	while(T --) solve();
	return 0;
}
```

ccf 赶紧支持 `c++17`。

---

## 作者：Xy_top (赞：2)

一眼秒掉的 *2400。

不一样的做法。

正难则反，考虑对于每一个节点统计作为 LCA 的次数。

如果该节点 $n$ （不为叶子节点）的左子树中叶子节点的个数为 $l$，另一个为 $r$，那么来考虑什么时候能使 $n$ 成为 LCA。显然，左右都必须要选一个，故方案数为 $(2^l-1)\times (2^r-1)$。

于是便有了和建线段树的函数长的差不多的做法。

```cpp
void fun (int l, int r, int k) {
	if (l == r) {
		ans = (ans + k) % mod;
		return;
	}
	int mid = l + r >> 1;
	ans = (ans + k * (q_pow (2, mid - l + 1) - 1) % mod * (q_pow (2, r - mid) - 1) ) % mod;
	fun (l, mid, k << 1);
	fun (mid + 1, r, k << 1 | 1);
}
```


这一题还要让我们乘以节点的编号，但当子树大小相同时，不乘编号是一样的，于是可以用乘法分配律把编号提出来，里面是 $(2^l-1)\times (2^r-1)$。

所以只有编号的和以及大小是重要的，在 ``map`` 中存储这两个东西，然后发现走左右子树的时候右子树编号的和难以得到，还要再存一个 ``map`` 记录子树大小对应的个数，这也很好维护，具体看代码。

代码实现用了两个 ``map``，写得很丑见谅。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
#define For(i, a, b) for (int i = (a); i <= (b); i ++)
#define foR(i, a, b) for (int i = (a); i >= (b); i --)
using namespace std;
int n, ans;
map <int, int> m1, m2;
map <int, int> cnt1, cnt2;
const int mod = 998244353;
int q_pow (int x, int y) {
	if (y == 0) return 1;
	if (y & 1) return x * q_pow (x * x % mod, y >> 1) % mod;
	return q_pow (x * x % mod, y >> 1);
}
void solve () {
	ans = 0;
	m1.clear ();
	m2.clear ();
	cnt1.clear ();
	cnt2.clear ();
	cin >> n;
	m1[n] = 1;
	cnt1[n] = 1;
	For (i, 1, 65) {
		if (!m1.empty () ) {
			for (auto p : m1) {
				//p.second 为节点编号之和
				//1 ~ p.first
				int mid = p.first + 1 >> 1;
				ans = (ans + p.second * (q_pow (2, mid) - 1) % mod * (q_pow (2, p.first - mid) - 1) % mod) % mod;
				if (mid - 1) {
					m2[mid] = (m2[mid] + p.second * 2) % mod;
					cnt2[mid] = (cnt2[mid] + cnt1[p.first]) % mod;
				} else ans = (ans + p.second * 2) % mod;
				if (p.first - mid - 1) {
					m2[p.first - mid] = (m2[p.first - mid] + p.second * 2 + cnt1[p.first]) % mod;
					cnt2[p.first - mid] = (cnt2[p.first - mid] + cnt1[p.first]) % mod;
				} else ans = (ans + p.second * 2 + cnt1[p.first]) % mod;
			}
			m1.clear ();
			cnt1.clear ();
		} else {
			for (auto p : m2) {
				//p.second 为节点编号之和
				//1 ~ p.first
				int mid = p.first + 1 >> 1;
				ans = (ans + p.second * (q_pow (2, mid) - 1) % mod * (q_pow (2, p.first - mid) - 1) % mod) % mod;
				if (mid - 1) {
					m1[mid] = (m1[mid] + p.second * 2) % mod;
					cnt1[mid] = (cnt1[mid] + cnt2[p.first]) % mod;
				} else ans = (ans + p.second * 2) % mod;
				if (p.first - mid - 1) {
					m1[p.first - mid] = (m1[p.first - mid] + p.second * 2 + cnt2[p.first]) % mod;
					cnt1[p.first - mid] = (cnt1[p.first - mid] + cnt2[p.first]) % mod;
				} else ans = (ans + p.second * 2 + cnt2[p.first]) % mod;
			}
			m2.clear ();
			cnt2.clear ();
		}
	}
	cout << ans;
}
signed main () {
	int _ = 1;
	cin >> _;
	while (_ --) {
		solve ();
		cout << '\n';
	}
	return 0;
}	
```


---

## 作者：happybob (赞：2)

先考虑 $n$ 比较小的时候怎么做。

非常显然地，按照线段树建树，枚举每个点作为 LCA 的答案。假设当前节点 $u$，对应区间 $[l,r]$，区间长度 $len = r-l+1$，那么对答案的贡献为 $u \times (2^{\lceil \frac{len}{2}\rceil} - 1) \times (2^{\lfloor \frac{len}{2}\rfloor} - 1)$，即在左右子树的叶子节点中各选若干，且保证左右两侧都至少选了一个点。答案即为每个点贡献之和。

上述的朴素做法复杂度为 $O(n)$。通常在线段树或者完全二叉树之类的比较优秀的树形结构上求一些贡献，但不能完全建出树时，常用方法是记忆化。例如在线段树上有经典结论，每个点对应的不同的 $len=r-l+1$ 的数量量级为 $O(\log n)$。而上文的做法中确实需要用 $len$ 计算贡献。所以不妨考虑记忆化搜索。

但现在问题是，上文的贡献中还有 $u$。而 $u \in [1,n]$，不同数量很大。于是我们想把贡献中的 $u$ 分出来。我们猜测以 $(u,len)$ 为根的子树贡献是一个关于 $u$ 的一次函数，其中 $len$ 是定值。这样我们就可以记忆化的过程中维护每个 $len$ 对应的一次函数即可。

现在的问题是，为什么是关于 $u$ 的一次函数。考虑归纳证明：

令 $f(u,len)$ 为根节点为 $u$，根的区间 $[l,r]$，区间长度 $len=r-l+1$ 时的整棵子树答案。

首先，$len=1$ 时，必有 $f(u,1) = u$。这很显然是一个 $b=0$ 的一次函数。

考虑 $len > 1$。我们假设 $u$ 的左右儿子的 $f(u,len)$ 都是关于 $u$ 的一次函数。考虑 $f(u,len)$ 的转移形式：$f(u,len) = f(lson,\lceil \frac{len}{2} \rceil) + f(rson,\lfloor \frac{len}{2} \rfloor) + u \times (2^{\lceil \frac{len}{2}\rceil} - 1) \times (2^{\lfloor \frac{len}{2}\rfloor} - 1)$。

进一步，由于左右儿子的 $f$ 都是一次函数，且 $lson = 2u$，$rson = 2u + 1$。

所以 $f(u,len) = k_{\lceil \frac{len}{2} \rceil} \times 2u + b_{\lceil \frac{len}{2} \rceil} + k_{\lfloor \frac{len}{2} \rfloor} \times (2u+1) + b_{\lfloor \frac{len}{2} \rfloor} + u \times (2^{\lceil \frac{len}{2}\rceil} - 1) \times (2^{\lfloor \frac{len}{2}\rfloor} - 1)$。

其中 $k$ 是斜率，$b$ 是截距。

发现这个式子关于 $u$ 是一次的，把式子整理成关于 $u$ 的一次函数就可以发现 $k_{len}$ 和 $b_{len}$ 关于左右儿子的递推式。

具体地：$k_{len} =  2 \times (k_{\lceil \frac{len}{2} \rceil} + k_{\lfloor \frac{len}{2} \rfloor}) + (2^{\lceil \frac{len}{2}\rceil} - 1) \times (2^{\lfloor \frac{len}{2}\rfloor} - 1), b_{len} = b_{\lceil \frac{len}{2} \rceil} + b_{\lfloor \frac{len}{2} \rfloor} + k_{\lfloor \frac{len}{2} \rfloor}$。读者自证不难。

使用 `map` 记忆化即可。复杂度 $O(T \log^2 n)$。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#include <map>
using namespace std;

const long long MOD = 998244353ll;

using ll = long long;

int t;
ll n;
map<ll, pair<ll, ll>> mp;

ll qpow(ll a, ll b)
{
	ll res = 1ll, base = a;
	while (b)
	{
		if (b & 1ll) res = res * base % MOD;
		base = base * base % MOD;
		b >>= 1ll;
	}
	return res;
}

pair<ll, ll> query(ll u, ll len)
{
	if (mp.count(len)) return mp[len];
	if (len == 1) return (mp[len] = make_pair(1ll, 0ll));
	if (len == 0) return (mp[len] = make_pair(0ll, 0ll));
	ll x = (len + 1) / 2ll, y = len / 2ll;
	auto lft = query(u << 1ll, x), rit = query(u << 1ll | 1ll, y);
	auto res = make_pair(((2ll * lft.first % MOD + 2ll * rit.first % MOD) % MOD + ((qpow(2ll, x) - 1) * (qpow(2ll, y) - 1) % MOD)) % MOD, (lft.second + rit.second + rit.first) % MOD);
	return mp[len] = res;
}

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> t;
	while (t--)
	{
		cin >> n;
		mp.clear();
		auto g = query(1, n);
		cout << (g.first + g.second) % MOD << "\n";
	}
	return 0;
}
```


---

## 作者：phigy (赞：2)

同上一篇题解的做法，但是我们只需要一只 $\log$。

----

具体的，根编号为 $i$ 的大小为 $x$ 的树的答案可以表示为 $f_xi+g_x$。

其中 $f_x$ 与 $g_x$ 均为定值。

同时由于左子树大小和右子树大小分别为 $\lceil\dfrac{x}{2}\rceil,\lfloor\dfrac{x}{2}\rfloor$。

设 $l=\lceil\dfrac{x}{2}\rceil,r=\lfloor\dfrac{x}{2}\rfloor$ 我们有转移方程 $f_x=2f_l+2f_r+(2^l-1)(2^r-1),g_x=f_r+g_l+g_r$。

为了方便我们求出 $2^l$ 和 $2^r$ 我们记录 $h_x=2^x$ 即可。

同上一篇题解一样我们可以证明大小为 $x$ 的树内子树大小种类为 $O(\log n)$ 种。

那么我们使用记忆化搜索和 `unordered_map` 便可以 $O(T\log n)$ 的复杂度通过本题。

```cpp
#include <bits/stdc++.h>

#define REN 1000000
#define MAXN (REN+5)
#define MOD 998244353
#define int long long

using namespace std;

int read()
{
    int x=0,f=1;
    char c=getchar();
    while(!isdigit(c)) {if(c=='-') {f=-1;} c=getchar();}
    while(isdigit(c))  {x=x*10+c-'0';c=getchar();}
    return x*f;
}
int T;
int n;
unordered_map<int,int>f,g,h;/// fx+g h=2^x
void calc(int x)
{
    if(f[x]) {return ;}
    int r=x>>1,l=x-r;
    calc(l);calc(r);
    f[x]=2*f[l]+2*f[r]+(h[l]+MOD-1)*(h[r]+MOD-1)%MOD;
    g[x]=f[r]+g[l]+g[r];
    h[x]=h[l]*h[r]%MOD;
    f[x]%=MOD;
    g[x]%=MOD;
}
signed main()
{
    int i,j,k;
    T=read();
    f[1]=1;g[1]=0;h[1]=2;
    while(T--)
    {
        n=read();
        calc(n);
        cout<<(f[n]+g[n])%MOD<<'\n';
    }
    return 0;
}
```


---

## 作者：xzy090626 (赞：1)

数数题。

我们可以考虑先暴力做法然后找规律。首先枚举 LCA 为 $x$ 是一个传统思路，那就是在它的左右子树各找至少一个结点，也就是说贡献为 $x\times (2^{siz_l}-1)\times (2^{siz_r}-1)$。显然如果 $mid=\lfloor{(l+r)\over 2}\rfloor$，那么 $siz_l=mid-l+1,siz_r=r-mid$。但是这样并不容易计算，于是我们考虑：线段树一定是一棵完全二叉树，也就是说 $siz_r\leq siz_l$，且如果 $siz_r\neq 0$，那么 $siz_l=2^{d_n-d_x-1}$，其中 $d_i=\lfloor \log_2 i \rfloor$ 即深度（标号从 $0$ 开始）。我们发现根据这个性质，对于深度相同的一层，子树大小一定是只有两种，于是我们可以直接分别计算，复杂度过得去。

也就是说我们只需要对每一层单独考虑了。对于子树为满的情况显然可以直接计算，然后子树不满但是有贡献的结点显然只有一个，单独递归计算即可。

复杂度是 $O(T\log^2 n)$，因为 $2$ 的幂次不能预处理需要快速幂算。

---

## 作者：Engulf (赞：0)

设 $f(u, l, r)$ 表示一个线段树节点子树内的答案。考虑 $u$ 成为 lca 的情况，即在左子树内选择至少一个点，右子树内选择至少一个点的方案数乘上 lca 编号 $u$，所以 $f(u, l, r) = f(2u, l, mid) + f(2u + 1, mid + 1, r) + u(2^{mid - l + 1} - 1)(2^{r - mid}-1)$。

这样算时间复杂度是 $O(n)$ 的。

考虑记忆化，注意到重复的长度很多，而去重后的长度只有 $O(\log n)$ 个，猜想答案是跟 $u$ 相关的，发现次数是 $1$，所以猜想 $f(u, l, r)$ 是 $u$ 的一次函数。设以 $x$ 为根的子树的答案 $f(u, l, r) = k_{len}x + b_{len}$。

$$f(u, l, r) = f(2u, l, mid) + f(2u + 1, mid + 1, r) + u(2^{mid - l + 1}-1)(2^{r - mid} - 1)$$

$$= k_{mid - l + 1}(2u) + b_{mid - l + 1} + k_{r - mid}(2u + 1)+b_{r - mid} + u(2^{mid - l + 1} - 1)(2^{r - mid} - 1)$$

$$=[2k_{mid - l + 1}+2k_{r - mid}+(2^{mid - l + 1} - 1)(2^{r - mid - 1})]u + b_{mid - l + 1} + k_{r - mid} + b_{r - mid}$$

所以

$$k_{r - l + 1} = 2k_{mid - l + 1}+2k_{r - mid}+(2^{mid - l + 1} - 1)(2^{r - mid - 1})$$

$$b_{r - l + 1} = b_{mid - l + 1} + k_{r - mid} + b_{r - mid}$$

用 map 记录即可。时间复杂度 $O(T\log^2n)$，因为快速幂。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

const int mod = 998244353;

int qpow(int a, ll b) {
    int res = 1;
    while (b) {
        if (b & 1) res = 1ll * res * a % mod;
        a = 1ll * a * a % mod;
        b >>= 1;
    }
    return res;
};

map<ll, int> k, b;

inline int f(ll u, ll len) {return (1ll * k[len] * u + b[len]) % mod;}

void dfs(ll u, ll l, ll r) {
    if (l == r) return;
    ll mid = l + r >> 1;
    ll len = r - l + 1;
    if (k[len]) return;
    ll l1 = mid - l + 1, l2 = r - mid;
    dfs(u << 1, l, mid);
    dfs(u << 1 | 1, mid + 1, r);
    k[len] = (((2ll * k[l1] + 2ll * k[l2]) % mod + 1ll * (qpow(2, l1) - 1) * (qpow(2, l2) - 1) % mod) % mod + mod) % mod;
    b[len] = ((b[l1] + k[l2]) % mod + b[l2]) % mod;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tt;
    cin >> tt;
    while (tt--) {
        ll n;
        cin >> n;
        k.clear(), b.clear();
        k[1] = 1;
        dfs(1, 1, n);
        cout << f(1, n) << "\n";
    }
    return 0;
}
```

---

## 作者：lyhqwq (赞：0)

# Solution 

很有意思的计数，感觉这类的题练的还是不够。

正难则反，考虑一个点作为 lca 会被计算多少次。

对于一个点，设它区间为 $[l,r]$，那么只需要在它的左子树和右子树中各选至少一个叶子节点即可，方案数为 $(2^{\frac{rl-l}{2}}-1)\times(2^{\frac{r-l+1}{2}}-1)$。不难发现长度相同的区间只有编号不同，不妨一起计算。

令 $f_x$ 表示长度为 $x$ 的区间的编号总和，$g_x$ 表示长度为 $x$ 的区间有多少。

$f_{\frac{x+1}{2}}=f_x\times 2$

$f_{\frac{x}{2}}=f_x\times 2+g_x$

$g_{\frac{x+1}{2}}=g_x$

$g_{\frac{x}{2}}=g_x$

线段树上不同长度的区间只有 $O(\log n)$ 个，map 存储状态递归计算即可，复杂度 $O(T\log^3n)$。

# Code
```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int Mod=998244353;
int _;
LL n,ans;
map<LL,LL> f,g,vis;
priority_queue<LL> q;
LL qpow(LL a,LL b){
	LL ans=1;
	for(;b;b>>=1,a=a*a%Mod) if(b&1) ans=ans*a%Mod;
	return ans;
}
void bfs(){
	q.push(n);
	f[n]=g[n]=vis[n]=1;
	while(!q.empty()){
		LL x=q.top();
		q.pop();
		if(x==1) ans=(ans+f[x])%Mod;
		else{
			LL L=(x+1)/2,R=x/2;
			ans=(ans+f[x]*(qpow(2,L)-1)%Mod*(qpow(2,R)-1)%Mod)%Mod;
			g[L]=(g[L]+g[x])%Mod;
			f[L]=(f[L]+f[x]*2%Mod)%Mod;
			g[R]=(g[R]+g[x])%Mod;
			f[R]=(f[R]+f[x]*2%Mod+g[x])%Mod;
			if(!vis[L]) q.push(L),vis[L]=1;
			if(!vis[R]) q.push(R),vis[R]=1;
		}
	}
}
int main(){
	scanf("%d",&_);
	while(_--){
		scanf("%lld",&n);
		f.clear(),g.clear(),vis.clear();
		ans=0;
		bfs();
		printf("%lld\n",ans);
	}
	return 0;
}

```

---

## 作者：XYQ_102 (赞：0)

首先容易想到大致思路是递归求，可以发现递归过程中会出现的区间长度只有 $\log n$ 种，容易想到记忆化。

很显然记忆化的时候参数只能带个长度，不能带别的，比如什么祖先的标号贡献啥的,因为带了状态就太多了没办法记忆化。

我们需要这些东西，我们定义 $dp_i$ 为当前长度为 $i$ 的区间为根节点（标号 $1$）时的答案（子集 LCA 之和）。并且定义 $f_{i,j}$ 为当前区间长度为 $i$ 为根节点（标号 $1$）时，子树内所有 LCA 在第 $j$ 层的子集数量。

考虑祖先节点对子区间答案的影响。

对于某个结点如果当前的标号为 $x$，如果给当前的线段树增加一个新的父亲，并且当前线段树是这个新父亲的左儿子会有什么影响呢？

答案是这个结点标号会增加 $2^d$，其中 $d$ 为深度。

类似地,如果线段树是新父亲的右儿子,那么结点标号增加 $2^{d+1}$。所以我们只需要记录每个深度方案的数量就能加上增加一个根节点带来的贡献。
## Code
```cpp
#include<iostream>
#include<cstring>
#include<vector>
#include<map>
#include<array>
using namespace std;
using LL = long long;
template<const int T>
struct ModInt {
    const static int mod = T;
    int x;
    ModInt(int x = 0) : x(x % mod) {}
    ModInt(long long x) : x(int(x % mod)) {} 
    int val() { return x; }
    ModInt operator + (const ModInt &a) const { int x0 = x + a.x; return ModInt(x0 < mod ? x0 : x0 - mod); }
    ModInt operator - (const ModInt &a) const { int x0 = x - a.x; return ModInt(x0 < 0 ? x0 + mod : x0); }
    ModInt operator * (const ModInt &a) const { return ModInt(1LL * x * a.x % mod); }
    ModInt operator / (const ModInt &a) const { return *this * a.inv(); }
    bool operator == (const ModInt &a) const { return x == a.x; };
    bool operator != (const ModInt &a) const { return x != a.x; };
    void operator += (const ModInt &a) { x += a.x; if (x >= mod) x -= mod; }
    void operator -= (const ModInt &a) { x -= a.x; if (x < 0) x += mod; }
    void operator *= (const ModInt &a) { x = 1LL * x * a.x % mod; }
    void operator /= (const ModInt &a) { *this = *this / a; }
    friend ModInt operator + (int y, const ModInt &a){ int x0 = y + a.x; return ModInt(x0 < mod ? x0 : x0 - mod); }
    friend ModInt operator - (int y, const ModInt &a){ int x0 = y - a.x; return ModInt(x0 < 0 ? x0 + mod : x0); }
    friend ModInt operator * (int y, const ModInt &a){ return ModInt(1LL * y * a.x % mod);}
    friend ModInt operator / (int y, const ModInt &a){ return ModInt(y) / a;}
    friend ostream &operator<<(ostream &os, const ModInt &a) { return os << a.x;}
    friend istream &operator>>(istream &is, ModInt &t){return is >> t.x;}

    ModInt pow(int64_t n) const {
        ModInt res(1), mul(x);
        while(n){
            if (n & 1) res *= mul;
            mul *= mul;
            n >>= 1;
        }
        return res;
    }
    
    ModInt inv() const {
        int a = x, b = mod, u = 1, v = 0;
        while (b) {
            int t = a / b;
            a -= t * b; swap(a, b);
            u -= t * v; swap(u, v);
        }
        if (u < 0) u += mod;
        return u;
    }
    
};
using mint = ModInt<998244353>;

const int M = 60;
struct Node{
    mint sum = 0;
    array<mint, M + 1> cnt = {}; 
};

int main(){

#ifdef LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif

    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(0);

    map<LL, Node> ans;
    auto solve = [&](auto &&solve, LL x) -> Node {
        if (x == 1) return {1, {1}};
        if (ans.contains(x)) return ans[x];
        mint sum = 0;
        LL tot = x;
        LL l = x - x / 2, r = x / 2;
        // lca = 根
        sum += mint(2).pow(tot) - mint(2).pow(l) - mint(2).pow(r) + 1;
        array<mint, M + 1> cnt = {};
        cnt[0] += sum;
        // lca 为左儿子
        {
            auto [s, c] = solve(solve, x - x / 2);
            sum += s;
            for(int i = 0; i < M; i++){
                cnt[i + 1] += c[i];
                sum += mint(1LL << i) * c[i];
            }
        }
        // lca 为右儿子
        {
            auto [s, c] = solve(solve, x / 2);
            sum += s;
            for(int i = 0; i < M; i++){
                cnt[i + 1] += c[i];
                sum += mint(1LL << (i + 1)) * c[i];
            }
        }
        return ans[x] = {sum, cnt};
    };

    int T;
    cin >> T;
    while(T--){
        LL n;
        cin >> n;
        cout << solve(solve, n).sum << '\n';
    }

}
```

---

