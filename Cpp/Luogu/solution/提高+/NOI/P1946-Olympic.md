# Olympic

## 题目描述

奥运会正在如火如荼的进行着，金牌榜上也有许多队伍需要排名。你需要选择三个整数 $P_g,P_s$ 和 $P_b$，分别表示每获得一块金、银、铜牌所对应得分。并且满足 $1000 \ge P_g \ge P_s \ge P_b \ge 1$。队伍将依据他们获得的分数进行排序（高分在前）。现在，为了使你所在的队伍排名尽可能的靠前，由你来选择 $P_g,P_s,P_b$。

## 说明/提示

### 数据范围

- 对于 $10\%$ 的数据，保证最优解的 $P_g \le 10$；
- 对于 $30\%$ 的数据，保证最优解的 $P_g \le 100$。


## 样例 #1

### 输入

```
3
1 1 1
0 1 2
2 1 0```

### 输出

```
1 1 1```

# 题解

## 作者：CodyTheWolf (赞：4)

来自攻略组成员的首发题解：

------------
### [开头小广告：自己做的一个模板库OwO](https://www.luogu.org/blog/29354/Templet)

------------
## 算法考察：线性规划

## 思路：

直接暴力三层循环是稳稳的$O(1000^3)$也就是$O(10^9)$，我们考虑优化最后一个循环。

到第3个循环，也就是枚举Cu的分数时，我们可以把前面Au和Ag的分数先给每个队伍算好：

设第$i$个队伍的总分数在只有Au和Ag分数时是$tot_i$，拥有的Cu数量是$cu_i$

如果第一个队伍要赢过第$i$个队伍，设Cu的分数是k，明显有不等式：

$tot_1+k \times cu_1 \geq tot_i+k\times cu_i$

化简:

### $k \geq \frac{tot_i-tot_1}{cu_1-cu_i}$

但是这里$cu1-cu_i$是可0可负的，因此我们要分类讨论：

### $cu_1-cu_i > 0$ 我们有：$k \geq \frac{tot_i-tot_1}{cu_1-cu_i}$

### $cu_1-cu_i < 0$ 我们有：$k \leq \frac{tot_i-tot_1}{cu_1-cu_i}$

### $cu_1-cu_i = 0$ 我们有：当$tot_i \geq tot_1$时，1队伍绝对获胜（分数相等1排在最前）

我们想象一个数轴，作关于这些不等式的垂线，我们从1出发（积分最少为1）。

对于小于等于的不等式，我们一开始就是满足的，先累加进我们的答案，当我们穿过他（而不是停留在这）时，减去一个答案。因为我们都是整数答案，所以**小于等于号的右边要向下取整**。

对于大于等于的不等式，我们停留在这的时候，我们的答案便加上一个。因为我们都是整数答案，所以**大于等于号的右边要向上取整**。


对于数轴，我们不需要一个一个单位走，按照不等式右边排序即可，然后就可以按照$n$个不等式，从小到大跳着走了（反正中间也不可能出现不等式了）。

每跳到一个不等式，可能有其他的不等式跟这个不等式在同一个单位，这时候要**全部处理完毕才能更新答案**，很显然。

## 注意：

1.题目条件：Au分数大于等于Ag分数大于等于Cu分数，注意枚举的范围，也要注意最后一个循环用线性规划优化时不要超过Ag分数了。

2.有些条件是可以提前预判掉的，比如$k<=0$是不可能到达的条件。

# Code

