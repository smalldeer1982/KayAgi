# Subrectangle Guess

## 题目描述

Michael 和 Joe 在玩一个游戏。一共有 $t$ 次，每次 Michael 给出一个 $n\times m$ 的矩阵和一对 $h,w$，Jeo 在 Michael 看不见的情况下盖住任意一个 $h\times w$ 的子矩阵，问 Michael 这个子矩阵中最大的数是多少。Michael 答对即为获胜。

现在，我们对每一次给出的矩阵都要找出一对最小的 $h,w$，使得 Michael 一定能赢。

## 说明/提示

在第一组数据中，矩阵是 $1\times 1$ 的，因此对于 $h,w$，唯一可能的选择是 $h=1，w=1$，给出了 $h\cdot w=1$ 的面积。

描述中展示了第二组数据给出的矩阵。可以证明，只要 $h=3$，$w=3$，迈克尔就能保证胜利，而只要 $h\cdot w\le 8$，任何选择都不能保证胜利。

对于所有数据，$1\le t\le 20,1\le n,m\le 40,-10^9\le 矩阵中的元素\le 10^9$。

## 样例 #1

### 输入

```
3
1 1
3
4 4
2 12 6 10
3 15 16 4
1 13 8 11
14 7 9 5
2 3
-7 5 2
0 8 -3```

### 输出

```
1
9
4```

# 题解

## 作者：Strelitzia_ (赞：3)

## 题目大意

两个人玩游戏。其中一个人给出一个 $n\times m$ 的矩阵和一组 $h,w$，另一个人任意选出一个 $h\times w$ 的子矩阵（$h,w\ge 1$），第一个人要在完全看不见的情况下猜出这个子矩阵的最大值。求在 $h$ 与 $w$ 的乘积最小情况下的必胜策略。

## 思路

首先，显然的是整个矩阵的最大值是是所有包含它的子矩阵的最大值，也大于所有不包含它的子矩阵的最大值。那么，假设我们选出的 $h,w$ 一定能使最大值包含在选出的子矩阵中，由于第一个人已经知道整个矩阵的最大值，这样一定是必胜策略——第一个人只要说出整个矩阵的最大值就可以赢了。

那么假设我们选了比上文说的更小的 $h,w$ 呢？显然，这时选出的子矩阵不一定包含矩阵的最大值，第一个人就不知道这时子矩阵最大值是不是整个矩阵的最大值，可能会输。

综上所述，假设矩阵最大值的位置是 $(x,y)$，那么我们选出的 $h,w$ 应该是：$\max(x,n-x+1),\ \max(y,m-y+1)$。注意，我们输出的应该是**两者的乘积**。最后放一下主程序代码：

```cpp
signed main(){
	int t=read();
	while(t--){
		int _max=-INF,n=read(),m=read();
		int ansi,ansj;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				int x=read();
				if(_max<x){
					_max=x;
					ansi=i;
					ansj=j;
				}
			}
		}
		printf("%lld\n",max(ansi,n-ansi+1)*max(ansj,m-ansj+1));
	}
	return 0;
}
```

---

## 作者：CodeMao (赞：2)

##### 简化题意：

相信大家题目都读懂了，就是让我们找到最小的 $a\times b\ (a\le n,b\le m)$ 使得在原矩阵中无论怎样选取 $a\times b$ 的矩阵中的最大值都一样。

##### 主要思路：

设最大值的位置为 $(i,j)$

