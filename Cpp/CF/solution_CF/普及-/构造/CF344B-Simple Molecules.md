# Simple Molecules

## 题目描述

Mad scientist Mike is busy carrying out experiments in chemistry. Today he will attempt to join three atoms into one molecule.

A molecule consists of atoms, with some pairs of atoms connected by atomic bonds. Each atom has a valence number — the number of bonds the atom must form with other atoms. An atom can form one or multiple bonds with any other atom, but it cannot form a bond with itself. The number of bonds of an atom in the molecule must be equal to its valence number.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF344B/e6377325271b4515d315f9767d5c5b94bf56f174.png)Mike knows valence numbers of the three atoms. Find a molecule that can be built from these atoms according to the stated rules, or determine that it is impossible.

## 说明/提示

The first sample corresponds to the first figure. There are no bonds between atoms 1 and 2 in this case.

The second sample corresponds to the second figure. There is one or more bonds between each pair of atoms.

The third sample corresponds to the third figure. There is no solution, because an atom cannot form bonds with itself.

The configuration in the fourth figure is impossible as each atom must have at least one atomic bond.

## 样例 #1

### 输入

```
1 1 2
```

### 输出

```
0 1 1
```

## 样例 #2

### 输入

```
3 4 5
```

### 输出

```
1 3 2
```

## 样例 #3

### 输入

```
4 1 1
```

### 输出

```
Impossible
```

# 题解

## 作者：Dws_t7760 (赞：5)

我们首先阅读一下题意。

有一个具有三个顶点的无向图，给出每个顶点的度（即与这个顶点相连的边的数目）

如果有一种连接边的方式，使得每个顶点的度都等于给出的数字，请输出这种方案：

输出格式：

- 输出共 $1$ 行，三个整数，用空格分开；

- 三个整数分别为第 $1$ 和第 $2$，第 $2$ 和第 $3$，第 $3$ 和第 $1$ 顶点之间的边数；

否则输出 `Impossible`。

通过观察题目描述中的图片，我们可以得到如下两个结论：

1. 一个具有三个顶点的无向图的边的数量，等于所有顶点的度之和除以二。

2. 在一个具有三个顶点的无向图中，任意两个顶点之间的边数为这个无向图中边的总数和另外一个顶点的度之差。

所以我们可以得出，在如下两种情况中没有连接方案：

1. 得出的无向图的边数不是整数。

2. 存在有一个顶点的度数大于无向图的边数。

根据这些结论，我们不难写出代码。

代码如下：

```cpp
#include<iostream>
using namespace std;
int a,b,c,s,s12,s23,s13;
int main() {
	cin>>a>>b>>c;
	if((a+b+c)%2) {
	    cout<<"Impossible";
	    return 0;
	}
	s=(a+b+c)/2;
	s12=s-c,s23=s-a,s13=s-b;
	if(s12<0||s23<0||s13<0) cout<<"Impossible";
	else cout<<s12<<' '<<s23<<' '<<s13;
	return 0;
}
```


---

## 作者：abensyl (赞：2)

## [原题传送门](https://www.luogu.com.cn/problem/solution/CF344B)

## 题面翻译

有一个具有三个顶点的无向图，给出每个顶点的度（即与这个顶点相连的边的数目）

如果有一种连接边的方式，使得每个顶点的度都等于给出的数字，请输出这种方案：

输出格式：

- 输出共 $1$ 行，三个整数，用空格分开；

- 三个整数分别为第 $1$ 和第 $2$ ，第 $2$ 和第 $3$ ，第 $3$ 和第 $1$ 顶点之间的边数；

否则输出 `Impossible`。

## 思路

~~一看到这个题，就知道是暴力枚举~~

>1. 先读入三个数 $x$, $y$, $z$
>2. 暴力枚举找到一个合适的值 $i$ ，使得 $x+y=z+i \times 2$
>3. 找到以后输出并结束全程序
>4. 找不到输出 Impossible

## 代码：
```
#include <bits/stdc++.h>
using namespace std;
int x,y,z;
int main() {
    scanf("%d%d%d",&x,&y,&z); 
    for (int i=0;i<=min(x,y);++i) //枚举i的值，直到i大于x,y中的任意一个
        if (x+y==z+i*2) { //判断是否满足条件
        	printf("%d %d %d\n",i,y-i,x-i); //如果满足，就输出
            return 0; //然后直接结束全程序
		}
    puts("Impossible"); //查找结束，没有找到满足条件的，输出Impossible
    return 0; 
}
```

### [AC记录](https://www.luogu.com.cn/record/78066449)

---

## 作者：20111019Yu (赞：2)

