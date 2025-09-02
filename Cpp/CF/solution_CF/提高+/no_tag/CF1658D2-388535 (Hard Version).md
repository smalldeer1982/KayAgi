# 388535 (Hard Version)

## 题目描述

This is the hard version of the problem. The difference in the constraints between both versions are colored below in red. You can make hacks only if all versions of the problem are solved.

Marin and Gojou are playing hide-and-seek with an array.

Gojou initially perform the following steps:

- First, Gojou chooses $ 2 $ integers $ l $ and $ r $ such that $ l \leq r $ .
- Then, Gojou will make an array $ a $ of length $ r-l+1 $ which is a permutation of the array $ [l,l+1,\ldots,r] $ .
- Finally, Gojou chooses a secret integer $ x $ and sets $ a_i $ to $ a_i \oplus x $ for all $ i $ (where $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)).

Marin is then given the values of $ l,r $ and the final array $ a $ . She needs to find the secret integer $ x $ to win. Can you help her?

Note that there may be multiple possible $ x $ that Gojou could have chosen. Marin can find any possible $ x $ that could have resulted in the final value of $ a $ .

## 说明/提示

In the first test case, the original array is $ [7, 6, 5, 4] $ .

In the second test case, the original array is $ [4, 7, 6, 5] $ .

In the third test case, the original array is $ [3, 1, 2] $ .

## 样例 #1

### 输入

```
3
4 7
3 2 1 0
4 7
4 7 6 5
1 3
0 2 1```

### 输出

```
4
0
3```

# 题解

## 作者：JS_TZ_ZHR (赞：11)

## 题意：

给定 $l,r$ 和一个长为 $r-l+1$ 的所有数都不相等的序列 $a$。请你找到任意一个数 $x$ 满足序列 $a$ 中的所有数异或上 $x$ 后正好为 $[l,l+1,...,r-1,r]$ 的一个排列。

## 题解：

显然 $a$ 中一定存在一个数 $a_i$ 使得 $a_i$ 异或 $x$ 等于 $l$。所以我们可以确定存在一个 $a_i$ 使得 $x=a_i\oplus l$，这里 $\oplus$ 指异或。

又由于 $a$ 中的数互不相同，所以其中的数异或上 $x$ 也互不相同。故当 $a$ 中的数异或上 $x$ 后最大值为 $r$，最小值为 $l$ 时，就可以确定此时 $a$ 取到了 $[l,r]$ 中间的每个值。 这个用 trie 维护即可。

```cpp
#include<bits/stdc++.h>
#define N 1000005
#define int long long
using namespace std;
int T,l,r,a[N],cnt,trie[N][30],b[N];
void insert(int sum){
	int now=0;
	for(int i=17;i>=0;i--){
		bool tmp=(1<<i)&sum;
		if(!trie[now][tmp])trie[now][tmp]=++cnt;
		now=trie[now][tmp];
	}
}
int Max(int sum){
	int now=0,res=0;
	for(int i=17;i>=0;i--){
		bool tmp=(1<<i)&sum;
		if(!trie[now][tmp^1])now=trie[now][tmp];
		else now=trie[now][tmp^1],res+=(1<<i);
	}
	return res;
}
int Min(int sum){
	int now=0,res=0;
	for(int i=17;i>=0;i--){
		bool tmp=(1<<i)&sum;
		if(!trie[now][tmp])now=trie[now][tmp^1],res+=(1<<i);
		else now=trie[now][tmp];
	}
	return res;
}
signed main() {
	cin>>T;
	while(T--){
		cin>>l>>r;
		for(int i=0;i<=cnt;i++)trie[i][0]=trie[i][1]=0;
		cnt=0;
		for(int i=l;i<=r;i++)cin>>a[i],b[i]=a[i]^l;
		for(int i=l;i<=r;i++)insert(a[i]);
		for(int i=l;i<=r;i++){
			if(Max(b[i])==r&&Min(b[i])==l){
				cout<<b[i]<<endl;
				break;
			}
		}
	}
}
```


