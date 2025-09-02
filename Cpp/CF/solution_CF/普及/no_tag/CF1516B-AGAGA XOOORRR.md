# AGAGA XOOORRR

## 题目描述

Baby Ehab is known for his love for a certain operation. He has an array $ a $ of length $ n $ , and he decided to keep doing the following operation on it:

- he picks $ 2 $ adjacent elements; he then removes them and places a single integer in their place: their [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR). Note that the length of the array decreases by one.

Now he asks you if he can make all elements of the array equal. Since babies like to make your life harder, he requires that you leave at least $ 2 $ elements remaining.

## 说明/提示

In the first sample, he can remove the first $ 2 $ elements, $ 0 $ and $ 2 $ , and replace them by $ 0 \oplus 2=2 $ . The array will be $ [2,2] $ , so all the elements are equal.

In the second sample, there's no way to make all the elements equal.

## 样例 #1

### 输入

```
2
3
0 2 2
4
2 3 1 10```

### 输出

```
YES
NO```

# 题解

## 作者：江户川·萝卜 (赞：7)

这里提供一个比较新颖且好写的思路，且时间复杂度为 $O(tn)$。

---

前面思路与 Cry_For_theMoon 大佬一致。

就是设最后剩下的数为若干个 $s$。

考虑所有数的异或和 $S$。

因为异或具有结合性，容易想到 $S=s \operatorname{xor} s \operatorname{xor} s \operatorname{xor} \cdots \operatorname{xor} s$

根据 $s\operatorname{xor}s=0$，当 $s$ 个数为偶数时 $S=0$，否则 $S=s$。

当 $S=0$ 时：

$$S=a_1\operatorname{xor}a_2\operatorname{xor}\cdots\operatorname{xor}a_n$$
$$(a_1\operatorname{xor}a_2\operatorname{xor}\cdots a_i)\operatorname{xor}(a_{i+1}\operatorname{xor}a_{i+2}\operatorname{xor}\cdots a_n)=0$$

由 $x\operatorname{xor}x=0$ 反推得 $(a_1\operatorname{xor}a_2\operatorname{xor}\cdots a_i)=(a_{i+1}\operatorname{xor}a_{i+2}\operatorname{xor}\cdots a_n)$。

即任意找一个分界点两边异或和始终相等，满足题意，直接输出 `YES`。

---
下面重点讨论 $S\not=0$ 的情况。

此时可以确定各块的异或和就等于 $S$。

那么很简单，直接依次异或一下，如果累计出现 $S$ 的个数（当然每次出现后要清零）。

最后判断一下即可。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int a[2005];
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		int n;
		scanf("%d",&n);
		int x=0;
		for(int i=1;i<=n;i++) scanf("%d",&a[i]),x^=a[i];
		if(x==0) puts("YES");
		else{
			int cnt=0,cur=0;
			for(int i=1;i<=n;i++){
				cur^=a[i];
				if(cur==x) cnt++,cur=0;
			}
			if(cnt>=2) puts("YES");
			else puts("NO");
		}
	}
	return 0;
}
```

---

## 作者：Priori_Incantatem (赞：5)

[题目链接](https://www.luogu.com.cn/problem/CF1516B)  
[在我的Blog查看](https://blog.csdn.net/Brian_Pan_/article/details/115999951)

### 题目大意

给出一个长度为 $n$ 的序列，可以进行若干次操作，每次操作将某相邻两数变为他们的异或和（注意操作后序列长度减一）。求是否可以经过若干次操作，得到一个长度至少为 $2$ 且所有元素相等的序列

----

首先，我们考虑所有满足条件的目标序列之间的关系  
对于一个长度不小于 $3$ 的所有元素相等的序列，设序列长度为 $n$，则该序列一定可以变换成一个长度为 $n-2$ 的元素相等序列。我们称这两个序列是本质相同的

那么，我们可以发现，在所有满足条件的目标序列中，最多只会有两个不等价的。并且他们的长度分别为 $2,3$。  
所以，我们只需要判断原序列是否能划分为 $2/3$ 个异或和相等的段即可

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
const int Maxn=2010;
const int Maxm=40;
int a[Maxn],f[Maxn][Maxn];
int n;
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0' && ch<='9')s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*w;
}
bool check()
{
	for(int i=1;i<n;++i)
	{
		if(f[1][i]==f[i+1][n])return 1;
		for(int j=i+2;j<=n;++j)
		if(i+1<j && f[1][i]==f[i+1][j-1] && f[j][n]==f[i+1][j-1])
		return 1;
	}
	return 0;
}
int main()
{
	// freopen("in.txt","r",stdin);
	int T=read();
	while(T--)
	{
		n=read();
		for(int i=1;i<=n;++i)
		a[i]=read();
		for(int i=1;i<=n;++i)
		for(int j=i;j<=n;++j)
		f[i][j]=(f[i][j-1]^a[j]);
		if(check())puts("YES");
		else puts("NO");
		memset(f,0,sizeof(f));
	}
	return 0;
}
```

