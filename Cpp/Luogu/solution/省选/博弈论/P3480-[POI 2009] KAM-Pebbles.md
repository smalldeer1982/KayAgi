# [POI 2009] KAM-Pebbles

## 题目描述

有 $n$ 堆石子。除了第一堆外，每堆石子个数都不少于前一堆的石子个数。两人轮流操作。每次操作可以从一堆石子中移走任意多颗石子，但是要保证操作后仍然满足初始时的条件。没有石子可移动的人就输掉了游戏。问先手是否必胜。

## 样例 #1

### 输入

```
2
2
2 2
3
1 2 4
```

### 输出

```
NIE
TAK
```

# 题解

## 作者：Vatyr (赞：31)

设a[i]表示第i堆石子的个数，c[i]表示a[i]-a[i-1],则我们每堆可以拿的石子数即为c[i]。当我们在第i堆拿了x个时，c[i]变成了c[i]-x，c[i+1]变成了c[i+1]+x，相当于我们把第i堆中可拿的石子转移到了i+1堆，由此我们可以把此题转化为一道反着的阶梯nim游戏。

下面简单讲解一下阶梯nim，如果不懂的话可以去网上搜一下。

阶梯nim是指，有n堆石子，每次我们可以从第i堆的石子中拿走一部分放到第i-1堆中，或者把第1堆中的石子拿走一部分，无法操作的人算输。先说结论：阶梯nim的游戏结果与只看奇数堆的石子数的普通nim结果相同。

假设我先手，那么我可以按照必胜策略把奇数堆中的石子转移到偶数堆，当对方拿的时候我们分情况讨论：

1. 对方拿奇数堆中的石子到偶数堆，相当于进行对于奇数堆的普通nim，我们继续按照必胜策略拿奇数堆中的石子；

2. 对方把偶数堆的石子拿到奇数堆，则我们可以把这部分石子继续向下拿，对于奇数堆相当于局势没有变动。


