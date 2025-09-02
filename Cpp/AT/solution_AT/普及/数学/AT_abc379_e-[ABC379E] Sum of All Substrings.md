# [ABC379E] Sum of All Substrings

## 题目描述

给定一个长度为 $N$ 的字符串 $S$，其中 $S$ 里只包含数字字符，且没有数字字符 `0`。  
对于每一对正整数 $1 \le i \le j \le N$，定义 $f(i,j)$ 表示将 $S$ 的第 $i \sim j$ 个字符提取出来的子串作为一个数字。  
现在请你求出 $ \sum _ {i = 1} ^ N \sum _ {j = i} ^ N f(i,j)$ 的结果。

## 说明/提示

对于 $100\%$ 的数据，保证 $1 \le N \le 2 \times 10^5,|S|=N$ 且 $S$ 只由数字字符 `1` $\sim$ `9` 组成。

## 样例 #1

### 输入

```
3
379```

### 输出

```
514```

## 样例 #2

### 输入

```
30
314159265358979323846264338327```

### 输出

```
369673254065355789035427227741```

# 题解

## 作者：gesong (赞：12)

题目传送门：[[ABC379E] Sum of All Substrings](https://www.luogu.com.cn/problem/AT_abc379_e)。
# 思路
考虑拆贡献，可以假设第 $i$ 个数的数码为 $a_i$，那么它左边选择的值对他没有影响只会增加 $i$ 种不同的情况，而右边选择的区间会对答案产生 $10^0+10^1+10^2+\cdots+10^{n-i}$ 的贡献，因此总共的贡献即为 $ia_i(10^0+10^1+10^2+\cdots+10^{n-i})=ia_i10^0+ia_i10^1+ia_i10^2+\cdots+ia_i10^{n-i}$，因此我们可以使用差分求出 $10^i$ 要乘的系数，然后模拟进位即可。
# 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+100;
string s;
int a[N];
inline int read(){
	char c=getchar();
	int f=1,ans=0;
	while(c<48||c>57) f=(c==45?f=-1:1),c=getchar();
	while(c>=48&&c<=57) ans=(ans<<1)+(ans<<3)+(c^48),c=getchar();
	return ans*f;
}
main(){
	int n=read();cin>>s;s=" "+s;
	for (int i=1;i<=n;i++){
		int x=n-i+1,y=(s[i]-48)*i;
		a[1]+=y,a[x+1]-=y;
	}
	for (int i=1;i<=n;i++) a[i]+=a[i-1];
	a[0]=n;
	int k=0;
	for (int i=1;i<=n;i++){
		a[i]+=k;
		k=a[i]/10;
		a[i]%=10; 
	}
	while(k) a[++a[0]]=k%10,k/=10;
	for (int i=a[0];i>0;i--) cout <<a[i];
    return 0;
}
// NOIP 2024 RP++
// NOIP 2024 RP++
// NOIP 2024 RP++
// NOIP 2024 RP++
// NOIP 2024 RP++
```

---

## 作者：Moya_Rao (赞：4)

# 题目大意
现在有一个长度为 $N$ 的字符串 $S$。  
定义 $f(i,j)$ 表示截取字符串 $S$ 的第 $i \sim j$ 位的子串，再作为一个数字即为 $f(i,j)$。  
请你求出 $ \sum _ {i = 1} ^ N \sum _ {j = i} ^ N f(i,j)$ 的结果。

# 思路
闲话：赛时第一次做出 E 题，感觉不错！

很容易发现不好从一个个数字下手，因为一共有大概 $N^2$ 个数字，遍历一遍都是不可能的。那么我们可以从位数下手，因为一个 $f(i,j)$ 它的位数最多只是 $N$ 而已。就是枚举位，即个位、十位、百位、千位等。

那我们就需要知道当了每个位的所有数字之和是多少（一个数字可以当多次这个位则需要多次累加和）。打个表可以发现：

对于个位来说：  

|下标|$1$|$2$|$3$|$4$|$\dots$|$N$|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|出现次数|$1$|$2$|$3$|$4$|$\dots$|$N$|

对于十位来说：

|下标|$1$|$2$|$3$|$4$|$\dots$|$N-1$|$N$|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|出现次数|$1$|$2$|$3$|$4$|$\dots$|$N-1$|$0$|

对于百位来说：

|下标|$1$|$2$|$3$|$4$|$\dots$|$N-2$|$N-1$|$N$|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|出现次数|$1$|$2$|$3$|$4$|$\dots$|$N-2$|$0$|$0$|

发现了么？对，原来是下标是多少就出现多少次，但是高一个位，就会从后面开始依次废掉一个数字。

那不就好办了么，首先扫一遍整个字符串 $S$，拿一个 $sum$ 对个位的情况求一次和，然后遍历让这些数字一个个废掉，用高精度算一下就行了。注意第 $1$ 个数字没必要让它也废一次，因为那是就什么都不用加了，而且算个位的时候是一个数字都没有废掉的，那么你要么单独拎出来算，要么就当做删掉 $S$ 的第 $N+1$ 个数字字符，可以自己构造一个 $0$ 放在末尾嘛，我用的是这种做法。最后做一些高精度的常规处理，进下位再去个前导零，倒序输出就好啦。

最后献上考场时一字未改的[提交记录](https://atcoder.jp/contests/abc379/submissions/59612273)，可以在里边查看 AC 代码哟~

如果你觉得这篇题解对你有帮助的话，请点一个赞，谢谢！

---

## 作者：Po7ed (赞：2)

妙妙拆贡献题。最后 2 min 做出来的。

一个显然的想法：由于 $S$ 的一个子串必然是 $S$ 的一个前缀的后缀。所以考虑遍历每个前缀，维护其所有后缀的 $f$ 值之和。

由于这题需要高精，直接做是 $O\left(\dfrac{n^2}{L}\right)$ 的，$L$ 为常数，取决于你高精的实现，过不了。

思考这个做法的本质。对于一个字符 $S_i$，包含它的前缀 $j$ 一共有 $(n-i+1)$ 个，因为 $i\le j\le n$。而对于其中任意一个前缀，其包含 $i$ 的前缀的后缀 $k$ 只有 $i$ 个，因为 $1\le k\le i$。

举个例子，样例 `379`，考虑 $7$ 的贡献。包含它的区间有 $[1,2],[2,2],[1,3],[2,3]$。对于区间 $[1,2],[2,2]$，贡献为 $7+7$，因为 $7$ 在 $37,7$ 的个位。对于 $[1,3],[2,3]$，贡献为 $70+70$，因为 $7$ 在 $379,79$ 的十位。同理答案为 $3+30+300+7+7+70+70+9+9+9=514$。

形式化地说，$S_i$ 的贡献 $g(i)$ 为

$$
\begin{aligned}
g(i)&=\sum_{j=i}^{n}\sum_{k=1}^{i}(S_i-\texttt{`0'})\times 10^{j-i}\\
&=\sum_{j=i}^{n}i\times (S_i-\texttt{`0'})\times 10^{j-i}\\
&=\sum_{j=0}^{n-i}i\times (S_i-\texttt{`0'})\times 10^{j}\\
\end{aligned}
$$

观察形式，发现上式类似于对答案的十进制表示进行「区间加」。

不妨设答案为 $ans$，其第 $j$ 位（$10^j$）为 $ans_j$。答案加上 $g(i)$ 等价于

$$
\forall 0\le j\le n-i,\,ans_j\gets ans_j+i\times (S_i-\texttt{`0'})\times 10^{j}
$$

$ans$ 可以用差分数组维护。我们不用考虑进位，进位到所有贡献加完后处理。

赛时代码，实现略有不同（代码中字符串下标从 $0$ 开始，$ans$ 记为 `num`）。

```cpp
#include <bits/stdc++.h>

using std::cin;
typedef long long ll;
constexpr int N=214514;
int n;
std::string s;
ll num[N];

int main()
{
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin>>n>>s;
	ll val;
	for(int i=0;i<n;i++) // 注意下标从 0 开始，g(i) 式子略有不同
	{
		val=(i+1)*(s[i]-'0'); // g(i)，单字符贡献
		num[1]+=val; // 利用差分区间加
		num[n-i+1]-=val;
	}
	for(int i=1;i<=n+114;i++) // 注意这里 n+114，因为进位可能导致 ans 远大于 S
	{
		num[i]+=num[i-1]; // 还原
	}
	std::string ans;
	for(int i=1;i<=n+114;i++)
	{
		// printf("%c",num[i]%10+'0');
		ans.push_back(num[i]%10+'0'); // 先存 ans 里
		num[i+1]+=num[i]/10; // 处理进位
	}
	while(!ans.empty()&&ans.back()=='0')ans.pop_back(); // 去除前导 0
	std::reverse(ans.begin(),ans.end()); // 倒序输出
	if(ans.empty())puts("0");
	else printf("%s\n",ans.c_str());
	return 0;
} // 赛时急了，实现可能不是很好
```

---

## 作者：SXqwq (赞：2)

### Description

给定一个长度为 $n$ 的字符串 $S$，由 $1-9$ 的数字组成。定义 $f(i,j)$ 为 $S$ 从 $i$ 到 $j$ 在十进制意义下的数。求

$$\sum\limits_{i=1}^n\sum\limits_{j=i}^nf(i,j)$$

$n\le 2\times 10^5$。

### Analysis

提供一个很魔怔的做法。理论上可以过，但是不好写。

这个式子一看就很分治。考虑跨过中点的怎么做。

对于区间 $[l,r]$，跨过中点的区间一定是 $[l,mid]$ 的后缀拼上 $[mid+1,r]$ 的前缀。考虑扫描区间左端点 $L$，显然 $L\in[l,mid]$。对于任意左端点 $L$，都可以拼区间 $[mid+1,mid+2],[mid+1,mid+3]\dots[mid+1,r]$，这个贡献是定值，可以预处理。左边的区间 $[L,mid]$ 产生贡献可以用等比数列求和公式直接做。具体的，区间 $[L,mid]$ 产生 $f(L,mid)\times \dfrac{10^{r-mid+1}-10}{9}$ 的贡献。

时间复杂度 $O(n\log n)$。

不难写出如下代码。

```cpp
//highPrecisionMultiply 是 ChatGPT 写的 __int128_t 类型乘法。highPrecisionMultiply(x,y) 返回 x*y
    __int128_t cdq(int l,int r)
    {
        __int128_t ans = 0;
        if(l == r) return (__int128_t)(1LL * (long long)(s[l] - '0'));
        int mid = (l+r) >> 1;
        ans += cdq(l,mid),ans += cdq(mid+1,r);
        __int128_t sum = 0,resr = 0;
        for(int i=mid+1;i<=r;i++) {resr = resr * 10*1 + 1*(int)(s[i]-'0');sum += resr;}
        __int128_t resl = 0;
        for(int i=mid;i>=l;i--) 
        {
            resl = resl + highPrecisionMultiply(pow(10,mid-i),(s[i]-'0'));
            ans += sum;
            __int128_t t = highPrecisionMultiply(resl,(pow(10,(r-mid+1))-10));
            t = 1LL*t/9;
            ans += t;
        }
        return ans;
    }
```
$n\le 2\times 10^5$，`__int128_t` 无法接受，得手写高精。高精代码太难看就不放了。

---

## 作者：Genius_Star (赞：1)

### 思路：

考虑推一波式子：

$$\begin{aligned} \sum_{l = 1}^n \sum_{r = l}^n f(l, r) & = \sum_{l = 1}^n \sum_{r = l}^n \sum_{i = l}^r 10^{r  - i} a_i \\ & = \sum_{i = 1}^n a_i \sum_{l = 1}^i \sum_{r = i}^n 10^{r - i} \\ & = \sum_{i = 1}^n i a_i \sum_{r = i}^n 10^{r-i} \\ &= \sum_{i = 1}^n ia_i (10^0 + 10^1 + 10^2 + \cdots + 10^{n-i})\end{aligned}$$

那么对于 $a_i$ 的贡献，相当于给答案的 $0$ 到 $n-i$ 位都加上一个 $ia_i$，故不需要写高精。

时间复杂度为 $O(N)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#define Add(x, y) (x + y >= mod) ? (x + y - mod) : (x + y)
#define lowbit(x) x & (-x)
#define pi pair<ll, ll>
#define pii pair<ll, pair<ll, ll>>
#define iip pair<pair<ll, ll>, ll>
#define ppii pair<pair<ll, ll>, pair<ll, ll>>
#define ls(k) k << 1
#define rs(k) k << 1 | 1
#define fi first
#define se second
#define full(l, r, x) for(auto it = l; it != r; ++it) (*it) = x
#define Full(a) memset(a, 0, sizeof(a))
#define open(s1, s2) freopen(s1, "r", stdin), freopen(s2, "w", stdout);
#define For(i, l, r) for(register int i = l; i <= r; ++i)
#define _For(i, l, r) for(register int i = r; i >= l; --i)
using namespace std;
using namespace __gnu_pbds;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const int N = 4e5 + 10;
inline ll read(){
    ll x = 0, f = 1;
    char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-')
          f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9'){
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x > 9)
	  write(x / 10);
	putchar(x % 10 + '0');
}
ll sum;
int n, len;
char s[N];
ll a[N], ans[N];
bool End;
int main(){
	n = read();
	scanf("%s", s + 1);
	for(int i = 1; i <= n; ++i){
		a[i] = s[i] - '0';
		sum += 1ll * i * a[i];
	}
	for(int i = 0; i < n; ++i){
		ans[i] = sum;
		sum -= 1ll * (n - i) * a[n - i];
	}
	for(int i = 0; i < 2 * n; ++i){
		ans[i + 1] += ans[i] / 10;
		ans[i] %= 10;
		if(ans[i])
		  len = i;
	}
	for(int i = len; i >= 0; --i)
	  putchar(ans[i] + '0');
	cerr << '\n' << abs(&Begin - &End) / 1048576 << "MB";
	return 0;
}
```

---

## 作者：__yun__ (赞：1)

### 思路：
注：第 $i$ 位指从左往右数第 $i$ 位。

考虑拆位。通过手玩样例，发现原数的第 $i$ 位会对答案的第 $i$ 至 $n$ 位产生 $i$ 次贡献（分别在第 $1$ 至 $i$ 位做开头，第 $i$ 至 $n$ 位做结尾时产生）。

由此不难想到 $O(n^2)$ 的做法，显然它会TLE。随后考虑优化，我们惊奇地发现答案第 $i$ 位的是包含第 $i-1$ 位的，而剩下的部分就是 $i$ 倍的原数的第 $i$ 位，由此可以将时间复杂度将至 $O(n)$。

对于进位，先不管它，分别计算答案的每一位，最后统一处理进位。

### Code:
```cpp
#include<bits/stdc++.h>
//#define int long long
#define rd read<int>()
#define rdl read<ll>()
#define pb emplace_back
#define mkp make_pair
#define Endl putchar('\n')
#define Space putchar(' ')
#define chmin(x,y) x=min(x,y)
#define chmax(x,y) x=max(x,y)
using namespace std;
typedef long long ll;
using pii=pair<int,int>;
const int mod=998244353,inf=0x3f3f3f3f;
const ll Inf=0x3f3f3f3f3f3f3f3f;
template<class T> inline T read(){
	T s=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){s=(s<<3)+(s<<1)+c-'0';c=getchar();}
	return s*f;
}
template<typename T> inline void write(T x){
	if(x==0){putchar('0');return ;}
	if(x<0){putchar('-');x=-x;}
	T y=1;while(y<=x){if(y*10>x||(y*10)%10)break;y*=10;}
	while(y){putchar((x/y)^'0');x%=y;y/=10;}
}
inline char readc(){
	char c=getchar();
	while(c=='\n'||c=='\r'||c==' '||c==EOF)c=getchar();
	return c;
}
const int N=2e5+10;
int n;
ll a[N];
inline void solve(){
    n=rd;
    int cnt=0;
    for(int i=1;i<=n;i++){
    	int x=readc()-'0';
    	a[i]=a[i-1]+x*i;
	}
	for(int i=n;i>=1;i--){
		a[i-1]+=a[i]/10;
		a[i]%=10;
	}
	if(a[0])write(a[0]);
	for(int i=1;i<=n;i++){
		putchar(a[i]^48);
	}
}
signed main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	int T=1;
//	T=read<signed>();
	while(T--){
		solve();
	}
    return 0;
}
```

---

## 作者：array2022 (赞：1)

### 题意简述

因为这题还没有翻译所以加上题意简述。

求一个长度为 $N$ 的字符串所有子串所代表的十进制数之和。$1\le N\le 2\times 10^5$。

### 题目分析

- 看到数据范围后可以直接想到要使用高精度，其次就是一个重要的技巧**按位拆分**，考虑每一位的数对结果的贡献。
- 通过找规律可以发现第 $i$ 位的数 $x$ 的贡献为 $g(N-i+1)\cdot x\cdot i$，其中 $g(n)=\begin{matrix}\\ \underbrace{111\cdots 111}\\ \scriptsize{n \ 个 \ 1}\end{matrix}$，那么答案就是 $\sum\limits_{i=1}^n g(N-i+1)\cdot S(i)\cdot i$，其中 $S(i)$ 表示题目所给字符串的第 $i$ 位。
- 上面的解释可能有些抽象，我们用字符串 $3456$ 举个例。答案为 $3333+444\times 2+55\times 3+6\times 4=4410$。
- 下面让我们尝试证明这个结论。（不想看可以跳过）考虑 $S(i)$ 在子串中出现在**从后往前**第 $j$ 位的情况，那么只要选择 $S$ 的第 $y$ 位到第 $i+j-1$ 位即可，其中 $1\le y\le i$。所以总共的贡献为 $i\cdot x\cdot \begin{matrix}\\ \underbrace{111\cdots 111}\\ \scriptsize{(N-i+1) \ 个 \ 1}\end{matrix}$。
- 最后我们考虑如何计算答案，可以发现这个问题需要区间修改（全部加上一个数）和区间查找（找出这个区间内所有数的和），所以我们使用和差分前缀和处理，最后考虑一下进位问题即可。
- 关于最后的答案有多大，可以先把数组开到很大，输一个最大的字符串进去跑一下，答案是长度为 $2\times 10^5+1$ 的一个数。

### 通过代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,d[5000005]; // 赛时为了保险开了 5e6 的数组
string s;
signed main(){
	ios::sync_with_stdio(0);
	cin>>n>>s;
	s=' '+s; // 个人习惯，仅供参考
	for (int i=1;i<=n;i++){
		d[0]+=(s[i]-'0')*i;
		d[n-i+2]-=i*(s[i]-'0'); // 计算差分数组
	}
	for (int i=1;i<=5000000;i++){
		d[i]+=d[i-1]; // 前缀和
	}
	for (int i=1;i<=5000000;i++){
		d[i+1]+=d[i]/10;
		d[i]%=10; // 处理进位
	}
	int len=5000000;
	while (d[len]==0&&len>1) len--;
	for (int i=len;i>=1;i--){
		cout<<d[i];
	}
	return 0;
}
```

---

## 作者：chenxi2009 (赞：1)

# 思路
对于 $S_i$，可以有 $[0,i-1]$ 个数字排在它前面，也就是说它前面出现的数字有 $i$ 种可能（需要注意前面的数字**不影响 $S_i$ 所在的数位**）。\
同样发现 $S_i$ 所在的数位有 $N-i+1$ 种可能，对应的贡献为 $S_i\times10^{[0,N-i]}$，根据前段讨论，这个贡献做了 $i$ 次。总贡献为：
$$
\sum_{j=0}^{N-i}i\times S_i\times10^j
$$
用高精度存，连续的若干位上加上同一个数，区间加法用差分维护，加完之后前缀和得到答案，最后做个高精度进位操作就没了。

~~E 题最简单的一次。~~
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
long long ans[300001],c[200001];
char s[200001];
bool st;
int main(){
	scanf("%d%s",&n,s + 1);
	for(int i = 1;i <= n;i ++){
		c[i] = i * (s[i] - '0');
	}
	for(int i = n;i;i --){
		ans[i] = ans[i + 1] + c[n - i + 1];//差分
	}
	for(int i = 1;i < 300000;i ++){//进位
		ans[i + 1] += ans[i] / 10;
		ans[i] = ans[i] % 10;
	}
	for(int i = 300000;i;i --){
		if(ans[i]){//去除前导零
			st = true;
		}
		if(st){
			printf("%lld",ans[i]);
		}
	} 
	return 0;
}
```

---

## 作者：crz_qwq (赞：0)

简单推一下，发现第 $i$ 个数字对整个数的贡献是 $\sum_{j=0}^{n-i}10^j\times S_i$。

于是就变成了给高精度上的第 $0$ 位到第 $n-i$ 位加上 $S_i$，可以用差分维护。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5;
int n;string s;
int tr[N],ans[N];
void add(int x,int d)
{
	for(int i=x;i<=n;i+=i&-i)
		tr[i]+=d;
}
void update(int l,int r,int k)
{
	add(l,k);
	add(r+1,-k);
}
int query(int x)
{
	int res=0;
	for(int i=x;i;i-=i&-i)
		res+=tr[i];
	return res;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>n>>s;s="#"+s;
	for(int i=1;i<=n;++i)
	{
		int x=s[i]^48;
		update(1,n-i+1,x*i);
	}
	for(int i=1;i<=n;++i)
		ans[i]=query(i);
	for(int i=1;i<N-1;++i)
	{
		ans[i+1]+=ans[i]/10;
		ans[i]%=10;
	}
	bool flag=0;
	for(int i=N-1;i;--i)
	{
		if(ans[i])
			flag=1;
		if(flag||ans[i])
			cout<<ans[i];
	}
}
```

---

## 作者：4041nofoundGeoge (赞：0)

这是一道高精度的题目。

## 低精度写法

如果不看范围，我们可以写出低精度的写法（伪代码）。

```
#include<bits/stdc++.h>
using namespace std;
int main(){
  输入;
  for(i:1->n){
    for(j:i->n){
      截取 s 的第 i 位到第 j 位
      相加求和。
    }
  }
  return 0;
}
```

## 高精度写法

#### 为什么用高精度？

这道题的 $N=2\times10^5$。也就是代表 $S$ 有 $2\times 10^5$ 位数，远远超过 long long，故要用高精度。 

关于高精度，请查看[这里](https://oi-wiki.org/math/bignum/)。

于是，根据模板，我们即可得出答案。

```cpp
#include<bits/stdc++.h>
using namespace std;
int T[2<<17];
int main()
{
	int N;
	string S;
	cin>>N>>S;
	for(int i=0;i<N;i++)
	{
		int c=S[i]-'0';
		if(i>0)T[i]=T[i-1];
		T[i]+=c*(i+1);
	}
	string t="";
	long long cur=0;
	for(int i=N-1;i>=0||cur>0;i--)
	{
		if(i>=0)cur+=T[i];
		t+=cur%10+'0';
		cur/=10;
	}
	for(int i=t.size();i--;)cout<<t[i];
	cout<<endl;
}

```

---

## 作者：qfy123 (赞：0)

# Solution
我们从小的情况开始推式子找规律。例如 $n = 3$：
$$\begin{aligned}ans &= f(1,1) + f(1,2) + f(1,3) + f(2, 2) + f(2, 3) + f(3,3)\\ &= s_1 + 10s_1 + s_2 + 100s_1 + 10s_2 + s_3 + s_2 + 10s_2 + s_3 + s_3 \\ &= 100s_1 + 10(s_1 + 2s_2) + (s_1 + 2s_2 + 3s_3) \end{aligned}$$
这就意味着，在不考虑进位的情况下，从高到低位第一位放 $s_1$，第二位放 $s_1 + 2s_2$，……第 $i$ 位放 $\sum_{j=1}^i j \times s_j$。

于是这题的做法就呼之欲出了：用一个变量 $sum$ 维护当前这一位该放多少，从高位到低位填数，最后进位并输出答案即可。
# Code
```cpp
#include<bits/stdc++.h>
#define int long long 
#define ull unsigned long long
#define ri register int
#define rep(i,j,k) for(ri i=(j);i<=(k);++i) 
#define per(i,j,k) for(ri i=(j);i>=(k);--i)
#define repl(i,j,k,l) for(ri i=(j);(k);i=(l))
#define IOS ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
#define pc(x) putchar(x)
#define fir first
#define se second 
#define MP pair<int,int>
#define pii pair<int,int>
#define PB push_back
#define lson p << 1
#define rson p << 1 | 1
#define ls(p) tr[p].ch[0]
#define rs(p) tr[p].ch[1]
using namespace std;
char BUFFER[100000],*P1(0),*P2(0);
#define gtc() (P1 == P2 && (P2 = (P1 = BUFFER) + fread(BUFFER,1,100000,stdin), P1 == P2) ? EOF : *P1++)
inline int R(){
    int x;char c;bool f = 0;
	while((c = gtc()) < '0') if(c == '-') f = 1;
	x = c ^ '0';
	while((c = gtc()) >= '0') x = (x << 3) + (x << 1) + (c ^ '0');
	return f?(~x + 1):x;
}
inline string Rs(){
	string str = "";
	char ch = gtc();
	while(ch == ' ' || ch == '\n' || ch == '\r') ch = gtc();
	while(ch != ' ' && ch != '\n' && ch != '\r' && ch > '\0') str += ch, ch = gtc();
	return str;
}
inline int rS(char s[]){
	int tot = 0; char ch = gtc();
	while(ch == ' ' || ch == '\n' || ch == '\r') ch = gtc();
	while(ch != ' ' && ch != '\n' && ch != '\r' && ch > '\0') s[++tot] = ch, ch = gtc();
	return tot; 
}
inline void O(int x){
    if(x < 0) pc('-'),x = -x;
    if(x < 10) pc(x + '0');
    else O(x / 10),pc(x % 10 + '0');
}
inline void out(int x,int type){
	if(type == 1) O(x),pc(' ');
	if(type == 2) O(x),pc('\n');
	if(type == 3) O(x);
}
inline void Ps(string s, int type){
	int m = s.length();
	rep(i, 0, m - 1) pc(s[i]); 
	if(type == 1) pc(' ');
	if(type == 2) pc('\n');
}
inline void pS(char *s, int type){
	int m = strlen(s + 1);
	rep(i, 1, m) pc(s[i]);
	if(type == 1) pc(' ');
	if(type == 2) pc('\n');
}
inline void OI(){
	freopen(".in","r",stdin);
	freopen(".out","w",stdout);
}
const int N = 2e5 + 10;
char c[N];
int n, a[N << 1], sum;
inline void solve(){
	n = R(); rS(c);
	rep(i, 1, n){
		sum += i * (c[i] - '0');
		a[i] = sum;
	}
	reverse(a + 1, a + n + 1);
	int now = 1;
	while(a[now]){
		a[now + 1] += a[now] / 10;
		a[now] %= 10;
		now++; 
	} 
	now--;
	reverse(a + 1, a + now + 1);
	rep(i, 1, now) out(a[i], 3);
}
signed main(){
    // OI();
    int T = 1;
    // T = R();
	while(T--) solve();
	return 0;
}

```

---

## 作者：Luxe877 (赞：0)

很有意思的题目。

## 题意
给定一个 $N$ 位的整数 $S$，定义 $f(i,j)$ 表示 $S$ 中从第 $i$ 个数字到第 $j$ 个数字的子串转为十进制数所表达的数。比如当整数为 $2384$ 时，$f(2,4)=384,f(1,2)=23$。

现在需要你求出 $\sum \limits_{i=1}^{n} \sum \limits_{j=i}^{n} f(i,j)$。

## 解题
考虑每一位数对答案的贡献。（不是数位 dp）

从样例入手，根据样例解释，答案为 $3+37+379+7+79+9$。

拆解这个式子，不难得出：

$
3+37+379+7+79+9\\
=3+30+300+7+70+7+70+9+9+9\\
=1 \times 3 \times 111+2 \times 7 \times 11+3 \times 9 \times 1 \\
=3 \times 100+(3+14)\times 10+(3+14+27) \times 1
$

其中最后一行为解题的关键所在。进一步探讨其它样例，可以发现答案的公式如下：

$
ans= \sum \limits_{i=1}^{n} [10^{n-i}\times \sum \limits_{j=1}^{i} (S_i \times j)]
$

发现这个公式之后，写好高精度计算即可得出答案。注意开 `long long`！

赛时 AC 代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
string s;
long long num[200002];
long long ans[400002];
int main()
{
	cin>>n;
	cin>>s;
	for(int i=1;i<=n;i++)
	{
		num[i]=(s[i-1]-'0');
	}
	for(int i=1;i<=n;i++)
	{
		num[i]*=i;
		num[i]+=num[i-1];
		ans[n-i+1]+=num[i];
	}
	for(int i=1;i<=n;i++)
	{
		ans[i+1]+=ans[i]/10;
		ans[i]%=10;
	}
	int i=n+1;
	while(ans[i]>=10)
	{
		ans[i+1]+=ans[i]/10;
		ans[i]%=10;
	}
	for(i-=(ans[i]==0);i>=1;i--)
	{
		printf("%lld",ans[i]);
	}
	return 0;
}
/*
379
3+37+379+7+79+9
=3+30+300+7+70+7+70+9+9+9
=1*3*111+2*7*11+3*9*1
=100*3+10*(3+14)+1*(3+14+27)

1234
1+12+123+1234+2+23+234+3+34+4
=1+10+100+1000+2+20+200+2+20+200+3+30+3+30+3+30+4+4+4+4
=1*1*1111+2*2*111+3*3*11+4*4*1
=1000*1+(1+4)*100+(1+4+9)*10+(1+4+9+16)*1

999
9+99+999+9+99+9

*/
```

---

## 作者：IGA_Indigo (赞：0)

## 题目大意
给定一个十进制数，位数 $\le 2\times 10^5$，求将其所有的子串看作一个十进制数之后的和。
## 大体思路
$O(n^2)$ 肯定过不了，所以我们考虑拆开内层的累加，记录每个数在每一位上的贡献，进行差分，之后做一个前缀和并处理进位，倒着输出即可。

就比如第一个样例：
```cpp
3
379
```

![](https://cdn.luogu.com.cn/upload/image_hosting/vuky74bi.png)

我们可以容易的推得，从左往右数第 $i$ 位对答案的位数贡献是 $0$ 到 $n-i+1$，对每一位值的贡献是 $a_i\times i$（每一位上的数是 $a_i$）。

我们差分处理它然后前缀和加起来，接着处理进位的情况。

类似于高精度（雾）。
```cpp
for(int i=0;i<=n;i++){
  sum[i+1]+=sum[i]/10;
  sum[i]%=10;
}
```

最后我们倒着输出即可。为了避免前导零，我们要特判一下，为了避免检测不到前导零，我们从从右向左数第 $n+2$ 位开始判断。

```cpp
int bj=0;
for(int i=n+2;i>=0;i--){
  if(sum[i]==0&&!bj){
    continue ;
  }
  else{
    bj=1;
  }
  write(sum[i]);
}
```
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long read(){
	long long x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-'){
			f=-1;
		}
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}
void write(long long x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9){
		write(x/10);
	}
	putchar(x%10+'0');
	return ;
}
long long sum[200005];
int main(){
	int n=read();
	string s;
	cin>>s;
	s=' '+s;
	for(int i=1;i<=n;i++){
		sum[0]+=(s[i]-'0')*i;
		sum[n-i+1]-=(s[i]-'0')*i;//差分 
	}
	for(int i=1;i<=n;i++){
		sum[i]=sum[i-1]+sum[i];//前缀和 
	}
	for(int i=0;i<=n;i++){//处理进位 
		sum[i+1]+=sum[i]/10;
		sum[i]%=10;
	}//最后一位其实不用再进了，直接输出即可，反正进上去输出下来也是一个数，毕竟前面都是 0 
	int bj=0;
	for(int i=n+2;i>=0;i--){//避免查不到前导零 
		if(sum[i]==0&&!bj){//跳过前导零 
			continue ;
		}
		else{
			bj=1;//后面的零不能跳 
		}
		write(sum[i]);//输出当前位（未输出的最高位） 
	}
	return 0;
}
```

---

## 作者：CaoSheng_zzz (赞：0)

感觉是最简单的 E 了。

看数据范围首先确定高进度。

然后考虑每个数字在个、十、百、$\dots$ 位被答案统计了多少次。

然后不难发现 $S$ 的第 $n$ 位在个位统计 $n$ 次，$S$ 的 $n - 1$ 被在个位被统计 $n - 1$ 次，十位统计 $1$ 次。依次类推 $S$ 的第 $i$ 位在第 $x$ 位被统计 $i - x + 1$ 次。

然后我们用程序实现上述的东西就行了。

Code：
```cpp
const int maxn = 2e5 + 1 ;
char s[maxn] ;  
__int128 a[maxn << 1] ;
__int128 sum = 0 ;
int n, cnt = 1 ;

signed main() {
    n = read() ;
    scanf("%s", s + 1) ;
    for(int i=1 ; i<=n ; i++) sum += (s[i] - '0') * i ;
    for(int i=1 ; i<=n ; i++) {
        a[i] = sum ;
        sum -= (s[n - i + 1] - '0') * (n - i + 1) ;
    }
    while(cnt <= n || a[cnt] > 0) {
        ++ cnt ;
        a[cnt] += a[cnt - 1] / 10 ;
        a[cnt - 1] %= 10 ;
    }
    for(int i=cnt-1 ; i>=1 ; i--) output(a[i]) ;
    return 0 ;
}
```

---

## 作者：Union_Find (赞：0)

首先看到题目，吓了一跳，以为是高精度大模拟题。其实没那么复杂。

分析一下，我们分别考虑每一位的贡献。

假设第 $i$ 位的数字是 $a_i$，那么 $a_i$ 的贡献就分别考虑它在个位，十位，百位等位数的贡献。以百位举例，单独出现在百位时贡献是 $10^2a$，并且有 $i$ 个数是以 $a_i$ 作为百位的，所以在百位的贡献就是 $i \times 10^2a$。

那么这样子我们就得出了 $a_i$ 总共产生的贡献，应该是 $\sum_{j=0}^{n-i}(ia_i \times 10^i)$。不要以为他是 $O(n^2)$ 的，其实它相当于在结果的各个位数都加上 $ia_i$ 的贡献。以样例 $379$ 为例，那么它结果就是下图。



|百位|十位|个位|
|:-:|:-:|:-:|
|||$3 \times 9 = 27$|
||$2 \times 7 = 14$|$2 \times 7 = 14$|
|$1 \times 3 = 3$|$1 \times 3 = 3$|$1 \times 3 = 3$|

看到了吧，他其实就是 $n$ 个长度为 $O(n)$ 的数字相加。但是这样还是 $O(n^2)$ 的，所以要改一下。我们发现，结果的第 $i$ 位在不考虑进位时就是第 $i - 1$ 加上 $ia_i$。所以我们看可以前缀和快速求出每一位不进位时的结果，最后 $O(n)$ 处理进位，可以直接使用高精度板子。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define il inline
#define N 200005
il ll rd(){
	ll s = 0, w = 1;
	char ch = getchar();
	for (;ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') w = -1;
	for (;ch >= '0' && ch <= '9'; ch = getchar()) s = ((s << 1) + (s << 3) + ch - '0');
	return s * w;
}
ll n = rd(), a[N], cnt, ans[N];
char s[N];
int main(){
	scanf ("%s", s + 1);
	for (int i = 1; i <= n; i++)
        a[i] = a[i - 1] + (s[i] - '0') * i;//前缀和
	for (int i = n; i >= 2; i--){
		ans[++cnt] = a[i] % 10;
		a[i - 1] += a[i] / 10;
	}//进位处理
  while (a[1]){
		ans[++cnt] = a[1] % 10;
		a[1] /= 10;
	}//最高位可能有多位
  for (int i = cnt; i >= 1; i--) printf ("%lld", ans[i]);
	return 0;
}

```

---

