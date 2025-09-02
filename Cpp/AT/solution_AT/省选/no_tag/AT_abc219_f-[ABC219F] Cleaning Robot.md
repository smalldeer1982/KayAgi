# [ABC219F] Cleaning Robot

## 题目描述

# [ABC219F] 清扫机器人

## **问题描述**

一个清扫机器人被放置在无限扩展的二维网格的方格 $(0, 0)$ 上。

给定了一个由四种类型的字符 `L`、`R`、`U`、`D` 组成的字符串程序。  
机器人根据给定的程序，依次读取每个字符，并针对每个字符采取以下行动：

1. 将机器人的当前位置设为方格 $(x, y)$
2. 根据读取的字符执行以下移动：
   - 当读取 `L` 时：向左移动到方格 $(x-1, y)$。
   - 当读取 `R` 时：向右移动到方格 $(x+1, y)$。
   - 当读取 `U` 时：向上移动到方格 $(x, y-1)$。
   - 当读取 `D` 时：向下移动到方格 $(x, y+1)$。

给定一个由 `L`、`R`、`U`、`D` 组成的字符串 $S$ 和整数 $K$。机器人执行的程序是将字符串 $S$ 重复连接 $K$ 次。

一旦机器人访问过的方格（包括机器人的初始位置 $(0, 0)$）就会被清扫。  
请输出在机器人执行程序结束后，被清扫的方格的数量。

## 样例 #1

### 输入

```
RDRUL
2```

### 输出

```
7```

## 样例 #2

### 输入

```
LR
1000000000000```

### 输出

```
2```

## 样例 #3

### 输入

```
UUURRDDDRRRUUUURDLLUURRRDDDDDDLLLLLLU
31415926535```

### 输出

```
219911485785```

# 题解

## 作者：ziyistudy (赞：9)

