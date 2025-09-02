# Infinite Replacement

## 题目描述

You are given a string $ s $ , consisting only of Latin letters 'a', and a string $ t $ , consisting of lowercase Latin letters.

In one move, you can replace any letter 'a' in the string $ s $ with a string $ t $ . Note that after the replacement string $ s $ might contain letters other than 'a'.

You can perform an arbitrary number of moves (including zero). How many different strings can you obtain? Print the number, or report that it is infinitely large.

Two strings are considered different if they have different length, or they differ at some index.

## 说明/提示

In the first example, you can replace any letter 'a' with the string "a", but that won't change the string. So no matter how many moves you make, you can't obtain a string other than the initial one.

In the second example, you can replace the second letter 'a' with "abc". String $ s $ becomes equal to "aabc". Then the second letter 'a' again. String $ s $ becomes equal to "aabcbc". And so on, generating infinitely many different strings.

In the third example, you can either leave string $ s $ as is, performing zero moves, or replace the only 'a' with "b". String $ s $ becomes equal to "b", so you can't perform more moves on it.

## 样例 #1

### 输入

```
3
aaaa
a
aa
abc
a
b```

### 输出

```
1
-1
2```

# 题解

## 作者：初雪_matt (赞：2)

## 题目大意

给定字符串 $s$ 和 $t$，你可以将 $s$ 中字符```a```的地方替换成 $t$，求 $s$ 最终有几种可能的字符串，若无数种输出```-1```。

## 题目思路

分情况讨论即可：

$1$. $t$ 为字符```a```。若 $s$ 不包含字符```a```，自身只算一种。若 $s$ 中包含字符```a```，由于 $t$ 也为字符```a```，所以 $s$ 不变，也只有一种，综上所述，这种情况只有一种可能。

$2.$ $t$ 中有字符```a```（不包含第 $1$ 种情况）。此时可以发现，$t$ 中若有字符```a```，便就可以无限嵌套，这种情况有无数种，则输出```-1```。

$3.$ 其他所有情况，既然不包含了上述情况，每一个 $s$ 中的```a```便有换成 $t$ 或不换两种可能性，又因为 $s$ 全为字符```a```组成，所以根据乘法原理易得答案为 $2^{S_{len}}$。

## 代码

```
a=int(input())
for i in range(a):
    s=input()
    t=input()
    if t=='a'://第一种情况
        print(1)
    elif 'a'in t://第二种情况
        print(-1)
    else://第三种情况
        print(2**len(s))
//很简单吧~
```

---

## 作者：xzyg (赞：2)

## 题意简述

给定仅由字符 'a' 组成且长度为 $ n $ 的非空字符串 $ s $ 和 非空字符串 $t$。可以将 $ s $ 中的一个 'a' 换作 $ t $。求能构成多少种不同的字符串；若可以构成无限多个，输出 '-1'。

## Sol:

当 $t$ 中只有一个字符且该字符为 'a' 时，方案数为 $1$~~（换了，但没完全换）~~。

不难发现，构成无限多个方案时 $ t $ 中必定有 'a'~~（无限套娃）~~。

判断一下 $ t $ 中是否有 'a' 即可解决合法性 和 特殊情况。

对于 $ t $ 中没有 'a' 的情况，容易发现方案数为 $ 1 \sim n $ 在 $ n $ 中的组合数之和，即：

$$ \sum_{k=0}^{n}\binom{n}{k} $$

感觉和二项式定理的右边差不多：

$$ (x + a) ^ n =  \sum_{k=0}^{n}\binom{n}{k} x^k a^{n-k} $$

可令上式中 $ x = a = 1$，就化出来了：

$$ 2 ^ n =  \sum_{k=0}^{n}\binom{n}{k} 1^k 1^{n-k} =  \sum_{k=0}^{n}\binom{n}{k} $$

