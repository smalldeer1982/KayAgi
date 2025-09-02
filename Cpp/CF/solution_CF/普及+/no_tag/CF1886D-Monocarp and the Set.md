# Monocarp and the Set

## 题目描述

Monocarp has $ n $ numbers $ 1, 2, \dots, n $ and a set (initially empty). He adds his numbers to this set $ n $ times in some order. During each step, he adds a new number (which has not been present in the set before). In other words, the sequence of added numbers is a permutation of length $ n $ .

Every time Monocarp adds an element into the set except for the first time, he writes out a character:

- if the element Monocarp is trying to insert becomes the maximum element in the set, Monocarp writes out the character &gt;;
- if the element Monocarp is trying to insert becomes the minimum element in the set, Monocarp writes out the character &lt;;
- if none of the above, Monocarp writes out the character ?.

You are given a string $ s $ of $ n-1 $ characters, which represents the characters written out by Monocarp (in the order he wrote them out). You have to process $ m $ queries to the string. Each query has the following format:

- $ i $ $ c $ — replace $ s_i $ with the character $ c $ .

Both before processing the queries and after each query, you have to calculate the number of different ways to order the integers $ 1, 2, 3, \dots, n $ such that, if Monocarp inserts the integers into the set in that order, he gets the string $ s $ . Since the answers might be large, print them modulo $ 998244353 $ .

## 说明/提示

In the first example, there are three possible orderings before all queries:

- $ 3, 1, 2, 5, 4, 6 $ ;
- $ 4, 1, 2, 5, 3, 6 $ ;
- $ 4, 1, 3, 5, 2, 6 $ .

After the last query, there is only one possible ordering:

- $ 3, 5, 4, 6, 2, 1 $ .

## 样例 #1

### 输入

```
6 4
<?>?>
1 ?
4 <
5 <
1 >
```

### 输出

```
3
0
0
0
1```

## 样例 #2

### 输入

```
2 2
>
1 ?
1 <
```

### 输出

```
1
0
1```

# 题解

## 作者：uid_310801 (赞：12)



> 不要高估 CF 网友的实力。当你想到一个巨麻烦的做法的时候，那就是你假了。

从前往后，每次将数**插入**排列中。

如果是 `>` 或 `<`，那么只能往两端插入，否则必须插到中间去。

所以如果有一个 `?`，那么答案乘上它前面插入的数 $-1$ 就行了。

最后特判一下答案是 $0$ 的情况，用逆元处理询问。

```cpp
#include<bits/stdc++.h>
namespace Spouter_27{
using namespace std;
typedef long long ll;
#define int long long
#define deb(x) cerr<<"Line: "<<__LINE__<<", "<<#x<<" = "<<x<<"; \n"
#define pii pair<ll,ll>
#define mp make_pair
#define fi first
#define se second
const ll N=3e5+10,mod=998244353;
inline ll read(){
	ll a=0,x=1;
	char c=getchar();
	while(!isdigit(c)){
		if(c=='-')	x=-x;
		c=getchar();
	}
	while(isdigit(c)){
		a=a*10+c-'0';
		c=getchar();
	}
	return a*x;
}
ll qpow(ll a,ll b){
	ll ans=1,base=a;
	while(b){
		if(b&1)	ans=ans*base%mod;
		base=base*base%mod;
		b>>=1;
	}
	return ans;
}
ll n,m,ans=1;
char s[N];
ll calc(){
	if(s[2]!='?')	return ans;
	return 0;
}
signed main(){
	n=read(),m=read();
	scanf("%s",s+2);
	for(int i=3;i<=n;i++){
		if(s[i]=='?')	(ans*=(i-2))%=mod;
	}
	printf("%lld\n",calc());
	while(m--){
		ll x=read()+1;
		char c=getchar();
		if(x!=2){
			if(s[x]=='?')	(ans*=qpow(x-2,mod-2))%=mod;
		}
		s[x]=c;
		if(x!=2){
			if(s[x]=='?')	(ans*=(x-2))%=mod;
		}
		printf("%lld\n",calc());
	}
	return 0;
}












}signed main(){return Spouter_27::main();}

```




---

## 作者：SunnyYuan (赞：9)

建议标签：数学。

建议难度：普及/提高-。

## 思路

这个题目非常有意思。

当您苦思冥想都想不出来怎么正着做的时候，不妨把问题反过来想想。

题中说是加数，我们就可以把所有的操作反过来，从 $n$ 个数字中不断删除数字。

首先如果是 $>$，那么就只能删除最大值，有一种选法。

