# [USACO14JAN] Recording the Moolympics S

## 题目描述

Being a fan of all cold-weather sports (especially those involving cows),Farmer John wants to record as much of the upcoming winter Moolympics as possible.


The television schedule for the Moolympics consists of N different programs(1 <= N <= 150), each with a designated starting time and ending time.  FJ has a dual-tuner recorder that can record two programs simultaneously.

Please help him determine the maximum number of programs he can record in total.

农民约翰热衷于所有寒冷天气的运动（尤其是涉及到牛的运动）， 农民约翰想录下尽可能多的电视节目。 moolympics 的节目时间表有 $N$ 个不同的节目 （$1\le N\le 150$），每个节目给定开始时间和结束时间。FJ 有一个双调谐器录音机，可以同时录制两个节目。 请帮助他确定他能录制的节目的最大数量。


## 说明/提示

INPUT DETAILS:


The Moolympics broadcast consists of 6 programs.  The first runs from time 0 to time 3, and so on.


OUTPUT DETAILS:


FJ can record at most 4 programs.  For example, he can record programs 1 and 3 back-to-back on the first tuner, and programs 2 and 4 on the second tuner.


Source: USACO 2014 January Contest, Silver


## 样例 #1

### 输入

```
6
0 3
6 7
3 10
1 5
2 8
1 9```

### 输出

```
4```

# 题解

## 作者：BFSBFSBFSBFS (赞：21)

贪心题.写证明.

题意.给出$n$个节目.每个节目有开始时间$a_i$与结束时间$b_i$.

$a_i > b_j$的2个节目不能放在1组.$(1 <= i,j <= n)$.

求2组.最大化节目数量..

**贪心策略:**

....按照结束时间排序.

....若节目可以放.则必定放.

....尽量放在结束时间长的1组.

**证明:**

....对于其中1组.设它结束时间为$p$.

....若有$p <= a_i$.则该节目可以放在这组上.

....我们希望结束时间越小越好.用来放置更多的节目.

....那么取$p = min(b_i), (p <= a_i, 1 <= i <= n)$.

....若有$b_j$同样满足$(p <= a_j, 1 <= j <= n)$.

....用$b_j$代替$b_i$.

....那么节目总个数不会变.

....因$b_i <= b_j$.$p$可能增大.并非最优.

....所以按结束时间排序的思想正确.

....从2组的角度来看.

....若要使节目数+1.

....$p_1$与$p_2$必然存在1个$p = min(b_i)$.

....所以若$p_1 < p_2$.且$p_2 <= a_i, (1 <= i <= n)$.

....放在$p_1$则留下$p_2, b_i$.

....放在$p_2$则留下$p_1, b_i$.

....因为$p_1 < p_2$.

....放在$p_2$更优.

完毕.

~~还是很假.~~

Diu代码.

```cpp
program P2255;
 var
  a,b:array[0..151] of longint;
  i,j,n,t,t1,s:longint;
 begin
  readln(n);
  for i:=1 to n do
   readln(a[i],b[i]);       //开始与结束时间....
  for i:=1 to n-1 do        //按结束时间排序....
   for j:=i+1 to n do
    if (b[i]>b[j]) or (b[i]=b[j]) and (a[i]>a[j]) then
     begin
      t:=b[i];
      b[i]:=b[j];
      b[j]:=t;
      t:=a[i];
      a[i]:=a[j];
      a[j]:=t;
     end;
  t:=0;
  t1:=0;                    //2组分别的结束时间.
  s:=0;                     //具体节目数量..
  for i:=1 to n do
   if a[i]>=t then          //能放在第1组..
    begin
     inc(s);
     if (t1>=t) and (a[i]>=t1) then t1:=b[i] //第2组能放.且更优..
                               else t:=b[i];
    end
              else if a[i]>=t1 then          //能放在第2组..
    begin
     inc(s);
     t1:=b[i];
    end;
  writeln(s);
 end.
 ```
