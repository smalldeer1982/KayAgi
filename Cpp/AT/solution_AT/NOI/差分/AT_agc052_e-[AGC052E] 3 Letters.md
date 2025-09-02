# [AGC052E] 3 Letters

## 题目描述

由 `A`、`B`、`C` 组成的字符串，如果任意连续的 $2$ 个字符都不相同，则称为**好**字符串。例如，`ABABAB` 和 `ABC` 是好字符串，而 `ABBA` 和 `AABBCC` 不是好字符串。

给定两个长度为 $N$ 的**好**字符串 $S$ 和 $T$。每次操作，你可以从 $S$ 中任选一个字符，将其变为 `A`、`B`、`C` 中的另一个字符。操作后，$S$ 仍需保持为**好**字符串。

请问最少需要多少次操作，才能将 $S$ 变为 $T$。可以证明一定可以在有限次操作内完成。

## 说明/提示

## 限制

- $1 \leq N \leq 5 \times 10^5$
- $S$ 是由 `A`、`B`、`C` 组成的长度为 $N$ 的**好**字符串。
- $T$ 是由 `A`、`B`、`C` 组成的长度为 $N$ 的**好**字符串。

## 样例解释 1

以下是用 $6$ 次操作达成目标的一个例子：`CABC` $\to$ `BABC` $\to$ `BCBC` $\to$ `BCAC` $\to$ `ACAC` $\to$ `ABAC` $\to$ `CBAC`。在这种情况下，至少需要 $6$ 次操作。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
CABC
CBAC```

### 输出

```
6```

## 样例 #2

### 输入

```
10
ABABABABAB
BABABABABA```

### 输出

```
15```

# 题解

## 作者：UnyieldingTrilobite (赞：6)

首先，方便起见，我们以 $2,0,1$ 代替 $A,B,C$（方便直接 ASCII 取模）。接下来，我们试图为一个好串 $S$ 找到一个长为 $n$ 的序列刻画方式，其中 $n$ 是 $S$ 的长度。

我们意识到，相邻字母只要不同，转换为数值后模 $3$ 之差一定是 $1$ 或 $-1$，那么我们不妨对序列 $A$ 给出如下约束：

+ $|A_{i+1}-A_i|=1$

+ $A_i\equiv S_i(\bmod\ 3)$

我们把这样的序列称作“好序列”。不难发现，固定 $S$ 与 $A_1$ 后，好序列是唯一的。**但注意 $A_1$ 不固定时好序列不是唯一的，且所有这些不唯一的好序列都能对应到同一个 $S$ 上**。

我们注意到，对于 $S$ 中相邻的三个字母，如果它们两两不同，那么中间那个字母是一定无法变化的（不然变完一定失去好串性质）。那么为了变化中间的字母，两端的字母一定要相同（也就是得是类似于 $010$ 的形式）。这样一来，在 $A$ 序列中，两端的数值一定是相同的，而中间的数值在变化前后分别是两端的数值加一或减一（也就是 $x,x+1,x$ 变成 $x,x-1,x$ 或反之）。如此一来，我们发现，在序列维持是好序列的前提下，单个元素单次变化的绝对值一定是 $|1-(-1)|=2$。**以上讨论没有专门分变化位置在边界的类，但其实是一样的**。

回到原问题。我们不妨考虑我们已经确定了 $S$，$T$ 对应出的好序列 $A$，$B$。由于两个好序列可以同步平移，我们事实上可以不妨直接定下 $A$。注意到我们每一次操作并不会改变元素的奇偶性，所以必须满足 $A$ 与 $B$ 每个对应位置的奇偶性都相同。考虑到 $A$ 的相邻位置一定有奇偶变化（$B$ 同理），实际上只需要做到 $A_1$ 与 $B_1$ 奇偶性相同。

接下来我们考虑至少要多少步能把 $A$，$B$ 变成同一个序列（事实上由于变化是可逆的，具体变成什么样其实我们并不关心）。容易发现，答案的下界是 $\frac 1 2\sum_{i=1}^{n}|A_i-B_i|$，考虑到我们最优情况下每一步也只能让它减少一。而我们猜测答案就是这个值，那我们断言存在一种策略能保证每一步都能让它减少一。换句话说，每一步一定会找到一个 $A_i\gt B_i$ 的位置并把 $A_i$ 减二，或是一个 $A_i\lt B_i$ 的位置把 $B_i$ 减二。这两者没有区别。

由于 $A$ 和 $B$ 还不完全相同，我们不妨存在位置使得 $A_i\gt B_i$（反之一定存在位置使得 $A_i\lt B_i$，完全同理即可）。我们找到所有这样的位置中 $A_i$ 最大的那一个，试图证明 $A_{i-1}$ 和 $A_{i+1}$（均若存在）一定都等于 $A_i-1$。反之，不妨 $A_{i-1}=A_i+1$，注意到 $B_{i-1}\le B_i+1\lt A_i+1=A_{i-1}$，那么 $i-1$ 也是一个符合条件的位置，与 $A_i$ 的最大性矛盾！

如此一来，我们只要确定了 $A$ 和 $B$，答案便能通过 $\frac 1 2\sum_{i=1}^{n}|A_i-B_i|$ 快速计算。实际上，$A$ 是确定的，$B_i-B_1$ 是确定的，我们不妨记 $B_1=x$，那么 $x$ 只需要满足 $x\equiv A_1(\bmod\ 2)$ 且 $x\equiv T_1(\bmod\ 3)$ 即可。再设 $x=6y+k$（其中 $k$ 是由以上两个约束计算得出的常数），$A_i-B_i+B_1-k=C_i$，那么答案实际上便化为了 $\frac 1 2\sum_{i=1}^{n}|C_i-6y|$。注意到此时 $y$ 已经是一个完全自由的变元，枚举 $6y$ 在 $C$ 中位数两端计算答案取 $\min$ 即可。

在代码中，下标从 $0$ 开始，且计算的 `b` 数组实际上是 $B_i-B_1+k$，注意不要混淆。另外注意到 C++ 除号在被除数是负数的时候取整可能不能如我们所愿，所以简单一点就中间+两边三项取 $\min$ 就不会有问题了（这部分可以参考代码理解）。

```cpp
#include <bits/stdc++.h>
using namespace std;
signed main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n;
  string s, t;
  cin >> n >> s >> t;
  vector<int> a(n), b(n), c(n);
  a[0] = s[0] % 3, b[0] = t[0] % 3;
  if ((a[0] ^ b[0]) & 1) b[0] += 3;
  for (int i = 1; i < n; ++i) {
    a[i] = a[i - 1] + 1, b[i] = b[i - 1] + 1;
    if ((s[i] - a[i]) % 3) a[i] -= 2;
    if ((t[i] - b[i]) % 3) b[i] -= 2;
  }
  for (int i = 0; i < n; ++i) c[i] = a[i] - b[i];
  nth_element(c.begin(), c.begin() + (n >> 1), c.end());
  auto calc = [&](int x) {
    long long ret = 0;
    for (int i = 0; i < n; ++i) ret += abs(c[i] - x);
    return ret;
  };
  int w = c[n >> 1] / 6 * 6;
  return cout << (min({calc(w), calc(w - 6), calc(w + 6)}) >> 1) << endl, 0;
}

