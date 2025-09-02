# Gellyfish and Forget-Me-Not

## 题目描述

Gellyfish and Flower are playing a game.

The game consists of two arrays of $ n $ integers $ a_1,a_2,\ldots,a_n $ and $ b_1,b_2,\ldots,b_n $ , along with a binary string $ c_1c_2\ldots c_n $ of length $ n $ .

There is also an integer $ x $ which is initialized to $ 0 $ .

The game consists of $ n $ rounds. For $ i = 1,2,\ldots,n $ , the round proceeds as follows:

1. If $ c_i = \mathtt{0} $ , Gellyfish will be the active player. Otherwise, if $ c_i = \mathtt{1} $ , Flower will be the active player.
2. The active player will perform exactly one of the following operations: 
  - Set $ x:=x \oplus a_i $ .
  - Set $ x:=x \oplus b_i $ .

Here, $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

Gellyfish wants to minimize the final value of $  x  $ after $  n  $ rounds, while Flower wants to maximize it.

Find the final value of $  x  $ after all $  n  $ rounds if both players play optimally.

## 说明/提示

In the first test case, there's only one round and Gellyfish is the active player of that round. Therefore, she will choose $ a_1 $ , and the final value of $ x $ is $ 0 $ .

In the second test case, Flower will be the active player in both rounds. She will choose $ a_1 $ and $ b_2 $ , and the final value of $ x $ is $ a_1 \oplus b_2 = 15 $ . Flower may also choose $ b_1 $ and $ a_2 $ instead for the same result of $ x=a_2 \oplus b_1 = 15 $ .

In the third test case, $ a_1 = b_1 $ so it doesn't matter what decision Gellyfish makes in the first round. In the second round:

- If Flower chooses $ a_2 $ , then $ x $ will become $ 7 $ . Gellyfish will choose $ b_3 $ in the third round, so the final value of $ x $ will be $ 4 $ .
- Otherwise, Flower chooses $ b_2 $ , then $ x $ will become $ 4 $ . Gellyfish will choose $ a_3 $ in the third round, so the final value of $ x $ will be $ 6 $ .

Flower wants to maximize the final value of $ x $ , so Flower will choose $ b_2 $ in the second round. Therefore, the final value of $ x $ will be $ 6 $ .

## 样例 #1

### 输入

```
5
1
0
2
0
2
12 2
13 3
11
3
6 1 2
6 2 3
010
4
1 12 7 2
4 14 4 2
0111
9
0 5 10 6 6 2 6 2 11
7 3 15 3 6 7 6 7 8
110010010```

### 输出

```
0
15
6
11
5```

# 题解

## 作者：zac2010 (赞：4)

### Part1：一些转化

为了使操作形式更加好看，我们在所有操作前，将答案异或上 $\oplus_{i=1}^n b_i$。然后令 $c_i=a_i\oplus b_i$。这样每次只需要决定一个 $c_i$ 选不选就行了。

显然转化后与原问题等价。
* 不选 $c_i$，对应着选择 $b_i\oplus 0=b_i$
* 选择 $c_i$，对应着选择 $b_i\oplus c_i=a_i$

### Part2：做法推导

运算与进制有关的，且答案求最值的，优先考虑**从高位往低位贪心**。

先考虑 $c_i\in [0,1]$ 怎么做。显然操作最后一个 $c_i=1$ 的人能决定答案。带入到原问题中，二进制最高位是 $0/1$，**取决于最后一个最高位为 $1$ 的数将要被谁操作**。

然而，前面那些最高位为 $1$ 的 $c_i$，能带来的影响也并非没有变化。我们用 $y$ 代表最后一个，$x$ 代表前面的 $c_i$。

为了方便考虑，假设前面的 $x$ 唯一，且操作 $y$ 的人希望最大化。注意到此时有 $x$ 选 $y$ 不选，或 $x$ 不选 $y$ 选。两种情况相差一个 $x\oplus y$ 的贡献。

换而言之，**$x$ 在此时的作用等价于一个 $c_i=x\oplus y$ 的数**。故而考虑将所有前面的 $x$ 异或上 $y$。

更低位可以效仿当前的做法。

最后将会存在若干**能决定一个位是 $0/1$ 的数**，按决定的位从高往低依次模拟两个人怎么选就行了。

* 注：这个过程其实很类似**线性基**。

### Part3：代码实现

