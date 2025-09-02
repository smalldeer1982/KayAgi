# Haywire

## 题目描述

Farmer John有 $N$ 只奶牛（$4 \leq N \leq 12$，$N$ 是偶数）。

他们建立了一套原生的系统，使得奶牛与他的朋友可以通过由干草保护的线路来进行对话交流。


每一头奶牛在这个牧场中正好有 $3$ 个朋友，并且他们必须把自己安排在一排干草堆中。


一条长 $L$ 的线路要占用刚好 $L$ 堆干草来保护线路。


比如说，如果有两头奶牛分别在草堆 $4$ 与草堆 $7$ 中，并且他们是朋友关系，那么我们就需要用 $3$ 堆干草来建造线路，使他们之间能够联系。


假设每一对作为朋友的奶牛都必须用一条单独的线路来连接，并且我们可以随便地改变奶牛的位置，请计算出我们建造线路所需要的最少的干草堆。


## 说明/提示

样例解释： 奶牛最好的排列是 `6, 5, 1, 4, 2, 3`, 这个时候我们只需要 $17$ 个单位的干草堆。


## 样例 #1

### 输入

```
6
6 2 5
1 3 4
4 2 6
5 3 2
4 6 1
1 5 3```

### 输出

```
17```

# 题解

## 作者：ArachnidaKing (赞：27)

