# [CEOI 2010] mp3player (day2)

## 题目描述

有一个 MP3 播放器，这个播放器如果连续 $t$ 秒没有任何操作就会自动休眠。在休眠期间，任何按键都不会起到按键本身的作用，而只会终止休眠。

例如，假设 $t=5$ 且播放器当前处于锁定状态。然后进行如下 $4$ 步操作：

- 按下 `A`，停顿 $3$ 秒；
- 按下 `B`，停顿 $5$ 秒；
- 按下 `C`，停顿 $6$ 秒；
- 按下 `D`。

这些操作过后，实际执行的只有 `B` `C`。注意，在按 `C` 和按 `D` 之间播放器已经休眠了。

这个 MP3 还有两个音量控制键 `+` `-`，分别为将音量调高一个单位或降低一个单位。音量只能为介于 $0\sim V_{\max}$ 之间的整数，即如果音量为 $0$ 时按 `-` 或音量为 $V_{\max}$ 时按 `+`，音量均不发生改变。

刚开始你并不知道 $t$ 的值，便想通过实验来得出。

播放器刚开始是休眠的。你会从某一个音量 $V_1$ 开始，经过 $n$ 次操作得到音量 $V_2$，操作的具体步骤已经给出，每次操作形如 `+/-` $C_i$，表示在距离实验开始 $C_i$ 秒时按下 `+` 或 `-`。

不幸的是，你也不知道 $V_1$ 的值，现在，你需要找出符合实验操作的 $t$ 的最大值，并输出相应的 $V_1$ 。



## 说明/提示

#### 【样例解释】

#### 样例 1 解释

当 $t=5$ 时，按键的情况为；`解锁,解锁,+,+,解锁,-`。

此时对于 $V_1\in \{2,3,4\}$，可以得到 $V_2=3$。但是要输出最大的 $V_1$。

当 $t\geq 6$ 时，最后两个按键都会发挥正常的作用，也就是连续下调两个音量。此时结果无法为 $V_2=3$，故 $t_{\max}=5$。 

#### 样例 2 解释

当 $V_1=10$ 时，任意的 $t$ 都能满足条件。

#### 【数据规模与约定】

- 对于 $40\%$ 的数据，保证 $n\le 4000$；
- 对于 $70\%$ 的数据，保证 $n\times V_{\max}\le 4\times 10^5$；
- 对于 $100\%$ 的数据，保证 $2\le n\le 10^5$，$2\le V_{\max}\le 5000$，$0<C_i<2\times 10^9$，$0\le V_2\le V_{\max}$，$x_i\in\{\texttt{+}, \texttt{-}
\}$。


#### 【说明】

