# 【模板】高精度乘法 | A*B Problem 升级版

## 题目背景

本题数据已加强，请使用 FFT 或分治乘法。

## 题目描述

给你两个正整数 $a,b$，求 $a \times b$。

## 说明/提示

【数据范围】   
$1\le a,b \le 10^{1000000}$

可能需要一定程度的常数优化。  
数据由 NaCly_Fish 重造

## 样例 #1

### 输入

```
83517934
327830610
```

### 输出

```
27379735249159740
```

# 题解

## 作者：Trilarflagz (赞：703)

[博客食用更佳哦QAQ](https://blog.csdn.net/Flag_z/article/details/99163939)
# 前言
昨天学了一晚上，终于搞懂了FFT。希望能写一篇清楚易懂的题解分享给大家，也进一步加深自己的理解。
FFT算是数论中比较重要的东西，听起来就很高深的亚子。但其实学会了（哪怕并不能完全理解)，会实现代码，并知道怎么灵活运用 ~~（背板子）~~ 就行。接下来进入正题。

# 定义
**FFT（Fast Fourier Transformation）**，中文名**快速傅里叶变换**，是离散傅氏变换的快速算法，它是根据离散傅氏变换的奇、偶、虚、实等特性，对离散傅立叶变换的算法进行改进获得的。

而在信奥中，一般用来**加速多项式乘法**。
朴素高精度乘法的时间为$O(n^2)$，但FFT能将时间复杂度降到 $O(nlog_2n)$

学习FFT之前，需要了解一些有关**复数**和**多项式**的知识。
# 有关知识
## 多项式的两种表示方法
### 系数表示法
$F[x]=y=a_0x^0+a_1x^1+a_2x^2+......a_nx^n$        

{$a_0,a_1,a_2,...,a_n$} 是这个多项式每一项的系数，所以这是*多项式的系数表示法*
### 点值表示法
在函数图像中，$F[x]$这个多项式可以被n个点唯一确定，即代入n个点作为$x$,分别解出对应的 $y$，得到n个式子。
把这n条式子联立起来成为一个有n条方程的n元方程组，每一项的系数都可以解出来.（可类比二元一次方程）

也就是说，使用{$(x_0,f[x_0])$,$(x_1,f[x_1])$,...,$(x_n,f[x_n])$}就可以完整描述出这个多项式,这就是 *多项式的点值表示法*
## 多项式相乘
设两个多项式分别为$f(x)$,$g(x)$,我们要把这两个多项式相乘 (即求卷积)。

如果用**系数表示法**:
我们要枚举$f$的每一位的系数与$g$的每一位的系数相乘，多项式乘法时间复杂度$O(n^2)$，这也是我们所熟知的高精度乘法的原理。

如果用**点值表示法**:

$f[x]$={$(x_0,f[x_0])$,$(x_1,f[x_1])$,...,$(x_n,f[x_n])$}

$g[x]$={$(x_0,g[x_0])$,$(x_1,g[x_1])$,...,$(x_n,g[x_n])$}

$f[x]*g[x]$={$(x_0,f[x_0]*g[x_0])$,$(x_1,f[x_1]*g[x_1])$,...,$(x_n,f[x_n]*g[x_n])$}

我们可以发现，如果两个多项式取相同的$x$，得到不同的$y$值，那么只需要$y$值对应相乘就可以了！

复杂度只有枚举$x$的$O(n)$ 

那么问题转换为将多项式系数表示法转化成点值表示法。

朴素**系数转点值**的算法叫**DFT（离散傅里叶变换）**,优化后为**FFT（快速傅里叶变换）**，**点值转系数**的算法叫**IDFT（离散傅里叶逆变换）**，优化后为**IFFT(快速傅里叶逆变换**)。之后我会分别介绍。
## 卷积
~~其实不理解卷积也没关系，但这里顺便提一下，可以跳过的~~ 
 卷积与傅里叶变换有着密切的关系。利用一点性质，即两函数的傅里叶变换的乘积等于它们卷积后的傅里叶变换，能使傅里叶分析中许多问题的处理得到简化。
 
 $F(g(x)*f(x)) = F(g(x))F(f(x))$

其中F表示的是**傅里叶变换**          
## 复数
高中数学会详细讲解，知道的可以跳过这一部分，没学过也没关系，看以下内容应该能很清楚的理解。
### 1.定义
数集拓展到实数范围内，仍有些运算无法进行。比如判别式小于0的一元二次方程仍无解，因此将数集再次扩充，达到复数范围。

**复数**$z$被定义为二元有序实数对$(a,b)$,记为$z=a+bi$,这里$a$和$b$是实数，规定$i$是虚数单位。 
($i^2=-1$  即$i=\sqrt{-1}$)

对于复数$z=a+bi$。实数$a$称为复数z的**实部(real part)**,记作$rez=a$.实数$b$称为复数z的**虚部(imaginary part**)记作 Imz=b.

当虚部等于零时，这个复数可以视为**实数**。
即当$b=0$时，$z=a$,这时复数成为实数；当且仅当$a=b=0$时，它是实数0；

当z的虚部不等于零时，实部等于零时，常称z为**纯虚数**。
即当$a=0$且$b≠0$时，$z=bi$，我们就将其称为纯虚数。

将复数的实部与虚部的平方和的正的平方根的值称为该**复数的模**，记作$∣z∣$。

