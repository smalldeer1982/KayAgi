# Numbers Box

## 题目描述

You are given a rectangular grid with $ n $ rows and $ m $ columns. The cell located on the $ i $ -th row from the top and the $ j $ -th column from the left has a value $ a_{ij} $ written in it.

You can perform the following operation any number of times (possibly zero):

- Choose any two adjacent cells and multiply the values in them by $ -1 $ . Two cells are called adjacent if they share a side.

Note that you can use a cell more than once in different operations.

You are interested in $ X $ , the sum of all the numbers in the grid.

What is the maximum $ X $ you can achieve with these operations?

## 说明/提示

In the first test case, there will always be at least one $ -1 $ , so the answer is $ 2 $ .

In the second test case, we can use the operation six times to elements adjacent horizontally and get all numbers to be non-negative. So the answer is: $ 2\times 1 + 3\times2 + 3\times 3 + 2\times 4 + 1\times 5 = 30 $ .

## 样例 #1

### 输入

```
2
2 2
-1 1
1 1
3 4
0 -1 -2 -3
-1 -2 -3 -4
-2 -3 -4 -5```

### 输出

```
2
30```

# 题解

## 作者：试试事实上吗 (赞：4)

题意很清晰，首先关注翻转的性质，有一个结论：

**实际上每次可以翻转任意两个数。**

为什么呢？考虑比如我们要翻转$(x_1,y_1),(x_2,y_2)(x_1\le x_2,y_1\le y_2)$，我们可以一路翻转$(x_1,y_1),(x_1,y_1+1)$，再翻转$(x_1,y_1+1),(x_1,y_1+2)$，一直到$(x_1,y_2-1),(x_1,y_2)$。同理我们可以一路翻转到$(x_2,y_2)$，可以发现，除了两个端点$(x_1,y_1),(x_2,y_2)$，一路上所有的点都被翻转了两次翻回来了，所以就实现了翻转任意两个数。

接下来就很简单了。首先如果负数是偶数个，那么可以直接翻转，否则必然要剩下一个，我们就选取矩形中绝对值最小的数作为剩下的负数就可以了。

代码：

```cpp
#include <cstdio>
#include <iostream>
using namespace std;
const int maxn=105;

int n,m;

int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int cnt=0,ans=0,mi=101;
		scanf("%d%d",&n,&m);
		for(int i=1,x;i<=n;++i)
			for(int j=1;j<=m;++j)
			{
				scanf("%d",&x);
				if(x<0) x=-x,++cnt;
				mi=min(mi,x);ans+=x;
			}
		if(cnt&1) printf("%d\n",ans-mi*2);
		else printf("%d\n",ans);
	}
	return 0;
}
```





---

## 作者：czxQQQ (赞：0)

## 思路

定义一个变量 $sum$ 来记录所有数的**绝对值**。

接下来定义一个变量 $t$ 来记录负数的出现个数。那么就可以分两种情况：

$1.$ 当 $t$ 是偶数时，就说明所有数都可以变成**非负数**。直接输出 $sum$ 即可。

$2.$ 当 $t$ 是奇数时，就定义一个变量 $mi$ 来记录最小**绝对值**，然后输出 $sum-mi-mi$ 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int l,n,m,x,sum,mi,t;
	cin>>l;
	while(l--){
		sum=0;mi=105;t=0;
		cin>>n>>m;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				cin>>x;
				sum+=abs(x);//sum记录所有数的绝对值 
				if(abs(x)<mi) mi=abs(x);//mi记录最小绝对值 
				if(x<0) t++;//t记录负数的个数 
			}
		}
		if(t%2==0) cout<<sum<<"\n";//t是偶数的情况 
		else cout<<sum-mi-mi<<"\n";//t是奇数的情况 
	}
	return 0;
} 
```


---

## 作者：Sternenlicht (赞：0)

思路：贪心。

设矩阵 $a$ 中负数个数为 $num$ 个，则有如下两种情况：

1. $num$ 为偶数，则经过若干次操作之后，必将所有负数转为正数，这时将所有数的绝对值相加即可。

2. $num$ 为奇数，则经过若干次操作之后，只会剩下一个负数，将这个负数减去即可。

```cpp
#include <bits/stdc++.h>
namespace IO{
	#define LL long long
	inline LL read(){
		LL x=0,f=1;char c=getchar();
		for (;!isdigit(c);c=getchar())if (c=='-')f=-1;
		for (;isdigit(c);c=getchar())x=(x<<3)+(x<<1)+(c^48);
		return x*f;
	}
	inline void write(LL x,char c='\n'){
		if (x){
			if (x<0)x=-x,putchar('-');
			char a[30];short l;
			for (l=0;x;x/=10)a[l++]=x%10^48;
			for (l--;l>=0;l--)putchar(a[l]);
		}else putchar('0');putchar(c);
	}
}using namespace IO;
using namespace std;