```cpp
#include <bits/stdc++.h>
#define FL(i, a, b) for (int i = a; i <= b; ++i)
#define FR(i, a, b) for (int i = a; i >= b; --i)
const int N = 1e5 + 5;
long long T, n, V, x, y, a[N], b[N], c[N];
int main() {
	for (scanf("%lld", &T); T--; printf("%lld\n", V)) {
		scanf("%lld", &n), V = 0;
		FL(i, 1, n) scanf("%lld", &a[i]);
		FL(i, 1, n) scanf("%lld", &b[i]);
		FL(i, 1, n) scanf(" %c", &c[i]);
		FL(i, 1, n) a[i] ^= b[i], V ^= b[i];
		FR(j, 59, 0) {
			x = y = 0;
			FR(i, n, 1) if (a[i] >> j & 1) {
				a[i] ^= (x? x : (y = c[i], x = a[i]));
			}
			V ^= ((V >> j & 1) ^ (y - 48)) * x;
		}
	}
}
```

---

## 作者：flyfreemrn (赞：3)

## [div1D. Gellyfish and Forget-Me-Not](https://codeforces.com/contest/2115/problem/D)

首先是一个转化，我们可以让 $x$ 一开始等于 $\bigoplus a_i$，然后定义 $p_i = a_i \oplus b_i$，现在变成了选一些 $p_i$ 来异或 $x$。

对于异或操作，显然我们要从高到低考虑，对于第 $i$ 位（后文第 $i$ 位都指从高往低考虑）是 0 还是 1，取决于序列中 $p$ 的第 $i$ 位为 1 的最后一个位置 $p_u$ 由谁来操作，可以先是贪心的选择对自己更优的状态的。

假设我们找到最后一个第 $i$ 位为 1 的数在 $u$ 位置，找到其他第 $i$ 位为 1 的数的位置 $v$。那么 $u$ 最终是否要选其实是取决于前面选了多少个 $v$。因为我们是从高往低考虑，要保证这一位一定最优，所以如果我本来要选 $u$ 而前面选了奇数个 $v$，此时就不能选 $u$，反过来同理。

因此，对于所有的 $v$，其实是有**逼迫更改 $u$ 这一位决策** 的能力的，也可以认为**所有 $p_v$ 对答案的贡献等价于 $p_v \oplus p_u$**。

所以，我们每次找到 $u$ 和 $v$，贪心的选择 $p_u$ 之后更改 $p_v$ 的值，这样每轮以后就不存在第 $i$ 位之前有 1 的 $p$ 了（这个过程可以类比线性基）。因此我们只需要做 $\log V$ 轮就能得到最终的 $x$ 了。

最终时间复杂度 $O(n \log V)$。

---

## 作者：lfxxx (赞：1)

好题我懂得欣赏。

首先我们要化简问题，不妨令 $X = \oplus_{i=1}^n a_i,b_i \gets b_i \oplus a_i$。

问题变成可以选择异或上 $b_i$ 或者什么都不做。

考虑从高往低确定答案，当考虑最高位时显然最后一个 $1$ 的归属者可以控制这个位置。

但是你发现，高位的控制和低位的控制之间存在影响，也就是说当某个人决定用某个 $b_i$ 控制了某一位的值时，这个决策会对后面的局面产生影响。

在后面的决策时考虑前面决策的限制不好做，我们考虑在做前面的决策时对局面进行一些修改使得能对后面的决策产生正确的影响。

当你控制了第 $j$ 位时，用 $b_i$ 来控制这一位，首先你会对于当前的 $X$ 这一位上的值来决定你是否会选择当前某个 $b_i$，如果 $i$ 前面的第 $j$ 位为 $1$ 的 $b_k$ 了奇数个，你就会调整 $b_i$ 的选择以控制这一位，也就是让答案异或上 $b_i$，不难发现可以通过让 $i$ 前面所有第 $j$ 位为 $1$ 的 $b_k \gets b_k \oplus b_i$，并且由于你已经刻画了 $b_i$ 选择的所有情形并通过对局面的修改使得选择 $b_i$ 贡献已经能被表达出来，所以 $b_i$ 在后面的决策中会失效，也就是需要让 $b_i \gets 0$。

还有两个问题：

1. 第 $j$ 位 $b_i$ 做出的决策对 $i$ 后面第 $j$ 位为 $1$ 的 $b_k$ 有什么影响。

2. 如果某一位最后几个 $1$ 都是同一方的，那么到底应该用哪个 $1$ 控制这一位。

问题 $2$ 是好解决的，因为根据对控制位运行逻辑的分析不难发现用哪个 $1$ 控制都无所谓。

所以问题 $1$ 也解决了，直接用最后一个 $1$ 控制就没有这个问题了。