首先阅读一下题意，我们不难发现，这是一道数学题，但在开始解题之前，我们先把错误的情况排除。

1. 因为一条边有且只有两个端点，所以如果 $(a+b+c)\equiv1\pmod{2}$，则奇偶性不同，不可能。

1. 若两点的的度之和小于另一个点的度，则也不可能，因为每个点最多连一条边，两个点连的边就算都连另一个点，那个点的度也达不到，所以这种情况也不可能。

现在剩下的数据就都是可行的了。

## 证明：


每个点因为不能连自环，所以只能连另外两个点，所以每个点的度为这个点连的边数。

现在选择一个点，假如是点 $1$，则设 $a=e+d$，$e$ 为点 $1$ 连接点 $2$ 的边数，$d$ 为点 $1$ 连接点 $3$ 的边数。

又因点 $2$ 连接点 $3$ 的边的端点数必须一样，所以 $b-e=c-d$。

将 $b-e$ 与 $c-d$ 相加，等于 $b+c-e-d=b+c-a$ 答案为点 $2$ 与点 $3$ 之间的连边数乘 $2$。

所以 $\frac{b+c-a}{2}$ 就为点 $2$ 与点 $3$ 之间的连边数。

同时点 $1$ 与点 $2$ 之间的连边数为 $b-\frac{b+c-a}{2}$，点 $1$ 与点 $3$ 之间的连边数为 $c-\frac{b+c-a}{2}$。

最后输出答案就行了。

## code

```cpp
#include <bits/stdc++.h>
using namespace std;
int a, b, c, x, y, z, d, e;

int main(){
    cin >> a >> b >> c;
    if((a + b + c) % 2 || (a + b) < c || (b + c) < a || (a + c) < b){
        cout << "Impossible" << endl;
        return 0;
    }
    cout << b - (b + c - a) / 2 << " " << (b + c - a) / 2 << " " << c - (b + c - a) / 2 << endl;
    return 0;
}
```

本人对码风有严格的奇怪要求，若看不懂，勿喷。

---

## 作者：hh20080501hh (赞：1)

想拥有更好的阅读体验？~~想都别想~~，你什么也戳不了。


------------

# 题面：
有一个具有三个顶点的无向图，给出每个顶点的度（即与这个顶点相连的边的数目）

如果有一种连接边的方式，使得每个顶点的度都等于给出的数字，请输出这种方案：

输出格式：

输出共 $1$ 行，三个整数，用空格分开。

三个整数分别为第 $1$ 和第 $2$，第 $2$ 和第 $3$，第 $3$ 和第 $1$ 顶点之间的边数。

否则输出 `Impossible`。

[题面戳这里~](https://www.luogu.com.cn/problem/CF344B)
# 分析
1. 给定每个顶点的度，所以我们需要先理解度是什么：
```plain
   图结构中与某节点相连接的边的数目为该节点的度，而图中各个的节点度的散布情况就为度分布。

								————来自百度百科。
```
2. 根据上一条可得，某个节点的度即是该节点边的数量，而边必定会连接 $2$ 个节点（本题中不考虑自环，但是可以有重边）。

3. 由上一条可以容易得出，若给定的度之和是奇数，那么就一定不满足题意，因为有一条边连不到两个节点上（请仔细思考）。

4. $1$ 到 $2$ 的边的数量，就是边的总数量（即度数量之和除以 $2$）减去节点 $3$ 的度。$2$ 和 $3$ 同理，可以自己去推一推。


------------

# 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a , b , c;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	cin >> a >> b >> c;//a为第一个节点的度，b和c同理
	if ((a+b+c)&1)
	{
		cout << "Impossible";
		return 0;
	}
	int way_sum = (a+b+c)/2;//度总和除以二，即边的条数
	int way1to2 = way_sum-c , way2to3 = way_sum-a , way3to1 = way_sum-b;//way1to2表示节点1到节点2的边，剩下两个同理
	if (way1to2>=0 && way2to3>=0 && way3to1>=0)
    //如果有一个节点到另外一个节点的
    //的边为负数，很明显不符合情况，所以加特判
	{
		cout << way1to2 << " " << way2to3 << " " << way3to1 << endl;
	}
	else
	{
		cout << "Impossible";
	}
	return 0;
}