```

---

## 作者：隔壁泞2的如心 (赞：4)

首先注意到一个性质，就是任何一个字符在每一时刻都只有最多一种改变方式，只有某字符两边的字符一样，这个字符才可能改变，这看上去就有点眼熟了。进一步地，我们将 ```ABC``` 看成模 $3$ 意义下的 $012$，那么对于不在两端的字母的操作，其实就是————

![](https://cdn.luogu.com.cn/upload/image_hosting/ruazc0em.png)

震撼人心。

当然，保证完差分，还得保证一个端点。对于在两端的字母的操作，其实就是将差分数组的两端取反，并且取反的方式和次数在模 $3$ 意义下有要求。比如，要是给定的串第一个字母是 ```A```，目标串第一个字母是 ```B```，那么在差分数组开头将 $+1$ 取反为 $-1$ 的次数（若是将 $-1$ 取反为 $+1$，则记为 $-1$ 次）模 $3$ 必须为 $2$。我们可以只考虑差分中的 $-1$，那么取反就可以认为是从假想的有无限个 $-1$ 的差分数组的第 $0$、$n$ 项换出或换入 $-1$。

然后我们记录起始串和目标串差分的 $-1$ 位置，那么只需要将这些位置匹配，然后计算差的绝对值之和即可算出这种匹配下的最小操作次数。而取反次数要求，其实就是匹配时偏移量的要求。具体地，我们在两个差分数组前面加上无数个 $0$，后面加上无数个 $n$，记为 $\{A_i\},\{B_i\}$（下标可能为负数），那么我们就是要对于所有模 $3$ 余某定值的整数 $k$，求

$$\sum |A_i-B_{i+k}|$$

的最小值。

这个式子感觉好不可做啊！直接暴力显然过不去，找性质吗？指望着它单峰？指望着它凸？找个“中间值”往两边扩然后卡时？我想了很久很久怎么解决这个问题，结果一拍脑门发现，由于 $\{A_i\},\{B_i\}$ 都单调，这个式子一拆贡献再差分就可以直接对于每个可能有用的 $k$ 都算出来值……

这就……

```
#include<cstdio>
#include<algorithm>
#define int long long 
using namespace std;
char s1[654321],s2[654321];
int n,q1[654321],l1,q2[654321],l2,cal[1048576];
signed main(){
	scanf("%lld",&n);
	scanf("%s%s",s1,s2);
	for(int i=1;i<n;i++){
		if((s1[i]-'A'+1)%3==s1[i-1]-'A')q1[++l1]=i;
		if((s2[i]-'A'+1)%3==s2[i-1]-'A')q2[++l2]=i;
	}
	q1[++l1]=n;q2[++l2]=n;
	for(int i=1,j=1;i<l1;i++){
		cal[0]+=q1[i];
		while(q2[j]<=q1[i])++j;
		cal[j+l1-i]-=2*q1[i]; 
	}
	for(int i=1,j=0;i<l2;i++){
		cal[0]-=q2[i];
		while(q1[j]<q2[i])++j;
		cal[i+(l1-(j-1))]+=2*q2[i];
	}
	for(int i=1;i<=l1+l2;i++)cal[i]+=cal[i-1];
	for(int i=0;i<=l1+l2;i++)cal[i]+=abs(l2-i)*n;
	int ans=1844674073709551616ll;
	int dif=(s1[0]-s2[0]+3)%3;
	for(int i=l1+dif;i<=l1+l2;i+=3)if(i>=0)ans=min(ans,cal[i]);
	for(int i=l1+dif;i>=0;i-=3)if(i<=l1+l2)ans=min(ans,cal[i]);
	printf("%lld",ans);
} 
```


---

## 作者：drmr (赞：3)

**题意**：给定两个长度为 $N$ 的字符串 $S, T$，字符集 $U = \{A, B, C\}$。现在一次操作可以选择 $1 \le i \le N$ 和 $K \in U$，使 $S_i \leftarrow K$，且 $S_{i-1} \ne K, S_{i +1} \ne K$。求把 $S$ 变为 $T$ 的最小步骤数，可以证明一定有解。

设整数数列 $s$，使得 $\forall 1 \le i \le N$，$s_i$ 和 $S_i$ 对于 $3$ 同余，同理定义整数数列 $t$。我们一定可以构造出一组 $s$ 使得 $\forall 1 \le i < N$，有 $|s_i - s_{i+1}| = 1$。也同理约束 $t$。

我们发现，若操作 $i$，则 $S_{i-1} = S_{i+1}$，此时 $s_{i-1} = s_{i+1} = s_i \pm 1$。操作可以使 $s_i \leftarrow s_i \pm 2$，操作后仍然满足相邻两数绝对值为 $1$ 的限制。

通过贪心的证明，我们容易证明 $\frac{\sum_{i \in [1, N]} |s_i - t_i|}{2}$ 是操作次数的下界。我们考虑最小化该值。

![](https://cdn.luogu.com.cn/upload/image_hosting/j1emb1u3.png)

这个问题十分简单，如图，蓝线和橙线分别代表 $s$ 和 $t$，那么当我们将蓝线向上移动时，$s_i \ge t_i$ 的部分会将贡献加一，否则则会减一，因此 $s_i \ge t_i$ 和 $s_i < t_i$ 的 $i$ 的数量越接近，答案越小，这等价于将两者的中位数对齐。然而，我们只能将 $t$ 整体加 $3$ 的倍数，且需要保证 $s_i$ 和 $t_i$ 奇偶性相同，需要注意实现细节。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 5e5 + 5;
int n, a[N], b[N], c[100][100], d, ans, p[N], q[N];
string s, t;

signed main(){
	cin >> n >> s >> t, s = "@" + s, t = "@" + t;

	c['A']['B'] = 1, c['A']['C'] = -1;
	c['B']['C'] = 1, c['B']['A'] = -1;
	c['C']['A'] = 1, c['C']['B'] = -1;

	a[1] = s[1] % 3;
	for(int i = 2; i <= n; i++)
		a[i] = a[i - 1] + c[s[i - 1]][s[i]];
	b[1] = t[1] % 3;
	for(int i = 2; i <= n; i++)
		b[i] = b[i - 1] + c[t[i - 1]][t[i]];

	for(int i = 1; i <= n; i++) p[i] = q[i] = i;
	sort(p + 1, p + 1 + n, [](int x, int y){return a[x] < a[y];});
	sort(q + 1, q + 1 + n, [](int x, int y){return b[x] < b[y];});

	int d = a[p[(n + 1) / 2]] - b[q[(n + 1) / 2]], mn = 1e18;
	for(int e = d / 3 * 3 - 18; e <= d / 3 * 3 + 18; e += 3){
		if(((b[1] + e) ^ a[1]) & 1) continue;
		ans = 0;
		for(int i = 1; i <= n; i++)
			ans += abs(a[i] - b[i] - e);
		mn = min(mn, ans);
	}
	cout << mn / 2;
	return 0;
}
```