**题目译自 [CEOI 2010](http://ceoi2010.ics.upjs.sk/Contest/Tasks) day 2 *[T1 mp3player](https://people.ksp.sk/~misof/ceoi2010/mp3-eng.pdf)***。

翻译版权为题目提供者@[ShineEternal](https://www.luogu.com.cn/user/45475) 所有，未经许可禁止转载。



## 样例 #1

### 输入

```
6 4 3
- 0
+ 8
+ 9
+ 13
- 19
- 24```

### 输出

```
5 4```

## 样例 #2

### 输入

```
3 10 10
+ 1
+ 2
+ 47```

### 输出

```
infinity```

# 题解

## 作者：kemingyu (赞：3)

### 思路 
  考虑初始音量 $x$，如果 $x$ 在某次操作后超过 $Vmax$，显然没有用处；同理如果小于 $0$，也没有用处。然后就用线段树维护当前区间有用的初始音量范围。然后求一下答案即可。
### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100005
#define M 300005
using namespace std;
int n, m, gol, pos[N], lf[M], rg[M], icr[M];
struct node {
    int x, y;
    bool k;
} a[N];
bool cmp(const node &u, const node &v) {
    return u.x < v.x;
}
void build(int k, int l, int r) {
    rg[k] = m;
    if (l == r) {
        // 将该位置对应的线段树节点编号记录在pos数组中
        pos[l] = k;
        return;
    }
    int mid = (l + r) >> 1;
    // 递归构建左子树
    build(k << 1, l, mid);
    // 递归构建右子树
    build(k << 1 | 1, mid + 1, r);
}
int main() {
    scanf("%d%d%d", &n, &m, &gol);
    n--;
    // 读取第一个操作的字符（'+'或'-'）和对应的时间值
    int i, k, x, y;
    char cr = getchar();
    while (cr!= '-' && cr!= '+')
        cr = getchar();
    scanf("%d", &x);
    // 循环读取后续的操作信息，构建操作节点数组a
    for (i = 1; i <= n; i++, x = y) {
        // 读取操作字符（'+'或'-'），跳过不是操作字符的输入
        cr = getchar();
        while (cr!= '-' && cr!= '+')
            cr = getchar();
        // 根据读取的操作字符确定k的值，true表示'+'操作，false表示'-'操作
        a[i].k = (cr == '+');
        // 读取本次操作与上一次操作的时间间隔对应的时间值
        scanf("%d", &y);
        a[i].x = y - x;
        a[i].y = i;
    }
    // 对操作节点数组a按照操作时间间隔x进行排序
    sort(a + 1, a + n + 1, cmp);
    // 构建线段树，根节点编号为1，初始区间为[1, n]
    build(1, 1, n);
    int ans1 = 1, ans2 = gol;
    for (i = 1; i <= n; i++) {
        // 如果当前操作是增加音量操作（'+'）
        if (a[i].k) {
            // 找到当前操作对应的线段树节点编号k
            k = pos[a[i].y];
            // 减少当前节点表示区间的右端点值
            rg[k]--;
            // 增加当前节点的增减量值
            icr[k]++;
        }
        // 如果当前操作是降低音量操作（'-'）
        else {
            k = pos[a[i].y];
            // 增加当前节点表示区间的左端点值
            lf[k]++;
            // 减少当前节点的增减量值
            icr[k]--;
        }
        // 向上更新线段树节点信息
        for (k >>= 1; k; k >>= 1) {
            // 更新当前节点的左端点值，取左右子树左端点值中的较大值
            lf[k] = max(lf[k << 1], lf[k << 1 | 1] - icr[k << 1]);
            // 更新当前节点的右端点值，取左右子树右端点值中的较小值
            rg[k] = min(rg[k << 1], rg[k << 1 | 1] - icr[k << 1]);

            // 如果当前节点的左端点值小于等于右端点值
            if (lf[k] <= rg[k])
                // 更新当前节点的增减量值，为左右子树增减量值之和
                icr[k] = icr[k << 1] + icr[k << 1 | 1];
            else
                // 如果右子树的右端点值加上其增减量值小于左子树的左端点值
                if (rg[k << 1] + icr[k << 1] < lf[k << 1 | 1]) {
                    // 将当前节点的左右端点值和增减量值都设置为左子树的左端点值和增减量值
                    lf[k] = rg[k] = lf[k << 1 | 1];
                    icr[k] = icr[k << 1 | 1];
                } else {
                    // 将当前节点的左右端点值和增减量值都设置为右子树的右端点值和增减量值
                    lf[k] = rg[k] = rg[k << 1 | 1];
                    icr[k] = icr[k << 1 | 1];
                }
        }
        // 如果当前是最后一个操作或者下一个操作的时间间隔与当前操作不同
        if (i == n || a[i].x!= a[i + 1].x) {
            // 如果当前节点的左端点值加上其增减量值小于等于目标值gol，且目标值gol小于当前节点的右端点值加上其增减量值
            if (lf[1] + icr[1] <= gol && gol < rg[1] + icr[1]) {
                // 更新答案变量ans1为当前操作序号加1
                ans1 = i + 1;
                // 更新答案变量ans2为目标值gol减去当前节点的增减量值
                ans2 = gol - icr[1];
            } else if (rg[1] + icr[1] == gol) {
                // 如果当前节点的右端点值加上其增减量值等于目标值gol
                ans1 = i + 1;
                // 将答案变量ans2设置为m
                ans2 = m;
            }
        }
    }
    if (ans1 > n)
        puts("infinity");
    else
        printf("%d %d\n", a[ans1].x - 1, ans2);
    return 0;
}
```

---

## 作者：yuanzhiteng (赞：2)

[题目链接](https://www.luogu.com.cn/problem/P6520)    
****   
### 一. 错误思路   
拿到题后一头雾水......    
容易想到的是二分 $t$，然后倒推模拟。   
这种做法有两个错误。   
$(1)$ 二分的前提：二分对象具有 **单调性**。   
但是本题中的 $t$ 具有单调性吗？    
换句话说，若对于 $t_1$ **不**满足题意，$\forall t_2>t_1$ 都**不**满足题意吗？   
稍微手玩一下会发现 $t$ 并没有单调性。   
比如看下面这个例子：  
```cpp
3 3 1
- 0
+ 3
+ 6
```
若 $t=3$，它是不满足题意的。   
但若 $t=4$，它却是满足题意的。   
所以 **不能二分 $t$** 。（注意不是不能二分，而是不能二分 $t$，下面会说）    
$(2)$ 倒推真的可以吗？    
我们知道，当给定一个序列和 $V_1$ 后，正推是很好推的。   
但是倒推呢？   
如果没有 $触底/触顶$ 机制还好说，可以倒推，但是如果有了这个机制呢？   
由于状态 $i$ 是由状态 $i-1$ 得到，所以我们无法知道状态 $i-1$ 时是否触底/顶。     
比如：倒推此时 $nowv=0,op=-$，无法确定上一个状态是 $1$ 还是 $0$。   
所以倒推也是不行的。   
~~当然如果你对于触底时随机选择，多跑几遍取 max 当我没说，脸好可以骗点分。~~
****    
### 二. 题目分析     
那怎么办？    
~~俗话说：“OI 暴力始”~~ 先考虑暴力如何做。    
既然 $t$ 不能二分，那干脆直接枚举 $[0,maxt]$ 中的所有 $t$。   
有了 $t$ 后还不够。   
上面已经说了不能倒推。    
所以只能正着推。   
问题又来了，正着推缺条件—— $V_1$。   
管他的，暴力枚举。    
那么有了 $V_1$ 和 $t$ 后就能 $\mathcal{O}(n)$ 模拟得到相应的 $V_2$ 了。   
如果对于 $t=maxt$ 仍然能满足题意，那么输出 infinity。    
时间复杂度 $\mathcal{O}(nV_{max}\max(C_i))$。   
好恐怖的复杂度。(* ￣▽￣* )    
考虑优化。   
首先，$t$ 是否需要枚举所有的 $t$？   
发现不需要，只需要枚举 **时间段** 即可。   
什么意思呢？  
呐，比如说样例一。   
对于 $t=2$ 和 $t=3$ 效果是一样的。   
枚举的关键应该在于 **操作序列状态的改变**。  
所以在样例一中只需要枚举 $t=1,4,5,6,8$。   
这样便将 $t$ 的范围缩小到了 $\mathcal{O}(n)$。  
其次，真的都不能二分吗？   
发现 **$V_1$ 可以二分**。    
感性地理解，当 $V_1$ 增加了，相当于“起点”上升了，但后面的过程一样，由于起点更高，终点自然也就不会更低。   
具体地，设 $f(V_1)$ 表示 $V_1$ 经过操作序列后能得到的 $V_2$。  
那么 $f(V_1)$ 是**非严格单调递增**的。   
所以可以 $\mathcal{O}(\log n)$ 枚举 $V_1$。  
所以优化后的时间复杂度为 $\mathcal{O}(n^2\log n)$。    
有分，但不多。     
再考虑去优化它。    
时间复杂度的瓶颈在哪里呢？   
二分 $V_1$ 是没有办法省去的，毕竟要正着推。   
那......$t$ 呢？   
好像也没法直接地省去。   
没办法了吗？   
难道......真的要在这里倒下了吗哦(* >﹏<* )？    
换一种思考角度，既然没办法直接去掉时间复杂度，那能不能将它“拆”开呢？  
**换句话说，能不能先判断 $t$ 有无对应的 $V_1$ 符合题意，求出最大的 $t$ 后再去二分 $V_1$ 呢？**    
假设判断是至多 $\mathcal{O}(\log n)$ 的，那么时间复杂度就降为了 $\mathcal{O}(n\log n+logn)=\mathcal{O}(n\log n)$ 。   
这不就可以通过了吗？    
所以关键在于**如何快速判断对于一个给定的 $t$ 是否存在合法的 $V_1$ 使之满足题意**。    
如何判断？   
再次仔细观察题面：  
如果当前操作成功，则  
对于 $+$ 操作，音量 $x$ 会变为 $\min(V_{max},x+1)$；  
对于 $-$ 操作，音量 $x$ 会变为 $\max(0,x-1)$；    
欸，感觉来了。 (≧∇≦)  
**这不就是 $\min(c,\max(b,x+a))$ 复合函数的形式吗？**    
对于 $+$ 操作，即 $c=V_{max},b=0,a=1$；  
对于 $-$ 操作，即 $c=V_{max},b=0,a=-1$；   
对于不成功的操作，即 $c=V_{max},b=0,a=0$；   
而且经验告诉我们，**这个函数是可以复合的！！！**  
证明如下：   

> 由于在网上翻遍了也没有对复合函数的详细证明，要么是“手玩一下”，要么是“易知”，要么是提都不提，但真的有这么容易吗？反正我是不会。     
捣敲了老半天，终于搞出来了。   
自己推的复合函数 $g(f(x))$ 推法：      
> 令 $f(x)=\min(c_1,\max(b_1,x+a_1)),g(x)=\min(c_2,\max(b_2,x+a_2))$，则   
> $$\begin{aligned}
g(f(x))&=\min(c_2,\max(b_2,\min(c_1,\max(b_1,x+a_1))+a_2)) \\  
&=\min(c_2,\max(b_2,\min(a_2+c_1,\max(a_2+b_1,x+a_1+a_2))))
\end{aligned}$$    
然后分类进行讨论：   
> (1) 若 $a_2+c_1<\max(a_2+b_1,x+a_1+a_2)$，则：   
> $$g(f(x))=\min(c_2,\max(b_2,a_2+c_1))$$   
> 然后注意到有一个**重要结论**：   
> $$\min(a,\max(b,c))=\max(b,\min(a,c))$$   
> 这个结论可以对 $a,b,c$ 大小关系分类去证明。    
> 所以就可以继续化简：   
> $$g(f(x))=\max(b_2,\min(c_2,a_2+c_1))$$   
> （其实情况 $1$ 并不需要继续化简，但情况 $2$ 必须这样同样化简，所以先给出）    
> (2) 若 $a_2+c_1\ge \max(a_2+b_1,x+a_1+a_2)$，则：   
> $$\begin{aligned}
g(f(x))&=\min(c_2,\max(b_2,\max(a_2+b_1,x+a_1+a_2)))\\
&=\min(c_2,\max(x+a_1+a_2,\max(b_2,a_2+b_1))) \\  
&=\max(x+a_1+a_2,\min(c_2,\max(b_2,a_2+b_1)))
\end{aligned}$$   
> 因此才有：   
> $$f(g(x))=\min(\max(b_2,\min(c_2,a_2+c_1))\ ,\  \max(\min(c_2,\max(b_2,a_2+b_1)),x+(a_1+a_2)))$$  
> 这个形式与 $\min(c,\max(b,x+a))$ 是吻合的。  
   
告诉我，对于一段序列的复合函数如何维护？   
**线段树！**   
噫吁嚱，豁然开朗呼！    
做法便明朗了：    
令每一个操作的 $t_i=Time_{i}-Time_{i-1}$。     
先将所有操作打入线段树，用线段树维护贡献。   
然后判断 $V_2$ 是否落在 $f(V_1)$ 的值域中。   
（因为 $V_1$ 的定义域不变，始终是 $[0,V_{max}]$）   
如果是，那么说明所有操作均有效时可以，$t$ 可以无穷大，输出 infinity。   
否则，将 $t_i$ 从大到小排序。   
一个一个枚举 $nowtime=t_i$，将所有 $t=nowtime$ 的操作的贡献从线段树中单点修改去掉。   
然后判断 $V_2$ 是否落在 $f(V_1)$ 的定义域中。   
即判断 $V_2\ge tree[1].calc(0)\text{且}V_2\le tree[1].calc(V_{max})$ 是否成立。   
如果成立，那么 $nowtime-1$ 即为 $t$ 的答案。   
为什么要 $-1$ 呢？    
因为此时的 $nowtime$ 表示所有 $\le nowtime$ 的操作均不合法，要使得 $t_i=nowtime$ 的操作不合法，就需要 $t<nowtime$，故应为 $nowtime-1$。  
最后确定 $t$ 即确定操作序列的状态后，直接二分 $V_1$，判断 $tree[1].calc(V_1)$ 与 $V_2$ 的大小关系即可。   
时间复杂度 $\mathcal{O}(n\log n)$。     
嘛，还有一点就是，那个，**操作 $1$ 一定是无效操作！！！**   
所以要忽略掉操作 $1$。   
别踩坑了。   
具体细节见代码。    
****    
### 三. 代码实现    
```cpp
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
const int maxn = 1e5 + 5;

template <typename T>
inline void read(T& x){
x = 0; int f = 1; char c = getchar(); while (c < '0' || c > '9') { if (c == '-') f = -f; c = getchar(); }
while (c >= '0' && c <= '9') { x = (x << 3) + (x << 1) + (c ^ 48), c = getchar(); } x *= f;
}
template <typename T, typename... Args>
inline void read (T &x, Args&... Arg) { read (x), read (Arg...); }

int n,Vmax,V2;
int Time[maxn],val[maxn];
struct Operation{
    int time,val,id;
}a[maxn];                       //存放操作序列
struct Segment{
    int a,b,c;                  //线段树维护函数min(c,max(b,x + a))
    int calc(int x){
        return min(c,max(b,x + a));
    }
}tree[maxn << 2];
inline int left(int x){
    return x << 1;
}
inline int right(int x){
    return x << 1 | 1;
}
inline void push_up(int p){
    int lson = left(p),rson = right(p);
    int a1 = tree[lson].a,b1 = tree[lson].b,c1 = tree[lson].c;
    int a2 = tree[rson].a,b2 = tree[rson].b,c2 = tree[rson].c;
    tree[p].c = max(b2,min(c2,c1 + a2));
    tree[p].b = min(c2,max(b2,b1 + a2));
    tree[p].a = a1 + a2;                        //这里的复合要手推一下,博客有详细证明
}
inline void build(int p,int l,int r){
    if(l == r){
        tree[p] = (Segment){val[l],0,Vmax};
        return;
    }
    int mid = (l + r) >> 1;
    build(left(p),l,mid);
    build(right(p),mid + 1,r);
    push_up(p);
}
inline void update(int p,int l,int r,int x){    //将操作x的贡献抹除掉
    if(l == r){
        tree[p] = (Segment){0,0,Vmax};
        return;
    }
    int mid = (l + r) >> 1;
    if(x <= mid)    update(left(p),l,mid,x);
    else update(right(p),mid + 1,r,x);
    push_up(p);
}
inline bool cmp(Operation x,Operation y){
    return x.time > y.time;
}
inline int get_V1(){        //由于复合函数对于f(V1)具有单调性,故在确定操作序列(即已经确定了t)后可以二分找V1
    int V1 = 0;
    int l = 0,r = Vmax,mid;
    while(l <= r){
        mid = (l + r) >> 1;
        if(tree[1].calc(mid) <= V2) V1 = mid,l = mid + 1;
        else r = mid - 1;
    }
    return V1;
}
int main(){

    read(n,Vmax,V2);
    for(int i=1;i<=n;i++){
        char c;
        cin >> c;
        if(c == '+')    val[i] = 1;
        else    val[i] = -1;
        read(Time[i]);
    }
    n--;                                    //将数组整体向左移了一格,至于为什么这么做嘛,第一步操作肯定是无效的
    for(int i=1;i<=n;i++){
        val[i] = val[i+1];                  //左移操作
        Time[i] = Time[i+1] - Time[i];      //由于t与间隔有关,所以只存t的阶段
        a[i] = (Operation){Time[i],val[i],i};
    }
    build(1,1,n);
    if(V2 >= tree[1].calc(0) && V2 <= tree[1].calc(Vmax)){      //所有操作都存在时满足(对于V1的值域[0,Vmax]经过复合函数后得到的值域包含了V2)那么t就是无穷解
        printf("infinity\n");
        return 0;
    }

    sort(a + 1,a + 1 + n,cmp);
    int i,j;
    for(i=1;i<=n;i=j){                      //从大到小枚举时间段t,并将操作一个一个从序列中减去,当V2恰好落在复合函数的值域中时,t最大,为nowtime-1(-1是因为要想让这些操作失效,必须<nowtime)
        int nowtime = a[i].time;
        for(j=i;a[j].time == a[i].time;j++)    //将所有这个时间段内的贡献抹去    
            update(1,1,n,a[j].id);
        if(V2 >= tree[1].calc(0) && V2 <= tree[1].calc(Vmax)){  //第一次满足时即为答案
            printf("%d %d\n",nowtime-1,get_V1());
            return 0;
        }
    }

    return 0;
}
```


---

## 作者：Azazеl (赞：1)

### 「CEOI2010」 MP3Player

#### 题意

>  $~~~~$ 给出 $n$ 次对音量的操作，每次操作为使音量 $+1$ 或 $-1$ ，同时若音量操作后超出 $[0,V_{\max}]$ 或该操作与上一个操作的时间间隔 $>t$ 则该操作无效（不论上一个操作是否有效）。已知若干次操作后的最终音量，求 $t$ 可能的最大值以及该最大值下可能的最大的初始音量。
>
> $~~~~$ $1\leq n\leq 2\times 10^5,2\leq V_{\max}\leq 5000$

#### 题解

$~~~~$ ~~线段树可以维护的东西增加了，线段树yyds~~

$~~~~$ 先给出一个暴力通用思路：枚举所有在操作中出现的 $t$ ，则对于任意一个初始音量 $V_1$，我们都可以 $\mathcal{O(n)}$求出其对应的结束音量 $V_2$ 。并且输出出来我们可以发现若将 $V_2$ 视作 $V_1$ 的函数，则该函数不降,故可以二分求出是否存在 $V_1$ 在该 $t$ 下使得结束音量为 $V_2$ 。时间复杂度：$\mathcal{O(n^2\log n)}$  ~~似乎一个subtask都过不了（~~

$~~~~$ 考虑继续发掘一下该函数的性质，可以发现该函数存在 $A,B$ ，使得 $[0,A)$ 内所有 $V_1$ 的 $V_2$ 相同，$[A,B)$ 内所有 $V_1$ 的 $V_2$ 每个相对前一个多 $1$ ，$[B,V_{\max}]$ 内所有 $V_1$ 的 $V_2$ 也相同。简单来说该函数依次是：常函数、一次函数、常函数。理性理解一下， $V_1$ 在从 $0$ 开始增长时中途一定会有一段时间卡在下界、增长到 $V_{max}$ 前有一段时间卡在上界，当然这段时间可以为空。那么显然，该函数的值域也一定是连续的整数区间。

$~~~~$ 由此，我们可以考虑维护两个常函数的值 $a,b$ 和一次函数的 $y=x+c$ 的 $c$ 。则当我们知道两段相连区间的 $a,b,c$ 时，我们就可以考虑复合两个函数得到这个大区间的 $a,b,c$ 。稍微手玩一下就可以推出 $\mathcal{O(1)}$ 转移，这点可以见代码。自然而然地，我们想到用线段树维护区间的函数值。

$~~~~$ 因此，我们仍然保留枚举所有可能的 $t$ ，然后每次在线段树上删除某个点对应的贡献，并检查该函数值域中是否有 $V_2$ 。该过程中每个点只会被删去一次，所以时间复杂度 $\mathcal{O(n\log n)}$ 。

#### 代码

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
int n,Vmax,V2;
int val[200005],Time[200005];
struct node{
	int val,Time,id;
	node(){}
	node(int V,int T,int I){val=V,Time=T,id=I;}
}P[200005];
struct Seg{
	#define ls p<<1
	#define rs p<<1|1
	#define lson p<<1,l,mid
	#define rson p<<1|1,mid+1,r
	struct Func{
		int a,b,c;
		Func(){}
		Func(int A,int B,int C){a=A,b=B,c=C;}
		int F(int x){return min(b,max(a,x+c));}
	}tr[800005];
	//a一平的值 b二平的值 c一次函数 y=x+c 
	void pushUp(int p)
	{
		tr[p].a=min(tr[rs].b,max(tr[rs].a,tr[ls].a+tr[rs].c));
		tr[p].b=max(tr[rs].a,min(tr[rs].b,tr[ls].b+tr[rs].c));
		tr[p].c=tr[ls].c+tr[rs].c;
	}
	void Build(int p,int l,int r)
	{
		if(l==r)
		{
			tr[p]=Func(0,Vmax,val[l]);
			return;
		}
		int mid=(l+r)>>1;
		Build(lson);Build(rson);
		pushUp(p);
	}
	void Modify(int p,int l,int r,int aim)
	{
		if(l==r)
		{
			tr[p]=Func(0,Vmax,0);
			return;
		} 
		int mid=(l+r)>>1;
		if(aim<=mid) Modify(lson,aim);
		if(mid<aim)  Modify(rson,aim);
		pushUp(p);
	} 
}Seg;
int Calc()
{
	int l=0,r=Vmax,mid,Ans=0;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(Seg.tr[1].F(mid)<=V2) l=mid+1,Ans=mid;
		else r=mid-1;
	}
	return Ans;
}
bool cmp(node x,node y){return x.Time>y.Time;}
int main() {
	scanf("%d %d %d",&n,&Vmax,&V2);
	char S[10];
	for(int i=1;i<=n;i++)
	{
		scanf("%s %d",S+1,&Time[i]);
		val[i]=(S[1]=='+')?1:-1;
	}n--;
	for(int i=1;i<=n;i++)
	{
		val[i]=val[i+1];
		Time[i]=Time[i+1]-Time[i];
		P[i]=node(val[i],Time[i],i);
	}
	Seg.Build(1,1,n);
	sort(P+1,P+1+n,cmp);
	if(Seg.tr[1].F(0)<=V2&&V2<=Seg.tr[1].F(Vmax)) return puts("infinity")&0;
	int j;
	for(int i=1;i<=n;i=j)
	{
		int Tmp=P[i].Time;
		for(j=i;P[j].Time==P[i].Time;j++) Seg.Modify(1,1,n,P[j].id);
		if(Seg.tr[1].F(0)<=V2&&V2<=Seg.tr[1].F(Vmax)) return printf("%d %d\n",P[i].Time-1,Calc())&0;
	}
	return 0;
}
```



---

## 作者：songhongyi (赞：0)

考虑二分，可惜没有好用的单调性，考虑枚举 $t$。

考虑 $t$ 已知时怎么做。我们联想到一个熟知的结论，即两个形如 $\min\left(c,\max\left(b,x+a\right)\right)$ 的函数的复合仍为此形式。证明如下：

设 $f(x) = \min(c_1, \max(b_1, x + a_1))$，$ g(x) = \min(c_2, \max(b_2, x + a_2))$。

那么我们可以推式子：
$$
\begin{aligned}g(f(x)) &= \min(c_2, \max(b_2, \min(c_1, \max(b_1, x + a_1)) + a_2))\\&= \min(c_2, \max(b_2, \min(c_1 + a_2, \max(b_1 + a_2, x + a_1 + a_2))))\\&= \min(\max(b_2, \min(c_2, c_1 + a_2)), \max(\min(c_2,\max(b_2,b_1+a_2)), x + (a_1 + a_2))),\\\end{aligned}
$$
（证明誊抄自 ABC196 E 题解）

我们发现题目中的两种操作，分别对应了 $x \gets \min (V_{\max},x+1)$ 与 $x \gets \max (0,x-1)$ 都符合上面的形式。因此我们通过维护 $a,b,c$ 三个参数就可以得出操作序列对应的函数。得到最终函数形式后，不难判断是否有解且得出 $V_1$。复杂度 $O(n)$。

这样我们至少能够判断 `infinity` 的情况了。这种情况当且仅当执行所有操作可以达到 $V_2$。因而将所有操作表示成的函数依次符合，如果此时 $V_2$ 在值域内就是 `infinity`。

这个过程显然不好做到更快了，那么再套上枚举的复杂度就到 $O(n^2)$ 了。但我们发现一个性质，即一个操作是否进行是与 $t$ 单调的。也就是说，在 $t$ 递增时，每个操作只会加入一次。通过线段树维护一次函数的方式维护加入操作并统计答案，即可在 $O(n \log n)$ 的复杂度内完成此题。（可以认为不执行的操作是一个 $a=0,b=0,c=V_{\max}$ 的操作）。

Hint：按照题意，第一次操作没有用，小心踩坑。

实现细节见代码：

```cpp
//
// Problem: P6520 [CEOI2010 day2] mp3player
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P6520
// Memory Limit: 256 MB
// Time Limit: 500000 ms

#include <iostream>
#include <queue>
#include <vector>
#define lson x * 2
#define rson x * 2 + 1
using namespace std;
struct Node
{
    int a, b, c;
    Node() {}
    Node( int a, int b, int c )
    {
        this->a = a;
        this->b = b;
        this->c = c;
    }
    int calc( int val )
    {
        return min( c, max( b, val + a ) );
    }
} tree[ 400010 ];
Node merge( Node x, Node y )
{
    Node res;
    res.a = x.a + y.a;
    res.b = min( y.c, max( y.b, x.b + y.a ) );
    res.c = max( y.b, min( y.c, x.c + y.a ) );
    return res;
}
int val[ 100010 ], vmax;
void build( int x, int l, int r )
{
    if ( l == r )
    {
        tree[ x ] = Node( val[ l ], 0, vmax );
        return;
    }
    int mid = ( l + r ) / 2;
    build( lson, l, mid );
    build( rson, mid + 1, r );
    tree[ x ] = merge( tree[ lson ], tree[ rson ] );
}
void modify( int x, int l, int r, int p )
{
    if ( l == r )
    {
        tree[ x ] = Node( 0, 0, vmax );
        return;
    }
    int mid = ( l + r ) / 2;
    if ( p <= mid )
    {
        modify( lson, l, mid, p );
    }
    else
    {
        modify( rson, mid + 1, r, p );
    }
    tree[ x ] = merge( tree[ lson ], tree[ rson ] );
}
int tim[ 100010 ];
struct T
{
    int t, id;
};
auto cmp = []( T a, T b ) { return a.t < b.t; };
priority_queue< T, vector< T >, decltype( cmp ) > q( cmp );
int sol( int v2, Node node )
{
    int l = 0, r = vmax;
    int ans = 0;
    while ( l <= r )
    {
        int mid = ( l + r ) / 2;
        if ( node.calc( mid ) <= v2 )
        {
            l = mid + 1;
            ans = mid;
        }
        else
        {
            r = mid - 1;
        }
    }
    return ans;
}
int main()
{
    cin.tie( 0 );
    int n, v2;
    cin >> n >> vmax >> v2;
    for ( int i = 1; i <= n; i++ )
    {
        char c;
        cin >> c >> tim[ i - 1 ];
        if ( c == '+' )
        {
            val[ i - 1 ] = 1;
        }
        else
        {
            val[ i - 1 ] = -1;
        }
    }
    n--;
    for ( int i = 1; i <= n; i++ )
    {
        T tmp;
        tmp.id = i;
        tmp.t = tim[ i ] - tim[ i - 1 ];
        q.push( tmp );
    }
    build( 1, 1, n );
    Node t = tree[ 1 ];
    if ( t.calc( 0 ) <= v2 and t.calc( vmax ) >= v2 )
    {
        cout << "infinity" << endl;
        return 0;
    }
    while ( not q.empty() )
    {
        T tmp = q.top();
        while ( not q.empty() and q.top().t == tmp.t )
        {
            modify( 1, 1, n, q.top().id );
            q.pop();
        }
        t = tree[ 1 ];
        if ( t.calc( 0 ) <= v2 and t.calc( vmax ) >= v2 )
        {
            cout << tmp.t - 1 << " " << sol( v2, tree[ 1 ] ) << endl;
            return 0;
        }
    }
}
```





---

## 作者：Blithe_C (赞：0)

[原题](https://www.luogu.com.cn/problem/P6520)的翻译已经很好了.

***
需要分析题意的好题.

本题中，我们要求的是一个最大解：最大符合操作结果的锁键时间间隔 $T$ 和初始音量 $V_s$；已知的条件只有操作序列和操作结果 $V_e$（我们称一个操作序列和操作结果构成一个**操作局**）. 比较现实的分析方式大概只有从 $V_e$ 沿操作序列倒推回去了. 然而由于锁键时间的存在，某些操作是无效的，这给倒推造成麻烦. 

因此本题的 puzzle 主要在两个方面，一个是音量加减操作及其累加效果，一个是锁键时间对操作的影响.

先看后者. 题目提示我们 $T = 0$ 时总是有解，因为这相当于全部操作无效；而在极端情形下，$T$ 可能为任意大的正数，这相当于所有操作都有效时本局仍然有解，样例 2 就是一例.

$T$ 从 $0$ 到无穷大，操作从全部无效趋于全部有效，故应从小到大枚举 $T$. 注意，本题的 $T$ 可达 $2×10^9$，因此必须离散化枚举，而不是逐一枚举：我们建一个所有操作的小根堆，比较键值是时间差 $\Delta t$，然后循环取出最小元素（同时取出所有键值相同的元素，设此键值为 $T_0$），使对应的操作由无效变为有效，然后询问此时操作局是否有解（并找到其中 $V_s$ 最大的解），直到小根堆只剩下第一个操作（其一定无效）.

这样每当操作局有解，就意味着不仅当前 $T_0$ 是操作局的解，而且设下一个取出的键值为 $T_0'$，则 $[T_0,T_0')$ 里的整数都是解. 那么只需在每次有解时更新  $V_s$；并在每次无解且前一次有解时，把  $T$ 更新为此时的 $T_0-1$. 假如最后一轮循环即 $T_0$ 最大时有解，则 $T_0'=∞$，输出 ``infinity``.

***
下面需要实现「询问此时操作局是否有解」的算法：
> 假如给出了 $V_e$ 和一个全部有效的操作序列 $A$（值均为$ +1$ 或 $-1$），怎么快速确定有无解以及最大的 $V_s$？

这个问题有意义就是因为音量上限 $V_{max}$ 和下限 $0$ 的存在，它们会**吸收**多余的 $+1/-1$ 操作，令情况复杂. 从右向左看，在音量没有**碰顶 / 碰底**时，该位置的音量值显然能严格靠倒推操作序列确定；一旦碰了顶 / 底，音量变化就还依赖于起始位的选择了.

称“碰顶”的位置为 $roof$ 位、“碰底”的位置为 $floor$ 位；称从右向左第一个 $roof$ 位（如果有）为 $roof_0$，从右向左第一个 $floor$ 位（如果有）为 $floor_0$. 极端情况下，碰顶 / 碰底可能不发生. 易见，此时 $V_s$ 总是等于 $V_e-\Sigma A_i$，且 $A$ 的后缀和总在 $(V_e-V_{max},V_e)$ 范围内. 记 $lower=V_e-V_{max}$、$upper=V_e$，$A$ 的后缀和序列为 $S$.

**如果序列从右向左倒推操作序列先碰到的是顶**，称这是一个**先顶序列**；**如果先碰到的是底**，称这是一个**先底序列**. 易知（从右向左）先顶序列第一个使得 $S_i=lower$ 的下标 $i$ 就是 $roof_0$；先底序列第一个使得 $S_i=upper$ 的下标 $i$ 就是 $floor_0$.

我们想一下什么操作序列会造成无解. 根据样例 1 解释，不合法的根源是：i) $roof$ 位左边紧接着一个 $-1$ 操作，或 ii) $floor$ 位左边紧接一个 $+1$ 操作，两种情况. 从后缀和的角度来看呢？不难证明，情况 i) 会使后缀和 $S$ **超过“下界”** $lower$，即 $S_{roof-1}<lower$；情况 ii) 会导致后缀和**超过“上界”**，$S_{floor-1}>upper$.

