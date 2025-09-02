# Far Relative’s Problem

## 题目描述

Famil Door wants to celebrate his birthday with his friends from Far Far Away. He has $ n $ friends and each of them can come to the party in a specific range of days of the year from $ a_{i} $ to $ b_{i} $ . Of course, Famil Door wants to have as many friends celebrating together with him as possible.

Far cars are as weird as Far Far Away citizens, so they can only carry two people of opposite gender, that is exactly one male and one female. However, Far is so far from here that no other transportation may be used to get to the party.

Famil Door should select some day of the year and invite some of his friends, such that they all are available at this moment and the number of male friends invited is equal to the number of female friends invited. Find the maximum number of friends that may present at the party.

## 说明/提示

In the first sample, friends $ 3 $ and $ 4 $ can come on any day in range $ [117,128] $ .

In the second sample, friends with indices $ 3 $ , $ 4 $ , $ 5 $ and $ 6 $ can come on day $ 140 $ .

## 样例 #1

### 输入

```
4
M 151 307
F 343 352
F 117 145
M 24 128
```

### 输出

```
2
```

## 样例 #2

### 输入

```
6
M 128 130
F 128 131
F 131 140
F 131 141
M 131 200
M 140 200
```

### 输出

```
4
```

# 题解

## 作者：zhangruozhong (赞：2)

### 题意简述:

想邀请好朋友聚次会，时间待定，现已知每位朋友的性别及该年其在哪段时间内空闲，现想使聚会的朋友尽可能多但男女数量要相等，求最多可邀请几位好友前来聚会。

### 题目分析:

显然此题是要求最多次重复的区间，并且在这个重复的区间内，男性的人数等于女性的人数，这样一来，我们就可以对一年中的每一天进行扫描，判断当天所包含的两类区间的数量，取两类中的最小值，并遍历一遍进行比较，输出最大值乘以二即可。

  
### Code :

```
#include<bits/stdc++.h>
#define MAX 5005
#define INF 0x3f3f3f
using namespace std;
int main(){
    int n,j,i,t;
    char op[3];
    scanf("%d",&n);
	int m[MAX],f[MAX];
    int beg,end;
    memset(m,0,sizeof(m));
    memset(f,0,sizeof(f));
    for(i=1;i<=n;i++){  //扫描
        scanf("%s%d%d",op,&beg,&end);
        if(op[0]=='M')
            for(j=beg;j<=end;j++)
                m[j]++;
        else
            for(j=beg;j<=end;j++)
                f[j]++;
    }
    int sum=-INF;
    int F,M;
    F=M=0;
    for(i=1;i<=366;i++)
        sum=max(sum,min(m[i],f[i])); //取最大值
    printf("%d\n",sum*2);
    return 0;
}
```


---

## 作者：封禁用户 (赞：2)

