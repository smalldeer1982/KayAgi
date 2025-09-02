# [GXPC-S 2025] 异或之力 / xor

## 题目背景

题目来源：2025 年广西中小学生程序设计挑战赛复赛（进阶组[试题](https://mp.weixin.qq.com/s?__biz=MzI3NDM3MzcwNQ==&mid=2247490166&idx=5&sn=e7ba7e3bc8126027b9abd662518c208b&chksm=ea9c06dd4d18206ed9d88124cc78b947298df2555889e98620204c2ea1471f58c135c00f99fb&mpshare=1&scene=23&srcid=0724dNJdhMxpUHag1dqkhiqL&sharer_shareinfo=7e47197d6e5c044ae705613db988029c&sharer_shareinfo_first=7e47197d6e5c044ae705613db988029c#rd)）。


## 题目描述



传说中，只有能够将力量完美分解的勇者，才能获得王国中最强大的能量 —— 异或之力。

对于每一个 01 字符串都含有一定异或之力。假设某个 01 字符串所代表的十进制数为 $C$，当 $C \le 1$ 时异或之力为 $0$；当 $C > 1$ 时，将 $C$ 分解成任意两个正整数 $A$ 和 $B$ （$A > 0$，$B > 0$，$A + B = C$），得到 $A$ 异或 $B$ 的最大值为 $P$，异或最小值为 $Q$，异或之力即为 $P$ 和 $Q$ 的差值。

作为王国的继承者，你被赋予了一个正整数 $n$。你的任务是寻找所有长度为 $n$ 的 01 字符串（注意：字符串可含前导零，即 $(0011)_2$ 是合法的，与 $(11)_2$ 相同都代表着数字 3）中，最大异或之力是多少。这个数可能很大，请输出其对 $10^9 + 7$ 取模之后的结果。

异或运算（$\oplus$）：对于两个二进制数的每一位，如果相同则为 $0$，不同则为 $1$。例如，$6\oplus 3=(110)_2\oplus (011)_2=(101)_2=5$，$9\oplus 3=(1001)_2\oplus (0011)_2=(1010)_2=10$。


## 说明/提示

#### 样例解释

长度为 3 的 01 字符有 111、110、101、100、011、010、001、000。  
对于 $(110)_2$ 也就是 6 来说，当分解成 4 和 2 时取得异或最大值 6，当分解成 3 和 3 时取得最小异或值 0。没有其他情况使得最大与最小异或值差大于 6，故答案为 6。

#### 数据范围


- 对于 $20\%$ 的数据，$2 \le n < 10$；  
- 对于 $40\%$ 的数据，$2 \le n < 64$；  
- 对于 $60\%$ 的数据，$2 \le n \le 10^6$；  
- 对于 $100\%$ 的数据，$2 \le n \le 10^9$。



## 样例 #1

### 输入

```
3```

### 输出

```
6```

# 题解

## 作者：XiaoHongChong (赞：4)

本题的第一篇题解！  
设长度为 $n$ 的 01 字符串中，最大的是 $S$。即 $S = 2^n - 1$。  
我们先拿 $S$ 进行分解。  
最大值：由于异或就是不进位的加法，所以可以有 $a, b$ 使得 $a + b = n$ 且 $a \oplus b = n$，所以最大值为 $S$。  
最小值：如果$a \oplus b = 0$，那么一定满足 $a = b$。$S$ 是奇数，没有办法平均分，所以最小值至少为 $1$。  
如果拿 $S$ 分解，异或之力**最大**为 $S - 1$。  

再拿 $S - 1$ 进行分解。  
最大值：和 $S$ 的最大值同理，为 $S - 1$。
最小值：由于有 $2 \times a = S - 1$ 的整数解，所以最小值为 $0$。
如果拿 $S - 1$ 分解，异或之力为 $S - 1$。  

剩下的数就不用看了，因为它们的最大值不会超过 $S - 1$。
所以答案为 $2^n - 2$。注意特判 $n = 2$ 的情况，这时答案为 $0$。

---

## 作者：zyr2011 (赞：3)

### 题目解法
首先，我们先了解异或的一个性质，那就是 $a \oplus a = 0$，由此我们可以得出**偶数**被分解后的异或最小值 $Q$ **一定**是 $0$，因为我们可以将这个数**平分**后互相异或，根据前面的性质，异或的结果一定是 $0$。  
接下来找最优解，对于**形如 $2 ^ k - 1$ 的奇数**，容易发现其异或最小值 $Q = 2 ^k -2$，其异或最大值 $P = 2 ^ k - 1$，异或之力只有 $1$，显然**不是最优解**。而**形如 $2 ^ k - 2$ 的数**，前面已经证明其异或最小值 $Q = 0$，而通过 $2 ^ k - 4 \oplus 2 = 2 ^ k - 2$ 可以得出异或最大值 $P = 2 ^ k - 2$，可以发现这**是最优解**。**所以 $2 ^ n - 2$ 就是答案**，直接用**快速幂**把这个数给求出就可以通过了。注意特判 $n = 2$ 的情况。
### 满分代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
inline int kp(int a,int b){
	int ans=1;
	while(b){
		if(b&1){
			ans=ans*a%mod;
		}
		a=a*a%mod;b>>=1;
	}
	return ans;
}//快速幂模版 
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int n;cin>>n;
	if(n==2){
		cout<<0<<endl;return 0;
	}//特判n=2的情况 
	cout<<(kp(2,n)-2%mod+mod)%mod;
	return 0;
}
```

---

## 作者：Lyw_and_Segment_Tree (赞：2)

直觉告诉我们可以从 $111... = 2 ^ n - 1$ 这个可能的串出发，根据异或的性质，我们应当让 $A$ 与 $B$ 的二进制位中 $1$ 与 $0$ 的配对最大化。

不妨设 $k = 2 ^ n - 1$。考虑让 $A = k - 1, B = 1$，可以把这个分解刻画到二进制位上面，容易发现当 $A \not= 1$ 时，$A$ 的最后一位一定是 $0$，而 $B$ 最后一位是 $1$，并且仅有这一位为 $1$，此时 $A \oplus B = k$，这必然是 $A \oplus B$ 可能的最大值，因为异或这个运算没有进位的可能，所以必然有 $A \oplus B \le k$。

继续考虑 $A \oplus B$，设 $A + B = x$，那么 $(A \oplus B)_{\min} = x \bmod 2$，做法是考虑设 $A = \lceil \frac x2 \rceil, B = \lfloor \frac x2 \rfloor$，根据这个构造容易得出上述结论，当 $k = 2 ^ n - 1, A + B = k$ 时，显然因为 $k$ 为奇数，所以其最小值为 $1$。

那么，当 $k = 2 ^ n - 1$ 时，所求答案即为 $2 ^ n - 2$，这显然非常优，但是我们仍然需要证明这个最优性，不妨设 $1 \le k \lt 2 ^ n - 1$，令 $A + B = k$，则 $(A \oplus B)_{\max} = k, (A \oplus B)_{\min} = 0$，不妨先不考虑能否取到，此时的答案为 $k$，因为 $k \lt 2 ^ n - 1$，所以 $k \le 2 ^ n - 2$，并且不一定取得到，这样我们就证明了 $k = 2 ^ n - 1$ 时，所求答案的最优性，所以答案即为 $2 ^ n - 2$。

最后要特别注意 $n = 2$ 的时候，此时最大值的最优取法与最小值的最优取法相同，需要特判掉为 $0$。

求 $2 ^ n - 2$ 直接快速幂就是对的，最终时间复杂度 $O(\log n)$。

code：

```cpp
#include <bits/stdc++.h>
#define ll long long
#define endl "\n"

