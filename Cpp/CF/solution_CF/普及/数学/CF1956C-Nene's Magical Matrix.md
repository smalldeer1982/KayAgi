# Nene's Magical Matrix

## 题目描述

The magical girl Nene has an $ n\times n $ matrix $ a $ filled with zeroes. The $ j $ -th element of the $ i $ -th row of matrix $ a $ is denoted as $ a_{i, j} $ .

She can perform operations of the following two types with this matrix:

- Type $ 1 $ operation: choose an integer $ i $ between $ 1 $ and $ n $ and a permutation $ p_1, p_2, \ldots, p_n $ of integers from $ 1 $ to $ n $ . Assign $ a_{i, j}:=p_j $ for all $ 1 \le j \le n $ simultaneously.
- Type $ 2 $ operation: choose an integer $ i $ between $ 1 $ and $ n $ and a permutation $ p_1, p_2, \ldots, p_n $ of integers from $ 1 $ to $ n $ . Assign $ a_{j, i}:=p_j $ for all $ 1 \le j \le n $ simultaneously.

Nene wants to maximize the sum of all the numbers in the matrix $ \sum\limits_{i=1}^{n}\sum\limits_{j=1}^{n}a_{i,j} $ . She asks you to find the way to perform the operations so that this sum is maximized. As she doesn't want to make too many operations, you should provide a solution with no more than $ 2n $ operations.

A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 说明/提示

In the first test case, the maximum sum $ s=1 $ can be obtained in $ 1 $ operation by setting $ a_{1, 1}:=1 $ .

In the second test case, the maximum sum $ s=7 $ can be obtained in $ 3 $ operations as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1956C/3b20fbb55df6b6d6328669ffd917221602db721d.png)It can be shown that it is impossible to make the sum of the numbers in the matrix larger than $ 7 $ .

## 样例 #1

### 输入

```
2
1
2```

### 输出

```
1 1
1 1 1
7 3
1 1 1 2
1 2 1 2
2 1 1 2```

# 题解

## 作者：Day_Tao (赞：3)

### 题目大意

让你构造出一种方案，每次操作让一个 $n\times n$ 的矩阵中某一行或者某一列的数变成一个排列，并使得 $\sum \limits_ {i=1}^n \sum \limits_ {j=1}^n a_{i,j}$ 最大。最多操作 $n\times 2$ 次。

### Sol
先说结论，最优情况应该是这种：
```cpp
1 2 3 4 5
2 2 3 4 5
3 3 3 4 5
4 4 4 4 5
5 5 5 5 5
```

在场上我也只是根据样例瞎猜了这个结论，过了。那现在我来尝试证明一下其正确性。

首先可以确定，最终的这个矩阵一定只会出现一行和一列为一个排列。假如说有两列是一个排列，可以将这两个排列相同的数两两对齐，然后用一行去更新这两列，一定是有方法可以让这两列的数变大。

然后对于每行每列，一样的数字最多出现 $n \times 2 - 1$ 次，也就是我给出的这个矩阵 $5$ 的情况，处在最外圈。对于这种出现次数最多的数字，肯定是要选择最大的，也就是 $n$。然后考虑出现次数第二多的，由于最多的位置已经被占去，剩下的每行每列最多只存在 $(n-1) \times 2 - 1$ 个位置可供使用，也就是第二大的那一圈。剩下的也是以此类推。

接下来考虑怎么构造。不妨从这个矩阵逆推。可以看到第一行、第一列都是一个排列，就说明可以最后更新。接下来问题就转化成了这个矩阵的构造方法：
```cpp
? ? ? ? ?
? 2 3 4 5
? 3 3 4 5
? 4 4 4 5
? 5 5 5 5
```
其中标有 $?$ 的地方是可以随便填的，因为最终肯定会被覆盖。这时发现，对于第二行列，在左边或者上面是 $1$ 的情况下可以构成一个排列，那么问题就变成了这样：
```cpp
? ? ? ? ?
? ? ? ? ?
? ? 3 4 5
? ? 4 4 5
? ? 5 5 5
```
现在想必大家都发现了规律：从第一行列开始逐个往下分析，因为靠前行列的会覆盖靠后的，那么就从最后的行列开始处理，用排列 $1\dots n$ 来一次次进行覆盖，最终就形成了原先我所说的最优矩阵。

### Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define pqg priority_queue<int, vector<int>, greater<int>>
#define pql priority_queue<int, vector<int>, less<int>>
#define pii pair<int, int>
#define mp(x, y) make_pair(x, y)
#define ls root << 1
#define rs root << 1 | 1
#define scnaf scanf
#define rt register int
#define int long long
const int MAX = 2e5 + 5;
const int INF = 0x7fffffff;
int T, n;
signed main()
{
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	scanf("%lld", &T);
	while (T--)
	{
		scanf("%lld", &n);
		int ans = 0;
		for (int i = 1; i <= n; i++)
			ans += i * (i * 2 - 1);//不难发现总和就是这样计算的
		printf("%lld %lld\n", ans, n * 2);
		for (int i = n; i >= 1; i--)//从最后一行列开始到第一行列
		{
			printf("1 %lld ", i);//处理行
			for (int j = 1; j <= n; j++)
				printf("%lld ", j);
			printf("\n");
			printf("2 %lld ", i);//处理列
			for (int j = 1; j <= n; j++)
				printf("%lld ", j);
			printf("\n");
		}
	}
	system("pause");
	return 0;
}
```
---
### END

---

## 作者：w9095 (赞：1)

[CF1956C Nene's Magical Matrix](https://www.luogu.com.cn/problem/CF1956C)

被这题送走了，纪念一下。

巧妙的构造题，考虑比较方便处理的方案，假设我们从左上角的顶点开始涂，每次涂一个 $1,2,3\dots n$ 的排列。其余方案可以通过这种方案交换数字顺序得到，所以只考虑这种方案。

考虑分析总和最大时矩阵的性质。显然，最内圈最大为 $1$，最外圈最大为 $n$。最后的矩阵必然是这个形式：

$$\begin{bmatrix}1&2&\dots&n\\2&2&\dots&n\\\dots&\dots&\dots&n\\n&n&n&n&\\\end{bmatrix}$$

接下来，我们考虑构造一种方案得到这个矩阵。我们只需要从外圈到内圈，纵横交错着涂。这样，每一圈不符合要求的数字就会被覆盖，达到这种情况。

操作数量刚好是 $2n$。

```cpp
#include <bits/stdc++.h>
using namespace std;
long long t,n,op[2200],p[2200],s[610][610];
int main()
{
	scanf("%lld",&t);
	while(t--)
	   {
	   	long long ans=0,cnt=0;
	   	scanf("%lld",&n);
	   	for(int i=n;i>=1;i--)
	   	    {
	   	    	op[++cnt]=1,p[cnt]=i;
	   	    	op[++cnt]=2,p[cnt]=i;
	   	    	for(int j=1;j<=n;j++)s[i][j]=j,s[j][i]=j;
			}
		for(int i=1;i<=n;i++)
		    for(int j=1;j<=n;j++)
			    ans+=s[i][j];
		printf("%lld %lld\n",ans,cnt);
		for(int i=1;i<=cnt;i++)
		    {
		    	printf("%lld %lld ",op[i],p[i]);
		    	for(long long j=1;j<=n;j++)printf("%lld ",j);
		    	printf("\n");
			}
       }
	return 0;
} 
```

---

## 作者：zxh923 (赞：1)

# CF1956C Nene's Magical Matrix 题解

[题目传送门](luogu.com.cn/problem/CF1956C)

### 思路

我们发现可以构造一个矩阵使得 $a_{i,j}=\max(i,j)$。

可以证明，这是最优的方案。

于是我们用 $2\times n$ 次操作，每次覆盖当前未被覆盖的行或列，覆盖的排列为 $1,2,3,\cdots,n$。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 200005
using namespace std;
int t,n;
void solve(){
	int ans=0;
	cin>>n;
	for(int i=1;i<=n;i++){
		ans+=i*((i<<1)-1);
	}
	cout<<ans<<' '<<(n<<1)<<'\n';
	for(int i=(n<<1);i;i--){
		if(i&1)cout<<"1 ";
		else cout<<"2 ";
		cout<<((i+1)>>1)<<' ';
		for(int j=1;j<=n;j++)cout<<j<<' ';
		cout<<'\n';
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--){
		solve();
	}
	return 0;
}
```

