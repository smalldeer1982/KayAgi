# The Number of Subpermutations

## 题目描述

给定一个数组 $a_1, a_2, \dots, a_n$。

我们称数组的某个子数组 $a_l, a_{l+1}, \dots, a_r$ 为“子排列”，如果它恰好包含从 $1$ 到 $r-l+1$ 的所有整数各一次。例如，数组 $a = [2, 2, 1, 3, 2, 3, 1]$ 包含 $6$ 个子数组是子排列：$[a_2 \dots a_3]$、$[a_2 \dots a_4]$、$[a_3 \dots a_3]$、$[a_3 \dots a_5]$、$[a_5 \dots a_7]$、$[a_7 \dots a_7]$。

请你计算数组 $a$ 的子排列的数量。

## 说明/提示

第一个测试用例中有 $7$ 个子排列。它们的下标区间分别为 $[1, 4]$、$[3, 3]$、$[3, 6]$、$[4, 7]$、$[6, 7]$、$[7, 7]$ 和 $[7, 8]$。

在第二个测试用例中，有 $6$ 个子排列：$[1, 1]$、$[2, 2]$、$[2, 3]$、$[3, 4]$、$[4, 4]$ 和 $[4, 5]$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
8
2 4 1 3 4 2 1 2
```

### 输出

```
7
```

## 样例 #2

### 输入

```
5
1 1 2 1 2
```

### 输出

```
6
```

# 题解

## 作者：zhoutb2333 (赞：32)

观察到一个子区间 $[l, r]$ 如果是一个 $1$ 到 $r - l +1$ 的排列，那么等价于：

- $[l, r]$ 中没有重复的数字。
- $[l, r]$ 中的最大值为 $r - l + 1$ 。

于是可以分治，每次考虑包含在大区间 $[L, R]$ 中且经过 $mid$ 的所有区间。其中 $mid$ 是 $[L, R]$ 中最大值所在的位置，有多个最大值随意选一个。

那么这些区间的最大值就确定为 $a[mid]$ 了，只需再满足第一个条件。

预处理每个位置的 $pre$ 表示这个数字的前一次出现位置。令 $max_{pre}$ 为 $pre$ 的前缀 $max$ ，那么 $[l, r]$ 中没有重复的数字就等价于 $max_{pre}[r] <l$ （注意到 $max_{pre}[l]$ 肯定 $< l$ ，所以没问题）。

考虑优化复杂度。查看大区间左半边和右半边哪个更短。假设左半边更短，那么枚举每个 $[L,mid]$ 中的位置作为左端点，由于区间长度必须等于 $a[mid]$ ，那么右端点也就确定了。此时再看这个区间是否满足 $max_{pre}[r] < l$ 即可。

复杂度 $O(n\log n)$ ，是个确定性算法。（由于枚举到了每一个答案，所以也就证明了答案的上界是 $O(n \log n)$ ？

``` cpp
#pragma GCC optimize("O2,Ofast,inline,unroll-all-loops,-ffast-math")
#pragma GCC target("popcnt")
#include <bits/stdc++.h>
#define maxn 400010
#define ll long long
#define ull unsigned long long
#define ld long double
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define pob pop_back
#define pf push_front
#define pof pop_front
#define pii pair<int, int>
#define pil pair<int, ll>
#define pll pair<ll, ll>
#define IL inline
#define ss system
using namespace std;

