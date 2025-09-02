# Vasya and Cornfield

## 题目描述

Vasya owns a cornfield which can be defined with two integers $ n $ and $ d $ . The cornfield can be represented as rectangle with vertices having Cartesian coordinates $ (0, d), (d, 0), (n, n - d) $ and $ (n - d, n) $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1030B/104e0bfeaf07ab93dff4c549bd13618b0eb766eb.png)An example of a cornfield with $ n = 7 $ and $ d = 2 $ .Vasya also knows that there are $ m $ grasshoppers near the field (maybe even inside it). The $ i $ -th grasshopper is at the point $ (x_i, y_i) $ . Vasya does not like when grasshoppers eat his corn, so for each grasshopper he wants to know whether its position is inside the cornfield (including the border) or outside.

Help Vasya! For each grasshopper determine if it is inside the field (including the border).

## 说明/提示

The cornfield from the first example is pictured above. Grasshoppers with indices $ 1 $ (coordinates $ (2, 4) $ ) and $ 4 $ (coordinates $ (4, 5) $ ) are inside the cornfield.

The cornfield from the second example is pictured below. Grasshoppers with indices $ 1 $ (coordinates $ (4, 4) $ ), $ 3 $ (coordinates $ (8, 1) $ ) and $ 4 $ (coordinates $ (6, 1) $ ) are inside the cornfield.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1030B/e5639eb53ffd6809c606315deea176befa06452d.png)

## 样例 #1

### 输入

```
7 2
4
2 4
4 1
6 3
4 5
```

### 输出

```
YES
NO
NO
YES
```

## 样例 #2

### 输入

```
8 7
4
4 4
2 8
8 1
6 1
```

### 输出

```
YES
NO
YES
YES
```

# 题解

## 作者：AnicoderAndy (赞：3)

## 前置知识
平面直角坐标系、一次函数及其性质(应该是八年级上学期知数学识点，没学过的请自行查询资料)、等腰三角形的三线合一、矩形的性质。

## 思路
首先，平面直角坐标系内有两条直线非常特殊，它们是$y=x$和$y=-x$，它们分别是一三象限和二四象限的角平分线。而与它们平行的线，即$y=x+b$和$y=-x+b$，也非常特殊。