这样看来，是不是我们每次只用看后缀和 $S$ 是否曾越过上下界，亦即检验**后缀和的最大及最小项**有没有超过 $lower$ 和 $upper$，就可以判定有无解了？不全对，但基本对了！稍后会找出余下的细节问题，现在先看怎么维护上述信息.

需要写一个数据结构，其：

i) 维护一个 $0/+1/-1$ 构成的序列（需要维护无效操作，其不能改变音量，数值为 $0$）；

ii) 支持单点数值更改（随着枚举 $T$，操作从无效变为有效，要将相应的项从 $0$ 改成输入的 $+1/-1$）；

iii) 支持查询最大/最小后缀和.

由于询问的是后缀和，我们干脆维护后缀和而非原序列. 此时 ii) 的单点修改就变成了区间的数值修改，因此使用线段树是很自然的了.

我们还要做一件事：求出解中的最大初始音量 $V_s$. 注意，把初始音量设得尽量高，相当于尽可能多吸收 $+1$ 操作、而尽量不吸收 $-1$ 操作. 因此：
1. 如果一个合法操作序列 $A$ 的最小后缀和大于 $lower$，即没有碰过顶. 此时秉持尽量不吸收 $-1$ 操作的最优原则，会发现没有任何操作能被吸收，$\max V_s$ 就是从 $V_e$ 倒推得到的值. $\max V_s = V_e-\Sigma A_i$.
2. 如果一个合法操作序列 $A$ 的最小后缀和不大于 $lower$，即碰过顶. 观察样例 1 发现，可以直接将 $V_s$ 设为 $V_{max}$，且可以证明这一定保持合法性. $\max V_s = V_{max}$.