以上，我们简单证明了阶梯nim与奇数堆普通nim的等价。下面贴上渣代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int u;
int n;
int a[10004];
int c[10004];
int main()
{
    scanf("%d",&u);
    while(u--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        for(int i=1;i<=n;i++)
            c[i]=a[i]-a[i-1];
        int ans=0;
        for(int i=n;i>=1;i-=2)
            ans^=c[i];
        if(ans)printf("TAK\n");
        else printf("NIE\n");
    }
    return 0;
}
```

一定要注意这道题是从第i堆拿到第i+1堆，所以要反着跑阶梯nim！！


---

## 作者：秋日私语 (赞：27)

Nim游戏基本模型
安利个人blog，感觉写的挺详细的：
http://blog.csdn.net/A_Comme_Amour/article/details/79347291

希望这篇题解能都帮到初学者。
Nim游戏
==



----------


从一个问题进入。

描述
--

今天我们要认识一对新朋友，Alice与Bob。 
Alice与Bob总是在进行各种各样的比试，今天他们在玩一个取石子的游戏。 
在这个游戏中，Alice和Bob放置了N堆不同的石子，编号1..N，第i堆中有Ai个石子。 
每一次行动，Alice和Bob可以选择从一堆石子中取出任意数量的石子。至少取1颗，至多取出这一堆剩下的所有石子。 
Alice和Bob轮流行动，取走最后一个石子的人获得胜利。 
假设每一轮游戏都是Alice先行动，请你判断在给定的情况下，如果双方都足够聪明，谁会获得胜利？

讨论
--

这是一个古老而又经典的博弈问题：Nim游戏。

Nim游戏是经典的公平组合游戏(ICG)，对于ICG游戏我们有如下定义：

 - 两名选手
 - 两名选手轮流行动，每一次行动可以在有限合法操作集合中选择一个
 - 游戏的任何一种可能的局面(position)，合法操作集合只取决于这个局面本身，不取决于轮到哪名选手操作、以前的任何操作、骰子的点数或者其它因素；局面的改变称为“移动”(move)
 - 如果轮到某名选手移动，且这个局面的合法的移动集合为空（也就是说此时无法进行移动），则这名选手负

对于第三条，我们有更进一步的定义Position，我们将Position分为两类：

 1. P-position：在当前的局面下，先手必败
 2. N-position：在当前的局面下，先手必胜

它们有如下性质：

1. 合法操作集合为空的局面是P-position
2. 可以移动到P-position的局面是N-position
3. 所有移动都只能到N-position的局面是P-position

**算法实现**
取子游戏算法实现—— 

> 步骤1:将所有终结位置标记为必败点（P点）；
>步骤2: 将所有一步操作能进入必败点（P点）的位置标记为必胜点（N点）
>步骤3:如果从某个点开始的所有一步操作都只能进入必胜点（N点） ，则将该点标记为必败点（P点） ；
>步骤4: 如果在步骤3未能找到新的必败（P点），则算法终止；否则，返回到步骤2。


在这个游戏中，我们已经知道A[] = {0,0,…,0}的局面是P局面，那么我们可以通过反向枚举来推导出所有的可能局面，总共的状态数量为A1∗A2∗...∗AN。并且每一次的状态转移很多。 
虽然耗时巨大，但确实是一个可行方法。

当然，我们这里会讲这个题目就说明肯定没那么复杂。没错，对于这个游戏有一个非常神奇的结论：

> 对于一个局面，当且仅当A1 xor A2 xor ... xor AN =0时，该局面为P局面。

如何证明这个结论呢？

![这里写图片描述](http://img.blog.csdn.net/20180222132340314?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvQV9Db21tZV9BbW91cg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

#**SG函数**

----------


同样从一个问题进入。

描述
--

给定一个有向无环图和一个起始顶点上的一枚棋子，Alice和Bob交替的将这枚棋子沿有向边进行移动，无法移动者判负。问是否有必胜策略。

讨论
--

事实上，这个游戏可以认为是所有ICG游戏的抽象模型。也就是说，任何一个ICG游戏都可以通过把每个局面看成一个顶点，对每个局面和它的子局面连一条有向边来抽象成这个“有向图游戏”。下面我们就在有向无环图的顶点上定义SG(Sprague-Garundy)函数。

Sprague-Grundy Theorem
-
![这里写图片描述](http://img.blog.csdn.net/20180222144012787?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvQV9Db21tZV9BbW91cg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

SG函数的建立
--

首先定义mex(minimal excludant)运算，这是施加于一个集合的运算，表示最小的不属于这个集合的非负整数。例如mex{0,1,2,4}=3、mex{2,3,5}=0、mex{}=0。

对于一个给定的有向无环图，定义关于图的每个顶点的SG函数sg如下：sg(x)=mex{ sg(y) | y是x的后继 }。也就是说，一个点的SG函数为在它所有后继中都未出现的最小的值。

SG函数的性质
--

来看一下SG函数的性质。首先，所有的没有出边的顶点，其SG值为0，因为它的后继集合是空集。然后对于一个sg(x)=0的顶点x，它的所有后继y都满足 sg(y)≠ 0。对于一个sg(x)≠ 0的顶点，必定存在一个后继y满足sg(y)=0。

这个时候你就应该有所发现了！SG函数的性质和N,P局面的性质非常相似！ 
以上表明，**顶点x所代表的postion是P-position当且仅当sg(x)=0（跟P-positioin/N-position的定义是完全对应的）。**

#####后手必胜当且仅当sg的异或和为0

解题模型
--

举个**栗子**

例如：取石子问题，有1堆n个的石子，每次只能取{1，3,4}个石子，先取完石子者胜利，那么各个数的SG值为多少？
sg[0]=0，f[]={1,3,4},
x=1时，可以取走1-f{1}个石子，剩余{0}个，mex{sg[0]}={0}，故sg[1]=1;
x=2时，可以取走2-f{1}个石子，剩余{1}个，mex{sg[1]}={1}，故sg[2]=0；
x=3时，可以取走3-f{1,3}个石子，剩余{2,0}个，mex{sg[2],sg[0]}={0,0}，故sg[3]=1;
x=4时，可以取走4-f{1,3,4}个石子，剩余{3,1,0}个，mex{sg[3],sg[1],sg[0]}={1,1,0},故sg[4]=2;
x=5时，可以取走5-f{1,3,4}个石子，剩余{4,2,1}个，mex{sg[4],sg[2],sg[1]}={2,0,1},故sg[5]=3；
以此类推.....
  
     x         0  1  2  3  4  5  6  7  8....
     sg[x]     0  1  0  1  2  3  2  0  1....


**过程**
1.把原游戏分解成多个独立的子游戏，则原游戏的SG函数值是它的所有子游戏的SG函数值的异或。

 - 即sg(G)=sg(G1)^sg(G2)^...^sg(Gn)。

2.分别考虑没一个子游戏，计算其SG值。

 - SG值的计算方法：（重点）
1. 可选步数为1~m的连续整数，直接取模即可，SG(x) = x % (m+1);
2. 可选步数为任意步，SG(x) = x;
3. 可选步数为一系列不连续的数，用模板计算。

关于SG(x) = x % (m+1);和SG(x) = x;
![这里写图片描述](http://img.blog.csdn.net/20180222134031870?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvQV9Db21tZV9BbW91cg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

**模板**
两种方法我觉得都是搜索

方法一：打表
f[]可以取走的石子个数,注意f[]需要从小到大排序 
sg[]SG函数值；vis[]标记数组，用于求mex{} 

```
int f[MAXN],sg[MAXN];
bool vis[MAXN];
void getSG(int n)
{
	sort(f+1,f+1+n);
	memset(sg,0,sizeof(sg));
	for (int i=1; i<=n; i++)
	{
		memset(vis,0,sizeof(vis));
		for (int j=1; f[j]<=i; j++)//f排序是为了让每一种取法都循环到
			vis[sg[i-f[j]]]=1;
		for (int j=0; j<=n; j++)
		{
			if (vis[j]==0)
			{
				sg[i]=j; break;
			}	
		}
	}
}
```
方法二：dfs
s数组是定义特殊取法规则的数组，注意要按照从小到大排序；n表示集合大小
SG函数要初始化为-1，每个集合只需初始化一遍 

```
int s[MAXN],sg[MAXN],n;
bool vis[MAXN];
int SG_dfs(int x)
{
	if (sh[x]!=-1)
		return sg[x];
	memset(vis,0,sizeof(vis));
	for (int i=0; i<n; i++)
	{
		if (x>=s[i])
		{
			SG_dfs(x-s[i]);
			vis[sg[x-s[i]]]=1;
		}
	}
	int i=0;
	while (1)
	{
		if (!vis[i])
			return sg[x]=i;
		i++;
	}
}
```
拓展
--

**SG函数与Nim游戏的联系？**
　　如果对于一个游戏，它是ICG。那么我们可以发现，对于此游戏的一种局面，ICG上的多个sg函数的值，如果看做多个石堆的话，就相当于一个nim游戏！我们来一步步推导：

 - 首先来个引理，s≥sg(x)s≥sg(x)，这个用归纳法证，应该说简单。
 - 如果当前局面，所有sg函数的值都是零，先手必输。分类讨论一下。如果当前局面上的所有棋子都不能走了，显然它们的sg函数值都是零，那么先手必输。如果还有棋子能走，我们可以选一个棋子走一步，那么这个棋子的sg函数值就会变成非零。非零说明什么，说明当前棋子所在结点的孩子结点一定有一个sg函数值为零，那对手只要将棋走到那个结点就行了。然后局面就又变成了原来的。
 - 前面那个其实相当于nim游戏的终止局面。那普通局面就相当于有sg函数的值不为零。还是分类讨论。如果现在对手走，sg值异或和为零（注意是异或和），他会选一个石子，然后把这个石子放到它的孩子结点上。sg值有可能增加，也有可能减少。只要sg值增加，你就把它还原回来（根据sg函数的定义，好好思考一下！），那么sg函数总有不能增加的一天，因为第一条的引理。这就相当于sg值只能减少！那这不是一个nim游戏吗？根据nim游戏里面的证明，你一定可以找到一个数，找一个石子堆，减去这个数以后，异或和还是零。最终对手就会被逼迫到第二条的局面上，然后它就输了。反之如果异或和不为零，你一定输！

通过这个sg函数，我们就可以**把所有ICG游戏转换成nim游戏**！

#经典题目
----

一、Nim游戏
-
第一个当然是Nim game；
####Nim游戏的变形
![这里写图片描述](http://img.blog.csdn.net/20180222152434418?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvQV9Db21tZV9BbW91cg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)
![这里写图片描述](http://img.blog.csdn.net/20180222152444640?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvQV9Db21tZV9BbW91cg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)
二、阶梯博弈
-
这也是十分经典的一类题，并且有许多变形

 - 有N堆石子放在N级楼梯上，楼梯编号为1..N（地面为0层），每堆有a[n]个石子。
 - 两人轮流游戏，每次将任意堆j中的任意个石子但至少一个移动到它的相邻层 j - 1。
 - 直到所有石子都移动到地面，最后移动的为胜者。

![阶梯博弈](http://img.blog.csdn.net/20150921132547106?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQv/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/Center)

这种问题只需要考虑奇数的位置进行Nim游戏，因为石子在偶数位置是可以模仿操作的。
为什么呢？因为任何人移动了偶数层的石子后，另外一个人总是可以把他们再移到下一奇数层，那么奇数层拿到偶数层的石子就相当于是丢掉了。
所以就变成了只有奇数层的Nim游戏。

变形1
--
![这里写图片描述](http://img.blog.csdn.net/20180222151920174?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvQV9Db21tZV9BbW91cg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)
可以看做独立的问题，使用sg函数求mex
（为什么可以看做独立的问题？）
变形2
----
![这里写图片描述](http://img.blog.csdn.net/20180222152036769?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvQV9Db21tZV9BbW91cg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)
因为会对以后的台阶造成影响，问题不是独立的。

---

## 作者：zerc (赞：5)

前置芝士：**阶梯 Nim** .

dalao の blog：( 例8 ) [浅谈算法——博弈论 - Wolfycz 的博客](https://www.luogu.com.cn/blog/Wolfycz/qian-tan-suan-fa-bo-yi-lun-zong-ling-kai-shi-di-bo-yi-lun-post) .

> **我们先来看看什么是阶梯 Nim：**
>
> 有 $n$ 堆石子，每堆石子的数量为 $x_{1},x_{2},\dots,x_{n}$，$A,B$ 轮流操作，每次可以选第 $k$ 堆中的任意多个石子放到第 $k-1$ 堆中，第 $1$ 堆中的石子可以放到第 $0$ 堆中，最后无法操作的人为输。问 $A$ 先手是否有必胜策略。

是不是和我们这个题很像，直接套结论就行了（不是 .

仔细看看，还是有很多不一样的，但如果我们只看两堆之间的差值呢？

|      堆      |  0   |  1   |  2   |  3   |
| :----------: | :--: | :--: | :--: | :--: |
| 石子数 ($S$) |  -   |  1   |  2   |  4   |
|  差值 ($D$)  |  1   |  1   |  2   |  -   |

当我们从第 $2$ 堆取出 $1$ 个石子时，$D_{1,2}-1,\ D_{2,3}+1$ ，这不就相当于我们从 $D_{1,2}$ 取 $1$ 个石子到 $D_{2,3}$ ，很好的满足了阶梯 Nim 的要求（只不过是逆序的），也就可以用阶梯 Nim 来求解 .

先说结论：先手必败当且仅当奇数堆中的石子数异或和为 $0$ .

>  **证明过程：**
>
> 假如我们是先手，我们就按照这个方法将多余的石子从奇数堆移动到偶数堆里面。
>
> 此后如果对手移动的是奇数堆，我们就继续移动奇数堆使得 $SG$ 值重新变为 $0$ ；如果对手移动的是偶数堆，我们就将他移动到奇数堆中的石子继续往下移。
>
> 这样经过多次操作我们总能使奇数堆保持必胜状态，最后我们总可以在对手之后将石子从奇数堆移动到偶数堆，最后移动到第 $0$ 堆，这样对手就不能移动了。
>
> 所以通过整个过程我们可以发现，偶数堆中的石子不会影响整个游戏的结果，只有奇数堆中的石子会影响游戏结果。

```cpp
#include<cstdio>
using namespace std;
int T, n, k, input[1111];
int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        k = 0;
        for (int i = 1; i <= n; i++) 
            scanf("%d", &input[i]);
        for (int i = n; i >= 1; i--)
            if ((n - i + 1) & 1)
                k ^= (input[i] - input[i-1]);
        if (k) printf("TAK\n");
        else printf("NIE\n");
    }
    return 0;
}
```

这里对 `(n - i + 1) & 1` 做下解释：前 main ~~（面~~ 我们已经将问题转化为逆序阶梯 Nim，所以我们就要倒序枚举找奇数位，$1,2,3,4$ `n - i + 1` 后就是 $4,3,2,1$ ，这时候再去找奇数就可以了（这个有很多种实现方式，只不过这种比较常见），`& 1` 和 `% 2` 作用相同 .

还有一点就是**多组测试变量清零** . 

$AD:$ [BLOG](https://zerc.tk/) .

---

## 作者：ycyaw (赞：4)

~~博弈论题题都是神仙~~

这题怎么考虑？我们发现石子时刻满足从左到右递增，感觉没什么思路，那么根据博弈论的套路，我们开始。。~~天马行空地乱想~~。

先考虑$SG$函数，发现这题取石子的限制是时刻在变的，显然不行。

然后，这题多堆石子且并不相互独立，没什么表打，打表也滚粗了。

石子个数递增？？是不是长得像阶梯？？(~~大雾~~

顺着这个瞎想的思路，再康一康题目，发现移走一堆石子，它两边石子与它的差值会变。

怎么变呢？设一堆石子移走$x$，显然左边与它的差值$-x$，右边与它的差值$+x$，这不就是阶梯$nim$吗？？

什么？你不知道阶梯$nim$？那你肯定没有好好看[洛咕日报](https://www.luogu.org/blog/Wolfycz/qian-tan-suan-fa-bo-yi-lun-zong-ling-kai-shi-di-bo-yi-lun-post)。这里不详细展开了。

左边与它的差值$-x$，右边与它的差值$+x$，那么显然模型就是一个反向$($从右向左$)$的阶梯，做一遍阶梯$nim$，问题解决。

博弈论代码真的短：
```cpp
#include<bits/stdc++.h>
#define ts cout<<"ok"<<endl
#define ll long long
#define hh puts("")
using namespace std;
int n,a[1005];
inline int read(){
    int ret=0,ff=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-') ff=-ff;ch=getchar();}
    while(isdigit(ch)){ret=ret*10+(ch^48);ch=getchar();}
    return ret*ff;
} 
signed main(){
    int T=read();
    while(T--){
        n=read();
        int ans=0;
        for(int i=1;i<=n;i++) a[i]=read();
        for(int i=n;i>=1;i--)
            if((n-i+1)&1)
                ans^=(a[i]-a[i-1]);
        puts(ans?"TAK":"NIE");
    }
    return 0;
}
```


---

## 作者：大菜鸡fks (赞：4)

对于数组差倒着做阶梯nim。

阶梯nim本质就是级数阶的普通nim


```cpp
#include<cstdio>
using namespace std;
inline int read(){int x=0,f=1,ch=getchar(); while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();} while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();} return x*f;}
int ans,n,last;
int main(){
	int T=read();
	while (T--){
		n=read();
		ans=last=0;
		for (int i=1;i<=n;i++){
			int x=read();
			if ((n-i+1)&1) ans^=(x-last);
			last=x;	
		}
		puts(ans?"TAK":"NIE");
	}
	return 0;
}
```

---

## 作者：DengDuck (赞：3)

# 什么是阶梯博弈？

我们在一个阶梯上进行取石子游戏，每次可以将任意一个台阶上的石子向下一级台阶转移一些。

最后，第一个将所有石子转移到第 $0$ 级台阶者胜。

怎么做呢？我们想想，第 $0$ 级台阶就是偶数级台阶，是不是如果石子都在偶数台阶则先手必败？否则必胜？

不难发现是这样的，如果石子都在偶数台阶，先手无论怎么操作，后手都可以再操作，使得所有石子仍然都在偶数台阶。

因此不难想到对奇数级的台阶做一个 Nim 博弈，博弈的胜负就是答案。

# 本题思路

注意到要维护石子堆不递减，相当于石子堆之间的差非负，不难想到对石子堆的差分数组做阶梯博弈。

具体地，我们注意到，对于原数组取一些石子，相当于对前一项差分数组石子堆取石子放在后一项差分石子堆，同时满足要求，因此是形成对应的。

注意：阶梯博弈的方向是左边在上，右边在下的。

```cpp
#include<bits/stdc++.h>
#define LL long long 
using namespace std;
const LL N=1e5;
LL T,n,a[N+5],sum; 
int main()
{
	cin>>T;		
	while(T--)
	{
		cin>>n;
		sum=0;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			if((n-i+1)&1)sum^=(a[i]-a[i-1]);
		}
		if(sum==0)
		{
			puts("NIE");
		} 
		else
		{
			puts("TAK");
		}
	}
} 
```

---

## 作者：dhsheng (赞：2)

注：本篇题解为半萌新向，

知道什么是 nim 游戏的跳到第二章；

知道什么是阶梯 nim 的跳到第三章；

~~只是想看代码的去第四章；~~

---

# 一：nim 游戏

nim 游戏规则：
有 $n$ 堆石子，数量分别为 $ a_1,a_2,a_3,\cdots,a_n $。
两个玩家轮流拿石子，每次从任意一堆中拿走任意数量的石子，拿到最后一个石子的玩家获胜。

如何判断胜负？对于任意的 $ a_1,a_2,a_3,\cdots,a_n $，nim 游戏有一个很简单的判断胜负的方法。

**定理1：**

若 $ a_1 \operatorname{xor} a_2 \operatorname{xor} a_3 \operatorname{xor} \cdots \operatorname{xor} a_n = 0$，则先手必败。
 
若 $ a_1 \operatorname{xor} a_2 \operatorname{xor} a_3 \operatorname{xor} \cdots \operatorname{xor} a_n \neq 0$，则先手必胜。

在 nim 游戏中进行的异或运算一般被称为 **Nim-sum** 运算。

下面对该定理进行简单证明：

1. 若先手处于必胜点，则先手必然可以将局势转化为必败点。为什么？我们任选一堆石头，例如第 $i$ 堆，石头数量为 $a_i$；对剩下的 $n-1$ 堆进行异或运算，设结果为 $H$。若 $H < k$，就把第 $i$ 堆石头减少到 $H$ 个。因为 $H \operatorname{xor} H = 0$，所以这样操作以后 $n$ 堆石头的异或等于 $0$。可以证明，总会存在这样的第 $i$ 堆石头。

2. 若先手处于必败点，则先手必然只能转移到必胜点。因为先手不论取哪堆，取多少，都会使得这一堆的二进制表达至少产生一位不同，导致异或值改变。

3. 当所有石子取完时，显然为先手必败点（可以看作后手在上一轮取走了最后一个石子），又所有石头此时异或值为 $0$，证毕。

---

# 二：阶梯 nim 游戏

阶梯 nim 规则：

有 $n$ 堆石子，数量分别为 $ a_1,a_2,a_3,\cdots,a_n $。
两个玩家轮流进行以下操作：

1. 从第 $i$ 堆石子中移动任意颗石子到第 $i - 1$ 堆中（$i \ge 2$）。
2. 从第一堆石子中移除任意颗石子。

这东西和 nim 游戏有啥关系啊？

关系就在：

**定理二：**

阶梯 nim 的结果与只看奇数堆的普通 nim 是**一样**的。

证明如下：

1. 若对手将奇数堆的石子移至偶数堆，则相当于是在奇数堆中清除了这些石子。

2. 若对手将偶数堆的石子移至奇数堆，则可以将这些石子从奇数堆再移回偶数堆，相当于“抵消”了这次对手的行动。

Q：为啥阶梯 nim 的结果不是与只看偶数堆的普通 nim 一样？证明起来好像只用把奇偶调换一下就可以了啊？

A：关键就在于那个“抵消”操作。若对手将第二堆中的石子挪到第一堆，就无法再将那些石子移回偶数堆了。

# 三：本题思路
看到这一题的特殊要求“每堆石子个数都不少于前一堆的石子个数”时，首先考虑差分。因为这个条件可以使差分中的每一项均为正。

设 $c_i = a_i - a_{i - 1}$，其中第一项 $c_1 = a_1$。

好像没什么感觉。我们拿走一些石子试试。

从第 $i$ 堆中取走 $x$ 颗石子，则 $c_i$ 变为 $c_i - x$，$c_{i + 1}$ 变为 $c_{i + 1} + x$。

和阶梯 nim 神似有木有？只不过变成从前往后拿，所以需要倒着取奇数堆。

那么……

# 四：代码奉上

因为上面写的很详细就不加注释了

```cpp
#include <iostream>
using namespace std;

