# Matrix of Differences

## 题目描述

For a square matrix of integers of size $ n \times n $ , let's define its beauty as follows: for each pair of side-adjacent elements $ x $ and $ y $ , write out the number $ |x-y| $ , and then find the number of different numbers among them.

For example, for the matrix $ \begin{pmatrix} 1 & 3\\ 4 & 2 \end{pmatrix} $ the numbers we consider are $ |1-3|=2 $ , $ |1-4|=3 $ , $ |3-2|=1 $ and $ |4-2|=2 $ ; there are $ 3 $ different numbers among them ( $ 2 $ , $ 3 $ and $ 1 $ ), which means that its beauty is equal to $ 3 $ .

You are given an integer $ n $ . You have to find a matrix of size $ n \times n $ , where each integer from $ 1 $ to $ n^2 $ occurs exactly once, such that its beauty is the maximum possible among all such matrices.

## 样例 #1

### 输入

```
2
2
3```

### 输出

```
1 3
4 2
1 3 4
9 2 7
5 8 6```

# 题解

## 作者：_299817_ (赞：6)

## Part 1: 思路

我们先思考一个问题：对于 $1 \dots k$，他们的差有多少种情况？

显然，有 $k - 1$ 个情况。

那么，我们现在有 $n^2$ 个整数，就有 $n^2 - 1$ 种情况。

那么我们怎么构造这 $n^2-1$ 种情况呢？

我们先不构造 $n^2-1$ 种情况，我们先从最简单的方法说起，构造 $n^2 - n$ 种情况：

这种构造方法特别好想：例如，当 $n=4$ 的时候，我们可以构造如下的矩阵：

$$
\begin{pmatrix}
  1&  16&  2&  15 \\
  3&  14&  4&  13 \\
  5&  12&  6&  11 \\
  7&  10&  8&  9 \\
\end{pmatrix}
$$

它的构造方法就是：从最小、最大数开始交替放入矩阵。

可见我们的差的 $n^2 - n$ 种情况分别为：$1,2,3,5,6,7,9,10,11,13,14,15$。

那么我们就只差：$4,8,12,16$ 了，也就是 $n$ 的整数倍。

现在，我们把偶数行都翻转过来，例如：

$$
\begin{pmatrix}
  1&  16&  2&  15 \\
  13&  4&  14&  3 \\
  5&  12&  6&  11 \\
  9&  8&  10&  7 \\
\end{pmatrix}
$$

现在，我们惊奇的发现：每两行之间的上下对应的两个数的差也就是 $n$ 的整数倍了！

按照这个方法我们就可以生成美丽度为 $n^2-1$ 的矩阵了。

## Part 2: 代码

~~蚂蜂比较奇怪，轻喷。~~

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstdlib>
#include<cmath>
#include<iomanip>
#include<cstring>
#include<unordered_map>
#include<map>
#define sort stable_sort
#define map unordered_map
using namespace std;
typedef long long ll;

