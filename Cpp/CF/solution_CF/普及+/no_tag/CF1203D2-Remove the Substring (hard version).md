# Remove the Substring (hard version)

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

## 作者：学委 (赞：18)

删掉 s 某个子串后，s 分成两串，必须保证左边串从前往后对应的 t 的最右端 >= 右边串从后往前对应的 t 的最左端 - 1。设 r 是从 i 开始删除的合法最右端，那么随着 i 的递增，r 显然也是递增的，所以枚举 i 并维护 r 可以做到 O(n)。

```cpp
#include <cstdio>
#include <cstring>
 
const int N = 2e5 + 10;
 
char s[N], t[N];
int p, f[N], g[N], n, m, ans = 0;
 
int main() {
  scanf("%s%s", s + 1, t + 1);
  n = strlen(s + 1); m = strlen(t + 1);
  p = 1;
  for (int i = 1; i <= n; ++i) {
    f[i] = f[i - 1];
    if (s[i] == t[p])
      ++f[i], ++p;
  }
  p = m;
  g[n + 1] = m + 1;
  for (int i = n; i >= 1; --i) {
    g[i] = g[i + 1];
    if (s[i] == t[p])
      --g[i], --p;
  }
  p = 1;
  for (int i = 0; i <= n; ++i) {
    if (p < i + 1)
      p = i + 1;
    while (p <= n and g[p] <= f[i] + 1)
      ++p;
    if (g[p] <= f[i] + 1)
      break;
    if (ans < p - i - 2)
      ans = p - i - 2;
  }
  for (int i = 1; i <= n; ++i)
    if (f[i] == m and ans < n - i)
      ans = n - i;
  printf("%d\n", ans);
  return 0;
}
```

---

## 作者：__HHX__ (赞：3)

# 题目大意
删掉 $s$ 的字串，让 $t$ 任然能成为 $s$ 的子序列。

求出删掉的字串的最大长度。
# 思路
我们可以预处理出 $s$ 最先出现和最后出现的 $t$（原因后面会讲）。

然后我们就开始考虑删的方法。

删除的方法有三种：

1. 从 $1$ 向前删。

2. 从 $|s|$ 向后删。

3. 从中间删。

---

考虑从 $1$ 向前删。

要保证 $t$ 能成为 $s$ 的子序列。

就只能删掉 $t$ 最后出现在 $s$ 的子序列的位置的前面。

看一组自编样例：

```
elyjcodeisnb
code
```
考虑从 $1$ 向前删。

code 在最后出现的位置分别是 $5,6,7,8$。

那我们就可以删掉 $1$ 到 $4$ 的子串。

---

考虑从 $|s|$ 向前删。

要保证 $t$ 能成为 $s$ 的子序列。

就只能删掉 $t$ 最先出现在 $s$ 的子序列的位置的后面。

还是那组样例：

```
elyjcodeisnb
code
```
考虑从 $|s|$ 向前删。

code 在最先出现的位置分别是 $5,6,7,8$。

那我们就可以删掉 $12$ 到 $9$ 的子串。

---
考虑从中间删。

我们先看自编样例：

```
ccfomadecodeisnb
code
```
考虑从 $1$ 向前删。

code 在最先出现的位置分别是 $1,4,7,8$。

code 在最后出现的位置分别是 $9,10,11,12$。

我们可以尝试不要位置 $9$ 的 c，要位置 $1$ 的 c。

那我们就可以删掉 $2$ 到 $9$ 的子串。

那这个子串的长度就变成了 $r_i-l_{i-1}-1$。

$r_i$ 为最后出现的 $t_i$ 的位置。

$l_i$ 为最先出现的 $t_i$ 的位置。

