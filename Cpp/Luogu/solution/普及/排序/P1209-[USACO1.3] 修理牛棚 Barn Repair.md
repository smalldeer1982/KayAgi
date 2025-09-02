# [USACO1.3] 修理牛棚 Barn Repair

## 题目描述

在一个月黑风高的暴风雨夜，Farmer John 的牛棚的屋顶、门被吹飞了 好在许多牛正在度假，所以牛棚没有住满。   

牛棚一个紧挨着另一个被排成一行，牛就住在里面过夜。有些牛棚里有牛，有些没有。 所有的牛棚有相同的宽度。   

自门遗失以后，Farmer John 必须尽快在牛棚之前竖立起新的木板。他的新木材供应商将会供应他任何他想要的长度，但是吝啬的供应商只能提供有限数目的木板。 Farmer John 想将他购买的木板总长度减到最少。

给出 $m,s,c$，表示木板最大的数目、牛棚的总数、牛的总数；以及每头牛所在牛棚的编号，请算出拦住所有有牛的牛棚所需木板的最小总长度。


## 说明/提示

【数据范围】  
对于 $100\%$ 的数据，$1\le m \le 50$，$1\le c \le s \le 200$。 

USACO Training Section 1.3


## 样例 #1

### 输入

```
4 50 18
3 
4 
6 
8 
14
15 
16 
17 
21
25 
26 
27 
30 
31 
40 
41 
42 
43
```

### 输出

```
25
```

# 题解

## 作者：Starlight_Glimmer (赞：182)

典型的贪心题目

我们可以先假设只有一块木板从编号最小的牛棚一直铺到编号最大的牛棚，然后断开m-1处。自然要按相邻牛棚的编号差从大到小断开才能使我们断开的地方可以有效节省木板长度（因为中间省去的要更多）

另外，要将输入的数据排序，数据可能不是按编号从小到大给的

代码：


```cpp
#include<cstdio> 
#include<algorithm> 
#include<iostream> 
#define MAXN 205
using namespace std; 
int m,s,c,ans;
int a[MAXN],C[MAXN];
bool cmp(int x,int y)
{
    return x>y;
}
int main() 
{ 
    scanf("%d %d %d",&m,&s,&c);
    for(int i=1;i<=c;i++)
        scanf("%d",&a[i]);
    if(m>c) { //特判，如果木板数大于牛数，那么每只牛可以有一块木板
        printf("%d\n",c);
        return 0;
    }
    sort(a+1,a+c+1);
    ans=a[c]-a[1]+1;//假设只有一块木板连续地铺着
    for(int i=2;i<=c;i++)
        C[i-1]=a[i]-a[i-1];
    sort(C+1,C+c,cmp);
    for(int i=1;i<=m-1;i++)//减去差最大的//将木板从差最大的地方减去
        ans=ans-C[i]+1;
    printf("%d\n",ans);
} 

```

---

## 作者：封禁用户 (赞：37)

此题的算法是这样的，首先用一块木板从第一个牛的位置覆盖到最后一个牛的位置。

然后反复调用“增加block过程”，直到所使用的木板数达到题目给出的限制，或空白全部被填满。

这样得到的状态S(ｐ)就是最优状态。［ｐ等于给出的可用木板数与空白数的较小值］

这个一个贪心算法，下面使用一个循环不变式证明它的正确性，这里假设没有两个空白具有相同的长度

(因为当最长的空白有多个时可以选择任意一个，所以这种假设是可行的)。

循环不变式：在首先用一块木板从第一个牛的位置覆盖到最后一个牛的位置后

(得到状态S(1))，每次调用“增加block过程”后得到的状态S(ｉ)均是最优的

。 初始：容易看出S(1)是最优的。

中间：假设S(k)是最优的，则使用“增加block过程”后S(k+1)也是最优的，

下面用反证法来证明。 如果S(k+1)不是最优的，则存在S'(k+1)最优，

 使得 |S'(k+1)| < |S(k+1)|，且S'(k+1)不等于S(k+1) 
设在S(k)到S(k+1)的转变中我们去掉的那个最长的空白为b,

 则有 |S(k+1)| = |S(k)| - |b|， 又因为|S'(k+1)| < |S(k+1)|，
 所以有|S'(k+1)| <　|S(k)| - |b|，即　|S(k)|　> |S'(k+1)| + |b|　＜１式＞， 当S'(k+1)没有覆盖ｂ时，
 我们可以把ｂ两头的木板连起来覆盖ｂ得到S'(k),且有 |S'(k)| = |S'(k+1)| + |b|， 根据＜１式＞有 |S(k)| > |S'(k)|　，这与假设S(k)最优矛盾。
  当S'(k+1)覆盖了ｂ时，因为ｂ是S(k)中最长的空白，则S'(k+1)中一定存在一个没有覆盖的空白d,使得 |d| < |b|， 这是因为如果ｄ不存在的话表明前ｋ次删除空白时我们删除了最长的ｋ个空白(b是第ｋ长的)
  ，这意味着S'(k+1)等于S(k+1)，别忘了我们假设没有两个空白具有相同的长度。 因此S'(k+1)覆盖了ｂ时ｄ一定存在，此时如果在S'(k+1)中交换ｂ、ｄ（不覆盖ｂ，而覆盖ｄ），则可得S(k+1)， 又因为 |d| < |b| ，
  所以 |S(k+1)| < |S'(k+1)|，这与S'(k+1)最优矛盾。
由此可知S(k+1)是最优的，即算法正确。

以上思路仅供参考


---

## 作者：以墨 (赞：32)

看到用#DP#的童鞋这么少，呵呵......

楼下的DP都是二维数组，可能和我的不太一样，我就没看了~

**初始形态**

用f(i,j)表示前i个牛棚用j块木板的最优解

显然f(i,j)=min{f(i-1,j)+a[i]-a[i-1],f(i-1,j-1)+1}

a(i)表示第i个牛棚的位置。

说明一下吧~

第一个式子表示在前i-1头牛已经用了j块木板，说明第i个牛棚只能和前一个牛棚连起来，作为一个木板使用，所以要加上距离；

第二个式子表示在前i-1头牛已经用了j-1块木板，说明第i个牛棚是单独的一块木板，最少就用长度为1的呗。

最后输出就是f[c][m]

**一级进化**

如果可以细心观察的话，你能发现每一次计算，更新值只和上一个阶段(i-1)有关。

所以这里可以用滚动数组来优化。只记录i与2的余数就可以了。

这样来说可以降低一点空间复杂度。//虽然来说空间复杂度不要钱，但是能省点尽量省省吧~~~

这时空间复杂度由原来的O(cm)降低到O(m)级别//常数暂且省略

******终极形态******

如果对01背包有深入了解的话，一定能发现，如果将第二层循环从大到小，这时的j-1和j都是上一个阶段的值，连滚动数组都不需要了~~



```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int f[52],a[202],n,k,m,i,j;
int main()
{
    scanf("%d%d%d",&m,&k,&n);
    if(m>=n)//我觉得可以先特判，木板数>=牛棚数，直接就输出牛棚数
    {
        printf("%d\n",n);
        return 0;
    }
    for(i=1;i<=n;i++)
        scanf("%d",&a[i]);
    sort(a+1,a+1+n);//**对牛棚位置进行排序**
    for(i=1;i<=n;i++)
    {
        for(j=m;j>=1;j--)//从大到小
            f[j]=min(f[j]+a[i]-a[i-1],f[j-1]+1);
        f[0]=1<<30;//注意！由于f[0]不参与计算，所以如果没有把它在每一个阶段后赋值为很大的数，结果必然是1
    }
    printf("%d\n",f[m]);//最后一定要输出f[m]，因为无论怎样，木板数越多，需要盖住的和就肯定会少。不能在f[1]~f[m]中取最小值
    return 0;
}
最后估算一下时间复杂度：两层循环O(cm)，比贪心的O(ClogC)略慢。但是说实话，DP比贪心更稳一点。
```

