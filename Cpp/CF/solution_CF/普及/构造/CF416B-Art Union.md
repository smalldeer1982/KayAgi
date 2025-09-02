# Art Union

## 题目描述

A well-known art union called "Kalevich is Alive!" manufactures objects d'art (pictures). The union consists of $ n $ painters who decided to organize their work as follows.

Each painter uses only the color that was assigned to him. The colors are distinct for all painters. Let's assume that the first painter uses color 1, the second one uses color 2, and so on. Each picture will contain all these $ n $ colors. Adding the $ j $ -th color to the $ i $ -th picture takes the $ j $ -th painter $ t_{ij} $ units of time.

Order is important everywhere, so the painters' work is ordered by the following rules:

- Each picture is first painted by the first painter, then by the second one, and so on. That is, after the $ j $ -th painter finishes working on the picture, it must go to the $ (j+1) $ -th painter (if $ j&lt;n $ );
- each painter works on the pictures in some order: first, he paints the first picture, then he paints the second picture and so on;
- each painter can simultaneously work on at most one picture. However, the painters don't need any time to have a rest;
- as soon as the $ j $ -th painter finishes his part of working on the picture, the picture immediately becomes available to the next painter.

Given that the painters start working at time 0, find for each picture the time when it is ready for sale.

## 样例 #1

### 输入

```
5 1
1
2
3
4
5
```

### 输出

```
1 3 6 10 15 ```

## 样例 #2

### 输入

```
4 2
2 5
3 1
5 3
10 1
```

### 输出

```
7 8 13 21 ```

# 题解

## 作者：cute_overmind (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF416B)

### 题目大意
一共有 $n$ 幅画，$m$ 种颜色。已知第 $j$ 个画家完成第 $i$ 幅画所需的时间是 $t_{i,j}$。问每一幅画最小完成时间。

### 分析
一道动规模板题，转移方程如下：
$$f_{i,j} = \max(f_{i-1 ,j},f_{i,j-1})+a_{i,j}$$
注意：输入部分是先输入 $m$，在输入 $n$。

~~被坑了好多次。~~

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 5e4 + 10 , M = 15; 
int a[N][M] , f[N][M] , n , m;
int main() 
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) cin >> a[i][j];
    for (int i = 1; i <= n ; i++) for (int j = 1; j <= m; j++) f[i][j] = max(f[i][j - 1], f[i - 1][j]) + a[i][j];
    for (int i = 1; i <= n; i++) cout << f[i][m] << ' ';
    return 0;
}
```

---

## 作者：Sun_pirf (赞：2)

# CF416B Art Union 题解
### [CF416B Art Union ](https://www.luogu.com.cn/problem/CF416B)  
首篇题解，求过 QWQ。
## 思路
这是一道极板的动态规划。  
我们先定义 $\operatorname{dp_{i,j}}$，表示为给第 $i$ 幅画涂第 $j$ 种颜色所需的最短时间。  
他需要先等自己画完第 $i-1$ 幅画（ $dp_{i-1,j}$ ）,他也需要先等第 $j-1$ 名画家完成 $i$ 幅画，故而 状态转移方程为:
$$dp_{i,j} = \max(dp_{i-1,j}, dp_{i,j-1}) + a_{i,j}$$
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[50005][10],dp[50005][10],n,m;
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>a[i][j];
	for(int i=1;i<=n ;i++)
		for(int j=1;j<=m;j++)
			dp[i][j]=max(dp[i][j-1],dp[i-1][j])+a[i][j];
	for(int i=1;i<=n;i++)
		cout<<dp[i][m]<<' ';
	return 0;
}
``` 

感谢观看。

---

## 作者：Sammy_prime (赞：2)

