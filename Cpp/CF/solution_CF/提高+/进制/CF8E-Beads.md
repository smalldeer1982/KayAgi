# Beads

## 题目描述

One Martian boy called Zorg wants to present a string of beads to his friend from the Earth — Masha. He knows that Masha likes two colours: blue and red, — and right in the shop where he has come, there is a variety of adornments with beads of these two colours. All the strings of beads have a small fastener, and if one unfastens it, one might notice that all the strings of beads in the shop are of the same length. Because of the peculiarities of the Martian eyesight, if Zorg sees one blue-and-red string of beads first, and then the other with red beads instead of blue ones, and blue — instead of red, he regards these two strings of beads as identical. In other words, Zorg regards as identical not only those strings of beads that can be derived from each other by the string turnover, but as well those that can be derived from each other by a mutual replacement of colours and/or by the string turnover.

It is known that all Martians are very orderly, and if a Martian sees some amount of objects, he tries to put them in good order. Zorg thinks that a red bead is smaller than a blue one. Let's put 0 for a red bead, and 1 — for a blue one. From two strings the Martian puts earlier the string with a red bead in the $ i $ -th position, providing that the second string has a blue bead in the $ i $ -th position, and the first two beads $ i-1 $ are identical.

At first Zorg unfastens all the strings of beads, and puts them into small heaps so, that in each heap strings are identical, in his opinion. Then he sorts out the heaps and chooses the minimum string in each heap, in his opinion. He gives the unnecassary strings back to the shop assistant and says he doesn't need them any more. Then Zorg sorts out the remaining strings of beads and buys the string with index $ k $ .

All these manupulations will take Zorg a lot of time, that's why he asks you to help and find the string of beads for Masha.

## 说明/提示

Let's consider the example of strings of length 4 — 0001, 0010, 0011, 0100, 0101, 0110, 0111, 1000, 1001, 1010, 1011, 1100, 1101, 1110. Zorg will divide them into heaps: {0001, 0111, 1000, 1110}, {0010, 0100, 1011, 1101}, {0011, 1100}, {0101, 1010}, {0110, 1001}. Then he will choose the minimum strings of beads in each heap: 0001, 0010, 0011, 0101, 0110. The forth string — 0101.

## 样例 #1

### 输入

```
4 4
```

### 输出

```
0101
```

# 题解

## 作者：zhylj (赞：8)

### Solution

这题并不需要数位 dp，qwq.

首先串的第一个位置显然是 $0$，则反串的条件可以满足。

考虑枚举（前后均指从左到右数）前 $\left\lfloor \dfrac n2\right\rfloor$ 位，设这些位组成的二进制数位 $i$。

若 $n$ 为偶数，考虑后 $\dfrac n2$ 位一共有多少个合法方案：
- 若最后一位为 $0$，则后半串的逆序串字典序恒小于取反后的逆序串，只需考虑不取反的逆序串即可。则第 $\dfrac n2+1$ 到倒数第二位的逆序串必须小于等于 $i$，显然这样的情况数共有 $2^{n-1}-i$（总数减去小于 $i$ 的情况数）（当然，若 $i=0$ 还需特判全 $0$ 串）
- 若最后一位为 $1$，则取反后的逆序串恒小于未取反的，取反后一共 $2^{n-1}-i$ 种，则取反前总数也为 $2^{n-1}-i$。

若 $n$ 为奇数，则需要考虑中间位置的贡献。要特判如果后面的最后一位为 $1$，则中间那位不能为 $0$.

这样，我们可以花 $\mathcal O(2^{\left\lfloor \frac n2\right\rfloor})$ 的时间确定第 $k$ 大的前 $\left\lfloor \dfrac n2\right\rfloor$ 位，再暴力确定后面的位就好了。我写的比较丑，复杂度多了个 $n$，由于常数小，跑的过去。实际上可以预处理 rev 来做到 $\mathcal O(2^{\left\lfloor \frac n2\right\rfloor})$ 的时间复杂度。

### Code

