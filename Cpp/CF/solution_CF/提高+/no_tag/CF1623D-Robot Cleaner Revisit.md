# Robot Cleaner Revisit

## 题目描述

The statement of this problem shares a lot with problem A. The differences are that in this problem, the probability is introduced, and the constraint is different.

A robot cleaner is placed on the floor of a rectangle room, surrounded by walls. The floor consists of $ n $ rows and $ m $ columns. The rows of the floor are numbered from $ 1 $ to $ n $ from top to bottom, and columns of the floor are numbered from $ 1 $ to $ m $ from left to right. The cell on the intersection of the $ r $ -th row and the $ c $ -th column is denoted as $ (r,c) $ . The initial position of the robot is $ (r_b, c_b) $ .

In one second, the robot moves by $ dr $ rows and $ dc $ columns, that is, after one second, the robot moves from the cell $ (r, c) $ to $ (r + dr, c + dc) $ . Initially $ dr = 1 $ , $ dc = 1 $ . If there is a vertical wall (the left or the right walls) in the movement direction, $ dc $ is reflected before the movement, so the new value of $ dc $ is $ -dc $ . And if there is a horizontal wall (the upper or lower walls), $ dr $ is reflected before the movement, so the new value of $ dr $ is $ -dr $ .

Each second (including the moment before the robot starts moving), the robot cleans every cell lying in the same row or the same column as its position. There is only one dirty cell at $ (r_d, c_d) $ . The job of the robot is to clean that dirty cell.

After a lot of testings in problem A, the robot is now broken. It cleans the floor as described above, but at each second the cleaning operation is performed with probability $ \frac p {100} $ only, and not performed with probability $ 1 - \frac p {100} $ . The cleaning or not cleaning outcomes are independent each second.

Given the floor size $ n $ and $ m $ , the robot's initial position $ (r_b, c_b) $ and the dirty cell's position $ (r_d, c_d) $ , find the expected time for the robot to do its job.

It can be shown that the answer can be expressed as an irreducible fraction $ \frac x y $ , where $ x $ and $ y $ are integers and $ y \not \equiv 0 \pmod{10^9 + 7}  $ . Output the integer equal to $ x \cdot y^{-1} \bmod (10^9 + 7) $ . In other words, output such an integer $ a $ that $ 0 \le a < 10^9 + 7 $ and $ a \cdot y \equiv x \pmod {10^9 + 7} $ .

## 说明/提示

