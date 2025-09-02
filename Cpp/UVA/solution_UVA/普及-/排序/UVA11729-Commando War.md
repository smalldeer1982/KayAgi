# Commando War

## 题目描述

>  _我们在树林里等待命令，前线的消息却始终没有传来  
到傍晚，枪声已经遥远  
啊，我们悄悄地穿过阴影，轻轻地从树间溜走  
在薄雾中穿过他们的防线，跪着爬过田野  
而我所能看到的  
是空中的火焰，发出红光，映衬着随风飘散的烟雾_

有一场对你的国家来说形势并不乐观的战争。现在是时候行动了。你有一支突击队可以调遣，并计划对附近一个重要的敌军营地进行伏击。你的队伍里有 $N$ 名士兵。在你总体的计划中，每个士兵都有独特的职责，你不希望任何士兵知道其他人的计划，以便每个人都能专注于自己的任务。为了达成这一点，你分别向每个士兵简要说明任务，并在他们被派往战场之前单独进行简报。你知道每个士兵完成任务需要一定的时间。你也很清楚给每个士兵进行简报需要多长时间。由于你急于尽快完成整个行动，你需要找到一个简报顺序，使所有士兵完成任务的总时间最少。你可以假设，没有士兵的计划依赖于其他士兵的任务。换句话说，一旦士兵开始执行任务，他可以不间断地完成任务。

## 样例 #1

### 输入

```
3
2 5
3 2
2 1
3
3 3
4 4
5 5
0```

### 输出

```
Case 1: 8
Case 2: 15```

# 题解

## 作者：Cripple_Abyss (赞：9)

## [题目传送门](https://www.luogu.com.cn/problem/UVA11729)

## STEP 1 大致题意：
- 有个上司要给 n 个部下安排任务。

- 安排任务分为两个步骤：**交代任务** 和 **执行任务**。

- 这个上司在同一时刻 **只** 能给一个部下 **交代任务** 。

- 而这些部下可以在同一时刻 **执行他们各自的任务** 。

- 问 **执行完所有任务** 的 **最短时间** 。

## STEP 2 题目解法：

- 一道很明显的贪心题。

- 我们先将 **执行任务时间长的人** 的任务安排了。
 
- 然后再安排 **执行任务时间短的** 。

## STEP 3 Code ：
```cpp
#include <algorithm>
#include <cstdio>
using namespace std;
inline int in() {
	int x=0,f=1;
	char ch=getchar();
	while (ch<'0'||ch>'9') {
		if (ch=='-') f=-1;
		ch=getchar();
	}
	while (ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return x*f;
}
const int N=1000+5;
int n,cnt,now,ans;
struct node {
	int x,y;
} a[N];
bool cmp(node a,node b) { 
	if (a.y!=b.y) return a.y>b.y;
	return a.x<b.x;
}
int main() {
	while (1) {
		n=in();
		if (!n) return 0;
		cnt++;
		for (int i=1; i<=n; ++i) a[i].x=in(),a[i].y=in(); // 读入 
		sort(a+1,a+n+1,cmp); // 排序 
		now=ans=0; // now 指：下一个安排任务的时间    ans 指：执行完任务的时间 
		for (int i=1; i<=n; ++i) now+=a[i].x,ans=max(now+a[i].y,ans);  // 取大值 
		printf("Case %d: %d\n",cnt,ans); // 输出 
	}
	return 0;
}
```

都看到这里了，点个赞再走呗 QwQ

---

## 作者：asasas (赞：4)

一道简单贪心题。

