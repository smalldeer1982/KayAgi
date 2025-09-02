# [AGC037E] Reversing and Concatenating

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc037/tasks/agc037_e

高橋君は英小文字からなる長さ $ N $ の文字列 $ S $ を持っています。 高橋君は $ S $ に対して以下の操作を $ K $ 回行うことにしました。

- $ S $ を反転した文字列を $ T $ として、$ S $ と $ T $ をこの順に連結して得られる文字列を $ U $ とする。
- ある $ U $ の連続する長さ $ N $ の部分文字列を $ S' $ として、$ S $ を $ S' $ で置き換える。

最終的な $ S $ として考えられる文字列の内、辞書順で最小のものを求めてください。

## 说明/提示

### 制約

- $ 1\ ≦\ N\ ≦\ 5000 $
- $ 1\ ≦\ K\ ≦\ 10^9 $
- $ |S|=N $
- $ S $ は英小文字からなる

### Sample Explanation 1

$ S= $`bacba`のとき、$ T= $`abcab`, $ U= $`bacbaabcab`であるので $ S'= $`aabca`とするのが最適です。

## 样例 #1

### 输入

```
5 1
bacba```

### 输出

```
aabca```

## 样例 #2

### 输入

```
10 2
bbaabbbaab```

### 输出

```
aaaabbaabb```

# 题解

## 作者：Kinandra (赞：5)

标签: 字符串.

记 $k$ 次操作后字典序最小的字符串为 $s'$ (即答案).

设 $s$ 初始最小的字符为 $c$ , 那么我们显然希望 $s'$ 开头的 $c$ 尽量多.

假设 $c$ 不在末尾, 我们可以用一次操作将任意一段 $c$ 移动到末尾, 之后每次操作都可以使这段 $c$ 倍长. 显然这段 $c$ 越长越好. 

除此之外, 我们希望 $s'$ 除去开头的 $c$ 的部分 $s''$ 字典序尽量小, 考虑这个部分是怎么来的: 设 $t$ 为第一次操作拼接成的字符串(**不是**截取后的), 假设我们截取的右端为 $r(r\geqslant n)$ , 以 $r$ 为结尾的极长 $c$ 段左端点为 $l$ , 不难发现 $s''=t_{l-1}t_{l-2}t_{l-3}...$ , 我们只要把 $t$ 翻转后找到最小的后缀即可, 这个数据范围怎么暴力都可以. 另外, 如果我们在 $t$ 上找最长 $c$ 段,  就不用关心 $c$ 是否在末尾了. 

注意特判一下 $k=1$ 的情况.

时间复杂度 $\mathcal O(n^2)$ .

```cpp
#include <bits/stdc++.h>
using namespace std;
int read();
int n, k;
char s[10004], res[10004], c = 'z';
int l[10004], len, mx, vis;

void cpy(int p) {
    for (int i = 1; i <= n; ++i) res[i] = s[p + i - 1];
}

void check(int p) {
    if (!vis) cpy(p), vis = 1;
    for (int i = 1; i <= n; ++i) {
        if (res[i] < s[p + i - 1]) return;
        if (res[i] > s[p + i - 1]) return cpy(p);
    }
}

int main() {
    scanf("%d%d%s", &n, &k, s + 1);
    for (int i = 1; i <= n; ++i) c = min(c, s[(n << 1) + 1 - i] = s[i]);
    if (k >= 15) {
        for (int i = 1; i <= n; ++i) putchar(c);
        return 0;
    }
    if (k == 1) {
        for (int i = 1; i <= n + 1; ++i) check(i);
        for (int i = 1; i <= n; ++i) putchar(res[i]);
        return 0;
    }
    for (int i = 1; i <= n + n; ++i)
        (s[i] == c) ? mx = max(mx, l[i] = l[i - 1] + 1) : 0;

    if ((len = mx << k - 1) >= n) {
        for (int i = 1; i <= n; ++i) putchar(c);
        return 0;
    }
    for (int i = 1; i <= n + mx; ++i)
        if (l[i] == mx) check(i - l[i] + 1);
    for (int i = 1; i <= len; ++i) putchar(c);
    for (int i = len + 1; i <= n; ++i) putchar(res[i - len + mx]);
    return 0;
}
```



---

## 作者：M00R (赞：3)

提供一种 $\text{O}(n)$ 的做法。

设字符串中最小的字符为 `a`。

求字典序最小的题可以从贪心的角度想：在进行一次操作后，我们可以将串中的 `a` 移到串尾，串尾的 `a` 复制加倍。

例如：

