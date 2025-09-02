# [ABC141F] Xor Sum 3

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc141/tasks/abc141_f

$ N $ 個の非負整数 $ A_1,\ A_2,\ ...,\ A_N $ があります。

このうち $ 1 $ 個以上 $ N-1 $ 個以下を赤色で、残りを青色で塗り分けることを考えます。

塗り分けの **美しさ** を、「赤く塗った整数の $ \text{XOR} $」と「青く塗った整数の $ \text{XOR} $」の和とします。

塗り分けの美しさの最大値を求めてください。

 $ \text{XOR} $ とは $ n $ 個の非負整数 $ x_1,x_2,\ \ldots,\ x_n $ の $ \text{XOR} $ $ x_1\ \oplus\ x_2\ \oplus\ \ldots\ \oplus\ x_n $ は以下のように定義されます。

- $ x_1\ \oplus\ x_2\ \oplus\ \ldots\ \oplus\ x_n $ を二進表記した際の $ 2^k(k\ \geq\ 0) $ の位の数は $ x_1,x_2,\ \ldots,\ x_n $ のうち、二進表記した際の $ 2^k(k\ \geq\ 0) $ の位の数が $ 1 $ となるものの個数が奇数ならば $ 1 $、そうでなければ $ 0 $ となる。
 
 例えば、$ 3\ \oplus\ 5\ =\ 6 $ となります。

## 说明/提示

### 制約

- 入力はすべて整数
- $ 2\ \leq\ N\ \leq\ 10^5 $
- $ 0\ \leq\ A_i\ <\ 2^{60}\ (1\ \leq\ i\ \leq\ N) $

### Sample Explanation 1

$ (3,\ 6,\ 5) $ をそれぞれ $ (青,\ 赤,\ 青) $ で塗り分けたとき、美しさは $ (6)\ +\ (3\ \oplus\ 5)\ =\ 12 $ になります。 $ 12 $ よりも高い美しさの塗り分けは存在しないので、答えは $ 12 $ です。

### Sample Explanation 3

$ A_i $ や答えは $ 32 $ ビット整数型に収まらないことがあります。

## 样例 #1

### 输入

```
3
3 6 5```

### 输出

```
12```

## 样例 #2

### 输入

```
4
23 36 66 65```

### 输出

```
188```

## 样例 #3

### 输入

```
20
1008288677408720767 539403903321871999 1044301017184589821 215886900497862655 504277496111605629 972104334925272829 792625803473366909 972333547668684797 467386965442856573 755861732751878143 1151846447448561405 467257771752201853 683930041385277311 432010719984459389 319104378117934975 611451291444233983 647509226592964607 251832107792119421 827811265410084479 864032478037725181```

### 输出

```
2012721721873704572```

# 题解

## 作者：Lskkkno1 (赞：7)