---
综上所述长度为这三种情况的最大值。
# 代码
```cpp
#include <algorithm>
#include <iostream>

using namespace std;

const int kMaxN = 2e5 + 3;

int l[kMaxN], r[kMaxN];
int ans;
int main() {
  string s, t;
  cin >> s >> t;
  int ls = s.size(), lt = t.size();
  for (int i = 0, j = 0; i < ls && j < lt; i++) {
    if (s[i] == t[j]) {
      l[j++] = i;
    }
  }
  for (int i = ls - 1, j = lt - 1; i >= 0 && j >= 0; i--) {
    if (s[i] == t[j]) {
      r[j--] = i;
    }
  }
  ans = r[0];  // 前面删掉的数量
  for (int i = 1; i < lt; i++) {
    ans = max(ans, r[i] - l[i - 1] - 1);  // 中间删掉的数量
  }
  ans = max(ans, ls - l[lt - 1] - 1);  // 后面删掉的数量
  cout << ans;
  return 0;
}
```
```cpp
#include <algorithm>
#include <iostream>

using namespace std;

const int kMaxN=2e5+3;

int l[kMaxN],r[kMaxN];
int ans;
int main() {
	string s, t;
	cin>>s>>t;
	int ls=s.size(),lt=t.size();
	for(int i=0,j=0;i<ls&&j<lt;i++)
	{
		if(s[i]==t[j])
		{
			l[j++]=i;
		}
	}
	for(int i=ls-1,j=lt-1;i>=0&&j>=0;i--)
	{
		if(s[i]==t[j])
		{
			r[j--]=i;
		}
	}
	ans=r[0];//前面删掉的数量
	for(int i=1;i<lt;i++)
	{
		ans=max(ans,r[i]-l[i-1]-1);//中间删掉的数量 
	}
	ans=max(ans,ls-l[lt-1]-1);//后面删掉的数量 
	cout<<ans;
	return 0;
}
```

---

## 作者：OuOu2021 (赞：3)

### 题意：字符串t是字符串s的子序列（可以不连续），从中删掉一个最长的子串（连续），使t仍然是s的子序列


------------
- 记录一个匹配前缀数组$pre$，使$t[0..pre[i]-1]$是$s[0..i]$的子序列；一个匹配后缀数组$suf$，使$t[suf[i]+1..tlen-1]$是$s[i..slen-1]$的子序列。它们都可以$O(N)$预处理出来
- 剩下的看代码，ccf完全还原，连缩进都一样的代码。

------------

### Talk is cheap,give me the code!
```cpp
#include <iostream>
#include <string>
using namespace std;
const int maxl = 210000;
string s,t;
int pre[maxl],suf[maxl];

int main(){
	cin>>s>>t;
	int slen = s.length(),tlen = t.length();
	for(int i = 0, j = 0;i < slen; ++i) {
		if(j<tlen && s[i] == t[j]) ++j;
		pre[i] = j;//t[0..j-1]是s[0..i]的子序列 
	}
	for(int i = slen-1, j = tlen - 1; i >= 0; --i) {
		if(j>=0 && s[i] == t[j]) --j;
		suf[i] = j;//t[j+1..tlen-1]是s[i..slen-1]的子序列 
	}
	suf[slen]=tlen-1;
	int ans = 0;
	for(int i = 0, j = 0, tmp = 0; i <= slen; ++i){
		while(j <= slen && tmp >= suf[j]+1)++j;
		ans=max(ans, j - i - 1);
		tmp = pre[i];
	} 
	cout << ans << endl;
	return 0;
}




```

------------

### NY OIer出品


---

## 作者：_Fontainebleau_ (赞：2)

### 题意

- 给定 $s,t$ 两个字符串，其中 $t$ 是 $s$ 的子序列。求最长可以在 $s$ 中删去多长的连续子序列，使得 $t$ 仍为 $s$ 的子序列。
- $1\le |t|,|s|\le 2\times 10^5$。

### 做法

Greedy.

$|s|\le 2\times 10^5$，考虑 $O(n)$ 的做法。

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

## 作者：tXX_F (赞：0)

# Remove the Substring

## [传送门](https://www.luogu.com.cn/problem/CF1203D2)

### 正文

假设 $s$ 的长度为 $n$，$t$ 的长度为 $m$。首先，暴力肯定是不行的了，我们就得考虑找规律。

可以发现，删除的字串可分三种情况：

#### 情况 $1$：删除 $s$ 最左边子串

由于要求可删除的子字符串的最大长度，所以要从 $s$ 的首位开始找，直至找到第一个与 $t$ 串相同的子字符串出现位置，记录下每一元素位置，并停止寻找。

```cpp
len = 1;
for (int i = 1; i <= len1 && len <= len2; i++) {
	if (s[i] == t[len]) {
		a1[len++] = i;
	}
}
```

#### 情况 $2$：删除 $s$ 最右边子串

与情况 $1$ 差不多，只是从 $s$ 末尾开始从后往前找，直至找到第一个与 $t$ 串相同的子字符串出现位置，记录下每一元素位置，并停止寻找。

```cpp
len = len2;
for (int i = len1; i >= 1 && len >= 1; i--) {
	if (s[i] == t[len]) {
		a2[len--] = i;
	}
}
```

在完成之后，$ans = \max (a2_1 - 1, len1 - a1_{len2})$。

####  情况 $3$：删除 $s$ 中间某一子串