int c[1001];

int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		int n;
		cin >> n;

		int la = 0;
		for (int i = 1; i <= n; i++)
		{
			int z;
			cin >> z;
			c[i] = z - la;
			la = z;
		}

		int nim_sum = 0;
		for (int i = n; i > 0; i -= 2)
		{
			nim_sum ^= c[i];
		}
		nim_sum ^= 0;

		if (nim_sum == 0)
		{
			cout << "NIE" << endl;
		}
		else
		{
			cout << "TAK" << endl;
		}
	}
}

```

---

## 作者：Purslane (赞：1)

## Solution

博弈论 .

首先要满足单调不降 , 这启示我们使用差分 .

差分之后 , 我们发现 , 取走一些石子 , 本质是把它从差分序列中往右移动一些 . 这个序列最右边是垃圾桶 , 石子扔进去就拿不出来了 .

我们大胆猜测 : 必胜条件等价于所有石子数异或起来不等于 $0$ , 模仿 Nim 游戏 . 真的是这样吗 ?

我们判断给先手必胜找到一个充分必要条件 , 需要满足一下特征 :

- 最终状态是这个条件的反命题 .
- 必胜状态可以转移为必败状态 .
- 必败状态只能转化为必胜状态 .

考虑到我们是把一堆石子往右移 , 变了 $2$ 堆 , 所以不好控制 .

考虑研究所有从右往左的奇数位置 , 看他们异或起来不等于 $0$ 能否满足 .

- 最终状态 , 所有非垃圾桶的石子堆都没有石子 , 满足 .
- 如果现在异或起来等于 $0$ , 随便改一个就可以啦 .
- 如果现在异或起来不等于 $0$ . 考虑异或和最高位是 $a$ 位 . 那么必有一堆石子 $a$ 位有值 . 那么把这堆石子上异或和是 $1$ 的位全部去反 . 不难发现 , 最终这堆石子数量变小 , 这是可以做到的 .

为什么不能从左往右编号呢 ? 因为假设石子堆数是偶数 , 如果只有最后一堆有值 , 那么它扔到垃圾桶的时候 , 我们要求的异或是不改变的 , 但它就胜了 . 所以我们的编号需要每次取石子都能改变答案 , 就这么做了 .

code 

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1000+10;
int T,n,a[MAXN];
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--) {
		int n;cin>>n;
		ffor(i,1,n) cin>>a[i];
		int ans=0;
		ffor(i,1,n) if((n-i+1)&1) ans^=(a[i]-a[i-1]);
		if(ans) cout<<"TAK\n";
		else cout<<"NIE\n";
	}
	return 0;
}
```

