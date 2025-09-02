# [ABC217H] Snuketoon

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc217/tasks/abc217_h

AtCoder 社が開発したゲーム『スヌケトゥーン』は、プレイヤーがすぬけ君を操作して水鉄砲から飛んでくる水を回避するゲームです。

ゲームのステージは無限に続く数直線からなり、ゲーム開始時点ですぬけ君は地点 $ 0 $ にいます。  
 ゲーム開始直後から、すぬけ君は $ 1 $ 秒ごとに「 $ 1 $ 小さい地点に移動」「 $ 1 $ 大きい地点に移動」「動かない」の $ 3 $ 択から行動を選べます。より厳密には、すぬけ君がゲーム開始後 $ t $ 秒 $ (t\ \geq\ 0 $, $ t $ は整数$ ) $ の時点で地点 $ p $ にいるとき、 $ t+1 $ 秒の時点では地点 $ p-1 $ ・地点 $ p $ ・地点 $ p+1 $ の $ 3 $ ヵ所のいずれかに行くことができます。

すぬけ君は水鉄砲から発射された水を浴びるとダメージを受けてしまいます。水鉄砲は $ N $ 回発射されて、 $ i $ 回目の発射は $ T_i,\ D_i,\ X_i $ を用いて次のように表されます。

- ゲーム開始から $ T_i $ 秒後に左右いずれかから水が発射されます。すぬけ君が $ T_i $ 秒の時点でいる地点を $ p $ としたとき、ダメージを受ける範囲および値は次の通りです。 
  - $ D_i\ =\ 0 $ のとき、$ p\ \lt\ X_i $ の範囲にいると $ X_i\ -\ p $ のダメージを受ける。
  - $ D_i\ =\ 1 $ のとき、$ X_i\ \lt\ p $ の範囲にいると $ p\ -\ X_i $ のダメージを受ける。

プロゲーマーの高橋君は、攻略情報をツイートするために $ N $ 回目の水鉄砲の発射が終わった後のすぬけ君の合計ダメージを最小化することにしました。高橋君が合計ダメージを最小化するようにすぬけ君を操作したときの合計ダメージを求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ T_1\ \lt\ T_2\ \lt\ \dots\ \lt\ T_N\ \leq\ 10^9 $
- $ D_i $ $ (1\ \leq\ i\ \leq\ N) $ は $ 0 $ または $ 1 $
- $ -10^9\ \leq\ X_i\ \leq\ 10^9 $ $ (1\ \leq\ i\ \leq\ N) $
- 入力は全て整数である。

### Sample Explanation 1

便宜上 $ t $ をゲーム開始から経過した秒数を表す変数とします。全ての水鉄砲の発射が終了するまでのすぬけ君の最適な動きは以下の通りです。 - $ t\ =\ 0 $ のときすぬけ君は地点 $ 0 $ にいます。すぬけ君は $ 1 $ 大きい地点に移動します。 - $ t\ =\ 1 $ のときすぬけ君は地点 $ 1 $ にいて、 $ 1 $ 回目の水鉄砲の発射により $ 2 $ のダメージを受けます。すぬけ君は $ 1 $ 小さい地点に移動します。 - $ t\ =\ 2 $ のときすぬけ君は地点 $ 0 $ にいます。すぬけ君は移動しません。 - $ t\ =\ 3 $ のときすぬけ君は地点 $ 0 $ にいて、 $ 2 $ 回目の水鉄砲の発射によるダメージを受けません。すぬけ君は $ 1 $ 大きい地点に移動します。 - $ t\ =\ 4 $ のときすぬけ君は地点 $ 1 $ にいて、 $ 3 $ 回目の水鉄砲の発射により $ 5 $ のダメージを受けます。 このときすぬけ君は合計で $ 7 $ のダメージを受けるので、 $ 7 $ を出力します。

## 样例 #1

### 输入

```
3
1 0 3
3 1 0
4 0 6```

### 输出

```
7```

## 样例 #2

### 输入

```
3
1 0 1
6 1 1
8 0 -1```

### 输出

```
0```

## 样例 #3

### 输入

```
5
1 0 1000000000
2 1 -1000000000
3 0 1000000000
4 1 -1000000000
5 0 1000000000```

### 输出

```
4999999997```

# 题解

## 作者：绝顶我为峰 (赞：14)

先整个暴力 dp，设 $f_{i,j}$ 表示 $T_i$ 时刻角色在 $j$ 可能的最小伤害，转移就枚举上一次在哪，容易得到转移方程 $f_{i,j}=\min\limits_{k=j-len}^{j+len}\{f_{i-1,k}\}+|j-X_i|[(j>X_i)=D_i]$，其中 $len=T_i-T_{i-1}$。