请注意我们还要在后缀和序列 $S$ 最后补一个 $0$，这个值始终不修改，对应着不执行任何操作. 为什么这样做？考虑一下 $V_e=V_{max}$ 的边界情况即可.

***
但我们并没有做完. 如果认为有解的充要条件是操作序列的最大后缀和 $\leq upper$ 且最小后缀和 $\geq lower$，会在一些数据点上 ``WA``.

这是因为条件给紧了，实际上后缀和可以突破这两个界. 考虑 $V_{max}=5$，$V_e=3$，且操作序列的一个后缀如下：

| $A$ | ... | $-$ | $-$ | $-$ | $-$ | $-$ | $-$ | $-$ | $-$ | $-$ | $-$ | $+$ | $+$ | $+$ | $+$ | $+$ | $+$ | $+$ | $-$ | $-$ |  |
| ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
| $S$ | ... | $-5$ | $-4$ | $-3$ | $-2$ | $-1$ | $0$ | $1$ | $2$ | $3$ | $4$ | $5$ | $4$ | $3$ | $2$ | $1$ | $0$ | $-1$ | $-2$ | $-1$ | $0$ |
| 位置 | ... | $19$ | $18$ | $17$ | $16$ | $15$ | $14$ | $13$ | $12$ | $11$ | $10$ | $9$ | $8$ | $7$ | $6$ | $5$ | $4$ | $3$ | $2$ | $1$ | $0$ |