- [AT4835 [ABC141F] Xor Sum 3](https://www.luogu.com.cn/problem/AT4835)

### 题目描述：

给定一个长度为 $N$ 的序列  $(N \le 10^5)$。

要你把这个序列划分成两个集合。

最后答案等于第一个集合中所有元素的异或和（$\operatorname{xor}$）加上第二个集合中所有元素的异或和。

最大化答案。

### 正解 

一般看到**位运算**都会要先去把每一位分开考虑。

假如这一位有奇数个 1，那么无论怎么拆分成两个集合这一位始终有 1 的贡献。

所以先把奇数个 1 的贡献给算出来，不加以考虑。

假如这一位有偶数个 1，那么这一位的所有数异或起来结果肯定是 0。

设分成两个集合之后，两个集合不考虑奇数个 1 的位个话，异或和分别为 $x_1$, $x_2$。

就有 $x_1 \operatorname{xor}x_2$ 等于 0，也就是说 $x_1=x_2$。 

那么只要让其中一个数最大，另一个数会等于这个数，答案也就是最大的。

这一步可以用**线性基**做，时间复杂度$O(n\log n)$。

$\color{DeepSkyBlue} Code :$



```cpp
#include <bits/stdc++.h>
#define MAX 100005
#define bit(x) (1ll << x)

using namespace std;

int n;
int cnt[64];
long long a[MAX], ans;

inline long long Rd() {
	long long x = 0; char ch = getchar();
	while(!isdigit(ch)) ch = getchar();
	while(isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
	return x;
}

struct linear_base {
	long long u[60];
	inline void insert(long long val) {
		for(int i = 59; i >= 0; --i) {
			if(val & bit(i)) {
				if(u[i]) val ^= u[i];
				else {
					u[i] = val;
					return;
				}
			}
		}
	}
	inline long long query() {
		long long res = 0;
		for(int i = 59; i >= 0; --i)
			if((res ^ u[i]) > res) res ^= u[i];
		return res;
	}
}lsk;

int main() {
	n = Rd();
	for(int i = 1; i <= n; ++i) {
		a[i] = Rd();
		for(int j = 59; j >= 0; --j)
			if(a[i] & bit(j)) ++cnt[j];
	}
	
	for(int i = 59; i >= 0; --i) {
		if(cnt[i] & 1) {
			ans += bit(i);
			for(int j = 1; j <= n; ++j) {
				if(a[j] & bit(i)) {
					a[j] ^= bit(i);
				}
			}
		}
	}
	for(int i = 1; i <= n; ++i) lsk.insert(a[i]);

	cout << ans + 2ll * lsk.query() << endl;
	return 0;
}

```

---

## 作者：shinkuu (赞：5)

偶然找到的线性基好题。

考虑 $s=\bigoplus x_i$，则此时 $b=s\oplus a$，问题变为 $\max(a+(s\oplus a))$。

然后观察 $s$，有一个很典的想法是，$s$ 为 $0$ 的位上，$a$ 如果是 $0$ 则会产生 $0$ 的贡献，否则产生 $2$，$s$ 为 $1$ 的位则稳定产生 $1$ 的贡献，结合异或本质理解。

所以现在要求 $x_i$ 的一个子集的异或和中 $s$ 所有 $0$ 的位组成的值的 $\max$。这显然是一个线性基，具体实现是将所有 $x$ 按位与一个取反后的 $s$，再插入线性基。

code：

```cpp
int n,m;ll c[N];
struct XXJ{
	ll a[63];
	il void insert(ll x){
		drep(i,59,0){
			if(!(x>>i&1ll))continue;
			if(a[i])x^=a[i];
			else{a[i]=x;return;}
		}
	}
	il ll query(ll x){
		drep(i,59,0)if((x^a[i])>x)x=x^a[i];
		return x;
	}
}T;
void Yorushika(){
	scanf("%d",&n);
	ll sum=0;
	rep(i,1,n)scanf("%lld",&c[i]),sum^=c[i];
	rep(i,1,n)T.insert(c[i]&(~sum));
	printf("%lld\n",2*T.query(sum)-sum);
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

## 作者：Leasier (赞：5)

本题解将介绍两种做法。

1. 模拟退火

前置芝士：[模拟退火](https://oi-wiki.org/misc/simulated-annealing/)、[线性基](https://oi-wiki.org/math/basis/)

看到求极值的题没有思路，考虑模拟退火。

考虑设定一个初始状态，不难想到将子集最大异或和设为初始状态，每次尝试更新最优解的过程就直接随机一个 $[1, n]$ 的整数 $pos$，并尝试将当前异或和异或 $a_{pos}$。

由于直接模拟退火过不去第三个样例，我们直接小数据爆搜即可。

但~~很可恶的是~~我们伟大的 AT 卡了模拟退火，模拟退火会 WA on #24 和 #25。

代码看看就好。

代码：
```cpp
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef long long ll;

const int N = 1e5 + 7, M = 59;
const double eps = 1e-9;
bool flag = false;
ll a[N], b[M + 7];

inline void insert(ll x){
	for (int i = M; i >= 0; i--){
		if (x >> i & 1){
			if (b[i] == 0){
				b[i] = x;
				return;
			}
			x ^= b[i];
		}
	}
	flag = true;
}

inline ll max(ll a, ll b){
	return a > b ? a : b;
}

ll dfs(int cur, int n, ll x, ll y){
	if (cur > n) return x + y;
	int cur_i = cur + 1;
	return max(dfs(cur_i, n, x, y ^ a[cur]), dfs(cur_i, n, x ^ a[cur], y));
}

inline ll get_max(){
	ll ans = 0;
	for (int i = M; i >= 0; i--){
		ans = max(ans, ans ^ b[i]);
	}
	return ans;
}

inline int rand32(){
#if RAND_MAX == 0x7fff
	return rand() * rand();
#else
	return rand();
#endif
}

inline ll sa(int n, ll val, ll sum){
	ll ans = (val != sum || flag) ? val + (sum ^ val) : 0;
	double temp = 1e9;
	while (fabs(temp) > eps){
		int pos = rand32() % n + 1;
		ll t = val ^ a[pos], cur_ans = t + (sum ^ t);
		if (ans < cur_ans){
			if (val != sum || flag) ans = cur_ans;
			val = t;
		} else if (exp(-(ans - cur_ans) / temp) > 1.0 * rand() / RAND_MAX){
			val = t;
		}
		temp *= 0.98;
	}
	return ans;
}

int main(){
	int n;
	ll sum = 0;
	scanf("%d", &n);
	srand(time(NULL));
	for (int i = 1; i <= n; i++){
		scanf("%lld", &a[i]);
		sum ^= a[i];
		insert(a[i]);
	}
	if (n <= 20){
		printf("%lld", dfs(1, n, 0, 0));
	} else {
		printf("%lld", sa(n, get_max(), sum));
	}
	return 0;
}
```
2. 线性基

前置芝士：[线性基](https://oi-wiki.org/math/basis/)

考虑全局异或和中的一位 $S_i$。

- $S_i = 1$

显然构成答案的两个异或和的第 $i$ 位一定为 $0$ 和 $1$，于是直接将答案加上 $2^i$ 即可。

- $S_i = 0$

显然构成答案的两个异或和的第 $i$ 位一定为全 $0$ 或全 $1$。

于是去除 $S_i = 1$ 的位的影响后跑子集最大异或和，答案为 $S_i = 1$ 的答案加上 $2 \times$ 子集最大异或和。

代码：
```cpp
#include <stdio.h>
#include <math.h>

typedef long long ll;

const int N = 1e5 + 7, M = 59;
ll a[N], b[M + 7];

inline void insert(ll x){
	for (int i = M; i >= 0; i--){
		if (x >> i & 1){
			if (b[i] == 0){
				b[i] = x;
				return;
			}
			x ^= b[i];
		}
	}
}

inline ll max(ll a, ll b){
	return a > b ? a : b;
}

inline ll get_max(){
	ll ans = 0;
	for (int i = M; i >= 0; i--){
		ans = max(ans, ans ^ b[i]);
	}
	return ans;
}

int main(){
	int n;
	ll sum = 0, ans = 0;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++){
		scanf("%lld", &a[i]);
		sum ^= a[i];
	}
	for (int i = 0; i <= M; i++){
		if (sum >> i & 1){
			ll cur = 1ll << i;
			ans += cur;
			for (int j = 1; j <= n; j++){
				if (a[j] >> i & 1) a[j] ^= cur;
			}
		}
	}
	for (int i = 1; i <= n; i++){
		insert(a[i]);
	}
	printf("%lld", ans + get_max() * 2);
	return 0;
}
```

---

## 作者：541forever (赞：3)

**题意**

给出 $n$ 个数，你需要将其划分为两个集合，使得两个集合的异或和之和最大。

**Solution**

看上去是一道经典题？考虑在二进制下自高向低逐位计算，该位为 $1$ 的出现次数为奇数是可以发现无论如何划分总有一组算到会算到这一位的贡献，那么我们只需考虑出现次数数为偶数的位。考虑将所有数的个数为奇数的位置 $1$ 置为 $0$（因为这些位的贡献已经算过了），那么现在对于每一位而言，它们 $1$ 的出现次数皆为偶数。那么我们不难发现，无论如何划分这两组，他们的异或和都一定相等，因此直接用线性基选出最大的一组的异或和即可。

代码也十分的精简。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=100000;
int n,cnt[62];
long long ans,val[62],a[MAXN+2]; 
void insert(long long x){
	for(int i=60;i>=0;--i){
		if((x>>i)&1){
			if(val[i]){
				x^=val[i]; 
			}else{
				val[i]=x;
				break;
			}
		}
	}
}
long long query(){
	long long ans=0;
	for(int i=60;i>=0;--i){
		ans=max(ans,ans^val[i]);
	}
	return ans;
}//线性基 
signed main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%lld",&a[i]);
		for(int j=0;j<60;++j){
			if((a[i]>>j)&1){
				++cnt[j];//统计出现次数 
			}
		}
	}
	for(int i=0;i<60;++i){
		if(cnt[i]&1){
			ans+=(1ll<<i);
			for(int j=1;j<=n;++j){
				if(a[j]&(1ll<<i)){
					a[j]^=(1ll<<i);//若出现次数为偶数，删去该位的 1 
				}
			}
		}
	}
	for(int i=1;i<=n;++i){
		insert(a[i]);
	}
	ans+=query()<<1ll;
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：robinyqc (赞：2)

### 题意简述

给定 $n$ 个数 $A = \{a_i\}$。将 $A$ 任意划分成两个非空集合 $U, V$，设 $b$ 为 $U$ 的按位异或和，$r$ 为 $V$ 的按位异或和。输出 $b + r$ 的最大值。$n\leq 10^5, 0\leq a_i< 2^{60}$。

### 解题思路

有一个比较明显的观察：$b \oplus r$ 是全局异或和，是个定值。不妨设这个值为 $x$。设 $v_i$ 表示二进制下 $v$ 从低到高第 $i$ 位。

若 $x_i = 1$，可以发现，无论怎么划分集合，$b_i$ 和 $r_i$ 中有且仅有一个为 $1$。所以，这一位对答案的贡献是个定值：$2^i$。

现在我们**只考虑 $x_i = 0$ 的位**，有 $b_i = r_i$。因此只看这些位的话，$b = r$。最大化 $b + r$，就是最大化 $b$。我们相当于要最大化一个子集的异或和。这个用线性基容易解决。

一个减少细节的结论是，因为 $a\oplus b \leq a + b$，所以 $a_1\oplus a_2\oplus a_3\dots\leq a_1 + a_2\oplus a_3\oplus\dots$。因此若 $U = A$，并不会影响答案。

### 代码实现

```rust
use proconio::input;

