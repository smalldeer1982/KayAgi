# 「dWoi R1」Sixth Monokuma's Son

## 题目背景

题目首先定义矩阵环为，给定一个矩阵 $A$，初始全为白色，在其中选定一个子矩阵 $A_1$ 标黑，再在 $A_1$ 内选定一个子矩阵 $A_2$ 标白，就会形成一个矩阵环。注意，矩阵环至少上下左右都有被选定的部分，且整个矩阵环不是一个长方形的矩阵。

假设 `+` 为黑，`-` 为白，下面这个就是矩阵环：

```
---+++++--
---++--+--
---+++++--
---+++++--
----------
```

下面就不是矩阵环：

```
------- ------
---+++- --+++-
---+-+- --+++-
------- --+++-
```

因此，矩阵环会出现上，下，左，右四条边，每个方向有多少个涂黑的部分，就是那个方向的厚度。比如对于第一张符合要求的图，上方，右方的厚度为 $1$，左方，下方的厚度为 $2$。

**注意，一个完整的矩阵不是一个矩阵环。**

---

接下来是正经的题目背景：

最原得到了“狱原发现一些小昆虫”这个线索后，立刻采取了行动。首先，他利用入间的 ~~遗物~~，那个类似喷火器的东西，吸进了一些空气，然后，他打算利用机望的机械眼进行查看。

## 题目描述

机望的机械眼能扫到一片 $n \times m$ 的区域，第 $i$ 行第 $j$ 列发现了 $a_{i,j}$ 的不对劲值。

因为机望被外部力量折磨的厉害，所以机望只能锁定一个矩阵环进行查看。机望想求助于你，他想让你锁定一个矩阵环，使得这个矩阵环中的所有位置的不对劲值的和最大，**上方，下方的厚度为 $1$ 且上方的那一行在整个区域的第一行，下方的那一行在整个区域的最后一行**。至于左右的厚度，机望不限制更多要求。

## 说明/提示

#### 样例说明

关于样例 1 的解释：

可以选择如下形式的矩阵环（但其实两个解是一样的，因为第一列所有数之和为 $0$）：

```
++++  -+++
++-+  -+-+
++-+  -+-+
++++  -+++
```

其中 + 为选定的，- 为未选定的。