---

## 作者：wheneveright (赞：3)

## 题意

$T$ 组数据，每组数据给出一个由 $N$ 个数字组成的序列，你可以操作无限次，每次操作将相邻的两个数字进行 $\operatorname{Xor}$ 并且将结果合并，求问最后能不能让序列成为一个好的序列。我们定义一个序列是好的当且仅当这个序列没个数都相同，特别的，序列长度必须大于 $1$。

## 分析

对于给出的数据，问题等同于将其分成两块及以上，使块的 $\operatorname{Xor}$ 相等。显然需要构造一个前缀 $\operatorname{Xor}$，然后考虑用容斥的思想去控制块内 $\operatorname{Xor}$ 的结果，考虑只要分出两个或三个块就行了。

$N^2$ 枚举两个断点使得断电和边界组成的块 $\operatorname{Xor}$ 相等，特别的当 $\operatorname{Xor}_{i = 1}^N a_i = 0$ 时这个序列刚好可以被分成两半，你也可以用 $\operatorname{O}(n)$ 的复杂度去解决。

接下来证明为什么只要两个或三个块：因为一个数 $\operatorname{Xor}$ 两次与不 $\operatorname{Xor}$ 是等价的，所以任何块数大于 $2$ 的偶数分法都可以令任意三个相邻的 $\operatorname{Xor}$ 合并消耗掉两个，所以这又变成了一个奇偶性问题，本来最正宗的奇偶性问题判断的是 $0$ 和 $1$ 但是题目中有要求说不得小于 $2$ 块，所以选择 $2$ 和 $3$。

这道题判断三个的部分还是可以优化下复杂度的（因为数据太小所以不提供代码仅提供思想）：思考循环的配置以及前 $\operatorname{Xor}$ 和的性质，用数据解构可以优化到 $\operatorname{O}(n\times \log_2 n)$。

## 代码

```cpp
# include <bits/stdc++.h>
using namespace std;

const int maxn = 2005;

int T;
int N, A[maxn], S[maxn];

int main () {
    cin >> T;
    while (T--) {
        cin >> N;
        for (int i = 1; i <= N; i++) cin >> A[i], S[i] = S[i - 1] xor A[i];
        bool check = not S[N]; // 判断二个块的情况
        for (int i = 1; i <= N; i++) for (int j = i + 1; j <= N - 1; j++)
        check |= ((S[i] == (S[j] xor S[i])) and S[i] == (S[N] xor S[j]));
        puts (check? "YES" : "NO");
    }
    return 0;
}
``` 


---

## 作者：Cry_For_theMoon (赞：3)

