# [USACO08FEB] Making the Grade G

## 题目描述

A straight dirt road connects two fields on FJ's farm, but it changes elevation more than FJ would like. His cows do not mind climbing up or down a single slope, but they are not fond of an alternating succession of hills and valleys. FJ would like to add and remove dirt from the road so that it becomes one monotonic slope (either sloping up or down).

You are given N integers A1, ... , AN (1 ≤ N ≤ 2,000) describing the elevation (0 ≤ Ai ≤ 1,000,000,000) at each of N equally-spaced positions along the road, starting at the first field and ending at the other. FJ would like to adjust these elevations to a new sequence B1, . ... , BN that is either nonincreasing or nondecreasing. Since it costs the same amount of money to add or remove dirt at any position along the road, the total cost of modifying the road is

|A1 - B1| + |A2 - B2| + ... + |AN - BN |Please compute the minimum cost of grading his road so it becomes a continuous slope. FJ happily informs you that signed 32-bit integers can certainly be used to compute the answer.

农夫约翰想改造一条路，原来的路的每一段海拔是$A_i$，修理后是 $B_i$，花费 $|A_i - B_i|$。我们要求修好的路是单调不升或者单调不降的。求最小花费。


## 样例 #1

### 输入

```
7
1
3
2
4
5
3
9
```

### 输出

```
3
```

# 题解

## 作者：ButterflyDew (赞：146)

提供一种$nlogn$的神奇做法

先说操作（以单调非降为例）：
从左到右，把当前位置的数放进大根堆，然后比较这个数和堆顶的大小。

若比堆顶大，就不管

若比堆顶小，就把堆顶拿出来变成这个数，然后答案增加堆顶与这个数的差

代码大概是这样
```cpp
for(int i=1;i<=n;i++)
{
    scanf("%d",&a);
    q.push(a);
    if(a<q.top())
    {
        ans+=q.top()-a;
        q.pop();
        q.push(a);
    }
}
```

为什么捏？

假设塞到第$i$了，前面是一个合法的递增序列，堆顶为$y$，当前为$x$且$x<y$

这时候我们花掉了$y-x$块钱进行调整，考虑我们调整可以得到哪些结果

二元组$(x,x),(x+1,x+1),..(y-1,y-1),(y,y)$都是可能的结果，虽然有的结果可能不合法，但一定存在合法的结果

我们尽可能想让当前的数值小，所以我们尽可能会选择小的合法结果

这时候我们发现，如果堆顶在后面被更新了，我们的合法结果的选择集合就变了

如果我们直接把最小的可能不合法的结果放进堆，那么当比它大的元素都被砍掉后（也就是它成了堆顶），它就变得合法了

---

## 作者：nihanchu (赞：30)

这里有一个结论就是修改后的道路高度在原来的那些道路的高度中，出现过（修改后为了节省花费，肯定数字要尽量向那些没修改过的靠近，）

所以我们把所有出现过的道路高度离散化，存在b数组中b[j]表示第j大的高度。

我们用f[i][j]将前i段变作不下降序列，且第j段道路的高度为b[j]时的最小花费，显而易见，

