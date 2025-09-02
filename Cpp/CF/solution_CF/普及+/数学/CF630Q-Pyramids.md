# Pyramids

## 题目描述

IT City administration has no rest because of the fame of the Pyramids in Egypt. There is a project of construction of pyramid complex near the city in the place called Emerald Walley. The distinction of the complex is that its pyramids will be not only quadrangular as in Egypt but also triangular and pentagonal. Of course the amount of the city budget funds for the construction depends on the pyramids' volume. Your task is to calculate the volume of the pilot project consisting of three pyramids — one triangular, one quadrangular and one pentagonal.

The first pyramid has equilateral triangle as its base, and all 6 edges of the pyramid have equal length. The second pyramid has a square as its base and all 8 edges of the pyramid have equal length. The third pyramid has a regular pentagon as its base and all 10 edges of the pyramid have equal length.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF630Q/112717337cf1125078951016c57ed1b9db5b5a6b.png)

## 样例 #1

### 输入

```
2 5 3
```

### 输出

```
38.546168065709```

# 题解

## 作者：封禁用户 (赞：2)

楼上大佬给出了本题中正n棱锥体积的计算公式 ：
$$\dfrac{\operatorname{l^3_n}\operatorname{n}}{12\tan\dfrac{\operatorname{\pi}}{n}}\sqrt{1-\dfrac{1}{4\sin^2\dfrac{\operatorname{\pi}}{n}}}$$
这里我简单证明一下。

对于所有的正棱锥 ，都满足 $\operatorname{V}=\dfrac{1}{3}\operatorname{Sh}$，其中 S 是底面积 ，h 是顶点到底面的距离 , 即高 。

正 n 棱锥的底面是一个正 n 边形 , 边长为 $\operatorname{l}_n$ 。 过正 n 边形的几何中心将其平分为 n 个三角形 ， 易知等腰三角形的顶角为 $\dfrac{2\pi}{n}$ ， 底边为 $\operatorname{l}_n$ ， 计算可得 ：
$$\operatorname{S}=\dfrac{\operatorname{l}^2_n}{4\tan\dfrac{\pi}{n}}$$
对于棱锥的高 ， 考虑构造如下三角形求解 ：

![](https://cdn.luogu.com.cn/upload/image_hosting/i5ba6t9f.png)

A 为底面某一顶点 , H 为棱锥的顶点 ， OH 为棱锥的高 。
由前者等腰三角形可以推出腰长 $\operatorname{OA}=\dfrac{\operatorname{l}_n}{\sin\dfrac{\pi}{\operatorname{n}}}$ ， 依题意可知 $\operatorname{AH}=\operatorname{l}_n$ 。由勾股定理得 ：
$$\operatorname{OH}=\sqrt{\operatorname{AH}^2-\operatorname{OA}^2}$$
$$=\sqrt{\left(\operatorname{l}_n\right)^2-\left(\dfrac{\operatorname{l}_n}{\sin\dfrac{\pi}{\operatorname{n}}}\right)^2}$$
$$=\operatorname{l}_n\sqrt{1-\dfrac{1}{4\sin^2\dfrac{\pi}{n}}}$$

则 $\operatorname{V}=\dfrac{1}{3}\operatorname{S}\cdot\operatorname{OH}=\dfrac{\operatorname{l^3_n}\operatorname{n}}{12\tan\dfrac{\operatorname{\pi}}{n}}\sqrt{1-\dfrac{1}{4\sin^2\dfrac{\operatorname{\pi}}{n}}}$

---

## 作者：lgx57 (赞：1)

# CF630Q Pyramids 题解
这是本人的第 4 篇题解，如有问题欢迎大家指出。
## 1.题意
给出一个正三棱锥、一个正四棱锥和一个正五棱锥的棱长，让你求出它们的体积之和。
## 2.分析
经过 bdfs，我们可以得到上述几个立体图形的体积：
$$S_{ \text{正三棱锥} }=\frac{\sqrt 2}{12}l_{3}^{3}$$  
$$S_{ \text{正四棱锥} }=\frac{\sqrt 2}{6}l_{4}^{3}$$

$$S_{ \text{正五棱锥} }=\frac{5+\sqrt 5}{24}l_{5}^{3}$$

只需要照着公式打代码就可以了。
## 3.参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
void fio(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
}
double ans[3];
signed main(){
	int l3,l4,l5;
	cin>>l3>>l4>>l5;
	ans[0]=sqrt(2)/12.0*pow(l3,3);
	ans[1]=sqrt(2)/6.0*pow(l4,3);
	ans[2]=(5.0+sqrt(5))/24.0*pow(l5,3);
	double sum=0.0;
	for (int i=0;i<3;i++){
		sum+=ans[i];
	}
	printf("%.12f",sum);
	return 0;
}

```

---

## 作者：Insouciant21 (赞：1)

计算正棱锥体的体积

计算棱锥体积有公式 $V=\dfrac{1}{3}Sh$

但是这里只给出了棱长，应该如何计算高呢

首先由底面的正三角形求出边心距 $a=\dfrac{\sqrt{3}}{6}l_1$ （边心距公式 $a=\dfrac{t}{2\tan(\pi/n)}$ )

然后通过勾股定理求出顶点到底面边中点的距离 $d=\sqrt{l_1^2-\left(\dfrac{l_1}{2}\right)^2}=\dfrac{2\sqrt{3}l_1}{2}$

则高 $h=\sqrt{d^2-a^2}=\sqrt{\dfrac{12\ l_1^2}{4}-\dfrac{3l_1^2}{36}}=\dfrac{\sqrt{6}}{3}l_1$

底面积为 $S=\dfrac{\sqrt{3}}{4}l_1^2$

可得
$$V_1=\dfrac{1}{3}Sh=\dfrac{\sqrt{3}}{12}l_1^2\times\dfrac{\sqrt{6}}{3}l_1=\dfrac{1}{12}\sqrt{2}\ l_1^3$$

剩下两个同理，易得

$V_2=\dfrac{1}{6}\sqrt{2}\ l_2^3$

$V_3=\dfrac{5+\sqrt{5}}{24}\ l_3^3
$

代码直接套式子即可

AC代码
```
#include <bits/stdc++.h>

using namespace std;

int main() {
    double l1, l2, l3;
    scanf("%lf %lf %lf", &l1, &l2, &l3);
    printf("%.9lf", 1 / 12.0 * sqrt(2) * l1 * l1 * l1 + 1 / 6.0 * sqrt(2) * l2 * l2 * l2 + 1 / 24.0 * (5.0 + sqrt(5)) * l3 * l3 * l3);
    return 0;
}
```


---

## 作者：__main__ (赞：1)

对于一个正$n$棱锥，其体积公式为$\frac{l_{n}^{3} n}{12 \tan \frac{\pi}{n}} \sqrt{1 - \frac{1}{4 \sin^{2} \frac{\pi}{n}}}$，模拟即可。

注意，这里的$\pi$取值要尽量精确，我第一次取了$3.1415926$然后就WA了。

```cpp
#include <bits/stdc++.h>
using namespace std;
const double PI = 3.1415926535898;
double f(double l, double n)
{
    return l * l * l * n / (12 * tan(PI / n)) * sqrt(1 - 1 / (4 * sin(PI / n) * sin(PI / n)));
}
int main()
{
    int l3, l4, l5;
    scanf("%d%d%d", &l3, &l4, &l5);
    printf("%.9f\n", f(l3, 3) + f(l4, 4) + f(l5, 5));
    return 0;
}
```

---

