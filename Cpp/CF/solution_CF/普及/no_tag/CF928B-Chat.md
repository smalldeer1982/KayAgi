# Chat

## 题目描述

有 $n$ 条信息，每次可以显示当前信息、前 $k$ 信息以及后 $k$ 条信息,如果当前信息以上或以下的信息数不足 $k$ ,则忽略不足。对于第 $i$ 个信息，可以通过其链接访问第 $a_i$ 个信息,可以访问当前信息的链接，但如果 $a_i=0$​​ 则不可访问。问最多可以访问多少条信息。

## 样例 #1

### 输入

```
6 0
0 1 1 2 3 2
```

### 输出

```
1 2 2 3 3 3 
```

## 样例 #2

### 输入

```
10 1
0 1 0 3 4 5 2 3 7 0
```

### 输出

```
2 3 3 4 5 6 6 6 8 2 
```

## 样例 #3

### 输入

```
2 2
0 1
```

### 输出

```
2 2 
```

# 题解

## 作者：N_z_ (赞：4)

## 思路
对于数列$a_1,a_2...a_n$，对于每个$a_x$：
* $a_x=0$ 答案为第$x$个左右$k$个，注意判断是否可以取。
* $a_x≠0$ 观察到题目保证$a_x\le x$，所以答案为第$x$个左右$k$个+第$a_x$个的答案减去重叠。

使用数组维护之前的答案，我们可以只记录它依赖的及它之前的，将其设为$b$数组。

对于数列$a_1,a_2...a_n$，对于每个$a_x$：
* $a_x=0$ 
```cpp
b[x]=min(k,x-1)+1;
ans=b[x]+min(k,n-x);
```
* $a_x≠0$ 
```cpp
b[x]=b[a[x]]+min(k*2+1,x-a[x]);
ans=b[x]+min(k,n-x);
```

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100001];
int main()
{
    int n,k;
    cin>>n>>k;
    for(int x=1;x<=n;x++)
    {
        int y;
        cin>>y;
        if(y==0)a[x]=min(k,x-1)+1;
        else a[x]=a[y]+min(k*2+1,x-y);
        cout<<a[x]+min(k,n-x)<<endl;
    }
}
```

---

## 作者：Morxita_lmy (赞：2)

# CF928B Chat 题解

## Link

[洛谷](https://www.luogu.com.cn/problem/CF928B)

[Codeforces](https://codeforces.com/problemset/problem/928/B)

## Description

当你查看一条消息时，消息显示界面上会显示这条消息，上面和下面的 $k$ 条消息。每条消息**可能**可以跳转到某一条其他的消息，对于每一个开始阅读的信息位置，求看到消息的最大数量。

## Solution

观察到题目中的重要性质：**保证 $a_{i} < i$**，这意味着我们可以从第一条消息开始递推而不需要考虑后效性。

令 $res_{i}$ 为消息 $i$ 可以看到的**在消息 $i$ 之前的**信息的最大数量。

则有如下转移：

- 当 $a_{i} = 0$ 时，$res_{i} = \min (k,i - 1) + 1$。其中 `min` 是为了保证不越界。

- 当 $a_{i} \ne 0$ 时，$res_{i} = res_{a_{i}}+ \min (2 \times k + 1, i - a_{i})$。

同时，$ans_{i}$ 即为 $res_{i} + \min(k , n - i)$。

从 $1$ 到 $n$ 递推，计算时直接输出答案即可，时间复杂度 $O(n)$。

思维难度评级：普及+/提高-，代码难度评级：入门。

## Codes

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define max_n 1000101
void read(int &p)
{
    p = 0;
    int k = 1;
    char c = getchar();
    while (c < '0' || c > '9')
    {
        if (c == '-')
        {
            k = -1;
        }
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        p = p * 10 + c - '0';
        c = getchar();
    }
    p *= k;
    return;
}
void write_(int x)
{
    if (x < 0)
    {
        putchar('-');
        x = -x;
    }
    if (x > 9)
    {
        write_(x / 10);
    }
    putchar(x % 10 + '0');
}
void writesp(int x)
{
    write_(x);
    putchar(' ');
}
void writeln(int x)
{
    write_(x);
    putchar('\n');
}
int n, k;
int a[max_n], res[max_n];
signed main()
{
#if _clang_
    freopen("1.in", "r", stdin);
    freopen("1.out", "w", stdout);
#endif
    read(n), read(k);
    for (int i = 1; i <= n; i++)
    {
        read(a[i]);
        switch (a[i])
        {
        case 0:
            // 向前拓展
            res[i] = min(k, i - 1) + 1;
            break;
            break;
        default:
            // 向前拓展，注意间距和 2*k+1的关系
            res[i] = res[a[i]] + min(2 * k + 1, i - a[i]);
            break;
        }
        writesp(res[i] + min(k, n - i));
    }
    return 0;
}
```