f[i][j]=min(f[i-1][k])+abs(a[i]-b[j])(1<=k<=j）其中a[i]表示第i段路原本的高度。

然而如果枚举k的话，你会发现时间复杂度为n^3。为了解决这个问题，我们发现min(f[i-1][k])是可以在做第i-1段路段的时候处理出来的，（这个还是看代码吧。）所以复杂度就成了n^2。我表示懒得用滚动数组，所以开了二维。。。

处理不上升序列的话和这个差不多。

下面是代码：

```cpp
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cmath>
using namespace std;
int n,m,minf[2009][2009],f[2009][2009],a[2009],b[2009],t[2009],ans;
void ini()
{
  for (int i=0;i<=n;i++)
  for (int j=0;j<=m;j++)
  minf[i][j]=f[i][j]=0;
}
void dp()
{
 for (int i=1;i<=n;i++)
  for (int j=1;j<=m;j++)
  {
    f[i][j]=minf[i-1][j]+abs(a[i]-b[j]);
    if (j!=1) minf[i][j]=min(minf[i][j-1],f[i][j]);
    else minf[i][j]=f[i][j];
  }
}
int main()
{
  scanf("%d",&n);
  for (int i=1;i<=n;i++) 
  {
    scanf("%d",&a[i]);
    t[i]=a[i];
  }
  sort(t+1,t+1+n);
  int now=-1;
  for (int i=1;i<=n;i++) if (now!=t[i]) b[++m]=t[i],now=t[i];
  ini(); dp(); ans=minf[n][m]; 
  for (int i=1;i<=m/2;i++) swap(b[i],b[m-i+1]);
  ini(); dp(); ans=min(ans,minf[n][m]);
  printf("%d\n",ans);
  return 0;
}

```

---

## 作者：傅思维666 (赞：27)

## 题目大意：
给定长度为N的序列A，构造一个长度为N 的序列B。
要求B非严格单调，并最小化花费（Ai-Bi的绝对值）
 
## 题意分析：
马上想到动归。

思路不是特别好想，状态转移方程也不是特别好设。

首先我们需要明确，在满足花费最小化的前提下，一定存在一种构造B的方案，使得B中的每个数都是A序列中的。

可以证明：

假设结论针对于N=K-1成立，那么对于数列N=K，在满足单调性的情况下，可以令Bk=Ak,命题仍成立。

否则的话，令Bk=Bk-1,命题也成立，也就是说可以层层递推下去，一直到N=1的情况。

而显然N=1的情况下命题是成立的。

证毕，命题成立。

我们只是证明这种情况（B中所有元素都是A的一部分）存不存在，并不是在证明只要存在就一定是这种情况。

所以才有了上面的证明过程，证明出这种情况可以存在，为之后的解题过程提供了思路基础。

回到本题。

这道题是构造类型的动态规划。我的思路是，设F[i][j]为完成前i个数的构造，其中Bi=j时，S的最小值。

根据刚刚证明的命题，我们可以考虑把A的数据离散化之后存到B中，离散化的功用是降低时间复杂度，这样一个O（N^3）的算法就会被我们降成O（N^2）。

这样就比较完美了，通过动归求出非严格单调递减之后，仿照这个思路再求一遍非严格单调递增，答案可求。

CODE：
```cpp
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m,ans,a[2001],t[2001],b[2001];
int f[2001][2001],minf[2001][2001];
bool cmp(int a,int b)
{
    return a>b;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        t[i]=a[i];
    }
    sort(t+1,t+n+1);
    int now=-1;
    for(int i=1;i<=n;i++)
        if(now!=t[i])
            b[++m]=t[i],now=t[i];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            f[i][j]=minf[i-1][j]+abs(a[i]-b[j]);
            if(j==1)
                minf[i][j]=f[i][j];
            else
                minf[i][j]=min(minf[i][j-1],f[i][j]);
        }
    ans=minf[n][m];
    memset(f,0,sizeof(f));
    memset(minf,0,sizeof(minf));
    sort(b+1,b+m+1,cmp);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            f[i][j]=minf[i-1][j]+abs(a[i]-b[j]);
            if(j==1)
                minf[i][j]=f[i][j];
            else
                minf[i][j]=min(minf[i][j-1],f[i][j]);
        }
    ans=min(ans,minf[n][m]);
    printf("%d",ans);
    return 0;
}
```
**再次强调一个好的代码习惯多么重要。**

### 看我打了这么久的份上，管理大大能给我过么？

祝大家生活愉快！
——FSW
 

---

## 作者：Utsuji_risshū (赞：21)

给个$n<=2000$长度数列，可以把每个数改为另一个数代价是两数之差的绝对值。求把它改为单调不增or不减序列最小代价。

话说这题其实是一个结论题。。找到结论应该就很好做了呢。

手玩的时候就有感觉，改造出来的数列的元素会不会全是原来数列里有的数？

所以这题结论就上面那个。

------------


补证明。~~其实lyd书上是有的但是不容易懂~~。后来由于thx学长帮助，大概理解了（%%%）。

数学归纳法。

对于$n=1$，显然成立。

对于$n=k-1$时假设其满足由原数列的数构成最优解。那么，考虑对于$n=k$。

当$A_n ≥ B_{n-1}$时（B为之后的数列）显然直接用$A_n$最优。

当$A_n ≤ B_{n-1}$时有两种选择。一种是由上一个$B_{n-1}$继续过来。

一种是把当前$B_i$向下调整。向下调整时，前面的构造好的数列要被迫下调。

那么假设下调至$x$。前面连着的一段应当也调为$x$。

（到这里都是lyd原话）

为什么统一调为$x$，前面构造好的数为什么不会变的比$x$更小从而更优？

如果之前的变得更小就更优的话，那我在之前就应当将它改为更小值保证最优了，而不是现在。

也就是说只能统一改为一个数$x$。

这时候用结论，这一段每个数与$x$差的绝对值要最小化，做多了就知道这是个中位数问题。

那么取这段数中的$mid$一定是可以保证代价最小的。

综上，$B_n$在保证最优的情况下只可能用A数列中有的数。

------------


然后就简单了啊。有个很好想的状态$f[i][j]$第$i$位填数字$j$（因为$j$是只在原数组中出现的，所以可以离散化压缩状态为2000个）。于是每次枚举之，在上一位中找小于当前值的转移过来。

$f[i][j]=min(f[i-1][k]+|A[j]-a[i]|)$       $1<=k<=j$

然后k那一维做个前缀max减一维枚举就n方啦。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
#define dbg(x) cerr<<#x<<" = "<<x<<endl
#define ddbg(x,y) cerr<<#x<<" = "<<x<<"   "<<#y<<" = "<<y<<endl
using namespace std;
typedef long long ll;
template<typename T>inline char MIN(T&A,T B){return A>B?A=B,1:0;}
template<typename T>inline char MAX(T&A,T B){return A<B?A=B,1:0;}
template<typename T>inline T _min(T A,T B){return A<B?A:B;}
template<typename T>inline T _abs(T A){return A<0?-A:A;}
template<typename T>inline T _max(T A,T B){return A>B?A:B;}
template<typename T>inline T read(T&x){
    x=0;int f=0;char c;while(!isdigit(c=getchar()))if(c=='-')f=1;
    while(isdigit(c))x=x*10+(c&15),c=getchar();return f?x=-x:x;
}
const int N=2000+7;
ll f[N][N],ans;
int a[N],A[N],n,m;
inline void dp(){
	for(register int i=1;i<=n;++i){
		ll minx=f[i-1][1];
		for(register int j=1;j<=m;++j)MIN(minx,f[i-1][j]),f[i][j]=minx+_abs(A[j]-a[i]);
	}
}

int main(){//freopen("test.in","r",stdin);//freopen("test.out","w",stdout);
	read(n);
	for(register int i=1;i<=n;++i)A[i]=read(a[i]);
	sort(A+1,A+n+1),m=unique(A+1,A+n+1)-A-1;
	dp();
	ans=f[n][1];
	for(register int i=2;i<=m;++i)MIN(ans,f[n][i]);
	reverse(a+1,a+n+1);
	dp();
	for(register int i=1;i<=m;++i)MIN(ans,f[n][i]);
	printf("%lld\n",ans);
	return 0;
}
```
等一下。。

这题还有对应的拓展。

-     把原序列改为不严格单调增序列，至少改多少数？
    $ans=len-maxlen$（不下降子序列）。原因很简单，保证有一个最长的不降序列，才能保证剩下的修改最少嘛。
-     把原序列改为严格单调增序列，至少改多少数？
     令$B_i=A_i-i$。$ans=len-maxlen$（B的不下降子序列）。这个比较重要。

    首先要考虑的问题是，严格单调递增→若原数列中两数相差超过下标差时，这段数一定要改一些数，否则改掉也“挤不下”。这是问题所在。
    要保证“挤得下”，就必须$A_j-A_i>=j-i $  $(i<j)$。即$A_j-j>=A_i-i$，才有严格递增。
    
    更准确地说，要$A_i<A_{i+1}\Leftrightarrow A_i \leqslant A_{i+1}-1\Leftrightarrow A_i-i\leqslant A_{i+1}-(i+1)\Leftrightarrow B_i\leqslant B_{i+1}$
    
    这是一个$><$号转$≥≤$的重要方法。所以要严格大于，我构造上述序列B，即可将其转化为大于等于。
    
    两者是等价的。
    
    后面那种方法源于[https://blog.csdn.net/guhaiteng/article/details/52549991](https://blog.csdn.net/guhaiteng/article/details/52549991)的大佬的。tql%%%。

    然后[这题](http://acm.hdu.edu.cn/showproblem.php?pid=5256)就可以顺带切掉了。

另外，将一开始问题的要求改为严格递增的最小代价，该怎么求？转化。同理，用上述方法构造序列。由于在原A序列和构造的B序列上修改代价是一样的，所以保证B满足不严格单调并且代价最小也就保证了A的严格单调。

然后相关题目是CF714E。

当然还有一个神仙的log做法。左偏树。我不会。逃。（[要用log的做的题](https://www.lydsy.com/JudgeOnline/problem.php?id=1367)）

---

## 作者：dz_ice (赞：18)

[欢迎来看看呀](https://www.cnblogs.com/dzice/)

[题目链接](https://www.luogu.com.cn/problem/P2893)

这道题代码虽然简单，但是状态转移方程还是比较难想的

首先我们可以贪心地发现一个性质，要使修理完的路花费最小，每条路必然都会是原来已经存在的高度，不然就会造成损失

接下来该怎么处理呢？考虑利用上面的性质来设计一个状态

先将输入的数据离散化一下，$b[i]$表示第$i$高的路的高度，可以用$f[i][j]$表示当第$i$条路的高度为$b[j]$时，修理完前$i$条路所用的最小花费，转移不是很难想

$f[i][j]=min(f[i-1][k])+|a[i]-b[j]|(k\in[1,j))$

其中$min(f[i-1][k])$可以用一个数组记录下来，就可以把$O(n^3)$的复杂度优化到$O(n^2)$

接下来是代码

```
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int n,a[2003],b[2003],mi[2003][2003],f[2003][2003];//mi数组用来记录min(f[i-1][k])
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		b[i]=a[i];
	}
	sort(b+1,b+n+1);//离散化
	for(int i=1;i<=n;i++)
		mi[i][0]=1e9;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
			f[i][j]=mi[i-1][j]+abs(a[i]-b[j]),mi[i][j]=min(mi[i][j-1],f[i][j]);		
	}
	cout<<mi[n][n];
	return 0;
}