关于样例 3，提供者 @[cmll02](https://www.luogu.com.cn/user/171487)，感谢他的贡献。

#### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（5 pts）：$n \le 2$ 或 $m \le 2$。
- Subtask 2（5 pts）：$a_{i,j}>0$。
- Subtask 3（40 pts）：$m \le 1000$。
- Subtask 4（50 pts）：无特殊限制。

对于 $100\%$ 的数据，$1 \le n \le 10$，$1 \le m \le 10^5$，$|a_{i,j}| \le 100$。

## 样例 #1

### 输入

```
4 4
3 -4 2 -2
-5 3 -4 2
-1 3 -4 0
3 -3 3 4```

### 输出

```
8```

## 样例 #2

### 输入

```
1 2
11 45```

### 输出

```
-1```

## 样例 #3

### 输入

```
7 7
10 10 10 -100 11   11 11
10 10 10 -100 11 -100 11
10 10 10 -100 11 -100 11
10 10 10 -100 11 -100 11
10 10 10 -100 11 -100 11
10 10 10 -100 11 -100 11
10 10 10 -100 11   11 11```

### 输出

```
176```

# 题解

## 作者：wsyhb (赞：11)

## 题意简述

定义矩阵环为**将矩阵中的一个非空子矩阵去掉后得到的图形**，给定一个 $n \times m$ 的矩阵 $a$，问所有**上下厚度均为 $1$** 的矩阵环的元素之和的最大值。

**数据范围**：$n \le 10$，$m \le 10^5$，$|a_{i,j}| \le 100$

## 分析 + 题解

考虑将矩阵环拆成左、中、右三个部分：

```
--+++++++++-    --+++ ++++ ++-
--+++----++-    --+++ ---- ++-
--+++----++- -> --+++ ---- ++-
--+++----++-    --+++ ---- ++-
--+++++++++-    --+++ ++++ ++-
```

由此可见，矩阵环左、右两部分为若干个完整的列，中间部分为若干个只有上下两行的列，且**左、中、右三部分都必须非空**。考虑**分三个阶段进行 DP**。

记 $s_i$ 为第 $i$ 列元素之和，$t_i$ 为第 $i$ 列首尾元素之和，设 $dp1_i$ 表示**以第 $i$ 列为止**的**左**边部分的元素之和最大值，$dp2_i$ 表示以第 $i$ 列为止的**左、中**部分的元素之和最大值，$dp3_i$ 表示以第 $i$ 列为止的**左、中、右**部分的元素之和最大值，则有下列转移方程：

$$dp1_i=\max(dp1_{i-1},0)+s_i$$

$$dp2_i=\max(dp2_{i-1},dp1_{i-1})+t_i$$

$$dp3_i=\max(dp3_{i-1},dp2_{i-1})+s_i$$

**说明**：每一阶段可以由**这一部分或上一部分加上这一列**转移而来。由于每一部分必须非空，$dp1_0=dp2_0=dp3_0=-inf$。

别忘了若 $n \le 2$ 或 $m \le 2$，不存在矩阵环，即**无解**。

## 代码

代码非常地好写~

``` cpp
#include<bits/stdc++.h>
using namespace std;
const int max_n=10+5;
const int max_m=1e5+5;
int s[max_m],t[max_m];
int dp1[max_m],dp2[max_m],dp3[max_m];
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	if(n<=2||m<=2)//判无解 
	{
		puts("-1");
		return 0;
	}
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
		{
			int a;
			scanf("%d",&a);
			s[j]+=a;
			if(i==1||i==n)
				t[j]+=a;
		}//直接读入并更新 s 和 t，无需存储 
	dp1[0]=dp2[0]=dp3[0]=-1e9;//初始化 
	int ans=-1e9;
	for(int i=1;i<=m;++i)
	{
		dp1[i]=max(dp1[i-1],0)+s[i];
		dp2[i]=max(dp2[i-1],dp1[i-1])+t[i];
		dp3[i]=max(dp3[i-1],dp2[i-1])+s[i]; 
		ans=max(ans,dp3[i]);//更新答案 
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：xuan_gong_dong (赞：5)

## 题目
[P7160 「dWoi R1」Sixth Monokuma's Son](https://www.luogu.com.cn/problem/P7160)

题目大意：给你一个 $n \times m$ 的矩形 $(n\le10,m\le10^5)$，要求你寻找一个中空的**矩阵环**，使得其覆盖的部分**和最大**。

## 废话
一开始看到 $n\le 10$ 还以为是状态压缩。想了变天重新理解题意的时候才发现题意读错了捏。

## 分析
发现这个所求图形可以被分成三个部分。如图所示
![](https://cdn.luogu.com.cn/upload/image_hosting/a2o9gh70.png)

不妨设 $pre_i=\sum_{j=1}^n a_{ij}$ 表示的含义是第 $i$ 列的数和。
再设 $hys_i$ 为 $a_i$ 与 $a_n$ 的和。

再设 $dp0_i$ 为枚举到第 $i$ 列时左边那一块的和的最大值，$dp1_i$ 为枚举到第 $i$ 列时左边那一块与中间那两块的和的最大值。$dp2_i$ 为枚举到第 $i$ 列时矩阵环的最大值。

易得转移方程 

$$dp0_i=\max(dp0_{i-1},0)+pre_i$$
$$dp1_i=\max(dp1_{i-1},dp0_{i-1})+hys_i$$
$$dp2_i=\max(dp2_{i-1},dp1_{i-1})+pre_i$$

答案就是所有 $dp2_i$ 的最大数。

## 细节
当 $n \le 2$ 且 $m \le 2$ 时发现无法中空，则此情况一定无解。

```cpp
#include<bits/stdc++.h>
using namespace std;
int dp[100010][3];
int a[15][100010];
int pre[100010];//表示第i列的数和
int hys[100010];//表示第i列的上下两个数之和
int n,m;
inline int read() {
	int x=0,f=0;
	char c=getchar();
	while(!isdigit(c)) {
		f|=c=='-';
		c=getchar();
	}
	while(isdigit(c)) {
		x=(x<<3)+(x<<1)+(c^48);
		c=getchar();
	}
	return f?-x:x;
}
int main() {
	n=read(),m=read();
	if(n<=2&&m<=2) {
		printf("-1");
		exit(0);
	}
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)
			a[i][j]=read();
	for(int i=1; i<=m; i++) {
		for(int j=1; j<=n; j++)
			pre[i]+=a[j][i];
		hys[i]=a[1][i]+a[n][i];
	}
	int Max=-2e9;
	for(int i=1; i<=m; i++) {
		dp[i][0]=max(dp[i-1][0],0)+pre[i];//第一部分 
		if(i!=1) { 
			if(i!=m)
				dp[i][1]=max(dp[i-1][0],dp[i-1][1])+hys[i];//第二部分 
			dp[i][2]=max(dp[i-1][1],dp[i-1][2])+pre[i];//第三部分 
			Max=max(Max,dp[i][2]);//求得答案 
		}
	}
	printf("%d",Max);
	return 0;
}
```


---

## 作者：一只书虫仔 (赞：5)

![](https://cdn.luogu.com.cn/upload/image_hosting/zxxf3qro.png)

$$\sf\color{LimeGreen}dWoi\ Round\ 1\ D\ Sixth\ Monokuma's\ Son$$

注意本文的复杂度分析可能没带上输入的复杂度。

#### Description

> 给定一个 $n \times m$ 的矩阵，求一个上下厚度为 $1$ 且上面那一行属于矩阵的第一行，下面那一行属于矩阵的最后一行的矩阵环使得矩阵环里的数字和最大。          
> $1 \le n \le 10$，$1 \le m \le 10^5$，$|a_{i,j}| \le 100$

#### Subtask 1

约束条件：$n \le 2$ 或 $m \le 2$。

没有符合要求的矩阵环，输出 $-1$。

#### Subtask 2

约束条件：$a_{i,j}>0$。

这时肯定选的数越多越好，但你不能选择一个整矩阵，因此选择不为第 $1$ 列和第 $m$ 列的一列中除去第一个数和第 $n$ 个数和最小的一列，把他的和减掉即可。

#### Subtask 3

约束条件：$1 \le m \le 2000$。

我们首先把整个矩阵环拆一下：

```
---+++++++--    ---++ ++++ +--
---++----+--    ---++ ---- +--
---++----+-- -> ---++ ---- +--
---++----+--    ---++ ---- +--
---+++++++--    ---++ ++++ +--
```

左边，右边其实都可以做一个最大子段和，只要把一行的所有 $a[i][j]$ 值加起来即可，这个预处理并不麻烦。

所以，我们只需要枚举中间即可，时间复杂度大约为 $\mathcal O(m^2)$。

#### Subtask 4

我们把上面矩阵环左边右边的空格去掉后再分拆，如下：

```
++ ++++ +
++ ---- +
++ ---- +
++ ---- +
++ ++++ +
```

整个矩阵环可以看做是三个部分，最左边的长条，最左边加上最中间的 $C$ 形，左中右加起来的矩阵环。

那么，我们其实可以这三部分分别进行动归计算一个大的最大子段和。

假设 $dp1[i]$ 代表经过第 $i$ 列后长条的最大子段和，$dp2[i]$ 代表经过第 $i$ 列后 $C$ 形的最大子段和，$dp3[i]$ 代表经过第 $i$ 列后矩阵环的最大子段和，这三个类型其实可以互相转换。

首先，预处理 $s[i]=\sum\limits_{j=1}^n a[i][j]$，即第 $i$ 列所有数之和，$t[i]=a[i][1]+a[i][n]$，即第 $i$ 列第 $1$ 个和第 $n$ 个数之和。

然后我们来分析最大子段和：

- $dp1[i]=\max\{dp1[i-1],0\}+s[i]$，最简单的最大子段和。
- $dp2[i]=\max\{dp1[i-1],dp2[i-1]\}+t[i]$，因为一个 $C$ 形块可以是一个长条加上 $t[i]$ 也可以是一个 $C$ 行块加上一个 $t[i]$。
- $dp3[i]=\max\{dp2[i-1],dp3[i-1]\}+s[i]$，因为一个矩形环可以是一个 $C$ 形块加上一个 $s[i]$ 也可以是一个矩形环加上一个 $s[i]$。

然后输出 $dp3[m]$ 即可。

如果预处理很优秀的话，那么能做到 $\mathcal O(m)$。

#### Code

```cpp
#include <bits/stdc++.h>

