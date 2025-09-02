# String painter

## 题目描述

有两个仅含有小写字母的等长字符串 $A$ 和 $B$，每次操作可以将 $A$ 的其中一个子串的所有位置修改为同一个任意字符。求将 $A$ 覆盖成  $B$ 的最小操作次数。

$1\le |a |=|b|\le100。$

## 样例 #1

### 输入

```
hfcnndeziymohaewnrbmquyhigwm
bcbysbjvxbzvmspshggrzaukbipm
jmmeqimjobpxyavjneyvyuuhhwiqowmme
kmpgpviubhzrjkezqqoilsuwgedctxkxl
ikynfrlcsltkrbdkdqpirtdnajhzhbhipeqtyxvskhkti
qmziwxbbjzjfymrzvflthsbaqgdoqmiduiudviqzztclb
vwysgqniecydcycqk
cqgudqbkgcsvimpdj
mcrrqwfegpnukyuk
vezrniuriscgtcth
rdjtgk
wzfycu
nwxqfdtigwj
rrhcndwcohx
knjmrwlwxfroyppgxhrknntrvbcqjrranufutrginldqydsjsfyjqfyqq
lghrdjsgvbffgfpclqmrzzoniyhlsoisgpbfdqpiblsbtirrbdjdjxsuy
nujagihmgqvwiwvbmbe
pnxicvskosnzneztzhd
bzjvffvyv
mnvjbgwdw```

### 输出

```
20
26
33
15
13
6
8
43
15
8```

# 题解

## 作者：Mickey_snow (赞：25)

　这题大体的思路比较好想，就是一个动态规划。

　不过，由于我们是要把一个字符串刷成另外一个字符串，那么这个字符串当中有一部分可能已经是另外的那个字符串中相同的一部分了。换句话说，记这两个字符串为A和B.那么有可能存在A\[i] == B\[i].那么这些字符在我们还没有开始使用刷子的时候就已经是符合要求的了。假如A和B相同，那么我们根本就不需要使用刷子。

　可见，由于A和B中字符的不确定性，我们并不能够轻易地定义出状态并写出状态转移方程。但是，如果换一个思路考虑就可以简化问题。

　假设有一个全部由空格组成的字符串，与A和B的长度相等，我们记这个字符串为E.由于空格并不存在与A或者B中，所以可以把E理解成每一个字符都和相同位置的A或B的字符都不相同。我们尝试将E刷成B.
```cpp
	int D[][];
```

　定义一个二维数组D\[i]\[j] = E中i到j刷成和B中i到j相同需要刷的最小次数.

　那么显而易见
```cpp
	D[i][i] = 1;
```

　假如B中存在两个字符是相同的，那么其实还有另外一种刷法。不妨设
```cpp
	B = "a b u d i s p b m l  k  j"
	E = "_ _ _ _ _ _ _ _ _ _  _  _"
	[]   1 2 3 4 5 6 7 8 9 10 11 12
```

　在这里，B中有两个相同的字符b.那么我们可以先把E\[8-12]刷成与B一样的，由于我们肯定有一次使用刷子是把E\[8]刷成了'b'，那么在这一次使用刷子的时候，可以顺便把E\[4-7]全部变成'b',那么
```cpp
	B = "a b u d i s p b m l  k  j"
	E = "_ b b b b b b b m l  k  j"
	[]   1 2 3 4 5 6 7 8 9 10 11 12
```
　随后，再刷E\[3-7].这样，转移方程就呼之欲出了。
```cpp
	//枚举i,j。i从后往前，j从i往后。
	D[i][j] = D[i + 1][j] + 1;
	//在i + 1和j之间枚举k.作为切分的位置。
	if(B[i] == B[k])
		D[i][j] = min(D[i][j], D[i + 1][k - 1] + D[k][j]);
```

 　接下来处理从A刷到B.定义Dp\[i] = A前i个字符刷成与B前i个字符相同需要刷的最小次数。那么
```cpp
	Dp[i] = D[1][i];
```

　前面提到，如果A中有某些字符在一开始就和B中相同位置的字符一样，那么这些字符就可以不用刷 前面提到，如果A中有某些字符在一开始就和B中相同位置的字符一样，那么这些字符就可以不用刷。
```cpp
	if (A[i] == B[i])
		Dp[i] = (i == 1 ? 0 : Dp[i - 1]);
```

　同样地，我们还是枚举一下k，作为切分的位置。可以先将A\[1-k]刷成B\[1-k],然后再把A\[k+1-i]当作E\[k+1-i]来刷。
```cpp
	Dp[i] = min(Dp[i],  Dp[k] + D[k + 1][i]);
```

　
 
　完整的程序如下。

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read() {
	int X = 0, w = 0; char ch = 0;
	while (!std::isdigit(ch)) { w |= ch == '-'; ch = std::getchar(); }
	while (std::isdigit(ch)) X = (X << 3) + (X << 1) + (ch ^ 48), ch = std::getchar();
	return w ? -X : X;
}
template<typename T>
inline void write(T x) {
	if (x < 0) std::putchar('-'), x = -x;
	if (x > 9) write(x / 10);
	std::putchar(x % 10 + '0');
}
template<typename T>
inline void writeLine(T x) {
	write(x);
	std::putchar('\n');
}
template<typename T>
T min_(T& numb, T comp) {
	if (comp < numb) { numb = comp; return comp; }
	else return numb;
}

int main()
{
	char A[105], B[105];
	int len;
	int D[105][105], Dp[105];

	while (scanf("%s%s", B + 1, A + 1) == 2)
	{
		len = strlen(A + 1);

		memset(D, 0, sizeof(D)); 
		memset(Dp, 0, sizeof(Dp));

		//Dp1
		for (int i = 0; i <= len; i++)D[i][i] = 1;
		for (int i = len - 1; i > 0; i--)
			for (int j = i + 1; j <= len; j++) {
				D[i][j] = D[i + 1][j] + 1;
				for (int cut = i + 1; cut <= j; cut++)
					if (A[i] == A[cut])
						min_(D[i][j], D[i + 1][cut - 1] + D[cut][j]);
			}

		//Dp2
		for (int i = 1; i <= len; i++) {
			Dp[i] = D[1][i];
			
			if (A[i] == B[i])
				Dp[i] = (i == 0 ? 0 : min_(Dp[i], Dp[i - 1]));

			else {
				for (int cut = 1; cut < i; cut++)
					min_(Dp[i], Dp[cut] + D[cut + 1][i]);
			}
		}

		writeLine(Dp[len]);
	}

	return 0;
}