```cpp
int n, f1; ll k; bool flag;
void Print(int x) {
	for(int i = n / 2 - 1; ~i; --i)
		printf("%d", (x >> i) & 1);
}
inline int Rev(int x) {
	int ret = 0;
	for(int i = 0; i < n / 2; ++i)
		ret |= ((x >> i) & 1) << (n / 2 - 1 - i);
	return ret;
}
int main() { 
	rd(n, k); f1 = (1 << (n / 2)) - 1;
	for(int i = 0; i < 1 << (n / 2 - 1); ++i) {
		int siz = ((1 << (n / 2 - 1)) - i) << (1 + (n & 1));
		siz -= !i + (n & 1);
		if(k > siz) k -= siz;
		else {
			flag = true;
			for(int j = 1; j < 1 << (n / 2); ++j) {
				if(Rev(j) >= i && Rev((j ^ f1)) >= i) --k;
				if(!k) {
					Print(i);
					if(n & 1) printf("0");
					Print(j);
					printf("\n");
					break;
				}
			}
			if((n & 1) && k) {
				for(int j = 0; j < 1 << (n / 2); ++j) {
					if(Rev(j) >= i && Rev((j ^ f1)) > i) --k;
					if(!k) {
						Print(i);
						printf("1");
						Print(j);
						printf("\n");
						break;
					}
				}
			}
		}
		if(flag) break;
	}
	if(!flag) printf("-1\n");
}
```



---

## 作者：nobody_knows (赞：7)

数位dp
显然满足题意的二进制串的首位必须是0。考虑一位一位地确定答案串。假设已经确定了答案串的前k位，我们假设第k+1位是0，则要设法统计出满足条件的串的个数s。
那么如果s<m，则答案串第k+1位为1，同时m=m−s；否则答案串第k+1位为0。于是问题转化为，统计所有长度为n的，前缀为prefix的二进制串中，满足题目要求的串的个数。
这是一类与数位有关的统计问题，于是很容易想到数位dp
。那么考虑dp[i][j][rev][inv]表示，当前已经确定了前i位和末j位，rev表示前i位与末j位的逆序是否相等，inv表示前i位与末j位的逆序取反后是否相等。状态转移比较显然，我们枚举第i+1位和第n−i位的取值，如果它满足prefix的限制，且新的串没有违反题目要求（可以利用rev和inv和取值判断）， 那么更新rev和inv的状态，并累加到对应的新状态上。

```
#include<cmath>
#include<math.h>
#include<ctype.h>
#include<algorithm>
#include<bitset>
#include<cassert>
#include<cctype>
#include<cerrno>
#include<cfloat>
#include<ciso646>
#include<climits>
#include<clocale>
#include<complex>
#include<csetjmp>
#include<csignal>
#include<cstdarg>
#include<cstddef>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<cwchar>
#include<cwctype>
#include<deque>
#include<exception>
#include<fstream>
#include<functional>
#include<iomanip>
#include<ios>
#include<iosfwd>
#include<iostream>
#include<istream>
#include<iterator>
#include<limits>
#include<list>
#include<locale>
#include<map>
#include<memory>
#include<new>
#include<numeric>
#include<ostream>
#include<queue>
#include<set>
#include<sstream>
#include<stack>
#include<stdexcept>
#include<streambuf>
#include<string>
#include<typeinfo>
#include<utility>
#include<valarray>
#include<vector>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
using namespace std;

typedef long long ll;

#define pb push_back
#define mp make_pair
#define x first
#define y second

const ll inf=2147483647;

//codeforces 8E

ll read()
{
    ll x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

void print(ll x)
{
    if(x<0)putchar('-'),x=-x;
    short a[20]= {},sz=0;
    while(x>0)a[sz++]=x%10,x/=10;
    if(sz==0)putchar('0');
    for(int i=sz-1; i>=0; i--)putchar('0'+a[i]);
}

ll dp[55][5][5];
ll a[55];
ll n,k;

ll dfs(ll pos,ll lim1,ll lim2){
    if(pos<n-pos+1) return 1;
    if(dp[pos][lim1][lim2]>=0) return dp[pos][lim1][lim2];
    
    ll ans=0;
    for(ll i=0;i<=1;i++){
        if(a[pos]==i || a[pos]==-1){
            for(ll j=0;j<=1;j++){
                if(a[n-pos+1]==j || a[n-pos+1]==-1){
                    if(lim1 && i>j || lim2 && i>!j || pos==n-pos+1 && i!=j) continue;
                    ans=ans+dfs(pos-1,lim1&&(i==j),lim2&&(i!=j));
                }
            }
        }
    }
    
    return dp[pos][lim1][lim2]=ans;
}



int main(){
    n=read(),k=read();
    memset(a,-1,sizeof(a));
    memset(dp,-1,sizeof(dp));
    k++;
    a[n]=0;
    if(dfs(n,1,1)<k){
        puts("-1");
        return 0;
    }
    cout<<0;
    for(ll i=n-1;i>=1;i--){
        a[i]=0;
        memset(dp,-1,sizeof(dp));
        ll nw=dfs(n,1,1);
    //    cout<<nw<<endl;
        if(nw<k){
            a[i]=1;
            cout<<1;
            k-=nw;
        }
        else{
            cout<<0;
        }
    }
    return 0;
}
```

