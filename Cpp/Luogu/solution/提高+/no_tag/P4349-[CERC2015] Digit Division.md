# [CERC2015] Digit Division

## 题目描述

给定一个长度为 $n$ 的十进制数字序列。需要将该序列划分为一个或多个连续的子序列，使得每个子序列在被解释为十进制数时都能被给定的整数 $m$ 整除。

求不同的划分方式的数量，结果对 $10^9 + 7$ 取模。当判断两个划分是否不同的时候，我们只考虑子序列边界的位置，而不是数字本身。例如，划分 $2|22$ 和 $22|2$ 被认为是不同的。

## 说明/提示

Central Europe Regional Contest 2015 Problem D。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
4 2
1246```

### 输出

```
4```

## 样例 #2

### 输入

```
4 7
2015```

### 输出

```
0```

# 题解

## 作者：Genius_Star (赞：6)

### 思路：

简单题，考虑找到可以分割的点的个数 $x$，每一个点可以选择分割或者不分割，总方案数为 $2^x$。（运用快速幂）

注意到，每个区间都被 $m$ 整除，则选几个区间合并起来也能被 $m$ 整除，于是可以从左到右扫一遍，如果当前 $1 \sim i$ 的数字能被 $m$ 整除，则该点可以作为分割点。

但是如果最后一个点是分割点的话，分割或者不分割是一样的，所以不算这个答案；无解的话是整个数字都不被 $m$ 整除的情况。

时间复杂度为 $O(N + \log{p})$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=300300,mod=1e9+7; 
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll n,m,sum,ans;
char c;
ll qpow(ll sum,ll b){
	ll ans=1;
	while(b){
		if(b&1ll)
		  ans=(ans*sum)%mod;
		sum=(sum*sum)%mod;
		b>>=1ll;
	}
	return ans;
}
int main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++){
		scanf("%c",&c);
		sum=(sum*10%m+c-'0')%m;
		if(!sum)
		  ans++;
	}
	write(sum?0:qpow(2ll,ans-1));
	return 0;
}
```


---

## 作者：gxy001 (赞：4)

看到题的第一眼我是考虑 $\text{dp}$ 的，~~太菜没想到正解~~，设 $f_i$ 为在第 $i$ 位后分割的方案数，则有：

$$f_i=\sum\limits_{j=0}^{i-1}f_j[m\mid a_{j+1,i}]$$

其中 $a_{i,j}$ 表示从第 $i$ 位到第 $j$ 位组成的数字。

显然 $\mathrm{O(n^2)}$ 的 $\text{dp}$ 不能通过此题，考虑如何优化。

我们可以在 $\mathrm{O(n)}$ 的时间复杂度内预处理出所有最小的能被 $m$ 整除的区间，我们只需要考虑每个分割点即可。

这时我们可以发现，对于每个分割点，都可以选择分割或不分隔，由于

$$a \operatorname{mod}m=0,b\operatorname{mod}m=0$$

$$\text{有} (a\times10^k+b) \operatorname{mod}m=0$$

所以我们可以在所有分割点中选择任意几个分割，这方案数其实就是 $2^k$，$k$ 为分割点数量。 

Q：何时无解？

A：当整体无法被 $m$ 整除时，则无解。

### 代码

```cpp
#include<cstdio>
int n,m,aa,k;
char c[300010];
int pow(int x,int y){
	int res(1);
	while(y){
		if(y&1) res=1ll*res*x%1000000007;
		x=1ll*x*x%1000000007;
		y>>=1;
	}
	return res%1000000007;
}
int main(){
	scanf("%d%d%s",&n,&m,c);
	for(int i=0;i<n;i++){
		aa=(aa*10%m+c[i]-'0')%m;
		if(aa==0)++k;
	}
	if(aa) puts("0");
	else printf("%d\n",pow(2,k-1));
	return 0;
}
```

---

## 作者：姬小路秋子 (赞：4)

