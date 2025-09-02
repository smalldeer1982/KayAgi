# Labs

## 题目描述

In order to do some research, $ n^2 $ labs are built on different heights of a mountain. Let's enumerate them with integers from $ 1 $ to $ n^2 $ , such that the lab with the number $ 1 $ is at the lowest place, the lab with the number $ 2 $ is at the second-lowest place, $ \ldots $ , the lab with the number $ n^2 $ is at the highest place.

To transport water between the labs, pipes are built between every pair of labs. A pipe can transport at most one unit of water at a time from the lab with the number $ u $ to the lab with the number $ v $ if $ u > v $ .

Now the labs need to be divided into $ n $ groups, each group should contain exactly $ n $ labs. The labs from different groups can transport water to each other. The sum of units of water that can be sent from a group $ A $ to a group $ B $ is equal to the number of pairs of labs ( $ u, v $ ) such that the lab with the number $ u $ is from the group $ A $ , the lab with the number $ v $ is from the group $ B $ and $ u > v $ . Let's denote this value as $ f(A,B) $ (i.e. $ f(A,B) $ is the sum of units of water that can be sent from a group $ A $ to a group $ B $ ).

For example, if $ n=3 $ and there are $ 3 $ groups $ X $ , $ Y $ and $ Z $ : $ X = \{1, 5, 6\}, Y = \{2, 4, 9\} $ and $ Z = \{3, 7, 8\} $ . In this case, the values of $ f $ are equal to:

- $ f(X,Y)=4 $ because of $ 5 \rightarrow 2 $ , $ 5 \rightarrow 4 $ , $ 6 \rightarrow 2 $ , $ 6 \rightarrow 4 $ ,
- $ f(X,Z)=2 $ because of $ 5 \rightarrow 3 $ , $ 6 \rightarrow 3 $ ,
- $ f(Y,X)=5 $ because of $ 2 \rightarrow 1 $ , $ 4 \rightarrow 1 $ , $ 9 \rightarrow 1 $ , $ 9 \rightarrow 5 $ , $ 9 \rightarrow 6 $ ,
- $ f(Y,Z)=4 $ because of $ 4 \rightarrow 3 $ , $ 9 \rightarrow 3 $ , $ 9 \rightarrow 7 $ , $ 9 \rightarrow 8 $ ,
- $ f(Z,X)=7 $ because of $ 3 \rightarrow 1 $ , $ 7 \rightarrow 1 $ , $ 7 \rightarrow 5 $ , $ 7 \rightarrow 6 $ , $ 8 \rightarrow 1 $ , $ 8 \rightarrow 5 $ , $ 8 \rightarrow 6 $ ,
- $ f(Z,Y)=5 $ because of $ 3 \rightarrow 2 $ , $ 7 \rightarrow 2 $ , $ 7 \rightarrow 4 $ , $ 8 \rightarrow 2 $ , $ 8 \rightarrow 4 $ .

Please, divide labs into $ n $ groups with size $ n $ , such that the value $ \min f(A,B) $ over all possible pairs of groups $ A $ and $ B $ ( $ A \neq B $ ) is maximal.

In other words, divide labs into $ n $ groups with size $ n $ , such that minimum number of the sum of units of water that can be transported from a group $ A $ to a group $ B $ for every pair of different groups $ A $ and $ B $ ( $ A \neq B $ ) as big as possible.

Note, that the example above doesn't demonstrate an optimal division, but it demonstrates how to calculate the values $ f $ for some division.

If there are many optimal divisions, you can find any.

## 说明/提示

In the first test we can divide $ 9 $ labs into groups $ \{2, 8, 5\}, \{9, 3, 4\}, \{7, 6, 1\} $ .

From the first group to the second group we can transport $ 4 $ units of water ( $ 8 \rightarrow 3, 8 \rightarrow 4, 5 \rightarrow 3, 5 \rightarrow 4 $ ).

From the first group to the third group we can transport $ 5 $ units of water ( $ 2 \rightarrow 1, 8 \rightarrow 7, 8 \rightarrow 6, 8 \rightarrow 1, 5 \rightarrow 1 $ ).

From the second group to the first group we can transport $ 5 $ units of water ( $ 9 \rightarrow 2, 9 \rightarrow 8, 9 \rightarrow 5, 3 \rightarrow 2, 4 \rightarrow 2 $ ).

From the second group to the third group we can transport $ 5 $ units of water ( $ 9 \rightarrow 7, 9 \rightarrow 6, 9 \rightarrow 1, 3 \rightarrow 1, 4 \rightarrow 1 $ ).

