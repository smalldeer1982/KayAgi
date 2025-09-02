# Palindromes Coloring

## 题目描述

You have a string $ s $ consisting of lowercase Latin alphabet letters.

You can color some letters in colors from $ 1 $ to $ k $ . It is not necessary to paint all the letters. But for each color, there must be a letter painted in that color.

Then you can swap any two symbols painted in the same color as many times as you want.

After that, $ k $ strings will be created, $ i $ -th of them will contain all the characters colored in the color $ i $ , written in the order of their sequence in the string $ s $ .

Your task is to color the characters of the string so that all the resulting $ k $ strings are palindromes, and the length of the shortest of these $ k $ strings is as large as possible.

Read the note for the first test case of the example if you need a clarification.

Recall that a string is a palindrome if it reads the same way both from left to right and from right to left. For example, the strings abacaba, cccc, z and dxd are palindromes, but the strings abab and aaabaa — are not.

## 说明/提示

- In the first test case, $ s $ ="bxyaxzay", $ k=2 $ . We use indices in the string from $ 1 $ to $ 8 $ . The following coloring will work: $ \mathtt{\mathbf{\color{red}{b}\color{blue}{xy}\color{red}{a}\color{blue}{x}z\color{red}{a}\color{blue}{y}}} $ (the letter z remained uncolored). After painting:
  - swap two red characters (with the indices $ 1 $ and $ 4 $ ), we get $ \mathtt{\mathbf{\color{red}{a}\color{blue}{xy}\color{red}{b}\color{blue}{x}z\color{red}{a}\color{blue}{y}}} $ ;
  - swap two blue characters (with the indices $ 5 $ and $ 8 $ ), we get $ \mathtt{\mathbf{\color{red}{a}\color{blue}{xy}\color{red}{b}\color{blue}{y}z\color{red}{a}\color{blue}{x}}} $ .
  
  Now, for each of the two colors we write out the corresponding characters from left to right, we get two strings $ \mathtt{\mathbf{\color{red}{aba}}} $ and $ \mathtt{\mathbf{\color{blue}{xyyx}}} $ . Both of them are palindromes, the length of the shortest is $ 3 $ . It can be shown that the greatest length of the shortest palindrome cannot be achieved.
- In the second set of input data, the following coloring is suitable: $ [1, 1, 2, 2, 3, 3] $ . There is no need to swap characters. Both received strings are equal to aa, they are palindromes and their length is $ 2 $ .
- In the third set of input data, you can color any character and take it into a string.
- In the fourth set of input data, you can color the $ i $ th character in the color $ i $ .
- In the fifth set of input data can be colored in each of the colors of one character.
- In the sixth set of input data, the following coloring is suitable: $ [1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 0] $ . Rearrange the characters so as to get the palindromes abcba and acbca.

## 样例 #1

### 输入

```
10
8 2
bxyaxzay
6 3
aaaaaa
6 1
abcdef
6 6
abcdef
3 2
dxd
11 2
abcabcabcac
6 6
sipkic
7 2
eatoohd
3 1
llw
6 2
bfvfbv```

### 输出

```
3
2
1
1
1
5
1
1
3
3```

# 题解

## 作者：EC75 (赞：6)

这道题非常简单。我觉得它应该贴上“入门”标签。

## 思路

首先，我们将尝试将相同的字符对添加到回文中。只要至少有  $k$ 对字符，我们就可以添加它们。之后就不能再添加几个字符了，但是可以尝试在中间添加一个字符。如果至少还有 $k$ 对字符，则可以无需绘制其他的。

## 代码
```python
t = int(input())
while t > 0:
    cnt = [0] * 26
    pairs = single = 0
    n, k = map(int, input().split())
    s = input()
    for i in range(n):
        cnt[ord(s[i]) - 97] += 1
    for i in range(26):
        pairs += cnt[i] // 2
        single += cnt[i] % 2
    print(2 * (pairs // k) + (single + 2 * (pairs % k) >= k))
    t -= 1
```
最后再说一句，这种类型的题最好用 pypy3 提交，否则可能会 TLE 。

---

## 作者：AFewSuns (赞：4)

**CF764 Div.3（VP） 做题记录**

- A. plus One on the Subset

- B. Make AP

- C. Division by Two and Permutation

- $\color{red}\texttt{D. Palindromes Coloring}$

- E. Masha-forgetful

- F. Interacdive Problem

- G. MinOr Tree

### 题目大意

$t$ 组询问，给定一个长度为 $n$ 的字符串，可以给其中一些字符染色（可以不染），颜色种类不超过 $k$。然后将同种颜色的字符进行任意交换。

定义一个颜色串为，所有染上此颜色的字符按照 **原串顺序（交换后）** 组成的字符串。

