# Correcting Mistakes

## 题目描述

Analyzing the mistakes people make while typing search queries is a complex and an interesting work. As there is no guaranteed way to determine what the user originally meant by typing some query, we have to use different sorts of heuristics.

Polycarp needed to write a code that could, given two words, check whether they could have been obtained from the same word as a result of typos. Polycarpus suggested that the most common typo is skipping exactly one letter as you type a word.

Implement a program that can, given two distinct words $ S $ and $ T $ of the same length $ n $ determine how many words $ W $ of length $ n+1 $ are there with such property that you can transform $ W $ into both $ S $ , and $ T $ by deleting exactly one character. Words $ S $ and $ T $ consist of lowercase English letters. Word $ W $ also should consist of lowercase English letters.

## 说明/提示

In the first sample test the two given words could be obtained only from word "treading" (the deleted letters are marked in bold).

In the second sample test the two given words couldn't be obtained from the same word by removing one letter.

In the third sample test the two given words could be obtained from either word "tory" or word "troy".

## 样例 #1

### 输入

```
7
reading
trading
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5
sweet
sheep
```

### 输出

```
0
```

## 样例 #3

### 输入

```
3
toy
try
```

### 输出

```
2
```

# 题解

## 作者：CarrotMeow (赞：1)

正难则反。可以理解为，在 $s, t$ 中各添加一个字符使得二者相等。由于题目保证 $s \neq t$，显然最多只有 $2$ 种不同的 $w$。

所有 $s_i = t_i$ 的位置不用处理，找出 $s_{l \ldots r} \neq t_{l \ldots r}$ 的最长区间 $[l, r]$。

具体地，举出两个例子。

$$
\begin{aligned}
\texttt{aaaab} \\
\texttt{caaaa}
\end{aligned}
$$

在区间 $[l, r)$ 内，$s_i$ 对应 $t_{i + 1}$，所以可以在 $s, t$ 两端各添加一个字符以匹配对方。$w$ 可以取 $\texttt{caaaab}$。反之，若有 $s_i \neq t_{i + 1}$，则无法使用这种办法构造出 $w$。

$$
\begin{aligned}
\texttt{baaaa} \\
\texttt{aaaac}
\end{aligned}
$$

同理，在区间 $[l, r)$ 内，$s_{i + 1}$ 对应 $t_i$，同样可以构造出 $w = \texttt{baaaac}$。反之，若有不匹配的位置，则无法用该办法构造。

在实现代码时，找出区间 $[l, r]$ 并判断 $[l, r)$ 中是否有 $s_i \neq t_{i + 1}$ 或 $s_{i + 1} \neq t_i$ 的情况，如果有，其构造方法就无法构造出 $w$。

