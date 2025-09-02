# [OOI 2022] Good arrays

## 题目描述

最近，Vasya 学会了整数除法。受到这项神奇知识的启发，他决定进一步了解满足某些整除性质的正整数数组。更具体地说，Vasya 称一个数组 $a = \{a_1, a_2, \ldots, a_n\}$ 为**好数组**，当且仅当对于每个 $i$ 从 $1$ 到 $n-1$，$a_i$ 能被 $a_{i+1}$ 整除。

请你帮助他计算长度为 $n$，且所有元素均为不超过 $c$ 的正整数的**好数组**的数量。

## 说明/提示

本题的测试数据分为 7 组。只有在通过某一组的所有测试点以及所有必需的前置组后，才能获得该组的分数。

**离线评测**表示该组的评测结果将在比赛结束后公布。

| 组别 | 分值 | 附加限制 | $n$ | $c$ | 子任务依赖 | 备注 |
|:----:|:----:|:--------:|:--:|:--:|:------------:|:----:|
| 0 | 0 | - | - | - | - | 样例测试点 |
| 1 | 15 | - | $n \le 10$ | $c \le 10$ | 0 |
| 2 | 14 | - | $n \le 1000$ | $c \le 1000$ | 0, 1 |
| 3 | 12 | - | $n \le 5000$ | $c \le 5000$ | 0-2 |
| 4 | 16 | - | $n \le 100\,000$ | $c \le 100\,000$ | 0-3 |
| 5 | 14 | - | $n \le 10^6$ | $c \le 10^6$ | 0-4 |
| 6 | 15 | - | $n \le 10^7$ | $c \le 10^7$ | 0-5 |
| 7 | 14 | - | - | - | 0-6 | **离线评测** |

## 样例 #1

### 输入

```
3 3```

### 输出

```
7```

## 样例 #2

### 输入

```
2 6```

### 输出

```
14```

# 题解

## 作者：0Io_oI0 (赞：16)

# 我的解法

这道题目的时间限制为 $2$ 秒，空间限制为 $1\ \mathrm{GB}$。

注意数据范围，可知我们需要一个线性复杂度。

我们可以设 $a_n=k$，那么我们就有 $k\mid a_i\ (1\le k\le n)$，那我们不妨得到一个新的数列 $b$ 使得 $b_i=\frac{a_i}{k}$。

那么原本的问题就转化为了 $b_n=1$ 且 $b_{i+1}\mid b_i\ (1\le i<n)$ 且 $1\le b_1\le \left \lfloor  \frac{c}{k}\right \rfloor $。

那么，由于 $b_n=1$，我们只需要考虑剩下 $n-1$ 个数即可，易见 $b_1$ 为 $b$ 数列中其它所有数的倍数，我们不妨考虑，将 $b_n$ 分解为 $n-1$ 个数的乘积。

我们假设 $\mathrm{f}(x)$ 代表将 $x$ 分解为 $n-1$ 个数的乘积的方案数。

那么，我们简化后的问题的答案就为：

$$\sum_{i=1}^{\left \lfloor \frac{c}{k} \right \rfloor }\mathrm{f}(i)$$

然后，由于我们上面的 $k$ 的范围为 $1\le k\le c$，所以最后的答案就是：

$$\sum_{i=1}^{c}\sum_{j=1}^{\left \lfloor \frac{c}{i} \right \rfloor }\mathrm{f}(j)$$

那么问题就变成了，用线性复杂度求出 $\mathrm{f}(x)$ 的大小，把这个问题解决了，其它就都好办了。

我们考虑分解 $x$：

$$x=\prod_{i=1}^{m}p_i^{\alpha_i}$$

那么，我们使用插板法即可得到：

$$\mathrm{f}(x)=\prod_{j}\begin{pmatrix}
\alpha_j+n-2 \\n-2

\end{pmatrix}$$

然后，我们应该时可以证明 $\mathrm{f}(x)$ 为积性函数的。

具体的，我们需要证明当 $\gcd(a,b)=1$ 时，$\mathrm{f}(a\times b)=\mathrm{f}(a)\times \mathrm{f}(b)$。

我们考虑 $\mathrm{f}(a\times b)$ 这个函数的值为 $\prod_{i=1}^{n-1}c_i=a\times b$ 的 $k$ 元组 $(c_1,c_2,\dots,c_{n-1})$ 的数量。