本题需要按执行任务的时间**从大到小排**，先交代执行时间长的任务，留更多的时间去执行任务。然后遍历一遍，每次加上交代时间，同时每次将**最终答案ans**和当前**共交代过的时间**再加上这个**部下执行任务**的时间取**较大值**（想一想为什么，代码里解释）。最后输出即可。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
struct as{
	int b,j;
}a[1005];//定义结构体 
inline bool cmp(as x,as y){//排序函数 
	return x.j>y.j;//按执行任务所花时间从大到小排 
}
int main(){
	int n,m,num=0;
	while(1){
		cin >> n;
		if (!n) return 0;//读入0就退出
		for (register int i=1;i<=n;i++){
			cin >> a[i].b >> a[i].j;//读入 
		} 
		sort(a+1,a+1+n,cmp);//按照cmp的排序方式将a数组排序
		int ans=0,sum=0;//ans最终用时,sum为过渡变量 
		for (register int i=1;i<=n;i++){
			sum+=a[i].b;//加上交代的时间
			ans=max(sum+a[i].j,ans);//sum+a[i].j是每个部下完成自己任务所花的时间，只有所有部下结束任务，才能最终结束，所以要取最大值 
		}
		cout << "Case " << ++num  << ": " << ans << endl;
	} 
}
```


---

## 作者：寒鸽儿 (赞：2)

#### UVA11729 Commando War
##### 题意
$1$ 台机器 $n$ 个任务的机器调度问题。 任务 $i$ 处理时间为 $B_i$ 执行时间为 $J_i$ 。  
数据范围 : $n \leqslant 1000, B_i,J_i \leqslant 10^4$ 。  
##### 题解
**贪心策略** : 按照 $J_i$ 降序排序 , 依次进行处理。  
**推导过程** : 假设有排列 $a$ 为一个操作方案。那么时间应该为 
$$
\sum_i b_{a_i} + \max_{1 \leqslant i \leqslant n}\{c_{a_i} - \sum_{j > i}{b_{a_j}}, 0 \}
$$
由于 $B_i \geqslant 0$ , 所以后缀显然是越长越大的 , 那么 $c_i$ 降序的策略显然能让 $\max$ 那部分的取值不大于其他策略。用交换法很容易证。  
##### code
```cpp
#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
#define repp(i,a,b) for(int i=(a);i<(b);++i)
#define perr(i,a,b) for(int i=(a);i>(b);--i)
#define debug(...) fprintf(stdout, __VA_ARGS__)
using namespace std;

typedef pair<int,int> pii;

template<class T> void cmax(T &x, T y) { x = x > y ? x : y; }

int main() {
    if(fopen("yl.in", "r")) {
        freopen("yl.in", "r", stdin);
        freopen("yl.out", "w", stdout);
    }
    int n, cnt;
    while(~scanf("%d", &n) && n) {
        vector<pii> v;
        v.resize(n);
        repp(i,0,n) scanf("%d %d", &v[i].first, &v[i].second);
        sort(v.begin(), v.end(), [&](pii &a, pii &b) { return a.second < b.second || (a.second == b.second && a.first > b.first); });
        int presum = 0, over = 0;
        repp(i,0,n) {
            cmax(over, v[i].second - presum);
            presum += v[i].first;
        }
        printf("Case %d: %d\n", ++cnt, presum + over);
    }
    return 0;
}
```

---

## 作者：A_Plus_Gu (赞：2)

## 此题解是按照刘汝佳的思路写的

### 考察内容：贪心

思路：执行时间较长的任务应该先交待，所以我们想到用贪心算法，按照j从大到小的顺序给各个任务排序，然后依次交代即可。

```
#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;
struct job{//定义结构体
	int j,b;//交待任务的时间和执行任务的时间
}ji[1001];
bool cmp(job a,job b){
	return a.j>b.j;
}//结构体排序（按照j从大到小的顺序排序）
int main(){
	int n,k=1;
	while(cin>>n&&n){//输入结束标志为N=0,所以当n不等于0时执行循环
		for(int i=1;i<=n;i++)cin>>ji[i].b>>ji[i].j;
		sort(ji+1,ji+n+1,cmp);
		int s=0,ans=0;
		for(int i=1;i<=n;i++){//贪心算法
			s+=ji[i].b;
			ans=max(ans,s+ji[i].j);
		}
		printf("Case %lld: %lld\n",k++,ans);
	} 
	return 0;
}

