# String Coloring (hard version)

## 题目描述

This is a hard version of the problem. The actual problems are different, but the easy version is almost a subtask of the hard version. Note that the constraints and the output format are different.

You are given a string $ s $ consisting of $ n $ lowercase Latin letters.

You have to color all its characters the minimum number of colors (each character to exactly one color, the same letters can be colored the same or different colors, i.e. you can choose exactly one color for each index in $ s $ ).

After coloring, you can swap any two neighboring characters of the string that are colored different colors. You can perform such an operation arbitrary (possibly, zero) number of times.

The goal is to make the string sorted, i.e. all characters should be in alphabetical order.

Your task is to find the minimum number of colors which you have to color the given string in so that after coloring it can become sorted by some sequence of swaps. Note that you have to restore only coloring, not the sequence of swaps.

## 样例 #1

### 输入

```
9
abacbecfd```

### 输出

```
2
1 1 2 1 2 1 2 1 2```

## 样例 #2

### 输入

```
8
aaabbcbb```

### 输出

```
2
1 2 1 2 1 2 1 1```

## 样例 #3

### 输入

```
7
abcdedc```

### 输出

```
3
1 1 1 1 1 2 3```

## 样例 #4

### 输入

```
5
abcde```

### 输出

```
1
1 1 1 1 1```

# 题解

## 作者：ix35 (赞：16)

根据逆序对那套理论，要通过相邻数交换使得序列有序，每一组逆序对必须要交换一次。

所以事实上题目的要求就是如果两个下标 $i,j$ 满足 $i<j$ 并且 $S_i>S_j$，那么 $col_i\ne col_j$，$col_i$ 表示 $i$ 的颜色。

如果对这个模型比较熟悉的话，可以发现它和最长下降子序列有关。

在一个下降子序列 $S_{a_1},\cdots,S_{a_k}$ 中，因为有 $S_{a_1}>S_{a_i}\ \ (i>1)$，所以所有的 $a_i\ \ (i>1)$ 的颜色都和 $a_1$ 不同，同样的，所有 $a_i\ \ (i>2)$ 的颜色都和 $a_2$ 不同，于是我们可以直接得到：下降子序列中元素的颜色两两不同。

因此不同颜色的数量不小于最长下降子序列的长度，下面证明：存在一种染色方案，使得不同颜色的数量等于最长下降子序列的长度。

令 $dp(i)$ 表示后缀 $[i,n]$ 中以 $i$ 开头的最长下降子序列长度，令 $i$ 的颜色为 $dp(i)$，下面论证这种染色方案合法。

对于任意一组逆序对 $(i,j)$，显然有 $dp(i)\ge dp(j)+1$，因为 $j$ 是 $i$ 的转移之一，于是有 $dp(i)\ne dp(j)$，保证了逆序对的颜色不相同。

