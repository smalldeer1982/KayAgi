# Three Occurrences

## 题目描述

You are given an array $ a $ consisting of $ n $ integers. We denote the subarray $ a[l..r] $ as the array $ [a_l, a_{l + 1}, \dots, a_r] $ ( $ 1 \le l \le r \le n $ ).

A subarray is considered good if every integer that occurs in this subarray occurs there exactly thrice. For example, the array $ [1, 2, 2, 2, 1, 1, 2, 2, 2] $ has three good subarrays:

- $ a[1..6] = [1, 2, 2, 2, 1, 1] $ ;
- $ a[2..4] = [2, 2, 2] $ ;
- $ a[7..9] = [2, 2, 2] $ .

Calculate the number of good subarrays of the given array $ a $ .

## 样例 #1

### 输入

```
9
1 2 2 2 1 1 2 2 2```

### 输出

```
3```

## 样例 #2

### 输入

```
10
1 2 3 4 1 2 3 1 2 3```

### 输出

```
0```

## 样例 #3

### 输入

```
12
1 2 3 4 3 4 2 1 3 4 2 1```

### 输出

```
1```

# 题解

## 作者：Zelotz (赞：19)

考虑枚举区间右端点 $r$，统计有多少合法的 $l$。

接下来将问题的限制拆分为两部分：
- 区间 $[l,r]$ 内每个数出现的次数是 $3$ 的倍数次。
- 区间 $[l,r]$ 每个数出现的次数不超过 $3$ 个。

先考虑如何统计满足第一个限制的区间数量。开一个桶记录每个数出现的数量，对 $3$ 取模，容易得到一个区间 $[l,r]$ 合法当且仅当 $r$ 对应的桶与 $l-1$ 对应的桶相同。无法 $\mathcal O(n)$ 判断两个桶是否相同，可以使用哈希解决。

再考虑第二个限制。只需要使用双指针，在右指针扫到 $i$ 的时候，不停将左指针向右移动并减去这个桶的出现次数，直到 $a_i$ 的出现次数小于等于 $3$ 为止。此时再统计答案，两个限制都可以满足。

在代码实现上，不需要繁琐的字符串哈希（难写而且会被卡单模数），只需要对每个值赋一个 $10^{18}$ 级别的随机数，桶的哈希值即为每个数出现的次数乘对应的随机数。
```
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define R(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e5 + 5;
const ll P = 1e18;
int n, a[N];
ll rdm[N], ans;
int cnt[N];// cnt维护每个数出现了几次 第二次使用时一个不能超过3次
__int128 hsh[N]; 
map <__int128, int> mp;
signed main()
{
    cin >> n; // 3的倍数次非常简单 hash即可 考虑如何恰好3的倍数次  
    mt19937_64 rnd(time(0));
    R(i, 1, n) rdm[i] = rnd() % P + 1;
    R(i, 1, n) 
    {
        hsh[i] = hsh[i - 1];
        cin >> a[i];
        hsh[i] -= 1ll * cnt[a[i]] * rdm[a[i]];
        ++cnt[a[i]]; cnt[a[i]] %= 3;
        hsh[i] += 1ll * cnt[a[i]] * rdm[a[i]];
    }
    mp[0] = 1;
    memset(cnt, 0, sizeof cnt);
    for (int i = 1, j = 0; i <= n; ++i)
    {
        ++cnt[a[i]];
        while (cnt[a[i]] > 3) --cnt[a[j]], (j ? --mp[hsh[j - 1]] : 1), ++j;
        ans += mp[hsh[i]];
        ++mp[hsh[i]];
    }
    cout << ans << '\n';
    return 0;
}

```

---

## 作者：George1123 (赞：17)


