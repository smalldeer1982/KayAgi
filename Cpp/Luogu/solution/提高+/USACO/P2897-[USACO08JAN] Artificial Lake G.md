# [USACO08JAN] Artificial Lake G

## 题目背景

USACO 2008 January Gold

## 题目描述

The oppressively hot summer days have raised the cows' clamoring to its highest level. Farmer John has finally decided to build an artificial lake. For his engineering studies, he is modeling the lake as a two-dimensional landscape consisting of a contiguous sequence of N soon-to-be-submerged levels (1 ≤ N ≤ 100,000) conveniently numbered 1..N from left to right.


Each level i is described by two integers, its width Wi (1 ≤ Wi ≤ 1,000) and height (like a relative elevation) Hi (1 ≤ Hi ≤ 1,000,000). The heights of FJ's levels are unique. An infinitely tall barrier encloses the lake's model on the left and right. One example lake profile is shown below.

          
```cpp
         *             *  :
         *             *  :
         *             *  8
         *    ***      *  7
         *    ***      *  6
         *    ***      *  5
         *    **********  4 <- height
         *    **********  3
         ***************  2
         ***************  1
Level    |  1 |2|  3   |
```
In FJ's model, he starts filling his lake at sunrise by flowing water into the bottom of the lowest elevation at a rate of 1 square unit of water per minute. The water falls directly downward until it hits something, and then it flows and spreads as room-temperature water always does. As in all good models, assume that falling and flowing happen instantly. Determine the time at which each elevation's becomes submerged by a single unit of water.


```cpp
WATER              WATER OVERFLOWS                     
       |                       |                           
     * |          *      *     |      *      *            *
     * V          *      *     V      *      *            *
     *            *      *    ....    *      *~~~~~~~~~~~~*
     *    **      *      *~~~~** :    *      *~~~~**~~~~~~*
     *    **      *      *~~~~** :    *      *~~~~**~~~~~~*
     *    **      *      *~~~~**~~~~~~*      *~~~~**~~~~~~*
     *    *********      *~~~~*********      *~~~~*********
     *~~~~*********      *~~~~*********      *~~~~*********
     **************      **************      **************
     **************      **************      **************
     After 4 mins        After 26 mins       After 50 mins

     Lvl 1 submerged     Lvl 3 submerged     Lvl 2 submerged
```
Warning: The answer will not always fit in 32 bits.

夏日那让人喘不过气的酷热将奶牛们的烦躁情绪推到了最高点。最终，FJ决定建一个人工湖供奶牛消暑之用。为了使湖看起来更加真实，FJ决定将湖的横截面建成N(1 <= N <= 100,000)个连续的平台高低错落的组合状，所有的平台从左到右按1..N依次编号。当然咯，在湖中注入水后，这些平台都将被淹没。    平台i在设计图上用它的宽度W\_i(1 <= W\_i <= 1,000)和高度（你可以理解为该平台顶离FJ挖的地基的高度）H\_i(1 <= H\_i <= 1,000,000)来描述的。所有平台的高度都是独一无二的。湖的边缘可以视为无限高的平台。下面给出了一张FJ的设计图：


按FJ的设想，在坑挖好后，他会以1单位/分钟的速度往最低的那个平台上注水。水在离开水管后立即下落，直到撞到平台顶或是更早些时候注入的水。然后，与所有常温下的水一样，它会迅速地流动、扩散。简单起见，你可以认为这些都是在瞬间完成的。FJ想知道，对于每一个平台，它的顶部是从哪个时刻开始，与水面的距离至少为1单位长度。


## 样例 #1

### 输入

```
3
4 2
2 7
6 4```

### 输出

```
4
50
26```

# 题解

## 作者：幻·光 (赞：11)