From the third group to the first group we can transport $ 4 $ units of water ( $ 7 \rightarrow 2, 7 \rightarrow 5, 6 \rightarrow 2, 6 \rightarrow 5 $ ).

From the third group to the second group we can transport $ 4 $ units of water ( $ 7 \rightarrow 3, 7 \rightarrow 4, 6 \rightarrow 3, 6 \rightarrow 4 $ ).

The minimal number of the sum of units of water, that can be transported from one group to another is equal to $ 4 $ . It can be proved, that it is impossible to make a better division.

## 样例 #1

### 输入

```
3
```

### 输出

```
2 8 5
9 3 4
7 6 1
```

# 题解

## 作者：wlj_55 (赞：10)

### 题目大意

定义两个长度为$n$的数列$A,B$的差异值为:在$A$中任取一个数$u$，在$B$中任取一个数$v$，使得$u>v$的数对对数。

现在有$n^2$个数字，编号为$1$~$n^2$，将这些数字放在一个$n\times n$的矩阵里，使任意两行间的差异值最小。
### 解析
我们考虑$n$很小的情况：

$1.n=1\qquad\space\space\space1$

$2.n=2\qquad\space\space\space1\space 4$

$\qquad\qquad\qquad2\space3$

$3.n=3$，由样例知差异值最小为$4$，所以我们可以构造出下面的矩阵，使其差异值为$4$：

$\qquad\qquad\qquad1\space6\space7$

$\qquad\qquad\qquad2\space5\space8$

$\qquad\qquad\qquad3\space4\space9$

观察一下上面的矩阵，我们可以发现一个规律：

对于一个边长为$n$的矩阵，我们可以这样构造：

第一列$1-n$正序，第二列$n+1-2n$倒序，……,直到排满矩阵。

我们抱着试一试的心态交了上去，发现离奇的过了全部的数据点。那么这是为什么呢？

### 正确性证明
由于我们的差异值具有方向，所以我们要从上往下计算一次差异值，再反方向计算一次。

我们先考虑$n$为奇数的情况。

那么我们的矩阵为:

$$
\begin{bmatrix} 
1 & 2n &2n+1 &...&n(n-1)+1\\\\ 
2 & 2n-1&2n+2&...&n(n-1)+2\\\\
3 & 2n-2&2n+3&...&n(n-1)+3\\\\
...&...&...&...&...\\\\
n & n+1&3n&...&n^2
\end{bmatrix}
$$

对于上面的行和下面的行比较，我们观察到第奇数行的数从上往下递增，偶数行从上往下递减，左边的行的所有数都小于右边的行。

那么上下任意两行比较的差异值为

$$0+2+2+4+4+...+(n-1)+(n-1)=\frac{n^2-1}{2}$$

我们再考虑从下往上比，按照同样的方式推出差异值为

$$1+1+3+3+...+(n-1)+(n-1)+n=\frac{n^2+1}{2}$$

$$\frac{n^2+1}{2}>\frac{n^2-1}{2}$$

所以任意两行间最小差异值的最大为$\frac{n^2-1}{2}$

我们再考虑$n$为偶数的情况。

那么我们的矩阵为：
$$
\begin{bmatrix} 
1 & 2n &2n+1 &...&n^2\\\\ 
2 & 2n-1&2n+2&...&n^2-1\\\\
3 & 2n-2&2n+3&...&n^2-2\\\\
...&...&...&...&...\\\\
n & n+1&3n&...&n(n-1)+1
\end{bmatrix}
$$

从上往下比较，我们的差异值为

$$0+2+2+4+4+...+(n-2)+(n-2)+n=\frac{n^2}{2}$$

从下往上比较，我们的差异值为

$$1+1+3+3+...+(n-1)+(n-1)=\frac{n^2}{2}$$

任意两行间最小差异值最大为$\frac{n^2}{2}$

因为有$n^2$个数，所以总差异值最大为

$$(n^2-1)+(n^2-2)+...+1=\frac{n^4-n^2}{2}$$

一共有$n^2-n$行进行了比较,所以最小差异值$=\frac{n^4-n^2}{2(n^2-n)}$

$$\frac{n^4-n^2}{2(n^2-n)}\le\frac{n^4-n^2}{2(n^2-1)}=\lfloor\frac{n^2}{2}\rfloor$$

