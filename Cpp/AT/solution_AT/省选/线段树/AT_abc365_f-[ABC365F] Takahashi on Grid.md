# [ABC365F] Takahashi on Grid

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc365/tasks/abc365_f

平面上に無限個のマスがあります。 整数の $ 2 $ つ組 $ (x,y) $ すべてに対して対応するマスがひとつ存在し、マス $ (x,y) $ と呼ぶことにします。

すべてのマスは、それぞれ空きマスか壁マスのどちらか一方です。  
 長さ $ N $ の正整数列 $ L=(L\ _\ 1,L\ _\ 2,\dotsc,L\ _\ N),U=(U\ _\ 1,U\ _\ 2,\dotsc,U\ _\ N) $ が与えられます。 ここで、$ i=1,2,\ldots,N $ について $ L\ _\ i,U\ _\ i $ は $ 1\leq\ L\ _\ i\leq\ U\ _\ i\leq10\ ^\ 9 $ を満たします。  
 マス $ (x,y)\ (1\leq\ x\leq\ N,L\ _\ x\leq\ y\leq\ U\ _\ x) $ はすべて空きマスで、それ以外のマスは壁マスです。

高橋くんが空きマスであるマス $ (x,y) $ にいるとき、次の行動のいずれかを行うことができます。

- マス $ (x+1,y) $ が空きマスならば、マス $ (x+1,y) $ に移動する。
- マス $ (x-1,y) $ が空きマスならば、マス $ (x-1,y) $ に移動する。
- マス $ (x,y+1) $ が空きマスならば、マス $ (x,y+1) $ に移動する。
- マス $ (x,y-1) $ が空きマスならば、マス $ (x,y-1) $ に移動する。
 
どの空きマスどうしも、高橋くんが行動を繰り返すことで行き来できることが保証されます。

次の形式の $ Q $ 個の質問に答えてください。

$ i $ 番目 $ (1\leq\ i\leq\ Q) $ の質問では整数の $ 4 $ つ組 $ (s\ _\ {x,i},s\ _\ {y,i},t\ _\ {x,i},t\ _\ {y,i}) $ が与えられるので、高橋くんがマス $ (s\ _\ {x,i},s\ _\ {y,i}) $ にいるところからマス $ (t\ _\ {x,i},t\ _\ {y,i}) $ に移動するために必要な行動回数の最小値を求めてください。 各質問について、与えられる $ 2 $ つのマスは空きマスであることが保証されます。

## 说明/提示

### 制約

- $ 1\leq\ N\leq2\times10\ ^\ 5 $
- $ 1\leq\ L\ _\ i\leq\ U\ _\ i\leq10\ ^\ 9\ (1\leq\ i\leq\ N) $
- $ \lbrack\ L\ _\ i,U\ _\ i\rbrack\cap\lbrack\ L\ _\ {i+1},U\ _\ {i+1}\rbrack\neq\emptyset\ (1\leq\ i\lt\ N) $
- $ 1\leq\ Q\leq2\times10\ ^\ 5 $
- $ 1\leq\ s\ _\ {x,i}\leq\ N $ かつ $ L\ _\ {s\ _\ {x,i}}\leq\ s\ _\ {y,i}\leq\ U\ _\ {s\ _\ {x,i}}\ (1\leq\ i\leq\ Q) $
- $ 1\leq\ t\ _\ {x,i}\leq\ N $ かつ $ L\ _\ {t\ _\ {x,i}}\leq\ t\ _\ {y,i}\leq\ U\ _\ {t\ _\ {x,i}}\ (1\leq\ i\leq\ Q) $
- 入力はすべて整数
 
### Sample Explanation 1

