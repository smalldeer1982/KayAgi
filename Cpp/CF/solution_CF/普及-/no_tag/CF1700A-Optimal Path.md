# Optimal Path

## 题目描述

# 最优路径


你得到一个大小为 $ n \times m $ 的表 $ a $ 。我们将考虑从上到下从 $1$ 到 $n$ 编号的表格行，从左到右从 $1$ 到 $m$ 编号的列。我们将在 $ i $ -th 行和 $ j $ -th 列中的单元格表示为 $ (i, j) $ 。在单元格 $ (i, j) $ 中有一个数字 $ (i - 1) \cdot m + j $ ，即 $ a_{ij} = (i - 1) \cdot m + j $ 。

一只乌龟最初站在单元格 $ (1, 1) $ 中，它想来到单元格 $ (n, m) $ 。从单元格 $ (i, j) $ 它可以一步转到单元格 $ (i + 1, j) $ 或 $ (i, j + 1) $ 之一，如果它存在的话。路径是一系列单元格，其中对于序列中的每两个相邻单元格，满足以下条件：乌龟可以一步从第一个单元格到达第二个单元格。路径的成本是写入路径单元格中的数字的总和。

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1700A/f97a8d75c2b2fd773655dec21eded248ca86a4f4.png)例如，$ n = 2 $ 和 $ m = 3 $ 表格将如上所示。海龟可以走以下路径： $ (1, 1) \rightarrow (1, 2) \rightarrow (1, 3) \rightarrow (2, 3) $ 。这种方式的成本等于 $ a_{11} + a_{12} + a_{13} + a_{23} = 12 $ 。另一方面，路径 $ (1, 1) \rightarrow (1, 2) \rightarrow (2, 2) \rightarrow (2, 1) $ 和 $ (1, 1) \rightarrow (1, 3) $是不正确的，因为在第一条路径中乌龟不能迈出一步 $ (2, 2) \rightarrow (2, 1) $ ，而在第二条路径中它不能迈出一步 $ (1, 1) \右箭头 (1, 3) $ 。

你被要求告诉海龟从单元 $ (1, 1) $ 到单元 $ (n, m) $ 的路径的最小可能成本。请注意，单元格 $ (1, 1) $ 和 $ (n, m) $ 是其中的一部分。

## 说明/提示

在第一个测试用例中，唯一可能的路径由单个单元格 $ (1, 1) $ 组成。

语句中显示了第二个测试用例中成本最低的路径。

在第四和第五个测试用例中，从 $ (1, 1) $ 到 $ (n, m) $ 只有一条路径。两条路径都访问表中的每个单元格。

## 样例 #1

### 输入

```
7
1 1
2 3
3 2
7 1
1 10
5 5
10000 10000```

### 输出

```
1
12
13
28
55
85
500099995000```

# 题解

## 作者：Otue (赞：3)

## 题意
一个 $n\times m$ 的矩阵 $a_{i,j}$，其中 $a_{i,j}=(i-1)\times m+j$。

从左上角走到右下角，每次只能向右或向下移动一步，问路径经过的格子的值的和最小是多少。
## 思路
容易发现，最佳的路径，就是横着走到底，再竖着走到底。

所以分为两步：

* 乌龟从 $(1,1)$ 开始，走到 $(1,m)$ 的成本   
	计算可得答案为 $\dfrac{m\times (m+1)}{2}$

* 乌龟从 $(1,m)$ 开始，走到 $(n,m)$ 的成本   
	答案为 $\dfrac{n\times (n+1)}{2}\times m$
    
所以两个式子直接相加输出即可。
## 代码
```c++
#include <bits/stdc++.h>
using namespace std;

int t;

int main() {
	cin >> t;
	while (t--) {
		long long  n, m;
		cin >> n >> m;
		cout << m * (m + 1) / 2 + ((n * (n + 1) / 2) * m) - m << endl;
	}
}
```

---

## 作者：Fleeing_loser (赞：2)