---

## 作者：tzc_wk (赞：5)

> Codeforces 8E

> 题意：给出两个整数 $n,k$，求出从小到大第 $k$ 个满足以下要求的字符串：

> 1. 该字符串是 $01$ 串

> 2. 该字符串中既包含 $0$ 也包含 $1$。

> 3. 该字符串的字典序不能超过它的反转（将所以 $0$ 变成 $1$，$1$ 变成 $0$）、它的逆序（将整个字符串翻转过来）、它的反转+逆序（两者的结合）

> $1 \leq n \leq 50$，$1 \leq k \leq 10^{16}$

数位 $dp$。

很奇怪这道题 CF 上难度评分 $2600$ 洛谷上才蓝。

我么再一次地观察这道题的三个条件：

~~对于第一个，没什么好说的~~

对于第二个，实际上只是去掉一个 $\begin{matrix}\underbrace{000\dots0}\\n\end{matrix}$，只需将 $k$ 加一就行了。

关键就是这个第三个条件。不难发现，一个字符串 $s$ 的字典序大于它的反转，那么一定大于它的逆序、反转+逆序之一。原因非常简单——一个字符串的字典序大于它的反转，说明第一位是 $1$，如果最后一位是 $0$，则 $s$ 的字典序会大于 $s$ 逆序的字典序，如果最后一位是 $1$，则 $s$ 的字典序会大于 $s$ 反转+逆序的字典序。因此我们可以忽略这个条件。

由于是找字典序第 $k$ 小的字符串 $s$，因此我们考虑第一位到第 $n$ 位一位一位地填 $0/1$，假设现在填第 $i$ 位，那么我们固定住前 $i-1$ 位，之前我们求得的第 $i$ 位填 $a_i$。那么我们可以用数位 $dp$ 求出第 $1$ 位填 $s_1$，第 $2$ 位填 $s_2$，$\dots$ ，第 $i-1$ 位填 $s_{i-1}$，第 $s$ 位填 $0$ 的方案数，设其为 $sum$，如果 $k \leq sum$，那么我们更新 $s_i=0$，否则令 $k=k-sum$，$s_i=1$。最后的 $s$ 就是答案。

那么怎么求方案数呢？这就要用到数位 $dp$ 了，设 $dp_{i,j,k}$ 为：

- 填好了前 $i$ 位和后 $i$ 位，前 $i$ 位与后 $i$ 位组成的字串相等的情况为 $j$（$1$ 表示相等，$0$ 表示不相等），前 $i$ 位与后 $i$ 位的反转组成的字串相等的情况为 $k$ 的方案数。