题目传送>>[CF629B](https://www.luogu.com.cn/problem/CF629B)  
### 题意简述：  
- 想邀请好朋友聚次会，时间待定，现已知每位朋友的性别及该年其在哪段时间内空闲，现想使聚会的朋友尽可能多但男女数量要相等，求最多可邀请几位好友前来聚会。  
- $1 \le n \le 5000$，$1 \le a_i \le b_i \le 366$。
  
### 题目分析:  
该题即求该年中同一天空闲的男性、女性朋友组对最多的那天可组上对的男性、女性朋友数量，我们可以分别记录每天空闲的男性、女性朋友数（使用两个数组），其当天可组对数即当天空闲男性、女性朋友数中较小那个，然后再对每天可组对数进行比较，取其最多的那天作为聚会日期，邀请的朋友数即当天可组对数乘 $2$。  
### Code:  
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int m[366]={0},wm[366]={0};   //开两个数组分别记录该年每天空闲的男性、女性朋友数并初始化
int main()
{
	//freopen("friend.in","r",stdin);   //定义输入文件名
	//freopen("friend.out","w",stdout);   //定义输出文件名
	ios::sync_with_stdio(0);   //关同步流加速cin输入和cout输出
	int n,begin,end;   //定义总朋友数、每位朋友该年空闲日期起始和结束
	char gender;   //定义每位朋友的性别
	int minb=100000000,maxe=-100000000,ans=0;   //定义朋友的最早空闲起始日和最晚空闲结束日并以极值初始化（避免遍历该年每一天），需邀最多朋友数
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>gender>>begin>>end;
		minb=min(minb,begin);   //朋友的最早空闲起始日
		maxe=max(maxe,end);   //朋友的最晚空闲结束日
		for(int j=begin;j<=end;j++)
		{
			if(gender=='M') m[j]++;   //如为男性则在当天空闲男性数累加
			else wm[j]++;   //如为另一性别－－女性，则在当天空闲女性数累加
		}
	}
	for(int i=minb;i<=maxe;i++)   //从朋友的最早空闲起始日到最晚空闲结束日间遍历
	{
		ans=max(ans,min(m[i],wm[i]));   //求该年空闲男性、女性朋友组对最多那天的对数
	}
	ans*=2;   //需邀朋友数为对数两倍
	cout<<ans;
	//fclose(stdin);fclose(stdout);   //关闭文件
	return 0;   //结束整个程序
}
```
### 结果（未吸氧）:  
![JieGuo](https://cdn.luogu.com.cn/upload/image_hosting/14sat864.png)  
企鹅的题解到此结束，祝各位 OIers 进步 ++~

---

## 作者：Light_az (赞：1)

## 暴力

~~怎么天天写暴力~~，这道题的范围非常小，只有 $366$，那么我们统计一下 $1$~$366$ 这几天分别能有多少人参加，再循环跑一遍。当然我们要统计男女生的人数。如果人数相同，取最大值，但是当男女生人数不同时，为了让他们相同，我们只能取其中的最小值，比如：当男生有 $3$ 人，女生有 $4$ 人时，我们要拒绝 $1$ 位女生，才能保证男女生人数相同。最后记得人数要乘 $2$，因为有男女两种人。下面是完整代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,cnt=0;
int l,r;
char s;
struct num{
	int man,woman;
}a[405];//记录当天男女生数量 
int main(){
	cin>>n;
	for(int i=1;i<=366;i++){//清空 
		a[i].man=0;
		a[i].woman=0;
	}
	for(int i=1;i<=n;i++){
		cin>>s>>l>>r;
		for(int j=l;j<=r;j++){//赋值 
			if(s=='M')
				a[j].man++;
			else
				a[j].woman++;
		}
	}
	for(int i=1;i<=366;i++){//枚举暴力 
		if(a[i].man==a[i].woman){//男女生相同 
			cnt=max(a[i].man*2,cnt);//取最大值 
		}
		else{
			cnt=max(min(a[i].man,a[i].woman)*2,cnt);//取人数较少的性别的人数 
		}
	}
	//人数一定要乘2 
	cout<<cnt;
	return 0;
}
```


---

## 作者：smyslenny (赞：1)

**Solution**

题意很好理解，就是求 $2\times\max_{pepol}(\min(man,woman))$ ，找男人女人个数的较小值最大的那一天。

看到有的题解中是直接暴力加，这样过是可以过，但是我们还是考虑优化一下，我们这里可以用差分标记区间加，表示这个区间加上一个人有空闲时间的人。

