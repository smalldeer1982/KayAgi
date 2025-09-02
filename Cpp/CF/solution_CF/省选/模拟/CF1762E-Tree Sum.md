# Tree Sum

## 题目描述

Let us call an edge-weighted tree with $ n $ vertices numbered from $ 1 $ to $ n $ good if the weight of each edge is either $ 1 $ or $ -1 $ and for each vertex $ i $ , the product of the edge weights of all edges having $ i $ as one endpoint is $ -1 $ .

You are given a positive integer $ n $ . There are $ n^{n-2} \cdot 2^{n-1} $ distinct $ ^\dagger $ edge-weighted trees with $ n $ vertices numbered from $ 1 $ to $ n $ such that each edge is either $ 1 $ or $ -1 $ . Your task is to find the sum of $ d(1,n)^\ddagger $ of all such trees that are good. Since the answer can be quite large, you only need to find it modulo $ 998\,244\,353 $ .

 $ ^\dagger $ Two trees are considered to be distinct if either:

- there exists two vertices such that there is an edge between them in one of the trees, and not in the other.
- there exists two vertices such that there is an edge between them in both trees but the weight of the edge between them in one tree is different from the one in the other tree.

Note that by [Cayley's formula](https://rb.gy/hho7vu), the number of trees on $ n $ labeled vertices is $ n^{n-2} $ . Since we have $ n-1 $ edges, there are $ 2^{n-1} $ possible assignment of weights(weight can either be $ 1 $ or $ -1 $ ). That is why total number of distinct edge-weighted tree is $ n^{n-2} \cdot 2^{n-1} $ .

 $ ^\ddagger $ $ d(u,v) $ denotes the sum of the weight of all edges on the unique simple path from $ u $ to $ v $ .

## 说明/提示

In the first test case, there is only $ 1 $ distinct good tree. The value of $ d(1,2) $ for that tree is $ -1 $ , which is $ 998\,244\,352 $ under modulo $ 998\,244\,353 $ .

In the second test case, the value of $ d(1,1) $ for any tree is $ 0 $ , so the answer is $ 0 $ .

In the third test case, there are $ 16 $ distinct good trees. The value of $ d(1,4) $ is:

- $ -2 $ for $ 2 $ trees;
- $ -1 $ for $ 8 $ trees;
- $ 0 $ for $ 4 $ trees;
- $ 1 $ for $ 2 $ trees.

The sum of $ d(1,4) $ over all trees is $ 2 \cdot (-2) + 8 \cdot (-1) + 4 \cdot (0) + 2 \cdot (1) = -10 $ , which is $ 998\,244\,343 $ under modulo $ 998\,244\,353 $ .

## 样例 #1

### 输入

```
2```

### 输出

```
998244352```

## 样例 #2

### 输入

```
1```

### 输出

```
0```

## 样例 #3

### 输入

```
4```

### 输出

```
998244343```

## 样例 #4

### 输入

```
10```

### 输出

```
948359297```

## 样例 #5

### 输入

```
43434```

### 输出

```
86232114```

# 题解

## 作者：Leasier (赞：6)

注意到样例中除了答案为 $0$ 的样例 2 之外，$n$ 均为偶数且答案非 $0$。

接下来我们可以观察出下面的结论：

- Observation 1：当且仅当 $n$ 为偶数时符合条件的树存在。

证明：若一棵 $n$ 个点的树满足条件，则 $(-1)^n = ((\pm 1)^2)^{n - 1} = 1$，则 $n$ 必须为偶数。

- Observation 2：当 $n$ 为偶数且树的形态固定，满足条件的填边权方案唯一。

证明：像 Prufer 序列那样依次给叶子与其相连的边填数并删除叶子，可以得到唯一的填数方案。

- Observation 3：一条边 $(u, v)$ 权值为 $1$ 当且仅当割断这条边后 $u$ 或 $v$ 所在连通块大小为偶数。

证明：连上前还是两边分别像上面那样填（但是把 $u, v$ 分别当成根），若连通块大小为奇数则两边恰好只有 $u, v$ 还得乘 $-1$ 才可以满足条件，若连通块大小为偶数则两边都满足条件了（即直接填 $1$ 就行）。

现在我们来考虑怎么算。

显然可以逐边算贡献。枚举 $1$ 所在连通块大小 $i$，则 $n$ 所在连通块大小为 $n - i$。

- 边权为 $(-1)^i$。
- 从剩下 $n - 2$ 个点中选出 $i - 1$ 个点扔到 $1$ 那边、余下 $n - i - 1$ 个点扔到 $n$ 那边去，方案数为 $C_{n - 2}^{i - 1}$。
- 两边随便构造无根树，方案数为 $f_i f_{n - i}$，其中 $f_n = n^{n - 2}$。
- 两边随便各选一个点连边，方案数为 $i(n - i)$。

对每个 $i$ 把这些东西乘起来再求和即可。时间复杂度为 $O(n \log n)$。

代码：
```cpp
#include <stdio.h>

typedef long long ll;

const int mod = 998244353;
ll fac[500007], inv_fac[500007];

inline ll quick_pow(ll x, ll p, ll mod){
	ll ans = 1;
	while (p){
		if (p & 1) ans = ans * x % mod;
		x = x * x % mod;
		p >>= 1;
	}
	return ans;
}

inline void init(int n){
	fac[0] = 1;
	for (register int i = 1; i <= n; i++){
		fac[i] = fac[i - 1] * i % mod;
	}
	inv_fac[n] = quick_pow(fac[n], mod - 2, mod);
	for (register int i = n - 1; i >= 0; i--){
		inv_fac[i] = inv_fac[i + 1] * (i + 1) % mod;
	}
}

inline ll comb(int n, int m){
	if (n < 0 || m < 0 || n < m) return 0;
	return fac[n] * inv_fac[m] % mod * inv_fac[n - m] % mod;
}

inline ll f(int n){
	if (n == 1) return 1;
	return quick_pow(n, n - 2, mod);
}

int main(){
	int n;
	scanf("%d", &n);
	if (n % 2 == 1){
		printf("0");
		return 0;
	}
	ll ans = 0;
	init(n);
	for (register int i = 1; i < n; i++){
		if (i % 2 == 0){
			ans = (ans + (ll)i * (n - i) % mod * comb(n - 2, i - 1) % mod * f(i) % mod * f(n - i) % mod) % mod;
		} else {
			ans = ((ans - (ll)i * (n - i) % mod * comb(n - 2, i - 1) % mod * f(i) % mod * f(n - i) % mod) % mod + mod) % mod;
		}
	}
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：FLAMEs_ (赞：2)

做完真长脑子了！（喜

---

需要读者**理解** $\text{Prüfer}$ 序列。

- 一个无向图的生成树个数为 $n^{n-2}$ 个。

$\text{Prüfer}$ 序列的长度为 $n-2$，而序列中的每个元素都有 $n$ 种放法，由此可推得上方结论。

---

对于这题，首先有结论 $1$：当 $n$ 是奇数的时候，不存在这样的树。

证明：假设 $n$ 为奇数时有合法方案。则此时“每一个节点所连的边的边权之积是 $-1$ ”这一条件被满足，此时边权之积为 $(-1)^n=-1$。但显然，每一条边都会被计算两次（连接两个点）。此时边权之积应为 $(\pm1)^{2n}=1$，与上文所推矛盾。故 $n$ 不能为奇数。

结论 $2$：当树的形态确定时，填边权的方案数为 $1$ 。

证明可以参考 $\text{Prüfer}$ 序列的构建方式。（给限制最少的叶子填数，然后删去叶子，这样可以得到唯一的方案。）

结论 $3$：构建时，对于任意一条边 $(u,v)=1$，割去该边后剩下两个联通块大小均为偶数。

类似分治思想，当一条边边权为 $1$ 时对正负性无影响。可以将树拆成两部分，然后由结论 $1$ 可证。

放置方法：

割掉一条边，令 $1$ 和 $n$ 所在连通块不同。枚举 $1$ 所在连通块大小 $i$。

- 边权大小为 $(-1)^i$。

- 可以选择 $n-2$ 个节点中的 $i-1$ 个节点与 $1$ 连通。方案数为 $\binom{n-2}{i-1}$。 

- 生成树随便搞。方案数为 $i^{i-2}\times(n-i)^{n-i-2}$。

- 割掉的一条边可能有 $i\times(n-i)$ 种情况。

答案为：

$\sum_{i=1}^{n-1}(-1)^i\times\binom{n-2}{i-1}\times i^{i-1}\times(n-i)^{n-i-1}$。

---

## 作者：MurataHimeko (赞：1)

小清新题，做完后感觉神清气爽。

其实也算是给计数题提供了一个思考的方向。

对于一颗固定的树，考虑求出它有几种染色方案。

不妨从最特殊的叶子节点开始，它连向父亲的边权一定为 $-1$，确定边权后删掉这个叶子节点。那么一轮结束后，有新的点成为了叶子节点。对于一个新的叶子节点，如果它的权值为 $-1$，那么它连向父亲的边权为 $1$，并不影响它父亲的正负，所以可以继续将这个点删除，直到不存在权值为 $-1$ 的叶子。

容易发现根据上述过程，一棵树对应的边权是唯一的。继续分析，不妨稍微调整一下删点的过程，对于一个叶子，当且仅当它的所有兄弟也都是叶子时，才将这些点删除。如果一次连着删除奇数个叶子，那么他们的父亲的权值是 $-1$，也会连带着删除。所以一次删除必然删除偶数个点。那么当 $n$ 是奇数时答案为 $0$。

其实这也告诉了我们如何计数：

枚举 $1$ 到 $n$ 路径上的一条边 $(u,v)$，当 $u,v$ 所在连通块都为偶数时，边权为 $1$，否则为 $-1$。

那么枚举 $1,n$ 所在连通块大小，用 prufer 计算出这两个连通块的方案数，再乘上连通块大小之积即可。

即:

$$ ans = \sum_{i=0}^{n-2} (-1)^{i+1} \binom{n-2}{i} (i+1)^{i}(n-i-1)^{n-i-2} $$



---

## 作者：User_Authorized (赞：1)

## 题意
对于一棵 $n$ 个节点的树 $T$，定义 $\operatorname{good}(T)$ 为真当且仅当边权 $w \in \left\{-1,1\right\}$ 且对于任意节点 $u$，均有 $\displaystyle f(u) = \prod\limits_{\left(u, v\right) \in E} w\left(u, v\right) = -1$。

求

$$\sum\limits_{\operatorname{good}(T)} \operatorname{dist}(1, n) \bmod 998244353$$

## 题解
分析题目性质。

### 性质 $1$

> 若 $n$ 为奇数，那么不存在符合性质的树。

因为题目中要求对于任意节点 $u$ 均有 $f(u) = -1$，所以当 $n$ 为奇数时，$\displaystyle \prod\limits_{i = 1}^{n} f(i) = \left(-1\right)^n = -1$。

考虑计算每条边对 $\displaystyle \prod\limits_{i = 1}^{n} f(i)$ 的贡献，可以得出对于任意一条边 $\left(u, v\right) \in E$，无论其边权如何，均会对 $f(u)$ 和 $f(v)$ 产生共两次贡献，即产生的贡献为 $w\left(u, v\right)^2 = 1$，进而可以得出 $\displaystyle \prod\limits_{i = 1}^{n} f(i) = 1$，与 $\displaystyle \prod\limits_{i = 1}^{n} f(i) = \left(-1\right)^n = -1$ 冲突。

### 性质 $2$

> 若已经确定了树的形态，那么仅有一种边权分配方式使其符合要求。

设 $\operatorname{pw}(u) = w\left(u, fa_u\right)$，即 $u$ 向其父亲节点相连的边的边权。考虑首先钦定任意一点为根，然后从叶子节点向上归纳，对于叶子节点 $v$，显然有 $\displaystyle f(v) = \operatorname{pw}(v) \Rightarrow \operatorname{pw}(v) = -1$。对于任意非叶子节点，有 $\displaystyle f(u) = -1 \Rightarrow \operatorname{pw}(u) = \left(-1\right)\prod\limits_{v \in \operatorname{son}_u} \operatorname{pw}(v)$。由于树的形态唯一，所以每个节点的 $\displaystyle \operatorname{pw}(u)$ 唯一，进而边权分配方式唯一。

### 性质 $3$

> 若边 $\left(u, v\right)$ 一侧有 $k$ 个节点，那么该边边权为 $\left(-1\right)^k$。

该性质等价于 $pw(u) = \left(-1\right)^{size_u}$，考虑使用数学归纳法证明。该结论对于叶子节点显然，对于非叶子节点 $u$，有

$$\operatorname{pw}(u) =  \left(-1\right)\prod\limits_{v \in \operatorname{son}_u} \operatorname{pw}(v) = \left(-1\right)^{1 + \sum\limits_{v \in \operatorname{son}_u} size_v} = \left(-1\right)^{size_u}$$

---

接下来计算答案，考虑按边枚举贡献。

对于一条边 $\left(u, v\right)$，如果其能产生贡献，那么该边一定联通点 $1$ 和 点 $n$ 所属的联通块，我们设点 $1$ 所属的连通块有 $k$ 个点，那么根据上文推出的性质可得这条边的边权为 $\displaystyle \left(-1\right)^k$。下面考虑有多少种符合要求的树 $T$ 种会出现这类边（这里这类边指的是联通点 $1$ 和 点 $n$ 所属的联通块且点 $1$ 所属的连通块有 $k$ 个点的边）。

首先，因为节点是标号的，所以将点划分为两个连通块的方案数为 $\displaystyle {n - 2 \choose k - 1}$。对于每个连通块考虑子树的形态，有 $\displaystyle k^{k - 2} \left(n - k\right)^{n - k - 2}$ 种方案。考虑边联通的为哪个点对，有 $\displaystyle k \times \left(n - k\right)$ 种方案。所以对于这类边，会包括他的树的种类数为

$${n - 2 \choose k - 1}k^{k - 2} \left(n - k\right)^{n - k - 2}k \times \left(n - k\right)$$

通过枚举边的种类 $k$，可以得出总的答案

$$\sum\limits_{k = 1}^{n - 1} {n - 2 \choose k - 1}k^{k - 1} \left(n - k\right)^{n - k - 1}$$

该式可以以 $\displaystyle \mathcal{O}(n \log n)$ 的复杂度完成计算，可以通过本题。

## Code
```cpp
//Codeforces - 1762E
#include <bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;

constexpr valueType MOD = 998244353;

bool ModOperSafeModOption = false;

template<typename T1, typename T2, typename T3 = valueType>
void Inc(T1 &a, T2 b, const T3 &mod = MOD) {
    if (ModOperSafeModOption) {
        a %= mod;
        b %= mod;

        if (a < 0)
            a += mod;

        if (b < 0)
            b += mod;
    }

    a = a + b;

    if (a >= mod)
        a -= mod;
}

template<typename T1, typename T2, typename T3 = valueType>
void Dec(T1 &a, T2 b, const T3 &mod = MOD) {
    if (ModOperSafeModOption) {
        a %= mod;
        b %= mod;

        if (a < 0)
            a += mod;

        if (b < 0)
            b += mod;
    }

    a = a - b;

    if (a < 0)
        a += mod;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 sum(T1 a, T2 b, const T3 &mod = MOD) {
    if (ModOperSafeModOption) {
        a %= mod;
        b %= mod;

        if (a < 0)
            a += mod;

        if (b < 0)
            b += mod;
    }

    return a + b >= mod ? a + b - mod : a + b;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 sub(T1 a, T2 b, const T3 &mod = MOD) {
    if (ModOperSafeModOption) {
        a %= mod;
        b %= mod;

        if (a < 0)
            a += mod;

        if (b < 0)
            b += mod;
    }

    return a - b < 0 ? a - b + mod : a - b;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 mul(T1 a, T2 b, const T3 &mod = MOD) {
    if (ModOperSafeModOption) {
        a %= mod;
        b %= mod;

        if (a < 0)
            a += mod;

        if (b < 0)
            b += mod;
    }

    return (long long) a * b % mod;
}

template<typename T1, typename T2, typename T3 = valueType>
void Mul(T1 &a, T2 b, const T3 &mod = MOD) {
    if (ModOperSafeModOption) {
        a %= mod;
        b %= mod;

        if (a < 0)
            a += mod;

        if (b < 0)
            b += mod;
    }

    a = (long long) a * b % mod;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 pow(T1 a, T2 b, const T3 &mod = MOD) {
    if (ModOperSafeModOption) {
        a %= mod;
        b %= mod - 1;

        if (a < 0)
            a += mod;

        if (b < 0)
            b += mod - 1;
    }

    T1 result = 1;

    while (b > 0) {
        if (b & 1)
            Mul(result, a, mod);

        Mul(a, a, mod);
        b = b >> 1;
    }

    return result;
}

class Inverse {
public:
    typedef ValueVector container;

private:
    valueType size;
    container data;
public:
    explicit Inverse(valueType n) : size(n), data(size + 1, 0) {
        data[1] = 1;

        for (valueType i = 2; i <= size; ++i)
            data[i] = mul((MOD - MOD / i), data[MOD % i]);
    }

    valueType operator()(valueType n) const {
        return data[n];
    }
};

int main() {
    valueType N;

    std::cin >> N;

    Inverse Inv(N);

    ValueVector Fact(N + 1, 1), InvFact(N + 1, 1);

    Fact[0] = 1;
    InvFact[0] = 1;
    for (valueType i = 1; i <= N; ++i) {
        Fact[i] = mul(Fact[i - 1], i);
        InvFact[i] = mul(InvFact[i - 1], Inv(i));
    }

    typedef std::function<valueType(valueType, valueType)> CalcFunction;

    CalcFunction C = [&Fact, &InvFact](valueType n, valueType m) -> valueType {
        if (n < 0 || m < 0 || n < m)
            return 0;

        return mul(Fact[n], mul(InvFact[m], InvFact[n - m]));
    };

    valueType ans = 0;

    for(valueType i = 1; i < N; ++i) {
        valueType sum = 1;

        Mul(sum, C(N - 2, i - 1));
        Mul(sum, mul(i, N - i));
        Mul(sum, mul(pow(i, i - 2), pow(N - i, N - i - 2)));

        if (i & 1)
            Dec(ans, sum);
        else
            Inc(ans, sum);
    }

    std::cout << ans << std::endl;

    return 0;
}
```

---

## 作者：Cxny (赞：1)

小结论：

结论 $1$：设 $val_i$ 表示与 $i$ 相连的边权之积，$wei$ 表示边权，则 $\prod val_i=(-1)^n=(\prod wei_i)^2=1$。因此，$n$ 为奇数时一定无解。

结论 $2$：在有解时，**一种树的形态唯一对应一种染色方案**。从叶子节点向上染色可知正确性。

观察题目，发现不是计数而是算 $1$ 到 $n$ 路径长度和。

考虑拆边算贡献。

继续发掘性质。

结论 $3$：一条边权值为 $-1$ 当且仅当**其连接的两个连通块大小均为奇数**，否则这条边边权为 $1$。同样自底向上染色，归纳可以证明。

加上题目已经提示了 $n$ 个节点有标号无根树的个数是 $n^{n-2}$，可以直接枚举一侧连通块大小计算贡献。

设 $tree_{i}$ 表示 $i$ 个点形成的有标号无根树数量，则
$$
tree_i=\begin{cases}
1&i=1\\
i^{i-2}&i>1
\end{cases}
$$
钦定 $1$ 所在连通块大小为 $i$， 
$$
ans=\sum_{i=1}^n\binom{n-2}{i-1}tree_i\cdot tree_{n-i}\cdot i(n-i)
$$
上式相当于：

- 先从剩下 $n-2$ 个点中选出 $i-1$ 个点形成 $1$ 所在连通块。
- 两侧树的形态各有 $tree_i$ 与 $tree_{n-i}$ 种。

- 边的左右端点分别有 $i$ 与 $n-i$ 种。

直接算。

```cpp
const int maxn = 5e5 + 10, mod = 998244353;
int n;
ll fac[maxn], ifac[maxn], tr[maxn], ans;
ll qpow(int x, int y){
    ll ret = 1;
    while(y){
        if(y & 1) ret = ret * x % mod;
        x = 1ll * x * x % mod, y >>= 1;
    }
    return ret;
}
ll C(int x, int y){
    return fac[x] * ifac[y] % mod * ifac[x - y] % mod;
}
signed main(){
    scanf("%d", &n);
    if(n & 1) return puts("0"), 0;
    fac[0] = 1;
    for(int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % mod;
    ifac[n] = qpow(fac[n], mod - 2);
    for(int i = n; i >= 1; i--) ifac[i - 1] = ifac[i] * i % mod;
    for(int i = 2; i <= n; i++) tr[i] = qpow(i, i - 2);
    tr[1] = 1;
    for(int i = 1; i <= n; i++)
        ans = (ans + C(n - 2, i - 1) * tr[i] % mod * tr[n - i] % mod * i % mod * (n - i) % mod * ((i & 1) ? -1 : 1) + mod) % mod;
    printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：Alex_Wei (赞：1)

设 $d_i$ 表示与 $i$ 相连的边权乘积。

因为每条边对 $\prod d_i$ 的贡献恒为 $(\pm 1) ^ 2 = 1$，所以，当 $n$ 为奇数时，$\prod d_i = -1$ 的要求无法被满足，不存在合法的树，答案为 $0$。

否则，我们通过经典的剥叶子套路，证明当树的形态确定时，赋边权使得合法的方案唯一。

直接枚举 $d(1, n)$ 显然不好做，我们将贡献摊至路径上的每条边。直接枚举产生贡献的边两侧的子树大小 $L, n - L$。当 $L$ 为奇数时，因为两棵子树内部 $\prod d_i$ 为 $1$，为使得除了与当前边相连的两点以外的所有点的 $d_i = -1$，则与当前边相连的两点的 $d_i = 1$，故当前边权值为 $-1$。当 $L$ 为偶数时，当前边权值为 $1$。

求方案数：两侧子树均选择一个根作为两端。因为大小为 $n$ 的有标号有根树的数量为 $n ^ {n - 1}$，再从 $2\sim n - 1$ 中选出与 $1$ 同侧的 $L - 1$ 个点，故方案数为 $L ^ {L - 1} (n - L) ^ {n - L - 1} \binom {n - 2} {L - 1}$。

时间复杂度 $\mathcal{O}(n\log n)$。[代码](https://codeforces.com/contest/1762/submission/185406946)。

---

## 作者：MSqwq (赞：1)

题意：  
我们定义边加权树为一棵 $n$ 个点的树，边权只能为 $-1$ 或 $1$。那么 $n$ 个点 一共可以构成 $n^{n-2}\times 2^{n-1}$ 棵边加权树。  
定义对于每个顶点 $i$，所有端点为 $i$ 的边的权值的乘积为 $-1$，那么我们称这棵为好的边加权树。  
求每棵好的边加权树，$1$ 到 $n$ 的最短路径的和，答案模 $998244353$。  


------------
题解：  
首先要推一堆结论：  
1. 当 $n$ 为奇数时，一定无解。很好证明，我们定义每个点的贡献：所有端点为为该端点的边的权值的乘积。因为为奇数，那么所有端点的贡献之积一定为 $-1$，因为是 $n\times -1$ 嘛。换个角度看，如果用边的贡献算所有端点的的贡献之积呢，那么对于每条边一定算了两遍，因为该边有两个顶点，在单独算的时候每个顶点会乘一遍，两个点就是两遍，那么我们可以得出结论，每条边的贡献都为 $1$，那么贡献之积一定也为 $1$ 与前面矛盾，所以一定无解。  
2. 对于每颗边加权树，一定是唯一解，从叶子节点开始思考，叶子节点只有一条边，那么一定为 $-1$，继续往上面思考，每个父节点，只剩下一条边未确定，因为所有边的乘积确定为 $-1$ 所以连向上的那个点也一定唯一。那么可以一直递推到根，所以具有唯一解。  
3. 根据性质 $2$ 我们甚至可以求出每条边的权值。考虑一个节点，若包括它本身的子树大小为 $x$，那么该边的权值为 $(-1)^x$ 很好证明，该点已经确定的边同样是 $(-1)^{x_{son}}$ 递归到最后就到叶子节点，而叶子节点的边我们确定是 $-1$ 所以可以归纳到该边为 $(-1)^x$。  

得出这些结论的你发现和这题并没有什么鸟用，你还是一头雾水，不知道怎么推柿子。  
然后回到本题，要求 $1$ 到 $n$ 的最短路径，那我们就考虑在路径上的边，其实就是这条边把整棵树分成两半，$1$ 在一边，$n$ 在另一边。继续结合我们的结论 $3$，那么 $1$ 和 $n$ 确定了，你得去构造你的子树了吧，那么我们设 $i$ 号边的子树大小就是 $i$，那么该子树选点可以有 $\binom{n-2}{i-1}$ 种选法，那么这条边怎么连呢，一边有 $i$ 个点，另一边为 $n-i$ 个点，这条边都可以连，那么就是一共有 $i\times (n-i)$ 种连法，再考虑两边的树结构那不就是 $i^{i-1}\times (n-i)^{n-i-2}$ 了嘛，就根据题意，或者根据 [凯莱公式](https://baike.baidu.com/item/%E5%87%AF%E8%8E%B1%E5%85%AC%E5%BC%8F/55604647?fr=aladdin)。那么最后根据乘法原理，搞在一起就好啦。  
结论就是：  
$\sum\limits_{i=1}^{n-1}(-1)^i\times\binom{n-2}{i-1}\times i\times(n-i)\times i^{i-2} \times (n-i)^{n-i-2}$  
基本没啥细节吧，随便搬个板子过来，一个循环就完了。  
代码：  
```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int mod=998244353;
const int INF=0x3f3f3f3f;

inline ll read()
{
	ll x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-'0',c=getchar();}
	return x*f;
}

const int N=1e6+10;
ll f[N],invf[N];
ll ksm(ll a,ll b)
{
	int res=1;
	while(b)
	{
		if(b&1)res=res*a%mod;
		b>>=1;
		a=a*a%mod;
	}
	return res;
}
void init()
{
    f[0]=1;
    invf[0]=ksm(f[0],mod-2);
    for(int i=1;i<N;i++)
    {
        f[i]=f[i-1]*i%mod;
        invf[i]=ksm(f[i],mod-2);
    }
}
int C(int a,int b)
{
	if(a<b)return 0;
	return f[a]*invf[a-b]%mod*invf[b]%mod;
}

int main()
{
	init();
	ll n=read();ll ans=0;
	if(n&1){printf("0\n");return 0;}
	for(ll i=1;i<=n-1;i++)
		ans=(ans+((i&1)?-1:1)*C(n-2,i-1)*i%mod*(n-i)%mod*ksm(i,max(0ll,i-2))%mod*ksm(n-i,max(0ll,n-i-2))%mod+mod)%mod;
	printf("%lld\n",ans);
	return 0;
}

```


---

## 作者：Purslane (赞：0)

# Solution

思维过程可以简洁一点。

显然，记 $\deg_u$ 表示 $u$ 相邻的 $-1$ 边的个数。有 $2 \mid \sum_{u=1}^n \deg_u$，得出 $2 \mid n$。故 $2 \nmid n$ 时输出 $0$。

当树的形态固定后，把 $1$ 当做根，求出 DFS 的结果。所有叶子节点和其父亲的连边边权必定为 $-1$。剩下的点可以根据他的儿子的情况选择和父亲连边边权是否为 $-1$。

显然，当这个子树大小为奇数的时候，他和父亲连边边权为 $-1$。

计算 $\sum dis(1,n)$ 的时候，考虑枚举每一条边，把 $1$ 和 $n$ 分在两侧。

假设 $1$ 这一边的子树大小为 $x$，另一边为 $n-x$。使用乘法原理：

1. 划分派别，$\dbinom{n-2}{x-1}$；
2. 两边进行“有标号有根树计数（公式为 $n^{n-1}$）”：$x^{x-1}(n-x)^{n-x-1}$；
3. 奇偶性。$(-1)^{x}$。

因此答案就是：

$$
\sum_{x=1}^{n-1} \dbinom{n-2}{x-1}x^{x-1}(n-x)^{n-x-1}(-1)^x
$$

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=5e5+10,MOD=998244353;
int n,frac[MAXN],inv[MAXN],ans;
int qpow(int base,int p) {
	int ans=1;
	while(p) {
		if(p&1) ans=ans*base%MOD;
		base=base*base%MOD,p>>=1;
	}
	return ans;
}
int C(int u,int d) {
	return frac[d]*inv[u]%MOD*inv[d-u]%MOD;	
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	if(n&1) return cout<<0,0;
	frac[0]=1;
	ffor(i,1,n) frac[i]=frac[i-1]*i%MOD;
	inv[n]=qpow(frac[n],MOD-2);
	roff(i,n-1,0) inv[i]=inv[i+1]*(i+1)%MOD;
	ffor(i,1,n-1) {
		ans=(ans+C(i-1,n-2)*qpow(i,i-1)%MOD*qpow(n-i,n-i-1)%MOD*((i&1)?-1:1))%MOD;
	}
	cout<<(ans%MOD+MOD)%MOD;
	return 0;
}
```

---

