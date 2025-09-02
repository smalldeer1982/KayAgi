# Guess the Root

## 题目描述

评委选定了一个多项式 $f(x) = a_0 + a_1 \cdot x + a_2 \cdot x^2 + \dots + a_k \cdot x^k$，其中 $k \leq 10$，所有 $a_i$ 都是整数，且 $0 \leq a_i < 10^6 + 3$。保证至少存在一个 $i$ 使得 $a_i > 0$。

现在，评委希望你找到一个整数 $x_0$，使得 $f(x_0) \equiv 0 \pmod{10^6 + 3}$，或者报告不存在这样的 $x_0$。

你最多可以询问 $50$ 次：每次你可以询问一个值 $x_q$，评委会告诉你 $f(x_q) \bmod (10^6 + 3)$ 的值。

注意，输出答案不计入查询次数。

## 说明/提示

第一个样例中的多项式为 $1000002 + x^2$。

第二个样例中的多项式为 $1 + x^2$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
 
1000002

0
```

### 输出

```
? 0

? 1

! 1```

## 样例 #2

### 输入

```
 
5

2

1

```

### 输出

```
? 2

? 1

? 0

! -1```

# 题解

## 作者：hht2005 (赞：7)

# 题目链接

[cf1155E](http://codeforces.com/problemset/problem/1155/E)

# sol

**思路**

众所周知，n个点可以确定一个n-1次多项式，所以我们问11次就可确定这个多项式。问11次后可以[高斯消元](https://www.luogu.org/problemnew/solution/P3389)或[拉格朗日插值](https://www.luogu.org/problemnew/solution/P4781)，之后暴力带入0到1e6-3之间的数检验。

可能会有分数，需要逆元，使用拉格朗日插值会更简单。

**code**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1e6+3;
inline int powmod(int a,int b) {
	int ans=1;
	while(b) {
		if(b&1)ans=1ll*ans*a%mod;
		a=1ll*a*a%mod;
		b>>=1;
	}
	return ans;
}
int p[11];
int qry(int a) {//交互询问
	printf("? %d\n",a);fflush(stdout);
	int t;
	cin>>t;
	return t;
}
void write(int i) {//交互输出
	printf("! %d\n",i);fflush(stdout);
	exit(0);
}
int main() {
	for(int i=0;i<=10;i++) {//先问11次
		p[i]=qry(i);
		if(!p[i])write(i);
		for(int j=0;j<=10;j++) {
			if(i==j)continue;
			p[i]=1ll*p[i]*powmod(i-j,mod-2)%mod;//拉格朗日插值，顺便考虑逆元。
		}
	}
	for(int i=11;i<mod;i++) {//暴力代入
		int v=0;
		for(int j=0;j<=10;j++) {
			int val=1;
			for(int k=0;k<=10;k++) {
				if(j==k)continue;
				val=1ll*val*(i-k)%mod;
			}
			v=(v+1ll*val*p[j])%mod;
		}
		if(v==0)write(i);
	}
	write(-1);
	return 0;
}
```

---

## 作者：Fido_Puppy (赞：4)

$$\texttt{Foreword}$$

~~感觉这道交互题好简单……~~

我这种交互黄题都做不出来的蒟蒻尽然能在 Virtual participation 中过了这题。

$$\texttt{Description}$$

