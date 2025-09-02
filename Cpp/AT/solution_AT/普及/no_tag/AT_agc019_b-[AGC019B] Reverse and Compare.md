# [AGC019B] Reverse and Compare

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc019/tasks/agc019_b

英小文字からなる文字列 $ A\ =\ A_1\ A_2\ ...\ A_n $ があります。

あなたは $ 1\ \leq\ i\ \leq\ j\ \leq\ n $ であるような任意の二つの添字 $ i,\ j $ を選び、$ A $ のうち部分文字列 $ A_i\ A_{i+1}\ ...\ A_j $ を反転することができます。

この操作は一回まで行うことができます。

これによって得られる文字列は何通りあるでしょうか？

## 说明/提示

### 制約

- $ 1\ \leq\ |A|\ \leq\ 200,000 $
- $ A $ は英小文字からなる。

### Sample Explanation 1

得られる文字列は `aatt`（何もしない）、`atat`（$ A[2..3] $ を反転）、`atta`（$ A[2..4] $ を反転）、`ttaa`（$ A[1..4] $ を反転）、`taat`（$ A[1..3] $ を反転）です。

### Sample Explanation 2

どの部分文字列を反転しても、結果は `xxxxxxxxxx` です。

## 样例 #1

### 输入

```
aatt```

### 输出

```
5```

## 样例 #2

### 输入

```
xxxxxxxxxx```

### 输出

```
1```

## 样例 #3

### 输入

```
abracadabra```

### 输出

```
44```

# 题解

## 作者：Autream (赞：3)

#### 题意简述

给定一个字符串 $A$，你可以选择任意一个连续区间 $[l,r]$，并将其翻转一次，求能够组合出多少种不同的字符串。

---

#### 题目分析

