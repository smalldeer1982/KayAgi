# Power Consumption Calculation

## 题目描述

Tom 对他最喜欢的笔记本电脑的耗电量很感兴趣。他的笔记本电脑有三种模式。在正常模式下，笔记本每分钟消耗 $P_{1}$ 瓦特。Tom 最后一次移动鼠标或按下键盘后的 $T_{1}$ 分钟，屏幕保护程序启动，耗电量变为每分钟 $P_{2}$ 瓦特。最后，从屏幕保护程序启动起经过 $T_{2}$ 分钟后，笔记本进入“睡眠”模式，耗电量变为每分钟 $P_{3}$ 瓦特。如果 Tom 在第二种或第三种模式下移动鼠标或按下键盘，笔记本会切换回第一种（正常）模式。Tom 使用笔记本的过程可以分为 $n$ 个时间段 $[l_{1}, r_{1}], [l_{2}, r_{2}], \ldots, [l_{n}, r_{n}]$。在每个区间内，Tom 会持续移动鼠标和按键盘。在这些时间段之间，Tom 离开了笔记本。请计算在 $[l_{1}, r_{n}]$ 这段时间内，笔记本总共消耗了多少电量。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
1 3 2 1 5 10
0 10
```

### 输出

```
30```

## 样例 #2

### 输入

```
2 8 4 2 5 10
20 30
50 100
```

### 输出

```
570```

# 题解

## 作者：Mars_Dingdang (赞：68)

题目本身难度不算太大，但我觉得比一般的红题难理解一点。
### 题目大意
输入 $n,P_1,P_2,P_3,T_1,T_2$，然后输入 $n$ 组数据 $l_i,r_i$，表示时间段。输出从开始使用到最后一个时间段结束所消耗的功率。
### 大体思路
- 首先，每个时间段内所消耗的功率为 $P_1×(r_i-l_i)$，这个很好理解，故不赘述。
	
    ```cpp
	int p1,p2,p3,t1,t2,n,ans=0;//如题
	cin>>n>>p1>>p2>>p3>>t1>>t2;
	for(int i=1;i<=n;i++){
		cin>>a[i].start>>a[i].end;/输入，a[i].start即l，a[i].end即r。
		a[i].seconds=a[i].end-a[i].start;
		ans+=a[i].seconds*p1;//计算使用时所消耗的功率。
	}
	```

- 这道题的重点就在于如何处理两时间段之间所消耗的功率。这需要再遍历一边。变量 $t$ 表示两时间段中间的间隔。然后就用分支结构讨论即可。当 $t<=T_1$ 时，功率为 $p1×t$；当 $T_1<t<=T_2+T_1$ （由于题目中说`再过 T2 秒`)时，功率为 $p1×t1+p2×(t-t1)$；当 $t>T_2$ 时，功率为 $p1×t1+p2×t2+p3×(t-t1-t2)$。

```cpp
	for(int i=1;i<n;i++){//由于最后一次不用计算，故为1~n-1。
		int t=a[i+1].start-a[i].end;//记录间隔长度。
		if(t<=t1) 
        	ans+=p1*t;
		else if(t>t1 && t<=t2+t1) 							ans+=p1*t1+p2*(t-t1);
		else ans+=p1*t1+p2*t2+p3*(t-t1-t2);//计算功率。
	}
```
### AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct USE{
	int start;
	int end;
	int seconds;
}a[105];
int main(){
	int p1,p2,p3,t1,t2,n,ans=0;
	cin>>n>>p1>>p2>>p3>>t1>>t2;
	for(int i=1;i<=n;i++){
		cin>>a[i].start>>a[i].end;
		a[i].seconds=a[i].end-a[i].start;
		ans+=a[i].seconds*p1;
	}
	for(int i=1;i<n;i++){
		int t=a[i+1].start-a[i].end;
		if(t<=t1) ans+=p1*t;
		else if(t>t1 && t<=t2+t1) ans+=p1*t1+p2*(t-t1);
		else ans+=p1*t1+p2*t2+p3*(t-t1-t2);
	}
	cout<<ans;
	return 0;
}
```
看得这么认真，不点个赞再走嘛qaq

---

## 作者：A_Cute_757 (赞：9)

