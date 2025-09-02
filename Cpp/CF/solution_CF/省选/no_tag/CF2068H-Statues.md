# Statues

## 题目描述

某市市长计划在城市交叉路口放置 $n$ 座雕像。城市交叉路口的坐标为所有整数坐标点 $(x, y)$。交叉路口之间的距离使用曼哈顿距离计算，定义如下：

$$ \text{distance}((x_1, y_1), (x_2, y_2)) = |x_1 - x_2| + |y_1 - y_2|. $$

市议会对雕像的放置提出了以下要求：
- 第一座雕像必须放置在 $(0, 0)$；
- 第 $n$ 座雕像必须放置在 $(a, b)$；
- 对于 $i = 1, \dots, n-1$，第 $i$ 座雕像与第 $(i+1)$ 座雕像之间的距离必须为 $d_i$。允许将多座雕像放置在同一个交叉路口。

请帮助市长找到满足条件的 $n$ 座雕像的放置方案，或判定其不存在。

## 说明/提示

第一个样例中，不存在满足条件的 3 座雕像的放置方案。

第二个样例中，图示展示了一种可能的有效方案（注意并非唯一解）：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2068H/bac019e6fadcb1218e4149365f9308ab75fb2f84.png)

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3
5 8
9 0```

### 输出

```
NO```

## 样例 #2

### 输入

```
4
10 6
7 8 5```

### 输出

```
YES
0 0
6 -1
11 2
10 6```

# 题解

## 作者：baka24 (赞：0)

先把一些显然无解的情况判掉。

$$
\sum_{i=1}^n d_i < a+b\\
\exists i,
\sum [j\ne i] d_j +a+b< d_i\\
 2\nmid \sum _{i=1}^n d_i+a+b
$$

分别对应了全加起来依然不够，有一个 $d_i$ 太大了其他的没法绕回来，奇偶性不满足。

考虑曼哈顿距离的限制相当于什么，画在图上，发现所有符合条件的点长这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/kcc2cxfo.png)

那我们不妨把这个菱形旋转 $90$ 度，那么限制相当于 $i+1$ 的中心要在 $i$ 的边上。

此时原来的点 $(x,y)$ 将会变为 $(x+y,x-y)$

![](https://cdn.luogu.com.cn/upload/image_hosting/rnam9hx7.png)


考虑一个正方形对 $x,y$ 位移的影响，相当于 $x$ 方向 $\pm d_i$，$y$ 方向 $[-d_i,d_i]$，或者对称过来。

那么考虑分配 $d_i$ 到 $x$ 方向还是 $y$ 方向，目标是让 $x$ 方向的和为 $a-b$，$y$ 方向的和为 $a+b$。

不妨将最大的 $d_n$ 分配到 $x$，剩下的全部分配到 $y$。

对于 $x$ 方向，将 $a-b$ 设为初值，从大到小遍历 $d_1\sim d_{n-1}$：如果当前值为正就加入 $-d_i$，否则加入 $+d_i$。

这里是因为要尽可能最小化绝对值。并且由于保证了 $\sum d \ge a$，所以最后得到的值一定 $\in [-d_n,d_n]$。

对于 $y$ 方向，将 $a+b-d_n$ 设置为初值，正就减，负就加，因为每个 $d_i$ 都可以自由调整，所以怎么搞都可以。

因为保证了 $d_n\le \sum _{i=1}^{n-1}d_i+a+b$ 所以最后一定可以调到 $0$。

但是这样还有一个问题：

![](https://cdn.luogu.com.cn/upload/image_hosting/8c7fwvn3.png)

如图，旋转了坐标系后奇数点和偶数点并非互相可达，也就是说对于所有 $d_i$ 它被分配的值的奇偶性都必须与 $d_i$ 相同。

但是这个只需要在考虑 $y$ 方向时分别考虑奇数和偶数的贡献就行了。（先考虑用偶数调整，再用奇数两两拼起来调整，再用一个奇数调对奇偶性）

因为保证了 $\sum d_i+a+b$ 奇偶性总和是对的所以不会出问题。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int> 
#define fr first
#define sc second 
#define mk make_pair
#pragma gcc optimize(2)
int read(){int x=0,f=1;char c=getchar();while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}x=c-'0';c=getchar();while(c<='9'&&c>='0'){x*=10;x+=c-'0';c=getchar();}return x*f;}
const int MAXN=3010;
int n,x,y,tot,a,b;
int fl;
pii d[MAXN];
int p[MAXN],q[MAXN],id[MAXN];
void slv(){
    n=read(),x=read(),y=read();
    a=x-y,b=x+y;
    for(int i=1;i<n;i++)d[i].fr=read(),d[i].sc=i;
    sort(d+1,d+n);
    int sum=0;
    for(int i=1;i<n;i++)sum+=d[i].fr;
    if((sum+b)&1){puts("NO");return;}
    if(sum<b){puts("NO");return;}
    for(int i=1;i<n;i++)if(sum+b<2*d[i].fr){puts("NO");return;}
    int tmp=-a;
    for(int i=n-2;i>=1;i--)if(tmp>0)p[i]=-d[i].fr,tmp-=d[i].fr;else p[i]=d[i].fr,tmp+=d[i].fr;
    p[n-1]=-tmp,tmp=-b+d[n-1].fr,q[n-1]=+d[n-1].fr;
    if(tmp&1){if(tmp>0)tmp--,fl=1;else tmp++,fl=-1;}
    for(int i=n-2;i>=1;i--)
        if(d[i].fr&1^1)if(tmp>0)q[i]=-min(tmp,d[i].fr),tmp-=min(tmp,d[i].fr);else q[i]=-max(tmp,-d[i].fr),tmp-=max(tmp,-d[i].fr);
        else if(tmp>0)q[i]=-min(tmp,d[i].fr-1),tmp-=min(tmp,d[i].fr-1);else q[i]=-max(tmp,-d[i].fr+1),tmp-=max(tmp,-d[i].fr+1);
    tmp+=fl;
    for(int i=n-2;i>=1;i--)if(d[i].fr&1){
        if(tmp>0)q[i]+=-1,tmp--;else q[i]+=1,tmp++;
    }
    int lx=0,ly=0;
    for(int i=1;i<=n;i++)id[d[i].sc]=i;
    puts("YES");
    for(int i=1;i<=n;i++)printf("%lld %lld\n",(lx+ly)/2,(ly-lx)/2),lx+=p[id[i]],ly+=q[id[i]];
}
signed main(){
    freopen("1.in","r",stdin);freopen("1.out","w",stdout);
    slv();
    return 0;
}
```