举两个例子：![](https://cdn.luogu.com.cn/upload/image_hosting/j59xrh0d.png)

易得：$a\times b$ 的最小值就是 $\max(i,n-i+1)\times \max(j,n-j+1)$。

上代码：

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define N 45
int t,n,m,x,y,mxx;
int a[N][N];
inline void in(int &a){
    a=0;char ch=getchar();bool f=0;
    while(ch<'0'||ch>'9')
        {if(ch=='-') f=1;ch=getchar();}
    while(ch>='0'&&ch<='9')
        a=(a<<1)+(a<<3)+(ch^48),ch=getchar();
    if(f) a=~a+1;
}
inline void op(int a){
    if(a>9) op(a/10);
    putchar(a%10+'0');
}
inline void out(int a,bool f){
    op(a);
    if(f) puts("");else putchar(' ');
}
inline int max(int a,int b){
    return a>b?a:b;
}
int main(){
    // freopen("G:\\C\\in.in","r",stdin);
    // freopen("G:\\C\\out.out","w",stdout);
    in(t);
    while(t--){
        in(n),in(m);mxx=-0x7f7f7f7f;
        memset(a,0,sizeof(a));
        for(int i=1;i<=n;++i)
            for(int j=1;j<=m;++j) in(a[i][j]);
        for(int i=1;i<=n;++i)   
            for(int j=1;j<=m;++j)
                if(a[i][j]>mxx) mxx=a[i][j],x=i,y=j;
        out(max(x,n-x+1)*max(y,m-y+1),1);
    }
    return 0;
}
```

---

## 作者：WilliamFranklin (赞：2)

### 主要思路

相信大家题都读懂了，那么我们很容易就能总结出，这其实是在让我们找到一个 $a$ 和一个 $b$，其中 $a \le n$ 和 $b \le m$，然后输出 $a \times b$。

首先，设最大数的位置为 $(x, y)$ 再仔细思考一下可以发现，要是想满足必须存在那个最大数，那么必须要满足 $a \le \lceil \frac n 2 \rceil$ 和 $b \le \lceil \frac m 2 \rceil$ 才行。

又可以很容易发现，其实这个 $a$ 就是 $\max\{x, n - x\}$，$b$ 就是 $\max\{y, m - y\}$。

但是，还要再考虑周全一点，要是有多个最大数呢？对！我们只要那一组 $a \times b$ 的积最小的即可。

好啦，上代码。

### AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[50][50];
int main() {
	int t;
	cin >> t;
	while (t--) {
		int n, m;
		cin >> n >> m;
		int ans = 1e9;
		int maxn = -1e9 - 5;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				cin >> a[i][j];
				if (a[i][j] > maxn) {
					maxn = a[i][j];
				}
			}
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				if (a[i][j] == maxn) {
					ans = min(ans, max(i, n - i + 1) * max(j, m - j + 1));
				}
			}
		}
		cout << ans << endl;
	}
} 
```

这题还是蛮简单的，点个赞呗！

---

## 作者：_Sushi (赞：0)

###### 题目：
[CF1695A Subrectangle Guess](https://www.luogu.com.cn/problem/CF1695A)
###### 分析：
题目中说明了矩阵中每个数都各不相同，那么每个数就是唯一的。题目要求让 Michael 赢，也就是说，每个 $ h \times w $ 的子矩阵的最大值相同，而他提前知道这个最大值，因此能赢。           
那么问题就转化成了求出最小的 $ h $ 、 $ w $ ，使得任意一个 $ h \times w $ 的子矩阵都包含 $ max $ （ $ max $ 为大矩阵中的最大值）。由于最大值是唯一的，就可以根据最大值的位置计算出 $ h $ 、 $ w $ 的最小值。  
设 $\mathit{a}_{x,y}$ 为矩阵最大值，为了使各个子矩阵都能包括最大值，应该求出最边缘的子矩阵的大小，取最大值。            
公式： $ h = \max ( x , n - x + 1 ) , w = \max ( y , m - y + 1 ) $              
最后计算乘积，输出。
###### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int n,m,x;
int maxx,maxa,maxb;
int main()
{
	scanf("%d",&t);     //多组数据
	while(t--)
	{
		scanf("%d%d",&n,&m);
		maxx=-1e9;        //有多组数据，因此要初始化
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
			{
				scanf("%d",&x);
				if(x>=maxx)   //更新最大值和最大值的位置
				{
					maxx=x;
					maxa=i;
					maxb=j;
				}
			}
		printf("%d\n",max(maxa,n-maxa+1)*max(maxb,m-maxb+1));      //利用公式计算，输出
	}
	return 0;
}
```


---

## 作者：Dovish (赞：0)

其实这道题换个想法就很简单了。

既然我们是找一个任意 $ h\times w $ 大小的区间可以包括整个矩阵中的最大值的。

那我们就可以只考虑极端情况，即这个 $ h\times w $ 的区间的对角一个在大矩阵中与其最大值相距最远的角上，另一个在最大值上的情况即可。

贴上代码：


------------

```
#include <bits/stdc++.h>
using namespace std;
long long t,n,m,f[1001][1001];
int main()
{
	cin>>t;
	while(t--)//共t组数据
	{
		cin>>n>>m;
		long long maxx=-1e10,maxi=0,maxj=0;//maxx一定要赋值为-1e9以下，不然会WA
		for(long long i=1;i<=n;i++)
		for(long long j=1;j<=m;j++)
		{
			cin>>f[i][j];
			if(f[i][j]>maxx)
			{
				maxx=f[i][j];
				maxi=i;
				maxj=j;//寻找最大值，及其坐标
			}
		}
		long long x=max(maxj,m-maxj+1);
		long long y=max(maxi,n-maxi+1);//考虑区间在最远的角上要成立的最小情况
        	//最大点到最远角的横纵距离就等于要取的区间的长和宽
		cout<<x*y<<endl;
	}
	return 0;
}
```

---

## 作者：donk_666 (赞：0)

做法与其他题解一样，不过用另一种方式理解

------------

让我们画一张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/8ao6gphl.png)

可以这么理解：最小满足条件的矩形的一种是有两条边在边界上的，这样矩形才可以被卡住，如果不在边界上，矩形就可以往边界靠，使最大数不在矩形里。

最小满足条件的矩形的两条边就是最大数的坐标与边界的最大距离。~~（当然你也可以找规律理解）~~

（比较形象，~~但我也证明不了~~，严谨思路可以看其他题解）

代码：

```
#include<bits/stdc++.h>
using namespace std;
int t,n,m,a[45][45],f[45][45],ma;
int main(){
	cin>>t;
	while(t--){
		cin>>n>>m;
		ma=-1000000005;//注意ma最初赋值
		int x,y;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				cin>>a[i][j];
				if(a[i][j]>ma){
					x=i;
					y=j;
					ma=a[i][j];//存最大值，横纵坐标
				}
			}
		}
	//	cout<<"    "<<ma<<endl;
		cout<<((x>n-x+1)?x:n-x+1)*((y>m-y+1)?y:m-y+1)<<endl;//注意是乘积
	}
}

