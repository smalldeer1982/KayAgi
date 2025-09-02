# Restaurant

## 题目描述

A restaurant received $ n $ orders for the rental. Each rental order reserve the restaurant for a continuous period of time, the $ i $ -th order is characterized by two time values — the start time $ l_{i} $ and the finish time $ r_{i} $ ( $ l_{i}<=r_{i} $ ).

Restaurant management can accept and reject orders. What is the maximal number of orders the restaurant can accept?

No two accepted orders can intersect, i.e. they can't share even a moment of time. If one order ends in the moment other starts, they can't be accepted both.

## 样例 #1

### 输入

```
2
7 11
4 7
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5
1 2
2 3
3 4
4 5
5 6
```

### 输出

```
3
```

## 样例 #3

### 输入

```
6
4 8
1 5
4 7
2 5
1 3
6 8
```

### 输出

```
2
```

# 题解

## 作者：oycr0 (赞：10)

# [CF597B Restaurant](luogu.com.cn/problem/CF597B)题解
### 贪心策略：将结束时间早的订单先进行
其实这道题跟[P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)没什么区别，只是订单结束时不能立刻开始，需要等待一个时间单位,


#### 其余内容将在代码中详细讲解
```cpp
#include <bits/stdc++.h>
using namespace std;
struct node
{
	int s,e;//使用结构体来存放开始和结束时间会更简便
}a[500001];
bool cmp(node x,node y)//结构体使用快排需要写一个CMP函数确定排序顺序及排序目标
{
	return x.e<y.e;//贪心策略：把结束时间早的放在前面
}
int n,i,s;
int main() {
	cin>>n;
	for(i=1;i<=n;i++)
		cin>>a[i].s>>a[i].e;
	sort(a+1,a+1+n,cmp);//快速排序，CMP调用上文函数
	int o=-1;//因为开始时间可从0开始，所以将当前时间初始化至-1
	for(i=1;i<=n;i++)
		if(a[i].s>=o){//如果第i个订单的开始时间大于等于当前时间，该订单可以进行
			s++;//计数器+1
			o=a[i].e+1;//将当前时间设置为该订单结束时间+1，因为通过样例可知订单结束时是不能马上开始新订单的
		}
	cout<<s;
	return 0;
}
```




---

## 作者：Alex_Wei (赞：5)

#### 最大线段覆盖