由于 $\gcd(a,b)=1$ 所以我们可以唯一分解 $c_i=d_i\times e_i$，并且 $d_i\mid a,e_i\mid b$ 且 $\gcd(d_i,e_i)=1$，则：

$$\prod_{i=1}^{n-1}c_i=\prod_{i=1}^{n-1}(d_i\times e_i)=\left(\prod_{i=1}^{n-1}d_i\right)\times \left(\prod_{i=1}^{n-1}e_i\right)=a\times b$$

接下来，我们只需要证明 $\prod_{i=1}^{n-1}d_i=a,\prod_{i=1}^{n-1}e_i=b$ 即可。

我们取任意质数 $p$：

- 若 $p\mid a$，则 $p\nmid b$，此时 $v_p(a\times b)=v_p(a)+v_p(b)=v_p(a)$，又因为 $v_p(c_i)=v_p(d_i)+v_p(e_i)$，但是 $e_i\mid b$ 所以 $v_p(e_i)=0$，所以 $v_p(c_i)=v_p(d_i)$，因此：
$$v_p\left(\prod_{i=1}^{n-1}d_i\right)=\sum_{i=1}^{n-1}v_p(d_i)=\sum_{i=1}^{n-1}v_p(c_i)=v_p(ab)=v_p(a)$$
- 若 $p\mid b$，与上面同理可得 $v_p\left(\prod_{i=1}^{n-1}e_i\right)=v_p(b)$。
- 若 $p\nmid a\times b$，那么 $v_p\left(\prod_{i=1}^{n-1}d_i\right)=0=v_p(a),v_p\left(\prod_{i=1}^{n-1}e_i\right)=0=v_p(b)$。

所以，对于所有的质数 $p$，都有 $v_p\left(\prod_{i=1}^{n-1}d_i\right)=v_p(a)$ 和 $v_p\left(\prod_{i=1}^{n-1}e_i\right)=v_p(b)$，所以 $\prod_{i=1}^{n-1}d_i=a,\prod_{i=1}^{n-1}e_i=b$。

然后，这道题目就好做了，我们考虑使用线性筛求 $\mathrm{f}(x)$，我们考虑两种情况当前的数为 $i$，质数为 $p_i$。

若 $p_i\mid i$，则我们推一下式子，就是我们设 $i=p_i^k\times m$ 那么现在的 $i\times p_i=p_i^{k+1}\times m$，我们用我们上面的表达式写出来，也就是 $\mathrm{f}(i)=\begin{pmatrix}k+n-2\\n-2\end{pmatrix}\times \mathrm{g}_{m},\mathrm{f}(i\times p_i)=\begin{pmatrix}k+n-1\\n-2\end{pmatrix}\times \mathrm{g}_{m}$，我们那么我们将这两个式子做比，就能得到：
$$\frac{\mathrm{f}(i\times p_i)}{\mathrm{f}(i)}=\frac{\begin{pmatrix}k+n-1\\n-2\end{pmatrix}}{\begin{pmatrix}k+n-2\\n-2\end{pmatrix}}=\frac{k+n-1}{k+1}$$
所以，我们可以得到 $\mathrm{f}(i\times p_i)=\mathrm{f}(i)\times\frac{k+n-1}{k+1}$，这里我们用乘法逆元做就可以了。

第二种情况就是，若 $p_i\mid i$ 那么，由于 $\mathrm{f}(x)$ 为积性函数，所以 $\mathrm{f}(i\times p_i)=\mathrm{f}(i)\times \mathrm{f}(p_i)$。

然后，这道题目就基本做完了，我们只需要再加一点细节就够了。

# 关于积性函数证明中的解释

我们的证明过程中出现了一种符号，叫做 **$p$ 进赋值**，它的定义为 $v_p(x)=\max\left\{k\in \mathbb{N}_0\ |\ p^k\mid x \right\}$，其中 $\mathbb{N}_0$ 代表非负整数集。

它有一个性质：

- 若 $p\nmid x$，则 $v_p(x)=0$。
- 对于任意正整数 $a,b$ 和质数 $p$ 有 $v_p(a\times b)=v_p(a)+v_p(b)$。

还有一些性质，就不一一列举了，我们的证明中用到了如上两个性质。

# 参考代码