[CF416B](https://www.luogu.com.cn/problem/CF416B)

# 本题思路
这道题不就是一道简单的动规题嘛。

1. 第 $i$ 个画家把前一张画画完了;

2. 第 $j$ 张画把画的颜料上好了。

这样，状态转移方程就会写了。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e4+5;
int m,n,a[N][5],f[N][5];
int main(){
    scanf("%d%d",&m,&n);
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++)
            scanf("%d",&a[i][j]);
    for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++) 
		    f[i][j]=max(f[i-1][j],f[i][j-1])+a[i][j];
	for(int i=1;i<=m;i++)
	    printf("%d ",f[i][n]);
	return 0;
}
```


---

## 作者：2021sunzishan (赞：1)

一道极其水的 dp 题。
## 题目大意：
有 $n$ 副画，每幅画都要涂上 $m$ 个颜色。这 $n$ 幅画必须按 $1\sim n$ 的顺序涂，每幅画必须按 $1\sim m$ 的顺序上色。现给定 $m$ 个颜色分别要涂多久，求每幅画画完的时间。

## 思路：
显然的 dp。

定义 $f[i][j]$ 为第 $i$ 幅画涂了 $j$ 个颜色的时间。

那么很显然，$f[i][j]$ 就是 $f[i-1][j]$ 和 $f[i][j-1]$ 里面取一个最大值然后加上涂这个颜色的时间，最后按顺序输出即可。

以上就是本题的思路了。如果还有不懂的就看看代码吧！

**切勿抄袭！！！**

## 代码 ：
```cpp
#include <bits/stdc++.h>
using namespace std;
int f[50005][10],a[50005][10];
int n,m;
inline int read(){//快读
	int a=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if  (c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		a=a*10+(c-'0');
		c=getchar();
	}
	return f*a;
}
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	n=read(),m=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			a[i][j]=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			f[i][j]=max(f[i-1][j],f[i][j-1])+a[i][j];//转移方程
	for(int i=1;i<=n;i++)
		printf("%d ",f[i][m]);//输出
	return 0;
}
```

完结~

---

## 作者：zjjc1104111 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF416B)

# 思路

很明显，本题需要用背包做。

首先，第 ${i}$ 名画家画第 ${j}$ 所需要等待的时间。

1. 该画家已经画完了第 ${j-1}$ 幅画。

2. 第 ${i-1}$ 名画家已经画完了这幅画。

二者缺一不可。

因此，我们能得到：${dp[i][j]=\max(dp[i-1][j],dp[i][j-1])+a[i][j]}$。

方程都求出来了，下面看代码。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[50001][6],dp[50001][6];
int main(){
	int m,n;
	cin>>m>>n;
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++) cin>>a[i][j];
	}
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++) dp[i][j]=max(dp[i-1][j],dp[i][j-1])+a[i][j];
		cout<<dp[i][n]<<" ";
	}
	return 0;
} 
```




---

## 作者：int1024 (赞：1)

小蒟蒻的第二篇题解~