int T;
int n;
int a[60][60]; // 记录生成的矩阵

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> T; //多组输入数据。
    while(T--){
        cin >> n;
        int i1 = 1; //从前往后。
        int i2 = n * n; //从后往前。
        int flag = 0; //判断现在应该插入i1还是i2。
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                if(flag == 0){ //把i1放入矩阵，更新i1和flag。
                    a[i][j] = i1;
                    i1++;
                    flag = 1;
                }else{ //把i2放入矩阵，更新i2和flag。
                    a[i][j] = i2;
                    i2--;
                    flag = 0;
                }
            }
        }
        for(int i = 1; i <= n; i++){
            if(i % 2 == 0){ //判断是不是偶数行。
                for(int j = 1; j <= n / 2; j++){ //如果是偶数行那么就把这行翻转过来
                    swap(a[i][j], a[i][n - j + 1]);
                }
            }
        }
        for(int i = 1; i <= n; i++){ //输出
            for(int j = 1; j <= n; j++){
                cout << a[i][j] << " ";
            }
            cout << "\n";
        }
    }
    return 0;
}
```

---

## 作者：cyrxdzj (赞：4)

### 一、思路

首先思考一个问题：你可以从 $1$ 到 $k$ 选择两个正整数，它们的差的绝对值有多少种可能？

很显然，是 $k-1$。具体来说，这些可能从 $1$ 排到 $k-1$。

再看看本题，结合上面所说的，一个矩阵的最大的 beautiful 值是 $n^2-1$。可以证明，无论如何这都是可以达到的。

为什么？考虑用这种方式排列数字：

![](https://cdn.luogu.com.cn/upload/image_hosting/5c7tf778.png)

我们一般称之为“反复横跳”。

此时，第一个数（这里指第一个放置的数，下面也是）与第二个数的绝对值之差为 $n^2-1$，第二个数与第三个数的绝对值之差为 $n^2-2$……第 $n^2-1$ 个数与第 $n^2$ 个数的绝对值之差为 $1$。

至于不在上图箭头路径上的绝对值之差，我们不必在乎。

### 二、代码

```cpp
// Problem: B. Matrix of Differences
// Contest: Educational Codeforces Round 141 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1783/problem/B
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<cstdio>
using namespace std;
int t;
int n;
int a[55][55];
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		int now=1,cnt=1;
		for(int i=1;i<=n;i++)
		{
			if(i&1)
			{
				for(int j=1;j<=n;j++)
				{
					a[i][j]=now;
					if(cnt&1)
					{
						now=n*n-now+1;
					}
					else
					{
						now=n*n-now+2;
					}
					cnt++;
				}
			}
			else
			{
				for(int j=n;j>=1;j--)
				{
					a[i][j]=now;
					if(cnt&1)
					{
						now=n*n-now+1;
					}
					else
					{
						now=n*n-now+2;
					}
					cnt++;
				}
			}
		}
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
			{
				printf("%d ",a[i][j]);
			}
			printf("\n");
		}
	}
	return 0;
}
```

---

## 作者：abensyl (赞：3)

原题：[CF1783B Matrix of Differences](https://www.luogu.com.cn/problem/CF1783B)。

看到大家和我思路一样，但是代码实现不一样，来发一篇题解。

## 思路

我们可以知道，在最有情况下，我们可以使相邻数差在 $(1,n^2-1)$ 中都出现一次，此时序列美丽度为 $n^2-1$，易证为最大，这样得到的一定是最优解。

- 如何实现上述方案？

易发现：有一个这样的序列：$1,n^2,2,n^2-1,3\dots$，这个序列满足上述条件，即相邻数差 $(1,n^2-1)$ 都出现一次，所以构造思路就变成了如何将这个序列扭曲并放置到一个矩阵中。

而放到矩阵中的方法我和大家非常不一样，我看到很多人是奇偶数讨论了一下 $n$，但是我的方法是 dfs。虽然空间大了一点，但是也可过。

详细注解可以参照代码注释。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

const int mod = 998244353, N = 2e5 + 4, INF = 1 << 30;

int a[103][103];
int n,m;

void dfs(int x, int y, int k) {
  a[x][y] = k;
  k = k > (m >> 1) ? m - k + 1 : m - k; //设置下一个搜索的位置
  if (!a[x + 1][y]) dfs(x + 1, y, k); //优先搜索x+1,y
  if (!a[x - 1][y]) dfs(x - 1, y, k); //次优先搜索x-1,y
  if (!a[x][y + 1]) dfs(x, y + 1, k); //否则就搜索x,y+1
  //如果没有发起搜索说明此处为死胡同，搜完了。
}

void solve() {
  memset(a, 0x3f, sizeof a);
  cin >> n;
  m = n * n + 1;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j) a[i][j] = 0;
  //把需要搜索的地方全部设为0，其余地方全部设为0x3f，便于搜索。
  dfs(1, 1, 1); //发起搜索
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) cout << a[i][j] << ' ';
    cout << '\n';
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int T;
  cin >> T;
  while (T--) solve();
}
```

