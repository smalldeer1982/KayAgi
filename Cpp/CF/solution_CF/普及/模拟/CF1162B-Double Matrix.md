# Double Matrix

## 题目描述

【问题描述】

如果矩阵每行从左到右的所有数字严格递增，则称行严格递增，如果从上到下的所有数字都严格递增，则列严格递增。如果所有行和列都严格递增，则称矩阵为递增矩阵。

给出两个包含整数的n×m矩阵A和B，你可以尝交换A_ij和B_ij的值（即交换A、B矩阵同一位置的值）使矩阵A和B变成递增矩阵。

## 样例 #1

### 输入

```
2 2
2 10
11 5
9 4
3 12
```

### 输出

```
Possible
```

## 样例 #2

### 输入

```
2 3
2 4 5
4 5 6
3 6 7
8 10 11
```

### 输出

```
Possible
```

## 样例 #3

### 输入

```
3 2
1 3
2 4
5 10
3 1
3 6
4 8
```

### 输出

```
Impossible
```

# 题解

## 作者：Withershine (赞：4)

[传送门](https://www.luogu.com.cn/problem/CF1162B)

说句实话，如果不是先写了 [Showstopper](https://www.luogu.com.cn/problem/CF1798A) 这道题的话，我应该会在这里卡很久，因为做 Showstopper 我就卡了很久 QwQ。

## 思路
太像了，实在是太像了，与 Showstopper 想比，仅仅就是换成二维数组，求最大值变为找递增矩阵，处理方法一模一样：将数组 $a$ 和 $b$ 中较小的值存在一个数组里，较大的值存在一个数组里就行了。

为什么要这样存呢？举个例子：

当满足 $a_{i,j}<a_{i,j+1}$ 且 $a_{i,j}<b_{i,j+1}$，$a_{i,j+1}>b_{i,j+1}$ 时，此时无论是 $a_{i,j+1}$ 还是 $b_{i,j+1}$ 都会比 $a_{i,j}$ 大，那么将这两个数较小的一个来满足递增，这样对于另外一个数组而言，满足递增的几率才会更大。这里的**几率**如果看不明白，可以自己将位置 $(i,j)$ 所有情况列出来进行比较，不是很多，这里就不一一列出来了。（~~其实主要是懒得写~~）

## 代码
```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#include<string>
#include<ctime>
#include<cstring>
#include<algorithm>
#include<climits>
#include<queue>
#include<map>
#include<set>
#include<sstream>
#include<cassert>
#include<stdio.h>
#define ll long long
#define inf 0x3f3f3f3f
#define fr(i , a , b) for(ll i = a ; i <= b ; ++i)
#define fo(i , a , b) for(ll i = a ; i >= b ; --i)
using namespace std;
inline char gchar()
{
    static char buf[1000000] , *p1 = buf , *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf , 1 , 1000000 , stdin) , p1 == p2) ? EOF : *p1++;
}
inline ll read()
{
    ll x = 0 , f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
	  {
        if(ch == '-')
        {
        	f = -1;
		}
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9')
	  {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}
ll n , m , a[55][55] , b[55][55];
signed main()
{
    n = read();
    m = read();
    fr(i , 1 , n)
    {
        fr(j , 1 , m)
        {
            a[i][j] = read();
        }
    }
    fr(i , 1 , n)
    {
        fr(j , 1 , m)
        {
            b[i][j] = read();
            if(a[i][j] > b[i][j])
            {
                swap(a[i][j] , b[i][j]);
            }
        }
    }
    fr(i , 1 , n)//判断行
    {
        fr(j , 1 , m - 1)
        {
            if(a[i][j] >= a[i][j + 1] || b[i][j] >= b[i][j + 1])
            {
                printf("Impossible");
                system("pause");
                return 0;
            }
        }
    }
    fr(j , 1 , m)//判断列
    {
        fr(i , 1 , n - 1)
        {
            if(a[i][j] >= a[i + 1][j] || b[i][j] >= b[i + 1][j])
            {
                printf("Impossible");
                system("pause");
                return 0;
            }
        }
    }
    printf("Possible");
    system("pause");
    return 0;
}
```


---

## 作者：wangping (赞：1)

题意：给出两个 $n\times m$ 的数组，问通过对应位置互换可以使这两个数组变为行列都从左上角开始严格递增的吗？

思路：可以先将两个数组里面对应位置小的放到第一个数组里面，大的放到第二个数组里面，然后看两个数组是否满足就可以了。

**Code**
```cpp
#include<bits/stdc++.h>
#define _swap(x,y) temp=x, x=y, y=temp
#define in scanf("%d%d", &n, &m);for (register int i = 1; i <= n; ++i)for (register int j = 1; j <= m; ++j)scanf("%d", &a[i][j]);for (register int i = 1; i <= n; ++i)for (register int j = 1; j <= m; ++j)scanf("%d", &b[i][j]);
using namespace std;
int a[55][55], b[55][55], flag, n, m, temp;
int main()
{
	memset(a, 0x3f3f3f, sizeof(a));
	memset(b, 0x3f3f3f, sizeof(b));
	in
	for (register int i = 1; i <= n; ++i)
		for (register int j = 1; j <= m; ++j)
			if (a[i][j] > b[i][j])
				_swap(a[i][j], b[i][j]);
	for (register int i = 1; i <= n; ++i)
		for (register int j = 1; j <= m; ++j)
			if (a[i][j] >= a[i][j + 1] || a[i][j] >= a[i + 1][j]||b[i][j] >= b[i][j + 1] || b[i][j] >= b[i + 1][j])
				flag = 1;
	if (flag == 0)
		printf("Possible\n");
	else
		printf("Impossible\n");
	return 0;
}
```

---

## 作者：_SupremeLiYebin_QwQ_ (赞：1)

这是一篇 python 题解，我大概是首个用 python 的，以此题解纪念我下午的比赛。

如果位置交换了以后还不能与前面的数字构成递增关系，那就直接输出再结束程序，因为一个点错就不能构成严格递减了。

行和列都需要遍历一遍，先判断当前的这个数与前面的数是否构成递增，不行的话就交换一下另一个矩阵的数，如果还不能构成递增就输出。

python 读取遍历都很方便，读入直接 list ，遍历直接 for 循环要遍历的东西。

```python
a=[]
b=[]
n,m=map(int,input().split())
x=0
for i in range(n):
    ai=list(map(int,input().split()))
    a.append(ai)
for i in range(n):
    bi=list(map(int,input().split()))
    b.append(bi)
for i in range(1,n+1):
    for j in range(2,m+1):
        if(a[i][j]<=a[i][j-1] or b[i][j]<=b[i][j-1]):
            c=a[i][j]
            a[i][j]=b[i][j]
            b[i][j]=c
            if a[i][j]<=a[i][j-1] or b[i][j]<=b[i][j-1]: x=1
if(x):
    print("Impossible")
else:
        for i in range(1,n+1):
            for j in range(2,m+1):
                if(a[i][j] >= a[i + 1][j] or b[i][j] >= b[i + 1][j]):
                    c=a[j][i]
                    a[j][i]=b
                    b[j][i]=c
                    if a[i][j]<=a[i][j-1] or b[i][j]<=b[i][j-1]: 
                        x=1
if(x):
    print("Impossible")
else:
    print("Possible")
```

---

## 作者：danb123 (赞：0)

## 题目大意
非常得明白，这道题给定我们两个矩阵，让我们通过交换这两个矩阵相同位置的数据，看能否组成严格递增矩阵。
## 题目分析
是一道模拟题，先输入再模拟。如果位置交换了以后还不能与前面的数字构成递增关系，那就直接输出再结束程序。

当然行和列都需要遍历一遍，先判断当前的这个数与前面的数是否构成递增，不行的话就交换一下另一个矩阵的数，如果还不能构成递增就直接输出。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[105][105],b[105][105],n,m;
int main() {
	cin>>n>>m;
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)
			cin>>a[i][j];
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)
			cin>>b[i][j];
	for(int i=1; i<=n; i++) 
		for(int j=2; j<=m; j++) 
			if(a[i][j]<=a[i][j-1]||b[i][j]<=b[i][j-1]) {
				swap(a[i][j],b[i][j]);
				if(a[i][j]<=a[i][j-1]||b[i][j]<=b[i][j-1]) {cout<<"Impossible";return 0;}
			}
	for(int i=1; i<=m; i++) 
		for(int j=2; j<=n; j++) 
			if(a[j][i]<=a[j-1][i]||b[j][i]<=b[j-1][i]) {
				swap(a[j][i],b[j][i]);
				if(a[j][i]<=a[j-1][i]||b[j][i]<=b[j-1][i]) {cout<<"Impossible";return 0;}
			}
	cout<<"Possible";
	return 0;
}
```

---

## 作者：ZSYZSYZSYZSY (赞：0)

# CF1162B Double Matrix
## Description
给出两个 $n \times m$ 的二维数组，通过对应位置互换可以使这两个数组变为行列都从左上角开始严格递增的的二维数组。

## Solution
我们交换 $a_{i,j}$ 和 $b_{i,j}$ 的值，我们再用 $O(mn)$ 的暴力枚举 $a_{i,j}$ 和 $b_{i,j}$ 的值，如果交换前和交换后，两个数字不能同时满足递增矩阵的性质，那么就一定是不行的。

注意，在讨论交换的时候，该操作一定要操作，因为交换会影响到后面数值的比较。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int a[5005][5005],b[5005][5005];

int main(){
	ll n,m;
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			scanf("%lld",&a[i][j]);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			scanf("%lld",&b[i][j]);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=2;j<=m;j++){
			if(a[i][j]<=a[i][j-1]||b[i][j]<=b[i][j-1]){
				swap(a[i][j],b[i][j]);
				if(a[i][j]<=a[i][j-1]||b[i][j]<=b[i][j-1]){
					printf("Impossible");
					return 0;//直接结束
				}
			}
		}
	}
	for(int i=1;i<=m;i++){
		for(int j=2;j<=n;j++){
			if(a[j][i]<=a[j-1][i]||b[j][i]<=b[j-1][i]){
				swap(a[j][i],b[j][i]);
				if(a[j][i]<=a[j-1][i]||b[j][i]<=b[j-1][i]){
					printf("Impossible");
					return 0;//直接结束
				}
			}
		}
	}
	printf("Possible");
	return 0;
}
```