using namespace std;

long long s[10000005];
long long t[10000005];

long long dp1[10000005];
long long dp2[10000005];
long long dp3[10000005];

int main () {
    int n, m;
    scanf("%d%d", &n, &m);
    memset(dp1, -0x3f, sizeof(dp1));
    memset(dp2, -0x3f, sizeof(dp2));
    memset(dp3, -0x3f, sizeof(dp3));
    if (n <= 2 || m <= 2) {
        puts("-1");
        return 0;
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            long long a;
            scanf("%lld", &a);
            s[j] += a;
            if (i == 1 || i == n) t[j] += a;
        }
    for (int i = 1; i <= m; i++) {
        dp1[i] = max(dp1[i - 1], 0ll) + s[i];
        if (i != 1 && i != n) dp2[i] = max(dp1[i - 1], dp2[i - 1]) + t[i];
        if (i != 1) dp3[i] = max(dp2[i - 1], dp3[i - 1]) + s[i];
    }
    long long Max = -0x3f;
    for (int i = 1; i <= m; i++) Max = max(Max, dp3[i]);
    printf("%lld", Max);
    return 0;
}
```

---

附赠来自 lgswdn 的解：

考虑矩阵环的组成，可以拆成三部分：左边一个 $p\times n$ 的矩阵，中间上下两条，以及右边一个 $q\times n$  的矩阵。考虑设 $f(i)$ 为满足 $l=i, r\in [i,n]$ 中总和最大的，最左边为 $l$ 这一列，最右边为 $r$ 这一列的子矩阵的 $a_{i,j}$ 的总和。设 $h_i$ 表示第 $i$ 列的 $a$ 之和。显然这个可以直接 $dp: $ $f(i)=\max(f(i+1),0)+h_i$。

我们再看左边的情况。设 $g(i)$ 表示 $r=i,l\in [1,i]$ 的总和最大的，最左边为 $l$ 这一列，最右边为 $r$ 这一列的子矩阵。于是，$ans=\max_i g(i)+\max_{j\ge i+2}\{f_j+\sum_{k=i+1}^{j-1}h_k\}$。我们中间这个求和用前缀和 $s_i=\sum_{j=1}^{i} h_j$拆开，得到
$$
ans=\max_i g(i)+\max_{j\ge i+2} \{f_j+s_{j-1}-s_{i}\}。
$$

显然后面的 $s_i$ 可以移出来。预计算 $mf(i)=\max _{j\ge i} f_j+s_{j-1}$

可以直接算出的答案

$$
ans=\max_i g(i)-s_i+mf(i+2)
$$

复杂度 $\mathcal O(nm)$。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(register int i=(a);i<=(b);i++)
#define per(i,a,b) for(register int i=(a);i>=(b);i--)
using namespace std;
const int N=19,M=1e5+9,minf=-0x3f3f3f3f3f3f3f3f;

inline int read() {
    register int x=0, f=1; register char c=getchar();
    while(c<'0'||c>'9') {if(c=='-') f=-1; c=getchar();}
    while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+c-48,c=getchar();}
    return x*f;
}

int n,m,a[N][M],st[M],h[M],f[M],mf[M],ans=minf;

signed main() {
	n=read(), m=read();
	if(n<=2||m<=2) {
		puts("-1");
		return 0;
	}
	rep(i,1,n) rep(j,1,m) a[i][j]=read();
	rep(j,1,m) st[j]=st[j-1]+a[1][j]+a[n][j];
	rep(j,1,m) rep(i,1,n) h[j]+=a[i][j];
	per(j,m,3) f[j]=max(0ll,f[j+1])+h[j];
	mf[m+1]=minf;
	per(j,m,3) mf[j]=max(mf[j+1],f[j]+st[j-1]);
	int sum=0;
	rep(j,1,m-2) {
		sum=max(0ll,sum)+h[j];
		ans=max(ans,sum+mf[j+2]-st[j]);
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Kohakuwu (赞：4)

## 前言
这篇题解会教您如何把黄题当蓝题写。
## 思路
首先确认 $n,m\geq 3$，不然输出 $-1$。

我们记每一列的总和为 $a_i$，每一列去掉第一行和最后一行的和为 $b_i$。

再记 $b_l,b_{l+1},b_{l+2},\cdots,b_r$ 的最大子段和为 $B_{l,r}$，

那么题意即求出 $\max\limits_{l=1}^{n-2}\max\limits_{r=l+2}^n(\sum\limits_{i=l}^ra_i+B_{l+1,r-1})$，即一段 $a_i$ 的和减掉一段 $b_i$ 的和，要求 $b_i$ 这段被 $a_i$ 两端覆盖。

注意到最大子段和问题可以用**线段树**维护，此题我们同样用线段树维护。

考虑一下答案的几种可能：

1. 答案完全在左区间内。
2. 答案完全在右区间内。
3. $a$ 数组的和跨越左右，$b$ 数组完全在左边。
4. $a$ 数组的和跨越左右，$b$ 数组完全在右边。
5. $a,b$ 数组的和跨越左右。

因此我们要记录这些信息：

1. 区间的答案。
2. 区间的前缀和最大值。
3. 区间的后缀和最大值。
4. 区间的前缀答案最大值。定义前缀答案即一个 $a$ 的前缀和减去一个 $b$ 的前缀和，同时 $b$ 的长度严格小于 $a$。
5. 区间的后缀答案最大值。
6. 区间的前缀最大值。
7. 区间的后缀最大值。

于是我们就得到了一份极丑的 $O(nm+n\log n)$ 代码：
## 代码
```
#include<bits/stdc++.h>
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int a[100003],b[100003];
struct node
{
	int pre,PRE,suf,SUF,pre0,suf0,pre1,suf1,ans;
};
#define newnode (node){-1000000000,-1000000000,-1000000000,-1000000000,-1000000000,-1000000000,-1000000000,-1000000000,-1000000000}
node getans(int l,int r)
{
	if(l==r) return newnode;
	int mid=(l+r)>>1;
	node L=getans(l,mid),R=getans(mid+1,r),res=newnode;
	res.ans=max(max(max(L.ans,R.ans),max(L.SUF+R.pre,L.suf+R.PRE)),max(L.suf0+R.pre1,L.suf1+R.pre0));
	for(int i=l,x=0,y=0,t=0x3f3f3f3f; i<=r; i++) x+=a[i],y+=b[i],res.pre=max(res.pre,x-t),res.PRE=max(res.PRE,x-min(t,0)),t=min(t,y);
	for(int i=r,x=0,y=0,t=0x3f3f3f3f; i>=l; i--) x+=a[i],y+=b[i],res.suf=max(res.suf,x-t),res.SUF=max(res.SUF,x-min(t,0)),t=min(t,y);
	for(int i=l,x=0; i<=r; i++) x+=a[i],res.pre1=max(res.pre1,x);
	for(int i=r,x=0; i>=l; i--) x+=a[i],res.suf1=max(res.suf1,x);
	for(int i=l,x=0,y=0,t=0x3f3f3f3f; i<=r; i++) x+=a[i],y+=b[i],res.pre0=max(res.pre0,x-t),t=min(t,y),y=min(y,0);
	for(int i=r,x=0,y=0,t=0x3f3f3f3f; i>=l; i--) x+=a[i],y+=b[i],res.suf0=max(res.suf0,x-t),t=min(t,y),y=min(y,0);
	return res;
}
signed main()
{
	//freopen("D.in","r",stdin);
	//freopen("D.ans","w",stdout);
	int m=read()-2,n=read();
	if(n<3||m<1) puts("-1"),exit(0); 
	for(int i=1; i<=n; i++) a[i]+=read();
	for(;m--;) for(int i=1; i<=n; i++) b[i]+=read();
	for(int i=1; i<=n; i++) a[i]+=read(),a[i]+=b[i];
	printf("%d\n",getans(1,n).ans);
	return 0;
} 
```

---

## 作者：翼德天尊 (赞：1)

疯狂刷 $\text{dp}$ 题&&写 $\text{dp}$ 题题解$\text{.jpg}$

本题解主要就解题思路方面进行分析。

------------

首先读题。

我们从题目中的一个小细节——第一行和最后一行必须选——可以发现，我们的这个矩阵环不能将列分割开来。什么意思呢？意思就是说，对于一列的元素，是不会有的框入矩阵环，有的不框的。

所以根据这个细节，我们可以很自然地将该矩阵分为 $3$ 个部分：左侧部分，中侧只选首尾部分，右侧部分。拿样例为例，可以分割成：

```
++|+|+
++|-|+
++|-|+
++|+|+
```

对应的，我们可以将矩阵预处理一下，提前求出每一列的和以及首尾元素和。

下面就开始进行 $\text{dp}$ 了。

------------

因为我们设置了三个部分，所以我们也可以对应将 $dp$ 数组设置成三个，或者多加一维。$dp_{i,0}$ 表示前 $i$ 列化为第一部分时的最大值，$dp_{i,1}$ 表示前 $i$ 列化为第一、二部分时的最大值，$dp_{i,2}$ 表示前 $i$ 列化为第一、二、三部分时的最大值。下面我们来考虑一下转移方程。（下面设第 $i$ 列之和为 $sum_i$，第 $i$ 列的首尾和为 $sw_i$）

首先先来思考第一个 $dp$ 数组的转移方程。它的值的由来应该可以分为两种情况，一种是接着前面选的（即前面已经有几列），一种是新选的（即成为左侧部分的第一列）。那么将这两种情况选一个最大值就可以了。即：

$$dp_{i,0}=max\left\{dp_{i-1,0}+sum_i,sum_i\right\}$$

由于两边都有 $sum_i$，所以可化为：

$$dp_{i,0}=max\left\{dp_{i-1,0},0\right\}+sum_i$$

再来思考第二个 $dp$ 数组。它的值的由来也可以分为两种情况，一种是前面一列为左侧部分，一种是前面一列为中侧部分。将这两种情况取一个最大值即为该数组的转移方程，即：

$$dp_{i,1}=max\left\{dp_{i-1,0},dp_{i-1,1}\right\}+xw_i$$

第三个 $dp$ 数组与第二个同理，即：

$$dp_{i,2}=max\left\{dp_{i-1,1},dp_{i-1,2}\right\}+sum_i$$

最终的答案即为所有的第三个 $dp$ 数组的最大值。

哦，对了，别忘了特判当矩阵任意一边长小于等于 $2$ 时，答案为 $-1$。

------------

### AC 代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 100005
#define INF 999999999
int n,m,l[N],sw[N],dp[N][3],ans=-INF;
int read(){//快读
	int w=0,f=1;
	char c=getchar();
	while (c>'9'||c<'0'){
		if (c=='-') f=-1;
		c=getchar();
	}
	while (c<='9'&&c>='0'){
		w=(w<<3)+(w<<1)+(c^48);
		c=getchar();
	}
	return w*f;
}

int main(){
	n=read(),m=read();
	for (int i=0;i<3;i++) dp[0][i]=-INF;//初始化
	if (n<=2||m<=2){//特判
		puts("-1");
		return 0;
	}
	for (int i=1;i<=n;i++)//读入+预处理
		for (int j=1;j<=m;j++){
			int a=read();
			if (i==1||i==n) sw[j]+=a;
			l[j]+=a;
		}
	for (int i=1;i<=m-2;i++)//转移
		dp[i][0]=max(dp[i-1][0],0)+l[i];
	for (int i=2;i<=m-1;i++)
		dp[i][1]=max(dp[i-1][1],dp[i-1][0])+sw[i];
	for (int i=3;i<=m;i++){
		dp[i][2]=max(dp[i-1][2],dp[i-1][1])+l[i];
		ans=max(dp[i][2],ans);
	}
	printf("%d\n",ans);
    return 0;
}
```


