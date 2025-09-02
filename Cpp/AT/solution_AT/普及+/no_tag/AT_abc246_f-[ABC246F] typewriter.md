# [ABC246F] typewriter

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc246/tasks/abc246_f

$ N $ 段からなるタイプライターがあります。このうち、上から $ i $ 段目のキーでは文字列 $ S_i $ に含まれる文字が打てます。

このキーボードを使って、以下のルールで文字列をひとつ入力することを考えます。

- まず、整数 $ 1\ \le\ k\ \le\ N $ を選択する。
- その後、空文字列から始めて、上から $ k $ 段目にあるキーだけを使ってちょうど $ L $ 文字の文字列を入力する。

このルールに従って入力可能な $ L $ 文字の文字列は何通りありますか？ 答えは非常に大きくなる場合があるので $ 998244353 $ で割った余りを出力してください。

## 说明/提示

### 制約

- $ N,L $ は整数
- $ 1\ \le\ N\ \le\ 18 $
- $ 1\ \le\ L\ \le\ 10^9 $
- $ S_i $ は `abcdefghijklmnopqrstuvwxyz` の(連続とは限らない)空でない部分列

### Sample Explanation 1

入力可能な文字列は `aa`, `ab`, `ac`, `ba`, `bb`, `ca`, `cc` の $ 7 $ つです。

### Sample Explanation 3

答えを $ 998244353 $ で割った余りを出力してください。

## 样例 #1

### 输入

```
2 2
ab
ac```

### 输出

```
7```

## 样例 #2

### 输入

```
4 3
abcdefg
hijklmnop
qrstuv
wxyz```

### 输出

```
1352```

## 样例 #3

### 输入

```
5 1000000000
abc
acde
cefg
abcfh
dghi```

### 输出

```
346462871```

# 题解

## 作者：e4fsrc2e4fsrc2 (赞：3)

## [typewriter](https://www.luogu.com.cn/problem/AT_abc246_f)
## 思路分析
这个题的容斥比较明显，如果只有两个字符串，则明显答案为：由第一个字符集组出的字符串数量+由第二个字符集组出的字符串数量-两个字符集都能组出的字符串数量。用数学语言表示就是 ${\lvert s1 \rvert}^L+{\lvert s2 \rvert}^L-{\lvert s1 \cap s2 \rvert}^L$。

那么推广到 $N$ 个字符集，答案也是类似的：

$\sum -1^{count{s}} \times {\lvert s1 \cap s2 \cap ...\rvert}^L$

其中 $counts$ 表示 $s$ 中字符集的个数，$\lvert s1 \cap s2 \cap ...\rvert$  表示 $s$ 中所有的字符集的并集。

这道题的字符集的个数 $N \leq 18$，所以可以考虑使用状态压缩去枚举子集，令全集为 $2^{n-1}-1$，对于每个状态，二进制第 $i$ 位为 $1$ 表示选择第 $i$ 个字符集，在枚举的时候 ```__builtin_popcount()``` 计算,状态中 $1$ 的个数，奇数加，偶数减。

然后对于每一个字符串，因为都是小写字母，字符比较少，也可以用一个 $26$ 位的二进制数去表示一个字符串中是否存在对应的字母。显然把需要的字符串的状态都按位与，则可以得到共有的字母。

几个字符串交集的元素个数就是它们共有的字母在长度 $L$ 上随意放置产生的串的个数，也就是 $cnt^L$（$cnt$ 为共有字母的个数），这个共有的字母个数也可以用 ```__builtin_popcount() ``` 得到。
## AC Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define R register int
using namespace std;
const int N=19,mod=998244353;
int n;ll l,a[N],fac[N],inv[N],ans;
string s;
ll qpow(ll a,int b){
	ll res=1;
	while(b){
		if(b&1)res=res*a%mod;
		a=a*a%mod,b>>=1;
	}
	return res;
}
void init(){
	fac[0]=inv[0]=1;
	for(R i=1; i<N; i++)
		fac[i]=fac[i-1]*i%mod,inv[i]=inv[i-1]*qpow(i,mod-2);
}
int f(int x){return __builtin_popcount(x);}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>l;init();
	for(R i=1; i<=n; i++){
		cin>>s;
		for(R j=0; j<s.size(); j++)
			a[i]|=(1<<s[j]-'a');
	}
	for(R i=1; i<(1<<n); i++){
		R x=i,cnt=1,cn=f(i);ll y=(1<<26)-1;
		while(x){
			if(x&1)y&=a[cnt];
			x>>=1,cnt++;
		}
		if(cn&1)ans=(ans+qpow(f(y),l))%mod;
		else ans=(ans-qpow(f(y),l)+mod)%mod;
	}
	cout<<ans;
	return 0;
}