int a[maxn], pre[maxn], nxt[maxn], pos[maxn], f[maxn], g[maxn], st[maxn][20], lg2[maxn], n, ans = 0;
template <class T> void read(T &x) {
  char ch = x = 0;
  bool fl = false;
  while (!isdigit(ch))
    fl |= ch == '-', ch = getchar();
  while (isdigit(ch))
    x = x * 10 + ch - '0', ch = getchar();
  x = fl ? -x : x;
}
int calc(int l, int r) {
  int len = lg2[r - l + 1];
  return a[st[l][len]] >= a[st[r - (1 << len) + 1][len]] ? st[l][len] : st[r - (1 << len) + 1][len];
}
void solve(int l, int r) {
  if (l > r)
    return;
  if (l == r)
    return ans += a[l] == 1, void();
  int mid = calc(l, r);
  if (mid - l < r - mid) {
    for (int i = l; i <= mid; i++) {
      int tmp = i + a[mid] - 1;
      if (tmp < mid || tmp > r || tmp >= g[i])
        continue;
      ans++;
    }
  } else {
    for (int i = mid; i <= r; i++) {
      int tmp = i - a[mid] + 1;
      if (tmp < l || tmp > mid || tmp <= f[i])
        continue;
      ans++;
    }
  }
  
  solve(l, mid - 1), solve(mid + 1, r);
}
int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i], pre[i] = pos[a[i]], pos[a[i]] = i, f[i] = max(f[i - 1], pre[i]);
  }
  for (int i = 1; i <= n; i++) {
    pos[i] = n + 1;
  }
  g[n + 1] = n + 1;
  for (int i = n; i; i--) {
    nxt[i] = pos[a[i]], pos[a[i]] = i, g[i] = min(g[i + 1], nxt[i]);
  }
  for (int i = 1; i <= n; i++) {
    st[i][0] = i;
  }
  for (int i = 2; i <= n; i++) {
    lg2[i] = lg2[i >> 1] + 1;
  }
  for (int j = 1; j <= lg2[n]; j++) {
    for (int i = 1; i + (1 << j) - 1 <= n; i++) {
      st[i][j] = a[st[i][j - 1]] >= a[st[i + (1 << j - 1)][j - 1]] ? st[i][j - 1] : st[i + (1 << j - 1)][j - 1];
    }
  }
  solve(1, n);
  printf("%d\n", ans);
  return 0;
}
```

---

## 作者：Alex_Wei (赞：26)

> [CF1175F The Number of Subpermutations](https://www.luogu.com.cn/problem/CF1175F)

给出 **好写且容易理解的确定性线性做法**。

考虑某个 $i$ 以及此时所有 $i$ 之前的位置 $j$ 到 $i$ 的最大值 $v_j = \max\limits_{p = j} ^ i a_p$，容易单调栈维护相同 $v_j$ 形成的极长连续段 $[l_j, r_j]$，则 $v_{r_j} = a_{r_j}$，且 $v_{l_j - 1} > v_{l_j} = \cdots = v_{r_j}$。

此外，我们需要将 $a_i$ 上一次出现位置 $p$ 及之前的 $j$ 全部弹出，因为这些位置到 $i$ 之间出现了重复数字，不可能产生贡献。因此需支持开头删除，末尾加入删除，将栈改成双端队列。

在此基础上，我们注意到如果一个极长连续段 $[l, r]$ 在 $i$ 处对答案产生贡献，则必然是 $l\sim i$ 形成 $1\sim i - l + 1$ 的排列：若 $l < p\leq r$ 的 $p$ 对答案产生贡献，则 $v_p = i - p + 1$，推出 $v_l < i - l + 1$，那么 $l\sim i$ 之间必然出现重复数字，矛盾。

进一步地，考虑一个极长连续段 $[l, r]$，则它会在 $i = l + v_r - 1$ 即 $l + a_r - 1$ 处产生 $1$ 的贡献，可以直接开数组 $val_i$ 表示在 $i$ 处产生贡献的极长连续段数量，则对每个 $i$ 操作结束后将答案加上 $val_i$ 即可。

对极长连续段进行修改时，在原来产生贡献的位置将 $val$ 减去 $1$，在新产生贡献的位置将 $val$ 加上 $1$。由于对极长连续段进行修改的次数均摊线性，所以时间复杂度为小常数 $\mathcal{O}(n)$。

由该算法可以证明答案级别为 $\mathcal{O}(n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 3e5 + 5;
int n, a[N], lst[N], ans, val[N << 1];
int hd = 1, tl;
struct dat {
  int l, r;
  void add(int v) {val[l + a[r] - 1] += v;}
} d[N];
int main() {
  cin >> n;
  for(int i = 1; i <= n; i++) {
    cin >> a[i];
    int pos = lst[a[i]];
    while(hd <= tl && d[hd].l <= pos) {
      d[hd].add(-1);
      if(d[hd].r <= pos) hd++;
      else d[hd].l = pos + 1, d[hd].add(1);
    }
    dat I = {i, i};
    while(hd <= tl) {
      if(a[d[tl].r] > a[i]) break;
      I.l = d[tl].l, d[tl--].add(-1);
    }
    I.add(1);
    d[++tl] = I;
    ans += val[i];
    lst[a[i]] = i;
  }
  cout << ans << endl;
  return 0;
}
/*
2022/8/16
author: Alex_Wei
start coding at 9:22
finish debugging at 9:40
*/
```

---

## 作者：Dregen_Yor (赞：23)


### [更好的阅读体验](http://dregen-yor.123ds.tk/index.php/2022/10/17/cf1175f/)。

# 背景

最近打模拟赛用到了**异或哈希**的知识，于是就在 CF 上找到了这一题。

据出题人说：“**xor-hashing** 可能最近普及开来了，记得 PKUSC 和 ABC 都有考过啊。”

# 思路

为了避免异或值重复的情况，我们用**梅森旋转算法**将 $1\sim n$ 赋成一个随机值，用一个数组 $base_i$ 记录前 $i$ 个数的异或和，这样一会在判断该序列是否为一个自排列的时候会方便很多。

我们考虑枚举所有 $1$ 的位置，分别向左和向右搜索能达到的最大值，**用这个最大值当做序列的长度**，设这个最大值为 $m$，并判断序列内的异或和是否与前 $m$ 个元素的异或和相等即可。

为了节省时间复杂度，我们考虑利用前缀和进行优化，用前缀和模拟向左搜索的过程，再将整个序列倒过来模拟向右搜索的过程即可。

# 代码

```cpp
#include<bits/stdc++.h>
#include<ctime>
#define int long long
#define N 300010
using namespace std;
int n,a[N],rd[N],pre[N],base[N],ans;
mt19937_64 rnd(time(0));
signed main(){
    scanf("%lld",&n);
    for(int i=1;i<=n;i++){
        scanf("%lld",&a[i]);
        rd[i]=rnd();
        base[i]=base[i-1]^rd[i];
    }
    for(int i=1;i<=n;i++){
        pre[i]=rd[a[i]]^pre[i-1];
    }
    for(int i=1,j=1;i<=n;i++){
        if(a[i]==1){
            j=1;
            ans++;
        }
        else {
            j=max(j,a[i]);
            if(i>=j&&(pre[i]^pre[i-j])==base[j]){
                ans++;
            }
        }
    }
    for(int j=1;n-j+1>=j;j++){
        swap(a[j],a[n-j+1]);
    }
    for(int i=1;i<=n;i++){
        pre[i]=rd[a[i]]^pre[i-1];
    }
    for(int i=1,j=1;i<=n;i++){
        if(a[i]==1){
            j=1;
        }
        else {
            j=max(j,a[i]);
            if(i>=j&&(pre[i]^pre[i-j])==base[j]){
                ans++;
            }
        }
    }
    printf("%lld",ans);
    return 0;
}
```