(ಡωಡ).


---

## 作者：shadowice1984 (赞：21)

蜜汁Ac

按照贪心即可过这道题

我们在每次调用摄像机2号时，鲁棒的交换摄像机1和摄像机2。

因为交换过后优先级较高的永远是最后拍摄的摄像机

我们就可以将它转换为一个只有一台摄像机的问题

而使用另一台摄像机只是开挂了，删除了一个任务。

上代码~


```cpp
#include<stdio.h>
#include<algorithm>
using namespace std;
int n;
struct data
{
    int st;int ed;
    friend bool operator <(struct data a,struct data b)//重载运算符
    {
        if(a.ed==b.ed)return a.st>b.st;
        return a.ed<b.ed;
    }
}mis[150];
int now1=-1;int now2=-1;int res;
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        scanf("%d%d",&mis[i].st,&mis[i].ed);
    }
    sort(mis,mis+n);//按结束时间排序
    for(int i=0;i<n;i++)
    {
        if(now1<=mis[i].st)//第一摄像机优先
        {
            res++;now1=mis[i].ed;
            //printf("now1is%d\n",now1);
        }
        else if(now2<=mis[i].st)
        {
            res++;now2=mis[i].ed;
            //printf("now2is%d\n",now2);
            swap(now1,now2);//调用摄像机2交换优先级
        }
    }
    printf("%d",res);
    return 0;//拜拜程序
}

```

---

## 作者：onepeople666 (赞：15)