---

## 作者：Supor__Shoep (赞：0)

一年前做过的这道题，现在才来提交题解……

由于是一年前的思路，所以我容易想到暴力解法。由题意得到，我们只能交换 $a_{i,j}$ 和 $b_{i,j}$ 的值，这是只有两个数的 $O(1)$ 交换操作。那么我们再用 $O(mn)$ 的暴力枚举 $a_{i,j}$ 和 $b_{i,j}$ 的值，如果交换前和交换后，两个数字不能同时满足递增矩阵的性质，那么就一定是不行的。而且我们需要注意，在讨论交换的时候，该操作一定要操作，因为交换会影响到后面数值的比较。

总的来说，这样的方法在这样的数据下是可以过的，时间复杂度 $O(mn)$。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	int a[55][55],b[55][55];
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			scanf("%d",&a[i][j]);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			scanf("%d",&b[i][j]);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=2;j<=m;j++){
			if(a[i][j]<=a[i][j-1]||b[i][j]<=b[i][j-1]){
				swap(a[i][j],b[i][j]);
				if(a[i][j]<=a[i][j-1]||b[i][j]<=b[i][j-1]){
					printf("Impossible");
					return 0;
				}
			}
		}
	}
	for(int j=1;j<=m;j++){
		for(int i=2;i<=n;i++){
			if(a[i][j]<=a[i-1][j]||b[i][j]<=b[i-1][j]){
				swap(a[i][j],b[i][j]);
				if(a[i][j]<=a[i-1][j]||b[i][j]<=b[i-1][j]){
					printf("Impossible");
					return 0;
				}
			}
		}
	}
	printf("Possible");
	return 0;
}
```

---

## 作者：Abeeel51 (赞：0)

#### 题目大意
给出两个二维数组 $A$ 和 $B$ ，可以随意交换两个数组中相同位置的数值，问是否可以将这两个数组变成递增矩阵，可以输出 Possible，不可以输出 Impossible。
#### 解题思路
利用贪心的策略，将 $A_{i,j} , B_{i,j}$ 中小的值放在 $A_{i,j}$，大的值放在 $B_{i,j}$，这样是成为递增矩阵可能性最大的办法。调换后判断是否为递增序列，输出，AC。
#### 参考代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[55][55],b[55][55];
int n,m;
int main(int argc, const char * argv[]) {
    // insert code here...
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) scanf("%d",&a[i][j]);
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) scanf("%d",&b[i][j]);
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) if(a[i][j]>b[i][j]) swap(a[i][j],b[i][j]);
    bool flag=true;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            if(i+1<=n){if(a[i][j]>=a[i+1][j]) flag=false;if(b[i][j]>=b[i+1][j]) flag=false;}
            if(j+1<=m){if(a[i][j]>=a[i][j+1]) flag=false;if(b[i][j]>=b[i][j+1]) flag=false;}
        }
    if(flag){
        cout<<"Possible";
    }else{
        cout<<"Impossible";
    }
    return 0;
}
```