```cpp
// luogu-judger-enable-o2
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

const int MAXN = 16, MAX = 1e3;

typedef pair<int, bool> pib;
int au[MAXN], ag[MAXN], cu[MAXN];
int tot[MAXN];
pib temp[MAXN];

int n;

int ans = 0, ansx = 1, ansy = 1, ansz = 1;

inline bool Compare(pib a, pib b)
{
    return a.first < b.first;
}

inline void Solve(int x, int y)
{
    int num = 0, tail = 0;

    for (int i = 1; i <= n; i++)
        tot[i] = au[i] * x + ag[i] * y;

    for (int i = 2; i <= n; i++)
    {
        double delta = tot[i] - tot[1], k = cu[1] - cu[i];

        if (!k)
        {
            num += (tot[i] >= tot[1]);
            continue;
        }
        if (k < 0 && delta > 0)
            continue;
        if (k > 0 && delta < 0)
        {
            num++;
            continue;
        }

        if (k > 0)
            temp[++tail] = make_pair(ceil(delta / k), true);
        else
            temp[++tail] = make_pair(floor(delta / k), false);
    }

    sort(temp + 1, temp + tail + 1, Compare);

    for (int i = 1; i <= tail; i++)
        if (!temp[i].second)
            num++;

    for (int i = 1; i <= tail; i++)
    {
        int j = i, cnt = 0;
        while (temp[j + 1].first == temp[i].first && j + 1 <= tail)
            j++;

        for (int k = i; k <= j; k++)
            if (temp[k].second)
                num++;
            else
                cnt++;

        if (num > ans && temp[i].first > 0 && temp[i].first <= y)
            ans = num, ansx = x, ansy = y, ansz = temp[i].first;

        i = j, num -= cnt;
    }

    return;
}

signed main(void)
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        scanf("%d %d %d", au + i, ag + i, cu + i);

    for (int i = 1; i <= MAX; i++)
        for (int j = 1; j <= i; j++)
            Solve(i, j);

    printf("%d %d %d\n", ansx, ansy, ansz);

    return 0;
}
```


---

## 作者：星空舞涵 (赞：1)

# 你谷上号，开冲

## 美好的一天从发题解开始QAQ

关于这道题其他几个大佬已经说得很good的，但是我想来点想我这样的蒟蒻能看懂的。

## 首先介绍坑点：

$1$.  不一定是第一名，只是排名尽量靠前。（刚开始给我写傻了）

$2$.  1000>=Pg>=Ps>=Pb>=1 这点很重要，金牌分数一定是最大的

## 方法：
首先$N^3$的枚举是不可能的，这辈子都不可能

但是最后一个循环我们是可以优化滴

每次枚举银牌和金牌的分数

记录每个队伍金牌银牌总分的和

然后我们来分析一波：

假设A队总分比你高，并且铜牌数不比你少(≥),那你肯定干不过他

假设A队总分比你高，但是铜牌没你多，当Ps≥x的情况下你可能比他高

	x的值可以是  分数差÷铜牌数差(向上取整)

假设A队总分和你一样  那就是比铜牌量呗，你的铜牌≥他的情况下你赢了(相同分数你赢)，其他情况他赢


假设A队总分没有你高，如果你的铜牌数不比他少(≥)，那你稳赢

假设A队总分没有你高，但是铜牌数比你多，当Ps≤x的情况下你赢

	x的值可以是  分数差÷铜牌数差(向下取整)
                        
一共就这6种情况（是不是和初中数学差不多）