---

## 作者：strcmp (赞：1)

毕竟是纯靠思维就成为 AGC E 的题，直接去想肯定没出路的。

一般这种染色问题，有一种 trick 是构造字符串到序列的某种映射。尤其用来解决三染色问题尤其适用。

具体来说，我们把整个 $s$ 看成三进制数，再把这个三进制数的每一位写出来，在模 $3$ 意义下得到一个序列 $a$。我们实际上就是要求 $\forall a_i \ne a_{i - 1}$。

不等号是难搞的，但是我们有了这个序列，考虑根据序列怎么描述这个不等号。

其实就是 $a_i \equiv a_{i - 1} \pm 1 \pmod 3$。毕竟 $+2$ 在模 $3$ 的意义下就是 $-1$。

前面这些部分光靠自己想出还是有相当难度的，但实际上三染色问题很多时候可以用类似 trick，这也方便了我们做题。

好了现在有了这种方式描述一个不等号，先考虑构造 $s$ 到 $a$ 的映射。令 $a_1 = k$，注意 $k \in \mathbb N$。 

如果 $s_{i - 1}$ 和 $s_{i}$ 的关系是 $\texttt{\{(A, B),\,(B, C),\,(C, A)\}}$ 这种关系，那么令 $a_i \gets a_{i - 1} + 1$，否则令 $a_i \gets a_{i - 1} - 1$。

