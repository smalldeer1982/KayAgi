# Property

## 题目描述

Bill is a famous mathematician in BubbleLand. Thanks to his revolutionary math discoveries he was able to make enough money to build a beautiful house. Unfortunately, for not paying property tax on time, court decided to punish Bill by making him lose a part of his property.

Bill’s property can be observed as a convex regular $ 2n $ -sided polygon $ A_{0}\ A_{1}...\ A_{2n-1}\ A_{2n},\ A_{2n}=\ A_{0} $ , with sides of the exactly 1 meter in length.

Court rules for removing part of his property are as follows:

- Split every edge $ A_{k}\ A_{k+1},\ k=0...\ 2n-1 $ in $ n $ equal parts of size $ 1/n $ with points $ P_{0},P_{1},...,P_{n-1} $
- On every edge $ A_{2k}\ A_{2k+1},\ k=0...\ n-1 $ court will choose one point $ B_{2k}=\ P_{i} $ for some $ i=0,...,\ n-1 $ such that ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF852C/e71ce7d28e76a9d68c876b746b3556061957b614.png)
- On every edge $ A_{2k+1}A_{2k+2},\ k=0...n-1 $ Bill will choose one point $ B_{2k+1}=\ P_{i} $ for some $ i=0,...,\ n-1 $ such that ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF852C/7095d055aa9dac0eea6c740c3e32d5c3310f8624.png)
- Bill gets to keep property inside of $ 2n $ -sided polygon $ B_{0}\ B_{1}...\ B_{2n-1} $

Luckily, Bill found out which $ B_{2k} $ points the court chose. Even though he is a great mathematician, his house is very big and he has a hard time calculating. Therefore, he is asking you to help him choose points so he maximizes area of property he can keep.

## 说明/提示

To maximize area Bill should choose points: $ B_{1}=P_{0} $ , $ B_{3}=P_{2} $ , $ B_{5}=P_{1} $

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF852C/56dafbdba9c3350fcbc41412bc74c64b71c99fdf.png)

## 样例 #1

### 输入

```
3
0 1 2
```

### 输出

```
0 2 1
```

# 题解

## 作者：xzggzh1 (赞：2)

题意：

有一个正  $2n$ 边形，在每条边上有  $n$ 等分点。现在已经选定了  $n$ 个点，第  $i$个点分别位于第  $2i+1$ 条边上，且这  $n$ 个点的序号构成了一个排列；你需要再选出  $n$ 个点位于第  $2i$ 条边上，并且这  $n$ 个点的序号也构成一个排列，使得这些点构成的多边形面积最大。

---

这是个和几何略相关的题，简略作一个角的图，设左边的取到 $i$ 等分，右边的取到 $j$ 等分，中间的取到 $x$ 等分，设两遍之角的补交为 $\theta$。

![](https://cdn.luogu.com.cn/upload/image_hosting/hzejs21i.png)

那么红色部分的面积为 $(L-j+i)\cos \theta \times (L-j+i)\sin \theta-x(L-j)\sin \theta -(L-x)i\sin\theta $

刨去前面和 $x$ 无关的部分，留下 $\sin \theta (-Lx-Li+x(i+j))$ 要使这个最大，只要大的 $x$ 匹配大的 $(i+j)$ 即可，排序一下就好了。


---

核心代码

```cpp
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i)scanf("%d",&a[i]);
	a[n+1]=a[1];
	for(int i=1;i<=n;++i)b[i]=mp(a[i]+a[i+1],i);
	sort(b+1,b+n+1);
	for(int i=1;i<=n;++i)a[b[i].second]=i-1;
	for(int i=1;i<=n;++i)printf("%d ",a[i]);
}
```

---

## 作者：1234567890sjx (赞：0)

不会做，没救了。

可以把新添加的 $n$ 个点所添加的面积看作是在其原来有的左右两个点和这个点构成的三角形。问题在于如何构造点让这个面积最大。考虑上计算几何。设其左边原有的点为 $A_i$ 等分，右边原有的点为 $A_j$ 等分。若枚举中间的点为 $p$ 等分，那么就可以容易的发现新的三角形的面积和 $A_i+A_j$、$p$ 均强相关。若 $A_i+A_j$、$p$ 更大则三角形的面积更大。因此问题变为给定一个数组 $A$，现在需要找到一个排列 $p$ 满足 $\sum\limits_{i=1}^n A_ip_i$ 的值尽量大。这个贪心一下，让尽量大的 $A_i$，也就是前面所说的 $A_i+A_j$ 配尽量大的 $p$ 即可。时间复杂度为 $O(n\log n)$，（写个基排能 $O(n)$）。

---

## 作者：EuphoricStar (赞：0)

NOIP 模拟赛 T1，小清新几何题。

要让选出的点组成的多边形面积最大，就要让正多边形的面积减去选出的点组成的多边形面积最小。而这个面积差可以表示成 $2n$ 个三角形的面积，即 $\sum\limits_{i = 0}^{2n - 1} S_{\triangle A_i A_{(i + 1) \bmod n} B_{(i + 1) \bmod n}}$。

众所周知 $S_{\triangle} = \frac{1}{2} ab \sin \theta$，而在本题中 $\theta$ 恒等于正 $2n$ 多边形的内角，因此可以约去。如果令给出的排列为 $p$，要求的排列为 $q$，相当于最小化 $\sum\limits_{i = 0}^{n - 1} (n - p_i) q_i + (n - q_i) p_{(i + 1) \bmod n}$。化简后相当于最大化 $\sum\limits_{i = 0}^{n - 1} q_i (p_i + p_{(i + 1) \bmod n})$。

令 $c_i = p_i + p_{(i + 1) \bmod n}$，式子变成 $\sum\limits_{i = 0}^{n - 1} q_i c_i$。显然小的和小的配对，大的和大的配对，因此 $q_i$ 即为 $c_i$ 的排名。排序求一下即可。

[code](https://codeforces.com/contest/852/submission/232177109)

---