假设我们已经求出了 $dp_{i,j,k}$，我们枚举**从左往右数**第 $i+1$ 位填的数和**从右往左数**第 $i+1$ 位填的数，假设分别为 $x$，$y$，那么这个填法是合法的，当且仅当：

- 从左往右数第 $i+1$ 个数没有限制，或者 $x$ 与从左往右数第 $i+1$ 个数所限制的数 $=x$

- 从右往左数第 $i+1$ 个数没有限制，或者 $x$ 与从右往左数第 $i+1$ 个数所限制的数 $=y$

- $j=0$，或者 $x \leq y$

- $k=0$，或者 $x+y \leq 1$

- 如果从右往左数第 $i+1$ 个数与从右往左数第 $i+1$ 个数表示的位置相同，那么 $x=y$（这一点巨坑无比）

最终方案数就是 $dp_{0,1,1}$。

```cpp
//Coded by tzc_wk
/*
数据不清空，爆零两行泪。
多测不读完，爆零两行泪。
边界不特判，爆零两行泪。
贪心不证明，爆零两行泪。
D P 顺序错，爆零两行泪。
大小少等号，爆零两行泪。
变量不统一，爆零两行泪。
越界不判断，爆零两行泪。
调试不注释，爆零两行泪。
溢出不 l l，爆零两行泪。
*/
#include <bits/stdc++.h>
using namespace std;
#define fi			first
#define se			second
#define fz(i,a,b)	for(int i=a;i<=b;i++)
#define fd(i,a,b)	for(int i=a;i>=b;i--)
#define foreach(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define all(a)		a.begin(),a.end()
#define giveup(...) return printf(__VA_ARGS__),0;
#define fill0(a)	memset(a,0,sizeof(a))
#define fill1(a)	memset(a,-1,sizeof(a))
#define fillbig(a)	memset(a,0x3f,sizeof(a))
#define fillsmall(a) memset(a,0xcf,sizeof(a))
#define mask(a)		(1ll<<(a))
#define maskx(a,x)	((a)<<(x))
#define _bit(a,x)	(((a)>>(x))&1)
#define _sz(a)		((int)(a).size())
#define filei(a)	freopen(a,"r",stdin);
#define fileo(a)	freopen(a,"w",stdout);
#define fileio(a) 	freopen(a".in","r",stdin);freopen(a".out","w",stdout)
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#define put(x)		putchar(x)
#define eoln        put('\n')
#define space		put(' ')
#define y1			y_chenxiaoyan_1
#define y0			y_chenxiaoyan_0
#define int long long
typedef pair<int,int> pii;
inline int read(){
	int x=0,neg=1;char c=getchar();
	while(!isdigit(c)){
		if(c=='-')	neg=-1;
		c=getchar();
	}
	while(isdigit(c))	x=x*10+c-'0',c=getchar();
	return x*neg;
}
inline void print(int x){
	if(x<0){
		putchar('-');
		print(abs(x));
		return;
	}
	if(x<=9)	putchar(x+'0');
	else{
		print(x/10);
		putchar(x%10+'0');
	}
}
inline int qpow(int x,int e,int _MOD){
	int ans=1;
	while(e){
		if(e&1)	ans=ans*x%_MOD;
		x=x*x%_MOD;
		e>>=1;
	}
	return ans;
}
int n=read(),k=read(),a[55];
int dp[55][2][2];
inline int dfs(int l,int r,bool lim1,bool lim2){
	if(~dp[l][lim1][lim2])	return dp[l][lim1][lim2];
	if(l+1>r-1)				return 1;
	int ans=0;
	dp[l][lim1][lim2]=0;
	for(int k1=0;k1<2;k1++){
		if((a[l+1]==k1||a[l+1]==-1))
		for(int k2=0;k2<2;k2++){
			if(l+1==r-1&&k1!=k2)	continue;
			if((a[r-1]==k2||a[r-1]==-1)){
				if((!lim1||(k1<=k2))&&(!lim2||(k1<=1-k2))){
					ans+=dfs(l+1,r-1,lim1&(k1==k2),lim2&(k1!=k2));
				}
			}
		}
	}
	dp[l][lim1][lim2]=ans;
//	cout<<l<<" "<<r<<" "<<lim1<<" "<<lim2<<" "<<ans<<endl;
	return ans;
}
signed main(){
	fill1(a);
	fill1(dp);k++;
//	cout<<dfs(0,n+1,1,1)<<endl;
	if(dfs(0,n+1,1,1)<k){
		return puts("-1"),0;
	}
	fz(i,1,n){
		fill1(dp);
		a[i]=0;
		int sum=dfs(0,n+1,1,1);
//		cout<<sum<<" "<<k<<endl;
		if(sum<k){
			k-=sum;a[i]=1;
		}
	}
//	if(k>0){
//		puts("-1");
//		return 0;
//	}
	fz(i,1,n)	putchar(a[i]^48);
	return 0;
}
```

