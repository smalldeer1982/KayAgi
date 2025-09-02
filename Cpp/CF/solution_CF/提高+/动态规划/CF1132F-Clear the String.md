# Clear the String

## 题目描述

You are given a string $ s $ of length $ n $ consisting of lowercase Latin letters. You may apply some operations to this string: in one operation you can delete some contiguous substring of this string, if all letters in the substring you delete are equal. For example, after deleting substring bbbb from string abbbbaccdd we get the string aaccdd.

Calculate the minimum number of operations to delete the whole string $ s $ .

## 样例 #1

### 输入

```
5
abaca
```

### 输出

```
3
```

## 样例 #2

### 输入

```
8
abcddcba
```

### 输出

```
4
```

# 题解

## 作者：一只书虫仔 (赞：17)

update on 2020.10.23 感谢 @[我谔谔](https://www.luogu.com.cn/user/127284) 的纠错

#### Description

> 给定一个字符串 $S$，每次可以删除一个所有字符都相等的连续子串，求最小删除次数使得这个串变为空串。

#### Solution

区间 dp 套路题，套路类似 [这题](https://www.luogu.com.cn/problem/P4170)，建议先做一做这题。

定义 $dp[l][r]$ 为删除区间 $[l,r]$ 需要的最小删除次数，$\forall k \in [i,j)$，状态转移方程如下：

$$dp[i][j]=\min\{dp[i][k]+dp[k+1][j-1]+[S[j] \ne S[k]]\}$$

当 $i=j$ 时，$dp[i][j]=1$。

$S[j]\ne S[k]$ 的特判原因是因为通过这样判断这个区间能不能删除。

#### Code

```cpp
#include <bits/stdc++.h>

using namespace std;

int dp[1001][1001];

int main () {
	int n;
	char s[505];
	scanf("%d", &n);
	scanf("%s", s);
	for (int len = 0; len < n; len++)
		for (int i = 0; i < n - len + 1; i++) {
			int j = i + len;
			int Min = 0x3f3f3f3f;
			if (i == j) {
				dp[i][j] = 1;
				continue;
			}
			for (int k = i; k < j; k++) {
				if (s[j] == s[k]) Min = min(Min, dp[i][k] + dp[k + 1][j - 1]);
				else Min = min(Min, dp[i][k] + dp[k + 1][j - 1] + 1);
			}
			dp[i][j] = Min;
		}
   	while (1);
	printf("%d", dp[0][n - 1]);
	return 0;
}

```

By Shuchong           
2020.10.17

---

## 作者：天梦 (赞：11)

[CF1132F](https://www.luogu.com.cn/problem/CF1132F)
## 区间dp

区间dp，就是对区间做dp，实际上，如果每个位置是一样的话，状态设计可以设计成 $f_i$ ，否则，我们通常设计为 $f_{i,j}$ ，表示区间 $[i,j]$ 的状态。

在转移时，前者多为枚举上一个状态，后者为区间断点，值得注意的是，后者的dp顺序一般为从短到长dp。

## 思路

关注到数据范围，这道题是一道区间dp，于是我们很自然的设状态 $f_{i,j}$ 表示删去 $[i,j]$ 所花费的最小代价。

我们进行转移，转移时多枚举一个断点，但是我们这样转移少考虑了一种情况，即枚举断电后，左边一段和右边一段是一起删的。

实际上我们只需要考虑左端点和右端点一起被删的情况，因为如果不是这样的话，显然我们枚举断点可以照顾到，只有左端点和右端点一起被删时，无论怎样枚举断点都无法兼顾这种情况。

考虑到如果左右端点一起被删，那么一定是最后一个被删，我们考虑最后一个删除。

贪心的想，如果左右端点能够被删，就把他们一起删，这样做肯定不会比不把左右节点一起删更差。

如果能删，那么所用次数减 $1$。

所以我们就有了一下转移：

$$
f_{i,j}=\min\limits_{k\in[i,j-1]}(f_{i,k}+f_{k+1,j})-1\times[s[i]=s[j]]
$$

## 代码：

```c++
#define N 510
#define M number
using namespace std;

const int INF=0x3f3f3f3f;

inline int Min(int a,int b){
    return a<b?a:b;
}

inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}

int n,f[N][N];
char s[N];

int main(){
    scanf("%d%s",&n,s+1);
    memset(f,INF,sizeof(f));
    for(int i=1;i<=n;i++) f[i][i]=1;
    for(int i=2;i<=n;i++){//枚举区间长度
        for(int j=1;j<=n-i+1;j++){//枚举左端点
            int l=j,r=j+i-1;
            for(int k=l;k<=r-1;k++){//枚举断点
                f[l][r]=Min(f[l][r],f[l][k]+f[k+1][r]);
            }
            if(s[l]==s[r]) f[l][r]--;//29到32：转移
        }
    }
    printf("%d",f[1][n]);
    return 0;
}
```



---

## 作者：StudyingFather (赞：6)

这是一道非常基础的区间DP题。与其他几篇题解稍有不同，这篇题解的DP采用了记忆化搜索实现。

我们设 $ f_{l,r} $ 代表删除 $ l $ 到 $ r $ 之间的所有字符的最小花费。

那么有两种决策：

1. 单独删掉开头的字符，则 $ f_{l,r} = f_{l+1,r} + 1 $ 。
2. 在串中找到一个与开头字符相同的位置一块删，我们枚举中间位置 $ k $ ，则有 $ f_{l,r} = f_{l+1,k-1}+f_{k,r} $ 。

本题采用记忆化搜索的优点在于，我们无需确定递推的转移顺序，只需按照自然的 dfs 顺序搜索即可。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
char s[505];
int f[505][505];
int dfs(int l,int r)
{
 if(f[l][r]!=-1)return f[l][r];
 if(l==r)return f[l][r]=1;
 if(l>r)return f[l][r]=0;
 f[l][r]=1+dfs(l+1,r);
 for(int i=l+1;i<=r;i++)
  if(s[l]==s[i])f[l][r]=min(f[l][r],dfs(l+1,i-1)+dfs(i,r));
 return f[l][r];
}
int main()
{
 int n;
 memset(f,-1,sizeof(f));
 scanf("%d",&n);
 scanf("%s",s);
 printf("%d\n",dfs(0,n-1));
 return 0;
}
```

---

## 作者：Zechariah (赞：5)

这次的F意外的水啊~~不过我不会就是了~~  
设$dp_{l,r}$表示消除$l$到$r$区间需要的最少次数  
那么我们很容易推出  
1. $dp_{l,r}$可以由$dp_{l+1,r}$或$dp_{l,r-1}$转移过来  
2. 枚举$[l,r]$中间的点$k$，如果$s_k==s_l$，$dp_{l,r}$可以由$dp_{l+1,k-1}$和$dp_{k,r}$转移过来，可以理解为——先消去$[l+1,k-1]$，此时$s_l$与$s_k$相邻了，相当于就是一个字符，然后消去$[k,r]$就消完了  
最后答案$dp_{1,n}$  

```cpp
#include <bits/stdc++.h>
#define lowbit(x) (x&-x)
#define loc(x, y) (x-1)*m+y
#define jh(x, y) x^=y^=x^=y
#define rg register
#define inl inline
typedef long long ll;
const int N = 5e2 + 5, mod = 1e9 + 7, INF = 0x3f3f3f3f;
using namespace std;
namespace fast_IO {
	inl ll read() {
		rg char c;
		rg ll x = 0;
		rg bool flag = false;
		while ((c = getchar()) == ' ' || c == '\n' || c == '\r');
		if (c == EOF)return c; if (c == '-')flag = true; else x = c ^ 48;
		while ((c = getchar()) != ' ' && c != '\n' && c != '\r'&&~c)
			x = (x << 1) + (x << 3) + (c ^ 48);
		if (flag)return -x; return x;
	}
	inl ll max(rg ll a, rg ll b) { if (a > b)return a; return b; }
	inl ll min(rg ll a, rg ll b) { if (a < b)return a; return b; }
	void write(rg ll x) { if (x < 0)putchar('-'), x = -x; if (x >= 10)write(x / 10); putchar(x % 10 ^ 48); }
}
int dp[N][N];
char s[N];

int main(void)
{
	rg int n = fast_IO::read(); scanf("%s", s + 1);
	for (rg int i = 1; i <= n; ++i)dp[i][i] = 1;
	for (rg int len = 1; len <= n; ++len)
		for (rg int i = 1; i <= n - len + 1; ++i)
		{
			rg int l = i, r = i + len - 1;
			dp[l][r] = fast_IO::min(dp[l + 1][r], dp[l][r - 1]) + 1;
			for (rg int k = l; k <= r; ++k)
				if (s[l] == s[k])dp[l][r] = fast_IO::min(dp[l][r], dp[l + 1][k - 1] + dp[k][r]);
		}
	fast_IO::write(dp[1][n]);
	return 0;
}

```


---

## 作者：BMTXLRC (赞：5)

看到这道题大家应该都能马上想到区间 DP，而且这种题大家肯定都做过：

[P4170 [CQOI2007]涂色](https://www.luogu.com.cn/problem/P4170)

[P7414 [USACO21FEB] Modern Art 3 G](https://www.luogu.com.cn/problem/P7414)

以上两道题与这道题是三倍经验，此题的本质与上两题相同，可自行理解。

考虑设 $dp_{i,j}$ 表示 $[i,j]$ 区间需要最少多少次操作。那么就有以下几种情况：

$$
\begin{cases}
dp_{i,i}=1,\\
dp_{i,j}=\min(dp_{i+1,j},dp_{i,j-1}),&s_i=s_j\\
dp_{i,j}=\min(dp_{i,k}+dp_{k+1,j},dp_{i,j}),&s_i\neq s_j
\end{cases}
$$

其中第一条状态转移方程的意思是，每一个单独的字符都需要一次操作，这是初始化。

第二条状态转移方程我举个例子：

$$
s=\texttt{abccb},i=2,j=5
$$

处理到这个长度的时候，其长度减 $1$ 的状态均已处理好，所以相当于 $\tt ccb$ 或 $\tt bcc$ 增加一个字符，而这个字符不会影响答案，因为其两侧的字符相同，从中间消掉则 $i,j$ 必然连在一起，可以由一次操作解决。

第三条状态转移方程就是区间 DP 的标志，不用说了，枚举断点 $k$。

代码如下：

```cpp
//CF1132F
#include<bits/stdc++.h>
using namespace std;
const int N=5e2+5;
char s[N];
int f[N][N],n;
int main(){
    scanf("%d",&n);
	scanf("%s",s+1);
	n=strlen(s+1);
	memset(f,0x7F,sizeof(f));
	for(register int i=1;i<=n;i++) f[i][i]=1;
	for(register int l=1;l<n;l++){
		for(register int i=1,j=1+l;j<=n;i++,j++) {
			if(s[i]==s[j]) f[i][j]=min(f[i+1][j],f[i][j-1]);
			else for(register int k=i;k<j;++k) f[i][j]=min(f[i][j],f[i][k]+f[k+1][j]);
		}
	}
	printf("%d",f[1][n]);
}
```

---

## 作者：mulberror (赞：5)

~~首杀：又是我（蒟蒻）chh~~  
首先丢出自己博客的链接:[传送门1](http://chhokmah.top/2019/03/11/codeforces1132F%20Clear%20the%20String/) [传送门2](https://www.cnblogs.com/chhokmah/p/10508762.html)

---
# 题意
给你一个串s，每次可以花费1的代价删去一个子串，要求子串的每一位为同一个字符。
求删去整个串的最小代价。

----
# 分析
这是一道非常简单的区间$DP$问题，我们定义$f[i][j]$表示删去子串$[i,j]$的最小花费。  
就像合并石子一样，我们枚举中间的$k$，k的范围是$i$~$j$。  
为了方便解决问题，将k的定义域定义成一个半闭半合区间$[i,j)$，或者是$(i,j]$ 都可以，我们题解以$[i,j)$为准。  
决策考虑以下：  
* 如果$s[k]=s[j]$，那么说明当前的区间可以进行消除。
* 反之，则不能消除。  
那么状态转移方程就是：$f[i][j]=min(f[i][j],f[i][k]+f[k+1][j]+1-(s[k]=s[j]))$。

---
# ac代码
```cpp
#include <bits/stdc++.h>
#define N 505
#define inf 0x3f3f3f3f
using namespace std;
char s[N];
int f[N][N];
int len;
int main() {
	scanf("%d%s", &len, s);
	for (int i = 0; i < len; i ++) f[i][i] = 1;
	for (int i = 1; i < len; i ++) 
		for (int j = 0; j < i; j ++) {
			f[j][i] = inf;
			for (int k = j; k < i; k ++) 
				f[j][i] = min(f[j][i], f[j][k] + f[k + 1][i - 1] + 1 - (int)(s[k] == s[i]));
		}
	printf("%d\n",f[0][len - 1]);
	return 0;
}
```

---

## 作者：Nero_Claudius (赞：2)

太久没有搞信息了果然会RP--。

考场竟然没有看出来是区间dp，胡乱打了个贪心，好在其他题问题不大。

---

子状态为$dp[i][j]$表示消除区间$[i,j]$内所有字母所需的最小步数。

我们从两个方向考虑转移。

1. 与上一个状态相比，新的字母不能缩短步数，那么直接加1。

2. 可以缩短步数。那么枚举与哪一个字母相同。

第一种转移为$dp[i][j]=min(dp[i+1][j],dp[i][j-1])+1$。

第二种转移枚举$[i,j]$中的$k$，然后有$dp[i][j]=min(dp[i][j],dp[i+1][k-1]+dp[k][j])$。

在维护上有一个需要注意的细节：因为第一种转移需要$dp[i+1][j]$和$dp[i][j-1]$的数据，所以我们需要先枚举$j$再枚举$i$，同时$j$从大到小枚举。

---

AC代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

namespace StandardIO {

	template<typename T>inline void read (T &x) {
		x=0;T f=1;char c=getchar();
		for (; c<'0'||c>'9'; c=getchar()) if (c=='-') f=-1;
		for (; c>='0'&&c<='9'; c=getchar()) x=x*10+c-'0';
		x*=f;
	}

	template<typename T>inline void write (T x) {
		if (x<0) putchar('-'),x*=-1;
		if (x>=10) write(x/10);
		putchar(x%10+'0');
	}

}

using namespace StandardIO;

namespace Fate {
	
	const int N=1010;
	
	int n;
	char c[N];
	int dp[N][N]; // min steps for clearing [i,j]
	
	inline void Grand_Order () {
		read(n);
		for (register int i=1; i<=n; ++i) {
			cin>>c[i];
			dp[i][i]=1;
		}
		for (register int r=2; r<=n; ++r) {
			for (register int l=r-1; l>=1; --l) {
				dp[l][r]=min(dp[l+1][r],dp[l][r-1])+1;
				for (register int k=l; k<=r; ++k) {
					if (c[l]==c[k]) {
						dp[l][r]=min(dp[l][r],dp[l+1][k-1]+dp[k][r]);
					}
				}
			}
		}
		write(dp[1][n]);
	}
	
}

int main () {
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	Fei_De::Gan_Bu_Guo_Ou_De();
}

```

---

## 作者：Neil_Qian (赞：0)

# Clear the String 题解

给定一个字符串 $S$，每次可以删除它的一个子串，使得子串内的每个元素相等，问最少几次即可将整个字符串删除。

注意到 $|S|\le500$，在加上只有一个字符串，明显可以用区间动态规划解决。

我们用 $dp_{l,r}$ 表示删除 $S$ 的一个区间 $[l,r]$ 的最小次数。如何将 $dp_{l,r}$ 从其它状态转移？我们可以找一个分界点 $k\in[l,r-1]$，则可用两边的次数相加，即 $dp_{l,r}=dp_{l,k}+dp_{k+1,r}$。还有一种情况，如果 $S_l=S_r$ 的话，我们在最后删除 $l$ 或 $r$ 时，把另一边的一起删了就行了，所以 $dp_{l,r}=\min(dp_{l+1,r},dp_{l,r-1})$。

对于 $dp_{i,i}$，也就是一个字符，显然 $dp_{i,i}=1$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define _for(i,a,b) for(int i=(a);i<=(int)(b);i++)
int n,dp[502][502],r;string str;
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);//cin和cout加速
	cin>>n>>str;str=" "+str;//前面加个空格，可以从1开始
	_for(i,1,n)dp[i][i]=1;//[i,i]区间，显然值为1
	_for(i,1,n)_for(j,i+1,n)dp[i][j]=1e9;
	_for(len,2,n)_for(l,1,n-len+1){
		r=l+len-1;//dp过程如上所述
		if(str[l]==str[r])dp[l][r]=min(dp[l+1][r],dp[l][r-1]);//两边相等
		_for(k,l,r)dp[l][r]=min(dp[l][r],dp[l][k]+dp[k+1][r]);//以k为分界点，分成两段
	}
	return cout<<dp[1][n]<<"\n",0;
}
```

---

## 作者：Unordered_OIer (赞：0)

# CF1132F

区间 dp

## Description

每次可以动态删除一个字符相同的子段，求多少次能够删空。

## Solution

可以把题目倒过来看，看作一个 $n$ 个元素的序列，然后每次覆盖一个颜色，看覆盖多少次能全都覆盖掉。

这个问题就是经典的套路题了，设 $f[i][j]$ 表示 $[i,j]$ 全部覆盖的最少次数。

转移方程：

$$f[i][j]=\begin{cases}\min(f[i+1][j],f[i][j-1])&col[i]=col[j]\\\min\limits_{k=1}^{j-1} f[i][k]+f[k+1][j] & col[i] \neq col[j]\end{cases}$$

复杂度 $\mathcal O(n^3)$。

## Code

```cpp
#include<bits/stdc++.h>
#define N 505
#define INF 0x3f3f3f3f
using namespace std;
typedef long long ll;
inline ll read(){
	ll x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
	while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}
inline void write(ll x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)write(x/10);
	putchar(x%10+'0');
}
inline void writeln(ll x){write(x),putchar('\n');}
ll n,c[N],f[N][N];
//区间dp，f[i][j]表示[i,j]最小变换次数 
int main(){
	n=read();
	for(ll i=1;i<=n;i++){
		char ch=getchar();
		c[i]=ch-'a'+1;
		f[i][i]=1;
	}
	for(ll i=n-1;i>=1;i--)
		for(ll j=i+1;j<=n;j++){
			if(c[i]==c[j]){
				f[i][j]=min(f[i+1][j],f[i][j-1]);
			}else{
				f[i][j]=INF;
				for(ll k=i;k<=j-1;k++)
					f[i][j]=min(f[i][j],f[i][k]+f[k+1][j]);
			}
		}
	writeln(f[1][n]);
	return 0;
}
```

---

## 作者：Zxsoul (赞：0)

前言

> 我来发篇题解，因为我愚蠢的错误

**思路**

状态：$f_{i,j}$ 表示区间 $[i,j]$ 删除的最小次数

在转移时，考虑两端点相邻的位置是否相同，这样我们有了

$$
f_{i,j}=\min\{f_{i,j-1},f_{i+1,j}\}+1
$$

不难发现，这存在后效性，即只能判断当前，但不能合并成大区间的最优解，因此我们还需要考虑枚举断点，进行合并，

$$
f_{i,j}=\min\{f_{i,k}+f_{k+1,j-1}\}
$$

此种情况是当 $a[k]=a[j]$ 时，我们可以合并他们区间内的，这样 $k,j$ 就挨在一起了，从而完成了更新，所以上述转移的条件是 $a[k]=a[j]$

**后言**
> 作者用 string 定义，最后答案出去的是 $f_{1,n}$，我一定是疯了



```c
#include <cmath>
#include <queue>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;