```


---

## 作者：yzhzs (赞：2)

# 分析
大佬们认为执行时间较长的任务应该先交待，显然应该用贪心算法。
```cpp
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
struct job{
	int j,b;
	bool operator < (const job& x)const{  //重载运算符
		return j>x.j;
	}
};
int main(){
	int n,b,j,kase=1;
	while(scanf("%d",&n)==1&&n){
		vector<job>v;
		for(int i=0;i<n;i++){
			scanf("%d%d",&b,&j);
			v.push_back((job){j,b});
		}
		sort(v.begin(),v.end());    	//使用上面的重载运算符
		int s=0;
		int ans=0;
		for(int i=0;i<n;i++){
			s+=v[i].b;					//此任务开始执行的时间
			ans=max(ans,s+v[i].j);		//任务完成的最晚时间
		}
		printf("Case %d: %d\n",kase++,ans);
	}
	return 0;
}
```

---

## 作者：Merron (赞：1)

这道题是一道贪心。

通过观察样例，我们会有一个直觉——**时间长的要先交代，时间短的靠后**。

举个栗子：
老师要安排2名同学打扫卫生，一个拖地(5min)，一个擦窗户(3min)，交代任务都要2min。如果你是老师，你怎样做？

---
方法一:先交代时间长的，后交代时间短的。
总用时:7min

---

方法二:先交代时间短的，后交代时间长的。
总用时:9min

(此处就不放图了，自行脑补)

很明显，方法一更优。

于是，可以写代码了。

---
Code:
```cpp
#include <bits/stdc++.h>
using namespace std ;

struct Job
{
	int j ;
	int b ;
	bool operator < (const Job& x) const
	{
		return j > x.j ;//结构体排序
	}
} ;

int n ;

vector<Job> v ;

void input()
{
	v.clear() ;
	for(int i = 0 ;i < n ;i ++)
	{
		int j, b ;
		cin >> j >> b ;
		v.push_back((Job){b, j}) ;
	}
}

void solve(int x)
{
	sort(v.begin(), v.end()) ;
	int s = 0 ;
	int ans = 0 ;
	for (int i = 0 ;i < n ;i ++)
	{
		s += v[i].b ;
		ans = max(ans, s + v[i].j) ;
	}
	printf("Case %d: %d\n", x, ans) ;
}

int main()
{
	int sum = 0 ;
	while(scanf("%d", &n) == 1 && n)
	{
		sum ++ ;
		input() ;
		solve(sum) ;
	}
	return 0 ;
}
```
P.S.:参考《算法竞赛入门经典训练指南》。

---

## 作者：唔啊唔 (赞：1)

这是一道简单的贪心题

```cpp
//蒟蒻代码请不要建议 
#include<bits/stdc++.h>
using namespace std;
int n;
struct sb{				//士兵结构体 
	int b,j;
}a[1010];
int v(sb x,sb y){		//执行时间越长就越早交代 
	return x.j>y.j;
}
int main(){
	int cnt=0;
	while(cin>>n){
		if(n==0)return 0;	//结束输入 
		cnt++;				//计算数据组数 
		int ans=0,sum=0;	//ans是在此之前的总交代时长 
		for(int i=1;i<=n;i++){
			cin>>a[i].b>>a[i].j;
		}
		sort(a+1,a+1+n,v);	 
		for(int i=1;i<=n;i++){
			ans+=a[i].b;
			if(sum<(ans+a[i].j))sum=ans+a[i].j;	//sum是这个士兵要执行到什么时候 
		}
		cout<<"Case "<<cnt<<": "<<sum<<endl;	//输出 
	}
	return 0;	//功德圆满 
}
```

---

## 作者：Umbrella_Leaf (赞：0)

[题目传送](https://www.luogu.com.cn/problem/UVA11729)

没啥好说的，就是
## 排序+贪心
首先假设我们有两个任务，一个需要1000000分钟交待（好复杂的任务），1分钟就可以完成；另一个需要1分钟交待，1000000分钟才可以完成（好难做的任务）。

显然第二个任务应该先交待。

那么我们建立如下推论：执行时间长的任务应该先交待。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
struct node{
	int b,j;
}p[1005];
bool cmp(node x,node y){
	return x.j>y.j;
}
int main(){
	int kase=0;
	while(scanf("%d",&n)==1 && n){
		for(int i=1;i<=n;i++)scanf("%d%d",&p[i].b,&p[i].j);
		sort(p+1,p+n+1,cmp);
		int s=0,ans=0;
		for(int i=1;i<=n;i++){
			s+=p[i].b;
			ans=max(ans,s+p[i].j);
		}
		printf("Case %d: %d\n",++kase,ans);
	}
	return 0;
} 
```
上述代码直接交上去就可以了。

