# [AGC063C] Add Mod Operations

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc063/tasks/agc063_c

非負整数列 $ A\ =\ (A_1,\ \ldots,\ A_N) $ および $ B=(B_1,\ \ldots,\ B_N) $ が与えられます．

以下の操作を $ 0 $ 回以上 $ N $ 回以下行うことで，$ A $ を $ B $ に一致させることができるか否かを判定してください．

- 操作：$ 0\leq\ x\ <\ y\leq\ 10^{18} $ を満たす整数 $ x,y $ を選ぶ．すべての $ i $ に対して，$ A_i $ を $ (A_i+x)\bmod\ y $ に置き換える．
 
$ A $ を $ B $ に一致させることが可能な場合には，そのような手順をひとつ出力してください．

## 说明/提示

### 制約

- $ 1\leq\ N\leq\ 1000 $
- $ 0\leq\ A_i\leq\ 10^9 $
- $ 0\leq\ B_i\leq\ 10^9 $
 
### Sample Explanation 1

次のようにして $ A $ を $ B $ に一致させることができます． - はじめ $ A\ =\ (7,2,4,5) $ です． - $ (x,y)\ =\ (3,5) $ として操作を行うと，$ A\ =\ (0,0,2,3) $ になります． - $ (x,y)\ =\ (3,6) $ として操作を行うと，$ A\ =\ (3,3,5,0) $ になります．

## 样例 #1

### 输入

```
4
7 2 4 5
3 3 5 0```

### 输出

```
Yes
2
3 5
3 6```

## 样例 #2

### 输入

```
1
5
3```

### 输出

```
Yes
1
2 4```

## 样例 #3

### 输入

```
2
3 1
3 1```

### 输出

```
Yes
0```

## 样例 #4

### 输入

```
2
0 0
1 2```

### 输出

```
No```

# 题解

## 作者：yuheng_wang080904 (赞：5)

## 题意

给定 $N$ 和两个非负整数列，问能否经过 $k(1\le k\le N)$ 次操作使得数列 $A$ 变成数列 $B$。

定义一次操作为选定一组 $(x,y)(0\le x<y\le 10^{18})$，并将数列 $A$ 中的每个数 $A_i$ 用 $(A_i+x)\bmod y$ 代替。

如果不能输出 `No`，否则就给出一种方案。

## 思路

首先 `No` 的情况是容易考虑的。若 $A_i=A_j(i\neq j)$ 且 $B_i\neq B_j$ 显然无解，否则均有解。

首先对于满足 $A_i=A_j(i\neq j)$ 且 $B_i=B_j$ 的 $(i,j)$，我们只需要考虑一个即可。

这样我们就保证了数列 $A$ 中的数互不相等，排序后有 $A_1<A_2<\cdots<A_n$。

对于 $n=1$，答案是容易的。定义一个极大数 $P>10^9$（ $P$ 也不能太大，否则爆 `long long` ），则可构造一组 $(x,y)=(P-a_1,P-b_1)$ 即可满足要求。

对于 $n\ge 2$ 的情况，思路就不是很容易想了。我们尽量希望 $A_i$ 的变动能够更灵活些，这样才能更容易使得 $A_i=B_i$。由于 $y>x$，我们考虑这样的 $y=x+\mathrm{max}(A)$。这样，除了数列 $A$ 中的最大值变成了 $0$，其余的都加上了 $x$。我们考虑这些点在数轴上的相对位置，就相当于去掉了最大数和第二大数之间的线段，然后加上了一个任意长度 $x$ 的线段在开头（原点左移 $x$）。这样 $n-1$ 次操作后，我们可以发现，原来的 $A_1$ 成为了最大数，而所有的数，以及所有数之间的相对位置都是任意的，似乎已经达到了我们的要求。有一个小技巧，我们可以让 $x_1\leftarrow x_1-A_1$，这样就相当于原来的 $A_1$ 作为原点。

