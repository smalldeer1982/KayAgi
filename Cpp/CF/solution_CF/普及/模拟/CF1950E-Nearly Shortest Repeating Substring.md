# Nearly Shortest Repeating Substring

## 题目描述

You are given a string $ s $ of length $ n $ consisting of lowercase Latin characters. Find the length of the shortest string $ k $ such that several (possibly one) copies of $ k $ can be concatenated together to form a string with the same length as $ s $ and, at most, one different character.

More formally, find the length of the shortest string $ k $ such that $ c = \underbrace{k + \cdots + k}_{x\rm\ \text{times}} $ for some positive integer $ x $ , strings $ s $ and $ c $ has the same length and $ c_i \neq s_i $ for at most one $ i $ (i.e. there exist $ 0 $ or $ 1 $ such positions).

## 说明/提示

In the first test case, you can select $ k = \texttt{a} $ and $ k+k+k+k = \texttt{aaaa} $ , which only differs from $ s $ in the second position.

In the second test case, you cannot select $ k $ of length one or two. We can have $ k = \texttt{abba} $ , which is equal to $ s $ .

## 样例 #1

### 输入

```
5
4
abaa
4
abba
13
slavicgslavic
8
hshahaha
20
stormflamestornflame```

### 输出

```
1
4
13
2
10```

# 题解

## 作者：Infinite_Loop (赞：8)

# CF1950E
## 题意
给定一个长度为 $n$ 的字符串 $s$，求出长度最小的字符串 $k$，使得经过若干次拼接，新的字符串的长度等于 $s$ 的长度，且与 $s$ 不相同的字符个数小于等于 $1$。
## 思路
因为经过若干次拼接长度要和 $s$ 的长度相等，所以 $k$ 的长度必定是 $s$ 的长度的因数。于是我们就可以枚举 $k$ 的长度，当是 $s$ 的长度的因数时，进行拼接，若不同的个数小于等于 $1$，将 $ans$ 变成更优的长度。最后输出 $ans$。

然后你就会发现样例过不了。

第四组样例 ```hshahaha```，程序是这样计算的：

- $k$ 为 ```h```，有四个不一样，舍去。

- $k$ 为 ```hs```，有三个不一样，舍去。

- $k$ 为 ```hsha```，有一个不一样，输出 $4$。

可是样例为 $2$。

到底哪里错了呢？

我们发现，当 $k$ 为 ```ha``` 时，只有一个不一样，长度为 $2$，比 $4$ 更优。

