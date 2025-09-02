# Distinct Split

## 题目描述

Let's denote the $ f(x) $ function for a string $ x $ as the number of distinct characters that the string contains. For example $ f(\texttt{abc}) = 3 $ , $ f(\texttt{bbbbb}) = 1 $ , and $ f(\texttt{babacaba}) = 3 $ .

Given a string $ s $ , split it into two non-empty strings $ a $ and $ b $ such that $ f(a) + f(b) $ is the maximum possible. In other words, find the maximum possible value of $ f(a) + f(b) $ such that $ a + b = s $ (the concatenation of string $ a $ and string $ b $ is equal to string $ s $ ).

## 说明/提示

For the first test case, there is only one valid way to split $ \texttt{aa} $ into two non-empty strings $ \texttt{a} $ and $ \texttt{a} $ , and $ f(\texttt{a}) + f(\texttt{a}) = 1 + 1 = 2 $ .

For the second test case, by splitting $ \texttt{abcabcd} $ into $ \texttt{abc} $ and $ \texttt{abcd} $ we can get the answer of $ f(\texttt{abc}) + f(\texttt{abcd}) = 3 + 4 = 7 $ which is maximum possible.

For the third test case, it doesn't matter how we split the string, the answer will always be $ 2 $ .

## 样例 #1

### 输入

```
5
2
aa
7
abcabcd
5
aaaaa
10
paiumoment
4
aazz```

### 输出

```
2
7
2
10
3```

# 题解

## 作者：WilliamFranklin (赞：8)

### 主要思路

首先，观察一下题：分成两个字符串！！！这就意味着我们可以枚举一下这两个字符串 $a$ 和 $b$ 的分界线，然后求出 $f(a) + f(b)$ 的最大值即可。

但我们想，如何快速求出来 $f(a) + f(b)$ 的最大值呢？

嗯。。。我们可以很容易想到，只要求出一个字符串中每一个字符出现的个数，再用总数减去，就是第二个字符串中每一个字符出现的个数了，然后判断一下两个字符串分别有多少个字符出现字数大于 $0$ 即可。

字符串长度为 $n$，小写字母一共就 $26$ 个，所以时间复杂度就是 $O(26 \cdot n)$ 的。

可能说的不太清楚，看代码吧！

### AC Code

```cpp
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <cstdio>
#include <sstream>

using namespace std;

int cnt[30], pre[30];

int main() {
	int t;
	
	cin >> t;
	
	while (t--) {
		memset(cnt, 0, sizeof(cnt));
		memset(pre, 0, sizeof(pre));
		
		int n;
		string s;
		
		cin >> n >> s;
		
		for (int i = 0; i < n; i++) {
			cnt[s[i] - 'a'] ++;
		}
		
		int nans = 0;
		for (int i = 0; i < n; i++) {
			pre[s[i] - 'a']++;
			
			int ans = 0;
			for (int i = 0; i < 26; i++) {
				if (pre[i]) {
					ans++;
				}
				
				if (cnt[i] != pre[i]) {
					ans++;
				}
			}
			
			nans = max(nans, ans);
		}
		
		cout << nans << endl;
	}
	
	return 0;
}
```

可能会有一些不足，请各位大佬指出，谢谢！

还有。。。点个赞呗。。。

---

## 作者：BlackPanda (赞：4)

