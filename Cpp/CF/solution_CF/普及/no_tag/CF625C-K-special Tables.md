# K-special Tables

## 题目描述

People do many crazy things to stand out in a crowd. Some of them dance, some learn by heart rules of Russian language, some try to become an outstanding competitive programmers, while others collect funny math objects.

Alis is among these collectors. Right now she wants to get one of $ k $ -special tables. In case you forget, the table $ n×n $ is called $ k $ -special if the following three conditions are satisfied:

- every integer from $ 1 $ to $ n^{2} $ appears in the table exactly once;
- in each row numbers are situated in increasing order;
- the sum of numbers in the $ k $ -th column is maximum possible.

Your goal is to help Alice and find at least one $ k $ -special table of size $ n×n $ . Both rows and columns are numbered from $ 1 $ to $ n $ , with rows numbered from top to bottom and columns numbered from left to right.

## 样例 #1

### 输入

```
4 1
```

### 输出

```
28
1 2 3 4
5 6 7 8
9 10 11 12
13 14 15 16
```

## 样例 #2

### 输入

```
5 3
```

### 输出

```
85
5 6 17 18 19
9 10 23 24 25
7 8 20 21 22
3 4 14 15 16
1 2 11 12 13

```

# 题解

## 作者：Dr_Octopus (赞：2)

# CF625C K-special Tables 题解

## 题意

输出一个 $n \times n$ 的矩阵，符合三个要求：

$1$：$1$ 到 $n \times n$ 中各个数有且只有一个；

$2$：保证第 $k$ 列，在所有答案中最大；

$3$：每一行都要递增。


------------


## 思路

**贪心：** 尽量让小的数字先在前 $k - 1$ 列出现，剩下的数按顺序在每一行从左往右排就可以了。


------------


## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
const int maxn = 520;
using namespace std;
 
int a[maxn][maxn];
int n, k;

signed main() {
	
    cin >> n >> k;
    
    int num = 0;
    for (int i = 1;i <= n; i++)
        for (int j = 1;j <= k - 1; j++) a[i][j] = ++ num;
        
    for (int i = 1;i <= n; i++)
        for (int j = k;j <= n; j++) a[i][j] = ++ num;
        
    int ans = 0;
    for (int i = 1;i <= n; i++) ans += a[i][k];
    cout << ans << endl;
    
    for (int i = 1;i <= n; i++) {
    	for (int j = 1;j <= n; j++) {
            cout << a[i][j];
            if (j == n) {
            	puts("");
	    }
            else{
            	putchar(' ');
	    }
        }
    }
	
    return 0;
}
```


---

## 作者：boluo2014 (赞：1)

这么简单的题，竟然没人写题解？

### 思路

贪心，做人也要贪心。既然要让第 $k$ 列的和尽量大，那先让前面小一点，才能流出足够的大数去为第 $k$ 列“服务”。

所以 $a_{i,1},a_{i,2},a_{i,3} \dots a_{i,k-1}$ 我们都将它简单的设置为 $(i-1)n+j$，也就是以此 $+1$，分别存入。

而且，这样可以满足每一排的前 $(k-1)$ 个数肯定是递增的。

然后，后面由于也必须是递增的，又不能太“浪费”，所以呢，我们也采用“依次 $+1$ 法”。这里需要注意：样例输出二是骗人的！cf 的题经常搞骗人！

而依次 $+1$ 法最大的好处就是可以保证递增，保证最大。

### 代码

代码很简单，有简单的注释：
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[505][505];
signed main()
{
    int n,k,i,j,now=0;
    cin>>n>>k;
    for(i=1;i<=n;i++)//将所有横排的前k-1个数赋值：依次+1
    {
        for(j=1;j<=k-1;j++)
        {
            now++;
            a[i][j]=now;
        }
    }
    for(i=1;i<=n;i++)//求和，输出
    {
        for(j=k;j<=n;j++)
        {
            now++;
            a[i][j]=now;
        }
    }
    int sum=0;
    for(i=1;i<=n;i++)
    {
        sum+=a[i][k];
    }
    cout<<sum<<endl;
    for(i=1;i<=n;i++)//将所有横排的第k个到最后一个的数赋值：依次+1
    {
        for(j=1;j<=n-1;j++)
        {
            cout<<a[i][j]<<' ';
        }
        cout<<a[i][n]<<endl;
    }
    return 0;
}

```
### 总结