---

## 作者：subcrip (赞：4)

（可能是本题实现最简单的方法？）

既然只是让我们猜 $x$ 的值，那么直接从高到低一位一位地试就行了。具体来说，从第 16 位直到 0 位，对于 $x$ 第 $i$ 位的两种情况 0 或 1，我们算出让当前猜出的 $x$ 的 $[i,16]$ 这些位去异或输入的数组，看看还原出的数组的 $[i,16]$ 位是否和原数组的这些位相等。如果相等，那么第 $i$ 位就猜对啦。时间复杂度 $O(n\log n)$ 。

---

Code:

```cpp
void solve() {
    read(int, left, right);
    int n = right - left + 1;
    readvec(int, a, n);
    int x = 0;
    array<vector<int>, 17> tar;
    for (int i = 0; i < 17; ++i) {
        for (int j = left; j <= right; ++j) {
            tar[i].emplace_back(j >> i);
        }
        sort(tar[i].begin(), tar[i].end());
    }
    for (int i = 16; ~i; --i) {
        for (int t = 0; t < 2; ++t) {
            x ^= 1 << i;
            vector<int> nw;
            for (int j = 0; j < n; ++j) {
                nw.emplace_back((a[j] >> i) ^ (x >> i));
            }
            sort(nw.begin(), nw.end());
            if (nw == tar[i]) {
                break;
            }
        }
    }
    cout << x << '\n';
}
```

---

## 作者：SunnyYuan (赞：4)

## 题意

原题面讲的很清楚了，我再来复述一下。

有一个长度为 $r - l + 1$ 的排列 $p$，满足 $l \le p_i\le r$，让我们找一个 $x$ 满足，对于每一个 $a_i = p_i \oplus x$，现在给你 $a$ 数组，让你找到一个可能的 $x$。

## 思路

异或有如下性质：$a \oplus b = c$，那么 $a \oplus c = b$。

因为 $a_i = p_i \oplus x$，所以 $a_i \oplus x = p_i$。

因为 $l \le p_i\le r$，所以 $l \le a_i \oplus x \le r$。

自然而然地，我们可以想到，我们可以枚举 $x$，在序列 $a$ 中找到可以异或出来的最大值 $\max$ 和最小值 $\min$，如果 $\max = r$ 且 $\min = l$，那么现在枚举的 $x$ 就是答案！

**那么在一个序列中找到一个数字 $x$ 可以异或出来的最大值和最小值，不就是妥妥的字典树吗？**

