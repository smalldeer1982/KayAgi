# Period

## 题目描述

对于给定字符串 $S$ 的每个前缀，我们想知道它是否为周期串（周期串定义为由若干最小循环节拼接而成的字符串），若是，输出前缀长度和循环节数量。

## 说明/提示

$n\leq10^6$，字符串 $S$ 均由小写字母构成。

## 样例 #1

### 输入

```
3
aaa
12
aabaabaabaab
0
```

### 输出

```
Test case #1
2 2
3 3

Test case #2
2 2
6 2
9 3
12 4
```

# 题解

## 作者：_louhc (赞：13)

良心画了图！ ~~麻烦点个赞，蟹蟹~~  
[安利博客](https://www.cnblogs.com/louhancheng/p/10135744.html#autoid-2-4-0)
# 写在前面

> Substr(i, j)表示s的子串s[i~j]
>
> 这里s的下标从**1**开始
>
> i的上一个匹配：一个位置j,满足Substr(1, j) == Substr(i - j + 1,N)
>
> 下面黑线表示字符串，其中红框中包含的字符相等（这是自然，同一个字符串嘛）。
>
> ![](https://img2018.cnblogs.com/blog/1431616/201812/1431616-20181218102734586-2122926692.png)
>
> j还要满足
>
> ![](https://img2018.cnblogs.com/blog/1431616/201812/1431616-20181218103344286-2025081922.png)
>
> （注意啦 两条黑线表示同一个字符串，只是位置不同）
>
> （其实这也算是KMP的复习吧。。。）
>
> 下面图中红框中都表示相同

# 算法

KMP。由于这不是KMP学习笔记，不仔细讲，请先学会KMP。

# 思路

这题也可算是“拍大腿”系列了吧？其实你看看下面代码，真的很简单，关键就是如何推出这个结论。

（我不用next，用了f做数组名，希望大家不要看不习惯，意思是一样的）

![](https://img2018.cnblogs.com/blog/1431616/201812/1431616-20181218104051370-846710528.png)

粉色部分也表示相同。这很明显，因为字符是一一对应的嘛(同一个字符串位置相同、长度相同的字符串当然一样)。

由于红框内完全相同，还可以——

![](https://img2018.cnblogs.com/blog/1431616/201812/1431616-20181218104300780-1011214916.png)

继续对应！灰线表示在原字符串中是对应的。

还可以对应！

![](https://img2018.cnblogs.com/blog/1431616/201812/1431616-20181218104619297-427336946.png)

**可能**就会出现这样的情况！(当然可能最前面不够长度)

因此，只要f[i]>0，i前面肯定有循环节！（只不过不知道是否完整，bb|abb|abb|abb这样也看作是）而且循环节长度为i - f[i] + 1！。因此只要判断循环节长度能否将长度整除即可。具体请见代码（真的短）。

# 代码

```cpp
#include<cstdio>
using namespace std;
#define MAXN 1000005

int N, T;
char s[MAXN];
int f[MAXN];

int main(){
	while( ~scanf( "%d", &N ) && N ){
		scanf( "%s", s + 1 ); T++;
		printf( "Test case #%d\n", T );
		int t(0); f[1] = 0;
		for ( int i = 2; i <= N; ++i ){
			while ( s[i] != s[t + 1] && t ) t = f[t];
			if ( s[i] == s[t + 1] ) t++;
			f[i] = t;
			if ( f[i] != 0 && i % ( i -  f[i] ) == 0 ) printf( "%d %d\n", i, i / ( i - f[i] ) );
		}
		putchar('\n');
	}
	return 0;
}
```





---

## 作者：Link_Space (赞：10)

题目大意就是给你一个字符串，让你求出这个字符串的所有前缀中有多少个前缀是由一个不为自己本身的字符串通过循环得到的。

评论区的大佬们大多都是判断$i-next[i]$是否能被$i$整除来判断这个前缀是否为一个不为自己本身的字符串通过循环得到的，但大佬们仿佛都没有太细讲为什么$i-next[i]$能被$i$整除就一定说明这个前缀满足条件，为了方便和我一样的蒟蒻理解，以下给出自认为比较好理解的证明。

![](https://cdn.luogu.com.cn/upload/image_hosting/1bkqltu7.png)

考虑到next数组的含义，图中两个黄色部分一定相同

![](https://cdn.luogu.com.cn/upload/image_hosting/8s9hvw5d.png)

同时可以推得下面的字符串的黄色部分等于上面的字母串的红色部分，同时也等于它右边的红色部分

![](https://cdn.luogu.com.cn/upload/image_hosting/hvp43fnc.png)

不停地推演可以发现图中所有方块部分的字符串都相同，也就是说明这一个前缀是由一个小方块部分的字母串通过循环得到的。

以上是$i-nxt[i]$能够被$i$整除的情况。

接下来我们考虑不能整除的情况

![](https://cdn.luogu.com.cn/upload/image_hosting/rya77i6a.png)

和之前的推演相同，我们可以推出图中两种颜色的小方块都代表同一个字符串。

我们和之前一样继续推演。

![](https://cdn.luogu.com.cn/upload/image_hosting/xgh5d1t9.png)

推到这个时候时，我们就卡住了，没有更多的线索，也就说明我们不能保证这个前缀是由一个字符串循环而成的。

由此得证，所以只需要判断$i-next[i]$是否能被$i$整除即可，以下是代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int N = 1e6 + 5;
char s[N];
int nxt[N];
int main()
{
	int n;
	int T = 0;
	while(scanf("%d",&n)&&n)
	{
		for (int i = 1; i <= n; i++)
			cin >> s[i];
		printf("Test case #%d\n", ++T);
		for (int i = 2, j = 0; i <= n;i++)
		{
			while(j&&s[i]!=s[j+1])
				j = nxt[j];
			if(s[i]==s[j+1])
				j++;
			nxt[i] = j;
			if(j&&!(i%(i-j)))
				printf("%d %d\n", i, i / (i - j));
		}
		puts("");
	}
}
```


---

## 作者：Lucky_Cloud (赞：8)

## 前情提要
本题解重在使大家理解。

本题需要 KMP，相信阅读本篇的大佬都会吧。
 
没学过也没关系，点[这里](https://blog.csdn.net/starstar1992/article/details/54913261)。这是一篇我喜欢的讲解，不喜勿喷。

## 分析
看见本题的第一感就是会与 KMP 中的 $next$ 数组有关。

我们通过下面证明可以得出：满足 $i \bmod len = 0$，且 $S[1 \sim i-len] = S[len+1 \sim i]$ 这样的 $len$ 为循环节，其中 $i$ 为 $S$ 字符串中某个前缀的末尾项。

### 证必要性：

不妨我们先设 $len$ 为字符串 $S[1 \sim i]$ 循环节的长度，我们明显可得：$i \bmod len = 0$，且 $S[1 \sim i-len]=S[len+1 \sim i]$。如：

$S= \texttt{abcabc}$。则 $len=3$，$i=6$。我们可以发现 $i \bmod len=0$。$S[1 \sim i-len]=\texttt{abc}$。$S[len+1 \sim i]=\texttt{abc}$。所以 $S[1 \sim i-len]=S[len+1 \sim i]$。

对于 $S[1 \sim i-len]=S[len+1 \sim i]$ 其实我们也可以这样理解：因为 $S[1 \sim i]$ 是由 $k$ 个长度为 $len$ 的循环元组成，$S[1 \sim i-len]$ 与 $S[len+1 \sim i]$ 均是由 $k - 1$ 个长度为 $len$ 的循环元组成，那么自然可以得出 $S[1 \sim i-len] = S[len+1 \sim i]$。

至于 $i \bmod len = 0$，我相信不用多讲了吧。

### 证充分性：

这里，我们就可以设 $len$ 能整除 $i$ 且 $S[1 \sim i-len] = S[len+1 \sim i]$。自然，我们可以得出**以上两个字符串的长度能整除** $len$。

得出了这个结论我们又可以开始推导：$S[1 \sim len] = S[len + 1 \sim 2 \times len]$，$S[len+1 \sim 2 \times len] = S[2 \times len+1 \sim 3 \times len]$，依次类推，我们可以得出结论 $S[1 \sim i - len]$ 与 $S[len +1 \sim i]$ 均是由 $k$ 个长度为 $len$，也就是 $S[1 \sim len]$ 是 $S[1 \sim i]$ 的循环节。

还是看不懂？

没事看一下图：

![图](https://cdn.luogu.com.cn/upload/image_hosting/abpyiz9a.png)

注：图中 $len=2,i=8$。

解释一下。本图中：

$S[1 \sim len]= \texttt{ab}$。

$S[len + 1 \sim 2 \times len]= \texttt{ab}$。

$S[2 \times len+1 \sim 3 \times len]= \texttt{ab}$。

---

好，回到现在，我们已经证了满足能整除 $i$ 且 $S[1 \sim i-len]=S[len+1 \sim i]$ 的 $len$ 一定是循环结，那这又和 $next$ 数组有什么关系呢？

你们看，这 $S[1 \sim i-len]=S[len+1 \sim i]$ 不就是 $S[1 \sim next_i] = S[i-next_i+1 \sim i]$ 吗？

也就是 $i-len=next_i$。

我们要求**长度最小**的循环节，就需要 $i-len$ 越大！这不就巧了？$next_i$ 刚好符合这样的条件。

那么这道题也就解出来了！

## 回顾过程
1. 求 $next$ 数组。
1. 判断 $i-next$ 是否能整除 $i$。
1. 若步骤 2 成立，那么 $len \gets i-next_i$，否则没有循环节。
1. 重复 2，3。


## 代码
本人马蜂不好，不喜勿喷。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 100;
string s;
int n, nxt[N], num;//其中的nxt也就是上文的next数组。

int main() {
	ios::sync_with_stdio(0);
	while (cin >> n && n) {//重复输入
		cin >> s; s = " " + s;//我习惯从1开始遍历
		nxt[1] = 0;
		for (int i = 2, j = 0; i <= n; i++) {
			while (j > 0 && s[i] != s[j + 1]) j = nxt[j];
			if (s[i] == s[j + 1]) j++;
			nxt[i] = j;
		}//步骤1：求next数组
		cout << "Test case #" << ++num << "\n";
		for (int i = 2; i <= n; i++) {
			if (i % (i - nxt[i]) == 0 && i / (i - nxt[i]) > 1)//步骤2
				cout << i << " " << i / (i - nxt[i]) << endl;//步骤3
		}
		cout << endl;
	}
	return 0;
}
```

## The End
注：部分内容来自 lyd 的[算法竞赛进阶指南](https://book.douban.com/subject/30136932/)，图片自绘。

---

## 作者：Strelitzia (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/UVA1328)

---

前置知识：$\texttt{KMP}$

做这道题前可以先做一下[Power Strings](https://www.luogu.com.cn/problem/UVA10298)，其实这道题就是 $\text{Power Strings}$ 多了一点判读。

我们要深刻理解这个 $\text {pre}$ 这个数组的含义，它也是 $\texttt{KMP}$ 的精髓。

这里要引入一个~~结论~~?

就是长度为 $\operatorname n$ 的字符串，如果 $n \equiv 0 \mod (n -nxt_n)$，那循环节出现的次数就为 $n / (n - nxt_n)$。

具体证明就可以看这篇[博客](https://www.luogu.com.cn/blog/hzz/solution-uva10298)。

代码还有一点小细节，要注意。

```cpp
#include <cmath>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

template<typename T>void read(T &x) {
    T f = 1;x = 0;char s = getchar();
    while(s < '0' || s > '9') {if(s == '-')f = -1;s = getchar();}
    while(s >= '0' && s <= '9') {x = x * 10 + s - '0';s = getchar();}
    x *= f;
}
template<typename T>void print(T x) {
    if(x < 0) putchar('-'),x = -x;
    if(x > 9) print(x / 10);
    putchar(x % 10 + '0');
}

const int maxn = 2000005;

char a[maxn],b[maxn],c[maxn];
int lena,lenb,f[maxn];

int pre[maxn],cnt;

void make_pre(char b[],int lenb) {
	pre[1] = 0;
	int j = 0;
	for (int i = 2 ; i <= lenb ; ++ i) {
		while (j && b[i] != b[j + 1]) j = pre[j];
		if (b[i] == b[j + 1]) j ++;
		pre[i] = j;
	}
}

int main () {
	read(lena);
	int www = 0;
	while (lena) {
		scanf("%s",a + 1);
		make_pre(a,lena);
		printf("Test case #%d\n",++ www);
		for (int i = 2 ; i <= lena ; ++ i) {
			if (i % (i - pre[i]) == 0 && i / (i - pre[i]) > 1) {
				printf("%d %d\n",i,i / (i - pre[i]));
			}
		}
		puts("");
		read(lena);
	}
	return 0;
}
```

---

## 作者：HEIMOFA (赞：2)

分析题目，这道题的难点在于如何判断 $S[1\sim j]$ 是 $S[1\sim i](j<i)$ 的**最小循环节**。

首先有一个很明显的结论——$j$ 能够整除 $i$。

其次有一个不是很明显的结论——当 $j$ 能够整除 $i$ 且 $S[1\sim i-j]=S[j+1\sim i]$ 时，$S[1\sim j]$ 是 $S[1\sim i](j<i)$ 的最小循环节。

> 证明
>
> 因为 $j$ 能够整除 $i$，所以 $j$ 也能够整除 $(i-j)$。
>
> 也就是说 $S[1\sim i-j]$ 和 $S[j+1\sim i]$ 的长度应当都为 $j$ 的倍数。
>
> 那么分别取两个字符串的前 $j$ 项，显然也相等。
>
> 再取后面 $j$ 项，显然还是相等。
>
> 由于是 $j$ 的倍数，所以肯定刚好取完。
>
> 也就是说这两个字符串以 $j$ 为间隔错位相等的。
>
> 那么很明显，最后整个字符串也自然以 $j$ 为循环节展开。

题目要求最小循环节，那么就要让 $S[1\sim i-j]$ 和 $S[j+1\sim i]$ 的长度最长。

这个东西是不是十分眼熟，它就是 KMP 算法中的核心——$next$ 数组。

接下来思路是不是就非常清晰了，求出 $next$ 数组后枚举 $i$，判断是否整除且循环节个数大于 $1$，如果两个都满足的话输出就行了。

```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,t;
const int N=1e6+5;
int nxt[N];
char x[N];

void get(char *s){
	nxt[1]=0;
	int len=strlen(s+1);
	for(int i=2,j=0;i<=len;i++){
		while(j>0&&s[i]!=s[j+1]) j=nxt[j];
		if(s[i]==s[j+1]) j++;
		nxt[i]=j;
	}
}
signed main()
{
	while(scanf("%lld",&n),n){
		scanf("%s",x+1);
		get(x);
		printf("Test case #%lld\n",++t);
		for(int i=2;i<=n;i++){
            //i为前缀的长度
            //(i-nxt[i])为最小循环节的长度
            //i/(i-nxt[i])为最小循环节的个数
			if(i%(i-nxt[i])==0&&i/(i-nxt[i])>1){
				printf("%lld %lld\n",i,i/(i-nxt[i]));
			}
		}
		puts("");
	}
	return 0;
}
```

---

## 作者：0xFF (赞：2)

#### 题目大意


------------
如果一个字符串 $S$ 是由字符串 $T$ 叠加 $K$ 次形成的，那么我们就称 $T$ 是 $S$ 的循环节，同时，使得 $K$ 最大的 $T$ 称为 $S$ 的**最小循环节**，此时的 $K$ 称为是**最大循环次数**。

给定一个 $S$，若其任意前缀的**最大循环次数**大于 $1$，就输出该前缀的长度和最大循环次数。

#### 题目分析


------------
此题似于[UVA10298](https://www.luogu.com.cn/problem/UVA10298)。

注意到题目有关于**循环节**，考虑使用 ```KMP``` 解决此题。

首先引入一个结论：对于任意一个长度为 $n$ 的字符串，其最小循环节长度为 $n - next_n$。其中$next_n$ 可以通过 ```KMP``` 来求解。

结论证明如下：

- 根据定义：$next$ 数组记录的是上一个与当前字符串相同的字符串的位置。
- 如果字符串 $S$ 是由字符串 $T$ 叠加 $K$ 次形成的，那么当前字符串与上一个与其相同的字符串之间的距离即是最小循环节长度，最大循环次数即为**字符串长度** ${\div}$ **最短循环节长度**。
- 综上可以推得当 ```i%(i-nxt[i])==0``` 时,答案为 ```i/(i-nxt[i])```。

#### 代码实现


------------
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdlib>

using namespace std;
const int N = 1000010;


int n,T;
char s[N];
int nxt[N];

int main(){
	while( ~scanf("%d",&n) && n){
		scanf("%s",s+1);
		T++;
		printf("Test case #%d\n",T);
		int j = 0;
		nxt[1] = 0;
		for(int i=2;i<=n;i++){
			while(j && s[j+1] != s[i]){
				j = nxt[j];
			}
			if(s[j+1] == s[i]){
				j ++;
			} 
			nxt[i] = j;
			if(nxt[i] != 0 && i % (i - nxt[i]) == 0) 
				printf("%d %d\n",i,i/(i-nxt[i]));
		}
		printf("\n");
	}
	return 0;
}
```


---

## 作者：_ANIG_ (赞：1)

看题解大部分是 KMP，这里给出一个 ACAM 的做法。

先把这个字符串插到里面，然后求下 $fail$ 数组，遍历每个点，往上跳 $fail$，如果每次跳过的字符个数相同，则有循环节，跳的次数就是答案。

直接统计会 TLE。对于每个点，记录一下它跳 $fail$ 后会越过几个点，查询的时候直接判断 $i-fail_i$ 是否等于 $fail_i$ 的这个值即可，最后除以记录的值就是答案。
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,ccns,p[1000005],f[1000005];
string s;
int main(){
	while(1){
		cin>>n;
		if(n==0)return 0;
		cin>>s;
		printf("Test case #%d\n",++ccns);
		memset(p,0,sizeof(p));
		memset(f,0,sizeof(f));
		p[1]=0,f[1]=1;
		for(int i=2;i<=n;i++){
			if(s[i-1]==s[p[i-1]])p[i]=p[i-1]+1;
			else if(s[0]==s[i-1])p[i]=1;
			else p[i]=0;
			if(!p[i])f[i]=i;
			else if(i-p[i]==f[p[i]])f[i]=f[p[i]];
			else f[i]=i;
			if(f[i])if(i/f[i]>1)printf("%d %d\n",i,i/f[i]);
		}
		printf("\n");
	}
}
```


---

## 作者：让风忽悠你 (赞：1)

[原题](https://www.luogu.com.cn/problem/UVA1328)

## 题意

如果一个字符串 $S$ 是由一个字符串 $T$ 重复 $K$ 次形成的，则称 $T$ 是 $S$ 的循环节。使 $K$ 最大的字符串 $T$ 称为 $S$ 的最小循环节，此时的 $K$ 称为最大循环次数。

现给定一个字符串 $S$，如果它的任意一个**前缀的最大循环次数**大于 1，就输出前缀的长度和最大循环次数。

## 做法

提到字符串的最小循环节，考虑使用 KMP。这里引入一个结论：在 KMP 中，对于任意一个长度为 $n$ 的字符串，其最小循环节长度为 $n-next_n$。解释一下,$next$ 数组记录的是上一个与当前字符串相同的字符串的位置，所以如果字符串 $S$ 是由一个字符串 $T$ 重复 $K$ 次形成的，当前字符串和上一个与其相同的字符串的位置差即为最小循环节的长度。所以，最大循环次数即为 $\text{字符串长度} \div \text{最短循环节长度}$。

## 代码

```cpp
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cstring>
#define N 1000005

using namespace std;

int n,j,T;
int nxt[N];
char s[N];

inline void clear(){
	nxt[1]=nxt[0]=0;
	j=0;
} // 清空，避免影响下一组数据操作 

int main(){
	while(scanf("%d",&n)!=EOF && n){
		scanf(" %s",s+1);
		clear();
		printf("Test case #%d\n",++T);
		for(int i=2;i<=n;++i){
			while(j && s[i]!=s[j+1]) j=nxt[j];
			if(s[i]==s[j+1]) ++j;
			nxt[i]=j;
		} // KMP 基本操作，没啥好说的 
		for(int i=2;i<=n;i++)
			if(nxt[i] && i%(i-nxt[i])==0) // 判断当前前缀是否符合要求 
				printf("%d %d\n",i,i/(i-nxt[i]));
		printf("\n"); // 记得过行 
	}
	return 0;
}
```


---

## 作者：陷语 (赞：1)

### Period

**题目意思：**

给你一个字符串，要你求这个字符串各个前缀的最小循环元，和最大循环次数K

**思路：**

对于每一个字符串， 我们都可以先让它进行自我匹配，求出每一个next[i]，通过题目意思与样例观察，我们可以发现一个前缀要符合题目条件有循环元，那这个前缀的长度一定是大于1的，并且最大循环次数一定也是大于1的，所以我们可以得到以下性质：

**1.当前循环元的长度一定可以整除当前前缀的长度；**

**2.当前循环元的长度整除当前前缀的长度得到的最大循环次数一定是 >= 2的；**

**附上代码：**

```cpp
#include <cstdio>
#include <cstring>

using namespace std;
const int N = 1000100;

int n, cnt;
char c[N];
int nex[N];

int main() {
//	freopen("in.txt", "r", stdin);
	while(~scanf("%d", &n) && n) {
		
		scanf("%s", c + 1);
		nex[1] = 0;
		//对字符串进行自我匹配，即kmp
		 for(int i = 2, j = 0; i <= n; ++i) {
		 	while(j > 0 && c[i] != c[j + 1]) j = nex[j];
		 	if(c[i] == c[j + 1]) ++j;
		 	nex[i] = j;
		 }
		 
		 printf("Test case #%d\n", ++cnt);
		 for(int i = 2; i <= n; ++i) {
		 	if(!(i % (i - nex[i])) && (i / (i - nex[i])) >= 2)
		 		printf("%d %d\n", i, i / (i - nex[i]));
		 }
		 puts("");
	}
	return 0;
}
```


---

## 作者：hovny (赞：1)

## [English题面](https://uva.onlinejudge.org/external/13/p1328.pdf)

### 题意：

给你一个长度为n的字符串，依次取字符串前i个（前缀），如果前缀由k(k>0)个相同[真子串]()构成，那么输出i和k

直到n为0结束，每组数据后要有一行空白

## 思路：

### KMP+一点点判断

其实这道题并不是很难

可以先用**KMP**求出**最长的** 是**s[1~i]**的前缀和后缀的**真子串**的长度**j**

话说的有点复杂，分开来理

#### 1、真子串：

不是字符串本身的子串

#### 2、是**s[1~i]**的前缀和后缀：

以**aabaab**为例

> **aab**aab
>
> aab**aab**
>
> **aab**是aabaab的前缀，又是后缀
>
> j=3

#### 两种条件下：

以aaa为例

就应该是

> **aa**a
>
> a**aa**
>
> **aa**是aaa的前缀&后缀&真子串
>
> j=2

### 判断方法

> if(i%(i-j)==0) //说明循环的子串长度为`i-j`，循环次数为`i/(i-j)`

#### 证明：

![](https://www.cnblogs.com/images/cnblogs_com/hovny/1364959/o_]ZX}_CBJQLSA_1$FNGBS]W5.png)

> RT：
>
> $\because$ l=r
>
> $\therefore$ ①=①，②=②，③=③
>
> $\therefore$ ①=②=③
>
> 其他情况无论多少都可以这样 **连等**，只要i-j能够整除i那么就是成立的

Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int n,t;
int len,cur;
int p[1000010];
int read()
{
	int s=0;
	char c=getchar();
	while(!isdigit(c))
		c=getchar();
	while(isdigit(c))
	{
		s=(s<<1)+(s<<3)+c-'0';
		c=getchar();
	}
	return s;
}
int main()
{
	int i,j;
	n=read();
	while(n)
	{
		printf("Test case #%d\n",++t);
		cin>>s;
		len=s.size();
		for(i=len;i;i--)
			s[i]=s[i-1];
		for(i=2,j=0;i<=len;i++)//KMP大法
		{
			while(j&&s[i]!=s[j+1])//求前缀的那个东东
				j=p[j];
			if(s[i]==s[j+1])
				j++;
			p[i]=j;
			if(j>=(i>>1)&&i%(i-j)==0)//判断一下
				printf("%d %d\n",i,i/(i-j));
		}
		printf("\n");
		n=read();
	}
	return 0;
}
```

### 友情链接

[KMP百度百科](https://baike.baidu.com/item/kmp%E7%AE%97%E6%B3%95/10951804?fr=aladdin)

[【模板】KMP字符串匹配](https://www.luogu.org/problemnew/show/P3375)

---

## 作者：Lyccrius (赞：0)

对字符串 $S$ 自匹配求出 $next$ 数组，根据定义，对于每个 $i$，$S[i - next[i] 1 \sim i]$ 与 $S[1 \sim next[i]]$ 是相等的，且不存在更大的 $next$ 值满足这个条件。

**引理**：$S[1 \sim i]$ 具有长度为 $len \lt i$ 的循环元的充要条件是 $len$ 能整除 $i$ 并且 $S[len + 1 \sim i] = S[1 \sim i - len]$（即 $i - len$ 是 $next[i]$ 的候选项）。

根据引理，当 $i - next[i]$ 能整除 $i$ 时，$S[1 \sim i - next[i]]$ 就是 $S[1 \sim i]$ 的循环元。它的最大循环次数就是 $i / (i - next[i])$。其中 $i - next[i]$ 能整除 $i$ 的条件是为了保证循环元每次重复的完整性。

进一步地，如果 $i - next[next[i]]$ 能整除 $i$，那么 $S[1 \sim i - next[next[i]]$ 就是 $S[1 \sim i]$ 的最小循环元。以此类推，我们还可以找出 $S[1 \sim i]$ 所有可能的循环元。

```
#include <cstdio>
#include <cstring>

const int maxn = 1e6 + 10;

int t;
int n;
char s[maxn];
int next[maxn];
int f[maxn];

void KMP() {
    next[1] = 0;
    for (int i = 2, j = 0; i <= n; i++) {
        while (j > 0 && s[i] != s[j + 1]) j = next[j];
        if (s[i] == s[j + 1]) j++;
        next[i] = j;
    }
    for (int i = 2; i <= n; i++) {
        if (i % (i - next[i]) == 0 && i / (i - next[i]) > 1) {
            printf("%d %d\n", i, i / (i - next[i]));
        }
    }
    return;
}

int main() {
    while (scanf("%d", &n) && n) {
        t++;
        printf("Test case #%d\n", t);
        scanf("%s", s + 1);
        KMP();
        printf("\n");
    }
    return 0;
}
```

---

## 作者：wzy2021 (赞：0)

前置知识：KMP

本蒟蒻已经默认大佬们会了 KMP


------------
我们来看一下这道题：

设 $nxt_i$ 表示 $A$ 中以 $i$ 为结尾的非前缀子串与 $A$ 的前缀 能够匹配的最长长度，即：

$nxt_i = \max(j)$，其中 $j < i$ 并且 $A_{i - j + 1}$ ~ $A_i = A_1$ ~ $A_j$

$nxt_i$是 KMP 的精髓，不在讲述。

显然，若 $i - nxt_i$ 能被 $i$ 整除时， $A_1$ ~ $A_{nxt_i}$ 就是 $A_1$ ~ $A_i$ 的最小循环元，那么它的最大循环次数是 $i / (i - nxt_i)$。

其中，$i - nxt_i$ 能整除 $i$ 的条件是为了保证循环元每次重复的完整性

具体实现，请看代码。

```cpp
#include <iostream>
using namespace std;

const int maxn = 1000010;
char a[maxn];
int nxt[maxn], n, t;

void calc () {
    nxt[1] = 0;
	for (int i = 2, j = 0; i <= n; ++i) {
		while (j > 0 && a[i] != a[j + 1]) j = nxt[j];
		if (a[i] == a[j + 1]) j ++;
		nxt[i] = j; 
	}
}

int main() {
	while (scanf ("%d", &n) != EOF && n) {
		scanf ("%s", a + 1);
		calc (); // 计算 nxt[i]
		printf ("Test case #%d\n", ++t);// 注意输出
		for (int i = 2; i <= n; ++i) {
			if (i % (i - nxt[i]) == 0 && i / (i - nxt[i]) > 1) {
				printf ("%d %d\n", i, i / (i - nxt[i]));
			}
		}
		printf ("\n");
	}
	return 0;
}
```


---

## 作者：ZRHan (赞：0)

利用KMP的nxt数组，首先如果一个子串是循环节，那么他第一次出现循环的时候一定在偶数的位置。比如说：
```latex
  abcabcabcabc
       ^  ^  ^
i      6  9  12
k      2  3  4
```
在i=6的位置可以是一个可行的前缀。而且当且仅当它的nxt是$\frac{i}{2}$，它才是k=2的循环节。在例子中nxt[6]显然等于3。它的周期$t$会等于$\frac{i}{2}$也就是3。


然后可以按照类似线性筛的方法枚举它的每个周期，即k=3，k=4，k=5......
如果某个$k$能成为循环，那么此时的nxt应该是$(k-1)*t$。比如i=9的显然是一个可行的循环，此时t=3，k=3，而nxt[i]=6。


期间用vis记录，访问过的就跳过，就可以$O(n)$解决。

```cpp
#include<cstdio> 
#include<cstring>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
const int maxn = 1e6+5;
int nxt[maxn], n;
char s[maxn];
bool vis[maxn];

void getnxt()
{
    for(int i=2, j=0; i<=n; ++i)
    {
        while(j>0 && s[i]!=s[j+1]) j = nxt[j];
        if(s[i]==s[j+1]) ++j;
        nxt[i] = j;
    }
}

int main()
{
    int qwq=0;
    scanf("%d", &qwq);
    for(int qqq=1; qqq<=qwq; ++qqq)
    {

        scanf("%d", &n);
        if(n==0) return 0;
        scanf("%s", s+1);

        printf("Test case #%d\n", qqq);
        getnxt();

        for(int i=2; i<=n; i+=2)
        {
            if(vis[i]) continue;
            if(nxt[i] == i>>1)  //当且仅当它的nxt是i/2，它才是k=2的循环节
            {
                int t = i>>1;
                vis[i] = 1;
                printf("%d %d\n", i, 2);
                for(int j=i+t, cnt=1; j<=n; j+=t, ++cnt)  //枚举k=3，k=4，k=5... 
                {
                    if(vis[j]) continue;
                    if(nxt[j] == (cnt+1)*t) 
                    {
                        printf("%d %d\n", j, cnt+2);
                        vis[j] = 1;
                    }
                    else break;  
                    //如果已经不满足循环了，k就不能再加了，因为即使后面的满足也被这个不满足的部分中断 
                }
            }
        }

        puts("");
        
        //初始化 
        for(int i=0; i<=n; ++i)
        {
            vis[i] = nxt[i] = s[i] = 0;
        }
    }
    return 0;
}
```

---

## 作者：傅思维666 (赞：0)

一道KMP算法的练手好题。

大体的题目大意是这样的：

## 题目大意：

如果一个字符串S是由一个字符串T重复K次形成的，则称T是S的循环元。使K最大的字符串T称为S的最小循环元，此时的K称为最大循环次数。

现给一个给定长度为N的字符串S，对S的每一个前缀S[1~i]，如果它的最大循环次数大于1，则输出该前缀的最小循环元长度和最大循环次数。

## 题解：

一道KMP算法的题目，如果对KMP算法还是没有什么深刻的理解或者还没学KMP算法的，请移步我的这篇博客，讲解还算详细：

[KMP算法详解]( https://www.cnblogs.com/fusiwei/p/11945030.html )

一开始拿到题没什么思路（我还是太菜了）

后来发现，对给出的串$S$自匹配求出$nxt$数组之后，对于每一个$i$，一定会有这么一个结论：
$$
S[1\,\,to\,\,nxt[i]]=S[i-nxt[i]+1\,\,to\,\,i]
$$
这是通过KMP算法对$nxt$数组的定义得来的。

那么，既然这两个东西是相等的，那么在对这个子串进行匹配的时候，这个循环节长度就应该是$i-nxt[i]$，然后循环次数当然就是$i/(i-nxt[i])$，当然，前提需要是$i\%(i-nxt[i])==0$。

代码如下：

```cpp
#include<cstdio>
using namespace std;
const int maxl=1e6+10;
int n,tot;
char s[maxl];
int nxt[maxl];
int main()
{
    while(~scanf("%d",&n) && n)
    {
        scanf("%s",s+1); 
        tot++;
        printf("Test case #%d\n",tot);
        nxt[1]=0;
        for(int i=2,j=0;i<=n;++i)
        {
            while(s[i]!=s[j+1] && j) 
                j=nxt[j];
            if(s[i]==s[j+1]) 
                j++;
            nxt[i]=j;
            if(nxt[i]!=0 && i%(i-nxt[i])==0) 
                printf("%d %d\n",i,i/(i-nxt[i]));
        }
        printf("\n");
    }
    return 0;
}
```



---

## 作者：Ouaoan (赞：0)

题目：[Period](https://www.luogu.org/problemnew/show/UVA1328)



思路：

假如一段字符串有周期，那么 i - next[i]一定是最小周期长。

因为next[i]表示最长的相同前缀、后缀的长度，假设这个有周期的字符串一共有x个周期，此时，最长的相同的前缀、后缀是 第1到第x-1个周期 和 第2到第x个周期，则一个周期长就是 i-next[i]。

比如一个字符串为 abcabcabc，next=6，i=9，则周期长为3。

如果一个字符串的 i%( i - next[i] ) ! = 0 ，那么可以肯定这个字符串没有周期。因为如果它有周期，那么它一定可以被划分成整数个长度为 i - next[i] 的串。



注意：听说 noip 变量名用 next 会挂。



代码：


```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <stack>
#include <queue>
#include <deque>
#include <set>
#include <cstring>
#include <map>
using namespace std;

#define maxn 1000000

int n;
char a[maxn+5];
int nxt[maxn+5]={0};

int main() {
	
	int T=0;
	while(~scanf("%d",&n)&&n!=0){
		printf("Test case #%d\n",++T);
		scanf("%s",a);
		nxt[0]=-1;
		for(int i=0;i<n;i++){
			int j=nxt[i];
			while(j>=0&&a[j]!=a[i]){
				j=nxt[j];
			}
			nxt[i+1]=++j;
		}
		for(int i=1;i<=n;i++){ 
			if(nxt[i]&&i%(i-nxt[i])==0){
				printf("%d %d\n",i,i/(i-nxt[i]));
			}
		}
		printf("\n");
	}
	
	return 0;
}

```




---

## 作者：cellur925 (赞：0)

$Algorithm$

题意：给出一个字符串，对这个字符串的所有前缀，检查它是不是一个周期串，并求出最小循环节。

考虑周期串的性质：如果$S$=$A^k$（$k$个$A$连在一起），那么$A^{k-1}$既是$S$的前缀又是$S$的后缀。这是不是和$KMP$算法中的$next$数组的含义很像？事实上，显然有$A^{k-1}$的长度等于$next$($S$)的关系。

如果|$S$|-$next$($S$)是当前字符串长度的一个约数，根据前缀后缀的相等关系我们可以断定$S$必然是周期串。又由于$next$($S$)的最大性质，前|$S$|-$next$($S$)个字符一定是最小循环节。否则$S$不是一个周期串。
而本题问的是最小循环次数，那么我们的答案就是$i$/($i$-$next[i]$)。

又因为我们要求长度大于1的循环节，所以加一步特判即可。

（算法部分，引用2018.5济南$qbxt$邹雨恒老师的字符串课件讲解，侵删。）



------------

$Code$
```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>

using namespace std;

int n,j,pos=1;
int nxt[1000090]; 
char a[1000090];

int main()
{
    while(scanf("%d",&n)!=EOF&&n!=0)
    {
        scanf("%s",a+1);
        printf("Test case #%d\n",pos);
        pos++;
        j=0;
        for(int i=2;i<=n;i++)
        {
            while(j&&a[i]!=a[j+1]) j=nxt[j];
            if(a[i]==a[j+1]) j++;
            nxt[i]=j;
        }
        for(int i=2;i<=n;i++)
            if(i%(i-nxt[i])==0&&i/(i-nxt[i])>1) printf("%d %d\n",i,i/(i-nxt[i])); 
        memset(nxt,0,sizeof(nxt));
        printf("\n");
    }
    return 0;
}
```
注意每组数据结束后的多余空行。$qwq$


------------

$ex$

求出循环串的所有可能的循环元？类比刚才的过程，我们可以继续运用$next$数组的性质，若$i$除以$i$-$next[next[i]]$余数为0，那么$i$/$i$-$next[next[i]]$就是周期串的次小循环节，以此类推。


------------

$Advertisement$

欢迎大家来我的[](http://www.cnblogs.com/nopartyfoucaodong/)$Blog$~

---

## 作者：览遍千秋 (赞：0)

思路：本题就是和KMP差不多，求出这个字符串的$next$数组，满足
$i mod (i-Next_i)=0$且$Next_i≠0$时，$i$即可取。

代码的细节，在最后一个测试数据的末尾也要有一个空行。

代码较为简单，就不给出了。如果有问题请私信我。

---

