# Beautiful Function

## 题目描述

给出$n$个圆，构造两个合法的函数$f(t),g(t)$，设点集$S$是整数$t\in[0,50]$时$(f(t),g(t))$构成的点的集合，你需要保证对于每一个圆，至少存在一个点（包括边界）在点集$S$中。

令$w(t)$与$h(t)$为两个合法的函数，那么合法的函数由以下几种函数复合而成：

①$s(t) = abs(w(t))$，其中$abs()$表示取绝对值

②$s(t) = (w(t) + h(t))$

③$s(t) = (w(t) - h(t))$

④$s(t) = (w(t) \times h(t))$

⑤$s(t) = C$（C为整数）

⑥$s(t) = t$

在$f(t)$与$g(t)$中，只能至多出现$50$次函数相乘的操作，函数长度不能超过$100n$，**输出时不能出现空格**，并且当整数$t \in [0,50]$时，$-10^9 \leq f(t),g(t) \leq 10^9$

## 样例 #1

### 输入

```
3
0 10 4
10 0 4
20 10 4
```

### 输出

```
t 
abs((t-10))```

# 题解

## 作者：gcwixsxr (赞：2)

题目传送门：[CF593C Beautiful Function](https://www.luogu.com.cn/problem/CF593C)

首先注意到可以使用的函数运算符有加减乘和 $abs$，那么题目显然是要求我们利用这几个运算符的性质。

值得注意的是，拉插在此题并不适用，因为此题并不支持除法。显然我们要利用若干函数实现 $[t=i]$ 这一个式子，接下来只需要令 $f(t)=\sum_i[t=i]x_i$ 即可。

$abs$ 的性质：

1. $abs(a-b)=a-b\Leftrightarrow a\geq b$；
2. $abs(a)< x \Leftrightarrow -x< a< x$。

那么考虑如下式子的含义：

$$
g(x,y)=1-abs(x-y)+abs(abs(x-y)-1)
$$

令 $a=abs(x-y),b=1$，利用性质 $1$，当 $a\geq b$ 时，$g(x,y)$ 的值为零。接下来考虑 $a<b$，利用性质 $2$，$a<b$ 等价于 $-1<x-y<1$，而 $x,y$ 为整数，所以有 $x=y$。

总结一下，当 $x=y$ 时，$g(x,y)$ 等于 $2$，否则等于 $0$。那就相当于实现了 $[t=i]$ 函数的一半。

其实这个 $2$ 因子对于原式的影响并不大：由于圆的半径大于 $2$，也就是说， $1$ 的误差在允许范围之内，我们直接使用 $\left\lfloor\dfrac {x_i} 2\right\rfloor$ 乘上 $g(t,i)$ 即可。

---

## 作者：skyskyCCC (赞：0)

## 前言。
补一个构造的思路，大约是个正解。
## 分析。
显然不可能构造出一个简单的函数，例如一次函数，就能通过所有的圆。

要穿过所有的圆，我们就考虑穿过每一个圆的圆心。此时我们的期望就是构造出 $f\left(t\right)= y_1\left(t\right)+y_2\left(t\right)+y_3\left(t\right)+\ldots+y_i\left(t\right)$ 的形式。然后我们通过构造使得它刚好取到第一个圆圆心位置 $x_1$ 的时候只有 $g_1$ 有值且必须为 $y_i$ 同时其他各项都不存在，即为零。然后如法炮制，构造第二个圆，第三个圆。

考虑绝对值的情况。前面的题解已经讲述的的很详细，这里不作赘述，主要讲解一些如何构造的问题。

首先由前文，需要的 $y_1\left(t\right)$ 可以满足只有在 $t=t_1$ 时有值，那么我们令 $d=\left|t-t_i\right|$ 则可以得到 $\left(1-d+\left|1-d\right|\right)$ 的式子。此时，当 $t_1\neq t$ 时 $d>0$ 且 $d$ 为整数，所以 $d\ge1$ 一定存在，所以 $\left(1-d+\left|1-d\right|\right)=1-d+d-1=0$ 的情况成立。同时注意到，对于圆 $i$ 而言，当且仅当 $x_1=x$ 时 $d=0$ 此时原式就变成 $2$ 的情况，需要特殊考虑。

所以可以如下构造：对与圆 $i$ 首先给 $f$ 加上 $\left\lfloor\dfrac{x_i}{2}\right\rfloor\times\left(1-d+\left|1-d\right|\right)$ 然后再给 $g$ 加上 $\left\lfloor\dfrac{y_i}{2}\right\rfloor\times\left(1-d+\left|1-d\right|\right)$ 即可。

但是虽然这么构造，但是存在一个问题就是，事实上我们构造的这个函数有可能不能正好通过圆心，而是离圆心有 $1$ 左右的误差，但是因为题目保证了 $r$ 大于等于 $2$ 所以事实上我们及时距离圆心 $1$ 个单位长度，也远远小于半径，所以仍在圆内。

代码如下，仅供参考：
```
#include<iostream>
#include<cstdio>
using namespace std;
/*struct node{
	int x;
	int y;
	int r;
}a[55];*/
int n,a[55][5];
void work(int l2,int r2,int d){
    if(l2==r2){
    	printf("(%01d*abs(((1-abs((t-%d)))+abs((abs((t-%d))-1)))))",a[l2][d]/2,l2,l2);
    }
    else{
	  printf("(");
	  work(l2,(l2+r2)>>1,d);
	  printf("+");
	  work(((l2+r2)>>1)+1,r2,d);
	  printf(")");
	}
}
int main(){
    cin>>n;
    for (int i=1;i<=n;i++){
    	//cin>>a[i].x>>a[i].y>>a[i].r;
    	cin>>a[i][0]>>a[i][1]>>a[i][2];
	}
	work(1,n,0);
	cout<<"\n";
	work(1,n,1);
    return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力回答的。

---

