# Prime Square

## 题目描述

Sasha likes investigating different math objects, for example, magic squares. But Sasha understands that magic squares have already been studied by hundreds of people, so he sees no sense of studying them further. Instead, he invented his own type of square — a prime square.

A square of size $ n \times n $ is called prime if the following three conditions are held simultaneously:

- all numbers on the square are non-negative integers not exceeding $ 10^5 $ ;
- there are no prime numbers in the square;
- sums of integers in each row and each column are prime numbers.

Sasha has an integer $ n $ . He asks you to find any prime square of size $ n \times n $ . Sasha is absolutely sure such squares exist, so just help him!

## 样例 #1

### 输入

```
2
4
2```

### 输出

```
4 6 8 1
4 9 9 9
4 10 10 65
1 4 4 4
1 1
1 1```

# 题解

## 作者：45dinо (赞：8)

想到特殊的**非质数**0和1。

尝试只用这两个数完成这个“质方”。

构造每一行，每一列都恰有两个1的矩阵即可。

喜闻乐见的代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
bool pri(int x)
{
	if(x<2)
		return 0;
	for(int i=2;i*i<=x;i++)
		if(x%i==0)
			return 0;
	return 1;
}
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			for(int l=1;l<=n;l++)
				if(l==i||l==i%n+1)
					cout<<1<<" ";
				else
					cout<<0<<" ";
			cout<<endl;
		}
	}
	return 0;
}
```


---

## 作者：tuzhewen (赞：6)

这个题目其实并没有多么麻烦，简单思考一下就可以发现只要我们处理好了一行，整个矩阵就可以了。

因为我们可以每次把一行向左移一位，这样的话，对于一个$n\times n$的矩阵就完全被覆盖了，简单的举个栗子：

现在我们得到了一个合法的序列：`1 4 6 8`，那么我们开始构造整个矩阵：

```
1 4 6 8
8 1 4 6(向右移动一位)
6 8 1 4(同上)
4 6 8 1(同上)
```

然后这样就是满足条件的了。

那么我们考虑先把一整行都填成$1$，然后可以发现如果$n$是质数，那么直接合法，如果$n$不是质数，我们就去找到第一个大于$n$的质数(记为$sum$)作为这一行的和，那么我们就改动这一行的任意一个位置，将其改为$sum-n+1$(这样才能保证和为$sum$)，然后再判断这个是不是质数，如果不是则继续去找下一个合法的$n$（要提前把素数表筛出来），一直做就可以了。

### $ACcode:$
```cpp
#include<bits/stdc++.h>
#define F(i,l,r) for(register int i=l;i<=r;i++)
#define D(i,r,l) for(register int i=r;i>=l;i--)
#define ll long long
#define mem(a,b) memset(a,b,sizeof(a))
#define p_b push_back
#define m_p make_pair
#define il inline
#define fi first
#define se second
const int INF=0x3f3f3f3f;
using namespace std;
int T;
int n;
int a[105][105];
int prime[100005],cnt;
bool isp[100005];
void shai() {
	F(i,2,100000) isp[i]=1;
	F(i,2,100000) {
		if(isp[i]) prime[++cnt]=i;
		F(j,1,cnt) {
			if(i*1ll*prime[j]>100000) break;
			isp[i*prime[j]]=0;
		}
	}
}//筛法
int main() {
	scanf("%d",&T);
	shai();
	while(T--) {
		scanf("%d",&n);
		F(i,1,n) F(j,1,n) a[i][j]=1;//把所有的都填成1
		ll sum=n;
		do{
			int pos=upper_bound(prime+1,prime+1+cnt,sum)-prime;
			sum=prime[pos];//找合法的sum，其实不用二分的，一个下标一直++就好了（是我懒得写了）
		}while(isp[sum-n+1]);//看看更改过后的那个数字是不是素数，不是才合法
		F(i,1,n) a[i][i]=sum-n+1;//把对角线都改成sum-n+1，其实还是上面所说的“把这一行向右移一位”，只不过是因为整个矩阵都是1，只更改对角线就能达到这个效果了
		F(i,1,n) {
			F(j,1,n) printf("%d ",a[i][j]);
			puts("");
		}//输出
	}
	return 0;
}