于是我们得到了一组最小染色方案。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=200010;
int n,ans,dp[MAXN],mx[27];
char c[MAXN];
int main () {
	scanf("%d%s",&n,c+1);
	for (int i=n;i>=1;i--) {
		dp[i]=mx[c[i]-'a']+1;
		for (int j=c[i]-'a'+1;j<=25;j++) {mx[j]=max(mx[j],dp[i]);}
		ans=max(ans,dp[i]);
	}
	printf("%d\n",ans);
	for (int i=1;i<n;i++) {printf("%d ",dp[i]);}
	printf("%d\n",dp[n]);
	return 0;
}
```


---

## 作者：dz_ice (赞：3)

[欢迎来看看呀](https://www.cnblogs.com/dzice)

题目大意：给你一串长度为n的字符串,你可以给每个位置上染上一种不大于n的颜色,对于相邻的两个位置，如果他们的颜色不同则可以交换他们的位置,现在需要交换若干次后按照字典序排序,你需要找到最少满足条件的颜色数并输出方案

可以想到，只有一个字符要与另一个字符交换，才要染成不同颜色，从前往后来考虑，我们只用考虑一个字符与在它前面的字符交换就行了，因为枚举到后面需要与其交换的字符，自然会考虑到它

只有比它大的字符才会跟它交换，所以我们只需要让它与比它大的字符不同颜色即可

然后要想到这样的一个结论，这一些字符的颜色必然在$[1,x]$这样的一个区间里，而且包含着$[1,x]$中的每一种颜色，所以我们对于枚举到的字符，找到对应的$x$,然后把枚举到的字符的颜色设为$x+1$即可

我一开始还想写权值线段树，结果一想只有26个字符，暴力就完事了，复杂度$O(26*n)$

代码很简单，如果有不理解的我相信看一看代码你就懂了

```
#include<bits/stdc++.h>
using namespace std;
int n,a[200003],maxx[200],maxxx=0,ans[200003],col;
char c;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		cin>>c;
		a[i]=c-'a'+1,maxxx=0;
		for(int j=a[i]+1;j<=26;j++)
			maxxx=max(maxxx,maxx[j]);
		ans[i]=maxxx+1,col=max(col,ans[i]);
		maxx[a[i]]=max(maxx[a[i]],maxxx+1);
	}
	cout<<col<<endl;
	for(int i=1;i<=n;i++)
		cout<<ans[i]<<" ";
	return 0;
}
```

---

## 作者：FutaRimeWoawaSete (赞：2)

**CF1296E2 sol**

如果要冒泡排序，则显然两个逆序对至少被交换一次。

即如果 $i < j$ 且 $s_i \leq s_j$ 它们是可以被划分为一个颜色的。

那么我们将序列划分成最少的不下降子序列组即为颜色的最小种类数。

考虑运用 Dilworth 定理，则显然，问题变成了求最长下降子序列长度。

构造时将每个位置的颜色划为以 $i$ 开头的最下降子序列长度是一组合法方案，因为这样保证任何的逆序对所属颜色不相同。

```cpp
#include "bits/stdc++.h"
using namespace std;
const int Len = 2e5 + 5;
int n,m,mx[28],dp[Len],as;
char s[Len];
int main()
{
	scanf("%d",&n);
	scanf("%s",s + 1);
	for(int i = n ; i >= 1 ; i --) 
	{
		dp[i] = 1;
		for(int j = 0 ; j < s[i] - 'a' ; j ++) dp[i] = max(dp[i] , mx[j] + 1);
		mx[s[i] - 'a'] = dp[i];
		as = max(as , dp[i]);
	}
	printf("%d\n",as);
	for(int i = 1 ; i <= n ; i ++) printf("%d ",dp[i]);
	return 0;
}
```

---

## 作者：奇米 (赞：2)

## 题解- CF1296E2

* **题目意思**
	
    就是要给每个位置分配一种颜色，使得不同的颜色相邻的字符可以完成交换位置。求一种合理的方案。
    
* $Sol$
	
   思维题。
   其实发现几个显然的性质就很容易啦。
    
   对于一段相同或者递增的串只要使得他们相同即可，因为不需要进行交换，可以随意填色。但是值得注意的是，如果一个串长成$eaabb$此时就要保证$a,b$的颜色要不同于$e$因为要使得$e$交换上来。所以对于这次要填的颜色只要暴力找出比它大的最大值即可，复杂度$O(n*26)$。
   
* $Code$

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N=2e5+5;

int n,m,ans[N],ton[105],tot=1,mx;
int main()
{
	scanf("%d",&n);
	for ( int i=1;i<=n;i++ ) 
	{
		char c;
		cin>>c;
		mx=0;
		for ( int j=(c-'a'+2);j<=26;j++ ) mx=max(mx,ton[j]);
		ans[i]=mx+1;
		ton[c-'a'+1]=max(ton[c-'a'+1],mx+1);
		tot=max(tot,ans[i]);
	}
	printf("%d\n",tot); 
	for ( int i=1;i<=n;i++ ) printf("%d ",ans[i]);
	return 0;
}
```



---

## 作者：XL4453 (赞：1)

### 解题思路：

对于每一个字母，这个字母要和前面的某一个字母的颜色不同，当且仅当字典序大的那一个字母在前面，字典序小的在后面。