const int A = 1e7+10;
const int B = 1e6+10;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

inline int read() {
  char c = getchar();
  int x = 0, f = 1;
  for ( ; !isdigit(c); c = getchar()) if (c == '-') f = -1;
  for ( ; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
  return x * f;
}

int f[3000][3000],n;
string a;

int main()
{
	n=read();
	cin>>a;
	for (int i=0;i<n;i++) f[i][i]=1;
	for (int len=2;len<=n;len++)
		for (int i=0;i+len-1<n;i++)
		{
			int j=i+len-1;
			f[i][j]=min(f[i+1][j],f[i][j-1])+1;
			for (int k=i;k<j;k++)
			{
				
				if (a[j]==a[k])
				{
					f[i][j]=min(f[i][j],f[i][k]+f[k+1][j-1]);
				}
			}
			
		}
	printf("%d",f[0][n-1]);
}
```

---

## 作者：程门立雪 (赞：0)

# Clear the String

>给你一个串$s$，每次可以花费 $1$ 的代价删去一个子串，要求子串的每一位为同一个字符。求删去整个串的最小代价。

**题解：**

设$f[i][j]$表示从$i$到$j$的最小花费。

可以直接删去尾，即$ f[i][j] = min  f[i][j−1] + 1$。

然后枚举中间哪个字符是可以和 $j$位置的字符一起被删去。

假设枚举的位置是$k$，那么$f[i][j] = f[i][k] + f[k+1][j−1]$。

$k$和$j$之间的字母删完，$s_k$就和$s_j$ 就并在一起了。

因为 $s_k = s_j$，所以两个位置可以一起删去。

```c
#include <cstdio>
#include <iostream>
#include <cstring>
#define orz cout << "AK IOI" <<"\n"

using namespace std;
const int maxn = 510;

inline int read()
{
	int x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {if(ch == '-') f = -1; ch = getchar();}
	while (ch >= '0' && ch <= '9') {x = (x << 3) + (x << 1) + (ch ^ 48);ch = getchar();}
	return x * f;
}
int n, f[maxn << 1][maxn << 1];
char s[maxn];
int main()
{
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    n = read();
    cin >> s;
    for(int len = 0; len < n; len++)
    {
    	for(int i = 0; i < n - len + 1; i++)
    	{
    		int j = i + len;
    		f[i][j] = 0x3f3f3f3f;
    		if(i == j) {f[i][j] = 1; continue;}
    		for(int k = i; k < j; k++)
    		{
    			if(s[k] == s[j]) f[i][j] = min(f[i][j], f[i][k] + f[k + 1][j - 1]);
    			else f[i][j] =  min(f[i][j],f[i][j - 1]  + 1);
			}
		}
	}
    printf("%d", f[0][n - 1]);
	return 0;
}
```


---

## 作者：black_trees (赞：0)

区间Dp

---

看到这种可以区间区间删的东西。

直接就可以想到区间DP。

那么设 $f[i][j]$ 表示把 $[i,j) $ 删完 的最小代价。

考虑如何转移。

记得有一道 CQOI 的题，好像是叫涂色来着，和这道题的做法比较像。

那道题的经典思路就是判断 $s[j]=s[k]$ 是否为真，为真即表示这个区间 $[j,k)$ 可以涂上一种颜色。

看到这一道题，我联想到的就是雷同于涂色那道题的做法。

那么还是：判断 $s[j]=s[k]$ 是否为真。

不过这一道题是说直接删去，我们就可以想到，如果上式为真，那么合并这个区间的价值就直接是 $f[i][k]+f[k+1][j]$

反之，我们需要多删去 $s[j]$ 和 $s[k]$ 中的任意一个，那么就要花费 `1` 的代价。

所以不难搞出方程： ` f[i][j]=min(f[i][j],f[i][k]+f[k+1][j]-(int)(s[k]==s[j]));`

还有，边界条件。

我们根据状态的定义，直接把所有的 $f[i][i]$ 都赋值为 `1`。

当然，如果我们在外面初始化了，在转移的时候，如果 $i=j$，我们直接 `continue` 掉就可以了。

代码：

```cpp

#include<bits/stdc++.h>
using namespace std;

const int si=1003;
int n;
char s[si];
int f[si][si];

int main(){
    scanf("%d",&n);
    cin>>s+1;//把字符串长度加一
    memset(f,0x3f,sizeof(f));//先赋一个初值
    for(register int i=1;i<=n;++i){
        f[i][i]=1;
    }
    for(register int len=2;len<=n;++len){
        for(register int i=1;i+len-1<=n;++i){
            register int j=i+len-1;
            if(i==j){
                continue;
            }//i=j直接跳过
            else{
                for(register int k=i;k<j;++k){
                    f[i][j]=min(f[i][j],f[i][k]+f[k+1][j]-(int)(s[k]==s[j]));//转移
                }
            }
        }
    }
    printf("%d",f[1][n]);
    return 0;
}
```


---

## 作者：lgswdn_SA (赞：0)

区间 DP。看数据范围知道应该可以用 $O(n^3)$ 的区间 DP。

有两种删法。第一种直接删除最左侧或右侧的一个字符。$f(l,r)=1+\min f(l+1,r),f(l,r-1)$。

第二种我们看样例一，找一个可以一起合并的字符 $k$。如果 $s_k=s_l$，那么 $k$ 和 $l$ 可以一起合并，$f(l,r)=f(l+1,k-1)+f(k,r)$。为什么不用再算 $s_l=s_r=s_k$ 了呢？因为这种情况相当于先在 $[l,r]$ 中 $l,k$ 一起合并再在 $[k,r]$ 中 $k,r$ 一起合并。为什么不再算 $s_r=s_k$ 了呢？因为这种情况包含在 $f(l,r)=1+f(l+1,r)$ 中。

所以转移方程：

$$
f(l,r)=1+\min f(l+1,r),f(l,r-1)
$$
$$
f(l,r)=\min _{k\in [l,r],s_k=s_l} f(l+1,k-1)+f(k,r)
$$

我这里采用了记搜，尽管常数有一点点的大，但是 ~~我懒~~

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(register int i=a;i<=b;i++)
using namespace std;
const int N=509;

int n,f[N][N];
char s[N];

int dfs(int l,int r) {
	if(f[l][r]) return f[l][r];
	if(l==r) return f[l][r]=1;
	if(l+1==r) return f[l][r]=1+(s[l]!=s[r]);
	if(l>r) return 0;
	f[l][r]=1+min(dfs(l+1,r),dfs(l,r-1)); 
	rep(k,l,r) if(s[k]==s[l])
		f[l][r]=min(f[l][r],dfs(l+1,k-1)+dfs(k,r));
	return f[l][r];
}

int main() {
	scanf("%d%s",&n,s+1);
	printf("%d",dfs(1,n));
	return 0;
}
```

---