```

---

## 作者：ListenSnow (赞：14)

## 题意

有两个用小写英文字母组成的**等长**字符串。你有一个强大的字符串刷子，在这把刷子的帮助下，你可以将一个字符串的一个字串中的字符全部刷成任何你想要的字符。也就是说，用刷子刷过的字串就变成用同一个字母组成的了。现在你想要用这一把刷子把字符串A刷成B，而且要求刷的次数最少。

## 思路

本题的题意与[涂色](https://www.luogu.com.cn/problem/P4170)类似。不同之处在于本题有些位置上的字符本身就相等，没必要修改。

可以发现如果修改的两个区间是相交的关系，那么这个交区间就等价于只修改了后一次，那么前一次修改的区间就没必要再包含这个交区间了。于是就可以知道，一定存在一组最优解，使得所有修改的区间的关系只有包含和无交集。那么就可以用**区间 dp**解决本题。

设 $f[i][j]$ 表示将 A 转化为 B 时不考虑本身相等的字符所需的最少修改次数。得到其中一个状态转移方程：

$f[i][j]=\min(f[i][k]+f[k+1][j])$。

此外，如果两个端点的字符相等，那么就可以将扩大修改的边界，即：

$f[i][j]=\min(f[i+1][j],f[i][j-1])$。

接下来考虑不需要修改的情况。不难发现，把相等的字符去掉后，就剩下了若干个子区间。那么就可以从前往后考虑是否需要断开区间。用 $g[i]$ 表示将 $[1,i]$ 的字符串修改成一致所需的最少次数。得到状态转移方程：

$g[i]=\min(g[j]+f[j+1][i])$。

如果此时不需要修改，即满足 $a[i]=b[i]$ 时，得到：

$g[i]=g[i-1]$。

## code：

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=110,INF=0x3f3f3f3f;
int n,f[N][N],g[N];char a[N],b[N];
int main()
{
	while(scanf("%s%s",a+1,b+1)==2)
	{
		memset(f,0x3f,sizeof(f));n=strlen(a+1);
		for(int i=1;i<=n;i++) f[i][i]=1;
		for(int len=2;len<=n;len++)
		    for(int l=1,r=l+len-1;r<=n;l++,r++)
		    {
		    	if(b[l]==b[r]) f[l][r]=min(f[l][r-1],f[l+1][r]);
		    	for(int k=l;k<r;k++) f[l][r]=min(f[l][r],f[l][k]+f[k+1][r]);
			} 
		for(int i=1;i<=n;i++)
		{
			g[i]=f[1][i];
			if(a[i]==b[i]) g[i]=min(g[i],g[i-1]);
			for(int j=1;j<i;j++) g[i]=min(g[i],g[j]+f[j+1][i]);
		}
		printf("%d\n",g[n]);
	}
	return 0;
}
```


---

## 作者：浅夜_MISAKI (赞：7)

##### 首先呢这道题是个区间DP（别问我怎么知道的233）
两个字符串一起处理会非常脑壳疼，所以我们分步处理

现将空白串改成目标串，然后a串与空白串的优点在于a串有一部分和b串是一样的没必要再刷

所以先预处理出dp[i][j]表示空白到目标串i到j的最少次数，这是第一个区间DP，可以模仿poj的brackets那道题的思想

然后用一个ans表示0~i的答案是多少，显然这还是个区间DP；
ans[i]=min(ans[i],ans[k]+dp[k+1][i])(1<=k<=i-1);
#注意ans[i]最后要和dp[0][i]进行比较，不然第一个样例都过不了
#还有这是多组数据哦，记得memset

AC代码在此
```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#define _ 0
#include<string>
using namespace std;
char a[150],b[150];
int dp[150][150],ans[150];
int n;//0->b ; b->a
int main()
{
	//freopen("misaki.in","r",stdin);
	//freopen("misaki.out","w",stdout);
	while(scanf("%s%s",a+1,b+1)==2)
	{
		memset(dp,0x7f,sizeof(dp));//清数组清数组
		memset(ans,0x7f,sizeof(ans));//清数组清数组
		n=max(strlen(a+1),strlen(b+1));
		for(int i=1;i<=n;i++)dp[i][i]=1;
		for(int len=2;len<=n;len++)
		{
			for(int i=1,j;i+len-1<=n;i++)
			{
				j=i+len-1;
				if(b[i]==b[j])dp[i][j]=max(dp[i+1][j],dp[i][j-1]);
				else
				{
					for(int k=i;k<=j-1;k++)
					{
						dp[i][j]=min(dp[i][j],dp[i][k]+dp[k+1][j]);
					}
				}
			}
		}//第一个区间DP
		if(a[1]==b[1])ans[1]=0;else ans[1]=1;
		for(int i=2;i<=n;i++)
		{
			if(a[i]==b[i])ans[i]=min(ans[i-1],ans[i]);
			else
			{
				for(int k=1;k<=i-1;k++)
				{
					ans[i]=min(ans[i],ans[k]+dp[k+1][i]);
				}
			}
			ans[i]=min(ans[i],dp[1][i]);//这个不要忘了
		}//第二个区间DP
		printf("%d\n",ans[n]);
	}
	return ~~(0^_^0);//卖萌专用
}
```

---

## 作者：Hisaishi_Kanade (赞：4)

A 涂成 B 似乎很困难，不如先考虑从空串涂成 B 串。这个问题是非常简单的。

你直接设 $f_{i,j}$ 表示把 B 的 $[i,j]$ 涂好的最小次数，那么当 $b_i=b_j$ 的时候只要在涂 $i$ 的时候多涂一点就可以了，$f_{i,j}=f_{i,j-1}$。

