# Cutting Carrot

## 题目描述

----------------
有一根高为$h$，底为$1$的胡萝卜（姑且可以认为它就是一个三角形），欲将其水平切成$n$段（水平即每一刀都平行于底边），使每一段面积相等。

## 样例 #1

### 输入

```
3 2
```

### 输出

```
1.154700538379 1.632993161855
```

## 样例 #2

### 输入

```
2 100000
```

### 输出

```
70710.678118654752
```

# 题解

## 作者：江户川·萝卜 (赞：6)

## [CF794B Cutting Carrot](https://www.luogu.com.cn/problem/CF794B)题解
[博客食用更佳](https://www.luogu.com.cn/blog/258085/solution-cf794b)

~~我 切 我 自 己~~

题意：有一根高为 $h$ ，底为 $1$ 的三角形，欲将其水平切成 $n$ 段（水平即每一刀都平行于底边），使每一段面积相等。

先算总面积：
$$S_\text{总}=\dfrac{1}{2}ah=\dfrac{h}{2}$$

对于第 $i$ 刀其实可以看做切出一个面积为 $S_{\text{总}}\times\dfrac{i}{n}=\dfrac{hi}{2n}$ 的三角形。

设 $h_i(1\le i\le n)$ 为第 $i$ 刀距三角形顶端的距离（即第 $i$ 刀切出三角形的高），$a_i$ 为第 $i$ 刀的长度（即第 $i$ 刀切出三角形的底），且 $h_n=h,a_n=1$

显然有：
$$\dfrac{h_1}{a_1}=\dfrac{h_2}{a_2}=\cdots=\dfrac{h_n}{a_n}=\dfrac{h}{1}=h$$
也即：
$$\dfrac{h_i}{a_i}=h$$
可得：
$$a_i=\dfrac{h_i}{h}$$
$$\because S_\text{三角形}=\dfrac{1}{2}ah, S_i=\dfrac{hi}{2n}$$
$$\therefore \dfrac{hi}{2n}=\dfrac{1}{2}\times h_i\times\dfrac{h_i}{h}$$
化简得：
$$\dfrac{ih^2}{n}=h_i^2$$
$$h_i=\sqrt{\dfrac{ih^2}{n}}$$

代入就行了。
### Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n,h;
    cin>>n>>h;
    for(int i=1;i<n;i++) cout<<fixed<<setprecision(12)<<sqrt((1ll*i*h*h*1.0)/n)<<" ";
    return 0;
}
```

---

## 作者：xxxr_2024 (赞：2)

# CF794B Cutting Carrot 题解
## 分析
水题，建议降橙。

题目其实提示的很明显了。它让你求 $h$ 减每一刀的高度，这不就是刀痕之上所有段合起来的三角形的高嘛。整个三角形的面积为 $\dfrac{h}{2}$，每一段的面积就为 $\dfrac{h}{2n}$，第 $k$ 刀上面的三角形的面积就是 $\dfrac{kh}{2n}$。考虑**相似三角形**。明显每一刀上面的三角形与整个三角形是相似的，两个相似三角形的底之比等于高之比。设第 $k$ 刀上面的三角形的高为 $k$，可以列出式子 $\dfrac{kh}{2n}:\dfrac{h}{2}=x^2:h^2$，解出来 $x=\sqrt{\dfrac{kh^2}{2}}$。代码暴力枚举 $k$ 即可。

注意，枚举 $k$ 时只用枚举 $n-1$ 次即可，因为 $n$ 段只用切 $n-1$ 刀。还用误差要求不超过 $0.000001$，取小数点后位数大于6即可。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
namespace Raiden
{
    signed work()
    {
        int n,h;
        cin>>n>>h;
        for(int i=1;i<n;i++)
        {
            cout<<fixed<<setprecision(8)<<sqrt(1.0*i*h*h/n)<<endl;
        }
        return 0;
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return Raiden::work();
}
```

---

## 作者：No21 (赞：2)

## 题目分析

水题，很简单，没什么算法需求，直接推式子。~~式子也很简单。~~


------------
## 解题思路

设当前切的是第 $i$ 刀，切在高度为 $x$ 处。