那么考虑将每一个点的颜色设置为恰好比要其必须与之交换的点的颜色的最大值加一。

这样的话每一个点一定能归到其应该在的位置，而后面的如果要交换也一定可以找到另外的，所以不需要在前面就预先考虑好。

---

实现上，将所有的字母的最高颜色标号离线下来，然后对于每一个字母直接在字母表里找最大的就行了。

这样做单次复杂度是 $O(1)$，总复杂度是 $O(n)$ 的，也就避免了从前往后找导致总复杂度达到 $O(n^2)$ 而超时的情况。

---

需要注意的是，不可以考虑将某一种字母全都替换成单一颜色，这样的话由于前后部分颜色重合，可能会导致算多了的情况。

---
### 代码：

```
#include<cstdio>
#include<algorithm>
using namespace std;
int n,num[30],now[200005],ans;
char a[200005];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		a[i]=getchar();
		while(a[i]>'z'||a[i]<'a')a[i]=getchar();
		for(int j=a[i]-'a'+1;j<=26;j++)num[a[i]-'a']=max(num[a[i]-'a'],num[j]+1);
		now[i]=num[a[i]-'a'];
		ans=max(ans,num[a[i]-'a']);
	}
	printf("%d\n",ans);
	for(int i=1;i<=n;i++){
		printf("%d ",now[i]);
	}
	printf("\n");
	return 0;
}
```


---

## 作者：DengDuck (赞：0)

首先我们可以发现这题就是划分出最少的 LIS。

根据一个 D 什么的定理（Dilworth’s Theorem）：
- 我们假设这是一张图，一个点向它后面的所有比它小的点连边。
- 问题变成最小链覆盖。
- 最小链覆盖就是最大反链。
- 最大反链在这里等同于最长下降子序列。

我们可以得到这就是求最长的最长下降子序列。

然后直接利用值域小的性质直接记录前缀最大值优化 DP 就行。

求方案咋求也比较简单想。


```cpp
#include<bits/stdc++.h>
#define LL long long
#define LF long double
#define pLL pair<LL,LL>
#define pb push_back
#define LowBound lower_bound
#define UpBound upper_bound
//#define Fi first
//#define Se second
//#define Ls(x) (x<<1)
//#define Rs(x) (x<<1|1)
//#define Ls(x) t[x].Lson
//#define Rs(x) t[x].Rson
using namespace std;
//const LL Inf;
const LL N=2e5+5;
//const LL M;
//const LL Mod;
//const LF eps;
//const LL P;
LL n,Ans,F[N],Mx[26];
char C[N];
int main()
{
	scanf("%lld%s",&n,C+1);
	for(int i=n;i>=1;i--)
	{
		F[i]=Mx[C[i]-'a']+1;
		for(int j=C[i]-'a'+1;j<26;j++)Mx[j]=max(Mx[j],F[i]);
		Ans=max(Ans,F[i]);
	}
	printf("%lld\n",Ans);
	for(int i=1;i<=n;i++)printf("%lld ",F[i]);
	return 0;
}
//RP++
```

---

## 作者：Merge_all (赞：0)

## 思路：
- 这道题其实就是让逆序对颜色不同，所以我们可以用一个 $sum$ 数组记录字符染色**最大值**，对于每一个位置，枚举**比它大的已经出现过的字母就是逆序对**，所以当前位置的染色值必然是比它大的字母的染色值中**最大值**加 1，最后输出即可。

```
#include<bits/stdc++.h>

using namespace std;

const int N=200010;

int n,cnt=1,Max;
char s[N];
int ans[N],sum[N];

signed main(){
	scanf("%d%s",&n,s+1);
	ans[1]=1;
        sum[s[1]]=1;
	for(int i=2;i<=n;i++){
		Max=0;
		for(int j=s[i]+1;j<='z';j++) Max=max(Max,sum[j]);
		ans[i]=Max+1;
		cnt=max(cnt,ans[i]);
		sum[s[i]]=max(sum[s[i]],ans[i]);
	}
	cout<<cnt<<"\n";
	for(int i=1;i<=n;i++) cout<<ans[i]<<" ";
	return 0;
}
```