否则枚举断点，$f_{i,j}=\min\{f_{i,k}+f_{k+1,j}\}$。

那么如何再改成从 A 涂成 B 呢，设 $f^{\prime}_{i}$ 表示把 A 前 $i$ 个符号刷好。

当 $a_{i}=b_i$ 的时候，这个就不需要刷了，即 $f^{\prime}_{i}=f^{\prime}_{i-1}$。否则，还是枚举断点，将后面某一段当成空串刷，也就是 $f^{\prime}_{i}=\min\{f^{\prime}_{k}+f_{k+1,i}\}$。

那么先处理出 $f$ 然后处理出 $f^{\prime}$。答案显然 $f^{\prime}_n$。

```cpp
/*
首先考虑空串转成 B，这个是 simple 的。
f[i][j] 表示把 [i,j] 都转的答案。
f[i][j]=f[i][j-1] (b[i]==b[j])
        f[i][k]+f[k+1][j] (otherwise)
如果是 A 转成 B 是否是类似的呢？
不如钦定从左边开始刷，那么如果 a[i] 和 b[i] 相同，就是 粉刷 [1,i-1] 的价值，
否则其实就是刷空串了。
*/
#include <stdio.h>
#include <string.h>
const int N=505,inf=1<<30;
char a[N],b[N];
int f[N][N],dp[N];
int i,j,len,k,n;
inline int min(int x,int y)
{
	return x<y?x:y;
}
void solve()
{
	n=strlen(a+1);
	for(i=1;i<=n;++i)for(j=1;j<=n;++j)f[i][j]=inf;
	for(i=1;i<=n;++i)f[i][i]=1,dp[i]=inf;
	for(len=2;len<=n;++len)
		for(i=1;i+len-1<=n;++i)
		{
			j=i+len-1;
			if(b[i]==b[j])
				f[i][j]=f[i][j-1];
			else
				for(k=i;k<j;++k)
					f[i][j]=min(f[i][j],f[i][k]+f[k+1][j]);
//			printf("%d %d %d\n",i,j,f[i][j]);
		}
	for(i=1;i<=n;++i)
	{
		dp[i]=f[1][i];
		if(a[i]==b[i])dp[i]=dp[i-1];
		else
		{
			for(j=1;j<i;++j)
				dp[i]=min(dp[i],dp[j]+f[j+1][i]);
		}
	}
	printf("%d\n",dp[n]);
}
int main(){while(~scanf("%s %s",a+1,b+1))solve();}
```

---

## 作者：DDOSvoid (赞：4)

为了方便，本题解中是将 B 涂成 A

注意到，只有两种涂法是优秀的，一种是对于 A 中一段连续的相同字符，在 B 中直接一次将这段涂成像 A 一样。 第二种涂法是，A 中有一段字符，两端相同，中间与两端不同，在 B 中直接将这一段都涂成 A 中这一段两端的颜色

令 f[i][j][k] 表示将 i 到 j 的字符都涂成 k，然后再变成和 A 相同的最小次数

然后就可以转移了，注意细节

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 110
#define INF 1000000000
using namespace std;

int n, m, a[maxn], b[maxn];

char s1[maxn], s2[maxn];

int f[maxn][maxn][27], dp[maxn];
void mem(){ // 对于 i > j f[i][j][k] = 0
	for(int i = 1; i < maxn; ++i)
		for(int j = i; j < maxn; ++j) 
			for(int k = 1; k < 27; ++k) f[i][j][k] = INF;
	for(int i = 0; i < maxn; ++i) dp[i] = INF;
}

// transfer b to a
void work(){
    mem(); n = strlen(s1 + 1);
    for(int i = 1; i <= n; ++i) b[i] = s1[i] - 'a' + 1, a[i] = s2[i] - 'a' + 1;
	for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= 26; ++j) f[i][i][j] = (a[i] != j);
    for(int L = 1; L < n; ++L)
        for(int i = 1; i + L <= n; ++i){
            int j = i + L;
            for(int c = 1; c <= 26; ++c){
            	if(a[i] == a[j])
					f[i][j][c] = min(f[i][j][c], f[i + 1][j - 1][a[i]] + (a[i] != c));//第二种涂法
                for(int k = i; k < j; ++k)
					f[i][j][c] = min(f[i][j][c], f[i][k][c] + f[k + 1][j][c]); 
                	  // 这里并没有考虑 a[k] == a[k + 1] 的情况是因为
					  // 如果 a[k] 和 a[k + 1] 可以一次涂的话，这种情况在上面已经处理过了
			}
		}
	dp[0] = 0;    
    for(int i = 1; i <= n; ++i){
        dp[i] = dp[i - 1] + (a[i] != b[i]); // 第一种涂法
		for(int j = 1; j < i; ++j)
            if(a[i] == a[j]) dp[i] = min(dp[i], dp[j - 1] + 1 + f[j + 1][i - 1][a[i]]);
    }
    cout << dp[n] << endl;           
}
 
int main(){
    while(~scanf("%s%s", s1 + 1, s2 + 1)) work();
    return 0;
}
          
```

---

## 作者：_CHO (赞：3)

这题大概就是[P4170](https://www.luogu.com.cn/problem/P4170)多了一步



------------
设$f[][]$为将空白序列的子区间$(i,j)$涂成$b[]$的子区间$(i,j)$的最小代价

$g[i] $为将$a[]中$前$i$个数涂成$b[]$中前$i$个数的最小代价

把$a[]$涂成$b[]$太复杂，我们考虑把空白的序列涂成$b[]$，这一步直接套用P4170那道题即可，很简单的区间dp，不要忘记边界的处理。

然后我们开始考虑如何将$a[]$涂成$b[]$，如果$a[i]=b[i]$，那么显然$g[i]<-g[i-1]$ ； 当二者不等时，我们则需要用到与上面相似的做法，枚举一个端点，依次取最小值。

最后不要忘记把$g[i]$与$f[1][i]$取个$min$。显然这个更新是正确的。因为如果把空白序列涂成$b$比把$a$涂成$b$更优，而$a$涂成$b$的代价必然不小于空白涂成$b$，所以是可以更新的。



```cpp
#include <bits/stdc++.h>
using namespace std;

