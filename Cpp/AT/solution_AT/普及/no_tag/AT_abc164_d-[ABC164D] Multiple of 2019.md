# [ABC164D] Multiple of 2019

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc164/tasks/abc164_d

`1` から `9` までの数字のみからなる文字列 $ S $ が与えられます。

次のような条件を満たす整数の組 $ (i,j) $ ($ 1\ <\ =\ i\ <\ =\ j\ <\ =\ |S| $) の総数を求めてください。

条件: $ S $ の $ i $ 文字目から $ j $ 文字目までを $ 10 $ 進法の整数としてみると、この整数は $ 2019 $ の倍数である。

## 说明/提示

### 制約

- $ 1\ <\ =\ |S|\ <\ =\ 200000 $
- $ S $ は `1` から `9` までの数字のみからなる文字列

### Sample Explanation 1

条件を満たすのは $ (1,5),\ (5,9),\ (9,13) $ の $ 3 $ 個です。

### Sample Explanation 3

条件を満たす整数の組は存在しません。

## 样例 #1

### 输入

```
1817181712114```

### 输出

```
3```

## 样例 #2

### 输入

```
14282668646```

### 输出

```
2```

## 样例 #3

### 输入

```
2119```

### 输出

```
0```

# 题解

## 作者：Lynkcat (赞：10)

挺板子的一题。

考虑后缀的一个数 $a_i$ 。那么这个数对答案的贡献是满足 $(a_i-a_j) \mod 2019=0 ( i \leq j \leq len)$ 的 $j$ 的个数，上述式子又可转化为 $a_i \mod 2019=a_j \mod 2019$ ，直接从后往前扫搞个桶记录即可。

```
string st;
int n,s[N],b[N],ans;
signed main()
{
	cin>>st;
	n=st.length();
	st=' '+st;
	s[n+1]=0;
	ll p=1;
	for (int i=n;i>=1;i--) s[i]=(s[i+1]+(ll)(st[i]-'0')*p%mod)%mod,p=p*10%mod;
	for (int i=n+1;i>=1;i--)
	{
		ans=ans+b[s[i]];
		b[s[i]]++;
	}
	writeln(ans);
}

---

## 作者：b6e0_ (赞：10)

本人第2篇题解，求兹磁qwq

[Atcoder题面传送门](https://atcoder.jp/contests/abc164/tasks/abc164_d) [洛谷题面传送门](https://www.luogu.com.cn/problem/AT4892) [博客食用更佳](https://www.luogu.com.cn/blog/b6e0/tijie-AT4892)

本文中字符串$s$的下标是从$1$开始的。

$|s|$最大为$200000$，暴力枚举区间肯定是不行的。我们一般处理统计区间个数的问题时是怎么做的？前缀和或者后缀和。这里前缀和是不行的，因为两个前缀和相减得不到区间。这里就要用到后缀和：后缀和$s[l]-s[r+1]$就能得到$[l,r]$这个区间表示的数（其实还要除以$10^{|s|-r}$，但是对于这道题可以忽略不计）。

对于一段区间$[l,r]$，如果$s[l]\equiv s[r+1]\pmod{2019}$，那么$[l,r]$表示的数一定$\bmod$ $2019$为$0$。~~读者自证不难。~~ 上面的同余式移项得$s[l]-s[r+1]\equiv0\pmod{2019}$，减出来后面的那一串$0$可以不用管。

对于某一个余数$i$，记余$i$的后缀个数为$t$，那么这样余$i$的$s[l],s[r+1]$的对数就是$\dfrac{t(t-1)}2$。那么直接用一个计数数组记录每一个余数的个数就行了。
## 但是，坑点来了！！！

对于余$0$的情况。这个后缀可以自成一段。**所以答案要加上余$0$的个数。** 这东西卡了我半天。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long tot[2105],z[200010];//应该是要long long的
int main()
{
	string s;
	int i;
	long long x=1,ans;
	cin>>s;
	for(i=s.size()-1;i>=0;i--)
	{
		z[i]=(z[i+1]+(s[i]-'0')*x)%2019;//做后缀和
		x=x*10%2019;
		tot[z[i]]++;//统计余数
	}
	ans=tot[0];//这句不能忘！！！
	for(i=0;i<2019;i++)
		ans+=tot[i]*(tot[i]-1)/2;
	cout<<ans;
	return 0;
}
```

---

## 作者：SpeedStar (赞：4)

### 算法分析
令$n$为$S$的长度，$a_k$为$S$的左数第$k$个数字。