更 $\mu$ 棒的阅读体验 $\to $ [`George1123`](https://www.cnblogs.com/George1123/p/13749148.html)

---
## 题面

> [CF1418G Three Occurrences](https://www.luogu.com.cn/problem/CF1418G)

> 给一个 $n$ 个数的序列 $a_i$，求每个出现过的数出现次数为 $3$ 的子序列个数。

> 数据范围：$1\le n\le 5\cdot 10^5$，$1\le a_i\le n$。

---
## 蒟蒻语

做了半个上午做出了最离谱的做法：表格打叉叉。

用线段树求矩阵面积并实现，时间复杂度 $\Theta(n\log n)$，总用时 $1.40 min$。

---
## 蒟蒻解

想象有一个 $n\times n$ 的表格，行表示右端点，列表示左端点。

如果表格上的数为 $1$ 表示这个区间没被叉掉，对答案有贡献，否则这个区间不符合题目要求。

可以发现每次叉的都是一个矩阵，线段树扫描线求矩阵面积并即可。

**考虑数据：**

```cpp
8
1 1 2 1 2 1 2 1

answer=2
```

现在的表表是：

|||||||||
|-|-|-|-|-|-|-|-|
|$1$|$1$|$1$|$1$|$1$|$1$|$1$|$1$|
|$1$|$1$|$1$|$1$|$1$|$1$|$1$|$1$|
|$1$|$1$|$1$|$1$|$1$|$1$|$1$|$1$|
|$1$|$1$|$1$|$1$|$1$|$1$|$1$|$1$|
|$1$|$1$|$1$|$1$|$1$|$1$|$1$|$1$|
|$1$|$1$|$1$|$1$|$1$|$1$|$1$|$1$|
|$1$|$1$|$1$|$1$|$1$|$1$|$1$|$1$|
|$1$|$1$|$1$|$1$|$1$|$1$|$1$|$1$|

$(1)$ 把左端点大于右端点的给叉了：

|||||||||
|-|-|-|-|-|-|-|-|
|$1$|$0$|$0$|$0$|$0$|$0$|$0$|$0$|
|$1$|$1$|$0$|$0$|$0$|$0$|$0$|$0$|
|$1$|$1$|$1$|$0$|$0$|$0$|$0$|$0$|
|$1$|$1$|$1$|$1$|$0$|$0$|$0$|$0$|
|$1$|$1$|$1$|$1$|$1$|$0$|$0$|$0$|
|$1$|$1$|$1$|$1$|$1$|$1$|$0$|$0$|
|$1$|$1$|$1$|$1$|$1$|$1$|$1$|$0$|
|$1$|$1$|$1$|$1$|$1$|$1$|$1$|$1$|

$(2)$ 把超过 $3$ 个相同的数的区间叉了：

|||||||||
|-|-|-|-|-|-|-|-|
|$1$|$0$|$0$|$0$|$0$|$0$|$0$|$0$|
|$1$|$1$|$0$|$0$|$0$|$0$|$0$|$0$|
|$1$|$1$|$1$|$0$|$0$|$0$|$0$|$0$|
|$1$|$1$|$1$|$1$|$0$|$0$|$0$|$0$|
|$1$|$1$|$1$|$1$|$1$|$0$|$0$|$0$|
|$0$|$1$|$1$|$1$|$1$|$1$|$0$|$0$|
|$0$|$1$|$1$|$1$|$1$|$1$|$1$|$0$|
|$0$|$0$|$1$|$1$|$1$|$1$|$1$|$1$|

$(3)$ 把少于 $3$ 个相同的数的区间叉了：

|||||||||
|-|-|-|-|-|-|-|-|
|$0$|$0$|$0$|$0$|$0$|$0$|$0$|$0$|
|$0$|$0$|$0$|$0$|$0$|$0$|$0$|$0$|
|$0$|$0$|$0$|$0$|$0$|$0$|$0$|$0$|
|$0$|$0$|$0$|$0$|$0$|$0$|$0$|$0$|
|$0$|$0$|$0$|$0$|$0$|$0$|$0$|$0$|
|$0$|$0$|$0$|$0$|$0$|$0$|$0$|$0$|
|$0$|$1$|$0$|$0$|$0$|$0$|$0$|$0$|
|$0$|$0$|$1$|$0$|$0$|$0$|$0$|$0$|


然后剩下的 $2$ 就是答案了。

手玩一下就可以发现叉的规律了，非常简单易懂，蒟蒻就不负责任地放代码里了。

---
## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

//Start
typedef long long ll;
typedef double db;
#define mp(a,b) make_pair((a),(b))
#define x first
#define y second
#define be(a) (a).begin()
#define en(a) (a).end()
#define sz(a) int((a).size())
#define pb(a) push_back(a)
#define R(i,a,b) for(int i=(a),I=(b);i<I;i++)
#define L(i,a,b) for(int i=(b)-1,I=(a)-1;i>I;i--)
const int iinf=0x3f3f3f3f;
const ll linf=0x3f3f3f3f3f3f3f3f;

//Data
const int N=5e5;
int n,a[N],d[N]; ll ans;
vector<int> id[N];
struct line{
    int l,r,t; line(){}
    line(int l,int r,int t):l(l),r(r),t(t){}
};
vector<line> p[N+1];
void addmat(int xl,int xr,int yl,int yr){
    // cout<<"(["<<xl<<","<<xr<<"),["<<yl<<","<<yr<<"))\n";
    p[xl].pb(line(yl,yr,1)),p[xr].pb(line(yl,yr,-1));
}

//SegmentTree
const int tN=N<<2;
#define mid ((l+r)>>1)
int mn[tN],mc[tN],mk[tN];
void pushup(int k){
    if(mn[k*2+1]<mn[k*2+2]) mn[k]=mn[k*2+1],mc[k]=mc[k*2+1];
    else if(mn[k*2+1]>mn[k*2+2]) mn[k]=mn[k*2+2],mc[k]=mc[k*2+2];
    else mn[k]=mn[k*2+1],mc[k]=mc[k*2+1]+mc[k*2+2];
}
void pushadd(int k,int v){mn[k]+=v,mk[k]+=v;}
void pushdown(int k){pushadd(k*2+1,mk[k]),pushadd(k*2+2,mk[k]),mk[k]=0;}
void build(int k=0,int l=0,int r=n){
    if(r-l==1) return mn[k]=0,mc[k]=1,void();
    build(k*2+1,l,mid),build(k*2+2,mid,r),pushup(k);
}
void add(int x,int y,int v,int k=0,int l=0,int r=n){
    if(r<=x||y<=l) return; if(x<=l&&r<=y) return pushadd(k,v);
    pushdown(k),add(x,y,v,k*2+1,l,mid),add(x,y,v,k*2+2,mid,r),pushup(k);
}

//Main
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n;
    R(i,0,n) id[i].pb(-1),id[i].pb(-1),id[i].pb(-1);
    R(i,0,n) cin>>a[i],--a[i],d[i]=sz(id[a[i]]),id[a[i]].pb(i);
    R(i,0,n) id[i].pb(n),id[i].pb(n),id[i].pb(n);
    // cout<<"ok 60\n";
    R(i,0,n){
        addmat(i,i+1,i+1,n); // 把左端点大于右端点的给叉了
        addmat(i,n,0,id[a[i]][d[i]-3]+1); //把超过 3 个相同的数的区间叉了
        addmat(i,id[a[i]][d[i]+2],id[a[i]][d[i]-1]+1,i+1); //把少于 3 个相同的数的区间叉了
    }
    // cout<<"ok 66\n";
    build();
    R(i,0,n){ //求个矩阵面积并
        for(line u:p[i])if(u.r>u.l) add(u.l,u.r,u.t);
        ans+=mc[0]*(mn[0]==0);
    }
    cout<<ans<<'\n';
    return 0;
}
```
---
**祝大家学习愉快！**

---

## 作者：YLWang (赞：16)

这个题老厉害了。

看到这个题的第一想法是这样的：

考虑枚举右端点，维护合法的左端点个数。这玩意属实可以线段树搞。思维简单，实现也不难。

但有一种很牛逼的只要写十行的做法。

先考虑长度是 3 的倍数怎么做。

我们考虑维护每个前缀的每个数的出现个数 $cnt_{i, j}$，表示前 $i$ 个数中数 $j$ 出现的次数**模 3 的值**。

那么一段区间 $[l, r]$ 符合条件当且仅当 $cnt_{l-1} = cnt_r$。容易哈希。

至于恰好为 3？扫描线一下就没了。

放个代码链接。https://www.luogu.com.cn/paste/3t04xvxn。



---

## 作者：Xy_top (赞：6)

一道好题，输出所有区间满足其内部每个数要么出现 $3$ 次要么不出现的个数。

因为是区间，数量很多，发现贡献是可以抵消的，直接无脑预处理前缀的桶。

然后枚举左端点，统计答案，怎么处理呢？

疯狂地向右扩展，直到区间内有数字出现了 $3$ 次以上（这样是对的，待会儿证明，另外扩展到前一个就够了，不要到有数字出现了 $4$ 次）。

现在的区间内出现的数字都是 $3$ 次及以下了，接着看这个区间内有没有合适的前缀桶 $b$，$b$ 的每一项减去 $1\cdots l-1$ 这个前缀的桶 $c$，然后得到一个新的桶 $d$，如果 $d$ 内元素都是 $0$ 或 $3$，那么合法的答案就多了一个。

现在我们发现桶内的元素值已经不重要了，重要的是对 $3$ 取模的结果对吧？这样如果两个前缀桶 $b$ 和 $c$ 相减能构成答案，那么这两个桶的每一项元素就必定相同了吧。

如何维护两个桶是否相同呢？暴力还是行不通的，我们可以把它从高到低看成一个 $13331$ 进制的数（

这么大的数还是存不下啊，我们把它对一个质数取模就行了，然后再开一个桶维护前缀桶就能快速找到在给定的区间内与桶 $d$ 大概率相同的桶啦。

再来看下那个的证明，假设有个合法的区间 $l$ $r$，那么它中的所有元素出现个数一定小于等于 $3$，所以在以 $l$ 为左端点扩展时一定会扩展到 $r$ 了，所以一定会被统计到。

这样会不会重复统计呢？当然不会，我们把答案分左端点统计了啊。

然后单模数哈希过不了，写了双哈希。

```
#include <iostream>
#include <unordered_map>
#define int long long
using namespace std;
const int mod1 = 998244353, mod2 = 1000000009;
int n, l, r, ans;
int a[500005], s[500005], s1[500005], s2[500005];
int p1[500005], p2[500005];
unordered_map <int, int> b, w, b_;
signed main () {
	cin >> n;
	p1[0] = p2[0] = 1;
	for (int i = 1; i <= n; i ++) {
		p1[i] = p1[i - 1] * 13331 % mod1;
		p2[i] = p2[i - 1] * 13331 % mod2;
	}
	for (int i = 1; i <= n; i ++) cin >> a[i];
	for (int i = 1; i <= n; i ++) {
		++ b[a[i] ];
		s1[i] = s1[i - 1] + p1[a[i] ];
		s2[i] = s2[i - 1] + p2[a[i] ];
		if (s1[i] >= mod1) s1[i] -= mod1;
		if (s2[i] >= mod2) s2[i] -= mod2;
		if (b[a[i] ] == 3) {
			b[a[i] ] = 0;
			s1[i] -= p1[a[i] ] * 3;
			s2[i] -= p2[a[i] ] * 3;
			s1[i] = ( (s1[i] % mod1) + mod1) % mod1;
			s2[i] = ( (s2[i] % mod2) + mod2) % mod2;
		}
		s[i] = s2[i] * 1000000011 + s1[i];//把 s1 s2 连起来看成一个 1000000011 进制的数，这样是能唯一确定的。
	}
	b.clear ();
	for (l = 1; l <= n; l ++) {
		while (1) {
			if (r != n && b_[a[r + 1] ] != 3) {
				++ b_[a[++ r] ];
				++ b[s[r] ];
			} else break;
		}
		ans += b[s[l - 1] ];
		-- b_[a[l] ];
		-- b[s[l] ];
	}
	cout << ans;
	return 0;
}
```

---

## 作者：JackMerryYoung (赞：5)

# 前言

复习 XOR-Hash 时找到的小清新板子题。

感觉题解区的几篇都不是特别清晰（一定是我比较菜），决定还是自己写一篇，权当是消遣。

# 正文

声明：本题所谓任何数的的倍数均不包括 $0$。

首先我们知道一个思想，证明充要条件就要证明它既充分又必要；同样，要证明一个数等于某个值，必须让它既小于等于又大于等于这个值（听起来有点像废话，但确实有用，因为它实际上表示两种约束条件）。

这个思想运用到这道题上就十分方便。我们让所有数的出现个数 $cnt = 3$，便是要去满足 $cnt \geq 3 \land cnt \leq 3$ 这俩约束。

第一个约束十分好想，可以规约到 $cnt \equiv 0 \pmod 3$ 上去（三的倍数必然大于等于三），然后显然用 XOR-Hash 搞一下就行。具体来说：

我们对于值域内每一个数 $i$，生成俩随机值 $X_i, Y_i$。若一个数已经出现了一次，它的哈希值为 $X_i$，出现两次则为 $Y_i$，三次就是 $X_i \oplus Y_i$。

这样就可以使得出现次数为三的倍数的数对于前缀异或和的贡献为零了（显然 $X_i \oplus Y_i \oplus (X_i \oplus Y_i) = 0$，此时数字 $i$ 对前缀异或和的贡献自然为 0）

然后考虑第二个约束。我们考虑使用类似于双指针的算法，具体来说：

考虑对于一个满足约束二的 $[l, r]$ 区间，右指针每次往右移动一次，都**可能**会破坏原本“满足约束二”的性质。

那么为了让其重新满足，我们需要让左指针一直向右移动，即：从左到右删去数字使得区间再次满足约束二。

（只需让新加入的右指针的值 $a_r$ 出现的次数小于等于三即可；因为这样删除必然不会导致“因为其他数字出现次数减少而导致不能满足约束二”这种情况，理由显然）

令 $pre_r$ 为 $[1, r]$ 区间的异或和（也就是到 $r$ 为止的前缀异或和）。当删除完毕之后，我们统计满足 $pre_r = pre_{pos}$ 且 $pos \in [l, r]$ 的 $pos$ 数量，这一点可以使用 map 或者哈希表完成。

那么这道题就完成了，复杂度 $\mathcal{O}(N \log_2 N)$ 或者纯线性。

# 代码

``` cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

mt19937_64 rnd(time(NULL));

ll N, ans, arr[500005], tmp[500005], pre[500005];
ll cnt[500005], xmas[500005], ymas[500005];

ll bkt[500005];

map<ll, ll> MAP;

signed main()
{
	cin >> N;
	for(ll i = 1; i <= N; ++ i)
		cin >> arr[i];
	
	for(ll i = 1; i <= 500000; ++ i)
		xmas[i] = rnd(), ymas[i] = rnd();	
	
	for(ll i = 1; i <= N; ++ i)
	{
		++ cnt[arr[i]];
		if(cnt[arr[i]] % 3 == 1) tmp[i] = xmas[arr[i]];
		if(cnt[arr[i]] % 3 == 2) tmp[i] = ymas[arr[i]];
		if(cnt[arr[i]] % 3 == 0) tmp[i] = xmas[arr[i]] ^ ymas[arr[i]];
		pre[i] = pre[i - 1] ^ tmp[i];
	}
	
	MAP[0] = 1;
	for(int l = 0, r = 1; r <= N; ++ r)
	{
		++ bkt[arr[r]];
		while(bkt[arr[r]] > 3) 
		{
			-- bkt[arr[l]];
			if(l > 0) -- MAP[pre[l - 1]];
			++ l;
		}
		
		ans += MAP[pre[r]];
		++ MAP[pre[r]];
	}
	
	cout << ans << endl;
	return 0;
}
```

---

## 作者：lg_zhou (赞：5)

相信大家都学过一种证明方法，证明 $a=b$ 可以证明 $a\le b$ 且  $a \ge b$。

区间内出现的个数都等于三个，等价于区间内所有数都出现大于等于三次，且小于等于三次。我们可以一个一个满足。

在此之前确定一个解题的大方向，求区间个数问题，我们一般可以通过枚举右端点来判断对应的左端点个数来做，这道题也不例外。

先解决小于等于三次，对于任意一个右端点 R 来说，我们都可以双指针找到最靠左的 l 来满足 [l,R] 中的所有数都出现小于等于三次，这个开个桶维护一下即可。

下面来解决在区间中可以找到多少个左端点 L 使得 [L,R] 中所有数都大于等于三次。 

这会用到第二个转化，有数值出现大于等于三次，可以转化为这个数值的最后一个数和倒数第三个数均出现。那么我们每遇到最后一个数就前缀 $+1$，每遇到倒数第三个数就前缀 $-1$，目标就是有多少个位置恰好等于 $0$，最后一个数个数肯定大于等于倒数第三个数的个数，所以我们只用维护区间加和区间最小值个数即可，可以用线段树维护。

```cpp
#include<bits/stdc++.h>

#define fi first
#define se second
#define endl '\n'
// #define int long long
using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef long double db;

const int N = 5e5+5;
const int inf = 1e9;

struct seg{
    int l, r;
    int mn,cnt,add;
    #define mn(x) tree[x].mn
    #define l(x) tree[x].l
    #define r(x) tree[x].r
    #define cnt(x) tree[x].cnt
    #define add(x) tree[x].add
}tree[N*4];

void push_up(seg &x, seg l, seg r){
    x.mn = min(l.mn,r.mn);
    x.cnt = 0;
    if (x.mn == l.mn) x.cnt += l.cnt;
    if (x.mn == r.mn) x.cnt += r.cnt;
}
void update(int x, int v){
    mn(x) += v;
    add(x) += v;
}
void push_down(int x){
    update(x*2,add(x));
    update(x*2+1,add(x));
    add(x) = 0;
}
void build(int x, int l, int r){
    l(x) = l, r(x) = r;
    if (l == r){
        mn(x) = 0; cnt(x) = 1;
        return;
    }
    int mid = l+r>>1;
    build(x*2,l,mid);
    build(x*2+1,mid+1,r);
    push_up(tree[x],tree[x*2],tree[x*2+1]);
}
void modify(int x, int l, int r, int v){
    if (l(x) >= l && r(x) <= r){
        update(x,v);
        return;
    }
    push_down(x);
    int mid = l(x)+r(x)>>1;
    if (l <= mid) modify(x*2,l,r,v);
    if (r > mid) modify(x*2+1,l,r,v);
    push_up(tree[x],tree[x*2],tree[x*2+1]);
}
seg query(int x, int l, int r){
    if (l(x) >= l && r(x) <= r){
        return tree[x];
    }
    push_down(x);
    int mid = l(x)+r(x)>>1;
    seg ans; ans.mn = inf;
    if (l <= mid && r > mid) push_up(ans, query(x*2,l,r),query(x*2+1,l,r));
    else if (l <= mid) ans = query(x*2,l,r);
    else if (r > mid) ans = query(x*2+1,l,r);
    return ans;
}

int n,a[N];
int pos[N], lst[N],cnt[N];
void oper(int p, int v){
    if (p) modify(1,1,p,v);
    if (lst[lst[p]]) modify(1,1,lst[lst[p]],-v);
}
signed main(){
    // freopen("a.in","r",stdin);

    ios::sync_with_stdio(false); cin.tie(0u); cout.tie(0u);
    cin >> n;
    for (int i = 1; i <= n; i++){
        cin >> a[i];
        lst[i] = pos[a[i]];
        pos[a[i]] = i;
    }
    build(1,1,n);

    ll res = 0;
    for (int r = 1, l = 1; r <= n; r++){
        cnt[a[r]]++;
        if (cnt[a[r]] > 3){
            while(cnt[a[r]] > 3) cnt[a[l++]]--;
        }
        oper(r,1); oper(lst[r],-1);
        seg qr = query(1,l,r);
        if (qr.mn == 0){
            res += qr.cnt;
        }
    }
    cout << res << endl;
    return 0;
}
```


---

## 作者：Purslane (赞：5)

# Solution

菜题，速切。

考虑枚举右端点，计算符合要求的左端点的数量。

假设右端点 $r$ 左边的所有值为 $v$ 的数**最后四次**出现的位置分别是 $c_v$，$x_v$，$h_v$ 和 $q_v$，那么左端点 $l$ 可能的取值为 $(c_v,x_v] \cup (q_v,i_v]$。符合要求的 $l$ 要对于所有的 $v$ 都在这个两个区间的至少一个中。

因此你可以记录数轴上每个点被覆盖的次数。如果我们认为每个 $1 \le v \le n$ 中的数都会产生贡献的话，符合要求的 $l$ 应当被覆盖了 $n$ 次。显然这个是能被覆盖次数的最大值。于是线段树维护即可。

上述操作很容易线段树动态修改。不做赘述。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=5e5+10;
int n,a[MAXN],tag[MAXN<<2],mxval[MAXN<<2],mxcnt[MAXN<<2];
#define lson (k<<1)
#define rson (k<<1|1)
#define mid (l+r>>1)
void build(int k,int l,int r) {
	mxcnt[k]=r-l+1;
	if(l!=r) build(lson,l,mid),build(rson,mid+1,r);
	return ;	
}
void push_down(int k,int l,int r) {
	tag[lson]+=tag[k],tag[rson]+=tag[k];
	mxval[lson]+=tag[k],mxval[rson]+=tag[k];
	tag[k]=0;
	return ;	
}
void push_up(int k,int l,int r) {
	mxval[k]=max(mxval[lson],mxval[rson]),mxcnt[k]=0;
	if(mxval[k]==mxval[lson]) mxcnt[k]+=mxcnt[lson];
	if(mxval[k]==mxval[rson]) mxcnt[k]+=mxcnt[rson];	
	return ;
}
void update(int k,int l,int r,int x,int y,int v) {
	if(x<=l&&r<=y) return tag[k]+=v,mxval[k]+=v,void();
	push_down(k,l,r);
	if(x<=mid) update(lson,l,mid,x,y,v);
	if(y>mid) update(rson,mid+1,r,x,y,v);
	push_up(k,l,r);
	return ;
}
int _1[MAXN],_2[MAXN],_3[MAXN],_4[MAXN];
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n; ffor(i,1,n) cin>>a[i];
	build(1,1,n);
	long long ans=0;
	ffor(i,1,n) {
		update(1,1,n,i,i,n);
		//原来合法区间 (_1,_2] (_4,i]
		//现在合法区间 (_2,_3]
		int v=a[i];
		if(_1[v]<_2[v]) update(1,1,n,_1[v]+1,_2[v],-1);
		if(_4[v]<i) update(1,1,n,_4[v]+1,i,-1);
		if(_2[v]<_3[v]) update(1,1,n,_2[v]+1,_3[v],1);
		_1[v]=_2[v],_2[v]=_3[v],_3[v]=_4[v],_4[v]=i;
		if(mxval[1]==n) ans+=mxcnt[1];
	}
	cout<<ans;
	return 0;
}
```

然后看了一眼题解区，感觉更为厉害了。

考虑记录前缀 $[1,i]$ 中每个数出现次数模 $3$ 的值构成的 $3$ 进制 $n$ 位数位 $v_i$。那么 $[l,r]$ 是好区间等价于 $v_{l-1}=v_r$ 且 $[l,r]$ 中不存在一个数出现了至少 $4$ 次。

还是扫描右端点，找到最后一个 $p_r$ 使得 $[p_r,r]$ 中每个数只出现最多 $3$ 次，然后统计 $[p_r-1,r-1]$ 中与 $v_r$ 相同的数的个数。可以哈希。

由于 $p_r$ 单调不降，因此可以 two-pointer + map。

没写代码。

上述两种做法的复杂度都是 $O(n \log n)$。

---

## 作者：素质玩家孙1超 (赞：4)


~~单哈希不能过差评，我卡了整整20次，最后只能妥协写双哈希~~

题意：

问区间中所有元素都严格出现三次的区间个数。 $n\leq 500000$


---
思路：

我们先考虑区间里的元素出现次数都是三的倍数如何做。（那么原题只要在扫的过程中记录前三个点，并且每次把已经没有贡献的删掉就好了）

那么区间 $l,r$ 有贡献的条件是对于 $l$ 点和 $r$ 点，所有元素在这个点之前出现的次数对 $3$ 取模相同。（也就是说如果我们不关心到某个点某个元素出现多少次，我们只关心这个元素出现的次数对 $3$ 取模的值，那么一个区间要产生贡献只要两个端点的所有元素的这个值相同就好了。）

显然我们不能对于每个点都开一个桶来存下到这个点位置每个元素出现的次数。

所以我们只要搞出一个哈希值代替这个桶，每次使用哈希值来计算。（由于是cf题，所以单哈希会被hack）

---

实现：

不用其他数据结构，直接扫一遍，扫的同时开一个指针记录删除前面没有贡献的点，并对于每个点记录他前面的点与他哈希值相同的就好了。（至于哈希的方法，我是把每个元素 $x$ 算作 $base^x$ 来搞）

把map的log计算进去，复杂度$O(nlogn)$

---


小蒟蒻比较菜，不太会写题解，代码又丑，大佬们轻喷。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int unsigned long long 
inline int min(int a,int b){return a<b?a:b;}
const int Maxn=5e5+5;
inline int R()
{
	int res,sign=1;char c;
	while((c=getchar())>'9'||c<'0') if(c=='-') sign=-1;res=c-'0';
	while((c=getchar())>='0'&&c<='9') res=res*10+c-'0';
	return res*sign;
}
const int Mo=3158565539;
const int  P=1526024417;
const int base=15260279;
map<int,int>q,Q;
int a[Maxn],n,ans,dp[Maxn],pre[Maxn][3],power[Maxn],num[Maxn],cnt=0;
int               Dp[Maxn],             Power[Maxn];//双哈希 
inline int H(int x){if(num[x]) return num[x];return num[x]=++cnt;}
signed main()
{
	n=R();power[0]=1;Power[0]=1;
	for(int i=1;i<=500000;i++) power[i]=(power[i-1]*base)%Mo;
	for(int i=1;i<=500000;i++) Power[i]=(Power[i-1]*base)% P;
	int x,State=0,state=0,p1=1;
	for(int i=1;i<=n;i++)
	{
		q[state]++;
		Q[State]++;
		dp[i]=state;
		Dp[i]=State;//dp存每个位置的状态 
		x=H(R());a[x]++;
		if(pre[x][0]){//删除没贡献的点的贡献 
			if(pre[x][1]){
				if(pre[x][2])
					while(p1<=pre[x][2]) 
					{
						q[dp[p1]]--;
						Q[Dp[p1++]]--;
					}
				pre[x][2]=pre[x][1];
			}
			pre[x][1]=pre[x][0];
		}
		pre[x][0]=i;
		if(a[x]!=3) //修改状态 
		{
			state+=power[x];
			State+=Power[x];
		}
		else 
		{
			a[x]=0;
			state=state-power[x]+Mo;
			state=state-power[x]+Mo;
			State=State-Power[x]+ P;
			State=State-Power[x]+ P;
		}
		state%=Mo;
		State%= P;
		ans+=min(Q[State],q[state]);//计算贡献 
	}
	cout<<ans;
}

```




---

## 作者：ywy_c_asm (赞：4)

这题我用了两种截然不同的方法：

### 1.分治+$Hash$

看到统计区间个数立马想到分治，考虑每次如何把跨$mid$的两个前后缀**拼接**起来。比如我左区间的后缀里有2个1，那么为了与之互补，右区间的前缀里就必须有1个1，不难想到把$cnt$数组哈希起来，与之互补的$cnt$数组的哈希值也是能算的，当扫描前或后缀时某个数$cnt$超过3，那么后面的就都是非法的，不作统计。$cnt=3$时就把它当0处理。当然，这要特殊考虑左右部分各有3个相同的数的情况。

复杂度$O(n\log n)$（用unordered_map处理Hash表），然而单模数时就已经要跑4s多，并且会被卡（~~我取了17位的超大模数还是WA声一片……~~），无法通过本题……代码就不上了。

### 2.线段树

我们换用另一种统计区间个数的思路，即枚举区间右端点找左端点。

这个时候，我对于数$i$，记$lst_i$表示$i$最后出现的位置，那么，如果$i$被包含在以当前扫描的位置为右端点的区间内，一定是$lst_i$以及它的前两个被恰好包含在了里面，再令$pre_i$为$lst_i$往前第二个$i$出现的位置，那么合法的左端点就是：①它到当前右端点这段区间里没有数出现超过3次，②这段区间里每个数的$pre$和$lst$都被包含其中。

对于第一个限制，维护一个单调右移的指针限制查找范围即可。对于第二个限制，我对每个位置记录它到当前位置分别有多少$pre$和$lst$，我要让他俩相等，那么可以在每个为$lst$的位置的**前缀**整体+1，在每个为$pre$的位置的前缀进行整体-1，为0的位置就是合法的左端点。而注意到对前缀-1时一定不会减成负的，最小值最小就是0，那么拿线段树维护区间最小值个数即可。$O(n\log n)$

上代码~

```cpp
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#include <iostream>
#include <cstdio>
#include <cstring>
#define ll long long
#define N 500010
#define ls(_o) (_o << 1)
#define rs(_o) ((_o << 1) | 1)
#define did(_o, _x) \
    adds[_o] += _x; \
    minn[_o] += _x
using namespace std;
namespace ywy {
inline int get() {
    int n = 0;
    char c;
    while ((c = getchar()) || 23333)
        if (c >= '0' && c <= '9')
            break;
    n = c - '0';
    while ((c = getchar()) || 23333) {
        if (c >= '0' && c <= '9')
            n = n * 10 + c - '0';
        else
            return (n);
    }
}
int minn[N * 4], adds[N * 4], cnt[N * 4], pre[N][4], lst[N], ints[N];
inline void up(int tree) {
    minn[tree] = min(minn[ls(tree)], minn[rs(tree)]);
    cnt[tree] = 0;
    if (minn[tree] == minn[ls(tree)])
        cnt[tree] += cnt[ls(tree)];
    if (minn[tree] == minn[rs(tree)])
        cnt[tree] += cnt[rs(tree)];
}
inline void down(int tree) {
    did(ls(tree), adds[tree]);
    did(rs(tree), adds[tree]);
    adds[tree] = 0;
}
void build(int l, int r, int tree) {
    cnt[tree] = r - l + 1;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    build(l, mid, ls(tree));
    build(mid + 1, r, rs(tree));
}
void add(int rl, int rr, int l, int r, int tree, int x) {
    if (rl == l && rr == r) {
        did(tree, x);
        return;
    }
    int mid = (l + r) >> 1;
    down(tree);
    if (rl > mid)
        add(rl, rr, mid + 1, r, rs(tree), x);
    else {
        if (rr <= mid)
            add(rl, rr, l, mid, ls(tree), x);
        else {
            add(rl, mid, l, mid, ls(tree), x);
            add(mid + 1, rr, mid + 1, r, rs(tree), x);
        }
    }
    up(tree);
}
typedef struct _p {
    int a, b;
    _p() { a = b = 0; }
    _p(int i, int j) {
        a = i;
        b = j;
    }
    friend _p operator+(const _p &a, const _p &b) {
        _p r;
        r.a = min(a.a, b.a);
        r.b = 0;
        if (r.a == a.a)
            r.b += a.b;
        if (r.a == b.a)
            r.b += b.b;
        return (r);
    }
} pair;
pair query(int rl, int rr, int l, int r, int tree) {
    if (rl == l && rr == r)
        return (_p(minn[tree], cnt[tree]));
    down(tree);
    int mid = (l + r) >> 1;
    if (rl > mid)
        return (query(rl, rr, mid + 1, r, rs(tree)));
    if (rr <= mid)
        return (query(rl, rr, l, mid, ls(tree)));
    return (query(rl, mid, l, mid, ls(tree)) + query(mid + 1, rr, mid + 1, r, rs(tree)));
}
void ywymain() {
    int n = get();
    build(1, n, 1);
    for (register int i = 1; i <= n; i++) {
        ints[i] = get();
        pre[i][0] = i;
        if (lst[ints[i]]) {
            for (register int j = 1; j <= 3; j++) pre[i][j] = pre[lst[ints[i]]][j - 1];
        }
        lst[ints[i]] = i;
    }
    int ptr = 1;
    ll ans = 0;
    for (register int i = 1; i <= n; i++) {
        if (pre[i][1])
            add(1, pre[i][1], 1, n, 1, -1);
        add(1, i, 1, n, 1, 1);
        if (pre[i][2])
            add(1, pre[i][2], 1, n, 1, -1);
        if (pre[i][3]) {
            while (ptr <= pre[i][3]) ptr++;
        }
        pair ret = query(ptr, i, 1, n, 1);
        if (ret.a == 0)
            ans += ret.b;
    }
    cout << ans << endl;
}
}  // namespace ywy
int main() {
    ywy::ywymain();
    return (0);
}
```

---

## 作者：Gmt丶FFF (赞：2)

竟然没有人用无脑分块。

首先我们可以发现，如果当右端点在 $i$ 时且要满足 $a_i$ 这个数的条件，设上上上个与 $a_i$ 相等的下标为 $x$，上上个与 $a_i$ 相等的下标为 $y$，那么左端点一定在 $(x,y]$ 内。

那么我们可以将 $[1,x]$ 与 $(y,i]$ 的区间全部加上 $1$，那么值为 $0$ 的下标就是满足条件的下标。

对于要满足所有数的条件，那就将所有数的这种区间全部加上 $1$，然后查询 $[1,i]$ 中值为 $0$ 的下标个数。

那么区间加减与查询区间一个数的个数，就可以直接分块了。

设 $f_{i,j}$ 为块 $i$ 中数 $j$ 的数量，设块长为 $K$。

对于修改整块，打上标记即可，复杂度为 $O(\frac{n^2}{K})$。

对于修改散块，直接暴力重构这个块即可，复杂度为 $O(nK)$。

下放标记重构块即可，复杂度为 $O(nK)$。

那么总复杂度即为 $O(nK+\frac{n^2}{K})$。

由于 $n$ 较大，空间限制为 $500$ MB，所以我们要调长块长与使用 short 来卡空间，但这样会因为常数较大而过不了，所以需要卡一下常数，具体优化其实只需当一个没有打标记的区间要进行散块修改时不重构，直接修改要修改的数即可。

时间复杂度：$O(nK+\frac{n^2}{K})$，约为 $O(n\sqrt n)$。

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
using namespace std;
const int N=5e5+5;
const int K=1100;
const int M=K+5;
const int T=N/K+5;
char s1;
vector<int>t[N];
int n,a[N],B[N],L[T],R[T],len[N],p[N],laz[T];
short f[T][N];
char s2;
inline int max(int x,int y)
{
	return x>y?x:y;
}
inline int min(int x,int y)
{
	return x<y?x:y;
}
void init()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i=-~i)t[i].push_back(0);
	for(int i=1;i<=n;i=-~i)scanf("%d",&a[i]),B[i]=i/K+1,t[a[i]].push_back(i);
	for(int i=1;i<=B[n];i=-~i)L[i]=max(1,(i-1)*K),R[i]=min(n,i*K-1),f[i][0]=R[i]-L[i]+1;
}
void pushdown(int x)
{
	for(int i=L[x];i<=R[x];i=-~i)f[x][p[i]]--;
	for(int i=L[x];i<=R[x];i=-~i)p[i]+=laz[x];
	laz[x]=0;
}
void rebuilt(int x)
{
	for(int i=L[x];i<=R[x];i=-~i)f[x][p[i]]++;
}
void update(int l,int r,int k)
{
//	cerr<<l<<" "<<r<<" "<<k<<endl;
	if(B[l]==B[r])
	{
		if(!laz[B[l]])for(int i=l;i<=r;i=-~i)f[B[l]][p[i]]--,p[i]+=k,f[B[l]][p[i]]++;
		else
		{
			pushdown(B[l]);
			for(int i=l;i<=r;i=-~i)p[i]+=k;
			rebuilt(B[l]);
		}
		return;
	}
	if(!laz[B[l]])for(int i=l;i<=R[B[l]];i=-~i)f[B[l]][p[i]]--,p[i]+=k,f[B[l]][p[i]]++;
	else
	{
		pushdown(B[l]);
		for(int i=l;i<=R[B[l]];i=-~i)p[i]+=k;
		rebuilt(B[l]);
	}
	if(!laz[B[r]])for(int i=L[B[r]];i<=r;i=-~i)f[B[r]][p[i]]--,p[i]+=k,f[B[r]][p[i]]++;
	else
	{
		pushdown(B[r]);
		for(int i=L[B[r]];i<=r;i=-~i)p[i]+=k;
		rebuilt(B[r]);
	}
	for(int i=B[l]+1;i<B[r];i=-~i)laz[i]+=k;
}
int query(int x)
{
	int res=0;
	for(int i=1;i<B[x];i=-~i)if(laz[i]<=0)res+=f[i][-laz[i]];
//	pushdown(L[B[x]]);
//	rebuilt(L[B[x]]);
	for(int i=L[B[x]];i<=x;i=-~i)res+=(p[i]==0);
	return res;
}
void solve()
{
	long long res=0;
	for(int i=1;i<=n;i=-~i)
	{
		++len[a[i]];
		update(t[a[i]][len[a[i]]-1]+1,t[a[i]][len[a[i]]],1);
		if(len[a[i]]>=3)update(t[a[i]][len[a[i]]-3]+1,t[a[i]][len[a[i]]-2],-1);
		if(len[a[i]]>=4)update(t[a[i]][len[a[i]]-4]+1,t[a[i]][len[a[i]]-3],1);
		res+=query(i);
//		for(int i=0;i<=2;i++)cout<<f[1][i]<<" ";
//		cerr<<i<<" "<<res<<endl; 
	}
	printf("%lld\n",res);
}
int main()
{
//	freopen("data.in","r",stdin);
//	freopen("d.out","w",stdout);
//	cerr<<(((&s1)-(&s2))>>20)<<endl;
	init();
	solve();
	return 0;
}
```


---

## 作者：7KByte (赞：2)

YY 了一个标记永久化的做法。

对于每个位置 $i$ ，我们记 $pre_i$ 为它前面第一个和它颜色相同的位置。

如果我们求每个数恰好出现一次的方案数，就是对于每个 $i$ ，ban掉 $[1,pre_i]$ 这个区间。

扩展到出现恰好三次，就是对每个 $i$，ban掉 $[1,pre_{pre_{pre_i}}]$ 和 $[pre_{pre_i}+1,i]$ 。

同时我们还要求没有 ban 掉的位置数。

普通线段树非常不好求，但是我们可以对 tag 标记永久化，实现细节见代码。

时间复杂度 $\mathcal{O}(N\log N)$ ，常数小于一半线段树。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 500005
using namespace std;
int n,u[N],pre[N],c[N];
struct node{
	int l,r,sum,tag;
}a[N<<2];
#define L a[x].l
#define R a[x].r
#define ls (x<<1)
#define rs (ls|1)
#define S a[x].sum
#define T a[x].tag
void build(int x,int l,int r){
	L=l,R=r,T=0,S=r-l+1;
	if(l==r)return ;
	int mid=(l+r)>>1;
	build(ls,l,mid);
	build(rs,mid+1,r); 
}
inline void updata(int x){if(T)S=0;else if(L==R)S=1;else S=a[ls].sum+a[rs].sum;}
void change(int x,int l,int r,int val){
	if(L>=l&&R<=r)T+=val,updata(x);
	else{
		int mid = (L + R) >> 1;
		if(mid >= l)change(ls,l,r,val);
		if(mid < r)change(rs,l,r,val);
		updata(x);
	}
}
int ask(int x,int l,int r){
	if(T)return 0;
	if(L>=l&&R<=r)return S;
	int mid=(L+R)>>1,cur = 0;
	if(mid>=l)cur += ask(ls,l,r);
	if(mid<r)cur += ask(rs,l,r);
	return cur;
}
int main(){
	scanf("%d",&n);
	rep(i,1,n)scanf("%d",&u[i]),pre[i]=c[u[i]],c[u[i]]=i;
	build(1,1,n);long long ans = 0;int l = 0;
	rep(i,1,n){
		if(!pre[i])change(1,1,i,1);
		else if(!pre[pre[i]])change(1,1,pre[i],-1),change(1,1,i,1);
		else if(!pre[pre[pre[i]]])change(1,1,pre[i],-1),change(1,pre[pre[i]] + 1,i,1);
		else{
			change(1,pre[pre[pre[i]]] + 1,pre[i],-1);
			change(1,pre[pre[i]] + 1,i,1);
		}l = max(l,pre[pre[pre[i]]] + 1);
		ans += ask(1,l,i);
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Nuyoah_awa (赞：1)

### 题目大意

给定一个数组 $a$，问这个数组中有多少段区间中所有出现的数都只出现了 $3$ 次。

### 题目分析

常规思想，枚举右界然后看左界分别有多少种可能，假设枚举右界 $R$，则对于一个数 $x$，它最后出现的四次分别为 $a_{x_1}, a_{x_2}, a_{x_3}, a_{x_4}$ 则左界只有可能在 $(x_1, x_2]$ 或 $(x_4, R]$ 之间，所以 $L$ 即为所有数字上述条件的交集。

于是我们不妨记录一下每个点是否可以作为左界，动态维护，对于每个数，我们将处可行的区域外的点都赋上 $1$ 否则为 $0$，则 $L$ 可能的位置即为所赋值为 $0$ 的部分。

于是问题就转化为了区间赋值，区间求 $0$ 的个数，不难发现，赋完值后，每个点的值应都在 $0 \sim n$ 之间，所以可以当成区间求最小值及最小值有几个，然后就是线段树板子了。

### code
```cpp
#include <iostream>
#include <cstdio>
#define mid ((l+r)>>1)
#define ls (p<<1)
#define rs (ls^1)
#define int long long

using namespace std;

const int N = 5e5 + 5;
int n, a[N], lst[N], mx[N], ans, tmn[N<<2], tsm[N<<2], tag[N<<2];

void push_up(int p)
{
    if(tmn[ls] == tmn[rs])
        tmn[p] = tmn[ls], tsm[p] = tsm[ls] + tsm[rs];
    else if(tmn[ls] < tmn[rs])
        tmn[p] = tmn[ls], tsm[p] = tsm[ls];
    else
        tmn[p] = tmn[rs], tsm[p] = tsm[rs];
}
void push_down(int p)
{
    if(tag[p] == 0) return ;
    tmn[ls] += tag[p], tag[ls] += tag[p];
    tmn[rs] += tag[p], tag[rs] += tag[p];
    tag[p] = 0;
}

void build(int p, int l, int r)
{
    if(l == r)
    {
        tmn[p] = 0, tsm[p] = 1, tag[p] = 0;
        return ;
    }
    build(ls, l, mid), build(rs, mid + 1, r);
    push_up(p);
}

void update(int p, int l, int r, int ll, int rr, int val)
{
    if(ll <= l && r <= rr)
    {
        tmn[p] += val, tag[p] += val;
        return ;
    }
    push_down(p);
    if(ll <= mid)   update(ls, l, mid, ll, rr, val);
    if(rr > mid)    update(rs, mid + 1, r, ll, rr, val);
    push_up(p);
}

int last(int x, int y){return !y || !x ? x : last(lst[x], y-1);}

signed main()
{
    scanf("%lld", &n);
    for(int i = 1;i <= n;i++)
    {
        scanf("%lld", &a[i]);
        lst[i] = mx[a[i]];
        mx[a[i]] = i;
    }
    build(1, 1, n);
    for(int i = 1;i <= n;i++)
    {
        if(last(i, 3) > last(i, 4))
            update(1, 1, n, last(i, 4) + 1, last(i, 3), 1);
        if(last(i, 2) > last(i, 3))
            update(1, 1, n, last(i, 3) + 1, last(i, 2), -1);
        if(last(i, 0) > last(i, 1))
            update(1, 1, n, last(i, 1) + 1, last(i, 0), 1);
        if(tmn[1] == 0)
            ans += (tsm[1] - (n-i));
        //printf("%lld\n", ans);
    }
    printf("%lld", ans);
    return 0;
}
```

---

## 作者：youdu666 (赞：1)

思路：主席树，随机哈希

发现如果只需要序列中是 $3$ 的倍数的话其实比较好做，可以给每种值赋三种哈希值，按照从前往后的顺序赋值过去，其中前两个哈希值随机，第三个哈希值是前两个的异或起来的值，这样就可以做到对于一段里面全由 $3$ 的倍数个组成的数字的异或和为 $0$ 了。用随机哈希最大的好处就是不怕被 CF 卡，也不用双哈希了。

然后发现答案中不能包含超过 $4$ 个同一个数字，于是把同一种数字每四个就把前面的最右边更新区间缩减一下，使得每次查询时不会查询到一个包含四个及以上相同数字的区间。

哈希值为 $0$ 其实就等同于左右端点前缀哈希值相等，于是可以把前缀异或值用主席树存下来，直接查询可用区间即可。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
#define ull unsigned long long
mt19937_64 rng(random_device{}());
const int N=5e5+5;
ull s[N],x,y,z,b[N];
std::vector<int> v[N];
int n,a[N],tot,mn[N];
struct sg_tree{
	int x,ls,rs;
}t[N*30];int num;
int rot[N];
void build(int &k,int l,int r){
	k=++num;
	if(l==r)return;
	int mid=(l+r)>>1;
	build(t[k].ls,l,mid);
	build(t[k].rs,mid+1,r);
}
void update(int x,int &y,int l,int r,int id){
	y=++num;
	if(l==r){
		t[y].x=t[x].x+1;
		return;
	}
	int mid=(l+r)>>1;
	if(id<=mid)t[y].rs=t[x].rs,update(t[x].ls,t[y].ls,l,mid,id);
	else t[y].ls=t[x].ls,update(t[x].rs,t[y].rs,mid+1,r,id);
}
int query(int x,int y,int l,int r,int id){
	if(l==r)return t[y].x-t[x].x;
	int mid=(l+r)>>1;
	if(id<=mid)return query(t[x].ls,t[y].ls,l,mid,id);
	return query(t[x].rs,t[y].rs,mid+1,r,id);
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i],v[a[i]].emplace_back(i);
	for(int i=1;i<=n;i++)mn[i]=n;
	for(int i=1;i<=n;i++)if(v[i].size()){
		x=rng(),y=rng(),z=x^y;
		for(int j=0;j<v[i].size();j++){
			if(j%3==0)s[v[i][j]]=x;
			if(j%3==1)s[v[i][j]]=y;
			if(j%3==2)s[v[i][j]]=z;
			if(j>=3)mn[v[i][j-3]]=min(mn[v[i][j-3]],v[i][j]-1);
		}
	}
	for(int i=1;i<=n;i++)s[i]^=s[i-1],b[i]=s[i];
	b[n+1]=0;
	sort(b+1,b+n+2);
	tot=unique(b+1,b+n+2)-b-1;
	for(int i=0;i<=n;i++)s[i]=lower_bound(b+1,b+tot+1,s[i])-b;
	build(rot[0],1,tot);
	update(rot[0],rot[0],1,tot,s[0]);
	for(int i=1;i<=n;i++)update(rot[i-1],rot[i],1,tot,s[i]); 
	int sm=n,ans=0;
	for(int i=n;i>=0;i--){
		ans+=query(rot[i],rot[sm],1,tot,s[i]);
		sm=min(sm,mn[i]);
	}
	cout<<ans<<"\n";
}
```


---

## 作者：MurataHimeko (赞：0)

来点小清新做法。

考虑 XOR Hash，对于每种数，先随机两个权值 $x_i,y_i$，然后设 $p_{i,j}$ 为第 $i$ 种数的第 $j$ 次出现位置，那么有



$$ v_{p_{i,j}} =
\begin{cases}

x_i   (j\bmod 3 \equiv 1) \\
y_i (j\bmod 3 \equiv 2) \\
x_i\oplus y_i (j\bmod 3 \equiv 0)

\end{cases}

$$

再设 $pre_i$ 为 $v_i$ 的异或前缀和。

如果对于 $l,r$，满足 $pre_r \oplus pre_{l-1} = 0$，就意味着 $[l,r]$ 内每个数都出现了 $3$ 的倍数次。题目中要求每个数出现正好 $3$ 次，那么就相当于限定了 $l$ 必须大于某个值，双指针维护即可。

如果使用哈希表可以做到 $O(n)$。

代码：

```cpp
#include <bits/stdc++.h>
#define rep(i, f, t) for(int i(f); i <= t; ++i)
#define re(i, t) for(int i(1); i <= t; ++i)
#define per(i, t, f) for(int i(t); i >= f; --i)
#define pe(i, t) for(int i(t); i >= 1; --i) 
#define nx(i, u) for(int i(head[u]); i; i = e[i].nxt)
typedef long long ll; 
using namespace std;
// #define int long long
typedef pair <int, int> pii;
#define pb push_back
#define fi first
#define se second
#define ix(l, r) ((l + r) | (l != r)) 
#define inf (int)(1e9+7) 
bool sT;
namespace IO {
char buf[1 << 21], *p1 = buf, *p2 = buf, buf1[1 << 21];
inline char gc() {return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++;}
template<class I>
inline void read(I &x) {x = 0;I f = 1;char c = gc();while (c < '0' || c > '9') {if (c == '-') {f = -1;} c = gc();}while (c >= '0' && c <= '9') {x = x * 10 + c - '0';c = gc();}x *= f;}
template<class I>
inline void write(I x) {if (x == 0) {putchar('0');return;}I tmp = x > 0 ? x : -x;if (x < 0) {putchar('-');}int cnt = 0;while (tmp > 0) {buf1[cnt++] = tmp % 10 + '0';tmp /= 10;}while (cnt > 0)putchar(buf1[--cnt]);}
#define outn(x) write(x), putchar('\n')
#define out(x) write(x), putchar(' ')
} using namespace IO;

const int N = 5e5 +5;
int n;
int a[N];
ll b[N];
mt19937_64 rnd(time(0));
int vis[N];
vector<int>vec[N];
ll pre[N];
ll ans;
map<ll, int>mp;

int main () {
	read(n);
	int r = 1;
	++mp[0];
	re(i, n) {
		read(a[i]);
		if(vis[a[i]] <= 1) {
			b[i] = rnd();
			vec[a[i]].pb(i);
		}
		else {
			int x = vis[a[i]]; 
			b[i] = b[vec[a[i]][x-2]] ^ b[vec[a[i]][x-1]];
			if(x >= 3) {
				int p = vec[a[i]][x-3];
				rep(j, r, p) {
					--mp[pre[j-1]];
				}
				r = max(r, p+1);
			}
			vec[a[i]].pb(i);
		}	
		++vis[a[i]];
		pre[i] = pre[i-1] ^ b[i];
		ans += mp[pre[i]];
		++mp[pre[i]];
	}
	outn(ans);
}
```


---

