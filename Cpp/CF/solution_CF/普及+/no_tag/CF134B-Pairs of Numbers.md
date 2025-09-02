# Pairs of Numbers

## 题目描述

让我们假设有一对数$(a,b)$。我们可以从前一步得到后一对数$(a+b,b)$或者$(a,a+b)$。

让我们规定一开始这对数为$(1,1)$。你的任务就是找到数$k$，使$k$为从$(1,1)$转换到一对至少含有一个$n$的数对的最少步骤。

## 样例 #1

### 输入

```
5
```

### 输出

```
3
```

## 样例 #2

### 输入

```
1
```

### 输出

```
0
```

# 题解

## 作者：GalwayGirl (赞：10)

看题解里都是用的搜索，~~我为了造福后人~~，写下了这篇题解。

## Solution 
首先看到题目中 $(a,b)$ 可以变成 $(a+b,b)$ 以及 $(a,a+b)$，我立马联想到了更相减损术，它是这样子的：
$$\gcd(a,b)=\gcd(b,a-b)=\gcd(a,a-b)$$

好像并没有什么用，如果直接这么写无异于暴搜，~~虽然暴搜也能过。~~ 但不要忘记它是等同于辗转相除法的：
$$\gcd(a,b)=\gcd(b,a\bmod b)$$

这样子不断转换效率快很多，那先按着这个思路走，一步一步推。

- 因为辗转相除法是倒着递归的， $n$ 是已知的，所以还要枚举另一个数，并且这个数是小于等于 $n$ 的，因为大于的话会多操作，显然不优。
- 进入递归后，因为我们递归的是 $(b,a\bmod b)$，操作次数不能一步一步加出来，但其实想想就知道这样子的操作次数是 $a/b$，加上即可。
- 假设递归时 $(a,b)$，$b$ 变成了 $1$，因为起点是 $(1,1)$，所以还要把 $a$ 变成 $1$，操作次数为 $a-1$，需加上。
- 还需要特判一下，当 $(a,b)$ 中 $b$ 成为 $0$ 后，说明该方案是不合法的，返回正无穷即可。