```cpp
#include<bits/stdc++.h>
#define I using
#define AK namespace
#define IOI std
#define i_ak return
#define ioi  0
#define i_will signed
#define ak main
#define IMO ()
#define double long double
#define R register
#define fi first
#define se second
#define mem memset
#define rep(a,b,c) for(int a=b;a<=c;++a)
#define per(a,b,c) for(int a=b;a>=c;--a)
#define pb push_back
#define sort stable_sort
#define con continue
#define br break
#define Int Integer
I AK IOI;
class Integer{private:std::string value;public:Integer(void) = default;Integer(const int& x){value = std::to_string(x);}Integer(int&& x){value = std::to_string(x);x = 0;}Integer(const Integer& x){value = x.value;}Integer(Integer&& x) noexcept{if (&x != this){value = x.value;x.value = "";}}Integer(const std::string& x){value = x;}Integer(std::string&& x) noexcept{if (&x != &(this->value)){value = x;x = "";}}void operator=(const Integer& x){value = x.value;}void operator=(Integer&& x) noexcept{if (&x != this){value = x.value;x.value = "";}}const Integer operator+(const Integer& x) const{Integer all;all.value.resize(value.size() >= x.value.size() ? value.size() + 1 : x.value.size() + 1);int a = 0;bool more = false;while (a < (value.size() <= x.value.size() ? value.size() : x.value.size())){all.value[all.value.size() - a - 1] = (value[value.size() - a - 1] - '0') + (x.value[x.value.size() - a - 1] - '0') + (int)more + '0';more = false;if (all.value[all.value.size() - a - 1] > '9'){all.value[all.value.size() - a - 1] -= 10;more = true;}a++;}while (a < value.size()){all.value[all.value.size() - a - 1] = (value[value.size() - a - 1] - '0') + (int)more + '0';more = false;if (all.value[all.value.size() - a - 1] > '9'){all.value[all.value.size() - a - 1] = all.value[all.value.size() - a - 1] - 10;more = true;}a++;}while (a < x.value.size()){all.value[all.value.size() - a - 1] = (x.value[x.value.size() - a - 1] - '0') + (int)more + '0';more = false;if (all.value[all.value.size() - a - 1] > '9'){all.value[all.value.size() - a - 1] = all.value[all.value.size() - a - 1] - 10;more = true;}a++;}if (more){all.value[0] = '1';}else{all.value.erase(all.value.begin());}return all;}void operator+=(const Integer& x){value = operator+(x).value;}void operator++(){value=operator+(1).value;}const Integer operator-(const Integer& x) const{Integer all;all.value.resize(value.size());int a = 0;bool less = false;while (a < (value.size() <= x.value.size() ? value.size() : x.value.size())){all.value[all.value.size() - a - 1] = (value[value.size() - a - 1] - '0') - (x.value[x.value.size() - a - 1] - '0') - (int)less + '0';less = false;if (all.value[all.value.size() - a - 1] < '0'){all.value[all.value.size() - a - 1] += 10;less = true;}a++;}while (a < value.size()){all.value[all.value.size() - a - 1] = (value[value.size() - a - 1] - '0') - (int)less + '0';less = false;if (all.value[all.value.size() - a - 1] < '0'){all.value[all.value.size() - a - 1] += 10;less = true;}a++;}while (all.value.size() > 1 && *all.value.begin() == '0'){all.value.erase(all.value.begin());}if (all.value.empty()){return (Integer)0;}else{return all;}}void operator-=(const Integer& x){value = operator-(x).value;}void operator--(){value=operator-(1).value;}const Integer operator*(const Integer& x) const{if (value == "0" || x.value == "0"){return (Integer)0;}Integer all;all.value.resize(value.size() + x.value.size(), '0');for (int a = value.size() - 1; a >= 0; a--){int more = 0;for (int b = x.value.size() - 1; b >= 0; b--){int total = (value[a] - '0') * (x.value[b] - '0') + (all.value[a + b + 1] - '0') + more;all.value[a + b + 1] = (total % 10) + '0';more = total / 10;}if (more){all.value[a] = (more + '0');}}while (!all.value.empty() && *all.value.begin() == '0'){all.value.erase(all.value.begin());}if (all.value.empty()){return (Integer)0;}else{return all;}}void operator*=(const Integer& x){value = operator*(x).value;}const Integer operator/(const Integer& x) const{Integer last = 0;std::string total = "";for (int a = 0; a < value.size(); a++){last = last * (Integer)10 + (Integer)(value[a] - '0');int count = 0;while (x * (Integer)count <= last){count++;}total += count - 1 + '0';last -= x * (Integer)(count - 1);}while (total.size() > 1 && *total.begin() == '0'){total.erase(total.begin());}return (Integer)total;}void operator/=(const Integer& x){value = operator/(x).value;}const Integer operator%(const Integer& x)const{Integer last = 0;std::string total = "";for (int a = 0; a < value.size(); a++){last = last * (Integer)10 + (Integer)(value[a] - '0');int count = 0;while (x * (Integer)count <= last){count++;}total += count - 1 + '0';last -= x * (Integer)(count - 1);}while (total.size() > 1 && *total.begin() == '0'){total.erase(total.begin());}return last;}void operator%=(const Integer& x){value = operator%(x).value;}bool operator<(const Integer& x) const{if (value.size() < x.value.size()){return true;}else if (value.size() > x.value.size()){return false;}else{return value < x.value;}}bool operator>(const Integer& x) const{if (value.size() > x.value.size()){return true;}else if (value.size() < x.value.size()){return false;}else{return value > x.value;}}bool operator<=(const Integer& x) const{if (value.size() < x.value.size()){return true;}else if (value.size() > x.value.size()){return false;}else{return value <= x.value;}}bool operator>=(const Integer& x) const{if (value.size() > x.value.size()){return true;}else if (value.size() < x.value.size()){return false;}else{return value >= x.value;}}bool operator==(const Integer& x) const{if (value.size() != x.value.size()){return false;}else{return value == x.value;}}bool operator!=(const Integer& x) const{if (value.size() != x.value.size()){return true;}else{return value != x.value;}}operator int(void) const{return std::stoi(value);}friend std::istream& operator>>(std::istream& stream, Integer& x){stream >> x.value;return stream;}friend std::ostream& operator<<(std::ostream& stream, const Integer& x){stream << x.value;return stream;}~Integer(void) = default;};namespace fastIO{char *p1,*p2,buf[100000];
	#define nc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
	inline void read(int&n){int x=0,f=1;char ch=nc();while(ch<48||ch>57){if(ch=='-'){f=-1;}ch=nc();}while(ch>=48&&ch<=57){x=(x<<3)+(x<<1)+(ch^48),ch=nc();}n=x*f;}inline void read(string&s){s="";char ch=nc();while(ch==' '||ch=='\n'){ch=nc();}while(ch!=' '&&ch!='\n'){s+=ch,ch=nc();}}inline void read(char&ch){ch=nc();while(ch==' '||ch=='\n'){ch=nc();}}inline void write(int x){if(x<0){putchar('-'),x=-x;}if(x>9){write(x/10);}putchar(x%10+'0');return;}inline void write(const string&s){for(R int i=0;i<(int)s.size();i++){putchar(s[i]);}}inline void write(const char&c){putchar(c);}
}using namespace fastIO;
const int INF=0x3f3f3f3f;
inline int gcd(int a,int b){if(a==0)return b;if(b==0)return a;int k;for(k=0;((a|b)&1)==0;k++){a>>=1;b>>=1;}while((a&1)==0)a>>=1;do{while((b&1)==0)b>>=1;if(a>b)swap(a,b);b=(b-a);}while(b!=0);return a<<k;}inline int lcm(const int&a,const int&b){return a*b/gcd(a,b);}
inline int pow(int a,int b){int res=1;while(b){if(b&1)res*=a;a*=a;b>>=1;}return res;}
inline int powmod(int a,int b,const int&mod){int res=1;a%=mod;while(b){if(b&1)res=res*a%mod;a=a*a%mod;b>>=1;}return res%mod;}
inline int lowbit(int x){return x&(-x);}
const int mod=998244353,N=50000005;
int inv[32],f[N],F[N],cnt[N],primes[N/10],n,c,tot,ans;
bool not_prime[N];
i_will ak IMO{
    cin>>n>>c;
    inv[1]=1;
    rep(i,2,31)inv[i]=(long long)(mod-mod/i)*inv[mod%i]%mod;
    f[1]=1;
    not_prime[1]=1;
    rep(i,2,c){
        if(!not_prime[i]){
            primes[++tot]=i;
            f[i]=n-1;
            cnt[i]=1;
        }
        for(int j=1;j<=tot&&(long long)i*primes[j]<=c;j++){
            int p=primes[j];
            not_prime[i*p]=1;
            if(i%p==0){
                cnt[i*p]=cnt[i]+1;
                int k=cnt[i];
                f[i*p]=(long long)f[i]*(k+n-1)%mod;
                f[i*p]=(long long)f[i*p]*inv[k+1]%mod;
                br;
            }
			else{
                cnt[i*p]=1;
                f[i*p]=(long long)f[i]*f[p]%mod;
            }
        }
    }
    rep(i,1,c)F[i]=(F[i-1]+f[i])%mod;
    rep(i,1,c)ans=(ans+F[c/i])%mod;
    cout<<ans;
    i_ak ioi;
}
```