`cbabc`->`cbabccbabc`->`bccba`，将 `a` 转移到字符串尾；

`ccbaa`->`ccbaaaabcc`->`baaaa`，将字符串尾部的 `a` 个数翻倍。

若这是最后一次操作，只需要截取的字符串把最长的 `a` 连续段放在串首即可。

这里我们可以发现，当 $k$ 大于 $13$ 时，最终得到的串中一定全部是 `a`。

处理完 `a` 的问题后，剩下的字母自然是越小越好。

设 $A$ 是一段由连续的 `a` 组成的字符串，$B$ 是不以 `a` 结尾的字符串，$B_R$ 是字符串 $B$ 的翻转。

形如 $BA$ 的串操作后截取的子串要么是 $BAA$ 的一段后缀用于继续操作，要么是 $AAB_R$ 的一段前缀用于当作答案。所以我们希望 $B_R$ 的字典序尽量小。

由于原串和原串的翻转拼接后是个回文串，我们可以将 $BA$ 操作中的长串 $BAAB_R$ 理解为 $AB_R$ 的翻转与它自身拼接得到，所以选出 $BA$ 等价于选出 $AB_R$。而 $A$ 是连续的 `a` 串，$B_R$ 的字典序要尽量小，那么 $AB_R$ 就是原串中的字典序最小子串。

现在问题转化为了：在长为 $2n$ 的字符串 $s$ 中找到字典序最小的长为 $n$ 的子串。

于是想到~~前几天刚学的~~ [$\text{Lyndon}$ 分解](https://oi-wiki.org/string/lyndon/)，利用它强有力的性质：串 $s$ 的 $\text{Lyndon}$ 分解 $w_1w_2\cdots w_k$ 满足 $w_1\ge w_2\ge \cdots \ge w_k$，那只要像最小表示法一样：取出这个分解中的一个 $\text{Lyndon}$ 串 $t$，使得它的起点小于 $n$ 且终点大于等于 $n$，就能找到字典序最小子串。

~~主要是代码比较好默~~


```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e6+7;
char a[N];
int n,k,len,ans,res;
ll qpow(ll a,ll b){ll ans=1;while(b){if(b&1) ans=ans*a;a=a*a,b>>=1;}return ans;}
int main(){
	scanf("%d%d",&n,&k);
	scanf("%s",a+1);
	for(int i=1;i<=n;i++) a[n*2-i+1]=a[i];
	int i=1;
	while(i<=n*2){
		int j=i+1,k=i;
		while(j<=n*2&&a[k]<=a[j]){
			if(a[k]<a[j]) k=i;
			else k++;
			j++;
		}
		while(i<=k) ans=i<=n?i:ans,i+=j-k;
	}
	if(k==1){for(int i=ans;i<ans+n;i++) printf("%c",a[i]);exit(0);}
	k--;
	int tmp=ans;while(a[tmp]==a[tmp+1]) tmp++;
	len=tmp-ans+1,res=min(1ll*n,1ll*len*qpow(2,k));
	if(k>32) res=n;
	for(int i=1;i<=res;i++) printf("%c",a[ans]);
	for(int i=1;i<=n-res;i++) printf("%c",a[tmp+i]);
	return 0;
}
```

---

## 作者：chen_zhe (赞：3)

# [AGC037E] Reversing and Concatenating

难得的比较简单的 AGC 的 E 题。

为了让最后所得的 $S$ 字典序最小，同时我们会发现在过程中并没有加入任何字符，因此我们考虑要找到一种方案，让原来的 $S$ 中，最小的那个字母尽可能长地位于开头。

我们来考虑对于每一次操作，我们会怎么处理，使得留给下一次操作的字符串 $S$ 最优。

很明显，我们会找到其中最小的同时也是最长的连续字符 $c$，不妨设长度为 $len$，然后以此为我们截出来的字符串的末尾，这样再进行一次翻转，就能有 $2 \times len$ 个 $c$ 在 $S$ 中间。很明显这样做，下一次就是有 $4 \times len$ 个 $c$，以此类推。

这样我们可以发现，对于最优解，至少有 $len\times 2^{k-1}$ 个 $c$ 位于原字符串的开头，那么我们可以先给最后的字符串输出 $len \times 2^{k-1}$ 个 $c$。如果 $N \leq len \times 2^{k-1}$ 那么就做完了。但是若 $N>len \times 2^{k-1}$，这个时候我们就应当找到原来的 $S$ 拼上翻转的 $S$ 后，其中的最小的长度为 $N$ 的子串，在输出 $2^{k-1}$ 个 $c$ 后再把子串接下去输出即可。

而因为查找最小子串的暴力是 $O(n^2)$ 的（暴力匹配），所以可以大力出奇迹。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cctype>
#include <queue>
#include <vector>

using namespace std;

inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
	while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}

