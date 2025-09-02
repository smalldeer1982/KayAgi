# Queue

## 题目描述

Little girl Susie went shopping with her mom and she wondered how to improve service quality.

There are $ n $ people in the queue. For each person we know time $ t_{i} $ needed to serve him. A person will be disappointed if the time he waits is more than the time needed to serve him. The time a person waits is the total time when all the people who stand in the queue in front of him are served. Susie thought that if we swap some people in the queue, then we can decrease the number of people who are disappointed.

Help Susie find out what is the maximum number of not disappointed people can be achieved by swapping people in the queue.

## 说明/提示

Value $ 4 $ is achieved at such an arrangement, for example: $ 1,2,3,5,15 $ . Thus, you can make everything feel not disappointed except for the person with time 5.

## 样例 #1

### 输入

```
5
15 2 1 5 3
```

### 输出

```
4
```

# 题解

## 作者：Michael123456 (赞：9)

题目大意：

有n个人排队买东西，每个人都有一个购买时间ti,如果这个人等待的时间超过他的购买时间他就会失望，求怎样排队使不失望的人数最多。

思路：

从小到大排一下序，记录总时间_time,只要_time在这个人的等待时间内就加他，否则把它放到最后去（本蒟蒻看了楼下的算法，相当于我们把他从队列中踢出），很好实现，看代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=1e5+10;

int n,a[maxn];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	sort(a+1,a+1+n);
	int _time=0,ans=0;
	for(int i=1;i<=n;i++)if(_time<=a[i])ans++,_time+=a[i];//只有有用的要把_time加进去，没用的踢掉
	printf("%d",ans);
	return 0;
}

```
最后希望本蒟蒻的题目大意能帮助更多的蒟蒻（逃）

管理员过了吧

---

## 作者：宁_缺 (赞：9)

# ~~作为C++STL的忠实爱好者~~不发一篇STL的题解于我心何忍呢？
看到楼下有不少sort()的，我决定**另辟蹊径**,发一篇优先队列的。~~其实我最初想到的就是优先队列~~
### 对于不知道优先对列的蒟蒻（~~和我一样~~），稍微介绍一下。拿
```cpp
priority_queue<int,vector<int>,greater<int> >que;
```
### 举例子，<>里第一个int是队列的类型，vector<int>是队列的存储容器， greater是从小到大排序（若从大到小就把greater换成less）
代码如下
```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
LL n,read(),sum,ans;//本来n,read(),ans都可以用int的，不过这里就偷个懒了
priority_queue<LL,vector<LL>,greater<LL> >q;
int main()
{
	scanf("%lld",&n);
	for(LL i=1;i<=n;i++)q.push(read());//push()弹入
	for(LL i=1;i<=n;i++,q.pop())//pop()是将队首（最小值）弹出
		if(sum<=q.top())ans++,sum+=q.top();
      //sum是前面人数等待时间的总和，也就是要等待的时间
      //因为选时间短的肯定比时间长的更优（sum更小），所以能选小的就选小的（就是贪心思想）
	printf("%lld",ans);
	return 0;
}
//read()就不用介绍了吧，自己打一个有返回的快读即可
```
## ~~期望第一篇题解能通过~~

---

## 作者：封禁用户 (赞：5)

这D比C还简单。。。

直接贪心：如果要让尽可能多的人不失望，就要让用时少的排在前面（小学内容？）这样我们就可以贪心，找出最小的。

```
#include <bits/stdc++.h>
using namespace std;
int n;
int t[100005];
int ans;
int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> t[i];
    sort(t + 1, t + n + 1);
    int tim = 0;
    for(int i = 1; i <= n; i++) {
        if(t[i] >= tim)
            ans++;
        tim += t[i];
    }
    cout << ans;
    return 0;
}
```
---

#### BUT

这样只(ju)是(ran)过了前两个点！！！

随便一组数据就可以卡掉这个程序

还有要注意的是，只有当这个人不失望，才让他作为下一个，不然已经失望了，为何不让他排在后面呢？

最后献上AC代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
int t[100005];
int ans;
int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> t[i];
    sort(t + 1, t + n + 1);
    int tim = 0;
    for(int i = 1; i <= n; i++) {
        if(t[i] >= tim)
            ans++, tim += t[i];
    }
    cout << ans;
    return 0;
}
```

其实我看谷歌翻译做的时候，吧$10 ^ 5$看成了$1050$……（光速逃

---

