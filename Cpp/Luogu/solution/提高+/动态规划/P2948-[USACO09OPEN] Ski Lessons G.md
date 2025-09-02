# [USACO09OPEN] Ski Lessons G

## 题目描述

农夫约翰想带贝西去科罗拉多滑雪。不幸的是，贝西滑雪技术并不是很好。

贝西了解到滑雪场全天提供 S (0 \le S \le 100) 节滑雪课。第 i 节课从时间 M\_i (1 \le M\_i \le 10,000) 开始，持续时间为 L\_i (1 \le L\_i \le 10,000)。在第 i 节课后，贝西的滑雪能力变为 A\_i (1 \le A\_i \le 100)。注意：这种能力是绝对值变化，而不是增量变化。

贝西购买了一张地图，上面显示了所有 N (1 \le N \le 10,000) 条滑雪道，以及滑下第 i 条滑雪道所需的时间 D\_i (1 \le D\_i \le 10,000) 和安全滑下该滑雪道所需的技能水平 C\_i (1 \le C\_i \le 100)。贝西的技能水平必须大于或等于滑雪道的技能水平，才能安全滑下。

贝西可以把时间花在滑雪、上课或喝热可可上，但必须在时间 T (1 \le T \le 10,000) 前离开滑雪场，这意味着她必须在不超过该时间限制的情况下完成她最后一条滑雪道的滑行。

找出贝西在时间限制内可以完成的最大滑雪次数。她一天开始时的技能水平为 1。

前 50 次提交将提供额外反馈。



## 说明/提示

滑第二条滑雪道一次，上课，然后在时间用完前滑第一条滑雪道 5 次：总共 6 条滑雪道。
（由 ChatGPT 4o 翻译）

## 样例 #1

### 输入

```
10 1 2 
3 2 5 
4 1 
1 3 
```

### 输出

```
6 
```

# 题解

## 作者：Twilight_ (赞：20)

观察题目，发现上一节滑雪课所造成的影响就是在这节课结束，和要上的下节课之间的时间空隙中可以滑多少次雪。

很自然地可以联想到枚举所上的课和上这节课之前所上的课。


代码变量解释：

建立状态：dp[i][j]:表示i时刻，j能力值所能滑雪的最大次数；

sl[i]:表示能力值为i时，滑一次雪所需的最小时间；

les[i].co/.st/en:第i节课的能力值/开始时刻/结束时刻；


状态转移方程：

1.dp[x][y]=max(dp[x][y],dp[x2][y2]+q);这节课x时刻结束，能力值为y，上节课x2时刻结束，y2能力值，q表示在上一节课结束和这一节课开始之间一次滑雪的最小时间；

2.dp[x][y2]=dp[x2][y2]+(x-x2)/sl[y2];这节课x时刻结束（但并没有上这节课），上节课x2时刻结束，y2能力值，q表示在上一节课结束和这一节课结束之间一次滑雪的最小时间；