const ll mod = 1e9 + 7;

using namespace std;

ll qpow(ll a, ll b) {
    ll res = 1;

    while (b) {
        if (b & 1) res = res * a % mod;

        a = a * a % mod, b >>= 1;
    }

    return res % mod;
}

int main() {
    ll n; cin >> n;

    if (n == 2) {
        cout << 0 << endl;

        return 0;
    }
    
    cout << (qpow(2, n) - 2 + mod) % mod << endl;
}
```

[AC record](https://www.luogu.com.cn/record/229262849)

---

## 作者：TLE_qwq (赞：2)

### 核心思路

- 长度为 $ n $ 的最大 01 字符串是二进制 $ n $ 个 1，十进制是 $ 2^n - 1 $，其异或之力计算为：
   - 最大值 $ P = 2^n - 1 $
   - 最小值 $ Q = 1 $（因 $ 2^n - 1 $ 是奇数）
   - 差值为 $ (2^n - 1) - 1 = 2^n - 2 $
- 特殊情况：一定要注意，当 $ n=2 $ 时，所有字符串对应数值最大为 3，其异或之力为 0，需要单独特判哦。~~本蒟蒻刚开始就没想到。~~

### 结论
- 如果 $ n=2 $，直接输出 0。
- 不然就计算 $ (2^n - 2) \mod (10^9+7) $，用快速幂更快！
### 代码
```cpp
#include <iostream>
using namespace std;
const int MOD = 1e9 + 7;

