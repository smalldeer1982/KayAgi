# Constructing Tests

## 题目描述

Let's denote a $ m $ -free matrix as a binary (that is, consisting of only $ 1 $ 's and $ 0 $ 's) matrix such that every square submatrix of size $ m×m $ of this matrix contains at least one zero.

Consider the following problem:

You are given two integers $ n $ and $ m $ . You have to construct an $ m $ -free square matrix of size $ n×n $ such that the number of $ 1 $ 's in this matrix is maximum possible. Print the maximum possible number of $ 1 $ 's in such matrix.

You don't have to solve this problem. Instead, you have to construct a few tests for it.

You will be given $ t $ numbers $ x_{1} $ , $ x_{2} $ , ..., $ x_{t} $ . For every ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF938C/af14780d5ff18b4dd564246057ccec0b94dd745f.png), find two integers $ n_{i} $ and $ m_{i} $ ( $ n_{i}>=m_{i} $ ) such that the answer for the aforementioned problem is exactly $ x_{i} $ if we set $ n=n_{i} $ and $ m=m_{i} $ .

## 样例 #1

### 输入

```
3
21
0
1
```

### 输出

```
5 2
1 1
-1
```

# 题解

## 作者：Mine_King (赞：5)

[在我的博客获得更好的阅读体验](https://www.cnblogs.com/mk-oi/p/15371051.html)

## Problem

[CF938C Constructing Tests](http://codeforces.com/problemset/problem/938/C)

**题目大意：**

在一个 $n \times n$ 的矩阵中填 $0,1$，使得每一个 $m \times m$ 的子矩阵中都包含至少一个 $0$，要让 $1$ 的个数最多。

现在知道最多有 $x$ 个 $1$，问满足条件的 $n,m$，输出任意一个。如果不存在则输出 `-1`。

有多组数据，数据组数为 $t$。

## Solution

首先我们要去观察原问题，要使 $0$ 最少，我们自然希望一个 $0$ 能覆盖尽量多的矩阵。  
我们假设 $n$ 无限大，那么一个 $0$ 能覆盖的范围如下：

![](https://i.loli.net/2021/10/06/Gao4NzlTkQEHWp2.png)

上图中边框内任意一个 $m \times m$ 的子矩阵都会包含中间的 $0$。  
如果右上角的矩阵再往右移一位，或者左下角的矩阵再往下移一位，就又需要一个新的 $0$，所以我们可以把问题转化成在一个 $n \times n$ 的矩形内放置若干 $m \times m$ 的矩形，使他们相邻且互不重叠，能放多少个矩形。容易得到答案为 $\lfloor \dfrac{n}{m} \rfloor ^2$。  

这里顺便解释下为什么是下取整。其实看一张图就明白：

![](https://i.loli.net/2021/10/06/hWnC1aZdwHSvMIG.png)

对于右边不满 $m$ 的部分，我们只要在最后一个矩形的右下角填 $0$，就可以把它覆盖掉。

所以我们可以得到：对于给定的 $n,m$，$1$ 最多有 $n^2 - \lfloor \dfrac{n}{m} \rfloor ^2$ 个。

根据初一第二学期的数学知识，我们可以得到 $n^2 - \lfloor \dfrac{n}{m} \rfloor ^2 = (n + \lfloor \dfrac{n}{m} \rfloor)(n - \lfloor \dfrac{n}{m} \rfloor)$。  
又因为这个东西 $= x$，所以我们将 $x$ 进行拆分并求解 $n,m$，再判断是否符合条件即可。  
什么？带下取整你不会求解？那直接把下取整无视掉，解出来后再判一下不就行了。

时间复杂度 $O(t\sqrt{x})$。

## Code

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int T,x;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&x);
		if(x==0){puts("1 1");continue;}
		if(x==1){puts("-1");continue;}
        //特判
		for(int i=1;i*i<x;i++)
			if(x%i==0)
			{
				int a=x/i,b=i;
				int n=(a+b)/2,m=(a+b)/(a-b);//解方程可得
				if(1ll*n*n-(1ll*n/m)*(1ll*n/m)==x)//记得要判断一下
				{
					printf("%d %d\n",n,m);
					goto End;
				}
			}
		puts("-1");
		End:;
	}
	return 0;
}
```



---

## 作者：王奕清 (赞：2)

首先我们可以得出：让每一个0的间距都是$m-1$是最优的，所以每$m*m$格只要放一个0,那么1的个数就是 $n^2-\left\lfloor\dfrac{n}{m}\right\rfloor^2$，所以我们只要找到这样一对 $n$ 和 $m$ 就可以了。

具体实现就是通过初始化枚举 $n$和 $\left\lfloor\dfrac{n}{m}\right\rfloor$把所有的可行的 $X$ 都找出来，然后排序一下后，每次询问都二分查找答案。

注意：初始化要用整除分块否则复杂度就是 $X$ 级别的。

在另一篇题解中复杂度是$T \times \sqrt X $的，而我的复杂度则是$X^{\frac{3}{4}} \times log(X)+T \times log(X) $，所以T可以开到1e6。

代码：
```
#include<bits/stdc++.h>
using namespace std;
int t,x,cnt;
const int inf=1e9;
struct node{
	int x,y,z;
	inline bool operator < (const node&w)const
	{
		return x<w.x;
	}
}p[7500005];
signed main()
{
	cin>>t;
	p[++cnt]=(node){0,1,1};
	for(int i=2;i<=40000;i++)
	{
		for(int j=2;;)
		{
			if((long long)i*i-(i/j)*(i/j)>inf)break;
			p[++cnt]=(node){i*i-(i/j)*(i/j),i,j};
			if(i/j==1)break;
			int r=i/j-1;
			int ls=i/r;
			if(ls==j)ls++;
			j=ls;
		}
		if((long long)i*i-(i/2)*(i/2)>inf)break;
	}
	sort(p+1,p+cnt+1);
	while(t--)
	{
		cin>>x;
		int l=1,r=cnt,fl=0;
		while(l<=r)
		{
			int mid=l+r>>1;
			if(p[mid].x<x)l=mid+1;
			else if(p[mid].x==x)
			{
				printf("%d %d\n",p[mid].y,p[mid].z);
				fl=1;
				break;
			}
			else r=mid-1;
		}
		if(fl==0)puts("-1");
	}
}
```

---

## 作者：A_zjzj (赞：2)

### 一道简单的思维题

我们先按照题目中所说：

>给定两个正整数 $n,m(m\le n)$，对于一个 $n$ 阶 $0-1$ 方阵， 其任意 $m$ 阶子方阵中至少有一个元素 “$0$”，则可以求解这个方阵中的 “$1$” 的最大数目。

那么显然，每一个 $0$ 都填在 $(x\times m,y\times m)$ 位置最优。

这样一共就填了：

$$

n^2-\lfloor\frac{n}{m}\rfloor^2

=(n+\lfloor\frac{n}{m}\rfloor)(n-\lfloor\frac{n}{m}\rfloor)

$$

那么，现在他告诉了我们这个值，让我们去推 $n,m$。

那就枚举两个数相乘是 $x$ ，判断是否有解就可以了（还要看看拆分的这两个数奇偶性是否相同）



```cpp
#include<cstdio>
using namespace std;
int T,x;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&x);
        if(x==0){printf("1 1\n");continue;}//特判
        else if(x==1){printf("-1\n");continue;}//特判
        bool flag=1;
		for(int i=1;i*i<x;i++){
			if(x%i!=0)continue;
			int a=i,b=x/i;
			if((a+b)%2==1)continue;
			int aa=(a+b)/2,bb=(b-a)/2,xx=aa/bb;
			if(bb==aa/xx){
				printf("%d %d\n",aa,xx);
				flag=0;
				break;
			}
		}
		if(flag)printf("-1\n");
	}
	return 0;
}
```

---

## 作者：AFO_Lzx (赞：1)

## [题目传送门](/problem/CF938C)

我们假设给定了 $n$ 和 $m$，需要求出 $x$，那么可以考虑一种贪心的做法，就是让所有的子矩阵尽量共用一个 $0$，这样 $1$ 的数量就会更多。所以我们把每一个 $0$ 都放在矩阵的右下角，那么得到 $x=n^2-(\frac{n}{m})^2$，循环解方程即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	int T;
	cin >> T;
	
	while (T--) {
		int x;
		cin >> x;
		
		if (x == 0) {
			cout << 1 << ' ' << 1 << '\n';
			continue;
		}
		
		bool flag = 0;
		for (int i = 1; i <= 1e5; i++) {
			if (i * i == n) continue;
			int u = i / sqrt(i * i - n);
			if (i * i - (i / u) * (i / u) == n) {
				cout << i <<  ' ' << u << '\n';
				flag = 1;
				break;
			}
		}
		
		if (!flag) cout << "-1\n";
	}
	
	return 0;
}
```

---

## 作者：rainbow_cat (赞：0)

我们先考虑给定 $n,m$ 求 $x$。很明显，让每个子矩阵使用尽量多的公共 $0$ 会使答案更优，因此将每个 $0$ 放在子矩阵的右下角答案最优。于是我们得到公式 $n^2-(\frac{n}{m})^2=x$ 由此公式反推就得到了本题的答案。
代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n;
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--)
	{
		cin>>n;
		bool flag=0;
		if(n==0)
		{
			cout<<"1 1\n";
			continue;
		}
		for(int i=1;i<=100000;i++)
		{
			if(i*i-n==0)continue;
			int l=i/sqrt(i*i-n);
			if(i*i-(i/l)*(i/l)==n)
			{
				cout<<i<<' '<<l<<'\n';
				flag=1;
				break;
			}
		}
		if(!flag)cout<<-1<<'\n';
	}
	return 0;
}
```

---