---

## 作者：SSerxhs (赞：1)

这题需要大量查询区间和，而第 $1$ 行和第 $n$ 行等价，其余行分别等价，可以考虑设 $f_n=\sum\limits_{i=1}^na_{1,i}+a_{n,i}$，$g_n=\sum\limits_{i=1}^n\sum\limits_{j=2}^{n-1}a_{j,i}$，又设矩形环左边的左右边界分别为 $a+1,b$，右边的左右边界分别为 $c+1,d$，则 $ans=f_d-f_{a}+g_d-g_c+g_b-g_a$。考虑令 $f_n\leftarrow f_n+g_n$，则 $ans=f_d-g_c+g_b-f_a$。

这里的限制为 $0\le a<b<c-1<d\le m$，可以考虑一遍扫描求出 $f_a$ 的前缀最小值，可以对任意的 $b$ 计算出 $g_b-f_a$ 的最大值，同时同理扫描一遍求出前述最大值的前缀最大值，可以对任意的 $c$ 求出 $-g_c+g_b-f_a$。重复以上过程，即可求出 $ans$ 的最大值。

代码的具体实现不同，赛时写了前后缀两种

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int c,fh;
inline void read(int &x)
{
	c=getchar();fh=1;
	while ((c<48)||(c>57))
	{
		if (c=='-') {c=getchar();fh=-1;break;}
		c=getchar();
	}
	x=c^48;c=getchar();
	while ((c>=48)&&(c<=57))
	{
		x=x*10+(c^48);
		c=getchar();
	}
	x*=fh;
}
const int N=1e5+2;
int s[N],a[N],ps[N],ns[N],na[N];
int n,m,i,j,x,lst,ans;
int main()
{
	//freopen("a.in","r",stdin);
	read(n);read(m);
	if (n<=2||m<=2) return puts("-1"),0;
	for (j=1;j<=m;j++) read(s[j]);
	for (i=2;i<n;i++) for (j=1;j<=m;j++) read(x),a[j]+=x;
	for (j=1;j<=m;j++) read(x),s[j]+=x;
	for (i=1;i<=m;i++) s[i]+=s[i-1];
	for (i=1;i<=m;i++) a[i]+=a[i-1];
	for (i=1;i<=m;i++) s[i]+=a[i];
	ps[0]=0;ns[m+1]=-1e9;na[m+1]=-1e9;
	for (i=1;i<=m;i++) ps[i]=min(ps[i-1],s[i]);
	for (i=m;i;i--) ns[i]=max(ns[i+1],s[i]);
	for (i=m;i;i--) na[i]=max(na[i+1],ns[i]-a[i-1]);
	ans=-1e9;
	for (i=1;i<m-1;i++) ans=max(ans,a[i]-ps[i-1]+na[i+2]);
//	for (i=1;i<m-1;i++) if (a[i]-ps[i-1]+na[i+2]==ans) printf("b=%d\n",i);
	printf("%d",ans);
}
```

---

## 作者：patrickwen (赞：0)

### 题意：
• 题目首先定义矩阵环为，给定一个矩阵  $A$ ，初始全为白色，在 其中选定一个子矩阵  $A1$ 标黑，再在  $A1$ 内选定一个子矩阵  $A2$ 标白，就会形成一个矩阵环。注意，矩阵环至少上下左右都有被 选定的部分，且整个矩阵环不是一个长方形的矩阵。

• 假设 $+$ 为黑，$-$ 为白，下面这个就是矩阵环：
![](https://cdn.luogu.com.cn/upload/image_hosting/p1ismtgq.png)

 • 因此，矩阵环会出现上，下，左，右四条边，每个方向有多少 个涂黑的部分，就是那个方向的厚度。比如对于第一张符合要 求的图，上方，右方的厚度为  $1$ ，左方，下方的厚度为  $2$ 。
 
 **• 注意，一个完整的矩阵不是一个矩阵环。**

### 解法：
• 我们可以把矩阵环分为左中右三部分：

![](https://cdn.luogu.com.cn/upload/image_hosting/umxg295h.png)

• 左右两部分是完全由+组成的矩形，中间部分为首尾行是+，中间是-的矩形。

• 设 $𝑓_{i,j}$ 表示考虑到第𝑖列，矩阵前 $1/2/3$ 个部分时的最⼤值。

• 预处理 $𝑠𝑢𝑚_i$ 表示当前列之和 $cur_i$ 表示当前列首尾元素之和。

• 则有:
```cpp
    for (ll i = 1; i <= m; i++)
    {
        f[i][0] = max(f[i - 1][0], 0ll) + sum[i];
        if (i != 1)
        {
            if (i != m)
                f[i][1] = max(f[i - 1][1], f[i - 1][0]) + cur[i];
            f[i][2] = max(f[i - 1][2], f[i - 1][1]) + sum[i];
            ans = max(ans, f[i][2]);
        }
    }