这道题目好像是一道动规题目，但是我们发现题目给出的二维表格填数的规律可以发现填数的规律是先填完一列，然后再接着填下一列，而其数字都是连续的。

因为一次只能向左或向下走一步，不难发现，先走完第一行一行，然后再从第 $m$ 列向下走，得到的值一定是最小的。

代码如下:
```cpp
#include<bits/stdc++.h>
using namespace std;
void read(int &x)
{
    int f=1;x=0;char s=getchar();
    while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
    while(s>='0'&&s<='9'){x=x*10+s-'0';s=getchar();}
    x*=f;
}
void print(long long x)
{
    if(x<0)putchar('-'),x=-x;
    if(x>9)print(x/10);
    putchar(x%10+'0');
}
int main()
{
    int t;
    read(t);
    while(t--)
    {
        int r,c;
        long long ans=0;//多测清空，且结果较大开long long
    	read(r); read(c);
        for(int j=1;j<=c;++j)
        {
            ans+=j;//先加走第一行的值
        }
        for(int i=2;i<=r;++i)
        {
            ans+=(i-1)*c+c;//再加走第m列的值
        }
        print(ans);
        printf("\n");
    }
    return 0;
}
```


---

## 作者：RE_Prince (赞：2)

# CF1700A Optimal Path

