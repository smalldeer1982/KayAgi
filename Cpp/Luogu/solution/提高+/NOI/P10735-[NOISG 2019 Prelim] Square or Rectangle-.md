# [NOISG 2019 Prelim] Square or Rectangle?

## 题目背景

翻译自 [NOISG2019 Prelim D.Square or Rectangle?](https://github.com/noisg/sg_noi_archive/blob/master/2019_prelim/)。

请注意，本题为**交互题**，请**尽量使用 C++ 进行作答**。同时，你**只需要实现题目中要求的函数**。**不要将答案输出在标准输出。**

## 题目描述

现在有一个 $N\times N$ 的网格，网格内**有一个至少占网格总大小 $4\%$ 的矩形**。但是，你现在不知道这个矩形是长方形还是正方形，你需要**定义一个函数**来完成这个问题。

### 【实现细节】
你需要定义以下函数：

`bool am_i_square(int N, int Q)`

- $N$：网格的大小
- $Q$：能询问评测机的次数。

为了确定形状，你可以向评测机至多调用 $Q$ 次 `bool inside_shape(int X, int Y)` 函数。调用这个来询问评测机方格 $(X,Y)$ 是否在这个矩形中。

一旦你确定了形状，你就可以返回一个 `bool` 类型的量，代表这个矩形是否为**正方形**。

评测机会调用你的函数 $T$ 次。$T$ 的大小见【数据范围与评测方法】。

## 说明/提示

### 【样例】
考虑以下调用：

![](https://cdn.luogu.com.cn/upload/image_hosting/so2eprl8.png)

`am_i_square(5, 25)`

这表示这是一个 $5 \times 5$ 大小的网格，你可以调用至多 $25$ 次。

`inside_shape(3, 3) = true`

这询问了方格 $(3,3)$ 是否在矩形内，它在正方形的正中间，所以返回 `true`。

`inside_shape(5, 4) = false`

这询问了方格 $(5,4)$ 是否在矩形内，它不在正方形内，所以返回 `false`。

`inside_shape(1, 1) = false`

这询问了方格 $(1,1)$ 是否在矩形内，它不在正方形内，所以返回 `false`。

`inside_shape(2, 4) = true`

这询问了方格 $(2,4)$ 是否在矩形内，它在正方形的左下角，所以返回 `true`。

综上，我们可以确定这是一个正方形，所以该函数返回 `true`。
### 【数据范围与评测方法】
对于 $100\%$ 的测试点：$N=100,1\leq T \leq 1000$。
| $\text{Subtask}$ | 分值 | 附加条件 |
| :----------: | :----------: | :----------: |
| $0$ | $14$ | $Q=10^4$ |
| $1$ | $19$ | $Q=100$ |
| $2$ | $18$ | $Q=40$，图形至少占网格总大小的 $25\%$ |
| $3$ | $49$ | $Q=50$，得分见下文 |
### 【Subtask 3 的计分方法】
记你在所有调用中最大使用了 $q$ 次询问。
- 若 $q >50$，你得到 $0$ 分。
- 若 $34 \leq q \leq 50$，你得到 $40-30\times \frac{q-34}{17}$ 的分数。
- 若 $q \leq 33$，你得到满分。
### 【提示】
请在你的函数前加上以下内容：
```cpp
#include <bits/stdc++.h>
using namespace std;
extern "C" bool inside_shape(int x,int y);
```
同时，请在你的 `bool am_i_square(int N, int Q)` 前加上`extern "C" `。

# 题解

## 作者：ZYLZPP (赞：18)

## 三句话题意

- $100 \times 100$ 的网格中有一个**占比 $\ge 4\%$ 的矩形**。

- 用**至多 $33$ 次** `bool inside_shape(int X, int Y)` 询问方格 $(X,Y)$ 是否在这个矩形中。

- 判断出该矩形是否为**正方形**。

## 前置分析

1. 此处最麻烦的是：如果不确定矩形在哪里，**什么都干不了**。

2. 其次是：随机尝试，确定矩形位置（找到一个点）的**期望步数**是 $25$ 步，这样就**只剩下 $8$ 步了**。

### 这提醒我们

1. 需要找到快速的方法**确定矩形位置**。

2. 需要快速**确定矩形的边界**。

## 解法1（非正解）

由于**占比** $\ge 4\%$，**矩形边长** $\ge 100 \times 4\% = 4$，显然间隔 $4$ 设置**采样点**，必有一点**被矩形包含**。

再通过**二分**确定四边界。

共 $25 \times 25 + \log{4} \times 4 = 633$ 次操作，$14$ pt。

## 解法2

刚才我们渴望寻找**矩形**内的一点，但**矩形**的限制只有 $4$，使复杂度过高。

注意到：题目只要求判断是否为**正方形**，不需要**矩形**的任何其他信息。

由此，我们假定**此矩形是正方形**：

- **正方形边长** $\ge \sqrt{4\%} \times 100 = 20\% \times 100 = 20$。

- 确定**三边的边界**，可通过**边长**，判断**第四边是否符合正方形**。

我们沿用上一解法的**采样点思路**，设置 $5 \times 5$ 个**采样点**，寻找**正方形**包含的点。

若没有，则**不是正方形**。

之后**二分**确定三边边界，再判断**第四边**。

共 $5 \times 5 + \log{20} \times 3 + 1 \approx 40$ 次操作，$80.41$ pt。

## 解法2 + 优化

注意到：**二分**不可优化。

由此尝试**优化采样**：

- 原先设置为 $(20,20) \sim (20x,20y) \sim (100,100)$。

- **最边缘的L形**的采样点 $(20x,100) \sim (100,100) \sim (100,20y)$ 已经**达到边界**，采样是不优的。

- 注意到：若 $4 \times 4$ 的采样中没有点被包含，则**正方形边长**只能为 $20$，且就在**L 形边框**中。

### 优化算法

1. 判断 $4 \times 4$ 采样点，若有，同优化前。

2. 若没有，采样**L 形边框**，若有，二分求出**一边**后即可用边长 $20$ 判断是否是**正方形**。

3. 若还没有，为**长方形**。

综上，共 $4 \times 4 + \log{20} \times 3 + 1 \approx 32$ 或 $5 \times 5 + \log{20} + 1 \approx 31$ 次操作，$100$ pt。

## ACcode

```cpp
#include <bits/stdc++.h>
using namespace std;
extern "C" bool inside_shape(int x, int y);

inline int get_left_point(int x, int y, int p) {
    int l = p, r = y - 1, res = y;
    while (l <= r) {
        int m = (l + r) >> 1;
        if (inside_shape(x, m)) res = m, r = m - 1;
        else l = m + 1;
    }
    return res;
}

inline int get_up_point(int x, int y, int p) {
    int l = p, r = x - 1, res = x;
    while (l <= r) {
        int m = (l + r) >> 1;
        if (inside_shape(m, y)) res = m, r = m - 1;
        else l = m + 1;
    }
    return res;
}

inline int get_right_point(int x, int y, int p) {
    int l = y + 1, r = p, res = y;
    while (l <= r) {
        int m = (l + r) >> 1;
        if (inside_shape(x, m)) res = m, l = m + 1;
        else r = m - 1;
    }
    return res;
}

extern "C" bool am_i_square(int N, int Q) {
    int d = ceil(0.2 * N); //20
    int x = N + 1, y = N + 1, X = 0, Y = 0;
    for (int i = d; i < N; i += d)
        for (int j = d; j < N; j += d)
            if (inside_shape(i, j)) {
                x = min(x, i);
                y = min(y, j);
                X = max(X, i);
                Y = max(Y, j);
            } //4*4
    if (X) { //若有
        int a = get_right_point(X, Y, min(N, Y + d)) - get_left_point(x, y, y - d + 1);
        int b = get_up_point(x, y, x - d + 1) + a; //求3边，判第4边
        return b<=N && (inside_shape(b, Y) && (b == N || !inside_shape(b + 1, Y)));
    }
    //若没有，判L形
    if (inside_shape(N, N)) return !inside_shape(N - d, N) && !inside_shape(N, N - d); //(N,N)特判
    for (int i = d; i < N; i += d) if (inside_shape(i, N)) {
        x = get_up_point(i, N, i - d + 1); //求1边，判对边
        return !inside_shape(x + d, N);
    }
    for (int j = d; j < N; j += d) if (inside_shape(N, j)) {
        y = get_left_point(N, j, j - d + 1);
        return !inside_shape(N, y + d);
    }
    return false; //若还没有
}
```

感谢审核，辛苦 : ) 。

---

## 作者：Resonate (赞：16)

## 前言
这是一道交互题，不了解交互题的推荐先看[洛谷交互题功能说明](https://help.luogu.com.cn/manual/luogu/problem/interactive-problems)、[OI Wiki对交互题的说明](https://oi.wiki/contest/interaction/)、[P1733 猜数（IO交互版）<--交互入门1](https://www.luogu.com.cn/problem/P1733)、[P1947 猜数<--交互入门2](https://www.luogu.com.cn/problem/P1947)。

## 题意
有 $N \times N (N \le 100)$ 的网格内有**至少** $4\%$ 的涂色方格，它们组成一个矩形，你的任务是在**最多** $33$ 次询问方格中的 $(X,Y)$ 方格是否涂色，并以此判断这个矩形是否为**正方形**。

## 思路

我们可以假设**所有的矩形都是正方形**，以 $N = 10$ 为例，则网格内**至少**有 $10 \times 10 \times 4 \% = 4$ 个涂色方块，因为它们都是**正方形**，故它的边长为 $2$，设这个值为 $p$。

对于网格中**任意一点**，都有可能成为涂色矩形中的一点，为了不浪费询问次数，我们可以每隔 $p$ 查询一次，这样可以最大化利用，如图所示，绿色方格为要询问的方格。

![](https://s21.ax1x.com/2024/08/07/pkzSv1x.png)

那为什么 $10$ 行和 $10$ 列不查呢？因为我们要减少询问次数，这个矩形在边缘的概率很小 ~~(不排除毒瘤样例)~~。这样对于 $N = 100$ 的网格，最多只需询问 $16$ 次。

接下来，如果找到了某些点是涂色的，就用 $\min$ 和 $\max$ 找到在矩形中的左上点和右下点（也可以选择其他的），每一次询问，都是为了**使左上的点更在左上，右下的点更在右下**，为后面的寻找矩形的边缘奠定基础。

如果没有找到涂色的点，那这个矩形**一定是在边缘**（可以参考上图），我们再对边缘判断即可。

如果找到了，用二分找左上点**上面的边和左边的边**，找右下点**下面的边**，然后可以通过计算得知**右边的边**，此方法最多的询问次数为 $4 \times 4 + \log 20 \times 3 + 2$ 或 $5 \times 5 + \log 20 + 1$ 次，可以通过本题。

## code

```cpp
#include <bits/stdc++.h>
using namespace std;
extern "C" bool inside_shape(int x,int y);
int up(int x,int y,int s)//向上走，从 x+1 到 s
{
	int l=x+1,r=s,mid,ans=x;
	while(l<=r)
	{
		mid=(l+r)/2;
		if(inside_shape(mid,y))
		{
			ans=mid;
			l=mid+1;
		}
		else
		{
			r=mid-1;
		}
	}
	return ans;
}
int down(int x,int y,int s)//向下走，从 s 到 x-1
{
	int l=s,r=x-1,mid,ans=x;
	while(l<=r)
	{
		mid=(l+r)/2;
		if(inside_shape(mid,y))
		{
			ans=mid;
			r=mid-1;
		}
		else
		{
            l=mid+1;
		}
	}
	return ans;
}
int left(int x,int y,int s)//向左走，从 s 到 y-1
{
	int l=s,r=y-1,mid,ans=y;
	while(l<=r)
	{
		mid=(l+r)/2;
		if(inside_shape(x,mid))
		{
			ans=mid;
			r=mid-1;
		}
		else
		{
			l=mid+1;
		}
	}
	return ans;
}
int right(int x,int y,int s)//向右走，从 y+1 到 s
{
	int l=y+1,r=s,mid,ans=y;
	while(l<=r)
	{
		mid=(l+r)/2;
		if(inside_shape(x,mid))
		{
			ans=mid;
			l=mid+1;
		}
		else
		{
			r=mid-1;
		}
	}
	return ans;
}
extern "C" bool am_i_square(int N, int Q)
{
	int x_1=N+1,x_2=0,y_1=N+1,y_2=0;
	int plus=ceil(0.2*N);//对应上文变量 p
	for(int i=plus;i<N;i+=plus)
	{
		for(int j=plus;j<N;j+=plus)
		{
			if(inside_shape(i,j))
			{
				x_1=min(x_1,i);
				x_2=max(x_2,i);
				y_1=min(y_1,j);
				y_2=max(y_2,j);
			}
		}
	}
	if(x_2)
	{
		int new_x_1=0,new_y_1=0,new_x_2=0,new_y_2=0;
		new_x_1=down(x_1,y_1,x_1-plus+1);//x_1 和 y_1 是左上点
		new_y_1=left(x_1,y_1,y_1-plus+1);
		new_x_2=up(x_2,y_2,min(N,x_2+plus));//x_2 和 y_2 是右下点
		// new_y_2=right(x_2,y_2,min(N,y_2+plus)); 会超限哦~
		new_y_2=new_y_1+(new_x_2-new_x_1);
		return new_x_2<=N and (inside_shape(new_x_2,new_y_2) and (new_y_2==N or !inside_shape(new_x_2,new_y_2+1)));//要求：这个值不能大于 N，计算的右下点被涂色，右下点右边的点未涂色
	}
	if(inside_shape(N,N))//特判
	{
		return !inside_shape(N-plus,N) and !inside_shape(N,N-plus);
	}
	int new_x=0,new_y=0;
	for(int i=plus;i<N;i+=plus)
	{
		if(inside_shape(i,N))
		{
			new_x=down(i,N,i-plus+1);
			return !inside_shape(new_x+plus,N);//如果(i,N)存在，那么(找到的下边+p,N)一定不存在，如果返回为 1 就是这个矩形不是正方形，
		}
	}
	for(int i=plus;i<N;i+=plus)
	{
		if(inside_shape(N,i))
		{
			new_y=left(N,i,i-plus+1);
			return !inside_shape(N,new_y+plus);//同上
		}
	}
	return 0;
}
```

### 后记

~~交互题太好玩啦，[本人千疮百孔的调试代码](https://www.luogu.com.cn/paste/z6rm6oy8)。~~

---

## 作者：xiaoliebao1115 (赞：7)

题面很清楚了，这里就不赘述了，这题还是非常有趣的，自己~~菜~~死做了一天终于做出来了。

## 二分

倘若你已经找到了一个处于矩形内部的位置，就可以向四面二分找到这个矩形的边界，判断是否为矩形即可，现在的问题就转化为如何找到一个处于矩形内部的位置。

## $32$ pts

考虑随机数，随机这个位置的下标，理论上需要的次数并不高，但是因为数据量较大，可能会出现随机了 $100$ 次还没有找到的情况。

### code
```cpp
int x=rand()%N+1,y=rand()%N+1;
while(1){
	if(inside_shape(x,y)==1) break;
	x=rand()%N+1,y=rand()%N+1;
}
int l=1,r=y-1,ans1=y,ans2=y,ans3=x,ans4=x;
while(l<=r)
{
	int mid=(l+r)>>1;
	if(inside_shape(x,mid)==1) r=mid-1,ans1=mid;
	else l=mid+1;
}
l=y+1,r=N;
while(l<=r)
{
	int mid=(l+r)>>1;
	if(inside_shape(x,mid)==1) l=mid+1,ans2=mid;
	else r=mid-1;
}
l=1,r=x-1;
while(l<=r)
{
	int mid=(l+r)>>1;
	if(inside_shape(mid,y)==1) r=mid-1,ans3=mid;
	else l=mid+1;
}
l=x+1,r=N;
while(l<=r)
{
	int mid=(l+r)>>1;
	if(inside_shape(mid,y)==1) l=mid+1,ans4=mid;
	else r=mid-1;
}
if(ans2-ans1==ans4-ans3) return true;
return false;
```
## $82$ pts

因为题目让我们求的只是是否是正方形，所以考虑极限情况。
当正方形的边长最小时也有 $20$，因为面积要超过 $4\%$。
假说给定矩形是正方形，则可以行列都差 $20$ 去枚举，则是枚举 $20,40,60,80,100$。行列都按照这样去枚举，一定能够找到一个点使得它处于矩形内部。如果找不到则一定不是正方形。

然后再根据找到的点进行二分，再判断即可，实现的好的话可以得到 $82$ 分甚至更高。

### code
```cpp
#include<bits/stdc++.h>
using namespace std;
extern "C" bool inside_shape(int x,int y);
extern "C" bool am_i_square(int N, int Q){
	int a[5][5];
	bool p=false;
	int x,y;
	for(int i=1;i<=5;i++){
		for(int j=1;j<=5;j++){
			if(inside_shape(i*20,j*20)){
				x=i,y=j;
				i=6,j=6;
				p=true;
				break;
			}
		}
	}
	if(!p) return 0;
  //以下省略二分
}
```


## 正解

观察 $20,40,60,80,100$ 这个序列，会发现 $100$ 这个数有点多余，因为 $100$ 的后面没有数了，所以考虑将其去掉，那么你需要枚举的坐标就变成了 $4\times4=16$ 种，可以分成两种情况考虑。

### 找到

若在 $4\times4=16$ 种当中找到了若干个点处于矩形之中，则可以处理出若干个点中左上和右下两个顶点，分别从这两个顶点进行二分，此时二分的范围被缩小到 $20$ 以内，因为这是两个顶点往下二分超过 $20$ 之后就会触碰边界或者搜到以前询问过的不处于矩形之中的点。

### 未找到

则将 $100$ 重新加入枚举序列，将与 $100$ 有关的数进行查询。此时正方形的长度已经确定为 $20$，则可以通过一次操作确定上端点或者左端点。假若新查询的数中有且仅有一个处于矩形之中，则对于这一个进行二分，否则不可能成为正方形。

### 优化

以上分类讨论的次数仍然过大，所以考虑再次优化。当你确定了这个图形的上下左右端点的其中 $3$ 个，则你可以推理出当图形为正方形时最后一个端点对应的答案，令它为 $a$，只需要判断这个 $a$ 是否满足 $a$ 处于图形内，且 $a+1$ 不处于图形内即可。

### 次数
此时所对应最坏情况下的询问次数大概如下，很明显可以通过此题。

找到的情况：

$16+3\times \log20+2=16+15+2=33$

未找到的情况：

$25+1+\log20+2=33$

### code

有一些细节给了注释。

```cpp

extern "C" bool am_i_square(int N, int Q){
	int x,y;
	int maxx=0,maxy=0,minx=N+1,miny=N+1;
	for(int i=1;i<=4;i++){
		for(int j=1;j<=4;j++){
			if(inside_shape(i*20,j*20)){
				maxx=max(i,maxx);
				maxy=max(j,maxy);
				minx=min(i,minx);
				miny=min(j,miny);
			}
		}
	}
	if(maxx==0&&maxy==0&&minx==N+1&&miny==N+1){//未找到
		int sum=0,kk,ll;
		for(int i=1;i<=5;i++){
			for(int j=1;j<=5;j++){
				if(i==5||j==5){
					if(inside_shape(i*20,j*20)){
						kk=i,ll=j,sum++;
					}
				}
			}
		}
		if(sum!=1) return 0;
		x=kk,y=ll;
		if(x==5&&y==5){
			if(inside_shape(x*20-19,y*20-19)) return 1;
			return 0;
		}
		if(x==5){
			if(!inside_shape((x-1)*20+1,y*20)) return 0;//先判断能够确保判断的
			int l=(y-1)*20+1,r=y*20-1,ans;
			while(l<=r){
				int mid=(l+r)>>1;
				if(inside_shape(x*20,mid)==1) r=mid-1,ans=mid;
				else l=mid+1;
			}
			if(inside_shape(x*20,19+ans)==1&&inside_shape(x*20,20+ans)==0) return 1;
			return 0;
		}
		if(y==5){
			if(!inside_shape(x*20,(y-1)*20+1)) return 0;//先判断能够确保判断的
			int l=(x-1)*20+1,r=x*20-1,ans;
			while(l<=r){
				int mid=(l+r)>>1;
				if(inside_shape(mid,y*20)==1) r=mid-1,ans=mid;
				else l=mid+1;
			}
			if(inside_shape(19+ans,20*y)==1&&inside_shape(20+ans,20*y)==0) return 1;
			return 0;
		}
	}
	int l=(miny-1)*20+1,r=miny*20-1,ans1=miny*20,ans2=maxy*20,ans3=minx*20,ans4=maxx*20;
	if(l==99)l=100;//100才是边界也要算进去
	if(r==99)r=100;
	while(l<=r){
		int mid=(l+r)>>1;
		if(inside_shape(minx*20,mid)==1) r=mid-1,ans1=mid;
		else l=mid+1;
	}
	l=maxy*20+1,r=(maxy+1)*20-1;
	if(l==99)l=100;
	if(r==99)r=100;
	while(l<=r){
		int mid=(l+r)>>1;
		if(inside_shape(maxx*20,mid)==1) l=mid+1,ans2=mid;
		else r=mid-1;
	}
	l=(minx-1)*20+1,r=minx*20-1;
	if(l==99)l=100;
	if(r==99)r=100;
	while(l<=r){
		int mid=(l+r)>>1;
		if(inside_shape(mid,miny*20)==1) r=mid-1,ans3=mid;
		else l=mid+1;
	}
	ans4=ans2-ans1+ans3;//确定第四个边界
	if(inside_shape(ans4,maxy*20)==1&&inside_shape(ans4+1,maxy*20)==0) return true;
	return false;
}
```
## check

这里提供一个程序以检验您的程序是否正确，不正确可以方便检查错误。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int n=100;
int step=0,x1,x2,y11,y2,t;
bool inside_shape(int x,int y)
{
	step++;
	if(x>=x1&&x<=x2&&y>=y11&&y<=y2) return 1;
	return 0;
}
bool am_i_square(int N, int Q){
	//你的程序
}
int main()
{
	srand(time(0));
	for(int i=1;i<=100000;i++){
		step=0;
		x1=rand()%n+1,x2=rand()%n+1,y11=rand()%n+1,y2=rand()%n+1,t=rand()%2;//0 1
		while(1){
			if(x1<x2&&y11<y2){
				if((x2-x1+1)*(y2-y11+1)>=400&&(t==1&&x2-x1==y2-y11||t==0)){
					break;
				}
			}
			x1=rand()%n+1,x2=rand()%n+1,y11=rand()%n+1,y2=rand()%n+1;
		}
		if(x2-x1==y2-y11) t=1;
		bool g=am_i_square(100,50);
		if(g==t&&step<=33) cout<<"correct"<<" "<<step<<endl;
		else 
		{
			cout<<"wrong"<<endl;
			cout<<x1<<" "<<x2<<" "<<y11<<" "<<y2<<endl;
			break;
		}
	}
}
```

---

## 作者：vorDeal (赞：2)

第一道交互题，记之。

### 解法一
全部扫一遍即可。

需要 $100 \times 100=10^4$ 次查询，期望得分 $14$ pts。

### 解法二

考虑只取一部分点。

一个显然的想法是随机取，然而危险性太大。

观察到矩形的面积至少为 $400$，所以矩形的宽至少为 $4$。考虑以 $4\times4$ 为单位采样，再二分扩大四周边界。

最坏情况下需要 $25 \times 25 +4\times\log4=633$ 次查询，期望得分 $14$ pts。

### 解法三

发现我们实际上不需要知道矩形长宽。我们考虑问题的另一种形式：所给矩形是否是正方形？

假设所给矩形是正方形，因为面积至少为 $400$，所以正方形的边长至少为 $20$。考虑以 $20\times20$ 为单位采样，再二分扩大四周边界。如果采不到样，或长不等于宽，则不为正方形。

最坏情况下需要 $5 \times 5 +4\times\lceil\log20\rceil=45$ 次查询，期望得分 $33\sim 56$ pts。

### 解法四

在最后判断长宽是否相等时，我们考虑一个优化，先确定矩形纵向长度，找到左边界，再判断平移后是否为右边界。

最坏情况下需要 $5 \times 5 +3\times\lceil\log20\rceil+2=42$ 次查询，期望得分 $56\sim 83$ pts。

### 解法五

发现采样密度和单次二分已经无法优化，考虑对二者其一进行优化。

分类讨论。

- A 部：左上角 $80\times80$ 区域。
- B 部：右下角折线形剩余区域。

我们对 A 部应用解法四进行采样，如果采到样，那么二分扩大边界求解。最坏情况下需要 $4 \times 4+3\times\lceil\log20\rceil+2=33$ 次查询。

否则呢，符合要求的正方形仅可能存在于 B 部，边长仅可能为 $20$。我们对 B 部 $9$ 个采样点进行采样。如果没有采到样，不是正方形。否则我们选取一个方向的边界进行扩展，再考察矩形长宽是否均为 $20$，以此确定形状。最坏情况下需要 $5 \times 5 +\lceil\log20\rceil+3=33$ 次查询。

可以通过本题。

**AC Code：**
```cpp
#include <bits/stdc++.h>
using namespace std;
extern "C" bool inside_shape(int x, int y);

int u_expand(int x, int y)
{
    int l = x - 19, r = x - 1, res = x, mid;
    while (l <= r)
        mid = (l + r) >> 1, (inside_shape(mid, y) ? res = mid,
                             r = mid - 1          : l = mid + 1);
    return res;
}

int l_expand(int x, int y)
{
    int l = y - 19, r = y - 1, res = y, mid;
    while (l <= r)
        mid = (l + r) >> 1, (inside_shape(x, mid) ? res = mid,
                             r = mid - 1          : l = mid + 1);
    return res;
}

int r_expand(int x, int y)
{
    int l = y + 1, r = y + 20, res = y, mid;
    while (l <= r)
        mid = (l + r) >> 1, (inside_shape(x, mid) ? res = mid,
                             l = mid + 1          : r = mid - 1);
    return res;
}

extern "C" bool am_i_square(int n, int q)
{
    int cnt = 0;
    int u = 101, d = 0, l = 101, r = 0;
    for (int i : {20, 40, 60, 80})
        for (int j : {20, 40, 60, 80})
            if (inside_shape(i, j))
                u = min(u, i), d = max(d, i),
                l = min(l, j), r = max(r, j), cnt++;
    if (cnt > 0)
    {
        u = u_expand(u, l), r = r_expand(d, r);
        l = l_expand(u, l), d = u + r - l;
        if (d > 100 || !inside_shape(d, r))
            return false;
        return d == 100 || !inside_shape(d + 1, r);
    }
    for (int i : {20, 40, 60, 80})
    {
        if (inside_shape(100, i))
            return !inside_shape(100, l_expand(100, i) + 20);
        if (inside_shape(i, 100))
            return !inside_shape(u_expand(i, 100) + 20, 100);
    }
    if (inside_shape(100, 100))
        return !(inside_shape(80, 100) || inside_shape(100, 80));
    return false;
}
```

---

