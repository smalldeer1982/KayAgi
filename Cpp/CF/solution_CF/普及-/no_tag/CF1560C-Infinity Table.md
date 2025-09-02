# Infinity Table

## 题目描述

Polycarp has found a table having an infinite number of rows and columns. The rows are numbered from $ 1 $ , starting from the topmost one. The columns are numbered from $ 1 $ , starting from the leftmost one.

Initially, the table hasn't been filled and Polycarp wants to fix it. He writes integers from $ 1 $ and so on to the table as follows.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1560C/fbe22cdb57a9c1d91e54741c4b3ed27f17ef455a.png)The figure shows the placement of the numbers from $ 1 $ to $ 10 $ . The following actions are denoted by the arrows.The leftmost topmost cell of the table is filled with the number $ 1 $ . Then he writes in the table all positive integers beginning from $ 2 $ sequentially using the following algorithm.

First, Polycarp selects the leftmost non-filled cell in the first row and fills it. Then, while the left neighbor of the last filled cell is filled, he goes down and fills the next cell. So he goes down until the last filled cell has a non-filled neighbor to the left (look at the vertical arrow going down in the figure above).

After that, he fills the cells from the right to the left until he stops at the first column (look at the horizontal row in the figure above). Then Polycarp selects the leftmost non-filled cell in the first row, goes down, and so on.

A friend of Polycarp has a favorite number $ k $ . He wants to know which cell will contain the number. Help him to find the indices of the row and the column, such that the intersection of the row and the column is the cell containing the number $ k $ .

## 样例 #1

### 输入

```
7
11
14
5
4
1
2
1000000000```

### 输出

```
2 4
4 3
1 3
2 1
1 1
1 2
31623 14130```

# 题解

## 作者：Doqin07 (赞：5)

