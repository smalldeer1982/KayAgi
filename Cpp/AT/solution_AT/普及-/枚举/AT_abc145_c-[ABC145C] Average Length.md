# [ABC145C] Average Length

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc145/tasks/abc145_c

座標平面上に $ N $ 個の町があります。町 $ i $ は、座標 ( $ x_i $ , $ y_i $ ) に位置しています。町 $ i $ と町 $ j $ の間の距離は $ \sqrt{\left(x_i-x_j\right)^2+\left(y_i-y_j\right)^2} $ です。

これらの町を全て $ 1 $ 回ずつ訪れるとき、町を訪れる経路は全部で $ N! $ 通りあります。$ 1 $ 番目に訪れる町から出発し、$ 2 $ 番目に訪れる町、$ 3 $ 番目に訪れる町、$ \ldots $、を経由し、$ N $ 番目に訪れる町に到着するまでの移動距離 (町から町への移動は直線移動とします) を、その経路の長さとします。これらの $ N! $ 通りの経路の長さの平均値を計算してください。

## 说明/提示

### 制約

- $ 2\ <\ =\ N\ <\ =\ 8 $
- $ -1000\ <\ =\ x_i\ <\ =\ 1000 $
- $ -1000\ <\ =\ y_i\ <\ =\ 1000 $
- $ \left(x_i,\ y_i\right)\ \neq\ \left(x_j,\ y_j\right) $ ( $ i\ \neq\ j $ のとき)
- (21:12 追記) 入力中の値はすべて整数である。

### Sample Explanation 1

町を訪れる経路は $ 1 $ → $ 2 $ → $ 3 $ , $ 1 $ → $ 3 $ → $ 2 $ , $ 2 $ → $ 1 $ → $ 3 $ , $ 2 $ → $ 3 $ → $ 1 $ , $ 3 $ → $ 1 $ → $ 2 $ , $ 3 $ → $ 2 $ → $ 1 $ の $ 6 $ 通りです。 このうち、経路 $ 1 $ → $ 2 $ → $ 3 $ の長さは、$ \sqrt{\left(0-1\right)^2+\left(0-0\right)^2}\ +\ \sqrt{\left(1-0\right)^2+\left(0-1\right)^2}\ =\ 1+\sqrt{2} $ となります。 同様に他の経路についても長さを計算すると、経路の長さの平均値は、 $ \frac{\left(1+\sqrt{2}\right)+\left(1+\sqrt{2}\right)+\left(2\right)+\left(1+\sqrt{2}\right)+\left(2\right)+\left(1+\sqrt{2}\right)}{6}\ =\ 2.276142... $ であると分かります。

### Sample Explanation 2

町を訪れる経路は $ 1 $ → $ 2 $ , $ 2 $ → $ 1 $ の $ 2 $ 通りありますが、これらの経路の長さは一致します。

## 样例 #1

### 输入

```
3
0 0
1 0
0 1```

### 输出

```
2.2761423749```

## 样例 #2

### 输入

```
2
-879 981
-866 890```

### 输出

```
91.9238815543```

## 样例 #3

### 输入

```
8
-406 10
512 859
494 362
-955 -475
128 553
-986 -885
763 77
449 310```

### 输出

```
7641.9817824387```

# 题解

## 作者：_IcyFire (赞：1)

### 题意简述
------------

给定一个整数 $n$，代表有 $n$ 个点。

给出 $n$ 对数，每一对数有两个数 $x_i,y_i$ 组成，代表每个点的坐标。

任意两个点之间都有路径，路径等于两点之间的**欧几里得距离**。

问求 $n!$ 条边遍历所有点各一遍的路径总长度的平均值。

题目翻译中没写到的是，最终输出保留 $10$ 位小数。

### 解题思路
------------

首先，我们知道**欧几里得距离**的求法如下：

$$dis_{i \to j} = \sqrt{(x_i - x_j)^2 + (y_i-y_j)^2}$$

在第 $i$ 次输入时，我们要记录下 $x_i,y_i$，然后 $1 \to (i-1)$ 遍历一遍，在第 $j$ 个点上，让 $ans$ 累加上 $dis_{i \to j}$。

因为题目要的是平均距离，所以输出 $\dfrac{ans}{n}$？

不是，应该要输出 $\dfrac{2 \times ans}{n}$。

因为题目要求的是 $n!$ 条边，每个点之间有 $\dfrac{[1+(n-1)] \times (n-1)}{2}$，化简得 $\dfrac{n^2-n}{2}$，这样平均到每条边上有 $\dfrac{n^2-n}{2} \times n!$，化简得 $(n-1)! \times 2$。

所以最终输出 $\dfrac{2 \times ans}{n}$ 即可。



### 代码实现
------------

``` cpp
#include<bits/stdc++.h>
using namespace std;
int n; double x[10005],y[10005],ans;
double dis(double x1,double x2,double y1,double y2) {
	return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;i++) {
		scanf("%lf%lf",&x[i],&y[i]);
		for(int j=1;j<i;j++) ans+=dis(x[i],x[j],y[i],y[j]);
	}
	printf("%.10lf",ans*2/n);
	return 0;
}
//code by _IcyFire
```

---

## 作者：yeshubo_qwq (赞：1)

思路：

先求出每条边用了几次。

因为遍历所有点各一遍共用了 $n! \times \left( n-1 \right)$ 条边（遍历条数乘每次遍历边数），而任意两点之间一共有 $n \times \left( n-1 \right) \div2$ 条边，平均分给每一条边就是 $n! \times \left( n-1 \right) \div \left[ n \times \left( n-1 \right) \div2 \right]$，化简得出每条边用了 $\left( n-1 \right)!\times2$ 次。

设每条边长度之和为 $s$，答案就是 $s\times\left( n-1 \right)!\times2 \div n!=s \times2 \div n$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,i,j;
double s,x[10],y[10];
signed main(){
	scanf("%d",&n);
	for (i=1;i<=n;i++){
		scanf("%lf%lf",&x[i],&y[i]);
		for (j=1;j<i;j++)
			s+=sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
	}
	return printf("%.10lf",s*2/n),0;
}
```


---

## 作者：Ninelife_Cat (赞：0)

### 题目大意：

有 $n$ 个点，每两个点之间都有路径，路径长度为它们的欧几里得距离。

求 $n!$ 条遍历所有点各一遍的路径总长度的平均值。

### 思路：

模拟。

我们可以将 $1$ 到 $n$ 的排列用一个数组记录下来，然后用 STL 中的 ```next_permutation``` 函数实现全排列来模拟每次经过的点的顺序，累加答案并计算即可。


### 核心代码

```
const int N=11;
int n,a[N],fac[N];//fac为阶乘数组,a数组记录点的编号
double ans,x[N],y[N];
inline double dis(double x,double y,double tx,double ty) 
{return sqrt((tx-x)*(tx-x)+(ty-y)*(ty-y));}
//计算欧几里得距离
signed main()
{
	n=read();fac[0]=1;
	for(ri int i=1;i<=n;++i)
		a[i]=i,x[i]=read(),y[i]=read(),fac[i]=fac[i-1]*i;
	do
		for(ri int i=2;i<=n;++i)
			ans+=dis(x[a[i]],y[a[i]],x[a[i-1]],y[a[i-1]]);
	while(next_permutation(a+1,a+n+1));
	cout<<fixed<<setprecision(12)<<ans/fac[n];//取平均值
	return 0;
}

---