---

## 作者：junyuge (赞：20)

luogu P1209 修理牛棚 <贪心> 
-
看到木板最大数目，容易下意识想到二分。但是我们冷静思考下，这道题怎么样才能使总长度最短。
因为有些牛不在，所以有些牛棚是不需要覆盖木板的。如果能每个牛棚分单独一个木板，一定总长度是最小的。但是由于木板数量有限制，所以我们有时只能用一个比较长的木板的时候，顺便把没有牛的牛棚也覆盖了。就造成了浪费。所以一定是使用最大数目木板的。

我们考虑，如果第一头牛在a[1],最后一头牛在a[c]。我们先考虑，把这个这一段放置一整个木板，显然这是最不优秀的方法。因为我们只用了一个木板。我们考虑这一段内，有些两头牛之间的一段牛棚都没有牛，那么我们把原先的一整个木板拆成两个，就可以使得这一个没有牛的区间不放木板，从而节省了长度。所以就相当于，每多一块木板，就能使得区间内一段没有牛的部分，可以不覆盖木板。我们就对所有没有牛的区间排一个序，然后优先去删掉较大的，删m-1个即可。
注意题目中输入的a数组可能无序，需要排序后使用

```

#include<bits/stdc++.h> 
using namespace std;
int m,s,c,ans;
int a[210],b[210];
int main()
{
    scanf("%d%d%d",&m,&s,&c);
    for (int i = 1;i <= c;i++)
        scanf("%d",&a[i]);
    sort(a + 1,a + c + 1);
    ans = a[c] - a[1] + 1;
    for (int i = 1;i <= c - 1;i++)
        b[i] = a[i + 1] - a[i] - 1;
    sort(b + 1,b + c);
    for (int i = c - 1;i >= c - m + 1;i--)
        ans -= b[i];
    printf("%d\n",ans);
}
```

---

## 作者：wubaiting2020 (赞：9)

可以先将这道题反过来想