本文译自 [atcoder official editorial](https://atcoder.jp/contests/abc219/editorial/2664)，由于改文特别详细的讲解了做法，固本文只对一些地方做稍微修改，以便于理解。

我们用 $(0, 0) \rightarrow (x_1, y_1) \rightarrow (x_2, y_2) \rightarrow \cdots \rightarrow (x_{|S|}, y_{|S|})$ 来表示机器人的位置变换。令 $a=x_{|S|},b=y_{|S|}$。

观察到，对于机器人每轮走的第 $i$ 步，它们都应该在同一条直线上，且该直线斜率为 $\frac{a}{b}$。

形式化地，我们让 $V_i$ 为第 $i$ 轮访问的方格的集合。比如，$V_1$ 是一个由 $(0, 0), (x_1, y_1), (x_2, y_2), \cdots, (x_{|S|}, y_{|S|})$ 组成的集合，没有**重复**。我们对其中的元素任意编号。

> $V_1 = \lbrace (X_1, Y_1), (X_2, Y_2), \ldots, (X_N, Y_N) \rbrace$

这里，$N$ 是 $V_1$ 的元素个数。

那么，将 $V_1$ 中的每个元素移位 $(a, b)$ 即可得到集合 $V_2$，即机器人在第二次执行过程中访问的方格集合：

> $V_2 = \lbrace (X_1 + a, Y_1 + b), (X_2 + a, Y_2 + b), \ldots, (X_N + a, Y_N + b) \rbrace$


则我们可以推广到 $V_k$。

> $V_k = \lbrace (X_1 + (k-1)a, Y_1 + (k-1)b), (X_2 + (k-1)a, Y_2 + (k-1)b), \ldots, (X_N + (k-1)a, Y_N+ (k-1)b) \rbrace$ 

则过程如下，对于 $i = 1, 2, \ldots, N$ 来说，$(X_i, Y_i) \in V_1$ 对应的是：

- $(X_i + a, Y_i + b)$ 对应第二次执行；
- $(X_i + 2a, Y_i + 2b)$ 对应第三次执行；
- $\cdots$
- $(X_i + (k-1)a, Y_i + (k-1)b)$ 对应第 $k$ 次操作。


这里，对于 $i = 1, 2, \ldots, N$，让：

> $d_i$ := （最小整数 $j$ ，使得 $(X_i+ja, Y_i+jb) \in V_1$ ）

如果不存在这样的整数 $j$，则 $d_i := \infty$。

然后，像刚刚一样，关注 $(X_i, Y_i) \in V_1$：

- 在第一次执行中，它**第一次**访问了方格 $(X_i, Y_i)$；
- 在第二次执行中，它**第一次**访问了方格 $(X_i + a, Y_i + b)$；
- 在第三次执行中，它**第一次**访问了方格 $(X_i + 2a, Y_i + 2b)$；
- $\cdots$
- 在 $d_i$ 次执行中，它**第一次**访问了方格 $(X_i + (d_i-1)a, Y_i + (d_i-1)b)$。

然而，对于 $(d_i+1)$ 次执行和之后的执行：

- 它在 $(d_i+1)$ 次执行过程中访问了方格 $(X_i + d_ia, Y_i + d_ib)$，但**这不是它第一次访问该方格**。  
	（根据 $d_i$ 的定义：$(X_i + d_ia, Y_i + d_ib) \in V_1$。所以它在第一次执行时已经访问过）。

- 它在执行 $(d_i+2)$ 次执行时访问了方格 $(X_i + (d_i+1)a, Y_i + (d_i+1)b)$，但**这不是它第一次访问该方格**。  

- 它在 $(d_i+3)$ 次执行时访问了方格 $(X_i + (d_i+2)a, Y_i + (d_i+2)b)$，但**这不是它第一次访问该方格**。  

- $\cdots$

等等。

因此，在对于字符串 $S$ 执行 $K$ 次的时候，$(X_i, Y_i)$ 将一个未访问过的方格变为访问过的方格 $\min(d_i, K)$ 次。

因此，本题答案为：

> $\displaystyle\sum_{i = 1}^N \min(d_i, K)$

所以，这个问题转化为如何找到数组 $d_i$，现在我们来解决这个问题。

如果 $a = b = 0$，我们可以看到 $d_1 = d_2 = \cdots = d_N = 1$。另外，如果 $a = 0, b \neq 0$，我们可以交换 $X$ 坐标和 $Y$ 坐标来假设 $a \neq 0$，因此我们在下文中假设 $a \neq 0$。

首先，对于每个 $i = 1, 2, \ldots, N$ 我们计算：

> $q_i = \left\lfloor \displaystyle\frac{X_i}{a} \right\rfloor$
>
> $s_i = X_i - q_i a$
>
> $t_i = Y_i - q_i b$

并根据 $(s_i, t_i)$ 将 $V_i$ 中的元素分组。(我们定义当且仅当 $(s_i, t_i) = (s_j, t_j)$ 时，$(X_i, Y_i)$ 和 $(X_j, Y_j)$ 属于同一个组）。

对于任意 $1 \leq i, j \leq N$ 、

> $(s_i, t_i) = (s_j, t_j) \Leftrightarrow (X_j, Y_j) = (X_i + (q_j-q_i)a, Y_i + (q_j-q_i)b)$

因此，通过按 $q_i$ 对每组元素进行排序，我们可以在总共花费 $\mathrm{O}(|S|\log|S|)$ 的时间内，为每个 $i = 1, 2, \ldots, N$ 找出 $d_i$ 的值。

因此，我们总共可以用 $\mathrm{O}(|S|\log|S|)$ 的时间来解决这个问题。

[code](https://atcoder.jp/contests/abc219/submissions/51467601)

---

## 作者：Licykoc (赞：7)

设 $n$ 表示 $S$ 的长度，首先按照 $S$ 进行一次模拟，即得到 $(0, 0) \to (x_1, y_1) \to (x_2, y_2) \to \cdots \to (x_n, y_n)$。

设 $a = x_n, b = y_n$，并设 $P_i$ 记录第 $i$ 次操作经过的点集。

> $P_1 = \{(0, 0), (x_1, y_1), \cdots, (x_n, y_n)\}$

容易发现之后每一次经过的点集都是 $P_1$ 中的点偏移若干个 $(a, b)$，即：

> $P_i = \{(0 + (i - 1)a, 0 + (i - 1)b), (x_1 + (i - 1)a, y_1 + (i - 1)b), \cdots, (x_n + (i - 1)a, y_n + (i - 1)b)\}$

答案就是求 $|P_1 \cup P_2 \cup \cdots \cup P_n |$。

将 $P_1$ 中的点集扔到二维平面上，发现会重复的点都在某条斜率为 $\dfrac{b}{a}$ 的直线上。取出该直线上的两个点 $(x_i, y_i), (x_j, y_j)$ 满足 $x_i \bmod a = x_j \bmod a$。它们中的一个在 $|\dfrac{x_j - x_i}{a}|$ 次操作后会被第二次访问到，也就是说，它们对答案的贡献为 $\min(|\dfrac{x_j - x_i}{a}|, K)$。

所以做法就是找到每一条直线，对于其上 $x \bmod a$ 相同的点对计算贡献。

具体实现时有些细节：

- 如果 $a=b=0$，直接输出 $|P_1|$。

- 如果 $a=0$，交换两维。

- 如果 $a \lt 0$，取反所有的 $x$。

最后用 `map` 存下每条直线即可。

时间复杂度 $O(n \log n)$。

---

## 作者：QuQi_ZhouSi (赞：4)

~~[更不好的阅读体验](http://blog.godcraft.net/post/ATabc219f)~~
## 题解思路
1. **读取输入**：首先读取指令字符串 $S$ 及循环次数 $k$。
2. **模拟运动**：根据指令字符串 $S$ 模拟机器人在平面上的运动，记录每一个到达的位置。
3. **特判起点**：如果最终回到起点 $(0, 0)$，说明这是一个周期运动，每一个周期内的所有位置都会被清扫一次，最终结果为 $k$ 乘以一个周期内清扫的位置数。
4. **坐标处理**：
    - 如果最终横坐标或纵坐标为 $0$，则可以通过交换坐标来处理。
    - 如果最终横坐标为负值，可以通过取反处理为正值。
5. **循环计算**：
    - 计算在多次循环后被清扫的格子数。
    - 使用哈希表记录每个位置在周期内被到达的时间点，通过排序和差分计算得到所有被清扫的格子数。
6. **输出结果**：输出最终被清扫的格子数。

## 代码实现

```c++
#include <bits/stdc++.h>
#define int long long//讨论区疑似有见祖宗人
using namespace std;
int read() {
    int sz = 0, zf = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') zf = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        sz = sz * 10 + (ch - '0');
        ch = getchar();
    }
    return sz * zf;
}

int k, x, y, ans;  // 定义变量：循环次数k，当前位置x，y，结果ans
string s;  // 定义指令字符串s
vector<pair<int, int>> v;  // 存储机器人经过的所有位置
map<pair<int, int>, vector<int>> mp;  // 存储经过每个位置的时间点

signed main() {
    ios::sync_with_stdio(0);  // 加速输入输出
    cin.tie(0); cout.tie(0);  // 同上

    cin >> s;  // 读取指令字符串
    k = read();  // 读取循环次数
    v.push_back({x, y});  // 初始位置(0, 0)

    // 模拟机器人运动
    for (int i = 0; i < s.size(); i++) {
        switch (s[i]) {
            case 'U': y--; break;  // 向上移动
            case 'D': y++; break;  // 向下移动
            case 'L': x--; break;  // 向左移动
            case 'R': x++; break;  // 向右移动
        }
        v.push_back({x, y});  // 记录当前位置
    }

    // 处理特殊情况：如果最终回到起点(0, 0)
    if (x == 0 && y == 0) {
        map<pair<int, int>, int> mp;  // 用于记录每个位置
        for (int i = 0; i < v.size(); i++) mp[v[i]] = 1;  // 记录位置
        cout << mp.size();  // 输出被清扫的格子数
        return 0;
    } else if (x == 0) {  // 如果最终横坐标为0，交换坐标处理
        swap(x, y);
        for (int i = 0; i < v.size(); i++) swap(v[i].first, v[i].second);
    } else if (x < 0) {  // 如果最终横坐标为负，取反处理为正
        x = -x;
        for (int i = 0; i < v.size(); i++) v[i].first = -v[i].first;
    }

    // 循环计算被清扫的格子数
    for (int i = 0; i < v.size(); i++) {
        int nx = (v[i].first % x + x) % x;
        int ny = (v[i].second - y * (v[i].first - nx) / x);
        mp[{nx, ny}].push_back((v[i].first - nx) / x);
    }

    for (auto it : mp) {
        sort(it.second.begin(), it.second.end());
        for (int i = 0; i < it.second.size() - 1; i++) 
            ans += min(k, it.second[i + 1] - it.second[i]);  // 计算最小步数
        ans += k;  // 累加总步数
    }

    cout << ans;  // 输出结果
    return 0;
}
```
###### 有一个[繁体版本](https://www.luogu.com.cn/paste/rbb6djpi)哦，想看來看捏

---

## 作者：mojoege (赞：4)

## 题意
[题目传送门](https://www.luogu.com.cn/problem/AT_abc219_f)

[题目传送门](https://atcoder.jp/contests/abc219/tasks/abc219_f)
## 分析

先模拟一遍样例，我们发现在第二次操作的时候画出来的路径就是第一次操作的路径往一个方向偏移了一个值，也就是每一次的起点都偏移了相同的 $(x,y)$ 值。

具体的，设第一轮运动（$x_0=0,y_0=0$）的点集为 $P=\{(x_0,y_0),(x_1,y_1),\cdots,(x_n,y_n)\}$，显然增量 $\Delta x=x_n-x_0=x_n$ 同理 $\Delta y=y_n$。

接着我们可以再手搓一点样例出来，发现路径中的每一个点也是相较于上一次操作偏移了 $(\Delta x,\Delta y)$。

~~这里就可以特判骗一点分~~：如果 $\Delta x = 0$ 且 $\Delta y = 0$，直接输出一轮有多少个点。

虽然这个结论看起来很没用，实际上这对之后计算很有帮助。很容易发现我们得减去重复的值。~~接下来就开始抽象了~~。

对于重复点的计算，因为我们有上面“每一次的增量都是固定的”这一说法，那重复的点也是固定的，带入一次函数，每组重复的点组成的直线的斜率一定是 $\frac{\Delta y}{\Delta x}$（这里增量固定，所以一组重复的点一定是在一条直线上的）。

但是我们发现重复次数依旧不好计算，那我们只能算贡献了，分成两种点：

- 到一个时间以后都没有贡献。**同一条直线上**前一个点走过的路被当前点走过了，贡献就是这两个点之间要走的次数。具体的，$(x_i,y_i)=(x_j+d\Delta x,y_j+d\Delta y)$ 时， $x_j$ 的贡献就是 $d=\frac{x_i-x_j}{\Delta x}$（每一次 $x$ 运动 $\Delta x$ 个单位距离）。
![](https://cdn.luogu.com.cn/upload/image_hosting/we37nuts.png)

- 一直有贡献。**每条直线**最后一个点（最远的那个点）移动的时候肯定是没有点拦着的，直接让 $ans$ 加上运动次数 $k$ 就好了。
![](https://cdn.luogu.com.cn/upload/image_hosting/u2mrpneo.png)

事实上，只要统计第一次移动出现过的点的贡献（第一种），其他的点要么是以后都有贡献的点，要么是已经不可能再有贡献的点了。

这道题做完了……吗？现在只剩最后一个问题，怎么记录同一条直线？稍微学过高中直线方程的都知道，只要知道斜率、一个点，就能确定一条直线，这个点就可以选在这条直线出现的第一个点，也就是 $(x \bmod \Delta x,y\bmod \Delta y)$，直接用 `map` 去存这个点到所在直线上的点运动的次数，然后给这些次数排个序再去统计答案。

为了便于计算我们需要更改下不满足条件的 $(\Delta x,\Delta y)$:

- 当 $\Delta x=0$ 时，交换 $\Delta x$ 和 $\Delta y$（在模的时候便于操作），记得交换每一个点的 $(x,y)$。
- 当 $\Delta x< 0$ 时，直接取反 $\Delta x$，同时取反每一个点的 $x$。

上面我们交换了 $\Delta x=0$ 的时候的这两个值，那么 $y \bmod \Delta y$ 时我们只能根据斜截式方程去转化一下，变成 $y-\Delta y \cdot \frac{x - x \bmod \Delta x}{\Delta x}$，之后正常操作。

## 代码
```cpp
#include  <bits/stdc++.h>
#define int long long
using namespace std;

int k, x, y, ans;
string s;
vector<pair<int, int>> v;

signed main(){
    cin >> s >> k;
    v.push_back({x, y});//不要忘记原点
    for (int i = 0; i < s.size(); i++){//统计第一次的路径
        if (s[i] == 'U') y--;
        if (s[i] == 'D') y++;
        if (s[i] == 'L') x--;
        if (s[i] == 'R') x++;
        v.push_back({x, y});
    }
    if (x == 0 && y == 0){//特判原地不动
        map<pair<int, int>, int> mp;
        for (int i = 0; i < v.size(); i++) mp[v[i]] = 1;
        return cout << mp.size(), 0;
    }
    if (x == 0){//特判x = 0
        swap(x, y);
        for (int i = 0; i < v.size(); i++) swap(v[i].first, v[i].second);//记得掉换
    }
    if (x < 0){//特判 x < 0
        x = -x;
        for (int i = 0; i < v.size(); i++) v[i].first = -v[i].first;
    }
    map<pair<int, int>, vector<int>> mp;
    for (int i = 0; i < v.size(); i++){
        int nx = (v[i].first % x + x) % x;//记得这样取模，避免出现负数炸掉
        int ny = (v[i].second - y * (v[i].first - nx) / x);//斜截式方程
        mp[{nx, ny}].push_back((v[i].first - nx) / x);//记录从直线第一个点经过多少次操作能来到当前节点，也就是贡献
    }
    for (auto it : mp){
        sort(it.second.begin(), it.second.end());//次数排序
        for (int i = 0; i < it.second.size() - 1; i++) ans += min(k, it.second[i + 1] - it.second[i]);//统计两个点之间走的次数
        ans += k;//一直都有贡献的点
    }
    cout << ans;
    return 0;
}
```

---

## 作者：2020luke (赞：4)

# [[ABC219F] Cleaning Robot](https://www.luogu.com.cn/problem/AT_abc219_f) 题解

## 思路解析

**要点：将整个图拆分成每一轮的每一个点单独考虑贡献。**

首先看到 $k \le 10^{12}$ 发现不能直接枚举 $k$ 轮，于是开始找每一轮的规律。首先可以知道，如果操作固定，那么起点和路径上每一个点以及终点的相对位置不会改变。也就是说每一轮的起点之间的相对位置，我们记作每一轮的偏移量，其实是不会改变的。若不理解，请看下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/i83ahlfv.png)

其中红线代表经过的位置和线路，黑线代表起点与各个点之间的偏移量。由此可见不论如何移动起点，它移动所形成的形状是不会改变的。

了解完这个规律之后就很好理解了。我们可以先做出来第一次所经过的所有点的位置，由于起点和终点的偏移量不会改变的特点，我们在以后每一轮的这一个操作完后的位置，和上一轮进行完这一个操作之后的位置，偏移量也是不会改变的。若不理解，请看下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/15oid89u.png)

其中红点表示第一次经过的点，蓝点表示第二次经过的点，黑线表示第一轮的当前次序遍历到的点与第二轮的当前次序遍历到的点之间的偏移量。可以发现每一个点的位置与下一轮的位置之间的偏移量也是不会变的，而这个偏移量其实就是每一轮的起点和终点的偏移量，因为每一轮的开始都是上一轮的结束，所以每一轮的起点的偏移量是固定的，那么其他点的偏移量也是固定的。所以这时我们发现，有一些点在下一轮到达了未经过的位置，它对答案造成了贡献（如上图最右边的两个蓝色点），而有一些则又经过了之前已经经过了的其他点，就对答案没有贡献（如上图的其他蓝色点）。

接下来我们则需要思考第一轮中有哪些点对答案有贡献，贡献分别是多少。我们考虑下面这幅图。

![](https://cdn.luogu.com.cn/upload/image_hosting/aviab8tl.png)

红，蓝，绿点分别表示第一，二，三轮经过的点。我们发现后两轮造成了贡献的点只有三个，分别是 $(0,0),(0,2),(1,2)$ 这三点。而其中 $(0,0)$ 点只造成了 $1$ 次贡献，并且可以发现该点以后再也不会造成任何贡献。原因是如果我们把一个点增加 $1 \to k$ 次偏移量的每一种情况都列举出来，如果中途的第 $i$ 个点在第一轮就被遍历过了，那么第 $i \to k$ 这些所有的轮数里当前点都不会再有任何贡献。换句话说，当前点对答案的贡献就是 $i$，因为还有第一轮造成的贡献。

明确了答案统计的方式之后，我们需要计算的值就是对于第一次移动遍历到的每一个点，找到加上 $i$ 轮偏移量后会与第一轮经过的某一个点重合的最小的 $i$。由于每一轮之间的偏移量不变，所以当前点经过 $k$ 轮移动后所有的点都在同一条斜率为 $\frac{x}{y}$ 的直线上，其中 $x,y$ 分别是偏移量的 $x,y$ 轴。所以问题就变成了对于每一个点，找到经过当前点的斜率为 $\frac{x}{y}$ 的直线上往后找与当前点最接近的点，计算当前点需要经过多少轮的偏移量才能到达这个点，也就是将距离除以偏移量的值。这里的点指第一轮中经过的所有点。这样我们就可以把每一条直线给找出来，对于每一条直线都用一个 `vector` 存下这条直线上所有的点与起点之间经过的轮数，设 $a,b$ 分别为当前点的 $x,y$ 轴，起点就是 $(a \mod x,b-y\times\lfloor a/x \rfloor)$。最后的答案就是对于每一条直线，设 $v_{i}$ 为当前直线上的第 $i$ 个点，求 $\sum_{i=1}^{size-1} \min(v_{i+1}-v_{i},k)+k$，因为如果相差轮数大于 $k$，那么对答案就没有影响，同时最后一个点不会被阻挡，所以要加上 $k$。

最后就是几个需要注意的小细节：

- 若 $x=0,y=0$，就说明之后的每一轮都不会有新的贡献，直接输出第一轮的贡献即可。
- 若 $x=0,y \ne 0$，为了防止 $a \mod x$ 没有结果，我们交换 $x,y$ 和所有的 $a,b$。
- 若 $x<0$，为方便计算，我们取反 $x$ 和所有的 $a$。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define PII pair<int, int>
#define fir first
#define sec second
string str;
long long k;
vector< PII > v;
int dx[150], dy[150];
void init() {
	dx['U'] = -1;
	dx['D'] = 1;
	dy['L'] = -1;
	dy['R'] = 1;
}
signed main() {
	init();
	cin >> str >> k;
	int x = 0, y = 0;
	v.push_back({x, y});
	for(int i = 0; i < (int)str.size(); i++) {
		x += dx[(int)str[i]], y += dy[(int)str[i]];
		v.push_back({x, y});
	}
	sort(v.begin(), v.end());
	v.erase(unique(v.begin(), v.end()), v.end());
	if(x == 0 && y == 0) {
		cout << v.size(); return 0;
	}
	if(x == 0) {
		swap(x, y);
		for(auto &it : v) swap(it.fir, it.sec);
	}
	if(x < 0) {
		x = -x;
		for(auto &it : v) it.fir = -it.fir;
	}
	map< PII, vector<int> > mp;
	for(auto it : v) {
		int nx = it.fir, ny = it.sec;
		int mod = (nx % x + x) % x;
		mp[{mod, ny - (long long)y * (nx - mod) / x}].push_back((nx - mod) / x);
	}
	long long ans = 0;
	for(auto it : mp) {
		sort(it.sec.begin(), it.sec.end());
		for(int i = 0; i <= (int)it.sec.size() - 2; i++) {
			ans += min(k, (long long)it.sec[i + 1] - it.sec[i]);
		}
		ans += k;
	}
	cout << ans;
	return 0;
}
```

---

## 作者：Saint_ying_xtf (赞：3)

我们先把第一轮中每一个点的点处理出来。变成一个 pair 数组。

如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/7kpijz2q.png)

黑色点是原始的点。

我们设一开始第一个点为 $(0,0)$，然后最后一个点为 $(dx,dy)$。那么我们就可以发现对于每一轮，他们之间的差都是一个固定的偏移量，偏移量是 $(dx,dy)$，也就是第 $i$ 轮的最后一个点是 $(dx \times i,dy \times i)$。

如果这个点第一次出现是在 $(x,y)$。那么他后面对应的 $(x+(i-1) \times dx,y + (i-1)\times dy)$。

图中只画了两轮。

第二轮便是蓝色的点。

分别对应着他们的编号。

由于每一个点下一轮的偏移量都是相同的，于是，我们发现对于这个点，之后都是形成了一个斜率为 $\dfrac{dx}{dy}$ 的一条直线。然后我们只需要对每一条斜线上去判断。

由于所有的线都是斜率相同，所以不用考虑斜率，将他（斜率）默认为 $\dfrac{dx}{dy}$ 即可。

我们课以将每一块（相当于每轮的区域）切割出来，如下图，被切成了若干块。

每一个点在不同轮数中在他们自己对应的块内相对位置都是相同的。

例如点 $3$ 在它的那一块的相对位置，就是两个箭头所指向。也就是对于他们这个块内第一个出现的点的位置偏移量都是一样的。

![](https://cdn.luogu.com.cn/upload/image_hosting/r9vs73vh.png)

对于 $(x,y)$ 他所在的斜线就是编号为 $(x \mod dx,y - b \times \left\lfloor\dfrac{x}{dx}\right\rfloor $ 的斜线上，也就是 $(x \mod dx,y - dy \times \dfrac{x-x \mod dx}{dx}$（注意，这个编号是有两个数值，你可以开一个 pair 来作为映射的键）。

因为，重复，仅仅有可能是一条斜线上重复，不可能是，另一条直线上与这条直线重复，毕竟两条斜率相同的直线不可能是有交点，必须是平行的，不然他们就不是斜率相同的。

所以我们只需要针对相同编号的数，进行计算，相同编号，代表着，就是在一条直线上。

所以我们对于每一个 $(x,y)$。将编号为 $(x \mod dx,y - b \times \dfrac{x-x \mod dx}{dx}$) 的直线，存储一下 $\left\lfloor\dfrac{x}{dx}\right\rfloor$，$\left\lfloor\dfrac{x}{dx}\right\rfloor$ 代表什么呢？代表的就是这个点所在块的编号。

很显然，对于直线上所有点的块编号，去重排序后，第 $i$ 个和第 $i-1$ 个只差，都是他们之间会出现的个数，注意，有可能会大于 $k$，这显然不可能，因为最多 $k$ 轮。还要与 $k$ 取最小值。

假设这个编号内所有点的块编号都存在了 $v$ 数组中，那么答案要加上 $\sum \min(k,v_i - v_{i-1})$。

时间复杂度是 $O(n \log n)$。

代码实现中还有一些细节。

- 由于所有的编号都得要排序和去重，所以我们选额开 set 来存储。

- 如果 $dx$ 和 $dy$ 都是 $0$，我们可以直接把一开始统计的数量（去重后）输出。

- 如果 $dx$ 是 $0$，那么他就不能做除数，所以我们要交换一下 $dx$ 和 $dy$，是没有区别的，只不过是相当于把整个图旋转了一下。（旋转后的 $dx$ 不可能 $0$，因为如果 $dx$ 和 $dy$ 都等于 $0$，那么就直接被之前的条件判掉了）。所有的点也得交换一下。

- 如果 $dx < 0$，那么也不好搞，所以把他换成整数，对应的所有存储的坐标也是乘个 $-1$。

- 取模记得注意负数情况。

AC 的代码：[link](https://atcoder.jp/contests/abc219/submissions/51111545)。

---

## 作者：MortisM (赞：1)

挺妙的一道题，充分的体现了换个角度看问题的重要性。建议读者先看前面的部分，自己想后面的处理细节。

**提示：观察每个点的运动轨迹。**

如果你专注于整个图形的轨迹来看的话，那就会发现无法得到任何有用的结论。但是如果你专注于一个特定的点的话，很显然，它每次都会运动 **相同的增量**。

形式化地，设第一轮运动组成的点集为（$x_0=0,y_0=0$）
$$
P_1=\{(x_0,y_0),(x_1,y_1),\cdots,(x_n,y_n)\}
$$

设运动一轮的增量为 $a=\Delta x,b=\Delta y$，其中易得 $\Delta x=x_n,\Delta y=y_n$（因为一开始的点是 $(0,0)$）。

那么运动完第 $i$ 轮的点集为：
$$
P_i=\{(x_0+(i-1)a,y_0+(i-1)b),(x_1+(i-1)a,y_1+(i-1)b),\cdots,(x_n+(i-1)a,y_n+(i-1)b)\}
$$

答案为 $|P_1\cup P_2\cup\cdots\cup P_k|$。

--------------

后面的部分建议读者自行思考。

此时就可以推断出每一个点运动轨迹都是直线，并且斜率都为 $\displaystyle\frac{b}{a}$。

唯一需要处理的问题就是有些点可能走着走着就到了另一个点，这样就 **重叠** 了，贡献不能算 $k$。

考虑什么样的点会重叠，显然需要满足 $(x_1,y_1)=(x_0+da,y_0+db)$。

那么怎样处理呢？实际上可以用一个 `map` 来维护 $x\bmod a$ 和 $\displaystyle y-b\cdot\frac{x-x\bmod a}{a}$ 即可，理由就拿斜截式一次函数方程推一下就行，非常简单。

这样就可以把所有都压在一个 `vector` 里，并对它们的 $d$ 排序，可以得到答案为 $\sum\min(\text{相邻两个的 d 之差},k)+k$。

时间复杂度 $\mathcal{O}(n\log n)$。

----

下面有几个实现代码需要注意的细节：

+ 若 $a=0,b=0$，则直接用 `map` 统计答案。
+ 若 $a=0$，则将 $a,b$ 交换。
+ 若 $a<0$，则将 $a$ 取反。
+ 对 $a$ 取模注意 $x$ 为负数的情况。

[代码](https://atcoder.jp/contests/abc219/submissions/37748215)。

---

## 作者：daniEl_lElE (赞：1)

首先先找出循环节的位移，即操作一个循环节会让原位置移动 $(\Delta x,\Delta y)$。

$\Delta x=\Delta y=0$ 特判一下。

否则，我们对于每个在第一次经过的点 $(x',y')$，就会经过 $(x'+\Delta x\times k,y'+\Delta y\times k)$。

将 $(x',y')$ 归到一个形如 $(x'',y'')=(x'+\Delta x\times k,y'+\Delta y\times k)$ 且 $0\leq x<|\Delta x|$ 的位置，然后算出其对应的能在的 $(x'+\Delta x\times k,y'+\Delta y\times k)$ 的 $k$ 的区间。

对于每个 $0\leq x<|\Delta x|$ 的有经过的点归到的位置，将其能经过的 $k$ 区间取并集并求和即可。

总复杂度 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1)
#define add(i,j) ((i+j>=mod)?i+j-mod:i+j)
using namespace std;
map<int,int> mp[500005];
map<pair<int,int>,int> mpp;
vector<pair<int,int>> vc[200005];
int cnt;
signed main(){
	string s; cin>>s;
	int k; cin>>k;
	int nowx=250000,nowy=250000;
	int tot=1;
	mp[nowx][nowy]=1;
	for(int i=0;i<s.size();i++){
		if(s[i]=='L') nowy--;
		if(s[i]=='R') nowy++;
		if(s[i]=='U') nowx--;
		if(s[i]=='D') nowx++;
		if(!mp[nowx][nowy]) mp[nowx][nowy]=1,tot++;
	}
	if(nowx==250000&&nowy==250000){
		cout<<tot;
		return 0;
	}
	int cycx=nowx-250000,cycy=nowy-250000;
	nowx=250000,nowy=250000;
	for(int i=0;i<s.size();i++){
		int rx,ry,num;
		if(!cycx){
			rx=nowx; ry=nowy%cycy; num=nowy/cycy;
		}
		else if(!cycy){
			rx=nowx%cycx; ry=nowy; num=nowx/cycx;
		}
		else{
			num=min(nowx/cycx,nowy/cycy);
			rx=nowx-num*cycx; ry=nowy-num*cycy;
		}
		if(!mpp[make_pair(rx,ry)]) mpp[make_pair(rx,ry)]=++cnt;
		vc[mpp[make_pair(rx,ry)]].push_back(make_pair(num,num+k+(i==0)-1));
		if(s[i]=='L') nowy--;
		if(s[i]=='R') nowy++;
		if(s[i]=='U') nowx--;
		if(s[i]=='D') nowx++;
	}
	int ans=0;
	for(int i=1;i<=cnt;i++){
		sort(vc[i].begin(),vc[i].end());
		int nowm=-1e18;
		for(auto v:vc[i]){
			ans+=max(0ll,v.second-max(v.first,nowm+1)+1);
			nowm=max(nowm,v.second);
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：FRZ_29 (赞：0)

# AtCoder abc219_f Cleaning Robot
题目传送门：[AtCoder](https://atcoder.jp/contests/abc219/tasks/abc219_f)，[luogu](https://www.luogu.com.cn/problem/AT_abc219_f)  
[也许更好的阅读体验](https://www.cnblogs.com/FRZ29/p/18335853)

## 思路  
设集合 $V_i$ 表示第 $i$ 次执行时经过的点的集合。则答案即为这 $k$ 次操作产生的集合的并集的大小（元素个数）。

每个集合的大小均为 $|S|$，所以题目的关键为如何处理每次操作后重复的部分。

假设第一次执行程序后（即运行一次字符串）后扫地机器人位于 $(a, b)$，之后的第 $2,3,\cdots,k$ 次后扫地机器人位于 $(2a,2b),(3a,3b),\cdots,(ka, kb)$，它们恰好都在一条斜线上。由此启发，每一次执行后对应的点应该在同一斜线上。

因为每一次执行后对应的点应该在同一斜线上，所以如有重合，那么一定是位于同一斜线上的。  
同样假设第一次执行程序后扫地机器人位于 $(a, b)$，则每次操作后对应点的偏移量就是 $(a, b)$。

设一个种类为在同一条斜线上，且可以通过移动互相到达的点。容易发现，设 $(m, n)$ 为该种类的点的坐标，则 $(m \bmod a, n - \left \lfloor \dfrac{m}{a} \right \rfloor \times b)$ 对于所有该种类的点相同，因为 $(m \bmod a, n - \left \lfloor \dfrac{m}{a} \right \rfloor \times b)$ 为该种类第一个出现的点。

设一个点 $(x,y)$，将它存在对应的种类（$S$）之中，每次存它从第一次的位置要经过几次偏移到达现在的位置（为权值），即为 $\left\lfloor\dfrac{m}{a}\right\rfloor$。将种类内的点按权排序，那么答案即为两次之间的间隔之和（$\sum_{i = 2}^n(S_i - S_{i - 1})$），再加上最后一点的 $k$ 次偏移。

## 细节
1. 如果第一次偏移后机器人位于 $(0, 0)$，那么答案即为第一次偏移机器人经过的点的个数。
2. 若偏移后的 $a = 0$，$\left\lfloor\dfrac{m}{a}\right\rfloor$ 不好处理，可以将整张图的横纵坐标对换。
3. 如果 $a \lt 0$,同样不好处理，把整张图的横轴正负对换一下。
4. 注意对负数取模。
## 代码
```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <map>
typedef long long LL;

using namespace std;

const int N = 2e5 + 5;

#define FI first
#define SE second
#define PB push_back
#define PII pair<LL, LL>
#define LF(i, __l, __r) for (int i = __l; i <= __r; i++)
#define RF(i, __r, __l) for (int i = __r; i >= __l; i--)

LL k, ans;
char s[N];
LL len, nx, ny, id;
map< PII, LL> mp;
vector< PII > p;
vector<LL> vec[N];

int main() {
    scanf("%s%lld", s, &k);
    len = strlen(s);
    mp[{0, 0}] = 1;
    p.PB({0, 0});

    LF(i, 0, len - 1) {
        if (s[i] == 'L') nx -= 1;
        if (s[i] == 'R') nx += 1;
        if (s[i] == 'U') ny -= 1;
        if (s[i] == 'D') ny += 1;
        mp[{nx, ny}] = 1;
        p.PB({nx, ny});
    }

    if (nx == 0 && ny == 0) {
        printf("%d", mp.size());
        return 0;
    }

    if (nx == 0) {
        swap(nx, ny);
        LF(i, 0, p.size() - 1) swap(p[i].FI, p[i].SE);
    }

    if (nx < 0) {
        nx = -nx;
        LF(i, 0, p.size() - 1) p[i].FI = -p[i].FI;
    }

    mp.clear();

    for (auto to : p) {
        LL x = (to.FI % nx + nx) % nx, y = to.SE - ny * ((to.FI - x) / nx);
        if (!mp[{x, y}]) mp[{x, y}] = ++id;
        vec[mp[{x, y}]].PB((to.FI - x) / nx);
    }

    LF(i, 1, id) {
        sort(vec[i].begin(), vec[i].end());
        LF(j, 1, vec[i].size() - 1) ans += min(k, vec[i][j] - vec[i][j - 1]);
        ans += k;
    }

    printf("%lld", ans);
    return 0;
}
```

> “日拱一卒无有尽，功不唐捐终入海。”——《法华经》

---

## 作者：C_Pos_Princess (赞：0)

## 题解

这个题其实想清楚轨迹是什么样子的基本上就做完了。

首先，他肯定是一个不停循环走同一种形状的函数，每一遍遍历 $S$ 结束都会有一个固定的增量，我们记为 $(\Delta x,\Delta y)$，且不同循环中的对应点所连直线的斜率不变，为 $\frac{\Delta y}{\Delta x}$。

其实这样就可以开算了，但是我们注意到，在同一条直线上的点可能会出现重复的情况，而这个条件其实很好想，假设（在同一条直线上）有两个点 $(x_i,y_i)$ 和 $(x_j,y_j)$，当且仅当 $x_i \equiv x_j \pmod{\Delta x}$ 且 $y_i \equiv y_j \pmod{\Delta y}$。

## 完整代码

```

ll k, x, y, ans;
string s;
vector<pair<ll, ll> > v;


int main() {
	cin >> s;
	read(k);
	v.push_back({x, y});
	int len = s.length();
	for (int i = 0; i < len; i++) {
		if (s[i] == 'U') y--;
		if (s[i] == 'D') y++;
		if (s[i] == 'L') x--;
		if (s[i] == 'R') x++;
		v.push_back({x, y});
	}

	if (x == 0 && y == 0) {
		map<pair<ll, ll>, ll >mp;
		for (int i = 0; i < v.size(); i++) mp[v[i]] = 1;
		write(mp.size());
		return 0;
	}

	if (x == 0) {
		swap(x, y);
		for (int i = 0; i < v.size(); i++) swap(v[i].first, v[i].second);
	}
	if (x < 0) {
		x = -x;
		for (int i = 0; i < v.size(); i++) v[i].first = -v[i].first;
	}

	map<pair<ll, ll>, vector<ll> >mp;

	for (int i = 0; i < v.size(); i++) {    //所有的点 
		int xx = (v[i].first % x + x) % x;
		int yy = (v[i].second - y * (v[i].first - xx) / x);
		mp[ {xx, yy}].push_back((v[i].first - xx) / x);   //第一个点走了几次 
	}

	for (auto it : mp) {
		sort(it.second.begin(), it.second.end());
		for (int i = 0; i < it.second.size() - 1; i++)
			ans += min(k, it.second[i + 1] - it.second[i]);
		ans += k;
	}
	write(ans);

	return 0;
}


```

---

## 作者：TernaryTree (赞：0)

模拟赛题，场切了，感觉不是很难，完全没有 at *2542 的难度。

考虑先只跑一遍，去重之后得到一个点集 $S$。设跑一遍最后到达 $(dx,dy)$，则显然跑第二遍的时候到达的点集为 $\{(x+dx,y+dy)\mid (x,y)\in S\}$，以此类推，第 $k$ 遍到达的点集就是  $\{(x+(k-1)dx,y+(k-1)dy)\mid (x,y)\in S\}$。我们需要求出这 $k$ 个点集的并的大小，转化一下，对每个 $(x,y)\in S$，定义其“拓展集”为 $\{(x+i\times dx,y+i\times dy)\mid 0\le i\lt k\}$，则原问题等价于对所有点的“拓展集”求并的大小。

我们会发现，假设一些点的“拓展集”有交，则它们在一条直线上，且直线的斜率始终为 $\dfrac{dy}{dx}$。由此，我们可以计算每个点与 $(dx,dy)$ 的叉积，将叉积相等的划分为同一个等价类，每个等价类是独立的。

当 $dx\neq 0$ 时，可以将一个等价类的所有点按模 $|dx|$ 的值再划分若干个小等价类，那么我们可以在小等价类里对横坐标相邻的两个点计算出贡献，这个是好算的。

当 $dx=0$ 时，$dy=0$ 是好做的，否则沿用之前做法，按 $|dy|$ 分类即可。

```cpp
#include <bits/stdc++.h>
#define int long long
#define fs first
#define sc second
#define ls (u << 1)
#define rs (u << 1 | 1)
#define mid ((l + r) >> 1)
#define lc ls, l, mid
#define rc rs, mid + 1, r
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define per(i, r, l) for (int i = (r); i >= (l); --i)
#define gc getchar
#define pc putchar

using namespace std;
using pii = pair<int, int>;
using vi = vector<int>;

const int maxn = 1e6 + 10;
const int inf = 1e18;
const bool multidata = 0;

template<typename T = int>
T read() {
	T x = 0, f = 1; char c = gc();
	while (c < '0' || c > '9') { if (c == '-') f = -f; c = gc(); }
	while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = gc();
	return x * f;
}

template<typename T = int>
void write(T x) {
	if (x < 0) pc('-'), x = -x;
	if (x < 10) return void (pc(x + '0'));
	write<T>(x / 10), pc(x % 10 + '0');
}

int n, k, ans = 0;
char s[maxn];
map<pii, int> bk;
pii a[maxn]; 
vector<pii> p[maxn];
unordered_map<int, int> id;
int cnt;
int lst[maxn];
int cov[maxn];
int qwq[maxn];
int gx[maxn];

void fake_main() {
	rep(i, 0, maxn - 1) lst[i] = cov[i] = inf;
	cin >> s + 1 >> k;
	n = strlen(s + 1);
	a[0] = {0, 0};
	rep(i, 1, n) {
		a[i] = a[i - 1];
		if (s[i] == 'L') --a[i].fs;
		else if (s[i] == 'R') ++a[i].fs;
		else if (s[i] == 'U') ++a[i].sc;
		else if (s[i] == 'D') --a[i].sc;
	}
	int dx = a[n].fs, dy = a[n].sc;
	if (dx < 0) {
		rep(i, 0, n) a[i].fs *= -1;
		dx = -dx;
	}
	if (dy < 0) {
		rep(i, 0, n) a[i].sc *= -1;
		dy = -dy;
	}
	sort(a, a + 1 + n);
	n = unique(a, a + 1 + n) - a - 1;
	if ((!dx && !dy) || k == 1) {
		write(n + 1);
		return;
	} else if (dx) {
		rep(i, 0, n) {
			int delta = a[i].fs * dy - a[i].sc * dx;
			if (!id.count(delta)) id[delta] = ++cnt;
			p[id[delta]].push_back({a[i].fs, i});
		}
		rep(i, 1, cnt) {
			int s = p[i].size();
			sort(p[i].begin(), p[i].end());
			per(j, s - 1, 0) {
				int d = (p[i][j].fs % dx + dx) % dx;
				if (lst[d] != inf) ans += min((lst[d] - p[i][j].fs) / dx, k);
				else ans += k;
				lst[d] = p[i][j].fs;
			}
			per(j, s - 1, 0) lst[(p[i][j].fs % dx + dx) % dx] = inf;
		}
	} else {
		rep(i, 0, n) {
			int delta = a[i].fs * dy - a[i].sc * dx;
			if (!id.count(delta)) id[delta] = ++cnt;
			p[id[delta]].push_back({a[i].sc, i});
		}
		rep(i, 1, cnt) {
			int s = p[i].size();
			sort(p[i].begin(), p[i].end());
			per(j, s - 1, 0) {
				int d = (p[i][j].fs % dy + dy) % dy;
				if (lst[d] != inf) ans += min((lst[d] - p[i][j].fs) / dy, k);
				else ans += k;
				lst[d] = p[i][j].fs;
			}
			per(j, s - 1, 0) lst[(p[i][j].fs % dy + dy) % dy] = inf;
		}
	}
	write(ans); 
}

signed main() {
//	freopen("loop.in", "r", stdin);
//	freopen("loop.out", "w", stdout);
	int T = multidata ? read() : 1;
	while (T--) fake_main();
	return 0;
}

/*
URDLD
2
*/

```

---