int n,k;

char s[10050],ans[10050];

int main()
{
	n=read(),k=read();
	cin >> (s+1);
	for (int i=1;i<=n;i++)
		s[n*2-i+1]=s[i];
	for (int i=1;i<=n;i++)
		ans[i]=s[i];
	for (int i=1;i<=n;i++)
	{
		bool flag=true;
		for (int j=i;j<=n+i-1 && flag;j++)
		{
			if (ans[j-i+1]<s[j])
				flag=false;
			else if (ans[j-i+1]>s[j])
				break;
		}
		if (flag)
		{
			for (int j=i;j<=n+i-1;j++)
				ans[j-i+1]=s[j];
		}
	}
	int len=1;
	while (len<=n && ans[len]==ans[1])
		len++;
	len--;
	if (k>15 || len*(1<<(k-1))>=n)
	{
		for (int i=1;i<=n;i++)
			cout << ans[1];
	}
	else
	{
		int res=n-(len*(1<<(k-1)));
		for (int i=1;i<=n-res;i++)
			cout << ans[1];
		for (int i=1;i<=res;i++)
			cout << ans[i+len];
	}
	return 0;
}
```

---

## 作者：UnyieldingTrilobite (赞：2)

首先这个 $k$ 看着，很吓人锕！

我们考虑，既然是要字典序最小，那我们先考虑 $s$ 的第一个字符最小。我们可以先把所有不是最小的字符全部归为一类，换而言之，字符串现在只剩下了零和一。我们注意到，第 $k$ 次操作后字典序最小的串，实际上对应到就是第 $k$ 次倍长后最长的连零段（和它拖着的一堆字符）。我们观察这个连零，如果没有跨越俩第 $k-1$ 次操作后串的分界，那连零数量一定不多于第 $k-1$ 次操作后串里的连零数量，进而也不多于第 $k-1$ 次倍长后串里的最长连零长度（过 $n$ 自动截断）。而如果跨越了这个分界，则至多使连零长度翻倍（理想状态，连零正好在最末尾）。我们实际上发现，也只有按照如此操作，最后得到的连零才会是最长的。只有第一次操作需要二择一下——挑一个连零段塞到末尾，或者直接把末尾的连零段倍长。

这样我们就有基本思路了，然后大眼观察一下发现这个 $n$ 其实很小，那我们就可以直接采用最暴力的方式：枚举第一步，然后按照上面的固定策略大力模拟。注意到一次模拟中当连零已经充满了整个串就可以直接截断了。如此一来每个字符也是至多被踢出去一次，一轮模拟是线性的，总复杂度也就是平方的。

代码巨大好写。由于需要支持这个字符串长得像个队列，而且不希望像标准库队列那样只提供少得可怜的接口，这里使用了 deque 实现。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef deque<char> str;
int n, k;
str calc(str s) {
  int cnt = 0;
  for (auto it = s.rbegin(); it != s.rend(); ++cnt, ++it)
    if (*it != *s.rbegin()) break;
  for (int i = 0; i < k && cnt < n; ++i, cnt <<= 1)
    for (int j = 0; j < min(cnt, n - cnt); ++j) {
      s.pop_front();
      s.push_back(s.back());
    }
  return reverse(s.begin(), s.end()), s;
}
signed main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  string s;
  cin >> n >> k >> s, --k;
  str tmp(s.begin(), s.end()), ans = calc(tmp);
  for (int i = 1; i <= n; ++i) {
    tmp.pop_front();
    tmp.push_back(s[n - i]);
    ans = min(ans, calc(tmp));
  }
  return cout << string(ans.begin(), ans.end()) << endl, 0;
}
```

---

## 作者：GIFBMP (赞：2)

难得比较简单的 AGC 题。首先我们发现，对于 $k\ge \lceil\log n\rceil+1$ 的情况，我们只用找到 $S$ 中最小的字符输出 $n$ 次即可。那么我们就只用考虑 $k<\lceil\log n\rceil+1$ 的情况。

为了让字典序最小，最后开头最小字符的数量就要尽量多。首先我们找到原串中每个极大的最小字符组成的连续段，设它的长度为 $l$，那么在最后的串中，如果这个极长连续段的右端点为 $n$，那么开头最小字符数量即为 $l\times 2^k$，否则为 $l\times 2^{k-1}$。对于最后数量更大的，直接覆盖答案即可，否则我们需要比较后面部分的字典序。我们发现，对于右端点为 $n$ 的情况，后面的部分相当于从左端点不断往前跳，将扫到的字符依次连接形成的串；而对于右端点不为 $n$ 的情况，后面的部分相当于从右端点跳到 $n$ 再跳回去，将扫到的字符依次连接形成的串。（可以画图感性理解）