---

### 后记

第一篇题解，大家多多支持。

[提交记录](https://www.luogu.com.cn/record/108346272)


---

## 作者：CharlesZiy (赞：2)

这题还是很有意思的，需要一段时间的思考。

本篇题解大致作为另一篇题解的补充，主要关于时间复杂度的分析和如何想到要用此类解法。

### 思路（TLE）

看到这道题，递归思想第一个映入眼帘。

对于编号 $1$ 到 $n$ 的每一条消息都跑一次递归如下：

```cpp
int lst[100005]; //存储每一条信息的数组
bool tmp[100005]; //临时数组，会在递归函数中用到

void find(int x)
{
	for (int i = x - 1; i > 0 && i >= x - k; i--) tmp[i] = 1;
	
	tmp[x] = 1;
	
	for (int i = x + 1; i <= n && i <= x + k; i++) tmp[i] = 1;
	
	if (lst[x]) find(lst[x]);
}
```
时间复杂度 $O(n^2)$ 及以上。  
然而：

> 计算机每秒大约可以处理 $10^7$ 条指令。

并且，在本题中：

> 保证 $n \leq 100000$。

显然不能 `AC`。

### 思路（AC）

有了上面的教训，我们来分析一下复杂度：

首先，读入占了一个 $O(n)$ 复杂度（最坏情况下占去 $100000$ 次操作的时间）。这就意味着我们需要在 $9~900~000$ 条指令下求解并输出，平均到每一个数上的可用指令只有 $100$ 条不到。

所以，我们正在面对一个严峻的问题：我们需要在 $O(1)$ 的复杂度下求出解法。

而对于 $O(1)$ 访问的算法，前缀和思想是一个不错的想法。而本蒟蒻认为，前缀和的作用其实就相当于一个 $O(1)$ 的简单递归，只是递归是“从上往下”，而前缀和是“从下往上”而已。

这样的话，结合题解池里 N_z_ 大佬的题解，我们就可以用一个类似前缀和思想的方法解决本题了（具体思路在那一篇题解中有详细叙述，我就不再“班门弄斧”了）。

### Code:
```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int n, k;
int lst[100005];
int ans[100005];

int main()
{
	std::ios::sync_with_stdio(false);
	
	cin >> n >> k;
	
	for (int i = 1; i <= n; i++)
	{
		int a;
		cin >> a;
		
		if (a == 0) ans[i] = min(k, i - 1) + 1;
		else ans[i] = ans[a] + min(k * 2 + 1, i - a);
		cout << ans[i] + min(k, n - i) << " ";
	}
}
```

---

## 作者：linan04195 (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/CF928B)
## 思路

这题要是没翻译还真看不懂。

读题，发现可以分类讨论。

答案 $ans$ 有两种情况：

1. $a_i\ne0$ 时，$ans$ 为 $i$ 左右 $k$ 个之和加上自身。
2. $a_i=0$ 时，$ans$ 为 $i$ 左右 $k$ 个之和。

## Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int ans[N];
int n,k;
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		int t;
		cin>>t;
		if(t==0) ans[i]=min(k,i-1)+1;
		else ans[i]=ans[t]+min(k*2+1,i-t);
		cout<<ans[i]+min(k,n-i)<<" ";
	}
}
```

---

## 作者：hyacinth_lpy (赞：1)

根据题意，如果 $a_i=0$ 时则不可访问，那么，答案为第 $i$ 个左右 $k$ 个之和，并且，我们还需要判断一下是否可取。$\\$
对于 $a_i≠0$ 的情况，题目中指出，会保证 $a_i<i$ ，所以，答案则为第 $i$ 个左右 $k$ 个的基础上再加上 $a_i$ 。$\\$
所以，对于以上的情况，每个 $a_i$ 需要分开判断。
## Code
```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
using namespace std;
typedef long long ll;
inline int read()
{
    int x=0,y=1;
    char c=getchar();
    while(c<'0' || c>'9')
    {
        if(c=='-')y=-1;
        c=getchar();
    }
    while(c>='0' && c<='9')x=(x<<3)+(x<<1)+c-'0',c=getchar();
    return x*y;
}int __lcm(int a,int b){return a*b/__gcd(a,b);}
bool prime(int n)
{
	if(n<2)return false;
	for(int i=2;i<=sqrt(n);i++)if(n%i==0)return false;
	return true;
}
int a[1010101],b[1010101];
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie();cout.tie();
	//freopen("","r",stdin);
	//freopen("","w",stdout);
	int n,k;
	n=read();
    k=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)
	{
		if(a[i]==0)b[i]=min(i-1,k)+1;
		else b[i]=min(i-a[i],k*2+1)+b[a[i]];
		cout<<min(n-i,k)+b[i]<<' ';
	}
	return 0;
}
```

---

## 作者：LouYiYang1 (赞：1)

对于数列 $a_{1},a_{2}…a_{n}$ ，对于每个 $a_{i}$ ：

- $a_{i} = 0$ 答案为第 $i$ 个左右 $k$ 个，注意判断是否可以取。
- $a_{i} \ne 0$ 观察到题目保证 $a_{i} ≤ i$ ，所以答案为第 $i$ 个左右 $k$ 个加上第 $a_{i}$ 个的答案减去重叠。

对于不同的情况，我们只要分开判断就行了。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[100005];
int main() {
	int n, k;
	cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		int m;
		cin >> m;
		if (m == 0) {
			a[i] = min(k, i - 1) + 1;
		} else {
			a[i] = a[m] + min(k * 2 + 1, i - m);
		}
		cout << a[i] + min(k, n - i) <<" ";
	}
	return 0;
}
```