int n,a[200],b[200];
char s[200];
int f[200][200],g[200];
int main(){
	while(scanf("%s",s)==1){
		n = strlen(s);
		for(int i=1;i<=n;++i)a[i] = s[i-1]-'0';
		memset(s,0,sizeof(s));
		scanf("%s",s);
		for(int i=1;i<=n;++i)b[i] = s[i-1] - '0';
		memset(s,0,sizeof(s));
		memset(f,0x7f,sizeof(f));
		memset(g,0x7f,sizeof(g));
		for(int i=1;i<=n;++i) f[i][i] = 1;
		for(int len=2;len<=n;++len){
			for(int i=1,j=i+len-1;j<=n;++i,++j){
				if(b[i]==b[j])f[i][j] = min(f[i+1][j],f[i][j-1]);
				for(int k=i;k<j;++k) f[i][j] = min(f[i][j],f[i][k]+f[k+1][j]);
			}
		}
		if(a[1]!=b[1]) g[1] = 1;
		else g[1]=0;
		for(int i=2;i<=n;++i){
			if(a[i]==b[i]) g[i] = g[i-1];
			for(int k=1;k<i;++k) g[i] = min(g[i],g[k]+f[k+1][i]);
			g[i] = min(f[1][i],g[i]);
		}
		printf("%d\n",g[n]);
	}
	return 0;
}
```

---

## 作者：Y_QWQ_Y (赞：2)

本来模拟赛出了 [P4170 涂色](https://www.luogu.com.cn/problem/P4170)，然后双倍经验翻到了 [CF1132F](https://www.luogu.com.cn/problem/cf1132f)，再在讨论帖里看到了建议升紫，然后就在帖子里找到了这道题。（其实我早就把这题切了，也写了题解，但是还是再切了一遍）

### 解题思路
言归正传，其实本题思路与上面的两题是相似的，更改数组大小之后稍微进行一些操作即可。题目的本质其实就是把 $a_i$ 涂成 $b_i$，先考虑把空字符串涂成 $b$。

对于这种区间操作问题，我们一般可以考虑区间 dp。设状态如下：令 $f_{i,j}$ 表示把 $i$ 到 $j$ 这一区间全都染上颜色的最小步数。对于任意 ${1\le i\le n},f_{i,i}=1$，因为只需要将 $i$ 到 $i$ 都涂上原本的颜色就可以了，不需要考虑覆盖。

现在来考虑转移方程。显然，对于一个区间 $i,j$，我们可以找到一个断点 $k$，使得 $f_{i,k}+f_{k+1,j}$ 之和最小。这时这个最小的和就是当前这个区间的代价。就这么完了吗？显然不是的，因为对于区间 $i,j$，它的左端点颜色等于右端点颜色时，就可以通过一遍染色染到这两个点，那么这个时候，代价将会减少 $1$。写成转移方程：

$$f_{i,j} = \begin {cases} \min_{k=i}^j f_{i,k}+f_{k+1,j} - 1 & b_i = b_j\\\min_{k=i}^j f_{i,k}+f_{k+1,j} & b_i \neq b_j\end{cases}$$

我们继续思考，$a$ 并不是空串，我们可以令 $g_i$ 表示把 $a$ 从 $1$ 涂到 $i$ 所需要的最少步数，那么它的初始值应该为 $f_{1,i}$。

依旧可以写出转移方程：

$$g_i=\begin{cases}
g_{i-1} & a_i=b_i\\
\min\in{\min_{k=1}^{i-1} g_{k}+f_{k + 1,i},f_{1,i}} & a_i\neq b_i\end{cases}$$

那么最后的答案就是 $g_n$。

两个最关键的式子都给出了，代码实现就很简单了。

Update：

- 10.8 打完模拟赛之后又做了一遍，感觉之前写的太难看了，没讲清楚，所以就大改了一下，[原题解链接](https://www.luogu.com.cn/article/67lhiaro)。

---

## 作者：封禁用户 (赞：2)

很明显是一个区间 dp。

因为把 A 涂成 B 比较困难，所以先考虑从空串涂成 B 串。

设 $dp_{l,r}$ 表示把区间 $[l,r]$ 的空串涂成 B 的最小次数。

- 如果 $b_{l}=b_{r}$，只要在涂 $l$ 的时候往后涂到 $r$ 或者在涂 $r$ 的时候往前涂到 $l$ 就行，$dp_{l,r}=\min(dp_{l+1,r},dp_{l,r-1})$。

- 接着枚举断点 $k$，$dp_{l,r}=\min(dp_{l,r},dp_{l,k}+dp_{k+1,r}),k\in[l,r)$。

最后考虑从 A 转成 B，可以设 $ans_{i}$ 表示把区间 $[1,i]$ 的 A 串涂成 B 串的最小次数。

- 如果 $a_{i}=b_{i}$，则不需要修改，$ans_{i}=ans_{i-1}$。

- 接着枚举断点 $k$，$ans_{i}=\min(ans_{i},ans_{k}+dp_{k+1,i}),k\in [1,i)$。

最终答案为 $ans_{|A|}$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int dp[105][105];
int ans[105];
signed main(){
	string s,t;
	int n;
	while(cin>>s>>t){
		memset(dp,0x3f,sizeof(dp));
		n=s.size();
		s=" "+s;
		t=" "+t;
		for(int i=1;i<=n;++i){
			dp[i][i]=1;
		}
		for(int len=2;len<=n;++len){
			for(int l=1;l<=n-len+1;++l){
				int r=l+len-1;
				if(t[l]==t[r]){
					dp[l][r]=min(dp[l+1][r],dp[l][r-1]);
				}
				for(int k=l;k<r;++k){
					dp[l][r]=min(dp[l][r],dp[l][k]+dp[k+1][r]);
				}
			}
		}
		for(int i=1;i<=n;++i){
			ans[i]=dp[1][i];
			if(s[i]==t[i]) ans[i]=min(ans[i],ans[i-1]);
			for(int k=1;k<i;++k) ans[i]=min(ans[i],ans[k]+dp[k+1][i]);
		}
		cout<<ans[n]<<endl;
	}
	return 0;
}
```

