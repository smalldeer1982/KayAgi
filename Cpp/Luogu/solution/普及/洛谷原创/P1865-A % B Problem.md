# A % B Problem

## 题目背景

题目名称是吸引你点进来的。    
实际上该题还是很水的。

## 题目描述

给定 $l, r$，求区间 $[l, r]$ 内质数的个数。

## 说明/提示

#### 数据范围与约定

- 对于 $20\%$ 的数据，保证 $n,m\le 10$。
- 对于 $100\%$ 的数据，保证 $1\le n\le1000$，$1\le m\le10^6$，$-10^9\le l\le r\le 10^9$。

## 样例 #1

### 输入

```
2 5
1 3
2 6```

### 输出

```
2
Crossing the line```

# 题解

## 作者：Enderturtle (赞：151)

首先，这个是在“数论”这个任务里的

那我们就聊聊数论。

素数（质数）的定义大家小学都学过：除了1和它本身没有其他约数的数叫素数，有其他约数的叫合数，1既不是素数，也不是合数；

~~（这个先搁置一边）~~

我们判断素数的程序大家应该都写过

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;//n保证是自然数 
    cin>>n;
    if(n==1)
    {
        cout<<"既不是素数，也不是合数";
        return 0; 
    }
    for(int i=2;i<=sqrt(n);i++)
    {
        if(n%i==0)
        {
            cout<<"是合数";
            return 0; 
        }
    }
    cout<<"是素数";
    return 0;
}
```
这个方法的原理就是素数的定义；

当然在这里，这样求区间素数个数显然会超时；

所以我们换个角度从判断素数，变成判断合数；

合数显然是可以分解质因数的，既然如此，也就说明，质数的倍数（倍数>1）都是合数，所以就有了埃氏筛（不懂各种筛法的同学可以看洛谷[【模板】线性筛素数](https://www.luogu.org/problemnew/show/3383 "【模板】线性筛素数")的题解）

本质上就是从2开始把它除本身的倍数全部删去，以此类推（这时你可能要问那到这个数的时候怎么判断它是不是质数，事实上，如果自然数N在N-1的时候没有把它标记掉就肯定是质数（具体证明可百度））

区间和可以用前缀和处理；

f[r]-f[l-1] (此处已修改，感谢@33028120040712wcl @Kyle_Lowry，以前太弱了~~现在也是~~)

下面是代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int f[1000001];
bool vis[1000001];

void shai(int n)
{
    f[1]=0;
    vis[1]=true;
    for(int i=2;i<=n;i++)
    {
        if(vis[i]==false) //在筛里进行前缀和
        {
            f[i]=f[i-1]+1;//前缀和计算
            for(int j=i+i;j<=n;j=j+i)
            {
                vis[j]=true;//标记操作
            }
        }
        else f[i]=f[i-1];//前缀和转移
    }
}

int main()
{
    int n,m;
    scanf("%d%d",&m,&n);
    shai(n);
    for(int i=1;i<=m;i++)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        if(l<1 || r>n) cout<<"Crossing the line"<<endl;//判断是否超出区间
        else 
        {
            int y=f[r]-f[l-1];//此处已经修改
            cout<<y<<endl;
        }
    }
    return 0;
}
```

---

## 作者：BeyondStars (赞：51)

今天借这道题给大家介绍一下一种编程方法：**面向储存的源码级轻量预处理编程**
其实这道题很简单，~~数论什么的，我数学差，不会~~。我用的**面向储存的源码级轻量预处理编程**。这样的话时间非常短，只有80ms，并且内存只用了**788KB**，我看过提交记录，是最少的。以下是对它的定义  

>面向储存的源码级轻量预处理编程是一种在算法竞赛(competitive programming)中常用技巧(skill)，它是一种基于预处理的思想尔演变出来的编程方法。要采用这种方法，首先可以把整个程序分为两部分：1.生成器(genernater) 2.结果程序(result)。我们通常使用生成器把一定的结果预处理出来，然后再把它结合到结果程序里面，这样可以很快的针对算法竞赛中的各种数据而采用最合适的策略。并且这种方法对使用者思维水平要求较低。但是它的缺点就是当生成器的运行时间过长或者结果过于繁杂会导致这种方法不适应。     ------沃·镃基德·百科

~~说白了就是打表~~

