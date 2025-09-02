# 4-point polyline

## 题目描述

You are given a rectangular grid of lattice points from $ (0,0) $ to $ (n,m) $ inclusive. You have to choose exactly 4 different points to build a polyline possibly with self-intersections and self-touching. This polyline should be as long as possible.

A polyline defined by points $ p_{1},p_{2},p_{3},p_{4} $ consists of the line segments $ p_{1}p_{2},p_{2}p_{3},p_{3}p_{4} $ , and its length is the sum of the lengths of the individual line segments.

## 样例 #1

### 输入

```
1 1
```

### 输出

```
1 1
0 0
1 0
0 1
```

## 样例 #2

### 输入

```
0 10
```

### 输出

```
0 1
0 10
0 0
0 9
```

# 题解

## 作者：N_z_ (赞：2)

## 思路
对于给出的$n$和$m$，设$n$较短，如果：
* 其中有$0$，那么我们取$(0,1)\ (0,m)\ (0,0)\ (0,m-1)$
* 不然，我们有两种取法：
	* $(1,0)\ (n,m)\ (0,0)\ (n-1,m)$
   * $(0,0)\ (n,m)\ (n,0)\ (0,m)$
   * 判断大小即可。
   
如果$m$较短，则上述所有坐标横纵交换并用$m$代替$n$，用$n$代替$m$即可。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n,m;
    cin>>n>>m;
    if(min(n,m)==0)
    if(m>n)cout<<"0 1\n0 "<<m<<"\n0 0\n0 "<<m-1<<endl;
    else cout<<"1 0\n"<<n<<" 0\n0 0\n"<<n-1<<" 0"<<endl;
    else if(2*sqrt((min(n,m)-1)*(min(n,m)-1)+max(n,m)*max(n,m))>max(n,m)+sqrt(min(n,m)*min(n,m)+max(n,m)*max(n,m)))
    if(m>n)cout<<"1 0\n"<<n<<" "<<m<<"\n0 0\n"<<n-1<<" "<<m<<endl;
    else cout<<"0 1\n"<<n<<" "<<m<<"\n0 0\n"<<n<<" "<<m-1<<endl;
    else if(m>n) cout<<"0 0\n"<<n<<" "<<m<<endl<<n<<" 0\n0 "<<m<<endl;
    else cout<<"0 0\n"<<n<<" "<<m<<"\n0 "<<m<<endl<<n<<" 0"<<endl;
}
```

---

## 作者：luuia (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/CF452B)

## 题意
有一个 $(0,0)$ 到 $(n,m)$ 的矩形网格点。在网格点上选择 $4$ 个不同的点，按顺序连接各点形成折线，使得折线长最大，输出 $4$ 个点。

## 分析

分 $2$ 种情况讨论：

- $n = 0$ 或 $m = 0$

这个时候$4$个点都在坐标轴上，不妨假设在$x$轴上，那么选出的最佳的$4$个点的$x$坐标即为$0,1,m-1,m$，以如下顺序排列：$1,m,0,m-1$，可以使得距离最大。

- $n \neq 0 $ 且 $m \neq 0$

由对称性，我们把 $n$ 作为 $n$，$m$ 中小的一个，$m$ 作为大的一个。

我们可以取矩形的一条对角线和剩余的两个顶点，或者取如下的 $4$ 个点：

$(n - 1,m)$，$(0,0)$，$(n,m)$，$(1,0)$

这 $4$ 条线段是其中跨度最大的线段，是折线最长的 $4$ 个点。就像下图

![图1](https://cdn.luogu.com.cn/upload/image_hosting/ecwskixz.png)


或者取矩形的一条对角线和两条边，即取$BD$，$DC$，$AC$

![图2](https://cdn.luogu.com.cn/upload/image_hosting/iicrbvz2.png)

比较两种情况，取最大值即可。

第一种情况：取矩形的一条对角线和剩余的两个顶点，计算出答案为：

$$ m + 2 \times \sqrt{n ^ 2 + m ^ 2}$$

第二种情况，取 $(n - 1,m)$，$(0,0)$，$(n,m)$，$(1,0)$，计算出答案为：

$$2 \times \sqrt{{(n - 1)} ^ 2 + m ^ 2}+ \sqrt{n ^ 2 + m ^ 2}$$

比较两个的大小即可。

## 代码

下面是 AC 代码，按照以上思路模拟即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
 
int main()
{
    int n,m;
    double a1,a2;
    cin >> n >> m;
    if(n == 0)
    {
    	cout << "0 1" << endl;
    	cout << "0 " << m << endl;
    	cout << "0 0" << endl;
    	cout << "0 " << m - 1 << endl;
    	return 0;
	}
	else if(m == 0)
	{
		cout << "1 0" << endl;
    	cout << m << " 0" << endl;
    	cout << "0 0" << endl;
    	cout << m - 1 << " 0" << endl;
    	return 0;
	}
    int p = max(n,m);
    n = min(n,m);
    m = p;
	a1 = m + sqrt(n * n + m * m) + sqrt(n * n + m * m);
    a2 = sqrt((n - 1) * (n - 1) + m * m) + sqrt((n - 1) * (n - 1) + m * m) + sqrt(n * n + m * m);
	if(a1 > a2)
    {
    	cout << "0 0" << endl;
    	cout << n << " " << m << endl;
    	cout << n << " 0" << endl;
    	cout << "0 " << m << endl;
	}
	else
	{
		cout << n - 1 << " " << m << endl;
		cout << "0 0" << endl;
		cout << n << " " << m << endl;
		cout << "1 0" << endl;
	}
	return 0;
}
```


---

