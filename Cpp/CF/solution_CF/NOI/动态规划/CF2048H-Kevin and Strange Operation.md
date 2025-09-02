# Kevin and Strange Operation

## 题目描述

Kevin 正在唐人街研究与二进制字符串相关的问题。当他一筹莫展时，一位陌生人走过来，向他介绍了一种奇特的操作：

- 假设当前的二进制字符串为 $t$，长度为 $|t|$。选择一个整数 $1 \leq p \leq |t|$。对于所有 $1 \leq i < p$，同时执行操作 $t_i = \max(t_i, t_{i+1})$，然后删除 $t_p$。

例如，假设当前二进制字符串为 01001，选择 $p = 4$。对 $t_1$、$t_2$ 和 $t_3$ 执行 $t_i = \max(t_i, t_{i+1})$，字符串变为 11001，然后删除 $t_4$，得到 1101。

Kevin 觉得这种奇怪的操作很有趣。因此，他想问你：给定一个二进制字符串 $s$，通过任意次数（可以为零）这种操作，最多能得到多少个不同的非空二进制字符串？

由于答案可能非常大，你只需要输出结果对 $998\,244\,353$ 取模后的值。

## 说明/提示

在第一个测试用例中，所有可以得到的二进制字符串为：11001、1001、1101、001、101、111、01、11 和 1。一共有 $9$ 个。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2
11001
000110111001100```

### 输出

```
9
73```

# 题解

## 作者：zac2010 (赞：4)

## Part1：观察描述

* 对于任意次操作后的字符串，其每个位置都对应原序列一段区间的 $\max$。我们记当前第 $i$ 个数来源于为 $[l_i,r_i]$。
* 初始时 $l=r=\{1,2,\dots,n\}$。考虑每次操作前 $p$ 个数，等价于删去 $[l_1,r_1],[l_2,r_2],\dots[l_p,r_p]$，替换成 $[l_1,r_2],[l_2,r_3],\dots,[l_{p-1},r_p]$。
* 注意到这个操作等价于每次删去 $r_1$，执行了 $k$ 次后 $r=\{k+1,k+2,\dots,n\}$。 同时，操作后 $l,r$ 会保持原来的顺序，即数组元素递增。

## Part2：设计算法

* 考虑枚举右端点从右往左 $\text{DP}$。记 $f_{i,j}$ 为，右端点为 $i$，左端点为 $j$ 的方案数。

* 每次为了防止算重，我们贪心的仅在最大的合法 $j$ 更新我们的方案。

* 更具体的，我们分以下情况讨论：

  1. $s_i=1$

     * 下一位只能是 $1$：$f_{i,j}\to f_{i-1,j-1}$

  2. $s_i=0$

     * 下一位是 $0$：$f_{i,j}\to f_{i-1,j-1}$

     * 下一位是 $1$：$f_{i,j}\to f_{i-1,pre_i}(j>pre_i)$

       其中 $pre_i$ 表示 $i$ 前面最近的 $s_j=1$。

* 这个 $\text{DP}$ 本质上是区间平移，单点修改。

  我们可以另第二个维度 $j'=i-j$，这样 $f_i\to f_{i-1}$ 的时候大部分位置就不会变了（事实上会变的只有表示 $pre_i$ 的位置）。

  因为 $pre_i$ 有单调性，我们容易将过程优化到 $O(n)$。

## Part3：代码实现

```cpp
#include <bits/stdc++.h>
#define FL(i, a, b) for (int i = (a); i <= (b); ++i)
#define FR(i, a, b) for (int i = (a); i >= (b); --i)
using namespace std;
const int N = 1e6 + 10;
const int MOD = 998244353;
int n, pre[N], f[N];
char s[N];
void AddTo(int &x, int y) {
	x = (x + y >= MOD? x + y - MOD : x + y);
}
void Solve() {
	scanf("%s", s + 1);
	n = strlen(s + 1);
	f[0] = 1;
	FL(i, 1, n) {
		if (s[i] == '1') {
			pre[i] = i;
		} else {
			pre[i] = pre[i - 1];
		}
	}
	int j = n, cnt = 0, sum = 1, ans = 0;
	FR(i, n, 1) {
		for (; j > pre[i]; --j) {
			AddTo(cnt, f[i - j]);
		}
		if (pre[i]) {
			if (s[i] == '0') {
				AddTo(f[i - pre[i]], cnt);
				AddTo(sum, cnt);
			}
			AddTo(cnt, MOD - f[(i - 1) - pre[i]]);
		}
		AddTo(ans, sum);
		AddTo(sum, MOD - f[i - 1]), f[i - 1] = 0;
	}
	printf("%d\n", ans);
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		Solve();
	}
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：4)

