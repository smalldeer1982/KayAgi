# [ABC158E] Divisible Substring

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc158/tasks/abc158_e

高橋君は `0` から `9` までの数字から成る長さ $ N $ の文字列 $ S $ を持っています。

素数 $ P $ が好きな高橋君は、$ S $ の空でない連続する部分文字列 $ N\ \times\ (N\ +\ 1)\ /\ 2 $ 個のうち、十進表記の整数と見なした際に $ P $ で割り切れるものの個数を知りたくなりました。

ただし部分文字列は先頭が `0` であっても良いものとし、文字列として等しい場合や、整数と見なした際に等しい場合も、部分文字列の $ S $ 内の位置で区別します。

高橋君のためにこの個数を計算してください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ S $ は数字から成る
- $ |S|\ =\ N $
- $ 2\ \leq\ P\ \leq\ 10000 $
- $ P $ は素数である

### Sample Explanation 1

$ S $ = `3543` です。$ S $ の空でない連続する部分文字列は次の $ 10 $ 個があります。 - `3` は $ 3 $ で割り切れる。 - `35` は $ 3 $ で割り切れない。 - `354` は $ 3 $ で割り切れる。 - `3543` は $ 3 $ で割り切れる。 - `5` は $ 3 $ で割り切れない。 - `54` は $ 3 $ で割り切れる。 - `543` は $ 3 $ で割り切れる。 - `4` は $ 3 $ で割り切れない。 - `43` は $ 3 $ で割り切れない。 - `3` は $ 3 $ で割り切れる。 このうち $ 3 $ で割り切れるものは $ 6 $ 個であるので、$ 6 $ を出力してください。

### Sample Explanation 2

$ S $ = `2020` です。$ S $ の空でない連続する部分文字列は $ 10 $ 個ありますが、その全てが $ 2 $ で割り切れるので $ 10 $ を出力してください。 先頭が `0` である部分文字列も許容されることに注意してください。

## 样例 #1

### 输入

```
4 3
3543```

### 输出

```
6```

## 样例 #2

### 输入

```
4 2
2020```

### 输出

```
10```

## 样例 #3

### 输入

```
20 11
33883322005544116655```

### 输出

```
68```

# 题解

## 作者：きりと (赞：6)

