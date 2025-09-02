# [USACO06DEC] River Hopscotch S

## 题目描述

Every year the cows hold an event featuring a peculiar version of hopscotch that involves carefully jumping from rock to rock in a river. The excitement takes place on a long, straight river with a rock at the start and another rock at the end, L units away from the start (1 ≤ L ≤ 1,000,000,000). Along the river between the starting and ending rocks, N (0 ≤ N ≤ 50,000) more rocks appear, each at an integral distance Di from the start (0 < Di < L).

To play the game, each cow in turn starts at the starting rock and tries to reach the finish at the ending rock, jumping only from rock to rock. Of course, less agile cows never make it to the final rock, ending up instead in the river.

Farmer John is proud of his cows and watches this event each year. But as time goes by, he tires of watching the timid cows of the other farmers limp across the short distances between rocks placed too closely together. He plans to remove several rocks in order to increase the shortest distance a cow will have to jump to reach the end. He knows he cannot remove the starting and ending rocks, but he calculates that he has enough resources to remove up to M rocks (0 ≤ M ≤ N).

FJ wants to know exactly how much he can increase the shortest distance \*before\* he starts removing the rocks. Help Farmer John determine the greatest possible shortest distance a cow has to jump after removing the optimal set of M rocks.

奶牛跳房子：从N块石头中移除M块，使得间距最小值最大。


## 说明/提示

Before removing any rocks, the shortest jump was a jump of 2 from 0 (the start) to 2. After removing the rocks at 2 and 14, the shortest required jump is a jump of 4 (from 17 to 21 or from 21 to 25).


## 样例 #1

### 输入

```
25 5 2
2
14
11
21
17```

### 输出

```
4```

# 题解

## 作者：seek_my_calling (赞：24)

#  河中跳房子（经典二分答案）
- 呃呃呃我是第一次写题解，请大佬指教。
- 这题是经典的二分答案题，求最大化的最小值。我们可以枚举最大跳远距离。大家千万别忘了把重点算进去！！当石头间的距离小于枚举出的距离时，记成答案。
- 好，不多说了，来看代码！！！