[传送门](https://www.luogu.com.cn/problem/CF1516B)

吐槽一下pretest太弱了，1小时四题，赛后B题光荣 fst /cy/cy

我们考虑最后的划分方案，设每一段异或和为 $s$，全局和为 $S$.

- 如果有偶数段，则 $S=0$. 反过来，不难发现如果 $S=0$ 一定可以找到一个分界点，使得两边异或和相等。即等价。

- 如果有奇数段，则 $S=s$. 

对于第二种情况，由于段数 $>1$，枚举第二段出现位置从而确定第一段还有剩下的所有段，不难发现这三段异或和全部相等即是一种合法的划分方案。同时反过来，一种合法的划分方案也满足这个性质。即等价。

所以一个极其好写的 $n^2$ 算法就出来了。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(ll i=(a);i<=(b);i++)
#define per(i,a,b) for(ll i=(a);i>=(b);i--)
#define op(x) ((x&1)?x+1:x-1)
#define odd(x) (x&1)
#define even(x) (!odd(x))
#define lc(x) (x<<1)
#define rc(x) (lc(x)|1)
#define lowbit(x) (x&-x)
#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a<b?a:b)
#define next Cry_For_theMoon
#define il inline
#define pb(x) push_back(x)
#define is(x) insert(x)
#define sit set<int>::iterator
#define mapit map<int,int>::iterator
#define pi pair<int,int>
#define ppi pair<int,pi>
#define pp pair<pi,pi>
#define fr first
#define se second
#define vit vector<int>::iterator
#define mp(x,y) make_pair(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef double db;
using namespace std;
const int MAXN=2010;
int T,n,a[MAXN];
int sum[MAXN];
int main(){
	cin>>T;
	while(T--){
		memset(sum,0,sizeof sum);
		cin>>n;rep(i,1,n)cin>>a[i],sum[i]=sum[i-1]^a[i];
		if(!sum[n]){
			printf("YES\n");continue;
		}
		rep(i,2,n){
			rep(j,i,n){
				if((sum[j]^sum[i-1])==sum[i-1] && (sum[n]^sum[j])==sum[i-1]){
					goto OK;
				}	
			}
		}
		printf("NO\n");continue;
		OK:printf("YES\n");
	}
	return 0;
}

```


---

## 作者：feicheng (赞：2)

**UPD：修改了代码的小问题**

## Description

给定一个 $n$ 长度的数组 $a$ ，可以进行操作：
将数组相邻的两个元素删除，并在原来的位置插入这两个元素的异或和。

求在最多删除 $n-2$ 个元素（即至少剩余 $2$ 个元素）的情况下能否使数组所有元素相等。

**限制**：$1\le t\le15,2\le n\le2000,0\le a_i<2^{30}$

## Solution

给出一个 $\Theta(n)$ 的解法。

容易知道一个序列如果有答案，那么最后只剩下 $2$ 或 $3$ 个数，对于两种情况，我们分类讨论：

### 1.最后只剩下两个数

如果能够出现这种情况，那么

$$\bigoplus_{i=1}^na_i=0$$

因为剩下的两个数一定是由一个前缀和一个后缀异或得到的，又因为他们俩相等，所以总异或和为 $0$。

### 2.最后只剩下三个数

记$s_x=\bigoplus_{i=1}^xa_i$

设剩下的三个数分别为 $x,y,z$，

则 $\exists p\in[1,n],s_p=0$
（即 $x\oplus y$）,且 $s_n=z$。

也就是说在 $[1,p]$ 范围内有一 $q$ 使得
$s_q=x=z=s_n$，所以我们可以枚举 $q$，检验答案。

感谢 @Gipppp 的 hack，之前的代码没有考虑到前面的数全是 $0$ 的情况，已修复。

## Code

```cpp
inline void solve() {
    memset(s,0,sizeof s) ;
    cin >> n ; 
    if(n == 1) return cout << "NO" << '\n',void() ;
    for(int i = 1;i <= n;++i) cin >> a[i],s[i] = s[i - 1] ^ a[i];
    if(s[n] == 0) return cout << "YES\n",void() ;
    int pos = 0,non = 0;
    for (int i = 1; i <= n; ++i) 
        if (a[i] != 0) {
            non = i ;
            break ;
        }
    for(int i = non; i <= n;++i) {
        if(s[i] == 0 && i != 1) {
            pos = i;
            break ;
        }
    }
    for(int i = 1;i <= pos;++i) if(s[i] == s[n]) return cout << "YES\n",void() ;
    cout << "NO\n" ;
}
```

---

## 作者：LeavingZzz (赞：2)

## $\mathsf{Solution\space To\space CF1516B}$  
### $\mathsf{Description}$  
给定一个长度为 $n$ 的数组，你可以执行以下操作任意多次：  
- 选择两个相邻的数字，将这两个数字删掉，在他们原来的位置添加**一个**数字，其值为删掉的两个数字的异或值，操作后数组长度减一。  

问可不可以让整个数组内的所有数字相等，需要保证最后数组内至少有两个元素。  
### $\mathsf{Analysis}$
有结论：如果可以让整个数组内所有数字相等的话，那么也一定可以操作到剩下 $2$ 个或者 $3$ 个相等的数字。  

证明：如果可以让整个数组内所有数字相等，假设都等于 $x$，数组内剩下 $k$ 个 $x$，每次选择两个相邻的 $x$ 异或后得到 $1$ 个 $0$，然后再与相邻的 $x$ 异或得到一个 $x$，你发现这个过程相当于在数组长度 $\ge3$ 的时候一次性减掉 $2$ 个 $x$，在保证数组内至少有 $2$ 个 $x$ 的情况下，最后要么剩 $2$ 个，要么剩 $3$ 个。  

显然最后数组中剩下的每一个元素对应原数组中一段元素的异或和，由上面的结论可推断出，可以将原数组划分成 $2$ 段或者 $3$ 段异或值相同的区间等价于原问题有解。  

所以直接枚举区间分界点即可。  
时间复杂度 $O(Tn^2)$
### $\mathsf{Code}$  
```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cctype>
#include<cstdlib>
#include<ctime>
using std::max;
using std::min;
using std::sort;
using std::swap;
const int maxn=2007;
int sum[maxn];
int A[maxn];
int T,N;
inline int R()
{
    int re;
    char c;
    while(!isdigit(c=getchar()));
    re=c-48;
    while(isdigit(c=getchar()))
    re=re*10+c-48;
    return re;
}
int main()
{
    #ifndef ONLINE_JUDGE
    freopen("1.in","r",stdin);
    #endif
    T=R();
    while(T--)
    {
        N=R();
        for(int i=1;i<=N;i++)
            A[i]=R(),sum[i]=sum[i-1]^A[i];
        bool f=false;//是否有解
        for(int i=1;i<N;i++)
        if((sum[N]^sum[i])==sum[i]) {f=true;break;}//分成[1,i]和[i+1,N]两段
        for(int i=1;i<N;i++)//分成[1,i],[i+1,j],[j+1,N]三段
            for(int j=i+1;j<N;j++)
                if(sum[i]==(sum[j]^sum[i])&&sum[i]==(sum[N]^sum[j])) {f=true;break;}
        if(f) puts("YES");
        else puts("NO");
    }
    return 0;
}

```

---

## 作者：Engulf (赞：1)

假设我们已经操作完了整个序列，由于异或操作的性质，$x \oplus x = 0$，$0 \oplus x = x$。

所以，如果整个序列的异或和是 $0$，那么最后一定是有偶数个段，一定可以操作成所有元素相等。

如果异或和不是 $0$ 而是 $x$，只需要判断一下有多少段的异或和为 $x$ 即可。如果有大于 $1$ 个段就可以完成操作。

```cpp
#include <bits/stdc++.h>
using namespace std;

namespace fastIO
{
	template<typename T> inline void read(T &t)
	{
		T x = 0;
		int f = 0;
		char ch = getchar();
		while (!isdigit(ch)) f ^= !(ch ^ 45), ch = getchar();
		while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
		t = f ? -x : x;
	}
	template<typename T, typename ...Args> inline void read(T &x, Args&... args)
	{
		read(x), read(args...);
	}
	template<typename T> void write(T t)
	{
		if (t < 0) putchar('-'), t = -t;
		if (t >= 10) write(t / 10);
		putchar(t % 10 + '0');
	}
	template<typename T, typename ...Args> void write(T t, Args... args)
	{
		write(t), putchar(' '), write(args...);
	}
	template<typename T> void writeln(T t)
	{
		write(t), putchar('\n');
	}
};
using namespace fastIO;

int main()
{
	int tt;
	read(tt);
	while (tt -- )
	{
		int n, x = 0;
		read(n);
		vector<int> a(n);
		for (auto &i: a) read(i), x ^= i;
		if (x == 0) {puts("YES"); continue;}
		int cnt = 0, cur = 0;
		for (int i = 0; i < n; i ++ )
		{
			cur ^= a[i];
			if (cur == x) {cur = 0; cnt ++ ;}
		}
		puts(cnt >= 2 ? "YES" : "NO");
	}
	return 0;
}
```

---

## 作者：huayucaiji (赞：1)

有时候比赛考的是审题。

题目中提到了：

> he picks $2$ **adjacent** elements

'adjacent' 没看到，浪费 1.5h，这场比赛凉凉了。

具体分析做法。

容易想到最后留下的数要么 $2$ 个，要么 $3$ 个。这很好证明。

如果有 $n(n>3)$ 个数相等，那么我一定可以拉出来两个数，异或一下，变成 $0$，然后随便搞到一个数身上。由于最后不可以只留下一个数，所以留下的数要么 $2$ 个，要么 $3$ 个。

$2$ 个数的情况很好判断，只需要判断所有数异或起来是否等于 $0$。

$3$ 个数也很好做，注意到 $N$ 的范围，我们可以直接枚举三个区间，利用好维护好的前缀和随便搞一下即可。

```cpp
//Don't act like a loser.
//This code is written by huayucaiji
//You can only use the code for studying or finding mistakes
//Or,you'll be punished by Sakyamuni!!!
#include<bits/stdc++.h>
#define int long long
using namespace std;

int read() {
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9') {
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f*x;
}

int n;
int a[5000],s[5000]; 

void judge() {
	for(int i=1;i<=n;i++) {
		for(int j=i+1;j<n;j++) {
			if((s[j]^s[i])==s[i]&&s[i]==(s[n]^s[j]) ){
				puts("YES");
				return ;
			}
		}
	}
	puts("NO");
}

signed main() {
	int t=read();
	while(t--) {
		n=read();
		for(int i=1;i<=n;i++) {
			a[i]=read();
			s[i]=s[i-1]^a[i];
		}
		
		if(s[n]==0) {
			puts("YES");
			continue;
		}
		judge();
	}
	return 0;
}

```

如果没有相邻这个条件，可能要用到线性基。

---

## 作者：我梦见一片焦土 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF1516B)

------------
# 思路：
容易想到最后留下的数要么 $2$ 个，要么 $3$ 个。这很好证明。

如果有 $n$ 个数相等，那么我一定可以拉出来两个数，异或一下，变成 $0$，然后随便搞到一个数身上。由于最后不可以只留下一个数，所以留下的数要么 $2$ 个，要么 $3$ 个。

$2$ 个数的情况很好判断，只需要判断所有数异或起来是否等于 $0$。

$3$ 个数也很好做，注意到 $N$ 的范围，我们可以直接枚举三个区间，利用好维护好的前缀和搞一下即可。

------------
代码：
```cpp
#include <bits/stdc++.h>

#define LL long long
using namespace std;
const int N = 2e3 + 10 , INF = 0x3f3f3f3f;
inline LL read(){
	   LL x = 0 , f = 1 ; char ch = getchar();
	   while (ch < '0'||ch > '9'){if (ch == '-') f = -1 ; ch = getchar();}
	   while (ch >= '0'&&ch <= '9'){x = x * 10 + ch - 48 ; ch = getchar();}
	   return x * f;
}
void write(LL x){
    if(x < 0)
        putchar('-'),x = -x;
    if(x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}
LL a[N]; 
LL f[N] , b[N];
signed main(){
	int T = read();
	while(T --){
		int n = read() , g; bool flag = 0;
		for(int i = 1;i <= n;i ++)
			cin >> a[i];
		b[n + 1] = 0; f[0] = 0;
		for(int i = 1;i <= n;i ++) f[i] = f[i - 1] ^ a[i];
		for(int i = n;i >= 1;i --) b[i] = b[i + 1] ^ a[i];
		for(int i = 2;i <= n - 1;i ++){
			g = 0;
			for(int j = i ;j < n;j ++){
				g ^= a[j];
				if(g == f[i - 1] && g == b[j + 1]) {
					flag = 1;
					break ;
				}
			}
		}
		if(!f[n]) flag = 1;
		puts( flag ? "YES" : "NO");
	}
	      
	return 0;
}
```
 		 		 	   			 	 	     		     	

---

