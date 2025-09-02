# Double-ended Strings

## 题目描述

You are given the strings $ a $ and $ b $ , consisting of lowercase Latin letters. You can do any number of the following operations in any order:

- if $ |a| > 0 $ (the length of the string $ a $ is greater than zero), delete the first character of the string $ a $ , that is, replace $ a $ with $ a_2 a_3 \ldots a_n $ ;
- if $ |a| > 0 $ , delete the last character of the string $ a $ , that is, replace $ a $ with $ a_1 a_2 \ldots a_{n-1} $ ;
- if $ |b| > 0 $ (the length of the string $ b $ is greater than zero), delete the first character of the string $ b $ , that is, replace $ b $ with $ b_2 b_3 \ldots b_n $ ;
- if $ |b| > 0 $ , delete the last character of the string $ b $ , that is, replace $ b $ with $ b_1 b_2 \ldots b_{n-1} $ .

Note that after each of the operations, the string $ a $ or $ b $ may become empty.

For example, if $ a= $ "hello" and $ b= $ "icpc", then you can apply the following sequence of operations:

- delete the first character of the string $ a $ $ \Rightarrow $ $ a= $ "ello" and $ b= $ "icpc";
- delete the first character of the string $ b $ $ \Rightarrow $ $ a= $ "ello" and $ b= $ "cpc";
- delete the first character of the string $ b $ $ \Rightarrow $ $ a= $ "ello" and $ b= $ "pc";
- delete the last character of the string $ a $ $ \Rightarrow $ $ a= $ "ell" and $ b= $ "pc";
- delete the last character of the string $ b $ $ \Rightarrow $ $ a= $ "ell" and $ b= $ "p".

For the given strings $ a $ and $ b $ , find the minimum number of operations for which you can make the strings $ a $ and $ b $ equal. Note that empty strings are also equal.

## 样例 #1

### 输入

```
5
a
a
abcd
bc
hello
codeforces
hello
helo
dhjakjsnasjhfksafasd
adjsnasjhfksvdafdser```

### 输出

```
0
2
13
3
20```

# 题解

## 作者：_xbn (赞：4)

我们对题意进行适当转化，由于只能在 a ， b 首尾进行操作，所以最后得到的

肯定是 a ， b 的最长公共子串，所以最少操作即为 a 串的长度加 b 串长度，

再减去 2 倍的最长公共子串，至于求最长公共子串，我们可以考虑 dp ，我们

用 k 表示 a ， b 当前的最长公共子串，若 $a(i+k)$ 等于 $b(i+k)$ 则更新 k 的长度

最后 k 即为答案。

```cpp
#include <bits/stdc++.h>
using namespace std;
void solve() 
{
	string a, b;
	cin >> a >> b;
	int maxk = 0;
	for (int i=0; i<a.size(); i++) 
	{
		for (int j=0; j<b.size(); j++) 
		{
			int k = 0;
			while (i+k < a.size() && j+k < b.size() && a[i+k] == b[j+k])k++;
			if (k > maxk) maxk = k;
		}
	}
	cout << a.size() + b.size() -2*maxk << endl;
}

int main() 
{
	int T;
	cin >> T;
	for (int i=1; i<=T; i++)solve();
}

```

代码应该是题解区最短的了。


---

## 作者：chenkaiwen (赞：2)

理解题意。

现有两个字符串，能从头尾删除字符，使得两个字符串相等。

**因为只能从头尾删除，所以中间的元素不会改变，所以这一题是在变相地求两个字符串的最长公共子串。**

注意：中间元素不会改变，所以想要使得两个字符串相同，必须是连续的子串而非不连续的子序列。

我们再看一下数据范围， $N\leqslant20$，$T\leqslant100$ 那么，我们只需要用 $O(N^3T)$ 的大暴力就能解决这题。


