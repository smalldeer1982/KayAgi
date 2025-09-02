# Mushroom Scientists

## 题目描述

As you very well know, the whole Universe traditionally uses three-dimensional Cartesian system of coordinates. In this system each point corresponds to three real coordinates $ (x,y,z) $ . In this coordinate system, the distance between the center of the Universe and the point is calculated by the following formula: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF185B/19a510fc1d19a415f46c3e3ff454cf87815504ab.png). Mushroom scientists that work for the Great Mushroom King think that the Universe isn't exactly right and the distance from the center of the Universe to a point equals $ x^{a}·y^{b}·z^{c} $ .

To test the metric of mushroom scientists, the usual scientists offered them a task: find such $ x,y,z $ $ (0<=x,y,z; x+y+z<=S) $ , that the distance between the center of the Universe and the point $ (x,y,z) $ is maximum possible in the metric of mushroom scientists. The mushroom scientists aren't good at maths, so they commissioned you to do the task.

Note that in this problem, it is considered that $ 0^{0}=1 $ .

## 样例 #1

### 输入

```
3
1 1 1
```

### 输出

```
1.0 1.0 1.0
```

## 样例 #2

### 输入

```
3
2 0 0
```

### 输出

```
3.0 0.0 0.0
```

# 题解

## 作者：renrua52 (赞：4)

### 前言
是的, 我来之前此题0提交0通过；  
我几乎放弃了, 准备去问[chenxia25](https://www.luogu.com.cn/user/138400)巨佬；  
可是时间太晚了, 巨佬可能睡觉了；  
于是我只好默默做题。。。

------------

### 问题
问题就是使这玩意最大  
![](https://i.loli.net/2020/03/10/CSF5qcMAgmjXpsl.png)  
最大值！ 求导！  
哦，三元啊，我再想想。。。

------------

### 思考
最大值的问题自然想到运用不等式：  
学过哪些不等式呢，什么柯西不等式啊，排序不等式啊，  
什么 **均值不等式** 啊

------------

### 均值不等式
我们只需要知道它的一部分  
![](https://i.loli.net/2020/03/10/m1dTexZhvuW4GXB.png)  
玄学？义为几何平均数不大于算术平均数，即  
![](https://i.loli.net/2020/03/10/S2iKXx8hYMPW3OT.png)  
亦即  
![](https://i.loli.net/2020/03/10/jxC3lKuWTOGbR6Y.png)  
如果你知道这个不等式，不妨先再思考一会；  
如果你不知道这个不等式，最好还是看完。  
[均值不等式的证明](https://baike.baidu.com/item/%E5%9D%87%E5%80%BC%E4%B8%8D%E7%AD%89%E5%BC%8F/8046796?fr=aladdin)

------------
### 推导
对原式变形得  
![](https://i.loli.net/2020/03/10/nbzN3fHKk1RCmBG.png)  
运用均值不等式得  
![](https://i.loli.net/2020/03/10/bLgdsqO7HyC48iV.png)  
当且仅当 **x/a=y/b=z/c** 时等号取得  
结合 x+y+z=S 即得以x, y, z为主元的方程组，解得  
![](https://i.loli.net/2020/03/10/64slTfu5hSLKjMY.png)  
直接输出即可。注意a+b+c=0的特殊情况，因为 0^0=1 > 非零实数^0，故将S全部分配给a, b, c之一取得最大。

------------
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

double s;
double a, b, c;

int main(){
	scanf("%lf", &s);
	scanf("%lf%lf%lf", &a, &b, &c);
	if(a + b + c == 0)
		return printf("%.08lf 0 0\n", s), 0;
	printf("%.12lf %.12lf %.12lf\n", s * a / (a + b + c), s * b / (a + b + c), s * c / (a + b + c));

	return 0;
}
```

------------
### 后记
事实上[chenxia25](https://www.luogu.com.cn/user/138400)巨佬睡得比我还晚

---

## 作者：BotDand (赞：0)

2021.3.11 将图片改为$\LaTeX$，若$\LaTeX$炸了，请在博客中观看。

# $\text{Problems}$
给出$a,b,c$求使$x^ay^bz^c$最大时$x,y,z$的值。
# $\text{Answer}$
前置知识：[均值不等式](https://baike.baidu.com/item/%E5%9D%87%E5%80%BC%E4%B8%8D%E7%AD%89%E5%BC%8F/8046796?fr=aladdin)

先将原式变形得：

$$
x^{a}y^{b}z^{c}\\
=a^{a}b^{b}c^{c}\cdot x^{a}y^{b}z^{c} \div a^{a}b^{b}c^{c}\\
=a^{a}b^{b}c^{c}\cdot \left( \frac{x}{a} \right)^{a} \left( \frac{y}{b} \right)^{b} \left( \frac{z}{c} \right)^{c}\\
\because \frac{a_{1}a_{2}\dots a_{n}}{n}\ge \sqrt[n]{a_{1}a_{2}\dots a_{n}}\\
\therefore \left ( \frac{a_{1}a_{2}\dots a_{n}}{n} \right)^{n}\ge a_{1}a_{2}\dots a_{n}\\
\therefore a^{a}b^{b}c^{c}\left ( \frac{a\cdot\frac{x}{a}b\cdot\frac{y}{b}c\cdot\frac{z}{c}}{abc} \right )^{abc}\ge a^{a}b^{b}c^{c}\cdot \left ( \frac{x}{a}\right )^{a} \left ( \frac{y}{b}\right )^{b} \left ( \frac{z}{c}\right )^{c}\\
\therefore a^{a}b^{b}c^{c}\left ( \frac{S}{a+b+c} \right )^{a+b+c}\ge a^{a}b^{b}c^{c}\left ( \frac{x}{a}\right )^{a} \left ( \frac{y}{b}\right )^{b} \left ( \frac{z}{c}\right )^{c}\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\left ( \frac{x}{a}=\frac{y}{b}=\frac{z}{c} \right )
$$

换主元得：

$$
\left\{\begin{matrix}
x=\frac{S\cdot a}{a+b+c} \\
y=\frac{S\cdot b}{a+b+c} \\
z=\frac{S\cdot c}{a+b+c}
\end{matrix}\right.
$$

特判$\text{a+b+c=0}$即可。
# $\text{Code}$
```cpp
#include<bits/stdc++.h>
using namespace std;
double s,a,b,c,sum,x,y,z;
int main()
{
    cin>>s;
    cin>>a>>b>>c;
    if(a+b+c==0) {cout<<"0.0 0.0 0.0";return 0;}
    sum=a+b+c;
    x=s*a/sum;
    y=s*b/sum;
    z=s*c/sum;
    cout<<fixed<<setprecision(12)<<x<<" "<<y<<" "<<z;
    return 0;
}
```

---