**[题目传送门](https://www.luogu.com.cn/problem/AT5361)**

### 题目大意

见中文翻译。

### 解题思路

思维题，关键点在于要想出线性求字串数量的方法。

先给出结论：在大多数情况下，如果两个字串所对应的数字 $\bmod$ $p$ 所得的余数相等，且一个串是另一个的末尾某一段，则他们相减后得到的串符合要求。

证明：设第一个数为 $a+x$ ，第二个数为 $b+x$ ， $a$ ，$b$ 均为 $p$ 的倍数，则在十进制下两数相减得到的差值也为 $p$ 的倍数，然后此差值可以写成 $c+10^x$，当 $10$ 的质因子中不含 $p$ 时，结论成立。

解决方法：当 $p=2$ 或 $p=5$ 时特判，另外情况可以参见代码内的注释。

### Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10,M=1e4+10;
char s[N];
int cnt[M];      //cnt[i]表示余数为i的数在之前出现了几次
signed main()
{
    int n,p,ans=0;
    cnt[0]=1;
    cin>>n>>p;
    cin>>s+1;
    if(p==2||p==5)
    {
        for(int i=1;i<=n;i++)
        {
            if((s[i]-'0')%p==0)
            {
                ans+=i;    //2，5的倍数都是只看个位，所以个位能被整除就可以+i
            }
        }
    }
    else
    {
        int t=1,r=0;
        for(int i=n;i>=1;i--)
        {
            r+=(s[i]-'0')*t%p;      //r记录当前位置所构成的数字%p的余数
            r%=p;
            ans+=cnt[r];      //更新答案
            cnt[r]++;
            t*=10;         //t记录10的x次方
            t%=p;
        }
    }
    cout<<ans<<endl;
    return 0;
}

```



---

## 作者：w33z8kqrqk8zzzx33 (赞：3)

首先，如果 $P\in\{2,5\}$，那必须要特判。在这个情况，可以找那些位置包含一个可以除 $P$ 的数，然后直接统计答案。

现在，我们有 $(10,P)=1$。假设 $f(x)=$ 一个 $N$-位数字使得它的前 $x$ 位相当于 $S$ 的前 $x$ 位，然后后面位全是 $0$。那就可以得到：

 $$S[l:r]\equiv0\pmod P\iff f(r)-f(l-1)\equiv0\pmod P$$

（注意数字表达是 $S[|S|]S[|S|-1]\dots S[3]S[2]S[1]$）

为什么呢？第一，$S[l:N]\cdot10^{l-1}=f(l)$，所以 $S[l:r]\cdot10^{l-1}=f(r)-f(l-1)$。但是如果 $(10,P)=1$，那把 $S[l:r]$ 的值在乘一个 $10^{l-1}$ 不会变 $S[l:r]\equiv0\pmod P$ 的正确或者错误性。

这样，就直接用一个数组统计所有 $f(x)\pmod P$ 的值，然后把一样摸结果的前面的 $f$ 值个数计入到答案里。

代码：

```cpp
// writer: w33z8kqrqk8zzzx33
#include <bits/stdc++.h>
using namespace std;
 
#define iter(i, a, b) for(int i=(a); i<(b); i++)
#define rep(i, a) iter(i, 0, a)
#define rep1(i, a) iter(i, 1, (a)+1)
#define log(a) cerr<<"\033[32m[DEBUG] "<<#a<<'='<<(a)<<" @ line "<<__LINE__<<"\033[0m"<<endl
#define all(a) a.begin(), a.end()
#define fi first
#define se second
#define pb push_back
#define mp make_pair

using ll=long long;
using pii=pair<int, int>;
//#define int ll
int MOD = 1000000007;

int mc[10004];

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int N, P; cin >> N >> P;
    string S; cin >> S;
    if(P == 2 || P == 5) {
        ll ans = 0;
        rep(i, N) if((S[i]-'0')%P == 0) ans += (i+1);
        cout << ans << endl;
        return 0;
    } else {
        int ps=0,c=1;
        ll ans=0;
        mc[0]++;
        reverse(all(S));
        rep(i,N) {
            ps=(ps+c*(S[i]-'0'))%P,c=c*10%P;
            ans+=mc[ps];
            mc[ps]++;
        }
        cout << ans << endl;
    }
}

```

---

## 作者：WaterSun (赞：2)

[更好的阅读体验](https://watersun.top/[%E9%A2%98%E8%A7%A3]AT_abc158_e%20[ABC158E]%20Divisible%20Substring/)

# 思路

首先发现一个事情，任意一个子串都可以由 $s$ 的某一个后缀的后面删除一些字符得到。

因此假如 $s$ 的某一个后缀的值为 $x$，那么我们可以减去后面的我们不用的数字 $a$，然后除以 $10$ 的若干次幂得到，即 $\frac{x - a}{10^n}$。

于是得到：

$$
\frac{x - a}{10^n} \equiv 0 \pmod p
$$

可以推出：

$$
x \equiv a \pmod p
$$

因此考虑处理后缀模 $p$ 的结果，同时用桶存起来即可。

注意到有可能 $a$ 比 $x$ 大的情况，因此需要把这种情况删掉；同时注意到当 $p = 2/5$ 时，$\frac{x - a}{10^n} \bmod p$ 不存在（因为 $10$ 与 $p$ 不互质了），需要特殊处理。

# Code

```cpp
#include <bits/stdc++.h>
#define re register
#define int long long

using namespace std;

const int N = 2e5 + 10;
int n,p,ans;
char s[N];
vector<int> v[N];

inline int read(){
    int r = 0,w = 1;
    char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        r = (r << 3) + (r << 1) + (c ^ 48);
        c = getchar();
    }
    return r * w;
}

inline void solve1(){
	for (re int i = 1;i <= n;i++){
		if ((s[i] - '0') % p == 0) ans += i;
	}
}

inline void solve2(){
    for (re int i = n,x = 0,mul = 1;i;i--,mul = mul * 10 % p){
        x = (x + mul * (s[i] - '0')) % p;
        if (!x) ans++;
        v[x].push_back(i);
    }
    for (re int i = 0;i < p;i++) sort(v[i].begin(),v[i].end());
    for (re int i = n,x = 0,mul = 1;i;i--,mul = mul * 10 % p){
        x = (x + mul * (s[i] - '0')) % p;
        ans += (upper_bound(v[x].begin(),v[x].end(),i) - v[x].begin() - 1);
    }
}

