# [POI 2011] TEM-Temperature

## 题目描述

The Byteotian Institute of Meteorology (BIM) measures the air temperature  daily.

The measurement is done automatically, and its result immediately printed.

Unfortunately, the ink in the printer has long dried out...

The employees of BIM however realised the fact only recently, when the    Byteotian Organisation for Meteorology (BOM) requested access to that data.

An eager intern by the name of Byteasar saved the day, as he systematically    noted down the temperatures reported by two domestic alcohol thermometers    placed on the north and south outside wall of the BIM building.

It was established decades ago by various BIM employees that the temperature    reported by the thermometer on the south wall of the building is never lower    than the actual temperature, while that reported by the thermometer on the    north wall of the building is never higher than the actual temperature.

Thus even though the exact temperatures for each day remain somewhat of    a mystery, the range they were in is known at least.

Fortunately for everyone involved (except Byteasar and you, perhaps),    BOM does not require exact temperatures. They only want to know the longest    period in which the temperature was not dropping (i.e. on each successive    day it was no smaller than on the day before).

In fact, the veteran head of BIM knows very well that BOM would like this    period as long as possible.

To whitewash the negligence he insists that Byteasar determines, based on    his valuable notes, the longest period in which the temperature    could have been not dropping.

Now this is a task that Byteasar did not quite expect on his BIM internship,    and he honestly has no idea how to tackle it.

He asks you for help in writing a program that determines the longest such    period.