```


---

## 作者：Yaha (赞：13)

## DP

首先看数据范围，$n^2$可以过。

单调不降或者单调不升，我们很容易想到DP。

我们想要花费最小，说明尽可能让每个数动的幅度小一点。能不动就不动，如果必须要动的话，变成上一个位置上的数就可以了。这里假设上一个位置的数已经确定。

所以一个数要么是自己，要么是上一个位置上的数。而上一个数怎么来的呢？很明显，也是这样，要么不动，要么是上上个位置的数。可以一直推下去。这就~~口胡~~得出了众题解中的结论了:

#### 存在一种最优方案，每个位置上的数，是原序列中的数。

下面由单增举例：

我们设$f[i][j]$表示第i个位置放j时的方案数，显然，前一个位置放的数必须比j小。

为了转移方便，我们处理一个b数组，为a数组排序后的数，$f[i][j]$表示第i个位置放b[j]时方案数，前一个位置为b[1]~b[j]，这就满足了前一个位置比这个位置小的要求。

于是得出转移方程：

$f[i][j]=(f[i-1][k]+|a[i]-b[j]|)_{min}$，其中k为1~j中的数。

所以我们定义一个$Min[i][j]$表示f[i][1]~f[i][j]中的最小值。

则新的转移方程为：

### $f[i][j]=Min[i-1][j]+|a[i]-b[j]|$

下面只贴单增的代码 （虽然也可以过Q^Q

```cpp
#include<bits/stdc++.h>
using namespace std;
const int amou=2101,Inf=0x3f3f3f3f;
int a[amou],b[amou],n;
int f[amou][amou],Min[amou][amou];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		b[i]=a[i];
	}
	sort(b+1,b+n+1);
	for(int i=1;i<=n;i++)
	{
		Min[i][0]=Inf;
		for(int j=1;j<=n;j++)
		{
			f[i][j]=Min[i-1][j]+abs(a[i]-b[j]);
			Min[i][j]=min(Min[i][j-1],f[i][j]);
		}
	}
	printf("%d",Min[n][n]);
	return 0;
}
```


---

## 作者：薛定谔的鱼 (赞：7)

直入主题。
农夫约翰想改造一条路，原来的路的每一段海拔是Ai，修理后是Bi花费|A_i–B_i|。我们要求修好的路是单调不升或者单调不降的。求最小花费。

数据范围：n<=2000,0≤ Ai ≤ 1,000,000,000

最一开始，就打了一个贪心。

此贪心思路 
很容易发现，如果想要最小值的话，凹下去的土块一定会被填起来，而且填的高度一定会使这个土块和两侧最低的那个相平（比如样例第三个土块，填起来一定会和 二 一样高）于是考虑跑两遍，一个单增，一个单减。

结果：40分

。。。

随手一组hack数据：

9
5 5 5 1 1 1 5 5 5；

我没有及时更新高度，以至于会有后效性。
于是我每次减完会把它更新一次高度。
但是发现，还是会有后效性，hack数据还是毒瘤。

我终于想到了dp~~**（我恨dp）**~~

接下来考虑转移方程式
考虑第i个土块，对其有影响的数据只有前i个土块的高度，还有本土块的高度，所以：
我们用dp[i][j]将前i段变作不下降序列，且第j段道路的高度为j时的最小花费

但是，j的枚举会把时间炸上天！！！！

通过前面的结论，我们发现，最小的填补一定会在目标高度中出现，所以我们开另外一个数组，把高度存到里面，排序，从里面找一个合适的Ai，就省去了遍历1—100000000的时间

继续方程式。写出来就是这样，前i个柱子最小（此为单调不递减）
 
此题，洛谷数据过于划水以至于只考虑单增就可以过了。
 
于是放代码（只放单增的了）

```cpp
#include<bits/stdc++.h>
using namespace std;
const int inf=0x7fffffff;
const int maxn=2010;
int n;
int a[maxn],b[maxn];
int dp[maxn][maxn];
int main()
{
    int ans=inf;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
	scanf("%d",&a[i]),b[i]=a[i];
    sort(b+1,b+1+n);
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(j==1)//因为循环边界，所以当j==1我们要特判一发，把1拍到最低
                dp[i][j]=dp[i-1][j]+abs(a[i]-b[j]);
            else
                dp[i][j]=min(dp[i][j-1],dp[i-1][j]+abs(a[i] - b[j]));//拍土了
            if(i==n)
                ans=min(dp[i][j],ans);
    	}
    }
    printf("%d\n",ans);
    return 0;
}
```


大概就是这样了。，我觉得我自己理解得也不够透彻，说得不对请大家说出来。





---

## 作者：小小二逼兽 (赞：5)

×这是一种$ n^3$的做法
### 状态定义
$f[i]$表示从$1-i$且$ b[i]=a[i]$时的最小花费


### 状态转移

$f[i]=min{f[j]+cost(j+1,i-1)};(0<=j<i)(ai<=aj) $

$cost(j+1,i+1)$表示从$1-i$同时满足$a[j]<=b[j+1]<=……<=b[j-1]$时，$j+1$到$i-1$的花费的最小值
### 思路

由引理可知$b[i]$由$a[i]$中的一段段数构成。
把$b$的区间$[j+1,k]$中的数变为$a[j]$，后面的$[k+1，i-1]$中的数变为$a[i]$
的最小花费

不需要考虑其中$b[k]$中的一部分数会变成$a[k]$，因为该情况在$j=k$时已经被考虑到。

（以上垃圾缩写《算法竞赛进阶指南》）

但……$f[n]$并不是答案，因为最后的数$b[n]$可能不等于$a[n]$，所以要对答案进行一下微妙的处理，其实就是把$b[i+1]$一直到$b[n]$全都赋成$a[i]$就好，然后统计下答案。
```