---

## 作者：Drifty (赞：1)

### Solution

由于其要求操作数不超过 $2n$，我们不妨直接拉满，考虑直接进行 $2n$ 次。

那我们就可以进行如下构造：

- 对于第 $2i-1$ 次操作：我们对于第 $i$ 行进行操作 $1$，将其赋值为 $[n,n-1,n-2,\dots,3,2,1]$ 的排列。
- 对于第 $2i$ 次操作：我们对于第 $i$ 列进行操作 $1$，将其赋值为 $[n,n-1,n-2,\dots,3,2,1]$ 的排列。
- 其中 $i\in \{1,2,3,\dots,n-1,n\}$。

为了更具象化这个过程，我们对 $n=3$ 进行模拟：
```
0 0 0
0 0 0
0 0 0

3 2 1
2 0 0
1 0 0

3 3 1
3 2 1
1 1 0

3 3 3
3 2 2
3 2 1
```

这是可证明的，过程详见 [`https://codeforces.com/blog/entry/128426`](https://codeforces.com/blog/entry/128426)。

### AC-Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
void solve()
{
	int n,m=0;
	cin>>n;
	for(int i=1;i<=n;i++)m+=i*(2*i-1);
	cout<<m<<' '<<n*2<<'\n'; 
	for(int i=1;i<=n;i++)
	{
		cout<<1<<' '<<i<<' ';
		for(int j=n;j>=1;j--)cout<<j<<' ';
		cout<<'\n'<<2<<' '<<i<<' ';
		for(int j=n;j>=1;j--)cout<<j<<' ';
		cout<<'\n';
	}
}
main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL),cout.tie(NULL);
	int T;
	cin>>T;
	while(T--)
		solve();
	return 0;
}
```

---

## 作者：Moyou (赞：0)

## 思路

首先我们考虑一个 naive 的想法：

每一列都放 `1 2 3 .. n`，但是这样并不是最优解，因为我们可以在全部是 $1$ 的第一行进行一次行覆盖，覆盖为 `1 2 3 .. n`，接着发现，在 $n$ 足够大的时候，第二行以及后面的行也需要这样的操作才能变得更优。

因为一次操作是覆盖，所以可以用时间倒流的套路，把一次操作变为填充。

> 例如某一行当前是 `1 2 x 3 x`，其中 `x` 表示尚未被填充，那我们在这一行如果放置了 `1 2 3 4 5`，那么这一行的情况就会变成 `1 2 3 3 5`。

这样一来，我们先在左上角第一行进行一次行覆盖成 `1 2 3 4 ... n`，为了贪心地使得 $1$ 少一点，再在第一列进行一次列覆盖，变成：

```
1 2 3 ... n
2 x x .....
3 x x .....
...........
n .........
```

这个时候第一行和第一列都已经不可改变了，所以剩下的网格就变成了一个子问题，解法是一样的。

这样就构造出了最优解，这个构造的操作次数刚好是 $2n$ 次，最后的矩阵形如：

```
1 2 3 ... n
2 2 3 ... n
3 3 3 ... n
. . . ... n
n n n n n n
```

不要忘记输出的时候要正着输出。

时间复杂度：$O(n ^ 2)$。

## 参考代码

```cpp
// Problem: C. Nene's Magical Matrix
// Contest: Codeforces - Codeforces Round 939 (Div. 2)
// Author: Moyou
// Copyright (c) 2024 Moyou All rights reserved.
// Date: 2024-04-13 23:01:08

#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#define int long long
#define x first
#define y second
using namespace std;
typedef pair<int, int> PII;
typedef long long ll;
const int N = 500 + 10;

