# Intersection

## 题目描述

You are given two set of points. The first set is determined by the equation $ A_{1}x+B_{1}y+C_{1}=0 $ , and the second one is determined by the equation $ A_{2}x+B_{2}y+C_{2}=0 $ .

Write the program which finds the number of points in the intersection of two given sets.

## 样例 #1

### 输入

```
1 1 0
2 2 0
```

### 输出

```
-1
```

## 样例 #2

### 输入

```
1 1 0
2 -2 0
```

### 输出

```
1
```

# 题解

## 作者：ahawzlc (赞：3)

本题需掌握知识：~~一次函数相关知识、分支结构~~。

要想考虑全面确实起码绿的难度，再加上 if 不写乱，蓝题也是差不多的罢（个人向）。

----

考虑各种情况，我们一 一分析：

1. 有一个式子三个系数都是0：很显然无论 x,y 取何值，0=0 这个恒等式绝对成立，那么这个式子是覆盖整个坐标系的，肯定有无限个点重合，```-1```石锤。
2. 有一个式子 a,b 两系数为0，c不为0：很显然这个式子无解，所以绝对没有重合，```0```石锤。
3. **在上述均不满足的条件下**，有一个式子 b 系数为0：此时该直线平行于 y 轴，另一条直线一定会与它相交。
4. 在两个式子的 b 均为0的情况下：
	1. 有一个式子 a 为0 但c不为0，同2.所述。
    2. 两个式子 c都为0 或 a都为0 或 a,c 成比例关系，说明两直线重合，输出```-1```。
    3. 剩余情况肯定平行或无解，```0```石锤。
5. **在上述均不满足且a,b成比例关系时**：
	1. 如果 b,c 也成比例关系，说明两直线重合，```-1```走人。
    2. 肯定平行。
6. 肯定相交。

~~心态差点炸了~~

注意：因为涉及到除法运算，建议使用```float```或```double```类型存储六个数据。

``` cpp
#include<bits/stdc++.h>
using namespace std;
double a1,b1,c1,a2,b2,c2;
int solve() {
	if(b1||b2) {
		if((!a1&&!b1&&!c1)||(!a2&&!b2&&!c2)) return -1;
		if((!a1&&!b1)||(!a2&&!b2)) return 0;
		if(!b1||!b2) return 1;
	} else {
		if((!a1&&c1)||(!a2&&c2)) return 0;
		if(!(c2||c1)||!(a2||a1)||a1/c1==a2/c2) return -1;
		return 0;
	}
	if(a1/b1==a2/b2) {
		if(c1/b1==c2/b2) return -1;
		return 0;
	}
	return 1;
}
int main() {
	cin>>a1>>b1>>c1>>a2>>b2>>c2;
	cout<<solve();
	return 0;
}
```
代码还是很短的，~~但是调好有点难~~。