#define INF 0x3f3f3f3f
const int N = 20;
int a[N][N];
int main(){
	int T=read();
	while (T--){
		//ans统计绝对值之和，num统计负数个数，minn记录绝对值最小的数 
		int n=read(),m=read(),ans=0,num=0,minn=INF;
		for (int i=1;i<=n;i++)
			for (int j=1;j<=m;j++)
				a[i][j]=read();
		for (int i=1;i<=n;i++)
			for (int j=1;j<=m;j++){
				minn=min(minn,abs(a[i][j]));//求绝对值最小的数 
				ans+=abs(a[i][j]);//求绝对值之和 
				if (a[i][j]<0)num++;//记录负数个数 
			}
		if (num&1)ans-=2*minn;//若有奇数个负数，ans减去绝对值最小的数
		write(ans);//输出 
	}
	return 0;
}
```

---

## 作者：YYen (赞：0)

### 思路
这道题的突破口在于，**一定可以把矩阵内任意位置的两个数同时取相反数（即使这两个位置不相邻）。**

举个例子：
$$\begin{bmatrix}
-1 & 2 & 2 \\
3 & 4 & 4 \\
3 & 4 & -4 \\
\end{bmatrix}$$

目标：把 $ (1, 1) $ 和 $ (3, 3) $ 同时取相反数。

做法：把 $ (1, 1) $ 和 $ (1, 2) $ 取相反数，把 $ (1, 2) $ 和 $ (1, 3) $ 取相反数，把 $ (1, 3) $ 和 $ (2, 3) $ 取相反数，把 $ (2, 3) $ 和 $ (3, 3) $ 取相反数。（除了一头一尾两个数分别各取了 $ 1 $ 次相反数，其他位置的数均取了 $ 2 $ 次相反数，目标达成）。

因此，题目算法可以总结为：

①、如果矩阵内负数个数为偶数个，负数可以两两一组全部可以调整为正数，因此答案就为矩阵内数据的绝对值之和；

②、如果矩阵内负数个数为奇数个，不论如何调整，矩阵内最终必定有 $ 1 $ 个负数（有 $ 0 $ 的情况就看作是 $ -0 $ 即可），因此可以考虑，把矩阵内绝对值最小的数据调整为负数，其他数据调整为正数，然后答案就为矩阵内数据之和。

### 代码
略

---

## 作者：—维尼— (赞：0)

## 题目描述

给你一个$n\times m$的矩阵，你可以进行任意次操作，每次操作可以将矩阵中两个相邻的数分别乘 -$1$，也就是取反，问，矩阵的和能达到的最大值是多少？

## 题目思路

简单贪心，思路点在于判断负数数量的奇偶性，这里简单证明一下：

首先，很明显的，不管原来有多少个负数，你都可以通过取反最小化负数的数量

ps:给看不出来的（就算负数不相邻，你也可以通过直接给一个负数及其相邻的数取反来达到“跳一格”，从而让两个负数相邻，最后消掉）


所以剩下一个还是零个，就取决于负数的数量了

然后我们将这些数的绝对值排序，如果最后剩一个负数，那就让绝对值最小的那个成为负数！

有人可能会有这样的疑问，如果我负数数量是奇数，但是我有一个0，给他取反不就所有数都大于等于0了？

其实这种思路不需要处理0，如果有0的话，因为我们将原序列的绝对值排序了，就算后来再反悔取反，取的也是最小的0


所以前面处理负数数量的时候不用管0，因为如果：负数数量是

举个例子好理解：

$-1\ -1$

$-2\ \ \ \ \ \ 2$

此时为负数数量为奇数，我们无法操作使所有负数消失，所以就贪心，让绝对值最小的变为负数（对最后的和影响小）

所以最后的和为$-1+1+2+2=4$

**总结：计算负数数量，如果是偶数，直接输出所有数的绝对值的和就行，如果是奇数，那就让最小的那个是负数，其他还是绝对值，累加即可**

## 代码
```c++
#include<bits/stdc++.h>
using namespace std;
int a[15][15];
struct xxx{
	int num,sum;
}b[1005];
bool cmp(xxx x,xxx y){
	return x.sum<y.sum;
} 
int main(){
	int t;
	cin>>t;
	while(t--){
		int n,m;
		cin>>n>>m;
		int suma=0,sumb=0;
		long long ans=0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				cin>>a[i][j];
				b[++suma].sum=abs(a[i][j]);
				if(a[i][j]<0){
					b[suma].num=0;
					sumb++;
				}
				else
					b[suma].num=1; 
			}
		}
		if(sumb%2)
			sumb=1;
		else
			sumb=0;
		sort(b+1,b+1+suma,cmp);
		for(int i=1;i<=suma;i++){
			if(sumb>=1){
				ans+=-b[i].sum;
				sumb=0;
			}
			else
				ans+=b[i].sum;
		}
		cout<<ans<<endl;
		//for(int i=1;i<=suma;i++)
		//	cout<<b[i].sum<<" ";
	}
}
```

---

## 作者：vectorwyx (赞：0)

当原矩阵中只有一个负号时，我们可以将这个负号“转移”到任意位置。

因此，当原矩阵中有多个负号时，我们总可以将负号两两消去。最终得到的矩阵中只会有一个负数（原矩阵有奇数个负数）或均为非负数（原矩阵有偶数个负数），对于后一种情况，直接输出矩阵元素的绝对值之和即可，对于前一种情况，贪心地令绝对值最小的元素为负即可。

代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define ll long long
#define fo(i,x,y) for(register int i=x;i<=y;++i)
#define go(i,x,y) for(register int i=x;i>=y;--i)
using namespace std;

inline int read(){
	int x=0,fh=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*fh;
}

int a[15][15];

void work(){
	int n=read(),m=read(),cnt=0,sum=0,mx=-1e9,mn=1e9;
	fo(i,1,n)
		fo(j,1,m) a[i][j]=read(),sum+=abs(a[i][j]);
	fo(i,1,n)
		fo(j,1,m){
			if(a[i][j]<0) ++cnt,mx=max(mx,a[i][j]);
			else mn=min(mn,a[i][j]);
		}
	if(cnt&1) printf("%d\n",sum-2*min(-mx,mn));
	else printf("%d\n",sum);
	//puts("");
}
int main(){
	int T=read();
	while(T--){
		work();
	}
	return 0;
}

```