#include<bits/stdc++.h>
using namespace std;
long long a[2001];
long long f[2001];
	long long ans=LLONG_MAX;
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		f[i]=LLONG_MAX;
	}
	f[0]=0;
	for(int i=1;i<=n;i++)
	{   
		
		for(int j=0;j<=i-1;j++)
		{   
			if(a[i]<a[j])
				continue;	
			long long cost=0;
			long long res=LLONG_MAX;
			for(int k=j+1;k<=i-1;k++)cost+=abs(a[k]-a[i]);
			
			res=min(res,cost);
			for(int k=j+1;k<=i-1;k++){
				cost=cost-abs(a[k]-a[i])+abs(a[j]-a[k]);
				res=min(res,cost);
			}
			f[i]=min(f[i],f[j]+res);
		}
	}

	for(int i=1;i<=n;i++)
	{
		long long res=f[i];
		for(int j=i+1;j<=n;j++)
		{
			res+=abs(a[i]-a[j]);
		}
		ans=min(ans,res);
	}
	printf("%lld\n",ans);
	
	return 0;
}
```
其实我写这个的原因是在网上找不到这种写法的代码


此非正解（仅供娱乐）90‘


---

## 作者：LazySheep (赞：4)

- #### 引理

>在满足答案最小化的前提下，一定存在一种构造新序列的方案，使得新序列中的值全都在原序列中出现过。

证明略。

以上摘自《算阶》。

------------

 - #### 方程

为了方便起见，只考虑不下降的情况

设f[ i,j ]为**修改到第i段路，且修改后高度为 j 的最优值**

根据引理得，j 一定在原序列中出现过，所以可**将 j 离散化**

f[ i,j ]的意义变为**修改到第 i 段路，且修改后高度为第 j 段路高度的最优值**

由此可得:

#### **f[ i,j ]=min(f[ i-1,k ]+$\mid$a[ i ]-a[ j ]$\mid$)，k$\in$[ 1,n ]$\bigcap$a[ k ]<=a[ j ]**，a代表原序列值

------------

#### CODE
```cpp
for(int i=1;i<=n;++i)
	for(int j=1;j<=n;++j)
		for(int k=1;k<=n;++k)
			if(a[k]<=a[j])
				f[i][j]=min(f[i][j],f[i-1][k]+abs(a[i]-a[j]));
```

时间复杂度O(N^3)，无法承受

------------

- #### 优化

声明：本人语文很糟，下述优化讲得不是很好。如果想清楚了解，可以私信。

根据DP方程的定义，很容易看出，i 和 j 的循环是不可省的。

所以优化从 k 入手。

观察这句话。

```cpp
for(int k=1;k<=n;++k)
	if(a[k]<=a[j])
		f[i][j]=min(f[i][j],f[i-1][k]+abs(a[i]-a[j]));
```

我们很容易看出，在找满足 a[ k ]<a[ j ] 的 k，检查能否更新时花费了大量时间。

这启发我们在O(1)的时间内实现转移。

可以这样做：**新建一个结构体 b，存 a 的值和对应的下标，以值为关键字从小到大排序**。

排完序后，用一个数组 tong，执行以下操作：

```cpp
for(int i=1;i<=n;++i)
	tong[b[i].id]=i;