---

## 作者：RP_INT_MAX (赞：2)

Upd on 2023.3.1：修了代码里的一处状态转移。

## $\tt Solution$

一眼丁真鉴定为区间 dp。以下令原串为 $A$，目标串为 $B$。

本题和 [P4170 涂色](https://www.luogu.com.cn/problem/P4170) 比较相似。不同的是需要考虑 $A$ 串和 $B$ 串某些字符相同的情况。

首先不考虑相同字符（可以视为初始是空白串），令 $f(i,j)$ 表示将一个空白串的区间 $[i,j]$ 染成 $B_{i \sim j}$ 需要的最少步数。基础区间 dp，直接给出转移方程，不过多做解释。

$$
f(i,j)=
\left\{
\begin{aligned}
& \min\{f(i,k)+f(k+1,j) \mid i \le k < j\} & B_i \not= B_j \\
& \max\{f(i+1,j),f(i,j-1)\} & B_i = B_j\\
\end{aligned}
\right.
$$

接下来处理考虑相同字符的情况，令 $g(i)$ 表示将 $A_{1 \sim i}$ 染成 $B_{1 \sim i}$ 需要的次数。

若 $A_i = B_i$，则不需要修改，令 $g(i)=g(i-1)$。

若 $A_i \not= B_i$，需要修改，枚举断点 $j$，令 $g(i)=\min\{f(j+1,i)+g(j) \mid 1 \le j < i\}$。

考虑一种特殊情况：在以上转移后 $g(i) > f(1,i)$，这时的 $g(i)$ 一定不是最优解。因此令 $g(i)=\min\{g(i),f(1,i)\}$。

最终答案为 $g(n)$。

## $\tt Code$

代码轻度压行，但应该能看懂。

```cpp
#include <cstring>
#include <iostream>
#define for1(i,a,b) for(int i=(a);i<=(b);++i)
#define for2(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int N=110;
char a[N],b[N];
int f[N][N],g[N];
int main () {
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	while(cin>>(a+1)>>(b+1)) {
		int n=strlen(a+1);
		memset(f,0x3f,sizeof f);
		memset(g,0x3f,sizeof g);
		for1(i,0,n) f[i][i]=1;
		for1(l,1,n) for(int i=1,j=i+l;j<=n;++i,++j)
			if(b[i]==b[j]) f[i][j]=max(f[i+1][j],f[i][j-1]);
			else for1(k,i,j-1) f[i][j]=min(f[i][j],f[i][k]+f[k+1][j]);
		g[1]=a[1]!=b[1];
		for1(i,2,n) {
			if(a[i]==b[i]) g[i]=min(g[i],g[i-1]);
			else for1(j,1,i-1) g[i]=min(g[i],g[j]+f[j+1][i]);
			g[i]=min(g[i],f[1][i]);
		}
		cout<<g[n]<<'\n';
	}
	return 0;
}
```

---

## 作者：StarPatrick (赞：2)

这道题我来写一种非同一般的区间 DP 写法。（由于记忆化搜索比较好写好讲，这里用记忆化搜索来讲）

定义 `dfs(l, r, color)` 表示将 $A[l,r]$ 区间转化成 $B[l,r]$ 区间所需要花费的次数（若 `color` 等于 0，那么此区间的字符为原 A 数组，否则，此区间全部被刷成了一个字符，此字符为 `color+'a'-1`）。

边界为左端点大于右端点时返回 0，当区间只剩一个字符，即左端点等于右端点，判断一下相不相等，若相等返回 0，否则返回 1。

代码描述边界：
```cpp
if (l>r)
{
	return 0;
}
if (l==r)
{
	if (color==0)
	{
		if (a[l]==b[l])
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
	else
	{ 
		if (color+'a'-1==b[l])
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
}
```

接下来，我们先不慌搜索，先判断一下区间左右两边是否与 B 数组相等，若相等，缩小左右边界。

这样，左右两边和 B 数组就没有相等的了，然后，我们开始搜索。

若 `color==0` ，也就是区间的字符是原数组的字符，枚举 $[l,r]$ 区间，如果 `b[l]==b[i]`，那么，我们就用字符刷将 $[l,r]$ 区间刷成 $a[l]$ 的字符。然后就把这个区间分成了两部分，接下来求最小值就行了。

若 `color!=0` ，也差不多，只是分成的两个区间 `color` 的值不同罢了。

最后，别忘了加上记忆化，记忆化数组是三维，大小 $300\times300\times30$。

最终代码：
```cpp
#include <iostream>
#include <cstring>
using namespace std;
char a[305], b[305];
int n, dp[305][305][30];
int dfs(int l, int r, int color)
{
	if (dp[l][r][color]!=-1)
	{
		return dp[l][r][color];
	}
	if (l>r)
	{
		return dp[l][r][color]=0;
	}
	if (l==r)
	{
		if (color==0)
		{
			if (a[l]==b[l])
			{
				return dp[l][r][color]=0;
			}
			else
			{
				return dp[l][r][color]=1;
			}
		}
		else
		{
			if (color+'a'-1==b[l])
			{
				return dp[l][r][color]=0;
			}
			else
			{
				return dp[l][r][color]=1;
			}
		}
	}
	if (color==0)
	{
		if (a[l]==b[l])
		{
			return dp[l][r][color]=dfs(l+1, r, 0);
		}
		else if (a[r]==b[r])
		{
			return dp[l][r][color]=dfs(l, r-1, 0);
		}
		else
		{
			int ans = 2147483647;
			for (int p=l;p<=r;p++)
			{
				if (b[p]==b[l])
				{
					ans = min(ans, dfs(l+1, p-1, b[l]-'a'+1)+dfs(p+1, r, 0)+1);
				}
			}
			return dp[l][r][color]=ans;
		}
	}
	else
	{
		char temp = color+'a'-1;
		if (temp==b[l])
		{
			return dp[l][r][color]=dfs(l+1, r, color);
		}
		else if (temp==b[r])
		{
			return dp[l][r][color]=dfs(l, r-1, color);
		}
		else
		{
			int ans = 2147483647;
			for (int p=l;p<=r;p++)
			{
				if (b[p]==b[l])
				{
					ans = min(ans, dfs(l+1, p-1, b[l]-'a'+1)+dfs(p+1, r, color)+1);
				}
			}
			return dp[l][r][color]=ans;
		}
	}
}
int main()
{
	while (cin>>a>>b)
	{
		memset(dp, -1, sizeof(dp));
		n = strlen(a);
		cout<<dfs(0, n-1, 0)<<"\n";
	}
	return 0;
}
```



---

## 作者：ncwzdlsd (赞：1)

一眼区间DP。

先考虑最劣情况，两字符串完全不同，下面对 $A$ 进行讨论。

假设有这样一种刷法，我们可以把一段连续的字符串刷成一个值，比如可以把 $\texttt{abc}$ 刷成 $\texttt{aaa}$，后刷的可以覆盖先刷的，令 $f(i,j)$ 为用这种刷法刷从 $i$ 到 $j$ 这段距离的最小花费，那么：

- 当 $i=j$ 时，$f(i,j)=1$；

- 当 $i\neq j$ 时，
	
    - 若两端相等，则只需要在 $f(i+1,j)$ 或 $f(i,j-1)$ 时多刷上它即可；状态转移方程：$f(i,j)=\min(f(i+1,j),f(i,j-1))$。
    
    - 若两端不等，此时区间的两端都可以向内走，所以我们需要枚举断点找到最优解；状态转移方程：$f(i,j)=\min(f(i,j),f(i,k)+f(k+1,j))$。
    
需要注意的是，前面说的这种刷法并不是最优的，显然有些时候不需要这种刷法，我们假设从 $1$ 到 $i$ 这段区间的最优解为 $dp(i)$，则 $dp(i)$ 最大值显然为劣的刷法的最优解，即 $f(1,i)$，并且注意初始化，$dp(0)=0$。

对于第 $i$ 位来说：

- 如果 $A$、$B$ 相同，那么直接多刷这个格子即可，即 $dp(i)=dp(i-1)$；

- 如果 $A$、$B$ 的第 $i$ 位不同，那么我们就需要对 $B$ 进行如上修改，同样的，我们需要枚举断点，在从 $k+1$ 到 $i$ 这个区间内的字符串进行操作，都刷成 $B$ 的第 $i$ 位。状态转移方程：$dp(i)=\min\limits_{0\leq k\leq i}(dp(i),dp(i)+f(k+1)(i))$。

这样下来思路就已经很清晰啦，按部就班做就好啦，代码就不放了，要自己思考哟！

---

## 作者：LSG_waterlyf (赞：1)

## 比较显然的区间dp
首先发现有两种刷的方法：

 - 对于单个字符原来串是什么就刷什么 

 - 对于区间$[l,r]$，若$b[l]=b[r]$,将整个区间刷为 $b[l]$,再划分为子问题处理。 

考虑第二种方法，设 $f[i][j][k]$表示$[l][r]$开始为 $k$，刷成目标串的最小次数。$f[i][j][k]=f[i+1][j-1][k]+(k!=b[i])$;

综合两种方法，设 $dp[i]$为刷完前$i$个的最小次数，$dp[i]=min(dp[j]+f[j+1][i][b[i]]+1,dp[i-1]+a[i]!=b[i])$.
```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 510
int a[N],b[N],dp[N][N][N],ans[N],n;
string s;
void init()
{
	memset(ans,0x3f,sizeof(ans));
	memset(dp,0,sizeof(dp));
	for(int i=1;i<=n;i++)
	  for(int j=i;j<=n;j++) 
	    for(int c=1;c<=26;c++) dp[i][j][c]=1e9;
}
void test()
{
	for(int i=1;i<=n;i++) printf("%d ",a[i]);
	puts("");
	for(int i=1;i<=n;i++) printf("%d ",b[i]);
	puts("");
}
int main()
{
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
	cin>>s;
		n=s.size();
		for(int i=1;i<=n;i++) a[i]=s[i-1]-'a'+1;
		cin>>s;
		for(int i=1;i<=n;i++) b[i]=s[i-1]-'a'+1;
		init();
		//test();
		for(int l=1;l<=n;l++)
		  for(int i=1;i+l-1<=n;i++)
		  {
		  	  int j=i+l-1;
		  	  for(int c=1;c<=26;c++)
		  	  {
		  	  	  if(b[i]==b[j]) dp[i][j][c]=min(dp[i][j][c],dp[i+1][j-1][b[i]]+(b[i]!=c));
		  	  	  for(int k=i;k<j;k++)
		  	  	    dp[i][j][c]=min(dp[i][j][c],dp[i][k][c]+dp[k+1][j][c]);
			  }
		  }
		ans[0]=0;
		for(int i=1;i<=n;i++)
		{
			ans[i]=ans[i-1]+(a[i]!=b[i]);
			for(int j=0;j<i;j++) 
			  ans[i]=min(ans[i],ans[j]+dp[j+1][i][b[i]]+1);
		}
		cout<<ans[n];
	return 0;
}
```


---

## 作者：tsqtsqtsq0309 (赞：1)

# UVA1437 String painter

## 题目大意

给定两个字符串 $A$、$B$，其中 $A$ 可以通过若干次变换得到 $B$，试求出变换次数。

## 思路

显然是一道区间 DP。

首先不考虑相同的字符，可以令 $f_{i,j}$ 表示将空白串的区间 $[i,j]$ 变换为 $B_{i \sim j}$ 需要的最小步数。

考虑两种情况：

1. 当 $B_i \ne B_j$ 时，这意味着需要对字符串进行变换，通过枚举断点 $k$ 进行转移，思路跟一般的区间 DP 差不多，这里不做过多解释。
2. 当 $B_i = B_j$ 时，这意味着无需对字符串进行变换，可以直接由 $f_{i+1,j}$ 或者 $f_{i,j - 1}$ 转移得到。

综上所述，易得状态转移方程如下：
$$
f(i, j) = \begin{cases}
\min \left\{f(i, k) + f(k + 1, j) \mid i \le k < j \right\} & B_i \ne B_j \\
\max \left\{f(i + 1, j), f(i, j - 1) \right\} & B_i = B_j \\
\end{cases}
$$
有了上面的 DP 数组，现在我们就可以考虑处理相同字符。令 $g_i$ 表示将 $A_{1 \sim i}$ 变换成 $B_{1 \sim i}$ 需要的最小步数。考虑两种情况：

1. 当 $A_i = B_i$ 时，则不需要再做其他修改，此时 $g_i = g_{i - 1}$。
2. 当 $A_i \ne B_i$ 时，则需要进行修改，通过枚举断点 $j$ 进行转移，此时 $g_i = \min \left\{f_{j + 1, i} + g_j \mid 1 \le j < i \ \right\}$。

综上所述，易得状态转移方程如下：
$$
g_i = \begin{cases} g_{i - 1} & A_i \ne B_j \\ \min \left\{f_{j + 1, i} + g_j \mid 1 \le j < i \ \right\} & A_i = B_j \\\end{cases}
$$
此外还有一种特殊情况：在转移之后可能会出现 $g_i > f_{1, i}$ 的情况，这个时候的 $g_i$ 就不是最优解了，因此还需要令 $g_i = \min \left\{g_i, f_{1, i})\right\}$。最终答案显然是 $g_n$，具体细节请看代码……

## 代码

```cpp
#include <iostream>
#include <cstring>
#define MAXN 105
using namespace std;
char a[MAXN], b[MAXN];
int n, f[MAXN][MAXN], g[MAXN];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0); // 加速
	while(cin >> (a + 1) >> (b + 1)){
		n = strlen(a + 1);
		memset(f, 998244353, sizeof(f));
		memset(g, 998244353, sizeof(g)); // 记得初始化
		for(int i = 0 ; i <= n ; i ++)f[i][i] = 1;
		for(int len = 1 ; len <= n ; len ++) // 枚举长度
            for(int i = 1, j = i + len ; j <= n ; i ++ , j ++){
                if(b[i] == b[j])f[i][j] = max(f[i + 1][j], f[i][j - 1]);
                else for(int k = i ; k < j ; k ++)f[i][j] = min(f[i][j], f[i][k] + f[k + 1][j]); // 枚举断点
            }g[1] = a[1] != b[1];
		for(int i = 2 ; i <= n ; i ++){
			if(a[i] == b[i])g[i] = min(g[i], g[i - 1]);
			else for(int j = 1 ;j < i ; j ++)g[i] = min(g[i], g[j] + f[j + 1][i]); // 枚举断点
			g[i] = min(g[i], f[1][i]); // 特判
		}cout << g[n] << endl; // 输出答案
	}return 0;
}
```



---

## 作者：紊莫 (赞：0)

这是一道好题。

首先我们要分两步解决这个问题，一是在不考虑 $a$ 的限制下，二是考虑的情况下。

为什么可以这么做？因为假如我们要修改 $a$ 中的某个区间，那么这个区间实际上是什么就没有意义了。然后我们要选出一些段，使得这些段不被修改，其余被修改，并求一个最小值。

对于第一个情况，我们可以使用区间 DP 来完成，因为这个喷涂操作只可能嵌套或者并列，所以可以直接区间 DP。

对于第二部分，我们设 $g_i$ 表示前 $i$ 位变得一样的最小花费，那我们枚举之前的一个端点 $j$，然后改变这之间的答案即可。

```cpp
void solve() {
  n = a.size();
  a = " " + a;
  m = b.size();
  b = " " + b;
  memset(f, 0x3f, sizeof f);
  F(i, 1, m) f[i][i] = 1;
  for (int len = 2; len <= m; len++) {
    for (int l = 1, r = l + len - 1; r <= m; l++, r++) {
      if (b[l] == b[r]) f[l][r] = min(f[l + 1][r], f[l][r - 1]);
      for (int k = l; k < r; k++) {
        f[l][r] = min(f[l][r], f[l][k] + f[k + 1][r]);
      }
    }
  }
  memset(g, 0x3f, sizeof g);
  g[0] = 0;
  F(i, 1, n) {
    if (a[i] == b[i]) g[i] = g[i - 1];
    F(j, 0, i - 1) { g[i] = min(g[i], g[j] + f[j + 1][i]); }
  }
  cout << g[n] << '\n';
}
```

---

## 作者：Addicted_Game (赞：0)

# [传送门](https://www.luogu.com.cn/problem/UVA1437)

## 题意。

有两个字符串 $A$ 与 $B$，你可以将 $A$ 连续的一段改为同一字母，请问最少需要多少步才能将 $A$ 变成 $B$。
## 思路。

###### 区间 **DP** 模版题。

### 第一步：将空白字符串转化为目标串 $B$。

先定义 **DP** 状态。

设 $dp[ i ][ j ]$ 为区间 $[i,j]$ 内 $A$ 转化为 $B$ 的最少次数。

再推动态转移方程。

（1）当 $B_i$ 与 $B_j$ 相同时。

先将 $[i,j]$ 整体刷一遍，再刷 $[i,j-1]$ 或 $[i-1,j]$ 。

这种方法一定是最优的，可以减少两端各刷一次的次数。当去掉两端端点时，得到两个区间 $[i,j-1]$ 与 $[i-1,j]$ ，因为两端只刷一遍，所以 $dp[i][j]=dp[i-1][j] $ 或 $ dp[i][j-1]$。

（2） 当 $B_i$ 与 $B_j$ 不同时。

因为两端端点不同，所以要各刷一遍，就是标准的区间 **DP**。

枚举中间点 $k$ ，那么 $dp[i][j]=\min (dp[i][k]+dp[k+1][j])$。

### 第二步：将目标串转化为给定字符串。

（1）当 $A_i$ 与 $B_i$ 相同时。

那么字符串不需要转化，就与上一状态相同 $dp[1][i]=dp[1][i-1]$。

（2）当 $A_i$ 与 $B_i$ 不同时。

仍然是区间 **DP** ，把区间分为 $[1,k]$ 与 $[k+1,i]$ 两部分，求它的最小和。

$dp[1][i]=\min (dp[1,k]+dp[k+1][i])$。

### 代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
char a[105],b[105];
int dp[105][105]; 
int len;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
    //为了更好写，我是从下表为1开始存。
	while(cin>>a+1>>b+1){//注意有多组数据。
		len=strlen(a+1); 
		memset(dp,0x3f,sizeof dp);//初始化设为极大值。
		for(int i=1;i<=len;i++) dp[i][i]=1;//同一个点只需一步。
		for(int l=2;l<=len;l++){
			for(int i=1;i<=len-l+1;i++){
				int j=i+l-1;
				if(a[i]==a[j]) dp[i][j]=dp[i+1][j];//取一边 也可以是dp[i][j]=dp[i][j+1]。
				else{
					for(int k=i;k<j;k++){
						dp[i][j]=min(dp[i][j],dp[i][k]+dp[k+1][j]);
					}
				}
			}
		}
		for(int i=1;i<=len;i++){
			if(a[i]==b[i]) dp[1][i]=dp[1][i-1];
			else{
				for(int k=1;k<i;k++){
					dp[1][i]=min(dp[1][i],dp[1][k]+dp[k+1][i]);
				}
			}
		}
		cout<<dp[1][len]<<endl;
	}
	return 0;
}


