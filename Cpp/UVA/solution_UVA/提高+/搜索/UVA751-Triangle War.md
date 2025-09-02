# Triangle War

## 题目描述

## 题面翻译

给出10个点，共有18条边，每次A,B两个人轮流加入一条边。A先加。

如果形成一个三角形，则三角形归他所有，**而且还必须再走一步**。最后三角形多的人胜。

现在已经给出一部分已经完成的步数，由于两位玩家都是**最聪明的**，他们都会走**为自己带来最大优势**的步数。你需要判断谁会赢得游戏。

## 样例 #1

### 输入

```
4
6
2 4
4 5
5 9
3 6
2 5
3 5
7
2 4
4 5
5 9
3 6
2 5
3 5
7 8
6
1 2
2 3
1 3
2 4
2 5
4 5
10
1 2
2 5
3 6
5 8
4 7
6 10
2 4
4 5
4 8
7 8```

### 输出

```
Game 1: B wins.
Game 2: A wins.
Game 3: A wins.
Game 4: B wins.```

# 题解

## 作者：Ciyang (赞：3)

[更好的体验，博客中查看](https://xciyang.github.io/2019-12/19-luoguuva751/)

### 前言

这个题是练习max-min策略+alpha-beta剪枝的好题，但是我们也可以记忆化搜索。

并且此题状态少，记忆化只需要20ms，比用alpha-beta剪枝的做法要快一些。

### 分析

当然我做这道题还是想学习alpha-beta剪枝的，使用此算法的题解已有，所以不多加解释。

此题有两种max-min策略的解法，解法1是最大最小化最终胜负（1为先手胜利，-1为后手胜利），解法2是最大最小化最终得分差（先手得分-后手得分），当然流程就是先手最大化此值，后手最小化此值。

至于局面的存储，与已有题解类似，存储边的编号，然后用二进制表示已连接的边。而三角形连接我们就手写一个数组表示需要哪三条边（很麻烦）。这个题只有单位三角形得分，似乎题意里没说。

再来说两种解法的差异，因为最终胜负在一方大于等于5分就可判定，所以解法1效率较高，并且我们还可用使用alpha-beta剪枝来优化。

当然我们也可以用解法2。有一个显然的结论，无论此步是A还是B，一个状态只会对应一个最优得分。那么就可以使用记忆化，已知状态总共有$(1 << 18) - 1$种，这样效率就高了。并且我们每组数据前不需要清空记忆化数组，因为一个状态对应一个分数，并不需要知道你是如何到达此状态的。

实现时先模拟给出的N步，然后记录双方已得分数。然后max_min搜索，如果此步得分，继续操作，如果此步不得分，就让对手操作，然后减去对手操作的分数，如果全部连接就返回0，每层都是最大化自己的得分。至于为什么双方都是最大化，我给出以下解释：A最大化(A的得分-B的得分)，B最大化(B的得分-A的得分)，所以都是最大化。

在最终判定胜负时，设当前玩家为p(p为0或1)，若p已得分数+max_min(从p开始)的结果>(p^1)的分数就判定p胜利，否则(p^1)胜利。

### 代码

解法1

```cpp
#include <iostream>
#include <stdio.h>
using namespace std;
int edg[11][11];
int tri[] = {(1 << 0) + (1 << 1) + (1 << 2),
			 (1 << 3) + (1 << 4) + (1 << 7),
			 (1 << 2) + (1 << 4) + (1 << 5),
			 (1 << 5) + (1 << 6) + (1 << 10),
			 (1 << 8) + (1 << 9) + (1 << 15),
			 (1 << 7) + (1 << 9) + (1 << 11),
			 (1 << 11) + (1 << 12) + (1 << 16),
			 (1 << 10) + (1 << 12) + (1 << 13),
			 (1 << 13) + (1 << 14) + (1 << 17)};
#define addedge(x, y, z) (edg[x][y] = edg[y][x] = z)
void init() {
	addedge(1, 2, 0);
	addedge(1, 3, 1);
	addedge(2, 3, 2);
	// ...
	// 本连边方式不推荐学习，因此部分内容已省略，相信有更好的方式
	return;
}
int T, n, tmpx, tmpy;
int nextStep(int lst, int nst) {
	int cnt = 0;
	// lst 为之前状态 nst 为当前状态
	for(int i = 0; i < 9; i++)
		if((lst & tri[i]) != tri[i] && (nst & tri[i]) == tri[i]) ++cnt;
	return cnt;
}
const int full = (1 << 18) - 1;
int alpha_beta(int nowp, int st, int alpha, int beta, int ans[2]) {
	if(ans[0] >= 5) return 1;
	if(ans[1] >= 5) return -1;
	int fst = full ^ st, nst;
	while(fst) {
		int edge = fst & (-fst);
		// 枚举连边
		int res = nextStep(st, (nst = st | edge));
		if(res) {
			ans[nowp] += res;
			(nowp ? beta : alpha) = (nowp ? min< int > : max< int >)((nowp ? beta : alpha), alpha_beta(nowp, nst, alpha, beta, ans));
			ans[nowp] -= res;
		}
		else {
			(nowp ? beta : alpha) = (nowp ? min< int > : max< int >)((nowp ? beta : alpha), alpha_beta(nowp ^ 1, nst, alpha, beta, ans));
		}
		// 压行写法
		if(alpha >= beta) break;
		// alpha-beta剪枝
		fst -= edge;
	}
	return nowp ? beta : alpha;
}
int main() {
	init();
	cin >> T;
	for(int t = 1; t <= T; t++) {
		cin >> n;
		int st = 0, p = 0, ans[2] = {0};
		for(int i = 1; i <= n; i++) {
			cin >> tmpx >> tmpy;
			int res = nextStep(st, st | (1 << edg[tmpx][tmpy]));
			st = st | (1 << edg[tmpx][tmpy]);
			if(res) {
				ans[p] += res;
			}
			else {
				p ^= 1;
			}
		}
		// 模拟
		int res = alpha_beta(p, st, -0x3f3f3f3f, 0x3f3f3f3f, ans);
		cout << "Game " << t << ": ";
		if(res >= 0) {
			cout << "A wins." << endl;
		}
		else {
			cout << "B wins." << endl;
		}
	}
	return 0;
}
```

解法2

```cpp
#include <iostream>
#include <stdio.h>
using namespace std;
int edg[11][11];
int tri[] = {(1 << 0) + (1 << 1) + (1 << 2),
			 (1 << 3) + (1 << 4) + (1 << 7),
			 (1 << 2) + (1 << 4) + (1 << 5),
			 (1 << 5) + (1 << 6) + (1 << 10),
			 (1 << 8) + (1 << 9) + (1 << 15),
			 (1 << 7) + (1 << 9) + (1 << 11),
			 (1 << 11) + (1 << 12) + (1 << 16),
			 (1 << 10) + (1 << 12) + (1 << 13),
			 (1 << 13) + (1 << 14) + (1 << 17)};
#define addedge(x, y, z) (edg[x][y] = edg[y][x] = z)

const int full = (1 << 18) - 1;
int mm[full + 1];

void init() {
	addedge(1, 2, 0);
	addedge(1, 3, 1);
	addedge(2, 3, 2);
	// ...
	// 本连边方式不推荐学习，因此部分内容已省略，相信有更好的方式
	for(int i = 0; i < full; i++) mm[i] = -0x3f3f3f3f;
	mm[full] = 0;
	return;
}


int T, n, tmpx, tmpy;
int nextStep(int lst, int nst) {
	// lst 为之前状态 nst 为当前状态
	int cnt = 0;
	for(int i = 0; i < 9; i++)
		if((lst & tri[i]) != tri[i] && (nst & tri[i]) == tri[i]) ++cnt;
	// 本次得分
	return cnt;
}

int max_min(int nowp, int st) {
	if(mm[st] != -0x3f3f3f3f) return mm[st];
	int fst = full ^ st, nst, maxx = -0x3f3f3f3f;
	while(fst) {
		int edge = fst & (-fst);
		// 枚举连边
		int res = nextStep(st, (nst = st | edge));
		if(res) {
			maxx = max(maxx, res + max_min(nowp, nst));
		}
		else {
			maxx = max(maxx, -max_min(nowp ^ 1, nst));
		}
		fst -= edge;
	}
	return mm[st] = maxx;
}
int main() {
	init();
	cin >> T;
	for(int t = 1; t <= T; t++) {
		cin >> n;
		int st = 0, p = 0, ans[2] = {0};
		for(int i = 1; i <= n; i++) {
			cin >> tmpx >> tmpy;
			int res = nextStep(st, st | (1 << edg[tmpx][tmpy]));
			st = st | (1 << edg[tmpx][tmpy]);
			if(res) {
				ans[p] += res;
			}
			else {
				p ^= 1;
			}
		}
		// 模拟
		int res = max_min(p, st);
		cout << "Game " << t << ": ";
		if((ans[p] + res > ans[p ^ 1]) ^ p) {
			cout << "A wins." << endl;
		}
		else {
			cout << "B wins." << endl;
		}
	}
	return 0;
}
```
### 后记

不过这个题3s时限怕是有点水了。

然后还可以做[ 【九省联考2018】一双木棋chess](https://www.luogu.com.cn/problem/P4363)，也可以使用max-min策略+记忆化搜索。


---

## 作者：Kato_Megumi (赞：1)

实质意义上有一点慢，仅供大家参考一下~~（co标就不用co我这个蒟蒻的了）~~
#### ------------以下是题解部分-------------  
这道题的思想是**极大极小搜索+alpha_beta优化**。

通过对博弈树不断的搜索，在节点处判断来实现博弈对局。

具体的讲述的话，可以看一看这两篇文章，我在这里就不详述了。
http://www.xqbase.com/computer/search_minimax.htm
http://www.xqbase.com/computer/search_alphabeta.htm

对于这道题来说，稍微有点不一样。

它是一张有10个点的图，不断地在两个点上连边，组成三角形进行博弈。

那么这道题就有几个难点。

其一是**判三角形**。

这个问题，我们解决方法也很简单：对边进行编号。
![对边编号](https://cdn.luogu.com.cn/upload/pic/17399.png)

就像这样↑

这个样子的话，我们就可以用状压的方式表示棋盘，也可以直接用&表示三角形。例如：
![example](https://cdn.luogu.com.cn/upload/pic/17400.png)

这个三角形就可以用 _2^3 + 2^4 + 2^5 = 56_  表示

其二是**局面的存储**。

我们的结束状态是填完了所有边，那么按照表示来说就是2^18-1；

对于三角形，我们应该开一个数组tri[9]，保存下所有的三角形状态。

对于这道题，代码就分为两个部分。

**预处理部分**

首先，在边的部分我们可以暴力处理，用一个mat[11][11]记录两点之间的边的编号。

其次，我们可以用状压来表示连边，连边构成的三角形记录于tri[9]中。

由状压可得，当状态达到(1<<18)-1时，所有边都被连上，即最终状态。

**Alpha_Beta部分**

只有一个小小的问题。

局面评估不是单纯的inf,0,-inf了 (除非最后来判断,但这样会显得复杂一些),

无论双方是谁,都要根据双方的三角形个数来看了，

初始估价都是棋盘上剩下的三角形,随后双方都取最大值则可满足都是最优方案。

###  ----------- ~~（万众期待的）~~代码部分 ------------
加了很多注释，真的很多，有些影响可读性。请各位多多包涵

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<iomanip>
#include<cmath>
#include<algorithm>
#include<queue>
#pragma GCC optimize(3)
using namespace std;
typedef long long LL;
const int maxn=800,INF=(1<<20);
const double eps=1e-8;
inline int Getint(){
    register char c;register int rec=0,f=1;
    for(c=getchar();c<'0'||c>'9';c=getchar())if(c=='-')f=-1;
    while(c>='0'&&c<='9')rec=(rec<<1)+(rec<<3)+(c-'0'),c=getchar();
    return rec*f;
}
int t,m;
int map[11][11]={  
	{0,0,0,0,0,0,0,0,0,0,0},    
	{0,0,0,2,0,0,0,0,0,0,0},    
	{0,0,0,1,3,5,0,0,0,0,0},    
	{0,2,1,0,0,6,8,0,0,0,0},    
	{0,0,3,0,0,4,0,9,11,0,0},    
	{0,0,5,6,4,0,7,0,12,14,0},    
	{0,0,0,8,0,7,0,0,0,15,17},    
	{0,0,0,0,9,0,0,0,10,0,0},    
	{0,0,0,0,11,12,0,10,0,13,0},    
	{0,0,0,0,0,14,15,0,13,0,16},    
	{0,0,0,0,0,0,17,0,0,16,0},    
};    
//建立连边 
int tri[9] = {7,56,98,448,3584,6160,28672,49280,229376};
/*	tri[0]=1|(1<<1)|(1<<2);
	tri[1]=(1<<3)|(1<<4)|(1<<5);
	tri[2]=(1<<1)|(1<<5)|(1<<6);
	tri[3]=(1<<6)|(1<<7)|(1<<8);
	tri[4]=(1<<9)|(1<<10)|(1<<11);
	tri[5]=(1<<4)|(1<<11)|(1<<12);
	tri[6]=(1<<12)|(1<<13)|(1<<14);
	tri[7]=(1<<7)|(1<<14)|(1<<15);
	tri[8]=(1<<15)|(1<<16)|(1<<17);*///储存三角形 
int end_state=(1<<18)-1; // 终结状态 2^18-1,即所有边均被填充
int place(int state,int edge,int &cnt){
	int newstate=(state|edge);//当前局面并上一条边形成新局面
	for(int i=0;i<9;i++){//如果新局面能形成一个新的单位三角形，则计数+1
		if(((state&tri[i])!=tri[i])&&((newstate&tri[i])==tri[i]))
			cnt++;
	}
	return newstate;
}
int alpha_beta(int turn,int state,int alpha,int beta,int ca,int cb){
	if(ca>=5) return 1;// 如 A得到 5分以上则 A赢
	if(cb>=5) return -1;// 如 B得到 5分以上则 A输
	int remain=((~state)&end_state);//计算剩余可走的边
	if(turn){//A的回合 
		while(remain){//有剩余的边 
			int move=(remain&(-remain));//选择一条边
			int ta=ca;
			int val;
			int newstate=place(state,move,ta);
			if(ta>ca){//得分就新添一条边 
				val=alpha_beta(turn,newstate,alpha,beta,ta,cb); 
			}
			else{//否则换人 
				val=alpha_beta(turn^1,newstate,alpha,beta,ca,cb);
			}
			if(val>alpha) alpha=val;
			if(alpha>=beta) return alpha;
			remain-=move;//去掉这条边 
		}
		return alpha; 
	}
	else{//B的回合 
		while(remain){ 
			int move=(remain&(-remain));
			int tb=cb;
			int val;
			int newstate=place(state,move,tb);
			if(tb>cb){ 
				val=alpha_beta(turn,newstate,alpha,beta,ca,tb); 
			}
			else{
				val=alpha_beta(turn^1,newstate,alpha,beta,ca,cb);
			}
			if(val<beta) beta=val;
			if(alpha>=beta) return beta;
			remain-=move; 
		}
		return beta;
	} 
}
int main(){
	int alpha=-INF;
	int beta=INF;
	int ans;
	int turn;
	int ca,cb;
	int ta,tb,status;//ca:A的得分，cb:B的得分，turn:A走或B走 
	t=Getint();
	for(int i=1;i<=t;i++){
		m=Getint();
		ans=status=ca=cb=turn=0;
		for(int i=1;i<=m;i++){
			int x=Getint(),y=Getint();
			ta=ca,tb=cb;
			status=place(status,1<<map[x][y],(turn&1)?cb:ca);//现在棋盘状态 
			if(ta==ca&&tb==cb){//没有得分，换人 
				turn++; 
			}
		}
		if(turn&1) ans=alpha_beta(0,status,alpha,beta,ca,cb);//B的回合 
		else ans=alpha_beta(1,status,alpha,beta,ca,cb);//A的回合
		if(ans>=0) printf("Game %d: A wins.\n",i);
		else printf("Game %d: B wins.\n",i);
	}
} 
```


---

## 作者：普罗 (赞：0)

### 1、初步准备
这是一道alpha-beta剪枝算法的题目，但是由于该题的棋面很小，因此其实用不上alpha-beta，用极大-极小值算法（ab算法的一个简化）即可。

首先我们先了解一下什么是alpha-beta/极大极小值算法：
对于棋面上的每一个棋局，弈棋人都会有很多种操作可以选择，我们把这若干个操作合并为“一层”，在该层中，我们每一种操作都可以形成一棵子树，其中每个结点保存了接下来一步可能形成的棋面。我们对于每一个棋面都取一个估值，用来评估该棋面对于我方的优劣程度。很显然，在每一层中，我们应当选择估值最好的那一步。

那么估值怎么来？这是一个很庞大的问题，在传统的棋中，估值需要参考弈棋大师们的棋谱。也就是说想要评估一个棋面的优劣，还是需要依靠人们的经验，所以传统棋类的估值系统是一门特别大的学问，其中包含了概率论、博弈论、棋谱等等知识。言外之意，就是alpha-beta算法严格意义上只是一个用来评估局面，帮助你选择更有可能获胜的操作的一个算法，它并不能保证你一定能赢。

所以这题就不用做了嘛？不是的。因为这道题的棋面很小，我们可以通过递归搜到游戏结束。这就意味着我们的估值可以简化得特别简单，它的取值只有2种：该棋面必胜 or 该棋面必败。

这个地方需要仔细理解一下，也就是说对于这道题而言，任何一个棋面都是要么必胜 要么必败的。

### 2、理解局部
首先我们规定，如果一个棋面A有必胜策略，则返还值为-1；如果B有必胜策略则返还值为1。
要想理解递归这个过程，最好的方法就是从递归的最深层开始。我们现在直接考虑棋局结束的最后一步：

情况1：A若选择A1操作，B无论选择哪种操作，最后都是A赢
首先从B这一层开始考虑，无论我们选择B1 B2还是B3，最后都是A胜利，所以B这一层我们返还-1，表示这一层无论怎么选都是A获胜。（换言之，B层返还-1，代表B层对应的A结点是A必胜操作）

情况2：A若选择A1操作，B存在操作可以使得B胜利
B1和B2是A必胜结点，但是B3结点是B胜利，即B这一层存在B必胜结点
这就意味着假如我们进入A1结点，那么B会选择那个B必胜结点，那么A就输了。所以这一层是B必胜结点，整体返还的值是1（好好理解这一步）

所以我们就得出了结论：
对于B层而言，假如它的每一个结点都是A必胜，则该层返还-1；只要存在B必胜的结点，那么就返还1。
同理，对于A层而言，假如它的每一个结点都是B必胜，则自己返还1；
否则自己返还-1。

因此我们得出，处理A层的alpha函数和处理B层的beta函数的伪代码：
```
int alpha(...)
{
	对于每一个A的操作方法
		进行操作
		判断它下面的B层的返还值是1还是-1
			只要有一个是-1，那么该层就是A必胜层，直接返还-1
		回溯操作
	结果全都是1，所以返还1
}
int beta(...)
{
	对于每一个B的操作方法
		进行操作
		判断它下面的A层的返还值是1还是-1
			只要有一个是1，那么该层就是B必胜层，直接返还1
		回溯操作
	结果全都是-1，所以返还-1
}

```
### 3、对接题目
对于该题，“操作”就是画线，“回溯”就是删线，判断A结点下B层的返还值就是调用beta递归函数。
要注意的是，一旦连成三角形，那么下一步仍然是己方下，因此这时候要调用的是自己的这一层。
那么回到这道题，我们的alpha函数步骤就是：
```
int alpha(分数a,分数b)
{
	如果分数a很高决定胜局，返还-1
	如果分数b很高决定胜局，返还1
	枚举每一个可以连接的线
		连接线，并查看是否得分
		如果得分，那么下一步还是自己，因此仍然调用alpha函数
		如果没得分，轮到B操作，则调用beta函数，来获取A这个操作对应B层的返还值
		如果返还值为-1，返还-1
		删除线
	如果无线可画，即对弈结束，若A分高返还-1，若B分高返还1
	返还1
}

```
beta函数也同理。

具体怎么画线、怎么判断是否连成三角形，这个暴力是没有问题的，状态压缩当然更好

```cpp
#include<stdio.h>

int alphafs(int as,int bs);
int betafs(int as,int bs);
bool line[18];
int linecheck(int i)
{
	int total=0;
	if(i==0){line[0]=true;if(line[1]==true&&line[2]==true)total++;return total;}
	if(i==1){line[1]=true;if(line[0]==true&&line[2]==true)total++;return total;}
	if(i==2){line[2]=true;if(line[0]==true&&line[1]==true)total++;if(line[4]==true&&line[6]==true)total++;return total;}
	if(i==3){line[3]=true;if(line[4]==true&&line[5]==true)total++;return total;}
	if(i==4){line[4]=true;if(line[3]==true&&line[5]==true)total++;if(line[2]==true&&line[6]==true)total++;return total;}
	if(i==5){line[5]=true;if(line[3]==true&&line[4]==true)total++;if(line[10]==true&&line[12]==true)total++;return total;}
	if(i==6){line[6]=true;if(line[7]==true&&line[8]==true)total++;if(line[2]==true&&line[4]==true)total++;return total;}
	if(i==7){line[7]=true;if(line[6]==true&&line[8]==true)total++;return total;}
	if(i==8){line[8]=true;if(line[6]==true&&line[7]==true)total++;if(line[13]==true&&line[15]==true)total++;return total;}
	if(i==9){line[9]=true;if(line[10]==true&&line[11]==true)total++;return total;}
	if(i==10){line[10]=true;if(line[9]==true&&line[11]==true)total++;if(line[5]==true&&line[12]==true)total++;return total;}
	if(i==11){line[11]=true;if(line[9]==true&&line[10]==true)total++;return total;}
	if(i==12){line[12]=true;if(line[13]==true&&line[14]==true)total++;if(line[5]==true&&line[10]==true)total++;return total;}
	if(i==13){line[13]=true;if(line[12]==true&&line[14]==true)total++;if(line[8]==true&&line[15]==true)total++;return total;}
	if(i==14){line[14]=true;if(line[12]==true&&line[13]==true)total++;return total;}
	if(i==15){line[15]=true;if(line[16]==true&&line[17]==true)total++;if(line[8]==true&&line[13]==true)total++;return total;}
	if(i==16){line[16]=true;if(line[15]==true&&line[17]==true)total++;return total;}
	if(i==17){line[17]=true;if(line[15]==true&&line[16]==true)total++;return total;}
}
int transform(int a,int b)
{
	if(a==1&&b==2)return linecheck(0);
	if(a==1&&b==3)return linecheck(1);
	if(a==2&&b==3)return linecheck(2);
	if(a==2&&b==4)return linecheck(3);
	if(a==2&&b==5)return linecheck(4);
	if(a==4&&b==5)return linecheck(5);
	if(a==3&&b==5)return linecheck(6);
	if(a==3&&b==6)return linecheck(7);
	if(a==5&&b==6)return linecheck(8);
	if(a==4&&b==7)return linecheck(9);
	if(a==4&&b==8)return linecheck(10);
	if(a==7&&b==8)return linecheck(11);
	if(a==5&&b==8)return linecheck(12);
	if(a==5&&b==9)return linecheck(13);
	if(a==8&&b==9)return linecheck(14);
	if(a==6&&b==9)return linecheck(15);
	if(a==6&&b==10)return linecheck(16);
	if(a==9&&b==10)return linecheck(17);
}
int alphafs(int as,int bs)
{
	int score=0,v=0,flag=0;
	if(as>=5)return -1;
	if(bs>=5)return 1;
	for(int i=0;i<18;i++)
	{
		score=0;
		if(line[i]==false)score=linecheck(i);
		else continue;
		flag=1;
		if(score==0)v=betafs(as,bs);
		else v=alphafs(as+score,bs);
		line[i]=false;
		if(v<0)return -1;
	}
	if(flag==0&&bs>as)return 1;
	if(flag==0&&bs<as)return -1;
	return 1;
}
int betafs(int as,int bs)
{
	int score=0,v=0,flag=0;
	if(as>=5)return -1;
	if(bs>=5)return 1;
	for(int i=0;i<18;i++)
	{
		score=0;
		if(line[i]==false)score=linecheck(i);
		else continue;
		flag=1;
		if(score==0)v=alphafs(as,bs);
		else v=betafs(as,bs+score);
		line[i]=false;
		if(v>0)return 1;
	}
	if(flag==0&&bs>as)return 1;
	if(flag==0&&bs<as)return -1;
	return -1;
}
int main()
{
	int m,n,a,b,term=0,scorea=0,scoreb=0,score;
	scanf("%d",&m);
	for(int k=0;k<m;k++)
	{
		scorea=0;
		scoreb=0;
		term=0;
		for(int i=0;i<18;i++)line[i]=false;
		scanf("%d",&n);
		while(n--)
		{
			scanf("%d%d",&a,&b);
			score=transform(a,b);
			if(score==0)term=term^1;
			else
			{
				if(term==0)scorea+=score;
				else scoreb+=score;
			}
		}
		if(term==0)printf("Game %d: %c wins.\n",k+1,alphafs(scorea,scoreb)<0?'A':'B');
		else printf("Game %d: %c wins.\n",k+1,betafs(scorea,scoreb)<0?'A':'B');
	}
}

```


---