根据小学数学知识可以得到，每一小块的面积为 $\dfrac{n(n - 1)}{2}$，根据初中数学知识可以得到切第 $i$ 刀后，得到一个小三角形，高为 $x$，底为 $\dfrac{x}{2h}$，因此不难得到方程

$$\dfrac{x}{2h}\times x=\dfrac{h}{2n}\times i$$

解得

$$x=\sqrt{\dfrac{h^2i}{n}}=h\times \sqrt{\dfrac{i}{n}}$$

注意精度要求为 $10^{-6}$，因此样例只要小数点后前 $6$ 位相同，第 $7$ 位相差 $1$ 或 $0$ 即可。~~蒟蒻没认真看题，觉得样例没过疑惑了很久。~~

```
#include<bits/stdc++.h>
using namespace std;
namespace TO
{
    int n,h;
    int mian()
    {
        cin>>n>>h;
        for(int i=1;i<n;i++)
            cout<<fixed<<setprecision(7)<<1.0*sqrt(1ll*1.0*h*h*i/n)<<' ';
        return 0;
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    return TO::mian();
}
```

---

## 作者：nytyq (赞：1)

## Part 1.分析

很明显，这道题有平行并且是面积相等，考虑用相似三角形解决。

易知 $S=\displaystyle \frac{h}{2}$，可得每一块的面积为 $\displaystyle \frac{h}{2n}$。

由于每一块的面积需要相等，则可以知道在我们切第 $i$ 刀时，上面的总面积为 $\displaystyle \frac{ih}{2n}$。

这里我们能看出，在切第 $i$ 刀的时候，第 $i$ 刀以上的一个小三角形和整个大三角形相似。令第 
$i$ 刀到三角形顶端的距离为 $x$，所以有如下式子：
$$
 \displaystyle \frac{ih}{2n}: \displaystyle \frac{h}{2}=x^2: h^2
$$

化简可得:

$$
x=\sqrt{\displaystyle\frac{ih^2}{n}}
$$

所以枚举 $i$ 的值算出 $x$ 即可。

## Part2.ACcode

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,h;
int main(){
    cin>>n>>h;
    for(int i=1;i<n;i++){
        printf("%0.12lf ",(double)sqrt(1.0*i*h*h/n));
    }
    return 0;
}
```

---

## 作者：shenbairui (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/solution/CF794B)

### 题目大意
给定一个底为 $ 1 $，高为 $ h $ 的等腰三角形。用平行于三角形的底的 $ (n−1) $ 条直线将三角形切成 $ n $ 段，要求这 $ n $ 段面积相等。求三角形顶点分别到这 $ (n−1) $ 条直线的距离。

### 题目分析

因为是三角形，前 ii 份组成的三角形所占面积为 $ \frac{i}{n} $，即 $ \frac{S_i}{S_n}=\frac{i}{n} $。

然后就可以利用小学就会的[相似三角形](https://baike.baidu.com/item/%E7%9B%B8%E4%BC%BC%E4%B8%89%E8%A7%92%E5%BD%A2/159057?fr=aladdin)得到 $ \frac{S_i}{S_n}=\frac{(X_i) ^ 2}{n ^ 2} $。

### 代码如下


```cpp
#include <bits/stdc++.h>
using namespace std;
double n, h;
int main() {
	cin >> n >> h;
	for (int i = 1; i < n; i++) {
		cout << fixed << setprecision(7) << sqrt(h * h * i / n) <<" ";
	}
	cout << endl;
	return 0;
}
```
下次见！拜拜！

---

## 作者：BLuemoon_ (赞：1)

[link](https://www.luogu.com.cn/problem/CF794B)

## 题意

给定一个底为 $1$，高为 $h$ 的等腰三角形。用平行于三角形的底的 $(n-1)$ 条直线将三角形切成 $n$ 段，要求这 $n$ 段面积相等。求三角形顶点分别到这 $(n-1)$ 条直线的距离。

## 思路

看图（这张图不保证面积相等）：

![](https://cdn.luogu.com.cn/upload/image_hosting/9xdgllt8.png)

根据题目条件，我们知道 $S_{\triangle ABC}=\frac{1}{2}h$，而每一段的面积就是 $\frac{S_{\triangle ABC}}{n}=\frac{h}{2n}$，第 $i(1 \le i < n)$ 刀以上的面积就是 $\frac{ih}{2n}$。

设第 $i$ 刀以上的三角形底为 $c_i$，高为 $h_i$。

易得：$\triangle ADE \sim \triangle AFG \sim \triangle AHI \sim \triangle ABC$，则 $\frac{h_1}{c_1}=\frac{h_2}{c_2}=\dots=\frac{h_i}{c_i}=\dots=\frac{h_n}{c_n}=h$。

根据三角形面积公式，可以得到 $\frac{1}{2}c_ih_i=\frac{ih}{2n}$，而 $\frac{h_i}{c_i}=h \Rightarrow c_i=\frac{h_i}{h}$。

则：

$$\frac{1}{2} \times \frac{h_i}{h} \times h_i=\frac{ih}{2n}$$

整理左式得：

$$\frac{h_i^2}{2h}=\frac{ih}{2n}$$

两边同时乘上 $2h$，得：

$$h_i^2=\frac{ih^2}{n}$$

两边同时开方，得：

$$h_i=\sqrt{\frac{ih^2}{n}}$$

然后遍历代入输出结果即可。

## 代码

```cpp
// BLuemoon_
#include <bits/stdc++.h>