与えられたマスは以下のようになります。 !\[\](https://img.atcoder.jp/abc365/4d07a40c98eda33ee86b773e564681c7.png) $ 1 $ つめの質問では、例えば以下のように移動することでマス $ (1,4) $ からマス $ (6,3) $ へ $ 10 $ 回の行動で移動することができます。 !\[\](https://img.atcoder.jp/abc365/4e579f6b171a642891732ae6efcdd550.png) $ 9 $ 回以下の行動でマス $ (1,4) $ からマス $ (6,3) $ へ移動することはできないため、$ 10 $ を出力してください。

### Sample Explanation 2

出力すべき値が $ 32\operatorname{bit} $ 整数に収まらない場合があることに注意してください。

## 样例 #1

### 输入

```
7
1 5
3 3
1 3
1 1
1 4
2 4
3 5
3
1 4 6 3
1 4 1 1
7 5 1 5```

### 输出

```
10
3
14```

## 样例 #2

### 输入

```
12
1 1000000000
1000000000 1000000000
1 1000000000
1 1
1 1000000000
1000000000 1000000000
1 1000000000
1 1
1 1000000000
1000000000 1000000000
1 1000000000
1 1
1
1 1 12 1```

### 输出

```
6000000005```

## 样例 #3

### 输入

```
10
1694 7483
3396 5566
2567 6970
1255 3799
2657 3195
3158 8007
3368 8266
1447 6359
5365 8614
3141 7245
15
3 3911 6 4694
7 5850 10 4641
1 5586 6 4808
2 3401 8 2676
3 3023 6 6923
8 4082 3 6531
6 3216 7 6282
8 5121 8 3459
8 4388 1 6339
6 6001 3 6771
10 5873 8 5780
1 6512 6 6832
8 5345 7 4975
10 4010 8 2355
7 5837 9 6279```

### 输出

```
2218
1212
4009
1077
3903
4228
3067
1662
4344
6385
95
6959
371
4367
444```

# 题解

## 作者：_JoeyJ_ (赞：13)

## 题解

容易发现题目中的一段连续的区间可以分为两类：

- 区间有交，可以一路到底的：

  ![](https://cdn.luogu.com.cn/upload/image_hosting/461r3mcn.png)

- 区间无交，需要绕路的：

  ![](https://cdn.luogu.com.cn/upload/image_hosting/vy4dwiqc.png)

对于这两类连续段，我们考虑现在起点和终点分别在这段区间的首位两个区间时对答案的横向贡献：

- 区间有交时，若起点（终点）在区间中，则贡献为 $0$
，否则贡献为起点（终点）到该区间的最小距离。

- 区间无交时，我们先计算出通过这段区间的最短路的起点（终点），发现从起点（终点）先走到最短路的起点（终点）肯定不劣，所以直接计算起点（终点）走到最短路的起点（终点）的距离。

现在的问题在于如何合并区间信息并计算贡献，我们称区间有交的连续段为 A 类，区间无交的连续段为 B 类。显然单个区间均为 A 类连续段。合并可以分为以下几种情况：

- 合并 A 类连续段和 A 类连续段。若合并后区间仍有交集，则合并后仍然是 A 类连续段，合并的贡献为 $0$。否则合并后为 B 类连续段，贡献增加两个区间的最短路的距离。

  ![](https://cdn.luogu.com.cn/upload/image_hosting/yi7h3x4b.png)

- 合并 B 类连续段和 B 类连续段。这是简单的，合并后仍然是 B 类连续段，贡献增加前面连续段最短路的终点和后面连续段最短路起点的距离。

  ![](https://cdn.luogu.com.cn/upload/image_hosting/uftju3jj.png)

- 合并 A 类连续段和 B 类连续段。若 B 类连续段端点在 A 类连续段中，则合并的贡献为 $0$，否则贡献为端点到 A 类连续段区间交的最短路。

  ![](https://cdn.luogu.com.cn/upload/image_hosting/ryop95vw.png)

最后加上纵向贡献和起点与终点的横向贡献就可以了。

## 代码

信息合并，`typ=0` 是 A 类，`typ=1` 是 B 类。

```cpp
struct Seg{
    int l,r,typ,w;
    pair<int,int> st,ed;
    Seg(){}
    Seg(int a,int b){l=a;r=b;typ=0;st=ed={a,b};}
    Seg(int a,int b,pair<int,int> c,pair<int,int> d,int wr,int t){l=a;r=b;typ=t;st=c;ed=d;w=wr;}
    Seg operator +(Seg x){
        if(typ==-1||x.typ==-1) return Seg(0,0,{0,0},{0,0},inf,-1);
        if(max(ed.first,x.st.first)>min(ed.second,x.st.second)) return Seg(0,0,{0,0},{0,0},inf,-1);
        if(typ){
            if(x.typ){
                return Seg(l,x.r,st,x.ed,w+x.w+abs(r-x.l),1);
            }else{
                if(r<x.l) return Seg(l,x.l,st,x.ed,w+x.w+abs(r-x.l),1);
                else if(r>x.r) return Seg(l,x.r,st,x.ed,w+x.w+abs(r-x.r),1);
                else return Seg(l,r,st,x.ed,w+x.w,1);
            }
        }else{
            if(x.typ){
                if(l>x.l) return Seg(l,x.r,st,x.ed,w+x.w+abs(l-x.l),1);
                else if(r<x.l) return Seg(r,x.r,st,x.ed,w+x.w+abs(r-x.l),1);
                else return Seg(x.l,x.r,st,x.ed,w+x.w,1);
            }else{
                if(l>x.r) return Seg(l,x.r,st,x.ed,w+x.w+abs(l-x.r),1);
                else if(r<x.l) return Seg(r,x.l,st,x.ed,w+x.w+abs(r-x.l),1);
                else return Seg(max(l,x.l),min(r,x.r),st,x.ed,w+x.w,0);
            }
        }
    }
};
```
```cpp
int s,t,a,b;
cin>>s>>a>>t>>b;
if(s>t) swap(s,t),swap(a,b);
Seg res=Query(1,s,t);
if(res.typ==-1) cout<<-1<<endl;
else{
    int ans=res.w+abs(s-t);
    if(res.typ) ans+=abs(a-res.l)+abs(b-res.r);
    else{
        if(a<res.l&&b<res.l||a>res.r&&b>res.r) ans+=min(abs(a-res.l),abs(a-res.r))+min(abs(b-res.l),abs(b-res.r));
        else ans+=abs(a-b);
    }
  cout<<ans<<endl;
}
```

---

## 作者：DengDuck (赞：13)

支持修改操作的线段树做法。

## 鸣谢

感谢 @_JoeyJ_ 还有 @DeepSeaSpray 两位大神对我的帮助，感激不尽。


本题解的图来自大神 @_JoeyJ_，厕纸是电，厕纸是光，厕纸是唯一的神话！

## 正文

我们用线段树维护区间答案，当然由于答案对于不同的横坐标不相同，所以我们维护的可以说是区间的策略。

该维护啥？咋维护？探究一手走路的策略，我们肯定是：

- 能往下走直接就往下走。
- 不能往下走就左右调整横坐标，直到可以走。

我们以此对区间分类：

对于第一种，我们发现区间内的所有 $[L_i,R_i]$ 的交应该是不为空的，这样我们就会先走到这个交集内，然后一路向下，“从南走到北，从白走到黑”。

![](https://cdn.luogu.com.cn/upload/image_hosting/461r3mcn.png)


对于第二种，交应该是空的，所以我们需要不断地调整横坐标位置，然后走到人家那我们再向下走。

![](https://cdn.luogu.com.cn/upload/image_hosting/vy4dwiqc.png)

然后我们发现这种情况总是存在一个最优入口和最优出口，就是无论我一开始在什么位置，我先走到这个最优入口肯定不劣。同理最后无论要到哪里，先从最优出口出来肯定不劣。

为啥肯定有这样一个东西存在呢？考虑我们的 $[L_i,R_i]$ 无交，所以我走的时候肯定应该向左拐或者向右拐至少一次，因此我们先走到一开始的区间左端点或者右端点肯定不劣（注意可能这个第二种区间是第一种区间和第二种区间拼出来的，那么最优入口是第一种区间那个交的左端点或右端点），出口同理。

因此，我们发现需要维护区间内所有的 $[L_i,R_i]$ 的交，如果是第二种区间，我们还要维护最优入口、最优出口，还有在这其中行走的最小代价，然后我们求解问题就很简单了！

然后我们大力分讨合并区间：

- 对于两个第一种区间，要是有交，那么就还是第一种区间，求出交集。
- 对于两个第一种区间，要是无交，那么就变成第二种区间，讨论位置关系求入口出口。
- 对于两个第二种区间，最优入口是前者的最优入口，最优出口是后者的最优出口。
- 对于第一种区间和第二种区间，分讨位置关系得到最优入口，最优出口是后者的最优出口。
- 对于第二种区间和第一种区间，最优入口是前者的最优入口，分讨位置关系得到最优出口。

记得合并代价。

最后依旧是分讨一下起点终点横坐标与最优入口出口或者交区间的位置关系，然后就做完了。

时间复杂度是大常数的 $\mathcal O((n+q)\log n)$，代码有点难写，因为分讨。

```cpp
#include<bits/stdc++.h>
#define LL long long
#define Ls(x) (x<<1)
#define Rs(x) (x<<1|1)
#define Mid (L+R>>1)
using namespace std;
const int N=6e5+5;
int n,Q,pL[N],pR[N];
struct Tree{int L,R,U,V;LL W;}t[N<<2];
inline Tree Mrg(Tree X,Tree Y,int P)
{
	Tree Res;
	Res.L=max(X.L,Y.L),Res.R=min(X.R,Y.R),Res.W=X.W+Y.W+1;
	if(pR[P]<pL[P+1]||pR[P+1]<pL[P]||X.W==-1||Y.W==-1)
	{
		Res.W=-1;
		return Res;
	}
	if(X.R<X.L&&Y.R<Y.L)
		Res.U=X.U,Res.V=Y.V,Res.W+=abs(X.V-Y.U);
	else if(X.R<X.L)
	{
		Res.U=X.U;
		if(X.V<Y.L)Res.V=Y.L,Res.W+=Y.L-X.V;
		else if(X.V>Y.R)Res.V=Y.R,Res.W+=X.V-Y.R;
		else Res.V=X.V;
	}
	else if(Y.R<Y.L)
	{
		Res.V=Y.V;
		if(Y.U<X.L)Res.U=X.L,Res.W+=X.L-Y.U;
		else if(Y.U>X.R)Res.U=X.R,Res.W+=Y.U-X.R;
		else Res.U=Y.U;
	}	
	else if(Res.L>Res.R)
	{
		if(X.R<Y.L)Res.U=X.R,Res.V=Y.L,Res.W+=Y.L-X.R;
		else Res.U=X.L,Res.V=Y.R,Res.W+=X.L-Y.R;
	}
	return Res;
}
void Upd(int Rt,int L,int R,int x)
{
	if(L==R)
	{
		t[Rt].L=pL[x],t[Rt].R=pR[x];
		return;
	}
	if(x<=Mid)Upd(Ls(Rt),L,Mid,x);
	else Upd(Rs(Rt),Mid+1,R,x);
	t[Rt]=Mrg(t[Ls(Rt)],t[Rs(Rt)],Mid);
}
Tree Qry(int Rt,int L,int R,int l,int r)
{
	if(l<=L&&R<=r)return t[Rt];
	if(r<=Mid)return Qry(Ls(Rt),L,Mid,l,r);
	if(Mid<l)return Qry(Rs(Rt),Mid+1,R,l,r);
	return Mrg(Qry(Ls(Rt),L,Mid,l,r),Qry(Rs(Rt),Mid+1,R,l,r),Mid);
}
int main()
{
	scanf("%d",&n);
	for(int i=1,l,r;i<=n;i++)
	{
		scanf("%d%d",&l,&r);
		pL[i]=l,pR[i]=r;
		Upd(1,1,n,i);
	}
	scanf("%d",&Q);
	while(Q--)
	{
		int l,r,x,y;
		scanf("%d%d%d%d",&l,&x,&r,&y);
		if(l>r)swap(l,r),swap(x,y);
		if(x<pL[l]||x>pR[l]||y<pL[r]||y>pR[r])
		{
			puts("-1");
			continue;
		}
		Tree Res=Qry(1,1,n,l,r);
		if(Res.L>Res.R)
		{
			if(Res.W==-1)puts("-1");
			else
			{
				Res.W+=abs(x-Res.U)+abs(y-Res.V);
				printf("%lld\n",Res.W);
			}
		}
		else
		{
			if(x<Res.L)Res.W+=Res.L-x+abs(Res.L-y);
			else if(Res.R<x)Res.W+=x-Res.R+abs(Res.R-y);
			else Res.W+=abs(x-y);
			printf("%lld\n",Res.W);
		}
	}
}
```

---

## 作者：快乐的大童 (赞：4)

官方题解区有一个在线单 log 做法和一个离线双 log 的做法。

这里是一个离线单 log 的做法。

为了表述方便，令：
- $x$ 轴正方向为“下”，$y$ 轴正方向为“右”，“行”即为 $x$ 轴，“列”即为 $y$ 轴。
  - 实际上，本篇文章是将原题的坐标系视为二维数组进行讨论的。
- 原题面中的 $U_i$ 为 $R_i$。

### 分析

首先令起点在终点的上方。

其次，我们的最优方案一定会从起点开始，一直往下走，直到走不动了，或者走到终点所在行了。

如果能走到终点所在行，直接特判掉。

否则，我们一定会向左/右不断的走直到找到一个可以继续往下走的地方，且会走到下一行的左/右端点，因为你往非端点的格子多走一定不优。具体地，设此时我们在坐标 $(x,y)$，若 $y<L_{x+1}$，则我们会移动到 $(x+1,L_{x+1})$；若 $y>R_{x+1}$，则我们会移动到 $(x+1,R_{x+1})$；不存在其他情况，否则可以继续往下走。

走到 $(x+1,L_{x+1})$ 或者 $(x+1,R_{x+1})$ 后，继续按照以上方法一直往下走直到走不了或者走到终点所在行，然后又走到了 $(x'+1,L_{x'+1})$ 或者 $(x'+1,R_{x'+1})$，然后继续走直到走到终点所在行。

我们对于每一行的左右端点维护从此处出发最终会到达哪一行以及左端点还是右端点。暴力跳即可，时间复杂度显然可以被卡到 $O(n^2)$，但优化也比较简单，直接倍增跳即可。

最后我们需要解决如何快速找到从某点出发最终会跳到哪一行（跳到左右端点是好求的，因为往下走的过程中纵坐标不变）。

考虑离线，从后往前扫起点所在行 $i$，那么区间 $[1,L_i),(R_i,10^9]$ 无法被到达，横坐标在 $i$ 之前，纵坐标在这些区间中的点会在此行无法继续往下走，所以把这两段区间用 $i$ 推平即可（实际上主席树应该也能做到在线）。

时间复杂度 $O((n+q)\log n)$。

[code](https://atcoder.jp/contests/abc365/submissions/56334751)

~~注释的位置可能比较抽象，请谨慎阅读~~

---

## 作者：wmrqwq (赞：2)

# 题目链接

[at_abc365_f](https://atcoder.jp/contests/abc365/tasks/abc365_f)

# 解题思路

根号分治。

首先有一个显然的贪心，就是能往右走，是一定要往右走的，而剩下的情况，若我们在最高点的上面，那么一直往下走直到可以往右走是最优的，若我们在最低点的下面，那么一直往上走直到可以往右走是最优的。

于是我们就有了 $O(nq)$ 的做法。

设阙值为 $B$，需要行走的横距离小于等于 $B$ 的询问直接暴力做即可。

对于剩余的情况，我们可以直接预处理 $f1_{i,0/1}$ 表示第 $i$ 格的最上/下方到达 $i + \sqrt{n}$ 格时所需的最少的步数，$f2_{i,0/1}$ 表示第 $i$ 格的最上/下方到达 $i + \sqrt{n}$ 格时所需的最少的步数最终到达的点。

于是对于一开始，我们可以直接使用线段树 + 二分的方式来找到第一个不能直接往右走的点，之后走 $\sqrt{n}$ 格后再次进行二分，这样循环往复地进行操作即可。

时间复杂度 $O(n \sqrt{n} \log n)$。

---

## 作者：zrl123456 (赞：2)

[[ABC365F] Takahashi on Grid](https://www.luogu.com.cn/problem/AT_abc365_f)  

题目考察：ST 表，倍增。  
题目简述：  
有一个地图 $a$，横坐标在 $[1,n]$。地图上有一些点可以通过，对于 $i\in[1,n]$，$a_{i,l_i},a_{i,l_{i+1}},\dots,a_{i,t_i}$ 是可以通过的。然后有 $q$ 次询问，每次询问给出 $s_x,s_y,t_x,t_y$，求从 $(s_x,s_y)$ 到 $(t_x,t_y)$ 所走的最短路径。  
数据范围：
- $1\le n,q\le 2\times 10^5$
- $\forall i\in[1,n],1\le l_i,u_i\le 10^9$
- $\forall i\in[1,n-1],[l_i,u_i]\cup[l_{i+1},u_{i+1}]\ne\emptyset$
- $1\le s_x,t_x\le n,l_{s_x}\le s_y\le u_{s_x},l_{t_x}\le t_y\le u_{t_x}$
---
我们将 $x$ 坐标为 $i$ 的所有点称为第 $i$ 层，由于每一层的可通过点都是一个区间。所以说我们用一种贪心策略（能下一层就不继续走），设我们在走到下一层要向左走：
- 若我们的走到下下层要向左走，那么我们一直往左或下走就可以得到最短路。
- 反之，我们肯定希望靠着右边走，这样才能更快的往下走。

那么我们可以维护一个 ST 表，$mx_{i,j}$ 表示 $\displaystyle\max_{k=i}^{i+2^j-1}(l_k)$，$mn_{i,j}$ 表示 $\displaystyle\min_{k=i}^{i+2^j-1}(u_k)$，然后我们倍增对于每一个询问一直往下跳，直到跳不下去了为止。我们在预处理出 $fl_{i,j}$ 和 $fu_{i,j}$，代表从 $l_i$ 和 $u_i$ 跳下去 $2^j-1$ 层所花费的代价，然后我们往下跳 $2^j-1$ 层，花费 $fl_{i,j}$ 或 $fu_{i,j}$（$j$ 是最大的 $j$ 使 $2^j\le len$，这里的 $len$ 指还需要往下跳的层数），继续往下递归（当然我们可以用同样的方法求出 $fl$ 和 $fu$）。  
这样我们每次求都是 $\Theta(\log n)$ 的，然后我们求 ST 表都是 $\Theta(n\log n)$ 的，所以总体复杂度是 $\Theta(n\log^2 n+q\log n)$。  

[代码](https://atcoder.jp/contests/abc365/submissions/56315878)

---

## 作者：Xy_top (赞：2)

赛时线段树询问的两个区间交换时少写了一句话，一直没调出来，写篇题解纪念一下。

和楼上的思路是一样的，重点讲下查询最后的步骤。

如果最后求出来的最短路是会拐弯的，不能一路走到底的那种，设这条最短路的起点和终点分别为 $s$ $t$，那么我们只需加上从起点走到 $s$，再从 $t$ 走到终点这两段距离即可。

如果求出来的最短路是一路走到底的那种。如果这个区间包含了出发的起点，那么直接往右走，走到和终点一列的时候走上去就行；如果这个区间没包含出发的起点，那么我们分别走两边然后取一下最小值即可。


```cpp
#include<bits/stdc++.h>
#define For(i, a, b) for(int i = (a); i <= (b); i ++)
#define foR(i, a, b) for(int i = (a); i >= (b); i --)
#define int long long
using namespace std;
int n, q;
int x[200005], y[200005];
struct Seg {
	int sx, sy, tx, ty;
	int mi;
}a[800005];
Seg merge (Seg s1, Seg s2) {
	Seg ret;
	ret.mi = s1.mi + s2.mi + 1;
	if (min (s1.ty, s2.sy) >= max (s1.tx, s2.sx) ) {
		if (s1.tx != s1.ty) {
			ret.sx = max (s1.tx, s2.sx);
			ret.sy = min (s1.ty, s2.sy);
		} else {
			ret.sx = s1.sx;
			ret.sy = s1.sy;
		}
		if (s2.sx != s2.sy) {
			ret.tx = max (s1.tx, s2.sx);
			ret.ty = min (s1.ty, s2.sy);
		} else {
			ret.tx = s2.tx;
			ret.ty = s2.ty;
		}
	} else {
		if (s1.ty < s2.sx) {
			ret.mi += s2.sx - s1.ty;
			ret.sx = s1.sy;
			ret.sy = s1.sy;
			ret.tx = s2.tx;
			ret.ty = s2.tx;
		} else {//s1.tx > s2.sy
			ret.mi += s1.tx - s2.sy;
			ret.sx = s1.sx;
			ret.sy = s1.sx;
			ret.tx = s2.ty;
			ret.ty = s2.ty;
		}
	}
	return ret;
}
void build (int l, int r, int k) {
	if (l == r) {
		a[k] = {x[l], y[l], x[l], y[l], 0};
		return;
	}
	int mid = l + r >> 1;
	build (l, mid, k << 1);
	build (mid + 1, r, k << 1 | 1);
	a[k] = merge (a[k << 1], a[k << 1 | 1]);
}
Seg query (int l, int r, int k, int x, int y) {
	if (x <= l && y >= r) return a[k];
	int mid = l + r >> 1;
	if (y <= mid) return query (l, mid, k << 1, x, y);
	if (x > mid) return query (mid + 1, r, k << 1 | 1, x, y);
	return merge (query (l, mid, k << 1, x, y), query (mid + 1, r, k << 1 | 1, x, y) );
}
void solve () {
	cin >> n;
	For (i, 1, n) cin >> x[i] >> y[i];
	build (1, n, 1);
	cin >> q;
	while (q --) {
		int sx, sy, tx, ty;
		cin >> sx >> sy >> tx >> ty;
		if (sx > tx) {
			swap (sx, tx);
			swap (sy, ty); //就是这句话漏写了
		}
		if (sx == tx) {
			cout << abs (sy - ty) << '\n';
			continue;
		}
		Seg s = query (1, n, 1, sx, tx);
		int ans = 10000000000000000LL;
		if (s.sx == s.sy) cout << s.mi + abs (sy - s.sx) + abs (ty - s.tx) << '\n';
		else {
			if (s.sx <= sy && sy <= s.sy) cout << s.mi + abs (sy - ty) << '\n';
			else {
				if (sy < s.sx) cout << s.mi + s.sx - sy + abs (s.tx - ty) << '\n';
				else cout << s.mi + sy - s.sy + abs (s.ty - ty) << '\n';
			}
		}
	}
}
signed main() {
	int _ = 1;
//	cin >> _;
	while (_ --) {
		solve ();
		cout << '\n';
	}
	return 0;
}
```

---

## 作者：Sorato_ (赞：0)

# ABC365F Takahashi on Grid 题解

## 题目大意

有一个网格图，对于 $i=1,2,\dots n$，第 $i$ 列的 $[L_i,U_i]$ 上的单元格是可到达的，形如下面这张图。

![](https://img.atcoder.jp/abc365/4d07a40c98eda33ee86b773e564681c7.png)

图中对于 $i=1,2,\dots7$，$[L_i,U_i]$ 分别为：

```
1 5
3 3
1 3
1 1
1 4
2 4
3 5
```

现有 $q$ 次询问，每次询问给定起点 $(sx,sy)$ 和终点 $(tx,ty)$。从起点出发，规定每次只能走到相邻的空单元格上，问最少走多少步能走到终点。

## Solve

首先考虑暴力怎么计算步数。假定起点在左，终点在右。贪心地，如果我当前单元格右侧是空的，直接向右走，否则走到右侧离他最近的空单元格。如此走到终点所在列之后再加上到终点的距离即可。$O(n)$ 暴力模拟之。

怎么优化？感觉要上一些数据结构，线段树不会，莫队感觉麻烦了，所以考虑分块。

对于一个起点，我一定是先一直水平向右走知道右侧没有空单元格，然后走到右侧空单元格的最上方或者最下方。所以对于每个块，我们维护如下信息：

- $sum_{i,0/1}$ 表示从第 $i$ 列空单元格的最下/上方开始，走到第 $i$ 列所在块的最右端所需最小步数。对于每一列都暴力模拟跑一遍即可，预处理总复杂度 $O(n\sqrt n)$。
- $p_{i,0/1}$ 表示从第 $i$ 列空单元格的最下/上方开始，走到第 $i$ 列所在块的最右端步数最小时，停在了第几行，处理 $sum$ 顺便记录下来即可。
- $mn_i$ 表示从第 $i$ 列所在块左端点到第 $i$ 列中，最上方的空单元格横坐标，即 $U$ 的最小值；$mx_i$ 表示从第 $i$ 列所在块左端点到第 $i$ 列中，最下方的空单元格横坐标，即 $L$ 的最大值。维护这些是为了方便求出一个单元格水平向右最多走到哪。

接下来考虑如何在询问时将相邻的块的信息拼接起来。

比如我们现在走到了第 $x$ 的块的右端点，横坐标为 $now$，我们需要找到第 $x+1$ 个块里，最左侧的第 $now$ 行不是空单元格的列。我们二分查找 $mn_{[l_{x+1},r_{x+1}]}$ 里第一个小于 $now$ 的位置 $p1$ 和 $mx_{[l_{x+1},r_{x+1}]}$ 里第一个大于 $now$ 的位置 $p2$，取 $\min$ 即可。

对于代价，若 $p1<p2$，令总代价加上 $sum_{p1,1}$，否则令总代价加上 $sum_{p2,0}$。即从第 $p1$ / $p2$ 列的最上/下方开始走到第 $x+1$ 块的最右端的代价。然后让 $now=p_{p1,1}$ / $p_{p2,0}$，继续下一块的拼接。

将整块拼接完后再特别处理一下终点所在散块的拼接，二分出第一个无法水平向右走到的位置，从那个位置开始暴力跑一遍代价即可。

询问总复杂度 $O(q\sqrt n\log_2n)$。显然可以调块长把 $\log$ 写到根号里，但本题不卡常。

## Code

```c++
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	short f=1;
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9')	{if(c=='-')	f=-1;c=getchar();}
	while(c>='0'&&c<='9')	x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return x*f;
}
typedef long long ll;
const int N=2e5+10,M=500;
int n,q,a[N],b[N],sx,sy,tx,ty;
int m,len,l[M],r[M],p[N][2],pos[N],mn[N],mx[N];
ll sum[N][2];
inline ll calc(int x,int now,int y,int &lst)//从 (x,now) 走到第 y 列的最小代价，最终横坐标为 lst
{
	ll res=0;
	for(int i=x;i<y;i=-~i)
	{
		if(now>b[i+1])	res+=now-b[i+1],now=b[i+1];
		if(now<a[i+1])	res+=a[i+1]-now,now=a[i+1];
	}
	return lst=now,res;
}
inline void pre(int u)//预处理第 u 块的信息
{
	for(int i=r[u];i>=l[u];i--)
		sum[i][0]=calc(i,a[i],r[u],p[i][0]),
		sum[i][1]=calc(i,b[i],r[u],p[i][1]);
	mn[l[u]]=b[l[u]];mx[l[u]]=a[l[u]];
	for(int i=l[u]+1;i<=r[u];i=-~i)
		mn[i]=min(b[i],mn[i-1]),mx[i]=max(a[i],mx[i-1]);
}
inline int lower(int l,int r,int x)//mn[l~r] 中第一个比 x 小的位置
{
	if(mn[r]>=x)	return r+1;
	while(l<r)
	{
		int mid=l+r>>1;
		if(mn[mid]<x)	r=mid;
		else	l=-~mid;
	}
	return l;
}
inline int upper(int l,int r,int x)//mx[l~r] 中第一个比 x 大的位置
{
	if(mx[r]<=x)	return r+1;
	while(l<r)
	{
		int mid=l+r>>1;
		if(mx[mid]>x)	r=mid;
		else	l=-~mid;
	}
	return l;
}
inline ll query()
{
	int x=pos[sx],y=pos[tx],now;
	if(x==y)	return calc(sx,sy,tx,now)+abs(now-ty);
	ll res=calc(sx,sy,r[x],now);//对于两边的散块，暴力跑代价
	for(int i=x+1,p1,p2;i<y;i=-~i)
	{
		p1=upper(l[i],r[i],now),p2=lower(l[i],r[i],now);
		if(min(p1,p2)>r[i])	continue;//如果能水平向右走到右端点
		if(p1<p2)	res+=sum[p1][0]+a[p1]-now,now=p[p1][0];
		else	res+=sum[p2][1]+now-b[p2],now=p[p2][1];
	}
	int p1=upper(l[y],tx,now),p2=lower(l[y],tx,now);//拼接终点所在散块
	if(min(p1,p2)<=tx)
	{
		if(p1<p2)	res+=a[p1]-now+calc(p1,a[p1],tx,now);
		else	res+=now-b[p2]+calc(p2,b[p2],tx,now);
	}
	return res+abs(now-ty);//加上同一列里走到终点横坐标的代价
}
signed main()
{
	n=read();len=sqrt(n*1.0);m=n/len;
	for(int i=1;i<=m;i=-~i)
		l[i]=-~r[i-1],r[i]=r[i-1]+len;
	if(n%len)	m=-~m,l[m]=r[m-1]+1,r[m]=n;
	for(int j=1;j<=m;j=-~j)
		for(int i=l[j];i<=r[j];i=-~i)
			a[i]=read(),b[i]=read(),pos[i]=j;
	for(int i=1;i<=m;i=-~i)	pre(i);
	q=read();
	while(q--)
	{
		sx=read();sy=read();tx=read();ty=read();
		if(sx>tx)	swap(sx,tx),swap(sy,ty);//默认从左往右走
		printf("%lld\n",query()+tx-sx);//别忘了加上横向代价
	}
	return 0;
}
```

---

