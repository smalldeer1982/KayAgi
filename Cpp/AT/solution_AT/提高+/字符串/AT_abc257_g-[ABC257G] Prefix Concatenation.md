# [ABC257G] Prefix Concatenation

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc257/tasks/abc257_g

英小文字のみからなる $ 2 $ つの文字列 $ S,T $ が与えられます。

(相異なっても良い) $ S $ の接頭辞を $ k $ 個連結することで $ T $ と一致させられるような最小の正整数 $ k $ を求めてください。

すなわち、$ S $ の $ 1 $ 文字目から $ i $ 文字目までを取り出した文字列を $ S_i $ としたときに、 $ k $ 個の $ 1 $ 以上 $ |S| $ 以下の整数の組 $ (a_1,a_2,\ldots,\ a_k) $ によって、  
 $ T=S_{a_1}+S_{a_2}+\cdots\ +S_{a_k} $（ここで $ + $ は文字列としての連結を表す）と書くことができるような 最小の正整数 $ k $ を求めてください。

$ T $ と一致させる事が不可能な場合は $ -1 $ を出力してください。

## 说明/提示

### 制約

- $ 1\ \leq\ |S|\ \leq\ 5\times\ 10^5 $
- $ 1\ \leq\ |T|\ \leq\ 5\times\ 10^5 $
- $ S,T $ は英小文字のみからなる文字列

### Sample Explanation 1

$ T= $ `ababaab` は `ab` + `aba` + `ab` と書け、`ab`, `aba` はそれぞれ $ S= $ `aba` の接頭辞となっています。 `ababaab` を $ 2 $ 個以下の `aba` の接頭辞の連結によって表す方法はないため、$ 3 $ を出力します。

### Sample Explanation 2

$ T $ を $ S $ の接頭辞の連結によって表す方法はないため、$ -1 $ を出力します。

## 样例 #1

### 输入

```
aba
ababaab```

### 输出

```
3```

## 样例 #2

### 输入

```
atcoder
ac```

### 输出

```
-1```

# 题解

## 作者：wangbinfeng (赞：6)