```

---

## 作者：cyrxdzj (赞：0)

### 一、思路

首先，找到整个矩阵中最大的数。显然，这个数有且只有一个。为什么要找呢？待会再说。

然后，计算子矩形（原文是 `subrectangle`）的宽度和高度，使得这个子矩形无论怎么在矩阵中移动都能包含那个最大的数。怎么计算呢？其实很简单，子矩形的宽度就是这个数到左边或右边的距离的最大值，高度就是这个数到上边或下边的距离的最大值，这样就能保证这个子矩形无论怎么在矩阵中移动都能包含这个数了。

最后，计算这个子矩形的面积，输出即可。

为什么要找整个矩阵中最大的数呢？因为~~缺心眼的~~ Joe 可以将子矩形放到包含整个矩阵的最大的数的位置，这个时候 Michael 不猜到那个数就输了。

### 二、代码

```
#include<cstdio>
#include<algorithm>
using namespace std;
int t;
int n,m;
int a[45][45];
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				scanf("%d",&a[i][j]);
			}
		}
		int x=1,y=1;
		for(int i=1;i<=n;i++)//找到最大的数的位置。
		{
			for(int j=1;j<=m;j++)
			{
				if(a[i][j]>a[x][y])
				{
					x=i;
					y=j;
				}
			}
		}
		//注：max(x,n-x+1)是计算子矩形的宽度，max(y,m-y+1)是计算子矩形的高度。
		printf("%d\n",max(x,n-x+1)*max(y,m-y+1));
	}
	return 0;
}

```


---

