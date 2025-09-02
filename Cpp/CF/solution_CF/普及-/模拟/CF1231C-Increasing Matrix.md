# Increasing Matrix

## 题目描述

In this problem, a $ n \times m $ rectangular matrix $ a $ is called increasing if, for each row of $ i $ , when go from left to right, the values strictly increase (that is, $ a_{i,1}<a_{i,2}<\dots<a_{i,m} $ ) and for each column $ j $ , when go from top to bottom, the values strictly increase (that is, $ a_{1,j}<a_{2,j}<\dots<a_{n,j} $ ).

In a given matrix of non-negative integers, it is necessary to replace each value of $ 0 $ with some positive integer so that the resulting matrix is increasing and the sum of its elements is maximum, or find that it is impossible.

It is guaranteed that in a given value matrix all values of $ 0 $ are contained only in internal cells (that is, not in the first or last row and not in the first or last column).

## 说明/提示

In the first example, the resulting matrix is as follows:

```
<pre class="verbatim"><br></br>1 3 5 6 7<br></br>3 6 7 8 9<br></br>5 7 8 9 10<br></br>8 9 10 11 12<br></br>
```

In the second example, the value $ 3 $ must be put in the middle cell.

In the third example, the desired resultant matrix does not exist.

## 样例 #1

### 输入

```
4 5
1 3 5 6 7
3 0 7 0 9
5 0 0 0 10
8 9 10 11 12
```

### 输出

```
144
```

## 样例 #2

### 输入

```
3 3
1 2 3
2 0 4
4 5 6
```

### 输出

```
30
```

## 样例 #3

### 输入

```
3 3
1 2 3
3 0 4
4 5 6
```

### 输出

```
-1
```

## 样例 #4

### 输入

```
3 3
1 2 3
2 3 4
3 4 2
```

### 输出

```
-1
```

# 题解

## 作者：neil021110 (赞：2)

若数字为零，要想和最大且满足要求，0为其右侧或下侧数字的最小值-1
```cpp
#include<iostream>
using namespace std;
int main(){
	int n,m;
	cin>>n>>m;
	int a[n][m];//设置矩阵
	int sum=0;//设置和
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			cin>>a[i][j];
		}
	}
	for(int i=n-2;i>0;i--){
		for(int j=m-2;j>0;j--){
			if(a[i][j]==0){//若数字为零，要想和最大且满足要求，0为其右侧或下侧数字的最小值-1
				a[i][j]=min(a[i][j+1],a[i+1][j])-1;
			}	
		}
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			sum+=a[i][j];//最大和累加
			if(i!=n-1&&a[i][j]>=a[i+1][j]){//检查是否符合要求
				cout<<-1;//若不符合，输出-1
				return 0;
			}
			if(j!=m-1&&a[i][j]>=a[i][j+1]){
				cout<<-1;
				return 0;
			}
		}
	}
	cout<<sum;//若符合，输出最大和
}
```


---

## 作者：SH___int (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF1231C)
## 一、题意理解
先来看看这道题让我们干什么。

将矩阵中所有的 $0$ 改为某个整数，使得该 $0$ 所在的行里所有的数为递增的状态，同样的，其所在的列里所有的数也要为递增的状态。如果这个数不存在，输出 $-1$ , 否则，输出整个矩阵中所有（包括改后的）数的和，并使这个和尽量大。
## 二、题目分析
这道题用到了贪心的思想，我们要解决的问题就是：如何使所有数的和尽量大。