```
变量名的意义见注释。

**成功 AC** 。

---

## 作者：Jerrycyx (赞：1)

这道题可以用 $O(1)$ 的**三元一次方程**来做。

我们设 $1$ 号节点的度为 $a$，$2$ 号节点的度为 $b$，$3$ 号节点的度为 $c$；再设 $1,2$ 号节点有 $x$ 条连边，$2,3$ 号节点有 $y$ 条连边，$3,1$ 号节点有 $z$ 条连边。用一张图来表示就是：

![graph](https://cdn.luogu.com.cn/upload/image_hosting/pankjubm.png)

因为节点的度就是它所连边的条数，所以 $1$ 号点的度也为 $x+z$，$2,3$ 号分别为 $x+y$ 和 $y+z$。即

$$\begin{cases}
	a=x+z\\
	b=x+y\\
	c=y+z
\end{cases}$$

只需要解出这个方程了 ~~（应该都会解三元一次方程吧）~~。三个式子相加得：

$$a+b+c=2x+2y+2z$$

交换式子两边并同时除以 $2$ 得：

$$x+y+z=\frac{a+b+c}{2}$$

把这个式子减去 $x+z=a$ 得到：$y=\frac{a+b+c}{2}-a$，$x,z$ 也可以同理得到，即：

$$\begin{cases}
	x=\frac{a+b+c}{2}-c\\
	y=\frac{a+b+c}{2}-a\\
	z=\frac{a+b+c}{2}-b
\end{cases}$$

然后直接输出 $x,y,z$ 即可。

还要注意 **`Impossible` 的情况：**

+ $a+b+c$ 不是偶数，即不被 $2$ 整除。
+ $x,y,z$ 中任意一个算出来是个负数。

这两种情况需要进行判断。

**这样，就可以用 $O(1)$ 的时间复杂度得到答案了**，根本不用 $O(\max(a,b,c))$ 的循环。

### 代码

```cpp
#include<cstdio>
using namespace std;
int a,b,c;
int main()
{
	scanf("%d%d%d",&a,&b,&c);
	int sum=(a+b+c)>>1;		//(a+b+c)>>1 等价于 (a+b+c)/2 
	int x=sum-c,y=sum-a,z=sum-b;
	if((a+b+c)&1||x<0||y<0||z<0)	//(a+b+c)&1 等价于 (a+b+c)%2 
		printf("Impossible\n");
	else printf("%d %d %d\n",x,y,z);
	return 0;
}
```

$$\Large\frak{The\ End}$$

---

## 作者：baoziwu2 (赞：0)

看到 $10^6$ 的数据范围，不妨直接枚举顶点 $1$ 与 顶点 $2$ 的边数 $i$。

然后判断是否满足顶点 $3$ 的度数要求即可(即顶点 $1$ 的度数 $+$ 顶点 $2$ 的度数 $-2i$ = 顶点 $3$ 的度数)。

```
a, b, c = map(int, input().split())
for i in range(min(a, b) + 1):
    if(a + b - 2 * i == c):
        print(i, b - i, a - i)
        exit(0)
print("Impossible")
```

---

## 作者：HuZHUNZHUN (赞：0)

设 $x,y,z$ 分别代表我们要求的三个变量。

由于图中没有自环，因此我们可以自信地列出如下的方程组：

$\begin{cases} x+y=b \\ y+z=c\\ z+x=a \end{cases}$;

这是一个典型的轮换对称的方程组，因此我们可以自信地把它解出来：

$\begin{cases} x=\dfrac{a+b-c}{2} \\ y=\dfrac{b+c-a}{2}\\ z=\dfrac{c+a-b}{2} \end{cases}$;

下面，我们来看一下成立的条件：

首先，要求 $x,y,z$ 都非负；其次，要求 $x,y,z$ 至少有两个非零；最后，要求 $x,y,z$ 都是整数。最后，我们列出如下的条件：

$\begin{cases} abc\ne0 \\ a+b\ge c \\ b+c\ge a \\ c+a\ge b \\ 2\mid a+b+c \end{cases}$;

上代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c;
int main()
{
	ios::sync_with_stdio(false);
	cin>>a>>b>>c;
	if(a*b*c==0)
	{
		cout<<"Impossible"<<endl;
		return 0;
	}
	if(a+b<c || b+c<a || c+a<b)
	{
		cout<<"Impossible"<<endl;
		return 0;
	}
	if((a+b+c-1)%2==0)
	{
		cout<<"Impossible"<<endl;
		return 0;
	}
	else cout<<(a+b-c)/2<<" "<<(b+c-a)/2<<" "<<(c+a-b)/2<<endl;
	return 0;
}
```

---

## 作者：Qiancy1427 (赞：0)

[原题目传送门](/problem/CF344B)

### 题意

有一个具有 $3$ 个顶点的无向图，给出与每个顶点相连的边的数量，求每两个点之间的边的数量（或者不存在，即 Impossible）。

### 思路

这个题可以通过一个简单的三元一次方程组简单的解决。

~~应该都学过了吧~~