思路完毕，最后贴上代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,min_=1e9;
int gcd(int a,int b){
    if(!b)return 1e9;
    if(b==1)return a-1;
    return gcd(b,a%b)+a/b;
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)min_=min(min_,gcd(n,i));
    printf("%d",min_);
    return 0;
}
```
码量极小还跑的飞快，这多是一件美事啊。

---

## 作者：CGDGAD (赞：8)

### 原题大意：

有个数对 $(a, b)$，每次可以变化成 $(a + b, b)$ 或 $(a, a + b)$，这个数对一开始是 $(1, 1)$，请问经过最少多少次变化后 $a, b$ 中的一个是 $n$。

### 思路：

最先想到的思路肯定是递归了，使用dfs。

我一开始写了一个正向的，从 $(1, 1)$ 往后找。

可是这样并不行，因为有太多种情况了，运算的次数是 **指数级的**，再多的剪枝也不行。

所以我们采用逆向bfs。

定义函数 `void dfs(int a, int b, int step)`。
$step$ 是操作的次数。

主程序：输入 $n$，然后从 $1$ 遍历到 $n$，每次执行 $dfs(i, n, 0)$ 。

### dfs()实现方法：


**边界条件：**

如果 $a = 1$ 以及 $b = 1$，将目前的 $step$ 值与事先定义好的变量 $min$ （代表最小的次数）比较，如果更小就将 $step$ 赋给 $min$；

如果 $a \lt 1$ 或 $b \lt 1$，则返回，不符合题意（原题是从 $(1, 1)$ 开始的，如果 $\lt 1$ 就不对了）

如果 $step \geq min$，已经比最好的方案差了，那么就不用再继续找了。

在其他的情况下，执行 $dfs(a - b, b, step + 1)$ 和 $dfs(a, b - a, step + 1);$。 当然，前提分别是 $a - b \gt 0$ 和 $b - a \gt 0$，才执行。

### 完整代码：

（上文都讲过了，就不给注释了）

```cpp
#include <cstdio>
#define MIN(A, B) (A < B ? A : B)
int min = 100000000, n;
void dfs(int a, int b, int step) {
	if (a < 1 || b < 1 || step >= min) {
		return;
	}
	if (a == 1 && b == 1) {
		min = MIN(min, step);
	}
	if (a - b > 0) {
		dfs(a - b, b, step + 1);
	}
	if (b - a > 0) {
		dfs(a, b - a, step + 1);
	}
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i += 1) {
		dfs(i, n, 0);
	}
	printf("%d\n", min);
	return 0;
}
```

---

## 作者：Purple_Circle (赞：3)

题意简述：通过把 $(a,b)$ 变换成 $(a+b,b)$ 或 $(a,a+b)$ 的形式直到 $(1,1)$，输出最佳步数。


~~这简直是道 Dfs 裸题~~

很容易能想到 Dfs 进行搜索，具体思路如下：

-----
第一步，搜索思路。

容易想到并非是从 $(1,1)$ 开始搜，而是应该枚举 $(1,n)$ 到 $(n,n)$ 中所有的序列倒着往 $(1,1)$ 搜索。也就是每次搜索 ```dfs(i,n,0)```。

-----
第二步，dfs 本体。

对于每个 ```dfs(x,y,now)``` ，规定 $x,y$ 为数对 $(x,y)$ 的两个数，而 $now$ 则为当前所走的步数。

Dfs 策略如下:

1，如果 $x<1$ 或 $y<1$ 或 $now \ge ans$，退出，因为此时变换已经毫无意义或超出了原有范围。（剪枝）

2，如果此时是 $(1,1)$，更新答案，return。

3，否则递归到 ```dfs(a-b,b,now+1)``` 与 ```dfs(a,b-a,now+1)```。

完整代码如下：

```cpp
#include<bits/stdc++.h>
#define rd read()
using namespace std;
inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	return x * f;
}
int ans=0x3f3f3f3f,n;
void dfs(int a,int b,int now){
	if(a<1||b<1||now>=ans){
		return;
	}
	if(a==1&&b==1){
		ans=now;
	}
	dfs(a-b,b,now+1);
	dfs(a,b-a,now+1);
}
int main(){
	n=rd;
	for(int i=1;i<=n;i++){
		dfs(i,n,0);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：TheSky233 (赞：2)

## Description
给定正整数 $n$，使数对 $(1,1)$ 经过变换成 $(a+b,a)$ 或 $(a,a+b)$ 后使数对中含有 $n$ 的最小步骤。
## Solution
### 思路
首先想到的自然是从 $(1,1)$ 开始进行深搜。分析一下时间复杂度，发现为 $O(2^{step})$，会 TLE，这时候，就要从 $(i,n)$ 的最终状态开始倒着搜，这样会省去很多无用状态。


------------
### 思路证明
证明:数对中含有 $n$ 的最小步骤一定在 $(1 \cdots n,n)$ 中：

如果最小步骤位于
$$(k \times n+1 \cdots k \times n+n,n),k \geq 1$$ 
中，则可以通过 
$$((k-1) \times n+1 \cdots (k-1) \times n+n,n)$$ 
推出，可知 $(k \times n+1 \cdots k \times n+n,n)$ 的步骤一定更小，与假设不符。


------------
### 主函数
所以，主函数内要做的事就很明确了，```for``` 循环从 $1$ 枚举到 $n$，进行 ```dfs(i,n,0)```，这三个参数下面会讲到。

------------
### dfs 怎么写
定义 ```dfs(int a,int b,int step)```，$a,b$ 表示数对的两个数字，$step$ 表示现在用的步骤。

一个显而易见的最优性剪枝：如果当前的 $step$ 大于等于之前搜到的答案，就可以直接 ```return``` 了。

当 $a > b$ 时，显然是通过 $(a-b,b)$ 推出， ```dfs(a-b,b,step+1)``` 即可。

同理，$a < b$ 时，显然是通过 $(a,b-a)$ 推出， ```dfs(a,b-a,step+1)``` 即可。

如果 $a=1$ 且 $b=1$ 时，就可以记录一下答案然后  ```return``` 掉了。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;

inline int read(){
    char c; bool f (true);
    while (c = getchar(), c < '0' || c > '9') f = c != '-';
    int x (c ^ 48);
    while (c = getchar(), c >= '0' && c <= '9') x = (x << 1) + (x << 3) + (c ^ 48);
    return f ? x : -x;
}
inline void write(int x){
    char c[30]; int top(0);
    if (x < 0) x = -x, putchar('-');
    do c[++ top] = x % 10 + 48; while (x /= 10);
    do putchar(c[top --]); while (top);
}

int n,ans=INT_MAX;

void dfs(int a,int b,int step){
	if(step>=ans) return;
	
	if(a==1 && b==1){
		ans=step;
		return;
	}
	
	if(a>b) dfs(a-b,b,step+1);
	if(b>a) dfs(a,b-a,step+1);
}

int main(){
	n=read();
	for(int i=1;i<=n;i++) dfs(i,n,0); 
	write(ans);
	return 0;
}
```
## [AC](https://www.luogu.com.cn/record/67936247)

---

## 作者：codeLJH114514 (赞：1)

[$\colorbox{blue}{\textcolor{white}{CF134B}}$](https://www.luogu.com.cn/problem/CF134B)

# Problem

[原题链接](https://www.luogu.com.cn/problem/CF134B)

给定一个基础数对，变大全靠自己加自己！

问最少用几步才能来到一个至少有一个 $n$ 的数对？

# Sulotion

本题我可以想到两种方法来解决。

这道题我的第一想法就是 DFS！

当然纯 DFS 肯定 TLE。

DFS 函数的主体就是：
```cpp
void DFS(int a, int b, int s); // a,b 就是一个数对，s 就是步数。
```

所以我们就可以使用**优化的** DFS 即可，当然一般不叫优化的 DFS，叫剪枝！

那可以使用什么剪枝呢？

**剪枝1：最优化剪枝。**

因为题目让我们求最小值，所以如果当前的步数大于目前的答案，直接 return 掉即可。

**剪枝2：可行性剪枝。**

因为题目的变化方法只有加法，所以如果 $a,b$ 中有一个大于 $n$，那么就再也无法挽回了，因为在怎么变换大于 $n$ 的那个数已经不可能再等于 $n$ 了，下一步小于 $n$ 的那个数加上更大的那个数也不可能再等于 $n$ 了，综上所述，当 $a,b$ 中有一个数大于 $n$ 就可以直接 return 掉。

事实证明这两个剪枝足以让我们的代码起死回生。

## Sulotion1: DFS+剪枝

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
int ans = 0x3f3f3f3f;
void DFS(int, int, int);
int main() {
    cin >> n;
    DFS(1, 1, 0);
    cout << ans;
    return 0;
}
void DFS(int a, int b, int s) {
    if (s >= ans)
        return ; // 最优化剪枝
    if (a == n or b == n)
        ans = s;
    if (a > n or b > n)
        return ; // 可行性剪枝
    DFS(a, a + b, s + 1);
    DFS(a + b, b, s + 1);
}
```

这个代码还有一个优化方法，那就是倒推法，就是从 $(i, n) (i = 1, \dots, n)$ 搜到 $(1, 1)$，这样也是可以过的，并且时间差不多。

注意也加上了**最优化剪枝**和**可行性剪枝**。

## Sulotion2: DFS+倒推

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
int ans = 0x3f3f3f3f;
void DFS(int, int, int);
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        DFS(i, n, 0);
    cout << ans;
    return 0;
}
void DFS(int a, int b, int s) {
    if (s >= ans) // 最优化剪枝
        return ;
    if (a == 1 and b == 1)
        ans = s;
    if (a < 1 or b < 1 or (a == 1 and b == 1))
        return ; // 可行性剪枝（or 后面的是刚才的答案，赋值了之后要 return。）
    if (a < b) DFS(a, b - a, s + 1);
    if (a > b) DFS(a - b, b, s + 1);
}
```

拒绝抄袭题解，共创美好洛谷。

---

## 作者：Exiler (赞：0)

## 原题

[CF134B Pairs of Numbers](https://www.luogu.com.cn/problem/CF134B)

---

## 思路概述

### 题意分析

给定一个初始值为 $(1,1)$ 的有序数对和 $n∈N^*$ ，规定每次能执行操作 $(a,b)→(a+b,b) \text{ or } (a,b)→(a,a+b)$ ，求该数对操作到满足 $a=n \text{ or } b=n$ 的最小步数。

### 思路分析

操作方式太原始，直接考虑DFS。但一个数对 $(a,b)$ 满足其中一个等于 $n$ 的状态数太多，故考虑反向搜索，从 $(n,k)(k∈N^*)$ 搜回 $(1,1)$ 。

---

## 算法实现

### 关于反向搜索

首先讨论反向搜索的正确性。由于题目要求构造一种从 $(1,1)$ 转移到 $(n,k)(k∈N^*)$ 的操作方案并求最小步数，再考虑操作方式，不难得出：对于除 $n$ 外的另一个数 $k$ ，其大小与步数始终呈正相关关系。所以在满足步数最小的情况下， $k$ 的值必然在区间 $[1,n]$ 内（若 $k>n$ ，则数对 $(n,k)$ 必然由 $(n,k-n)$ 转移而来，则当前求出数对所需操作数不是最小值）。

### 关于搜索

正常深度优先搜索算法结构，终止条件为 $x=1 \text{ and } y=1$ 。主函数中枚举 $(n,k)(k=1,2,3...n)$ 即可。
```cpp
if(x==1 && y==1)
{
	minimum=s;
	return;
}
else
{
	if(x>y) dfs(x-y,y,s+1);
	else dfs(x,y-x,s+1);
	return;
}
```

### 简单剪枝技巧

对于搜索过程中出现的步数 $s$ 大于当前纪录最小步数最小值 $minimum$ ，直接返回，可优化部分无效搜索。

---

## AC code
```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<queue>
#include<set>
#include<ctime>
#define RI register int
using namespace std;
int n,minimum=0x3f3f3f3f;
inline int read();/*快读（板子自带）*/
inline void print(int x);/*快输（板子自带）*/
inline void dfs(int x,int y,int s);/*DFS 但是逆向搜索*/
int main()
{
	n=read();
	for(RI i=1;i<=n;++i) dfs(n,i,0);
	print(minimum);
	return 0;
}
inline int read(void)
{
	char putin;bool isneg=false;RI ret=0;
	putin=getchar();
	while((putin>'9' || putin<'0') && putin!='-')
		putin=getchar();
	if(putin=='-')
	{
		isneg=true;
		putin=getchar();
	}
	while(putin>='0' && putin<='9')
	{
		ret=(ret<<3)+(ret<<1)+(putin&15);
		putin=getchar();
	}
	return isneg?-ret:ret;
}
inline void print(int x)
{
	if(x<0)
	{
		putchar('-');
		x=-x;
	}
	if(x>9) print(x/10);
	putchar(x%10+'0');
	return;
}
inline void dfs(int x,int y,int s)
{
	if(s>minimum) return;/*简单剪枝操作 若当前操作步数已经超过记录的最小值 则直接停止搜索*/
	else if(x==1 && y==1)/*搜到x=1,y=1的情况 搜索终止 开始回溯*/
	{
		minimum=s;
		return;
	}
	else
	{
		if(x>y) dfs(x-y,y,s+1);
		else dfs(x,y-x,s+1);
		return;
	}	
}
```



---

## 作者：Mars_Dingdang (赞：0)

## 题目大意
对于一个数字对 $(a, b)$，我们可以通过一次操作将其变为新数字对 $(a+b, b)$ 或 $(a, a+b)$。

给定一正整数 $n$，问最少需要多少次操作可将数字对 $(1, 1)$ 变为一个数字对，该数字对至少有一个数字为 $n$。

## 大体思路：
因为这一题是要求 $(1,1)$ 到 $(n,i)$ 的最少步数 (可证 $i\leq n$，因为当 $i>n$ 时一定会可以在前一步或几步中出现过 $(n,i_2)$中 $i_2\leq n$ 的情况) ，因此我们可以枚举 $i$ 从 $1\sim n$，当出现一种正确的情况时与当前最小次数比较，保留较小的次数。

此外还需要考虑边界的问题。分析可知当 $(x,y)$ 中 $x=y$ 时可以返回步数的值。$x$ 与 $y$ 相等时又分两种:

1. 如果其中一个是 $1$，说明还原成功了，直接返回步数

2. 如果其中一个不是 $1$，那么一定无法继续还原得到$(1,1)$，返回一个大数

如果在还原过程中第一个数小于第二个数，不用交换，将大数一直减去小数直到这个数比原来的小数还要小即可；这时我们还需要考虑步数，还原的步数其实就是大数减去小数的次数，加到下一个递归里就可以了。

可以设计一个函数记录次数

（附：如果前面 $i$ 从 $1$ 枚举到 $n-1$ ，那么 $n=1$ 时需要进行特判）

## 完整代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int minn=2000000000;
void dfs(int x,int y,int r){
    if(r>minn)
        return ;//剪枝
    if(x==1&&y==1){
        minn=min(minn,r);
        return ;//满足条件
    }
    if(x<1||y<1)
        return ;//边界
    if(x>y)
        dfs(x-y,y,r+1);
    else if(y>x)
        dfs(x,y-x,r+1);//递归
}
int main(){
    int n;
    cin>>n;
    if(n<=1) {
        cout<<0;
        return 0;
    }
    if(n==2) {
        cout<<1;
        return 0;//特判几种情况
    }
    for(int i=2;i<n;i++)
        dfs(i,n,0);//搜索
    cout<<minn;//输出
    return 0;//over！
}

---

## 作者：江山_远方 (赞：0)

这题意思很简单，就是~~开局一数对，升级全靠加~~，开局数对为（1,1），之后每次可以由(a,b)变为（a,a+b）或(a+b,b),
求a或b变成n的最小次数

直接做会超时，考虑从（n,i）变为（1,1），每次枚举i=1~max(n-1,1),上代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
using namespace std;
int n,ans,MIN;
void dfs(int k,int a,int b)
{
    if(ans>0)return ;
    if(a==1&&b==1&&k>0)
    {
        ans=k;
        return ;
    }
    if(b%a>0&&b%a<a)dfs(k+b/a,b%a,a);
    if(b%a>0&&b%a>=a)dfs(k+b/a,a,b%a);
    if(b%a==0&&a!=b)dfs(k+(b-a)/a,a,a);
    if(a==b&&(a!=1||b!=1))return ;
}
int main()
{
    cin>>n;
    MIN=2000000000;
    for(int i=1;i<=max(n-1,1);i++)
    {
        ans=0;
        dfs(0,i,n);
        if(ans!=0)MIN=min(ans,MIN);
    }
    if(MIN!=2000000000)cout<<MIN;
      else cout<<0;
}
```


---

## 作者：tanghairong (赞：0)

容易发现，如果按照题目的规则进行搜索的话，显然会超时（搜索次数会达到 $2^k$）

那么换一种思路，既然搜过去行不通，搜回来呢？

显然，此时时间复杂度会更优。

搜 $n$ 遍，起点分别为 $(i,n)$ $(1\leq i\leq n)$

Q1：为什么对于比 $n$ 大的 $i$ 不用搜索呢？

A1：因为 $(i,n)$ 可由 $(i-n,n)$ 变换而来，故比 $n$ 大的 $i$ 一定不会比 $i-n$ 更优。

Q2：为什么不用搜 $(n,i)$ 呢？

A2：因为这两种情况是关于直线 $(1,1)$ 和 $(n,n)$ 对称的，在搜索时，我们只需保证对任意节点 $(a,b)$，有 $a\leq b$ 即可。

Q3：如何转移保证考虑到每一种有用且合理的情况？

A3：一个点 $(a,b)$ 可由 $(a-b,b)$ $(b,a-b)$ $(b-a,a)$ $(a,b-a)$ 四个点转移而来，比较 $a$ 和 $b$ 的大小，$a$ 比 $b$ 大就用前2个，$a$ 比 $b$ 小就用后2个。

Q4：如何保证每一个节点 $(a,b)$ 使得 $a\leq b$ ？

A4：对 $a-b$ 和 $b$，对 $b-a$ 和 $a$ 分别比大小，小的作为新的 $a$，大的作为新的 $b$。

Q5：还有没有剪枝？

A5：当 $a$ 或者 $b$ 有越界的时候，或者目前的转移数量 $now$ 已经大于等于目前的最小答案 $k$ 的时候，$return$。

另外，如果 $a=1$ 并且 $b=1$，即找到源头，可尝试更新答案。

$code$：

```cpp
#include<iostream>
using namespace std;
int k=0x3f3f3f3f;
void dfs(int a,int b,int now){
    if(a<1||b<1||now>=k)return;
    if(a==1&&b==1){k=min(k,now);return;}
    if(a>b)dfs(min(a-b,b),max(a-b,b),now+1);
    if(b>a)dfs(min(b-a,a),max(b-a,a),now+1);
}
int main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)dfs(i,n,0);
    cout<<k;
    return 0;
}
```

---

## 作者：_lxy_ (赞：0)

### 题意

略

### 分析

爆搜即可。如果从 $(1,1)$ 开始搜，显然会 TLE，所以可以枚举最终的状态，倒推 dfs 得到 $(1,1)$，打擂台取最少步数。对于一个状态 $(a,b)$，如果 $a>b$，说明是从 $(a'+b',b')$ 扩展得到的，所以就倒推回 $(a',b')$，也就是 $(a-b,b)$；同理，如果 $a<b$，就倒推回 $(a,b-a)$，如果 $a=1,b=1$ 就比较当前步数与当前最少的步数，更新答案。

### 代码

```cpp
#include <bits/stdc++.h>
#define mem(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int MAXN=1e5+7;
inline void qread(){}template<class T1,class ...T2>
inline void qread(T1 &a,T2&... b)
{
	register T1 x=0;register bool f=false;char ch=getchar();
	while(ch<'0') f|=(ch=='-'),ch=getchar();
	while(ch>='0') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	x=(f?-x:x);a=x;qread(b...);
}
template<class T1,class T2>inline T1 qmax(const T1 &x,const T2 &y){return x>y?x:y;}
template<class T1,class T2>inline T1 qmin(const T1 &x,const T2 &y){return x<y?x:y;}
int n,ans=2139062143;
void dfs(int a,int b,int c)
{
	if(a==1&&b==1) ans=qmin(ans,c); // 回到初始状态，就更新答案
	if(a>b) dfs(a-b,b,c+1); // 从(a'+b',b')扩展来
	if(b>a) dfs(a,b-a,c+1); // 从(a',a'+b')扩展来
}
int main()
{
	qread(n);
	for(int i=1;i<=n;i++) dfs(i,n,0),dfs(n,i,0); //枚举每一个最终状态
	printf("%d\n",ans);
	return 0;
}
```

---

