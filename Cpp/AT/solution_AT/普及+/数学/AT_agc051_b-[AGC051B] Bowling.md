# [AGC051B] Bowling

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc051/tasks/agc051_b

> 平面上にボウリングのピンが何本か立っており、それを $ 4 $ 人の人が異なる角度から眺めています。 $ 1 $ 人にだけ他の人より遥かに多くのピンが見えることはあるでしょうか。

ピンを単純に $ xy $ 平面上の点集合とみなしましょう。 $ 4 $ 人の位置を以下の図に示します。 厳密には、

- **A** さんから見ると、$ y $ 座標が等しい $ 2 $ 本のピンは重なって見えます。
- **B** さんから見ると、($ x $ 座標 - $ y $ 座標) が等しい $ 2 $ 本のピンは重なって見えます。
- **C** さんから見ると、$ x $ 座標が等しい $ 2 $ 本のピンは重なって見えます。
- **D** さんから見ると、($ x $ 座標 + $ y $ 座標) が等しい $ 2 $ 本のピンは重なって見えます。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_agc051_b/cf17bb504667e73875a26607be26bad6c893bba0.png)

**A**, **B**, **C**, **D** さんに見えるピンの数をそれぞれ $ a,\ b,\ c,\ d $ とします。

以下の条件を全て満たすような何らかのピンの配置を構成してください。

- $ d\ \geq\ 10\ \cdot\ \max\ \{\ a,\ b,\ c\ \} $
- ピンの本数は $ 1 $ 本以上 $ 10^5 $ 本以下である。
- ピンの座標は全て $ 0 $ 以上 $ 10^9 $ 以下の整数である。
- $ 2 $ 本のピンが同じ位置にあることはない。

## 说明/提示

### Sample Explanation 1

\*\*この出力例は出力形式を例示するものであり、正解ではありません。\*\* この出力は問題文中の図に対応し、$ d\ =\ 8,\ a\ =\ b\ =\ c\ =\ 7 $ です。頑張りましたが、AC には届きません。

## 样例 #1

### 输入

```
```

### 输出

```
9
1 1
1 5
2 7
4 4
5 3
6 8
7 5
8 2
8 7```

# 题解

## 作者：墨笙_Mooos (赞：8)

## 题意翻译

> 有数个大头钉在二维平面上，有四个人从不同的角度观察它们，重叠的点视为一个，是否可能有一个人观察到的大头钉数量远多余其他人？

让我们把大头钉的位置简化为二维坐标上的点。四个人观察的角度如下：

* ```A``` 从左往右观察。即所有 $y$ 坐标相同的点是重叠的。
* ```B``` 从左下往右上观察。即所有 $x$ 坐标与 $y$ 坐标相减的值相同的点是重叠的。
* ```C``` 从下往上观察。即所有 $x$ 坐标相同的点是重叠的。
* ```D``` 从右下往左上观察。即所有 $x$ 坐标与 $y$ 坐标相加的值相同的点是重叠的。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_agc051_b/cf17bb504667e73875a26607be26bad6c893bba0.png)

令 ```A, B, C, D``` 观察到的大头针数量为 $a, b, c, d$，你需要构造一组大头针的排布，满足以下一些条件：

* $d \geq 10 \times \max\{a, b, c\}$
* 大头钉的数量不多于 $10^5$ 个。
* 大头钉的坐标均为 $[0, 10^9]$ 内的整数。
* 不存在两个坐标相同的大头钉。

没有输入，直接输出一组解。

## 思路

考虑 ```A``` 的视角，因为 ```D``` 看到的点是 $\max\{a, b, c\}$ 的十倍，所以 ```A``` 每看到一个点就至少有九个点被挡住了。

同理 ```B, C``` 视角也有至少有九成的点被挡住了。

因此，可以令 $\vec{i}, \vec{j}, \vec{k}$ 分别表示与 $y = 0, y = x, x = 0$ 平行且长度不为零的向量（即与 ```A, B, C``` 视线平行的向量），构造一个如下的向量集合 / 点集。

$$\left\{ p\vec{i} + q\vec{j} + r\vec{k}|0\leq p, q, r < 10 \right\}$$

由上可知，只要这个集合没有重复元素，就有 ```A, B, C``` 视角中九成的点被挡。