想想小学生是怎么做除法的，假设一个数为x*10+y（x即为十位，y即为个位），除以一个数z，那么做除法就是从高位到低位做，首先x除以z，然后再将它的余数*10再加上y，再除以z，即a[i]=(a[i-1]*10+a[i])%z，那么这样就可以用O(n)的时间从前往后扫一遍，求出哪些数能被m整除，答案即为2的这种数的个数-1次方（因为n位那个一定得选嘛，不选最后一个数就不能被m整除了）。
所以说最后判断一下整个数能否被m整除，如果不能就输出0（因为你怎么分也不行）。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,i,ans;
long long sum,t;
char s[1000001];
int main(){
	scanf("%d%d",&n,&m);
	scanf("%s",&s);
	for(i=0;i<n;i++){
		t=(t*10+s[i]-'0')%m;
		if(!t)ans++;
	}
	if(t){
		printf("0");
		return 0;
	}
	ans--;
	sum=1;t=2;
	while(ans>0){
		if(ans%2==1)sum=(sum*t)%1000000007;
		t=(t*t)%1000000007;
		ans/=2;
	}
	printf("%lld",sum);
}
```

---

## 作者：andysk (赞：2)

# Luogu4349 [CERC2015]Digit Division

### 题意

   有一个N位的数字，将其分割，保证每个区间里的数字可以被M整除。问有多少种方法，将答案对 $10^9 + 7$ 取余

### 题解

  刚开始看到这个题我还以为是个DP，跟那个[数字游戏]([https://www.luogu.org/problemnew/show/P1043](https://www.luogu.org/problemnew/show/P1043)) 还有点像的，后来发现不会搞看了一下题解然后开始往数学的方向想。

  思路其实还挺简单的。
  对于一个数 $m$ ,如果有 $m|a$ & $m | b$ 那么把ab连起来也有 $m|(a * \lceil log_{10}b\rceil + b$

  证明一下（Luogu上神仙的题解都没有证，可能是因为我TCL，还是证一下）:

$a, b$拼接以后的数是:$a * \lceil log_{10}b\rceil + b$

  设$p_1, p_2$分别为 $a$ 的一对非平凡因子

  $∵m|a$  

$∴m|p_1 * p_2$

  由此可得:$m|p_1 * p_2 * \lceil log_{10}b\rceil + b$

之后还有一个结论是，这个数可以被划分的方法有:$可以划分的位置个数2^{可以划分的位置个数-1}$
不证了，组合数学基础

还要注意的就是，最后一个区间如果不能被整除，那么答案应该为$0$

### Code
```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int SIZE = 300000 + 5;

int n, m;
char str[SIZE];

inline int read()
{
    char ch = getchar();
    int f = 1, x = 0;
    while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = (x << 1) + (x << 3) + ch - '0'; ch = getchar(); }
    return x * f;
}

inline LL Qpow(LL b, LL p, LL k)
{
    LL ans = 1, t = b;
    for ( ; p; p >>= 1, t = t * t % k)
        if (p & 1) ans = ans * t % k;
    return ans % k;
}

int main()
{
    int cur = 0, cnt = 0;
    n = read(), m = read();
    scanf("%s", str + 1);
    for (int i = 1; i <= n; i++)
    {   
        cur = ((cur << 1) + (cur << 3) + str[i] - '0') % m;
        cnt += (!cur);
    }
    printf("%lld", cur ? 0 : Qpow(2, cnt - 1, 1e9 + 7));
    return 0;
}


