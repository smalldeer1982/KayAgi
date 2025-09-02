# [XJTUPC 2025] Primal Core Optimization: Attribute Balance

## 题目描述

你正在玩一款被称为「韵律原罪」的游戏。在这个游戏里，你需要操纵你的搭档们，在「世界」中探索。

在游戏中，每一个搭档都有三种属性：$\mathrm{Stop}$ (S)，$\mathrm{Flag}$ (F) 和 $\mathrm{Ever}$ (E)。当所有搭档的属性完全一致时，她们就能成功融合。

现在你想要把所有搭档全部融合，换句话说就是让每一对搭档的属性全部相等。为了达成这一目的，你不得不对她们的属性进行修改。一次修改分为以下步骤：

- 你任选一位搭档作为修改的目标（你只能选一位搭档）；
- 你任选她的若干个属性；
- 将她的所选属性的数值全部增加 $1$ 或全部减少 $1$（必须同时执行同一种操作，即全部加或全部减）。

由于你的魔力不强，所以每次修改都需要花费 $1$ 源石。现在你想知道，你至少需要花费多少源石，才能达到你的目标。

## 说明/提示

对于第一组样例，存在以下操作方式，使得总修改次数是 $2$ 次：

- 选择搭档 $3$ 和她的第一个属性，将她的属性修改为 $2$, $2$, $3$；
- 选择搭档 $3$ 和她的第三个属性，将她的属性修改为 $2$, $2$, $2$。

同时可以证明，不能通过少于 $2$ 次操作达成目标。所以，你应该输出 $2$。

对于第二组样例，存在以下操作方式，使得总修改次数是 $4$ 次：

- 选择搭档 $1$ 和她的第一、第三属性，将她的属性修改为 $3$, $3$, $2$；
- 选择搭档 $2$ 和她的第二、第三属性，将她的属性修改为 $3$, $4$, $2$；
- 选择搭档 $2$ 和她的第二个属性，将她的属性修改为 $3$, $3$, $2$；
- 选择搭档 $3$ 和她的第二、第三属性，将她的属性修改为 $3$, $3$, $2$。

同时可以证明，不能通过少于 $4$ 次操作达成目标。所以，你应该输出 $4$。

对于第三组样例，因为只有一位搭档，所以不需要进行操作。所以，你应该输出 $0$。


## 样例 #1

### 输入

```
3
2 2 2
2 2 2
1 2 3```

### 输出

```
2```

## 样例 #2

### 输入

```
3
2 3 1
3 5 3
3 2 1```

### 输出

```
4```

## 样例 #3

### 输入

```
1
201 502 10```

### 输出

```
0```

## 样例 #4

### 输入

```
4
1 2 3
1 2 3
4 5 6
4 5 6
```

### 输出

```
6```

# 题解

## 作者：chenzhiyou12 (赞：12)

赛时 lg 榜和正式榜独占（大概是？）。

可惜队友没有做出 FIM，遗憾 rk7。

下面给出一种比较简单易懂的做法（如有锅请大佬指正）。

首先，对于最终值取 $A,B,C$ 的情况，我们不难弄出一个人的最小操作次数，即 $cost(i)=\max({A-a_i,B-b_i,C-c_i,0})+\max({a_i-A,b_i-B,c_i-C,0})$。然后修改完所有的次数就是 $f(A,B,C)=\sum_{i=1}^{n}{cost(i)}$。

题意转化为求 $f(A,B,C)$ 的最小值。

不难发现，$f(A,B,C)$ 是分段凸函数，可以形象的理解为三位空间中一个表面粗糙的碗。

注意到 $A\in[\min(a_i),\max(a_i)],B\in[\min(b_i),\max(b_i)],C\in[\min(c_i),\max(c_i)]$。

按照直觉，我们可以先把 $A,B,C$ 分别取成 $a,b,c$ 三个数组的中位数，也就是让我们的起点尽量在“碗”靠内的位置。随后，因为 $f(A,B,C)$ 其实只在整点上有取值，所以我们可以不断地试图向 $27$ 个方向上的整点跳，根据凸性，如果跳出来的更优，那么我们就应该跳。