**面向储存的源码级轻量预处理编程**预处理出从1到kn的质数个数，类似于前缀和的样子。这样子呢，就可以把这道题做成分块的题，直接判断l和r在哪个区间内然后求出1-r的质数个数再减去1-l的质数个数就是答案。
以下是生成器代码:
```cpp
#include <cstdio>
#include <iostream>
#include <fstream>
using namespace std;
int read(){
	int f = 1,x = 0;
	static char c = getchar();
	while(c<'0'||c>'9'){if(c=='-')f = -1;c = getchar();}
	while(c>='0'&&c<='9')x = (x<<1)+(x<<3)+c-'0';
	return f*x;
}
bool judge(int x){
	if(x==1)return false;
	for(int i = 2;i*i<=x;i++){
		if(x%i==0)return false;
	}
	return true;
}
const int block_length = 125;
int main(){
	ofstream out("data");//C++自带的流输出，不懂得可以查一下，推荐使用必应而不是百度
	int cnt = 0;
	int tot = 0;
	for(int i = 1;i<=1000000;i++){
		if(judge(i)){
			cnt++;
		}
		tot++;
		if(tot == block_length){
			out<<cnt<<',';
			tot = 0;
			printf("%.2lf\n",(double)i/(double)1000000);//输出处理进度 
		}
	}
	out.close();
	return 0;
}
```
然后我们可以做出一个预处理结果~~打表~~  把这个结果和**结果程序**有机结合在一起，于是我们就成功的使用**面向储存的源码级轻量预处理编程**  
以下是AC代码：
```cpp
#pragma GCC optimize("Ofast")
#include <fstream>
#include <stdlib.h>
#include <algorithm>
#include <cstdio>//打表程序
using namespace std;
inline int read(){
    char ch = getchar();
    int f = 1 ,x = 0;
    while(ch > '9' || ch < '0'){if(ch == '-')f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0';ch = getchar();}
    return x * f;
}
int table[10000]= {168,303,430,550,669,783,900,1007,1117,1229,1335,1438,1547,1652,1754,1862,1960,2064,2158,2262,2360,2464,2564,2668,2762,2860,2961,3055,3153,3245,3340,3432,3538,3638,3732,3824,3923,4017,4107,4203,4291,4392,4494,4579,4675,4761,4851,4946,5035,5133,5222,5319,5408,5500,5590,5683,5782,5873,5963,6057,6145,6232,6320,6413,6493,6591,6675,6774,6854,6935,7033,7128,7218,7301,7393,7484,7567,7662,7746,7837,7925,8017,8106,8190,8277,8362,8450,8543,8619,8713,8802,8887,8984,9070,9157,9252,9336,9418,9505,9592,9673,9766,9853,9933,10024,10106,10198,10274,10365,10453,10536,10620,10701,10789,10871,10964,11045,11135,11214,11301,11389,11475,11563,11651,11734,11818,11901,11987,12076,12159,12244,12327,12414,12496,12576,12665,12761,12841,12926,13010,13097,13184,13266,13343,13422,13507,13591,13674,13757,13848,13933,14023,14111,14188,14272,14357,14433,14521,14598,14683,14768,14852,14933,15016,15093,15173,15254,15337,15410,15497,15584,15665,15754,15833,15916,15991,16086,16159,16248,16342,16413,16492,16583,16662,16745,16836,16915,17002,17082,17170,17245,17326,17415,17499,17573,17658,17734,17821,17907,17984,18061,18148,18226,18304,18381,18464,18547,18634,18719,18807,18891,18977,19046,19127,19213,19287,19363,19443,19527,19618,19696,19776,19857,19937,20020,20104,20180,20260,20349,20437,20521,20599,20675,20746,20833,20906,20982,21055,21142,21221,21301,21392,21468,21545,21633,21713,21797,21876,21964,22044,22115,22203,22281,22362,22438,22525,22597,22675,22761,22837,22914,22987,23066,23150,23230,23308,23395,23489,23564,23642,23726,23804,23887,23958,24038,24121,24204,24278,24359,24432,24519,24604,24681,24753,24843,24920,24991,25062,25139,25224,25308,25385,25463,25531,25616,25691,25773,25846,25919,25997,26082,26165,26237,26321,26409,26489,26571,26644,26720,26800,26879,26948,27034,27120,27196,27273,27357,27441,27522,27608,27687,27767,27848,27919,28006,28091,28164,28250,28323,28404,28484,28566,28638,28719,28796,28873,28957,29037,29114,29182,29266,29343,29420,29500,29580,29656,29736,29818,29895,29977,30051,30132,30214,30290,30377,30456,30523,30603,30686,30757,30825,30904,30980,31064,31141,31218,31303,31382,31454,31522,31592,31668,31749,31822,31904,31989,32069,32140,32217,32300,32372,32448,32522,32603,32681,32761,32839,32908,32983,33067,33148,33227,33313,33400,33475,33547,33622,33697,33779,33860,33930,34001,34077,34152,34222,34305,34372,34453,34532,34614,34687,34768,34842,34911,35001,35081,35148,35230,35315,35390,35465,35538,35615,35698,35779,35853,35924,36002,36073,36162,36238,36317,36401,36481,36566,36648,36721,36791,36866,36941,37020,37092,37177,37265,37347,37415,37483,37556,37626,37706,37798,37874,37937,38009,38083,38165,38238,38315,38390,38458,38535,38604,38678,38755,38840,38914,38983,39066,39151,39223,39310,39388,39461,39539,39619,39705,39780,39849,39934,40005,40082,40160,40242,40317,40382,40445,40527,40605,40688,40766,40844,40920,40987,41069,41149,41236,41304,41385,41457,41538,41617,41691,41758,41834,41910,41993,42069,42140,42216,42291,42363,42445,42515,42592,42673,42739,42824,42907,42983,43061,43134,43217,43296,43365,43442,43521,43605,43677,43747,43825,43905,43973,44052,44126,44198,44269,44356,44423,44501,44572,44645,44722,44800,44881,44949,45018,45091,45167,45244,45322,45401,45476,45547,45627,45704,45765,45853,45921,45995,46072,46158,46219,46302,46369,46446,46524,46596,46668,46739,46819,46904,46976,47061,47133,47203,47280,47358,47435,47511,47588,47661,47740,47813,47891,47963,48044,48123,48210,48283,48351,48422,48489,48569,48646,48724,48801,48880,48953,49025,49098,49174,49247,49330,49406,49479,49553,49625,49703,49781,49861,49934,50005,50081,50160,50231,50306,50391,50472,50539,50612,50689,50759,50833,50908,50986,51055,51125,51195,51266,51341,51408,51489,51566,51636,51718,51796,51869,51943,52002,52074,52151,52222,52290,52360,52446,52521,52595,52674,52747,52831,52892,52966,53051,53120,53198,53271,53342,53412,53491,53564,53647,53717,53791,53868,53945,54022,54095,54169,54235,54309,54384,54460,54536,54613,54686,54761,54835,54898,54980,55063,55138,55216,55282,55360,55432,55506,55580,55662,55736,55815,55875,55954,56031,56104,56180,56257,56330,56409,56471,56543,56618,56689,56770,56841,56928,56996,57078,57152,57229,57306,57384,57460,57532,57605,57671,57754,57823,57888,57955,58029,58107,58184,58257,58343,58418,58487,58563,58638,58714,58789,58858,58934,59005,59080,59154,59233,59302,59380,59450,59531,59598,59672,59745,59812,59876,59943,60019,60090,60166,60238,60306,60391,60464,60535,60618,60688,60754,60822,60901,60978,61055,61135,61203,61282,61354,61436,61514,61582,61659,61733,61810,61885,61955,62031,62103,62170,62240,62316,62397,62468,62538,62620,62688,62763,62838,62915,62985,63058,63138,63206,63284,63355,63437,63508,63581,63660,63737,63809,63880,63951,64036,64102,64172,64241,64319,64398,64466,64536,64605,64683,64761,64833,64902,64974,65052,65121,65196,65271,65333,65416,65491,65563,65647,65725,65796,65877,65955,66024,66093,66161,66237,66316,66398,66466,66533,66606,66677,66741,66821,66890,66960,67029,67112,67180,67258,67328,67397,67474,67549,67617,67687,67764,67838,67904,67975,68048,68126,68202,68271,68342,68419,68493,68576,68636,68716,68796,68864,68942,69022,69095,69174,69232,69308,69373,69448,69528,69603,69670,69748,69823,69903,69972,70044,70117,70186,70263,70339,70410,70487,70555,70623,70703,70772,70844,70918,70998,71062,71137,71213,71274,71348,71421,71491,71554,71635,71705,71785,71865,71944,72026,72088,72169,72240,72294,72367,72437,72509,72588,72663,72734,72806,72878,72950,73031,73107,73187,73261,73324,73394,73474,73543,73612,73688,73756,73837,73905,73976,74047,74119,74187,74261,74340,74412,74488,74561,74627,74699,74765,74832,74907,74983,75053,75131,75196,75269,75345,75403,75472,75549,75618,75686,75774,75845,75919,75993,76063,76136,76202,76277,76350,76426,76504,76578,76641,76726,76796,76862,76922,77002,77067,77134,77209,77279,77349,77419,77495,77571,77634,77705,77777,77848,77927,77992,78060,78138,78207,78276,78359,78433,78498,};
const int block_length = 1000;
bool judge(int x){
    if(x==1)return false;
    for(int i = 2;i*i<=x;i++){
        if(x%i==0)return false;
    }
    return true;
}
int cal(int a,int b){
    int ba = a/block_length;int bb = b/block_length;
    if(bb-ba<=1){//ab在同一块内,上暴力
        int cnt = 0;
        for(int i = a;i<=b;i++){
            if(judge(i))cnt++;
        }
        return cnt;
    }else{//ab不在同一块内，分块+打表
        int sum1 = 0;
        int sum2 = 0;
        for(int i = ba*block_length+1;i<=a-1;i++){if(judge(i)){sum1++;}}

        if(a>=block_length)sum1+=table[ba-1];
        for(int i = bb*block_length+1;i<=b;i++)if(judge(i))sum2++;
        sum2+=table[bb-1];
        return sum2-sum1;
    }
}
int main(void){
//    freopen("a.txt","r",stdin);
//    freopen("b.txt","w",stdout);
    int n,m;
    n = read(),m = read();
    int l,r;
    while(n--){
        l = read(),r = read();
        if(l>m||l<1||r<1||r>m||l>=m){
            printf("Crossing the line\n");
            continue;
        }else{
            printf("%d\n",cal(l,r));
        }
    }
    return 0;
}

```
注意，两份代码中的block_legth表示的是每一块的长度，必须保持一致(虽然数据比较水，不一致也可以过好几个点)
之前为了跑快点块大小开150被卡了，现在换成1000又可以过了
![结果](https://cdn.luogu.com.cn/upload/pic/41305.png)

---

## 作者：杨咩咩咩啊 (赞：29)

首先，~~我认为~~我码风很丑。

## 好我们开始正经写题解。

### 【关键词】记忆化搜索，素数判断，AC  
~~是的就是题目标签里的两个词，很水~~

### 【思路】
1，从**1到m**遍历，**前缀和**求出**每个数及之前**的质数个数。  
2，1到n输入区间，直接查询：**a[r]-a[l-1]** ，输出。   
（注意是L-1而不是L，因为包括L~~这里是故意用的大写L因为l和1太像不好区分~~）  
3，提交，AC~  
~~4，自己不太会判断时间复杂度，但是自己感觉我这个代码过不了可能会T，，，交了居然一遍AC也是蛮神奇的了hhh，可能是数据水叭~~
### 惯例附【代码】：
（建议思路看会的就自己写叭毕竟~~码风丑而且~~自己写记得才牢哇）
```cpp
/*(^-^)*/
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
#define ll long long
ll n,m,l,r,t,a[1000005];

bool judge(ll x)
{
	if(x==1)return false;//来个特判
	for(ll i=2;i<=sqrt(x);i++)
		if(x%i==0)return false;
	return true;
}
//简单的判断素数

int main()
{
	scanf("%lld %lld",&n,&m);
	for(ll i=1;i<=m;i++)
	{
		if(judge(i))a[i]=a[i-1]+1;
		else a[i]=a[i-1];
	}
    //1~m的遍历
	
    for(ll i=1;i<=n;i++)
	{
		scanf("%lld %lld",&l,&r);
		if(l>m||r>m||l<1||r<1){printf("Crossing the line\n");}
		else printf("%lld\n",a[r]-a[l-1]);
	}//输入输出完事儿~
	return 0;
}
```

---

## 作者：Lucaster_ (赞：29)

## 首先奉上AC代码
```cpp
#include<cstring>
#include<iostream>
#define N 1000001
using namespace std;
int i,j,m,n,l,r,x,p[N],ans[N];
bool ip[N];
int tot=0;
int main()
{
	cin>>n>>m;
	memset(ip,true,sizeof(ip));
	ip[0]=ip[1]=false;
	ans[1]=0;
	for(i=2;i<=m;++i)
	{
		ans[i]=ans[i-1];
		if(ip[i])
		{
			p[++tot]=i;
			ans[i]=tot;
		}
		for(j=1;j<=tot&&i*p[j]<=m;++j)
		{
			ip[i*p[j]]=false;
			if(i%p[j]==0) break;
		}
	}
	for(i=1;i<=n;++i)
	{
		cin>>l>>r;
		if(l<1||r>m) cout<<"Crossing the line";
		else cout<<ans[r]-ans[l-1];
		cout<<endl;
	}
	return 0;
}
```


没错……

正如原题中所说……

标题是吸引你进来的……

这题跟%这个东西没有任何关系

~~其实还是可以扯上一些关系的：就是我秒切这道题后可能会收到%%%hhhhh~~

一看数据范围：-10^9~10^9
——
哇要完，又要打线段树了

等等
——
为什么会有负数

再读一遍题

crossing the line（好像是越界的意思）的条件之一即l为负数啊

那这道题就成了线筛一波+查询+输出

（不会线筛的同学们先[来这](https://www.luogu.org/problemnew/show/P3383)）

至于如何快速求区间内个数呢
想到了前缀和

比如说：我们自己造一组样例2 7

答案应该是4（2,3,5,7）

我们在筛素数的过程中，把每个素数是第几个素数记录下来，就相当于一个前缀和了

线筛的质数记录方法:

if(ip[i]) p[++tot]=i;

我们稍作改进

也就是这一部分

```cpp
		ans[i]=ans[i-1];
		if(ip[i])//ip是isprime的缩写，bool数组判断是否为素数
		{
			p[++tot]=i;
			ans[i]=tot;
		}
```

看不懂的同学从2开始手推几个数就明白了


然后……就没什么难点了吧

（只要不越界）输出ans[r]-ans[l-1]就AC咯！

---

## 作者：nianheng (赞：21)

### 乍一看，数据范围 -$10^9-10^9$用朴素的区间求素数一定会$TLE$~~(千万不要注意m的大小)~~

区间上的题目，数据范围又很大，我们~~自然而然~~的想到了莫大队长的算法。

相信很多~~蒟蒻~~们还不了解莫队算法，下面先简单介绍一下吧、

莫队算法是一种离线查询区间内特定数的数量的$Algorithm$，比线段树查询要简单的多，~~短小精干~~

#### 例如：
- 求解区间内至少出现$n$次的数的个数
- 区间内连续长度为$n$的序列的个数

等等……都要用莫队算法来解决

遵循着$A+B$ $Problem$大佬们的~~创新~~精神,我们~~愉快地~~用莫队算法来解决这道~~难题~~

----

----
#### 讲一下具体的做法：
- 首先将$1...m$区间内的素数打成一个表(减小常数);
- 然后将询问区间排一遍序，排序时要注意按左端点大小分组排序，每一组的大小为$\sqrt m$，根据莫队的思想，这样可以减少左右指针移动次数(不要忘记把输入顺序存起来);
- 根据我们刚才的排序，一个一个处理询问的区间，我们会发现:经过我们刚才的分组，左端点的移动次数会减少很多;

附上~~莫队核心代码~~：

```cpp
void modui(int l,int r)
{
	while(sushu[t+1]<=r)
	{
		ans++;
		t++;
	}
	while(s>1&&sushu[s-1]>=l)
	{
		ans++;
		s--;
	}
	while(sushu[t]>r)
	{
		ans--;
		t--;
	}
	while(sushu[s]<l)
	{
		if(s)
			ans--;
		s++;
	}
	return;
}
```

- 最后再根据输入顺序排一遍序，就可以输出答案啦！

最后附上全部代码：
```
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
int zu,ans,n,m,a,b,num,s,t,tot,nu,sushu[80010],bj[1000010];
struct node
{
	int l,r,poi,bs;
};
node lie[1100];
bool cmp(node x,node y)
{
	if(x.l/zu!=y.l/zu)
		return x.l/zu<y.l/zu;
	return x.l<y.l;
}
void modui(int l,int r)
{
	while(sushu[t+1]<=r)
	{
		ans++;
		t++;
	}
	while(s>1&&sushu[s-1]>=l)
	{
		ans++;
		s--;
	}
	while(sushu[t]>r)
	{
		ans--;
		t--;
	}
	while(sushu[s]<l)
	{
		if(s)
			ans--;
		s++;
	}
	return;
}
bool cm(node x,node y)
{
	return x.bs<y.bs;
}
void qsushu(int x)
{
	sushu[0]=1;
	for(int i=2;i<=x;i++)
		if(!bj[i])
		{
			sushu[++nu]=i;
			for(int j=1;j*i<=x;j++)
				bj[j*i]=1;
		}
	return;
}
int main()
{
	scanf("%d%d",&n,&m);
	qsushu(m);
	sushu[nu+1]=123123123;
	zu=sqrt(m);
	while(n--)
	{
		tot++;
		scanf("%d%d",&a,&b);
		if(a<1||b>m)
		{
			lie[tot].l=123123123;
			lie[tot].r=lie[tot].l;
			lie[tot].bs=tot;
		}
		else
		{
			num++;
			lie[tot].l=a;
			lie[tot].r=b;
			lie[tot].bs=tot;
		}
	}
	sort(lie+1,lie+tot+1,cmp);
	s=0;
	t=0;
	for(int i=1;i<=num;i++)
	{
		modui(lie[i].l,lie[i].r);
		lie[i].poi=ans;
	}
	sort(lie+1,lie+tot+1,cm);
	for(int i=1;i<=tot;i++)
		if(lie[i].l==123123123)
			printf("Crossing the line\n");
		else
			printf("%d\n",lie[i].poi);
	return 0;
}
```

~~是不是很容易理解啊？？~~

---

## 作者：Lemon_lover (赞：13)

```cpp
#include<cstdio>//谁说暴力一定会超时的
#include<cstring>//本宝宝的线段树+暴力成功ac
#include<iostream>
#include<cmath>
using namespace std;
int n,m,xx=0,ans;
struct tree{//线段树，sum存质数个数
    int val,sum;
};tree t[4000005];
inline int read(){//读入优化
    char a;bool fla=0;
    a=getchar();int ret=0;
    while((a<'0'||a>'9')&&a!='-') a=getchar();
    if(a=='-'){
        fla=1;a=getchar();
    }
    while(a>='0'&&a<='9'){
        ret=ret*10+a-'0';
        a=getchar();
    }
    if(fla) return 0-ret;
    else return ret;
}
int judge(int x){//暴力判断质数
    if(x==1) return 0;
    for(int i=2;i<=sqrt(x);i++){
        if(x%i==0) return 0;
    }
    return 1;
}
void build(int l,int r,int v){
    if(l==r){
        t[v].val=++xx;
        if(judge(t[v].val)==1) t[v].sum=1;
        return;
    }
    int mid=(l+r)/2;
    build(l,mid,2*v);
    build(mid+1,r,2*v+1);
    t[v].sum=t[2*v].sum+t[2*v+1].sum;
}
void query(int l,int r,int v,int a,int b){
    int mid=(l+r)/2;
    if(a<=l&&b>=r){
        ans+=t[v].sum;
    }
    else if(b<=mid){
        query(l,mid,2*v,a,b);
    }
    else if(a>mid){
        query(mid+1,r,2*v+1,a,b);
    }
    else{
        query(l,mid,2*v,a,b);
        query(mid+1,r,2*v+1,a,b); 
    }
}
int main(){
    ios::sync_with_stdio(false);
    n=read();m=read();
    build(1,m,1);
    for(int i=1;i<=n;i++){
        int x,y;x=read();y=read();
        if(x<1||y>m){
            cout<<"Crossing the line"<<endl;continue;
        }
        ans=0;
        query(1,m,1,x,y);//区间查询
        cout<<ans<<endl;
    }
}
```

---

## 作者：䜣昤丶 (赞：10)

#### 题目: [P1865 A%B problem](https://www.luogu.org/problemnew/show/P1865)

~~我翻了一遍题解貌似没有和我用一样的方法的..~~

~~在看到**题目描述**之前,我还真没看懂这道题的意思...~~ 没想到是查询区间素数的个数.

然后看到了$l,$ $ r$的范围...开了个$longlong$.. ~~恢复了一下心态~~

没想到后面查询的范围只和$m$有关。 ~~我开心的拍起了肚皮~~


## 正文开始

### **理解题意:**

看完题目会发现,其实小于了$1$的 $l$会直接判出界,大于了$m$的 $r$也会直接判定出界

因此本题的思路则转化为:**求区间$[1, m]$中任意一段区间的素数个数**

### **思路:**

首先想到的是在线筛法 (输入每一组数据都重新数一遍) 

结果->[戳这里](https://www.luogu.org/recordnew/show/15821012)。 $T$了$4$个嗷!!!

然后突然想到可以把查询拎出来啊 (就是离线筛啦)...判断$[1, m]$的素数，用$flag[i]$数组打一个标记，$0$为初始状态，$1$则是代表有约数的整数 (即合数)，打一个~~烙印~~ 标记为合数。

//$\color{#FF5151}\text{关于i }\mathrm{}$ $i$代表区间$[1, m]$中的每一个数,程序内只需要查询$i$是否为合数,是则打个标记 $(flag[i] = 1)$

每输入一个需要查询的区间$[l, r]$,就数一数其中$flag[i]=0$的个数即可.

### **优化:**

一个很小很小很小的优化:大于 $2$ 的偶数可以直接在筛之前就全部打标记，这样只要查询奇数是否为合数。(就只需要判断一半的整数了 $very$ $nice$)

**解释:**所有大于 $2$的偶数都2整除了啊. ~~这有什么好解释的$qwq$~~

**$bug$点:**但是$2$属于质数啊.所以加一个判断。

$i$从$2$开始,走完一遍之后$i--;$ $i+=2$ 然后 $i$ 就成功转变成了$3$ $5$ $7$ ……

~~我不管我就不让ans = 1;~~

### **理解:**

在这里解释一下为什么求合数的约数是要开根号的.

每个数都能拆成 $:$ $N=a*b$ ($N$为正整数)的形式,不同的是 $a$ $b$ 的值.

除开约数是本身和$1$来说，每个合数的最大约数就是本身开根号。

否则是一个数大于$\sqrt{N}$一个数小于$\sqrt{N}$

$N=\sqrt{N}*\sqrt{N}$ $←$ 很明显只有这种情况下$N$的约数是最大的.可自行举例验证

因此$j$只要 $<=$ $\sqrt{i}$ 也就是 $j*j<=i$ (两边平方)

~~这样可以省去一个头文件省去一个sqrt了~~
 

### **代码实现:**

//吸个氧就$AC$啦~~ ~~(不吸氧会[$T$一个点](https://www.luogu.org/recordnew/show/15890333)..我也不知道咋办qwq~~
```cpp
#include <iostream>
#include <cstdio>
using namespace std;

//定义变量, 次数n, 范围m,   l, r表示区间.  flag数组用来判断是不是素数
int n, m, ans, flag[1000000+6];
long long l, r;

//简单的加法. 
int pd(int l ,int r)
{
	ans = 0; //初始化计数
	for (int i = l; i <= r; i++) //查询区间素数个数
		if (flag[i] == 0) ans++; //如果没有打标记的 则为素数,计数++
	return ans;//把计数丢回去输出
}

int main()
{
	scanf ("%d %d", &n, &m);
	for (int i = 4; i <= m; i+=2)//把 > 2的偶数打标记
		flag[i]=1;
	for (int i = 2; i <= m; i+=2)//i相当于要求的素数 
	{
		for (int j = 2; j * j <= i; j++)//j是合数的约数 
			if (flag[i] != 1)
				if (i % j == 0)
				{
					flag[i] = 1;//如果是合数,定为1
					break;//只要找到它有一个非本身和1的约数,就可以直接判断下一个数i了~~
				}
		if(i == 2) i--; //让循环从奇数3开始
	}
	for (int i = 1; i <= n; i++)
	{
		scanf ("%ll %ll", &l, &r);//cin >> l >> r;
		//越界的情况 
		if(r > m || l < 1) {printf ("Crossing the line\n"); continue;}
		if (r < 2) {printf("0\n"); continue;}//这个也是越界 
		else if (l < 2) l = 2;//其实貌似这步可以不用? 
		printf ("%d\n", pd(l, r));//输出 
	}
	return 0;
}
//完结撒花~~ 
```

求过阿qwq.

#### //有不对之处还望$dalao$们指出.谢谢~

---

## 作者：7wwwwth (赞：7)

这个题不难看出用一般的判断素数的方法是会T的，那么我们就要尝试着用欧拉筛法。

我看别的题解都没有说易错的地方，我就点一下易错的点吧。

我的欧拉筛法跟别的有些不同的是用了vector

用bool数组np来记录不是素数的点，用vector p来记录是素数的点 
数组ga[i]来计算前缀和，即i前的素数数。

欧拉筛法的代码如下
```
void prime(){
	np[1]=true;
	vector<int>p;
	for(int i=2;i<=m;i++){
		if(!np[i]) p.push_back(i);
		for(int j=0;j<p.size()&&i*p[j]<=m;j++){
			np[i*p[j]]=true;
			if(i%p[j]==0) break;
		}
		if(!np[i]) ga[i]=ga[i-1]+1; //这两行是非常关键的，开始我就因为没有注意想当然的以为但pd到不是素数的就会直接break完全没有意识到跳出的是j那个循环。果然我还是太弱了
		else ga[i]=ga[i-1];
	}
}
```
全部的代码如下
```
#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
int n,m,l,r;
int t;
bool np[1000010];
int ga[1000010];

void prime(){
	np[1]=true;
	vector<int>p;
	for(int i=2;i<=m;i++){
		if(!np[i]) p.push_back(i);
		for(int j=0;j<p.size()&&i*p[j]<=m;j++){
			np[i*p[j]]=true;
			if(i%p[j]==0) break;
		}
		if(!np[i]) ga[i]=ga[i-1]+1;
		else ga[i]=ga[i-1];
	}
}


int main(){
	cin>>n>>m;
	prime();
	for(int i=1;i<=n;i++){
		cin>>l>>r;
		if(l<1||r>m||r<1||l>m) cout<<"Crossing the line"<<endl;
		else{
			cout<<ga[r]-ga[l-1]<<endl;
		}
	}
}
```

---

## 作者：Social_Zhao (赞：6)

~~好像线段树的那篇题解打的是大暴力，这个应该不重复吧~~

让我们来审一下题~~（不都该这样吗）~~
- 首先，m的范围有点大。这表示我们需要**线性筛素数**。
- 然后，我们看见了“区间”二字，于是我们就~~自然而然地~~想到了**线段树**
- 用线段树维护区间和（素数个数）
- 详见[P3383 【模板】线性筛素数](https://www.luogu.org/problemnew/show/P3383)
以及[P3374 【模板】树状数组 1](https://www.luogu.org/problemnew/show/P3374)
~~不要问我为什么是树状数组模板，看就是了~~
- ~~如果你太懒~~，你也可以选择看我这个蒟蒻的解释（dalao自行跳过）。

# 线性筛素数
- 首先，**1和0不是素数，2是最小的素数**（~~这不是废话吗~~）
- 其次，**如果一个数是素数，那么它的倍数全都不是素数**
- 那么，我们需要一个数组 
```
int is_prime[1000001]
```
(~~又是废话~~)
- 初值赋为1（为线段树服务）
```
for(register int i=1;i<=a;i++) is_prime[i]=1;
```
- 那么如果一个数没有被筛，就说明它是素数。
- ### 完整代码：
```cpp
void prime(int a) 
{
	for(register int i=1;i<=a;i++) is_prime[i]=1;
	is_prime[0]=is_prime[1]=0;
	for(int i=2;i*i<=a;i++) {
		if(is_prime[i]==1) {
			for(int j=i*i;j<=a;j+=i) {
				is_prime[j]=0;
			}
		}
	}
}
```
# 线段树
- 首先，你需要知道线段树是什么。
- 摘自百度：[（~~其实我自己也看不懂~~）](https://baike.baidu.com/item/%E7%BA%BF%E6%AE%B5%E6%A0%91/10983506?fr=aladdin)
- 线段树是一种二叉搜索树，与区间树相似，它将一个区间划分成一些单元区间，每个单元区间对应线段树中的一个叶结点。 
- 对于线段树中的每一个非叶子节点[a,b]，它的左儿子表示的区间为[a,(a+b)/2]，右儿子表示的区间为[(a+b)/2+1,b]。因此线段树是平衡二叉树，最后的子节点数目为N，即整个线段区间的长度。
- 为了方便，我写了两个宏定义：

```cpp
#define lson u<<1,l,mid
#define rson u<<1|1,mid+1,r
```
- 线段树结构体：

```
struct node {
	int l,r,sum;//维护区间和
}n[4000001];//一定要开四倍内存

```

- 那么在本题中，建树的方法如下：

```cpp
void build(int u,int l,int r)
{
	n[u].l=l;
	n[u].r=r;
	if(l==r) {//如果是叶节点
		n[u].sum=is_prime[l];return;//赋值并返回
	}
	int mid=(l+r)>>1;//中指针
	build(lson);
	build(rson);//递归建左右子树
	n[u].sum=n[u<<1].sum+n[u<<1|1].sum;//本区间和等于其左右两个子区间和
	return;
}
```
- 另外，查询的方法如下：

```cpp
int query(int u,int l,int r,int a,int b) 
{
	if(l==a&&r==b) //如果是目标区间
	{
		return n[u].sum;//返回
	}
	int mid=(l+r)>>1;//中指针
    //分类讨论：
	if(b<=mid) return query(lson,a,b);//目标区间在左子区间，递归查询
	else if(a>mid) return query(rson,a,b);//目标区间在右子区间，递归查询
	else return query(lson,a,mid)+query(rson,mid+1,b);//横跨两个区间
}
```
# dalao空降地点
- 所以，我们就有了此题的完整代码:

```cpp
#include<bits/stdc++.h>
using namespace std;

int is_prime[1000001];
int N,M;
struct node {
	int l,r,sum;
}n[4000001];

#define lson u<<1,l,mid
#define rson u<<1|1,mid+1,r

void prime(int a) 
{
	for(register int i=1;i<=a;i++) is_prime[i]=1;
	is_prime[0]=is_prime[1]=0;
	for(int i=2;i*i<=a;i++) {
		if(is_prime[i]==1) {
			for(int j=i*i;j<=a;j+=i) {
				is_prime[j]=0;
			}
		}
	}
}//线性筛

void build(int u,int l,int r)
{
	n[u].l=l;
	n[u].r=r;
	if(l==r) {
		n[u].sum=is_prime[l];return;
	}
	int mid=(l+r)>>1;
	build(lson);
	build(rson);
	n[u].sum=n[u<<1].sum+n[u<<1|1].sum;
	return;
}//建树

int query(int u,int l,int r,int a,int b) 
{
	if(l==a&&r==b) 
	{
		return n[u].sum;
	}
	int mid=(l+r)>>1;
	if(b<=mid) return query(lson,a,b);
	else if(a>mid) return query(rson,a,b);
	else return query(lson,a,mid)+query(rson,mid+1,b);
}//查询

int main()
{
	cin>>N>>M;
	prime(M);
	build(1,1,M);
	for(int i=1;i<=N;i++) {
		int l,r;
		cin>>l>>r;
		if(l<1|r>M) {
			cout<<"Crossing the line"<<endl;
			continue;
		}//越界直接进下一次循环
		cout<<query(1,1,M,l,r)<<endl;//区间查询素数个数
	}
	return 0;
}
```
- 愉快结束（~~管理大大求过~~）

---

## 作者：开心的金鸣 (赞：4)

这道题~~一看就能想到~~打质数表，首先判断素数。

朴素算法

枚举2 ~ sqrt(x)的数

粘代码
```cpp
bool pd(int x)
{
	if (x==1)return 0;
	for (int i=2;i<=sqrt(x);i++)
		if (x%i==0)return 0;
	return 1;
}
```

这应该挺好理解的，，，，

这样把质数表打完后，统计区间内质数的个数，就~~~~~~~~~~~~~~~TLE了


------------

接下来才是正解

zs[i] 表示从1~i的质数个数

然后疯狂判断素数

（不要问我为什么我一会儿质数一会儿素数的）

代码：
```cpp
int sum=0;
for (int i=1;i<=m;i++)
{
	if (pd(i))sum++;
	zs[i]=sum;
}
```

这样计算区间素数个数时，就只要用zs[y]-zs[x]就好了。

全代码：
```cpp
#include<bits/stdc++.h>
int zs[1000001];
using namespace std;
bool pd(int x)
{
    if (x==1)return 0;
    for (int i=2;i<=sqrt(x);i++)
        if (x%i==0)return 0;
    return 1;
}
int main()
{
    int n,m;
    cin>>n>>m;
    int n2=0;
    for (int i=1;i<=m;i++)
    {
        if (pd(i))n2++;
        zs[i]=n2;
    }
    for (int i=1;i<=n;i++)
    {
        int a,b;
        cin>>a>>b;
        if(b>m || a<=0)
        {
            cout<<"Crossing the line"<<endl;
            continue;
        }
        cout<<zs[b]-zs[a-1]<<endl;
    }
}
```

---

## 作者：Robert2259960864 (赞：3)

看了几页的题解，各位dalao们都是什么离线，线段树，莫队，打表，线筛……本蒟蒻没那么多本事。但是我们再次看题目，发现一段区间内的质数的数量是一定的！！！那么我们每次只要查询1~x中有多少个质数不就可以了吗？再看这个质数表，发现里面的质数的值竟然是单调的！！！~~（废话）~~
就可以用二分啦

------------
所以，我们可以先将质数记录下来
## 做成质数表
再用
## 二分查询
区间的质数的数量


------------
废话不多说，上代码~
```c
#include<bits/stdc++.h> //懒人专用头文件
using namespace std;
#define MAXN 1000005
int n,m,vl,vr,vis[MAXN],f[MAXN],ans;

void prepare(int d){ //做成质数表，用埃筛即可
	memset(vis,0,sizeof(vis));
	for(int i=2; i<=d; i++){
		if(vis[i] == 0){
			ans++;
			f[ans] = i;
			for(int j=i; j<=d; j+=i){
				vis[j] = 1;
			}
		}
	}
}

int find(int d){ //开始了！二分
	int l=0, r=ans,rt = 0;
	while(l <= r){
		int mid = (l+r)/2;
		if(f[mid] <= d){
			rt = mid;
			l = mid+1;
		}else{
			r = mid-1;
		}
	}
	return rt;
}

int main(){
	freopen("in.txt","r",stdin);
	cin>>n>>m;
	prepare(MAXN);
	while(n--){
		scanf("%d%d",&vl,&vr);
		if(vr < vl){
			swap(vl,vr);
		}
		if(vl<1 || vr>m){
			printf("Crossing the line\n");
			continue;
		}
		printf("%d\n",find(vr)-find(vl-1));
	}
	fclose(stdin);
	return 0;
}
```
然后，发现时间贼短！
（本蒟蒻第一次发题解，求过呜呜呜）


---

## 作者：royzhu (赞：3)

/\*
题目背景上说得对，这题真的水。

主要思路：

开一个1000000的int数组，每一个存1~i之间的素数个数（很暴力）

    for(int i=2;i<=m;i++)//核心代码 

    if(i%2!=0||i==2)a[i]=ss(i)+a[i-1]; 

    else a[i]=a[i-1];

\*/

```cpp
#include<cmath>
#include<cstdio>
int a[1000005];
int ss(int x)//判断素数 
{
    if(x==1)return 0;//1不是素数 
    if(x==2)return 1;//2是素数 
    for(int i=2;i<=sqrt(x);i++)//sqrt（x）是x的根号，判到它就可以 
    {
        if(x%i==0)return 0;//如果被除尽，x不为素数 
    }
    return 1;//判完都没除尽，x为素数 
}
int main()
{
    a[1]=0;
    int n,m;scanf("%d %d",&n,&m);//输入n，m 
    for(int i=2;i<=m;i++)
    if(i%2!=0||i==2)a[i]=ss(i)+a[i-1];//if(i%2!=0||i==2)是小优化 （2以上的偶数是是合数） 
    else a[i]=a[i-1];
    //a[i]=ss(i)+a[i-1]是a[i]=a[i]前所有素数的个数，如果i是素数 a[i]要加一，否则不加（比较懒，判素数的函数回的是1或0） 
    for(int i=1;i<=n;i++)
    {
        int x,y;scanf("%d %d",&x,&y);//输入x，y 
        if(x>=1&&x<=m&&y>=1&&y<=m)//判断在不在区间
        {
            printf("%d\n",a[y]-a[x-1]);//a[y]-a[x-1]表示x~y之间的素数的个数（1~y之间的素数个数-1~x之间的素数个数） 
        }
        else//否则依题意，输出 
        {
            printf("Crossing the line\n");
            continue;//到下一组数（打不打没有太大区别） 
           } 
    }
}
```

---

## 作者：Ledger (赞：2)

蒟蒻第一次发题解，若有不当之处望指出
新人上路，轻喷

先上代码：



------------

  ```cpp
#include<iostream>
#include <cstdio>
using namespace std;
#define maxn 10000000

struct node {    //开多个数组会 WA 所以可以开一个结构体来存放
	int x = 1;
	int prime = 0;
	int vis = 0;//  0为素数
}pri[maxn];
void Screening(int n) {    //  线性筛
	pri[0].vis = pri[1].vis = 1;
	int cnt = 0;
	for (int i = 2; i <= n; i++) {
		if (!pri[i].vis) pri[cnt++].prime = i;
		for (int j = 0; j < cnt && i * pri[j].prime <= n; j++) {
			pri[i * pri[j].prime].vis = 1;
			if (i % pri[j].prime == 0) break;
		}
	}
}
int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	Screening(m);
	int l, r;
	int ans = 0;
	for (int i = 2; i <= m; i++) {    //  标志当前有几个素数，做预处理， 可以有效避免TLE
		if (!pri[i].vis) 
			pri[i].x += pri[i - 1].x;
		else
			pri[i].x = pri[i - 1].x;
	}

	for (int i = 0; i < n; i++) {
		scanf("%d %d", &l, &r);
		if (l >= 1 && l <= m && r >= 1 && r <= m) {
			ans = pri[r].x - pri[l-1].x;// 这是一个坑，这是41行
			printf("%d\n", ans);
			ans = 0;
			l = 0;
			r = 0;
		}
		else printf("Crossing the line\n");
	}

	return 0;
}
```
                                           
                                                几个主要点都已经注释了，对于第41行的解释如下
 为什么要用 r 减去 l - 1 呢 而不是减去 l 呢                   首先当我们标记 1 为第一个数但是 1 不是素数，这是重点
 而第一个素数 2 的标记位数为 2 依次类推
 第 n 个素数的位数被标志为 n + 1；
 举个栗子：如果区间刚好为【2，3】那么pri[r].x - pri[l].x = 3 -2 =1
 对应的确实两个素数 则产生矛盾，所以让 l-1 得到的数才刚刚好，如果不信可以自行下载数据实践一下，毕竟实践出真知。
 

------------
补充一点这题必须进行预处理结果否则一发入魂直接TLE
                                                

---

## 作者：纸片人 (赞：2)

在写这道题之前建议先A了这道题：[P3383 【模板】线性筛素数](https://www.luogu.org/problem/P3383)

最近智推天天各种模板题（洛谷终于发现我什么算法都不知道了）。质数筛嘛，明显的基础模板。但之前一直写的是埃氏筛，这次学了个优化：[教会我这个优化的博客](https://blog.csdn.net/huang_miao_xin/article/details/51331710)

```
bool ps(int a){
    if(a==1) return 0;
    if(a==2||a==3) return 1;
    if(a%6!=1&&a%6!=5) return 0;
    for(int i=5;i*i<=a;i+=6){
        if(a%i==0||a%(i+2)==0) return 0;
    }
    return 1;
}

```
速度比普通埃氏筛还是快一些的（这个1s，埃氏筛1.31s）

另：[学委大佬的欧拉筛题解](https://www.luogu.org/blog/costudy/base-3#)。


------------

以上是质数筛的写法，接下来回归正题。先放一下AC代码吧，看了一下思路有人写过，但我是独立思考出来的qwq

```
#include<bits/stdc++.h>
using namespace std;
int flag[1000002];
bool ps(int a){
    if(a==1) return 0;
    if(a==2||a==3) return 1;
    if(a%6!=1&&a%6!=5) return 0;
    for(int i=5;i*i<=a;i+=6){
        if(a%i==0||a%(i+2)==0) return 0;
    }
    return 1;
}
int main(){
    int n,m,num=0;
    cin>>n>>m;
    for (int i=1;i<=m;i++){
        if (ps(i)) {
        	num++;
		}
		flag[i]=num;
    }
    for (int i=1;i<=n;i++){
        int l,r;
        cin>>l>>r;
        if (r>m||l<1) {
	    	cout<<"Crossing the line"<<endl;
			continue;
		}
        cout<<flag[r]-flag[l-1]<<endl;
    }
    return 0;
}
```


------------


这真的不难，然鹅——

*写码10分钟，找错半小时。*

几乎就是裸的质数筛，还是大括号的问题。下面展示一下我一开始的错误部分代码：

```
int n,m,num=0;
    cin>>n>>m;
    for (int i=1;i<=m;i++){
        if (ps(i)) {
        	num++;
		}
		flag[i]=num;//这句不能写在上面if的大括号里
    }

```
那么为什么呢？来写两段简单代码比较一下就知道了：

代码1（正解）：

```
#include<bits/stdc++.h>
using namespace std;
int flag[100];
int main (){
	int m,num=0;
    cin>>m;
    for (int i=1;i<=m;i++){
        if (i%3==0) {
        	num++;
		}
        flag[i]=num;//此时这句话在外面
        cout<<flag[i]<<endl;
    }
    return 0;
}
```

代码2（错误）：

```
#include<bits/stdc++.h>
using namespace std;
int flag[100];
int main (){
	int m,num=0;
    cin>>m;
    for (int i=1;i<=m;i++){
        if (i%3==0) {
        	num++;
        	flag[i]=num;//这句在里面
		}
		cout<<flag[i]<<endl;
    }
    return 0;
}
```

很显然这两段代码的作用是求1-m中有多少个3的倍数（固然平时不用这么写，但这道题要用flag数组就这么试验了）

>输入：9

>>代码1输出：0
0
1
1
1
2
2
2
3（实际上有换行）

>>代码2输出：0
0
1
0
0
2
0
0
3

虽然最后的结果一样（因为9是3的倍数），但上下对比可以发现，代码2有着明显的问题：非3的倍数flag[i]为0。

既然发现了错误就重新审视代码。不难看出，在代码2中，一旦i不是3的倍数，flag[i]=num 这句话便不会执行（因为在if里面一起跳掉了）。于是自然，当i不能整除3的时候，flag[i]不被赋值，也就是原来的初始值：0。

当输入不再是特殊值的时候，这个错误便会明显呈现：

>输入：8

>>代码1输出：0
0
1
1
1
2
2
**2**

>>代码2输出：0
0
1
0
0
2
0
**0**

这个zz错误差不多就总结到这里了，题目本身固然简单，错误固然明显（~~我还不是没找出来qwq~~），还是要从中吸取一些教训的（~~才能不枉费我拼死拼活赶作业+用复习明天小测的时间写这个~~）。

* 有时候答案会有部分正确，这种时候就要分析数据，想一想为什么这个就是对的答案，那种数据就错了；以及记住有时候错误过程也能得出正确答案，但它还是错的。

* （这个是找出错误后芬达大佬说的），要学会调试啊，遇到这种情况就要把flag打出来看一看。

---

## 作者：Space_Gold_Trash (赞：2)

这是我在知道线性筛之前做的

做完打开题解，线性筛是什么鬼？？？？好高级的样子（后来发现这太弱了）

然后准备发个题解，然后一直拖到现在......

废话不多说，进入正题：

弱鸡用的弱鸡方法：

设f[i]表示1-i的质数个数

那么容易想到l-r的质数个数即为f[r]-f[l-1]

那么只要预处理f即可

很显然，当k是质数，则f[k]=f[k-1]+1

否则f[k]=f[k-1]

显然f[1]=0,f[0]=0

那么就可以初始化f了


```c
#include <bits/stdc++.h>
using namespace std;
int a,b[1000001],n,m;
inline int zhi(int x){
    int i;
    if(x==1)return 0;
    else for(i=2;i<=sqrt(x);i++)if(x%i==0)return 0;
    return 1;
}
inline void shu( ){
    int i;
    b[1]=b[0]=0;
    for(i=2;i<=1000000;i++)
    if(zhi(i)==0)b[i]=b[i-1];
    else b[i]=b[i-1]+1;
}
int main( ){
    int num=0,i,j,k,x,y;
    shu( );
    scanf("%d %d",&n,&m);
    for(i=1;i<=n;i++){
        num=0;
        scanf("%d %d",&x,&y);
        if(x<1||y>m){printf("Crossing the line\n");continue;}
        else printf("%d\n",b[y]-b[x-1]);
    }
}
```

能过，数据太水

## ~~求赞~~

---

## 作者：引领天下 (赞：2)

这题大家应该都能看出来要用筛法+前缀和吧……~~所以我觉得这题顶多普及-~~

所以我来讲两个优化：

# 1. 其实前缀和并不用再开一个数组

# 2. 前缀和其实并不是非要套在循环里绕，完了再特判，只需要再开一个循环就可以了

具体看代码：

```cpp
#include <cstdio>
int n,m,l,r,a[1000000];
void prime(){
    for (int i=2;i<=m;i++)if (!a[i])
    for (int j=i*2;j<=m;j+=i)a[j]=1;//标准线筛
    for (int i=2;i<=m;i++)a[i]=!a[i],a[i]+=a[i-1];//处理前缀和：直接在同一个数组里处理，a[i]=!a[i]是把原来对质数的标记0改成1，对合数的标记1改成0，然后就可以放心地加上前面的了
}
template <typename _Tp>
inline void read(_Tp &x){
    int w=1;char c=0;x=0;
    while (c^'-'&&(c<'0'||c>'9'))c=getchar();
    if (c=='-')w=-1,c=getchar();
    while (c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x*=w;
}
inline void write(int n){
    if(n==0) return;
    write(n/10);
    putchar(n%10+'0');
}
int main(){
    read(n),read(m);
    prime();
    while (n--){
        read(l),read(r);
        if (l<1||l>m||r<1||r>m){puts("Crossing the line");continue;}
        if (a[r]-a[l-1])write(a[r]-a[l-1]);//标准前缀和输出方式
        else putchar('0');puts("");
    }
}//至于某些多打的部分是快读+快输，个人喜好。
```

---

## 作者：1010_ (赞：2)

### 线性筛素数裸题（适合练手~~（ＱＡＱ请大佬放过我ＱＡＱ）~~）

就像如下代码所写，我们从２开始枚举质数的倍数，利用质数的性质，用线性的时间复杂度筛出质数。
```cpp

#include<cstdio>
using namespace std;
const int N=1e6+1;
bool bo[N];
int sum[N],n,m;
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=2;i<=m;++i)
		if (!bo[i])
		{
			for (int j=1;j*i<=m;++j)bo[j*i]=1;／／枚举倍数
			sum[i]=sum[i-1]+1;／／筛素数时顺便记录［１，ｉ］的质数个数
		}
		else sum[i]=sum[i-1];
	for (int i=1,l,r;i<=n;++i)
	{
		scanf("%d%d",&l,&r);
		if (l<1||r>m)puts("Crossing the line");／／题目要求输出
		else printf("%d\n",sum[r]-sum[l-1]);
	}
	return 0;
}
```

---

## 作者：_Qer (赞：2)

- 素数的定义我就不说了，不知道就看各位巨佬的解释，很清楚


- 看到这题第一反应是用线段树，但是我想了想，还是没用~~（其实是不会）~~


- 用的是线性筛+前缀和，一个1000000的int数组即可


- 前面几位巨佬貌似都多用了一个bool数组


- 感觉一个数组就够了


- 数组的每一位存1~n这个区间的素数数量


- 处理当前位时只需加上上一位的素数数量，如果这一位是素数，就再加上一


- 上代码：

```cpp

#include<iostream>    
using namespace std;  
int n,m,l,r;    //依次为问题数，范围，区间的左右端点  
int ps[1000010];//第i个存1~i的素数数量  
void inprime(){ //线性筛+前缀和的函数，往ps里赋值  
    for(int i=2;i<=m;++i){//2以上都赋值为1，代表是素数（暂时）  
        ps[i]=1;  
    }  
    for(int i=2;i<=m;++i){//循环到每一位  
        if(ps[i]){        //如果是素数  
            for(int j=2;i*j<=m;++j){//线性筛  
                ps[i*j]=0;//所有倍数都标记为非素数  
            }  
        }  
        ps[i]+=ps[i-1];//前缀和，加上上一位的素数数量  
    }  
}  
int main(){  
    cin>>n>>m;  
    inprime();//初始化ps数组，调用函数  
    /*  
    for(int i=1;i<=m;++i){  
        cout<<ps[i]<<" ";  
    }  
    cout<<endl;  
    */  
    for(int i=0;i<n;++i){  
        cin>>l>>r;//区间左右端点  
        if(l<=0||r>m){//超界的情况  
            cout<<"Crossing the line"<<endl;  
            continue;  
        }else{  
            cout<<ps[r]-ps[l]+(ps[l]>ps[l-1]?1:0)<<endl;  
//如果l是素数，还要加上一，不然就要出事，因为这个区间要包括l  
//就用一个问号表达式，若？前为true，返回：前面的数，否则返回后面的  
        }  
    }  
    return 0;  
} 
```  

###### 最后宣传一下自己的~~辣鸡~~博客

[我的博客](https://www.luogu.org/blog/WAFUN/)


---

## 作者：Ameiyo (赞：2)

本蒟蒻的第一篇题解。。。。

先跑一边循环，求出1-i中的质数个数（包括i）存在pri数组中。

最后再跑一遍循环，解决问题。

首先是判断素数：



```cpp
    bool prime(int a){
        if(a<2)return false;
        for(int i=2;i<=sqrt(a);++i)
            if(a%i==0)return false;
        return true;
    }
```
然后是从1-m存储：

    for(i=1;i<=m;++i)

            if(prime(i))pri[i]+=pri[i-1]+1;//如果是质数就是前一个加一 

            else pri[i]=pri[i-1];//如果不是素数就等于前一个 

最后是解决问题：


```cpp
    for(i=1;i<=n;++i){
            int l,r;
            cin>>l>>r;
            if(l<1 || r>m){//越界 
                cout<<"Crossing the line\n";
                continue;//重新判断循环条件 
            }
            int d=pri[r]-pri[l];//l-r之间的个数等于1-r的个数减去1-l的个数 （包括r不包括l） 
            if(pri[l]!=pri[l-1])d++;//如果pri[l]=pri[l-1]就说明l不是质数，反之l是质数，所以要加上l这一个 
            cout<<d<<endl;
        }
```
全代码（AC）：

    
    
```cpp
    #include <bits/stdc++.h>
    using namespace std;
    const int x=1000005;
    int n,m,pri[x];
    bool prime(int a){
        if(a<2)return false;
        for(int i=2;i<=sqrt(a);++i)
            if(a%i==0)return false;
        return true;
    }
    int main(){
        ios::sync_with_stdio(false);
        cin>>n>>m;
        int i;
        for(i=1;i<=m;++i)
            if(prime(i))pri[i]+=pri[i-1]+1;
            else pri[i]=pri[i-1];
        for(i=1;i<=n;++i){
            int l,r;
            cin>>l>>r;
            if(l<1 || r>m){
                cout<<"Crossing the line\n";
                continue;
            }
            int d=pri[r]-pri[l];
            if(pri[l]!=pri[l-1])d++;
            cout<<d<<endl;
        }
        return 0;
    }

```

---

## 作者：RagnaLP (赞：2)

这道题是一个很不错的埃氏算法的模版

~~**如果**~~直接套就可以了

先上一段直接怼的

    
    
```cpp
    #include<iostream>
    #include<cstdio>
    #include<algorithm>
    #include<cmath>
    using namespace std;
    int _r() {//快速读入打着
        int x=0,f=1;
        char c=getchar();
        while(c>'9'||c<'0') {
            if(c=='-')f=-1;
            c=getchar();
        }
        while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
        return x*f;
    }
    int n,m;
    int pr[2000001]= {0,1};//pr[i]是否为质数，用bool一样的
    void shake(int e) { //筛法核心，不要吐槽函数名字
        int j=1,d;
        for(int i=2; i<=sqrt(e)+1; i++) {
            if(pr[i]==1) continue;//加速，算过的肯定是某一个数的倍数，再找就是重复的
            d=e/i;//划定边线
            j=2;//从这个数的两倍开始，以为这个数不一定是合数
            while(j<=d) {
                pr[i*j]=1;//倍数打标记
                j++;
            }
        }
    }
    int cnt(int l,int r) {//从l数到r
        int ans=0;
        for(int i=l; i<=r; i++) {
            if(!pr[i])
                ans++;
        }
        return ans;
    }
    void Init() {
        n=_r();
        m=_r();
        shake(m);//输入完直接筛
        int l,r;
        for(int i=0; i<n; i++) {
            l=_r(),r=_r();
            if(l<1||r>m) {//注意是或
                printf("Crossing the line\n");
                continue;
            }
            printf("%d\n",cnt(l,r));
        }
    }
    int main() {
        Init();
        return 0;
    }
```
然后的结果就是这样的
https://www.luogu.org/record/show?rid=5045423

然后我发现其实这是O(n\*m)的，而O(n+m)的其实很简单

就是多加一个预处理,计算前缀和



    
    
```cpp
    #include<iostream>
    #include<cstdio>
    #include<algorithm>
    #include<cmath>
    using namespace std;
    int _r() {
        int x=0,f=1;
        char c=getchar();
        while(c>'9'||c<'0') {
            if(c=='-')f=-1;
            c=getchar();
        }
        while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
        return x*f;
    }
    int n,m;
    int pr[2000001]= {0,1};
    int k[1000001]= {0};//用k表示i之前（包含i）有多少个质数
    void shake(int e) {//和之前的一样
        int j=1,d;
        for(int i=2; i<=sqrt(e)+1; i++) {
            if(pr[i]==1) continue;
            d=e/i;
            j=2;
            while(j<=d) {
                pr[i*j]=1;
                j++;
            }
        }
    }
    void cnt() {
        int ans=0;
        for(int i=1; i<=m; i++) {
            if(!pr[i])
                ans++;
            k[i]=ans;//就算i不是质数前面也有ans个质数（对于这个i,ans没有改变）
        }
    }
    void Init() {
        n=_r();
        m=_r();
        shake(m);
        cnt();//要在筛完之后记数，毕竟是预处理
        int l,r;
        for(int i=0; i<n; i++) {
            l=_r(),r=_r();
            if(l<1||r>m) {
                printf("Crossing the line\n");
                continue;
            }
            //千万不要写成k[r]-k[l]
            //因为是找一个闭区间的值所以应该是-k[l-1]
            printf("%d\n",k[r]-k[l-1]);
        }
    }
    int main() {
        Init();
        return 0;
}
```

---

## 作者：Seauy (赞：1)

## 前置知识：
1. Eratosthenes筛
2. 二分查找

------------

### 然而太基础的算法了直接跳过，开始进入正题

------------

看一眼数据（由于声称不看数据被各种大佬劝退，所以提醒大家一定要看数据！QAQ），当然不能暴力，至少不能每次查询的时候都要用 O(sqrt(m)) 算法来判断（除了某些玄学算法）

于是考虑一开始就把 ∈[ 2,m ] 的质数全部找出，可以用埃筛，当然做了去重优化后还可以做到线性筛，然而埃筛就已经够用了

```cpp
for(int i=2;i<=m;i++)
	if(!JCM[i])//不为合数
	{
		prime[++num]=i;//存入表中
		for(int j=2;i*j<=m;j++)
			JCM[i*j]=1;//标记
	}
```

[ 本人尝试过打表（就像首页大佬一样），然而代码太长无法提交 QAQ 所以老老实实筛吧 ]

------------

然后我们获得了质数表，运用二分查找

1. 找出第一个 >= l 的质数在表中位置，P

2. 找出最后一个 <= r 的质数在表中位置, Q

然后输出 Q-P+1 完事 qwq

[ 当然还有不在范围内的事，数据保证了 l<=r，所以只要判断两者都在范围里就行啦 ]

------------

### 完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

bool inseg(int bef,int ob,int aft)//判断在范围内
{return bef<=ob && ob<=aft;} 

int n,m;
bool JCM[1000005];//判断合数
int prime[80000],num;//质数表

int First(int ob)//二分查找第一个
{
	int L=1,R=num;
	while(L<=R)
	{
		int mid=(L+R)>>1;
		if(prime[mid]>=ob) R=mid-1;
		else L=mid+1;
	}
	return L;
}

int Last(int ob)//二分查找最后一个
{
	int L=1,R=num;
	while(L<=R)
	{
		int mid=(L+R)>>1;
		if(prime[mid]>ob) R=mid-1;
		else L=mid+1;
	}
	return R;
}

int main()
{
	scanf("%d %d",&n,&m);
	for(int i=2;i<=m;i++)//埃筛
		if(!JCM[i])
		{
			prime[++num]=i;
			for(int j=2;i*j<=m;j++)
				JCM[i*j]=1;
		}
	/*
		for(int i=1;i<=num;i++) printf("%d ",prime[i]);
		printf("\n");
	*/
	while(n--)
	{
		int a,b;
		scanf("%d %d",&a,&b);
		if(!inseg(1,a,m) || !inseg(1,b,m)) {printf("Crossing the line\n");continue;}
		printf("%d\n",Last(b)-First(a)+1);//输出
	}
	return 0;
}
```


---

## 作者：YangQuijote (赞：1)

先对【1，m】的范围用埃拉托斯特尼筛选法生成质数表（用数组a保存），然后扫描一遍整张表，用sum数组保存质数个数的前缀和，读入询问时进行特判后直接用前缀和相减的方式（sum【r】-sum【l-1】）求出答案即可。注意输出答案时无论是数字还是字符串都要输出回车（血的教训）。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int a[1000010],sum[1000010];
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    int i,j;
    a[1]=1;
    for(i=2;i<=m;i++)
    {
        if(a[i]==0)
        {
            for(j=i+i;j<=m;j=j+i)
            {
                a[j]=1;
            }
        }
    }
    for(i=1;i<=m;i++)
    {
        if(a[i]==0)
        {
            sum[i]=sum[i-1]+1;
        }
        else
        {
            sum[i]=sum[i-1];
        }
    }
    int l,r;
    for(i=1;i<=n;i++)
    {
        scanf("%d%d",&l,&r);
        if(l<1||r>m)
        {
            printf("Crossing the line\n");
        }
        else
        {
            printf("%d\n",sum[r]-sum[l-1]);
        }
    }
    return 0;
}
```

---

## 作者：s66104444 (赞：1)

刚学的欧拉筛法，果断试试，调试了2下才过。

典型的欧拉筛+前缀和。

这样才不会TLE，注意数组要大开一点。

来我的代码吧。

蒟蒻的丑代码。


```cpp
#include<iostream>
#include<cstring>
using namespace std;
int pri[1000000];
int vst[1000000];
int tot=0;
int n,m;
int sum[1000000];
int main()
{
    scanf("%d%d",&n,&m);
    memset(vst,0,sizeof(vst));
    vst[1]=1;//1排除掉。
    for(int i=2;i<=m;i++)
    {
        if(!vst[i])pri[++tot]=i;
        for(int j=1;j<=tot;j++)
        {
            int t=pri[j]*i;
            if(t>m)break;
            vst[t]=1;
            if(i%pri[j]==0)break;
        }
     }
     sum[1]=0;
     for(int i=2;i<=m;i++)
     {
         if(vst[i]==0)sum[i]=sum[i-1]+1;
         else sum[i]=sum[i-1];
      }
      for(int i=1;i<=n;i++)
      {
          int l,r;
          scanf("%d%d",&l,&r);
          if(l<=0||r>m)
          {
              cout<<"Crossing the line"<<endl;
              continue;
          }
          else {
              cout<<sum[r]-sum[l-1]<<endl;
          }
       } 
    return 0;
}
```

---

## 作者：FREEH (赞：1)

\_用筛法，可以快速求出范围内的素数。\_

\_用部分和，如果当前数是素数，前一部分+1，否则+0。\_


代码：

```cpp
#include<cstdio>
#include<iostream>
using namespace std;
int n,m,sum[1000005];
bool s[1000005];
int main()
{
    scanf("%d%d",&n,&m);
    for (int i=2;i*i<=m;i++)
        if (s[i]==0)
        for (int j=2;j<=m/i;j++)
            s[i*j]=1;//筛法求素数
    s[1]=1;//1不是质数（我忘记加了这句话，错了1次）
    for (int i=1;i<=m;i++)
        sum[i]=sum[i-1]+(1-s[i]);//部分和
    for (int i=1;i<=n;i++)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        if (a<1||b>m) {printf("Crossing the line\n");continue;}//不在范围内
        printf("%d\n",sum[b]-sum[a-1]);
    }
    return 0;
}
```

---

## 作者：fzj2007 (赞：1)

# 一看题目       P1865 A % B Problem
点进来秒杀掉他————

然而，点进来发现没有那么简单。。。~~（不过还是很简单）~~

好了，步入正题

**一道长长的分界线**

------------

首先看题目：题目描述：区间质数个数（好平淡啊）

输入格式：
一行两个整数 询问次数n，范围m接下来n行，每行两个整数 l,r 表示区间

原来是素数啊。。。

下面来几个模板：
No1 最简单素数模板：
```
isPrime(int x){
    for(int i=2;i<x;i++)
   	  if(x%2==0) return false;
    return true;
}
```



---

## 作者：ikka (赞：1)

普及组~~都拿不到省一的~~蒟蒻来分享一下自己的代码

这题乍一看是很简单，其实就是很简单，暴力判素数也挂不了

但喜欢折腾的我非搞了一个线段树+欧拉筛

没什么可说的，线段树求区间和，欧拉筛判素数，直接上代码



```cpp
    #include <cstdio>
    #include <cstring>
    #define lch (id<<1)        //左孩子，等于id*2 
    #define rch (id<<1|1)        //右孩子 ，等于id*2+1 
    const int N = 1000000 + 10;
    int psize,isprime[N],prime[N>>2];
    struct segtree{
        int l,r;
        int sum;
    }st[N<<2];        //线段树 
    void is_prime()        //欧拉筛筛素数 
    {
        memset(isprime,1,sizeof(isprime));
        isprime[1]=0;
        for(int i=2;i<=N;i++)
        {
            if(isprime[i]) prime[++psize]=i;
            for(int j=1;j<=psize&&i*prime[j]<=N;j++)
            {
                isprime[i*prime[j]]=0;
                if(!(i%prime[j])) break;
            }
        }
    }
    void creat(int id,int l,int r)        //建树 
    {
        st[id].l=l; st[id].r=r;
        if(l==r)
        {
            st[id].sum=isprime[l]?1:0;        //sum用来存储素数个数 
            return;
        }
        int mid=(l+r)>>1;
        creat(lch,l,mid); creat(rch,mid+1,r);
        st[id].sum=st[lch].sum+st[rch].sum;
    }
    int stsum(int id,int l,int r)        //区间求和 
    {
        if(st[id].l==l&&st[id].r==r) return st[id].sum;
        int mid=(st[id].l+st[id].r)>>1;
        if(r<=mid) return stsum(lch,l,r);
        if(l>mid) return stsum(rch,l,r);
        return stsum(lch,l,mid)+stsum(rch,mid+1,r);
    }
    int main()
    {
        is_prime();        //筛素数 
        int n,m,l,r;
        scanf("%d%d",&n,&m);
        creat(1,1,m);        //建树 
        for(int i=1;i<=n;i++)
        {
            scanf("%d%d",&l,&r);
            if(l<1||l>m||r<1||r>m)        //判断给出的l，r是否在区间内 
            {
                printf("Crossing the line\n");
                continue;
            }
            printf("%d\n",stsum(1,l,r));        //输出区间求和结果 
        }
        return 0;
}
```

---

## 作者：nekko (赞：1)

。。。裸筛素数。。。然而不会线性筛QAQ。。。

埃氏筛法（应该是这个名字）：若要求1～n之间所有素数，则枚举2～sqrt(n)之间的所有自然数，每次将枚举的自然数的倍数删去（一倍除外），最后剩下的数就是1～n之间的素数。（当然要先删掉1咯。。。QAQ）



```cpp
    #include <cstdio>
    int n,m,l,r,s[1000005];
    int main(){
        scanf("%d%d",&n,&m);
           for(int i=2;i<=m;i++)s[i]=1;
        for(int i=2;i*i<=m;i++)
               for(int j=i+i;j<=m;j+=i)
                s[j]=0;
        for(int i=1;i<=m;i++)
            s[i]+=s[i-1];
        while(scanf("%d%d",&l,&r)==2)
            (l<1||r>m)?printf("Crossing the line\n"):printf("%d\n",s[r]-s[l-1]);
}
```

---

## 作者：Mine_King (赞：0)

## 方法一：
我会暴力！暴力枚举l~r每一个数，判断是不是质数，并记录下来，复杂度O(肯定过不了)
## 方法二：
[线性筛素数](https://www.luogu.org/problem/P3383)，不懂的可以看[这个](https://www.luogu.org/blog/yhdhg1395754790/solution-p3383)。所以筛完之后再枚举一下l~r就行了。复杂度O(很悬)
## 方法三：
在方法二的基础上，我们其实可以记录前缀和，即1~n有几个质数，即$sum_n = sum_{n-1} + f_n$，这里sum是前缀和数组，f是质数标记。sum可以在筛完后O(n)更改，也可以在筛地过程中改，具体看代码叭。
```cpp
#include<cstdio>
using namespace std;
int n,m;
bool f[1000005];//质数标记
int sum[1000005];//前缀和数组
int main()
{
	scanf("%d%d",&n,&m);
	f[1]=true;//注意1不是质数
	for(int i=2;i<=m;i++)//埃筛法筛质数
	{
		if(!f[i])
		{
			sum[i]=sum[i-1]+1;//如果这个数是质数，那么就要+1
			for(int j=i*2;j<=m;j+=i) f[j]=true;//记得更改后面的值哦
		}
		else sum[i]=sum[i-1];//否则就不用加
	}
	for(int i=1;i<=n;i++)
	{
		int l,r;
		scanf("%d%d",&l,&r);
		if(l<1||r>m) printf("Crossing the line\n");//注意判断l和r的范围
		else printf("%d\n",sum[r]-sum[l-1]);
	}
	return 0;
}
```
[安利一发博客~](https://www.luogu.org/blog/yhdhg1395754790/)

---

## 作者：ShadowNight (赞：0)

先看题分析：


1.询问范围为[1，m]，很自然就会想到埃氏筛

2.询问n次，这tm明示的数据存储，用啥存呢？
各位还记得学线段树前提到了为了快速运算区间数的和，我们使用数组存储s[i]= 1->i Σa[i]，区间大小s[r]-s[l-1].所以现在我们同理存储s[i]=1~i中质数的个数就好啦！

开两个数组，埃氏筛和区间和：
```cpp
int s[1000001];// 区间和
bool f[1000001];//埃氏筛
```
埃氏筛和求区间和代码：

```cpp
for(int i=2;i<=m;i++)//1不用管，从2开始
	{
		s[i]=s[i-1]+(!f[i]);
      //质数时f[i]=0，!f[i]=1,强制int转换形成递推关系式
		if(!f[i])//i为质数时，i的倍数都为合数
		for(int j=i*2;j<=m;j+=i)f[j]=true;
	}
```
提问解答代码：

```cpp
for(int i=1;i<=n;i++)
	{
		int l,r;cin>>l>>r;
		(l<1||r>m)?			//越界判断
      cout<<"Crossing the line"<<endl//越界输出
      :cout<<s[r]-s[l-1]<<endl;		 //区间质数个数
      //三目大发好啊
	}
```

最后附上完整代码：
```cpp
#include<iostream>
using namespace std;
const int Friendship_is_Magic=;
int s[1000001];
bool f[1000001];
int main()
{
	int n,m;cin>>n>>m;
	for(int i=2;i<=m;i++)
	{
		s[i]=s[i-1]+(!f[i]);
		if(!f[i])
		for(int j=i*2;j<=m;j+=i)f[j]=true;
	}
	
	for(int i=1;i<=n;i++)
	{
		int l,r;cin>>l>>r;
		(l<1||r>m)?cout<<"Crossing the line"<<endl:cout<<s[r]-s[l-1]<<endl;
	}
	return Friendship_is_Magic;//防白嫖√
}
```



---

## 作者：qiyue1118 (赞：0)

直接用prim的算法求解，会有3个TLE，原因是计算素数用的时间太长。
我们可以先把1到M的素数全部算出来，然后保存在数组里，最后直接求区间arr[r]-arr[l-1]之间的素数即可。  
- 重点：
如何保存从1到M之间的素数个数？  
从1开始，如果当前数是素数，就在前一个计算结果arr[j-1]的基础上加1，如果不是，就继续保留上一个arr[j-1]的计算结果，也可以理解为arr[j-1]+0。
```java

```
for(int j=1;j<=M;j++) {
			if(prim(j))
				arr[j]=arr[j-1]+1;
			else
				arr[j]=arr[j-1];
		}
```java
import java.io.*;
import java.util.*;

public class Main {
	static int N,M,arr[];

	public static void main(String[] args) throws Exception {
		// TODO Auto-generated method stub
//		System.setIn(new FileInputStream("C:\\Users\\SDSC-XAD\\Downloads\\testdata (5).in"));
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer s=new StringTokenizer(br.readLine());
		N=Integer.parseInt(s.nextToken());
		M=Integer.parseInt(s.nextToken());
		arr=new int [M+1];
		for(int j=1;j<=M;j++) {
			if(prim(j))
				arr[j]=arr[j-1]+1;
			else
				arr[j]=arr[j-1];
		}
		for(int i=0,l,r;i<N;i++) {
			s=new StringTokenizer(br.readLine());
			l=Integer.parseInt(s.nextToken());
			r=Integer.parseInt(s.nextToken());
			int count=0;
			if(l<1 || r>M)
				System.out.println("Crossing the line");
			else {
				System.out.println(arr[r]-arr[l-1]);
			}
			
		}
		
}	
	static boolean prim(int n) {
		if(n==1) return false;
		if(n==2) return true;
		if(n%2==0) return false;
		for(int i=3;i<=Math.sqrt(n);i=i+2) {
			if(n%i==0)
				return false;
		}
		return true;
			
		}
}	

```


---

## 作者：vivianru (赞：0)

先来看一下题意

~~我弄了半天才清楚~~

给你两个数，一个范围最小值，一个范围最大值

要你求范围中有多少个质数

前提：最小值不小于1，最大值不超过m

若不满足前提，则输出Crossing the line

满足则求解

注意：最好别用暴力方法，会超时

~~我就在#4，#5，#6上超时了~~

~~不止一次~~

废话不多说，还是赶紧贴一下代码吧
```cpp
#include<bits/stdc++.h>
using namespace std;
int ans;//输出 
int n,m,l,r;//询问次数n,范围m,区间l,r
int zs[100000000];
int qzh[100000000];
void qzhzs()
{ 
    zs[1]=1;//1不是素数 
    for(int i=2;i*i<=m;i++)
	{ 
        if(zs[i]==0)
		{ 
			for(int j=i*i;j<=m;j+=i)
			{
				zs[j]=1;//它们都不是素数
			}
             
        }
    }
    for(int i=2;i<=m;i++)
	{ 
        qzh[i]=qzh[i-1];//将它前一位数的值先赋上 
        if(zs[i]==0)
		{
			qzh[i]++;//若是素数就加1
		} 
    }
}
int main()
{
	cin>>n>>m;//询问次数n,范围m
	qzhzs();//先把准备工作做好 
	for(int i=1;i<=n;i++)
	{
		cin>>l>>r;
		if(l<1 || r>m)//越界 
		{
			cout<<"Crossing the line"<<endl;//直接输出
			continue;//并跳到下一组 
		}
		else
		{
			ans=qzh[r]-qzh[l-1];//最大值前的质数个数减（最小值-1）前的质数个数就是答案了 
			
		} cout<<ans<<endl;//都到这一步了说明肯定有 
			ans=0;//别忘了把ans清0
	}
	return 0;
}
```
对了

感谢@skiy_gyx提供的判断素数思路

其他应该也没什么了

吧

---

## 作者：Dzhao (赞：0)

## 看着大佬们什么样的代码都有，但是都太高端了，像我这样的~~蒟蒻~~
# 太弱了
于是我来发一篇较好理解的

-------------------------------------------------我是分割线------------------------------------------------

首先，看到这道题，第一反应就是
## 暴力
但是，看过了数据范围，发现
## 铁定TLE
于是我们会想到使用前缀和来做，用pi来存1~i这段区间内质数的数量，再求l~r区间的质数数量时，即可用p[r]-p[l-1]来求，这样查找的时间复杂度就是O(1)
## GOOD
那么现在我们来看下代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 1000009
int p[N];
bool judge(int x) //素数判断 
{
    if(x<=1) return 0;
    if(x==2) return 1;
    if(x%2==0) return 0; //优化 
    for(int i=3;i<=sqrt(x);i+=2)
        if(x%i==0) return 0;
    return 1;
}
int main()
{
    int n,m,l,r;
    cin>>n>>m;
    p[0]=0; //初始化 
    p[1]=0; 
    p[2]=1;
    for(int i=3;i<=m;i++) //核心，求前缀和 
    {
        if(judge(i)) p[i]=p[i-1]+1;
        else p[i]=p[i-1];
    }
    for(int i=1;i<=n;i++)
    {
        cin>>l>>r;
        if(l<1 || r>m) //越界 
        {
            printf("Crossing the line\n");
            continue;
        }
        printf("%d\n",p[r]-p[l-1]); // 输出l~r区间质数数量 
    }
    return 0;
} 
```
### [评测记录](https://www.luogu.org/recordnew/show/20195060)
香甚




---

## 作者：MissKingchen (赞：0)

1. 首先题目意思是给n组测试数据，每组测试数据是一个区间，求区间l-r里有多少个质数，如果这个区间的l<1或者r>m也就是超区间就输出Crossing the line否则输出答案；
1. 看懂意思我们来想解题方法，如果每个区间进行一次质数求和，那么肯定超时，大佬的代码我们又看不懂！怎么办？可以看看我这个蒟蒻的质数判断答案保留法
1. 肯定是可以的，对于给定的m,先对1~m里的每个数的答案进行保留，然后给我区间我就能直接用当前的尾区间的质数的个数减去头区间质数的个数，当然头减尾时头得往前一个位置，因为头可能就是一个质数，我们不能减去它
1. 答案用数组保留，具体请看代码
```cpp
#include<iostream>
#include<cmath>
using namespace std;
int ans[1000005];		//答案 
int isprime(int x)		//质数判断优化方法，不会的也可以暴力判断 
{
	if(x==2||x==3)
	return 1;
	if(x%6!=1&&x%6!=5)
	return 0;
	for(int i=5;i<=sqrt(x);i+=6)
	if(x%i==0||x%(i+2)==0)
	return 0;
	return 1;
}
int main()
{
	cin.tie(0);				//优化cin 
	int n,m;
	cin>>n>>m;
	ans[1]=0;				//1不能在isprime里判断，所以直接写答案 
	for(int i=2;i<=m;i++)
	ans[i]=ans[i-1]+isprime(i);		//2~i区间质数的个数等于前一个区间质数的个数加上当前这个数是不是质数 
	int l,r;
	while(n--)
	{
		cin>>l>>r;
		if(l<1||r>m)
		cout<<"Crossing the line"<<endl;
		else
		cout<<ans[r]-ans[l-1]<<endl;	//l-1,前面说了，头可能是一个质数,请保留它做质数的权利 
	}
	return 0;
} 
```


---

## 作者：Portland (赞：0)

对于每一道题，先写一个思路，这是个好习惯


```
#include<iostream>
using namespace std;

int n,m,l,r;
bool isprime[1000005]={0};

int main(){
	int i,j;
	cin>>n>>m;
	
	线性筛出质数

	for(i=0;i<n;i++){
		cin>>l>>r;
		if(越界){
			cout<<"Crossing the line\n";
		}
		else{
			cout<<l到r间质数个数<<endl;
		}
	}
	return 0;
}
```
思路写好了，先解决线性筛
```
for(i=2;i<=m;i++){ 
//0,1不是质数，从2开始假设他们全部都是质数   
	isprime[i]=true;
}
for(i=2;i<=m;i++){
	if(isprime[i]){ //如果i是质数，则i的倍数都不是质数
		for(j=i*2;j<=m;j+=i){
			isprime[j]=false;
		}
	}
}
```
然后，解决越界条件，越界条件是：$r>m || l<1$

接着，求l到r之间的质数个数
```
for(j=l;j<=r;j++){
	if(isprime[j])
		ans++;
}
```
最后，整合代码
```
#include<iostream>
using namespace std;

int n,m,l,r;
bool isprime[1000005]={0};

int main(){
	int i,j;
	cin>>n>>m;
	
	for(i=2;i<=m;i++){
		isprime[i]=true;
	}
	for(i=2;i<=m;i++){
		if(isprime[i]){
			for(j=i*2;j<=m;j+=i){
				isprime[j]=false;
			}
		}
	}
	/*
	for(i=0;i<=m;i++){
		cout<<isprime[i]<<endl;
	}
	*/
	for(i=0;i<n;i++){
		cin>>l>>r;
		if(r>m || l<1){
			cout<<"Crossing the line\n";
		}
		else{
			int ans=0;
			for(j=l;j<=r;j++){
				if(isprime[j])
					ans++;
			}
			cout<<ans<<endl;
		}
	}
	return 0;
}
```

---

## 作者：jave28 (赞：0)

什么前缀和啦，我就不解释了。只是个人判断素数有些特殊罢了：

首先，我们来打个表，枚举1~100的素数：

2 3 5 7

11 13 17 19

23 29

31 37

41 43 47

53 59/

61 67

71 73 79

83 89  

97

于是不难看出凡是大于10的素数都是以1，3，7,9结尾的；所以假设一个数i，若i%6!=1&&i%6!=5,则必定不是素数，但由于3和9的存在，还要再加一个判断:

for(int k=5;k*k<=i;k+=6) if(i%k==0||i%(k+2)==0) 则不是素数;

------------华丽分割线------------------------------------------
```cpp
#include<cstdio>
using namespace std;
int n,m;
int f[1000001];
bool check(int i){
	if(i==1) return false;//1不是素数
	if(i==2||i==3) return true;//特判
	if(i%6!=1&&i%6!=5) return false;
	for(int k=5;k*k<=i;k+=6)
		if(i%k==0||i%(k+2)==0) return false;//如上
	return true;
}
void inline dp(){
	for(int i=1;i<=m;i++){
		if(check(i)) f[i]=f[i-1]+1;
		else f[i]=f[i-1];
	}
}
int main(){
	scanf("%d%d",&n,&m);
	dp();//求1~m的总素数个数和
	for(int i=1,x,y;i<=n;i++){
		scanf("%d%d",&x,&y);
		if(x<1||y>m){
			printf("Crossing the line\n");
			continue;
		}
		printf("%d\n",f[y]-f[x-1]);//输出前缀和
	}
	return 0;
}
```



---

## 作者：L62626 (赞：0)

表示dalao们的题解没怎么看懂

。。

自己写了一个特别称得上本蒟蒻身份的

：

首先依据题意把所给范围内的素数筛出来

    for(int i=2;i<=sqrt(m);i++)

    {

        if(!b[i])
 
        {

            for(int j=i*2;j<=m;j+=i)

            b[j]=1;

        }

    }

其中i小于根号m即可

其次要注意b[1]=1;

输入l，r。直接判断即可

上代码

    #include<iostream>
    #include<cstdio>
    #include<cmath>
    using namespace std;
    bool b[10000005];
    int main()
    {
	    int n,m;
	cin>>n>>m;
	b[1]=1;
	for(int i=2;i<=sqrt(m);i++)
	{
		if(!b[i])
		{
		    for(int j=i*2;j<=m;j+=i)
		    b[j]=1;
		}
	}
	while(n--)
	{
		int l,r;
		scanf("%d%d",&l,&r);
		if(l<1||r<1||l>m||r>m)//判断是否越界
		cout<<"Crossing the line"<<endl;
		else
		{
			int num=0;
			for(int i=l;i<=r;i++)
			if(!b[i]) num++;
			printf("%d\n",num);
		}
	}
	return 0;
}

---

## 作者：Accoty_AM (赞：0)

非前缀和题解
灵感来自大于5的质数都在6的两侧
代码
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
bool a[10000010];
int n,m,r,l,sum;
inline bool pd(int num){
	if(num==1)return 0;
	if(num==2||num==3)return 1;
	if(num%6!=1&&num%6!=5)return 0;
	for(int i=5;i<=sqrt(num);i+=6){
		if(num%i==0||num%(i+2)==0)return 0;
	}
	return 1;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=sqrt(m);++i){
		if(pd(i)){
			int tot=i+i;
			while(tot<=m){
			a[tot]=1;
			tot+=i;
			}
		} 
	}
	a[1]=1;
	for(int i=1;i<=n;++i){
		scanf("%d%d",&r,&l);
		if(r<1||l>m)printf("Crossing the line\n");
		else{
			for(int i=r;i<=l;++i){
				if(a[i]==0)++sum;
			}
			printf("%d\n",sum);
			sum=0;
		}
	}
	return 0;
 } 
```

---

## 作者：Ikari_Shinji (赞：0)

### Freedom仔细想了想，发现这道题其实挺水~~（然鹅自己也交了三次QAQ）~~

## 思路：埃筛~~（欧筛我不会啊!）~~+枚举

### 主代码如下：
```c
#include<bits/stdc++.h>
using namespace std;
bool num[1000010];  //数组最好开大
int main(){
    int n,m,a,b;
    num[1]=1;   //1不是素数
    scanf("%d%d",&n,&m);
    for(int i=2;i<=1000000;i++)
        if(!num[i])     //0代表素数，1代表不是素数
            for(int j=i+i;j<=1000000;j+=i)
                num[j]=1;
    while(n--){
        scanf("%d%d",&a,&b);
        if(b>m||a<=0)   //范围是1~m，不包括负数和0
            printf("Crossing the line\n");
        else{
            int ans=0;
            for(int i=a;i<=b;i++){  //从a枚举到b
                if(!num[i])
                    ans++;  //累加答案
            }
            printf("%d\n",ans);
        }
    }
    return 0;   //完美结束
}
```
### 埃筛不会的可以看看下面的埃筛素数过程（并试着做做P3383）：
```c
   bool num[N]     //N是范围
    num[1]=1;   //1既不是素数，也不是合数
    for(int i=2;i<=1000000;i++)		//从2开始
        if(!num[i])     //0代表是素数，1则不是
            for(int j=i+i;j<=1000000;j+=i)  //将该数的倍数筛去（该数是素数）
                num[j]=1;

```
#### 管理大大求过QAQ!

---

## 作者：邱江坤 (赞：0)

分段打表+MR算法的暴力，不算快，但是可以解决问题。总共的用时是400+ms。如果数据范围特别大，这个算法的优势就显示出来了。

实际上还有更黑的科技，参考P3912 【素数个数】的题解

关于MR算法，参考[我的另一篇题解](https://rocon.blog.luogu.org/solution-p3912)和[MR算法的讲解](https://www.cnblogs.com/Norlan/p/5350243.html)
```
#include <bits/stdc++.h>
using namespace std;


    typedef long long ll;

    ll pow_mod ( ll a, ll b, ll m )
    {
        a %= m;
        ll ans = 1;
        do
        {
            if ( b & 1 )
                ans = ans * a % m;
            a = a * a % m;
        }
        while ( b >>= 1 );
        return ans;
    }

    bool Miller_Rabin ( ll n, ll a, ll d )
    {
        if ( n < 2 ) return false;
        if ( n == 2 ) return true;
        if ( n == a ) return false;
        if ( ~ n & 1 ) return false;
        while ( ~ d & 1 ) d >>= 1;
        ll t = pow_mod ( a, d, n );
        while ( d != n - 1 && t != n - 1 && t != 1 )
        {
            t = t * t % n;
            d <<= 1;
        }
        return t == n - 1 || ( d & 1 ) == 1;
    }

    bool isprime ( ll n )
    {
        static const int a[] = {2, 7, 61};
        for ( int i = 0; i < 3; ++i )
        {
            if ( n == a[i] ) return true;
            if ( !Miller_Rabin ( n, a[i], n - 1 ) ) return false;
        }
        return true;
    }
    struct Ans
    {
        int index, val;
    };
    const int segment = 1000;
    int main()
    {
        int l = 0, r = 1000000;
        
        int ans = 0;
        for ( int i = l; i <= r; ++i )
        {
            ans += isprime ( i );
            if (i % segment == 0)
            {
                cout << "{"<<i << "," << ans<<"}," << endl;
            }
        }
        cout << ans << endl;
        

    }
}



```


缺少表格的主程序
```
#include <bits/stdc++.h>
using namespace std;

namespace my
{
    typedef long long ll;

    ll pow_mod ( ll a, ll b, ll m )
    {
        a %= m;
        ll ans = 1;
        do
        {
            if ( b & 1 )
                ans = ans * a % m;
            a = a * a % m;
        }
        while ( b >>= 1 );
        return ans;
    }

    bool Miller_Rabin ( ll n, ll a, ll d )
    {
        if ( n < 2 ) return false;
        if ( n == 2 ) return true;
        if ( n == a ) return false;
        if ( ~ n & 1 ) return false;
        while ( ~ d & 1 ) d >>= 1;
        ll t = pow_mod ( a, d, n );
        while ( d != n - 1 && t != n - 1 && t != 1 )
        {
            t = t * t % n;
            d <<= 1;
        }
        return t == n - 1 || ( d & 1 ) == 1;
    }

    bool isprime ( ll n )
    {
        static const int a[] = {2, 7, 61};
        for ( int i = 0; i < 3; ++i )
        {
            if ( n == a[i] ) return true;
            if ( !Miller_Rabin ( n, a[i], n - 1 ) ) return false;
        }
        return true;
    }
    struct Ans
    {
        int index, val;
    };
    const Ans ansers[] = {{0, 0},{1000, 168},{2000, 303},{3000, 430},{4000, 550},{5000, 669},{6000, 783},{7000, 900},{8000, 1007},{9000, 1117},{10000, 1229},{11000, 1335},{12000, 1438}......};
    const int segment = 1000;
    int main()
    {
        int n, m;
        cin >> n >> m;
        while(n--)
        {
            int l, r;
            cin >> l >> r;
            if (l < 1 or l > m or r < 1 or r > m)
            {
                cout << "Crossing the line" << endl;
                continue;
            }
            if (l > r)
            {
                swap(l, r);
            }
            if (r - l > segment)
            {
                int left = ceil(1.0 * l / segment);
                int right = r / segment;
                int ans = max(ansers[right].val - ansers[left].val, 0);
                for ( int i = l; i <= ansers[left].index; ++i )
                {
                    ans += isprime ( i );
                }

                for ( int i = max(l, ansers[right].index + 1); i <= r; ++i )
                {
                    ans += isprime ( i );
                }
                cout << ans << endl;
            }
            else
            {
                int ans = 0;
                for ( int i = l; i <= r; ++i )
                {
                    ans += isprime ( i );
                }
                cout << ans << endl;	
            }

        }
    }
}





int main()
{
#ifdef LOCAL
    freopen ( "./input.txt", "r", stdin );
#endif
    ios::sync_with_stdio ( false );
    cin.tie ( 0 );
    my::main();
    return 0;
}
```

---

## 作者：Stella_Yan (赞：0)

楼下大佬的代码都好复杂,其实只要先递推出1~n的素数个数,然后再用1~r的素数减去1~l的素数就可以了。

递推式:$f[i]=isprime(i)?f[i-1]+1:f[i-1]$

意思是如果第i个数是素数,1到i之间的素数就+1,加的那一个"1"就是素数i,否则还是不变。

而且用朴素算法判断素数也不会超时 ~~其实是因为本蒟蒻不太会线性筛~~。

具体分析看代码:

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
int n,m;
int f[1000010];//递推数组
bool isp(int x)//判断素数不说了
{
	if(x<=1)
		return false;
	int xx=sqrt(x);
	for(int i=2;i<=xx;i++){
		if(x%i==0){
			return false;
		}
	}
	return true;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){//递推
		if(isp(i)){//如果i是素数
			f[i]=f[i-1]+1;//f[i]=f[i-1]+1
		}
		else{如果不是
			f[i]=f[i-1];//f[i]=f[i-1]
		}
	}
	int l,r;
	for(int i=1;i<=n;i++){
		scanf("%d%d",&l,&r);
		if(r<1 || r>m || l<1 || l>m){//判断越界
			printf("Crossing the line\n");
			continue;
		}
		printf("%d\n",f[r]-f[l-1]);//输出,l要-1是因为l也在l~r的区间里
	}
}
```
[~~无耻地挂一个blog~~](https://jiying.blog.luogu.org/)

---

## 作者：DPair (赞：0)

# 思路

本题可以先考虑使用筛法求出m范围内所有素数，m以外的全部直接结束处理。这样可以节省大量时间，而不是每一次求一个。

# 程序

```cpp
#include <cstdio>
#include <iostream>
#include <cmath>
#define LL long long

using namespace std;
LL n, m, l, r, ans;
bool prime_number[1000010] = {0};//素数统计，true 不是, false是

int main()
{
	scanf("%lld%lld", &n, &m);
    
	prime_number[1] = true;//筛法求素数，求到m为止
	for (LL i = 2;i <= sqrt(m);i ++)
	{
		if(prime_number[i] == false)
		{
			for (LL j = 2;i * j <= m;j ++)
			{
				prime_number[i*j] = true;
			}
		}
	}
	
	for (LL i = 1;i <= n;i ++)//开始处理每一组数据
	{
		ans = 0;//先假设没有素数，清零
		scanf("%lld%lld", &l, &r);//输入数据
		if(r > m || l < 1)//检查有无超出，确保没有RE
		{
			printf("Crossing the line\n");
			continue;//下一组数据
		}
		else
		{
			for (LL j = l;j <= r;j ++)
			{
				if(prime_number[j] == false)//如果是素数
				{
					ans ++;//计数器增加一个
				}
			}
			printf("%lld\n", ans);//输出这组数据答案
		}
	}
}
```

---

## 作者：LJB00125 (赞：0)

首先,筛出1~m中的素数：

```cpp
//数组he为bool型,对于he[i],如果为1,表示i为合数，否则为素数
memset(he,0,sizeof(he)); //初始化
he[0]=he[1]=1; //特判0和1
for(int i=2;i<=m;i++)
    if(!he[i]) //如果没有标记为合数
        for(int j=i*2;j<=m;j+=i) 
        //那么它所有的倍数(不包括自身)都是合数
            he[j]=1; //标记
```
筛完之后,很容易想到这种做法:

```cpp
for(int _i=1;_i<=n;_i++)
{
    scanf("%d %d",&l,&r); //读入
    if(l==0||l<0||(!(r>=1&&r<=m))) //判断越界的情况
    {
        printf("Crossing the line\n");
        continue; //跳出循环
    }
    ans=0; //记录素数的个数
    for(int i=l;i<=r;i++) //遍历l~r
        if(!he[i]) //如果是素数
            ans++; //累加
    printf("%d\n",ans); //输出结果并换行
}
```

但是,#6会TLE！

于是我调试了半天才发现这道题应该**记录前缀和**！


于是,正确的代码应该是这样的……

```cpp
for(int i=1;i<=m;i++) //记录前缀和
{
    qianzhui[i]=qianzhui[i-1]; 
    //令第1~i的前缀和先等于1~(i-1)的前缀和
    if(!he[i]) qianzhui[i]++; //如果第i项也是素数,qianzhui[i]增加1
}

for(int _i=1;_i<=n;_i++)
{
    scanf("%d %d",&l,&r); //读入
    if(l==0||l<0||(!(r>=1&&r<=m)))
    {
        printf("Crossing the line\n");
        continue;
    } //同上
        
    /*ans=0;
    for(int i=l;i<=r;i++)
        if(!he[i])
            ans++;*/
    printf("%d\n",qianzhui[r]-qianzhui[l-1]); 
    //输出前缀和的差(一定要减去qianzhui[l-1]而不是qianzhui[l]!!!)
}
```

---

## 作者：SKTT1Faker (赞：0)

这道题某一看会暴力，但是肯定会超时。

于是，这里就用了俩个很经典的优化方法：前缀和与线性筛书（欧拉筛数）；

前缀和就是把它前面的和加起来，要查询的时候只需（m[r]-m[l-1]);

欧拉筛数运用到了一个原理：如果一个数是质数，那么他的倍数就不是质数。

如（2的k倍=2\*k\*1）有3个因数。

不说了，代码：

 
```cpp
var
  a,b,i,k,x,y:longint;
  m:array[1..1000000] of boolean;      //质数数组
  n:array[0..1000000] of longint;    //前缀和数组
begin
  readln(a,b);
  m[1]:=true;
  for i:=2 to b do    //线性筛质数
  begin
    if m[i]=false then
    begin
      k:=2*i;
      while k<=b do  //把i的倍数全设为合数
      begin
        m[k]:=true;
        k:=k+i;
      end;
    end;
  end;
  for i:=1 to b do
  begin
    n[i]:=n[i-1];
    if m[i]=false then n[i]:=n[i]+1;  // 如果这个数是质数，那么前缀加1
  end;
  for i:=1 to a do
  begin
    readln(x,y);
    if (x<1) or (y>b) then     //判断越界
    begin
      writeln('Crossing the line');
      continue;
    end;
    writeln(n[y]-n[x-1]);
  end;
end.
```
希望大家理解，不要抄袭。
祝大家国庆中秋快乐，多AC不WA


---

## 作者：sanae (赞：0)

本蒟蒻第一次发题解；

刚学习了线性筛，发个简单易懂的题（模）解（版）帮助大家理解，顺便也加强一下自己的理解和记忆（滑稽）；

  
```cpp
#include<cstdio>
#include<cstring>
#include<cstdlib>
#define MAXL 1000001
//MAXL+1避免爆范围 
int prime[MAXL+1];
int t[MAXL+1];
int check[MAXL+1];
int tot=0,n,m,i,j,l,r;
int main()
{
  memset(check,0,sizeof(check));
  memset(t,0,sizeof(t));
  scanf("%d%d",&n,&m);
  for(i=2;i<m;++i)
  {
  //t[i]确认1~i中的质数个数 
      t[i]=t[i-1];
    if(!check[i]) prime[++tot]=i,t[i]++;//    prime数组记录的必然是质数 
    for(j=1;j<=tot;++j)
    {
      if(i*prime[j]>m){break;}//    超出范围就跳出循环 
      check[i*prime[j]]=1;//    check数组标记合数 
      if(i%prime[j]==0){break;}//   当i为合数时，跳出循环，并标记该数的2倍，确保每个合数只被标记一次,避免浪费时间 
    }
  }
  for(i=1;i<=n;i++)
  {
      scanf("%d%d",&l,&r);
      if(l<1||r<1||l>m||r>m) printf("Crossing the line\n");
    else printf("%d\n",t[r]-t[l-1]);//    若l为质数，需保留l 
  }
}
```

---

## 作者：I_AM_HelloWord (赞：0)

请不要不懂装懂，楼下的“dalao”们，你们写的那叫线性筛吗，教坏小朋友！那就是普普通通的埃氏筛法，

虽说效率是O(nloglogn)及其接近与O(n),但是在10^7的数据下还是会TLE.

简单的说说线性筛，

线性筛就是对埃氏筛法的一个优化，主要就是把第二层循环j=2\*i;j<=m;j+=i改成在一个质数表（我们在i之前筛出的）中枚举一个质数，然后乘以i，把这个数筛掉，这样我们就可以保证每个合数都只会被它最小的那个质因子筛掉一次，而不像埃氏筛法重复被筛掉，例如12，只会在2时就被筛掉，不会在3时又被筛一次。

当然，看起来还是两层循环，但是可以证明效率就是O(n)的，神奇吧。证明就有点复杂了，没必要了解。


参考代码：

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=1001000;
int n,m,tot=0;
bool isprime[N];
int prime[N],sum[N];
int main(){
    scanf("%d%d",&n,&m);
    memset(isprime,1,sizeof(isprime));
    isprime[1]=false;
    for (int i=2;i<=m;i++){
        if (isprime[i])prime[++tot]=i;
        for (int j=1;j<=tot && i*prime[j]<=m;j++){
            isprime[i*prime[j]]=false;
            if (i%prime[j]==0)break;
        }
        sum[i]=sum[i-1]+isprime[i];
    }
    for (int i=1;i<=n;i++){
        int l,r;
        scanf("%d%d",&l,&r);
        if (l<1 || l>m || r<1 || r>m)printf("Crossing the line\n");
        else printf("%d\n",sum[r]-sum[l-1]);
    }
    return 0;
}
```

---

## 作者：codesonic (赞：0)

此题初看起来并不复杂，好像一个简单的暴力就能AC（暴力都会TLE），但其实此题考了两个很好用的算法和思想：线性筛素数&前缀和

如果缺少任意一个，都会导致TLE以至于不能AC（有兴趣的可以看看我的记录）

线性筛素数是一种找素数的方法（具体百度），其实就是做一个素数表，要用到就在素数表里面查找，可以做做洛谷3383（模板线性筛素数），不用像常规方法一个一个找，数据大就TLE。

前缀和也是一种防TLE的的思想，具体看下面的代码和注释应该看的懂

总而言之，以上两种方法都是防TLE的重要途径，建议大家学习。

以下是AC代码（附注释）

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
bool flag[1000001];
int sum[1000001];
int main()
{
    memset(flag,0,sizeof(flag));//默认所有数都是素数
    memset(sum,0,sizeof(sum)); //清零
    int n,m,l,r;
    cin>>n>>m;
    for(int i=2;i<=m;i++)//制作素数表
    {
        if(flag[i]==0)//如果flag[i]没有被任何数筛掉过
        {
            for(int j=i*2;j<=m;j+=i)
                flag[j]=1;//将每个i的倍数设为合数 筛掉所有以i为因数的合数 
            sum[i]=sum[i-1]+1;//前缀和的第一部分
        }
        else
            sum[i]=sum[i-1];//前缀和 
```
}//线性筛素数 共11行，简单而快速，时间复杂度也很低
```cpp
    for(int i=1; i<=n; i++)
    {
        scanf("%d %d",&l,&r);
        if(l<1||r>m)
            printf("Crossing the line\n");
        else
            printf("%d\n",sum[r]-sum[l-1]);//前缀和的另一部分（sum[n]指1到n的素数总数）
    }
    return 0;
}
//结束了，另外建议用C++的尽量用scanf和printf，它们比cin和cout都快很多，（我的输入n和m用了cin，是因为没有循环，只有一次，没有多大影响）
```

---

## 作者：piggy (赞：0)

我们可以利用质数线性筛来事先处理好一个“质数个数”前缀和，（线性筛就是素数也用来往后筛，然后适当地break一下，保证每个数只会被“筛”一次）

不过不知为什么跑了这么久……

```cpp
#include <cstdio>
int f[1000005],p[1000005],s[1000005],a,b,n,m,num;

void getp(){
    for (int i=2; i<=m; i++){
        s[i]=s[i-1];
        if (!f[i]) p[++num]=i,s[i]++;
        for (int j=1,o=i<<1,ok=1; ok && j<=num && o<=m; j++,o=p[j]*i) f[o]=1, ok=i%p[j];
    }
}

int main(){
    scanf("%d%d",&n,&m);
    getp();
    while (n--){
        scanf("%d%d",&a,&b);
        if (a>=1 && a<=b && b<=m) printf("%d\n",s[b]-s[a-1]);
        else printf("Crossing the line\n");
    }
}
```

---

## 作者：usqwedf (赞：0)

[Problem 系列题 III]

[A % B Problem]

思路：

题意即为求质数个数。

显然只需要质数筛即可。

统计之时，我们可以设f[i]为1~i的质数个数

那么 若i为质数 f[i]=f[i-1]+1

反之 f[i]=f[i-1]

注意判断是否越界。

时间复杂度 O(m+m+n)

```delphi

var  
  a:array[0..1000000] of boolean;  
  num,n,i,m,j,l,r:longint;  
  prime,f:array[0..1000000] of longint;  
begin  
  readln(n,m);  
  num:=0;   
  for i:=2 to m do begin  
    if a[i]=false then begin   
        num:=num+1;   
        prime[num]:=i;   
    end;  
    for j:=1 to num do begin  
      if prime[j]*i>m then break;  
      a[i*prime[j]]:=true;  
      if i mod prime[j]=0 then break;  
    end;  
  end;   
  for i:=2 to m do  
    if a[i]=false then f[i]:=f[i-1]+1 else f[i]:=f[i-1];  
  for i:=1 to n do begin  
    readln(l,r);  
    if (l<1)or(r>m) then writeln('Crossing the line') else writeln(f[r]-f[l-1]);  
  end;  
end.  

```

---