## 作者：wzm2007 (赞：3)

    排一下序，记录总时间t,只要t在这个人的等待时间内就加他，否则把它放到最后去
    代码：

------------

    #include<bits/stdc++.h>  //万能头文件
    using namespace std;
    int a[100010];
    int main()
    {
        int n,t=0,ans=0;
        cin>>n;
        for(int i=0;i<n;i++)scanf("%d",&a[i]);
        sort(a,a+n);  //排序
        for(int i=0;i<n;i++)
            if(t<=a[i])ans++,t+=a[i];  //只有有用的要把t加进去，没用的踢了
        cout<<ans;
        return 0;
    }

---

## 作者：封禁用户 (赞：2)

真的很简单啊（逃

做题必须好好读题：

>有一个有$n$个人的队伍，其中第$i$个人需要$t_i$分钟来服务，期间后面的人就要等着。如果一个人等待的时间大于了他被服务的时间，他就会失望。你的任务是重排队伍，使失望的人尽量的少，并只需输出不失望的人的数量的最大值。

不难想到，先服务服务时间少的，后面的人等的时间就少。

所以，可以用排序的思想，定义一个$a$数组，$sort$一下。

然后遍历$a_1-a_n$，如果当前的人并没有失望，则$x+1$，$sum+=a_i$。

请你务必把数组**开大点**。。

代码实现起来就很简单了：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100001],n,x=0,sum;
int main() {
	scanf("%d",&n);
	for(int i=1; i<=n; i++) scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	for(int i=1; i<=n; i++) {
		if(sum<=a[i]) {
			x++;
			sum+=a[i];
		}
	}
	printf("%d\n",x);
	return 0;
}
```


---

## 作者：伟大的王夫子 (赞：1)

若要获得更好的使用体验，欢迎来到[我的博客](https://www.luogu.com.cn/blog/I-AK-IOI/)

换位思考，统计失望的人数，剩下来的就是不失望的人数

为了使失望的人最少，我们要把这个数列排个序

为什么这么贪心是争取的？简单证明一下

设排序后的数列的值为$val_1,val_2\cdots val_n$

由于是排好了序的，对于一个$a_i$，设他的位置为$pos$
若$pos \le i$,显然是最优情况，如果这样他还失望，那么这个$a_i$就没得救了

否则，我们就可以一个一个扫描过来，如果这个人很失望，那么就不管他，否则就把他加进去并统计

~~如此简单的证明~~希望对初学者有帮助


上代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, a[100001], ans;
int main() {
	cin >> n;
	for (register int i = 1; i <= n; ++i) scanf("%d", a + i);//读入数据
	sort(a + 1, a + n + 1);//贪心
	int sum = 0;
	for (register int i = 1; i <= n; ++i) {
		if (sum <= a[i]) sum += a[i], ++ans;
	} 
	cout << ans;
} 
```


---

## 作者：s_ShotღMaki (赞：1)

题目叫queue，那我们就从队列入手咯

但，

## 像一个贪心

## but，题目叫Queue，所以我们就用queue来写，题解里好像还没有这么写的。

帖代码

```cpp
#include<cstdio>
#include<iostream>
#include<queue>
#include<algorithm>

#define maxn 100005
#define ll long long
#define WA AC
#define TLE AC
#define MLE AC
#define RE AC
#define CE AC

using namespace std;

int n;
int a[maxn];
ll sum;
int ans;
ll now;

queue <int> q;

inline int read ()
{
    int f = 1, x = 0;
	char ch;
    do {ch = getchar (); if (ch== '-') f = -1;} while (ch < '0' || ch > '9');
    do {x = x * 10 + ch - '0'; ch = getchar ();} while (ch >= '0' && ch <= '9');
    return f * x;
}

int main ()
{
	n = read ();
	for (int i = 1; i <= n; i ++) a[i] = read ();
	sort (a + 1, a + n + 1);
	for (int i = 1; i <= n; i ++) q.push (a[i]);
	while (!q.empty ())
	{
		now = q.front (); q.pop ();
		if (sum <= now) sum += now, ans ++;
	}
	printf ("%d", ans);
	return 0;
}
```
思路其实就是计算时间能压就压进去，如果不能压就pop掉了不管他，标准贪心。

