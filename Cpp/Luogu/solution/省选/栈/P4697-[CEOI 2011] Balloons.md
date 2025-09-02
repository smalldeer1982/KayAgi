# [CEOI 2011] Balloons

## 题目描述

有 $n$ 个气球，他们一开始都是空的。

接下来，它们会按照从 $1$ 到 $n$ 的顺序依次充气，其中第 $i$ 个气球与地面在 $x_i$ 位置接触。

当气球碰到碰到前面的某个气球，或者达到半径最大限制时，就会停止充气。其中第 $i$ 个气球的半径最大限制为 $r_i$。

现在请你求出，每个气球最终半径是多少。

## 说明/提示

对于 $100\%$ 的数据，保证 $1\le n\le 200\ 000;0\le x_i\le 10^9;1\le r_i\le 10^9;x_1< x_2< \cdots < x_n$。

## 样例 #1

### 输入

```
3
0 9
8 1
13 7```

### 输出

```
9.000
1.000
4.694```

# 题解

## 作者：嘉然小姐的狗 (赞：14)

翻阅了网上屈指可数的题解，似乎都没有提到决策的单调性的证明；因此本人于此补上证明。

对于只想看看决策单调性证明的人，请手动翻到下面的**证明 2** 一节。

对于想要到我的洛谷博客查看的人，请到[这里](https://www.luogu.com.cn/blog/moonoshawott/loj2487)。

---

前置知识：以点 $A$ 为圆心的半径为 $r_A$ 的圆，与以点 $B$ 为圆心的半径为 $r_B$ 的圆不相交的充要条件是

$$\text{dis}(A, B) \geq r_A + r_B$$

其中 $\text{dis}(A, B)$ 表示点 $A$ 到点 $B$ 的距离，$\text{dis}(A, B) = \sqrt {(x_A - x_B)^2 + (y_A - y_B)^2}$。

---

对于 $j < i$，圆 $j$ 和圆 $i$ 不相交的充要条件是

$$
\begin{aligned}
	(r_i - r_j)^2 + (x_i - x_j)^2 &\geq (r_i + r_j)^2 \\
	(x_i - x_j)^2 &\geq 4r_ir_j \\
	r_i &\leq \frac {(x_i - x_j)^2}{4r_j} \ \\
\end{aligned}
$$

在没有限制的情况下，可以得到

$$r_i = \min_{1 \leq j < i} \left\{\frac {(x_i - x_j)^2}{4r_j}\right\}$$

考虑如何求解。

**定理 1**：若 $x_i < x_j$ 且 $r_i \leq r_j$，则圆 $i$ 一定不会影响到 $j$ 后面的圆。即，对于 $k > j$ 有

$$\frac {(x_k - x_j)^2}{4r_j} < \frac {(x_k - x_i)^2}{4r_i}$$

**证明 1**：显然有 $(x_k - x_j)^2 < (x_k - x_i)^2$ 且 $r_j > r_i$，易证。

此时我们可以忽略圆 $i$。我们可以用一个单调栈维护它，使栈内从顶到底 $x_i$ 单调下降且 $r_i$ 单调上升。

下面考虑如何决策。

**定理 2**：对于栈内元素 $i < j$ 和当前决策点 $k$（$i < j < k$），若 $r_k < r_j$，则 $r_k$ 不会受到 $i$ 的影响。

更直白地，若一个气球的半径比前面某个气球 $j$ 的半径小，则它不会受到 $j$ 前面气球的影响。

**证明 2**：考虑证明 $r_j < \frac {(x_k - x_i)^2}{4r_i}$。这个证明是显然的：

$$r_k < r_j < \frac {(x_j - x_i)^2}{4r_i} < \frac {(x_k - x_i)^2}{4r_i}$$

也就是 $r_k < \frac {(x_k - x_i)^2}{4r_i}$，即 $r_k$ 不会受到 $j$ 之前气球 $i$ 的影响。

这一点保障了我们决策时只需要找出栈顶进行决策即可：

1. 取出栈顶 $j$ 对当前决策点 $k$ 进行决策；
2. 若 $r_k < r_j$，则它不会受前面的气球的影响了。把 $r_k$ 加入栈顶，退出；
3. 否则弹出栈顶 $j$（为了维护 $r_j$ 递增），回到 1。

```plain
stack.clear()
for i = 1 to n
    while stack is not empty
        j = stack.top
        r[i] = min(r[i], (x[i] - x[j]) * (x[i] - x[j]) / 4 / r[j])
        if r[i] < r[j] then
            break
        else
            stack.pop()
    stack.push(i)
```

时间复杂度：$O(n)$。

---

## 作者：Durancer (赞：5)

#### 前言

被单调栈搞懵的第 $n$ 天

#### 思路

对于这个题，核心思路就是要判断两两圆的相切

因为位置是单调递增的，所以说做这道题更加简便了 

那么对于在平面内的两个圆 $A(x_i,y_i)$ 半径为$r_i$, $B(x_j,y_j)$ ,半径为 $r_j$ 相切(或者不相交)的条件$(i>j)$为

$$(x_i-x_j)^2+(y_i-y_j)^2 \geq (r_i+r_j)^2$$

化简可得 

$$r_i\leq\frac{(x_i-x_j)^2}{4r_j}$$

整合上面两个公式可得

$$r_i=\min_{1\leq j<i}(\frac{(x_i-x_j)^2}{4r_i})$$

考虑用单调栈来求解

#### 证明

对于单调栈中的元素 $i<j$ 来说，假设一个点 $i<j<k$ ,如果$r_k<r_j$ 那么 $k$ 一定不会受到 $i$ 的影响

通过上面的定理可以得到一个条件：

$r_k<r_j<\dfrac{(x_j-x_i)^2}{4r_i}<\dfrac{(x_k-x_i)^2}{4r_i}$

即 $r_k<\dfrac{(x_k-x_i)^2}{4r_i}$ 的时候，$k$ 就不会受到 $j$ 之前的气球的影响

那么可以用单调栈实现以下操作：

- 取出栈顶 $j$ 

- 如果 $r_k<r_j$ 不受之前的影响,加入栈顶

- 为了维护单调栈是递增的，如果$r_k>r_j$,弹出栈顶 $j$ 保证递增，返回继续循环执行三个操作

#### 代码

```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<stack>
#include<map>
#include<algorithm>
#include<map>
#include<cmath>
using namespace std;
const int N=2e5+9;
double r[N];// 
double x[N];//第i个气球与地面在x_i的位置相遇 
int stk[N];
int top,n;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%lf%lf",&x[i],&r[i]);
    for(int i=1;i<=n;i++)
    {
        while(top>0)
        {
            int di=stk[top];
            double dis=(x[i]-x[di])*(x[i]-x[di])/(4.0*r[di]);
            r[i]=min(r[i],dis);
            if(r[i]<=r[di]) break;//必须保证单调递增 
            top--;
        }
        stk[++top]=i;
        printf("%.4lf\n",r[i]); 
    }
    return 0;
} 
```





---

## 作者：吹雪吹雪吹 (赞：5)

#### [$\large \color{#ff7daf}\texttt{CEOI2011 Balloons}$](https://xc.fubuki.cn/2019/CEOI2011Balloons)

先膜拜随机过题的大佬 [$\texttt{Alpha}$](https://www.luogu.org/space/show?uid=87058) 。

若圆 $i$ 与圆 $j$ 相切，则 $r_i=\frac{(x_i-x_j)^2}{4r_j}$ ；若存在 $i,j$ 满足 $x_i>x_j,r_i>r_j$ ，则圆 $j$ 一定不会对后加入的点产生有效限制。因为题目保证 $x$ 递增，所以这里能用一个单调栈轻松维护。

接下来考虑决策。不难发现，若存在 $j$ 满足 $R(i, j)\leq r_j$ （其中 $R(i, j)$ 表示圆 $i$ 与圆 $j$ 相切时的 $r_i$ ），则所有 $j$ 之前的圆不会对 $i$ 产生有效限制；若 $R(i, j)>r_j$ ，则该限制可能是一个有效限制，并且一定有 $r_i > r_j$ ，可以直接从栈中删去 $j$ 。

时间复杂度 $O(n)$ ，证明略（其实挺显然的????）

```cpp

#include <cstdio>

#define maxn 200005

int n, stk[maxn], top;
double r[maxn], x[maxn];

int main()
{
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%lf%lf", &x[i], &r[i]);
        while (top > 0)
        {
            int j = stk[top];
            double now = (x[i] - x[j]) / 4.0 / r[j] * (x[i] - x[j]);
            r[i] = now < r[i] ? now : r[i];
            if (r[i] <= r[j])
                break;
            else
                --top;
        }
        stk[++top] = i;
        printf("%.6lf\n", r[i]);
    }
    return 0;
}

```

---

## 作者：HearTheWindSing (赞：3)

题目大意不多赘述。

#### 首先

最朴素的思路是充新的气球时，枚举前面的所有已经确定的气球。

#### 然后

考虑如何对这个做法进行优化。

显然，对于两个气球 $i$ 和 $j (i<j)$，

如果 $x_j-x_i>r_i+r_j$，

那么两个气球必然相离。

所以只要根据每个已经确定的气球的 $x+r$ 来进行限制就可以减少枚举的次数。

这里使用 `multiset` 使 $x+r$ 有序。

对 `multiset` 中的元素进行从大到小的枚举，枚举过程中同时更新新充的气球的最大半径，这样枚举的范围是不断、大幅地缩小的。

---

这种做法看起来过不了，但测试点中用时最多的只有 280ms（肯定比正解慢些啦）。

最后，附上代码。

```cpp
#include <cstdio>
#include <cmath>
#include <set>
#define min(x,y) ((x)<(y) ? (x) : (y))
using namespace std;

const int NMAX=2e5+10;

struct Ball{
    double x,rt;
}b[NMAX];

bool operator<(Ball x,Ball y){
    return x.x+x.rt<y.x+y.rt;
}

multiset<Ball> s;

int main(){
    int n;
    scanf("%d",&n);
    int t1,t2;
    scanf("%d%d",&t1,&t2);
    b[0]={double(t1),double(t2)};
    s.insert(b[0]);
    for (int i=1;i<n;i++){
        scanf("%d%d",&t1,&t2);
        b[i]={double(t1),double(t2)};
        for (auto j=s.end();j!=s.begin();j--){
            auto t=j;
            t--;
            if (b[i].x-(*t).x>b[i].rt+(*t).rt){
                break;
            }
            double maxr=double(b[i].x-(*t).x)*double(b[i].x-(*t).x)/((*t).rt*4);
            b[i].rt=min(b[i].rt,maxr);
        }
        s.insert(b[i]);
    }
    for (int i=0;i<n;i++){
        printf("%.8lf\n",b[i].rt);
    }
    return 0;
}

```

---

## 作者：Liu_Tianze (赞：3)

# P4697 [CEOI2011] Balloons 题解

[**原题链接**](https://www.luogu.com.cn/problem/P4697)

推荐跳转至[我的博客](https://www.luogu.com.cn/blog/Liu-Tianze/p4697-solution)进行阅读。

### 题目分析

对于每个气球，有两个限制：

- 不能超过半径最大限制 $r_i$ ；

- 与之前的所有气球只能相切，不能重合。

设每一个确定的气球半径为 $ans_i$ ，显然 $ans_1=r_1$ 。

**考虑如何判断两气球相切的情况**，设当前圆的半径为 $R$ ，考虑到第 $i$ 个圆时，作图如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/3zwm71mc.png)

由勾股定理，对于图中绿色三角形，可列出关于 $R$ 的方程：


$(x_i-x_{i-1})^2+(ans_{i-1}-R)^2=(ans_{i-1}+R)^2$

解得 $R= \dfrac{(x_i-x_{i-1})^2}{4\times ans_{i-1}}$

但如果对于每一个圆都计算与之前所有圆相切时的半径，再取最小值的做法，时间复杂度为 $O(n^2)$ ，显然不行。

通过观察发现，考虑第 $i$ 个圆时（图中蓝色和绿色圆），若 $ans_{i-2}<ans_{i-1}$ ，气球 $i$ 的大小**不会受到气球 $i-2$ 的影响。**

![](https://cdn.luogu.com.cn/upload/image_hosting/asumnjho.png)

所以考虑在过程中使用**单调栈**维护之前可能对当前的气球半径有影响的气球编号。

若考虑 $i$ 气球时 $ans_{i-1}<ans_{i}$ ，则将 $i-1$ 弹出。

### 代码实现

实现难度不大，注意何时需要弹出元素即可。

```cpp
#include <iostream>
#include <stack>
using namespace std;
const int N=2e5+10;
double x[N],r[N];
double ans[N];
stack<int> sta;
int main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>x[i]>>r[i];
        ans[i]=r[i];
    }
    ans[1]=r[1];
    sta.push(1);
    for(int i=2;i<=n;i++){
        while(!sta.empty()){
            int j=sta.top();
            ans[i]=min(ans[i],(x[i]-x[j])*(x[i]-x[j])*1.0/(4.0*ans[j])*1.0);
            if(ans[i]<ans[j]){
                break;
            }else{
                sta.pop();
            }
        }
        sta.push(i);
    }
    for(int i=1;i<=n;i++){
        printf("%lf\n",ans[i]*1.0);
    }
    return 0;
}

```

算法时间复杂度为 $O(n)$ ，可以通过本题。

---

## 作者：DiruiXiao (赞：2)

## P4697 [CEOI2011] Balloons

**【题意】**

给定 $n$ 个圆，其中第 $i$ 个圆的坐标为 $(x_i, r_i)$ (对于 $r_i$ 表示的是第 $i$ 个圆的最大半径限制)，设第 $i$ 个圆的实际半径是 $r_i$ 。$r_i$ 满足当前圆刚好和 $i$ 之前的圆相切，现要求求出对于每个 $i$ ($1 \le i \le n$) 求出一个最大的 $r_i$ 。

**【分析】**

首先根据题意，能够影响 $r_i$ 的值的只有在 $i$ 之前的圆。

若考虑直接枚举上一个圆 $j$, 则显然有：
$$
r_i = \min\limits_{1\le j < i} \left(\sqrt{(x_i - x_j)^2+(r_i-r_j)^2} - r_j\right)
$$
$$
(r_i+r_j)^2 = (x_i - x_j) ^2 + (r_i - r_j)^2
$$
$$
4r_ir_j = (x_i-x_j)^2
$$
$$
r_i=\frac{(x_i-x_j)^2}{4r_j}
$$
$$
r_i = \min\limits_{1\le j < i}\left(\frac{(x_i-x_j)^2}{4r_j}\right)
$$
此时直接枚举的效率就是 $O(n^2)$ ，考虑继续优化。

**单调栈：**

观察式子发现对于 $m$, $n$ 如果满足 $x_m > x_n$ 且 $r_m > r_n$ 则可以保证 $n$ 对只后的答案一定没有贡献。

证明：
$$
r_1 = \frac{(x_i - x_m)^2}{4r_m}
$$
$$
r_2 = \frac{(x_i - x_m)^2}{4r_n}
$$

则显然有 $r_1 < r_2$ ，得证。

考虑使用单调栈来维护出一个 $x_i$, $r_i$ 均单增的序列。此时每次枚举决策点的位置只需枚举栈内的元素，时间复杂度介于 $O(n)$ 到 $O(n^2)$ ，考虑继续优化。

**决策单调性优化：**

对于 $m$, $n$ ($1 \le m < n \le i$), 其中 $i$ 是当前决策点，如果满足 $r_m < r_n$，$x_m < x_n$ 且 $r_i < r_n$ 则 $r_i$ 不会受到 $r_m$ 的影响。

证明, 带入上式可得(设 $r_{a, b}$ 表示 $a$，$b$ 两圆的最大半径)：
$$
r_i < r_n \le \frac{(x_n - x_m)^2}{4x_m}
$$
又有
$$
\frac{(x_n - x_m)^2}{4x_m} < \frac{(x_i - x_m)^2}{4x_m}
$$
所以有
$$
r_i < \frac{(x_i - x_m)^2}{4x_m} = r_{i, m}
$$
得证。

又由于我们已经维护了一个单调栈，保证了上述证明的性质，因此只需每次取出栈顶元素判断即可。

**【总结】**

首先，对于当前求值的 $i$ 来说，每次取出栈顶元素 $j$ 。对于当前的 $r_i$ 计算出一个值，如果当前的 $r_i < r_j$ 满足单调栈的性质，入栈，否则弹出栈顶元素，重新取出 $j$。

因为每个元素只会入、出栈一次，时间复杂度为 $O(n)$ 。

代码(简短版，卡常版戳[这里](https://www.luogu.com.cn/record/86161599))：

```cpp
#include<iostream>
#include<cstdio>
#define MAXN 200005
using namespace std;
typedef long long ll;
double x[MAXN], r[MAXN]; int stack[MAXN], top = 0, n, i = 1;
int main() {
	scanf("%d", &n);
	for (; i <= n; i ++) scanf("%lf %lf", x + i, r + i);
	for (i = 1; i <= n; ++i) {
		while (top > 0) {
			int j = stack[top]; r[i] = min(r[i], (1.0 * (x[i] - x[j]) * (x[i] - x[j])) / (4 * r[j]));
			if (r[i] <= r[j]) break;
			else top--;
		}
		stack[++top] = i;
		printf("%.4lf\n", r[i]);
	}
	return 0;
}
```



---

## 作者：船酱魔王 (赞：1)

# P4697 [CEOI2011] Balloons 题解

## 题意回顾

有 $ n $ 个 X 轴上的不重合的点，从左面的点开始每个点依次构造一个圆使得底端在点位置与 X 轴相切，且不与之前的点构造的圆相交，且不超过这个点初始给定的半径上限，在此基础上半径最大。求出最后每个圆的半径。

$ 1 \le n \le 2 \times 10^5 $，点的坐标在 $ [0, 10^9] $ 范围内，半径上限在 $ [1, 10^9] $ 范围内。

## 分析

考虑 $ O(n^2) $ 的朴素暴力，如果有圆初始点在 $ x_1 $ 半径为 $ r_1 $，则初始点在 $ x_2 $ 的圆的半径受第一个圆的影响为与 $ \frac{(x_2-x_1)^2}{4r_1} $ 取最小值。

可以发现，一个圆的半径为上限与之前所有圆按照上式计算的影响的最小值。

我们发现，如果一个圆在另一个圆之后且半径更大，这个圆对于后面的圆的影响的值一定小于前面的圆，因为是取最小值所以前面那个圆就没有用了。考虑使用单调栈维护。

我们发现，如果一个圆受到了另一个圆的影响导致半径小于影响的发出圆的话，这个圆不再会受到更前面圆的影响，因为受到发出圆阻隔无法继续和前面相交，否则可以在单调栈里代替发出圆，再考虑下一个发出圆对其的影响，直到半径小于某一个发出圆。

因为每个圆只会被加入一次，删除一次，因此时间复杂度线性。

## AC 代码

```
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <stack>
using namespace std;
const int N = 2e5 + 5;
int n;
struct node {
    int x;
    double r;
};
node make(int x2, double r2) {
    node res;
    res.x = x2;
    res.r = r2;
    return res;
}
stack<node> sta;
int main() {
    scanf("%d", &n);
    int x, r;
    for(int i = 1; i <= n; i++) {
        scanf("%d%d", &x, &r);
        double now = r;
        while(!sta.empty()) {
            node tmp = sta.top();
            now = min(now, (double)(x - tmp.x) * (x - tmp.x) / 4 / tmp.r);
            if(now > tmp.r) {
                sta.pop();
            } else {
                break;
            }
        }
        sta.push(make(x, now));
        printf("%.6lf ", now);
    }
    return 0;
}

```

---

## 作者：TianTian2008 (赞：1)

需要掌握单调栈算法和一点数学基础。

虽然气球是三维物体，但是所有气球都排在同一条直线上，所以可以简化为二维的问题。

考虑两个气球，气球 $1$ 的 $x$ 坐标为 $x_1$，半径为 $r_1$，气球 $2$ 的 $x$ 坐标为 $x_2$，半径为 $r_2$。

![P4697-1](https://cdn.luogu.com.cn/upload/image_hosting/2s8m330g.png)

因为两圆相切的充要条件是两圆圆心的距离等于两圆半径之和，

$\therefore \sqrt{(x_1-x_2)^2+(r_1-r_2)^2}=r_1+r_2$

$\therefore (x_1-x_2)^2+r_1^2+r_2^2-2r_1r_2=r_1^2+r_2^2+2r_1r_2$

$\therefore 4r_1r_2=(x_1-x_2)^2$

$\therefore r_2=\frac{(x_1-x_2)^2}{4r_1}$

![P4697-2](https://cdn.luogu.com.cn/upload/image_hosting/wjc2vrpr.png)

显然，第 $i$ 个气球的半径 $r_i=\min\limits_{j=1}^{i-1}\frac{(x_i-x_j)^2}{r_j}$。注意到如果气球 $1$ 和气球 $2$ 满足 $x_1<x_2$ 并且 $r_1\leqslant r_2$，则气球 $2$ 之后的气球都不会受到气球 $1$ 的影响（被气球 $2$ 挡住了）。因此考虑用单调栈维护可能对之后气球产生影响的气球。具体地，如果当前的栈顶气球的半径小于等于当前气球的半径，则把栈顶气球弹出。

到此，得出了此题的思路。

```
#include <iostream>
#include <cstdio>
using namespace std;
typedef long long ll;
typedef double db;
ll n,st[200001];
db x[200001],r[200001],ans[200001];
inline db sq(db x){return x*x;}
inline db calc(db x1,db r1,db x2){return sq(x2-x1)/r1/4;}//计算气球半径
int main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;++i) scanf("%lf%lf",&x[i],&r[i]);
	ll top=0;
	for(int i=1;i<=n;++i)
	{
		ans[i]=r[i];
		while(top>0)
		{
			ans[i]=min(ans[i],calc(x[st[top]],ans[st[top]],x[i]));
			if(ans[st[top]]<=ans[i]) --top;//当前栈顶气球不会对之后的气球产生影响，将其弹出
			else break;//栈中气球都有可能对之后的气球产生影响
		}
		st[++top]=i;//把当前气球压入栈中
	}
	for(int i=1;i<=n;++i) printf("%.4lf\n",ans[i]);//防止精度出现误差，多输出一位
	return 0;
}
```

---

## 作者：Nuyoah_awa (赞：0)

### 题目大意

$n$ 个圆依次扩大，扩大到与其它圆相交或大于规定半径时无法再扩大，问最后所有圆的半径。

### 题目分析

#### 暴力

依次考虑每个圆，将其与已定的圆计算半径，取最小。

对于两个圆，我们将两圆心连线，两圆心与 $x$ 轴作垂线，将线段平移得到直角三角形，设两圆坐标差为 $\Delta$，一圆半径为 $R$，另一圆半径为 $r$。

根据勾股定理可得 $(R - r) ^ 2 + \Delta^2 = (R + r) ^ 2$。

展开得 $R^2 - 2 \times R \times r + r^2 + \Delta^2 = R^2 + 2 \times R \times r + r^2$

化简移项得 $r = \dfrac{\Delta^2}{4 \times R}$。

于是可以 $\mathcal O(1)$ 求 $r$。

暴力的时间复杂度为 $\mathcal O(n^2)$。

#### 正解

考虑优化暴力，我们发现每个圆需要与其他所有圆求半径。

我们可以考虑如何省略一些圆，当 $\Delta > R + r$ 时，我们知道 $r$ 只会更小，于是这两个圆就不会相交了。

如果两个圆右边圆的半径大于左边圆的半径，则左边这个圆对后面的圆没有贡献，于是可以考虑单调栈。

我们用当前圆去计算最小 $r$，计算完后，如栈顶圆的半径小于该圆，弹栈，继续计算左边的圆。

否则说明栈顶圆的 $R > r$ 所以这个圆不会再向左延伸了，直接结束计算。

总的时间复杂度是线性的。

### code
```cpp
#include <iostream>
#include <cstdio>
#include <stack>
#define int long long
#define double long double

using namespace std;

const int N = 2e5 + 5;
int n, x[N];
double r[N];
stack <int> q, p;

inline double get_r(int u, int v)
{
    double D = (x[u] - x[v]);
    return (D * D) / (4 * r[u]);
}

signed main()
{
    scanf("%lld", &n);
    for(register int i = 1;i <= n;i++)
    {
        scanf("%lld%Lf", &x[i], &r[i]);
        while(!q.empty())
        {
            r[i] = min(get_r(q.top(), i), r[i]);
            if(r[i] >= r[q.top()])
                q.pop();
            else
                break;
        }
        q.push(i);
        printf("%.3Lf\n", r[i]);
    }
    return 0;
}

```

---