这一道题其实并不难，不用数组就能够通过。
这篇题解应该是目前该题最简便的解法了。
希望还能够看到更加简便的解法！
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n,p1,p2,p3,t1,t2;//定义变量
    int l,r,s,ans=0;//定义变量
    cin>>n>>p1>>p2>>p3>>t1>>t2;//输入
    for(int i=1;i<=n;i++)//循环
    {
        cin>>l>>r;//输入区间的起始点和终点
        if(i>1)//忽略i等于1时的计算
        {
            ans=ans+min(t1,l-s)*p1;//ans加上t1或是l-s乘以两个区间的距离
	        if(l-s>t1)//如果l-s没有达到t1，证明t2是存在的
	        {
	            ans=ans+min(l-s-t1,t2)*p2;//将剩下的空间与p2对比，取出p2功耗的区间
	            if(l-s>t1+t2)//再一次做对比，判断是否存在t3
	            {
	                ans=ans+(l-s-t1-t2)*p3;//t3的值其实就是区间减去t1和t2后剩余的时间。再将这一段时间与p3功耗相乘就，能得出该区间的功耗
	            }
	        }		
        }		
        ans=ans+(r-l)*p1;
        s=r;	
    } 
    cout<<ans;//输出ans
    return 0;//完美的结尾
}
```

---

## 作者：封禁用户 (赞：4)

这道题的翻译不怎么样，它把t2打成了t3，并且没打输入格式。我来补充一下，输入格式是：n,t1,t2,p1,p2,p3，其中n表示这个人用了几次电脑。~~（然后我输入顺序反了WA几次）~~

然后我们可以开始讲正事儿了。比如说，这个人从10时刻开始没有用电脑，30时刻又一次使用电脑，t1是10，t2是5，那么我们模拟一下，就可以推出for循环里面的内容了。

那么怎么模拟呢？由于我们假设的t1是10，也就是说，这台电脑需要耗费10时刻的p1能源，然后在20时刻才进入休息状态。可得如下代码：

```c
if(t<t1){he+=t*p1;continue;}
he+=t1*p1;
t-=t1;
```
然后，还需要5时刻才进入睡眠模式，也就是说这台电脑需要再花费5时刻的p2能源，到25时刻才进入睡眠模式。可得如下代码：
```c
if(t<t2){he+=t*p2;continue;}
he+=t2*p2;
t-=t2;
```

但还有5时刻才进入第二次使用电脑的30时刻，所以还需要花费5时刻的p3能源，可得如下代码：he+=t*p3;

但是，这个t怎么来的呢？很简单，用两个变量x,y存放上一次输入的起始时间、结束时间（其实只存放结束时间就好），再用这次输入的起始时间减掉y，就得出t了。

注意，如果这是第一次使用电脑的话，把输入的数据复制给x,y，就用continue跳过这次循环了。

献上完整AC代码：

```c
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<string>

using namespace std;
int n,t1,t2,p1,p2,p3,a,b,x,y,t,he;
int main()
{
	cin>>n>>p1>>p2>>p3>>t1>>t2;
	for(int i=1; i<=n; i++)
	{
		cin>>a>>b;
		he+=(b-a)*p1;
		t=a-y;
		x=a;
		y=b;//求t，赋值x,y
		if(i==1)continue;
		if(t<t1){he+=t*p1;continue;}
		he+=t1*p1;
		t-=t1;//判断两次使用电脑的时间间隔是否达到t1，能不能进入休息状态
		if(t<t2){he+=t*p2;continue;}
		he+=t2*p2;
		t-=t2;//判断两次使用电脑的时间间隔能否达到t1+t2，能不能进入睡眠状态
		he+=t*p3;//把进入睡眠状态后还剩余的时间，也就是休眠状态的时间，乘上p3，并累加。
	}
	cout<<he;





    return 0;
}
```


---

## 作者：dfadfsafsdaf (赞：4)

[**模拟**](https://blog.csdn.net/qq_36257171/article/details/95651331)

[**排序**](https://blog.csdn.net/qq_30815237/article/details/88646699)

[**概率论**](https://baike.baidu.com/item/%E6%A6%82%E7%8E%87%E8%AE%BA/829122?fr=aladdin)

解模拟题的方法：
-

（1）认真仔细的读懂题目。模拟题的描述通常都比较详细，篇幅一般都比较长，应该边阅读边将有关的条件一条条地记录下来，阅读完成后要反复核对，绝对不能有错漏。

（2）建立各个条件之间的关系，最好用一些简明的表格列出。

（3）认真分析这些关系，并建立这些关系的数学模型。

（4）规划各个模块的结构，用相应的语言、逐步求精的方法描述具体的算法。

（5）编写程序，调试并运行。

（6）检查题目给出的样例能否通过。竞赛题目中一般都会给出输入输出样例，以便检查程序的输入输出格式是否正确，但这些样例往往会比竞赛时评判所用的测试数据简单，所以你不能满足于通过这些样例，还要尽量自拟一些更复杂、更全面的测试数据来检查程序的正确性。经过反复的调试、检查，才算完成该题。

好的，上代码~

ACcode：
--------
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,p1,p2,p3,t1,t2;
int l,r,s,ans=0;
void inp();
void io();
int main()
{
	inp();
	io();
	return 0;
}
void inp()
{
	cin>>n>>p1>>p2>>p3>>t1>>t2;//读入
}
void io()//代码核心
{
	for(int i=1; i<=n; i++)
	{
		cin>>l>>r;
		if(i>1)
		{
			ans=ans+min(t1,l-s)*p1;
			if(l-s>t1)
			{
				ans=ans+min(l-s-t1,t2)*p2;
				if(l-s>t1+t2)
				{
					ans=ans+(l-s-t1-t2)*p3;
				}
			}
		}
		ans=ans+(r-l)*p1;
		s=r;
	}
	cout<<ans;
}
```