比如原串是 $\color{red}{\texttt{a}}\color{blue}{\texttt{b}}\color{black}{\texttt{c}}\color{blue}{\texttt{d}}\color{red}{\texttt{e}}\color{red}{\texttt{f}}\color{blue}{\texttt{g}}$，现在交换同颜色的 $\color{red}{\texttt{a}}$ 和 $\color{red}{\texttt{e}}$，变成 $\color{red}{\texttt{e}}\color{blue}{\texttt{b}}\color{black}{\texttt{c}}\color{blue}{\texttt{d}}\color{red}{\texttt{a}}\color{red}{\texttt{f}}\color{blue}{\texttt{g}}$，然后红色串是 $\color{red}\texttt{eaf}$，蓝色串是 $\color{blue}\texttt{bdg}$，$\texttt{c}$ 没被染色不用管。

你要使得所有颜色串均为回文串，并且所有颜色串长度的最小值最大。求这个最大值。

$1 \leq t \leq 10^4,1 \leq k \leq n \leq 2 \times 10^5,\sum n \leq 2 \times 10^5$

### 题目分析

看到题目要求最小值最大，可以初步判断要二分。

假设现在颜色串长度的最小值为 $len$，那么所有长度 $>len$ 的颜色串一定可以通过删除某些字符（相当于不染一些字符），变成一个长度为 $len$ 的回文串。

也就是说，我们只需判断是否存在 $k$ 个长度为 $len$ 的回文颜色串即可。

同理，如果颜色串长度为 $len$ 可以，那么 $len-1$ 也可以。这就说明了 $len$ 具有单调性，我们可以愉快地二分了。

回到题目，发现我们可以不限次数地交换同颜色字符。这说明我们可以将颜色串字符的顺序进行任意变换，得到我们想要的颜色串。

所以，我们只需知道同颜色的字符有哪些，就可以快速判断它是否为回文串。统计出每个字符出现的次数，如果它是回文串，要么出现的次数均为偶数（颜色串长度为偶数），要么只有一个奇数（颜色串长度为奇数）。

按照这个思路，开一个桶 $cnt_i$ 记录一下原来整个串中，字符 $i$ 出现了多少次。若 $len$ 为偶数，我们就要为 $k$ 种不同颜色串提供 $\frac{len}{2}$ 对相同字符，总共就是 $k \times \frac{len}{2}$ 对。直接判断 $\displaystyle\sum_{i=1}^{26}\lfloor\frac{cnt_i}{2}\rfloor$ 是否大于等于 $k \times \frac{len}{2}$ 即可。

若 $len$ 为奇数，同理，先判断 $\displaystyle\sum_{i=1}^{26}\lfloor\frac{cnt_i}{2}\rfloor$ 是否大于等于 $k \times \lfloor\frac{len}{2}\rfloor$，因为长度为奇数的回文串还有中间一个落单的字符，所以还需判断剩下未使用的字符是否大于等于 $k$。相当于判断 $\displaystyle\sum_{i=1}^{26}cnt_i$ 是否大于等于 $k \times len$。

时间复杂度 $O(26n\log n)$。

### 代码

```cpp
#include<bits/stdc++.h>
#define ll long long 
using namespace std;
ll t,n,k;
char c[200020];
bool ck(ll x){
	ll cnt[27];
	for(ll i=1;i<=26;i++) cnt[i]=0;
	for(ll i=1;i<=n;i++) cnt[c[i]-'a'+1]++;
	ll tmp=x/2,tot=0;//tmp表示需要多少对相同字符 
	for(ll i=1;i<=26;i++) tot+=cnt[i]/2;//计算最多有多少对相同字符 
	if(tot<tmp*k) return 0;//不够直接返回0 
	if(x%2==0) return 1;
	tot=0; 
	for(ll i=1;i<=26;i++) tot+=cnt[i];//长度为奇数时，计算总字符个数 
	return tot>=x*k;
}
int main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld %lld",&n,&k);
		scanf("%s",c+1);
		ll l=1,r=n/k;
		while(l<r){//二分 
			ll mid=(l+r+1)>>1;
			if(ck(mid)) l=mid;
			else r=mid-1;
		}
		printf("%lld\n",l);
	}
}
```

---

## 作者：lalaji2010 (赞：3)

# CF1624D

## 题意

给定一个均由小写字母组成的字符串 $s$，将其中的字母分别染成 $k$ 种颜色（不必全部字母都染色，但是被染色的字母应包含全部 $k$ 种颜色），可以任意调换涂有相同颜色的两个字母，调换的次数不限，并将同样颜色的字母从左到右组成一个字符串，要求总共组成的 $k$ 个均为回文串，并且这些字符串中最短的字符串的长度尽可能大。