```

这样，tong[ j ] 就代表**原始序列中的第 j 个元素**在**排序后序列元素的下标**。

新建一个q数组，设 **q[ j ] 代表排序后序列中，第 j 小DP值**。

这样，就可以用 q[ tong[ j ] ] 以O(1)复杂度访问到 f[ i-1,k ] 中满足条件的最小值

每轮转移结束后，更新 q[ ] 中的DP值

问题又来了。该如何更新呢？

回顾定义，f[ i,j ] 中 j 的定义为修改后高度为第j段路高度的最优值，而 q[ j ] 的定义为排序后序列中，第 j 小DP值。

也就是说，**q[ tong[ j ] ]=f[ i,j ]**（i是一轮DP结束后未自加的i）。

因为要求的序列满足单调不下降，所以比这次修改后土坡高的上一修改后土坡都能参与转移，我们只需保留DP值最小的。

换言之，**q[ ]是单调递减的**，可以在 q[ tong[ j ] ]=f[ i,j ] 赋值完后，再遍历一次更新最值。

```cpp
int tmp=2139062143;//tmp初始为一个极大值
	for(int j=1;j<=n;++j)
		if(q[j]>=tmp)
			q[j]=tmp;
		else tmp=q[j];
```

最开始q[ ]初值均赋0，因为没有进行DP。

时间复杂度O(N^2)，可以接受 ~~（虽然常数很大）~~

------------

#### CODE

```cpp
#include<bits/stdc++.h>
using namespace std;
const int INF=2139062143;
const int N=3000;
struct kkk{
	int id,x;
}b[N];
int f[N][N],a[N];
int tong[N],q[N];
int n,ans=INF;
bool cmp(kkk x,kkk y){
	return x.x==y.x?x.id<y.id:x.x<y.x;
}
bool cop(kkk x,kkk y){
	return x.x==y.x?x.id<y.id:x.x>y.x;
}
int main(){
	scanf("%d",&n);
	memset(f,127,sizeof(f));
	for(int i=0;i<=n;++i)
		f[0][i]=0;
	for(int i=1;i<=n;++i){
		scanf("%d",&a[i]);
		b[i].id=i;b[i].x=a[i];
	}
	sort(b+1,b+1+n,cmp);
	for(int i=1;i<=n;++i)
		tong[b[i].id]=i;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j)
			f[i][j]=min(f[i][j],q[tong[j]]+abs(a[i]-a[j]));
		for(int j=1;j<=n;++j)
			q[tong[j]]=f[i][j];
		int tmp=2139062143;
		for(int j=1;j<=n;++j)
			if(q[j]>=tmp)
				q[j]=tmp;
			else tmp=q[j];
	}
	for(int i=1;i<=n;++i)
		ans=min(f[n][i],ans);
	memset(q,0,sizeof(q));
	memset(f,127,sizeof(f));
	for(int i=0;i<=n;++i)
		f[0][i]=0;
	sort(b+1,b+1+n,cop);
	for(int i=1;i<=n;++i)
		tong[b[i].id]=i;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j)
			f[i][j]=min(f[i][j],q[tong[j]]+abs(a[i]-a[j]));
		for(int j=1;j<=n;++j)
			q[tong[j]]=f[i][j];
		int tmp=2139062143;
		for(int j=1;j<=n;++j)
			if(q[j]>=tmp)
				q[j]=tmp;
			else tmp=q[j];
	}
	for(int i=1;i<=n;++i)
		ans=min(ans,f[n][i]);
	printf("%d",ans);
	return 0;
}
```

------------

最后，附上[某位大佬](https://www.luogu.com.cn/user/187259)的O(NlogN)贪心26行代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[2001],f[2001][2001];
int ans1,ans2; 
priority_queue<int,vector<int>,greater<int> >q;
priority_queue<int,vector<int>,less<int> >w;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){ 
		scanf("%d",&a[i]);
		q.push(a[i]);
		if(a[i]>q.top()){
			ans1+=a[i]-q.top();
			q.pop(); q.push(a[i]);
		}
	}
	for(int i=1;i<=n;i++){
		w.push(a[i]);
		if(a[i]<w.top()){
			ans2+=w.top()-a[i];
			w.pop(); w.push(a[i]);
		}
	}
	printf("%d",min(ans1,ans2));
	return 0;
}
```
~~所以用DP做的都是猪脑子。~~

---

## 作者：_CHO (赞：3)

~~其实这边题解的思路和楼上基本差不多~~

~~但是看到还可以提交~~

~~那怎么能不交呢~~

**~~并且hack掉了楼上某一篇题解中的hack~~**

希望能为大家带来一些新的思考



------------


首先这道题数据比较水，只需要考虑单调不降的情况即可但事实上单调不增和单调不降其实是一样的，只需要改变一下递推顺序即可。

首先考虑贪心，我们考虑把每一个路的海拔提升至上一个路海拔。例如
```
9
5 5 5 1 1 1 5 5 5
```
则只需要将中间的三个1升高到5，总花费为12

但是，这种做法是非常好卡掉的，看下面这组数据

```
5
1000000000 0 0 0 1000000000
```
如果按照上面的贪心思想答案应为$3000000000$（不用数了有$9$个铃）。很显然，这是错误的，我们只需要将第一个路由10^9降为0即满足题意，总花费为$10^9$。

> 贪心解决不了的问题，一般是动态规划。——rxz

那么我们来考虑动态规划，容易想到状态$f[i][j]$表示

我们看到j的范围高达$10^9$,而总共只有不多余$2000$个数，所以考虑离散化，把路高从小到大排序，存在$b[]$中。修改一下状态。 $f[i][j]$ 表示处理到第$i$个路，第i个路高为$b[j]$时的最小花费。

接下来考虑转移，很显然的是

$f[i][j] = min([i-1][k]) + abs(a[i]-b[j]),0<k<j+1$

这样复杂度为O(n^3)，不能接受。下面考虑优化。

我们发现，每一次我们都花费了$O(n)$ 来寻找$min([i-1][k])$，那么我们能否在处理第i-1个路的时候就顺便将其算出来呢？显然是可以的。具体参见代码

