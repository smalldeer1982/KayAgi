# AB-string

## 题目描述

The string $ t_1t_2 \dots t_k $ is good if each letter of this string belongs to at least one palindrome of length greater than 1.

A palindrome is a string that reads the same backward as forward. For example, the strings A, BAB, ABBA, BAABBBAAB are palindromes, but the strings AB, ABBBAA, BBBA are not.

Here are some examples of good strings:

- $ t $ = AABBB (letters $ t_1 $ , $ t_2 $ belong to palindrome $ t_1 \dots t_2 $ and letters $ t_3 $ , $ t_4 $ , $ t_5 $ belong to palindrome $ t_3 \dots t_5 $ );
- $ t $ = ABAA (letters $ t_1 $ , $ t_2 $ , $ t_3 $ belong to palindrome $ t_1 \dots t_3 $ and letter $ t_4 $ belongs to palindrome $ t_3 \dots t_4 $ );
- $ t $ = AAAAA (all letters belong to palindrome $ t_1 \dots t_5 $ );

You are given a string $ s $ of length $ n $ , consisting of only letters A and B.

You have to calculate the number of good substrings of string $ s $ .

## 说明/提示

In the first test case there are six good substrings: $ s_1 \dots s_2 $ , $ s_1 \dots s_4 $ , $ s_1 \dots s_5 $ , $ s_3 \dots s_4 $ , $ s_3 \dots s_5 $ and $ s_4 \dots s_5 $ .

In the second test case there are three good substrings: $ s_1 \dots s_2 $ , $ s_1 \dots s_3 $ and $ s_2 \dots s_3 $ .

## 样例 #1

### 输入

```
5
AABBB
```

### 输出

```
6
```

## 样例 #2

### 输入

```
3
AAA
```

### 输出

```
3
```

## 样例 #3

### 输入

```
7
AAABABB
```

### 输出

```
15
```

# 题解

## 作者：youngk (赞：9)

这个题目要我们计算的是goodstring的个数，我们不妨把答案变成$\frac{n*(n-1)}{2 } - cnt$。其中$cnt$是“badstring”的个数。

首先我们很容易想到两种badstring：$AB$、$BA$。同时显然如果一个字符旁边有相同的字符，如:$AA$、$BB$，呢么这两个字符在一个字符串中已经满足了有回文串的情况，所以如果一个字符串为badstring，呢么问题肯定出在这个字符的相邻两位不同的地方。

首先我们要讨论一个字符串为badstring，必然只有一个$AB$或$BA$的情况，不妨每次讨论两个相邻最近的两个形如$AB$或$BA$的情况，如果两个情况只有三个字符$ABA$、$BAB$等，枚举一下可以发现这本身就是一个回文串，如果大于三个字符，呢么中间间隔的必然都是相同的字符，因为我们现在讨论的相邻最近的情况，实际上就会变成$ABB....BBBA$和$BAA...AAAB$的情况，本身就是一个回文串。呢么如果一个串中出现了多个形如$AB$或$BA$的情况，呢么两两相邻的统计，就可以找到一个回文串覆盖它们。

进而我们再讨论，如果再$AB$、$BA$上扩展，怎样才会让这个位置继续保持为无法组成回文串的形式。首先可以想到不能够在一个字符旁边加上一个不同的字符，形如$ABA$的样子，这样本事就会形成一个回文串，破坏最多只有一个$AB$或$BA$的情况。呢么只能在一个字符旁边一直加相同的字符，形如$AAB$的样子，经过思考一下，其实是可以在一遍无限增加一个相同的字符的，因为这只会让原本字符串中$AB$中一直重复相同的呢个字符有回文串覆盖，另外一个不能被覆盖。因为如果一边增加的字符有更换，就会出现两个$AB$或$BA$的情况不行，如果另一边也增加相同的变量，如$AAABB$，呢么这个$AB$就会被两个完全相同的回文串覆盖。

经过讨论，显然只有以下四种badstring

$ABBBB.....$

$BAAAA.....$

$.....AAAAB$

$.....BBBBA$