[link](https://www.luogu.com.cn/problem/CF1700A)

## Sol

考虑在所有情况下怎么走最优。

我先举个矩阵大小为 $2\times 3$ 的栗子。

$\begin{bmatrix}1&2&3\\&&\\4&5&6\end{bmatrix}$

很显然，最优路径是 $1\rightarrow 2\rightarrow 3\rightarrow 6$。

我们可以在举几个例子，不难发现，最优路径永远成一个 `7` 字形。

那为什么呢？

我们知道最顶端的数字是最小的，所以我们尽量走上面，即使往下时会经过几个较大的数字，它们加起来的大小也不会超过其他路径的和。

所以我们大胆猜想：每次统计 `7` 字形上所有数字之和。

果然，此算法是正确的， Accepted 了。

我的代码如下：

```cpp
#pragma G++ optimize(1)
#pragma G++ optimize(2)
#pragma G++ optimize(3)
#pragma G++ optimize("inline")
#pragma G++ optimize("Ofast")
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, m, i, j, k;
signed main() 
{
    ios::sync_with_stdio(0);
    int T;
    cin >> T;
    while (T--)
    {
        cin >> n >> m;
        if (n == 1 && m == 1)
        {
            cout << 1 << endl;
            continue;
        }//特判（但好像没啥用）
        int sum = (m * (m + 1) >> 1);//横着的
        for (i = 2; i <= n; i++) sum += m * i;//竖着的
        cout << sum << endl;
    }
    return 0;
}
```

时间复杂度 $\mathcal O(n)$。

---

## 作者：幸存者 (赞：1)

## 思路
最优解为 $(1,1)\rightarrow(1,2)\rightarrow\cdots\rightarrow(1,m)\rightarrow(2,m)\rightarrow\cdots\rightarrow(n,m)$，证明过程如下：

对于任何一条路径，必能通过上述路径将连续的右下改为下右（如将 $(1,1)\rightarrow(1,2)\rightarrow(2,2)$ 改为 $(1,1)\rightarrow(2,1)\rightarrow(2,2)$）而得到。

设将路径中的 $(x,y)$ 改为 $(x+1,y-1)$，则更改之后总成本会 $+(x\times m+y-1)-[(x-1)\times m+y]=+m-1$，而 $m\ge1$，所以成本必然增加。

那么对于任何一条路径其成本必然 $\ge$ 上述路径的成本，证毕。

所以最终答案就是 $\dfrac{m\times(m+1)}{2}+\dfrac{n\times(n+1)}{2}\times m-m$。
## $\text{AC Code}$
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        long long n, m;
        cin >> n >> m;
        cout << m * (m + 1) / 2 + n * (n + 1) / 2 * m - m << endl;
    }
    return 0;
}
```

---

## 作者：Dream_weavers (赞：1)

python 题解，~~随便写的~~，c++ 思路一样。

## 思路

这道题没必要 dp，$O(nm)$ 的复杂度；贪心即可，$O(1)$ 的复杂度（单次查询）。

先举一个例子：

```
1 2 3 4
5 6 7 8
9 10 11 12
```
很明显从 $1\to 4$ 加上 $8\to 12$ 的成本最小，也就是 $(1,1)$ 到 $(1,m)$ 加上 $(2,m)$ 到 $(n,m)$ 的总成本，先横后竖。

先看 $1\to 4$，成本是 $1+2+3+4$，很明显等差数列，也就是 $\dfrac{m(m+1)}{2}$。再看 $8\to 12$，提取公因数 $m$ 后变成 $2+3$，也是等差数列，求和后再乘 $m$，得 $\dfrac{(n-1)(n+2)}{2}\times m$。

答案就是 $\dfrac{m(m+1)}{2}+\dfrac{(n-1)(n+2)}{2}\times m$。

## 代码

```python
t=int(input())
for _ in range(t):
    s=input().split()
    n=int(s[0])
    m=int(s[1])
    print(m*(m+1)//2+(n-1)*(n+2)//2*m)

```

---

## 作者：Qerucy (赞：1)

看完题目后，我考虑 dp ，但看了一下数据范围之后，发现 dp 的时间复杂度直接上天......

想了一会儿，便想出了正解。

既然是要求从单元 $ (1, 1) $ 到单元 $ (n, m) $ 的路径的最小可能成本 并且 单元格 $ (i, j) $ 的成本为 $ (i - 1) \cdot m + j $，那么我们走最上面的一行和最右边的一排即可。因为横着走的最小成本就是最上面的一行，走最右边的一排的成本不管有多少，两者相加，便是答案。（~~因为走其它的路线太麻烦了~~）

[事实](https://www.luogu.com.cn/record/78038416)证明我的结论是对的

代码

```cpp
#include<cstdio>
#include<algorithm>

#define int long long//注意开long long

using namespace std;

int n,m,t;
int ans;

signed main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld%lld",&n,&m);
		ans=(1+m)*m/2;//等差数列求和算出行的成本
		for(int i=2;i<=n;i++){
			ans+=i*m;//列的成本
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

写题解不易，望通过。

---

## 作者：Phartial (赞：0)

## 简要题意

给你一个 $n\times m$ 的矩阵 $a_{i,j}$，其中 $a_{i,j}=(i-1)\times m+j$。从左上角走到右下角，每次只能向右或向下移动一步，问路径经过的格子的值的和最小是多少。

## 分析

发现由于 $m\ge 1$，而且向右走和向下走时相当于将接下来的路径上的格子权值 $+1$ 或者 $+m$，前者显然不劣于后者，所以我们只需要一直向右走，走到头时向下走即可。

## 代码

```cpp
#include <iostream>

using namespace std;
using LL = long long;

int t, n, m;
LL ans;

int main() {
  for (cin >> t; t--;) {
    cin >> n >> m;
    ans = 0;
    for (int i = 1; i <= m; ++i) { // 向右走
      ans += i;
    }
    for (int i = 2; i <= n; ++i) { // 向下走
      ans += i * m;
    }
    cout << ans << '\n';
  }
}
```

---

## 作者：happy_dengziyue (赞：0)

### 1 视频题解

![](bilibili:BV1Fv4y137u9)

### 2 思路

很明显的，先走上面的路径，再走右边的路径，一定是最优的。

那么我们可以运用等差数列公式计算。

首先，上面的权值是 $1$ 到 $m$，加起来是 $\dfrac{m(m+1)}{2}$；

然后，右边的权值是 $m$ 到 $n\times m$，加起来是 $\dfrac{n(m+n\times m)}{2}$；

右上角又有个重复部分 $m$；

答案就是：

$$\dfrac{m(m+1)+n(m+n\times m)}{2}-m$$

### 3 代码与记录

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
int t;
long long n,m;
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1700A_1.in","r",stdin);
	freopen("CF1700A_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%lld%lld",&n,&m);
		printf("%lld\n",(m+1)*m/2+(m+n*m)*n/2-m);
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/77692706)

By **dengziyue**

---

## 作者：瀛洲仙子 (赞：0)

### 大体思路概括
这道题作为 T1 可以说不算水题。如果直接开数组表示，那么会 MLE。然后我抱着试一试的心态做了一下递归解法，显然 TLE 伺候。一看这个数据范围，看来不得不搞一个 $O(1)$ 的算法。
### 具体思路
题目中有一个看似比较牛逼的算式 $a_{i_j}=(i-1) \times m + j$，实际上一个表格就暴露了。    
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1700A/f97a8d75c2b2fd773655dec21eded248ca86a4f4.png)   
实际上就是把每一个数标出来。然后让我们找一个和最少的路。
用 DFS 还真不行肯定会超时（数据范围 $1 \le n,m \le 10000$）。但是不难发现这是一道**绝对的贪心**。
![](https://cdn.luogu.com.cn/upload/image_hosting/tx5kegkz.png)
可以发现，无论如何总和最少的路一定是最有上边的一条。于是代码就出来了。还要特判是不是有只有一行的情况。
### 完整程序
根据以上思路，[无注释代码](https://codeforces.com/contest/1700/submission/161200373)如下。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
 int n;cin>>n;while(n--)
 {
  long long a,b;cin>>a>>b;long long ans(0);
  if(a==1){ans=b*(b+1)/2;cout<<ans<<endl;continue;}
  if(b==1){ans=a*(a+1)/2;cout<<ans<<endl;continue;}
  ans+=b*(b+1)/2;ans+=a*(a+1)*b/2;ans-=b;cout<<ans<<endl;
 }
}
```
**珍爱生命，远离抄袭！**
### 更新日志
* 2022.7.4 替换图片并删除吐槽内容，麻烦管理大人再次审核谢谢。

---

## 作者：hyc1026 (赞：0)

本题答案：

$\dfrac{m\times (m+1)}{2}+\left(\dfrac{n\times (n+1)}{2}\times m\right)-m$

解释：本题需要乌龟先向右走到头，在向下走到头。即可获取最小值。

首先来看 $\dfrac{m\times (m+1)}{2}$：

这个式子代表了乌龟从 $(1,1)$ 开始，走到 $(1,m)$ 的总成本。等价于 $1+2+3+\cdots+m$。

再来看 $\dfrac{n\times (n+1)}{2}\times m$：

这个式子代表了乌龟从 $(1,m)$ 开始，走到 $(n,m)$ 的总成本。等价于 $(1+2+3+\cdots+n)\times m$。

乘 $m$ 的原因是在这一列中，第 $i$ 行的格子的值是 $i\times m$。

最后减 $m$ 是因为 $(1,m)$ 这个点被算了两次，需要减掉，而它的值为 $m$。

此题不开 long long 见祖宗。

AC Code:

```cpp
#include <bits/stdc++.h>
using namespace std;
 
int main()
{
    int t;
    cin >> t;
    while(t--)
    {
        long long n,m;
        cin >> n >> m;
        cout << m*(m+1)/2 + ((n*(n+1)/2)*m)-m << endl;
    }
}
```

---

## 作者：tian_jun_cheng (赞：0)

## 题意概述

有一只乌龟从 $ ( 1 , 1 ) $ 点走到  $  ( n , m ) $ 点，每次只能往下或往右走。乌龟走过的格子上的数一共是多少？

## 思路

因为格子上的数是有规律的，而且数据范围是 $ 1 0 ^ 4 $ ，所以不能用动态规划，用贪心即可。

对于行来说，我们直接走第一行即可，最后走列。

公式推导：

$$ ( 1 + 2 + . . .  + m ) + 2   \times  m + 3  \times  m   + . . . + n  \times m 
 $$

$$ ( 1 + m )  \times m \div 2 + (  2 + . . . + n )     \times ( n - 2 + 1 )   \div 2 \times m $$

$$ ( 1 + m )  \times m \div 2 + ( n + 2 )  \times ( n - 1 )   \div 2 \times m $$

为什么呢？

先看图。

![](https://cdn.luogu.com.cn/upload/image_hosting/2rmnq5zq.png)

这是最短路线，  $ 3 $ 行 $ 4 $ 列 。

如果我们不走 $ 4 $ ，走另一条路的话，很明显，答案会多 $ 3 $ 。

我们知道，往下一行，答案 $ + n $ ，往左一列，答案 $ + 1 $ 。

当 $ n > 1 $ 的时候，显然按照标准路线走最短。

那么，当 $ n = 1 $ 的时候，只有一条路线啊！

```cpp
int t;
cin>>t;
while(t--)
{
	long long n,m;
	cin>>n>>m;
	long long ans=(1+m)*m/2;
	long long ans1=(2+n)*(n-2+1)/2*m;
	cout<<ans+ans1<<endl;
}
```




---

## 作者：Fr0sTy (赞：0)

### 题意简述
------------

给定 $t$ 组数据，每组数据有两个整数 $n,m$，表示有一个 $n \times m$ 的矩阵。

矩阵的每个点都有值，表示到这个点要的成本，且这个值为 $a_{ij} = (i-1) \cdot m + j$。

现在要从 $(1,1)$ 到 $(n,m)$，问最小成本。

### 解题思路
------------

这里的最优解就是**先横着走，再竖向走**。

因为在第一行横着走时，$i-1 = 0$，此时 $a_{ij} = j$。而向下走成本都是一样的，可以证明这种走法最优。

横向走的成本(**等差数列**优化到 $\Theta (1) $ 级别)：

$$ans_1 = \dfrac{(m+1) \cdot m}{2}$$

竖向走的成本：

$$ans_2 = \dfrac{(m + m * n) \cdot n}{2}$$

总成本（有个 $m$ 重复算了，要减掉）：

$$ans = ans_1 + ans_2 - m$$

最后，一定要开 `long long`。

### 代码实现
------------

``` cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,m;
int main() {
	scanf("%d",&t);
	while(t--) {
		scanf("%d%d",&n,&m);
		long long ans1=m*(m+1)/2;
		long long ans2=n*(m+m*n)/2;
		printf("%lld\n",ans1+ans2-m);
	}
	return 0;
}
//code by TheCedar
```

---

## 作者：_Ad_Astra_ (赞：0)

我们可以很容易看出，如果有一条路线中某一段为 $a_{i,j},a_{i+1 ,j},a_{i+1,j+1}$ ，那么它一定大于走 $a_{i,j},a_{i,j+1},a_{i+1,j+1}$ ，因为 $a_{i,j+1} \lt a_{i+1,j}$ 。所以，我们要走的路径实际上就是先一直往右走，再一直往下走，不然中间总会出现一个 $a_{i,j},a_{i+1 ,j},a_{i+1,j+1}$ 的情况。

我们可以把这个路径分成两部分，第一部分是 $a_{1,1},a_{1,2},\cdots,a_{1,m}$ ，也就是 $1,2,3,\cdots,m$ ，第二部分就是 $a_{2,m},a_{3,m},\cdots,a_{n,m}$ ，也就是 $2 \times m,3 \times m,\cdots,n \times m$ 。第一部分的和可以表示为 $\frac{m \times (m+1)}{2}$ ，第二部分的和则是 $\frac{(n-1)(n+2)}{2} \times m$ 。所以答案就是 $\frac{m \times (m+1)}{2} + \frac{(n-1)(n+2)}{2} \times m$ 。

code:

```cpp
#include <bits/stdc++.h>
using namespace std;
long long t,n,m;

int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n>>m;
		cout<<m*(m+1)/2+(n-1)*(n+2)/2*m<<endl;
	}
	return 0;
}
```

---