```


---

## 作者：FjswYuzu (赞：2)

每一个区间都能被m整除，那么几个相邻的区间合起来也一定能被整除，则这个数可以划分的方法有$2^x$个（x等于可以划分的次数-1）

证明过程极其简单，在下不多阐述

同时，特判最后一个区间能否被整除，如果不能，则该数不能被划分，输出0

同时，这道题要用到一个模板---[P1226 取余运算](https://www.luogu.org/problemnew/show/P1226) 这道题就AC了
```cpp
#include<cstdio>
#define MOD 1000000007//题目要求的“109+7”
int n,m,ans=-1;//因为这里ans已经设为-1，下面就不用ans--了
long long tot=1,check;
char str[1000005];
int main(){
    scanf("%d %d",&n,&m);
    scanf("%s",str);
    for(int i=0;i<n;i++)
    {
        check=(check*10+str[i]-'0')%m;
        if(!check)	ans++;//这一段的余数为0了，这段就必定能被整除，可以划分的次数就+1
    }
    if(check)	return printf("0")*0;//最右一个区间不可能被除尽时，这个数无论怎么划分都不能被整除
    tot=1,check=2;
    while(ans)
    {
        if(ans&1)	tot=(tot*check)%MOD;
        check=(check*check)%MOD;
        ans>>=1;
    }//这段代码看不懂的请转到P1226哦
    //求2的ans次方
    printf("%lld",tot);
    return 0;
}
```
~~怀疑这道题有恶意评分~~

---

## 作者：Anguei (赞：1)

假设 $m \mid a$ 且 $m \mid b$，那么 $a, b$ 两个数字拼接起来也一定被 $m$ 整除，即一定有 $m \mid \left(a \times \lceil\log_{10}b\rceil + b\right)$。这个很好理解，就不证明了。

于是我们就可以使用类似读入优化的办法，从左到右边读边取模，每当结果为零时，就意味着这个地方左边的数字区间可以被 $m$ 整除。那么根据上面的结论，这个位置无论割还是不割，都可以。

所以最终答案就是 $2^{\text{可以割的位置个数 - 1}}$。

最后特判一下：如果右半段模出来不为零（不能被整除），那么答案应该为零。

```cpp
int main() {
    int n = read(), m = read(), now = 0, cnt = 0;
    std::string s; std::cin >> s;
    rep(i, 1, n) {
        now = (now * 10 + s[i - 1] - 48) % m;
        cnt += (!now);
    }
    println(now ? 0 : qpow(2, cnt - 1));
}
```

---

## 作者：Link_Cut_Y (赞：0)

神题！

首先考虑到这样一个事实：不妨设 $a \bmod m = 0, b \bmod m = 0$，那么一定有 $(a \times 10 ^ t + b) \bmod m = 0$。换言之，两个数 $\bmod \,m$ 如果都是 $0$ 的话，他们拼起来也能够整除 $m$。

将 $m \mid \overline{a_1 a_2 \sim a_i}$ 的所有 $i$ 作为“分割点”，“分割点”的个数为 $s$。每个分割点选或不选构成 $2 ^ s$ 种方案，易得这些方案都是合法的。

需要注意的是，如果整个数字都不能被 $m$ 整除则方案数为 $0$。结尾的分割点没有作用。

```cpp
read(n, m); scanf("%s", s + 1);
int sum = 0, cnt = 0; rep(i, 1, n) {
	sum = (sum * 10 + s[i] - '0') % m;
	if (sum == 0 and i != n) cnt ++ ;
} if (sum != 0) puts("0");
else printf("%lld\n", qpow(2, cnt));
```

---

## 作者：Supor__Shoep (赞：0)

### $O(n^2)$ 做法

和大部分人最开始一样，我也想的是 DP。

设 $dp_i$ 表示用前面 $i$ 个字符拆分得到的答案。既然是统计方案数，我们肯定是根据前面的答案累加。考虑在 $[1,i-1]$ 中选择一个 $j$，如果 $[j+1,i]$ 的字符组成的数字能够被 $m$ 整除，那么 $dp_i$ 就可以累加一个 $dp_j$ 的值，因为如果当前区间满足条件，就相当于这里是一个可行的拆分，那么前面 $j$ 个字符得到的答案很明显也都可以成为累加的一部分。

假设 $flag_{j,i}$ 表示区间 $[j,i]$ 组成的数字是否可以被 $m$ 整除，$1$ 表示可以，$0$ 表示不可以。则有转移方程：

$$dp_i=
\sum _{j=1}^{i-1}dp_j
\times flag_{j+1,i}$$

那么答案就是在 $dp_{n}$ 这里了。

此做法时间复杂度为 $O(n^2)$，而 $n
\leq 3\times 10^5$，并且无法进行优化，所以 DP 只能进行骗分。

### $O(n)$ 做法

考虑运用数学运算进行求解。

设想一下，假如字符串的**前缀**组成的数字 $x$ 能够被 $m$ 整除会怎么样？如果整个字符串组成的数字 $sum$ 也能够被 $m$ 整除，那么这个前缀以后的所有字符组成的数字也必定可以被 $m$ 整除。即 $m\mid sum-x\times 10^{num}$，其中 $num$ 是**非前缀**的字符个数。这个是非常容易想到的一个式子。

那么这样的一个式子有什么用呢？既然前缀后面的数字可以被 $m$ 整除，那么我们能否按照相同的思路，在这之中进行拆分？假设后面的数字为 $sum$，在这个数字里面找一个前缀组成数字 $x$，由上文第一步推断知道 $m\mid sum$，如果此时 $m\mid x$，那么这个前缀后面的数字也可以被 $m$ 整除，这个思路和上文一模一样。

所以我们可以得出一个结论，如果整个字符串的某个前缀组成的数字能被 $m$ 整除，且整个字符串组成的数字能够被 $m$ 整除，那么此时这个前缀的**最后一个字符的下标处**就是一个可以进行拆分的地方。如果在这里进行拆分，那么前后的字符串也都会被 $m$ 整除，因此这里**一定会**被某一个拆分方式进行拆分。

所以我们可以找到所有被 $m$ 整除的前缀数字，记录下这样的前缀的个数 $res$。然后这个问题就转化成了对 $res$ 个可以拆分的地方进行**组合**。因为这里面的前缀会包括整个字符串，所以中间选择的拆分的地方有 $res-1$ 个。由于每个地方有**选与不选**的 $2$ 种可能，因此计算的答案就是 $2^{res-1}$ 次方。而求幂我们使用**快速幂**就可以了。

一定要注意，如果整个字符串组成的数字不能被 $m$ 整除，那么答案**一定**是 $0$，因为找不到任何一个拆分的地方，使得前后两个数字都能够被 $m$ 整除。

代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long//方案取模题，日常开 long long 
using namespace std;
const int MAXN=3e5+5;
const int MOD=1e9+7;
int n,m;
char s[MAXN];
int quick_pow(int x)//2^x的快速幂 
{
	int ans=1,sum=2;
	while(x)
	{
		if(x&1)	ans=ans*sum%MOD;
		sum=sum*sum%MOD;
		x>>=1;
	}
	return ans;
}
signed main()
{
	cin>>n>>m>>(s+1);
	int res=0,x=0;
	for(int i=1;i<=n;i++)	x=(x<<1)+(x<<3)+(s[i]^48),x%=m,res+=(!x);//计算可拆分地方的个数 
	if(x)	puts("0");//特判 
	else	cout<<quick_pow(res-1);//组合 
	return 0;
}
```