```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxs 170
int t,s,n,tem,tem2,tem1,ans,sl[10050],dp[20000][maxs];
struct xxx
{
    int st,en,co;
}les[maxs];
bool cmp(xxx a,xxx b)
{
    return a.en<b.en;
}
int main()
{
    cin>>t>>s>>n;
    for(int i=1;i<=s;i++)
    {
        scanf("%d%d%d",&les[i].st,&tem,&les[i].co);
        les[i].en=tem+les[i].st;
    }
    for(int i=0;i<=t+1;i++)sl[i]=999999;
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",&tem1,&tem2);
        sl[tem1]=min(sl[tem1],tem2);
    }
    for(int i=1;i<=t;i++)sl[i]=min(sl[i],sl[i-1]);    
    sort(les+1,les+1+s,cmp);
    les[0].co=1;les[0].st=0;les[0].en=0;
    for(int i=0;i<=s;i++)
        for(int j=0;j<i;j++)
        {
            int x=les[i].en,y=les[i].co,x2=les[j].en,y2=les[j].co;
            if(x2<les[i].st)
            {
                int q=sl[y2];
                q=(les[i].st-x2)/q;
                dp[x][y]=max(dp[x][y],dp[x2][y2]+q);
            }
            dp[x][y2]=max(dp[x][y2],dp[x2][y2]+(x-x2)/sl[y2]);
        }
    for(int j=0;j<=s;j++)
    {
        int y2=les[j].co,x2=les[j].en;
        if(dp[x2][y2]+(t-x2)/sl[y2]>dp[t][y2])dp[t][y2]=dp[x2][y2]+(t-x2)/sl[y2];
    }
    for(int i=0;i<=s;i++)if(dp[t][les[i].co]>ans)ans=dp[t][les[i].co]; 
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：ghj1222 (赞：13)

题解里面全是dp的大神本蒟蒻瑟瑟发抖奉上一篇记忆化搜索...

其实嘛，记忆化搜索还是很安全透彻清真人品的，一般递推不好实现dp可以用记忆化搜索

然后本题先预处理一个`mint[i]`代表当前能力值为`i`，参与滑雪的最小时间。一开始赋初值为$+\infty$，每当读入一个滑雪任务`(c,d)`后，把`[c,100]`区间内的数组对`d`去取一个min

然后就可以缩索了，`search(x,y)`返回当前时间为x，能力值为y滑雪最大次数。枚举所有课程，如果这个课程开始时间在x后面(或者就在x也就是$\ge x$，那么我们就用上这门课来更新本次答案，也就是`search(a[i].m + a[i].l, a[i].a)`。mla如题意。一个剪枝：当当前课程a小于等于当前能力值，选他一定不比不选他优，所以不用考虑。然后贪心地在当前时间x和课程开始时间内滑雪(用当前时间除以当前能力值能滑雪最短时间就是最大滑雪的次数)。

备注：数据貌似有一点水，不写记忆化tle两个点，不写记忆化开O2tle一个点。

```cpp
#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

struct course
{
    int m, l, a;
}a[110];

int mint[110];

int t, s, n, f[10010][110];

//记忆化缩索，表示在x时候能力值为y能滑雪最大数
int search(int x, int y)
{
    if(f[x][y] != -1)
        return f[x][y];
    f[x][y] = 0;
    for (int i = 1; i <= s + 1; i++)
        if(a[i].m >= x && a[i].a > y)
            f[x][y] = max(f[x][y], search(a[i].m + a[i].l, a[i].a) + (a[i].m - x) / mint[y]);
    return f[x][y];
}

int main()
{
    scanf("%d%d%d", &t, &s, &n);
    for (int i = 1; i <= s; i++)
    {
        scanf("%d%d%d", &a[i].m, &a[i].l, &a[i].a);
    }
    a[s + 1] = (course){t, 0, 101};
    memset(mint, 0x3f, sizeof(mint));
    for (int c, d, i = 1; i <= n; i++)
    {
        scanf("%d%d", &c, &d);
        for (int j = c; j <= 100; j++)
            mint[j] = min(mint[j], d);
    }
    memset(f, -1, sizeof(f));
    printf("%d\n", search(0, 1));
    return 0;
}
```

让我们一起膜拜大佬林瑞堂 @[olinr](https://www.luogu.org/space/show?uid=88460)

让我们一起膜拜搜索王@[ZAGER](https://www.luogu.org/space/show?uid=87967)

---

## 作者：A天天t (赞：4)

可以在纸上画一个平面直角坐标系，

用x轴代表时间，y轴代表所需要的能力

起始的点为（0，1）；// 即，开始的状态为：时间在0,能力为1，

然后只有三种移动方式

1.上课：斜向上（向右,+向上（时间增加，能力增加））移动，或斜向下移动（时间增加，能力减小）（但我们知道等级越大应该越好，因为可以选择的坡更多,可以加个剪枝节省时间，但我刚开始没想到，后来看了别人的题解才发现，不过此处不剪枝的话并不会超时）；

2.滑雪:向右移动（时间增加，能力不变）；伴随滑雪次数加1

3.sip hot cocoa:向右移动（为了节省时间，我们只移动一个单位,即喝一个时间单位的可可）；而且下一次我们仍然还向右移动，所以包含了喝任意单位时间的情况

# 最后，加上今天在百度百科，“动态规划”里看到的一句让自己博有感触的话:"除了要对基本概念和方法正确理解外，必须具体问题具体分析处理，以丰富的想象力去建立模型，用创造性的技巧去求解"





    

    
```cpp
uses math;
type
int=longint;
point=^node;
node=record
t,a:int;// time requried + ability can get 
ne:point;
end;
const
mt=100000;
ma=100;
var 
c:array[0..mt]of point;// 记录课程
i:point;
st:array[0..ma]of int; // 每种难度等级滑坡需要的时间
t,a,tt,sa,x,y,z,nc,ns,j,ans:int;
f:array[0..mt,0..ma] of int;
procedure com(st,t,a:int);
var 
i:point;
begin 
i:=c[st];
new(c[st]);
c[st]^.t:=t;
c[st]^.a:=a;
c[st]^.ne:=i;
end;
begin 
readln(tt,nc,ns);
for j:=1 to nc do 
    begin 
        readln(x,y,z);
        com(x,y,z);
    end;