int n, a[N][N];
void work() {
    cin >> n;
    int ans = 0;
    for(int i = 1; i <= n; i ++)
        for(int j = 1; j <= n; j ++)
            ans += max(i, j);
    cout << ans << ' ' << n * 2 << '\n';
    for(int i = n; i; i --) {
        cout << 1 << ' ' << i << ' ';
        for(int j = 1; j <= n; j ++) cout << j << ' '; cout << '\n';
        cout << 2 << ' ' << i << ' ';
        for(int j = 1; j <= n; j ++) cout << j << ' '; cout << '\n';
    }
    return ;
}

signed main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T = 1; 
    cin >> T;
    while (T--) work();

    return 0;
}

```

---

## 作者：锦依卫小生 (赞：0)

# CF1956C
## 题意分析
对一个 $n \times n$ 的初始元素全 $0$ 的方阵，每次操作可以将每一行或每一列赋值成 $n$ 的排列，通过 $2n$ 或其以下次操作使得方阵的元素和最大，求出最大元素和、操作次数与每一次操作内容。
## 基本算法
不妨进行一些尝试。例如 $3 \times 3$ 的矩阵。很自然想到对每一行进行操作使其变成：$\begin{bmatrix} 1 & 2 & 3 \\ 1 & 2 & 3 \\ 1 & 2 & 3 \end{bmatrix}$。显然，对第一列再操作一次可以更好：$\begin{bmatrix} 1 & 2 & 3 \\ 2 & 2 & 3 \\ 3 & 2 & 3 \end{bmatrix}$。注意，此时依然没有到最优情况。继续对第二列操作：$\begin{bmatrix} 1 & 1 & 3 \\ 2 & 2 & 3 \\ 3 & 3 & 3 \end{bmatrix}$。和之前相比没有变化，但是如果再对第一行操作一次：$\begin{bmatrix} 1 & 2 & 3 \\ 2 & 2 & 3 \\ 3 & 3 & 3 \end{bmatrix}$。  
此时，我们发现，继续任何操作都无法使得我们的矩阵元素之和更大了。观察此时的矩阵，易得其规律：宽泛地说，元素 $i$ 出现在边长为 $i$ 的正方形右和下边上。不难发现，对任意方阵，这样的策略总是最优的，其元素和为 $\sum _ {i = 1} ^ n i \times (2 \times i -1)$。  
进一步分析得到，对每一个方阵，都可以用 $2n$ 次操作达到目标。可以从 $n$ 开始，每次对当前行和列按照下标递增赋值排列，不断向前直到第一行与第一列。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAX=505;
int T,n,m;
long long s;
void solve(){
	scanf("%d",&n);
	//m=n+n/2;
	s=0;
	m=2*n;
	for(int i=1;i<=n;++i)
		s=s+i*(2*i-1); 
	printf("%lld %d\n",s,m); 
	for(int i=n;i>=1;--i){
		printf("1 %d ",i);
		for(int j=1;j<=n;++j)
			printf("%d ",j);
		printf("\n");
		printf("2 %d ",i);
		for(int j=1;j<=n;++j)
			printf("%d ",j);
		printf("\n");
	}
}
int main(){
	cin>>T;
	while(T--){
		solve();
	}
}
```

---

## 作者：JuRuoOIer (赞：0)

# 题解 CF1956C Nene's Magical Matrix

前排提示：本题是结论题。

### 题意

一个 $n\times n$ 的矩阵，开始时全是 $0$，现在你可以进行两种操作：
- 操作 $1$：选择一个 $1$ 到 $n$ 的排列 $p$,并将 $p$ 填充到矩阵的某一行中；
- 操作 $2$：选择一个 $1$ 到 $n$ 的排列 $p$,并将 $p$ 填充到矩阵的某一列中。

求通过不超过 $2n$ 次操作，最多能使矩阵所有元素之和为多少，并给出构造方案。

数据范围：$n \le 500,\sum n^2 \le 5\times 10^5$。