---

## 作者：happybob (赞：0)

把这个相邻两项曼哈顿距离补全成环，记 $d_0 = \operatorname{distance}((0,0),(x_n,y_n))$。

不难发现有解的两个必要条件：

1. $a+b$ 与 $\sum \limits_{i=1}^{n-1} d_i$ 同奇偶，即 $\sum \limits_{i=0}^{n-1} d_i$ 为偶数。
2. $a+b \leq \sum \limits_{i=1}^{n-1} d_i$。即 $d_0 \leq \sum \limits_{i=1}^{n-1} d_i$。进一步地，对于所有 $i$ 都有 $d_i \leq \sum \limits_{j \neq i} d_j$，意义是直接走的距离总是不超过绕一圈的距离。

事实上这是充要条件。考虑给出归纳性证明。

对于目前的终点 $(a,b)$，我们只需要找到 $(x_{n-1},y_{n-1})$ 使得新的 $d_{0}',d_1,\cdots,d_{n-2}$ 符合上述两个要求。

考虑条件 $1$，发现无论如何选择 $(x_{n-1},y_{n-1})$ 总天然满足限制，原因是绕一圈必然有总距离为偶数。

对于条件 $2$，先考虑 $d_{0}' \in [|d_0 - d_{n-1}|,d_0+d_{n-1}]$，并且 $d_0'$ 能取到范围内与 $d_0 + d_{n-1}$ 同奇偶的所有值。这个是由于 $(x_{n-1},y_{n-1})$ 总在 $(x_n,y_n)$ 为中心的一个斜三角形边上。

事实上我们可以证明取 $d_0' = \min(d_0+d_{n-1},\sum \limits_{i=1}^{n-2} d_i)$ 符合归纳条件。这个可以分类讨论 $\min$ 取在哪一边。

$n$ 很小，咋维护都行。

---