时间复杂度 $\Theta(n^2)$。

Code:

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cassert>
using namespace std ;
const int MAXN = 5e3 + 10 ;
int n , K , lg[MAXN] ;
char s[MAXN * 2] , t[MAXN] , ans[MAXN] ;
int main () {
	scanf ("%d%d" , &n , &K) ;
	for (int i = 2 ; i <= n ; i++) lg[i] = lg[i >> 1] + 1 ;
	scanf ("%s" , s + 1) ; char ch = 'z' ;
	for (int i = 1 ; i <= n ; i++)
		if (s[i] < ch) ch = s[i] ;
	if (K > lg[n] + 1 || (K == lg[n] + 1 && lg[n] != lg[n - 1])) {
		for (int i = 1 ; i <= n ; i++) putchar (ch) ;
		return 0 ;
	}
	for (int i = 1 ; i <= n ; i++) s[2 * n - i + 1] = s[i] ;
	if (K == 1) {
		bool flag = 0 ;
		for (int i = 1 ; i <= n + 1 ; i++) {
			if (s[i] != ch) continue ;
			for (int j = i ; j <= i + n - 1 ; j++) t[j - i + 1] = s[j] ;
			if (!flag) {
				flag = 1 ;
				for (int j = 1 ; j <= n ; j++) ans[j] = t[j] ;
				continue ;
			}
			bool ff = 0 ;
			for (int j = 1 ; j <= n ; j++)
				if (t[j] < ans[j]) {ff = 1 ; break ;}
				else if (t[j] > ans[j]) break ;
			if (ff) for (int j = 1 ; j <= n ; j++) ans[j] = t[j] ;
		}
		for (int i = 1 ; i <= n ; i++) putchar (ans[i]) ;
		return 0 ;
	}
	int mx = 0 ;
	for (int i = 1 , p = 0 ; i <= n ; i = p + 1) {
		if (s[i] != ch) {p = i ; continue ;}
		for (p = i ; p <= n && s[p] == ch ; p++) ;
		p-- ;
		int tmp = p - i + 1 ;
		//printf ("%d %d:%d\n" , i , p , tmp) ;
		if (p == n) tmp *= 2 ;
		if (tmp * (1 << (K - 1)) >= n) {
			for (int j = 1 ; j <= n ; j++) putchar (ch) ;
			return 0 ;
		}
		if (tmp > mx) {
			mx = tmp ; int nx = tmp * (1 << (K - 1)) + 1 ;
			for (int j = 1 ; j < nx ; j++) ans[j] = ch ;
			int k = p + 1 ; bool f1 = 0 ;
			if (p == n) k = i - 1 , f1 = 1 ;
			for (int j = nx ; j <= n ; j++) {
				ans[j] = s[k] ;
				if (f1) k-- ;
				else {
					k++ ;
					if (k == n + 1) k-- , f1 = 1 ;
				}
			}
				
		}
		else if (tmp == mx) {
			int nx = tmp * (1 << (K - 1)) + 1 ;
			for (int j = 1 ; j < nx ; j++) t[j] = ch ;
			int k = p + 1 ; bool f1 = 0 ;
			if (p == n) k = i - 1 , f1 = 1 ;
			for (int j = nx ; j <= n ; j++) {
				t[j] = s[k] ;
				if (f1) k-- ;
				else {
					k++ ;
					if (k == n + 1) k-- , f1 = 1 ;
				}
			}
			bool ff = 0 ;
			for (int j = 1 ; j <= n ; j++)
				if (t[j] < ans[j]) {ff = 1 ; break ;}
				else if (t[j] > ans[j]) break ;
			if (ff) for (int j = 1 ; j <= n ; j++) ans[j] = t[j] ; 
		}
	}
	for (int i = 1 ; i <= n ; i++) putchar (ans[i]) ;
	return 0 ;
}
```

---

## 作者：FZzzz (赞：2)

设整个串里最小的字母为 `a`。我们考虑这个串里 `a` 的连续段：
- 若一个 `a` 连续段在末尾，可以使得一次操作后的串有一个长度为它两倍的 `a` 段；
- 对于不在末尾的 `a` 段，可以使得一次操作后的串有一个与它等长的 `a` 段。

当然，所有这些段的长度不能大于 $n$。

那么由此，若 $k>1$，我们可以计算出一次操作后能得到的最长 `a` 段长度，并且把这个段放在得到的串的末尾。之后每次操作，我们使得这个段的长度加倍，并同样把它放在末尾，但在最后一次操作把它放在开头。

这样，我们放在结果串开头的这个 `a` 段一定是我们能够得到的最长 `a` 段，那么我们目标的字典序最小串一定也在开头有这么多 `a` 串，并且也一定可以由上述这种形式的一系列操作得到。我们接下来需要考虑让后面的串的字典序尽量小。

设 $A$ 表示一个极长的 `a` 段。那么，一个形如 $BA$ 的串一次操作后会得到的是 $BA^2$ 的一个后缀（如果这不是最后一次操作）。可以得到，如果第一次操作后得到的串是 $BA$，那么最后的串是 $A^{2^{k-1}}B_R$ 的一个前缀。于是我们只需要使得 $B_R$ 的字典序最小。

接下来是我觉得这道不算困难的题真正有意思的地方：由于 $SS_R$ 是回文串，那么若 $BA$ 在其中出现，则 $AB_R$ 也在其中出现。又由于 $A$ 是 $SS_R$ 中最长的 `a` 段，所以 $AB_R$ 就是 $SS_R$ 中字典序最小的长度为 $n$ 的子串。

于是我们得到了整个算法的另一种描述（注意到在一段以前我们已经得到了算法的一种描述，配合一些特判已经可以通过此题）：找到 $SS_R$ 字典序最小的长度为 $n$ 的子串，然后将其开头的同种字符的连续段 $2^{k-1}$ 倍长。而这样正好也完美契合了 $k=1$ 的情况！看到了吗，我们最终导出了一个非常简洁的算法，包含了所有特殊情况，并且甚至不需要显式找出整个串内最小的字符。

剩下的只有如何找到这个字典序最小的子串——当然是 $O(n^2)$ 暴力即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int readint(){
	int x=0;
	bool f=0;
	char c=getchar();
	while(!isdigit(c)&&c!='-') c=getchar();
	if(c=='-'){
		f=1;
		c=getchar();
	}
	while(isdigit(c)){
		x=x*10+c-'0';
		c=getchar();
	}
	return f?-x:x;
}
const int maxn=5e3+5;
int n,k;
char s[maxn],t[maxn];
char get(int x){
	return x<=n?s[x]:s[n*2-x+1];
}
int main(){
	#ifdef LOCAL
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	#endif
	n=readint();
	k=readint();
	scanf("%s",s+1);
	for(int i=1;i<=n;i++) t[i]=s[i];
	for(int i=2;i<=n+1;i++){
		bool flag=0;
		for(int j=1;j<=n;j++) if(get(i+j-1)!=t[j]){
			flag=get(i+j-1)<t[j];
			break;
		}
		if(flag) for(int j=1;j<=n;j++) t[j]=get(i+j-1);
	}
	int x=1;
	while(x<n&&t[x+1]==t[1]) x++;
	int y=k<15?min(x<<(k-1),n):n;
	for(int i=1;i<=y;i++) printf("%c",t[1]);
	for(int i=1;i<=n-y;i++) printf("%c",t[x+i]);
	#ifdef LOCAL
	fprintf(stderr,"%d\n",(int)clock());
	#endif
	return 0;
}
```
（其实本来想写个比较理性的严谨证明的，但是最后写出来就比较奇怪？

