# Kosuke's Sloth

## 题目描述

Kosuke is too lazy. He will not give you any legend, just the task:

Fibonacci numbers are defined as follows:

- $ f(1)=f(2)=1 $ .
- $ f(n)=f(n-1)+f(n-2) $ $ (3\le n) $

 We denote $ G(n,k) $ as an index of the $ n $ -th Fibonacci number that is divisible by $ k $ . For given $ n $ and $ k $ , compute $ G(n,k) $ .As this number can be too big, output it by modulo $ 10^9+7 $ .

For example: $ G(3,2)=9 $ because the $ 3 $ -rd Fibonacci number that is divisible by $ 2 $ is $ 34 $ . $ [1,1,\textbf{2},3,5,\textbf{8},13,21,\textbf{34}] $ .

## 样例 #1

### 输入

```
3
3 2
100 1
1000000000000 1377```

### 输出

```
9
100
999244007```

# 题解

## 作者：chenxi2009 (赞：5)

~~VP 7min 切了。~~
### Upd 2024.11.1
优化了证明内容，在保证正确性的情况下略作精简。
# 思路
首先发现斐波那契数列对 $k$ 取余的余数是有周期性的，可以感性理解为一个 $k$ 的倍数后面一定会出现两个对 $k$ 同余的数，于是每个 $k$ 的倍数之间是等距的。换句话说，$G(n,k)=n\times G(1,k)$。（详细证明见文末）

另有结论：模数为 $p$ 的斐波那契数列循环节长度 $\pi(p)\le6p$。~~虽然但是，我不会证。~~

线性递推斐波那契数列直到找到 $k$  的倍数，时间复杂度为 $O(\sum k)$。
```cpp
#include<bits/stdc++.h> 
using namespace std;
const long long MOD = 1000000007;
int T,k,a1,a2,a3,ans;
long long n;
int main(){
	scanf("%d",&T);
	while(T --){
		scanf("%lld%d",&n,&k);
		if(k == 1){
			printf("%lld\n",n % MOD);
			continue;
		}
		a1 = a2 = 1;
		for(int i = 3;true;i ++){//用余数递推即可 
			a3 = (a1 + a2) % k;
			if(!a3){
				ans = i;
				break;
			}
			a1 = a2,a2 = a3;
		}
		printf("%lld\n",n % MOD * ans % MOD);
	}
}
```
# 上文结论的证明
证明 $G(n,k)=G(1,k)\times n$：

令 $G(1,k)=x$，发现 $f(x+1)\equiv f(x+2)\pmod k$。令 $f(x+1)\equiv m\pmod k$，再转化递推式为
$$
f_{i+x}=a_1f_{i+1}+a_2f_{i+2}(i\in\N)
$$
又有
$$
f_x=a_1f_1+a_2f_2=a_1+a_2\equiv0\pmod k\\
\therefore f_{2x}=a_1f_{x+1}+a_2f_{x+2}\equiv(a_1+a_2)m\equiv0\pmod k
$$
同理可证 $k\mid f_{ix},i\in\N^*$。

---

若 $\exist k\mid f_{ix+j},i,j\in\N,j\in[1,x)$，则可转化递推式为
$$
f_j=a_3f_1+a_4f_2(i\in\N)
$$
发现
$$
(a_3+a_4)m\equiv0\pmod k
$$
若 $a_3+a_4\equiv0\pmod k$，则发现了更小的循环周期，矛盾；若 $m\equiv0\pmod k$，说明周期为 $1$，不存在满足条件的 $f_{ix+j}$，矛盾。

综上，$k\mid f_i$，当且仅当 $i\mid G(1,k)$。

得证。

---

## 作者：lailai0916 (赞：3)

## 原题链接