## 分析

题目描述的说法叫染色，但通俗地讲，题目进行的操作其实是**分组**。

那么问题就转化成了，将一个字符串分成 $k$ 组（可以有字符被舍弃），组内字符可以任意调换顺序，使得 $k$ 个子串均为回文串且最短的回文串尽可能的长。

思考：怎样能构成回文串呢？

一共分两种情况：

1. 回文串长度为偶数，其中共有 $t$ 种字符且**每种字符均出现偶数次**。

2. 回文串长度为奇数，其中共有 $t$ 种字符且 $t-1$ 种字符出现偶数次，**有且仅有 $1$ 种出现了奇数次**。

所以，一个字符每出现 $2$ 次，就必定可以安放在 $1$ 个回文子串里，那么最终的回文子串想要**最短的最长**，就需要均分这些出现了 $2$ 次及以上的字符。

当然，假如一个字符出现了 $3$ 次，那么我们会让其中的 $2$ 次参与均分。

那剩下的 $1$ 次和其他出现了 $1$ 次的字符呢？

上文提到，假如一个回文串有奇数个字符，那么其中必然有一种字符出现了奇数次。所以，如果在出现了大于等于 $2$ 次的字符分配完后，还剩下 $k$ 个及以上出现了奇数次的字符，那么这些字符中的 $k$ 个又能被统一分配到 $k$ 组长度为偶数的回文子串中，使得它们的长度统一增加 $1$。

那么，出现了奇数次的字符该怎样计算呢？

分为三类：
1. 本身出现了 $1$ 次。

2. 本身出现了 $(2n+1)$次，其中 $2n$ 次已经被统计到偶数次字符中，**剩下 $1$ 次**。

3. 这一种极为特殊。在统计到的偶数次字符种数除以 $k$ 的过程中会有**余数**，假设统计到 $5$ 对字符(即 $5$ 个成对的字符)，分成 $3$ 组，则有 $5 \bmod 3=2$ 即会余下 $2$ 对字符，它们虽然都是成对的字符，但是无法参与平均分配给 $k$ 组这个操作，所以只能当作 $2 \times 2=4$ 个字符，而不是 $2$ 种出现了偶数次的字符。

最后，根据分析进行统计即可。

