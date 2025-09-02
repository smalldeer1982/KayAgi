# [POI 2020/2021 R3] 星间通信 / Komunikacja międzyplanetarn

## 题目背景

译自 [XXVIII Olimpiada Informatyczna - III etap](https://sio2.mimuw.edu.pl/c/oi28-3/dashboard/) [Komunikacja międzyplanetarn](https://szkopul.edu.pl/problemset/problem/43LcdhShos7i99wnVNtQYUUK/statement/)。

d2t1。

## 题目描述

二维平面上有 $n$ 个点。

对于每个点，算出它到其他所有点的欧氏距离之和。

相对误差不超过 $0.1\%$ 即可。

## 说明/提示

对于所有数据，$2\leq n\leq 100000$，$-10^6\leq x,y\leq 10^6$。

| 子任务编号 | 附加限制 | 分数 |
| :----------: | :----------: | :----------: |
| 1 | $n\leq 1000$ | 4 |
| 2 | 所有点共线 | 16 |
| 3 | 点的坐标随机，相对误差不超过 $2\%$ 即可 | 20 |
| 4 | | 60 |

## 样例 #1

### 输入

```
4
-1 0
0 0
3 3
-1 1
```

### 输出

```
7.000000000000
6.656854249492
13.714776642119
6.886349517373
```

## 样例 #2

### 输入

```
25
-2 -2
-2 -1
-2 0
-2 1
-2 2
-1 -2
-1 -1
-1 0
-1 1
-1 2
0 -2
0 -1
0 0
0 1
0 2
1 -2
1 -1
1 0
1 1
1 2
2 -2
2 -1
2 0
2 1
2 2
```

### 输出

```
79.340412611230
68.023981606779
64.155694316737
68.023981606779
79.340412611230
68.023981606779
55.532407162959
51.265774235248
55.532407162959
68.023981606779
64.155694316737
51.265774235248
46.859106568475
51.265774235248
64.155694316737
68.023981606779
55.532407162958
51.265774235248
55.532407162959
68.023981606779
79.340412611230
68.023981606779
64.155694316737
68.023981606779
79.340412611230
```

## 样例 #3

### 输入

```
见附件```

### 输出

```
见附件```

# 题解

## 作者：wind_boy (赞：6)

[妙妙题！](https://www.luogu.com.cn/problem/P9405)

- **黎曼和近似**

根据定积分的定义，我们将区间 $[A,B]$ 分割成 $n$ 份，对每一份用区间中点处的 $f$ 值来近似平均值，从而近似整个区间的值. 形式化地：
$$
\int_A^Bf(x)\approx \sum_{i=0}^{n-1}\frac{B-A}nf(A+\frac{i(B-A)}n+\frac1{2n})
$$
那么，黎曼和近似的精度是多少呢？

> **定理**：如果 $f$ 在 $[A,B]$ 内任意阶可导，黎曼和近似的绝对误差在最坏情况下不超过 $\dfrac{K(B-A)^3}{24n^2}$，其中 $K$ 为 $|f^{(2)}(x)|$ 在 $[A,B]$ 中的最大值.

证明略。

-------

题解：

众所周知 $\int_0^{\frac\pi2}\cos\theta\,\text{d}\theta=1$。

也就是说，将一条线段映射到一条斜率为 $\tan \theta\pod{0\leq \theta\leq \pi}$ 的直线上的长度的积分为该线段长度的 $2$ 倍，即 $\int_0^{\pi}l\,|\cos\theta|\,\text{d}\theta=2l$。

考虑黎曼求和。我们选取 $m$ 个均匀的角度 $\alpha_1,\alpha_2,\cdots,\alpha_m$，将这些线段依次映射到 $y=\tan{\alpha_i}\cdot x$ 上，于是就转化为了一维问题。

对于一维问题，我们只需将其排序然后做前缀后缀和即可。

根据上述定理，其精度误差为 $O(m^{-2})$，因此取 $m=\Theta(\epsilon^{-0.5})$ 即可。

时间复杂度 $O(n\epsilon^{-0.5}\log n)$。

```cpp
#include<bits/stdc++.h>
#define fo(i,l,r) for(int i=(l);i<=(r);++i)
#define fd(i,l,r) for(int i=(l);i>=(r);--i)
#define ld double
using namespace std;
const int N=100007,B=30;
const ld PI=acos(-1.0);
int n,w[N];ld ans[N],v[N];
struct point{int x,y;}p[N];
bool cmp(int a,int b){return v[a]<v[b];}
int main()
{
	scanf("%d",&n);
	fo(i,1,n) scanf("%d%d",&p[i].x,&p[i].y);
	fo(T,0,B-1)
	{
		ld c=cos(PI/B*(T+0.5)),s=sin(PI/B*(T+0.5)),sum=0;
		fo(i,1,n) v[i]=p[i].x*c-p[i].y*s,w[i]=i;//旋转后映射到x轴
		sort(w+1,w+n+1,cmp);
		fo(i,1,n) ans[w[i]]+=v[w[i]]*(i-1)-sum,sum+=v[w[i]];
		sum=0;
		fd(i,n,1) ans[w[i]]+=sum-v[w[i]]*(n-i),sum+=v[w[i]];
	}
	fo(i,1,n) printf("%.6lf\n",ans[i]*PI/B/2);
}
```

---

## 作者：Aleph_Drawer (赞：6)

### 前言

两篇题解都写得比较简略，这里来一个比较详细的。

建议先掌握积分再做这道题目。

### 题解

非常有趣的题目！

这题的难度在于神秘却十分优美的转化上面。首先，根据部分分的提示，我们可以想到将二维的平面距离求和转移到一维上面。我们在平面上画一条 $y = \tan \theta \cdot x$ 的直线，然后在选定一个点 $(x,y)$。我们尝试将这个点映射到直线上，然后我们在这条直线上面计算完所有距离，最后我们除以 $\cos$ 值，然后就可以得到结果了。

具体的计算过程，我们可以先上图，然后再解释：

![](https://cdn.luogu.com.cn/upload/image_hosting/5hnxrs3z.png)

令 $A$ 的坐标为 $(x,y)$，那么 $|OC| = x, |DC| = \tan \gamma \cdot x, |AD| = y - \tan \gamma \cdot x$。

接下来是一个初中数学小 trick，八字模型，$\angle DAB = \angle DOC = \gamma$，所以进一步的，$|BD| = \sin \gamma (y - \tan \gamma \cdot x)$。

而 $|OD| = \dfrac x{\cos \gamma}$。

所以我们想要的 $|OB| = \dfrac x{\cos \gamma} + y \cdot \sin \gamma - \sin \gamma \tan \gamma \cdot x$。

由于 $\tan \gamma = \dfrac{\sin \gamma}{\cos \gamma}$，所以上式化简为 $y \cdot \sin \gamma - x \cdot \dfrac {\sin^2 \gamma - 1}{\cos \gamma}$。又因为 $\sin^2 \gamma + \cos^2 \gamma = 1$，所以最后化简为 $y \cdot \sin \gamma + x \cdot \cos \gamma$。这就是我们想要的东西了。

现在，我们可以随手画出一条经过原点的直线，然后就可以立刻得到 $|OB|$ 的长度了。

然而，对于不同的线段，由于其夹角不同，所以要乘上的系数也不同，如果我们想要画一条线段就解决问题，这是不可能的。

这种情况下，有一个非常有趣的降维打击方法，这来源于一个想法：

> 如果我把 $\gamma$ 值全部取一遍，最后再除以一个数，是不是可以得到值？

这的确是一个非常妙的想法，夹角与 $\gamma$ 是一个一次函数关系，而且当 $0 \leq \gamma \leq \pi$ 的时候，夹角的值是与 $\gamma$ 一一对应的。然而，这就意味着，我们不得不引入更高级的**积分**概念。

我们想象一个线段，它的长度是 $l$。然后现在已经画好了一条直线，$l$ 与直线的顺时针夹角为 $\alpha(0 \leq \alpha \leq \pi)$。

那么我们要求的就是

$$
\int_0^{\pi} l \cdot |\cos \alpha| \text{ d}\alpha
$$

把 $l$ 提取出来，就是

$$
l \cdot \int_0^\pi |\cos \alpha| \text{ d}\alpha
$$

绝对值看上去太别扭，按照性质拆成

$$
2l \cdot \int_{0}^{\pi / 2} \cos \alpha \text { d}\alpha
$$

此时答案就已经很明了了，但是我还是想多拆几步，令 $f(x) = \cos \alpha$，显然 $F(x) = \sin \alpha + C$。

然后就是 $2l (F(\dfrac \pi 2) - F(0)) = 2l$。

所以那个我们要除去的数就是 $2$。

接下来，正解就很明了了。我们把这个积分划成多段，然后分部求数值积分。对于每一段的积分，我们枚举 $\alpha$，按照要求算出所有映射的点，简单排序一下，然后用前缀和优化一下计算即可。

时间复杂度是 $O(n \log n \cdot k)$。其中 $k$ 是你将积分分成的部分数量。$k$ 取 $50$ 是可以通过的。

### 代码

```c++
#include<bits/stdc++.h>

typedef long double ld;

const int N = 1e5 + 105, K = 50;
const ld pi = acos(-1);

int n;
ld x[N], y[N], sum[N], res[N];

struct pairs {
	ld v; int id;
}tmp[N]; // 手写 pairs

bool cmp(pairs a, pairs b) {return a.v < b.v;}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%Lf%Lf", &x[i], &y[i]);
	for(int k = 1; k <= K; k++) {
		ld alpha = (ld)k * (pi / (ld)K); // alpha : 枚举的角度
		for(int i = 1; i <= n; i++)
			tmp[i].id = i, tmp[i].v = y[i] * sin(alpha) + x[i] * cos(alpha); // tmp[i].v : 映射的位置
		std::stable_sort(tmp + 1, tmp + n + 1, cmp);
		sum[1] = 0;
		for(int i = 2; i <= n; i++)
			sum[i] = sum[i - 1] + (ld)(i - 1) * (tmp[i].v - tmp[i - 1].v), res[tmp[i].id] += sum[i]; // 使用前缀和优化计算，这里分成两段计算
		sum[n] = 0;
		for(int i = n - 1; i; i--)
			sum[i] = sum[i + 1] + (ld)(n - i) * (tmp[i + 1].v - tmp[i].v), res[tmp[i].id] += sum[i];
	}
	for(int i = 1; i <= n; i++)
		printf("%Lf\n", res[i] * pi / K / 2.0); // 乘上每一个矩形的宽度，最后记得除以2
	return 0;
}
```



---

## 作者：Gorenstein (赞：4)

对于一点 $\boldsymbol\alpha_i:=(x_i,y_i)$，设其倾斜角为 $\theta$。不失一般性地，考察 $\theta\leqslant\dfrac{\pi}{2}$ 的情形。由于

$$
\begin{aligned}
\int_{0}^{\pi}\left|\cos(\varphi-\theta)\right|\text d\varphi&=\int_{-\theta}^{\pi-\theta}\left|\cos\varphi\right|\text d\varphi\\
&=\int_{-\theta}^{\frac{\pi}{2}}\cos\varphi\,\text d\varphi-\int_{\frac{\pi}{2}}^{\pi-\theta}\cos\varphi\,\text d\varphi\\
&=2\sin\frac{\pi}{2}+\sin\theta-\sin(\pi-\theta)\\
&=2,
\end{aligned}
$$

所以对于第 $m$ 个点，我们实际上只需求

$$
\frac{1}{2}\int_0^{\pi}\left(\sum_{i\neq m}\left|(\boldsymbol\alpha_i-\boldsymbol\alpha_m)\boldsymbol\cdot\boldsymbol e_{\varphi}\right|\right)\text d\varphi,
$$

其中 $\boldsymbol e_{\varphi}$ 是单位向量 $\boldsymbol i\cos\varphi+\boldsymbol j\sin\varphi$。



数值积分转一圈过去，每一度算一下就好了。但每次重新计算 $\boldsymbol\alpha_i-\boldsymbol\alpha_m$ 要做一百八十遍 $O\big(n^2\log n\big)$。利用前缀和可以做到对于每个 $\boldsymbol e_{\varphi}$，一次性算出每个投影点到其他投影点的距离之和。至此数值积分的单次运算可在 $O(n\log n)$ 时间内完成。

```cpp
for(ll i=1;i<=180;i++){
	DB rAd=pi*i/180.0;
	DB ex=cos(rAd),ey=sin(rAd);
	DB dphi=pi/180;
	for(ll i=1;i<=n;i++)a[i]=x[i]*ex+y[i]*ey,p[i]=i;
	sort(p+1,p+n+1,cmp);
	for(ll i=2;i<=n;i++)s1[i]=s1[i-1]+(a[p[i]]-a[p[i-1]])*(i-1);
	for(ll i=n-1;i;i--)s2[i]=s2[i+1]+(a[p[i+1]]-a[p[i]])*(n-i);
	for(ll i=1;i<=n;i++)ans[p[i]]+=(s1[i]+s2[i])*dphi/2.0;
}
```

---

## 作者：Semsue (赞：4)

和[这个](https://www.luogu.com.cn/blog/328405/ou-ji-li-dei-ju-li-zhi-hu)是一模一样的，我再复读一遍。

尝试把答案化为两点在斜率为 $\tan\theta$ 的直线上投影的积分。

$$
\int_{0}^{2\pi}\sqrt{(x_i-x_j)^2+(y_i-y_j)^2}|\cos\theta|\text{d}\theta=\int_{0}^{2\pi}|v_i-v_j|\mathrm d\theta=4\sqrt{(x_i-x_j)^2+(y_i-y_j)^2}
$$

其中 $v_i=x_i\cos\theta-y_i\sin\theta$。

而 $\int_{0}^{2\pi}|v_i-v_j|\mathrm d\theta$ 可以使用黎曼和近似估计。算出所有 $v$ 之后排序即可 $O(n)$ 求出所有点的答案。

这题卡时间不卡精度，划分少一点（我搞了 $100$ 个）矩形即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 5;
const long double eps = 1e-4, pi = acos(-1.0);
int n, rk[maxn];
struct node{
    long double x, y;
}p[maxn];
long double ans[maxn], v[maxn];
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%Lf%Lf", &p[i].x, &p[i].y);
    }
    int B = 100;
    for (int i = 0; i < B; i++)
    {
        long double cs = cos(2.0 * pi * i / B), si = sin(2.0 * pi * i / B);
        for (int j = 1; j <= n; j++)
            v[j] = p[j].x * cs - p[j].y * si, rk[j] = j;
        sort(rk + 1, rk + n + 1, [&](int x, int y)
        {
            return v[x] < v[y];
        });
        long double sum = 0;
        for (int t = 1; t <= n; t++)
        {
            int j = rk[t];
            ans[j] += v[j] * (t - 1) - sum;
            sum += v[j];
        }
        sum = 0;
        for (int t = n; t; t--)
        {
            int j = rk[t];
            ans[j] += sum - v[j] * (n - t);
            sum += v[j];
        }
    }
    for (int i = 1; i <= n; i++) printf("%.10Lf\n", ans[i] / B * pi / 2.0);
    return 0;
}
```

---

## 作者：qiyichen12 (赞：1)

# 预告
本题解重在实现，证明可能有疏漏，还请读者包涵。
# 思路
我们的思路是，$\forall 0 ≤ \alpha ≤ \pi$，画直线 $y = \tan(\alpha)x$，将所有的点都映射到上面，用前缀和将时间复杂度将为 $O(n)$，最后除以个常数。

# 计算
设映射线段原长度为 $d$，则我们计算的是：

$\displaystyle \int_0^{\pi} d\left| \cos(\alpha) \right | \mathop{}\!\mathrm{d} \alpha = d \displaystyle \int_0^{\pi} \left| \cos(\alpha) \right | \mathop{}\!\mathrm{d} \alpha$

因为 $\displaystyle \int_0^{\pi/2} \cos(\alpha) \mathop{}\!\mathrm{d} \alpha = -\displaystyle \int_{\pi/2}^{\pi} \cos(\alpha) \mathop{}\!\mathrm{d} \alpha$

所以 $d \displaystyle \int_0^{\pi} \left| \cos(\alpha) \right | \mathop{}\!\mathrm{d} \alpha = 2d \displaystyle \int_0^{\pi/2} \cos(\alpha) \mathop{}\!\mathrm{d} \alpha$

众所周知 $\cos$ 积分为 $\sin$，所以：

原式 = $2d \times (\sin(\pi/2)-\sin(0)) = 2d$

所以常数为 $\frac{2d}{d} = 2$
# 实现
用 $\frac{k}{K}$ 模拟 $\mathop{}\!\mathrm{d}\alpha$


```cpp
for (int k = 1;k <= 100;k++) long double dal = k/(long double)100*Pi;
```


接下来要推映射。

设点 $A(x,y)$ 投影在直线 $OP(y = \tan(\alpha)x)$ 上为 $P(x_P,y_P)$。作 $AB \perp PB$ 于 $B$ 使得 $AB \parallel x$轴。所以 $x_P = x-\sin(\alpha)\times AP$，$y_P = y-cos(\alpha) \times AP$。所以 $OP = \sqrt{x_P^2+y_P^2} = \sqrt{x^2+y^2+AP^2+2\sin(\alpha) \times AP+2\cos(\alpha) \times AP}$。

作 $AC \parallel y$轴，则 $C(x,\tan(\alpha)x)$，$AP = \sin(\alpha)\times (y-\tan(\alpha)x) = \sin(\alpha)y-\frac{\sin^2(\alpha)}{\cos(\alpha)}x$。

简化可得 $OP = \cos(\alpha)x+\sin(\alpha)y$（过程实在写不下了，可以看看[**Aleph_Drawer**](https://www.luogu.com.cn/user/181571)的题解）


```cpp
for (int i = 1;i <= n;i++) ur[i] = sin(dal)*r[i][1]+cos(dal)*r[i][0];//ur是OP r是x、y。
```

得到了以后，要对数组进行排序。

```cpp
sort(ur+1,ur+n+1);
```
然后本题的第二要点来啦！用前缀和优化，具体还要推一推。对于直线上第 $i$ 个点，设其为 $P_i$，它前面的点距离之和是 $P_1P_i+P_2P_i+... = \sum_{j = 1}^{i-1}P_jP_i = \sum_{j=1}^{i-1}j\times P_jP_{j+1}$，后面同理。于是设 $sum_i$ 表示前面的点距离之和与后面的点距离之和。

```cpp
        for (int i = 2;i <= n;i++) sum[i] = sum[i-1] + (i-1)*(ur[i]-ur[i-1])；
        sum[n] = 0;
        for (int i = n-1;i >= 1;i--) sum[i] = sum[i+1] + (n-i)*(ur[i+1]-ur[i])；
```

这时只需要建立 $rs_i$ 表示结果，但因为有过排序，所以要让 $ur$ 数组变成结构体，增加 $ip$ 一项记录原位置。

```cpp
        for (int i = 2;i <= n;i++) sum[i] = sum[i-1] + (i-1)*(ur[i].v-ur[i-1].v),rs[ur[i].ip] += sum[i];
        sum[n] = 0;
        for (int i = n-1;i >= 1;i--) sum[i] = sum[i+1] + (n-i)*(ur[i+1].v-ur[i].v),rs[ur[i].ip] += sum[i];
```

最后输出即可：

```cpp
for (int i = 1;i <= n;i++) printf("%.10Lf\n",rs[i]*Pi/(long double)100.0/2.0);
```

---

## 作者：Rurirat (赞：1)

> 数竞党的防御性证明会用严谨的逻辑说明结论的正确性，而对“解题思路是如何想到的”一类的问题没有任何启发；oier/acmer 的题解则大多会提示我们从哪里入手，却不加严谨的证明。而本题解采取折中的方案：既对解题思路没有任何启发，也不加严谨的证明。

**题意**：给定 $Q_1...Q_n\in \mathbb{R}^2$，对每个 $k\in\{1...n\}$，求 $a_k:=\sum_{i=1}^{n}Q_kQ_i$

先推公式：

$$
a_k 
= \sum_{i=1}^{n} Q_kQ_i
= \frac12\sum_{i=1}^{n} Q_kQ_i\times 2
= \frac12\sum_{i=1}^{n} Q_kQ_i\int_0^\pi|\cos(\theta-\phi_i)|d\theta
$$

对 $\forall \phi_1...\phi_n\in\mathbb{R}$ 成立。

因为 $|\cos\theta|$ 作为 $\theta$ 的函数以 $\pi$ 为周期，而积分区间的长度恰好为 $\pi$，所以任意平移后积分值恒为 $2$。

$$
=\frac12\int_0^\pi\sum_{i=1}^nQ_kQ_i|\cos \min(|\theta-\phi_i|,2\pi-|\theta-\phi_i|)|d\theta
$$

注意 $\cos$ 是以 $2\pi$ 为周期的偶函数，上式显然成立。

而对于 $a,b\in[0,2\pi)$，$\min(|a-b|,2\pi-|a-b|)=:\arg(a,b)$ 就是射线 $a$ 与 $b$ 的夹角。（不是标准的符号。）

$$
=\frac12\int_0^\pi\sum_{i=1}^nQ_kQ_i|\cos\arg(\theta,\phi_i)|d\theta
$$

取 $\phi_i=\arg\vec{Q_kQ_i}$，这里 $\arg$ 表示取向量的方向，值域为 $[0,2\pi)$。

对于 0 向量，方向任取即可，因为这只是理论推导，并不会在代码中求 0 向量的方向。

$$
=\frac12\int_0^\pi\sum_{i=1}^n|\vec{Q_kQ_i}\cdot\vec{e_\theta}|d\theta
$$

其中 $\vec{e_\theta}:=(\cos\theta,\sin\theta)$ 为 $\theta$ 方向的单位向量。

$$
=\frac12\int_0^\pi\sum_{i=1}^n|(\vec{Q_i}-\vec{Q_k})\cdot\vec{e_\theta}|d\theta
=\frac12\int_0^\pi\sum_{i=1}^n|\vec{Q_i}\cdot\vec{e_\theta}-\vec{Q_k}\cdot\vec{e_\theta}|d\theta
$$

设 $c_j=\vec{Q_j}\cdot\vec{e_\theta}$，$j=1...n$，则

$$
=\frac12\int_0^\pi\sum_{i=1}^n|c_i-c_k|d\theta
$$

设 $d_1...d_n$ 是 $c_1...c_n$ 的递增的排列，$d_{r_j}=c_j$，其中 $r_1...r_n$ 是 $1...n$ 的一个排列。

$$
=\frac12\int_0^\pi\sum_{i=1}^n|d_i-d_{r_k}|d\theta
$$

注意到 $d_1\leq...\leq d_{r_k}\leq...\leq d_n$，于是

$$
=\frac12\int_0^\pi\sum_{i=1}^{r_k}(d_{r_k}-d_i)+\sum_{i=r_k+1}^n(d_i-d_{r_k})d\theta
=\frac12\int_0^\pi\sum_{i=r_k+1}^nd_i-\sum_{i=1}^{r_k}d_i+(2r_k-n)d_{r_k}d\theta
$$

设 $D_j=\sum_{i=1}^jd_i$ 为 $d$ 的前缀和，特别地 $D_0=0$。

$$
=\frac12\int_0^\pi D_n-2D_{r_k}+(2r_k-n)d_{r_k}d\theta
=\frac12\int_0^\pi f(k,\theta)d\theta
$$

注意到，对于一个 $\theta$，可以一起计算所有的 $f(k,\theta)$；反之对于一个 $k$，则不能很好地计算 $\int f(k,\theta)d\theta$。换言之

```cpp
for(θ=0度;θ<=180度;θ+=1度)
{
    计算所有的f(k,θ) // O(n)
    for(k=1;k<=n;k++)
        使用f(k,θ)
}
```
是可行的，复杂度为 $O(n\times180)$；但
```cpp
for(k=1;k<=n;k++)
{
    计算∫f(k,θ)dθ
}
```
是不行的。

于是考虑对定积分进行估计：取 $m$ 是一个较大的自然数，将积分区间分成 $m$ 份，第 $j$ 份为 $[\frac{(j-1)\pi}{m},\frac{j\pi}{m}]$，$j=1...m$。用区间右端点的函数值代替这个区间内的函数值。

$$
\approx\frac12\sum_{j=1}^mf(k,\frac{j\pi}{m})\times\frac{\pi}{m}
=\frac{\pi}{2m}\sum_{j=1}^mf(k,\frac{j\pi}{m})
$$

至此可以用如下代码计算，复杂度 $O(mn)$。
```cpp
for(int j=1;j<=m;j++)
{
	计算所有的f(k,jπ/m) // O(n)
	for(int k=1;k<=n;k++)
		answer[k]+=f(k,jπ/m)(π/2m);
}
```

实践 $m$ 不必取得很大，太大反而会超时，大约 $180$ 即可通过。

---

## 作者：LEE114514 (赞：0)

有史以来做过在最巧妙的前提下最简洁的题目，非常有意思，出题人简直是天才！

## 思路

抛开第一档暴力分，我们看到子任务二，最有启发的一个子任务。所有点共线时，我们可以通过计算相邻两点间的距离并通过前缀和解决这个问题。

具体的，不妨设这 $n$ 个点于 $x$ 轴共线，其他直线同理。假设他们的横坐标升序排列分别为 $x_1,x_2,x_3,\cdots,x_n$，则左边的点对 $i$ 的贡献记作 $f_i=\sum_{j=1}^{i-1} {x_i-x_j}$，右边的记作 $g_i=\sum_{j=i+1}^{n} {x_j-x_i}$，则 $ans_i=f_i+g_i$。

可以推导出 $f_i=f_{i-1}+(i-1)(x_i-x_{i-1}),g_i=g_{i+1}+(n-i)(x_{i+1}-x_{i})$，因此配合前缀和优化可以在 $O(n \log n)$ 的情况下解决共线的情况，瓶颈为排序。

由此想到，要把问题转化到一条直线上。在本题中，我们通过投影实现这一点。

接下来我们证明，将一条线段投影至绕原点旋转半周的直线上，其投影长度对直线倾斜角的积分值为线段长度的两倍。

不妨设线段所对应的向量为 $(l \cos \theta,l \sin \theta),\theta \in [0,\frac{\pi}{2})$，$\theta$ 取其它范围时同理可证。设旋转直线的倾斜角为 $\phi$，那么线段在直线上的投影长度为 $l |\cos (\phi-\theta)|$，于是所求积分即为

$$
\begin{aligned}
\int_{0}^{\pi} l |\cos(\phi-\theta)|d\phi&=l \int_{0}^{\pi} |\cos(\phi-\theta) |d\phi
\\&=l \int_{-\theta}^{\pi-\theta} |\cos \phi| d\phi
\\&=l(\int_{-\theta}^{\frac{\pi}{2}} \cos \phi d\phi - \int_{\frac{\pi}{2}}^{\pi-\theta} \cos \phi d\phi)
\\&=l(1+\sin \theta+1-\sin(\pi-\theta))
\\&=2l
\end{aligned}
$$

这说明我们可以通过投影和积分来解决这题。投影有一个美妙的性质是先投影再相减与先相减再投影没有区别，而且可以将一个平面转化为一条直线。

设第 $i$ 个点坐标 $p_i$。于是，对于第 $m$ 个点我们所求可以转化为：
$$
\begin{aligned}
\sum_{i\neq m} \frac{1}{2} \int_{0}^{\pi}{|(p_i-p_m)\cdot e_\phi| d\phi}
&=\frac{1}{2} \int_{0}^{\pi}  \sum_{i\neq m}{|(p_i-p_m)\cdot e_\phi| d\phi}
\\&=\frac{1}{2} \int_{0}^{\pi}  \sum_{i\neq m}{|p_i \cdot e_\phi - p_m \cdot e_\phi| d\phi}
\end{aligned}
$$
其中 $e_\phi=(\cos\phi,\sin\phi)$。

再令 $q_i = p_i \cdot e_\phi$，即投影后的对应点。则有：
$$
\frac{1}{2} \int_{0}^{\pi}  \sum_{i\neq m}{|q_i - q_m| d\phi}
$$
已经转化为了共线的形式，因此我们需要的就是枚举 $\phi$，并且对每一个 $\phi$，把所有点 $p_i$ 投影到 $y=\tan \phi$ 上对应的 $q_i$ 求出来用刚才的共线算法跑一遍。若把 $\pi$ 分成 $k$ 份，则复杂度为 $O(k n \log n)$。

## Code

把 $\frac{d\phi}{2}$ 提出来最后一起算。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
const double pi=acos(-1);
int n;
int x[maxn],y[maxn];
double f[maxn],g[maxn],res[maxn];
pair<double,int> s[maxn];
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;++i) scanf("%d%d",x+i,y+i);
    for(int k=0;k<180;++k){
        double phi=k*pi/180;
        double cc=cos(phi),ss=sin(phi);
        for(int i=1;i<=n;++i) s[i]=make_pair(cc*x[i]+ss*y[i],i);
        sort(s+1,s+n+1);
        for(int i=1;i<=n;++i) f[i]=f[i-1]+(i-1)*(s[i].first-s[i-1].first);
        for(int i=n-1;i>=1;--i) g[i]=g[i+1]+(n-i)*(s[i+1].first-s[i].first);
        for(int i=1;i<=n;++i) res[s[i].second]+=f[i]+g[i];
    }
    for(int i=1;i<=n;++i) printf("%.9lf\n",pi*res[i]/360);
}
```

---

## 作者：littlez_meow (赞：0)

神秘妙妙技巧题。

[题目指路](https://www.luogu.com.cn/problem/P9405)。

## 思路

首先考虑在一条直线上的情况。将这条直线旋转至 $x$ 轴并按横坐标排序，设其坐标分别为 $x_1,x_2,\cdots,x_n$，则对于点 $i$，左侧点的贡献为 $(x_2-x_1)+2(x_3-x_2)+\cdots+(i-1)(x_i-x_{i-1})$，右侧点同理。这是前缀和就可以简单解决的。

接下来考虑把一般情况映射到在一条直线上的情况。首先，根据初中数学知识，过 $(x,y)$ 向直线 $y=\tan\theta \cdot x$ 作垂线，垂足到原点的距离为 $x\cos\theta+y\sin\theta$。因此，将 $(x,y)$ 投影到斜率为 $\tan\theta$ 的直线上，再将该直线旋转至 $x$ 轴，得到的坐标为 $(x\cos\theta+y\sin\theta,0)$。

此时，原先长度为 $d$，与 $x$ 轴正半轴夹角为 $\alpha$ 的线段长度就会变成 $d\cos(\alpha-\theta)$。

如果对于每条线段，它们的 $\alpha$ 都一样，我们就可以把线段长度乘的系数提出来，当一条直线计算。然而，它们不一样。

怎么办呢？

我们可以多取几条直线。当直线的数量趋于无穷大，就可以认为 $\alpha-\theta$ 均匀取遍了每个值，我们就可以交换求和顺序，将 $\alpha-\theta$ 相同的放在一起计算，最后除以某个值就行。

既然求和已经到了无穷，又要除以无穷大，这显然可以想到积分。我们有下式：

$$\int_{0}^{\pi}l|\cos\theta|\mathrm{d}\theta=2l$$

拆开绝对值易证。其意义为，一条长度为 $l$ 的线段，投影到斜率为 $\tan\theta$ 的直线上，投影后长度对 $\theta$ 的积分，为两倍线段长度。

对于每个 $\theta$，都可以按一条直线的方式求出 $l$。

这个积分怎么求？自适应辛普森显然是不合适的。我们可以用最朴素的方法：黎曼和。我们把积分划分成多段，每一段取一个 $\theta$，就近似认为成那个值。

时间复杂度 $O(Tn\log n)$。其中 $T$ 为积分段数，$n\log n$ 为排序。

## 代码
非常简洁。

```cpp
#include<bits/stdc++.h>
#define F(i,a,b) for(int i(a),i##i##end(b);i<=i##i##end;++i)
#define R(i,a,b) for(int i(a),i##i##end(b);i>=i##i##end;--i)
#define ll long long
#define File(a) freopen(#a".in","r",stdin);freopen(#a".out","w",stdout)
using namespace std;
const int MAXN=1e5+1,T=30;
const long double pi=acos(-1);
int n;
struct Point{
	int id;
	long double x;
	bool operator<(Point t){
		return x<t.x;
	}
}pos[MAXN];
int x[MAXN],y[MAXN];
long double ans[MAXN];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;
	F(i,1,n) cin>>x[i]>>y[i];
	F(TwT,1,T){
		long double theta=pi/T*TwT,si=sin(theta),co=cos(theta);
		long double sum(0);
		F(i,1,n) pos[i].id=i,pos[i].x=co*x[i]-si*y[i];
		sort(pos+1,pos+n+1);
		F(i,2,n) sum+=(i-1)*(pos[i].x-pos[i-1].x),ans[pos[i].id]+=sum;
		sum=0;
		R(i,n-1,1) sum+=(n-i)*(pos[i+1].x-pos[i].x),ans[pos[i].id]+=sum;
	}
	F(i,1,n) cout<<fixed<<setprecision(6)<<ans[i]*pi/T/2<<"\n";
	return 0;
} 
```

完结撒花，不喜勿喷 ovo~

---

