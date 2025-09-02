# Palindromic Indices

## 题目描述

给定一个回文字符串 $s$ ，它的长度为 $ n $ $ (2 \leq n \leq 10^5) $ ，问一共有多少种方式使它去掉一个字符后仍是回文字符串。

## 说明/提示

数据保证所有的 $ n $ 之和不超过 $ 2 \cdot 10^5 $ 。

## 样例 #1

### 输入

```
3
3
aba
8
acaaaaca
2
dd```

### 输出

```
1
4
2```

# 题解

## 作者：RE_Prince (赞：2)

# CF1682A Palindromic Indices

[link](https://www.luogu.com.cn/problem/CF1682A)

## Sol

一道贪心题。

我们考虑一个回文串删除一个字符必须还是回文的情况有哪些。

我们假设这个回文串为如下：

$\begin{matrix}aaabbb\underbrace{ddddddd\cdots ddddd}bbbaaa\\n \times d\end{matrix}$


显然，只能删除回文串中间的 $n$ 个 $d$ 。也就是说只能删除回文串中间的连续的几个字符。

那为什么呢？

答：因为**回文串**，顾名思义，就是左边右边都有相同元素。但只要不删除中间的连续字符，必定会变成非回文串。因为题目只让删除一个字符，但删除两边是至少删除两个，所以只能删中间。


所以找中间开始连续的字符就好了。

比如说上面的例子，就直接输出 $n$ ，因为中间有 $n$ 个连续的 $d$ 。

得出AC代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
char a[100009];
int n, m, i, j, k;
signed main()
{
	int T;
	cin >> T;
	while (T--)
	{
		cin >> n;
		cin >> a + 1;
		int len = strlen(a + 1);
		int len2;
		int cnt = 1;
		if (len & 1) len2 = len / 2 + 1;
		else len2 = len / 2;
		i = len2;
		//cout << len2 << " ";
		while (i >= 1)
		{
			if (i < 1) break;
			if (a[i] == a[i - 1]) cnt++;
			else break;
			i--;
			//cout << i << " ";
		}
		i = len2;
		while (i <= len)
		{
			if (i > len) break;
			if (a[i] == a[i + 1]) cnt++;
			else break;
			i++;
		}
		cout << cnt << endl;
	}
	return 0;
}
```

---

## 作者：_Ad_Astra_ (赞：2)

因为原字符串是回文的，所以不难证明，除了删除位于 $s$ 的正中间的连续的相同字母以外，得到的字符串都不可能是回文串，因为假设删除不属于正中间的连续的相同字母的第 $i$ 个字符 $s_i$ ，那么得到的字串中原来 $s_{n-i+1}$ 的位置，也就是原串中 $s_i$ 对应的字符就没有与之对应的字符（因为 $s_i$ 已经被删除）。而如果删除中间字符则不会影响。

具体做法的话先找到中心字符（即 $s_{[\frac{n}{2}]+1}$ ），然后往左右遍历，找到满足条件的左端点和右端点即可。复杂度 $O(n)$ 。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define pii pair<int,int>
#define fir first
#define sec second 
const int inf=0x3f3f3f3f3f3f3f3f;
#define ISMOD998244353
#ifdef ISMOD998244353
const int mod=998244353;
#else
const int mod=1e9+7;
#endif
void chmax(int &a,int b)
{
	a=max(a,b);
}
void chmin(int &a,int b)
{
	a=min(a,b);
}
int quickpow(int x,int p)
{
//	if(x==0&&p==0)return 1;
//	if(p==0)return 0; 
    int base=x;
    int ans=1;
    while(p)
    {
        if(p&1)ans=ans*base%mod;
        p>>=1;
        base=base*base%mod;
    }
    return ans%mod;
}
int popcount(int x)
{
	return __builtin_popcount(x);
}
void add(int &a,int b)
{
	a=(a+b)%mod;
}
void sub(int &a,int b)
{
	a=(a-b)%mod;
}
void mul(int &a,int b)
{
	a=(a*b)%mod;
}
//以上为预处理

int t,n,ans;
string s;
void solve()
{
	cin>>n>>s;
	ans=1;
	int id=n/2;	//找到中心点，由于下标从0开始所以为n/2
	for(int i=id-1;i>=0&&s[i]==s[id];i--)ans++;//往左寻找符合条件的字符
	for(int i=id+1;i<n&&s[i]==s[id];i++)ans++;//往右寻找符合条件的字符
	cout<<ans<<endl;
}
signed main()
{
	cin>>t;
	while(t--)solve();
    return 0;
}
```

---

## 作者：Night_sea_64 (赞：2)

大家好，本蒟蒻又来写题解了~

[这里是题目](https://www.luogu.com.cn/problem/CF1682A)

从一个回文字符串内，删除一个字符还是回文串。这种情况下，删除的字符一定是在中间位置的字符。因为如果删了别的字符，还得再删一个跟它对称的才能保持回文。

这里的中间位置到底指的是什么位置呢？比如说样例里的第二组数据，$s=\texttt{acaaaaca}$。很容易发现，对称中心是 $s_3$ 和 $s_4$ 两个字符。这两个字符当然可以删去，因为删去了其中之一，另一个还可以自己当对称中心。我们又发现 $s_2$ 和 $s_5$ 与对称中心的字符相同，说明这两个字符也可以删去。

那么这个问题就好解决了。我们拿到一个回文串，不知道它从哪个位置开始是可以删去的。那我们就先找到它的对称中心。

如果长度是奇数，比如 $\texttt{abcba}$。在这个例子里对称中心是 $s_2$，也就是 $s_{\left \lfloor N\div2 \right \rfloor}$。（下标是从 $0$ 开始。）我们从 $s_{\left \lfloor N\div2+1 \right \rfloor}$ 开始枚举，直到 $s_i\not=s_{i-1}$ 为止计数，然后再 $\times\text{ }2+1$（因为有两边，还有一个中间），就是答案。

如果长度是偶数，比如 $\texttt{abba}$。在这个例子里对称中心是 $s_1$ 和 $s_2$，也就是 $s_{N\div2-1}$ 和 $s_{N\div2}$。我们从 $s_{N\div2}$ 开始枚举，也像上面那样计数，答案再 $\times$ $2$（因为有两边）。

蒟蒻语文不好，可能有一些没讲明白。详见 AC 代码（超短，$20$ 行）：

```cpp
#include<iostream>
#include<cstring>
using namespace std;
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        string s;
        cin>>n>>s;
        int cnt=0;
        for(int i=n/2+n%2/*起始位置。奇数是 n/2+1，偶数是 n/2*/;i<n&&s[i]==s[i-1]/*如果 s[i]!=s[i-1] 就自动跳出循环*/;i++)cnt++;
        cout<<cnt*2+n%2<<endl;
        //输出的答案。奇数是 cnt*2+1，偶数是 cnt*2。
    }
    return 0;
}
```

如果有不明白的可以私信本蒟蒻。祝大家 RP++！！！

---

## 作者：accomplishment (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF1682A)

签到题，建议评红。思路很简单，假设字符串 $s$ 是回文串：

$s$ 的长度 $n$ 是偶数时，从 $s_0$ 至 $s_{\frac{n}{2} - 1}$ 与 $s_{\frac{n}{2}}$ 至 $s_{n - 1}$ 对称。

$s$ 的长度 $n$ 是奇数时：$s_0$ 至 $s_{\lfloor \frac{n}{2} \rfloor}$ 与 $s_{\lfloor \frac{n}{2} \rfloor}$ 至 $s_{n - 1}$ 对称。

而如果要使字符串 $s$ 删除一项依然是回文串，这一项只能位于中间 $x$ 个相同字母中，否则左右将不对称，因此只需要找出中间连续相同字母的长度，也就是 $x$ 即可。

方法：从中间项开始，分别向左和向右扩展，知道发现字母与中间项不同为止。

注意：中间项在向左和向右两次统计中会重复统计，所以最后要 $-1$。

中间项的定义为：

偶数：$s_{\frac{n}{2} - 1}$ 或 $s_{\frac{n}{2}}$ 均可，为了方便，取 $s_{\frac{n}{2}}$；

奇数：$s_{\lfloor \frac{n}{2} \rfloor}$。

$Code: $

```cpp
// Problem: CF1682A Palindromic Indices
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1682A
// Memory Limit:  MB
// Time Limit: 250000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

/*
 * Author: guzheran @YYXX
 */

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ldb;
typedef vector<int> vi;
typedef pair<int, int> pii;

#define fi first
#define se second
#define register rg
#define mp make_pair
#define pb push_back
#define pf push_front

#define rep(i, s, t) for (int i = s; i <= t; i++)
#define per(i, s, t) for (int i = t; i >= s; i--)

namespace IO {
	
	template <typename type>
	inline void Read (type &theNum) {
	
		char theChar = 0;
		int negative = 0; 
		
		theNum = 0;
		theChar = getchar();
		negative = 1;
		
		while (theChar < '0' || theChar > '9') {
			if (theChar == '-') {
				negative = -1;
			}
			
			theChar = getchar();
		}
		
		theNum = theChar ^ 48;
		
		while ((theChar = getchar()) > '0' - 1 && theChar < '9' + 1) {
			theNum = (theNum << 3) + (theNum << 1) + (theChar ^ 48);
		}
		
		theNum *= negative;
		
	}
	
	template <typename type>
	inline void RecursionWrite (type theNum) {
		
		if (theNum) {
			RecursionWrite(theNum / 10);
			putchar(theNum % 10 + 48);
		}
		
	}
	
	template <typename type1, typename type2>
	inline void Write (type1 theNum, type2 endChar) {
		
		if (!theNum) {
			putchar('0');
		}
		
		if (theNum < 0) {
			putchar('-');
			theNum *= -1;
		}
		
		if (theNum) {
			RecursionWrite(theNum / 10);
			putchar(theNum % 10 + 48);
		}
		
		putchar(endChar);
		
	}
	
}

using namespace IO;

/* template ends here */

int main () {
	
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	int T;
	
	cin >> T;
	
	while (T--) {
		int n;
		string s;
		int cnt = 0;
		
		cin >> n >> s;
		
		char a = s[n / 2];
		int index = n / 2;
			
		while (s[index] == a) {
			index++;
			cnt++;
		}
		
		index = n / 2;
		
		while (s[index] == a) {
			index--;
			cnt++;
		}
			
		cout << cnt - 1 << '\n';
	}
	
	return 0;
	
}
```

---

## 作者：Failure_Terminator (赞：0)

## Problem

给定一个字符串 $s$，删除一个字符，使字符串仍然是回文，求这样的字符个数。

## Solution

由于字符串已经回文，因此只要 $s$ 正中间存在一串全都一样的数，那么删除这个数列中的任意一个都可以。

因此只需求出这段数的长度即为答案。

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int n,T;
void solve(){
    cin>>n>>s;
    int cnt=0;
    for(int i=(n-1)/2;i>=0;i--){
    	if(s[i]==s[(n-1)/2]) cnt++; 
    	else break;
    }
    cout<<2*cnt-(n&1)<<"\n";
}
int main()
{
    cin>>T;
    while(T--) solve();
    return 0;
}
```
### 代码注释

```cpp
for(int i=(n-1)/2;i>=0;i--){
    	if(s[i]==s[(n-1)/2]) cnt++; 
    	else break;
}
cout<<2*cnt-(n&1)<<"\n";
```

这里折半进行计算，不影响结果。

~~只是想降低一些时间复杂度而已。~~

By **haimo**

---

## 作者：Jason12 (赞：0)

## 题目：
[传送门](https://www.luogu.com.cn/problem/CF1682A)
## 思路：
  由于问的是删去**单个**字符仍能保持回文的方案数，若从回文字符串的两侧删单个字符，则不能保持回文的性质（除非字符串中的字符全部相同，否则另外一侧必定有一个和被删字符相同的字符剩下），所以要从中间开始删。所以问题就变成了求该回文字符串中间字符连在一起的相同字符的数量（因为只能删掉单个字符），如样例中的 `acaaaaca`，从第 $3$ 个字符到第 $6$ 个字符，无论删掉哪个，都能保持回文的性质。就从中间的字符分别向两边遍历，记录相同字符的数量。需要注意的是：第二次遍历需要从中间字符右边的字符开始遍历，否则中间字符会被统计 $2$ 次。
## 代码：
```cpp
#include <bits/stdc++.h>
  using namespace std;
int m,n,s,i;
char c[100005];
int main()
{
	scanf("%d",&m);
	while (m--)
	{
		scanf("%d\n%s",&n,c);
		s=0;//记得初始化。
		for (i=n/2;i>=0;i--)//从中间字符向左遍历。
		{
			if (c[i]==c[n/2]) s++;
			else break;//若不相同就退出循环。
		}
		for (i=n/2+1;i<n;i++)//从中间字符的右边字符向右遍历。
		{
			if (c[i]==c[n/2]) s++;
			else break;//若不相同就退出循环。
		}
		cout<<s<<endl;
	}
	return 0;
}


```


---

## 作者：WilliamFranklin (赞：0)

### 主要思路

这道题很容易发现：我们删除中间的相同字符都可以满足题中条件。

可能说的不清楚，画个图：

![](https://cdn.luogu.com.cn/upload/image_hosting/wtmjrdik.png?x-oss-process=image/resize,m_lfit,h_1000,w_1000)

应该理解点了吧。

那么我们就可以从 $n/2$ 这个字符，向左边找，没找一个就将计数器加一个 $1$，直到不等于它后一个字符。因为我们只弄了一边的，所以还要将计数器里的值乘 $2$，就是最后的结果。

可这时，有人就要问了：如果 $n$ 整除不了 $2$，那么不就会向下取整吗？这样不就会少一个吗？

其实很简单，我们再加一个判断就可以了(当然还有种独特的方式，见代码）。

好啦，贴代码。

### AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
	int n;
	int t;
	cin >> t;
	while(t--) {
		cin >> n;
		string a;
		getchar();
		cin >> a;
		getchar();
		int ans = 0;
		for (int i = n / 2 - 1; i >= 0; i--) {
			if (a[i] == a[i + 1]) {
				ans++;
			} else {
				break;
			}
		}
		ans *= 2;
		ans += (n % 2);
		cout << ans << endl;
	}
    return 0;
}
```

可能会有些不足的地方，请大家指出，谢谢！

---

## 作者：qwq___qaq (赞：0)

### 题意
对于一个回文串 $s$，每次删除一个字符 $s_i$，求删除 $s_i$ 后可以使 $s$ 仍然回文的 $i$ 的数量。
### 思路
对于 $n$ 为奇数的情况：

假设中心为 $k$，$k$ 显然符合条件；否则如果 $i$ 在 $k$ 左边，那么原来 $[i,k-1]$ 的区间就移动到了 $[i+1,k]$，如果这两个区间如果完全相同，那么就可行；同理，若 $i>k$，那么只需判断 $[k+1,i]$ 与 $[k,i]$ 是否完全相同即可。

对于 $n$ 为偶数的情况：

假设中心为 $[l,r]$，$l$ 和 $r$ 显然可行，若 $i<l$，那么 $[i,l-1]$ 移到 $[i+1,l]$，判断两者是否相等即可；同理，若 $i>r$，那么 $[r+1,i]$ 移到 $[r,i-1]$，判断两者是否相等即可。

至于判断是否相等，可以 $O(1)$ 解决，时间复杂度 $O(n)$。
```cpp
#include<bits/stdc++.h>
#define ull unsigned long long
using namespace std;
const int maxn=2e5+5;
const ull k=31;
int T,n;
ull h[maxn],p[maxn];
char s[maxn];
inline int read(){
  	int res=0,f=0;
   	char ch=getchar();
   	while(ch<'0'||ch>'9'){
   		f|=(ch=='-');
   		ch=getchar();
   	}
   	while(ch>='0'&&ch<='9'){
   		res=(res<<1)+(res<<3)+(ch^'0');
   		ch=getchar();
   	}
   	return f?-res:res;
}
inline ull ask(int l,int r){
   	return h[r]-h[l-1]*p[r-l+1];
}
int main(){
   	T=read();
   	p[0]=1;
   	for(int i=1;i<=2e5;++i)
   		p[i]=p[i-1]*k;
   	while(T--){
   		n=read();
   		for(int i=1;i<=n;++i){
   			s[i]=getchar();
   			while(s[i]<'a'||s[i]>'z')
   				s[i]=getchar();
   		}
   		for(int i=1;i<=n;++i)
   			h[i]=h[i-1]*k+s[i]-'a';
   		int sum=0;
   		for(int i=1;i<=n;++i){
   			if(n&1){
   				int k=n+1>>1;
   				if(i==k)
   					++sum;
   				else if(i<k){
   					if(ask(i+1,k)==ask(i,k-1))
   						++sum;
   				} else{
   					if(ask(k+1,i)==ask(k,i-1))
   						++sum;
   				}
   			} else{
   				int l=n>>1,r=l+1;
   				if(i==l||i==r)
   					++sum;
   				else if(i<l){
   					if(ask(i+1,l)==ask(i,l-1))
   						++sum;
    			} else{
    				if(ask(r+1,i)==ask(r,i-1))
    					++sum;
    			}
    		}
    	}
    	printf("%d\n",sum);
    }
    return 0;
}
```

---