即当$n$为奇数时最小差异值最大为$\frac{n^2-1}{2}$，当$n$为偶数时最小差异值最大为$\frac{n^2}{2}$。

证毕。

### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int f[305][305],n,cnt=0;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		if(i&1){
			for(int j=1;j<=n;j++){
				f[j][i]=++cnt;
			}
		}
		else{
			for(int j=n;j>=1;j--){
				f[j][i]=++cnt;
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cout<<f[i][j]<<" ";
		}
		cout<<endl;
	}
}
```

---

## 作者：reyik (赞：2)

贪心！

从第一列开始

奇数列递增

偶数列递减

就没了

```cpp

#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
int n,a[3005][3005],cnt=0;
int main() {
	scanf("%d",&n);
	for (int i=1;i<=n;++i) {
		if(i&1) {
			for (int j=1;j<=n;++j) {
				++cnt;
				a[j][i]=cnt;
			}
		}
		else {
			for (int j=n;j>=1;--j) {
				++cnt;
				a[j][i]=cnt;
			}
		}
	}
	for (int i=1;i<=n;++i) {
		for (int j=1;j<n;++j) printf("%d ",a[i][j]);
		printf("%d\n",a[i][n]);
	}
	return 0;
}
```

---

## 作者：lzy120406 (赞：1)

## [原题](https://codeforces.com/problemset/problem/1236/C)
我们有 $n^2$ 个实验室，编号从 $1$ 到 $n^2$，编号越小的实验室海拔越低。我们需要将这些实验室分成 $n$ 组，每组包含 $n$ 个实验室。对于每一对不同组 $A$ 和 $B$，定义 $f(A,B)$ 为从组 $A$ 到组 $B$ 可以传输的水的总量，即满足 $u > v$ 且 $u$ 在组 $A$，$v$ 在组 $B$ 的实验室对 $(u,v)$ 的数量。

我们的目标是找到一种分组方式，使得所有不同组对 $(A,B)$ 的 $f(A,B)$ 的最小值最大化。

## 思路
实验室的编号越小，海拔越低。因此，编号大的实验室可以向编号小的实验室传输水。

为了使 $f(A,B)$ 的最小值最大化，我们需要确保每一对不同组之间的传输量尽可能均衡。一种直观的策略是将实验室编号均匀地分配到各组中，避免某一组包含过多的高编号或低编号实验室。

具体方法如下：

1. 将实验室编号从 $1$ 到 $n^2$ 按顺序排列。
2. 将这些实验室分成 $n$ 组，每组 $n$ 个实验室。
3. 为了均衡分配，可以采用“蛇形”分配法，即交替分配高编号和低编号实验室到各组中。

对于每一对不同组 $A$ 和 $B$，遍历组 $A$ 中的每个实验室 $u$ 和组 $B$ 中的每个实验室 $v$，统计满足 $u > v$ 的对数。

具体细节看代码。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int groups[305][305] ;// 初始化实验室编号
int main() {
	int n;
	cin >> n;
	// 蛇形分配法
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (i % 2 == 0) {
				groups[j][i] = i * n + j + 1;
			} else {
				groups[n - j - 1][i] = i * n + j + 1;
			}
		}
	}
	// 输出分组结果
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cout << groups[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}
```
时间复杂度 $ \mathcal{O}(n^2) $，可以通过本题。

---

## 作者：Lazy_Labs (赞：1)

# 题意描述
给定一个数 $n$ 构造一个含有 $1-n^2$ 这些数的 $n\times n$ 的矩阵 $G$（不重复不遗漏），定义 $f(a,b)$ 表示 $\sum_{i=1}^n \sum_{j=1}^n [G_{a,i}>G_{b,j}]$。使得最小的 $f(a,b)$ 最大。
# 分析
## 正常方法
首先我们可以证明 $f(a,b)+f(b,a)=n^2$。

根据定义

$f(a,b)+f(b,a)=\sum_{i=1}^n \sum_{j=1}^n [G_{a,i}>G_{b,j}]+\sum_{i=1}^n \sum_{j=1}^n [G_{b,i}>G_{a,j}]=\sum_{i=1}^n \sum_{j=1}^n [G_{a,i}>G_{b,j}]+\sum_{i=1}^n \sum_{j=1}^n [G_{a,i}<G_{b,j}]=n^2$

[证毕]

因此，我们知道，最小值最大只能是 $\left \lfloor \dfrac{n^2}{2} \right \rfloor$。

接下来我们来构造。

