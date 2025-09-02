# Clear the Multiset

## 题目描述

You have a multiset containing several integers. Initially, it contains $ a_1 $ elements equal to $ 1 $ , $ a_2 $ elements equal to $ 2 $ , ..., $ a_n $ elements equal to $ n $ .

You may apply two types of operations:

- choose two integers $ l $ and $ r $ ( $ l \le r $ ), then remove one occurrence of $ l $ , one occurrence of $ l +         1 $ , ..., one occurrence of $ r $ from the multiset. This operation can be applied only if each number from $ l $ to $ r $ occurs at least once in the multiset;
- choose two integers $ i $ and $ x $ ( $ x \ge 1 $ ), then remove $ x $ occurrences of $ i $ from the multiset. This operation can be applied only if the multiset contains at least $ x $ occurrences of $ i $ .

What is the minimum number of operations required to delete all elements from the multiset?

## 样例 #1

### 输入

```
4
1 4 1 1```

### 输出

```
2```

## 样例 #2

### 输入

```
5
1 0 1 0 1```

### 输出

```
3```

# 题解

## 作者：activeO (赞：46)

## 题目大意

[题面](https://www.luogu.com.cn/problem/CF1400E) 讲的很清楚了，这里就不说了。

## 思路

对于一段区间 $ [l,r] $，有两种操作的可能。

- 整段用操作 2，因为对于一个数，肯定是直接减完最好，所以数目是 $ r-l+1 $。
- 先用操作 1，再用操作 2，会有一个最小值 x 的位置是 i，用操作 1 减完后，状态转变成 $ f(l,i-1)+f(i+1,r)+x $。

$ [l,r] $ 区间最终的答案就是 $ \min(r-l+1,f(l,i-1)+f(i+1,r)+x) $。

**算法：贪心+分治**

时间复杂度：$ O(n^2) $ 可以通过此题。

## 代码

```cpp
#include <bits/stdc++.h>//祝大家学习愉快！

using namespace std;

const int maxn=5010;
const int inf=0x3f3f3f3f;
int a[maxn];

int solve(int l,int r){
	if(l>r) return 0;
	if(l==r) return min(a[l],1);
	int minn=inf,tmp;
	for(int i=l;i<=r;i++){
		if(minn>a[i]){
			minn=a[i];
			tmp=i;
		}
	}
	for(int i=l;i<=r;i++) a[i]-=minn;
	return min(r-l+1,solve(l,tmp-1)+solve(tmp+1,r)+minn);
}

int main(){
	
	int n;
	
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	
	printf("%d\n",solve(1,n));
	
	return 0;
}


```


---

## 作者：haochengw920 (赞：12)

## 前言
这是一道笛卡尔树的好练手题 ， 数据可以加强到 $ 10 ^ 6 $ 甚至 $ 10 ^ 7 $ 级别。但是题解区以 $ O(n ^ 2) $ 为主，少量提到了 $ O(n \log n) $ 解法的也不是笛卡尔树。运用笛卡尔树可以做到 $ O( n ) $ 的时间复杂度。几乎未经卡常跑到了[最优解第三](https://www.luogu.com.cn/record/115329066)，并且时间并列最优。

## 笛卡尔树介绍
[笛卡尔树](http://magic.vicp.io/oi-wiki/ds/cartesian-tree/) 是一种解决和区间最值有关问题的一个很强力的树形数据结构，本质上是二叉堆和二叉搜索树的结合，因此其具有二叉堆和二叉搜索树的所有性质。关于它的构造方法（以小根堆为例）可以考虑使用单调栈使节点权值和下标均单调递增，即维护笛卡尔树最右边的链。具体实现方法可以参考 [P5854](https://www.luogu.com.cn/problem/solution/P5854) 的模板。

## 题意
[题目链接](https://www.luogu.com.cn/problem/CF1400E) 。在题意（题面已经很清晰了）的基础上，我们定义上面那个操作为操作一，另外一个为操作二。

## 解题思路
对于操作一，我们先考虑一个简单的贪心的性质：如果要对一个区间使用操作一，那必然会操作到无法操作为止（即出现零）。这时显然可以分治了。考虑如何维护分治点(即区间最小值），这时候我们就会用到笛卡尔树的一个重要性质：两端点的最小值即它们在笛卡尔树上的 lca ，即笛卡尔树上的一点是该点子树区间内的的最小值。故我们可以以结点来计算贡献，以 $a_i$ 建出笛卡尔树并分治。

对于操作二，仍然对点考虑贡献，即为该点在笛卡尔树上的子树大小。

所以列出流程：

- 输入，以 $a_i$ 建出笛卡尔树，并维护结点字数大小；

- 从根节点开始递归，一个点的贡献即为其子树大小和分治贡献的较小值，具体可看代码。

## 代码

具体的看注释

```
#include<cstdio>
#include<stack>
#include<algorithm>
using namespace std;

const int MAXN = 100005;

int n, a[MAXN], rt;
int ch[MAXN][2], siz[MAXN];

inline void dfs(int u) { // 维护子树大小，也可以在建树过程中完成 
	if (u == 0) return; 
	if (ch[u][0] == 0 && ch[u][1] == 0) { //叶子节点 
		siz[u] = 1;
		return;
	}
	dfs(ch[u][0]); dfs(ch[u][1]);
	siz[u] = 1 + siz[ch[u][0]] + siz[ch[u][1]];
}
inline void Build() { //建树 
	stack<int>stc;
	for (int i = 1; i <= n; ++ i) {
		int lc = 0;
		while (!stc.empty() && a[stc.top()] > a[i]) lc = stc.top(), stc.pop();
		if (!stc.empty()) ch[stc.top()][1] = i;
		if (lc) ch[i][0] = lc;
		stc.push(i); 
	}
	while (!stc.empty()) rt = stc.top(), stc.pop(); // 根节点即为栈底元素 
	dfs(rt);
}

inline int Solve(int u, int tg) {
	if (ch[u][0] == 0 && ch[u][1] == 0) return (a[u] - tg > 0); //叶子节点，若不为 0 则花费 1 的代价变为 0 
	return min(siz[u], Solve(ch[u][0], a[u]) + Solve(ch[u][1], a[u]) + a[u] - tg); //分别对应操作二和操作一 
}

int main()
{
	scanf ("%d", &n);
	for (int i = 1; i <= n; ++ i) scanf ("%d", a + i);
	Build();
	int res = Solve(rt, 0);
	return printf ("%d\n", res), 0;
}
```

望通过。


---

## 作者：hpcwdclcx (赞：8)

首先注意到二操作，要减肯定得一口气减完。

思路：**分治+贪心**

我们考虑求 $f(l,r)$ 表示把区间 $[l,r]$ 都消完需要的最小操作数。分为两种情况：

1. 不用一操作。此时答案为 $r-l+1$ 。

1. 先用一操作。此时肯定要反复对 $[l,r]$ 进行操作，直到其中有一个数为 $0$ 。设这个数位置为 $x$ ，本来值为 $k$ ，则答案为 $f(l,x-1)+f(x+1,r)+k$ 。

两者取 $min$ 即可。答案为 $f(1,n)$ 。

code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[5010];
int f(int l,int r)
{
	if(l>r)return 0;
	if(l==r)return min(a[l],1);
	int k=2e9,x;
	for(int i=l;i<=r;i++)if(k>a[i])k=a[i],x=i;
	for(int i=l;i<=r;i++)a[i]-=k;
	return min(r-l+1,f(l,x-1)+f(x+1,r)+k);
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	return printf("%d",f(1,n)),0;
}
```


---

## 作者：momo5440 (赞：6)

提供一个纯dp的解法，首先有一个显而易见的性质，答案$<=n$，这是因为我们可以全用操作二，这样所有$a_{i}>n$的我们都用操作而干掉才最优，不然全一的话答案就$>n$了

我们这样设计dp状态，令$dp[i][j]$为到第$i$个数且之前有$j$个$-1$带到这里了，下面便是转移

$Case 1:$用操作一干掉$a[i]$

1，新做一些操作一

$dp[i][a[i]]=min(dp[i-1][j]+a[i]-j),(j<=a[i])$

2，有一些操作一结束了

$dp[i][a[i]]=min(dp[i-1][j]),(j>=a[i])$

$Case 2:$用操作二干掉$a[i]$

那首先$j<=a[i]$不然上来$a[i]<0$了

其实跟刚才一样，还是讨论是新做操作一，还是消去操作一

1，新做一些操作一

$dp[i][j]=min(dp[i-1][k]+j-k+1)(k<=j)$

2，有一些操作一结束了

$dp[i][j]=min(dp[i-1][k]+1)(k>=j)$

两个转移前缀和优化一下就行了

总复杂度$O(N^{2})$

```cpp
#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
const int maxn=5e3+5;
int dp[maxn][maxn],a[maxn],n;
int main(){
	cin>>n;
	for (int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	memset(dp,0x3f,sizeof(dp));
	dp[0][0]=0;
	for (int i=1;i<=n;i++){
		if (a[i]>n){
			int cur=1e9;
			for (int j=n;j>=0;j--){
				cur=min(cur,dp[i-1][j]);
				dp[i][j]=min(dp[i][j],cur+1);
			}
			cur=1e9;
			for (int j=0;j<=n;j++){
				cur=min(cur,dp[i-1][j]-j);
				dp[i][j]=min(dp[i][j],cur+j+1);
			}
			continue;
		}
		else{
			for (int j=0;j<=a[i];j++){
				dp[i][a[i]]=min(dp[i-1][j]+a[i]-j,dp[i][a[i]]);
			}
			for (int j=a[i];j<=n;j++){
				dp[i][a[i]]=min(dp[i-1][j],dp[i][a[i]]);
			}
			int cur=1e9;
			for (int j=a[i];j<=n;j++){
				cur=min(cur,dp[i-1][j]);
			}
			for (int j=a[i];j>=0;j--){
				cur=min(cur,dp[i-1][j]);
				dp[i][j]=min(dp[i][j],cur+1);
			}
			cur=1e9;
			for (int j=0;j<=a[i];j++){
				cur=min(cur,dp[i-1][j]-j);
				dp[i][j]=min(dp[i][j],cur+j+1);
			}
		}
	}
	int ans=1e9;
	for (int i=0;i<=n;i++){
		ans=min(ans,dp[n][i]);
	}
	cout<<ans<<endl;
}
```


---

## 作者：ZigZagKmp (赞：6)

本文同步发表于[我的cnblog](https://www.cnblogs.com/ZigZagKmp/p/13563143.html)

本场题解可见[此](https://www.luogu.com.cn/blog/ZigZagKmp/codeforces-1400-edu-94-solution)
## 题意简述
给定一个长度为$n$数列$\{a_n\}$，你可以进行如下操作：

- 任意选择一个区间$[l,r](l\le r)$，使区间内的每一个数减$1$；
- 任意选择一个点$p$和一个正整数$x(x\ge 1$，使$a_p$减去$x$。

求把原数列全部变为$0$的最少的操作次数。
$1\le n\le 5000$，$0\le a_i\le 10^9$。
### 算法考察
贪心，分治
## 算法分析

~~CF自己出自己的原题可还行(CF448C)。~~

~~CF出NOIp的原题的原题的改编题可还行(铺设道路/积木大赛)。~~

如果只有第二种操作，答案显然是$n$。

如果只有第一种操作，就是铺设道路/积木大赛，答案也容易求。

现在我们把两种操作综合起来。

我们不难想到一个贪心，要么直接$n$次操作2解决，要么尽可能使用操作1，使得整个序列不能再整体减少（否则会出现负数），再对被$0$分隔开的每一个区间采取类似的方法操作。

这个贪心的正确性可以归纳证明，显然边界条件是剩余部分序列的值相等，这时可以直接按照上述方法操作，这里的最优性容易证明。

下面我们假设分开的每一个区间都是最优情况。

我们只要证明**尽可能使用操作1**一定不会比**不完全使用操作1**答案差即可。我们假设给这个区间少减去1，这种调整对后面全部使用操作2的区间没有影响，对原来为0的区间需要多1次操作，对原来先使用操作1的区间也需要多使用至少1次操作，因此一定不如原来的方案优。

至此我们得出了这样一个分治的贪心算法，复杂度$O(n^2)$，可以证明处理一个长度为$len$的区间的额外开销是$O(len)$，每一次分治至少使总区间长度$-1$，因此$T(n)=T(n-1)+O(n)=O(n^2)$，常数很小。

另：本题和$CF448C$有一点点区别，$CF448C$中$a_i>0$，本题$a_i\ge 0$，要注意如下的数据：

```plain
1
0
```

## 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 5005
#define maxm 2000005
#define inf 0x3f3f3f3f
#define int long long
#define mod 1000000007
#define local
template <typename Tp> void read(Tp &x){
	int fh=1;char c=getchar();x=0;
	while(c>'9'||c<'0'){if(c=='-'){fh=-1;}c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c&15);c=getchar();}x*=fh;
}
int n,m;
int a[maxn];
//实际实现中并不需要真正区间减
int solve(int l,int r,int h){
	if(l==r){
		if(a[l]==h)return 0;
		else return 1;//注意特判，否则HACKED
	}
	int mh=inf;
	for(int i=l;i<=r;i++)mh=min(mh,a[i]);//求解
	int ans=mh-h,j;
	for(int i=l;i<=r;i++){
		if(a[i]==mh)continue;
		for(j=i;j<=r;j++){
			if(j==r||a[j+1]==mh)break;
		}//找到被分割开的区间
		ans+=solve(i,j,mh);
		i=j+1;
	}
	return min(ans,r-l+1);//与全操作2比较
}
signed main(){
	read(n);
	for(int i=1;i<=n;i++)read(a[i]);
	printf("%lld\n",solve(1,n,0));
	return 0;
}
```

---

## 作者：Little09 (赞：1)

这题其实重题了，但是我没有发现。

考虑怎么弄掉一个区间。要么用操作 $2$ 把它们一次切光，要么用操作 $1$ 把它们切到一个为 $0$，再递归下去。

由于区间不重复，所以不用记忆化，直接做就可以了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n; 
int a[30005];
int work(int l,int r)
{
	if (l>r) return 0; 
	if (l==r) 
	{
		if (a[l]==0) return 0;
		return 1;
	}
	int minn=1e9+7;
	for (int i=l;i<=r;i++)minn=min(minn,a[i]);
	for (int i=l;i<=r;i++) a[i]-=minn;
	int last=l,res=0;
	for (int i=l;i<=r;i++)
	{
		if (a[i]==0) 
		{
			res+=work(last,i-1);
			last=i+1;
		}
	}
	res+=work(last,r);
	for (int i=l;i<=r;i++) a[i]+=minn;
	return min(res+minn,r-l+1);
}
inline int read()
{
	char C;
	int F=1,ANS=0;
	while (C<'0'||C>'9')
	{
		if (C=='-') F=-1;
		C=getchar();
	}
	while (C>='0'&&C<='9')
	{
		ANS=ANS*10+C-'0';
		C=getchar();
	}
	return F*ANS;
} 
int main()
{
	n=read();
	for (int i=1;i<=n;i++) a[i]=read();
	cout << work(1,n);
	return 0;
}
```


---

## 作者：black_trees (赞：1)


### 核心：贪心+分治思想

-----
题目和[CF448C](https://www.luogu.com.cn/problem/CF448C)基本是一样的。只有数据范围有一丢丢不同。

讲一下思路。

（这里直接用448C来讲，因为这题题面换个说法就是448C的题面）

-------

一般人先想到的是横着刷，因为这样可以多刷一点。

但是如果数据是这样子的：

![](https://cdn.luogu.com.cn/upload/image_hosting/wfugnjqx.png)

你要横着涂就会这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/0ubklin7.png)

也就是会出现分成好几个独立的小块的情况。

那么在某些数据里，这样就不是最优解了。

（当然也可以理解成尽量不重复刷）

-----

所以，我们在每次粉刷之后要这样做。

~~~cpp

int d_a_c(int l,int r){
    int horizontal;//水平涂
    int vertical;//竖着涂

    /*分治过程*/

    return min(horizontal,vertical);
}
~~~

也就是贪心（也许是）一下，取两种返回结果（横着和竖着）的最小值。

当然这两个值肯定是在里面递归返回之后得到的结果。

在这里面的分治过程应该不用说了。

唯一要注意的是这组数据：

~~~
1
0
~~~

CF上很多人就是交448C的代码没看这种特殊情况的。

然后就被hack了。

详情可以看这里：[link](https://codeforc.es/blog/entry/81916?#comment-686653)

---

代码略。

---

## 作者：AlanSP (赞：1)

## E.Clear the multiset

#### [题目链接](https://codeforces.com/contest/1400/problem/E)

贪心+分治。

每次进行一次操作后，原问题都转化成了一个新的子问题，可以分治解决。

如果只有第一种方式，那么我们贪心选择能选的最大数字和宽度。

这样做一定比其他方式更优或不劣。

找到最大的连通区域，减去最大数字后递归求解。

再考虑第二种方式，对于任意一个区间操作次数均为 $r-l+1$ 。

将两者取min，就得到了当前问题的最优解法。

得到了子问题的最优方案，便可以归并求得最终答案。

l=r时为边界，如果非0则操作次数为1，否则为0.

#### Code:

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
#define int long long
int n;
int h[5009];

inline int solve(int l,int r,int H)
{
	if(l==r) return h[l]?1:0;
	int minn=0x7f7f7f7f,res=0;
	for(int i=l;i<=r;i++) minn=min(minn,h[i]);
	res+=minn-H;
	int p;
	for(int i=l;i<=r;i=p+1)
	{
		p=i;
		if(h[i]==minn) continue;
		for(int j=i+1;j<=r;j++)
		{
			if(h[j]==minn) break;
			p=j;
		}
		res+=solve(i,p,minn);
	} 
	return min(res,r-l+1);
}

signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++) scanf("%lld",&h[i]);
	printf("%lld\n",solve(1,n,0));
	return 0;
}
```



---

## 作者：k2saki (赞：0)

分治好题。

考虑一段区间，要么全部用 1 操作清零，要么一直用 2 操作直到不能用了，再去用同样的方法去递归两个子区间。

假设区间最小的那个点的编号是 pos，就有 $f(l,r)=f(l,pos-1)+f(pos+1,r)+a[pos]-max(a[l-1],a[r+1])$

复杂度 $O(n^2)$，用线段树或 ST 可以优化到 log

核心代码：

```cpp
int dfs(int l, int r)
{
    if (l > r)
        return 0;
    int pos, minn = 1010101010;
    for (int i = l; i <= r; ++i)
    {
        if (a[i] < minn)
            pos = i, minn = a[i];
    }
    return min(r - l + 1, dfs(l, pos - 1) + dfs(pos + 1, r) + a[pos] - max(a[l - 1], a[r + 1]));
}
```

答案就是 dfs(1,n)

---

## 作者：yzyjh (赞：0)

蒟蒻也来写题解了awa

此题貌似和CF448C重题了呢

### 思路

首先横着涂，在竖着涂，每次涂都要找到涂最大化的涂法

简单来说就是贪心

```cpp
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
 
using namespace std;
const int N = 5007;
int n, a[N];
int solve(int l, int r) {
    if(l > r) return 0;
    if(l == r) {
        if(a[l] == 0)
            return 0;
        else 
            return 1;
    }
    int now = 0x7fffffff, k;
    for(int i = l; i <= r; i ++)
        if(a[i] < now)
            k = i, now = a[i];
    for(int i = l; i <= r; i ++)
        a[i] -= now;
    return min(now + solve(l, k - 1) + solve(k + 1, r), r - l + 1);
 
}
 
int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i ++)
        scanf("%d", &a[i]);
    printf("%d\n", solve(1, n));
    return 0;
}
```


---

## 作者：引领天下 (赞：0)

显然对于一段**全部非0**的区间 $[l,r]$，当 $r-l+1>\min_{i=l}^r{a_i}$ 时，挨个删除一定更优。

否则就可以考虑区间删除。

也许有人有这样的疑问：如果出现以下情况

![](https://cdn.luogu.com.cn/upload/image_hosting/c9gf45vn.png)

如何处理？

事实上，以上情况可以等效为下图

![](https://cdn.luogu.com.cn/upload/image_hosting/ltauntsw.png)

故如果采取区间删除，区间较长时一定不会更劣。

于是我们就可以递归解决了。

```cpp
#include <bits/stdc++.h>
#define min(x,y) ((y)^(((x)^(y))&(-((x)<(y)))))
#define max(x,y) ((x)^(((x)^(y))&(-((x)<(y)))))
using namespace std;
int n,a[5005];
long long work(int l,int r){
    if(l>r)return 0;
    if(l==r)return !!a[l];//此区间只剩一个位置，显然可以直接一发操作二解决问题
    int mn=1<<30,p=l,ans;
    for(register int i=l;i<=r;i++)mn=min(mn,a[i]);
    for(register int i=l;i<=r;i++)a[i]-=mn;
    ans=mn;
    if(ans>r-l+1)return r-l+1;//如果挨个删更划算，就挨个删
    for(register int i=l;i<=r;i++)if(!a[i]){
        ans+=work(p,i-1);//递归，加上子代答案
        p=i+1;
        if(ans>r-l+1)return r-l+1;//挨个删更划算，就挨个删
    }
    ans+=work(p,r);
    return min(ans,r-l+1);//最后再取一次min
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    printf("%lld",work(1,n));
    return 0;
}
```

---

## 作者：_lxy_ (赞：0)

[博客食用效果更佳](https://www.cnblogs.com/lxy-2022/p/CF-shua-ti-ji-lu.html)
#### 分析

发现清空一个区间 $[l,r]$ 有两种方式，第一种是每次把一个数变为 $0$，第二种是整段减最小值，这样原来的区间就变成了左右两个小区间，中间一个元素是 $0$。只有这两种做法可能最优，第一种很好理解，第二种因为如果在大区间都没有整段减，那在小区间就更不可能用了。分治计算即可。

#### 核心代码

```cpp
int n,a[MAXN];
int solve(int l,int r){
    if(l>r) return 0;if(l==r) return !!a[l];int p=l;
    for(int i=l;i<=r;i++) if(a[p]>a[i]) p=i;
    int x=a[p];for(int i=l;i<=r;i++) a[i]-=x;
    return qmin(r-l+1,solve(l,p-1ll)+solve(p+1ll,r)+x);
}
signed main(){
    qread(n);int i,j;for(i=1;i<=n;i++) qread(a[i]);
    printf("%lld\n",solve(1,n));
    return 0;
}
```

---