### 做法

先假设 $n=5$ 试一试。

我们先考虑最大化 $5$ 的数量。一个很简单的想法是，我们可以竖着铺满矩阵，像这样：

```
55555
44444
33333
22222
11111
```

然后横着铺下面四行：

```
55555
54321
54321
54321
54321
```

这样显然 $5$ 的数量就最大化了，因为一次填充会使一行或一列只有一个 $5$，而我们每行每列都有至少一个了。

接着考虑在此基础上最大化 $4$ 的数量。

按照刚才的思路，我们应该铺成这样：

```
54321
44444
54321
54321
54321
```

但是我们想保留原来的 $5$，于是我们需要处理掉两部分：
- 顶上的 `4321`，我们只需要竖着填完后不填顶上那行就行了；
- 左边的 $4$，显然为此我们应该先填充第二行再填充右四列（这样第二行第一列的 $5$ 不会被覆盖掉）。

以此类推，我们应该得到：

```
55555
54444
54333
54322
54321
```

而操作的方式就是纵横交错：

```
50000  50000  55000  55000
40000  54321  54321  54321
30000->30000->33000->54321->...
20000  20000  22000  22000
10000  10000  11000  11000
(一列) (一行) (一列) (一行)
```

拓展到 $n\times n$ 的矩阵是一样的。

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<fstream>
#include<algorithm>
#include<queue>
#include<cmath>
#include<vector>
#include<map>
#include<set>
#include<cstring>
#include<string>
#define ll long long
#define ull unsigned long long
#define lf double
#define ld long double
using namespace std;
ll t,n;
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		ll s=0,k=n*2-1;
		for(int i=1;i<=n;i++){
			s+=i*(i*i-(i-1)*(i-1));
		}
		cout<<s<<' '<<k<<endl;
		for(int i=1;i<=k;i++){
			if(i%2){
				cout<<2<<' '<<i/2+1;
				for(int j=n;j>=1;j--)cout<<' '<<j;
				cout<<endl;
			}
			else{
				cout<<1<<' '<<i/2+1;
				for(int j=n;j>=1;j--)cout<<' '<<j;
				cout<<endl;
			}
		}
	}
	return 0;
}

```

---

## 作者：smart_kai (赞：0)

通过题目，我们可以发现，要使得矩阵所有元素和尽可能大，就需要使**更大的数字出现更多的次数**。

操作的类型有两种：

- 选择一**行**，修改为 $1$ 到 $n$ 的排列。
- 选择一**列**，修改为 $1$ 到 $n$ 的排列。

不难发现，可以构造如下矩阵（如下表，$n=5$）：
|  | 第一列 | 第二列 | 第三列 | 第四列 | 第五列 |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| 第一行 | 5 | 5 | 5 | 5 | 5 |
| 第二行 | 5 | 4 | 4 | 4 | 4 |
| 第三行 | 5 | 4 | 3 | 3 | 3 |
| 第四行 | 5 | 4 | 3 | 2 | 2 |
| 第五行 | 5 | 4 | 3 | 2 | 1 |

只需要**交替进行**两项操作。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;

void fun(int n)
{
    for (int i=n; i>=1; i--) cout << i << " ";
}

void solve(int testCase)
{
    int n,tmp=1,tot=0;
    cin >> n;
    for (int i=1; i<=n; i++)
    {
        tot += i*tmp; tmp+=2;
    }
    cout << tot << " " << 2*n << "\n";
    for (int i=1; i<=n; i++)
    {
        cout << 1 << " " << i << " " ;
        fun(n);
        cout << "\n";
        cout << 2 << " " << i << " " ;
        fun(n);
        cout << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t=1;
    cin >> t;
    for (int testCase=1; testCase<=t; testCase++)
    {
        solve(testCase);
    }
    return 0;
}
```

---

## 作者：Expert_Dream (赞：0)

我们发现最优的情况一定是这样：

```
1 2 3 4
2 2 3 4
3 3 3 4
4 4 4 4
```

就是这样，绕一圈一圈的，这样保证每一个数在最后一次渲染都是成为可能。