不会差分的可以看[这里](https://www.cnblogs.com/xbhog/p/14348830.html)，学习完后这道题就非常简单了。


我们设 $Sum$ 来表示差分数组，记录修改的时候直接 $Sum_l+1$，$Sum_{r+1}-1$ ,这可以在读入的时候直接处理。

同时记录一个最大值 $Max$ 表示最远可以再那一天有空闲，这样我们就不用了枚举 $366$ 天了。

最后直接前缀和分别计算当天男和女的值，取一个较小值与当前答案比较，最后答案加倍，因为问的是人数不是对数。

**Code**

个人感觉简单易懂。

```c++
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <cstdlib>

using namespace std;

int n;

int read()
{
	int x=0,y=1;
	char c=getchar();
	while(c<'0' || c>'9') {if(c=='-') y=0;c=getchar();}
	while(c>='0' && c<='9') { x=x*10+(c^48);c=getchar();}
	return y?x:-x;
}

int Man[M],Woman[M],Max,Ans,Ans_1,Ans_2;


int main()
{
	n=read();
	for(int i=1,l,r;i<=n;i++)
	{
		char op;
		cin>>op;l=read(),r=read(),Max=max(Max,max(l,r));
		if(op=='M')//差分
			Man[l]++,Man[r+1]--;
		else
			Woman[l]++,Woman[r+1]--;
	}
	for(int i=1;i<=Max;i++)//前缀和
	{
		Ans_1+=Man[i],Ans_2+=Woman[i];
		Ans=max(Ans,min(Ans_1,Ans_2));
	}
	printf("%d\n",Ans<<1);
	return 0;
}

```


---

## 作者：wangkangyou (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF629B)

~~新手专享，dalao勿喷~~

## 简述一下题意：
一个数轴，上面覆盖着 $A,B$ 两种区间；求数轴上某一个点，使它所覆盖到的 $A,B$ 区间数量的 $\min(Sum_A , Sum_B) \times 2$ 的值最大。**（注意一定要乘以 2。）**

由于 $A,B$ 区间的左端点和右端点值均小于 $366$，我们可以采用桶的方法。但是，我们如何统计呢？

![](https://cdn.luogu.com.cn/upload/image_hosting/zgvwimg9.png)

如上图，我们可以对与每个区间，在桶上累加一遍。但是，由于 $A$ 类区间和 $B$ 类区间是需要分开讨论的，我们可以开两个数组记录。像上图中数轴上面的标记那样。

这样一来，我们就可以对一年中的每一天进行扫描，判断当天所包含的 $A,B$ 类区间的数量，取两类中的最小值，并打一遍擂台进行比较，输出最大值乘以二即可。**注意：一定要乘以 2！！** (因为比较的是 $A,B$ 相等，真正的包含数量实际上是两倍)。

上代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int read(){//快读快写
   int sum=0,f=1;
   char ch=getchar();
   for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
   for(;isdigit(ch);ch=getchar()) sum=(sum<<3)+(sum<<1)+(ch^48);
   return sum*f;
}
void write(int x){
   if(x<0) putchar('-'),x=-x;
   if(x>9) write(x/10);
   putchar('0'+x%10);
   return;
}
const int inf=1e10;
const int N=1e6+10;
struct node {//结构体
	int p,l,r; //分别是属于哪类区间、左端点、右端点
} a[N];
int v[N][2];
signed main(){
   int n = read ();
   char ch;
   for (int i = 1; i <= n; ++ i){
      ch = getchar ();//这里用了一个小技巧，把字母转换成数字，然后开在同一张表上，方便比较
      a[i].p = ch == 'F' ? 0:1;
      a[i].l = read ();
      a[i].r = read ();
   }
   for (int i = 1; i <= n; ++ i){
      for (int j = a[i].l; j <= a[i].r; ++ j){
         v[j][a[i].p] ++;//统计两类区间的数量
      }
   }
   int maxn = 0;
   for (int i = 0; i <= 366; ++ i){
      maxn = max (maxn, min(v[i][0], v[i][1]));//再统计最大值
   }
   write (maxn * 2);//一定要乘以二！！！
   return 0;
}

```
本蒟蒻第一篇题解，不喜勿喷，管理大大求过。

---

## 作者：wangyi_c (赞：0)

[你谷题目传送门](https://www.luogu.com.cn/problem/CF629B)

[CF题目传送门](http://codeforces.com/problemset/problem/629/B)

## 1.题目大意

给出我们 $n$ 个人的空闲时间区间和性别，问在这些时间内，那一天举办聚会男女数量相等并且参加人数最多（假设有空的人都会来）。

## 2.思路讲解

其实我们只需要分类来思考：如果这个人是男的，那么他空的时间内每个日子男生数量都要加一；如果这个人是女的，那么他空的时间内每个日子女生数量都要加一。然后我们找出最开始有人空的日子和最后有人空的日子，进行一波枚举，当天参加聚会最多的人数便是**男生女生当天空的人数取最小值再乘二**。最后对这些日子能参加的人数取个最大值就行了。

## 3.AC 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int ans=-1e18;//答案
int start=1e18,finish=-1e18;//最开始和最末尾
char xingbie;
int b,e,n,day_w[400],day_m[400];//当天男生的数量和女生的数量
signed main(){
	cin>>n;
	while(n--){
		cin>>xingbie>>b>>e;
		start=min(start,b);
		finish=max(e,finish);		
		for(int i=b;i<=e;i++){//枚举这个人当前空的日子
			if(xingbie=='M'){
				day_m[i]++;//男生数量加一
			}
			else day_w[i]++;//女生数量加一
		}
	}
	for(int i=start;i<=finish;i++){//从最开始到最末尾
		ans=max(ans,min(day_w[i],day_m[i]));//男生女生取最小值后取最大值
	}
	ans*=2;//乘二别忘了
	cout<<ans;
	return 0;
}
```
_THE END_

谢谢观看

By wangyi

---

## 作者：cxy000 (赞：0)

题目解析：

其实这道题个人感觉和校门外的树有点相像。

首先我们要明确最大区间（即最早的开始时间和最晚的结束时间），分别用两个变量存储。

再分别循环开始和结束时间，并标记男女的记号。

在同一时间，为了让男女数量相等，我们应该取男女中赴会者较少的一个。

注意：输出答案时可能要乘以 $2$。

没有什么坑了。

上代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int maxx,minn=1e9;
char c[1000100];
int a[1000100],b[1000100];
int m[1000100],w[1000100];
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>c[i]>>a[i]>>b[i];
		minn=min(a[i],minn);
		maxx=max(b[i],maxx);
		for(int j=a[i];j<=b[i];j++){
			if(c[i]=='F') m[j]++;
			else w[j]++;
		}
	}
	int ans=0;
	for(int i=minn;i<=maxx;i++){
		ans=max(ans,min(m[i],w[i]));
	}
	cout<<ans*2;
	return 0;
}
```


---

## 作者：Sternenlicht (赞：0)

思路：

读入时，$man_j$ 和 $woman_j$ 分别记录第 $x$ 天能来参加聚会的男性个数和女性个数。

再记录一个最小开始时间 minbegin 和一个最大结束时间 maxend，求答案时在 minbegin ~ maxend 这个时间段找，看哪天能来的人数最多，就记录。

注意要 $\times 2$，因为我们求的是最多有几对男女，而题目要求共有多少人。

```cpp
#include <bits/stdc++.h>
#define LL long long
#define INF 0x3f3f3f3f
//快读快写 
namespace IO{
	inline LL read(){
	    LL x=0,f=1;char ch=getchar();
	    for (;!isdigit(ch);ch=getchar())if (ch=='-')f=-1;
	    for (;isdigit(ch);ch=getchar())x=(x<<3)+(x<<1)+(ch^48);
	    return x*f;
	}
	inline void write(LL x,char c='\n'){
	    if (x){
	    	if (x<0)x=-x,putchar('-');
	    	char a[30];short l;
	    	for (l=0;x;x/=10)a[l++]=x%10^48;
	    	for (l--;l>=0;l--)putchar(a[l]);
		}
		else putchar('0');putchar(c);
	}
	inline char getc(){
		char ch=getchar();
		while (isspace(ch))ch=getchar();
		return ch;
	}
}
using namespace IO;
using namespace std;