signed main(){
    n = read(),p = read(),scanf("%s",s + 1);
    if (p == 2 || p == 5) solve1();
	else solve2(); 
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：Acfboy (赞：2)

其实感觉挺好想的。

随便来个样例，把所有的列出来。

```plain
3
35
354
3543
 5
 54 
 543
  43
   3
```

中间显然有很多重复，那是不是只要维护一组(指最开始一个起点)就可以了呢？

若只维护第一组，那么每次每个要减去的数不一样，很难统一维护。所以从后面开始。

```plain
   3
  43
 543
3543
  4
 54
354
 5
35
3
```

这样对于每一组，就是把组中第一个数字去掉，然后剩下的每一个减去最后一个位再除以十就可以了。

因为对于所有数的处理都一样，所以直接把取模完每一个答案有几个给记下来，然后维护一个 $k$, 满足经过了哪些操作原来答案为 $k$ 的答案会变为 $0$, 然后加上这个就可以了。

具体地，比如有 $5$ 个数，我现在要求倒数第二组的答案，则 $k$ 需要满足($inv$ 是 $10$ 的逆元)

$$
((((((k-s_5)\times inv) - s_4) \times inv) - s_3) \times inv \equiv 0 \pmod p
$$

化简一下就是每次 $k$ 加上 $s_i \times 10^{n-i}$。

然后你就可以交了。

代码

```cpp
#include <cstdio>
#define int long long
int n, m, p, ans, f[10005];
char s[200005];
signed main() {
    scanf("%lld%lld", &n, &p);
    scanf("%s", s + 1);
    for (int i = n, pow = 1, now = 0; i >= 1; i--, pow = pow * 10 % p) {
        now = (now + (s[i] - '0' + p) * pow % p) % p;
        f[now]++;
    }
    for (int i = n, pow = 1, now = 0; i >= 1; i--, pow = pow * 10 % p) {
        ans = ans + f[now];
        now = (now + (s[i] - '0') * pow % p) % p;
        f[now]--;
    }
    printf("%lld", ans);
}

```

交了以后会发现：WA 了

细细一想，发现若 $p$ 是 $10$ 的约数时连个逆元都没有，你乘个锤子！

所以特判一下 $p$ 是 $2$ 和 $5$ 的情况。

```cpp
    if (p == 2 || p == 5) {
        for (int i = 1; i <= n; i++)
            if ((s[i] - '0') % p == 0)
                ans += i;
        printf("%lld", ans);
        return 0;
    }
```

现在真的过了。这错误我调了 $40$ 分钟。

---

## 作者：CQ_Bob (赞：1)

## 分析

6，这题好。

很显然我们倒着来表示整数会比正着来简单。对于下标 $i$，$S_i \sim S_{|S|}$ 这个后缀表示的整数可以写成：$f_i=\sum\limits_{j=i}^{|S|}S_j \times 10^{n-i}$。

子串，其实就是一个后缀在减去这个后缀的一个后缀。区间 $[i,j]$ 表示的整数可以写成：$g_{i,j}=\frac{f_i-f_{j+1}}{10^{n-j}}$。然后问题就变成了 $g_{i,j}$ 是 $p$ 的倍数的 $(i,j)$ 数量。

由于 $10=2 \times 5$，而 $p=2,5$ 的时候可以 $O(|S|)$ 求答案。所以在 $p\ne 2,5$ 时，分母是没有任何贡献的。于是问题变成 $g_{i,j}=f_i-f_{j+1}$ 是 $p$ 的倍数的 $(i,j)$ 数量。

记录 $cnt_i$ 表示 $f_k \bmod p =i$ 的数量。根据 $(f_i-f_{j+1}) \bmod p=0$，有 $f_i\equiv f_{j+1} \pmod p$。所以以位置 $i$ 为整数开头的答案就是 $ans_i=cnt_{f_i}$，然后 $cnt_{f_i}$ 增加 $1$。最后的答案就是 $\sum \limits_{i=1}^{|S|}ans_i$。复杂度 $O(|S|)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline
#define pii pair<int,int>
#define x first
#define y second
#define gc getchar()
#define rd read()
#define debug() puts("------------")

namespace yzqwq{
	il int read(){
		int x=0,f=1;char ch=gc;
		while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=gc;}
		while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=gc;
		return x*f;
	}
	il int qmi(int a,int b,int p){
		int ans=1;
		while(b){
			if(b&1) ans=ans*a%p;
			a=a*a%p,b>>=1;
		}
		return ans;
	}
	il auto max(auto a,auto b){return (a>b?a:b);}
	il auto min(auto a,auto b){return (a<b?a:b);}
	il int gcd(int a,int b){
		if(!b) return a;
		return gcd(b,a%b);
	}
	il int lcm(int a,int b){
		return a/gcd(a,b)*b;
	}
	il void exgcd(int a,int b,int &x,int &y){
		if(!b) return x=1,y=0,void(0);
		exgcd(b,a%b,x,y);
		int t=x;
		x=y,y=t-a/b*x;
		return ;
	}
	mt19937 rnd(time(0));
}
using namespace yzqwq;

const int N=4e5+10;
int n,p,ans;
char s[N];
int f[N],_10[N];
int cnt[N];

il void solve2(){
	for(re int i=1;i<=n;++i)
		if((s[i]-'0')%2==0) ans+=i;
	printf("%lld\n",ans);
	return ;
}
il void solve3(){
	for(re int i=1;i<=n;++i){
		if((s[i]-'0')%5==0) ans+=i;
	}
	printf("%lld\n",ans);
	return ;	
}
il void solve(){
	n=rd,p=rd,scanf("%s",s+1);
	
	if(p==2) return solve2(),void(0);
	else if(p==5) return solve3(),void(0);
	
	_10[0]=cnt[0]=1;for(re int i=1;i<=n;++i) _10[i]=_10[i-1]*10%p;
	for(re int i=n;i>=1;--i)
		f[i]=(_10[n-i]*(s[i]-'0')%p+f[i+1])%p,
		ans+=(cnt[f[i]]++);
	printf("%lld\n",ans);
	return ;
}

signed main(){
	int t=1;while(t--)
	solve();
	return 0;
}
```


---

## 作者：Wf_yjqd (赞：1)

水蓝。

------------

记 $[i,n]$ 一个后缀变成数字为 $s_i$，则 $[l,r]$ 变成数字可表示为 $\frac{s_l-s_{r+1}}{10^{n-r}}$。

题意即是求 $p|\frac{s_l-s_{r+1}}{10^{n-r}}$ 的数量。

若 $\gcd(p,10)=1$，$p|s_l-s_{r+1}$，$s_l\equiv s_{r+1}(\mod p)$。

用桶统计下每种余数的次数，简单组合统计方案。

否则 $p$ 只能取 $2,5$，统计最后一位是 $p$ 的倍数的方案即可。

------------

为啥要分两种情况呢，发现是否是 $2,5$ 的倍数只由最后一位决定，套用上面的做法所有的余数都会相同。

------------

放个代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=2e5+26;
int p,n;
ll ans,pw,s[maxn],cnt[maxn];
int main(){
	scanf("%d%d",&n,&p);
	for(int i=1;i<=n;i++)
		scanf("%1d",&s[i]);
	if(p==2||p==5){
		for(int i=1;i<=n;i++)
			if(s[i]%p==0)
				ans+=i;
		printf("%lld",ans);
		return 0;
	}
	pw=1;
	cnt[0]=1;
	for(int i=n;i>=1;i--){
		s[i]=(s[i]%p*pw%p+s[i+1]%p)%p;
		cnt[s[i]]++;
		pw=pw*10%p;
	}
	for(int i=0;i<p;i++)
		ans+=cnt[i]*(cnt[i]-1)/2;
	printf("%lld",ans);
	return 0;
} 
```


---

## 作者：Union_Find (赞：0)

注意力惊人，我们发现如果一个字串的数字是 $p$ 的倍数，那么就是 $a \equiv 0 \pmod p$。但是区间的问题不好处理，所以我们~~发扬人类智慧~~考虑转化成前缀和或后缀和。

如果使用前缀和，出现的问题就是 $s_r - s_{l - 1} \times 10^{l-1} \equiv 0 \pmod p$，但是这样子就算移项也没有很好的结构，利用不了 $p$ 为质数这一个点。所以考虑使用后缀和，就是 $\frac{s_{l} - s_{r - 1}}{10^{r-l}} \equiv 0 \pmod p$。这样子，因为除了 $p = 2$ 或 $p = 5$，其他情况下 $10$ 和 $p$ 互质，分母就没有了，就变成了 $s_l \equiv s_{r+1} \pmod p$。直接开桶维护即可。

那 $p = 2$ 或 $p = 5$ 可以直接判断个位，直接加上即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define il inline
#define ll long long
#define N 200005
il int rd(){
	int s = 0, w = 1;
	char ch = getchar();
	for (;ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') w = -1;
	for (;ch >= '0' && ch <= '9'; ch = getchar()) s = ((s << 1) + (s << 3) + ch - '0');
	return s * w;
}
int n, p, a[N], t[N];
ll ans;
char s[N];
int main(){
	n = rd(), p = rd();
	scanf ("%s", s + 1);
	if (p == 2 || p == 5){
		for (int i = 1; i <= n; i++) if ((s[i] - '0') % p == 0) ans += i;
		return 0 & printf ("%lld\n", ans); 
	}
	for (int i = n, base = 1; i >= 1; i--, base = 1ll * base * 10 % p) a[i] = (a[i + 1] + 1ll * (s[i] - '0') * base % p) % p;
	for (int i = 1; i <= n + 1; i++) ans += t[a[i]], t[a[i]]++;
	printf ("%lld\n", ans);
	return 0;
}

```

说句闲话，如果你想练莫队，可以做 [P3245 [HNOI2016] 大数](https://www.luogu.com.cn/problem/P3245) 这题，题目几乎一样，就是变成了区间查询，套一个莫队板子即可。

---

## 作者：gcx12012 (赞：0)

#### 前言
模拟赛想这题想了一个小时，还得多练。

场上想的是比较难写的分治，给大家分享一下。
#### Solution
因为是子区间计数题，所以可以自然而然地去想分治做法。

首先把一个区间 $[l,r]$ 分成 $[l,mid]$ 和 $[mid+1,r]$ 分成两段，对左区间处理后缀数，对右区间处理前缀数。

我们设某个前缀数为 $a$，某个后缀数为 $b$，后缀数 $b$ 的位数为 $k$，那么有 $10^ka+b$ 模 $\text{P}$ 为 $0$。移项一下就是：
$$
a\equiv \frac{-b}{10^k}(\text{mod P})
$$
然后这道题就做完了，时间复杂度为 $O(n \log^2 n)$。
```cpp
#include<bits/stdc++.h>
#include<cmath>
#define ll long long
#define lll __int128
#define ui unsigned int
#define ull unsigned long long
#define N 300010
#define For(i,a,b) for(ll i=a;i<=b;++i)
#define Rof(i,a,b) for(ll i=a;i>=b;--i)
#define ls x<<1 
#define rs x<<1|1
#define lson ls,l,mid
#define rson rs,mid+1,r
#define pb push_back
#define mk make_pair
#define pque priority_queue
#define pii pair<int,int>

using namespace std;
bool st;
char s[N];
ll a[N];
ll mi[N],mi2[N];
ll n,p,ans;
bool ed;

ll read(){
	ll x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
ll ksm(ll x,ll y){
	ll q=1;
	while(y){
		if(y&1) q=q*x%p;
		x=x*x%p;
		y>>=1;
	}
	return q;
}
ll mp[N];
ll now[N],b[N],cnt=0;
void sol(int l,int r){
	if(l==r){
		if(a[l]%p==0) ans++;
		return;
	}
	int mid=(l+r)>>1;
	ll pp=0,sum=0;
	now[mid+1]=0;
	cnt=0;
	for(int i=mid;i>=l;--i) now[i]=(now[i+1]+mi[pp]*a[i])%p,++pp,b[++cnt]=now[i]+1;
	pp=0;
	for(int i=mid+1;i<=r;++i){
		++pp;
		sum=(sum*10+a[i])%p;
		b[++cnt]=(p-sum)*mi2[pp]%p+1;
	}
	sort(b+1,b+cnt+1);
	cnt=unique(b+1,b+cnt+1)-b-1;
	for(int i=mid;i>=l;--i){
		now[i]=lower_bound(b+1,b+cnt+1,now[i]+1)-b;
		mp[now[i]]++;
	}
	pp=0;
	sum=0;
	for(int i=mid+1;i<=r;++i){
		++pp;
		sum=(sum*10+a[i])%p;
		ll nowp=(p-sum)*mi2[pp]%p+1;
		nowp=lower_bound(b+1,b+cnt+1,nowp)-b;
		ans+=mp[nowp];
	}
	for(int i=mid;i>=l;--i) mp[now[i]]--;
	sol(l,mid);
	sol(mid+1,r);
}

int main()
{
	//fprintf(stderr,"%.2lf",(&ed-&st)/1024.0/1024.0);
	cin>>n>>p;
	For(i,1,n) cin>>s[i];
	if(p==5 || p==2){
		For(i,1,n){
			if((s[i]-'0')%p==0) ans+=i;
		}
		cout<<ans;
		return 0;
	}
	mi[0]=mi2[0]=1;
	for(int i=1;i<=n;++i) mi[i]=mi[i-1]*10%p,mi2[i]=ksm(mi[i],p-2);
	for(int i=1;i<=n;++i) a[i]=s[i]-'0';
	sol(1,n);
	cout<<ans;
 	return 0;
}
/*

*/
```

---

## 作者：cosf (赞：0)

对于 $p=2$ 或 $p=5$，显然一个数是 $p$ 的倍数只与最后一位有关，循环一遍就做完了。

对于其他的 $p$，若 $x$ 是 $p$ 的倍数，则 $x \times 10^k$ 也一定是 $p$ 的倍数。

因此，我们可以用后缀和，判断有哪一些后缀模 $p$ 相同，这个个数便是答案。

例如样例 $1$，它的后缀和是 $3543, 543, 43, 3, 0$，模 $3$ 之后为 $0, 0, 1, 0, 0$，可以选出 $6$ 组相等的数，因此答案就是 $6$。

代码可以使用高贵的 aclib 中的 `modint` 来实现。

```cpp
#include <iostream>
#include <vector>
#include <map>
#include <atcoder/modint>
using namespace std;
using namespace atcoder;

using ll = long long;
using mint = modint;

int n, p;

string s;

int main()
{
    cin >> n >> p;
    cin >> s;
    s = " " + string(s.rbegin(), s.rend());
    if (p == 2 || p == 5)
    {
        ll res = 0;
        for (int i = 1; i <= n; i++)
        {
            if ((s[i] - '0') % p == 0)
            {
                res += n - i + 1;
            }
        }
        cout << res << endl;
        return 0;
    }
    mint::set_mod(p);
    mint m = 0, b = 1;
    map<int, int> mp;
    mp[0]++;
    ll res = 0;
    for (int i = 1; i <= n; i++)
    {
        m += b * (s[i] - '0');
        res += mp[m.val()];
        mp[m.val()]++;
        b *= 10;
    }
    cout << res << endl;
    return 0;
}

```

---

## 作者：StevenLiTheOIer (赞：0)

## 前言：
~~忆一时，悟一事。~~ 一定要特判啊！！！
## 思路：
由于 $p$ 是质数，所以当两个子串表示的数在模 $p$ 的意义下同余时，其中一个串在另一个串的尾部，这时两串对应的数相减，余数相抵消，得到的串就可以被 $p$ 整除，对答案产生 $1$ 的贡献。

所以只要记录每个余数出现的次数，线性扫一遍就可以了。

真的是这样吗？

要注意到 $p=2$ 和 $p=5$ 的情况。此时 $p$ 是 $10$ 的质因子，所以在十进制取模 $p$ 意义下的统计就会出问题，需要特判。所幸 $2$ 和 $5$ 的整除性质只看个位，所以特判的复杂度也可以接受。

细节见代码。
## Code：
```cpp
#include <bits/stdc++.h>
using namespace std;
string s;
int a[10006], b[200006]; //b[i] 表示模 p 余 i 的数的个数 
int main()
{
	int n, p;
	long long ans = 0;
	cin >> n >> p >> s;
	if (p == 2 || p == 5) //用整除性质特判 
	{
		for (int i = 0; i < n; i++)
			if ((s[i] - '0') % p == 0) ans += i + 1;
	}
	else
	{
		int cnt = 0, t = 1; //cnt 表示当前的余数，t 用来快速求出 10 的次方 
		a[0] = 1;
		for (int i = n - 1; i >= 0; i--) //从低位到高位统计余数 
		{
			cnt = (cnt + t * (s[i] - '0')) % p; //更新余数 
			ans += a[cnt]++;
			t = (t * 10) % p;
		}
	}
	cout << ans << endl;
	return 0;
}
```

---