我的 [AC记录](https://www.luogu.com.cn/record/99807458)。

---

## 作者：Night_sea_64 (赞：1)

### 题目大意：

对于一个 $n\times n$ 的矩阵，对于每一对相邻（有公共边）的值 $a,b$，写下 $|a-b|$（即 $a$ 与 $b$ 差的绝对值）。定义这个矩阵的美丽度为写下的不同的值的个数。以如下的矩阵为例：

$$\left(\begin{matrix}1&3\\4&2\end{matrix}\right)$$

则所有相邻值的绝对值分别是 $|1-3|=2,|1-4|=3,|3-2|=1,|4-2|=2$。共有 $1,2,3$ 三种不同的值，则这个矩阵的美丽度为 $3$。

给你 $t$ 次询问，每次询问给定一个正整数 $n$。输出任意一个 $n\times n$ 的矩阵，满足 $1\sim n^2$ 在矩阵中各出现一遍，并且该矩阵的美丽度最大。

---

### 题解：

首先，相邻值的差的绝对值，一定在 $1\sim n^2-1$ 之内。

然后我们考虑差。$1$ 必须跟 $n^2$ 相邻，因为只有它们能构造出 $n^2-1$ 的差。然后为了构造出 $n^2-2$ 的差，可以再让 $n^2$ 与 $2$ 相邻。同理 $2$ 跟 $n^2-1$ 相邻，$n^2-1$ 再跟 $3$ 相邻……这样，就可以构造出 $1\sim n^2-1$ 的所有差了，而且数还不重复。

然后我们就把数填入矩阵中就好了。可以“之”字形填，也可以螺旋形填……我用的是前者。只要保证应该相邻的数相邻就好了。

举个例子，如果 $n=3$，按照刚才说的方法填，可以填出如下的矩阵：

$$\left(\begin{matrix}1&9&2\\7&3&8\\4&6&5\end{matrix}\right)$$
 
时间复杂度 $O(t\times n^2)$。代码如下：

```cpp
#include<iostream>
using namespace std;
int a[60][60];
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        a[1][1]=1;
        int last=1,now=n*n-1,p=1;
        for(int i=1;i<=n;i++)
        {
            if(i%2)
                for(int j=(i==1?2:1);j<=n;j++)
                {
                    a[i][j]=last=last+now*p;
                    p=0-p,now--;
                }
            else for(int j=n;j>=1;j--)
                {
                    a[i][j]=last=last+now*p;
                    p=0-p,now--;
                }
        }
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++)
                cout<<a[i][j]<<" ";
            cout<<endl;
        }
    }
    return 0;
}
```

---

## 作者：AllenKING_RED (赞：1)

## 题目大意

把从 $1$ 到 $n^2$ 的 $n^2$ 个数排成一个 $n \times n$ 的矩阵，使得矩阵每两个相邻的数的差组成的可重集中不同的数的数量最多。

## 基本思路

首先，显而易见的可以看出数量最多时从 $1$ 到 $n^2-1$ 都曾在集合里出现过。

那么问题便转化成了保证这些数都曾在矩阵相邻元素的差值中出现过。

考虑将矩阵变为长度为 $n^2$ 的一条链，然后保证这些元素在该链相邻元素的差值中出现过。

假设第一个数放 $1$，由于所有数都要出现，所以第二个数必然是 $n^2$，
以此类推可以得到一个序列是最大最小数相互交替,满足以上要求。

得到了这样的序列我们可以将其转化为矩阵并保持相邻的数依然相邻，这样的矩阵必然是符合要求的。

可以将序列蛇形排列，例子:

```
链： 

1 9 2 8 3 7 4 6 5

矩阵： 

1 9 2
7 3 8
4 6 5
```

这样问题就解决了。

## 代码实现

赛时代码，十分简单：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(void)
{
	int T;
	cin>>T;
	while(T--)
	{
		int n;
		cin>>n;
		int a[2550],b[55][55];
		for(int i=1;i<=n*n;i++)
		{
			if(i%2==1)a[i]=(i/2)+1;
			else a[i]=n*n-(i/2)+1;
		}
		int sum=0;
		for(int i=1;i<=n;i++)
		{
			if(i%2==1)
				for(int j=1;j<=n;j++)
				{
					++sum;
					b[i][j]=a[sum]; 
				}
			else 
				for(int j=n;j>=1;j--)
				{
					++sum;
					b[i][j]=a[sum];
				}
		}
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
				cout<<b[i][j]<<" ";
			cout<<endl;
		}
	}
	return 0;
}
```



---

## 作者：123456789dd (赞：0)

**大意：**这题需要构造一个矩阵，使得相邻的两个数的差**互不相同**。

显然，对于 $n^2$ 个数的矩阵，其差最多也只能有 $n^2-1$ 种情况。

这种方法并不容易构造。

我们容易想到：$(n-1) \ne ((n-1)-2) \ne ((n-2)-3) \ne \ldots$，由此可通过**最大值与最小值交替的形式**，构造出该矩阵。

我们举一个例子，这是一个四行四列的矩阵：

$\left( \begin{array}{cccc} 1 & 16 & 2 & 15 \\ 3 & 14 & 4 & 13 \\ 5 & 12 & 6 & 11 \\ 7 & 10 & 8 & 9 \end{array} \right)$

同理，一个三行三列的矩阵应该这样构造：

$\left( \begin{array}{ccc} 1 & 9 & 2 \\ 8 & 3 & 7 \\ 4 & 6 & 5 \end{array} \right)$

但是，我们发现，对于 $n$ 是偶数的情况，这样构造只能满足 $n^2-n$ 种不同的差，并不能实现 $n^2-1$ 种。

若 $n$ 是奇数，那么这样正好对应了 $n^2-1$ 个差。

于是，我们为了解决**列的和相等**的情况（仅限于 $n$ 是偶数），将矩阵的**第偶数行正反对调**了。

这时，对调后的四行四列矩阵如下：

$\left( \begin{array}{cccc} 1 & 16 & 2 & 15 \\ 13 & 4 & 14 & 3 \\ 5 & 12 & 6 & 11 \\ 9 & 8 & 10 & 7 \end{array} \right)$

我们发现，这正好对应了 $n^2-1$ 个差。

如果把这样的改进方法运用到奇数矩阵上，会发现：

$\left( \begin{array}{ccc} 1 & 9 & 2 \\ 7 & 3 & 8 \\ 4 & 6 & 5 \end{array} \right)$

这里依然出现了 $n^2-1$ 个差，所以**这种改进方法对奇数也生效**。

这就是构造这个矩阵的方法。

代码较简单。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n,a[60][60];
        cin>>n;
        int minn=1,maxn=n;
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++)
            {
                if((i*n+j)&1)
                {
                    a[i][j]=minn;
                    minn++;
                }
                else
                {
                    a[i][j]=maxn;
                    maxn--;
                }
            }
        }
        for(int i=1;i<=n;i++)
        {
            if(!(i&1))
            {
                for(int j=1;j<=n/2;j++)
                {
                    swap(a[i][j],a[i][n-j+1]);
                }
            }
        }
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++)
            {
                cout<<a[i][j]<<" ";
            }
            cout<<endl;
        }
    }
    return 0;
}
```