其次如果是 $<$，那么只能删除最小值，也只有一种选法。

当操作为 $?$ 时，那么既不删除最大值，也不删除最小值，有 $len - 2$ 种选法，$len$ 是数组长度。

因为当第 $i$ 次操作完的时候有 $i$ 个数字，去除最大最小值，答案就是所有满足 $s_i = ?$ 的 $(i - 2)$ 的乘积。

对于每一个询问，如果要将是问号的一位改成别的（$s_i = '?' \rightarrow s_i = >/<$），那么就要除以 $(i - 2)$，这个可以使用逆元实现，不会的可以去补一补数论。当然，如果是一个别的字符改成问号也要记得乘上 $(i - 2)$。

还要特判，如果在只有两个数字的时候有 $?$，那不可能完成！因为除了最大值就是最小值，所以要直接输出 $0$。

## 代码

```cpp
/*******************************
| Author:  SunnyYuan
| Problem: D. Monocarp and the Set
| Contest: Codeforces - Educational Codeforces Round 156 (Rated for Div. 2)
| URL:     https://codeforces.com/contest/1886/problem/D
| When:    2023-10-11 14:41:49
| 
| Memory:  256 MB
| Time:    2000 ms
*******************************/

#include <bits/stdc++.h>

using namespace std;

const int N = 300010, mod = 998244353;

int n, m, ans;
int modfs[N];
char s[N];

int pow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = 1ll * res * a % mod;
        a = 1ll * a * a % mod;
        b >>= 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> (s + 2);
    for (int i = 1; i <= n; i++) modfs[i] = pow(i, mod - 2);
    ans = 1;
    for (int i = 3; i <= n; i++)
        if (s[i] == '?')
            ans = 1ll * ans * (i - 2) % mod;

    if (s[2] == '?') cout << "0\n";
    else cout << ans << '\n';

    int p;
    char x;
    while (m--) {
        cin >> p >> x;
        p++;
        if (s[p] == '?' && p > 2) ans = 1ll * ans * modfs[p - 2] % mod;
        if (x == '?' && p > 2) ans = 1ll * ans * (p - 2) % mod;
        s[p] = x;
        if (s[2] == '?') cout << "0\n";
        else cout << ans << '\n'; 
    } 
    return 0;
}
```

---

## 作者：TernaryTree (赞：2)

简单题。

考虑一个加字符的过程，即动态地维护当前字符串前缀的答案。

记字符串前缀 $[1,i]$ 的答案为 $pre_i$。

考虑 $pre_{i-1}$ 向 $pre_{i}$ 转移。根据当前字符，有三种情况：

- 当前字符为 `<`

   这个数只能为 $1$，$pre_i=pre_{i-1}$
   
- 当前字符为 `>`
  
   这个数只能为 $i+1$，$pre_i=pre_{i-1}$

- 当前字符为 `?`

  这个数可以是 $2\sim i$ 的任意一个数，$pre_i=(i-1)pre_{i-1}$。
  
至此，我们发现 $ans=pre_{n-1}=\prod\limits_{s_i=\texttt{?}}(i-1)$。

然后修改操作就是每次乘上一个数，或者除以一个数，即乘逆元。

注意到 $0$ 没有逆元，所以当反复修改 $1$ 这个位置时需要特判掉。仅维护

$$\prod\limits_{s_i=\texttt{?},i\ge 2}(i-1)$$

即可。

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int maxn = 1e6 + 10;
const int p = 998244353;

int n, m, ans = 1;
char s[maxn];
int inv[maxn];

