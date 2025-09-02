# [USACO14JAN] Bessie Slows Down S

## 题目背景

奶牛题


## 题目描述

Bessie the cow is competing in a cross-country skiing event at the winter Moolympic games.  She starts out at a speed of 1 meter per second. However, as she becomes more tired over time, she begins to slow down. Each time Bessie slows down, her speed decreases: she moves at 1/2 meter per second after slowing down once, then 1/3 meter per second after slowing down twice, and so on.

You are told when and where Bessie slows down, in terms of a series of events.  An event like this:

T 17
means that Bessie slows down at a specific time -- here, 17 seconds into the race.  An event like this:

D 10
means that Bessie slows down at a specific distance from the start -- in this case, 10 meters.

Given a list of N such events (1 <= N <= 10,000), please compute the amount of time, in seconds, for Bessie to travel an entire kilometer.  Round your answer to the nearest integer second (0.5 rounds up to 1).

贝西正在参加一项滑雪比赛。她从起点出发的时候，速度恒定为每秒 1 米。然而，随着比赛进程的增加，她会犯很多错误，每次失误都会使她的速度下降。当她第一次失误后，速度会下降到每秒1/2 米，第二次失误后，速度会下降到每秒 1/3 米，第 k 次失误后，速度会下降到每秒 1/(k + 1) 米。

约翰记录了贝西的所有失误，一共有 N 个。有两种失误，一种发生在比赛开始后的某个时间点，另一种发生在赛道的某个位置上。有时，贝西可能在某个时间点到达某个位置，而恰好在这个时间点和位置上都有一次失误的记录，这两个记录要算作不同的失误，会对贝西的速度造成两次影响。比赛的终点距离起点有 1000 米，请问贝西需要多少时间才能滑过终点？


## 说明/提示

前 10 秒，贝西的速度是每秒 1 米，她滑了 10 米。然后她遭遇了第一次失误，在接下

来的 20 秒内，她又滑了 10 米。之后她遭遇了第二次失误，还剩下 980 米，所以她共计花去

10 + 20 + 2940 = 2970 秒才完成比赛


## 样例 #1

### 输入

```
2
T 30
D 10```

### 输出

```
2970```

# 题解

## 作者：LevenKoko (赞：11)

//没有什么人发题解，是不是看到 提高+/省选-被吓走了（幸好我没看到）

 
//思路蛮简单的(虽然我做了好久好久)，把 T和D分开存储并分别排序


//然后再是比较Ti Dj，比较Ti乘上速度加上原来走的路程和Di


//最后再把没有完成的路程所需时间加上去（然而我第一次打了时间=路程\*速度，hhhhhhh）

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<vector>
#include<map>
#include<iomanip>
#include<stack>
#include<set>
#include<queue>
#include<algorithm>
using namespace std;
char chr;
double s=0,tot=0,v1,st,sd;//tot表示时间（无奈） 
int n,t[10001]={0},d[10001]={0},lt=0,ld=0,v=1;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        cin>>chr;
        if(chr=='T') cin>>t[++lt];
        else cin>>d[++ld];
```
}//这里把T D分开读入；
    
```cpp
    sort(t+1,t+lt+1);
    sort(d+1,d+ld+1);//排序不讲 
    d[ld+1]=0x3f3f3f3f;
    t[lt+1]=0x3f3f3f3f;//重点：如果没有这里的话，下面的i和j可能一个永远不变，一个一直加1； 
    int i=1,j=1;
    while(i<=lt||j<=ld)
    {
        v1=1.0/v;//算速度； 
        st=s+(t[i]*1.0-tot)*v1;//用Ti的时间 
        sd=d[j];//用Dj的时间 
        if(st<sd)
        {
            s=st;//更新路程 
            tot=t[i];//这里不要 路程/速度，可能会有精度问题 （我也没试过） 
            i++;
        }
        else
        {
            tot+=(sd-s)/v1;
            s=sd;
            j++;
        }
        v++;//时间的分母++； 
    }
    tot+=(1000-s)/(1.0/(v*1.0));//最后再把没有完成的路程所需时间加上去 
    cout<<int(tot+0.5);//四舍五入噢！ 
    return 0;
}