这题看到我就觉得做过类似的，后来发现是我们学校模拟赛一道题的一部分，[p1230](https://www.luogu.org/problemnew/show/P1230)，这道题，其实这道紫（hong）题（ti）算是这道黄题其中的一部分了。做过这个紫题的可以去看那个黄题。




---

## 作者：first_fan (赞：0)

显然，我们要让每个人的等待时间发挥最大效力（说得丧心病狂一点，就是让他能等多久就等多久）。

所以我们考虑一个队列，这个队列里谁最急谁先来，满足了就下一个，如果下一个已经等不及，那就只好再见。

这个过程可以像其他题解一样排序，但是！本着模拟的原则，我们决定就建一个队列来搞定。这个队列显然有一定的优先性：谁急谁先。

那么优先队列（小根堆）就可以解决了，我们按照等待时间为优先级，越小优先级越高，一次次取出队首元素就好了，排序这个事情就交给bits库好了。

这样看来，连数组都不必建了呢。$\sf \huge OwO$

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ri register int
using namespace std;
int read()
{
	int num=0;
	int flg=1;
	char c=getchar();
	while(!isdigit(c))
	{
		if(c=='-')
		{
			flg=-1;
		}
		c=getchar();
	}
	while(isdigit(c))
	{
		num=(num<<1)+(num<<3)+(c^48);
		c=getchar();
	}
	return num*flg;
}

int n;
priority_queue<int,vector<int>,greater<int> > q;
//数字越小越优先
int main()
{
	n=read();
	for(ri i=1; i<=n; i++)
	{
		q.push(read());
	}//不必排序了
	int now=0;
	int tot=0;
	while(q.size())
	{
		int top=q.top();
		q.pop();//弹队
		if(now<=top)
		{
			tot++;
			now+=top;
		}//不满足条件就再见
	}
	return 0&printf("%d",tot);
}
/*
5
15 2 1 5 3
out:
4
*/
```

又及：怎么才能有效防止评分走水？（欢迎讨论区讨论）

---

## 作者：WKAHPM (赞：0)

#### 这道题基本思路就是贪心（~~标签里的队列是什么鬼不会是因为标题叫队列吧~~）

### 主要还是证明贪心的正确性(~~大佬勿喷~~)

  设总等待时间为 $time$ , $n$个人等待时间分别为$t_{1}$,$t_{2}$,$t_{3}$···$t_{n}$,要使总等待人数最少,则$time$
  要取最小值:
  
 $time$ = $t_{1}$+($t_{1}$+$t_{2}$)+($t_{1}$+$t_{2}$+$t_{3}$)+···+($t_{1}$+$t_{2}$+$t_{3}$+···$t_{n}$)
  
 $time$ = $n \cdot t_{1}$+ $(n-1)\cdot t_{2}$+ ··· + $t_{n}$
 
 当$t_{1} \le $ $t_{2} \le$ ······ $t_{n}$ 时，$time$为最小值(~~简单的证明过程~~)
 
 ——————————————————————————————————————————
 
 所以只要先每个人的等待时间排序一遍，设定一个总时间变量$time$,只要$time$小
 
 于这个人的等待时间答案就+1，同时$time$也要加上这个人的等待时间
 
 ### 代码
 
 ```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t[100010],sum,ti;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&t[i]);
	sort(t+1,t+n+1);//排序（从小到大)
	for(int i=1;i<=n;i++)
	{
		if(t[i]>=ti)//如果time<这个人等待时间
		{
			sum++;//答案+1
			ti+=t[i];//time加上这个人的等待时间
		 } 
	}
	printf("%d",sum);
	return 0;
}

```
 

---

## 作者：RealityCreator (赞：0)

# 既然没有Pascal的题解，那我就来发一篇
```pascal
var
  n,i,ans,time:longint;
  a:array[1..100001] of longint;
procedure sort(l,r:longint);
var
  i,j,x,y:longint;
begin
  i:=l;
  j:=r;
  x:=a[(l+r) div 2];
  repeat
    while a[i]<x do
     inc(i);
    while x<a[j] do
     dec(j);
    if not(i>j) then
    begin
      y:=a[i];
      a[i]:=a[j];
      a[j]:=y;
      inc(i);
      j:=j-1;
    end;
  until i>j;
  if l<j then
   sort(l,j);
  if i<r then
   sort(i,r);
end;//快排
begin
  readln(n);
  for i:=1 to n do read(a[i]);
  sort(1,n);
  for i:=1 to n do begin
    if time<=a[i] then begin
      inc(ans);
      inc(time,a[i]);
    end;
  end;
  write(ans);
end.
```

---