```
• 全代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n, m;
ll a[15][100005], cur[100005], sum[100005], f[100005][15];
int main()
{
    cin >> n >> m;
    for (ll i = 1; i <= n; i++)
    {
        for (ll j = 1; j <= m; j++)
        {
            cin >> a[i][j];
        }
    }
    for (ll j = 1; j <= m; j++)
    {
        cur[j] = a[1][j] + a[n][j];
        for (ll i = 1; i <= n; i++)
        {
            sum[j] += a[i][j];
        }
    }
    ll ans = -1e18;
    for (ll i = 1; i <= m; i++)
    {
        f[i][0] = max(f[i - 1][0], 0ll) + sum[i];
        if (i != 1)
        {
            if (i != m)
                f[i][1] = max(f[i - 1][1], f[i - 1][0]) + cur[i];
            f[i][2] = max(f[i - 1][2], f[i - 1][1]) + sum[i];
            ans = max(ans, f[i][2]);
        }
    }
    cout << (n > 2 && m > 2 ? ans : -1) << endl;
}
```

---

## 作者：yzysdTNT (赞：0)

本篇题解主要是梳理做题时的思路，可能有点啰嗦，但是每一个点都是做题时的思考过程。

## 题意简述

给定一个矩阵，求矩阵中元素和最大的矩阵环，要求此矩阵环的上下两行**厚度均为 1 **且分别**位于第一、最后一行**。

