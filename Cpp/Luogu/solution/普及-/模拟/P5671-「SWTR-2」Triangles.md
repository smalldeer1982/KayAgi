# 「SWTR-2」Triangles

## 题目背景

小 $\mathrm{A}$ 在学数学。

## 题目描述

他遇到了两个谜题：

- 在一个平面内，**线段** $DE$ 与**直线** $FG$ 相交于点 $O$，已知 $\angle DOF=x^{\circ}$，请你在**直线** $FG$ 上找一点 $P$，使得 $\triangle DOP$ 为**等腰**三角形，求 $\angle D$ 的度数。（如果答案不是整数，则保留 $1$ 位小数）

- 已知一个**直角三角形**的两条边分别为 $m,n$，求第三条边的长度（保留 $5$ 位小数）。

![](https://cdn.luogu.com.cn/upload/image_hosting/qjle5b4c.png)

写一个程序求出问题的答案。

## 说明/提示

---

### 样例说明

问题 $1$：

- 当点 $P$ 在点 $O$ 左边时，形成的 $\triangle DOP$ 为等边三角形，$\angle D=60^{\circ}$。

- 当点 $P$ 在点 $O$ 右边时，形成的 $\triangle DOP$ 中，$\angle DOP=180^{\circ}-60^{\circ}=120^{\circ}$，为顶角，$\angle D=(180^{\circ}-120^{\circ})/2=30^{\circ}$。

问题 $2$：

第三条边为斜边，长度为 $\sqrt{1^2+1^2}=\sqrt{2}=1.41421\dots$。

---

### 数据范围与约定

$x<90,m\leq n\leq 10^9$。

---

### 出题组提示：

**方法千万条，审题第一条，多解不考虑，爆零两行泪。**

## 样例 #1

### 输入

```
60 1 1```

### 输出

```
30 60
1.41421```

# 题解

## 作者：Alex_Wei (赞：8)

$\color{orange}T1.\ Triangles$

[$\color{orange}\text{题面}$](https://www.luogu.org/problem/P5671)

$\color{orange}\text{官方题解}$

---

**小学数学级别**

主要考察的是 $\mathrm{OIers}$ 的数学功底

暴力分：$100\%$

---

- **第一问**：

对于第一问，只有可能是以下四种答案：

$x/2\quad x\quad 180-x* 2\quad (180-x)/2$

由于 $0<x<90$，所以上面四种答案都是合法的

别忘了排序，去重

---

- **第二问**：

对于第二问，只有可能是以下两种答案

$\sqrt{n*n-m*m}\quad \sqrt{n*n+m*m}$

当 $n=m$ 时，第一种答案不存在

---

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ld double
ld x,m,n;
void solve1()
{
	vector <ld> ans;
	ans.push_back(x);
	ans.push_back(180-x*2);
	ans.push_back((180-x)/2);
	ans.push_back(x/2);
	sort(ans.begin(),ans.end());
	for(int i=0;i<ans.size();i++)
		if(i==0||ans[i]!=ans[i-1])
			cout<<ans[i]<<" ";
	puts("");
}
void solve2()
{
	ld sq1=n*n+m*m,sq2=n*n-m*m;
	if(sq2!=0)printf("%.5lf ",sqrt(sq2));//因为 sq2 一定比 sq1 小，所以我们先输出 sq2
	printf("%.5lf ",sqrt(sq1));
	puts("");
}
int main()
{
	cin>>x>>m>>n;
	solve1();
	solve2();
	return 0;
}
```


---

## 作者：LRL65 (赞：3)

这里是[官方题解](https://www.luogu.org/blog/wjz060130/swtr-02sweet-round-02-t1-triangles)。

对于SWTR，我是支持的，毕竟出题人是NFLS的，所以期盼SWTR-03.


------------
这题目主要是数学题，只要在纸上推一下就能找出答案。

### 先讲第一问：
可以推出以下四个式子：
1. x/2
1. x
1. 180-2x
1. 180-x/2

只要把这四个式子带进去算就行了。

别忘了**去重排序**。

### 再讲第二问：
只有两种可能：
1.  $\sqrt{n*n-m*m}$
1. $\sqrt{n*n+m*m}$

**当n==m时，只有第二种。**

AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
double x,a[5],b,b1,b2=0;
long long m,n;
int main(){
	cin>>x>>m>>n;
	a[1]=180-2*x;a[2]=x/2;a[3]=x;a[4]=(180-x)/2;//公式
	sort(a+1,a+5);//排序
	for(int i=1;i<=4;i++)if(a[i]!=a[i-1])cout<<a[i]<<" ";
	cout<<endl;
	b=double(m*m+n*n);//公式
	b1=sqrt(b);
	if(m!=n) {
		if(m<n)swap(m,n);
		b=double(m*m-n*n);//公式
		b2=sqrt(b);
	}
	if(b2!=0&&b1>b2)swap(b1,b2);
	printf("%.5f ",b1);
	if(b2!=0)printf("%.5f ",b2);
}
```


---

## 作者：hensier (赞：2)

本题是一道纯几何题，思维难度堪称入门。

我们先来看第一问。题目中说：

> 在一个平面内，**线段** $DE$ 与**直线** $FG$ 相交于点 $O$，已知 $\angle DOF=x^{\circ}$。

顺着题意，我们可以绘制出下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/2dnehrun.png)

接着，题目说：

> 请你在**直线** $FG$ 上找一点 $P$，使得 $\triangle DOP$ 为**等腰**三角形，求 $\angle D$ 的度数。（如果答案不是整数，则保留 $1$ 位小数）

那么，我们可以想到一个可以称作为$\color{red}\text{两圆一线}$的几何模型，也就是说，如果我们想要构造等腰三角形，而且已知两个点$A,B$，那么总共有$3$种几何图形可以构造：

1. 以$A$为圆心，$B$为半径的圆

![](https://cdn.luogu.com.cn/upload/image_hosting/38znj10f.png)

【结论】$⊙A$上的任一点到$A$点的距离与其到$B$点的距离相等

2. 以$B$为圆心，$A$为半径的圆

![](https://cdn.luogu.com.cn/upload/image_hosting/psvxqims.png)

【结论】$⊙B$上的任一点到$A$点的距离与其到$B$点的距离相等

3. $AB$的垂直平分线（中垂线）

![](https://cdn.luogu.com.cn/upload/image_hosting/o104di8s.png)

【结论】$AB$的垂直平分线上的任一点到$A$点的距离与其到$B$点的距离相等

我们可以通过上述方式得到线段相等，从而构造出等腰三角形。

接着，我们来看具体的操作（$P$的第$i$个交点用$P_i$表示，对应的$∠D$用$∠D_i$表示）：

【方法$1$】

画$⊙O$，半径为$OD$，交直线$FG$于$P_1,P_2$：

![](https://cdn.luogu.com.cn/upload/image_hosting/71q50cam.png)

连接$P_1D,P_2D$。在$⊙O$中，$OD=OP_1=OP_2$（同圆的半径相等）。$∴$△$ODP_1,$△$ODP_2$是等腰三角形。

因此$∠D_1=\dfrac{180-x}{2}^\circ,∠D_2=\dfrac{x}{2}^\circ$：

![](https://cdn.luogu.com.cn/upload/image_hosting/7xsydbvf.png)

【方法$2$】

画$⊙D$，半径为$DO$，交直线$FG$于$P_3$：

![](https://cdn.luogu.com.cn/upload/image_hosting/z8xd3p3v.png)

连接$P_3D$。在$⊙O$中，$OD=OP_3$（同圆的半径相等）。$∴$△$ODP_3$是等腰三角形。

因此$∠D_3=(180-2x)^\circ$：

![](https://cdn.luogu.com.cn/upload/image_hosting/6p1gui23.png)

【方法$3$】

画$OD$的垂直平分线交直线$FG$于$P_4$：

![](https://cdn.luogu.com.cn/upload/image_hosting/xg6vcgba.png)

连接$P_4D$。有$P_4D=P_4O$，$∴$△$ODP_4$是等腰三角形。

因此$∠D_4=x^\circ$

![](https://cdn.luogu.com.cn/upload/image_hosting/qimy876t.png)

综上所述，$∠D=\{\dfrac{180-x}{2}^\circ,\dfrac{x}{2}^\circ,(180-2x)^\circ,x^\circ\}$。

把这些数据存入数组，进行快排，然后输出大于$0$的值。因为最终所有结果乘$2$必为整数，所以每个元素要么为整数，要么是$x+0.5(x∈N+)$的形式。因此直接$\text{cout}$即可。

接着是第二问。题目中说：

> 已知一个**直角三角形**的两条边分别为 $m,n$，求第三条边的长度（保留 $5$ 位小数）。

当然，分类讨论的意识依然是要有的。

- 当$m,n$为直角边时，第三边为$\sqrt{m^2+n^2}$

- 当$n$为斜边，$m$为其中一直角边时，第三边为$\sqrt{n^2-m^2}$

因为有$m\leq n\leq 10^9$，所以上述的开方运算不会出现虚数。但是最终结果$\ge 0$，而一个三角形的所有边长$\gt 0$，所以必须考虑$m=n$的情况。

经过上述分析，我们可以得到代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int x,m,n;
double ans1[5],ans2[4];//ans1，ans2分别保存第1、2问的答案
int main()
{
    cin>>x>>m>>n;
    ans1[1]=(180-x)*0.5;
    ans1[2]=x*0.5;
    ans1[3]=x;
    ans1[4]=180-(x<<1);//按照之前的分析进行赋值
    sort(ans1+1,ans1+5);//按从小到大排序
    for(int i=1;i<5;i++)
    {
        if(ans1[i]<=0||ans1[i]>180||ans1[i]==ans1[i-1])continue;//如果该角小于0、大于180或者与前面的重复，则不输出
        cout<<ans1[i]<<" ";
    }
    putchar('\n');//换行
    ans2[1]=sqrt(1ll*m*m+1ll*n*n);//由于n和m在10的9次方范围以内，所以相乘会爆int，所以要加1ll*，否则该题会爆零
    ans2[2]=sqrt(1ll*n*n-1ll*m*m);
    sort(ans2+1,ans2+3);//快排
    for(int i=1;i<3;i++)
    {
        if(ans2[i]==0)continue;//特判等于0的情况
        printf("%.5lf ",ans2[i]);
    }
    return 0;
}
```

---

## 作者：　　　吾皇 (赞：2)

### 分析

![](https://cdn.luogu.com.cn/upload/image_hosting/qjle5b4c.png)
- 第一问

等腰三角形多种可能性讨论（△DOP）

条件：∠DOF=x（x<90就很好做了）

1. DO=OP 
   1. 此时若P在O左边，∠D=∠DPO=$\frac{1}{2}$(180-∠DOF)=90-$\frac{1}{2}$x。   
   
   2.否则∠D=$\frac{1}{2}$∠DOF=$\frac{1}{2}$x

2. DO=DP 此时∠D=180-∠DPO-∠DOF=180-2x

3. DP=OP 此时∠D=∠DOF=x

只要把它们都存到一个set里面即可（自动去重排序）

注意如果角度是整数不用保留小数

- 第二问

若m=n，显然只有一种情况，输出$sqrt(2*m*m)$即可

否则若第三条边作为直角边，长度为$sqrt(n*n-m*m)$；作为斜边，长度为$sqrt(n*n+m*m)$




### 代码
```
#include<bits/stdc++.h>
using namespace std;
int x,t1,t2;
long long m,n;
#define db double
set<db> a;
set<db>::iterator it;
inline void put(db x) {//将x存入set类型a中
	a.insert(x);
}
inline bool f(db x,int y) {//判断该数是否为整数 即它和它向下取整的差的绝对值是否几乎为0 （浮点数比较尽量不要用==）
	return abs(x-y)<0.000001;
}
int main() {
	scanf("%d%lld%lld",&x,&m,&n);
	put(x),put(180-2*x),put(90-x/2.0),put(x/2.0);//把四种可能都存入
	for(it=a.begin();it!=a.end();it++) {//遍历，判断，输出
		double l=*it;
		if(f(l,int(l))) printf("%d ",int(l));
		else printf("%.1f ",l);
	}
	puts("");//换行
	if(m==n) printf("%.5f",(sqrt(2*m*m)));
	else printf("%.5f %.5f",(sqrt(n*n-m*m)),(sqrt(n*n+m*m)));//输出可能情形
}
```

### 总结 
作为一道T1 其难度并非很大，但要注意很多细节 做的时候可以画图分析

---

## 作者：Accepted喵 (赞：0)

# 本题主要考察各位OIer的数学素养


## 第一题：
- DO=OP：
此时若P在O左边，∠D=∠DPO=½(180-∠DOF)=90-½x。

 否则∠D=½,∠DOF=½x

- DO=DP：此时∠D=180-∠DPO-∠DOF=180-2x

- DP=OP 此时∠D=∠DOF=x

- 所以只有可能是以下四种答案：

x,
x÷2,
180-x×2,
(180-x)÷2x

- **由于 0<x<90，所以上面四种答案都是合法的，最后别忘了排序&去重**


------------
## 第二题

- 第一种情况，m&n都是直角边，此时斜边长=√（m²+n²）
- 第二种情况，m是直角边，n是斜边（m≤n），此时斜边长 =√（n²-m²）
- 当 m=nm=n 时，√（n²-m²）=0，故此时第二种情况不存在。
------------
### 数据范围与约定：

**x<90，m≤n≤10⁹，不开long long见祖宗**
#  AC原码
个人比较喜欢用函数，所以不会的同学[戳这里](https://www.luogu.com.cn/paste/uxwazdih)
```cpp
#include<cmath>
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
long long n,m;
int x;
double a[5];
void yi(int x){
	a[0]=x,a[1]=x/2.0,a[2]=(180-x)/2.0,a[3]=180-2*x;
    sort(a,a+4);
    for(int i=0;i<4;i++) if(a[i]!=a[i-1])cout<<a[i]<<" ";
    cout<<endl;
}
void er(long long n,long long m){
    if(n==m) printf("%.5lf",sqrt(n*n+m*m));
    else printf("%.5lf %.5lf",sqrt(m*m-n*n),sqrt(n*n+m*m));
}
int main(){
	scanf("%d%lld%lld",&x,&n,&m);
	yi(x); 
	er(n,m);
        return 0;
} 
```
------------

**这是萌新我第一次写题解，欢迎各位大佬指正**

~~点赞关注+转发~~

---

## 作者：CLCK (赞：0)

## 前言
题目不难，专业水平不高，主要涉及初中几何问题。

## 分析
**方法千万条，审题第一条，多解不考虑，爆零两行泪。**

⬆️这个非常重要，考点之一为分类讨论。

### 问题1
直接用图说话，几种可能画出来了，稍加计算可得：
![](https://cdn.luogu.com.cn/upload/image_hosting/x194dq91.png)
(有四个答案)

$x/2$ 

$x$

$180 − x * 2$

$(180 − x) / 2$

代入数据：$ x < 90 $ 后，发现答案均合法，排序去重输出即可。

### 问题2
还是一样，这题主要用到勾股定理，图附上，两种情况。

![](https://cdn.luogu.com.cn/upload/image_hosting/v3a5fs4a.png)
那么显而易见，答案就出来了。

（顺便普及一下，大犇跳过）
勾股定理指的是对于一个直角三角形，两条直角边的平方和（注意是平方后加和），等于斜边平方。

勾股函数因为输出格式有要求，这里给出来，两种方式输出都可。

```cpp
void gg(int m, int n) {
	if (n != m) {
	    cout << fixed << setprecision(5) << sqrt(n * n - m * m) << " "; //记得iomanip和cmath头文件
	    //printf("%.5lf ", sqrt(n * n - m * m));
	}
	cout << fixed << setprecision(5) << sqrt(n * n + m * m);
	//printf("%.5lf ", sqrt(n * n + m * m));
	return ;
}
```


**完结撒花～**

---

## 作者：SqrtSecond (赞：0)

一道简单的小学奥数题。

# [第一题]
已知一等腰三角形的一角**或一角补角**为$x^{\circ}$，求另一角可能是多少。

先设另一角为$y^{\circ}$,分**五种情况**讨论；

## [情况一]

$x$与$y$皆为底角，则$y=x$；

## [情况二]

$x$为底角，$y$为顶角，则$2x+y=180^{\circ}$，解得$y=180-2x$；

## [情况三]

$x$为顶角，$y$为底角，则$x+2y=180^{\circ}$，解得$y=90-\frac{1}{2}x$；

## [情况四]

x为顶角补角，$y$为底角，则$(180-x)+2y=180^{\circ}$，解得$y=\frac{1}{2}x$

## [情况五]

$x$为底角补角，由于$x<90^{\circ}$，则底角$>90^{\circ}$，故此种情况无解。

### 温馨提示：记得排序去重！

------------


# [第二题]

给定直角三角形两边$m,n(m≤n)$，求第三边。

设第三边为$p$，则亦可分两种情况讨论。

## [情况一]

若$p$为斜边，则$p^2=m^2+n^2$，得$p=\sqrt{m^2+n^2}$；

## [情况二]

若$n$为斜边且$m≠n$，则$p^2=n^2-m^2$，得$p=\sqrt{n^2-m^2}$。



------------
上~~华丽的~~代码

```cpp
#include<bits/stdc++.h>
using namespace std;
double x,m,n,ans1[5],ans2[3];//x，m，n设成double，方便以后计算
int cnt1,cnt2;
int main()
{
	cin>>x>>m>>n;
	ans1[++cnt1]=x;
	ans1[++cnt1]=180-2*x;
	ans1[++cnt1]=90-x/2;
	ans1[++cnt1]=x/2;//计算第一题
		/* 
		ans1[1]=x;
		ans1[2]=180-2*x;
		ans1[3]=90-x/2;
		ans1[4]=x/2;
		*/
	ans2[++cnt2]=sqrt(m*m+n*n);
	if(m!=n)ans2[++cnt2]=sqrt(n*n-m*m);//计算第二题 
	sort(ans1+1,ans1+cnt1+1);
	sort(ans2+1,ans2+cnt2+1);//排序 
	for(int i=1;i<=cnt1;++i)
	{
		if(ans1[i]==ans1[i-1])continue;//去重 
		cout<<ans1[i]<<" "; 
	}
	cout<<endl;//换行 
	for(int i=1;i<=cnt2;++i)
	{
		if(ans2[i]==ans2[i-1])continue;
		printf("%.5f ",ans2[i]);//同上 
	}
	return 0;//需要return 0，不然会UKE 
}
```


---

## 作者：Daidly (赞：0)

# STEP1
首先我们先看第一个小问，第一问它可以有多个答案，这个需要用到外角定理和等腰三角形的性质。一个外角等于与它不相邻两角之和，等腰三角形的两边相等，它们的底角也相同。这样我们就可以判断出来四种情况，分别是：$x,x/2,(180-x)/2,180-x* 2$，然后从小到大输出就行。
# STEP2
第二问主要牵扯到一个勾股定理，两直角边的平方等于斜边的平方，所以我们要判断两个边是两个直角边，还是一个直角边和一个斜边。所以可能会有两个答案，或者有一个答案。最多有两个，然后我们就可以挑选出共同的那一刻输出，然后再判断另外一个有没有。
# STEP3
```
#include<bits/stdc++.h>//万能头文件
using namespace std;
double m,n,a[4];//定义m，n和一个数组
int x;
int main(){
	cin>>x>>m>>n;
	a[0]=x;//分别把这四个答案录入四个数组中
	a[1]=a[0]/2;
	a[2]=(180-a[0])/2;
	a[3]=180-a[0]*2;
	sort(a,a+4);//从大到小排序
	double t=a[0];
	cout<<t;//输出最小的
	for(int i=1;i<4;++i){//然后一一比较
		if(a[i]!=t){
			cout<<" "<<a[i];
			t=a[i];
		}
	}
	cout<<endl;
	double ans;
	if(n>m){//因为最多有两个答案，所以我们只需要判断其中一个答案，然后输出共同的那个答案
		ans=sqrt(n*n-m*m);
		printf("%.5lf ",ans);//保留5位小数
	}
	ans=sqrt(n*n+m*m);
    printf("%.5lf\n",ans);//保留5位小数
	return 0;
} 
```
完美结束！

---