我么可以将这个矩阵想象成一个二维平面，要解决这个问题，我们一定要保证改后的数比他上边和左边的数大，比他右边和下边的数小，所以当这个数是它右边和下边的数减 $1$ 时，它就是最大的，这时只需要判断这个数是否比它上边和左边的数大，如果小的话，说明该数不存在，我们就输出 $-1$ , 否则，我们就将它更改，算出整个矩阵的和，这个问题就被我们完美解决啦。
## 三、代码实现
说了这么多，~~好像还是代码最重要~~还是理解最重要哩，让我们把理解融入代码吧。
```
#include<bits/stdc++.h>
using namespace std;
int shu[501][501],ans,n,m;//定义矩阵，答案
int dg(int h,int z)//定义一个递归函数，不断更改0的值
{
	if(shu[h][z]==0)//如果是0
	{
		shu[h][z]=min(dg(h+1,z)-1,dg(h,z+1)-1);//求出它下边与右边的值
		//在函数里就要更改，避免重复计算，不然会超时
		return shu[h][z];//进而求出它的值，并返回
	}
	else
	{
		return shu[h][z];//不用更改，直接返回就好
	}
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin>>shu[i][j];
		}
	}//以上是输入部分
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(shu[i][j]==0)//假如是0
			{
				shu[i][j]=dg(i,j);//更改它的值
			}
			if(shu[i][j]<=shu[i-1][j]||shu[i][j]<=shu[i][j-1])//它最大能达到的值都小于它上边或左边的数
			{
				cout<<"-1";//肯定不满足，直接输出-1
				return 0;//结束程序
			}
			ans+=shu[i][j];//满足就将它加入答案中
		}
	}
	cout<<ans;//完美输出答案
	return 0;
}
```
## 四、题目总结
这道题总的来说比较简单，只要把贪心的部分弄懂，就可以通过啦，如果对这一篇题解有什么意见或建议的话，欢迎评论出来呀，我也会及时改正的QWQ，感谢阅读呀！

---

## 作者：asas111 (赞：0)

## 思路
先找到 $a_{i,j}=0$ 的位置，它的大小取决于 $a_{i+1,j}$ 和 $a_{i,j+1}$ 的大小。因为要使矩阵递增，所以 $a_{i,j}$ 最大可以取 $\min(a_{i+1,j},a_{i,j+1})-1$。不过这道题还有一个坑，要从右下角开始遍历。如果按照正常的方法从左上角开始遍历，$a_{i,j}$ 的右边和下面可能为 $0$，会使 $a_{i,j}=-1$。从右下角开始遍历就没有这种问题。
## 代码
```cpp
#include<bits/stdc++.h>
#define N 509
using namespace std;
int n,m,a[N][N],b=0;
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>a[i][j];
	for(int i=n;i>=1;i--)
		for(int j=m;j>=1;j--)
			if(!a[i][j])a[i][j]=min(a[i+1][j],a[i][j+1])-1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			if(a[i][j]<=a[i-1][j]||a[i][j]<=a[i][j-1]){
				cout<<-1;
				return 0;
			}
			b+=a[i][j];
		}
	cout<<b;
	return 0;
}
```


---

## 作者：Steve_xh (赞：0)

# 题面