// 快速幂计算
long long f(long long un, long long nu, int mod) {
    long long res = 1;
    un %= mod;
    while (nu > 0) {
        if (nu % 2 == 1) res = (res * un) % mod;
        un = (un * un) % mod;
        nu /= 2;
    }
    return res;
}

int main() {
    int n;
    cin >> n;
    if (n == 2) { // 特判n=2的情况
        cout << 0;
        return 0;
    }
    long long ans = (f(2, n, MOD) - 2 + MOD) % MOD;
    cout << ans << endl;
    return 0;
}
```

---

## 作者：Bill_luogu (赞：1)

## 题目思路：
由于题目要求使 $P-Q$ 最大，所以考虑 $P$ 最大和 $Q$ 最小。
::::info[$P$ 最大]
我们知道长度为 $n$ 的 01 字符串在二进制下的最大值为 $2^n-1$，记作 $X$。我们可以构造 $A,B$，使得 $A+B=X,A\oplus B=X$，因此 $P$ 最大为 $2^n-1$，$C=X$。
::::
::::info[$Q$ 最小]
要使 $Q$ 最小，我们就得使 $A\oplus B$ 最小，最小为 $0$，这时 $A=B$，而 $C\bmod2=0$，所以 $A\oplus B\ge1$，$Q$ 最小为 $1$。
::::
答案即为 $P-Q=2^n-1-1=2^n-2$，使用[快速幂](https://oi-wiki.org/math/binary-exponentiation/)计算即可。

自信提交，你会惊讶地发现 WA 了一个点，这是为什么呢？

这是因为我们忘记判断特殊情况了。

当 $n=2$ 时，只有 $C=2$ 和 $C=3$ 两种情况。
- $C=2$ 时：
  - 只能分解成 $A=1$ 且 $B=1$，此时 $P=Q$，答案为 $0$。
- $C=3$ 时：
  - 只能分解成 $A=1,B=2$ 或 $A=2,B=1$ 两种情况，$P=3,Q=3$，此时 $P=Q$，答案为 $0$。

得出结论： $n=2$ 时答案为 $0$，$n\not=2$ 答案为 $2^n-2$。

~~于是我们便愉快地 AC 了此题。~~
## AC Code：
```cpp lines=6-17,21-21 line-numbers
#include<iostream>
using namespace std;
typedef long long ll;
const ll mod=1e9+7;
ll n;
//快速幂模板
ll ksm(ll x,ll mi)
{
    ll ans=1;
    while(mi)
    {
        if(mi&1)ans=ans*x%mod;
        x=x*x%mod;
        mi>>=1;
    }
    return ans;
}
int main()
{
    cin>>n;
    if(n==2)cout<<0;//特判
    else cout<<(ksm(2,n)+mod-2)%mod;
    return 0;
}
```

---

## 作者：linhanmo (赞：1)

# 题解：B4372 [GXPC-S 2025] 异或之力 / xor

## 异或最大值

- $C$ 不形如 $2^k$：设其二进制下最低位的 $1$ 是在第 $p$ 位，取 $A=C-2^{p-1},B=2^{p-1}$，$A\oplus B=C$；

- $C$ 形如 $2^k$：取 $A=C-1,B=1$，则 $A\oplus B=C-2$。

## 异或最小值

设 $C$ 最低位的 $0$ 在第 $p$ 位，则答案等于 $2^{p-1}-1$。

## 合并

- $n=2$：不论怎么取，答案都等于 $0$；
- $n>2$：显然取 $2^n-2$ 时最优，答案是 $2^n-2$。

::::success[code]
```cpp lines=12-13 line-numbers
#include <stdio.h>
constexpr int MOD = 1e9 + 7;
int power(int base, int exp) {
    int res = 1;
    for (; exp; base = 1ll * base * base % MOD, exp >>= 1)
        if (exp & 1) res = 1ll * res * base % MOD;
    return res;
}
int n;
int main(void) {
    scanf("%d", &n);
    printf("%d", n == 2 ? 0
          : (power(2, n) - 2 + MOD) % MOD);
    return 0;
}
```
::::

---

## 作者：weichenglu (赞：1)

## 前置芝士
[快速幂](https://www.luogu.com.cn/problem/P1226)。

## 题目概括
给定一个整数 $n$，考虑所有长度为 $n$ 的 01 字符串（可以包含前导零）。每个字符串对应一个二进制数 $C$。  
对于每个 $C$，设其异或之力为 $a$，计算 $a$：
- 如果 $C \le 1$，$a = 0$。  
- 如果 $C > 1$，枚举**所有**可能的分解方式 $A + B = C$，并计算：
  - $P = \max(A \operatorname{xor} B)$
  - $Q = \min(A \operatorname{xor} B)$
  - $a = P - Q$

最终，在所有长度为 $n$ 的 01 字符串中，找出最大的 $a$，并对 $10^{9} + 7$ 取模后输出。

## 思路分析
通过手玩一些较小的 $n$，或者 DFS 搜索打表就容易发现这道题的规律。

### 简单说明：
我们可以从长度为 $n$ 的最大 01 串，$2^{n}-1$ 开始手磨。  
但是，$2^{n}-1$ 是不可能成为答案的，虽然异或最大值可以是 $2^{n}-1$，但是由于其无法分成两个相等的整数，所以异或最小值一定大于 $0$。  
因此，我们尝试 $2^{n}-2$，其实其就是二进制长度为 $n$ 的最大的偶数。  
思考一下：我们要想拆分出来的两个数的异或最大值减去异或最小值最大，那么就要拆分出来的异或最大值尽可能大，最小值尽可能小。**异或最大值，可以是这个二进制数本身**，因为只需要让每一个二进制位不相同就行；**异或最小值可以为 $0$**，因为只需要让每一个二进制位都相同，也就是说两个数相同的时候就行。这样，我们容易发现 $2^{n}-2$ 成为答案是可行的，因为偶数一定可以拆分成两个相同的数，而相同的数异或结果为 $0$。  

综上所述，答案就是 $2^{n}-2$。

因为 $1 \le n \le 10^{9}$，需要使用**快速幂**求解。

## 注意
1. 我们需要特判当 $n=2$ 的时候，因为 $n=2$ 时，只能分解为 $1+1=2$，不能分解为 $2+0$，所以此时答案为 $0$。
2. 因为在快速幂运行完成后，需要减 $2$，所以取模时可能出现**负数**，因此在取模前应先加上模数。
3. **不开 long long 见祖宗！**

## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int n;
const int mod = 1e9+7;

int qpow(int x,int y){
	int res = 1;
	while (y){
		if (y&1) res = res * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return res % mod;
}

signed main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n;
	if (n == 2) cout << 0;
	else {
		int ans =  qpow(2,n) % mod - 2;
		if (ans >= 0) cout << ans;
		else cout << ans + mod;
	}
	
	return 0;
}
```
## 总结
一道~~诈骗题~~偏思维题。

