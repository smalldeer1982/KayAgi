# Cutting Rectangle

## 题目描述

A rectangle with sides $ A $ and $ B $ is cut into rectangles with cuts parallel to its sides. For example, if $ p $ horizontal and $ q $ vertical cuts were made, $ (p + 1) \cdot (q + 1) $ rectangles were left after the cutting. After the cutting, rectangles were of $ n $ different types. Two rectangles are different if at least one side of one rectangle isn't equal to the corresponding side of the other. Note that the rectangle can't be rotated, this means that rectangles $ a \times b $ and $ b \times a $ are considered different if $ a \neq b $ .

For each type of rectangles, lengths of the sides of rectangles are given along with the amount of the rectangles of this type that were left after cutting the initial rectangle.

Calculate the amount of pairs $ (A; B) $ such as the given rectangles could be created by cutting the rectangle with sides of lengths $ A $ and $ B $ . Note that pairs $ (A; B) $ and $ (B; A) $ are considered different when $ A \neq B $ .

## 说明/提示

In the first sample there are three suitable pairs: $ (1; 9) $ , $ (3; 3) $ and $ (9; 1) $ .

In the second sample case there are 6 suitable pairs: $ (2; 220) $ , $ (4; 110) $ , $ (8; 55) $ , $ (10; 44) $ , $ (20; 22) $ and $ (40; 11) $ .

Here the sample of cut for $ (20; 22) $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF963C/278439628d1e70bac8f3d98ded9fac389f122d75.png)The third sample has no suitable pairs.

## 样例 #1

### 输入

```
1
1 1 9
```

### 输出

```
3
```

## 样例 #2

### 输入

```
2
2 3 20
2 4 40
```

### 输出

```
6
```

## 样例 #3

### 输入

```
2
1 2 5
2 3 5
```

### 输出

```
0
```

# 题解

## 作者：panyanppyy (赞：0)

@houzhiyuan 食堂给的题目，思维过程有点痛苦，最后想出来了。
## Problem
给你 $n$ 个形如 $a,b,c$ 的三元组，分别表示矩形的长宽和数量，问用所有矩形拼出一个经过横切 $p$ 刀，竖切 $q$ 刀（一刀切到底，$p,q$ 为任意非负整数）的矩形构成的大矩形的方案数。
## Solution
首先考虑怎么构造出一种情况。

我们先考虑每一行的 $a$，这时候问题就变成了对于每个不同的 $a$ 能否通过一些方式使每一行的 $b$ 和 $c$ 的排列相等（由于题目不关心长宽一样的答案矩形，所以只需要其中一种排列相等就行了）。

$b$ 的值是不能修改的，所以如果 $b$ 的排列不相等就输出 $0$。

然后考虑怎么求出所有方案，那就考虑所有 $c$ 对答案的贡献。

从样例二中的矩形中可以发现，每一行每种不同矩形的数量可以拆成它们 $\gcd$ 的其中一个因数个部分，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/mzns5g2j.png)

这张图中长为 $c$ 的 $\gcd=2$ 所以可以拆成下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/7tsqu7gz.png)

于是乎答案就很显然了，对所有 $c$ 取一遍 $\gcd$ 然后输出它的因数个数就可以了。

## Code
代码很短，但是思考过程很长。
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ri register
#define all(x) (x).begin(),(x).end()
using namespace std;
vector<pair<ll,ll>>s,t;
map<ll,vector<pair<ll,ll>>>mp;
int n;
ll g,G,ans;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		static ll x,y,z;
		scanf("%lld%lld%lld",&x,&y,&z);
		mp[x].emplace_back(y,z);
	}//对于每个a放入b,c
	for(auto i:mp){
		t=i.second,sort(all(t)),g=0;
		for(auto[x,y]:t)g=__gcd(g,y);
		for(auto&[x,y]:t)y/=g;
		G=__gcd(g,G);
		if(s.empty())s=t;
		else if(s!=t)return puts("0")&0;//b,c不同，无解
	}
	for(ll i=1;i*i<=G;i++)
		if(G%i==0)ans+=2-(i*i==G);
	printf("%lld\n",ans);
	return 0;
}
```

---