[博客](https://www.luogu.com.cn/blog/int1024/) 食用效果更佳~

### 题目大意：

有 $ n $ 个画家，$ m $ 幅画，要先让编号小的画家作画，每个画家都必须按编号从小到大来作画。求每幅画的最短完成时间。

### 思路：

这道题其实是有 （简单的） DP 的思想的，当然也可以用模拟做（如第一篇题解），但这篇题解主要讲 DP 的思想。

我们用 $ dp[i][j] $ 表示第 $ i $ 幅画第 $ j $ 个画家完成的最短时间，用 $ a[i][j] $ 表示已知**第 $ j $ 个画家画第 $ i $ 幅画**（坑点）需要的时间。

那么动态转移方程呢？

可以发现：我们首先必须加上第 $ j $ 个画家自身画第 $ i $ 幅画需要的时间，也就是先加 $ a[i][j] $。

这位画家作画前要等多久呢？

他需要先等自己画完第 $ i-1 $ 幅画，也就是 $ dp[i-1][j] $。他也需要先等第 $ j-1 $ 画家画完第 $ i $ 幅画，也就是 $ dp[i][j-1] $。

∴ 他需要等 $ max(dp[i][j-1],dp[i-1][j]) $ 的时间。

这样动态转移方程就有啦—— $ dp[i][j]=\max(dp[i][j-1],dp[i-1][j])+a[i][j] $。

接下来的代码就很简单了。

### code

```cpp
#include<bits/stdc++.h>
using namespace std;
int m,n,a[50001][7],dp[50001][7];
int main()
{
	cin>>m>>n;
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++) cin>>a[i][j];
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++) dp[i][j]=max(dp[i][j-1],dp[i-1][j])+a[i][j];
	for(int i=1;i<=m;i++) cout<<dp[i][n]<<" ";
	return 0;
} 
```
 留个赞再走呗~

---

## 作者：liyp (赞：0)

[题目传送门 CF416B](https://www.luogu.com.cn/problem/CF416B)

## 题目大意
总共 $m$ 幅画，$n$ 名画家，每幅都必须要被每个画家进行上色，且编号小的画家要比大的先上色，每个画家给每幅画上色的顺序都必须是从小到大。

## 思路
用 dp（动态规划），背包问题来做。

要想让第 $i$ 名画家对第 $j$ 幅画进行上色，需要满足以下两个条件：

1. 该画家此刻上色完了第 $ j - 1$ 幅画；

2. 第 $ i - 1 $ 名画家已经对这幅画完成了上色。

因此我们能得到这个方程：
$$
dp[i][j] = \max(dp[i][j-1],dp[i-1][j]) + a[i][j]
$$

## 代码
```cpp
#include<bits/stdc++.h>
#define LL long long
//#define int long long
using namespace std;
const int MAXN = 5e4 + 10;
int a [MAXN] [10] , dp [MAXN] [10] , n , m;
signed main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	//输入加速 
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	//输入部分
	cin >> m >> n ; 
	for (int i = 1; i <= m; i ++ )
		for (int j = 1; j <= n; j ++ )
			cin >> a [i] [j] ;
	
	//DP
	for (int i = 1; i <= m; i ++ )
		for (int j = 1; j <= n; j ++ )
			dp [i] [j] = max ( dp [i] [j-1] , dp [i-1] [j] ) + a [i] [j] ;
	
	//输出
	for (int i = 1; i <= m; i ++ ) 
		cout << dp [i] [n] << " "; 
	return 0;
}
```
[AC 记录](https://www.luogu.com.cn/record/151413946)

---

## 作者：GeYang (赞：0)

# 题意

有 $m$ 个画家和 $n$ 种颜色，每幅画都要用上所有画家和所有颜色且必须满足以下条件。

- 上色按照 $1\to n$ 的顺序。

- 画家作画按照 $1\to m$ 的顺序。

第 $j$ 个画家完成第 $i$ 幅画的时间是 $t_{i,j}$ 求每幅画被画好的时间。

# 思路

依题意得，第 $j$ 个画家完成第 $i$ 幅画时，必须满足以下条件。

- 这幅画第 $1$ 到第 $j-1$ 种颜色已经涂上了。

- 上一幅画的第 $j$ 种颜色已经涂上了。

所以只要求出它们之间较大的一个再加上时间 $t_{i,j}$ 即可。转移方程如下。

$$dp_{i,j}=\max(dp_{i-1,j},dp_{i,j-1})+t_{i,j}$$

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int M=5e5+10,N=7;
int m,n,a[M][N],dp[M][N];
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin>>a[i][j];
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
   		{
			dp[i][j]=max(dp[i-1][j],dp[i][j-1])+a[i][j];
		}
	}
	for(int i=1;i<=n;i++)
	{
		cout<<dp[i][m]<<" ";
	}
	return 0;
}
```

---

## 作者：tanshunyu0913 (赞：0)

### 思路
 $f_{i,j}$ 表示表示第 $i$ 幅画上第 $j$ 颜色的最小时间。根据题意，第 $i$ 幅画上第 $j$ 颜色时要满足：
 - 区间 $\left[1,j-1\right]$ 的颜色已经填了。
 - 第 $i-1$ 幅画的第 $j$ 种颜色已经填了。
 
 由此可以列出如下转移方程：
 $$
 f_{i,j}=\max\left(f_{i-1,j},f_{i.j-1}\right)+t_{i,j}
 $$
 则答案为每一个 $f_{i,n}$。
 ### code
 ```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e5+10;
int n,m,t[N][7],f[N][7];//t[i][j]表示第i幅画上第j颜色的最小时间 
signed main(){
	cin>>m>>n;
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)cin>>t[i][j];
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
			f[i][j]=max(f[i-1][j],f[i][j-1])+t[i][j];
	for(int i=1;i<=m;i++)
		cout<<f[i][n]<<' '; 
	return 0;
}

