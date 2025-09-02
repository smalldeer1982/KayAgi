# Remove the Substring (easy version)

## 题目描述

**请注意：本题的简单版和困难版之间的唯一区别是字符串的长度限制。**  

给你一个字符串$s$和一个字符串$t$，两者都只包含小写字母。你可以通过从$s$中删除一些字符（不必连续，可不删除）而不改变剩余字符的顺序（换句话说，删除一些字符后$t$仍然是$s$的子序列），保证最初$t$是$s$的子序列。  
例如，字符串"`test`", "`tst`", "`tt`", "`et`"和""都是字符串"`test`"的子序列，而"`tset`", "`se`", "`contest`"都不是字符串"`test`"的子序列。   
您希望从s中删除一些最大可能长度的连续子序列，在删除后t仍将是s的子序列。  
如果要删除子串$s[l;r]$，则原字符串$s$将变化为$s_1s_2...s_{l-1}s_{r+1}s_{r+2}...s_{|s|-1}s_{|s|}$ （$|s|$为字符串$s$的长度）。  
找到可以删除的连续子字符串的最大可能长度，使得删除后$t$仍将是$s$的子序列。

## 样例 #1

### 输入

```
bbaba
bb
```

### 输出

```
3
```

## 样例 #2

### 输入

```
baaba
ab
```

### 输出

```
2
```

## 样例 #3

### 输入

```
abcde
abcde
```

### 输出

```
0
```

## 样例 #4

### 输入

```
asdfasdf
fasd
```

### 输出

```
3
```

# 题解

## 作者：tXX_F (赞：3)

# Remove the Substring

## 解题思路

假设 $s$ 的长度为 $n$，$t$ 的长度为 $m$。首先，暴力肯定是不行的了，我们就得考虑找规律。

可以发现，删除的字串可分三种情况：

1. 删除 $s$ 最左边子串

   由于要求可删除的子字符串的最大长度，所以要从 $s$ 的首位开始找，直至找到第一个与 $t$ 串相同的子字符串出现位置，记录下每一元素位置，并停止寻找。相关代码如下：

   ```cpp
   len = 1;
   for (int i = 1; i <= len1 && len <= len2; i++) {
	   if (s[i] == t[len]) {
		   a1[len++] = i;
	   }
   }
   ```

2. 删除 $s$ 最右边子串

   与情况 $1$ 差不多，只是从 $s$ 末尾开始从后往前找，直至找到第一个与 $t$ 串相同的子字符串出现位置，记录下每一元素位置，并停止寻找。相关代码：

   ```cpp
   len = len2;
   for (int i = len1; i >= 1 && len >= 1; i--) {
	   if (s[i] == t[len]) {
		   a2[len--] = i;
	   }
   }
   ```

   在完成之后，$ans = \max (a2_1 - 1, len1 - a1_{len2})$。

3. 删除 $s$ 中间某一子串

   在 $s$ 中找到最前与最后的与 $t$ 相同的子字符串后，要删中间的字串就相当于吧最前与最后的子字符串拼接起来。相关代码如下：

   ```cpp
   for (int i = 1; i < len2; i++) {
	   ans = max(ans, a2[i + 1] - a1[i] - 1);
   }
   ```

