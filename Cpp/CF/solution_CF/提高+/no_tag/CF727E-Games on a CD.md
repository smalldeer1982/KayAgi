# Games on a CD

## 题目描述

已知g个长度为k互不相同的字符串r[1..g]和一个长度为n×k的环形字符串s，问是否能从r[1..g]中选出n个组成字符串s。如果能，则输出YES，并在第二行按在s中的顺序输出对应的r的编号，否则输出NO。

## 样例 #1

### 输入

```
3 1
abc
4
b
a
c
d
```

### 输出

```
YES
2 1 3 
```

## 样例 #2

### 输入

```
4 2
aabbccdd
4
dd
ab
bc
cd
```

### 输出

```
NO
```

# 题解

## 作者：sdxjzsq (赞：5)

### 题目链接  
https://www.luogu.com.cn/problem/CF727E  
https://codeforces.com/problemset/problem/727/E  
### 题意  
已知$g$个长度为$k$互不相同的字符串$r[1..g]$和一个长度为$n\times k$的环形字符串$s$，问是否能从$r[1..g]$中选出$n$个组成字符串$s$。如果能，则输出`YES`，并在第二行按在$s$中的顺序输出对应的$r$的编号，否则输出`NO`。  
### 思路  
算法：字符串哈希（双哈希）  
首先，因为本题的字符串$s$是一个环，所以读入以后需要复制一遍（其实只复制前$k$个字符就可以。）  
之后，把$r[1..g]$的双哈希值放入map中，值为字符串的编号。  
接着，因为环形字符串$s$划分为长度为$k$的划分方法只可能有$k$种，也就是只能把$s[1],s[2],\cdots,s[k]$作为划分后第一个字符串的第一个字符，$s[k+1]$就与第一种划分方式重复了（这就是为什么我前面说只需要复制前$k$个字符就可以）。所以枚举$s[1],s[2],\cdots,s[k]$作为划分后第一个字符串第一个字符的情况，对于每个$s$的长度为$k$的子串在map中匹配并记录编号，如果曾经匹配过或者不在map中直接进入下一次枚举即可。  
复杂度$O(n\times k)$  
### Tips  
1. 本题一定要用双哈希，大概尝试了好多模数，最多也就撑到测试点22，换了双哈希以后直接就A掉了。  
2. 双哈希判断相同字符串的条件的时候，必须是两个哈希值之前同时出现过才是相同字符串，因为这个被卡了好几次提交...  
3. 双哈希用map记录编号的时候可以将map定义为`map<pair<long long,long long>,int> M`，这样就可以用`M[make_pair(foo_1,foo_2)]=bar`来记录数据了。  

### code  
``` cpp
#include<cstdio>
#include<map>
#include<queue>
using namespace std;
const int maxn = 2e6+7;
long long mod = 998244353,mod2 = 1e9+7,base = 131;
map<pair<long long,long long>,int> M;//Tips3
map<long long,int>N,N2;
//其实N也可以定义成和M一样的形式，甚至可以把get_hash都写成pair的返回值，但是懒得改了咕咕咕 
int n,m,k,t,ans[maxn];
char s[maxn];
long long h[maxn],h2[maxn],p[maxn],p2[maxn],g[maxn],g2[maxn];
inline long long get_hash(int l,int r)
{
	return (h[r]-h[l-1]*p[r-l+1]%mod+mod)%mod;
}
inline long long get_hash2(int l,int r)
{
	return (h2[r]-h2[l-1]*p2[r-l+1]%mod2+mod2)%mod2;
}
int main()
{
	scanf("%d%d%s%d",&n,&k,s+1,&t);m=n*k;p[0]=1;p2[0]=1;
	for(register int i=1;i<=m;i++)s[i+m]=s[i];m<<=1;
	for(register int i=1;i<=m;i++)
		h[i]=(h[i-1]*base+s[i])%mod,h2[i]=(h2[i-1]*base+s[i])%mod2,//计算哈希 
		p[i]=p[i-1]*base%mod,p2[i]=p2[i-1]*base%mod2;
	for(register int j=1;j<=t;j++)
	{
		scanf("%s",s+1);
		for(register int i=1;i<=k;i++)g[j]=(g[j]*base+s[i])%mod,g2[j]=(g2[j]*base+s[i])%mod2,M[make_pair(g[j],g2[j])]=j;
	}
	for(register int j=1;j<=k;j++)
	{
		N.clear();N2.clear();bool flag=true;
		for(register int i=0;i<n;i++)
		{
			long long now = get_hash(i*k+j,i*k+j+k-1),now2 = get_hash2(i*k+j,i*k+j+k-1);
			if((N.count(now)&&N2.count(now2))||(M.count(make_pair(now,now2))==0)){flag=false;break;}//Tips2这里一定要now和now2同时出现过才需要退出！ 
			N[now]=N2[now2]=1;ans[i+1]=M[make_pair(now,now2)];//记录出现情况并记录答案 
		}
		if(flag)
		{
			printf("YES\n");
			for(register int i=1;i<=n;i++)printf("%d ",ans[i]);
			return 0;
		}
	}
	printf("NO");
	return 0;
} 
```