---

## 作者：_shine_ (赞：0)

题意建议看 CF 原版。

定义 $f_{i,j}$ 表示为第 $i$ 幅画要涂完第 $j$ 中颜色所需要的时间，则可有 $f_{i,j}=\max\left(f_{i-1,j},f_{i,j-1}\right)+a_{i,j}$，则每一个答案为 $f_{i,m}$。

难度虚高，建议降橙。
#### code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=5e4+10;
int n,m,a[maxn][10],f[maxn][10];
signed main(){
	cin >> m >> n;
	for(int i=1;i<=m;++i)for(int j=1;j<=n;++j)cin >> a[i][j];
	for(int i=1;i<=m;++i)for(int j=1;j<=n;++j)f[i][j]=max(f[i-1][j],f[i][j-1])+a[i][j];
	for(int i=1;i<=m;++i)cout << f[i][n] << " "; 
	return 0;
}
```

---

## 作者：sssscy_free_stdio (赞：0)

一道挺水的 DP。

我们设 $dp_{i,j}$ 为第 $i$ 幅画涂第 $j$ 种颜色时所用的时间，于是，我们可以得到以下两种情况：

- 用 $dp_{i-1,j}$ 转移得到，表示前一幅画涂完第 $j$ 种颜色后，涂这幅画的第 $j$ 种颜色花的时间。

- 用 $dp_{i,j-1}$ 转移得到，表示涂完前一种颜色后，涂这前一种颜色的到的颜色花的时间。

转移就是在上面两个之中选一个最大值然后加上 $t_{i,j}$ 即可。

然后输出每一个 $dp_{i,n}$ 即可。

### CODE:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int a[500010][10],dp[500010][10];
int main(){
	scanf("%d%d",&m,&n);
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++){
			scanf("%d",&a[i][j]);
		} 
	}for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++){
			dp[i][j]=max(dp[i-1][j]+a[i][j],dp[i][j-1]+a[i][j]);
		}
	}for(int i=1;i<=m;i++){
		printf("%d ",dp[i][n]);
	}return 0; 
}
```

---

## 作者：Terry2011 (赞：0)

板子题，纯纯的板子题！
# 题目分析
一看题目，动态规划嘛，简单的背包算法。

1. 第 $i$ 个画家已经画完了前一张；
1. 第 $j$ 张画已经上好了前一种颜料。

只有这样，才能继续画画。