- [洛谷 CF2033F Kosuke's Sloth](https://www.luogu.com.cn/problem/CF2033F)

## 参考资料

- [皮萨诺周期 - 维基百科](https://zh.wikipedia.org/wiki/皮萨诺周期)
- [A000045 - OEIS](https://oeis.org/A000045)

## 题意简述

求 Fibonacci 数列中第 $n$ 个能被 $k$ 整除的数的下标。

## 解题思路

Fibonacci 数列对 $k$ 取模具有周期性（皮萨诺周期），且周期 $r\le 6k$。

暴力枚举求出周期 $r$，则第 $n$ 个数的下标为 $rn$。

## 参考代码

```cpp

 #include <bits/stdc++.h>
using namespace std;
 
using ll=long long;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;
	cin>>T;
	while(T--)
	{
		ll n,k;
		cin>>n>>k;
		n%=mod;
		if(k==1)
		{
			cout<<n<<'\n';
			continue;
		}
		int f1=1,f2=1,f3=1;
		ll cnt=2;
	    while(f3!=0)
	    {
	    	f3=(f1+f2)%k;
	    	f1=f2;
	    	f2=f3;
	    	cnt++;
	    }
	    cout<<cnt*n%mod<<'\n';
	}
	return 0;
}
```

---

## 作者：Super_Cube (赞：1)

# Solution

斐波那契数列在模 $k$ 意义下有循环节，且循环节长度为 $O(k)$ 级别的。这东西学术名叫皮萨诺周期，证明了循环节长度不超过 $6k$。所以这题直接暴力找到循环节，答案就是其 $n$ 倍。

# Code

```cpp
#include<bits/stdc++.h>
const int mod=1e9+7;
int T,m,a,b,c,k;
long long n;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%lld%d",&n,&m);
		if(m==1){
			printf("%lld\n",n%mod);
			continue;
		}
		for(a=b=k=1;a;a=b,b=c,++k)
			if((c=a+b)>=m)c-=m;
		printf("%lld\n",n%mod*k%mod);
	}
	return 0;
}
```

---

## 作者：loser_seele (赞：0)

前置知识：https://www.luogu.com.cn/problem/solution/SP13419

有了上题的结论，我们不难算出斐波那契数列的最小周期，然后直接乘 $ n $ 即可。

然而我们发现如果直接提交，这个代码连样例都过不去。

原因在一个数模 $ p $ 等于 $ 0 $ 并不能代表其下一位一定模 $ p $ 后为 $ 1 $，不符合最小周期的定义。

于是我们发现这个周期一定是最小周期的某个约数，这里由于上述结论循环节不超过 $ 6p $ 所以直接枚举出所有约数之后判断其约数对应的位置是否为 $ 0 $，当然也可以用更优秀的实现，比如矩阵快速幂等等，此处不再详述。

不优化时的时间复杂度不变，为 $ \mathcal{O}(Tn) $，采取优化之后可以进一步优化到 $ \mathcal{O}(Tn^\frac{1}{4}\log{n}) $，来自质因数分解和矩阵快速幂的时间复杂度，因为实现太复杂所以没写。

[code](https://codeforces.com/contest/2033/submission/290475291)

---

## 作者：_Lazy_whr_ (赞：0)

这题很明显是一个数学题。

斐波那契数列取模 $k$ 具有周期性，这个周期叫做皮萨诺周期，并且周期 $L \le 6k$。

所以我们暴力枚举求出周期 $L$ ，则第 $n$ 个数的下标为 $L \times n$。
```cpp
#include<bits/stdc++.h>
#define int long long
#define endl "\n"
#define x1 x10
#define y1 y10
// #define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, (1 << 20), stdin), p1 == p2) ? EOF : *p1++)
// #pragma GCC target("avx")
// #pragma GCC optimize(3,"Ofast","inline")
namespace FastIO {
	char buf[(1 << 20)], *p1, *p2;
	char pbuf[(1 << 20)], *pp;
	inline int read () {
		int x = 0, f = 1;
		char ch = getchar ();
		while (ch < '0' || ch > '9') {
			if (ch == '-')
				f = -1;
			ch = getchar ();
		}
		while (ch >= '0' && ch <= '9') {
			x = (x << 1) + (x << 3) + (ch ^ 48);
			ch = getchar ();
		}
		return x * f;
	}
	
	template<typename T> inline void read (T &x) {
		x = read ();
		return;
	}
	
	template<typename T,typename... Args> inline void read (T &x,Args &...x_) {
		read (x);
		read (x_...);
		return;
	}
}

namespace Constants {
	const int INF = 1e18;
	const int DIR[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
	const double EPS = 1e-7;
	const double PI = 3.14159265358979323;
}

using namespace std;
using namespace FastIO;
using namespace Constants;

void CLOSE () {
	ios::sync_with_stdio (false);
	cin.tie (nullptr);
	cout.tie (nullptr);
	return;
}

const int MOD = 1e9 + 7;

int n, k;

signed main() {
	CLOSE ();
    int t = read ();
    while (t--) {
        read (n, k);
        n %= MOD;
        if (k == 1) {
            cout << n << endl;
            continue;
        }
        int x = 1, y = 1, z = 1;
        int L = 2;
        while (z != 0) {
            z = (x + y) % k;
            x = y;
            y = z;
            L++;
        }
        cout << L * n % MOD << endl;
    }
	return 0;
}
```

---

## 作者：The_foolishest_OIer (赞：0)

纪念第一次在 Div.3 中切掉 F 题（虽然没打多少场）。

总所周知，斐波那契数列对 $k$ 取模时余数是有周期的，所以，$G(n,k) = G(1,k) \times n$。

然后就暴力找 $k$ 的倍数，时间复杂度 $O(\sum k)$，可以通过本题。

代码十分简单：


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int N = 1e5 + 10;
const int mod = 1e9 + 7;
int t,n,k;
void solve(){
	cin >> n >> k;
	if (k == 1){
		cout << n % mod << endl;
		return;
	}
	int x = 1,y = 1,z = 1;
	int cnt = 2;
	while(z){
		cnt++;
		x = y;
		y = z;
		z = (x + y) % k;
	}
	cout << ((n % mod) * cnt) % mod << endl; // 取模！！！！！
}
void close(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}
signed main(){
	close();
	cin >> t;
	while (t--) solve();
	return 0;
}
```

---

## 作者：abensyl (赞：0)

原题：[CF2033F Kosuke's Sloth](https://www.luogu.com.cn/problem/CF2033F)。

## 思路

考察斐波那契数列[皮萨诺周期](https://oeis.org/A001175)的性质。

简单来说，皮萨诺周期就是斐波那契数列模 $k$ 意义下的的最小正周期，可以证明，这个周期长度不超过 $6k$，且等号只在 $k=2\times 5^p$（$p\in N^*$）时取得。

那么也就是说我们只需要枚举最小正周期就可以了，答案即为最小正周期长度乘以 $n$。

总时间复杂度为 $O(\sum k)$。

[代码 + 我的 AC 记录](https://codeforces.com/contest/2033/submission/289124691)。

---