本题题意如下图。
![](https://cdn.luogu.com.cn/upload/image_hosting/nhxpltwd.png)
图中，两边无限高，而$C$最矮，那么就从$C$开始注水，当水位到达$C$两边最矮的那个平台（也就是$B$）顶部时，就注满了，接着开始$C$出栈，$D$移到$B$右边，然后注$B……$（以此类推）。

那么，实际上就是一个单调递减栈。

如果进栈元素比栈顶高，那么栈内比它矮的都先注满，再出来，累加出栈元素的宽度，实现过程如下图。
![](https://cdn.luogu.com.cn/upload/image_hosting/4ter9wgt.png)

那么代码就是下面这样。


```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=1e6+50;
struct pingtai
{
	 long long kuandu;//平台宽度 
	 long long gaodu;//平台高度 
}a[N];
long long ans[N],sta[N][2],tt,temp,minn=100000099,sta1[N];
int main()
{
	long long n,zz=0;
	cin>>n;
	a[0].gaodu=9999999999;//题目说了，两边无限高 
	a[n+1].gaodu=9999999999;//奶牛：我上不来了
	for(long long i=1;i<=n;i++)
	{
		cin>>a[i].kuandu>>a[i].gaodu;
		if(a[i].gaodu<minn)
		{
			minn=a[i].gaodu;//最矮平台
			temp=i;//最矮平台下标 
		}
	} 
	sta1[++tt]=temp;
	long long now=0;//现在所用时间
	long long l=temp-1,r=temp+1;//l:最矮平台左边那个平台的下标；r：最矮平台右边那个平台的下标 
	for(long long i=1;i<=n;i++)
	{
		long long xx,yy;//分别记录高度和宽度
		long long kuan=0;//用来累计宽度
		if(a[l].gaodu<a[r].gaodu)//如果l平台比r平台矮，就该往l平台注水
		{
			xx=a[l].gaodu;
			yy=a[l].kuandu;//统计
			while(tt>0 && a[l].gaodu>a[sta1[tt]].gaodu)//单调递减栈 
			{
				a[sta1[tt]].kuandu+=kuan;
				ans[sta1[tt]]=now+a[sta1[tt]].kuandu;//填满这个地方所需时间就是宽度*1，直接加上宽度就可以了 
				kuan=a[sta1[tt]].kuandu;//加上栈顶宽度 
				now+=(min(a[sta1[tt-1]].gaodu,a[l].gaodu)-a[sta1[tt]].gaodu)*a[sta1[tt]].kuandu;
				tt--;
			}
			a[l].kuandu+=kuan;//进栈平台宽度要加上出栈平台的宽度 
			sta1[++tt]=l;
			l--;//l一直向左移，所以--，r相反 
		} 
		else
		{
			xx=a[r].gaodu;
			yy=a[r].kuandu;//统计
			while(tt>0 && a[r].gaodu>a[sta1[tt]].gaodu)//单调递减栈 
			{
				a[sta1[tt]].kuandu+=kuan;
				ans[sta1[tt]]=now+a[sta1[tt]].kuandu;//填满这个地方所需时间就是宽度*1，直接加上宽度就可以了 
				kuan=a[sta1[tt]].kuandu;//加上栈顶宽度 
				now+=(min(a[sta1[tt-1]].gaodu,a[r].gaodu)-a[sta1[tt]].gaodu)*a[sta1[tt]].kuandu;
				tt--;
			}
			a[r].kuandu+=kuan;//进栈平台宽度要加上出栈平台的宽度 
			sta1[++tt]=r;
			r++; 
		}
	} 
	for(long long i=1;i<=n;i++)
	{
		cout<<ans[i]<<endl;
	}
	return 0;
}

```


---

## 作者：LOVE_Ynoi (赞：6)

## **模拟灌水后合并平台（双向链表）**

**step1**:找到最低的一个平台  
&emsp;(将now与左右比较，向左或向右移动)  

**step2**:记录答案:  
&emsp;"与水面的距离至少为1单位长度",  
&emsp;答案即为:&emsp;**现在的时间 + 现在平台的宽度** 

**step3**:累增时间  
&emsp;累计时间 =  **现在的需要灌水的高度 乘 现在平台的宽度**  
&emsp;现在需要灌水的高度即为   
&emsp;&emsp;**左右平台高度的最小值 - 现在平台的高度**  
&emsp;&emsp;(灌完水即可合并)&nbsp;&nbsp;&nbsp;(不要忘记转换成long long) 

**step4**:删除节点  
&emsp;删除节点很容易 代码如下
```cpp
		nxt[pre[now]] = nxt[now];
		pre[nxt[now]] = pre[now];
```
**step5**:合并高度  
&emsp;找到左边小还是右边小，哪边小，哪边就是合并的对象 把宽度累加起来 

**至此，一轮循环就完成了**  
循环至就剩一个节点，在进行一次step2，就可以输出啦   

### 代码部分：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
//宽
int w[200000];
//高
int h[200000];
//前指针
int pre[200000];
//后指针
int nxt[200000];
//现在处理的平台
int now;
//现在的时间
long long t;
//答案
long long ans[200000];

int main() {
	/********* init 读数***********/
	scanf("%d", &n);
        //高墙
	h[0] = h[n + 1] = 0x7f7f7f7f;
	for (int i = 1; i <= n; i++) {
		scanf("%d %d", &w[i], &h[i]);
		pre[i] = i - 1;
		nxt[i] = i + 1;
                //寻找最低平台
		if (h[i] < h[now])
			now = i;
	}
	/********* init 读数***********/

	/********* main 主 ************/
	//不是只剩一个节点
	while (pre[now] != 0 || nxt[now] != n + 1) {
		//转移now
		if (h[now] > h[pre[now]]) {
			now = pre[now];
			continue;
		}
		if (h[now] > h[nxt[now]]) {
			now = nxt[now];
			continue;
		}
		//记录
		ans[now] = t + w[now];
		//累加时间
		t += w[now] * 1ll * ( min( h[pre[now]], h[nxt[now]] ) - h[now] );
		//合并节点
		nxt[pre[now]] = nxt[now], pre[nxt[now]] = pre[now];
		//合并高度
		if (h[pre[now]] > h[nxt[now]])
			w[nxt[now]] = w[now] + w[nxt[now]], now = nxt[now];
		else
			w[pre[now]] = w[now] + w[pre[now]], now = pre[now];
	}
	/********* main 主 ************/

	/********* output 输出************/
	ans[now] = t + w[now];
	for (int i = 1; i <= n; i++)
		printf("%lld\n", ans[i]);
	/********* output 输出************/
	return 0;
}
```

---

## 作者：巨型方块 (赞：6)

栈？
算了，直接暴力好了

建一个双向链表；

从k点开始暴力

k点完了吧k点从链表里删掉；

然后左右找一个比较小的高度继续模拟；

如果k点左右有比k低的那么先去搞低的

代码删掉了io优化

```cpp
#include<bits/stdc++.h>
#define Ll long long
using namespace std;
const int N=1e5+5;
struct cs{int x,y,w,h;Ll v;}a[N];
int n,m,k;
Ll now;
int main()
{
    n=RR();
    for(int i=1;i<=n;i++){
        read(a[i].w,a[i].h);
        a[i].x=i-1;
        a[i].y=i+1;
        if(!k||a[k].h>a[i].h)k=i;
    }
    a[0].h=a[n+1].h=1e9;
    while(a[k].x!=0||a[k].y!=n+1){
        if(a[k].h>a[a[k].x].h){k=a[k].x;continue;}
        if(a[k].h>a[a[k].y].h){k=a[k].y;continue;}
        int h=min(a[a[k].x].h,a[a[k].y].h)-a[k].h;
        a[k].v=now+a[k].w;now=now+1ll*a[k].w*h;
        a[a[k].x].y=a[k].y;a[a[k].y].x=a[k].x;
        if(a[a[k].x].h>a[a[k].y].h)
            a[a[k].y].w+=a[k].w,k=a[k].y;
        else a[a[k].x].w+=a[k].w,k=a[k].x;
    }
    a[k].v=now+a[k].w;
    for(int i=1;i<=n;i++)WW(a[i].v);
}
```

---

## 作者：zhaozejian (赞：5)

# 题解 P2897 [USACO08JAN] Artificial Lake G
[题目传送门](https://www.luogu.com.cn/problem/P2897)

## 这是一道单调栈  
FJ 是从最矮的台阶开始注水的，且水往低处流。

假设我们在对第 $k$ 个台阶注水（其他满了水就会流过去，相当于对第 $k$ 个台阶注水）,如果第 $k+1$ 个比它矮，那么就相当于对第 $k+1$ 个台阶注水；如果第 $k+1$ 个比它高，那么我们就可以开始计算第 $k$ 个台阶注水时间：**当前总时间 $+$ 宽度 $\times 1$（$1$ 秒时间去覆盖）**。

如果发现下一个比当前矮，就去检测下一个，否则计算答案，再检测下一个。

如果发现下一个比当前小，就把下一个加进来，否则计算，答案再把下一个加进来。

咦？像不像一个**单调递减栈**？

这样想就简单多了，维护一个单调递减栈，一旦遇到比当前高的就计算一次（遇到比当前高的水才不会流走）并记录下来，弹出后加入这个新来的。

## 如何计算时间呢？
 ~~与作者而言，这是个大问题。~~
 
图有点简陋，勿喷qwq。
```cpp
/*
土              土
土土        土  土
土土空  土  土  土
土土空  土  土  土
土土土  土土土土土
土土土  土土土土土
土土土土土土土土土
土土土土土土土土土
1 2 3 4 5 6 7 8 9
*/
```
从 $4$ 号开始灌，为了方便，我们把 $4$ 号灌到一定高度后与相邻的柱子合并在一起。

和谁合并呢？很显然是 $3$ 号，因为和 $5$ 号合并的话，图中标记“空”的地方无法计算。所以与相邻的两个柱子中最矮的那个合并。

所以，结束了！！！
## 代码（带注释讲解）
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,minn=1000005,mini;
long long ans[100005];//不开long long见祖宗啊
struct S{
	long long w,h;//h为高度，w为宽度 
};
S s[100005];
stack<int>q;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&s[i].w,&s[i].h);
		if(minn>s[i].h)
		{
			minn=s[i].h;//找最小值 
			mini=i;//找最小值的坐标 
		}
	}
	s[0].h=s[n+1].h=1000005;//建立两个无限高的岸边 
	int l=mini-1,r=mini+1,f=0;
	long long t=0;
	q.push(mini);
	for(int i=1;i<=n;i++)
	{
		if(s[l].h<s[r].h)f=l--;//水向低处流，f确定向左还是向右
		else f=r++;
		long long o=0;
		while(!q.empty()&&s[f].h>=s[q.top()].h)//单调递减栈 
		{
			int u=q.top();
			q.pop();
			int uu=0;
			if(!q.empty())uu=q.top();//uu是栈的第二个元素（数组模拟栈就不用这么大费周章了）
			q.push(u);
			o+=s[q.top()].w;//计算宽度 
			ans[q.top()]=t+o;//该柱子覆盖时间=当前总时间+宽度*1（1秒时间去覆盖）
			t+=(min(s[f].h,s[uu].h)-s[q.top()].h)*o;//总时间的计算，覆盖到 栈的第二个元素（比栈顶高且与栈顶相邻）与目标f 中更矮的一个的高度 
			//上面那一行就是长*宽 
			q.pop();//出栈 
		}
		q.push(f);//把目标入栈 
		s[f].w+=o;//合并宽度 
	}
	for(int i=1;i<=n;i++)
	{
		printf("%lld\n",ans[i]);//愉快输出awa
	}
	return 0;
}
```

---

## 作者：zengzidi (赞：3)

审核大大晚上好，这是我的第一篇题解，求过。
### 思路
 从最低的地方开始灌水，灌到两边最低的高度，相当于模拟他的灌水过程，通过维护一个递减单调栈，当当前的高度比上一个高，就往上一个灌水，上一个灌到上上个的高度再往上上个灌，以此类推。上升到隔壁所要的体积是 $\text{要上升的高度（即高度差）} \times \text{这几个的宽度} $。
```cpp
#include<bits/stdc++.h>
#define int long long//方便的定long long 
using namespace std;
int a[100005],b[100005],c[100005],d,e,f,g,h,k,l,m,n,o,r,s,t,u,v,w,x,y,z;//独特的马蜂 
stack<int>p;
int qq()//奇特的函数名，用来返回栈顶第二个的位置 
{
	int oo,uu;
	oo=p.top();
	p.pop();
	if(!p.empty())//如果不判就会爆炸 因为栈可能只有一个元素，无法top 
	{
		uu=p.top();
		p.push(oo);
		return uu;
	}
	p.push(oo);
	return 0;
}
signed main()
{
	cin>>n;
	a[0]=1e9,a[n+1]=1e9;
	for(int i=1;i<=n;i++)
	{
		cin>>b[i]>>a[i];
		if(a[i]<a[t])t=i;//以最低的位置来做起始位置 
	}
	l=t-1,r=t+1;//左右指针
	p.push(t);
	for(int i=1;i<=n;i++)
	{
		o=0;
		if(a[l]<a[r])u=l--;
		else u=r++;//向比较小的移动 
		while(!p.empty() && a[u]>a[p.top()])//维护一个递减的栈 
		{
			o+=b[p.top()];//增加一单位高度所需注水的体积  把栈顶的的现在的合并 
			c[p.top()]=h+o;//h是完成之前的时间 加上o是让他有1单位的水 
			h+=(min(a[u],a[qq()])-a[p.top()])*o;//更新时间，让栈顶的水升到新的高度或上一个的高度 
			p.pop();//出栈 
		}
		p.push(u);//入栈 
		b[u]+=o;
	}
	for(int i=1;i<=n;i++)cout<<c[i]<<endl;
	return 0;
}//由于我独特的马蜂，不推荐多看，理解就行了 
```

---

## 作者：__sxx (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/P2897)
# 题意
给出 $n$ 个平台的高度和宽度，每秒向最低的平台注水 $1$ 单位，它会迅速地流动、扩散。简单起见，你可以认为这些都是在瞬间完成的。最后问每个平台的顶部被水面完全覆盖的时间（要比平台高度高 $1$ 单位长度）。
## 思路
利用单调栈。从最低处开始灌水，灌满后继续向两边较小高度平台灌水。在每次的单调栈中，记录总宽度，总时间加上与旁边最小高度差的乘积，当前时间为之前的总时间加宽度。
## 注意
**要将边界赋值为极大值，同时要开 long long！**
## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,h[100005],w[100005],mi,ans[100005],sum;
stack<int>q;
signed main()
{
   cin>>n;  
   h[0]=h[n+1]=1e18;
   for(int i=1;i<=n;i++)
   {
   	  cin>>w[i]>>h[i];
   	  if(h[mi]>h[i])mi=i;//找到最低的
   }
   int l=mi-1,r=mi+1,p,s;//枚举哪个入单调栈
   q.push(mi);//将最低的入栈
   for(int i=1;i<=n;i++)
   {
   	  s=0;
   	  if(h[l]<h[r])p=l--;//找到对哪个进行入单调栈
   	  else p=r++;
   	  while(!q.empty()&&h[p]>h[q.top()])//单调栈，找出那些小于当前高度的
   	  {
   	  	int u=q.top();
		    q.pop();
   	  	s+=w[u];//累加宽度
   	  	ans[u]=sum+s;//当前时间
   	  	int o;
   	  	if(q.empty()) o=0;
   	  	else o=q.top();
   	  	sum+=(min(h[p],h[o])-h[u])*s;//总时间
	  }
	  q.push(p);//加入单调栈
	  w[p]+=s;//因为比它低还在附近的都注水到了这个高度，所以当前宽度也累加
   }
   for(int i=1;i<=n;i++)cout<<ans[i]<<"\n";
  return 0;
}

```

---

## 作者：狸初 (赞：3)

```cpp
#include "stdio.h"
#include "string.h"
#include "iostream"
#include "algorithm"
#define N 101000
#define inf 0x3f3f3f3f
using namespace std;
struct Pool
{
    long long w;
    int h,id;
    Pool(long long _w=0,int _h=0,int _id=0):w(_w),h(_h),id(_id){}
}pool[N],stk[N];
int top,n;
long long ans[N],now;
int main()
{
    int i;
    int temp=inf,id;
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    {
        scanf("%lld%d",&pool[i].w,&pool[i].h);
        pool[i].id=i;
        if(temp>pool[i].h)
            temp=pool[i].h,id=i;
    }
    stk[++top]=pool[id];
    stk[0].h=inf;
    int l=id,r=id,p;
    pool[0].h=pool[n+1].h=inf;
    for(int rn=1;rn<=n;rn++)
    {
        long long add=0;
        if(pool[l-1].h<pool[r+1].h)
            p=--l;
        else
            p=++r;
        while(pool[p].h>stk[top].h&&top)
        {
            stk[top].w+=add;
            ans[stk[top].id]=now+stk[top].w;
            now+=stk[top].w*(min(pool[p].h,stk[top-1].h)-stk[top].h);
            add=stk[top].w;
            top--;
        }
        pool[p].w+=add;
        stk[++top]=pool[p];
    }
    for(i=1;i<=n;i++)
        printf("%lld\n",ans[i]);
    return 0;
}
```
这题就是模拟从最低的平台注水，然后将最低的填满以后从最低的平台向两边扩展，每次找最近的最低的平台h，然后将水填到h高度。
栈里存的是向外扩展的时候，有时会遇到高度递减的情况，这时并不能填水，但要把这些高度都递减（即扩展时的顺序）记录进栈，然后遇到一个比比水面高的平台h时，模拟倒水，水会挨个淹没最低的平台，即需要从栈顶一个一个出战计算淹没时间，直至栈顶平台高度>h，此时h入栈。重复执行就可算出答案


---

## 作者：ifxxx (赞：2)

从最矮的位置注水，意味着我们无需考虑左右都矮于自己的情况。

此时开始一个个模拟注水。

## 实现步骤

### 寻找灌水位置

在所有水可以流到的地方中，找到未被灌溉且最小的。

### 灌满时间

发现如果一个位置左右的与其同高（被灌满成同样的高度），那么在灌输其时会将它左右也同时被灌输。

加答案时记得要加上左右宽度。

### 灌输高度

当灌输到左右两边中更矮的即可，这时又可以覆盖至另一个。

不断重复上面操作，直到溢出水池（超出左右边界极限）即可。

## Code:

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int kmaxn=1e5+10;
int n,h[kmaxn],w[kmaxn],an[kmaxn],now,l[kmaxn],r[kmaxn],sem;
void eras(int x){
  l[r[x]]=l[x];
  r[l[x]]=r[x];
  return ;
}
signed main(){
  ios::sync_with_stdio(false);
  cin.tie(0);cout.tie(0);
  cin>>n;
  int ba=1;
  for(int i=1;i<=n;i++){
    cin>>w[i]>>h[i];
    l[i]=i-1,r[i]=i+1;
    if(h[i]<h[ba])ba=i;
  }
  sem=ba;
  h[0]=INT_MAX,h[n+1]=INT_MAX;
  while(sem<=n&&sem>=1){
    if(h[l[sem]]<h[sem]){
      sem=l[sem];
      continue;
    }
    if(h[r[sem]]<h[sem]){
      sem=r[sem];
      continue;
    }
    an[sem]=w[sem]+now;
    now=now+w[sem]*(min(h[l[sem]],h[r[sem]])-h[sem]);
    eras(sem);
    if(h[r[sem]]<h[l[sem]]){
      w[r[sem]]+=w[sem];
      sem=r[sem];
    }else{
      w[l[sem]]+=w[sem];
      sem=l[sem];
    }
  }
  for(int i=1;i<=n;i++)cout<<an[i]<<" \n";
  return 0;
}


```


---

## 作者：lihaoda0120 (赞：2)

# 思路

我们研究几个小样例就会发现，灌水的过程和单调栈很像。

于是我们可以利用一个单调递减栈模拟湖的灌水，初始时从最矮的平台开始向两边灌水，每次灌两边更小的那个平台，每次有一个新的平台时，先合并会在它前面被淹的平台（即高度小于它的），并计算被合并平台的答案，再把它入栈。

# 代码

```cpp
#include<bits/stdc++.h>
#define fre(name) freopen(name".in","r",stdin),freopen(name".out","w",stdout)
#define int long long
#define psb push_back
#define pii pair<int,int>
#define ppb pop_back
#define fi first
#define se second
#define endl '\n'
using namespace std;
const int N=1e5+5;
int n,w[N],h[N],top,ans[N],now;
pii st[N];
void push(int id){
	int lw=0;
	while(top&&h[st[top].fi]<h[id]){
		lw+=st[top].se;
		ans[st[top].fi]=now+lw;
		int lst=h[st[top--].fi];
		now+=lw*(min(h[id],h[st[top].fi])-lst);
	}
	st[++top]={id,lw+w[id]};
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	int mi=1e9,id=0;
	for(int i=1;i<=n;i++){
		cin>>w[i]>>h[i];
		if(mi>h[i])id=i,mi=h[i];
	}
	h[0]=h[n+1]=1e9;
	int l=id,r=id;
	push(id);
	for(int i=1;i<n;i++)push(h[l-1]<h[r+1]?--l:++r);
	push(0);
	for(int i=1;i<=n;i++)cout<<ans[i]<<endl;
	return 0;
}
```

---

## 作者：_EternalRegrets_ (赞：1)

## P2897 题解

### 题意描述：

>有一个人工湖，它可以被划分为 $n$ 个平台，已知平台的高度和宽度。
从人工湖的最低平台上方开始注水，水会自然流动（假设瞬间流动）。
求各个平台被覆盖（被浸没至少 $1$ 单位高度）的时间。



---

### Solution:

这里可以使用链表，将相邻的平台链接起来。（链表可以表示左右的关系）

当一个平台被注水，使得与两侧的某一个平台水平（没有同样高度的平台），它们就可以被视为一个大平台。

具体实现方法见代码中注释。

### code:

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

struct node{
	int w,h,l,r;
};

node a[100005];
int ans[100005];

signed main(){
	int n; cin>>n;
	
	int k; k=-1; //寻找最低点；k指的是现在向最低点注水时，相当于向编号为k的平台注水（因为流动）
    for(int i=1;i<=n;i++){
        cin>>a[i].w>>a[i].h;
        a[i].l=i-1,a[i].r=i+1;
        
        if(k==-1 || a[k].h>a[i].h){
        	k=i;
		}
    }
    
    a[0].h=a[n+1].h=LLONG_MAX; //两侧的墙壁
    int now; now=0; //时间
    
    while(a[k].l!=0 || a[k].r!=n+1){
        if(a[k].h>a[a[k].l].h){
			k=a[k].l;
			continue;
		} //如果左侧墙壁比现在的高度要更低，则转移到左侧（此时右侧不可能也比现在的高度低）
		
        if(a[k].h>a[a[k].r].h){
			k=a[k].r;
			continue;
		} //同上，但是对称

        //现在两侧均比现在个高度高
        int nowh; nowh=min(a[a[k].l].h,a[a[k].r].h)-a[k].h;
        ans[k]=now+a[k].w;
        //找到左右边哪个更低，nowh是需要填的高度
		now+=a[k].w*nowh;
    //填充到左右较低侧的高度

//----------------------------------------接链表
		a[a[k].r].l=a[k].l;
        a[a[k].l].r=a[k].r;
		
        if(a[a[k].l].h>a[a[k].r].h){
        	a[a[k].r].w+=a[k].w; //可以视为一个大平台
			k=a[k].r;
		}
        else{ //题目中说明高度不可能相同
        	a[a[k].l].w+=a[k].w; //同上
			k=a[k].l;
		}
    }
//----------------------------------------
    ans[k]=now+a[k].w; //补上最后一层 （此时 a[k].w 等于人工湖的总宽度）

    for(int i=1;i<=n;i++){
		cout<<ans[i]<<endl; 
	}
	
	return 0; //完结撒花！
}
 
```

---

## 作者：Cure_Wing (赞：1)

[P2897 [USACO08JAN] Artificial Lake G](https://www.luogu.com.cn/problem/P2897)

这块地如果没用了，把它填平也许还可以做路。

### 思路

首先第一步大家都会想，就是先找到最低的平台，计算答案，然后把它灌满。第二步呢就是找左右两边比较低的。因为在灌满后水面高度会与两侧较低的平台等高。我们可以看作是把这两个平台合并为一个平台，也就是把这两个平台的宽度合并。虽然我们的水面会到达这个平台，但是如果左边或者右边有更低的平台，水会往左边或右边流下去。于是我们可以暴力查找左右水会流到的最低平台。为了避免平台的合并对之后查询左右位置关系的干扰，我们用双向链表维护平台之间的左右关系。至于为什么暴力搜索是对的，因为如果这一次搜索是从左到右的，说明平台左高右低，水只会从左往右流，而不会从右往左流，于是这个平台只会暴力查找一次，总复杂度为 $O(n)$。

至于统计答案，把每次灌满对应平面（包括合并的平面）所需的时间累加，再把使水面离该平面距离为一的时间（即该平面的宽度）相加即为该平面的答案。

时间复杂度 $O(n)$。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using std::cin;using std::cout;
constexpr int N=100005,inf=1e9;
int n,h[N],l[N],r[N],low=1;
long long w[N],ans[N],tot;
signed main(){
	// freopen("P2897_2.in","r",stdin);
	// freopen("P2897.out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
	cin>>n;w[0]=w[n+1]=1;h[0]=h[n+1]=inf;//特高边界处理
	for(int i=1;i<=n;++i){
		cin>>w[i]>>h[i];l[i]=i-1;r[i]=i+1;
		if(h[i]<h[low]) low=i;//寻找最低平台
	}
	for(int i=1;i<=n;++i){
		ans[low]=tot+w[low];//答案=灌满之前平台+当前的宽度
		tot+=(std::min(h[l[low]],h[r[low]])-h[low])*w[low];//灌满当前平台的总长度，累加答案。
		r[l[low]]=r[low];l[r[low]]=l[low];//合并平台，即取缔该平台的存在
		if(h[l[low]]<h[r[low]]){
			w[l[low]]+=w[low];low=l[low];//向左合并平台
			while(h[l[low]]<h[low]) low=l[low];//向左暴力查询可达最低平台
		}else{
			w[r[low]]+=w[low];low=r[low];//向右合并平台
			while(h[r[low]]<h[low]) low=r[low];//向右暴力查询可达最低平台
		}
	}
	for(int i=1;i<=n;++i) cout<<ans[i]<<'\n';
	return 0;
}
```

---

## 作者：Aisaka_Taiga (赞：1)

[原版](https://www.luogu.com.cn/blog/317872/p2897-ti-xie)

我算是搬运一下，提供另一个用 stack 的版本。

本题的基本思路就是先把两边设成无限高，一个一个进栈，只要再进去的比栈顶元素高就把水注满再把栈顶元素弹出，保证栈内的元素单调递减。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct sb{
	long long kuan,gao;
}a[100010];
long long sum[100010],temp,minn=99999999;
stack<long long>q;
int main()
{
	long long n;
	cin>>n;
	a[0].gao=999999999;
	a[n+1].gao=999999999;
	for(long long i=1;i<=n;i++)
	{
		cin>>a[i].kuan>>a[i].gao;
		if(a[i].gao<minn)
		minn=a[i].gao,temp=i;
	}
	q.push(0);
	q.push(temp);
	long long now=0,l=temp-1,r=temp+1;
	for(long long i=1;i<=n;i++)
	{
		long long xx,yy,kuan1=0;
		if(a[l].gao<a[r].gao)
		{
			xx=a[l].gao;
			yy=a[l].kuan;
			while(!q.empty()&&a[l].gao>a[q.top()].gao)
			{
				a[q.top()].kuan+=kuan1;
				sum[q.top()]=now+a[q.top()].kuan;
				kuan1=a[q.top()].kuan;
				int hhh=q.top();q.pop();
				now+=(min(a[q.top()].gao,a[l].gao)-a[hhh].gao)*a[hhh].kuan;
			}
			a[l].kuan+=kuan1;
			q.push(l);
			l--;
		}
		else
		{
			xx=a[r].gao;
			yy=a[r].kuan;
			while(!q.empty()&&a[r].gao>a[q.top()].gao)
			{
				a[q.top()].kuan+=kuan1;
				sum[q.top()]=now+a[q.top()].kuan;
				kuan1=a[q.top()].kuan;
				int hhh=q.top();q.pop();
				now+=(min(a[q.top()].gao,a[r].gao)-a[hhh].gao)*a[hhh].kuan;
			}
			a[r].kuan+=kuan1;
			q.push(r);
			r++;
		}
	}
	for(long long i=1;i<=n;i++)
	cout<<sum[i]<<endl;
	return 0;
 } 
```

如果原作者觉得不合适可以私信一下，我自己删掉

---

## 作者：A天天t (赞：1)


很好的考验了一个人利用计算机解决实际问题的能力（情景真的很真实，比那些为了考验某个算法和数据结构而胡乱设计的题目（像什么“苹果摘淘淘，傻子合并...”）让人感觉舒服多了~）；

（按照老师的话来说，应该算作一个“模拟”，（“模拟”应该就是说什么就怎么做吧，实际情况是什么样的就怎么做吧~））

考验了一个人把一个能够用人类语言表达的问题转化为机器语言

（一点点的来，真的很简单）


开始说题目

这个题目刚开始有个让我困惑的地方就是水从最低点向两边流动怎么解决

后来想到，可以假设较高的一边为边界，既可以转化为向一边流动的题目

然后等水将要越过边界的时候，就把此时处理的一边作为边界，再去处理另一边

循环往复一直做到两边都到头了就好


至于为什么要使用栈，只是因为，如果平台时递减的，就要先用栈储存下来，等一下再处理（即水要先淹没最低的地方,等低的地方被淹没了，再回来淹没较高的（栈中的平台）；






    

        
    






```cpp
type
int=longint;
const
mn=1000003;
infinite=100000000;
var 
tol:int64; //<10^14
an:array[0..mn]of int64;
z:array[0..mn]of int;
dd,h,w:array[0..mn]of int;
i,j,ml,top:int;
hd,wd,x,n,ans:int;
function min(y,x:int):int;
begin 
if x>y then exit(y) ;
    exit(x);
end;
procedure init;
var i:int;
begin 
    assign(input,'1.in');reset(input);
    readln(n);
    dd[0]:=0;
    ml:=1;
    for i:=1 to n do 
        begin 
            readln(w[i],h[i]);
            dd[i]:=w[i]+dd[i-1];
            if h[i]<h[ml] then 
                begin ml:=i; end;
        end;
end;
//向右扩展时，以左边将要扩展的编号为栈底，
procedure right;
begin 
    z[0]:=i; top:=0; // top:=0; z[top]:=0;    
        repeat 
        while (h[j]<h[z[top]]) do 
            begin     
                inc(top); 
                z[top]:=j;         
                inc(j); // 保证自动向右扩展；
            end;     
        // 栈顶元素即为将要被处理的最低元素
        while (h[z[top]]<h[j])and(top>0) do
            begin 
                x:=z[top]; dec(top); // 淹没，退栈
                //右边将要淹没( j)的到左面将要淹没(z[top])的之间的距离
                wd:=dd[j-1]-dd[z[top]]; 
                an[x]:=tol+wd; //writeln(x);
                hd:=min(h[j],h[z[top]])-h[x];
                inc(tol,wd*hd);    
            end;        
    until h[j]>=h[i]; //(h[z[top]); //两边均infinite 的时候会等于
end;
//z[top]:=j; //以向右扩展位置为右边界 top:=0;
procedure left;
begin 
    top:=0; 
    z[top]:=j;
    repeat //inc(ans); if ans>mn then begin writeln(ans);halt; end;
    //如果递减，就进站
    while h[i]<h[z[top]] do      //write('sd');
        begin //inc(ans);// if ans>mn then begin writeln(ans);halt; end;
        inc(top);
        z[top]:=i;
        dec(i);
        end;
    //不递减了，就处理 栈中的数据,处理小于 i 的数据    
    while (h[z[top]]<h[i]) and(top>0) do 
        begin // inc(ans); if ans>mn then begin writeln(ans);halt; end;
            // 处理（下一个被水淹没的），即退栈
                x:=z[top];
                dec(top);
            // 宽度为右边最低的（未被淹没，栈中的数据）
            // 减去 左边 最低的（未被淹没，i) 
            // 为什么不是 x-1呢？ 因为x-1 可能已经在退栈的时候被处理过了
            wd:=dd[z[top]-1]-dd[i]; //下一次将要淹没到栈顶
            an[x]:=tol+wd; //writeln(x);
            hd:=min(h[z[top]],h[i]); //下一次将要淹没的高度 ，预处理 
            hd:=hd-h[x]; //升高的高度
            inc(tol,hd*wd);
        end;
    until h[i]>=h[j];
end;
procedure main;
begin 
    h[0]:=infinite;  
    h[n+1]:=infinite; 
    i:=ml-1; // 
    j:=ml; // 将最低点划分到you面
    tol:=0;// 初始情况；
    while (i>=1)or (j<=n) do
        begin 
        right;//    
        left;
    end;
end;
begin 
    init;
    main;
    for i:=1 to n do  
        writeln(an[i]);     
end.

```

---