const int N = 5e3+10;
//man记录第x天能来的男性个数，woman记录第x天能来的女性个数 
int n,man[N],woman[N],ans;//ans记录共有几人参加聚会 
int minbegin,maxend;//minbegin为最小开始时间，maxend为最大结束时间 
int main(){
	n=read();
	for (int i=1;i<=n;i++){
		char ch=getc();int a=read(),b=read();//如题意 
		minbegin=min(minbegin,a);//求最小开始时间
		maxend=max(maxend,b);//求最大结束时间
		for (int j=a;j<=b;j++)//记录在这个时间段内，有几人能参加 
			if (ch=='M')man[j]++;//第j时间有几位男性可以参加聚会
			else woman[j]++;//第j时间有几位女性可以参加聚会 
	}
	//从最小开始时间枚举至最大结束时间，在哪个时间段人最多 
	for (int i=minbegin;i<=maxend;i++) 
		ans=max(ans,min(man[i],woman[i])*2);//使最少的男女对数最多
	write(ans); 
    return 0;
}
```

---

## 作者：lrmlrm_ (赞：0)

# 题意

小白想要邀请 $ n $ 个朋友 ， 已知他们的性别 $ c_i $ , `M` 代表男生 ， `F` 代表女生 ， 且这些朋友在 $ a_i $ 到 $ b_i $ 天有时间 。

小白希望参加的朋友的男女数量刚好相等 ， 且能参加的人数越多越好 。 当然为了男女人数相等 ， 他也可以婉拒其中的某些人 。 请计算最多有多少个朋友可以参加 。

# 思路

使用两个数组 $ f_i $ 和 $ m_i $ , 分别表示有多少个女生和男生在第 $ i $ 天有时间 。

然后从 $ 1 $ 到 $ 366 $ ， 一天一天的找出每天男生和女生中人数最少的一种性别的人数 ， 把它 $ \times 2 $ 后取 $ \min $ 即可 。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,b,ma,f[5010],m[5010];
char c;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        cin>>c;
        scanf("%d%d",&a,&b);
        if(c=='F')
		   for(int i=a;i<=b;i++)
				f[i]++;
        if(c=='M')
			for(int i=a;i<=b;i++)
				m[i]++;
    }
    for(int i=1;i<=366;i++)
        f[i]=min(f[i],m[i]),ma=max(f[i]*2,ma);
    printf("%d",ma);
    return 0;
}
```

