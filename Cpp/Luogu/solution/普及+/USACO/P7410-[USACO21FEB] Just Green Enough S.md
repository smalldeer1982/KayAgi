# [USACO21FEB] Just Green Enough S

## 题目描述

Farmer John 的草地可以被看作是一个由 $N \times N$ 个正方形方格（$1 \leq N \leq 500$）组成的方阵（想象一个巨大的棋盘）。由于土壤变异性，某些方格中的草可能更绿。每个方格 $(i,j)$ 可以用一个整数绿度值 $G(i,j)$ 来描述，范围为 $1 \ldots 200$。

Farmer John 想要给他的草地的一个子矩阵拍摄一张照片。他希望确保这一子矩阵看上去足够绿，但又不绿得过分，所以他决定拍摄一个 $G$ 的最小值恰好等于 100 的子矩阵。请帮助他求出他可以拍摄多少不同的照片。子矩阵最大可以为整个草地，最小可以仅为一个方格（共有 $N^2(N+1)^2/4$ 个不同的子矩阵——注意该数可能无法用 $32$ 位整数型存储，所以你可能需要使用 $64$ 位整数类型，例如 C++ 中的 long long）。


## 说明/提示

#### 测试点性质：

 - 对于 $50\%$ 的数据，满足 $N\le 200$。
 - 对于另外 $50\%$ 的数据，没有额外限制。

供题：Brian Dean

## 样例 #1

### 输入

```
3
57 120 87
200 100 150
2 141 135```

### 输出

```
8```

# 题解

## 作者：szzzzs (赞：33)


## [题目传送门](https://www.luogu.com.cn/problem/P7410)

芜湖~

起飞~

### $Subtask 1-4$

设 $ A,B$ 两点，一个作为矩阵左上角的点，一个作为右下角的点，这样就可以确定一个矩阵区间。

接下来直接枚举其中的点判断此举这是否合法即可。

```cpp
for(int i=1; i<=n; i++)
for(int j=1; j<=n; j++)
{
	if(a[i][j]<100) continue;
	for(int ii=i; ii<=n; ii++)
	for(int jj=j; jj<=n; jj++)
	{
		pan1=0,pan2=0;
		for(int l=i; l<=ii; l++)
		{
			if(pan2) break;
			for(int r=j; r<=jj; r++)
			{
				if(a[l][r]==100) pan1=1;
				if(a[l][r]<100) pan2=1;
				if(pan2==1) break;
			}
		}
		if(pan1&&!pan2) ans++;
}
```
### $Subtask1-8$
首先将所有绿度值大于等于 $100$ 的格子看做可以形成矩阵的格子求出矩阵个数。然后将绿度值等于 $100$ 的格子删除后再次求出格子数再次求出矩阵个数。前者减去后者就是答案。

那么怎么求出由多个小正方向形组成的不规则图形的子矩阵个数便是我们当前要解决的问题了。

具体思路如下：

首先把上面数据转化位由 $0,1$ 组成的矩阵，样例转化出来后如下：
```cpp
0 1 0
1 1 1
0 1 1
```

我们可以从 $（1,1）$ 开始枚举到 $（n，n）$.
因此我们只需要算一下当前的点与右下形成的矩阵个数即可（因为与左上方的小正方形形成的矩阵在先前应已被判断）。

怎么处理与右下方小正方形形成的矩阵数呢?

~~我的方法比较 $LJ$ 只是简单的枚举。~~

从左向右枚举，直到没有 $1$ 的时候暂停，记录当前宽度的最小值（因为如果此列超过了上面长度的最小值组成的就不是矩阵了），然后在从上到下枚举，看一看能不能枚举到下一行（当然是从最左边向下枚举）。

就这样一个一个枚答案就出来。

**$Code$**
```cpp
void dt(int xx,int yy,int maxx)
{
	int maxn;
	if(!a[xx][yy]) return;
	for(int i=yy;i<=maxx;i++)
	if(!a[xx][i])break;
	else ans++,maxn=i;
	dt(xx+1,yy,maxn);
}
int main()
{
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)	dt(i,j,n);
	swap(ans,ans2);
	for(int i=1;i<=num;i++)
	a[la[i].x][la[i].y]=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)	dt(i,j,n);
	cout<<ans2-ans<<endl;
	return 0;
}
```



### $Subtask 1-10$

上面的代码复杂度~~应该~~是$O_{n^4}$。听说 $O_{n^3}$ 的复杂度就可以过所以我将数据先处理了一下。简单说就是将一个数下面连续接了几个$1$处理了出来拿样例举个栗子。
```cpp
030
122
011
```

这时只需要从左向右枚举一排只可，不再需要向下枚举列了。但是要保证每次想右枚举时，本列列长不能大于最小列长。

**$Code$**
```cpp
#include<iostream>
#include<cstdio>
#define N 510
using namespace std;
int a[N][N]；					//处理之前
int n,num
int val[N][N];//处理后的数组
long long ans2,ans;;
struct bala{int x,y;} la[N*N];			//存储等于100的点
void dt(int xx,int yy)  			//枚举当前点可形成的矩阵数
{
	int minn=val[xx][yy];			//minn是最小列长
	for(int i=yy;i<=n;i++)
		if(!a[xx][i]) break;
		else {
			minn=min(minn,val[xx][i]);
			ans+=minn;
		}
}
void prt() 					//预处理
{
	for(int j=1;j<=n;j++)
		for(int i=n;i>=1;i--) {
			val[i][j]=0;		//因为用了两遍所以在这里需要清空
			if(a[i][j]) val[i][j]=val[i+1][j]+1;
		}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
	{
		scanf("%d",&a[i][j]);
		if(a[i][j]==100)
		la[++num].x=i,la[num].y=j;
		if(a[i][j]>=100) a[i][j]=1;
		else a[i][j]=0;
	}
	prt();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)	dt(i,j,n);
	swap(ans2,ans);
	for(int i=1;i<=num;i++)
		a[la[i].x][la[i].y]=0;
	prt();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)	dt(i,j,n);
	cout<<ans2-ans<<endl;
	return 0;
}
```

**来到你谷的第一篇题解，望过！**

~~码风较丑勿喷~~



---

## 作者：YBaggio (赞：20)

### 备注：此做法来自nzq巨佬
## 题意：
FJ 有一个边长为 $n (n \leq 500)$， 共有 $n^2$ 个格子的正方形草地，每一个格子有一个 $1...200$ 的绿度值。对于 FJ 的这个草地，有很多个子矩阵。现在需要你求出子矩阵中所有格子的最小值是 $100$ 的子矩阵的个数。

**样例:**

输入
```
3
57 120 87
200 100 150
2 141 135
```
输出
```
8
```
_____
## 思路
我们可以发现答案显然等于最小值小于 $100$ 的矩阵的个数减去最小值小于等于 $100$ 的个数。

**如何计算这两个值呢？**

我们设函数 `query(m)` 为最小值小于 $m$ 的子矩阵个数，那么答案就等于 `query(100)-query(101)` 。

这个函数怎么写呢，我们将所有小于 $m$ 的格子设为 $1$, 将所有大于等于 $m$ 的格子设为 $0$， 我们对于每一行记一个 $sum_{i,j}$。