例如，不可能出现如下情况：

```
1 2 3 4
2 2 4 4
3 3 3 4
4 4 4 4
```

自己手玩一下即可发现。

所以我们应该如何做到这种情况呢。

我们根据贪心的策略，肯定先把大的固定好了，在搞小的。所以说，我们可以倒着来。改变的顺序如下：第 $n$ 行，第 $n$ 列，第 $n-1$ 行，第 $n-1$ 列，等等。

这样，渲染出来的就是这样一圈一圈的效果。

由于我们没有反例证明他是错的，所以他是对的，因此，我们只需要对这个过程模拟即可。


```cpp
#include<bits/stdc++.h>
#define For(x,y,z) for(int x = y;x <= z;x++)
#define For_(x,y,z) for(int x = y;x >= z;x--)
using namespace std;
#define int long long
const int N = 505;
int n;
int a[N][N];
void puuuu(int x){
	For(i,1,x) cout<<i<<" ";
}
void solve(){
	cin >> n;
	For(i,1,n)For(j,1,n)a[i][j]=0;
	
	int res= 0;
	For(i,1,n)For(j,1,n)res+=max(i,j);
	
	
	cout<<res<<" "<<2*n<<endl;
	
	For_(i,n,1){
		cout << 1 << " " << i << " ";
		puuuu(n);cout<<endl;
		cout << 2 << " " << i << " ";
		puuuu(n);cout<<endl;
	}
}
signed main(){
	int T=1;
	cin >> T;
	For(_,1,T) solve();
	return 0;
}

```

---

## 作者：Xiphi (赞：0)

考虑观察法。猜得最终矩阵一定类似于：
$$\begin{bmatrix}
  1&  2&  3& 4\\
  2&2  &3  &4 \\
  3&3  &3  &4 \\
  4&4  &4  &4
\end{bmatrix}$$

的形式（旋转之后也是可以的），再往外的话，相当于第 $i$ 次在外边半圈加上 $i$。

继续猜结论，我们猜测可能是类似于涂一行，然后涂一列这种交替的形式。于是我们尝试先涂第 $1$ 列，然后第 $1$ 行，然后第 $2$ 列，以此类推。每次的排列是 $1,2,3\dots,n$。

但这样形成的矩阵是类似这样子的：


$$\begin{bmatrix}
  1&  1& 1& 1\\
  1&2  &2  &2 \\
  1&2  &3 &3 \\
  1&2  &3  &4
\end{bmatrix}$$

似乎和我们要求的矩阵反过来了（最大变成最小，次大变成次小）。那我们就考虑把操作也反过来，这样就是正确的了。意思就是把每次涂的排列改成 $n,n-1,\dots,1$。

代码：
```
#include<bits/stdc++.h>
#define _for(i,x,y) for(int i=x;i<=y;++i)
#define _forp(i,x,y,z) for(int i=x;i<=y;i+=z)
#define _rep(i,x,y) for(int i=x;i<y;++i)
using namespace std;
int T,n;
int f[505];
int main(){
//	freopen("test.in","r",stdin);
//	freopen("test.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
	cin>>T;
	f[0]=0;
	_for(i,1,500){
		f[i]=f[i-1]+i*(2*i-1);
	}
	while(T--){
		cin>>n;
		cout<<f[n]<<' '<<2*n<<'\n';
		_for(i,1,n*2){
			if(i&1){
				cout<<1<<' '<<(i+1)/2<<' ';
				_for(j,1,n) cout<<n-j+1<<' ';
				cout<<'\n';
			}else{
				cout<<2<<' '<<i/2<<' ';
				_for(j,1,n) cout<<n-j+1<<' ';
				cout<<'\n';
			}
		}
	}
	return 0;
}
/*
1 2 3 4
2 2 3 4
3 3 3 4
4 4 4 4

1 1 1 1
1 2 2 2
1 2 3 3
1 2 3 4

4 4 4 4
4 3 3 3
4 3 2 2
4 3 2 1
*/
```

---