[CF1155E Guess the Root](https://www.luogu.com.cn/problem/CF1155E)

$$\texttt{Solution}$$

由于多项式的次数不超过 $10$，所以我们只需要询问 $11$ 次就可以把多项式确定下来。

具体就是解一个**十一元一次方程组**，明显可以用 [高斯消元](https://www.luogu.com.cn/problem/P3389) 做。

~~别的大佬好像用的都是拉格朗日插值，什么都不会的蒟蒻瑟瑟发抖。~~

这道题由于是在 $\mod (10^6 + 3)$ 下，我们除法就可以改成逆元（不用考虑精度问题啦），并且求零点时只需要 $0 \sim 10^6 + 2$ 暴力枚举就行了。

$$\texttt{Code}$$

```cpp
#include "bits/stdc++.h"

int main() {
	std :: ios_base :: sync_with_stdio(false);
	std :: cin.tie(nullptr);
	
	typedef long long ll;
	const int mod = 1e6 + 3;
	
	std :: vector < std :: vector <ll> > a(20, std :: vector <ll> (20));
	
	auto qpow = [&] (ll x, int p) {
		ll ans = 1;
		while (p) {
			if (p & 1) ans = ans * x % mod;
			x = x * x % mod;
			p >>= 1;
		}
		return ans;
	};
	
	for (int i = 1; i <= 11; i++) {
		std :: cout << "? " << i - 1 << std :: endl;
		int y; std :: cin >> y;
		ll P = 1ll;
		for (int j = 1; j <= 11; j++) {
			a[i][j] = P;
			P = P * 1ll * (i - 1) % mod;
		}
		a[i][12] = y;
	}
	
	for (int i = 1; i <= 11; i++) {
		for (int j = i + 1; j <= 12; j++) {
			a[i][j] = a[i][j] * qpow(a[i][i], mod - 2) % mod;
		}
		a[i][i] = 1ll;
		for (int j = 1; j <= 11; j++) {
			if (i != j) {
				for (int k = i + 1; k <= 12; k++) {
					a[j][k] = (a[j][k] - a[j][i] * a[i][k] % mod + mod) % mod;
				}
				a[j][i] = 0;
			}
		}
	}
	
	for (int i = 0; i < mod; i++) {
		ll sum = 0, P = 1ll;
		for (int j = 1; j <= 11; j++) {
			sum = (sum + P * a[j][12]) % mod;
			P = P * 1ll * i % mod;
		}
		if (sum == 0) {
			std :: cout << "! " << i << std :: endl;
			return 0;
		}
	}
	
	std :: cout << "! -1" << std :: endl;
	
	return 0;
}
```

$$\texttt{Thanks for watching!}$$

---

## 作者：封禁用户 (赞：2)

首先看到模数只有$10^6+3$,所以我们可以考虑通过某些手段搞出来这个多项式然后暴力枚举所有数带进去检验是否是根。

至于如何搞出来这个多项式？

假设多项式的次数为k,那么我们可以搞出来k个点值然后高斯消元\拉格朗日插值。

关于确定多项式的次数？k次多项式在连续值域上的k+1阶差分全都是0.

所以把1-50的值求出来后差分检验一下多项式次数即可。

```cpp
#include <algorithm>
#include <cstring>
#include <iostream>
#include <tuple>
#include <utility>
#include <vector>
using int_t = long long int;
using pair_t = std::pair<int_t, int_t>;
using std::cin;
using std::cout;
using std::endl;

const int_t mod = 1e6 + 3;
const int_t LARGE = 1e5;
int_t power(int_t base, int_t index) {
    const int_t phi = mod - 1;
    index = (index % phi + phi) % phi;
    int_t result = 1;
    while (index) {
        if (index & 1) result = result * base % mod;
        index >>= 1;
        base = base * base % mod;
    }
    return result;
}

void poly_mul(const int_t* A, int_t n, const int_t* B, int_t m, int_t* C) {
    static int_t Cx[LARGE];
    std::fill(Cx, Cx + 1 + n + m, 0);
    for (int_t i = 0; i <= n; i++) {
        for (int_t j = 0; j <= m; j++) {
            Cx[i + j] = (Cx[i + j] + A[i] * B[j] % mod) % mod;
        }
    }
    std::copy(Cx, Cx + 1 + n + m, C);
}
void poly_div(const int_t* A, int_t n, const int_t* B, int_t m, int_t* Q) {
    static int_t R[LARGE];
    std::copy(A, A + 1 + n, R);
    for (int_t i = n - m; i >= 0; i--) {
        int_t Qx = R[i + m] * power(B[m], -1) % mod;
        Q[i] = Qx;
        for (int_t j = m; j >= 0; j--) {
            R[i + j] = (R[i + j] - B[j] * Qx % mod + 2 * mod) % mod;
        }
    }
}
int main() {
    std::vector<pair_t> vtxs;
    std::vector<int_t> vec;
    for (int_t i = 1; i <= 50; i++) {
        cout << "? " << i << endl;
        cout.flush();
        int_t x;
        cin >> x;
        vec.push_back(x);
        vtxs.push_back(pair_t(i, x));
    }
    //差分
    int_t count = 0;
    while (true) {
        for (int_t i = 0; i < vec.size() - 1; i++)
            vec[i] = (vec[i + 1] - vec[i] + mod) % mod;
        vec.pop_back();
        count++;
#ifdef DEBUG
        cout << "diff " << count << " ok ";
        for (int_t x : vec) cout << x << " ";
        cout << endl;

#endif
        if (std::count(vec.begin(), vec.end(), 0) == vec.size()) {
            break;
        }
    }

    while (vtxs.size() > count) vtxs.pop_back();
#ifdef DEBUG
    cout << "count = " << count << endl;
    for (auto x : vtxs) cout << x.first << " " << x.second << endl;
#endif
    static int_t prod[LARGE];
    prod[0] = 1;
    for (const auto& kvp : vtxs) {
        int_t B[] = {mod - kvp.first, 1};
        poly_mul(prod, vtxs.size(), B, 1, prod);
    }
    static int_t result_poly[LARGE];
    for (const auto& kvp : vtxs) {
        int_t x, y;
        std::tie(x, y) = kvp;
        int_t coef = y;
        int_t prod2 = 1;
        for (int_t i = 0; i < vtxs.size(); i++) {
            if (vtxs[i].first != x) {
                prod2 = prod2 * (x - vtxs[i].first + mod) % mod;
            }
        }
        coef = coef * power(prod2, -1) % mod;
        static int_t curr[LARGE];
        int_t B[] = {mod - x, 1};
        poly_div(prod, vtxs.size(), B, 1, curr);
        for (int_t i = 0; i <= vtxs.size(); i++) {
            result_poly[i] = (result_poly[i] + coef * curr[i] % mod) % mod;
        }
    }
    // for (int_t i = 0; i <= vtxs.size(); i++) cout << result_poly[i] << " ";
    // cout << endl;
    const auto subs = [&](int_t x) {
        int_t result = 0, pow = 1;
        for (int_t i = 0; i <= vtxs.size() - 1; i++) {
            result = (result + pow * result_poly[i] % mod) % mod;
            pow = pow * x % mod;
        }
        return result;
    };
    for (int_t i = 0; i < mod; i++) {
        if (subs(i) == 0) {
            cout << "! " << i << endl;
            cout.flush();
            return 0;
        }
    }
    cout << "! -1" << endl;

    return 0;
}
```

---

## 作者：tanghg (赞：0)

首先如果我们能够知道这个多项式，然后又因为保证了 $x\leq 10^6$，所以确定出所有的 $a$ 之后枚举即可。至于这个 $a$，因为这个多项式的次数不超过十，所以可以随便询问十次然后解一元十次方程。

矩阵就长成这样：
$$\begin{bmatrix} x_1 & x_1^2 & \cdots & f(x_1) \\ x_2 & x_2^2 & \cdots & f(x_2) \\ \vdots & \vdots & \ddots & \vdots \\ x_{10} & x_{10}^2 & \cdots & f(x_{10}) \end{bmatrix}$$

在高斯消元中注意取模。然后注意开 long long。

```cpp
#include<iostream>
#define int long long
using namespace std;
typedef int ll;
const ll MAXN=55;
const ll MOD=1e6+3;
ll ksm(ll a,ll b){
    ll ans=1;
    while(b){
        if(b&1){
            ans=(ans*a)%MOD;
        }
        a=(a*a)%MOD;
        b>>=1;
    }
    return ans%MOD;
}
ll inv(ll x){
    return ksm(x,MOD-2);
}
ll n;
ll a[MAXN][MAXN];
ll ans[MAXN];
void Gauss(){
    for (int i = 1; i <=n ; ++i) {
        ll r=i;
        for (int j = i+1; j <=n ; ++j) {
            if(a[r][i]<a[j][i]){
                r=j;
            }
        }
        swap(a[i],a[r]);
        for(int j=i+1;j<=n;++j){
            ll t1=a[j][i];
            for(int k=i;k<=n+1;++k){
                a[j][k]=a[j][k]*a[i][i]%MOD;
                a[j][k]-=(a[i][k]*t1)%MOD;
                a[j][k]=(a[j][k]%MOD+MOD)%MOD;
            }
        }
    }
    for (ll i = n; i >=1 ; --i) {
        ans[i]=a[i][n+1];
        for (ll j = i+1; j <=n ; ++j) {
            ans[i]-=(ans[j]*a[i][j])%MOD;
            ans[i]=(ans[i]%MOD+MOD)%MOD;
        }
        ans[i]*=inv((a[i][i]%MOD+MOD)%MOD);
        ans[i]=(ans[i]%MOD+MOD)%MOD;
    }
}
signed main(){
    n=10;
    cout<<"? "<<0<<endl;
    ll x0;
    cin>>x0;
    x0%=MOD;
    for(int i=1;i<=n;++i){
        cout<<"? "<<i<<endl;
        ll x;
        cin>>x;
        x-=x0;
        x=(x%MOD+MOD)%MOD;
        a[i][11]=x;
        ll X=i;
        for(int j=1;j<=n;++j){
            a[i][j]=X;
            X*=i;
            X%=MOD;
        }
    }
    Gauss();
    for(int i=0;i<1e6+3;++i){
        ll val=0;
        ll last=i;
        for(int j=1;j<=10;++j){
            val+= last*ans[j]%MOD;
            val%=MOD;
            last=last*i%MOD;
        }
        val=(val+x0)%MOD;
        if(val==0){
            cout<<"! "<<i<<endl;
            return 0;
        }
    }
    cout<<"! "<<-1<<endl;
    return 0;
}
```

---

## 作者：船酱魔王 (赞：0)

# Guess the Root 题解

## 题意回顾

在模 $ P $ 意义下，存在未知的不高于 $ 10 $ 次非负整系数多项式函数 $ f(x) $，定义域和值域均在 $ [0,P) $ 之内的整数。

你可以询问 $ f(x) $ 的值，目标是输出函数零点值或报告定义域内无零点。

$ P=10^6+3 $，你最多**询问** $ 50 $ 次。

## 分析

如果知道多项式的话，可以直接枚举定义域内的所有值以寻找零点。

询问次数很宽，其实 $ 11 $ 次询问一定出解。确定 $ f(x) $ 在 $ [0,10] $ 内的取值即可唯一确定常数项和 $ 1 \sim 10 $ 次项，若次数不足 $ 10 $ 高次项就是 $ 0 $，故可以直接当成 $ 10 $ 次多项式。

数据范围小，高斯消元和拉格朗日插值都行。

注意模意义下高斯消元的及时取模和避免溢出，还有除法需要用逆元，$ P $ 是质数直接费马小定理即可。

## AC 代码

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#define int long long
using namespace std;
const int N = 15;
const int mod = 1e6 + 3;
int n = 10;
int a[N][N];
int b[N];
int c = 0;
int x[N];
int ksm(int x, int y) {
	int res = 1;
	int mul = x;
	while(y) {
		if(y & 1) {
			res = res * mul % mod;
		}
		mul = mul * mul % mod;
		y >>= 1;
	}
	return res;
}
signed main() {
	cout << "? 0" << endl;
	cin >> c;
	for(int i = 1; i <= n; i++) {
		cout << "? " << i << endl;
		cin >> b[i];
		b[i] -= c;
		b[i] = (b[i] % mod + mod) % mod;
		a[i][0] = 1;
		for(int j = 1; j <= n; j++) {
			a[i][j] = a[i][j - 1] * i % mod;
		}
		a[i][0] = 0;
	}
	for(int i = 1; i <= n; i++) {
		int id = 0;
		for(int j = i; j <= n; j++) {
			if(a[j][i] > a[id][i]) {
				id = j;
			}
		}
		if(i != id) {
			for(int j = i; j <= n; j++) {
				swap(a[id][j], a[i][j]);
			}
			swap(b[id], b[i]);
		}
		for(int j = i + 1; j <= n; j++) {
			int aq = a[j][i];
			for(int k = i; k <= n; k++) {
				a[j][k] = a[j][k] * a[i][i] % mod;
				a[j][k] -= a[i][k] * aq % mod;
				a[j][k] = (a[j][k] % mod + mod) % mod;
			}
			b[j] = ((b[j] * a[i][i] % mod - b[i] * aq % mod) % mod + mod) % mod;
		}
	}
	for(int i = n; i >= 1; i--) {
		int qr = b[i];
		for(int j = n; j > i; j--) {
			qr -= x[j] * a[i][j] % mod;
			qr = (qr % mod + mod) % mod; 
		}
		x[i] = qr * ksm((a[i][i] % mod + mod) % mod, mod - 2) % mod;
		x[i] = (x[i] % mod + mod) % mod;
	}
	int ok = 0;
	for(int i = 0; i < mod; i++) {
		int qr = 0;
		for(int j = 1; j <= n; j++) {
			qr += x[j] * ksm(i, j) % mod;
			qr %= mod;
		}
		qr += c;
		qr %= mod;
		if(qr == 0) {
			cout << "! " << i << endl;
			ok = 1;
			break;
		}
	}
	if(ok == 0) {
		cout << "! -1" << endl;
	}
	return 0;
}
```

---

## 作者：5k_sync_closer (赞：0)

通过拉格朗日插值，确定一个 $10$ 次多项式只需要 $11$ 个点值，也就是只需要 $11$ 次询问。

多项式的值是模 $10^6+3$ 意义下的，所以有零点时 $[0,10^6+3)$ 内必有一个零点，枚举这个范围即可。

```cpp
#include <cstdio>
#define M 1000003
#define int long long
int f[20], o[M + 50], v[M + 50];
int F(int x)
{
    if (x <= 10)
        return f[x];
    int z = 1, q = 0;
    for (int i = 0; i <= 10; ++i)
        z = z * (x - i) % M;
    for (int i = 0, k; i <= 10; ++i)
        k = f[i] * v[x - i] % M * v[o[i]] % M * v[o[10 - i]] % M, q = 10 - i & 1 ? (q + M - k) % M : (q + k) % M;
    return q * z % M;
}
signed main()
{
    for (int i = o[0] = 1; i <= M; ++i)
        o[i] = o[i - 1] * i % M;
    v[1] = 1;
    for (int i = 2; i < M; ++i)
        v[i] = (M - M / i) * v[M % i] % M;
    for (int i = 0; i <= 10; ++i)
    {
        printf("? %lld\n", i);
        fflush(stdout);
        scanf("%lld", f + i);
    }
    for (int i = 0; i < M; ++i)
        if (!F(i))
        {
            printf("! %lld\n", i);
            fflush(stdout);
            return 0;
        }
    puts("! -1");
    fflush(stdout);
    return 0;
}
```


---

## 作者：xlpg0713 (赞：0)

## 题意：

交互题，界为十的多项式，最多得到 $50$ 组 $x$ 取值下 $y$ 的取值，求原多项式的零点。模 $10^6+3$ 意义下。

## 思路：
考虑如果知道了原多项式，可以枚举模意义下每个可能的取值判断，模数较小，可以通过。

因此问题转化成了如何求解原多项式，设原多项式为 $\sum_{i=0}^na_i\times x^i$ 其中 $n$ 为多项式的界。
对于每个询问 $x_j$，设 $f_{j,i}$ 表示 $(x_j)^i$。我们就可以得到 $\sum_{i=0}^nf_{j,i}\times a_i$。

很明显我们是知道 $f$ 的（你问的你不知道）。发现这个形式就可以高斯消元做了，只需要问至少 $11$ 次（包括常数项），得到 $n$ 个 $n$ 元 $1$ 次方程，联立解掉就行了。

最后这题是模意义下的，记得求逆元。

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int mod = 1e6 + 3;
int a[21][21], b[231], n = 11;
inline int qpow(int a, int b){
    int res = 1; while(b){
        if(b & 1) res = res * a % mod;
        a = a * a % mod; b >>= 1;
    } return res; //逆元
}
inline int f(int x){
    int res = 0;
    for(int i = 1, j = 1; i <= 11; i++)
        (res += b[i] * j) %= mod, j = j * x % mod;
    return res;
}
signed main(){
    for(int i = 1, x; i <= n; i++){
        cout << "? " << i << endl;
        cin >> x; a[i][12] = x;
        for(int j = 1, k = 1; j <= 11; j++)
            a[i][j] = k, k = k * i % mod;
    }// 询问11次
    for(int i = 1; i <= n; i++){
        for(int j = i; j <= n; j++) if(a[j][i]) {swap(a[i], a[j]); break;}
        for(int j = 1; j <= n; j++){ if(i == j) continue;
            int d = (-a[j][i]*qpow(a[i][i],mod-2)%mod+mod)%mod;
            for(int k = 1; k <= 12; k++) (a[j][k]+=a[i][k]*d%mod)%mod;
        }
    } //高斯消元
    for(int i = 1; i <= n; i++) b[i] = a[i][12] * qpow(a[i][i], mod - 2) % mod;
    for(int i = 0; i < mod; i++)
        if(f(i) == 0) return cout << "! " << i << endl, 0; //枚举答案
    cout << "! -1" << endl; //记得无解
}
```

---

## 作者：_sunkuangzheng_ (赞：0)

$\textbf{1.1 Hints}$

- $\textbf{1.1.1 Hint 1}$

如果知道多项式每一项的系数，如何求出答案？

- $\textbf{1.1.2 Hint 2}$

如果你知道 $11$ 处多项式的取值，你就能得到一个关于系数的十一元一次方程组。

- $\textbf{1.1.3 Hint 3}$

使用高斯消元求解。

$\textbf{1.2 Solution}$

我们询问 $1 \sim 11$ 的 $f(x)$，得到十一个一次方程，直接高斯消元即可。

然后得到多项式后，暴力枚举检验答案。时间复杂度 $\mathcal O(np+n^3)$，其中 $n=11,p = 10^6+3$。

$\textbf{1.3 Code}$

```cpp
/**
 *    author: sunkuangzheng
 *    created: 04.10.2023 21:21:07
**/
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 1e6+3;
int t,n,a[15][15],f[15];
int qp(int a,int b){
    int r = 1;
    for(;b;b >>= 1,a = a * a % mod) if(b & 1) r = r * a % mod;
    return r;
}int g(int x){
    int r = 0,a = 1;
    for(int i = 11;i >= 1;i --) r = (r + a * f[i]) % mod,a = a * x % mod;
    return r;
}signed main(){
    ios::sync_with_stdio(0),cin.tie(0);
    for(int i = 1;i <= 11;i ++){
        cout << "? " << i << endl,cin >> a[i][12];int fs = 1;
        for(int j = 11;j >= 1;j --) a[i][j] = fs,fs = fs * i % mod;
    }for(int i = 1;i <= 11;i ++){
        for(int j = i;j <= 11;j ++) if(a[j][i]) {swap(a[i],a[j]);break;}
        if(!a[i][i]) return cout << "! -1",0;
        for(int j = 1;j <= 11;j ++){
            if(i == j) continue; int d = a[j][i] * qp(a[i][i],mod-2) % mod;
            for(int k = 1;k <= 12;k ++) a[j][k] = (a[j][k] - a[i][k] * d % mod + mod) % mod;
        }
    }for(int i = 1;i <= 11;i ++) f[i] = a[i][12] * qp(a[i][i],mod-2) % mod;
    for(int i = 0;i < mod;i ++) if(!g(i)) return cout << "! " << i,0;
    cout << "! -1";
}
```


---

## 作者：DQYdqy (赞：0)

## Solution:

考虑拉格朗日插值多项式的式子：
$$
F(x)=\sum_{i=0}^n(\prod_{0\le j\le n,i\not =j}\frac{x-x_i}{x_i-x_j})y_i
$$
因为至多11项，所以我们询问11次即可得到这个多项式

由于$x<1e6+3$，得到多项式后我们暴力枚举$x$计算$F(x)$即可

## Code:

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e6+3;
int p[11];
int read(){
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
    while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}
    return x*f;
}
int qpow(int a,int b){
    int re=1;
    while(b){
        if(b&1) re=(re*1ll*a)%mod;
        b>>=1;a=(a*1ll*a)%mod;
    }return re%mod;
}
int query(int x){
    printf("? %d\n",x);fflush(stdout);
    int val=read();return val;
}
void write(int x){
    printf("! %d\n",x);fflush(stdout);
    exit(0);
}
signed main(){
    for(int i=0;i<=10;i++){
        p[i]=query(i);
        if(p[i]==0) write(i);
    }
    for(int i=0;i<=10;i++){
        int v=1;
        for(int j=0;j<=10;j++){
            if(i==j) continue;
            v=((i-j+mod)%mod*1ll*v)%mod;
        }
        p[i]=(p[i]*1ll*qpow(v,mod-2))%mod;
    }
    for(int i=11;i<mod;i++){
        int v=0;
        for(int j=0;j<=10;j++){
            int val=1;
            for(int k=0;k<=10;k++){
                if(j==k) continue;
                val=((i-k+mod)%mod*1ll*val)%mod;
            }val=(val*1ll*p[j])%mod;
            v=(v+val)%mod;
        }
        if(!v) write(i);
    }write(-1);
    return 0;
}

```


---