我们处理完当前情况下你和其他队伍的关系

	就可以根据每一个结果是≥的柿子进行枚举了
    
 但是我要考虑一种特殊情况没有结果是≥的柿子
 
 对于这种情况我们可以发现题上给了一个要求Ps≥1
 
 我们只用额外枚举这个就可以了QAQ
 
 下面就是你们最想要的东西了
 
 变量名有点丑，根据中文命名的，码分也不是很好，请见谅
 
 ```cpp
#include<bits/stdc++.h>
using namespace std;
long long  n,cc,l[16],fen[16],ans,ansg=0,anss=0,ansb=0,maxx,fenn;
//1! 2= 3> 4<    l[i]代表的状态  1表示稳输   2表示稳赢   3表示铜牌分数大于某个值时赢    4表示铜牌分数小于某个值时赢 
struct cxk{long long  a,b,c;}d[16];
int main()
{

	cin>>n;
	for(int i=1;i<=n;i++)cin>>d[i].a>>d[i].b>>d[i].c;
	for(int i=1;i<=1000;i++)
	for(int j=1;j<=i;j++)
	{
		int cc=d[1].c;
		int zhong=i*d[1].a+j*d[1].b;
		for(int k=2;k<=n;k++)
		{
			int zzhong=i*d[k].a+j*d[k].b;//其他队伍的总分 (金牌银牌)
			if(zzhong>zhong)
			{
				if(d[k].c>=cc)l[k]=1;// （总分大，铜牌多）不可能超越 
				else 
				{
					int cha=cc-d[k].c;
					int ccha=(zzhong-zhong)/cha;
					if((zzhong-zhong)%cha!=0)ccha++;
					l[k]=3;
					fen[k]=ccha;
				}
			}
			if(zhong==zzhong)
			{
				if(d[k].c>cc)l[k]=1;
				else l[k]=2;
			}
			if(zzhong<zhong)
			{
				if(d[k].c<=cc)
				{
					l[k]=2;
				}
				else 
				{
					int cha=d[k].c-cc;
					int ccha=zhong-zzhong;
					ccha=ccha/cha;
					l[k]=4;
					fen[k]=ccha;
				}
			}
		}
		maxx=0;
		for(int k=2;k<=n;k++)//枚举满足仅仅保证Pb>1的情况 ，并且假设没有不等式的条件是>1,如果有下面会枚举QAQ 
		{
			if(l[k]==2)maxx++; 
			if(l[k]==4&&fen[k]>=1)maxx++;
		}
		if(maxx>ans)
		{
			ans=maxx;
			ansg=i;
			anss=j;
			ansb=1;	
		}
		for(int k=2;k<=n;k++)
		{
			if(l[k]==1||l[k]==2||l[k]==4)continue;//仅仅枚举符号是大于的不等式 
			if(fen[k]>j)continue;
			fenn=fen[k];
			maxx=1;//满足自己 
			for(int p=2;p<=n;p++)//其他有多少不等式可以被满足 
			{
				if(l[p]==1||k==p)continue;
				if(l[p]==2)maxx++;
				if(l[p]==3&&fenn>=fen[p])maxx++;
				if(l[p]==4&&fenn<=fen[p])maxx++;
			}
			if(maxx>ans)
			{
				ans=maxx;
				ansg=i;
				anss=j;
				ansb=fenn;
			}
			else if(maxx==ans)
			{
				if(ansg>=i&&ansb>=j)//金牌银牌分数一样比铜牌 
				{
					ansb=min(ansb,fenn);
				}
			}
		
		}
	}
	cout<<ansg<<" "<<anss<<" "<<ansb<<endl;
}
```

管理大大，通过吧QAQ


---

## 作者：Seauy (赞：1)

## 此题正解：线性规划

楼下已经说过了，但这题其实涉及不到线性规划的很多东西，实际上我觉得算法是：

先暴力枚举 $ Pg $ 与 $ Ps $，再取出一些关键的 $ Pb $ 值（当 $ Pb $ 在增长时，经过这些点会改变我的排名），离散化后选取最优的一段

这么说有些抽象，拿例子来说吧

我们已经把 $ Pg $ 与 $ Ps $ 枚举出来成为已知数了，那么如果把不确定的 $ Pb $ 的值看成变量 $ x $，会发现可以在平面直角坐标系上画出直线

$ y=B\cdot x+G \cdot Pg+ S \cdot Ps $

$ (1 \leq x \leq Ps) $

把我队与其他所有队的图像都画出来

（样例十分地不好，所有队伍的图像怎么样都是汇聚到一点的，下面是自己举的例子