---

## 作者：lalaouye (赞：1)

感觉并不难。

最小化字典序有个套路是一个一个确定，这道题一看就难以这样做。然后我们考虑让字符串中充满最小的字符，但是发现还是不太好做。于是我们考虑考虑最大化开头最小字符的长度发现就简单了。我们先让字符串后缀为最小字符，每翻转合并一次连续最小字符段就会超级加倍，这样我们其实就做完了。我们只需要找到反转后字典序最小的前缀作为开始的 $s$，之后直接超级加倍并保持最长的连续最小字符段在后缀即可，最后一次移到前缀。

注意到本题可以 $\mathcal{O}(n^2)$，于是我就写了这个复杂度。[代码](https://atcoder.jp/contests/agc037/submissions/62387222)。

---

## 作者：xht (赞：1)

## [Reversing and Concatenating](https://atcoder.jp/contests/agc037/tasks/agc037_e)

### 题意

- 给定一个长度为 $n$ 的字符串 $s$。
- 你可以进行如下操作 $k$ 次：
  - 将 $s$ 变成 $ss^r$ 的一个长度为 $n$ 的子串。
- 要求最终 $s$ 的字典序最小。
- $n \le 5 \times 10^3$，$k \le 10^9$。

### 题解

另 $s$ 中最小的字符为 $c$，设 $s$ 中最长连续的 $c$ 的长度为 $l$，则最终的 $s$ 内我们至少可以构造出开头连续 $\min(n, 2^{k-1}l)$ 个 $c$ 的串。

若 $\min$ 是取到 $2^{k-1}l$，则意味着后面还有一些字符要确定，可以发现后面的字符一定是 $ss^r$ 的一个后缀，由于数据范围很小，直接暴力找最小后缀即可，时间复杂度 $\mathcal O(n^2)$。

### 代码

```cpp
const int N = 1e4 + 7;
int n, k, a[N], l, w;
char s[N], c, ans[N];

inline void upd(int p) {
	bool ok = 1;
	for (int i = 1; i <= w; i++) {
		if (ans[i] > s[p - i + 1]) break;
		if (ans[i] < s[p - i + 1]) {
			ok = 0;
			break;
		}
	}
	if (!ok) return;
	for (int i = 1; i <= w; i++)
		ans[i] = s[p - i + 1];
}

int main() {
	rd(n, k), rds(s, n);
	for (int i = 1; i <= n; i++)
		s[n + n + 1 - i] = s[i];
	c = *min_element(s + 1, s + n + n + 1);
	for (int i = 1; i <= n + n; i++)
		a[i] = s[i] == c ? a[i - 1] + 1 : 0;
	l = *max_element(a + 1, a + n + n + 1);
	if (k >= 14 || ((n - 1) >> (k - 1)) + 1 <= l) {
		for (int i = 1; i <= n; i++) printc(c);
		return 0;
	}
	w = n - (l << (k - 1));
	ans[1] = 'z' + 1;
	for (int i = 1; i <= n; i++)
		if (a[n + i] == l) upd(n + i - l);
	for (int i = 1; i <= (l << (k - 1)); i++) printc(c);
	prints(ans, w);
	return 0;
}
```

---

## 作者：关怀他人 (赞：1)

### AGC 037E
#### Solution
首先为了字典序最小，我们肯定是让最小的字母接在最前面，记开头的连续最小字母个数为$len$

如果$s[n]$是最小字母，且以$s[n]$为结尾的连续的最小字母长度为$L$，那么$len$要和$L\times 2^k$取较大值

如果$s[i](i\neq n)$是最小字母，且包含$s[i]$的连续的最小字母长度为$L$，那么$len$要和$L\times 2^{k−1}$取较大值

然后取这其中字典序最小的即可，复杂度$\mathcal O(n^2)$
#### Code
```cpp
int n,K;
char minn = 'z';
char s[MAXN],t[MAXN],ans[MAXN];

bool cmp(char *a,char *b){
    for(int i = 1;i <= n;i++){
        if(a[i] != b[i])
            return a[i] < b[i];
    }
    return false;
}

void Solve(char *s,int k){
    int pos = n,len = 0;
    while(pos && s[pos] == minn){
        pos -= 1;
        len += 1;
    }
    while(k && len < n){
        len <<= 1;
        k -= 1;
    }
    if(len >= n){
        for(int i = 1;i <= n;i++)
            putchar(minn);
        exit(0);
    }
    for(int i = 1;i <= len;i++)
        t[i] = minn;
    for(int i = len + 1;i <= n;i++)
        t[i] = s[pos--];
    if(cmp(t,ans)){
        for(int i = 1;i <= n;i++)
            ans[i] = t[i];
    }
}

int main(){
    scanf("%d%d%s",&n,&K,s + 1);
    for(int i = 1;i <= n;i++){
        minn = min(minn,s[i]);
        ans[i] = 'z';
        s[(n << 1) - i + 1] = s[i];
    }
    if(s[n] == minn)
        Solve(s,K);
    for(int i = n;i <= (n << 1);i++){
        if(s[i] == minn)
            Solve(s + i - n,K - 1);
    }
    for(int i = 1;i <= n;i++)
        putchar(ans[i]);
    return 0;
}
```

---

## 作者：Acfboy (赞：0)

首先想到只进行一步这样的操作，显然是要把最小的那个在一起最长的取走，若有相同长度，那么后面的字典序要尽可能的小。

那么要进行更多的步骤怎么做呢，显然每次把最小的放在头上是不合理的，因为只有尾部的会被复制，而一次操作可以把任意一段扔到队尾或放到开头，所以除了开头可结尾，让最小的字母组成的一段放在最末尾肯定是最优的。

但如果存在同样的几组的怎么办呢，模拟几个小的数据观察就会发现，复制后前面的一段就会反过来拼在最小的那段复制完的后面，而这一段是永远不会变的。

比如 $\textsf{twtwa}\rightarrow  \textsf{t\underline{wtwaa}wtwt}\rightarrow \textsf{wt\underline{waaaa}wtw} \rightarrow \textsf{aaaaw}$

虽然最后结果中前面的 `a` 的数量增加了，但最后一直是 $\textsf{wtwt}$ 后面减少掉了一些，所以若开始时最小的字母组成的一块 **前面一段倒过来** 的字典序是最小的，变换后肯定也是最小的。

所以我们就有了以下做法：

1. 使用一步将最小的字母组成的最长的块（相同的取前面一段倒过来字典序最小的）移到最后。
2. 按题目要求进行变换，同时保证最小的字母组成的一块在最后。
3. 使用最后一步将最小的字母组成的移动到字符串最前面。

需要注意的是，开始时取的前面一段字典序最小是要在复制后的意义下复制出来的部分前面一段字典序最小，因为那才是我们实际上取的，由于复制意义下才是我们真正取的，所以还要判断最后的几个字符复制以后成为最长的最小字母组成的一块的情况（因为这个调了很久）。

在第二步模拟时如果最小字母组成的那块长度已经大于 $n$, 就不用继续了。这条性质保证了时间复杂度是 $O(n \log_2 n)$ 的。（但第一步处理需要 $n^2$）

$k=1$ 的时候要进行特判，因为没有机会让我们执行前两步了。

代码

```cpp
#include <iostream>
#include <string>
#include <algorithm>
#include <cstdio>
int n, k;
std::string s;
int main() {
	std::cin >> n >> k;
	std::cin >> s;
	char min = 'z';
	for(int i = 0; i < n; i++) min = std::min(min, s[i]);
	int maxj = 0, maxs = 0;
	std::string minpre;
	for(int i = 0; i < n; i++) minpre += 'z'+1;
	for(int i = n-1; i >= 0; i--) 
		if(s[i] == min) {
			int cnt = 0, j = i;
			for( ; j >= 0 && s[j] == min; cnt++, j--) ;
			std::string tmp1 = s.substr(j+1, n-1-j-1+1);
			std::string tmp2 = s.substr(n-j-1, n-n+j+1+1);
			std::reverse(tmp2.begin(), tmp2.end());
			std::string twt = tmp1 + tmp2;
			if(cnt > maxs || cnt == maxs && twt < minpre) 
				maxs = cnt, maxj = j, minpre = twt;
		}	
	int j = n-1, cnt = 0;
	for( ; j >= 0 && s[j] == min; j--, cnt++) ;
	std::string tm = s.substr(n-j-1, j+1) + s.substr(j+1, n-j-1);
	std::reverse(tm.begin(), tm.end());
	if(cnt*2 > maxs || cnt*2 == maxs && tm < minpre) maxs = cnt, maxj = j, minpre = tm;
	maxj ++;
	std::string t;
	t = s;
	std::reverse(t.begin(), t.end());
	s = s + t;
	if(k == 1) {
		s = s.substr(maxj, n);
		std::cout << s;
		return 0;
	}
	if(maxj + maxs != n) {
		s = s.substr(n-maxj, n);
		k -= 1;
	}
	for(int i = 1; i < k; i++) {
		t = s;
		std::reverse(t.begin(), t.end());
		s = s + t;
		s = s.substr(maxs, n);
		maxs <<= 1;
		if(maxs >= n) break; 
	}
	if(maxs > n) maxs = n;
	t = s;
	std::reverse(t.begin(), t.end());
	s = s + t;
	s = s.substr(n-maxs, n);
	std::cout << s;
	return 0;
}
```

---

## 作者：int08 (赞：0)

## 前言
睡前脑力小测验，偶遇超级唐题，保住睡眠时间。

# Solution

看这个 $k$，它很大，我们合理猜测应该很大的 $k$ 没啥用，也就是要求出多少次操作可达到理论最小。

发现理论能得到的最小串是 $n$ 个串中最小字母（以下记为 `a`，我们第一步先考虑放一个 `a` 在结尾，接下来每一步，由于对称，这个 `a` 后缀长度都可以增加一倍，只需要 $O(\log k)$ 次就可以变成全 `a`。

那么在没有变成全 `a` 的时候，我们肯定贪心地希望 `a` 后缀（注意要用最后一次变成前缀）越长越好啊。

那么第一步获得的 `a` 后缀应该越长越好，于是，除了第一次操作有多种方案，后面每次操作的最优位置都是唯一的。

第一次的时候可能有多个位置有等长的 `a` 串，我们希望最小化后面的部分，于是选取（翻转过来之后）字典序最小的那个。

最后我们得到了一个非常闹弹的结论：每次选择翻转后字典序最小的子串即可。

直接暴力查找，复杂度 $O(n^2\log n)$，不过跑不满，直接过了。

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,i,j;
string s,mi,a; 
int main()
{
	cin>>n>>k>>s;
	s.resize(2*n);mi.resize(n),a.resize(n);
	for(i=n;i<2*n;i++) s[i]=s[2*n-1-i];
	while(k--)
	{
		for(i=0;i<n;i++) mi[i]='z';
		for(i=0;i<=n;i++)
		{
			for(j=0;j<n;j++) a[j]=s[i+j];
			mi=min(mi,a);
		}
		for(i=1;i<n;i++) if(mi[i]!=mi[0]) break;
		if(i==n) cout<<mi,exit(0);
		if(k) reverse(mi.begin(),mi.end());
		for(i=0;i<n;i++) s[i]=mi[i],s[2*n-1-i]=s[i];
	}
	cout<<mi;
	return 0;
}
```

# The End.

---

## 作者：Infiltrator (赞：0)

[$\Large\color{#FFBBFF}\textit{Tian-Xing's blog}$](https://Tian-Xing.github.io)

------------

# Description

[传送门](https://atcoder.jp/contests/agc037/tasks/agc037_e)

------------

# Solution

要求字典序最小，那么把原字符串中最小的移到开头一定是最优的。

同时为了使字典序尽量小，我们要使字符串中开头最小的字符串的数量尽可能的多且连续，由于是把字符串的反串放到字符后面，那我们先把最小的字符移动到字符串结尾，然后截取若干段最小字符和前面的一些字符，我们会得到结尾是若干最小字符的新串，这样反复操作，直到最后一次操作时截取开头是若干最小字符的字符串一定是最优的。

把最小的字符移动到结尾保证了开头字符最小，正串和反串接起来最后一段会加倍保证了连续的最小字符数量最多。

这样我们除第一次外每次操作都能使得字符串中最小的字符的个数翻倍，那么过不了多久整个字符串就全变成了最小字符。

所以可以暴力模拟整个过程，具体的找到原串中连续最小字符最多的一个子串用一次操作移动到结尾，然后每次操作加倍，注意到如果最后不是整个串都是最小字符，后面会剩下原串的一些东西，其实每次可以暴力把这些东西提出来比较，但是也可以在最开始把反串接到原串后面找到最小的位置，代码量大幅度减少。

------------

# Code

```cpp
/*
    _______                       ________                        _______
   / _____ \                     / ______ \                      / _____ \
  / /     \_\  _     __     _   / /      \ \   _     __     _   / /     \_\
 | |          | |   |  |   | | | |        | | | |   |  |   | | | |
 | |          | |   |  |   | | | |     __ | | | |   |  |   | | | |
 | |       __ \  \  |  |  /  / | |     \ \| | \  \  |  |  /  / | |       __
  \ \_____/ /  \  \/ /\ \/  /   \ \_____\  /   \  \/ /\ \/  /   \ \_____/ /
   \_______/    \___/  \___/     \______/\__\   \___/  \___/     \_______/
*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int N = 5000;

int n, k;

char st[N * 2 + 50];

int Cmp(int a, int b)
{
	for (int i = 1; i <= n; i++)
	{
		if (st[a - i + 1] < st[b - i + 1]) return 1;
		if (st[a - i + 1] > st[b - i + 1]) return 2;
	}
	return 0;
}

int main()
{
	scanf("%d%d", &n, &k);
	scanf("%s", st + 1);
	for (int i = 1; i <= n; i++) st[n * 2 - i + 1] = st[i];
	int pos = n;
	for (int i = n + 1; i <= n * 2; i++) if (Cmp(i, pos) == 1) pos = i;
	k--;
	int len = 1;
	while (st[pos - len] == st[pos] && len + 1 <= n) len++;
	int tmp = len;
	int ned = 0;
	while (len < n && ned + 1 <= k) len *= 2, ned++;
	if (len >= n) for (int i = 1; i <= n; i++) putchar(st[pos]);
	else
	{
		for (int i = 1; i <= len; i++) putchar(st[pos]);
		for (int i = 1; i <= n - len; i++) putchar(st[pos - tmp + 1 - i]);	
	}
	return 0;
}
```

---