代码如下:

```cpp
for(int i=1;i<=n;i++){
    for(int j=1;j<=n;j++){
        if(a[i][j]<maxx)b[i][j]=1,sum[i][j]=0;
        else sum[i][j]=sum[i][j-1]+1,b[i][j]=0;
    }
}
```
其中 $a$ 表示该格子的绿度值， $b_{i,j}=1$ 时表示该格子的绿度值小于 $m$ 等于 $1$ 则表示该格子大于 $m$。

显然，如果 $b_{i,k \ldots j}$ 都为 $1$ 时， $sum_{i,j}=j-k+1$， 如果 $b_{i,j}=0$ 则 $sum_{i,j}=0$。

记录完了 $sum$ 和 $b$ 后，我们枚举每一个格子，我们把这个格子作为一个子矩阵的右下角，为了方便，用 $x$ 表示。那么能与 $x$ 符合的左端点有几个呢？我们发现符合条件的子矩阵需要满足它每一个格子都要大于等于 $m$， 这时候我们统计的 $sum$ 就有用了，我们枚举所有与 $x$ 在同一列且在 $x$ 上方的格子(即行数小于等于 $x$ 的格子)，我们看这些格子在 $sum$ 数组中的最小值。将每个最小值累加起来就是 `query(m)` 的答案了。

AC代码：
```cpp
#include<bits/stdc++.h>
#pragma G++ optimize(3)
using namespace std;
#define inf 1000000010
const int maxn=510;
int n,a[maxn][maxn],b[maxn][maxn],sum[maxn][maxn];
long long query(int maxx){
    long long ans=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(a[i][j]<maxx)b[i][j]=1,sum[i][j]=0;
            else sum[i][j]=sum[i][j-1]+1,b[i][j]=0;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(b[i][j])continue;
            long long Min=inf;
            for(int k=i;k>=1;k--){
                Min=min(Min,(long long)sum[k][j]);
                ans+=Min;
            }
        }
    }
    return ans;
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            scanf("%d",&a[i][j]);
        }
    }
    printf("%lld",query(100)-query(101));
    return 0;
}
```
 

---

## 作者：QQ82272760 (赞：11)

如果记除去所有 $G<100$ 元素后矩形的个数为 $ans1$，除去所有 $G\le 100$ 元素后矩形的个数为 $ans2$，则显然答案为 $ans=ans1-ans2$。
以上两种情况都可以归结为求出一个 01矩阵中所有元素均为 $1$ 的矩形的个数，下面来讨论如何快速求解。

如果求出以每个为 $1$ 的位置为右下角的满足条件的矩形的个数，那么答案就为所有这些个数的总和。为求出最后结果，我们可以假设 $cnt[i][j]$ 表示点 $(i,j)$ 及其右边连续 $1$ 的个数，那么他可以 $O(n^2)$ 求出来
```cpp
for(int i=1;i<=n;i+=1){
	for(int j=1;j<=n;j+=1){
		if(a[i][j]) cnt[i][j]=cnt[i][j-1]+1;
        else cnt[i][j]=0;
	}
}
```
现在假设有这样一个 01 方阵（每个元素记作 $a_{ij}$）
$$
\left[
\begin{aligned}
&1\ \ 0\ \ 1\ \ 0\\
&1\ \ 1\ \ 1\ \ 1\\
&0\ \ 1\ (1)\ 0\\
&1\ \ 0\ \ 0\ \ 1
\end{aligned}
\right]
$$
假设现在要求以打括号那个 $1$ 为右下角的矩形总个数，则每个矩形可以由它的左上角唯一表示出来。不难发现，第三行可取左上角个数为 $cnt[3][3]=2$，第二行可取左上角个数为 $min(cnt[3][3],cnt[2][3])=2$，第一行为 $min(cnt[3][3],cnt[2][3],cnt[1][3])=1$，共有 $5$ 个矩形，于是用 $O(n^3)$ 就可以求解完成了。
```cpp
for(int i=1;i<=n;i+=1){
    for(int j=1;j<=n;j+=1){
    	m=cnt[i][j];
    	for(int k=i;k>=1;k-=1){
    		m=min(m,cnt[k][j]);
    		res+=m;
    	}
    }
}
```
虽然这道题 $O(n^3)$ 可以过，但并不代表它不能优化，要做高级玩家就要对此优化。我们发现若对于 $k<i$ 有 $cnt[i][j]\le cnt[k][j]$，那么实际上 $(j-cnt[k][j]+1,k)$ 到 $(j-cnt[i][j]+1,k)$ 这部分点是从现在开始就无法再被取到的，就可以考虑把 $cnt[i][j]$ 和 $cnt[k][j]$ 想方法“合并”，这样就相当于把 $cnt[k][j]$ 删掉，那么对于 $i>k$ 都有 $cnt[i][j]>cnt[k][j]$，也就是对每一列都维护一个单调递增的单调栈。栈中的元素为有序数对，每个数对存储最大能取到的矩形的长 $c$ 和对应的行的数目 $h$。假设到第 $i$ 行时某列对应的可取矩形的左上角数目为 $s$，则
$$s=\sum_{i=1}^{top}stk[i].c\times stk[i].h$$

每当加入一个新的 $cnt$，就将本列的 $s$ 加上 $cnt$。如果本列对应的栈顶为 $(c,h)$ 满足 $c\ge cnt$，就将栈顶删除，把计数器 $H$ 加上 $h$，同时 $s-=(c-cnt)\times h$，最后将 $(cnt,H+1)$ 加入栈顶并更新 $cnt+=s$ 就行了。

上述方法每一列都能在 $O(n)$ 内求解出所有的 $s$，总时间复杂度为 $O(n^2)$。