怎么决定跳多长的距离呢？可以直接倍增（准确来说是“倍减”），我们设 $k=max(\max(a_i)-\min(a_i),\max(b_i)-\min(b_i),\max(c_i)-\min(c_i))$（为了覆盖整个碗面），如果有一次跳成功了，我们就继续尝试跳，否则就将 $k$ 折半。还是因为只在整点取值，所以倍增一定能跳到最终最优的点（一定能凑出来整数）。

所以就有了代码：

``` cpp
#include<bits/stdc++.h>
#define ll long long
#define db double
#define vi vector<int>
#define pb push_back
#define pii pair<int,int>
#define mkp make_pair
#define For(i,j,k) for(int i=j;i<=k;++i)
#define Rof(i,j,k) for(int i=j;i>=k;--i)
using namespace std;
const int N=1e5+10,inf=0x3f3f3f3f;
int n;
vi a,b,c;
ll f(int A,int B,int C){
    ll ret=0;
    For(i,0,n-1){
        int d1=A-a[i],d2=B-b[i],d3=C-c[i];
        int v1=max({d1,d2,d3,0});
        int v2=max({-d1,-d2,-d3,0});
        ret+=v1+v2;
    }
    return ret;
}
int med(vi x){sort(x.begin(),x.end());return x[x.size()/2];}
int mn(vi x){
    int ret=inf;
    for(auto v:x){ret=min(ret,v);}
    return ret;
}
int mx(vi x){
    int ret=0;
    for(auto v:x){ret=max(ret,v);}
    return ret;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL),cout.tie(NULL);
    cin>>n;
    For(i,1,n){
        int na,nb,nc;cin>>na>>nb>>nc;
        a.pb(na),b.pb(nb),c.pb(nc);
    }
    int A=med(a),B=med(b),C=med(c);
    ll ans=f(A,B,C);
    int mna=mn(a),mxa=mx(a);
    int mnb=mn(b),mxb=mx(b);
    int mnc=mn(c),mxc=mx(c);
    int stp=max({mxa-mna,mxb-mnb,mxc-mnc});
    while(stp){
        bool flg=false;
        For(i,-1,1){For(j,-1,1){For(k,-1,1){
            int na=A+i*stp,nb=B+j*stp,nc=C+k*stp;ll now=f(na,nb,nc);
            if(now<ans){
                ans=now;
                A=na,B=nb,C=nc;
                flg=true;
            }
        }}}
        if(!flg){stp>>=1;}
    }
    cout<<ans<<'\n';
    return 0;
}
```

下面证明 $f(A,B,C)$ 的凸性。

首先我们知道，若 $f_1$ 和 $f_2$ 均为凸函数，$f_3=f_1+f_2$ 也是凸函数。

我们先证一个引理：

若 $g(x)=\max({f_1(x),f_2(x),\ldots,f_n(x)})$，其中 $f_1(x),f_2(x),\ldots,f_n(x)$ 均为仿射函数（形如 $f(x)=Ax+B$ 的函数），则 $g(x)$ 是凸函数。

证明：

可以先取两个向量 $x_1,x_2$ 和 $t\in[0,1]$。

有 
$$g(tx_1+(1-t)x_2)=\max f(tx_1+(1-t)x_2)$$
$$=\max [tf(x_1)+(1-t)f(x_2)]$$
$$\leq t(\max f(x_1))+(1-t)(\max f(x_2))$$
$$=tg(x_1)+(1-t)g(x_2)$$

整理就是：$g(tx_1+(1-t)x_2) \leq tg(x_1)+(1-t)g(x_2)$，符合凸函数的定义。

有了这个引理之后就好弄了。

$cost(i)=\max({A-a_i,B-b_i,C-c_i,0})+\max({a_i-A,b_i-B,c_i-C,0})$，不难发现，$A-a_i,B-b_i,C-c_i,0,a_i-A,b_i-B,c_i-C$ 都是仿射函数，所以 $\max({A-a_i,B-b_i,C-c_i,0})$ 和 $\max({a_i-A,b_i-B,c_i-C,0})$ 都是凸函数，所以 $cost(i)$ 是凸函数。

因为 $cost(i)$ 是凸函数，证得 $f(A,B,C)=\sum_{i=1}^{n}{cost(i)}$ 也是凸函数。

---

## 作者：迟暮天复明 (赞：5)

出题人题解。