[题目传送门](https://www.luogu.com.cn/problem/CF1231C)

**题目大意：**

给定一个 $n\times m$ 的矩阵，问能否在每个 $0$ 的位置更改，使其变成一个每行每列均为递增的矩阵，若能输出最大和，不能则输出 $-1$。

# 思路

每行每列都要从左到右从上到下递增，那么每到一个 $0$ 的位置就能知道若要使这个数最大则肯定是越贴近下一个大数越好。比如：$1,2,0,6$ 这段序列，要使其成为递增序列可以将 $0$ 改成 $3$，$4$ 或 $5$。但要满足和最大的话明显要选最贴近 $6$ 的数 $5$。也就是说若 $a_{i,j}=0$ 那么 $a_{i,j}$ 就要改成 $\min(a_{i+1,j},a_{i,j+1})-1$，最后看看填完的矩阵满不满足递增条件就行啦。

你以为这就结束了？

你的第一反应是不是递增条件判断和完善矩阵时的 $i$ 和 $j$ 都从 $1$ 开始？那就错了。比如我们来看看样例 $1$ 的矩阵，如果我们下标从 $1$ 开始的话就会出现 $0$ 的右边或下面也会是 $0$ 的情况，那这个数就会变成 $-1$ 从而导致答案不正确。正确的做法是完善矩阵时从最右下角开始遍历，这样第一个遇到的 $0$ 的下面和右边一定不是 $0$，而到后面再来找这个 $0$ 的时候这个 $0$ 已经填好数了，因此不会出现上面说的问题。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[555][555],n,m;
void wanshan(){//完善矩阵
//这里从右下角开始也是我卡了好久才发现的
    for(int i=n;i>=1;i--)
        for(int j=m;j>=1;j--)
            if(!a[i][j])
                a[i][j]=min(a[i+1][j],a[i][j+1])-1;//找到最大值的最接近的数填上去
}
int ans(){
    int reans=0;
    for(int j=1;j<=m;j++)
        for(int i=1;i<=n;i++){//判断是否合格顺便加一下
            if(i<n&&a[i+1][j]<=a[i][j]||j<m&&a[i][j+1]<=a[i][j])
                return -1;
            reans+=a[i][j];
        }
    return reans;
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            cin>>a[i][j];
    wanshan();
    cout<<ans();
    return 0;
}
```

---

## 作者：zhang_kevin (赞：0)

# Solution

首先要想到，如果满足递增，就说明：任意一个位置，如果它的右边和下边（如果有的话）一定大于它。

那么，我们填数的时候可以按照这个方法填：枚举 $0$ 的位置，将这个位置填上**右边与下边的最小值减一**。因为，这样可以保证它满足递增，而且是最大的。

但是，还要考虑一个问题：我们填上后，不一定满足条件（左上两个没考虑），因此需要进行二次判断。

最后，注意要逆向遍历，因为顺序遍历会出现右下方向为 $0$ 的情况。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, m, a[1+1*4+514][(1-1)/4+514];
inline int sum(){
	int res = 0;
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) res += a[i][j];
	return res;
}
inline int check(){
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			
			if(
			
			( a[i+1][j] <= a[i][j] && i != n )
			
			||
			
			( a[i][j+1] <= a[i][j] && j != m )
			
			){
				
				return -1;
				
			}
			
		}
	}
	return sum();
}
int main(){
	cin >> n >> m;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			cin >> a[i][j];
		}
	}
	for(int i = n; i >= 1; i--){
		for(int j = m; j >= 1; j--){
			if(!a[i][j]){
				a[i][j] = min(a[i+1][j], a[i][j+1]) - 1;
			} 
		}
	}
	cout << check() << endl;
	return 0;
} 
```


---

## 作者：zzy_zzy (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1231C)
### 题目大意：
给出一个 $n\times{}m$ 的矩阵 $a$，问能否使每一行，每一列均为递增数列（若某一位置上为数字 $0$，则可以将它替换成其它的任意正整数）。

数据范围：$3\le{}n,m\le500$，$0\le{}a_{i,j}\le8\times10^3$。
### 思路：
因为每一行，每一列都要是一个递增数列，所以对于每一个 $a_{i,j}=0$ 时，要满足 $a_{i+1,j}-a_{i-1,j}>1$ 且 $a_{i,j+1}-a_{i,j-1}>1$（请读者自己想想为什么），那么如果满足，$a_{i,j}$ 到底等于几呢？因为是递增序列，所以很容易得出：
```cpp
a[i][j]=min(a[i+1][j],a[i][j+1])-1;
```
最后再检验是否符合递增序列就可以了。

**注意：**
由于如果正向枚举这个矩阵，会出现右边和下面还依然等于 $0$ 的错误，所以应该反向枚举。

**AC Code：**

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[510][510];
int main(){
	int n,m,sum=0;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[i][j];
		}
	}
	for(int i=n;i>=1;i--){
		for(int j=m;j>=1;j--){
			if(a[i][j]==0){
				if(a[i+1][j]-a[i-1][j]>1&&a[i][j+1]-a[i][j-1]>1){	//判断能否有一个正整数插在中间
					a[i][j]=min(a[i+1][j],a[i][j+1])-1;
				}
			}
			if(a[i][j]<=a[i-1][j]||a[i][j]<=a[i][j-1]){	//判断是不是递增序列
				cout<<-1;
				return 0;
			}
			sum+=a[i][j];	//求和
		}
	}
	cout<<sum;
	return 0;
}
```

---