---

## 作者：happybob (赞：0)

传送门：[CF1162B Double Matrix](https://www.luogu.com.cn/problem/CF1162B)

考虑贪心，我们只能交换 $a_{i,j}$ 和 $b_{i,j}$，所以我们考虑将 $a_{i,j}$ 和 $b_{i,j}$ 中小的数放入 $a_{i,j}$，大的数放入 $b_{i,j}$。紧接着判断一次，如果两个矩阵都严格递增，输出 Possible，否则输出 Impossible。

那么有没有证明呢？

如果新的矩阵不满足递增顺序，那么无论如何排序，矩阵仍然无法递增。我们这样考虑：

假设新的矩阵 $a$ 中有一个 $a_{i,j}$ 与 $a_{i, j-1}$ 非递增顺序，那么我们尝试交换 $a_{i,j}$ 与 $b_{i,j}$ 的值。我们以最好的方向考虑，假设 $b_{i,j}>a_{i,j-1}$，那么我们要证明的就是 $a_{i,j} \le b_{i,j-1}$。

首先，在没有交换 $a_{i,j}$ 与 $b_{i,j}$ 的值前，$b_{i,j}$ 与 $b_{i, j-1}$ 有两种可能的关系：

1. 递增，即 $b_{i,j}>b_{i,j-1}$，那么交换后需要满足 $a_{i,j}>b_{i,j-1}$，如果 $a_{i,j}>b_{i,j-1}$，那么显然因为 $b_{i,j-1}>a_{i,j-1}$ 可得 $a_{i,j} \ge a_{i,j-1}$，与一开始的假设矛盾，故交换 $a_{i,j}$ 与 $b_{i,j}$ 的值后矩阵不可能递增。

1. 不递增，即 $b_{i,j} \le b_{i,j-1}$，那么又因为 $a_{i,j} \le b_{i,j}$，显然 $a_{i,j} \le b_{i, j-1}$，故不行。

综上得证。

纵向的推导过程也是这样。

代码：

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;

const int N = 55;
int a[N][N], b[N][N], n, m;

int main()
{
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++) scanf("%d", &a[i][j]);
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			scanf("%d", &b[i][j]);
			if (b[i][j] < a[i][j]) swap(a[i][j], b[i][j]);
		}
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			if (a[i][j] <= a[i][j - 1] || a[i][j] <= a[i - 1][j] || b[i][j] <= b[i][j - 1] || b[i][j] <= b[i - 1][j])
			{
				puts("Impossible");
				goto End;
			}
		}
	}
	puts("Possible");
	End:
	return 0;
}
```



---

## 作者：Goodrage (赞：0)

贪心。

#### 思路分析

贪心策略：将两个矩阵里每个对应元素互相比较，较大的放进一个矩阵里，较小的放进另一个里，如果能拼出两个递增矩阵就可以，否则不可以。

因为它说严格递增，后面的一定要盖过前面的，尽量用小数盖过小的数，用大数盖过大的数，以免防止浪费。

如果小数不能放进小矩阵，则它一定也不能放进大矩阵；如果大的都不能放进大矩阵，小的也一定不能放进大矩阵。而最终是要两个矩阵都成为递增矩阵，必须两个都能放进去才可以继续。

#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[53][53],b[53][53];
int tmp1[53][53],tmp2[53][53];//tmp1表示小数，tmp2表示大数
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
			scanf("%d",&a[i][j]);
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
			scanf("%d",&b[i][j]);
	}
	tmp1[1][1]=min(a[1][1],b[1][1]);
	tmp2[1][1]=max(a[1][1],b[1][1]);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			tmp1[i][j]=min(a[i][j],b[i][j]);//小
			tmp2[i][j]=max(a[i][j],b[i][j]);//大
			if(tmp1[i][j]<=tmp1[i-1][j]||tmp1[i][j]<=tmp1[i][j-1])//小的不符合，那么小的放进大的里也不能符合。
			{
				printf("Impossible");
				exit(0);//直接结束
			}
			if(tmp2[i][j]<=tmp2[i-1][j]||tmp2[i][j]<=tmp2[i][j-1])//大的不符合，小的也不能放进大矩阵
			{
				printf("Impossible");
				exit(0);//直接结束
			}
		}
	}
	printf("Possible");能做出两个递增矩阵
	return 0;
}
```