即对于**复数z=a+bi**，它的模为$∣z∣=\sqrt{(a^2+b^2)}$
### 2.复数的几何意义
直接两张图搞定√ ~~(应该可以一目了然)~~ 
![在这里插入图片描述](https://img-blog.csdnimg.cn/20190811100118403.PNG?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0ZsYWdfeg==,size_16,color_FFFFFF,t_70)
![在这里插入图片描述](https://img-blog.csdnimg.cn/2019081109564340.PNG?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0ZsYWdfeg==,size_16,color_FFFFFF,t_70)

### 3.运算法则
**加法法则**:$(a+bi)+(c+di)=(a+c)+(b+d)i;$
**减法法则**:$(a+bi)-(c+di)=(a-c)+(b-d)i;$
  注：复数加减满足**平行四边形法则**：

![在这里插入图片描述](https://img-blog.csdnimg.cn/20190811100516641.png)

**乘法法则**:$(a+bi)·(c+di)=(ac-bd)+(bc+ad)i$

复数相乘一个重要法则：**模长相乘，幅角相加**。（这个定理很重要）

**模长**：这个向量的模长，即这个点到原点的距离。（不懂的可再看下向量的几何意义）。

**幅角**:  从原点出发、指向x轴正半轴的射线绕原点逆时针旋转至过这个点所经过的角。

在极坐标（可看成平面直角坐标系）下，复数可用模长r与幅角θ表示为$(r,θ)$。
对于复数$a+bi$,  $r=\sqrt{a^2+b^2}$，$θ=arctan(b/a)$。此时，复数相乘表现为模长相乘，幅角相加。

**除法法则**：$(a+bi)÷(c+di)=[(ac+bd)/(c²+d²)]+[(bc-ad)/(c²+d²)]i$
### 4. 共轭复数
一个复数$z=a+bi$的**共轭复数**为$a−bi$（实部不变，虚部取反），记为 $\overline{z}=a-bi$ 
。当复数**模为1**时（即|z|=1），与共轭复数互为**倒数**

证明：$z*\overline{z}=a^2-b^2*i^2=a^2+b^2=|z|^2=1$
# FFT加速多项式乘法
由于多项式乘法用点值表示比用系数表示快的多，所以我们先要将**系数表示法**转化成**点值表示法**相乘，再将结果的**点值表示法**转化为**系数表示法**的过程。

第一个过程叫做**FFT（快速傅里叶变换)**，第二个过程叫**IFFT（快速傅里叶逆变换）**
在讲这两个过程之前，首先了解一个概念：
## 单位根
复数$\omega$满足$\omega^n=1$，称$\omega$是**n次单位根**
### 怎么找单位根？
**单位圆**:圆心为原点、1为半径的圆
把**单位圆n等分**，取这n个点（或点表示的向量）所表示的**复数**（即分别以这n个点的横坐标为实部、纵坐标为虚部，所构成的虚数），即为**n次单位根**。

下图包含了当n=8时，所有的8次单位根，分别记为$\omega_8^1,\omega_8^2.....,\omega_8^8$
(图中圆的半径是1，w表示$\omega$,且下标8已省略） 

~~图是我自己画的，可能有点丑QWQ~~ 
![单位根图像byTrilarflagz](https://img-blog.csdnimg.cn/20190811112251133.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0ZsYWdfeg==,size_16,color_FFFFFF,t_70)
由此我们知道如何找单位根啦
从点(1,0)开始（即$\omega_n^1$）,逆时针将这n个点从0开始编号，第k个点对应的虚数记作$\omega_n^k$

由复数相乘法则：**模长相乘幅角相加**​	
可得：

$$(\omega_n^1)^k=\omega_n^k$$ 

根据每个复数的幅角，可以计算出所对应的点/向量。
$\omega_n^k$对应的点/向量是

(cos⁡$\frac{k}{n}2π$,sins⁡$\frac{k}{n}2π$)，即为复数 cos⁡⁡$\frac{k}{n}2π$+i sin⁡$\frac{k}{n}2π$

 ### 单位根的性质
 建议记住，因为对之后的分析很重要！！

#### 1.$\omega_n^k=\omega_{2n}^{2k}$
####  2.$\omega_n^k=-\omega_{n}^{k+\frac n 2}$
#### 3.$\omega_n^0=\omega_{n}^n=1$
至于怎么证明，就是复数相乘时模长相乘幅角相加的原则。或者你直接观察图也可以很显然的得出结论。​
# DFT（离散傅里叶变换）
对于任意多项式系数表示转点值表示，例如$F[x]=y=a_0x^0+a_1x^1+a_2x^2+......+a_nx^n$   ，可以随便取任意n个$x$值代入计算,但这样时间复杂度是$O(n^2)$

所以伟大数学家[傅里叶](https://baike.so.com/doc/5915463-6128375.html)取了一些特殊的点代入，从而进行优化。

他规定了点值表示中的$n$个$x$为$n$个模长为1的复数。这$n$个复数不是随机的，而是**单位根**。

把上述的n个复数（单位根）$\omega_n^0,\omega_n^1.....,\omega_n^{n-1}$代入多项式，能得到一种特殊的点值表示，这种点值表示就叫**DFT（离散傅里叶变换）**。
# FFT（快速傅里叶变换）
虽然**DFT**能把多项式转换成点值但它仍然是暴力代入$n$个数，复杂度仍然是O(n2)，所以它只是快速傅里叶变换的朴素版。

所以我们要考虑利用**单位根的性质**，加速我们的运算，得到**FFT（快速傅里叶变换）**

对于多项式 $A(x)$=$a_0$+$a_1x$+$a_2x^2$+...+$a_{n-1}x^{n-1}$，
将A(x)的每一项按照下标的奇偶分成两部分：

$A(x)=a_0x^0+a_2x^2+...+a_{n-2}x^{n-2}+x(a_1x^0+a_3x^2+...+a_{n-1}x^{n-2})$

设两个多项式 $A_0(x)$和$A_1(x)$，令：
$A_0(x)=a_0x^0+a_2x^1+...+a_{n-2}x^{n/2-1}$
$A_1(x)=a_1x^0+a_3x^1+...+a_{n-1}x^{n/2-1}$

显然，$A(x)=A_0(x^2)+x*A_1(x^2)$

假设$k<n$，代入$x=ω_n^k$（n次单位根）：
 $A(\omega_n^k)$$=A_0(\omega_n^{2k})+\omega_n^{k}*A_1(\omega_n^{2k})$$=A_0(\omega_\frac n2^{k})+\omega_n^{k}*A_1(\omega_\frac n 2^{k})$

$A(\omega_n^{k+\frac n 2})=A_0(\omega_n^{2k+n})+\omega_n^{k+\frac n 2}*A_1(\omega_n^{2k+n})$$=A_0(\omega_\frac n2^{k})-\omega_n^{k}*A_1(\omega_\frac n 2^{k})$

考虑A1(x)和A2(x)分别在$(\omega_\frac n 2^{1},\omega_\frac n 2^{2},\omega_\frac n 2^{3},...,\omega_\frac n 2^{\frac n 2-1})$的点值表示已经求出，就可以O(n)求出A(x)在$(\omega_n ^{1},\omega_n ^{2},\omega_n ^{3},...,\omega_n ^{n-1})$处的点值表示。

这个操作叫**蝴蝶变换**。

而A1(x)和A2(x)是规模缩小了一半的子问题，所以不断向下递归分治。当n=1的时候返回。

**注**：这个过程一定要求每层都可以分成两大小相等的部分，所以多项式最高次项一定是2的幂，不是的话直接在最高次项补零QAQ。

时间复杂度$O(nlog_2n)$
# IFFT（快速傅里叶逆变换）
我们已经将两个多项式从系数表示法转化成点值表示法相乘后，还要将结果从点值表示法转化为系数表示法，也就是**IFFT（快速傅里叶逆变换）** 

首先思考一个问题，为什么要把$\omega_n^k$（单位根）作为x代入？

当然是因为离散傅里叶变换特殊的性质，而这也和IFFT有关。

**一个重要结论**

把多项式A(x)的离散傅里叶变换结果作为另一个多项式B(x)的系数，取单位根的倒数即$\omega_n^0,\omega_n^{-1}.....,\omega_n^{1-n}$作为x代入B(x)，得到的每个数再除以n，得到的是A(x)的各项系数，这就实现了傅里叶变换的逆变换了。

相当于在FFT基础上再搞一次FFT。

**证明**~~（个人觉得写的非常清楚，不想看的跳过吧）~~~~  

设$(y_0,y_1,y_2,...,y_{n-1})$为多项式
$A(x)=a_0+a_1x+a_2x^2+...+a_{n-1}x^{n-1}$的离散傅里叶变换。

设多项式$B(x)=y_0+y_1x+y_2x^2+...+y_{n-1}x^{n-1}$
把离散傅里叶变换的$\omega_n^0,\omega_n^1.....,\omega_n^{n-1}$这n个单位根的倒数，即$\omega_n^0,\omega_n^{-1}.....,\omega_n^{1-n}$作为x代入$B(x)$, 得到一个新的离散傅里叶变换($z_0$,$z_1$,$z_2$,...,$z_{n-1}$)

$z_k$=$\sum_{i=0}^{n-1}y_i(\omega_n^{-k})^i$

=$\sum_{i=0}^{n-1}(\sum_{j=0}^{n-1}a_j*(\omega_n^i)^j)(ω_n^{-k})^i$ 

=$\sum_{j=0}^{n-1}a_j*(\sum_{i=0}^{n-1}(\omega_n^i)^{j-k})$

当$j-k=0$时，$\sum_{i=0}^{n-1}(\omega_n^i)^{j-k}=n$

否则，通过等比数列求和可知：

$\sum_{i=0}^{n-1}(\omega_n^i)^{j-k}$
=$\frac{(ω_n^{j-k})^n-1}{ω_n^{j-k}-1}$=$\frac{(ω_n^{n})^{j-k}-1}{ω_n^{j-k}-1}$=$\frac{1-1}{ω_n^{j-k}-1}=0$   
（因为$\omega_n^n$=$\omega_n^0$=1）

所以

$z_k=n*a_k$

$a_k=\frac {z_k} n$ 

得证。

怎么求单位根的倒数呢？

单位根的倒数其实就是它的共轭复数 。~~不明白的可以看看前面共轭复数的介绍~~ 

到现在你已经完全学会FFT了，但写递归还是可能会超时，所以我们需要优化
# 优化：迭代FFT
在进行FFT时，我们要把各个系数不断分组并放到两侧，一个系数原来的位置和最终的位置的规律如下。

初始位置：$\omega_n^0$ $\omega_n^1$ $\omega_n^2$ $\omega_n^3$ $\omega_n^4$ $\omega_n^5$ $\omega_n^6$ $\omega_n^7$

第一轮后：$\omega_n^0$ $\omega_n^2$ $\omega_n^4$ $\omega_n^6$|$\omega_n^1$ $\omega_n^3$ $\omega_n^7$ $\omega_n^5$ 

第二轮后：$\omega_n^0$ $\omega_n^4$|$\omega_n^2$ $\omega_n^6$|$\omega_n^1$ $\omega_n^5$|$\omega_n^3$ $\omega_n^7$ 

第三轮后：$\omega_n^0$|$\omega_n^4$|$\omega_n^2$|$\omega_n^6$|$\omega_n^1$|$\omega_n^5$|$\omega_n^3$|$\omega_n^7$

“|”代表分组界限 
把每个位置用二进制表现出来。

位置x上的数，最后所在的位置是“x二进制翻转得到的数”，例如4(100）最后到了1（001）。5(101)最后不变为5(101)，3(011)最后到了6(110)。

所以我们先把每个数放到最后的位置上，然后不断向上还原，同时求出点值表示就可以啦。

迭代版FFT就比之前的递归版快多了,真$O(nlog_2n)$绝妙算法

# 代码实现FFT
下面是本人写的**FFT加速高精度乘法**的代码（并有详细注释）：
```javascript
#include<bits/stdc++.h>
using namespace std;
//complex是stl自带的定义复数的容器 
typedef complex<double> cp;
#define N 2097153
//pie表示圆周率π 
const double pie=acos(-1);
int n;
cp a[N],b[N];
int rev[N],ans[N];
char s1[N],s2[N];
//读入优化 
int read(){
	int sum=0,f=1;
	char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){sum=(sum<<3)+(sum<<1)+ch-'0';ch=getchar();}
	return sum*f;
}
//初始化每个位置最终到达的位置 
{
    int len=1<<k;
	for(int i=0;i<len;i++)
	rev[i]=(rev[i>>1]>>1)|((i&1)<<(k-1));
}
//a表示要操作的系数，n表示序列长度
//若flag为1，则表示FFT，为-1则为IFFT(需要求倒数） 
void fft(cp *a,int n,int flag){ 
    for(int i=0;i<n;i++)
	{
	 //i小于rev[i]时才交换，防止同一个元素交换两次，回到它原来的位置。 
	  if(i<rev[i])swap(a[i],a[rev[i]]);
	}
	for(int h=1;h<n;h*=2)//h是准备合并序列的长度的二分之一
	{
	cp wn=exp(cp(0,flag*pie/h));//求单位根w_n^1 
	 for(int j=0;j<n;j+=h*2)//j表示合并到了哪一位
	 {
	  cp w(1,0);
	   for(int k=j;k<j+h;k++)//只扫左半部分，得到右半部分的答案
	   {
	     cp x=a[k];
	     cp y=w*a[k+h];
         a[k]=x+y;  //这两步是蝴蝶变换 
         a[k+h]=x-y;
         w*=wn; //求w_n^k 
	   }
	 }
	 }
	 //判断是否是FFT还是IFFT 
	 if(flag==-1)
	 for(int i=0;i<n;i++)
     a[i]/=n;
}
int main(){
	n=read(); 
	scanf("%s%s",s1,s2);
	//读入的数的每一位看成多项式的一项，保存在复数的实部 
    for(int i=0;i<n;i++)a[i]=(double)(s1[n-i-1]-'0');
	for(int i=0;i<n;i++)b[i]=(double)(s2[n-i-1]-'0');
	//k表示转化成二进制的位数 
	int k=1,s=2;
 	while((1<<k)<2*n-1)k++,s<<=1;
	init(k);
	//FFT 把a的系数表示转化为点值表示 
    fft(a,s,1);
    //FFT 把b的系数表示转化为点值表示 
    fft(b,s,1);
    //FFT 两个多项式的点值表示相乘 
    for(int i=0;i<s;i++)
    a[i]*=b[i];
    //IFFT 把这个点值表示转化为系数表示 
    fft(a,s,-1);
    //保存答案的每一位(注意进位） 
    for(int i=0;i<s;i++)
    {
    //取实数四舍五入，此时虚数部分应当为0或由于浮点误差接近0
	ans[i]+=(int)(a[i].real()+0.5);
	ans[i+1]+=ans[i]/10;
	ans[i]%=10;
	}
	while(!ans[s]&&s>-1)s--;
	if(s==-1)printf("0");
	else
	for(int i=s;i>=0;i--)
	printf("%d",ans[i]);
	return 0;
}
```
# 后记
这篇博客写了一天，终于写完了，完结撒花✿✿ヽ(°▽°)ノ✿
FWT我来啦！！！

---

## 作者：皎月半洒花 (赞：435)

这个题是不是一直少一篇正常的题解啊 $\rm QAQ$

感觉为什么其他同样是 $FFT$ 的码风这么不正经啊 $\rm QAQ$

$py$ 好用但是 ~~圈钱组织~~ CCF不承认啊 $\rm QAQ$

所以我们还是老老实实地 $FFT$ 吧 = = 

## 正确性：

对于每一个 $n$ 位的十进制数，我们可以看做一个 $n-1$ 次多项式 $A$，满足

$$
A(x) =a_0+a_1 \times 10+a_2\times10^2 \cdots +a_{n-1}\times10^{n-1}
$$

那么对于两个大整数相乘,我们就可以卷起来辣$qwq$

## 小细节：
- 不要忘记进位$qwq$

- 不要忘了要保证数位上的单调性，因为我们普通的$FFT$卷积时，高次项一定由低次项得到，放在这里也一样,所以我们要倒序存储。

- 不会$FFT$的，戳这里[Link](https://www.cnblogs.com/pks-t/p/9251147.html)

```cpp
#include <cmath>
#include <cstdio>
#include <iostream>
#define il inline
#define MAXN 3000100

using namespace std ;
char s1[MAXN], s2[MAXN] ;
int N, M, K, res = 0, ans[MAXN], AA, BB ;
int i, j, k, l, Lim = 1, L, R[MAXN] ; 
const double Pi = acos(-1.0) ;
struct node{
    double x, y ;
    node (double xx = 0, double yy = 0){
        x = xx, y = yy ;
    }
}A[MAXN], B[MAXN] ;
node operator * (node J, node Q){
    return node(J.x * Q.x - J.y * Q.y , J.x * Q.y + J.y * Q.x);
}
node operator + (node J, node Q){
    return node(J.x + Q.x , J.y + Q.y);
}
node operator - (node J, node Q){
    return node(J.x - Q.x , J.y - Q.y );
}

il int qr(){
    int k = 0, f = 1 ;
    char c = getchar() ;
    while(!isdigit(c)){if(c == '-') f = -1 ;c = getchar() ;}
    while(isdigit(c)) k = (k << 1) + (k << 3) + c - 48 ,c = getchar() ;
    return k * f ;
}
il void FFT(node *J, double flag){
    for(i = 0; i < Lim; i ++)
        if(i < R[i]) swap(J[i], J[R[i]]) ;
    for(j = 1; j < Lim; j <<= 1){
        node T(cos(Pi / j), flag * sin(Pi / j)) ;
        for(k = 0; k < Lim; k += (j << 1) ){
            node t(1, 0) ;
            for(l = 0 ; l < j; l ++, t = t * T){
                node Nx = J[k + l], Ny = t * J[k + j + l] ;
                J[k + l] = Nx + Ny ;
                J[k + j + l] = Nx - Ny ;
            }
        }
    }
}
int main(){
    N = qr() ;
    scanf("%s%s", s1, s2) ;
    for(i = N - 1; i >= 0; i --) A[AA ++].x = s1[i] - 48;
    for(i = N - 1; i >= 0; i --) B[BB ++].x = s2[i] - 48;
    while(Lim < N + N ) Lim <<= 1, L ++ ;
    for(i = 0; i <= Lim; i ++ ) R[i] = (R[i >> 1] >> 1) | ((i & 1) << (L - 1)) ;
    FFT(A, 1), FFT(B, 1) ;
    for(i = 0; i <= Lim; i ++) A[i] = A[i] * B[i] ;
    FFT(A, -1) ;
    int tot = 0 ;
	for(i = 0; i <= Lim; i++) {
        ans[i] += (int) (A[i].x / Lim + 0.5) ;
        if(ans[i] >= 10) 
            ans[i + 1] += ans[i] / 10, ans[i] %= 10, Lim += (i == Lim);
    }
    while(!ans[Lim] && Lim >= 1) Lim -- ;
    Lim ++ ;
	while( -- Lim >= 0) cout << ans[Lim] ; 
    return 0 ;
}
```

---

## 作者：warzone (赞：47)

鉴于毒瘤鰰加强了数据,在此发一篇关于加强数据的NTT题解

## 一、如何优化高精乘

众所周知,朴素的高精乘是 $\Theta(n^2)$ 的,对于超过 $10^{10000}$ 的数据,要尝试去优化ta  
一个比较简单的方法是压位,就是用一个int或者long long连续存储多位,以此优化常数,然而...

![](https://cdn.luogu.com.cn/upload/image_hosting/hrsyu8mu.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/23c9eirm.png)   
于是 $a,b\le 10^{65536} => a,b\le 10^{1000000}$ ,就必须优化复杂度来做这道题了。怎么优化呢?

首先,我们可以通过位值原理将一个数转化为n次函数(多项式),  
如$\quad3579=3x^3+5x^2+7x+9\quad$,其中 $x=10$。

我们称这种我们一般用来表示n此函数的方法称为**系数表示法**。  
不难发现,该多项式的乘法就是不带进位的高精乘 (加法同理)

此外,~~用小学知识~~可知,用 $(n+1)$ 个点可唯一确定一个 $n$ 次函数,  
我们定义这种表示方法为**点值表示法**。  
于是设第一个多项式A可转化为 $(x_0,a_0),(x_1,a_1)\cdots(x_n,a_n)$，  
第二个多项式B可转化为$\quad\quad\quad(x_0,b_0),(x_1,b_1)\cdots(x_n,b_n)$，  
我们就可以用 $\Theta(n)$ 的复杂度把它们乘起来,于是答案就是  
$(x_0,a_0\times b_0),(x_1,a_1\times b_1)\cdots(x_n,a_n\times b_n)$

Q:可是代入这些值也要 $\Theta(n^2)$ 呀,而且显而易见会爆long long,
	这种做法不应更劣吗?  
A:不急,我们接下来就讲。

## 二、傅里叶的优化方法  
鉴于这一情况,大佬傅里叶找到了一组特殊的值在特定意义下代入,以此来缩短值域,优化常数和精度

我们把 将系数表示法 通过代入他找到的值 转化为点值表示法 称为**DFT**,  
再把 由DFT转化成的点值表示法 重新转化为系数表示法 称为**IDFT** 

如何让代入的值达到这种效果呢? 我们希望代入的值满足以下条件：  
	1.代入的值互不相同(显而易见,如果相同就相当于同一个点)  
    2.代入的值的乘方在一个范围内转圈圈。(这个比较重要,对值域和精度都有限制)
    
于是我们就有两种做法来限制:取模(NTT)和复数运算(FFT)。其中复数运算涉及涉及高中内容,  
相关定理对于初中萌新较为难理解,而且实数运算有精度限制,所以这里我们用取模来限制,即NTT

## 三、NTT的前置芝士
1.乘法逆元(鰰叕在模板上面卡了常)   
[P3811 【模板】乘法逆元](https://www.luogu.org/problem/P3811)   
[P5431 【模板】乘法逆元2](https://www.luogu.org/problem/P5431)  
2.原根  
	学过乘法逆元的朋友应该都知道费马小定理: $\text{若}p\text{为质数,则}a^{p-1}\equiv 1\quad(\text{mod }p)$  
   那么对于一个质数 $p$ ,如果有一个数 $a$ ,使得 $a^0,a^1,\cdots a^{p-2} $在$\mod p$意义下互不相等，  
   ,我们就称a为$\mod m$的**原根**,通常用字母 $g$ 表示
   
   换个方式理解,原根的乘方相当于把$1\sim p-1$全部遍历了一遍
   然后回到了原点,刚好满足条件1和条件2
   
## 四、NTT加速多项式乘法

1.单位根  
	为了方便分治,我们先将多项式补足到$2^k$,  
   然后将形如 $q\times 2^k+1$ 的质数作为模数,让计算在其模意义下进行
  
   NTT常用的模数有$998244353=119\times 2^{23}+1,1004535809=479\times 2^{21}$,二者的原根都为3   
   如果需要更多的模数,可以看[这里](https://www.cnblogs.com/Guess2/p/8422205.html)
   
   然后我们代入的数就是  
   $g^0,g^q,g^{2q},g^{3q}\cdots g^{(2^k-1)q}(\text{mod }q\times 2^k+1)$
   
   于是在模意义下代入它们就得到了DFT,  
   而IDFT就是就是按顺序把代入得到的值作为系数,依次代入这些数的逆元,  
   最后乘上$2^k$的逆元就可以转回来了
   
   为方便称呼,我们设$2^k=n,w^x_n=g^{xq}$,此时$w^x_n$我们称它为**单位根**
   
   
   于是就可以得到一些性质：
   
$\quad$1.$w^0_n=w^n_n=1,w^x_n\equiv (w^1_n)^x(\text{mod }q\times 2^k+1)$ (显而易见)  
$\quad$2.$w^{2x}_{2n}\equiv w^x_n(\text{mod } q\times 2^k+1)$(相当于从$2^k$中提取一个2到q)  
$\quad$3.若$x<\frac{n}{2}$,则$w^x_n\equiv -w^{x+\frac{n}{2}}_n(\text{mod }q\times 2^k+1)$  
 $\qquad$证明:两边同时乘以$w^x_n$的逆元,得   
 $\qquad\qquad 1\equiv -w^{\frac{n}{2}}_n(\text{mod }q\times 2^k+1)$   
$\qquad\qquad\because (w^{\frac{n}{2}}_n)^2=w^n_n=1,$且由原根的性质$,w^{\frac{n}{2}}_n\ne w^0_n=1$  
$\qquad\qquad\therefore w^{\frac{n}{2}}_n\equiv-1(\text{mod } q\times 2^k+1)$,证毕  

透过这些性质，就可以用分治来做了  
设要代入的多项式为$F(x)=a_0+a_1x^1+a_2x^2+\cdots+a_{n-1}x^{n-1}$  
把下标为偶数的放一边,下标为奇数的放一边,得到  
$F(x)=(a_0+a_2x^2+\cdots+a_{n-2}x^{n-2})+x(a_1+a_3x^2+\cdots a_{n-1}x^{n-2})$  
于是设$A(x)=a_0+a_2x^1+\cdot+a_{n-2}x^{\frac{n}{2}-1},B(x)=a_1+a_3x^1+\cdot+a_{n-1}x^{\frac{n}{2}-1}$  
所以$F(x)=A(x^2)+x\times B(x^2)$  
代入$w^x_n$,得到$F(w^x_n)=A((w^x_n)^2)+w^x_n\times B((w^x_n)^2)=A(w^x_{\frac{n}{2}})+w^x_n\times B(w^x_{\frac{n}{2}})$  
这时,若我们代入$w^{x+\frac{n}{2}}_n$,就可以得到  
$F(w^{x+\frac{n}{2}}_n)=A((w^{x+\frac{n}{2}}_n)^2)+w^{x+\frac{n}{2}}_n\times B((w^{x+\frac{n}{2}}_n)^2)=A(w^x_{\frac{n}{2}})-w^x_n\times B(w^x_{\frac{n}{2}})$  
这时,我们发现,我们在扫过$F(w^0_n\sim w^{\frac{n}{2}-1}_n)$时,可以顺带得到$F(w^{\frac{n}{2}}_n\sim w^{n-1}_n)$,也就可以$\Theta(n\log n)$分治了

## 五、FFT/NTT的常数优化

1.非递归写法  
	我们在划分$A(x),B(x)$的时候,是按下标的奇偶性来分的,也就是看下标二进制的最后一位  
   于是整体递归下来,就是先看下标二进制的最后一位,再看倒数第二位,再...  
   于是最终递归到的位置就是下标二进制翻转过来,可以预处理好
   
2.蝴蝶变换：就地进行FFT\NTT  
	如果已经顺序存储了$A(1\sim w^{\frac{n}{4}}_{\frac{n}{2}}),B(1\sim w^{\frac{n}{4}}_{\frac{n}{2}})$，A在B的前面  
  	对于要迭代到的$w^x_n$和$w^{x+\frac{n}{2}}_n$，可以同时进行迭代,  
    将$w^x_n$放到原$A(w^x_{\frac{n}{2}})$的位置,将$w^{x+\frac{n}{2}}$放到原$B(w^x_{\frac{n}{2}})$的位置,保证顺序不变
    
### 六、最终代码

```cpp
#include<stdio.h>
#include<string.h>
typedef unsigned char byte;
typedef unsigned int word;
typedef unsigned long long ull;
typedef long long ll;
const word mod=1004535809,size=21;
//NTT模数,结果不超过(1<<size) 
char io[(1<<size)+1];//输入输出 
word a[1<<size],b[1<<size];//多项式/高精 
word realid[1<<size],root[1<<size],inverse[1<<size];
//迭代后系数所在的位置,单位根及其逆元 
word i,id,floor;
ll num1,num2;
char *top;
//循环变量 
inline ll pow(ll a,ll b){//快速幂 
	register ll ans=1;
	for(;b;b>>=1){
		if(b&1) (ans*=a)%=mod;
		(a*=a)%=mod;
	}
	return ans;
}
inline void loading(){//预处理迭代后位置,单位根及其逆元 
	root[0]=inverse[0]=1;
	num1=pow(3,mod>>size);
	num2=pow(num1,mod-2);
	for(i=1;i<1<<size;i++){
		root[i]=num1*root[i-1]%mod;
		inverse[i]=num2*inverse[i-1]%mod;
		for(id=i,floor=0;floor<size;floor++,id>>=1)
			realid[i]=realid[i]<<1|(id&1);
	}
}
inline void read(){
//直接用fread,然后指针前移读入数据,效率较高,写法较简单 
//因fread特性,DEV-CPP下不能以数字结尾(不停读入最后一个字符),但linux下可以 
	top=io+(1<<size);
	fread(io+1,1,1<<size,stdin);
	while('0'>*top||*top>'9') top--;
	for(i=0;'0'<=*top&&*top<='9';top--,i++)
		a[realid[i]]=*top-'0';//直接放到迭代后的位置 
	while('0'>*top||*top>'9') top--;	
	for(i=0;'0'<=*top&&*top<='9';top--,i++)
		b[realid[i]]=*top-'0';//b同理 
} 
inline void DFT(){ //非迭代版DFT 
	for(floor=0;floor<size;floor++)
		for(i=0;i<1<<size;i+=(1<<(floor+1)))
			for(id=0;id<1<<floor;id++){
				num1=a[i+id];//蝴蝶变换 
				num2=a[i+id+(1<<floor)];
				(num2*=root[id<<size-floor-1])%=mod;
				a[i+id]=(num1+num2)%mod;//放回原位 
				a[i+id+(1<<floor)]=(num1+mod-num2)%mod;
				 
				num1=b[i+id];//b同理 
				num2=b[i+id+(1<<floor)];
				(num2*=root[id<<size-floor-1])%=mod;
				b[i+id]=(num1+num2)%mod;
				b[i+id+(1<<floor)]=(num1+mod-num2)%mod;
			}
}
inline void IDFT(){
	for(floor=0;floor<21;floor++)//与DFT相同 
		for(i=0;i<0x200000;i+=1<<floor+1)
			for(id=0;id<1<<floor;id++){
				num1=root[i+id];
				num2=root[i+id+(1<<floor)];
				(num2*=inverse[id<<20-floor])%=mod;//乘上单位根逆元 
				root[i+id]=(num1+num2)%mod;
				root[i+id+(1<<floor)]=(num1+mod-num2)%mod;
			}
}
inline void write(){//fwrite输出,同输入
	num2=pow(1<<size,mod-2);
	top=io+(1<<size);
	num1=0;
	for(i=0;i<1<<size;i++){
		num1+=num2*root[i]%mod;//最后要乘上n的逆元 
		top--;
		*top=num1%10+'0';
		num1/=10;
	}
	while(*top=='0'&&top!=io+(1<<size)) top++;
	if(top==io+(1<<size)) putchar('0');
	else fwrite(top,1,io+(1<<size)-top,stdout);
}
int main(){
	loading();
	read(); 
	DFT();
	for(i=0;i<1<<size;i++)
		root[realid[i]]=(ll)(a[i])*b[i]%mod;//点值相乘 
	IDFT();
	write(); 
	return 0;
}
```
### END、数据范围

设NTT模数为$q\times 2^k+1$,那么多项式长度不能超过$2^k$

设原本相乘多项式的系数不超过n,长度为P,则相乘后的系数不超过$n^2P$  

如果要使得到的结果在模意义下仍旧是唯一的,除了扩大NTT模数,也可以取多个模数做NTT,  
最后将得到的结果用中国剩余定理合并(这也就是任意模数NTT的方法)


---

## 作者：cy1999 (赞：38)

介绍一种~~并不能过题~~的Karatsuba 乘法。

假设我们要求x*y,我们让：
$$x=a*10^{n/2}+b,y=c*10^{n/2}+d$$

那么
$$xy=ac\times10^{(n-n/2)\times2}+(ad+bc)\times10^{n-n/2}+bd$$
又因为
$$ad+bc=(a+b)(c+d)-(ac+bd)$$
所以我们可以重复利用ac和bd的结果，不用做四次乘法。
这样递归下去求的复杂度是 (来自百度百科)
$$3n^{log3}≈3n^{1.585}$$

下面是这个算法本蒟蒻的代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int L=120010;
string add(string a,string b)
{
    string ans;
    int na[L]={0},nb[L]={0};
    int la=a.size(),lb=b.size();
    for(int i=0;i<la;i++) na[la-1-i]=a[i]-'0';
    for(int i=0;i<lb;i++) nb[lb-1-i]=b[i]-'0';
    int lmax=la>lb?la:lb;
    for(int i=0;i<lmax;i++) na[i]+=nb[i],na[i+1]+=na[i]/10,na[i]%=10;
    if(na[lmax]) lmax++;
    for(int i=lmax-1;i>=0;i--) ans+=na[i]+'0';
    return ans;
}
string sub(string a,string b)
{
    string ans;
    int na[L]={0},nb[L]={0};
    int la=a.size(),lb=b.size();
    for(int i=0;i<la;i++) na[la-1-i]=a[i]-'0';
    for(int i=0;i<lb;i++) nb[lb-1-i]=b[i]-'0';
    int lmax=la>lb?la:lb;
    for(int i=0;i<lmax;i++)
    {
        na[i]-=nb[i];
        if(na[i]<0) na[i]+=10,na[i+1]--;
    }
    while(!na[--lmax]&&lmax>0)  ;lmax++;
    for(int i=lmax-1;i>=0;i--) ans+=na[i]+'0';
    return ans;
}
//---------------------大数加减法---------------------------------//
string karatsuba(string a,string b){
    if(a.size()<b.size()) swap(a,b);
    int tmp=a.size()-b.size();
    string qd0="";for(int i=0;i<tmp;i++) qd0+='0';
    b=qd0+b;
    //---------------补前导0------------------//
    if(a.size()==b.size()&&a.size()==1){
        string ans="";
        int ansnum=(a[0]-48)*(b[0]-48);
        while(ansnum){ans=(char)('0'+ansnum%10)+ans;ansnum/=10;}
        if(ans.size()==0) ans="0";
        return ans;
    }
    int mid=a.size()-a.size()/2;
    string qa,ha,qb,hb;
    qa=a.substr(0,mid);ha=a.substr(mid,a.size()-mid);
    qb=b.substr(0,mid);hb=b.substr(mid,b.size()-mid);
    string qaqb=karatsuba(qa,qb);
    string hahb=karatsuba(ha,hb);
    string qahbhaqb=sub(karatsuba(add(qa,ha),add(qb,hb)),add(qaqb,hahb));
    //------------------三次乘法---------------------------//
    for(int i=0;i<(a.size()-mid)*2;i++) qaqb+='0';
    for(int i=0;i<(a.size()-mid);i++) qahbhaqb+='0';
    //------------------移位------------------------------//
    string ans=add(qaqb,qahbhaqb);
    ans=add(ans,hahb);
    return ans;
}
int main(){
    int n;cin>>n;
    string a,b;cin>>a>>b;
    cout<<karatsuba(a,b)<<endl;
    return 0;
}

```

---

## 作者：Maisie586_ (赞：38)

本文为 Python 题解。

首先，先看一下数据范围，达到了 $10^{1000000}$，所以我们要使用 Python 的 **decimal** 模块来解决。

**以下为思路解释和代码。**

- 从 decimal 模块导入 Decimal 类和 setcontext 函数。

- 设置计算上下文，以支持高达 2000000 位的精度，以及相应的指数范围。
- 从标准输入读取两行，每行包含一个数字，并将它们转换为 Decimal 对象。
- 执行乘法运算，并将结果打印出来。


```python
from decimal import *
import sys
setcontext(Context(prec=2000000, Emax=2000000, Emin=0)) 
print((Decimal(sys.stdin.readline())*Decimal(sys.stdin.readline())))
```

---

## 作者：strcmp (赞：7)

![](https://cdn.luogu.com.cn/upload/image_hosting/qckbliha.png)

**挂一个人，图文无关。**

感觉到目前为止题解区缺少对 FFT 的具体描述，或者要么很不适合初学者进行学习。因此我决定写一篇足够适合初学者学习的题解，因此会适当牺牲一些严谨性和相对困难的证明。

个人认为本文**如果你不在乎证明**且其余部分较认真的读的话，即使只有初中三年级数学水平也足够看懂。

希望如果有一些疏忽导致的事实性错误可以有人指出，本文可能会视情况修正一些错误以及更新一些扩展。

**强烈建议**你在知道 $\sin$ 和 $\cos$ 是什么之后再阅读本文，**强烈建议**你知道弧度值是什么之后再阅读本文。如果你实在不知道什么是弧度值，你就记住 $\pi = 180^\circ$ 即可。

**建议**你在知道向量是什么之后再阅读本文。

如果可以，建议先知道**复数**是什么。

注意，**如果你要看懂证明的话**，至少要有部分线性代数和复数的知识背景。

**虽然不是必须的，但最好有一部分线性代数基础。**

- 本文默认任何下标都以 $0$ 开头。

- **我们可以用多项式来描述十进制乘法**，具体来说我们从低到高依次把每一位从低到高写到多项式系数上（第 $i$ 位写到 $x^{i - 1}$ 的系数上），那么我们的数值就是多项式取 $x = 10$ 的值。比如现在我要做 $21$ 和 $74$ 的乘法，就先写出来 $f(x) = 2x + 1$ 和 $g(x) = 7x + 4$ 进行乘法，可以得到 $h(x) = 14x^2 + 15x + 4$，怎么转成十进制？带入 $f(10)$ 即可，我们得到 $f(x) = 14 \times 10 \times 10 + 15 \times 10 + 4 = 1554 = 21 \times 74$。在实际情况中我们直接从低到高进位即可。

- 我们知道两点确定一条直线，三点确定一条抛物线，**$n + 1$ 个点确定 $n$ 次多项式。**

我们初中的时候就学过了带入系数法求二次函数系数。当然可以扩展到多项式，设我们的多项式是 $\sum\limits_{i = 0}^{n} a_ix^i$

考虑 $n$ 个点的点值 $(x_i,\,y_i),\,0 \le i \le n,\,i \ne j \Rightarrow x_i \ne x_j$，以及线性方程组：

$$
\begin{bmatrix}
1 & x_0 & x_0^2 & \cdots & x_0^{n} \\ 
1 & x_1 & x_1^2 & \cdots & x_1^{n} \\
1 & x_2 & x_2^2 & \cdots & x_2^{n} \\
\vdots & \vdots & \vdots & \ddots & \vdots \\
1 & x_n & x_n^2 & \cdots & x_n^{n} \\ 
\end{bmatrix}
\begin{bmatrix}
a_0 \\
a_1 \\
a_2 \\
\vdots \\
a_n
\end{bmatrix}
 = \begin{bmatrix}
y_0 \\
y_1 \\
y_2 \\
\vdots \\
y_n
\end{bmatrix}
$$

这个是**范德蒙矩阵**，可以用归纳法证明其满秩，且行列式值为 $\prod\limits_{0 \le j < i \le n} x_i - x_j$。

所以原线性方程组有唯一解。

- 如果我们知道了两个次数为 $n$ 的多项式 $f,\,g$ 分别 $2n + 1$ 个点值 $(x_0,\,y_0) \dots (x_{2n},\,y_{2n}),\,y_i = f(x_i)$ 和 $(x_0,\,y'_0) \dots (x_{2n},\,y'_{2n}),\,y'_i=g(x_i)$（注意两个多项式的点值的 $x$ 对应相等）。

- 在实际应用中，如果这两个多项式次数不一样（分别为 $n,\,m$），我们就统一默认两个多项式的次数均为 $n + m - 1$。高位补零补上去即可。比如 $f(x) = 3x + 1$ 和 $g(x) = x^2 + 2x + 1$，我们就补成 $f(x) = 0x^3 + 0x^2 + 3x + 1$ 和 $g(x) = 0x^3 + x^2 + 2x + 1$。
 
那么我们也就可以知道它们乘积的 $n + m$ 个点值 $(x_i,\,y_i \times y'_i)$。

我们知道 $n + m$ 个点值确定一个 $n + m - 1$ 次多项式，而 $n$ 次多项式和 $m$ 次多项式相乘恰好是 $n + m - 1$ 次多项式。所以这 $n + m$ 个点值恰好能够确定我们的乘积（一个 $n + m - 1$ 次多项式）。当然我们的多项式可能是补上来的，次数没有 $n + m - 1$ 次，但是这个并不影响，我们的点值也能唯一确定这个多项式（比如用**三点共线确定一条直线**）。

由此确定了我们的思路：**求点值，对应相乘，再插值。**

- 但是现在摆在我们面前两个难题，一是怎么低于 $\Theta(n^2)$ 的求点值，二是怎么低于 $\Theta(n^2)$ 的**插值**（也就是根据点值确定多项式）。

- 一般来说，我们有秦九韶算法对多项式求值（要求 $\Theta(n)$ 次点值，每次求一次点值复杂度是 $\Theta(n)$），拉格朗日插值法（本身就是 $\Theta(n^2)$）对点值进行插值，但是直接做两个部分都是 $\Theta(n^2)$ 的，本末倒置了。

- 我们的优势在于：**我们可以任意选定要求的点值的横坐标。**

比如我们完全可以求 $(0,\,f(0))$，求 $(1,\,f(1))$。

但不管怎么在实数域上选取横坐标，我们的点值仍然不好求。

### 复数

我们定义 $i = \sqrt{-1}$，这看起来很魔怔，不过确实能帮助我们解决相当多问题，比如接下来的多项式乘法。

我们把形如 $z = a + bi$ 的数称为复数，同时令 $\mathbb C$ 为复数域。那么我们可以定义复数的运算了，$z_0 = a + bi,\,z_1 = c + di,\,z_0 + z_1 = (a + c) + (b + d)i,\,z_0 - z_1 = (a + c) - (b + d)i,\,z_0 \times z_1 = (a + bi)(c + di) = (ac - bd) + (ad + bc)i,\,\dfrac{z_0}{z_1} = \dfrac{ac + bd}{c^2 + d^2} + \dfrac{bc - ad}{c^2 + d^2}i$。

对于复数 $z = a + bi$，我们将 $a$ 称为 $z$ 的**实部**，$b$ 称为 $z$ 的**虚部。**

- 一个复数 $z = a + bi$ 可以表示为平面上的一个点 $(a,\,b)$，也就是实部代表横坐标，虚部代表纵坐标。我们干脆用**向量** $\vec z = (a,\,b)$ 表示。

- 比如乘一个 $i$，可以看作向量逆时针旋转了 $90^\circ$。

- 关于向量 $(a,\,b)$，你可以看作从原点往横坐标正方向移动 $a$ 个单位长度，纵坐标正方向移动 $b$ 个单位长度的一个量（有方向有大小）。比如你可以把它理解成**箭**（物理上的“矢量”）。

**Euler Formula**：$e^{\theta i} = \cos(\theta) + i\sin(\theta)$。

关于欧拉公式，严谨证明涉及到太多东西。这里给个导数方面的理解方法（只能说是理解方法，因为实际上有循环论证）。

我们知道 $(e^{xa})' = ae^{ax}$，那么 $(e^{xi})' = ie^{xi}$ 可以理解为导数是自身的 $i$ 倍，那么画个箭头其实就是每时每刻的移动方向都指向逆时针方向，并且垂直于当前位置代表的向量。这其实就是**匀速圆周运动。**

**de Morive Formula**：将复数看成向量，两个复数相乘的几何意义是**辐角相加，模长相乘**。对应的，两个复数相除的集合意义是辐角相减，模长相除。

向量 $\vec z$ 的辐角：从 $x$ 轴正半轴开始，**逆时针**转多少度能跟向量 $\vec z$ 同向。

向量 $\vec z$ 的模长就是向量 $\vec z$ 的长度。

![](https://cdn.luogu.com.cn/upload/image_hosting/p2iz1lht.png)

于是在复数域下，我们仍然有 **$n + 1$ 个点确定一个 $n$ 次复系数多项式**。毕竟显然只有 $z = 0$ 的模长是 $0$，而我们之前 $\prod\limits_{0 \le j < i \le n} x_i - x_j$。由于 $x_i \ne x_j$ 因此这些复数的模长也不会有一个是 $0$，得到的行列式结果也不会是 $0$（不过这里要说明满秩复系数方程组有唯一解，实际上复数不会影响我们证明实数时候的证明）。

## Fast Fourier Transform

记得我们之前说过的吗？

> 我们的优势在于：**我们可以任意选定要求的点值的横坐标。**

> **$n + 1$ 个点确定一个 $n$ 次复系数多项式。**

因此我们完全可以把我们的**横坐标设置为复数**，再进行求值和插值，也许就不同了。

**以下默认 $n$ 是 $2$ 的非负整数次幂，如果不是那么类似之前说的高位补零即可，这是为了之后的算法可以运行**。这对我们的算法只是常数上的影响。

以下默认我们是对某个**多项式** $f(x)$ 求 **$n$ 个点值**，且多项式的次数小于 $n$。

- 我们令 $\omega^{k}_{n} = e^{\frac{2k\pi}{n}i} = \cos(\frac{2k\pi}{n}) + i\sin(\frac{2k\pi}{n})$（这里看不懂没关系，重点是看懂图形），注意我们单位根的幂 $k$ 是完全可以大于 $n$ 的，此时它会产生循环。

我们发现：把 $\omega^{k}_{n}$ 画成点，其实就是**单位圆上的 $n$ 等分点。**

![](https://cdn.luogu.com.cn/upload/image_hosting/a87wqtxv.png)

单位根的模长都是 $1$，这样我们就完全不需要关心模长相乘了，只需要关心辐角。

并且通过欧拉公式，我们得到单位根的三个性质：

- $\omega^{n}_{n} = 1$（刚好转了一圈）。

- $\omega^{k}_{n} = \omega^{2k}_{2n}$（约分掉了）。

- $\omega^{k}_{n} = -\omega^{k + \frac{n}{2}}_{n}$（刚好转了半圈）。

**离散傅里叶变换**：已知多项式 $f(x)$，对 $0 \le k < n$，求$(\omega^{k}_{n},\,f(\omega^{k}_{n}))$，时间复杂度 $\Theta(n \log n)$。

**离散傅里叶逆变换**：已知 $n$ 个点值 $(\omega^{i}_{n},\,y_i)_{i = 0}^{n - 1}$，求其唯一对应的多项式 $f(x)$，使得 $f(x)$ 的次数为 $n - 1$ 且 $f(\omega^{i}_{n}) = y_i$。时间复杂度 $\Theta(n \log n)$。

> 一个小 hint：在 OI 中说 FFT 的复杂度是 $\Theta(n \log n)$ 是没有问题的，确实只进行 $\Theta(n \log n)$ 次浮点数的加减乘除，但是实际上 FFT 的模至少要是 $\Theta(\log n)$ 的，因此理论上我们使用的 SSA 算法是 $\Theta(n \log n \log \log n)$ 的。不过人类已经发明了严格 $\Theta(n \log n)$ 的多项式乘法的算法，参考 David Harvey 和 Joris van der Hoeven 的论文 `Integer multiplication in time O(n log n)`，这实际上是很新的成果。

- **离散傅里叶变换（DFT）**

这东西其实是简单分治算法。

注意以下默认 $n \ge 2$，如果 $n = 1$ 那我们直接返回就完了。

首先设 $f(x) = \sum\limits_{i = 0}^{n - 1}a_ix^i$ 是我们要求点值的多项式。

现在我们要求 $\omega_{n}^{k}$ 的点值对吧。FFT 会先把 $f(x)$ 奇偶位拆开。

$$
f(x) = a_0 + a_1x + a_2x^2 + \dots + a_{n - 1}x^{n - 1}\\
g(x) = a_0 + a_2x^2 + a_4x^4 + \dots + a_{n - 2}x^{n - 2}\\
h(x) = a_1 + a_3x^3 + a_5x^5 + \dots + a_{n - 1}x^{n - 1}\\
A(x) = a_0 + a_2x + a_4x^2 + \dots + a_{n - 2}x^{\frac{n}{2} - 1}\\
B(x) = a_1 + a_3x + a_5x^2 + \dots + a_{n - 1}x^{\frac{n}{2} - 1}\\
f(x) = A(x^2) + xB(x^2)
$$

现在考虑 $x = \omega^{k}_{n}$。

$$
\begin{aligned}
& f(\omega^{k}_{n}) \\
& = A(\omega^{2k}_{n}) + \omega^{k}_{n} \times B(\omega^{2k}_{n})\\
& = A(\omega^{k}_{\frac{n}{2}}) + \omega^{k}_{n} \times B(\omega^{k}_{\frac{n}{2}})
\end{aligned}
$$

感觉规律还不是很明显？考虑一下我们喜闻乐见的 $\omega^{k}_{n} = -\omega^{k + \frac{n}{2}}_{n}$。

$$
\begin{aligned}
& f(\omega^{k + \frac{n}{2}}_{n}) \\
& = A(\omega^{2k + n}_{n}) + \omega^{k + \frac{n}{2}}_{n} \times B(\omega^{2k + n}_{n})\\
& = A(\omega^{2k}_{n}) - \omega^{k}_{n} \times B(\omega^{2k}_{n})\\
& = A(\omega^{k}_{\frac{n}{2}}) - \omega^{k}_{n} \times B(\omega^{k}_{\frac{n}{2}})
\end{aligned}
$$

于是我们只要求出来 $A(\omega^{k}_{\frac{n}{2}})$ 和 $B(\omega^{k}_{\frac{n}{2}})$ 就可以算出 $f(\omega^{k}_{n})$ 和 $f(\omega^{k + \frac{n}{2}}_{n})$ 了！

很有分治的感觉，现在我们可以设计一个函数 `DFT`，输入了一个多项式 $f(x)$ 和其次数 $+ 1$ 的值 $n$。最后我们要返回 $n$ 个点，对于第 $k$ 个点横坐标为 $\omega^{k}_{n}$，纵坐标为 $f(\omega^{k}_{n})$。

我们把 $A(\omega^{k}_{\frac{n}{2}})$ 和 $B(\omega^{k}_{\frac{n}{2}})$ 的表达式写出来，注意这里 $k < \frac{n}{2}$，因为我们可以靠着 $k < \frac{n}{2}$ 这部分算出来  $f(\omega^{k + \frac{n}{2}}_{n})$。

那么对于 $A(x)$，其实就是已知多项式 $A(x)$ 长度为 $\frac{n}{2}$，求 $k = 0 \dots \frac{n}{2} - 1,\,(\omega^{k}_{\frac{n}{2}},\,A(\omega^{k}_{\frac{n}{2}}))$。对于 $B(x)$，也是已知多项式 $B(x)$ 长度为 $\frac{n}{2}$，求 $k = 0 \dots \frac{n}{2} - 1,\,(\omega^{k}_{\frac{n}{2}},\,B(\omega^{k}_{\frac{n}{2}}))$。

再对比一下，就是已知多项式 $A(x)$ 求 $\text{DFT}(A(x))$，已知多项式 $B(x)$ 求 $\text{DFT}(B(x))$！

于是我们直接写出代码。

```cpp
// 注意我们已经将多项式补为了 2 的幂
using ld = double; 
using cp = complex<ld>;
const ld pi = 3.141592653589;
#define rep(i, a, b) for (int i = a; i < b; i++)
void DFT(cp * a, int n) {
	if (n == 1) return;
	int mid = n >> 1; static cp b[N];
	rep(i, 0, mid) b[i] = a[i << 1], b[i + mid] = a[(i << 1) | 1];
	rep(i, 0, n) a[i] = b[i]; DFT(a, mid), DFT(a + mid, mid);
	cp w(1.0, 0.0), wn(cos(2.0 * pi / n), sin(2.0 * pi / n)); // wn 是 ω1n，初始 w 是 ω0n
	rep(i, 0, mid) {
		b[i] = a[i] + w * a[i + mid], b[i + mid] = a[i] - w * a[i + mid];
		w = w * wn;
	}
	rep(i, 0, n) a[i] = b[i];
}
```

时间复杂度 $T(n) = 2T(\frac{n}{2}) + \Theta(n)$ 由主定理得 $T(n) = \Theta(n \log n)$。

- **离散傅里叶逆变换（IDFT）**

现在我们已经知道了全体单位根的点值，怎么求出来多项式？

> 我们将单位根设置为其倒数，进行 DFT，然后再将所有数除以 $n$ 即可得到我们的多项式。

你如果没有任何线性代数基础，可以不关心证明。

我们求点值就是多项式当成向量，转置后左乘范德蒙矩阵，而**范德蒙矩阵的逆矩阵也很特殊**，我们对范德蒙矩阵的每个元素取倒数再除以 $n$ 即可得到范德蒙矩阵的逆矩阵（证明可以自行搜索）。

而我们 DFT 的过程其实就是用 $\Theta(n \log n)$ 的时间复杂度完成了这个单位根组成的矩阵和多项式向量的乘法，我们把单位根的倒数当成单位根，仍然不影响我们单位根的那三个性质，因此可以继续用 DFT 来求。

> 所以说重点是我们单位根的那三个性质，而不是我们单位根本身，比如 NTT 用的就是模意义下的原根。

因此我们只需要最后再除以 $n$ 就可以了。

```cpp
using ld = double; 
using cp = complex<ld>;
const ld pi = 3.141592653589;
#define rep(i, a, b) for (int i = a; i < b; i++)
void DFT(cp * a, int n, int f) {
    // 如果传入的参数 f 是 1，则表示是 DFT，否则是 IDFT
	if (n == 1) return;
	int mid = n >> 1; static cp b[N];
	rep(i, 0, mid) b[i] = a[i << 1], b[i + mid] = a[(i << 1) | 1];
	rep(i, 0, n) a[i] = b[i]; DFT(a, mid, f), DFT(a + mid, mid, f);
	cp w(1.0, 0.0), wn(cos(2.0 * pi / n), f * sin(2.0 * pi / n)); // wn 是 ω1n，初始 w 是 ω0n
	rep(i, 0, mid) {
		b[i] = a[i] + w * a[i + mid], b[i + mid] = a[i] - w * a[i + mid]; 
		w = w * wn;
	}
	rep(i, 0, n) a[i] = b[i];
}
```

然后得到我们的代码：

```cpp
cp a[N], c[N]; int n;
void work() {
	DFT(a, n, 1), DFT(c, n, 1);
	rep(i, 0, n) a[i] *= c[i]; DFT(a, n, -1);
	rep(i, 0, n) ans[i] = int(a[i].real() / (ld)n + 0.5L);
	rep(i, 0, n) ans[i + 1] += ans[i] / 10, ans[i] = ans[i] % 10;
}
```

- **一些常数优化**

FFT 是可以写成非递归的，我们接下来要从底向上开始，用倍增代替掉递归。

我们模拟拆分过程，实际上对于 $i$，它最后到达的位置是 $i$ 在二进制下翻转后的结果。比如对于 $6 = 110$，它最后到达的位置是 $3 = 011$。

我们可以用递推来 $\Theta(n)$ 计算每个数的二进制翻转。

```cpp
// bit 是 n - 1 的位数
rep(i, 0, n) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1)); 
```

这个递推的思想相对简单，留给读者自行思考。

- 蝶形运算

我们可以做到 $\Theta(1)$ 的额外空间进行 DFT。

简单来说，我们知道了 $A(\omega^{k}_{\frac{n}{2}})$ 和 $B(\omega^{k}_{\frac{n}{2}})$ 对吧，我们二进制翻转后，我们需要保证：

$A(\omega^{k}_{\frac{n}{2}})$ 存放在数组下标为 $k$ 的位置，$B(\omega^{k}_{\frac{n}{2}})$ 存放在数组下标为 $k + \frac{n}{2}$ 的位置。

然后我们就可以以从左到右的方式覆写数组的下标，而之前用过的下标之后显然是不会再用了，类似一个刷表法。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 3e6 + 10;
#define rep(i, a, b) for(int i = a; i < b; i++)
typedef double ld;
using cp = complex<ld>;
const ld pi = 3.141592653589; cp u, t;
int ans[N], bit = 0, rev[N];
void DFT(cp* a, int n, int f) {
	if (n == 1) return;
	rep(i, 0, n) if (i < rev[i]) swap(a[i], a[rev[i]]);
	for (int mid = 1; mid < n; mid <<= 1) {
		cp wn(cos(pi / (ld)mid), f * sin(pi / (ld)mid)); // 我们的 "n"
		for (int i = 0; i < n; i += (mid << 1)) {
			cp w(1.0, 0.0);
			for (int j = 0; j < mid; j++, w = w * wn) {
				u = a[i + j], t = w * a[i + j + mid];
				a[i + j] = u + t, a[i + j + mid] = u - t;
			}
		}
	}
}
cp a[N], c[N]; int n;
void work() {
	DFT(a, n, 1), DFT(c, n, 1);
	rep(i, 0, n) a[i] *= c[i]; DFT(a, n, -1);
	rep(i, 0, n) ans[i] = int(a[i].real() / (ld)n + 0.1);
	rep(i, 0, n) ans[i + 1] += ans[i] / 10, ans[i] = ans[i] % 10;
}
int main() {
	string s1, s2; cin >> s1 >> s2;
	rep(i, 0, s1.size()) a[i] = cp(s1[s1.size() - i - 1] - '0', 0);
	rep(i, 0, s2.size()) c[i] = cp(s2[s2.size() - i - 1] - '0', 0);
	n = 1; int len = s1.size() + s2.size() - 1;
	while (n <= len) n <<= 1, ++bit;
	rep(i, 0, n) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1)); work();
	len = s1.size() + s2.size() - 1;
	while (ans[len] == 0 && len) --len;
	for (int i = len; i >= 0; i--) cout << ans[i];
	return 0;
}
```

代码是很久之前写的，可能比较远古。

- **关于一些扩展**

FFT 的精度问题其实是比较大的，有些题让我们进行多项式乘法，并且系数对一个数（比如 $998244353$）取模。

或者没有取模，但是任意时刻我们的最大数都不会超过模数。

**快速数论变换 NTT**：模意义下的 FFT。

简单来说如果我们令 $n$ 为大于 $1$ 的 $2$ 的幂，并且 $p$ 为质数满足 $n \mid (p - 1)$，同时我们有 $g$ 是 $p$ 的一个原根。

- 原根你可以这样通俗的理解：一个数 $a$ 是模 $m$ 意义下的原根，当且仅当存在最小的一个 $k$ 使得 $a^k \equiv 1 \pmod m$，并且有 $k = \phi(m)$。

- 如果你学过群论，并且对于质数 $p$ 的剩余系，$a$ 的生成子群等于整个群，那么 $a$ 就是 $p$ 的原根。

这个有啥好处呢，我们设 $g_n = g^\frac{p - 1}{n}$，我们发现 $g^{k}_{n}$ 的性质包含了 $\omega^{k}_{n}$ 那三个性质。或者说，$\omega^{k}_{n}$ 在模 $p$ 意义下就是 $g^{k}_{n}$。

比如 $998244353 = 2^{23} \times 119 + 1$，那么这就是一个相当好用的模数。

然后我们的 $n$ 只要不超过 $2^{23}$，我们就可以用 NTT 来进行多项式乘法了（当然也因为这个，所以 NTT 的模数是相对受限的，比如我们一般不能用 $10^9 + 7$ 作为模数做 NTT）。

**更进一步的扩展**：如果我们要做多项式乘法，但是模数不是 NTT 模数，同时浮点数精度爆了怎么办？

1. 我们用三个模数跑 NTT！然后用 CRT 合并。当然这种方式要跑九遍 NTT，比较魔怔。

2. 把 FFT 拆成两段系数分别跑，据我所知一般是拆成五次 FFT 或者四次 FFT。似乎有拆成三次的做法，也挺魔怔的。

感兴趣者可以看看 P4245 这道题。

---

## 作者：masonxiong (赞：5)

# 前言

本篇题解主要介绍了快速傅里叶变换以及其优化技巧。

作者目前为本题最优解第二名。

# 快速傅里叶变换详解

快速傅里叶变换（Fast Fourier transform，FFT）是用于计算多项式乘法的重要算法，也是其它多项式算法的根本。

下面我将尽可能详细地讲解它。

## 前置知识

非常基础。

- 暴力高精度乘法。
- 初中数学知识。

## 从整数乘法到多项式乘法

首先使用小学学习竖式计算的时候就已经会了的拆位将整数拆开，变成一个多项式的表示形式。

举个例子：

$$
114514=1\cdot10^5+1\cdot10^4+4\cdot10^3+5\cdot10^2+1\cdot10^1+4\cdot10^0
$$

我们把拆开的式子中的 $10$ 看作 $x$，得到 $114514$ 所对应的多项式 $F(x)$：

$$
F(x)=1\cdot x^5+1\cdot x^4+4\cdot x^3+5\cdot x^2+1\cdot x^1+4\cdot x^0
$$

于是你完成了从整数乘法到多项式乘法的转换。非常简单，不是吗。

## 多项式乘法的一些记号

假设我们有多项式 $F(x)=\sum_{i=0}^nf_ix^i$，那么：

- 次数：$n$。**注意 $n$ 次多项式有 $n+1$ 项**。
- 系数：$f_i$ 被称作 $F$ 的 $i$ 次项系数。

## 别样的多项式表示形式

初中学平面直角坐标系时，我们已经充分掌握了用两个点确定一条直线解析式的能力，使用待定系数法列出方程即可。

我们又知道：$n$ 个等式可以得出 $n$ 元方程的解。那么我们得出结论：**用 $n+1$ 个点可以确定一个 $n$ 次多项式**。

例如直线就是一个一次多项式，它就可以用两个点确定。

那么我们不妨使用 $n+1$ 个点来表示多项式，这些点你可以随便选。这就是**多项式的点值表示法**。

## 点值表示法进行乘法

我们引用生物学上的一句话：“存在即合理”。这种点值表示法之所以被众多数学家采纳，它一定是有用的，其用处在于：乘法很好计算。

例如：我们有 $n$ 次多项式 $F(x)$，$m$ 次多项式 $G(x)$ 的点值表示法，求 $n+m$ 次多项式 $H(x)=F(x)\cdot G(x)$ 的点值表示法。

假设 $F(x)$ 上有 $(a,b)$，$G(x)$ 上有 $(a,c)$，那么 $H(x)$ 上就有 $(a,H(a))=(a,F(a)\cdot G(a))=(a,b\cdot c)$。我们这样就获得了 $H(x)$ 上的一个点。

只要我们从 $F(x)$ 和 $G(x)$ 上各找 $n+m+1$ 个点，我们就能求出 $H(x)$ 的点值表示法了，非常的方便。

## 傅里叶变换的流程

傅里叶采用了这种表示法，设计出了傅里叶变换，其主要流程非常简单自然：

1. 将 $F(x)$ 和 $G(x)$ 转成点值表示法。
2. 求 $H(x)$ 的点值表示法。
3. 根据 $H(x)$ 的点值表示法，求 $H(x)$ 的系数表示法。

显然步骤 2 比较简单，那么重点在于步骤 1 和 3，它们分别称作：

- 离散傅里叶变换（Discrete Fourier transform，DFT）
- 逆离散傅里叶变换（Inverse discrete Fourier transform，IDFT）

我们的神人为了高效执行这两个步骤，他决定：

- 将复数单位根 $\omega_{n+1}^0\sim\omega_{n+1}^n$ 代入多项式来求点值表示法。

接下来我们来讲解这个神秘方法的原理。但是在这之前，我们先需要学习复数的一些基本知识。

## 复数

首先我们定义 $i^2=-1$。复数是形如 $a+b\cdot i\space (a,b\in\R)$ 的数。

我们知道，实数 $a$ 可以用实数轴上的一个点进行表示。现在复数多了 $b\cdot i$ 这一项，我们不妨拉出一条纵向的虚数轴，组成一个**复平面直角坐标系**。

那么这里复数 $a+b\cdot i$ 就可以与点 $(a,b)$ 对应了。当然，你也可以使用类似于极坐标系的表示方法，把复数表示成 $r(\cos\theta+i\sin\theta)$ 的形式，其中 $r$ 是这个点到原点的距离，$\theta$ 是这个点到原点组成的直线与实数轴形成的夹角。

复数相关的记号：

- 实部：$a$。
- 虚部：$b$。
- 共轭：实部相同，虚部取相反数。
- 模长：极坐标表示法中的 $r$，也就是 $\sqrt{a^2+b^2}$。
- 幅角：极坐标表示法中的 $\theta$，也就是 $\arctan\frac ba$。

复数相关的基本运算：

- 加法：$(a+b\cdot i)+(c+d\cdot i)=(a+c)+(b+d)\cdot i$。实部、虚部分别相加。

- 减法：$(a+b\cdot i)-(c+d\cdot i)=(a-c)+(b-d)\cdot i$。实部、虚部分别相减。

- 乘法：$(a+b\cdot i)\cdot(c+d\cdot i)=(a\cdot c-b\cdot d)+(a\cdot d+b\cdot c)\cdot i$。直接按整式运算法则展开即可。

- 除法：$\frac{a+b\cdot i}{c+d\cdot i}=\frac{a\cdot c+b\cdot d}{c^2+d^2}+\frac{a\cdot d+b\cdot c}{c^2+d^2}\cdot i$。类比“分母有理化”。

### 复数乘法的几何意义

我们不妨采用更加贴近几何的类似于极坐标的表示法：

$$
\begin{align}
r_1(\cos\theta_1+i\sin\theta_1)\cdot r_2(\cos\theta_2+i\sin\theta_2)\\
=r_1r_2(\cos\theta_1\cos\theta_2-\sin\theta_1\sin\theta_2+i(\sin\theta_1\cos\theta_2+\cos\theta_1\sin\theta_2))\\
=r_1r_2(\cos(\theta_1+\theta_2)+i\sin(\theta_1+\theta_2))
\end{align}
$$

解释：

1. 极坐标表示法。
2. 直接乘，暴力展开，提出 $r_1r_2$。
3. 三角函数的和差公式。

你发现这得出了一个新的复数：

- 其模长为原先两个复数的模长的乘积。
- 其幅角为原先两个复数的幅角的和。

**这一结论非常的重要**。无论是数学还是 OI。

### 单位根

定义：若复数 $c$ 满足 $c^n=1\space(n\in\N^*)$，则称 $c$ 为一个 $n$ 次单位根。如何求解呢？

首先 $1$ 可以表示为 $1+0\cdot i$，也就是一个模长为 $1$ 的复数。根据前一节提到的复数相乘几何意义，若 $c$ 的模长大于 $1$，那模长肯定越乘越长，不可能达到 $1$；若 $c$ 的模长小于 $1$，那模长肯定越乘越小，也不可能达到 $1$。

那么可能单位根的复数模长一定为 $1$。根据几何意义，我们发现：这是复平面直角坐标系上，以原点为圆心，半径为 $1$ 的圆。学过高中三角函数的知道，这是单位圆。

由于模长肯定为 $1$，我们可以抛开不看，我们只关心幅角。不妨假设 $c$ 的幅角为 $\theta$，那么根据复数相乘的几何意义，$c^n$ 的幅角为 $n\cdot\theta$，若它是单位根，那这个角度一定和 $1+0\cdot i$ 的角度重合（也就是和实数轴重合）。

我们发现：幅角为 $\frac kn\cdot2\pi\space(k\in\N\cap[0,n))$（这里 $2\pi$ 是弧度制表示法，没学过的话把它当 $360\degree$ 看）的复数都是单位根，因为它们的幅角自乘 $n$ 倍后为 $k\cdot 2\pi$，而 $k$ 是整数，所以说明它旋转了周角的整数倍，也就是转回来了。

这些复数共有 $n$ 个。根据代数基本定理: $n$ 次方程在复数域内有且只有 $n$ 个根，所以这些就是所有的单位根。

几何意义上来说，这些单位根把单位圆划分成 $n$ 个相同的扇形。我们从复数 $1$ 开始，逆时针将这些复数标号 $0\sim n-1$，分别记作 $\omega_n^0,\omega_n^1,\cdots,\omega_n^{n-1}$。

### 单位根相关性质

单位根有一些相当重要的性质：

1. $\omega_n^0=1$。这是定义的一部分。

2. $(\omega_n^1)^k=\omega_n^k$。根据复数乘法的几何意义以及单位根的定义，每乘上一个 $\omega_n^1$ 就相当于逆时针旋转了 $\frac1n\cdot2\pi$，乘上 $k$ 个就相当于旋转了 $\frac kn\cdot2\pi$，就是 $\omega_n^k$ 了。

3. $\omega_n^p\cdot\omega_n^q=\omega_n^{p+q}$。由 2 以及幂运算法则：$\omega_n^p\cdot\omega_n^q=(\omega_n^1)^p\cdot(\omega_n^1)^q=(\omega_n^1)^{p+q}=\omega_n^{p+q}$。

4. $\omega_{2n}^{2k}=\omega_n^k$。$\omega_{2n}^{2k}$ 转了 $\frac{2k}{2n}\cdot2\pi=\frac kn\cdot2\pi$，就是 $\omega_n^k$ 转过的角度。

6. $\omega_{2n}^{k+n}=-\omega_{2n}^k$。根据 3：$\omega_{2n}^{k+n}=\omega_{2n}^k\cdot\omega_{2n}^n$，后者相当于 $1$ 转过 $\frac{n}{2n}\cdot2\pi=\pi$ 角度，也就是转到了 $-1$，乘起来自然就是 $-\omega_{2n}^k$ 了。

## 回归算法本身

现在我们已经学习了所有需要学的内容，下面我们来实现离散傅里叶变换和逆离散傅里叶变换吧。

### 离散傅里叶变换

假设有 $n=2^k\space(k\in\N^*)$，对于一个 $n-1$ 次多项式 $F(x)=\sum_{i=0}^{n-1}f_ix^i$，我们将其按次数的奇偶拆成两个部分：

- $F_1(x)=\sum_{i=0}^{\frac n2-1}f_{2i}x^i=f_0x^0+f_2x^1+f_4x^2+\cdots+f_{n-2}x^{\frac 2n-1}$

- $F_2(x)=\sum_{i=0}^{\frac n2-1}f_{2i+1}x^i=f_1x^0+f_3x^1+f_5x^2+\cdots+f_{n-1}x^{\frac 2n-1}$。

那么就有 $F(x)=F_1(x^2)+x\cdot F_2(x)$。下面是离散傅里叶变换的精髓，代入单位根：

首先代入 $\omega_n^k$ 得到：

$$
\begin{align}
F(\omega_n^k)=F_1((\omega_n^k)^2)+\omega_n^k\cdot F_2((\omega_n^k)^2)\\
=F_1(\omega_n^{2k})+\omega_n^k\cdot F_2(\omega_n^{2k})\\
=F_1(\omega_{\frac n2}^k)+\omega_n^k\cdot F_2(\omega_{\frac n2}^k)
\end{align}
$$

解释：

4. 直接代入。
5. 根据单位根性质 2。
6. 根据单位根性质 4。

这个式子有什么用呢？假设我们有 $F_1(x)$ 和 $F_2(x)$ 在 $\omega_{\frac n2}^{0\sim\frac n2-1}$ 的点值，**我们就可以 $O(n)$ 求出 $F(x)$ 在 $\omega_n^{0\sim\frac n2-1}$ 的点值**。

但是我们这时候还缺 $\frac n2$ 个点，不过我们还可以代入 $\omega_n^{k+\frac n2}$：

$$
\begin{align}
F(\omega_n^{k+\frac n2})=F_1((\omega_n^{k+\frac n2})^2)+\omega_n^{k+\frac n2}\cdot F_2((\omega_n^{k+\frac n2})^2)\\
=F_1(\omega_n^{2k+n})+\omega_n^{k+\frac n2}\cdot F_2(\omega_n^{2k+n})\\
=F_1(\omega_n^{2k})+\omega_n^{k+\frac n2}\cdot F_2(\omega_n^{2k})\\
=F_1(\omega_{\frac n2}^k)+\omega_n^{k+\frac n2}\cdot F_2(\omega_{\frac n2}^k)\\
=F_1(\omega_{\frac n2}^k)-\omega_n^k\cdot F_2(\omega_{\frac n2}^k)
\end{align}
$$

解释：

7. 直接代入。
8. 根据单位根性质 2。
9. 单位根可以减去整圈数。
10. 根据单位根性质 4。
11. 根据单位根性质 5。

再运用这个式子，你就又 $O(n)$ 求出了 $F(x)$ 在 $\omega_n^{\frac n2\sim n-1}$ 的点值。再看看上一个式子，我们就有了 $n$ 个点值。

那么我们就实现了**根据 $F_1(x)$ 和 $F_2(x)$ 的点值 $O(n)$ 计算 $F(x)$**。然后我们递归利用这个方法解决 $F_1(x)$ 和 $F_2(x)$ 的求值即可。

时间复杂度分析和归并排序类似，为 $O(n\log n)$，我们实现了离散傅里叶变换！

### 逆离散傅里叶变换

假设我们对 $F(x)$ 执行离散傅里叶变换，得到了 $F(x)$ 在 $\omega_n^{0\sim n-1}$ 上的点值，现在我们要求 $F(x)$ 的系数表达式，也就是求 $f$。

令 $G(k)$ 为 $F(x)$ 在 $\omega_n^k$ 上的点值，即 $G(k)=F(\omega_n^k)$。先说结论：$f_k=\frac1n\sum_{i=0}^{n-1}(\omega_n^{-k})^iG(i)$，我们进行证明。

首先展开 $G(k)$ 的定义：

$$
\begin{align}
G(k)=F(\omega_n^k)\\
=\sum_{i=0}^{n-1}(\omega_n^k)^if_i
\end{align}
$$

解释：

12. $G(k)$ 定义。
13. $F(x)$ 定义。

然后将结论代入：

$$
\begin{align}
=\frac1n\sum_{i=0}^{n-1}(\omega_n^k)^i\sum_{j=0}^{n-1}(\omega_n^{-i})^jG(j)\\
=\frac1n\sum_{i=0}^{n-1}\sum_{j=0}^{n-1}\omega_n^{ik-ij}G(j)
\end{align}
$$

解释：

14. 直接代入。
15. 交换求和顺序。

分类讨论：

- $j=k$。此时的贡献为：

$$
\begin{align}
\frac1n\sum_{i=0}^{n-1}\omega_n^0G(k)\\
=\frac1n\cdot n\cdot G(k)\\
=G(k)
\end{align}
$$

解释：

16. 代入。
17. $\omega_n^0=1$，$n$ 次加法就是乘上 $n$。
18. 显然。

- $j\ne k$。令 $t=k-j$，此时的贡献为：

$$
\begin{align}
\frac1n\sum_{i=0}^{n-1}\omega_n^{i\cdot t}G(j)\\
=\frac1n\sum_{i=0}^{n-1}\omega_n^{i\cdot t}G(k-t)\\
=\frac1n\omega_i^t\bigg(\sum_{i=0}^{n-1}\omega_n^i\bigg)G(k-t)\\
=\frac1n\omega_i^t\cdot0\cdot G(k-t)\\
=0
\end{align}
$$

解释：

19. 代入。
20. $t=k-j\implies j=k-t$。
21. $\omega_n^{i\cdot t}=\omega_n^t\cdot\omega_n^i$，然后提出公因式 $\omega_n^t$。
22. 根据定义，$\omega_n^i$ 构成等比数列，公比为 $\omega_n^1$。使用等比数列求和公式可得。
23. 显然。

两部分的贡献加起来显然为 $G(k)$，这证明了我们的结论是正确的。

然后你发现这个和离散傅里叶变换的式子很像，区别仅有：

- 最后的答案要除以 $n$。
- 将 $\omega_n^1$ 替换为 $\omega_n^{-1}$。

那么我们逆离散傅里叶变换的部分也讲完了。

## 快速傅里叶变换的流程总结

我们已经知道了两个关键步骤的实现，下面总结一下流程：

1. 将两个多项式 $F(x)$ 和 $G(x)$ 补齐到 $n-1$ 次，其中 $n=2^k\space(k\in\N^*)$。
3. 分别对它们进行离散傅里叶变换，得到点值 $F'(k)$ 和 $G'(k)$。
4. 将点值函数对位相乘，得到新的点值 $H'(k)$。
5. 对 $H'(k)$ 进行逆离散傅里叶变换，得到多项式 $H(x)$ 的系数表示。
6. 将 $H(x)$ 缩减到其应有的长度。

# 高精度乘法优化

如果你按照以上流程写了一份快速傅里叶变换实现的高精度乘法，你会发现要么有些点超时了，要么就是过了但跑的巨慢（6 秒左右，甚至会更慢）。

同时，如果你尝试过 Python 的话，你发现用 Python 写的高精度乘法只用了 1 秒多。况且翻翻 Python 底层代码，发现它用的是 $O(n^{\log_23})\approx O(n^{1.58})$ 的 Karatsuba 分治乘法，复杂度甚至劣于快速傅里叶变换，但跑得却比我们快得多。

这样大的常数我们是无法忍受的，下面我们对它进行效果显著的优化。

## 分治转倍增

我们发现在递归分治的过程中，发生了一些很影响效率的事情：

- 分治时，我们将奇数项系数与偶数项系数分开，使用了大量的内存移动。
- 合并时，我们也使用了临时的内存附注计算，使用了大量的内存移动。
- 递归本身带来了额外的额外开销。

那么我们把递归分治转成迭代倍增，就可以解决以上所有问题。

无法直接转化为迭代实现的一个重要原因就是：你不知道一个元素在分治结束后的位置。那么我们为了转成迭代，我们不妨打表，然后发现这样一条规律：**一个元素分治后的位置的二进制表示，是其分治前的位置的二进制表示的位逆序置换**。

用人话说，就是把原先位置的二进制倒过来就可以得到新的位置了。下面我们对这一结论进行简单的证明。

令 $R(n,k)$ 表示一个 $n$ 项多项式中原先位置为 $k$ 的元素分治后的位置。根据定义，有：

$$
\begin{cases}
R(1,k)=k\\
R(n,k)=(k\otimes1)\texttt{ << }(n-1)+R(n-1,k\texttt{ >> }1)
\end{cases}
$$

解释：

1. 只有一项时不分治，显然位置不动。
2. 将奇数项 $[k\otimes1=1]$ 移动到左边，偶数项放到右边。

将其展开，得到：

$$
R(n,k)=\sum_{i=0}^{n-1}((k\texttt{ >> }i)\otimes1)\texttt{ << }(n-i-1)
$$

解释这个式子，就是：将 $k$ 的第 $i$ 位移动到第 $n-i-1$ 位。这正是“位逆序置换”。

有了这条结论，我们就可以：

- 在开始时将每个元素移动到其分治后的位置上（模拟分治过程）。
- 然后，倍增地去合并它们。

同时你发现，在使用位逆序置换后，当你想要合并，也就是通过 $F_1(\omega_n^k)$ 以及 $F_2(\omega_n^{k+\frac n2})$ 时求 $F(\omega_n^k)$ 和 $F(\omega_n^{k+\frac n2})$ 时，你发现：

- $F_1(\omega_n^k)$ 的值存储在整体数组位置 $k$ 上，$F_2(\omega_n^{k+\frac n2})$ 的值存储在整体数组位置 $k+\frac n2$ 上（因为我们已经提前进行了置换，其位置不会改变了）。
- $F(\omega_n^k)$ 的值**应当**存储在整体数组位置 $k$ 上，$F(\omega_n^{k+\frac n2})$ 的值**应当**存储在整体数组位置 $k+\frac n2$ 上。

于是我们避免了原先递归那样额外开数组然后再复制的操作，直接原位合并，省下了空间和时间。那么现在的关键就在于：如何求位逆序置换。

首先我们假设 $P(x)$ 为 $x$ 的位逆序置换，那么有 $P(x)=P(x\texttt{ >> }1)\texttt{ >> }1+(x\otimes1)\texttt{ << }(n-1)$。

解释：

- $P(x\texttt{ >> }1)$ 是 $x$ 从最高位到倒数第二位的位逆序置换，再右移一位是因为置换后“最高位到倒数第二位”被换到了“次高位到倒数第一位”。
- $(x\otimes1)\texttt{ << }(n-1)$ 是倒数第一位置换后的结果。

于是我们从小到大计算 $P(x)$ 即可。以上是快速傅里叶变换经典优化方法，加上这些优化完全足够了。

## 压位

这是针对高精度计算的经典优化。

将连续的 $w$ 个数位压缩至一个数进行存储，可以有效提升效率。一般取 $w=8$，用 $32$ 位无符号整数 `std::uint32_t (unsigned int)` 进行存储。

## 预处理单位根

这一点是显然的。你单次计算单位根需要调用三角函数，效率非常低。不如我们直接在最开始就把所有单位根算出来。

首先一种朴素的想法是：对于每一个单位根的计算，我们都调用三角函数。这种方法效率是极低的，虽然比之前的方法好一些。

另一种朴素的想法是：先用三角函数计算 $\omega_n^1$，然后根据 $\omega_n^i\cdot\omega_n^j=\omega_n^{i+j}$ 依次用 $\omega_n^1$ 递推转移。这种方法效率是高了，但是精度没有保障。

我们采取一种折中的方法：对于所有 $i=2^k\space(k\in\N^*)$ 的 $\omega_n^i$，我们调用三角函数进行计算；剩下的，我们有 $\omega_n^i=\omega_n^{\operatorname{lowbit}(i)}\cdot\omega_n^{i-\operatorname{lowbit}(i)}$。这种方法只用 $\log n$ 次三角函数调用，同时每一个 $\omega_n^i$ 都至多在 $\log n$ 次递推内算出。

## 内存访问优化

普通的逆序位置换方法设计了大量的内存随机访问，会增加一定的常数。稍微重新排布一下置换以及合并的顺序，确保内存顺序访问，可以保证缓存友好，加快一定的运行速度。

比如我的代码使用了一种隐式的逆序位置换的策略，甚至还避免了重排。

同时，你可以使用迭代器以及指针来代替朴素的数组下标访问以获得更小的常数。

## 更高效的复数类

你发现 `std::complex` 似乎速度并不快，它底层的乘法实现仍然是四次乘法。

不妨我们自己写一个基于 AVX2 指令集 `__m128d` 的复数类：

```cpp
struct Complex {
    __m128d value;

    Complex() = default;

    Complex(__m128d initialValue) : value(initialValue) {}

    Complex(double real, double imagine = 0.0) : value(_mm_set_pd(imagine, real)) {}

    Complex operator+(Complex other) const {
        return value + other.value;
    }

    Complex operator-(Complex other) const {
        return value - other.value;
    }

    Complex operator*(Complex other) const {
        return _mm_fmaddsub_pd(_mm_unpacklo_pd(value, value), other.value, _mm_unpackhi_pd(value, value) * _mm_permute_pd(other.value, 1));
    }

    Complex operator*(double other) const {
        return value * _mm_set1_pd(other);
    }

    double real() {
        return value[0];
    }

    double imag() {
        return value[1];
    }
};
```

# 代码

完整代码见[提交记录](https://www.luogu.com.cn/record/218767773)，这里只放上快速傅里叶变换相关的部分。

值得一提的是，这个模板居然跑的比那些大力循环展开（放眼望去，满屏幕的 `switch case`）的代码跑的快了大约 120ms。

```cpp
#include <bits/stdc++.h>

struct Transform {
    static constexpr std::int64_t Base = 100000000, FFTBase = 10000;
    static constexpr std::double_t Pi = 3.141592653589793;

    static std::vector<std::complex<std::double_t>> omega;

    static void initialize(std::size_t length) {
        if (length > omega.size() << 1) {
            std::size_t temp = std::__lg(length - 1);
            omega.resize(length = 1 << temp), omega[0] = 1.0;
            for (std::size_t i = 1; i < length; i <<= 1)
                omega[i] = std::polar(1.0, Pi / (i << 1));
            for (std::size_t i = 1; i < length; ++i)
                omega[i] = omega[i & (i - 1)] * omega[i & -i];
        }
    }

    static void  DFT(std::vector<std::complex<std::double_t>>& array) {
        for (std::size_t left = array.size() >> 1, right = array.size(); left; left >>= 1, right >>= 1) {
            for (std::size_t i = 0; i < left; ++i) {
                const std::complex<std::double_t> A = array[i], B = array[i + left];
                array[i] = A + B, array[i + left] = A - B;
            }
            auto index = omega.begin() + 1;
            for (std::size_t i = right; i < array.size(); i += right, ++index) {
                for (std::size_t j = i; j < i + left; ++j) {
                    const std::complex<std::double_t> A = array[j], B = array[j + left] * *index;
                    array[j] = A + B, array[j + left] = A - B;
                }
            }
        }
    }

    static void  IDFT(std::vector<std::complex<std::double_t>>& array) {
        for (std::size_t left = 1, right = 2; left < array.size(); left <<= 1, right <<= 1) {
            for (std::size_t i = 0; i < left; ++i) {
                const std::complex<std::double_t> A = array[i], B = array[i + left];
                array[i] = A + B, array[i + left] = A - B;
            }
            auto index = omega.begin() + 1;
            for (std::size_t i = right; i < array.size(); i += right, ++index) {
                for (std::size_t j = i; j < i + left; ++j) {
                    const std::complex<std::double_t> A = array[j], B = array[j + left];
                    array[j] = A + B, array[j + left] = (A - B) * std::conj(*index);
                }
            }
        }
    }

    static void convolution(std::vector<std::complex<std::double_t>>& A, std::vector<std::complex<std::double_t>>& B) {
        Transform::initialize(A.size()), Transform:: DFT(A), Transform:: DFT(B);
        const std::double_t inverse = 1.0 / A.size(), quarterInverse = 0.25 * inverse;
        A.front() = std::complex<std::double_t>(
            A.front().real() * B.front().real() + A.front().imag() * B.front().imag(),
            A.front().real() * B.front().imag() + A.front().imag() * B.front().real()
        ), A.front() *= inverse, A[1] *= B[1] * inverse;

        for (std::size_t k = 2, m = 3; k < A.size(); k <<= 1, m <<= 1) {
            for (std::size_t i = k, j = i + k - 1; i < m; ++i, --j) {
                const std::complex<std::double_t> oi = A[i] + std::conj(A[j]), hi = A[i] - std::conj(A[j]);
                const std::complex<std::double_t> Oi = B[i] + std::conj(B[j]), Hi = B[i] - std::conj(B[j]);
                const std::complex<std::double_t> r0 = oi * Oi - hi * Hi * ((i & 1) ? -omega[i >> 1] : omega[i >> 1]), r1 = Oi * hi + oi * Hi;
                A[i] = (r0 + r1) * quarterInverse, A[j] = std::conj(r0 - r1) * quarterInverse;
            }
        }
        Transform:: IDFT(A);
    }

    static void multiply(std::vector<std::int64_t>& A, const std::vector<std::int64_t>& B) {
        const std::size_t sizeA = A.size(), sizeB = B.size(), size = 2 << std::__lg(sizeA + sizeB - 1);
        std::vector<std::complex<std::double_t>> cA(size, 0.0), cB(size, 0.0);
        std::transform(A.begin(), A.end(), cA.begin(), [](std::int64_t element) {
            return std::complex<std::double_t>(element % FFTBase, element / FFTBase);
        });
        std::transform(B.begin(), B.end(), cB.begin(), [](std::int64_t element) {
            return std::complex<std::double_t>(element % FFTBase, element / FFTBase);
        });
        std::int64_t sum = 0;
        convolution(cA, cB), A.resize(sizeA + sizeB);
        std::transform(cA.begin(), cA.begin() + A.size(), A.begin(), [&](std::complex<std::double_t> element) {
            sum += std::int64_t(element.real() + 0.5) + std::int64_t(element.imag() + 0.5) * FFTBase;
            std::int64_t result = sum % Base;
            return sum /= Base, result;
        });
    }
};
```

---

## 作者：Sunrise_beforeglow (赞：3)

# 了解 FFT

由于本人是 xxs，数学学的不多，还请多多谅解。

## 前情提要

我们都知道，高中数学有一个叫做复数的东西。

虚数单位 $i$ 其实就是用来表示 $x^2=-1$ 的根。

为什么一定要弄一个这个东西呢，因为我们知道平方具有非负性，但虚数不一样，$i^2=-1$，也就是 $i=\sqrt{-1}$。

那么复数，其实就是 $a+bi$ 的形式，其中 $a,b\in \mathbb{R}$。

然后这个东西的加减乘除并不复杂，它也满足结合律，所以可以直接使用乘法、加法结合律计算，比如 $(a+bi)(c+di)=ac+i^2bd+i(ad+bc)=ac-bd+i(ad+bc)$。

这个复数在编程中可以手写，也可以使用 STL 中的 `complex` 项。

这里我放上自己手写的：

```cpp
struct node
{
    double x,y;
    node operator +(const node &g)const{return {g.x+x,g.y+y};}
    node operator -(const node &g)const{return {x-g.x,y-g.y};}
    node operator *(const node &g)const{return {g.x*x-g.y*y,g.x*y+g.y*x};}
};
```

那么我们其实可以将它一一映射到平面直角坐标系上，其中 $a+bi$ 在坐标系上可以唯一表示为点 $(a,b)$。

我们再在坐标系上画出一个单位圆，它的方程为 $(x-0)^2+(y-0)^2=1$，意思是所有 $(x,y)$ 满足与 $(0,0)$ 距离为 $1$ 的点。

那么了解 FFT 之前，我们需要知道 $n$ 次单位根，我们定义 $\omega_n^1$ 为方程 $x^n=1$ 的根。

那么所有的根分别为 $\omega_n^0,\omega_n^1\cdots \omega_{n}^{n-1}$。

这几个数的复数表示分别为 $1,\cos(\dfrac{2\pi}{n})+i\sin(\dfrac{2\pi}{n})\cdots \cos((n-1)\dfrac{2\pi}{n})+i\sin((n-1)\dfrac{2\pi}{n})$，也就是把单位圆平均分成 $n$ 份。

大概的示意图就是这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/3fllo7y7.png)

我知道你们有很多疑问，让我们一个个解决。

为了方便，令 $\alpha=\dfrac{2\pi}{n}$。

首先我们需要知道单位圆的参数方程：

$$
\begin{cases}
x=\cos\alpha\\
y=\sin\alpha
\end{cases}
$$

这个很好证，把这个带入单位圆的方程即可，意思是从 $x$ 轴开始，在单位圆上逆时针转 $\alpha$ 度。

所以这 $n$ 个根都在单位圆上。

接下来，我们需要知道，当我们已经定义 $w_n^1=\cos\alpha +i\sin \alpha$ 时，为什么 $w_n^x=\cos x\alpha+i\sin x\alpha$。

我们可以使用归纳法证明：

- 当 $x=1$ 时，显然成立。

- 假设 $x=k-1$ 时成立，那么 $x=k$ 时。

$$w_n^k=w_n^{k-1}\times w_n^1=(\cos(k-1)\alpha+i\sin(k-1)\alpha)(\cos \alpha +i\sin \alpha)$$

$$=\cos k\alpha+i\sin k\alpha$$

所以，$(w_n^i)^n=w_n^{ni}=\cos2\pi i+i\sin2\pi i=1$。

于是 $w_n^0,w_n^1\cdots w_n^{n-1}$ 为方程 $x^n=1$ 的 $n$ 个复数根。

于是，从几何意义上看，我们知道了 $\omega_{2n}^k=-\omega_{2n}^{k+n}$。

我们还要了解多项式。

什么是多项式，我们定义一个 $n$ 次多项式 $f(x)=a_{n-1}x^{n-1}\cdots a_0x_0=\sum\limits_{i=0}^{n-1}a_ix^i$。

那么求 $f(x)$ 的值，就是把 $x$ 代入这个多项式。

我们也可以使用 $(x_0,y_0)\cdots (x_{n-1},y_{n-1})$ 这 $n$ 个点来唯一确定这个多项式，毕竟这 $n$ 个方程可以唯一确定这 $n$ 个系数。

## 正片开始

FFT，其实就是把系数表示法转换为点值表示法，再转换为系数表示法，进而加速多项式运算的过程。

### FFT 正变换

我们可以做如下变换：

$$\sum_{i=0}^{n-1}a_ix^i=\sum_{i=0}^{\frac{n}{2}-1}a_{2i}x^{2i}+x\sum_{i=0}^{\frac{n}{2}-1}a_{2i}x^{2i}$$

然后我们令 $F(x)=\sum\limits_{i=0}^{\frac{n}{2}-1}a_{2i}x^{2i},G(x)=\sum\limits_{i=0}^{\frac{n}{2}-1}a_{2i}x^{2i}$ 不难发现它们均为偶函数。

所以 $f(\omega_n^k)=F(\omega_n^k)+\omega_n^kG(\omega_n^k)$。

$f(\omega_n^{k+\frac{n}{2}})=F(\omega_n^k)-\omega_n^kG(\omega_n^k)$。

也就是说，我们只要递归求解 $F(\omega_n^k)$ 与 $G(\omega_n^k)$ 的值，就可以知道 $f(\omega_n^k)$ 与 $f(\omega_n^{k+\frac{n}{2}})$ 的值。将它转化为点值表示法。

那么时间复杂度是多少，我们发现，一共会递归 $\log_2n$ 层，每层需要花 $O(n)$ 的代价合并，所以总时间复杂度 $O(n\log_2n)$。

然后我们发现由于总是出现 $\dfrac{n}{2}$ 所以我们不妨把 $n$ 直接补成二的若干次方的形式。

然后我们如果要求 $f(x)g(x)$ 的点值表示法，我们可以求出 $f(\omega_n^i)$ 和 $g(\omega_{n}^i)$ 表示的值，那么 $f(x)g(x)$ 在 $\omega_{n}^i$ 对应的值为 $f(\omega_n^i)g(\omega_{n}^i)$。

### FFT 逆变换

假设一个多项式 $h(x)=\sum\limits_{i=0}^{n-1}a_ix^i$，现在我们已经知道了它的点值表示法 $(\omega_{n}^0,h(\omega_{n}^0))\cdots (\omega_{n}^{n-1},h(\omega_{n}^{n-1}))$。

现在我们需要根据点值表示法反推系数表示法。

我们干一个很匪夷所思的事情。

我们把它的点值表示法看成系数表示法。

也就是定义 $H(x)=\sum\limits_{i=0}^{n-1}x^i(\sum\limits_{j=0}^{n-1}a_j\omega_n^{ij})$。

然后我们以 $H(x)$ 做一次 FFT，只不过这一次单位根要换成 $\omega_n^{-k}$。

那么接下来我们推一下 $H(\omega_n^{-k})$。

$$H(\omega_n^{-k})=\sum\limits_{i=0}^{n-1}\omega_n^{-ik}(\sum\limits_{j=0}^{n-1}a_j\omega_n^{ij})$$

$$=\sum\limits_{i=0}^{n-1}(\sum\limits_{j=0}^{n-1}a_j\omega_n^{ij}\omega_n^{-ik})$$

$$=\sum\limits_{i=0}^{n-1}(a_k+\sum\limits_{j=0,j\neq k}^{n-1}a_j\omega_n^{i(j-k)})$$

$$=na_k+\sum_{j=0,j\neq k}^{n-1}\omega_n^{j-k}a_j\sum_{i=0}^{n-1}\omega_{n}^i$$

又 $\sum\limits_{i=0}^{n-1}\omega_n^i=\dfrac{\omega_n^n-\omega_n^0}{\omega_n^1-1}=0$。

所以原式等于 $na_k$。

所以做一次 FFT 之后，把得到的系数除以 $n$ 即可，时间复杂度 $O(n\log_2n)$。

```cpp
//这里node是我自己写的一个复数项
void FFT(node y[],int x,int type)//系数，长度，正变换或逆变换
{
    if(x==1)return;//当只剩常数项，直接返回
    node u[x/2+1],v[x/2+1];//为了节省空间，保证每一层空间都是O(n)复杂度
    for(int i=0;i<x;i+=2)u[i/2]=y[i],v[i/2]=y[i+1];//装填系数
    FFT(u,x/2,type);
    FFT(v,x/2,type);
    node w={cos(2*PI*type/x),sin(2*PI*type/x)},W={1,0};//预处理单位根
    //W其实就是单位根的i次方
    for(int i=0;i<x/2;i++)
    {
        y[i]=u[i]+W*v[i];
        y[i+x/2]=u[i]-W*v[i];
        W=W*w;//每次让W乘上一个单位根，使次数+1
    }
}
```

空间复杂度 $O(n\log_2n)$。

不过这个东西可以 AC 另一道模板题。

## 我们继续提高难度

我们发现，递归 FFT 的缺点就是常数太大。

递归的常数过于大了。

那有没有什么办法，使得我们不需要递归呢？

有的兄弟有的。这时候就要讲一下蝶形算法优化。

我们假设函数 $f(n,a)$ 表示编号为 $a$ 的数最后经过 FFT 之后会变到哪里。

1. 如果 $a\equiv 1\pmod 2$。那么偶数项都会排到前面，所以 $f(n,a)=2^{n-1}+f(\dfrac{n}{2},\lfloor\dfrac{a}{2}\rfloor)$。

2. 如果 $2\mid a$，那么它会排到前半列，所以 $f(n,a)=f(\dfrac{n}{2}，\dfrac{a}{2})$。

设 $n=2^k$。

我们发现，如果把它看成二进制有 $k$ 位的数，那么如果这个数最低位有一，那么最后的顺序的最高位就有一。

这不是**把这个二进制数直接翻转**的结果吗！

比如我们举个栗子。

$$\omega_8^0,\omega_8^1,\omega_8^2,\omega_8^3,\omega_8^4,\omega_8^5,\omega_8^6,\omega_8^7$$

变换一次：$\omega_8^0,\omega_8^2,\omega_8^4,\omega_8^6|\omega_8^1,\omega_8^3,\omega_8^5,\omega_8^7$。

变换两次：$\omega_8^0,\omega_8^4|\omega_8^2,\omega_8^6|\omega_8^1,\omega_8^5|\omega_8^3,\omega_8^7$。

变换最终结果：$\omega_8^0|\omega_8^4|\omega_8^2|\omega_8^6|\omega_8^1|\omega_8^5|\omega_8^3|\omega_8^7$。

只看次数：$(000)_2,(100)_2,(010)_2,(110)_2,(001)_2,(101)_2,(011)_2,(111)_2$。

最终顺序：$(000)_2,(001)_2,(010)_2,(011)_2,(100)_2,(101)_2,(110)_2,(111)_2$。

如何求解一个数翻转二进制位得到的数？

设它为 $res_i$，那么 $res_i=res_{i\div 2}\div 2+[2\nmid i]\times 2^{n-1}$。

什么意思？$[2\nmid i]$ 是指当 $i$ 为奇数时返回 $1$，否则返回 $0$。所以 $[2\nmid i]\times 2^{n-1}$ 就代表翻转之后 $i$ 的最高位。

$res_{i\div 2}$ 意思就是把 $i$ 的最低位去掉，然后翻转。但我们想要的是最高位空出来，所以再除以 $2$。

```cpp
for(int i=0;i<x;i++)
{
    res[i]=res[i/2]/2;
    if(i&1)res[i]|=(x/2);
    if(i<res[i])swap(y[i],y[res[i]]);
}
```

那么为什么只有当 $i<res_i$ 的时候才会交换呢？

因为 $res_i$ 翻转之后是 $i$，你要是 $i>res_i$ 的时候再交换一遍，那不换回去了吗？

于是我们就有了以下非递归版 FFT。

```cpp
void FFT(node y[],int x,int type)
{
    for(int i=0;i<x;i++)
    {
        res[i]=res[i/2]/2;
        if(i&1)res[i]|=(x/2);
        if(i<res[i])swap(y[i],y[res[i]]);
    }
    for(int g=2;g<=x;g*=2)//枚举分割的区间长度
    {
        node w={cos(PI*2/g),type*sin(PI*2/g)};
        //这里利用三角函数的cos(-x)=cos(x),sin(-x)=-sin(x)
        for(int i=0;i<x;i+=g)//每次向前跳一个区间
        {
            node o={1,0};
            for(int j=i;j<i+g/2;j++,o=o*w)//用上一层的点值答案推这一层的点值
            {
                node l=y[j],r=y[j+g/2];
                //由于y[j],y[j+g/2]推的刚好是这一层的y[j],y[j+g/2]，所以可以优化空间
                y[j]=l+o*r;
                y[j+g/2]=l-o*r;
            }
        }
    }
    if(type==-1)//处理逆变换
    {
        for(int i=0;i<x;i++)
        {
            y[i].x/=x;
            y[i].y/=x;
        }
   }
}
```

两个大整数相乘可以看成两个系数为 $10^k$ 的多项式相乘。

于是此题思路显而易见。

# 复杂度分析

我们发现，第一层循环花费 $\log_2n$ 的时间。

第二三层循环相当于把整个序列遍历了一遍。

所以总时间复杂度 $O(n\log_2n)$。

空间复杂度由于我们一直在用一个数组求解，所以总空间复杂度 $O(n)$。

# code

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,res[3000005],len;
string u,v;
struct node
{
    double x,y;
    node operator +(const node &g)const{return {g.x+x,g.y+y};}
    node operator -(const node &g)const{return {x-g.x,y-g.y};}
    node operator *(const node &g)const{return {g.x*x-g.y*y,g.x*y+g.y*x};}
};
node a[3000005],b[3000005];
double PI=3.1415926535;
void FFT(node y[],int x,int type)
{
    for(int i=0;i<x;i++)
    {
        res[i]=res[i/2]/2;
        if(i&1)res[i]|=(x/2);
        if(i<res[i])swap(y[i],y[res[i]]);
    }
    for(int g=2;g<=x;g*=2)
    {
        node w={cos(PI*2/g),type*sin(PI*2/g)};
        for(int i=0;i<x;i+=g)
        {
            node o={1,0};
            for(int j=i;j<i+g/2;j++,o=o*w)
            {
                node l=y[j],r=y[j+g/2];
                y[j]=l+o*r;
                y[j+g/2]=l-o*r;
            }
        }
    }
    if(type==-1)
    {
        for(int i=0;i<x;i++)
        {
            y[i].x/=x;
            y[i].y/=x;
        }
   }
} 
int main()
{
    cin>>u>>v;
    n=u.size(),m=v.size();
    for(int i=n-1;i>=0;i--)a[n-1-i].x=u[i]-'0';
    for(int i=m-1;i>=0;i--)b[m-1-i].x=v[i]-'0';
    len=1;
    while(len<n+m)len*=2;
    FFT(a,len,1);
    FFT(b,len,1);
    for(int i=0;i<len;i++)a[i]=a[i]*b[i];
    FFT(a,len,-1);
    for(int i=0;i<len;i++)
    {
        int u=a[i].x+0.5;
        a[i+1].x+=u/10;
    }
    while((int)(a[len].x+0.5)<=0)len--;
    if(len==0)
    {
        cout<<0;
        return 0;
    }
    for(int i=len;i>=0;i--)
    {
        int u=a[i].x+0.5;
        cout<<u%10;
    }
    return 0;
}
```
# 几道例题

都是模板题：

[【模板】高精度乘法 | A*B Problem 升级版](https://www.luogu.com.cn/problem/P1919)。

[【模板】多项式乘法（FFT）](https://www.luogu.com.cn/problem/P3803)。

# 后记

感谢同学 @[_FastFT2013](https://www.luogu.com.cn/user/701478) 的文章赞助：[link](https://www.luogu.me/article/i3tw5t0r)。麻烦关注他谢谢。

---

## 作者：complete_binary_tree (赞：2)

[更好的阅读体验](https://complete-binary-tree-blog.github.io/blog/2025/05/28/%E5%A4%9A%E9%A1%B9%E5%BC%8F%E4%B9%98%E6%B3%95%E4%BC%98%E5%8C%96/)

---

# 多项式乘法优化

如何借助复数和分治，将多项式乘法从 $O(n^2)$ 优化到 $O(n \log n)$？

本文将介绍两种算法：FFT，FNTT。

## FFT

**快速傅里叶变换**（Fast Fourier Transform）是基于**傅里叶变换**（Fourier Transform），并使用**复数**优化的算法，可用于处理多项式乘法。

### 前置知识：复数

**虚数单位**用 $\mathrm i$（**不能**使用 $i$）表示，满足 $\mathrm i^2=-1$。

> **一种错误理解**
>
> $\sqrt {-1}=\mathrm i$ 是不严谨的。

**复数**是一种有两个部分的数，包含实部和虚部，通常表示为 $z=x+y\mathrm i$，其中 $\mathrm i$ 是虚数单位。

**复数的模**定义为 $\sqrt{x^2+y^2}$，通常写作 $|z|$。

**单位根**若复数 $\omega$ 满足 $\omega^n=1$，则称 $\omega$ 是 $n$ 次单位根，可以用 $\omega_n$ 表示。

单位根还可以这样算出：$\omega_n=\mathrm e^{\cdot \frac{2k\pi\mathrm{i}}{n}}$，其中 $k \in [0,n)$ 且 $k \in \mathbb Z$。

当然，单位根还有一个性质：若 $n$ 为偶数，则 $\omega^{\frac n 2}=-1$。

**复数加法**若 $z_1=a_1+b_1\mathrm i$，$z_2=a_2+b_2\mathrm i$，则 $z_1+z_2=(a_1+a_2)+(b_1+b_2)\mathrm i$。

**复数减法**若 $z_1=a_1+b_1\mathrm i$，$z_2=a_2+b_2\mathrm i$，则 $z_1-z_2=(a_1-a_2)+(b_1-b_2)\mathrm i$。

**复数乘法**若 $z_1=a_1+b_1\mathrm i$，$z_2=a_2+b_2\mathrm i$，则 $z_1 \times z_2=(a_1a_2-b_1b_2)+(a_1b_2+b_1a_2)\mathrm i$。

可以证明，复数加减法、复数乘法分别满足交换律、结合律，复数乘法与加减法满足分配律。

### 多项式点值表示法

我们知道，已知一些点对 $(x_i,y_i)$，其中 $\forall i,j \in [1,n],x_i \not= x_j$，那么我们可以**唯一**确定一个 $n-1$ 次多项式。

> **这不是插值吗？**
>
> 还真是。
>
> 因为 $n$ 个点可以确定一个 $n-1$ 次多项式。

假设这两个要乘起来的多项式分别是 $f(x)$、$g(x)$，那么我们可以取一些值 $x_i$，则 $(x_i,f(x_i) \cdot g(x_i))$ 这个点肯定在他们俩乘起来的多项式上。

然而，我们要想办法如何快速实现求值和确定多项式呢？

### 借助单位根

我们取 $\omega=\mathrm{e}^{\frac{2\pi\mathrm{i}}{n}}$，取这个值的目的是为了 $\omega^n=1$，即 $\omega$ 是 $n$ 次单位根。

> **为什么不取其他使 $\omega^n=1$ 的值？**
>
> 也可以，不过这样取可以更方便求单位根。
>  
> 而且有一些单位根可能会存在整数 $k<n$，使得 $\omega_n^k=1$，这样子 $\{\omega_n^0,\omega_n^1,\omega_n^2,\dots,\omega_n^n\}$ 中会**有重复**，就不满足点值表示的要求（点值表示中 $x$ **不可重复**）。

我们很容易求出 $n$ 对点对 $(\omega^i,f(\omega^i))$。

那么怎么知道点对求多项式呢？

设有点对 $\{(\omega^i,y_i)\}$，多项式为 $f(x)=\sum_{i=0}^{n-1}a_ix^i$。

直接求太困难了，~~伟大的逆傅里叶变换告诉我们~~我们可以构造一个序列 $c$ 满足

$$c_i = \sum_{j=0}^{n-1}y_j\omega^{-ij}$$

也就是分别把点 $[\omega^{-0i},\omega^{-i},\omega^{-2i},\dots,\omega^{-(n-1)i}]$ 代入求多项式 $\sum_{i=0}^ny_ix^i$ 的值。

考虑把 $y_j=\sum_{k=0}^{n-1}a_k\omega^{jk}$ 代入式子：

$$\begin{align*}
c_i &= \sum_{j=0}^{n-1}y_j\omega^{-ij}\\
    &= \sum_{j=0}^{n-1}\left(\sum_{k=0}^{n-1}a_k\omega^{jk}\right)\omega^{-ij}\\
    &= \sum_{k=0}^{n-1}\sum_{j=0}^{n-1}a_k\omega^{jk-ij}\\
    &= \sum_{k=0}^{n-1}a_k\sum_{j=0}^{n-1}\omega^{j(k-i)}
\end{align*}$$

我们考虑 $\sum_{k=0}^{n-1}a_k\sum_{j=0}^{n-1}\omega^{j(k-i)}$：

1. 如果 $k=i$

    那么后面的 $\omega^{j(k-i)}$ 项全都变成了 $\omega^{0j}$，也就是 $1$。

    所以 $c_i=a_i\sum_{j=0}^{n-1}1=na_i$。

2. 如果 $k \not= i$

    那么 $\sum_{j=0}^{n-1}\omega^{j(k-i)}$ 相当于一个公比为 $\omega^j$ 的等比数列。

    套求和公式，$\sum_{j=0}^{n-1}\omega^{j(k-i)}=1^{k-i} \times \frac{1-\omega^{n(k-i)}}{1-\omega^{k-i}}$。

    又 $\omega^n=1$，即 $1^{k-i} \times \frac{1-\omega^{n(k-i)}}{1-\omega^{k-i}}=1^{k-i} \times \frac{1-1}{1-\omega^{k-i}}=0$。

    所以 $a_k\sum_{j=0}^{n-1}\omega^{j(k-i)}=0$。

综上，$a_i=\frac {c_i} n$，即 

$$a_i = \frac1n \cdot \sum_{j=0}^{n-1}y_j\omega^{-ij}$$

这个式子和刚刚求多项式的式子差不多（只不过 $\omega^{ij}$ 变成了 $\omega^{-ij}$），所以我们可以利用类似求多项式值的方法求出。

### 分治优化

不过到目前算法复杂度还是只能达到 $O(n^2)$，我们考虑分治优化。

现在我们有了两个式子：

$$y_i=\sum_{j=0}^{n-1}a_j\omega^{ij}$$

$$a_i = \frac1n \cdot \sum_{j=0}^{n-1}y_j\omega^{-ij}$$

然而朴素地计算它们时间复杂度是 $O(n^2)$ 的，无法接受。

所以我们考虑奇偶分治。（先把 $\omega^i$ 替换成 $x$ 不然看的难受）

$$\begin{align*}
f(x)&= (a_0+a_2x^2+a_4x^4+\dots)+(a_1x+a_3x^3+a_5x^5+\dots)\\
    &= (a_0+a_2x^2+a_4x^4+\dots)+x(a_1+a_3x^2+a_5x^4+\dots)
\end{align*}$$

设 $f_1(x)=a_0+a_2x^1+a_4x^2+\dots$，$f_2(x)=a_1+a_3x^1+a_5x^2+\dots$。

那么

$$f(x)=f_1(x^2)+xf_2(x^2)$$

由于进行了平方，所以变成 $f_1(x^2)$ 和 $f_2(x^2)$ 之后只要算一半（单位根性质，$\{\omega_{n}^{2i}(i \in [1,n])\}=\{\omega_{\frac n2}^{i}(i \in [1,\frac n2])\}$，其中 $\omega_n=\mathrm{e}^{\mathrm{i}\frac{2\pi}{n}}$）。

单位根还有另外一个性质：

上式代入 $\omega^i$

$$y_i=f_1(\omega^{2i})+\omega^{i}f_2(\omega^{2i})$$

代入 $\omega^{i+\frac n 2}$

$$\begin{align*}
y_{i+\frac n 2} &= f_1(\omega^{2(i+\frac n 2)})+\omega^{i + \frac n 2}f_2(\omega^{2(i+\frac n 2)})\\
    &= f_1(\omega^{2i})-\omega^{i}f_2(\omega^{2i})
\end{align*}$$

可以发现这两个式子（几乎）完全一样。

所以由于单位根性质，只要算 $y_0,y_1,\dots,y_{\frac n 2-1}$ 就能 $O(1)$ 得出 $y_{\frac n 2},y_{\frac n 2+1},\dots,y_{n-1}$。

所以可以进行分治。

时间复杂度 $T(n)=O(n)+2T(\frac n 2)$，即 $O(n \log n)$。

### 核心代码

```cpp
typedef complex<double> comp;
const double pi=acos(-1.0); // cos(pi)=-1

/// @brief 聚 DFT、IDFT 于一体的 FFT 函数。
/// @param n 需要求的多项式长度。
/// @param a 需要求的多项式数组。结果在此处返回。
/// @param type 1 表示 DFT，-1 表示 IDFT
void FastFastTLE(int n, comp*a, int type){
    if(n==1)return; // 常数项直接返回

    comp*a1=new comp[n>>1],*a2=new comp[n>>1];
    for(int i=0;i<n;++i) // 奇偶分类
        if(i&1)a2[i/2]=a[i];
        else a1[i/2]=a[i]; 
    
    // 递归分治
    FastFastTLE(n>>1, a1, type);
    FastFastTLE(n>>1, a2, type);

    // wmul 就是单位根，w 表示 wmul^i
    comp wmul=comp(cos(2.0*pi/n),sin(2.0*pi/n)*type), //这里也可以使用 exp 函数，效果一样
         w=comp(1.0,0.0);
    for(int i=0;i<(n>>1);++i){
        comp tmp=w*a2[i]; // 复数计算比较慢，提前计算节省时间
        a[i]=a1[i]+tmp,a[i+(n>>1)]=a1[i]-tmp; // 式子
        w*=wmul;
    }

    delete[] a1;
    delete[] a2;
}
```

## FNTT

**快速数论变换**（Fast Number-Theoretic Transform）是一种基于**数论变换**（Number-Theoretic Transform），并利用**原根**进行优化的算法，可以处理带模数的多项式乘法。

在不引起混淆的语境下，FNTT 也可以简称为 NTT。

## 前置知识：原根

在模 $p$ 意义下，**原根** $g$ 是一个满足以下条件的整数：

1. $g^{\varphi(p)} \equiv 1 \pmod p$；

2. $\forall i \in [1,\varphi(p)),g^{i}\not\equiv 1\pmod p$；

3. $g \in [0,p)$。

在 $p$ 为奇质数时，$\varphi (p)=p-1$，此时它具有以下性质：

如果我们设 $n$ 为偶数，$\omega=g^{\frac {p-1}n}$，那么有：

1. $\omega^{n}=g^{p-1}=1$；

2. $\omega^{0},\omega^1,\omega^2,\dots,\omega^{n-1}$ 两两不同（原根第 $2$ 条）；

3. $\omega^{\frac n 2} \equiv -1 \pmod p$。

> **$3$ 的证明**
>
> 由于 $g^{p-1}\equiv 1\pmod p$，即 $g^{2 \cdot \frac{p-1}2}-1 \equiv 0\pmod p$。
>
> 因式分解，$(g^{\frac{p-1}2}+1)(g^{\frac{p-1}2}-1) \equiv 0\pmod p$。
>
> 由于 $g^{\frac{p-1}2} \not \equiv 1$，所以 $g^{\frac{p-1}2} \equiv -1$。
>
> 所以 $\omega^{\frac{n}2}\equiv -1\pmod p$。

根据上面三个性质，我们发现：在模 $p$ 意义下，**原根可以代替 FFT 中的单位根**。

于是我们可以直接套上 FFT，并把单位根替换成原根，然后再加上模数即可。

> **注意**
>
> NTT 对于模数**有要求**。
>
> 对于一个模数 $p$，它可以处理的最长序列是 $2^k$，其中 $k$ 为满足 $2^k \mid p$ 的最大整数。
>
> 如果 $2^k$ 太大了会导致 $\frac{p-1}{2^k}$ 不是整数，就做不了 NTT 了。
>
> 像常见模数 $998344353=7 \times 17 \times 2^{23}$，所以模 $998244353$ 最大可以做 $n=2^{23}$ 的序列。
>
> 对于任意模数 NTT，请见 [任意模数多项式乘法](https://www.luogu.com.cn/problem/P4245)。

### 核心代码

```cpp
typedef long long ll;
ll W[(1<<21)+5],invW[(1<<21)+5]; // （需要提前预处理）这两个数组在下标为 n 的时候分别表示 n 次单位根、n 次单位根的逆元。

/// @brief NTT 函数。
/// @param n 需要求的多项式长度。
/// @param a 需要求的多项式数组。结果在此处返回。
/// @param type 1 表示 DFT，-1 表示 IDFT。
///
/// 基本架构和 FFT 一样，只不过 complex 变成了 long long，还有需要预处理一下单位根（现场求 O(logn) 对常数影响极大）。
void Nearly_Totally_TLE(int n,ll* a,int type){
    if(n==1)return;
    ll*a1=new ll[n>>1],*a2=new ll[n>>1];
    for(int i=0;i<n;++i)if(i&1)a2[i/2]=a[i];else a1[i/2]=a[i];
    Nearly_Totally_TLE(n>>1,a1,type),Nearly_Totally_TLE(n>>1,a2,type);
    ll wmul=(type+1)?W[n]:invW[n],w=1; // 单位根 comp -> ll
    for(int i=0;i<(n>>1);++i)a[i]=(a1[i]+w*a2[i])%mod,a[i+(n>>1)]=(a1[i]-w*a2[i])%mod,w=w*wmul%mod;
    delete[] a1;
    delete[] a2;
}
```

## 例题

### [P3803 【模板】多项式乘法（FFT）](https://www.luogu.com.cn/problem/P3803)| [P1919 【模板】高精度乘法 | A*B Problem 升级版](https://www.luogu.com.cn/problem/P1919)

本质相同的两道模板题。

只需对两个序列分别做一遍 DFT，然后把点值相乘，最后再做一遍 IDFT 即可。使用 FFT、NTT 实现均可。

需要注意的是，最后答案**要除以做 DFT/IDFT 的长度**，而且**做 DFT/IDFT 的长度要一样且是 $2$ 的整数次幂**。还有就是做高精度乘法的时候要记得**把数组反向**。如果 TLE 了可以考虑一些常数优化。

---

## 作者：derderhaoyue (赞：2)

# 高精度乘法（加强版）

## 序言 & 简介

这道题是一道高精度运算模板题，高精度乘法一般用于计算非常大的数的乘法，由于数据很大，需要一种比较高级的算法来解决。

## 解决

首先，我们为了应对这道题巨大的数据，需要一种能快速计算两个高精度数乘法的方式，这就需要 FFT，接下来就是 FFT 的讲解了。

不过，在正式开始讲解 FFT 本身之前需要先了解一下前置知识：

### 多项式的表示法

1. 系数表示法
   这种方法算得上是最常见的多项式表示法，一般的时候我们也用得最多，形如 $f(x)=\sum^{n}_{k=0}{a_kx^k}$。
   以这种方式计算多项式乘法时间复杂度为 $\Theta(n^2)$。

2. 点值表示法
   这种方法类似于初中的给几个点求函数解析式的情景，一个 $n$ 次多项式可以使用 $n+1$ 个点来表示出来，即这个多项式被点 $(x_1,y_1),(x_2,y_2),\cdots,(x_{n+1},y_{n+1})$ 唯一表示。
   但是这样计算复杂度仍然为 $\Theta(n^2)$。

   而 FFT 就是在这一种表示法之上进行的，它能将这种计算的复杂度降低到 $\Theta(n\log(n))$。

### 单位根

在讲单位根之前，我们先讲一下单位圆，单位圆就是以坐标轴为原点，半径为 1 的圆。
而单位根就是把一个圆 $n$ 等分，取这 $n$ 个点所表示的复数，就是这个圆的 $n$ 次单位根。
更加形式化的定义：

> 数学上，$n$ 次单位根是 $n$ 次幂为 $1$ 的复数。它们位于复平面的单位圆上，构成正n边形的顶点，其中一个顶点是 $1$。

—— 引用自百度百科。
根据定义，找单位根的方法就有了：
先将一个圆 $n$ 等分，然后从 $(1,0)$（即 $\omega^1_n$）这个点开始逆时针编号，第 $k$ 个点所对应的复数为 $\omega^k_n$。

注：为了便于实现，下文中的 $n$ 将默认为 $2$

而根据复数的乘法法则可得：$(\omega^m_n)^k =\omega^{mk}_n$ 根据每个复数的幅角，可以计算出这个点的坐标，例如 $\omega^k_n$ 所对应的点为 $(\cos\frac{2k\pi}{n},\sin\frac{2k\pi}{n})$，也是复数 $\cos\frac{2k\pi}{n}+sin\frac{2k\pi}{n}\times i$。

接下来是单位根的性质：

1. $\omega^{2k}_{2n}=\omega^{k}_{n}$

证明：

$$\begin{aligned}\omega_{2n}^{2k} & = \cos\frac{4k\pi}{2n}+\sin\frac{4k\pi}{2n}\times i \\ & = \cos\frac{2k\pi}{n}+\sin\frac{2k\pi}{n}\times i \\ & = \omega_{n}^{k}\end{aligned}$$

2. $\omega^{k+n}_{n}=\omega^{k}_{n}$

证明：

$$\begin{aligned}\omega_{n}^{k + n} & = \cos\frac{2(k + n)\pi}{n} + \sin\frac{2(k + n)\pi}{n} \times i \\ & = \cos\frac{2k\pi}{n} + \sin\frac{2k\pi}{n} \times i \\ & = \omega_{n}^{k}\end{aligned}$$

3. $\omega^{k+\frac{n}{2}}_{n}=-\omega^{k}_{n}$

证明：

$$\begin{aligned}\omega^{k+\frac{n}{2}}_{n} & = \cos\frac{2(k+\frac{n}{2})\pi}{n}+\sin\frac{2(k+\frac{n}{2})\pi}{n}\times i \\ & = \cos(\frac{2k\pi}{n}+\pi)+(\sin\frac{2k\pi}{n}+\pi)\times i \\ & = -\cos\frac{2k\pi}{n}-\sin\frac{2k\pi}{n}\times i \\ & = -\omega^{k}_{n}\end{aligned}$$

### 点值相乘

在快速傅里叶变换（FFT）中，多项式的乘法操作可以通过点值相乘来实现。具体而言，给定两个多项式 $A(x)$ 和 $B(x)$，我们可以通过以下三部进行乘法计算：

1. 计算点值表示法：使用 FFT 将多项式 $A(x)$ 和 $B(x)$ 转换为点值表示法，即计算 $A(\omega^k_n)$ 和 $B(\omega^k_n)$，其中 $\omega_n$ 是单位根，$k=0,1,\cdots,n-1$。

2. 点值相乘：对每个 $k$，计算 $F(\omega^k_n) = A(\omega^k_n) \times B(\omega^k_n)$，得到乘积多项式 $F(x)$ 的点值表示法。

3. 逆变换：使用逆 FFT（IFFT）将点值表示法转换回系数表示法，得到最终的乘积多项式 $F(x)$ 的系数。

## FFT 推导 & 正确性证明

假设一个 $n$ 次多项式：$F(x)=a_0+a_1\times x+a_2\times x^2\cdots a_{n-1}\times x^{n-1}$ 将它的下标按奇偶性分类，并设：

$$F_1 = a_0+a_2\times x+a_4\times x^2\cdots+a_{n-2}\times x^{\frac{n}{2}-1}$$

$$F_2 = a_1+a_3\times x+a_5\times x^2\cdots+a_{n-1}\times x^{\frac{n}{2}-1}$$

则有：

$$F(x)=F_1(x^2)+xF_2(x^2)$$

分别将 $\omega^k_n$ 与 $\omega^{k+\frac{n}{2}}_{n}$ 代入得

$$\begin{aligned}F(\omega^k_n) & = F_1(\omega^{2k}_n)+\omega^k_nF_2(\omega^{2k}_n) \\ & = F_1(\omega^{k}_{\frac{n}{2}})+\omega^k_nF_2(\omega^{k}_{\frac{n}{2}})\end{aligned}$$

和

$$\begin{aligned}F(\omega^{k+\frac{n}{2}}_{n}) & = F_1(\omega^{2k+n}_{n})+\omega^{k+\frac{n}{2}}_{n}F_2(\omega^{2k+n}_{n}) \\ & = F_1(\omega^{2k}_{n})-\omega^k_nF_2(\omega^{2k+n}_{n})\\ & = F_1(\omega^{k}_{\frac{n}{2}})-\omega^{k}_{n}F_2(\omega^{k}_{\frac{n}{2}})\end{aligned}$$

这两个式子长得极为相像，意味着我们只需要求一半便可得知另一半的结果，如果我们将 $F_1$ 与 $F_2$ 也这么递归地计算下去，就可以得到递归版的代码，由于每层递归计算量是 $\Theta(n)$ 并且递归层数为 $\Theta(\log(n))$，所以总复杂度为 $\Theta(n\log(n))$。

但是，这样写常数巨大，十分的慢，这时候就要请出一个天才般的想法了，接下来，请观察分组前后的数组（以 $n=8$ 为例）：

前：$\{0,1,2,3,4,5,6,7\}$

后：$\{0,4,2,6,1,5,3,7\}$

好像没什么规律？
转化成二进制下试试！

$$\{(000)_2,(001)_2,(010)_2,(011)_2,(100)_2,(101)_2,(110)_2,(111)_2\}$$

$$\{(000)_2,(100)_2,(010)_2,(110)_2,(001)_2,(101)_2,(011)_2,(111)_2\}$$

这不就是将分组前的数组每个数给翻转了吗，这样，我们就可以将翻转后的数组计算出来了。

但，为什么可以这样呢？
证明：
设 $F(m,k)$ 表示一个序列中从 $0$ 到 $2^m-1$ 中第 $k$ 个位置被分组后的位置。
现在将 $k$ 按奇偶性分类讨论：

1. 若 $k$ 为奇数，则将其右移一位，并将它的二进制表示下的第 $n-1$ 位修改成 $1$。

2. 若 $k$ 为偶数，则将其右移一位，并将它的二进制表示下的第 $n-1$ 位修改成 $0$。

于是可得：

$$\begin{aligned} F(m,k) & = (k \operatorname{and} 1) 2^{n - 1} + ((k \gg 1) \operatorname{and} 1) 2^{n - 2} + \cdots + ((k \gg n - 1) \operatorname{and} 1)2^{0} \\ & = \sum_{i = 0}^{n - 1}((k \gg i) \operatorname{and} 1)2^{n - i - 1} \end{aligned}$$

即将 $k$ 的二进制表示翻转。

于是就有了迭代版的代码：

```cpp
for(int i=0;i<lim;i++){
  if(i<r[i]){
      swap(F[i],F[r[i]]);
  }
}
for(int mid=1;mid<lim;mid<<=1){
  comp wn(cos(pie/mid),oper*sin(pie/mid));
  for(int R=mid<<1,j=0;j<lim;j+=R){
      comp w(1.0,0.0);
      for(int k=0;k<mid;k++,w=w*wn){
          comp y=F[j+k],z=w*F[j+mid+k];
          F[j+k]=y+z;
          F[j+mid+k]=y-z;
      }
  }
}
```

但这还没完，还有要将点值表示法转回点值表示法的步骤没有完成，这就需要 IFFT（快速傅里叶逆变换）登场了。

使用矩阵来理解 IFFT 是一种比较简单的理解方式，从矩阵的角度看我们刚才的计算，实际上就是在进行如下操作：

$$\begin{bmatrix} F_0 \\ F_1 \\ F_2 \\ \vdots \\ F_{n-1} \end{bmatrix} = \begin{bmatrix} 1 & 1 & 1 & \cdots & 1 \\ 1 & \omega^{1}_{n} & \omega^{2}_{n} & \cdots & \omega^{n-1}_{n} \\ 1 & \omega^{2}_{n} & \omega^{4}_{n} & \cdots & \omega^{2(n-1)}_{n} \\ \vdots & \vdots & \vdots & \ddots & \vdots \\ 1 & \omega^{n-1}_{n} & \omega^{2(n-1)}_{n} & \cdots & \omega^{(n-1)^2}_{n} \end{bmatrix} \begin{bmatrix} a_0 \\ a_1 \\ a_2 \\ \vdots \\ a_{n-1} \end{bmatrix}$$

现在，我们已经完成了求左边式子的值这个任务，而中间的值在多项式的点值表示法中也是一一对应的，接下来只需要在两边左乘中间矩阵的逆矩阵即可。（因为矩阵乘法不满足交换律，所以把一个矩阵乘在另一个矩阵的左边和右边结果不同，乘在左边就是左乘）
这个矩阵有一个非常好的性质就是每一项取倒数再除以变换的长度 $n$ 就是他的逆矩阵。
在代码实现上就是将原来 FFT 的单位根替换为它的倒数，然后计算出结果再除以 $n$ 就好了。

到此为止，对于大数据运算会 TLE 的问题就解决了，接下来要做的就是把 FFT 装载到一个普通的高精乘板子上，就能完
成这道题目了。

## 实现代码

最后，将我的代码一并献给大家，感谢各位神犇的观看！

```cpp
#include<bits/stdc++.h>
using namespace std;
constexpr int M=2097153;
constexpr int N=200;
const double pie=acos(-1.0);
char s1[M],s2[M];
int cnt1,cnt2,l,lim=1;
int ans[M],r[M];
struct comp{// 手打复数，避免被卡。
    double real,img;
    comp(double xx=0,double yy=0){
        real=xx;
        img=yy;
    }
    comp operator + (const comp b)const{ 
        return comp(real+b.real , img+b.img);
    }
    comp operator - (const comp b)const{ 
        return comp(real-b.real , img-b.img);
    }
    comp operator * (const comp b)const{ 
        return comp(real*b.real-img*b.img,real*b.img+img*b.real);
    }
}f[M],g[M];
void init(int k){
    int len=1<<k;
	for(int i=0;i<len;i++)
	r[i]=(r[i>>1]>>1)|((i&1)<<(k-1));
}
void fft(comp *F,int oper){// FFT 的主体，oper 是操作类型，为 1 是 FFT,-1 是 IFFT。
    for(int i=0;i<lim;i++){
        if(i<r[i]){
            swap(F[i],F[r[i]]);
        }
    }
    for(int mid=1;mid<lim;mid<<=1){
        comp wn(cos(pie/mid),oper*sin(pie/mid));
        for(int R=mid<<1,j=0;j<lim;j+=R){
            comp w(1.0,0.0);
            for(int k=0;k<mid;k++,w=w*wn){
                comp y=F[j+k],z=w*F[j+mid+k];
                F[j+k]=y+z;
                F[j+mid+k]=y-z;
            }
        }
    }
}
int main(){
    scanf("%s %s",s1,s2);
    int n1=0,n2=0;
    for(int i=0;s1[i]>='0'&&s1[i]<='9';i++){// 高精度输入。
        n1++;
    }
    for(int i=0;s2[i]>='0'&&s2[i]<='9';i++){
        n2++;
    }
    for(int i=n1-1;i>=0;i--){
        f[cnt1++].real=s1[i]-48;
    }
    for(int i=n2-1;i>=0;i--){
        g[cnt2++].real=s2[i]-48;
    }
    while(lim<=n1+n2){// 走 FFT 标准流程。
        lim<<=1;
        l++;
    }
    for(int i=0;i<=lim;i++){
        r[i]=(r[i>>1]>>1)|(i&1)<<(l-1);
    }
    fft(f,1);
    fft(g,1);
    for(int i=0;i<=lim;i++){
        f[i]=f[i]*g[i];
    }
    fft(f,-1);
    for(int i=0;i<=lim;i++){
        ans[i]+=(int)(f[i].real/lim+0.5);
        if(ans[i]>=10){
            ans[i+1]+=ans[i]/10;
            ans[i]%=10;
            lim+=(i==lim);
        }
    }
    while(!ans[lim]&&lim>=1){
        lim--;
    }
    lim++;
    if(lim==-1){// 输出部分。
        printf("0");
    }
    while(--lim>=0){
        printf("%d",ans[lim]);
    }
    return 0;
}
```

## 参考资料

[oi wiki](https://oi-wiki.org/math/poly/fft/) （部分内容参考与代码参考）。

[_不会dp不改名_大佬的文章](https://ltnotfty.blog.csdn.net/article/details/143757440?spm=1001.2101.3001.6650.3&utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7Ebaidujs_baidulandingword%7ECtr-3-143757440-blog-114287897.235%5Ev43%5Econtrol&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7Ebaidujs_baidulandingword%7ECtr-3-143757440-blog-114287897.235%5Ev43%5Econtrol&utm_relevant_index=5) （位逆序置换证明参考）。

---

## 作者：Chase12345 (赞：1)

# 算法介绍
以下内容摘自[我的文章](https://www.luogu.com.cn/article/9ck0bhaz/)。

FFT 是一种优化多项式乘法的一种算法，通常运用于高精乘、信号处理、图像处理、通信系统、音频处理还有医学上都会用到（其实还有很多运用的场景，这里没有完整列出。）

FFT 是使用分治的方法将卷积的复杂度从 $O(n^2)$ 优化到 $O(n \log n)$。

主要用到的核心思想就是：
> 多项式乘积 $C(x)=A(x) \cdot B(x)$，在点值表示下对应于逐点相乘，即 $C(\omega_n^k)=A(\omega_n^k) \cdot B(\omega_n^k)$。

这样，我们可以考虑分治，每次递归处理，最后合并得到答案。这样就是 FFT 的运算过程。

复杂度就是 $T(n)=2T(\frac{n}{2}) + O(n)=O(n \log n)$。

分治策略，具体而言：对于 $n$ 次多项式 $A(x)$，假设 $n$ 为 $2$ 的幂次（如果不足可以补 $0$），我们可以将其使用分治思想分成两部分：
* 奇数项：$A_0(x)=a_0+a_2x+a_4x^2+\dots$
* 偶数项：$A_1(x)=a_1+a_3x+a_5x^2+\dots$

那么我们可以得到 $A(x)=A_0(x^2)+x \cdot A_1(x^2)$。

在 $n$ 个单位根处求值时，使用单位根的折半定理和消去定理，即可得到我们只需要计算前 $\frac{n}{2}$ 个单位根处的值：$A(\omega_n^k)=A_0(\omega_{\frac{n}{2}}^k)+\omega_n^k \cdot A_1(\omega_{\frac{n}{2}}^k)A(\omega_n^{k+\frac{n}{2}})=A_0(\omega_{\frac{n}{2}}^k)-\omega_n^k \cdot A_1(\omega_{\frac{n}{2}}^k)$。

最终的合并我们称为蝶形运算。

具体的运算过程，举个例子，如 $8$ 点 FFT。
```
Stage 1（分组 = 2）:
x0─────(+)──→ A0  
 │      (-)──→ A1  
x4─────┘ 
 
x2─────(+)──→ B0  
 │      (-)──→ B1  
x6─────┘ 
 
x1─────(+)──→ C0  
 │      (-)──→ C1  
x5─────┘ 
 
x3─────(+)──→ D0  
 │      (-)──→ D1  
x7─────┘ 
 
Stage 2（分组 = 4）:
A0─────(+)───────→ E0  
 │      (-)─W4^0─→ E2  
B0─────┘ 
 
A1─────(+)───────→ E1  
 │      (-)─W4^1─→ E3  
B1─────┘ 
 
C0─────(+)───────→ F0  
 │      (-)─W4^0─→ F2  
D0─────┘ 
 
C1─────(+)───────→ F1  
 │      (-)─W4^1─→ F3  
D1─────┘ 
 
Stage 3（分组 = 8）:
E0─────(+)───────→ X[0]  
 │      (-)─W8^0─→ X[4]  
F0─────┘ 
 
E1─────(+)─W8^1─→ X[1]  
 │      (-)─W8^3─→ X[5]  
F1─────┘ 
 
E2─────(+)─W8^2─→ X[2]  
 │      (-)─W8^6─→ X[6]  
F2─────┘ 
 
E3─────(+)─W8^3─→ X[3]  
 │      (-)─W8^7─→ X[7]  
F3─────┘
```
# IFFT
这是将点值表示转换回系数表示的过程，与 FFT 过程类似，只需将单位根取共轭，并在最后除以 $n$。

举个例子：$8$ 点 IFFT：
```
Stage 1（分组 = 2）:
X0─────(+)──→ A0  
 │      (-)──→ A1  
X4─────┘ 
 
X2─────(+)──→ B0  
 │      (-)──→ B1  
X6─────┘ 
 
X1─────(+)──→ C0  
 │      (-)──→ C1  
X5─────┘ 
 
X3─────(+)──→ D0  
 │      (-)──→ D1  
X7─────┘ 
 
Stage 2（分组 = 4）:
A0─────(+)───────→ E0  
 │      (-)─W4^0─→ E2  
B0─────┘ 
 
A1─────(+)───────→ E1  
 │      (-)─W4^1─→ E3  
B1─────┘ 
 
C0─────(+)───────→ F0  
 │      (-)─W4^0─→ F2  
D0─────┘ 
 
C1─────(+)───────→ F1  
 │      (-)─W4^1─→ F3  
D1─────┘ 
 
Stage 3（分组 = 8）:
E0─────(+)───────→ x0 = (E0 + F0) / 8  
 │      (-)─W8^0─→ x4 = (E0 - F0) * 1 / 8  
F0─────┘ 
 
E1─────(+)─W8^-1─→ x1 = (E1 + F1 * (1+i)/√2) / 8  
 │      (-)─W8^-3─→ x5 = (E1 - F1 * (1+i)/√2) * (-1+i)/√2 / 8  
F1─────┘ 
 
E2─────(+)─W8^-2─→ x2 = (E2 + F2 * i) / 8  
 │      (-)─W8^-6─→ x6 = (E2 - F2 * i) * (-i) / 8  
F2─────┘ 
 
E3─────(+)─W8^-3─→ x3 = (E3 + F3 * (-1+i)/√2) / 8  
 │      (-)─W8^-7─→ x7 = (E3 - F3 * (-1+i)/√2) * (1-i)/√2 / 8  
F3─────┘
```
我们需要证明 IFFT 不用额外多写一份代码，也即证明：
$$
\text{IFFT}(X) = \frac{1}{n} \text{conj}(\text{FFT}(\text{conj}(X)))
$$
由 IDFT 定义（如上），两边取共轭并除以 $n$，可以得到：
$$
\frac{1}{n} \text{conj}(\text{FFT}(\text{conj}(X)))_k = x_k
$$
 欸，是不是 IDFT 就可以表示为：
$$
\text{IFFT}(X) = \frac{1}{N} \text{conj}(\text{FFT}(\text{conj}(X)))
$$
这说明~~我们不用多写一份代码了~~能省略一点代码量。
# 与 FFT 的关系
这道题和 FFT 有何关系呢？我们首先知道，FFT 能优化多项式乘法。这里如何运用呢？欸，是否可以考虑将两个数变为多项式呢？答案是肯定的。注意到对于十进制正整数 $a$，设位数从低位到高位分别为 $a_0\sim a_{n-1}$，根据位值原理，容易得到：
$$
A(x)=a_0 10^0+a_110^1+\dots
$$
这不就是多项式吗？两个数乘法不就变成了多项式乘法吗？也就是可以用 FFT 优化了啊。

如果讲得不够清晰，详见此图的示例：
```text
Stage 1（分组=2）:
A偶[4,2,0,0] → [4,4], [2,2]
A奇[3,1,0,0] → [3,3], [1,1]
 
Stage 2（分组=4）:
[4,2] + [3,1] → [6,2,4,2]
[4,2] + [3,1] → [6,2,4,2]
 
Stage 3（分组=8）:
[6,6] + [4,4] → [12,0, (4+W8·4), (4-W8·4)]
[2,2] + [2,2] → [4,0, (2+W8·2), (2-W8·2)]
```
# 正确性证明
关于 FFT 的证明，见[此文](https://www.luogu.com.cn/article/9ck0bhaz)。高精乘转换成多项式乘法的正确性相对显然。
# 代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
 
const int MAXN = 1 << 21;
const double PI = acos(-1.0);
 
struct Complex {
    double x, y;
    Complex (double _x = 0.0, double _y = 0.0) : x(_x), y(_y) {}
    Complex operator + (const Complex& b) const {
        return Complex(x + b.x, y + b.y);
    }
    Complex operator - (const Complex& b) const {
        return Complex(x - b.x, y - b.y);
    }
    Complex operator * (const Complex& b) const {
        return Complex(x * b.x - y * b.y, x * b.y + y * b.x);
    }
};
 
int rev[MAXN];
 
void init(int bit) {
    for (int i = 0; i < (1 << bit); i++)
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
}
 
void fft(Complex* a, int n, int inv) {
    int bit = 0;
    while ((1 << bit) < n) bit++;
    for (int i = 0; i < n; i++)
        if (i < rev[i])
            swap(a[i], a[rev[i]]);
    for (int mid = 1; mid < n; mid <<= 1) {
        Complex wn(cos(PI / mid), inv * sin(PI / mid));
        for (int i = 0; i < n; i += mid * 2) {
            Complex w(1, 0);
            for (int j = 0; j < mid; j++, w = w * wn) {
                Complex x = a[i + j], y = w * a[i + j + mid];
                a[i + j] = x + y;
                a[i + j + mid] = x - y;
            }
        }
    }
    if (inv == -1)
        for (int i = 0; i < n; i++)
            a[i].x /= n;
}
 
Complex A[MAXN], B[MAXN];
int output[MAXN];
 
int main() {
    string a, b;
    cin >> a >> b;
    int n = a.size(),  m = b.size(); 
    if (a == "0" || b == "0") {
        cout << "0" << endl;
        return 0;
    }
    for (int i = 0; i < n; i++)
        A[n - 1 - i].x = a[i] - '0';
    for (int i = 0; i < m; i++)
        B[m - 1 - i].x = b[i] - '0';
    int len = 1, bit = 0;
    while (len < n + m) {
        len <<= 1;
        bit++;
    }
    init(bit);
    fft(A, len, 1);
    fft(B, len, 1);
    for (int i = 0; i < len; i++)
        A[i] = A[i] * B[i];
    fft(A, len, -1);
    for (int i = 0; i < len; i++)
        output[i] = (int)(A[i].x + 0.5);
    for (int i = 0; i < len; i++)
        if (output[i] >= 10) {
            output[i + 1] += output[i] / 10;
            output[i] %= 10;
        }
    int high = len - 1;
    while (high >= 0 && output[high] == 0)
        high--;
    if (high < 0)
        cout << "0";
    else
        for (int i = high; i >= 0; i--)
            cout << output[i];
    cout << endl;
    return 0;
}
```

---

## 作者：zhou2414 (赞：1)

UPD：更正一个错误。

UPD：又更正一个错误，且增加了对非递归版优化的说明。
# 前置知识
- 复数。
- 至少高一的数学基础。
- 一般的高精度乘法。
# FFT 简介
FFT，即**快速傅里叶变换**。

为方便理解，我先讲 FFT 的作用，然后再解释原理。
## 作用
~~知周所众~~，一个一元 $n$ 次多项式有两种表示方式。第一种是常见的**系数表示法**，如下：
$$
a_0+a_1x+a_2x^2+\cdots+a_nx^n
$$
还有一种是不那么常见的**点值表示法**，如下：
$$
(x_0,y_0),(x_1,y_1),(x_2,y_2),\dots,(x_n,y_n)
$$
第二种表示方法常见的例子有：用平面直角坐标系上两点确定一条直线，或者三点确定一条抛物线。它的本质就是取 $n+1$ 个不同的值带入多项式，得出结果，以此确定一个多项式。

FFT 的作用就是在 $O(n\log n)$ 的时间复杂度内将一个一元 $n$ 次多项式在两种表示法中转换。

那和高精度乘法有什么关系呢？

将一个正整数的每一位分开看作系数，就可以将其转换为一个系数表示法的多项式。朴素的高精度乘法就是将两个用系数表示法表示的多项式相乘，时间复杂度 $O(n^2)$。

那么如果是点值表示法的两个多项式相乘呢？首先要保证 $x_i$ 是对应相等的，然后 $y_i$ 相乘即可，时间复杂度 $O(n)$。是不是快了很多？

然而有个残酷的事情是，如果朴素的将系数表示法转换为点值表示法，即一一带入数字并计算结果，那么时间复杂度依然是 $O(n^2)$，起不到任何优化。

这时，FFT 的作用就体现出来了。它可以优化这一部分复杂度至 $O(n\log n)$，大大加快了效率。与它作用相似的还有 NTT，感兴趣的读者可以自行上网查询资料。
## 原理
FFT 通过将复数**单位根**的整数次幂带入多项式，**分治**快速求解。至于为什么选择它，自然是因为单位根具有一些美妙的性质。
### 单位根
> 数学上，$n$ 次单位根是 $n$ 次幂为1的复数。它们位于复平面的单位圆上，构成正 $n$ 边形的顶点，其中一个顶点是 $1$。

摘自[百度百科](https://baike.baidu.com/item/%E5%8D%95%E4%BD%8D%E6%A0%B9/10927387#:~:text=%E6%95%B0%E5%AD%A6%E6%9C%AF%E8%AF%AD%E6%95%B0%E5%AD%A6%E4%B8%8A%EF%BC%8Cn%E6%AC%A1%E5%8D%95%E4%BD%8D%E6%A0%B9%E6%98%AFn%E6%AC%A1%E5%B9%82%E4%B8%BA1%E7%9A%84%E5%A4%8D%E6%95%B0%E3%80%82%E5%AE%83%E4%BB%AC%E4%BD%8D%E4%BA%8E%E5%A4%8D%E5%B9%B3%E9%9D%A2%E7%9A%84%E5%8D%95%E4%BD%8D%E5%9C%86%E4%B8%8A%EF%BC%8C%E6%9E%84%E6%88%90%E6%AD%A3n%E8%BE%B9%E5%BD%A2%E7%9A%84%E9%A1%B6%E7%82%B9%EF%BC%8C%E5%85%B6%E4%B8%AD%E4%B8%80%E4%B8%AA%E9%A1%B6%E7%82%B9%E6%98%AF1%E3%80%82)。

什么是单位圆呢？

就是圆心为原点，半径为单位长度的圆，如图所示：

![单位圆](https://cdn.luogu.com.cn/upload/image_hosting/uenx30jg.png)

而如果我们将单位圆 $n$ 等分，且其中一个等分点在 $(1,0)$ 处，那么从实轴开始逆时针遇到的第二个点表示的复数即为单位根，设为 $\omega_n$ 。如图为 $n=8$ 时的情况：

![单位根](https://cdn.luogu.com.cn/upload/image_hosting/vjaua6dy.png)

容易发现这些点按逆时针可依次表示为 $\omega_8^0$、$\omega_8^1$、$\omega_8^2$、$\cdots$、$\omega_8^7$，而 $\omega_8^8=\omega_8^0=1$。这符合上文提到的单位根的定义。

还有两个十分重要的发现是当 $n$ 为 $2$ 的整数次幂时，$\omega_n^i=-\omega_n^{i+\frac{n}{2}}$，以及当 $n$ 为偶数时，$\omega_n^{2i}=\omega_{\frac{n}{2}}^i$,至于严格的证明~~我不会~~，可以自行上网查阅。

FFT 要求 $n$ 必须为 $2$ 的正整数次幂。即多项式最简形式的项数必须为 $2$ 的正整数次幂。
# 实现
## 递归版
这时有巨佬就要发问了，这些性质有什么用？

可以举个例子（来自 [oi-wiki](https://oi-wiki.org/math/poly/fft/#%E5%BF%AB%E9%80%9F%E5%82%85%E9%87%8C%E5%8F%B6%E5%8F%98%E6%8D%A2)）。

设一个一元 $7$ 次多项式如下：
$$
f(x)=a_0+a_1x+a_2x^2+a_3x^3+a_4x^4+a_5x^5+a_6x^6+a_7x^7
$$
将其各项按奇偶性分为两组,并在奇数组提出一个 $x$：
$$
f(x)=(a_0+a_2x^2+a_4x^4+a_6x^6)+(a_1x+a_3x^3+a_5x^5+a_7x^7)\\
=(a_0+a_2x^2+a_4x^4+a_6x^6)+x(a_1+a_3x^2+a_5x^4+a_7x^6)\\
=g(x^2)+x\cdot h(x^2)
$$
其中 $g,h$ 的形式与 $f$ 类似，只是项数少了一半。

如果 $x=\omega_8^k$ 呢？

由上文中得到的性质可得：
$$
f(\omega_8^k)=g((\omega_8^k)^2)+\omega_8^k\cdot h((\omega_8^k)^2)\\
=g(\omega_8^{2k})+\omega_8^k\cdot h(\omega_8^{2k})\\
=g(\omega_4^k)+\omega_8^k\cdot h(\omega_4^k)
$$
$$
f(\omega_8^{k+4})=g((-\omega_8^k)^2)-\omega_8^k\cdot h((-\omega_8^k)^2)\\
=g(\omega_8^{2k})-\omega_8^k\cdot h(\omega_8^{2k})\\
=g(\omega_4^k)-\omega_8^k\cdot h(\omega_4^k)
$$
发现可以分治递归下去。
### 递归版代码
由此就得到了递归版 FFT。
```cpp
#define cpd complex<dd>//c++自带复数STL模板
cpd tmp[N];
void FFT(cpd *f, ll n) {//递归版
//f[i]表示f(w_n^i)
	if (n == 1)return; //此时的多项式内不含未知数，无需带入
	for (int i = 0; i < n; i++) {
		if (i & 1)
			tmp[i / 2 + n / 2] = f[i];
		else
			tmp[i / 2] = f[i];
	}
	for (int i = 0; i < n; i++)
		f[i] = tmp[i];
	cpd *g = f,*h = f + n / 2; //节约空间
	FFT(g, n / 2), FFT(h, n / 2);
	cpd wn = {cos(2 * pi / n), sin(2 * pi / n)}; //单位根
	//2*pi/n为弧度制中单位根的辐角大小
	cpd w = {1, 0}; //单位根的k次幂
	for (int k = 0; k < n / 2; k++) {
		cpd u = g[k], v = w * h[k];
		f[k] = u + v;
		f[k + n / 2] = u - v;
		w *= wn;
	}
}
```
## 非递归版
递归版常数巨大，效率过低，所以就有了非递归版。

首先可以发现在递归到最底层之前没有对数据本身进行任何操作，所以可以想到提前把数据放到底层的位置，然后进行合并操作。

一次完整递归如图所示，大括号表示一组的范围：

![递归](https://cdn.luogu.com.cn/upload/image_hosting/19mjhg3s.png)

可以发现递归前后的位置编号为其二进制下各位颠倒后的数。~~证明我不会~~。

于是可以先预处理出各位最后的位置，然后合并求解。

至于如何预处理，设 $rev_i$ 表示下标 $i$ 转换后的位置。当枚举到 $i$ 时，$rev_{\lfloor\frac{i}{2}\rfloor}$ 一定被求过，此时将 $rev_{\lfloor\frac{i}{2}\rfloor}$ 右移一位得到的数即为 $rev_i$ 不考虑首位的结果。然后判断 $i$ 是否为奇数决定首位即可。

原因是 $\lfloor\frac{i}{2}\rfloor$ 就相当于去掉 $i$ 的二进制末位。

其实递归版也可以这样优化，但是实现较为麻烦，而且效率依旧不及非递归版，本文不再赘述。
### 非递归版代码
然后就得到了非递归版 FFT。
```cpp
#define cpd complex<dd>
void init() {
	ll pos = 1ll << (k - 1);
	for (ll i = 1; i < len; i++) {
		rev[i] = rev[i >> 1] >> 1;
		if (i & 1)rev[i] += pos;
	}
}
inline void change(cpd f[]) {
	for (ll i = 0; i < len; i++) {
		if (i >= rev[i])continue;//防止转换两次又到原位
		swap(f[i], f[rev[i]]);
	}
}
inline void fft(cpd f[]) {//非递归版
//f[i]表示f(w_n^i)
	change(f);
	for (ll n = 2; n <= len; n <<= 1) {//枚举块的大小
		cpd wn = {cos(2 * pi / n), sin(2 * pi / n)};
		//2*pi/n为弧度制中单位根的辐角大小
		for (ll j = 0; j < len; j += n) {//遍历每一个块
			cpd w = {1, 0};
			for (ll i = j; i < j + n / 2; i++) {
				cpd g = f[i], h = w * f[i + n / 2];
				f[i] = g + h;
				f[i + n / 2] = g - h;
				w *= wn;
			}
		}
	}
}
```
# IFFT
通过上面的讲解，可能有巨佬已经发现了。我们只讲了如何从系数表示法转换为点值表示法，而没有讲如何从点值表示法转换回系数表示法。而我们最终需要的是系数表示法的结果。

那么 IFFT（**快速傅里叶逆变换**）就派上用场了。

它其实就是将公式中的 $\omega_n^k$ 替换为 $\omega_n^{-k}$，然后做一遍 FFT，再将最终得到的结果除以 $n$ 即可。

也可以理解为顺时针沿着单位圆转圈。

至于为什么这样做是对的呢？

考虑原本的多项式为：
$$
f(x)=\sum_{i=0}^{n-1}a_ix^i
$$
对其做两遍 FFT，第二遍相当于相当于将第一遍的结果视为另外一个多项式的系数，然后再做 FFT。

所以设：
$$
y_i=f(w_n^i)\\
p(x)=\sum_{i=0}^{n-1}y_ix^i
$$
将 $\omega_n^k$ 的倒数 $\omega_n^{-k}$ 带入 $p$ 可得：
$$
p(\omega_n^{-k})=\sum_{i=0}^{n-1}y_i\omega_n^{-ki}\\
=\sum_{i=0}^{n-1}\omega_n^{-ki}\sum_{j=0}^{n-1}a_j(\omega_n^{j})^i\\
=\sum_{j=0}^{n-1}a_j\sum_{i=0}^{n-1}\omega_n^{ij-ik}\\
=\sum_{j=0}^{n-1}a_j\sum_{i=0}^{n-1}(\omega_n^{j-k})^i
$$
设 $s(\omega_n^x)=\sum_{i=0}^{n-1}(\omega_n^x)^i$，当 $x=0(\mod n)$ 显然有 $s(\omega_n^x)=n$。

当 $x\neq 0(\mod n)$ 时，可得：
$$
s(\omega_n^x)=\sum_{i=0}^{n-1}(\omega_n^x)^i\\
\omega_n^xs(\omega_n^x)=\sum_{i=1}^{n}(\omega_n^x)^i
$$
错位相减，可得：
$$
(\omega_n^x-1)s(\omega_n^x)=\omega_n^n-\omega_n^0=0
$$
即：
$$
s(\omega_n^x)=0
$$
所以只有 $j=k$ 的时候，$\sum_{j=0}^{n-1}(\omega_n^{j-k})^i$ 不为 $0$，即 $\sum_{j=0}^{n-1}(\omega_n^{j-k})^i=n$。于是得：
$$
p(\omega_n^{-k})=\sum_{i=0}^{n-1}a_j\sum_{j=0}^{n-1}(\omega_n^{j-k})^i\\
=\sum_{i=0}^{n-1}a_jn
$$
由此可得，只要反着做一遍 FFT，然后将结果除以 $n$ 即可。

可以将这两个操作合二为一，只要将单位根替换为单位根的倒数（即将其纵坐标变为原来的相反数），结束时特判除以 $n$ 即可。（代码见完整代码）
# 完整代码
递归版和非递归版的代码都在这。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define dd double
ll __sta[1000009], __len;
inline void write(ll x, ll bo) {
	if (x < 0)putchar('-'), x = -x;
	do __sta[++__len] = x % 10 + 48, x /= 10;
	while (x);
	while (__len)putchar(__sta[__len--]);
	if (bo == 3)return;
	putchar(bo ? '\n' : ' ');
}
#define cpd complex<dd>
const ll N = 3e6+9;
const dd pi = acos(-1.0);
char a[N], b[N];
cpd x1[N], x2[N];
ll len1, len2, len;
ll ans[N];
ll rev[N];
void init() {
	cin >> a >> b;
	len1 = strlen(a), len2 = strlen(b);
	len = 1;
	ll k = 0;
	while (len < len1 * 2 || len < len2 * 2)len <<= 1, k++;
	ll pos = 1ll << (k - 1);
	for (ll i = 1; i < len; i++) {
		rev[i] = rev[i >> 1] >> 1;
		if (i & 1)rev[i] += pos;
	}
	for (ll i = 0; i < len1; i++)
		x1[len1 - i - 1] = a[i] - '0';
	for (ll i = 0; i < len2; i++)
		x2[len2 - i - 1] = b[i] - '0';
//	for(ll i=0;i<len2;i++)cout<<x2[i];
}
/*————————————华丽的分割线————————————*/
inline void change(cpd f[]) {
	for (ll i = 0; i < len; i++) {
		if (i >= rev[i])continue;//防止转换两次又到原位
		swap(f[i], f[rev[i]]);
	}
}
inline void fft(cpd f[], ll on) {//非递归版
//f[i]表示f(w_n^i)
	change(f);
	for (ll n = 2; n <= len; n <<= 1) {//枚举块的大小
		cpd wn = {cos(2 * pi / n), sin(on * 2 * pi / n)};
		//2*pi/n为弧度制中单位根的辐角大小
//	cout<<wn.real()<<' '<<wn.imag()<<endl;
		for (ll j = 0; j < len; j += n) {//遍历每一个块
			cpd w = {1, 0};
			for (ll i = j; i < j + n / 2; i++) {
				cpd g = f[i], h = w * f[i + n / 2];
				f[i] = g + h;
				f[i + n / 2] = g - h;
				w *= wn;
			}
		}
	}
	if (on == -1) {
		for (ll i = 0; i < len; i++)
			f[i] /= len;
	}
}
/*————————————华丽的分割线————————————*/
cpd tmp[N];
void FFT(cpd *f, ll n, ll on) {//递归版
//f[i]表示f(w_n^i)
	if (n == 1)return; //此时的多项式内不含未知数，无需带入
	for (int i = 0; i < n; i++) {
		if (i & 1)
			tmp[i / 2 + n / 2] = f[i];
		else
			tmp[i / 2] = f[i];
	}
	for (int i = 0; i < n; i++)
		f[i] = tmp[i];
	cpd *g = f,*h = f + n / 2; //节约空间
	FFT(g, n / 2, on), FFT(h, n / 2, on);
	cpd wn = {cos(2 * pi / n), sin(on * 2 * pi / n)}; //单位根
	//2*pi/n为弧度制中单位根的辐角大小
	cpd w = {1, 0}; //单位根的k次幂
	for (int k = 0; k < n / 2; k++) {
		cpd u = g[k], v = w * h[k];
		f[k] = u + v;
		f[k + n / 2] = u - v;
		w *= wn;
	}
}
inline void fix(cpd *f) {
	for (int i = 0; i < len; i++)f[i] /= len;
}
/*————————————华丽的分割线————————————*/
void solve() {
	for (ll i = 0; i < len; i++)
		x1[i] *= x2[i];
}
void finish() {
	for (ll i = 0; i < len; i++) {
		ans[i] += x1[i].real() + 0.5;
		ans[i + 1] += ans[i] / 10;
		ans[i] %= 10;
	}
	bool bo = 0;
	for (ll i = len; i >= 0; i--) {
		if (!bo && ans[i] == 0)continue;
		bo = 1;
		write(ans[i], 3);
	}
	if (!bo)write(0, 3);
}
int main() {
	init();

	FFT(x1, len, 1), FFT(x2, len, 1);//递归版
	//或
	fft(x1, 1), fft(x2, 1);//非递归版

	solve();

	FFT(x1, len, -1);
	fix(x1);//递归版
	//或
	fft(x1, -1);//非递归版

	finish();
	return 0;
}
```
# 参考资料
[oi-wiki](https://oi-wiki.org/math/poly/fft/)。

---

## 作者：XYstarabyss (赞：1)

# 算法介绍

观前提示，前置知识：[复数](https://zh.wikipedia.org/wiki/%E5%A4%8D%E6%95%B0_(%E6%95%B0%E5%AD%A6)) [单位根](https://zh.wikipedia.org/wiki/%E5%8D%95%E4%BD%8D%E6%A0%B9) [奇偶函数](https://zh.wikipedia.org/wiki/%E5%A5%87%E5%87%BD%E6%95%B8%E8%88%87%E5%81%B6%E5%87%BD%E6%95%B8)。

对于这一道题，直接使用暴力 $O(n^2)$ 的做法肯定会炸，所以我们考虑把两个数的乘法转化为两个多项式的乘法。

以 P3803 的样例为例，把 $x$ 的意义看作是 $10$，我们就可以把形如 $12$ 这样的十进制数看作 $1x^1+2x^0$，把形如 $121$ 这样的十进制数看作 $1x^2+2x^1+1x^0$，因此 $12 \times 121$ 就可以看作是 $(1x^1+2x^0)(1x^2+2x^1+1x^0)$，算出来就是 $(1x^3+4x^2+5x^1+2x^0)$，即 $1452$，然后再单独处理一下进位就能算出答案了。

那么直接暴力的多项式乘法的时间复杂度也是 $O(n^2)$，这样岂不是优化了个寂寞？

诶，但是我们发现对于一个 $n-1$ 次多项式，既可以用 $n$ 个系数来确定，也可以用 $n$ 个点来确定。也就是说，我们可以使用两个数组来存一个多项式，一个的意义是 $x$，另一个的意义是 $f(x)$，然后，我们默认 $x$ 确定，就只用一个 $f(x)$ 的数组来存这一个多项式。这一种存储方式被称为点值表示法。

更令人振奋的是，此时两个多项式相乘，最终的结果就是 $f_{1}(x) \times f_{2}(x)$ ，也就意味着我们可以用 $O(n)$ 的时间复杂度跑完一遍乘法！

但也别高兴得太早，题目给的多项式还是用的系数表示法，而直接暴力带入 $n$ 个点值计算的时间复杂度还是 $O(n^2)$（到目前为止还是优化了个寂寞……），此时我们就要请出 **快速傅里叶变换**，它可以将多项式从系数表示法转化为点值表示法，并且时间复杂度只有 $O(n\log n)$。

我们来思考一个问题：对于一个函数，如果它是奇函数或者偶函数，那么我们在带入点值的时候能不能偷点懒？

比如说 $f(x)$ 如果是一个偶函数，那么我们算出来 $f(a) = b$ 的时候，也就可以知道 $f(-a) = b$ 了，这样就可以减少一定的计算量。

奇函数同理，若 $f(a) = b$，则 $f(-a) = -b$。

快速傅里叶变换就是运用了选点的艺术，把上面的特殊偷懒情况推广到了一般。

因为大多数多项式对应的函数都是非奇非偶的，所以我们考虑没有条件，就创造条件，把奇函数或偶函数凑出来呗！把

$f(x) = a_{0}x^0 + a_{1}x^1 + a_{2}x^2 + \dots + a_{n}x^n$

拆成

$f(x) = f_1(x^2) + xf_2(x^2)$

其中

$f_1(x) = a_{1}x^0 + a_{3}x^1 + \dots + a_{n - 1}x^{\frac{n}{2} - 1}$

而

$f_2(x) = a_{0}x^0 + a_{2}x^1 + \dots + a_{n}x^{\frac{n}{2}}$

注意，我们默认多项式的次数 $n$ 是偶数，如果不是偶数，可以为多项式添加一个次数为 $n + 1$ 而系数为 $0$ 的单项式，这样就变成了次数为偶数的多项式。

然后我们就把求 $f(x)$ 的值问题变成了求 $f_1(x)$ 的值和 $f_2(x)$ 的值的问题。

而且，根据上面的推论，这样的做法很有偷懒空间，因为

$f(x) = f_1(x^2) + xf_2(x^2)$

$f(-x) = f_1(x^2) - xf_2(x^2)$

所以我们要求的值变成了一半。

对于剩下需要求的值，我们仍然可以通过上述策略拆分函数。一切顺利的话，我们就可以获得梦寐以求的 $O(n\log n)$ 做法。

但是还是不要高兴得太早。作为十级考纲的内容，这个算法这么可能那么简单？

注意到 $x \in \R$ 时，$0 \le x^2$。所以，等到 $f_1$ 和 $f_2$ 
求值时，所有的 $x$ 都变成了正数，与互为相反数的要求不符，递归不成立，我们的算法寄了。

但是趁着我们的推论还没有凉透，我们发现是在 $x \in \R$ 时 $0 \le x^2$ 那么我们找一个神奇的 $x \in C$ 是不是还有救？

恰好，**单位根满足这样的性质**。

那单位根是什么玩意？

考虑一个方程 $\omega ^ n = 1$。

根据代数基本定理，$n$ 次方程 **有** 且 **仅有** $n$ 个根（在复数范围内），所以 $\omega ^ n = 1$ 也有 $n$ 个根。

此方程的 $n$ 个根，叫做 $n$ 次单位根，记作 $w_n$。它的值为 $e^{\frac{2\pi i}{n}}$，即 $\cos(\frac{2\pi}{n}) + i\sin(\frac{2\pi}{n})$。

以下是 $n = 12$ 时单位根的分布。

![](https://cdn.luogu.com.cn/upload/image_hosting/areb4f46.png)

容易发现，这 $n$ 个解在以原点为圆心，以 1 为半径的一个圆上均匀分布。

可以证明，$\omega ^ n$ 是这个圆的 $n$ 等分点。

$n$ 个单位根分别是欧拉公式求出的 $\omega ^ n$ 的 $m$ 次方，$m \in [0,n]$。

例如 $4$ 次单位根分别是 $\omega _ 4 ^ 1,\omega _ 4 ^ 2,\omega _ 4 ^ 3,\omega _ 4 ^ 4$。同时，$\omega _ 4 ^ 0$ 和 $\omega _ 4 ^ 4$ 都为 $1$。

然后再给出两条引理。

### 引理一：$\omega _ {dn} ^ {dm} = \omega _ n ^ m$。

### 引理二：如果 $n > 0$ 且 $n$ 为偶数，那么 $n$ 个 $n$ 次单位根的平方集合就是 $\frac{n}{2}$ 个 $\frac{n}{2}$ 次单位复数根集合。

引理的证明下面再给。

此时，再把 $f(x)$ 中的 $x$ 换成 $\omega_n^m$，

$f(x) = f_1(x^2) + xf_2(x^2)$

即

$f(\omega_n^m) = f_1((\omega_n^m)^2) + \omega_n^mf_2((\omega_n^m)^2)$

$f(\omega_n^m) = f_1(\omega_n^{2m}) + \omega_n^mf_2(\omega_n^{2m})$

根据引理一

$f(\omega_n^m) = f_1(\omega_{\frac{n}{2}}^{m}) + \omega_n^mf_2(\omega_{\frac{n}{2}}^{m})$

又因为 $\omega _ {n} ^ {m+\frac{n}{2}} = -\omega _ {n} ^ {m}$（结合上面给的示意图理解）

所以第二个式子

$f(-\omega_n^m) = f_1(\omega_{\frac{n}{2}}^{m}) - \omega_n^mf_2(\omega_{\frac{n}{2}}^{m})$

就可以变成

$f(\omega _ {n} ^ {m+\frac{n}{2}}) = f_1(\omega_{\frac{n}{2}}^{m}) - \omega_n^mf_2(\omega_{\frac{n}{2}}^{m})$

很明显两个式子后两者只差了一个单项式系数的符号，所以我们在求出左半部分时，可以 $O(1)$ 求出右半部分。这再次缩减了求值的次数。

这样，我们就可以递归地求解 $f_1$ 和 $f_2$。

不过这次我们没有用上偶函数的思想，而是在拆解的时候做了文章，根据引理二，我们这里的递归同样缩小了一半的范围。

看到这里，你就已经可以开始敲代码了，但是递归版本的虽然好敲但是常数大，这里介绍另一种方法。

可以证明，对于每一个系数，它最后位置位于将原系数的二进制反转，得到新的二进制数字对应的位置。（从 0 开始计数）。

例如，处于第 $6 = (110)_2 $ 位置的系数最终位于 $3=(011)_2$ 位置。

这里放一张图辅助理解。

![](https://cdn.luogu.com.cn/upload/image_hosting/3gwzsv0m.png)

那么，我们可以先将所有系数调整到最终的位置，随后合并。

到这里，快速傅里叶变换终于算是讲完了。但是我们还要讲快速傅里叶逆变换把点值表示法转化回系数表示法。

不过不要慌，我们在快速傅里叶变换时，只需要将代入的单位根取倒数，并将得到的结果都除以 $n$，即是快速傅里叶逆变换。

而单位根的倒数，即是单位根的共轭复数。

# 正确性证明

对于引理一：

$$
\omega_{dn}^{dm}
 = e^{\frac{2\pi idm}{dn}} = e^{\frac{2\pi im}{n}} = (e^{\frac{2\pi i}{n}})^m = \omega_n^m

$$

对于引理二：

$$
(\omega_{n}^{m})^2 = 
\omega_{n}^{2m} = 
\omega_{\frac{n}{2}}^{m}

$$

又有 $\omega _ {n} ^ {m+\frac{n}{2}} = -\omega _ {n} ^ {m}$，

所以 $(\omega _ {n} ^ {m+\frac{n}{2}})^2 = (\omega _ {n} ^ {m})^2$

又根据 $(\omega _ {n} ^ {m+\frac{n}{2}})^2 = (\omega _ {n} ^ {m})^2$，所以相当于集合元素少了一半。

而对于整个算法，由上面那个系数去向图的层数得一只 $\log$，由最低层的运算得一只 $n$，所以最后的时间复杂度为 $O(n\log n)$。但需要注意的是，虽然说是这个时间复杂度，但是这个算法涉嫌到极多的浮点数运算，常数极大，慎用，或者去学一下快速数论变换，那个要快一些。

# 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
#define f(n,m,i) for (register int i(n);i <= m;++ i)
#define fm(n,m,i,l) for (register int i(n);i <= m;l)
#define fc(n,m,i) for (register int i(n);i >= m;-- i)
#define dbug(x) cerr<<(#x)<<':'<<x<<' ';
#define ent cerr<<'\n';
#define max(a,b) (((a)>(b))?(a):(b))
#define min(a,b) (((a)<(b))?(a):(b))
#define C ios::sync_with_stdio(false),cin.tie(0),cout.tie(0),cerr.tie(0);
//火车头
const double PI(acos(-1.0));//顾名思义
struct com{//手搓复数类型
    double x,y;//x为实部，y为虚部
    com(double a = 0.0,double b = 0.0){//复数赋值
        x = a,y = b;
    }
    friend com operator-(com &a,com &b){//复数相减
        return com(a.x - b.x,a.y - b.y);
    }
    friend com operator+(com &a,com &b){//复数相加
        return com(a.x + b.x,a.y + b.y);
    }
    friend com operator*(com &a,com &b){//复数相乘
        return com(a.x * b.x - a.y * b.y,a.x * b.y + a.y * b.x);
    }
};
//本代码的FFT采用迭代版，change函数的用途为先把每个数预先处理到最后的位置上
void change(com *y, int n){
    int j(n >> 1),k;
    f(1,n - 2,i){
        if (i < j){//防止换两次换回去了
            swap(y[i], y[j]);
        }
        k = n >> 1;
        while (j >= k){
            j -= k;
            k >>= 1;
        }
        if (j < k){
            j += k;
        }//找到i位置上的元素最终会到哪
    }
}
void fft(com *y/*传来要做变换的数组*/,int n/*长度*/,int isFFT/*是否是正变换*/){
    change(y,n);//预处理
    int ul(log2(n));
    f(1,ul,i){//合并序列操作次数
        int h(1 << i);//准备合并序列的长度
        com wn(cos(2 * PI / h),sin(isFFT * 2 * PI / h));//准备好对应的单位根，如果是IFFT则准备对应的共轭复数
        fm(0,n - 1,j,j += h){//挪到对应的位置，准备合并
            com w(1,0);//就是1
            f(j,j + (h >> 1) - 1,k){//扫描数组的左半部分
                com u(y[k]),t(w * y[k + (h >> 1)]);
                y[k] = u + t;
                y[k + (h >> 1)] = u - t;//代码精髓部分
                w = w * wn;//算出k次的单位根
            }
        }
    }
    if (isFFT == -1){//如果是IFFT
        f(0,n - 1,i){
            y[i].x /= n;
        }//逆变换还需要都除以n
    }
}
com x1[4000005],x2[4000005],res[4000005];//分别存第一个数、第二个数、二数相乘
char num1[4000005],num2[4000005];//用于输进来两个数
int ans[4000005]/*用于把结果转化回整型*/,n(1);
void work(com *x,int &len,char *num){
    f(0,len - 1,i){
        x[i] = com(num[len - 1 - i] - '0', 0);
    }//低位存相应的数字
    f(len,n - 1,i){
        x[i] = com(0, 0);
    }//高位补零
    fft(x,n,1);//系数表示法->点值表示法
}
int main(){ C
    cin >> num1 >> num2;//输入两个数字，因为太大所以采用字符数组的形式输入
    int len1(strlen(num1)),len2(strlen(num2));//算出两个数字的位数
    while (n < (len1 << 1) || n < (len2 << 1)){    n <<= 1;}
    //算出最小的比两个数字位数都要大的2^n
    work(x1,len1,num1),work(x2,len2,num2);//把数字转化存在复数数组内并且做FFT
    f(0,n - 1,i){
        res[i] = x1[i] * x2[i];
    }//点值表示法O(n)做乘法
    fft(res,n,-1);//做IFFT
    f(0,n - 1,i){
        ans[i] = int(res[i].x + 0.5);
    }//从复数类型转化为整型
    f(0,n - 1,i){
        ans[i + 1] += ans[i] / 10;
        ans[i] %= 10;
    }//处理进位
    n = len1 + len2 - 1;//两数进行乘法的最高可能位数
    while (!ans[n] && n > 0){    -- n;}//去除前导零
    fc(n,0,i){
        cout << ans[i];
    }//然后输出答案
    cout << '\n';
    return 0;//结束
}
/*
g++ fft.cpp -o code
./code

83517934
327830610

*/
```

---

