# [USACO08NOV] Time Management S

## 题目描述

Ever the maturing businessman, Farmer John realizes that he must manage his time effectively. He has N jobs conveniently numbered 1..N (1 <= N <= 1,000) to accomplish (like milking the cows, cleaning the barn, mending the fences, and so on).

To manage his time effectively, he has created a list of the jobs that must be finished. Job i requires a certain amount of time T\_i (1 <= T\_i <= 1,000) to complete and furthermore must be finished by time S\_i (1 <= S\_i <= 1,000,000). Farmer John starts his day at time t=0 and can only work on one job at a time until it is finished.

Even a maturing businessman likes to sleep late; help Farmer John determine the latest he can start working and still finish all the jobs on time.

作为一名忙碌的商人，约翰知道必须高效地安排他的时间。他有 $N(1\le N\le 1000)$ 个工作要做，比如给奶牛挤奶，清洗牛棚，修理栅栏之类的。

为了高效，约翰列出了所有工作的清单。第 $i(1\le i\le N)$ 个工作需要 $T_i(1\le T_i\le 1000)$ 单位的时间来完成，而且必须在 $1\le S_i\le 10^6$ 或之前完成。现在是 $0$ 时刻。约翰做一份工作必须直到做完才能停止。

所有的商人都喜欢睡懒觉。请帮约翰计算他最迟什么时候开始工作，可以让所有工作按时完成。（如果始终无法完成全部任务，输出 $-1$）


## 说明/提示

Farmer John has 4 jobs to do, which take 3, 8, 5, and 1 units of time, respectively, and must be completed by time 5, 14, 20, and 16, respectively.


Farmer John must start the first job at time 2. Then he can do the second, fourth, and third jobs in that order to finish on time.


## 样例 #1

### 输入

```
4 
3 5 
8 14 
5 20 
1 16 
```

### 输出

```
2 
```

# 题解

## 作者：zhz小蒟蒻 (赞：36)

~~其实这道题水的要命，别看它是道黄题~~ ~~（之所以这么讲，其实是因为本蒟蒻只是个小学生，黄题都非常困难）~~，  
如果这句话伤到了你，我表示抱歉(^_^)