也可以用一个集合的子集个数理解，具体请移步 [P2415](https://www.luogu.com.cn/problem/P2415)。

### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath> 
#define ll long long

using namespace std;

int main(){
	ll T;
	cin >> T;
	while(T--){
		string s,t;
		cin >> s >> t;
		if(t == "a"){
			cout << 1 << endl;
			continue; 
		}
		
		bool f = false;
		
		for(ll i = 0; i < t.size(); i++){
			if(t[i] == 'a'){
				f = true;
				break;
			}
		} 
		
		if(f)
			cout << -1 << endl;
		else{
			ll ans = pow(2,s.size());//这里得用一个临时变量存储，不然会炸。
			cout << ans << endl;
		}
	} 
	return 0;
}
```


---

## 作者：Day0 (赞：1)

[更好的食用体验](http://blog.hhdxgd.com/post/cf1674c-infinite-replacement-ti-jie/)

[原题传送门](https://codeforces.com/problemset/problem/1674/C)

## 1.题目大意
给你一个字符串 $s$ 和 $t$  , 当 $s[i]$ 为字符 `a` 时候，可以选择使用 $t$ 字符串来替换 `a` 问可以替换出多少不同的字符串,如果有无数种，则输出 $-1$

## 2.思路
分情况考虑
	
1. $t$ 字符串中不含有 `a`
	这种情况最容易考虑， $s$ 字符串每出现一个 `a` , 我们都可以考虑换或者不换，若 $s$ 字符串有 $k$ 个 `a` , 则显然答案为 $2^k$
(位运算的时候要注意需要用 `1LL` , 单纯使用 `1<<n` 会返回 `int` 类型的参数，可能会爆`int`)

1. $t$ 字符串中含有 `a`
	1. 如果 $t$ 的长度为 $1$ , 则无论如何 ，字符串 $s$ 都不会发生改变，答案为 $1$
   
   1. 如果 $t$ 的长度大于 $1$ , 则字符串 $s$ 中的 `a` 每被 $t$ 替换一次，都会至少出现一个新的 `a` , 而 $t$ 可以再对这个 `a` 进行替换 ， `a` 永远不会消失，而 $t$ 字符串的其他字符会越来越多 ， 我们就会得到无数多的新字符串，答案为 $-1$
   
## 3.核心代码
```cpp
	string s, t;
	cin >> s >> t;
	int size = t.size();
	int flag = 0;
	for (int i = 0; i < size; i++) {
		if (t[i] == 'a') {
			flag = 1;
			break;
		}
	}
	if (flag) {
		if (t.size() == 1) {
			cout << 1 << endl;
		} else {
			cout << -1 << endl;
		}
	} else {
		int ans = 1LL << s.size();
		cout << ans << endl;
	}
```




---

## 作者：pengzy (赞：0)

### 思路：

很显然，根据样例，此题可以分为三种情况进行讨论。

1. $t=a$ 

显然，不管怎么改动，最后都只能是原来的字符串 $s$ 这一种。

2. $t$ 含有 $a$

因为每一个 $a$ 都可以被替换为 $t$，所以这种情况会无限嵌套下去，输出 $-1$。

3. 排除以上两种情况的一般情况

对于给定字符串 $s$ 的每一个字符，都有换和不换两种选择，所以根据乘法原理，答案就是 $2^{length(s)}$。

### 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int T;
int main()
{
	cin>>T;
	while(T--) {
		string s,t;
		cin>>s>>t;
		if(t=="a") {
			cout<<1<<endl;
			continue; 
		}
		bool f=false;
		for(int i=0;i<t.size();i++)
			if(t[i]=='a') {
				f=true;
				break;
			}
		if(f)cout<<-1<<endl;
		else {
			long long ans=pow(2,s.size());
			cout<<ans<<endl;
		}
	}
	return 0;
}
```

---

## 作者：Helium_Ship (赞：0)

# 思路
如果 $t$ 中仅有一个 'a'，那么显然替换于不替换相同，答案显然为 $1$。

如果 $t$ 中有一个及以上的 'a'，并且 $s$ 的长度大于 $1$，那么则能够不断地替换，答案则有无数种，输出 $-1$。


如果 $t$ 中没有 'a'，那么根据组合数学可知答案为 $2^{|s|}$。
# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
string n,m;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>T;
	while (T--)
	{
		cin>>n>>m;
		bool flag=0;
		for (int i=0;i<m.size();i++)
			if (m[i]=='a')
				flag=1;
		if (flag&&m.size()==1)
			cout<<"1\n";
		else if (flag&&m.size()>1)
			cout<<"-1\n";
		else 
		{
			long long sum=1;
			for (int i=0;i<n.size();i++)
				sum*=2;
			cout<<sum<<"\n";
		}
	}
	return 0;
 } 
