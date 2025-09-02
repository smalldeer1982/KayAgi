# 【MX-X12-T7+】「ALFR Round 5」地铁（Hard Version）

## 题目背景

原题链接：<https://oier.team/problems/X12H>。

---

**本题与 Easy Version 的区别在于数据范围和时间限制不同，且本题需要输出构造方案。**

## 题目描述

为了方便市民出行，缓解地面上的道路拥堵问题，S 市决定在地底下建一些地铁。

根据城市规划，S 市的地下网络将由 $n$ 条横向通道和 $m$ 条纵向通道构成。地铁站将设置在所有横向通道与纵向通道的交叉处，共 $n\times m$ 处。

地下网络的所有站点都需要被地铁线路覆盖，地铁线路之间可以有重叠部分。

每一条地铁线路都不应「绕路」。如果一条地铁线路，在从其中一个起点站开到终点站的过程中，存在两段列车朝相反方向行驶的平行道路，则我们称这条地铁线路是「绕路」的。

在下图所示的地下网络中，灰线代表地下通道（深灰色的格子为地铁站，即道路交叉处）。红、绿、蓝线所代表的地铁线路没有「绕路」，而黄、橙、紫线所代表的地铁线路「绕路」了。

![](https://cdn.luogu.com.cn/upload/image_hosting/kyzwyen0.png)

此外，地铁线路网必须是连通的。也就是说，无论从哪个地铁站出发乘坐地铁，经过若干次换乘（可以不换乘），都一定可以到达其它所有地铁站。

因为盾构一条地铁线路的流程十分麻烦，S 市不想要建造太多的地铁线路。现在，你知道了 S 市的地下网络大小为 $n\times m$，请你求出 S 市最少要建几条地铁线路，并给出一个方案。如果你求出的数不是最少需要的地铁线路数量，也可以获得一部分分数。**具体评分标准请参照题目最后面。**

## 说明/提示

**【样例解释】**

第一组数据的构造方案如下图。要覆盖所有深灰色的交叉路口，至少需要四条地铁线路。

![](https://cdn.luogu.com.cn/upload/image_hosting/ed95ib4j.png?x-oss-process=image/resize,m_lfit,h_450,w_600)

第二组数据的构造方案如下图。要覆盖所有深灰色的交叉路口，至少需要六条地铁线路。

![](https://cdn.luogu.com.cn/upload/image_hosting/h9xxiqum.png?x-oss-process=image/resize,m_lfit,h_680,w_900)

**【数据范围】**

**具体评分标准请参照题目最后面。**

对于 $100\%$ 的数据，$1\le T\le10$，$1\le n,m\le10^3$，$nm>1$。

|子任务|测试点个数|总分|特殊性质|
|:-:|:-:|:-:|:-:|
|$1$|$5$|$10$|$n,m\le10$|
|$2$|$5$|$5$|$m\ge n^2$|
|$3$|$5$|$15$|$n=m$|
|$4$|$6$|$30$|$n\le10$|
|$5$|$10$|$40$|无|

其中 Subtask 5 保证第 $k(k\in[1,10])$ 个测试点满足 $\max(\frac n m,\frac m n)\in[arr_{k-1},arr_{k})$，$arr$ 的值如下：

| $x$ | $0$ | $1$ | $2$ | $3$ | $4$ | $5$ | $6$ | $7$ | $8$ | $9$ | $10$ |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| $arr_x$ | $1$ | $\frac{11}{10}$ | $\frac{6}{5}$ | $\frac{4}{3}$ | $\frac{3}{2}$ | $\frac{5}{3}$ | $2$ | $3$ | $5$ | $10$ | $1000$ |

**【评分标准】**

**每个子任务得分为该子任务各个测试点得分向下取整之和。每个测试点得分为该测试点每组测试数据得分的平均值。**

每组测试数据评分标准如下：

- 如果程序未按格式要求输出或输出不符合题意，将获得 $0\%$ 的分数。一个测试点中，只要有一个测试数据因此获得 $0\%$ 的分数，则整个测试点都不会得分。
  - 未按格式要求输出的例子：没有另外输出 $ans$ 行，$s$ 的长度不为 $l$ 等。
  - 输出不符合题意的例子：有地铁线路「绕路」或超出 $n\times m$ 的范围了，所有地铁线路并没有连通，有路口没有被任何线路经过等。
- 否则，若程序在本测试数据输出了一个答案 $ans$ 并正确构造出了一个对应的方案，设 $X=\min(n,m)+1$，$A$ 为该测试数据的正确答案，即最少需要的地铁线路数量，则将会获得 $\lfloor-\frac{100}{X-A}ans+\frac{100X}{X-A}\rfloor\%$ 的分数。除去下取整，这是一个经过 $(A,100\%)$ 和 $(X,0\%)$ 的一次函数。

## 样例 #1

### 输入

```
2
5 7
9 8```

### 输出

```
4
1 1 10 RRRDDDDRRR
5 7 10 UULLLLLLUU
5 1 10 URUURRRURR
1 7 10 DLDDLLLDLL
6
1 1 15 RRRDDRRRDDDDRDD
1 1 14 DDRRDDRRRDDDRD
5 1 11 RDDDRRRDRRR
7 1 12 RRURUURRUURR
9 1 15 RRRUURURRRUUUUU
9 1 15 UUUUURUURRRURRR```

# 题解

## 作者：cff_0102 (赞：30)

$x,y$ 保持 Easy Version 的定义（左上到右下、左下到右上的地铁线路数量）。

关于 $ans$ 如何计算，由于 Hard Version 的数据范围更小，所以也可以直接枚举 $x$ 和 $y$，不会超时。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
bool check(int x,int y){
	return x*y>=(x+y)*(x+y)-(x+y)*(n+m)+n*m;
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int t;cin>>t;
	while(t--){
		cin>>n>>m;
		int ans=1e9;
		for(int x=0;x<=min(n,m)/2+1;x++){
			for(int y=0;y<=min(n,m)/2+1;y++){
				if(check(x,y))ans=min(ans,x+y);
			}
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

不过 Easy Version 最后推导出的答案公式在这篇题解后面还会用到。

另外，这篇题解也默认了 $x$ 要么等于 $y$，要么等于 $y+1$。

在后面的图片中，把所有交叉路口之间的道路全部省去，原图变为一个 $n\times m$ 的网格，需要用若干条不往回走的路径覆盖这个网格的所有格子。

所有线路连通的要求可以丢掉不管，因为所有线路都可以延长到四个角落，从而一定与其它所有线路互相连通。在后面的图片中，为了美观，把这些延长的线去掉了。

### Subtask 1

也就是 Easy Version Subtask 1 的打表或者爆搜加上个输出，代码略。

### Subtask 2

答案为 $n$。

证明：每条线最多覆盖 $n+m-1$ 个路口，若答案 $\le n-1$，则有：

$$(n-1)(n+m-1)\ge nm$$
$$(n-1)^2+nm-m\ge nm$$
$$(n-1)^2\ge m$$

当 $m\ge n^2$ 且 $n\ge 1$ 时，这个式子不可能成立。因此，答案不可能 $\le n-1$。

或者根据 Subtask 1 部分提到的 $m\ge\lfloor\dfrac{(n+1)^2}{4}\rfloor$ 时答案为 $n$，由于当 $n\ge1$ 时 $n^2\ge\dfrac{(n+1)^2}{4}$，而这里保证了 $m\ge n^2$，所以答案必为 $n$。

当 $ans=n$ 时，有一个很简单的构造：

![](https://cdn.luogu.com.cn/upload/image_hosting/ab6whie8.png?x-oss-process=image/resize,m_lfit,h_600,w_600)

（上图中，前文所说的“延长的线”用粉色细线标出了，在后面的图片中不会再画出这些“延长的线”。）

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int t;cin>>t;
	while(t--){
		int n,m;cin>>n>>m;
		cout<<n<<"\n";
		for(int i=0;i<n;i++){
			cout<<"1 1 "<<n+m-2<<" "<<string(i,'D')<<string(m-1,'R')<<string(n-i-1,'D')<<"\n";
		}
	}
	return 0;
}
```

### Subtask 3

在 Easy Version Subtask 2 的基础上加上输出构造方案。

考虑 $3\times3$ 的盘面，有两种构造方法使其答案为 $2$。现在，在上面堆 $x$ 条线路，下面堆 $y$ 条线路，画一个像 $3\times3$ 的盘面一样的图案即可，也就是把那个图案的一条线换成若干条线。例如这是 $9\times9$ 的其中一种构造方案。

![](https://cdn.luogu.com.cn/upload/image_hosting/5v1xpssz.png?x-oss-process=image/resize,m_lfit,h_300,w_300)

其它大小的构造方案类似，就是有可能会出现线路重合的情况，不太好看，所以不画了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int t;cin>>t;
	while(t--){
		int n,m;cin>>n>>m;
		int ans=ceil(2.0/3.0*n);
		int y=ans/2,x=ans-y;
		cout<<ans<<"\n";
		for(int i=1;i<=x;i++){
			cout<<"1 1 "<<n+m-2<<" ";
			cout<<string(i-1,'D');
			cout<<string(x-i,'R');
			cout<<string(y,'R');
			cout<<string(n-x,'D');
			cout<<string(n-x-y,'R');
			cout<<string(i-1,'R');
			cout<<string(x-i,'D');
			cout<<"\n";
		}
		for(int i=1;i<=y;i++){
			cout<<n<<" 1 "<<n+m-2<<" ";
			cout<<string(i-1,'R');
			cout<<string(y-i,'U');
			cout<<string(x,'U');
			cout<<string(n-y,'R');
			cout<<string(n-x-y,'U');
			cout<<string(i-1,'U');
			cout<<string(y-i,'R');
			cout<<"\n";
		}
	}
	return 0;
}
```

### Subtask 4

由 Subtask 2 得，$m\ge100$ 时，答案必为 $n$。

还可以通过 Easy Version Subtask 1 部分提到的 $m\ge\lfloor\dfrac{(n+1)^2}{4}\rfloor$ 时答案为 $n$ 得出，$m\ge30$ 时，答案都必为 $n$。

当 $n$ 大于这个数时，可以提前特判输出。

剩下 $n\le10,m\le99$（或 $m\le29$）的情况，考虑状压，但是出题人懒了。理论上能过。

### Subtask 5

#### 部分分构造

有一个显然的 $\min(n,m)$ 的构造，同 Subtask 2。不过在大部分情况下都拿不到什么分。

还可以用 Subtask 3 的构造方法，此时的答案为 $\lceil\dfrac23\max(n,m)\rceil$。

这两个构造方法可以结合，哪个更小就用哪个。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int t;cin>>t;
	while(t--){
		int n,m;cin>>n>>m;
		int ans1=min(n,m);
		int ans2=ceil(2.0/3.0*max(n,m));
		cout<<min(ans1,ans2)<<"\n";
		if(ans1<ans2){
			if(n<m){
				for(int i=0;i<n;i++){
					cout<<"1 1 "<<n+m-2<<" "<<string(i,'D')<<string(m-1,'R')<<string(n-i-1,'D')<<"\n";
				}
			}else{
				for(int i=0;i<m;i++){
					cout<<"1 1 "<<n+m-2<<" "<<string(i,'R')<<string(n-1,'D')<<string(m-i-1,'R')<<"\n";
				}
			}
		}else{
			int y=ans2/2,x=ans2-y;
			for(int i=1;i<=x;i++){
				cout<<"1 1 "<<n+m-2<<" ";
				cout<<string(i-1,'D');
				cout<<string(x-i,'R');
				cout<<string(y,'R');
				cout<<string(n-x,'D');
				cout<<string(m-x-y,'R');
				cout<<string(i-1,'R');
				cout<<string(x-i,'D');
				cout<<"\n";
			}
			for(int i=1;i<=y;i++){
				cout<<n<<" 1 "<<n+m-2<<" ";
				cout<<string(i-1,'R');
				cout<<string(y-i,'U');
				cout<<string(x,'U');
				cout<<string(m-y,'R');
				cout<<string(n-x-y,'U');
				cout<<string(i-1,'U');
				cout<<string(y-i,'R');
				cout<<"\n";
			}
		}
	}
	return 0;
}
```

一共可以获得 $54$ 分，其中第五个测试点 $12$ 分。

考虑将 Subtask 3 的构造推广到所有的 $n,m$，可以画出一个图：

![](https://cdn.luogu.com.cn/upload/image_hosting/a4jlc1pc.png?x-oss-process=image/resize,m_lfit,h_500,w_500)

由此可以列出方程：$\begin{cases}2x+y=n\\x+2y=m\end{cases}$，解得 $ans=x+y=\dfrac{n+m}3$，$x=n-ans$，$y=m-ans$。不过这只适用于 $3\mid n+m$ 的情况，如果 $3\nmid n+m$，那么答案应该是 $\lceil\dfrac{n+m}3\rceil$，且 $y=ans-x$。结合 Subtask 2 的构造，$\lceil\dfrac{n+m}3\rceil>\min(n,m)$ 时输出答案为 $\min(n,m)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int t;cin>>t;
	while(t--){
		int n,m;cin>>n>>m;
		int ans=ceil((n+m)/3.0);
		if(ans>min(n,m)){
			cout<<min(n,m)<<"\n";
			if(n<m){
				for(int i=0;i<n;i++){
					cout<<"1 1 "<<n+m-2<<" "<<string(i,'D')<<string(m-1,'R')<<string(n-i-1,'D')<<"\n";
				}
			}else{
				for(int i=0;i<m;i++){
					cout<<"1 1 "<<n+m-2<<" "<<string(i,'R')<<string(n-1,'D')<<string(m-i-1,'R')<<"\n";
				}
			}
			continue;
		}
		int x=n-ans,y=ans-x;
		cout<<ans<<"\n";
		for(int i=1;i<=x;i++){
			cout<<"1 1 "<<n+m-2<<" ";
			cout<<string(i-1,'D');
			cout<<string(x-i,'R');
			cout<<string(y,'R');
			cout<<string(n-x,'D');
			cout<<string(m-x-y,'R');
			cout<<string(i-1,'R');
			cout<<string(x-i,'D');
			cout<<"\n";
		}
		for(int i=1;i<=y;i++){
			cout<<n<<" 1 "<<n+m-2<<" ";
			cout<<string(i-1,'R');
			cout<<string(y-i,'U');
			cout<<string(x,'U');
			cout<<string(m-y,'R');
			cout<<string(n-x-y,'U');
			cout<<string(i-1,'U');
			cout<<string(y-i,'R');
			cout<<"\n";
		}
	}
	return 0;
}
```

注：上面的构造中有很大可能出现 $x$ 与 $y$ 相差不止 $1$ 的情况~~不然就是满分构造了~~。

一共可以获得 $66$ 分，其中第五个测试点 $18$ 分。

还有其它构造方法，这里略。

#### 满分构造

正片开始。

构造方案不唯一，下面是出题人的构造。

注意到具体的方案会导致一条边的两端是一堆线路的起点或终点，而中间有且仅有连续的一段不是任何线路的起终点。考虑对于 $\min(n,m)$ 那条边，计算出这一段长度的上界。

另一条更长的边越长，可能需要的线路就越多，这样中间的这一段长度就越短。所以，要让中间这一段最长，需要尽量缩短另一条边的长度，直到 $n=m$ 后就不能再缩了，因为这样 $\min(n,m)$ 就变成了另一条边。因此长度为 $\min(n,m)$ 的边中间那一段的长度要取到上界，可以令 $n=m=\min(n,m)$。

再代入 $ans=\lceil2\times\dfrac{(n+m)-\sqrt{n^2+m^2-nm}}{3}\rceil$，得到 $ans=\lceil\dfrac{2}{3}n\rceil$（也就是本题的 Subtask 2 答案）。中间那一段的长度是 $n-ans$，即 $\lfloor\dfrac{1}{3}n\rfloor$。因此中间那一段的长度不会超过这条边的 $\dfrac13$。这样就能得出一个结论：**无论如何，上下那两段作为线路起终点的部分的长度都不比中间这段短**。还有一个推论：**如果上下两段的长度有一个小于中间那段长度，那么这条边一定不是更短的那条边**。

接下来就可以开始构造了。这里以 $13\times26$ 的情况为例。其答案为 $11$，也就是 $x=6,y=5$。

令左右两条边是短边，上下两条边是长边，从左往右构造。首先还是在左侧的上面堆 $x$ 条线路，下面堆 $y$ 条线路。根据前面的推导，可以像下图一样把四个角落的线路画好再说（这里具体的方向并没有关系，只要把角落三角形的位置填满即可）。

![](https://cdn.luogu.com.cn/upload/image_hosting/tovni9u4.png?x-oss-process=image/resize,m_lfit,h_500,w_500)

接着，像前面所说的经过推广的 Subtask 3 做法一样，让下面的所有线路往上移动，直到到达上面的线路下方，再右拐。

![](https://cdn.luogu.com.cn/upload/image_hosting/7fl2hlkt.png?x-oss-process=image/resize,m_lfit,h_500,w_500)

这时，下面空出来了和中间那一段一样长的几行。从上面连下来同样个数的线路，接着这些线路就可以直接连到右下角了，如下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/5y4s94zx.png?x-oss-process=image/resize,m_lfit,h_500,w_500)

现在，中间又出现了相同长度的一段空白。这次让上面的所有线路往下移动，再从下面连同样数量的线路到上面，填满同样数量的几行。

![](https://cdn.luogu.com.cn/upload/image_hosting/c81d41wb.png?x-oss-process=image/resize,m_lfit,h_500,w_500)

这样的操作结束，上下的线路数量都减少了中间那一段的长度，原问题也变成了更小的一个矩形的子问题（在这个例子中为 $9\times 13$）。

可以一直重复这样的操作（**上面和下面都减少相同数量算一次这样的操作**，也就是说，上下两边同时减少中间那段的长度，这样上下线路数量之差可以保持至多为 $1$），直到**上下有至少一侧的线路数量小于中间那段的长度**。

![](https://cdn.luogu.com.cn/upload/image_hosting/9w5frrz3.png?x-oss-process=image/resize,m_lfit,h_500,w_500)

现在要是再做一次同样的操作，会出现线路不够填满上/下出现的空缺的情况，怎么办呢（在图片的例子中恰好再进行半次操作即可连好，但是这里考虑更普遍的情况）？

根据前面的推论，因为**上下两侧的线路数量至少有一个小于中间那段的长度**，所以在这个子问题中，矩形的短边不再是现在竖着的这条边了，而是另一条横着的边。因此，要解决剩下的这个矩形的子问题，只需要旋转 $90\degree$ 再用同样的方法就可以了。

![](https://cdn.luogu.com.cn/upload/image_hosting/mfgtqit1.png?x-oss-process=image/resize,m_lfit,h_500,w_500)

一直这样递归解决即可（上图中橙色线为解决 $4\times5$ 的子问题时延伸出的线路，黄色线为再旋转 $90\degree$ 后解决 $1\times 2$ 子问题时延伸出的线路）。

因为在这样的构造中，没有多余的交叉路口，且根据计算这样的 $x$ 和 $y$ 只要不产生多余的交叉路口就可以填满 $n\times m$ 的区域，所以这样的构造一定能填满所有交叉路口。

写代码的时候要注意旋转之后方向的处理，以及解决子问题时可能出现“线路太多”的问题，要记得“及时止损”：具体地，如果左边的线路已经到达右边对应的行或列，那么直接连上即可。此时在上面图片的例子中，黄色的线路就不需要经过新的一轮递归再画出了。

下面的代码为了实现方便，可能在某些地方和前面说的有点不同。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e4+5;
int n,m;
bool rev;
struct metro{
	bool ud;
	int sx,sy,ex,ey,sp,ep;
	string s;
	bool locked;
	void setup(bool b){
		locked=0;
		ud=b;
		if(ud){
			sx=1;sy=1;
			ex=n;ey=m;
		}else{
			sx=n;sy=1;
			ex=1;ey=m;
		}
		sp=0;ep=n+m-3;
		s.resize(n+m-2);
	}
	void print(){
		if(ud)cout<<"1 1 "<<n+m-2<<" "<<s<<"\n";
		else cout<<n<<" 1 "<<n+m-2<<" "<<s<<"\n";
	}
	void er(){
		s[ep--]='R';
		ey--;
	}
	void eu(){
		s[ep--]='U';
		ex++;
	}
	void ed(){
		s[ep--]='D';
		ex--;
	}
	void _r(){
		if(!rev){
			s[sp++]='R';
			sy++;
		}else{
			if(ud){
				s[ep--]='D';
				ex--;
			}else{
				s[sp++]='U';
				sx--;
			}
		}
	}
	void _d(){
		if(!rev){
			s[sp++]='D';
			sx++;
		}else{
			s[ep--]='R';
			ey--;
		}
	}
	void _u(){
		if(!rev){
			s[sp++]='U';
			sx--;
		}else{
			s[sp++]='R';
			sy++;
		}
	}
	void lock(){
		if(sx==ex){
			while(sp<=ep){
				s[sp++]='R';
				sy++;
			}
			locked=1;
		}else if(sy==ey){
			if(ud){
				while(sp<=ep){
					s[sp++]='D';
					sx++;
				}
			}else while(sp<=ep){
				s[sp++]='U';
				sx--;
			}
			locked=1;
		}
	}
	void u(int l){
		lock();
		while(l--)if(!locked){
			_u();
			lock();
		}
	}
	void d(int l){
		lock();
		while(l--)if(!locked){
			_d();
			lock();
		}
	}
	void r(int l){
		lock();
		while(l--)if(!locked){
			_r();
			lock();
		}
	}
}ud[N],du[N];
int ady,x,y;
int idx(int i){
	return i;
}
int idy(int i){
	if(!rev)return i+ady;
	else return y-i+1+ady;
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int t;cin>>t;
	while(t--){
		cin>>n>>m;int nn=n,nm=m;ady=rev=0;
		int ans=ceil(2*(n+m-sqrt(n*n+m*m-n*m))/3);
		y=ans/2,x=ans-y;int ox=x,oy=y;
		cout<<ans<<"\n";
		for(int i=1;i<=x;i++){
			ud[i].setup(1);
			for(int j=0;j<x-i;j++)ud[i].ed();
			for(int j=0;j<i-1;j++)ud[i].er();
		}
		for(int i=1;i<=y;i++){
			du[i].setup(0);
			for(int j=0;j<y-i;j++)du[i].eu();
			for(int j=0;j<i-1;j++)du[i].er();
		}
		for(int i=1;i<=x;i++){
			ud[i].d(i-1);
			ud[i].r(x-i);
		}
		for(int i=1;i<=y;i++){
			du[i].u(i-1);
			du[i].r(y-i);
		}
		while(nn&&nm){
			if(nn>nm)swap(nn,nm),rev^=1;
			int w=nn-x-y;
			if(w<=0){
				if(nn-x>0)for(int i=1;i<=x;i++)ud[idx(i)].d(nn-x);
				if(nn-y>0)for(int i=1;i<=y;i++)du[idy(i)].u(nn-y);
				break;
			}
			for(int i=1;i<=y;i++)du[idy(i)].u(w);
			for(int i=1;i<=x;i++)ud[idx(i)].r(y);
			for(int i=x-w+1;i<=x;i++)ud[idx(i)].d(y+w);
			for(int i=1;i<=y;i++)du[idy(i)].r(y+w);
			x-=w;
			for(int i=1;i<=x;i++)ud[idx(i)].d(w);
			for(int i=1;i<=y;i++)du[idy(i)].r(x);
			for(int i=y-w+1;i<=y;i++)du[idy(i)].u(x+w);
			for(int i=1;i<=x;i++)ud[idx(i)].r(x+w);
			y-=w;
			if(rev)ady+=w;
			nm-=nn;
			nn-=w*2;
		}
		for(int i=1;i<=ox;i++)ud[i].print();
		for(int i=1;i<=oy;i++)du[i].print();
	}
	return 0;
}
```

---

一些关于这两题的 fun facts：

1. 本题来源于我两年前的灵感。当时我画了 $10$ 以内的 $n=m$ 的情况，发现了 $ans=1,2,2,3,4,4,5,6,6,\dots$ 的规律，即 Subtask 1（不过没发现 Subtask 5 的通用构造方法）。
2. 本题的线路不能「绕路」，实际上灵感来源于游戏「跳舞的线」，~~其实也有一些对某些城市地铁线路拐来拐去，交而不换的吐槽~~。
3. 这题刚出出来的时候，我认为这题的难度与 [CSP-J 2022 T2](/problem/P8814) 相差不大，因为那题也是解一元二次。
4. 分成两个 Version 的想法是在组题的时候才有的，原本这题只有 Easy Version。
5. Easy Version 样例中的倒数第二组数据是开根会出现精度误差的数据，最后一组输入有意义且满足 $ans=n-9999$。

---