当然，在问题 $2$ 的分析中可以得知，实际上对后面的 $b_k$ 的影响也是 $b_k \gets b_k \oplus b_i$，因为实际上可以视作在用后面所有的 $b_k$ 和 $b_i$ 一同控制第 $j$ 位，进而可以发现最后几个 $1$ 选哪个都是等价的。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 1e5+114;
int a[maxn],b[maxn];
char c[maxn];
const int maxh = 60;
int ty[maxh],v[maxh];//第 i 位是 ty 则异或 v
int dight[maxn];
int n;
void work(){
    cin>>n;
    int X=0;
    memset(ty,0,sizeof(ty));
    memset(v,0,sizeof(v));
    for(int i=1;i<=n;i++) cin>>a[i],X^=a[i];
    for(int i=1;i<=n;i++) cin>>b[i],b[i]^=a[i],a[i]=0;
    for(int i=1;i<=n;i++) cin>>c[i];
    for(int i=59;i>=0;i--){
        for(int j=n;j>=1;j--){
            if((1ll<<i)&b[j]){
                if(c[j]=='0'){
                    if((1ll<<i)&X){
                        X^=b[j];
                        for(int k=1;k<j;k++){
                            if((1ll<<i)&b[k]) b[k]^=b[j];
                        }
                        b[j]=0;
                        break;
                    }else{
                        for(int k=1;k<j;k++){
                            if((1ll<<i)&b[k]) b[k]^=b[j];
                        }
                        b[j]=0;
                        break;
                    }
                }else{
                    if((1ll<<i)&X){
                        for(int k=1;k<j;k++){
                            if((1ll<<i)&b[k]) b[k]^=b[j];
                        }
                        b[j]=0;
                        break;
                    }else{
                        X^=b[j];
                        for(int k=1;k<j;k++){
                            if((1ll<<i)&b[k]) b[k]^=b[j];
                        }
                        b[j]=0;
                        break;
                    }
                }
            }
        }
    }
    cout<<X<<"\n";
    return ;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t;
    cin>>t;
    while(t--) work();
    return 0;
}
```

---

## 作者：冷却心 (赞：1)

赛后过的，但感觉难度 2900* 高了，为啥我场上不会做。

二选一异或有点复杂，我们不妨记 $c_i=a_i \oplus b_i$，这样如果让答案一开始为所有 $a_i$ 异或和，那么就是每次可以选择是否异或 $c_i$，使最终答案最大或最小。

我们经典地从高位往低位考虑，设 $d$ 为所有 $c_i$ 中最高位的位置，那么此时不论前面怎么决策，最后一个最高位为 $d$ 的位置总能使得这一位变成决策者希望的最大或最小。形式化地，我们记下标集合 $S$ 表示最高位为 $d$ 的 $c_i$ 的位置集合，记 $t=\max S$，那么如果 $S\setminus \{t\}$ 这个集合中最终操作得到答案的第 $d$ 位和 $c_t$ 的决策者想要的不同，那么 $c_t$ 就会异或进入答案，否则不变。于是我们先判断当前答案的第 $d$ 位是否需要 $c_t$ 异或，然后把全部 $c_i$ 中最高位是 $d$ 的位置全部异或上 $c_t$，表示如果这一位选进答案，那么 $c_t$ 是否选择的状态就要改变。容易发现这样操作一次最高位会降低，并且后面的操作不会改变更高的位置，所以最优。

时间复杂度 $\mathcal O(n\log V)$。

```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int N = 1e5 + 10;
int n; LL A[N]; char S[N];