```

---

## 作者：Galois_Field_1048576 (赞：0)

如果 $t = \tt{a}$，则 $\tt{a}$ 永远是 $\tt{a}$，其他的也不能替换，只能产生 1 个字符串。  
如果 $\tt{a} \in t$ 且 $t \ne \tt{a}$，那么有 $\infty$ 个不同的字符串。  
> 证明：  
> 反证法。如果存在一个 $j \in \mathbb{N}$，使得有 $j$ 个不同的字符串，反证如下  
> 定义 $h_0 \gets s$，$h_{i+1} \gets \texttt{replace}(h_i,\texttt{a},s)$，其中第一个参数是要替换的字符串，第二个是旧字符串，第三个是新字符串。  
> 显然 $\forall i \in \mathbb{N}, h_i \ne h_{i+1}$。  
> 故有 $\gt j$ 个字符串。证毕。  

否则，每个 $s$ 中的 $\tt a$ 都有两种可能，替换或不替换。所以 根据乘法原理，有 $2^{|s|}$ 种可能。



代码：

```python3
for i in range(int(input())):
    A = input()
    B = input()
    if B == "a": print(1)
    elif "a" in B: print(-1)
    else: print(pow(2, A.count("a")))
```

---

## 作者：Deuteron (赞：0)

题意传送门：[here](https://www.luogu.com.cn/problem/CF1674C)

## solution:

考虑几种情况。

设 $\vert S \vert$ 为字符串 $S$ 的长度 ， $\vert T \vert$ 为字符串 $T$ 的长度 。

情况 $1$ ：
$T$ 中含有 $\texttt a$ 且 $\vert T \vert >1$ 

显然可以替换无穷多次，每次都会添加更多的字母。

情况 $2$ ：
$T$ 中含有 $\texttt a$ 且 $\vert T \vert =1$ 

显然不能有其他替换，答案为 $1$ 。

情况 $3$ ：
$T$ 中没有 $\texttt a$ 

$S$ 中每个 $\texttt a$ 都可以替换成 $T$ 且只能替换一次。

根据乘法原理，答案显然为 $2^{\vert S \vert}$ 。

## code:

```cpp
#include<iostream>
#include<cstring>
using namespace std;
int T;//数据组数
string s,t;
long long ans=1;//答案最大2^50 要开long long
int main(){
	cin>>T;
	while(T--){
		cin>>s>>t;
		int fl=0;//初始化
     		ans=1;
		for(int i=0;i<t.length();i++){
			if(t[i]=='a') fl=1;//检测是否有a
		}
		if(fl&&t.length()>1){
			cout<<"-1"<<endl;//第一种情况，输出-1
			continue;
		}
		if(fl&&t.length()==1){
			cout<<"1"<<endl;//第二种情况，输出1
			continue;
		}
		for(int i=1;i<=s.length();i++) ans*=2;
		cout<<ans<<endl;//第三种情况
	}
	return 0;
}
```


---

## 作者：cyrxdzj (赞：0)

### 一、思路

如果字符串 $t$ 中不含字母 `a`，那么答案就是 $2^{|s|}$，其中 $|s|$ 代表字符串 $s$ 的长度。

为什么呢？因为，字符串 $s$ 中的每个字符既可以选择替换为字符串 $t$，也可以不选择，并且选择替换后字符串 $s$ 一定会消失一个字母 `a`（字符串 $t$ 里没有），根据组合数学可知答案。

如果字符串 $t$ 中含有字母 `a` 但字符串 $t$ 只有一个字母，那么答案为 $1$。显然，无论怎么替换，字符串 $s$ 都不会变。

如果字符串 $t$ 中含有字母 `a` 并且字符串 $t$ 不止一个字母，那么答案为无限。显然，每次替换，字符串 $s$ 中的字母 `a` 一定不会减少，就可以做到无限替换。

### 二、代码

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
int t;
char a[55],b[55];
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%s%s",a+1,b+1);
		int la=strlen(a+1),lb=strlen(b+1);
		bool flag=false;
		for(int i=1;i<=lb;i++)
		{
			if(b[i]=='a')
			{
				flag=true;
				break;
			}
		}
		if(flag)//含有
		{
			if(lb==1)
			{
				printf("1\n");
			}
			else
			{
				printf("-1\n");
			}
			continue;
		}
		printf("%lld\n",(long long)1<<la);//不开long long见祖宗
	}
	return 0;
}

```