---

## 作者：Jerrywang09 (赞：0)

显然是区间 DP，使用记忆化搜索实现较为简便。

定义 DP 状态 $f(l,r,c)$ 表示将区间 $[l,r]$ 染成字符 $c$ 的最小代价。如果 $c=0$，表示这个区间暂未染色。

考虑转移。分情况考虑：

1. 目前 $[l,r]$ 最左（右）边的字符就是目标字符。此时可以将区间缩小成 $[l+1,r]$（$[l,r-1]$）。
2. $b_k=b_l$。可以将 $[l,k]$ 全部染成 $b_k$，$[k+1,r]$ 保持原色。最优解一定可以这样构造而成。

有人可能会问：染成 `abcaba` 难道是先染 $[1,4]$ 吗？显然不是，因为可以转移 $k=6$，先染 $[1,6]$。

还有：似乎染不成 `bac`？$k=l$ 是可能的，先染 $[1,1]$，再处理 $[2,3]$。

```cpp
#include <bits/stdc++.h>
#define rep(i, s, t) for(int i=(s); i<=(t); ++i)
const int N=105, inf=1e9;
using namespace std;

char a[N], b[N];
int n;
int f[N][N][128];
int dfs(int l, int r, char c)
{
    if(l>r) return 0;
    if(l==r)
    {
        if(c) return c!=b[l];
        return a[l]!=b[l];
    }
    int &dp=f[l][r][c];
    if(~dp) return dp;
    dp=inf;
    if(c)
    {
        if(c==b[l])
            return dp=dfs(l+1, r, c);
        if(c==b[r])
            return dp=dfs(l, r-1, c);
        rep(k, l, r)
            if(b[k]==b[l])
                dp=min(dp, dfs(l+1, k-1, b[l])+dfs(k+1, r, c)+1);
        return dp;
    }
    if(a[l]==b[l])
        return dp=dfs(l+1, r, 0);
    if(a[r]==b[r])
        return dp=dfs(l, r-1, 0);
    rep(k, l, r)
        if(b[k]==b[l])
            dp=min(dp, dfs(l+1, k-1, b[l])+dfs(k+1, r, 0)+1);
    return dp;
}

int main()
{
    while(scanf("%s%s", a+1, b+1)==2)
    {
        memset(f, -1, sizeof f);
        n=strlen(a+1);
        printf("%d\n", dfs(1, n, 0));
    }
    
    return 0;
}
```