首先是偶数，此时的所有 $f(a,b)=\dfrac{n^2}{2}$，构造也很简单，只需将每组的前 $\dfrac{n}{2}$ 个递增，后 $\dfrac{n}{2}$ 递减即可。如：

$\begin{bmatrix}
1 & 2 & 15 & 16 \\
3 & 4 & 13 & 14 \\
5 & 6 & 11 & 12 \\
7 & 8 & 9 & 10 
\end{bmatrix}$

代码如下：
```cpp
for(int i=1;i<=n;i++)
{
	for(int j=1;j<=n/2;j++)printf("%d ",fir++);
	for(int j=1;j<=n/2;j++)printf("%d ",las--);
	puts("");
}
```

然后就是奇数，则 $f(a,b)=\dfrac{n^2 \pm 1}{2}$，我们可以知道：$0+2+2+4+4+\cdots+(n-1)+(n-1)=\dfrac{n^2 - 1}{2}$。

然后我们就可以进行构造，即第一个无被贡献，第二个被贡献前两个，第三个被贡献前两个。基于此，我们可以构造出任意两组只要都满足如下：

设第一组是 $a$，第二组是 $b$。则我们要使得对于 $
\forall i<j$ 满足 $a_i<a_j$ $b_i<b_j$ $a_i<b_j$ $b_i<a_j$（即对所有前一列的均小于后一列的）。

以及对于 $\forall i$ 
$\begin{cases}
a_i<b_i, & \text{if } i \text{ is odd}\\
a_i>b_i, & \text{if } i \text{ is even}
\end{cases}$

如：$1 4 5 8$ 和 $2 3 6 7$

但是因为在同一列上的单调性不变，于是我们可以构造出一个在奇数列单调递增，偶数列单调递减的矩阵，如：

$\begin{bmatrix}
1 & 6 & 7 \\
2 & 5 & 8 \\
3 & 4 & 9  
\end{bmatrix}$

代码如下：
```cpp
int x=1,y=1,now=1;
while(x!=n||y!=n)
{
	g[x][y]=now++;
	if(y&1)
	{
		if(x!=n)x++;
		else y++;
	}
	else 
	{
		if(x!=1)x--;
		else y++;
	}
}
g[n][n]=n*n;
for(int i=1;i<=n;i++)
{
	for(int j=1;j<=n;j++)
	printf("%d ",g[i][j]);
	puts("");
}
```
## 找规律法
首先偶数的构造很简单，和上面一样，但是奇数就没有那么简单了。

这时我们看看样例
```
2 8 5
9 3 4
7 6 1
```

明显它非常的难看，我们把它重排一下
```
1 6 7
2 5 8
3 4 9
```
诶，这不就是我们刚刚得出来的结论吗？

至于证明？我们当然不用自己去证，我们可以写一个 ```checker``` 来检验啊。

检验完发现都为 $\left \lfloor \dfrac{n^2}{2} \right \rfloor$，所以我们就可以提交这份代码了。

# AC CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define fr(x) freopen(#x".in","r",stdin);freopen(#x".out","w",stdout)
#define dbout cerr<<"[DeBug]:"
#define mem(x,y) memset(x,y,sizeof(x))
inline ll read()
{
 	ll x(0),f(1);char c=getchar();
    while(c>'9'||c<'0')f=c=='-'?-1:1,c=getchar();
    while(c>='0'&&c<='9')x=x*10+c-48,c=getchar();
	return f*x;
}
int g[310][310];
int main()
{
	//fr();
//	freopen("a.out","w",stdout);
	int n=read();printf("%d\n",n);
	int fir=1,las=n*n;
	if(n&1)
	{
		int x=1,y=1,now=1;
		while(x!=n||y!=n)
		{
			g[x][y]=now++;
			if(y&1)
			{
				if(x!=n)x++;
				else y++;
			}
			else 
			{
				if(x!=1)x--;
				else y++;
			}
		}
		g[n][n]=n*n;
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
			printf("%d ",g[i][j]);
			puts("");
		}
	}
	else for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n/2;j++)printf("%d ",fir++);
		for(int j=1;j<=n/2;j++)printf("%d ",las--);
		puts("");
	}
	return 0;
}
```
## 附checker
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define fr(x) freopen(#x".in","r",stdin);freopen(#x".out","w",stdout)
#define dbout cerr<<"[DeBug]:"
#define mem(x,y) memset(x,y,sizeof(x))
inline int read()
{
 	int x(0),f(1);char c=getchar();
    while(c>'9'||c<'0')f=c=='-'?-1:1,c=getchar();
    while(c>='0'&&c<='9')x=x*10+c-48,c=getchar();
	return f*x;
}
int g[310][310],n;
int to(int a,int b)
{
	int cnt=0;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
	if(g[a][i]<g[b][j])cnt++;
	return cnt;
}
int main()
{
	//fr();
	freopen("a.out","r",stdin);
	n=read();
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
	g[i][j]=read();
	int minn=INT_MAX;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
	if(i!=j)cerr<<i<<" "<<j<<" "<<to(i,j)<<endl,minn=min(minn,to(i,j));
	printf("%d",minn);
	return 0;
}

```