序列合法，但后缀和既突破过 $lower$ 也突破过 $upper$. 为什么？因为这个序列显然碰过顶，故在 $roof$ 位（上面的 $2$ 号位）以左能**无限吸收** $+1$ 操作；也显然碰过底，在 $floor$ 位（上面的 $9$ 号位）以左能无限吸收 $-1$ 操作.

再结合前文「i) $roof$ 位左边紧接着一个 $-1$ 操作，或 ii) $floor$ 位左边紧接一个 $+1$ 操作，均不合法」和「i) 会使后缀和 $S$ 超过“下界” $lower$，即 $S_{roof-1}<lower$；ii) 会导致后缀和超过“上界”，$S_{floor-1}>upper$」，可以得出以下性质：
1. 合法序列的 $roof$ 位以左能有任意多个 $+1$，$floor$ 位以左能有任意多个 $-1$.
2. 合法序列的 $roof$ 位以左不能出现 $S_i<lower$ 的位置，**但前提是此 $roof$ 位以右没有 $floor$ 位**，否则违反上一条性质；同理，$floor$ 位以左不能出现 $S_i>upper$ 的位置，**但前提是此 $floor$ 位以右没有 $roof$ 位**.

> 结论：**当序列的前缀和突破了 $lower$ 或 $upper$ 时**，性质 1 导致解仍可能存在；根据性质 2，只需多做一步检验：对于**先顶序列**，有 $roof_0>floor_0$，**检查 $[floor_0,roof_0]$ 这个区间内有无后缀和 $S_i$ 小于 $lower$**（注意此时 $floor_0$ 不确定，但其最大为从右向左第一个使得 $S_{i_0}=upper$ 的下标 $i_0$，因此只需检查区间 $[i_0,roof_0]$ 的最大值），是则无解；同理对于**先底序列**，**检查 $[roof_0,floor_0]$ 这个区间内有无后缀和 $S_i$ 大于 $upper$**，是则无解.