struct HamelBasis
{
    basis: [i64; 60]
}

impl HamelBasis
{

    pub fn insert(self: &mut Self, x: i64) 
    {
        let mut x = x;
        for i in (0..60).rev() {
            if ((x >> i) & 1) == 1 {
                if self.basis[i] == 0 {
                    self.basis[i] = x;
                    break;
                }
                else {
                    x ^= self.basis[i];
                }
            }
        }
    }

    pub fn max(self: &Self) -> i64
    {
        let mut res = 0i64;
        for i in (0..60).rev() {
            if ((res >> i) & 1) == 0 && self.basis[i] != 0 {
                res ^= self.basis[i];
            }
        }
        res
    }
}

fn main()
{
    input! {
        n: usize,
        mut a: [i64; n]
    }
    let mut xor_sum = 0i64;
    for i in 0..n {
        xor_sum ^= a[i];
    }
    let mut ans = 0i64;
    for i in 0..60 {
        if ((xor_sum >> i) & 1) == 1 {
            ans += 1i64 << i;
            let x = 1i64 << i;
            for v in &mut a {
                if ((*v >> i) & 1) == 1 {
                    *v ^= x;
                }
            }
        }
    }
    let mut hb = HamelBasis { basis: [0; 60] };
    for i in a {
        hb.insert(i);
    }
    println!("{}", hb.max()* 2 + ans);
}
```

---

## 作者：Shiota_Nagisa (赞：0)

[原题传送门](https://atcoder.jp/contests/abc141/tasks/abc141_f)

对于位运算题目，考虑按位处理。我们发现，对于二进制第 $i$ 位，如果数组中在第 $i$ 位二进制值为 $1$ ，则答案中第 $i$ 位值必为一，否则为 $0$ 或 $2$。

对于后面一种情况，我们运用线性基进行求解。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e5+10,M=61;//M要开到60 
int n,a[N],b[70],sum,ans;
bool used[70];
void ins(int x){//线性基板子 
	for(int i=M;i>=0;i--){
		if((x&(1ll<<i))==0) continue;//在这里一定要写1ll 
		if(!b[i]){
			b[i]=x;
			return ;
		}
		else x^=b[i];
	}
}
int qmax(){
	int cnt=0;
	for(int i=M;i>=0;i--){
		if((cnt^b[i])>cnt) cnt=cnt^b[i];
	}
	return cnt;
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		sum^=a[i];
	}
	for(int i=0;i<=M;i++){
		if((1ll<<i)&sum){
			ans+=(1ll<<i);
			for(int j=1;j<=n;j++){
				if(a[j]&(1ll<<i)){//我们不处理答案中有的位数 
					a[j]-=(1ll<<i);
				}
			}
		}
	}
	for(int i=1;i<=n;i++) ins(a[i]);
	cout<<ans+2*qmax(); 
}
```