则答案应为 $min(f[n][k])$

最后注意边界条件与数组初始化就可以了

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 2010;
int n;
int a[maxn],b[maxn];
int f[maxn][maxn],mn[maxn][maxn];
int main(){
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>a[i];
		b[i]=a[i];
	}
	sort(b+1,b+n+1);
	memset(mn,0x7f,sizeof(mn));
	memset(mn[0],0,sizeof(mn[0]));
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			f[i][j] = mn[i-1][j] + abs(a[i]-b[j]);
			mn[i][j] = min(mn[i][j-1],f[i][j]);
		}
	}
	for(int i=2;i<=n;++i) f[n][i]=min(f[n][i],f[n][i-1]);
	printf("%d",f[n][n]);
	return 0;
}
```

---

## 作者：SUNCHAOYI (赞：2)

**首先设f[i][j]表示长为i，高为j的不下降/不上升的序列长度  那么状态转移f[i][j] = q[i - 1][j] + abs(a[i] - c[j]); q数组是记录最优解的，同时q数组也要更新**
```
if(j != 1) q[i][j] = min(f[i][j],q[i][j - 1]);
else q[i][j] = f[i][j];
```

**先把数据输入后排序，然后进行dp后再变为降序进行dp**

**两次的答案取最小值即可**

------------

**代码：**

```
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;
const int MAX = 2010;
int a[MAX],b[MAX],c[MAX],f[MAX][MAX],k = -1,m = 0,n,q[MAX][MAX],ans = 0x3f3f3f3f;
void ready();
void work();
int main()
{
    cin>>n;
    for(int i = 1;i <= n;i++)
    {
        cin>>a[i];
        b[i] = a[i];
    }
    sort(b + 1,b + n + 1);//排成上升序列
    for(int i = 1;i <= n;i++)//有无重复
        if (k != b[i]){c[++m] = b[i],k = b[i];}
    //上升下降各找一遍取min
    ready();work();ans = q[n][m];
    for(int i = 1;i <= m / 2;i++) swap(c[i],c[m - i + 1]);//交换后成下降序列
    ready();work();ans = min(ans,q[n][m]);
    cout<<ans<<endl;
    return 0;
}
void ready()//初始化
{
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= m;j++) f[i][j] = q[i][j] = 0;
}
void work()
{
    //q记录最小的，最优解；f用来转移
    for(int i = 1;i <= n;i++)
    {
        for(int j = 1;j <= m;j++)
        {
            f[i][j] = q[i - 1][j] + abs(a[i] - c[j]);
            if(j != 1) q[i][j] = min(f[i][j],q[i][j - 1]);
            else q[i][j] = f[i][j];
        }
    }
}

```


---

## 作者：Patrickpwq (赞：2)

萌新冒泡

这道题是一道较难的dp综合运用题

在手玩几组数据后 我们会发现一个数要么不改 要么改成原序列中某个数的值

（以下我们只讨论不下降序列）

比如100 250 130 如果要修改250 那肯定修改成130是最优的 而不是110 120等等

那我们或许可以尝试枚举当前数修改成的值？但由于 Ai ≤ 1,000,000,000，我们最好先离散化再来

那设f[i][j]表示第i个数修改成j(j是离散后的值)所需要的最小花费

则 f[i][j]=min{f[i-1][k]+abs(a[i]-b[j]) } (1<=k<=j b是排过序的数组)

然后这样好像是n^3的 考虑优化 我这里采用了类似单调队列的方式 边枚举j边更新
```cpp
//n^2
#include<bits/stdc++.h>
const int N=2005;
const int INF=0x3f3f3f3f;
using namespace std;
int n,m,a[N],b[N],dp[N][N],ans,q[N],tail;
int minx=INF;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)	cin>>a[i],b[i]=a[i];
	sort(b+1,b+n+1);
	for(int i=1;i<=n;i++)
	{
		tail=0;
		for(int j=1;j<=n;j++)
		{
			while(tail&&dp[i-1][j]<dp[i-1][q[tail]])	tail--;
			q[++tail]=j;
			dp[i][j]=dp[i-1][q[1]]+abs(a[i]-b[j]); 
		}
	}
	ans=INF;
	for(int i=1;i<=n;i++)	ans=min(ans,dp[n][i]);
	memset(dp,0,sizeof(dp));
	for(int i=1;i<=n;i++)
	{
		tail=0;
		for(int j=n;j>=1;j--)    //倒序枚举保证k∈[j,n]
		{
			while(tail&&dp[i-1][j]<dp[i-1][q[tail]])	tail--;
			q[++tail]=j;	
			dp[i][j]=dp[i-1][q[1]]+abs(a[i]-b[j]);
		}
	}	
	for(int i=1;i<=n;i++)	ans=min(ans,dp[n][i]);
	cout<<ans<<endl;
	return 0;
}

```

---

## 作者：D2T1 (赞：0)

[$\color{blue}{\text {pwp }~{\to\textbf{My blog}\gets}}~\text{qwq}$](https://www.luogu.com.cn/blog/390770/blogcenter)

## 题解 P2893

一道 DP。

### 1.状态

影响决策的两个因素只有**已完成构造数个数**和**上一个元素**，所以我们设 $f(i,j)$ 表示已经完成前 $i$ 个数的构造，构造出的 $B$ 数组的第 $i$ 位为 $j$ 时的最小花费。

$j$ 的范围是 $1e9$ 太大了怎么办？离散化即可。

### 2.转移方程

可以把题目分为**构造单调不升序列**和**构造单调不降序列**两部分，最终答案取最小值即可，现在先考虑**构造单调不降序列**。

可以想到一个方程：$f(i,j)=\min\limits_{0 \leq k \leq j}\{f(i-1,k)+|A_i-j|\}$。

但是这样的话复杂度是 $O(n^3)$ 的，显然会 TLE，所以我们使用 传 统 艺 能：可以发现在枚举 $j$ 时 $i$ 的值是不变的，所以我们可以完全不用枚举 $k$，在枚举 $j$ 的时候顺便存储 $f(i-1,k)$ 的最小值即可。具体可以看代码。 

而单调不升序列怎么构造？可以把原序列翻转过来构造单调不降序列即可。

## 代码

```cpp
//P2893
#include <bits/stdc++.h>
using namespace std;