然后就能发现我们需要从后往前再搞一次，就能过了！
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
string s;
int main(){
	cin>>t;
	while(t--){
		cin>>n>>s;
		int ans=n;
		for(int i=1;i<=n;i++){
			if(n%i!=0)continue;//不是因子 
			string s2=s.substr(0,i);//从前往后，截取0到i-1的字符串 
			int sum=0;
			for(int j=0,k=0;j<n;j++){
				if(s[j]!=s2[k++])sum++;
				if(k>=i)k=0;
				if(sum>1)break;
			}
			if(sum<=1)ans=min(ans,i);
			s2=s.substr(n-i,i),sum=0;//从后往前，截取n-i到n-1的字符串 
			for(int j=0,k=0;j<n;j++){
				if(s[j]!=s2[k++])sum++;
				if(k>=i)k=0;
				if(sum>1)break;
			}
			if(sum<=1)ans=min(ans,i);
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：fujiayu (赞：2)

# CF1950E - Nearly Shortest Repeating Substring

[原题地址](http://codeforces.com/problemset/problem/1950/E)

## 题意：

给定一个长为 $n$ 的小写字母字符串 $s$，求最短的字符串 $k$，使 $k$ 经过复制拼接 $x$ 次后得到的字符串 $t$ 与 $s$ 长度相等且最多有一个字符不同，输出 $k$ 的长度。

## 思路：

设 $k$ 的长度为 $m$，$s$ 的 $m\times (i-1)\sim m\times i$ 部分为 $s_i$。

首先，$m$ 一定是 $n$ 的因数，而 $n$ 最多有 $\sqrt{n}$ 个因数，所以我们可以枚举 $m$。

因为 $t$ 与 $s$ 只有一个字符不同，所以只有一个 $s_i\ne k$，因此 $s_1$ 和 $s_2$ 中至少有一个 $=k$，所以我们可以分别令 $k=s_1,s_2$，枚举判断是否合法，只要其中的一个合法就输出 $m$。

## 代码：

时间复杂度：$\Theta(n\sqrt{n})$。

```cpp
#pragma gcc optimize(2)
#include<iostream>
#include<string>
#define int long long
#define fastio ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
using namespace std;

signed main()
{
	fastio;
	int T; cin >> T;
	while(T --)
	{
		int n; string s; cin >> n >> s;
		for(int i=1; i<=n; i++)
		{
			if(n % i) continue; // m必须是n的因数
			string a = s.substr(0, i); // s1
			string b = s.substr(i, i); // s2
			int fa=0, fb=0;
			for(int j=0; j*i<n; j++) // 枚举 s_1~s_(n/m)
			{
				string t = s.substr(j*i, i); // s_(j+1)
				for(int k=0; k<t.length(); k++)
				{
					fa += (a[k] != t[k]); // s_1 -- s_(j+1)
					fb += (b[k] != t[k]); // s_2 -- s_(j+1)
				}
			}
			if(fa <= 1 || fb <= 1) // 合法
			{
				cout << i << '\n';
				break;
			}
		}
	}
	return 0;
}
```

---

## 作者：spire001 (赞：2)

## CF1950E 题解

很基础的一道题，考察了找因数的方法。

枚举 $[1,\sqrt n]$ 内 $n$ 的因数即可找到所有 $n$ 的因数。

同时由于原题面中 $i \le1$ 可得出被重复的子串要么是第一个，要么是第二个。

复杂度 $O(T\sqrt n)$

于是就可以写出代码。

### CODE

```cpp
# include <iostream>
# include <climits>
# include <cstring>
# include <algorithm>
# include <vector>
# include <cstdio>

using namespace std;

constexpr int N = 1e5 + 2;
int n;
string a, b;

bool check(int x)
{
	string tmp = a.substr(0, x); // substr(size_t, size_t = 0) 取子串函数
	b.clear(); // 记得清空
	for(int i = 1; i <= n / x; i++) b += tmp;
	
	int cnt = 0;
	
	for(int i = 0; i != n; i++) cnt += a[i] != b[i];
	
	if(cnt <= 1) return true;
	
	cnt = 0; tmp = a.substr(x, x);
	b.clear();
	for(int i = 1; i <= n / x; i++) b += tmp;
	
	for(int i = 0; i != n; i++) cnt += a[i] != b[i];
	
	if(cnt <= 1) return true;
	else return false;
}

void solve()
{
	cin >> n >> a;
	
	int ans = INT_MAX;
	
	for(int i = 1; i * i <= n; i++)
	{
		if(n % i == 0)
		{
			if(check(i)) ans = min(ans, i);
			if(check(n / i)) ans = min(ans, n / i);
		}
	}
	
	cout << ans << '\n';
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int T; cin >> T;
	
	while(T--) solve();
	
	return 0;
}

```

---

## 作者：Crazyouth (赞：0)

## 分析

显然 $x$ 是 $n$ 的因数，所以可以枚举 $n$ 的因数，再每 $x$ 个字符检查一次。把串 $S$ 分成 $x$ 个串，也就是 $S_1S_2\cdots S_x,S_{x+1}S_{x+2}\cdots S_{2x},\cdots$，把这些子串放进 set 里去重。如果 set 内只有一个串或两个满足条件的串且它们其中一种不超过一个，那么 $x$ 就是符合条件的答案。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
set<string> st;
map<string,int> mp;
int check(string s,string t)
{
	int cnt=0;
	for(int i=0;i<s.size();i++) cnt+=(s[i]!=t[i]);
	if(cnt>1) return 0;
	return 1;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		cin>>n;
		string s;
		cin>>s;
		s=' '+s;
		for(int i=1;i<=n;i++)
		{
			if(n%i) continue;
			st.clear();
			mp.clear();
			for(int j=1;j<=n;j+=i)
			{
				string t=s.substr(j,i);
				st.insert(t);
				mp[t]++;
			}
			if(st.size()>2)
			{
				continue;
			}
			if(st.size()==1)
			{
				cout<<i<<'\n';
				break;
			}
			if((mp[*st.begin()]>1&&mp[*(++st.begin())]>1)||!check(*st.begin(),*(++st.begin())))
			{
				continue;
			}
			cout<<i<<'\n';
			break;
		}
	}
}

---

## 作者：Dtw_ (赞：0)

[CF](https://codeforces.com/contest/1950/problem/E)
# 题目大意
求能否把一个字符串分解成连续的几个相同的字符串。可以使拼成的字符串与原来的字符串相差一个字符。求最短的分成的串的长度。

# 思路
我们首先可以发现的是：分成的这个字符串的长度一定是 $n$ 的因数。

那么我们考虑枚举他的长度，然后在判断一下这个串是否可以。

至于如何判断，我们先将这个串复制然后挨个判断，那这样是 $O(n)$ 的，枚举串的长度是 $O(\sqrt n)$ 的所以时间上是可过的。

至于正确性的问题，在此来证明一下。

首先我们需要拿所有分成的区间的任意两个串，然后以选择的这两个串分别拼起来，与整个字符串进行比较去判断，有一个成立那就可以。

至于为啥要取两个，我们可以看例子：

`hshaha`

`accabcabc`

就是说，如果这个长的串划分成若干个这样的串它是可行的，那么他一定是可以分成一堆相同的子串以及一个只有一个字符与其他子串不同的子串（举个例子：`ababac` 被分成 $2$ 个 `ab` 以及 $1$ 个 `ac`）或者说全是相同的子串 (`ababab` 分成 $3$ 个 `ab`) 那么我们只需要找任意两个不同的子串来判断即可。虽然我们可能找到同一个，但是他显然不影响（`aba` 都找到 `a` 但还是不影响结果，还是因为刚才说的结论）所以我们可以随便取两个来判断。

# Code
```cpp
#include<bits/stdc++.h>

using namespace std;

#define endl '\n'

#define TRACE 1
#define tcout TRACE && cout

#define IN(o) insert(o)

#define fi first
#define se second

#define int long long

#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

const int INF = 0x3f3f3f3f3f3f3f3f;

const int P = 998244353;

const int N = 1e6 + 10;

void solve()
{
	int n;
	cin >> n;
	string s;
	cin >> s;
	for(int i=1; i<=n; i++) //我找的是第一个和最后一个，其实取任意两个都可以
	{
		if(n % i == 0)
		{
			int p = 2;
			for(int j=0; j<i; j++)
			{
				for(int k=j+i; k<n; k+=i)
				{
					if(s[k] != s[j])
					{
						p--;
					}
				}
			}
			if(p > 0)
			{
				cout << i << endl;
				return ;
			}
			p = 2;
			for(int j=n-i; j<n; j++)
			{
				for(int k=j-i; k>=0; k-=i)
				{
					if(s[k] != s[j])
					{
						p--;
					}
				}
			}
			if(p > 0)
			{
				cout << i << endl;
				return ;
			}
		}
	}
}

signed main()
{
	int t;
	cin >> t;
	while(t--)
	{
		solve();
	}
	return 0;
}




```

---

## 作者：Sternenlicht (赞：0)

### 思路

显然，想要有一个字符串满足题意，这个字符串的长度 $len$ 必须为 $n$ 的因数。那我们先求出 $n$ 的所有因数。

易知，$len$ 的最大值为 $n$，即最坏情况下，$n$ 即为答案。

如果 $len < n$ 呢？那么此时一定满足 $len \le \frac{n}{2}$ 的。我们从小到大枚举 $len$。考虑将当前的两种可能的不同方案都列出来，即取两个长度均为 $len$ 的子串，且这两个子串不重合。显然，若其中的一个子串满足条件，那么此时的 $len$ 即为最小值。

```cpp
#include <bits/stdc++.h>
#define il inline
namespace Fast_IO {
	template <typename T> il void read(T &x) {
		x = 0; int f = 0; char ch = getchar();
		while (!isdigit(ch)) f |= (ch == '-'), ch = getchar();
		while (isdigit(ch)) x = x * 10 + (ch - 48), ch = getchar();
		x = f ? -x : x;
	}
	template <typename T, typename ...Args>
	il void read(T &x, Args& ...args) {read(x), read(args...);}
	template <typename T> il void write(T x, char c = '\n') {
		if (x) {
			if (x < 0) x = -x, putchar('-');
			char a[30]; short l;
			for (l = 0; x; x /= 10) a[l ++] = x % 10 ^ 48;
			for (l --; l >= 0; l --) putchar(a[l]);
		} else putchar('0');
		putchar(c);
	}
} using namespace Fast_IO;
using namespace std;

il void solve() {
	int n; read(n);
	string s; cin >> s;
	vector<int> vec; //存储 n 的因数
	for (int i = 1; i <= sqrt(n); i ++)
		if (n % i == 0)
			if (i * i == n) vec.push_back(i);
			else vec.push_back(i), vec.push_back(n / i);
	sort(vec.begin(), vec.end()); //注意从小到大排序，以便之后的遍历 
	int len = vec.size();
	for (int i = 0; i < len; i ++) {
		int x = vec[i]; //截取的子串长度
		if (x == n) {write(x); return ;} //最坏情况 
		string s1 = "", s2 = ""; //两种可能的不同方案 
		for (int k = 0; k < x; k ++) s1 += s[k], s2 += s[k + x];
		string form1 = "", form2 = ""; //两种方案所形成的最终字符串
		for (int k = 1; k <= n / x; k ++) form1 += s1, form2 += s2;
		int cnt1 = 0, cnt2 = 0; //两种方案与原字符串的不同位置的个数
		for (int k = 0; k < n; k ++) cnt1 += (form1[k] != s[k]), cnt2 += (form2[k] != s[k]) ;
		if (min(cnt1, cnt2) <= 1) {write(x); return ;} //由于排过序，所以一定是最小的 
	}
}
signed main() {
	int T; read(T);
	while (T --) solve();
	return 0;
}
```

---

## 作者：what_can_I_do (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1950E)

首先根据题目可知 $k$ 的长度一定是 $n$ 的因数，所以我们可以先枚举 $k$ 的长度，也就是 $n$ 的因数。

将 $k$ 的长度记为 $len$。

然后取出 $s$ 的前 $len$ 个字符和第 $len+1$ 到第 $2\times len$ 个字符，分别组成字符串去进行操作。

具体的操作就是把这个字符串当作 $k$，然后将 $\frac{n}{len}$ 个 $k$ 连起来，与 $s$ 相对比，如果有偏差的字符个数不超过 $1$，那么就说明长度为 $len$ 是可行的。

其实不需要真的将这些字符取出连成字符串，只需要用在 $s$ 中的相对应的字符去进行比对就行了。

# CODE:
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int t;
int n;
char s[200010];
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		for(register int i=1;i<=n;i++) cin>>s[i];
		int f=0;
		for(register int len=1;len<=n;len++)
		{
			if(n%len) continue;
			int sum=0;
			for(register int k=2;k<=n/len;k++)
			{
				for(register int i=1;i<=len;i++)
				{
					if(s[i]!=s[i+(k-1)*len]) sum++;
					if(sum>1) break;
				}
				if(sum>1) break;
			}
			if(sum<=1)
			{
				printf("%d\n",len),f=1;
				break;
			}
			sum=0;
			for(register int k=1;k<=n/len;k++)
			{
				if(k==2) continue;
				for(register int i=1;i<=len;i++)
				{
					if(s[len+i]!=s[i+(k-1)*len]) sum++;
					if(sum>1) break;
				}
				if(sum>1) break;
			}
			if(sum<=1)
			{
				printf("%d\n",len),f=1;
				break;
			}
		}
		if(!f) printf("%d\n",n);
	}
	return 0;
}
```

---

## 作者：PDAST (赞：0)

## 题意
在字符串 $s$ 中取一段长度为 $k$ 的字串，不断重复，直到长度与 $s$ 相同，且与 $s$ 不同的字符数小于等于 $1$，求最小的 $k$ 值。
## 思路
水题一道，直接暴力枚举长度，暴力判断是否可行即可。
## 代码
~~~cpp
#include<bits/stdc++.h>
using namespace std;
signed main(){
	int T,n;
	cin>>T;
	while(T--){
		string st;
		cin>>n>>st;
		for(int len=1;len<=n;len++){
			if(n%len){
				continue;
			}
			int t=0;
			for(int i=0;i<n&&t<=1;i++){
				if(st[i%len]!=st[i]){
					t++;
				}
			}
			if(t<=1){
				cout<<len<<"\n";
				break;
			}
			if(len!=n){
				t=0;
				for(int i=0;i<n&&t<=1;i++){
					if(st[i%len+len]!=st[i]){
						t++;
					}
				}
				if(t<=1){
					cout<<len<<"\n";
					break;
				}
			}
		}
	}
	return 0;
}
~~~

---