```cpp
#include<bits/stdc++.h>
using namespace std;
string s1,s2,ans="",sum="";
int Max=-1,l1,l2,l=0;
void In(){
	cin>>s1>>s2;
	ans="";Max=-1;
	l1=s1.size(),l2=s2.size();//注意 .size()的时间复杂度的O(N)的，所以不能放在循环中。
}
void Work(){
	Max=-1;
	for(int i=0;i<l1;i++){
		for(int j=0;j<l2;j++){
			sum="";int k;
			for(k=0;k+j<l2&&k+i<l1;k++){//三重暴力。
				if(s1[i+k]!=s2[j+k]){
					if(Max<k){
						ans=sum;
						Max=k;
					}
					break;
				}
				sum+=s1[i+k];
			}
			if(Max<k){
				ans=sum;
				Max=k;
			}
		}
	}
	cout<<l1-Max+l2-Max<<endl;
}
int main(){
	int t;cin>>t;
	while(t--){
		In();
		Work();
	}
	return 0;
}

```


---

## 作者：Infinity_Detail (赞：1)

题目传送门：[CF1506C](https://www.luogu.com.cn/problem/CF1506C)

现在 $div.3$ 的C题变难了啊。一般 $D$、$E$ 题才会考这种题啊。

不过理解起来不是很难，有点像KMP字符串匹配的反配题。

而且数据范围也很小！！！

### 题意概述：

对于两个字符串，只能删掉他们的头或者尾。如果要使这两个字符串是匹配的，求最少需要的删除操作之和。

## 思路：
体面非常不难理解，思路也是比较好想的。

我们可以从侧面看一下这个题面中**只能删头和尾**这一段内容。因为只能去头或去尾，所以最终删完得到部分的一定是连着的。根据这一结论，我们不难想到这道题其实就是一个取最长公共子串长度的题。
### 首先考虑暴力：两种方法。
1.直接从第一个字符串的每个位置上查找第二个字符串的相应位置，然后暴力记录最长公共部分。

2.对于第一个字符串中的每个字符，都在第二个字符串中找相同的，然后在每个位置上往后匹配。

虽然复杂度很高，但是数据范围小啊，我们可以随便霍霍（bushi）。

还是想一想有没有什么好的办法？当然有，还有好多。我们仍然选择好用的DP来做。

### 既然是DP，那就要考虑 ：      **状态和转移**。


#### 状态：
设这两个字符串分别为a和b，然后设 $dp_{i,j}$ 为以 $a_{i-1}$ 和 $b_{j-1}$ 
作为结尾的两个公共子串的长度，初始值为0。

#### 转移：

1.如果 $a_i$ 与 $b_j$ 是一样的，说明这里可能是公共子串的开头，也有可能这个地方可以承接之前的公共子串，那么继续往后扫，公共子串的长度也就加一。所以转移方程就很容易得出 :

###   $dp_    {i+1,j+1}=dp_{i,j}+1$ .
                   
2.如果 $a_i$ 与 $b_j$ 是不同的，说明这时公共子串的结尾是他们的上一个字符，那么此时以这两个地方为结尾的字符串最长公共子串长度为 $0$ 。那么转移方程也就呼之欲出：

###    $dp_{i+1,j+1}=0$ .


#### 最后处理答案：
既然要求删掉的次数，那就求出来剩下的，因为剩下的东西在两个串里是一样的，那答案就是：两个字符串的长度和减去最长公共子串的长度的两倍。

思路已经很明确了吧，下面直接上代码：

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<string>
using namespace std;
int dp[25][25];
string a,b;
int t,maxl;
int main(){
	cin>>t;
    while(t--){
        cin>>a>>b;
        maxl=0;
        memset(dp,0,sizeof(dp));
        for(int i=0;i<a.size();i++){ 
            for(int j=0;j<b.size();j++){
            	if(a[i]==b[j]) dp[i+1][j+1]=dp[i][j]+1;
            	else dp[i+1][j+1]=0;
                maxl=max(maxl,dp[i+1][j+1]);
            }
		} 
        cout<<a.size()+b.size()-maxl*2<<endl;
    }
    return 0;
}
```


---

## 作者：nalemy (赞：1)

首先，这道题的要求是给两个字符串 $a,b$，删掉它们第一个字符或最后一个字符任意次，求最少几次能够使这两个字符串相等。

由于只能删掉前缀或后缀，所以剩下的部分在源字符串中必须是**连续的**，这道题本质上就是求两个字符串的**最长公共子串**。

我们考虑动态规划：$dp_{i,j}$ 表示以 $a_{i-1}$ 和 $b_{j-1}$ 这两个位置为结尾的最长公共字串长度。

接下来考虑状态转移方程：

1. 如果 $a_i=b_i$，那么这里其实**可以承接前面的最长公共子串**；
2. 如果 $a_i\not=b_i$，那么前面的最长公共子串到上一个位置就**结束了**，以这两个位置为结束字符的最长公共子串长度为 $0$。

因此我们得到状态转移方程如下：
$$
dp_{i+1,j+1}=\begin{cases}
dp_{i,j}+1 & (a_i=b_j) \\
0 & (a_i\not=b_j)
\end{cases}
$$
更新答案：在每次转移 $dp$ 时进行求最大值（虽然这样可能不是最优，但是保险）

最后求解答案。题目求的是**最少删去多少字符**，因为除了最长公共子串以外都要删掉，所以答案就是两字符串长度之和减去最长公共子串长的的**两倍**。

代码如下：

```C++
#include<iostream>
#include<cstring>
#define N 20
using namespace std;

int dp[N][N];
int main() {
    string a, b;
    int q, as, bs, mx; cin >> q;
    while (q--) {
        cin >> a >> b, mx = 0, as = a.size(), bs = b.size();
        memset(dp, 0, sizeof(dp));
        for (int i=0; i<as; i++)
            for (int j=0; j<bs; j++)
                dp[i+1][j+1] = a[i] == b[j] ? dp[i][j] + 1 : 0,
                mx = max(mx, dp[i+1][j+1]);
        cout << as + bs - mx * 2 << endl;
    }
    return 0;
}
```



---

## 作者：Dragonbell_exp (赞：0)

### 题意：
给两个字符串，你可以删除这两个字符串的首尾元素，求使两个字符串完全相等所需的最少删除次数。
### 思路：
在只删除首尾元素的情况下，每一个字符串的子序列的连续性是无法更改的。

也就是说，我们只能取每个字符串中一段连续的部分，想要让两个字符串在只删除首尾元素的情况下相等也只能是这两个字符串中有某一段连续部分相等。为了让删除次数最少，自然就是让这个部分最长。这个最长连续部分也就是 $a$ 与 $b$ 的最长连续公共子序列，我们把它命名为 $s$。

除 $s$ 外这两个字符串的其它东西都要被删除。 $s$ 就是最长的了，其它任何连续公共字符列都没有 $s$ 长，只保留两个字符串中 $s$ 这一部分就能在删除次数最少的情况下保证 $a$ 与 $b$ 完全相等。

##### 最小删除次数就是 $|a|+|b|-s-s$。
为什么要减两个 $s$？因为 $s$ 是 $a$ 与 $b$ 共有的一部分。
### 实现：
队里的巨佬都会用 DP，只有我不会，所以给出暴力做法。

从 $a$ 里找一块与 $b$ 相同的部分，那么就枚举 $a$ 与 $b$ 中的每一部分，然后循环记录最长的连续公共子序列，输出即可。

### 代码：
```c
#include<iostream>
#include<cstring>
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
	while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int t;//数据组数 
char o1[100];//a和b 
char o2[100];
int far;//每一次的连续公共子序列长度 
int ans;//最长连续公共子序列 
int main(){
	t=read();
	while(t--){
		cin>>o1>>o2;
		ans=0;
		int lo1=strlen(o1);
		int lo2=strlen(o2);//取a，b长度 
		for(int i=0;i<lo1;i++){//暴力枚举a与b中相同的部分 
			for(int j=0;j<lo2;j++){
				far=0;
				int v1=i;
				int v2=j;
				while(v1<lo1&&v2<lo2&&o1[v1]==o2[v2]){//寻找连续公共子序列 
					far++;
					v1++;
					v2++; 
				}
				ans=max(ans,far);//求最长连续公共子序列 
			}
		}
		cout<<lo1+lo2-ans-ans<<endl;//输出结果 
	}
	return 0;
}
```




---

## 作者：Allanljx (赞：0)

[洛谷传送门](https://www.luogu.com.cn/problem/CF1506C)

[CF传送门](http://codeforces.com/problemset/problem/1506/C)
## 思路
因为当留下来的字母最长时，要删除的字符最短，所以用 $dp$ 求最长公共子串。 最后用总长度减去留下的长度。
```cpp
n+m-2*ans
```


$dp[i][j]$ 表示当当前字符是 $s1[i]$ 和 $s2[j]$ 时的最长公共子串。

转移方程： 
```cpp
if(s1[i]==s2[j]) dp[i][j]=dp[i-1][j-1]
```
## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
char s1[31],s2[31];
int dp[31][31];
signed main()
{
	int t;
	cin>>t;
	while(t--)
	{
		memset(dp,0,sizeof(dp));//清零 
		cin>>s1>>s2;
		int n=strlen(s1),m=strlen(s2),ans=0;
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<m;j++)
			{
				if(s1[i]==s2[j])//如果当前字符一样，则从i-1和j-2转移过来 
				{
					if(i==0||j==0)//如果是头的话 则dp[i][j]为1，否则会越界 
					{
						dp[i][j]=1;
						continue;
					}
					dp[i][j]=dp[i-1][j-1]+1;
				}
			}
		}
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<m;j++)
			{
				ans=max(ans,dp[i][j]);
				//cout<<dp[i][j]<<' ';
			}
			//cout<<endl;
		}
		cout<<n+m-2*ans<<endl;
	}
    return 0;
}
```
注意：并非最长公共子序列

---

## 作者：yxy666 (赞：0)

题意：叫我们把两个字符串从头或尾分别干掉几个字母，使两个字符串相等。叫我们求最小的删除次数。

思路：如果直接从删字母的角度来说，是有点困难的。那我们就换一个看法，题目叫我删尽量少的字母，不就是想要让留下来的字符串相同且长一点吗！那么模型就变成了求两个字符串的最长公共子序列的长度。

由于题目问我们的是删掉几个字母，那么答案就是第一个字符串的长度加第二个字符串的长度减去最长公共子序列的长度的两倍。由于本题字符串长度较小，所以我们可以通过哈希来解决。先枚举最长公共子序列长度，然后看一下第一个字符串和第二个字符串中是否都有。取最大值用于计算。

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,W=37,w[25],s[25],p[25];
char a[25],b[25];
bool flg;
inline int read(){
	int ret=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
	while(isdigit(ch))ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}//快读
int main(){
	T=read();w[0]=1;
	for(int i=1;i<=20;i++)w[i]=w[i-1]*W;
	while(T--){
		scanf("%s",a+1);int len=strlen(a+1);
		scanf("%s",b+1);int Len=strlen(b+1);
		for(int i=1;i<=len;i++)s[i]=s[i-1]*W+a[i]-'a'+1;//构造hash数组
		for(int i=1;i<=Len;i++)p[i]=p[i-1]*W+b[i]-'a'+1;//构造hash数组
		int first=0; 
		for(int k=min(len,Len);k>=0;k--){//从大到小枚举长度
			for(int i=k;i<=len;i++){//开始找
				first=s[i]-s[i-k]*w[k];
				for(int j=k;j<=Len;j++){
					if(first==p[j]-p[j-k]*w[k]){//有的话就直接输出
						printf("%d\n",Len+len-2*k);
						flg=1;break;
					}
				}
				if(flg)break;
			}
			if(flg)break;
		}
		flg=0;
	}
	return 0;
}
```


---

## 作者：_Clown_ (赞：0)

# 概述
|题号|难度|$AC$时间及记录|
| :----: | :----: | :----: |
|$\texttt{CF1506C}$|$\texttt{洛谷难度:暂无评定}$|[$\texttt{On 2021/03/26}$](https://www.luogu.com.cn/record/48474878)|
# 解析
这是一道简单题。

题意不难理解。

其实，我们稍微想一想，就知道：
- 如果 $a$ 非空，删除 $a$ 的第一个字符。
- 如果 $a$ 非空，删除 $a$ 的最后一个字符。
- 如果 $b$ 非空，删除 $b$ 的第一个字符。
- 如果 $b$ 非空，删除 $b$ 的最后一个字符。

这一大段话，意思就是：
- 求 $a$ 和 $b$ 的**最长公共子串**。

然后我们可以用一个 $\mathcal{O(nm)}$ 的 $Dp$ 求出解。

这个不会请自己百度吧。

（$n$，$m$ 是两字符串长度）

顺便还是说一句：求出最长公共子串以后，我们还需要处理一下答案。![jk](https://cdn.luogu.com.cn/upload/pic/62234.png)
```cpp
AA=A.size(),BB=B.size();
cout<<AA+BB-2*findLength(A,B)<<endl;
```
# 代码
```cpp
/*
Author:Xsmyy
Problem:CF1506C
Date:2021/03/25
*/
#include<bits/stdc++.h>
#define BetterIO ios::sync_with_stdio(false)
using namespace std;
int N,K;
bool Flag[101];
inline int findLength(string A,string B) {
    int asize=A.size();
    int bsize=B.size();
    int dp[asize][bsize];
    int max = 0;

    for(int i=0,j=0; i<asize; i++){
        if(A[i] == B[j]){
            dp[i][j] = 1;
            max = 1;
        }else{
            dp[i][j] = 0;
        }
    }

    for(int i=0,j=0; j<bsize; j++){
        if(A[i] == B[j]){
            dp[i][j] = 1;
            max = 1;
        }else{
            dp[i][j] = 0;
        }
    }

    for(int i=1; i<asize; i++){
        for(int j = 1; j<bsize; j++){
            if(A[i] == B[j]){
                dp[i][j] = dp[i-1][j-1] + 1;
            }else{
                dp[i][j] = 0;
            }

            if(dp[i][j] > max){
                max = dp[i][j];
            }
        }
    }

    return max;
}
int main(void)
{
	BetterIO;
	register int Case;
	cin>>Case;
	while(Case--)
	{
		register string A,B;
		cin>>A>>B;
		register int AA,BB;
		AA=A.size(),BB=B.size();
		cout<<AA+BB-2*findLength(A,B)<<endl;
	}
	return 0;
}
```

---

## 作者：LinkZelda (赞：0)

- **题意**：

给你两个字符串，你每次可以删除其中一个字符串的首字符或者尾字符，求最少操作次数使得两个字符串相等。

- $Solution$:

鉴于这是 div3 ，我们采用朴素做法。直接暴力搜索，用较短的字符串枚举删首字符或者末尾字符，然后每次 $O(n^2)$ 判断该字符串是否为较长字符串的一个子串，更新答案即可。

当然，我们应该适当剪枝：判断目前枚举的字符串是否枚举过。这个可以用 `hash` 实现，为了方便，我用了 `map` 来判重。

- [代码](https://www.luogu.com.cn/paste/368tih9k)

---

## 作者：Eason_AC (赞：0)

## Content
有两个字符串 $a,b$。我们每次操作可以将两个字符串中的一个字符串的最前面一个字符或这最后面一个字符删去（**可以将某个字符串通过若干次操作变为空串**）。求需要多少次操作才能够使 $a,b$ 两个字符串是相同的。

**数据范围：$t$ 组数据，$1\leqslant t\leqslant 100$，$1\leqslant |a|,|b|\leqslant 20$。**
## Solution
我们发现只要你能够找到 $a,b$ 两个字符串之间的公共部分，你就只需要去删这公共部分之外的其它的部分就好，所以这道题目本质上讲就是要我们去求 $a,b$ 的**最长公共子串的长度**。而又因为 $a,b$ 的长度实在是小得可怜，因此我们考虑直接枚举。

首先枚举 $a,b$ 两个字符串中子串的起始位置，然后再枚举长度，之后用 STL 中自带的 `substr` 函数去提取出两个字符串的子串，如果这两个子串相等，就去比较先前的答案，取长度的较大值。设我们最终得到的最长公共子串为 $s$，则答案就是 $|a|+|b|-2\cdot|s|$。
## Code
```cpp
string a, b;

int main() {
	MT {
		cin >> a; int len1 = a.size(); cin >> b; int len2 = b.size();
        int ans = 0;
		F(int, i, 0, len1 - 1) F(int, j, 0, len2 - 1) F(int, k, 0, len1 - i) F(int, l, 0, len2 - j) {
			if(k != l) continue; //连长度都不一样，这两个子串肯定不相同，跳过。
			string s1 = a.substr(i, k), s2 = b.substr(j, l);
			if(s1 == s2) ans = max(ans, (int)s1.size());
		}
		println(len1 + len2 - ans * 2);
	}
    return 0;
}
```

---

## 作者：feicheng (赞：0)

## Description

给两个字符串，可以从头或尾删除字母使得两个字符串相等，最小化删除次数（空串也相等）。

## Solution

我们会发现按照这样的删除方式，只有连续的公共子串不会被删除。所以我们可以把问题转化成求两个子串的最长连续公共子串长度。即：

设字符串为 $s,t$， **$f[i][j]$ 表示 $s$ 以 $s_i$ 结尾，$t$ 以 $t_j$ 结尾的最长连续子串长度**，则可以分类转移：

$$\begin{cases}
f[i][j]=f[i-1][j-1]\quad(s[i]=s[j])\\
f[i][j]=0\quad otherwise\\
\end{cases}$$

时间复杂度为 $\Theta(ta_{length}b_{length})$

## Code

```cpp
/*If you are full of hope,you will be invincible*/
#define ri register int
typedef long long ll;
std::mt19937 hpy(time(nullptr)+(unsigned long long)(new char));
using std::cin;
using std::cout;
constexpr int inf=0x3f3f3f3f;
std::string s1,s2;
int ans;
int f[30][30];
int t;
inline void solve() {
    memset(f,0,sizeof f);
    int len1 = s1.size(),len2 = s2.size();
    for(int i = 0;i < len1;++i) {
        for(int j = 0;j < len2;++j) {
            if(s1[i] == s2[j]) {
                if(!i || !j) f[i][j] = 1;
                else f[i][j] = f[i-1][j-1] + 1;
            }
        }
    }
    int mx = 0;
    for(int i = 0;i < len1;++i) {
        for(int j = 0;j < len2;++j) mx = std::max(f[i][j],mx);
    }

    ans = len1 + len2 - mx*2;//最长公共子串的贡献为其长度的两倍（在a中的贡献和在b中的贡献）
}
int main(int argc,const char *argv[]){
	std::ios::sync_with_stdio(false);
    cin >> t;
    while(t--) {
        cin >> s1 >> s2;
        solve();
         cout << ans << '\n';
    }
	return 0;
}
```

---

## 作者：thhxxx (赞：0)

#  **题目翻译** 




本题给定两个字符串 $a$ 和 $b$，在两个字符串非空时我们可以把两个字符串其中一个的第一个字符或最后一个字符截掉记为一次操作，求最少多少次操作可以使两个字符串相同。

本题数据范围：有 $t\leq100$ 组数据，且串 $a$ 和串 $b$ 的长度范围为 $1\leq\vert a \vert,\vert b\vert\leq20$。

注意：两个空串也可视为相同！

# **思路**




分析题意我们可以知道 

  - 该题的本质是求两个字符串的**最长公共子串**。
  -  $a$ 和串 $b$ 的长度范围为 $1\leq\vert a\vert,\vert b\vert\leq20$，完全可以使用**暴力枚举**的方法枚举公共字串所有可能子串。（长度从1到  $a$ 串和 $b$ 串中长度较短的字符串的长度）
  - 在两个字符串中暴力枚举所有子字符串，若找到公共子串，记录下该公共字串的长度，直到枚举完所有字串，得到的最长的长度便是最长公共字串的长度，最后 $a$ 串和 $b$ 串的长度与最长公共字串的长度相减的差之和便是最少所需操作次数。



# **AC代码**






```

#include <iostream>

using namespace std;

int main()
{
    int n;
    cin>>n;

    while (n--)
    {
        string a,b;
        cin>>a>>b;
        int maxn=0;//当两个字串完全不相同时最长公共子串长度为0

        int l1=a.size(),l2=b.size();

        for (int len=1;len<=min(l1,l2);len++
        {
            for (int i=0;i+len-1<l1;i++)
            {
                for (int j=0;j+len-1<l2;j++)
                {
                    if (a.substr(i,len)==b.substr(j,len)) //substr(起始下标，(子串长度))，返回子串
                        maxn=max(maxn,len);
                }
            }
        }
        cout<<(l1-maxn)+(l2-maxn)<<'\n';
    }
    return 0;
}
```


---

