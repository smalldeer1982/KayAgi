# Yet Another Substring Reverse

## 题目描述

You are given a string $ s $ consisting only of first $ 20 $ lowercase Latin letters ('a', 'b', ..., 't').

Recall that the substring $ s[l; r] $ of the string $ s $ is the string $ s_l s_{l + 1} \dots s_r $ . For example, the substrings of "codeforces" are "code", "force", "f", "for", but not "coder" and "top".

You can perform the following operation no more than once: choose some substring $ s[l; r] $ and reverse it (i.e. the string $ s_l s_{l + 1} \dots s_r $ becomes $ s_r s_{r - 1} \dots s_l $ ).

Your goal is to maximize the length of the maximum substring of $ s $ consisting of distinct (i.e. unique) characters.

The string consists of distinct characters if no character in this string appears more than once. For example, strings "abcde", "arctg" and "minecraft" consist of distinct characters but strings "codeforces", "abacaba" do not consist of distinct characters.

## 样例 #1

### 输入

```
abacaba
```

### 输出

```
3
```

## 样例 #2

### 输入

```
abcdecdf
```

### 输出

```
6
```

## 样例 #3

### 输入

```
aabbcc
```

### 输出

```
3
```

## 样例 #4

### 输入

```
abcdeefc
```

### 输出

```
6
```

# 题解

## 作者：灵茶山艾府 (赞：10)

SOSDP。

遍历 $S$，处理出所有不含相同字符的子串，由于子串不含相同字符，因此可以用二进制数来表示。

翻转操作本质上是在 $S$ 中找两个不相交子串，且拼接后不含相同字符。

因此，从位运算的角度，原问题等价于：

> 给一个数组 $a$，求满足 $a_i \& a_j = 0$ 的 $a_i | a_j$ 的二进制中 $1$ 的个数的最大值。

我们可以枚举 $a_i$，求出 $a_i$ 的补集的子集中的二进制中 $1$ 的个数的最大值，其与 $a_i$ 的二进制中 $1$ 的个数之和的最大值就是答案。

这可以用 SOSDP 来做，转移时维护二进制中 $1$ 的个数的最大值即可。

AC 代码（Golang）:

```go
package main
import("bufio";."fmt";."os")

func main() {
	s := ""
	Fscan(bufio.NewReader(Stdin), &s)
	dp := make([]int, 1<<20)
	for i := range s {
		for j, x := i, 0; j >= 0 && x>>(s[j]-'a')&1 == 0; j-- {
			x |= 1 << (s[j] - 'a')
			dp[x] = i - j + 1
		}
	}
	for i := 0; i < 20; i++ {
		for j := 0; j < 1<<20; j++ {
			j |= 1 << i
			dp[j] = max(dp[j], dp[j^1<<i])
		}
	}
	ans := 0
	for i, v := range dp {
		ans = max(ans, v+dp[1<<20-1^i])
	}
	Print(ans)
}

func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}
```


---

## 作者：littleseven (赞：8)

### 题目解析：