如果固定 $a_1$，那么这就是一个双射。

现在考虑变换 $s$ 的一个字符对 $a$ 产生什么影响。

注意到 $s$ 变换一个字符 $s_i$，必须满足两边的字符都是相同的，那么此时 $a_i$ 的变化就是 $+2$ 或者 $-2$（不可能 $\pm 1$，否则一定会跟旁边的一样）。

这就是这个双射给我们的便利，在仅考虑 $s$ 的时候我们很难去描述变换一个字符到底代表什么。但是有了 $a_i$ 我们就可以大概计算一个下界。

考虑得到 $s$ 的一个映射 $a$ 和 $t$ 的一个映射 $b$，假设我们已经钦定了 $a_1$ 和 $b_1$。

首先 $a$ 和 $b$ 的奇偶性必须相同，因为我们都是 $\pm 2$。

所以我们有一个下界是 $\frac{1}{2} \sum |a_i - b_i|$。

有了下界怎么用？我们考虑**证明任意情况下都可以到达这个下界。**

直接开始构造，我们先令 $c_i \gets a_i - b_i$，那么我们相当于是 $+2$ 或者 $-2$ 使得 $c$ 变为全 $0$。

我们不妨在所有 $c_i > 0$（假设存在的话）的 $i$ 中找到一个最大的 $a_i$，并且把这个 $a_i$ 减 $2$。