int main() {
	freopen(".in", "r", stdin); freopen(".out", "w", stdout);
	ios :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int _; cin >> _;
	while (_ --) {
		cin >> n; LL Ans = 0, x;
		for (int i = 1; i <= n; i ++) cin >> A[i], Ans ^= A[i];
		for (int i = 1; i <= n; i ++) cin >> x, A[i] ^= x;
		cin >> (S + 1);
		for (int i = 59; i >= 0; i --) {
			int t = n; while (t && !((A[t] >> i) & 1)) t --;
			if (!t) continue;
			if (((Ans >> i) & 1) ^ (S[t] == '1')) Ans ^= A[t];
			for (int j = 1; j <= n; j ++) if ((A[j] >> i) & 1) A[j] ^= A[t];
		} cout << Ans << "\n";
	}
	return 0;
}
```

---

## 作者：orz_z (赞：1)

首先选择 $a_i,b_i$ 可以转化为令 $c_i=a_i\oplus b_i$，选择 $c_i$ 或者不选，且初始 $x=\oplus_{i=1}^{n}b_i$。

考虑从高到底位贪心，在满足高位为最优解时，观察当前第 $x$ 位为 $1$ 的位置 $i_1,\cdots,i_k$，根据 $i_k$ 是由 A 控制还是 B 控制，以及 $x$ 这一位上的值，可以得出类似当 $i_1,\cdots i_{k-1}$ 都不选时，$i_k$ 是否选的限制。

然后当翻转了 $i_1,\cdots i_{k-1}$ 中的其中一个时，$i_k$ 是否选的状态也发生变化，这可以转化为令 $\forall j\in[1,k],c_{i_j}\leftarrow c_{i_j}\oplus c_{i_k}$。

这样处理后第 $x$ 位刚好全是 $0$ 了，故满足当前高位都是最优解，只需考虑子问题即可。

时间复杂度 $\mathcal O(n\log W)$。


```cpp
int res = 0;
F(i, 1, n) {
  res ^= b[i];
  a[i] ^= b[i];
}
vi id;
dF(j, 59, 0) {
  id.clear();
  F(i, 1, n) if(a[i] >> j & 1) id.pb(i);
  if(id.empty()) continue;
  int z = id.back();
  if((res >> j & 1) ^ (str[z] - '0')) {
    res ^= a[z];
  }
  for(int v : id) a[v] ^= a[z];
}
cout << res << '\n';
```

---

## 作者：XZhuRen (赞：0)

好玩的贪心，建议升紫，需要对线性基有较深理解。

洛谷的位运算符不用 $\And,|,\oplus$ 有点难读啊。

---

贪心，对于某一位 $k$，求解对于它的贪心，设 $base=2^k$。

发现真正决定答案的元素是最后一个 $a_i \operatorname{and} base \not= b_i\operatorname{and} base$ 的数，即 $((a_i \operatorname{xor} b_i)\operatorname{and} base)=1$ 的数。

方便操作，把所有的 $a_i \to a_i \operatorname{xor} b_i$，$x \to x \operatorname{and} a_i$。

发现接下来的问题即是否选 $a_i$，考虑从高位到低位贪心，我们在决定这一位答案的 $a_d$ 贪心。

发现若在决策中选择了之前**对这一位有影响**的元素，则我们为了保证贪心的最优性，会改变 $a_d$ 的选择状态。

这个类似线性基的求最值操作，直接 $\forall (a_i\operatorname{and} base)=base,a_i\to a_i \operatorname{xor} a_d$。

---

## 作者：E_firework (赞：0)

由于题意足够简单，这里不提供简要题意。

### 解法

下文中所有数字在二进制下考虑。

这种通过位运算操作最大/最小化一个整数变量的题目正解大概率是按位贪心，也有可能是用线性基或 FWT 等方法处理，不过这个题只需要按位贪心就行了。

为了方便后续的思考，我们对原题意做一步转化：令 $x\leftarrow \bigoplus_{i=1}^n a_i$。这时每一轮的操作变为了选择令 $x\gets x\oplus a_i\oplus b_i$ 或者不操作。我们设 $c_i=a_i\oplus b_i$。

考虑从大到小地枚举数位，假设现在处理到了第 $i$ 位且所有的 $c$ 的最高位都不超过 $i$。我们考虑找到最后一个最高位为 $i$ 的 $c$，设其为 $c_j$，那么第 $j$ 轮的操作者将有权力决定最终 $x$ 的第 $i$ 位是什么。无论之前的操作对 $x$ 的第 $i$ 位产生了何种影响，都可以在第 $j$ 轮消除。并且第 $j$ 轮之后 $x$ 的第 $i$ 位也无法再改变。于是可以将所有满足 $k<j$ 且 $c_k$ 的最高位为 $i$ 的 $c_k$ 异或上 $c_j$，这表示第 $k$ 轮操作对 $x$ 的第 $i$ 位的影响可以在第 $j$ 轮被消除。这样处理之后只有 $c_j$ 的最高位是 $i$。这时可以直接根据现在 $x$ 的第 $i$ 位的值和第 $j$ 轮的操作方决定 $x$ 是否需要异或上 $c_j$。因为第 $j$ 轮的决策已经做完了，所以我们可以简单地在操作序列中删除第 $j$ 轮。这时第 $i$ 位的决策就做完了。因为我们可以保证在上述处理后所有的 $c$ 的最高位都不超过 $i-1$。于是可以继续用这个做法处理第 $i-1$ 位的决策。那么这道题就做完了。

时间复杂度为 $O(\sum n\log V)$，其中 $V$ 表示值域。

[#322599098](https://codeforces.com/contest/2115/submission/322599098)（实现与上述算法略有区别）

---