矩阵环定义：将某个矩阵的**非空**子矩阵去掉后的图形，即一个圈。

## 分析

### Part1 算法使用

~~其实可以直接看算法标签~~，没有标签时我们应该怎么分析呢？

先看范围，$1 \le n \le 10$，$1 \le m \le10^5$，m 的范围有点吓人，好像没法 DP ；  
再看题，题意中“上下两行厚度均为 $1$ 且分别位于第一、最后一行” 可理解为选中一列有两种情况：

- 一整列全部选中（矩阵环的左、右部分）
- 只选择第一、最后一行的元素（矩阵环的中间部分，即上、下边界）

因此可得我们的操作单位是**每一列**，n 其实是没有什么用的，所以可以一维 DP。

---
### Part2 输入（预处理）

根据第一步的分析，我们可以在输入时进行预处理，对于每一列的输入，只存储第一行、最后一行的元素之和以及一整列的元素之和，既能方便后续 DP 操作，~~还能减少空间~~。

CODE：
```cpp
for(int i = 1;i <= n;i++){
	for(int j = 1;j <= m;j++){
		cin >> a;//mid表示中间部分的值，line表示左右两边的部分
		if(i == 1 || i == n){//位于第一、最后一行
			mid[j] += a;
		}
		line[j] += a;
	}
}
```
---
### Part3 状态转移