对于一组符合条件的 $(x_1,x_2,\cdots,x_{n-1})$，那么 $n-1$ 次操作后，原来的数列 $A$ 所形成的数列 $C$ 是这样的：$C_2=0$，$C_{i+1}=C_i+x_{n+1-i}(2\le i\le n-1)$，$C_1=C_n+x_1$。由此要一步从数列 $C$ 变为数列 $B$（只能一步解决，因为 $k_{max}=N$ 且 $n_{max}=N$），则可使 $x_n=B_2$。若 $C_i=B_i-B_2$，则不免出现负数的情况。因此为了保证数列在变换中不出现负数的情况，必要时我们需要给一些数加上 $P$，那么 $y_n=P$，因为这些 $P$ 的倍数都必须去掉。因此 $C_i$ 可以这么表示 $C_i=B_i-B_2+P\times K_i$。再由数列 $C$ 的递推公式，有 $x_{n+1-i}=C_{i+1}-C_i=B_{i+1}-B_2+P\times K_{i+1}-(B_i-B_2+P\times K_i)=(B_{i+1}-B_i)+P\times(K_{i+1}-K_i)$。由于 $x_{n+1-i}\ge 0$，而 $B_{i+1}-B_i$ 正负不一定，因此可以这样设置数列 $K$，$K_1=N$，$K_i=i-2(2\le i\le n)$。这样就能保证所有数列的数均为非负整数，也就满足了要求。

综上，$C_i=B_i-B_2+P(i-2)(2\le i\le n)$，$C_1=B_1-B_2+Pn$。由此推得 $x_i=C_{n+2-i}-C_{n+1-i}(2\le i\le n-1)$，$x_1=C_1-C_n-A_1+P$，$y_i=x_i+\mathrm{max}(A)(1\le i\le n-1)$。最后 $(x_n,y_n)=(B_2,P)$。

## 代码

思路清晰，代码并不麻烦。

```cpp
ll n,bignum=1e10,x,y;
pair<ll,ll>a[1005];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i].first;
	for(int i=1;i<=n;i++)cin>>a[i].second;
	sort(a+1,a+n+1);
	n=unique(a+1,a+n+1)-a-1;
	for(int i=1;i<=n-1;i++){
		if(a[i].first==a[i+1].first)over("No")
	}
	cout<<"Yes"<<endl<<n<<endl;
	if(n==1){
		if(a[1].first>a[1].second)cout<<bignum-a[1].first<<" "<<bignum-a[1].second<<endl;
		else cout<<a[1].second-a[1].first<<" "<<bignum<<endl;
		return 0;
	}
	a[1].second+=bignum*n;
	for(int i=2;i<=n;i++)a[i].second+=bignum*(i-2);
	for(int i=n;i>=2;i--){
		if(i==n)x=bignum-a[1].first+a[1].second-a[n].second;
		else x=a[i+1].second-a[i].second;
		y=a[i].first+x;
		for(int j=1;j<=n;j++)a[j].first=(a[j].first+x)%y;
		cout<<x<<" "<<y<<endl;
	}
	cout<<a[2].second<<" "<<bignum<<endl;
	return 0;
}
```


---

## 作者：_LHF_ (赞：3)

整点不一样的做法。

不妨假设对于所有 $1\le i<n$ 有 $A_i<A_{i+1}$。

先考虑把两个操作分开怎么做，也就是说要么全局加，要么全局取模。

仔细思考一下就有一种 $2n+1$ 次的做法（其实就是今年信友队图灵杯的题目）。

还是稍微讲一下，首先如果 $B_i$ 也单增就很好做了，先把所有 $A$ 加上一个很大的数，然后维护 $i$ 使得 $i+1\sim n$ 已经弄好（即差分数组相等），然后每次把 $A_i$（显然是序列中的最大值）变成 $0$（模数为最大的数），然后再全局加。