呢么再统计下一所有这种串的个数，复杂度是$O(n)$。在实际操作的时候，我们可以认为所有的字符都分在两个不同的badstring的结尾，多余计算的只有最左端和最右段相同的部分以及所有的$AB$或$BA$，再加回来就好了。

代码:

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<set>
#define _USE_MATH_DEFINES
#include<math.h>
#include<queue>
#include<vector>
#include<limits.h>
#include<functional>
#include<stack>
typedef long long ll;
#pragma GCC optimize(2)
using namespace std;
ll n;
string s;
int cnt;
ll a[500000];
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> s;
	for (int i = 0; i < n; i++)
	{
		a[cnt] = 1;
		while (i != n && s[i] == s[i + 1])
		{
			a[cnt]++;
			i++;
		}
		cnt++;
	}
	cout << (n * (n - 1)) / 2 - 2 * n + a[0] + a[cnt - 1] + cnt - 1;
	return 0;
}
```


---

## 作者：叶ID (赞：2)

题目链接：[CF1238D AB-string](https://www.luogu.org/problem/CF1238D)

【广告】[在个人博客食用](https://toxic2018.ml/1887/)风味更佳

****

### 题目描述

一个好的字符串$t$（下标从1开始）满足：对于其中任意一个字符，都属于一个或多个长度大于$1$的回文子串。

回文串是从前向后或从后向前读都一样的字符串。比如A，BAB，ABBA，BAABBBAAB都是回文串，而AB，ABBBAA，BBBA都不是。

下面是好的字符串的例子：

- $t$ = AABBB（其中$t_1$和$t_2$属于子串$t_{1..2}$，$t_3$，$t_4$和$t_5$属于子串$t_{3..5}$）

- $t$ = ABAA（其中$t_1$，$t_2$和$t_3$属于$t_{1..3}$，$t_4$属于子串$t_{3..4}$）

- $t$ = AAAAA（所有字符属于回文子串$t_{1..5}$）

给你一个长度$n$的字符串$s$，请计算其好的子串的数量。

### 输入格式

第一行一个整数$n\ (1 \leq n \leq 3\cdot 10^5)$，表示$s$的长度。

第二行一个仅由字符'A'和'B'构成的字符串$s$。

### 输出格式

一个整数，$s$中好的子串的数量。

### 样例解释

样例1：有$s_{1..2}$，$s_{1..4}$，$s_{1..5}$，$s_{3..4}$，$s_{3..5}$，$s_{4..5}$

样例2：有$s_{1..2}$，$s_{2..3}$，$s_{1..3}$

****

### 解题思路

注意：字符串只由'A'和'B'构成。字符下标从$1$开始。

我们考虑一个字符串中不在两端的字符。容易发现，这个字符一定属于一个长度大于$1$的回文子串。设这个字符为$t_i$

- 如果 $t_{i-1} =\not t_{i+1}$，那么$t_{i-1}$和$t_{i+1}$中必有一个和$t_i$相等。不妨令$t_i = t_{i+1}$，那么$t_i$就属于$t_{i..i+1}$这个回文子串。

- 如果 $t_{i-1} = t_{i+1}$，那么$t_i$属于$t_{i-1..i+1}$这个回文子串。

因此只需考虑两端的字符是否属于一个长度大于$1$的回文子串（换句话说，是否同时有一个回文前缀和回文后缀，前缀和后缀包含本身），就可以判断一个字符串是不是好的了。

接下来我们考虑在字符串$s$上统计。

假设当前考虑的子串从$s_i$开始。那么，可能存在一个字符$s_j$（$j$尽可能小，$j>i$），使得如果当前子串结束点在$s_j$之后，那么这个字符串就有一个回文前缀。

- 如果存在一个$j$，那么定义$next[i] = j$。
- 否则，$next[i] = 0$

很显然，$s_{i..next[i]}$是以$s_i$开头的，最短的回文子串。

相应地，我们定义$prev[]$，使$s_{prev[i]..i}$是$s_i$结尾的，最短的回文子串。很显然：

- 如果存在$j$使$next[j]=i$，那么$prev[i] = j$
- 否则，$prev[i] = 0$

那么如何求$next$数组呢？

由于字符串中只存在'A'和'B'，$next[i]$等于满足$s_j = s_i$和$j>i$的最小$j$。

有了$prev$和$next$之后，我们就可以知道符合要求的子串$s_{x..y}$满足下面的条件：

- $x \leq prev[y]$
- $next[x] \leq y$

于是我们可以用[树状数组1](https://www.luogu.org/problem/P3374)实现统计（树状数组是一种维护序列的$log(n)$数据结构，功能是：单点修改，求前缀和）。细节见代码。

****

```cpp
// status: [Accepted]
// oj:     [luogu]