~~良怒最近爆发段了吗，一连写了这么多题解~~

---

## 作者：LOVE_Ynoi (赞：0)

# CF1162B题解
### 传送门： [题目](https://www.luogu.com.cn/problem/CF1162B)
这道题的正解就是将小的放在矩阵 $A$ 中，将大的放在矩阵 $B$ 中。  
如果这样还不满足定义，就一定不可能。  

证明~~(不是严格的数学证明)~~：  
我们可以知道，我们所选的矩阵元素只有两个，**大元素**和**小元素**，  
显然，第一个放大的和放小的对答案没有有影响。   
之后，如果把大的元素放到了小的元素的右边或下边，  
那么另一个矩阵所对应的大的元素的下边或右边就会被填入小元素，容易不满足递增矩阵的定义，  
同时，第一个矩阵需要的满足递增矩阵定义的下一个元素又会变得更大， 
这样答案就不是最优的了。  
所以，对于矩阵中所有元素来说，要么都大，要么都小，这样才能使答案最优。



代码：
```c++
#include<bits/stdc++.h>
using namespace std;
int n,m;
int a[100][100];
int b[100][100];
int main(){
    cin>>n>>m;
    for(int i = 1;i<=n;i++){
        for(int j = 1;j<=m;j++){
            cin>>a[i][j];
        }
    }
    for(int i = 1;i<=n;i++){
        for(int j = 1;j<=m;j++){
            cin>>b[i][j];
        }
    }
    for(int i = 1;i<=n;i++){
        for(int j = 1;j<=m;j++){
            if(a[i][j]<b[i][j]) swap(a[i][j],b[i][j]);
        }
    }
    for(int i = 1;i<=n;i++){
        for(int j = 1;j<=m;j++){
            if(a[i][j]<=a[i][j-1]||b[i][j]<=b[i][j-1]){
                cout<<"Impossible"<<endl;
                exit(0);
            }
        }
    }
    for(int i = 1;i<=m;i++){
        for(int j = 1;j<=n;j++){
            if(a[j][i]<=a[j-1][i]||b[j][i]<=b[j-1][i]){
                cout<<"Impossible"<<endl;
                exit(0);
            }
        }
    }
    cout<<"Possible"<<endl;
    return 0;
}
```

---