亲测可过，请勿抄袭。

---

## 作者：0Io_oI0 (赞：5)

众所周知这道题目卡空间。

我们注意到这篇题解：[link](https://www.luogu.com.cn/article/c7ev0iwq)。

为什么这篇题解的代码为什么能过呢，其实这篇代码是有优化的，我们一起来看一看。

首先，我们发现这里的所有数都是 `int` 类型，众所周知 `long long` 的空间很高，所以为了节省空间，我们可以在可能超过 `int` 范围的时候强转为 `long long` 类型即可。

其次，我们观察到 `inv` 数组只开了 $32$ 这是因为我们注意到 `cnt` 数组是用来求一个数里面有几个 $p$ 的，而这个值不超过 `int` 而 `int` 的最大值就是 $2^{32}-1$ 所以我们只需要开成 $32$ 即可。

我们还可以看到 `primes` 数组的大小为 $\frac{N}{10}$ 这是因为其实在 $N$ 以内的质数不会太多，这样同样节省了空间。

但是其实我们可以继续优化空间，这是题解中并没有做到的，比如我们可以不开 `F` 数组，而是在 `f` 数组的基础上直接求前缀和，这样也可以节省很多空间。

---

## 作者：buowen123 (赞：3)

~~唐题，5min 秒了。~~

下文统一设 $p$ 表示质数。设 $a_i$ 中 $p$ 的幂次为 $b_i$，应当有 $b_i \ge b_{i+1} \ge 0$。不妨设 $b_1=m$。

令 $b_i \gets b_i+n-i+1$，则 $b_1=m+n > b_2 > \dots > b_n > 0$，方案数为 $\binom{m+n-1}{n-1}$。这样只需对于每个 $a_1=x$，计算

$$\prod_{p^\alpha||x}\binom{\alpha+n-1}{n-1}$$

这显然是积性的，那么线性筛即可。

我们设 $f_x$ 表示上式的值，并维护 $v_x$ 表示 $x$ 的最小质因子的幂次。在线性筛中作转移 $i \to i\times p$：
- 初始状态：$v_1=0,f_1=1,v_p=1,f_p=n$。
- $p\mid i$：$v_{i\times p} \gets v_i+1$，$f_{i\times p} \gets f_i\times \dfrac{v_i+n}{v_i+1}$。
- $p\nmid i$：$v_{i\times p} \gets 1$，$f_{i\times p} \gets f_i\times f_p$。

答案为 $\sum f_i$，时间复杂度 $O(c)$。

------

卡空间技巧是搞清楚每个数组开多少，怎么开：
- $1 \sim 5\times 10^7$ 中只有不超过 $3.002 \times 10^6$ 个质数。
- `isp` 数组可以用 `bitset` 代替。
- $f,v$ 数组只需要 $5 \times 10^7$ 个 `int`，使用时强转为 `long long` 即可。

除去最优解第一位的神秘 BFS 做法，直接拿下最优解第二（~~我不是大常数选手吗~~）。

:::info[代码]{open}
```cpp
const int maxn=5e7+5,maxm=3001134+5,maxk=1e5+5,mod=998244353;
int n,c,k=100,p[maxm],f[maxn],cnt,v[maxn];
bitset<maxn>b;
ll res,fc[maxk],ifc[maxk],inv[maxk];
ll qpow(ll a,ll b){
	ll res=1;
	while(b){
		if(b&1) res=res*a%mod;
		a=a*a%mod,b>>=1;
	}
	return res;
}
void Main(){
	cin>>n>>c;
	fc[0]=ifc[0]=f[1]=1;
	for(int i=1;i<=k;i++){
		fc[i]=fc[i-1]*i%mod;
	}
	ifc[k]=qpow(fc[k],mod-2);
	for(int i=k-1;i>=1;i--){
		ifc[i]=ifc[i+1]*(i+1)%mod;
		inv[i]=ifc[i]*fc[i-1]%mod;
	}
	for(int i=2;i<=c;i++){
		if(!b[i]){
			p[++cnt]=i;
			f[i]=n,v[i]=1;
		}
		for(int j=1;j<=cnt&&i*p[j]<=c;j++){
			b[i*p[j]]=1;
			f[i*p[j]]=1ll*f[i]*f[p[j]]%mod;
			v[i*p[j]]=1;
			if(i%p[j]==0){
				v[i*p[j]]=v[i]+1;
				f[i*p[j]]=1ll*f[i]*(v[i]+n)%mod*inv[v[i]+1]%mod;
				break;
			}
		}
	}
	for(int i=1;i<=c;i++){
		res=(res+f[i])%mod;
	}
	cout<<res<<'\n';
}
```
:::

---

## 作者：qwqerty (赞：1)

首先把题略改一下可以变为求有多少个数组 $a$ 满足 $\prod\limits_{i=1}^n a_i=x$ 且 $x\le c$。  
改为加法是简单的，只需插板即可。在这里为乘法，可以非常自然地考虑到分解质因数。  
对于每个质因数，都可以将指数设为看做加法操作使用插板法。注意会有 $0$ 的情况。对于指数为 $cnt$ 的情况共有 $\binom{cnt+n-1}{n-1}$ 种。  
由于该结果对于每个质因子独立，故该函数是积性的。由于 $n$ 只开到了 $5\times 10^7$，线性筛筛出暴力求和就能做了。  
卡空间技巧：
- 全开 `int`，取模时在强转为 `long long`。
- 由于组合的两个参数相差极大，一个为 $O(\log n)$ 级别一个为 $O(n)$ 级别的。故计算预处理组合数时可以分两部分计算。

[提交记录](https://www.luogu.com.cn/record/228047272)。

---

## 作者：Polarisx (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P13541)。

建议降蓝。

## 思路

不妨枚举第一个数填什么（假设为 $x$），接下来填的数全是它的因子，考虑在这 $n$ 个位置中，每个位置相对上一个位置下降多少，不难发现每个质因子的贡献是独立的，对每个 $x$ 的质因子 $p$ 讨论，假设 $p$ 在 $x$ 的幂次为 $k$，那么它的贡献就是 $\binom{n-1+k}{k}$，相当于在 $n$ 个盒子里放 $k$ 个 $p$，最后会降到 $1$，这个 $1$ 可以不用管，直接剔除，直接埃氏筛可以做到 $\mathcal O(n\ln \ln n)$。

由于质因子贡献是独立的，假设 $f(c)$ 表示第一个数填 $c$ 的方案数，那么 $f$ 是积性函数，有转移 $f(i\times p^c)\gets f(i)\times f(p^c),(i\bot p)$。

最后要求的就是该积性函数的前缀和，也可以通过 min25 筛做到更优的时间复杂度。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int Maxn=5e7+100,N=5e7+30;
const int Mod=998244353;
int n,c;
bitset<Maxn>isp;

int ans;
int fac[Maxn],ifac[Maxn];
int val[Maxn],pk[Maxn],pm[Maxn];
int prm[Maxn/20],tot;

inline ll ksm(ll a,int b,int mod){
    ll z=1;
    while(b){
        if(b&1) z=z*a%mod;
        a=a*a%mod; b>>=1;
    }
    return z;
}
inline int binom(int x,int y){
    if(y>x or x<0) return 0;
    return 1ll*fac[x]*ifac[y]%Mod*ifac[x-y]%Mod;
}

int main(){
    scanf("%d%d",&n,&c);

    fac[0]=1;
    for(int i=1;i<=N;i++) fac[i]=1ll*i*fac[i-1]%Mod,val[i]=1;
    ifac[N]=ksm(fac[N],Mod-2,Mod);
    for(int i=N-1;~i;i--) ifac[i]=1ll*ifac[i+1]*(i+1)%Mod;

    val[1]=1; ans=1;
    for(int i=2;i<=c;i++){
        if(!isp.test(i)) prm[++tot]=i,val[i]=n,pk[i]=i,pm[i]=1;
        for(int k=1;k<=tot;k++){
            int j=prm[k];
            const int t=i*j; if(t>c) break; isp.set(t); 
            if(!(i%j)){
                pk[t]=pk[i]*j; pm[t]=pm[i]+1;
                if(pk[t]==t) val[t]=binom(pm[t]+n-1,n-1);
                else val[t]=1ll*val[t/pk[t]]*val[pk[t]]%Mod;
                break;
            }
            pk[t]=j,pm[t]=1;
            val[t]=1ll*val[i]*val[j]%Mod;
        }
        ans+=val[i];
        if(ans>Mod) ans-=Mod;
    }

    printf("%d",ans);
    
    return 0;
}
```

---