---

## 作者：yaaaaaan (赞：0)

### 思路
这道题其实就是让逆序对颜色不同，所以我们可以用一个 $a$ 数组记录字符染色最大值，对于每一个位置，**枚举比它大的已经出现过的字母就是逆序对**，所以当前位置的染色值必然是比它大的字母的染色值中最大值加 $1$，最后输出即可。
### code
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,a[26],b[200001];
string s;
signed main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>s;
	for(int i=0;i<n;i++)
	{
		int maxx=0;
		for(int j=s[i]-'a'+1;j<='z'-'a';j++)
		{
			maxx=max(maxx,a[j]);
		}
		b[i]=maxx+1;
		a[s[i]-'a']=max(a[s[i]-'a'],b[i]);
	}
	int maxx=0;
	for(int i=0;i<n;i++)
	{
		maxx=max(maxx,b[i]);
	}
	cout<<maxx<<"\n";
	for(int i=0;i<n;i++) cout<<b[i]<<" ";
	return 0;
}
//aa

```

---

## 作者：WorldMachine (赞：0)

逆序对一定要被交换，所以一定会被染成不同的颜色。因此，最小的颜色数，就等于将字符串拆成若干个不下降子序列的最小个数。

由 Dilworth 定理得，答案为最长下降子序列的长度。

题目还要求构造答案，可以将位置 $i$ 染成以 $i$ 结尾的最长下降子序列长度，这样既可以保证颜色不超过 $n$，逆序对也不会被染成同样的颜色。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
int n, c, f[N], g[26];
char s[N];
int main() {
	scanf("%d%s", &n, s + 1);
	for (int i = 1, m; i <= n; i++) {
		m = 1;
		for (int j = s[i] - 'a' + 1; j < 26; j++) m = max(m, g[j] + 1);
		g[s[i] - 'a'] = f[i] = m, c = max(c, m);
	}
	printf("%d\n", c);
	for (int i = 1; i <= n; i++) printf("%d ", f[i]);
}
```

---

## 作者：_HCl_ (赞：0)

非常不错的小清新题。
## CF1296E2 题解

**题意简述**

给长度为 $n$ 的字符串染色。染色后进行如下操作：对于相邻的两个位置，若颜色不同就可以进行交换。求最小的染色数，使得存在若干次操作后字符串可以按字典序排列。

**思路引导**

不难发现这个操作其实就是一个冒泡排序。但是为了使得需要的交换可以完成，必须使得原始序列中，每个逆序对的颜色不同。

容易想到可以将序列分解成若干个不交的不降子序列，给每个不降子序列染上相同的颜色。那么最少的染色数就是分解成的不降子序列数量的最小值。

根据 Dilworth 定理，不降子序列数量最小值等于最长下降子序列的长度。所以我们只用求出最长下降子序列的长度即可。

可以使用线段树优化 DP，时间复杂度为 $\mathcal{O}(n\log n)$。

另外，我们在 DP 的过程中求出的 $f_i$（以 $a_i$ 为结尾的最长下降子序列长度），其实就可以作为染色方案。对于这个，读者可自行理解。