老师再见！同学再见！总结没有用再见！

---

## 作者：achjuncool (赞：1)

# 做法

显然，如果我们要使第 $k$ 列的和最大，要使第 $1$ 列到第 $k-1$ 列尽量小，所以我们把 $1$ 到 $n\times (k-1)$ 分配到第 $1$ 列到第 $k-1$ 列，只要满足每行单调递增就行了。

那么第 $k$ 列到第 $n$ 列该如何分配呢？

我们设答案数组为 $a$，则要求 $\mathit{a}_{i,n} > \mathit{a}_{i,n-1} > \mathit{a}_{i,n-2} >\dots > \mathit{a}_{i,k}(1\le i\le n)$，即将 $n\times (k-1)+1$ 到 $n^2$ 分为 $n$ 组，每组 $k$ 个数，再将每组最小的数填到 $a$ 的第 $k$ 列，顺序随意。

这时答案就很显然了，设 $b=n\times (k-1)+1$，我们将 $b,b+(n-k+1),b+2\times(n-k+1),\dots ,b+n\times (n-k+1)$ 这 $n$ 个数填入 $a$ 的第 $k$ 列，并把这个数接下来的 $n-k$ 个自然数填到这一行中它的后面。

这样说可能不太形象，那么看看下面这个图（$n=5,k=3$）：

![](https://cdn.luogu.com.cn/upload/image_hosting/r5yhtp6e.png)

~~好像更抽象了~~

# Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define qwq ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define endl '\n'
ll n, k, a[505][505], cur, ans;
int main(){
	qwq;
	cin >> n >> k;
	for(ll i = 1; i < k; i++) for(ll j = 1; j <= n; j++) a[j][i] = ++cur;
	for(ll i = 1; i <= n; i++){
		for(ll j = k; j <= n; j++){
			a[i][j] = ++cur;
			if(j == k) ans += cur;
		}
	}
	cout << ans << endl;
	for(ll i = 1; i <= n; i++){
		for(ll j = 1; j <= n; j++) cout << a[i][j] << " ";
		cout << endl;
	}
	return 0;
}
```

---

## 作者：da32s1da (赞：1)

考虑贪心

首先先把$1$到$k-1$列的先填上，然后在填$k$列到$n$列的即可。

```
#include<cstdio>
const int N=505;
int n,k,a[N][N],cnt,Sum;
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
	for(int j=1;j<k;j++)
	a[i][j]=++cnt;
    //1~k-1列
	for(int i=1;i<=n;i++)
	for(int j=k;j<=n;j++)
	a[i][j]=++cnt;
    //k~n列
	for(int i=1;i<=n;i++)Sum+=a[i][k];
	printf("%d\n",Sum);
	for(int i=1;i<=n;i++,puts(""))
	for(int j=1;j<=n;j++)printf("%d ",a[i][j]);
}
```

---

## 作者：lizhixun (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF625C)

### $\texttt{Description}$

给定 $n$ 和 $k$ 两个正整数，要求构造一个 $n \times n$ 的矩阵，满足以下三个条件：

- 包含了 $1 \sim n^2$ 的每一个数字，且每个数字只出现 $1$ 次。
- 每一行都是单调递增的。
- 满足以上两个条件，第 $k$ 列的和最大。

输出任意一个矩阵即可。

### $\texttt{Solution}$

这题如果数据范围小的话可以用全排列，但是现实是数据较大，没法枚举。

所以我们可以用贪心的方法来做这道题。

我们可以先把小的数字放在前 $k-1$ 列中，然后接下来的 $n-k+1$ 列就从左往右依次排开就行了。

我们可以画一个示意图理解一下：

![](https://cdn.luogu.com.cn/upload/image_hosting/kfrza0x7.png)

### $\texttt{Code}$

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e3 + 5;
int a[N][N], n, k;

signed main() {
	cin >> n >> k;
	
	int num = 0;
	
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j < k; j++) {
			a[i][j] = ++num;
		}
	}
	
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = k; j <= n; j++) {
			a[i][j] = ++num;
			ans += (j == k ? a[i][j] : 0);
		}
	}
	
	cout << ans << "\n";
	
	for (int i = 1; i <= n; i++) {
		for (int j = 1;j <= n; j++) {
			cout << a[i][j];
			cout << (j == n ? "\n" : " ");
		}
	}
	
	return 0;
}
```

完结。

---

