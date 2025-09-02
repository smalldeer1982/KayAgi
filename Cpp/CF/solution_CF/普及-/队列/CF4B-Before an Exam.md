# Before an Exam

## 题目描述

Tomorrow Peter has a Biology exam. He does not like this subject much, but $ d $ days ago he learnt that he would have to take this exam. Peter's strict parents made him prepare for the exam immediately, for this purpose he has to study not less than $ minTime_{i} $ and not more than $ maxTime_{i} $ hours per each $ i $ -th day. Moreover, they warned Peter that a day before the exam they would check how he has followed their instructions.

So, today is the day when Peter's parents ask him to show the timetable of his preparatory studies. But the boy has counted only the sum of hours $ sumTime $ spent him on preparation, and now he wants to know if he can show his parents a timetable $ sсhedule $ with $ d $ numbers, where each number $ sсhedule_{i} $ stands for the time in hours spent by Peter each $ i $ -th day on biology studies, and satisfying the limitations imposed by his parents, and at the same time the sum total of all $ schedule_{i} $ should equal to $ sumTime $ .

## 样例 #1

### 输入

```
1 48
5 7
```

### 输出

```
NO
```

## 样例 #2

### 输入

```
2 5
0 1
3 5
```

### 输出

```
YES
1 4 ```

# 题解

## 作者：Priori_Incantatem (赞：36)

本蒟蒻不会楼下dalao们用的优先队列和DP，来发个最简单的贪心

首先判断sumtime是否在maxtime之和 和 mintime之和之间

~~如果不在的话Peter就死定啦~~

如果有解的话就先每天学习mintime[ i ]小时然后多余的时间就依次塞到每一天里，但每一天最多只能塞到那一天的maxtime


------------
奉上代码：
```cpp
#include<iostream>
using namespace std;
int n,i,s,mins,maxs;
int a[31],b[31];//每一天的maxtime和mintime
int main(){
    cin>>n>>s;
    for(i=1;i<=n;i++)
    {
        cin>>a[i]>>b[i];
        mins+=a[i];//mintime之和
        maxs+=b[i];//maxtime之和
    }
    if(s<=maxs&&s>=mins)//如果有解的话
    {
        cout<<"YES"<<endl;
        s-=mins;
        i=1;
        while(s)   //当s!=0
        {   
            if(s>b[i]-a[i])
            {
                s-=b[i]-a[i];
                a[i]=b[i];
            }
            else 
            {
                a[i]+=s;
                s=0;
            }
            i++;
        }
        for(i=1;i<=n;i++)
        cout<<a[i]<<' ';
    }
    else cout<<"NO! YOU ARE DEAD!!!"<<endl;
    return 0;
}
```

---

## 作者：Mars_Dingdang (赞：14)

### 题目大意
给出总时间（$sum$），天数 $d$ 以及每天时间的区间（$MaxTime_i,MinTime_i$），求出一种满足条件的方案。若没有满足条件的方案则输出 `NO`。

### 大体思路
- 首先是判断能否有满足条件的方案。其实这一点非常容易，只要总时间在最少时间之和与最大时间之和之间即可，即 $sum∈[Σ_{ MinTime_i},Σ_{ MaxTime_i}]$。

代码如下：
```cpp
	int d,sum,minn=0,maxm=0;
	cin>>d>>sum;
	for(int i=1;i<=d;i++){
		cin>>a[i].mint>>a[i].maxt;//输入
		minn+=a[i].mint;// MinTime之和
		maxm+=a[i].maxt;// MaxTime之和
	}
	if(sum<minn||sum>maxm) {//判断能否满足
		cout<<"NO";
		return 0;//如果不能，输出“NO”，结束程序。
	}
```
- 接下来的任务则是寻找满足条件的方案，用贪心即可。用总时间 $sum-minn$，得到还需满足的时间，如果这个值为零则表示此方案满足条件，输出并结束程序，否则继续寻找。对于每一天的数据寻找，范围是 $1$ ~ $MaxTime_i-MinTime_i$，一次让 $Mintime_i+1,sum-1$。若 $sum=0$ 则表示此方案满足条件。