**代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,N=27;
string str;
int a[200005],f[200005],t[10001];
int query(int x,int l,int r,int L,int R){
	if(L<=l&&r<=R)return t[x];
	int mid=(l+r)>>1,ret=0;
	if(L<=mid)ret=max(ret,query(x<<1,l,mid,L,R));
	if(R>mid)ret=max(ret,query(x<<1|1,mid+1,r,L,R));
	return ret;
}
void update(int x,int l,int r,int p,int k){
	if(l==r){
		t[x]=max(t[x],k);
		return;
	}
	int mid=(l+r)>>1;
	if(p<=mid)update(x<<1,l,mid,p,k);
	else update(x<<1|1,mid+1,r,p,k);
	t[x]=max(t[x<<1],t[x<<1|1]);
}
int main(){
	cin>>n;
	cin>>str;
	for(int i=0;i<str.length();++i)a[i+1]=str[i]-'a'+1;
	for(int i=1;i<=n;++i){
		f[i]=query(1,1,N,a[i]+1,N)+1;
		update(1,1,N,a[i],f[i]);
	}
	int ans=0;
	for(int i=1;i<=n;++i)ans=max(ans,f[i]);
	cout<<ans<<"\n";
	for(int i=1;i<=n;++i)cout<<f[i]<<" ";
	return 0;
}
```

---

## 作者：_masppy_ (赞：0)

### 题目链接：[Link](https://www.luogu.com.cn/problem/CF1296E2)

&nbsp;

### 题目大意：
给定一个长度为 $n$ 的字符串，现在你需要给字符串中的所有字符染色，染色后拥有不同颜色的相邻字符可以相互交换，交换可以进行若干次。现在需要你给出最少需要的颜色数量，并给出一种染色方案，使得对于字符串中的字符进行若干次如上的交换操作后，字符串中的字符按照字典序从左到右排列

&nbsp;

### 解题思路：
根据 `Easy version` 的结论可以得出，所有的颜色一致的数一定构成不下降子序列。也就是说染色本质上便是把原字符串划分成若干个不下降子序列。同时可以保证的是不下降子序列的端点越靠右，则右端点的字典序一定越小，且每个不下降子序列的右端点一定不相等。

由此不难发现，对于一个下降子序列，其中的所有字符一定不会被染成同种颜色，于是便可以将问题转化为一个求最长下降子序列的问题，由于字符字典序的值只有 $26$ 个，因此我们可以对于每种字符维护，对于每种字符记录所有字典序大于它的字符的最长下降子序列长度，然后在此基础上 $+1$ 即可。

表述可能有些不清楚，可以结合代码理解一下：
```cpp
int main(){
	//freopen("test.in","r",stdin);
	scanf("%d",&n);
	scanf("%s",c+1);
	
	int ans=0;
	for(int i=1;i<=n;i++){
		dp[i]=a[c[i]-'a']+1;//a数组记录所有以字典序大于c[i]且位置更靠前的字符的最长下降子序列
		
		for(int j=0;j<c[i]-'a';j++) a[j]=max(a[j],dp[i]);//更新所有字典序小于c[i]的答案
		ans=max(ans,dp[i]);//找最大长度 
	}
	
	printf("%d\n",ans);
	
	for(int i=1;i<=n;i++) printf("%d ",dp[i]);
	return 0;
}
```


---

## 作者：Milmon (赞：0)

[in Blog](//milk-lemon.blog.luogu.org/solution-CF1296E2) & [Problem](//www.luogu.com.cn/problem/CF1296E2)

## 题目大意

- 给定一个长度为 $n$ 的字符串 $s$，要求给每个字母染色，使得可以通过若干次操作让字符串的字母按字典序升序排列，其中每次操作可以交换两个相邻的不同色的字母。求符合条件的所需颜色总数，并给出构造方案。

- $1\leq n\leq 2\times 10^5$

## 解题思路

容易发现字典序大的字母若出现在字典序小的字母前面，则为了让字符串的字母按字典序升序排列，必有一步需要将这两个字母进行交换，故这两个字符颜色不能相同。

从前往后处理字符。设已处理的字符中，字符 $c$ 的颜色最大是 $maxn_c$，且即将要处理的这个字符为 $c_0$。考虑已处理的字符中字典序大于 $c_0$ 的字符，为保证该字符的颜色不与它们的颜色相同，不妨令这个字符 $c_0$ 的颜色为

$$
\max_{i=c_0+1}^\texttt{z}maxn_i+1.
$$

我们只需维护数组 $maxn$，即可在 $\Theta(C)$（$C=26$ 为字符集大小）的时间复杂度内处理一个字母。时间复杂度 $\Theta(nC)$。

## AC 代码

```c++
#include<bits/stdc++.h>
using namespace std;

int n,maxn['z'+1],ans[200001],color;
string str;