---

## 作者：Eric_jx (赞：0)

## 思路详解 

我们发现直接将 $A$ 串转换成 $B$ 串会非常困难。

这时候我们考虑先将一个空串转换成 $B$ 串，然后再考虑这个串对 $A$ 串的影响。

考虑区间 dp。设 $f_{i,j}$ 表示把空区间 $[i,j]$ 变成和 $B$ 一样需要的最少次数。

初始化：$f_{i,i}=1$。 

如果两个端点 $i$ 和 $j$ 的字符相等，则 $f_{i,j}=f_{i,j-1}$。

否则，我们可以把大区间的最小操作次数转换为两个小区间的最小操作次数之和，即 $f_{i,j}=\min(f_{i,k}+f_{k+1,j})$。

那么如何再改成从 $A$ 串涂成 $B$ 串呢。考虑再进行一次 dp。

我们设 $dp_i$ 表示 表示将 $[1,i]$ 的字符串修改成一致所需的最少操作次数。
 
如果第 $i$ 位两个串相等，那么 $dp_i=dp_{i-1}$。否则 $dp_i=\min(dp_j+f_{j+1,i})$。

答案就是 $dp_n$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
char a[10005],b[100005];
int f[1005][1005],dp[100005];
int main(){
	while(~scanf("%s%s",a+1,b+1)){
	int n=strlen(a+1);
	memset(f,0x3f3f3f3f,sizeof(f));
	for(int i=1;i<=n;++i){
		f[i][i]=1;
		dp[i]=0x3f3f3f3f;
	}
	for(int len=2;len<=n;len++)
		for(int i=1;i+len-1<=n;i++){
			int j=i+len-1;
			if(b[i]==b[j]){
				f[i][j]=f[i][j-1];
			}
			else{
				for(int k=i;k<j;k++){
					f[i][j]=min(f[i][j],f[i][k]+f[k+1][j]);
				}
			}
		}
	for(int i=1;i<=n;i++){
		dp[i]=f[1][i];
		if(a[i]==b[i]){
			dp[i]=dp[i-1];
		}
		else{
			for(int j=1;j<i;j++){
				dp[i]=min(dp[i],dp[j]+f[j+1][i]);
			}
		}
	}
	cout<<dp[n]<<"\n";
	}
	return 0;
}
```

 

---