代码如下：
```cpp
	cout<<"YES\n";//由于不符合条件的已经输出“NO”并结束程序，此处直接输出“YES”。
	sum-=minn;//求出待满足的时间
	if(sum!=0){//若此时不满足条件
		for(int i=1;i<=d;i++){
			bool flag=0;//标记是否找到
			for(int j=1;j<=a[i].sub;j++){
				a[i].mint++;//时间+1
				sum--;//差值-1
				if(sum==0){
					flag=1;
					break;
				}
			}
			if(flag==1) break;//若找到则结束循环
		}
	}
```
此时 $a[\ i\ ].mint$ 存的便是一组答案。
最后输出即可。

### 完整代码
```cpp
#include<bits/stdc++.h>//头文件
using namespace std;
struct STUDY{
	int mint;//即MaxTime
	int maxt;//即MinTime
	int sub;//记录两者差值，后续循环要用
}a[33];
int main(){
	int d,sum,minn=0,maxm=0;
	cin>>d>>sum;
	for(int i=1;i<=d;i++){
		cin>>a[i].mint>>a[i].maxt;//输入
		minn+=a[i].mint;
		maxm+=a[i].maxt;
		a[i].sub=a[i].maxt-a[i].mint;//处理
	}
	if(sum<minn||sum>maxm) {
		cout<<"NO";
		return 0;
	}//若不满足条件，输出“NO”并结束程序
	cout<<"YES\n";
	sum-=minn;//记录差值
	if(sum!=0){//若此时不满足条件
		for(int i=1;i<=d;i++){
			bool flag=0;
			for(int j=1;j<=a[i].sub;j++){
				a[i].mint++;
				sum--;
				if(sum==0){
					flag=1;
					break;
				}
			}
			if(flag==1) break;
		}
	}
	for(int i=1;i<=d;i++) 
    	cout<<a[i].mint<<" ";//输出
	return 0;//完美
}
```
~~看得这么认真，不点个赞再走嘛qaq~~

---

## 作者：Loner_Knowledge (赞：7)

这是一道贪心题

---

首先如果总计的$minTime$大于$sumTime$或者总计的$maxTime$小于$sumTime$，就必定输出`NO`。


如果不满足`NO`的条件，那么对于每个区间必定能选$minTime$，遍历时只需要贪心地判断每个区间能否选到$maxTime$，如果不能就选择剩余的$Time$加上$minTime$即可。


```cpp
#include<cstdio>
struct Data {
    int min,max;
    int delta;        //为了实现对YES情况先选择总计的minTime，记录maxTime与minTime的差值
}D[31],sum;
int main() {
    int d,t;
    scanf("%d%d",&d,&t);
    for(int i=0;i<d;++i) {
        scanf("%d%d",&D[i].min,&D[i].max);
        D[i].delta=D[i].max-D[i].min;
        sum.min+=D[i].min;
        sum.max+=D[i].max;
    }
    if(sum.max<t||sum.min>t)
        printf("NO");
    else {
        printf("YES\n");
        t-=sum.min;                //先选择总计的minTime
        for(int i=0;i<d;++i) {
            if(t>=D[i].delta) {            //贪心地选择
                printf("%d ",D[i].max);
                t-=D[i].delta;
            }
            else {
                printf("%d ",t+D[i].min);
                t=0;
            }
        }
    }
    return 0;
}
```

---

---

## 作者：dfadfsafsdaf (赞：4)

