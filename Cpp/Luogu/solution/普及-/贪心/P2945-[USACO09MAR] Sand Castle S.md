# [USACO09MAR] Sand Castle S

## 题目描述

Farmer John has built a sand castle! Like all good castles, the walls have crennelations, that nifty pattern of embrasures (gaps) and merlons (filled spaces); see the diagram below. The N (1 <= N <= 25,000) merlons of his castle wall are conveniently numbered 1..N; merlon i has height M\_i (1 <= M\_i <= 100,000); his merlons often have varying heights, unlike so many.

He wishes to modify the castle design in the following fashion: he has a list of numbers B\_1 through B\_N (1 <= B\_i <= 100,000), and wants to change the merlon heights to those heights B\_1, ..., B\_N in some order (not necessarily the order given or any other order derived from the data).

To do this, he has hired some bovine craftsmen to raise and lower the merlons' heights. Craftsmen, of course, cost a lot of money. In particular, they charge FJ a total X (1 <= X <= 100) money per unit height added and Y (1 <= Y <= 100) money per unit height

reduced.

FJ would like to know the cheapest possible cost of modifying his sand castle if he picks the best permutation of heights. The answer is guaranteed to fit within a 32-bit signed integer.

Note: about 40% of the test data will have N <= 9, and about 60% will have N <= 18.

## 说明/提示

FJ's castle starts with heights of 3, 1, and 1. He would like to change them so that their heights are 1, 2, and 2, in some order. It costs 6 to add a unit of height and 5 to remove a unit of height.


FJ reduces the first merlon's height by 1, for a cost of 5 (yielding merlons of heights 2, 1, and 1). He then adds one unit of height to the second merlon for a cost of 6 (yielding merlons of heights 2, 2, and 1).


## 样例 #1

### 输入

```
3 6 5 
3 1 
1 2 
1 2 
```

### 输出

```
11 
```

# 题解

## 作者：ysy666 (赞：20)

题目描述:

约翰用沙子建了一座城堡．正如所有城堡的城墙，这城墙也有许多枪眼，两个相邻枪眼中间那部分叫作“城齿”． 城墙上一共有N(1≤N≤25000)个城齿，每一个都有一个高度Mi.(1≤尬≤100000)．现在约翰想把城齿的高度调成某种顺序下的Bi，B2，…，BN(I≤Bi≤100000). -个城齿每提高一个单位的高度，约翰需要X(I≤X≤100)元；每降低一个单位的高度，约翰需要Y(1≤y≤100)元． 问约翰最少可用多少钱达到目的．数据保证答案不超过2^32．

解题思路：

先将修改前后的数据排一次序，比较相对应的每一位的大小，求出他们的差，然后\*x或是\*y

附上代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
int n,x,y;
int a[100010],b[100010];  //两个数组分别记录初始状态和修改后的 
long long ans;  //保险起见还是用long long吧 
int main()
{
    cin>>n>>x>>y;
    for(int i=1;i<=n;i++)  cin>>a[i]>>b[i];
    sort(a+1,a+1+n);  //排序两次 
    sort(b+1,b+1+n);  //使修改前后一一对应 
    for(int i=1;i<=n;i++)
    {
        if(a[i]<b[i])  ans+=(b[i]-a[i])*x;  //如果修改前小于修改后，就让他们的差*x 
        else  ans+=(a[i]-b[i])*y;  //反之*y，相等的差为0，所以不用考虑 
    }
    cout<<ans;  //最后直接将ans输出即可 
    return 0;
}
```

---

## 作者：花千树 (赞：6)

这题看到有dalao用优先队列做，其实用数组做也比较方便（主要是刚学的新手好理解）

读入数据，再调用快排函数，对号入座，最后输出

一道经典贪心，话不多说，上代码！

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>//万能头文件，sort必备
using namespace std;
long long ans;//其实题目上说2^31-1，不会爆int，但开long long保险一点
int a[1000005],b[1000005];//数组开大点，不会错（只要不爆）
int main(){//过程华丽开始
    int n,x,y;
    cin>>n>>x>>y;//读入
    for(int i=1;i<=n;i++){//读入
        cin>>a[i];
        cin>>b[i];
    }
    sort(a+1,a+1+n);//直接快排，用贪心做
    sort(b+1,b+1+n);
    for(int i=1;i<=n;i++){//开始处理（贪心）
        if(a[i]>b[i])ans+=(a[i]-b[i])*y;//如果高就下降
        if(a[i]<b[i])ans+=(b[i]-a[i])*x;//如果低就上升
        //这里其实省了一步等于的情况，其实要不要无所谓，等于本来就不加不减QAQ
       }
    printf("%lld\n",ans);//输出，记得用long long就对号入座用%lld，用int就%d
    return 0;//过程华丽结束
}

```