我们可以得到方程式：$dp[i][j]=\max(dp[i-1][j],[i],[j-1])+a[i][j]$，根据这个，我们可以写代码了。
# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int m,n,a[50001][7],dp[50001][7];
int main()
{
	cin>>m>>n;
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++) cin>>a[i][j];
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++) dp[i][j]=max(dp[i][j-1],dp[i-1][j])+a[i][j];
	for(int i=1;i<=m;i++) cout<<dp[i][n]<<" ";
	return 0;
} 
```

---

## 作者：szh_AK_all (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF416B)

## 题意
有 $n$ 个作家，要画 $m$ 张画，每张画都要由每个画家来上色，也就是每个画家都要画每张画。某一个画家在画完第 $i-1$ 张画之前不能画第 $i$ 张画，某一张画在上完第 $i-1$ 种颜料之前不能上第 $i$ 种颜料。求每张画是什么时候画完的。
## 分析
这是正宗背包问题呀！第 $i$ 个画家画第 $j$ 张画，需要满足两个条件：一、第 $i$ 个画家已经画完了第 $j-1$ 张画；二、第 $j$ 张画已经上好了前 $i-1$ 种颜料。于是我们得出：$dp[i][j]=\max(dp[i-1][ j],dp[i][j-1])+a[i][j]$。这里的 $dp$ 数组指的是背包数组，$a$ 数组指的是每个画家给每张画上颜料的时间。下面直接上代码。

## Code
```c
#include<iostream>
#include<algorithm>
using namespace std;
int a[500005][10],f[500005][10];
int main()
{
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    for(int j=1;j<=m;j++)
        cin>>a[i][j];
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        f[i][j]=max(f[i][j-1],f[i-1][j])+a[i][j];
        cout<<f[i][m]<<" ";
    }
    return 0;
}
```


---

## 作者：shengheng (赞：0)

**此题解主要帮大家理解题意。**

## 题意

题目极为拗口。是让 $n$ 名画家画 $m$ 幅画，**要排队画不能插队，而不是说一个画家画完了，他必须等这幅画被人画完才能继续画的意思。**
这一点必须要注意，我就是被这个题意坑的，半天做不出来。

## 思路

此题一看就是 dp。

第 $j$ 名画家需要等前面画家画完第 $i$ 幅画，不能插队，自己也要画完第 $i-1$ 幅画。

所以 $dp_{ij}=\max dp_{i-1,j},dp_{i,j-1}+a_{ij}$。

见代码。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[50001][6],n,m,dp[50001][6];
int mian(){
	cin>>m>>n;
	for(int i=1;i<=m;i++)for(int j=1;j<=n;j++)cin>>a[i][j];
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++)dp[i][j]=max(dp[i-1][j],dp[i][j-1])+a[i][j];
		cout<<dp[i][n]<<' ';//精华部分，dp求出每幅画画完的时间。
	}return 0;
}
```


---

## 作者：_Weslie_ (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF416B)。

本题建议评橙。

前置芝士：$\tt dp$（基础）。

## 样例研究

```
4 2

2 5
3 1
5 3
10 1
```

在第一组 ```2 5``` 中，$1$ 画家需要 $2$ 时间来完成，此后 $2$ 画家才能画 $5$ 时间完成，总时间是 $2+5=7$。

在第二组 

```
2 5
3 1
```
中，画家 $1$ 用 $2$ 时间画完第一幅画后，开始画第二幅画，画完的时间是 $2+3=5$。

画家 $2$ 则是在 $7$ 时间之后才开始画第二幅画，用时 $1$，最终用时 $8$。所以 $2$ 拖累了 $1$。

第三组和第二组同理。

第四组中，画家 $1$ 画完第四幅已经是 $20$ 了，而画家 $2$ 画完第三幅仅仅只是 $13$。这时画家 $1$ 拖累了画家 $2$。

由此，我们得出思路——

## 思路历程

到这里，我们发现这一题是个裸 $\tt dp$。

既然是 $\tt dp$，那么就需要一个状态和状态转移方程。

状态方面，设 $dp_{i,j}$ 为画家 $j$ 在画完第 $i$ 幅画后用的时间。

那么状态转移方程显而易见：

$$dp_{i,j}=\max{dp_{i-1,j},dp_{i,j-1}}+a_{i,j}$$

最后写出代码，此题终。

```
#include<bits/stdc++.h>
using namespace std;
int a[50001][6],n,m,dp[50001][6];
int main(){
	cin>>m>>n;
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++){
			cin>>a[i][j];
		}
	}
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++){
			dp[i][j]=max(dp[i-1][j],dp[i][j-1])+a[i][j];
		}
		cout<<dp[i][n]<<' ';
	}
	return 0;
}
```

时间复杂度 $\operatorname{O}(nm)$，$n\leq5$，$m\leq50000$，不会超时。