---

## 作者：IOI_can_AK_lsr (赞：0)

# CF1783B题解

### [洛谷传送门](https://www.luogu.com.cn/problem/CF1783B) | [CF传送门](https://codeforces.com/contest/1783/problem/B)

[更好的阅读体验](https://www.luogu.com.cn/blog/910468/cf1783b-tijie)

## 题意

输入一个整数 $n$，构造一个 $n\times n$ 的矩阵，使其中每一个数减去相邻数的绝对值**数量**最多。

## 思路

这道题的差肯定很多（~~那不废话吗~~），所以可以使用贪心算法，构造出 $n^2-1$ 个差值（相邻两个数的最大差值为 $n^2-1$，最小为 $1$，共有 $n^2-1$ 种差值）。

我们可以先构造一个“蛇形方阵”，像这样：
```
1 9 2
7 3 8
4 6 5
```

这样，第一个数和第二个数的差就是 $n^2-1$，第二个数和第三个数呢？就是 $n^2-2$……以此类推。

可以来看代码啦。

[代码&&AC记录见此处](https://codeforces.com/contest/1783/submission/224869528)

完结撒花！！！

---

## 作者：xiaofeng_and_xiaoyu (赞：0)

[题目](https://www.luogu.com.cn/problem/CF1783B)

一道数学题，既然范围那么小，用暴力即可。

那么如何推公式呢？

很明显可以看出，当差为 $n^{2}-1$ 时，只能选用 $n^{2}$ 和 $1$。

所以要么沿 $1$ 递推得 $1, n^{2},2,n^{2}-1$ $\cdots$ $\cdots$ ，要么沿 $n^{2}$ 递推得 $ n^{2},1,n^{2}-1,2$ $\cdots$ $\cdots$ 。

注意要以“之”字形排列。

下面给出第一种递推方式的通过代码：

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int n[60][60],l[60]，ans;
int main(){
	int a;
	cin>>a;
	while(a--){
		int t;
		cin>>t;
		int x=1,y=t*t,z=1;//可以通过改变x和y的值实现第二种递推方式
		for(int i=0;i<t;i++){
			if(i%2==0){
				for(int j=0;j<t;j++){
					if((i*t+j)%2==0){
						n[i][j]=x;
						x++;
					}else{
						n[i][j]=y;
						y--;
					}
                    ans++;
				}
			}else{
				for(int j=t-1;j>=0;j--){
					if(t%2==0){
						if((i*t+j)%2==0){
							n[i][j]=y;
							y--;
						}else{
							n[i][j]=x;
							x++;
						}
					}else{
						if((i*t+j-1)%2==0){
							n[i][j]=y;
							y--;
						}else{
							n[i][j]=x;
							x++;
					}
                    ans++;
					}
					
				}
			}
		}
		for(int i=0;i<t;i++){
			for(int j=0;j<t;j++){
				cout<<n[i][j]<<' ';
				n[i][j]=0;//因为要多组数据，所以要更新为0
			}
			cout<<endl;
		}
	}
//cout<<ans;
    return 0;
}
```

---

## 作者：Failure_Terminator (赞：0)

## Problem

给定一个整数 $n$，构造一个 $n \times n$ 的矩阵，使其满足以下条件：

- $1 \sim n \times n$ 的每一个整数**有且仅有**一个。

- 对于位置相邻的两个数之差，不同的情况数最多。

若有多种构造，输出任意一个即可。

## Hints



- 对于一个 $n \times n$ 的矩阵，位置相邻两个数的最大差值为 $n^2 - 1$，最小为 $1$。

- 对于一个 $n \times n$ 的矩阵，不同的情况数最多有 $n^2 - 1$ 种。

## Solution

不得不说这真是一道有意思的思维题。

首先，以 $n = 4$ 的情况为例，我们可以发现有一个很特殊的序列。

$$1, 16, 2, 15, 3, 14, 4, 13, 5, 12, 6, 11, 7, 10, 8, 9$$

- 对于其奇数项，从 $1$ 递增到 $\left \lceil \dfrac{n^2}{2.0} \right \rceil$。

- 对于其偶数项，从 $n^2$ 递减到 $\left \lceil \dfrac{n^2}{2.0} \right \rceil + 1$。

结果得出的差的序列为：

$$15,14,13,12,11,10,9,8,7,6,5,4,3,2,1$$

正好为最多的 $n^2-1$ 种。

因此，对于 $n \times n$ 的矩阵，构造出这样的一个序列 $q$。

并以合适的方式填充进矩阵，使对于每个 $i$ $\in$ $[1, n^2 - 1]$，$q_i$ 与 $q_{i + 1}$ 位置相邻。

有多种构造方式。

## AC Code

本题有多种构造方式，这利用的是螺旋方阵构造。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int now=0,nev=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')nev=-1;c=getchar();}
	while(c>='0'&&c<='9'){now=(now<<1)+(now<<3)+(c&15);c=getchar(); }
	return now*nev;
}

const int N = 55;
int a[N][N], q[N * N], n;

void solve(){
	n = read();
	for (int i = 1; i <= n; i ++) for (int j = 1; j <= n; j ++) a[i][j] = 0;
	for (int i = 1; i <= n * n; i ++){
		if (i & 1) q[i] = i / 2 + 1;
		else q[i] = n * n - i / 2 + 1;
	}
	int cnt = 1;
	int i = 1, j = 1;
	a[i][j] = q[cnt];
	while (cnt < n * n){
		while (a[i][j + 1] == 0 && j < n) a[i][++ j] = q[++ cnt];
		while (a[i + 1][j] == 0 && i < n) a[++ i][j] = q[++ cnt];
		while (a[i][j - 1] == 0 && j > 1) a[i][-- j] = q[++ cnt];
		while (a[i - 1][j] == 0 && i > 1) a[-- i][j] = q[++ cnt];
	}
	for (int i = 1; i <= n; i ++){
		for (int j = 1; j <= n; j ++)
			cout << a[i][j] << " ";
		cout << "\n";
	}
}

signed main()
{
	int t = read();
	while (t --) solve();
    return 0;
}
```

---

## 作者：zajasi (赞：0)

前言：这道题的构造方法很多，本蒟蒻下面介绍的只是一种构造方法。
## 题意
给你一个整数 $n$，你需要构造一个 $n \times n$ 的矩阵，满足每一个数减去相邻一个数的绝对值的个数最多。
## 解题思路
由于这道题的差有很多个，采取贪心的思想，不难发现肯定会有 $n^2-1$ 个差值，不然肯定不是最优解。（详细可以看下面的构造方法）。也就是说，$1$ 和 $n^2$ 必须在一起，然后 $1$ 和 $n^2-1$ 或 $2$ 和 $n^2$ 在一起等，以此类推。

所以，我们可以构造一个斜行的矩阵。第一斜行最小，第二斜行最大，第三斜行最小。也就是偶数斜行最大，奇数斜行最小。举个例子：当 $n=3$ 时，构造出来是这样的：
```
1 8 4
9 3 6 
2 7 5
```
上面的问题（最多有 $n^2-1$ 个差值）也就能证明了。
## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t;
int n;
int a[51][51];
main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n;
		int l=1,r=1;//记录当前位置
		int c=2;//c 记录两个东西：应该放最大还是最小和出界时 l 的位置
		int z1=1,z2=n*n;//z1 记录最小到哪里，z2 记录最大到哪里
		for(int i=1;i<=(1+n)*n/2;i++){//一半一半讨论
//			cout<<l<<" "<<r<<" : ";
			if(c&1){
				a[l][r]=z2--;
//				cout<<z2+1<<"\n";
				l--;
				r++;
				if(r>n||l<=0){//出界了
					r=1;
					l=c;
					c++;
				}
			}
			else{
				a[l][r]=z1++;
//				cout<<z1-1<<"\n";
				l--;
				r++;
				if(r>n||l<=0){
					r=1;
					l=c;
					c++;
				}
				
			}
		}
//		for(int i=1;i<=n;i++){
//			for(int j=1;j<=n;j++){
//				cout<<a[i][j]<<" ";
//			}cout<<"\n";
//		}
		l=n;
		r=2;
		int x=2;
		for(int i=(n+1)*n/2+1;i<=n*n;i++){
			if(c&1){
				a[l][r]=z2--;
				l--;
				r++;
				if(r>n||l<=0){
					l=n;
					r=x+1;
					x++;
					c++;
				}
			}
			else{
				a[l][r]=z1++;
				l--;
				r++;
				if(r>n||l<=0){
					l=n;
					r=x+1;
					x++;
					c++;
				}				
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				cout<<a[i][j]<<" ";
			}cout<<"\n";
		}
	}
	return 0;
}
```


---