**[Problem](https://www.luogu.com.cn/problem/CF1791D)**

------------
## Description

有 $t$ 次询问，每次给出 $n$ 和长度为 $n$ 的字符串 $s$。

定义 $f(x)$ 为字符串 $x$ 中不同字符的个数。求出将 $s$ 划分成两个非空字符串 $a$ 和 $b$ 后 $f(a) + f(b)$ 的最大值。

------------
## Solution

有思维难度的模拟题，建议评上位橙。

记数组 $c1$ 为子串 $a$ 中每个字符的出现次数，数组 $c2$ 为子串 $b$ 中每个字符的出现次数。这里的 $a$ 和 $b$ 指将字符串 $s$ 划分后的两个子串。

我们可以先将字符串中每个字符出现的次数记到数组 $c1$ 中，然后遍历字符串，每次将 $s_i$ 对应字符的数量从 $c1$ 中减去 $1$，然后在 $c2$ 数组中加上 $1$，相当于从 $i$ 处将字符串划分成两个子串，然后枚举 $1 \sim 26$ 个字符，取每次 $f(a) + f(b)$ 的最大值即可。

------------
## Code

赛时 AC 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
string s;
int c1[205], c2[205];
int res = 0;

void solve()
{
	res = 0;
	memset(c1, 0, sizeof(c1));
	memset(c2, 0, sizeof(c2));
	cin >> n >> s;
	for (int i = 0; i < n; i ++ )
		c1[s[i] - 'a' + 1] ++ ;
	for (int i = 0; i < n; i ++ )
	{
		c1[s[i] - 'a' + 1] -- ;
		c2[s[i] - 'a' + 1] ++ ;
		int s1 = 0, s2 = 0;
		for (int j = 1; j <= 26; j ++ )
		{
			if (c1[j])	s1 ++ ;
			if (c2[j])	s2 ++ ;
		}
		res = max(res, s1 + s2);
	}
	cout << res << endl;
	return ;
}

int main()
{
	int T; cin >> T;
	while (T -- )	solve();
	return 0;
}

```

---

## 作者：arrow_king (赞：0)

## 思路

由于小写字符的数量只有 $26$ 个，所以可以开一个长度 $26$ 的桶来记录。

~~当然了如果非要用主席树来记录的话没人管你~~

首先计算 $f(s)$ 的方法是直接线性扫一遍桶来求解，~~这里可以近似当成常数~~。

由于要将原字符串切成两半，分别统计 $f(s)$，所以开一个前缀一个后缀。

显然预处理的时间耗费有点大，所以考虑动态更新。

由于每次只会改变一个点，所以每次经过一个字符时，可以在前缀数组上加 $1$，在后缀数组上减 $1$。这样就可以枚举切分点，然后枚举桶求得答案，最终答案取中间所有情况的 $\max$ 就可以了。

时间复杂度 $\mathcal O(nw)$，其中 $w$ 是最大 $26$ 的“常数”。

似乎 $w$ 的大小与 $\log n$ 是一个量级的，所以也可以当做近似的 $\mathcal O(n\log n)$。

## 代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
#define ll long long
#define il inline
il ll read() {
	ll x=0,f=1;char c=getchar();
	while(c<'0'||c>'9') {if(c=='-') {f=-1;} c=getchar();}
	while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
int t,n,b1[27],b2[27];
char s[200005];
int main() {
	t=read();
	while(t--) {
		for(int i=1;i<=26;i++) b1[i]=b2[i]=0;
		n=read();
		scanf("%s",s+1);
		for(int i=1;i<=n;i++) b2[s[i]-'a'+1]++;
		int ans=-1,now=0;
		for(int i=1;i<n;i++) {
			b2[s[i]-'a'+1]--;
			b1[s[i]-'a'+1]++;
			now=0;
			for(int i=1;i<=26;i++) {
				if(b1[i]) now++;
				if(b2[i]) now++;
			}
			ans=max(ans,now);
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：LincW (赞：0)

考虑枚举切割的位置 $k$，枚举时维护：

- 字符串 $a$ 中每个字母出现的频率 $\mathrm{freq}_{a,\mathrm{ch}}$。

- 字符串 $b$ 中每个字母出现的频率 $\mathrm{freq}_{b,\mathrm{ch}}$。

- 字符串 $a$ 中出现的字母种数 $\mathrm{typ}_a$。

- 字符串 $b$ 中出现的字母种数 $\mathrm{typ}_b$。

每次将 $k\gets k+1$ 时，依次进行以下操作，以维护。

1. $\mathrm{freq}_{b,s[k+1]}\gets\mathrm{freq}_{b,s[k+1]}-1$。

2. $\mathrm{freq}_{a,s[k+1]}\gets\mathrm{freq}_{a,s[k+1]}+1$。

3. 若 $\mathrm{freq}_{b,s[k+1]}=0$（这是 $b$ 的唯一一个 $s_{k+1}$ 字母），$\mathrm{typ}_b\gets\mathrm{typ}_b-1$（唯一一个 $s_{k+1}$ 字母被分到了 $a$， $b$ 不再有 $s_{k+1}$，字母种数减少）。

4. 若 $\mathrm{freq}_{a,s[k+1]}=1$，$\mathrm{typ}_a\gets\mathrm{typ}_a+1$（类似，不赘述）。

答案取枚举过程中最大的 $\mathrm{typ}_a+\mathrm{typ}_b$。

```cpp
#include<iostream>
using namespace std;
typedef long long ll;
int freq[30],freq2[30];
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		string s;
		int n;
		cin>>n>>s;
		int get1=0,get2=0,mxa=0;
		for(int i=0;i<26;++i) freq[i]=0;
		for(int i=0;i<26;++i) freq2[i]=0;
		for(int i=0;i<n;++i)
		{
			freq[s[i]-'a']++;
			if(freq[s[i]-'a']==1) get1++;
		}
		for(int i=0;i<n-1;++i)
		{
			freq2[s[i]-'a']++;
			freq[s[i]-'a']--;
			if(freq[s[i]-'a']==0) get1--;
			if(freq2[s[i]-'a']==1) get2++;
			mxa=max(mxa,get1+get2);
		}
		cout<<mxa<<endl;
	 } 
	return 0;
}
```


---

## 作者：loser_seele (赞：0)

简单题。

枚举所有断点，然后暴力判断 $ a,b $ 中颜色分别出现了几种，这个可以开桶记录，如果一个颜色出现超过一次则答案 $ +1 $。最后在所有情况中取最大值即可。

时间复杂度 $ \mathcal{O}(n\left| S \right|) $，其中 $ \left| S \right| =26 $ 为字符集大小，可以通过。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int a[2000020],ans=0;
void gen(int n)
{
int f[2000020];
for(int i=1;i<=n;i++)
f[i]=i;
do
{
if(0)//add something here.
ans++;
}while(next_permutation(f+1,f+n+1));
}
#define Y cout<<"Yes"<<'\n'
#define N cout<<"No"<<'\n'
int cnt[26],p[26];
signed main()
{
int T;
cin>>T;
while(T--)
{
    int n; 
    string s; 
    cin>>n>>s;
    for(int i=0;i<26;i++)
    cnt[i]=p[i]=0;
    for(auto x: s) 
    cnt[x-'a']++;
    int ans=0;
    for(auto x: s) 
    {
        --cnt[x-'a'];
        ++p[x-'a'];
        int cur = 0;
        for(int i = 0; i < 26; ++i) 
        cur += min(1ll, cnt[i]) + min(1ll, p[i]);
        ans = max(ans, cur);
    }
    cout<<ans<<'\n';
}
}
```


---