signed main() {
	cin >> n >> m;
	cin >> (s + 1);
	inv[1] = 1;
	for (int i = 2; i <= n; i++) inv[i] = (p - p / i) * inv[p % i] % p;
	for (int i = 2; i <= n - 1; i++) if (s[i] == '?') ans = ans * (i - 1) % p;
	if (s[1] == '?') cout << 0 << endl;
	else cout << ans << endl;
	while (m--) {
		int i;
		char x;
		cin >> i >> x;
		if (i != 1) {
			if (s[i] == '?' && x != '?') ans = ans * inv[i - 1] % p;
			if (s[i] != '?' && x == '?') ans = ans * (i - 1) % p;
		}
		s[i] = x;
		if (s[1] == '?') cout << 0 << endl;
		else cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：Priestess_SLG (赞：0)

简单题。考虑维护每一个字符对答案的贡献：`<` 和 `>` 只能为当前的最大值，贡献为 $1$，而 `?` 可以为其他所有值，贡献为 $i-2$（$i$ 表示当前是第 $i$ 个字符）。

然后直接统计出来，修改的时候乘逆元即可。时间复杂度为 $O(n\log n)$。如果线性预处理逆元则可以做到 $O(n)$。

```cpp
#pragma GCC optimize(3) 
#include <bits/stdc++.h>
#define eb emplace_back
#define int long long
using namespace std;
const int N = 2000100, mod = 998244353;
char s[N];
int ksm(int a, int b, int c) {
    int ans = 1;
    while (b) {
        if (b & 1) {
            ans = ans * a % c;
        }
        a = a * a % c;
        b >>= 1;
    }
    return ans;
}
signed main() {
    int n, m;
    scanf("%lld%lld%s", &n, &m, s + 1);
    int now = 1;
    for (int i = 3; i <= n; ++i) {
        if (s[i - 1] == '?') {
            now = now * (i - 2) % mod;
        }
    }
    if (s[1] != '?') {
    cout << now << '\n';
    } else {
        cout << "0\n";
    }
    while (m--) {
        int o; char x;
        cin >> o >> x;
        if (o > 1) {
        if (s[o] == '?') {
            now = now * ksm(o - 1, mod - 2, mod) % mod;
        }
        if ((s[o] = x) == '?') {
            now = now * (o - 1) % mod;
        }
        } else {
            s[o] = x;
        }
        if (s[1] != '?') {
            cout << now << '\n';
        } else {
            cout << "0\n";
        }
    }
    return 0;
}

/*



*/
```

---

## 作者：2huk (赞：0)

> - 有一个排列 $p$ 和一个空集合。你需要按照顺序将 $p_i$ 插入集合并构造一个字符串 $s_2 \dots s_n$。若插入后 $p_i$ 是集合中的最大值则 $s_i = \texttt >$，最小值 $\texttt <$，否则 $\texttt ?$。给定 $s$ 并多次单点修改，每次修改后求初始 $p$ 的合法数量。

注意本文中 $s$ 的下标都比题目中的大 $1$。

正序插数转化成倒序删数。即最开始有一个集合 $\{1, 2, \dots, n\}$，若 $s_i = \texttt >$ 则删除最大值，$s_i = \texttt <$ 则删除最小值，$s_i = \texttt ?$ 则删除其它的任意一个值。

显然 $s_i = \texttt >$ 或 $s_i = \texttt <$ 时只有 $1$ 种方案，$s_i = \texttt ?$ 时方案数是 $|S| - 2$。而到 $s_i$ 时大小 $|S| = i$，因此答案为 $\prod_{s_i = \texttt ?} (i - 2)$。

我们需要动态维护这个值。令上一次操作后的答案为 $res$，那么将 $s_x \gets y$ 后 $res \gets \dfrac{res}{[s_x = \texttt ?] (x - 2)} \times [y = \texttt ?](x-2)$。但是当 $x = 2$ 时除法不对，我们需要特判。

事实上 $\prod_{s_i = \texttt ?} (i - 2)$ 中暗含着当 $s_2 = \texttt ?$ 时答案为 $0$，所以当 $x = 2$ 时我们不更改答案。输出答案时判断 $s_2$ 是否为 $\texttt ?$ 即可。

```cpp
int n, m;
char s[N];
int res;

int fpm(int a, int b) {
	int res = 1;
	while (b) {
		if (b & 1) res = (ll)res * a % P;
		b >>= 1, a = (ll)a * a % P;
	}	
	return res;
}

int calc() {
	return s[2] == '?' ? 0 : res;
}

signed main() {
	cin >> n >> m;
	res = 1;
	for (int i = 2; i <= n; ++ i ) {
		cin >> s[i];
		if (i != 2 && s[i] == '?') res = (ll)res * (i - 2) % P;
	}
	
	cout << calc() << '\n';
	
	while (m -- ) {
		int x;
		char y;
		cin >> x >> y;
		++ x;
		if (x != 2) {
			if (s[x] == '?') res = (ll)res * fpm(x - 2, P - 2) % P;
			if (y == '?') res = (ll)res * (x - 2) % P;
		}
		s[x] = y;
		cout << calc() << '\n';
	}
	
	return 0;
}
```

---

## 作者：Exp10re (赞：0)

CF 的出题组都不学数论的吗，幽默简单题定数 \*2100 是不是比较抽象了。

## 解题思路

注意到集合添加一个新元素时生成的符号只和这个元素与集合最大值最小值的相对位置有关。

考虑第 $i$ 个字符，对于一个 $\texttt{<}$ 和 $\texttt{>}$ 其相对位置是一定的，不产生额外贡献，对于一个 $\texttt{?}$ 其可能存在于集合中间的任意位置，可能的相对位置个数为 $i-1$，那么对方案数产生翻 $(i-1)$ 倍的贡献。

那么总方案数显然为 $\displaystyle\prod^{n-1}_{i=1} (i-1)[s_i=\texttt{?}]$。

考虑先统计总方案数，如果将某一位的 $\texttt{<}$ 或 $\texttt{>}$ 改为 $\texttt{?}$ 就乘上 $i-1$，如果将某一位的 $\texttt{?}$ 改为 $\texttt{<}$ 或 $\texttt{>}$ 就乘上 $i-1$ 的逆元。

注意的点只有特判第一个字符的情况。

时间复杂度 $O(n+|V|),V=3\times 10^5$，表示值域。

没了？没了。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long MAXN=301000,Moder_=998244353;
long long inv[MAXN],n,m,ans,flag;
char s[MAXN];
long long poww(long long ta,long long tb)
{
	long long ans=1;
	while(tb>0)
	{
		if(tb&1)
		{
			ans*=ta;
			ans%=Moder_;
		}
		ta*=ta;
		ta%=Moder_;
		tb/=2;
	}
	return ans;
}
void init()
{
	long long i;
	for(i=1;i<=300000;i++)
	{
		inv[i]=poww(i,Moder_-2);
	}
	return;
}
int main()
{
	init();
	long long i,j,t;
	char c;
	ans=1;
	scanf("%lld %lld\n%s",&n,&m,s+1);
	for(i=2;i<=n-1;i++)
	{
		if(s[i]=='?')
		{
			ans=(ans*(i-1))%Moder_;
		}
	}
	if(s[1]=='?')
	{
		flag=0;
	}
	else
	{
		flag=1;
	}
	printf("%lld\n",ans*flag);
	for(i=1;i<=m;i++)
	{
		scanf("\n%lld %c",&t,&c);
		if(t==1)
		{
			if(c=='?'&&s[t]!='?')
			{
				flag=0;
			}
			else if(c!='?'&&s[t]=='?')
			{
				flag=1;
			}
		}
		else
		{
			if(c=='?'&&s[t]!='?')
			{
				ans=(ans*(t-1))%Moder_;
			}
			else if(c!='?'&&s[t]=='?')
			{
				ans=(ans*inv[t-1])%Moder_;
			}
		}
		s[t]=c;
		printf("%lld\n",ans*flag);
	}
	return 0;
}
```

---

## 作者：lfxxx (赞：0)

考虑倒着删数。

加入是大于或者小于号，只有一种删除方法，否则假若当前剩下 $x$ 个数就有 $x-2$ 种删除方法，直接以此计数即可。

记得特判第一个只能是大于或者小于，否则方案数为 $0$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define mod 998244353
int qpow(int a,int b){
    if(b==0) return 1;
    if(b==1) return a%mod;
    int res=qpow(a,b/2);
    res=(res*res)%mod;
    if(b%2==1) res=(res*a)%mod;
    return res;
}
int n,m;
const int maxn = 3e5+114;
char opt[maxn];
int ans;
signed main(){
    //freopen("Cbig.in","r",stdin);
    //freopen("Cbig.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m;
    ans=1;
    for(int i=2;i<=n;i++) cin>>opt[i];
    for(int i=3;i<=n;i++) if(opt[i]=='?') ans=(ans*(i-2))%mod;
    cout<<ans*(opt[2]!='?')<<'\n';
    while(m--){
        int i;
        char c;
        cin>>i>>c;
        i++;
        if(i>2){
            if(opt[i]=='?') ans=(ans*qpow(i-2,mod-2))%mod;
        }
        opt[i]=c;
        if(i>2){
            if(opt[i]=='?') ans=(ans*(i-2))%mod;
        }
        cout<<ans*(opt[2]!='?')<<'\n';
    }
    return 0;
}
```


---

## 作者：Hisaishi_Kanade (赞：0)

-52，-52，-52。

卑微的世界，活不下去了。

- - - 

考虑对于一个给定的字符串有多少种构造方案。

一个比较显然的特判是 $s_1$ 为 `?` 时显然方案数为 $0$。

然后钦定前 $i$ 个字符（我使用 $1$ 下标存储字符串）恰好添加了 $1\sim i$ 这个排列。这个时候你会发现，如果加入第 $i+1$ 个字符：

+ 为 `<`，此时只有一种添加方案。$ans\gets ans\times 1$。其实可以完全当成前面的每个方案中，每个数向右平移一个，显然是一一对应的。
+ 为 `>`，同理。
+ 为 `?`，注意到已经有 $i$ 个数，则恰好有 $(i-1)$ 个空挡，显然两边不能选。也可以理解为前面的方案中大于等于加入的这个数的全部平移一位，依然一一对应。$ans\gets ans\times (i-1)$。

那么修改也是显然的啊，乘一个逆元就好了。

总复杂度 $O(n+q)$。

```cpp
#include <bits/stdc++.h>
#define per(i, l, r) for(i=l; i<r; ++i)
#define rep(i, l, r) for(i=l; i<=r; ++i)
#define req(i, r, l) for(i=r; i>=l; --i)
using namespace std;
using ll=long long;
static const int Buf_size=1<<25;
static char _c; static int _x;
static const signed int base_10=10, zero(48), nine(57), flag_signed(45);
static char buf[Buf_size], *p1=buf, *p2=buf;
#define digit() (zero<=_c&&_c<=nine)
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,Buf_size,stdin),p1==p2)?EOF:*p1++)
inline int read(){_x=0;_c=getchar();while(!digit()){_c=getchar();}while(digit()){_x=_x*10+(_c^zero);_c=getchar();}return _x;}
const int N=3e5+5, inf=2e9, p=998244353;
const ll illf=1e18;
ll inv[N];
char str[N]; char c;
int qt, n, i, j, k, q, pos;
int main()
{
	scanf("%d %d %s", &n, &q, str+1);
	inv[1]=1;
	rep(i, 2, n) inv[i]=(p-p/i)*inv[p%i]%p;
	ll res=1;
	rep(i, 2, n) if(str[i]=='?') (res*=i-1)%=p;
	if(str[1]=='?') puts("0");
	else printf("%lld\n", res);
	while(q--)
	{
		scanf("%d %c", &pos, &c);
		if(pos!=1)
		{
			if(str[pos]=='?' && c!='?')
				res=(res*inv[pos-1])%p;
			if(str[pos]!='?' && c=='?')
				res=(res*(pos-1))%p;
		}
		str[pos]=c;
		if(str[1]=='?') puts("0");
		else printf("%lld\n", res);
//		puts(str+1);
	}
}
```

---

## 作者：KingPowers (赞：0)

[题目链接](https://www.luogu.com.cn/problem/CF1886D)

有点诈骗题的感觉了嗷。

你会发现直接维护这么个东西是很抽象的，正难则反，我们不妨将整个插入过程倒着考虑，理解成删除的过程。

倒序遍历整个字符串，对 $s_i$ 分类讨论一下：

- 如果当前遇到了 `>`，那么我们只能将当前的最大值给删掉，对答案产生 $1$ 系数的贡献。

- 如果当前遇到了 `<`，同理。

- 如果当前遇到了 `?`，那么设当前有 $x$ 个数，那么我们去掉最大值和次大值之后可以选择剩下的 $x-2$ 个数给删掉，而 $x=i+1$，所以对答案产生 $i-1$ 系数的贡献。

整理一下，不难发现答案为

$$
\prod_{i=2}^{n-1}(i-1)\times[s_{i}=\text{?}]
$$

那么对于修改操作，如果改掉了一个问号，我们就先乘上其对应的逆元就好了。

$s_1$ 为 `?` 时答案为 $0$，这个需要判掉。

时间复杂度如果预处理逆元可以 $O(n+q)$，但没必要。

```cpp
#include<bits/stdc++.h>
#define int long long
#define For(i,a,b) for(int i=(a);i<=(b);i++)
#define Rof(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int N=5e5+5;
const int mod=998244353;
int n,q,ans=1;
char s[N];
int qpow(int x,int y,int res=1){
    for(;y;x=x*x%mod,y>>=1)
        if(y&1) res=res*x%mod;
    return res;
}
void Main(){
    cin>>n>>q>>(s+1);
    For(i,2,n) if(s[i]=='?') ans=ans*(i-1)%mod;
    if(s[1]=='?') cout<<0<<'\n';
    else cout<<ans<<'\n';
    while(q--){
        int pos;char c;
        cin>>pos>>c;
        if(pos!=1){
            if(s[pos]=='?') ans=ans*qpow(pos-1,mod-2)%mod;
            if(c=='?') ans=ans*(pos-1)%mod;
        }
        s[pos]=c;
        if(s[1]=='?') cout<<0<<'\n';
        else cout<<ans<<'\n';
    }
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int T=1;//cin>>T;
    while(T--) Main();
    return 0;
}
```


---