~~小学数学题嘛这不是~~依次考虑区间的长度，把每个长度的答案累加起来（其实就是[加法原理](https://oi-wiki.org/math/combinatorics/combination/)），然后减去不合法方案就行。

如何找到不合法方案呢？

举个例子，对于字符串 $A=\texttt{abtaca}$，我们可以发现，翻转区间 $[2,3]$ 和 $[1,4]$，$[4,6]$ 和 $[5,5]$，$[1,6]$ 和 $[2,5]$ 得到的字符串是一样的。

即：对于任意整数 $l,r \in [1,|A|]$，如果 $A_l=A_r$，那么翻转 $[l,r]$ 和翻转 $[l+1,r-1]$ 是一样的，如果有 $x$ 个字符 $c$，那么 $c$ 对不合法答案的贡献就是考虑两个 $c$ 的位置，把每个位置的答案累加起来（还是加法原理）。

遍历统计即可。

---

#### AC Code

```cpp
#include<bits/stdc++.h>
#define arrout(a,n) rep(i,1,n)std::cout<<a[i]<<" "
#define arrin(a,n) rep(i,1,n)std::cin>>a[i]
#define rep(i,x,n) for(int i=x;i<=n;i++)
#define dep(i,x,n) for(int i=x;i>=n;i--)
#define erg(i,x) for(int i=head[x];i;i=e[i].nex)
#define dbg(x) std::cout<<#x<<":"<<x<<" "
#define mem(a,x) memset(a,x,sizeof a)
#define all(x) x.begin(),x.end()
#define arrall(a,n) a+1,a+1+n
#define PII std::pair<int,int>
#define m_p std::make_pair
#define u_b upper_bound
#define l_b lower_bound
#define p_b push_back
#define CD const double
#define CI const int
#define int long long
#define il inline
#define ss second
#define ff first
#define itn int
CI N=1e5+5;
std::string s;
int n,ans,cnt,a[30];
signed main() {
    std::cin>>s;
    n=s.size();
    ans=(1+n-1)*(n-1)/2+1;
    rep(i,0,n-1){
        a[s[i]]++;
    }
    rep(i,'a','z'){
        cnt+=a[i]*(a[i]-1)/2;
    }
    std::cout<<ans-cnt;
    return 0;
}
```

---

## 作者：gi_A (赞：3)

假设翻转 $[i,j]$ 和 $[i',j']$ 得到的串相等，那么有以下几种情况：

1. 包含关系：

![](https://cdn.luogu.com.cn/upload/image_hosting/fs8qql89.png)

- 两段红色部分一定是“回文的”（$s_i=s_j,s_{i+1}=s_{j-1}...s_{i'-1}=s_{j'+1}$）。若 $[i',j']$ 不在 $[i,j]$ 的中央，则子串 $s[i,j]$ 和 $s[i',j']$ 都是回文串且**翻转后都与原串相等**。

2. 相交但不包含：

![](https://cdn.luogu.com.cn/upload/image_hosting/bp87m8fc.png)

- 可以由“翻转后相等”这一条件最终推出子串 $s[i,j]$ 和 $[i',j']$ 都是回文串，且**翻转后都与原串相等**。

3. 不相交：

- 容易想到，这与第 $2$ 种情况结果一样。

由此，我们已经可以发现，翻转后是一个新串需要的条件：$s_i$ $\not=$ $ s_j$。（没有算原串。）

补充说明：虽然在第 $1$ 种情况中，选择较大的一个翻转区间（翻转区间 $[i,j]$ 比 $[i',j']$ 大）也是一个新串，但选择小的可以同时去掉后两种情况，更方便。

核心代码：

```cpp
int main()
{
	cin>>s;n=strlen(s);
	for(int i=0;i<n;i++){
		a[s[i]-'a']++;//a:每个字母出现次数
		b[i]=a[s[i]-'a'];//b[i]:1~i中字母si出现的次数
	}
	for(int i=0;i<n;i++)
		ans+=n-i-1-(a[s[i]-'a']-b[i]);//在i之后与si不同字符的个数 
	ans++;//原串
  	cout<<ans;
	return 0;
}
```

---

## 作者：GIFBMP (赞：1)

前言：上周学校模拟赛考了这题，然后我当时脑子不知道出了什么毛病，先是没看出 T1 是个斯特林数板子，再是没想出这题，导致白送的 200pts 一分没拿到，喜提垫底。然后我今天回来看了一下这题，秒掉了……不由得感慨我怎么连黄题都做不出来了。

考虑什么样的两次操作会产生同样的结果。假设这次操作翻转的区间是 $[i,j]$，如果 $s_i=s_j$，那么翻转 $[i+1,j-1]$ 也会达到同样的效果。
因此我们只需要统计所有满足 $s_i\ne s_j$ 的区间数量即可。

时间复杂度 $\Theta(|S|)$。

Code:
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std ;
const int MAXN = 2e5 + 10 ;
int n , t[30] ;
char s[MAXN] ;
typedef long long ll ;
ll ans ;
int main () {
	scanf ("%s" , s + 1) , n = strlen (s + 1) ;
	for (int i = 1 ; i <= n ; i++) t[s[i] - 'a']++ ;
	ans = (ll)n * (n - 1) / 2 + 1 ;
	for (int i = 0 ; i < 26 ; i++) ans -= (ll)t[i] * (t[i] - 1) / 2 ;
	printf ("%lld\n" , ans) ;
	return 0 ;
}
```

---

## 作者：run_away (赞：0)

## 题意


给定一个长度为 $n$ 小写英文字母组成的字符串 $s$。可以任意选定 $1\le x\le y\le n$，把 $s_x$ 到 $s_y$ 之间的字符翻转。求最终不同字符串的方案数。


## 分析


我们先考虑所有字符都不同的情况。


小学奥数的加法原理告诉我们，每一位都不同的字符串，对于第 $i$ 位，可以增加 $i-1$ 种翻转方案。


再考虑加入相同的情况。


如 $s=\texttt{abca}$，若翻转 $[1,4]$，和翻转 $[2,3]$ 等效。同理，每一组相同字符都要给答案减一。


用一个桶记录每种字母出现次数，总时间复杂度 $O(|s|)$。


## Code


```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
inline ll read(){ll x=0,f=1;char c=getchar();while(c<48||c>57){if(c==45)f=0;c=getchar();}while(c>47&&c<58)x=(x<<3)+(x<<1)+(c^48),c=getchar();return f?x:-x;}
string s;
ll n,sum[200],ans=1;
signed main(){
    cin>>s;
    n=s.size();
    for(ll i=0;i<n;++i){
        ++sum[s[i]];
        ans+=i+1-sum[s[i]];
    }
    printf("%lld",ans);
}
```

---

## 作者：So_noSlack (赞：0)

[洛谷链接](https://www.luogu.com.cn/problem/AT_agc019_b)&[Atcoder 链接](https://www.luogu.com.cn/remoteJudgeRedirect/atcoder/agc019_b)。

## 题目简述

给定一个字符串 $A$，可以选择**区间** $[i,j]$ 翻转一次，求能得到多少**本质不同**的字符串。（$A$ 的长度不超过 $2 \times 10^5$）。

## 思路

首先解释**本质不同**的含义，即**不完全相等的两个字符串**（可能 $A$ 是 $B$ 的字串）。

如果想直接求得答案显然是不现实的（虽然可求）。那么可以想到正难则反，既然求**本质不同**的字符串难求，则可求总方案数和**本质相同**的方案数并相减即可。

可以发现，如 $str_{i -  1} = str_{j + 1}$，则区间 $[str_i,str_j]$ 与区间 $[str_{i - 1},str_{j + 1}]$ 的字串**本质相同**，故只能算一种方案。

总方案数为 $\frac{n \times (n - 1)}{2}$，其中 $n$ 为字符串 $A$ 的长度，其次**本质相同**的方案数即为每种字母中选两个的方案数**总和**，具体体现为 $\sum {\frac{a_i \times (a_i - 1)}{2}}$。

下面是代码实现：

```cpp
#include<iostream>
#include<cstring>
using namespace std;

long long num[30]; // 记得开 long long!
string str;

int main() {
	cin >> str;
	long long n = str.size();
	for(int i = 0; i < n; i ++) num[int(str[i] - 'a')] ++; // 预处理字母个数。
	long long ans = n * (n - 1) / 2; // 总方案数。
	for(int i = 0; i < 26; i ++) ans -= num[i] * (num[i] - 1) / 2; // 减去本质相同的方案数。
	cout << ans + 1 << endl; // 要加上本身！
	return 0;
}
```

因为洛谷提交不了，所以放上官网的提交记录：

![](https://cdn.luogu.com.cn/upload/image_hosting/shkdqmqc.png)

$$\texttt{The End!}$$

---

## 作者：Miyamizu_Mitsuha (赞：0)

我们可以观察到以下几个性质：

+ 如果字符串 $A$ 中存在两个不相邻的相同字符（即 $A[i]=A[j]$，且 $|i-j|>1$），那么不管如何翻转区间 $[i,j]$，得到的字符串都是相同的。
+ 对于字符串 $A$ 中的任意字符 $A[i]$，只要存在一个不相邻的相同字符 $A[j]$（即 $A[i]=A[j]$，且 $|i-j|>1$），那么不管如何翻转区间 $[i,j]$，得到的字符串都是相同的。

根据上述性质，可以得出结论：只有当字符串 $A$ 中不存在两个不相邻的相同字符时，通过翻转操作才能得到不同的字符串。因此，只需计算字符串 $A$ 中不相邻的相同字符的数量。

RMJ 坏了，代码不敢放，等好了再补。

---

## 作者：wangyibo201026 (赞：0)

## 题意

给你一个字符串，要求你可以翻转**一**次，请问能翻转出多少不同的字符串。

## 思路

考虑本质相同的字符串如何得到。

如果此时 $s_i = s_j$，那么 $s_{i + 1}$ 和 $s_{j - 1}$ 翻转一次肯定是本质相同的。那 $s_{i - 1}$ 和 $s_{j + 1}$ 翻转呢？显然在**所有**是不同的（如果是回文的那么肯定会再接下来的计算中算贡献）。

如果此时 $s_i \ne s_j$，考虑此时的贡献无非就是 $s_{i - 1}$ 和 $s_{j + 1}$ 翻转的贡献，而这个贡献已经被算过了，所以就没了，至于里面的区间翻转，这种上面已经说明过了。

所以答案就是所有区间数量减去两边相同的区间数量。记得答案最后要加 $1$，原本字符串也算。

---

## 作者：Endt (赞：0)

# Reserve and Compare-题解

### 转化

有一句废话：对于一个翻转操作，如果它进行之后的字符串不是重复的，那么这个字符串就是不一样的。

所以只需要用总方案数减去翻转后一样的方案数就行啦。

### 实现

总方案数：$|s|\cdot (|s|-1)+1$。加一是因为原串也是一个串。

不同的方案数：记录某字符出现的次数，从中选取两个组合，因为可以只翻转它们中间的字符，它们翻转得到的串是重复的。

### 代码

```
#include<bits/stdc++.h>

long long t[300];
char s[200005];long long lens;
long long ans;
int main(){
    scanf("%s",s);lens=strlen(s);
    for(int i=0;i<lens;++i){
        ++t[(int)s[i]];
    }
    
    ans=lens*(lens-1)/2+1;
    for(char i='a';i<='z';++i){
        ans-=t[(int)i]*(t[(int)i]-1)/2;
    }
    printf("%lld",ans);
    
    return 0;
}
```

---

## 作者：atarashiTLE (赞：0)

### 题意简述：
题意翻译
给定一个字符串 $A$，可以选择区间 $[i,j]$ 翻转一次，求能得到多少本质不同的字符串。

|$A|\leq 2\times 10^5$。

----
### 思路：
统计$a_i=a_j$的个数求出不合法的方案数，再从总方案数中减去它从而得到合法方案数。为什么要这样[gi_A的题解](https://www.luogu.com.cn/blog/Lixwe/solution-at2701)中已经说得很清楚了。

这里提供一种使用STL的`map`的标程。
code:
```cpp
#include <iostream>
#include <map>
#define int long long
using namespace std;
map<char, int> m;
int ans, len;
signed main()
{
	char c;
	while ((c = getchar()) && c != '\n')
		m[c]++, len++;
	ans = len * (len - 1) / 2;
	for (int i = 0; i < 256; i++)
		if (m.count(i))
			ans -= m[i] * (m[i] - 1) / 2;
	cout << ans + 1 << endl;
	return 0;
}
```

---

## 作者：铃宕 (赞：0)

如果 **$s[i]$==$s[j]$** 那么交换后的序列一定和 ($s[i+1]$,$s[j-1]$) 一样

只需统计$s[i]$==$s[j]$的个数即可，这里通过记录字符出现的个数的方法实现

总方案数减不合法的方案数就是合法方案数

注意方案数最后要加 $1$，字符串可以不翻转

```cpp
#include<bits/stdc++.h>
using namespace std;
char s[200020];
long long l,id[200020],cnt[200020],tot,ans,f[200020];//不开long long见祖宗
int main(){
	scanf("%s",s+1);
	l=strlen(s+1);//输入
	for(int i=1;i<=l;i++){//统计没种字符出现的个数
		if(f[s[i]]) cnt[id[s[i]]]++;//如果以前出现过，个数++
		else{
			f[s[i]]=1;//以前没出现过，记录
			tot++;
			id[s[i]]=tot;
			cnt[tot]++;
		}
	}
	ans=l*(l-1)/2;//总方案数
	for(int i=1;i<=tot;i++){
		ans-=cnt[i]*(cnt[i]-1)/2;//减不合法方案数
	}
	printf("%lld",ans+1);
}
```


---

## 作者：zxh923 (赞：0)

# AT_agc019_b [AGC019B] Reverse and Compare 题解

[题目传送门](https://www.luogu.com.cn/problem/AT_agc019_b)

### 思路

这道题一开始看其实会觉得有点晕，这是因为很难理解出怎样翻转才能产生新的字符串。

所以我们可以考虑正难则反，考虑什么情况下翻转是没有用的。

我们可以发现，如果 $s[i]$ 与 $s[j]$ 相等的话，这次翻转就是无用功。

为什么呢？因为这种方法与翻转 $i+1$ 到 $j-1$ 的区间是没有任何差别的。

比如这个字符串为 $\texttt {abca}$。

我们翻转区间 $1$ 至 $4$ 和翻转区间 $2$ 至 $3$ 是一样的，所以结论成立，我们需要把这种情况减掉。

所以我们只需要统计，对于每一个字母，有多少种方案会做无用功。

首先，所有方案即选择一个字母后再从剩下的字母中选一个，为 $\frac {len^2-len}2$。

我们就可以用这个公式计算每个字母重复的情况，最后减掉即可。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
string s;
int len,cnt[30],ans;
signed main(){
	cin>>s;
	len=s.size();
	for(int i=0;i<len;i++){
		cnt[(int)(s[i]-'a')]++;
	}ans=len*(len-1)/2;//所有方案
	for(int i=0;i<26;i++){
		ans-=cnt[i]*(cnt[i]-1)/2;//扣掉不合法方案
	}cout<<ans+1<<'\n';//加上原字符串
	return 0;
}
```


---