如果存在 $c_i > 0$，这样一定合法，考虑证明：

不合法当且仅当 $c_{i - 1} \le 0 \wedge a_{i - 1} = a_{i} + 1$ 或者 $c_{i + 1} \le 0 \wedge a_{i + 1} = a_{i} + 1$，我们证明这种情况不合法。这里只证明 $a_{i + 1}$ 的情况，另一种情况是对称的。

直接反证，$c_{i + 1} = a_{i + 1} - b_{i + 1} = a_i + 1 - b_{i + 1} \ge a_i + 1 - (b_i + 1) = a_i - b_i = c_i > 0$。矛盾。

所以如果存在 $c_i > 0$，一定能进行这种操作。

$c_i < 0$ 也是对称的。

操作总是能进行且没有浪费，于是我们证明了一定能进行操作使得 $a_i = b_i$ 且操作次数是 $\frac{1}{2} \sum |a_i - b_i|$。

固定 $a_1 = s_1 \bmod 3$，现在问题是 $b_1$ 不固定，我们怎么求出 $b_1$。

直接令 $b_1 = t_1 \bmod 3$ 并求出 $c_i = a_i - b_i$。我们现在相当于最小化 $\sum |c_i|$。

注意到显然取 $c$ 的中位数，但是中位数不一定能使得 $a,\,b$ 的奇偶性相同。并且这里还有个细节是 $s_1$ 和 $t_1$ 的映射 $a_1 \equiv b_1 \pmod 3$，否则我们的字符没办法对齐。

因此实际上我们保证奇偶性相同的情况下只能把 $b$ 同时增加或者减少 $\text{lcm}(2,\,3) = 6$。

于是考虑中位数附近 $6$ 的倍数带入 $b_1$ 即可。

使用 `ntn_element`，时间复杂度 $\Theta(n)$。

```cpp
#include <bits/stdc++.h>
#define X first
#define Y second
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define per(i, a, b) for (int i = a; i >= b; i--)
#define pb push_back
#define mp make_pair
#define mid (l + r >> 1)
using namespace std;
typedef long long int ll;
using ull = unsigned long long int;
using pii = pair<int, int>;
using pil = pair<int, ll>;
using pq = priority_queue<int>;
using vec = vector<int>;
constexpr int maxn = 1e6 + 10, mod = 998244353, B = 600; constexpr ll inf = 1e16;
int n, a[maxn], b[maxn]; char s[maxn], t[maxn];
void geta(char* s, int* a) {
	a[1] = s[1] - 'A';
	rep(i, 2, n) {
		if ((s[i - 1] == 'A' && s[i] == 'B') || (s[i - 1] == 'B' && s[i] == 'C') || (s[i - 1] == 'C' && s[i] == 'A')) a[i] = a[i - 1] + 1;
		else a[i] = a[i - 1] - 1;
	}
}
inline ll calc(int w) {
	ll ans = 0;
	rep(i, 1, n) ans += abs(a[i] - w) / 2;
	return ans;
}
int main() {
	scanf("%d%s%s", &n, s + 1, t + 1);
	geta(s, a), geta(t, b); ll ans = inf;
	if (a[1] % 2 != b[1] % 2) rep(i, 1, n) b[i] += 3;
	rep(i, 1, n) a[i] -= b[i];
	nth_element(a + 1, a + n / 2 + 1, a + n);
	int w = a[n / 2 + 1] / 6 * 6;
	rep(i, -3, 3) ans = min(ans, calc(w + i * 6));
	printf("%lld\n", ans);
	return 0;
}
```

还是想一下这个映射带给我们什么，如果只考虑 $s$，首先我们难以计算下界，其次我们不知道选择哪个改变。

那个所谓的 $a_i > b_i$ 且 $a_i$ 最大的点，我们难以在 $s$ 上找到一个什么很好的描述方法。你可以把它看作一个类似折线的东西，我们字符之间的关系形成了折线，那么我们考虑一个峰或者谷一定是可以的。但是放到 $s$ 上的时候我们的峰或者谷可以改变，这点并不很显然。我们相当于是把那个烦人的 $\bmod 3$ 去掉了，来帮助我们找到这个峰或者谷，不然在 $\bmod 3$ 的意义下完全找不到这个山峰和山谷。