在 $s$ 中找到最前与最后的与 $t$ 相同的子字符串后，要删中间的字串就相当于吧最前与最后的子字符串拼接起来。

```cpp
for (int i = 1; i < len2; i++) {
	ans = max(ans, a2[i + 1] - a1[i] - 1);
}
```

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
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	work();
	return 0;
}
```

---

## 作者：Cure_Wing (赞：0)

[CF1203D2 Remove the Substring (hard version)](https://www.luogu.com.cn/problem/CF1203D2)

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

## 作者：return_CE (赞：0)

## 题意
给定字符串 $ s $，$ t $，$ t $ 是 $ s $ 的子序列。要求在 $ s $ 中删除一段连续的子序列，使得 $ t $ 仍然为  $ s $ 的子序列。问最长可以删除多少。
#### 子序列不要求连续。
## 思路
开两个数组，分别记录序列 $ t $ 在 $ s $ 中第一次完整出现的位置和最后一次完整出现的位置。

在首位的两个序列都是完整的 $ t $ 序列。所以任取 $ t $ 序列中的第     $ i $ 个字母，分别在首尾两个序列中找到其位置，如 $ a $，$ b $。这两个字母中间的序列对于构成序列 $ t $ 并没有贡献,可以删除。

所以可以大胆地将 $ a $ 与 $ b $ 之间的序列全部删除而 $ t $ 依然包含在 $ s $ 中。 删除的长度为 $ b - a + 1 $。
## 实现
从头到尾扫一遍确定 $ b $ 数组用于存储 $ t $ 序列第一次完整出现时每个字母的在 $ s $ 中的位置，其中 $ b[i] $ 为子序列第一次完整出现时第   $ i $ 个元素的位置。从后向前扫一遍确定 $ a $ 数组储存最后一次完整出现的位置,其中 $ a[i] $ 为子序列最后次完整出现时第   $ i $ 个元素的位置。再计算每个元素可以满足删除的最长序列长度。

在所有 $ a[i+1] - b[i] - 1 $  中输出最大值即可。
## 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
char s[200005],t[200005];
int a[200005],b[200005];
int ans,ls,lt;
int main()
{
	scanf("%s",s+1);
	scanf("%s",t+1);
	ls=strlen(s+1); 
	lt=strlen(t+1);
	int k=1;
	for(int i=1;i<=ls;i++){
		if(s[i]==t[k]){
			b[k]=i;
			k++;
		}	
		if(k>lt)break;
	}
 	k=lt;
	for(int i=ls;i>=1;i--){
		if(s[i]==t[k]){
			a[k]=i;
			k--;
		}	
		if(k<1)	break;
	}
	ans=max(a[1]-1,ls-b[lt]);
	for(int i=1;i<lt;i++)
	ans=max(ans,a[i+1]-b[i]-1);
	cout<<ans;
	return 0;
}

---

## 作者：TEoS (赞：0)

这题初赛让我白给了6分，于是我决定回来解决一下它。

说实话，看原题题面和看CCF代码真是两种完全不同的感受……

本文同步发表在[我的blog](https://www.cnblogs.com/TEoS/p/11773920.html)。

------------
思路分析：

把$s$串删去一部分之后，会把$s$串分成两部分，当然其中一部分有可能为空。$t$串作为$s$串的字串，在删去一部分之后也会被分为两部分。因此我们可以枚举$t$串被分开的位置，然后进行计算。

设$t$串在$t[p]$和$t[p+1]$之间被分开,$s$串在$s[i]$和$s[i+1]$之间被分开。因为要使答案最大，因此我们要让$s$串的左半部分包含且仅包含一个$t$串的左半部分，右半部分也是一样。

因此，按照CCF的讲法，设$s$串和$t$串的长度分别为$slen$和$tlen$，我们可以设$head[i]=p$表示$s[0...i]$包含且仅包含一个子串为$t[0...p]$，设$back[i]=p$表示$s[i...slen-1]$包含且仅包含一个字串为$t[p...tlen-1]$。

如何递推$head$和$back$数组？很显然了，用两个指针分别指向$s$串和$t$串，表示当前位置，相同即匹配成功。

因为指针初值需要设置为0，因此以下代码将$s$串和$t$串都整体后移了一位。

```cpp
p=1;
for(int i=1;i<s.size();i++)
{
	head[i]=head[i-1];
	if(s[i]==t[p])
		head[i]=p++;
}
p=t.size()-1;back[s.size()]=t.size();
for(int i=s.size()-1;i;i--)
{
	back[i]=back[i+1];
	if(s[i]==t[p])
		back[i]=p--;
}
```
递推出$head$和$back$数组后，枚举断点计算答案就行了。用两个指针$i,j$分别指向删除的部分两端。为了让答案最大，应该找到满足$head[i]=p$的最小的$i$，以及满足$back[j]=p+1$的最大的$j$，这两个步骤用两个while循环就可以轻松搞定了。有一个需要注意的点，当被分开的两部分其中一部分包含整个$t$串时，另一部分取空串是最优的，这个需要特判一下。答案即为$j-i-1$。计算答案时也要特判不合法的情况。各个指针的初值也需要注意。

```cpp
#include<iostream>
#include<cstdio>
#include<string>
using namespace std;
const int N=1e6;
int p=1,ans;
int head[N],back[N];
string s,t;
int main()
{
	cin>>s>>t;s='.'+s,t='.'+t;//后移一位
	for(int i=1;i<s.size();i++)
	{
		head[i]=head[i-1];
		if(s[i]==t[p])
			head[i]=p++;
	}
	p=t.size()-1;back[s.size()]=t.size();
	for(int i=s.size()-1;i;i--)
	{
		back[i]=back[i+1];
		if(s[i]==t[p])
			back[i]=p--;
	}
	p=0;
	for(int i=0,j=1;i<s.size(),j<s.size(),p<t.size();p++)
	{
		while(head[i]<p && i<s.size())
			i++;
		while(back[j+1]<=p+1 && j<s.size())
			j++;//找到最优的i和j
		if(p==t.size()-1)
			j=s.size();//贪心地让另一部分为空串
		if(i<s.size() && j<=s.size())//合法才更新答案
			ans=max(ans,j-i-1);
	}
	printf("%d",ans);
	return 0;
}
```
因为指针$i,j$一定是递增的，因此时间复杂度$O(n)$。

------------
既然是初赛原题，那么再来看看CCF的代码：（实测比我的代码快15ms...不过我的代码有的地方常数的确比较大）
```cpp
#include<iostream>
#include<string>
using namespace std;
const int maxl=1e6;//改了一下数组大小，可以过困难版
string s,t;
int pre[maxl],suf[maxl];//分别相当于head和back数组

