# 『JROI-2』Dancing Line

## 题目背景

> 若唤音乐随直线走动，那么你的双眸就是无穷。

k 舔喜欢玩 Dancing Line。

k 舔决定自己做一个 Dancing Line 关卡。

## 题目描述

注：本题不考虑「迷宫」等线转向方式特殊，「足球」等传送线，「钢琴」等飞跃落地的情况。

众所周知，Dancing Line 的路线是一条折线，每次点击会使线的前进方向**顺时针或逆时针旋转 $90^\circ$**，且**任意相邻两次旋转方向不同**。

比如下面是合法的路径（路径**不一定要随着平面直角坐标系的网格行走**）：

![](https://cdn.luogu.com.cn/upload/image_hosting/zuh1rvxz.png)  

![](https://cdn.luogu.com.cn/upload/image_hosting/5gct7zuf.png)

而下面是不合法的路径：

旋转角度不为 $90^\circ$：

![](https://cdn.luogu.com.cn/upload/image_hosting/kg8d4571.png)  

连续两次向左转弯：

![](https://cdn.luogu.com.cn/upload/image_hosting/6hfn6cxe.png)  

显然不符合要求的路径：

![](https://cdn.luogu.com.cn/upload/image_hosting/lm76sj88.png)

k 舔将路线放进了二维坐标系内，并记下了路线的**起点**、**终点**和**拐弯点**的坐标（横纵坐标**均为整数**），放进文件里就离开了。

等到 k 舔回来打开电脑时，发现他文件里的数据全部乱掉了，各点的坐标不再像之前那样按顺序存储好，而是按一种奇怪的顺序排列好了。

k 舔想要根据这些数据来重新复原这条路线，他还想要估计这个关卡的难度，用 $s$ 来表示：

$$s=\sum\limits_{i=1}^{n}{t_i^2},t_i=\dfrac{d(P_{i-1},P_i)}{v}$$

其中：

- $P_i(0\leq i\leq n)$ 表示路线**复原后**从起点开始的第 $i$ 个点（起点为 $P_0$，终点为 $P_n$）。
- $v$ 为线的速度，是一个给定的**正整数**。
- $d(A,B)$ 表示点 $A$ 和点 $B$ 在坐标轴内的距离。

你能帮助他吗？

## 说明/提示

**样例解释**

对于样例一，路线如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/1a4dp2si.png)

各段长度分别为 $2\sqrt{5},2\sqrt{5},\sqrt{5},3\sqrt{5},2\sqrt{5},\sqrt{5},4\sqrt{5},2\sqrt{5}$，$s$ 值为 $53\dfrac{3}{4}$，取模后结果为 $249561142$。

------------

**数据范围与约定**

本题采用**捆绑测试**。

- Subtask 1（5 pts）：$n\leq 6$。
- Subtask 2（15 pts）：$n\leq 80$。
- Subtask 3（30 pts）：$n\leq 800$。
- Subtask 4（50 pts）：无特殊限制。

对于 $100\%$ 的数据，满足：

- $2\leq n \leq 10^6$。
- $-10^9\leq x_i,y_i\leq 10^9$。
- $1\leq v\leq 10^7$。
- **保证所有点坐标各不相同**。
- **保证给出的点一定能且只能复原出唯一的路径。**

------------

$d(A,B)=\sqrt{(x_A-x_B)^2+(y_A-y_B)^2}$，其中 $A(x_A,y_A),B(x_B,y_B)$。

-----
Source：[JROI-2 Summer Fun Round](https://www.luogu.com.cn/contest/30241) - T3

Idea&Sol&Data：[kkk的小舔狗](/user/104581)

Std&Retest：[Tony2](/user/171288)




## 样例 #1

### 输入

```
8 2
-7 7
-11 5
-3 4
-5 3
4 0
0 -2
5 -2
13 2
15 -2
```

### 输出

```
249561142
```

# 题解

## 作者：云浅知处 (赞：6)

注意到横纵坐标必然有一个单调不减，因此我们枚举是横坐标还是纵坐标不减，然后检查并计算即可。

由于线可能平行于坐标轴，因此我们在按照横纵坐标排序的时候还要枚举一下应当把另一个关键字按照递增还是递减的规则来排序。

感觉不是很好说清楚 qwq，具体看代码

```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdlib>

#define int long long
const int MN=1e6+6;
const int mod=998244353;

using namespace std;

inline int read(){
    int x=0,f=1;char c=getchar();
    for(;(c<'0'||c>'9');c=getchar()){if(c=='-')f=-1;}
    for(;(c>='0'&&c<='9');c=getchar())x=x*10+(c&15);
    return x*f;
}
 
int ksm(int y,int z,int p){
    y%=p;int ans=1;
    for(int i=z;i;i>>=1,y=y*y%p)if(i&1)ans=ans*y%p;
    return ans%p;
}
 
int inv(int x,int p){return ksm(x,p-2,p)%p;}

struct Node{int x,y;}pnt[MN];

int n,v;

bool cmp1(Node p,Node q){return (p.x==q.x)?(p.y<q.y):(p.x<q.x);}
bool cmp2(Node p,Node q){return (p.x==q.x)?(p.y>q.y):(p.x<q.x);}
bool cmp3(Node p,Node q){return (p.y==q.y)?(p.x<q.x):(p.y<q.y);}
bool cmp4(Node p,Node q){return (p.y==q.y)?(p.x>q.x):(p.y<q.y);}

bool f(int x,int y,int xx,int yy,int xxx,int yyy){return ((xx-x)*(xx-xxx)+(yy-y)*(yy-yyy)==0);}//判断垂直

bool chk(){
    for(int i=2;i<n;i++)if(!f(pnt[i-1].x,pnt[i-1].y,pnt[i].x,pnt[i].y,pnt[i+1].x,pnt[i+1].y))return 0;
    return 1;
}//判断是否符合条件

int dis(int x,int y,int xx,int yy){
    return ((x-xx)*(x-xx)%mod+(y-yy)*(y-yy)%mod)%mod;
}//计算两点距离的平方

int calc(){
    int res=0;
    for(int i=1;i<n;i++)res=(res+dis(pnt[i].x,pnt[i].y,pnt[i+1].x,pnt[i+1].y))%mod;
    return res%mod*inv(v,mod)%mod*inv(v,mod)%mod;
}//计算答案
 
signed main(void){

    cin>>n>>v;
    n++;
    for(int i=1;i<=n;i++)pnt[i].x=read(),pnt[i].y=read();
    sort(pnt+1,pnt+n+1,cmp1);
    if(chk()){cout<<calc()<<endl;return 0;}
    sort(pnt+1,pnt+n+1,cmp2);
    if(chk()){cout<<calc()<<endl;return 0;}
    sort(pnt+1,pnt+n+1,cmp3);
    if(chk()){cout<<calc()<<endl;return 0;}
    sort(pnt+1,pnt+n+1,cmp4);
    if(chk()){cout<<calc()<<endl;return 0;}
 
    return 0;
}
```

---

## 作者：littleKtian (赞：4)

upd on 2021.8.2：更新了更更更简单的做法，所以重新写了一遍题解。

[原题解链接](https://www.luogu.com.cn/paste/i0s5fg13)。

------------

可以发现整条路径上的所有点按顺序必然是以 $x$ 坐标或 $y$ 坐标单调的，所以我们直接排序，将相邻的两点连起来判断即可（注意特判连边和坐标轴平行的情况）。

复杂度 $O(n\log n)$。

---

## 作者：Terraria (赞：3)

~~考场上写挂了，特地来发一篇题解警醒自己。~~

## 题目大意

根据已有的点还原路线，并求其关卡难度。详见题面。

## 分析

由于题目的特殊限制，我们不难发现一个奇妙的性质：对于一条合法的路线，一定有 $x$ 或 $y$ 坐标严格不降。我们就从这个性质入手。

接下来我会按照考场上的思路逐步讲解，大佬可以直接跳过。

首先我没有想很多，只写了两个 `cmp` 函数，分别给 $x$ 和 $y$ 排序。排完序后，我采用了解析式法，得到第 $i-2$ 与 $i-1$ 个点所在直线、第 $i-1$ 与第 $i$ 个点所在直线的 $k_1,k_2$ 值。~~根据初中数学知识可得~~ 若 $k_1 \times k_2=-1$，则这两条直线垂直。

根据这个思路，我就写出了这个代码（限于篇幅放在剪切板里）：[代码 $1$](https://www.luogu.com.cn/paste/2a4t5vyu)。

显然，这个代码只能得到 $5$ 分。原因一会儿分析会提到。

后来我根据这个代码构造出了 Hack 数据：

```cpp
2 1
1 0
0 0
0 1
```
我发现我的代码跑出来的是 $3$，而实际上应该为 $2$。那么，是为什么呢？

因为——`cmp` 函数并不能保证排序出来的点在满足 $x$ 或 $y$ 坐标相等时，对应的另一个坐标与上一个坐标相等！（自行理解吧）并且我只 `check` 了 $x$ 坐标是否合法，而没有检查 $y$ 坐标。因此可能 $x$ 坐标和 $y$ 坐标都不合法。而我却按照 $y$ 坐标算了。

例如，上面所举的 Hack 数据，可能按照 $x$ 坐标排完序发现不合法，直接按照 $y$ 坐标排序，排完序就变成了：

```
0 1
1 0
0 0
```
那么按照这样子算，我的代码确实可以算出 $3$。

那么解决办法就是——

排四次序！检四次查！

对于这部分代码，我也放在了剪切版里：[代码 $2$](https://www.luogu.com.cn/paste/3xfhmf6j)。然而这份代码却也只有 $5$ 分。

~~然后好不容易想到要排四次序就**比赛结束**了。~~

赛后，我去请教了 [Okimoto](https://www.luogu.com.cn/user/303132) 大佬。他看了一眼我的代码立马就发现了问题——

首先看到 `fm`，它的值是 $v^2$，这点没问题吧。

然后！看到 `Pow` 函数：

```
int Pow(int a,int b){
    int ans=1;
    for(;b;b>>=1,a=a*a%mod){
    	if(b&1) ans=ans*a%mod;
    }
    return ans;
}
```
已知 `fm` 传进去后就是 `a`，也就是 `a` 的值就是 $v^2$。再仔细看看？


`a=a*a%mod`

这意味着什么？

`a` 首先变成了 $v^4$ 才取模！而 $1 \leq v \leq 10^7$！$10^{28}$ 不爆 `long long` 才怪！

一个较好的解决办法就是在 `fm` 传进去前就取好模。这部分代码就不放了。因为就只加了一句：`fz%=mod,fm%=mod;`。

有了这一句话，分数：$5 \to 85$！？

我直接狂喜，这分差也太大了吧！（当然主要是因为我太菜了不配拥有高分）。

那么现在取模问题解决了，`cmp` 问题也解决了，问题出在哪呢？

**会不会 `check` 卡我精度啊？会不会 `check` 函数就写错了啊？**

赛后调了精度，没过，于是我又请教了 [Okimoto](https://www.luogu.com.cn/user/303132) 大佬。他说：判断直角除了 $k$ 值相乘为 $-1$，还可以用勾股啊！

对啊！勾股！我怎么没想到！这多简单啊！直接把第 $i-2$、$i-1$ 个点所连线段长度记为 $a$，把第 $i-1$、$i$ 个点所连线段长度记为 $b$，把第 $i-2$、$i$ 个点所连线段长度记为 $c$，只要 $a^2+b^2=c^2$ 就好了啊！

于是我就 AC 了。

参考代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 998244353
using namespace std;
struct point{
	int x,y;
}a[1000009];
int n,v;
bool f=true;
int kk;
bool cmp1(point p1,point p2){
	if(p1.x==p2.x) return p1.y>p2.y;
	return p1.x>p2.x;
}
bool cmp2(point p1,point p2){
	if(p1.x==p2.x) return p1.y<p2.y;
	return p1.x>p2.x;
}
bool cmp3(point p1,point p2){
	if(p1.y==p2.y) return p1.x>p2.x;
	return p1.y>p2.y;
}
bool cmp4(point p1,point p2){
	if(p1.y==p2.y) return p1.x<p2.x;
	return p1.y>p2.y;
}
int fz=0;
int fm=0;
int dis(int x1,int x2,int y1,int y2){
	return ((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
void check(int num){
	f=true;
	double last=0;
	for(int i=2;i<=n;i++){
		int s1=dis(a[i-2].x,a[i-1].x,a[i-2].y,a[i-1].y);
		int s2=dis(a[i-1].x,a[i].x,a[i-1].y,a[i].y);
		int s3=dis(a[i-2].x,a[i].x,a[i-2].y,a[i].y);
		if(s1+s2!=s3){
			f=false;
			break;
		}
	}
	if(f) kk=num;
}
int gcd(int x,int y){
	if(y==0) return x;
	return gcd(y,x%y);
}
int Pow(int a,int b){
    int ans=1;
    for(;b;b>>=1,a=a*a%mod){
    	if(b&1) ans=ans*a%mod;
	}
    return ans;
}
signed main(){
	cin>>n>>v;
	for(int i=0;i<=n;i++) cin>>a[i].x>>a[i].y;
	sort(a,a+n+1,cmp1);check(1);
	sort(a,a+n+1,cmp2);check(2);
	sort(a,a+n+1,cmp3);check(3);
	sort(a,a+n+1,cmp4);check(4);
	if(kk==1) sort(a,a+n+1,cmp1);
	if(kk==2) sort(a,a+n+1,cmp2);
	if(kk==3) sort(a,a+n+1,cmp3);
	if(kk==4) sort(a,a+n+1,cmp4);
	
	for(int i=1;i<=n;i++){
		fz=(fz+dis(a[i].x,a[i-1].x,a[i].y,a[i-1].y))%mod;
		
	}
	fm=v*v;
	int _gcd=gcd(fz,fm);
	fz/=_gcd,fm/=_gcd;
	fz%=mod,fm%=mod;
	cout<<(fz*Pow(fm,mod-2))%mod;
}
```


---

## 作者：dts_std (赞：3)

## 更新日志

upd on 2022.6.30：更改小细节，丰富后记内容。

upd on 2022.6.30：再次更改小细节，更改 $\LaTeX$ 公式。

## 题目大意

[题目传送门](https://www.luogu.com.cn/problem/P7778)

给定平面上的 $n$ 个点 $P_{1},P_{2},\dots,P_{n}$ 和一个整数 $v$ ，连接点形成 $n-1$ 条线段。题目保证有且仅有一条符合题意（连续，过所有点，遇点转直角弯，任意相邻两次旋转方向不同）的路径，并让点按路径顺序排序，形成点组 $A_{1},A_{2},\dots,A_{n}$ 。

定义 $d(A,B)$ 为点 $A$ ，$B$ 的距离，已知 $s$ 满足：

$$t_i=\dfrac{d(A_{i-1},A_i)}{v},s=\sum \limits_{i=2}^{n}{t_i^2}$$

求 $s$ 的值。

## 思路

上面好多楼主说:


> 可以发现整条路径上的所有点按顺序必然是以 $x$ 坐标或 $y$ 坐标单调的。

其实，这就是思路。

但是，“可以发现”未免让在下这样的强迫症晚期摸不着头脑。

若你想看证明，请往下看；若不想看，请跳到 “解法” 部分。

## 证明

好的，我默认你已经学会了平面直角坐标系和平面向量的知识。

为了表述方便，我们把线段赋予方向，变成向量（真正的 _dancing line_ 其实也是有方向的）。

无特殊说明时，下文中的“点”指排序后的点。

------------

**当向量与坐标轴平行（或在坐标轴上）时**

此时对于的相邻两点，都有 $x$ 或 $y$ 坐标相等。

令第一个向量向 $x$ 轴正方向，则：

若此时左转，则第二个向量向 $y$ 轴正方向。

则第三段朝 $x$ 轴正方向，以此类推，成为如图所示的路径。

![](https://cdn.luogu.com.cn/upload/image_hosting/kh1wh6b9.png)

当相邻点的 $x$ 坐标不同时， $x$ 坐标的值必是增加，此时 $y$ 坐标不变。

当相邻点的 $y$ 坐标不同时， $y$ 坐标的值必是增加，此时 $x$ 坐标不变。

所以当第一个向量向 $x$ 轴正方向时，每个点的 $x$ 坐标和 $y$ 坐标同时单调递增。时，每个点的 $x$ 坐标和 $y$ 坐标同时单调递增。

------------

若此时右转，则第二个向量向 $y$ 轴负方向。

则第三段朝 $x$ 轴正方向，以此类推。

当相邻点的 $x$ 坐标不同时， $x$ 坐标的值必是增加，此时 $y$ 坐标不变。

当相邻点的 $y$ 坐标不同时， $y$ 坐标的值必是减少，此时 $x$ 坐标不变。

所以当第一个向量向 $x$ 轴正方向时，每个点的 $x$ 坐标递增， $y$ 坐标递减。

其他三种情况（第一个向量向 $x$ 轴负方向， $y$ 轴正方向， $y$ 轴负方向）同理。

则当路径与坐标轴平行（或在坐标轴上）时，排序后每个点的 $x$ 坐标和 $y$ 坐标同时具有单调性。

------------

**当向量与坐标轴不平行时**

则有两种线段，四种向量，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/8iji9r8o.png)

我就取以第一种向量开头的路径进行证明（剩下几种经过镜像等变换也会转化成相同情况）。

设初始向量 $\overrightarrow{a}=(x,y)$，则有

$\overrightarrow{e}=(y,-x),\overrightarrow{f}=(-y,x)$ 满足 $\overrightarrow{e} \bot \overrightarrow{a}$ 且 $\overrightarrow{f} \bot \overrightarrow{a}$ 。

简单证明一下：

$$\because \overrightarrow{e} \cdot \overrightarrow{a} = xy - xy = 0 , \overrightarrow{f} \cdot \overrightarrow{a} = - xy + xy = 0$$

$$\therefore \overrightarrow{e} \bot \overrightarrow{a} , \overrightarrow{f} \bot \overrightarrow{a}$$

令 $x>0 , y>0$ ，接下来继续分类讨论：

设转弯后的路径为向量 $\overrightarrow{b} = (x_{b},y_{b})$ 。

------------

若此时右转，则有 $\overrightarrow{b} , \overrightarrow{e} $ 方向相同。

因为 $\overrightarrow{e} = (y , -x) $，而 $ y > 0 , (-x) < 0$

所以 $ x_{b} > 0 , y_{b} < 0 $。

如下图就是一个示例：

![](https://cdn.luogu.com.cn/upload/image_hosting/pj3k5qjr.png)

在这基础上只能左转（因为每次转弯方向都和前一次相反），左转后的向量和 $\overrightarrow{a}$ 方向相同。

以此类推，就成为了如图所示的路径：

![](https://cdn.luogu.com.cn/upload/image_hosting/i7fk0xtt.png)

看图就可以知道 $x$ 方向单调递增。

再简单证明一下：

因为表示路径的向量和 $\overrightarrow{a}$ 或 $\overrightarrow{e}$ 相同，而 $\overrightarrow{a}$ 和 $\overrightarrow{e}$ 都满足 $x$ 轴坐标大于 $0$ 。

所以路径上的所有向量都满足 $x$ 轴坐标大于 $0$ 。

设点组为 $A_{1}(x_{1},y_{1}),A_{2}(x_{2},y_{2}),\dots,A_{n}(x_{n},y_{n})$

则 $\overrightarrow{A_{1}A_{2}}=(x_{2}-x_{1},y_{2}-y_{1}),\overrightarrow{A_{2}A_{3}}=(x_{3}-x_{2},y_{3}-y_{2}),\dots,\overrightarrow{A_{n - 1}A_{n}}=(x_{n}-x_{n-1},y_{n}-y_{n-1})$。

由题意，所有向量都满足 $x$ 轴坐标大于 $0$ 。

所以 $x_{2}-x_{1} > 0,x_{3}-x_{2} > 0,\dots,x_{n}-x_{n-1} > 0$

所以此时所有点的排序后每个点的 $x$ 坐标递增。

------------

若此时左转，则$\overrightarrow{b} , \overrightarrow{f}$方向相同。

因为 $\overrightarrow{f} = (-y , x)$ ，而 $x > 0 , (-y) < 0$，

所以 $x_{b} > 0 , y_{b} < 0$。

如下图就是一个示例：

![](https://cdn.luogu.com.cn/upload/image_hosting/59vqiv2b.png)

在这基础上只能右转（因为每次转弯都和前一次相反），右转后的向量和 $\overrightarrow{a}$方向相同。

以此类推，就成为了如图所示的路径：

![](https://cdn.luogu.com.cn/upload/image_hosting/9ujse3j8.png)

看图就可以知道 $y$ 方向单调递增。

再简单证明一下：

因为表示路径的向量和 $\overrightarrow{a}$ 或 $\overrightarrow{f}$ 相同，而 $\overrightarrow{a}$ 和 $\overrightarrow{f}$ 都满足 $y$ 轴坐标大于 $0$ 。

所以路径上的所有向量都满足 $y$ 轴坐标大于 $0$ 。

设点组为 $A_{1}(x_{1},y_{1}),A_{2}(x_{2},y_{2}),\dots,A_{n}(x_{n},y_{n})$

则 $\overrightarrow{A_{1}A_{2}}=(x_{2}-x_{1},y_{2}-y_{1}),\overrightarrow{A_{2}A_{3}}=(x_{3}-x_{2},y_{3}-y_{2}),\dots,\overrightarrow{A_{n - 1}A_{n}}=(x_{n}-x_{n-1},y_{n}-y_{n-1})$。

由题意，所有向量都满足 $y$ 轴坐标大于 $0$ 。

所以 $y_{2}-y_{1} > 0,y_{3}-y_{2} > 0,\dots,y_{n}-y_{n-1} > 0$ .

所以此时每个点的 $y$ 坐标递增。

------------

上面证明了第一个向量在第一象限的情况，同理，在其他象限情况，也可以同理证明每个点的 $x$ 坐标或 $y$ 坐标具有单调性。

具体如下：

当第一个向量在第二象限时，每个点 $x$ 坐标递减或 $y$ 坐标递增。

当第一个向量在第三象限时，每个点 $x$ 坐标递减或 $y$ 坐标递减。

当第一个向量在第四象限时，每个点 $x$ 坐标递增或 $y$ 坐标递减。

所以，当向量与坐标轴不平行时，每个点的 $x$ 坐标或 $y$ 坐标具有单调性。

------------

综上所述，排序后每个点的 $x$ 坐标或 $y$ 坐标具有单调性，特别的，当路径与坐标轴平行（或在坐标轴上）时，排序后每个点的 $x$ 坐标和 $y$ 坐标同时具有单调性。

**证毕！**

## 解法

证明完之后，我们回到题目讨论正解。

令排序后的点组为 $A_{1}(x_{1},y_{1}),A_{2}(x_{2},y_{2}),\dots,A_{n}(x_{n},y_{n})$.

先把式子变形一下：

$$\because d(A_{i-1},A_i)=\sqrt{(x_{i-1}x_i)^2+(y_{i-1}-y_i)^2} , $$

$$t_i=\dfrac{d(A_{i-1},A_i)}{v}s=\sum\limits_{i=2}^{n}{t_i^2}$$

$$\therefore s=\frac{\sum_{i=2}^{n} [d(A_{i-1},A_i)]^2 }{v^2}=\frac{\sum_{i=2}^{n} [(x_{i-1}-x_i)^2+(y_{i-1}-y_i)^2] }{v^2}$$

所以只要求出排序后点对，就可以求出 $s$ 。

上面已经证明过了，排序后每个点的 $x$ 坐标或 $y$ 坐标具有单调性。

所以只有满足这个条件的路径才有可能是最终路径。

于是我们就可以——直接按 $x$ 或 $y$ 坐标为第一关键字排序并验证是否正确。

但是这个策略有一个问题：

当路径与坐标轴平行时，存在$x$ 或 $y$坐标相同的情况。
 
所以，当路径与坐标轴平行时，我们在按 $x$ 为第一关键字排序之后，需要对相同 $x$ 坐标的点进行处理，因为相同 $x$ 坐标的点的顺序还不能确定。

有两种处理方法：

1. 因为 $y$ 坐标也具有单调性，我们就可以以 $y$ 坐标为第二关键字排序。但是要排两遍序，一次  $y$ 坐标递增，一次递减，分别验证（这里留个思考题，为什么要照这样排两遍）。这是正规方法。

2. 因为题目只需求距离，而且没有无解情况，所以就有一个较为投机的方法：按 $x$ 为第一关键字排一遍序，遇到 $x$ 相等时计算距离即可，然后按 $y$ 为第一关键字排序，遇 $y$ 相等时计算距离。我使用了这种方法。

因为算法最多排 $4$ 遍序，忽略常数后可得时间复杂度为 $O(n \cdot log_{2} n)$.

小细节：取模！取模！不断地取模！重要的事情说三遍！

对于除以 $v^2$ 的情况，题目中已明确说明，具体如下：

$\because$ 当 $gcd(x,y)=1$ 时, 

$$ \frac {x}{y} \mod 998244353 = x \cdot y^{998244351} \mod 998244353$$

$$\therefore \frac {1} {v^2} \mod 998244353 = (\frac {1}{v})^2 \mod 998244353$$

$$ = (v^{998244351} \mod 998244353)^2 \mod 998244353 $$

所以还要加上快速幂计算该值。这里我默认你已经学会了快速幂，不会的话可以做做模板题（
[传送门](https://www.luogu.com.cn/problem/P1226)
）
## 代码

~~我知道你们只看这个~~

```cpp
#include<bits/stdc++.h>
using namespace std;
#define mod 998244353
class dot{
	public:
		long long x;
		long long y;
}a[1000010];
bool cmpx(dot a,dot b){//按x坐标为第一关键字排序
	if(a.x==b.x) return a.y<b.y;
	return a.x<b.x;
}
bool cmpy(dot a,dot b){//按y坐标为第一关键字排序
	if(a.y==b.y) return a.x<b.x;
	return a.y<b.y;
}
long long sq(long long a){
	return a*a;
}
long long sqdis(dot a,dot b){//两点距离的平方
	return (sq(a.x-b.x)+sq(a.y-b.y));
}
bool cmpk(long long i){/*判断线段a[i-1]a[i],线段a[i]a[i+1]是否垂直，
我用了勾股定理，其实也可以用向量*/
	return sqdis(a[i],a[i-1])+sqdis(a[i],a[i+1])==sqdis(a[i-1],a[i+1]);
}
bool check(long long n){//判断线路是否合理
	long long i;
	for(i=2;i<=n-1;i++){
		if(!cmpk(i)){
			return false;
		}
	}
	return true;
}
long long qpow(long long a,long long p){//快速幂
	long long k=a,ans=1;
	while(p){
		if(p%2) ans=ans*k%mod;
		k=k*k%mod;
		p/=2;
	}
	return ans;
}
int main(){
	long long n,i,v,s,t;
	scanf("%lld%lld",&n,&v);
	n++;
	for(i=1;i<=n;i++){
		scanf("%lld%lld",&a[i].x,&a[i].y);
	}
	sort(a+1,a+n+1,cmpx);//若路线的点按x轴递增
	if(check(n)){
		s=0;
		for(i=1;i<=n-1;i++){
			t=sqdis(a[i],a[i+1])%mod;
			s=(s+t)%mod;
		}
		s=s*(qpow(v,mod-2)%mod)%mod*(qpow(v,mod-2)%mod)%mod;
//对s/(v^2)在取模意义上进行运算，后面同理
		printf("%lld",s);
		return 0;
	}
	sort(a+1,a+n+1,cmpy);//若路线的点按y轴递增
	if(check(n)){
		s=0;
		for(i=1;i<=n-1;i++){
			t=sqdis(a[i],a[i+1])%mod;
			s=(s+t)%mod;
		}
		s=s*(qpow(v,mod-2)%mod)%mod*(qpow(v,mod-2)%mod)%mod;
		printf("%lld",s);
		return 0;
	}
	sort(a+1,a+n+1,cmpx);//若路线与坐标轴平行或重合，因为题目保证有解，所以不用验证
	s=0;
	for(i=1;i<=n-1;i++){
		if(a[i].x==a[i+1].x){
			t=sqdis(a[i],a[i+1])%mod;
			s=(s+t)%mod;
		}
	}
	sort(a+1,a+n+1,cmpy);
	for(i=1;i<=n-1;i++){
		if(a[i].y==a[i+1].y){
			t=sqdis(a[i],a[i+1])%mod;
			s=(s+t)%mod;
		}
	}
	s=s*(qpow(v,mod-2)%mod)%mod*(qpow(v,mod-2)%mod)%mod;
	printf("%lld",s);
	return 0;
}
```

## 后记

**后记的前言**

同志们想看就看，不想看也可以跳过（因为讲的东西和题目关系并不是很大）

**后记的正文：关于贪心**

还有对于贪心策略，我是这样想的：

除非是比赛时为了骗分，应该把贪心策略严格证明出来才罢休。严谨的证明才是支撑贪心策略的基础。

这就是我贡上这么长的证明过程的原因。

**后记的后记**

最后附上那句无名氏说的话吧：

题解千万条，理解第一条。如果直接抄，棕名两行泪。

---

## 作者：Mo_Han136 (赞：2)

~~过来蹭一篇题解……~~

[P7778 『JROI-2』Dancing Line](https://www.luogu.com.cn/problem/P7778)

## 题目描述

有一段折线，每个折点为顺时针或逆时针旋转 $90 \degree$，且相邻两个折点的方向相反。

现给 $n+1$ 个点，包括起点、终点和折点，保证这些点组成的折线合法，求 $\sum_{i=1}^nt_i^2,t_i=\dfrac{d(P_{i-1},P_i)}{v}$。

## 题解

按照题意实际上答案为 $ans=\dfrac{\sum_{i=1}^{n}d(P_{i-1},P_i)^2}{v^2}$。

因此只需求 $\sum_{i=1}^{n}d(P_{i-1},P_i)^2$。

可以分成三种情况讨论：

（1）：

![1](https://cdn.luogu.com.cn/upload/image_hosting/3cisfoi0.png)

关于这种情况，可以发现每个点的 $x_i$ 各不相同，且$x_i$ 相邻的点相连。

因此只需按照 $x_i$ 排序后从小到大依次连接计算即可。

（当然还是要判断是否合法的……）

实现起来非常简单：

```cpp
sort(a,a+n+1,cmp1);fl=1;
rep(i,1,n)if(a[i-1].x==a[i].x)fl=0;
if(fl && chk()){
	rep(i,1,n)Add(ans,calc(i));
	printf("%lld\n",1ll*ans*m%P);return 0;
}
```

（2）：

![2](https://cdn.luogu.com.cn/upload/image_hosting/kvz5pjhe.png)

同样发现 $y_i$ 相邻的点相连，因此按照 $y_i$ 排序后依次计算即可。

实现起来和（1）几乎一样：

```cpp
sort(a,a+n+1,cmp2);fl=1;
rep(i,1,n)if(a[i-1].y==a[i].y)fl=0;
if(fl && chk()){
	rep(i,1,n)Add(ans,calc(i));
	printf("%lld\n",1ll*ans*m%P);return 0;
}
```

（3）：

![3](https://cdn.luogu.com.cn/upload/image_hosting/0eb2ri0s.png)

一开始觉得这是最棘手的情况，因为 $x_i$ 和 $y_i$ 都没有特点。

结果发现只需要将 $x_i$ 或 $y_i$ 相等的两个点进行计算即可……

排除了（1）（2）后就只可能是（3）了，因此连是否合法都不需要判断。

```cpp
sort(a,a+n+1,cmp1);
rep(i,1,n)if(a[i-1].x==a[i].x)Add(ANS,calc(i));
sort(a,a+n+1,cmp2);
rep(i,1,n)if(a[i-1].y==a[i].y)Add(ANS,calc(i));
printf("%lld\n",1ll*ANS*m%P);
```

## 实现

没拿到最优解，但也懒得优化了，就这样吧……

```cpp
#include<bits/stdc++.h>
#define db double
#define reg register
#define LL long long
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define ull unsigned long long
#define rep(i,a,b) for(int i=a,i##end=b;i<=i##end;++i)
#define drep(i,a,b) for(int i=a,i##end=b;i>=i##end;--i)
#define erep(i,a) for(int i=head[a];i;i=e[i].nxt)


using namespace std;
bool Handsome;
inline int rd(){
	reg int x=0;reg char o=getchar();reg bool O=0;
	for(;o<48 || 57<o;o=getchar())if(o=='-')O=1;
	for(;48<=o && o<=57;o=getchar())x=(x<<1)+(x<<3)+(o^48);
	return O?-x:x;
}
inline void Mi(int &x,int y){if(x>y && (x=y));}
inline void Mx(int &x,int y){if(x<y && (x=y));}
const int M=1e6+5,P=998244353;
int n,m,ans,ANS;bool fl;
struct node{int x,y;}a[M];
bool cmp1(node a,node b){return a.x<b.x;}
bool cmp2(node a,node b){return a.y<b.y;}
void Add(int &x,int y){
	x+=y;
	if(x>=P)x-=P;
	if(x<0)x+=P;
}
int FAST(int x,int y){
	int res=1;
	for(;y;y>>=1){
		if(y&1)res=1ll*res*x%P;
		x=1ll*x*x%P;
	}
	return res;
}
int calc(int p){
	LL x=(a[p-1].x-a[p].x);
	LL y=(a[p-1].y-a[p].y);
	return (x*x+y*y)%P;
}
const db e=1e-10;
bool chk(){
	db k=1.0*(a[1].x-a[0].x)/(a[1].y-a[0].y);
	rep(i,2,n){
		db t;
		if(i&1)t=1.0*(a[i].x-a[i-1].x)/(a[i].y-a[i-1].y);
		else t=1.0*(a[i].y-a[i-1].y)/(a[i-1].x-a[i].x);
		if(fabs(k-t)>e)return 0;
	}
	return 1;
}
bool Most;
int main(){
//	printf("%.2lfMB\n",(&Most-&Handsome)/1024.0/1024.0);
	n=rd();m=rd();m=FAST(1ll*m*m%P,P-2);
	rep(i,0,n)a[i].x=rd(),a[i].y=rd();
	sort(a,a+n+1,cmp1);fl=1;
	rep(i,1,n)if(a[i-1].x==a[i].x)fl=0,Add(ANS,calc(i));
	if(fl && chk()){
		rep(i,1,n)Add(ans,calc(i));
		printf("%lld\n",1ll*ans*m%P);return 0;
	}
	sort(a,a+n+1,cmp2);fl=1;
	rep(i,1,n)if(a[i-1].y==a[i].y)fl=0,Add(ANS,calc(i));
	if(fl && chk()){
		rep(i,1,n)Add(ans,calc(i));
		printf("%lld\n",1ll*ans*m%P);return 0;
	}
	printf("%lld\n",1ll*ANS*m%P);
	return 0;
}
```

$\mathcal{By}\quad\mathcal{Most}\ \mathcal{Handsome}$

$\mathcal{2021.08.06}$

---

## 作者：MC_OIer (赞：1)

# P7778 解题报告
## 解题思路
考虑到不能连续同一个方向转弯两次，每次转弯的角度都为直角，所以不可能出现“调头”的情况，所以将每个点按横/纵坐标排序，必定有一种正确。  
坑点：只要两次排序？不，考虑两个横坐标相等的点 $p$，$q$，不妨设 $p$ 的纵坐标大于 $q$ 的纵坐标，那么 $p$ 在前或 $q$ 在前都有可能成为答案。于是就有了这四种比较函数：  
```cpp
bool cmp1(node p,node q){
    if(p.x==q.x)return p.y<q.y;
    return p.x<q.x;
}
bool cmp2(node p,node q){
    if(p.y==q.y)return p.x<q.x;
    return p.y<q.y;
}
bool cmp3(node p,node q){
    if(p.x==q.x)return p.y>q.y;
    return p.x<q.x;
}
bool cmp4(node p,node q){
    if(p.y==q.y)return p.x>q.x;
    return p.y<q.y;
}
```
接着考虑如何判断排列是否合法，即判断是否每个角都是直角。根据勾股逆定理，我们知道当三角形三边分别为 $a$，$b$，$c$ 时，若 $c^2=a^2+b^2$，那么这个三角形为直角三角形且斜边为 $c$。使用这个定理就可以简单快速地验证直角：
```cpp
int dist(node p,node q){
    return ((q.x-p.x)*(q.x-p.x)%mod+(q.y-p.y)*(q.y-p.y)%mod)%mod;
}//注意，这里dist计算的是两点距离的平方，题目不需要我们求两点间的距离，最后答案也是求平方
bool check(){
    bool flag=true;
    for(int i=0;i<=n-2;i++){
        if((dist(a[i],a[i+1])+dist(a[i+1],a[i+2]))%mod!=dist(a[i],a[i+2])){
            flag=false;
            break;
        }
    }
    return flag;
}
```
至此，只剩统计答案了，枚举每条边让答案加上距离的平方，最后整个除以 $v^2$ 即可。  
坑点：算答案的时候不能直接把 $v^2$ 塞进快速幂，long long 会爆炸，先取模再塞进去就可以了。
```cpp
for(int i=0;i<n;i++){
    ans+=dist(a[i],a[i+1]);
    ans%=mod;
}
cout<<(ans*qpow((v*v)%mod,mod-2))%mod;
```
## 完整代码
```cpp
#include<bits/stdc++.h>
#define mod 998244353
#define int long long
using namespace std;
int qpow(int a,int b){
    int res=1;
    while(b){
        if(b%2!=0)res=(res*a)%mod;
        a=(a*a)%mod;
        b/=2;
    }
    return res;
}
struct node{
    int x,y;
}a[1000005];
bool cmp1(node p,node q){
    if(p.x==q.x)return p.y<q.y;
    return p.x<q.x;
}
bool cmp2(node p,node q){
    if(p.y==q.y)return p.x<q.x;
    return p.y<q.y;
}
bool cmp3(node p,node q){
    if(p.x==q.x)return p.y>q.y;
    return p.x<q.x;
}
bool cmp4(node p,node q){
    if(p.y==q.y)return p.x>q.x;
    return p.y<q.y;
}
int n,v,ans;
int dist(node p,node q){
    return ((q.x-p.x)*(q.x-p.x)%mod+(q.y-p.y)*(q.y-p.y)%mod)%mod;
}
bool check(){
    bool flag=true;
    for(int i=0;i<=n-2;i++){
        if((dist(a[i],a[i+1])+dist(a[i+1],a[i+2]))%mod!=dist(a[i],a[i+2])){
            flag=false;
            break;
        }
    }
    return flag;
}
inline void print(int n){if(n<0){putchar('-');print(-n);return;}if(n>9)print(n/10);putchar(n%10+'0');}
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
signed main(){
    cin>>n>>v;
    for(int i=0;i<=n;i++)cin>>a[i].x>>a[i].y;
    sort(a,a+1+n,cmp1); 
    if(check())goto awa;  
    sort(a,a+1+n,cmp2);
    if(check())goto awa; 
    sort(a,a+1+n,cmp3);
    if(check())goto awa; 
    sort(a,a+1+n,cmp4);
    if(check())goto awa; 
    awa:;//其实就是check返回1就跳到这里，我用了神奇的goto来实现
    for(int i=0;i<n;i++){
        ans+=dist(a[i],a[i+1]);
        ans%=mod;
    }
    cout<<(ans*qpow((v*v)%mod,mod-2))%mod;
    return 0;
}
//坑点上面都讲过了，就没放什么注释了
```

---

## 作者：Jorisy (赞：0)

不难发现，一条路径的拐点的坐标中必有至少一维是单调的，于是枚举即可。

特别地，对于路径平行于坐标轴的，要枚举横纵坐标的单调性。

代码写的一坨。
```cpp
#include<bits/stdc++.h>
#define ll long long
#define mod 998244353
using namespace std;

struct node{
    ll x,y;
}a[1000005];
int n,v;
ll ans;

bool cmp1(node x,node y)
{
    return x.x==y.x?x.y<y.y:x.x<y.x;
}

bool cmp2(node x,node y)
{
    return x.y==y.y?x.x<y.x:x.y<y.y;
}

bool cmp3(node x,node y)
{
    return x.x==y.x?x.y>y.y:x.x<y.x;
}

bool cmp4(node x,node y)
{
    return x.y==y.y?x.x>y.x:x.y<y.y;
}

ll qpow(ll x,ll y)
{
    ll res=1;
    while(y)
    {
        if(y&1) res=res*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return res;
}

int main()
{
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout)
    scanf("%d%d",&n,&v);
    n++;
    for(int i=1;i<=n;i++) scanf("%lld%lld",&a[i].x,&a[i].y);
    sort(a+1,a+n+1,cmp1);
    for(int i=2;i<n;i++)
    {
        if((a[i-1].y-a[i].y)*(a[i+1].y-a[i].y)+(a[i+1].x-a[i].x)*(a[i-1].x-a[i].x)) goto p1;
    }
    goto p0;
    p1:;
    sort(a+1,a+n+1,cmp2);
    for(int i=2;i<n;i++)
    {
        if((a[i-1].y-a[i].y)*(a[i+1].y-a[i].y)+(a[i+1].x-a[i].x)*(a[i-1].x-a[i].x)) goto p2;
    }
    goto p0;
    p2:;
    sort(a+1,a+n+1,cmp3);
    for(int i=2;i<n;i++)
    {
        if((a[i-1].y-a[i].y)*(a[i+1].y-a[i].y)+(a[i+1].x-a[i].x)*(a[i-1].x-a[i].x)) goto p3;
    }
    goto p0;
    p3:;
    sort(a+1,a+n+1,cmp4);
    p0:;
    for(int i=2;i<=n;i++)
    {
        ll d1=a[i-1].x-a[i].x,d2=a[i-1].y-a[i].y;
        (ans+=d1*d1%mod+d2*d2%mod)%=mod;
    }
    cout<<ans*qpow(1ll*v*v%mod,mod-2)%mod;
    return 0;
}
```

---