------------

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;
int l,n,m,a[50003],ans;//定义变量
int count(int mid)
{
	int j=0,x=0;//x记录删去石头数
	for(int i=1;i<=n+1;i++)
	{
		if(a[i]-a[j] < mid)//石头间距离如果小于枚举的，就记录并删去。
        x++;
		else j=i;//否则移动起点。
	}
	return x;
}
int main()
{
	scanf("%d%d%d",&l,&n,&m);
	for(int i=1;i<=n;i++)
	scanf("%d",&a[i]);
	sort(a+1,a+1+n); //别忘了排序。
	a[n+1]=l;//记录终点
	int left=1,right=l;
	while(left<=right)//开始二分。
	{
		int middle=(left+right)/2;
		if(count(middle)<=m)//计数函数
        {
		ans=middle;
		left=middle+1;	
		} 
		else right=middle-1;
	}
	printf("%d",ans);//输出
	return 0;
}
```

---

## 作者：_maze (赞：13)

一道二分练手题，做这道题我们首先来了解一下什么是二分

举个例子，查找一个队列里的元素，正常的方法跑一边时间复杂度是 O(n) ，一般也够用了，可是有些数据就会tle，怎么办呢？

有些同学可能玩过猜数游戏，那我们就知道每次都猜最中间的一个数，1024也只要十次就能猜完

突然感觉很激动有没有！！！

查数是不是也能这么查？

查数的代码我就不放上来了，重要的是我们能从查数中领悟二分的精髓。

二分中我们要定义两个边界，一个最大的，一个最小的。这两个边界就相当于两块板子，框住了一个范围。每次更新后范围越来越小，最后，剩下的那个数就是我们要的结果啦！

接着，我们就要缩小范围，判断mid（中间的数）是大了还是小了，大了右往左移，小了左往右移

然后，就可以找出结果了。下面说一下本题要注意的地方：

1、二分的一个大前提就是数据有序，这题很显然没有排过序，首先就用sort一波

2、这题最大肯定是起点到终点的距离了（+1，后面我会解释为什么），最小是不跑，肯定是零。

3、我们要不停的缩小范围，那什么时候停止呢？所以我们要用一个while循环

```cpp
while(l+1<t)//l为最小边界，n为最大边界
```

这个循环的好处就是在停下来时l<t，且他们是相邻的，会省掉很多麻烦。

4、这道题中不能像查数一样简单判断，我们需要一个函数来判断此时移的石块有没有超过能移的石块。

```cpp
int pd(int x){//x为mid，就是中间数
    int w=0,j=0;//w为放过的石块，j为第i个石块的上一个石块
    for(int i=1;i<=n+1;i++){
        if(a[i]-a[j]<x){//如果上一个石块小于最小值则要让它变大
            w++;//石块数++
        }
        else{
            j=i;//下一块石头的上一块是他
        }
    }
    return w<=m;//判断有没有大于规定
}
```

讲完这些，整个代码也就呼之欲出了！

```cpp
#include<bits/stdc++.h>
#define cheng xiaoke is so cute 
using namespace std;
int n,w,m,a[1000001],r=0,maxx=0,t,l;
bool pop[100001];
int pd(int x){//x为mid，就是中间数
    int w=0,j=0;//w为放过的石块，j为第i个石块的上一个石块
    for(int i=1;i<=n+1;i++){
        if(a[i]-a[j]<x){//如果上一个石块小于最小值则要让它变大
            w++;//石块数++
        }
        else{
            j=i;//下一块石头的上一块是他
        }
    }
    return w<=m;//判断有没有大于规定
}
int main()
{
    cin>>t>>n>>m;//输入 
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    sort(a,a+n+1);//排序，排序，排序！！！ 
    r=t+1;//规定边界，加一让以后不用特判终点的石头的情况 
    a[n+1]=t;//这样方便终点的石头调用 
    while(l+1<r){//规定 
        int mid=l+(r-l)/2;//创建中间数（整形除以整形会自动取整） 
        if(pd(mid)==true){//如果判断为真 
            l=mid;//还可以继续放石头 
        }
        else{//如果为假 
            r=mid;//少几块石头 
        }
    }
    cout<<l;//输出最小值就可以了 
    return 0;//结束了！ 
}
```


------------

好了，我们来总结一下二分的步骤：
1:初始化边界，判断边界是干什么的，我们要求什么

2：判断循环存在条件

3：判断边界变化方式

这样，一道二分的题就基本做完了！


---

## 作者：yuyer (赞：6)

# 经典的二分答案+贪心
## 思路如下：
#### 1. 由于n是中间的石头数，并未包含终点的石头，所以要加入到距离队列中。
#### 2. 由于二分的数组需要有序，所以需要用sort排好。
#### 3. 二分距离（或者说是枚举距离，只不过不是顺序枚举罢了）。因为答案在二分的左侧（较小数中的最大值），所以需要及时记录答案（即mid）。
#### 4. 判断函数：统计出当距离为s时总共需要移走几个石头。具体思路用到贪心，详见注释。有两种写法：一个是直接统计出需要移走的数量，一个是先统计留下来的石头的总数，再在return时用总数来算出移走的数量。
### 判断函数1：

```cpp
int check(int s)//s是猜测的距离
{
	int j=0,c=0;//j是上一个留下的石头的位置（距离）
	for(int i=1;i<=n;i++)
	if(a[i]-a[j]>=s)//到达上一个石头的距离足够了
	{
		c++;//计数
		j=i;//更新上一个石头的位置
	}
	return n-c;//先求留下的数量
}
```
### 判断函数2：

```cpp
int check(int s)
{
	int j=0,c=0;//同上
	for(int i=1;i<=n;i++)//距离达不到要求的距离，就需要去除
	if(a[i]-a[j]<s) c++;
	else j=i;//达到要求距离，更新石头位置
	return c;//直接求去除的数量
}
```
### 主程序：

```cpp
#include<cstdio>
#include<algorithm>
#define MAXN 50005
int a[MAXN]={0};
using namespace std;
int l,m,n,ans=0;
int main()
{
	scanf("%d%d%d",&l,&n,&m);
	for(int i=1;i<=n;i++)
	scanf("%d",&a[i]);
	a[++n]=l;//记录终点 
	sort(a+1,a+n+1);//记得排序
	int mid,tl=1,tr=l;//二分初始化
	while(tl<=tr)
	{
		mid=(tl+tr)/2;
		if(check(mid)<=m)//满足条件
		{
			ans=mid;//记录答案（有人会说要求最大的满足条件的数，需要单独判断，其实是二分没有理解透彻。在这个二分中，最后求出的ans绝对是最大的。
			tl=mid+1;
		}
		else tr=mid-1;
	}
	printf("%d\n",ans);
	return 0;
}
```

~~同学们只需要把check函数带入到主程序中就可以了。~~

**该程序仅供参考，希望大家能够理解并AC。**

---

## 作者：codeboyzzb (赞：5)



------------
     **P2855 [USACO06DEC]河跳房子River Hopscotch 题解**
------------
直接上代码吧,解析见代码
```cpp
/************************************************ 
                    18\02\19 12:02
                       二分算法 
************************************************/ 
#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN = 1e6+5;
int l,n,m;
int a[MAXN];
int BinarySearch(int l,int r) //二分模板,二分出:答案 
{
	while(l + 1 <r)   //循环:两个不挨着的时候才执行 
	{
		int mid = (l + r) / 2; //检验区间 
		int cnt = 0;  //定义一个计数器 
		int i =0,j = 0;
		while(i <= n) 
		{
			j = i + 1;
			while(a[j] - a[i] < mid and  j <= n + 1)   //在"mid"这个区间有多少块石头可以消除 
			{
				++ j;
			}
			cnt += j - i- 1;
			i = j;
		}
		if(cnt <= m) l = mid; //判断:如果计数器≤m时,刷新l的数值 
		else r = mid;         //剩下的,刷新r的数值 
	}
	return l;      //返回l 
}
int d[MAXN+5];
using namespace std;
int main()
{
	scanf("%d %d %d",&l,&n,&m);
	if(n==0&&m==0)   //下载数据后发现的坑人数据(*/ω＼*) 
	{
		printf("%d",l);
		return 0;
	}
    for(int i=1;i<=n;i++)
    scanf("%d",&a[i]);
    a[n+1]=l;
    sort(a+1,a+2+n);//排序一下 
    printf("%d",BinarySearch(0,l));//答出答案 
    return 0;
}
```
心得:这道题主要靠的是二分算法,直接筛出答案.
这道题并不是很难,但是要注意几点:


------------

****1:要排序!要排序!要排序!我就是因为没排序错了几遍(*/ω＼*)


------------

****2:要特判!要特判!要特判!OJ上有一组坑人的数据:___ 0 0
0块石头...直接输出长度就可以了


//本人第12次写题解(前面11次都没通过...),望批准!

---

## 作者：syf2008 (赞：4)

请看到最后，有惊喜

题目的意思很简单，就是最多移走m块石头，使得选手跳跃的最短距离最大即可。

这是一道非常好的二分答案题，~~因为他不需要高深的算法~~

简单的思路：从起点出发，先选定一段距离mid，若前面的石头B与你所站着的石头A的距离小于mid，就把B搬掉，记录一下；如果不，就把B留下，再跳到石头B上。照这个步骤多次循环后，如果搬掉的石头多了，就把距离mid定小点；如果少了，就把mid定大点。

上代码
```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int ss,n,m,mid,now,a[50005],s,ans;
	cin>>ss>>n>>m;
	for(int i=1;i<=n;i++)
	cin>>a[i];
	sort(a+1,a+n+1);
	int l=0,r=ss;
	while(l<=r)
	{
	mid=r+l>>1;
	now=0;s=0;
	for(int i=1;i<=n;i++)
	if(a[i]-a[now]<mid)
	s++;
else now=i;
	if(s<=m)
	{ans=mid;
	l=mid+1;}
else r=mid-1;}
	cout<<ans;
	return 0;
}
```
惊喜来了
[双倍经验（把sort去掉就能过）](https://www.luogu.com.cn/problem/P2678)

---

## 作者：做梦想Peach (赞：1)

####  因为题目求最小值最大，显然就是二分。 二分最小值最大距离，然后贪心处理。

这里我们在头尾各增加一个石头，贪心时先从第一个石头开始记为$\text l$，然后往后扫描，当前扫描的石头记为$\text r$，如果 $a[r]-a[l]<mid$的话，就说明$\text l,\text r$中间的石头就算都移走都不能满足最小值最大为$mid$，所以我们一直往后找，找到一个
$a[r]$−$a[l]$ $\geq$ $mid$
时停下来，移掉中间的所有石头数$r-l-1$，之后和$\text m$比较即可。

我们来看看简单滴代码吧，请不要埋怨窝奇怪滴马蜂。![/kk](https://cdn.luogu.com.cn/upload/image_hosting/y609uyc8.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

```cpp
#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;//这系头文件。
int L,M,N,a[50010],mid,i,left,right;//定义变量，left、mid、right就是二分中的左、中、右。
bool judge (int x) {
	int dis=0,i,num=0;
	for (i=1;i<=N;i++) {
		if (a[i]-dis<x)//如果上一个石块小于最小值则要让它变大 
			num++;//记录有多少石块。
		else 	
			dis=a[i];//dis记录上一块石头。
	}
	if (L-dis<x) num++;
	return num<=M;//判断是否可取。
}
int main () {
	scanf ("%d%d%d",&L,&N,&M);
	for (i=1;i<=N;i++) scanf ("%d",&a[i]);//读入。
	sort (a+1,a+N+1);//贪心思想。
	left=0,right=L;//左端点，右端点。
	if (M==0) {//如果M是0的话，那就直接输出L了。
		printf ("%d\n",L);
		return 0;
	}
	while (left+1<right) {//普通的二分。
		mid=(left+right)/2;
		if (judge(mid)) 
			left=mid;
		else
			right=mid;
	}
	printf ("%d\n",left);//输出答案。
	return 0;
}
```
#### 这就结束啦。是一道不错滴二分练习题，886![886](https://cdn.luogu.com.cn/upload/image_hosting/eelk6mg4.png?x-oss-process=image/resize,m_lfit,h_170,w_225)。

---

## 作者：CJHGOD (赞：1)

[原题传送门](https://www.luogu.org/problem/P2678)

我那道题的代码是这样的

```cpp
#pragma GCC optimize(3)
#include<bits/stdc++.h>
using namespace std;
int n,m,l,a[50005];
int check(int x){
    int s=0,k=0,mid=0;
    //s是移走的石头数，mid是位置
    while (k<n+1){
        k++;
        if (x>a[k]-a[mid])s++;//哦，距离满足，搬一块石头
        else mid=k;
    }
    if(s>m)return 1;
    else return 0;
}
int main(){
	int ans;
	cin>>l>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	a[n+1]=l;//重点
	int left=0,right=INT_MAX;
	while (left<=right){
		int mid;
		mid=(left+right)/2;
		if(!check(mid)){
			ans=mid;left=mid+1;
		}
		else right=mid-1;
	}//经典二分，不予解释
	cout<<ans;
	return 0；
}
```

# ~~# 细心的oier会发现：原题的数据是有序的，这里是无序的，所以只要再加上一行代码：~~

sort(a+1,a+n+2);//有n+1个数据

---

## 作者：BBD186587 (赞：1)

# 标准二分答案
## 这题要排序！要排序！要排序！
其余就没什么可讲的了，直接上代码~
```cpp
#include<algorithm>
#include<iostream>
#include<cstdio>
using namespace std;
long long l,n,m,i,a[100010];
bool check(int x)//主要
{
	int s=0,cnt=0;
	for(i=1;i<=n+1;i++)
	{
		s+=a[i]-a[i-1];
		if(s>=x) s=0;
		else cnt++;
	}
	return cnt<=m;
}
int main()
{
	scanf("%lld%lld%lld",&l,&n,&m);
	for(i=1;i<=n;i++) scanf("%lld",&a[i]);
	sort(a+1,a+n+1);
	a[0]=0,a[n+1]=l;
	int left=0,right=l,mid;
	while(left<right)//标准二分
	{
		mid=(left+right)/2;
		if(check(mid+1)) left=mid+1;
		else right=mid;
	}
	cout<<right;
	return 0;
}
```


---

## 作者：doby (赞：1)

考试时没人ac，原来题目上写错了，原来是不按顺序给的

怪不得wly,xfy,lyh,yyy几位大佬都没ac……

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int l,n,m,d[50009],lef=233333333,rig,mid,sum,last;
int check(int s)
{
    sum=0,last=0;
    for(int i=1;i<n;i++)//贪心证明
    {
        if(d[i]-last<s){sum++;continue;}
        last=d[i];
    }
    if(sum>m){return 0;}//不说了，很好理解……
    else{return 1;}
}
int main()
{
    scanf("%d%d%d",&l,&n,&m);
    n++,d[n]=l,rig=l;//把最后也加入石头数组
    for(int i=1;i<=n-1;i++){scanf("%d",&d[i]);}
    sort(d+1,d+n+1);//排序
    for(int i=1;i<=n;i++){if(d[i]-d[i-1]<lef){lef=d[i]-d[i-1];}}
    while(lef+1<rig)//二分
    {
        mid=(lef+rig)/2;
        if(check(mid)){lef=mid;}
        else{rig=mid;}
    }
    if(check(rig)){printf("%d",rig);return 0;}//强化的判断，因为不好确定……
    printf("%d",lef);
    return 0;
}
```

