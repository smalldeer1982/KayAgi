# Interactive Treasure Hunt

## 题目描述

This is an interactive problem.

There is a grid of $ n\times m $ cells. Two treasure chests are buried in two different cells of the grid. Your task is to find both of them. You can make two types of operations:

- DIG $ r $ $ c $ : try to find the treasure in the cell $ (r, c) $ . The interactor will tell you if you found the treasure or not.
- SCAN $ r $ $ c $ : scan from the cell $ (r, c) $ . The result of this operation is the sum of Manhattan distances from the cell $ (r, c) $ to the cells where the treasures are hidden. Manhattan distance from a cell $ (r_1, c_1) $ to a cell $ (r_2, c_2) $ is calculated as $ |r_1 - r_2| + |c_1 - c_2| $ .

You need to find the treasures in at most 7 operations. This includes both DIG and SCAN operations in total. To solve the test you need to call DIG operation at least once in both of the cells where the treasures are hidden.

## 样例 #1

### 输入

```
1
2 3

1

1

3

0

1```

### 输出

```
SCAN 1 2

DIG 1 2

SCAN 2 2

DIG 1 1

DIG 1 3```

# 题解

## 作者：djwj223 (赞：7)

[题目链接](https://www.luogu.com.cn/problem/CF1666I)

题目大意： $n\times m$ 的网格中有两个格子有宝藏。你可以进行至多 $7$ 次操作，每次二选一：

**挖：** 返回 $0/1$ 表示是否挖到宝藏，$1$ 表示挖到了。

**扫描：** 返回当前坐标与两个宝藏点的曼哈顿距离和。

一个显然的性质：宝藏在 $(x_1,y_1),(x_2,y_2)$ 和在 $(x_2,y_1),(x_1,y_2)$ **扫描**后返回值一样。

所以我们可以假设第一个宝藏的横纵坐标都小于第二个宝藏，最后可以花三个**挖**来成功挖出宝藏。

余下 $4$ 次操作供**扫描**，可以想想怎么用四次精确找出改变要求后的宝藏位置。

显然，不会有人不把询问点放在角上，而前两次放在对角也显得很憨憨，于是我打算放在 $(1,1),(n,1)$。

我们设改变题设后的宝藏位置为 $(x_1,y_1),(x_2,y_2)$，两次返回值为 $k_1,k_2$。

$$x_1-1+y_1-1+x_2-1+y_2-1=k_1\ ,\ 2\times n-x_1+y_1-x_2+y_2-2=k_2$$
$$2\times y_1+2\times y_2+2\times n=k_1+k_2+6$$
$$y_1+y_2=\frac{k_1+k_2}{2}+3-n$$
$$2\times x_1+2\times x_2-2\times n=k_1-k_2+2$$
$$x_1+x_2=\frac{k_1-k_2}{2}+1+n$$

后两询问也很容易想到： $\left(\frac{x_1+x_2}{2},\frac{y_1+y_2}{2}\right),\left(1,\frac{y_1+y_2}{2}\right)$。

设两次返回值为 $k_3,k_4$。

$$k_3=y_2-y_1+x_2-x_1\ ,\ k_4=y_2-y_1+x_2+x_1-2$$

$$x_2+x_1-2-x_2+x_1=k_4-k_3$$

$$x_1=\frac{k_4-k_3}{2}+1$$

由此可推

$$x_2=\frac{k_1-k_2-k_4+k_3}{2}+n$$

$$y_1=\frac{\frac{k_1+k_2}{2}+3-n-k_3+x_2-x_1}{2}$$

$$y_2=\frac{\frac{k_1+k_2}{2}+k_3-x_2+x_1+3-n}{2}$$

做就完了。

---

## 作者：qzhwlzy (赞：4)

## 思路
首先，我们将问题简化成一维：在数轴上有两个点 $x_1$ 与 $x_2$（不妨设 $1\le x_1<x_2\le n$），通过询问任意的 $x$ 点到两点的曼哈顿距离纸之和，找出这两个点。

假设我们询问点 $x$，其到两点的曼哈顿距离之和应为 $y = |x-x_1|+|x-x_2|$，~~通过画图~~，我们可以知道，$y$ 关于 $x$ 的函数表达式应为 $y = |x-x_1|+|x-x_2| = \begin{cases}-2x+(x_1+x_2)&x<x_1\\x_2-x_1&x_1\le x\le x_2\\2x-(x_1+x_2)&x>x_2\end{cases}$。证明如下：

------------
1. 若 $x<x_1<x_2$，则 $x-x_1<0,x-x_2<0$，故 $y=(x_1-x)+(x_2-x)=-2x+(x_1+x_2)$
2. 若 $x_1\le x\le x_2$，则 $x-x_1\ge 0,x-x_2\le 0$，故 $y=(x-x_1)+(x_2-x)=x_2-x_1$
3. 若 $x_1<x_2<x$，则 $x-x_1>0,x-x_2>0$，故 $y=(x-x_1)+(x-x_2)=2x-(x_1+x_2)$

整理可得上述函数。（下图绿色虚线为求出的函数，红色为模拟描点得到的函数，可看出两者重合）

![](https://cdn.luogu.com.cn/upload/image_hosting/upjt0b27.png)

可以这样理解：在数轴上，两点之间的点到这两点的曼哈顿距离之和就是两点间的距离 $(x_2-x_1)$。在 $x_1$ 左侧时每左移一个单位，距离多 $2$，右侧时每右移一个单位距离也多 $2$。

------------
也就是说，在 $\left[x_1,x_2\right]$ 范围内，点到 $x_1,x_2$ 两点的曼哈顿距离之和为定值，之外每远离一个单位曼哈顿距离之和距离之和增加 $2$（性质 $1$）。同时，我们还可以知道，图像关于直线 $x=\dfrac{x_1+x_2}{2}$ 对称，所以我们知道若两不同点 $a,b$ 到两端点的曼哈顿距离之和相等，则 $\dfrac{a+b}{2}$ 一定在“平底”上（性质 $2$）。

结合图像的性质，我们可以着手解决问题。我们可以求出函数“平底”的一段来看出两点的位置（“平底”段的两端点就是所求两点横坐标）。我们发现可以选两个点，求出一个一定在范围内的点，询问后就可以解出答案。详细步骤及证明如下：

- 首先我们可以对 $1,n$ 两端点进行询问，记返回值分别为 $f(1),f(n)$。假设 $f(1)>f(n)$，那么根据性质 $1$ 一定有 $f(1+\dfrac{f(1)-f(n)}{2})=f(n)$（由性质 $1$，点 $1$ 向右一个单位距离减 $2$，想要达到和 $f(n)$ 相同时距离应减小 $f(1)-f(n)$，也就是从 $1$ 开始向右 $\dfrac{f(1)-f(n)}{2}$ 单位），再根据性质 $2$ 有 $(\dfrac{(1+\frac{f(1)-f(n)}{2})+n}{2})$ 一定在“平底”上。  
- 再对这个点进行询问，我们可以得到一个值，记为 $f(mid)$，所以有 $f(x_1)=f(mid)$，故再使用性质 $1$，我们得到 $x_1=1+\dfrac{f(1)-f(mid)}{2}$。同理我们可以得到 $f(x_2)=f(mid)$，$x_2=n-\dfrac{f(n)-f(mid)}{2}$。
- 而当 $f(1)<f(n)$ 时，同理可以得到 $mid = \dfrac{1+(n-\frac{f(n)-f(1)}{2})}{2}$，也有 $x_1=1+\dfrac{f(1)-f(mid)}{2},x_2=n-\dfrac{f(n)-f(mid)}{2}$。
- 在 $f(1)=f(n)$ 时，上述两种情况都适用，有 $mid=\dfrac{1+n}{2}$，$x_1=1+\dfrac{f(1)-f(mid)}{2},x_2=n-\dfrac{f(n)-f(mid)}{2}$。

这样，我们就完成了一维版本，最少需要 $3$ 次 SCAN 操作。

------------
我们再将结论推广到二维。
同样地，我们可以推出，在以目标点 $(x_1,y_1),(x_2,y_2)$ 之间的直线为对角线的矩形中，点到两点的曼哈顿距离之和为定值，如图中浅红色的点（红色的为目标点）。其它点每离这个矩形水平方向或竖直方向上远一格距离之和都会加 $2$。证明即在横纵方向上各用一次一维的结论即可。

![](https://cdn.luogu.com.cn/upload/image_hosting/w4allkl8.png)

所以，我们不妨关注一下第一列（图中浅蓝色部分）（其实哪一列应该都可以，为了下面计算方便可以选第一列）。这一列中，每个点到两个曼哈顿距离之和可以看成是 竖直方向上点到目标点在第一列上投影的点（即 $(x_1,1),(x_2,1)$）的曼哈顿距离和（图中橙色部分） 加上 水平方向上的 $|y_1-1|+|y_2-1|$（图中亮橙色部分，为定值）。那么，既然如此，我们抛开水平方向上的定值不看，真正决定距离和大小的其实就是竖直方向上的这两段。我们仔细看就能发现，竖直方向上的这两段就可以看作是刚才的一维的问题，于是，我们可以用刚才一样的方法求得 $x_1$ 及 $x_2$（可以这么求的前提是 $|y_1-1|+|y_2-1|$ 这一定值不会对结果有影响，上述式子中我们的 $f(1),f(mid),f(n)$ 都是通过相减推出其它量的，所以没有影响）。也就是说，我们将目标点限制在了两条直线上，需要 $3$ 次操作。

![](https://cdn.luogu.com.cn/upload/image_hosting/3yowstih.png)

同理，我们在第一行也按上述方法能够求出 $y_1,y_2$，也就是说，我们得到了两组点 $(x_1,y_1),(x_2,y_2)$ 和 $(x_1,y_2),(x_2,y_1)$，需要 $3$ 次操作。答案只能是其中一组（显然答案不可能是 $(x_1,y_1),(x_2,y_1)$ 这类的），于是我们要 DIG 一组中的一点，若是则另一个答案即为这一组的另一点；若不是则答案即为另一组的两个点，也就是说，要 $3$ 次才能挖出所有点。

计算一下，目前我们一共用了 $3+3+3 = 9$ 次操作，除去重复的 SCAN $1\ 1$（第一列和第一行求解时都要用到）也要 $8$ 次，比题中要求的 $7$ 次多一次，所以，我们想如何减少一次操作。

如下图，观察 $(n,1),(1,m)$ 到两目标点的曼哈顿距离，我们发现，水平方向上两段加起来正好是 $2(m-1)$ 而竖直方向上恰好是 $2(n-1)$，所以有 $f_{(n,1)}+f_{(1,m)}=2(n+m-2)$，所以我们 SCAN 其中的一个就能算出另一个。这时，我们刚好将操作次数减到了 $7$ 次。

![](https://cdn.luogu.com.cn/upload/image_hosting/6qn7r5tv.png)

### 代码
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int T,n,m;
int lt,ld,lm,rt,mt;
int anst,ansd,ansl,ansr;
int opt;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		//对第一列计算
		printf("SCAN 1 1\n");fflush(stdout);scanf("%d",&lt);
		printf("SCAN %d 1\n",n);fflush(stdout);scanf("%d",&ld);
		if(lt>ld) {printf("SCAN %d 1\n",(n+(1+(lt-ld)/2))/2);fflush(stdout);scanf("%d",&lm);}
		else {printf("SCAN %d 1\n",(1+(n-(ld-lt)/2))/2);fflush(stdout);scanf("%d",&lm);}
		anst=1+(lt-lm)/2;ansd=n-(ld-lm)/2;//两目标点的横坐标
		rt=(2*(n+m-2)-ld);//算左上角点
		//对第一行计算
		if(lt>rt) {printf("SCAN 1 %d\n",(m+(1+(lt-rt)/2))/2);fflush(stdout);scanf("%d",&mt);}
		else {printf("SCAN 1 %d\n",(1+(m-(rt-lt)/2))/2);fflush(stdout);scanf("%d",&mt);}
		ansl=1+(lt-mt)/2;ansr=m-(rt-mt)/2;//两目标点的纵坐标
		printf("DIG %d %d\n",anst,ansl);fflush(stdout);scanf("%d",&opt);//挖答案
		if(opt) {printf("DIG %d %d\n",ansd,ansr);fflush(stdout);scanf("%d",&opt);}
		else {printf("DIG %d %d\n",anst,ansr);fflush(stdout);scanf("%d",&opt);
		printf("DIG %d %d\n",ansd,ansl);fflush(stdout);scanf("%d",&opt);}
	}
	return 0;
}
```

---

## 作者：lingfunny (赞：2)

私以为其它题解并没有展现这道题的合理的思路，有的开始就讲一维，有的甚至是从 DIG 操作解题的。写一个自认为合理顺畅的想法。

2022年6月24日。

最基础的，一次询问可以得到一个方程，理想情况下得到 $4$ 个方程就可以解出答案，最后挖两次总和 $6$ 次。

如果在中间问，根本无法判断结果的式子是什么样的，即拆不了绝对值，所以不难想到问四个角。然后发现左上和右下的式子是一样的，右上和左下也是一样的，于是考虑问分别各问一个，目前花费 $2$。

- 左上/右下：$x_1+y_1+x_2+y_2=a$，由 $\left | n-x_1\right|+\left|n-x_2\right|+\left|m-y_1\right|+\left|m-y_2\right|$ 变形而来，绝对值相信大家都会拆。
- 右上/左下：$x_1-y_1+x_2-y_2=b$，由 $\left | x_1-1 \right|+\left|m-y_1\right|+\left|x_2-1\right|+\left|m-y_2\right|$ 变形而来，绝对值相信大家都会拆。

不难得到 $x_1+x_2$ 和 $y_1+y_2$ 的值，问题就是无法区分出 $x_1,x_2$。

看一下式子的本质：如果询问的位置在两点同侧，就只能得到 $x_1+x_2$ 的值。想要区分出来，只能问夹在两点中间的点，所以想到查中点是非常合理顺畅的事情。

但不能一次询问查两个中点，因为这样的结果是 $\left|x_1-x_2\right|+\left|y_1-y_2\right|=p$，根本解不了方程（当然你可以再问一次得到 $\left|x_1-x_2\right|=q$，但没必要）。

考虑查 $(\frac{x_1+x_2}{2},1)$，这样可以得到 $\left|x_1-x_2\right|=k-(y_1+y_2)$。通过这个绝对值可以解出两个 $x$ 的值，但不知道这两个 $x$ 的对应情况。$y$ 同理。

但到这里，只用了四次询问，加上两次挖，也就六次，还能再问一次。还有另一点非常重要，你并不需要知道谁是第一个点和第二个点，只需要挖出这两点。换句话说，你并不关心两点的顺序。

不妨设解出来的四个数分别为 $X,x,Y,y$，且 $X>x, Y>y$，会发现**无序的**两个**有序点对**只有两种（点对之间是无序的，点对内部是有序的）：

1. $(X, Y),(x, y)$
2. $(X, y),(x, Y)$

于是引出了正解：我们不妨试错一下 $(X, Y)$，如果这个点没有宝藏，说明答案一定是 $(X, y), (x, Y)$，否则另一个点是 $(x, y)$。

刚好六到七次。

---

## 作者：_O_v_O_ (赞：1)

[双倍经验](/problem/P12822)。

不懂 $n,m$ 为啥才 $16$。似乎是拿来诈骗 $2^4=16$ 从而想到二分的人。

注意到要挖两次答案，而两个点是轮换对称的，所以还要挖一次，那么只剩 $4$ 次。

我们不妨令 $x_1\le x_2,y_1\le y_2$

为了消除掉绝对值的影响，先用 SCAN 询问 $(1,1),(1,m)$，设答案为 $a,b$。

那么就能得出一组方程：

$$\begin{cases}x_1-1+y_1-1+x_2-1+y_2-1=a \\ x_1-1+m-y_1+x_2-1+m-y_2=b\end{cases}$$

化简可得：

$$\begin{cases}x_1+y_1+x_2+y_2=a+4 \\ x_1-y_1+x_2-y_2=b+2-2\times m\end{cases}$$

那么能算出 $x_1+x_2=\frac{a+b+6-2\times m}2=\frac{a+b}2+3-m,y_1+y_2=\frac{a-b+2+2\times m}2=\frac{a-b}2+1+m$。

继续消除绝对值的影响，询问外面是不现实的，那么我们不妨询问里面，不妨询问 $(1,\frac{y_1+y_2}2),(\frac{x_1+x_2}2,1)$，设答案为 $c,d$。

那么就有：

$$\begin{cases}x_1-1+x_2-1+|y_1-y_2|=c \\ y_1-1+y_2-1+|x_1-x_2|=d\end{cases}$$

由于我们先前令 $x_1\le x_2,y_1\le y_2$，那么就能得出 $x_1+x_2,x_2-x_1$，容易解出 $x_1,x_2$，同理可以解出 $y_1,y_2$。

code：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define y1 qwqawa
#define y2 awaqwq

int n,m;

signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int T;cin>>T;while(T--){
		cin>>n>>m;
		cout<<"SCAN "<<1<<' '<<1<<endl;
		int a;cin>>a;
		cout<<"SCAN "<<1<<' '<<m<<endl;
		int b;cin>>b;
		int sumx=(a+b)/2+3-m;
		int sumy=(a-b)/2+1+m;
		cout<<"SCAN "<<1<<' '<<sumy/2<<endl;
		int c;cin>>c;c+=2,c-=sumx;
		cout<<"SCAN "<<sumx/2<<' '<<1<<endl;
		int d;cin>>d;d+=2,d-=sumy;
		int x1=(d+sumx)/2,x2=sumx-x1;
		int y1=(c+sumy)/2,y2=sumy-y1;
		cout<<"DIG "<<x1<<' '<<y1<<endl;
		int nailong;cin>>nailong;
		if(nailong){
			cout<<"DIG "<<x2<<' '<<y2<<endl;
			cin>>nailong;
		}
		else{
			cout<<"DIG "<<x1<<' '<<y2<<endl;
			cin>>nailong;
			cout<<"DIG "<<x2<<' '<<y1<<endl;
			cin>>nailong;
		}
	}
	return 0;
}
```

---

## 作者：LXcjh4998 (赞：1)

[Luogu 链接](https://www.luogu.com.cn/problem/CF1666I)

[Codeforces 链接](https://codeforces.com/problemset/problem/1666/I)
# 题意
**本题为 IO 交互题，请注意刷新缓冲区。**

---
> ### 题目描述
> 有一个 $n\times m$（$1\le n,m\le 16$）的网格，其中有两个不同的格子有宝藏，你可以进行以下两种操作：
> 
> - $\texttt{DIG}\ r\ c$：交互器将告诉你格子 $(r,c)$ 里是否有宝藏。
> - $\texttt{SCAN}\ r\ c$：交互器将告诉你格子 $(r,c)$ 到两个宝藏所在格子的曼哈顿距离之和。
> 
> **你最多只能执行这些操作共 $7$ 次，并且对于每个宝藏的位置你需要至少 $\texttt{DIG}$ 一次**。
>
> 多测，组数 $T\le 100$。
# 思路
我们设第一个宝藏的坐标为 $(x_1,y_1)$，第二个宝藏的坐标为 $(x_2,y_2)$，并且 $x_1\le x_2$。

显然，有四个未知数，所以我们至少要 $\texttt{SCAN}$ 四次才能得出 $x_1,x_2,y_1,y_2$ 的值。

但是 $y_1$ 和 $y_2$ 的值是可以交换的，所以我们先要 $\texttt{DIG}\ x_1\ y_1$，若返回值为 $1$，则继续 $\texttt{DIG}\ x_2\ y_2$；否则 $\texttt{DIG}\ x_1\ y_2$ 和 $\texttt{DIG}\ x_2\ y_1$。

因此，我们至多只需要 $7$ 次操作就可以找到两个宝藏的位置可以通过此题。

接下来，我们继续讨论如何求出 $x_1,x_2,y_1,y_2$ 的值：

> - 第一步：令 $s_1=\texttt{SCAN}\ 1\ 1$，则有 $(x_1+x_2)+(y_1+y_2)=s_1+4$。
> - 第二步：令 $s_2=\texttt{SCAN}\ 1\ m$，则有 $(x_1+x_2)-(y_1+y_2)=s_2-2m+2$。
> 
> 通过前两步，我们可以计算出 $\displaystyle sum_x=x_1+x_2=\frac{s_1+s_2-2m+6}{2}$ 和 $\displaystyle sum_y=y_1+y_2=\frac{s_1-s_2+2m+2}{2}$。
>
> 而要算出 $delta_x=x_2-x_1$ 和 $delta_y=\lvert y_1-y_2\rvert$，我们可以进行如下操作：
>
> - 第三步：令 $\displaystyle s_3=\texttt{SCAN}\ \lfloor\frac{sum_x}{2}\rfloor\ 1$，则有 $(x_2-x_1)+(y_1+y_2)=s_3+2$。
> - 第四步：令 $\displaystyle s_4=\texttt{SCAN}\ 1\ \lfloor\frac{sum_y}{2}\rfloor$，则有 $(x_1+x_2)+\lvert y_1-y_2\rvert=s_4+2$。
> 
> 通过上述两步，我们可以计算出 $delta_x=s_3+2-sum_y,delta_y=s_4+2-sum_x$。
>
> 计算出 $sum_x,sum_y,delta_x,delta_y$ 后，我们利用~~小学~~数学知识就可以计算出 $x_1,x_2,y_1,y_2$ 了，此处不再赘述。
# 代码
[AC 记录](https://codeforces.com/contest/1666/submission/309720651)
```cpp
#include<cstdlib>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<queue>
#include<cstdio>
#include<iostream>
#include<vector>
#include<map>
#include<cmath>
#include<iomanip>
#include<string>
#include<stack>
#include<random>
#include<utility>
#define re register
#define ll long long
#define ull unsigned long long
#define vl __int128
#define ld long double
#define LL 2e18
#define INT 1e9
#define INF 0x3f3f3f3f
#define MP make_pair
#define pb push_back
#define lb(x) (x&(-x))
#ifdef __linux__
#define gc getchar_unlocked
#define pc putchar_unlocked
#else
#define gc _getchar_nolock
#define pc _putchar_nolock
#endif
int T=1;
using namespace std;
pair<int*,int*> pair_int;pair<ll*,ll*> pair_ll;pair<ull*,ull*> pair_ull;pair<double*,double*> pair_double;pair<ld*,ld*> pair_ld;pair<char*,char*> pair_char;pair<bool*,bool*> pair_bool;
inline bool blank(const char x){return !(x^32)||!(x^10)||!(x^13)||!(x^9);}
template<typename Tp>inline void read(Tp &x){x=0;bool z=true;char a=gc();for(;!isdigit(a);a=gc())if(a=='-')z=false;for(;isdigit(a);a=gc())x=(x<<1)+(x<<3)+(a^48);x=(z?x:~x+1);}
inline void read(double &x){x=0.0;bool z=true;double y=0.1;char a=gc();for(;!isdigit(a);a=gc())if(a=='-')z=false;for(;isdigit(a);a=gc())x=x*10+(a^48);if(a!='.')return x=z?x:-x,void();for(a=gc();isdigit(a);a=gc(),y/=10)x+=y*(a^48);x=(z?x:-x);}
inline void read(ld &x){x=0.0;bool z=true;ld y=0.1;char a=gc();for(;!isdigit(a);a=gc())if(a=='-')z=false;for(;isdigit(a);a=gc())x=x*10+(a^48);if(a!='.')return x=z?x:-x,void();for(a=gc();isdigit(a);a=gc(),y/=10)x+=y*(a^48);x=(z?x:-x);}
inline void read(char &x){for(x=gc();blank(x)&&(x^-1);x=gc());}
inline void read(char *x){char a=gc();for(;blank(a)&&(a^-1);a=gc());for(;!blank(a)&&(a^-1);a=gc())*x++=a;*x=0;}
inline void read(string &x){x="";char a=gc();for(;blank(a)&&(a^-1);a=gc());for(;!blank(a)&&(a^-1);a=gc())x+=a;}
template<typename T>inline void read(pair<T*,T*> p){T *begin,*end,*i;begin=p.first,end=p.second;if(begin<end)for(i=begin;i<end;++i)read(*i);else for(i=begin-1;i>=end;--i)read(*i);}
template<typename T,typename ...Tp>inline void read(T &x,Tp &...y){read(x),read(y...);}
template<typename Tp>inline void write(Tp x){if(!x)return pc(48),void();if(x<0)pc('-'),x=~x+1;int len=0;char tmp[64];for(;x;x/=10)tmp[++len]=x%10+48;while(len)pc(tmp[len--]);}
inline void write(const double x){int a=6;double b=x,c=b;if(b<0)pc('-'),b=-b,c=-c;double y=5*powl(10,-a-1);b+=y,c+=y;int len=0;char tmp[64];if(b<1)pc(48);else for(;b>=1;b/=10)tmp[++len]=floor(b)-floor(b/10)*10+48;while(len)pc(tmp[len--]);pc('.');for(c*=10;a;a--,c*=10)pc(floor(c)-floor(c/10)*10+48);}
inline void write(const ld x){int a=6;ld b=x,c=b;if(b<0)pc('-'),b=-b,c=-c;ld y=5*powl(10,-a-1);b+=y,c+=y;int len=0;char tmp[64];if(b<1)pc(48);else for(;b>=1;b/=10)tmp[++len]=floor(b)-floor(b/10)*10+48;while(len)pc(tmp[len--]);pc('.');for(c*=10;a;a--,c*=10)pc(floor(c)-floor(c/10)*10+48);}
inline void write(const pair<int,double>x){int a=x.first;if(a<7){double b=x.second,c=b;if(b<0)pc('-'),b=-b,c=-c;double y=5*powl(10,-a-1);b+=y,c+=y;int len=0;char tmp[64];if(b<1)pc(48);else for(;b>=1;b/=10)tmp[++len]=floor(b)-floor(b/10)*10+48;while(len)pc(tmp[len--]);a&&(pc('.'));for(c*=10;a;a--,c*=10)pc(floor(c)-floor(c/10)*10+48);}else printf("%.*lf",a,x.second);}
inline void write(const pair<int,ld>x){int a=x.first;if(a<7){ld b=x.second,c=b;if(b<0)pc('-'),b=-b,c=-c;ld y=5*powl(10,-a-1);b+=y,c+=y;int len=0;char tmp[64];if(b<1)pc(48);else for(;b>=1;b/=10)tmp[++len]=floor(b)-floor(b/10)*10+48;while(len)pc(tmp[len--]);a&&(pc('.'));for(c*=10;a;a--,c*=10)pc(floor(c)-floor(c/10)*10+48);}else printf("%.*Lf",a,x.second);}
inline void write(const char x){pc(x);}
inline void write(const bool x){pc(x?49:48);}
inline void write(char *x){fputs(x,stdout);}
inline void write(const char *x){fputs(x,stdout);}
inline void write(const string &x){fputs(x.c_str(),stdout);}
template<typename T>inline void write(pair<T*,T*> p){T *begin,*end,*i;begin=p.first,end=p.second;for(i=begin;i<end;++i)write(*i),write(' ');}
template<typename T>inline void write(pair<pair<T*,T*>,char> p){T *begin,*end,*i;begin=p.first.first,end=p.first.second;char c=p.second;for(i=begin;i<end;++i)write(*i),write(c);}
template<typename T,typename ...Tp> inline void write(T x,Tp ...y){write(x),write(y...);}
template<typename T>inline void init(T *begin,T *end,const T& val=T()){T* i;for(i=begin;i<end;++i)*i=val;}
template<typename T>inline T max(T *begin,T *end){T *ans,*i;for(i=begin;i<end;++i)if(i==begin||*ans<*i)ans=i;return *ans;}
template<typename T>inline T min(T *begin,T *end){T *ans,*i;for(i=begin;i<end;++i)if(i==begin||*i<*ans)ans=i;return *ans;}
template<typename T>inline T calc_sum(T *begin,T *end,const T& val=T()){T ans=val,*i;for(i=begin;i<end;++i)ans+=*i;return ans;}
template<typename T>inline bool is_equal(T *begin,T *end,const T& val=T()){T *i;for(i=begin;i<end;++i)if(*i!=val)return false;return true;}
template<typename T>inline T qp(T x,T y){T ans=1;while(y){if(y&1)ans=ans*x;x=x*x;y>>=1;}return ans;}
template<typename T>inline T qp(T x,T y,T z){T ans=1;while(y){if(y&1)ans=ans*x%z;x=x*x%z;y>>=1;}return ans;}

ll mod=0;
const int MAXN=0;
const int N=MAXN+10;
//#define DEBUG
//#define more_text

int t,n,m;

int s1,s2,s3,s4,sx,sy,dx,dy,ans;

void SOLVE(int _){
	cin>>t;
	while(t--){
		cin>>n>>m;
		
		cout<<"SCAN 1 1"<<endl;cin>>s1;
		cout<<"SCAN 1 "<<m<<endl;cin>>s2;
		sx=(s1+s2-2*m+6)/2,sy=(s1-s2+2*m+2)/2;
		
		cout<<"SCAN "<<sx/2<<" 1"<<endl;cin>>s3;
		cout<<"SCAN 1 "<<sy/2<<endl;cin>>s4;
		dx=s3+2-sy,dy=s4+2-sx;
		
		cout<<"DIG "<<(sx-dx)/2<<" "<<(sy-dy)/2<<endl;cin>>ans;
		if(ans==1)cout<<"DIG "<<(sx+dx)/2<<" "<<(sy+dy)/2<<endl,cin>>ans;
		else{
			cout<<"DIG "<<(sx-dx)/2<<" "<<(sy+dy)/2<<endl;cin>>ans;
			cout<<"DIG "<<(sx+dx)/2<<" "<<(sy-dy)/2<<endl;cin>>ans;
		}
	}
}
/*
Input:

Output:

Outline:

*/
int main(){
	#ifdef DEBUG
	freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);
	#endif
	#ifdef more_text
	read(T);
	#endif 
	for(int i=1;i<=T;++i)SOLVE(i);
	#ifdef DEBUG
	fclose(stdin);fclose(stdout);
	#endif
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

# CF1666I 题解



## 思路分析

注意到对于第一次询问 `SCAN r c`，由于我们不知道 $r,r_1,r_2$ 和 $c,c_1,c_2$ 之间的大小关系，因此这个东西不太好入手，考虑如何去掉绝对值。

注意到在 $(r,c)$ 为矩形的四个角的时候，我们能同时拆掉两个绝对值，因此从四个角入手。

执行这四个查询操作能够得到的对 $(r_1,r_2,c_1,c_2)$ 的限制方程，我们能够联想到通过解方程组来证明这样的 $(r_1,r_2,c_1,c_2)$ 是唯一的。

我们可以得到联立这四个方程得到的方程组对应的行列式应该形如下面的形式：
$$
\begin{bmatrix}
r_1\\
r_2\\
c_1\\
c_2
\end{bmatrix}
\times
\begin{bmatrix}
1&1&1&1\\
1&1&-1&-1\\
-1&-1&1&1\\
-1&-1&-1&-1
\end{bmatrix}
=
\begin{bmatrix}
v_1\\
v_2\\
v_3\\
v_4
\end{bmatrix}
$$
不过我们发现这样询问四个角的做法是错误的，原因是系数矩阵中有线性相关的行向量，因此我们需要重新选取恰当的四个询问点。

注意到询问左上角和右上角得到的两个向量是线性无关的，因此保留询问左上角和右上角的过程可以保留下来。

设询问左上角得到回答 $v_1$，询问右上角得到回答 $v_2$ 得到的方程组应该为：
$$
\begin{cases}
(r_1+r_2)+(c_1+c_2)&=v_1+4\\
(r_1+r_2)-(c_1+c_2)&=v_2-2m+2
\end{cases}
$$
那么我们把 $r_1+r_2$ 和 $c_1+c_2$ 看成两个整体，我们能够解得这两个整体的值。

此时我们还剩下两个向量没确定，显然在剩下的两个方程中，$r_1,r_2$ 系数不同和 $c_1,c_2$ 系数不同至少有一个要成立。

假设 $r_1,r_2$ 系数不同那么我们询问的列 $r$ 应该满足 $\min(r_1,r_2)\le r\le \max(r_1,r_2)$，我们发现 $\left\lfloor\dfrac{r_1+r_2}2\right\rfloor$ 恰好满足条件，我们在这一行中任取一列询问即可得到第三个方程。

类似计算第三个方程的过程，我们在第 $\left\lfloor\dfrac{c_1+c_2}2\right\rfloor$ 列中任取一行询问可以得到第四个方程。

最后，我们联立这四个方程能够解出 $r_1,r_2,c_1,c_2$，由于 $n$ 和 $m$ 很小，暴力枚举也可以通过。

不过注意到我们实际上不能得到 $r_1,r_2$ 之间和 $c_1,c_2$ 之间的实际大小关系，这意味着我们将无法分辨 $\{(r_1,c_1),(r_2,c_2)\}$ 和 $\{(r_1,c_2),(r_2,c_1)\}$ 中哪一个点对才是真正的答案。

不过我们注意到目前只用了 $4$ 次操作，除去提交答案的 $2$ 次操作还剩 $1$ 次操作，因此可以先操作 `DIG r1 c1`，通过返回的结果是 $1$ 还是 $0$ 分辨到底是哪两个点对，总的操作次数在 $6$ 和 $7$ 之间。

时间复杂度 $\Theta(n^2m^2)$。

## 代码呈现

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(int r,int c) {
	cout<<"SCAN "<<r<<" "<<c<<endl;
	int ret; cin>>ret; return ret; 
}
inline bool chk(int x,int y,int r1,int c1,int r2,int c2,int d) {
	return abs(x-r1)+abs(x-r2)+abs(y-c1)+abs(y-c2)==d;
}
inline void solve() {
	int n,m;
	cin>>n>>m;
	vector <int> r(4),c(4),v(4);
	v[0]=read(r[0]=1,c[0]=1);
	v[1]=read(r[1]=1,c[1]=m);
	int sr=((v[0]+4)+(v[1]+2-2*m))/2;
	int sc=((v[0]+4)-(v[1]+2-2*m))/2;
	v[2]=read(r[2]=1,c[2]=sc/2);
	v[3]=read(r[3]=sr/2,c[3]=1);
	for(int r1=1;r1<=n;++r1) for(int c1=1;c1<=m;++c1) {
		for(int r2=1;r2<=n;++r2) for(int c2=1;c2<=m;++c2)  {
			bool ok=true;
			for(int k:{0,1,2,3}) {
				if(!chk(r[k],c[k],r1,c1,r2,c2,v[k])) {
					ok=false;
					break;
				}
			}
			if(ok) {
				int s;
				cout<<"DIG "<<r1<<" "<<c1<<endl; cin>>s;
				if(s==1) {
					cout<<"DIG "<<r2<<" "<<c2<<endl; cin>>s;
				} else {
					cout<<"DIG "<<r1<<" "<<c2<<endl; cin>>s;
					cout<<"DIG "<<r2<<" "<<c1<<endl; cin>>s;
				}
				return ;
			}
		}
	}
}
signed main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```



---

## 作者：hyman00 (赞：0)

# CF1666I

首先，设坐标分别为 $(x_1,y_1),(x_2,y_2)$。

发现任何 SCAN 操作都不能区分 $(x_1,y_1),(x_2,y_2)$ 和 $(x_1,y_2),(x_2,y_1)$，就需要额外的一次 DIG。

还要两次 DIG 求答案，所以有 4 次~~有用~~的操作，关键还有 4 个未知数。

先上操作的代码。

```c++
int q1(int x,int y){
	cout<<"SCAN "<<x<<" "<<y<<"\n";
	cout.flush();
	re read();
}
int q2(int x,int y){
	cout<<"DIG "<<x<<" "<<y<<"\n";
	cout.flush();
	re read();
}
```

发现：

$$
q1(1,1)=x_1+x_2+y_1+y_2-4
$$
$$
q1(1,m)=x_1+x_2-y_1-y_2+2m-2
$$
就可以算出 $X=x_1+x_2$ 和 $Y=y_1+y_2$。

再进行 
$$
q1\left(1,\left\lfloor\frac Y2\right\rfloor\right),q1\left(\left\lfloor\frac X2\right\rfloor,1\right)
$$
即可。

```c++
	int a=q1(1,1),b=q1(1,m),x=(a+b-2*m+6)/2,y=a+4-x,xdif=q1(x/2,1)-y+2,ydif=q1(1,y/2)-x+2;
	int x1=(x+xdif)/2,x2=(x-xdif)/2,y1=(y+ydif)/2,y2=(y-ydif)/2;
	if(q2(x1,y1))q2(x2,y2);
	else q2(x1,y2),q2(x2,y1);
```

---