In the first test case, the robot has the opportunity to clean the dirty cell every second. Using the [geometric distribution](https://en.wikipedia.org/wiki/Geometric_distribution), we can find out that with the success rate of $ 25\% $ , the expected number of tries to clear the dirty cell is $ \frac 1 {0.25} = 4 $ . But because the first moment the robot has the opportunity to clean the cell is before the robot starts moving, the answer is $ 3 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1623D/1348996177ef0ab22704318e93e1192dad2b1f54.png)Illustration for the first example. The blue arc is the robot. The red star is the target dirt cell. The purple square is the initial position of the robot. Each second the robot has an opportunity to clean a row and a column, denoted by yellow stripes.In the second test case, the board size and the position are different, but the robot still has the opportunity to clean the dirty cell every second, and it has the same probability of cleaning. Therefore the answer is the same as in the first example.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1623D/8530d74bbb858250eb8f573d1b14027e43bcb77e.png)Illustration for the second example.The third and the fourth case are almost the same. The only difference is that the position of the dirty cell and the robot are swapped. But the movements in both cases are identical, hence the same result.

## 样例 #1

### 输入

```
6
2 2 1 1 2 1 25
3 3 1 2 2 2 25
10 10 1 1 10 10 75
10 10 10 10 1 1 75
5 5 1 3 2 2 10
97 98 3 5 41 43 50```

### 输出

```
3
3
15
15
332103349
99224487```

# 题解

## 作者：TonyYin (赞：11)

[**更好的阅读体验**](https://www.tonyyin.top/2022/01/cf1623d/)

[题目链接 - CodeForces](https://codeforces.com/contest/1623/problem/D) 

## 题意

地板有 $n$ 行 $m$ 列，一个机器人被安置在坐标 $(r_b, c_b)$，还有一个障碍位于 $(r_d, c_d)$。

每过一秒，机器人的坐标会 $(r, c)\rightarrow (r+d_r, c+d_c)$。

初始时 $d_r=d_c=1$，当机器人到达边界后，$d_r,d_c$ 会变化：

- 若机器人碰到上/下边界（$r=1$ 或 $r=n$），下一秒 $d_r\leftarrow -d_r$，
- 若机器人到达左/右边界（$c=1$ 或 $c=m$），下一秒 $d_c\leftarrow -d_c$.

每一秒内，位于 $(r,c)$ 的机器人有 $\frac{p}{100}$ 的概率，成功清理掉位于第 $r$ 行和第 $c$ 列的障碍，**之后**，它将按照上面的规则进行移动。

若每次清理的结果相互独立，求清理掉障碍物 $(r_d, c_d)$ 所需的期望时间。

## 题解

**参考了由 [darkkcyan](https://codeforces.com/profile/darkkcyan) 提供的 [Codeforces Round #763 (Div. 2) Editorial](https://codeforces.com/blog/entry/98463)。**

首先，设 $\overline{p}=1-\frac{p}{100}$，代表不成功的概率。可以发现，机器人的轨迹会形成一个循环。

#### 样例一

从样例一开始分析。

![](https://wordpress-blog-1301627340.cos.ap-beijing.myqcloud.com/2022/01/03/46b9c9979c1db.png)

循环共两步，**设 $x_1$ 表示机器人从 $(1,1)$ 出发的答案，$x_2$ 表示从 $(2,2)$ 出发的答案**。

当位于 $(1, 1)$ 时，**如果成功**，花费时间 $0s$；**若否**，走到 $(2,2)$ 需要 $1s$，之后还需要 $x_2$，所以有：
$$
\begin{cases}
x_1=p\cdot 0 + \overline{p}(1+x_2)=\overline{p}(1+x_2)\\
x_2=p\cdot 0 + \overline{p}(1+x_1)=\overline{p}(1+x_1)\\
\end{cases}
$$
联立一下，得到关于 $x_1$ 的方程：
$$
x_1=\overline{p}(1+\overline{p}(1+x_1))
$$
逐层展开求解，$x_1$ 就是题目所求的答案。

#### 样例二

再看样例二。

![](https://wordpress-blog-1301627340.cos.ap-beijing.myqcloud.com/2022/01/03/380a00f5fd09e.png)

循环共四步：$(1,1)\rightarrow (2,2)\rightarrow (1,3)\rightarrow (2,2)$，**其中 $(1,1)$ 不可能清除障碍**，其余位置均有可能。

同理，设 $x_1$ 表示从 $(1,1)$ 出发的答案，$x_i$ 表示从循环第 $i$ 步出发的答案。（注意 $x_2\neq x_4$，它们的方向不同）

与样例一类似地，有：
$$
\begin{cases}
x_1 = 1 + x_2\\
x_2 = \overline{p}(1 + x_3)\\
x_3 = \overline{p}(1 + x_4)\\
x_4 = \overline{p}(1 + x_1)\\
\end{cases}
$$
联立，得到关于 $x_1$ 的方程：
$$
x_1=1 + \overline{p}(1 + \overline{p}(1 + \overline{p}(1 + x_1)))
$$

#### 做法

若我们已知循环共有 $k$ 个点，且已知其中每个点的坐标，则可以列出像上面那样的方程组。

联立后的方程形如：
$$
x=a_1(1+a_2(1+a_3(1+\cdots a_k(1+x)\cdots)))
$$
其中 $a_i\in\{1,\overline{p}\}$，是系数。**当循环中第 $i$ 步可以清除障碍时 $a_i=\overline{p}$，否则 $a_i=1$**.

由于数据范围 $4\leq n\cdot m\leq 10^5$，我们可以直接**暴力搜索找到循环**。

求解方程时，考虑从内向外逐层展开，过程中记录：常数项 $u$、一次项系数 $v$。

初始 $u=0$，$v=1$，**每次展开时先算出 $a$，之后 $\begin{cases}v\leftarrow a\cdot v\\u\leftarrow a\cdot (u+1)\end{cases}$ 就可以了**。

#### 循环长度

我们把机器人的移动，分解在 $x/y$ 方向分别看。在一维的投影上，它们的周期分别为 $2(n-1)$ 和 $2(m-1)$.、

![](https://wordpress-blog-1301627340.cos.ap-beijing.myqcloud.com/2022/01/03/bb435997809dc.png)

因此，$4(n-1)(m-1)$ 一定是 $\operatorname{lcm}(2(n-1), 2(m-1))$ 的整数倍，**是循环长度的整数倍**。

所以不必通过暴力搜索找到循环，对于所有数据都直接迭代 $4(n-1)(m-1)$ 次即可。

## 代码

注意倒序。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod = 1e9 + 7;
inline int power(int x, int k) {
	int ret = 1;
	while(k) { if(k & 1) ret = ret * x % mod; x = x * x % mod; k >>= 1; }
	return ret;
}
inline int inv(int x) { return power(x % mod, mod - 2); }
int T, n, m, ax, ay, bx, by, dx, dy, p, pp;
signed main() {
	cin >> T;
	while(T--) {
		cin >> n >> m >> ax >> ay >> bx >> by >> p;
		pp = (100 - p) * inv(100) % mod;
		p = p * inv(100) % mod;
		int u = 0, v = 1;
		dx = dy = -1; //倒序
		for(int cas = 1; cas <= 4 * (n - 1) * (m - 1); cas++) { //迭代4(n-1)(m-1)次
			if(ax + dx > n || ax + dx < 1) dx = -dx;
			if(ay + dy > m || ay + dy < 1) dy = -dy;
			ax += dx; ay += dy;
			u = (u + 1) % mod;
			if(ax == bx || ay == by) u = u * pp % mod, v = v * pp % mod;
		}
		cout << u * inv(mod + 1 - v) % mod << endl;
	}
	return 0;
}
```

---

## 作者：GaryH (赞：5)

# CF1623D 题解

#### Upd：修好了挂掉的 `Latex` ——3/7/2022

**题意**：

给一个 $n\times m$ 大小的地图和一个以 $(r_b,c_b)$ 为起点的机器人，机器人每次会走一步，

走的方式是将当前其所在的坐标 $(r,c)$ 变成 $(r+dr,c+dc)$，其中初始时 $dr=dc=1$，

每当机器人下一步的横坐标 $r$ 大于 $n$ 或小于 $1$ 时将 $dr$ 变成 $-dr$，

当机器人下一步的纵坐标 $c$ 大于 $m$ 或小于 $1$ 时将 $dr$ 变成 $-dc$，

同时，机器人每到一个新的位置时（初始位置也算到了一个新位置），

就会有 $p$ 的概率将所有横坐标等于 $r$ 的点和纵坐标为 $c$ 的点一起覆盖。

问特殊点 $(r_d,c_d)$ 第一次被覆盖时，机器人走的期望步数。

**做法**：

显然，机器人走的路径对应的位置序列虽然无限长，但是存在一个长度不超过 $4nm$ 的循环节，

因为一个机器人在某个位置时，其以后如何移动只与其坐标和移动方向有关，

那么用四元组 $(dr,dc,r,c)$ 表示一个机器人的位置和方向。又因为 $dr$ 和 $dc$ 只有 $4$ 种不同的可能，

则如果两次机器人的位置和方向对应四元组完全相等，则两次以后的所有行动也都完全相等，

这样就产生了一个循环节。

而两两不完全相同的四元组最多有 $4nm$ 个，故循环节长度不超过 $4nm$。

那么我们记一个循环节中，机器人第 $i$ 次有机会覆盖到特殊点时，数 $t_i$ 等于：

从这个循环节的起点到当前机器人所在位置，机器人走的步数。

定义机器人在某个位置 $(r,c)$ 时有机会覆盖到特殊点，当且仅当 $r=r_d $ 或 $ c=c_d$。

我们再记最终答案为 $T$，不覆盖的概率 $q=1-p$，循环节长度为 $z$，

一个循环节中有 $k$ 个位置使得机器人有机会覆盖到特殊点，则我们有：

$T=pt_1+q(pt_2+q(pt_3+q(\cdots q(pt_k+q(z+pt_1+q(pt_2+q(\cdots))))\cdots)))$，

含义是：

从某一个循环节开始，我们第一次有 $p$ 的概率覆盖特殊点，这时一共走了 $t_1$ 步；

同时，我们有 $q=1-p$ 的概率不覆盖特殊点，我们就需要继续走，

直到我们第二次有机会覆盖特殊点，我们又有 $p$ 的概率覆盖特殊点，这时我们一共走了 $t_2$ 步，

我们也有 $q$ 的概率不覆盖特殊点，我们就又需要继续走，这样的过程一直进行，

一直到我们第 $k$ 次有机会覆盖特殊点，此时我们有 $p$ 的概率覆盖特殊点，这时一共走了 $t_k$ 步，

我们同样有 $q$ 的概率不覆盖特殊点，我们就又需要继续走，

这时我们走完了一个循环节，已经走了 $z$ 步后进入下一个循环节，

而下一个循环节，在加上一个循环节的 $z$ 步后，就和上面的过程相似了。

我们发现，既然下一个循环节的过程和这个循环节相似，

那么，在减掉这个及之前的循环节所走的步数后，下一个循环节的答案还是 $T$。

那么我们也许可以尝试用答案 $T$ 去表达自己，即：

$T=pt_1+q(pt_2+q(pt_3+q(\cdots q(pt_k+q(z+T))\cdots)))$。

写成和式的形式，就是：

$T=(\sum\limits_{i=1}^{k}q^{i-1}pt_i)+q^{k}(z+T)$。

这个就很像一个关于 $T$ 的方程，我们解一下就可以得到：

$(1-q^k)T=(\sum\limits_{i=1}^{k}q^{i-1}pt_i)+q^{k}z$，即 $T=\frac{(\sum\limits_{i=1}^{k}q^{i-1}pt_i)+q^{k}z}{1-q^k}$。

因为模数是质数，所以我们只需要处理逆元后就可以算了。

时间复杂度是 $O(k)$ 的，而 $k\leq z\leq 4nm$，故可以通过。

当然，我写的代码里用了 STL map 记录一个四元组是否出现过，

这样比较方便，但复杂度就带了 $\log$，而实际上可以直接用数组记录，复杂度就是线性。

```
#define mp make_pair
#define int long long
#define pii pair < int , int >
#define rep(i, a, b) for (int i = (a); i <= (b); i++)

// 快读就不放了

const int N (1e6 + 10);
const int mod (1e9 + 7);

int ksm (int a, int b) {
	int r = 1;
	for (; b; a = a * a % mod, b >>= 1) if (b & 1) r = r * a % mod;
	return r;
}

int t[N];
map < pair < pii, pii > , int > vis;
int n, m, k, rb, cb, rd, cd, p, P, q, z;

void work() {
	vis.clear();
	n = read(), m = read(), rb = read(), cb = read();
    rd = read(), cd = read(), P = read();
	p = P * ksm (100, mod - 2) % mod, q = (mod + 1 - p) % mod;
	int dr = 1, dc = 1;
	k = z = 0;
	if (rb + dr > n || rb + dr <= 0) dr = -dr;
	if (cb + dc > m || cb + dc <= 0) dc = -dc;
	for (int i = 0; ; i++) {
		vis[mp (mp (rb, cb), mp (dr, dc))] = 1;
		if (cd == cb || rd == rb) t[++k] = i;
		rb += dr, cb += dc, z++;
		if (rb + dr > n || rb + dr <= 0) dr = -dr;
		if (cb + dc > m || cb + dc <= 0) dc = -dc;
		if (vis.count (mp (mp (rb, cb), mp (dr, dc)))) break;
	}
	int inv = mod + 1 - ksm (q, k);
	inv %= mod, inv = ksm (inv, mod - 2);
	int ans = z * ksm (q, k) % mod * inv % mod;
	rep (i, 1, k) 
	ans = (ans + (t[i] * p % mod * inv % mod * ksm (q, i - 1) % mod) % mod) % mod;
	cout << ans << endl;
}

signed main() {
	int t = read();
	while (t--) work();
	return 0;
}
```



---

## 作者：I_am_Accepted (赞：2)

### Analysis

下文用 $p$ 代替题目中的 $\dfrac{p}{100}$，表示每秒机器人清扫的概率。

期望的一般求法：$\sum\limits_{i}p_i\times v_i$，其中 $p_i$ 表示这种情况发生的概率，$v_i$ 表示这种情况的代价（或价值，本题中指时间）。

容易发现机器人走动的路线会以 $cy=2\times\operatorname{lcm}(n-1,m-1)
$ 秒时间为循环节，由于 $cy\leqslant 2\times10^5$，我们暴力遍历 $0\to(cy-1)$ 秒，依次记录有可能能清理垃圾的时间 $t_0,t_1,\dots,t_{k-1}$。

$t_i$ 秒正好清扫垃圾的概率为 $(1-p)^{i}p$，表示前面 $i$ 次机会都没把握住而这次把握了。

但是答案并不是 $tans=\sum\limits_{i=0}^{k-1}(1-p)^{i}pt_i$ 这么简单，因为有可能一次路线循环后机器人仍然没有清扫垃圾。

但是观察接下来的期望公式：

第二轮时：

$$\begin{aligned}
&\sum\limits_{i=0}^{k-1}(1-p)^{i+k}p(t_i+cy)
\\=&(1-p)^{k}\sum\limits_{i=0}^{k-1}(1-p)^{i}p(t_i+cy)
\\=&(1-p)^{k}(tans+cy\cdot p\sum\limits_{i=0}^{k-1}(1-p)^{i})
\end{aligned}$$

第 $L$ 轮时：

$$\begin{aligned}
&\sum\limits_{i=0}^{k-1}(1-p)^{i+(L-1)k}p(t_i+(L-1)cy)
\\=&(1-p)^{(L-1)k}(tans+(L-1)cy\cdot p\sum\limits_{i=0}^{k-1}(1-p)^{i})
\end{aligned}$$

将每一轮的结果累加即为答案（使用等比公式，设 $tmp=(1-p)^k$ 表示一轮路径没有清扫的概率）：

$$\begin{aligned}
&\sum\limits_{L=1}^{\infty}(1-p)^{(L-1)k}(tans+(L-1)cy\cdot p\sum\limits_{i=0}^{k-1}(1-p)^{i})
\\&=\sum\limits_{L=0}^{\infty}tmp^Ltans+\sum\limits_{L=0}^{\infty}L\cdot tmp^Lcy\cdot p\sum\limits_{i=0}^{k-1}(1-p)^{i}
\\&=tans\sum\limits_{L=0}^{\infty}tmp^L+cy\cdot p(\sum\limits_{i=0}^{k-1}(1-p)^{i})\sum\limits_{L=0}^{\infty}L\cdot tmp^L
\\&=\dfrac{1}{1-tmp}tans+cy(1-(1-p)^{k})\sum\limits_{L=0}^{\infty}L\cdot tmp^L
\end{aligned}$$

其中

$$\sum\limits_{L=0}^{\infty}L\cdot tmp^L
=\sum\limits_{i=1}^{\infty}tmp^i(\sum\limits_{L=0}^{\infty}tmp^L)
=\dfrac{\sum\limits_{i=1}^{\infty}tmp^i}{1-tmp}
=\dfrac{\dfrac{1}{1-tmp}-1}{1-tmp}
=\dfrac{tmp}{(1-tmp)^2}$$

### Detail

注意数学细节。

### Code

```cpp
void work(){
	t.clear();
	cin>>n>>m>>pos.fir>>pos.sec>>v.fir>>v.sec>>p;
	mmu(p,inv(100));//mod mul,inv 为乘法逆元
	cy=2*lcm(n-1,m-1);
	s=mkp(1,1);//make_pair
	For(i,0,cy-1){
		if(pos.fir==v.fir || pos.sec==v.sec) t.pb(i);//push_back
		if(pos.fir==n && s.fir==1) s.fir*=-1;
		if(pos.fir==1 && s.fir==-1) s.fir*=-1;
		if(pos.sec==m && s.sec==1) s.sec*=-1;
		if(pos.sec==1 && s.sec==-1) s.sec*=-1;
		pos.fir+=s.fir;
		pos.sec+=s.sec;
	}
   //此处为简化代码，计算过程与推导不同
	int ans=0,tmp=pw((mod+1-p)%mod,t.size()),ss=(mod+1-p)%mod;//pw:quick power
	int tot=0;
	for(int i:t){
		ans+=pw(ss,tot)*p%mod*i%mod;
		tot++;
	}
	mad(ans,cy);//mod add
	mmu(ans,inv((mod+1-tmp)%mod));
	mad(ans,-cy);
	cout<<ans<<endl;
} 
```

---

## 作者：Argon_Cube (赞：1)

怎么全是 $\mathrm O(nm)$ 的做法，来一发 $\Theta((n+m)\log(n+m))$ 的（其实是读错题了以为 $1\leq n,m\leq 10^5$）。

首先，那些不能扫到垃圾的点是没用的。我们只关心能扫到垃圾的点。

注意到，运动轨迹以 $2(n-1)(m-1)$ 作为循环节，并且能扫到垃圾的时间只有 $2k(n-1)+a_0,2k(n-1)+a_1,2k(m-1)+a_2,2k(m-1)+a_3$ 这四类，我们可以暴力的找出 $a_{0\sim3}$。

然后就可以直接得到所有小于 $2(n-1)(m-1)$ 的能扫到垃圾的时间，我们将其排序后存在 $t$ 中。

那么直接根据期望的定义，答案是

$$
\begin{aligned}
&\sum_{i=0}^{c-1}\sum_{j=0}^{\infty}p(1-p)^{jc+i}(t_i+2j(n-1)(m-1))\\

=&p\sum_{i=0}^{c-1}(1-p)^i\left(t_i\sum_{j=0}^{\infty}((1-p)^c)^j+2(n-1)(m-1)\sum_{j=0}^{\infty}((1-p)^c)^jj\right)\\

=&\sum_{i=0}^{c-1}p(1-p)^i\left(\frac{t_i}{1-(1-p)^c}+\frac{2(n-1)(m-1)(1-p)^c}{(1-(1-p)^c)^2}\right)
\end{aligned}
$$

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
#include <bitset>
#include <string>
#include <array>

using namespace std;

long long fast_pow(long long base,long long expnt,long long moder)
{
    long long result;
    for(result=1;expnt;(expnt&1)&&(result=result*base%moder,false),base=base*base%moder,expnt>>=1);
    return result;
}
inline long long inverse(long long num,long long prime)
{
    return fast_pow(num,prime-2,prime);
}

vector<long long> ticks;
const int moder=1e9+7;

int main(int argc,char* argv[],char* envp[])
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testcnt;
    cin>>testcnt;
    while(testcnt--)
    {
        int n,m,xa,xb,ya,yb,p,a0=-1,a1=-1,a2=-1,a3=-1;
        cin>>n>>m>>xa>>ya>>xb>>yb>>p;
        long long prob=inverse(100,moder)*p%moder;
        for(int i=0,x=xa,dx=1;a1==-1;i++,x+=dx)
        {
            if(x+dx>n||!(x+dx))
                dx*=-1;
            if(x==xb)
                if(a0==-1)
                    a0=i;
                else
                    a1=i;
        }
        for(int i=0,y=ya,dy=1;a3==-1;i++,y+=dy)
        {
            if(y+dy>m||!(y+dy))
                dy*=-1;
            if(y==yb)
                if(a2==-1)
                    a2=i;
                else
                    a3=i;
        }
        long long cyclen=2ll*(n-1)*(m-1);
        for(int i=0;2ll*i*(n-1)+a0<cyclen;i++)
            ticks.push_back(2ll*i*(n-1)+a0),ticks.push_back(2ll*i*(n-1)+a1);
        for(int i=0;2ll*i*(m-1)+a2<cyclen;i++)
            ticks.push_back(2ll*i*(m-1)+a2),ticks.push_back(2ll*i*(m-1)+a3);
        sort(ticks.begin(),ticks.end()),ticks.resize(unique(ticks.begin(),ticks.end())-ticks.begin());
        while(ticks.back()>=cyclen)
            ticks.pop_back();
        long long tmp=fast_pow(moder+1-prob,ticks.size(),moder);
        long long tmp0=inverse(moder+1-tmp,moder);
        long long tmp1=tmp0*tmp0%moder,tmp2=1;
        long long answer=0,tmp3=2ll*(n-1)*(m-1)%moder*tmp%moder*tmp1%moder;
        for(int i=0;i<ticks.size();i++)
            answer+=prob*tmp2%moder*(ticks[i]%moder*tmp0%moder+tmp3)%moder,tmp2=(moder+1-prob)*tmp2%moder;
        cout<<answer%moder<<'\n';
        ticks.clear();
    }
    return 0;
}
```

---

## 作者：ArrogHie (赞：1)

## 题意

同 CF1623A，但每一次机器人只有 $\frac{p}{100}$ 的几率清理，问清理掉细胞的期望步数是多少。

## 题解

设机器人现在的状态为 $x$，其中状态由所在的坐标及方向决定，下一步的状态为 $y$，且处于 $y$ 时能清理细胞。设若以 $x$ 状态为起点，期望步数为 $a$，以 $y$ 状态为起点，期望步数为 $b$。则 $a=(1-\frac{p}{100})(1+b)$。该式子含义为：处于 $b$ 状态时有 $1-\frac{p}{100}$ 的几率不能清理，所以 $a$ 即为 $b+1$ 乘以概率 $1-\frac{p}{100}$，因为从 $x$ 走到 $y$ 需要花费一步，所以要加一。

如果处于 $y$ 时不能清理细胞，则 $a=1+b$，因为此时不能清理的概率为 $1$。

机器人的行动存在周期，且周期中所有状态都不相同，~~（证明很简单，留给读者作课后作业）~~ 设周期中的状态分别为 $x_1,x_2,x_3,\cdots,x_T$,其中 $T$ 为周期长度，则对于一个状态 $x_i$ 对应的期望步数（设为 $a_i$ ）为 $a_i=\bar{p}_{i+1}(1+a_{i+1})$，其中 $\bar{p}_{i+1}$ 是 $x_{i+1}$ 不能清理细胞的概率，若 $x_{i+1}$ 与细胞处于同一列或者同一行则 $\bar{p}_{i+1}=1-\frac{p}{100}$，否则 $\bar{p}_{i+1}=1$。

之后可以得出方程组：

$\left\{\begin{matrix} a_1=\bar{p}_2(1+a_2)\\ a_2=\bar{p}_3(1+a_3)\\ a_3=\bar{p}_4(1+a_4)\\ \cdots 
\\ a_n=\bar{p}_1(1+a_1)\end{matrix}\right.$

合并后变成：

$a_1=\bar{p}_2(1+\bar{p}_3(1+\bar{p}_4(1+\bar{p}_5(1+\cdots \bar{p}_T(1+a_1)\cdots))))$

化简后只需要 DFS 枚举所有状态，就能轻易算出答案 $a_1$ 了。

---

## 作者：Priestess_SLG (赞：0)

考虑到平面中所有不同合法状态数不超过 $4nm$（当前点横纵坐标 / 当前偏移量），因此可以直接暴力找出从当前点开始机器人会移动的路径，该路径的长度不超过 $4nm$。设该路径 $L$ 中包含的坐标分别为 $(x_1,y_1),(x_2,y_2),\ldots,(x_k,y_k)$。那么对于每一个坐标 $(x_i,y_i)$：

+ 若 $(x_i,y_i)$ 和目标坐标在同一行 / 同一列上，那么有 $\frac{p}{100}$ 的概率完成，$\frac{100-p}{100}$ 的概率完不成。
+ 若 $(x_i,y_i)$ 和目标坐标不在同一行 / 同一列上，那么有 $0$ 的概率完成，$1$ 的概率完不成。

考虑设 $p_i$ 表示 $(x_i,y_i)$ **完不成**目标的概率，那么可以设答案是 $x$，然后列出方程：

$$
x=p_1(1+p_2(1+p_3(\ldots(1+p_k(1+x)))))
$$

但是这个方程中存在环，无法直接转移。因此套路的拆括号，得到：

$$
x=p_1+p_1p_2+p_1p_2p_3+\ldots+p_1p_2p_3\ldots p_k+p_1p_2p_3\ldots p_kx
$$

移项得：

$$
(1-p_1p_2p_3\ldots p_k)x=p_1+p_1p_2+p_1p_2p_3+\ldots+p_1p_2p_3\ldots p_k
$$

把左边这个东西除到右边，得到：

$$
x=\frac{p_1+p_1p_2+p_1p_2p_3+\ldots+p_1p_2p_3\ldots p_k}{1-p_1p_2p_3\ldots p_k}
$$

即：

$$
x=\frac{\sum\limits_{i=1}^n\prod\limits_{j=1}^ip_i}{1-\prod\limits_{i=1}^kp_i}
$$

下面这个东西可以直接算，上面部分直接算是 $O(n^2)$ 的，因此考虑设 $f_i=\prod\limits_{j=1}^i p_j$，那么上面部分变为：

$$
\sum\limits_{i=1}^n f_i
$$

此时上下部分都可以 $O(n)$ 计算答案，因此做完了。

[代码](https://codeforces.com/contest/1623/submission/303594398)。

---