感谢各位在评论区 $\tt hack$ 的大佬们~

---

## 作者：minecraft_herobrine (赞：0)

## solution

由于第一个样例~~狗屁不是~~没有参考价值，所以直接研究第二个样例。

```
4 2
2 5
3 1
5 3
10 1
----------------
7 8 13 21 
```
不难发现，画家一先花了 $2$ 秒的时间画好了第一幅画的第一种颜色，然后画家二花了 $5$ 秒的时间画好了第一幅画的第二种颜色。所以答案是 $7$。而在画家二画好了第一幅画的时候，画家一已经在画第二幅画的第一个颜色了，这里由于两个画家在画不同的画，所以他们可以同时行动。当画家二花了 $5$ 秒画好了第一幅画的时候，画家一的第二幅画已经完事了，所以画家二只花了 $1$ 秒便把第二幅画画完了，所以第二个画的答案是 $8$。

我们就有了个比较暴力的方法：用一个 ``pair`` 来存储每个画家的进度，``first`` 存他画到第几个画，``second`` 存当前画的剩余时间，每次一秒一秒的跑，每秒更新画家进度，如果一个画家的 ``second`` 值为 $0$ 了，那就把他的 ``first`` 值加一，``second`` 值重置为他画下一张画所需的时间。如果多个画家的进度在同一个画上那就只更新编号最小的。

不难发现，这种方法最坏情况要跑 $\sum t_{i,j}$ 次，极限数据大概是 $2.5e8$ 次，很危险。

考虑优化这个方法，很容易可以发现

```
2 2
114 514
1919 810
```
这里面前 $113$ 次更新都是没必要的。因为你可以让时间直接快进到 $114$ 秒，这样刚好到达一个重要的节点。

取当前所有画家的 ``second`` 的最小值，注意如果有多个画家在同一幅画上的时候只能让编号最小的画家计算最小值，忽略这幅画的其他画家。接下来把**所有参与计算最小值的画家**的 ``second`` 值减去这个最小值，如果有画家的 ``second`` 值变成了 $0$ 就让他的 ``first`` 值加一并且按照上文所述方法重置 ``second`` 值。

判断结束的方法就是看所有画家的 ``first`` 值是否全部大于 $m$。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=50010;
int t[MAXN][6],n,m;
pair<int,int> p[6];
bool vis[MAXN]={false};
bool jud()
{
	int i;
	for(i=1;i<=m;i++)
		if(p[i].first<=n) return false;//有画家还没画完 
	return true;//全画完了 
}
int main()
{
	int i,j,res=0;
	scanf("%d %d",&n,&m);//我个人习惯是先读n在读m，所以这里的nm是反着的 
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++) scanf("%d",&t[i][j]);
	for(i=1;i<=m;i++) t[n+1][i]=1145141919;//把第n+1幅画给极大值，把画完所有画的画家都给固定住 
	for(i=1;i<=m;i++)
	{
		p[i].first=1;//初始所有画家都在1号画 
		p[i].second=t[1][i];
	}
	while(!jud())//只要有没画完的就接着画 
	{
		int minn=1145141919;
		for(i=1;i<=m;i++)
		{
			if(vis[p[i].first]) continue;//如果有编号更小的画家在这个画上就忽略 
			vis[p[i].first]=true;//标记 
			minn=min(minn,p[i].second);//找出最小的second值 
		}
		res+=minn;//时间增加了这么多 
		for(i=1;i<=m;i++)
		{
			if(!vis[p[i].first]) continue;
			vis[p[i].first]=false;//减去了时间就把标记清掉，避免同一幅画多个画家一起被减 
			p[i].second-=minn;
			if(p[i].second==0)//如果某个画减成了0 
			{
				if(i==m) printf("%d ",res);//最后一个画家画完的时候一定就是这幅画被画完的时候 
				p[i].first++;//换下一个画 
				p[i].second=t[p[i].first][i];
			}
		}
	}
	return 0;
}
```

---