int main(){
	cin>>s>>t;
	int slen=s.length(),tlen=t.length();
	for(int i=0,j=0;i<slen;++i){
		if(j<tlen && s[i]==t[j]) ++j;
		pre[i]=j;
	}
	for(int i=slen-1,j=tlen-1;i>=0;--i){
		if(j>=0 && s[i]==t[j]) --j;
		suf[i]=j;
	}
	suf[slen]=tlen-1;//递推基本相同，表示略有区别
	int ans=0;
	for(int i=0,j=0,tmp=0;i<=slen;++i){
		while(j<=slen && tmp>=suf[j]+1)	++j;
		ans=max(ans,j-i-1);
		tmp=pre[i];
	}
	cout<<ans<<endl;
	return 0;
}
```
可以发现思路实际上大体相同，但是计算答案时略有差别。

分析一下这个计算答案的过程，枚举$s$的断点。可以发现，对于当前的循环，$tmp=pre[i-1]$，即$t[0...tmp-1]$是$s[0...i-1]$的字串，那么接下来为了使答案最大，应该找到满足$t[tmp...tlen-1]$是$s[j...slen-1]$的$j$。而这份代码中的while循环找到的$j$应该会比我们要找的$j$大1，因此要删除的部分就是$s[i...j-2]$，长度$j-i-1$。

然后分析一下题目：（理解了题意之后感觉想错都难qwq）

1.

Q：程序输出时，suf数组满足：对于任意$0\leq i\leq slen$，$suf[i]\leq suf[i+1]$。

A：T，显然$suf$数组是递增的。

2.

Q：当$t$是$s$的子序列时，输出一定不为0。

A：F，反例样例3。

3.

Q：程序运行到第23行时，“j-i-1”一定不小于0。

A：F，在本题中的确不会出现这种情况，但初赛题目中可没保证$t$是$s$的子串，$t$不是$s$的字串时就会出现这种情况。

4.

Q：当$t$是$s$的子序列时，$pre$数组和$suf$数组满足：对于任意$0\leq i<slen$，$pre[i]>suf[i+1]+1$。

A：F，反例样例1。

5.

Q：若$tlen=10$，输出为0，则$slen$最小为（ ）。

A：输出为0说明$t$不是$s$的子序列或者$s=t$，显然前者可以使答案更小，即$t$越短越好。由于cin不能输入空串，因此最短只能是1。

6.

Q：若$tlen=10$，输出为2，则$slen$最小为（ ）。

A：$s$最多删去两个字符使$t$仍是$s$的字串，显然$t$串最短长度为12。

最后祝大家CSP-J/S 2019rp++。

---

## 作者：eb0ycn (赞：0)

# [CF1203D2](https://www.luogu.com.cn/problem/CF1203D2) 题解

## 导论

>众所周知，不同情况差别对待也是平等。

既然这题有两种难度，那我们就[暴力](https://www.luogu.com.cn/blog/diaoling-cwx/solution-cf1203d1)过[简单版](https://www.luogu.com.cn/problem/CF1203D1)，再用正解过困难版……

## 题意

给你一个字符串 $s$ 和它的其中一个**子序列** $t$，删除 $s$ 的某个**字串**使得 $t$ 仍是 $s$ 的子序列，问可以删除的最大长度。

## 思路

假设 $s$ 的长度为 $n$，$t$ 的长度为 $m$。

首先，暴力肯定是不行的了，我们就得考虑找规律。通过推理可以发现，删除的字串大体可以分为三类：

1. 删除 $s$ 最左边的子串；
1. 删除 $s$ 最右边的子串；
1. 删除 $s$ 中间的某个子串。

### 情况一、情况二：

其中，第一、二种情况很好判断。因为一个字符串可能有多个本质相同的子序列，所以 $t$ 的元素在 $s$ 中的位置不唯一。只要知道 $t$ 第一个字符在 $s$ 中出现的最后一个位置（记作 $hou_1$，对应情况一）和 $t$ 最后一个字符在 $s$ 中出现的第一个位置（记作 $xian_m$，对应情况二）即可。

下图中，最上方黑色矩形表示字符串 $s$，中间的红色矩形对应情况二，表示 $t$ 在 $s$ 中最靠前的位置范围（中间的元素 $t_i$ 可能跟 $s_i$ 不相等，但两边一定是对得上的，即 $t_l=s_l$ 且 $t_r=s_r$，下同），最下面的蓝色矩形对应情况一，表示 $t$ 在 $s$ 中最靠后的位置范围。

![图1 情况一和情况二](https://cdn.luogu.com.cn/upload/image_hosting/nn0m7ost.png)

我们设答案为 $ans$，则此时 $ans \gets \max (hou_{1}-1,n-xian_{m})$。

### 如何干爆情况三？

先上图：

![](https://cdn.luogu.com.cn/upload/image_hosting/t7o7yfwt.png)

对于任意的 $2\le i \le m$，我们都能把 $(xian_{i-1},hou_{i})$ 子串删掉。因为这两个下标之间的元素对子序列没有影响。

然后就做完了。

时间复杂度：$O(n)$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,ans,hou[200001],xian[200001],k=1;
char s[200001],t[200001];
int main()
{
	scanf("%s%s",s+1,t+1);
	n=strlen(s+1),m=strlen(t+1);
	for(int i=1;i<=n;++i)if(s[i]==t[k])xian[k++]=i;//循环完以后k=m+1。
	--k;
	for(int i=n;i;--i)if(s[i]==t[k])hou[k--]=i;
	ans=max(hou[1]-1,n-xian[m]);
	for(int i=2;i<=m;++i)ans=max(ans,hou[i]-xian[i-1]-1);
	printf("%d",ans);
	return 0;
}
```

感觉相比我之前写的 $O(n^2 \log n)$ 暴力，这个代码还更简单呐。

---

## 作者：Zofia (赞：0)

恭喜学委 @学委 押中CSP-S 2019真题。

以下提供CCF的做法，具体解析可以康康学委的讲解。

```cpp
#include<bits/stdc++.h>
using namespace std;

int slen,tlen;
char s[200001],t[200001];
int pre[200001],suf[200001];

int main(){
	scanf("%s%s",s,t);
	slen=strlen(s);
	tlen=strlen(t);
	for(int i=0,j=0;i<slen;i++){
		if(j<tlen&&s[i]==t[j]){j++;}
		pre[i]=j;
	}for(int i=slen-1,j=tlen-1;i>=0;i--){
		if(j>=0&&s[i]==t[j]){j--;}
		suf[i]=j;
	}suf[slen]=tlen-1;
	int ans=0;
	for(int i=0,j=0,tmp=0;i<=slen;i++){
		while(j<=slen&&tmp>=suf[j]+1){j++;}
		ans=max(ans,j-i-1);
		tmp=pre[i];
	}printf("%d",ans);
	return 0;
}
```


---

