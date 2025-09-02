# Diverse Substrings

## 题目描述

A non-empty digit string is diverse if the number of occurrences of each character in it doesn't exceed the number of distinct characters in it.

For example:

- string "7" is diverse because 7 appears in it $ 1 $ time and the number of distinct characters in it is $ 1 $ ;
- string "77" is not diverse because 7 appears in it $ 2 $ times and the number of distinct characters in it is $ 1 $ ;
- string "1010" is diverse because both 0 and 1 appear in it $ 2 $ times and the number of distinct characters in it is $ 2 $ ;
- string "6668" is not diverse because 6 appears in it $ 3 $ times and the number of distinct characters in it is $ 2 $ .

You are given a string $ s $ of length $ n $ , consisting of only digits $ 0 $ to $ 9 $ . Find how many of its $ \frac{n(n+1)}{2} $ substrings are diverse.

A string $ a $ is a substring of a string $ b $ if $ a $ can be obtained from $ b $ by deletion of several (possibly, zero or all) characters from the beginning and several (possibly, zero or all) characters from the end.

Note that if the same diverse string appears in $ s $ multiple times, each occurrence should be counted independently. For example, there are two diverse substrings in "77" both equal to "7", so the answer for the string "77" is $ 2 $ .

## 说明/提示

In the first test case, the diverse substring is "7".

In the second test case, the only diverse substring is "7", which appears twice, so the answer is $ 2 $ .

In the third test case, the diverse substrings are "0" ( $ 2 $ times), "01", "010", "1" ( $ 2 $ times), "10" ( $ 2 $ times), "101" and "1010".

In the fourth test case, the diverse substrings are "0" ( $ 3 $ times), "01", "011", "0110", "1" ( $ 2 $ times), "10", "100", "110" and "1100".

In the fifth test case, the diverse substrings are "3", "39", "399", "6", "9" ( $ 4 $ times), "96" and "996".

In the sixth test case, all $ 15 $ non-empty substrings of "23456" are diverse.

## 样例 #1

### 输入

```
7
1
7
2
77
4
1010
5
01100
6
399996
5
23456
18
789987887987998798```

### 输出

```
1
2
10
12
10
15
106```

# 题解

## 作者：Xy_top (赞：9)

这道题看似很复杂，其实很简单

首先我们可以得到一个长超过 $10$ 的数字串，里面出现最多的数字的次数最少也得是 $2$ （即 $0,1,2...,9$ 各出现一次，然后再出现一个已经有的数字）

由此我们可以得出一个长超过 $100$ 的数字串，里面出现最多的数字的次数最少是 $11$，而这个串里的数字种类最多有 $10$ 种，所以只要长度超过 $100$ 的数字串都是不合法的。

那么就可以暴力了，枚举数字串子串的开头，然后每一个开头我们只往后 $100$ 个，看这些数字串是否合法，超过 $100$ 的就没有意义了，不需要枚举。

这种算法时间复杂度是 $O(T\times n\times 10000)$，因为数字只有 $10$ 种，开一个桶保存，时间复杂度就是 $O(T\times n\times 100)$，可以通过此题

上代码：

```cpp
#include <iostream>
using namespace std;
long long t, n, ans;
int main()
{
	scanf ("%d", &t);
	while (t --)
	{
		ans = 0;
		cin >> n;
		string s;
		cin >> s;
		for (long long i = 0; i < n; ++ i)
		{
			long long d[10] = {0}, mx = 0, dis = 0;
			for (long long j = i; j < min (i + 101, n); ++ j)
			{
				d[s[j] - '0'] ++;
				if (d[s[j] - '0'] == 1) ++ dis;
				mx = max (mx, d[s[j] - '0']);
				if (mx <= dis) ans ++;
			}
		}
		cout << ans << endl;
	}
	return 0;
}
```


---

## 作者：Dry_ice (赞：1)