---

## 作者：南橙未熟k (赞：1)

看到题解中一堆c++大佬，我知道本人只是个pascal蒟蒻，~~但没关系，直接上啊（有点不要脸）~~
好了，废话少说，来讲一下这道题的思路。
### 首先，我们知道这道题的范围会比较大，如果直接暴力会超时，那么我们自然就想到了二分答案。
#### 1、二分必定要使数组有序排列，我们直接~~偷个~~快排就没事了
#### 2、我们二分的是距离，且是最小距离，我们可以分段，若当前距离需要移走的石头大于可以移走的石头，就不能继续二分下去



------------
```pascal
var l,n,m,i,t,w,mid,max:longint;
    a:array[0..100001] of longint;
 procedure sort(l,r: longint);//这里是快排，对a数组进行排序
      var
         i,j,x,y: longint;
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
      end;
function pd(mid:longint):boolean;//函数用来判断当前距离是否可行
var s,t,i:longint;
begin
  s:=0;t:=0;
  for i:=1 to n+1 do
    if a[i]-s<mid then
    begin
      t:=t+1;
      if t>m then exit(false);
    end
    else s:=a[i];
  exit(true);
end;
begin
  readln(l,n,m);
  a[0]:=0;a[n+1]:=l;//进行范围限制
  for i:=1 to n do
    readln(a[i]);//读入石头的距离
  sort(1,n);
  t:=0;w:=l;//开始二分，t和w表示距离范围
  while t<=w do
  begin
    mid:=(t+w) div 2;
    if pd(mid) then//若可行则记录当前距离，前指针=mid+1
    begin
      max:=mid;
      t:=mid+1;
    end
    else w:=mid-1;//若不行，则后指针=mid-1
  end;
  writeln(max);//输出
end.
```


