# [ARC157F] XY Ladder LCS

## 题目描述

给定两个由 `X` 和 `Y` 组成、长度为 $N$ 的字符串 $S$ 和 $T$。对于每个 $i=1,2,\dots,N$，你可以自由选择是否交换 $S$ 和 $T$ 的第 $i$ 个字符。这样一来，最终可以得到 $2^N$ 种不同的字符串对。请你求出这些字符串对的所有**公共子序列**（不要求连续）中最长的一个。如果有多个长度相同的公共子序列，请输出其中**字典序最小**的那个。

公共子序列的定义如下：字符串 $S$ 的**子序列**是指从 $S$ 中删除 $0$ 个或多个字符后，按原顺序排列剩下的字符所得到的字符串。字符串 $S$ 和 $T$ 的**公共子序列**是指既是 $S$ 的子序列又是 $T$ 的子序列的字符串。（也可以参考样例 1 的说明。）

## 说明/提示

## 限制条件

- $1 \leq N \leq 50$
- $S$ 和 $T$ 均为由 `X` 和 `Y` 组成的长度为 $N$ 的字符串。

## 样例解释 1

- 如果不交换任何字符，`XXX` 和 `YYY` 的公共子序列只有空字符串。
- 如果只交换第 1 个字符，`YXX` 和 `XYY` 的公共子序列有：空字符串、`X`、`Y`。
- 如果只交换第 2 个字符，`XYX` 和 `YXY` 的公共子序列有：空字符串、`X`、`Y`、`XY`、`YX`。
- 如果只交换第 3 个字符，`XXY` 和 `YYX` 的公共子序列有：空字符串、`X`、`Y`。
- 交换 2 个或更多字符的情况，可以通过交换 $S$ 和 $T$ 本身来等价地考虑上述情况。
- 因此，可能的最长公共子序列为 `XY` 和 `YX`，其中字典序最小的是 `XY`，所以答案为 `XY`。

## 样例解释 2

答案也可能是空字符串。

## 样例解释 3