设分别与 $3$ 个点相连的边的数量为 $a$，$b$，$c$；两点之间的边的数量分别为 $x$，$y$，$z$。

可以得到

$\begin{cases}x+z=a\\x+y=b\\y+z=c\end{cases}$

解得

$\begin{cases}x=\dfrac{1}{2}(a-b+c)\\\\y=\dfrac{1}{2}(c-a+b)\\\\z=\dfrac{1}{2}(a-b+c)\end{cases}$

根据题意，我们输入了 $a$，$b$，$c$，那么 $x$，$y$，$z$ 就可以直接解出了。

### AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c,x,y,z;
int main(){
	cin>>a>>b>>c;
	if(a+b-c<0||(a+b-c)%2!=0||c-a+b<0||(c-a+b)%2!=0||a-b+c<0||(a-b+c)%2!=0){//特判
		cout<<"Impossible";
		return 0;
	}
	x=(a+b-c)/2,y=(c-a+b)/2,z=(a-b+c)/2;
	cout<<x<<" "<<y<<" "<<z;
	return 0;
}
```

~~（小声 bb）另外，为什么现在流行把 AC 记录放到题解上啊。~~

---

## 作者：agicy (赞：0)

# 题意

有一个具有三个顶点的无向图，给出每个顶点的度（即与这个顶点相连的边的数目）

如果有一种连接边的方式，使得每个顶点的度都等于给出的数字，请输出这种方案：

输出格式：

- 输出共$1$行，三个整数，用空格分开；
- 三个整数分别为第$1$和第$2$，第$2$和第$3$，第$3$和第$1$顶点之间的边数；

否则输出`Impossible`。

# 思路

枚举顶点$1,2$的边数$i$，则

- $1,3$之间的边数：$a-i$；

- $2,3$之间的边数：$b-i$；

所以如果满足条件：$a-i+b-i=c$，那么就输出。

注：条件用`C++`写成：`a+b-(i<<1)==c`

# 代码

根据思路，代码如下：

```cpp
#include <cstdio>

int a, b, c;

int main(void)
{
    register int i;
    scanf("%d%d%d", &a, &b, &c);//读入
    for (i = 0; i <= a && i <= b; ++i)//枚举
        if (a + b - (i << 1) == c)//条件
            return printf("%d %d %d\n", i, b - i, a - i), 0;//输出
    puts("Impossible");//无方案，输出
    return 0;
}
```

## [我的评测记录](https://www.luogu.org/recordnew/show/15906696)


---

## 作者：_Glassy_Sky_ (赞：0)

[题目在这儿](https://www.luogu.com.cn/problem/CF344B)

这题其实算是一道很简单的题目了，个人觉得难度可能就入门级别吧。

现在开始切入正题。首先我们可以知道，两点一线，一条线的成立必然就需要两个点，反之，在描述三个点的时候，必然两点之间的一条线会被描述两次。就比如点 $A$ 有一条与点 $B$ 相连的连边，描述一下；点 $B$ 又有一条与点 $A$ 相连的连边，描述一下。总共就描述了两下！以此类推的话，我们只需要将所有连边加起来，再除以二，就可以得到真正的连边数量！

真正的连边数量知道了，问题就迎刃而解了。设点 $A$ 与点 $B$ 和点 $C$ 共有 $x$ 条连边，点 $B$ 与点 $C$ 有 $y$ 条连边，共有 $z$ 条连边，显然那就可以得出式子 $z-y=x$，由此我们就可以得出其他点的边数了。

但是此题真正的坑点在于**特判**。第一点是如果有输入数据小于或等于 $0$ 的，不可能；输入数据总和是奇数的，不通过；最后得出的结果有小于 $0$ 的，卡掉。

最后是代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int a, b, c;
	cin >> a >> b >> c;
	if(a <= 0 || b <= 0 || c <= 0)
	{
		cout << "Impossible";
		return 0;
	}
	if((a + b + c) % 2 == 1)
	{
		cout << "Impossible";
		return 0;
	}
	int cnt = (a + b + c) / 2;
	int anow = cnt - c, bnow = cnt - b, cnow = cnt - a;
	if(anow < 0 || bnow < 0 || cnow < 0)
	{
		cout << "Impossible";
		return 0;
	}
	cout << anow << " " << bnow << " " << cnow;
	return 0;
}

```
谨此

---

## 作者：tder (赞：0)

