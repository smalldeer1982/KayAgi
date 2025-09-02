# [NOISG 2018 Finals] Lightning Rod

## 题目背景

译自 [NOISG 2018 Finals C. Lightning Rod](https://github.com/noisg/sg_noi_archive/tree/master/2018/tasks/lightningrod)。

## 题目描述

新加坡的城市天际线可以看成一个平面直角坐标系，第 $i$ 栋大楼的顶端是点 $(X_i,Y_i)$。

一根避雷针可以安装在大楼的顶端上。它的保护区域为从该大楼顶端向左下方和右下方作两条与坐标轴呈 $45^\circ$ 的射线所产生的 $\frac{1}{4}$ 平面。所有顶端在该保护区域内或落在保护区域边缘上的大楼都可以被保护到。

换句话说，若避雷针安装在大楼 $i$ 上，则所有且仅所有满足 $|X_i-X_j|\le Y_i-Y_j$ 的大楼 $j$ 可以被该避雷针保护到。

你的任务是找出最少的安装避雷针数量，使得所有大楼都可以被至少一根避雷针保护到。

## 说明/提示

### 样例 #1 解释

所有大楼都需要安装避雷针。

这组样例满足所有子任务。

### 样例 #2 解释

在大楼 $2$ 的顶端安装避雷针。

这组样例满足子任务 $2$ 至 $7$。

### 样例 #3 解释

![](https://cdn.luogu.com.cn/upload/image_hosting/glq0s3hc.png)

如图所示，在大楼 $1$ 和大楼 $3$ 的顶端安装避雷针。

这组样例满足子任务 $3,4,5,7$。

### 子任务

对于 $100\%$ 的数据，$2\le N\le 10^7$，$0\le X_i,Y_i\le 10^9$。

| 子任务 | 得分 | $N$ | $X_i,Y_i$ |
| :----------: | :----------: | :----------: | :----------: |
| $1$ | $4$ | 无特殊限制 | $Y_i=1$ |
| $2$ | $7$ | $=2$ | 无特殊限制 |
| $3$ | $12$ | $\le20$ | 无特殊限制 |
| $4$ | $21$ | $\le 2\times 10^3$ | 无特殊限制 |
| $5$ | $26$ | $\le 2\times 10^5$ | 无特殊限制 |
| $6$ | $10$ | 无特殊限制 | $X_i=i,Y_i\le 1$ |
| $7$ | $20$ | 无特殊限制 | 无特殊限制 |


## 样例 #1

### 输入

```
2
1 1
2 1```

### 输出

```
2```

## 样例 #2

### 输入

```
2
1 0
2 1```

### 输出

```
1```

## 样例 #3

### 输入

```
4
1 1
3 2
4 3
5 1```

### 输出

```
2```

# 题解

## 作者：Forge_Unique (赞：1)

## 思路 & 代码实现

先将大楼按高度排好位置（从低到高），然后从倒数第二矮的大楼开始枚举比它矮一层的大楼如果可以保护的到，把保护到的大楼加入这栋大楼的集合里（这个可以用双指针加并查集来做到，时间复杂度 $O(n \log n)$ 足够了）。

然后求不同的集合有几个，输出即可。

---

## 作者：0x00AC3375 (赞：1)

### 1. 题意

有若干座高楼大厦，需要在某一些大楼的顶部安装避雷针。

求最少需要安装多少避雷针，才能保证所有的大楼都在保护范围内。

### 2. 分析

本题可以看做是一个**计算几何**问题，属于图形覆盖问题。

根据题意，每根避雷针保护的区域是以该避雷针所在位置为顶点的等腰直角三角形区域。

分析过程中，如果出现了**大三角形完全覆盖小三角形**的情况，意味着小三角形对应的避雷针是不必要的。

由于题目中保证所有的横坐标单调不减地给出（其实不保证单调不减也无所谓，多一步排序操作就可以了，但就本题而言可能会出现TLE），因此我们可以线性扫描。

我们可以考虑用一个栈维护所有三角形，栈顶的元素是**扫描到当前位置，横坐标最靠右的，必须使用的三角形**。

当新加入一个三角形时...
- 检查栈顶的若干三角形（最靠右的若干三角形），若能够被新增的三角形覆盖，就将其全部移除，然后将新增的三角形加入，新增的三角形就成为**最靠右的必须三角形**；
- 新增的三角形如果可被一个已有三角形覆盖，就将其忽略。

判断是否覆盖的本质是比较某点（楼顶）位置 $(x_A,y_A)$ 到另一栋大楼底部 $(x_B,0)$ 的**街区距离**是否小于另一栋大楼的高度 $y_B$。

全部扫描完毕后，栈中的三角形数量就是答案。

### 3. 代码

必须使用快读。使用 `scanf` 或者 `cin` 或者 C# 的 `StreamReader` （据说相当于 C++ 的快读）皆会出现 TLE。

```cpp
#include <cstdio>
#include <stack>
#include <cmath>
using namespace std;

class TriangleVertex {
public:
    int topX, topY;
    bool TriangleCover(TriangleVertex& another) const noexcept
    {
        return abs(topX - another.topX) <= topY - another.topY;
    }
    TriangleVertex(int x, int y) : topX(x), topY(y) { }
}

inline int readInt() 
{
    int x = 0;
    char ch = getchar_unlocked();
    while (ch < '0' || ch > '9') ch = getchar_unlocked();
    while (ch >= '0' && ch <= '9')
    {
		x = (x << 3) + (x << 1) + ch - '0';
		ch = getchar_unlocked();
	}
    return x;
}

int main(void)
{
    stack<TriangleVertex> triangle_needed;
    int n = readInt(), x, y;
    for (int i = 0; i < n; ++i) 
    {
        x = readInt(), y = readInt();
        TriangleVertex vertex(x, y);
        if (!triangle_needed.empty() && triangle_needed.top().TriangleCover(vertex))
        {
            continue;
        }
        while (!triangle_needed.empty() && vertex.TriangleCover(triangle_needed.top()))
        {
            triangle_needed.pop();
        }
        triangle_needed.push(vertex);
    }
    printf("%d\n", triangle_needed.size());
}
```

记录：https://www.luogu.com.cn/record/201460012

### 4. Trivia

本题的情景同样可以推广到三维空间。

如果推广到三维空间，则位于 $(x_0,y_0,z_0)$ 的避雷针可以覆盖的区域是一个以该点为顶点的正四棱锥区域，这个边界区域的方程是 $|x-x_0|+|y-y_0|+z=z_0$，其中 $z,z_0$ 必须为正，$x,y,x_0,y_0$ 可正可负。使用类似的方法同样可以解决三维问题。

由于题目中，栈中存储的是**横坐标最大的，必须使用的三角形**；类似的，在三维问题中可以考虑按照距离原点的水平距离 $\sqrt{x_0^2+y_0^2}$ 作为指标，栈顶存储的是**距离原点最远的，必须使用的金字塔**。

这里假设所有的坐标 $(x_i,y_i,z_i)$ 全为正并且按照 $\sqrt{x_i^2+y_i^2}$ 单调不减输入。

代码：

```cpp
#include <cstdio>
#include <stack>
#include <cmath>
using namespace std;

class Pyramid {
public:
    int topX, topY, topZ;
    Pyramid(int x, int y, int z) : topX(x), topY(y), topZ(z) {}
    bool PyramidCover(Pyramid& another) const noexcept 
    {
        return abs(topX - another.topX) + abs(topY - another.topY) <= topZ - another.topZ;
    }
};

inline int readInt()
{
    int x = 0;
    char ch = getchar_unlocked();
    while (ch < '0' || ch > '9') ch = getchar_unlocked();
    while (ch >= '0' && ch <= '9')
    {
        x = (x << 3) + (x << 1) + ch - '0';
        ch = getchar_unlocked();
    }
    return x;
}

int main(void)
{
    stack<Pyramid> pyramid_needed;
    int n = readInt(), x, y, z;
    for (int i = 0; i < n; ++i)
    {
        x = readInt(), y = readInt(), z = readInt();
        Pyramid vertex(x, y, z);
        if (!pyramid_needed.empty() && pyramid_needed.top().PyramidCover(vertex))
        {
            continue;
        }
        while (!pyramid_needed.empty() && vertex.PyramidCover(pyramid_needed.top()))
        {
            pyramid_needed.pop();
        }
        pyramid_needed.push(vertex);
    }
    printf("%d\n", pyramid_needed.size());
}
```

---

## 作者：CommonDigger (赞：1)

可以把题意理解成第一象限内有若干个等腰三角形，小的三角形被大的覆盖，最小要多少避雷针就是问能看到几个三角形。

观察到 $N\leq10^7$ 且 $x$ 坐标是单调不递减地给出，都表明需要使用线性做法。注意到小三角形被大的**完全**覆盖后就对后续计算没有意义了，所以我们只需要关注大三角形即可。这符合单调栈的性质。

用一个栈维护所有三角形，当新加入一个三角形时，如果栈中有能被其覆盖的，就出栈（代表被覆盖没用了），最后新三角形进栈。所以栈中的三角形都是没有被覆盖的，所有三角形处理完毕后栈的大小即是能看到的三角形数量，也就是需要用的最小避雷针数量。

另外大数据都推荐使用快读快写。这个题只需要输出一个数所以无需使用快写。

```cpp
/*
Luogu P11596 Lightning Rod
https://www.luogu.com.cn/problem/P11596
*/
#include <iostream>
#include <stack>
using namespace std;
int n, x0, y0;
struct point {
    int x, y;
    point(int x=0, int y=0) {
        this->x=x;
        this->y=y;
    }
};
stack<point> s;
bool cover(point pre, point now) { // 检查 "now" 是否被 "pre" 所覆盖
    return abs(pre.x-now.x) <= pre.y-now.y;
}
int read() {
    int x1=0;
    char c=getchar();
    while (c<'0' || c>'9') c=getchar();
    while (c>='0' && c<='9') {
        x1 = x1*10+c-'0';
        c=getchar();
    }
    return x1;
}
int main() {
    n=read();
    while (n--) {
        x0 = read(); y0=read();
        point now=point(x0, y0);
        if (s.size() && cover(s.top(), now)) continue;
        while (s.size() && cover(now, s.top())) s.pop();
        s.push(now);
    }
    cout << s.size();
}
```

---

## 作者：Shunpower (赞：1)

题目显然要求我们给出一个线性做法。

先分析一些性质。首先，一个已经被其他避雷针保护的建筑之上必然没有必要再放避雷针，因为它的保护区域一定会被保护它的避雷针的保护区域完全覆盖。

于是我们考虑从左往右扫所有建筑。假设前缀已经构成一个最优解，且使得最右边这个点上保护区域的高度尽量高，考虑下一步选择。

如果这一步选择完全被左侧的保护区域涵盖，那么完全没有必要选择这个避雷针。

如果没有，那么我们必然要选择这个避雷针。因为我们保证了前缀的解最右侧保护区域最高，我们绝不可能通过调整前缀选到这个避雷针。

选择这个避雷针之后可能可以干掉左侧的一些避雷针。可以证明，干掉的一定是一个选择的避雷针的后缀。利用我们一开始分析的性质可以简单地反证。

于是拿个栈维护选择的避雷针就可以了。我也不知道这个东西叫不叫单调栈。需要注意一下高度为 $0$ 的楼的问题。

```cpp
read(n);
fr1(i,1,n) read(x[i]),read(y[i]);
ry=x[1]-1;
fr1(i,1,n){
    ry=max(ry-(x[i]-x[i-1]),-1);
    if(ry>=y[i]) continue;
    while(!st.empty()){
        if(y[st.top()]<=y[i]-(x[i]-x[st.top()])) st.pop();
        else break;
    }
    ry=y[i];
    st.push(i);
}
cout<<st.size()<<'\n';
```

---

## 作者：PokerKing (赞：0)

## 思路

我们使用 **单调栈** 来维护避雷针的分布。

### 1. 避雷针的保护范围

安装在建筑物 $i$ 上的避雷针保护范围为：$[x_{i} - y_{i}, x_{i} + y_{i}]$。

### 2. 栈的维护逻辑

- 栈中的元素记录建筑物编号，表示这些建筑物上安装了避雷针。
- **弹出栈顶的条件**：当当前建筑物的避雷针能够完全覆盖栈顶建筑物时，弹出栈顶。
- 每次安装新避雷针后，将当前建筑物编号压入栈中。

### 3. 遍历规则

- 动态调整每栋建筑物的避雷针保护范围，确保覆盖所有建筑物。
- 遍历结束时，输出栈的大小。

---

## 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;

int x[10000005], y[10000005];
stack<int> st;

// 快速读入函数
inline int readInt() {
	int x = 0;
	char ch = getchar_unlocked();
	while (ch < '0' || ch > '9') ch = getchar_unlocked();
	while (ch >= '0' && ch <= '9') {
		x = (x << 3) + (x << 1) + ch - '0';
		ch = getchar_unlocked();
	}
	return x;
}

int main() {
	int n;
	n = readInt();	// 读取建筑物数量
	for (int i = 1; i <= n; i++) {
		x[i] = readInt();
		y[i] = readInt();
	}

	int ty = x[1] - 1;	// 初始化保护范围
	for (int i = 1; i <= n; i++) {
		// 动态调整当前保护范围
		ty = max(ty - (x[i] - x[i - 1]), -1);
		if (ty >= y[i]) {
			continue;  // 当前建筑物已被保护
		}

		// 检查并更新栈
		while (!st.empty()) {
			if (y[st.top()] <= y[i] - (x[i] - x[st.top()])) {
				st.pop();  // 栈顶建筑物被替代
			} else {
				break;
			}
		}

		// 更新当前保护范围并压入栈
		ty = y[i];
		st.push(i);
	}

	// 输出最少避雷针数量
	cout << st.size();
	return 0;
}
```

---

## 作者：lzx111218 (赞：0)

# P11596 [NOISG 2018 Finals] Lightning Rod
[题目传送门](https://www.luogu.com.cn/problem/P11596)
## 思路
每个避雷针的保护区域是由从该大楼顶端向左下方和右下方作两条与坐标轴呈 $45$° 角的射线形成的 $\displaystyle\frac{1}{4}$ 平面。这个平面会涵盖落在它的边界内的所有建筑物。

给定建筑物的顶端坐标 $X_i$ $Y_i$ 和 $X_j$ $Y_j$，可以通过以下方式判断大楼 $j$ 是否在大楼 $i$ 的保护范围内：

若 $|X_i - X_j| ≤ Y_i - Y_j$ 条件成立，则大楼 $i$ 的避雷针能够保护到大楼 $j$。

对于每个新的建筑物，判断它是否在栈顶建筑物的保护范围内。如果不在，就需要安装一个新的避雷针。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
namespace fastIO{char *p1,*p2,buf[100000];
	#define nc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
	inline void read(int&n){int x=0,f=1;char ch=nc();while(ch<48||ch>57){if(ch=='-'){f=-1;}ch=nc();}while(ch>=48&&ch<=57){x=(x<<3)+(x<<1)+(ch^48),ch=nc();}n=x*f;}
	inline void read(string&s){char ch=nc();while(ch==' '||ch=='\n'){ch=nc();}while(ch!=' '&&ch!='\n'){s+=ch,ch=nc();}}
	inline void read(char&ch){ch=nc();while(ch==' '||ch=='\n'){ch=nc();}}
	inline void write(int x){if(x<0){putchar('-'),x=-x;}if(x>9){write(x/10);}putchar(x%10+'0');return;}
	inline void write(const string&s){for(register int i=0;i<(int)s.size();i++){putchar(s[i]);}}
	inline void write(const char&c){putchar(c);}
}using namespace fastIO;
int main(){
	stack<int> st;  
    int n;
	read(n); 
    vector<int> x(n + 1), y(n + 1);
    for (int i = 1; i <= n; i++) {
        read(x[i]);
        read(y[i]);
    }
    int ty = x[1] - 1;  
    for (int i = 1; i <= n; i++) {
        ty = max(ty - (x[i] - x[i - 1]), -1);
        if (ty >= y[i]) {
            continue;  
        }
        while (!st.empty()) {
            if (y[st.top()] <= y[i] - (x[i] - x[st.top()])) {
                st.pop();  
            } else {
                break;
            }
        }
        ty = y[i];
        st.push(i);
    }
    ios::sync_with_stdio(false);
	cout.tie(0);
    cout<<st.size();
    return 0;
}
```

---

