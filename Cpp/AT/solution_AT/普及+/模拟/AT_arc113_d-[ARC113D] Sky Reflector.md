# [ARC113D] Sky Reflector

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc113/tasks/arc113_d

縦 $ N $ マス横 $ M $ マスのマス目の各マスに $ 1 $ 以上 $ K $ 以下の整数をひとつずつ書き込み、列 $ A,B $ を以下のように定義します。

- $ i=1,\dots,\ N $ に対し、$ A_i $ は $ i $ 行目のマスに書かれた整数の最小値
- $ j=1,\dots,\ M $ に対し、$ B_j $ は $ j $ 列目のマスに書かれた整数の最大値

$ N,M,K $ が与えられるので、列対 $ (A,B) $ としてありうる相異なるものの個数を $ 998244353 $ で割った余りを求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N,M,K\ \leq\ 2\times\ 10^5 $
- 入力はすべて整数である

### Sample Explanation 1

$ (A_1,A_2,B_1,B_2) $ としてありうるものは、$ (1,1,1,1),(1,1,1,2),(1,1,2,1),(1,1,2,2),(1,2,2,2),(2,1,2,2),(2,2,2,2) $ の $ 7 $ 通りです。

## 样例 #1

### 输入

```
2 2 2```

### 输出

```
7```

## 样例 #2

### 输入

```
1 1 100```

### 输出

```
100```

## 样例 #3

### 输入

```
31415 92653 58979```

### 输出

```
469486242```

# 题解

## 作者：__log__ (赞：4)

模拟赛出了超级无敌加强版，数组开太大爆炸了，100 分全没了。

## 正文

1. $n=1,m=1$：$ans = k$；
2. $n=1,m\ge2$：$ans= k^m$；
3. $n\ge2,m=1$：$ans=k^n$；

以上三点特判即可。

4. $n,m \ge 2$：

假定我们已经知道 $A$ 序列，那 $B$ 序列有什么要求才能合法呢？

在 WC 里的灵光一闪告诉我们，只需满足：

$$\forall i\in [1,n], j \in [1,m],B_j \ge A_i$$

即可。

必要性证明：

> 假设 $\exist i\in [1,n], j \in [1,m],B_j < A_i$，
>
>那第 $j$ 列的所有数都会小于这个 $A_i$，所以 $G_{i,j} < A_i$，与 $A_i = \min _ {j=1} ^ {M} G_{i,j}$ 矛盾。

充分性证明：