```

---

## 作者：Zhao_daodao (赞：1)

## $\mathcal{Description}$
存在 $n$ 个字符集，任选一个字符集，从中组出长度为 $l$ 的字符串。

求最多得到多少种不同的字符串。
## $\mathcal{Solution}$
考虑容斥。
### 两个字符串
对于两个字符串 $S_{1}$ 和 $S_{2}$：$ans=\left|S_{1}\right|^{l}+\left|S_{2}\right|^{l}-\left|S_{1}\cap S_{2}\right|^{l}$。
### 推广结论
显然这个结论具有普遍性，将结论推广。

$ans=\sum_{T\in N}^{}(-1)^{|T|}\times\left|S_{1}\cap S_{2}\cap\dots\cap S_{|T|}\right|^L$。
### 然后
这个题就做完了。用 **状态压缩** 去枚举子集。

枚举每一个字母，看他是否存在于所有子集中包含的字符串。
## $\mathcal{code}$
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,l,len,a[20],ans,sum,mod=998244353;
string stt;
int qpow(int x,int y)
{
	int ret=1;
	while(y){
		if(y&1)
			ret=ret*x%mod;
		x=x*x%mod;
		y/=2;
	}
	return ret;
}
signed main()
{
	cin>>n>>l;
	for(int i=1;i<=n;i++){
		cin >> stt;
		int tt=stt.size();
		for(int j=0;j<tt;j++)a[i]|=(1<<(stt[j]-'a'));
	}
	for(int h=1;h<(1<<n);h++)
	{
		int now=(1<<27)-1;
		for(int i=1;i<=n;i++){
			if(h&(1<<(i-1)))
				now&=a[i];
		}
		sum=qpow(__builtin_popcount(now),l);
		if(__builtin_popcount(h)&1)
			ans=(ans+sum)%mod;
		else
			ans=(ans-sum+mod)%mod;
	}
	cout<<ans;
}
```

---

## 作者：cppcppcpp3 (赞：0)

### Problem

给定 $n$ 个字符串，字符集为小写字母。可以任意选择一个字符串，用其所包含的字符组成字符串（字符可以重复），求可以组成的长度为 $l$ 的不同字符串的数量。

### Solution

容斥。

枚举用 $i$ 个给出的字符串，将它们的交集 $T$ 作为组出的字符串的字符库。则可以组出 $ \lvert T \rvert ^{l}$ 个满足条件的字符串。由容斥可知，当 $i$ 为奇数时，答案减去组成的字符串数量；反之加上。

同时，为了方便，对每个给出的字符串进行状态压缩。对于每一个 $i$，搜索即可。

### Code

代码里的 $k$ 是题面中的 $l$。

```cpp
#include<bits/stdc++.h>
#define il inline
#define int long long
#define S ((1<<n)-1)
using namespace std;
const int P=998244353;

il int wrd(){
	int x=0,f=1; char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)) x=x*10+c-48,c=getchar();
	return x*f;
}

int n,k,ans,state[26];

int popcnt(int x){
	int cnt=0;
	while(x) cnt++,x&=(x-1);
	return cnt;
}

il int qpow(int a,int b){
	int ans=1;
	while(b){
		if(b&1) (ans*=a)%=P;
		(a*=a)%=P,b>>=1; 
	}
	return ans;
}

int u[20];

void dfs(int x,int l){
	if(x>l){
		int v=(1<<26)-1;
		for(int i=1;i<=l;++i) v&=state[u[i]];
		
		int p=popcnt(v);
		if(l&1) ans=(ans+qpow(p,k))%P; //统计答案。
		else ans=(ans+P-qpow(p,k))%P;
		return;
	}
	for(int i=u[x-1]+1;n-i>=l-x;++i){
		u[x]=i,dfs(x+1,l);
	}
}

main(){
	n=wrd(),k=wrd();
	for(int i=1;i<=n;++i){
		string s; cin >> s;
		int l=s.size();
		for(int j=0;j<l;++j) state[i]|=(1<<(s[j]-'a')); //状态压缩。
	}
	
	for(int i=1;i<=n;++i) dfs(1,i); //用i个字符串的交集作为字符库。
	
	return printf("%lld",ans),0;
}
```

---

## 作者：迟暮天复明 (赞：0)