[博客地址](http://littleseven.top/)

部分参考：https://www.cnblogs.com/Lubixiaosi-Zhaocao/p/11620068.html

只用前20个字母，这不会是歧视吧……$QwQ$。

——————这不告诉你用状压嘛！！！

那么提出一个想法：

令集合$X=\{ 'a','b','c', \dots ,'t',\}$，用$|x|$表示集合$X$的大小。

预处理集合$X$的所有有效子集（在原字符串当中可以找到），之后在枚举$X$的子集$A$，和集合$A$在$X$中的补集$B$的子集$C$。如果$C$有效（原串能够找到），那么$|A|+|C|$就是答案的一种可能。

不过………………显然TLE！！！

到现在为止还没有用到DP，那么我们考虑一个问题，加入我们知道集合$B$的有效自己的大小的最大值$max \{ |C| \}$，就可以用$|A| + max \{ |C|\}$在$O(1)$的时间内更新答案。这时我们就要用到DP预处理出$max\{ |C|\}$。

用$dp[now]$表示以二进制表示的集合$S$的最大有效自己的大小，那么：

- 如果$S$有效，$dp[now] = |S|$
- 否则：$dp[now] = max(dp[now],dp[now xor (1 << i)]) ~~~ (i \in 0 \sim 20 ,(now \& (1 << i)))$

```cpp
#include <bits/stdc++.h>
 
using namespace std;
 
const int N = 20;
 
const int M = 10e6 + 10;
 
int dp[1 << N];
 
int main() {
	char s[M];
	scanf("%s", s);
	int len = strlen(s);
	for (int i = 0; i < len; i ++ ) {
		int now = 0;
		for (int j = 0; j < N && i + j < len; j ++ ) {
			int ch = s[i + j] - 'a';
			if (now & (1 << ch)) {
				break ;
			}
			now |= (1 << ch);
			dp[now] = j + 1;
		}
	}
	for (int now = 0; now < (1 << N); now ++ ) {
		for (int i = 0; i < N; i ++ ) {
			if (now & (1 << i)) {
				dp[now] = max(dp[now], dp[now ^ (1 << i)]);
			}
		}
	}
	int ans = 0;
	for (int now = 0; now < (1 << N); now ++ ) {
		int tmp = ((1 << N) - 1) ^ now;
		ans = max(ans, dp[now] + dp[tmp]);
	}
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：Kelin (赞：6)

## [题意](https://blog.csdn.net/BeNoble_/article/details/101947804)

给你一个字符串$S$，你可以翻转一次$S$的任意一个子串。

问翻转后$S$的子串中各个字符都不相同的最长子串长度。

$|S|\le10^6,|$字符集$|\le20$

------------

## 题解

可以发现通过翻转操作我们可以将任意两个子串拼在一起。

这样子串所在的位置就不重要了，只需要记录字符的状态即可。

注意到$|$字符集$|\le20$，考虑状压记录所有的字符集状态。

设$f_s$表示状态$s$中有多少字母（其实就是$s$的二进制中有多少$1$），设全集为$T$。

那么：

$$f_s=\max_{1\le i\le j\le|S|}(j-i+1|S_i\neq S_{i+1}\neq...\neq S_j,s=S_i+...+S_j)$$

所以：

$$Ans=\max_{s\subseteq T}(f_s+\max_{t\subseteq T-s}f_t)$$

可以发现后面的枚举子集完全可以预处理出来。

记$g_s=\max_{t\subseteq s}f_t$，则$Ans=\max_{s\subseteq T}(f_s+g_{T-s})$

总时间复杂度$O(|S||T|+|T|2^{|T|})$

```
#include<bits/stdc++.h>
#define fp(i,a,b) for(register int i=a,I=b+1;i<I;++i)
#define fd(i,a,b) for(register int i=a,I=b-1;i>I;--i)
#define go(u) for(register int i=fi[u],v=e[i].to;i;v=e[i=e[i].nx].to)
#define file(s) freopen(s".in","r",stdin),freopen(s".out","w",stdout)
template<class T>inline bool cmax(T&a,const T&b){return a<b?a=b,1:0;}
template<class T>inline bool cmin(T&a,const T&b){return a>b?a=b,1:0;}
using namespace std;
const int N=1e6+5,M=21,S=(1<<20)-1;
int n,ans,Mi[M],cnt[S+5],f[S+5];char s[N];
int main(){
	#ifndef ONLINE_JUDGE
		file("s");
	#endif
	Mi[0]=1;fp(i,1,19)Mi[i]=Mi[i-1]<<1;
	fp(i,0,S)cnt[i]=cnt[i>>1]+(i&1);
	gets(s+1);n=strlen(s+1);
	fp(i,1,n){
		vector<bool>v(20);
		int w=0;
		fp(j,0,min(19,n-i)){
			if(v[s[i+j]-'a']==1)break;
			v[s[i+j]-'a']=1;
			w|=Mi[s[i+j]-'a'];
			f[w]=cnt[w];
		}
	}
	fp(i,1,S)fp(j,0,19)
		if(i&Mi[j])cmax(f[i],f[i^Mi[j]]);
	fp(i,1,S)if(f[i]==cnt[i])
		cmax(ans,f[i]+f[S^i]);
	printf("%d\n",ans);
return 0;
}
```

---

## 作者：laoliu12345 (赞：2)

## CF1234F
[题目传送门](https://www.luogu.com.cn/problem/CF1234F)
### 解法说明
#### 一、对于字符串翻转的理解
   字符串翻转这个操作很难进行，**经过思考后我们发现翻转字符串   $s[r_1+1,r_2]$   这个操作可以看作选择   $s[l_1,r_1]$   和   $s[l_2,r_2]$   这两段序列**。故题意转化为在序列   $S$   中选两个字符串，使得拼起来后各个字符依然都不相同，并且长度最长。直接统计有多少种此种字符串，时间复杂度   $O(k \times N)$  。 
##### 二、考虑如何找到两个满足条件的最长字符串
因为两个字符串没有相同的字符，所以可以以  $O(2^k)$  的时间复杂度枚举字符集   $A$   $B$  的每种可能。
那么所选的两个字符串就是  $A$  $B$  的子集。  此时用**状压**的思想，再用**高位前缀和**进行转移，即可算出对于每个集合子集中的最大值，时间复杂度  $O(k \times 2^k)$  。

**整体时间复杂度   $O(k \times N+k \times 2^k)$    。解释：  $k$   指字符集大小，最大为二十。**
下面就可以愉快的写代码了。
### 本题代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1<<20;
int f[N];
string s;
signed main()
{
	cin>>s;
	f[0]=0;
	for(int i=0;i<s.size();i++)
	    for(int j=i,k=0;j>=0;j--)
	    {
	    	if(k&(1<<s[j]-'a')) break;
	    	k|=(1<<s[j]-'a');
	    	f[k]=__builtin_popcount(k);
		}
	for(int i=0;i<20;i++)
	    for(int j=0;j<(1<<20);j++)
	        f[j|(1<<i)]=max(f[j|(1<<i)],f[j]);
	int ans=0;
	for(int i=0;i<(1<<20);i++)
	    ans=max(ans,f[i]+f[((1<<20)-1)^i]);
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：liangbowen (赞：2)

[blog](https://www.cnblogs.com/liangbowen/p/17934640.html)。小清新题，下文 $V=20$ 即值域。

---

反转操作，本质就是选两个不相交连续段拼起来。

显然合法的最终串长度一定 $\le V$。将这些合法串预处理出来，那么每个串都对应一个「字母集合」。

随便 DP 一下，求出所有集合中，的最大的合法「字母集合」大小。$dp_{\small U}$ 就是**只选一个连续段**的答案（$U=\small\{\texttt{a},\cdots,\texttt{t}\}$）。

那么选两个连续段就是 $\max\limits_{s\subseteq U}dp_s+dp_{\small U\normalsize-s}$。输出即可。

[code](https://codeforces.com/contest/1234/submission/239086683)，时间复杂度 $O(2^VV)$，其中 $V=20$。

---

## 作者：ziyistudy (赞：1)

## 前言

> 模拟赛赛时切紫，什么实力？！

## 正言

发现一个性质：因为只能翻转一次，所以我们不可能将三个连续子串弄到一起；且对于任意位置没有相交的两个连续子串，我们都能将它们通过翻转变成一个子串。

所以我们只需要找到两个“不相交，没有重复字母”的连续子串的最长长度和。

容易想到状压 dp。对于每个合法子串（发现长度不会超过 $20$，所以不会超时），打上标记。

可发现直接找不相交太多了，考虑进行高维前缀和（[想到上次模拟赛也有一道高维后缀和](https://www.luogu.com.cn/article/4ev489mw)）。这样，便可以轻松通过并集等于 $2^n-1$ 快速求解。


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define eb emplace_back
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
typedef vector<int> VI;
typedef long long ll;
typedef pair<int,int> PII;
const ll MOD=998244353;
// head
const int N=20,M=1e6+5;
int dp[(1<<N)+5];
int a[M];
int flag;
signed main() 
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    string s;cin>>s;int slen=s.length();
    for(int i=0;i<slen;i++) a[i]=1<<(s[i]-'a');
    int i=0,j=0;
    while(j<slen)
    {
        if(j<slen&&(!(flag&a[j]))){
            flag^=a[j];
            j++;
        }
        else {
            int tmp=0;
            for(int x=i;x<j;x++){
                tmp=0;
                for(int y=x;y<j;y++){
                    tmp^=a[y];
                    dp[tmp]=y-x+1;
                }
            }
            flag^=a[i];
            i++;
        }
    }
    int tmp=0;
    for(int x=i;x<j;x++){
        tmp=0;
        for(int y=x;y<j;y++){
            tmp^=a[y];
            dp[tmp]=y-x+1;
        }
    }
    for(int i=0;i<(1<<N);i++){
        if(dp[i]){
            for(int j=0;j<N;j++) if(!(i&(1<<j))) dp[i^(1<<j)]=max(dp[i^(1<<j)],dp[i]);  
        }
    }
    int ans=0;
    for(int i=0;i<(1<<N);i++){
        ans=max(ans,dp[i]+dp[((1<<N)-1)^i]);
    }
    cout<<ans<<endl;
}
```

---

## 作者：Targanzqq (赞：1)

### 思路：状压 dp。

我们考虑到字符集的大小只有 $20$，就能想到使用二进制位表示每个字符是否只出现 $1$次。

在这个题中，翻转并不会带来顺序影响，只会带来位置影响。因此我们相当于是把两个不相邻的字符串拼到一起，通过这种方式来增加贡献。

然而产生贡献的子串并集一定为 $0$，要不然它们拼起来就会出现相同字符，也就是说它们按位与运算结果为 $0$。然后我们要把它们合并，这里使用按位或运算或者按位异或运算都行。

因此，我们可以预处理出来所有合法子串是否出现。我们只要枚举所有在 $S$ 中的子串，判断它是否合法，如果合法就给他打上标记。

然后我们就对所有合法子串枚举补集的子集。如果这个子集出现过了，我们就让答案更新为当前子串和这个子集按位或运算的结果中 $1$ 的数量。而且它们没有重合部分，否则它们的交集就不为 $0$ 了。设字符集大小为 $n$，这样做的时间复杂度为 $O(n3^n+|S|n)$。这样做显然会超时。

因此我们还有一个方法，就是在处理出合法子串后，再从小到大枚举，这样可以满足在合法状态中加入 $1$ 的数量相对于它转移前的状态更多。这样我们就减少了枚举子集的部分。时间复杂度 $O(n2^n+|S|n)$，可以通过本题。

源代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define n 20 
using namespace std;

string s;
int a[1000001],f[1<<20],g[1<<20],lst[20],m,ans;
queue<int> q;

void find(){
	for(int i=0;i<m;i++){
		int now=(1<<a[i]);
		g[now]=1;f[now]=1;
		for(int j=1;i+j<m;j++){
			if(now&(1<<a[i+j]))break;
			now|=(1<<a[i+j]);
			g[now]=j+1;
			f[now]=j+1;
		}
	}
	for(int i=0;i<(1<<n);i++){
		for(int j=0;j<n;j++){
			if(i&(1<<j)){
				g[i]=max(g[i],g[i^(1<<j)]);
			}
		} 
	}
}

void solve(){
	for(int i=0;i<(1<<n);i++){
		if(f[i]){
			int k=0;
			for(int j=0;j<n;j++){
				if(!(i&(1<<j)))k+=(1<<j);
			}
			ans=max(ans,f[i]+g[k]);
		}
	}
}

signed main(){
	ios::sync_with_stdio(false);
	cin>>s;
	int cnt=0;
	for(auto i:s){
		a[cnt++]=i-'a';
	}
	m=s.length();
	find();
	solve();
	cout<<ans;
}

```

---

## 作者：2huk (赞：1)

> - 给你一个字符串 $S$，你可以翻转一次 $S$ 的任意一个子串。问翻转后 $S$ 的子串中各个字符都不相同的最长子串长度。
> - $|S| = n \le 10^6$，$s_i \in \{\texttt a, \texttt b, \dots, \texttt t\}$，字符集大小 $V \le 20$。

首先答案为最长的两个各个字符都不同的子串的长度和。因为两个子串一定可以通过一次旋转变得相邻。

若令 $f(S)$ 表示是否存在一个子串的字母的 **出现状态** 为 $S$，其中 $S$ 是一个大小 $\le 20$ 的字符集合。那么答案为：

$$
\max_{f(S) \text{ is true} ,f(S') \text{ is true},S \cap S' = \varnothing}\{|S| + |S'|\}
$$

可以用 $\Theta(Vn)$ 预处理 $f(S)$，并用 $\Theta(2^{2n})$ 计算答案。显然不优。

考虑优化：

$$
\max_{f(S) \text{ is true}, S' \subseteq \overline{S}, f(S')\text{ is true}}\{|S| + |S'|\}
$$

也就是枚举 $S$ 的补集的子集 $S'$。复杂度为 $\Theta(3^n)$。还是不优。

若我们可以预处理 $g(S)$：

$$
g(S)= \max_{S' \subseteq S, f(S) \text{ is true}} \{|S'|\}
$$

那么答案为：

$$
\max_{f(S) \text{ is true}}\{|S| + g(\overline{S})\}
$$

$g$ 就是标准的 **高维前缀和** 形式了。

```cpp
#include <bits/stdc++.h>

constexpr int N = 2e6 + 10, M = 20;

char str[N];
int f[N], n, a[N], g[N];

int main() {
	scanf("%s", str + 1);
	n = strlen(str + 1);
	for (int i = 1; i <= n; ++ i ) a[i] = str[i] - 'a';
	
	int res = 0;
	for (int i = 1; i <= n; ++ i ) {
		g[1 << a[i]] = f[1 << a[i]] = 1;
		for (int j = 2, state = (1 << a[i]); i + j - 1 <= n; ++ j ) {
			if (state >> a[i + j - 1] & 1) break;
			state |= (1 << a[i + j - 1]);
			g[state] = f[state] = j;
		}
	}
	
	for (int i = 0; i < (1 << M); ++ i )
		for (int j = 0; j < M; ++ j )
			if (i >> j & 1) g[i] = std::max(g[i], g[i ^ (1 << j)]);
	
	for (int i = 0; i < (1 << M); ++ i ) {
		if (!f[i]) continue;
		res = std::max(res, f[i] + g[~i & ((1 << M) - 1)]);
	}
	
	std::cout << res << '\n';
	
	return 0;
}
```

---

## 作者：Expert_Dream (赞：1)

这道题首先考虑反转的性质，发现反转前有两个子串，在反转之后两个子串会合并在一起，由于先后顺序无关，所以等价。

因此题意转换为两个没有相同字母交集的两个子串，长度之和最大是多少。

发现字母只有 $20$ 个，所以子串长度最多也就 $20$，因此子串可以暴力枚举，总共有 $20 \times n$ 个子串。

我们可以将每一个子串的状态，也就是对应字母是否出现预处理出来。如果对于一个子串的状态是 $s_x$，则当有一个 $s_x \& s_y = 0$ 的子串 $y$ 时它们可以匹配，作为一对，然后长度相加。（$\&$ 表示二进制按位与）。

这样问题转换为了 [CF165E](https://www.luogu.com.cn/problem/CF165E) 的问题。变成了高维前缀和模板，直接套用即可，转移的时候取最大值。

最后记得判断一下答案在 $[1,n]$ 的范围内。

~~梦熊 OJ 上不用特判最后一个地方可以过耶~~。

```cpp
string s;
int vis[N],n,a[N],ans=0,f[N];
void solve(){
	cin >> s; 
	n=sz(s);
	For(i,1,n) a[i] = s[i-1]-'a';
	set<pii> st;
	For(i,1,n){
		int z=0;
		For_(j,i,max(0ll,i-20)){
			if(z & (1ll<<a[j])){
				break;
			}z |= (1ll<<a[j]);
			vis[z]=max(vis[z],i-j+1);
		}	
	}For(i,0,(1<<22)-1){
		f[i]=vis[i];
	}
	For(i,0,21)For(j,0,(1<<22)-1){
		if(j&(1<<i)) f[j] = max(f[j],f[j^(1<<i)]); 
	}
	int ans=0;
	For(i,0,(1<<22)-1){
		ans = max(ans,f[((1<<22)-1)^i]+vis[i]);
	}cout<<min(max(ans,1ll),n);
}
```

---

## 作者：SAMSHAWCRAFT (赞：0)

关键词：状态压缩 DP。

题意很简单易懂，给定字符串 $S$，可以翻转 $S$ 的任意一个子串，求翻转后 $S$ 的子串中每一个字符都不相同的最长子串长度。其中 $|S|\le 10^6$，记字符集为 $V$，有 $|V|\le 20$。

看到 $|V|\le 20$ 我们一般往高维 DP 或者状压 DP 上想。注意到通过翻转操作我们可以把任意两个不相交的子串拼接在一起，这里给一个构造解，假设现在有串 $abcde$，欲使子串 $d$ 与 $b$ 拼接，只需翻转 $bc$ 或 $cd$ 即可，对于更长不相交子串都可以规约到这个模型上。有了这个结论，我们发现我们无需关心子串的位置，而只要看子串内部含有的字符种类即可，我们使用状态压缩记录串内是否出现某种字符即可。

设计状态 $f(x)$ 为串内出现字符状态为 $x$ 的每一个字符都不相同的子串的长度，我们考虑 $O(|S||V|)$ 枚举每一个字符都不相同的子串 $T$（下标从 $0$ 开始），即对 $\forall i,j\in [0,|T|)\cap \mathbb{Z}$，若 $i\ne j$，都有 $T_i\ne T_j$，可以用下面这种方法处理出 $f(x)$ 的初值（即翻转之前各状态对应的值）：

```cpp
for(int cx=0;cx<n;++cx){
  int S=0;
  for(int cy=0;cy<B&&cx+cy<n;++cy){
    //B 为字符集大小，即题解中的 V
    int ch=s[cx+cy]-'a';
    if(S&(1<<ch)) break;
    S|=(1<<ch);
    dp[S]=cy+1;
  }
}
```

接下来考虑对串的翻转，我们要的是翻转后没有相同字符的最长子串长度，所以在全集 $U=2^V$ 上枚举，可以得知 $f(x)$ 的状态转移方程：

$$
f(x)=\max_{x\subseteq U} \{ f(x),\max_{y\subseteq x } f(y) \} 
$$

其中 $\oplus$ 为按位异或。而 $\max_{y\subseteq U\oplus x } f(y)$ 正是我们之前预处理出的 $f$ 的初值，代码如下：

```cpp
for(int S=0;S<U;++S)
  for(int cx=0;cx<B;++cx)
    if(S&(1<<cx)) dp[S]=std::max(dp[S],dp[S^(1<<cx)]);
```

统计答案时直接在全集上枚举即可，答案即 $\max_{x\subseteq U} (f(x)+f(U\oplus x))$。

由此，我们有了一个 $O(|S||V|+|V||U|)$ 即 $O(|S||V|+|V|2^{|V|})$ 时间复杂度的做法，可以通过本题。

另附：[提交记录](https://www.luogu.com.cn/record/76697804)，想要完整代码可以找我。

---

