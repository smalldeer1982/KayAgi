# [入门赛 #14] Three-View Projection (Hard Version)

## 题目描述

> 全文与 $x, y, z$ 轴/方向有关的内容均基于以下的 $x, y, z$ 轴、位置及观测方向。观测者站在如图所示的位置，正在向着 $y$ 轴（绿线）正方向（箭头方向）观测。  
> ![](https://cdn.luogu.com.cn/upload/image_hosting/05erek0j.png)

现在有一个长、宽、高（沿 $x, y, z$ 轴延展的长度）为 $n \text{ cm}, m \text{ cm}, k \text{ cm}$ 的长方体区域。我们将这片区域划分为 $n \times m \times k$ 个小格子。每个小格子中可以放置一个边长为 $1 \text{ cm}$ 的小正方体。

我们使用一个整数三元组 $(x, y, z)$ 来表示一个格子在空间中的位置，其代表从左往右数第 $x$ 个，从前往后数第 $y$ 个，从下往上第 $z$ 个格子。

![](https://cdn.luogu.com.cn/upload/image_hosting/0yu909tc.png)

例如，上图展示的 $3 \times 3 \times 3$ 区域中，按照观测者的位置，可以发现红蓝线（$x, z$ 轴）所在的面为前面，蓝绿线（$y, z$ 轴）所在的面为左面，红绿线（$x, y$ 轴）所在的面为下面，五个小正方体的位置分别为 $(1, 1, 1), (1, 1, 2), (2, 3, 2), (3, 3, 2), (2, 2, 3)$。

三视图是观测者从上面（从上往下）、左面（从左往右）、正面（从前往后）三个不同角度观察同一个空间几何体而画出的图形。

![](https://cdn.luogu.com.cn/upload/image_hosting/p72x1i3q.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/6ucamb9o.png)

例如，以上是示例区域的三视图。

现在，给定一个区域及其中的正方体排布情况，请你帮助计算出这个区域的三视图。

## 说明/提示

### 样例 1 解释

样例 1 即为题目中的示例。

![](https://cdn.luogu.com.cn/upload/image_hosting/ho4l901w.png)

### 数据规模与约定

对于 $100\%$ 的数据，保证 $1 \leq n, m, k \leq 200$，$0 \leq a _ {x, y, z} \leq 1$。

## 样例 #1

### 输入

```
3 3 3
1 0 0
0 0 0
0 0 0
1 0 0
0 0 1
0 0 1
0 0 0
0 1 0
0 0 0```

### 输出

```
0 1 0
1 1 1
1 0 0
0 1 0
1 0 1
0 0 1
0 1 1
0 1 0
1 0 0```

## 样例 #2

### 输入

```
4 6 3
0 0 0 0 0 1
0 0 0 0 0 1
0 0 1 0 0 0
0 0 0 0 0 0
0 1 0 0 0 0
0 0 1 0 0 1
0 0 0 0 0 0
1 0 0 0 0 1
0 0 0 0 0 0
0 1 0 0 1 0
0 0 0 0 0 1
1 0 0 0 0 1```

### 输出

```
0 1 1 1
1 1 0 1
1 1 1 0
1 1 0 0 1 1
1 0 0 1 1 1
1 0 0 1 0 0
1 1 1 1
0 1 0 0
0 0 0 0
0 1 1 0
1 1 0 0
0 0 0 1```

# 题解

## 作者：maomao233 (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/P9456)

[Easy Version 传送门](https://www.luogu.com.cn/problem/B3809)

~~感觉这题评黄有些过分，应该是中位橙的难度，但真的很烧脑干~~

### 分析

~~本题难点在于特别特别为复杂的坐标转换。~~

首先是读入，大致有两种读入方法。第一种是按题面的输入，题面写的是输入的 $a_{x,y,z}$ 表示的是格子 $(y,z,x)$，所以若三重循环的变量分别为 $i,j,l$，则应该读入 $a_{j,l,i}$；第二种就是直接输入 $a_{i,j,l}$。其实本质没有什么区别，本篇题解就以第一种输入为例：

```cpp
int n,m,k;
	cin>>n>>m>>k;
	for(int i=1;i<=k;i++)
	{
		for(int j=1;j<=n;j++)
		{
			for(int l=1;l<=m;l++)
			{
				cin>>a[j][l][i];
			}
		}
	}
```

然后我们再沿三种视图来讲解：

### 正视图

正视图要求**自上而下自左至右**。因此我们首先需要**倒序**枚举 $z$ 轴（即变量 $k$，代表长方体的高），其次**正序**枚举 $x$ 轴（即变量 $n$，代表长方体的长），最后再是**正序往后**找 $m$ 个（即长方体的宽）小正方体即可。在枚举中，输出每一格的情况即可。

正视图部分代码：

```cpp
for(int i=k;i;i--)
	{
		for(int j=1;j<=n;j++)
		{
			int flag=0;
			for(int l=1;l<=m;l++)
			{
				if(a[j][l][i])
				{
					flag=1;
					break;
				}
			}
			cout<<flag<<" ";
		}
		putchar('\n');
	}
```

### 左视图

左视图要求**自上而下自后至前**。因此我们首先需要**倒序**枚举 $z$ 轴（即变量 $k$，代表长方体的高），其次**倒序**枚举 $y$ 轴（即变量 $m$，代表长方体的宽），最后再是**正序往右**找 $n$ 个（即长方体的长）小正方体即可。在枚举中，输出每一格的情况即可。

但是这里还需注意，这里不应该再是 $a_{j,l,i}$ 了，因为循环变量本身就“代表”了其第一次所对应的标准变量，比如 $i$ 对应 $k$，那么这次它也就“代表” $k$。所以按此规律，原本变量为 $n,m,k$，现在对应一下，这里应该为 $a_{l,j,i}$。（因为在这里 $i$ 代表 $k$，$j$ 代表 $m$，$l$ 代表 $n$，标准顺序是 $n,m,k$，所以循环变量应该排序成 $l,j,i$。）

这个规律通用于三个俯视图。当然，你也可以称其为小技巧。

左视图部分代码：

```cpp
for(int i=k;i;i--)
	{
		for(int j=m;j;j--)
		{
			int flag=0;
			for(int l=1;l<=n;l++)
			{
				if(a[l][j][i])
				{
					flag=1;
					break;
				}
			}
			cout<<flag<<" ";
		}
		putchar('\n');
	}
```

### 俯视图

俯视图要求**自后至前自左至右**。因此我们首先需要**倒序**枚举 $y$ 轴（即变量 $m$，代表长方体的宽），其次**正序**枚举 $x$ 轴（即变量 $n$，代表长方体的长），最后再是**正序往下**找 $k$ 个（即长方体的高）小正方体即可。在枚举中，输出每一格的情况即可。

这里循环变量也需对应，按“左视图”里的方法对应后，此处应为 $a_{j,i,l}$。

俯视图部分代码：

```cpp
for(int i=m;i;i--)
	{
		for(int j=1;j<=n;j++)
		{
			int flag=0;
			for(int l=1;l<=k;l++)
			{
				if(a[j][i][l])
				{
					flag=1;
					break;
				}
			}
			cout<<flag<<" ";
		}
		putchar('\n');
	}
```

完整代码就不给了，组合一下四段代码就是。

最后再说一个小技巧吧。下次遇到这种题目，各位如果实在不知道或想不出来要不要倒序或怎么将循环变量对应，就可以尝试枚举所有种情况。枚举这 $i,j,l$，一共也就 $2\times3=6$ 种可能。再加上倒序，一共也就 $12$ 种可能，依次尝试即可。虽然说这有点类似于骗分，~~但至少可以 AC，赛时我就是这样 AC 的。~~

---

## 作者：AlexandreLea (赞：3)

提供一种~~奇奇怪怪~~的解法。

首先，我们知道，输入给出了一些立体图形的“切片”，从下向上摞切片就可以得到整个立方体。因此，我们将这些切片从上向下摞以方便输出。

那么，读入就类似这样：

```cpp
for(int x=k;x>=1;x--)
    for(int y=1;<=n;y++)
        for(int z=1;z<=m;z++) cin>>v[x][y][z];
```

然后，~~根据常识~~，当我们从某个方向看一个物体的时候，只要眼睛射出的光芒碰到了一个立方体，那么就将这个方块并标注在视图上。因此，向某个方向寻找方块并输出的代码如下：

```cpp
bool c=false;
for(int ...=1;...<=...;...++) c|=v[...][...][...];
cout<<c<<" ";
```

然而我们的推理似乎就此走进了死路。然而，我们有一个东西：样例。将样例重新**狠狠地切割**并将各个片从上向下组合，就得到

```plaintext
0 0 0 0 0 0 => 0
0 1 0 0 1 0 => 1
0 0 0 0 0 1 => 1
1 0 0 0 0 1 => 1

0 1 0 0 0 0 => 1
0 0 1 0 0 1 => 1
0 0 0 0 0 0 => 0
1 0 0 0 0 1 => 1

0 0 0 0 0 1 => 1
0 0 0 0 0 1 => 1
0 0 1 0 0 0 => 1
0 0 0 0 0 0 => 0
```

它们分别对应正视图中的三行：

```plaintext
0 1 1 1
1 1 0 1
1 1 1 0
```

那么，将最上边的一片从左向右射出目光，我们就能得到第一行。类似地，我们就能依次得到第二三行。

于是，我们就得到了输出正视图的解法：

```cpp
for(int x=1;x<=k;x++){
    for(int y=1;y<=n;y++){
        bool c=false;
        for(int z=1;z<=m;z++) c|=v[x][y][z];
        cout<<c<<" ";
    }
    cout<<endl;
}
```

~~类似地~~，我们便得到了三视图的代码。这里就不说了吧。

**EOF**

---

## 作者：arrow_king (赞：2)

# [P9456](https://www.luogu.com.cn/problem/P9456) 题解

## 输入

>输入共 $n \times k + 1$ 行。
>
>第一行为三个整数 $n, m, k$，代表长方形区域的长、宽、高。  \
>接下来 $n \times k$ 行，每行 $m$ 个整数。其中，将其每 $n$ 行分为一组，第 $x$ 组第 $y$ 行（即第 $(x - 1) \times n + y$ 行）第 $z$ 列的整数 $a _ {x, y, z}$ 代表 $(y, z, x)$ 处格子的情况，若 $a _ {x, y, z} = 1$，代表该格子有小正方体；否则，代表该格子没有小正方体。

发现输入并不是常见的方式。

首先你要枚举 $k$ 这一维度。接下来枚举 $n$ 和 $m$ 维（这一部分就是普通的二维数组），开一个三维数组 $a_{n,m,k}$，$a_{x,y,z}$ 表示坐标 $(x,y,z)$ 有无正方体。

```cpp
n=read(),m=read(),q=read();		//read()是快读
for(int k=1;k<=q;k++) {			//因为循环变量用了k，所以我将原来的k改为了q
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=m;j++) {
			a[i][j][k]=read();
		}
	}
}
```

## 三视图处理

首先，三视图可以看做把原来的三维空间沿某个坐标轴“压扁”成一个平面。那么对于压扁成的平面上的一点，若它上面的空间里有立方体，那么这个点就可以标为 $1$。

那么可以先枚举 $n,m,k$ 中的两维，然后再枚举第三维，若第三维上的某个点是 $1$，那么三视图就是 $1$。

```cpp
for(int k=1;k<=q;k++) for(int j=1;j<=m;j++) {
	for(int i=1;i<=n;i++) vision[0][k][j]|=a[i][j][k];
}
for(int k=1;k<=q;k++) for(int i=1;i<=n;i++) {
	for(int j=1;j<=m;j++) vision[1][k][i]|=a[i][j][k];
}
for(int j=1;j<=m;j++) for(int i=1;i<=n;i++) {
	for(int k=1;k<=q;k++) vision[2][j][i]|=a[i][j][k];
}
```

## 输出

难点在于不确定先输出的是 $vision$ 中的哪一个，以及输出时的方向。

这个简单，先随意输出一次，然后对着输出和样例来调试输出顺序就可以了。

```cpp
for(int k=1;k<=q;k++) {
	for(int i=1;i<=n;i++) printf("%d ",vision[1][q-k+1][i]);
	putchar('\n');
}
for(int k=1;k<=q;k++) {
	for(int j=1;j<=m;j++) printf("%d ",vision[0][q-k+1][m-j+1]);
	putchar('\n');
for(int j=1;j<=m;j++) {
	for(int i=1;i<=n;i++) printf("%d ",vision[2][m-j+1][i]);
	putchar('\n');
}
```

# 完整代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
#define ll long long
#define il inline
#define N 205
il ll read() {
	ll x=0,f=1;char c=getchar();
	while(c<'0'||c>'9') {if(c=='-') {f=-1;} c=getchar();}
	while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
int n,m,q;
int a[N][N][N];
int vision[3][N][N];
int main() {
	n=read(),m=read(),q=read();
	for(int k=1;k<=q;k++) {
		for(int i=1;i<=n;i++) {
			for(int j=1;j<=m;j++) {
				a[i][j][k]=read();
			}
		}
	}
	for(int k=1;k<=q;k++) for(int j=1;j<=m;j++) {
		for(int i=1;i<=n;i++) vision[0][k][j]|=a[i][j][k];
	}
	for(int k=1;k<=q;k++) for(int i=1;i<=n;i++) {
		for(int j=1;j<=m;j++) vision[1][k][i]|=a[i][j][k];
	}
	for(int j=1;j<=m;j++) for(int i=1;i<=n;i++) {
		for(int k=1;k<=q;k++) vision[2][j][i]|=a[i][j][k];
	}
	for(int k=1;k<=q;k++) {
		for(int i=1;i<=n;i++) printf("%d ",vision[1][q-k+1][i]);
		putchar('\n');
	}
	for(int k=1;k<=q;k++) {
		for(int j=1;j<=m;j++) printf("%d ",vision[0][q-k+1][m-j+1]);
		putchar('\n');
	}
	for(int j=1;j<=m;j++) {
		for(int i=1;i<=n;i++) printf("%d ",vision[2][m-j+1][i]);
		putchar('\n');
	}
	return 0;
}

```

---

## 作者：_O_v_O_ (赞：1)

大模拟，比较简单。

我们可以用一个**三维数组**来记录这个区域，有方块则记录成 $1$，否则记录为 $0$。

接下来就是三视图了：

每种视图其实都可以枚举能看到的方块，有则输出 $1$，否则输出 $0$。

不过枚举轴需要有方式，下面是枚举方式（下面 $x$ 代表横向坐标，$y$ 代表纵向坐标，$z$ 代表高度。）：

1. 正视图：先逆向枚举 $z$ 坐标，再正向枚举 $x$ 坐标，最后正向枚举 $y$ 坐标。
2. 左视图：先逆向枚举 $z$ 坐标，再逆向枚举 $y$ 坐标，最后正向枚举 $x$ 坐标。
3. 俯视图：先逆向枚举 $y$ 坐标，再正向枚举 $x$ 坐标，最后正向枚举 $z$ 坐标。

其实你如果推导不出来的话，可以枚举。

代码：

```
#include<bits/stdc++.h>
using namespace std;

int n,m,k;
int a[505][505][505];

signed main(){
	cin>>n>>m>>k;
	for(int i=1;i<=k;i++){
		for(int j=1;j<=n;j++){
			for(int kk=1;kk<=m;kk++){
				cin>>a[i][j][kk];
			}
		}
	}
	for(int i=k;i>=1;i--){
		for(int j=1;j<=n;j++){
			bool b=false;
			for(int kk=1;kk<=m;kk++){
				if(a[i][j][kk]==1){
					b=true;
					break;
				}
			}
			cout<<b<<' ';
		}
		puts("");  //因为 puts 自带换行，所以只用 puts 空串就能换行。
	}
	for(int i=k;i>=1;i--){
		for(int j=m;j>=1;j--){
			bool b=false;
			for(int kk=1;kk<=n;kk++){
				if(a[i][kk][j]==1){
					b=true;
					break;
				}
			}
			cout<<b<<' ';
		}
		puts("");
	}
	for(int i=m;i>=1;i--){
		for(int j=1;j<=n;j++){
			bool b=false;
			for(int kk=1;kk<=k;kk++){
				if(a[kk][j][i]==1){
					b=true;
					break;
				}
			}
			cout<<b<<' ';
		}
		puts("");
	}
	return 0;
}
```


---

## 作者：MornStar (赞：0)

# [入门赛 #14] Three-View Projection (Hard Version) 题解
## 题面
[link](https://www.luogu.com.cn/problem/P9456)
## 思路
大膜你，只是输入有点坑。

先对照下面这张图来判断怎么输出。

![](https://cdn.luogu.com.cn/upload/image_hosting/42gu8v4p.png)

正视图对应过来应该是 $Z$ 轴从大到小枚举，$X$ 轴从小到大枚举，对于每个点，枚举 $Y$ 轴上是否存在方块。

另外两个视图同理。

注意：输入时循环顺序为 $k,n,m$。

## code

```cpp
//by MornStar
#include<bits/stdc++.h>
using namespace std;
//以下read与write函数为快读快写
long long n,m,k;
bool f[205][205][205];
int main(){
	n=read(),m=read(),k=read();
	for(int x=1;x<=k;x++){
		for(int y=1;y<=n;y++){
			for(int z=1;z<=m;z++){
				f[y][z][x]=read();
			}
		}
	}
	for(int z=k;z>=1;z--){
		for(int x=1;x<=n;x++){
			bool flag=0;
			for(int y=1;y<=m;y++){
				if(f[x][y][z]){
					flag=1;
					break;
				}
			}
			write(flag,' ');
		}
		putchar('\n');
	}//正视图
	for(int z=k;z>=1;z--){
		for(int y=m;y>=1;y--){
			bool flag=0;
			for(int x=1;x<=n;x++){
				if(f[x][y][z]){
					flag=1;
					break;
				}
			}
			write(flag,' ');
		}
		putchar('\n');
	}//左视图
	for(int y=m;y>=1;y--){
		for(int x=1;x<=n;x++){
			bool flag=0;
			for(int z=1;z<=k;z++){
				if(f[x][y][z]){
					flag=1;
					break;
				}
			}
			write(flag,' ');
		}
		putchar('\n');
	}//俯视图
}
```


---