---

## 作者：Aonynation (赞：1)

#### [我的 cnblogs](https://www.cnblogs.com/Oier-GGG/articles/16193652.html)

#### [题目链接](https://www.luogu.com.cn/problem/P3480 "题目链接")

首先，这道题看上去就是个博弈论，很显然的 $\text{Nim}$ 游戏。

因为每一个的取法都和它的上一位有关。

有一种非常显然的转换方式 ：**我们把这若干堆石子从前向后做一个差分** 。

我们记 $a_i-a_{i-1}=b_i$

题目转化成：
>对于若干堆石子，第 $i$ 堆石子的个数是 $b_i$ ，问先手是否必胜？

好像有点问题：

因为所有的石子都是动态变化的。

很显然当一个石子堆变化时，它和它后面一个石子堆的差分结果一定会变化。

所以最传统的 $\text{Nim}$ 游戏显然是不可行的。

考虑阶梯 $\text{Nim}$ 游戏。

我们可以把每一个差分的结果都映射到一个阶梯上。

很容易发现：我们对于每一堆石子的任意一个操作都可以通过在阶梯上移动实现。
（本人较懒，图片就咕咕咕了）

当我们发现所有的石子都移到最上层的台阶时。

可以看出所有的差都变成了 $0$ ，也就是说所有的都一样。