好了，废话不多说，我们切入正题，首先，不懂得分治的可以去看[这位大佬的文章](https://www.luogu.org/blog/HOJQVFNA/qian-tan-er-fen-di-bian-jie-wen-ti)，  
这道题是让我们求最晚可以在什么时间起床，这里我们需要加入一个小小的贪心，就是结束时间短的放前面处理，至于为什么，相信你肯定能理解  
然后，我们定义三个变量，$left$ ,$right$ ,$mid$ ,其中，$left$ 表示再找这个区间的起点，而 $right$ 表示这个区间的终点，$mid$ 表示它们中间的值,像这种地方，一般只需背个模板就行了，然后，本题最最重要的地方来了 —— 判断函数，（像本蒟蒻就是在这里卡了很久）  
首先，我们可以这么判断，如果当前所在的时间加上这个任务所需要的时间，没有超过这个任务所必须结束的时间，那么，新的时间则等于原来的时间加上任务所花的时间，否则，证明这个数不合法，本题的思路就是这样，如果你还不明白，请仔细看下面的代码：  
```
#include <iostream>
#include <cstdio>
using namespace std;
struct node
{
	int start;   //起始时间 
	int comes;   //必须在什么时间结束 
};
struct node que[1000001];
int n;
bool check(int cnt)
{
	int x,y,tnt=cnt;
	for(x=1;x<=n;x++)
	{
		if(que[x].start+tnt<=que[x].comes)//如果当前的时间加上任务所需的时间小于等于结束时间，将新的时间等于旧的时间加上任务时间
			tnt=que[x].start+tnt;
		else
			return false;//否则，说明这个数不合法
	}
	return true;
}
int main()
{
	int right=1000000000,left=1,mid=(left+right)/2;
	int i,j,k,ans=0;
	scanf("%d",&n);
	for(i=1;i<=n;i++)
		scanf("%d %d",&que[i].start,&que[i].comes);//读入数据
	for(i=1;i<=n;i++)
		for(j=i+1;j<=n;j++)
			if(que[i].comes>que[j].comes)
				swap(que[i],que[j]);//结束时间短的需放在前面处理
	while(left<=right)//这个只是一个模板，本人使用的是记录答案法
	{
		mid=(left+right+1)/2;//防止死循环
		if(check(mid))
		{
			ans=mid;    //如果这个数合法，那么在它的右边寻找更优解
			left=mid+1;
		}
		else
			right=mid-1;//否则，就在它的左边寻找解
	}
	if(ans!=0)
		cout<<ans;
	else
		cout<<-1;
	return 0;//圆满结束
}
```

---

## 作者：Dr_殇 (赞：22)

#这题我觉得好好想一想的话，其实就只有普及-的难度，用那个叫什么AOE网的思路做，其实超简单！


#就是从最后完成的那件事模拟，如果你完成这件事的结束时间是在那件事应该完成时间之前，那么那件事的开始时间就是这件事的结束时间减去这件事的完成所需时间，也是下件事的结束时间；如果不在应该完成时间之前，那么这件事的开始时间就是这件事应该完成时间减去这件事的完成所需时间，同样也是下一件事的结束时间。直到模拟到第一件事。


##代码如下







```cpp
#include <ctime>
#include <cmath>
#include <cstdio>
#include <string>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>//头文件准备
using namespace std;
struct Work{//定义结构体，方便排序
    int v;
    int f;
}work[1005];
int n,ans;
bool cmp(Work x,Work y){
    return x.f>y.f;
}
int main(){
    scanf ("%d",&n);
    for (int i=1;i<=n;i++){
        scanf ("%d %d",&work[i].v,&work[i].f);
    }
    sort (work+1,work+1+n,cmp);//按照结束时间排序
    ans=work[1].f;//一开始答案是最后一件事的结束时间，然后从最后一件事一直模拟到第一件事
    for (int i=1;i<=n;i++){
        if (ans<=work[i].f)ans-=work[i].v;//如果你完成这件事的结束时间是在那件事应该完成时间之前，那么那件事的开始时间就是这件事的结束时间减去这件事的完成所需时间
        else ans=work[i].f-work[i].v;//如果不在应该完成时间之前，那么这件事的开始时间就是这件事应该完成时间减去这件事的完成所需时间
    }
    if (ans<0)printf ("-1\n");//如果FJ无论如何都完不成，就输“-1”（输出格式里有）
    else printf ("%d\n",ans);//否则输出他能睡多久懒觉（。。。真懒）
    while (1);//反抄袭
    return 0;
}
##珍爱生命，拒绝抄袭！
```

---

## 作者：Benson2005 (赞：14)

这道水题竟然能评上普及？

思路：假设能完成，先考虑结束时间最晚的任务，显然它放在最后面完成越好，因为这样能~~偷懒~~更合理地运用后面的时间，对前面的影响更小。

于是让它在最后完成，这样，就剩下了结束时间倒数第二晚的任务，找到它能最晚完成的时间，搞定它，又剩下了倒数第三晚的，这样一直做下去，若开始时间$fst>-1$，直接输出，否则输出$-1$。

那么问题来了，怎么找到每一段的最晚完成时间呢？显然，第i晚结束的任务的最晚结束时间为该任务的最晚完成时间与第i-1晚结束的任务的最早开始时间的最小值。

于是上代码
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
struct node
{
	int t,l;
}a[1001];
int n,lst;
bool cmp(node x,node y)
{
	return x.l>y.l;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) 
		scanf("%d%d",&a[i].t,&a[i].l);
    sort(a+1,a+n+1,cmp);
	lst=a[1].l;
    for(int i=1;i<=n;i++) 
		lst=min(lst,a[i].l)-a[i].t;
    printf("%d",max(lst,-1));
    return 0;
}
```

---

## 作者：Diamiko (赞：10)

## 核心思想：二分答案

### 1.什么是二分答案

在一个单调不递减或单调不递增的区间里，我们要寻找一个答案使得题目的条件成立，最简单的方法是枚举，时间复杂度是O(n)，可以应付一些数据较小的题目；也可以通过二分的方法来找到这个值，时间复杂度为O(logn)，是时间上比较优秀的算法。

### 2.为什么本题可以二分答案

因为我们要寻找的答案是一个时间点（自然数），当然就是在一个递增的区间里寻找，符合二分答案的特点。

### 3.具体地？

我们把原数组按结束时间升序排序，只要仔细思考就能明白，我们要寻找的答案一定在$0$~$max\{a[i]\_end\}$之间。

那么，排序之后令`l=0,r=a[n]`，每次检验mid是否符合条件即可。

如果符合条件，那么再晚起一会儿说不定也可以，就把r缩过来，令`l=mid+1`，并且记录答案`ans=mid`

反之，说明起得太晚了，就把l缩过来，令`r=mid-1`

最后答案即为ans

#### 怎么检验呢？

二分答案的精髓正在于判断函数

每次二分找到一个x，判断从x开始如果每个工作都能按时完成说明解符合条件

遍历每个事件，只要当前的时间点加上这件事需要的时间，小于等于结束时间那么我们就可以完成这件事。否则就直接pass这个解，因为无法完成所有的工作

### 4.代码实现

（详见注释）

```cpp
#include<iostream>
#include<cmath>
#include<cstdio>
#include<algorithm>
using namespace std;
struct Thing
{
	int Cost;
	int End;
	friend bool operator <(Thing x,Thing y)
	{
		return x.End<y.End;
	}
	//重载小于号以便给结构体排序
}a[1005];
int n;
bool check(int x)
{
	int now=x;
	//now表示当前时间点
	//一开始赋值为x，因为x就是你起床的点
	for(int i=1;i<=n;i++)
	{
		if(now+a[i].Cost<=a[i].End)
		{
			//now表示当前时间，加上这件事的所用时间
			//如果小于等于最晚完成的时间
			//就说明这件事我们完全可以做完
			now+=a[i].Cost;
			//更新当前时间点
		}
		else
		{
			return false;
			//办不到答案就pass掉
		}
	}
	return true;
	//到了这句就说明一直没有被pass，那么所有事情都完成了，就ok
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&a[i].Cost,&a[i].End);
	}
	sort(a+1,a+n+1);
	//排序
	int l=0,r=a[n].End;
	//最早0点起床，最晚不超过最后一件事的结束时间
	int ans=-1;
	//无解输出-1，那我们可以直接赋值为-1，后期如果无解就不用判断了
	while(l<=r)
	{
		int mid=l+r>>1;
		//取中间点
		if(check(mid))
		{
			ans=mid,l=mid+1;
			//记录答案
		}
		else
		{
			r=mid-1;
		}
	}
	printf("%d\n",ans);
	//ans即为最优解
	return 0;
}
```
写题解不易，希望过审，大家有不懂的可以私信我，也可以at我，我会尽一臂之力

---

## 作者：Mingoal (赞：9)

我的做法比较奇怪，不过代码确实短

f[i]=0,1表示在这个时间做或者不做

这个数组有一个性质——

f[1]+f[2]+...+f[i]=在i时间之前要做多少时间的工作

```pascal
var f:array[-1..1000000] of longint;
    n,i,x,y:longint;