上代码！
```cpp
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;
int n,g[501][501],a[501][501];
ll cnt,s[501],ans;
pair<ll,ll>q[501][501];
ll check(){
	int top;
	ll x,res=0;
	for(int i=1;i<=n;i+=1){
		q[i][0].first=s[i]=0;  //初始化所有栈为空
	}
	for(int i=1;i<=n;i+=1){
		cnt=0;
		for(int j=1;j<=n;j+=1){
			if(a[i][j]==1) cnt+=1;
			else cnt=0;
			x=1; s[j]+=cnt; top=q[j][0].first;
			while(top&&q[j][top].first>=cnt){  //去掉不符合的栈顶
				s[j]-=(q[j][top].first-cnt)*q[j][top].second;
				x+=q[j][top--].second;
			}
			q[j][++top]=make_pair(cnt,x);  //加入
			q[j][0].first=top;
			res+=s[j];  //统计
		}
	}
	return res;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i+=1){
		for(int j=1;j<=n;j+=1) scanf("%d",&g[i][j]),a[i][j]=1;
	}
	for(int i=1;i<=n;i+=1){
		for(int j=1;j<=n;j+=1){
			if(g[i][j]<100) a[i][j]=0;  //去掉<100的点
		}
	}
	ans=check();  //第一次求解 ans1
	for(int i=1;i<=n;i+=1){
		for(int j=1;j<=n;j+=1){
			if(g[i][j]==100) a[i][j]=0;  //去掉=100的点
		}
	}
	ans-=check();  //ans=ans1-asn2
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：qwqUwU (赞：6)

## 题意化简

给定一个矩阵，求元素最小值为 $100$ 的子矩阵的个数。

## 题目分析

由于题目要求子矩阵最小绿度值 $x$ 恰好为 $100$，那么可以考虑把数分为 $3$ 类：

- $-1:x<100$

- $0:x=100$

- $1:x>100$

那么，合法的子矩阵就变成了不包含 $-1$ 且至少包含一个 $0$ 的子矩阵。

分别处理子矩阵的两个要求：

## 不包含 $-1$

直接把 $-1$ 全部删掉，对剩下的不规则图形进行求解。

## 至少包含一个 $0$
 
考虑到这不好直接求，这里采用容斥的思想，分别求出所有子矩阵个数 $val1$ 与不包含 $0$ 的个数 $val2$，这样最终答案 $ans=val1-val2$。

对于 $val2$，可以把 $0$ 改成 $-1$ 重新跑一遍，这样就把求 $val2$ 转化为和求 $val1$ 一模一样的方法。

现在只要算出 $val1$ 就可以了。

具体步骤如下：

1. 枚举每一个点作为子矩阵的左上角（当然任意方向均可），复杂度 $\varTheta(n^2)$。

2. 对当前列向下搜，直到碰到 $-1$ 或者超过前面的最大长度 $maxn$，然后把  $maxn$更新为当前搜的长度，复杂度 $\varTheta(n)$。

3. 向右枚举一列，复杂度$\varTheta(1)$。

4. 重复 $2$ 和 $3$，直到向右搜到 $-1$，复杂度 $\varTheta(n)$。

总时间复杂度为 $\varTheta(n^4)$。

上一下代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,a[501][501];
ll val1,val2;
ll count(int x,int y){//这里实现的是后三步的操作
	int maxn=n;//限制最大长度
	ll val=0;//计数器
	for(int i=x;i<=n;i++){
		int j=y;
		if(a[i][y]==-1)return val;//向右搜到头了
		while(j<=maxn&&a[i][j]!=-1)j++,val++;//逐个向下搜
		maxn=j-1;//更新限制
	}
	return val;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			int t;
			scanf("%d",&t);
			if(t>100)a[i][j]=1;
			if(t<100)a[i][j]=-1;//1,0,-1转换
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			val1+=count(i,j);//计算全部
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(a[i][j]==0)
				a[i][j]=-1;//删去0
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			val2+=count(i,j);//计算不包含0
	printf("%lld",val1-val2);
	return 0;
}
```
**直接提交这份代码,你将会获得 $80pts$ 的~~好~~成绩。** 

分析上文中的第 $2$ 步，每次都需要 $\varTheta(n)$ 的时间往下遍历。

**那么，为什么不把它拿出来单独计算呢？**

利用前缀和思想，我们可以开一个 $cnt(i,j)$ 数组表示位置 $(i,j)$ 往下（算上自己）有几个连续的非 $-1$，而这只需要 $\varTheta(n^2)$。

那么此时的 $\operatorname{count}$ 函数就从 $\varTheta(n^2)$ 压到了 $\varTheta(n)$，总时间复杂度压到了 $\varTheta(n^3)$，足够 AC。

上一下代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,a[501][501],cnt[501][501];
ll val1,val2;
void make(){//预处理cnt部分
	memset(cnt,0,sizeof(cnt));
	for(int i=1;i<=n;i++)
		for(int j=n;j>=1;j--)
			if(a[i][j]!=-1)
				cnt[i][j]=cnt[i][j+1]+1;
}
ll count(int x,int y){
	ll val=0;
	int minn=n;//以前搜到过的最小长度
	for(int i=x;i<=n;i++){
		if(a[i][y]==-1)break;
		minn=min(minn,cnt[i][y]);//更新最小长度
		val+=minn;//当前最小长度是多少,就新增多少个矩形
	}
	return val;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			int t;
			scanf("%d",&t);
			if(t>100)a[i][j]=1;
			if(t<100)a[i][j]=-1;
		}
	make();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			val1+=count(i,j);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(a[i][j]==0)
				a[i][j]=-1;
	make();//因为图更改了所以要重新计算
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			val2+=count(i,j);
	printf("%lld",val1-val2);
	return 0;
}
```
**完结撒花！**

---

## 作者：guozhetao (赞：5)

看不懂大佬思路的看过来，本文将**详细地**带你讲解（图文结合）。本题解思路来自[ 12345678hzx](https://www.luogu.com.cn/user/670775)，为了方便理解，变量名大部分和 hzx 相同。

## 思路

前置知识：[ST 表](https://www.luogu.com.cn/problem/P3865)。运用 $n$ 维的 $minn$ 数组求最小值。$minn_{i,j,k}$ 表示第 $i$ 行第 $j$ 个数及后面共 $2^k$  个数的最小值，这里不重点展开来讲。

### 部分代码
```cpp
	scanf("%lld",&n);
	for(int i = 1;i <= n;i++) for(int j = 1;j <= n;j++) scanf("%lld",&mmin[i][j][0]);
	for(int k = 1;k <= n;k++) {
		for(int j = 1;(1 << j)  <= n;j++) {
			for(int i = 1;i + (1 << (j - 1)) <= n;i++) {
				mmin[k][i][j] = min(mmin[k][i][j - 1],mmin[k][i + (1 << (j - 1))][j - 1]);
			}
		}
	}
```

接着，我们枚举长方形的左边，右边和底边，计算一共可以取几个。左边，右边我用 $i,j(i \le j)$ 表示，底边用 $k$ 表示。$x,y$ 分别表示上一个最小值小于 $100$ 的行和上一个最小值等于 $100$ 的行。下面的图片是初始情况。

![](https://cdn.luogu.com.cn/upload/image_hosting/6gcmmv2g.png?x-oss-process=image/resize,m_lfit,h_500,w_500)

如图所示，第一行 $i$ 列到 $j$ 列的最小值小于 $100$，我们更新 $y \gets 1$。因为以 $k$ 为底的不可能有，所以 $ans$ 不变。

![](https://cdn.luogu.com.cn/upload/image_hosting/xl7j6xib.png?x-oss-process=image/resize,m_lfit,h_500,w_500)

如图所示，当 $k = 2$ 时最小值等于 $100$。我们更新 $x \gets 2$。因为以 $x$ 为底的共可以有 $x - y$ 个，所以 $ans \gets ans + x - y$。

![](https://cdn.luogu.com.cn/upload/image_hosting/5t9ejer2.png)

如图所示，当 $k = 3$ 时最小值大于 $100$。这时需要分类讨论：当 $x > y$ 时 $ans \gets ans + x - y$（与 $k = 2$ 时同理）。否则 $ans$ 不变（因为在取到最小值等于 $100$ 的同时也会取到最小值小于 $100$ 的）。

![](https://cdn.luogu.com.cn/upload/image_hosting/cu5hoqxm.png?x-oss-process=image/resize,m_lfit,h_500,w_500)

所以，经过每次操作后，我们只需要将 $ans \gets ans + \max(x - y,0)$。
### 部分代码
```cpp
for(int i = 1;i <= n;i++) llog[i] = log(i) / log(2);//表示 i 在二进制下的位数，需要预先储存避免重复运算。
	for(int i = 1;i <= n;i++) {
		for(int j = i;j <= n;j++) {
			int x = 0,y = 0;
			for(int k = 1;k <= n;k++) {
				int v = llog[j - i + 1];
				int s = min(mmin[k][i][v],mmin[k][j-(1<<v)+1][v]);//取出最小值
				if(s < 100) y = k;
				if(s == 100) x = k;
				ans += max((long long)0,x - y);
			}
		}
	}