---

## 作者：Hutao__ (赞：1)

## 思路
简单模拟题。

对于每一个 $a_i$，我们有两种情况：

- 当 $i=0$ 时，显然答案为第 $x$ 个的左右 $k$ 个，注意可取性。

- 当 $i \neq 0$ 时，答案为第 $x$ 个的左右 $k$ 个加上第 $a_i$ 个的答案，然后减去重复部分。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100005];
int n,k;
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		if(x==0)a[i]=min(k,i-1)+1;
		else a[i]=a[x]+min(k*2+1,i-x);
		cout<<a[i]+min(k,n-i)<<' ';
	}
}
```

---

## 作者：headache (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF928B)


---

## 思路
  当我们彻底读懂这个复杂的描述后，可以精炼得得出两条结论。

  $\bullet$ 当 $a_i$ $=$ $0$ 时，答案为第 $i$ 个左右 $k$ 个之和

  **注意判断是否可取！！！**
  
  $\bullet$ 当 $a_i$ $\ne$ $0$ 时，描述中也保证   $a_i < i$ 答案则为第 $i$ 个左右 $k$ 个的基础上加上 $ a_i$ 本身。

  
  **注意减去重叠部分！！！**

  于是这道题变成了一道模拟 $+$ 条件分支题


---

## 代码部分

```
#include<bits/stdc++.h>
using namespace std;
int ans[100005],a[100005];
int main(){
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]==0) ans[i]=min(k,i-1)+1;
		else ans[i]=ans[a[i]]+min(k*2+1,i-a[i]);
		cout<<ans[i]+min(k,n-i)<<" ";
	}
	return 0;
}
```

---

## 作者：Graph_Theory (赞：0)

## 思路
因为 $a_i<i$ 所以可以递推。
### 定义
定义 $b_i$ 表示 从 $i$ 号点到 $1$ 号点可以看见的消息的数量。

### 转移

#### 1.当 $a_i>0$ 时
此时你可以看见从 $a_i$ 号点到 $1$ 号点可以看见的消息的数量。

因为我们定义的状况为当前点前面可以看到的点的数量，忽略了中间的部分所以还要加上从 $a_i$ 号点到 $i$ 之间可以看见的数量，这里要分类讨论。

##### 1.1 两个之间的长度大于 $2\times k$

此时 $a_i$ 号点又可向后看到 $k个点$ 而 $i$ 号点可看到 $k+1$ 个点这里加上 $1$ 是因为他还可以看到自己，此时答案为 $2*k+1$.

##### 1.2 两个之间的长度小于 $2\times k$

此时的长度为两点之间的点的数量以及 $i$ 号点本身，即为 $(i-a-1)+1$ 简化得 $i-a$。

不难看出，当两个之间的长度大于 $2 \times k$ 时 $i-a>2 \times k+1$。

当两个之间的长度小于 $2\times k$ 时 $i-a<2 \times k+1$。

所以我们只需对 $i-a<2 \times k+1$ 和 $i-a$ 取最小值即可。

最后得出：

$$b_i = b_{a_i}+\min(2\times k+1,i-a)$$

#### 2.当 $a_i=0$ 时 

为防止越界，对 $k$ 和到边界距离取最小值，最后再加自身的 $1$ 即可。

$$b_i = 1+\min(k,i-1)$$

### 答案

最后再加上后面长度。为防止越界，对 $k$ 和到边界距离取最小值。

$$ans=b_i + \min(k, n - i)$$

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

int n, k;
int b[100005];
int main()
{
	cin >> n >> k;
	for (int i = 1; i <= n; i++)
	{
		int a_i;
		cin >> a_i;		
		if (a_i == 0) b[i] = min(k, i - 1) + 1;
		else b[i] = b[a_i] + min(k * 2 + 1, i - a_i);
		cout << b[i] + min(k, n - i) << " ";
	}
}
```