## AC CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
int q,n,k;
string s;
int t[405];
int main(){
	cin>>q;
	while(q--){
		memset(t,0,sizeof t);//t数组统计字母出现次数
		cin>>n>>k;
		cin>>s;
		for(int i=0;i<n;i++){
			t[s[i]]++;
		}
		long long ans=0,cnt=0;
		for(int i=97;i<=122;i++){
			ans+=t[i]/2;//ans统计一共出现了多少对字符
			cnt+=t[i]%2;//cnt统计无法参与成对字符平均分配给k组的字符个数，此处统计的是出现奇数次的字符有多少个
		}
		long long answer=(ans/k)*2;//对数平均分配给k组再乘2表示每组的字符个数
		cnt+=(ans%k)*2;//统计成对字符平均分配给k组后余下的个数
		if(cnt>=k){//如果无法参与成对字符平均分配给k组的字符多于k个，那么k组都添上一个这样的单独字符
			answer++;
		}
		cout<<answer<<"\n";//输出答案即可
	}
	return 0;
}
```



---

## 作者：Bh_hurter (赞：2)

# CF1624D题解
作者评价：~~水题一道，觉得应该降为橙题，~~ 主要考察回文字符串相关知识点，思维成分较多
## 题目解释
[题目传送门](https://www.luogu.com.cn/problem/CF1624D)  

从给出的长度为 $N$ 的字符串中选出一些字符组成 $k$ 组回文字符串（**注意这 $k$ 组中每一组都不能为空，每组至少1个字符**），求这 $k$ 组字符串中最短的那一组的长度的最大值。

## 题解
### 首先回顾一下回文字符串：  
**定义**：若一个字符串正着读和反着读是一样的，就称其为回文字符串。  

**根据定义不难发现：**  
- 若字符串长度为偶数，则字符串中所有的字符个数一定是偶数。
- 若字符串长度为奇数，则字符串中除去位于字符串中间的那种字符外，所有的字符个数一定是偶数，而字符串中间的那种字符则是奇数。
### 那么如何做呢
我们可以采取主动将字符往 $k$ 组回文字符串中放。  

由于题目求的是这 $k$ 组字符串中最短的那一组的长度的最大值，所以不难想到往 $k$ 组回文字符串中放时要尽可能平均地放。

接下来开始放：  
首先，我们放字符的时候要有一个前提：**不能破坏已有的回文字符串**！ 

而有一种放的情况是一定不会破坏原来回文字符串的，那就是**一次性放两个相同的字符**！把这两个字符放在原来字符串首尾，自然不会影响原来的回文字符串。

- 所以代码第一步来了：  
**先把字符分成单个的一堆和成对的一堆，再把所有的成对的字符一对一平均对放到 $k$ 组字符串中去，此时最短的那一组回文字符串长度为 $\lfloor  \frac N k \rfloor$**。 由于剩下的几对字符目前不会再对答案造成影响，所以把剩余的几对字符拆成单个字符放到那一堆单个字符里。

至于那些单个字符能添加进去吗？  
回文字符串中间位置是可以出现单个字符的，所以可以把单个字符放到回文字符串中间，但只能放一次。  

- 所以代码第二步来了：  
**看看剩下的单个字符够不够 $k$ 个，如果够就答案+1，否则答案不动**。

最后输出答案。 
## AC Code

```cpp
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
#define ll long long
const int N = 2e5;
int t[30];
int main() {
    int T;
    cin >> T;
    while(T--) {
    	memset(t,0,sizeof t);
        int n,k,ans=0;
        string s;
        scanf("%d%d",&n,&k);
        cin>>s;
        int cntcouple=0,rest=0;
        for(int i=0;i<s.size();i++){
        	t[s[i]-96]++;
		}
		for(int i=1;i<=26;i++){
			cntcouple+=t[i]/2;
			rest+=t[i]%2;
		}
		ans+=2*(cntcouple/k);
		rest+=2*(cntcouple%k);
		if(rest>=k) ans++;
		cout<<ans<<endl;
    }
}
```

---

## 作者：BHDwuyulun (赞：0)

### 1 题目描述
将给出的长度为 $N$ 字符串划分成 $K$ 组，使每组字符串均为回文串，且这 $K$ 组字符串中最短的字符串尽可能长。
### 2 大体思路
输入的串可以分为一个单独的字符和成对的字符，例如字符串 abzhzb 可以分为字符``h``、``a``和成对的``bb``、``zz``。
所以就可以统计字符串中成对的字符的数量和成单的字符的数量，最后计算即可。
### 3 AC代码
```cpp
#include<bits/stdc++.h>
#define ll long long
#define bug printf("---OK---")
#define pa printf("A: ")
#define pr printf("\n")
#define pi acos(-1.0)
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
ll t,n,k;
ll a[200];
int main(){
	cin>>t;
	while(t--){
		string s;
		cin>>n>>k>>s;
		memset(a,0,sizeof a);
		ll even=0,odd=0;
		for(int i=0;i<s.size();i++){
			a[s[i]]++;
		}
		for(int i='a';i<='z';i++){
			even+=a[i]/2;
			odd+=a[i]%2;
		}
		ll sum=even/k*2;
		odd+=2*(even%k);
		if(odd>=k){
			sum++;
		}
		cout<<sum;pr;
	}
	return 0;
}
```

---

## 作者：BVVD_FM (赞：0)

# Description

有 $k$ 种颜色，给一个由小写字母组成的字符串 $s$ 染色，每个字母可以染第 $i(1 \le i \le k)$ 种颜色或者不染色。

染出的颜色为 $i(1 \le i \le k)$ 字符串将包含所有颜色为 $i$ 的字符，这个字符串需要构成一个回文串。

问这 $k$ 个字符串中最短的一个字符串的长度最大为多少。

# Solution

回文串可以分为一个单独的字母和任意个成对的字符，例如字符串 ```abzhzba``` 可以分为字符 ```h``` 和成对的 ```aa```，```bb```，```zz```。

所以可以统计 $s$ 中成对的字符的数量，成单的字符的数量，最后一遍计算就行。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,vis[30];
int cnt,cnt1,two,one;
bool cmp(int a,int b){
	return a>b;
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	int t;string a;
	cin>>t;
	while(t--){
		cin>>n>>k>>a;
		two=0,one=0;//two是成对字符的数量，one是成单字符的数量。 
		memset(vis,0,sizeof vis);
		for(int i=0;i<n;i++)vis[a[i]-97]++;//记录每一种字符出现的次数 
		for(int i=0;i<26;i++){
			two+=vis[i]/2;//统计成对字符的数量 
			one+=vis[i]%2;//统计成单字符的数量 
		}
		int every=2*(two/k);//这two对字符分到每个字符串中的数量（可能会剩下几对） 
		int f=0;
		if((two%k)*2+one>=k)f++;
		//若剩下的成对字符的数量加上成单字符的数量大于等于k,说明每个字符串都可以分到一个成单字符 
		cout<<every+f<<endl;
	}
	return 0;
}
```

---