```

---

## 作者：Sqrtyz (赞：3)

简单构造题。

### 题意

+ 构造出一个 $n \times n$ 的数字方阵，使得每一个位置上的数都不是素数，每一行 / 列的和是素数。

+ 只能使用非负整数。

### 解题

首先我们在整个方阵中全填 $0$，再在其基础上修改一些数。

比赛时最开始的想法是填一个类似

```
2 0 0 0 
0 2 0 0
0 0 2 0
0 0 0 2
```
的方阵。然而这并不满足每一个位置上的数都是素数。

然后突然想到，可以这样填：

```
1 0 0 1
0 1 1 0
0 1 1 0
1 0 0 1
```
就是两个对角线都填上 $1$，显然这样是可以的。

对于 $n$ 为奇数，特别地，我们要小小修改一下：

```
1 0 0 0 1
0 1 1 1 0
0 1 1 1 0
0 1 1 1 0
1 0 0 0 1
```

就像这样。中心 $3 \times 3$ 的全填 $1$。

然后就可以了。

---

比赛时叉人的时候还看到另一种填法，觉得也不错：

```
1 1 0 0 0
0 1 1 0 0
0 0 1 1 0
0 0 0 1 1
1 0 0 0 1
```
---
### 写在后面

构造题是比较考验思维的一类题目，希望读者们要引起重视（虽然在 NOIP 中貌似没咋考过）。

有兴趣的读者，可以思考更多的填法（锁题之后看到了一堆奇怪的填法）。

---

## 作者：Meaninglessness (赞：2)

## B. Prime Square

**题目大意:**

>给你正方形边长 $n$,请构造一个 $n\times n$ 的矩阵并满足:
> 
> - 每个数都不超过$10^5$;
> - 每个数都不是质数;
> - 每行或每列的和都为质数。

***

**解题思路:**

看似是一道很难的题,尤其是加上样例那个复杂的构造,让我们很难发现规律。

我们可以先将每个位置都写$1$,如果 $n$ 为质数则直接满足要求。

但如果 $n$ 是个合数,那我们就无法满足要求。

不过我们还可以选择更改,我们需要尽量保证修改的数只会都不在同一行同一列上,这样它们相互之间就不会影响 。所以我们就可以在其中一条对角线上的所有数修改为 $k$。这样相当于每一行每一列都加上 $(k-1)$ 。再判断这时加和是不是质数就行了。

***

**代码实现:[Code](https://www.luogu.com.cn/paste/d98rejkh)　时间复杂度$O(T)$**

---

## 作者：Ludo (赞：1)

这是一道构造题。

$\bold{Idea}$

这种构造题我的理解是用拼凑解出。

看 $n=2$ 的样例，我们有这样一种简单的解。

```latex
1 1
1 1
```

我们可以学到的是，由于 $1$ 不是质数，但拼出来的是质数。

赛时提醒给了我们一个思路，$0$ 也不是质数。

这或许是想让我们把 $0$ 塞进矩阵？

那么 $n=3$ 的呢？

经过一番挣扎，我们得到了这个。

```latex
1 0 1
1 1 0
0 1 1
```

可不可以拼出其他大点的矩阵呢？

$n=4$ (用两个 $n=2$ 的矩阵拼出)

```latex
1 1 0 0
1 1 0 0
0 0 1 1
0 0 1 1
```

$n=8$ (用三个 $n=2$ 的矩阵拼出)

```latex
1 1 0 0 0 0 0 0
1 1 0 0 0 0 0 0
0 0 1 1 0 0 0 0
0 0 1 1 0 0 0 0
0 0 0 0 1 1 0 0
0 0 0 0 1 1 0 0
0 0 0 0 0 0 1 1
0 0 0 0 0 0 1 1
```

$n=5$ (用一个 $n=3$，一个 $n=2$ 的矩阵拼出)

```latex
1 0 1 0 0
1 1 0 0 0
0 1 1 0 0
0 0 0 1 1
0 0 0 1 1
```

思想已经大致出来了，重点在怎么实现。

$\bold{Code}$

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int matrix2[3][3] = {{0, 0, 0}, {0, 1, 1}, {0, 1, 1}};
int matrix3[4][4] = {{0, 0, 0, 0}, {0, 1, 0, 1}, {0, 1, 1, 0}, {0, 0, 1, 1}};
int t;
int a[121][121];
int n, nx, ny, nn;
void build(int x, int y)
{
    for (int i = x; i <= x + 2; i++)
    {
        for (int j = y; j <= y + 2; j++)
        {
            a[i][j] = matrix3[i - x + 1][j - y + 1];
        }
    }
}
void build2(int x, int y)
{
    for (int i = x; i <= x + 1; i++)
    {
        for (int j = y; j <= y + 1; j++)
        {
            a[i][j] = matrix2[i - x + 1][j - y + 1];
        }
    }
}
int main()
{
    scanf("%d", &t);
    while (t--)
    {
        memset(a, 0, sizeof(a));
        scanf("%d", &n);
        nn = n;
        nx = 1, ny = 1;
        if (n & 1)
        {
            build(nx, ny);
            n -= 3;
            nx += 3;
            ny += 3;
        }
        for (; n > 0; n -= 2)
        {
            build2(nx, ny);
            nx += 2;
            ny += 2;
        }
        for (int i = 1; i <= nn; i++)
        {
            for (int j = 1; j <= nn; j++)
            {
                printf("%d ", a[i][j]);
            }
            printf("\n");
        }
    }
    return 0;
}
```


