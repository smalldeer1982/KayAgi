# 【MX-X12-T7】「ALFR Round 5」地铁（Easy Version）

## 题目背景

原题链接：<https://oier.team/problems/X12G>。

---

**本题与 Hard Version 的区别在于数据范围和时间限制不同，且本题不需要输出构造方案。本题满分为 $50$ 分。**

## 题目描述

为了方便市民出行，缓解地面上的道路拥堵问题，S 市决定在地底下建一些地铁。

根据城市规划，S 市的地下网络将由 $n$ 条横向通道和 $m$ 条纵向通道构成。地铁站将设置在所有横向通道与纵向通道的交叉处，共 $n\times m$ 处。

地下网络的所有站点都需要被地铁线路覆盖，地铁线路之间可以有重叠部分。

每一条地铁线路都不应「绕路」。如果一条地铁线路，在从其中一个起点站开到终点站的过程中，存在两段列车朝相反方向行驶的平行道路，则我们称这条地铁线路是「绕路」的。

在下图所示的地下网络中，灰线代表地下通道（深灰色的格子为地铁站，即道路交叉处）。红、绿、蓝线所代表的地铁线路没有「绕路」，而黄、橙、紫线所代表的地铁线路「绕路」了。

![](https://cdn.luogu.com.cn/upload/image_hosting/kyzwyen0.png)

此外，地铁线路网必须是连通的。也就是说，无论从哪个地铁站出发乘坐地铁，经过若干次换乘（可以不换乘），都一定可以到达其它所有地铁站。

因为盾构一条地铁线路的流程十分麻烦，S 市不想要建造太多的地铁线路。现在，你知道了 S 市的地下网络大小为 $n\times m$，你想知道 S 市最少要建几条地铁线路。

## 说明/提示

**【样例解释 #1】**

第一组数据的构造方案如下图。要覆盖所有深灰色的交叉路口，至少需要四条地铁线路。

![](https://cdn.luogu.com.cn/upload/image_hosting/ed95ib4j.png?x-oss-process=image/resize,m_lfit,h_450,w_600)

第二组数据的构造方案如下图。要覆盖所有深灰色的交叉路口，至少需要六条地铁线路。

![](https://cdn.luogu.com.cn/upload/image_hosting/h9xxiqum.png?x-oss-process=image/resize,m_lfit,h_680,w_900)

**【数据范围】**

**本题使用捆绑测试。**

对于 $100\%$ 的数据，$1\le T\le10^6$，$1\le n,m\le10^{18}$。

|子任务|分值|$T$|$n,m$|
|:-:|:-:|:-:|:-:|
|$1$|$5$|$T\le10$|$n,m\le10$|
|$2$|$5$|$T\le10$|$n=m\le10^5$|
|$3$|$5$|$T\le10$|$n,m\le10^5$|
|$4$|$5$|$T\le10^3$|$n,m\le10^5$|
|$5$|$10$|$T\le10^3$|$n,m\le10^8$|
|$6$|$20$|$T\le10^6$|$n,m\le10^{18}$|

**本题输入量较大，请使用较快的 I/O 方式。**

## 样例 #1

### 输入

```
2
5 7
9 8```

### 输出

```
4
6```

## 样例 #2

### 输入

```
7
1 1
4 5
1 4
3 3
2 7
114514430240 191981099899
90102 240520```

### 输出

```
1
3
1
2
2
92804190717
80103```

# 题解

## 作者：cff_0102 (赞：17)

### Subtask 1

数据范围很小，可以用很多种方法通过。甚至可以手画所有 $10$ 以内的情况，然后打一份表输出。看起来有 $100$ 种情况，但是实际上真正要画的不是很多。

```cpp
#include<bits/stdc++.h>
using namespace std;
int ans[15][15]={{0},
{0,1,1,1,1,1,1,1,1,1,1},
{0,1,2,2,2,2,2,2,2,2,2},
{0,1,2,2,3,3,3,3,3,3,3},
{0,1,2,3,3,3,4,4,4,4,4},
{0,1,2,3,3,4,4,4,4,5,5},
{0,1,2,3,4,4,4,5,5,5,5},
{0,1,2,3,4,4,5,5,5,6,6},
{0,1,2,3,4,4,5,5,6,6,6},
{0,1,2,3,4,5,5,6,6,6,7},
{0,1,2,3,4,5,5,6,6,7,7}};
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int t;cin>>t;
	while(t--){
		int n,m;cin>>n>>m;
		cout<<ans[n][m]<<"\n";
	}
	return 0;
}
```

你可能想要尝试找规律来通过这题：

斜着读并放到 OEIS 里面搜，可以搜到 A163994，但是实际上本题与 A163994 并不相同。例如 $5\times8$ 的情况，按照 OEIS 上面搜到的数列应该是 $5$，但实际上只用 $4$ 条地铁（下图直接由题目中的图片修改而来）：

![](https://cdn.luogu.com.cn/upload/image_hosting/n9b4kodj.png?x-oss-process=image/resize,m_lfit,h_450,w_600)

把最小的使得 $ans_{n,m}=n$ 的 $m$ 给列出来再放到 OEIS 搜，可以搜到 A002620（$m=\lfloor\dfrac{(n+1)^2}{4}\rfloor$），这个倒是对的。证明放在这篇题解的最后面了，因为需要用到 Subtask 6 中推出的一个式子。不过在 $m$ 小于这个数时显然也不可以通过什么 OEIS 里面的数列快速求出答案了，所以搜了也还是没用。

### Subtask 2

通过手画找规律之类的方法可以得知此时的答案为 $\lceil\dfrac23 n\rceil$。有特殊的构造方法，见 Hard Version 的 Subtask 3。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int t;cin>>t;
	while(t--){
		int n,m;cin>>n>>m;
		cout<<(int)ceil(2.0/3.0*n)<<"\n";
	}
	return 0;
}
```

### Subtask 3

首先，每条线路都只可能是从左上到右下，或者从左下到右上的。设这两种线路的数量分别为 $x,y$。

假设只有一条这样的线路，那么它最多经过 $n+m-1$ 个站点。在理想状态下，每条线路都可以经过 $n+m-1$ 个站点。可惜的是，本题并不理想，两条同向线路会至少在两个交叉口相交（在道路网的两角），两条不同向线路至少会在一个交叉口相交。设“无效点”为因为两条或多条线路相交所以需要在贡献中减去的交叉路口（“无效点”是相对线路而言的，如果一个交叉路口被 $k$ 条线路经过，那么算 $k-1$ 个“无效点”），那么肯定要想办法减少“无效点”的数量。

只考虑一个方向的线路的其中一个角落，在这里放进 $x$ 条线路，求最少会有几个“无效点”。考虑把这些“无效点”从线路中去掉，那么剩下的线路就互不相交。此时不难找到一个安排这些线路的方法：

首先，到左上角的距离为 $0,1,2,\dots$ 的交叉口的数量分别为 $1,2,3,\dots$。每次安排一个新的线路到能到达的最左上角（假设其为 $a$，则到左上角的距离小于 $a$ 的交叉口个数为 $0$），然后往一个方向连出去（此时到左上角的距离大于等于 $a$ 的交叉口个数全部 $-1$），直到安排完 $x$ 条线路。这样可以发现，每条线路删去“无效点”后的起点到左上角的距离分别为 $0,1,2,\dots,x-1$，因此被删掉的“无效点”个数也就是 $\dfrac{x(x-1)}{2}$。再加上右下角，那么从左上到右下的线路之间产生的“无效点”数量就是 $x(x-1)$，同理，左下到右上的线路的“无效点”数量是 $y(y-1)$。

另外别忘了考虑不同向线路交叉产生的 $xy$ 个“无效点”，因此最后实际覆盖的点的数量最多为 $(x+y)(n+m-1)-x(x-1)-y(y-1)-xy$。

原问题就可以转化为：找到最小的 $x+y$，使得 $(x+y)(n+m-1)-x(x-1)-y(y-1)-xy\ge nm$（对于一组满足这个式子的 $(x,y)$，一定可以构造两个方向的地铁数量分别是 $(x,y)$ 的能覆盖所有点的方案，具体见 Hard Version）。推一下这个式子：

$$nm+(x^2+y^2+xy)-(x+y)(n+m)\le0$$
$$xy\ge(x+y)^2-(x+y)(n+m)+nm$$

考虑枚举所有可能的 $x$，然后可以二分得出满足该式的 $y$。时间复杂度 $O(Tn\log n)$（在本题的时间复杂度分析中 $n=\min(n,m)$）。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m;
bool check(long long x,long long y){
	return x*y>=(x+y)*(x+y)-(x+y)*(n+m)+n*m;
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int t;cin>>t;
	while(t--){
		cin>>n>>m;
		int ans=1e9;
		for(int x=0;x<=min(n,m)/2+1;x++){
			int l=1,r=min(n,m);
			while(l<r){
				int mid=(l+r)>>1;
				if(check(x,mid)){
					r=mid;
				}else l=mid+1;
			}
			ans=min(ans,x+l);
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

### Subtask 4

注意到枚举出一个 $x$ 后，剩下的式子只有 $y$ 一个变量，因此可以解出这个一元二次不等式，不需要二分。时间复杂度 $O(Tn)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m;
bool check(long long x,long long y){
	return x*y>=(x+y)*(x+y)-(x+y)*(n+m)+n*m;
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int t;cin>>t;
	while(t--){
		cin>>n>>m;
		long long ans=min(n,m);
		for(long long x=0;x<=min(n,m)/2+1;x++){
			long long b=-(n+m-x),c=n*m-(n+m-x)*x;
			long long y=ceil((-b-sqrt(b*b-4*c))/2);
			ans=min(ans,x+y);
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

### Subtask 5

继续考虑在 Subtask 3 中得到的式子。直接继续推这个式子是推不下去的。但是不难发现，当 $x+y$ 已经确定时，要让式子前面的 $xy$ 尽量大，这个不等式才能尽量满足。因为两数和一定时，它们的差越小，乘积越大，所以 $x,y$ 要尽量接近。由此可以推出：无论如何，取 $x,y$ 最接近的解一定不劣。

因此，可以二分最终的答案 $ans$，那么 $x=\lfloor\dfrac{ans}2\rfloor,y=s-x$。时间复杂度 $O(T\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m;
bool check(long long s){
	__int128 x=s/2,y=s-x;
	return x*y>=(x+y)*(x+y)-(x+y)*(n+m)+(__int128)n*m;
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int t;cin>>t;
	while(t--){
		cin>>n>>m;
		long long l=1,r=min(n,m);
		while(l<r){
			long long mid=(l+r)>>1;
			if(check(mid)){
				r=mid;
			}else l=mid+1;
		}
		cout<<l<<"\n";
	}
	return 0;
}
```

### Subtask 6

我们可能需要在 $O(1)$ 的时间内计算出每组数据的答案。先假设 $x,y$ 可以是任意实数。由于取 $x,y$ 最接近的解一定不劣，因此不妨设 $x=y$。那么可以推出：

$$nm+3x^2-2x(n+m)\le0$$
$$3x^2-2(n+m)x+nm\le0$$

目标是要让原式中的 $x+y$ 尽量小，所以这个式子中的 $x$ 要尽量小。这是一个一元二次不等式，可以直接求出满足该式的 $x$ 最小值：

$$\begin{aligned}x_{\min}&=\dfrac{2(n+m)-\sqrt{4(n+m)^2-12nm}}{6}\\
&=\dfrac{(n+m)-\sqrt{n^2+m^2-nm}}{3}\end{aligned}$$

因此，当 $x=y$ 时，$(x+y)_{\min}=2x_{\min}=2\times\dfrac{(n+m)-\sqrt{n^2+m^2-nm}}{3}$。

考虑回现实情况，$x,y$ 需要是整数。不管怎么样，必须满足 $ans=x+y\ge2\times\dfrac{(n+m)-\sqrt{n^2+m^2-nm}}{3}$。于是就可以得出答案：

$$ans=\lceil2\times\dfrac{(n+m)-\sqrt{n^2+m^2-nm}}{3}\rceil$$

如果 $ans=\lceil2x\rceil$ 是偶数，那么可以取 $ansx=ansy=\lceil x\rceil$。根据前面的计算，这组 $(x,y)$ 显然是满足前面推出的不等式的。因此，此时计算出来的 $ans$ 没有问题。

但是，$ans$ 是在 $x=y$ 的前提下推出来的，在 $x=y+1$ 的情况下有没有可能不满足上面的不等式呢？

若 $ans$ 为奇数，那么设其为 $2k+1$，则 $k<\dfrac{(n+m)-\sqrt{n^2+m^2-nm}}{3}\le k+\dfrac12$（因为它的两倍在 $2k$ 和 $2k+1$ 之间）。首先，因为按照 $x=y$ 计算出来的 $x$ 的解大于 $k$，因此不存在 $2k$ 的答案，最终答案必然大于等于 $2k+1$。其次，因为按照 $x=y$ 计算出来的 $x$ 的解小于等于 $k+\dfrac12$，所以（如果 $x,y$ 可以是任意实数的话）$x=y=k+\dfrac12$ 满足前面推出的式子 $xy\ge(x+y)^2-(n+m)(x+y)+nm$，即 $k^2+k+\dfrac14\ge4k^2+4k+1-(n+m)(2k+1)+nm$。

如果 $ans$ 是奇数时不一定是正确答案，那么说明 $x=k,y=k+1$ 可能不满足 $xy\ge(x+y)^2-(n+m)(x+y)+nm$（前面说要满足该式最好尽量让 $x,y$ 接近，而这就是 $x,y$ 最接近的一组整数解）。假设它不满足，那么代入 $x,y$ 的值，可以列出：

$$\left\{\begin{aligned}&k^2+k+\dfrac14\ge4k^2+4k+1-(n+m)(2k+1)+nm\\&k^2+k<4k^2+4k+1-(n+m)(2k+1)+nm\end{aligned}\right.$$

对于下式，其左右侧必然都是整数。因此下式右侧的 $4k^2+4k+1-(n+m)(2k+1)+nm$ 应该大于等于 $k^2+k+1$。然而，根据上式，它又要小于等于 $k^2+k+\dfrac14$，矛盾。因此“$ans$ 是奇数时它并不是正确答案”的情况不存在。所以 $ans$ 是奇数时，答案也是 $\lceil2\times\dfrac{(n+m)-\sqrt{n^2+m^2-nm}}{3}\rceil$。

（其实不放心的话还可以算出 $ans$ 之后拿附近的 $x$ 和 $y$ 验证一下然后输出符合条件的 $x+y$ 最小的答案）

为了避免精度误差，计算出答案 $ans$ 时，可以再验证一遍 $ans-1,ans,ans+1$ 是否满足条件，然后输出最小的满足条件的那个数。`sqrtl` 的复杂度可以看成 $O(1)$，总时间复杂度 $O(T)$。

我们只证明了答案至少为这个数，要证明一定有对应的方案，还需要将其构造出来。不过不进行构造证明直接输出答案就能获得本题的 $50$ 分了。构造方案见 Hard Version。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m;
bool check(__int128 s){
	__int128 x=s/2,y=s-x;
	return x*y>=(x+y)*(x+y)-(x+y)*((__int128)n+m)+(__int128)n*m;
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int t;cin>>t;
    while(t--){
		cin>>n>>m;
		long long ans=ceil(2*(n+m-sqrtl((__int128)n*n+(__int128)m*m-(__int128)n*m))/3);
		if(check(ans-1))cout<<ans-1<<"\n";
		else if(check(ans))cout<<ans<<"\n";
		else cout<<ans+1<<"\n";
	} 
	return 0;
}
```

这里的 `__int128` 也可以改成 `long double`。

附对于 Subtask 1 部分提到的 $m\ge\lfloor\dfrac{(n+1)^2}{4}\rfloor$ 时答案即为 $n$ 的证明：

$$\begin{aligned}&\lceil2\times\dfrac{(n+m)-\sqrt{n^2+m^2-nm}}{3}\rceil=n\\\Longleftrightarrow\ &\dfrac23\times(n+m-\sqrt{n^2+m^2-nm})>n-1\\\Longleftrightarrow\ &m-\dfrac12n+\dfrac32>\sqrt{n^2+m^2-nm}\\\Longleftrightarrow\ &m^2+\dfrac14n^2+\dfrac94-nm+3m-\dfrac32n>n^2+m^2-nm\\\Longleftrightarrow\ &4m>n^2+2n-3\\\Longleftrightarrow\ &m>\dfrac{(n+1)^2}{4}-1\\\Longleftrightarrow\ &m\ge\lfloor\dfrac{(n+1)^2}{4}\rfloor\end{aligned}$$

---

一些关于这两题的 fun facts：

1. 本题来源于我两年前的灵感。当时我画了 $10$ 以内的 $n=m$ 的情况，发现了 $ans=1,2,2,3,4,4,5,6,6,\dots$ 的规律，即 Subtask 1（不过没发现 Subtask 5 的通用构造方法）。
2. 本题的线路不能「绕路」，实际上灵感来源于游戏「跳舞的线」，~~其实也有一些对某些城市地铁线路拐来拐去，交而不换的吐槽~~。
3. 这题刚出出来的时候，我认为这题的难度与 [CSP-J 2022 T2](/problem/P8814) 相差不大，因为那题也是解一元二次。
4. 分成两个 Version 的想法是在组题的时候才有的，原本这题只有 Easy Version。
5. Easy Version 样例中的倒数第二组数据是 `sqrtl` 会出现精度误差的数据，最后一组输入有意义且满足 $ans=n-9999$。

---

## 作者：Jorisy (赞：1)

太深刻了。

首先为了最大化一条线的覆盖点数，一定会选择从角开始，到角结束。这样就有**左上到右下**，**左下到右上**两类，两类的线条数分别设为 $x,y$，而且显然有 $x\le n,y\le m$，再多的线没必要。

显然对于每条线都会过 $n+m-1$ 个点，考虑去掉被多次覆盖的点。并且我们尝试最小化去掉的点的数量。

去掉的点分为两类，一类是**同类线**的多次覆盖，一类是**不同线**。

对于第一种情况，考虑左上角部分。到左上角的曼哈顿距离为 $t(t\le x)$ 的点的个数显然为 $t+1$。为了最小化交点数，这 $x$ 条线在此时至少也会有 $x-t$ 次重复覆盖。这样的话左上角的一块要去掉 $(x-1)+(x-2)+\cdots+2+1=\dfrac{(x-1)x}2$。其余四个角同理。总的数为 $x(x-1)+y(y-1)$。

考虑不同类的，必然会有至少一次相交，因此就有至少 $xy$。

故可以列出不等式：
$$
(n+m-1)(x+y)-x(x-1)-y(y-1)-xy\ge nm
$$
整理得：
$$
(x+y-m)(x+y-n)\le xy
$$
然后我们就要求 $\min\{x+y\}$。

下面我们先认为 $x,y\in\mathbb R_+$。

> 引理：$x=y\Leftrightarrow x+y\to\min$。

**充分性**的证明是，如果 $x+y$ 确定，根据基本不等式，那么 $x,y$ 越接近，$xy$ 越大，于是这个限制越宽松，故 $x=y$ 必然不会更劣。

这个题只要充分性就够了，但是这里可以证一下**必要性**。

将 $x,y$ 看作横纵坐标。如果这东西成立的话，就是说最小值在的坐标离原点最近，并且在直线 $y=x$ 上。

考虑将坐标系逆时针旋转 $\theta=45\degree$，则有新坐标 $(x',y')$ 满足关系式：

$$
\begin{cases}x=x'\cos\theta+y'\sin\theta=\dfrac{\sqrt2}2(x'+y')\\y=-x'\sin\theta+y'\cos\theta=\dfrac{\sqrt2}2(y'-x')\end{cases}
$$

代入不等式，有：

$$
\begin{aligned}
(x+y-m)(x+y-n)&\le xy\\
(\sqrt2y'-m)(\sqrt2y'-n)&\le\dfrac12(x'+y')(y'-x')\\
4(y')^2-2\sqrt2(n+m)y'+2nm&\le(y')^2-(x')^2\\
(x')^2+3(y')^2-2\sqrt2(n+m)y'-2nm&\le0\\
(x')^2+3\left(y'-\dfrac{\sqrt2}3(n+m)\right)^2&\le\dfrac23(n+m)^2+2nm
\end{aligned}
$$

发现这东西是一个中心在 $\left(0,\dfrac{\sqrt2}3(n+m)\right)$ 的椭圆。其下顶点离原点最近，并且是**唯一**的。

必要性就证完了。

---

这样就有一元二次不等式：

$$
3x^2-2(n+m)x+mn\le 0
$$

并且要最小化 $x$。

于是可以解得：

$$
\begin{aligned}
x_{\min}&=\dfrac{n+m-\sqrt{n^2+m^2-mn}}3
\end{aligned}
$$


故 $(x+y)_{\min}=2x_{\min}=\dfrac23(n+m-\sqrt{n^2+m^2-mn})$。

考虑如果 $x,y\in\mathbb N_+$ 要怎么取。

把这东西放到图像上，刚才我们已经知道图像是一个椭圆旋转 $45\degree$ 得到的了。

实数当然是取 $x=y$，那么整数要怎么取呢？

考虑极值的位置，只会是下面两种（$A,C$ 所在直线为 $y=x$）：

![](https://cdn.luogu.com.cn/upload/image_hosting/qpl6zhu4.png)

对于这种，我们仍然取 $x=y$，答案为 $\left\lceil\dfrac23(n+m-\sqrt{n^2+m^2-mn})\right\rceil$。

![](https://cdn.luogu.com.cn/upload/image_hosting/p6km1smo.png)

这种情况，点 $B,D$ 的位置比点 $C$ 优，也就是要取 $y=x\pm1$。而我们最终答案仍然为 $\left\lceil\dfrac23(n+m-\sqrt{n^2+m^2-mn})\right\rceil$，这恰好是直线 $BD$ 的截距，不会跑到点 $A,C$ 上去，因此不会变劣。

于是就做完了。

最后开根的时候注意精度问题。

---

## 作者：BennyT (赞：1)

# P12424 【MX-X12-T7】「ALFR Round 5」地铁（Easy Version） 题解
## 思路
首先可以发现一个很显然的性质，地铁的线路一定是从左上到右下或从右上到左下的，我们将从左上到右下的线路数量设为 $x$，从左下到右上的线路数量设为 $y$，则答案即为 $x+y$。

我们可以先计算线路最多可以覆盖的点数。我们设线路交叉的点为无效点，数量为 $w$，每一个无效点都会使覆盖的点数 $-1$，因为线路的最长长度为 $n+m-1$，所以最多可以覆盖的点数为 $(x+y)(n+m-1)-w$。

接下来我们来计算 $w$，一共有两种，分别是方向不同的线路的交叉和同向线路在起点的交叉。

#### 第一种情况

没啥好说的，就是 $xy$。

#### 第二种情况

以左上角为例，让我们来画个图（图中为方便演示将点画成网格），在图中标上每个点至左上角的距离。

![](https://cdn.luogu.com.cn/upload/image_hosting/6b78zzcs.png)

可以发现当距离左上角距离为 $p$ 的点有 $p+1$ 个。

为了减少无效点，每条线路的起始点应该离四角最近来覆盖尽可能多的点。

![](https://cdn.luogu.com.cn/upload/image_hosting/i5cn05zl.png)

这是我们发现从左上角出发的点每走一步都会走到距离 $+1$ 的点上，所以所有距离 $\ge 0$ 的点的数量都会 $-1$，则第 2 条线路最多只能选择距离左上角距离为 1 的点作为起始点，会产生 1 个无效点，第 3 条线路最多只能选择距离左上角距离为 2 的点作为起始点，会产生 2 个无效点，以此类推，第 $i$ 条线路最多只能选择距离左上角距离为 $i-1$ 的点作为起始点，会产生 $i-1$ 个无效点，则在左上角最少会产生 $0+1+2+3+...+x-1$ 个无效点，即 $\frac{x(x-1)}{2}$ 个无效点，算上右下角共有 $x(x-1)$ 个无效点，再加上从左下到右上的线路所产生的无效点数，该情况所产生的无效点数为 $x(x-1)+y(y-1)$。

综上所述，$w=xy+x(x-1)+y(y-1)$，最多可以覆盖 $(x+y)(n+m-1)-xy-x(x-1)-y(y-1)$ 个点，化简得 $xy\ge(x+y)^2-(x+y)(n+m)-nm$。

经过一系列计算得最终答案 $ans$ 为 $\lceil 2 \times \frac{n+m-\sqrt{n^2+m^2-nm}}{3} \rceil$，具体计算过程在[cff_0102](https://www.luogu.com.cn/user/542457)的题解中已详细给出，此处不再过多赘述。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128 lll;
ll t,n,m;
bool f(lll u){
	lll x=u/2,y=u-x;
	return (lll)x*y>=(lll)(x+y)*(lll)(x+y)-(lll)(x+y)*(lll)(n+m)+(lll)n*m;
}
ll print(){
	ll ans=ceil(2ll*((lll)n+(lll)m-sqrtl((lll)n*n+(lll)m*m-(lll)n*m))/3ll);//计算ans 
	if(f(ans-1ll))return ans-1;//防止精度问题 
	else if(f(ans))return ans;
	else return ans+1; 
	
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>t;
	while(t--){
		cin>>n>>m;
		cout<<print()<<'\n';
	} 
	return 0;
}


```

---