using namespace std;

double n, h;

int main() {
  cin >> n >> h;
  for (int i = 1; i < n; i++) {
    cout << fixed << setprecision(7) << sqrt(h * h * i / n) << ' ';
  }
  cout << '\n';
  return 0;
}
```

---

## 作者：InfSauf (赞：1)

根据题目，需要我们把一个三角形的萝卜切成 $n$ 个面积相同的部分，求这个萝卜的高减去每一刀切的高度，也就是说求每一刀上方切出的小三角形的高。

每一刀与三角形萝卜的底平行，也就是说每个切出来的小三角形都与原来的三角形相似。

我们设每个小三角形的高为 $h_i$，底为 $a_i$ 根据初中相似的知识可知，每个三角形的高与底成比例，也就是说 $\frac{h_i}{a_i}$ 是一个定值，所以我们可以得出：
$$\frac{h_i}{a_i}=h$$

如果这时把这个柿子代入面积，我们会发现不好求，于是我们将 $a_i$ 换出来得到：
$$\frac{h_i}{h}=a_i$$

设每个小三角形的面积为 $S_i$，则有 $S_i=\frac{ih}{2n}$，因为三角形的面积为：$S=\frac{ah}{2}$，所以我们将上式代入公式可得：
$$S=\frac{h_i^2}{2h}=\frac{ih}{2n}$$

$$\therefore h_i^2=\frac{h^2i}{n}$$

$$\therefore h_i=\sqrt{\frac{h^2i}{n}}$$

根据样例，我们保留12位小数。
```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	int h, n;
	cin >> n >> h;
	for(int i = 1; i < n; i++){
		printf("%.12lf ", sqrt(1.0 * i * h * h / n));
	}
}
```


---

## 作者：HUANGRUI11 (赞：0)

这不是数论水题？会相似三角形的不一眼秒。

直接开推公式。

首先算出每部分的面积：$\frac{hi}{2n}$，$i$ 表示是第几部分。

然后根据相似三角形的相似比的平方即为两个相似三角形的面积比，得出相似比：$ \sqrt{ \frac{2hi}{2nh}}$，在用这个相似比乘以高 $h$，就是每部分的高了。

化简后公式为：$ \sqrt{ \frac{h^2i}{n} } $。

小提示：写代码时要乘以 $1.0$。

---

## 作者：_Sky_Dream_ (赞：0)

# [传送门](https://luogu.com.cn/problem/CF794B)

看一下图，$i$ 表示现在在切第 $i$ 刀，$h_i$ 表示这一刀的高度。

![](https://cdn.luogu.com.cn/upload/image_hosting/6djzqve7.png)

求的就是每个 $h_i$。

首先，我们求出这个三角形的总面积：$S = \displaystyle \frac{h}{2}$。

那么，对于第 $i$ 刀，我们得到的面积是：$ S_i = \displaystyle \frac{h \times i}{2n}$。

然后，根据相似三角形，可以得到这一刀切出的小三角形的底边 $y$，存在有以下等式：$\displaystyle \frac{h}{h_i} = \displaystyle \frac{1}{y}$。

得到 $y = \displaystyle \frac{h_i}{h}$。

根据三角形面积公式，可得：$S_i = \displaystyle \frac{{h_i}^2}{2h}$。

列出方程：$ \displaystyle \frac{{h_i}^2}{2h} = \displaystyle \frac{h \times i}{2n} $。

然后就快乐的解方程。

$ \displaystyle \frac{{h_i}^2}{2h} = \displaystyle \frac{h \times i}{2n} $

$ {h_i}^2 \times 2n = 2h^2 \times i$

$ {h_i}^2  =\displaystyle \frac{h^2 \times i}{n}$

$ h_i  = \sqrt {\displaystyle \frac{h^2 \times i}{n}}$

AC Code：

```cpp
//#pragma GCC optimize(1)
//#pragma GCC optimize(2)
//#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define int long long
#define rep(i,x,y) for(register int i=x;i<=y;++i)
#define rp(i,x,y) for(register int i=x;i>=y;--i)
#define N 100005
#define MAX 1145141919810
using namespace std;
int n,h;
inline void Enchanted(){
	srand(time(0));
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	cin>>n>>h;
	rep(i,1,n-1)
		printf("%.12lf ",sqrt((i*h*h*1.0)/n));
}
signed main(){Enchanted();return 0;}