![](https://cdn.luogu.com.cn/upload/image_hosting/fr5ielkw.png)

本题找规律即可

可以看到 $1-x$ 是以这样“蛇形”的方式排列的，我们把一圈看成一段 eg. $5,6,7,8,9$, 对于第 $n$ 段，不难看出这一段的结束为 $n^2$，所以中间数（也就是第 $n$ 行，第 $n$ 列的数）为 $n^2-n+1$ 。

对于每一个要求坐标的 $cur$ ，可以看出分**三种**情况，
1. 正好为中间数，直接输出 $n,n$
2. 大于中间数，那我们可以确定它在第 $n$ 行，求出它在中间数左边多少格即可
3. 小于中间数，那我们可以确定它在第 $n$ 列，求出它在中间数中变多少格即可

### Code:
```cpp
#include <bits/stdc++.h>
using namespace std;

int T, k;
int main(){
	scanf("%d", &T);
	while (T--){
		scanf("%d", &k);
		int n = sqrt(k);
		if (n * n == k){
			printf("%d 1\n", n);
		} else{
			n++;
			int cur = n * n - n + 1;
			if (k == cur) printf("%d %d\n", n, n);
			else{
				if (k > cur){
					printf("%d %d\n", n, n - (k - cur));
				} else{
					printf("%d %d\n", n - (cur - k), n);
				}
			}
		}
	}
	return 0;
}








 
```


---

## 作者：sycqwq (赞：1)

__思路__

观察这个方阵，很明显可以发现，每一层数的数量是按 $1,3,5,7,9$ 的规律递推的；

再观察样例，最后一组数据 $k=10^9$，答案是 ```31623 14130``` ，所以最多一共有 $31623$ 层；

可以一层一层的枚举，判断出从第 $1$ 层到现在的层一共包含了多少数，然后对于每一个 $k$ 二分查找在每一层，然后再判断位置，就行了。

__代码__
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[500005],n=31623;
int ef(int x)
{
    int l=1,r=n,ans=0;
    while(l<r)
    {
        int mid=l+r>>1;
        if(a[mid]<x)
            l=mid+1;
        else
            r=mid;
    }
    return r;
}
int main()
{
    int t;
    cin>>t;
    for(int i=1;i<=n;i++)
    {
        a[i]=a[i-1]+2*i-1;
    }
    for(int i=1;i<=t;i++)
    {
        int x;
        cin>>x;
        int t=ef(x);
        int tp=x-a[t-1];
        if(tp==(a[t]-a[t-1])/2+1)
        {
            cout<<t<<' '<<t<<endl;
        }
        else if(tp<(a[t]-a[t-1])/2+1)
        {
            cout<<tp<<' '<<t<<endl;
        }
        else
        {
            cout<<t<<' '<<(a[t]-a[t-1])/2+1-(tp-((a[t]-a[t-1])/2+1))<<endl;
        }
    }
    return 0;
}
```

---

## 作者：Arctic_1010 (赞：1)

一道不错的找规律入门题。

### 题目大意
Polycarp 找到了一个无限大的表格，他在表格中按某种顺序填了一些数字：

他把表格的左上角填上了 $1$，然后接下来的所有数字都按顺时针围绕着之前填的数字，如题图。

他的一个朋友想知道他自己最喜欢的数字 $k$ 填在了这个表格的哪一行哪一列。

多测。$ 1 \leq t \leq 100$，$ 1 \leq k \leq 10^9$。

### 思路分析

数据范围与时空限制并不能支持我们打表，于是换一种思路。

既然数字的排列有顺序，那么可以猜想可能存在一种规律。

注意到数字按反L型排列，那么为了之后方便设计算法，我们就重点观察「从左上到右下的对角线」上的数字。即行列坐标相等的格子里填的数字。

于是，我们可以在坐标与数字里建立一种关系。据此列表：

```
  x,y=  1  2  3  4  5  6  ...
  num=  1  3  7 13 21 31  ...
```

然后找规律。我的方法是借助二次函数。

~~应该有更简便的方法，如果我做难了请跳过。~~

我们可以把每一个坐标与数的对应关系看做平面直角坐标系中的点，其中「坐标」对应横坐标，「数」对应纵坐标。描点并连线，不难看出描出来的线是一条抛物线。

于是开始初中数学：设抛物线解析式为 $y=ax^2+bx+c$。

代入前三个点的坐标并列出方程组：

$$
\left \{ 
\begin{array}{c}
a+b+c=1 \\ 
4a+2b+c=3 \\ 
9a+3b+c=7
\end{array}
\right.
$$

解得

$$
\left \{ 
\begin{array}{c}
a=1 \\ 
b=-1 \\ 
c=1
\end{array}
\right.
$$

所以原抛物线解析式为 $y=x^2-x+1$ $(x\gt0)$。

可以检验：代入上表中的任意三个点，得出的解析式都相同。

所以对于每一个 $i$（即为上文的 $x$），都可以代入解析式求 $s$（即上文的 $y$）的值。至此找到了关系。

其实找到了关系就已经成功了一半了。我们枚举 $i$，计算出对应的 $s$ 值。如果要查询的数 $n$ 在 $s$ 的正上方或正左方，那么停止枚举，继续找规律。

分情况讨论：

- $n$ 在 $s$ 的正上方，$n$ 的列坐标就是 $i$；显然此时 $n$ 比 $s$ 小，行坐标就是 $s$ 的行坐标减去 $s$ 和 $n$ 的差，即 $i-(s-n)=i-s+n$；

- $n$ 在 $s$ 的正左方，$n$ 的行坐标就是 $i$；显然此时 $n$ 比 $s$ 大，列坐标就是 $s$ 的列坐标减去 $n$ 和 $s$ 的差，即 $i-(n-s)=i-n+s$；

- $n$ 等于 $s$，直接输出 ```i i```。

但现在又有一个问题，$i$ 的枚举上界在哪里？

还是初中数学：当 $x\gt 0$ 并且 $y = 10^9$ 时，$x^2-x+1=1000000000$。

解得 $x$ 约为 $31624$（上取整）。

到这里为止，已经可以写出代码。

### 梳理

枚举对角线，找数与坐标的关系，然后通过关系计算出目标数在表格里的行列坐标。

### 注意

小心多测，虽然这题不用清空。


### Code

```cpp
#include<cstdio>
using namespace std;
int q;
signed main()
{
	scanf("%d",&q);
	while(q--)
	{
		int n;
		scanf("%d",&n);
		for(int i=1;i<=31624;i++)
		{
			int s=i*i-i+1;//找规律 
			if(s==n)//好家伙您的询问直接撞在了对角线上 
			{
				printf("%d %d\n",i,i);
				break;
			}
			if((s-i+1<=n && n<=s)||(s<=n && n<=s+i-1))//枚举到了目标数所在的那一层 
			{//分情况讨论 
				if(s-n<0) printf("%d %d\n",i,i+s-n);//正左方 
				else printf("%d %d\n",i-s+n,i);//正上方 
				break;
			}
		}
	} 
	return 0;
}
```

[AC记录](https://www.luogu.com.cn/record/56359576)

利用函数找规律真是个不错的trick呢。


---

## 作者：miserExist (赞：0)

## 题意
给定一个矩阵，每一列先从上往下依次填数，如果左边有空格且没有填过数，就改变方向从右往左填数。

数均为正整数且依次自增$1$。
## 思路
像分块(?)

可以看成从左上角一层一层覆盖，第 $n$ 层左右边界的数满足：
$$
[~(n-1)^2 + 1,n^2~]
$$
可以先确定层数在确定位置坐标。

细节再注释里。

所有坐标除特判外均自加 $1$。
## 代码
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
#define int long long
const int N = 1e6 + 10;

int n,m;

signed main(){
    int ttt;
    cin >> ttt;

    while(ttt --)
    {
       int n;
       cin >> n;

       int temp = sqrt(n);

        int l = temp * temp;
        if(l == n)//特判左边界
        {
            cout << sqrt(n) << " " << 1 <<endl;
            continue;
        }

       l ++;//真正的左边界
       int r = (temp + 1) * (temp + 1);//右边界
       int  mid = l + r >> 1;//拐角位置的数

       int x = sqrt(mid);
       int y = sqrt(mid);
        if(n < mid)//在从上往下的数列中
        {
            cout << x - (mid - n) + 1 << " " << y + 1<< endl;
        }
        else if(n > mid){//在从右往左的数列中
            cout << x + 1<< " " << y - (n - mid) + 1<< endl;
        }
        else if(mid == n)//就是拐角
        {
            cout << x + 1<< " " << y + 1 << endl;

        }

    }
    
    return 0;
}
    

```

---

## 作者：Chinshyo (赞：0)

本题通过找规律就可以发现，**表格第一列都是完全平方数**。如图：

![table](https://cdn.luogu.com.cn/upload/image_hosting/5s8uzefl.png)

~~给您列了这么多或许显而易见了。~~ 我们只要找到最小的比 $k$ 大的完全平方数 $p$ ，再一步步向 $k$ 推即可。 $p$ 的坐标为 $(\sqrt p,1)$ 。

```cpp
#include<bits/stdc++.h>
#define debug cout << "Helloworld" << endl
using namespace std;

int main() {
	int n;
	cin >> n;
	for(long long i = 1; i <= n; i++) {
		long long p = 1, s;
		cin >> s;
		while(p * p < s) p++; //找到找到最小的比k(本程序写为s)大的完全平方数
		long long tmp = p * p; 
		long long ar = tmp - s + 1, x = 1, y = p; //ar:还需要移动多少步
		for(long long i = 1; i <= ar; i++) {
			if(i <= p) x++; //向右移
			else y--; //向上移
		}
		cout << y << " " << x - 1 << endl;
	}
	return 0;
}

```


---

## 作者：happy_dengziyue (赞：0)

### 1 思路

看这模拟方阵：

```
1  2  5 10
4  3  6 11
9  8  7 12
16 15 14 13
```

我们可以看出有 $2$ 种位置：

+ 在下来的路径上，如 $10$ 到 $13$；

+ 在往左的路径上，如 $14$ 到 $16$。注意，在我的代码中，$13$ 不属于这一类。

输入 $n$，设 $k=\left\lfloor\sqrt{n}\right\rfloor$。

+ 如果 $k^2=n$（$n$ 是完全平方数），坐标在 $(k,1)$。这也是第二类路径，只是要注意特判。

+ 如果 $n\le k\times k+k+1$，坐标在 $(n-k\times k,k+1)$。这是第一类路径。

+ 否则，坐标在 $(k+1,(k+1)\times(k+1)-n+1)$。这是第二类路径。

### 2 代码与记录

```cpp
#include<cstdio>
#include<cmath>
using namespace std;
int t;
int n;
int k;
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1560C_1.in","r",stdin);
	freopen("CF1560C_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	for(int ca=1;ca<=t;++ca){
		scanf("%d",&n);
		k=(int)sqrt(n);
		if(k*k==n){
			printf("%d %d\n",k,1);
			continue;
		}
		if(n<=k*k+k+1)printf("%d %d\n",n-k*k,k+1);
		else printf("%d %d\n",k+1,(k+1)*(k+1)-n+1);
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/56326920)

By **dengziyue**

---

## 作者：滑_稽 (赞：0)

[题目传送门](/problem/CF1560C)

这道题虽说是 C 题，但还是比较好做的（毕竟是百年一遇的~~水逼~~ div3

### 题目大意

- 按照图里的规则填一个表格，求数 $k$ 在表格里的位置。表格行数与列数均从 $1$ 开始算起。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1560C/fbe22cdb57a9c1d91e54741c4b3ed27f17ef455a.png)

- 规则并不复杂，主要分为以下几个步骤：

1. 初始从 $1$ 填起，每次填完一个数 $x$ 后，下一个要填的数就是 $x+1$。

2. 找到表格第一行的格子中最靠左的空格子，填入数字。

3. 从第 $2$ 步中的那个格子往下填数，直到第一个左邻的格子为空的格子。从这个格子继续向左填数，直到表格边缘为止。

4. 重复步骤 $2,3$。

- 有多组数据，$1\le k\le 10^9$。

### 题目分析

显然模拟填数是不可取的，我们要构造一个 $O(1)$ 的算法。

首先发现列数为 $1$ 的所有格子内填的都是完全平方数，于是可以求一个数 $a=\left\lceil\sqrt{k}\right\rceil$。$a$ 满足性质：$k$ 所在的行数或列数至少有一个是 $a$。

$k$ 的位置无非就三种情况：

第一种情况，行数为 $a$，列数不为 $a$；

第二种情况，行数不为 $a$，列数为 $a$；

第三种情况，行数、列数都为 $a$。

因此，我们可以求出坐标为 $(a,a)$ 的数 $mid$，比较 $mid$ 与 $k$ 的大小。$mid<k$ 对应第一种情况，$mid>k$ 对应第二种情况，$mid=k$ 对应第三种情况。

观察一下由坐标为 $(1,1),(2,2),(3,3),\dots$ 的数组成的数列：

$$1,3,7,13,21,31,\dots$$

设第 $n$ 项为 $S_n$，显然有通项公式

$$S_n=n(n-1)+1$$

于是 $mid$ 的求法也就一目了然了，易得 $mid=a(a-1)+1$。

设 $\Delta=\left\lvert k-mid\right\vert$，当 $k<mid$，$k$ 的坐标为 $(a-\Delta,a)$ 即 $(a+k-mid,a)$；当 $k=mid$，$k$ 的坐标为 $(a,a)$；当 $k>mid$，$k$ 的坐标为 $(a,a-\Delta)$ 即 $(a,a-k+mid)$。

code:

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;

int t,k,r,c,n,mid;

int main(){
	ios::sync_with_stdio(false);
	cin>>t;
	while(t--){
		cin>>k;
		n=ceil(sqrt(k));//这里的n即为上文中的a
		mid=n*(n-1)+1;
		if(k<mid) r=n+k-mid,c=n;
		else if(k==mid) r=c=n;
		else r=n,c=n-k+mid;
		cout<<r<<" "<<c<<endl;
	}
	return 0;
}
```

$\textbf{The end.}$

---