---

## 作者：sodak (赞：0)

## 思路
因为操作次数无线，所以很容易发现我们可以任意选择两个数进行翻转，考虑有多少个负数，如果有偶数个，那么我们可以把所有的都翻转过来，答案那就是所有数的绝对值的加和，如果有奇数个，那么最后的矩阵中一定有一个是负数，选绝对值最小的就可以了

## code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define re register
#define ull unsigned long long
#define gc getchar()
#define getch while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=gc;}
#define getnu while(ch>='0'&&ch<='9'){s=(s<<1)+(s<<3)+ch-'0';ch=gc;}
using namespace std;
inline int read(){int s=0,f=1;char ch=gc;getch;getnu;return s*f;}
const int maxn=105;
int a[maxn][maxn];
int main(){
	int T=read();
	while(T--){
		int n=read(),m=read();
		int ans=0,Min=0x7f7f7f7f,cnt=0;
		for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)a[i][j]=read();
		for(int i=1;i<=n;i++)for(int j=1;j<=m;j++){
			if(a[i][j]<0)cnt++;ans+=abs(a[i][j]);Min=min(Min,abs(a[i][j]));
		}
		if(cnt%2)printf("%d\n",ans-Min*2);
		else printf("%d\n",ans);
	}
}


```

---

## 作者：CSP_Sept (赞：0)

### 题意简述

给定一个 $n\times m$ 的矩阵，满足 $-100\le a_{i,j}\le 100$，现在可以进行任意次操作，每次操作可以选择两个**相邻**的格子并将它们都乘上 $-1$，求矩阵中数的和的最大值。

### 思路

方便起见，先记 $sum=\sum\limits_{i=1}^n\sum\limits_{j=1}^m|a_{i,j}|$。

不难发现，矩阵中的一个负号可以转移至**任意一个**格子。

在此基础上，我们取 $M=\min\limits_{1\le i\le n,1\le j\le m}|a_{i,j}|$，则若矩阵中**有且仅有**一个负号时，答案输出 $sum-2M$（我们把负号转移到绝对值最小的数上）。

当**负号个数为偶数**时，容易发现，我们只要把负号都转移到相邻的格子内，这样就可以把所有负号消掉，答案即为 $sum$。

这样一来，我们把**负号个数为奇数**也转化成了有且仅有一个负号的情况。

于是很容易得出代码。

### $\mathcal{Code}$

[Link](https://codeforces.com/contest/1447/submission/98889667)

~~编号还挺顺~~

---