> 考虑直接构造一个符合 $A$ 与 $B$ 两序列的矩阵。
>
> ![](https://cdn.luogu.com.cn/upload/image_hosting/qddpo1y0.png)
>
> 容易证明，这种构造可以满足 $n,m\ge 2$ 的情形。

所以答案可以这么计算：

枚举 $A$ 序列的最大值 $p$，并计算 $A$ 序列最大值为 $p$ 时 $A$ 序列的方案数，乘上 $(k-p+1)^M$（这个数是此时 $B$ 序列的方案数），最后把这些数加起来。

表达式为：

$$ans = \sum _ {p=1} ^ {k}[p ^ N - (p - 1) ^ N](k - p + 1) ^ M$$

可以直接快速幂计算，时间复杂度 $O(k\log n)$。

但是作为一道 pion 模拟赛的 T1，怎么能这么轻松的放你过去，于是该死的出题人把 $k$ 调到了 $k \le 3 \times 10^7$。

## 不是正文的正文

注意到上式中要求的东西是 $a^N$ 和 $a^M$，并且不能暴力求解。

又注意到 $f(x)=x^n$ 是一个**完全积性函数**，众所周知**积性函数**均可以用**线性筛**求解，于是我们可以用求欧拉函数 $\varphi$ 的代码如法炮制。时间复杂度 $O(\frac{k\log n}{\ln k})$。

## Code

tips：以后 $7$ 次方数量级数组切忌开 `long long`。

$a_i$ 表示 $i^n$ 的值，$b_i$ 表示 $i^m$ 的值。

```cpp
// I love Furina forever.
# include <bits/stdc++.h>
# define maxn 30000001
# define mod 998244353
// # define int long long
# define ll long long
# define rep(i, j, k) for(int i = j; i <= k; ++i)
# define per(i, j, k) for(int i = j; i >= k; --i)
using namespace std;

ll n, m, k, ans, cnt;
int a[maxn], b[maxn];
int pri[maxn], tot;
bool vis[maxn];

inline int qp(ll a, int b) {ll mul = 1; while(b) mul = mul * (b & 1 ? a : 1) % mod, a = a * a % mod, b >>= 1; return mul;}

void init(int p, int q) {
    a[1] = 1; b[1] = 1;
    for(ll i = 2; i <= k; ++i) {
        if(!vis[i]) a[i] = qp(i, p), b[i] = qp(i, q), pri[++tot] = i;
        for(int j = 1; j <= tot && 1ll * i * pri[j] <= k; ++j) {
            a[i * pri[j]] = 1ll * a[i] * a[pri[j]] % mod;
            b[i * pri[j]] = 1ll * b[i] * b[pri[j]] % mod;
            vis[i * pri[j]] = 1;
            if(i % pri[j] == 0) break;
        }
    }
}

signed main() {
    freopen("matrix.in", "r", stdin);
    freopen("matrix.out", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> m >> k;
    if(n > m) swap(n, m);
    if(n == 1 && m == 1) {cout << k << '\n'; return 0;}
    init(n, m);
    if(n == 1 && m != 1) {
        rep(i, 1, k) {
            ll t1 = (0ll + a[i] - a[i - 1] + mod) % mod, t2 = (0ll + b[k - i + 1] - b[k - i] + mod) % mod;
            ans = (ans + 1ll * t1 * t2 % mod) % mod;
        }
        cout << ans << '\n';
        return 0;
    }
    rep(i, 1, k) {
        ll t1 = (0ll + a[i] - a[i - 1] + mod) % mod, t2 = b[k - i + 1];
        ans = (ans + 1ll * t1 * t2 % mod) % mod;
    }
    cout << ans << '\n';
    return 0;
}
```

## 正文之后的正文

1. [misaka_sama](https://www.luogu.com.cn/user/876598) 先生证明了 $n,m$ 交换之后答案不变。
2. 乱开数组的下场：

![](https://cdn.luogu.com.cn/upload/image_hosting/q4s0dvph.png)

---

## 作者：max666dong123 (赞：1)

## 题意

$A_i$ 表示第 $i$ 行的最小值。

$B_j$ 表示第 $j$ 列的最大值。

现在有一个 $N$ 行 $M$ 列的方格 $G$，$G$ 中的数在 $1$ 到 $k$ 中的数。

现在求 $(A,B)$ 的可能数量对 $998244353$ 取模。

## 解法

根据题意，可以很容易得知 $A_i \le G_{i,j} \le B_j$。

然后需要证明 $\max \{ A_i \} \le \min \{B_j \}$。

用反证法，假设结论不成立。

那么 $\max \{ A_i \} \ge \min \{B_j \}$。

可是根据 $A_i \le G_{i,j} \le B_j$ 可以推出 $A_i \le B_j$。

所以发现结论是对的。

然后开始枚举 $A_i$ 最大值的可能情况，设最大值为 $t$。

先计算 $A_i$ 的所有情况。

用总数-不可能情况。

$A_i$ 一共有 $i^t$ 种。

不可能情况是 $(i-1)^t$ 种，也就是没有选$i$的情况，

再讨论 $B_i$ ，

由于 $B_i$ 一定比 $A_i$ 大或相等，所以 $B_i$ 在 $i \sim k$ 之间，一共 $(k-i+1)$ 种。

最后步步相乘，求出最大值为 $t$ 的情况数。

答案就是所有最大值相加。

## AC代码

模拟上面的就行了。
```cpp
    #include<bits/stdc++.h>
    #define int long long
    using namespace std;
    const long long MOD=998244353;
    int f(int a,int b){//快速幂 
    	if(a==0)return 0;
    	if(b==0)return 1;
    	int ans=f(a,b/2);
    	ans=ans*ans%MOD;
    	if(b&1)ans=ans*a%MOD;
    	return ans;
    }
    signed main(){
    	int n,m,k;
    	cin>>n>>m>>k;
    	if(n==1||m==1){//特判 
    		int ans=f(k,n+m-1);//n,m中必定有一个1 
    		cout<<ans<<endl;
    		return 0;
    	}
    	int ans=0;
    	for(int i=1;i<=k;i++){
    		ans=(ans+((f(i,n)-f(i-1,n)%MOD)*(f(k-i+1,m%MOD)))%MOD+MOD)%MOD;//+MOD防止负号 
    	}
    	cout<<ans<<endl;
    	return 0;
    }
 ```
 ## 其他
 [参考资料](https://blog.csdn.net/tanjunming2020/article/details/128137151)

---

## 作者：StarRoam (赞：0)

观察本题，我们容易想到一个性质：

$$
\max_{i=1}^n a_i \le \min_{i=1}^m b_i
$$

证明也非常简单，我们只要想一下二者的定义：

- $a_i$：第 $i$ 行的最小值。
- $b_i$：第 $j$ 列的最大值。

假设存在一个 $b_i$ 小于 $a_i$，则 $b_i$  所在列上对应的数一定也小于 $a_i$，这与定义 $a_i$ 为第 $i$ 行的最小值矛盾，顾性质成立。

当次性质满足时，我们易发现不管如何填 $A$ 与 $B$，矩阵都合法。



```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int MOD=998244353;
int n,m,k;
ll qpow(ll x,int y){
	ll ct=1;
	while(y>0){
		if((y&1)) ct=ct*x%MOD;
		x=x*x%MOD,y=y>>1;
	}
	return ct;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
    cin>>n>>m>>k;
    if(n==1){
    	cout<<qpow(k,m)<<"\n";
    	return 0;
	}
	if(m==1){
		cout<<qpow(k,n)<<"\n";
		return 0;
	}
	ll ans=0;
	for(int i=1;i<=k;i++)
	{
		ll ct=(qpow(i,n)-qpow(i-1,n)+MOD)*qpow(k-i+1,m)%MOD;
		ans=(ans+ct)%MOD;
	}
	cout<<ans;
	return 0;
}
/*
 
*/
```

---

## 作者：Claire0918 (赞：0)

$n = 1$ 时显然答案是 $k^m$，$m = 1$ 时显然答案是 $k^n$。我们仅考虑 $n \geq 2, m \geq 2$ 的情况。

我们有定理：$\{A_i\}$ 和 $\{B_j\}$ 合法的充分必要条件是 $\max \{A_i\} \leq \min \{B_j\}$。

充分性是显然的，在两条对角线上分别放置 $\{A_i\}$ 和 $\{B_j\}$ 即可。考虑必要性。假设 $\max \{A_i\} > \min \{B_j\}$，也就是存在 $G_{i, j} > \min \{B_j\}$，那么 $B_j$ 就应该更新为比当前 $B_j$ 更大的 $G_{i, j}$，所以假设不成立，必要性得证。

考虑枚举 $t = \max\{A_i\}$，$\{A_i\}$ 的条件是 $\{A_i\} \in [1, t]^n \setminus [1, t)^n$，方案数是 $t^n - (t - 1)^n$。$\{B_i\}$ 的条件是 $\{B_i\} \in [t, k]$，方案数是 $(k - t + 1)^m$。综上，答案为
$$
\sum_{t = 1}^{k} (t^n - (t - 1)^n) \times (k - t + 1)^m
$$
直接计算可以做到 $\mathcal{O}(k\log n)$，可以通过本题。

事实上，还存在 $n, m \leq 10^9, k \leq 3 \times 10^7$ 的强化版，此时原复杂度无法直接通过。注意到幂函数是完全积性函数，可以使用线性筛筛出 $f(x) = x^n$ 和 $g(x) = x^m$。只有在 $x$ 是质数时才需要直接 $\mathcal{O}(\log n)$ 计算 $f(x)$ 和 $g(x)$，其他情况直接将已得到的两个答案相乘即可。时间复杂度 $\mathcal{O}(k + \pi(k)\log n)$，$\pi(k)$ 只有 $10^6$ 级别，可以轻松通过。

Code：
```cpp
#include<bits/stdc++.h>
#define mem(a, v) memset(a, v, sizeof(a))

using namespace std;

const int maxk = 3e7 + 10, mod = 998244353;

int n, m, k, tot = 0, res = 0;
int prm[maxk], pown[maxk], powm[maxk];
bitset<maxk> npr;

template<typename Tp_x, typename Tp_y>
inline int mod_add(Tp_x x, Tp_y y){
    return x += y, x >= mod ? x -= mod : x;
}

inline long long ksm(long long a, long long b){
    long long res = 1;
    while (b){
        if (b & 1){
            res = res * a % mod;
        }
        a = a * a % mod, b >>= 1;
    }
    return res;
}

int main(){
    scanf("%d %d %d", &n, &m, &k);
    if (n == 1){
        printf("%lld", ksm(k, m));
    }else if (m == 1){
        printf("%lld", ksm(k, n));
    }else{
        pown[1] = powm[1] = 1;
        for (int i = 2; i <= k; i++){
            if (!npr.test(i)){
                prm[++tot] = i, pown[i] = ksm(i, n), powm[i] = ksm(i, m);
            }
            for (int j = 1; j <= tot && i * prm[j] <= k; j++){
                const int x = i * prm[j];
                npr.set(x), pown[x] = (long long)pown[i] * pown[prm[j]] % mod, powm[x] = (long long)powm[i] * powm[prm[j]] % mod;
                if (!(i % prm[j])){
                    break;
                }
            }
        }
        for (int i = 1; i <= k; i++){
            res = mod_add(res, (long long)mod_add(pown[i], mod - pown[i - 1]) * powm[k - i + 1] % mod);
        }
        printf("%d", res);
    }

return 0;
}
```

---

## 作者：AzusidNya (赞：0)

## [ARC113D] Sky Reflector

### Description

在一个 $ N $ 行 $ M $ 列的方格 $ G $ 中，每一个方格中可以放置 $ 1 \sim K $ 中的任何一个数。

我们定义序列 $ A,B $ 定义如下：

$$ A_i=\min_{j=1}^M G_{i,j} $$

$$ B_j=\max_{i=1}^N G_{i,j} $$

现在给定 $ N,M,K $。问共有多少种不同的序列对 $ (A,B) $，答案对 $ 998244353 $ 取模。



### Solution

先考虑 $n = 1$ 或 $m = 1$ 的情况。此时 $G$ 矩阵只有 $1$ 行或 $1$ 列，所以 $G$ 的每个元素与 $A$ 或 $B$ 的每个元素一一对应，而当 $A$ 或 $B$ 确定后，另一者就确定了。故此时答案为 $k^n$ 或 $k^m$。

接下来考虑 $n \ge 2, m \ge 2$ 的情况。

观察样例解释可以猜想一个结论：

$$\max_{i=1}^{N}\left\{A_i\right\} \le \min_{i=1}^{M}\left\{B_i\right\}$$

证明很简单。考虑反证法。假设 $A_x=\max_{i=1}^{N}\left\{A_i\right\}, B_y = \min_{i=1}^{M}\left\{B_i\right\}$，但是有 $A_x \le G_{x, y} \le B_y$，与假设矛盾。故原命题成立。

现在假设已经确定了序列对 $(A, B)$ 并且满足 $\max_{i=1}^{N}\left\{A_i\right\} \le \min_{i=1}^{M}\left\{B_i\right\}$ ，尝试构造出矩阵 $G$ 匹配这一序列对 $(A, B)$。

当 $n = m = 2$ 时，可以这么构造：

$$\begin{bmatrix}A_1  & B_2\\B_1  & A_2\end{bmatrix}$$

假设 $n = i$ 时能够构造矩阵，考虑构造 $n = i + 1$，也就是 $A$ 序列增加了一个数。那么我们在矩阵增加一行，然后将 $A_{i + 1}$ 随便放一个位置即可，因为有 $\max_{i=1}^{N}\left\{A_i\right\} \le \min_{i=1}^{M}\left\{B_i\right\}$ ，所以不会与 $B$ 数列产生冲突，故构造是合法的。构造 $m = i + 1$ 同理。

因此当 $n \ge 2, m \ge 2$ 时，统计能构造出矩阵的数列对 $(A,B)$ 的数量可以转化为统计满足上述条件的数列对 $(A, B)$ 的数量。

枚举  $\max_{i=1}^{N}\left\{A_i\right\}$，设当前枚举的这一值为 $x$。

满足 $\max_{i=1}^{N}\left\{A_i\right\} \le x$ 的数列的数量为 $x^n$，那么满足 $\max_{i=1}^{N}\left\{A_i\right\} = x$ 的数列的数量即为 $x^n - (x - 1)^{n}$。

而 $B$ 数列只需要满足 $\min_{i=1}^{M}\left\{B_i\right\} \ge x$。易知方案数为 $(k - x + 1) ^ m$。

故答案为：

$$\sum_{x=1}^k \left[x^n - (x - 1)^{n}\right]\left[(k - x + 1) ^ m\right]$$ 



## Code

```cpp
// LUOGU_RID: 134801642
#include<iostream>
#include<fstream>
#include<algorithm>
#define int long long
using namespace std;
namespace solve1{
	int n, m, k;
	const int modd = 998244353;
	int ksm(int u, int v){
		int ret = 1;
		while(v){
			if(v & 1) ret = ret * u % modd;
			u = u * u % modd, v >>= 1;
		}
		return ret;
	}
	int main(){
		cin >> n >> m >> k;
		if(n == 1 && m == 1){
			cout << k;
			return 0;
		}
		if(n == 1){
			cout << ksm(k, m);
			return 0;
		}
		if(m == 1){
			cout << ksm(k, n);
			return 0;
		}
		int ans = 0;
		int lst = 0;
		for(int i = 1; i <= k; i ++){
			int x = ksm(i, n);
			int y = (x - lst) % modd;
			if(y < 0) y += modd; 
			(ans += y * ksm(k - i + 1, m) % modd) %= modd;
			lst = x;
		}
		cout << ans;
		return 0;
	}
}
signed main(){
	int T = 1;
	while(T --)
		solve1::main();
	return 0;
}
```



------

Fun fact：这个人打 abc 前开了 arc113，然后打完 abc 的前三题后不小心开到了这题，切了之后发现开错题了掉大分。

---

## 作者：Liyunze123 (赞：0)

先猜结论。

观察样例 $1$ 解释，我们发现 $b_j \ge a_i$。又因为 $(1,2,1,2)$ 不合法，猜测 $b_j \ge \max(a_i)$。

设 $f_{i,j}$ 是某种合法方案中 $i$ 行 $j$ 列填的数。

下面来证明这个结论。设 $\max(a_i)$ 是在第 $j$ 列处取到最小值，显然有 $b_j \ge f_{i,j}$，而 $f_{i,j} = a_i$，这种情况得证。对于 $k \neq j$，有 $f_{i,k} \ge f_{i,j}$，而 $b_k \ge f_{i,k}$，所以 $b_k \ge f_{i,j}=a_i$。得证。

那这道题的解法很显然了。枚举 $a$ 的最大值 $p$，$b$ 的合法方案数为 $(k-p+1)^m$。此时 $a$ 的方案数为 $p^n-(p-1)^n$。

上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;
int n,m,k,ans;
int qmi(int i,int j){
	if(!j)return 1;
	int d=qmi(i,j/2);
	return 1ll*d*d%mod*((j%2)?i:1)%mod;
}
int main(){
	scanf("%d%d%d",&n,&m,&k);
	if(n==1&&m==1)printf("%d",k);
	else if(n==1&&m>1)printf("%d",qmi(k,m));
	else if(n>1&&m==1)printf("%d",qmi(k,n));
	else{
		for(int w=1;w<=k;w++)ans=(ans+1ll*(qmi(w,n)-qmi(w-1,n)+mod)%mod*qmi(k-w+1,m))%mod;
		printf("%d",ans);
	}
	return 0;
} 
```
注意特判。

---