超水的一道贪心题
[贪心](https://blog.csdn.net/Septembre_/article/details/79809145)

贪心的定义：

       贪心选择是指所求问题的整体最优解可以通过一系列局部最优的选择，即贪心选择来达到。这是贪心算法可行的第一个基本要素，也是贪心算法与动态规划算法的主要区别。贪心选择是采用从顶向下、以迭代的方法做出相继选择，每做一次贪心选择就将所求问题简化为一个规模更小的子问题。对于一个具体问题，要确定它是否具有贪心选择的性质，我们必须证明每一步所作的贪心选择最终能得到问题的最优解。

最优子结构：


当一个问题的最优解包含其子问题的最优解时，称此问题具有最优子结构性质。运用贪心策略在每一次转化时都取得了最优解。问题的最优子结构性质是该问题可用贪心算法或动态规划算法求解的关键特征。贪心算法的每一次操作都对结果产生直接影响，而动态规划则不是。贪心算法对每个子问题的解决方案都做出选择，不能回退；动态规划则会根据以前的选择结果对当前进行选择，有回退功能。动态规划主要运用于二维或三维问题，而贪心一般是一维问题 

好的，话不多说，上代码~（本场最短哦！）
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node {
	int min,max,delta;
} e[31],sum;
int main() {
	int d,t;
	cin>>d>>t;
	for(int i=0; i<d; ++i) {
		cin>>e[i].min>>e[i].max;
		e[i].delta=e[i].max-e[i].min;
		sum.min+=e[i].min;
		sum.max+=e[i].max;
	}
	if(sum.max<t||sum.min>t) cout<<"NO";
	else {
		cout<<"YES\n";
		t-=sum.min;
		for(int i=0; i<d; ++i) 
			if(t>=e[i].delta) cout<<e[i].max<<" ",t-=e[i].delta;
			else cout<<t+e[i].min<<endl,t=0;
	}
	return 0;
}
```
谢谢观看~

---

## 作者：Michael_Kong (赞：2)

一道比较简单的贪心。。。

说实在看到标签上面说前缀和的时候我还愣了一下

这不就是比较简单的贪心吗。。。

就是首先求出这段时间内Peter能不能完成任务。检查的方法也很简单，就是他的复习总时间要在每天最小时间的和到每天最大时间的和之间，否则他就会被父母或生物暴捶

简单来讲就是sumTime>=minTime的总和，并且sumTime<=maxTime的总和

接下来我们还需要打印一个序列代表每天的耗时，我们可以先假设Peter每天只花了最少的时间来复习，这样做肯定会达不到复习总时间的要求。

再然后我们把前面x天(x<=d)每天的耗时直接拉满到最大，直到剩余总时间为0。

不多说了，直接上代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=1926;
int mint[maxn],maxt[maxn],n,tot;
int mins,maxs,ans[maxn];
int main(void) {
	scanf("%d %d",&n,&tot);
	for(int i=1; i<=n; i++) {
		scanf("%d %d",&mint[i],&maxt[i]);
		mins+=mint[i];
		maxs+=maxt[i];
	}
	if(tot>=mins&&tot<=maxs) {
		printf("YES\n");
	} else {
		printf("NO\n");
		return 0;
	}
	tot-=mins;
	for(int i=1; i<=n; i++) {
		if(tot-(maxt[i]-mint[i])>0) {
			tot-=maxt[i]-mint[i];
			ans[i]=maxt[i];
		}else{
			ans[i]=mint[i]+tot;
			tot=0;
		}
	}
	for(int i=1;i<=n;i++){
		printf("%d ",ans[i]);
	}
}
```

特别要注意yes和no都要大写~~(我就是在这里被坑掉了一次的)~~

萌新第一次写题解，求dalao轻喷

---

## 作者：konglk (赞：2)

相信大家一上来就能判断是No还是YES
```
如果每天都用最多时间maxtime还到不了需要的sumtime（这家长明显不是亲家长），一定是NO。
对于mintime也很类似地可以得出关于mintime什么时候NO的结论
```
好了，反之都是YES

不过情况怎么构造呢？我的思路是，假设皮特是个把所有事情都推到最后的人，每天能最少就最少，直到最少的完不成了，紧接着又在能完成的情况下最少

那么此时就需要看剩下几天最多能完成多少，来保证在能完成的情况下最少。
```cpp
//下面是蒟蒻的代码
#include<iostream>
using namespace std;
int maxt[31],mint[31],maxbeleft[31];//此处maxbeleft就是前面介绍的接下几天能最多学习多长时间
int main()
{
	int d,sum,mins=0,maxs=0;
	cin>>d>>sum;
	for(int i=1;i<=d;i++)
	{
	cin>>mint[i]>>maxt[i];
	mins+=mint[i];
	maxs+=maxt[i];
	for(int j=1;j<i;j++)
	maxbeleft[j]+=maxt[i];//每一个前面的天的maxbeleft都要加上新增的这一天的maxt
}
	if(sum<mins||sum>maxs)
	{
		cout<<"NO\n";
		return 0;
	}
	cout<<"YES\n";
	for(int i=1;i<=d;i++)
	{
		int det=mint[i];//det用来决定这一天能完成的下最少多少，肯定是先看最少的时候能不能完成任务
		while(det+maxbeleft[i]<sum)//只要加上以后能完成的最多的完不成，det就加1
		det++;
		cout<<det<<" ";
		sum-=det;
	}
	cout<<endl;
	return 0;
 } 
```
谢谢你的认真观看

---

## 作者：www2003 (赞：2)

看没有用前缀和+贪心的，赶紧来水一篇（感觉没见过这么简单的前缀和）。
思路：记录最大前缀和和最小前缀和-->从后往前推当前能取得最大值
具体请看代码

****

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<cstring>
#include<cmath>
#include<vector>
#include<map>
#include<sstream>
#include<iomanip>
#define pb push_back
#define LL long long
#define ff first
#define ss second
#define in inline
#define RE register
using namespace std;
const int MAXN=0x3f3f3f3f;
const int MAXL=0x7ffff
in void read(int &x){
   x=0;
   char c=getchar();
   while(c>'9'||c<'0')c=getchar();                
   while(c<='9'&&c>='0'){
   x=x*10+c-'0';
   c=getchar();
   }
}
inline void write(int re)
 {    
  if (re>9) write(re/10);
  putchar(re%10+'0');
}
int ans[35],ma[35],mi[35],qmax[35],qmin[35];
int n,d;
int main()
{
    read(n);
	read(d); 
	for(int i=1;i<=n;i++){
		read(mi[i]);
		read(ma[i]);
		qmin[i]=qmin[i-1]+mi[i];//最小前缀和
		qmax[i]=qmax[i-1]+ma[i];//最大前缀和
	}
	if(d>qmax[n]||d<qmin[n])
	{
		cout<<"NO";
		return 0;
	}//最小的也必须要的大或最大的比最小的小，果断不行
	cout<<"YES"<<endl;
	for(int i=n;i>=1;i--)
	{
		ans[i]=min(ma[i],d-qmin[i-1]);/*前几天听老师讲的一个很简单的玄学的思想，因为要去最大值，在能去的范围内取得最大值*/
		d-=ans[i];
	}
	for(int i=1;i<=n;i++){
	write(ans[i]);
	putchar(' '); 
	}//套路输出
}
```
_ 
------------

少抄题解，幸福一生

---

## 作者：TLMPEX (赞：1)

这是一道比较简单的贪心。

思路：我们可以用一个变量x来记录他妈让皮特每天最少用时之和，用一个变量y来记录他妈让皮特每天最多用时之和，如果x比皮特的总用时大或y比皮特的总用时小，则输出NO了。否则输出yes了。如果是yes呢，则先把皮特每天的用时置为他妈让皮特每天最少用时，把总时间减去x啦，如果还有时间，则用二重循环把皮特每天的用时一个一个加（在他妈让皮特每天最多用时只内），总用时一个一个减，最后输出皮特每天的用时情况，就完美结束啦！

```c
#include<bits/stdc++.h>
using namespace std;
int a[31],b[31],k[31];
int main(){
	int n,m,i,j,x=0,y=0,z;
	cin>>n>>m;
	z=m;
	for(i=1;i<=n;i++){
		cin>>a[i]>>b[i];
		x+=a[i];
		y+=b[i];
	}
	if(x>m||y<m)cout<<"NO";
	else{
		cout<<"YES"<<endl;
		for(i=1;i<=n;i++)
			k[i]=a[i];
		z-=x;
		if(z){
			for(i=1;i<=n;i++){
				int t=0;
				for(j=1;j<=b[i]-a[i];j++){
					k[i]++;
					z--;
					if(!z){
						t=1;
						break;
					}
				}
				if(t)break;
			}
		}
		for(i=1;i<=n;i++)
			cout<<k[i]<<" ";
	}
}
```


---

## 作者：离散小波变换° (赞：1)

## 题目大意

$n$ 天，每天可以选择 $[L_i,R_i]$ 时间用来复习。求是否可以使复习时间**恰好**为 $s$。若可以，求出方案。

## 题解

很显然这 $n$ 天的总复习时间可以为 $\left[\sum\limits_{i=1}^nL_i,\sum\limits_{i=1}^nR_i\right]$。

如果存在合法方案，那么每一天**必定**要学习至少 $L_i$ 时长。那么我们不妨先给每一天选择$L_i$时长，此时这一天**还可以**学习 $T_i=(R_i-L_i)$ 时长。初步分配后，我们还需要选择 $t=\left(s-\sum\limits_{i=1}^nL_i\right)$ 时长的学习时间。

此时依次考虑每一天。我们贪心地分配剩余地时间，即越靠前的天数多学习越多的时长。若 $T_i\le t$，那么就将这一天全部选满，并且令 $t\gets (t-T_i)$。如果出现了 
 $T_i>t$，那么只需要再学习 $T_i-t$ 天，那么就可以完成学习计划。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define up(l,r,i) for(int i=l;i<=r;i++)
#define dn(l,r,i) for(int i=l;i>=r;i--)
using namespace std;

typedef long long LL;
const int INF =2147483647;
int qread(){
    int w=1,c,ret;
    while((c=getchar())> '9'||c< '0')
    w=(c=='-'?-1:1); ret=c-'0';
    while((c=getchar())>='0'&&c<='9')
    ret=ret*10+c-'0';
    return ret*w;
}
const int MAXN =30+3;
int n,s,t,L[MAXN],R[MAXN],T[MAXN];
int main(){
    n=qread(),s=qread();
    up(1,n,i){
        L[i]=qread(),R[i]=qread();
        s-=L[i],T[i]=R[i]-L[i],t+=R[i]-L[i];
    }
    if(s<0||s>t) puts("NO"),exit(0);
    puts("YES"); up(1,n,i){
        if(s>=T[i]) s-=T[i],printf("%d ",L[i]+T[i]);
        else printf("%d ",L[i]+s),s=0;
    }
    return 0;
}
```

---

## 作者：aiyougege (赞：0)

### CF4B 【Before an Exam】
　　这道题大家简直就是*八仙过海各显神通*.
#### Solution
　　我是这么做的: 首先判断存不存在这么一种方案即总时间不小于最小时间不大于最大时间.

　　然后首先取每天的最少时间, 如果这样比总时间少的话就从有剩余时间的天里增加时间. 我使用了一个**优先队列**存每天剩余时间, 从剩余时间最大的那天增加时间.

　　注意:一天的时间被更新过之后不再放回优先队列.

#### Code
```c++
#include<cstdio>
#include<queue>
using namespace std;

struct Node{
    int pos,rest;
    bool operator<(const Node& s)const{
        return rest>s.rest;
    }
};

priority_queue<Node>que;

int n,sum;
int f[36];
int l[35],r[35];

int main(){
    scanf("%d%d",&n,&sum);
    int maxl,minl;maxl=minl=0;
    for(int i=1;i<=n;++i){
        scanf("%d%d",&l[i],&r[i]);
        maxl+=r[i],minl+=l[i];
    }
    if(maxl<sum||minl>sum){
        printf("NO");
        return 0;
    }
    int ans=0;
    for(int i=1;i<=n;++i){
        f[i]=l[i],ans+=l[i];
        que.push((Node){i,r[i]-l[i]});
    }
    while(ans<sum){
        Node top=que.top();
        que.pop();int val=min(sum-ans,top.rest);
        f[top.pos]+=val;
        ans+=val;
        top.rest-=val;
    }
    printf("YES\n");
    for(int i=1;i<=n;++i)
        printf("%d ",f[i]);
    return 0;
}
```

---

## 作者：早右昕 (赞：0)

# 这是一道DP题
---

按照背包的思路，设$dp_{i,k}$为前$i$天里总用时为$k$的可能，转移是显而易见的。为了输出一个解，我们用$f_{i,k}$表示前$i$天里总用时为$k$如要成立需要用多少时间，最终递归输出即可。

以下为代码：
```cpp
#include<bits/stdc++.h>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=300+5;

int n,sum,maxt[maxn],mint[maxn];
int f[maxn][maxn];
bool dp[maxn][maxn];
void out(int i,int k) {
  if(i==0) return;
  out(i-1,k-f[i][k]);
  printf("%d ",f[i][k]);
}
int main() {
  scanf("%d%d",&n,&sum);
  dp[0][0]=1;
  for(int i=1; i<=n; i++) {
    scanf("%d%d",&mint[i],&maxt[i]);
    for(int j=mint[i]; j<=maxt[i]; j++) {
      for(int k=sum; k>=j; k--) {
        if(dp[i-1][k-j]) {
          dp[i][k]=1;
          f[i][k]=j;
        }
      }
    }
  }
  if(!dp[n][sum]) puts("NO");
  else {
    puts("YES");
    out(n,sum);
  }
}

```

---