---

## 作者：Chenyichen0420 (赞：0)

## 思路分析

首先，遇到这种二进制相关的题，我们就要考虑从二进制位的角度按位分析。

先看一下每一位为一的数的个数。最简单的情况就是奇数个。因为无论你怎么分，总是有一边有，有一边没有，可以提前统计了，然后消除掉这些位。

偶数个的最难搞：你不一定能够保证左右都可以分到一，有的位甚至是因为没有数才是偶数个！

这有点难搞，但是实际上我们可以发现一个性质：当一边最优的时候另一边一定也最优。为什么呢？你想想，每一位的个数都是偶数个，所以异或起来的值就是 $0$。然后左右两边都是通过异或得到的，也就是说两边的数异或起来就是 $0$。所以两边相等啊！

好了，现在要做的就是从数组 $a$ 中选出一些数，使得其异或值最大。熟悉吗？线性基板子。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n, v[100005], cnt[60], lib[60], ans;
inline void add(const int& v) {
	for (int i = 0; i < 60; ++i)
		cnt[i]^=((v>>i)&1);
}
inline void ins(int v) {
	for (int i = 59; i >= 0; i--)
		if (v & (1ll << i))
			if (lib[i]) v ^= lib[i];
			else return void(lib[i] = v);
}
inline int que(int v) {
	for (int i = 59; i >= 0; i--)
		if ((v ^ lib[i]) > v) v ^= lib[i];
	return v;
}
signed main() {
	ios::sync_with_stdio(0);
	cin >> n;
	for (int i = 1; i <= n; ++i)
		cin >> v[i], add(v[i]);
	for (int i = 0; i < 60; ++i)
		if (cnt[i]) {
			for (int j = 1; j <= n; ++j)
				if (v[j] & (1ll << i)) v[j] ^= (1ll << i);
			ans |= (1ll << i);
		}
	for (int i = 1; i <= n; ++i) ins(v[i]);
	cout << ans + (que(0) << 1) << endl;
	return 0;
}
```

---

