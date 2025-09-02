# 题目信息

# Tiles

## 题目描述

Bob is decorating his kitchen, more precisely, the floor. He has found a prime candidate for the tiles he will use. They come in a simple form factor — a square tile that is diagonally split into white and black part as depicted in the figure below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1178C/51fd9adf02d36f09b63ea5e4909ce958161fd4a1.png)The dimension of this tile is perfect for this kitchen, as he will need exactly $ w \times h $ tiles without any scraps. That is, the width of the kitchen is $ w $ tiles, and the height is $ h $ tiles. As each tile can be rotated in one of four ways, he still needs to decide on how exactly he will tile the floor. There is a single aesthetic criterion that he wants to fulfil: two adjacent tiles must not share a colour on the edge — i.e. one of the tiles must have a white colour on the shared border, and the second one must be black.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1178C/b795f3504af8553334180ece9878d04b86535357.png)The picture on the left shows one valid tiling of a $ 3 \times 2 $ kitchen. The picture on the right shows an invalid arrangement, as the bottom two tiles touch with their white parts.Find the number of possible tilings. As this number may be large, output its remainder when divided by $ 998244353 $ (a prime number).

## 样例 #1

### 输入

```
2 2
```

### 输出

```
16
```

## 样例 #2

### 输入

```
2 4
```

### 输出

```
64
```

# AI分析结果

### 题目内容重写
# 瓷砖

## 题目描述

Bob正在装饰他的厨房，特别是地板。他找到了一种理想的瓷砖，瓷砖的形状是一个正方形，对角线将其分成白色和黑色两部分，如下图所示。

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1178C/51fd9adf02d36f09b63ea5e4909ce958161fd4a1.png)这种瓷砖的尺寸非常适合他的厨房，因为他需要恰好$w \times h$块瓷砖，且没有任何剩余。也就是说，厨房的宽度是$w$块瓷砖，高度是$h$块瓷砖。由于每块瓷砖可以旋转成四种不同的方式，他仍然需要决定如何铺设地板。他有一个美学标准：相邻的两块瓷砖在共享的边缘上不能有相同的颜色——即一块瓷砖在共享的边缘上必须是白色，另一块必须是黑色。

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1178C/b795f3504af8553334180ece9878d04b86535357.png)左边的图片展示了一个$3 \times 2$厨房的有效铺设方式。右边的图片展示了一个无效的铺设方式，因为底部的两块瓷砖在白色部分接触。求可能的铺设方式的数量。由于这个数字可能很大，输出其对$998244353$（一个质数）取模的结果。

## 样例 #1

### 输入

```
2 2
```

### 输出

```
16
```

## 样例 #2

### 输入

```
2 4
```

### 输出

```
64
```

### 算法分类
数学

### 题解分析与结论
所有题解都基于一个核心思路：确定第一行和第一列的瓷砖状态后，整个铺设方式就被唯一确定了。由于每块瓷砖有4种旋转方式，但相邻瓷砖的颜色必须不同，因此第一行和第一列的每块瓷砖有2种选择（除了第一块有4种选择）。最终，铺设方式的总数为$2^{w+h}$。

### 所选高分题解
#### 题解1：Zhoumy (5星)
**关键亮点**：简洁明了地解释了为什么第一行和第一列的瓷砖状态决定了整个铺设方式，并直接给出了$2^{w+h}$的计算方法。
**代码实现**：
```cpp
#include<iostream>
using namespace std;
long long ans=1,w,h;
int main(){
	cin>>w>>h;
	for(int i=1;i<=w+h;i++){
		ans*=2;
		ans%=998244353;
	}
	cout<<ans;
	return 0;
}
```

#### 题解2：Waddles (4星)
**关键亮点**：通过快速幂优化了计算过程，代码更加高效。
**代码实现**：
```cpp
ll ksm(ll x,ll y){//快速幂
	ll s=1;
	while(y){
		if(y&1)s=(s*x)%M;
		x=(x*x)%M;
		y>>=1;
	}
	return s%M;
}
int main(){
	in(n);in(m);
	cout<<ksm(2ll,n+m)<<endl;//输出
	return 0;
}
```

#### 题解3：_bql (4星)
**关键亮点**：详细分析了瓷砖的旋转方式及其对铺设方式的影响，并给出了$2^{w+h}$的推导过程。
**代码实现**：
```cpp
#define mo 998244353
#define ll long long

ll n,k;
int main()
{
	cin>>n>>k;
    ll p=n+k,b=2,ans=1;
    while(p>0)
    {
        if(p%2==1) ans=ans*b%mo;
        b=b*b%mo;
        p=p/2;   
    }
	cout<<ans;
	return 0;
}
```

### 最优关键思路
确定第一行和第一列的瓷砖状态后，整个铺设方式被唯一确定。每块瓷砖有2种选择（除了第一块有4种选择），因此总铺设方式为$2^{w+h}$。

### 拓展思路
类似的问题可以出现在其他需要满足相邻元素约束的排列组合问题中，如棋盘覆盖、图着色等。

### 推荐题目
1. [P1002 过河卒](https://www.luogu.com.cn/problem/P1002)
2. [P1028 数的计算](https://www.luogu.com.cn/problem/P1028)
3. [P1044 栈](https://www.luogu.com.cn/problem/P1044)

---
处理用时：34.32秒