---

## 作者：liangbowen (赞：1)

[blog](https://www.cnblogs.com/liangbowen/p/17837299.html)。抽象意义上单杀了。

---

首先第一位必定为 $0$，然后取反串就不用去考虑了。

$n\le50$，考虑爆搜。搜整个串的前一半（设半长为 $M=\left\lfloor\dfrac n2\right\rfloor$，前一半的串**在十进制下**值为 $v$），后半段的数量可以计算：

+ 整个串最后一位是 $0$，只需满足逆序串。$n$ 为偶数时方案数为 $(2^{M-1}-v)$，$n$ 为奇数时方案数为 $2(2^{M-1}-v)$。
+ 整个串最后一位是 $1$，只需满足逆序取反串。$n$ 为偶数时方案数为 $(2^{M-1}-v)$，$n$ 为奇数时方案数为 $(2^{M-1}-v-1)$。
+ 总的来说，$n$ 为偶数时方案数为 $2(2^{M-1}-v)$，$n$ 为奇数时方案数为 $2(2^{M-1}-v)+(2^{M-1}-v-1)$。

持续累加合法数量，显然可以找到前一半的答案。然后爆搜后一半的答案即可。

一些细节：全选 $0$ 是不合法的，为了方便可以在最开始 $k\gets k+1$；维护串时请在全局用数组模拟，[use string record](https://codeforces.com/contest/8/submission/232938708)。

[code](https://codeforces.com/contest/8/submission/232969677)，时间复杂度 $O(n2^n)$，瓶颈在后半段的爆搜，替换成二分可以做到 $O(2^n)$。

---

## 作者：盧鋅 (赞：1)

首先说明三个标记：
- $A^R$ 为A的逆序串
- $A^T$ 为A的取反串
- $A^{RT}=A^{TR}$ 为A的逆序取反串。

我们可以得到一个结论，那就是：

对于$A,A^R,A^T,A^{RT}$中，最多只有一个满足条件，至于证明可以考虑，大小关系,好像没什么用。

考虑$A\le A^T$,产生的约束：

- A[1]=0

考虑$A\le A^R$,产生的约束：

- if A[1]=0 -> A[n]=0/1

考虑$A\le A^{RT}$,产生的约束：

- if A[1]=0 -> A[n]=0/1;

从第一位以后$A\le A^T$不产生约束：

如果A[n]=0,则$A\le A^{RT}$不产生约束:

记新字符串为B,A=0B0

考虑$B\le B^R$,产生的约束：

- B[1]=B[n]=0/1 则可以进行递归
- B[1]=0,B[n]=1 则记新字符串D,B=0D1

如果A[n]=1,则$A\le A^{R}$不产生约束:

记新字符串为C,A=0C1

考虑$C\le C^{RT}$,产生的约束：

- C[1]^C[n]=1 则可以进行递归
- C[1]=1,C[n]=0 则记新字符串为D,C=1D0

那么对于D的计数，设D有x位，我们可以得到D的数量有$2^x$个

我们发现其实B和C在本质上是一样的，所以我们可以用同一种方式统计。

奇数长度和偶数长度在dp的方式是一样的，只需要考虑中心位置即可。

需要注意的是，长度为1的B和D串中心可以为0/1，长度为1的A和C串中心只能为0。

假设已经计算出来了，上边两个B,C的数量，从根本上并不能计算出答案。

我们可以讲BC合并，显然这是不难的，只需要讨论下某一位是1还是0就好了。

那么就计算出了前i位填1/0的方案数，假如单独进行奇偶讨论的话，处理到的范围是n/2上取整,否则为n/2下取整，但是仍然确定不出后边一半的确切取值，暴力即可

---

## 作者：kczno1 (赞：1)

串$<=$取反串 $<=>$ 第一位是$0$  
当串尾为$0$时，只需满足串<逆序串;  
当串尾为$1$时，只需满足串<逆序取反串;  
而且两者方案其实是一一对应的。  
当串前一半确定后，方案数是可以$O(1)$算的。  
所以可以$O(2^{n/2})$枚举(也可以二分)  
然后现在问题就是后一半  
也可以$O(2^{n/2})$枚举，  
同时维护逆序串  
总时间$O(2^{n/2})$  
```cpp
//by kcz 1552920354@qq.com
//if you find any bug in my code
//please tell me
#include<bits/stdc++.h>
using namespace std;

template <typename T> void chmin(T &x,const T &y)
{
	if(x>y)x=y;
}
template <typename T> void chmax(T &x,const T &y)
{
	if(x<y)x=y;
}
typedef long long ll;
typedef pair<int,int> pii;
#define rep(i,l,r) for(int i=l;i<=r;++i)
#define per(i,r,l) for(int i=r;i>=l;--i)
#define pb push_back
#define mp make_pair
#define gc (c=getchar())
int read()
{
    char c;
    while(gc<'-');
    if(c=='-')
    {
        int x=gc-'0';
        while(gc>='0')x=x*10+c-'0';
        return -x;
    }
    int x=c-'0';
    while(gc>='0')x=x*10+c-'0';
    return x;
}
#undef gc
int n;ll k;
void write(const ll &s)
{
	per(i,n-1,0)
	if((s>>i)&1)putchar('1');
	else putchar('0');
}
namespace ou
{
void solve()
{
	int m=n/2-1;
	int u=1<<m;
	int i=0,f;
	for(;i<u;++i)
	{
		f=2*(u-i);
		if(k>f)k-=f;
		else break;
	}
	if(i>=u)
	{
		puts("-1");
		return ;
	}
	int ans1=i;
	int ans2;
	int j=0,rev=0;
	++m;u*=2;
	int r=u-1-i;
	while(1)
	{
		if(rev>=i&&rev<=r)
		{
			if(!--k)break;
		}
		int low=0;
		for(;j&(1<<low);++low)
			rev-=1<<m-1-low;
		rev+=1<<m-1-low;
		++j;
	}
	ans2=j;
	write(((ll)ans1<<m)+ans2);	
}
};
namespace ji
{
void solve()
{
	int m=n/2-1;
	int u=1<<m;
	int i=0,f;
	for(;i<u;++i)
	{
		f=4*(u-i)-1;
		if(k>f)k-=f;
		else break;
	}
	if(i>=u)
	{
		puts("-1");
		return ;
	}
	f=(f+1)/2;
	int ans1=i,ans2;
	ans1*=2;
		int j=0,rev=0;
		++m;u*=2;
		int r=u-1-i;
	if(k>f)
	{
		k-=f;
		++ans1;
		--r;
	}
		while(1)
		{
			if(rev>=i&&rev<=r)
			{
				if(!--k)break;
			}
			int low=0;
			for(;j&(1<<low);++low)
				rev-=1<<m-1-low;
			rev+=1<<m-1-low;
			++j;
		}
		ans2=j;
	write(((ll)ans1<<m)+ans2);	
}
};
int main()
{
	freopen("1.in","r",stdin);//freopen("1.out","r",stdin);
	cin>>n>>k;
	++k;
	if(n%2==0)ou::solve();
	else ji::solve();
}

```

---