---

## 作者：Hutao__ (赞：0)

## 思路

一道明显的构造题。

当 $n = 1$ 时，明显构造出的矩阵是：

$$$
\begin{bmatrix}
1
\end{bmatrix}
$$$

当 $n = 2$ 时，构造出的矩阵是：

$$$
\begin{bmatrix}
1&4\\
2&3
\end{bmatrix}
$$$


当 $n = 3$ 时，样例得出的贡献值为4，我们能构造出以下矩阵：

$$$
\begin{bmatrix}
1&6&7\\
2&5&8\\
3&4&9
\end{bmatrix}
$$$

当 $n = 4$ 时，我们能构造出以下矩阵:

$$$
\begin{bmatrix}
1&8&9&16\\
2&7&10&15\\
3&6&11&14\\
4&5&12&13
\end{bmatrix}
$$$

通过上面的矩阵，我们能推出奇数列正着，偶数列倒着的规律。

## 证明

当 $n$ 是偶数时，我们容易得出只要构造出一个让前 $\cfrac{n}{2}$ 个递增，后 $\cfrac{n}{2}$ 个递减即可。

当 $n$ 是奇数时，$f(a,b)=\cfrac{n\pm 1}{2}$ 。对此，我们可以构造出一个奇数列递增，偶数列递减的矩阵。

## 代码


```cpp
//lgRMJ坏了，不保证此代码能通过本题
#include <bits/stdc++.h>
using namespace std;
int n,f[205][205],cnt;
int main(){
	cin >> n;
	for (int i = 1 ; i <= n ; i ++){
		if (i % 2 == 1){
			for (int j = 1;j <= n ; j ++){//正着
				f[j][i] = ++cnt;
			}
		}else{
			for (int j = n;j >= 1 ; j --){//倒着
				f[j][i] = ++cnt;
			}
		}
	}
	for(int i = 1;i <= n; i ++){
		for( int j = 1 ;j <= n;j ++)cout << f[i][j] <<' ';
		cout << '\n';
	}
} 
```

---

## 作者：t162 (赞：0)

越做题智商越低了属于是（

可以考虑答案的上界。

对于 $n^2$ 个数来说，每个数所输出的贡献和输入的贡献之和等于 $n^2-n$（所有的除了和它同一组的数），则总贡献是 $\frac{n^2(n^2-1)}2$。

根据抽屉原理（大概是吧，反正是那个意思），答案的上界为

$$\left\lfloor\frac{n^2(n^2-1)}{2\times n(n-1)}\right\rfloor=\left\lfloor\frac{n^2}{2}\right\rfloor$$

然后只要能够构造出答案等于这个上界的方案，则该方案一定是最优的。

对于 $n$ 为偶数的情况，答案等于 $\frac {n^2}2$。

那么，对于每一组，选择当前未被归类的数中最小的 $\frac n2$ 个和最大的 $\frac n2$ 个。可以证明这样答案为 $\frac {n^2} 2$

对于 $n$ 为奇数的情况，答案为 $\frac {n^2} 2 - \frac 12$。

可以删去最大的 $n$ 个数，按照偶数的方法构造每一组的前 $n-1$ 个数，再用这 $n$ 个数充填到末尾即可。

这样的话，只考虑前 $n-1$ 个数的答案是 $\frac 12(n-1)^2$，展开得到 $\frac 12 n^2 - n + \frac 12$。

对于两组 $G_i,G_j$，若 $G_i$ 末尾的数大于 $G_j$，则

$$f\left(G_i,G_j\right)=\frac 12 n^2 - n + \frac 12 + n=\frac 12 n^2 + \frac 12$$

否则

$$f\left(G_i,G_j\right)=\frac 12 n^2 - n + \frac 12 + n - 1=\frac 12 n^2 - \frac 12$$

答案便是 $\frac 12 n^2 - \frac 12$。

---