[没说更好的阅读体验](https://www.cnblogs.com/1358id/p/16435920.html)

有 $N$ 个字符集，可以任选一个字符集，从中任意组出一个长度为 $L$ 的字符串。问能得到多少种不同的字符串。
如两个字符集为 $\tt{ab}$ 和 $\tt{ac}$ 可以组成 $\tt{aa},\tt{ab},\tt{ac},\tt{ba},\tt{ca},\tt{bb},\tt{cc}$ 共 $7$ 个不同的字符串。

$N\leq18,L\leq10^9$

-----
容斥。

如果只有两个字符串，则明显答案为：由第一个字符集组出的字符串数量+由第二个字符集组出的字符串数量-两个字符集都能组出的字符串数量。

用数学语言表示就是 $|S_1|^L+|S_2|^L-|S_1\cap S_2|^L$。

那么推广到 $N$ 个字符集，也是类似的。答案就是 
$$\sum_{S\in N} -1^{\operatorname{count}\{S\}}\times |S_1\cap S_2\cap\ldots|^L$$

其中 $\operatorname{count}\{S\}$ 表示 $S$ 中字符集的个数，$|S_1\cap S_2\cap\ldots|$ 表示 $S$ 中所有字符串的并集。
那这样这个题就做完了。用状态压缩去枚举子集。做交集的时候我只需要知道有几个字符，而不需要知道是哪些字符，所以我枚举每一个字母，看他是否存在于所有子集中包含的字符串即可。

[Code](https://paste.ubuntu.com/p/xTP8WwHwSc/)

---

## 作者：Tsawke (赞：0)

# [ABC246F typewriter](luogu.com.cn/problem/AT_abc246_f) Solution

[TOC]

## [更好的阅读体验戳此进入](http://blog.monkey-hyx.tech?t=ABC246F)

## 题面

给定 $ n $ 个字符串，字符集为小写字母，可以任意选择一个字符串，作为字符库，然后（可多次选择同一字符）任意组成长度为 $ l $ 的字符串，求一共能形成多少种长度为 $ l $ 的字符串。

## Solution

容斥较为显然，显然最终答案也就是，用任意一个字符集形成的字符串减去任意两个的加上任意三个...于是我们考虑令全集为 $ S = 2^n - 1 $ 然后对其进行枚举子集，二进制第 $ i $ 位为 $ 1 $ 或 $ 0 $ 代表是否考虑这个数，所以枚举的时候直接 `__builtin_popcount()` 算一下个数，奇数代表加，反之减。然后对于每一个字符串，因为字符集较小，也用一个 `int` 的二进制表示是否存在对应的字符，然后把需要的字符串都与起来，设数量为 $ \xi $，则此次运算的字符集大小则为 $ \xi $，所以此次答案为 $ \xi^l $，加减考虑好即可。

## Code

```cpp
#define _USE_MATH_DEFINES
#include <bits/extc++.h>

#define PI M_PI
#define E M_E
#define npt nullptr
#define SON i->to
#define OPNEW void* operator new(size_t)
#define ROPNEW(arr) void* Edge::operator new(size_t){static Edge* P = arr; return P++;}

using namespace std;
using namespace __gnu_pbds;

mt19937 rnd(random_device{}());
int rndd(int l, int r){return rnd() % (r - l + 1) + l;}
bool rnddd(int x){return rndd(1, 100) <= x;}

typedef unsigned int uint;
typedef unsigned long long unll;
typedef long long ll;
typedef long double ld;

#define MOD 998244353

template<typename T = int>
inline T read(void);

int N, L;
int str[20];
int readStr(void){
    int ret(0);
    char c = getchar();
    while(!islower(c))c = getchar();
    vector < int > val;
    while(islower(c)){
        ret |= 1 << (c - 'a');
        c = getchar();
    }return ret;
}
ll qpow(ll a, ll b){
    ll ret(1), mul(a);
    while(b){
        if(b & 1)ret = ret * mul % MOD;
        b >>= 1;
        mul = mul * mul % MOD;
    }return ret;
}

int main(){
    N = read(), L = read();
    ll ans(0);
    for(int i = 1; i <= N; ++i)str[i] = readStr();
    // for(int i = 1; i <= N; ++i)
    //     cout << bitset < 32 > (str[i]) << endl;
    int Smx = (1 << N) - 1;
    // cout << "Smx" << bitset < 32 > (Smx) << endl;
    for(int S = Smx; S; S = (S - 1) & Smx){
        // cout << "S:" << bitset < 32 > (S) << endl;
        int cnt = __builtin_popcount(S);
        int tot((1 << 26) - 1);
        for(int i = 0; i <= N - 1; ++i)
            if((1 << i) & S)tot &= str[i + 1];
        // cout << "tot:" << bitset < 32 > (tot) << endl;
        ans = (ans + qpow(__builtin_popcount(tot), L) * ((cnt & 1) ? 1 : -1) + MOD) % MOD;
    }
    printf("%lld\n", ans);
    fprintf(stderr, "Time: %.6lf\n", (double)clock() / CLOCKS_PER_SEC);
    return 0;
}

template<typename T>
inline T read(void){
    T ret(0);
    short flag(1);
    char c = getchar();
    while(c != '-' && !isdigit(c))c = getchar();
    if(c == '-')flag = -1, c = getchar();
    while(isdigit(c)){
        ret *= 10;
        ret += int(c - '0');
        c = getchar();
    }
    ret *= flag;
    return ret;
}
```

## UPD

update-2022_10_21 初稿

---