```

---

## 作者：Yeji_ (赞：6)

## 失败的滑雪
### 前言
本题评为蓝题可以说是评高了，这道题其实就是一道纯模拟题，所以并没有什么可说的。

### 题意
就是Bessie她会在行驶到某个路程或某个时间的时候，速度就会降低到题目所述了。

### 解法
每次判断路程以及时间是否会出现错误，那么就直接给出代码

### 代码
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
int n,x,tot1,tot2,l,r;
double a[100005],b[100005],y,z;
char c;
int main()
{
    cin>>n;
    for (int i=1;i<=n;i++)
    {
        cin>>c>>x;
        if (c=='T')	
            a[++tot1]=x;
        else 
            b[++tot2]=x;
    }
    sort(a+1,a+1+tot1);
    sort(b+1,b+1+tot2);
    x=1;l=1;r=1;
    for (int i=1;i<=n;i++)
        if ((r>tot2||(b[r]-y)*x+z>=a[l])&&(l<=tot1))
        {
            if ((a[l]-z)/x+y>1000)
                break;
            y+=(a[l]-z)/x;
            z=a[l];x++;
            l++;
        }
        else
        {
            if (b[r]>1000)
                break;
            z+=(b[r]-y)*x;
            y=b[r];
            x++;
            r++;
        }
    cout<<int((1000-y)*x+z+0.499999);
}
```


---

## 作者：moosssi (赞：5)

感觉这道题难度虚高，直接模拟就可以过。

大概说一下我的模拟思路，先把 $T$ 和 $D$ 分开存起来，再从小到大排序，然后，依次枚举 $D$ 数组里的每个元素，判断在当前位置到下一个犯错位置之间 ，如果有犯错时间的节点，那么都处理掉，最后 $D$ 跑完了，如果还没到，就再执行之前的操作直到到达终点。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=10005;
int T[N],D[N],n;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		char s;
		int a;
		cin>>s>>a;
		if(s=='T')T[++T[0]]=a;//分开储存 
		else D[++D[0]]=a;			
	}
	sort(T+1,T+T[0]+1);
	sort(D+1,D+D[0]+1);
	double pos=0,tim=0,k=1;//以此为当前位置，当前时间，题中描述的k 
	int j=1;
	for(int i=1;i<=D[0];i++){
		double temp=(T[j]-tim)*1.0*(1/k)+pos;//到下一个时间点的总路程 
		while(temp<=D[i]&&j<=T[0]){//如果没超过下一个犯错位置就处理掉 
			tim=T[j++],pos=temp,k++;//更新各种元素 
			temp=(T[j]-tim)*1.0*(1/k)+pos;
		}
		tim+=(D[i]-pos)*1.0/(1/k);
		pos=D[i],k++;
	}
	double temp=(T[j]-tim)*1.0*(1/k)+pos;
	while(temp<=1000&&j<=T[0]){//再次判断，如果没走到终点，就重复执行 
		tim=T[j++],pos=temp,k++;
		temp=(T[j]-tim)*1.0*(1/k)+pos;		
	}
	if(pos<1000)tim+=(1000-pos)*k;
	printf("%d",(int)(tim+0.5)); 
	return 0;
}


```


---

## 作者：xMinh (赞：3)

#非正解系列

并不是很难的模拟，然而我又打的歪解……

各位dalao好像都是按照失误次数来跑循环，而我是按照时间轴

第一眼看到时间的范围是10的7 次方，就觉得有办法

然后每一秒先看路程，如果路程超了就先到达该摔的路程，之后这一秒里面剩下的换速度来跑

之后如果这一秒应该摔，就再变一下速度

到了一千米就算一下s和t，之后退出循环就行了

然鹅有一个恶心的地方就是一秒钟或者是同一路程能摔好几下，开数组处理就好了

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#define timi 10000000
#define rint register int
#define ind inline long double
using namespace std;
int n,k=1,tim,sum;
int t[10000000],d[10000];
ind fall(long double l,int m,int ti)
{
    long double s1=(m*1.0-l)*1.0;
    long double t1=(m*1.0-l)/(1.0/k);
    long double t2=(1.0-t1);
    long double s2=t2*(1.0/(++k));
    int f=0;
    if (t1>t2) f=1;
    tim=ti-1+f;
    return l+s1+s2;
}
int main()
{
    scanf("%d",&n);
    for (rint i=1;i<=n;i++)
    {
        char c;int x;
        cin>>c>>x;
        if (c=='T') t[x]++;
        if (c=='D') d[x]++;
    }
    long double v=1,s=0;
    for (rint i=1;i<=timi;i++)
    {    
        s+=v;
        while (d[int(s)])
        {
            s=fall(s-v,int(s),i);
            v=1.0/(k)*1.0;
            d[int(s)]--;
        }
        while (t[i]) 
        {
            v=1.0/(++k)*1.0;
            t[i]--;
        }
        if (int(s)==1000)
        {
            s=fall(s-v,int(s),i);
            printf("%d",tim);
            return 0;
        }
    }
}
```

