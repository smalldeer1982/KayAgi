# Security System

## 题目描述

狐狸茜尔安全地回到了她的城堡，但是城堡的安全系统出了问题：城堡里的传感器覆盖了她。

Ciel 现在位于城堡的点 $(1,1)$，她想移动到点 $(n,n)$，也就是她房间的位置。希尔可以从点 $ (x,y) $ 向 $ (x+1,y) $ （向右）或 $ (x,y+1) $ （向上）移动一步。

在她的城堡中，$ c^{2} $ 传感器被设置在点 $ (a+i,b+j) $ 上（对于每一个整数 $ i $ 和 $ j $ ，$ 0\leq i < c,0\leq j< c $）。

每个传感器都有一个计数值，每当 Ciel 移动一次，其计数值就会减少一次。初始时，每个传感器的计数值为 $ t $ 。 每当 Ciel 移动到点 $ (x,y) $ 时，位于点 $ (u,v) $ 的传感器的计数值会减少 ( $ |u-x|+|v-y| $ ) 。当某个传感器的计数值严格小于 $ 0 $ 时，该传感器将捕捉到 Ciel 这个可疑个体！

确定希尔能否在不被传感器捕获的情况下从 $ (1,1) $ 移动到 $ (n,n)$，如果可以，输出她的步骤。假设 Ciel 可以移动到每一个点，即使该点上有一个检查器。

## 说明/提示

第一个样本和第二个样本的答案如图所示：

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF79E/2c5562a40dba3d1d0c90775040aa3307664b4c01.png)
 
红点代表包含传感器的点。

## 样例 #1

### 输入

```
5 25 2 4 1
```

### 输出

```
RRUURURU
```

## 样例 #2

### 输入

```
3 6 1 2 2
```

### 输出

```
URUR
```

## 样例 #3

### 输入

```
3 5 1 2 2
```

### 输出

```
Impossible
```

## 样例 #4

### 输入

```
20 492 11 4 8
```

### 输出

```
RRRRRRRRRRRRRRRRUUUUURUUUUURRUUUUUUUUU
```

# 题解

## 作者：xtx1092515503 (赞：1)



> Observation 1.我们只需关注正方形四角上元素即可。

不断调整即可得到该结果。

> Algorithm 1.枚举下一步的方向。此时我们知道四角上监视器的剩余次数以及当前的位置，只需判定此时按照最优方式走，能否到达终点即可。

> Description 1.我们使用六个值即可描述一个状态，也即当前的坐标和四个监视器的剩余次数。

> Situation 1.假设仅有一个监视器。

此时，考虑以该监视器为原点建立新平面直角坐标系。则，我们发现在一三象限上，无论按照什么方式走，贡献总是一定的。在第二象限与 $x$ 轴负半轴上，向右走总是更优；在第四象限与 $y$ 轴负半轴上，向上走总是更优。

> Situation 2.有全部四个监视器。

此时考虑四个监视器 `ABCD` 将平面分成了如下九个部分：

```
III| II| I 
---B---A---
 IV| IX|VIII
---C---D---
 V | VI|VII
```

在 `I,V` 中显然任意走；在 `II,III,IV,VI,VII,VIII` 中的方向显然已经确定；唯独 `IX` 一块中，方向不确定。但是注意到 `IX` 对于 `A,C` 两监视器来说是在任意范围内的，因而仅需考虑 `BD` 两监视器。