#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll

const int MAXN = 300002;
// next数组
int nextMatch[MAXN];
// prev数组
int prevMatch[MAXN];
int n;
char s[MAXN];

// 树状数组1
struct WxwAkIoi {
    int data[MAXN];
    static inline int lowbit(int x) {return x&-x;}
    void update(int p,int v) {
        for(int i=p;i<MAXN;i+=lowbit(i)) {
            data[i] += v;
        }
    }
    int query(int p) {
        int ret = 0;
        for(int i=p;i;i-=lowbit(i)) {
            ret += data[i];
        }
        return ret;
    }
}tr;

// 预处理next数组
void pre() {
    int prevA = -1;
    int prevB = -1;
    for(int i=1;i<=n;i++) {
        if(s[i] == 'A') {
            if(prevA != -1) nextMatch[prevA] = i;
            prevA = i;
        }
        else if(s[i] == 'B') {
            if(prevB != -1) nextMatch[prevB] = i;
            prevB = i;
        }
        else {
            cerr<<"DDoSForces AK IOI";
            exit(28403);
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin>>n;
    cin>>(s+1);
    n = strlen(s+1);

    pre();

    // 计算prev数组
    for(int i=1;i<=n;i++) {
        if(nextMatch[i] != 0) {
            prevMatch[nextMatch[i]] = i;
        }
    }

    // 统计
    int ans = 0;
    for(int i=1;i<=n;i++) {
        if(prevMatch[i]) {
            // next[prev[i]] = i，而对于之后的i，有next[prev[i]] < new_i。
            // 这就满足了 next[x] <= y 的性质
            tr.update(prevMatch[i],1);
        }
        // 求树状数组从1到prev[i]的和。
        // 这就满足了 x <= prev[y] 的性质
        ans += tr.query(prevMatch[i]);
    }

    cout<<ans<<endl;
}

```

评测记录：[R25031139](https://www.luogu.org/record/25031139)


---

## 作者：_JF_ (赞：1)

[Link](https://www.luogu.com.cn/problem/CF1238D)

***1900**，思维题吧，不是很困难。

我们不妨去挖掘一下 good 字符串的性质。

先注意到原串只有 `A`，`B` 两种字符。思考某个位置 $i$ 应该怎么被匹配。

首先的，如果有连续数个相同的字符 $t$（数量 $\ge 2$），这些字符显然都能够满足条件。

但是只有一个呢？为了匹配，我们不妨找到距离 $t$ 最近的和 $t$ 相同的字符。

注意到是“最近的”，所以中间字符都相同，那么这些中间字符构成的字符串，显然是回文的。加上 $t$ 以及和 $t$ 相同的最近字符，显然也还是回文。

所以也满足。

如果找不到，说明到最后也没有字符和 $t$ 相同，那就构不成回文。

（同理可以推，你 $t$ 向前匹配也是一样的。）

综合上述两者，所以我们得到结论，如果字符串任意字符 $t$ 在前边或后边，有一个字符和 $t$ 相同，那就合法。

换成判断条件说就是，如果该串某个字符只出现了一次，就不合法。

这个是简单的。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int N =1e6+10;
char s[N];
int n,ans,Fir[N],Lst[N];
signed main(){
	cin>>n,ans=(1+n)*n/2;
	scanf("%s",s+1),ans-=n; 
	int node=0,node1=0;
	for(int i=1;i<=n;i++){
		if(s[i]=='A')	Fir[i]=node,node=i;
		else if(s[i]=='B')	Fir[i]=node1,node1=i;
	}
	node=n+1,node1=n+1;
	for(int i=n;i>=1;i--){
		if(s[i]=='A')	Lst[i]=node,node=i;
		else if(s[i]=='B')	Lst[i]=node1,node1=i;
	}
//	for(int i=1;i<=n;i++){
//		cout<<Fir[i]<<" "<<Lst[i]<<endl;
//	}
	for(int i=1;i<=n;i++){
//		int dus=(Lst[i]-1-(i+1)+1);
		ans-=((i-1-(Fir[i]+1)+1));
		ans-=(Lst[i]-1-(i+1)+1);
	}
	for(int i=1;i<=n;i++){
		if(s[i]=='A'&&s[i+1]=='B')	ans++;
		if(s[i]=='B'&&s[i+1]=='A')	ans++;
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：yangmuguang (赞：1)

### 题意

一个字符串是好串，当且仅当它的每个字符都在该字符串的一个回文子串里。

给定一个字符串 $s\space(1\le|s|\le 3\times10^5)$，只由 `A`、`B` 个字符构成，求它有多少个子串是好串。

### 思路

好串数量不是很好求，所以考虑找坏串。

要是一个字符串是坏串，则它必须有至少一个字符，它的两个相邻的字符都不跟它一样，不然所有的字符都可以与它相同的字符组成回文串，例如 `AA`、`BB`。

但是，它也不能有超过一段连续的 `A`  或 `B`。假设一共有 $3$ 段，形如 `A......AB......BA......A`。若其中一端的 `A` 只有一个，则可以构造回文串 `AB......BA`。若中间的 `B` 只有一个，那可以构造出回文串 。`ABA`若有超过 $3$ 段，可以从两端截去几段，让它成为 $3$ 段后构造回文串。

综上所述，坏串一共只有4种可能性：

`AB......B`

`A......AB`

`BA......A`

`B......BA`

暴力枚举即可。显然，均摊复杂度为 $\Theta (n)$。

### 代码

```
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define faster ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);ios_base::sync_with_stdio(0)
ll n,ans;
char a[300005];
struct _
{
	ll x,y;
	bool operator<(_ ot)const
	{
		return x==ot.x?y<ot.y:x<ot.x;
	}
};
map<_,bool>used;
int main()
{
	faster;
	cin>>n;
	for (ll i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for (ll i=1;i<n;i++)
	{
		for (ll j=i+1;j<=n;j++)
		{
			if (a[j]!=a[i])
			{
				ans++;
				used[{i,j}]=1;
			}
			else break;
		}
	}
	for (ll i=n;i>1;i--)
	{
		for (ll j=i-1;j>=1;j--)
		{
			if (a[j]!=a[i])
			{
				if (!used[{j,i}])ans++;
			}
			else break;
		}
	}
	cout<<n*(n-1)/2-ans;
	return 0;
}
```

##

---

## 作者：cppcppcpp3 (赞：1)

## 题意：

一个好的字符串：一个字符串（本题中仅由字母 A 和 B 构成），它的每一个字符都被这个字符串的至少一个回文的子串所包含。

现在让你求出：题目给出字符串的子串中，有多少个是好的。

## 思路：

这道题我们可以从反面出发，计算不好的子串的数量 $s$。

我们可以发现一个规律：**对于一个不好的字符串，若要使其长度增加，不能在两个相同的字母之间添加任何其它的字母。**

举个例子，ABB，如果在两个 B 中间加若干个 A，则会使原来不在回文子串的字母 A 此时也被回文子串 ABA 包含，并且添加到 A 也都在子串 B...AA...B 中，就不是不好的串了。

又因为所有的不好的串都可以通过 AB 和 BA 在中间加字母得到，所以不好的串只有 ABB...BB、BAA...AA、AA...AAB 和 BB...BBA 四种形式。

那么，怎么统计呢？对于两个相同的字母，如果夹在它们的串，仅由另一种字母构成，则称这个夹在中间的串为一个“块”。

先 $O(n)$ 求出每个位置所在“块”的左右端点。接着，对于非 $1$ 非 $n$ 的位置，如果它与左边字母不同，$s$ 加上左边位置所处“块”的长度，如果与右边字母不同，$s$ 加上右边位置所处“块”的长度。当然，要减去重复统计 AB、BA 的数量。

最后，用总的子串个数减去 $s$ 即可。

## 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+5;
const int inf=1e9+7;

inline int read(){
	int x=0,f=1; char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=x*10+c-48;c=getchar();}
	return x*f;
}

int l[N],r[N],n,ans;
char s[N]; 

main(){
	n=read();scanf("%s",s+1);
	l[1]=1,r[n]=n,ans=n*(n-1)/2; //代码中并没有直接统计不好的子串数量，而是用总数不断减去。
	
	for(int i=2;i<=n;++i){ //求每一位置所在“块”的左右端点。
		if(s[i]==s[i-1]) l[i]=l[i-1];
		else l[i]=i;
	}
	for(int i=n-1;i>=1;--i){
		if(s[i]==s[i+1]) r[i]=r[i+1];
		else r[i]=i;
	}
	
	for(int i=1;i<=n;++i){ //注意对于首尾位置有一点特殊处理，避免出现错误。
		if(i<n && s[i]!=s[i+1]) ans-=(r[i+1]-l[i+1]+1);
		if(i>1 && s[i]!=s[i-1]) ans-=(r[i-1]-l[i-1]+1);
	}
	
	for(int i=1;i<n;++i) if(s[i]!=s[i+1]) ans++; //补上重复减去AB,BA
	return printf("%lld",ans),0;
}
```

---

## 作者：Claire0918 (赞：0)

显而易见，所有子串去掉不是 good 的（称为 bad 的）就是 good 的子串。

bad 的字符串只有以下形式：

+ $\texttt{ABBBB \ldots BBB}$
+ $\texttt{AAAA \ldots AAAB}$
+ $\texttt{BAAAA \ldots AAA}$
+ $\texttt{BBBB \ldots BBBA}$

以上每一种字符串，如果在两侧加上任意字符，都将成为 good 字符串。

设 `l[i]` 为该字符在原串中的连续相同字符子串的左端点，`r[i]` 为右端点。可以 $\mathcal{O}(n)$ 扫描得到。

然后用 `l` 和 `r` 求出 bad 串的数量。

例：要求 $\texttt{ABBBBBB}$ 中 bad 串的数量。

可以枚举右侧端点，得到其中有 $6$ 个 bad 串，分别为 $\texttt{AB}$、$\texttt{ABB}$、$\texttt{ABBB}$、$\texttt{ABBBB}$、$\texttt{ABBBBB}$、$\texttt{ABBBBBB}$。

但原串中如果出现子串 $\texttt{AB}$，会被按 $\texttt{ABBBB \ldots BBB}$ 和 $\texttt{AAAA \ldots AAAB}$ 计算两次，要去掉重复的计算。

长度至少为 $2$ 的子串有 $\frac{n(n - 1)}{2}$ 个。

Code: 
```cpp
#include<bits/stdc++.h>
#define mem(a, v) memset(a, v, sizeof(a));

using namespace std;

const int maxn = 3e5 + 10;

long long n, res;
int l[maxn], r[maxn];
string s;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>s;
	s = " " + s;
	l[1] = 1, r[n] = n, res = n * (n - 1) >> 1;
	for (int i = 2; i <= n; i++){
		if (s[i] == s[i - 1]){
			l[i] = l[i - 1];
		}else{
			l[i] = i;
		}
	} 
	for (int i = n - 1; i; i--){
		if (s[i] == s[i + 1]){
			r[i] = r[i + 1];
		}else{
			r[i] = i;
		}
	}
	for (int i = 1; i <= n; i++){
		if (i > 1 && s[i] != s[i - 1]){
			res -= (r[i - 1] - l[i - 1] + 1);
		}
		if (i < n && s[i] != s[i + 1]){
			res -= (r[i + 1] - l[i + 1] + 1);
		}
	}
	for (int i = 1; i < n; i++){
		if (s[i] != s[i + 1]){
			res++;
		}
	}
	cout<<res;

return 0;
}
```

---