---

## 作者：ezоixx130 (赞：2)

这道题明显是一道模拟题。

我们可以将题目中所有的D事件和T事件分别存在两个vector里，然后分别排序。

显然的，我们只需要判断下一个时间是D事件还是T事件就可以了。

求出了下一个事件后，答案便不难求出了。


代码：

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int n,nt,nd;
vector<int> t,d;
double nowt,nowd;
int speed=1;

bool comp()
{
    return (nowt+(d[nd]-nowd)*speed)>t[nt];
}

int main()
{
    cin >> n;
    char c;
    int tp;
    for(int i=1;i<=n;++i)
    {
        cin >> c >> tp;
        if(c=='D' && tp>1000)continue;
        if(c=='D')d.push_back(tp);else t.push_back(tp);//分别对每个事件存入相应的vector中
    }
    d.push_back(1000);
    sort(d.begin(),d.end());//排序
    sort(t.begin(),t.end());//排序
    while(nt!=t.size() || nd!=d.size())
    {
        bool nxttime=nd==d.size();
        if(!nxttime && nt!=t.size())nxttime=comp();//确定下一个事件是D事件还是T事件
        if(nxttime)
        {
            nowd+=(t[nt]-nowt)/(double)speed;
            nowt=t[nt++];
        }
        else
        {
            nowt+=(d[nd]-nowd)*speed;
            nowd=d[nd++];
        }
        ++speed;
    }
    printf("%.0lf",nowt);//输出答案
}
```

---

## 作者：qscqesze_lca (赞：2)

没什么人发 我来

对D和T排序，然后判断下一次是D还是T

首先将所有位置和时间从小到大排序。

从小到大枚举每一个位置，判断是先到达此位置还是先到达下一个时间，相应的修改总路程、总时间和速度。

最终输出总时间。

在枚举距离的时候同时更新时间

从小到大枚举每一个位置，判断是先到达此位置还是先到达下一个时间，相应的修改总路程、总时间和速度。

最终输出总时间。

代码如下

```cpp
#include<iostream>  
#include<cstdio>  
#include<cstring>  
#include<algorithm>  
#include<cmath>  
#define F(i,j,n) for(int i=j;i<=n;i++)  
#define D(i,j,n) for(int i=j;i>=n;i--)  
#define MAXN 10050  
#define LL long long  
using namespace std;  
int n,x,p=1,lt=0,ld=0,per=1;  
char ch;  
double dis,tim=0,d[MAXN],t[MAXN];  
int main()  
{  
    scanf("%d",&n);  
    d[++ld]=0;  
    d[++ld]=1000;  
    F(i,1,n)  
    {  
        ch=getchar();  
        while (ch!='T'&&ch!='D') ch=getchar();  
        scanf("%d",&x);  
        if (ch=='T') t[++lt]=x;  
        else d[++ld]=x;  
    }  
    sort(t+1,t+lt+1);  
    sort(d+1,d+ld+1);  
    F(i,1,ld-1)  
    {  
        dis=d[i];  
        while (dis<d[i+1]&&p<=lt&&tim+(d[i+1]-dis)*per>t[p])  
        {  
            dis+=(t[p]-tim)/per;  
            per++;  
            tim=t[p++];  
        }  
        tim+=(d[i+1]-dis)*per;  
        per++;  
    }  
    tim=(int)(tim+0.5);  
    printf("%.0lf\n",tim);  
}
```

---

## 作者：Ezis (赞：1)

我们可以把所有 $T$ , $D$ 的情况存下来（两个数组）。

先让$T$的数组的头和尾分别定义为 $0$ 和 $1000$,再对他们分别排序。

然后枚举直到没有操作即可。

### 主要代码：

```cpp
for(int i=1;i<tot2;i++){
	double nd=b[i];
	while(nd<b[i+1]&&c<=tot1&&nt+(b[i+1]-nd)*v>a[c]){
		nd+=(a[c]-nt)/v;
		v++;
		nt=a[c++];
	}
	nt+=(b[i+1]-nd)*v;
	v++;
}
```

注意最后还要对它四舍五入


## 最终代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,tot1,tot2,v=1,c=1;
int a[10005],b[10005];
double nt,nd;
int main(){
//	freopen("slowdown.in","r",stdin);
//	freopen("slowdown.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		char t[10];
		scanf("%s",t);
		if(t[0]=='T'){
			int x;
			scanf("%d",&x);
			a[++tot1]=x;
		}
		else{
			int x;
			scanf("%d",&x);
			b[++tot2]=x;
		}
	}
	b[++tot2]=0;
	b[++tot2]=1000;
	sort(b+1,b+tot2+1);
	sort(a+1,a+tot1+1);
	for(int i=1;i<tot2;i++){
		double nd=b[i];
		while(nd<b[i+1]&&c<=tot1&&nt+(b[i+1]-nd)*v>a[c]){
			nd+=(a[c]-nt)/v;
			v++;
			nt=a[c++];
		}
		nt+=(b[i+1]-nd)*v;
		v++;
	}
	if(nt+0.5>=(int)nt+1)
		nt=(int)nt+1;
	else
		nt=(int)nt;
	printf("%.0lf",nt);
	return 0;
}
```