---

## 作者：Tx_Lcy (赞：0)

[更差的阅读体验](https://www.cnblogs.com/tx-lcy/p/16833361.html)

[题目传送门](https://www.luogu.com.cn/problem/P4349)

## 思路

以下纯考场思路。

今天模拟赛考到了这题的加强版，然后预处理写炸了，$100$ 变成 $70$，当是给 $\verb!CSP!$ 攒 $\verb!rp!$ 了。

首先一眼看到题目可能会没有思路，没什么关系，手推一个暴力 $\verb!DP!$，设 $f_i$ 表示以 $i$ 为结尾的划分方案数，显而易见的转移是：$f_i=\sum_{j=1}^{i-1} f_j$，其中满足 $j$ 至 $i$ 组成的数满足被 $m$ 整除。

这个东西似乎难以被优化，所以考虑打几个特殊性质。

若 $m=3$，显然上述转移柿子满足的条件是 $\sum_{k=j}^{i} a_k$ 是 $3$ 的倍数，设原序列的前缀和数组为 $sum_i$，则此问题等价于 $sum_i-sum_{j-1}$ 是 $3$ 的倍数。

不妨根据除 $3$ 的余数分类，显然 $sum_i$ 若能它之前的 $sum_j$ 转移过来必须满足它们除 $3$ 的余数相同，而我们又可以据此推得若 $sum_i$ 不是 $3$ 的倍数，$f_i$ 无法转移。

为什么呢，设 $sum_i$ 除三的余数为 $x$，其中 $x$ 不为 $0$，那么 $x$ 从 $i$ 之前的 $x$ 转移过来，如此往前推，必将找到一个点 $j$，使得 $j$ 前面不存在除 $3$ 余数为 $x$ 的数。

把这个东西推广一下，猜个结论，不难想到若 $1$ 至 $i$ 组成的数不是 $m$ 的倍数，那么无法转移。

这个东西证明也与 $3$ 的情况类似，不再赘述。

于是前缀和优化一下即可。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int const N=1e6+10;
int const mod=1e9+7;
int sum[N],f[N];
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int n,m;cin>>n>>m;
    string s;cin>>s;s=" "+s;
    sum[0]=f[0]=1;int res=0;
    //这里 res 表示前 i 位除 m 的余数，我们的考试题限制了区间长度只能为 l~r，我没有加上 1~l 的部分，于是挂分，警示后人！
    for (int i=1;i<=n;++i){
        res*=10;res+=(s[i]-'0');res%=m;
        if (!res) f[i]=sum[i-1];
        sum[i]=(sum[i-1]+f[i])%mod;
    }
    cout<<f[n]<<'\n';
    return 0;
}
```


---

## 作者：Otomachi_Una_ (赞：0)

首先给个小定理：

若 $m | a$ 且 $m|b$ ,则 $m|\overline{ab}$ ,这个证明很简单，略去。

对于分割的数，每两个相邻的数间都可以割或者不割，但是如果一个区间要割，必须保证前面的数是 $m$ 的倍数，不然答案必然不合法。

用 $k$ 来记录满足这些要求的分割点个数，答案就是 $2^{k-1}$。

特别的，如果这个数本身就不是 $m$ 的倍数，无论怎么分割都不可能满足要求。

## _Code_

```cpp
#include<iostream>
#include<cstring>
using namespace std;
#define ll long long
const int MOD=1e9+7;
int n,m;
string s;
ll k=1;
ll t=0;
int main(){
    cin>>n>>m>>s;
    for(int i=0;i<s.length();i++){
   		t=(10*t+s[i]-'0')%m;
   		if(t==0)
   			k=(2*k)%MOD;
    }
    if(t!=0) cout<<"0";
    else if(k%2==0) cout<<k/2;
    else cout<<(k+MOD)/2;
    return 0;
}
```


---