---

## 作者：M1__ (赞：0)

# 题解：B4372 [GXPC-S 2025] 异或之力 / xor

[Link](https://www.luogu.com.cn/problem/B4372)


> 假设某个 01 字符串所代表的十进制数为 $C$，当 $C \le 1$ 时异或之力为 $0$；当 $C > 1$ 时，将 $C$ 分解成任意两个正整数 $A$ 和 $B$ （$A > 0$，$B > 0$，$A + B = C$），得到 $A$ 异或 $B$ 的最大值为 $P$，异或最小值为 $Q$，异或之力即为 $P$ 和 $Q$ 的差值。

## 题目思路

设异或之力为 $f$，则 $f=P-Q=(A \oplus B)_{\max}-(A \oplus B)_{\min}$。

首先我们想到，对于一个 $n$ 位的二进制串，要使其十进制状态下最大，显然有这样一个字符串：

$$\texttt{11111111111111} \cdots \texttt{111111111111111}$$

设这个二进制串在十进制下的值为 $g(n)$，则 $g(n)=2^{n}-1$。

**考虑最大值**。根据异或的性质，有 $A+B=n$ 且 $A \oplus B = n$。因此必然有 $A \oplus B \le n$。因此最大值为 $g(n)=2^{n}-1$。

**考虑最小值**。因为 $2^n \bmod 2=0$，所以 $2^{n}-1 \bmod 2 \neq 0$。所以当 $A \oplus B=g(n)$ 时，一定有 $A \neq B$，因此 $(A \oplus B)_{\min}=1$。

此时 $f=(A \oplus B)_{\max}-(A \oplus B)_{\min}=2^{n}-1-1=2^{n}-2$。

**考虑是否最优**。令 $g(n)=2^{n}-2$，则 $g(n) \bmod 2=0$，此时 $(A \oplus B)_{\max}=g(n)=2^{n}-2$，$(A \oplus B)_{\min}=0$，此时 $f=(A \oplus B)_{\max}-(A \oplus B)_{\min}=2^{n}-2-0=2^{n}-2$。

令 $g(n)=2^{n}-3$，则 $g(n) \bmod 2 \neq 0$，此时 $(A \oplus B)_{\max}=g(n)=2^{n}-3$，$(A \oplus B)_{\min}=1$，此时 $f=(A \oplus B)_{\max}-(A \oplus B)_{\min}=2^{n}-3-1=2^{n}-4$。

所以我们可以得出，当 $g(n) < 2^n-1$ 时，$f \le 2^{n}-1$。

证毕，所以 $f=2^{n}-1$。 

**注意 $n=2$ 时，最大值和最小值的取值方法都是相同的，此时 $f=0$。**

考虑到 $2 \le n \le 10^{9}$，这里使用快速幂。

## 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MOD=1e9+7;
ll n;
inline ll qp(ll a,ll b,ll mod){
	ll ans=1;
	a%=mod;
	while(b){
		if(b&1) ans=(ans)*a%mod;
		a=a*a%mod,b>>=1;
	}
	return ans;
}
int main(){
	cin>>n;
	if(n==2){
		cout<<0;
		return 0;
	}
	cout<<(qp(2,n,MOD)-2+MOD)%MOD;
	return 0;
}
```

---