---

## 作者：SIGSEGV (赞：5)

考虑给每一个$1$~$n$的整数赋一个64位无符号值用于哈希，记为$h_1,h_2,...,h_n$，则序列中$[l,r]$的哈希值为
$h_{a_l} \oplus h_{a_{l+1}} \oplus ... \oplus h_{a_r} $，同理可得一个$1$~$k$排列的哈希值为$h_1 \oplus h_2 \oplus ... \oplus h_k$，且由于异或操作具有交换律和结合律，所以所得的哈希值与排列顺序无关。

对于每个$a_k=1$，从$k+1$开始递增枚举右端点$r$(长度为$1$的子排列单独统计)，令$L=\max_{k\le j\le r}a_j$，则显然$L$也为子排列长度（如果存在子排列的话），因此比较$h_1 \oplus h_2 \oplus ... \oplus h_L$与$h_{a_{r-L+1}} \oplus h_{a_{r-L+2}} \oplus ... \oplus h_{a_r}$，若相等则答案加一。当$a_r=1\lor r>n$时停止枚举（显然一个子排列里不会出现两个$1$）

这样珂以统计所有最大值在$1$右侧的子排列，再把整个序列反转一下进行统计，最后加上序列中$1$的个数即为答案

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 300005;
using ull = unsigned long long;
int n,a[N];
ull h[N],num[N],pre[N];
int calc(int pos)
{
    int mx = 1,ret = 0;
    for (int i = pos + 1;i <= n && a[i] != 1;i++)
    {
        mx = max(mx,a[i]);
        if (i >= mx && i - mx + 1 <= pos && num[mx] == (pre[i] ^ pre[i - mx])) ++ret;
    }
    return ret;
}
int main ()
{
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1;i <= n;i++) cin >> a[i];
    default_random_engine e;uniform_int_distribution<ull> u;
    e.seed(time(0));
    for (int i = 1;i <= n;i++) h[i] = u(e),num[i] = num[i - 1] ^ h[i];
    int ans = 0;
    for (int i = 1;i <= n;i++) pre[i] = pre[i - 1] ^ h[a[i]];
    for (int i = 1;i <= n;i++) if (a[i] == 1) ans += calc(i) + 1;
    reverse(a + 1,a + n + 1);
    for (int i = 1;i <= n;i++) pre[i] = pre[i - 1] ^ h[a[i]];
    for (int i = 1;i <= n;i++) if (a[i] == 1) ans += calc(i);
    cout << ans << endl;
    return 0;
}
```

---

## 作者：tzc_wk (赞：4)

[Codeforces 题面传送门](https://codeforces.ml/contest/1175/problem/F) & [洛谷题面传送门](https://www.luogu.com.cn/problem/CF1175F)

~~由于这场的 G 是道毒瘤题，蒟蒻切不动就只好来把这场的 F 水掉了~~

看到这样的设问没人想到[这道题](https://codeforces.ml/contest/997/problem/E)吗？那我就来发篇线段树+单调栈的做法。

首先显然一个区间 $[l,r]$ 满足条件当且仅当：

- $[l,r]$ 中不存在重复的数值
- $[l,r]$ 中最小值为 $1$
- $[l,r]$​ 中最大值与最小值的差为 $r-l$​

题解区中某位大佬说过：“数区间的题无非两种套路，枚举端点和分治”，这里咱们考虑枚举端点。具体来说，咱们枚举右端点 $r$，那么满足 $[l,r]$ 中不存在重复的数值的 $l$ 显然组成了一段连续的区间，且这个区间的右端点就是 $r$，因此可以在枚举右端点的同时 two pointers 找出满足“$[l,r]$ 中不存在重复的数值”的最大的 $l$，设为 $l'$ 这样我们左端点只用在 $[l',r]$ 中取值即可，这样第一个条件就解决了。第二个条件其实也异常 simple，我们只用找出上一个 $1$ 所在的位置 $p$，如果 $p<l'$ 那咱们就忽略这个区间，否则显然你区间的左端点必须 $\le p$，这样咱们区间的左端点的范围就进一步缩小到了 $[l',p]$。比较棘手的是第三个条件，不过按照那题的套路，第三个条件可以转化为 $\max\limits_{i=l}^ra_i-(r-l+1)=0$，又因为 $\forall l\in[l',p]$，区间 $[l,r]$ 中的数互不相同，因此 $\forall l\in[l',p],\max\limits_{i=l}^ra_i-(r-l+1)\ge 0$，因此我们可以开一棵线段树，线段树上 $l$ 位置上的值就是 $\max\limits_{i=l}^ra_i-(r-l+1)$，显然该线段树可以单调栈维护，那么我们只需要求出 $[l',p]$ 最小值即最小值个数即可算出贡献，具体来说如果最小值不为 $0$ 那么贡献为 $0$，否则贡献就是最小值的个数。

时间复杂度 $\mathcal O(n\log n)$

```cpp
const int MAXN=3e5;
int n,a[MAXN+5];
struct node{int l,r;pii p;ll lz;} s[MAXN*4+5];
pii operator +(pii lhs,pii rhs){
	pii res;res.fi=min(lhs.fi,rhs.fi);
	if(res.fi==lhs.fi) res.se+=lhs.se;
	if(res.fi==rhs.fi) res.se+=rhs.se;
	return res;
}
void pushup(int k){s[k].p=s[k<<1].p+s[k<<1|1].p;}
void build(int k,int l,int r){
	s[k].l=l;s[k].r=r;if(l==r) return s[k].p=mp(0,1),void();
	int mid=l+r>>1;build(k<<1,l,mid);build(k<<1|1,mid+1,r);pushup(k);
}
void pushdown(int k){
	if(s[k].lz){
		s[k<<1].p.fi+=s[k].lz;s[k<<1].lz+=s[k].lz;
		s[k<<1|1].p.fi+=s[k].lz;s[k<<1|1].lz+=s[k].lz;
		s[k].lz=0;
	}
}
void modify(int k,int l,int r,int x){
	if(l<=s[k].l&&s[k].r<=r){
		s[k].p.fi+=x;s[k].lz+=x;return;
	} pushdown(k);int mid=s[k].l+s[k].r>>1;
	if(r<=mid) modify(k<<1,l,r,x);
	else if(l>mid) modify(k<<1|1,l,r,x);
	else modify(k<<1,l,mid,x),modify(k<<1|1,mid+1,r,x);
	pushup(k);
}
pii query(int k,int l,int r){
	if(l<=s[k].l&&s[k].r<=r) return s[k].p;
	pushdown(k);int mid=s[k].l+s[k].r>>1;
	if(r<=mid) return query(k<<1,l,r);
	else if(l>mid) return query(k<<1|1,l,r);
	else return query(k<<1,l,mid)+query(k<<1|1,mid+1,r);
}
int pre[MAXN+5],cnt[MAXN+5];
int main(){
	scanf("%d",&n);build(1,1,n);ll res=0;
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	stack<int> stk;stk.push(0);a[0]=0x3f3f3f3f;
	for(int i=1,j=1;i<=n;i++){
		cnt[a[i]]++;while(cnt[a[i]]>=2) cnt[a[j++]]--;
		pre[a[i]]=i;modify(1,1,i,-1);modify(1,i,i,a[i]);
		while(!stk.empty()&&a[stk.top()]<a[i]){
			int x=stk.top();stk.pop();
			modify(1,stk.top()+1,x,a[i]-a[x]);
		} stk.push(i);if(pre[1]>=j){
			pii p=query(1,j,pre[1]);
			if(!p.fi) res+=p.se;
		}
	} printf("%ld\n",res);
	return 0;
}
```

还有一种思路便是**分治**（既然上面咱们选择了枚举端点，那这边咱们就要选择分治咯）

我们首先考虑怎样判断一个区间是否存在相同元素，按照区间数颜色的套路，我们记 $p_i$ 表示 $i$ 前面上一个与 $a_i$ 相等的 $a_j$ 的位置，那么区间 $[l,r]$ 不存在重复元素的充要条件是 $\max\limits_{i=l}^rp_i<l$。考虑分治，处理左右端点 $[l,r]$ 都在 $[l,r]$ 中的区间时，我们找出区间最大值所在的位置 $p$，那么显然 $[l,r]$ 中的区间可以像点分治那样分成三类：完全包含于 $[l,p-1]$、完全包含于 $[p+1,r]$，以及跨过 $p$，前两类显然可以递归处理。关于第三类，显然区间中最大的数就是 $a_p$，区间长度也就是 $a_p$，因此我们枚举所有长度为 $a_p$、且跨过位置 $p$（**这点一定要判断**）的区间计算贡献即可，但这样会 T，考虑优化，显然区间左端点必须在 $[l,p]$ 中对吧，右端点必须在 $[p,r]$ 中对吧，那么我们就考虑 $[l,p],[p,r]$ 中长度的较小者，如果 $[l,p]$ 长度较小就枚举左端点 $L\in[l,p]$，否则枚举右端点 $R\in[p,r]$。这样乍一看复杂度没啥变化，不过按照[这题](https://www.cnblogs.com/ET2006/p/luogu-P4755.html)的套路，这其实相当于启发式合并的逆过程，即**启发式分裂**（瞎起名字 ing），因此复杂度是严格单 log 的。

~~非常神奇，谁能告诉我为什么两个程序跑得一样快……358 ms~~

```cpp
const int MAXN=3e5;
const int LOG_N=18; 
int n,a[MAXN+5],pre[MAXN+5],st[MAXN+5][LOG_N+2],res=0;
pii st_val[MAXN+5][LOG_N+2];
int query(int l,int r){
	int k=31-__builtin_clz(r-l+1);
	return max(st[l][k],st[r-(1<<k)+1][k]);
}
int query_ps(int l,int r){
	int k=31-__builtin_clz(r-l+1);
	return max(st_val[l][k],st_val[r-(1<<k)+1][k]).se;
}
void solve(int l,int r){
	if(l>r) return;int ps=query_ps(l,r),len=a[ps];
	solve(l,ps-1);solve(ps+1,r);
	if(ps-l+1<=r-ps+1){
		for(int i=l;i<=ps;i++) if(i+len-1<=r&&i+len-1>=ps&&query(i,i+len-1)<i)
			res++;
	} else {
		for(int i=ps;i<=r;i++) if(i-len+1>=l&&i-len+1<=ps&&query(i-len+1,i)<i-len+1)
			res++;
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),st_val[i][0]=mp(a[i],i);
	for(int i=1;i<=n;i++) st[i][0]=pre[a[i]],pre[a[i]]=i;
	for(int i=1;i<=LOG_N;i++) for(int j=1;j+(1<<i)-1<=n;j++){
		st[j][i]=max(st[j][i-1],st[j+(1<<i-1)][i-1]);
		st_val[j][i]=max(st_val[j][i-1],st_val[j+(1<<i-1)][i-1]);
	} solve(1,n);printf("%d\n",res);
	return 0;
}
```

---

## 作者：intel_core (赞：3)

看到 $\text{CF}$ 标签里的 `hashing` ，果断哈希。

首先，给每个 $1$ 到 $n$ 里的数都随机赋一个哈希值 $p$。

哈希运算选一个满足交换律和结合律的，这里选的是异或。

如果一个长为 $k$ 子序列的哈希值是 $p_1 \oplus p_2 \oplus p_3\cdots p_{k-1}\oplus p_k$，那么这个子序列满足条件。

依次枚举每个 $1$，记当前 $1$ 的位置为 $k$，那么依次往后扫每一个 $r$，扫到下一个 $1$ 就停，统计扫到的合法序列的个数。

最后翻转一下序列再来一遍。

核心代码：

```cpp
int solve(int pos){
	int maxn=1,res=0;
	for(int i=pos+1;i<=n&&a[i]!=1;i++){
		maxn=max(maxn,a[i]);
		if(i>=maxn&&i-maxn+1<=pos&&num[maxn]==(pre[i]^pre[i-maxn]))res++;
	}
	return res;
}
```

---

## 作者：chenxia25 (赞：3)

泻药，提供一个不需要哈希且思路容易理解且复杂度线性的做法。

容易得到一个区间是子排列的充要条件：

1. 区间内元素互不相同；
1. 最大值为 $r-l+1$。

观察到第一个，显然是满足各种单调性的，即对于一个左 / 右端点，合法的右 / 左端点是前 / 后缀；并且对于左 / 右端点们，它所对应的最远右 / 左端点是单调的。于是我们可以枚举右端点，two-pointers 求最小左端点。

然后考虑第二个条件，我们可以维护每个位置的最大值，恰好套用这个扫描线的套路。直接在线段树上维护感觉不太行（分块可以考虑考虑），我们发现最大值显然也是单调的，单调栈轻松维护。但是对于每个右端点单调栈中每个区间的贡献方式又是会变的，要是每次都扫一遍单调栈显然会炸。我们可以考虑这样一个思路：对于每个区间记录它被加入的时间戳，然后被弹出的时候就总结一下它的一生，显然可以常数。

复杂度显然线性。

以上。

---

## 作者：nofind (赞：3)

## [题意](https://www.luogu.org/problem/CF1175F)

统计区间无非枚举端点或分治

考虑满足条件的区间$[l,r]$的性质:

1.最大值为$r-l+1$

2.没有重复数字

于是分治,对于$[l,r]$,选其中最大值的位置作为$mid$,统计所有过$mid$的区间,按照套路枚举一端点,由于$a[mid]$为区间长度,所以另一端点是确定的

考虑如何判断区间是否没有重复数字,对每个位置$i$求$pre[i]$表示$a[i]$上一次出现的位置,我们只要保证$max(pre[k])_{l\leqslant k\leqslant r}<l$即可

由于最大值分治可以被卡成$O(n^2)$,我们需要选择区间长度小的那一段枚举端点

code:
```
#include<bits/stdc++.h>
using namespace std;
const int maxn=3*1e5+10;
int n,ans;
int a[maxn],pre[maxn],last[maxn];
int st1[maxn][20],st2[maxn][20];
inline void ST()
{
	for(int i=1;i<=n;i++)st1[i][0]=i;
	for(int j=1;j<=18;j++)
		for(int i=1;i+(1<<j)-1<=n;i++)
			st1[i][j]=a[st1[i][j-1]]>a[st1[i+(1<<(j-1))][j-1]]?st1[i][j-1]:st1[i+(1<<(j-1))][j-1];
	for(int i=1;i<=n;i++)st2[i][0]=pre[i];
	for(int j=1;j<=18;j++)
		for(int i=1;i+(1<<j)-1<=n;i++)
			st2[i][j]=max(st2[i][j-1],st2[i+(1<<(j-1))][j-1]);
}
inline int query1(int l,int r)
{
	int t=(int)log2(r-l+1);
	return a[st1[l][t]]>a[st1[r-(1<<t)+1][t]]?st1[l][t]:st1[r-(1<<t)+1][t];
}
inline int query2(int l,int r)
{
	int t=(int)log2(r-l+1);
	return max(st2[l][t],st2[r-(1<<t)+1][t]);
}
void solve(int ql,int qr)
{
	if(ql>qr)return;
	if(ql==qr){if(a[ql]==1)ans++;return;}
	int mid=query1(ql,qr);
	if(mid-ql+1<=qr-mid)
	{
		for(int i=mid;i>=ql;i--)
		{
			int j=i+a[mid]-1;
			if(j>=mid&&j<=qr&&query2(i,j)<i)ans++;
		}
	}
	else
	{
		for(int i=mid;i<=qr;i++)
		{
			int j=i-a[mid]+1;
			if(j<=mid&&j>=ql&&query2(j,i)<j)ans++;
		}
	}
	solve(ql,mid-1),solve(mid+1,qr);
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)pre[i]=last[a[i]],last[a[i]]=i;
	ST();
	solve(1,n);
	printf("%d",ans);
	return 0;
}
```


---

## 作者：kouylan (赞：2)

## 题解 CF1175F 【The Number of Subpermutations】

[luogu题面](https://www.luogu.com.cn/problem/CF1175F)

[Codeforces题面](https://codeforces.com/contest/1175/problem/F)

分析可知，合法的子串肯定是一个排列，每个数只能出现一次。

那么什么东西可以判断一个数是否只出现一次呢？

**异或。**

所以这道题的思路就大致出来了。因为排列中肯定有 $1$，所以我们可以枚举 $1$ 的位置。每次向左/右搜，往一个方向搜的时候记录扫到的最大值，当作排列的长度（最大值），在判断这个子串是否合法就行了。

这样，我们就要把这个数列进行哈希。在计算 [$l,r$] 的哈希值时，只需要 $hs(r)\oplus hs(l-1)$，然后跟预处理出的排列哈希值比较，看是否相等即可。

另外，要注意 "^" 的优先级低于 "=="，要记得加括号。

下面是 AC 代码。

```cpp
/*
Codeforces 1175F
*/
#include <bits/stdc++.h>
using namespace std;