```


---

## 作者：_Fontainebleau_ (赞：4)

### 题意

- 给定一个 $n\times n$ 的矩阵。矩阵中的每一个元素都有一个值 $a_{i,j}$。求最小值为 $100$ 的子矩阵个数。

- $1\le n\le 500$。

### 做法

## 解法 1

**前置芝士**：悬线法

因为要求矩阵中的最小值为 $100$，那么我们可以把 $a_{i,j}$ 修改掉，具体而言：

- 若 $a_{i,j}>100$，则 $a_{i,j}=2$。
- 若 $a_{i,j}=100$，则 $a_{i,j}=1$。
- 若 $a_{i,j}<100$，则 $a_{i,j}=0$。

首先十分套路的处理出点 $(i,j)$ 向左向右分别能拓展出的最大距离 $l_{i,j},r_{i,j}$。

然后你一列列地扫，设当前列为 $x$，每次处理出两个数组， $L,R$。 $L_{i,j}=\min\limits_{k=i}^j l_{k,x}$ 表示当前第 $i$ 行至第 $j$ 行能向左拓展 $L_{i,j}$。$R$ 数组同理。

然后一列一列找。若 $a_{i,j}=1$ 则暴力向上向下拓展至第 $u$ 行，第 $v$ 行。每次产生的贡献就是 $L_{u,v}\times R_{u,v}$。

注意要开 long long。

没了。时间复杂度是 $O(n^3)$ 的。

但是常数巨 dark /se /se /se

### 代码

```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,ans;
int a[502][502];
int l[502][502],r[502][502];
int L[502][502],R[502][502];
inline int read()
{
    int x=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-f;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    return x*f;
}
signed main()
{
    n=read();
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            int x=read();
            if(x<100)    a[i][j]=0;
            if(x==100)  a[i][j]=1;
            if(x>100)    a[i][j]=233;    
        }
    for(int j=1;j<=n;j++)
    {
        for(int i=1;i<=n;i++)
            for(int k=1;k<=n;k++)
                if(a[i][k]) l[i][k]=l[i][k-1]+1;
        for(int i=1;i<=n;i++)
            for(int k=n;k>=1;k--)
                if(a[i][k]) r[i][k]=r[i][k+1]+1;
        for(int i=1;i<=n;i++)
        {
            L[i][i]=l[i][j],R[i][i]=r[i][j];
            for(int k=i+1;k<=n;k++)
                L[i][k]=min(L[i][k-1],l[k][j]),R[i][k]=min(R[i][k-1],r[k][j]);
        }
        for(int i=1;i<=n;i++)
            if(a[i][j]==1)
            {
                for(int k=i;k>=1&&a[k][j];k--)
                    for(int z=i;z<=n&&a[z][j];z++)   
                        ans+=L[k][z]*R[k][z];
                a[i][j]=l[i][j]=r[i][j]=0;
            }
    }
    printf("%lld\n",ans);
    return 0;
}
```

## 解法 2

**前置芝士**：悬线法+单调栈

挺 NB 的。目前没怎么卡就 Rk1  了。

首先考虑怎么查询最小值大于等于 $x$ 的子矩阵个数？不妨记为 $\operatorname{num}(x)$。

我们可以用 $l_{i,j}$ 表示点 $(i,j)$ 可以向左最远可以到达的点，即使得 $\min \limits_{k=l_{i,j}}^j a_{i,k} \ge x$ 。

最后的答案就是 $\operatorname{num}(100)-\operatorname{num}(101)$。

怎么求 $\operatorname{num}(x)$ 呢？

暴力的话，是 $O(n^2)$ 枚举每一个点，作为左下角，然后向上拓展，求贡献。时间复杂度是 $O(n^3)$，可以通过。

但是怎么优化呢？我们发现，每次网上枚举，向左拓展的长度都是取 $\min$ 的，于是想到用单调栈维护。然后我们枚举列，假设当前为第 $j$ 列。再枚举列上的每一个点。用单调栈维护当前这一列 $l$。用一个 $ans$ 数组记忆化，$ans_i$ 表示以 $(i,j)$ 为左下脚的合法矩阵数。每次弹出比该点拓展远的点，然后简单算一算当前点的贡献即可。

### 做法（给出关键的 $\operatorname{num}$ 函数）

```c++
inline long long num(int lim)
{
	long long res=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(a[i][j]<lim)	l[i][j]=j;
			else	l[i][j]=l[i][j-1];
	for(int j=1;j<=n;j++)
	{
		l[0][j]=j,tp=0;
		for(int i=1;i<=n;i++)
		{
			while(l[st[tp]][j]<l[i][j])	tp--;
			ans[i]=ans[st[tp]]+(j-l[i][j])*(i-st[tp]);
			res+=ans[i];st[++tp]=i;
		}
	}
	return res;
}
```



---

## 作者：KSToki (赞：4)

# 题目大意
求最小值为 $100$ 的子矩阵的个数。
# 前置芝士
悬线法，没了。
# 题目分析
还是挺裸的，根据数据范围可以看出需要一个 $O(n^3)$ 的做法。

用悬线法先处理出向左右能扩展的最大位置，一列一列扫，预处理出两个数组 $minl$ 和 $minr$，$minl_{i,j}$ 表示当前列第 $i$ 行到第 $j$ 行同时向左扩展的最远位置。每当找到一个 $100$ 以后暴力上下扩展统计答案即可。注意扫完后需要将该位置赋值成 $0$，因为这样已经统计了含有该位置的 $100$ 的所有合法子矩阵，不删除的话当扫下一个 $100$ 时可能还会算到。

这样我们需要每次更新向左右能扩展的最大位置。比赛时~~懒~~打得有点急，直接全部重算了，其实只需要重算那一行的。不过并不影响复杂度，~~但导致了我巨大的常数~~。
# 代码
比赛时的代码，可能有点乱，理解了的话问题应该不大。他都提示你开 `long long` 了不会有人不开吧。
```cpp
#include<bits/stdc++.h>
#define R register
#define I inline
#define ll long long
#define ull unsigned long long
#define LL __int128
#define db double
using namespace std;
#define pii pair<int,int>
#define mp(x,y) make_pair(x,y)
#define piii pair<pair<int,int>,int>
#define mp3(x,y,z) make_pair(make_pair(x,y),z)
#define fi first.first
#define se first.second
#define th second
#define putint(x) printf("%d\n",x)
#define putll(x) printf("%lld\n",x)
#define putull(x) printf("%llu\n",x)
#define lowbit(x) ((x)&(-(x)))
#define inf (0x7fffffff)
#define INF (1e18)
#define eps (1e-8)
I int read()
{
	char ch=getchar();
	int res=0,flag=1;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			flag=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res*flag;
}
int n,a[505][505],l[505][505],r[505][505],minl[505][505],minr[505][505];
ll ans;
bool v[505][505];
int main()
{
	n=read();
	for(R int i=1;i<=n;++i)
		for(R int j=1;j<=n;++j)
		{
			a[i][j]=read();
			if(a[i][j]==100)
				a[i][j]=1;
			else if(a[i][j]<100)
				a[i][j]=0;
			else
				a[i][j]=2;
		}
	for(R int j=1;j<=n;++j)
	{
		for(R int i=1;i<=n;++i)
			for(R int k=1;k<=n;++k)
				if(a[i][k])
					l[i][k]=l[i][k-1]+1;
		for(R int i=1;i<=n;++i)
			for(R int k=n;k;--k)
				if(a[i][k])
					r[i][k]=r[i][k+1]+1;
		for(R int k=1;k<=n;++k)
		{
			minl[k][k]=l[k][j];
			minr[k][k]=r[k][j];
			for(R int u=k+1;u<=n;++u)
			{
				minl[k][u]=min(minl[k][u-1],l[u][j]);
				minr[k][u]=min(minr[k][u-1],r[u][j]);
			}
		}
		for(R int i=1;i<=n;++i)
			if(a[i][j]==1)
			{
				for(R int k=i;k&&a[k][j];--k)
					for(R int u=i;u<=n&&a[u][j];++u)
						ans+=minr[k][u]*minl[k][u];
				a[i][j]=l[i][j]=r[i][j]=0;
			}
	}	
	putll(ans);
    return 0;
}
```


---

## 作者：Orange_qwq (赞：2)

# 前言

提供一种较为容易理解的 $O(n^3)$ 做法。

# 题意

给你一张表格，求表格内有多少个子矩阵的最小值为 $100$。

# 思路

## Step 1

首先考虑 $O(n^4)$ 暴力方法。

令 $lie_i$ 为当前第 $i$ 列的最小值。

枚举上、下、左、右边界。先确定上、下边界，更新 $lie$ 数组，然后枚举左右边界，如果有最小值等于 $100$ 的，答案 $+1$；如果有最小值小于 $100$ 的，直接 `break` 跳出此次右边界循环。

## Step 2

其次考虑优化。

由于每次枚举左右边界都要找最小值（及等于 $100$ 的和小于 $100$ 的），可以先预处理出每一列向右边延伸到第一个等于 $100$ 的位置，及每一列向右边延伸到第一个小于 $100$ 的位置。（相当于处理右边界）

然后再从左边开始扫，如果能延伸到的第一个小于 $100$ 的位置要比第一个等于 $100$ 的位置远，就可以把答案加起来。

加起来？加什么呢？

由于我们枚举的是左边界，那么右边界最近必须到第一个等于 $100$ 的位置，最远到第一个小于 $100$ 的位置**之前**。对于答案来说，长度每增加 $1$，答案就加 $1$，故答案应该加的是第一个小于 $100$ 的位置减掉第一个等于 $100$ 的位置。

# $\texttt{AC Code}$

需要注意的是，题面已经提醒了要开 `long long`。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
int n, a[510][510], lie[510], eq[510], ls[510];
// lie -> 第 i 列最小值
// eq -> 每一列向右边延伸的第一个等于 100 的位置 
// ls -> 每一列向右边延伸的第一个小于 100 的位置 
ll ans;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			scanf("%d", &a[i][j]);
	for (int i = 1; i <= n; ++i) {     // 上边界 
		for (int j = 1; j <= n; ++j) lie[j] = a[i][j];
		for (int j = i; j <= n; ++j) { // 下边界 
			for (int k = 1; k <= n; ++k) lie[k] = min(lie[k], a[j][k]);
			// 求每列最小值 
			eq[n + 1] = ls[n + 1] = n + 1; // 先做标记 
			for (int k = n; k; --k) {      // 因为是求向右延伸，故从右往前推 
				eq[k] = eq[k + 1];
				ls[k] = ls[k + 1];
				if (lie[k] == 100) eq[k] = k;
				if (lie[k] < 100) ls[k] = k;
			}
			for (int k = 1; k <= n; ++k)
				if (ls[k] > eq[k]) ans += ls[k] - eq[k]; // 累加答案 
		}
	}
	printf("%lld", ans);
	return 0;
} 
```