例如，如果只交换第 2 个字符，可以得到 `XYY` 作为公共子序列。不存在更长的公共子序列，也不存在长度相同且字典序更小的公共子序列，因此答案为 `XYY`。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
XXX
YYY```

### 输出

```
XY```

## 样例 #2

### 输入

```
1
X
Y```

### 输出

```
```

## 样例 #3

### 输入

```
4
XXYX
YYYY```

### 输出

```
XYY```

# 题解

## 作者：dehsirehC (赞：16)

提供一种简单、套路、易懂且时间复杂度比题解优秀的做法。 ~~`AtCoder rating` 太低只能在洛谷写题解了。~~

考虑求 `最长公共子序列` 的那个 `dp` ，设 $f_{i,j}$ 表示两个序列分别前 $i,j$ 个字符，它们的 `最长公共子序列` 。

考虑拓展到这一问题，状态新增一个 $S$ 表示下标为 $(\min(i,j),\max(i,j)]$ 的 `XY` 位置是否交换。

`dp` 的值为字典序最小的 `最长公共子序列` ，这个可以压成一个 `long long` 直接存储取 $\min$ ， $O(1)$ 转移是显然的。

考虑时间复杂度，设 `最长公共子序列` 的长度为 $l$ ，若 $n-|i-j|<l$ 则可以不 `dp` 它，因为它不可能成为答案。

由于任意三个位置都必定能匹上两个，故 $l\ge \lfloor\frac{2}{3}n\rfloor$ ，事实上这个界是可以达到的，构造如下。

```
XXYXXYXXY...
YXYYXYYXY...
```

由于 $l\ge \lfloor\frac{2}{3}n\rfloor$ ，故 $|i-j|\le n-l\le \lceil\frac{1}{3}n\rceil$ ，也就是总的状态数或者说总时间复杂度不超过 $O(n2^{\frac{n}{3}})$ 。

这个界很松，例如上述这一构造， $i,j$ 之间的 `XY` 数量大概不超过 $(\frac{1}{3})^2 n$ ，即上述构造总时间复杂度 $O(n2^{\frac{n}{9}})$ 。

继续挖掘它的性质，设刚开始的字符串的每个位置均为 `XY` ，考虑将一个 `XY` 的位置变成 `XX/YY` 会发生什么。

初始时 $l=n-1$ ，每改变两个位置会使 $l$ 减小 $1$ ，而这需要满足连续三个位置不全为 `XX/YY` ，否则无法减小 $1$ 。

设有 $k$ 个 `XX/YY` 的位置，则 $l$ 大概至多是 $n-\frac{k}{2}$ ，接下来考虑 $i,j$ 之间最多有多少个 `XY` 这种位置。

一个显然的思路就是假设 $i,j$ 之间全部为 `XY` ，那么 $|i-j|$ 最大约为 $\min(\frac{k}{2},n-\frac{3}{2}k)$ ， $k$ 取到 $\frac{n}{2}$ 时该式取到 $\frac{n}{4}$ 。

容易发现 $k$ 比 $\frac{n}{2}$ 小时 $n-l$ 太小达不到 $\frac{n}{4}$ ，比 $\frac{n}{2}$ 大时 $|i-j|$ 虽然可以很大但中间的 `XY` 位置很少。

具体的构造就是前面大概 $\frac{n}{4}$ 个位置为 `XY` ，剩余的位置为上面那个构造，此时总时间复杂度 $O(2^{\frac{n}{4}})$ ，达到上界。

至于 $l$ 如何得到就直接 `贪心` 即可，具体就是记录前面能保留什么字符，直接一位一位暴力 `贪心` 匹配即可。

事实上常数很大，但可以轻松跑过 $n=50$ ，只需要 $8\ \text{ms}$ ，目前在 `AtCoder` 上是最优解，可以 $200\ \text{ms}$ 内跑出 $n=80$ 。

随机数据下跑得非常快，大概可以在 $10\ \text{ms}$ 以内跑出 $n=120$ ， $n$ 更大的话 `__int128` 会存不下。[代码](https://atcoder.jp/contests/arc157/submissions/39330696)。

---

## 作者：DaiRuiChen007 (赞：5)

[Problem Link](https://www.luogu.com.cn/problem/AT_arc157_f)

**题目大意**

> 给定两个长度为 $n$ 的 01 串 $s,t$，你可以交换若干对 $(s_i,t_i)$，最大化 $\mathrm{LCS}(s,t)$ 并输出之，如有多解输出字典序最小的一个。
>
> 数据范围：$n\le 50$。

**思路分析**

首先对于每一对匹配的 $s_i,t_j$，可以通过交换 $(s_i,t_i),(s_j,t_j)$， 使得所有 $i<j$。

那么我们有一个暴力的做法：维护 $dp_{i,Q}$，表示考虑到了 $s[1,i]$，设最后一次匹配是 $s_j,t_k$，那么 $t[k+1,i]=Q$。

转移时枚举是否交换，是否匹配，如果把当前的 $s_i$ 匹配了，那么就从 $Q$ 的前面开始往后找，找到第一个 $Q_p=s_i$，然后删掉 $Q[1,p]$。

这样复杂度是 $\mathcal O(n2^n)$ 的，难以通过。

观察到答案看起来比较大，事实上可以通过暴力枚举证明对于连续的 $3$ 个位置，无论他们怎么排序，都有一种操作方式使得他们的 $\mathrm{LCS}\ge2$。

因此答案 $\ge 2\left\lfloor\dfrac n3\right\rfloor$，因此 $|Q|\ge \left\lceil\dfrac n3\right\rceil$ 一定不是最优解，那么此时状态数就优化到了一个可以接受的范围。

根据题目的要求，我们要按长度为第一关键字，字典序为第二关键字比较信息，显然 可以在最高位前面加一个 $1$ 作为符号位，那么符号位越高说明长度越大，为了求字典序最小值，把其他位 01 翻转即可，同理 $Q$ 也能这么表示。

时间复杂度：$\mathcal O(n2^{n/3})$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int S=1<<19;
ll f[S],g[S];
int n,tr[S<<1][2];
char a[55],b[55];
void upd(ll &x,ll y) { x=x>y?x:y; }
signed main() {
	scanf("%d%s%s",&n,a+1,b+1);
	for(int s=1;s<(S<<1);++s) for(int c:{0,1}) { //target=j
		int p=__lg(s)-1;
		for(;~p&&((s>>p)&1)!=c;--p);
		if(p==-1) tr[s][c]=-1;
		else tr[s][c]=(s&((1<<p)-1))|(1<<p);
	}
	f[1]=1;
	for(int i=1;i<=n;++i) {
		memset(g,0,sizeof(g));
		int x=(a[i]=='X'),y=(b[i]=='X');
		for(int s=1,t;s<S;++s) if(f[s]) {
			t=s<<1|x;
			if(~tr[t][y]) upd(g[tr[t][y]],f[s]<<1|y);
			if(t<S) upd(g[t],f[s]);
			t=s<<1|y;
			if(~tr[t][x]) upd(g[tr[t][x]],f[s]<<1|x);
			if(t<S) upd(g[t],f[s]);
		}
		memcpy(f,g,sizeof(f));
	}
	ll s=*max_element(f,f+S);
	for(int i=__lg(s)-1;~i;--i) putchar("YX"[(s>>i)&1]); puts("");
	return 0;
}
```

