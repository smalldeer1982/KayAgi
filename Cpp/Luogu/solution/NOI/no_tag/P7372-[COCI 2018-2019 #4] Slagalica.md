# [COCI 2018/2019 #4] Slagalica

## 题目描述

Jurica 创造了一个谜图游戏，它是一个 $N$ 行 $M$ 列的平行四边形，由若干个结点组成。

谜图中，行从 $1$ 到 $N$，顺序为从下到上；列从 $1$ 到 $M$，顺序为从左到右。每个结点用 $(x,y)$ 表示，其中 $x,y$ 分别为行和列。每个结点有一个在 $[1,N \times M]$ 内的唯一的整数权值。

当谜图的第 $i$ 行从左到右的结点的权值分别为 $M(i-1)+1 \sim Mi$ 时，谜图就被认为是解开了。

当 $N=3,M=4$ 时，谜图如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/9u5ys36s.png)

谜图中可以进行两种操作：

1. 选取单位大小的菱形，其中包含结点 $(x,y),(x+1,y),(x+1,y+1),(x,y+1)$，并将其顺时针旋转。

![](https://cdn.luogu.com.cn/upload/image_hosting/3xeumpya.png)

2. 选取单位大小的等边三角形，其中包含结点 $(x,y),(x+1,y),(x,y+1)$，并将其顺时针旋转。

![](https://cdn.luogu.com.cn/upload/image_hosting/jntexc3i.png)

Jurica 进行了若干次操作，将其称为一个大操作。并将该大操作（即一系列操作）重复进行了若干次，竟然将谜图解开了。

给定谜图的规模和大操作重复次数 $K$，判断是否有一种大操作，从解开的谜题开始，使得在 $K$ 次重复该大操作之后，首次再回到解开的状态。如果能解开，请输出组成大操作的操作。

## 说明/提示

#### 数据规模与约定

对于 $40\%$ 的数据，$N,M \le 3$，$K \le 20$。

对于 $100\%$ 的数据，$2 \le N,M \le 100$，$2 \le K \le 10^{12}$。

#### 说明

**本题分值按 COCI 原题设置，满分 $110$。**

**题目译自 [COCI2018-2019](https://hsin.hr/coci/archive/2018_2019/) [CONTEST #4](https://hsin.hr/coci/archive/2018_2019/contest4_tasks.pdf)  _T4 Slagalica_。**

## 样例 #1

### 输入

```
2 3 2```

### 输出

```
5
R 1 1
R 1 1
T 1 1
T 1 1
T 1 1```

## 样例 #2

### 输入

```
3 3 12```

### 输出

```
3
R 1 1
T 2 2
T 2 1```

## 样例 #3

### 输入

```
5 4 116```

### 输出

```
-1```

# 题解

## 作者：Liquefyx (赞：5)

~~2023-04-23：先吐槽一两句，洛谷这道题的题面是有问题的，原英文题面是要求为**恰好第一次恢复原样**，但翻译的题面没有体现出**第一次**这一限制条件 QAQ。~~

2024.1.11 update: 忽然发现题面改了，记录一下，留恋[qwq](https://www.luogu.com.cn/discuss/600937)，还补了个可能不是很详细的构造证明嘿嘿 (º﹃º )。

### 简化题意

已知有如图所示 $n$ 行 $m$ 列的图：

![](https://cdn.luogu.com.cn/upload/image_hosting/9u5ys36s.png)

操作 $1$ 能选择一个以位置 $x,y\ (1\leq x \leq n-1,\ 1\leq y \leq m-1)$ 为左下角的相邻点组成的平行四边形，然后将这四个点顺时针旋转；

操作 $2$ 能选择一个以位置 $x,y\ (1\leq x \leq n-1,\ 1\leq y \leq m-1)$ 为左下角的相邻点组成的等边三角形，然后将这三个点顺时针旋转；

请构造一组操作次数小于等于 $5\times 10^5$ 的操作序列，使得执行 $k$ 次操作序列后，图**恰好第一次恢复原样**，没有满足要求的序列则输出 $-1$。

### 题目分析

如果我们将每一次执行操作序列后的位置与原位置连边，那么这个变换就能以总点数为 $n\times m$ 的一些环表示出来，既然是“恰好第一次恢复原样”，说明所有环的长度的最小公倍数就恰好为 $k$。

考虑到总点数和操作序列的次数的限制，我们应该使得总环长尽可能的小，那么我们就可以对 $k$ 分解质因数，表示为 $\prod^{o}_{i=1} p_i^{c_i}$，然后构造 $o$ 个环长分别为 $p_i^{c_i}$ 的环即可（剩下的点看作自环不管就行），可以证明如此构造的环的总环长（不算自环，下面的证明同样不考虑自环）最小：~~（感觉不如感性理解）~~

有一个显然的结论，一个序列 $\{a_n\}$ 的最小公倍数相当于把序列中的每个数 $a_k$ 质因数分解后，将每一个质数求最大的出现次数的幂乘起来，形式化地，若序列每个数 $a_k$ 可分解为 $\prod_{i=1}^m p_i^{c_{i,k}}$，设 $mx_i=\max_{k=1}^n c_{i,k}$，则 $lcm=\prod_{i=1}^m p_i^{mx_i}$，所以，在我们分解题目中的 $k$ 后（$k=\prod^{o}_{i=1} p_i^{c_i}$），对于每个 $p_i$，一定能在环长序列中找到一个数使得其能被 $p_i^{c_i}$ 整除，既然要总和最小，序列中有多个数能被 $p_i$ 整除的情况一定是不优的，不能整除 $k$ 的质数也肯定不能整除序列中的任何数，于是分析存在多个质数能整除同一个数的情况，若一个环长 $a$ 能被两个不同的质数 $p_i$、$p_j$ 整除（设 $a=p_i^{c_i}\times p_j^{c_j},p_i<p_j$），因为此时最小的情况为 $6=2\times 3$，会发现刚好 $6>2+3$，并且当 $c_j$ 不变时如果 $c_i+=1$，那么 $a$ 的增长量为 $a\times (p_i-1)$，$p_i^{c_i}+p_j^{c_j}$ 的增长量为 $p_i^{c_i}\times (p_i-1)$，显然 $a$ 的增长量更多（$p_i-1 \ge 1,p_j^{c_j} \ge 3$ 嘛），由于 $p_i<p_j$，则 $c_i$ 不变 $c_j+=1$ 的情况也一样，所以把 $a$ 拆成两个数 $p_i^{c_i}$ 和 $p_j^{c_j}$ 一定更优，$a$ 能被多个质数整除的情况同样可以分析得到拆 $a$ 更优的结论（其实光看 $c_i=1$ 的情况即可，因为若 $c_i$ 增长，$a$ 的增长量一定更多，而 $j$ 个质数的情况能看作是 $j-1$ 个质数的情况添上了一个质数 $p$，那么最后分析下来依旧是 $a$ 的增长量更多，所以可得该结论阿巴阿巴），综上，最优情况肯定是构造的 $o$ 个环长分别为 $p_i^{c_i}$ 的环。

接下来我们要考虑如何去一个一个把环给构造出来。

通过~~瞎搞~~模拟我们能够发现，进行 $1$ 次操作 $1$ 后再进行 $2$ 次操作 $2$，我们能够把一个以位置 $x,y\ (1\leq x \leq n-1,\ 1\leq y \leq m-1)$ 为左下角的相邻点组成的平行四边形内的 $x+1,y$ 和 $x+1, y+1$ 两个点交换，如下图，可以理解为先将绿色点移到红色点位置，然后因为蓝色、粉色点在等边三角形内相对位置依旧不变，能直接利用操作 $2$ 将蓝色、粉色点复原，而红色点顺便也就到达了绿色点原来的位置，这组操作十分特殊，我们可以称之为一次单位操作。

![](https://cdn.luogu.com.cn/upload/image_hosting/frhcxik9.png)

我们若是想交换 $x,y$、$x+1,y$ 我们可以先进行一次操作 $1$，然后再进行一次单位操作，最后再进行 $3$ 次操作 $1$ 将其余的点转回去，其他相邻位置都可以像这样进行交换。

于是我们可以总结一下：对于任意相邻位置，我们可以将其放在一个满足操作 $1$ 的平行四边形内，先进行操作 $1$ 将这对相邻点放在单位操作能够进行交换的位置（即这个平行四边形的上边），然后进行单位操作，最后再把其他点用操作 $1$ 复原。

既然有了交换任意两个相邻点的方案，这题便迎刃而解惹，我们直接在一条相邻点连成的、能覆盖整张图的链上（比如蛇形填数、$S$ 路线遍历都可以，如下图）通过交换操作构造变换——那 $o$ 个环长分别为 $p_i^{c_i}$ 的环即可（从环的起始位置到终止位置，每两个点交换一次），至于为什么选择这种链，是因为遍历方便，而且这样做不会有多余的交换操作、交换次数最少，而操作序列的长度最多为 $n\times m\times 7$，能够满足条件。

![](https://cdn.luogu.com.cn/upload/image_hosting/zn8ud9ma.png)

具体细节详见代码：

```cpp
#include <bits/stdc++.h>
#define inLL long long
using namespace std;
int n, m, x, y, az, tot;
inLL k;
struct out {
	char a;
	int x, y;
}ans[500005];

template <typename T> void read(T& x) {
	x = 0; int f = 0; char c = getchar();
	while(c < '0' || c > '9') f |= (c == '-'), c=getchar();
	while(c >= '0' && c <= '9') x=(x<<1)+(x<<3)+(c^48), c=getchar();
	x=(f ? -x : x);
}
int lne; char put[105];
template <typename T> void write(T x, char ch) {
	lne = 0; if(x < 0) putchar('-'), x=-x;
	do { put[++lne]=x%10, x/=10; } while(x);
	while(lne) putchar(put[lne--]^48);
	putchar(ch);
}
void one(int xx, int yy) {//一次单位操作 
	ans[++tot]=out{'R', xx, yy};
	ans[++tot]=out{'T', xx, yy};
	ans[++tot]=out{'T', xx, yy};
}
void up(int xx, int yy) {//交换平行四边形的上边两点 
	one(xx, yy);
}
void down(int xx, int yy) {//交换平行四边形的底边两点 
	ans[++tot]=out{'R', xx, yy};
	ans[++tot]=out{'R', xx, yy};
	one(xx, yy);
	ans[++tot]=out{'R', xx, yy};
	ans[++tot]=out{'R', xx, yy};
}
void left(int xx, int yy) {//交换平行四边形的左边的两点 
	ans[++tot]=out{'R', xx, yy};
	one(xx, yy);
	ans[++tot]=out{'R', xx, yy};
	ans[++tot]=out{'R', xx, yy};
	ans[++tot]=out{'R', xx, yy};
}
void right(int xx, int yy) {//交换平行四边形的右边的两点
	ans[++tot]=out{'R', xx, yy};
	ans[++tot]=out{'R', xx, yy};
	ans[++tot]=out{'R', xx, yy};
	one(xx, yy);
	ans[++tot]=out{'R', xx, yy};
}
void nxt() {
	(x&1 ? ((y^m) ? ++y : ++x) : ((y^1) ? --y : ++x));
	//s型路线遍历嘻嘻,用了位运算和三目运算符优化:
	//x为奇数时,若y等于m则x+1,否则y+1;
	//x为偶数时,若y等于1则x+1,否则y-1;
}
void solve(inLL k/*当前需要构造的环长*/) {
	if(k > az) {//剩余点数不够了,一定无解,输出-1
		puts("-1");
		exit(0);
	}
	az-=k;//计算剩余点数 
	for(int o = 1; o <= k-1; ++o)
		(x&1 ? ((y^m) ?  ((x^1) ? up(x-1, y) : down(x, y)): right(x, y-1)) :
		((y^1) ? up(x-1, y-1) : left(x, y))), nxt()/*交换下一处*/;
	//进行交换操作,此处依旧用了位运算和三目运算符优化:
	//x为奇数时,若y等于m则取右下角为(x-1,y)的平行四边形交换右边两点,否则判断x是否等于1,
	//等于1则取右下角为(x,y)的平行四边形交换下边两点,不等于1就取右下角为(x-1,y)的平行四边形交换上边两点;
	
	//x为偶数时,若y等于1则取右下角为(x,y)的平行四边形交换左边两点,否则直接取右下角为(x-1,y-1)的平行四边形交换上边两点
	
	nxt();//这个环构造玩了,走到下个环的起始位置 
}

signed main() {
	read(n), read(m), read(k);
	x=y=1, az=n*m;
	for(inLL i = 2; i*i <= k; ++i) {
		if(k%i) continue;
		inLL pp = 1;
		while(!(k%i))
			pp*=i, k/=i;//分解k 
		solve(pp);//构造环 
	}
	if(k^1)
		solve(k);
	write(tot, '\n');//输出,详见题目"输出格式"部分 
	for(int i = 1; i <= tot; ++i)
		putchar(ans[i].a), putchar(' '), write(ans[i].x, ' '), write(ans[i].y, '\n');
	return 0;
}
```

芜湖，完结撒花 ヾ(◍°∇°◍)ﾉﾞ。

---

## 作者：Inui_Sana (赞：1)

又是模拟赛题，感觉挺牛的。kkio 场了/bx

首先发现每一次大操作等同于进行一次置换，会形成若干个置换环。根据经典结论得，设这些环长为 $cyc_i$，则有 $k=\operatorname{lcm}cyc_i$。于是考虑在原图中构造若干置换环。

然后通过手玩发现，可以在 $4$ 步以内交换任意两个相邻的数。于是可以把矩阵按照 S 形拉成一条链，再在这条链上割出来若干段作环。

再考虑怎么构造 $cyc_i$。因为所有的环长加起来不能超过 $n\times m$，所以要使 $\sum cyc_i$ 尽可能小。容易发现，将 $k$ 分解质因数得到 $k=\prod p_i^{c_i}$，$cyc_i$ 取到所有的 $p_i^{c_i}$，剩下为 $1$ 时，$\sum cyc_i$ 最小。

于是将这几个置换环构造出来，就做完了，并不难写。无解的情况就是 $\sum p_i^{c_i}>n\times m$。操作不会超过 $4\times n\times m$ 次。随便过。

code：

```cpp
int n,m;ll k;
struct op{
	int x,y,k;
	op(int _x=0,int _y=0,int _k=0):x(_x),y(_y),k(_k){}
};
vector<op> g;vector<int> p;vector<pii> d;
il void sw1(int x,int y){
	g.eb(op(x-1,y,0));
	g.eb(op(x-1,y,1));
	g.eb(op(x-1,y,1));
	g.eb(op(x-1,y,1));
}
il void sw2(int x,int y){
	g.eb(op(x,y,1));
	g.eb(op(x,y,1));
	g.eb(op(x,y,0));
	g.eb(op(x,y,1));
}
il void sw3(int x,int y){
	g.eb(op(x-1,y-1,0));
	g.eb(op(x-1,y-1,0));
	g.eb(op(x-1,y-1,1));
}
il void sw4(int x,int y){
	g.eb(op(x-1,y,1));
	g.eb(op(x-1,y,0));
	g.eb(op(x-1,y,1));
	g.eb(op(x-1,y,1));
}
void Yorushika(){
	scanf("%d%d%lld",&n,&m,&k);
	ll sum=0;
	for(int i=2;1ll*i*i<=k;i++){
		if(k%i==0){
			ll cnt=1;
			while(k%i==0)k/=i,cnt*=i;
			p.eb(cnt),sum+=cnt;
		}
	}
	if(k>1)p.eb(k),sum+=k;
	if(sum>n*m)return puts("-1"),void();
	drep(i,n,1){
		if(i&1)rep(j,1,m)d.eb(Mp(i,j));
		else drep(j,m,1)d.eb(Mp(i,j));
	}
	for(int x:p){
		pii lst=Mp(0,0);
		rep(i,1,x){
			pii j=d.back();d.pop_back();
			if(lst.fi){
				if(lst.fi!=j.fi){
					if(j.se==1)sw4(j.fi,j.se);
					else sw3(j.fi,j.se);
				}else{
					if(j.fi==1)sw2(j.fi,min(lst.se,j.se));
					else sw1(j.fi,min(lst.se,j.se));
				}
			}
			lst=j;
		}
	}
	printf("%d\n",(int)g.size());
	for(op i:g)printf("%c %d %d\n",!i.k?'T':'R',i.x,i.y);
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

## 作者：Feyn (赞：1)

[link](https://www.luogu.com.cn/problem/P7372)

本文思路有借鉴 Loj 上开源的代码，但所有解析均为自己所写。

首先这道题的题面是欠妥当的，它的意思应该是这样的：给定一个平行四边形，每个点上有一个确定且唯一的数，有两种操作，每种操作的格式和效果和题目描述一样。我们的目的是在重复**恰好** $K$ 次大操作（也就是我们构造的操作序列）之后整个平行四边形会**第一次**回到**原来的样子**，也就是每个点上的数字会和一开始一样。

由于 $K$ 很大，直接模拟肯定是会挂掉的，于是考虑简化这个问题。显然 $K$ 是这个平行四边形变化的循环节长度，模拟样例后发现这个平行四边形可能会有多个部分组成，那么整体的循环节长度应该是所有部分循环节长度的 lcm。而显然各部分循环节长度之和越短越容易构造，所以我们需要做的就是找出那么多个数，使它们的最小公倍数恰好为 $K$，并构造以它们为长度的循环。显然把 $K$ 唯一分解之后取每个质因子的极大次方会是和最小的方案，易证不再赘述。

但如何知道有几个循环，以及每个循环的循环节大小呢？经过瞪眼法（~~或者偷看 SPJ~~）可以发现，先模拟出一次大操作后的平行四边形，然后对每个位置向它上面的数的原位置连边，整个图会变成许多简单环（因为每个点出入度都是一），这样一来每次大操作就相当于是一个数在环上挪动了一次，那么每个环都是一个循环，而环的长度就是循环节的长度。

于是问题就变成了构造环。由于我们指不定需要多少环，所以我们希望的是在平行四边形里塞下尽量多的环，于是会想到把环如下图一样塞在平行四边形里：

![](https://cdn.luogu.com.cn/upload/image_hosting/zdryj0gz.png)![](https://cdn.luogu.com.cn/upload/image_hosting/fi29s23f.png)

我们构造环的理念就是先构造一条路径（如红线），然后取出路径上连续的一段作为一个环，容易证明这种构造方法可以充分利用结点（也就是无法构造出比这种方法包含更多环的方案啦）。

确定了构造方法，最后就是如何输出操作了。思考上面那种构造方法的本质，结合前面的分析，发现要达到上面的效果，只需要环上面的元素依次向后挪动一个。而这一过程又可以拆分为每相邻的两个元素交换一次。于是问题变成了如何输出操作使得两个元素交换位置。整道题最神仙的地方来了，直接给结论：给定一个以 $(x,y)$ 为左上角的单位平行四边形，要交换上面的两个元素，只需要对该点进行一次操作 $1$ 和 $2$ 次操作 $2$。模拟即可证明：

![](https://cdn.luogu.com.cn/upload/image_hosting/6qctoakv.png)

发现恰好只有上面的两个点交换了位置。其它操作也是一样，具体方式可以在代码中找到，我也不知道那些大神是怎么找到如此巧妙的方式的。

然后就简单了。有一些细节需要注意：由于进行以上操作的前提是以某个点为**左上点**的单位平行四边形存在，故而要适时地更换操作。还有就是老生常谈的列数奇偶性不同时行的变化方向也不一样。然后就没什么了，代码也比较好写，只要搞出了那几种变换方案。

```cpp
#include<bits/stdc++.h>
//#define feyn
#define int long long
const int N=110;
const int S=500010;
using namespace std;
inline void read(int &wh){
    wh=0;int f=1;char w=getchar();
    while(w<'0'||w>'9'){if(w=='-')f=-1;w=getchar();}
    while(w<='9'&&w>='0'){wh=wh*10+w-'0';w=getchar();}
    wh*=f;return;
}

//op: 0->T  1->R
struct node{int op,x,y;}ss[S];int ccnt;
inline void p(int op,int x,int y){ss[++ccnt]=(node){op,x,y};}

//核心部分，根据变量名可以懂得意思 
inline void up(int x,int y){p(1,x,y);p(0,x,y);p(0,x,y);}
inline void right(int x,int y){p(0,x,y);p(0,x,y);p(1,x,y);}
inline void ni(int x,int y){up(x,y);right(x,y);}//旋转平行四边形 
inline void down(int x,int y){p(1,x,y);ni(x,y);}
inline void left(int x,int y){ni(x,y);p(1,x,y);}
//分别是竖着交换两个数和横着交换两个数 
inline void link_x(int x,int y){y==1?left(x,y):right(x,y-1);}
inline void link_y(int x,int y){x==1?down(x,y):up(x-1,y);}

int m,n,x,y,num;bool ok=true;
inline void nxt(){y&1?(x==m?y++:x++):(x==1?y++:x--);}//找到下一个位置 
inline void solve(int wh){
	if(wh>num){if(ok==true)printf("-1\n");ok=false;return;}//如果没那么多位置构造环 
	for(int i=1;i<wh;i++)((y&1)&&x==m||(y&1)==0&&x==1)?link_y(x,y):link_x(x-1+(y&1),y),nxt();
	//i<wh:长度为wh的环只需要交换wh-1次 
	nxt();num-=wh;return;
}

signed main(){
	
	#ifdef feyn
	freopen("in.txt","r",stdin);
	#endif
	
	read(m);read(n);int k;read(k);
	num=m*n;x=1;y=1;
	for(int i=2;i*i<=k;i++){
		if(k%i)continue;int now=1;
		while(k%i==0)now*=i,k/=i;solve(now);//每个质因数的极大次方 
	}
	if(k>1)solve(k);if(ok==false)return 0;
	printf("%lld\n",ccnt);
	for(int i=1;i<=ccnt;i++){
		putchar(ss[i].op?'R':'T');
		printf(" %lld %lld\n",ss[i].x,ss[i].y);
	}
	
	return 0;
}
```

---

## 作者：WRuperD (赞：0)

一道非常有意思的题。

考虑构造出一堆环，使得每次大操作后每个环内数都沿着环走一步。

这样子最后重新回到初始状态的步数是所有环长的最小公倍数。

先来钦定一下环长，考虑 $k = \prod p_i^{c_i}$，那我们不加证明地猜测最优方案时环长 $len_i = p_i^{c_i}$。

考虑一个类似于 S 形填数。

![](https://cdn.luogu.com.cn/upload/image_hosting/5bi75sz1.png)

如图，这是这个图中存在的最大的一个可能的环。

接着，我们把这个环分成若干段。

![](https://cdn.luogu.com.cn/upload/image_hosting/otk3bltw.png)

如图是在 $k=60$ 时的一种划分方式。接下来我们只需要找到一种构造方式使得每一此只交换边上的两个点就做完了。

下面是其中一种方案：

![](https://cdn.luogu.com.cn/upload/image_hosting/bsga41xy.png)

至此，我们做完了整道题。

```cpp
// Problem: P7372 [COCI2018-2019#4] Slagalica
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P7372
// Memory Limit: 64 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)
#include<bits/stdc++.h>
using namespace std;
const long long inf = 1e18;
const int mininf = 1e9 + 7;
#define int long long
#define pb emplace_back
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
inline void write(int x){if(x<0){x=~(x-1);putchar('-');}if(x>9)write(x/10);putchar(x%10+'0');}
#define put() putchar(' ')
#define endl puts("")
const int MAX = 1e2 + 10;
struct node{
	int x, y, op;
}; vector <node> ans;

void up1(int x, int y){
	ans.pb(node{x, y, 2});
	ans.pb(node{x, y, 2});
	ans.pb(node{x, y, 1});
	// puts("u1");
	// write(x), put(), write(y), endl;
}

void up2(int x, int y){
	ans.pb(node{x, y, 1});
	ans.pb(node{x, y, 2});
	ans.pb(node{x, y, 1});
	ans.pb(node{x, y, 1});
	// puts("u2");
	// write(x), put(), write(y), endl;
}

void across2(int x, int y){
	ans.pb(node{x, y, 1});
	ans.pb(node{x, y, 2});
	ans.pb(node{x, y, 2});
	// puts("a1");
	// write(x), put(), write(y), endl;
}

void across1(int x, int y){
	ans.pb(node{x, y, 1});
	ans.pb(node{x, y, 1});
	ans.pb(node{x, y, 2});
	ans.pb(node{x, y, 1});
	// puts("a2");
	// write(x), put(), write(y), endl;
}

int n, m, k;
int nowx = 1, nowy = 1;

int id[MAX][MAX];

bool tonxt(){
	if(nowx % 2)	nowy++;
	else nowy--;
	if(nowy <= 0)	nowx++, nowy = 1;
	if(nowy > m)	nowy = m, nowx++;
	if(nowx > n)	return false;
	return true;
}

void work(int x){
	// write(x), endl;
	if(nowx > n){
		puts("-1");
		exit(0);
	}
	x--;
	int prex = nowx, prey = nowy;
	while(x--){
		if(!tonxt()){
			puts("-1");
			exit(0);
		}	
		if(prex == nowx){
			if(prex == n){
				across2(prex, min(prey, nowy));
			}else{
				across1(prex + 1, min(prey, nowy));
			}
		}else{
			if(nowy == m){
				up1(nowx, m - 1);
			}else{
				up2(nowx, 1);
			}
		}
		prex = nowx, prey = nowy;
	}
	tonxt();
	// endl;
}

void solve(){
	n = read(), m = read(), k = read();
	int psz = 0;
	for(int i = 2; i * i <= k; i++){
		int cnt = 1;
		while(k % i == 0){
			cnt *= i;
			k /= i;
		}
		if(cnt > 1)	work(cnt);
	}
	if(k > 1)	work(k);
	write(ans.size()), endl;
	for(int i = 0; i < ans.size(); i++){
		putchar(ans[i].op == 1 ? 'R' : 'T'), put();
		write(ans[i].x - 1), put(), write(ans[i].y), endl;
	}
}

signed main(){
	int t = 1;
	while(t--)	solve();
	return 0;
}
```


---

## 作者：EuphoricStar (赞：0)

模拟赛赛时被这题题面唬住了，没想到原来这么简单/ll。

设第 $i$ 个位置经过变化后的位置为 $p_i$。那么连边 $i \to p_i$ 后所有环长的 $\text{lcm}$ 为 $K$。

考虑先构造一组数 $\{a_n\}$ 使得 $\text{lcm}(a_1, a_2, \ldots, a_n) = K$ 且 $\sum\limits_{i = 1}^n a_i$ 最小，$a_i$ 表示第 $i$ 个环的环长。结论是把 $K$ 质因数分解后取 $a_i = p_i^{e_i}$ 即可。

所以现在我们的任务是构造一些长度给定的环。考虑走 S 形拎出一条链（借用一下 [Liquefyx 的图](https://www.luogu.com.cn/blog/RJ-lalala/solution-p7372)）：

![](https://cdn.luogu.com.cn/upload/image_hosting/zn8ud9ma.png)

所以我们如果可以交换相邻两个数，那么每次把链的第一个点逐个地交换到末尾即可。

写爆搜或者手玩可以得出交换相邻两个数的方案。于是这题就做完了。

[code](https://loj.ac/s/1987071)

---