例如考虑 ```A``` 视角时，无论 $p$ 的大小如何变化，其看到的点不会变化，而 $p$ 可取的数有 $10$ 个，故有九个点被遮挡。```B, C``` 视角同理。

因而此时只要 ```D``` 能看到所有的点就是一组解。

令 $A = \left| \vec{i} \right|, B = \left| \vec{j} \right|, C = \left| \vec{k} \right|$，以上命题等价于下列两个集合没有重复元素：

$$S=\left\{\left(pA + qB, qB + rC\right) | 0\leq p, q, r < 10\right\}$$
$$T=\left\{pA + 2qB + rC | 0\leq p, q, r < 10\right\}$$

因为有 $0\leq p, q, r < 10$ 的限制，可以考虑十进制，即令 $A = 1, B = 100, C = 10$，那么 $pA$ 控制个位数，$rC$ 控制十位数，$qB$ 控制百位数字，因此集合 $S$ 中不会有重复元素。在集合 $T$ 中，$qB$ 控制百位和千位数字，所以 $T$ 中也不会有重复元素。

注意，这里不能让 $qB$ 控制个位或者十位，因为在集合 $T$ 的元素中可能影响到后面一位。

还有一种思路，在 $\left[ 1, \dfrac{5\times 10^8}{9}\right]$ 内随机生成 $A, B, C$，这样有极大的概率可以使得集合 $S, T$ 没有重复元素。事实上，这也是 Official Editorial 中的做法。


```
// Solution 1
	A = 1, B = 100, C = 10;
	For (i, 0, 9) For (j, 0, 9) For (k, 0, 9)
		P.emplace_back (A * i + B * j, B * j + C * k);
	cout << P.size () << endl;
	for (auto& Now : P) cout << Now.first << ' ' << Now.second << endl;
```

```
// Solution 2
	A = Rnd () % 55555555, B = Rnd () % 55555555, C = Rnd () % 55555555;
	For (i, 0, 9) For (j, 0, 9) For (k, 0, 9)
		P.emplace_back (A * i + B * j, B * j + C * k);
	cout << P.size () << endl;
	for (auto& Now : P) cout << Now.first << ' ' << Now.second << endl;
```

---

## 作者：Sonnety (赞：1)

题意比较清晰，就不概括了。

## 分析：

按照题意，我们要让 A,B,C 三个方向所看到的球被挡住 $\frac{9}{10}$，因此，对于同一列，我们构造 $10$ 个点，有 $9$ 个点被挡住，同一行，构造 $10$ 个点，有 $9$ 个点被挡住，对于 $y=x$ 上的点，构造 $10$ 个点，有 $9$ 个点被挡住。

![你好](https://cdn.luogu.com.cn/upload/image_hosting/o8mh7jyk.png)

进行如上图的构造，线段由 $10$ 个 $y=x$ 上的点构成。

这样就保证了 $\frac{9}{10}$ 的点被挡住，而为了防止我们设置的点重合，需要保证我们 $x$ 的增长大于 $10$，$y$ 的增长大于 $x$ 的增长 $\times 10$。

而对于每一行，都有至少 $10$ 个露出的点在 D 的视角上，满足 $10$ 倍的关系。

## Code

代码构造了 $13\times 13\times 13$ 个数，其实没必要，$10\times 10\times 10$ 足够，可以通过。

```
#include<bits/stdc++.h>
using namespace std;
#define il inline
#define rg register int
typedef long long ll;
int Max(int x,int y)<%if(x<y)	return y;return x;%>
int Min(int x,int y)<%if(x<y)	return x;return y;%>
int Abs(int x)<%if(x<0)	return x*(-1);return x;%>
const int maxn=1e5+30; 

struct Vector{
	int x,y;
};Vector n1,n2,n3,ans[maxn];
int cnt;

int main(){
	n1.x=39,n1.y=0;
	n2.x=0,n2.y=8313;
	//神秘の数 
	//只要满足 n1.x>10,n2.y>n1.x*10，即可通过 
	n3.x=1,n3.y=1;
	for(rg i=1;i<=13;++i){
		for(rg j=1;j<=13;++j){
			for(rg k=1;k<=13;++k){
				ans[++cnt].x=n1.x*i+n3.x*k;
				ans[cnt].y=n2.y*j+n3.y*k;
			}
		}
	}
	//10*10*10可过 
	printf("2197\n");
	//13*13*13=2197
	for(rg i=1;i<=cnt;++i){
		printf("%d %d\n",ans[i].x,ans[i].y);
	} 
	return 0;
}
```

---

## 作者：User_Unauthorized (赞：1)

## 题意

> 有数个大头钉在二维平面上，有四个人从不同的角度观察它们，重叠的点视为一个，是否可能有一个人观察到的大头钉数量远多余其他人？

让我们把大头钉的位置简化为二维坐标上的点。四个人观察的角度如下：

* ```A``` 从左往右观察。即所有 $y$ 坐标相同的点是重叠的。
* ```B``` 从左下往右上观察。即所有 $x$ 坐标与 $y$ 坐标相减的值相同的点是重叠的。
* ```C``` 从下往上观察。即所有 $x$ 坐标相同的点是重叠的。
* ```D``` 从右下往左上观察。即所有 $x$ 坐标与 $y$ 坐标相加的值相同的点是重叠的。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_agc051_b/cf17bb504667e73875a26607be26bad6c893bba0.png)