不会的参见 [Hydro H1002](https://hydro.ac/p/H1002)。

我们将 $a$ 数组放入字典树，然后找出 $x$ 可以异或出来的最大值和最小值，判断它是否分别等于 $r$ 和 $l$，相等则输出 $x$，否则继续枚举 $x$。

那我们不能瞎枚举 $x$ 啊，数字有千千万万个，我们还要进行优化。

因为一定存在 $a_i \oplus x = l$，那么一定有 $a_i \oplus l = x$。

即答案 $x$，一定存在这 $n$ 个数字中：$\{a_i \oplus l\}$。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 3000010, M = 19;

int tr[N][2], idx;

void add(int x) {	// 将 x 放入字典树
    int p = 0;
    for (int i = M - 1; i >= 0; i--) {
        int g = (x >> i & 1);
        if (!tr[p][g]) tr[p][g] = ++idx;
        p = tr[p][g];
    }
}

int getnum(int x, int type) { // type 为 1 表示取最小值，type 为 2 表示取最大值
    int res = 0, p = 0;
    for (int i = M - 1; i >= 0; i--) {
        int g = x >> i & 1;
        if (type == 1) {    // min
            if (tr[p][g]) p = tr[p][g];
            else p = tr[p][g ^ 1], res ^= (1 << i);
        }
        else {              // max
            if (tr[p][g ^ 1]) p = tr[p][g ^ 1], res ^= (1 << i);
            else p = tr[p][g];
        }
    }
    return res;
}

int l, r, n;

void solve() {
    memset(tr, 0, sizeof(tr[0]) * (idx + 10)); // 初始化
    idx = 0;
    cin >> l >> r;
    n = r - l + 1;
    vector<int> b;
    for (int i = 0; i < n; i++) {              // 输入 a[i]（懒得用数组存了）
        int x;
        cin >> x;
        b.push_back(x ^ l);                    // 记录每一个可能的 x。
        add(x);                                // 将 x 放入字典树
    }
    for (int i = 0; i < n; i++) {
        if (getnum(b[i], 1) == l && getnum(b[i], 2) == r) {// 判断
            cout << b[i] << '\n';                          // 答案
            return;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) solve();
    
    return 0;
}
```

---

## 作者：Neil_Qian (赞：1)

# CF1658D2 388535 (Hard Version) 题解
给你两个整数 $l$ 和 $r$，以及一个长度为 $r-l+1$ 的数组 $a$，找到一个整数 $x$，使得对于每一个 $a_i$ 异或 $x$ 生成的数组元素互不相同且在 $[l,r]$ 范围内。

我们很容易发现，只要 $a$ 数组中互补相同，那么异或出来一定不同。既然 $r-l+1$ 个数异或出来的范围只有 $r-l+1$ 个数，那么一定有 $a_p⊕x=l$，于是我们能够找到 $r-l+1$ 个 $x$，所以接下来我们只需要验证 $x$ 即可。

如何验证一个 $x$ 是否成立呢？之前说过，一定互不相同。但如果用 $r-l+1$ 次运算，那就肯定会超时。我们想到，只要异或值最大的正好是 $r$ 且最小的正好是 $l$ 的话，一定满足。那么如何求和 $x$ 异或后的最小值和最大值呢？

我们想到了字典树。可以帮我们在 $\log x$ 的时间复杂度内找到最小值和最大值。简单提一句，把这个数二进制表示加到字典树里面。以最小值为例，对于每一位，尽可能在字典树中找到和这一位一样的，否则只能不一样。最大值相反。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;typedef long long ll;const int N=1e6+2;
ll T,n,l,r,s[N][2],x,op,y,cnt,res;vector<ll> v;
inline void add(ll k){//添加操作
	x=1;
	for(int j=20;j>=0;j--){
		op=((k>>j)&1);
		if(!s[x][op])s[x][op]=++cnt;
		x=s[x][op];
	}
}
inline ll fnd(ll k){//找最小值
	x=1,res=0;
	for(int j=20;j>=0;j--)op=((k>>j)&1),(s[x][op]?
		(x=s[x][op],res+=(op<<j)):
		(x=s[x][op^1],res+=((op^1)<<j)));
	return res;
}
inline ll fnd2(ll k){//找最大值
	x=1,res=0;
	for(int j=20;j>=0;j--)op=((k>>j)&1),(s[x][op^1]?
		(x=s[x][op^1],res+=((op^1)<<j)):
		(x=s[x][op],res+=(op<<j)));
	return res;
}
int main(){
	scanf("%lld",&T);
	while(T--){
		for(int i=1;i<=cnt;i++)s[i][0]=s[i][1]=0;//清零
		scanf("%lld%lld",&l,&r),n=r-l+1,v.clear(),cnt=1;//同上
		for(int i=1;i<=n;i++)
			scanf("%lld",&y),add(y),v.push_back(y^l);//注意要在字典树中添加完才能检查是否合法
		for(ll x:v)if((x^fnd(x))==l&&(x^fnd2(x))==r)//合法
		{printf("%lld\n",x);break;}//输出即可
	}
	return 0;
}
```

写题解不易，求点赞！

---

## 作者：intel_core (赞：1)

直接考虑区间 $[l,r]$ 中的每个数都能由某个 $a_i$ 异或 $x$ 得到并不好考虑，转化成最值考虑。

如果一个 $x$ 满足 $\max\limits_{1\le i\le n}a_i\oplus x=r,\min\limits_{1\le i\le n}a_i\oplus x=l$，那么等价于 $\{a_i\oplus x\}$ 构成区间 $[l,r]$。

因为 $\max a_i,l,r\le 2^{17}$，所以 $x\le 2^{17}$，一个一个枚举 $a_i$，代入 $a_i\oplus l$ 用 $\text{01Trie}$ 求最大值最小值验证即可。

复杂度 $O(V \log V)$，其中 $V=2^{17}$。

---

## 作者：Ghosty_Neutrino (赞：0)

## 题意

给一个 $l$ 和 $r$，然后选一个数 $x$ 对 $l-r$ 的排列 $p_i$ 每一项进行异或操作，得到数组 $a$，$a_i=p_i^x$。现在输入 $l$ 和 $r$ 和操作后的数组 $a$，让你求它们异或的数 $X$ 是什么？

## 分析

首先根据异或性质 $p_i^x=a_i$，那么 $a_i^x=p_i$，所以我们可以暴力遍历这个 $x$ 和 $a$ 进行异或，然后验证是否是 $l-r$ 排列即可，但……太暴力了嘿嘿，我们不能暴力。

### 优化（进化）

进一步优化：我们只需要 $\max(a_i^x)=l$ 然后 $\min(a_i ^ x) = r$ 即可，显然这个方法复杂度没变只是验证简单了。现在复杂度大头主要是 $x$ 和每个 $a_i$ 异或的复杂度，有没有方法能快速求出异或最大值，最小值？ 这里就使用 $01$ 字典树，它主要用于解决求异或最值问题，如给出 $x$ 和数组 $a$，求 $x^a_i$ 的值。

使用 $01$ 字典树我们解决原问题，由于遍历 $x$ 太多仍然会超时，我们发现我们要找 $a_i^x=l$，那么这个 $x$ 肯定在 $a_i^l$ 得到的集合中。

最终我们遍历 $x=a_i^l$，对每个 $x$，使用 $01$ 字典树求出 $\max$ 和 $\min$。如果分别等于 $l$ 和 $r$，则这个 $x$ 就是我们要的答案。

## 代码启动


```cpp
#include<bits/stdc++.h>
#define rep(i, a, n) for(int i = a; i <= n; ++ i)
#define per(i, a, n) for(int i = n; i >= a; -- i)
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
typedef pair<ll, int> PLI;
typedef pair<ll, ll> PLL;
const int N = 2e6 + 50;
const int mod = 998244353;
const double Pi = acos(- 1.0);
const ll INF = 1e12;
const int G = 3, Gi = 332748118;
ll qpow(ll a, ll b, ll p) { ll res = 1; while(b){ if(b & 1) res = (res * a) % p; a = (a * a) % p; b >>= 1;} return res % p; }
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
ll l, r, n;
ll a[N];
ll idx;
void insert(ll x, vector<vector<ll> > &nxt){
    ll now = 0;
    for(int i = 31; i >= 0; -- i){
        int y = (x >> i) & 1;
        if(!nxt[now][y]) nxt[now][y] = ++ idx;
        now = nxt[now][y];
    }
}
ll query_max(ll x, vector<vector<ll> > &nxt){
    ll now = 0, res = 0;
    for(int i = 31; i >= 0; -- i){
        int y = (x >> i) & 1;
        if(nxt[now][y ^ 1]){
            res += (1 << i);
            now = nxt[now][y ^ 1];
        }else now = nxt[now][y];
    }
    return res;
}

ll query_min(ll x, vector<vector<ll> > &nxt){
    ll now = 0, res = 0;
    for(int i = 31; i >= 0; -- i){
        int y = (x >> i) & 1;
        if(nxt[now][y]) now = nxt[now][y];
        else {
            res += (1 << i);
            now = nxt[now][y ^ 1];
        }
    }
    return res;
}

void solve(){
    idx = 0;
    scanf("%lld%lld",&l ,&r);
    n = r - l + 1;
    vector<vector<ll> > nxt(n * 32, vector<ll>(2, 0));
    for(int i = 1; i <= n; ++ i){
        scanf("%lld",&a[i]);
        insert(a[i], nxt);
    }

    for(ll i = 1; i <= n; ++ i) {
        ll ans = a[i] ^ l;
        ll L = query_min(ans, nxt);
        ll R = query_max(ans, nxt);
        if(L == l && R == r) {
            printf("%lld\n",ans);
            return;
        }
    }
}
int main() {
    int T; scanf("%d",&T);
    while(T --){
        solve();
    }
    return 0;
}
```

---

## 作者：Purslane (赞：0)

# Solution

专门在 CF 里面找到 Data Structure 的题写，怎么这个不是 DS 题啊。。。

考虑从高到低逐位确定 $x$ 的值。假设我们到了最高位。如果初始区间和终止区间最高位 $0$ 的个数不一样，那么 $x$ 这一位肯定为 $1$。

如果最高位 $0$ 的个数一样，且初始状态 $0$ 和 $1$ 的个数不一样，那么这一位肯定为 $0$。

如果最高位 $0$ 的个数一样，初始状态 $0$ 和 $1$ 的个数也是一样的，那么实际上初状态 $[l,r]$ 可以改为 $[l,2^k-1]$ 和 $[2^k,r]$ 两个对称的区间。所以这一位是 $0$ 是 $1$ 其实无所谓。你可以默认是 $0$。

我们结束这个过程之后，按照最高位是 $0$ 和 $1$ 分开，分治地解决子问题，求解更低以为的状态。

注意对于某一位我们可能有多个区间共同行动。由于答案存在，所以即使某一个区间算出来 $0$ 和 $1$ 皆可，也需要参考其他区间的限制。

> 其实这里有一个问题，就是对于第三种状态到底怎么分，因为这一位零一皆可。如果我们目前初始状态并不是从 $0$ 开始到 $2^{k+1}-1$ 结束，那么不可能有平行宇宙存在的。这一位选零还是选一都是无所谓的，反正是是对称的，大不了后面所有数同时取个反。如果目前初始状态为 $0$ 到 $2^{k+1}-1$，那么其实无论 $x$ 怎么定都是合法的的。因此甚至不需要继续往后找了。

不需要用 Trie 树。

code：[link](https://codeforces.com/problemset/submission/1658/212115963)

---

## 作者：ttq012 (赞：0)

$\color{#ffda00}\mathscr{Difficutly: *2300}$

## $\mathscr{DESCRIPTION}$

给定 $l$，$r$ 和一个长度是 $r-l+1$ 的一个序列 $a$，问选择哪一个整数 $x$ 满足 $a$ 序列全部异或上 $x$ 之后，是一个 $l\sim r$ 的排列。

## $\mathscr{SOLUTION}$

前置芝士：如果一个序列 $a$ 中的所有元素互不相同，那么 $a$ 中的所有的元素同时异或上相同的数字 $x$，所有的元素仍然互不相同。证明显然。

于是问题转化成了找到一个数 $x$ 满足 $\max (a_i\oplus x)=r$ 且 $\min (a_i\oplus x)=l$。

由于 $0\le l\le r<2^{17}$，$0\le a_i<2^{17}$，所以 $x$ 一定不会超过 $2^{17}$。

于是考虑枚举 $x$，用 `01-trie` 找最值，判断是否满足条件即可。

时间复杂度 $\mathcal O(n\log n)$。

## $\mathscr{CODE}$

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 3e5 + 10;
namespace OI_trie
{
  struct Node
  {
    int nxt[2], cnt, val;
    Node()
    {
      nxt[0] = nxt[1] = 0;
      cnt = val = 0;
    }
  } z[N];
  int ROOT = 1, cnt = 1;
  void clear()
  {
    for (int i = 0; i <= cnt; i++)
      z[i] = Node();
    ROOT = 1, cnt = 1;
  }
  void ps_ms(int val, int o)
  {
    int rt = ROOT;
    for (int i = 30; ~i; i--)
    {
      int p = val >> i & 1;
      if (!z[rt].nxt[p])
        z[rt].nxt[p] = ++cnt;
      rt = z[rt].nxt[p];
      z[rt].cnt += o;
    }
    z[rt].val = val;
  }
  void insert(int val) { ps_ms(val, 1); }
  void erase(int val) { ps_ms(val, -1); }
  int query_max(int val)
  {
    int rt = ROOT;
    for (int i = 30; ~i; i--)
    {
      int p = val >> i & 1;
      if (z[rt].nxt[p ^ 1] && z[z[rt].nxt[p ^ 1]].cnt > 0)
        rt = z[rt].nxt[p ^ 1];
      else
        rt = z[rt].nxt[p];
    }
    return val ^ z[rt].val;
  }
  int query_min(int val)
  {
    int rt = ROOT;
    for (int i = 30; ~i; i--)
    {
      int p = val >> i & 1;
      if (z[rt].nxt[p] && z[z[rt].nxt[p]].cnt > 0)
        rt = z[rt].nxt[p];
      else
        rt = z[rt].nxt[p ^ 1];
    }
    return val ^ z[rt].val;
  }
}
int a[N];
signed main()
{
  int T;
  cin >> T;
  while (T--)
  {
    OI_trie::clear();
    int l, r;
    cin >> l >> r;
    for (int i = l; i <= r; i++)
    {
      cin >> a[i];
      OI_trie::insert(a[i]);
    }
    for (int i = l; i <= r; i++)
      if (OI_trie::query_max(a[i] ^ l) == r && OI_trie::query_min(a[i] ^ l) == l)
      {
        cout << (a[i] ^ l) << '\n';
        break;
      }
  }
  return 0;
}
```

## $\mathscr{AC\ RECORD}$

[$\mathscr{LINK}$](https://www.luogu.com.cn/record/105371823)

---

## 作者：蒟蒻君HJT (赞：0)

### difficulty - 2500

### [problem link](https://www.luogu.com.cn/problem/CF1658D2)

### [code](https://codeforces.com/contest/1658/submission/189485916)

提供一种不用字典树的做法，但可能实际上跑的并不是最快。

说句闲话：在 cf 上找 interactive 标签做了这道题，做完了才发现根本不是交互题。。。

进入正题：关于异或运算有一个很常用的性质：$(2k) \operatorname{xor}{(2k+1)}=1$。而这两个数之间也可以用异或 $1$ 互相转化。

在这道题里还有一个性质：对于一对数字 $2k$ 和 $2k+1$，它们在异或了某一个值 $x$ 之后，一定还能“配对”，即变成 $2m$ 和 $2m+1$，只是相对顺序可能会改变。

这说明什么？我们从初始情况开始考虑：如果 $[l,r]$ 这 $r-l+1$ 个原始的数中存在没有“配对”的数字，即 $l$ 为奇数时的 $l$ 或 $r$ 为偶数时的 $r$，则这个（些）数字最后肯定还是没有“配对”的，所以我们可以再找出 $a_i$ 中没有“配对”的数字，进行暴力验证（最多验证 $2$ 组就能得到正确答案）。

而如果 $l$ 为偶数且 $r$ 为奇数，所有数字都配对了，你会发现 $x$ 的最后一位的取值 $0/1$ 是无所谓的，它只会改变最后配对的数字的相对顺序。举个例子吧，可能有点抽象（加括号的是配对的数字）：

$l=4,r=7,\{a_n\}=(0,1),(2,3)$

若取 $x=4$，$\{b_n\}=(4,5),(6,7)$；

若取 $x=5$，$\{b_n\}=(5,4),(7,6)$。

因此，我们可以把基数乘以 $2$，把 $[l,r]$ 和 $\{a_n\}$ 中的偶数取出来除以 $2$，用上述的方法递归求解 $x$ 的高位。问题规模缩小到了 $1/2$。

时间复杂度 $\mathcal{O}(n\log n)$。

---