---

## 作者：Starria的脑残粉 (赞：1)

```cpp
//这个难度有毒啊其实是一道pj难度的模拟题
#include<bits/stdc++.h>
using namespace std;
int n,x,n1,n2,l,r;
double a[100000],b[100000],y,z;
char c;
int main(){
    ios::sync_with_stdio(false);
    cin>>n;
    for (int i=1;i<=n;i++){
            cin>>c>>x;
            if (c=='T')a[++n1]=x;
                else b[++n2]=x;
        }
    sort(a+1,a+1+n1);sort(b+1,b+1+n2);
    x=1;l=1;r=1;//x 1/速度，y 路程，z 时间 
    for (int i=1;i<=n;i++)//然后是大力模拟拉
        if ((r>n2||(b[r]-y)*x+z>=a[l])&&(l<=n1)){
                if ((a[l]-z)/x+y>1000)break;
                y+=(a[l]-z)/x;z=a[l];x++;l++;
            }
            else{
                if (b[r]>1000)break;
                z+=(b[r]-y)*x;y=b[r];x++;r++;
            }
    cout<<int((1000-y)*x+z+0.499999)<<endl;//输出貌似是取整数部分的所以要四舍五入
}
```

---

## 作者：yxy666 (赞：0)

这道题应该还算蓝题中比较水的一道吧。

想法：把按时间减速的分为一类，按米数减速的分为一类，然后从小到大拍一趟序，一趟 $o(n)$ 的扫描。既然我们已经减速了，在下一次减速之前一直都是按照这个速度前进，那就可以直接得出：路程除以速度等于时间。然后是一个类似于毛毛虫的贪心，哪个离我现在近就先到哪个的位置。注意：剩下还有些零头要以最后的速度算掉。

 $code$ :
 ```
#include<bits/stdc++.h>
#define maxn 10005
#define db double
using namespace std;
int n,tt,dd,fm=1,t[maxn],d[maxn];
db ans,now_t,now_d;
int read(){
	int cnt=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
	while(isdigit(ch)) cnt=cnt*10+ch-'0',ch=getchar();
	return cnt*f;
}
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		char ch=getchar();
		while(ch!='T'&&ch!='D') ch=getchar();
		ch=='D'?d[++dd]=read():t[++tt]=read();
	}
	d[++dd]=1000;
	sort(t+1,t+1+tt);
	sort(d+1,d+1+dd);
	int i=1,j=1;
	while(i<=tt||j<=dd){
		if(now_d>=1000) break;
		db temp=now_d+(db)((db)t[i]-now_t)/fm;
		if((temp<d[j]&&i<=tt)||(j>dd)) now_d=temp,now_t=t[i],i++,fm++;
		else now_t=now_t+(d[j]-now_d)*fm,now_d=d[j],j++,fm++;
		ans+=now_t;
	}
	printf("%.lf",now_t);
	return 0; 
}

```


---

## 作者：Dzhao (赞：0)

## 题解 P2338
其实这是一道数学题&模拟题，想到怎么去做就很简单了（那肯定的）

让我们来看一下这道题

仔细发现，($1<=n<=10000$)

知道$O(n^2)$的算法应该过不了

QwQ我太菜了，$O(n^2)$都不会敲

---------------------------------------------------我是~~超级可爱的~~分割线----------------------------------------------------

注：D表示D x存下来的数组，T表示T x存下来的数组

我们可以for循环一遍他某个时间变换速度的情况，然后用一个指针从D数组开始往右移，并且不停更改从当前这个D是否在T后面，代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=10009;
int a[N],b[N],n,m;