上文中所分的两种情况中，

> - 一整列全部选中（矩阵环的左、右部分）
> - 只选择第一、最后一行的元素（矩阵环的中间部分，即上、下边界）

其实已经将整个矩阵环分成了三个部分：

1. 左侧部分（整列）；
2. 中间部分（第一、最后一个元素）；
3. 右侧部分（整列）。

那么我们的状态转移就是一步步完善整个矩阵环的过程，考虑分情况转移：

- $f1_i$ 表示以第 $i$ 列为结尾的左半部分的最大值；
- $f2_i$ 表示以第 $i$ 列为结尾的左半部分加中间部分的最大值（可以理解为一个半圆）；
- $f3_i$ 表示以第 i 列为结尾的一个完整的矩阵环的最大值。

显而易见，

- $f1_i$ 可直接推出；
- $f2_i$ 有从 $f1_{i-1}$ 推出和继承 $f2_{i-1}$ 两种状态；
- $f3_i$ 同样有从 $f2_{i-1}$ 推出和继承 $f3_{i-1}$ 两种状态。

因此有：
$$f1_i=\max(f1_{i-1}+line_i,line_i)$$
$$f2_i=\max(f1_{i-1}+mid_i,f2_{i-1}+mid_i)$$
$$f3_i=\max(f2_{i-1}+line_i,f3_{i-1}+line_i)$$

