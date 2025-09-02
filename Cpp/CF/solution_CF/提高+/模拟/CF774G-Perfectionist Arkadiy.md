# Perfectionist Arkadiy

## 题目描述

Arkadiy has lots square photos with size $ a×a $ . He wants to put some of them on a rectangular wall with size $ h×w $ .

The photos which Arkadiy will put on the wall must form a rectangular grid and the distances between neighboring vertically and horizontally photos and also the distances between outside rows and columns of photos to the nearest bound of the wall must be equal to $ x $ , where $ x $ is some non-negative real number. Look on the picture below for better understanding of the statement.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF774G/5594570290c0b989f39a81d820befd2001debe5b.png)Arkadiy haven't chosen yet how many photos he would put on the wall, however, he want to put at least one photo. Your task is to determine the minimum value of $ x $ which can be obtained after putting photos, or report that there is no way to put positive number of photos and satisfy all the constraints. Suppose that Arkadiy has enough photos to make any valid arrangement according to the constraints.

Note that Arkadiy wants to put at least one photo on the wall. The photos should not overlap, should completely lie inside the wall bounds and should have sides parallel to the wall sides.

## 说明/提示

In the first example Arkadiy can put $ 7 $ rows of photos with $ 5 $ photos in each row, so the minimum value of $ x $ equals to $ 0.5 $ .

In the second example Arkadiy can put only $ 1 $ photo which will take the whole wall, so the minimum value of $ x $ equals to $ 0 $ .

In the third example there is no way to put positive number of photos and satisfy the constraints described in the statement, so the answer is -1.

## 样例 #1

### 输入

```
2 18 13
```

### 输出

```
0.5
```

## 样例 #2

### 输入

```
4 4 4
```

### 输出

```
0
```

## 样例 #3

### 输入

```
3 4 3
```

### 输出

```
-1
```

# 题解

## 作者：A_zjzj (赞：7)

竟然没有人做这道题

### 先理理样例

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF774G/5594570290c0b989f39a81d820befd2001debe5b.png)

设这个小正方形摆了$n$行$m$列

我们可以列出等式：

$$n\times(a+x)+x=h,m\times(a+x)+x=w$$

变形一下:

$$(n+1)\times(a+x)=h+a,(m+1)\times(a+x)=w+a$$

因为$n,m$都是整数，所以要找一个$k=(a+x)$满足:

$(h+x)\div k,(w+x)\div k$都是正整数。

那么我们先找一个最大的整数$k$

显然，$k=\gcd(h+a,w+a)$

那么，最小的$k$就可以表示成$k\div p$

所以，$\dfrac{k}{p}\ge a$

显然，$p$取$\lfloor\dfrac{k}{a}\rfloor$时最优

所以，最终的答案$ans=\dfrac{k}{\lfloor\dfrac{k}{a}\rfloor}$

### 代码

```cpp
#include<cstdio>
using namespace std;
int a,h,w;
int gcd(int x,int y){return y?gcd(y,x%y):x;}
int main(){
	scanf("%d%d%d",&a,&h,&w);
	int k=gcd(h+a,w+a);
	if(k<a||a>h||a>w)return printf("-1"),0;//判一下无解
	printf("%.7lf",(double)k/(k/a)-a);//题中说是6位那我就输出7位
	return 0;
}
```

---

## 作者：NightTide (赞：1)

先来看到样例：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF774G/5594570290c0b989f39a81d820befd2001debe5b.png)

我们将大矩形的边长都加大 $a$，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/4ew5qnhl.png)

不难发现 $h+a$ 和 $w+a$ 都能够整除 $a+x$。

我们令 $g=\gcd(h+a,w+a)$，这里的 $g$ 就是 $a+x$ 的最大值。对于所有合法的 $x$，必然有 $(a+x)|g$。令 $k=\dfrac{g}{a+x},k\in N^* $。整理得 $\dfrac{g}{k} - a = x$。若要使 $x$ 最小，则 $\dfrac{g}{k}$ 最接近 $a$。因为 $\dfrac{g}{k} \ge a$ 且 $k\in N^* $，若要使 $\dfrac{g}{k}$ 最接近 $a$，则 $k=\lfloor\dfrac{g}{a}\rfloor$。

于是答案就是 $\dfrac{g}{\lfloor\dfrac{g}{a}\rfloor}-a$。

## CODE

```cpp
#include<bits/stdc++.h>
using namespace std;
int h,w,a;
double ans;
int gcd(int a,int b){
	return b==0 ? a : gcd(b,a%b);
}
int main(){
	scanf("%d%d%d",&a,&h,&w);
	int g=gcd(h+a,w+a);
	if(g<a||a>h||a>w) printf("-1\n");
	else{
		ans=(double)g/(g/a);
		printf("%lf\n",ans-a);
	}
	return 0;
}
```



---