[$\Large\color{black}\textbf{CF344B Simple Molecules}$](https://www.luogu.com.cn/problem/CF344B) $\Large\textbf{题解}$

[$\textbf{题目传送门}$](https://www.luogu.com.cn/problem/CF344B)

[$\textbf{更好的阅读体验}$](https://www.luogu.com.cn/blog/tder/solution-cf344B)

~~打着图的名字的数学题~~

---

$$\large\textbf{思路}$$

设每个点的度分别为 $x,y,z$，两点之间各有 $a,b,c$ 条边。

由于每条边有两个顶点，所以总边数即为 $3$ 个点的度数之和的一半，即 $\dfrac{x+y+z}2$。

![](https://cdn.luogu.com.cn/upload/image_hosting/nrjhau5x.png)

不难发现，两点之间的边数 $=$ 总边数 $-$ 第三点的度数，即 $c=\dfrac{x+y+z}2-x$，以此类推。

根据一些众所周知的常识，$0\le$ 任意两点间的边数 $\le$ 总边数 $\in \mathbb{N}$，并且每个点的度数均 $>0$ 。若不满足则输出 `Impossible`。

---

$$\large\textbf{代码}$$

```cpp
#include <bits/stdc++.h>
using namespace std;
int x, y, z, s, a, b, c;
int main() {
	cin>>x>>y>>z;
    if((x + y + z) % 2) { // 总边数需为整数
        cout<<"Impossible"; 
		return 0;
    }
    if(!x || !y || !z) { // 每个点的度数需大于 0
        cout<<"Impossible"; 
		return 0;
    }
    s = (x + y + z) / 2; // 计算总边数
    a = s - z, b = s - y, c = s - x; // 计算两点之间的边数
    if(a < 0 || b < 0 || c < 0) { // 任意两点间的边数需大于等于 0
        cout<<"Impossible"; 
		return 0;
    }
    cout<<a<<" "<<c<<" "<<b; // 输出边数
	return 0;
}
```

---

## 作者：lwx20211103 (赞：0)

# 分析与思路

首先，这跟图论没什么关系，是一道数学题。题目给了我们每个点连接的线段数量，求到各个点的边的数量，**因为是三条边的度，也只有三条边的数量，所以答案是唯一的**，这是样例二的解释：
![](https://cdn.luogu.com.cn/upload/image_hosting/0cduly1r.png)

## 方法一：三元一次方程

如果你还没上初中，且还不知道这个的话，建议去搜索以下这东西，或者看后面的方法二。

我们设答案为 $a,b,c$，输入是 $x,y,z$，如上，可得出： 

$$
\left\{ 
\begin{matrix}
a + c = x \\
a + b = y \\
b + c = z 
\end{matrix}
\right.
$$

化简，得

$$
\large\left\{ 
\begin{matrix}
a = \frac{x + y - z}{2} \\
b = \frac{y + z - x}{2} \\
c = \frac{x + z - y}{2} \\
\end{matrix}
\right.
$$

故可以产生时间复杂度为 $O(1)$ 的做法。
```cpp
#include<bits/stdc++.h>
using namespace std;

bool check(int p, int q, int m) //判断是否小于0且除得尽
{
    return !((p + q - m) & 1) && (p + q - m) >= 0; // true为偶数
}

int main()
{
    int x, y, z, a, b, c;
    cin >> x >> y >> z;
    // 根据方程推出，a = (x + y - z) / 2,  b = (y + z - x) / 2  c = (x + z - y) / 2
    if (check(x, y, z) && check(y, z, x) && check(x, z, y))
    {
        a = (x + y - z) / 2, b = (y + z - x) / 2, c = (x + z - y) / 2;
        cout << a << " " << b << " " << c;
    }
    else
    {
        cout << "Impossible";

    }
    return 0;
}

```

## 方法二：枚举

这里也有数学的思想在，还是上面那张图，我们设 $1 - 2$ 的线段数量为 $i$ , 那么  $1 - 3$ 的就是 $x - i$ ，$2 - 3$ 的就是 $y - i$，此时，因为第三点的数量是 $z$，所以可以得出四者关系：
$$
x - i + y - i = z
$$
即
$$
x + y - 2i = z
$$

应用一下

```cpp
#include<bits/stdc++.h>
using namespace std;

int main()
{
    int x, y, z, i;
    cin >> x >> y >> z;
    for (i = 0;i <= min(x, y);i++)
    {
        if (x + y - (i << 1) == z)
        {
            cout << i << " " << x - i << " " << y - i;
            return 0;
        }
    }
    cout << "Impossible";
    return 0;
}

```

## 总结

这题还有要注意的地方，比如 Impossible 要注意字母，枚举到 $x,y$ 的最小值，然后 方程要注意能不能整除和 对于 $0$ 的判断。

题解仅供参考，请勿直接抄袭，谢谢管理员的审核，感谢收看。

---