const int N=2010;
int n,m,a[N],dct[N],dp[N][N],ans=0x3f3f3f3f;

int main(){
	cin>>n;
	for(int i=1; i<=n; ++i) cin>>a[i], dct[i]=a[i];
	sort(dct+1,dct+n+1), m=unique(dct+1,dct+n+1)-(dct+1); //离散化
	memset(dp,0x3f,sizeof(dp)), dp[0][0]=0; //dp 数组初始化，因为求最小值所以全部初始为 inf，边界就是 dp[0][0]=0
	for(int i=1; i<=n; ++i){
		int t=dp[i-1][0];//记录 dp[i-1][k] 的最小值，进行转移
		for(int j=1; j<=m; ++j){
			t=min(t,dp[i-1][j]);// 更新最小值
			dp[i][j]=t+abs(a[i]-dct[j]);//转移
		}
	}
	for(int i=1; i<=m; ++i) ans=min(ans,dp[n][i]);//取答案
	reverse(a+1,a+n+1); //翻转序列，以下步骤同上
	memset(dp,0x3f,sizeof(dp)), dp[0][0]=0;
	for(int i=1; i<=n; ++i){
		int t=dp[i-1][0];
		for(int j=1; j<=m; ++j){
			t=min(t,dp[i-1][j]);
			dp[i][j]=t+abs(a[i]-dct[j]);
		}
	}
	for(int i=1; i<=m; ++i) ans=min(ans,dp[n][i]);
	cout<<ans<<'\n';
	return 0;
}
```


---

## 作者：一只书虫仔 (赞：0)

#### Description

> 给定一个长为 $n$ 的序列 $a_i$，把一个数从 $p$ 修改为 $q$ 需要用 $|p-q|$ 的代价，求将其修改为一个不下降或不上升序列的最小代价。

#### Solution

我们先用不下降序列讲。

比如说对于这三个数：$3\ 2\ 5$，将其修改为满足要求的序列，很明显要改变 $2$ 的值，然而要求变动最小，所以要让其改变为 $3$，即等于前面那一个数。如果中间的数是 $6$，将其改变为 $5$，即等于后面那一个数。不难发现，改为原序列中的一个数代价会最小。

因此，先将序列进行离散化，假设离散化后有 $w$ 个数 $c_i$。

考虑 dp，定义 $dp_{i,j}$ 为将序列的第 $i$ 个数改为 $c_j$ 使得 $a_{[1,i]}$ 为满足要求的序列需要的最少代价，很显然，对于所有 $k \in [1,j]$，对 $dp_{i-1,k}$ 取个 $\min$ 并加上 $|a_i-c_j|$ 即可，答案即为 $\min\limits_{i=1}^n dp_{i,j}$，形式化的转移方程：

$$dp_{i,j}=\min\limits_{k=1}^j dp_{i-1,k}+|a_i-c_j|$$

直接枚举 $k$ 是 $\mathcal O(n^3)$ 的，我们对于区间 $\min$，可以使用单调队列！！！（大雾）不知道是不是可以使用单调队列，但是太麻烦了，既然这个 $\min$ 与 $i$ 及以后的都没有关系，不如直接在算 $i-1$ 的时候就将其预处理。

对于不上升序列，如果您是个懒人，可以将 $c_i$ 序列颠倒一下，然后把 dp 过程粘贴下来就行了（

#### Code

```cpp
#include <bits/stdc++.h>

using namespace std;

int a[2005];
int dp1[2005][2005];
int dp2[2005][2005];
int b[2005];
int p[2005];

int main () {
	int n, cnt = 0, now = -1;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++) p[i] = a[i];
	sort(p + 1, p + n + 1);
	for (int i = 1; i <= n; i++)
		if (now != p[i]) {
			b[++cnt] = p[i];
			now = b[cnt];
		}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= cnt; j++) {
			dp1[i][j] = dp2[i - 1][j] + abs(a[i] - b[j]);
			if (j == 1) dp2[i][j] = dp1[i][j];
			else dp2[i][j] = min(dp2[i][j - 1], dp1[i][j]);
		}
	int ans = dp2[n][cnt];
	reverse(b + 1, b + cnt + 1);
	memset(dp1, 0, sizeof(dp1));
	memset(dp2, 0, sizeof(dp2));
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= cnt; j++) {
			dp1[i][j] = dp2[i - 1][j] + abs(a[i] - b[j]);
			if (j == 1) dp2[i][j] = dp1[i][j];
			else dp2[i][j] = min(dp2[i][j - 1], dp1[i][j]);
		}
	ans = min(ans, dp2[n][cnt]);
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：Martian148 (赞：0)