下面是证明：

假设我们交换两个相邻任务 $X$ 和 $Y$ 的交待顺序（交换前 $X$ 在 $Y$ 之前），不难发现其他任务的交代结束时间以及完成时间没有受到影响，而这两个任务的完成时间有两种情况：

- 情况一：交换之前 $Y$ 比 $X$ 先结束。显然交换之后 $X$ 的完成时间延后， $Y$ 的结束时间提前，答案不会变好。

- 情况二：交换之前 $X$ 比 $$Y 先结束。因此答案不变好的充要条件是：交换后 $X$ 的结束时间不比交换前 $Y$ 的结束时间早。这个条件可以写成
$$B_{Y}+B_{X}+J_{X} \leq B_{X}+B_{Y}+J_{Y}$$
化简得
$$J_{X} \leq J_{Y}$$
这就是我们贪心的依据。

---

## 作者：RoRoyyy (赞：0)



```latex
    贪心策略：
        优先交代做任务时间长的
    证明：
        假设两个人A、B
        done[A] > done[B]
        先交代A:
            T1 = max (need[A] + done[A], need[B] + need[A] + done[B])
        先交代B：
            T2 = max (need[B] + done[B], need[B] + need[A] + done[A])
        显然need[B] + done[B] < need[B] + need[A] + done[B]
            need[A] + done[A] < need[B] + need[A] + done[A]
        因为之前假设done[A] > done[B]
        所以need[B] + need[A] + done[A] > need[B] + need[A] + done[B] > need[B] + done[B]
        所以 T2 > T1
        所以T1 更优

```

```cpp

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
const int N = 1005;
typedef pair<int, int> PII;
int n;
PII job[N];
int t = 0;
int main() {
    while(scanf("%d", &n) && n) {
        t++;
        for(int i = 1; i <= n; i++) 
            scanf("%d%d", &job[i].second, &job[i].first);
        sort(job + 1, job + 1 + n, greater<PII>() );
        int last = 0, ans = 0;
        for(int i = 1; i <= n; i++) {
            ans = max(ans, last + job[i].first + job[i].second);
            last += job[i].second;
        }
        printf("Case %d: %d\n", t, ans);
    }
    return 0;
}
```


---

## 作者：张亦弛 (赞：0)

贪心算法

执行时间较长的任务应该先交代，这样可以利用之前的人执行的时间来给之后的人交代，于是我们可以按照J从大到小的顺序安排任务，然后依次交代。

代码如下：



```cpp
#include<bits/stdc++.h>
using namespace std;
int n;//n个部下 
struct st//结构已存部下，方便排序 
{
	int b;
	int j;
}a[1005];
bool com(st &A,st &B)//自定义排序 
{
	return A.j>B.j;//按照执行任务时间从大到小排序 
}
int tot;//计数器，输出使用 
int main()
{
	while(cin>>n)//多组数据 
	{
		if(n==0)//结束信号
			break; 
		tot++;//计数器累加 
		memset(a,0,sizeof(a));//多组数据记得清0 
		for(int i=1;i<=n;i++)
			cin>>a[i].b>>a[i].j;//输入交代任务时间和执行任务时间 
		sort(a+1,a+1+n,com);//按照执行任务时间从大到小排序 
		int s=0;//记录交代道到第i个人交时代任务总时间 
		int ans=0;//记录最终的总时间 
		for(int i=1;i<=n;i++)
		{
			s+=a[i].b;//计算交代道到第i个人交时代任务总时间 
			ans=max(ans,s+a[i].j);//ans记录的是第i-1个人完成时的时间
			//比较交代到第i个人的时间加上这个第i个人的执行时间之和跟i-1个人完成时间作比较
			//如果s+a[i].j小的话，说明i可以在前面的人执行的时候来交代任务 
		}
		cout<<"Case "<<tot<<": "<<ans<<endl;//输出有点坑人，注意空格 
	}
	return 0;
} 
```

---