另：可以使用[desmos](https://www.desmos.com/calculator)帮助理解。

---

## 作者：离散小波变换° (赞：3)

## 题目大意

两个点集 $P=\{(x,y)|A_1x+B_1y+C_1=0\}$，$Q=\{(x,y)|A_2x+B_2y+C_2=0\}$，求 $P\cap Q$ 的元素个数。如果有无穷个元素，输出 $-1$。

## 题解

非常初级的计算几何，但是要特判的地方有一点多……


给出的两个集合，都是直线的标准式 $Ax+By+C=0$ 的形式。但这并不意味着两个都是直线。因此需要分别考虑。为了方便下面的讨论，我们设全集 $U=\{(x,y)|x\in R,y\in R\}$，也就是平面上**所有**点的集合；空集为 $\varnothing$。

### $\textbf{1.P,Q}$ 存在一个不是直线

$Ax+By+C=0$ 不是直线，当且仅当 $A=B=0$。

显然，如果 $C=0$，那么该集合为 $U$；否则，如果 $C\ne 0$，那么就是 $\varnothing$。

如果存在一个集合是空集，那么显然结果是 $0$，因为空集与任何集合的交都为空；否则如果存在一个集合为 $U$，那么答案为 $-1$。因为只要有一个集合为全集 $U$，那么他与另外一个集合的交就是另外一个集合本身。而无论是直线集还是全集，它的元素个数都是无穷大。

### $\textbf{2.P,Q}$ 均为直线

这一部分内容相对容易判断，因为两条直线之间的关系只有**三**种情况：相交，平行，和**重合**。

有一个结论是，如果$P,Q$各项系数都不为零，那么 $P,Q$ 平行当且仅当 $\frac{A_1}{A_2}=\frac{B_1}{B_2}\ne \frac{C_2}{C_2}$。

关于这个式子的证明，我们可以将原来的标准式化为斜截式（即经典的 $y=kx+b$ 的形式），然后我们发现 $P=-\frac{A_1}{B_1}x+\frac{C_1}{B_1},Q=-\frac{A_2}{B_2}x+\frac{C_2}{B_2}$。两直线平行必有斜率相等，且 $y$ 轴上的截距不等。即 $\frac{A_1}{B_1}= \frac{A_2}{B_2},\frac{C_1}{B_1}\ne \frac{C_2}{B_2}$，化简就能得到上式。

关于系数为 $0$ 的特殊情况，可以分类讨论。这里不详细展开。

最后，我们能够得到这样的一个式子，$P/\!\!/Q$，当且仅当：

$$A_1\times B_2=A_2\times B_1\text{且}A_1\times C_2\ne A_2\times C_1\text{且}B_1\times C_2\ne B_2\times C_1$$

平行时，无交点，答案为 $0$；重合时，无穷个交点，答案为 $-1$；相交时，答案为 $1$。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define up(l,r,i) for(int i=l;i<=r;i++)
#define dn(l,r,i) for(int i=l;i>=r;i--)
using namespace std;

typedef long long LL;
const int INF =2147483647;
int qread(){
    int w=1,c,ret;
    while((c=getchar())> '9'||c< '0')
    w=(c=='-'?-1:1); ret=c-'0';
    while((c=getchar())>='0'&&c<='9')
    ret=ret*10+c-'0';
    return ret*w;
}
int a1,a2,b1,b2,c1,c2,f1,f2;
int main(){
    a1=qread(),b1=qread(),c1=qread();
    a2=qread(),b2=qread(),c2=qread();
    if(a1==0&&b1==0&&c1==0) f1= 1; else
    if(a1==0&&b1==0&&c1!=0) f1=-1;
    if(a2==0&&b2==0&&c2==0) f2= 1; else
    if(a2==0&&b2==0&&c2!=0) f2=-1;
    if(f1==-1||f2==-1) puts("0"); else
    if(f1== 1||f2== 1) puts("-1");else
    if(b1*a2-a1*b2!=0) puts("1"); else
    if(a1*c2==a2*c1&&b1*c2==b2*c1) puts("-1");
    else puts("0");
    return 0;
}
```

---

## 作者：XL4453 (赞：0)

### 解题思路：

这题的细节，真是够了。

思路很显然，就是一个一次函数相交、重合、平行的判断。

下面将所有的细节列出来：

1. 直线变为一条与坐标轴平行的线，此时 $a=0$ 或 $b=0$，这时需要另一条线也与坐比标轴平行或者与这一条线平行的情况。

2. 直线消失，不存在任何一个点满足方程，此时 $a=b=0$ 且 $c\ne 0$，这种情况下无论另一条直线是什么样的，都一定没有交点。

3. 直线变为整个平面，此时 $a=b=c=0$，这种情况下只要另一条直线没有消失，都是有无数个交点的。

4. 如果用 int 读入，记得强制类型转换成 double。

---
### 代码：

```cpp
#include<cstdio>
#include<cmath>
using namespace std;
int a,b,c,aa,bb,cc;
int main(){
	scanf("%d%d%d%d%d%d",&a,&b,&c,&aa,&bb,&cc);
	if(b==0||bb==0){
		if(bb==0&&aa==0&&cc!=0){printf("0\n");return 0;}
		if(b==0&&a==0&&c!=0){printf("0\n");return 0;}
		if(b==0&&a==0&&c==0){printf("-1\n");return 0;}
		if(bb==0&&aa==0&&cc==0){printf("-1\n");return 0;}
		if(b+bb!=0){printf("1\n");return 0;}
		if(a*cc==aa*c){printf("-1\n");return 0;}
		printf("0");return 0;
	}
	double k=-(double)a/(double)b,kk=-(double)aa/(double)bb,
	x=-(double)c/(double)b,xx=-(double)cc/(double)bb;
	if(abs(kk-k)<=1e-9){
		if(abs(x-xx)<=1e-9){
			printf("-1");
			return 0;
		}
		else{
			printf("0");
			return 0;
		}
	}
	printf("1");
	return 0;
}
```



---

## 作者：叶枫 (赞：0)

## 写在前面

这种题不应该一遍$A$么？![youl.png](https://i.loli.net/2019/09/22/HoAmLlPhrty6VG3.png)![youl.png](https://i.loli.net/2019/09/22/HoAmLlPhrty6VG3.png)

# $Idea$

这是一道数学题。

答案会有`0(平行),1(相交),-1(重合)`，三种

代码中注释![youl.png](https://i.loli.net/2019/09/22/HoAmLlPhrty6VG3.png)

# $Code$

```cpp
//可能是写法问题，跑的很慢；或许是我自带常数极大（雾？
namespace Sol{
	int a1,b1,c1,a2,b2,c2;
	inline int check(){
	    if((a1==0&&b1==0&&c1!=0)||(a2==0&&b2==0&&c2!=0)) return 0;
	    int f=1;//只有0个（平行），1个（相交），-1(无限)；
	    if((a2==0&&b2==0)||(a1==0&&b1==0)) return -1;//任意一点；
	    else if(a1!=0&&b1!=0){//有斜率；
	        if(a2!=0&&b2!=0){
	            if(a1*b2==a2*b1){//斜率相同
	                if(c1*b2==c2*b1) return -1;//过同一点说明重合；
	                else f=0;//斜率相同不过同一点说明平行；
	            }
	        }
	    }
	    else{
	        if(a1==0&&b1!=0){//一条横线；
	            if(a2==0&&b2!=0){
	                if(c2*b1==c1*b2) f=-1;//过同一点；
	                else f=0;
	            }
	        }
	        else{//一条竖线；
	            if(a2!=0&&b2==0){
	                if(c2*a1==c1*a2) f=-1;//过同一点；
	                else f=0;
	            }
	        }
	    }
	    return f;
	}
	inline int Main(){
		a1=read(); b1=read(); c1=read(); 
		a2=read(); b2=read(); c2=read();
		int f=check();
        printf("%d",f);
		return 0;
	} 
}
```

$$
\mathcal The \quad End
$$

$$
\text{我们都是小怪兽,有一天会被正义的奥特曼杀死。-《龙族》上杉绘梨衣(原谅我的臭屁~~)}
$$



---