和 [$\color{#00bfff}P1803$](https://www.luogu.org/problem/P1803) 只有区间端点的处理不一样

把区间按照右端点从小到大排序，然后贪心计算答案

代码如下

```
#include<bits/stdc++.h>
using namespace std;
struct node{
	int x,y;
}p[500005];
bool cmp(node a,node b){return a.y<b.y;}//右端点从小到大排序
int n,s,w;//w是目前右端点
int main()
{
	cin>>n;
	for(int x=1;x<=n;x++)cin>>p[x].x>>p[x].y;
	sort(p+1,p+n+1,cmp);
	for(int x=1;x<=n;x++)
		if(p[x].x>w)s++,w=p[x].y;//符合要求就取
	cout<<s;
	return 0;
}
```

求赞qwq

---

## 作者：Ryan_Yu (赞：4)

此题为结构题练习题，首先，我们需注意端点的位置：要按照右端点从小到大排序。

然后我们把 $start_i$ 定为开始时间，把 $finish_i$ 定为结束时间，$now$ 为现在时间。

然后用 `sort` 进行排序。

最后进行判断：如果现在时间比后一个单子的开始时间小，那么 $ans \gets ans+1$，否则将不会给予处理。

```cpp
#include<bits/stdc++.h>
using namespace std;
struct Node
{
    int start,finish;
};
bool cmp(Node b,Node c)
{
    return b.finish<c.finish;
  	 //这一条语句与sort的排列语句相同，只不过为a数组为Node型，要用Node型排序。
}
Node a[5000005];
int i,n,now,ans;
int main()
{
	 cin>>n;
    for(i=1;i<=n;i++)
        cin>>a[i].start>>a[i].finish;
    sort(a+1,a+1+n,cmp);
    for(i=1;i<=n;i++)
    {
        if(a[i].start>now)
        {
            ans++;
            now=a[i].finish;
        }
    }
    cout<<ans<<endl;
    return 0;
}
```




---

## 作者：精神小伙！ (赞：1)

## 思路
这道题和[P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)基本一样，只不过这道题订单结束后还要等一个时间。

先将所有的结束时间排序，然后依次进行贪心。如果能够接受就接受；如果订单冲突，就放弃。

## 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
struct Node{
	int L,R;
}a[1000010];
bool mycmp(Node a,Node b)
{
	return a.R<b.R;
}
int main()
{
	int n,ans=0;
	cin>>n;
	for(int i=1;i<=n;++i)
		cin>>a[i].L>>a[i].R;
	sort(a+1,a+n+1,mycmp);
	int t=-1; 
	for(int i=1;i<=n;++i)
	{
		if(a[i].L>t) ans++,t=a[i].R;
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：封禁用户 (赞：1)

一道典型的贪心例题。  
题解>>[CF597B](https://www.luogu.com.cn/problem/CF597B)  
### 题意简述:  
- 一餐馆收到 $n$ 个预订订单，每个订单都给出开始时间和结束时间，求最多可接受的订单数。  
- 不可同时进行两个订单。    

### 算法分析:  
#### 算法模型:   
给定 $n$ 个开区间（begin$i$，end$i$），选择尽量多的区间，使得两两不相交。  
#### 做法：  
首先按照 end$1$ $\le$ end$2$ $\le$ ... $\le$ end$n$ 的顺序，依次考虑各个订单，如果没有和已经接受的订单冲突，就选；否则就不选。  
#### 正确性：  
如果不选 end$1$，假设第一个选择的是 end$i$，则如果 end$i$ 和 end$1$ 不交叉则多选一个 end$1$ 更划算；如果交叉则把 end$i$ 换成 end$1$ 不影响后续选择。  
### Code:  
```cpp
#include <iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
struct order{   //利用结构体存各订单的开始时间和结束时间
	int begin;
	int end;
}a[500001];
bool cmp(order x,order y)   //依据结束时间升序排序
{
	return x.end<y.end;
}
int main()
{
	//freopen("input.in","r",stdin);
	//freopen("print.out",stdout);
	ios::sync_with_stdio(0);   //加速cin输入和cout输出
    int n;   //定义订单数
    int t=-1,ans=0;   //定义上一结束时间并初始化为-1（可使第一个区间与其他区间的操作相同）、可接受的订单总数
    cin>>n;
    for(int i=1;i<=n;i++)
    {
    	cin>>a[i].begin>>a[i].end;
    }
    sort(a+1,a+1+n,cmp);   //排序
    for(int i=1;i<=n;i++)
    {
    	if(a[i].begin>t)   //如果当前订单与之前最后结束的订单不冲突，就结束当前订单
    	{
    		ans++;
    		t=a[i].end;
    	}
    }
    cout<<ans;
    //fclose(stdin);fclose(stdout);
	return 0;   //结束整个程序
}
```
### 结果（未吸氧）:  
![JieGuo](https://cdn.luogu.com.cn/upload/image_hosting/5nababdc.png)  
企鹅的题解到此结束，祝各位 OIers 进步 ++~

---

## 作者：Carotrl (赞：1)

简单的贪心。

其实题目就是经典的线段覆盖问题。

### 先按右端点小到大排序，再从前向后扫描，如果上一次结束时间小于这次开始时间，那么这次订单可以接受，同时更新结束时间。

代码（压了几行：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
void in(int &x){//快读
    x=0;int f=1;char c=getchar();
    while((c<'0'||c>'9')&&c!='-')c=getchar();if(c=='-')f=-1,c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+c-'0',c=getchar();x*=f;
}
struct xd{int l,r;}a[1000005];
bool operator <(const xd &q,const xd &w){if(q.r!=w.r)return q.r<w.r;return q.l<w.l;}//右端点从小到大
int n,s,last;
int main(){
	in(n);
	for(int i=1;i<=n;i++){in(a[i].l);in(a[i].r);}
	sort(a+1,a+1+n);//排序
	s++;last=a[1].r;
	for(int i=2;i<=n;i++){if(a[i].l>last)++s,last=a[i].r;}//符合要求就接受
	printf("%d",s);
	return 0;
}
```


---

## 作者：_easy_ (赞：0)

# 思路
贪心

先将开始和结束时间放入结构体，然后按照结束时间排序，最后按照排序好的订单来模拟就行了。但是要注意：在模拟的时候，一定将当前时间设置为上一单结束时间 $+1$。

# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,ans,t;
struct node{
	int a,b;
}a[500005];
bool cmp(node x,node y){
	return x.b<y.b;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].a>>a[i].b;
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++){
		if(a[i].a>=t){//如果这单开始时间在上一单结束时间+1之前
			t=a[i].b+1;
			ans++;
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：BlackPanda (赞：0)

**[题目传送门](https://www.luogu.com.cn/problem/CF597B)**


------------
### 我的思路：
这道题就是贪心中的经典**区间覆盖问题**，先用右端点从小到大排序目的**是先进行时间少的订单**，然后用贪心算法进行计算：循环判断：
- **如果当前时间和订单开始时间不重复**，接受订单，就让计数器累加，然后把当前时间更新为订单结束时间。
- 否则拒绝订单，进行下一次循环

最后输出最大接受订单数

------------
### 代码如下：


```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std; 
struct Node{
	int s;	//订单开始时间 
	int e;	//订单结束时间 
}a[500010];
bool cmp(Node a,Node b){
	return a.e<b.e; 	//右端点从小到大排序 
}
int ans;	//计数器 
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)	cin>>a[i].s>>a[i].e; 
	sort(a+1,a+n+1,cmp);
	int now_time=-1;	//时间可以从 0 开始，当前时间要初始化成 -1
	for(int i=1;i<=n;i++){
		if(a[i].s>now_time){	//如果订单开始时间和当前时间不重复，就可以接受订单 
			ans++;	//符合条件就计数器累加 
			now_time=a[i].e;
		} 
	}
	cout<<ans<<endl;	//最后输出可以接受的最大订单数 
	return 0;
}
```


---

## 作者：BMTXLRC (赞：0)

### 思路：

贪心，按照区间右端点排序，发现如果不重合就直接加上，然后更新目前的区间右端点。，如果重合那肯定不能取，跳到下一个。

定义一个结构体，里面的变量一个为区间左端点，一个为区间右端点。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{int x,y;}a[500005];
bool cmp(node a,node b){return a.y<b.y;}
int n,s,now;
int main(){
	cin>>n;
	for(register int i=1;i<=n;i++) cin>>a[i].x>>a[i].y;
	sort(a+1,a+n+1,cmp);
	for(register int i=1;i<=n;i++) if(a[i].x>now) s++,now=a[i].y;
	cout<<s;
}
```


---

## 作者：动态WA (赞：0)

既然已经有大佬给出了正解，那我就来讲讲思路吧。(~~水题解警告~~

我们先按照订单的结束时间从小到大排序，对于任意个结束时间相同的订单，无论接受哪个，对后面的订单的影响都是相同的，所以这任意个个订单能选哪个就选哪个。

**这时**，可能有的蒟蒻（~~dalao~~）会问，为什么不按起始时间排序呢？

假如我们按照起始时间排序，跟据思路的话就是在起始时间相同的订单中选时间最短那个。可是——设a订单起始时间比b订单早一秒，结束时间比b订单晚99999秒，这时选择b订单肯定是划算的，可是程序由于根据起始时间排序，会选择a订单，而不能选择接下来的b订单。

**综上所述**，我们不能使用起始时间排序。（如果你是大佬并掌握玄学解法可以尝试）

另外一位大佬的代码已经写得很详细简洁了，大家看他的就行了。（~~其实是我码风过于奇特~~）

---