---

## 作者：lsj2009 (赞：0)

## 题目大意
给定字符串 $a$ 和 $b$，其中 $a$ 有且仅有字符 ``a``，我们可以用 $b$ 替换 $a$ 中若干个字符 ``a``（包括替换上的 $b$ 的字符也可以），问最终可能会有几种字符串 $a$？如有无数种，输出 ``-1``。
## 思路
很明显，如果 $b$ 有字符 $a$ 那么且长度为 $1$，则无论将其替换 $a$ 中的哪一个字符 ``a``，总是会得到原字符串 $a$，输出 $1$ 即可。

如果 $b$ 有字符 $a$ 且长度大于 $1$，则我们将 $b$ 替换其中一个 ``a``，然后，我们可以继续用 $b$ 替换 $b$ 本身中的那个字符 ``a``……以此类推，我们可以得到无数种字符串 $a$。

如果 $b$ 中没有字符 ``a``，那么对于 $a$ 中的每一个位置，我们都可以使用或不使用 $b$ 去替换，通过乘法原理，答案很明显为 $2^{|a|}$。

## Code:
```cpp
#include<bits/stdc++.h>
#define pd push_back
#define pb pop_back
#define mk make_pair
#define int long long
#define PII pair<int,int>
#define _for(a,b,c) for(int a=b;a<=c;a++)
#define _rep(a,b,c) for(int a=b;a>=c;a--)
#define _go(i,u) for(int i=head[u];i;i=Edge[i].nxt)
using namespace std;
namespace I {
	template <typename T> void read(T& x) {
		x=0; T f=1; char ch=getchar();
		while(ch<'0'||ch>'9') { if(ch=='-') f=-1; ch=getchar(); }
		while(ch>='0'&&ch<='9') { x=(x<<1)+(x<<3)+(ch&15); ch=getchar(); }
		x=x*f; return;
	}
	template <typename T,typename ...Arg> void read(T& x,Arg& ...arg) {
		read(x); read(arg...);
	}
}
namespace Math {
	template <typename T> T power(T a,T b,T MOD) {
		T ans=1; while(b) { if(b&1) ans=ans*a%MOD; a=a*a%MOD; b>>=1; } return ans%MOD;
	}
	template <typename T> T power(T a,T b) {
		T ans=1; while(b) { if(b&1) ans=ans*a; a=a*a; b>>=1; } return ans;
	}
	template <typename T> T gcd(T a,T b) {
		if(b) return gcd(b,a%b); return a;
	}
	template <typename T> T lcm(T a,T b) {
		return a/gcd(a,b)*b;
	}
	template <typename T> T inv(T n,T p) {
		return power(n,p-2);
	}
	const int Test[]={0,2,3,5,7,11,13,17,19,23,29};
	template <typename T> bool is_prime(T n) {
		if(n<2) return 0;
		T t=n-1,k=0; while((t+1)&1) ++k,t>>=1;
		_for(i,1,10) {
		    if(n==Test[i]) return 1;
		    T s=power(Test[i],t,n); T tmp=s;
		    _for(j,1,k) {
		        tmp=s*s%n; if(tmp==1&&s!=1&&s!=n-1) return 0; s=tmp;
		    }
		    if(s!=1) return 0;
		}
		return 1;
	}
}
const int N=100;
char a[N],b[N];
int Find(char s[],int n,char c) {
	int tot=0;
	_for(i,1,n)
		if(s[i]==c) ++tot;
	return tot;
}
signed main() {
	int T;
	I::read(T);
	while(T--) {
		scanf("%s%s",a+1,b+1);
		int n=strlen(a+1);
		int m=strlen(b+1);
		int cnta=Find(a,n,'a');
		int cntb=Find(b,m,'a');
		if(cntb)
			puts(m==1? "1":"-1");
		else
			printf("%lld\n",Math::power(2ll,cnta));
	}
	return 1;
}

```

