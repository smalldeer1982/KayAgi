# Squares

## 题目描述

Vasya has found a piece of paper with a coordinate system written on it. There are $ n $ distinct squares drawn in this coordinate system. Let's number the squares with integers from 1 to $ n $ . It turned out that points with coordinates $ (0,0) $ and $ (a_{i},a_{i}) $ are the opposite corners of the $ i $ -th square.

Vasya wants to find such integer point (with integer coordinates) of the plane, that belongs to exactly $ k $ drawn squares. We'll say that a point belongs to a square, if the point is located either inside the square, or on its boundary.

Help Vasya find a point that would meet the described limits.

## 样例 #1

### 输入

```
4 3
5 1 3 4
```

### 输出

```
2 1
```

## 样例 #2

### 输入

```
3 1
2 4 1
```

### 输出

```
4 0
```

## 样例 #3

### 输入

```
4 50
5 1 10 2
```

### 输出

```
-1
```

# 题解

## 作者：codemap (赞：2)

~~这竟然还是橙题?!!~~

有k个包含这个点的正方形相当于最大的k的正方形包含这个点

只要输出第k大的正方形的顶点就可以了

~~水到爆炸~~

不说了上代码
```c
#include<iostream>
#include<algorithm>
using namespace std;
int main()
{
    int n,k,a[51],i;
    cin>>n>>k;
    for(i=1;i<=n;i++)
        cin>>a[i];
    sort(a+1,a+n+1);//排序
    if(n<k)//如果没有k个正方形
    {
        cout<<-1;
        return 0;
    }
    cout<<a[n-k+1]<<" "<<a[n-k+1];//直接输出第k大的正方形的顶点，注意这里是n-k+1
    return 0;//完美结束
}
```

---

## 作者：Eason_AC (赞：1)

## Content
有 $n$ 个边长为 $a_i$ 的正方形，第 $i$ 个正方形的四个顶点分别是 $(0,0),(0,a_i),(a_i,0),(a_i,a_i)$，我们定义一个点属于一个正方形当且仅当这个点完全在正方形内或者在正方形的边界上。试找到一个属于 $k$ 个正方形的点，或者这样的点不存在。

**数据范围：$1\leqslant n,k\leqslant 50,1\leqslant a_i\leqslant 10^9$。**
## Solution
我们先按边长由小到大给这些正方形排序，然后由于在正方形边界上也算属于这个正方形，那么答案就可以是第 $n-k+1$ 大的正方形的右下顶点，直接输出就好。
## Code
```cpp
int n, k, a[57];

int main() {
	getint(n), getint(k);
	_for(i, 1, n)	getint(a[i]);
	if(k > n)	return printf("-1"), 0;
	sort(a + 1, a + n + 1);
	printf("%d 0", a[n - k + 1]);
	return 0;
}
```

---

## 作者：zyc8421 (赞：1)

## 题意

有$n$个边长为$a_i$的正方形，题目规定：如果某点位于某个正方形**内部**或其**边界**上，就称这个点属于这个正方形。

现规定一个$k$，判断是否能找到一个点$(x,y)$，恰好属于$k$个正方形。

如果找到，则输出一组可行解$(x,y)$即可，两数用空格隔开；如果无解，输出$-1$。

## 思路

1. 我们先把数组$a$**从大到小**排序一遍，以方便接下来的操作。

2. 在输出答案之前，我们再判断$k$是否**大于**$n$，如果大于，输出$-1$；因为要求正方形数量$k$**不可能大于**总数量$n$。 

3. 最后，我们在输出数组$a$中第$k$个正方形的右上角顶点坐标（重复两次它的边长即可）

4. 其实说白了，这道题就是寻找数组$a$中的**第$k$大**的数输出**两遍**。

## 代码

```cpp
#include<stdio.h>
using namespace std;
const int MAXN=60; //数组最大范围
void swap(int &a,int &b) //swap函数：交换两个整型变量的数值 
{
	int temp=a;
	a=b;
	b=temp;
} 
int main()
{
	int n,k,a[MAXN]={0}; //定义变量
	scanf("%d%d",&n,&k); //输入n,k
	for(int i=0;i<n;i++)
	{
		scanf("%d",&a[i]); //输入数组a的第i个元素
		for(int j=i;j>0;j--) //从大到小排序 
		{
			if(a[j]>a[j-1]) //判断后面的数值是否大于前面的数值 
			{
				swap(a[j],a[j-1]); //是则交换两数数值 
			}
		} 
	}
	if(k>n) //如果要求正方形数量大于总数量 
	{
		printf("-1"); //无解
		return 0; 
	} 
	printf("%d %d",a[k-1],a[k-1]); //输出第k-1个正方形（从大到小）右上角顶点坐标 
	return 0; 
} 
```


---

## 作者：Allanljx (赞：0)

## 题意
有 $n$ 个边长为 $a[i]$ 的正方形。题目规定：如果某点位于某个正方形内部或其边界上，就称这个点属于这个正方形。现规定一个 $k$，判断是否能找到一个点 $(x,y)$，恰好属于 $k$ 个正方形。如果找到，则输出一组可行解 $(x,y)$ 即可，两数用空格隔开；如果无解，输出 $-1$。

## 思路
因为每个正方形左下角都是固定的，所以如果这个点在一个面积较小的正方形中，那这个点一定在比他面积大的正方形中。所以，如果要让这个点位于恰好 $k$ 个正方形以内，他就可以在第 $n-k$ 小和第 $n-k+1$ 小之间。所以，我们就可以在排序后输出 $a[n-k+1]$。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[55];
int main()
{
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	sort(a+1,a+n+1);//排序
	if(k>n) cout<<-1;//不成立
	else cout<<a[n-k+1]<<' '<<a[n-k+1];
	return 0;
}
```


---

## 作者：xgwpp6710 (赞：0)

水题一道。

显然当 $k$ 大于 $n$ 的时候，无法使一个点在正方形内，因此输出 $-1$ 即可。

当 $k$ 小于等于 $n$ 的时候，因为显然大的正方形包含了小的正方形，因此让点在第 $k$ 大的正方形内，且不在第 $k-1$ 大的正方形内即可。因此可以输出第 $k$ 大的正方形的顶点坐标。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,a[55],k;
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1);//把正方形按边长排序
	if(n<k) cout<<"-1";//这步其实放在输入n和k之后更好，但是放这里也行，因为n比较小
	else cout<<a[n-k+1]<<" "<<a[n-k+1];//第k大的正方形顶点坐标
	return 0;
}
```

---

## 作者：Snow_Dreams (赞：0)



~~这好像是我第一次用LaTeX写题解~~

不难发现，**当且仅当**$k > n$时才会输出$-1$

接着发现$x[i],y[i] > 0$

所以就只用考虑第一象限

有$k$个包含这个点的正方形相当于最大的$k$的正方形包含这个点

接着我们输出这个点即可

不难找到最大的$k$个正方形的顶点符合要求

所以我们使用STL的$sort$即可

最后输出$a[n-k+1]$

---