int main(){
    cin>>n>>str;
    for(int i=0;i<n;i++){
        int tmp=1;
        for(int j=str[i]+1;j<='z';j++)
            tmp=max(tmp,maxn[j]+1);
        ans[i]=tmp,maxn[str[i]]=tmp;
        color=max(color,tmp);
    }
    printf("%d\n",color);
    for(int i=0;i<n;i++)
        printf("%d ",ans[i]);
    printf("\n");
    return 0;
}
```

---

## 作者：QianianXY (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1296E2)

## 标签

- 简单构造

## 题目分析

思考“颜色”真正的含义，可以得出两条性质：

1. 当两个字母颜色不同时，意味着它们有交换的必要。否则它们完全可以涂上相同的颜色。

2. 当一组字母颜色相同，意味着从开始到排序完成，它们之间的**相对顺序**都不会改变。

显然，一组字母相对顺序不变，只能是它们之间已经符合排序规则了，即单调递增。

所以性质 2 逆着来，就是构造方案了：

1. 在总序列中提取一组单调递增的子序列（**不一定连续**），标上同样的颜色，然后从总序列中删除。

2. 重复上述步骤，直到总序列为空。

那要如何实现呢？应该都能想到。

涉及到线性序列的删除和多次访问，用链表就好了。

复杂度 $O(n)$。

## code

```cpp
#include <bits/stdc++.h>
#define rei register int
#define N 500010
using namespace std;

template <typename T> inline void read(T &x)
{
	x = 0; int f = 1; char ch = getchar();
	while (!isdigit(ch)) {if (ch == '-') f = -f; ch = getchar();}
	while (isdigit(ch)) {x = x * 10 + ch - 48; ch = getchar();}
	x *= f;
}

int n, nxt[N], len, cnt, lst, col, co[N], fr;
char s[N];

int main()
{
	read(n); scanf("%s", s + 1); len = strlen(s + 1);
	for (rei i = 1; i <= len; i++) nxt[i] = i + 1; nxt[0] = 1;
	while (cnt < n)
	{
		lst = 0; col++; fr = 0;
		for (rei i = nxt[0]; i; i = nxt[i])
		{
			if (s[lst] <= s[i]) co[i] = col, lst = i, nxt[fr] = nxt[i], cnt++;
			else fr = i;
		}
	}
	printf("%d\n", col);
	for (rei i = 1; i <= n; i++) printf("%d ", co[i]);
	return 0;
}
```

---

## 作者：Nightingale_OI (赞：0)

比较简单的题。

------------

显然，如果 $ s_j < s_i $ 且 $ i < j $，那么它们一定要交换，不然无法排序。

并且，如果只交换上述位置，一定是可以按字典序排序的。

对于每一个位置，我们贪心地选择可行的颜色中最小的即可。

当一个位置选择了颜色后，后面所有字典序小于它的位置不能选择该颜色，可以用链表来维护。

------------

代码如下 （~~非常简单~~)：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,s,l;
const int maxn=202020;
struct list_ex{
    int v[maxn],l[maxn],r[maxn];
    inline void init(register const int& n){for(register int i=1;i<=n;++i){v[i]=1;l[i]=i-1;r[i]=i+1;}r[0]=1;l[n+1]=n;}
    inline void del(register const int& x){if(!v[x])return;v[x]=0;l[r[x]]=l[x];r[l[x]]=r[x];}
    inline int head(){return r[0];}
    inline int tail(){return l[n+1];}
}a[26];
int b[maxn];
char c[maxn];
int main(){
    cin>>n;
    scanf("%s",c+1);
    for(register int i=0;i<26;++i)a[i].init(n);
    for(register int i=1;i<=n;++i){
        b[i]=a[c[i]-'a'].head();
        if(b[i]>s)s=b[i];
        for(register int j=c[i]-'a'-1;~j;--j)a[j].del(b[i]);
    }
    printf("%d\n",s);
    for(register int i=1;i<=n;++i)printf("%d ",b[i]);
    return 0;
}
```

---