~~题外话：有人说模拟退火是对一道好题的不敬，我说要是会写正解我自然会表示出对该题的敬意QAQ~~  
## 首先声明！本题是一道模拟退火的练手好题！
模拟退火的概念较为简单，不懂的同学们可以先了解一下[此篇洛谷日报](https://m-sea.blog.luogu.org/qian-tan-SA)。  
本题虽为黑题，但实则比[P1337 [JSOI2004]平衡点 / 吊打XXX](https://www.luogu.org/problemnew/show/P1337)简单一些。此篇题解不对模拟退火点的概念过多赘述，如有不懂可以看一下某位机房大佬~~（大机佬）~~的[博客](https://ciyang.blog.luogu.org/solution-p2210)。这位大佬对模拟退火本身的讲解多，适合模拟退火入门的同学们。此篇题解对题目本身讲解多，以便同学们可以快速学会实际应用并可以类比用于其他题目。请同学们各取所需~  
#### 讲解尽在注释中——
```cpp
#include<cstdio>
#define tin int//以下9行防手残
#define itn int
#define tni int
#define nit int
#define nti int
#define pritnf printf
#define scnaf scanf
#define retrun return
#define sizoef sizeof//以下9行是我懒 
#define ld long double
#define inl inline
#define br break
#define con continue
#define mst(a,b) memset(a,b,sizeof(a))
#define fora(x,a,b) for(re tni x=a;x<=b;++x)
#define forb(x,a,b) for(re nit x=a;x>=b;--x)
#define re register
#define stt struct
#define infa 0x3f3f3f3f
#define infb 0x7fffffff
#define infd 0x7f
#define abss(x) ((x)>(0)?(x):(-1)*(x))
#define maxx(a,b) ((a)>(b)?(a):(b))//Tips：实测max()比大/小于计算慢了不止一点，所以自己写~ 
#define minn(a,b) ((a)<(b)?(a):(b))
#define pf(_) ((_)*(_))
typedef long long ll;
using namespace std;
const nit maxa=14;
const nit maxb=20;
const nit maxc=10;
#include<cstring>
#include<ctime>
#include<cstdlib>
#include<cmath>
//下面是四个参数，自己写模拟退火的时候多调一调，这便是模拟退火精髓所在。 
const double zhongzhishijian=0.998;//终止时的时间，不一定要开这么大！（建议理解一下，考试时卡时限专用）
const double zhongzhiwendu=1e-16;//终止时的温度（循环边界，停止条件）
const double dertT=0.99;//每次温度变化量（每次循环，当前温度*这个数） 
const double chushiwendu=1e7;//初始温度（不会模拟退火的话可以理解成对循环变量T初始化为一个较大数） 

tni n,f[maxa][4],p[maxa]={0},pp[maxa]={0},rc=0,lsc,x,y;
/*
	小蒟蒻最讨厌那些题解起一堆莫名其妙的字母、单词简称作变量名，经常让我看不懂！QAQ所以这里极力避免 
	n（Number of cows）：数据总数（牛的头数）。 
	f（friends）[i][j]：记录第i头牛的第j个好姬友。 
	p（最初地址/位置）[i]：存第i头牛的位置，用于作为每次循环开始时对pp[]赋值用的标准。
	pp（当前地址/位置）：记录一次退火过程（循环过程）中牛们的实时位置。每退火一次，它就被p[]重新赋一次值，一点都不自由（雾）。 
	rc（Result Cost）：最终结果（全局最小化费）。 
	lsc（临时c（Lin Shi Cost））：“临时”用于与“全局当前最优值”rc区分。顾名思义，每次循环时被临时算出、使用、比较、抛弃（被覆盖）的值。 
*/ 

inl tni qh();//（求和（Qiu He）：用于一次退火中每次循环求出当前解的优劣情况（具体看后面啦））。 
inl void exc(tin x,tni y);//交换函数（EXChange）：用于将玄（随）学（机）求（得）出（到）的两头牛位置进行交换。
inl tni sj(tni a,tni b);//随机（Sui Ji）：用于科学地得出结果的函数。 

tni mian()//主函数 
{
	srand(time(NULL));//最基本的随机种子 
	srand(rand()+19260817);//来自东方的神秘力量保佑我 
	srand(rand()+20021110);//我 保佑 我自己 
	srand(rand());//最后玄学一波 
	//
	scanf("%d",&n);//输入牛的数目 
	fora(i,1,n)//宏定义的for循环编写方便，意为：循环变量i从1（register int i=1;）循环至n（i<=n;++i） 
	{
		fora(j,1,3)
		{
			scanf("%d",&f[i][j]);//读入好姬友 
		}
		p[i]=i;//为标准位置（初始位置）赋值（不会变） 
		pp[i]=i;//为一开始的即时位置赋初值（这里随意，用那个随机打乱函数都行）——是“赋初值”不是“赋值”，说明这个数组会改变，而上一个不会。 
	}
	rc=qh();//用当前位置pp跑一边求和函数，得到初始解，用以以后被替换（本题求最小值，如果初值赋为零，srand（1......7）也救不了你），与rc=INF同作用。 
	//
	while((clock()/(1.0*CLOCKS_PER_SEC))<=zhongzhishijian)//卡时专用，本人不太会描述，不懂的可以参见上面Ciyang的博客 
	{
		lsc=rc;//每次循环用以作为临时值的lsc， 
		fora(i,1,n)
		{
			pp[i]=p[i];
		}
		//
		for(re double T=chushiwendu;T>=zhongzhiwendu;T*=dertT)//降温过程
		{
			do//随机生成一组x，y两个数，表示交换pp数组中x，y位置的两头（天选之）牛 
			{
				x=sj(1,n);//1-n的随机数
				y=sj(1,n);//1-n的随机数，可能等于x 
			}
			while(x==y);//理想状态下x！=y，但这样的概率还是有的不是吗？所以为了保险，只要相等就再随机生成一组（就看哪位欧皇在这个地方循环次数太多TLE了·^v·^）。 
			exc(x,y);//交换x，y位置的两头（天选之）牛。 
			lsc=qh();//求出交换后的花费，仅作临时比较之用。
			if(lsc<=rc)//如果比全局最优解都优，还等什么，快赋给全局最优解啊！ 
			{
				rc=lsc;
			}
			//如果当前临时解比最优解差，我们也暂时不能扔！见下-> 
			else if((1.0*exp(rc-lsc))/T>(1.0*rand()/RAND_MAX))//以一定的概率接受较差的新解，具体讲解见上面贴的Ciyang大佬的博客 
			{
				exc(x,y);//换回去（不换回去（即接受命运的审判（较差的新解））的概率会越来越低，可以自行理解，exp函数用法见Ciyang大佬的博客） 
			}
		}
	}
	//
	printf("%d\n",rc/2);//为什么除以二？其实我们计算过程中一直得到的都是答案的2倍——每条a-b的路，计算a时算了一次，计算b时又算了一次（它好委屈）！ 
	return 0；//完美收官 
}

inl void exc(tin x,tni y)//互换基本操作 
{
	tni z=pp[x];
	pp[x]=pp[y];
	pp[y]=z;
	//
	return;
}

inl tni sj(tni a,tni b)//同为基本操作 
{
	return rand()%(b-a+1)+a;
}

inl tni qh()//sun是（每条路被算两次的）花费和！ 
{
	tni sum=0;
	fora(i,1,n)
	{
		fora(j,1,3)
		{
			sum+=abss(pp[i]-pp[f[i][j]]);
		}
	}
	//
	return sum;//如果你愿意，大可以return sum/2;然后输出的时候不/2~ 
}//本代码已进行防抄袭处理，欢迎复制粘贴并顺利CE！·^v·^ 
```
替Ciyang大佬做了这么多广告……QAQ  
挂一波友链：[Ciyang大佬](https://www.luogu.org/space/show?uid=109815)  
顺便一提，用本题解参数跑出来会刚好每个点均为1000ms！实际上跑个200-300次就够了。

---

## 作者：Ciyang (赞：22)

## 此题一眼就看出是模拟退火模板题,写个模板就过了...
### 题目分析与思路:
此题要设置 N 个牛的位置,使每个牛与他的3个朋友的距离之和最小,并且  N  个牛的位置是 1 - N ,那么很容易想到,模拟退火中交换两个牛的位置,并随温度的大小,几率接受较差的排列方式就行了.
如果不知道[模拟退火](https://baike.baidu.com/item/%E6%A8%A1%E6%8B%9F%E9%80%80%E7%81%AB)是什么,可以自行看一下百科   
### 如果还不懂,我的凭自己的能力解释(瞎搞)一下:   
先放张一次模拟退火过程的示意图(来自wikipedia)  
![模拟退火](https://upload.wikimedia.org/wikipedia/commons/d/d5/Hill_Climbing_with_Simulated_Annealing.gif)     

此动态图片就是搜索最优解(最大函数值),在开始时先随便设置一个 X 坐标,计算函数值 Y ,设为当前最优解.   
毕竟算法名为模拟退火,顾名思义,那么起始的温度一定很高(~~不然怎么退火~~),所以每次搜索时 X 坐标的增大或减少量变化很大.认真观察这幅图片上温度值较高时的 X 坐标变化量,会发现波动很大.   
在每次改变 X 坐标后,就计算函数值 Y 坐标,称作当前解.如果当前解比最优解大,就更新最优解.如果当前解不如最优解,那么就会以一定几率接受.这样才会跳出当前当前最优解,才可能找到更优解.   
几率接受的几率是个很玄学的问题,通常情况,设当前温度为$ T $,当前解为$ k $,最优解为$ K_{max} $,我们通常用这样一个玄学公式...  
```cpp
exp((k-kmax)/T)<(double)rand()/RAND_MAX
```
我当初也不知道[exp](https://baike.baidu.com/item/exp)的意义何在,后来发现太妙了!如果不知道exp是啥,可以自己看一下百科,我稍作解释:
 exp函数在X < 0时, Y 一定为 0 - 1 之间的小数且单调递增,(double)rand()/RAND_MAX也是一个 0 - 1 之间的小数.这样温度越小,接受当前较差解的几率越低.
### 模拟退火最重要的三个参数,起始温度,终止温度,温度变化速度
这三个需要自己设置,起着改变准确率,精度,时间复杂度,较差解接受几率的作用,但这个题比较水,随便设置的差不多就能过
### 理解了模拟退火,就可以开始写这道题了.
这道题是找最小值,也是一样的思路.只需要写一个用来求当前的建造线路所需要的干草堆的函数和模拟退火过程函数.然后一直搜,多跑几次模拟退火全过程就行了
### 代码实现:
#### 评测详情
#### Accepted  100
#### 用时: 1903ms / 内存: 848KB
```cpp
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <queue>
#include <map>
#include <limits.h>
using namespace std;
namespace Ciyang {
	struct q_instream {
		template < typename classT >
		inline q_instream operator>>(classT &e) const {
			e= 0;
			classT f= 1, c= 0;
			while(c < '0' || c > '9') {
				if(c == '-') f= -1;
				c= getchar();
			}
			while(c >= '0' && c <= '9') e= e * 10 + c - '0', c= getchar();
			return e= e * f, (*this);
		}
	} qin;
    //读入优化
	struct q_outstream {
		template < typename classT >
		inline q_outstream operator<<(const classT &e) const {
			if(e < 0) {
				putchar('-');
				(*this) << -e;
			}
			else {
				if(e > 9) (*this) << (e / 10);
				putchar(e % 10 + '0');
			}
			return (*this);
		}
		inline q_outstream operator<<(const char &c) const {
			return putchar(c), (*this);
		}
	} qout;
    //输出优化
}  // namespace Ciyang
using namespace Ciyang;
//前面全部为读入输出优化
int n, f[13][3], pos[13], best_ans= INT_MAX;
template < typename T >
T absi(T a) {
//求绝对值函数,也可以用自带的abs.
	return a > 0 ? a : -a;
}
int get_cost() {
//求需要干草堆数量的函数
	int tmp_ans= 0;
	for(int i= 1; i <= n; i++) {
		for(int j= 0; j < 3; j++) {
			tmp_ans+= absi(pos[i] - pos[f[i][j]]);
            //每个牛与三个朋友的坐标差的绝对值相加
		}
	}
	return tmp_ans;
    //得出当前解
}
const double BeginT= 10000, EndT= 1e-12, ChangeT= 0.99;
//起始温度,终止温度,温度改变速度
void SA(int times) {
//模拟退火过程
	int x, y, tmp_ans;
	while(times--) {
		for(double T= BeginT; T > EndT; T*= ChangeT) {
			do {
				x= rand() % n + 1;
				y= rand() % n + 1;
			} while(x == y);
			swap(pos[x], pos[y]);
            //任意交换两个牛的位置
			tmp_ans= get_cost();
            //求出当前解
			if(tmp_ans <= best_ans) {
				best_ans= tmp_ans;
                //更优就更新答案
			}
			else if(exp((best_ans - tmp_ans) / T) > (double)rand() / RAND_MAX) {
            //条不接收较差的条件
				swap(pos[x], pos[y]);
                //不接受较差解,将两个牛位置交换回去
			}
		}
	}
	return;
}
int main() {
	srand(time(0));
    //随机种子,看人品
	qin >> n;
	for(int i= 1; i <= n; i++) {
		for(int j= 0; j < 3; j++) {
			qin >> f[i][j];
		}
		pos[i]= i;
        //设置每个牛的初始坐标就是自己的编号
	}
	SA(275);
	qout << best_ans / 2 << '\n';
    //计算时每两个牛的距离都算了都两遍
	return 0;
}
```
### 备注:模拟退火275次就行,试了几遍都过了,如果WA了就调大点次数
#### 希望更多同学能切掉这个黑题(简直是模板题,感觉难度最多紫题)
#### 如果想继续练习模拟退火,可以做[P1337 [JSOI2004]平衡点 / 吊打XXX](https://www.luogu.org/problemnew/show/P1337)

---

## 作者：HNFMS_tomoo (赞：14)

# 洛谷P2210 [Haywire]
怎么说。。。第一次碰见如此简单的黑题。。。

总之，一开始看到这道题，我的脑海中就闪现了一种机（sha）智（bi）的做法：
### 暴力枚举 
（没错，你没有听错，连是暴力搜索都不是，就是暴力枚举！！）

方法如下，首先枚举1~N的全排列（都点可怕），将每个排序的答案依次计算，然后利用一个Int变量来更新答案，最后输出最小的答案。

共有12个测试点（~~不要问我是怎么知道的。。~~），预计得分24/100（对3个点），实际得分49/100(这个骚操作666，~~没想到数据竟然这么水~~)

代码如下（49分）：

```c
#include "bits/stdc++.h"    //头文件竟然可以这么写666
using namespace std;  
int n,ans=9999999;   	//很大就行
int py[13][4],now[13],used[13],ppp;
bool rabbit[13],dianhua[13][13];
int search(int);
void cost();
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=3;j++)	
			cin>>py[i][j];
	for(int i=1;i<=n;i++) used[i]=i;
	search(1);  //从1开始深搜
	cout<<ans/2;
	return 0;
}
int search(int steps){   //search函数枚举全排列
	for(int i=1;i<=n;i++){
		if(rabbit[i]==false){
			rabbit[i]=true;
			now[steps]=i;
			if(steps==n) cost();  //如果本次排列已经完成，进入cost函数进行计算答案
			else search(steps+1);
			rabbit[i]=false;
		}
	}
}
void cost(){   //对于每个排列P，cost函数计算该排列的答案
	int money=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=3;j++){
			for(int f=1;f<=n;f++)
				if(now[f]==py[now[i]][j]){
					money=money+abs(used[i]-f);
					break;
				}
		}
	ans=min(ans,money); //变量ans更新最小的答案
}
```

以上的代码中，search的时间复杂度为O(N!),cost函数的时间复杂度为O(N^3),总时间复杂度为
## O(N！*N^3)
（可怕可怕，第一次见到如此可怕的时间复杂度）

所以，这种方法，是不行的！！

于是我陷入了深深的思考（啊啊啊。。。。） 大约2分钟之后，我想到了 
### 启发式搜索。
没错，启发式搜索。竟然暴力搜索不行，那我就优化一下吧。。

（楼上的什么第一行只放1或者N的方法我并不赞同，首先这个做法只是将O(N!)的复杂度转化成了O((N-1)!)的时间复杂度，其次，这种做法可能导致在计算时由于找不到最优排列而导致输出的答案错误）

于是，优化吧。。剪枝优化。。

预计得分84/100，实际得分100/100。。

好吧，看来数据比较水。。（~~我们教练出题我怎么就只有84分~~）

代码如下：

```c
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;
int N;
int nbr[13][3];
int best = 9999999, pos[13]; //best很大就行了
void solve(int so_far,int cost_so_far,int pending_links, int pending_link_cost)
{  if (so_far==N) {
    best = min(best, cost_so_far);
    return;
  }  //如果有更好的方案，剪枝。
  if (cost_so_far + pending_link_cost >= best) return;  
  so_far++;
  for (int i=1;i<=N;i++) 
    if (pos[i]==0) {
      pos[i] = so_far;
      int added_cost = 0, new_pending_links = 3;
      for (int j=0; j<3; j++)
	  if (pos[nbr[i][j]] != 0) { 
	    added_cost += pos[i] - pos[nbr[i][j]];   
	    new_pending_links -= 2;   //如果上一只牛已经安装好了电话线（就暂时叫做电话线吧）这条线的权值+2
	  }
      solve(so_far,cost_so_far + added_cost,pending_links + new_pending_links,pending_link_cost + (pending_links + new_pending_links) - added_cost);  //进入下一层函数进行递归，启发式寻找最优方案
        pos[i] = 0;
    }
}
int main(void)
{ 
  cin >> N;
  for (int i=1; i<=N; i++) {
    for (int j=0; j<3; j++) {
      cin >> nbr[i][j];
    }
  }
  solve(0, 0, 0, 0);
  cout << best << "\n"; //愉快地输出答案
  return 0;
}
```

好的，题目已经AC了，但是我们的征途并没有就此结束。。

我们教练出的数据，这个算法只能得到84分（超时2个点）.

所以，我们需要继续对程序进行优化。

动态规划？DP？都过不了100%的数据。我们要用的是：

## ~~某科学的玄学算法~~（状态压缩DP）

NICE~~

预计得分100/100，实际得分100/100

AC无压力炒鸡条炸天代码：

```c
#include <iostream>
#include <cstdio>
#include <algorithm>  //就是不用肥宅万能头文件~~
using namespace std;
#define NMAX 12
#define infinite 1000000000 //定义无限大的INF
int dp[1 << NMAX];  //哦。。骚操作。。nice~~
int main() {
	int n;
	scanf("%d", &n); //输入
	int nbr[13][3];
	for (int i = 0; i < n; i++) {
		scanf("%d %d %d", &nbr[i][0], &nbr[i][1], &nbr[i][2]);
		nbr[i][0]--;	nbr[i][1]--;	nbr[i][2]--;
	}
	dp[0] = 0;
	for (int subset = 1; subset < (1 << n); subset++) {
		int pending_links = 0;
		for (int i = 0; i < n; i++) {//计算连出去的线
			if (subset & (1<<i)) {
				pending_links += 3-(((subset >> nbr[i][0]) & 1+((subset >> nbr[i][1]) & 1) +((subset >> nbr[i][2]) & 1));
			}
		}  //每次把答案加上已有选择中的最优方案
		dp[subset] = infinite;
		for (int i = 0; i < n; i++) {
			if (subset & (1 << i)) {
				int cost = pending_links - 3 + 2 * (((subset >> nbr[i][0]) & 1) +((subset >> nbr[i][1]) & 1) +((subset >>  nbr[i][2]) & 1));
				dp[subset] = min(dp[subset], dp[subset & ~(1<<i)] + cost);
			}//每次循环寻找最优路径并免除剪枝带来的不必要麻烦，同时更新答案。
		}
	}
	printf("%d\n", dp[(1 << n) - 1]);
}
```

Oh..

Nice..

好了，题解到这里就全部结束了。希望我的这一份题解能够让大家学到更多的知识。

## 最后祝大家NOIP2018愉快AK!!

~~再补一句我其实还是很蒟蒻的啊~~

---

## 作者：Develop (赞：13)

#### 今天考试的一道题呀~~虽然没有过~~

~~老师的方法神似已发布某题解~~

不过我看没有解释，还是写一篇题解

------------
因为n<=12，我们可以考虑压缩状态优化时间

定义 f [ k ]中k的二进制下第i位为1 / 0表示第i个点在 / 不在集合中，

f [ k ]本身保存的是当前状态k下的最小代价(这个代价有点不一样)

由题意我们发现如果f [ k ]仅靠存集合k内所有能连上边(即两头牛是朋友)的牛所花费代价的话，状态并不好转移

不妨加一个条件：outedge 集合k向外需要连，但还没有连的边的条数(即一些牛在k内，但是朋友不在，连不起)；这时我们的代价还要加上这些未连的边在当前集合中的这一部分的代价

如 2 3 4————5 6 7 ；假设2和3连了一条边，2还要与5连边；那从右边看2连5的边在目前2 3 4内的长度(一部分)就是2

那我们现在来分析如何转移：
	
   		对于一个已知最小代价，加上一个点，只需要求没有这个点的最优解加上这个点加进来后仍然是出边的数量(+1)和加进来这个点新增的出边数(+1)，以及这个点能连回去的边数(+1)
       
括号内表示的是每一条边对答案的贡献都是1

~~虽然有代码了但我还是放上来吧~~
~~各位模拟退火大佬都好强~~

```cpp
#include <bits/stdc++.h>
#include <algorithm>
#define ll long long
#define Freopen(x) {freopen(#x".in","r",stdin);freopen(#x".out","w",stdout);}
using namespace std;
void init(),solve(); 
int fri[15][5];
int f[1<<13],n;
int main()
{
	init();
	solve();
	return 0;
}
void init()
{
	//Freopen(haywire)
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		for(int j=0;j<3;j++)
			scanf("%d",&fri[i][j]),
			fri[i][j]--;//这样方便处理
	return;
}
void solve()
{
	memset(f,0x3f,sizeof(f));
	f[0]=0;
	for(int k=1;k<(1<<n);k++)//状态压缩总共有1<<n种情况 
	{
		int outedge=0;//出边数
		for(int i=0;i<n;i++)
			if(k&(1<<i))//如果第i个点在集合k内 
				outedge+=3-((k>>fri[i][0])&1)-((k>>fri[i][1])&1)-((k>>fri[i][2])&1); //那么出边就要加上i的不在k中朋友的个数
		for(int i=0;i<n;i++)
		{
			if(k&(1<<i))//第i个点在集合k内 
			{
				int c=outedge-3+((k>>fri[i][0])&1)+((k>>fri[i][1])&1)+((k>>fri[i][2])&1)
				//括i点有outedge条边，现在假设没有i，把i加进来 
				//不包括i的集合就少了3-((k>>fri[i][0])&1)-((k>>fri[i][1])&1)-((k>>fri[i][2])&1)条边
                +((k>>fri[i][0])&1)+((k>>fri[i][1])&1)+((k>>fri[i][2])&1);
				//连上原来的集合还要加上 上行的代价
				f[k]=min(f[k],f[k&~(1<<i)]+c);
                //每次加一个点的代价就是所有现在出边的长度的数量(Ta的长度加了一)和i这个点连回k集合的边的数量(长度为一)
				//printf("%d\n",f[k]);
			}
		}
	}
	printf("%d\n",f[(1<<n)-1]);
	return;
}
```
管理大大辛苦了:）  ~~所以给过吧~~

---

## 作者：s_ShotღMaki (赞：10)

看了一眼题

状压DP？？？~~具体没想出来~~

退火？？？~~码量太大~~

A*？？？~~翻了一下题解~~

数据范围：
$n <= 12$

少年，你可知道有一种玄学的猴子算法

$Random Shuffle$

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <map>
#include <stack>
#include <algorithm>
#include <iomanip>
#include <set>

using namespace std;

int n;
int ans = 0x3f3f3f3f;
bool used[14][14];
int Ad[14], Bd[14];
int aaa;
int flag;
struct node
{
	int x, y, z, num;
} a[14];

inline int Mi (int x, int y)
{
	if (x < y) return x;
	return y;
}

inline void MIN ()
{
	int sum = 0;
	for (int i = 1; i <= n; i ++)
	{
		if (used[Ad[i]][a[i].x] == 0 && used[a[i].x][Ad[i]] == 0)
		{
			sum += abs (i - Bd[a[i].x]);
			used[Ad[i]][a[i].x] = 1, used[a[i].x][Ad[i]] = 1;
		}
		if (used[Ad[i]][a[i].y] == 0 && used[a[i].y][Ad[i]] == 0)
		{
			sum += abs (i - Bd[a[i].y]);
			used[Ad[i]][a[i].y] = 1, used[a[i].y][Ad[i]] = 1;
		}
		if (used[Ad[i]][a[i].z] == 0 && used[a[i].z][Ad[i]] == 0)
		{
			sum += abs (i - Bd[a[i].z]);
			used[Ad[i]][a[i].z] = 1, used[a[i].z][Ad[i]] = 1;
		}
	}
	//if (flag != 1) if (sum == 13) for (int i = 1; i <= n; i ++) printf ("%d ", Ad[i]), flag = 1;
	ans = Mi (ans, sum);
}

signed main ()
{
	scanf ("%d", &n);
	for (int i = 1; i <= n; i ++) scanf ("%d%d%d", &a[i].x, &a[i].y, &a[i].z), a[i].num = i;
	for (int q = 1; q <= 233333; q ++)
	{
		random_shuffle (a + 1, a + 1 + n);
		for (int i = 1; i <= n; i ++) Ad[i] = a[i].num;//当前位置是什么数
		for (int i = 1; i <= n; i ++) Bd[a[i].num] = i;//当前数字在什么位置 
		/*if (Ad[1] == 3 && Ad[2] == 6 && Ad[3] == 5 && Ad[4] == 2 && Ad[5] == 4 && Ad[6] == 1)
		{
			aaa = 1;
		}*/
		MIN ();
		memset (used, 0, sizeof (used));
	}
	printf ("%d", ans);
}
```




---

## 作者：Refined_heart (赞：6)

蒟蒻刚学模拟退火，来写一篇题解。

题目大意：每个点与其它三个点需要连边，连边代价为它们位置之差的绝对值。求一个排列使得这个值最小。

看到$n$都很小，虽然一般会想到状压，但是这题似乎不是一眼状压，考虑其它算法。

我们是不是可以随机一个数列，每次计算一下它的答案，根据一定次数的重复，从而得出一个可能的最优解呢？

我们可以用**模拟退火**。

考虑一次随机，我们做出的更改是交换这两个位置的点。那么每一次，我们的答案显然都会有一个改变。

计算这个答案，暴力即可；然后计算与当前答案的增量，以此判断是不是接受这个答案。

以此迭代，多迭代几次即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
const double h=0.996;
int a[50][50];
int ans;
int pos[50];
int calc(){
	int res=0;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=3;++j)
				res+=abs(pos[i]-pos[a[i][j]]);
	return res>>1;
}
void solve(){
	double T=6000;
	while(T>1e-16){
		int x=rand()%n+1;
		int y=rand()%n+1;
		swap(pos[x],pos[y]);
		int Num=calc();
		if(Num<ans)ans=Num;
		else if(exp(ans-Num)/T<double(rand())/RAND_MAX)swap(pos[x],pos[y]);
		T*=h;
	}
}
void work(){
	for(int i=1;i<=60;++i)solve();
	printf("%d\n",ans);
}
int main(){
	srand(time(0));
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d",&a[i][1]);
		scanf("%d",&a[i][2]);
		scanf("%d",&a[i][3]);
		pos[i]=i;
	}
	ans=2147483647;work();
	return 0;
}
```
~~话说这真是黑题吗……~~

---

## 作者：longlongzhu123 (赞：5)

# 题解

诶居然没有人写随机题解？我也来水一波~~

## 解法：随机化搜索

先解释一下题目意思吧。

给出 $n$ 头奶牛以及它们的 3 个朋友。求一个排列，使每对朋友之间的距离之和尽量小。

## 暴力 - 49分

可以看出这题没有什么特别的性质，难以DP。看到 $n$ 比较小，考虑暴搜。

套上暴搜模板~~  写一个 $dfs$ 生成序列，再写一个 $check$ 统计并更新答案。

可以很容易写出 $dfs$ ：

```cpp
int b[MAXN];  //  用 b 来保存生成的序列
int pos[MAXN];  //  为了方便呢，使用一个 pos[i] 来记录 i 在排列里出现的位置
bitset<MAXN> used;  //  用 bitset 来判断一个数是否用过
void dfs(int level) {
    if(level > n) {
        check();
    }
    else {
        for(int i = 1; i <= n; i ++) {
            if(!used[i]) {
                used[i] = true;
                b[level] = i;
                pos[i] = level;
                dfs(level + 1);
                used[i] = false;
            }
        }
    }
}
```

$check$ 就直接根据题目描述写出：

```cpp
//  f[i][j] 为第 i 只奶牛的第 j 个朋友
void check() {
    int ans = 0;
    for(int i = 1; i <= n; i ++) {
        for(int j = 1; j <= 3; j ++) {
            ans += abs(pos[f[b[i]][j]] - i);
        }
    }
    min1 = min(min1, ans);  //  min1 是要输出的答案
}
```

然后 ...... [49分](https://www.luogu.org/record/show?rid=11865635)

~~那么问题来了，~~怎么在时间限制内，使用简单的方式AC这题？

祭出 $std::rand()$ ！

## 随机搜索

如果我们随机生成一个排列，再用 $check$ 统计答案，会怎样？

```cpp
void gen() {
    used.reset();
    int a = rand() % n + 1;
    for(int i = 1; i <= n; i ++) {
        while(used[a]) {
            a = rand() % n + 1;
        }
        used[a] = 1;
        b[i] = a;
        pos[a] = i;
    }
}
```

emmm.... 你蒙对答案的概率还不如输出样例。。。

那如果多次生成排列呢？

那么恭喜你，这就是正解！

不停生成排列并统计答案，直到达到时限。

事实证明，这是非常实用的算法。

```cpp
srand(time(0));
min1 = INF;
while(clock() - c <= 0.7 * CLOCKS_PER_SEC) {
    gen();
    check();
}
cout<<min1<<endl;
```

将这份代码提交，你就会发现：

[Accept！](https://www.luogu.org/record/show?rid=11870143)

```cpp
// luogu-judger-enable-o2
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 20;
const int INF = 2000000000;
int n, f[MAXN][4];  //  friends
int b[MAXN], pos[MAXN];
bitset<MAXN> used;
int min1;
int read() {
    int res = 0;
    int get = getchar();
    while(!isdigit(get))
        get = getchar();
    while(isdigit(get)) {
        res = res * 10 + get - '0';
        get = getchar();
    }
    return res;
}
inline void generate() {
    used.reset();
    int a = rand() % n + 1;
    for(int i = 1; i <= n; i ++) {
        while(used[a]) {
            a = rand() % n + 1;
        }
        used[a] = 1;
        b[i] = a;
        pos[a] = i;
    }
}
int ans;
inline void check() {
    ans = 0;
    for(int i = 1; i <= n; i ++) {
        for(int j = 1; j <= 3; j ++) {
            ans += abs(pos[f[b[i]][j]] - i);
        }
    }
    min1 = min(min1, ans);
}
int main() {
    srand(time(0));
    min1 = INF;
    n = read();
    for(int i = 1; i <= n; i ++) {
        f[i][1] = read();
        f[i][2] = read();
        f[i][3] = read();
    }
    int c = clock();
    while(clock() - c <= 0.998 * CLOCKS_PER_SEC) {
        generate();
        check();
    }
    cout<<min1 / 2<<endl;
    return 0;
}
```



---

## 作者：违规用户名^F21#cA1 (赞：3)

dp了解一下```
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX 12
#define infinite 1000000000
int dp[1 << NMAX];
int main() {
    //freopen("haywire.in","r",stdin);
    //freopen("haywire.out","w",stdout);
    int n;
    scanf("%d", &n);
    int nbr[13][3];
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &nbr[i][0], &nbr[i][1], &nbr[i][2]);
        nbr[i][0]--;	nbr[i][1]--;	nbr[i][2]--;
    }
    dp[0] = 0;
    for (int subset = 1; subset < (1 << n); subset++) {
        int pending_links = 0;
        for (int i = 0; i < n; i++) {//计算链出去的线 
            if (subset & (1<<i)) {
                pending_links += 3-(((subset >> nbr[i][0]) & 1) +
                                 ((subset >> nbr[i][1]) & 1) +
                                 ((subset >> nbr[i][2]) & 1));
            }
        }
        dp[subset] = infinite;
        for (int i = 0; i < n; i++) {
            if (subset & (1 << i)) {
                int cost = pending_links - 3 + 2 * (((subset >> nbr[i][0]) & 1) +
                                           ((subset >> nbr[i][1]) & 1) +
                                           ((subset >>  nbr[i][2]) & 1));
                dp[subset] = min(dp[subset], dp[subset & ~(1<<i)] + cost);
            }
        }
    }
    printf("%d\n", dp[(1 << n) - 1]);
}
```

---

## 作者：封禁用户 (赞：3)

这道题神坑！！

我的方法是枚举n头牛的所有排列

但是有两个优化：

优化1：第一位总是1或n，这样就把时间复杂度降为O ( ( n-1 ) ! )

优化2：当n太大的时候，随机生成b数组的排列，这样能加快不少，但是未必能对

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[13][3],b[13],ans=2147000000,i;
inline int min(int x,int y){  //容易打的函数最好自己打，STL常数太大
    return x<y?x:y;
}
void calc(){  //当b数组确定后，计算答案，更新ans
    int s=0;
    for (int i=1;i<=n;i++)
         for (int j=0;j<3;j++) s+=abs(b[i]-b[a[i][j]]);
    ans=min(ans,s);
}
int main(){
    srand((unsigned)time(NULL)); //随机种子
    cin>>n;
    for (i=1;i<=n;i++) scanf("%d%d%d",&a[i][0],&a[i][1],&a[i][2]),b[i]=i;
    if (n<=9){
        do{
            calc();
        }while (next_permutation(b+2,b+n+1));//全排列函数
    }
    else for (i=0;i<200000;i++) random_shuffle(b+2,b+n+1),calc();//随机生成排列
    for (i=1;i<n;i++) b[i]=i+1;
    b[n]=1;
    if (n<=9){
        do{
            calc();
        }while (next_permutation(b+1,b+n));
    }
    else for (i=0;i<200000;i++) random_shuffle(b+1,b+n),calc();
    printf("%d",ans>>1);
}
```
要注意一下，随机生成所枚举的范围最好在200000以上，

我在15W,10W都试过了，过不了，可见20W以下AC几率不大


---

## 作者：荣耀南冥 (赞：2)

# ~~这个题很水~~
[题目传送门](https://www.luogu.com.cn/problem/P2210)

在C++函数库内有一个神奇的函数 ~~（我不会说是因为我忘了在哪个头文件的，建议写万能头）~~ :
```
srand(time(NULL))//先生成随机种子

random_shuffle()
```
它可以任意随机序列，用法和sort类似，区间左闭右开 ~~（STL不都是这niao xing）~~ ，然后现在就可以随机打乱序列，再更新最优解，比模拟退火要简单许多 ~~至少比模拟退货，DP，A* 好写吧~~

$ Code: $
```c++
#include <bits/stdc++.h>
using namespace std;
#define gc getchar()
double st=clock();//先初始时间
int n,ans=0x7fffffff;
int a[100];
int mp[100][100];
int m[100][100];

inline int read(){
	int r=0,l=1;char ch=gc;
	while(!isdigit(ch)){if(ch=='-')l=-1;ch=gc;}
	while(isdigit(ch)){r=(r<<3)+(r<<1)+ch-'0';ch=gc;}
	return r*l;
}

double time(){//判断运行时间
	return (clock()-st)/1e6;
}

inline void solve(){//暴力求次区间的解
	random_shuffle(a+1,a+n+1);//打乱序列
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			if(m[a[i]][a[j]])
           		   mp[a[i]][a[j]]=abs(i-j);
		}
	}
	int cnt=0;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			cnt+=mp[i][j];
	ans=min(ans,cnt/2);//更新一下ans
}

int main(){
	srand(time(NULL));
	n=read();
	for(int i=1;i<=n;++i)a[i]=i;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=3;++j)
			m[i][read()]=1;//判断两头牛是不是friend
	while(time()<0.98)//注意卡时间多跑几次。如果你觉的得自己是欧皇可以调小一点
      solve();
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：funky_monkey (赞：2)


```
/*
LGOJ P2210 Haywire 
算法：A* 启发式搜索 
时空限制：1000ms 128MB
主要思路：暴力搜索，每次在搜索当中估测出以后的最小花费，进行剪枝。 
*/ 
#include<bits/stdc++.h>
#define INF 1e9
using namespace std;
const int MAXN=12+5;
int f[MAXN][5],pos[MAXN],n,ans=INF; 
void Astar(int now,int nowcost,int goingto,int goingtocost)
{
	if(now==n) { ans=min(ans,nowcost); return; }//当搜索到第n头牛时，实际上决定的是第n+1头牛的位置，所以return 
	if(nowcost+goingtocost>=ans) { return; }//剪枝，如果现在花费加最少预计花费大于答案，直接return 
	now++;//做的是第now+1头牛的位置 
	for(int i=1;i<=n;i++)
	{
		if(pos[i]==0)
		{
			pos[i]=now;
			int addcost=0,newgoingto=3; //一开始先假设它和他的三个朋友距离都是1（这是最好情况） 
			for(int j=1;j<=3;j++)
			{
				if(pos[f[i][j]]!=0)
				{
					addcost+=now-pos[f[i][j]];
					newgoingto-=2; //已经确定了一头牛与其朋友的距离，就将预期的距离-2（因为已经算在已花费里面了） 
				}
			}
			Astar(now,nowcost+addcost,goingto+newgoingto,goingtocost+goingto+newgoingto-addcost);
			pos[i]=0;//回溯 
		}
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=3;j++)
		{
			scanf("%d",&f[i][j]);
		}
	}
	memset(pos,0,sizeof(pos));
	Astar(0,0,0,0);
	printf("%d\n",ans); 
	return 0;
}
```

---

## 作者：Erica_N_Contina (赞：1)

$f_s$ 表示将 $s$ 中所有牛的连接都建立需要的最小花费。

然后怎么转移呢？

我们枚举到一个状态 $s$，统计 $s$ 中有多少条未完成的连接：即这个连接只有一个端点在 $s$ 中。记数量为 $cnt$。

随后考虑枚举 $i\in s$，从 $f_{s-i}$ 转移来。那么就相当于向 $s-i$ 中插入 $i$，需要新增的最小花费是多少呢？统计出 $s$ 中和 $i$ 有关的未完成连接的数量 $r$，那么花费就是 $cnt-(3-r)+r$。为啥？

这意味着我们其余的那些未完成连接都要跨过 $i$ 这样会增加 $cnt-(3-r)$ 的代价（下面有解释）。减去 $3-r$ 是因为有 $3-r$ 条在加入i时补全了，后面不会再有新代价。加上r是因为新增了 $r$ 条未完成连接（这些连接当前只有一个端点，就是 $i$）。

也就是说加入点 $i$ 的代价就是加入 $i$ 后当前局面的**未完成连接的数量。**

为什么呢？

这里不存在什么贪心，我们枚举每个点的位置的流程就体现在插入到集合的顺序。所以我们默认当前插入的点就放在之前在集合内的点的后面。因此对未完成连接的代价就是 $1$ 了。



```C++
// Problem: P2210 Haywire
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P2210
// Memory Limit: 125 MB
// Time Limit: 1000 ms
// Challenger: Erica N
// ----
#include<bits/stdc++.h>

using namespace std;
#define rd read()
#define ull unsigned long long
#define int long long 
#define itn int
#define ps second 
#define pf first

inline int read(){
	int x;
	cin>>x;
	return x;
}
#define zerol = 1
#ifdef zerol
#define cdbg(x...) do { cerr << #x << " -> "; err(x); } while (0)
void err() {
	cerr << endl;
}
template<template<typename...> class T, typename t, typename... A>
void err(T<t> a, A... x) {
	for (auto v: a) cerr << v << ' ';
	err(x...);
}
template<typename T, typename... A>
void err(T a, A... x) {
	cerr << a << ' ';
	err(x...);
}
#else
#define dbg(...)
#endif
const int N=10+5;
const ull P=137;
const int INF=1e9+7;
/*

策略


*/

int f[1<<N];
int to[N][4];

signed main(){
	int n=rd;
	for(int i=0;i<n;i++){
		for(int j=0;j<=2;j++)to[i][j]=rd-1;
	}	
	
	
	for(int s=1;s<(1<<n);s++){
		int cnt=0;
		for(int i=0;i<n;i++){
			
			if((s>>i)&1){
				for(int j=0;j<3;j++){
					cnt++;
					cnt-=(s>>to[i][j])&1;
				}
			}
		}
		f[s]=INF;
		for(int i=0;i<n;i++){
			if((s>>i)&1){
				int r=0;
				for(int j=0;j<3;j++){
					r++;
					r-=(s>>to[i][j])&1;
				}
				int cost=cnt-3+2*r;
				f[s]=min(f[s],cost+f[s^(1<<i)]);
			}
		}
	}
	
	cout<<f[(1<<n)-1]<<endl
}


```

---

## 作者：damnM3bro (赞：1)

### 算法
随机化。

### 思路
直接枚举 $1 \sim n$ 的全排列，显然会 TLE。这时，可以考虑随机化。

我们需要一个数组 $a$ 来维护 $n$ 只奶牛的位置，每次随机打乱 $a$ 数组并计算答案，取最小值即可。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=13;
int minn=1e9+7,n,a[N],p[N][4],ans;

int main(){
    int t=clock();
    srand(time(NULL));
	cin>>n;
	for(int i=1;i<=n;++i)
		a[i]=i;
	for(int i=1;i<=n;++i)
		cin>>p[i][1]>>p[i][2]>>p[i][3];
	while(clock()-t<=0.9*CLOCKS_PER_SEC){
		random_shuffle(a+1,a+1+n);
		ans=0;
		for(int i=1;i<=n;++i)
			for(int j=1;j<=3;++j)
				ans+=abs(a[i]-a[p[i][j]]);
		minn=min(minn,ans/2);
	}
	cout<<minn;
	return 0;
}
```

---

## 作者：littlejuruo (赞：1)

其实这题吧。。。有一种玄学解法

这题的要求的就是一个最小化的顺序

那么，我们就不进想到了一种~~显然的~~写法

就是`random_shuffle`

>什么？这不是乱搞的非正解吗

然而，正如一句话说的好

>一个算法，如果你无法将他卡到错误，那么他就是对的

所以，就产生了下面的~~科学~~随机写法

随机化顺序，模拟过程，取ans最小值

## code

```cpp
#include<bits/stdc++.h>

using namespace std;
const int MAXN=20;
void file(string s){freopen((s+".in").c_str(),"r",stdin);freopen((s+".out").c_str(),"w",stdout);}
int read()
{
	int f=1,a=0;char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-'){
			f=-f;
		}
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		a=a*10+ch-'0';
		ch=getchar();
	}
	return a*f;
}
int n,ans=0x3f3f3f3f;
int a[MAXN],fri[MAXN][MAXN];
int main()
{
//  file("");
	n=read();
	for(int i=1;i<=n;++i){
		int x=read(),y=read(),z=read();
		fri[i][x]=fri[i][y]=fri[i][z]=1;
		a[i]=i;
	}
	for(int i=1;i<=300000;++i){
		random_shuffle(a+1,a+n+1);
		int re=0;
		for(int j=1;j<=n;++j){
			for(int k=j+1;k<=n;++k){
				int pos1,pos2;
				if(!fri[j][k]){
					continue;
				}
				for(int l=1;l<=n;++l){
					if(a[l]==j){
						pos1=l;
					}
					if(a[l]==k){
						pos2=l;
					}
				}
				re+=abs(pos1-pos2);
			}
		}
		ans=min(ans,re);
	}
	cout<<ans<<endl;
	return 0;
}
```


教给我这一写法的lbn @expect 太强了orzorz

推荐一道也可以这样~~科学解决~~随机化乱搞的题目：

[P3959 宝藏](https://www.luogu.org/problem/P3959)

本文同步发于[我的cnblog](https://www.cnblogs.com/zhu-chen/p/11823218.html)，欢迎各位大佬来碾压本蒟蒻

---

## 作者：蕾姆酱QvQ (赞：1)

~~明天就NOIP了我还在这里学玄学算法真的是要死啊QAQ~~

### 算了还是贴上一篇题解吧qwq，毕竟是人生中第一篇黑题题解qwq，

### 首先不会模拟退火的或者不会原理的请出门右转[模拟退火原理+使用](https://m-sea.blog.luogu.org/qian-tan-SA)

### 看一下题目，可以发现这个题就是让我们在所有的组合中找出一个最优解来，符合我们模拟退火的使用条件，所以我们可以开始考虑如何确定每一个值了

剩下的注意的地方和一些做法就放在代码里了qwq

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#define re register
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)

using namespace std;

int n;
int a[15][4];
int p[100],p1[101],linshi,x,y,dc;

const double starttem=1e9;
const double endtime=0.999;
const double changet=0.99;
const double endtem=1e-14;//mnth四位大大 

int abss(int x)
{
 	return x>0?x:x*-1;
}

int sum() //求和 
{
	int ans=0;
	for(re int i=1; i<=n; i++) 
		for(re int j=1; j<=3; j++) 
			ans+=abss(p1[i]-p1[a[i][j]]);
	return ans;
}

inline void change(int x,int y) //交换两个值
{
	int t=p1[x];
	p1[x]=p1[y];
	p1[y]=t;
}

int srandom(int a,int b) //非酋的最后一搏
{
	return rand()%(b-a+1)+a;
} 

int main()
{
	srand(time(NULL));
	srand(rand()+23333333);
	srand(rand()+19260817);//东方之力祝我成功
	srand(rand());//玄学四连 
	scanf("%d",&n);
	for(int i=1; i<=n; i++) 
	{
		scanf("%d%d%d",&a[i][1],&a[i][2],&a[i][3]);
		p[i]=i; //永远不变的初始位置 
		p1[i]=i;//变幻莫测的位置 
	}
	dc=sum();//先求初始解 
	while((clock()/(1.0*CLOCKS_PER_SEC))<=endtime)
	{
		for(re int i=1; i<=n; i++) p1[i]=p[i]; //先初始化好初值
		for(re double t=starttem; t>=endtem; t*=changet)
		{	
			linshi=dc;
			do
			{
				x=srandom(1,n);
				y=srandom(1,n);
			}while(x==y); //玩命找死 
			change(x,y);
			linshi=sum();
			if(linshi<=dc) dc=linshi; //看看是否比原先的更优 
			else if((exp(dc-linshi)*1.0/t>(rand()*1.0/RAND_MAX))) change(x,y); //用一定的概率接受该解（毕竟有比你优的，但是你肯定要把不优的换回去啊qwq 
		}
	}
	printf("%d",dc/2);//因为计算了两次，所以要除2，例如计算a-b你算a的时候计算了一次但你又在b时候又计算了所以必须除掉 
}
```
### 祝大家食用愉快qwq

---

## 作者：lx_zjk (赞：1)

# P2210 【Haywire】
~~卡着时限过题，真开心，粗浅~~学习了随机化算法，过了这道~~黑题~~
# 首先先看一手朴素算法 57pts
```cpp
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

inline ll read() {
    ll f=1,x=0;
    char ch;
    do {
        ch=getchar();
        if(ch=='-')f=-1;
    } while(ch>'9'||ch<'0');
    do {
        x=x*10+ch-'0';
        ch=getchar();
    } while(ch>='0'&&ch<='9');
    return f*x;
}

const int MAX_N=15 + 5;

int n,g[MAX_N][MAX_N],a[MAX_N];

int ans=0x7fffffff;

inline int calc(){
    int res=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(g[i][j]){
                res+=abs(a[i]-a[j]);	
            }
        }
    }
    return res/2;
}

int main(){
    n=read();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=3;j++){
            g[i][read()]=1;			
        }
        a[i]=i;
    }
    do{
        ans=min(ans,calc());
    }while(next_permutation(a+1,a+n+1));
    printf("%d",ans);
    return 0;
}

```

# 随机化算法，一遍AC，~~看来今天也是欧气满满的一天~~

看到T了这么多点，内心一句mmp，凑

然后用随机化算法来降低这道题的时间复杂度//其实没降低，只..

先普及一下
clock（）是计算时间的好工具

先random_shuffel生成一个排列

然后在1000ms内一直这样，从而大概率AC此题


```cpp
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

inline ll read() {
    ll f=1,x=0;
    char ch;
    do {
        ch=getchar();
        if(ch=='-')f=-1;
    } while(ch>'9'||ch<'0');
    do {
        x=x*10+ch-'0';
        ch=getchar();
    } while(ch>='0'&&ch<='9');
    return f*x;
}

const int MAX_N=15 + 5;

int n,g[MAX_N][MAX_N],a[MAX_N];

int ans=0x7fffffff;

inline int calc(){
    int res=0;
    //for(int i=1;i<=n;i++) cout<<a[i]<<" ";
    //cout<<"\n";
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(g[i][j]){
                res+=abs(a[i]-a[j]);	
            }
        }
    }
    return res/2;
}

int main(){
    
    n=read();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=3;j++){
            g[i][read()]=1;			
        }
        a[i]=i;
    }
    int c=clock();
    while(clock()-c<=0.998 * CLOCKS_PER_SEC)
    {
        random_shuffle(a+1,a+n+1);
        ans=min(ans,calc());
    }
    printf("%d",ans);
    return 0;
}

```
# 下午闲的没事干，又学了模拟退火和爬山算法

模拟退火 AC此题的关键之一就是设定好初始温度和终止温度

~~然并卵~~

有了第二篇算法的铺垫，我们可以用clock()函数来防止超时，这样~~妈妈再也不会担心我TLE~~

上代码，具体又不懂的可以来问我

```cpp
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

inline ll read() {
	ll f=1,x=0;
	char ch;
	do {
		ch=getchar();
		if(ch=='-')f=-1;
	} while(ch>'9'||ch<'0');
	do {
		x=x*10+ch-'0';
		ch=getchar();
	} while(ch>='0'&&ch<='9');
	return f*x;
}

const double delta_t=0.98;

double T_MAX=1e5;//初始温度 

const double T_MIN=1e-16;//终止温度 

const int MAX_N=15 + 5;

int n,g[MAX_N][MAX_N],a[MAX_N]; 

inline int calc(){
	int res=0;
	//for(int i=1;i<=n;i++) cout<<a[i]<<" ";
	//cout<<"\n";
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(g[i][j]){
				res+=abs(a[i]-a[j]);	
			}
		}
	}
	return res/2;
}

int ans;

int main(){
	n=read();
	srand(time(0));
	for(int i=1;i<=n;i++){
		for(int j=1;j<=3;j++){
			g[i][read()]=1;			
		}
		a[i]=i;
	}
	ans=calc();//先将ans赋值为初始化状态
	int c=clock(); 
	while(T_MAX>=T_MIN) 
	{
		int x,y;
		if(clock()-c>=0.97 * CLOCKS_PER_SEC) break;
		do{
			x=rand()%n+1;
			y=rand()%n+1;
		}while(x==y);
		swap(a[x],a[y]);
		int tmp_ans=calc();
		if(tmp_ans<=ans){
			ans=tmp_ans;
		}
		else if(exp((ans-tmp_ans)/T_MAX)*RAND_MAX>rand()){
			swap(a[x],a[y]);
		}
		T_MAX*=delta_t;
	}
	cout<<ans<<endl;
	return 0;
}

```

---

## 作者：201012280925LSY (赞：0)

## 前言
笔者是一个刚学模拟退火的蒟蒻，有写的不好的地方欢迎大家指出。
## 题目大意
有 $N$ 头奶牛，每一头奶牛有三个朋友，奶牛们都住在一条线上，如果有两头奶牛是朋友，那么他们之间就需要一条线路，线路的长度为两头奶牛的距离，现在求最短的总线路距离。

## 思路
如果是直接枚举全排列的话，那么显然会超时，所以考虑用模拟退火。模拟退火是一个优化暴力的东西，但是因为引入了更多的随机的因数，所以找到正解的概率大大增加。

那么应该退火什么呢？由枚举全排列可知，我们可以每次随机出来两个数，这两个数表示两头奶牛，然后我们让这两头奶牛交换它们的位置，就可以得到新的排列。

所以我们可以用一个数组记录奶牛的位置，下标 `i` 表示是第 `i` 头奶牛，而里面的值表示第 `i` 头奶牛在哪个位置。那么我们每次随机出两个数 `x` 和 `y`，然后 `swap(x,y)` 即可。

PS：如果随机出两个数相同，可以直接跳过，节省时间。

具体见代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const double T=2000.0,TD=0.999,TK=1e-15;//初始温度 T，每次下降温度的系数 TD，以及终止温度 TK。
long long n,a[15][4],b[15],answer=1e18;//answer 初始值应当是无穷大
long long calculate()//计算这个排列的答案
{
    long long sum=0;
    for(int i=1;i<=n;i++)
    {
        sum+=abs(b[i]-b[a[i][1]])+abs(b[i]-b[a[i][2]])+abs(b[i]-b[a[i][3]]);
    }
    return sum/2;//因为同时从 i 和 a[i] 计算了一次，所以要除以二
}
void sa()//模拟退火
{
    double t=T;//初始温度
    while(t>TK)
    {
        long long ex=rand()%n+1,ey=rand()%n+1;//随机出两个数
        if(ex==ey)continue;
        swap(b[ex],b[ey]);//产生新的排列
        long long eans=calculate();
        long long de=eans-answer;
        if(de<0)//答案更优秀
        {
            answer=eans;
        }
        else
        {
            if(exp(de/t)>rand())//这里是如果按一定概率接受答案没有接受，就把答案改回来
            {
                swap(b[ex],b[ey]);
            }
        }
        t*=TD;//降温
    }
    return;
}
int main()
{
    srand(time(0));
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        b[i]=i;
        cin>>a[i][1]>>a[i][2]>>a[i][3];//输入 i 头奶牛的三个朋友
    }
    sa();//多跑几次模拟退火
    sa();
    sa();
    sa();
    sa();
/*
如果你不放心，可以用这个踩着时间限制过去：
while(clock()<90000)sa();
*/
    cout<<answer;
    return 0;
}
```
[记录](https://www.luogu.com.cn/record/181180103)

---

## 作者：will1111 (赞：0)

# 题解：P2210 Haywire

**一道模拟退火的好题。**

## 思路

模拟退火，每次任选两只奶牛交换位置，由于 $4\le N\le 12$，所以求出正确答案的概率足够高。

至于计算一个解需要耗费干草堆的数量，枚举 $N$ 次，每次加上这头奶牛与其三个朋友的距离的和。

由于它和它的朋友各计算了一次，所以答案要除以 $2$。

## 代码

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>

using namespace std;

// 一些常量
const double init_tempeture=8000,cooling_speed=0.93,ending_tempeture=1e-4;

// 计算排列的值
int compute(vector<vector<int>>&frd,vector<int>&pos)
{
	int res=0;
	for(int i=1;i<frd.size();i++)
	{
		for(int j=0;j<3;j++)
		{
			res+=abs(pos[frd[i][j]]-pos[i]);
		}
	}
	return res/2;
}

int main()
{
	srand(time(0)); // 初始化随机
	int n;
	scanf("%d",&n);
	vector<vector<int>>frd(n+1,vector<int>(3)); // 记录朋友
	vector<int>pos(n+1); // 奶牛的位置
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d%d",&frd[i][0],&frd[i][1],&frd[i][2]);
	}
	int ans=1e9; // 全局最优解
	while(clock()<0.96*CLOCKS_PER_SEC)
	{
		for(int i=1;i<=n;i++) // 初始化位置
		{
			pos[i]=i;
		}
		double temp=init_tempeture;
		int now=1e9; // 局部最优解
		while(temp>ending_tempeture) // 开始退火
		{
			int x=rand()%n+1,y=rand()%n+1; // 随机交换
			while(x==y)
			{
				x=(rand()%n+n)%n+1;
				y=(rand()%n+n)%n+1;
			}
			swap(pos[x],pos[y]);
			int lcans=compute(frd,pos); // 计算答案
			if(lcans<=now) // 当前答案优于局部最优解，立即接受
			{
				now=lcans; // 修改局部最优解
			}
			else
			{
				if(exp(1.0*(now-lcans))/temp<1.0*rand()/RAND_MAX) // 概率接受
				{
					swap(pos[x],pos[y]);
				}
			}
			temp*=cooling_speed;
		}
		ans=min(ans,now);
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Furina_Saikou (赞：0)

# 思路

看到大佬都用模拟退火，我没有那个实力，既然数据范围那么小，于是……我们考虑普通的随机化算法，具体思路：随机化算法最核心的地方就是随机数，如何取随机数呢？很多人都知道 `rand()` 函数，但是相同的代码每次的 `rand()` 返回结果都相同，怎么办呢？我们可以用 `srand(time(0))` 函数来初始化随机数种子为系统时间，但这仍然不是最好的方法，因为 `time(0)` 只能精确到毫秒，这放在代码运行中显然是不够的，于是，传说中的 `mt19937` 随机数生成器出现了，这是质量更高更随机的生成器，在通过 chrono 库中的系统时间来得到精度更加高的时间，具体代码如下：`mt19937 rd(chrono::system_clock::now().time_since_epoch().count());`。

如何计算一个序列的代价我就不多说了，依题意模拟即可，注意去重。那么怎样安排顺序呢？因为数据量非常得渺小，所以我们完全可以随机地打乱序列，计算答案，最终取最小值。打乱序列可以使用 `shuffle(RandomIt first, RandomIt last, RandomFunc&& r)` 函数，其中第三个参数填随机数生成器。因为我们的数据小，所以每次计算的时间可以忽略不计，将打乱次数尽最大可能提高，你就会发现，我们能以极高的概率覆盖最优解，然后就奇妙的过了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=114;
mt19937 rd(chrono::system_clock::now().time_since_epoch().count());
int n,a[N][3],b[N],d[N],ans=1145141919810ll;
void solve()
{
	int cnt=0;
	shuffle(b+1,b+n+1,rd);
	for(int i=1;i<=n;i++)d[b[i]]=i;
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<3;j++)
		{
			int x=a[b[i]][j];
			if(d[x]<i)continue;
			cnt+=d[x]-i;
		}
	}
	ans=min(ans,cnt);
}
signed main()
{
	cin>>n;
	for(int i=1;i<=n;b[i]=i,i++)for(int j=0;j<3;j++)cin>>a[i][j];
	for(int t=3000000;t;t--)solve();
	cout<<ans;
	return 0;
}
```
毕竟不是正解，我还是学习了模拟退火。

---

## 作者：int_stl (赞：0)

我爱随机化算法！

对于这道题，我们考虑使用模拟退火。我们将初始温度设为 $25$，每次温度乘上 $0.99$。对于每次操作，我们把 $1 \sim n$ 的一个排列打乱一次，然后计算答案并且更新即可。

为了防止答案错误，我们可以卡时或者限定运行次数（$3000$ 次就够了），足以通过本题。

参考代码如下：

```cpp
#include <bits/stdc++.h>
#define ll long long
#define int long long
#define debug(x) cerr << (#x) << '\n'
#define ls (u << 1)
#define rs (u << 1 | 1)
#define pii pair <int, int>
#define pb emplace_back
#define chkmin(x, y) x > y ? x = y : 0
#define chkmax(x, y) x < y ? x = y : 0
#define L(i, a, b) for (int i = (a); i <= (b); i++)
#define R(i, a, b) for (int i = (a); i >= (b); i--)
using namespace std;
const double eps = 1e-10;
const double dt = 0.99;
const int N = 1e5 + 6;
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
#define rd(n) uniform_int_distribution <int>(1, n)(rnd)
#define rddb(n) uniform_real_distribution <double>(1, n)(rnd)
int n;
int a[14][4], p[14], ans = 0x3f3f3f3f;
int cal() {
	int ans = 0;
	L(i, 1, n) {
		L(j, 1, 3) {
			ans += abs(p[i] - p[a[i][j]]);
		}
	}
	return ans;
}
void SA() {
	double temp = 25.0;
	for (; temp >= eps; temp *= dt) {
		int x = rd(n), y = rd(n);
		swap(p[x], p[y]);
		int now = cal();
		if (now < ans) ans = now;
		else if (exp(abs(now - ans)) * 1.0 / temp < rddb(10000) / 32767) {
			ans = now;
		}
	}
}
signed main() {
	cin >> n;
	L(i, 1, n) {
		cin >> a[i][1] >> a[i][2] >> a[i][3];
		p[i] = i;
	}
	int t = 3000;
	while (t--) SA();
	cout << ans / 2;
}
```

---

## 作者：peterwuyihong (赞：0)

## 此题与$NOIP$某题十分类似
推荐去$A$了[这题](https://www.luogu.com.cn/problem/P3959)，再回来做此题

## 具体思路：~~猴排~~
$random\_shuffle$，每次打乱序列，判断最小值，配合
```cpp
while((double)clock()/CLOCKS_PER_SEC<=1)
```
于是有了本题最慢做法

```cpp
#include<bits/stdc++.h>
using namespace std;
#define debug(x) cerr<<#x<<' '<<x<<endl
#ifndef ONLINE_JUDGE
	#define fuck getchar
#else
	#define fuck nc
#endif
char nc(){
  	static char buf[1<<25],*p=buf,*q=buf;
  	if(p==q&&(q=(p=buf)+fread(buf,1,1<<25,stdin),p==q))return EOF;
  	return *p++;
}
template<class T>void read(T&x){
	short f=1;x=0;
	char ch=fuck();
	while(!isdigit(ch)){
		if(ch=='-')f=-1;
		ch=fuck();
	}while(isdigit(ch)){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=fuck();
	}x*=f;
}
template<class T>void write(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>=10)write(x/10);
	putchar(x%10+48);
}

int n;
int a[13][3];
int ord[13];
int pos[13];
int ans=INT_MAX;
signed main(){
#ifndef ONLINE_JUDGE
	freopen("testdata.in","r",stdin);
#endif
	read(n);
	for(int i=1;i<=n;i++){
		for(int j=0;j<3;j++)
		read(a[i][j]);
	}
	for(int i=1;i<=n;i++)ord[i]=i;
	while((double)clock()/CLOCKS_PER_SEC<=1){
		random_shuffle(ord+1,ord+n+1);
		for(int i=1;i<=n;i++)pos[ord[i]]=i;
		int res=0;
		for(int i=1;i<=n;i++){
			for(int j=0;j<3;j++)
			res+=abs(pos[a[i][j]]-pos[i]);
		}
		ans=min(ans,res>>1);
	}
	write(ans);
}

```


---

## 作者：LlLlCc (赞：0)

看到$n$非常小，所以很适合用模拟退火来做

先考虑如果位置确定了如何求需要铺多少草

设：$a_i$为第$i$头奶牛所在的位置

对于第$i$头奶牛，如果他的朋友的$a_j$大于$a_i$，就要铺$a_j-a_i$的草

所以我们可以先使$a_i=i$，然后用模拟退火每次随机两个$x,y$交换$a_x$和$a_y$，调调参数就过了（~~没打随机数种子都过了~~）

## code
```
#include<bits/stdc++.h>
#define maxn 20
using namespace std;
int n,a[maxn],ans,now,lnk[205],x,tot,nxt[205],son[205];
inline int read(){
	int ret=0;char ch=getchar();
	while (ch<'0'||ch>'9') ch=getchar();
	while (ch<='9'&&ch>='0') ret=ret*10+ch-'0',ch=getchar();
	return ret;
}
inline void add(int x,int y){nxt[++tot]=lnk[x];lnk[x]=tot;son[tot]=y;}
inline int Work(){
	int sum=0;
	for (int i=1;i<=n;i++)
	for (int j=lnk[i];j;j=nxt[j]) if (a[son[j]]>a[i]) sum+=a[son[j]]-a[i];
	return sum;
}
inline void SA(){
	double St=1e5,Tt=1e-14,Ct=0.917;
	for (double T=St;T>Tt;T*=Ct){
		int x=rand()%n+1,y=rand()%n+1;
		while (x==y) y=rand()%n+1;swap(a[x],a[y]);
		now=Work();
		if (now<ans) ans=now;
		else if ((double)exp((ans-now)/T)<=(double)(rand())/RAND_MAX) swap(a[x],a[y]);
	}
}
int main(){
	srand(2333);
	n=read();
	for (int i=1;i<=n;i++) x=read(),add(i,x),x=read(),add(i,x),x=read(),add(i,x);
	for (int i=1;i<=n;i++) a[i]=i;
	ans=Work();for (int i=1;i<10;i++) SA();
	printf("%d",ans);
	return 0;
}
```


---

## 作者：Smallbasic (赞：0)

~~今天刚讲模拟退火，就来发篇题解水积分~~

众所周知退火是一种玄学的随机算法，不过写得好+rp高会水过很多题

先看一个问题：求一个函数f最大点。

解决这个问题有种方法：爬山法

顾名思义就是想爬山一样爬。先随便找个方向走，如果增高则接着走，不然直接换方向。

这样爬山会走到最近的一个峰值，但不会得到最优解。

模拟退火其实就是爬山法优化。在不增高的时候，以一定的概率选择走下去或换方向。

一般设当前最优解为$ans$，得到的解为$k$，设一个因子t，当：

$$e^{k-ans\over t}>{rand()\over RANDMAX}$$

时换方向。（至于为什么我也不知道）。

至于t,因为越到后面答案越精确，t也会不断缩小。具体范围和缩小程度依题而定、

来张wikepedia的图，退火的过程大概就是这样的：

![](https://upload.wikimedia.org/wikipedia/commons/d/d5/Hill_Climbing_with_Simulated_Annealing.gif)

由于是随机算法，退火的值有很大概率不准，rp差一点还会爆0.但由于他的时间复杂度低且具有随机性，我们可以跑几千甚至上万次退火得到答案。

回到这道题，用换金币的套路，每次退火交换两个奶牛的位置统计答案即可。至于其他具体的东西就见代码吧。

~~于是我们有水过了一道黑题~~:

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <ctime>

using namespace std;

int n, fr[13][4], pos[13], ans = 0x3f3f3f3f;

inline void SA() {
	double beg = 5000, end = 1e-10, tt = 0.9112;
	for (double t = beg; t > end; t *= tt) {
		int x = (rand() % n) + 1, y = (rand() % n) + 1, mmm = 0;
		swap(pos[x], pos[y]);
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= 3; ++j)
				mmm += abs(pos[i] - pos[fr[i][j]]);
		if (mmm < ans) ans = mmm;
		else if (exp((ans - mmm) / t) > (double)rand() / (double)RAND_MAX) swap(pos[x], pos[y]);
	}
}

int main() {
	srand((unsigned)time(NULL)); scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		pos[i] = i;
		for (int j = 1; j <= 3; ++j)
			scanf("%d", &fr[i][j]);
	}
	int t = 5000;
	while (t--) SA();
	printf("%d", ans / 2); //我的做法每队是统计了两遍，这里要注意
	return 0;
}
```

---

## 作者：Vanity_ (赞：0)

# 思路

我们很容易知道第i号如果放的k号奶牛和1~i-1的奶牛有最多个的朋友那么把k号奶牛放到i号位置就是最优的。然后因为我吗不确定第第1个位置的奶牛所以枚举一下就可以了.

~~或许是数据太水没有卡我吧~~
# 2.程序

~~~cpp
#include <bits/stdc++.h>
using namespace std;

struct rabbit
{
	int a;
	int b;
	int c;
}a[17];

int b[17];
int c[17];
int d[17];

int main()
{
	int n,i,j,ans=0,k,minn=1000000000,kk;
	int ok;
//	freopen("haywire.in","r",stdin);
//	freopen("haywire.out","w",stdout);
	scanf("%d",&n);
	for(i=1;i<=n;i++)
		scanf("%d%d%d",&a[i].a,&a[i].b,&a[i].c);
	for(k=1;k<=n;k++)//枚举第1个位置放第几头奶牛 
	{
		for(i=1;i<=n;i++)
			d[i]=1,b[i]=0,c[i]=0;
		ans=0;
		c[1]=k;
		c[2]=a[k].c;
		b[k]=1;
		b[c[2]]=2;
		for(i=3;i<=n;i++)//用贪心获得第i位 
		{
			ok=0;
			for(j=1;j<i;j++)
			{
				for(kk=j+1;kk<i;kk++)
				{
					if(a[c[j]].a==a[c[kk]].a&&!b[a[c[j]].a])  {ok=a[c[j]].a;break;}//如果他的有两个朋友在队列里那么吧他放在队列里 
					if(a[c[j]].a==a[c[kk]].b&&!b[a[c[j]].a])  {ok=a[c[j]].a;break;}
					if(a[c[j]].a==a[c[kk]].c&&!b[a[c[j]].a])  {ok=a[c[j]].a;break;}
					if(a[c[j]].b==a[c[kk]].a&&!b[a[c[j]].b])  {ok=a[c[j]].b;break;}
					if(a[c[j]].b==a[c[kk]].b&&!b[a[c[j]].b])  {ok=a[c[j]].b;break;}
					if(a[c[j]].b==a[c[kk]].c&&!b[a[c[j]].b])  {ok=a[c[j]].b;break;}
					if(a[c[j]].c==a[c[kk]].a&&!b[a[c[j]].c])  {ok=a[c[j]].c;break;}
					if(a[c[j]].c==a[c[kk]].b&&!b[a[c[j]].c])  {ok=a[c[j]].c;break;}
					if(a[c[j]].c==a[c[kk]].c&&!b[a[c[j]].c])  {ok=a[c[j]].c;break;}
				}
				if(ok) break;
			}
			if(ok)//如果剩余的奶牛里面有两个朋友在队列里就代表找到了 
			{
				c[i]=ok;
				b[ok]=i;
				continue;
			}
			for(j=1;j<i;j++)
			{
				if(!b[a[c[j]].a]) {ok=a[c[j]].a;break;}//如果他的有一个朋友在队列里那么吧他放在队列里 
				if(!b[a[c[j]].b]) {ok=a[c[j]].b;break;}
				if(!b[a[c[j]].c]) {ok=a[c[j]].c;break;}
			}
			if(ok)//如果剩余的奶牛里面有两个朋友在队列里就代表找到了
			{
				c[i]=ok;
				b[ok]=i;
				continue;
			}
			for(j=1;j<=n;j++)//如果没找到就随便选一个 
				if(!b[j]) {ok=j;break;}
			c[i]=ok;
			b[ok]=i;
		}
		for(i=1;i<=n;i++)//统计答案
		{
			ans+=(b[a[c[i]].a]-i)*d[a[c[i]].a];
			ans+=(b[a[c[i]].b]-i)*d[a[c[i]].b];
			ans+=(b[a[c[i]].c]-i)*d[a[c[i]].c];
			d[c[i]]=0;
		}
		minn=min(ans,minn);//取最小值
	}
	printf("%d",minn);
}
}
~~~

---

## 作者：little_sun (赞：0)

模拟退火模板题...
 
每次随机将两个位置上的奶牛交换位置

然后算出现在所需的干草数量

如果比答案少就更新

否则就以一定概率接受这个解

然后。。多随机几次就做完了

```cpp
#include <bits/stdc++.h>
#define R register
#define ll long long
#define cmin(a, b) ((a < b) ? a : b)
#define cmax(a, b) ((a < b) ? b : a)
const double delta = 0.999;
const int MaxN = 20;
int n, ans = 0x3f3f3f3f;
double t = 10000000.0;
int pos[MaxN], fri[MaxN][4], g[MaxN][MaxN];
inline int read()
{
    int x = 0;
    char ch = getchar();
    while (ch > '9' || ch < '0')
        ch = getchar();
    while (ch <= '9' && ch >= '0')
        x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    return x;
}
inline int calc()
{
    int ret = 0;
    for (int i = 1; i <= n; i++)
    {
        ret += abs(pos[i] - pos[fri[i][1]]);
        ret += abs(pos[i] - pos[fri[i][2]]);
        ret += abs(pos[i] - pos[fri[i][3]]);
    }
    return ret / 2;
}
inline void SA()
{
    t = 1.0;
    while (t > 1e-10)
    {
        int x = rand() % n + 1, y = rand() % n + 1;
        std::swap(pos[x], pos[y]);
        int tmp = calc();
        int del = tmp - ans;
        if (del < 0)
            ans = tmp;
        else if (exp(-del / t) * RAND_MAX <= rand())
            std::swap(pos[x], pos[y]);
        t *= delta;
    }
}
int main()
{
    n = read();
    srand(time(NULL));
    for (int i = 1; i <= n; i++)
    {
        pos[i] = i;
        for (int j = 1; j <= 3; j++)
            fri[i][j] = read(), g[i][fri[i][j]] = 1, g[fri[i][j]][i] = 1;
    }
    for (int i = 1; i <= 100; i++)
        SA();
    printf("%d\n", ans);
    return 0;
}

```


---