---

## 作者：rain_dew (赞：0)

一道模拟题，需要一定动态规划基础。

### 题意：

共有 $n$ 个信息。对于当前第 $i$ 个信息，可以访问它前 $k$ 个信息，后 $k$ 个信息，第 $a_i$（在下面的代码中定义为 $f_i$）个信息（题目保证一定 $a_i < i$），和它本身的信息。试问当前点开第 $i$ 条信息后，最多能看到多少信息。

### 思路：

我们可以通过提供的样例 $2$ 来解释这道题目思路。

1. 当 $a_i=0$ 时，即不能跳转去其他任何信息时，它只能查看自己的信息与它前 $k$ 个与后 $k$ 个信息（如下图所示黑框线与蓝框线），同时要判断是否出现超界的情况：

![第一种情况](https://cdn.luogu.com.cn/upload/image_hosting/kqtzyws0.png)

+ $i-1$ 指除了当前 $i$ 的情况，前第 $1$ 项到第 $i$ 项是否不足于最大阅读数目 $k$，并与其取最小值。
+ $n-i$ 指除了当前 $i$ 的情况，后 $i+1$ 到递 $n$ 项是否不足于最大阅读数目 $k$，并与其取最小值。
+ 最后计算第 $i$ 项算一种答案。

$$dp_i= \min(i-1,k)+\min(n-i,k)+1$$

2. 当 $i-a_i \le 2\times k$ 时（即虽然能跳转，但跳转的属于 $k$ 能影响到的范围），为方便叙述，我们设 $a_i$ 为 $b$，如下图紫色框线所示：

![第二种情况](https://cdn.luogu.com.cn/upload/image_hosting/45wvceot.png)

+ 首先吸纳 $dp_b$ 的值。（橙色线条）
+ 判断 $i+k$（$i$ 号点向右 $k$ 个消息）是否超界（题目已经保证一定 $a_i < i$，无需在判断 $i-k$ 且已经包含在 $dp_b$ 的值中），并取最小值。（青色线条）
+ 同时，此时多算了 $b$ 号点向右的取值，因此需要再减去多算的部分，方法与上面 $i+k$ 的相似。（黑色线条）
+ 显而易见，最后橙色线条加上青色线条减去黑色线条即为答案。

$$dp_i=dp_b+\min(n,i+k)-\min(n,b+k)$$

3. 否则 $i-a_i > 2\times k$ 时（跳转到不属于 $k$ 能影响到的范围），为方便叙述，我们设 $a_i$ 为 $b$，如下图蓝色框线所示：

![第三种情况](https://cdn.luogu.com.cn/upload/image_hosting/7wt4qbod.png)

+ 首先吸纳 $dp_b$ 的值。（第一个紫色方框）
+ 还能得到前面 $k$ 个（已经保证了 $i-a_i > 2\times k$）消息。（第二个紫色方框）
+ 如同第一种情况，计算 $n-i$ 的情况。（第三个紫色方框）
+ 最后第 $i$ 项算一种答案。（蓝色方框）

$$dp_i=dp_b+k+ \min(n-i,k)+1$$

4. 按照要求输出每个答案。

### 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,k;
int dp[100005],f[100005];
int main()
{
	scanf("%d%d",&n,&k);
	for (int i=1;i<=n;i++)
	{
		scanf("%d",f+i);
		if (!f[i])
			dp[i]=min(i-1,k)+min(n-i,k)+1;
		else
			if (i-f[i]<=k*2)
				dp[i]=dp[f[i]]+min(n,i+k)-min(n,f[i]+k);
			else
				dp[i]=dp[f[i]]+k+min(n-i,k)+1;
		printf("%d ",dp[i]);
	}
	return 0;
}
```

---

## 作者：LouYiYang1 (赞：0)

对于数列 $a_{1},a_{2}…a_{n}$ ，对于每个 $a_{i}$ ：

- $a_{i} = 0$ 答案为第 $i$ 个左右 $k$ 个，注意判断是否可以取。
- $a_{i} \ne 0$ 观察到题目保证 $a_{i} ≤ i$ ，所以答案为第 $i$ 个左右 $k$ 个加上第 $a_{i}$ 个的答案减去重叠。

对于不同的情况，我们只要分开判断就行了。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[100005];
int main() {
	int n, k;
	cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		int m;
		cin >> m;
		if (m == 0) {
			a[i] = min(k, i - 1) + 1;
		} else {
			a[i] = a[m] + min(k * 2 + 1, i - m);
		}
		cout << a[i] + min(k, n - i) <<" ";
	}
	return 0;
}
```

---