---

## 作者：Werner_Yin (赞：1)

[更好的阅读体验](https://www.cnblogs.com/werner-yin/p/solution-CF-1436B.html)
## 题目大意
构造一个 $n*n$ 的矩阵,满足里面每个数都不为质数,但每行每列之和为质数．

## solution
刚拿到题被吓到了一下，以为要写爆搜，然后判断是不是满足条件．

但是这是Ｂ题，一定还有更快的方法，

注意到，

> all numbers on the square are **non-negative** integers not exceeding $10^5$;

只要非负？那么 $0$ 也可以了。

一下子简单了，我们只要这样构造：

```latex
1 1 0 0 0
0 1 1 0 0
0 0 1 1 0
0 0 0 1 1
1 0 0 0 1
```
也就是当 $i = j$ 或者 $i = j+1$ 或者 $i = n,j = 1$时 $a[i][j]$ 为$1$，其他为 $0$。

1,0 都不是质数，但每行每列之和为 $2$ ，是质数。

于是就水完了这道题。

## 代码
~~快读、头文件自行脑补~~
```cpp
int n;
int main (){
	int T; read(T);
	while(T--){
		read(n);
		for(int i = 1;i <= n;i++){
		    for(int j = 1;j <= n;j++)
			if(j == i+1||j == i||(j == 1&&i==n)) printf("1 ");
			else printf("0 ");
		    puts("");
		}
		printf("\n");
	}
	return 0;
}
```

---

## 作者：jun头吉吉 (赞：0)

## 题意
定义一个$n\times n$素数正方形为:
- 所有的数不大于$10^5$
- 所有的数不是质数
- 每行、每列的和都是质数

输入$n$，输出大小为$n$的素数正方形
## 题解
>Problem B. Prime Square
> *****
> I just want to remind you that:

> Smallest non-negative integers are 0, 1, 2, 3, ...

> Smallest prime numbers are 2, 3, 5, 7, ...

~~提示有些明显啊~~

思考：如果$n$为偶数，把对角线上的数全填$1$，剩下为$0$，每行每列都为$2$，显然可行

那么若$n$为奇数，则$\dfrac{n+1}2$只有$1$，那么我们只需要在$(1,\dfrac{n+1}2)$与$(\dfrac{n+1}2,1)$填上$1$，那么第$1$行，第$1$列为$3$，其他为$1$，显然可行。

## 代码
```cpp
int t,n,a[200][200];
signed main(){
	in::read(t);
	while(t--){
		in::read(n);
		memset(a,0,sizeof a);
		for(int i=1,j=1;i<=n&&j<=n;i++,j++)a[i][j]=1;
		for(int i=n,j=1;i>=1&&j<=n;i--,j++)a[i][j]=1;
		if(n&1)a[1][(n+1)/2]=1,a[(n+1)/2][1]=1;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++)
				printf("%d ",a[i][j]);
			printf("\n"); 
		}
	}
	return 0;
}
```

---

## 作者：WuhenGSL (赞：0)

对于一个 $n$ 阶方阵，我们发现：

当 $ n$ 为偶数时，对角线元素为 $1$ ，其他元素为 $0$ 时，可以保证每一行每一列的和都是 $2$，满足题意。

当 $n$ 为奇数时，则需要在以上构造的基础上在中心元素所在的行列填一个 $1$，使得中心元素所在的行列和为 $2$，而加入新元素的行列的和为 $2$ 或 $3$，仍然满足题意。

$n=4\left[ \begin{matrix} 1 & 0 & 0 & 1\\ 0 & 1 & 1 & 0  \\ 0 & 1 & 1 & 0 \\ 1 & 0 & 0 & 1\end{matrix} \right]$

$n=5\left[ \begin{matrix} 1 & 0 &1 & 0 & 1\\ 0 & 1 & 0 & 1 & 0  \\ 1 & 0 & 1 & 0 & 0 \\ 0 & 1 & 0 & 1 & 0\\ 1 & 0 & 0 & 0 & 1  \\\end{matrix} \right]$

```cpp
//AC代码
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 101
using namespace std;
int T,a[N][N],n;
int main()
{
	scanf("%d",&T);
	while(T--){
		memset(a,0,sizeof a);//别忘了清数组
		scanf("%d",&n);
		if(n==2){
			printf("%d %d\n%d %d\n",1,1,1,1); 
			continue;
		}
		for(int i=1;i<=n;++i)a[i][i]=1;
		for(int i=n,j=1;i>=1,j<=n;--i,++j)a[i][j]=1;
		if(n%2==1)a[1][n/2+1]=1,a[n/2+1][1]=1;
		for(int i=1;i<=n;++i){
			for(int j=1;j<=n;++j)printf("%d ",a[i][j]);
			printf("\n");
		}
		
	}
	return 0;
}
```

---