int main()
{
	char ch;
	int T;
	cin>>T;
	while(T--)
	{
		cin>>ch;
		if(ch=='T') scanf("%d",&a[++n]);
		if(ch=='D') scanf("%d",&b[++m]);
	}
	sort(a+1,a+n+1); //按时间排序 
	sort(b+1,b+m+1); //按距离排序 
	double s=0,t=0;
	int j=1,sp=1;
	for(int i=1;i<=n;i++)
	{
		double tmp=s+(a[i]-t)*1.0/sp; //统计当前所在时间到a[i]这个时间所走到的位置 
		while(b[j]<tmp && j<=m) t+=(b[j]-s)*sp,sp++,s=b[j++],tmp=s+(a[i]-t)*1.0/sp; //不停更新从b[i]这个位置的时间点开始到a[i]所走到的位置 
		s+=(a[i]-t)*1.0/sp,t=a[i],sp++; //到a[i]时刻 
	}
	while(j<=m) t+=(b[j]-s)*sp,s=b[j++],sp++; //把最后还未统计完的距离加入 
	if(s<1000) t+=(1000-s)*sp; //如果仍然未到终点，就走到终点 
	printf("%.0lf\n",t); //四舍五入输出答案 
	return 0;
}
```


---

## 作者：zhangbubu (赞：0)

兄弟们，这是一道模拟题。
如果只ac第一个点的同学请看一下有没有将时间和位置**排序**


啊啊啊我因为没有排序调了一上午woc！

既然是模拟题我们只需要理解题意就行了。
看注释。
```cpp
#include"bits/stdc++.h"
using namespace std;


int main()
{
    int n;
    int t[20000],d[20000];
    cin>>n;
    char s;
    int tott=0;int totd=0;
    for (int i=1;i<=n;i++)
    {
        cin>>s;
        if (s=='T') cin>>t[++tott];
        else cin>>d[++totd];

    }

    int fenmu=1;
    double dn=0;
    double xn=0.0;double tn=0.0;double vn=1.0;
    int topt=1;int topd=1;

    //tott(total time) 是全部的时间；
    //topt（top time）是现在处理到了哪个时间
    //totd和topd同理
    //xn：已经走的距离，vn：目前的速度，：tn：目前所用的时间

    while (xn<1000)//还没走到头嘛
     {
         if (topt<=tott&&topd<=totd)
          {
            double a=tn+(d[topd]-xn)/vn; //到达topd所指位置的时间
           double b=t[topt];//到达topt所指时间的时间

           if (a<b) tn+=(d[topd]- xn)/vn,xn=d[topd],vn=1.0/(++fenmu),topd++; //先到到topd所指的位置

           else if (a<b) xn=xn+(t[topt]-tn)*vn,tn=t[topt],vn=1.0/(++fenmu),topt++;//先到达topt所指的时间

            else xn=d[totd],tn=t[topt],vn=1.0/(fenmu+2),fenmu=fenmu+2,topt++,topd++; //题目说的同时到达

    }
        else if (topt<=tott)//只剩下在某个时间出错
              {
                  xn+=vn*(t[topt]-tn);
                  tn=t[topt];
                  vn=1.0/(++fenmu);
                  topt++;

              }

        else if(topd<=totd)  //只剩下在某个位置出错   
             {

                tn+=(d[topd]-xn)/vn;xn=d[topd];
                vn=1.0/(++fenmu);
                topd++;

              }

        else // 没有出错的地方了，直接走到头就行了
            {

                tn+=(1000-xn)/vn;
                xn=1000;

             }

     }

    cout<<(int )(tn+0.5);//四舍五入
 }
```

---

## 作者：luaddict (赞：0)

其实这道题不是很难，主要是越界和判断的问题。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int t[10001],d[10001];
int main()
{
    int n,i,j,v=1,p=1,v1,p1;
    double k=1,a,b,g=0,kk=0,o=2;
    char c;
    cin>>n;
    for(i=1;i<=n;i++)
    {
        cin>>c;
        if(c=='T')
        {
            scanf("%d",t+v);
            v++;
        }
        else
        {
            scanf("%d",d+p);
            p++;
        }
    }
    sort(t+1,t+v);
    sort(d+1,d+p);
    v1=v-1;
    p1=p-1;
    v=1;
    p=1;
    for(i=1;i<=n;i++)
    {
        if((t[v]-g)*k<(d[p]-kk)&&v<=v1||p1<p)
        {
            kk+=(t[v]-g)*k;
            g=t[v];
            v++;
            k=1/o;
            o++;
        }
        else if((t[v]-g)*k==(d[p]-kk)&&p<=p1&&v<=v1)
        {
            g=t[v];
            kk=d[p];
            p++;
            v++;
            i++;
            k=1/(o+1);
            o+=2;
        }
        else//越界处理
        {
            g+=(d[p]-kk)/k;
            kk=d[p];
            p++;
            k=1/o;
            o++;
        }
    }
    g+=(1000-kk)/k;
    printf("%.lf",g);
}
```

---