---

## 作者：lizongru (赞：4)

来一发Pascal题解，感觉p党在洛谷是弱势群体。。。

思想和楼上差不多，也是排序和贪心

还有不用quicksort就有一个点会TLE，要注意一下。

下面贴AC代码：

```cpp
var ans,i,j,n,x,y,tmp:longint;
    a:array[1..30000] of longint;
    b:array[1..30000] of longint;
procedure qsorta(l,r: longint);
var i,j,x,y: longint;
begin
  i:=l; j:=r; x:=a[(l+r) div 2];
  repeat
    while a[i]<x do inc(i);
    while x<a[j] do dec(j);
    if not(i>j) then
    begin
      y:=a[i]; a[i]:=a[j]; a[j]:=y;
      inc(i); j:=j-1;
    end;
  until i>j;
  if l<j then qsorta(l,j);
  if i<r then qsorta(i,r);
end;
procedure qsortb(l,r: longint);
var i,j,x,y: longint;
begin
  i:=l; j:=r; x:=b[(l+r) div 2];
  repeat
    while b[i]<x do inc(i);
    while x<b[j] do dec(j);
    if not(i>j) then
    begin
      y:=b[i]; b[i]:=b[j]; b[j]:=y;
      inc(i); j:=j-1;
    end;
  until i>j;
  if l<j then qsortb(l,j);
  if i<r then qsortb(i,r);
end;
begin
  readln(n,x,y);
  for i:=1 to n do
    readln(a[i],b[i]);
  qsorta(1,n);
  qsortb(1,n);
  ans:=0;
  for i:=1 to n do
    if a[i]<b[i] then ans:=ans+(b[i]-a[i])*x
      else ans:=ans+(a[i]-b[i])*y;
  writeln(ans);
end.
```

---

## 作者：妖孽寒 (赞：3)

水题解啦QAQ

这是一道比较~~水~~经典的贪心QAQ

题目翻译已经有了，我发下思路QAQ

题目需要总钱数最小，则把代表修建前和修建后的数组排序，再根据大小关系算钱QAQ

具体的证明(懒得写)QAQ