如果 $B_i$ 不单增我们就考虑最后再取模，这样问题就解决了。

然后发现最后取了两次模，如果能合成一次，那么操作数就是 $2n$ 了。

怎么办呢？

考虑我们调整最初加上的一个很大的数，使得最后两次取模操作时一次的模数是另一次的模数的倍数，这样就能并成一次了。

于是就做完了。

---

## 作者：Leasier (赞：3)

什么神必 Ad-hoc。

------------

若存在两个 $i, j$ 满足 $A_i = A_j$ 但 $B_i \neq B_j$ 则无解。

否则，我们可以对 $A$ 去重，$B$ 留下对应项得到 $a, b$，设 $a, b$ 长度为 $n$。

首先判掉 $n = 1$ 的情况。

对于 $n \geq 2$ 的情况，人类智慧地，我们想到可以这样利用题中给出的操作：

- 令 $y = x + \max(a)$，则我们可以将 $\max(a)$ 清零，其他 $a_i$ 加上 $x$。

不妨设 $a$ 升序排列，则我们可以这样操作：

- 第一次删去 $a_n$，原序列变为 $[x_1 + a_1, x_1 + a_2, \cdots, x_1 + a_{n - 1}, 0]$。
- 第二次删去 $a_{n - 1}$，原序列变为 $[x_1 + x_2 + a_1, x_1 + x_2 + a_2, \cdots, x_1 + x_2 + a_{n - 2}, 0, x_2]$。
- ……

第 $n - 1$ 次后，原序列变为 $a'_1 = \displaystyle\sum_{i = 1}^{n - 1} x_i + a_1$，$a'_2 = 0$，$\forall 3 \leq i \leq n, a'_i = \displaystyle\sum_{j = n - i + 2}^{n - 1} x_i$。

如果再类似地进行一次操作，则原序列变为 $a'_1 = 0$，$\forall 2 \leq i \leq n, a'_i = \displaystyle\sum_{j = n - i + 2}^n x_i$。

若 $b_1 = 0$ 且 $b$ 单调递增，则问题得到解决。否则，我们令 $b'_i = b_i + \infty (i - 1)$，$x_1$ 任意，$\forall 2 \leq i \leq n, x_i = b'_{n - i + 2} - b'_{n - i + 1}$，再操作一次 $x_{n + 1} = a_1, y_{n + 1} = \infty$ 即可。

但这样做的操作次数可能达到 $n + 1$。~~可能恰好超出限制 /ng~~

在这个思路的背景下，一个与最后 $\bmod \infty$ 类似的操作显然是必须的。考虑减少前面的操作次数。

注意到 $n - 1$ 次操作后 $a_1$ 还会作为 $a'_1$ 中的一项，不妨考虑在第一次操作时消去 $a_1$：