令 ```A, B, C, D``` 观察到的大头针数量为 $a, b, c, d$，你需要构造一组大头针的排布，满足以下一些条件：

* $d \geq 10 \times \max\{a, b, c\}$
* 大头钉的数量不多于 $10^5$ 个。
* 大头钉的坐标均为 $[0, 10^9]$ 内的整数。
* 不存在两个坐标相同的大头钉。

没有输入，直接输出一组解。

## 题解

**[更好的阅读体验](https://www.cnblogs.com/User-Unauthorized/p/solutio-AGC051B.html)**

设 $N = 10$，那么满足题目要求的点集一定可以划分为若干集合，其中每个集合内的点 $y$ 坐标相同，且这些集合的平均大小不小于 $N$；类似的，其也可以划分为若干集合，其中每个集合内的点 $x$ 坐标相同，且这些集合的平均大小不小于 $N$。

我们现在考虑观察者 ```A``` 和观察者 ```C```，发现其只有横纵坐标上的限制，故可以取 $N$ 条平行于横轴的直线和 $N$ 条平行于纵轴的直线，取其交点集合。可以发现这样构造的点集一定符合上述集合划分要求。

下面考虑观察者 ```B```，可以发现如果按 $x$ 坐标与 $y$ 坐标相减的值划分点集，那么点 $\left(x, y\right)$ 和点 $\left(x + d, y + d\right)$ 一定在同一集合中，所以取 $N$ 个合适的 $d$ 值，对于上述只考虑观察者 ```A``` 和观察者 ```C``` 所构造出的点集中的每个点 $\left(x, y\right)$，将点 $\left(x + d, y + d\right)$ 也放入最终答案集合。可以发现现在构造出的点集满足观察者 ```A```，```B```，```C``` 观察到的点均为不少于 $N$ 个点重叠在一起的形成的点。

考虑最大化观察者 ```D``` 观察到的点的数量，即最大化 $x$ 坐标与 $y$ 坐标相加的值的数量，随机取上文中的两组直线和 $N$ 个 $d$ 值即可，由于值域很大，所以很少会有冲突的情况。最终答案点的数量为 $N^3$，可以通过本题。

## Code

```cpp
#include <bits/stdc++.h>

typedef int valueType;
typedef std::vector<valueType> ValueVector;

void print(valueType x, valueType y) {
    std::cout << x << ' ' << y << '\n';
}

typedef std::mt19937 Engine;
typedef std::uniform_int_distribution<valueType> Distribution;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    constexpr valueType N = 40, V = 5e8;

    const unsigned int seed = (unsigned int) std::chrono::system_clock::now().time_since_epoch().count();

    std::cout << N * N * N << '\n';

    Engine engine(seed);
    Distribution distribution(0, V);

    ValueVector X(N), Y(N), D(N);

    for (valueType i = 0; i < N; ++i) {
        X[i] = distribution(engine);
        Y[i] = distribution(engine);
        D[i] = distribution(engine);
    }

    for (auto const &x: X)
        for (auto const &y: Y)
            for (auto const &d: D)
                print(x + d, y + d);

    std::cout << std::flush;

    return 0;
}
```

---