begin
read(n);
for i:=1 to n do
    begin
    read(x,y);
    f[y]:=f[y]+x;//见上面的性质，这相当于一个标记
    end;
for i:=1000000 downto 0 do
    if f[i]>1 then f[i-1]:=f[i-1]+f[i]-1;
//因为一个时间不能干多个事情，所以把标记前推。
//其实是把f[i]变成1，剩下的给f[i-1]，但因为f[i]和答案没有直接关系，所以把f[i]:=1;删掉了
for i:=0 to 1000000 do
    if f[i]>0 then break;
writeln(i-1);
end.
```

---

## 作者：y2823774827y (赞：9)

 简单的贪心思路：
1. 对每件事最迟结束时间从大到小排序，该顺序为完成最后一件事到最早一件事
1. 定义now为所有事件结束时间
1. 每件事最迟开始时间，与前一件事最迟结束时间比较，如果大于，说明此解不成立，为了维护时间，now赋成该值
1. 循环完后，如果now<0，与实际不符，说明无解输出-1，否则输出now（此时为最优解，可通过简单推算证明出）

代码如下
```cpp
# include<cstdio>
# include<algorithm>
using namespace std;
# define max_n 1001
  struct node{
  int pay,late;
}cun[max_n];
bool sort1(node t,node tt){return t.late>tt.late;}
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%d%d",&cun[i].pay,&cun[i].late);
	sort(cun+1,cun+1+n,sort1);//按结束时间从早到晚排序 ,由于求最迟时间,这样排序是最优解的顺序（贪心） 
	int now=cun[1].late;
	for(int i=1;i<=n;++i){
		now=now-cun[i].pay;//结束时间 
		if(i==n){
			if(now<0) printf("-1");else printf("%d",now);
			return 0;//循环到n退出 
		}
		if(now>cun[i+1].late) now=cun[i+1].late;//结束时间大于前一个事件,说明此方式无解需推前时间 
	}
}
```

---

## 作者：Rbu_nas (赞：7)

本题其实思路很好想，也有很多实现方式。在这里详细介绍一下好写不容易挂的二分答案。

---

关于二分：

**最常见的**模板大概就长这样了

```cpp
//此处l、r需要根据题目要求定义.
while(l <= r)
{
    mid=(l+r)>>1;
    if(check(mid))
        ans=mid, l=mid+1;
    else
        r=mid-1;
}
```

顾名思义，二分答案枚举的是答案，它的精髓就在于`check`函数了，二分答案又适用于哪些题目呢？

- 最大值最小、最小值最大

- 满足条件的第k个数

---

那么二分答案怎么想，怎么写呢？以本题为例，要求最迟的工作时间x，我们就可以**枚举时间x判断这个时间能否完成任务**，然后不断往后推（因为求最迟的），因而`l=mid+1`，也就是说对于时间x，必须满足**可以完成工作**的条件

很容易想到对它们的截止时间排序，然后依次判断，如果这时的x满足于$x+a_i.t <= a_i.end$ 那么x加上这次完成所需的时间对下一个$a_i$再次判断，`check`函数的思路也就出来了：

```cpp
inline bool check(int x)
{
    for(register int i=0; i<n; ++i)
    {
        if(x+a[i].t <= a[i].end) x+=a[i].t; 
        /*
        	如果可以满足要求就加上这次工作的时间
            看x下一次是否能满足期限内下个任务要求
        */
        else return false;
    }
    return true;
}
```

---

那么结合刚刚所说的右逼答案此题就很快能写出来了

```cpp
# include <cstdio>
# include <cstdlib>
# include <iostream>
# include <no-copy.h>
# include <algorithm>
using namespace std;