---

## 作者：installb (赞：4)

[题目链接](https://www.luogu.com.cn/problem/AT_arc157_f)

这个题看起来有些无从下手，LCS、01 串、字典序，看起来有很多切入点。

看到数据范围是 $N=50$。这个数据范围和一般的 LCS 题不符合，我们可以考虑一下这个数据范围，是否为 $N^5$ 或 $N^6$？看起来不太像。那会不会是指数，例如 $2^{\frac{N}{2}}$？很有可能，因为指数和本题中 **对于每个位置选择是否交换** 是相匹配的。

我们考虑 **结合指数枚举和 dp 求 LCS 的过程**。直接 dp 做这个题。

考虑一般的 LCS 是 $f_{i,j}$ 代表 $S_{1\dots i}$ 和 $T_{1\dots j}$ 的 LCS，然后转移到 $f_{i+1,j},f_{i,j+1},f_{i+1,j+1}$。

这里加上了可以交换的条件，于是我们加上大小为 $S=2^{|i-j|}$ 的一维，表示下标从 $i+1$ 到 $j$ 的这些位置是否交换，因为只有这些位置会影响当前 dp 的状态，$j$ 以后的还没有确定状态，$i$ 及以前的已经确定状态。状态变为 $f_{i,j,S}$，转移仍为 $O(1)$，时间复杂度 $N^22^N$。

我们猜测 dp 的过程中 $|i-j|$ 不需要很大就可以得出正确答案。根据 LCS 的转移方式可以发现，**如果 LCS 的长度为 $N-k$ 那么 $|i-j|$ 只需要枚举到** $k$。我们可以猜测答案实际上比较大，和 $N$ 很接近，事实上确实是这样。

（实际上做这题的时候，我是先注意到答案很大，至少是 $\frac{N}{2}$，再去考虑如何 dp 的。）

当然证到 $\frac{N}{2}$ 并不够。实际上我们可以进一步发现，LCS 的**长度至少**是 $2\left\lfloor\frac{N}{3}\right\rfloor$。

我们直接把原串每三个字母分一段，可以发现任意两个长度为 $3$ 的串在允许交换的情况下都可以得到长度为 $2$ 的 LCS。然后我们把得到的 LCS 拼起来，就可以取到这个界

- 存在一个字母在两串中出现 $\ge 4$ 次：一定可以通过交换使得该字母分别在两串中各出现两次，然后取两个该字母组成 LCS。
- `X` 和 `Y` 各出现 $3$ 次。
  - 如果存在一个位置 $S_i=T_i$，那么一定有另一个位置也满足 $S_i=T_i$ 且为另一个字母，否则无法达到 `X` 和 `Y` 各出现 $3$ 次的条件，这种情况下不交换就可以。
  - 所有位置 $S_i\neq T_i$，实际上这是一种情况。我们随便交换一下，组出来一个 `XY` 或 `YX` 的 LCS 都是可以的。

当然大家都不喜欢分类讨论，所以可以直接写个代码直接枚举所有情况。这样的话你也会发现四个字母分一段就不能保证得到长度为 $3$ 的 LCS 了。

$N=50$ 时最后两个数会落单，不过这两个数分一组也可以。所以本题差值取 $17$ 即可，我代码里写的 $16$ 但也过了。

接下来是输出方案。这题要求字典序最小，因为这题写不了 spj，我们可以用一个 `long long` 类型整数压缩存储整个串。用一个 `pair <int,long long>` 作为 dp 数组的类型。长度是第一关键字，字典序是第二关键字即可。

时间复杂度 $O(N^22^{\frac{N}{3}})$。可以通过本题。

代码写的太繁杂了，写的不好仅供参考。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1000005;

const int K = 16;

int s[55],t[55];
pair <int,ll> f[2][55][(1 << K) + 5];

void solve(){
    int n; string ss,st;
    cin >> n >> ss >> st;
    ss = ' ' + ss; st = ' ' + st;
    for(int i = 1;i <= n;i ++){
        s[i] = (ss[i] == 'X');
        t[i] = (st[i] == 'X');
    }
    int nxt = 1,cur = 0;
    for(int i = 0;i < n;i ++){
        for(int j = 1;j <= n;j ++){
            for(int S = 0;S < (1 << K);S ++){
                f[nxt][j][S] = {0,0ll};
            }
        }
        for(int j = max(i - K,0);j < i;j ++){
            for(int T,S = 0;S < (1 << (i - j));S ++){
                for(int c = 0;c <= 1;c ++){
                    T = (S | (c << (i - j))) >> 1;
                    if(((S & 1) ? s[j + 1] : t[j + 1]) == (c ? t[i + 1] : s[i + 1])){
                        int ch = (S & 1) ? s[j + 1] : t[j + 1];
                        pair <int,ll> to = {f[cur][j][S].first + 1,(f[cur][j][S].second << 1) | ch};
                        if(to > f[nxt][j + 1][T]) f[nxt][j + 1][T] = to;
                    }
                    T = S | (c << (i - j));
                    if(i - j < K && f[cur][j][S] > f[nxt][j][T]) f[nxt][j][T] = f[cur][j][S];
                    T = S >> 1;
                    if(f[cur][j][S] > f[cur][j + 1][T]) f[cur][j + 1][T] = f[cur][j][S];
                }
            }
        }
        
        if(s[i + 1] == t[i + 1]){
            int ch = s[i + 1]; pair <int,ll> to = {f[cur][i][0].first + 1,(f[cur][i][0].second << 1) | ch};
            if(to > f[nxt][i + 1][0]) f[nxt][i + 1][0] = to;
        }

        for(int j = i;j <= min(n,i + K);j ++){
            for(int T,S = 0;S < (1 << (j - i));S ++){
                for(int c = 0;c <= 1;c ++){
                    T = (S | (c << (j - i))) >> 1;
                    if(i != j && ((S & 1) ? s[i + 1] : t[i + 1]) == (c ? t[j + 1] : s[j + 1])){
                        int ch = (S & 1) ? s[i + 1] : t[i + 1];
                        pair <int,ll> to = {f[cur][j][S].first + 1,(f[cur][j][S].second << 1) | ch};
                        if(to > f[nxt][j + 1][T]) f[nxt][j + 1][T] = to;
                    }
                    T = S >> 1;
                    if(f[cur][j][S] > f[nxt][j][T]) f[nxt][j][T] = f[cur][j][S];
                    if(j < n && j - i < K){
                        T = S | (c << (j - i));
                        if(f[cur][j][S] > f[cur][j + 1][T]) f[cur][j + 1][T] = f[cur][j][S];
                    }
                }
            }
        }
        swap(nxt,cur);
    }
    pair <int,ll> ans = {0,0ll};
    for(int S = 0;S < (1 << K);S ++){
        if(f[cur][n][S] > ans) ans = f[cur][n][S];
    }
    for(int i = ans.first - 1;i >= 0;i --){
        cout << (((ans.second >> i) & 1) ? 'X' : 'Y');
    }
    cout << '\n';
}

int main(){
    ios::sync_with_stdio(false);
    solve();
    return 0;
}
```

好题，强推 ARC。

---

## 作者：SFlyer (赞：2)

[link to problem](https://atcoder.jp/contests/arc157/tasks/arc157_f)

观察数据范围：$1\le N\le 50$。

如果是 $20$，想到 $2^{20}$；如果是 $40$，想到 $2^{40\div 2}$；若果是 $50$ 呢？$2^{25}$ 有点大，于是想到 $2^{50\div 3}$。但是如何去凑？

**Hint**

| $N$ | $S$ | $T$ | $res$ |
| :------------: | :------------: | :------------: | :------------: |
| $6$ | $\tt{XXXXXX}$  | $\tt{YYYYYY}$  | $\tt{XYXYX}$  |
| $8$ | $\tt{XXXXXXXX}$ | $\tt{XXXXXXXX}$  | $\tt{XXXXXXXX}$  |
|  $20$ | $\tt{YYYXYYXXXXXYYXYYXXXY}$  |  $\tt{YXYYXXXYYXYYYYYYXXYY}$ |  $\tt{YYYXYXXYXXYYYYYXXY}$ |

备注：第一行是最坏情况，第二行最好，第三行随机。

答案长度都很大？再看看。最小长度多少？


> lemma: 答案 $\ge \lfloor \frac{2N}{3}\rfloor$。

证明：$N=3k+r$证明长度是 $3$ 的答案 $\ge 2$ 和 $r$ 的部分。

- 长度为 $1$。最坏 $S=\tt{X},T=\tt{Y}$，答案是 $0$。

- 长度为 $2$。若有一个相同，答案 $\ge 1$；若都不相同即 $S=\tt{XX},T=\tt{YY}$，可交换使答案为 $2$。

- 长度为 $3$。第一个和第三个若有一个相同，转化为 长度为 $2$ 的加上 $1$，答案显然 $\ge 2$；都不相同，若第二个相同（$S=\tt{XXX},T=\tt{YXY}$）或不相同（$S=\tt{XXX},T=\tt{YYY}$），均可答案 $\ge 2$。

考虑 $r$ 是几。

- $r=0$ 显然 答案 $\ge \lfloor \frac{2N}{3}\rfloor$。

- $r=1$，$1\times 2$ 对除 $3$ 下取整没有影响。

- $r=2$，$2\times 2$ 贡献一个 $1$，正好。

即证。

> lemma $2$: 如果将两个数匹配，若设第一个是 $S$ 的第 $i$ 位，第二个 $T$ 的第 $j$ 位，那么 $\mid i-j \mid\le \frac{N}{3}$。

证明：若不满足，上面的 lemma 就不满足了。

我们得到了一个 $\frac{N}{3}$。看来，$2^{50\div 3}$ 凑好了？考虑状压 dp？

此后令 $l=\frac{N+2}{3}+1$。设计一个 dp 状态。设 $dp_{i,msk}$ 代表 $S,T$ 匹配到第 $i$ 位了，现在没有用上的是 $msk$。

在转移之前，先弄清如何将一个 $\tt{XY}$ 串 encode 成 $01$ 串的 $msk$。考虑到：

- 答案要求在长度最长的基础下，字典序最小的。

- $01$ 串长度得记录，否则会出现不同字符串对应相同的 $01$ 串。

现在有两个选择：

- $\texttt{X}=0,\texttt{Y}=1$，dp 时求 min。

- $\texttt{X}=1,\texttt{Y}=0$，dp 时求 max。

显然第二种更好处理长度的记录。为了让更长的长度更优，在最前面的一位放上一个 $1$。

**一些栗子**

|  字符串 |  对应的 $msk$ |
| :------------: | :------------: |
|  $\tt{XXX}$ | $1111$  |
|  $\tt{YY}$ | $100$  |
|  $\tt{YX}$ |  $101$ |

> lemma $3$: 如果你要用 $msk$ 里面的东西来匹配 $i+1$，那么越往前的越优。

证明：显然的贪心。

这样我们来预处理一下对于每一个 $msk$，现在要匹配一个 $a$，加上一个 $b$，会怎样。

**具体实现**

令 $to_{msk,a,b}$ 是预处理的答案。

- $a=0$。找到除了第一位第一个 $0$，把前面的全删除，左移 $1$，或上 $b$。

- $a=1$。找到除了第一位第一个 $1$，把前面的全删除，左移 $1$，或上 $b$。

**这一部分 code**

```cpp
void init(){
	// to_{msk,a,b}: you have msk, you want to get one a, you add b.
	for (ll msk=1; msk<(1<<l); msk++){
		ll len=0;
		while ((msk^(1<<len))>(1<<len)){
			len++;
		}
		len--;
		ll cur=len;
		while (~cur && (msk&(1ll<<cur))>0){
			cur--;
		}
		if (~cur){
			to[msk][0][0]=((msk&((1ll<<cur)-1))^(1ll<<cur));
			to[msk][0][0]<<=1ll;
			to[msk][0][1]=to[msk][0][0]^1;
		}
		cur=len;
		while (~cur && (msk&(1ll<<cur))==0){
			cur--;
		}
		if (~cur){
			to[msk][1][0]=((msk&((1ll<<cur)-1))^(1ll<<cur));
			to[msk][1][0]<<=1ll;
			to[msk][1][1]=to[msk][1][0]^1;
		}
	}
}
```

万事具备，只欠东风！考虑 dp 怎么转移。

分三种情况：

- $S_i=\texttt{X},T_i=\texttt{X}$。

- $S_i=\texttt{Y},T_i=\texttt{Y}$。

- $S_i=\texttt{X},T_i=\texttt{Y}$ 或 $S_i=\texttt{Y},T_i=\texttt{X}$。

情况 $1,2$：

- 可以这两个匹配。

- 可以找前面 $msk$ 里面的匹配。

- 可以不匹配。

情况 $3$：

- 匹配 $\tt{X}$，$\tt{Y}$ 加入 $msk$。

- 匹配 $\tt{Y}$，$\tt{X}$ 加入 $msk$。

- 可以不匹配。

初始：$dp_{0,1}=1$。

**这一部分的 code**

```cpp
dp[0][1]=1;
for (int i=0; i<n; i++){
	for (int msk=0; msk<(1ll<<l); msk++){
		if (dp[i][msk]==0){
			continue;
		}
		if (s[i]=='X' && t[i]=='X'){
			// use this
			dp[i+1][1]=max(dp[i+1][1],dp[i][msk]<<1ll|1);
			if (to[msk][1][1]!=0){
				// use before
				dp[i+1][to[msk][1][1]]=max(dp[i+1][to[msk][1][1]],dp[i][msk]<<1ll|1);
			}
			if (msk<(1<<l-1)){
				// no use
				dp[i+1][msk<<1ll|1]=max(dp[i+1][msk<<1ll|1],dp[i][msk]);
			}
		}
		else if (s[i]=='Y' && t[i]=='Y'){
			// use this
			dp[i+1][1]=max(dp[i+1][1],dp[i][msk]<<1ll);
			if (to[msk][0][0]!=0){
				// use before
				dp[i+1][to[msk][0][0]]=max(dp[i+1][to[msk][0][0]],dp[i][msk]<<1ll);
			}
			if (msk<(1<<l-1)){
				// no use
				dp[i+1][msk<<1ll]=max(dp[i+1][msk<<1ll],dp[i][msk]);
			}
		}
		else{
			// use x
			if (to[msk][1][0]!=0){
				dp[i+1][to[msk][1][0]]=max(dp[i+1][to[msk][1][0]],dp[i][msk]<<1ll|1);
			}
			// use y
			if (to[msk][0][1]!=0){
				dp[i+1][to[msk][0][1]]=max(dp[i+1][to[msk][0][1]],dp[i][msk]<<1ll);
			}
			// no use
			if (msk<(1<<l-1)){
				dp[i+1][msk<<1ll]=max(dp[i+1][msk<<1ll],dp[i][msk]);
				dp[i+1][msk<<1ll|1]=max(dp[i+1][msk<<1ll|1],dp[i][msk]);
			}
		}
	}
}
```

输出答案 $\max_{i=1}^{l-1} dp_{N,i}$ 即可。
[submission。](https://atcoder.jp/contests/arc157/submissions/44634563)

---

## 作者：Astatinear (赞：1)

我们尝试给这个抽象题来一篇题解。

思考过程还是很重要的。

首先看了这个题，一看数据范围 $n\le 50$，然后就不懂了，你告诉我这玩意可以状压？？

然后我们一顿乱想，发现如果 $n$ 除以一个 $3$，那我们是不是就可以状压了。

那怎么除以 $3$ 呢。

接着我们手玩一下样例，发现似乎这个答案他不是很小啊。

然后我们继续，我们发现，如果答案够大，那么我们公共子序列的两对匹配点，假设在 $S,T$ 分别为 $(i_1,j_1),(i_2,j_2)$，他就可以保证 $|\max \{i_2-i_1,j_2-j_1\}|\le n-ans$。

所以，如果我们的答案 $ans \ge \dfrac{n}{3}$（向下取整），那我们就可以把两对匹配点之间的交换状况直接状压出来。

那么我们胡乱证明一下：

我们可以把这个序列分成若干个长度为 $3$ 的连续段，例如 $[1,3],[4,6],[7,9]$ 之类。

然后由于 $S_i,T_i\in\{X,Y\}$，所以我们可以在里面把 $2^6$ 种情况全部暴力枚举出来，然后发现里面至少会产生一个长度为 $2$ 的公共子序列，所以答案必然 $\ge \dfrac{2n}{3}$。

最终我们就通过一系列联想得到了这个结论。

然后有一个非常重要的东西，如果我们把 $X$ 当作 $1$，$Y$ 当作 $0$，那么最终答案就是这个二进制串的最大值，完美将方案输出，字典序最小，还有个数最大结合在一起。

然后我们考虑怎么状压。

~~这个状态是真的抽象啊，考场上纯属乱想的状态，好难解释。。~~

我们定义 $dp_{i,ST}$，表示当前在 $S,T$ 中考虑到了 $i$，从上次匹配点到当前点的状态为 $ST$ （这个 $ST$ 我很难解释，就是指在中间这一段中，你的 $S,T$ 可以取的字符，$X$ 为 $1$，$Y$ 为 $0$，由于可以交换，所以我们就将 $S,T$ 不区分开，不然你对两个都要打一个状态），的最小字典序（这个字典序就用上述的二进制串表示，其实就是这个二进制串的最大值）。

考虑顺推，这逆推太难了。

以及，为了方便，我们将 $1$ 作为初始状态，因为我们后面要从最高位开始向下找第一个满足条件的，所以需要先把最高位立在前面。

我们钦定 $S_i=X$ 是，$a_i=0$，否则 $a_i=1$。对于 $T_i$ 对应 $b_i$ 同理。

然后，如果我们不在这一步进行匹配，由于没有区分 $S,T$，就有下面两种情况：

+ $dp_{i+1,ST<<1|a_i} = \max\{dp_{i+1,ST<<1|a_i},dp_{i,ST}\}$

+ $dp_{i+1,ST<<1|b_i} = \max\{dp_{i+1,ST<<1|b_i},dp_{i,ST}\}$

（当然，进行这一步的前提是，你左移之后不会超过 $2^{\frac{2n}{3}}$）

接着，如果我们要用 $S_i,T_i$ 进行匹配，那么分为 $3$ 种情况：

+ 用 $S_i$ 匹配 $T_i$，也就是 $S_i=T_i$ 时。那么显然有 $dp_{i+1,0} = \max \{ dp_{i+1,0},dp_{i,ST} << 1|a_i\}$。

+ 用 $S_i$ 匹配前面的状态。我们从最高位开始（因为是左移，所以越高位越前面，而我们当然贪心的希望去选前面的符合要求的来匹配）找到第一个二进制位上等于 $a_i$ 的位置，将后面全部删掉，然后再将 $b_i$ 加入这个状态的首位（因为他没使用），假设操作完毕的状态为 $nxt$，那么有 $dp_{i+1,nxt}=\max \{dp_{i+1,nxt},dp_{i,ST}<<1|a_i\}$。

+ 用 $T_i$ 同理，将第二种情况的 $a,b$ 和 $S,T$ 交换一下就行。

由于此时时间复杂度已经达到 $n\times 2^{\frac{n}{3}}$，所以对于 $nxt$，我们直接用一个 $Nxt[ST][0/1][0/1]$ 来预处理即可。

这部分之前考试都有想到，但是范智打错。。

我们可以在思考一下正确性，就是你每次遇到 $S_i,T_i$ 要么将两者互相匹配，要么在后续状态中也只会选择其中的一个进行匹配，故状态只需要维护一个。

最后找到 $dp_{n,i}$ 的最大值（因为是二进制串），然后转化为 $X,Y$ 输出即可。

~~话说这题二进制串的到处乱移是真恶心。~~

### $\texttt{Code}$

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
long long dp[65][1 << 21];
int nxt[1 << 21][2][2];
int n;
char a[65], b[65];
signed main()
{
//	freopen("try.in", "r", stdin);
//	freopen("try.out", "w", stdout);
	scanf("%lld", &n);
	scanf("%s", a + 1), scanf("%s", b + 1);
	int limit = ceil(n / 3.0); 
	for (int i = 1; i < (1 << limit); ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			for (int k = 0; k < 2; ++k)
			{
				int pos = -1;
				for (int l = (__lg(i) - 1); l >= 0; --l) if(((i >> l) & 1) == j)
				{
					pos = l;
					break;
				}
				if(pos == -1) continue;
				nxt[i][j][k] = (((i & ((1ll << pos) - 1)) + (1 << pos)) << 1) + k;
			}
		}
	}
	dp[0][1] = 1;
	for (int i = 0; i < n; ++i)
	for (int j = 0; j < (1 << limit); ++j)
	{
		if(!dp[i][j]) continue;
		int p = (a[i + 1] == 'X'), q = (b[i + 1] == 'X');
		if(nxt[j][p][q]) dp[i + 1][nxt[j][p][q]] = max(dp[i + 1][nxt[j][p][q]], (dp[i][j] << 1) + p);
		if(nxt[j][q][p]) dp[i + 1][nxt[j][q][p]] = max(dp[i + 1][nxt[j][q][p]], (dp[i][j] << 1) + q);
		if(((j << 1) + p) < (1 << limit)) dp[i + 1][(j << 1) + p] = max(dp[i + 1][(j << 1) + p], dp[i][j]);
		if(((j << 1) + q) < (1 << limit)) dp[i + 1][(j << 1) + q] = max(dp[i + 1][(j << 1) + q], dp[i][j]);
		if(p == q) dp[i + 1][1] = max((dp[i][j] << 1) + p, dp[i + 1][1]);
	}
	long long ans = 0;
	for (int i = 0; i < (1 << limit); ++i) ans = max(ans, dp[n][i]);
	int cnt = __lg(ans);
	for (int i = cnt - 1; i >= 0; --i) if((ans >> i) & 1) putchar('X'); else putchar('Y');
	return 0;
}
```

---

## 作者：EXODUS (赞：0)

# Part 1：前言

很漂亮的一道题目，我一点不会。

# Part 2：正文

我们首先考虑一些暴力。我们从前向后扫描每一个位置，设 $f(i,S)$ 表示考虑到位置 $i$，从上次匹配位置到当前位置的状态是 $S$，所能达到的最长公共子序列的最小字典序。转移时，分当前位置的字符是否选中参与到子序列中讨论。若选中，注意到一个很好的性质是无论我们匹配一个 $\texttt{X}$ 还是 $\texttt{Y}$，我们一定会选择 $S$ 当中最靠左的一个，因此我们的转移可以 $O(1)$ 进行。具体而言，我们对每个 $S$ 所代表的状态预处理出其第一个 $\texttt{X}$ 所在的位置和 $\texttt{Y}$ 所在的位置，转移时舍弃匹配位置以前的部分，将其加入答案，然后把剩余的那个字符拼到当前备选状态的末尾，转移到这个状态对应的位置，否则直接拼到备选状态，分到底把哪个拼上去讨论即可。时间复杂度 $O(n2^n)$。

接下来有一个惊为天人的结论，答案的下界是 $\lfloor \dfrac{2n}{3}\rfloor$。原因是，如果我们把每三个相邻字符分到一组，这一组里的能贡献出的 LCS 长度至少为 $2$。可以使用一些分讨或直接暴搜证明，这里不再赘述。因此我们两个匹配的位置距离至多为 $\lceil \dfrac{n}{3} \rceil$。所以暴力 dp 第二维的状态为 $2^{\frac{n}{3}}$，总时间复杂度为 $O(n2^{\frac{n}{3}})$，可以通过此题。

代码实现上，我们需要把字符串映射为数字，官解给了一种很巧妙的方式是把长度为 $n$ 的字符串看做一个长度为 $n+1$ 的二进制数，后 $n$ 位表示把 $\texttt{X}$ 看成 $1$，$\texttt{Y}$ 看成 $0$ 后对应的二进制数，第一位代表终止符，始终为 $1$，这样映射后取最大值恰好对应了题目中要求的操作，容易 dp 解决。 



# Part 3：代码

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ldb;

#define rep(i,l,r) for(int i(l);i<=(r);++i)
#define per(i,r,l) for(int i(r);i>=(l);--i)
#define eb emplace_back
#define File(filename) freopen(filename ".in","r",stdin),freopen(filename ".out","w",stdout)

#ifdef EXODUS
	#define Debug(...) fprintf(stderr,__VA_ARGS__)
#else
	#define Debug(...) 0
#endif

//=========================================================================================================
// Something about IO

template<typename T>
void read(T &x){
	x=0;T flg=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')flg=-1;ch=getchar();}
	while(isdigit(ch))x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	x*=flg;
}
template<typename T,typename... Args>
void read(T &x,Args &...args){read(x),read(args...);}

//=========================================================================================================
// Define the global variables here.

bool membg=0;

constexpr int N=57;
int n;char s[N],t[N];
ll f[N][(1<<18)+7],trs[(1<<18)+7][2][2];

bool memed=0;

//=========================================================================================================
// Code here.

void solve(){
	read(n);scanf("%s%s",s+1,t+1);
	auto shift=[&](int x){return 1ll<<x;};
	auto chk=[&](ll &x,ll y){if(x<y)x=y;};
	int lim=(n-1)/3+2,full=shift(lim);
	for(int S=1;S<full;S++){
		int mxb=__lg(S);int _0=mxb-1,_1=mxb-1;
		while(_0>=0&&(S&shift(_0)))_0--;while(_1>=0&&!(S&shift(_1)))_1--;
		if(_0>=0)trs[S][0][0]=((S&(shift(_0)-1))|shift(_0))<<1,trs[S][0][1]=((S&(shift(_0)-1))|shift(_0))<<1|1;
		if(_1>=0)trs[S][1][0]=((S&(shift(_1)-1))|shift(_1))<<1,trs[S][1][1]=((S&(shift(_1)-1))|shift(_1))<<1|1;
		// printf("%lld %lld %lld %lld\n",trs[S][0][0],trs[S][0][1],trs[S][1][0],trs[S][1][1]);
	}
	f[1][1]=1;
	for(int i=1;i<=n;i++){
		int sn=(s[i]=='X'),tn=(t[i]=='X');
		for(int S=1;S<full;S++){
			if(!f[i][S])continue;
			if(sn==tn)chk(f[i+1][1],(f[i][S]<<1)|sn);
			if(S<shift(lim-1))chk(f[i+1][(S<<1)|sn],f[i][S]),chk(f[i+1][(S<<1)|tn],f[i][S]);
			if(trs[S][sn][tn])chk(f[i+1][trs[S][sn][tn]],(f[i][S]<<1)|sn);
			if(trs[S][tn][sn])chk(f[i+1][trs[S][tn][sn]],(f[i][S]<<1)|tn);
		}
	}
	ll ans=1;
	for(int S=1;S<full;S++)chk(ans,f[n+1][S]);
	for(int i=__lg(ans)-1;i>=0;i--)
		printf("%c",(ans&shift(i))?'X':'Y');
	printf("\n");
	return;
}


//=========================================================================================================

int main(){
	Debug("%.3lfMB\n",fabs(&memed-&membg)/1024.0/1024.0);
	int timbg=clock();
	int T=1;
	while(T--)solve();
	int timed=clock();
	Debug("%.3lfs\n",1.0*(timed-timbg)/CLOCKS_PER_SEC);
	fflush(stdout);
	return 0;
}
```

---

