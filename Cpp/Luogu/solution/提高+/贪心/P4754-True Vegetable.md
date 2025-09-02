# True Vegetable

## 题目描述

小A现在有$N$道题，编号为$1,2,\cdots,N$。每道题的起始毒瘤程度为$0$或$1$。在每回合，小A可以将编号连续的$K$道题的毒瘤程度+1。但小B因为本身比较菜，不是很愿意小A出毒瘤题，所以在$w_i$回合开始时可以向第$x_i$题传播$v_i$点的菜气，使得第$x_i$的毒瘤程度减少$v_i$点（减后可以为负）。这里我们假定菜是有限的，在释放了$v_i$点的菜气后，小B需要至少$r_{v_i}$个回合不能释放菜气。现在小A知道了小B释放菜气的计划，他想知道他至少需要多少个回合可以使得每道题的毒瘤程度至少为$1$。

## 说明/提示

$1 \le N,M \le 5 \times 10^5$

$1 \le K \le N$

$1 \le L \le 100$

$a[i] \in \{0,1\}$

$1 = r_1 < r_2 < \cdots < r_L \le 2 \times L$

$1 \le w_i \le N+L$

$w_i+r_{v_i} \le w_{i+1}$

$1 \le x_i \le N$

$1 \le v_i \le L$

## 样例 #1

### 输入

```
6 1 3 2
0 0 0 0 0 0
1 2
2 1 1```

### 输出

```
3```

## 样例 #2

### 输入

```
6 1 3 2
1 0 0 0 0 0
1 2
2 1 1```

### 输出

```
2```

## 样例 #3

### 输入

```
6 1 6 2
0 0 0 0 0 0
1 2
2 1 1```

### 输出

```
1```

# 题解

## 作者：FlierKing (赞：10)

如果一边被减一边填补，因为情况较多，决策难以判断。

如果直接二分时间，因为某个位置的难度可能一时被减去较多，不满足二分性质。

令被减去的时间为时间点，考虑二分被减的时间点，然后将难度先减去要减的值，因为减难度的冷却时间不小于需要加的数量，被减的数量可以用相同数量的时间填补，所以当一个时间点可以达到目标时，下一个时间点必然也能达到目标。

然后在时间点上计算出需要的时间。二分时间点，在减去生效的操作后，我们可以贪心地从左到右地考虑，当位置 $i$ 小于 $1$ 时，考虑贪心地将 $[i,i+K-1]$ 这个区间加 $1$，可以使需要的回合数尽量小。当确定小B有哪些操作生效时，这样就可以求出满足条件的准确最小时间，若这个时间小于下个时间点，那么check()就是有效的。

时间复杂度 $O(N\ log\ N)$

```cpp
#include <bits/stdc++.h>
#define ll long long
#define MAXN 500205
#define INF 2147483647
using namespace std;
struct sth
{
    int w,t;
    sth(){}
    sth(int n1,int n2){w=n1,t=n2;}
}q[MAXN];
    int n,m,k,l,ans;
    int a[MAXN],w[MAXN],x[MAXN],v[MAXN],r[MAXN],b[MAXN],d[MAXN];
int inline read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int cal(int x)
{
    memcpy(b,a,sizeof(a));
    memset(d,0,sizeof(d));
    for (int i=1;i<=x;i++)
        b[::x[i]]-=v[i];
    int tmp=0,step=0,dis;
    for (int i=1;i<=n;i++)
    {
        if (b[i]+tmp<=1)
        {
            dis=1-b[i]-tmp;
            step+=dis;
            d[i]+=dis;
            if (i+k-1<=n)
                d[i+k-1]-=dis;
        }
        tmp+=d[i];
    }
    return max(w[x],step);
}
int main()
{
    n=read(),m=read(),k=read(),l=read();
    for (int i=1;i<=n;i++)
        a[i]=read();
    for (int i=1;i<=l;i++)
        r[i]=read();
    for (int i=1;i<=m;i++)
        w[i]=read(),x[i]=read(),v[i]=read();
    w[0]=0,w[m+1]=INF;
    int le=0,ri=m,mid;
    while (le<=ri)
    {
        mid=le+ri>>1;
        if (cal(mid)<w[mid+1]) ans=mid,ri=mid-1;
        else le=mid+1;
    }
    printf("%d\n",cal(ans));
    return 0;
}
```

---

## 作者：Trinity (赞：3)

# 题目：P4754 True Vegetable 2018 洛谷7月月赛 T3