---

## 作者：yeshubo_qwq (赞：0)

思路：

首先考虑特殊情况。

+ 如果替换 a 的字符串长度为 $1$ 且唯一的字符是 a，那么变了和没变一样，答案为 $1$。

+ 如果替换 a 的字符串长度不为 $1$ 且包含字符 a，那么变了以后可以继续用新的 a 不断扩展，答案为无限，即输出 $-1$。

接下来就很简单了，每个位置有替换和不替换两种情况，若全部为 a 的串长度为 $s$，则答案为 $2^s$。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T,n,fl,i;
char a[55],s[55];
int _pow(int y){
	int ans=1;
	while (y--) ans<<=1;
	return ans;
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>T;
	while (T--){
		cin>>a+1>>s+1;
        n=strlen(s+1);
		fl=0;
		for (i=1;i<=n;i++)
			if (s[i]=='a')
				fl=1;
		if (fl==1&&n==1) cout<<"1\n";
		else if (fl==1) cout<<"-1\n";
		else cout<<_pow(strlen(a+1))<<'\n';
	}
	return 0;
}
```


---

## 作者：junxis (赞：0)

# Translation
给你一个含有若干个 $\texttt{a}$ 的字符串 $S$ 以及一个由小写字母构成的字符串 $T$，每次你可以将 $S$ 中的一个 $\texttt{a}$ 替换成 $T$。

这样的操作可以一直做到做不了了，问最后会产生多少种本质不同的字符串？

若有无穷多种，输出 $-1$。

多组数据。

# Analysis

$|S|$ 表示 $S$ 的长度。

若 $T$ 中有 $\texttt{a}$，且 $|T| \ne 1$，容易发现此时是有无穷中的，因为可以换完一个位置后继续把 $T$ 里的 $\texttt{a}$ 换掉，一直这样连环换即有无穷种可能。

若 $T$ 中有 $\texttt{a}$，且 $|T| = 1$，容易发现此时答案为 $1$。

否则，每个位置都有换或不换两种选择，答案即为 $2^{|S|}$。

代码实现难度依然为零。

---

## 作者：osfly (赞：0)

有意思的题目。

还是比较好想的。

先考虑 `-1` 的情况，可以想到，如果 $t$ 的长度不为 $1$，并且 $t$ 里面还有 `a` 的话，那么这个新的 `a` 又能被下一个 $t$ 替换，无限套娃。

剩下的，还是有两种情况：

1. 如果 $t$ 只有一个字符 `a` ，那么 $s$ 无论怎么被替换都是一样的（全部都是 `a` ），所以，这种情况输出 `1`。

1. 如果不是第 `1` 种情况，那么最终的答案就为:

	$\large C^0_n+C^1_n+C^2_n+C^3_n+...+C^n_n$

	其实上面这个式子很好理解，只要从 $s$ 里分别选出 $0$ 个，$1$ 个，$2$ 个，......，$n$ 个 `a` 出来被替换就是最后的方案数。
    
   根据组合数的定义，可以知道上面的式子就是 $\large2^n$。
   
   为了加快效率，可以使用 `cmath` 的 `pow` 函数，也可以先预处理所有的  $\large 2^i$ 的值。
   
code

```cpp
#include<cstdio>
#include<cstring>

int q;
char s[100],t[100];
unsigned long long pow[100];

void init()
{
	pow[0]=1;
	for(int i=1;i<=50;i++) pow[i]=pow[i-1]*2;
}

