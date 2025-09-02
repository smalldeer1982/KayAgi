# Vasily the Bear and Fly

## 题目描述

One beautiful day Vasily the bear painted $ 2m $ circles of the same radius $ R $ on a coordinate plane. Circles with numbers from $ 1 $ to $ m $ had centers at points $ (2R-R,0) $ , $ (4R-R,0) $ , $ ... $ , $ (2Rm-R,0) $ , respectively. Circles with numbers from $ m+1 $ to $ 2m $ had centers at points $ (2R-R,2R) $ , $ (4R-R,2R) $ , $ ... $ , $ (2Rm-R,2R) $ , respectively.

Naturally, the bear painted the circles for a simple experiment with a fly. The experiment continued for $ m^{2} $ days. Each day of the experiment got its own unique number from $ 0 $ to $ m^{2}-1 $ , inclusive.

On the day number $ i $ the following things happened:

1. The fly arrived at the coordinate plane at the center of the circle with number ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF336B/1b364c80eefc9bb591cfee14c9b688961a93a8ea.png) (![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF336B/2e19bbae9bd88a29fe3fe77f1d030d713103ddf9.png) is the result of dividing number $ x $ by number $ y $ , rounded down to an integer).
2. The fly went along the coordinate plane to the center of the circle number ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF336B/c14650a911b9c897e385d07e41f4fe67d4bab52b.png) (![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF336B/cb1d84ad58154eb7ea26b65d1ae0039570db9bb6.png) is the remainder after dividing number $ x $ by number $ y $ ). The bear noticed that the fly went from the center of circle $ v $ to the center of circle $ u $ along the shortest path with all points lying on the border or inside at least one of the $ 2m $ circles. After the fly reached the center of circle $ u $ , it flew away in an unknown direction.

Help Vasily, count the average distance the fly went along the coordinate plane during each of these $ m^{2} $ days.

## 说明/提示

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF336B/6102118b4e5d6ba27b3c37cb86bca9d322e9441e.png)

Figure to the second sample

## 样例 #1

### 输入

```
1 1
```

### 输出

```
2.0000000000
```

## 样例 #2

### 输入

```
2 2
```

### 输出

```
5.4142135624
```

# 题解

## 作者：liuzhongrui (赞：1)

## 主要思路

令 $1 \le i \le m$，第 $m + i$ 个圆的距离为 $2 \times R$。对于第 $m + j$ 个圆，其中  $\lvert j - i \rvert = 1$，距离为 $2 \times R + \sqrt{2} \times R$ 。至于其他圆，可以简单地计算它们的距离之和。当前圆左侧有 $i - 2$ 个圆，因此这些圆的距离之和为 $R \times (i - 2) \times (i - 1) + 2 \times R \times \sqrt{2} \times (i - 2)$。以相同的方式，我们可以计算位于当前圆右侧的圆的答案。

## Code

代码很简单。

```cpp
#include <bits/stdc++.h>
int N,R;
double ans,s;
int main(){
	scanf("%d%d",&N,&R),ans=N+(N-1)*(sqrt(2)+2);
	for (int i=3; i<=N; i++) s+=(2*sqrt(2)+i-1)*(i-2);
	printf("%.10lf\n",(ans+s)*2*R/N/N);
	return 0;
}
```


---

## 作者：xuan_gong_dong (赞：1)

## 题面

[Vasily the Bear and Fly](https://www.luogu.com.cn/problem/CF336B)

## 分析
题面大意其实就是下面的 $m$ 个圆心为起点，上面 $m$ 个店为终点，询问选择任意一个起点到任意一个终点的平均距离为多少。

那就是求出所有路径和，再除 $m^2$ 即为答案。
### 分一下三种情况

1. 直接从上面下来，距离为 $2 \times R$。
2. 从左上，右上一格处下来，距离为 $R \times ( 2 + \sqrt{2})$。
3. 其他位置，就是到 $i-2$ 或 $i+2$ 处，再穿过两个圆下来，穿过圆的长度为 $2 \times \sqrt{2}$。

整理一下其他位置的和就是

$$\sum_{i=2}^n 4 \times ( m - i ) \times ( ( i - 2 ) + \sqrt{2}) \times r$$

然后就写出来了。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
double M,R;
double ans;
int main()
{
	int m,r;
	scanf("%d%d",&m,&r);
	M=m;
	R=r;
	ans=0;
	ans+=M*(2*R);
	if(m>1)
		ans+=(M-1)*2*(R*sqrt(2)+2*R);
	for(int i=2;i<m;i++)
			ans+=4*(M-i)*(((i-1)+sqrt(2))*r);
	printf("%.10lf",ans/m/m);
	return 0;
}
```


---

## 作者：skyskyCCC (赞：0)

## 前言。
比较基础的计算题。
## 分析。
不妨考虑直接遍历每一个圆，既然是从下面的点到上面的点，任意选择起点与中点，那么起点的选择就有 $m$ 种，每一个起点对应的终点也有 $m$ 个，故一共有 $m^2$ 中可能，所以直接计算出一共可能的方案数中的距离的加和，最后除以方案数即是平均距离。

我们不妨拆出一个圆 $i$ 使得 $1\leq i\leq m$ 则我们考虑从这个圆出发那么第 $i$ 个圆距离到第 $m+i$ 个圆的直线最短距离（圆心距）就是两个半径的长度即 $2\times r$ 的长度。那么我们再考虑拐弯的情况。我们用题目中的一张图讲解可能会更直观：
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF336B/6102118b4e5d6ba27b3c37cb86bca9d322e9441e.png)
观察第一天或者第二天所对应的图像，下面的方向中带括号的表示第二天，不带的表示第一天。我们发现如果我们从第 $i$ 个圆到达第 $m+j\left(\lvert j-i \rvert=1\right)$ 个圆时，我们可以将它们看做是两个部分，就是先从第 $i$ 个圆的圆心出发，向右（左）移动到旁边的圆的圆弧上，然后在直接以直线距离到达第 $m+j$ 个圆和第 $i+1$ 个圆的交点上，此时不难看出最短距离就是两个交点的连线，最后再向上到达第 $m+j$ 个圆的圆心。那么整段路程就是两个半径在加上那一段直线距离，即:
$$2\times r+\sqrt{r^2+r^2}=2\times r+\sqrt2\times r=r\times\left(2+\sqrt2\right)$$
同理，我们分析一下在 $i$ 出发然后移动到 $i-2$ 或者 $i+2$ 的位置处，再穿过两个圆下来，这种情况我们不难得到是 $2\times\sqrt2$ 的距离。

这样我们每一种情况都分析好了，直接将这些情况都加起来，最后除以方案数即可。

代码如下，仅供参考：
```
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstdio>
using namespace std;
int m,r;
double ans,sum;
int main(){
	cin>>m>>r;
	ans=m+(m-1)*(sqrt(2)+2);
	for (int i=3;i<=m;i++){
		sum+=(2*sqrt(2)+i-1)*(i-2);
	}
	//cout<<ans<<"\n";
	ans=(ans+sum)*2*r/m/m;
	printf("%.10lf",ans);
	//cout<<ans<<"\n";
	return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