#define int long long

int n,a[300005],ans;
int v[300005],hs[300005],pm[300005];
vector<int> pos1;

signed main()
{
	srand(time(NULL));
	cin>>n;
	for(int i=1;i<=n;cin>>a[i++]);
	for(int i=1;i<=n;i++)
		v[i] = rand()*rand();
	for(int i=1;i<=n;i++)
		pm[i] = pm[i-1]^(i*v[i]);
	for(int i=1;i<=n;i++)
		hs[i] = hs[i-1]^(a[i]*v[a[i]]);
	for(int i=1;i<=n;i++)
		if(a[i]==1)
			pos1.push_back(i);
	for(int k=0;k<pos1.size();k++)
	{
		int mx=1,ll=(k==0 ? 1 : pos1[k-1]+1),rr=(k==pos1.size()-1 ? n : pos1[k+1]-1);
		for(int i=pos1[k]-1;i>=ll;i--)
		{
			mx = max(mx,a[i]);
			int l=i,r=i+mx-1;
			if(r<=n && r>=pos1[k] && (hs[r]^hs[l-1])==pm[mx])
				ans++;
		}
		mx = 1;
		for(int i=pos1[k]+1;i<=rr;i++)
		{
			mx = max(mx,a[i]);
			int l=i-mx+1,r=i;
			if(l>=1 && l<=pos1[k] && (hs[r]^hs[l-1])==pm[mx])
				ans++;
		}
	}
	cout<<ans+pos1.size()<<endl;
	
	return 0;
}
```

祝大家 AC 愉快！

---

## 作者：Leap_Frog (赞：1)

### P.S.
来一个用复杂度分析来做的 $O(n\log n)$ 的做法。  

### Description.
求一个序列中是排列的子串数量。  

### Solution.
首先，要满足是个排列，必须满足一下性质
1. 最大值是 $r-l+1$
2. 元素之间互不重复

我们考虑枚举最大值，那当前区间最长长度也知道了。  
因为它既是区间最大值，又需要满足区间不重复，  
所以我们只需要找出它前一个和后一个 $\ge$ 它的，在那边停止。  
同时因为区间长度已经给定，所以我们可以 $O(n)$ 扫描。  
复杂度至多 $O(n^2)$  

然后我们发现，加一个优化后，复杂度就变成了 $O(n\log n)$。  
优化大概就是因为当前区间左右端点需要同时满足在左边和右边，  
所以我们可以找出左右中扩展次数少一点的一侧，并枚举那一侧。  
可以证明，这样复杂度是 $O(n\log n)$，在最后会附上不严谨证明。  

然后这题就做完了。  
注意以上复杂度只是上界，实现时还需要保证序列内不存在相同的两个数。  

### Coding
```cpp
//是啊，你就是那只鬼了，所以被你碰到以后，就轮到我变成鬼了{{{
#include<bits/stdc++.h>
using namespace std;typedef long long ll;
template<typename T>inline void read(T &x)
{
	x=0;char c=getchar(),f=0;
	for(;c<48||c>57;c=getchar()) if(!(c^45)) f=1;
	for(;c>=48&&c<=57;c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	f?x=-x:x;
}/*}}}*/
int n,a[300005],ls[300005],nx[300005],pr[300005],st[300005],tp;
int main()
{
	read(n);int rs=0;for(int i=1;i<=n;i++) read(a[i]);
	memset(st,0,sizeof(st));for(int i=1;i<=n;i++) pr[i]=st[a[i]],st[a[i]]=i;
	for(int i=1;i<=n;st[++tp]=i++) while(tp&&a[st[tp]]<=a[i]) nx[st[tp]]=i,tp--;
	while(tp) nx[st[tp]]=n+1,tp--;
	for(int i=n;i>=1;st[++tp]=i--) while(tp&&a[st[tp]]<=a[i]) ls[st[tp]]=i,tp--;
	while(tp) ls[st[tp]]=0,tp--;
	for(int i=1;i<=n;i++) pr[i]=max(pr[i-1],pr[i]);
	//for(int i=1;i<=n;i++) printf("<%d,%d>%c",ls[i],nx[i],i==n?'\n':' ');
	for(int i=1;i<=n;i++) if(i-ls[i]<nx[i]-i)
		{for(int j=ls[i]+1;j<=i;j++) if(j+a[i]-1>=i&&j+a[i]-1<nx[i]&&pr[j+a[i]-1]<j) rs++;}
	else {for(int j=i;j<nx[i];j++) if(j-a[i]+1>ls[i]&&j-a[i]+1<=i&&pr[j]<j-a[i]+1) rs++;}
	return printf("%d\n",rs),0;
}
```

---

## 作者：yyy爱编程 (赞：1)

简单，随机权值过。

给定一个数列$a_1,a_2,a_3,···,a_n$,求有多少个子区间，满足下列条件：

- 设区间长度为 
$m$，则该子区间中 $1∼m$ 都恰好出现一次。

给$1~n$的每个数赋一个随机权值，一个区间的权值为区间内所有元素的权值的异或和。那么，对于每个$i$,$1~i$这些书对应一个权值。用$64$位整数随机赋权值，几乎不会冲突。

这样，对于满足条件的连续区间，只要看它的权值，和顺序就无关了。

区间肯定会包含$1$,所以枚举每个$1$的位置，再考虑包含这个$1$的区间的情况。

一个长度为$m$的区间的最大值为$m$,考虑最大值在区间右边的情况。

令最大值为$mx$。
从$1$开始向右扫描，并维护最大值$mx$和权值的异或和。如果目前已经有$k$个数，只要看 当前的异或和 异或 这个1左边$(mx-k)$个数的异或和是否等于长度为$m$的区间的权值。

预处理$1$左边的数的后缀异或和，向右扫描。

最大值在左边？同样处理。

$O(n)$,能过。

---

## 作者：TulipeNoire (赞：1)

题目描述非常的简单。

第一眼看：水题。

第二眼看：水题？

第三眼看：嗯。。。

第四眼看：不会。。。丢掉。

再看：算了，打暴力吧。

考后：A了？？？

言归正传。首先我们确定左端点 $l$，然后枚举右端点 $r$。我们发现，当 $\max\limits_{i=l}^r\{a_i\} >r-l+1$ 时，肯定没有答案，此时 $r$ 值可以直接变为 $l+\max\limits_{i=l}^r\{a_i\}-1$。我们就一直这样变换，当变不动时，就判断是否是一种答案（判定需要判重），然后 $r$ 再加 $1$，继续枚举。那么用两个ST表(一个维护区间最大值，一个维护区间后继最大值)就可以解决这个问题。

时间复杂度大约是：$O(ans)$。

code:

```
#include<bits/stdc++.h>
using namespace std;
const int N=500005;
int n,ans,a[N],st[25][N],dp[25][N],lst[N],base[N];
inline int max(int x,int y) {
    return x>y?x:y;
}
inline int min(int x,int y) {
    return x<y?x:y;
}
inline int get(int l,int r) {
    int L=base[r-l+1];
    return max(st[L][l],st[L][r-(1<<L)+1]);
}
inline int query(int l,int r) {
    int L=base[r-l+1];
    return min(dp[L][l],dp[L][r-(1<<L)+1]);
}
int main() {
    memset(lst,127,sizeof lst);
    scanf("%d",&n);
    for (int i=1;i<=n;i++) {
        scanf("%d",&a[i]);
        st[0][i]=a[i];
        base[i]=floor(log2(i));
    }
    for (int i=n;i>=1;i--) {
        dp[0][i]=lst[a[i]];
        lst[a[i]]=i;
    }
    int L=base[n];
    for (int j=1;j<=L;j++) {
        for (int i=1;i+(1<<j)-1<=n;i++) {
            st[j][i]=max(st[j-1][i],st[j-1][i+(1<<j-1)]);
            dp[j][i]=min(dp[j-1][i],dp[j-1][i+(1<<j-1)]);
        }
    }
    for (int i=1;i<=n;i++) {
        int j=i;
        while (j<=n) {
            while (j<=n&&i+get(i,j)-1>j&&query(i,j)>j) {//条件有点多
                j=i+get(i,j)-1;
            }
            if (j>n||i+get(i,j)-1<j||query(i,j)<=j) break;//若无法继续枚举下去，跳出。
            j++,ans++;
        }
    }
    printf("%d",ans); 
    return 0;
}
```

---

## 作者：Others (赞：0)

~~这题场上打了个假算法水了好多好多分~~

# Solution

这题的子序列稍稍想一下条件应该可以转化一下，对于“子排列”区间 $[l,r]$：

- 里面的数字不重复。
- 里面的最大值等于 $r-l+1$。

满足上面两个条件才能刚好填满值域，所以我们~~考虑暴力~~（先暴力后证复杂度得~~养成习惯~~）。我们枚举 $l$，对于 $l$ 我们从小到大枚举右端点，这里我们分别来讲讲怎样判断条件怎么满足：

- 不重复：可以打玄学数据结构（~~值域分块，树套树等~~），但是推荐用 `st`，我们对原数组整个 $lst$ 数组存上一此出现的位置，这里只需要保证 $\max\limits_{i=l}^{r}{lst_i}<l$ 很容易想到并实现。

- 最大值的限定：首先求最大值用 `st` 就行了，不赘述,这里讲这个条件的优化。我们拿到当前区间的最大值就可以知道这个左端点在当前情况（这里求得的最大值）下，最靠前的 $r=l+Max-1$，于是就这样更新 $r$，这样的复杂度是没有问题的。

**玄学优化**：

`st[100005][35]` 改成 `st[35][100005]` 可以降低接近一半的时间。

**复杂度**：

个人觉得证得不清楚，**可以跳过**。

这个“暴力”的复杂度的上界是 $O(n\log n)$，下界也是 $O(n\log n)$。

下界就是预处理 `st` 的复杂度，上界我们好好证明一下：

首先对于单增的序列，他的复杂度是 $O(\sum\limits_{i=1}^{n}\frac{n}{i})$，因为对于左端点 $i$，我们第一次更新的 $r$ 是 $i+i-1$，此时的最大值最小是 $i+i-1$，再次更新也会更新 $i$ 的长度，这样显然可以得到本段开头的复杂度，那东西化简后就是 $O(n\log n)$。

当时又脑抽了想了个以 $\sqrt n$ 为长度的单增的序列重复 $\sqrt n$ 次，其实是一样的（好像还要快些）。

献上我那丑陋的代码：

```cpp
#include <bits/stdc++.h>
#define max(x,y)(x>y?x:y)
using namespace std;
template<typename zqw>void qr(zqw &x){
	bool f=x=0;
	char c=getchar();
	while(!isdigit(c)) f|=c=='-',c=getchar();
	while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=getchar();
	x=f?~(x-1):x;
	return ;
}
int n,lo[500005],a[500005],top,pos[500005],lst[500005],st[35][500005],ans,sta[500005],bit[500005],Max[35][500005];
inline int getmax(int l,int r){return max(st[lo[r-l+1]][l],st[lo[r-l+1]][r-(1<<lo[r-l+1])+1]);}
inline int getMax(int l,int r){return max(Max[lo[r-l+1]][l],Max[lo[r-l+1]][r-(1<<lo[r-l+1])+1]);}
int main() {
	freopen("subpermutation.in","r",stdin);
	freopen("subpermutation.out","w",stdout);
	qr(n);
	for(int i=2;i<=n;i++) lo[i]=lo[i>>1]+1;
	for(int i=1;i<=n;i++){
		qr(a[i]);
		if(pos[a[i]]) lst[i]=pos[a[i]];
		pos[a[i]]=i;
		st[0][i]=lst[i];
		Max[0][i]=a[i];
	}
	for(int i=1;(1<<i)<=n;i++){
		for(int j=1;j+(1<<i)-1<=n;j++){
			st[i][j]=max(st[i-1][j],st[i-1][j+(1<<i-1)]);
			Max[i][j]=max(Max[i-1][j],Max[i-1][j+(1<<i-1)]);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n&&getmax(i,j)<i;j=(getMax(i,j)>j-i+1?i+getMax(i,j)-1:j+1)){
			if(j-i+1==getMax(i,j)) {
				ans++;
//				cout << i << " " << j << endl;
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}
/*
5
5 3 1 2 4

*/
```

---

## 作者：优秀的渣渣禹 (赞：0)

合法区间肯定包含 1，而且区间最大值等于区间长度。

具体的来说，我们横着扫一遍整个数列，每一个合法的子串都含1，我们需要给他包含进去。显然不含两个1，我们遇到下一个1就停止。我们维护一个当前经过的数的最大值，然后比如说当前扫描到$r$,然后最大值为$x$。显然如果合法应该是$r-x+1...r$，我们用$hash$ $O(1)$ $check$，然后我们对整个串反向，再求一次。
细节：对于长度为1的，我们可能多次计算，特殊处理一下就行了。

代码：
```cpp
#define B cout << "BreakPoint" << endl;
#define O(x) cout << #x << " " << x << endl;
#define O_(x) cout << #x << " " << x << " ";
#define Msz(x) cout << "Sizeof " << #x << " " << sizeof(x)/1024/1024 << " MB" << endl;
#include<cstdio>
#include<cmath>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
#include<ctime>
#define INF 1000000000
#define LL long long
#define pprint(x) ::print(x),putchar(' ')
#define fprint(x) ::print(x),putchar('\n')
#define ull unsigned long long
using namespace std;
inline LL read(){
	LL x = 0;
	int f = 1;
	char ch = getchar();
	for(;!isdigit(ch);ch = getchar())
		if(ch == '-')
			f = -1;
	for(;isdigit(ch);ch = getchar())
		x = x * 10 + (ch ^ 48);
	return x * f;
}
void print(ull x){
	if(x < 0) x = -x,putchar('-');
	if(x > 9) print(x / 10);
	putchar(x % 10 + '0');
}
const int N = 300010,mod = 19760817;
int n,a[N],ans;
ull h[N],num[N],t[N];
ull random(){
	return ((ull)rand() << 60) + ((ull)rand() << 31) + ((ull)rand() << 15) + ((ull)rand() << 7) + ((ull)rand() << 3) + ((ull)rand() << 1) + (ull)rand();
}
void init(){
	for(int i = 1;i <= n;i++) h[i] = h[i - 1] ^ num[a[i]];
}
bool check(int l,int r){
	return (h[r] ^ h[l - 1]) == t[r - l + 1];
}
void work(){
	init();
	int pos = 1;
	while(a[pos] != 1 && pos++ <= n);
	while(pos <= n){
		int l,maxx = a[pos++];
		while(a[pos] != 1 && pos <= n){
			if(check(pos - (maxx = max(maxx,a[pos])) + 1,pos)) ans++;
			pos++;
		}
	}
}
int main(){
	srand((unsigned)time(0));
	n = read();
	for(int i = 1;i <= n;i++){
		t[i] = t[i - 1] ^ (num[i] = random());
		ans += ((a[i] = read()) == 1);
	}
	work();
	reverse(a + 1,a + 1 + n);
	work();
	fprint(ans);
	return 0;
}
```

---