直接做是 $O(nV)$ 的，考虑优化。

首先把 $f_{i,j}$ 看成一个关于 $j$ 的函数，有结论 $f_{i,j}$ 是一个**线性分段下凸函数**。

线性和分段是显然的，接下来证明下凸性。

考虑归纳证明，$f_{0,j}$ 显然成立，考虑一次转移，转移方程的后半部分的函数图像只有两种形态，分别形如```\_```（对应 $D_i=0$ 的情况）和```_/```（对应 $D_i=1$ 的情况），且斜线部分的斜率是 $1$ 或 $-1$，是下凸的。

方程的前半部分是对一个下凸函数取区间 $\min$，这个操作等价于将函数最小值左右两侧的图像分别向两边平移，也是下凸函数。

两个下凸函数相加，得到的还是下凸函数，证明分别对两个下凸函数求二阶导即可，不再赘述。

因此 $f_{i,j}$ 是一个**线性分段下凸函数**，这启示我们使用 $\mathrm{slope\ trick}$ 加速 dp。

具体来说使用大根堆和小根堆维护分别维护下凸壳斜率为 $0$ 的区间的两侧的凸壳的拐点（注意堆中的元素表示斜率在这个位置改变了**恰好** $1$，因此如果在某个点变化大于 $1$ 要在堆中加入多个元素），一次转移本质上是把凸壳左侧向左平移 $len$ 个单位，凸壳右侧向右平移 $len$ 个单位，这可以通过直接打 tag 实现，然后再加入方程后半部分的函数，这部分就是在 $X_i$ 位置插入一个拐点，根据 $X_i$ 在斜率是 $0$ 的区间的左侧、右侧或当中分类讨论贡献，插入之后更新一下斜率是 $0$ 的区间即可。

具体实现还是要看代码，感觉这个东西比较难讲清楚……

时间复杂度 $O(n\log n)$。

```cpp
#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;
#define int long long
int n,ans,lst;
inline int read()
{
    int x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9')
    {
        if(c=='-')
            f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9')
    {
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
signed main()
{
    n=read();
    priority_queue<int> q1;
    priority_queue<int,vector<int>,greater<int> > q2;
    int tag1=0,tag2=0;
    for(int i=1;i<=n;++i)
    {
        q1.emplace(0);
        q2.emplace(0);
    }
    for(int i=1;i<=n;++i)
    {
        int t=read(),d=read(),x=read(),len=t-lst;
        lst=t;
        tag1-=len;
        tag2+=len;
        if(d==0)
        {
            if(x>q2.top()+tag2)
            {
                ans+=x-q2.top()-tag2;
                q1.emplace(q2.top()+tag2-tag1);
                q2.pop();
                q2.emplace(x-tag2);
            }
            else
                q1.emplace(x-tag1);
        }
        else
        {
            if(x<q1.top()+tag1)
            {
                ans+=q1.top()+tag1-x;
                q2.emplace(q1.top()+tag1-tag2);
                q1.pop();
                q1.emplace(x-tag1);
            }
            else
                q2.emplace(x-tag2);
        }
    }
    cout<<ans<<'\n';
    return 0;
}
```

---

## 作者：柳易辰 (赞：5)

Slope Trick 模板题

考虑设计一个 DP，$f_{i,x}$ 表示处理到第 $i$ 个任务，横坐标为 $x$ 时的受到伤害最小值。