为此，线段树还需要维护**从右向左第一个**权值 $\leq lower$ 或 $\geq upper$ 的叶节点位置，且这两个不等号可以改为等号. 幸运的是，这可以在 $O(\log n)$ 时间内完成，可参见下面的代码.

***
```
#include <bits/stdc++.h>

#define IOS_SPEED std::ios::sync_with_stdio(false)

using std::cin, std::cout;
using std::pair;
using std::priority_queue;
using std::max, std::min;

constexpr int INF = 1e9;

struct stroke{ // 一次操作
	int num, val, gap; // 操作编号, 操作效果, 操作时间差
};
bool operator <(const stroke &A, const stroke &B){return A.gap>B.gap;}

class segtree{ // 维护操作序列后缀和的线段树
	public:
		int left, right;
		int vmin, vmax, lazy;
		segtree *L, *R;
		static int first_roof, first_floor;
		inline void push_down();
		void create(int lower, int upper, int init);
		void update(int start, int end, int delta);
		pair<int, int> query(int start, int end);
		void update_roof(int lower);
		void update_floor(int upper);
		void wipe();
};

int segtree::first_roof = 0; int segtree::first_floor = 0; // 初始化为 0, 表示两个位置不存在

void segtree::create(int lower, int upper, int init){ // 此 lower, upper 是区间范围, 不是上述上下界
	left = lower; right = upper;
	L = R = nullptr; lazy = 0;
	if(left==right){
		vmin = vmax = init; return;
	}
	int mid = (left+right)>>1;
	auto LT = new segtree; LT->create(lower, mid, init); L = LT;
	auto RT = new segtree; RT->create(mid+1, upper, init); R = RT;
	vmax = max(L->vmax, R->vmax); vmin = min(L->vmin, R->vmin);
}

inline void segtree::push_down(){
	if(left!=right&&lazy!=0){
		L->vmax += lazy; R->vmax += lazy;
		L->vmin += lazy; R->vmin += lazy;
		L->lazy += lazy; R->lazy += lazy;
		lazy = 0;
	}
}

void segtree::update(int start, int end, int delta){
	if(start<=left&&end>=right){
		vmax += delta; vmin += delta; lazy += delta;
		return;
	}
	if(start>right||end<left) return;
	push_down();
	L->update(start, end, delta); R->update(start, end, delta);
	vmax = max(L->vmax, R->vmax); vmin = min(L->vmin, R->vmin);
}

pair<int, int> segtree::query(int start, int end){
	if(start<=left&&end>=right) return {vmin, vmax};
	if(start>right||end<left) return {INF, -INF};
	push_down();
	auto [L_min, L_max] = L->query(start, end);
	auto [R_min, R_max] = R->query(start, end);
	return {min(L_min, R_min), max(L_max, R_max)};
}

void segtree::update_roof(int lower){
    if(left==right){
        if(vmin==lower) first_roof = max(first_roof, left);
        return;
    }
    push_down();
    if(R->vmin<=lower) R->update_roof(lower);
    else L->update_roof(lower); // 如果右子树的值从未达到 lower, first_roof 只能在左子树
}

void segtree::update_floor(int upper){
    if(left==right){
        if(vmax==upper) first_floor = max(first_floor, left);
        return;
    }
    push_down();
    if(R->vmax>=upper) R->update_floor(upper);
    else L->update_floor(upper); // 如果右子树的值从未达到 upper, first_floor 只能在左子树
}

void segtree::wipe(){
	if(L!=nullptr) L->wipe(); if(R!=nullptr) R->wipe(); delete this;
}

int strokes, v_max, v_end;
priority_queue<stroke> ops;

pair<int, int> optimal_result(){
	int lower = v_end-v_max, upper = v_end;
	auto RT = new segtree; RT->create(1, strokes, 0);
	int lock_gap = 0, v_start = v_end; // 对应最坏情况下的解
	bool cur_valid = false, prev_valid = true;
	while(ops.size()>1){ // 循环到只剩第一个操作为止
		int cur_gap = ops.top().gap;
		while(ops.top().gap==cur_gap){ // 取出所有时间差相同的操作
			auto [num, val, gap] = ops.top(); ops.pop();
			RT->update(1, num, val); // 更新叶节点信息
		}
		auto [smin, smax] = RT->query(1, strokes); // 查询后缀和最值
		if(smin>=lower&&smax<=upper) cur_valid = true; // 如果后缀和没有超过 lower 和 upper, 一定有解
		else{
			RT->first_roof = RT->first_floor = 0;
			RT->update_roof(lower); RT->update_floor(upper);
			if(RT->first_roof==0||RT->first_floor==0) cur_valid = false; // 如果后缀和超过了 lower 或 upper, 顶和底必须都碰过才有解
			else if(RT->first_roof>RT->first_floor) // 先顶序列
				cur_valid = (RT->query(RT->first_floor, RT->first_roof).first>=lower);
			else // 先底序列
				cur_valid = (RT->query(RT->first_roof, RT->first_floor).second<=upper);
		}
		if(!cur_valid){
			if(prev_valid) lock_gap = cur_gap-1;
			prev_valid = cur_valid;
		}
		else{
			v_start = (smin<=lower)? v_max: (v_end-RT->query(1, 1).first);
			prev_valid = cur_valid;
			if(ops.size()==1) lock_gap = INF;
		}
	}
	RT->wipe();
	return {lock_gap, v_start};
}

void interface(){
	cin >> strokes >> v_max >> v_end;
	char sign; int cur_time = 0, prev_time = -1;
	for(int i=0; i<strokes; ++i){
		cin >> sign >> cur_time;
		int num = i, val = (sign=='+')? 1: (-1), gap = (prev_time==-1)? INF: (cur_time-prev_time);
		ops.push({num, val, gap});
		prev_time = cur_time;
	}
	auto [lock_gap, v_start] = optimal_result();
	if(lock_gap==INF) cout << "infinity\n";
	else cout << lock_gap << " " << v_start << "\n";
	while(!ops.empty()) ops.pop();
}

int main()
{
	IOS_SPEED;
	interface();
	return 0; 
}
```

算法时间复杂度 $O(n \log n)$，空间复杂度 $O(n)$.

---