------------
以上就是本人的思路和算法，~~代码巨丑，大佬勿喷，QWQ~~，谢谢

---

## 作者：RainFestival (赞：1)

明天要期末考试啦，我来写一篇题解

此题最简单的想法是直接枚举

我们枚举答案

从1到l

但绝对会超时TLE

但是结果是单调的，所以可以

## 二分答案

什么叫二分答案？？？？？？

自己百度^_^

推荐几道题（他们都是类似的二分答案）

[P1824](https://www.luogu.org/problemnew/show/P1824)
[P1316](https://www.luogu.org/problemnew/show/P1316)
[P2855](https://www.luogu.org/problemnew/show/P2855)
[P2678](https://www.luogu.org/problemnew/show/P2678)

下面是代码：

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int l,m,n;
int a[1000005];
bool check(int k)
{
    int p=0,q=0;
    for (int i=1;i<=n;i++)
      if (q+k>a[i]) p++;
      else q=a[i];
    if (p>m) return false;
    else return true;
}
void erfen(int l,int r)
{
    if (l==r)
    {
        cout<<l<<endl;
        return;
    }
    int mid=(l+r+1)/2;
    if (check(mid)) erfen(mid,r);
    else erfen(1,mid-1);
}
int main()
{
    cin>>l>>n>>m;
    for (int i=1;i<=n;i++)
      cin>>a[i];
    sort(a+1,a+n+1);
    erfen(1,l);
      
}
```

时间132ms, 空间2844KB，代码长度0.56KB

总比直接枚举好多了

谢谢巨巨巨佬与大大大佬们的观看！！！

---

## 作者：谭之荔 (赞：0)

#### 不多说，已经在程序中标记好了嘛
```cpp
#include<bits/stdc++.h>//咳咳，懒癌晚期 
using namespace std;

int ri[50003];//ri[i]表示第i个石子的位置 

int main()
{
	ios::sync_with_stdio(false);//加速cin cout 
	int l,r;//l r分别是二分中的左右 
	int ll,n,m; //ll是总长度，n是总石子，m是能删几个石子 
	cin>>ll>>n>>m;
	for(int i=1;i<=n;i++) cin>>ri[i];
	sort(ri+1,ri+1+n);//一定要排序，因为给出的数据不一定是按顺序来的，可能是第1个石子在23上，第2个在5上 
	ri[0]=0;//起点石子 
	ri[n+1]=ll;//终点石子 
	l=0;
	r=ll+1;
	int ans;//ans是每种情况中删除的石子数，算完后需与m相比 
	int i,j;//i j分别是第i j个石子，若第i和j间的距离<mid 就需要换下一个j，直到i j间距离>=m 
	while(l+1<r)//保证l位置和r位置间有石子 
	{
		int mid=(l+r)>>1; 
		ans=0;i=0;//记得赋初值 
		while(i<=n) 
		{
			j=i+1;
			while(ri[j]-ri[i]<mid&&j<n+1) j++;
			ans+=j-i-1;//ans是到当前位置共删除的
			//!!!这里与某些方法不同，这里是将i和j之间的石子一起删除 
			i=j;//i从j的位置继续找 
		}
		if(ans<=m) l=mid;//相等时也需继续，因为可能同样删除m个，距离可能更大 
		else r=mid;
	}
	cout<<l;
}
```


---

## 作者：墨舞灵纯 (赞：0)

    我的第三篇题解。（请大佬们多指教。当然，如果有看不懂的地方欢迎和我私信交流。）       
    从题目描述我们可以看出，此题是求最大最小值，即在条件成立(f(x)<=m)下最小的距离，对于此类问题，显然是二分答案求解：解的上下界确定(l=0,r=L),可以写出判断条件(f(x)<=m),解具有区间单调性(在某个值之前条件都成立，之后都不成立)。所以，我们可以通过样例去分析，写出判断条件，从而求解。
    所以，判断函数便很容易写出：
    bool check(int x){
	int i,last=0,k=0;//k表示当前除去的石头的数量，last表示上一个石头的位置
	for(i=1;i<=n;i++){
		if(a[i]-last<x)//当前石头与上一个石头的距离差小于最小距离x
			++k;//除去当前的石头
		else last=a[i];//不用除去石头，更新上一个石头的位置
	}
	return k<=m;//条件是否成立，成立返回真
    }
    既然判断函数已经写出，再套用二分模板即可：
	int midsearch(){
		int l,r;
		l=0;r=L;
		while(l<=r){
			int mid=(l+r)/2;
			if(check(mid))
				l=mid+1;
			else r=mid-1;
		}
		return r;
	}
    主函数如下：
    int main(){
        scanf("%d%d%d",&L,&n,&m);
       //细节提示:L,n,m为全局变量
        int i;
        for(i=1;i<=n;i++){
                scanf("%d",&a[i]);
        }
        a[++n]=L;
        sort(a+1,a+1+n);
        printf(“%d”,midsearch());
        return 0;
    }



---

## 作者：zhm411821 (赞：0)

noip2015 day2 T1

也是当年从OPEN JUDGE中选取的题目之一

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int la,n,m,ans,a[50010],l,r,mi;
int work(int x){//判断使最大距离为x时，是否去掉m块石头
    int k=0,num=0;
    for(int i=1;i<=n+1;i++){
        if(a[i]-a[num]<x){//如果两石块之间距离小于目标，则去掉后一个
            k++;
            if(k>m)
                return 0;
        }
        else
            num=i;//如果两石块间距离满足目标，则将标记指向第二块
        }
    return 1;
}
int main(){
    cin>>la>>n>>m;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    a[n+1]=la;
    sort(a+1,a+n+1);
    r=la;
    while(l<=r){//二分枚举可能的最大距离
        mi=(r-l)/2+l;
        if(work(mi)){
            ans=mi;
            l=mi+1;
        }
        else
            r=mi-1;
    }
    cout<<ans;
    return 0;
}

---

## 作者：NishikinoMaki (赞：0)

        
```cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#define nmax 100100
using namespace std;
unsigned long long l,r,mid,n,m,L[nmax],LL[nmax],LLL[nmax],tot;//字头；
bool can(int x){
    tot=0;//tot表移走石头的个数；
    for(int i=1;i<=n+1;i++)   LLL[i]=LL[i];//把LL数组复制到LLL数组里；
    for(int i=1;i<=n+1;i++){
        if(LLL[i]<x){//一段距离小于最小值了；
            tot++;LLL[i+1]+=LLL[i];//移走一段石头；
        }
    }
    return tot<=m;//看一共移走的石头和m谁大；
}
int main(){
    cin>>r>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>L[i];
    }
    sort(L+1,L+n+1);//先排序（不排序只ac10分，我第一次就这么死的）
    for(int i=1;i<=n;i++){
LL[i]=L[i]-L[i-1];//LL表两块石头间的距离，是不能变的，这就是为什么can函数里要再用一个LLL数组；
    }
    LL[n+1]=r-L[n];有n块石头，就有n+1段距离；
    while(l+1<r){//开始无脑二分；
        mid=(l+r)/2;
        if(can(mid)){//如果这是一个最小值；
            l=mid;//就去比他大的数里再找；
        }
        else{
            r=mid;//反之；
        }
    }
    if(can(r)) cout<<r;
    else cout<<l;//一个莫名其妙的判断；因为我忘了要输出l还是r了；好像不同的数据是不一样的；（尴尬）
    return 0;
}//以上；
```

---

## 作者：Coco_T (赞：0)

主体思想是二分查找最大跳跃最短距离，然后进行验证，看看在该查找情况下，需要移走的石头数是否等于m






```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int l,n,m;
int a[5000010];
int doit(int le,int ri)
{
    int tot,mid,i,x;
    while (le+1<ri)   //如果写成了le<ri或le<=ri会T。。。  
    {
        tot=0;
        x=0;
        mid=(le+ri)/2;
        i=0;
        while (i<=n)
        {
            x=i+1;                         //从当前石头开始，依次往后 
            while (a[x]-a[i]<mid&&x<=n)    //如果这两个石头之间的距离大于mid，x++ 
                  x++;                     //至于tot为什么这么加，大家自己体会一下就懂了 
            tot+=x-i-1;
            i=x;
        }
        if (tot>m)  //需要移走的石头数大于m，二分查找的距离太大 
           ri=mid;
        else
           le=mid;  
    }
    return le;
}
int main()
{
    scanf("%d%d%d",&l,&n,&m);
    int i;
    for (i=1;i<=n;i++)
        scanf("%d",&a[i]);
    sort(a+1,a+n+1);  //先排序 
    a[n+1]=l;         //不要忘了终点的石头 
    n++;
    printf("%d",doit(0,l+1));  // 这里带入l+1，是为了处理n=m=0的情况，当然，你也可以单独判断，这种情况下答案就是l  
}
```

---