------------
首先，我们要模一波出题人[【管理员】FlierKing](https://www.luogu.org/space/show?uid=9433)，他在百忙之中私下为我解答关于此题的问题，让我终于懂了这题的解法。话说回来，出题人的月赛题都很不（du）错（liu），建议大家做一做。因为此题的方法比较单一，而且我太弱，我的代码（很大一部分）参考了出题人的题解，但是在代码和思路方面，我会尽力讲的更加清楚。

------------

## 题目描述
$ \ \ \ \ \ \ \ \ $小A现在有 $N$ 道题 , 编号为 $1$ , $2$ , $...$ , $N$。每道题的起始毒瘤程度为 $0$ 或 $1$。在每回合 ，小 $A$ 可以将编号连续的 $K$ 道题的毒瘤程度 $+1$ , 但小 $B$ 因为本身比较菜，不是很愿意小 $A$ 出毒瘤题，所以在 $w_i$回合开始时可以向第 $x_i$ 题传播 $v_i$ 点的菜气，使得第 $x_i$ 的毒瘤程度减少 $v_i$ 点（减后可以为负）。            
$ \ \ \ \ \ \ \ \ $这里我们假定菜是有限的，在释放了 $v_i$点的菜气后，小B需要至少 $r_{v_i}$ 个回合不能释放菜气。现在小$A$知道了小 $ B$ 释放菜气的计划，他想知道他至少需要多少个回合可以使得每道题的毒瘤程度至少为 $1$ 。 
## 分析
$1$ . 反正看到这个题，我没有直接看出二分来（可能是我太水了），但是排除一切可能的算法，我们要寻找可二分的变量，二分的理由在下面给出，这便是本体的第一个思维难点。  
$2$ . 解决了思想，我们还需要寻找策略得到最小需要的步骤，就想到的贪心，这又是难点。
$3$ . 贪心的函数比较难写（如果你已经被$1$，$2$题搞蒙了)，接下来我会带大家一起模拟。
## 解答
$1$ . 显然，因为小 $B$ 同学十分阴险，他会突然在一个时间点放出很多菜气，导致毒瘤程度瞬降，形成波形，不满足二分的单调性性质；然后，我们又可以从数据范围$w_i+r_{v_i}\leq w_{i+1}$(藏得很刁）中又得知，小 $B$ 的操作的$CD$绝对不会短于小 $A$ 填补小 $B$ 这次操作造成的毒瘤度损失的时间（你挖我 $3$ 点,我就要三回合补回原来的状态 )。总而言之，我们得到：我们可以在下次小$B$操作前，我们能补回来，**也就是说，我们在一段时间内一定可以有盈余**，满足二分单调条件。我们可以把减去的时间当作一个时间点，二分它，计算其成果，满足即答案。**还需要知道一点，由上方证明，当一个时间点可以达到目标时，下一个时间点必然也能达到目标**。（$by\ \ FlierKing$)  
$2$ . 二分完美解决，开始解释贪心，随时间，我们优先选择从小 $B$ 动手的那个题目开始 $K$ 题（如果剩余的未满足题不足 $K$个，就全选），也就是 $[i,i+K-1]$ 的区间加 $1$。我们可以证明，这种情况下，**我们不会过度向任何一题加到超过 $1$ ，又能扫过所有的题目**，非常稳。  
$3$ . 主函数中，我们计算 $mid$ 对应贪心后的步骤，与下一次操作后的损失的时间相比，如果小于，就属于可行方案，缩小二分范围。  
$4$ . 现在来到最难的部分，实现我们的贪心计算。我们计算出这时，损失了难度后呢，我们搞一个暂时量 $y$ 来记录差值 ，下次利用；对于损失的时间和按照策略理论上计算的恢复时间相比，取小值，得到本次的计算答案。  
上代码，跟FlierKing很像，基本按照他的思路码了一遍，见谅，贴上他的[博客](https://www.luogu.org/blog/FlierKing/solution-p4754)。  
```
struct node
{
  int w,x,v;//用的结构体，其实不必要。
}plan[N];
int n,m,k,l,ans,a[N],r[N],pos=1,need,temp[N],want[N],y;
//ans->记录答案，pos->某下标，need->在策略下还需要的时间，temp->需要引用a数组，want->储存变化（不要被变量名迷惑了）。
inline int cal(int x)
{
  memset(want,0,sizeof(want));//多次计算，清零。
  for(int i=0;i<=n;i++)temp[i]=a[i];
  need=y=0,pos=1;//从第一道题开始跑。
  for(int i=1;i<=x;i++)temp[plan[i].x]-=plan[i].v;//先减去损失的点数。
  while(true)
  {
    if(pos>n)break;
    //if(need<plan[x].w)need=plan[x].w;先想要在线比较的，却会更新错。
    if(temp[pos]+y>1)y+=want[pos];//如果补回的时间后超了，那不太好，给后面。
    else
    {
      need+=1-(temp[pos]+y),want[pos]+=1-(temp[pos]+y);//更新，更新。
      if(pos+k-1<=n)want[pos+k-1]-=(1-(temp[pos]+y));//剩余题数不足，不要浪费。
      y+=want[pos];//下波再来。
    }
    pos++;
  }
  return (need>plan[x].w)?need:plan[x].w;//我们需要选优一点的策略。
}
inline void binary_search()
{
  int L=0,R=m,M=(L+R)/2;
  while(L<=R)
  {
    M=(L+R)/2;
    if(cal(M)<plan[M+1].w){ans=M;R=M-1;}//这次恢复时间小于下次损失时间，nice的操作，统计一波。
    else L=M+1;
  }
}
int main()
{
  n=read(),m=read(),k=read(),l=read();
  for(int i=1;i<=n;i++)a[i]=read();
  for(int i=1;i<=l;i++)r[i]=read();
  for(int i=1;i<=m;i++)plan[i]=node{read(),read(),read()};
  plan[0].w=0,plan[m+1].w=inf;//务必加上二分的边界，我没有这两句话，直到再翻题解才了解。
  binary_search();
  printf("%d\n",cal(ans));//答案，最后已经最优（但还是要算一算）。
  return 0;
}
```
## 总结
$1$ . 对于隐藏的比较好的二分题，我们要主动去寻求条件，但还是不要头铁。  
$2$ . 现在，我要郑重表明，可能因为此题的思维难度，在代码分享计划中发现了不少复粘题解，几人代码相同等问题，可能题不简单，题解不是很易懂，但请尽量自己找方法解决问题，不要为刷题而刷。  
希望大家能理解我的题解（对出题人题解的补充），不喜勿喷，谢谢。

---

## 作者：C2H6O (赞：0)

因为看错数据范围A了5天没A掉的蒟蒻来一发题解

思路和两位大佬差不多

首先如果题目令人无从下手，如果不是水平不够那么多半是二分

通过所给条件可以发现，小B释放菜气后到下一次释放之前，小A起码可以把这点损耗的毒瘤度补回来。假如用小B释放菜气的时间点把时间分为一段段间隔，那么一旦某段间隔中有一个时间点满足成立条件，那么之后的间隔中必有至少一个时间点满足成立条件（不一定是之后每时每刻都满足，因为小B可以突然释放一堆菜气，但是小A一定可以一点点补回来）

然后我的思路是这样的，如果某次释放菜气前一刻满足成立条件，那么释放前的这段时间或之前的时间段一定达成过条件，于是可以二分小B释放菜气的时间点，计算其前一刻是否达成条件。

怎么判断是否达成条件呢？或者说面对一个毒瘤度数组，如何判断最少需要几次次区间加法可以满足条件呢？可以简单的贪心，遇到毒瘤度低于1的就加一次以其为左端点的区间加法，计算次数即可。（另外区间加法无需暴力实现，设个记录数组和缓存变量就可了，具体看代码）

我的代码里check是计算某一刻时，比之前满足条件那一刻多出几次加法，如果是负显然不满足，正的话就是此刻时间点减去多出次数即为答案

附上蒟蒻的代码
```
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 1000010//就是这看错范围。。。开两倍为了防止add[i+k]越界
#define L 110
using namespace std;
int n, m, k, l, a[N], r[L], w[N], x[N], v[N];
int le, ri, ans, t;
int check(int p) {
	int b[N], times = w[p] - 1, tmp = 0, add[N];//add[i]记录是右端点为i - 1的区间数
	memcpy(b, a, sizeof(a));
	memset(add, 0, sizeof(add));
	for (int i = 1; i <= p; i++) b[x[i - 1]] -= v[i - 1];//b为小A不操作仅小B释放的结果
	for (int i = 1; i <= n; i++) {
		if (add[i] > 0) tmp -= add[i];//tmp记录i题被几个加法区间包括
		if (b[i] + tmp < 1) {
			add[i + k] = 1 - (b[i] + tmp);
			times -= add[i + k];
			tmp = 1 - b[i];
		}
	}
	return times;
}
int main() {
	scanf("%d%d%d%d", &n, &m, &k, &l);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= l; i++) scanf("%d", &r[i]);
	for (int i = 1; i <= m; i++) scanf("%d%d%d", &w[i], &x[i], &v[i]);
	w[m + 1] = 0x7f7f7f7f;
	le = 1; ri = m + 1;
	while (le <= ri) {
		int mid = le + ri >> 1, time = check(mid);
		if (time >= 0) {
			ri = mid - 1;
			ans = mid;
			t = time;
		}
		else le = mid + 1;
	}
	printf("%d\n", w[ans] - t - 1);
	return 0;
}
```

---