注意到穿越 `IX` 的路径的起讫点是确定的。则我们可以找到相对 `B` 最短的路径（此时相对 `D` 最长）以及相对 `D` 最短、相对 `B` 最长的路径。显然通过逐步调整，任何在这两条路径中间的效果都可以被构造出，接下来就只要判定 `BD` 剩下的步数是否落在这一范畴中即可。复杂度线性。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,a,b,c;ll T;
int dis(int x,int y,int X,int Y){return abs(x-X)+abs(y-Y);}
ll route(int s,int t){return 1ll*(s<t?s+t+1:s+t-1)*abs(s-t)>>1;}
#define _A a+c-1,b+c-1
#define _B a,b+c-1
#define _C a,b
#define _D a+c-1,b
bool che(int x,int y,ll A,ll B,ll C,ll D){
//	printf("I%d %d %lld %lld %lld %lld\n",x,y,A,B,C,D);
	ll _a,_b,_c,_d;
	if(x<a){
		_a=route(dis(x,y,_A),dis(a,y,_A));if(A<_a)return false;A-=_a;
		_b=route(dis(x,y,_B),dis(a,y,_B));if(B<_b)return false;B-=_b;
		_c=route(dis(x,y,_C),dis(a,y,_C));if(C<_c)return false;C-=_c;
		_d=route(dis(x,y,_D),dis(a,y,_D));if(D<_d)return false;D-=_d;
		x=a;
	}
	if(y<b){
		_a=route(dis(x,y,_A),dis(x,b,_A));if(A<_a)return false;A-=_a;
		_b=route(dis(x,y,_B),dis(x,b,_B));if(B<_b)return false;B-=_b;
		_c=route(dis(x,y,_C),dis(x,b,_C));if(C<_c)return false;C-=_c;
		_d=route(dis(x,y,_D),dis(x,b,_D));if(D<_d)return false;D-=_d;
		y=b;
	}
//	printf("II%d %d %lld %lld %lld %lld\n",x,y,A,B,C,D);
	_c=route(dis(x,y,_C),dis(n,n,_C));if(C<_c)return false;
	if(x>=a+c-1||y>=b+c-1){
		if(x<a+c-1){
			_a=route(dis(x,y,_A),dis(a+c-1,y,_A));if(A<_a)return false;A-=_a;
			_b=route(dis(x,y,_B),dis(a+c-1,y,_B));if(B<_b)return false;B-=_b;
			_d=route(dis(x,y,_D),dis(a+c-1,y,_D));if(D<_d)return false;D-=_d;
			x=a+c-1;
		}
		if(y<b+c-1){
			_a=route(dis(x,y,_A),dis(x,b+c-1,_A));if(A<_a)return false;A-=_a;
			_b=route(dis(x,y,_B),dis(x,b+c-1,_B));if(B<_b)return false;B-=_b;
			_d=route(dis(x,y,_D),dis(x,b+c-1,_D));if(D<_d)return false;D-=_d;
			y=b+c-1;
		}
		_a=route(dis(x,y,_A),dis(n,n,_A));if(A<_a)return false;A-=_a;
		_b=route(dis(x,y,_B),dis(n,n,_B));if(B<_b)return false;B-=_b;
		_d=route(dis(x,y,_D),dis(n,n,_D));if(D<_d)return false;D-=_d;
		return true;
	}
	_a=route(dis(_A,_A),dis(n,n,_A));if(A<_a)return false;A-=_a;
	_b=route(dis(_A,_B),dis(n,n,_B));if(B<_b)return false;B-=_b;
	_d=route(dis(_A,_D),dis(n,n,_D));if(D<_d)return false;D-=_d;
	_a=route(dis(x,y,_A),dis(a+c-1,b+c-1,_A));if(A<_a)return false;
	ll bl=route(dis(x,y,_B),dis(x,b+c-1,_B))+route(dis(x,b+c-1,_B),dis(_A,_B));
	ll dr=route(dis(x,y,_D),dis(x,b+c-1,_D))+route(dis(x,b+c-1,_D),dis(_A,_D));
	ll br=route(dis(x,y,_B),dis(a+c-1,y,_B))+route(dis(a+c-1,y,_B),dis(_A,_B));
	ll dl=route(dis(x,y,_D),dis(a+c-1,y,_D))+route(dis(a+c-1,y,_D),dis(_A,_D));
	if(B<bl)return false;if(D<dl)return false;
	assert(bl+dr==br+dl);
	ll sum=bl+dr;
	if(D<sum-min(br,B))return false;
	return true;
}
int main(){
	scanf("%d%lld%d%d%d",&n,&T,&a,&b,&c);
	if(!che(1,1,T,T,T,T)){puts("Impossible");return 0;}
	int x=1,y=1;ll A=T,B=T,C=T,D=T;
	while(x!=n||y!=n){
		if(x!=n&&(y==n||che(x+1,y,A-dis(x+1,y,_A),B-dis(x+1,y,_B),C-dis(x+1,y,_C),D-dis(x+1,y,_D))))
			x++,A-=dis(x,y,_A),B-=dis(x,y,_B),C-=dis(x,y,_C),D-=dis(x,y,_D),putchar('R');
		else y++,A-=dis(x,y,_A),B-=dis(x,y,_B),C-=dis(x,y,_C),D-=dis(x,y,_D),putchar('U');
	}
	return 0;
}
```


---