int main()
{
	init();
	
	scanf("%d",&q);
	
	while(q--)
	{
		scanf(" %s %s",s+1,t+1);
		
		int le=strlen(s+1);
		int len=strlen(t+1);
		
		//-1
		if(len>1)
		{
			bool yes=0;
			for(int i=1;i<=len;i++)
				if(t[i]=='a')
				{
					yes=1;
					break;
				}
			if(yes)
			{
				printf("-1\n");
				continue;
			}
			else printf("%lld\n",pow[le]);
		}
		else
		{
			if(t[1]=='a') printf("1\n");
			else printf("%lld\n",pow[le]);
		}
	}
	
	return 0;
}
```

---

## 作者：JCLinux (赞：0)

**题目大意：**

一共 q 组数据，每一组数据给你两个字符串，只有小写英文字母组成。

S

T

你可以把字符串 S 中的 $\texttt a$ 字符用 $\texttt b$ 字符串替换，问你一共有多少种方案，如果有无穷多种方案，输出 $-1$

**思路：**

首先我们来考虑无穷的情况，为什么会有无穷多中情况呢？

当字符串 T 的长度大于 $1$ 且字符串 T 中包含 $\texttt a$ 时，这就是无穷的情况。

因为我们用 T 替换掉 S 中的某个 $\texttt a$ 时，又会引入新的 $\texttt a$，这就导致 S 中的 $\texttt a$ 永远替换不完，且每次替换 S 都会变成一个**新的**字符串。

是不是当 T 中有 $\texttt a$ 就一定是无穷的呢，不是。 当 T 就只有一个字母 $\texttt a$ 时，每次替换都无法产生新的字符串 S，此时的答案应该是 $1$

接下来考虑其他情况了，假设 S 的长度的 $n$，也就是说 S 包含了 $n$ 个 $\texttt a$，对于每一个 $\texttt a$，我们有两种选择：把它替换掉或者不替换，而每一种选择都会对应不同的新的 S，故方案数等于 $2^n$

$2^n$ 我们可以用移位的方式方便求出，但是注意要用 long long 

**代码：**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t, n, m, k;
string a, b;
signed main()
{
	cin.sync_with_stdio(false);
	cin >> t;
	while(t--)
	{
		cin >> a >> b;
		if(b.size() == 1)
		{
			if(b[0] == 'a')cout << "1\n";
			else cout << (1ll << a.size()) << '\n';
		}
		else
		{
			bool flag = 0;
			for(auto x : b) if(x == 'a') flag = 1;
			if(flag) cout << "-1\n";
			else cout << (1ll << a.size()) << '\n';
		}
	}
}


```


---

## 作者：CmsMartin (赞：0)

## 题目描述

[题目传送门1](https://www.luogu.com.cn/problem/CF1674C)

[题目传送门2](http://codeforces.com/problemset/problem/1674/C)

给你两个由小写字母组成的字符串 $s1$ 和 $s2$，其中 $s1$ 仅由 `a` 组成。现在，你可以以 $s2$ 替换掉 $s1$ 中的任意一个 `a` ，得到一个新的字符串，并在新的字符串上继续该操作。请问会有几个不同的字符串（$s1$ 也算作一种）。
输出总数，若无穷，则为 $-1$。

## 思路

分三种情况讨论：

1. $s2$ 是 $a$，这样替换就无法造成改变，答案为 $1$；

2. $s2$ 中含有 $a$，这样每次替换都会消耗一个原本的 $a$ 并含有新的 $a$ ，可以不断替换，答案为 $-1$；

3. $s2$ 不含有 $a$，则可以在 $s1$ 中随便找若干个 $a$ 进行替换，答案为 $\sum\limits_{i=0}^n C_n^i=2^n$（$n$ 为 $s1$ 长度）。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int T;

string S1 , S2;

int main() {

    scanf("%d" ,&T);

    while (T--) {
        cin >> S1 >> S2;

        if(S2 == "a") {
            printf("1\n");
        }

        else {
            int ToT = 0;
            for(int i = 0; i < S2.size(); i++) {
                if(S2[i] == 'a') ToT++;
            }
            if(ToT != 0) printf("-1\n");

            else {
                long long Ans = 0;
                Ans = 1ll << S1.size();
                printf("%lld\n" ,Ans);
            }
        }
    }
    
    return 0;
}
```

---