显然此时会分出胜负。

#### Code
```cpp
#include <bits/stdc++.h>

const int N = 100005;

int T, n, a[N];

signed main(void) {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0); std::cout.tie(0);
  std::cin >> T;
  for (int test = 1; test <= T; test ++) {
    std::cin >> n;
    int ans = 0;
    for (int i = 1; i <= n; i++) {
      std::cin >> a[i];
      int num = a[i] - a[i - 1];
      if ((n - i) % 2 == 0) ans ^= num; 
    }
    if (ans == 0)
      std::cout << "NIE" << std::endl;
    else
      std::cout << "TAK" << std::endl;
  }
}
```

---

## 作者：半笙、凡尘 (赞：1)

#[POI2009]KAM-Pebbles
 - 唉，又是一题博弈论，我们先来康康题面；
 - 首先，我们可以发现题目中有一句话是这样的：每堆石子个数都不少于前一堆的石子个数。于是，我们可以很~~容易~~地想到一个模型-- **阶梯**。
 - 然后继续看题面，是不是感觉有点相似，这不是Nim游戏吗？
![](https://i.loli.net/2020/05/06/d6Qjrk5pWJBTNLU.png)
 - 哎，把我们想到的模型和Nim游戏综合起来，就有了一个名字：**Staircase Nim** 也叫阶梯Nim。
 - 不懂阶梯Nim可以下面这张图片，转载自[Wolfycz 洛谷博客](https://www.luogu.com.cn/blog/Wolfycz/qian-tan-suan-fa-bo-yi-lun-zong-ling-kai-shi-di-bo-yi-lun-post)
![](https://i.loli.net/2020/05/06/vZHUJec7EhI3QGt.png)
 - 显然，这题就是一个从右至左的阶梯，图片里说得很详细了，就不再补充了。
 - 接下来就是一点也不激动人心的代码了：

```cpp
#include<bits/stdc++.h>//Forever_chen
#define RT register
using namespace std;
template<class t> inline t read(t &x){
	char c=getchar();bool f=0;x=0;
	while(!isdigit(c)) f|=c=='-',c=getchar();
	while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();
	if(f)x=-x;return x;
}
template<class t>inline void write(t x){
	if(x<0)putchar('-'),write(-x);
	else{if(x>9)write(x/10);putchar('0'+x%10);}
}
template<class t>inline void writeln(t x){
	write(x);putchar('\n');
	return;
}
template<class t>inline void write_blank(t x){
	write(x);putchar(' ');
	return;
}
int tt,n,a[1010],ans; 
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	read(tt);
	while(tt--){
		read(n);
		ans=0;
		for(int i=1;i<=n;i++){
			read(a[i]);
		}
		for(int i=n;i>=1;i--){
			if((n-i+1)&1){
				ans^=(a[i]-a[i-1]);
			}
		}
		if(ans!=0){
			printf("TAK\n");
		}else{
			printf("NIE\n");
		}
	}  
	//system("pause");
	return 0;
}

```


---

## 作者：鸢一折远 (赞：1)

<http://www.cnblogs.com/mjy0724/p/4465355.html>

博客上讲的很全，不过是Pascal的，下面是我的C++代码

只有18行

```cpp
#include<iostream>
#include<cstdio>
#define F(i,s,t) for(int i=s;i<=t;i++)
using namespace std;
int T,n,ans;
int a[100001];
int main(){
    scanf("%d",&T);
    while(T--){
        ans=0;
        scanf("%d",&n);
        F(i,1,n) scanf("%d",&a[i]);
        for(int i=n;i>1;i-=2) ans^=(a[i]-a[i-1]);
        if(n&1) ans^=a[1];
        printf(ans?"TAK\n":"NIE\n");
    }
    return 0;
}
```

---

## 作者：qzhwlzy (赞：0)

## 题目大意

有 $n$ 堆石子，初始第 $i$ 堆有 $a_i$ 个，两人轮流操作，从一堆里面取出若干，但要时刻保证石子数量单调递增。问先手是否必胜。

## 思路

因为要保证 $a$ 单调递增，只需要保证差分数组 $d_i = a_i-a_{i-1}$ 恒大于 $0$。在一次操作后，假设从第 $i$ 堆中取走 $\Delta a$ 个石子，那么序列从 $\ldots,\,a_{i-1}\ ,\ a_i\ ,\ a_{i+1},\,\ldots$ 变为 $\ldots,\,a_{i-1}\ ,\ a_i+\Delta a\ ,\ a_{i+1},\,\ldots$，差分数组从 $\ldots,\,d_i\ ,\ d_{i+1},\,\ldots$ 变为 $\ldots,\,d_i-\Delta a\ ,\ d_{i+1}+\Delta a,\,\ldots$，把差分数组看做 $n$ 堆石子，上述操作可以看做是从第 $i$ 堆石子中拿出 $\Delta a$ 个移到第 $(i+1)$ 堆。

此时我们发现题目转化成了一个阶梯 Nim，于是直接使用结论求解即可。

```cpp
#include<iostream>
#include<cstdio>
#define maxn 1005
using namespace std;
int T,n,a[maxn],d[maxn],sgsum=0;
int main(){
	scanf("%d",&T); while(T--){
		scanf("%d",&n); for(int i=1;i<=n;i++){scanf("%d",&a[i]); d[i]=a[i]-a[i-1];}
		sgsum=0; for(int i=n;i>=1;i-=2) sgsum^=d[i]; if(sgsum==0) printf("NIE\n"); else printf("TAK\n");
	} return 0;
}
```

---

## 作者：XL4453 (赞：0)

### 解题思路：

好像是叫阶梯博弈。

直接处理每一个位置上的大小关系会非常麻烦，可以考虑将每一个位置和前一个位置作差。

这样处理完之后问题也就转化为了有若干堆石子，每一次操作可以将某一堆中的任意数量的石子放入右边一堆，或者将最右边一堆中的任意数量的石子移除。无法进行操作时算输。

---
在转化后的问题中，先考虑从右往左数的偶数位置上的石子，这些石子在某一个人往右边移动之后，另一个玩家就立即可以将同样多数量的石子进行移除，不会对结果造成任何影响。

而对于奇数组的石子，其实是和普通的 $\text{NIM}$ 游戏一样的，这些石子在移动到偶数位置之后将不会对游戏造成任何额外的影响，也就是“被移除”了。

最后的结论就是将所有的从右往左数的奇数位置上的数的异或和统计出来，简单地判断一下就行了。


---
### 代码：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int T,n,q,x,fi,la,sum_e,sum_o,now,opt;
int main(){
	scanf("%d",&T);
	while(T--){
		sum_o=sum_e=now=la=fi=0;
		scanf("%d",&n);
		now=0;
		for(int i=1;i<=n;i++){
			scanf("%d",&x);
			if(i==1)fi=x;
			now^=1;
			if(now==1)sum_o^=x-la;
			else sum_e^=x-la;
			la=x;
		}
		if(n&1)printf(sum_o==0?"NIE\n":"TAK\n");
		else printf(sum_e==0?"NIE\n":"TAK\n");
	}
	return 0;
}
```


---

## 作者：Mars_Dingdang (赞：0)

阶梯 NIM 的经典题。

## 问题描述

有 $n$ 堆石子，除了第一堆外，每堆石子个数都不少于前一堆的石子个数。两人轮流操作每次操作可以从一堆石子中移走任意多石子，但是要保证操作后仍然满足初始时的条件谁没有石子可移时输掉游戏。问先手是否必胜。

## 大体思路
首先，先来看什么是阶梯 NIM。这里借用 @Wolfycz 在日报中的说明：

>有 $n$ 堆石子，每堆石子的数量为 $x_{1},x_{2},...,x_{n}$， A,B 轮流操作，每次可以选第 $k$ 堆中的任意多个石子放到第 $k-1$ 堆中，第 $1$ 堆中的石子可以放到第 $0$ 堆中，最后无法操作的人为输。问 A 先手是否有必胜策略。

![](https://cdn.luogu.com.cn/upload/image_hosting/ls2u4665.png)

阶梯 Nim 其实可以通过一些转化变成我们所熟知的 Nim 游戏，先手必败当且仅当奇数阶梯上的石子数异或和为 $0$，那么为什么是这样呢？

假如我们是先手，我们就按照这个方法将多余的石子从奇数堆移动到偶数堆里面。

此后如果对手移动的是奇数堆，我们就继续移动奇数堆使得 SG 值重新变为 $0$；如果对手移动的是偶数堆，我们就将他移动到奇数堆中的石子继续往下移。

这样经过多次操作我们总能使奇数堆保持必胜状态，最后我们总可以在对手之后将石子从奇数堆移动到偶数堆，最后移动到第 $0$ 堆，这样对手就不能移动了。

所以通过整个过程我们可以发现，偶数堆中的石子不会影响整个游戏的结果，只有奇数堆中的石子会影响游戏结果。

因此对这个游戏而言，先手必败当且仅当奇数堆中的石子数异或和为 $0$。

______________

回到本题。由于题目中提到石子数 $a_i$ 递增，自然想到差分数组 $d_i=a_i-a_{i-1}$，考虑每次从 $a_i$ 拿走 $x$ 个，相当于 $d_i'=d_i-x,d_{i+1}'=d_{i+1}+x$。

再观察阶梯 NIM 中，每次 $a_i'=a_i-x,a_{i-1}'=a_{i-1}+x$，因此相当于编号为 $n\sim 1$ 的数组 $d$ 做阶梯 NIM，考虑奇数位异或和 $sum=d_n\oplus d_{n-2}\oplus d_{n-4}\oplus\cdots$，若 $sum=0$ 则后手胜，否则先手胜。

## 完整代码
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define rep(ii,aa,bb) for(re int ii = aa; ii <= bb; ii++)
#define Rep(ii,aa,bb) for(re int ii = aa; ii >= bb; ii--)
typedef long long ll;
typedef unsigned long long ull;
const int maxn = 1e4 + 5;
namespace IO_ReadWrite {
	#define re register
	#define gg (p1 == p2 && (p2 = (p1 = _buf) + fread(_buf, 1, 1<<21, stdin), p1 == p2) ? EOF :*p1++)
	char _buf[1<<21], *p1 = _buf, *p2 = _buf;
	template <typename T>
	inline void read(T &x){
		x = 0; re T f=1; re char c = gg;
		while(c > 57 || c < 48){if(c == '-') f = -1;c = gg;}
		while(c >= 48 &&c <= 57){x = (x<<1) + (x<<3) + (c^48);c = gg;}
		x *= f;return;
	}
	inline void ReadChar(char &c){
		c = gg;
		while(!isalpha(c)) c = gg;
	}
	template <typename T>
	inline void write(T x){
		if(x < 0) putchar('-'), x = -x;
		if(x > 9) write(x/10);
		putchar('0' + x % 10);
	}
	template <typename T>
	inline void writeln(T x){write(x); putchar('\n');}
}
using namespace IO_ReadWrite;
int T, n, a[maxn], d[maxn];//原数组及差分数组
int main() {
	read(T);
	while(T--) {
		read(n);
		int sum = 0;
		rep(i, 1, n) {
			read(a[i]);
			d[i] = a[i] - a[i - 1];
		}
		for(int i = n; i >= 1; i -= 2) 
			sum ^= d[i];//阶梯 NIM 奇数位异或和
		if(!sum) puts("NIE");
		else puts("TAK");
	}
	return 0;
}
```

---