[Problem Link](https://www.luogu.com.cn/problem/CF2048H)

**题目大意**

> 给定长度为 $n$ 的 01 串 $s$，每次操作可以选定一个 $i$，然后把 $s_1\sim s_i$ 替换成 $\max(s_1,s_2),\dots,\max(s_{i-1},s_i)$，求能得到多少本质不同字符串。
>
> 数据范围：$n\le 10^6$。

**思路分析**

可以发现最终的每个字符都对应原串一段区间的最大值，不妨设新串每个字符对应 $\max s[l_i,r_i]$。

观察一次操作后每个 $(l_i,r_i)$ 的变化情况，对于 $j\in[1,i)$，$(l_j,r_j)$ 会变成 $(l_j,r_{j+1})$。

仅观察 $l$ 数组，相当于删除 $l_i$，仅观察 $r$ 数组，相当于删除 $r_1$，因此原操作就是删除 $l_i,r_1$ 并重组所有 $(l,r)$。

那么在 $k$ 次操作之后，$r$ 数组一定是 $[k+1,k+2,\dots,n]$，而 $l$ 数组可以是 $[1,2,\dots,n]$ 的任意长度为 $n-k$ 的子序列。

翻转原串，此时 $l=[1,\dots,n-k]$，$r$ 是任意严格递增序列，因此我们判断一个字符串是否合法，只需要贪心地每次取最小合法的 $r$。

那么可以 dp：$f_{i,j}$ 表示选出前 $i$ 个字符，且 $r_i=j$ 的方案数。

如果 $s_i=0$ 且 $j<p$，那么 $f_{i,j}$ 转移到 $f_{i+1,p}$，其中 $p$ 是第一个大于 $i$ 且 $s_p=1$ 的位置，否则直接转移到 $f_{i+1,j+1}$。

需要一个支持整体平移区间求和的数据结构，直接树状数组维护。

时间复杂度 $\mathcal O(n\log n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e6+5,MOD=998244353;
char s[MAXN];
int n,nxt[MAXN];
struct FenwickTree {
	int dx,tr[MAXN*2],s;
	void init() { fill(tr,tr+2*n+1,0); }
	void add(int x,int v) { for(x+=dx;x<=2*n;x+=x&-x) tr[x]=(tr[x]+v)%MOD; }
	int qry(int x) { for(s=0,x+=dx;x;x&=x-1) s=(s+tr[x])%MOD; return s; }
}	F;
void solve() {
	cin>>(s+1),F.dx=n=strlen(s+1);
	reverse(s+1,s+n+1);
	F.add(0,1);
	int ans=0;
	nxt[n+1]=n+1;
	for(int i=n;i>=1;--i) nxt[i]=(s[i]=='1'?i:nxt[i+1]);
	for(int i=1;i<=n;++i) {
		--F.dx;
		if(s[i]=='0'&&nxt[i]<=n) {
			F.add(nxt[i],(F.qry(nxt[i]-1)+MOD-F.qry(i-1))%MOD);
		}
		ans=(ans+F.qry(n))%MOD;
	}
	cout<<ans<<"\n",F.init();
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int _; cin>>_;
	while(_--) solve();
	return 0;
}
```

---

## 作者：Eraine (赞：4)

来源：CF GR28   
编号：CF2048H  
tag：dp 优化  
难度：$\color{brown}{3174}$

观察操作，实际上是对序列产生如下两种变化之一：

- 若序列以 $1$ 开头，则将开头 $1$ 的连续段长度 $-1$。
- 将第一个 $0$ 的连续段到某一个 $0$ 的连续段执行 $0$ 段长度 $-1$，$1$ 段长度 $+1$。

不难发现 $0$ 段不可能碰到相遇的情况，所以每一段 $0$ 段都是独立的。而且发现对 $0$ 段执行 $-1$ 操作的次数从左往右递减。

但是考虑到第一个操作可能会对最后被删完的剩下的第一段 $1$ 长度产生影响，所以需要枚举最后状态的第一段存在 $0$ 的位置。对于枚举位置左边的方案数显然是一个区间，上下界是好求的。枚举右边位置需要满足执行 $-1$ 操作递减，所以考虑 dp。$f_{i,j}$ 表示从右到左第 $i$ 个 $0$ 连续段执行 $-1$ 操作的次数为 $j$ 的方案数。对于不同的 $i$，有用的 $j$ 大小不一定随 $i$ 递增，但是对于没用的 $j$ 直接从 $i-1$ 的状态复制即可。显然转移从 $f_{i-1,k}(k\le j)$，是一段连续区间。可以用树状数组优化。但是发现对于同一段区间有用转移不是动态更新的，所以可以用前缀和优化做到线性。（代码用了树状数组优化）

$\Theta(n)$。

[submission](https://codeforces.com/contest/2048/submission/297411890)

若有疑问和错误请指出，虚心接受您的意见。

---

## 作者：Daniel1234 (赞：3)

## 思路

~~或许是更容易理解的思路。~~

先考虑转换操作，可以转化成如下形式：

每次选择一个 $i \in \left [ 1, n \right ) \cap N$，然后对于 $1 \sim i$ 这一个前缀右移 $1$ 位并与原数组取或，最后删除开头。

这又等价于对于每个 $1$ 的连续段每次可以选择一个前缀并往右延伸 $1$ 格，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/nyry1m4i.png)

考虑如何统计方案，先枚举操作次数。对于操作了 $i$ 次的序列，我们只保留最后 $n-i$ 位，然后对于这之中每个 $0$ 的连续段，我们都要统计有几种方案是本质不同的覆盖方式，也就是至少有一个 $1$ 的连续段延续了更长的距离。

同时我们还要保证从前往后每个 $1$ 连续段延伸的长度单调不增，因为我们每次操作的是一个前缀。

使用 $dp_{i,j}$ 表示已经做完了第 $i$ 个及之后的 $0$ 的连续段，此时的延伸长度是 $j$ 的方案。

记 $len_i$ 表示第 $i$ 个 $0$ 连续段的长度，则有如下转移：

$dp_{i,j} = \sum_{k=0}^{j} dp_{i+1,k} \times \left  ( 1 - \left [j > len_i \right ] \times \left [k < j \right ] \right )$

求答案是简单的，我是把可能被 $i$ 断开的 $0$ 的连续段单独计算了，或许有更好的写法可以规避掉这一过程。

写完后优化是容易的，最后我使用了一颗线段树维护单点修改，区间查询。

时间复杂度：$O(n \log n)$。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define mod (int)(998244353)
int T, n;
string s;
int dp[1000005];
int bel[1000005];
int len[1000005];
struct point{
    int s, s2, len;
}f[4000005];
point operator+(point x, point y){
    point ans;
    ans.len = x.len + y.len;
    ans.s = (x.s + y.s) % mod;
    ans.s2 = (x.s2 + x.s * y.len % mod + y.s2) % mod;
    return ans;
}
void up(int now){
    f[now] = f[now * 2] + f[now * 2 + 1];
}
void init(int now, int l, int r){
    f[now].s = 0;
    f[now].s2 = 0;
    f[now].len = r - l + 1;
    if(l == r)return;
    int mid = l+r>>1;
    init(now * 2, l, mid);
    init(now * 2 + 1, mid + 1, r);
    up(now);
}
void chg(int now, int l, int r, int x, int y){
    if(l == r){
        f[now].s += y;
        f[now].s %= mod;
        f[now].s2 += y;
        f[now].s2 %= mod;
        return;
    }
    int mid = l+r>>1;
    if(x <= mid)chg(now * 2, l, mid, x, y);
    else chg(now * 2 + 1, mid + 1, r, x, y);
    up(now);
}
point qry(int now, int l, int r, int x, int y){
    if(x > y){
        return point{0,0,0};
    }
    if(x <= l && r <= y){
        return f[now];
    }
    int mid = l+r>>1;
    if(x <= mid && y > mid)return qry(now * 2, l, mid, x, y) + qry(now * 2 + 1, mid + 1, r, x, y);
    if(x <= mid)return qry(now * 2, l, mid, x, y);
    return qry(now * 2 + 1, mid + 1, r, x, y);
}
int Pre[1000005][2];
int suf[1000005][2];
int now[2];
signed main(){  
    cin >> T;
    while(cin >> s){
        n = s.size();
        s = " " + s;
        int tot = 0;
        for(int i = 1; i <= n; i++){
            if(s[i] == '0'){
                int en = i;
                while(en < n && s[en + 1] == s[en])en++;
                len[++tot] = en - i + 1;
                for(int j = i; j <= en; j++)bel[j] = tot;
                i = en;
            }
        }
        now[0] = now[1] = 0;
        for(int i = 1; i <= n; i++){
            now[s[i]-'0'] = i;
            Pre[i][0] = now[0], Pre[i][1] = now[1];
        }
        now[0] = now[1] = n + 1;
        for(int i = n; i >= 1; i--){
            now[s[i]-'0'] = i;
            suf[i][0] = now[0], suf[i][1] = now[1];
        }
        init(1, 0, n);
        chg(1, 0, n, 0, 1);
        // dp[0] = 1;
        int z = tot + 1;
        int ans = 0;
        for(int i = n; i >= 1; i--){
            int nxt = suf[i][1];
            // for(int j = i; j <= n; j++){
            //     if(s[j] == '1'){
            //         nxt = j;
            //         break;
            //     }
            // }
            int pre = Pre[i-1][1];
            // for(int j = i-1; j > 0; j--){
            //     if(s[j] == '1'){
            //         pre = j;
            //         break;
            //     }
            // }
            int nnxt = n + 1;
            if(nxt+1 <= n)nnxt=suf[nxt+1][0];
            // for(int j = nxt+1; j <= n; j++){
            //     if(s[j] == '0'){
            //         nnxt = j;
            //         break;
            //     }
            // }
            if(nnxt == n + 1){
                if(pre){
                    ans += max(0ll, min(pre + i - 1, nxt-1) - i + 2);
                }else{
                    ans++;
                }
            }else{
                int j = bel[nnxt];
                while(z > j){
                    z--;
                    for(int p = len[z]; p > 0; p--){
                        chg(1, 0, n, p, qry(1, 0, n, 0, p - 1).s);
                        // for(int k = 0; k < p; k++){
                        //     dp[p] += dp[k];
                        //     dp[p] %= mod;
                        // }
                    }
                }
                int res = 0;
                if(!pre || s[i] == '1'){
                    res += qry(1, 0, n, 0, i - 1).s;
                    // for(int high = 0; high < i; high++){
                    //     res += dp[high];
                    // }
                }else{
                    int L = i-pre, R = min(nxt-pre,i);
                    if(L <= R){
                        res += (R-L+1) * qry(1, 0, n, 0, i - pre - 1).s % mod;
                    }
                    L = max(0ll,i-pre), R = i - 1;
                    if(L <= R){
                        int high = L;
                        int num = max(0ll, min(nxt-pre,i) - high-1)+1;
                        int en = min(L+num-1, R);
                        res += qry(1, 0, n, L, en).s2;
                        res += qry(1, 0, n, en+1, R).s;
                    }
                    // for(int high = max(0ll,i-pre); high < i; high++){
                    //     res += dp[high];
                    //     for(int num = high+1; num < min(nxt-pre,i); num++)res += dp[high];
                    // }
                }
                res %= mod;
                ans += res;
            }
        }
        ans %= mod;
        cout << ans << '\n';
    }
    return 0;
}
```

---

## 作者：irris (赞：2)

> Little09 有一个 $\tt 01$ 串 $s$，一次操作选择一个 $1 \leq k \leq |s|$，然后对于每个 $1 \leq i < k$ 同时让 $s_i = \max(s_i, s_{i+1})$，然后删去 $s_k$。请问他能生成多少个不同的 $\tt 01$ 串，答案对 $998244353$ 取模。

解决这种问题不算重复的唯一方法只有一个字符一个字符加入。显然从后往前做是不太有后效性的，而从前往后就不太好处理了。所以从后往前。

设计 dp。设 $f_{i, j}$ 表示，满足下列条件的 $\tt 01$ 串 $s'$ 的数量：

- $s'$ 可以被 $s[i \dots n]$ 生成，并且不能被 $s[(i + 1) \dots n]$ 生成。
	- 我们做出这一步的动机就在于，因为我们可以把一个前缀随意删掉而不影响后缀，所以可以对于一个最短后缀进行 dp。这样就把许多不同的串压缩到了一起。
- 需要恰好进行 $j$ 次操作才能由后缀 $s[i \dots n]$ 得到 $s'$。显然 $j$ 是唯一的。

我们将证明，对于判定，首先我们同样先把两个串 reverse，然后一个贪心考虑匹配的策略便是对的：

> 这里先不展开写了，可以简单感性理解，大概就是如果匹配 $i$ 增加，$j$ 也增加，那么 $\tt 1$ 的连续段长度不减，而 $\tt 0$ 的连续段长度不增，之类的。  
> 因此我们只记录 $s'$ 于 $(i, j)$ 就足够了，对于 $(i + 1, j + 1)$ 其实都一样，反而在后续匹配 $\tt 0$ 的时候可能更加不优（而且不符合我们的状态设计）。

所以我们考虑在 $s'$ 左边能加入什么字符。如果 $s_{i-1} = \tt 1$，显然只能是 $\tt 1$，$f_{i,j} \to f_{i-1, j}$；否则，设 $s_{i-1}$ 向左共有 $k$ 个 $\tt 0$，那么由于后缀已经被操作了 $j$ 次，首先这个连续段的长度最多只有 $\max(k - j, 0)$ 了，那么只有 $j < k$ 的状态有用，别的都形如 $f_{i,j} \to f_{i-1, j}$，而 $\sum k = \mathcal O(n)$！

考虑 $0 \leq j < k$ 的状态具体应该如何转移，首先你会先得到 $j$ 个无法避开的 $\tt 1$，根据上述陈述，这都是无法避免的；然后剩下的 $\tt 0$ 每花费一次操作都可以减少一个，同步转移给 $i - k - 1$ 的位置，也就是说等价于进行

$$f_{i-k-1, j} \gets \sum_{w=0}^j f_{i-k, w}\ (0 \le j \leq k)$$

也即前缀和，于是做完了。

```cpp
#include <bits/stdc++.h>

constexpr int MOD = 998244353;
inline void add(int &x, int y) { (x += y) >= MOD && (x -= MOD); }

#define MAXN 1000001
int a[MAXN];
int main() {
	std::string s; std::cin >> s;
	int n = s.size(), ans = 0, sum = 0;
	std::reverse(s.begin(), s.end());
	a[0] = 1, sum = 1;
	for (int i = 0, k = 0; i < n; ++i) {
		if (s[i] == '0') ++k; else {
			for (int v = 1, pre = 1, t; v <= k; ++v) 
				t = pre, add(pre, a[v]), add(a[v], t), add(sum, t);
			k = 0;
		}
		add(ans, sum);
	}
	std::cout << ans << '\n';
	return 0;
}
```

---

## 作者：Otomachi_Una_ (赞：1)

我们先把整个序列反转。每个数 $a'_i$ 对应的肯定是原序列一个 $i$ 为左端点的区间的最大值。记为 $a_i'=\max a[i,r_i]$。

考虑 $r_i$ 的变化。实际上一开始都有 $r_i=i$，一次操作实际上就是删除了某个 $r_x$，然后把后面的 $r$ 往前靠。那么 $r_i$ 序列的取值就是值域 $[1,n]$ 之间所有的递增数列。

假设 $len_i=r_i-i+1$，那么 $len_i$ 是不降的。

考虑怎么判断 $a_i'$ 能否通过原序列 $a_i$ 通过操作取得？假设 $b_i$ 表示最小的自然数使得 $a_{i+b_i-1}=1$，不存在则为 $-1$。

维护 $len$ 初始为 $1$。对每个 $i=1,2,\dots,|a'|$ 执行以下算法：

- 如果 $a'_i=0$，那么如果 $len\geq b_i$ 则无解。否则不作操作。
- 如果 $a_i'=1$，如果 $len\leftarrow \max(len,b_i)$，如果 $b_i=-1$ 则无解。

通过执行上面的算法，我们就成功判断了 $a'$ 能否被操作出来。且这个算法唯一对应了一个 $\{len\}$ 数组。

考虑对这个 $len$ 数组进行 dp。假设 $f_{i,j}$ 表示考虑到 $a_{1\sim i}$，此时 $len_i=j$ 的序列数量。考虑 $a_{i+1}$ 带来的转移：

- 如果 $a_{i+1}=1$，那么相当于 $f_{i+1,j}\leftarrow^{+}f_{i,j}$（$j> f_{i+1}$），$f_{i+1,j}\leftarrow^+ \sum_{k\leq j}f_{i,k}$（$j=f_{i+1}$）；
- 如果 $a_{i+1}=0$，相当于 $f_{i+1,j}\leftarrow^{+}f_{i,j}$（$j<f_{i+1}$）。

注意到实际上只有 $f_{i+1,f_{i+1}}$ 和 $f_{i,f_{i+1}}$ 不同，其具体变化为增加了 $\sum_{k=1}^{f_{i+1}-1}f_{i,k}$。通过树状数组维护 $f_{i,*}$ 即可。

期数注意到 $\sum |b_i-b_{i+1}|$ 是 $O(n)$ 的能直接做到 $O(n)$。

---

## 作者：happybob (赞：1)

题意：

给定一个长度为 $n$ 的 $\texttt{01}$ 字符串 $s$，你可以进行任意（可以为 $0$）次操作。特别地，若字符串已经为空，你不能进行操作。

每次操作为：

假设目前串长度为 $m$，选择整数 $1 \leq p \leq m$，然后对于 $1 \leq i < p$，同时执行 $s_i \gets \max(s_i,s_{i+1})$，然后删除 $s_p$。

问能得到的本质不同非空字符串数量，答案对 $998244353$ 取模。

$1 \leq n \leq 10^6$，$2$ 秒。

解法：

操作很奇怪，考虑对于给定字符串 $t$，能否判定其能被操作得到。

首先有显然的性质，$t$ 中每个字符对应 $s$ 的一个区间的 $\max$。这些区间可能有交。

考虑所有区间，初始有 $l_i=r_i=i$，即每个区间都为 $[i,i](1 \leq i \leq n)$，考虑执行一次操作，我们手动模拟一下可以发现，操作的字符对应区间的后面区间不变，操作区间前面的区间左端点不变，右端点变成后一个区间的右端点。进一步地，可以发现假设操作了 $x$ 次，则右端点必然恰好覆盖了 $(x,n]$，左端点可以任意选择 $n-x$ 个位置。

于是判定性问题可以贪心，假设进行了 $k$ 次操作，从后往前枚举字符，维护目前的左端点指针，每次往前找第一个需要的字符即可。

然后过程比较简单，发现贪心的过程只维护了操作次数和最大的左端点。考虑 DP，记 $f_{i,j}$ 表示操作 $i$ 次，贪心得到左端点为 $j$ 的方案数。直接转移是 $O(n^2)$ 的，无法通过。但是仔细观察转移发现是整体平移和单点修改，维护线段树即可。复杂度 $O(n \log n)$。

[Submission Link.](https://codeforces.com/contest/2048/submission/297455770)

---

## 作者：ax_by_c (赞：0)

模拟赛 T2。场切 *3100 祭。

考虑判定，设原串结尾为 $x$，最终串结尾为 $y$。

- $x=y$，直接将它们删去。

- $x=1,y=0$，无法将原串结尾变成 0，因此不合法。

- $x=0,y=1$，对原串结尾进行操作。

考虑 DP，设 $f_{i,j}$ 为判定过程进行到第 $i$ 个位置且操作了 $j$ 次的最终串个数。

记 $pre_i$ 为 $1\sim i$ 中最后的 1 的位置，$sum_i$ 为 $1\sim i$ 中 1 的个数。

- $f_{i,j}\rightarrow f_{i-1,j}$。
 
- $sum_{i+j}=sum_{i-1},pre_i\neq 0$ 时 $f_{i,j}\rightarrow f_{pre_i-1,j+i-pre_i}$。

答案即为 $\sum_{i,j} f_{i,j}-1$。

考虑优化，注意到：

- $s_i=s_{i+1}=0$ 时，$f_i=f_{i+1}$。

- 对于 1 前面的 0 和可能的最后一个 0 的位置，$\sum i-pre_i=O(n)$。

于是可以只关心这些位置，并考虑把 $f_{i'\in[pre_i+1,i],j}$ 的转移放到 $f_{i,j}$ 做。

此时发现每个 $f_{i,j}$ 转移到的 $f_{pre_i-1,j'}$ 中 $j'\in [j+1,i-pre_i]$，使用差分优化同时维护 $\sum_j f_{i,j}$ 即可。

时间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define rep(i,l,r) for(int i=(l),qwp=(r);i<=qwp;i++)
#define per(i,r,l) for(int i=(r),qwp=(l);i>=qwp;i--)
#define repll(i,l,r) for(ll i=(l),qwp=(r);i<=qwp;i++)
#define perll(i,r,l) for(ll i=(r),qwp=(l);i>=qwp;i--)
#define pb push_back
#define clr clear
#define ins insert
#define uset unordered_set
#define umap unordered_map
using namespace std;
namespace ax_by_c{
typedef long long ll;
const ll mod=998244353;
const int N=1e6+5;
int n,sum[N],pre[N];
char s[N];
ll ans,f[N],d[N],S;
void slv(){
    scanf("%s",s+1);
    for(int i=1;s[i];i++)n=i;
    rep(i,1,n){
        sum[i]=sum[i-1]+(s[i]=='1');
        pre[i]=(s[i]=='0')?(pre[i-1]):(i);
    }
    ans=0,S=1;
    rep(i,0,n)f[i]=d[i]=0;
    f[0]=1;
    per(i,n,0){
        if(s[i]=='1'){ans=(ans+S)%mod;continue;}
        if(!pre[i]){ans=(ans+S*(i+1)%mod)%mod;break;}
        ans=(ans+S*(i-pre[i]+1)%mod)%mod;
        per(j,i-pre[i]-1,0)d[j+1]=(d[j+1]+f[j])%mod;
        rep(j,1,i-pre[i])d[j]=(d[j]+d[j-1])%mod,f[j]=(f[j]+d[j])%mod,S=(S+d[j])%mod,d[j-1]=0;
        d[i-pre[i]]=0;
        i=pre[i];
    }
    ans=(ans-1+mod)%mod;
    printf("%lld\n",ans);
}
void main(){
    int T;
    scanf("%d",&T);
    while(T--)slv();
}
}
int main(){
    ax_by_c::main();
    return 0;
}
/*
g++ -std=c++14 -O2 -Wall -Wextra "-Wl,--stack=200000000" string.cpp -o string.exe
string.exe
*/
```

---

