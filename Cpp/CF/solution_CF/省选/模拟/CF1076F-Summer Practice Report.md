# Summer Practice Report

## 题目描述

Vova 今年参加了暑期实习，现在他需要写一份关于实习过程的报告。

Vova 已经画好了所有的表格，也写下了所有的公式。此外，他已经决定报告将由恰好 $n$ 页组成，第 $i$ 页包含 $x_i$ 个表格和 $y_i$ 个公式。页面编号从 $1$ 到 $n$。

Vova 需要依次填写每一页，他不能在完成第 $i$ 页之前去填写第 $i+1$ 页，也不能跳过页面。

然而，如果他连续画超过 $k$ 个表格，或者连续写超过 $k$ 个公式，他就会感到无聊。Vova 想要在每一页内重新排列表格和公式，使得他在填写过程中不会感到无聊。Vova 不能将某个表格或公式移到另一页。

注意，计数在新的一页开始时不会重置。例如，如果某一页以 $3$ 个表格结尾，下一页以 $5$ 个表格开头，那么这被视为连续 $8$ 个表格。

请你帮助 Vova 判断，是否可以在每一页内重新排列表格和公式，使得连续的表格不超过 $k$ 个，连续的公式也不超过 $k$ 个。

## 说明/提示

在第一个样例中，唯一的排列方式如下（用 'T' 表示表格，用 'F' 表示公式）：

- 第 $1$ 页："TTFTTFT"
- 第 $2$ 页："TFTTFTT"

这样所有连续的表格块长度都是 $2$。