最后，祝 **CSP2022 R2 RP += INF**！！

---

## 作者：User439000 (赞：1)

### 怎么求矩形组合数
考虑一下当有一排正方形时候，这一排的正方形中所含的矩阵个数是不是可以通过组合数学算出即用首项加尾项乘项数除以二。而其中的矩阵组成是不是由大于一百和等于一百和小于一百所组相互之间或独立形成的矩阵的并集。由题意得出，其中合法的矩阵包括只含等于一百的矩阵或者只含等于一百和大于一百的矩阵。该部分等于去除掉小于一百的矩阵再除掉只含大于一百的矩阵。
### 算法设计
怎么用代码实现呢？我们将小于 100 的点赋值为比较小的负数，将等于一百的赋为一，大于一百的赋为零，然后我们将竖列前缀和。对于竖列任意一段，如果其值大于等于一，那么这是个合法的子阵（我们可以通过我们的特殊赋值来判断，可以自行思考下）。那么合法的子矩阵可以和相邻的合法矩阵构成新矩阵，也能和半合法的矩阵（只含大于一百的矩阵其前缀和必为零构成新矩阵。那接下来问题就变成了我们前面所讲的求组合方法。那我们如何排除小于零的矩阵呢？我们把每个竖列的子段和遍历，找出非负数的段，再依据上面的数学方法，可求出当前子段竖列合法矩阵数。那我们再枚举一下竖列子段长度和子段位置即可无遗漏求出所有合法矩阵个数。
### Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,s[502][502],sum,y[502][502];
int ji(int s,int e){
	return (s+e)*e/2;//首项加尾项乘项数除以二
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
	for(int u=1;u<=n;u++)
	{
		cin>>s[i][u];
		if(s[i][u]>100)
		s[i][u]=0;
		else if(s[i][u]<100) s[i][u]=-1e5;
		else s[i][u]=1;
	}
	
		for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		y[i][j]=y[i][j-1]+s[i][j];//竖列前缀和 
				
		for(int i=1;i<=n;i++)
		{
			for(int j=i;j<=n;j++){//模拟边界 即模拟子段的长度和其位置 
				int bg;
				
				for(int jj=1;jj<=n;jj++)//bg是第一个子段前缀和不为负数的点 
					if(y[jj][j]-y[jj][i-1]>=0)
					{
						bg=jj;
						break;
					}
				int len1=0;
				for(int u=bg;u<=n;u++){//枚举竖列即寻找一段前缀和为非负数的段 
					if(y[u][j]-y[u][i-1]<0)
					{
						int len=0;
						
						for(int k=u-1;k>=u-len1;k--)//再
						{
							if(y[k][j]-y[k][i-1]!=0) 
							{
								sum=sum-ji(1,len);
								len=0;
								continue;
							}
							else len++;
						}
						
						sum=sum-ji(1,len);
						sum+=ji(1,len1);
						len1=0;
						len=0;
					}
					else len1++;	
				}
						int len=0;
						for(int k=n;k>=n-len1+1;k--)//枚举我们所找到的段，看看其中有多少连续的等于零的段 
						{
							if(y[k][j]-y[k][i-1]!=0)//找到就减去这段只含零的组合方案
							{
								sum=sum-ji(1,len);
								len=0;
								continue;
							}
							else len++;
						}
						sum=sum-ji(1,len);//最后再加上非负数段的总矩阵数 
						sum+=ji(1,len1);	
			}
		}
	cout<<sum;
	
}
```



---

## 作者：_edge_ (赞：1)

我比较傻，不太会用 $101 - 100$，因此在这里介绍一下我的处理方式。

首先，枚举矩阵的上界和下界，然后列从左到右扫过去，很简单一种想法，我们把列最小值小于 $100$ 的视为 $2$，把列的最小值是 $100$ 的视为 $1$，答案即为当前这一列到达的 $1$ 的列减去能到达的 $2$ 的列。

这部分即为这一列在这个上界下界的容差。

考虑如何去维护这个东西，如果我们已经知道了某一列的最小值，那么就很容易去计算出这个东西。

一个简单的想法是预处理好所有列的，可惜那样会爆内存，介绍一种比较傻的方法，$O(n^2 \log n)$ 预处理，$O(n^3)$ 来计算答案，就 ST 表处理每一列的每个区间的最小值。

然后常数巨大，这种想法也只能这样，请大家谨慎尝试，题解区里面没有，所以我来补一下。

```cpp
#include <iostream>
#include <cstdio>
#define int long long 
using namespace std;
const int INF=505;
int n,a[INF][INF],f[INF][INF][25],kk,ans,lg[INF];
int query(int l,int ll,int rr) {
	int kk=lg[rr-ll+1];
	return min(f[l][ll][kk],f[l][rr-(1<<kk)+1][kk]);
}
signed main()
{
	ios::sync_with_stdio(false);
	cin>>n;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			cin>>a[i][j];
	lg[0]=-1;
	for (int i=1;i<=n;i++) lg[i]=lg[i>>1]+1;
	for (int i=1;i<=n;i++) {
		for (int j=1;j<=n;j++) f[i][j][0]=a[j][i]; // 第 i 列，第 j 行 
		for (int k=1;k<31;k++) {
			if ((1ll<<k)>n) continue;
			for (int l=1;l<=n;l++) {
				f[i][l][k]=min(f[i][l][k-1],f[i][l+(1<<(k-1))][k-1]);
			}
		}
	}
	for (int i=1;i<=n;i++) {
		for (int j=i;j<=n;j++) {
			int pre=0,pre1=0;
			for (int k=1;k<=n;k++) {
				if (query(k,i,j)<100) pre=k;
				else if (query(k,i,j)==100) pre1=k;
				ans+=max(0ll,pre1-pre);
//				cout<<i<<" "<<j<<" "<<k<<" "<<pre1-pre+1<<" fad?\n";
			}
		}
	}
	cout<<ans<<"\n";
	return 0;
}
```


---

## 作者：0xFF (赞：1)

#### 题目大意


------------
求最小值为 $100$ 的矩形个数。

#### 思路分析

------------
只要知道一个矩阵的左上角和右下角的坐标就可以确定该矩阵，故考虑枚举所有的矩阵并一一进行检查。

这样做的复杂度是 $\Theta(n^6)$ 显然不可行。

首先考虑对于检查的复杂度进行优化，由于一个矩形是否可行只与它的最小值有关，故考虑在输入的时候将所有等于 $100$ 的数按照原数储存，所有大于 $100$ 的数当做 $0$，所有小于 $100$ 的数当做无穷小。使用二维前缀和优化，如果一个矩阵的和小于 $0$ 说明一定有小于 $100$ 的值存在，故不满足条件，由于一个满足条件的矩阵中不一定只有一个 $100$，所以答案就是和大于等于 $100$ 的矩阵个数。

此时的时间复杂度为 $\Theta(n^4)$，加速后勉强可以通过第五个测试点。

接下来考虑如何优化枚举矩阵的边界。

首先考虑在序列上的操作。

记录序列中小于 $100$ 的数的位置，这些数将这个序列分成了若干个不相关的区间，对于每个这样的区间分别进行求解并将答案累加即可。

如果这段区间中没有 $100$，则这段区间对于答案的贡献是 $0$，如果有一个 $100$，则贡献为 $100$ 的位置到这段区间的首尾距离的乘积。

如果这段区间中有不止一个 $100$，如果仍按照上述对于一个 $100$ 的情况进行计算会出现重复的情况。

以两个 $100$ 的情况为例：

![1](https://cdn.luogu.com.cn/upload/image_hosting/xqert8s5.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

以左边的 $100$ 为最小值的矩阵左边界可以到这段区间的左边界，右边界可以到第二个 $100$，所以答案就是第一段区间长度和第二段区间长度的乘积，以右边的 $100$ 为最小值的矩阵的左边界可以到区间的左边界，右边界可以到区间的右边界，故答案为第一段区间长度和第三段区间长度的乘积和第二段区间长度和第三段区间长度的乘积的和，也就是第二个 $100$ 的左边的区间长度和右边的区间长度的乘积。

故可得一般情况下答案是所有 $100$ 到左边界的长度和到下一个 $100$ 的长度的乘积。

由此，只需枚举矩形的上下边界，此时只需要存下上边界到下边界这段中的最小值，此时的情况就是序列上的情况。

```cpp
int main(){
	int n = read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			a[i][j] = read();
		}
	}
	for(int i=1;i<=n;i++){
		for(int k=1;k<=n;k++){
			mn[k]=INF;
		}
		for(int j=i;j<=n;j++){
			int pos1 = 0 , pos2 = 0;
			for(int k=1;k<=n;k++){
				mn[k] = min(mn[k],a[j][k]);
			}
			for(int k=1;k<=n;k++){
				if(mn[k] < 100){
					if(pos2 > pos1){
						calc(pos1,pos2,k);
					}
					pos1 = k;
				}
				if(mn[k] == 100){
					if(pos2 > pos1){
						calc(pos1,pos2,k);
					}
					pos2 = k;
				}
			}
			if(pos2 > pos1){
				calc(pos1,pos2,n+1);
			}
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：jimmy2021 (赞：1)

我们定义函数 $\text{f}(x)$ 代表最小值大于等于 $x$ 的元素组成的子矩阵个数，那么最终的答案就是 $\text{f}(100) - \text{f}(101)$。同时，为了方便求 $\text{f}$ 函数的值，我们定义 $\text{t}(x, y)$ 代表 $(x, y)$ 这个点最多能往上「延伸」多少个元素，即求最大的、使得 $\forall a_{x, i} = 1\ (i \in [y - \text{t}(x, y) + 1, y])$ 的 $\text{t}(x, y)$。

而具体怎么用 $\text{t}$ 数组呢？放一张图，你就大概理解了。

\*注：红色格子代表新增的贡献（对应到代码中，这个方案数就是列 $\times$ 高），绿色格子代表当前格子，蓝色格子代表以前的贡献，灰色格子代表障碍（$a_{i, j} < x$ 的点），白色格子代表未参加贡献的格子。

![](https://cdn.luogu.com.cn/upload/image_hosting/z8epbaav.png)

也就是说对于当前的坐标，找到最左边的、$\text{t}$ 数组中的值不低于当前格子的 $\text{t}$ 值的纵坐标，将该纵坐标对应的贡献加上新增的贡献得到当前格子对应的贡献。而「求出 $\text{t}$ 数组中的值不低于当前格子的 $\text{t}$ 值的纵坐标」这个过程可以用`单调栈`维护。其他细节见代码。

代码：
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <limits.h>
#include <cstring>
using namespace std;

typedef long long LL;
typedef pair<int, int> PII;
const int INF = 0x3f3f3f3f, INF_BIT = 0x3f;

const int N = 510, M = 510;

LL n;
LL a[N][M];

LL m;

LL t[N][M];

LL st[N], tp;

LL d[N];

LL f(LL x){
    for(LL i = 1;i <= n;i++)
        for(LL j = 1;j <= m;j++)
            if(a[i][j] >= x) t[i][j] = t[i - 1][j] + 1;
            else t[i][j] = 0;
    
    LL ret = 0;
    
    for(LL i = 1;i <= n;i++){
        tp = 0;
        //为了配合43行while循环（注解在38~42行）进行处理
        t[i][0] = 0;
        for(LL j = 1;j <= m;j++){
            //此处不判tp是因为要用st[tp] = 0来更新前面的几个点*
            //*前面的几个点：无法再用前面的点的d值更新该点的d值的点
            //而此题不能用在while循环里更新d值的写法，
            //因为tp = 0时，st[tp] = 0，t[i][st[tp]] = 0，
            //0小于等于所有的t值，所以会死循环
            while(t[i][st[tp]] > t[i][j]) tp--;
            //画图理解（图在上面）
            d[j] = d[st[tp]] + (j - st[tp]) * t[i][j];
            //累加答案
            ret += d[j];
            //插入栈中
            st[++tp] = j;
        }
    }
    
    return ret;
}

int main(){
    scanf("%lld", &n);
    
    m = n;
    
    for(LL i = 1;i <= n;i++)
        for(LL j = 1;j <= m;j++)
            scanf("%lld", &a[i][j]);
    
    printf("%lld\n", f(100) - f(101));
    return 0;
}
```

---

## 作者：Mars_Dingdang (赞：1)

一道悬线法好题，如果数据范围大一点绝不止黄题（见 P4147）。

## 题目大意
给定一个 $n\times n$ 的矩阵，求最小值为 $100$ 的子矩阵的个数，$n\le 500$。

## 大体思路
首先，我们思考一个暴力的方法：枚举所有子矩阵。同时，我们对值为 $100$ 和值小于 $100$ 记录两类二维前缀和 $A_{i, j}, B_{i, j}$。

然后，枚举所有子矩阵，设其左上角为 $(a, b)$, 右下角为 $(c, d)$，则根据容斥可得，其中 $100$ 的个数为 $A_{c, d}-A_{c, b -1}-A_{a-1,d}+A_{a-1,b-1}$，同理可得小于 $100$ 的数的个数为 $B_{c, d}-B_{c, b -1}-B_{a-1,d}+B_{a-1,b-1}$。若其中小于 $100$ 的数的个数为 $0$ 且 $100$ 的个数不小于 $1$ 则令答案加一。

由于子矩阵共有 $\dfrac{n^2(n+1)^2 }{4}$，时间复杂度为 $O(n^4)$。具体实现时可以加入一定的优化，如预先判断是否有小于 $100$ 的数出现等，综合可得 $80$ 分。

```cpp
int num_0(int a, int b, int c, int d) {
	return B[c][d] - B[c][b - 1] - B[a - 1][d] + B[a - 1][b - 1];
} // 小于 100 的数的个数
int num_100(int a, int b, int c, int d) {
	return A[c][d] - A[c][b - 1] - A[a - 1][d] + A[a - 1][b - 1];
} // 等于 100 的数的个数
int main () {
	read(n);
	rep(i, 1, n)
		rep(j, 1, n) { // 输入+前缀和预处理
			read(x[i][j]);
			A[i][j] = A[i - 1][j] + A[i][j - 1] - A[i - 1][j - 1] + (x[i][j] == 100);
			B[i][j] = B[i - 1][j] + B[i][j - 1] - B[i - 1][j - 1] + (x[i][j] < 100);
		}
	ll ans = 0;
	rep(a, 1, n) // 枚举
		rep(b, 1, n){
			if(x[a][b] < 100) continue;
			int mi = n;
			rep(c, a, n)
				rep(d, b, mi) {
					if(num_0(a, b, c, d) > 0) {
						mi = min(mi, d);
						break;
					}
					if(num_100(a, b, c, d) > 0) ans++;
				}
		}
	writeln(ans);
	return 0;
}
```
_______________
由此可以发现，在计算过程中会有 $<100$ 的数作为障碍，进而联想到一题 [P4147 玉蟾宫](https://www.luogu.com.cn/problem/P4147)。那一题是利用悬线法和单调栈在 $O(nm)$ 复杂度内计算无障碍点的最大子矩阵，本题则是计算无障碍点的子矩阵计数，两者有极大的相似之处。因此，可以利用悬线法 + 单调栈解决本题。

由于要求包含 $100$，可以利用容斥原理，先计算不包含 $<100$ 的数的子矩阵 $F(100)$，再计算不包含 $<101$ 的数的子矩阵 $F(101)$，二者做差即可。

具体计算 $F(x)$ 时，我们用 $l_{i, j}$ 记录从 $(i,j)$ 向左最多能扩展到的位置，即
$$l_{i,j}=\begin{cases}j, a_{i, j}<x\\l_{i, j-1}, a_{i,j}\ge x\end{cases}$$
然后，枚举每一列 $j$，对于第 $i$ 行，通过单调栈向上寻找向左宽度比其小（即 $l_{t,j}>l_{i,j}, t<i$）的一行 $t$，则该格的贡献为 $f_i=f_t+(j-l_{i,j})\times (i-t)$，累加贡献即可得到 $F(x)$。

![](https://cdn.luogu.com.cn/upload/image_hosting/tbhh7akb.png)

## 完整代码
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
#define rep(ii,aa,bb) for(re int ii = aa; ii <= bb; ii++)
#define Rep(ii,aa,bb) for(re int ii = aa; ii >= bb; ii--)
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef pair<int, int> PII;
const int maxn = 505;
namespace IO_ReadWrite {
	#define re register
	#define gg (p1 == p2 && (p2 = (p1 = _buf) + fread(_buf, 1, 1<<21, stdin), p1 == p2) ? EOF :*p1++)
	char _buf[1<<21], *p1 = _buf, *p2 = _buf;
	template <typename T>
	inline void read(T &x){
		x = 0; re T f=1; re char c = gg;
		while(c > 57 || c < 48){if(c == '-') f = -1;c = gg;}
		while(c >= 48 &&c <= 57){x = (x<<1) + (x<<3) + (c^48);c = gg;}
		x *= f;return;
	}
	inline void ReadChar(char &c){
		c = gg;
		while(!isalpha(c)) c = gg;
	}
	template <typename T>
	inline void write(T x){
		if(x < 0) putchar('-'), x = -x;
		if(x > 9) write(x/10);
		putchar('0' + x % 10);
	}
	template <typename T>
	inline void writeln(T x){write(x); putchar('\n');}
}
using namespace IO_ReadWrite;
int n, a[maxn][maxn], l[maxn][maxn], stk[maxn], top, f[maxn];
inline ll F(int x) {
	ll ans = 0;
	rep(i, 1, n)
		rep(j, 1, n) {
			if(a[i][j] < x) l[i][j] = j;
			else l[i][j] = l[i][j - 1]; // 预处理
		}
	rep(j, 1, n) {
		l[0][j] = j;
		top = 0;
		rep(i, 1, n) {
			while(top && l[stk[top]][j] <= l[i][j]) top --; // 单调栈
			f[i] = f[stk[top]] + (j - l[i][j]) * (i - stk[top]); //之前+新贡献
			ans += f[i]; // 累加贡献
			stk[++top] = i;
		}
	}
	return ans;
}
int main () {
	read(n);
	rep(i, 1, n)
		rep(j, 1, n) 
			read(a[i][j]);
	writeln(F(100) - F(101)); // 容斥	
	return 0;
}
```

---

## 作者：__Seniorious__ (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P7410)
###### ~~居然没有大佬用st表 来水一波题解~~
## 题意浅析
求给出矩阵中最小值为 $100$ 的子矩阵个数

## 解题思路

st表大法好！

我们尝试枚举每个矩阵  
那么也就是枚举矩阵上下行、左右列编号  

若先枚举上下行 $i,j$  
那么接下来就要枚举左右列的坐标 （时间复杂度 $O(n^2)$）  
因为时间复杂度最大 $O(n^3)$  
所以我们尝试从 $1\sim n$ 枚举列来分析  

那么当前扫到的列 $k$ 有三种情况：  
+ 当前列最小值大于 $100$ 
+ 当前列最小值结束 $100$ 
+ 当前列最小值大于 $100$

我们发现列上最小值居然可以用st表维护！  
于是就有了：
```cpp
for(int k=1;k<=lg[n];k++)
	for(int i=1;i<=n;i++)
		for(int j=1;j+(1<<(k))-1<=n;j++)
			mn[i][j][k]=min(mn[i][j][k-1],mn[i][j+(1<<(k-1))][k-1]);

```
再回来看第 $k$ 列  
我们发现对于第 $k1-1$ 列最小值小于 $100$，
第 $k1$ 列最小值大于等于 $100$，  
第 $k2$ 列最小值等于 $100$，
第 $k$ 列最小值小于等与 $100$，   
且 $1\le k1\le k2\le k\le n$ 时，  
新增矩阵的个数即为 $(k-k2)\times (k2-k1+1)$  
所以只要枚举这样的区间即可

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[601][601],mn[601][601][11],lg[601]={-1},k1,k2,nw,t;
long long ans;
bool flag,f1;
char c;
int read()
{
	c=getchar(),t=0;
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9')
	{
		t=(t<<1)+(t<<3)+c-'0';
		c=getchar();
	}
	return t;
}
int main()
{
	n=read();
	for(int i=1;i<=n;i++)lg[i]=lg[i/2]+1;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			a[i][j]=read();
			mn[j][i][0]=a[i][j];
			mn[j][i-1][1]=min(a[i-1][j],a[i][j]);
		}
	}
	for(int k=1;k<=lg[n];k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j+(1<<(k))-1<=n;j++)
				mn[i][j][k]=min(mn[i][j][k-1],mn[i][j+(1<<(k-1))][k-1]);
	for(int i=1;i<=n;i++)
	{
		for(int j=i;j<=n;j++)
		{
			for(int k=1;k<=n;k++)
			{
				nw=min(mn[k][i][lg[j-i+1]],mn[k][j+1-(1<<lg[j-i+1])][lg[j-i+1]]);
				if(nw<100)
				{
					if(flag&f1)ans+=(k-k2)*(k2-k1+1);
					flag=f1=false;
					continue;
				}
				if(!flag)k1=k,flag=true;
				if(nw==100)
				{
					if(f1)ans+=(k-k2)*(k2-k1+1);
					k2=k,f1=true;
				}
			}
			if(flag&f1)ans+=(n+1-k2)*(k2-k1+1);
			flag=f1=false;
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：shaozhehan (赞：0)

[原题链接](https://www.luogu.com.cn/problem/P7410)

题目大意：

给你一个 $n\times m$ 的矩阵，第 $i$ 行第 $j$ 列的元素为 $a_{i,j}$。问有多少个子矩阵里的元素的最小值等于 $100$。

思路：

考虑前缀和预处理出 $a_{i,j}$ 里小于 $100$ 与等于 $100$ 的个数，方向为列，数组名分别为 ```pre_column_100``` 与 ```pre_column_less100```，代码如下。
```cpp
pre_column_100[i][j] = pre_column_100[i - 1][j];// 方向为列
pre_column_less100[i][j] = pre_column_less100[i - 1][j];
if (a[i][j] == 100){
    pre_column_100[i][j]++;
} else if (a[i][j] < 100){
    pre_column_less100[i][j]++;
}
```
然后，我们枚举子矩阵的第一行与最后一行，并用类似双指针法记录出最后一个含有 $100$ 和小于 $100$ 的数的列坐标，分别记作 ```last_100``` 与 ```last_less100```。我们枚举子矩阵最右边一列，利用刚才求出的前缀和来维护上述两个变量。最后，因为最右边一列保证了我们的子矩阵不会重复，所以如果 ```last_100``` 大于 ```last_less100```，就说明最后一列合法，那么我们把最后记录答案的变量 $ans$ 加上 ```last_100``` 与 ```last_less100``` 的差，就大功告成了，代码如下。
```cpp
for (int i = 1; i <= n; i++){
   for (int j = i; j <= n; j++){
      int last_100 = 0, last_less100 = 0;
      for (int k = 1; k <= n; k++){
         if (pre_column_less100[j][k] - pre_column_less100[i - 1][k] > 0){
            last_less100 = k;
         } else if (pre_column_100[j][k] - pre_column_100[i - 1][k] > 0){
            last_100 = k;
         }
         if (last_100 > last_less100){
            ans += last_100 - last_less100;
         }
      }
   }
}
```
时间复杂度为 $\mathcal{O}(n^3)$。

坑点：
- $ans$ 一定要开 ```long long```，否则可能会炸精度！

完整代码贴在[这里](https://www.luogu.com.cn/paste/pchlevt6)。

---