for j:=1 to ns do
    begin 
    readln(a,y); 
    if st[a]<>0 then 
        st[a]:=min(st[a],y)// 每个难度要求的滑坡，取消耗时间最短的，贪心
    else st[a]:=y;
    end;
fillchar(f,sizeof(f),$9f);
f[0,1]:=0;
for t:=0 to tt do // time line
    begin 
    for a:=1 to 100 do // ability line
        begin 
        // have class
        i:=c[t];//class begins at t
        while i<>nil do 
            begin 
                f[t+i^.t,i^.a]:=max(f[t+i^.t,i^.a],f[t,a]);// result is not changed
                i:=i^.ne; // next class;
            end;
        // ski slope i whose ability needed is under  present position(a=a); 
        for sa:=a downto 0 do 
            if st[sa]<>0 then // thie kind slope exists
                f[t+st[sa],a]:=max(f[t+st[sa],a],f[t,a]+1);// 
        // sip hot cocoa;
        f[t+1,a]:=max(f[t+1,a],f[t,a]);// just translate present condition /state
        end;
    end;
for a:=0 to 100 do 
    ans:=max(ans,f[tt,a]);
writeln(ans);
end.

```

---

## 作者：Illusory_dimes (赞：4)

不是我说

这道题
# 真好
一个直奔主题的dp
#### 说~~男~~难也~~男~~难
#### 说~~遗~~易也~~遗~~易
sum数组仿佛是将滑的久的拎走了似的,

方便在滑雪时省for与判断
###### ~~sum数组,你值得拥有~~
又因为f数组的能力有分100个

所以加一个ans数组表示···(见注释)

不仅在判断是否上课时省时间

也在输出时少一个for
###### ~~ans数组,你值得拥有~~
因此,上代码······
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=110,M=10101;
int t,s,n,f[M][N],sum[N],st[M][N],ans[M];
//f(i,j) 时刻为i,能力为j的最多滑雪次数
//sum(i) 至少能力为i的最短滑雪时间
//st(i,j)能力变为j的课中的最晚开始时间
//ans(i) i时刻的最多滑雪次数
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=getchar();
	return s*w;
}
int main()
{
	t=read(),s=read(),n=read();
	for(int i=1,m,l,a;i<=s;i++)
	{
		m=read(),l=read(),a=read();
		if(m>st[m+l-1][a])st[m+l-1][a]=m;
	}
	memset(sum,127,sizeof(sum));
	for(int i=1,c,d;i<=n;i++)
	{
		c=read(),d=read();
		for(int j=c;j<=100;j++)
		if(d<sum[j])sum[j]=d;
	}
	memset(f,128,sizeof(f));
	f[0][1]=ans[0]=0;
	for(int i=1;i<=t;i++)
	for(int j=1;j<=100;j++)
	{
		f[i][j]=f[i-1][j];//喝可可汁
		if(st[i-1][j])f[i][j]=max(f[i][j],ans[st[i-1][j]]);//上课
		if(i-sum[j]>=0)f[i][j]=max(f[i][j],f[i-sum[j]][j]+1);//滑雪
		if(ans[i]<f[i][j])ans[i]=f[i][j];
	}
	printf("%d",ans[t]);
	return 0;
}
```
初学者发题解,大佬勿喷

# 若有帮助，将是我莫大的荣幸

---

## 作者：clockwhite (赞：3)

# P2948 [USACO09OPEN]Ski Lessons G

# 前言

​	我已经很久很久，很久很久，没有只依靠自己想出一个DP了。开心。

# Solution

​		首先设计一下状态，$f_{i,j}$ 表示在时间 i ，能力值为 j 的时候能滑的最多场数。

​		接下来考虑在第 i 秒能干什么。有以下选项：