```

---

## 作者：xuhanxi_dada117 (赞：0)

[题目传送门&题目大意](https://www.luogu.com.cn/problem/CF794B)

# 解法

考虑切完胡萝卜每一部分的面积为：

$$\frac{1}{2}\times h\times \frac{1}{n}=\frac{h}{2n}$$

所以，对于第 $i$ 刀，上方已经切过的部分面积为：

$$\frac{ih}{2n}$$

（设为 $V$）

设第 $i$ 刀距顶 $g_i$，这一刀的横截面长度为 $s_i$：

$$V=\frac{1}{2}\times g_i\times s_i$$

又由平行线相似：

$$\frac{g_i}{h}=\frac{s_i}{1}$$

所以：

$$V=\frac{1}{2}\times g_i\times \frac{g_i}{h}$$

$$g_i^2=2Vh$$

$$g_i=\sqrt{2Vh}$$

直接统计 $V$ 即可。

# 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
    int n,h;cin>>n>>h;
	double VolPart=1.0*h/2.0/n,VolNeed=0.0;
    for(int i=1;i<n;++i){
    	VolNeed+=VolPart;
    	printf("%.12lf ",sqrt(2*h*VolNeed));
	}
    return 0;
}

```

[AC 记录](https://www.luogu.com.cn/record/119116964)


---

## 作者：chufuzhe (赞：0)

### 1.题意

用 $n-1$ 条垂直于高的直线将一个等腰三角形成 $n$ 等份，问这些直线的坐标。

### 2.思路

以为要分成 $n$ 等份，所以每份的面积为总面积的 $\frac{1}{n}$ 。考虑从上往下分，因为是三角形，前 $i$ 份组成的三角形所占面积为 $\frac{i}{n}$ ，即$\frac{S_i}{S_n}=\frac{i}{n}$ 。

根据 [相似三角形](https://baike.baidu.com/item/%E7%9B%B8%E4%BC%BC%E4%B8%89%E8%A7%92%E5%BD%A2/159057?fr=aladdin) 可以得到 $\frac{S_i}{S_n}=\frac{(X_i) ^ 2}{n ^ 2}$，再利用三角形面积公式就可以出来了。

### 3.代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n, m; //定义
    cin >> n >> m; //输入
    for(int i = 1; i < n; i++) { //输出每一条直线的坐标
    	cout << fixed << setprecision(10) << m * sqrt(i * 1.0 / n) << ' '; //注意要保留十位小数
    }
    return 0;
}
```


---