最后，我们可以发现 D2 的做法同上。

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int Maxn = 2e5 + 5;
char s[Maxn], t[Maxn];
int len1, len2, len, a1[Maxn], a2[Maxn];
int ans;
inline void work() {
	cin >> s + 1 >> t + 1;
	len1 = strlen(s + 1), len2 = strlen(t + 1);
	len = 1;
	for (int i = 1; i <= len1 && len <= len2; i++) {
		if (s[i] == t[len]) {
			a1[len++] = i;
		}
	}
	len = len2;
	for (int i = len1; i >= 1 && len >= 1; i--) {
		if (s[i] == t[len]) {
			a2[len--] = i;
		}
	}
	ans = max(a2[1] - 1, len1 - a1[len2]);
	for (int i = 1; i < len2; i++) {
		ans = max(ans, a2[i + 1] - a1[i] - 1);
	}
	cout << ans << endl;
}
signed main() {
	work();
	return 0;
}
```

---

## 作者：Lian_zy (赞：3)

# 0 题目传送门
[**点我传送**](https://www.luogu.com.cn/problem/CF1203D1)
# 1 分析
这是一道练习字符串的~~水~~好题。

字符串的长度 $ \le 200$，直接 $O(n^3)$ 的暴力枚举即可。

枚举删除区间的端点，并模拟扫描一遍。

``` cpp
for (int l = 0; l < n; l++) {
	for (int r = 0; r < n; r++) {
		//模拟扫描代码
	}
}
```
定义两个指针 $i$ 和 $j$，$i$ 遍历字符串 $s$，$j$ 遍历字符串 $t$，初始值为 $0$（字符串开头）。

$i$ 如果在删除区间内，跳过。

``` cpp
if (i >= l && i <= r) continue;
```

如果 $s_i$ 与 $t_j$ 相等，则比较下一个。

``` cpp
if (s[i] == t[j]) j++;
```

又可以写成 `j += s[i] == t[j];`，不过不太好理解，建议用第一个。

最后，如果 $t$ 依然是删除元素后的 $s$ 的子串，则比较删除元素个数的大小，取最大值。

``` cpp
if (j == m) ans = max(ans, r - l + 1);
```

又可以写成 `ans = j == m ? max(ans, r - l + 1) : ans;`，不过不太好理解，建议用第一个。

# 完整代码
看完了上面的分析，相信你已经可以做出来了。如果还是不会，就照着注释自己理解以下吧。

~~莫抄袭，没了 AC 记录，空悲切。~~

[**AC 记录**](https://www.luogu.com.cn/record/137167280)

``` cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 2e2 + 10;
int n, m, ans;
char s[maxn], t[maxn];
int main() {
	scanf("%s %s", s, t); 
	n = strlen(s);
	m = strlen(t);
	for (int l = 0; l < n; l++) {
		for (int r = 0; r < n; r++) {
			for (int i = 0, j = 0; i < n; i++) {
				if (i >= l && i <= r) continue; //删除区间，跳过
				j += s[i] == t[j]; //如果 s[i] 与 t[j] 相等，则比较下一个。
				ans = j == m ? max(ans, r - l + 1) : ans; //如果 t 依然是删除元素后的 s 的子串，则比较删除个数元素的大小，取最大值。
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：_Fontainebleau_ (赞：2)

### 题意

- 给定 $s,t$ 两个字符串，其中 $t$ 是 $s$ 的子序列。求最长可以在 $s$ 中删去多长的连续子序列，使得 $t$ 仍为 $s$ 的子序列。
- $1\le |t|,|s|\le 200$。

### 做法

Greedy.

**~~我们应当奔着最优时间复杂度去思考！~~** 所以我们考虑 $O(n)$ 的做法。

首先考虑什么时候可以在 $s$ 中删除连续子序列？肯定是最快匹配到 $t_{i}$时，最远的满足条件的$t_{i+1}$ 在 $s$ 中出现的位置中间这一段。或者是最晚出现的满足条件的 $t_1$ 的位置到 $s$ 开头这一段，或最早出现满足条件的 $t_{|t|}$ 的位置到 $s$ 结尾这一段。

说的有点繁琐，给一段代码就会清晰了。$\downarrow$

```cpp
int ans=max(bck[1]-1,slen-frt[tlen]);
	for(int i=1;i<tlen;i++)
		ans=max(ans,bck[i+1]-frt[i]-1);
```
上面的代码中 $bck_i$ 表示满足 $t_{i,i+1,\cdots,|t|}$ 是 $\displaystyle s_{bck_i,bck_{i}+1,\cdots,|s|}$ 的子序列且 $bck_i$ 最大。$frt_i$ 则类似，表示满足 $t_{1,2,\cdots,i}$ 是 $s_{1,2,\cdots,frt_i}$ 的子序列，且 $frt_i$ 最小。

需要注意的是，这里的 $frt_i,bck_i$ 一定是 $t$ 的前缀，后缀和 $s$ 的前缀，后缀的最快匹配，否则答案就有可能偏大。

我们只需要枚举 $t$ 的每一位即可。

至于怎么求 $frt_i,bck_i$？直接暴力一个个扫过去就好了。大家如有不理解，对着代码自己领悟一下。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
char s[200005],t[200005];
int bck[200005],frt[200005];
inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-f;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}
int main()
{
	cin>>s+1>>t+1;
	int slen=strlen(s+1),tlen=strlen(t+1);
	int p=1;
	for(int i=1;i<=slen;i++)
	{
		if(s[i]==t[p])	frt[p++]=i;
		if(p>tlen)	break;
	}
	p=tlen;
	for(int i=slen;i>=1;i--)
	{
		if(s[i]==t[p])	bck[p--]=i;
		if(p<1)	break;
	}
	int ans=max(bck[1]-1,slen-frt[tlen]);
	for(int i=1;i<tlen;i++)
		ans=max(ans,bck[i+1]-frt[i]-1);
	printf("%d\n",ans); 
	return 0;
}

```


---

## 作者：__HHX__ (赞：1)

# 题目大意
删掉 $s$ 的字串，让 $t$ 任然能成为 $s$ 的子序列。
# 思路
对于 easy 版本我们只考虑 $O(n^3)$ 的解法。

假设我要删除 $s_l,s_{l+1},\dots ,s_r$ 的地方。

我们只需枚举 $l$ 与 $r$ 的位置我们就知道要删除那里。

我们仅需把再历遍 $s$ 一次，取最大满足长度。
```cpp
#include<iostream>
using namespace std;

int main(){
	int ans=0;
	string s,t;
	cin>>s>>t;
	for(int l=0;l<s.size();l++)
	{
		for(int r=l;r<s.size();r++)
		{
			for(int i=0,j=0;i<s.size();i++)
			{
				while(i>=l&&i<=r)
				{
					i++;//这是删除部分 
				}
				if(s[i]==t[j])
				{
					j++;
				}
				if(j==t.size())
				{
					ans=max(ans,r-l+1);//满足条件 
				}
			}
		}
	}
	cout<<ans;
	return 0; 
} 
```

---

## 作者：issue_is_fw (赞：1)

$对于easy版本$

直接枚举删掉的区间$[l,r]$判断是否存在t子串

$这个很简单很暴力$

```
#include <bits/stdc++.h>
using namespace std;
const int maxn=209;
char s[maxn],t[maxn];
int ans;
bool isok(int l,int r)
{
	int x=1;
	for(int i=1;i<=strlen(s+1);i++)
	{
		if(i>=l&&i<=r)	continue;
		if(t[x]==s[i])	x++;
		if(x==strlen(t+1)+1)	return true;
	}
	return false;
}
int main()
{
	cin>>(s+1)>>(t+1);
	for(int i=1;i<=strlen(s+1);i++)
	for(int j=i;j<=strlen(s+1);j++)
		if(isok(i,j))	ans=max(ans,j-i+1);
	cout<<ans;
}
```

$hard版本$

$我们知道,区间最大有两种情况$

$一、首字符出现最晚,此时删掉[1,首字符)$

$末字符出现最早,此时删掉(末字符,n] (n是s串长度)$

二、当最快匹配到i位置时,下一个匹配的字母使其最远为j,此时可删掉$(i,j)$

$这些都不难想,包括最快匹配到i字符的位置$

$最快,所以我们一个字符一个字符匹配,相同就往后匹配$

$那如何知道下一个字母最晚能在哪里匹配呢?$

$我们只需要倒着求一遍倒着的t串最快匹配位置即可$

```
#include <bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
char s[maxn],t[maxn];
int pre[maxn],last[maxn],top1,top2,ls,lt,ans;
void isok1()
{
	int x=1;
	for(int i=1;i<=ls;i++)
	{
		if(s[i]==t[x])	pre[x++]=i;
		if(x>lt)	return;
	}
}
void isok2()
{
	int x=lt;
	for(int i=ls;i>=1;i--)
	{
		if(s[i]==t[x])	last[x--]=i;
		if(x<1)	return;
	}
}
int main()
{
	cin>>(s+1)>>(t+1);
	ls=strlen(s+1),lt=strlen(t+1);
	isok1();isok2();
	ans=max(last[1]-1,ls-pre[lt]);
	for(int i=1;i<lt;i++)
		ans=max(ans,last[i+1]-pre[i]-1);
	cout<<ans;
}
```

---

## 作者：Peter20122012 (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF1203D1)

## 思路
虽然这题 $O(n^{3})$ 能过，但是我还是写了一个 $O(n)$ 的贪心。

令 $n = |s|, m = |t|$。

首先注意要删除的是“连续子序列”，所以只能选择在字符串的左、中、右进行删除：
1. 如果保留左边删右边：我们可以从左往右**按字符串 $t$ 的顺序**寻找 $t$ 中每个字符，并记录下其位置 $idxl_{i}$（后面第三种情况会用），此时 $[1, idxl_{m}]$ 的字符保留，$[idxl_{m} + 1, n]$ 的字符被删除，共删除了 $n - idxl_{i}$ 个字符。
2. 如果保留左边删右边：我们可以从左往右**按字符串 $t$ 的顺序**寻找 $t$ 中每个字符，并记
录下其位置 $idxr_{i} $（后面第三种情况会用），此时 $[idxr_{0}, n]$ 的字符保留，$[1, idxr_{0} - 1]$ 的字符被删除，共删除了 $idxr_{0} - 1$ 个字符。
3. 如果留两边删中间：枚举从哪里分开，此时删除了 $[idxl_{i}, idxr_{i + 1}]$ 中的元素，共 $idxr_{i + 1} - idxl_{i} - 1$ 个字符被删除。

## AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;

#define MAX(x, y) (((x) >= (y)) ?(x) :(y))
#define MIN(x, y) (((x) <= (y)) ?(x) :(y))
#define FOR(st, ed, i) for (int i = st; i <= ed; ++i)
#define RFOR(st, ed, i) for (int i = ed; i >= st; --i)
#define fir first
#define sec second

//#define debug

typedef long long ll;
typedef double db;
typedef pair<ll, ll> pll;

const int maxn = 2e2 + 10;
const int maxm = 2e2 + 10;

string s, t;

int n, m, ans;
int idxl[maxn], idxr[maxn];

int main () {
	getline(cin, s);
	getline(cin, t);
	
	n = s.size();
	m = t.size();
	s = ' ' + s;
	t = ' ' + t;
    //保留左边删右边：
	for (int i = 1, j = 1; i <= n && j <= m; ++i) {
		if (s[i] == t[j]) {
			idxl[j] = i;
			++j;
		}
	}
    //保留左边删右边：
	for (int i = n, j = m; i >= 1 && j >= 1; --i) {
		if (s[i] == t[j]) {
			idxr[j] = i;
			--j;
		}
	}
	ans = MAX(n - idxl[m], idxr[1] - 1);
    //留两边删中间：
	FOR (1, m - 1, i) {
		ans = MAX(ans, idxr[i + 1] - idxl[i] - 1);
	}
	
	printf("%i\n", ans);
	return 0;
}
```

---

## 作者：Cure_Wing (赞：0)

[CF1203D1 Remove the Substring (easy version)](https://www.luogu.com.cn/problem/CF1203D1)

### 思路

我们可以对题意换个说法：在原字符串 $s$ 中找一个子序列，使其恰好为 $t$，求 $t$ 中相邻字符在 $s$ 中距离的最大值。

然后就很容易发现答案只会出现在相邻字符之间，贪心地想，让左边的字符尽可能靠左，让右边的字符尽可能靠右，那么这样相邻的字符的距离一定是最大的。

做法很明显了，先从前往后做一遍找出每个字符的最左可能位置，再从后往前做一遍找出每个字符的最右可能位置，然后按照上面的说法作差比较就可以了。

时间复杂度 $O(|t|\log|s|+|s|)$。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
using std::cin;using std::cout;
constexpr int N=200005;
std::string s,t;
int l[N],r[N],l1,l2,ans;
std::vector<int>a[30];
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
    cin>>s>>t;l1=s.size();l2=t.size();s=" "+s;t=" "+t;
    for(int i=1;i<=l1;++i) a[s[i]-'a'].push_back(i);r[l2+1]=l1+1;//把每个字符扔进一个数组来查找位置
    for(int i=1;i<=l2;++i) l[i]=*std::upper_bound(a[t[i]-'a'].begin(),a[t[i]-'a'].end(),l[i-1]);//找出每个字符的最左可能位置
    for(int i=l2;i>=1;--i) r[i]=*(--std::lower_bound(a[t[i]-'a'].begin(),a[t[i]-'a'].end(),r[i+1]));//找出每个字符的最右可能位置
    ans=std::max(r[1]-1,l1-l[l2]);//不要忘记前缀和后缀也可以删
    for(int i=1;i<l2;++i) ans=std::max(ans,r[i+1]-l[i]-1);
    cout<<ans;
    return 0;
}
```

---

## 作者：eb0ycn (赞：0)

# [CF1203D1](https://www.luogu.com.cn/problem/CF1203D1) 题解

## 思路

模拟！

题目问的是最多能删多长的子串，那我们就二分删的子串长度，枚举删除的子串的起始下标，检验删完以后 $t$ 是不是 $s$ 的子序列就可以了。

时间复杂度 $O(n^2 \log n)$，稳过好吧！


## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,l,r,mid;
char s[200000],t[200000];
bool check(int x)
{
	int k,cnt;//s
	for(int i=0;i<=n-x;++i)
	{
		k=cnt=0;
		for(int j=0;j<m;++j)//t
		{
			while(s[k]!=t[j]&&k<n)
			{
				if(k>=i&&k<i+x)k=i+x;//这里要避开[i,i+x]的区间。
				else ++k;
			}
			if(k>=i&&k<i+x)k=i+x;
			if(s[k]==t[j])++cnt;
			++k;
			if(cnt==m)return 1;
			if(k>=n)break;
		}
	}
	return 0;
}
int main()
{
	scanf("%s%s",s,t);
	n=strlen(s),m=strlen(t);
	l=0,r=n-m;
	while(l<=r)
	{
		mid=l+r>>1;
		if(check(mid))l=mid+1;
		else r=mid-1;
	}
	printf("%d",l-1);
	return 0;
}
```


---

## 作者：Neilchenyinuo (赞：0)

## 题目大意

1. 删除 $s$ 的一个连续字串，使 $t$ 仍然为 $s$ 的子串，求这个连续子串的最长长度。

## Solution 

1. 由于数据范围很小，我们可以三重循环解决问题。

2. 枚举左端点和右端点寻找可删的区间。

3. 再将 $s$ 扫一遍，取最大长度即可。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int ans;
string s,t; 
int main()
{
	cin>>s>>t;
	for(int l=0;l<s.size();l++)
	{
		for(int r=l;r<s.size();r++)
		{
			for(int i=0,j=0;i<s.size();i++)
			{
				while(i>=l&&i<=r)
					i++;//删除部分 
				if(s[i]==t[j])
					j++;//如果字符相同，继续核对。
				if(j==t.size())
					ans=max(ans,r-l+1);//如果 t 是删除后 s 的子串，记录满足条件的长度 
			}
		}
	}
	cout<<ans;
	return 0; 
} 
```


---

## 作者：minVan (赞：0)

**题目大意**

给定一个字符串 $s$ 和一个它的子序列 $t$，要求删除 $s$ 的一个子串(连续的一段字符串)，使得 $t$ 仍然是它的子序列，求最多删除多长的子串。

**解题思路**

一道模拟题。

先找到 $s$ 中最靠后的子序列 $t$，得到这个子序列每个字符在 $s$ 中的位置 $p_i$，我们可以删除 $p_0$ 前面的所有字符，将 $p_0$ 这个字符换成最靠前的字符，删除 $p_1$ 和 $p_0$ 中间的字符，再将 $p_1$ 这个字符换成最靠前的字符，删除 $p_2$ 和 $p_1$ 中间的字符，

**AC 代码，请勿抄袭**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
string s, t;
int pos, ans;
int p[N];
vector<int> a[30];
int main() {
	cin >> s >> t;
	int n = s.size(), m = t.size();
	for(int i = 0; i < n; i++) {
		int k = s[i] - 'a';
		a[k].push_back(i);
	}
	for(int i = 0; i <= 25; i++) {
		sort(a[i].begin(), a[i].end());
	}
	pos = m - 1;
	for(int i = n - 1; i >= 0; i--) {
		if(s[i] == t[pos]) {
			p[pos] = i;
			pos--;
			if(pos <= -1) {
				break;
			}
		}
	}
	ans = p[0];
	p[m] = n;
	for(int i = 0; i < m; i++) {
		int k = t[i] - 'a', pos;
		if(i == 0) {
			pos = upper_bound(a[k].begin(), a[k].end(), -1) - a[k].begin();
		} else {
			pos = upper_bound(a[k].begin(), a[k].end(), p[i - 1]) - a[k].begin();
		}
		p[i] = a[k][pos];
		ans = max(ans, p[i + 1] - p[i] - 1);
	}
	cout << ans;
	return 0;
}
```

---

