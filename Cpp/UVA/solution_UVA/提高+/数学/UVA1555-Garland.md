# Garland

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=448&page=show_problem&problem=4330

[PDF](https://uva.onlinejudge.org/external/15/p1555.pdf)

# 题解

## 作者：lemir3 (赞：3)

最近有人问我这个题这么做，光讲几句貌似没什么用，干脆发个题解吧（~~话说什么有人会来问我这个蒟蒻~~）

题面的意思大概就是说每个点的高度都和旁边2个点有关，整张图没有高度小于0的点,求最后一个点B的最低值

是不是长得像个数学题？所以我们用数学的方法来思考一下Hi怎么得出。

题目中说过，Hi = (H[i−1] + H[i+1])/2-1，也就是已知旁边的2个点，就可以求出中间的点2，因为表达式已知，所以我们可以通过其中2个点求出第3个点。

简单地推一推：设第1个点为a,第2个点为b，第3个点为c，已知a,b。

∵b=(a+c)/2-1;

∴2b+2=a+c

∴2b+2-a=c
  
这样一来，我们就可以通过前面的点直接推出后面的点了！所以我们就只需要找出使B最低并且每个点都>=0的第2个点就可以了qwq

现在我们已经知道了B点的高度和第2点相关了，但是要求出B的最低的值，该怎么确定第2个点的值呢？

遇到这种在条件中求最值问题，首先想到的肯定是二分。因为二分可以不断地缩小查找范围，最终缩小到不满足条件与满足条件之间，也就是最~~浪~~小的值了。

细节部分直接看代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const double mina=1e-6;
int n;
double a,l,r,mid,lp[1010];
bool judge(double x)//每次二分暴力的判断一下是否有点小于0
{
    lp[1]=a;
    lp[2]=x;
    for(int i=3;i<=n;i++)
    {
        lp[i]=2*lp[i-1]-lp[i-2]+2;
        if(lp[i]<0)return false;
    }
    return true;
}
int main()
{
    
    while(scanf("%d%lf",&n,&a)!=EOF)//这句话记住就好，貌似只在洛古上有用（哪位大佬告诉我是不是Linux的原因）
    {	
        for(int i=0;i<=1009;i++)lp[i]=0.00;
        l=a/2-1;//这里可以优化一下二分的范围，因为这个值刚好使第3个点为0
        r=a;//随便设个高一点的值即可
        while(r-l>mina)//保证精度
        {
            mid=(l+r)/2;
            if(judge(mid)==true)r=mid;//满足的话就可以再小一点
            else l=mid;//不满足的话就增大
        }
        printf("%0.2lf\n",fabs(lp[n]));
        getchar();//读走回车
    }
return 0;
}//看懂了记得点赞QWQ
```

---

## 作者：_maojun_ (赞：1)

提供一种复杂度更优的做法。

---

推式子。

已知 $f_1=a$，设 $f_2=b$。

由 $f_i=\dfrac{f_{i-1}+f_{i+1}}2-1$，得 $f_{i+1}=2f_i-f_{i-1}+2$。

当 $i\ge3$ 时，观察一些性质。

考虑 $a,b$ 的系数，把前几项写写发现分别是 $-i+2$ 和 $i-1$。

再看常数项，设为 $x_i$，则：

$x_i=\begin{cases}0&i\in\{1,2\}\\2x_{i-1}-x_{i-2}+2&i\ge3\end{cases}$

列出前几项：$0,0,2,6,12,20,30,42,\dots$

发现当 $i\ge3$ 时 $x_i=(i-1)(i-2)$

于是可以得到 $f_i=(-i+2)a+(i-1)b+(i-1)(i-2)$。

取 $i=n$，则 $B=f_n=(-n+2)a+(n-1)b+(n-1)(n-2)$，所以 $b$ 越小 $B$ 越小。

考虑二分 $b$，当 $b$ 确定的时候 $f_i=i^2+(-a+b-3)i+2a-b+2$。

题目里要求 $f_i\ge0$，但注意这里的 $i$ 是自然数而不是实数，所以 $f_i\ge0$ 不一定等价于 $\Delta\le0$。这里应该判断距离函数的最小点 $\dfrac{a-b+3}2$，最近的两个整数（向上取整和向下取整）的函数是否大等 $0$。

注意如果 $\left\lceil\dfrac{a-b+3}2\right\rceil<3$ 则只用检验 $3$，因为这时候函数值在 $[3,n]$ 是单增的。

同理当 $\left\lfloor\dfrac{a-b+3}2\right\rfloor>n$ 时只用比较 $n$。

因为 $f_3=2b-a+3\ge0$ 所以 $b\ge\dfrac a2-1$，上界定到 $a$，因为这是一个二次函数，如果 $a<b$ 则说明在 $[1,n]$ 间 $f_i$ 单增，一定时不优的。

于是可以做到每组测试的复杂度 $O(\log a)$。

注意特判一下 `-0.00`，在这里卡了好久。

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
using namespace std;

typedef double db;
const db eps=1e-7;
int n;db A;

inline db f(int x,db B){return x*x+(-A+B-3)*x+2*A-B+2;}
inline bool check(int x,db B){return f(x,B)>-eps;}	// 判断当 f(x) 是否大等 0
inline bool check(db B){
	db pos=(A-B+3)/2;
	int l=floor(pos),r=ceil(pos);					// 检验极值点两边的整点
	if(r<3)return check(3,B);
	if(l>n)return check(n,B);
	return check(l,B)&&check(r,B);
}
inline db binary_search(){
	db l=A/2-1,r=A,mid;
	while(r-l>eps){
		mid=(l+r)/2;
		if(check(mid))r=mid;
		else l=mid;
	}
	return l;
}
int main(){
	while(scanf("%d%lf",&n,&A)!=EOF){
		db res=f(n,binary_search());
		if(res<eps)printf("0.00\n");				// 特判 -0.00
		else printf("%.2lf\n",res);
	}
	return 0;
}
```

---

## 作者：Big_Yi (赞：0)

upd on October 12, 2024：之前的代码忽略了有多组数据的问题、可能存在精度不准的问题等，现在的代码保证 [AC](https://www.luogu.com.cn/record/181647646)。

## 二分查找
主要就是根据
$$
H_i=A,H_i=(H_{i-1}+H_{i+1}) \div2-1
$$
变形得到
$$
H_i=2 \times H_{i-1}-H_{i-2}+2
$$

然后就只要保证
$$
H_i>0 (1<i \le n),H_n=B
$$
即可。

因为 $H_1=A$，根据公式可以选择二分第二个点的高度，范围是 0 到一个比较大的值，比如说 10000000，或者 inf，多循环几次以增加精度。


------------


最后附上代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
double h[10005];
int n;
double a;
double b;
bool judgemid(double mid){
  h[1]=a;
	h[2]=mid;
	for(int i=3;i<=n;i++){
		h[i]=2*h[i-1]-h[i-2]+2;
		if(h[i]<0.000001){//精度问题，一般不能直接和0比较
			return 0;//上升
		}
	}
	b=h[n];
	return 1;//下降
}
int main(){
	while(cin>>n>>a){
		double left=0.0,right=1000000.0,mid;
		for(int i=0;i<=1009;i++){
			mid=left+(right-left)/2;//防超出范围
			if(judgemid(mid))right=mid;
			else left=mid;
		}
		printf("%.2f\n",h[n]);//保留两位小数
	}
	return 0;
}
```

---