某国进行了连续 $ n $ ( $ 1 \le n \le 1,000,000 $）天的温度测量，测量存在误差，测量结果是第 $i$ 天温度在 $[l_i,r_i]$ 范围内。

求最长的连续的一段，满足该段内可能温度不降。


## 样例 #1

### 输入

```
6
6 10
1 5
4 8
2 5
6 8
3 5```

### 输出

```
4```

# 题解

## 作者：Lonely_NewYear (赞：42)

# 洛谷 P3522 题解

## 前置知识 单调队列

单调队列可以通过不断弹出已经无用的决策来维护队列内的递增或递减。

举个例子，如果 OI 只注重第一名，而且有个神犇既比我小又比我强，那么我就可以退役了。因为我能参加的比赛他也能参加，而我又拿不到第一名，这时就可以把我弹出 OI 的队列了。

还有一点，就是如果某个人已经上大学了，那么即使他提高组能拿满分，他也参加不了，因为他年龄太大了，这时也要把他弹出。

具体实现时可以维护一个双端队列，每次读入今年的新的选手，并从队头开始弹出年龄过大的人，再从队尾弹出比当前选手弱的人，最后把当前选手插入队尾，就可以维护出每一年的比赛谁会拿第一名（队头）。

## 题目大意

对每一天的天气都给出上界和下界，求最长可能有多少个连续天的温度不下降（注意是可能，不要求一定！）。

很显然，这一段的每一天的最高温度都必须大于这一天之前的最低温度最大值。

## 题目分析

根据上面的分析，可以得出需要维护当前这一天前面几天的最低温度最大值，这个最低温度就相当于选手有多强。那么年龄又是什么呢？可以发现如果当前这一天的最高温度小于这个人的最低温度，那么这个人就可以退役了，因为它无法再为这一道题的答案做贡献了。

## 具体实现

维护一个双端队列，先从队头开始弹出最低温度过大的天，此时更新一下 $ans=\text{当前的天数}-\text{队头的天数}+1$，再从队尾弹出所有比这一天的最低温度小的天（维护单调性）。为了维护比较方便，推荐使用结构体。

```cpp
#include<cstdio>
#include<deque>
#include<algorithm>
using namespace std;
struct node
{
	int l,r,id;//id表示是第几天
};
int main()
{
	int n,ans=1;
	scanf("%d",&n);
	deque<node> q;
	for(int i=1;i<=n;i++)
	{
		int l,r;
		scanf("%d%d",&l,&r);
		while(!q.empty()&&q.front().l>r)//要判断队列非空哦
		{
			q.pop_front();
		}
		if(!q.empty())
		{
			ans=max(ans,i-q.front().id+1);
		}
		while(!q.empty()&&q.back().l<l)
		{
			q.pop_back();
		}
		q.push_back((node){l,r,i});
	}
	printf("%d",ans);
	return 0;
}
```

如果这样做会发现样例都过不了，哪里出问题了呢？

如果有一天的最低温度特别大，把前面的所有天都弹出了，不代表就要重新从这一天开始计数啊，前面的天还是可以用的，弹出这几天只是为了维护单调性。所以可以在弹出时记录一下最后一个被弹出的天，并把它赋值给这一天的天数。这个天数就代表这一段是从哪一天开始的，并且结构体中记录着这一段的最低温度最大值。

AC 代码：

```cpp
#include<cstdio>
#include<deque>
#include<algorithm>
using namespace std;
struct node
{
	int l,r,id;//id表示是第几天
};
int main()
{
	int n,ans=1;
	scanf("%d",&n);
	deque<node> q;
	for(int i=1;i<=n;i++)
	{
		int l,r;
		scanf("%d%d",&l,&r);
		while(!q.empty()&&q.front().l>r)//要判断队列非空哦
		{
			q.pop_front();
		}
		if(!q.empty())
		{
			ans=max(ans,i-q.front().id+1);
		}
		int tmp=i;
		while(!q.empty()&&q.back().l<l)
		{
			tmp=q.back().id;//维护这一段的起始天
			q.pop_back();
		}
		q.push_back((node){l,r,tmp});
	}
	printf("%d",ans);
	return 0;
}
```

谢谢观看。

---

## 作者：liangsheng (赞：17)

这是一篇较详细的**单调队列**解法题解 !

首先,我们要求出**最长**的**连续的一段**并且**不下降**的温度

相信大多数人看到要求的和我一样一脸懵 *

~~好了,回归正题~~

假设我们现在有一段连续且不下降的序列

那么经过分析我们可以知道:**只有这段序列中每天的最高温度大于这段序列中最大的最低温度**才能满足**不下降**

在这里,我们把这些连续天数中最低温度最大的那个放在队头,这样的好处就是:我们新入队的那一天的最高温度要和队头的最低温度比较,若小于队头那一天的最低温度,说明不能满足**不下降**,若大于说明可以添加

好了,只说原理相信很多像我一样的蒟蒻还是不明白,下面我们以样例为例子手动模拟一下:

这里我们定义: `l: 头指针, r: 尾指针 len: 最长连续不下降天数`

首先第一个元素入队,队列中记录对应的天数

|1  |  |
| :----------- | :----------- |

入队后,队列只有一个数1,代表第一天

此时 l = r = 1, len = 1

然后第二个元素入队比较,很明显第二天的最高温度小于队头的最低温度,说明第一天和第二天不能满足**不下降**的要求,但我们依然要入队,这是为什么呢?我来解释一下,大家可以思考,若第二天不入队及时后面的再入队,第一天和后面的也不能满足**连续**的要求,所以我们这里选择入队,但不会再去考虑第一天的温度

| 1 |2  |  |
| :----------- | :----------- | :----------- |

若不考虑第一天,我们要进行 l++
入队后 r++, 此时 l = r = 2, len = 1

下一步把第三个元素进行比较,很明显满足要求可以入队,但这时根据我上面所说的,我们总是把这段连续天数中最大的最低温度放在队头,所以我们可以得到入队后的情况:

|  1| 3 |  |  |
| :----------- | :----------- | :----------- | :----------- |

这时我们可以发现把之前的2覆盖了,那么这时候我们应该怎么计算天数呢?

我们可以思考:既然这段连续天数中最大的最低温度放在队头,那么队头的前一位肯定不在这段序列中,并且它应该是这段序列中开始满足要求的那天的前一天(这里2就是这段序列开始满足的第一天,而1则是2的前一天)

所以: `len = i-q[l-1]`

接下来的几天没有什么要注意的地方,我们只需要把第三天这里我们要注意的理解,那么就可以理解下面的代码

~~害,终于结束了~~

下面就是代码实现环节 ~~(码风较丑还请担待)~~

```cpp

#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cmath>
 
using namespace std;

typedef long long ll;
const int N = 1e6 + 5;

int n;
int a[N], b[N], q[N];

int main() {
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i];
    }
    int l = 1, r = 0, ans = 0, len;
    for(int i = 1; i <= n; i++) {
        while(l <= r && a[q[l]] > b[i]) l++;  //若第i天最高温度小于队头最低温度
        if(l > r) len = 1;
        else len = i - q[l - 1];
        ans = max(ans, len);	//记录最大天数
        while(l <= r && a[q[r]] < a[i]) r--;  //把这段序列中最大的最低温度放在队头
        q[++r] = i;  //入队
    }
    cout << ans << endl;
    return 0;
}
```


---

## 作者：Ofnoname (赞：14)

这道单调队列可不一般，只要一段区间至少有一点重叠就可以看做连续。

我们维护一个队列，从左往右扫，保证队列里的左端点单调递减。

- 对于一个新的点来说，只有他的r大于之前所有l的最大值时才有答案，而队列里的左端点是但单调递减的，所以不断弹出队列左端直到左端点降到合适位置即可

- 接下来要把这个点加入队列，因为要满足单调递减，所以应该把左端点比我低的点全部从右弹出，但是弹完以后并不是把新点直接入队，而是加入本线段与最后一个弹出线段的交集，显然本线段上面多出来的一截不能取。

（如图，再加入4号线段时，2,3号线段会被排除，最终加入的红色线段为2,4的交集）

![](https://s2.ax1x.com/2019/11/11/MQqAyT.png)

```cpp
#define MAX 1000000 + 7
#include <bits/stdc++.h>
using namespace std;

int N, ans, t, l[MAX], r[MAX];
deque <int> Q;

int main()
{
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
	{
		scanf("%d%d", &l[i], &r[i]);
		while (Q.size() && l[Q.front()] > r[i])
			Q.pop_front();
		if (Q.size())
			ans = max(ans, i - Q.front() + 1);
		
		t = i;
		while (Q.size() && l[i] > l[Q.back()])
			t = Q.back(), Q.pop_back();
		l[t] = l[i], Q.push_back(t);
	}printf("%d\n", ans);
}
```

---

## 作者：Holy_Push (赞：8)

作为一个蒟蒻，我用不正常方法在无数次错误之后终于过了这道题。

首先要声明的是，虽然我的代码时间复杂度并不优秀，常数巨大，代码难度大，而且还用了骗分、$O_2$等方法水过此题，但是我觉得我的思路对其他题可能有一些帮助，所以还是希望能分享一下。如果嫌麻烦或者我描述得不够清晰看不懂的话，可以看一下其他题解的单调队列做法。

首先发现，由于本题是温度“不下降”，而不是“严格上升”，所以可以大胆地离散。我们假设离散后的第$i$天温度范围为$L[i],R[i]$。然后我们考虑使用动态规划。

令$f[i][j]$表示以第$i$天温度为$j$的状态结尾时，最长有连续的多少天。我们可以很容易列出一个转移方程：

当$L[i]≤j≤R[i]$时，$f[i][j]=max(f[i-1][k],j)+1(k≤j),$ 否则$f[i][j]=0$。接下来我们考虑如何优化转移。

首先$i$这一维可以滚动掉，这很显然。然后我们又可以发现，$f[i][j]$在温度范围内是单调不减的。因此我们可以省去这个$max$环节，直接记录前缀$max$即可。时间复杂度简化为$O(n^2)$，依然不能通过此题。我们需要挖掘更多性质。我们考虑用线段树优化$DP$。

线段树中第$j$位表示的就是这一天温度为$j$时的最长连续天数。方便起见，我们把第$i-1$天的线段树称为$S$，第$i$天的线段树称为$T$（在实现的时候可以用同一棵线段树）。我们现在要做的就是把$S$快速变为$T$。

两天的温度状况有以下四种情况：

$1.L[i]>R[i-1]$，也就是今天的温度严格大于昨天的温度。这种情况很好考虑，我们只需要找出$S$中$[L[i-1],R[i-1]]$中的最大值$Max,$然后在$T$中把$[L[i],R[i]]$全部赋值为$Max$即可。由于单调性，我们找$Max$相当于单点询问$S$中$R[i-1]$位上的值。

$2.R[i]<L[i-1]$，也就是今天的温度严格小于昨天的温度。这种情况也其实很好考虑。由于今天的温度严格小于昨天的温度，所以$dp$的时候今天无法从昨天转移过来，因此直接在$T$中把$[L[i],R[i]]$全部赋值为$1$即可。

$3.L[i]≥L[i-1]$，也就是今天的最低温度比昨天高。这种情况中，我们又要讨论。在$[L[i],min(R[i],R[i-1])]$这段区间中，$f[i][j]$显然从$f[i-1][j]$转移过来最优，所以$T$中的这一段即为$S$中的这一段全部$+1$。而如果$R[i]>R[i-1]$的话，也就是说今天的最高温度比昨天高，那么$f[i][k](k∈[R[i-1]+1,R[i]])$这一段显然从$f[i-1][R[i-1]]$转移来最优，因此集体赋值为$S$中$R[i-1]$这一位的数$+1$。

$4.L[i]<L[i-1]$的时候与上一种情况类似，可以由你们自行思考，这里就不写了$QwQ$。

综上所述，我们只需要写一棵线段树，能够实现区间赋值、区间加和单点询问这三种操作即可。时间复杂度为$O(nlogn)$，常数巨大。细节挺多的，但最要注意两点：

$1.$上文提过，不在$[L[i],R[i]]$中的其他段在最后均要赋值为$0$。

$2.$每次做完之后都要更新最大值，最后输出的时候需要输出这个最大值。

然后我们发现我们$T$的很惨$……$我是怎么~~骗分~~优化的呢？

$1.$上文提到过的，离散。

$2.$快读是必须的，注意读入有负数。

$3.$能尽量减少线段树次数就尽量减少。

$4.$实在优化不下去的时候，我尝试着把线段树上界改为$1e6$（理论上有$2n$个值所以上界应该为$2e6$），抱着骗分的心态就过了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+1,M=1000000;

int n,len,ans,cnt;
int L[N],R[N],ls[N<<1];

struct node
{
	int add=-1,ass;
} t[N*6];

struct In
{
	int val,id,sum;
	bool operator < (const In &x)const {return val<x.val;}
}u[N<<1];

void pushdown(int i)
{
	int ls=i<<1,rs=ls|1;
	if (t[i].ass!=-1)
	{
		t[ls].ass=t[rs].ass=t[i].ass+t[i].add;
		t[i].ass=-1;t[i].add=0;t[ls].add=t[rs].add=0;
	}
	if (t[i].add)
	{
		t[ls].add+=t[i].add;t[rs].add+=t[i].add;
		t[i].add=0;
	}
}

void update(int i,int l,int r,int x,int y,int add)
{
	if (l>=x&&r<=y) {t[i].add+=add;return;}
	pushdown(i);int mid=(l+r)>>1;
	if (mid>=x) update(i<<1,l,mid,x,y,add);
	if (mid<y) update(i<<1|1,mid+1,r,x,y,add);
}

void assign(int i,int l,int r,int x,int y,int val)
{
	if (l>=x&&r<=y) {t[i].ass=val;t[i].add=0;return;}
	pushdown(i);int mid=(l+r)>>1;
	if (mid>=x) assign(i<<1,l,mid,x,y,val);
	if (mid<y) assign(i<<1|1,mid+1,r,x,y,val);
}

int query(int i,int l,int r,int x)
{
	if (l==r||t[i].ass!=-1) return t[i].add+t[i].ass;
	pushdown(i);int mid=(l+r)>>1;
	if (mid>=x) return query(i<<1,l,mid,x);
		else return query(i<<1|1,mid+1,r,x);
}

void read(int &x)
{
	x=0;char s=getchar();int t=1;
	while (!isdigit(s)) {if (s=='-') t=-1;s=getchar();}
	while (isdigit(s)) {x=(x<<1)+(x<<3)+s-'0';s=getchar();}
	x*=t;
}

int main()
{
	read(n);len=1;
	for (int i=1;i<=n;++i)
	{
		read(L[i]);read(R[i]);
		u[++cnt].val=L[i];u[cnt].id=i;u[cnt].sum=1;
		u[++cnt].val=R[i];u[cnt].id=i;u[cnt].sum=2;
	}
	sort(u+1,u+cnt+1);
	ls[0]=1;
	for (int i=1;i<=cnt;++i)
		if (u[i].val!=u[i-1].val) ls[i]=min(ls[i-1]+1,M);
			else ls[i]=ls[i-1];
	for (int i=1;i<=cnt;++i)
		if (u[i].sum==1) L[u[i].id]=ls[i];
			else R[u[i].id]=ls[i];
	assign(1,1,M,1,M,0);assign(1,1,M,L[1],R[1],1);ans=1;
	for (int i=2;i<=n;++i)
	{
		if (L[i]>R[i-1])
		{
			int g=query(1,1,M,R[i-1])+1;
			assign(1,1,M,1,M,0);assign(1,1,M,L[i],R[i],g);
			ans=max(ans,g);
		} else
		if (R[i]<L[i-1])
		{
			assign(1,1,M,1,M,0);assign(1,1,M,L[i],R[i],1);
		} else
		if (L[i]>=L[i-1])
		{
			if (R[i]>R[i-1]) assign(1,1,M,R[i-1]+1,R[i],query(1,1,M,R[i-1])+1);
			update(1,1,M,L[i],min(R[i-1],R[i]),1);
			assign(1,1,M,1,L[i]-1,0);assign(1,1,M,R[i]+1,M,0);
			ans=max(ans,query(1,1,M,R[i]));
		} else
		{
			if (R[i]>R[i-1]) assign(1,1,M,R[i-1]+1,R[i],query(1,1,M,R[i-1])+1);
			update(1,1,M,L[i-1],min(R[i-1],R[i]),1);assign(1,1,M,L[i],L[i-1]-1,1);
			assign(1,1,M,1,L[i]-1,0);assign(1,1,M,R[i]+1,M,0);
			ans=max(ans,query(1,1,M,R[i]));
		}
	}
	printf("%d\n",ans);
}
```


---

## 作者：chenxinyang2006 (赞：7)

- **题意：**

  你要给一个长度为 $n$ 的序列 $a$ 每一个位置填上一个数，第 $i$ 个位置可以填 $[x_i,y_i]$ 内的数，求一段最长的区间 $[l,r]$，满足填上数后可能不降
  
- **解析**

  注意到求的是最长区间 $[l,r]$，所以可以枚举右端点 $r$，然后扫描维护 $l$
  
  很显然的是这样维护的过程中 $l$ 是不降的，如果 $[l,r]$ 不行，$[l',r + 1](l' < l)$ 显然也不行
  
  对于一个区间 $[l,r]$，第 $i$ 个数至少要填 $\max(x_k),l \le k \le i$，才能满足不降
  
  但是如果 $\max(x_k) > y_i$，就不合法了
  
  所以如果要想从 $r$ 转移到 $r+1$，就是要把右端点 $l$ 向右边移动，使得 $[l,r]$ 中所有数都合法
  
  实际上我们只需要判 $r+1$ 是否合法就行了，对于 $[l,r]$ 的数，前缀 $\max$ 相比左端点在 $l$ 时必然是不增的，肯定满足条件
  
  于是写个 ST 表维护 RMQ 就完事了
  
  参考代码：
  
```cpp
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
int n;
int x[1000005],y[1000005];
int st[20][1000005];//st[i][j] [j,j + 2 ^ i - 1] 的最大值

int qry(int l,int r){
	int x = log2(r - l + 1);
	return max(st[x][l],st[x][r - (1 << x) + 1]);
}

int main(){  
    scanf("%d",&n);
    for(int i = 1;i <= n;i++) scanf("%d%d",&x[i],&y[i]);
    for(int j = 1;j <= n;j++) st[0][j] = x[j];
    for(int i = 1;i <= 19;i++){
    	for(int j = 1;j <= n;j++){
    		if(j + (1 << i) - 1 > n) break;
    		st[i][j] = max(st[i - 1][j],st[i - 1][j + (1 << (i - 1))]);
    	}
    } 
    int l = 1,ans = 0;
    for(int r = 1;r <= n;r++){
    	while(l <= r && qry(l,r) > y[r]) l++;
    	ans = max(ans,r - l + 1);
    }
    printf("%d\n",ans);
	return 0;
}
```

---

## 作者：zhendelan (赞：6)

[题面](https://www.luogu.com.cn/problem/P3522)  

当$[l,r-1]$是可能不降的时候，$R[r] >= max \{ L[l],L[l+1],...,L[r-1]\}$，$[l,r]$也是不降的。  

我觉得这个结论好像并没有这么显然，但其他题解都直接写出来了。也可能是我太菜了，我来证一下吧。

证明: 我们可以模拟区间$[l,r-1]$的每个点的温度选择。设当前要加入的点为$i$，$[l,i-1]$的温度为$t$，那么$temp[i]>=\max\{L[i],t\}$。我们让$temp[i]$ 尽量小，就会等于$\max\{L[i],t\}$。  
$t$的大小显然是一个子问题，归纳法可以证明出$[l,r-1]$的$temp[r-1]$为$\max \{L[l],L[l+1],...,L[r-1]\}$  
让$R[r]>=\max \{ temp[r-1]\}$就可以得到上面的结论。

如果$R[r] < max \{ L[l],L[l+1],...,L[r-1]\}$，那$l$肯定已经不可以作为左端点了，可以扔掉。

那我们用单调队列维护一个$L$单调减，$st$单调增的序列就可以了。$L$表示的是一段区间的$max \{ L[i]\}$。$st$则表示这个区间的开始节点。  

也就是说，对于单调队列中所有的决策点$st$,$[st,i]$都是可能不降的区间。  
我们在枚举$i+1$时就用这些区间更新答案。  

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e6+20;
int n;
int l[N],r[N],q[N],st[N],ans=0;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&l[i],&r[i]);
	int h=1,t=0;
	for(int i=1;i<=n;i++)
	{
		while(h<=t && r[i]<l[q[h]])h++;
		if(h<=t)ans=max(ans,i-st[h]+1);
		int tmp=i;
		while(h<=t && l[i] > l[q[t]])
			tmp = st[t--];
		q[++t]=i;
		st[t]=tmp;
	}
	printf("%d\n",ans);
}
```


---

## 作者：Purslane (赞：4)

## Solution

数据结构优化 DP .

LIS 问题我们的状态比较固定 : $dp_{i,j}$ 表示以 $i$ 为末尾 , 长度为 $j$ 的不下降子序列最后一个数最小是多少 .

但是这道题其实是连续段 , 所以我们用 $i-1$ 转移 .

考虑在 $dp_{i-1,j-1}$ 后面接一个 $[l,r]$ 范围内的数 , 变成 $dp_{i,j}$ .

分类讨论 :

- 当 $dp_{i-1,j-1}>r$ 时 , 显然接不上去 , 也就无法转移 ;

- 当 $l \le dp_{i-1,j-1} \le r$ , 这时候应该接自己 ( $dp_{i-1,j-1}$ ) , 不变 .

- 当 $dp_{i-1,j-1}<l$ 时 , 这应该接 $l$ .

此外 , $dp_{i,0}=l$ .

我们发现 , 转移方程只有赋值 ( 平移 ) 操作 , 考虑使用一种可以平移一段区间的数据结构来维护他 , 而且应该支持收尾插入删除 , 访问首尾元素 .

deque ! 具体实现的时候 , 应当 :

1. 把末尾过大的数删掉 ;

2. 把首部过小的数换为 $l$ ;

3. 在首部插入 $l$ .

复杂度过高 . 我们发现 , 它的连续段比较多 , 把相同的数压成一个数即可 .

这样复杂度有保证么 ? 显然 , 每一次我们都最多插入一个元素 , 有些给删掉的不会再加进来 , 所以复杂度是 $O(n)$ .

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
using namespace std;
int ans,cnt,tmp; deque<pair<int,int>> q;
int main() {
	freopen("1.in","r",stdin);
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	int n;cin>>n;
	ffor(i,1,n) {
		int l,r;cin>>l>>r;
		while(cnt&&q.back().first>r) cnt-=q.back().second,q.pop_back();
		tmp=0;
		while(cnt&&q.front().first<l) tmp+=q.front().second,cnt-=q.front().second,q.pop_front();
		q.push_front({l,tmp+1}),cnt+=tmp+1;
		ans=max(ans,cnt);
	}
	cout<<ans;
	return 0;
}
```

短小精悍 .

这题过于简单了 , 我们来一个难一点的 :

[CF809D](https://www.luogu.com.cn/problem/CF809D)

题解参阅 [此处](https://www.luogu.com.cn/paste/qnwdae58) .

---

## 作者：fanypcd (赞：1)

#### 题意：

给定 n 天的温度范围 $[l_i,r_i]$，求最优情况下最多能有连续的多少天温度单调不降。

#### 思路：

单调队列来维护每一天最多能往前扩展到第几天（显然当前天能扩展到的最早位置不会晚于下一天能扩展到的最早位置），总的复杂度 $O(n)$。

每扫到一天，首先弹出队头的最低温比本天的最高温还高的天（无效位置）。

然后队列中剩下的都是可行的，此时的答案就是当前遍历到的天的编号减去队头编号再加一。

现在考虑弹出队尾的冗余元素，即队尾所有最低温低于当前天最低温的位置（既然会到当前天，任何时刻温度不会低于当前天的最低温）。

然后将当前这天加入队列，注意此时当前天的最高温也不能高于最后弹出的那个元素的最高温。

此时只是改变了最后弹出的那天的温度范围（即能满足到当天的限制），所以入队的标号是最后弹出的那天。（本质是修改）。

#### Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
inline void read(int &x)
{
	x = 0;
	int f = 0;
	char ch = getchar();
	while(ch < '0' || ch > '9')
	{
		f |= ch == '-';
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9')
	{
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	x = f ? -x : x;
	return;
}
#define N 1000005
int n, l[N], r[N];
deque<int> q;
signed main()
{
	read(n);
	for(int i = 1; i <= n; i++)
	{
		read(l[i]), read(r[i]);
	}
	int ans = 1;
	for(int i = 1; i <= n; i++)
	{
		while(!q.empty() && l[q.front()] > r[i])
		{
			q.pop_front();
		}
		if(!q.empty())
		{
			ans = max(ans, i - q.front() + 1);
		}
		int last = i;
		while(!q.empty() && l[q.back()] < l[i])
		{
			last = q.back();
			q.pop_back();
		}
		l[last] = l[i];
		q.push_back(last);
	}
	printf("%d", ans);
	return 0;
}
```

---

## 作者：Galex (赞：1)

题意其他dalao已经解释的很清楚了，只要一天的最高可能温度比所有之前选择的天数的最低温度的最大值要大即可选择这一天。很明显是可以用 **单调队列** 来维护之前区间最低温度的最大值。然后你脑袋一热，大喊一声：“这不水题吗？”把模板一复制，改点细节，做完了！

就在你沾沾自喜又切了一道蓝题时，样例输出把你拉回了现实。没错，这样写连样例都不对。为什么呢？因为弹出数只是为了维护单调性，但计数并不是从当前开始啊！所以我们可以引入一个变量 $tmp$ ，表示当前的区间是从 $tmp$  开始的，然后把 $l[tmp]$ 改成 $l[i]$ ，这样就实现了开头不变，然后最大值也修改的操作。


```cpp
#include <bits/stdc++.h>
using namespace std;

int read(){
	int s = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9'){
		if (ch == '-')
			f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
		s = (s << 1) + (s << 3) + (ch ^ 48), ch = getchar();
	return s * f;
}

int n;
int l[1000005], r[1000005];
int q[1000005], head = 1, tail = 1, ans = 0;

int main(){
	n = read();
	for (int i = 1; i <= n; i++){
		l[i] = read(), r[i] = read();
		while (tail > head && r[i] < l[q[head]])//前面的最大值太大，弹出队首
			head++;
     	//核心部分 
		int tmp = i;//纪录最后一个弹出的值 
		while (tail > head && l[i] > l[q[tail - 1]])//维护单调性 
			tmp = q[--tail];
		l[tmp] = l[i], q[tail++] = tmp;//修改最大值并将tmp入队 
		ans = max(ans, i - q[head] + 1);//更新答案 
	}
	printf("%d", ans);
	return 0;
}
```

---

## 作者：xy_xw_for_2024 (赞：1)

感谢[h](https://blog.csdn.net/weixin_43904950/article/details/85161317) [c](https://blog.csdn.net/weixin_43904950)大佬提供的帮助

测量温度这道题，开始我想多了，然后就做成了一个nlogn的最长不下降子序列

经过讲解才知道是单调队列

我们发现，如果要使这个连续的天数最多，那么当天的最低温度就要尽可能的低

那么我们用一个类似于[单调栈（里面的二三题）](https://blog.csdn.net/qq_43890190/article/details/84873267)的方法来解

下面是代码：：
```
#include<cstdio>
#include<deque>
#include<iostream>
using namespace std;
inline void read(int &x) {
    x=0;
    int f=1;
    char s=getchar();
    while(s<'0'||s>'9') {
        if(s=='-')
            f=-1;
        s=getchar();
    }
    while(s>='0'&&s<='9') {
        x=x*10+s-48;
        s=getchar();
    }
    x*=f;
}
inline void pr(int x) {
    if(x<0) {
        putchar('-');
        x=-x;
    }
    if(x>9)
        pr(x/10);
    putchar(x%10+48);
}//快读快输不解释
struct node {
    int l,r;
}a[1000005];
deque<int>q;//双向队列q里面存的是下标
int i,n,j,k,ans,o;
int main() {
    read(n);
    for(i=1;i<=n;i++)
        read(a[i].l),read(a[i].r);
    q.push_back(1);
    for(i=2;i<=n;i++) {
        while(!q.empty()&&a[q.front()].l>a[i].r) {//如果当前的这天的最高温度比前面的最低温度
                                                  //还要低，那就计算现在的最大天数
            o=q.front();//因为计算时是看pop出去的前一个，所以要记录一下
            q.pop_front();
        }
        if(!q.empty())
            ans=max(ans,i-o);//更新ans
        while(!q.empty()&&a[q.back()].l<=a[i].l)//当前这一天的最低温度比对头得到温度低，对于
                                                //后面的可选择性就要高一些，把对头pop出去
            q.pop_back();
        q.push_back(i);
    }
    pr(ans);
}
```
附上我的[博客链接](https://blog.csdn.net/qq_43890190/article/details/85337381)

---

## 作者：shiroi (赞：0)

单调队列和线段树应该都可做。

考虑若干个 $[l,r]$ 区间，如果这几个区间的温度可能不降，该区间中的 $l$ 的最小值都可以被取到。

那么只要维护一个关于 $l$ 的单调递减队列，保证队头的 $l$ 小等于队尾的 $r$即可解决。

这里用STL的deque实现。

```cpp
#include <bits/stdc++.h>
using namespace std;

inline int read()
{
	int x=0; int f=1; char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1; ch=getchar();}
	while(isdigit(ch)) {x=x*10+ch-'0'; ch=getchar();}
	return x*f;
}

const int MAXN = 2000005;
int l[MAXN],r[MAXN];
std::deque<int> q;
int n,ans,tmp;

int main(int argc, char const *argv[])
{
	int n=read(); q.push_back(1);
	for(int i=1; i<=n; ++i)
		l[i]=read(),r[i]=read();
	for(int i=1; i<=n; ++i)
	{
		while(!q.empty() && l[q.front()]>r[i])
			q.pop_front();
		if(!q.empty()) ans=max(ans,i-q.front()+1);
		tmp=i;
		while(l[i]>l[q.back()] && !q.empty())
			tmp=q.back(),q.pop_back();
		l[tmp]=l[i]; q.push_back(tmp);
	}
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：linyinuo2008 (赞：0)

[原题链接](https://www.luogu.com.cn/problem/P3522)

这题曾经是一年（半）以前我们机房的一道考试附加题。所以复习单调队列的时候翻到了这道题，决定发一发题解。

## 前置知识：单调队列

这道题需要用到单调队列数据结构，其大致意思就是通过一个双端队列来维护一个队列内部单调性或自定义的特殊性质。

单调队列的大致的过程就是每当有一个新元素加进来时，就将前面比它大（小）的元素全部从队列尾弹出，并且时刻保持着区间长度的限制要求。但我要讲的是如何在这道题里面应用单调队列。关于更多单调队列的详情请看[这篇文章](https://www.luogu.com.cn/blog/kaiyuandeboke/dan-diao-dui-lie)。

配一张单调队列思维导图：

![](https://img-blog.csdnimg.cn/20181221124205643.PNG?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MzkwODk4MA==,size_16,color_FFFFFF,t_70)

## 一、题目大意

给你 $n$ （$n \leq 10^6$）段区间，让你求出**最长**的一些**连续**区间（**有顺序**），保证这些区间排好后没有如图所示的情况：

[![78buDJ.png](https://s4.ax1x.com/2022/01/14/78buDJ.png)](https://imgtu.com/i/78buDJ)

其中 $2$ 号在 $1$ 号后面。

## 二、算法思路

转移方程：
$$ f_i=\max(f_j+1,f_i)$$

仅当第i天的温度可以比第j天的温度高的时候才可以转移（判断一下就可以了）。


看完之后，我们显然可以打出一个类似于 $O(n^2)$ 的暴力，但是由于 $n$ 过大，这个算法大概能得 $20pts$ 。
所以我们需要一个更好的思路。

关键字是：`最长`，`连续`，`温度不降`。

所以思路就有了：用单调队列。我们就可以用一个单调下降队列来存每天的最低温度，队头就是最高温度。

那么每天的温度一进去就要和对头比较，拿这一天的最高温度与对头比较，如果大于等于的话说明加上这一天也可以组成一个温度不降的序列，否则就要去掉对头元素，与更低的温度进行比较，直到可以组成一个不降序列。

但是这还不够，因为我们还没有考虑这一天的最低温度。从队尾最低的最低温度开始，找到合适这一天的最低温度的位置，然后入队。

$\text{Tips}$: 由于可以在维护单调队列的时候进行转移，所以直接设定一个 $len$ 表示当前最长不下降温度的天数，于是每次直接与 $len$ 取 $max$ 就可以了。

## 三、代码

$O(n^2)$ 代码（预计 $0-20pts$）

```cpp
#include <iostream>
#include <cstring>
using namespace std;

const int N=1e6+5;
int f[N],l[N],r[N];
int n;

inline int max(int a,int b)
{
	return a>b?a:b;
}

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>l[i]>>r[i];
		f[i]=1;
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<i;j++)
		{
			if(l[j]<=r[i])
			{
				f[i]=max(f[i],f[j]+1);
			}
		}
	}
	cout<<f[n];
}

```

$O(n)$ 代码

```cpp
#include <iostream>
using namespace std;

const int N=1e6+5;

int q[N];//这里q[i]记录在单调队列中对应的天数而不记录具体温度 
int n,l[N],r[N],tail,head;//记录队头队尾

int main()
{
	int ans=1,len=1;
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>l[i]>>r[i];
	q[++tail]=ans=len=1;
	head=tail;
	for(int i=2;i<=n;i++)
	{
		while(head<=tail&&l[q[head]]>r[i]) head++;
		if(head>tail) len=1;
		else len=i-q[head-1];
		while(head<=tail&&l[i]>l[q[tail]]) tail--;
        ans=max(ans,len);
        q[++tail]=i;
	}
	cout<<ans;
	return 0;
}


```

**若有错误，欢迎指出！**

















---