谢谢观看~~

如果这篇题解对您有帮助，请点赞噢~~

[**我的博客1**](https://blog.csdn.net/zhaoweiming2019?orderby=ViewCount)

[**我的博客2**](https://zhaoweiming.blog.luogu.org/)



---

## 作者：OdtreePrince (赞：2)

# -模拟-

这是一道比较变态的模拟题！

题意有点难理解，慢慢来。

本题要分段统计耗能，最后输出答案

又是这标志性的Oh,yeah!

上代码！

~~~
#include<bits/stdc++.h>
using namespace std;
int ans,now1,now2,l[105],r[105],n,t1,t2,p1,p2,p3;
int main(){
    scanf("%d%d%d%d%d%d",&n,&p1,&p2,&p3,&t1,&t2);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&l[i],&r[i]);
    }
    for(int i=1;i<n;i++){
        ans+=p1*(r[i]-l[i]);
        now1=r[i]+t1;
        if(now1<l[i+1]){
            ans+=p1*t1;
            now2=now1+t2;
            if(now2<l[i+1]){
                ans+=t2*p2;
                ans+=p3*(l[i+1]-now2);
            }
            else ans+=p2*(l[i+1]-now1);
        }
        else ans+=(l[i+1]-r[i])*p1;
    }
    ans+=(r[n]-l[n])*p1;
    cout<<ans;
    return 0;
}
~~~

---

## 作者：蒲葵Sabal (赞：2)

一道题意有点复杂的模拟，理解之后还是挺好写der，注意细节，理解并处理好休眠的规则就很容易了。

另外，特别注意下，如果第一个区间不是从0开始，那么从0到第一次开始的时间是不计算能耗的。

下面上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long uns;
struct rtime
{
	uns s,e;
};
bool cmp(rtime x,rtime y)
{
	return x.s<y.s;
}
int main()
{
	uns n,p1,p2,p3,t1,t2,ans=0; cin>>n>>p1>>p2>>p3>>t1>>t2;	//数据读入
	rtime data[n+1];	//用个结构体存运行时间段
	for(uns i=1;i<=n;i++) cin>>data[i].s>>data[i].e;
	sort(data+1,data+n+1,cmp);	//排序，好像不必要orz
	for(uns i=1;i<=n;i++)
	{
		ans+=(data[i].e-data[i].s)*p1; //加上这个时间段运行时间的能耗
		if(i==1) continue;	//第一个时间段开始之前的时间不考虑能耗
		uns dt=data[i].s-data[i-1].e;	//两个时间段时间的空隙
		if(dt>=t1) ans+=t1*p1,dt-=t1;	//休眠的规则处理，代码不难，自行理解下QWQ
		else
		{
			ans+=dt*p1; continue;	
		}
		if(dt>=t2) ans+=t2*p2,dt-=t2;
		else
		{
			ans+=dt*p2; continue;	
		}
		if(dt>0) ans+=dt*p3;
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：陈科同 (赞：1)

一道较难的红题。

数据不大，用int，输入变量，两个for循环，大功告成。

代码奉上：
```
	int n,p1,p2,p3,t1,t2,i,a[101]={0},b[101]={0},t=0,z;
	cin>>n>>p1>>p2>>p3>>t1>>t2;
	for(i=1;i<=n;++i){
		cin>>a[i]>>b[i];
		t+=p1*(b[i]-a[i]);//先把用时的耗能算好
	}
	for(i=1;i<=n;++i){
    //再把不用时的耗能算好
		z=a[i+1]-b[i];
		if(z<=0);
		else{
			if(z>t1)t+=t1*p1,z-=t1;
			else t+=z*p1,z=0;//t1秒之前的耗能还是p1
			if(z>t2)t+=t2*p2,z-=t2;
			else t+=z*p2,z=0;//t2秒之前的耗能就是p2了
			t+=z*p3;//t2秒之后的耗能就是p3了
		}
	}
	cout<<t;
```




---