- 第一次：$[x'_1, x'_1 + a_2 - a_1, \cdots, x'_1 + a_{n - 1} - a_1, 0]$，注意实际操作的 $x_1 = x'_1 - a_1$。

后续操作中每次 $\min(a) = 0$，则不再需要考虑该问题。

在 $n - 1$ 次操作后，原序列变为 $a'_1 = \displaystyle\sum_{i = 1}^{n - 1} x_i$，$a'_2 = 0$，$\forall 3 \leq i \leq n, a'_i = \displaystyle\sum_{j = n - i + 2}^{n - 1} x_i$。

考虑更改 $b'_i$ 的定义：$b'_1 = b_1 + \infty n$，$\forall 2 \leq i \leq n, b'_i = b_i + \infty(i - 1)$。

于是我们只需要最后操作一次 $x_n = b_2, y_n = \infty$ 即可。

我的代码中 $\infty$ 取 $2 \times 10^9$，事实上取 $\max(b) + 1$ 就够了。

代码：
```cpp
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

const int addition = 2e9;
int A[1007], B[1007], b[1007], p[1007];
ll a[1007], b_[1007], ansx[1007], ansy[1007];

bool cmp(const int x, const int y){
	return a[x] < a[y];
}

inline ll get_min(int n){
	ll ans = 0x7fffffffffffffffll;
	for (int i = 1; i <= n; i++){
		ans = min(ans, a[i]);
	}
	return ans;
}

inline ll get_max(int n){
	ll ans = 0;
	for (int i = 1; i <= n; i++){
		ans = max(ans, a[i]);
	}
	return ans;
}

inline void apply(int n, int x){
	for (int i = 1; i <= n; i++){
		a[i] = (a[i] + ansx[x]) % ansy[x];
	}
}

int main(){
	int N, n = 0;
	cin >> N;
	for (int i = 1; i <= N; i++){
		cin >> A[i];
	}
	for (int i = 1; i <= N; i++){
		cin >> B[i];
	}
	for (int i = 1; i <= N; i++){
		bool flag = true;
		for (int j = 1; j <= n; j++){
			if (A[i] == a[j]){
				if (B[i] != b[j]){
					cout << "No";
					return 0;
				}
				flag = false;
				break;
			}
		}
		if (flag){
			n++;
			a[n] = A[i];
			b[n] = B[i];
		}
	}
	if (n == 1){
		cout << "Yes" << endl;
		cout << 1 << endl;
		cout << ((b[1] - a[1]) % (b[1] + 1) + (b[1] + 1)) % (b[1] + 1) << " " << b[1] + 1;
		return 0;
	}
	int ansk = 0;
	for (int i = 1; i <= n; i++){
		p[i] = i;
	}
	sort(p + 1, p + n + 1, cmp);
	b_[p[1]] = b[p[1]] + (ll)addition * n;
	for (int i = 2; i <= n; i++){
		b_[p[i]] = b[p[i]] + (ll)addition * (i - 1);
	}
	ansk++;
	ansx[ansk] = b_[p[1]] - b_[p[n]] - a[p[1]];
	ansy[ansk] = ansx[ansk] + get_max(n);
	apply(n, ansk);
	for (int i = n; i >= 3; i--){
		ansk++;
		ansx[ansk] = b_[p[i]] - b_[p[i - 1]];
		ansy[ansk] = ansx[ansk] + get_max(n);
		apply(n, ansk);
	}
	ansk++;
	ansx[ansk] = b[p[2]];
	ansy[ansk] = addition;
	cout << "Yes" << endl;
	cout << ansk << endl;
	for (int i = 1; i <= ansk; i++){
		cout << ansx[i] << " " << ansy[i] << endl;
	}
	return 0;
}
```

---

## 作者：紊莫 (赞：1)

>本文详细解释了题解区暂未详细提到的计算 $x$ 的方面，并提供了较为详细的解释。

Hint：无解的判断是 $a_i=a_j \wedge b_i \not = b_j$，存在一种操作 $(x,y),y = x + \max{A}$，其中 $x$ 是任选的值，$\max{A}$ 表示 $A$ 中的最大值，可以使得 $A$ 中的最大值变为 $0$ 而其他数字只发生平移的关系。

首先对于本题，数字的顺序是无关的，所以我们在判断完无解情况后便可以直接排序加离散化，设离散化后的序列长度为 $m$。

借用 Atcoder 官方题解的配图：

![](https://img.atcoder.jp/agc063/dc0563aebbb5cc324533f63ea6b6ab2e.png)

我们清晰的看到了，对于一次形如 $(x,y),y = x + \max{A}$ 的操作，我们将 $A_1,A_2,\dots,A_{m-1}$ 向数轴正方向平移了 $x$ 的单位，然后将 $A_{m}$ 放到了 $0$ 点。

若干次操作后，我们会得到这样的形式：

![](https://img.atcoder.jp/agc063/1ea711aa697931f331e49fb934033aad.png)

对于我们的 $x$，除了 $x_1 \ge A_1$ 外，只要求 $x_i \ge 0$，因为第一步中 $x_1$ 这段距离实际上还含着一开始 $A_1$ 到原点的一段距离。

为了清晰，我们设 $a_i$ 表示操作完后每个点的位置，根据上图，我们有 $a_2 = 0, a_i = a_{i-1} + x_{n+2-i}(2<i\le n), a_1 = a_n + x_1$，不要忘记我们的目标是使得 $a_i = B_i$，这要求我们给出一种构造 $x$ 的方式。

首先 $a_2 = 0$，这个显然和我们最后要求的 $B_2$ 很可能不一样，那么就要求最后给 $a_2$ 加上 $B_2$，这一步可以进行一次操作 $(b_2, K)$ 来得到，此处我们设 $K = 2 \times 10^9$，也就是说我们现在要求构造的实际上是 $B_i - B_2$。

$a_3 = a_2 + x_{n + 2 - i} = B_3 - B_2$，那么我们就知道了第 $n + 2 - i$ 次操作就是 $x = B_3 - B_2$，按照这样递推下去，可以得到类似的形式 $B_i - B_{i-1}$。

那么考虑第一次操作，应该是 $B_1 - B_m - A_1$，因为需要减去一开始 $[0,A_1]$ 这一段的长度。

到这一步可以写出如下代码：

```cpp
#include <bits/stdc++.h>
#define int long long

#define F(i, a, b) for (int i = (a); i <= (b); i++)
#define dF(i, a, b) for (int i = (a); i >= (b); i--)
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int N = 200005, M = (N << 1), inf = 2e9, mod = 1e9 + 7;
int n, m, A[N], B[N], a[N], b[N]; map<int, int> mp;
void work(int x, int y) { 
    cout << (x %= y) << ' ' << y << '\n';
    F(i, 1, n) (a[i] += x) %= y;
}
signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n; F(i, 1, n) cin >> A[i]; F(i, 1, n) cin >> B[i];
    F(i, 1, n) F(j, 1, n) if (A[i] == A[j] && B[i] != B[j]) cout << "No", exit(0);
    F(i, 1, n) mp[A[i]] = B[i]; for (auto i : mp) a[++m] = i.first, b[m] = i.second;
    cout << "Yes\n" << m << '\n'; if (m == 1) work(b[1] - a[1] + inf, inf), exit(0);
    // F(i, 2, m) b[i] += (i - 1) * inf; b[1] += m * inf;
    work(b[1] - b[m] - a[1], b[1] - b[m] - a[1] + a[m]);
    dF(i, m - 1, 2) work(b[i + 1] - b[i], b[i + 1] - b[i] + a[i]); 
    // 此处写 b[i + 1] - b[i] 实际上就是上文的 b[i] - b[i - 1]，可以自己算算看。
    work(b[2], inf);
    return 0;
}
```

但是有一些样例会 RE，原因是后面的模数可能等于零，这一步我们可以使用注释的那句话，使得 $b$ 相邻的差都很大，也就不存在上述情况。

至此，我们在 $\mathcal{O}(n^2)$ 的时间复杂度内解决了此题。

---

## 作者：DaiRuiChen007 (赞：1)

[Problem Link](https://www.luogu.com.cn/problem/AT_agc063_c)

**题目大意**

> 给定 $a_1\sim a_n$ 每次操作能选 $x,y$ 是的 $a_i\gets (a_i+x)\bmod y$，$n$ 次操作内使得 $\{a_i\}$变成 $\{b_i\}$。
>
> 数据范围：$n\le 1000$。

**思路分析**

首先如果 $a_i=a_j,b_i\ne b_j$ 就一定不行，然后我们就能去重 $a_i$ 并升序排列。

手玩可以发现：令 $y=a_n+x$，那么就能让 $a_1\sim a_{n-1}$ 加上 $x$，然后 $a_n=0$。

逐步清空原本 $a_i$ 的影响，设第 $i$ 次操作取 $x_i$，那么最后 $a'_i=\sum_{j=n-i+2}^{n}x_j$。

那么 $a’$ 递增，如果 $b_1=0$ 且 $b$ 递增，直接取合适的 $x_1\sim x_n$ 即可解决。

否则考虑取充分大值 $A$，令 $b'_i=b_i+iA$，那么再操作一次 $x=b'_1,y=A$ 即可。

但是这样操作数 $n+1$，还要再优化一下，注意到 $x_1$ 没有什么用，那么 $a'_1=a_1+\sum_{i=1}^{n-1}x_i$，取一个合适的 $x_1=x'_1-a_1$，那么操作一次 $[x'_1,x'_1+a_2-a_1,\dots,x'_1+a_{n-1}-a_1,0]$，那么再来 $n-2$ 次操作就能消掉所有 $a_i$，此时 $a'_2,a'_3,\dots,a'_n,a'_1$ 递增，类似处理即可。

时间复杂度 $\mathcal O(n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=1005;
const ll inf=2e9;
map <ll,ll> pr;
ll A[MAXN],B[MAXN],a[MAXN],b[MAXN];
int n,m;
void opr(ll x,ll y) {
	printf("%lld %lld\n",x%=y,y);
	for(int i=1;i<=n;++i) a[i]=(a[i]+x)%y;
}
signed main() {
	scanf("%d",&m);
	for(int i=1;i<=m;++i) scanf("%lld",&A[i]);
	for(int i=1;i<=m;++i) {
		scanf("%lld",&B[i]);
		if(pr.count(A[i])&&pr[A[i]]!=B[i]) return puts("No"),0;
		pr[A[i]]=B[i];
	}
	for(auto it:pr) a[++n]=it.first,b[n]=it.second;
	printf("Yes\n%d\n",n);
	if(n==1) return opr(b[1]-a[1]+inf,inf),0;
	for(int i=3;i<=n;++i) b[i]+=(i-2)*inf;
	b[1]+=(n-1)*inf;
	opr(b[1]-b[n]-a[1],b[1]-b[n]-a[1]+a[n]);
	for(int i=n-1;i>=2;--i) opr(b[i+1]-b[i],b[i+1]-b[i]+a[i]);
	opr(b[2],inf);
	return 0;
}
```

---

## 作者：xcyyyyyy (赞：1)

### [AGC063C] Add Mod Operations  

神奇 ad-hoc 题。

如果存在 $a_i=a_j$ 且 $b_i \neq b_j$ 必定无解。否则我们将 $a$ 相同的 $b$ 去重。

下面展示一个构造，令 $A$ 是一个极大值。

我们假设 $n=1$，此时我们只需要找一个极大值，操作 $(A-a_1,A-b_1)$ 即可。

对于 $n\gt 1$ 的情况，有一种人类智慧的构造，想法是将 $a_i$ 的影响消除，注意到操作 $(x,a_i+x)$ 可以使 $a_i$ 为 $0$，可是取模的操作可能会影响其他的点，所以我们将 $a$ 从小到大排序后，从大到小依次操作。

我们设 $x_i$ 表示操作 $i$ 的时候的 $x$，那么一遍操作下来后：

$a_1=0$，$a_2=x_1$，$a_3=x_1+x_2$，$a_4=x_1+x_2+x_3$......

注意到 $x_i$ 可以由我们选择，若 $b_i$ 递增，我们就可以通过定 $x$ 的来构造。我们可以设 $b_i'=i \times A+b_i$，构造出 $b_i'$ 后最后操作 $(b_1,A)$ 即可。

此时操作次数是 $n+1$，注意到 $x_n$ 还可以是任意数，通过定 $x_n$ 的方式将 $a_1$ 的影响消除，就不用单独用 $x_1$ 来消除了，最后操作次数是 $n$ 了。具体操作可以由读者自己思考。

注意先去重再判 $n=1$。

---

