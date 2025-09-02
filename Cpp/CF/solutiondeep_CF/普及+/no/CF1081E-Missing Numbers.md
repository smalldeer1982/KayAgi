# 题目信息

# Missing Numbers

## 题目描述

Chouti is working on a strange math problem.

There was a sequence of $ n $ positive integers $ x_1, x_2, \ldots, x_n $ , where $ n $ is even. The sequence was very special, namely for every integer $ t $ from $ 1 $ to $ n $ , $ x_1+x_2+...+x_t $ is a square of some integer number (that is, a [perfect square](https://en.wikipedia.org/wiki/Square_number)).

Somehow, the numbers with odd indexes turned to be missing, so he is only aware of numbers on even positions, i.e. $ x_2, x_4, x_6, \ldots, x_n $ . The task for him is to restore the original sequence. Again, it's your turn to help him.

The problem setter might make mistakes, so there can be no possible sequence at all. If there are several possible sequences, you can output any.

## 说明/提示

In the first example

- $ x_1=4 $
- $ x_1+x_2=9 $
- $ x_1+x_2+x_3=25 $
- $ x_1+x_2+x_3+x_4=36 $
- $ x_1+x_2+x_3+x_4+x_5=100 $
- $ x_1+x_2+x_3+x_4+x_5+x_6=144 $

 All these numbers are perfect squares.In the second example, $ x_1=100 $ , $ x_1+x_2=10000 $ . They are all perfect squares. There're other answers possible. For example, $ x_1=22500 $ is another answer.

In the third example, it is possible to show, that no such sequence exists.

## 样例 #1

### 输入

```
6
5 11 44
```

### 输出

```
Yes
4 5 16 11 64 44
```

## 样例 #2

### 输入

```
2
9900
```

### 输出

```
Yes
100 9900
```

## 样例 #3

### 输入

```
6
314 1592 6535
```

### 输出

```
No
```

# AI分析结果

### 题目内容
# 缺失的数字

## 题目描述
Chouti正在研究一道奇怪的数学题。

存在一个由 $n$ 个正整数 $x_1, x_2, \ldots, x_n$ 组成的序列，其中 $n$ 为偶数。这个序列非常特殊，即对于从 $1$ 到 $n$ 的每个整数 $t$，$x_1 + x_2 + \ldots + x_t$ 都是某个整数的平方（也就是一个[完全平方数](https://en.wikipedia.org/wiki/Square_number)）。

不知为何，奇数索引位置的数字丢失了，所以他只知道偶数位置上的数字，即 $x_2, x_4, x_6, \ldots, x_n$ 。他的任务是恢复原始序列。又轮到你帮他了。

出题者可能会犯错，所以可能根本不存在这样的序列。如果有多个可能的序列，你可以输出任意一个。

## 说明/提示
在第一个示例中：
- $x_1 = 4$
- $x_1 + x_2 = 9$
- $x_1 + x_2 + x_3 = 25$
- $x_1 + x_2 + x_3 + x_4 = 36$
- $x_1 + x_2 + x_3 + x_4 + x_5 = 100$
- $x_1 + x_2 + x_3 + x_4 + x_5 + x_6 = 144$

所有这些数都是完全平方数。在第二个示例中，$x_1 = 100$，$x_1 + x_2 = 10000$ 。它们也都是完全平方数。还有其他可能的答案。例如，$x_1 = 22500$ 也是一个答案。

在第三个示例中，可以证明不存在这样的序列。

## 样例 #1
### 输入
```
6
5 11 44
```
### 输出
```
Yes
4 5 16 11 64 44
```

## 样例 #2
### 输入
```
2
9900
```
### 输出
```
Yes
100 9900
```

## 样例 #3
### 输入
```
6
314 1592 6535
```
### 输出
```
No
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是基于数学原理，利用完全平方数的性质来解决问题。由于给定的偶数项 $x_{2i}$ 可以表示为两个完全平方数的差值，即 $x_{2i}=A^2 - B^2 = (A - B)(A + B)$，题解们围绕如何找到合适的 $A$ 和 $B$ 展开。
- **思路方面**：多数题解采用贪心策略，认为前面的数越小，越有利于后续找到满足条件的解。例如，在选择满足 $x_{2i}=A^2 - B^2$ 的 $A$ 和 $B$ 时，尽量选择使 $A$ 和 $B$ 较小的组合。
- **算法要点**：利用完全平方数的差与因数分解的关系，通过枚举因数对来寻找满足条件的完全平方数组合。一些题解还利用双指针或二分查找等技巧优化查找过程。
- **解决难点**：难点在于如何高效地找到满足条件的完全平方数对，并且保证整个序列的前缀和都为完全平方数。同时，需要处理无解的情况，即当找不到合适的完全平方数对时，判定序列不存在。

### 所选的题解
- **作者：dead_X (5星)**
    - **关键亮点**：思路清晰，直接抓住每组数的前缀和应越小越好这一要点，通过暴力枚举因数对来找到满足条件的最小前缀和。代码简洁明了，实现高效。
    - **个人心得**：把输入的 $x_{2i}\leq 10^5$ 看成 $10^{13}$ 然后觉得不可做，这提示在解题时要仔细审题，关注数据范围对解题思路的影响。
    - **核心代码实现思想**：对每个输入的偶数项 $a[i]$，枚举其因数对，找到满足条件且使前缀和最小的因数对，计算出对应的奇数项和偶数项，存入答案数组。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int a[1000003];
int ans[1000003];
void print(int n)
{
	for(int i=1; i<=n; i++) printf("%lld ",ans[i]);
	return ;
}
signed main()
{
	int c=0;
    int n=read(),m=n/2;
    for(int i=1,lst=0; i<=m; i++) 
    {
    	a[i]=read();
    	int X=0,Y=0,qwq=-1;
    	int j=1;
    	for(; j*j<=a[i]; ++j) ;
    	for(; j>=1; --j)if(a[i]%j==0)
    	{
    		int x=j,y=a[i]/x;
    		if((x&1)!=(y&1)) continue;
    		int a=(x+y)>>1,b=(y-x)>>1;
    		x=b,y=a;
    		if(x<=lst) continue;
    		qwq=0,X=x,Y=y;
    		break;
    	}
    	if(qwq==-1)
    	{
    		puts("No");
    		return 0;
    	}
    	ans[++c]=X*X-lst*lst;
    	ans[++c]=Y*Y-X*X;
    	lst=Y;
    }
    puts("Yes");
    print(n);
	return 0;
}
```
- **作者：Caro23333 (4星)**
    - **关键亮点**：详细地阐述了通过因数分解找到满足条件的完全平方数对的过程，并利用贪心思想和二分查找优化寻找过程，时间复杂度分析清晰。
    - **核心代码实现思想**：对每个偶数项 $a[i]$，先找出所有奇偶性相同的因数对，构成x数对并排序。然后从前到后依次构造答案，通过二分查找找到首项大于前一个x数对中较小项的x数对，计算并存储答案。
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#define pii pair<int,int>
#define mp make_pair
#define fi first
#define se second

using namespace std;
typedef long long ll;
const int MAXN = 200005;
inline int readint()
{
	int res = 0;
	char c = 0;
	while(!isdigit(c))
	    c = getchar();
	while(isdigit(c))
	    res = res*10+c-'0', c = getchar();
	return res;
}
int n,a[MAXN],f[MAXN];
vector<pii> s[MAXN];
vector<pii>::iterator it; 
ll ans[MAXN];

int main()
{
    n = readint();
    for(int i = 1; i<=n/2; i++)
        a[i] = readint();
    for(int i = 1; i<=n/2; i++)
    {
        int tmp = a[i];
        for(int j = 1; j*j<tmp; j++)
        {
            if(tmp%j)
                continue;
            if((j^(tmp/j))&1)
                continue;
            s[i].push_back(mp((tmp/j-j)/2,(tmp/j+j)/2));
	    }
	    if(s[i].empty())
	    {
	        cout << "No" << endl;
			return 0; 
		} 
		sort(s[i].begin(),s[i].end());
	}
	ll now = 0;
	for(int i = 1; i<=n/2; i++)
	{
		it = upper_bound(s[i].begin(),s[i].end(),mp(f[i-1],1<<30));
		if(it==s[i].end())
		{
	        cout << "No" << endl;
	        return 0;
		}
		int x = it->fi, y = it->se;
		ans[i*2-1] = 1ll*x*x-now, ans[i*2] = a[i]; 
		f[i] = y;
		now = 1ll*y*y;
	}
	printf("Yes\n");
	for(int i = 1; i<=n; i++)
	    printf("%lld ",ans[i]);
	printf("\n");
	return 0;
}
```
- **作者：yuhooo (4星)**
    - **关键亮点**：通过详细的提示，逐步引导解题思路，先给出完全平方数差的性质，再通过具体例子说明如何选择更优的因数分解方式，最后强调贪心策略的应用。
    - **核心代码实现思想**：对每个偶数项 $a[i]$，倒序枚举因数 $j$，找到满足奇偶性相同且能保证平方数合法性的因数对，计算并存储对应的奇数项和偶数项。
```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;

#define int long long

int a[N], b[N];
//a数组为题目中的x
//b数组为sqrt(Σx[i]) 
signed main() {
    int n;
    scanf("%lld", &n);
    for (int i = 2; i <= n; i += 2) {
        scanf("%lld", &a[i]);
        int flag = 0;
        for (int j = (int)(sqrt(a[i]) + 0.5); j >= 1; --j) { 
        //倒着循环为了保证b[i-1],b[i]尽量的接近，使得平方数尽量的小
            if (a[i] % j == 0) {
                if ((j & 1) ^ (a[i] / j & 1)) continue; 
                //拆分时奇偶不同直接pass，和与差都不能被2整除当然不行
                b[i] = (j + a[i] / j) >> 1;  //后面的平方和取大的
                b[i - 1] = (a[i] / j - j) >> 1; //前面的平方和取小的
                //倒着循环时也要保证合法性
                if (b[i - 1] <= b[i - 2] || b[i] * b[i] <= a[i]) continue; 
                else {
                    flag = 1; //合法时直接过，防止b[i]变得更大，留给后面的选择就不多了
                    break;
                }
            }
        } 
        if (!flag) {
            puts("No");
            return 0;
        }
    }
    // 处理数据并且输出
    for (int i = 1; i <= n; i += 2) {
        a[i] = b[i] * b[i] - b[i - 1] * b[i - 1]; 
    }
    puts("Yes");
    for (int i = 1; i <= n; ++i) {
        printf((i == 1)? "%lld" : " %lld", a[i]);
    }puts("");
    return 0; //华丽的结束
}
```

### 最优关键思路或技巧
利用完全平方数差的因数分解性质，结合贪心策略，在满足条件的因数对中选择使前缀和最小的组合。这种方法不仅减少了搜索空间，还提高了找到合法序列的可能性。同时，部分题解中使用的二分查找和双指针等技巧，进一步优化了查找满足条件的完全平方数对的过程，提高了算法效率。

### 同类型题或类似算法套路
此类题目通常围绕数论中的完全平方数、因数分解等知识点，结合贪心、枚举等策略。常见套路是根据给定条件建立数学等式，通过分析等式的性质，如因数的奇偶性、大小关系等，来缩小搜索范围，找到满足条件的解。

### 洛谷相似题目
- [P1306 斐波那契公约数](https://www.luogu.com.cn/problem/P1306)：考察数论知识，通过斐波那契数列的性质和最大公约数的计算来解决问题，与本题类似，都需要运用数学原理进行推导和求解。
- [P2398 GCD SUM](https://www.luogu.com.cn/problem/P2398)：涉及数论中的最大公约数和求和问题，需要通过数学方法优化枚举过程，与本题在利用数学知识优化算法方面有相似之处。
- [P2613 【模板】有理数取余](https://www.luogu.com.cn/problem/P2613)：主要考察数论中的逆元等知识，通过数学变换来解决有理数取余问题，同样需要对数学概念有清晰的理解和运用。 

---
处理用时：97.14秒