[![](https://img.shields.io/badge/题目-AT__abc257__g_[ABC257G]_Prefix_Concatenation-green)
![](https://img.shields.io/badge/难度-提高+/省选−-blue)
![](https://img.shields.io/badge/考点-KMP_优化_DP-red)
![](https://img.shields.io/badge/题型-传统题-yellow)](https://www.luogu.com.cn/problem/AT_abc257_g)
[![](https://img.shields.io/badge/作者-wangbinfeng(387009)-purple)](https://www.luogu.com.cn/user/387009)

---

前置知识：KMP 算法，具体参见 [P3375【模板】KMP](https://www.luogu.com.cn/problem/P3375)。

先考虑动态规划，用 $dp_i$ 表示以 $i$ 结尾的字符串的最小分割次数。

那么只要满足 $s_{j+1}\text{\textasciitilde} s_i$ 是 $t$ 的前缀， $dp_i$ 就可以从 $dp_j$ 转移。

而判断 $s_{j+1}\text{\textasciitilde} s_i$ 是否为 $t$ 的前缀可以采用字符串哈希，时间复杂度为 $\Theta(nm)$。

由于要求最小值可以观察到 $dp$ 数组是单调不降的，那么 $dp$ 数组的更新仅仅与 $s,t$ 字符串的相同前后缀长度有关，这很容易联想到 KMP 算法的失配数组（border/fail/next 数组），因此可以采用 KMP 优化掉这一部分。

代码如下：
```cpp
#include<bits/stdc++.h> 
using namespace std;
const int maxn=5e5+9,inf=0x3f3f3f3f;
string s,t;
int nxt[maxn],dp[maxn];
signed main(){
	ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr);
	cin>>s>>t,s='#'+s,t='#'+t;
	for(int i=2,j=0;s[i];i++){
		while(j&&s[i]!=s[j+1])j=nxt[j];
		if(s[i]==s[j+1])j++;
		nxt[i]=j;
	}
	memset(dp,0x3f,sizeof dp),dp[0]=0;
	for(int i=1,j=0;t[i];i++){
		while(j&&t[i]!=s[j+1])j=nxt[j];
		if(t[i]==s[j+1])j++;
		dp[i]=min(dp[i],dp[i-j]+1);
	}
	cout<<(dp[t.length()-1]>=inf?-1:dp[t.length()-1])<<endl;
	//for(int i=1;s[i];i++)cerr<<nxt[i]<<' ';
	//cerr<<endl;
	//for(int i=1;t[i];i++)cerr<<dp[i]<<' '; 
}
```

---
[![](https://jrenc.azurewebsites.net/api/signature?code=zHZRCCItO-yB8t7d2KyitELFDwADnXIotkeeIQL3juyNAzFucnyrWA%3D%3D&name=thacks%20for%20reading%20%20%20%20%20%20%20%20by%20%40wangbinfeng(387009)&animate=true&speed=0.7&color=purple)](https://www.luogu.com.cn/user/387009)
$$\color{grey}{\tiny{\texttt{发现上面的签名是动图了吗？}}}$$

---

## 作者：Superiority (赞：5)

# 思路

思维难度还是比较高的，我们可以尝试使用 KMP 再加上少许贪心思想来进行求解，不会 KMP 的同学看[这里](https://oi.wiki/string/kmp/)。

首先我们要很深刻理解 KMP，$next_i$ 代表 $1\sim i$ 中最长重复的前缀和后缀，而题目要求我们求字符串 $S$ 中最少需要被分成多少部分，并且每一部分都为 $T$ 的前缀。

我们思考如何匹配，这时候只要一点贪心思想就可以了。我们定义 $P$ 为前一个部分的终点，如果 $i-j+1$ 也就是如果左端点大于前一个部分终点了，也就是出现了一个新的部分，我们用 $ans$ 记录下来，最后就是总共最少划分的部分，并将这时候的 $P$ 赋值为此时的终点 $i$。

接下来就是不成立的情况，如果这个 $S$ 的某个部分不属于 $T$ 的前缀，这时候 $j$ 会等于 $0$，因为 $next$ 会不断向前找前缀，直到 $j = 0$ 或者满足条件的时候才会停止，如果没有就会一直搜到 $0$，只要在中间过程里判断一下 $j$ 是否等于 $0$ 就可以了。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;//by cqbzbbd
#define zjj long long
const int MAXN=1e7+5;
int n,m;
int idx;
string x,y;
int nxt[MAXN];
int ans,p;
void KMP(){
	nxt[1]=0;
	for(int i=2;i<=n;i++){
		while(idx&&x[i]!=x[idx+1]) idx=nxt[idx];
		if(x[idx+1]==x[i]) idx++;
		nxt[i]=idx;
	}
}
int main(){
	cin>>x>>y;
    n=x.length();
 	m=y.length();
	x=" "+x;
	y=" "+y;
	KMP();
	idx=0;
	for(int i=1;i<=m;i++){
		while(idx&&y[i]!=x[idx+1]) idx=nxt[idx];
		if(y[i]==x[idx+1]) idx++;
		if(idx==0){
			cout<<"Fake"<<endl;
			return 0;
		}
		if(i-idx+1>p){
			p=i;
			ans++;
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：AC_love (赞：3)

怎么题解区全是 KMP，来一发不用 KMP 的题解。

DP 状态设计很好想，设 $f(i)$ 表示前 $i$ 位最少能划分成几个步骤。

接下来，由于我们思考 DP 转移时通常会使用填表法，很容易给出这样的转移：

$$f(i) = \min_{j < i} f(j) + 1$$

其中满足 $j + 1 \sim i$ 是一段前缀。

我们发现满足条件的 $j$ 并不好找，从前往后枚举复杂度是 $O(n ^ 2)$ 的，太失败了，这可不行。

考虑为什么 $j$ 不好找。不难发现当 $j$ 从 $0$ 枚举到 $i - 1$ 时，$T[j + 1 : i]$ 这个子串一直是从前面删除字符的。这可能会导致一个原本不是前缀的子串变成了前缀，或者一个是前缀的子串变得不再是前缀。因此我们只能暴力枚举，这样做很劣。

我们能不能反过来，让枚举的字符串在后面添加字符呢？

不妨采用刷表法，考虑一个 $f(i)$ 可以转移到哪些 $f(j)$。

$$f(i) + 1 \rightarrow f(j)$$

此时依旧需要满足 $T[i + 1 : j]$ 这个子串是 $S$ 的前缀。不过此时不难发现：由于我们添加字符是从后面添加的，只会出现前缀变成非前缀的情况，而不会出现非前缀变成前缀的情况。

因此当出现非前缀的时候，就不需要继续向后枚举了，后面一定都是非前缀。

此时我们只要找到第一个非前缀位置即可，可以直接二分这个位置，然后用哈希判断。

接下来我们要给这个区间做一次区间赋值，可以用线段树来解决问题。

总复杂度 $O(n \log n)$，瓶颈在于二分和线段树。

https://atcoder.jp/contests/abc257/submissions/58135207

---

## 作者：A_small_WA (赞：2)

绝大多数人都是用线段树/树状数组/dp 过的这题，但是，这题如果直接贪心也是可以过的，而且超级简单！

首先令 $n$ 表示 $S$ 的长度，$m$ 表示 $T$ 的长度，给 $S,T$ 前各加一个空格，这样字符串下标就从 $1$ 开始。

和其它解法一样，我们先用哈希+二分枚举出 $T_i\sim T_m$ 和 $S$ 的最长公共前缀长度，记作 $len_i$。

然后以每个 $i(1\le i\le m)$ 为左端点，$i+len_i-1$ 为右端点创建区间（$len_i=0$ 的不用创建）。

将每个区间按照左端点升序排序（如果你是按顺序创建的区间，那区间已经有序），用一个指针 $j$，表示当前所在字符串 $T$ 的位置，初始 $j=1$。

开一个装区间（结构体）的堆，内部封装按右端点升序的排序逻辑。每一次找出所有左端点 $\le j$ 的区间扔进堆里，再取出堆中右端点最大的区间，让指针 $j$ 移到区间的右端点 $+1$ 的位置。最后求一共经历了几个区间就是答案。

这个方法相当于把前缀看成区间，求最少用多少个区间才能将 $1\sim m$ 完全覆盖。

时间复杂度 $O(m \log m)$。

---

## 作者：SkyLines (赞：2)

## Solution

在 KMP 中，每次循环 $S$ 中的第 $i$ 个时，会找到与此字符串相等的 $T$ 中的前 $j$ 个，则此字符串的起点为 $i-j+1$，终点为 $i$，如果此字符串的起点 $i-j+1$ 比前一个字符串的终点 $p$ 大，则不能与前一个字符串合并，另外划分一段。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e7 + 5;
string s1, s2;
int n, m, j, nxt[N], ans, p = -1;
int main(){
	cin >> s2 >> s1;
	m = s2.length();
	n = s1.length();
	s1 = " " + s1;
	s2 = " " + s2;
	j = 0;
	nxt[1] = 0;
	for(int i = 2; i <= m; i++){
		while(j && s2[i] != s2[j + 1]) j = nxt[j];
		if(s2[i] == s2[j + 1]) j++;
		nxt[i] = j;
	}
	j = 0;
	p = -1e9;
	for(int i = 1; i <= n; i++){
		while(j && s1[i] != s2[j + 1]) j = nxt[j];
		if(s1[i] == s2[j + 1]) j++;
		if(j == 0){
			printf("-1");
			return 0;
		}
		if(i - j + 1 > p){
			ans++;
			p = i;
		}
	}
	printf("%d", ans);
	return 0;
}
```

---

## 作者：Terrific_Year (赞：2)

## 题意简述

给定两个字符串 $t,s$，将 $s$ 划分为 $n$ 个子串，使得每一个子串都是字符串 $t$ 的前缀（含 $t$）。

求满足条件时最小的 $n$，无满足的情况则输出`-1`。

数据范围： $|t|,|s| \le 5 \times 10^5$。

## 思路分析

注：记字符串规模为 $n$。

考虑到字符串长度如此之大，我们需要一个 $O(n)$ 的算法（也可以是 $O(n\log n)$），因为要求和前缀有着很强的关联性，我们不难想到 KMP 算法，如果没有了解过 KMP 算法，可以先尝试 [P3375 【模板】KMP](/problem/P3375)，关于该算法的详细分析，这里就不过多赘述了。

这是一个 KMP 模板的关键操作：

```cpp
//预处理next数组
for(int i=2,j=0; i<=lt; ++i) {
	while(j&&(t[i]!=t[j+1]))j=nxt[j];
	if(t[i]==t[j+1])++j;
	nxt[i]=j;
}
//进行匹配
for(int i=1,j=0; i<=ls; ++i) {
	while(j&&(j==lt||s[i]!=t[j+1]))j=nxt[j];
	if(s[i]==t[j+1])++j;
}
```

字符串 $s$ 每匹配成功一次，我们就得到了一个可划分出的子串，也就是说：只要每次尝试匹配后，匹配长度 $j$ 都不为 $0$，字符串 $s$ 就是可划分的，这样就解决了什么时候输出 `-1` 的问题。

那么，怎样求最小划分呢？

其实，只需要尽可能利用已匹配的部分，只有当这次匹配的起点超过上次记录的终点位置时，才进行更新答案。因为当前匹配的终点只会往前推进，所以这样操作可以证明是正确的。

具体看代码：

```cpp
//匹配部分进行答案更新,x表示上次匹配的终点位置
for(int i=1,j=0,x=0; i<=ls; ++i) {
	while(j&&(j==lt||s[i]!=t[j+1]))j=nxt[j];
	if(s[i]==t[j+1])++j;
	if(j==0){//当匹配失败时，输出-1
		puts("-1");
		return 0;
	}
	if(i-j+1>x)++ans,x=i;//本次匹配的起点超过上次的终点时，更新答案和位置
}
```

完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e7+5;
int lt,ls,nxt[N],ans;
char t[N],s[N];
int main(){
	ios::sync_with_stdio(0);
	cin>>t+1,cin>>s+1;
	lt=strlen(t+1),ls=strlen(s+1);
	for(int i=2,j=0;i<=lt;++i){
		while(j&&(t[i]!=t[j+1]))j=nxt[j];
		if(t[i]==t[j+1])++j;
		nxt[i]=j;
	}
	for(int i=1,j=0,x=0;i<=ls;++i){
		while(j&&(j==lt||s[i]!=t[j+1]))j=nxt[j];
		if(s[i]==t[j+1])++j;
		if(j==0)puts("-1"),exit(0);
		if(i+1>j+x)++ans,x=i;
	}
	cout<<ans;
	return 0;
}
```

类似的题目：[P8112](/problem/P8112)。

---

## 作者：Tx_Lcy (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc257_g)

## 思路

怎么能没有线段树题解。

设 $f_i$ 表示 $t_{1 \cdots i}$ 划分成的最小前缀数。

然后考虑 $f_i$ 转移到 $f_j\ (j>i)$。

观察到这是一个区间，用标记永久化线段树维护即可，寻找区间可以使用哈希。

然后没了。

## 代码

```cpp
//A tree without skin will surely die.
//A man without face will be alive
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define mid ((l+r)>>1)
#define sqr(x) ((x)*(x))
#define all(x) (x).begin(),(x).end()
#define Tim ((double)clock()/CLOCKS_PER_SEC)
#define lowbit(x) (x&-x)
int const N=5e5+10;
int f[N];
unsigned int base[N],haah[N],hsah[N];
inline int query(int l,int r){
    return haah[r]-haah[l-1]*base[r-l+1];
}
struct Segment_Tree{
    #define ls (x<<1)
    #define rs (x<<1|1)
    int c[N<<2];
    inline void update(int x,int l,int r,int ll,int rr,int v){
        if (ll<=l && r<=rr){
            c[x]=min(c[x],v);
            return;
        }
        if (ll<=mid) update(ls,l,mid,ll,rr,v);
        if (mid<rr) update(rs,mid+1,r,ll,rr,v);
    }
    inline int query(int x,int l,int r,int p){
        if (l==r) return c[x];
        if (p<=mid) return min(c[x],query(ls,l,mid,p));
        else return min(c[x],query(rs,mid+1,r,p));
    }
}T;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    memset(T.c,0x3f,sizeof(T.c));
    string s,t;cin>>t>>s;
    int n=s.length(),m=t.length();
    s=" "+s,t=" "+t;
    base[0]=1;
    for (int i=1;i<=n;++i) base[i]=base[i-1]*233;
    for (int i=1;i<=n;++i) haah[i]=haah[i-1]*233+(s[i]-'a'+1);
    for (int i=1;i<=m;++i) hsah[i]=hsah[i-1]*233+(t[i]-'a'+1);
    memset(f,0x3f,sizeof(f));
    f[0]=0;
    for (int i=0;i<=n;++i){
        if (i) f[i]=T.query(1,1,n,i);
        int l=i+1,ans=-1,r=n;
        while (l<=r)
            if (query(i+1,mid)==hsah[mid-i]) l=(ans=mid)+1;
            else r=mid-1;
        if (ans==-1) continue;
        T.update(1,1,n,i+1,ans,f[i]+1);
    }
    if (f[n]>(1e9)) f[n]=-1;
    cout<<f[n]<<'\n';
    return 0;
}
```

---

## 作者：Vsinger_洛天依 (赞：1)

这题一眼 KMP，然后直接大力贪心，容易发现直接跑 KMP，在跑第 $i$ 个的时候如果找到了 $j$ 个相同的字符那么起点就是 $i-j+1$，此时如果左端点比上一段的终点要大了就只能再开一段了，我们此时给 $ans+1$ 即可

如果是不成立的情况呢？那就好办了，只要判断一下中间会不会找不到 $j$ 就行了。

---

## 作者：yaoyuchen2021 (赞：1)

# 题目大意
给定字符串 $S,T$，求最小的 $k$ 使 $T$ 被分为 $k$ 个 $S$ 的前缀，若无合理的分法，输出 `-1`。

# 解题思路
$S$ 和 $T$ 的长度均在 $5 \times 10^5$，所以复杂度只能是 $O(n)$ 的。线性的字符串匹配，自然而然想到了 **KMP 算法**。现在 $S$ 上遍历一遍，得到失配指针，然后在 $T$ 上遍历，得到最小的 $k$。如果不合理，在匹配的过程中指针会指向根节点，特判输出 `-1` 即可。

# AC Code

```cpp
#include <bits/stdc++.h>
//#define int long long
using namespace std;
int lt,ls,f[10000005],ans,sum;//f[]为失配指针
string t,s;
signed main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin>>t>>s;lt=t.size();ls=s.size();t=' '+t;s=' '+s;
    for(int i=2,j=0;i<=lt;i++)
    {
        while(j&&t[i]!=t[j+1])j=f[j];
        if(t[i]==t[j+1])j++;
        f[i]=j;
    }
    for(int i=1,j=0;i<=ls;i++)
    {
        while(j&&(j==lt||s[i]!=t[j+1]))j=f[j];
        if(s[i]==t[j+1])j++;
        if(!j)
        {
            cout<<"-1";//无合理分法
            return 0;
        }
        if(i+1>j+sum)sum=i,ans++;//分段
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：ScottSuperb (赞：1)

## 解法分析
KMP+贪心。  
我们在将 $S$ 对 $T$ 进行匹配时得到的结果存入一个数组 $f$，即 $f_i=\max\{j\}$，其中 $j\le i$ 并且 $T_{i-j+1\sim i}=S_{1\sim j}$。
可以发现，此题仿佛是为这个数组量身打造的。显然如果 $T$ 可以分成若干段 $S$ 的前缀，那么 $f_i$ 必定为正。因此在求 $f$ 数组过程中若发现有 $0$ 则可断定 $k$ 不存在，反之一定可以求出 $k$。  
为了求 $k$，很容易就能想出一个贪心算法：从 $T$ 末尾开始，按照该位置 $f$ 值分割，最后分出的段数即为答案。  
用反证法证明。如下图为此策略分割后可能出现的情况：![](https://cdn.luogu.com.cn/upload/image_hosting/bu20r0fu.png)  
那么假设有一种更优方案是这样的：![](https://cdn.luogu.com.cn/upload/image_hosting/pi5l4nen.png)  
于是我们发现 $T_{j1\sim j5}$ 是 $S$ 的前缀，则 $f_{j3}$ 应当至少为 $j3-j1+1>j3-j2+1$，这与 $f_{j3}$ 最大相矛盾，因此不存在更优方案。证得此策略可以保证答案最优。
## 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

int nxt[500005], f[500005];

int main() {
  int n, m;
  string s, t;
  cin >> s >> t;
  n = s.size(), m = t.size();
  for (int i = 1, j = 0; i < n; ++i) {
    while (j > 0 && s[i] != s[j]) j = nxt[j - 1];
    if (s[i] == s[j]) ++j;
    nxt[i] = j;
  }
  for (int i = 0, j = 0; i < m; ++i) {
    while (j > 0 && (j == n || t[i] != s[j])) j = nxt[j - 1];
    if (t[i] == s[j]) ++j;
    f[i] = j;
    if (!f[i]) puts("-1"), exit(0);
  }
  int k = 0;
  for (int i = m - 1; i >= 0; i -= f[i]) ++k;
  printf("%d\n", k);
  return 0;
}
```

---

## 作者：Wei_Han (赞：0)

给一个无脑做法。

设计 $f_i$ 表示前 $i$ 个字符的答案，那么显然对于一个位置 $j$，令 $j>i$，当且仅当 $i+1$ 到 $j$ 的这段字符与 $S$ 串中前 $j-i$ 个位置完全匹配时才有转移 $f_j = f_i + 1$。

这样的话，对于每一个 $i$，可以转移的合法位置 $j$ 每次向右扩展显然是单调的，我们可以用字符串哈希来比较两个子串，然后二分就好了，要更新 $[i+1,j]$ 的所有 $f$ 值，扔到线段树上就好了，这里写的是标记永久化。

```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f3f3f3f3f
#define inf 0x3f3f3f3f
#define pr putchar('\n')
#define fi first
#define se second
#define pp putchar(' ')
#define pii pair<ll,ll>
#define pdi pair<ll,ll>
#define mem(aa,bb) memset(aa,bb,sizeof(aa))
#define fo(a,i,b) for(register ll i = a ; i <= b ; ++ i )
#define Fo(a,i,b) for(register ll i = a ; i >= b ; -- i )
#define pb push_back
//#pragma GCC optimize(2)
using namespace std;
//typedef int ll;
//#define pis pair<ll,char >
typedef long long ll;
//typedef __int128 ll;
typedef double db;
inline void read(ll &opp){ll x=0,t=1;char ch;ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-'){t=-1;}ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}opp=x*t;return; }
inline void wr(ll x){if(x<0){putchar('-');x=-x;}if(x>9){wr(x/10);}putchar(x%10+'0');}
const ll N=5e5+10,M=2e4+5;
const ll base=131,mod=998244353;
ll pre[N][2],n,m,pw[N],f[N];
string s,t;
inline ll gethash(ll l,ll r,ll op){return (pre[r][op]-pre[l-1][op]*pw[r-l+1]%mod+mod)%mod;}
inline ll check(ll l,ll r){if(r-l+1>n) return 0;return gethash(1,r-l+1,0)==gethash(l,r,1);}
struct SGT{ll l,r,sum;}tree[N<<2];
#define rt tree[root]
#define ls tree[root<<1]
#define rs tree[root<<1|1]
inline void pushup(ll root){}
inline void build(ll root,ll l,ll r){rt.sum=INF;rt.l=l,rt.r=r;if(l==r) return rt.sum=INF,void();ll mid=l+r>>1;build(root<<1,l,mid),build(root<<1|1,mid+1,r);pushup(root);}
inline void upd(ll root,ll x,ll y,ll k){ll l=rt.l,r=rt.r;if(x<=l&&y>=r) return rt.sum=min(rt.sum,k),void();ll mid=l+r>>1;if(x<=mid) upd(root<<1,x,y,k);if(y>mid) upd(root<<1|1,x,y,k);pushup(root);}
inline ll ask(ll root,ll x){ll l=rt.l,r=rt.r;if(l==r) return rt.sum;ll mid=l+r>>1;if(x<=mid) return min(rt.sum,ask(root<<1,x));else return min(rt.sum,ask(root<<1|1,x));}
signed main(){
	cin>>s>>t;n=s.size(),m=t.size();
	s=" "+s,t=" "+t;vector<ll> P;
	pw[0]=1;fo(1,i,max(n,m)) pw[i]=pw[i-1]*base%mod;
	fo(1,i,n) pre[i][0]=(pre[i-1][0]*base%mod+s[i])%mod;
	fo(1,i,m) pre[i][1]=(pre[i-1][1]*base%mod+t[i])%mod;
	fo(1,i,m) if(t[i]==s[1]) P.pb(i);P.pb(m+1);
	if(P[0]!=1) return wr(-1),pr,0;
	ll now=0;
	mem(f,0x3f);f[0]=0;build(1,0,m);
	fo(0,i,m)
	{
		f[i]=min(f[i],ask(1,i));
		ll l=i+1,r=m;
		while(l<r)
		{
			ll mid=l+r+1>>1;
			if(check(i+1,mid)) l=mid;
			else r=mid-1;
		}
		if(!check(i+1,i+1)) continue;
		upd(1,i+1,l,f[i]+1);
	}
	wr(f[m]==INF?-1:f[m]),pr;
	return 0;
}
``````

---

## 作者：MrSWdAxiv (赞：0)

## 思路

先看数据范围，我们发现两个字符串的长度最大会达到 $5 \times 10^5$。 ~~这立刻打消了我用暴力的想法。~~

于是，我选择了用 KMP 模式匹配，这一个能够在线性时间内判定字符串 $A$ 是否是字符串 $B$ 的字串，并求出字符串 $A$ 在字符串 $B$ 中各次出现的位置。

如果不清楚 KMP 算法是如何实现的，可以看看[这个](https://oi-wiki.org//string/kmp/)或[这个](https://www.cnblogs.com/MithrilSwordXIV/p/17976737)。

我们知道一个字符串 $A$ 每次往后成功匹配一次，匹配长度就会改变成一个不为 $0$ 的数，而如果没有匹配成功，则会重新从头开始匹配，匹配长度为 $0$。

由此当匹配长度 $j$ 为 $0$ 时，无解输出 `-1`。

我们也知道每次匹配成功都是 $A\left[i - j + 1 \sim i\right] = A\left[1 \sim j\right]$，所以当每次 $i - j + 1$ 这一个起始点超过了上一次的终止点 $i$ 时，就可以让划分的段数变小，更新答案。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define MAX 500005
using namespace std;
int nxt[MAX],lens,lent,ans,tmp;
string s,t;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>s>>t;
    lens=s.length();
    lent=t.length();
    s=" "+s;//注意下标
    t=" "+t;
    for(int i=2,j=0;i<=lens;i++){
        while(j&&s[i]!=s[j+1])j=nxt[j];
        if(s[i]==s[j+1])j++;
        nxt[i]=j;
    }
    for(int i=1,j=0;i<=lent;i++){
        while(j&&(j==lens||t[i]!=s[j+1]))j=nxt[j];
        if(t[i]==s[j+1])j++;
        if(j==0){
            cout<<-1<<'\n';
            exit(0);
        }
        if(i-j+1>tmp){//更新答案
            ans++;
            tmp=i;
        }
    }
    cout<<ans<<'\n';
    return 0;
}
```


---

## 作者：Tsawke (赞：0)

# [[ABC257G] Prefix Concatenation](https://www.luogu.com.cn/problem/AT_abc257_g) Solution

[TOC]

## [更好的阅读体验戳此进入](http://blog.tsawke.com?t=ABC257G)

## 题面

给定仅存在小写英文字母的字符串 $ S, T $。你需要将 $ T $ 分割成 $ k $ 个 $ S $ 的前缀（或着说用 $ S $ 的若干个前缀组成 $ T $），最小化 $ k $，输出最小值。若 $ k $ 不存在输出 `-1`。

## Solution

首先 $ O(n^2) $ 的 DP 显然，我们记 $ S(i, j), T(i, j) $ 为对应字符串 $ [i, j] $ 的子串，令 $ dp(i) $ 表示考虑 $ T(1, i) $ 的最小 $ k $。易得转移：
$$
dp(i) = \min_{j \lt i \land S(1, i - j) = T(j + 1, i)}dp(j) + 1
$$
不难发现这个 $ \texttt{1D1D} $ 的 DP 是 $ O(n^2) $ 的无法通过，考虑优化。

首先有一个思路，已知 $ dp(i) $ 单调不降，证明显然，考虑若 $ dp(i) \gt dp(i + 1) $，那么在 $ dp(i + 1) $ 的方案中将最后一部分去掉第 $ i + 1 $ 个一定可以变为 $ dp(i) $ 且 $ k $ 不劣，得证。

然后根据这个思路我们每次转移只需要找到最小的合法 $ j $ 转移即可，可以通过 KMP 中的 `next` 数组维护。

具体地，不难发现我们这个东西求的可以转化为求 border，具体地，我们将 $ S $ 后追加一个占位符，然后再连接上 $ T $，记 `P = S + '#' + T`，这样我们对 $ P $ 跑一遍 KMP 的建立 next 数组过程，不难发现对于转移 $ i $ 时需要的 $ j $，即为 $ i - nxt(len_S + 1 + i) $，这里的 $ +1 $ 即为我们添加的占位符 `#`。

最终 DP 优化为 $ \texttt{1D0D} $，复杂度 $ O(n) $，可以通过。

同时还有一种方法，发现修改状态为后缀可以支持逆序转移，于是转移变为：
$$
dp(i) = \min_{j \gt i \land S(1, j - i) = T(i, j - 1)}dp(j) + 1
$$
此时发现每次可以转移的 $ j $ 是连续的，对应 $ S $ 和 $ T(i, len_T) $ 的 LCP，于是可以通过哈希 + 二分处理每次转移的 LCP 长度，然后线段树优化 DP 即可，最终复杂度 $ O(n \log n) $，劣于正向转移但也可以通过，且思路更直观，仅代码实现略长。

## Code

```cpp
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

#define PI M_PI
#define E M_E
#define npt nullptr
#define SON i->to
#define OPNEW void* operator new(size_t)
#define ROPNEW(arr) void* Edge::operator new(size_t){static Edge* P = arr; return P++;}

using namespace std;

mt19937 rnd(random_device{}());
int rndd(int l, int r){return rnd() % (r - l + 1) + l;}
bool rnddd(int x){return rndd(1, 100) <= x;}

typedef unsigned int uint;
typedef unsigned long long unll;
typedef long long ll;
typedef long double ld;

template < typename T = int >
inline T read(void);

string S, T;
char s[1100000];
int dp[1100000];
int nxt[1100000];

int main(){
    memset(dp, 0x3f, sizeof dp);
    cin >> S >> T;
    sprintf(s + 1, "%s#%s", S.c_str(), T.c_str());
    int lenS = S.length(), lenT = T.length();
    dp[lenS + 1] = 0;
    int cur(0);
    for(int i = 2; i <= lenS + lenT + 1; ++i){
        while(cur && s[cur + 1] != s[i])cur = nxt[cur];
        if(s[cur + 1] == s[i])++cur;
        if(i > lenS + 1)dp[i] = dp[i - cur] + 1;
        nxt[i] = cur;
    }printf("%d\n", dp[lenS + lenT + 1] < 0x3f3f3f3f ? dp[lenS + lenT + 1] : -1);
    fprintf(stderr, "Time: %.6lf\n", (double)clock() / CLOCKS_PER_SEC);
    return 0;
}

template < typename T >
inline T read(void){
    T ret(0);
    int flag(1);
    char c = getchar();
    while(c != '-' && !isdigit(c))c = getchar();
    if(c == '-')flag = -1, c = getchar();
    while(isdigit(c)){
        ret *= 10;
        ret += int(c - '0');
        c = getchar();
    }
    ret *= flag;
    return ret;
}
```

## UPD

update-2022_12_09 初稿

---

## 作者：_Kenma_ (赞：0)

# AT_abc257_g 解题报告

## 前言

VP 时因为降智错误特判了长度大小关系，贡献三发罚时。

不认为是贪心。

## 思路分析

一眼字符串 DP 题。

设 $f_i$ 表示 $T[1,i]$ 的最小代价。则有转移：

$$f_i=\min_{j}^{j<i} f_j+1$$

其中 $T[j+1,i]$ 是 $S$ 的前缀。

直接做是 $O(n^3)$ 的，又没有很好的哈希思路，所以考虑 KMP 优化。

注意到，在 KMP 做字符串匹配的过程中，每次记录的当前匹配长度 $j$，正好可以求出当前转移区间为 $[i-j,i-1]$。

直接说可能有点抽象，上图：

![](https://cdn.luogu.com.cn/upload/image_hosting/tik1vpl9.png)

但是确定了转移区间是 $O(n^2)$ 的，依然过不了。

****重要性质：$f$ 数组单调不降。****

考虑用反证法证明。

如果存在 $i<j,f_i>f_j$，那么，把$T[i+1,j]$ 删去，答案肯定不会变大，所以不存在 $f_i>f_j$ 的情况。

然后转移区间如果是 $[l,r]$，直接从 $f_l$ 转移一定是最优的。

然后就做完了。

具体地，在做 KMP 时，同时转移 $f_i$。设当前匹配长度为 $j$。则直接令 $f_i=f_{i-j}+1$。

复杂度为 $O(n+m)$。

## 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int inf=1e9;
string s,t;
int n,m,nxt[1000005],f[1000005];
int main(){
	cin>>s;
	cin>>t;
	n=s.size();
	m=t.size();
	s="*"+s;
	t="*"+t;
	for(int i=2;i<=n;i++){
		int j=nxt[i-1];
		while(j && s[j+1]!=s[i]) j=nxt[j];
		if(s[i]==s[j+1]) j++;
		nxt[i]=j;
	} 
	memset(f,0x3f,sizeof(f));
	f[0]=0;
	int j=0;
	for(int i=1;i<=m;i++){
		while(j && s[j+1]!=t[i]) j=nxt[j];
		if(s[j+1]==t[i]) j++;
		f[i]=min(f[i],f[i-j]+1);
	}
	if(f[m]>inf) cout<<-1;
	else cout<<f[m];
	return 0;
}
```

## 后记

没见过类似的题，感觉还挺有意思的。

---

## 作者：MiniLong (赞：0)

线段树 + $z$ 函数 优化 dp。

感觉是自己想复杂了，和其他人思路不太一样，但比较直观。

看到题面，$T$ 的每个后缀和 $S$ 的 lcp，~~这不是 $z$ 函数吗~~。

直接上 dp，令 $f_i$ 表示以 $i$ 结尾为一段，划分 $T[1,i]$ 最少个数（初始值是 $inf$，$f_0 = 0$）。

显然有 $f_i = \min\limits_{j=1}^i f_{j-1}+1$，其中要求 $T[j,i]$ 是 $S$ 的一个前缀。

然后直接硬上，对 $S$ 求出 $z$ 函数，然后拿 $T$ 的每个后缀跟它匹配。

令 $p_i$ 为 $T$ 以 $i$ 开头的后缀与 $S$ 的 lcp。

那么很显然，$T[i, i], T[i, i + 1] \dots T[i, i + p_i - 1]$ 都是 $S$ 的一个前缀。

所以，可以让 $f_i,f_{i+1} \dots f_{i+p_i -1}$ 都对 $f_{i-1} +1$ 取最小值。

这个操作可以用永久标记线段树来实现。

```cpp
#include <bits/stdc++.h>
#define _rep(i, x, y) for(int i = x; i <= y; ++i)
#define _req(i, x, y) for(int i = x; i >= y; --i)
#define _rev(i, u) for(int i = head[u]; i; i = e[i].nxt)
#define pb push_back
#define fi first
#define se second
#define mst(f, i) memset(f, i, sizeof f)
using namespace std;
#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif
namespace fastio{
    char ibuf[50007],*p1 = ibuf, *p2 = ibuf;
    #ifdef ONLINE_JUDGE
    #define get() p1 == p2 && (p2 = (p1 = ibuf) + fread(ibuf, 1, 50007, stdin), p1 == p2) ? EOF : *p1++
    #else
    #define get() getchar()
    #endif
    template<typename T> inline void read(T &t){
        T x = 0, f = 1;
        char c = getchar();
        while(!isdigit(c)){
            if(c == '-') f = -f;
            c = getchar();
        }
        while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
        t = x * f;
    }
    template<typename T, typename ... Args> inline void read(T &t, Args&... args){
        read(t);
        read(args...);
    }
    template<typename T> void write(T t){
        if(t < 0) putchar('-'), t = -t;
        if(t >= 10) write(t / 10);
        putchar(t % 10 + '0');
    }
    template<typename T, typename ... Args> void write(T t, Args... args){
        write(t), putchar(' '), write(args...);
    }
    template<typename T> void writeln(T t){
        write(t);
        puts("");
    }
    template<typename T> void writes(T t){
        write(t), putchar(' ');
    }
    #undef get
};
using namespace fastio;
#define multitest() int T; read(T); _rep(tCase, 1, T)
typedef long long ll;
typedef pair<int, int> PII;
const int N = 1e6 + 5, inf = 0x3f3f3f3f;
int lens, lent, f[N], z[N], p[N];
char s[N], t[N];
void getz(char *s){
	int len = strlen(s + 1);
	z[1] = len;
	for(int i = 2, l = 0, r = 0; i <= len; ++i){
		if(r >= i) z[i] = min(z[i - l + 1], r - i + 1);
		while(i + z[i] <= len && s[z[i] + 1] == s[i + z[i]]) z[i]++;
		if(i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
	}
}
void exkmp(char *s, char *t){
	int lens = strlen(s + 1), lent = strlen(t + 1);
	for(int i = 1, l = 0, r = 0; i <= lens; ++i){
		if(r >= i) p[i] = min(z[i - l + 1], r - i + 1);
		while(i + p[i] <= lens && s[p[i] + i] == t[p[i] + 1]) p[i]++;
		if(i + p[i] - 1 > r) l = i, r = i + p[i] - 1;
	}
}
#define ls x << 1
#define rs x << 1 | 1
int tr[N << 2];
void modify(int x, int l, int r, int L, int R, int v){
	if(l >= L && r <= R) return tr[x] = min(tr[x], v), void();
	int mid = l + r >> 1;
	if(L <= mid) modify(ls, l, mid, L, R, v);
	if(R > mid) modify(rs, mid + 1, r, L, R, v);
}
int query(int x, int l, int r, int p){
	if(l == r) return tr[x];
	int mid = l + r >> 1;
	if(p <= mid) return min(tr[x], query(ls, l, mid, p));
	return min(tr[x], query(rs, mid + 1, r, p));
}

int main(){
	mst(f, inf), mst(tr, inf), f[0] = 0;
	scanf("%s%s", s + 1, t + 1);
	lens = strlen(s + 1), lent = strlen(t + 1);
	getz(s), exkmp(t, s);
	_rep(i, 1, lent){
		if(p[i]) modify(1, 1, lent, i, min(lent, i + p[i] - 1), f[i - 1] + 1);
		f[i] = query(1, 1, lent, i);
	}
	writeln(f[lent] >= inf ? -1 : f[lent]);
    return 0;
}
```

---