inline void gi(int &x)
{
    x=0;int t=1,k=getchar();
    for(;k<'0'||k>'9';k=getchar())if(k=='-')t=-1;
    for(;k>='0'&&k<='9';k=getchar())x=(x<<1)+(x<<3)+(k^48);x*=t;
}

const int N=1000+5;
int n;

struct NODE
{
    int t, end; //t是工作所需的时间，end是截止时间
    bool operator < (const NODE &other) const
    {
        return end < other.end;
    }
} a[N];

inline bool check(int x)
{
    for(register int i=0; i<n; ++i)
    {
        if(x+a[i].t <= a[i].end) x+=a[i].t;
        else return false;
    }
    return true;
}

int main(void)
{
    gi(n);
    for(int i=0; i<n; ++i) gi(a[i].t), gi(a[i].end);
    sort(a, a+n); //对截止时间排序，越早的自然越先做
    int l=0, r=a[n-1].end+5, mid, ans=-1;
    /*
    r根据题目要求取一个不可取的值，这里取的是最晚的截止日期，因为显然不可能此时完成工作
    如果无解输出-1，所以直接把ans设为-1，如果没有时间x满足要求就直接输出-1了
    */
    while(l <= r)
    {
        mid=(l+r)>>1;
        if(check(mid)) 
        //每次枚举时间x看看是否能从第x分钟开始做完成任务
            ans=mid, l=mid+1;
        else
            r=mid-1;
    }
    printf("%d", ans);
    return 0;
}