可参考 [代码](https://codeforces.com/contest/533/submission/269362179) 理解。

---

## 作者：skyskyCCC (赞：1)

## 前言。
题意简述：给定两个长度为 $n$ 的字符串，这两个字符串都是在另一个原字符串的基础上减去一个字母得到的，问原字符串有几种可能性。

这个题换种说法，就可以这么认为：在字符串中添加字母，使得两个字符串一致。问可能的方案数。这么看，就可以用添加的操作代替删除了。
## 分析。
显然，如果两个字符串都可以通过一个字符串转换，那么这两个字符串必定存在一个或者两个的不同之处。我们不难想到，我们要删除，那么必须找到位置。我们知道，因为只删除一个字母，那么一定存在子串是相同的，所以我们不妨将这两个字符串的两端相同的子串删除掉，只留下有区别的地方。既然这里有区别，那么必定在它的附近发生了更改。同时，因为删除的位置不同，我们也可以得到，我们保留下来的这一部分的子串（中间的部分）的两端的字母一定不相同。那么如果我们想让它们匹配起来，必须在这个保留下来的子串的两端添加。因为添加在中间，对于两端是否能够匹配没有联系，而中间部分可能只好一一对应。

这样，保留的子串的两端都可以操作，所以答案最多只有两种。如下：一种是在第一个子串的第一个字符前添加一个，第二个子串最后一个字符后添加一个。另一个是在第一个子串的第一个字符的后面添加一个，第二个子串最后一个字符前面添加一个。具体的例子：
- 删除两端的重复子串。
```
(rea)ding(imey)
(rea)ingt(imey)
```
- 添加字符。

我们发现，保留下来的都有 ```ing``` 这个子串，事实上，我们可以推广到任意一个情况，就是如果存在方案，就有前面的一个字符和后面的一个字符不同，我们只需要把它们补上即可。于是可以：
```
ding(t)
(d)ingt
```
此时可以得到答案（可以证明没有第二个）：
```
rea(d)ing(t)imey
```
总结一下，我们直接对这两种方法进行尝试，交换首尾的字符，可以相同的作为答案即可。

代码如下，仅供参考：
```
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
int n;
string s1,s2;
int l=0x3f3f3f3f,r=-0x3f3f3f3f;
int ans1=1,ans2=1;//最多只有两种情况。
bool flag,pd; 
int main(){
    cin>>n>>s1>>s2;
    for (int i=0;i<n;i++){
        if(s1[i]!=s2[i]){
            l=min(l,i);
            r=max(r,i);
            //找不同的区间。 
        }
    }
    for (int i=l+1;i<=r;i++){
        if(s1[i]!=s2[i-1]){
        	ans1=0;
        //	if(flag==1){
        //		continue;
		//	}
        //	ans--;
        //	flag=1;
		}
        if(s1[i-1]!=s2[i]){
        	ans2=0;
        //	if(pd==1){
        //		continue;
		//	}
		//	ans--;
		//	pd=1;
        }
    }
    cout<<ans1+ans2<<"\n";
    return 0 ;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：_Winham_ (赞：1)

题目意思：

~~真不懂翻译的人翻译了什么鬼？~~

给定两个字符串 $a$ 和 $b$，这两个字符串都是在原字符串 $c$ 的基础上减去一个字母得到的，请问原字符串有几种可能性。

---

思路：

一开始想到暴力，可是数据范围太大，肯定会爆，所以得找优化方法。

不难发现有解的情况是，两个字符串的最长公共子串是 $n - 1$，或者完全相同。而最多解时，则是两个字符完全相同，而要插进去一个字符，则只用插在字符与字符之间，解得数量为 $n + 1$。

现在排除无解与最多解的情况后，枚举几组样例，能发现只有 $1$ 与 $2$ 的情况。而想要知道 $1$ 和 $2$ 的情况，就得去观察几组样例。经过发现解为 $1$ 的情况的话，两字符串 $a$ 与 $b$，同样的位置不同的字符，则这些字符肯定会与自己的位置其中相差一的字符相同。则解为 $2$ 的情况是两个不同字符的位置上完全相等。

----

上代码：

```cpp

#include<iostream>
#include<string>
#include<cctype>
#include<cmath>
#include<cstdlib>
#include<cstring>
#include<vector>
#include<algorithm>
#include<map>
#include<set>
#include<iomanip>
using namespace std;
#define LL long long
const int N = 1e6+10;
const int INF = 0x3f3f3f3f;
int n,l,r,sum;
string a,b; 
int main(){
	bool f1=false,f2=false;
	//freopen("","r",stdin);
	//freopen("","w",stdout);
	cin>>n>>a>>b;
	if(a==b){
		cout<<n+1<<endl;
		return 0;
	}
	a=" "+a,b=" "+b;//用l,r来缩小枚举的范围
	for(int i=1,j=n;i<=n&&j>=1;i++,j--){
		if(a[i]!=b[i]&&!f1)
			l=i,f1=true;
		if(a[j]!=b[j]&&!f2)
			r=j,f2=true;
		if(f1&&f2)break;
	}	
	int x=1,y=1;
	for(int i=l+1;i<=r;i++){
		if(a[i]!=b[i-1])x=0;
		if(b[i]!=a[i-1])y=0;
	}
//	cout<<l<<" "<<r<<" "<<x<<" "<<y<<endl;
	sum=x+y;
	cout<<sum<<endl; //不用判断0的情况，因为上面的代码判断0也是不成立的。
	return 0;
}
```

---

## 作者：Rt__ (赞：0)

[CF533E Correcting Mistakes](https://www.luogu.com.cn/problem/CF533E)
## 题意简述
给定两个不同的字符串 $s_1$  $s_2$ （长度均为 $n$ ），求有几个长度为 $n + 1$ 的 $s'$，能够删除一个字符，分别变为 $s_1$  $s_2$。
## 思路
刚开始想着从左往右扫，只要碰到 $s_1(i)$ 和 $s_2(i)$ 不相等的，就分为三种情况：
1.  $s_1(i + 1) = s_2(i)$ 
2.  $s_1(i) = s_2(i + 1)$ 
3.  $s_1(i + 1) = s_2(i + 1)$

前两种情况各出现一次，第三种情况不出现答案为 $1$；第三种情况出现一次，前两种情况不出现答案为 $2$，其余的答案为 $0$。但我们可以发现，当出现序列中只有两种字母时，会出现如 :
```
a a a b b b b 
a a a a b b b
1 2 3 4 5 6 7
```

的情况。这样遍历到第四位时，就会发现满足了情况 $2$ 和 $3$，这样我们不知道用哪种情况，所以放弃这种思路。


---


然后我们可以把问题抽象总结出来。原来字符串表示为：
>  $A + x + B + y + C$（$x$ 和 $y$ 为删除的两个字母， $A$，$B$，$C$ 为对应位置字串）

而 $s_1$ 和 $s_2$ 分别可以表示为：
> $s_1 = A + x + B + C$
> 
>
> $s_2 = A + B + y + C$

这样我们分别找到最左边第一个不一样的字母，最右边第一个不一样的字母，分别尝试着对应 $x$ 和 $y$。如果 $x$ 和 $y$ 在同一位置，则答案为 $2$；如果无论怎么对应 $x$ 和 $y$，都不能使两个 $B$ 相同，答案为 $0$；否则答案就为 $1$。

时间复杂度 $O(n)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200010;


signed main(){
	int n;
	cin >> n;
	string s1, s2;
	cin >> s1 >> s2;
	s1 = ' ' + s1;
	s2 = ' ' + s2;
	int fr, ba;
	for(fr = 1; fr <= n; fr ++){
		if(s1[fr] != s2[fr])break;
	}
	for(ba = n; ba >= 1; ba --){
		if(s1[ba] != s2[ba])break;
	}
	int ans = 0;
	if(s1. substr(fr + 1, ba - fr) == s2. substr(fr, ba - fr)){
		ans ++;
	}
	if(s1. substr(fr, ba - fr) == s2. substr(fr + 1, ba - fr)){
		ans ++;
	}
	cout << ans;
	return 0;
}
```

---