[题面传送门](https://www.luogu.com.cn/problem/P2255)

这题是一道**区间贪心**。

一般的区间贪心题是给你 $N$ 个区间，你的任务是尽量让更多的区间两两**不重合**。

对于一般的区间问题，我们要把每个区间的**右端点**从小到大排序，再按排好序的顺序来处理，因为这样可以使每个任务结束时间更早，以便安排下一个区间。

一般的区间贪心题有[自私的放牧](https://www.luogu.com.cn/problem/P2970)和[线段覆盖](https://www.luogu.com.cn/problem/P1803)。（~~其实是一模一样的题目，你交同一份代码都能AC，暗示着双倍经验~~）

接下来看这道题，这道题与一般的区间贪心的**唯一**区别是约翰的录音机非常神奇，可以同时记录两个节目。（~~两个节目的声音互相干扰真不知道约翰怎么录的~~）于是我们可以看做约翰有两个录音机，每一个都可以单独记录节目。我们每次处理节目，要尽量让每个录音机的空闲时间少，再按普通区间贪心的做法来解决。

了解完思路后，我们可以开一个结构体，分别存储每个任务的开始和结束时间，这里 $s$ 表示开始时间，$e$ 表示结束时间。

```cpp
struct cow
{
  int s,e;
};
```

然后我们要写比较函数，按**右端点**也就是**结束时间**排序。


```cpp
int cmp(cow a,cow b)
{
  if(a.e<b.e)
    return 1;
  return 0;
}
```


接下来我们读入 $n$，在 $main$ 函数里定义有 $n$ 个元素的动态结构体数组。（~~不直接开普通数组的原因是我不想看数据范围~~）


```cpp
  cin>>n;
  cow a[n+1];
```


定义完之后，就是读入和排序。


```cpp
for(int i=1; i<=n; i++)
    cin>>a[i].s>>a[i].e;//输入 
  sort(a+1,a+n+1,cmp);//按cmp也就是比较函数排序
```


我们可以定义 $p1$ 和 $p2$ 分别作为录音机1和录音机2处理任务的结束时间，然后按顺序处理，并让每个录音机空闲时间尽量少。
```cpp
int p1=0,p2=0;//开始时两个录音机的处理任务的结束时间都是0 
  for(int i=1; i<=n; i++)
  {
    if(a[i].s>=p1/*假如能处理*/&&p1>p2/*这样写是让录音机空闲时间尽量少*/||(a[i].s>=p1&&a[i].s<p2)/*或者录音机2不能处理*/)
    {
      c++;//答案加一 
      p1=a[i].e;//更新录音机1的结束时间 
    }
    else if(a[i].s>=p2)//如果录音机1没有处理录音机2又能处理就让录音机2处理 
    {
      c++;//答案加一 
      p2=a[i].e;//更新录音机2的结束时间
    }
  }
```
最后输出答案就行啦！~\(≧▽≦)/~

---

## 作者：ChenHacker (赞：7)

[我的独立博客来了](https://ch66.cf/index.php/328)

很水的贪心

1. 先按照结束时间sort，因为越早结束的节目越好

2. 选择接受的收音机是优先选择潜力小的收音机，因为潜力大的收音机留在后面可能更有用

3. return 0；

### 下面是代码

```
#include<bit/stdc++.h>
using namespace std;

int read() {
	register int x=1,ans=0;char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') x*=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){ans=ans*10+ch-48;ch=getchar();}
	return x*ans;
}

const int N=155;
struct dat {
	int a,b;
}d[N];
int cnt;

bool cmp(dat a,dat b) {
	if(a.b==b.b) return a.a>b.a;
	return a.b<b.b;
}

int main() {
	int n=read();
	for(register int i=1;i<=n;i++) {
		d[i].a=read(); d[i].b=read();
	}
	sort(d+1,d+n+1,cmp);
	int cpu0=0,cpu1=0;//不要问我为什么起这个名字，一开始我把这个抽象成了电脑cpu的多核调度，后来发现我的建模是错的......
	for(register int i=1;i<=n;i++) {
		if(cpu0<cpu1) {int t=cpu0; cpu0=cpu1; cpu1=t;}//将潜力小的收音机放在前面
		if(cpu0<=d[i].a) {//调用收音机1
			cnt++; cpu0=d[i].b;
		}
		else if(cpu1<=d[i].a) {//调用收音机2
			cnt++; cpu1=d[i].b;
		}
	}
	printf("%d\n",cnt); 
	return 0;
}
```

---

## 作者：Expecto (赞：7)

贪心大法好！

不知为什么第一次题解Wa了3个点QAQ

先按结束时间排序下，

记录两个记录仪的结束时间，for一遍贪心下

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
pair<int,int> a[166];
int v[166]={0};
int main(){
    int n;
    cin>>n;
    for (int i=0;i<n;i++) cin>>a[i].second>>a[i].first;
    sort(a,a+n);
    int t1=0,t2=0; 
    int ans=0;
    for (int i=0;i<n;i++){
        if (a[i].second<t1) continue;
        ans++;
        if (a[i].second<t2){
                t1=t2;
                t2=a[i].first;
        } else 
            t2=a[i].first;
    }
    cout<<ans<<'\n';
    return 0;
}
```

---

## 作者：Boxxxxxx (赞：4)

[博客链接](https://blog.csdn.net/qq_43804974/article/details/107238594)
**一种dp的解法**
首先对于每一个节目都是看与不看的问题，可以选择对开始时间排序后，按顺序考虑每一个节目，排序后优秀的地方在于，你考虑一个节目的时候，最优解的选取方法里，在你当前节目之前会选取到的节目都是在这个顺序之前会出现，这样就让一个无序的节目强行有序了起来。

先对时间去离散化，由于数据范围是在太小，所以很暴力的可以设计dp的转移方程F[i][j][z]代表当前判断到第i个节目，第一台机子的下一次可录制时间为j，第二台机子的下一次可录制时间为z。

方程有了后我们考虑转移，当前的节目可以选或者不选，如果不选那必然是继承之前的答案，如果选那么就考虑放在第一台机子或者第二台机子。我们思考如果用第一/二台机子去录那么对应机子结束时间是固定的。假设我们第一台机子去录这个节目那么就是f[i][node[i].E][z]，node[i].E是结束时间，我们需要枚举的是第三维度，上一个状态可以转移到当前状态就仅又f[i-1][1-node[i].S][z],node[i].S是开始时间，则你必须第一台机子可以录制下一个的时间在你节目开始之前。那么转移其实就做好了，这一步你可以额外开数组记录一个上一个状态的前缀max就可以了。

```cpp
int yuan[max_ << 1], ynn, N, f[max_][max_][max_];
struct kk {
	int S, E;
}node[max_];
bool cmp(const kk&t1, const kk&t2) {
	if (t1.S == t2.S)return t1.E < t2.E;
	return t1.S < t2.S;
}
int maxv[max_][max_],maxv2[max_][max_];
int ans = 0;
il void update(int id) {
	for (int i = 0; i <= ynn; i++) {
		maxv[i][0] = f[id][i][0]; ans = max(ans, maxv[i][0]);
		maxv2[0][i] = f[id][0][i]; ans = max(ans, maxv2[0][i]);
		for (int j = 1; j <= ynn; j++) {
			maxv[i][j] = max(maxv[i][j - 1], f[id][i][j]); ans = max(ans, maxv[i][j]);
			maxv2[j][i] = max(maxv2[j - 1][i], f[id][j][i]); ans = max(ans, maxv2[j][i]);
		}
	}
}
signed main() {
	N = read();
	for (int i = 1; i <= N; i++) {
		node[i].S = read(); node[i].E = read();
		yuan[++ynn] = node[i].S; yuan[++ynn] = node[i].E;
	}
	sort(yuan + 1, yuan + 1 + ynn);
	ynn = unique(yuan + 1, yuan + 1 + ynn) - yuan - 1;
	for (int i = 1; i <= N; i++) {
		node[i].S = lower_bound(yuan + 1, yuan + 1 + ynn, node[i].S) - yuan;
		node[i].E = lower_bound(yuan + 1, yuan + 1 + ynn, node[i].E) - yuan;
	}
	sort(node + 1, node + 1 + N, cmp);
	memset(f, 128, sizeof(f));
	f[0][0][0] = 0;
	update(0);
	for (int i = 1; i <= N; i++) {
		//不看这个电视
		for (int j = 0; j <= ynn; j++) {
			for (int z = 0; z <= ynn; z++) {
				f[i][j][z] = f[i - 1][j][z];
			}
		}
		//看这个电视
		for (int j = 0; j <= ynn; j++) {
			f[i][node[i].E][j] = max(f[i][node[i].E][j], maxv2[node[i].S][j] + 1);
			f[i][j][node[i].E] = max(f[i][j][node[i].E], maxv[j][node[i].S] + 1);
		}
		update(i);
	}
	cout << ans;
	return 0;
}
```


---

## 作者：A_Đark_Horcrux (赞：3)

这题其实就是[【P1803】 凌乱的yyy/线段覆盖](https://www.luogu.org/problem/P1803) 的加强版。 ~~（暗示双倍经验~~ ）P1803中，一次只能进行一场比赛，而这题中可以同时进行两项拍摄任务，怎么办呢？

在那一题中，我们的贪心策略是：首先将比赛按照结束时间排序，然后从头到尾用一个变量l来记录上一次比赛的结束时间，如果下一场比赛的开始时间在这场比赛结束时间之后，就参加。
那这题也同理。排序，然后拿 __两个变量l1,l2__ 记录两个录制器的录制情况，然后还是从头到尾，先将结束时间跟l1比较，再跟l2比较，此时l1和l2中肯定有一个拍摄的是结束时间迟，于是如果跟l2比较完，l2的值发生了改变，则交换l1,l2，因为 __总是要先判断结束时间较迟的一组__ 才能满足我们 __能放就放__ 的贪心策略。

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
struct A{int x,y;} a[2000000];//存比赛的开始和结束时间
bool cmp(A x,A y){ return x.y<y.y;}//sort用的cmp函数
int n,s,l=-1,t=-1,i;//比赛数量，能录制的比赛的数量，两个记录结束时间的变量，i
int main()
{
	scanf("%d",&n);
	for(i=1;i<=n;i++) scanf("%d %d",&a[i].x,&a[i].y);//输入
	sort(a+1,a+n+1,cmp);//按结束时间排序
	for(i=1;i<=n;i++)
		if(a[i].x>=l) s++,l=a[i].y;//如果比l迟，更新l,s++
		else if(a[i].x>=t) s++,t=a[i].y,swap(l,t);//如果比r迟，更新r，s++，将l和r互相交换	
	printf("%d",s);//输出
	return 0;
}//结束啦awa
```


---

## 作者：VioletIsMyLove (赞：2)

如果只有一台摄像机的话只需要将节目按左端点从大到小排序，如果当前的节目的右端点大于上之前已经左端点，那就不取，否则就取它。但这里有两台摄像机，所以把存两个端点，第一台和第二台的，每次都先把能给第二台摄像机的节目都给第二台，不能给再试着给第一台，当第一台的左端点大于第二台是互换一下就OK了。

Code:

```cpp
#include<cstdio>
#include<algorithm>
#define maxn 155
using namespace std;
int N,ans;
struct ZS{
	int s,t;
	bool operator <(const ZS b)const{return t<b.t;}
}a[maxn];
inline int read(){
	int ret=0;char ch=getchar();
	while (ch<'0'||ch>'9') ch=getchar();
	while (ch>='0'&&ch<='9') ret=ret*10+ch-'0',ch=getchar();
	return ret;
}
int main(){
    N=read();
    for(int i=1;i<=N;i++) a[i].s=read(),a[i].t=read();
    sort(a+1,a+1+N);
    int lst1=0,lst2=0;
    for (int i=1;i<=N;i++)
      if (a[i].s<lst1) continue;else
	  if (a[i].s<lst2) lst1=lst2,lst2=a[i].t,ans++;else lst2=a[i].t,ans++;
    printf("%d\n",ans);
    return 0;
}
```


---

## 作者：曹老师 (赞：1)

## Sol ##

[blog食用](http://www.caolaoshi.men/index.php/archives/usaco14jan-recording.html)

贪心蒟蒻写贪心题解……

贪心的情况其实就是分三种：

**1.该节目在两台录像机未结束时开始，则不选**

**2.该节目只能在一台录像机上，则就在这台录像机上**

**3.其他：选结束时间比较晚的录像机**

## Code ##

```
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

struct Node {
	int l , r;
	bool operator < (const Node &a) const {
		return r < a.r;
	}
};
Node seg[155];
int n , cow1 , cow2 , ans = 0;

int main() {
	scanf("%d",&n);
	for(int i=1; i<=n; i++)
		scanf("%d%d",&seg[i].l,&seg[i].r);
	sort(seg+1 , seg+n+1);
	for(int i=1; i<=n; i++) {
		if(seg[i].l < cow1 && seg[i].l < cow2)
			continue;
		ans++;
		if(seg[i].l >= cow1 && seg[i].l < cow2)
			cow1 = seg[i].r;
		else
			if(seg[i].l < cow1 && seg[i].l >= cow2)
				cow2 = seg[i].r;
		else
			if(cow1 < cow2)
				cow2 = seg[i].r;
			else
				cow1 = seg[i].r;
	}
	printf("%d",ans);
	return 0;
}
```

  [1]: http://usaco.org/index.php?page=viewproblem2&cpid=381
  [2]: https://www.luogu.org/problemnew/show/P2255

---

## 作者：meowla (赞：0)

题解都是用贪心做的..那我就来发一篇动规的题解吧！
这道题的状态定义和动规方程式很难想，如果做过这种双调动规的题会好很多。推荐UVa1347 Tour（可以在洛谷刷UVa的题）。这是一道经典的数学题和算法题。紫书《算法竞赛入门经典(第二版)》上面的页码是P269。

首先我们将所有节目按照起始时间从小到大排序(sort函数)。这样是为了二分查找(STL中的lower_bound函数)。换句话说：在每个dp()中，能够很方便的找到i,j之后，下一个可以拍什么。

这个题我的状态定义的是dp(i,j)，意思是第一台摄像机正在考虑要不要拍摄第i个节目，可以拍可以不拍；第二台摄像机正在考虑要不要拍第j个节目，可以拍可以不拍。为了方便，我们只允许每个dp()的i,j中，只有一个值可以转移。也就是说，要么改变i，要么改变j，不能同时都改变，那样太麻烦了。

综上，每个dp()都要考虑四种情况。分别是：拍i，不拍i，拍j，不拍j。注意：为什么不拍i和不拍j也要处理呢？因为：如果不拍i，那么i的值也要变，变到下一个可以考虑要不要用第一台摄像机拍的节目。注意该节目不是i+1，而是j+1。这个是因为一个规定，见下一个自然段。

我们为了避免重复，“武断地”规定，dp(i,j)中i<j，如果i大于j，就在dp()开头调换它们位置。并且i和j都不能变为<j的数。也就是说。当我们选择拍i时，就算>i且<j(也就是开区间i,j)这部分中有某个节目，满足其起始时间>=i的终止时间，也不拍它。因为j>该节目编号，就意味着这个节目可能被拍过了。当我们选择不拍i时，i应该变成j+1而非i+1。因为i<j，且i与j为整数，那么一定有i+1<=j。那么i+1可能被拍过！强行不允许这种情况。那么为什么这样不会漏解呢？比如dp(2,5)吧。如果我们想用i拍这中间的节目，比如说4吧，完全可以在dp(2,3)时，放弃用i拍2，变成dp(4,3)也就是dp(3,4)，这样就可以拍4了。其他的情况也会因为类似原因不会漏解。

那么动规方程式怎么写呢？比如第一种情况，拍i,对应的值是dp(max(lower_bound(&起始时间表[i+1],&起始时间表[n]+1,结束时间表[i]),j+1),j)。lower_bound那部分的意思是：在起始时间表第i项后面，选择第一个值大于等于i的结束时间的节目。要在lower_bound和j+1中取max，是因为上一段的原因。然后其他的三种情况也用类似的方法写。最后的结果就是在这四种情况的四个值里取max就行了。详细的另外三种的动规方程式见代码。
```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
int actf[151];
int actt[151];
int d[151][151];
struct Node{
	int f,t;
}node[151];
bool cpr(Node a,Node b){
	return a.f<b.f;
}
int dp(int i,int j){
	if(i>j){
		int t;
		t=i;i=j;j=t;
	}
	if(d[i][j]!=-1)
		return d[i][j];
	int temp1,temp2,ans=0;
	temp1=lower_bound(&actf[i]+1,&actf[n]+1,actt[i])-actf;
	temp1=max(temp1,j+1);
	temp2=lower_bound(&actf[j]+1,&actf[n]+1,actt[j])-actf;
	if(temp1!=n+1){
		ans=max(ans,dp(temp1,j)+1);//拍i的动规方程式 

	}	
	if(temp2!=n+1){
		ans=max(ans,dp(i,temp2)+1);//拍j的动规方程式 
	}	


	if(j!=n){
		ans=max(ans,dp(i,j+1));//不拍i的动规方程式 
		ans=max(ans,dp(j+1,j));//不拍j的动规方程式 
	}

	return d[i][j]=ans;
	
}
int main(){
	memset(d,-1,sizeof(d));
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>node[i].f>>node[i].t;
	sort(&node[1],&node[n]+1,cpr);
	for(int i=1;i<=n;i++){
		actf[i]=node[i].f;
		actt[i]=node[i].t;
	}
	if(n==1)
		cout<<1<<endl;
	else
		cout<<dp(1,2)+2<<endl;//+2的原因是第一个和第二个摄像机首个拍摄的节目不会在dp()中计数。
}
```



---