- 啥也不干，于是 $f_{i+1,j}$ 可以被 $f_{i,j}$ 更新

- 上一节课，$f_{i+L_k,A_k}$ 可以被 $f_{i,j}$ 更新，$k$ 为一个在 i 时间开始的课程。

- 滑一场雪，$f_{i+D_k,j}$ 可以被 $f_{i,j}$ 更新，$k$ 为一个滑雪场。

  ​	但是现在时间复杂度很显然不对，到达了 $O(TVN)$ 的级别，其中 $V$ 为能力值域。

  ​	问题在于枚举一个滑雪场过于冗杂。观察到一个滑雪场可以滑多次，这启发我们贪心，对于一切以当前能力值可以滑的场，总是从中选一个耗时最小的来滑。就可以省去枚举。

  ​	而这个耗时最小的场既可以用数据结构维护也可以提前预处理，此处我选择预处理，预处理时间复杂度为$O(NV)$,总的时间复杂度在 $O(VN+TV+VS)$, $VS$ 是因为每堂课会被枚举V次。

  ​	初始化为 $f_{0,1}=0$,其余负无穷。

  # CODE

  ```c++
  #define fe(i,a,b) for(int i=a;i<=b;++i)
  #define pii pair<int,int>
  #define mp(a,b) make_pair(a,b)
  const int inf=1e9;
  int t,s,n,minn[105],f[20005][105],ans;
  vector< pii > cl[10005];
  inline int M_min(int a,int b){return a<b?a:b;}
  inline int M_max(int a,int b){return a>b?a:b;}
  int main(){
  	t=read(),s=read(),n=read();
  	fe(i,0,100)minn[i]=inf;
  	fe(i,1,s){
  		int x=read(),y=read(),z=read();
  		cl[x].push_back(mp(y,z));
  	}
  	fe(i,1,n){
  		int c=read(),d=read();
  		fe(j,c,100)minn[j]=M_min(minn[j],d);
  	}
  	memset(f,-0x3f,sizeof(f));
  	f[0][1]=0;
  	fe(i,0,t){
  		int u=cl[i].size();
  		fe(j,0,100)if(f[i][j]>=0){
  			ans=M_max(ans,f[i][j]);
  			fe(k,0,u-1)f[i+cl[i][k].first][cl[i][k].second]=M_max(f[i][j],f[i+cl[i][k].first][cl[i][k].second]);
  			f[i+1][j]=M_max(f[i+1][j],f[i][j]);
  			if(i+minn[j]<=t)f[i+minn[j]][j]=M_max(f[i+minn[j]][j],f[i][j]+1);
  		}
  	}
  	printf("%d",ans);
  	return 0;
  }
  ```

  

---

## 作者：first_fan (赞：3)

### 本题考查的是基本$\small\color{darkturquoise}\text{状态转移方程的应用能力}$或者$\small\color{darkturquoise}\text{记忆化搜索能力}$。

#### 此处我来详细讲讲状态转移方程的推导。

第一步，题目告诉我们，一段时间的利用方式有三种：

* $\text{Drink Cocoa喝热可可}$~~睡觉~~
* $\text{Have Lessons训练}$
* $\text{Skiing滑雪}$

按照套路，先设$\large\text{ f [ i ][ j ] }$表示$i$时间内$j$能力时的最大滑雪次数。

接下来我们就三种情况来具体分析：

* 如果是睡觉，那么这无疑是效率最低的一种。但是在无法上课或者滑雪的情况下只选这一种。由于效率低下，它的**状态除了时间根本没有改变**。

即其能力不变，次数不变。

转移方程$1$:

$\text{f[i][j]=f[i-1][j]}$

* 如果是上课，那么可以推知，不管上不上课，上课前的滑雪次数是不变的（无后效性）。我们需要考虑的实际上即是上完这节课之后能滑多少次雪，不上这节课又能滑多少次雪。

此处我们考虑开一个$\text{ans[ i ]}$，表示$i$时间内最多的滑雪次数。所以答案就是输出$\text{ans[ end ]}\tiny\text{(end是闭馆时间)}$。

`那么这个数组怎么在过程中使用?`考虑上这节课之后的状态。

如果有一节课在$i$结束，效果为$effect$，那么我们把上课和不上课状态进行比较（必须在能力值相同的情况下）并取最优值。那么我们就需要记录效果为$effect$，结束时间为$i$的课程的开始时间，用$\_class$数组来记录：

