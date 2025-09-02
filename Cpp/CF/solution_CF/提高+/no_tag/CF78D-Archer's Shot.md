# Archer's Shot

## 题目描述

如下图，"$Civilization XIII$"游戏中的每一个正六边形边长都为1。有一个射箭运动员站在图中的$A$处：

![CF78DPIC](https://cdn.luogu.com.cn/upload/vjudge_pic/CF78D/4ab005c95a817122b246c2ebc315408e9138d480.png)

这个射箭运动员$A$有一个常数$k$，表示其可以射箭的长度范围。每个射箭运动员都可以射到六个顶点到自己的距离都小于等于$k$的正六边形。

## 样例 #1

### 输入

```
3
```

### 输出

```
7```

## 样例 #2

### 输入

```
4
```

### 输出

```
13```

## 样例 #3

### 输入

```
5
```

### 输出

```
19```

# 题解

## 作者：XL4453 (赞：0)

### $\text{Difficulty : 2300}$
---
### 解题思路：

考虑一种和圆内整点类似的方法。

以点 $A$ 为坐标原点建立坐标系，可以发现每一个点都可以描述为 $(\dfrac{1}{2}x,\dfrac{\sqrt{3}}{2}y)$ 的形式。

记录下每一个中心位置的 $x$ 和 $y$，可以直接通过简单的计算判断出中心位置所在的正六边形是否可以被射击到。

直接先上找到最大的可能位置，然后向右拓展到最右端的位置，找出边界即可。

---
注意计算的时候需要特殊处理一下中间一列，这一列没有与之对称的位置。

---
### 代码：

```cpp
#include<cstdio>
using namespace std;
#define int long long
int k,ans,x,y;
bool check(int x,int y){
	if((x+1)*(x+1)+3*(y+1)*(y+1)>4*k*k)return 0;
	if((x+2)*(x+2)+3*y*y>4*k*k)return 0;
	return 1;
}
signed main(){
	scanf("%I64d",&k);
	while(check(x,y))
	y+=2;
	ans=-y-3;
	while(y>=0){
		ans+=2*(y+1);
		x+=3;
		y+=1;
		while(y>=0&&(check(x,y)==0))y-=2;
	}
	printf("%I64d\n",ans);
	return 0;
}
```


---