# Link
[P2893 [USACO08FEB]Making the Grade G](https://www.luogu.com.cn/problem/P2893)

# Solve
这道题实际上是有$O(nlogn)$的做法的，但是$DP$的做法还是能带来很多思考的

因为数据很大，所以我们不能直接拿数值$DP$考虑用下标$DP$

这里我们有一个结论：

>  满足答案最小化的前提下，一定存在一种构造序列$B$的方案，使得$B$中的数值都在$A$中出现过。

证明：

数学归纳法。命题$N=1$显然成立

设结论对$N=k-1$成立，此时构造出的序列为$B_1$~$B_{k-1}$

当$N=k$时，若$B_{k-1}≤A_k$，则令$B_k=A_k$满足单调性且命题成立。

否则，要么令$B_k=B_{k-1}$，命题仍成立，要么存在一个$j$,令$B_j$，$B_{j+1},...,B_k$为同一个值$v$，设$A_j,A_{j+1},...,A_k$的中位数是$mid$，若$mid≥B_{j-1}$则有$v=mid$，否则有$v=B_{j-1}$。无论哪种情况，$B_1$~$B_k$中的数都在$A$中出现过。

证毕.

有了这个结论，就很简单了

我们定义$F[i][j]$表示前$i$个数，第$i$个数是$b[j]$的最优解，($b$是排序后的$a$，懒得离散了)

显然转移方程就比较简单了

$F[i][j]=min(F[i][k])+abs(a[i]-b[j]),(0<k<j)$

但是这个转移方程直接推是$O(n^3)$的，不够优秀

我们发现$min(F[i][k]$每次都去找$k<j$的最小值，所以可以用一个数组$Min[i][j]$提前记一下$F[i][1-j]$的最小值,每次转移的时候把$Min[i-1][j]$当做$min(F[i][j])$就好了，最后更新$Min[i][j]$

这种维护前面某个状态的最小值来降低维度的方法是可以转移的，如果前面某个量是线性增长的，就可以用记一下前面的最优答案方便转移。

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2005;
int N,ans=1<<30,a[maxn],b[maxn],F[maxn][maxn],Min[maxn][maxn];
inline int read(){
	int ret=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();}
	while(ch<='9'&&ch>='0')ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
int main(){
	freopen("P2893.in","r",stdin);
	freopen("P2893.out","w",stdout);
	N=read();
	for(int i=1;i<=N;i++)a[i]=read(),b[i]=a[i];
	sort(b+1,b+1+N);
	memset(Min,63,sizeof Min);
	memset(Min[0],0,sizeof Min[0]);
	for(int i=1;i<=N;i++)
		for(int j=1;j<=N;j++){
			F[i][j]=Min[i-1][j]+abs(a[i]-b[j]);
			Min[i][j]=min(F[i][j],Min[i][j-1]);
		}
	for(int i=1;i<=N;i++)ans=min(ans,F[N][i]);
	
	for(int i=1;i<=N/2;i++)swap(b[i],b[N-i+1]);
	memset(F,0,sizeof F);
	memset(Min,63,sizeof Min);
	memset(Min[0],0,sizeof Min[0]);
	for(int i=1;i<=N;i++)
		for(int j=1;j<=N;j++){
			F[i][j]=Min[i-1][j]+abs(a[i]-b[j]);
			Min[i][j]=min(F[i][j],Min[i][j-1]);
		}
	for(int i=1;i<=N;i++)ans=min(ans,F[N][i]);
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：MikukuOvO (赞：0)

### 题目大意

农夫约翰想改造一条路，原来的路的每一段海拔是Ai，修理后是Bi，花费|Ai – Bi|，我们要求修好的路是单调不升或者单调不降的，求最小花费。

### 题目分析

首先有一个比较显然的结论：b序列里的数全部都在a序列里出现过，我们可以这么理解：如果要使得花费尽可能的小，那么我们要使得修改后的序列和原序列差的尽可能小。

那么我们先将原序列排序去重，紧接着枚举得到的序列就可以了。

动态转移方程就是：f[i][j]=min(f[i-1][k])+abs(a[i]-b[j]) 其中a是原序列，b是得到的序列

这个方程有一个特点就是f[i][j]由f[i-1][k]的最小值得到，那么我们再维护一个minf[i][j]记录上一维最小值就可以优化一下了

### 性能分析

经典的dp枚举，复杂度n^2

### 代码实现

```cpp
//Head File _DAG_
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<deque>
#include<queue>
#include<stack>
#include<vector>
using namespace std;

//Debuger _DAG_
#define dej printf("Running\n");
#define dep1(x) cout<<#x<<"="<<x<<endl;
#define dep2(x,y) cout<<#x<<"="<<x<<' '<<#y<<"="<<y<<endl;
#define dep3(x,y,z) cout<<#x<<"="<<x<<' '<<#y<<"="<<y<<' '<<#z<<"="<<z<<endl;

//Replace _DAG_
#define LL long long
#define LB long double
#define reg register
#define il inline
#define inf 2147483644

//DTL _DAG_
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
#define abv(a) (((a)>(0))?(a):(-(a)))
#define UF(i,a,b) for(reg int i=a;i<=b;i++)
#define DF(i,a,b) for(reg int i=a;i>=b;i--)
#define SUF(c,a,b) for(reg int *S=c+a,*E=c+b+1;*S!=*E;*S++)
#define SDF(c,a,b) for(reg int *S=c+a,*E=c+b-1;*S!=*E;*S--)

//Sorce Limit _DAG_
#define maxn 2005
#define maxm 70005

int n,last=-1,cnt,ans1,ans;
int t[maxn],b[maxn],c[maxn];
int f[maxn][maxn],minf[maxn][maxn];

il bool cmp(int x,int y)
{
  return x<y;
}
int main()
{
    scanf("%d",&n);
    UF(i,1,n) scanf("%d",&c[i]),t[i]=c[i];
    sort(t+1,t+n+1,cmp);
    UF(i,1,n) if(last!=t[i]) b[++cnt]=t[i],last=t[i];
    UF(i,1,n)
    {
      UF(j,1,cnt)
      {
        f[i][j]=minf[i-1][j]+abv(c[i]-b[j]);
        if(j!=1) minf[i][j]=min(f[i][j],minf[i][j-1]);
        else minf[i][j]=f[i][j];
      }
    }
    ans=minf[n][cnt];
    UF(i,1,cnt/2) swap(b[i],b[cnt-i+1]);
    memset(f,0,sizeof(f)),memset(minf,0,sizeof(minf));
    UF(i,1,n)
    {
      UF(j,1,cnt)
      {
        f[i][j]=minf[i-1][j]+abv(c[i]-b[j]);
        if(j!=1) minf[i][j]=min(f[i][j],minf[i][j-1]);
        else minf[i][j]=f[i][j];
      }
    }
    ans=min(minf[n][cnt],ans);
    printf("%d\n",ans);
    return 0;
}


---