$\text{\_class[i][effect]=st}$

即为转移方程$2$:

$\text{f[i][effect]=\{f[i][effect],ans[\_class[i][effect]\}}_{max}$

* 第三个，我们考虑滑雪。如果结束时间$i$足够一次能力值为$j$的滑雪的话，我们就滑滑看。我们此时又需要前面初始化另一个数组：$min\_t[j]$。这个数组是指在$j$能力值下的最短化学时间，比它时间长的我们就可以直接扔掉。

这时我们就可以由滑雪开始时间的次数$+1$推导现在的状态：

即为状态转移方程$3$:

$\text{f[i][j]=\{f[i][j],f[i-min\_t[j]][j]+1\}}$

综上所述，我们有状态转移方程组：

 $f[i][j]=\begin{cases}f[0][1]=0&start\\f[i-1][j]&do\ nothing\\(f[i][j],ans[\_class[i][j]])_{max}&have\ a\ lesson\\(f[i][j],f[i-min\_t[j]][j]+1)_{max}&ski\end{cases}$ 
 
 我们只要将$i$在时间$1-end$内循环,$j$在$1-100$间循环就够了。
 
 $UPDATE:$可以在初始化$min\_t$数组时加入剪枝：如果新场（需要更高能力）时间还长于当前低能力场时间，可以直接$break$。
 
 下面是代码，初始化$ans,min\_t,\_class,f,$就没有讲了，但有注释，~~希望不要被认为是走水~~。
 
 ```cpp
 #include <bits/stdc++.h>
#define ri register int
#define ll long long
using namespace std;
const int maxn=1125;
int f[maxn*10][maxn];//时间i内能力值为j的最多滑雪次数。
//1.drink cocoa
//2.have class
//3.ski
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
}//快读

struct lesson
{
	int st;//开课时间
	int len;//课时
	int effect;//上了课能力变成effect
} l[maxn];

bool cmp(lesson a,lesson b)//按照结束时间排序
{
	return (a.st+a.len)<(b.st+b.len);
}

int ans[maxn*10];//时间为i时的最大滑雪次数
int min_t[maxn*10];//当能力值为i时滑雪一次的最小时间
int _class[maxn*10][103];//到i结束的一堂课获得j能力的开始时间

int main()
{
	memset(f,2003,sizeof(f));//这个地方的memset不能赋127.
	memset(min_t,127,sizeof(min_t));//能力不够时什么都做不了
	int end=read();//dawn
	int cls=read();//class
	int n=read();//number of places
	for(ri i=1; i<=cls; i++) //class input
	{
		l[i].st=read();
		l[i].len=read();
		l[i].effect=read();
	}//读入lesson信息
	sort(l+1,l+cls+1,cmp);//排序
	for(ri i=1; i<=cls; i++)
	{
		int ed=l[i].st+l[i].len;//下课时间
		if(ed>=end)
		{
			break;
		}//从这里开始上课会上超时，直接去掉
		//假如结束时刚好上完，那么也是无意义的
		_class[ed][l[i].effect]=l[i].st;//到ed为止，能力值可以达到l[i].effect,开始时间是st
	}
	for(ri i=1; i<=n; i++)
	{
		int need=read();//进入此滑雪区的条件
		int _time=read();//当前滑雪场的时间
		for(ri j=need; j<=100; j++) //再怎么样能力值不超过100
		{
			if(_time>min_t[j])
			//如果高手区的时间比新手区的时间还长，直接不要
			{
				break;
			}
			min_t[j]=min(min_t[j],_time);//更新最短时间
		}
	}
	f[0][1]=0;//时间0，达到能力值1，滑雪0次.
	for(ri i=1; i<=end; i++)
	{
		for(ri j=1; j<=100; j++)
		{
			f[i][j]=f[i-1][j];//drink cocoa
			if(_class[i][j])//有这样的一堂课，结束时间是i，课程效果是j
			{
				f[i][j]=max(f[i][j],ans[_class[i][j]]);
				//更新答案，在一节课的开始时间前的滑雪次数或者不上课的滑雪次数。
			}
			if(i>=min_t[j])
			{
				f[i][j]=max(f[i][j],f[i-min_t[j]][j]+1);//滑雪一次
			}
			ans[i]=max(ans[i],f[i][j]);//更新ans
		}
	}
	return 0&printf("%d",ans[end]);
	//printf()函数是有返回值的(int型), 0&int = 0 ,所以可以这样
}
 ```
 
 反思小结：跑得较快($50ms^-$)。数组略多，但是理解难度较低。

---

## 作者：小塘空明 (赞：1)

~~我dp好弱啊。~~

用cl[i]表示能力为i时能滑的所需时间最小的坡。

将s节课程按照结束时间排序，注意将初始状态加入，其能力值设为1。

用dp[x][y]表示第x秒，能力为y所能滑雪的最多次数。

假设上一节学的课程的开始时间为i，其能得到的能力值为j。

如果i课程的结束时间小于当前课程的开始时间，说明我们在保证上了上一节课的前提下能上这节课，并且我们上这节课。我们可以用两节课之间的空余时间滑雪。

转移方程式dp[x][y]=max(dp[x][y],dp[i][j]+(x.st-i)/cl[j]);

如果我们不能上这节课,dp[x][j]=max(dp[x][j],dp[i][j]+(x-i)/cl[j]);

我们枚举最后上的一节课，用它去更新答案，dp[t][y]=max(dp[t][y],dp[x][y]+(t-x)/cl[y]);

ans=max(dp[t][y]);

---

## 作者：Yorathgz (赞：1)

预先处理出两个数组，ke[i][j] 表示变成j能力的课中的最晚开始时间，po[i]  表示至少需要能力为i的最短滑雪时间。


f[i][j]表示i时刻能力为j的最多滑雪次数，g[i]表示i时刻的最多滑雪次数。


然后直接O(100\*T)的dp即可，状态转移方程见代码。


```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
typedef long long ll;
inline ll read(){
    ll x=0,f=1;char ch=getchar();
    while(ch!='-'&&(ch>'9'||ch<'0')) ch=getchar();
    if(ch=='-') f=-1,ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return x*f;
}

int t,s,n;
const int maxa=105,maxt=1e4+4;
int f[maxt][maxa],g[maxt],ke[maxt][maxa],po[maxa];

int main(){
    t=read();s=read();n=read(); 
    
    //处理ke数组 
    for(int i=1,m,l,a;i<=s;i++){
        m=read();l=read();a=read();
        ke[m+l-1][a]=max(ke[m+l-1][a],m);
    }
    
    //处理po数组 
    memset(po,0x3f,sizeof(po));
    for(int i=1,c,d;i<=n;i++){
        c=read();d=read();
        for(int j=c;j<=100;j++)
            po[j]=min(po[j],d);
    }
    
    memset(f,128,sizeof(f));
    f[0][1]=g[0]=0;
    for(int i=1;i<=t;i++){
        for(int j=1;j<=100;j++){
            f[i][j]=f[i-1][j]; //喝可可汁结束
            if(ke[i-1][j]) f[i][j]=max(f[i][j],g[ke[i-1][j]]); //上课结束
            if(i-po[j]>=0) f[i][j]=max(f[i][j],f[i-po[j]][j]+1); //滑雪结束
            g[i]=max(g[i],f[i][j]);
        }
    }
    printf("%d\n",g[t]);
    return 0;
}
```

---

## 作者：fighter_OI (赞：1)

来一波记忆化搜索……

思路同楼上，

f[i][j]表示i时刻能力值为j的最大滑雪数

显然f[0][1]=0,开始搜索

三种转移：

①美美的喝上一杯**：f[i+1][j]=max(f[i+1][j],f[i][j])

②滑雪，f[i+当前能力值所能滑雪最短时间][j]=max(f[i+当前能力值所能滑雪最短时间][j],f[i][j])

③上课，对于所有i时刻开始的课，f[i+该课所需时间][该课达到能力值]=max(f[i+该课所需时间][该课达到能力值],f[i][j])

##一个小剪枝：不会上小于等于当前能力值的课

#应当先搜索滑雪的情况，否则会tle掉两个点

上代码：

```cpp
#include<stdio.h>
#define max(a,b) ((a>b)?a:b)//求最大值
#define min(a,b) ((a<b)?a:b)//求最小值
int t,s,n,m,l,a,tot=0,w[10001],dd[200],f[10001][101],ans=0,c,d;
struct les
{
    int l,a,next;
}g[200];
void add(int m,int l,int a)//加入m时刻开始持续l时刻得到能力值a的课程
{
    tot++;
    g[tot].l=l;
    g[tot].next=w[m];
    g[tot].a=a;
    w[m]=tot;
}
void dfs(int k,int p,int sum)//记忆化搜索
{
    f[k][p]=sum;//存储当前答案
    if(k+dd[p]<=t)if(f[k+dd[p]][p]<sum+1)//如果可以滑雪
    {
        dfs(k+dd[p],p,sum+1);//滑雪
    }
    if(k<t&&f[k+1][p]<sum)dfs(k+1,p,sum);//如果可以休息就休息
    int q=w[k];
    while(q!=0)//枚举当前时刻所有课程
    {
        if(k+g[q].l<=t&&g[q].a>p)if(f[k+g[q].l][g[q].a]<sum)//上课划算
        {
            dfs(k+g[q].l,g[q].a,sum);//上课
        }
        q=g[q].next;
    }
}
inline int read()//快读
{
char c=getchar(); int ret=0,f=1; 
while (c<'0'||c>'9') {if(c=='-')f=-1;c=getchar();}
while (c<='9'&&c>='0') {ret=ret*10+c-'0';c=getchar();} 
return ret*f;
}
int main()
{
    t=read();
    s=read();
    n=read();
    for(int i=1;i<=s;i++)
    {
        m=read();
        l=read();
        a=read();
        add(m,l,a);//我用了一种类似点集的方式存某时刻的课程
    }
    for(int i=1;i<=100;i++)dd[i]=20000;//dd数组存某能力值下最短时间的滑雪选择
    for(int i=1;i<=n;i++)
    {
        c=read();
        d=read();
        dd[c]=min(dd[c],d);
    }
    for(int i=2;i<=100;i++)dd[i]=min(dd[i],dd[i-1]);
    for(int i=1;i<=t;i++)//初始化
        for(int j=1;j<=100;j++)f[i][j]=-1;
    dfs(0,1,0);//搜索
    for(int i=1;i<=100;i++)//比较最大值
        ans=max(ans,f[t][i]);
    printf("%d",ans);
}
```

---

## 作者：intel_core (赞：0)

[题目直达链接](https://www.luogu.com.cn/problem/P2948)   
本篇题解展示的是从最基础的DP优化到正解的过程，~~巨佬勿喷~~     
### 下面，正文开始：
最基础的做法(具有启发性的DP)：  
##### 注：本篇题解涉及到的所有转移均是被动转移，请注意    
令$f_{i,j}$表示在$i$时刻，能力值为$j$时的最大滑雪次数    
1. 当前时刻`Bessie`在摸鱼：$f_{i+1,j}=max(f_{i,j},f_{i+1,j})$    
2. 当前时刻`Bessie`在上编号为$k$的滑雪课：$f_{i+R_k,A_k}=max(f_{i,j},f_{i+R_k,A_k})|i==L_k$
3. 当前时刻`Bessie`正在编号为$k$的坡上滑雪：$f_{i+D_k,j}=max(f_{i,j},f_{i+D_k,j})|j>=C_k$   

这个做法时间复杂度是$O(TNC_{max})$的，难以通过本题     
考虑优化这个算法：    
来看一看几个重要的数据范围：
* $T \leq 10,000$
* $S \leq 100$
* $N \leq 10,000$
* $C_i,A_i \leq 100$    

这里可以发现，虽然有$N$个滑雪坡，但$C$相同的滑雪坡在$N->10000$时却可能会有$\frac{N}{C}->100$个    
而$C$相同的滑雪坡只要保存$D$最小的即可   
所以滑雪坡的个数降至$C_{max}$个    
总复杂度降至$O(TC_{max}^2)$，本机测试下来在$1.2s$左右    
对于`NOIp`这种开不了O2的比赛，还需要进一步优化   

注意到复杂度中有$C_{max}^2$  
其中一个是枚举当前能力值时加上去的   
另一个是枚举滑雪坡的$C_i$时加上去的   
但是我们并不关心我们每个滑雪坡的$C$值到底是多少    
所以我们可以预处理$minn_i$表示能力值为$i$时滑一次最少需要多少时间   
情况3的转移方程变为：$f_{i+minn_j,j}=max(f_{i,j},f_{i+minn_j,j})$    

##### 注：由于本人码风原因，代码中的$R_i$表示滑雪课的结束时间   

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NR=1e4+10;
const int MR=110;
int f[NR][MR];
int l[MR],r[MR];
int val[MR];
int minn[MR];
int T,n,m;
vector<int>v[NR];//用来存储起始时刻相同的滑雪课编号
int main(){
	cin>>T>>m>>n;
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&l[i],&r[i],&val[i]);
		r[i]+=l[i];
		v[l[i]].push_back(i);
	}
	memset(minn,999999,sizeof(minn));//minn初始化为无穷大
	for(int i=1;i<=n;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		minn[x]=min(minn[x],y);
	}
	for(int i=1;i<=100;i++)minn[i]=min(minn[i],minn[i-1]);
	memset(f,-999999,sizeof(f));//f初始化为无穷小
	f[0][1]=0;
	int ans=0;
	for(int i=0;i<T;i++)
		for(int j=1;j<=100;j++){
			f[i+minn[j]][j]=max(f[i+minn[j]][j],f[i][j]+1);
			f[i+1][j]=max(f[i+1][j],f[i][j]);
			for(int k=0;k<v[i].size();k++)f[r[v[i][k]]][val[v[i][k]]]=max(f[r[v[i][k]]][val[v[i][k]]],f[i][j]);
		}
	for(int i=1;i<=100;i++)ans=max(ans,f[T][i]);
	cout<<ans;
	return 0;
}
```


---

## 作者：moongazer (赞：0)

# 「洛谷P2948」【USACO09OPEN】滑雪课 题解
## 思路
1. 首先将所有课程按结束时间排序
2. 将相同滑坡能力值的分为一类, 对于能力为$i$的取其中所需时间最短的$lastmin_i$
3. $f(i, j)$表示对于第$i$个时刻, 能力值为$j$或$j$以上时最大的滑雪次数
4. 若第$j$个课程开始于$begin$结束于$i$, 若参加这个课程, 枚举开始时的能力值$k, f(i, abi_j)=max\{f(begin, k) | k<=100\}$ ($abi_j$是第$j$次获得的滑雪能力), 再枚举$abi_j$以下的能力$k, f(i, k)=max\{f(i, k), f(i, j)\}$
5. 对于每一个时刻$i$, 若滑雪, 枚举滑雪时的能力值$k, f(i, k)=max\{f(i-lastmin_k, k)|k<=100, i-lastmin_k>=0\}$

## 代码
注: 以下代码已省略头文件、read和write
```cpp
class Class {
public:
    int begin, end, abi;
    friend bool operator<(Class, Class);
}c[M];
// 课程类型, 可以视作struct
int dp[N][M];
int lastmin[M];
int main () {
    int n, m, t;
    read(t);
    read(n);
    read(m);
    for (int i=1; i<=n; i++) {
        int begin, last, abi;
        read(begin);
        read(last);
        read(abi);
        c[i].begin=begin;
        c[i].end=begin+last;
        c[i].abi=abi;
    }
    sort(c+1, c+n+1, [](Class i, Class j) {
        return i.end<j.end;
    });// 给课程按结束时间排序, 用到了匿名(lambda)函数, 需要开C++11
    for (int i=1; i<=100; i++) {
        lastmin[i]=inf;
    }
    for (int i=1; i<=m; i++) {
        int need, last;
        read(need);
        read(last);
        lastmin[need]=min(lastmin[need], last);
    }
    memset(dp, -1, sizeof(dp));
    for (int i=0; i<=t; i++) {
        dp[i][1]=0;
    }
    int ans=0;
    for (int i=1, j=1; i<=t; i++) {// j表示下一个课程的编号
        if (c[j].end==i) {
            for (int k=1; k<=100; k++) {
                dp[i][c[j].abi]=max(dp[i][c[j].abi], dp[c[j].begin][k]);
            }
            for (int k=1; k<c[j].abi; k++) {
                dp[i][k]=max(dp[i][k], dp[i][c[j].abi]);
            }
            j++;
        }// 上课
        for (int k=1; k<=100; k++) {
            if (i-lastmin[k]>=0) {
                if (dp[i-lastmin[k]][k]!=-1) {
                    dp[i][k]=max(dp[i][k], dp[i-lastmin[k]][k]+1);
                    ans=max(ans, dp[i][k]);
                }
            }
        }// 滑雪
    }
    write(ans);
    EL;
    return 0;
}
```


---