1. 记$y=x+b$与X轴交于(m,0)，与Y轴交于(0,n)，不难发现，$-m=n=b$。如图所示，$b=1$的情况。
![y=x+1](https://cdn.luogu.com.cn/upload/pic/60966.png)


1. 同样的，记$y=-x+b$与X轴交于(m,0)，与Y轴交于(0,n)，不难发现，$m=n=b$。如图所示，$b=1$的情况。
![y=-x+1](https://cdn.luogu.com.cn/upload/pic/60967.png)

再反观题设中的坐标$A(0,d)$,$B(d,0)$,$C(n,n-d)$,$D(n-d,n)$，不难发现，直线$AB$就是$y=-x+d$；

![题目中的图](https://cdn.luogu.com.cn/upload/pic/60968.png)

既然$AD$垂直于$AB$，那么直线$AD$的$k$值就为1，又因为它与Y轴交于$(0,d)$，所以易得它的解析式就为$y=x+d$。

再看$BC$⊥$AB$，所以直线$BC$的$k$值就为1，又因为它与X轴交于$(d,0)$，由我们刚刚提到的第1点说到的“$-m=n=b$”，在这里就可以得到该直线$b$的值为$-d$，所以直线$y=x-d$。

最后一条直线，我们可以把它延长，与X轴交于$E$，得到这个。

![垃圾画图软件](https://cdn.luogu.com.cn/upload/pic/60973.png)

因为$y=-x$是二四象限的角平分线，所以∠1=45°，又因为$y=-x+b$与$y=-x$互相平行，所以∠2=45°，易证△$BCE$是等腰直角三角形。又因为$CF$⊥$BE$，所以$FE=FB$。再由$B$、$C$的坐标求出$BF=n-d$，所以$BE=2n-2d$，易得$E((2n-2d)+d,0)$，即$(2n-d,0)$。由我们刚刚提到的第2点说到的“$m=n=b$”得到$b=2n-d$，所以直线为$y=-x+2n-d$。

那么给定的一个点$(a,b)$，只需要保证这个点在直线$y=-x+d$、$y=-x+2n-d$上或者上方，在直线$y=x-d$、$y=x+d$上或者下方，即

![公式](https://cdn.luogu.com.cn/upload/pic/60985.png)

就可以保证它在矩形内。

## 代码实现
```cpp
#include <iostream>
using namespace std;
int main()
{
    int d, n, m;
    cin >> n >> d >> m;

    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;

        if (b <= a + d && b >= a - d && b >= -a + d && b <= -a - d + 2 * n) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}
```

---

## 作者：KagurazakaKano (赞：2)

很好的一个解析几何题目！

题目大意：给定一个$n * n$的范围以及一个数字$d$，再给定$m$个点，要你求这$m$个点是否分别在 $(0,d),(d,0),(n,n - d)(n - d,n)$ 围成的范围里。

解析：真的是一道好题！

我们考虑先求出这四条直线的解析式。首先是过 $(0,d),(d,0)$ 的：$k = \frac{d - 0}{0 - d} = -1$，$b = d$。于是乎 $y= - x+d$ 推出 $x + y = d$。

过 $(0,d),(n - d,n)$ 的：$k = \frac{d - n}{0 - (n - d)} = 1$，$b = d$，于是乎 $y = x + d$ 推出 $x - y = -d$。

 过$(n - d,n), (n, n - d)$的：$k = \frac{n - (n - d)}{(n - d) - n} = -1$，$b = -2n + d$，于是乎 $y = - x - 2n + d$ 推出 $x - y = 2n - d$。

过$(d,0), (n, n - d)$的：$k = \frac{0 - (n - d)}{d - n} = 1$，$b = -d$，于是乎 $y = x - d$ 推出 $x - y = d$。

此时我们再考虑如何判断这些点是否在里面即可。

于是乎问题转化成一个线性规划问题。

即：给定 $4$ 条直线，求给定的点是否是在这四个点围成的矩形中。

于是只要满足：

$$ d \leq x + y$$
$$x + y \leq 2n - d $$
$$-d \leq x - y$$
$$ x - y \leq d$$

即可。

```cpp
#include <bits/stdc++.h>

using namespace std;

int main(){
	int n,d;
	scanf("%d%d",&n,&d);
	int m;
	scanf("%d",&m);
	for(int i = 1; i <= m; i++){
		int x, y;
		scanf("%d%d",&x,&y);
		if((x + y >= d) && (x + y <= (2 * n - d)) && (x - y >= -d) && (x - y) <= d){
			printf("YES\n");
		} else {
			printf("NO\n");
		}
	}
	return 0;
}
```

---

## 作者：qingchenMC (赞：1)

## 题目大意

给定一个矩形的四个顶点坐标，求一些点是不是在这个矩形内。

## 解法

想要判断一个点是不是在给定矩形内，可以求出这个矩形四条边的函数解析式，再依次判断这个点是不是在上面两条边的下面和下面两条边的上面即可。

好吧，这么说好像不太容易明白，我来画个图解释一下。

![](https://cdn.luogu.com.cn/upload/image_hosting/yb6xjuli.png)

有对钩的区域代表它们在对应颜色的线的下（上）方。此时我们发现，唯一一个有四种颜色对钩的区域就是这个矩形。因此，如果一个点满足四条边的判定，那么他一定在矩形内部。

而在矩形边上的情况，我们只需要在判断时加上一个等于号即可。

判断一个点在一个一次函数上方还是下方也很简单，只需要将他的横坐标代入解析式，求出对应的纵坐标，再拿这个坐标与这个点的纵坐标进行比较即可。

于是下面的问题转换为：求这四条边的函数解析式。

这一步也不难，因为四个点的坐标都已经给定了，只需设然后解即可。仅需一点初一的方程与函数知识即可。

最后解出来：

左下边：$y=-x+d$

右下边：$y=x-d$

左上边：$y=x+d$

右上边：$y=-x+2N-d$

所以符合条件的点 $(x,y)$ 满足：

$$$ \left\{
\begin{aligned}
y&\ge-x+d\\
y&\ge x-d\\
y&\le x+d\\
y&\le -x+2N-d
\end{aligned}
\right.$$$

输入一组 $(x,y)$ 后，判断即可。

## 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

int main(){
	int n,d,m;
	cin>>n>>d>>m;
	for(int i=1;i<=m;i++){
		int x,y;
		cin>>x>>y;
		if(y>=(-x+d)&&y>=(x-d)&&y<=(x+d)&&y<=(-x+2*n-d)){
			cout<<"YES"<<endl;
		}
		else{
			cout<<"NO"<<endl;
		}
	}
	return 0;
}
```
[AC](https://codeforces.com/contest/1030/submission/308614189)

---

## 作者：FurippuWRY (赞：1)

先求出此图形四条边的函数解析式。

因为四边都是直线，所以解析式都是一次函数，按照求一次函数解析式的方法做就行了。

如图，设四边形的四个顶点分别为 $A$、$B$、$C$、$D$，四条边的分别对应一次函数 $AD=f(x)$、$DC=g(x)$、$CB=h(x)$、$AB=i(x)$。

![](https://cdn.luogu.com.cn/upload/image_hosting/oeeeky83.png)

根据公式，斜率 $k=\dfrac{y_{1}-y_{2}}{x_{1}-x_{2}}$，截距 $b=y-kx$ 可得：

$$
\begin{aligned}
&f(x)=x+d\\
&g(x)=-x+2n-d\\ 
&h(x)=x-d\\
&i(x)=-x+d\\
\end{aligned}
$$  
如果一个点 $P(x_{0},y_{0})$ 要在这个四边形内部，那么：

$$
\begin{cases}
y_0\le f(x_0)\\
y_0\le g(x_0)\\
y_0\ge h(x_0)\\
y_0\ge i(x_0)\\
\end{cases}
$$

稍微变换一下，可以得到：

$$
\begin{cases}
x_0 - y_0\le d\\
x_0 + y_0\le 2n-d\\
x_0 - y_0\ge -d\\
x_0 + y_0\ge d\\
\end{cases}
$$

总之，只要这个点的坐标满足上述四个不等式，那么这个点就在四边形里。

# Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, d, x, y, k;
int main() {
	cin >> n >> d >> k;
	while (k--) {
		cin >> x >> y;
		if (x + y >= d && 
		    x + y <= 2 * n - d && 
		    x - y >= -d && 
		    x - y <= d) cout << "YES\n";
		else cout << "NO\n";
    }
	return 0;
}
```

---

## 作者：nb_jzy (赞：0)

# 题意
- 给你一个矩形，让你判断询问的点是否被这个矩形包含。

# 思路

看见大家都推了解析式，但我比赛时看见 $1\le d<n\leq 100$ 与 $1\le m\leq 100$ 时。~~这不妥妥的暴力吗~~。

确实，我是暴力做的，但同时有又包含了一点小思维。

首先，矩形有四条边，这点毫无问题，但经过观察，我们会发现：**每个在矩阵内部的点**，他们**向上下左右四个方向拓展**，最终**都会分别碰到四条边**。

于是，这就是我的思路。

# 做法
根据我们的思路，先把在四条边上的点标记出来。

于是，我们就可以暴力分别拓展被询问的点。如果**上下左右四个方向**都遍历到了被标记过的点，当前点对就一定在矩形的内部了。

时间复杂度 $\mathcal{O} (n\times m)$，不如其他人的 $\mathcal{O}(1)$，但是很好理解。

# 代码

就是几个循环。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,d,x,y,m;
bool a[105][105];
int main(){
    scanf("%d%d",&n,&d);
    for(int i=0,j=d;i<=d&&j>=0;i++,j--){
        a[i][j]=1;
    }
    for(int i=n-d,j=n;i<=n&&j>=n-d;i++,j--){
        a[i][j]=1;
    }
    for(int i=0,j=d;i<=n-d&&j<=n;i++,j++){
        a[i][j]=1;
    }
    for(int i=d,j=0;i<=n&&j<=n-d;i++,j++){
        a[i][j]=1;
    }//标记在四条边上的点
    scanf("%d",&m);
    for(int j=1;j<=m;j++){
        scanf("%d%d",&x,&y);
        bool f1=0,f2=0,f3=0,f4=0;
        for(int i=x;i>=0;i--){
            if(a[i][y]) f1=1;
        }
        for(int i=x;i<=n;i++){
            if(a[i][y]) f2=1;
        }
        for(int i=y;i<=n;i++){
            if(a[x][i]) f3=1;
        }
        for(int i=y;i>=0;i--){
            if(a[x][i]) f4=1;
        }
        if(f1&&f2&&f3&&f4){//是否都能拓展到边上的点。
            cout<<"YES"<<endl;
        }
        else{
            cout<<"NO"<<endl;
        }
    }
}
```

---

## 作者：knsg251 (赞：0)

## 题目意思
给出四个点，组成一个长方形，接下来问 $(x,y)$ 这个点是否在长方形内部。
## 题目分析
这其实就是一道函数题，长方形的每条边可以看做一个解析式。

以下是求出的四个解析式：
*	$y=-x+d$
*	$y=-x+2n-d$
*	$y=x-d$
*	$y=x+d$

接下来就是直接判断然后输出即可。

四个判断：

*	$b\ge-a+b$
*	$b\ge-a+2n-d$
*	$b\le a-d$
*	$b\le a+d$

## 代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,d,a,b;
int main(){
    cin>>n>>d;
    cin>>m;
    for(int i=1;i<=m;i++){
    	scanf("%d%d",&a,&b);//输入 
        if(a - b >= -d && a - b <= d && a + b >= d && a + b <= - d + 2 * n){//四个判断 
        	printf("YES\n");//满足就是在长方形内部，就输出YES
        }else{
            printf("NO\n");//不满足就输出NO
        }
    }
    return 0;//over
}
```

---

## 作者：Fraction (赞：0)

这里是暴力选手。

不会算数的人的福音。

不过说实话，就是这题，把我的$D$坑没了

其实这题当模拟还挺不错的啊。

```cpp
#include <bits/stdc++.h>
#define fp(i, l, r) for(register int i = (l); i <= (r); ++i)
#define fd(i, l, r) for(register int i = (l); i >= (r); --i)
#define full(a, b) memset(a, b, sizeof(a))
#define ll long long
#define il inline
using namespace std;

template <typename T> il void read(T &dig) {
	dig = 0;
	bool flag = false;
	char c = getchar();
	while(!isdigit(c) && c != '-') c = getchar();
	if(c == '-') flag = true, c = getchar();
	while(isdigit(c)) dig = dig * 10 + c - '0', c = getchar();
	if(flag) dig = -dig;
}

const int MAXN = (int)1e2 + 5;

int n, d, m;
int rope[MAXN][MAXN];

il bool get(int x, int y) {
	if(rope[x][y] == 1) return true;
	int px = x, py = y;
	bool l1 = false, l2 = false, r1 = false, r2 = false;
	while(px <= n) {
		if(rope[px][y] == 1) l1 = true;
		++px;
	}
	while(py <= n) {
		if(rope[x][py] == 1) r1 = true;
		++py;
	}
	px = x, py = y;
	while(px >= 0) {
		if(rope[px][y] == 1) l2 = true;
		--px;
	}
	while(py >= 0) {
		if(rope[x][py] == 1) r2 = true;
		--py;
	}
	if(l1 && l2 || r1 && r2) return true;
	else return false;
}

il void init() {
	full(rope, 0);
	scanf("%d%d%d", &n, &d, &m);
	int x_1 = d, x_2 = 0;
	while(d-x_2 >= 0) {
		rope[x_2][d-x_2] = 1;
		++x_2;
	}
	while(x_1 <= n) {
		rope[x_1][x_1-d] = 1;
		++x_1;
	}
	x_1 = n, x_2 = d;
	while(x_2 <= n) {
		rope[x_2-d][x_2] = 1;
		++x_2;
	}
	while(x_1 >= n-d) {
		rope[n+n-d-x_1][x_1] = 1;
		--x_1;
	}
//	fp(i, 0, n) {
//		fp(j, 0, n) {
//			printf("%d ", rope[i][j]);
//		}
//		cout << endl;
//	}
}

il void solve() {
	int a, b;
	fp(i, 1, m) {
		read(a), read(b);
		bool flag = get(a, b);
		if(flag == false) printf("NO\n");
		else printf("YES\n");
	}
}

int main() {
	init();
	solve();
	return 0;
}
```

---