---
一些小 tips：
- 在 $n \le 2$ 或者 $m \le 2$ 时，构不成矩阵环，可以直接特判然后输出 $-1$；
- 输入可能会有负数，而矩阵环又不能为空，为了保证矩阵环非空，我们要把 $f1_0$、$f2_0$、$f3_0$ 都初始化为一个极小值，例如 $-10^9$。

然后就可以快乐打代码啦！  
整体时间复杂度就是输入时的 $O(nm)$。

## [CODE](https://www.luogu.com.cn/record/154735844)

```cpp
#include <bits/stdc++.h>//个人觉得前面步骤挺清晰的，不写那么多注释了
using namespace std;
const int M = 1e5 + 5,inf = -1e9;//inf是极小值
int a,n,m,line[M],mid[M],f1[M],f2[M],f3[M];//line：每一列的和;mid:中间部分，即最上和最下的和；
int main(){
	cin >> n >> m;
	if(n <= 2 || m <= 2){//此时无法形成矩阵环 
		cout << -1;
		return 0;
	}
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++){
			cin >> a;
			if(i == 1 || i == n){
				mid[j] += a;
			}
			line[j] += a;
		}
	}
	f1[0] = f2[0] = f3[0] = inf;
	for(int i = 1;i <= m;i++){
		f1[i] = max(f1[i - 1] + line[i],line[i]);
		f2[i] = max(f1[i - 1] + mid[i],f2[i - 1] + mid[i]);
		f3[i] = max(f2[i - 1] + line[i],f3[i - 1] + line[i]);
	}
	int maxn = inf;
	for(int i = 1;i <= m;i++){
		maxn = max(maxn,f3[i]);//取最大值
	}
	cout << maxn;
	return 0;
}
```

---

## 作者：lqsy002 (赞：0)

[题目链接](https://www.luogu.com.cn/problem/P7160)。

## 解题思路

矩阵环相当于左侧若干列，上下若干列，右侧若干列。

1. 每一列处理出以该列结尾的左侧若干列的最大和，可能是继承了前面若干列，也可能是单独一列。

2. 处理出上下两行部分，考虑把它和左侧合并，形成一个 C 字形。用 $sum_i$ 代表上下两个元素和，$dp_i$ 表示可以由 $i$ 的上下两个元素组成 C 字型，也可以加入之前已经形成的 C 字型。

3. 补上右侧的，可以继承原来的，也可以补上前面 C 字型的。

具体转移方程可查看代码注释标有操作序号处。

## 参考代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define maxn 100010
#define inf -10000000000
using namespace std;
int n,m,a[15][maxn];
int sum2[maxn],sum1[maxn],ans=inf;
int dp[maxn],dpl[maxn],dpr[maxn];
signed main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>n>>m;
    if(n<=2||m<=2){
        cout<<-1;
        return 0;
    }
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j){
            cin>>a[i][j];
            sum1[j]+=a[i][j];
            if(i==1||i==n)
                sum2[j]+=a[i][j];
        }
    dp[0]=dpl[0]=dpr[0]=inf;
    for(int i=1;i<=m;++i){
        dp[i]=dpl[i]=dpr[i]=inf;
        dpl[i]=max(dpl[i-1]+sum1[i],sum1[i]);   //op1
        if(i>=2)
            dp[i]=max(dpl[i-1]+sum2[i],dp[i-1]+sum2[i]);    //op2
        if(i>=3)
            dpr[i]=max(dpr[i-1]+sum1[i],dp[i-1]+sum1[i]);   //op3
        ans=max(dpr[i],ans);
    }
    cout<<(ans>inf?ans:-1);
    return 0;
}
```

---