![](https://cdn.luogu.com.cn/upload/image_hosting/g4z5zehy.png)

其中绿线为我队的位置

可以发现我队与橙队在 $ x=4 $ 时有一个交点，再仔细一看，$ x \geq 4 $ 以后我队就超过橙队了

来找找规律，发现，如果我队铜牌数比他们多，那么在交点及之后，我们会一直领先于他们。由于题目要整数解，这里的交点的 $ x $ 值要向上取整

再来看看我队与蓝队，发现在 $ x > 10 $ 之后，我队被蓝队甩开了。根据上一次发现的规律，这次的情况应该是我队的铜牌数比蓝队少。看一眼斜率，还真是。显然，这里的 $ x $ 要向下取整

有了铜牌数不等的情况，那么如果铜牌数一样呢？显然，大家在铜牌的分数上谁也比不过谁，只能依据金牌与银牌得分定乾坤了

于是算法就出来了，找到所有队图像交点的 $ x $ 坐标，并标记再次以后我队是领先别人了还是落后别人了。若斜率相同，则比较已经获得了的金牌与银牌的总分，计入我队的排名中。把所有 $ x $ 坐标排序了之后，扫一遍，在扫的过程中根据标记更改我队排名，然后比较，更新答案

还有其它情况吗？当然了

如果交点 $ x $ 不在 $ [1 , Ps] $ 内呢？这就比较麻烦了，设交点 x 坐标为 $ t $

1. 若 $ B_1>B_i $

当 $ t\leq 1 $ 时，我队一直会比这个队领先

当 $ t>Ps $ 时，我队会一直落后

2. 若 $ B_1<B_i $

当 $ t<1 $ 时，我队会一直落后

当 $ t \geq Ps $ 时，我队会一直领先

我队与交点不在题目范围内的队伍的 x 坐标不用加入离散化队列中，一开始就计入排名就行了

对于楼下的 Hack 数据，一定要注意先把 $ Pb=1 $ 的情况先与答案更新，不然会出现离散化队列中没有数据，而不更新答案的尴尬情景

然后你就能愉快地 AC 黒题了

具体求交点什么的，看下面的代码吧

总复杂度：$ O(n\cdot \log n) $ ~~常数极大~~

```cpp
#include<bits/stdc++.h>
using namespace std;

const int MAXN=15;
const int MAXV=1000;

int n;
int G[MAXN+5],S[MAXN+5],B[MAXN+5];
pair<int,bool> discre[MAXN+5];int num;

bool cmp(pair<int,bool> a,pair<int,bool> b)
{return (a.first==b.first ? a.second<b.second : a.first<b.first);}

struct msg
{
	int Rank;
	int Pg,Ps,Pb;
	void Print() {printf("%d %d %d\n",Pg,Ps,Pb);}
	int Base(int g,int s) {return Pg*g+Ps*s;}
	int Score(int g,int s,int b) {return Pb*b+Base(g,s);}
	bool OK() {return Pg>=Ps && Ps>=Pb;}
}ans,cnt;

void PrintP(pair<int,bool> ob)
{cout<<ob.first<<' '<<ob.second<<endl;} 

int CEIL(double a,double b)
{return ceil(a/b);}

int FLOR(double a,double b)
{return floor(a/b);}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d %d %d",&G[i],&S[i],&B[i]);
	ans.Rank=INT_MAX;
	ans.Pg=ans.Ps=ans.Pb=1;
	for(cnt.Pg=1;cnt.Pg<=MAXV;cnt.Pg++)
		for(cnt.Ps=1;cnt.Ps<=cnt.Pg;cnt.Ps++)
		{
			cnt.Rank=1;
			cnt.Pb=1;
			num=0;
			for(int i=2,temp;i<=n;i++)
			{
				if(B[1]==B[i])
				{
					cnt.Rank+=(cnt.Base(G[1],S[1])<cnt.Base(G[i],S[i]));
					continue;
				}
				if(B[1]>B[i])
				{
					temp=CEIL(cnt.Base(G[i]-G[1],S[i]-S[1]),B[1]-B[i]);
					if(temp<=1) continue;//所有时候都能赶超
					if(temp>MAXV) {cnt.Rank++;continue;}//无论如何也超不过他，认命
					discre[++num]=make_pair(temp,0);
					cnt.Rank++;//一开始先认孙子 
				}
				else//B[1]<B[i]
				{
					temp=FLOR(cnt.Base(G[i]-G[1],S[i]-S[1]),B[1]-B[i]);
					if(temp>=MAXV) continue;
					if(temp<1) {cnt.Rank++;continue;}
					discre[++num]=make_pair(temp,1);
				}
			}
			sort(discre+1,discre+num+1,cmp);
			if(cnt.Rank<ans.Rank) ans=cnt;
			for(int i=1,j,k;i<=num;i=j+1)
			{
				j=i;
				while(discre[i].first==discre[j+1].first && j<num) j++;
				for(k=i;discre[k].second==0 && k<=j;k++) cnt.Rank--;
				cnt.Pb=discre[i].first;
				if(cnt.Pb>cnt.Ps) break;
				if(cnt.Rank<ans.Rank) ans=cnt;
				for(;discre[k].second && k<=j;k++) cnt.Rank++;
			}
		}
	ans.Print();
	return 0; 
} 
```

~~我不会告诉泥萌我在 $ Pg\geq Ps\geq Pb $ 这点上卡了半天~~

感觉并没有黒题难度……

---

## 作者：剑鞘承天 (赞：0)

本人的第五篇题解（如果算上没通过的话），其实本题也是我的第三道蓝题，所以一个萌新，所写的题解可能会有些许问题，但应该可以做到最易理解。

阅读题目，我们为了~~面子~~集体荣誉而需要令自己的队伍排名**尽量靠前**，注意不是**第一**，故要设定每个牌对应的分数来~~自欺欺人~~完成目的。

观察题目数据，按正常人的想法三层循环暴力的话，_$O(1000^3)$_ 将会是永远越不去的坎儿。

故再次阅读题目，发现，我们可以将控制两个变量，然后去寻找第三个变量的范围从而做到优化的目的。

理论上，控制银、铜数去查金牌或是金、铜数去查银牌也是可以的，但根据题中所给的：$1000>=Pg>=Ps>=Pb>=1$ 不难发现上述两种做法编写难度显然大于控制金、银而去查铜牌，故铜牌的那一层循环将是优化的对象。

优化的方式很好理解，先将金、银已得的分数算出，后将自己与别的队伍进行比较，情况有四种，并将四种状态记录到数组 con 中：

1. 不论铜牌分数是多少，我方稳输，记状态为0。
2. 不论铜牌分数是多少，我方稳赢，记状态为1。
3. 铜牌分数小于 _某值_ 时，我方可赢，记状态为2。
4. 铜牌分数大于 _某值_ 时，我方可赢，记状态为3。

于是情况便明朗起来，除输入输出外，程序将主要分为两个模块：记录该种情况为何种状态，判断该种状态下铜牌分数可否让我获胜。听上去很简单，不是吗？

现在我们的问题是，如何找出我们需要的 _某值_ ，记为 dv，这将是接下来解题的关键。

于是我们开始推推式子，将总分记为 totle，金、银总分记为 tot，我们要求：

$totle_{1}\geq totle_{else}$

即：

$tot_{1}+Cu_{1}\times dv\geq tot_{else}+Cu_{else}\times dv$

简单化简后，有：

$dv\geq \frac{tot_{else}-tot_{1}}{Cu_{1}-Cu_{else}}$

共有k支队伍，每一支队伍与一队都有不同的 dv，故可以将 dv 储存在一个数组 po 中，即：

$po_{k}\geq \frac{tot_{k}-tot_{1}}{Cu_{1}-Cu_{k}}$

值得注意的是，如果双方的铜牌数相等将出现除以0的问题而 RE，记得在此处加以特判。

现在，我们需要的 _某值_ 已经具象为一个可以讨论计算的数据，故我们所需要的四种状态便可以用 $po_{k}$ 来具体定义：

1. 若 $po_{k}>$ _银牌分数_ (记为 ps )，我方稳输，记状态为0。
2. 若 $po_{k}<0$ ，我方稳赢，记状态为1。
3. 铜牌分数小于 $po_{k}$ 时，我方可赢，记状态为2。
4. 铜牌分数大于 $po_{k}$ 时，我方可赢，记状态为3。

故，计算出 $po_{k}$，将状态记入 con 后，我们循环每一支队伍，并将胜利次数计入 ma，而关于 con 的判断语句将进行如下操作：

1. 若 $con_{k}$ 为0，即我方必输， $continue$。
2. 若 $con_{k}$ 为1，即我方必赢， ma++。
3. 若 $con_{k}$ 为2，即分数小于 $po_{k}$ 时,我们令铜牌分数为1然后 ma++。
4. 若 $con_{k}$ 为3，即分数不小于 $po_{k}$ 时,我们令铜牌分数为 $po_{k}$ 然后ma++。

注意到情况3与情况4不能同时进行统计，故在真正实现时，我们将两种情况分开统计。


每计算出一组答案同已经记录过得答案进行比对、判断并更新已有答案，最后得出最终答案并输出。

最后附上 AC 代码（对了，在写对拍时与另一篇题解的答案有冲突，上交却依然  AC ，还请各路大佬一同修正并轻喷）：

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,g[20],s[20],b[20],pg=1,ps=1,pb=1,pp,tot1,tot,dv,ma,po[20];
int con[20];//0 no way,1 no problem,2 k小于某值,3 k大于某值 

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>g[i]>>s[i]>>b[i];
	}
	int cu=b[1];
	for(int i=1;i<=1000;i++)//循环金牌分数
	{
		for(int j=1;j<=i;j++)//银牌分数不能大于金牌，铜牌同理
		{
			tot1=i*g[1]+j*s[1];
			for(int k=2;k<=n;k++)
			{
				tot=i*g[k]+j*s[k];
				if(cu-b[k])
				{
					dv=abs((tot-tot1)/(cu-b[k]));
				}
				
				if(tot>tot1)
				{
					if(cu<=b[k])
					{
						con[k]=0;
					}
					else
					{
						if(dv*(cu-b[k])<tot-tot1)
						{
							dv++;
						}
						con[k]=3;
						po[k]=dv;
					}
				}
				else if(tot==tot1)
				{
					if(cu>=b[k])
					{
						con[k]=1;
					}
					else
					{
						con[k]=0;
					}
				}
				else
				{
					if(cu>=b[k])
					{
						con[k]=1;
					}
					else
					{
						con[k]=2;
						po[k]=dv;
					}
				}
			}
			ma=0;
			for(int k=2;k<=n;k++)
			{
				if(con[k]==1||(con[k]==2&&po[k]>=1))
                //此时判定稳赢与小于某值时胜利的情况，并在后续操作中将铜牌赋为1分
				{
					ma++;
				}
			}
			if(ma>pp)
			{
				pp=ma;
				pg=i;
				ps=j;
				pb=1;
			}
			for(int k=2;k<=n;k++)
			{
				if(con[k]==0||con[k]==1||con[k]==2||po[k]>j)
				{
					continue;
				}
				ma=1;
				for(int l=2;l<=n;l++)
				{
					if(con[l]==0||l==k)
					{
						continue;
					}
					else if(con[l]==1||(con[l]==3&&po[k]>=po[l])||(con[l]==2&&po[k]<=po[l]))
					{
						ma++;
					}
				}
				if(ma>pp)
				{
					pp=ma;
					pg=i;
					ps=j;
					pb=po[k];
				}
				else if(ma==pp&&pg>=i&&ps>=j)
				{
					pb=min(pb,po[k]);
				}
			}
		}
	}
	cout<<pg<<" "<<ps<<" "<<pb<<endl; 
    return 0;
}
```
---
因为格式的原因给审核带来了很多麻烦……非常抱歉！

---