```

本题的`check`思路很简单，大家也可以做做[木材加工](https://www.luogu.org/problemnew/show/P2440)、[砍树](https://www.luogu.org/problemnew/show/P1873)练练手

如果有帮助的话请扣个赞QwQ，有问题欢迎在评论指出或提问

---

## 作者：Varuxn (赞：6)

楼上大佬们用**二分**、**贪心**~~（您们说啥呢？？？ 听不懂）~~

只可惜本蒟蒻孤陋寡闻，不会，我太难了！！

怎莫办呢

笨人自有笨的办法

请看如下代码：


-------无敌分割线-----

```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<algorithm>
using namespace std;
inline int read()   //比你跑得快[手动滑稽]
{
	int f=1,x=0;
	char ch=getchar();
	while(ch>'9'||ch<'0')
	{
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
struct abc
{
	int t,s;
}a[1005];
int n;
bool comp(abc x,abc y)//定义sort排序规则
{
	return x.s>y.s;
}
int main()
{
	n=read();
	for(int i=1;i<=n;i++)
	{
		a[i].t=read();
		a[i].s=read();
	}//读入
	sort(a+1,a+n+1,comp);//按照其截止时间从晚到早排序
	int ans=a[1].s;//从最晚的截止时间开始
	for(int i=1;i<n;i++)
		ans=min(ans-a[i].t,a[i+1].s);//核心
        /*
           比较较晚的任务的开始时间 和 较早任务的截止时间
           较早任务的结束时间是以上二者中最小的
        */
	ans-=a[n].t;
	if(ans<0) cout<<"-1";//特判
	else
	cout<<ans;
	return 0;
}
/*下面是自己编的几个样例（仅供参考）
一：输入
    2 9 16 3 5
   输出
    2
二：输入
    2 9 16 5 9
   输出
    2
三：输入
    2 9 16 5 7
   输出
    2
*/
```
希望管理大大给过

---

## 作者：Youngsc (赞：5)

[Youngsc](http://youngscc.github.io/)

### 个人表示这种题真是~~乱搞~~。

定义now为最晚开始工作的时间。

我们可以先将所有的任务按照结束时间早晚进行排序，然后将最晚结束的那个任务的结束时间作为now，通过这个now来一步步推知前边的时间并且更新now。

如果说我当前任务的结束时间要晚于我这个now，说明当前任务就提前开始，不然后边的任务无法按计划完成，应该提到多前呢？就是now减去它所耗费的时间，也就是说这个任务最晚在now结束，而不是s，那么我的now就被更新为$now-t$.

换言之，如果当前任务的结束时间早于now的话，就说明这个任务只要在它的最晚完成时间完成就可以了，也就是将now更新为他的最晚开始时间。

一切完成后，now就表示第一个任务最晚开始时间，如果$now>=0$直接输出now表示可行，否则表示输出-1.

（这道题方法真的多）

## 代码在这里

```cpp
# include <algorithm>
# include <iostream>
# include <cstring>
# include <cstdio>
# include <queue>
# include <cmath>
# define R register
# define LL long long

using namespace std;

int n,now;
struct zx{int t,s;}a[1010];

inline void in(R int &a){
    R char c = getchar();R int x=0,f=1;
    while(!isdigit(c)){if(c == '-') f=-1; c=getchar();}
    while(isdigit(c)) x = (x<<1)+(x<<3)+c-'0',c = getchar();
    a = x*f;
}

inline void maxx(R int &a,const int b){a>b? 0:a=b;}
inline void minn(R int &a,const int b){a<b? 0:a=b;}
inline bool cmp(zx a,zx b){return a.s>b.s;}

inline int yg(){
    // freopen("maze1.in","r",stdin);
    // freopen("maze1.out","w",stdout);
    in(n);
    for(R int i=1; i<=n; ++i)
        in(a[i].t),in(a[i].s);
    sort(a+1,a+n+1,cmp);
    now = a[1].s;//将now初始化为最晚结束时间
    for(R int i=1; i<=n; ++i)
    {
        minn(now,a[i].s);//判断我当前最晚结束时间，取较小值
        now -= a[i].t;//更新
    }
    maxx(now,-1);//如果负数则输出-1
    printf("%d",now);
    return 0;
}

int youngsc = yg();
int main(){;}
```
（减少代码复制，共创美好洛谷）


---

## 作者：不存在之人 (赞：3)

看懂题之后从最后结束的时间往前推即可。如果最后的得到的开始时间小于$0$就输出$-1$。

代码：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
struct use
{
	int st,en;
}a[1000010];
int n,ans(99999999);
bool cmp(use a,use b)
{
	return a.en>b.en;
}
int main()
{
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
	{
		scanf("%d%d",&a[i].st,&a[i].en);
	}
    sort(a+1,a+n+1,cmp);
    for (int i=1;i<=n;i++)
		ans=min(ans,a[i].en)-a[i].st;
    if (ans<0) ans=-1;
    printf("%d\n",ans); 
}
```
这可能是你看到的最简洁的代码

---

## 作者：Juvenile (赞：1)

#### 这是一道明显的**二分ans**题

------------

### 关于二分：
有这么几个注意点
>$\color{red}1.$二分基于有序数组，所以切记不要忘记sort

>$\color{red}2.$分清题目要求的是$\color{gold}max$的最小值,还是$\color{gold}min$的最大值

>$\color{red}3.$边界  **l,r** 的取值问题


------------
1. 考虑边界：l=0，r=时间总长

2. $\color{pink}check$函数的实现

将初始时间定为休息时间，每次加上所需时间( a[ i ].t )，再和时间节点相比较，若超出时间，就return 0(这样掐掉后从某种程度上来说会时间更少)
```cpp
bool check(int x)
{
	int time=x;
	for(int i=1;i<=n;i++)
	{
		if(time+a[i].t>a[i].s) return 0;
		time+=a[i].t;
	}
	return 1;
}
```

3.考虑贪心，$\color{pink}sort$按a [ i ].s的优先级排序


------------
### Solution:


```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 1009
struct Point{
	int t,s;
}a[N];
int n;
bool cmp(Point x,Point y){return x.s<y.s;}
bool check(int x)
{
	int time=x;
	for(int i=1;i<=n;i++)
	{
		if(time+a[i].t>a[i].s) return 0;
		time+=a[i].t;
	}
	return 1;
}
int main()
{
	scanf("%d",&n);
	int sum=0;
	for(int i=1;i<=n;i++)
		scanf("%d%d",&a[i].t,&a[i].s),sum+=a[i].t;
	sort(a+1,a+n+1,cmp);
	int ans=-1,l=0,r=sum;//ans初始值赋为-1则免去了最后判断的操作
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(check(mid)) ans=mid,l=mid+1;
		else r=mid-1;
	}
	printf("%d\n",ans);
	return 0;	
}
```


------------
### 复杂度O(nlogn)


------------
看写这么详细，审核给过呗

---

## 作者：installb (赞：1)

首先 将所有工作按s从小到大排序  
**reason:**  
如果一个较早需要完成的工作还没有完成 就先去完成一个需要较晚完成的工作 一定会导致完成前一个工作的时间比先完成这个工作后延 即需求时间减去完成该工作时间的值变小  
所以一定是按照s从小到大的顺序完成工作  
而文章中的**最迟什么时候开始工作**其实可以直接转化为完成每个工作时 目前的s减去目前已用时间的 最小值  
若最小值为负 就代表不能完成 输出-1  
## code:
```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <iostream>
#define LL long long
using namespace std;
const int INF = 0x3f3f3f3f;

struct node{
	int t,s;
	bool operator <(const node &nd)const{
		return s < nd.s; // 重载运算符 以s从小到大排序
	}
}a[100005];

int n,minn = INF,now_t = 0,now_s = 0;
// now_t now_s 分别表示目前工作已用时间和目前的需求完成时间

int main(){
	cin >> n;
	for(register int i = 1;i <= n;i ++){
		cin >> a[i].t >> a[i].s; // 读入
	}
	sort(a + 1,a + 1 + n); // 排序
	for(register int i = 1;i <= n;i ++){
		now_t += a[i].t; now_s = a[i].s;
        // now_t加上完成这个工作需要的时间
        // now_s直接改为目前工作的s
		minn = min(minn,now_s - now_t); 
	}
	if(minn < 0) minn = -1; // 答案为负数输出-1 没加这句WA了一次...
	printf("%d\n",minn);
	return 0;
}
```

---

## 作者：AcerMo (赞：1)

额我乱搞的并查集
先按结束时间从大到小排序
然后从结束时间向前数n个位置，n是持续时间，然后将这个区间内所有的点得父节点设成结束时间-结束时间，表示再有需要从这个区间内结束的要向前到父节点，看代码更好理解
```cpp
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int M=100500;
int n;
int fa[1005000];
int find(int x)
{
	if (fa[x]!=x) return fa[x]=find(fa[x]);
	return x; 
}
inline int read()
{
	int x=0;char ch=getchar();
	while (ch<'0'||ch>'9') ch=getchar();
	while (ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return x;
}
struct work
{
	int st,ed;
}emm[M];
bool cmp(work a,work b)
{
	return a.ed>b.ed;
}
void constt()
{
	for (int i=1;i<=emm[1].ed+1;i++) fa[i]=i;
	return ;
}
int main()
{
	n=read();
	for (int i=1;i<=n;i++) 
		emm[i].st=read(),emm[i].ed=read();
	sort(emm+1,emm+n+1,cmp);constt();
	for (int i=1;i<=n;i++)
	{
		int r1=find(emm[i].ed);
		int r2=r1-emm[i].st;
		if (r2<0){puts("-1");return 0;}
		for (int k=r2+1;k<=r1;k++) fa[k]=r2;
	}
	cout<<find(emm[n].ed);
	return 0;
}
```

---

## 作者：dapanshe (赞：0)

## 这题根据需要完成的末尾时间进行排序，然后依次看前面对最开始的shijian约束并实时更新，时间复杂度排序O(nlgn),遍历O(n)
```python
n = int(input())
a = []
for i in range(n):
    a.append(list(map(int, input().split())))
a.sort(key= lambda x: x[1])
cur = a[0][1]-a[0][0]
s = 0
for i in range(n):
    s += a[i][0]
    cur = min(cur, a[i][1]-s)
    if cur <= -1:
        cur = -1
        break
print(cur)
```


---

## 作者：Chicago_01 (赞：0)

## 题面
作为一名忙碌的商人，约翰知道必须高效地安排他的时间.他有N工作要 做，比如给奶牛挤奶，清洗牛棚，修理栅栏之类的.

为了高效，列出了所有工作的清单.第i分工作需要T_i单位的时间来完成，而 且必须在S_i或之前完成.现在是0时刻.约翰做一份工作必须直到做完才能停 止.

所有的商人都喜欢睡懒觉.请帮约翰计算他最迟什么时候开始工作，可以让所有工作按时完成.（如果无法完成全部任务，输出-1）

## 题意

有一个人有N项工作，给N组数据，每组数据有Ti和Si，分别表示第i组工作需要花费的时间和最晚完成的时间。

初始时间为0，要求算出最晚可以什么时间开始工作。

## 题解

### 50分操作 (有BUG 不严谨证明)
由题意可以知道这道题可以尝试以下模拟操作。

1. 排序每一项最晚完成的时间。

2. 枚举，如果前i项任务完成时间超过第i项任务花费的时间，就非法，输出-1。

3. 统计出每一项任务  最晚完成时间 - 花费时间的值。

4. 排序输出最小的统计值。 （不完全归纳法得出3、4操作，不严谨证明）

```
#include<bits/stdc++.h>
using namespace std;

int n = 0,tong[1010];

struct edge{
    int t,s;
    bool operator < (const edge &qxq)
    {
        return s < qxq.s;
    }
}num[1010];

int main(int argc, char const *argv[])
{
    cin >> n;

    for(int i = 1;i <= n;i++)
    {
        cin >> num[i].t >> num[i].s;
        if(num[i].t > num[i].s)
        {
            cout << -1;
            return 0;
        }
        tong[i] = num[i].s - num[i].t;
    }

    sort(num+1,num+n+1);
    sort(tong+1,tong+n+1);

    long long sum = 0;
    for(int i = 1;i <= n;i++)
    {
        sum += num[i].t;
        if(sum > num[i].s)
        {
            cout << -1;
            return 0;
        }
    }

    cout << tong[1];
    
    return 0;
}
```

### 满分做法 AC100

建立在50分的操作上进行严谨的贪心证明。

1. 排序每一项最晚完成的时间。

2. 得出最晚完成的时间，并用一个中间变量存储。

3. 枚举，用中间变量减去每一项所要花费的时间。

4. 对结果进行判断，如果中间变量小于0，非法，输出-1；否则中间变量剩余的时间就是答案，也就是商人最晚起床时间。

```
#include<bits/stdc++.h>
using namespace std;

int n = 0;

struct edge{
    int t,s;
    bool operator < (const edge &qxq)
    {
        return s > qxq.s;
    }
}num[1010];

int main(int argc, char const *argv[])
{
    cin >> n;

    for(int i = 1;i <= n;i++)
    {
        cin >> num[i].t >> num[i].s;
    }

    sort(num+1,num+n+1);

    int ans = num[1].s;
    for(int i = 1;i <= n;i++)
    {
        if(ans <= num[i].s) ans -= num[i].t;
        else ans = num[i].s - num[i].t;
    }

    if(ans < 0) cout << "-1";

    else cout << ans;
    
    return 0;
}
```


---

## 作者：RainShalder (赞：0)

-看到这道题题解里各位dalao都用二分做这道题，萌新瑟瑟发抖\_(:3」∠)\_

-下面说一下个人的（非二分）思路：

------------------第一部分：题面----------------

-输入输出格式中要求特判-1....没翻译....

------------------第二部分：数据----------------

-这题第八组数据有坑，在于有一项工作的Ti>Si，导致其最晚的开始时间小于0，

-所以直接跳过了for循环，ans的值没有改变。

-（具体我在程序中有写）

------------------第三部分：解题思路-----------

-拿到题，先看一下数据范围：N<=10^3,Si<=10^6,Ti<=10^3

-看起来数据范围比较小，那么我们完全可以尝试 通过枚举来解决此题

-具体来说，我们从0开始枚举，

-枚举到哪里呢？

-如果说我们开始工作的时间比每项工作的 最晚开始时间 的最小值还要大，那么一定不行。

-比如样例：最晚开始时间是5-3=2，我们从3开始工作，想必是完不成的。

-所以说，我们枚举到最晚开始时间的最小值为止。

-这样，我们就成功的缩小了枚举的范围。

-随后，每枚举一次就模拟一次工作，

-如果说枚举到一个时间无法完成，就直接break掉，

-答案即为这个时间-1。

-最后加一步特判：如果ans==0，就输出-1。.

-实测用时0ms，说明枚举是可行的。

-枚举的好处在于思考起来比较简单，不过数据再大一点就有可能TLE。

-下面放出AC代码：

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int n,nowtime,flag,minstart,ans;
struct Job
{
        int t,s,start;   //t,s题目里有解释，start存储此项工作的最晚的开始时间（即s-t）
}job[1001];
bool cmp1(Job a,Job b)
{
        return a.start<b.start;
}
bool cmp2(Job a,Job b)
{
        return a.s<b.s;
}
int main()
{
        cin>>n;
        for(int i=1;i<=n;i++)
                cin>>job[i].t>>job[i].s;
        for(int i=1;i<=n;i++)
                job[i].start=job[i].s-job[i].t;  //计算最晚开始时间
        sort(job+1,job+n+1,cmp1);  
        minstart=job[1].start;   //这两句首先按照最晚开始时间进行排序，然后取得最晚开始时间的最小值。
                                       //这里同样也可以遍历不断调用min函数得到，不过要慢一点。
        sort(job+1,job+n+1,cmp2);  //随后按照s排序，时间紧迫的先做
        for(int i=0;i<=minstart+1;i++)   //枚举开始时间
        {
                nowtime=i;        
                ans=i-1;        //首先记录下这个时间，以及目前的答案。-1是因为如果之后发现这个i无法满足，那么最终答案就是i-1.
                for(int j=1;j<=n;j++)
                {
                        if(nowtime+job[j].t<=job[j].s)
                                nowtime+=job[j].t;     //枚举每项工作，每次加上这项工作的t
                        else                //如果发现第j项工作不行
                        {
                                flag=1;      //将flag设为1，然后break出循环。设置flag变量是为了外层循环的判断。
                                break;
                        }
                }
                if(flag==1) 
                        break;      //如果flag是1，就break出i循环，随后输出答案
        }
        if(ans!=0)
            cout<<ans;
        else
                cout<<"-1";       //特判
        return 0;
}
```

---

## 作者：dolphin (赞：0)

随便搞一搞就水过了……这里说一下我的做法

对s从小到大排序

然后我们设从时间c[1].s-c[1].t开始工作，累加工作时间

如果某一次时间大于该工作的截止时刻，那就说明我们开始工作的时间晚了

所以t=c[i].s，顺便把开始工作的时间减去多出来的部分

最后看开始工作的时间是否为负即可

当然用别的办法加上一些优化，，比如二分什么的会更快一些……

'
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=1010;
int n;
struct fx{
    int s,t;
}c[N];
bool cmp(fx a,fx b){
    return a.s<b.s;
}
int main(){
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
        scanf("%d %d",&c[i].t,&c[i].s);
    sort(c+1,c+n+1,cmp);
    if (c[1].s-c[1].t<0){
        printf("-1");
        return 0;
    }
    int t=c[1].s,ts=0;
    for (int i=2;i<=n;i++){
        t+=c[i].t;
        if (t>c[i].s){
            ts+=t-c[i].s;
            t=c[i].s;
        }
    }
    int ans=c[1].s-c[1].t-ts;
    if (ans<0) ans=-1;
    printf("%d",ans);
    return 0;
}
'
```

---

## 作者：海纳百川 (赞：0)

首先有一个明显的贪心，要按照最后截止时间来排序

然后二分最晚开始时间，从前往后判断是否能完成任务

注意要特判-1

代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#define ll long long 
using namespace std;
ll n,l,r,mid,i,ans,f;
struct node
{
    ll s,t;
}a[100000];
bool cmp(node o,node p)
{
    return o.s<p.s;
}
bool pan(ll x)
{
    for(i=1;i<=n;i++)
    {
        if(x+a[i].t<=a[i].s) 
        x+=a[i].t;
        else return false;
    }
    f=1;
    return true;
}
int main()
{
    cin>>n;
    for(i=1;i<=n;i++)
    {
        scanf("%lld %lld",&a[i].t,&a[i].s);
    }
    sort (a+1,a+1+n,cmp);
    l=0;
    r=1000000000;
    while (l<=r)
    {
        mid=(l+r)>>1;
        if (pan(mid))
        {
            ans=mid;
            l=mid+1;
        }
        else r=mid-1;
    }
    if (!f)cout<<-1;
    else 
    cout<<ans;
    return 0;
}
```

---

## 作者：RiverHamster (赞：0)

##其实还有一种乱搞快排方法，先快排再直接顺序模拟

cmp比较两个结构体时，返回把a放在前面好还是b放在前面好

放个核心比较代码：

```cpp
inline bool TaskPriorit(Task a,Task b){
    return min(a.s-a.t,b.s-a.t-b.t)>min(b.s-b.t,a.s-a.t-b.t);
    //s表示最迟完成时间，t表示任务需要的时间。
}
```
这里不考虑其他元素，只考虑a，b的先后。所以其实两个min()算出的值没有任何实际的意义，只是两种方法的**相对优劣程度**。

PS:相对优劣程度表示仅考虑a，b时能休息的时间。

前一个min表示把a放在前面的优劣程度，后一个表示把b放在前面的优劣程度。

前一个min中`a.s-a.t`表示只做放在前面的任务可以休息的时间，`b.s-a.t-b.t`表示把两个任务都做完可以休息的时间，后一个min以此类推。两种方法如果a放前能多休息，那就把a放前，否则就把b放前。

###所以这题方法：

###1.按照上述方法快排一遍

###2.模拟扫一遍

模拟的代码：

```cpp
for(int i=1;i<=n;i++){
        now+=a[i].t;     //先不间断的把所有事做完并记录时间
        if(now>a[i].s){  //不能完成
            puts("-1");
            return 0;
        }
        ans=min(ans,a[i].s-now); //能睡的时间就是所有差的最小值
    }
```

---