在第二个样例中，没有办法排列所有内容，使得连续的表格和公式都不超过 $2$ 个。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2 2
5 5
2 2
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
2 2
5 6
2 2
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
4 1
4 1 10 1
3 2 10 1
```

### 输出

```
YES
```

# 题解

## 作者：skyskyCCC (赞：2)

## 前言。
膜拜递推人，码量精悍，不像我调了好半天。

这个题貌似是某个题的变式，但是具体哪道记不太清了，但是显然这道题是一个很明显的线性 DP 罢了。
## 分析。
考虑动态规划。我们考虑到可以去统计最小值看看是否可以组成，所以我们可以通过统计 ```T``` 和 ```F``` 在某一段区间内的最小值进行剖析。设 $dp\left[i\right]\left[j\right]$ 为在第 $i$ 段中，以 $j$ 字符为结尾的最后一小段长度的最小值。同时 $j$ 只包括两种情况及 ```T``` 和 ```F``` 我们用 $0$ 和 $1$ 来表示。为了以示区分，下文中这两个字符均由 $0$ 或 $1$ 代替。

考虑转移。该状态表示 $dp\left[i\right]\left[0\right]$ 表示组成第 $i$ 段字符，第 $i$ 段以 $0$ 结尾的 $0$ 的最小个数值。然后 $dp\left[i\right]\left[1\right]$ 表示组成第 $i$ 段字符，第 $i$ 段以 $1$ 结尾的 $1$ 的最小个数值。我们考虑将每一段字符的前面的字符和后面的字符看做一个隔板。那么如果现在是该字符串的结尾，则最少的隔板的下限就是 $\lceil\frac{\left(dp\left[i-1\right]\left[j\right]+x_i\right)}{k} \rceil-1$。那么上限是什么呢？如果 $y_i>sum$ 即超过上限，则显然此时的 $dp\left[i\right]\left[j\right]=1$ 所以该隔板个数的上限就是 $x_i\times k$。

如果对于另一种情况，现在是上一个字符串的结尾，则同理隔符数量下界是 $\left\lceil\dfrac{x_i}{k}\right\rceil-1$ 且上限是 $x_i\times k+\left(k-dp\left[i-1\right]\left[j\oplus 1\right]\right)$ 就行了。转移方程就是判断一些上限或下限即可。

最后判断一下统计 $0$ 的最小值的 $dp\left[n\right]\left[0\right]$ 和 $1$ 的最小值的 $dp\left[n\right]\left[1\right]$ 是不是满足题意即可。有一点需要注意，就是在特殊情况下，这两个上限后数据爆炸。比如说 $x_i\times k=10^6\times 10^6=10^{12}$ 所以在比较的时候要强制类型转换。

代码如下，仅供参考：
```
#include<iostream>
#include<algorithm>
#include<cmath> 
using namespace std;
int n,k,x[300005],y[300005];
int dp[300005][2];
int work(int a_fen,int b_fen,int xi,int yi){
	int res=0x3f3f3f3f;
	if(a_fen<=k){
		int sum=(a_fen+xi+k-1)/k-1;
		if(yi==sum){
			res=min(res,a_fen+xi-sum*k);
		}
		else if(yi>sum&&yi<=1ll*xi*k){
			res=min(res,1);
		}
	}
	if(b_fen<=k){
		int sum=(xi+k-1)/k-1;
		if(yi==sum){
			res=min(res,xi-sum*k);
		}
		else if(yi>sum&&yi<=1ll*(xi-1)*k+k-b_fen){
			res=min(res,1);
		}
	}
	return res;
}
int main(){
	cin>>n>>k;
	dp[0][0]=dp[0][1]=0;
	for (int i=1;i<=n;i++){
		cin>>x[i];
		dp[i][0]=0x3f3f3f3f;
	}
	for (int i=1;i<=n;i++){
		cin>>y[i];
		dp[i][1]=0x3f3f3f3f;
	}//初始化DP数组。 
	for (int i=1;i<=n;i++){
		dp[i][0]=work(dp[i-1][0],dp[i-1][1],x[i],y[i]);
		dp[i][1]=work(dp[i-1][1],dp[i-1][0],y[i],x[i]);
	}
	if(dp[n][0]==0x3f3f3f3f&&dp[n][1]==0x3f3f3f3f){
		cout<<"NO\n";
	}
	else cout<<"YES\n";
	return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：WinterRain208 (赞：2)

首先感叹:$CF$紫题大好！

注：本题解有对楼上苣佬思路进行参考，此篇题解大多是补充说明。望大家见谅。

首先，当英文不好的朋友回去看中文翻译的题面，看完之后，相信大家都和我一样：这是啥啊！

在这里，我为大家送上一份完整一些的题面解析。

你要写一篇文章，这篇文章一共$n$页，每页有$t[i]$个字母，其中只有$T$或$F$，有$x[i]$个$T$和$y[i]$个$F$,对于每页，给出一个$T$和$F$的排列，再将所有页上的排列组合在一起，形成一个大字符串，问这个大字符串是否有大于$k$个的连续且相同的字母。

输入分别是第一行$n$,$k$。第二行和第三行分别$n$个数字，$x[i]$和$y[i]$。

如果有输出$NO$,否则输出$YES$。

再帮大家分析以下样例：

样例二：

可能性一：$FFTFFTF$    $FFTFFTFF$

可能性二：$FTFFTFF$    $FFTFFTFF$

因为两个可能性均不符合题意，所以输出否。

题面解析到这里。

具体思路楼上苣佬说的非常清楚了，采用递推大法，正着求解前$i$页的最优组合。

可以再说一遍，$dpx$和$dpy$分别存储前$i$页最佳策略当前页数末尾中$T$的数量和$F$的数量。当其中之一大于$k$时，退出程序，输出否。同时，在第$i$页中要求末尾$T$尽可能少.

# AC CODE

```cpp
#include<bits/stdc++.h>
#define ll long long
#define F(i,j,r) for(int i=j;i<=r;++i)

using namespace std;
const int N=3e5+5;

ll n,dpx[N],dpy[N],x[N],y[N],k;
int main(){
	scanf("%d%d",&n,&k);
	F(i,1,n)cin>>x[i];//读入
	F(i,1,n)cin>>y[i];
	F(i,1,n){//求解
		dpx[i]=max(0ll,x[i]-(k*y[i]-dpx[i-1]));//递推
		dpy[i]=max(0ll,y[i]-(k*x[i]-dpy[i-1]));
		if(dpx[i]>k||dpy[i]>k){
			puts("NO");//判否
			exit(0);
		}
	}
	puts("YES");
    return 0;
}

```

总结来说，这题只是一道递推，如楼上苣佬所说，紫题有些夸张。


---

## 作者：oyoham (赞：1)

### Problem
[CF1076F](https://codeforces.com/problemset/problem/1076/F)
### Solution
观察题目可以发现，维护前 $k$ 个字符串最后合法剩余多少个 `T` 或 `F`。考虑贪心。连续放 $k$ 个对应的字符再放 $1$ 个另外的字符。如样例一摆法如下：  
```
TTFTTFT TFTTFTT
```  
### Proof
（以 `T` 举例，`F` 则交换 $x$ 与 $y$）设上一次剩下 $last_T$ 个，所以这次 `T` 共有 $last_T+x_i$ 个，有 $y_i$ 个 `F`，每个 `F` 最多分出 $k$ 个 `T`，所以总共分出 $k \times y_i$ 个 `T`，新的 $last_T \leftarrow last+x_i-k \times y_i$。  
考虑到最多也只能减到 $0$，所以将 $last_T$ 对 $0$ 取最大值。  
所以 $last_T \leftarrow \max(last+x_i-k \times y_i,0)$。  
如果某一次 $last_T$ 或 $last_F$ 大于 $k$，就不合法了，反之，跑完所有字符串后仍能合法，则可以。这样贪心正确性可以得到证明。
### Code
代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define int ll
inline ll read(){
	ll x=0;
	short f=1;
	char c=getchar();
	while(c>57||c<48){
		if(c==45) f=-1;
		c=getchar();
	}
	while(c<58&&c>47){
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}
inline void write(ll x){
	if(x<0ll) putchar(45),x=~x+1;
	if(x>9ll) write(x/10);
	putchar(x%10|48);
}
int n=read(),k=read();
int T[300005],F[300005];
int tyc,fyc;
signed main(){
	for(int i=1;i<=n;i++) T[i]=read();
	for(int i=1;i<=n;i++) F[i]=read();
	for(int i=1;i<=n;i++){
		int rest=tyc+T[i]-k*F[i];
		int resf=fyc+F[i]-k*T[i];
		if(rest>k||resf>k) return puts("NO"),0;
		else tyc=max(0ll,rest),fyc=max(0ll,resf);
	}
	puts("YES"); 
}
```

---