[更好的阅读体验](https://www.cnblogs.com/dry-ice/p/cf1748b.html)

题链：[cf](https://codeforces.com/contest/1748/problem/B) [luogu](https://www.luogu.com.cn/problem/CF1748B)

> 诈骗题。

## Description
给你一个数字（$0\sim 9$）组成的字串，问有多少个子串满足：**不同数字种类数**不少于**相同数字的最多出现次数**。

## Analysis
暴力思路很好想其实，无非就是暴力跑每一个子串，$\mathcal{O}(n^3)$，略加优化即可 $\mathcal{O}(n^2)$。

考虑一个合法的子串**最多长度不会超过 $100$**，证明也很容易：根据**鸽巢原理**，当全长达 $101$ 时，至少有一种数字个数达到 $11$ 或以上，而最多只有 $10$ 个不同数字种类，显然不满足**合法**的定义。故**合法**必须长度不超过 $100$。

由此，时间复杂度降为 $\mathcal{O}(100n)$。可写。~~不难看出是一道诈骗题。~~

## Code
此处为了进一步优化，用 $a$ 和 $b$ 直接记录**不同数字种类数**和**相同数字的最多出现次数**。可以看出当总长超出 $100$ 时亦会退出。

```cpp
#include <stdio.h>
const int N = (int)2e5 + 5;
int n; char s[N];
inline void Solve() {
	scanf("%d %s", &n, s + 1); long long ans = 0; int a, b;
	for (int i = 1; i <= n; ++i) {
		a = b = 0; int vis[10] = {0};
		for (int j = i; j <= n && a <= 10 && b <= 10; ++j) {
			if (!vis[s[j] - '0']) ++a; ++vis[s[j] - '0']; //不同
			if (vis[s[j] - '0'] > b) b = vis[s[j] - '0']; //最大次数
//			printf("%d %d: %d %d\n", i, j, a, b);
			if (a >= b) ++ans; //合法
		}
	}
	printf("%lld\n", ans);
}
int main(void) {
	int T; for (scanf("%d", &T); T--; ) Solve();
	return 0;
}
```

## The end. Thanks.

~~Codeforces 名手：诈骗题~~

---

## 作者：uid_310801 (赞：0)

因为数字最多只有 $10$ 个，若子串为多变的那么每个数字出现次数不超过 $10$ 次。所以子串长度不超过 $100$.

那么我们暴力枚举 $i$，从 $i$ 往后暴力枚举 $100$ 个数，检查是否满足条件即可。过程可以用桶轻松实现。

```cpp
/********************
  *	author:Spouter_27
  *	place:spst Alego
  * with:marmoreal_777
  ******************/
#include<bits/stdc++.h>
using namespace std;
//#define int long long
typedef long long ll;
const ll N=2e5+10;
ll n,T,t[10];
string a;
void init(){
}
void solve(){
	scanf("%lld\n",&n);
	getline(cin,a);
	ll ans=0;
	for(int i=0;i<n;i++){
		memset(t,0,sizeof(t));
		ll cnt=0,maxn=0;
		for(int j=i;j<min(n,i+101ll);j++){
			t[a[j]-'0']++;
			if(t[a[j]-'0']==1)	cnt++;
			maxn=max(maxn,t[a[j]-'0']);
			if(maxn<=cnt)	ans++;
		}
	}
	printf("%lld\n",ans);
	
}
signed main(){
	scanf("%lld",&T);
	init();
	while(T--){
		solve();
	}
	return 0;
}
/*
exSample:

*/

```


---

## 作者：shinzanmono (赞：0)

# 题意

定义一个数字串是多变的当且仅当其中所有数字的重复次数均不超过其中不同数字的种类数。

给定一个由 $0$ 到 $9$ 组成的长为 $n$ 的数字串 $s$，求其不同的多变的子串 $s_{[l,r]}$ 的个数。
  
# Solution：

因为一共有十个数字~~不会有人不知道吧~~，所以每个数字最多出现十次，所以字符串的长度一定小于 $10 \times 10 = 100$。所以只需暴力枚举每个长度 $<100$ 的子串，维护区间每个数字出现的次数与数字种类数即可，时间复杂度 $\Theta(1000\sum n)$，可以通过此题。

# Code:

```cpp
#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
int main() {
    std::ios::sync_with_stdio(false);
    int t;
    std::cin >> t;
    while (t--) {
        int n, ans = 0, type, cnt[10];
        std::string s;
        std::cin >> n >> s;
        for (int i = 0; i < n; i++) {
            memset(cnt, 0, sizeof cnt), type = 0;
            for (int j = 0; j < std::min(n - i, 100); j++) {
                int num = s[i + j] - '0';
                cnt[num]++;
                if (cnt[num] == 1) type++;
                bool flag = true;
                for (int k = 0; k < 10; k++)
                    if (cnt[k] > type) flag = false;
                if (flag) ans++;
            }
        }
        std::cout << ans << std::endl;
    }
    return 0;
}

```

---

## 作者：Cczzyy20150005 (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1748B)

## 思路
暴力，但不完全暴力。

从题面了解到字符就只有十种数字，又要使每数字的个数不超过数字种数。  
所以最长的“多样的”子串最长只有 $10 \times 10=100$ 个字符。  
于是我们从 $1$ 枚举到 $n$，每次暴力枚举子串长度，判断合不合法就行了。  
因为子串长度最多就 $100$，还要判断十个数字合不合法，所以时间复杂度为 $O(1000n)$，可以通过此题。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100001];
int cnt[10];
void solve(){
	int n,cn=0,ans=0;
	cin>>n;
	for(int i=1;i<=n;i++)scanf("%1d",&a[i]);
	for(int i=1;i<=n;i++){
		cn=0;
		for(int i=0;i<10;i++)cnt[i]=0;//需要初始化每种数字出现次数
		for(int j=1;j<=100&&(i+j-1)<=n;j++){
			int r=i+j-1;
			cnt[a[r]]++;
			if(cnt[a[r]]==1)cn++;//计算数字种数
			int f=0;
			for(int i=0;i<10;i++){//暴力判断
				if(cnt[i]>cn){
					f=1;
					break;
				}
			}
			if(f==0)ans++;
		}
	}
	printf("%d\n",ans);
}
int main(){
	int t;
	cin>>t;
	while(t--)solve();	
	return 0;
}
```

---