---

## 作者：2huk (赞：2)

## [CF727E Games on a CD](https://www.luogu.com.cn/problem/CF727E)

> - 已知 $m$ 个长度为 $k$ 互不相同的字符串 $r_1 \dots, r_m$ 和一个长度为 $nk$ 的环形字符串 $s$，问是否能从 $r_1\dots r_m$ 中选出 $n$ 个组成字符串 $s$，并给出方案。
> - $n, k, m \le 10^5$，$nk \le 10^6$。

如果不是环形字符串，做法显然。将 $s$ 连续的划分成 $n$ 个长度为 $k$ 的子串 $t_1, t_2, \dots, t_n$，那么此时就需要判断是否可重集 $\{t_1, t_2, \dots, t_n\} \subseteq \{r_1, r_2, \dots, r_m\}$。字符串 Hash 即可。

因为是环形字符串，所以第一步是倍长然后循环移位。不难发现移位最多移 $k$ 次，因为移 $i$ 和 $i \bmod k$ 次是等价的。

```cpp
// Problem: 
//     Games on a CD
//   
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF727E
// Memory Limit: 500 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

using namespace std;

#define int long long

const int N = 2000009, P = 1145147117, c = 13331;

int n, m, k;
char s[N], t[N];
int hs[N];
int C[N];

int calc(int l, int r) {
	return ((hs[r] - hs[l - 1] * C[r - l + 1] % P) % P + P) % P;
}

vector<int> S1, S2;
int res[N];

bool chk() {
	
	map<int, vector<int> > mp;
	for (int i = 0; i < m; ++ i ) {
		mp[S1[i]].push_back(i);
	}
	
	for (int i = 0; i < n; ++ i ) {
		auto &v = mp[S2[i]];
		
		if (v.empty()) return false;
		res[i] = v.back();
		v.pop_back();
	}
	
	return true;
}

signed main() {
	C[0] = 1;
	for (int i = 1; i < N; ++ i ) {
		C[i] = C[i - 1] * c % P;
	}
	
	cin >> n >> k;
	
	for (int i = 1; i <= n * k; ++ i ) {
		cin >> s[i];
		s[i + n * k] = s[i];
	}
	
	cin >> m;
	for (int i = 1; i <= m; ++ i ) {
		int hs = 0;
		for (int i = 1; i <= k; ++ i ) {
			cin >> t[i];
			hs = (hs * c % P + t[i] - 'a') % P;
		}
		S1.push_back(hs);
	}
	
	for (int i = 1; i <= 2 * n * k; ++ i ) {
		hs[i] = (hs[i - 1] * c % P + s[i] - 'a') % P;
	}
	
	for (int i = 1; i <= k; ++ i ) {
		S2.clear();
		for (int l = i, r = i + k - 1; r <= n * k + i - 1; l += k, r += k) {
			// cout << l << ' ' << r << '\n';
			S2.push_back(calc(l, r));
		}
		
		// puts("");
		
		if (chk()) {
			puts("YES");
			for (int i = 0; i < n; ++ i ) {
				cout << res[i] + 1 << ' ';
			}
			return 0;
		}
	}
	
	puts("NO");
	
	return 0;
}
```

---

## 作者：kimidonatsu (赞：1)

考虑题意：

给定 $g$ 个长度为 $k$ 且互不相同的字符串 $r_i$ 和长度为 $n\times k$ 的环形字符串 $s$。

求能否通过选择出 $n$ 个串，使得他们拼接后得到 $s$。

注意到起始位置只有 $k$ 种，暴力匹配 $n$ 次，哈希即可。

读入 $s$ 的时候需要倍长，当然只复制前 $k$ 个字符也可以。

[Submission](https://codeforces.com/contest/727/submission/264989773)

---