DP 方程：$f_{i,x}=\max(x_i-x,0)+\min(f_{i-1,x'}+|x'-x|)(|x'-x|\leqslant t_i-t_{i-1})$，这是 $d=0$ 的情况，$d=1$ 的情况是类似的。

我们把 $f_{i,x}$ 关于 $x$ 的函数画到平面直角坐标系上，容易发现这是个凸函数，原因在于：DP 转移中取 $\min$ 相当于函数极值左边向左平移，函数极值右边向右平移，加 $\max$ 的部分相当于加凸函数，函数凸性不变。

我们用大根堆存极值左侧的所有拐点，每两个相邻拐点之间的斜率相差均为 1，极值右侧的拐点则用小根堆存。

取 $\min$ 相当于把左侧拐点向左平移 $t_i-t_{i-1}$，右侧拐点向右平移 $t_i-t_{i-1}$。打标记即可。加 $\max$ 需要按照 $x_i$ 的位置分类。

设左侧极值点为 $pl$，右侧极值点为 $pr$，分类讨论：

1. $d=0,x\leqslant pr$，相当于左侧有一个新的拐点 $x$。
2. $d=0,x>pr$，右侧极值点进入左侧（因为右侧最左的线段斜率由 1 变为 0），右侧有一个新的拐点 $x$，此时极值更新，需要更新答案。
3. $d=1,x\geqslant pl$，相当于右侧有一个新的拐点 $x$。
4. $d=1,x<pl$，左侧极值点进入右侧（因为左侧最右的线段斜率由 -1 变为 0），左侧有一个新的拐点 $x$，此时极值更新，需要更新答案。

本题初始化时，每个堆中需要放 $n$ 个 0，原因在于假设当前 $f_i$ 图像的定义域是 $[-x,x]$，如果当前 $x_i<-x$ 或 $x_i>x$，我们会错误地增加一个定义域外的拐点。解决方法就可以初始化中放入 $n$ 个 0，那么就算加入了错误的拐点也不会被堆顶取出，不影响答案。

---

## 作者：roger_yrj (赞：5)

## [ABC217H] Snuketoon

设 $f_{i,j}$ 表示到了 $T_i$ 时刻位置为 $j$ 的最小伤害。容易写出转移方程：

- 当 $D_i=0$ 时，$$f_{i,j}=\max\{0,X_i-j\}+\min\limits_{|j-k|\le T_i-T_{i-1}}f_{i-1,k}$$
- 当 $D_i=1$ 时，$$f_{i,j}=\max\{0,j-X_i\}+\min\limits_{|j-k|\le T_i-T_{i-1}}f_{i-1,k}$$

仔细观察发现，$\max\{0,X_i-j\}$ 和 $\max\{0,j-X_i\}$ 都是凸函数。根据归纳法易证 $f_i$ 也为凸函数。（转移中有绝对值函数时也是类似的）

我们考虑利用 $f_i$​ 的凸性来优化转移。

对于这种转移，我们通常使用优先队列来维护拐点位置。对于这题，我们使用两个优先队列来维护左右两边的拐点。

设斜率为 $0$ 的段左右端点分别是 $l,r$。

转移的两部分是无关的。先看后半部分。

后半部分的实质就是将 $\le l$ 的部分向左平移 $T_i-T_{i-1}$ 个单位，将 $\ge r$ 的部分向右平移 $T_i-T_{i-1}$ 个单位。只需要维护两个 $tag$ 即可完成此操作。（或者你直接用 $T_i$ 也行）

再来观察前半部分。由于两种 $D_i$ 的情况是对称的，所以这里只讲 $D_i=0$ 的情况。

我们观察发现 $\max\{0,X_i-j\}$ 的函数图像大概是 `\_` 的形状，我们分类讨论拐点 $X_i$ 的位置：

当 $X_i\le r$​ 时，相当于函数的左边增加了一个拐点，没什么大的变化，答案也不变。

当 $X_i> r$ 时，那么 $[l,r]$ 这段的斜率变成了 $-1$ ，所以 $r$ 要从右边的优先队列去到左边的优先队列里，同时更新答案。

时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,tagl,tagr;
ll ans;
priority_queue<ll>L;
priority_queue<ll,vector<ll>,greater<ll> >R;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)L.push(0),R.push(0);
	ll t,x,d,lst=0;
	for(int i=1;i<=n;i++){
		scanf("%lld%lld%lld",&t,&d,&x);
		tagl-=t-lst;
		tagr+=t-lst;
		lst=t;
		if(!d){
			if(x<=R.top()+tagr)L.push(x-tagl);
			else{
				ans+=x-R.top()-tagr;
				L.push(R.top()+tagr-tagl);
				R.pop();
				R.push(x-tagr);
			}
		}else{
			if(x>=L.top()+tagl)R.push(x-tagr);
			else{
				ans+=L.top()+tagl-x;
				R.push(L.top()+tagl-tagr);
				L.pop();
				L.push(x-tagl);
			}
		}
	}
	cout<<ans;
}
```

---

## 作者：创世游戏科技 (赞：2)

# [ABC217H] Snuketoon

## 思路解析

容易设置状态 $f_{i,j}$ 表示当前完成了第 $i$ 个事件位置在 $j$ 处受到的最小伤害。

发现如果想要完成 $i$ 个事件必须已经完成了前 $i-1$ 个事件，前面那些状态与我们的转移无关。我们只需要考虑 $i-1$ 时刻在何位置即可。

当 $D_i=0$ 时我们有转移

$$f_{i,j}=\min\limits_{j-(T_i-T_{i-1})}\limits^{j+(T_i-T_{i-1})}f_{i-1,k}+\max(0,X_i-x) $$

考虑后半部分，它的函数图像是这样的。

![](https://cdn.luogu.com.cn/upload/image_hosting/5imdne7p.png)

显然是个下凸函数。

然后我们考虑右半部分是多个这种函数的叠加。仍然是个下凸函数。

![](https://cdn.luogu.com.cn/upload/image_hosting/uw7haaiu.png)

这样的下凸函数。

那么我们考虑左半部分相当于什么。对于一个线性函数取最小值就相当于这个区间里的所有点都变成了区间的左端点值或者右端点的值。

就相当于左半部分向左平移了 $T_i-T_{i-1}$ 个单位，右半部分向右平移了 $T_i-T_{i-1}$ 个单位。

![](https://cdn.luogu.com.cn/upload/image_hosting/dn0f2q5d.png)

具体解释起来紫色部分因为能取到水平线导致它也水平了，红色部分变成了它右侧区间内的最小值，这个时候可以类比成平移。

我们发现如果存在水平区间，那么这个时候答案可以取到 $0$ ，我们不需要修改答案。

当新加入一条线段时，我们需要先把老的凸包进行平移，然后分类讨论。

$L$ 是下降部分最后的拐点，$R$是上升部分第一个拐点。


![](https://cdn.luogu.com.cn/upload/image_hosting/9g562qob.png)

先不考虑平移，如果 $X_i\leq R$。

此时两条线段叠加仍然能取到最小值。答案无需变化。


![](https://cdn.luogu.com.cn/upload/image_hosting/uuv2eahr.png)

如果 $X_i\gt R$。

这个时候要把 $R$ 从右边拿出来放到左边。最小值应该是原来的 $R$ 加上新线段。

我们需要维护全局偏移量。用优先队列维护上述两个端点的真实值就好了。

注意开头时要给优先队列加入足够的 $0$ ，防止取到不合法的值。

## 参考实现


```
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,tag=0;
signed main(){
    priority_queue<int>q1;
    priority_queue<int,vector<int>,greater<int>>q2;
    cin>>n;
    int lst=0,tagl=0,tagr=0,ans=0;
    for(int i=1;i<=n;i++)q1.push(0),q2.push(0);
    for(int i=1;i<=n;i++){
        int t,d,x;cin>>t>>d>>x;
        int len=t-lst;
        tagl-=len;
        tagr+=len;
        lst=t;
        if(!d){
            if(x<=q2.top()+tagr){
                q1.push(x-tagl);
            }else{
                ans+=abs(x-(q2.top()+tagr));
                q1.push(q2.top()+tagr-tagl);
                q2.pop();
                q2.push(x-tagr);
            }
        }else{
            if(x>=q1.top()+tagl){
                q2.push(x-tagr);
            }else{
                ans+=abs(x-(q1.top()+tagl));
                q2.push(q1.top()+tagl-tagr);
                q1.pop();
                q1.push(x-tagl);
            }
        }
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：phigy (赞：2)

本题解主要注重讲解**解题思路**而非**解题本身**。

--------

$dp_{i,j}=\begin{cases}\min_{j-T_i+T_{i-1}\leq k\leq j+T_i-T_{i-1}}\{dp_{i-1,k}\}\text{ if }j\ge X_i,D_i=0 \\ \min_{j-T_i+T_{i-1}\leq k\leq j+T_i-T_{i-1}}\{dp_{i-1,k}+X_i-j\}\text{ if }j< X_i,D_i=0 \\ \min_{j-T_i+T_{i-1}\leq k\leq j+T_i-T_{i-1}}\{dp_{i-1,k}\}\text{ if }j\leq X_i,D_i=1 \\ \min_{j-T_i+T_{i-1}\leq k\leq j+T_i-T_{i-1}}\{dp_{i-1,k}+j-X_i\}\text{ if }j> X_i,D_i=1 \end{cases}$

暴力的 DP 是 $O(Vn^2)$ 的，使用数据结构可以优化至 $O(Vn\log n )$，这非常不优秀。

但是我们可以花费很短的时间写出一个值域为 $[0,20]$ 输出 DP 数组中每个数值的[代码](https://www.luogu.com.cn/paste/s5t0ydy9)，我们可以使用它测试并验证猜想。

如此一来我们就非常容易能观察到对于每位 $i$ ，$DP_{i,j}$ 数列都由前后分别一段不上升子段和不下降子段组成，即线性分段下凸函数，更具体的是分为**多段等差数列且它们公差的公差为一**。 

我们可以证明这个结论，但证明总不是解出题目的关键，由于下凸与决策单调性相关，此时可以将输出 DP 数组中每个数值改为输出决策点的[代码](https://www.luogu.com.cn/paste/vpljarww)。

这时我们不仅发现 DP 转移具有**决策单调性**，还发现决策点总由**一段相同位置和一段连续位置**构成，这就说明转移过程只是对不上升子段或不下降子段的平移以及转移的连续数列的叠加。

那么我们就可以用大根堆和小根堆维护公差的变化，用全局记录平移，用插入变化点完成叠加。

证明和实现楼上都讲得很清楚了。

```cpp
#include <iostream>
#include <cstring>
#include <cmath>
#include <iomanip>
#include <vector>
#include <queue>
 
#define int long long

using namespace std;

int n;
priority_queue<int>q1;
priority_queue<int,vector<int>,greater<int> >q2;
int ans;

signed main()
{
	int i,j,k;
	cin>>n;
	int last=0,len=0,move=0; 
	for(i=1;i<=n;i++)
    {
        q1.push(0);
        q2.push(0);
    }
	for(i=1;i<=n;i++)
	{
		int t,d,x;
		cin>>t>>d>>x;
		len=t-last;
		move+=len;
		if(d==0)
        {
            if(x>q2.top()+move)
            {
                ans+=x-move-q2.top();
                q1.push(q2.top()+2*move);
                q2.pop();
                q2.push(x-move);
            }
            else
            {
            	q1.push(x+move);	
			}
        }
        else
        {
            if(x<q1.top()-move)
            {
                ans+=q1.top()-move-x;
                q2.push(q1.top()-2*move);
                q1.pop();
                q1.push(x+move);
            }
            else
            {
            	q2.push(x-move);	
			}
        }
		last=t;		
	}		
	cout<<ans;
	return 0;
} 
```




---

## 作者：OtterZ (赞：1)

对于这道题，设 $dp_{i,j}$ 为在 $t_i$ 时刻在位置 $j$ 时后续的最小伤害，可知道：

1. 对于移动，有 $dp_{i,j} = \min_{k = j - t_{i + 1} + t_i}^{j + t_{i + 1} - t_i}dp_{i + 1,k}$；
2. 对于事件，按定义处理。

我们将第二维作为函数处理，可以知道：

1. 对于操作 $2$，操作使得一边斜率加 $1$，另一边斜率不变，对应点变为拐点。
2. 对于操作 $1$，函数以斜率为 $0$ 处为中心向两边扩张。

我们基于这个特点，用平衡树维护拐点横坐标，再求 $\min\{0,\text{最左侧拐点}\}$ 处纵坐标即可。


```cpp
#include<cstdio>
#include<algorithm>
#include<random>
#include<chrono>
using namespace std;
mt19937 rp(chrono :: steady_clock :: now().time_since_epoch().count());
struct treap{
	int val,tag,sz,lc,rc;
	double rk;
	treap(){
		sz = 1;
		tag = val = 0;
		lc = rc = 0;
		rk = 1.0 * rp() / 7 + rp(); 
	}
}t[200009];
int lk;
long long lb,nt;
void change(int x,int val){
	t[x].val += val;
	t[x].tag += val;
}
void push_down(int x){
	if(t[x].lc != 0)
		change(t[x].lc,t[x].tag);
	if(t[x].rc != 0)
		change(t[x].rc,t[x].tag);
	t[x].tag = 0;
}
void push_up(int x){
	t[x].sz = t[t[x].lc].sz + t[t[x].rc].sz + 1;
}
void val_split(int x,int v,int &L,int &R){
	if(x == 0){
		L = 0,R = 0;
		return;
	}
	push_down(x);
	if(t[x].val <= v){
		val_split(t[x].rc,v,L,R);
		t[x].rc = L;
		L = x;
		push_up(x);
	}
	else{
		val_split(t[x].lc,v,L,R);
		t[x].lc = R;
		R = x;
		push_up(x);
	}
}
void k_split(int x,int k,int &L,int &R){
	//printf(" %d %d\n",x,k);
	if(x == 0){
		L = 0,R = 0;
		return;
	}
	push_down(x);
	//printf("%d %d %d\n",t[x].val,t[t[x].lc].sz,k);
	if(t[t[x].lc].sz < k){
		k_split(t[x].rc,k - t[t[x].lc].sz - 1,L,R);
		t[x].rc = L;
		L = x;
		push_up(x);
	}
	else{
		k_split(t[x].lc,k,L,R);
		t[x].lc = R;
		R = x;
		push_up(x);
	}
}
int mrg(int x,int y){
	if(x == 0 || y == 0)
		return x + y;
	push_down(x),push_down(y);
	if(t[x].rk > t[y].rk){
		t[x].rc = mrg(t[x].rc,y);
		push_up(x);
		return x;
	}
	else{
		t[y].lc = mrg(x,t[y].lc);
		push_up(y);
		return y;
	}
}
int gt_min(int x){
	push_down(x);
	if(t[x].lc > 0)
		return gt_min(t[x].lc);
	else
		return x;
}
void play(int x){
	if(x == 0)
		return;
	push_down(x);
	play(t[x].lc);
	//printf("%d\n",t[x].val);
	lb += 1ll * lk * (t[x].val - nt);
	lk ++;
	nt = t[x].val;
	play(t[x].rc);
}
void show(int x){
	if(x == 0)
		return;
	push_down(x);
	show(t[x].lc);
	printf("%d\n",t[x].val);
	show(t[x].rc);
}
int n,ft[200009],d[200009],x[200009];
int main(){
	t[0].sz = 0;
	scanf("%d",&n);
	for(int i = 1; i <= n; i ++){
		scanf("%d %d %d",&ft[i],&d[i],&x[i]);
	}
	int rt = 0;
	for(int i = n; i >= 1; i --){
		int a,b;
		val_split(rt,x[i],a,b);
		if(a == 0){
			lb -= lk * (nt - x[i]);
			nt = x[i];
		}
		lb = lb + 1ll * (x[i] - nt) * (1 - d[i]);
		lk = lk - 1 + d[i];
	//	printf(" %d\n",lk);
		t[i].val = x[i];
		rt = mrg(mrg(a,i),b);
	//	printf("%d\n",rt);
	//	show(rt);
	//	puts("");
	//	printf("%d\n",lk);
		k_split(rt,-lk,a,b);
	//	printf("%d %d\n",a,b);
		change(a,ft[i - 1] - ft[i]);
		change(b,ft[i] - ft[i - 1]);
		rt = mrg(a,b);
		nt -= ft[i] - ft[i - 1];
	//	printf("%d\n",rt);
	//	show(rt);
	//	puts("");
	}
	int a,b;
	val_split(rt,0,a,b);
	if(a == 0){
		lb = lb - 1ll * nt * lk;
	}
	else{
		play(a);
		lb = lb - 1ll * nt * lk; 
	}
	printf("%lld\n",lb);
}
```

---

## 作者：Yansuan_HCl (赞：1)



暴力 DP：$g$ 是上一个时刻的状态，$f$ 是这个时刻的状态，则 $f(x)=\min\{g(x-1),g(x),g(x+1)\}$。一次攻击对应在 $f$ 上加半段一次函数，于是可以 Slope Trick.。

上面一个取 $\min$ 对应对凸包平移。每个时刻，左凸包可以取到其右边的值，右凸包可以取到其左边的值，谷可以保留谷。于是左凸包向左平移 $1$，右凸包向右平移 $1$。加射线是经典的 Slope Trick 操作。最后构造操作序列，求出答案。

但是每个时刻 $f$ 的定义域是 $[-t, t]$。不加限制的 Slope Trick 行不通。**这时我们平移 $x_i$ 使 $x_i$ 在 $[-t, t]$ 内。**由于只需要求出操作序列，我们只关心谷的位置而不关心其凸包上值的大小。分类讨论 $d$ 的 $0/1$ 与 $x_i$ 在 $-t$ 左侧或 $t$ 右侧，可以发现这样不会影响谷的位置（要么不变，要么定义域内加常数）。

```cpp
ll lim = max(min(x[i], t[i]), -t[i]);
q1.push(lim - d1);
```

记录每个时刻的谷底作为最佳答案，倒着推断答案以避免后效性。*谷底可能不存在，此时凸包单调。可以取值域的极值点。*最后一个决策的最佳答案能取到（凸包中的点都合法），之前的决策要根据与上一个决策的距离与时间进行限制。若超出限制则取到离它最近的限制点，这是由凸包的单调性决定的。

```cpp
#include <bits/stdc++.h>
#define ms(x, v) memset(x, v, sizeof(x))
#define il __attribute__((always_inline)) static
#define U(i,l,r) for(int i(l),END##i(r);i<=END##i;++i)
#define D(i,r,l) for(int i(r),END##i(l);i>=END##i;--i)
using namespace std;

typedef unsigned long long ull;
typedef long long ll;
template <class T> using BS = basic_string<T>;

template <class T> void rd(T& s) {
	int c = getchar(); T f = 1; s = 0;
	while (!isdigit(c)) { if (c == '-') f = -1; c = getchar(); }
	while (isdigit(c)) { s = s * 10 + (c ^ 48); c = getchar(); }
	s *= f;
}
template <class T, class... Y> void rd(T& x, Y&... y) { rd(x), rd(y...); }
#define meow(...) fprintf(stderr, __VA_ARGS__)
#define Assert(e, v) if (!(e)) exit(v);

const int N = 200005;
int n; ll dcs[N];
ll d1, d2, k;
priority_queue<ll> q1; priority_queue<ll, vector<ll>, greater<ll>> q2;
ll t[N], d[N], x[N];
bool valid[N];

int main() {
	rd(n);
	
	ll tl = 0;
	U (i, 1, n) {
		rd(t[i], d[i], x[i]);
		if (i != 1) {
			d1 -= t[i] - t[i - 1];
			d2 += t[i] - t[i - 1];
		}
		if (!d[i])
			--k;
		while (q2.size() && q1.size() < -k) { // 调整左凸包大小为 -k 
			ll t = q2.top() + d2;
			q2.pop();
			q1.push(t - d1);
		}
		ll lim = max(min(x[i], t[i]), -t[i]);
		q1.push(lim - d1);
		while (q1.size() > -k) {
			ll t = q1.top() + d1;
			q1.pop();
			q2.push(t - d2);
		}
		if (q1.empty())
			dcs[i] = -t[i]; // 这时候凸包单调不减 
		else 
			dcs[i] = q1.top() + d1;
		// 与以下写法等价 
//		if (q2.empty())
//			dcs[i] = t[i]; // 这时候凸包单调不增 
//		else 
//			dcs[i] = q2.top() + d2;
	}
//	U (i, 1, n) clog << dcs[i] << ' '; clog << endl;
	ll res[N] {}; res[n] = dcs[n];
	D (i, n - 1, 1) {
		ll dt = t[i + 1] - t[i];
		if (res[i + 1] >= dcs[i])
			res[i] = max(dcs[i], res[i + 1] - dt);
		else
			res[i] = min(dcs[i], res[i + 1] + dt);
	}
	
	ll ans = 0;
	U (i, 1, n)
		if (d[i])
			ans += max(0ll, res[i] - x[i]);
		else
			ans += max(0ll, x[i] - res[i]);
	cout << ans << endl;
}
```

---

## 作者：无名之雾 (赞：1)

slope trick 经典题。

## solution

题面演都不演就差直接把这题要用 slope trick 告诉你了。

考虑定义状态 $dp_{i,j}$ 表示 $t_i$ 时刻位于 $j$ 的最小代价。

不难得到一个简单的转移方程：

$$\min_{|x-j|\le t_i-t_{i-1}}\{dp_{i-1,k}\}+\Delta val_{x_i,j}$$

有绝对值，所以大抵是一个凸函数。

两种的操作无论是平移后取最小值亦或是再加上一个凸函数后，它仍然会是一个凸函数。所以显然维护左右凸包即可。

凸壳平移显然是可以打标记维护的，考虑 $\Delta val$ 这个增量。

发现这个增量其实也是一个连续分段下凸函数，只需要简单分讨就可以解决。

考虑 $d=0$ 的情况，我们添加的函数为 $f(x)=\max(0,x_i-x)$。

- 若 $x_i$ 在左凸壳或斜率为 $0$ 的段，直接在左凸壳插入分段点 $x_i$。
- 若 $x_i$ 在右凸壳范围内，那么新的斜率为 $0$ 的段是右凸壳最靠左的一段，原本右凸壳最靠左的分段点会变为新的左凸壳最靠右的分段点。
  
$d=1$ 同理。

上述操作开两个堆维护即可。

时间复杂度 $O(n\log n)$。

---

## 作者：冷却心 (赞：0)

前言：大家好，我喜欢用 `multiset` 维护可重集，并且删除一个元素 $x$ 的时候使用了 `multiset.erase(x)` 而不是 `multiset.erase(multiset.find(x))`，成功导致我保龄并调试 $40\ \text{mins}$，祝大家不要重蹈覆辙。

先考虑朴素 dp，定义 $f_{i,j}$ 表示第 $i$ 个事件发生的时候在 $j$ 位置，最少的伤害总和。记 $t=T_i-T_{i-1}$，$C_i(j)$ 表示第 $i$ 次事件站在 $j$ 所受伤害，有

$$f_{i,j}=\min_{j-t\leq k\leq j + t}f_{i-1,k}+C_i(j).$$

这个 dp 是 $O(nV)$ 的，直接倒闭了。然后你能发现这个转移的增量是一个关于 $j$ 的凸函数，所以考虑 Slope Trick。先介绍一下 Slope Trick。

Slope Trick 可以维护一个由若干段一次函数组成的一个凸分段函数。我们考虑记录这若干段一次函数的分界点的集合，并且分界点出现一次表示斜率增加或减少 $1$，如果出现多次则说明减少若干斜率，以及记录这个凸函数最开始那一段的 $k,b$，比如：

$$f(x)=\left\{\begin{aligned}&1-x,\quad&x\leq 5,\\&2x+8,&x>5.\end{aligned}\right.$$

这个函数在 Slope Trick 下维护出的集合就是 $\{5,5,5\}$，以及最开始一段的函数的 $k=-1,b=1$。所以这是一个可重集。

然后你会发现这个东西比较优美，可以有如下的操作：

1. 加上一个凸函数：因为凸函数加凸函数还是凸函数，所以直接把分界点集合合并即可，然后更新一下最开始一段的斜率和截距。
2. 平移：对分段点集合打全局加减标记即可。
3. 函数的最值：这里就不大相同，我们不维护最左边的斜率和截距。以凸函数为例，函数最大值就是斜率为 $0$ 的部分，所以我们考虑维护两个集合分别表示斜率为 $0$ 的左边和右边的分界点即可。最值就是中介斜率为 $0$ 的部分。
4. 函数取前后缀 $\min/\max$：联系上一点，就是把斜率为 $0$ 的左边或者右边丢掉。

回到本题，我们设 $F_i(j)=f_{i,j}$，我们发现这个就是一个凸函数（函数凹凸的图像和汉字形状是相反的 /xk）。本题我们需要支持加上一个凸函数，并且维护最小值，然后考虑转移式前面的那个 $\min$，这个就相当于把斜率为 $0$ 左边的部分向左移 $t$，右边的部分向右移 $t$。对于 $C_i(j)$，它在 $D_i=0$ 的时候是斜率由 $-1$ 变为 $0$，否则是 $0$ 变为 $1$。考虑加入这个凸函数的时候怎么更新斜率为 $0$ 的部分并且更新答案。


以 $D_i=0$ 为例，这时候函数大致呈 `\_` 状。我们记当前斜率为 $0$ 的一段区间为 $[l,r]$，如果这个函数的拐点 $X$ 大于等于 $l$，我们发现只需要 $X$ 加入右集合即可。否则要更新这个区间和答案。先吧 $X$ 加入左集合，我们会发现，原来斜率为 $0$ 的这个区间斜率变成了 $-1$，所以把 $r$ 加入右集合表示斜率减少 $1$，然后更新答案。

$D_i=1$ 同理。


```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int N = 2e5 + 10;
int n; LL T[N], D[N], X[N], Ans = 0;

struct Heap {
	multiset<LL> s; LL tag;
	void insert(LL x) { s.insert(x - tag); }
	void erase(LL x) { s.erase(s.find(x - tag)); }
	LL min() { return *s.begin() + tag; }
	LL max() { return *s.rbegin() + tag; }
	void add(LL x) { tag += x; }
} pql, pqr;

int main() {
	freopen(".in", "r", stdin); freopen(".out", "w", stdout);
	ios :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n; for (int i = 1; i <= n; i ++) pql.insert(0), pqr.insert(0);
	for (int i = 1; i <= n; i ++) {
		cin >> T[i] >> D[i] >> X[i]; LL len = T[i] - T[i - 1];
		pql.add(-len); pqr.add(len);
		if (D[i]) { // _/
			if (X[i] >= pql.max()) { pqr.insert(X[i]); continue; }
			pql.insert(X[i]); LL r = pql.max(); pql.erase(r); pqr.insert(r);
			Ans += pqr.min() - X[i];
		} else { // \_
			if (X[i] <= pqr.min()) { pql.insert(X[i]); continue; }
			pqr.insert(X[i]); LL l = pqr.min(); pqr.erase(l); pql.insert(l);
			Ans += X[i] - pql.max();
		}
	} cout << Ans;
	return 0;
}
```

---

## 作者：ty_mxzhn (赞：0)

slope trick 板子题。

看题，发现操作演都不带演的告诉你是维护折线段了。

走路操作看一眼不是很好搞，第二眼发现不就是递减的部分往右移动一步，递增的部分往左移动一步吗。

考虑直接拿一个对顶堆维护递减递增两个部分的斜率变化位置，走路操作就打个标记，攻击操作就插入折点。

实现代码时稍微谨慎一点，于是我们在 $O(n\log n)$ 的时间内做完了这个题。

---