[这里](https://www.cnblogs.com/Leohh/p/7648607.html)


上代码
```
#include<bits/stdc++.h>//万能头
using namespace std;//比较喜欢用cin,cout（就加这个）
long long a[25005],b[25005];//开全局省的清零（a：之前，b:之后）
int main()
{
    int m,n1,n2;
    cin>>m>>n1>>n2;
    for(int i=0;i<m;i++)
    {
        cin>>a[i]>>b[i];//输入
    }
    sort(a,a+m);//自带的排序（不用写cmp，这样是从小到大）
    sort(b,b+m);
    unsigned long long ans=0;//顺便说一下，有些时候你longlong爆掉，不想写高精偶尔用这个会OK（比long long大一点）
    for(int i=0;i<m;i++)
    {
        if(a[i]>b[i])
        {
            ans+=(a[i]-b[i])*n2;//要减高度*n2
        }
        else
        {
            ans+=(b[i]-a[i])*n1;//加高度*n1
        }
    }
    cout<<ans<<endl;//输出
}
```

---

## 作者：autoint (赞：1)

##经典的贪心模型，常规思路：将M和B排序即可

看到没有人用优先队列，于是我的showtime到了

#说下思路：

- 读入时将数加入啊a，b堆中，不用处理（二叉堆本来就有有序的性质）

- 读完后逐个判断，照题目模拟即可

- 总时间复杂度：O(nlogn)  其实就是**堆排序**的时间复杂度

楼下的那位用了**sort**还说是O(2n)的，大家不要犯这种低级错误

贴代码：






```cpp
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<ctime>
#include<iostream>
#include<string>
#include<vector>
#include<list>
#include<deque>
#include<stack>
#include<queue>
#include<deque>
#include<map>
#include<set>
#include<algorithm>
#pragma GCC optimize(2)//STL必带
using namespace std;
#define ll long long
const int maxn=0x7f;
const int INF=0x7fffffff;
inline void read(int&x){//quick input
    int data=0,w=1;
    char ch=getchar();
    while(ch!='-'&&!isdigit(ch))
        ch=getchar();
    if(ch=='-')
        w=-1,ch=getchar();
    while(isdigit(ch))
        data=10*data+ch-'0',ch=getchar();
    x=data*w;
}
void write(int x){//quick output
    if(x<0)
        putchar('-'),x=-x;
    if(x>9)
        write(x/10);
    putchar('0'+x%10);
}
priority_queue<int> a,b;
int main()
{
//    freopen(".in","r",stdin);
//    freopen(".out","w",stdout);
    int n,x,y,t;
    read(n);read(x);read(y);
    for(int i=1;i<=n;++i){//use variable "t" to improve memory and time
        read(t);
        a.push(t);
        read(t);
        b.push(t);
    }
    int ans=0,u,v;
    while(!a.empty()){//slower than "sort", easier to understand though
        u=a.top();
        a.pop();
        v=b.top();
        b.pop();
        if(u<v)//do as  what the problem said
            ans+=(v-u)*x;
        else if(u>v)
            ans+=(u-v)*y;
    }
    write(ans);
//    fclose(stdin);
//    fclose(stdout);
    return 0;
}

```

---

## 作者：青鸟_Blue_Bird (赞：0)

这道题第一眼看似乎有点难度 ~~别说你看不懂英文~~

然而，这道题只要用两次排序就能过了，具体思路如下。

通过两次排序，将更改前与更改后的数按大小排序配对起来，这样就可以使得更改的差值尽可能的小，从而减少花费。


就拿数据3 1 1 为例子吧，我们要将他们变成1 2 2 。
（注意，这里并没有说明一定要按顺序，给不懂的小伙伴提个醒）。

如果我们将数据进行排列，那么他就变成1 1 3，
第二组就变成 1 2 2 。
1 - 1 = 0，
2 - 1 = 1，
3 - 2 = 1，
怎么样，是不是比原先的配对省钱多了？
以下是我的代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,x,y,m[666666],b[666666];
long long ans = 0;
int main(){
	cin >> n >> x >> y;
	for(int i = 1; i <= n; i++){
		cin >> m[i] >> b[i];//常规输入不多说
	}
	sort(m + 1,m + n + 1);
	sort(b + 1, b + n + 1);//不喜欢用函数的朋友们可以自行敲排序
	
	for(int i = 1; i <= n; i++){
		if(m[i] > b[i])ans += (m[i] - b[i]) * y;
		else 
		ans += (b[i] - m[i]) * x;//注意x和y不要打反了，我在这吃了好几次亏 
	}
	cout << ans;//完美输出
	return 0;
}
```



---

## 作者：sjl40 (赞：0)

一题简单的模拟+贪心。（给定了钱数，排个序就好了。）

操作：

First：排序。（两个都要。进行匹配。从大到小，小到大都OK。）

Then:进行匹配（多的加，少的减。）算钱数。

Finally:输出钱数



------------


```cpp
#include<iostream>
  
#include<cstdio>
  
#include<algorithm>

using namespace std;
  
int n,u,d,a[25000+10],b[25000+10],s;
int main()
  
{ 
  
 cin>>n>>u>>d;
  
 for(int i=1;i<=n;i++)
                      
  scanf("%d%d",&a[i],&b[i]);
                      
 sort(a+1,a+1+n);//为了匹配进行排序
 
 sort(b+1,b+1+n);//为了匹配进行排序
 
 for(int i=1;i<=n;i++)
 
 {
  
  if(a[i]>b[i])s+=(a[i]-b[i])*d;//多的加提高高度的钱数。
  
  else s+=(b[i]-a[i])*u;//少的加减少高度的钱数。
 
 }
  
 cout<<s;//输出

}
```


---

## 作者：Extra·G·Ordinary_ (赞：0)

刚开始读题的时候读不懂意思（太菜了），在纸上写了一遍样例瞬间明白 。可以用集合来表示目前的城齿高度和期望的城齿高度。

输入样例#1： 

3 6 5 

3 1 

1 2 

1 2 

输出样例#1： 

11

即目前的城齿为集合jiu（旧）{3,1,1}；

期望的集合为集合xin（新）{1,2,2}；

我们发现如果不经过一定的处理得出的答案是（3-1）*5+2  *（2-1）*6=22，不是样例给出的11。
所以运用到了贪心的策略，修改次数最少肯定就是最佳答案了，样例中的11正是把集合jiu中的3变成2，把1变成2得出6+5=11；

到了这里就不难看出这是一道排序题目了，萌新代码如下（只要敲的时候注意就会一次ac）







```cpp
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;

#define re register //玄学register
#define LL long long//保险用ll
const int maxn=100005;

LL n,x,y;
LL jiu[maxn];
LL xin[maxn];
LL ans=0;

inline void init()//清空数组（可有可无）
{
	memset(jiu,0,sizeof(jiu));
	memset(xin,0,sizeof(xin));
}
int main()
{
	init();
	cin>>n>>x>>y;
	for(re int i=1;i<=n;++i)
		cin>>jiu[i]>>xin[i];
	sort(jiu+1,jiu+1+n);
	sort(xin+1,xin+1+n);
	for(re int j=1;j<=n;++j)
	{
		if(jiu[j]==xin[j])continue;
		else if(jiu[j]>xin[j])
		{
			ans+=(jiu[j]-xin[j])*y;
			continue;
		}
		else if(jiu[j]<xin[j])
		{
			ans+=(xin[j]-jiu[j])*x;
			continue;
		}
	}
	cout<<ans<<endl;
	return 0;
}
```



---

## 作者：zhangzhaoke (赞：0)

```cpp
#include<iostream>
#include<algorithm>//sort排序函数头文件 
using namespace std;
int main(){
	int n,x,y;//据题意 
	cin>>n>>x>>y;//输入 
	int a[n+1],b[n+1];//个人习惯，防止浪费 
	for(int i=0;i<n;i++)cin>>a[i]>>b[i];
	sort(a,a+n);//排序 
	sort(b,b+n);//同上 
	int answer=0;//答案 
	for(int i=0;i<n;i++){//循环计算 
		if(a[i]>b[i])answer+=(a[i]-b[i])*y;//注意此处应该乘y而不是乘x 
		else answer+=(b[i]-a[i])*x;//注意此处应该乘x而不是乘y		
	}
	cout<<answer;//输出 
	return 0;
}
/*
解释一下，因为每个分别最小，所以总和一定最小(贪心思想) 
*/ 
```

---

## 作者：Kio_ (赞：0)

### 这题有个大坑点。

我们用a[i]来表示第i个沙堡齿轮的位置，用b[i]来表示约翰想要调的位置。（用sort排序，使“大对大，小对小”，使差最小，即贪心）   。

# 注意！
当a[i]-b[i]<0（即a[i]的位置比b[i]低）时，齿轮应该往上调，而不是往下。（~~本来~~是很容易想到的，~~但我在这卡了10分钟~~）反之亦然。

上代码：

```
#include<cstdio>
#include<algorithm>
using namespace std;
int a[25010];//a数组
int b[25010];//b数组
int main()
{
    int n,x,y;//题目中的n，x，y
    scanf("%d %d %d",&n,&x,&y);
    for(int i=0;i<n;i++)
    {
        scanf("%d %d",&a[i],&b[i]);//输入
    }
    sort(a,a+n);//排序
    sort(b,b+n);
    int num=0;
    for(int i=0;i<n;i++)
    {
        if(a[i]-b[i]<0)
        {
            num+=(b[i]-a[i])*x;//注意！注意！
        }
        else
        {
            num+=(a[i]-b[i])*y;//注意！注意！
        }
    }
    
    return !printf("%d",num);//奇怪的东西
}
```

---

## 作者：guobaipeng0 (赞：0)

怎么就没人做呢？？

贪心算法，排序，直接把第i个齿，改成第i个新高度的齿，完了！


C++代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long s,i,n,x,y,a[25005],b[25005];
int main()
{
    cin>>n>>x>>y;
    for (i=1; i<=n; i++) cin>>a[i]>>b[i];
    sort(a+1,a+n+1);
    sort(b+1,b+n+1);
    for (i=1; i<=n; i++)
    {
        if (a[i]<b[i]) s+=(b[i]-a[i])*x; else s+=(a[i]-b[i])*y;  //计算总钱数
    }
    cout<<s;
    return 0;
}
完。。。
```

---

## 作者：zy小可爱ღ (赞：0)

时隔，额，多少个月来着。。。算了（就是这么随便）。。

好，开始说题目

这个题目是一道很明显的贪心题，而且没有陷阱，照常规思维做就好

先读入数据，然后排序，让最小的现在的高度对上最小的需要改造的高度

时间复杂度大概在O（2n）（算上读入。。）

具体见程序：：



```cpp
#include<algorithm>//sort的头文件
#include<cstdio>
using namespace std;
int n,x,y,ans;//读入的数据和答案
int a[25005],b[25005];//现在的高度和需要被改造的高度
int main(){
    scanf("%d  %d  %d",n,x,y);//读入，比cin，cout读入要快，具体快多少不清楚，但有时候确实会有卡读入输出的题目。。
    for(int i=1;i<=n;i++){
        scanf("%d  %d",a+i,b+i);//同上
    }
    sort(a+1,a+1+n);//排序
    sort(b+1,b+1+n)；
    for(int i=1;i<=n;i++){//对排完序的高度遍历一遍
        ans+=(a[i]>=b[i]?((a[i]-b[i])*y):((b[i]-a[i])*x));//三目表达式，实在理解不了就用if else语句
    }
    printf("%d\n",ans);//最后输出数据
    return 0;
}
```
完美结束
（对于抄代码党，我把代码小小的改了一下（三目表达式没改，不然我怕有些人改不回去。。），别想直接Ctrl C+Ctrl V ）


---