这个 idea 来源于读错了 [CF1394C](https://www.luogu.com.cn/problem/CF1394C) 的题，其实本题和那个题基本一致。只是要求的东西从距离最大值变成了距离和。

首先这个函数是凸的。题解 pdf 里有详细的证明，不过我证明它是凸的方式是原题也可以三分过。

考虑三分 $x,y$。接下来考虑 $z$ 和每一个搭档的修改次数之间的函数关系，不难发现是一个先下降然后平台最后上升的过程。使用二维差分维护这个函数。

然后三分是没有用的，因为完全可以直接二分然后考察取 $mid$ 和 $mid+1$ 的大小关系。这题校赛开了九秒，允许 $O(n\log^3n)$ 的复杂度通过。洛谷上开了 $1.5$ 秒，只允许两次二分或者实现的好的两次三分通过。

这个题梯度下降法跑了不到 $300$ 毫秒。

---

## 作者：ShwStone (赞：2)

给个不同的观察。

考虑题目涉及到的函数 $L(x,y,z) = \max(x,y,z,0)-\min(x,y,z,0)$，它满足下列条件：

**正定性**：

$L(x,y,z,0) \ge 0$，当且仅当 $x=y=z=0$ 时取等。

**绝对一次齐次性**：

$L(ax,ay,az,0) = |a|L(x,y,z,0)$，这要分 $a$ 的正负证明：

$a\ge 0$ 是平凡的，此时：
$$
\begin{aligned}
\max(ax,ay,az,0) &= a \max(x,y,z,0)\\
\min(ax,ay,az,0) &= a \min(x,y,z,0)\\
L(ax,ay,az) &= aL(x,y,z)
\end{aligned}
$$
$a < 0$ 时：
$$
\begin{aligned}
\max (ax,ay,az,0) &= a\min (x,y,z,0) \\
L(ax,ay,az) &= a(\min(x,y,z,0) - \max(x,y,z,0))\\
&= -aL(x,y,z)
\end{aligned}
$$

**三角不等式**：

我们记 $M_i=\max(x_i,y_i,z_i,0)$，$m_i=\min(x_i,y_i,z_i,0)$，则 $L(x_i,y_i,z_i) = M_i - m_i$。

另记 $M_{12} = \max(x_1+x_2,y_1+y_2,z_1+z_2,0)$，$m_{12} = \min(x_1+x_2,y_1+y_2,z_1+z_2,0)$，则有：$L(x_1+x_2,y_1+y_2,z_1+z_2)=M_{12} - m_{12}$。

由于 relu 函数 $\max(a,0)$ 显然有性质 $\max(a,0)+\max(b,0) \ge \max(a+b,0)$，不难推广到：

$$
M_1+M_2 \ge M_{12}
$$

同理，因为 $\min(a,0)$ 满足 $\min(a,0)+\min(b,0) \le \min(a+b,0)$，可以推广到：

$$
m_1+m_2\le m_{12}
$$

所以会有：

$$
\begin{aligned}
L(x_1,y_1,z_1) + L(x_2,y_2,z_2)&=M_1-m_1+M_2-m_2\\
&=(M_1+M_2)-(m_1+m_2)\\
&\ge M_{12} + m_{12}\\
&= L(x_1+x_2,y_1+y_2,z_1+z_2)
\end{aligned}
$$

由于 $L(x,y,z)$ 满足上面三个性质， $L$ 成功升格为 $\mathbb R^3$ 空间上的一个**范数**。我们记作 $\Vert\cdot\Vert_L$。

那么 $(\mathbb R^3,+, \Vert\cdot\Vert_L)$ 就是一个**赋范线性空间**。

这个范数可以诱导一个**度量**：$d(\mathbf u,\mathbf v) = \Vert \mathbf u - \mathbf v\Vert_L$。$(\mathbb R^3, d)$ 就是一个度量空间。

这时候，我们想知道的凸性什么的都已经是代数里的基本结论了。

而且，不难发现题目要求等价如下：

$$
\min_{\mathbf u\in \mathbb R^3} \sum_{i=1}^n d(\mathbf u, \mathbf x_i)
$$

如果是 $L_2$ 范数，结论是取 $\bf x_i$ 平均值；如果是 $L_1$ 范数，结论是取 $\bf x_i$ 每坐标分别的中位数。

由于所有范数在拓扑上的等价性，可以考虑一些乱搞做法：初值选在平均值或中位值，然后用一些一阶优化算法（梯度下降什么的）或者零阶优化算法（模拟退火、爬山什么的）。

---