可以理解为有一块木板将整个盖住，每两个有牛的棚子中间有空隙，可以断开m-1次，如图例![](https://cdn.luogu.com.cn/upload/pic/57707.png)

但还需要特判m>c的情况，因为需要的木板比消耗的木板多，会导致第6,7个点WA或RE

上代码
```cpp
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<queue>
using namespace std;
int m,s,c,a[205],b[205],ans=0;
bool cmp(int x,int y){return x>y;}//从大到小排 
int read()
{	int x=0; char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	return x;
}//快读 
int main()
{
	m=read();s=read();c=read();
	if(m>c){printf("%d",c);return 0;}//特判需要的木板比消耗的木板多的情况 
	for(int i=1;i<=c;i++)a[i]=read();
	sort(a+1,a+c+1);
	for(int i=2;i<=c;i++)b[i-1]=a[i]-a[i-1];//求出有牛的牛棚的中间的空隙 
	ans=a[c]-a[1]+1;//初始将整个盖住 
	sort(b+1,b+c,cmp);//空隙从大到小排 
	for(int i=1;i<=m-1;i++)ans=ans-b[i]+1;//减去空隙 
	printf("%d",ans);
	return 0;
}


```



---

## 作者：Jigsaw_Killer (赞：7)

/\*
本题可以抽象成在一个数轴上有C1，C2......Cn这n个点，数组X[i]表示Ci~C（i+1）的距离，ans的初始值就是假设只有一块木板

时的最小距离，显然是Cn-C1，但是注意，要+1；之后假设有两块木板，三块，四块......注意！！当前假设木板数1.显然

不能超过最多提供的木板数；2.显然不可超过有奶牛的牛棚数。满足这两点，开始循环，不断地减掉当前最大的距离。循环

完了就是答案！要写cmp       PS：C数组用a代替；X数组用b代替。

\*/
```cpp
#include<iostream>
#include<cstring>
#include<cmath>
#include<cstdio>
#include<algorithm>
using namespace std;
int a[1005],b[1005],m,s,c,i,ans;
bool cmp(int a,int b){       //从大往小排
    return a>b;
}
int main(){
    //freopen("barn1.in","r",stdin);
    //freopen("barn1.out","w",stdout);
    scanf("%d%d%d",&m,&s,&c);
    for(i=1;i<=c;i++)
        scanf("%d",&a[i]);
    sort(a+1,a+c+1);
    for(i=1;i<=c-1;i++) 
        b[i]=a[i+1]-a[i]-1;       //算Ci到Ci+1的距离
    sort(b+1,b+c,cmp);
    ans=a[c]-a[1]+1;             //ans最差情况，即赋初值
    for(i=1;i<m&&i<c;i++)
        ans-=b[i];                    //循环算答案
    printf("%d",ans);               //输出
    return 0;
}

```

---

## 作者：HenryHuang (赞：7)

这道题就是~~动态规划~~贪心好吧？我们老师把它放到DP训练里面，我还能说什么···

附上代码：

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
int a[201],b[201];
int main()
{
    int n,m,s,long1,ans;
    cin>>n>>m>>s;
    for(int i=1;i<=s;i++)//输入 
    cin>>a[i];
    sort(a+1,a+s+1);//对输入进行排序 
    for(int i=2;i<=s;i++)
    b[i]=a[i]-a[i-1]-1;//以相邻两块的第二块作下标，算出每两个有船的码头之间的距离 

    sort(b+2,b+s+1);//将间隔距离从小到大排序 
    ans=s;//默认每个码头都有一块长度为1的木板    
    long1=s;// 所以默认长度为1\*s=s 
    int i=2;//因为 b数组从2开始 
    while(ans>n)//当不符合要求 
    {
            ans--;//木板数--； 
            long1+=b[i];//将间隔的距离加至总长中（相当于用木板连接相邻两块，合为一块，覆盖了空隙） 
        i++; 
    }
    cout<<long1<<endl;//输出总长 
}

---

## 作者：ydclyq (赞：7)

这是一个令人悲伤的故事


贪心+排序

但是没想到数据那么。。。
awa

![](https://cdn.luogu.com.cn/upload/image_hosting/zufvrmiw.png)


### 因为是求所需木板的最小总长度。 
### 而且吝啬的供应商只能提供有限数目的木板

所以嘛。。。

最小总长度=有牛住的+没有牛住但是为了因为供应商的吝啬所必须有门的


# 数据有坑

下附代码：
 
 ```cpp
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cstring>
using namespace std;
int n,k,m;
struct node {
	int cha;
	int val;
	int xia;
} f[201];
bool cmp(node a,node b) {
	return a.cha>b.cha;
}
bool cmp11(node a,node b) {
	return a.val<b.val;
}
long long  ans;
signed main() {
	cin>>n>>k>>m;
	int t;
	for(int i=1; i<=m; i++)
		cin>>f[i].val;
	if(n>=m) {//如果提供的门板数，足够一个门一张板，就不需要浪费长度啦。。
		cout<<m<<" ";
		return 0;
	}
	sort(f+1,f+1+m,cmp11);

	for(int i=1; i<=m; i++) {
		f[i-1].xia=f[i].val;
		f[i-1].cha=f[i].val-f[i-1].val;
	}
	int start=f[1].val;
	t=f[m].val;
	sort(f+1,f+1+m,cmp);
	sort(f+1,f+n,cmp11);

	for(int i=1; i<n; i++) {
		ans+=f[i].val-start+1;
		start=f[i].xia;
	}
	ans+=t-start+1;
	cout<<ans;
	return 0;
}
```

祝大家CSP rp++

---

## 作者：abc_de (赞：3)

# 贪心
整体思路就是假设全部牛棚只有一块木板连着，然后记录每两个牛棚之间的差，把差最大的给减去，就是最终答案，十分的简单，代码如下：




```cpp
#include<bits/stdc++.h> 
using namespace std; 
int m,s,c,ans;
int a[10001],cha[10001];//a【】就是输入的数，cha【】就是每两个数之间的差。
bool cmp(int x,int y)
{
    return x>y;//从大到小排序。
}
int main() 
{ 
    cin>>m>>s>>c;//意义见题目，就不用我多说了。
    for(int i=1;i<=c;i++)//输入。
        cin>>a[i];
    if(m>c) { //只要最大木板数大于牛的数量，直接输出牛棚数就行，也就是相当于每个牛棚遮挡一个木板，最后结果肯定也是最小的。
        cout<<c;
        return 0;
    }
    sort(a+1,a+c+1);//排序。
    ans=a[c]-a[1]+1;//假设只有一块木板挡着。
    for(int i=2;i<=c;i++)//记录每两个牛棚之间的差。
        cha[i-1]=a[i]-a[i-1];
    sort(cha+1,cha+c,cmp)//把差排下序。
    for(int i=1;i<=m-1;i++)
        ans=ans-cha[i]+1;//把差最大的地方减去就好了。
    cout<<ans;//输出
    return 0;
} 
```


---

## 作者：柠檬树开 (赞：3)

##  【真-蒟蒻】第一篇题解
读过题之后，不难想到有牛的牛棚一定需要木板

所以我们只需要找到最小的木板浪费值就行了

（也就是需要木板修理的空牛棚数最小）

代码奉上~~(一个**贪心**你费什么话)~~

```
#include<bits/stdc++.h>
#define re register int
using namespace std;
int ans,a[201],b[201];
int num,d[201],m,s,c,;
int main()
{
    scanf("%d%d%d",&m,&s,&c);
	for(re i=1;i<=c;i++)
	    scanf("%d",&a[i]),b[a[i]]=1;//桶排，有牛的牛棚号设为1 
	sort(a+1,a+c+1);                
	for(re i=a[1];i<=a[c]-1;i++)
	{
		if(b[i]==1&&b[i+1]==0)      //如果遇到一个有牛的牛棚下一个牛棚没有牛 
		num++;                      //间隔数+1 
		else if(b[i]==0)            //如果这个牛棚没有牛 
		d[num]++;                   //当前间隔下空牛棚数量+1 
	}
	sort(d+1,d+num+1);              //空牛棚数小的间隔优先搭建 
	for(re i=1;i<=num-m+1;i++)      // num-m+1表示需要搭建的间隔数 
	    ans+=d[i];
	cout<<ans+c<<endl;              //（输出时别忘了加上c QAQ）
	return 0;                      
}
```













---

## 作者：Mychael (赞：2)

一看到这道题我就想到了动态规划

难道这题用动态规划不比搜索要来的简单得多么？


言归正传，动态规划三部曲：

1’确定状态

这道题明显是个二维dp，可设出dp[i][j]，表示用i片木板填补前j个牛棚所用的木板总长。


2'初始化

据多年经验，以状态1开始的dp的初始化只用考虑i=0或j=0的情况：

1：dp[0][j] 用0块木板填补前j个牛棚，显然不可能，赋值INF(一个很大的数)

2：dp[i][0] 用i块木板填补前0个牛棚，显然不需要木板，赋值0


3'确定状态转移方程

在dp[i][j]时，我们只用考虑第j个牛棚

①若无牛，显然不比白费力气填这个牛棚,便等于填到上一个牛棚的木板数，dp[i][j]=dp[i][j-1]


②若有牛

有两种决策：

1：单独用一个木板填，那么之前j-1个牛棚只能用i-1个木板，dp[i][j]=dp[i-1][j-1]+1

2：连着上一个有牛的牛棚，那么就等于之前j-1个牛棚的决策结果+该牛棚到上一个有牛的牛棚的距离,dp[i][j]=dp[i][j-1]+last[i]

(last表示该牛棚到上一个有牛的牛棚的距离)

选择需要木板最小的，即dp[i][j]=min(dp[i-1][j-1]+1,dp[i][j-1]+last[j])


这样子，程序自然就写出来了：



```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=205,INF=1000000000;
int dp[maxn][maxn];
int last[maxn];                                   //表示当前牛棚到上一个有牛的牛棚的距离
bool cow[maxn];                                //当前牛棚是否有牛
int read()                                           //读入优化，别在意。。
{
    int out=0;
    char c=getchar();
    while(c<48||c>57) c=getchar();
    while(c>=48&&c<=57)
    {
        out=out*10+c-48;
        c=getchar();
    }
    return out;
}
int main()
{
    fill(cow,cow+maxn,false);           //初始化所有牛棚均无牛
    fill(last,last+maxn,-1);               //可有可无
    int M=read(),N=read(),S=read(),pre=0;   //一些骚气的读入
    while(S--) cow[read()]=true;
    for(int i=1;i<=N;i++)                               //计算last
        if(cow[i])
        {
            if(pre) last[i]=i-pre;
            else last[i]=1;                                  //注意：第一个牛棚的last为1
            pre=i;
        }
    for(int i=0;i<=N;i++) dp[0][i]=INF;       //初始化
    for(int i=0;i<=M;i++) dp[i][0]=0;
    for(int i=1;i<=M;i++)                             //动态规划，详解如之前所述
        for(int j=1;j<=N;j++)
            if(cow[j]) dp[i][j]=min(dp[i-1][j-1]+1,dp[i][j-1]+last[j]);
            else dp[i][j]=dp[i][j-1];
    cout<<dp[M][N]<<endl;
    return 0;
}

```

---

## 作者：Violette (赞：2)

## 典型贪心题目

这道题一共可以分为

读入坐标、排序坐标、计算差、排序差、计算总长、从大到小减去m-1个差和输出六个部分。
 
#### 注意：从1到n的长度是这个数组的最后一项减去第一项再加1！

把思路整理好再写程序就不是很难了

附上代码：
```
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
int cow[210], d[210];
bool cmp(int x, int y)
{
    return x > y;
   
}//可以用greater<int>()来替代 
int main()
{
    // 读入坐标
    int m, s, c;
    cin>>m>>s>>c; 
    for (int i=1;i<=c;i++) cin>>cow[i];
    // 排序坐标
    sort(cow+1,cow+1+c);// 计算差
    int num=c-1;
    for (int i=1;i<=num;i++) d[i]=cow[i+1]-cow[i]-1;
    // 排序差
    sort(d+1,d+1+num,cmp);
    // 计算总长
    int len=cow[c]-cow[1]+1;
    // 从大到小减去m-1个差
    for (int i=1;i<=m-1;i++) 
        len-=d[i];
    cout<<len;//输出 
    return 0;
}
```



---

## 作者：doctorZ_ (赞：1)

~~对于我这种对动规一窍不通的人来说，一遇到动规就只能用dfs水分~~
### 现在步入正题
购买最小的木板，其实就是把牛的牛棚编号进行分组，然后使每组末位数字减首位数字的差加起来的和最小，且分的组数不能大于M(可能买到的木板最大的数目)
### 就拿样例说明:
|  | 第一组 | 第二组 |第三组  |第四组  |
| -----------: | -----------: | -----------: | -----------: | -----------: |
| 编号 |3-8 |14-21  | 25-31 | 40-43 |
这就是样例的最优分组方案
我们先在要做的就是枚举这些方案
### 于是，就有了下面这行代码
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int m,s,c,minn=2147483647;
int cow[201];
void dfs(int h,int record,int cnt,int before)
{
	for(int i=h;i<=c;i++)
	{
		if(record>=minn||cnt==m)//剪枝 
			return;
		if(i==c)
		{
			record+=cow[i]-cow[before]+1;//计算末位数字和首位数字的差 
			minn=min(minn,record);//取最小的和 
			return;
		}
		//分两种情况搜索，分和不分 
		dfs(i+1,record+cow[i]-cow[before]+1/*计算末位数字和首位数字的差 */,cnt+1,i+1);
		dfs(i+1,record,cnt,before);
	}
}
int main()
{
	scanf("%d %d %d",&m,&s,&c);
	for(int i=1;i<=c;i++)
		scanf("%d",&cow[i]);
	sort(cow+1,cow+1+c);//因为题目并未说明数据是从小到大的，所以要用sort排序一遍 
	dfs(1,0,0,1);
	printf("%d",minn);
	return 0;
}
```
-----70分
#### 现在我们要优化时间复杂度
怎么办呢？----我们可以使用记忆化搜索（由于本蒟蒻不会打破折号，只能用减号代替）
## 于是下面这行AC代码就出现了
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int m,s,c,minn=2147483647;
int cow[201],f[51][201][201];
void dfs(int h,int record,int cnt,int before)
{
	for(int i=h;i<=c;i++)
	{
		if(record>=minn||cnt==m||record>=f[cnt][i][before])//记录每种情况的最优权值 
			return;
		f[cnt][i][before]=record;
		if(i==c)
		{
			record+=cow[i]-cow[before]+1;
			minn=min(minn,record);
			return;
		}
		dfs(i+1,record+cow[i]-cow[before]+1,cnt+1,i+1);
		dfs(i+1,record,cnt,before);
	}
}
int main()
{
	memset(f,1,sizeof(f));//现在告诉大家一个小技巧，memset(1)可以把数组赋为16843009,对于本题来说这个数已经够大了 
	scanf("%d %d %d",&m,&s,&c);
	for(int i=1;i<=c;i++)
		scanf("%d",&cow[i]);
	sort(cow+1,cow+1+c);
	dfs(1,0,0,1);
	printf("%d",minn);
	return 0;
}
```
虽然时间和空间都比动规要大，但是已经可以过了

---

## 作者：muyang_233 (赞：1)

首先，这是一道贪心题。  
我们先来分析它的贪心策略。  
例如，样例：  
4 50 18  
3 
4 
6 
8 
14
15 
16 
17 
21
25 
26 
27 
30 
31 
40 
41 
42 
43  
它们之间的差是：  
1 2 2 6 1 1 1 4 4 1 1 3 1 9 1 1 1  
既然我们要让木板长度最小，那么我们就得**空出前m-1个最大的区域，把其他区域累加，再加上一个m（例如3~8的差是8-3=5，而实际木板长度为8-3+1=6，每个木板都多一个，那么m个木板会多出m个）**。  
代码1（50分代码）：  
```cpp
#include <bits/stdc++.h>
using namespace std;
struct node
{
	int cow,div;
	/*
	cow为该牛所占牛棚编号，
	div为该点与上一点差，
    _为这是一个WA代码，
	*/
}_[201];
int m,s,c;
bool cmp(node c,node d)
{
	return c.div>d.div;
}
int main()
{
	int ans=0;
	scanf("%d%d%d",&m,&s,&c);
	scanf("%d",&_[1].cow);_[1].div=0;
	for (int i=2;i<=c;i++)
	{
		scanf("%d",&_[i].cow);
		_[i].div=_[i].cow-_[i-1].cow;
	}
	sort(_+1,_+c+1,cmp);
	for (int i=m;i<=c;i++) ans+=_[i].div;
	ans+=m;
	printf("%d\n",ans);
	return 0;
}
```
这是一个50分代码。很显然，问题在于：认为输入的编号一定是升序序列。所以，添加abs和sort，代码为：  
代码2（80分代码）：  
```cpp
#include <bits/stdc++.h>
using namespace std;
struct node
{
    int cow,div;
    /*
    cow为该牛所占牛棚编号，
    div为该点与上一点差，
    _为这是一个WA代码。
    */
}_[201];
int m,s,c;
bool cmp1(node c,node d)
{
    return c.cow<d.cow;
}
bool cmp2(node c,node d)
{
    return c.div>d.div;
}
int main()
{
    int ans=0;
    scanf("%d%d%d",&m,&s,&c);
    scanf("%d",&_[1].cow);
    for (int i=2;i<=c;i++)
        scanf("%d",&_[i].cow);
    sort(_+1,_+c+1,cmp1);
    for (int i=2;i<=c;i++) _[i].div=abs(_[i].cow-_[i-1].cow);
    sort(_+1,_+c+1,cmp2);
    for (int i=m;i<=c;i++) ans+=_[i].div;
    ans+=m;
    printf("%d\n",ans);
    return 0;
}
```
这个代码很容易被认为是AC代码，其实不然。例如，测试点6，出现了m比c大的情况。那么它肯定不能用m个木板去覆盖。这种时候，我们只要在**每个点上都摆一个长度为1的木板就行了**，或者说，**木板总长即为牛的只数**。所以，代码如下：  
代码3（100分代码）：  
```cpp
//本题解由姆洋题解®提供。姆洋题解，蒟蒻们的题解。
#include <bits/stdc++.h>
using namespace std;
struct node
{
	int cow,div,_this,_last;
	/*
	cow为该牛所占牛棚编号，
	div为该点与上一点差，
	_this为该点，_last为上一点。
	*/
}_[201];
int m,s,c;
bool cmp1(node c,node d)
{
	return c.cow<d.cow;
}
bool cmp2(node c,node d)
{
	return c.div>d.div;
}
int main()
{
	int ans=0;
	scanf("%d%d%d",&m,&s,&c);
	if (m>=c) {printf("%d\n",c);return 0;}
	scanf("%d",&_[1].cow);_[1]._last=0;_[1]._this=1;
	for (int i=2;i<=c;i++)
		scanf("%d",&_[i].cow);
	sort(_+1,_+c+1,cmp1);
	for (int i=2;i<=c;i++) _[i].div=abs(_[i].cow-_[i-1].cow),_[i]._this=i,_[i]._last=i-1;
	sort(_+1,_+c+1,cmp2);
	for (int i=m;i<=c;i++) ans+=_[i].div;
	ans+=m;
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：VSEJGFB (赞：1)

这道题为什么有那么多DP题解.....而且难度是普及/提高-


仔细看题，求最短木板长就是 总长-（m-1）个空位。


使m-1个空位最大化就是了。


将空位排好序，用区间总长减去前m-1大个空位长就是答案了~


s就是个逗比数据。。。。

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int a[220],spc[220];
int main(){
    int m,s,c;
    cin>>m>>s>>c;
    for(int i=0;i<c;i++)
        cin>>a[i];
    sort(a,a+c);
    for(int i=1;i<c;i++) spc[i-1]=a[i]-a[i-1]-1;//存入空位长度
    sort(spc,spc+c-1);//给空位排序
    int ans=a[c-1]-a[0]+1;
    for(int i=0;i<m-1;i++) ans-=spc[c-i-2];//减去前m-1大个空位长度。
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：西瓜狼 (赞：0)

这是道贪心题目

我们可以先假设只有一块木板从编号最小的牛棚一直铺到编号最大的牛棚，然后断开m-1处。自然要按相邻牛棚的编号差从大到小断开才能使我们断开的地方可以有效节省木板长度（因为中间省去的要更多）
```
var
        m,s,min,max,b,c,i,j,temp:longint;
        a:array[1..200] of boolean;
        map:array[0..200] of longint;
begin
        readln(m,s,c);//读入木板最大的数目M ,牛棚的总数S和牛的总数C
        max:=0;
        min:=maxlongint;
        for i:=1 to c do
        begin
                readln(temp);
                a[temp]:=true;//表示这个位置是编号
                if temp>max then
                        max:=temp;//求最大值
                if temp<min then
                        min:=temp;//求最小值
        end;
        for i:=min to max do
        begin
                if a[i] then
                        map[i]:=0
                else
                begin
                        map[i]:=map[i-1]+1;//求与上一个编号之间的距离
                        map[i-1]:=0;//清零
                end;
        end;
        for i:=1 to s-1 do
        begin
                for j:=i+1 to s do
                begin
                        if map[i]<map[j] then
                        begin
                                temp:=map[i];
                                map[i]:=map[j];
                                map[j]:=temp;
                        end;
                end;
        end;//冒泡排序，如果嫌太慢，可以用快排
        temp:=max-min+1;//假设只有一块木板，长度就是编号最小的和编号最大的之差
        for i:=1 to m-1 do
                temp:=temp-map[i];//却掉m-1处间隙最大的木板
        writeln(temp);//输出答案
end.
```


---

## 作者：反手一只MJJ (赞：0)

#### 本人的第一篇题解，如有不好之处，请指示。
## 不喜欢用$sort$的我
-  废话不多说！直接说说本篇的核心思想↓。
#### 美丽容器：$map$
$1.$读题，数据还算水： 

------------
$N$,($0≤N≤2,000,000$)是需要牛奶的总数；$M$,($0≤M≤5,000$)是提供牛奶的农民个数。$Pi$($0≤Pi≤1,000$) 是农民$i$的牛奶的单价。$Ai$($0≤Ai≤2,000,000$)是农民$i$一天能卖给$Marry$的牛奶制造公司的牛奶数量。


------------
因此，可以直接考虑使用**自带排序的容器**譬如**set,FIFO,map**等。

$2.$琢磨规律：

要总结算(ans)最小，先把**单价**小的排在前面。每个奶农的单价可能相同，所以
#### 可以把单价相同的奶农看作一个奶农 (把他们的总产量叠加起来)
```cpp
cin>>p>>a;//p:牛奶的单价,a:牛奶数量
if(ma.count(p))ma[p]+=a;//如果p记过则叠加
else ma[p]=a;//否则建立新的元素p
```
$3.$关于怎么按照**单价从小到大**走程序：

如输入样例：共有五种单价,3,5,6,8,9。map有一个好用的查找指令↓
```cpp
map<int,int>ma//等价于int ma[]数组,好处是map方便查找。
int r=0;
r=ma.lower_bound(r)->first;//其中r是查找的结果,ma是map容器名字
if(ma[r]>=n){ans+=r*n;break;}
else {ans+=ma[r]*r;n-=ma[r];r++;}
//ma.lower_bound(r)->first是查找并返回ma中大于或等于r的元素(first)
//(second则会返回该元素对应的值)
```
- 如上，$r=0$时第一次查找找到元素$3$(也就是最小的**单价**（元素）)，
- 走完$3$的程序后，$r++$变成$4$，用**while循环**重新找大于或等于$4$的**元素**，于是就找到了$5$……
### 代码
```cpp
#include<iostream>
#include<map>
using namespace std;
int n,m,ans=0;
map<int,int>ma;
void record(){//record:记录，记下所有单价和总量
	cin>>n>>m;int p,a;
	for(int i=0;i<m;i++){
		cin>>p>>a;
		if(ma.count(p))ma[p]+=a;//这里是单价相同的叠加总量
		else ma[p]=a;
	}
	return;
}
void run(){
	int r=0;
	while(1){//因为题目明确说明所有奶农奶产量大于或等于需求。
		r=ma.lower_bound(r)->first;//所以此循环不会使r大于任意单价
		if(ma[r]>=n){ans+=r*n;break;}
		else {ans+=ma[r]*r;n-=ma[r];r++;}
	}//r是单价,ma[r]是单价r的奶产总量。
	return;
}
int main(){
	record();
	run();
	cout<<ans;
	return 0;
}
```
### 非常支持新手们去学习容器($set$,$map$,$FIFO$队列,$string$等)
## 超级有用哦！

---

## 作者：After__rain (赞：0)

看到这个题，立刻就想到了贪心
但如何贪，怎么有效的，直观的贪，这里面思维可深了

先列出最优解得情况（每一段连续的区间一定被覆盖）

（那不只要冰茶姬搞一搞就行了！！！！！！！！！）

但其实还有更简单的方法


让木板最有效的使用等价于让木板空的最少等价于让那些空了最多的就不铺木板

我们可以简易想到，这里一定要排序（排什么？？？）

当然是每一牛之间的距离（不是让木板空的最少吗？你把近的都排了，不就剩下的是距离最大的了吗？？？）

然后记得判重就ak了

弱弱的代码
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
int m,s,c,sum=0;
int cow[205];
int fa[205];
struct node{
    int price;
    int which;
}w[205];
bool cmp(int x,int y){
    return x<y;
}

bool cmp2(node x,node y){
    return x.price<y.price;
}

int main(){
    cin>>m>>s>>c;
    for(int i=1;i<=c;i++){
        cin>>cow[i];
    }
    sort(cow+1,cow+1+c,cmp);
    for(int i=1;i<c;i++){
        w[i].price=cow[i+1]-cow[i];
        w[i].which=i;
    }
    sort(w+1,w+c,cmp2);
    for(int i=1;;i++){
        if(c-i<m)break;
        //cout<<w[i].price<<endl;
        sum+=w[i].price;
    }
    cout<<sum+m<<endl;
}

```


千万要记得
# 题目给你的牛的位置没有排序


---

## 作者：RicardoShips (赞：0)

代码应该算是比较简练的

首先可以考虑贪心，而且是$O$ $($ $m$ $)$的贪心

然后再来思考一下贪心策略

这道题其实比较适合反向思维，思考难度因人而异

就是先确定一大块板，再去把它分成很多块小板

具体的来说就是从第一个牛棚到最后一个牛棚

因为这段区间的长度是一定的

又因为总共要覆盖$m$块木板,所以中间最多只能有$m$ $-$ $1$块空隙

所以我们只要找出$m$ $-$ $1$块最大的空隙，以确保木板总长度最短

所以我们可以使用两遍快速排序

第一遍排序牛棚，确定区间的长度

第二遍排序空隙，求出最长的$m$ $-$ $1$块空隙

然后依次减去最长的$m$ $-$ $1$块空隙就是所得的答案

```cpp
#include<bits/stdc++.h>
using namespace std;
int w[222];
int y[222];
int c,m,s,ans;
int main()
{
	scanf("%d%d%d",&m,&s,&c);
	for(register int i=1;i<=c;++i)
	    scanf("%d",&w[i]);
	if(m>=c) ans=c;
	else
	{
		sort(w+1,w+c+1);
		ans=w[c]-w[1]+1;
		for(register int i=1;i<=c-1;++i)
		    y[i]=w[i+1]-w[i]-1;
		sort(y+1,y+c);
		for(register int i=c-1;i>=c-m+1;--i)
		    ans-=y[i];
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：TangLongbin (赞：0)

本题是一个简单的贪心题目	
我们先将问题抽象出来	

**现在一条线段上有C个点	
用然后有至多M块长度任意的木板去覆盖这些点	
求木板总长的最小和**	

因为点的排布是随机的	
因此我们可以显然的发现	
当使用的木板越多时，总和越小（不明白的同学可以去想一想）	

**于是我们可以将问题转换成另一个问题	
我们将第一个点的位置和最后一个点的位置设为minn和maxx	
因为（minn--maxx）线段以外的没有必要去找	
去线段（minn--maxx）上找M-1最长的段空白（即没有点）的线段	
这些线段的和为cnt	
则最终的答案为maxx-minn+1-cnt**

代码实现如下：

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
int M, S, C;
int num;
int minn = 0x7fffffff, maxx = 0;
int qsum[205];
bool used[205];

void read() {
	cin >> M >> S >> C;
	for (register int i = 1; i <= C; ++i) {
		cin >> num;
		used[num]=true;//标记点的位置
		minn = min(minn, num);
		maxx = max(maxx, num);
	}
	return;
}

void presolve() {
	for (register int i = minn; i <= maxx; i++) {
		if (!used[i]) {
			qsum[i] = qsum[i - 1] + 1;
			qsum[i - 1] = 0;//因为qsum[i-1]是qsum[i]的一个真子集，所以要舍去；
		}//这里用的前缀和，qsum就是记录空白段的长度
	}
	sort(qsum + minn, qsum +1+ maxx);//排序后就得到了最长的空白段；
	return;
}

void solve() {
	int Maxx = maxx;	
	int cnt = 0;
	while (M>1&&qsum[Maxx]){//特别注意的就是当没有空白段（即qsum==0时就停止，不然数组可能越界；
		cnt += qsum[Maxx--];
		M--;
	}
	cout<<maxx - minn + 1 - cnt;
	return;
}

int main() {
	ios::sync_with_stdio(false);
	read();
	presolve();
	solve();
	//system("pause");
	return 0;
}
```

---

## 作者：LZDQ (赞：0)

## 这题怎么还有用DP的？
~~可能是我太渣了~~

题目理解：一开始用一块木板把全部的牛棚遮住，再用m-1次删除，删除相邻两个牛棚坐标差最大的木板。

样例中，肯定先删除31和40之间的木板，再删除8和14之间的木板，再删除17和21之间的木板。删除3次后就可以了。

不要把题目想得太复杂，我们只要把坐标排序，注意去重(但是这题数据好像不用去重)。

把相邻坐标相减的结果保存下来，然后再排序，选最大的m-1个结果就可以了。

~~如果答案不会求那么重新看一遍吧~~

如果这样，那么恭喜你80分。

可以买50个木板，但是只有10个牛棚需要遮，那么需要特殊判断，此时答案为10。

为了不占用屏幕，[代码](https://www.luogu.org/paste/h2bsjixf)在这里。

当然，~~像我对数据结构这么敏感的人怎么可能不优化呢~~

在tot个数里选前m个数，如果对全部数据排序，O($tot$ $log$ $tot$)，其实做了很多无用功。

这题可以用堆来优化，时间O($tot$  $log$ $m$)

原理：建一个小根堆，先往堆里放m个数，剩下tot-m个数一边push一边pop。

不知道别人有没有发现这个优化，但是既然前面已经要用O($tot$  $log$ $tot$)对坐标排序，所以这里优化几乎没有用，只能让自己更加熟悉数据结构。

```cpp
#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
priority_queue<int> que;
int m,s,c;
int sn[205],tot,ans;
bool cow[205];
int main(){
    scanf("%d%d%d",&m,&s,&c);
    for(int i=0;i<c;i++){
        scanf("%d",sn+tot);
        if(!cow[sn[tot]]) cow[sn[tot++]]=1;
    }
    sort(sn,sn+tot);
    if(m>tot){
        printf("%d\n",tot);
        return 0;
    }
    for(int i=1;i<m;i++) que.push(sn[i-1]-sn[i]);  //向大根堆中添加负数相当于小根堆 
    for(int i=m;i<tot;i++){
        que.push(sn[i-1]-sn[i]);
        que.pop();
    }
    ans=sn[tot-1]-sn[0];
    for(int i=1;i<m;i++){
        ans+=que.top();  //因为本来就是负数所以直接加法 
        que.pop();
    }
    printf("%d\n",ans+m);
    return 0;
}
```


---

## 作者：_gjm2005_ (赞：0)

其实这题构造好贪心模型就好了，最好让用1块木板的几个牛棚距离尽量少。
a[i]表示第i只牛的牛棚编号。建立一个存储相邻牛棚距离差的数组，对它从大到小排序。假设一开始ans为一块连续地大木板，先解决距离大的，使2个牛棚之间不再用一块连续地木板。最后直到不能提供木材了。
```cpp
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
using namespace std;

const int NR = 210;

int a[NR],cha[NR];//a储存位置，cha储存差

bool cmp(int a,int b) {return a > b;}//为了让sort从大到小排序

int main()
{
  //freopen("test.in","r",stdin);
  //freopen("test.out","w",stdout);
  int m,s,c;
  scanf("%d%d%d",&m,&s,&c);
  
  if(m >= c)//如果数量足够多，可以一个牛棚用一块木板
  {
  	printf("%d\n",c);
  	return 0;
  }
  
  for(int i = 1;i <= c;i++) 
     scanf("%d",&a[i]);//读入位置 
     
  sort(a + 1,a + 1 + c);//由小到大排序
  
  for(int i = 1;i < c;i++) 
    cha[i] = a[i + 1] - a[i];
  sort(cha + 1,cha + c,cmp);
  
  int ans = a[c] - a[1] + 1;
  for(int i = 1;i < m;i++)
  	ans -= cha[i] - 1;
  	
  printf("%d\n",ans);
  return 0;
}

```

---

## 作者：lixiao189 (赞：0)

### 思路：
首先我们有一些地方木板是必须要覆盖的，那就是有牛的牛棚，所以我们可以先用一个book数组，用book[i]=1标记牛棚i有牛，之后我们用

O(最后一个有牛的牛棚编号-第一个有牛的牛棚编号+1)的时间就可以扫一遍整个数组，统计出有牛的牛棚的个数。之后由于不耻的老板供应木板是有数量限制的，所以我们在这之后还要把一些没有木板的地方连接起来，知道剩下的木板数量符合条件为止。假设有这样的一个区间，这个区间中所有的木板盖着的牛棚都是有牛的，在所有的这样的区间以外的牛棚都是没有牛的，我们先统计出这样区间有几个，之后就可以得到我们需要合并多少的区间，这样之后在把没有牛的区间长度统计出来并把每个没牛的区间的长度放入一个数组中，之后对数组进行排序，之后选出需要的长度，加在答案上就可以了。

ps：其实这道题目的解法其实就是最小生成树的简化版本

### 代码：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 1e4+5;

int m,s,c;
int start=99999999,end1=-99999999;
int arr[N];
int book[N];

int main(){
	scanf("%d%d%d",&m,&s,&c);
	int tx;
	for(int i=1;i<=c;i++){
		scanf("%d",&tx);
		start=min(start,tx);
		end1=max(end1,tx);
		book[tx]++;
	}
	int sum=0;
	for(int i=start;i<=end1;i++){
		if(book[i]==1){
			sum++; //联通木条总长度
		}
	}
	int cnt=0; //连续牛棚区间的数量
	for(int i=2;i<=end1;i++){
		if(book[i]!=book[i-1] && book[i]==0){
			cnt++;
		}
	}
	if(book[end1]==1) cnt++;
	int rest=cnt-m; //需要联通的区间的数量
	int t_sum=0,head=0;
	for(int i=start;i<=end1;i++){ //获取每个未联通的区间的长度并存入数组 arr
		if(book[i]==0){
			t_sum++;
		}
		if(book[i]!=book[i-1] && book[i]==1 && i!=start){
			arr[head++]=t_sum;
			t_sum=0;
		}
	}
	if(book[end1]==0) arr[head++]=t_sum;
	sort(arr,arr+head); //也许有 Bug
	for(int i=0;i<rest;i++){
		sum+=arr[i];
	}
	printf("%d\n",sum);
	return 0;
}
```

---

## 作者：SIGSEGV (赞：0)

大家都是把一块木板从头铺到尾然后断开差最大的几个，但其实每个牛棚铺一块木板然后连上差最小的几个也行啊......
 
弄一个diff数组  ~~装差~~ 放差

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int m,s,c,ans,diff[300],a[300];
int main ()
{
	scanf("%d%d%d",&m,&s,&c);
	for (int i = 0;i < c;i++) scanf("%d",&a[i]);//读入
	ans = c;至少要放这么多
	sort(a,a + c);//排个序
	for (int i = 0;i < c - 1;i++) diff[i] = a[i + 1] - a[i] - 1;//算差
	sort(diff,diff + c - 1);//再次排序
	//for (int i = 0;i < c - 1;i++) printf("%d ",diff[i]); 调试用代码，请忽略
	int len = c,i = 0;
	while (len > m) //木板数不符合要求
	{
		len--;ans += diff[i++];
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：Celebrate (赞：0)

这一题有一个很神奇的地方：

n个牛棚：

用一个木板的最小花费：第一个牛棚和最后一个牛棚的差+1

用两个木板的最小花费:用一个木板的最小花费-最大的两个木板的间隔

好了有了这个就可以开始贪心了，这一题中贪心比dp效果跟好（个人感觉）

代码如下：

```cpp
#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
inline int cmp(const void *xx,const void *yy)
{
	int x=*(int*)xx;
	int y=*(int*)yy;
	if(x>y) return 1;
	if(x<y) return -1;
	return 0;
}
int n,m,k,a[510],f[510];
int main()
{
	int i,x,y,ans;
	scanf("%d%d%d",&n,&m,&k);
	for(i=1;i<=k;i++) scanf("%d",&a[i]);//输入 
	if(n>=k)//特殊判断 
	{
		printf("%d\n",k);
		return 0;
	}
	qsort(a+1,k,sizeof(int),cmp);//排序 
	for(i=1;i<k;i++) f[i]=a[i+1]-a[i]-1;//求出间隔 
	qsort(f+1,k-1,sizeof(int),cmp);//排序间隔 
	ans=a[k]-a[1]+1;//一个木板的长度 
	int t=k-n+1;if(t<1) t=1;
	for(i=k-1;i>=t;i--) //这里有一个细节，就是n个木板就要减n-1次 
		ans-=f[i];
	if(ans<0) ans=0;
	printf("%d\n",ans);return 0;//输出 
}
```

---

## 作者：浥轻尘 (赞：0)

### 做题的第一步当然是读题  
有些牛棚里是没有牛的  
木板是**没有长度限制**的，但是**有数量限制**。  
约翰这个小妖精偏偏想买**长度总和最短**的木板，把所有的牛都拦起来。

给出:   
可能买到的木板最大的数目**M**   
牛棚的总数**S**    
牛棚里牛的总数**C**  
和牛所在的牛棚的编号**stall_number**

###  思路
要用最短的木板，就是在M的限制下，留出最多的空牛棚。这样就可以机智的转化问题。把**最短的木板-->去掉最多的空牛棚**。  
不可以让任何一只牛牛吹风受冻，牛与前一只牛之间空的牛棚，就是可以去掉的空牛棚。  
从中找到M-1个空牛棚组合成的 **最多的空牛棚组合**，忽略他们，不栏他们，就可以解决问题了。

####  最短的木板=第一只牛到最后一只牛的距离-最多的空牛棚组合
第一只牛前的牛棚和最后一只牛以后的牛棚都不用拦起来啦。

### 实现
```
#include<iostream>
using namespace std;
int main()
{
    int c,m,s,N[1000],fb[1000];
    cin>>m>>s>>c;
    for(int i=1;i<=c;i++)
        cin>>N[i];
    for(int i=1;i<=c;i++)//牛的编号并没有按顺序给出，细心读题
     for(int j=i+1;j<=c;j++)
     	{
            if(N[j]<N[i]) 
            {
                int t=N[j];
                N[j]=N[i];
                N[i]=t;
            }
        }
    
    for(int i=2;i<=c;i++)
    {
        fb[i]=N[i]-N[i-1]-1;//求牛与上一只牛的空牛棚数	
    }
    for(int i=2;i<=c;i++)
     for(int j=i+1;j<=c;j++)
     	{
            if(fb[j]>fb[i]) 
            {
                int t=fb[j];
                fb[j]=fb[i];
                fb[i]=t;
            }
        }
    int x=0;//最多空牛棚组合
    for(int i=1;i<=m-1;i++)//m个木板把牛分成m个部分，m的部分有m-1个空
    {
        x=fb[i+1]+x;//因为之前按照降序排列，所以直接可以计算
    }

    int sum=N[c]-N[1]+1-x;
    cout<<sum<<endl;
}
```


---

## 作者：Bruteforces (赞：0)

看你们都用贪心，只有我用DP吗



```cpp
var
  a:array[0..200]of longint;
  f:array[0..50,0..200]of longint;
  m,n,c,i,j,k,t,x,y,z,ans:longint;
function min(x,y:longint):longint;
begin
  if x<y then exit(x) else exit(y);
end;
begin
  readln(m,n,c);
  for i:=1 to c do
    readln(a[i]);
  for i:=1 to c-1 do
    for j:=i+1 to c do
      if a[i]>a[j] then
        begin
          k:=a[i];a[i]:=a[j];a[j]:=k;
        end;
  fillchar(f,sizeof(f),$7f);
  for i:=0 to m do f[i,i]:=i;
  for i:=1 to m do
    for j:=1 to c do
      f[i,j]:=min(f[i-1,j-1]+1,f[i,j-1]+a[j]-a[j-1]);
  ans:=maxlongint;
  for i:=m downto 1 do
    if f[i,c]<ans then ans:=f[i,c];
  writeln(ans);
end.
f[i,j]表示用i块木板覆盖前j个牛棚（要先排序），木板的最小长度
```

---

## 作者：何苗苗 (赞：0)




    
    
    
    
                            
    
```cpp
#include <stdio.h>
#include <stdlib.h>
int camp (const void *p,const void *q)  // 从小到大排序 
{
    return *(int *)p - *(int *)q;
}
int fun (const void *p,const void *q) // 从大到小排序 
{
    return (*(int *)p - *(int *)q)*(-1);
}
int main ( void )
{
    int m, s1, c, i ;
    int a[210], b[210], sum;
    scanf ( "%d%d%d", &m, &s1, &c);
    for ( i=0; i < c; i++)
    {
        scanf ( "%d",&a[i]);
    } 
    qsort ( a, c, sizeof(int), camp); // 把有牛的牛棚编号按从小到大的顺序 排序
    if ( m >= c)
    {
        printf ( "%d\n", c );
        return 0;
    }
    for ( i = 0; i < c-1; i++) 
    {
        b[i] = a[i+1] - a[i] - 1;  // 相邻两个有牛的牛棚之间的间隙长度 
    }
    qsort ( b, c-1, sizeof(int), fun); // 间隙是按从大到小的顺序排列
    sum = a[c-1] - a[0] + 1 ; // 从第一个有牛的牛棚到最后一个有牛的牛棚的总长度  
    for ( i = 0; i < m-1 ;i++)  // m 块板 ，总共有 m-1 个间隙 
    {
        sum = sum - b[i];   
    }
    printf ( "%d\n", sum);    
    return 0;
}

```

---

## 作者：hfuuwh (赞：0)

#include"stdio.h"//另一种解法是总长度减去间隔比较大的前几个间隔

    
```cpp
int a[205]={0},f[205],e[205]={0};
int main()
{
    int m,s,c,i,j,t,ans=0;
    scanf("%d%d%d",&m,&s,&c);
    for(i=1;i<=c;i++)
           scanf("%d",&a[i]);
    if(m<c)
   {
     f[1]=e[1]=0;
    for(i=1;i<c;i++)//将牛棚的序号排序 
       for(j=i+1;j<=c;j++)
       {
           if(a[i]>a[j])
           {
               t=a[i];
               a[i]=a[j];
               a[j]=t;
           }
       }
       for(i=2;i<=c;i++)//得出牛棚间隔 
       {
        f[i]=a[i]-a[i-1];
        e[i]=f[i];
        } 
    for(i=1;i<m;i++)//将间隔排序 
       for(j=i+1;j<=c;j++)
       {
           if(e[i]<e[j])
           {
               t=e[i];
               e[i]=e[j];
               e[j]=t;
           }
       }
       for(i=1;i<m;i++)
       {
              for(j=1;j<=c;j++)
              if(e[i]==f[j])//将长度大的变为0 
              {
                  f[j]=0;
                  break;
              }
       }
       for(i=1;i<=c;i++)
            ans+=f[i];
           printf("%d",ans+m);//m块木板，减去要加上1 
     }    
     else 
       printf("%d",c);
    return 0;
}
```
/\*
20 50 18

3
4
6
8
14
15
16
17
21
25
26
27
30
31
40
41
42
43
\*/

---

## 作者：「QQ红包」 (赞：0)

题解：by redbag

ac记录：http://dev.luogu.org:3308/record/show?rid=690246

原文地址：http://redbag.duapp.com/?p=987

我的博客：http://redbag.duapp.com/ 欢迎来踩

此题用贪心。如果空比较长那个地方就不放板子，有一种特殊情况，就是可以放足够多的板子，那么就一间牛棚一个吧。

- /\*
- ID: ylx14274

- PROG: barn1

- LANG: C++

- \*/

```cpp
- #include<set>
- #include<map>
- #include<list>
- #include<queue>
- #include<stack>
- #include<string>
- #include<math.h>
- #include<time.h>
- #include<vector>
- #include<bitset>
- #include<memory>
- #include<utility>
- #include<stdio.h>
- #include<sstream>
- #include<iostream>
- #include<stdlib.h>
- #include<string.h>
- #include<algorithm>
- #define LL unsigned long long
- using namespace std;
- int m,s,c,i,sum;
- int a[201],b[201];//存编号
- bool cmp(int a,int b)
- {
- return a>b;
- }
- int main()
- {
- freopen("barn1.in","r",stdin);
- freopen("barn1.out","w",stdout);
- scanf("%d%d%d",&m,&s,&c);//最大的数目m，牛棚的总数s牛棚里牛的总数c
- for (i=1;i<=c;i++) scanf("%d",&a[i]);//读入
- if (m>=c)//如果可以放的板子足够多，那就一间牛棚一个吧
- {
- cout<<c<<endl;
- return 0;
- }
- sort(a+1,a+c+1);//a数组从小到大排序
- sum=a[c]-a[1]+1;//最长的覆盖长度，所有的放在一个板子下
- for (i=1;i<c;i++)//求间隙大小
- b[i]=a[i+1]-a[i];//b[i]为a[i]和a[i+1]之间的间隙
- sort(b+1,b+c,cmp);//从大到小排序
- for (i=1;i<m;i++)//本来就有一块，i是切的块数
- {
- sum=sum-b[i]+1;
- }
- cout<<sum<<endl;
- return 0;
- }
- //友情提示：抄代码的记得删文件
```

---

## 作者：snxiang (赞：0)

没有C++的代码，来补一个。

其实很简单，先对牛棚排个序，求一下Max-Min。再对牛棚间隙排个序去掉最大的几个就行了。（不知道为什么，但必须用menset初始数组，不然就一定80分）

```cpp
#include<iostream>
#include<algorithm>
#include <iterator>
#include<string>
using namespace std;

bool cmp(int a, int b){ return a > b; }

int main()
{

    int w, p, c;
    int cow[205];
    int co[205];
    memset(co, 0, sizeof(co));
    int i, j;
    cin >> w >> p >> c;
    for (i = 0; i < c; i++){ cin >> cow[i]; }
    sort(cow, cow + c);
    int sum = cow[c - 1] - cow[0]+1;
    for (j = 0; j < c - 1; j++){ co[j] = cow[j + 1] - cow[j]-1; }
    sort(co, co + j,cmp);
    for (i=0;i<w-1; i++){ sum -= co[i]; }
    cout << sum <<endl;
    return 0;
}
```（c/c++）


---

## 作者：旋风猪皮 (赞：0)

看了这道题，我发现牛棚的总数好像并没有什么用？！我们可以先假设所有的牛棚被一块木板盖住，那么此时木板长度就是有牛的牛棚中最大编号-最小编号+1（在下面写作F）。而题目中又说要用m个木板，所以说只需要从现在这块木板中“断开”m-1个地方，既可以满足题目要求。

然后可以用贪心算法，先算出每两个相邻的有牛的牛棚的编号差，然后把这些编号差从大到小进行排序（因为题目要求求最短木板总长度），接着用F减去排序后的前m-1个编号差减掉（就是使这两个牛棚之间假设的木板断开），剩下的F即为答案。

至于贪心的成立性，显然吧？你去“切”距离小的肯定不如去“切”距离大的。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int m,s,c,a[201],b[201],f;//a用来存储牛所在牛棚的编号，b用来储存相邻牛棚的编号差。
int main()
{
    cin>>m>>s>>c;
    for(int i=1;i<=c;i++)
    cin>>a[i];//读入
    if(m>=c)//这里需要一个特判，如果说木板数比牛的数量还多，那肯定就是每个有牛的牛棚面前盖一个，直接输出牛数。
    {
        cout<<c;
        return 0;
    }
    sort(a+1,a+c+1);//把有牛的牛棚编号排序，不要被样例迷惑了，数据不一定按编号从小到大读。
    f=a[c]-a[1]+1;//先假设用一块木板，别忘了+1，如题。
    for(int i=1;i<=c-1;i++)
    b[i]=a[i+1]-a[i];//把每两个相邻的有牛的牛棚编号差求出来。（排了序，可以保证a[i]和a[i+1]是相邻的两个有牛的牛棚）
    sort(b+1,b+c);//排序
    for(int i=c-1;i>=c-m+1;i--)//把相邻编号差最大的m-1个减掉，即为最后的答案
    {
        f-=b[i];
        f++;//+1，如题
    }
    cout<<f;//输出
    return 0;
}
```

---

## 作者：远航之曲 (赞：0)

思路同楼下,把牛棚之间的间隙从大到小排序,再从大到小减去间隙,直到块数等于最大购入量.

[/color]```cpp

#include<iostream>
#include<algorithm>
#include<cstdio> 
using namespace std;

const int MAXS = 202;
const int MAXM = 50;

int dis[MAXS];
int stn[MAXS];

int main(){
    int m,s,c,i,x;
    freopen("barn1.in","r",stdin);
    freopen("barn1.out","w",stdout);
    cin >> m >> s >> c;
    if(m >= c) { cout << c << endl; return 0;}
    for(i = 0; i < c; i++)
        cin >> stn[i];
    sort(stn, stn+c);//编号从大到小排序 
    for(i = 0; i < c-1; i++)
        dis[i] = stn[i+1] - stn[i]-1;//所有间隔 
    sort(dis,dis+c-1);//所有间隔按从大到小排列 
    x = stn[c-1] - stn[0] +1;
    for(i = 0; i < m-1; i++)
        x -= dis[c-2-i];//从大到小减去那些间隔，直到块数等于最大购入量
    cout << x << endl;
    return 0;
}

```


其实还有另一种想法,用dp做:

将所有牛的牛棚序号a[]排序后,设f[i,j]表示用前i个木板修到第j头牛所用的最短长度.

 f[i,j]=min{f[i-1,j-1]+1,f[i,j-1]+a[j]-a[j-1]}  

f[i-1][j-1]+1表示在第j个牛棚使用一块新的木板（长度为1）覆盖， f[i][j-1]+a[j]-a[j-1]表示延长第i块木板至第j个牛棚。

懒癌发作,不想写.


---