这也是这类题比较难以初见杀的原因，你必须把原题目放缩成一个更好解决的问题来找到性质。但是不知道性质我们也不知道应该如何放缩题目。太困难了，不知道第一个想出来这个东西的人大脑结构是什么样的。

但是这题的方法（构造双射），不止这道题，在三染色题目中经常是有用的。一个好例子是 [AGC059E](https://www.luogu.com.cn/problem/AT_agc059_e)，有兴趣者非常推荐去做。

---

## 作者：win114514 (赞：1)

妙妙题。

### 思路

我们考虑将一个字符串 $s$ 看作一个序列 $a$。

我们要求：

1. 当 $s_i=\text{a},a_i\equiv 1 \pmod3$
1. 当 $s_i=\text{b},a_i\equiv 2 \pmod3$
1. 当 $s_i=\text{c},a_i\equiv 0 \pmod3$

那么发现，由于 $s$ 中相邻字符都不相同，也就意味着 $|a_i-a_{i-1}|=1$。

那么当我们 $s$ 与 $a_1$ 确定后，整个 $a$ 序列就确定了。

考虑修改。

我们在修改一个字符的时候，要求两侧的字符相同，并都与中间的不同。

在序列上的表示即为：

$$
x,x+1/x-1,x
$$

那么我们只能把 $x+1$ 和 $x-1$ 互相变化。

因此我们的操作就是每一次给一个数加减二。

然后我们考虑在这种操作下，我们怎样把两个**数值**的序列 $a,b$ 变得相同。

首先，对于每一个位置，两个数的奇偶性要一样，否则就无解。

有一个比较简单的下界是：$\sum_{i=1}^n\frac{|b_i-a_i|}{2}$。

我们可以证明能够达到这个下界，具体的我们一定可以找到一个位置将其距离缩小二。

然后我们就把字符串距离转化为了序列的距离了。

我们考虑对两个字符串都固定一个序列。

由于两个都固定没有意义，我们可以将一个随意处理。

比如我们知道了 $s$ 的 $a$ 序列。

现在需要构造 $t$ 的 $b$ 序列。

由于 $b_1,a_1$ 的奇偶性相同，也要和第一个字符模三一样。

那么可以令：

$$
b_1=x+6\times k
$$

相当于我们求出任意一个 $b$ 后可以将它全部偏移 $6\times k$。

考虑此时的贡献：

$$
\begin{align}
&=\sum_{i=1}^n \frac{|(a_i-b_i)+6\times k|}{2}\\
&=\sum_{i=1}^n \frac{|(b_i-a_i)-6\times k|}{2}
\end{align}
$$

那么只要求 $b_i-a_i$ 的中位数，求能取到最优的答案。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

int n;
int a[500010];
int b[500010];
string s;
string t;

inline int calc(int x) {
  int res = 0;
  for (int i = 1; i <= n; i++)
    res += abs(a[i] - x) / 2;
  return res;
}

signed main() {
  cin >> n >> s >> t;
  if (s[0] == 'A') a[1] = 1;
  if (s[0] == 'B') a[1] = 2;
  if (s[0] == 'C') a[1] = 3;
  for (int i = 2; i <= n; i++) {
    if (s[i - 2] == 'A') a[i] = a[i - 1] + (s[i - 1] == 'B' ? 1 : -1);
    if (s[i - 2] == 'B') a[i] = a[i - 1] + (s[i - 1] == 'C' ? 1 : -1);
    if (s[i - 2] == 'C') a[i] = a[i - 1] + (s[i - 1] == 'A' ? 1 : -1);
  }
  if (t[0] == 'A') b[1] = 1;
  if (t[0] == 'B') b[1] = 2;
  if (t[0] == 'C') b[1] = 3;
  for (int i = 2; i <= n; i++) {
    if (t[i - 2] == 'A') b[i] = b[i - 1] + (t[i - 1] == 'B' ? 1 : -1);
    if (t[i - 2] == 'B') b[i] = b[i - 1] + (t[i - 1] == 'C' ? 1 : -1);
    if (t[i - 2] == 'C') b[i] = b[i - 1] + (t[i - 1] == 'A' ? 1 : -1);
  }
  if (a[1] % 2 != b[1] % 2) {
    for (int i = 1; i <= n; i++) b[i] += 3;
  }
  for (int i = 1; i <= n; i++) a[i] -= b[i];
  sort(a + 1, a + n + 1);
  int w = a[n / 2 + 1] / 6 * 6;
  int s = 1e18;
  for (int i = -5; i <= 5; i++)
    s = min(s, calc(w + i * 6));
  cout << s << "\n";
}
```

---

## 作者：云浅知处 (赞：1)

把 `A/B/C` 看成 $0,1,2$，我们把一个字符串看成一个序列 $A$，满足 $A_i\equiv S_i\pmod 3$，且 $|A_i-A_{i+1}|=1$。显然只要确定了 $A_1$，那么序列 $A$ 是唯一确定的。例如 `ABACBAB` 就可以看成序列 $0,1,0,-1,-2,-3,-2$。

那么一次操作就相当于，选择一个 $p$，把 $A_p\leftarrow A_p\pm 2$，使得序列仍然满足 $\forall i,|A_i-A_{i+1}|=1$。

那么首先，需要 $A_i\equiv B_i\pmod 2$，且操作数有下界 $\sum \frac{|A_i-B_i|}{2}$。下面我们证明可以取到这个下界。

我们考虑证明，只要 $\sum|A_i-B_i|>0$，那么一定存在一种操作，使得我们能把 $\sum |A_i-B_i|$ 减少 $2$。

我们选取 $A_i>B_i$ 的 $i$ 中，$A_i$ 最大的那个，那么操作这个 $A_i\leftarrow A_i-2$ 一定合法。如果不合法，说明一定是 $A_i$ 前后存在一个大于他的。不妨设 $A_{i-1}=A_i+1$，发现此时由于 $B_{i-1}\le B_i+1$，因此 $A_{i-1}>B_{i-1}$，而 $A_{i-1}>A_i$，与 $A_i$ 最大矛盾。 

不妨设 $A_1=0$，现在只需要选取 $B_1$ 满足 $B_1\equiv T_1\pmod 3,B_1\equiv A_1\pmod 2$，最小化 $\sum |A_i-B_i|$。由于确定 $B_1$ 后，每个 $B_i$ 都可以写成 $B_1+X_i$ 的形式，其中 $X_i$ 是定值。

那么就是需要选取 $B_1$，最小化 $\sum|A_i-X_i-B_1|$。这是一个经典问题，我们应当找到 $A_i-X_i$ 的中位数，然后让 $B_i$ 尽量接近这个中位数。由于值域为 $O(N)$ 可以在线性时间内排序，故本题可以在 $O(N)$ 时间内解决。

下面是 $O(N\log N)$ 的代码。

```cpp
#include<bits/stdc++.h>

#define ll long long

using namespace std;

template<typename T>void cmax(T &x,T v){x=max(x,v);}
template<typename T>void cmin(T &x,T v){x=min(x,v);}

const int N=5e5+5;
int a[N],b[N],n;
string s,t;
int get(char p,char q){
    if(p==q)return 0;
    if(q==p+1||q==p-2)return 1;
    return -1;
}

signed main(void){

#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif

    cin>>n>>s>>t;
    a[0]=0;for(int i=1;i<n;i++)a[i]=a[i-1]+get(s[i-1],s[i]);
    b[0]=0;for(int i=1;i<n;i++)b[i]=b[i-1]+get(t[i-1],t[i]);
    auto calc=[&](int t){
        ll ans=0;
        for(int i=0;i<n;i++)ans+=abs(a[i]-b[i]-t);
        return ans;
    };

    int L=-1e9,R=1e9,ans=R;
    while(L<=R){
        int mid=(L+R)>>1;
        if(calc(mid)<=calc(mid+1))ans=mid,R=mid-1;
        else L=mid+1;
    }

    ll res=1e18;
    int p=ans;while(p%2!=0||(p%3+3)%3!=(t[0]-s[0]+3)%3)p++;
    cmin(res,calc(p));
    p=ans;while(p%2!=0||(p%3+3)%3!=(t[0]-s[0]+3)%3)p--;
    cmin(res,calc(p));

    cout<<res/2<<endl;

    return 0;
}
```

---