对于$a_j + 10a_{j-1} + 10^2a_{j-2} + 10^{j-i}a_i$为$2019$的倍数的$(i,j)$元满足题目要求。

此外，$2019$不是$2$或$5$的倍数，所以存在$10 \, mod\, 2019$的逆元。所以$10n$为$2019$的倍数当且仅当$n$为$2019$的倍数。

令$T_k$为$S$的从$k+1$开始的数，也就是$a_n + 10a_{n-1} + \cdots + 10^{n-k-1}a_{k+1}(T_n = 0)$。然后，对于$10^{n-j}(T_{i-1} - T_j)$为$2019$的倍数的$(i,j)$元满足题目要求，换句话说就是$T_{i-1}\equiv T_j\, (mod\, 2019)$。

最后，我们只需计算出所有$T_i\, (mod\, 2019)$的余数，然后在同余的集合内任取$2$个元素，把此方案数累加进答案即可。


### C++代码
```cpp
#include <iostream>
#include <string>
#define rep(i, n) for(i = 0; i < n; i++)
#define int long long

using namespace std;

string s;
int cnt[2019];

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> s;
	int n = s.length();
	
	int i;
	int r = 0;
	int t = 1;
	cnt[r]++;
	for (i = s.length() - 1; i >= 0; i--) {
		r = (r + (s[i] - '0') * t) % 2019;
		t = (t * 10) % 2019;
		cnt[r]++;
	}
	
	int ans = 0;
	for (i = 0; i < 2019; i++) {
		ans += cnt[i] * (cnt[i] - 1) / 2;
	}
	cout << ans << endl;
	
	return 0;
}
```


---

## 作者：whx2009 (赞：1)

## 本题思路：
这道题乍一看上去十分复杂，但只要细细一想就可以发现一件事，那就是如果一个数能被 $2019$ 整除，那么在它后面再加一个能被 $2019$ 整除的数也能被 $2019$ 整除。那么我们就可以把从每一个数开始的第一个能被 $2019$ 整除的数枚举出来，然后这个数提供的数据就将是则个数据最前面的一位的前面满足条件的个数加 $1$。这样暴力走一遍就可以了！
## 本题代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[200001];
long long b[200001],c[200001];
int main()
{
	cin>>a+1;
	int n=strlen(a+1);
	for(int i=1;i<=n;i++)
	{
		a[i]=a[i]-'0';
	}
	for(int i=1;i<=n;i++)
	{
		long long sum=a[i];
		for(int j=i+1;j<=n;j++)
		{
			sum=(sum*10+a[j])%2019;//加一个%2019可以防止数字太大超时的可能性 
			if(sum==0)
			{
				b[j]=c[i-1]+1;//算一共提供几个数据 
				c[j]=c[i-1]+1; 
				break;
			}
		}
	}
	long long ans=0;
	for(int i=1;i<=n;i++)
	{
		ans+=b[i];
	}
	cout<<ans;
	return 0;
}
```
 

---

## 作者：kkxacj (赞：0)

#### [题目传送门](https://www.luogu.com.cn/problem/AT_abc164_d)

#### 题目大意

给出一个由 $1$ 到 $9$ 的数字组成的字符串 $S$，求其中有多少段数是 $2019$ 的整数倍。

#### 思路
提供一个暴力优化的方法。

首先我们要知道，两个为 $2019$ 的倍数拼接在一起的新的数一定为 $2019$ 的倍数，所以我们可以先暴力求出以第 $i$ 为头的第一个为 $2019$ 的倍数的数，如果以 $i - 1$ 为结尾的有为 $2019$ 的倍数的数，那么加上它，假设结尾为 $j$，那么将以 $j$ 结尾的先加上他本身的一，再加以 $i - 1$ 为结尾的有为 $2019$ 的倍数的数的个数。

code
```cpp
#include<bits/stdc++.h>
using namespace std;
int ans,m,l,t[4000010];//t为标记以i结尾的数有几个
unsigned long long sum;
string s;
int main()
{
	cin >> s;
	for(int i = 0;i < s.size();i++)
	{ 
		sum = 0;
		l = s.size();
		for(int j = i;j < l;j++)
		{
 			sum = sum * 10 + s[j] - '0';
			if(sum % 2019 == 0)
			{
				ans++;
				ans += t[i - 1];
				t[j] = t[i - 1] + 1;
				break;
			} 
			sum %= 2019;//每次取模，避免爆掉
		} 
	}
	cout << ans << endl;
	return 0;
}

```


---