---

## 作者：alex_liu (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF629B)

## 思路：
大模拟水题，枚举男和女可以参加派对的时间就行了。

## AC 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
char ch;
int n,ans=-1,x,y,men[1500],women[1500];//定义 men[i] 为第 i 天可参加的男生人数， women[i] 为第 i 天可参加的女生人数
int main(){
	cin>>n;//输入
	for(int i=1;i<=n;i++){
		cin>>ch>>x>>y;//输入 
		if(ch=='M'){//男 
			for(int i=x;i<=y;i++)men[i]++;//第 i 天的男生可参加人数 +1 
		}else{//女 
			for(int i=x;i<=y;i++)women[i]++;//第 i 天的女生可参加人数 +1 
		}
	}
	for(int i=1;i<=366;i++)ans=max(ans,min(men[i],women[i])*2);//枚举天数求可参加人数，想一下为什么这里要求最小值然后 *2
	cout<<ans<<endl;//输出
	return 0;//完美结束
} 
```

## 思考题：

因为男女人数要相等，也就是一一匹配（设男生人数为 $n$ ，女生人数为 $m$ ）

所以能匹配的对数为： $\min(m,n)$ 

那么可参加的人数就是： $\min(m,n)\times2$

---

## 作者：江山_远方 (赞：0)

本题可以按照数据模拟，由于数据较小，可以暴力循环统计每一天能来多少男的和多少女的，然后枚举每一天，看这一天最多能来多少人,最后输出最多人数  
注意!翻译有锅 虽然说是2019年，可是枚举天数时却要枚举366天！  
代码:
```cpp
#include<bits/stdc++.h>
using namespace std;
char ch;
int n,ans,x,y;
int men[1100],women[1100];//定义
int main()
{
	cin>>n;//读入
	for(int i=1;i<=n;i++)
	{
		cin>>ch;
		scanf("%d%d",&x,&y);//枚举每一天，这天Ta能来
		for(int i=x;i<=y;i++)
		if(ch=='M')men[i]++;
		  else women[i]++;
	}
	for(int i=1;i<=366;i++)ans=max(ans,min(men[i],women[i])*2);//求出最大人数
	cout<<ans;//输出
	return 0;
} 
```

---

## 作者：codemap (赞：0)

很水的一道橙题,暴力都能过...

我用了一种最无脑的方法:

开一个结构体存每个日期有几个男性能来和几个女性能来

然后输入的时候从看是日期到结束日期逐个个数++

最后算一下那个日期的min(男性个数,女性个数)*2

上代码
```cpp
#include<iostream>
using namespace std;
struct node//结构体
{
    int f;//能来男性个数
    int m;//能来女性个数
}a[367];//366+1
int main()
{
    int n,i,j,x,y,mmax=0;
    char c;
    cin>>n;
    for(i=1;i<=366;i++)//结构体全部赋零
    {
        a[i].f=0;
        a[i].m=0;
    }
    for(i=1;i<=n;i++)
    {
        cin>>c>>x>>y;//输入
        for(j=x;j<=y;j++)//从开始日期到结束日期遍历
        {
            if(c=='F')//如果是男的
                a[j].f++;//男性个数++
            else//否则
                a[j].m++;//女性个数++
        }
    }
    for(i=1;i<=366;i++)//遍历每天
        mmax=max(mmax,min(a[i].f,a[i].m)*2);//取最大值
    cout<<mmax;//输出
    return 0;//完美结束
}
```
# 请勿抄袭

---

