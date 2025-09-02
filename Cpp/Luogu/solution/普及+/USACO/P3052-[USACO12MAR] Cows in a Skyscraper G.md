# [USACO12MAR] Cows in a Skyscraper G

## 题目描述

A little known fact about Bessie and friends is that they love stair climbing races.  A better known fact is that cows really don't like going down stairs.  So after the cows finish racing to the top of their favorite skyscraper, they had a problem.  Refusing to climb back down using the stairs, the cows are forced to use the elevator in order to get back to the ground floor.

The elevator has a maximum weight capacity of W (1 <= W <= 100,000,000) pounds and cow i weighs C\_i (1 <= C\_i <= W) pounds.  Please help Bessie figure out how to get all the N (1 <= N <= 18) of the cows to the ground floor using the least number of elevator rides.  The sum of the weights of the cows on each elevator ride must be no larger than W.


## 说明/提示

There are four cows weighing 5, 6, 3, and 7 pounds.  The elevator has a maximum weight capacity of 10 pounds.


We can put the cow weighing 3 on the same elevator as any other cow but the other three cows are too heavy to be combined.  For the solution above, elevator ride 1 involves cow #1 and #3, elevator ride 2 involves cow #2, and elevator ride 3 involves cow #4.  Several other solutions are possible for this input.


## 样例 #1

### 输入

```
4 10 
5 
6 
3 
7 
```

### 输出

```
3 ```

# 题解

## 作者：mzq667 (赞：43)

此题一般思路为迭代加深。关键是枚举车厢数，再dfs奶牛号，每次递归遍历车厢号，看奶牛能进哪个车厢，就把它放进去，然后继续dfs（千万不要枚举奶牛号，然后往车厢里塞奶牛）。还有剪枝，可证第i奶牛放到i后车厢没有意义。即可得出答案。

代码：

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
int n, m, c[19], tot(0), ans(0), v[19];
bool dfs(int x, int num){//x为奶牛号， num为车厢数
    for (int i = 1; i <= x && i <= num; ++i)//for车厢号，看奶牛能被放进哪个车厢
        if(v[i] + c[x] <= m){
            v[i] += c[x];
            if(x == n) return 1;
            if(dfs(x+1, num)) return 1;
            v[i] -= c[x];
        }
    return 0;
}
int main(){
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%d", &c[i]);
    for (int i = 1; i <= n; ++i){//枚举车厢数
        fill(v+1, v+n+1, 0);//当然也可以memset
        if (dfs(1, i)){
            printf("%d\n", i);
            break;
        }
    }
    return 0;
}
```

---

## 作者：shadowice1984 (赞：43)

状态压缩动态规划

这道题是不能使用普通的线性dp的

因为每一头牛只能够用一次，这样会出现后效性

但是枚举全排列的n!做法又是承受不住n=18的数据范围

因此我们使用一个二进数j表示那些奶牛被选过。

令d[i][j]表示已经开了i架电梯，j是二进制数，第k位为1表示这个位置的奶牛被选过。

d[i][j]的值表示当前电梯里的重量。

那么如果存在d[i][j]这种方案，我们枚举k不属于j

那么就可以转移到d[i][j&(1<<k)]或者d[i+1][j&（1<<k)]

然后从前往后扫，扫到第一个存在j=2^n-1的方案即可

```cpp
#include<stdio.h>
#include<cmath>
#include<algorithm>
using namespace std;
int d[20][300000];
int n;int w[20];
int m;int up;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++)
    {
        scanf("%d",&w[i]);
    }
    up=pow(2,n);//定义上界
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<=up-1;j++)
        {
            d[i][j]=0x3f3f3f3f;//初始化为∞
        }
    }
    for(int i=0;i<n;i++)
    {
        d[1][1<<i]=w[i];//边界条件，第一架电梯放那一头牛
    }
    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=up-1;j++)//存在性dp
        {
            if(d[i][j]!=0x3f3f3f3f)//如果存在
            {
                //printf("d[%d][%d]=%d\n",i,j,d[i][j]);
                for(int k=0;k<n;k++)//枚举k
                {
                    if((j&(1<<k))!=0)continue;//如果属于jcontinue掉
                    if(d[i][j]+w[k]<=m)
                    {
                        d[i][j|(1<<k)]=min(d[i][j|(1<<k)],d[i][j]+w[k]);
                        //printf("d[%d][%d]->d[%d][%d]=%d\n",i,j,i,j|(1<<k),d[i][j|(1<<k)]);
                    }
                    else
                    {
                        d[i+1][j|(1<<k)]=min(d[i][j|(1<<k)],w[k]);
                        //printf("d[%d][%d]->d[%d][%d]=%d\n",i,j,i+1,j|(1<<k),d[i][j|(1<<k)]);
                    }
                }
            }
        }
    }
    for(int i=0;i<=n;i++)
    {
        if(d[i][up-1]!=0x3f3f3f3f)//从后往前走
        {
            printf("%d",i);break;
        }
    }
    return 0;
}
```

---

## 作者：哥你挺6啊 (赞：30)

这是一篇裸搜的题解（）

这题状压的方法很好，但是比较难想（可能是我太菜了）。像迭代加深搜索、模拟退火这种东西也只有dalao才能想出来（还是我太菜了）。

下面讲讲裸搜的方法，我们先把题意简化，n个物品装进一些体积为m的箱子中，问最少需要几个箱子。在搜索的过程中，我们枚举物品x可以放入的箱子。详见代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,c[19],tot,ans=1e9,b[19];
//b数组用来记录第i个箱子的剩余容量
void dfs(int x,int cnt)
{
	if(x==n+1){
		ans=min(ans,cnt);
		return;
	}
	if(cnt>=ans)return;//剪枝1（这个不用解释）
	for(int i=1;i<=x-tot;i++)
    //枚举箱子，看看物品x能放入那一个箱子
    //由于不可能有体积大于容量的物品，所以第x个物品顶多会用到第x个箱子，假如说原本每个物品都独占一个箱子，tot是用来记录有多少挤到已经有物品的箱子里的物品个数，因为有的物品和别的物品共用一个箱子，这必然会腾出该物品原来占有的箱子，所以只需枚举到x-tot个箱子就可以了。比如说2,3,4号物品共同占用2号箱子，那5号物品顶多会用到3号箱子，所以只需枚举到3.
	{
		if(b[i]<c[x])continue;
		if(b[i]==m)cnt++;
		else tot++;
		b[i]-=c[x];
		dfs(x+1,cnt);
		b[i]+=c[x];
		if(b[i]==m)cnt--;
		else tot--;
	}
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>c[i],b[i]=m;
    //把箱子剩余容量初始化为m
		dfs(1,0);
	cout<<ans;
}
```

最后，118ms过了这道题，相比状压啥的都要快。。

本蒟蒻一时脑热发了篇题解，还请大佬们多多关照Orz

---

## 作者：niiick (赞：26)


~~我来传播**退火邪教**啦~~

如果假设需要分组的物品**必须连续**，那么一个$n^2$的dp很容易想到

$dp[i]$表示**将前**$i$**个物品分组的最小组数**

初始化$dp[0]=0$，其余全为INF

状态转移方程
$dp[i]=min(dp[i],dp[j]+1)(sum[i]-sum[j-1]<=m)$其中sum为前缀和

那么现在物品可以不连续呢，
我们可以**模拟退火随机打乱原序列**啊

但是这题的数据真的hin毒瘤，感觉故意卡退火啊，
最后不得已采用了**将询问区间小范围变动**的方法才A
**************

```cpp
//niiick
#include<iostream>
#include<cmath>
#include<algorithm>
#include<queue>
#include<cstring>
#include<cstdio>
using namespace std;
typedef double dd;
typedef long long lt;
#define T 1000
#define eps 1e-8
#define delta 0.98

lt read()
{
    lt f=1,x=0;
    char ss=getchar();
    while(ss<'0'||ss>'9'){if(ss=='-')f=-1;ss=getchar();}
    while(ss>='0'&&ss<='9'){x=x*10+ss-'0';ss=getchar();}
    return f*x;
}

const int maxn=50;
int n,m;
lt a[maxn],sum[maxn];
int dp[maxn],ans;

int DP()
{
    memset(dp,67,sizeof(dp)); dp[0]=0;
    for(int i=1;i<=n;++i) sum[i]=sum[i-1]+a[i];
    for(int i=1;i<=n;++i)
    for(int j=0;j<i;++j)
    if(sum[i]-sum[j]<=m)
    dp[i]=min(dp[i],dp[j]+1);
    return dp[n];
}

void SA()
{
    dd t=T; 
    while(t>eps)
    {
    	int x=0,y=0;
    	while(x==y) x=rand()%n+1,y=rand()%n+1;
    	swap(a[x],a[y]);
    	int tt=DP();
    	int dE=ans-tt;
    	if(dE>=0) ans=tt;
    	else if( exp(dE/t) > (dd)rand()/(dd)RAND_MAX ) ;
    	else swap(a[x],a[y]);
    	t*=delta;
    }
}

int main()
{
    srand(19260817);
    n=read();m=read()*1.05;
    for(int i=1;i<=n;++i) a[i]=read();
    
    ans=DP();
    for(int i=1;i<=5;++i) SA();
    printf("%d",ans);
    return 0;
}
```


---

## 作者：feecle6418 (赞：20)

**UPD：修正时间复杂度**

这里有一种非正解的方法。

状压DP，$f[S]$ 表示达到状态 $S$ 需要分成的最小组数，其中 $S$ 第 $i$ 位表示第 $i$ 个数是否已经选过。首先预处理出 $s[S]$ 表示状态 $S$ 中所有树的和。那么转移方程为：

$$ f[S]=\min\{f[j]+1\},\text{j\ 为\ S\ 子集且\ s[S-j]}\le K$$

于是暴力转移即可。复杂度为 $O(3^n)$，要超时，但是吸氧之后能过。

不会枚举子集？你只需记住以下代码：（建议手动模拟加深印象qwq）

```cpp
for(int j=i;j;j=(j-1)&i)//do something
```

代码：

```cpp
// luogu-judger-enable-o2
#pragma GCC optimize(3)
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<cstdlib>
using namespace std;
int n,a[20];
int f[300005],s[300005],ans,K;
int main(){
	memset(f,0x3f,sizeof(f));
	f[0]=0;
	scanf("%d%d",&n,&K);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<(1<<n);i++){
		for(int j=1;j<=n;j++){
			if(i&(1<<(j-1)))s[i]+=a[j];
		}
	}
	for(int i=1;i<(1<<n);i++){
		for(int j=i;j;j=(j-1)&i){
			if(s[j]>K)continue;
			f[i]=min(f[i],f[i-j]+1);
		}
	}
	printf("%d\n",f[(1<<n)-1]);
	return 0;
}
```


---

## 作者：Floatiy (赞：12)

## 模拟退火
话说啊，贪心是错的，虽然一眼看上去是没有问题的。  
贪心：75分  
裸贪心显然是错的，证明略。

但是我们发现了一个有趣的事情，把奶牛的重量从大到小排个序贪心，在一般强度的数据下是正确的，有点像给罐子里先放石头再放沙子再放水比先放水再放沙子石头要更好一样。外加这题数据很小，n^2的贪心是可以执行1e5级别次的。  

综上，退火。  
但答案如果经过特殊构造，将使得退火效率降低，难以得到正确解，这时可以采取一个小技巧：**对题目询问的区间进行小幅晃动**。
对这道题而言就是略微调整w的范围。  

鉴于贪心的错误性，我把e设成了0.9。**在错误性较大的算法下，降温稍快可以让得到正解的可能增大**。  

不多说了，上代码。

~~用小号调了半天参WA来WA去WAWA大哭~~  

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<ctime>
using namespace std;

const int MAXN = 25;

int n,w,ans,tim;
int a[MAXN],s[MAXN];
double T,e;

bool cmp(int x,int y) {
	return x > y;
}

inline bool getposs() {
	T *= e;
	if(rand() % 10000 < T) return false;
	else return true;
}

inline void clean() {
	T = 9000, e = 0.9;
	memset(s,0,sizeof(s));
	tim = 0;
	return;
}

int main() {
	srand(time(NULL));
	scanf("%d%d",&n,&w);
	w *= 1.005;
	for(int i = 1;i <= n;i++) {
		scanf("%d",&a[i]);
	}
	sort(a+1,a+1+n,cmp);
	bool flag = false;
	int cnt = 200000;
	ans = 0x3f3f3f3f;
	while(cnt--) {
		clean();
		for(int i = 1;i <= n;i++) {
			flag = false;
			for(int j = 1;j <= tim;j++) {
				if(w - s[j] >= a[i] && getposs()) {
					s[j] += a[i];
					flag = true;
					break;
				}
			}
			if(!flag) s[++tim] += a[i];
		}
		ans = min(ans,tim);
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：xh39 (赞：10)

注:本题解物品已经其他的下标都是从**0**开始。

建议看本题解前先学习状态压缩dp,不然你很可能看不懂,或跳过本题解。

首先看到数据范围,n<=18,就要想到3个算法。

①模拟退火②dfs③状态压缩dp。

太巧了,这道题3个方法都可以。但我不推荐算法①,具有随机性。

我要讲的是算法②----------状态压缩dp。

因为n很小,所以直接设f[i]为所以物品选不选的最小答案。(二进制位从左数第$j$位中0为不选第$j$件物品,1为选。)例如$n=3,i=(101)_2$时,就表示0号物品和2号物品选,$n=5,i=(11001)_2$时,就表示第$0,3,4$物品选。

转移:我们如果塞得下这个物品,就直接转移就行了。如果塞不下,就要重新开一个组。所以就要+1。

因为我们要检查塞不塞得下,所以必须设一个另外的数组表示还剩余多少空间。这里就叫做size。

所以我们可以得到以下方程。其实$b$只是为了写得清楚方便而暂时把值存在$b$里。实际代码根本不需要。

$b=\begin{cases}f[i]\kern{20pt}(a[j]<=size[i])\\f[i]+1\kern{3pt}(a[j]>\kern{8pt}size[i])\\\end{cases}$ 

注:$f$数组的值要对原先的值取min(具体可见代码)。这样才能保证最小。

注意看清$f$数组中的中括号```[```和或运算```|```,其中$f$数组的中括号已标红。

$f\color{red}{[}\color{black}i|(1<<j)\color{red}{]}\color{black}=min(f\color{red}{[}\color{black}i|(1<<j)\color{red}{]}\color{black},b)$

当$f$数组更新了($b$要小一些),就表示这种方法得到的数更小。所以我们也就要把$size$数组更新。

为了方便我就继续设一个$b$。

$b=\begin{cases}size-a[j]\kern{10pt}(a[j]<=size) //塞得下就直接塞。原容量为size,塞一个a[j]就是size-a[j]。\\w-a[j]\kern{21pt}(a[j]>\kern{8pt}size) //塞不下就重新开一个,这个组原容量为w,放了一个a[j]就是w-a[j]。\\\end{cases}$ 
```cpp
#include<iostream>
using namespace std;
int a[1000005],f[1000005],size[1000005];
int main(){
	int n,w,i,j,ykb;
	cin>>n>>w;
	for(i=0;i<n;++i){
		cin>>a[i];
	}
	ykb=(1<<n);
	for(i=0;i<ykb;++i){
		f[i]=2147483647; //2147483647=2³¹-1,即int的最大存储范围。
	}
	f[0]=1; //至少要分1个组。
	size[0]=w; //容量就是w。因为我们什么东西都没放。
	for(i=0;i<ykb;++i){ //枚举所有状态。
		for(j=0;j<n;++j){
			if(i&(1<<j)){ //从左数第j位是1。即转移的相同,就直接跳过。
				continue;
			}
			if(size[i]>=a[j]){ //塞得下。
				if(f[i]<=f[i|(1<<j)]){ //如果f可以更新才会更新size。
					f[i|(1<<j)]=f[i];
					size[i|(1<<j)]=max(size[i|(1<<j)],size[i]-a[j]);
				}
			}else{  //塞不下。
				if(f[i]+1<=f[i|(1<<j)]){ //同上。
					f[i|(1<<j)]=f[i]+1; //加1是因为要重新开一个组。
					size[i|(1<<j)]=max(size[i|(1<<j)],w-a[j]);
				}
			}
		}
	}
	cout<<f[ykb-1]; //ykb为1<<n,减1则表示n个二进制位全是1。即所有物品都选。
	return 0;
} 
```

---

## 作者：Holy_Push (赞：9)

# 这是一篇诡异的题解！慎入！（P党的福利）

SY表示他脑子已经非常乱了，他看了看题解发现是状压。但他不喜欢状压，因为想转移方程太讨厌了……所以他看到这道题时就想打个随机水过去……毕竟N≤18，随机到正确答案概率为1/18，还是可以接受的

等等，随机？SY突然发现N≤18，那我们可不可以试试看某些诡异的随机算法水过去呢？


# 模拟退火！

N≤18这种数据虽然还算比较小的，但是对于模拟退火这种人品算法还是很悬的……SY表示他随机了N遍才把这道题水过去了……而且SY表示下次拿这个程序交的时候说不定还要WA掉。


ZX：这算法看起来很厉害的样子……会不会学不会

SY：我们抛开这个听起来非常厉害的名字，实际上他就是一个随机骗分算法……

ZX：随机？既然是分组，那我们随机分组情况吧！

SY：不行，经过多次试验发现，这样不仅时间很慢，而且因此正确率也不高。我们需要想一些更优秀的随机方法。


我们可以每次交换当前序列中的两个元素！

例如我们当前的排列是1 3 2 4，经过随机交换两个元素，我们得到的新的序列可能是1 2 3 4，或者是1 4 2 3……有什么用呢？

我们要定义一种计算方法。我们用一种贪心的思想，定义一个序列a的答案cnt的计算方法如下：（w表示不能超过的体积）
1. cnt置0，当前和sum置0
2. i从1~n循环。如果sum+a[i]>w，则答案+1，sum置0，否则不进行操作。然后sum加上a[i]。
3. 如果sum>0，那么cnt+1。

例如样例中我们随机到一个排列为3,6,5,7,w=10。

i=1时，sum=3,cnt=0

i=2时，sum=9,cnt=0

i=3时，sum=5,cnt=1

i=4时，sum=7,cnt=2

最后发现sum=7>0，所以cnt=3，也就是这样的计算方式下这个序列的答案为3。

显然这样的贪心策略是错误的，不然本题就可以O(N)轻轻松松水过。但是，在模拟退火中，这是对的。原因是模拟退火可能会把所有排列都做出来，而正确的排列在这种贪心策略下显然是可以得出答案的。所以只要随机次数过多，就很有可能得到正确答案。


# 接下来就是重头戏，模拟退火的做法了！
模拟退火是一种模拟金属冷却的过程blabla之类的话我们不喜欢听，因为我们听不懂，我们只需要知道怎么做就行了。

我们现在有一种求答案的策略。每次随机生成一个新的排列（方法即为随机交换两个数）。如果这个排列在刚刚那种计算方式下更优，就用这个序列继续做，否则序列不变。

这种方法叫爬山算法。但是本题中不适合用爬山算法，因为一个更优解可能需要从当前解经过一个更劣解才能得到，而爬山算法只能往更优解去做。而模拟退火就能摆脱这个限制，能经过较劣解进而得到更优解。

模拟退火的做法是，如果当前解更优，就选择这个解。否则，以一定概率接受这一个更劣解，并且随着时间推进这个概率逐渐降低。也就是说，答案最终会渐渐稳定下来。而这个概率的计算方法为exp(P)，也就是e的P次方，其中P是参数，一般控制P<0。P一般由两个量决定，一个是当前的温度Temp，一个是上一个答案距离当前答案的差值delta，则P=delta/Temp（如果delta为正则取相反数进行计算）。然后将exp(P)与一个随机量r（0<r<1）进行比较，以此确定是否接受更劣解。

```pascal
function accept(temp,delta:extended):boolean;
var rand:extended;
begin
    if delta>=0 then exit(true);
    rand:=random(2348284)/2348284;
    if rand<exp(delta/temp) then exit(true) else
        exit(false);
end;
```
以上代码的意思是：如果delta>=0（就是说上一个答案计算出来比现在这个答案大或相等，也就是说当前这个解不会更劣），就接受这个解，返回true，否则，在0~1中随机一个数rand，如果rand<exp(delta/temp)，就接受它，返回true，否则不接受，返回false。

ZX：等等，你刚刚说随着时间推进，接受更劣解的概率会越来越低，这点如何体现？

SY：我们来分析一下。显然，我们很早就说过这是一个模拟金属冷却的过程，所以temp会随着时间推进逐渐降低。当delta为常数且为负时，temp降低，delta/temp将会减小（例如，-1/3>-1/2）。由于exp是一个幂函数且e>1，所以exp是个单调递增的函数。P=delta/temp减小时，exp(P)也会跟着减小，因此rand<exp(delta/temp)的概率将会更小。

ZX：知道如何接受较劣解了，然后怎么做呢？

SY：然后就很简单了。你可以先设定一个初温temp（例如1e40），设一个降温系数delt（一般设为0.9,0.99,0.999之类的），以及一个终止温度endtemp（例如1e-60）。当temp>endtemp的时候进行如下操作：
1. 记上一次的答案为lastans，按照之前的算法随机一个新解，新解的答案为nowans，并判断是否接受这个新解（delta=lastans-nowans）。如果不接受，则还原。
2. 记录一个全局最优解best，如果nowans<best，则best=nowans
3. 降温，即temp=temp×delta; 

最终输出best即可。
如果你对这种算法的正确率不放心，你可以进行2、3次甚至更多次的模拟退火。

详见代码咯（不知道我有没有讲清楚……）
```pascal
（我怎么会告诉你我开了O2呢）
const
    endtemp=1e-60;
    delt=0.9999;
var n,w,i,lastans,best,x,y,nowans,j,max,maxt:longint;
sum,pos,recsum,recpos,a:array[0..19] of longint;
vis:array[0..19] of boolean;
flag:boolean;
temp:extended=1e40;

function accept(temp,delta:extended):boolean;
var rand:extended;
begin
    if delta>=0 then exit(true);
    rand:=random(2348284)/2348284;
    if rand<exp(delta/temp) then exit(true) else
        exit(false);
end;//判断是否接受新解

function calc:longint;
var cnt,i:longint;
begin
    cnt:=0;calc:=0;
    for i:=1 to n do
        begin
            if (cnt+a[i]>w) then
                begin
                    inc(calc);
                    cnt:=0;
                end;
            cnt:=cnt+a[i];
        end;
    if cnt>0 then inc(calc);
end;//计算当前这种排列的答案

procedure swap(i,j:longint);
var t:longint;
begin
    t:=a[i];a[i]:=a[j];a[j]:=t;
end;

begin
    randomize;
    readln(n,w);
    for i:=1 to n do
        read(a[i]);
    lastans:=calc;best:=lastans;//初始状态即初始解
    while temp>endtemp do
        begin
            x:=random(n)+1;
            y:=x;
            while y=x do y:=random(n)+1;
            swap(x,y);//随机一个新解
            nowans:=calc;//计算新解的答案
            if accept(temp,lastans-nowans) then
                lastans:=nowans else
                    swap(x,y);//接受新解则转移，否则变成原来的状态
            if nowans<best then best:=nowans;
            temp:=temp*delt;//记录全局答案并降温
        end;
    temp:=1e40;//恬不知耻的进行多次模拟退火提升正确率
    while temp>endtemp do
        begin
            x:=random(n)+1;
            y:=x;
            while y=x do y:=random(n)+1;
            swap(x,y);
            nowans:=calc;
            if accept(temp,lastans-nowans) then
                lastans:=nowans else
                    swap(x,y);
            if nowans<best then best:=nowans;
            temp:=temp*delt;
        end;
    temp:=1e40;
    while temp>endtemp do
        begin
            x:=random(n)+1;
            y:=x;
            while y=x do y:=random(n)+1;
            swap(x,y);
            nowans:=calc;
            if accept(temp,lastans-nowans) then
                lastans:=nowans else
                    swap(x,y);
            if nowans<best then best:=nowans;
            temp:=temp*delt;
        end;
    writeln(best);
end.






```





---

## 作者：qingfengwuhui (赞：8)

## 此为本蒟蒻的第一篇题解
###### （~~请不要有太大的期望~~）



------------
## [原题传送门](https://www.luogu.org/problem/P3052)

------------
先看题干（~~虽然没什么可看的~~）。这可以算一个深搜的模板，千万不要被他的难度吓倒。

还有，此题有多种解，深搜以及记搜 + 状压都可以来写此题。

------------
### 按照顺序，先一波爆搜。
此题的爆搜较为简单，主要思路为模拟。

from 1 to n 头奶牛，每个奶牛都有两种处理的方法：

1.	放在之前的某个组中

2.	放在一个新的组中

综上可知，要传递的参数主要为
#### 当前的奶牛下标 以及 当前的组数 用 dep 与 tot 表示
后

在dfs中循环 1 到 tot，看看是否能有那一个组能放下当前的奶牛。若能，放下奶牛dep++ ， tot不变。

在循环外，直接dfs,新建一个组，dep++ ， tot++。

（注意要使用一个数组来保存）
下为爆搜的代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n , W;//表示输入的n个奶牛数 以及 每一组的最大承受重量
int w[21];//表示每一头奶牛的重量
int a[21];//记录当前的每一组中的奶牛总重
int ans = 20;//以为题目中n <= 18 及 最多只能分成18组
void dfs(int x , int y){//表示当前要放的奶牛序号为 x且当前有y组 
	if(x == n + 1)//当所有的奶牛都遍历完毕 记录当前最小的ans
	{
		ans = min(ans , y);
		return;
	}
	a[y + 1] = w[x];
	dfs(x + 1 , y + 1);
	a[y + 1] = 0;//表示当前的奶牛直接进一个新的组
	for(int i = 1;i <= y;i ++)//循环 寻找当前所有组中是否有某组能放下次奶牛
	if(a[i] + w[x] <= W){
		a[i] += w[x];
		dfs(x + 1 , y);
		a[i] -= w[x];
	}//表示放入前y各组中的某个组
	return ;
}
int main(){
	cin >> n >> W;
	for(int i = 1;i <= n;i ++)
	cin >> w[i];
	dfs(1 , 0); //表示当前要放的奶牛序号为1 组数为0
	cout << ans <<endl; 
	return 0;
} 
```
有兴趣的的小伙伴可以去试试，这个只有
# 25分！！！
这很正常。
接下来让我们来优化
-------------
## 优化1.
这是一个最最最最最简单的剪枝：

```cpp
	if(y > ans)return;
```
我相信很多的人都用过这个剪枝。

当 当前的总方案数要比已经求出的最小方案数还要多 就直接return

不过他的作用也算比较大
```cpp
#include<bits/stdc++.h>
using namespace std;
int n , W;
int w[21];
int a[21];
int ans = 20;
void dfs(int x , int y){//表示当前要放的奶牛序号为 x且当前有y组 
	if(x == n + 1)
	{
		ans = min(ans , y);
		return;
	}
	if(y > ans)return;
	a[y + 1] = w[x];
	dfs(x + 1 , y + 1);
	a[y + 1] = 0;
	for(int i = 1;i <= y;i ++)
	if(a[i] + w[x] <= W){
		a[i] += w[x];
		dfs(x + 1 , y);
		a[i] -= w[x];
	}
	return ;
}
int main(){
	cin >> n >> W;
	for(int i = 1;i <= n;i ++)
	cin >> w[i];
	dfs(1 , 0); 
	cout << ans <<endl; 
	return 0;
} 
```
# 51分
有进步，再继续
----------
## 优化2.
举个栗子：


我们在使用天平的时候，总是先放大的砝码。

其实，这就是一种优化。

当奶牛的体重都输进来的之后，我们先使用一下sort函数，将奶牛体重从大到小排列。

它的优化是十分明显的，不信我们来试试，最终分数是：
## 100分！！！！
没错，加了他，基本可以满分。

当然，如果数据再继续加强，我们可以再此基础上，使用记搜 + 状压。
效果也同样明显。

只要理解了，代码还是比较好写的。


以下是满分代码,但是没有注释。
要看注释的向上翻：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n , W;
int w[21];
int a[21];
int ans = 20;
bool cmp(int x , int y){
	return x > y;
}
void dfs(int x , int y){
	if(x == n + 1)
	{
		ans = min(ans , y);
		return;
	}
	if(y >= ans)return;
	a[y + 1] = w[x];
	dfs(x + 1 , y + 1);
	a[y + 1] = 0;
	for(int i = 1;i <= y;i ++)
	if(a[i] + w[x] <= W){
		a[i] += w[x];
		dfs(x + 1 , y);
		a[i] -= w[x];
	}
	return ;
}
int main(){
	cin >> n >> W;
	for(int i = 1;i <= n;i ++)
	cin >> w[i];
	sort(w + 1 , w + 1 + n , cmp);
	dfs(1 , 0); 
	cout << ans <<endl; 
	return 0;
} 
```
---------
###### （~~写的不好，大佬勿喷~~）
# END

---

## 作者：zhenglier (赞：4)

# 暴搜出奇迹

小蒟蒻因为不会状态压缩，就只能用暴搜来做这道题。

先弄一个迭代加深，小蒟蒻不会二分，只能从1枚举到n。

在搜索中枚举每个物品的状态，就是这个物品到底放在哪里，暴力枚举每个车厢

然后就能愉悦的拿74分了，顺便提醒一句~~(十年OI一场空，不开long long见祖宗)~~
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
long long V,v[20],st[20];
void dfs(int now,int limit){
    if(now==n+1){
        cout<<limit<<endl;
        exit(0);
    }
    for(int i=1;i<=limit;++i){
        if(st[i]+v[now]<=V){
            st[i]+=v[now];
            dfs(now+1,limit);
            st[i]-=v[now];
        }
    }
}
int main()
{
    cin>>n>>V;
    for(int i=1;i<=n;++i){
        scanf("%lld",v+i);
    }
    for(int i=1;i<=n;++i){
        dfs(1,i);
    }
}
```
但这样拿不了满分~~(所以我们可以开O2)~~，但即使是开了O2也没用，我们要想一点有用的剪枝方法

可以发现前几个数可以放在多个没放过东西的地方，但这本质上是相同的，所以对于多个空的车厢，我们只用放一个就行了，我们可以建个变量存是否放置在空的车厢过就行了。

然后就可以愉悦的AC了

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
long long V,v[20],st[20];
void dfs(int now,int limit){
	if(now==n+1){
		cout<<limit<<endl;
		exit(0);
	}
	int b=0;
	for(int i=1;i<=limit;++i){
		if(st[i]==0&&b)continue;
		if(st[i]==0)b=1;
		if(st[i]+v[now]<=V){
			st[i]+=v[now];
			dfs(now+1,limit);
			st[i]-=v[now];
		}
	}
}
int main()
{
	cin>>n>>V;
	for(int i=1;i<=n;++i){
		scanf("%lld",v+i);
	}
	for(int i=1;i<=n;++i){
		dfs(1,i);
	}
}
```

---

## 作者：陈曦 (赞：4)

## 贪心版&&DP版模拟退火题解总结

我们发现这道题与均分数据有点像，所以我们可以随机序列状态。

如果我们按答案分法排在一起，不就成了
```
给你一个序列，让你分成几段，使每段的和不超过w，问最少可以分几段？
```

因为我们不知道要分几组，所以有两种方法。

一种是类似于贪心，一个个加，超过就 $tot++$ 。

第二种是 $dp$ ：如果假设需要分组的物品必须连续，那么一个 $n^2$ 的 $dp$ 很容易想到 

$dp[i]$ 表示将前 $i$ 个物品分组的最小组数

初始化 $dp[0]=0$ ，其余全为 $INF$

状态转移方程 $dp[i]=min(dp[i],dp[j]+1)(sum[i]-sum[j-1]<=w)$ 其中 $sum$ 为前缀和

（第二种摘自[niiick](https://www.luogu.org/space/show?uid=60885)的题解）

综合来说，dp正确率更高，但因为 $n$ 不大，但贪心也不会错，而且更容易码，复杂度更优（虽然模拟退火为 $O($~~玄学~~$)$）。

我们来证明一下贪心正确性：

如果有一个序列被劈成 $m$ 段，说明这 $m$ 段每一段和都小于 $w$ ，那么按照贪心去分，每一段尽可能多分，段数不会超过 $m$ 段，我们求的是最小值，所以贪心是正确的。

总的来说：贪心时间复杂度低：$O($迭代次数$\times n)$，空间复杂度也低。

而 $dp$ ：$O($迭代次数$\times n^2)$

第一种：

```cpp
int tanxin()
{
    int tot=0,pos=0;//tot记录当前总值，pos记录组数
    f[n+1]=w+1;//使n+1与n位置分开
    for(int i=1;i<=n+1;i++)
    {
        if(tot+f[i]>w)//超过w
        {
            tot=f[i];
            pos++;
        }
        else
        tot+=f[i];
    }
    return pos;//返回组数
}
```
第二种：
```cpp
inline int DP()//不解释了，dp方程在上面
{
    memset(dp,127,sizeof(dp)); 
    dp[0]=0;
    for(int i=1;i<=n;++i) 
    sum[i]=sum[i-1]+f[i];
    for(int i=1;i<=n;++i)
    for(int j=0;j<i;++j)
    if(sum[i]-sum[j]<=w)
    dp[i]=min(dp[i],dp[j]+1);
    return dp[n];
}

```
我们在退火时，随机交换两数位置，再计算，退火。

这样就可以随机序列了。

上代码（中间空出的把上面任意一种填进去就好了）：

```cpp
#include<iostream>
#include<cstdio>
#include<ctime>
#include<cstdlib>
#include<cmath>
#include<cstring>
using namespace std;
long long f[50]；
/*
long long dp[50],sum[50];//用dp时加
*/
double t,tmin=1e-8;
double delta=0.995;
double ans=20;
int w,n;
/*
......
*/
void sa()
{
    t=3000;double now=ans;
    while(t>tmin)
    {
        int x=rand()%n+1;
        int y=rand()%n+1;
        while(x==y)x=rand()%n+1,y=rand()%n+1;
        swap(f[x],f[y]);
        
        int pos=DP()或tanxin()
        
        double delta2=(double)pos-now;
        if(delta2<0)
        ans=now=pos;
        else  if(exp(-delta2/t)*RAND_MAX>rand());
        else swap(f[x],f[y]);
        t*=delta;
    }
}
int main()
{   srand(19491001);srand(rand());srand(rand());
    long long maxn=-9999999;
    scanf("%d%d",&n,&w);
    w*=1.05;//防止浮点数出错，把w扩大一点
    for(register int i=1;i<=n;i++)
    {
        scanf("%lld",&f[i]);
        maxn=max(f[i],maxn);
    }
    
    ans=DP()或tanxin()
    
    sa();sa();sa();sa();sa();//多跑几遍，怕非酋
    int last=ans;
    printf("%d",last);
}
```
另一种退火方式：（by [一秒](https://www.luogu.org/space/show?uid=20181)）

直接随机一整个序列，复杂度略次于 $dp$ ，但容易理解。
```cpp
#include<bits/stdc++.h>
using namespace std;
int s[20],p[20],s1[20],ans=1e9;
int main(){
        int n,m,k=1;cin>>n>>m;
        m*=1.05;
        srand((unsigned)time(NULL));
        for(int q=1;q<=n;q++)
                cin>>s[q];
        while(k<=10000){
                k++;int a;
                for(int q=1;q<=n;q++){
                        a=abs((rand()*65219+1973))%(n+1);
                        if(a==0)a++;
                        if(p[a]==0)p[a]=1,s1[q]=s[a];
                        else q--;
                }
                int ans1=1,sum=s1[1];
                for(int q=2;q<=n;q++){
                if(sum+s1[q]>m)
                        sum=s1[q],ans1++;
                else
                        sum+=s1[q];
                }
                ans=min(ans,ans1);
                memset(p,0,sizeof(p));
                memset(s1,0,sizeof(s1));
        }
        cout<<ans;
}
```

退火大法好，(~~8位~~)质数保平安。

---

## 作者：momo5440 (赞：3)

看到**n**的范围大概就想到了状压dp但奈何我实在是太弱了而且我也不会什么模拟退火，所以就只能玄学骗分了，所以在此我讲一下我的骗分方法由于受到[P1284 三角形牧场](https://www.luogu.org/problem/P1284)的启发所以我想这题是否也能按相同的方法骗分

再次我先说一下P1284这题的方法：先随意打乱整个序列然后贪心所以我这题的思路也是随意打乱序列，然后贪心我们设打乱以后的序列为**c**，那么一定存在一个**c**使得最优解所分的每组所包含的数在**c**里全部相邻，所以我们在**c**里就是连续取，能取就取不能取就再开一组，靠运气看能不能找到正确的**c**，而且正确的**c**组数不见得只有一个，因为连续的数任意排列都是对的

把代码贴上

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
ll n,w;
ll c[20];
void wash(){//打乱
	for (int i=0;i<n;i++){
		int t=rand()%n;
		swap(c[i],c[t]);
	}
}
ll ans=(1<<30);
ll work(){//贪心
	ll now=c[0];
	ll tp=1;
	for (int i=1;i<n;i++){
		if (now+c[i]<=w){
			now+=c[i];
		}
		else{
			now=c[i];
			tp++;
		}
	}
	return tp;
}
int main(){
	cin>>n>>w;
	for (int i=0;i<n;i++) scanf("%lld",&c[i]);
	ans=work();
	for (int j=1;j<=1500000;j++) {//只要不TLE就做
		wash();
		ans=min(ans,work());
	}
	cout<<ans<<endl;
}
```


---

## 作者：PhantasmDragon (赞：2)

状压大法好呀啊!

$f[i]$ 表示奶牛选择状态为 $i$ 时的最少分组数.

$sum[i]$ 表示状态为 $i$ 的时候奶牛重量总和

DP一下就好了啊, $sum$ 预处理一下就好了qwq

$f[i]=\min(f[j]+1|sum[i\ xor\ j]\leq lim)$


------------


```
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define maxn 19
#define RG register
using namespace std;
int w[maxn],f[(1<<19)],sum[(1<<19)],n,lim,F;
int main()
{
	scanf("%d%d",&n,&lim);
	F=(1<<n)-1;
	for(RG int i=1;i<=n;i++) scanf("%d",&w[i]),sum[(1<<i-1)]=w[i];
	for(RG int i=1;i<=F;i++) sum[i]=sum[i^(i&-i)]+sum[(i&-i)];
	memset(f,0x3f,sizeof(f));
	f[0]=0;
	for(RG int i=1;i<=F;i++)
	{
		for(RG int j=i;j;j=((j-1)&i))
		{
			if(sum[j]>lim) continue;
			f[i]=min(f[i],f[i^j]+1);
		}
	}
	printf("%d",f[F]);
}
```

---

## 作者：zht467 (赞：2)

谁说这不是DP？

输出被阉割了。

只输出最少分的组数即可。

f 数组为结构体

f[S].cnt 表示集合 S 最少的分组数

f[S].v 表示集合 S 最少分组数下当前组所用的最少容量

f[S] = min(f[S], f[S - i] + a[i]) (i ∈ S)

运算重载一下即可。

——代码







```cpp
#include <cstdio>
#include <iostream>
int n, m, w;
int a[19];
struct qwq
{
    int cnt, v;
    qwq(int cnt = 0, int v = 0) : cnt(cnt), v(v) {}
}f[1 << 19];
inline qwq operator + (const qwq x, const int d)
{
    return x.v + d <= w ? qwq(x.cnt, x.v + d) : qwq(x.cnt + 1, d);
}
inline bool operator < (const qwq x, const qwq y)
{
    return x.cnt == y.cnt ? x.v < y.v : x.cnt < y.cnt;
}
inline qwq min(qwq x, qwq y)
{
    return x < y ? x : y;
}
inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    for(; !isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for(; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + ch - '0';
    return x * f;
}
int main()
{
    int i, S;
    n = read();
    w = read();
    m = (1 << n) - 1;
    for(i = 1; i <= n; i++) a[i] = read();
    for(S = 1; S <= m; S++)
    {
        f[S] = qwq(1e9, w);
        for(i = 1; i <= n; i++)
        {
            if(!((1 << i - 1) & S)) continue;
            f[S] = min(f[S], f[(1 << i - 1) ^ S] + a[i]);
        }
    }
    printf("%d\n", f[m].cnt + 1);
    return 0;
}
```

---

## 作者：lx_zjk (赞：1)

这道题是道状态压缩的题目

首先我的思路是这样的 ~~不过后来被毙了~~

# part 1 正确 but TLE & MLE的题目

$dp[S][i]$ 表示在$S$阶段下,当前背包装下了i体积

状态转移方程式也比较易推

```cpp

if (i + v[j]) > w)
dp[s | (1 << j)][v[j]] = min(dp[s | (1 << j)][v[j]],dp[s][i] + 1);
else dp[s | (1 << j)][i + v[j]] = min(dp[s | (1 << j)][i + v[j]], dp[s][i]);
for (int i = 0; i <= w; i ++ )
	ans = max(dp[(1 << n) - 1][i]);

```

~~不过因为空间时间两开花 这个方法被毙了~~

# part 2


$f[s]$ 表示s状态下最小的背包数

但是状态转移方程式比较难推出

所以引出了$g[s]$ 

$g[s]$表示s状态下当前最小背包重量

状态转移方程式 $f[s | (1 << i)] = f[s] + (g[s] + v[i] > w)$

$g[s]$函数也要根据$f[s]$推出

```cpp

这里有个事项要注意一定要
if (g[i] + v[j] > w && f[i | (1 << j)] >= f[i] + 1) 

or

if (g[i] + v[j] <= w && f[i | (1 << j)] >= f[i]) 

才能转移

不然g[i]会错的 只有17pts
```

完整版转移方程
```cpp
for (int i = 0; i < (1 << n); i ++ ) {
	for (int j = 0; j < n; j ++ ) {
		if (!(i & (1 << j))) {
			if (g[i] + v[j] > w && f[i | (1 << j)] >= f[i] + 1) {
				f[i | (1 << j)] = f[i] + 1;
				g[i | (1 << j)] = min(v[j], g[i | (1 << j)]);
			}
			if (g[i] + v[j] <= w && f[i | (1 << j)] >= f[i]) {
				f[i | (1 << j)] = f[i];
				g[i | (1 << j)] = min(g[i] + v[j], g[i | (1 << j)]);
			}			
		}
	}
}
```

# 完整版CODE

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

inline ll read() {
    ll f = 1, x = 0;char ch;
    do {ch = getchar();if (ch == '-')f = -1;} while (ch > '9' || ch < '0');
    do {x = x * 10 + ch - '0';ch = getchar();} while (ch >= '0' && ch <= '9');
    return f * x;
}

const int MAX_N = 20;

const int MAX_S = (1 << 19) - 1; 


int n, w, v[MAX_N], f[MAX_S], g[MAX_S];

int main() {
	n = read(); w = read();	
	memset(f, 127, sizeof(f));
	memset(g, 127, sizeof(g));
	for (int i = 0; i < n; i ++ ) 
		v[i] = read();
	f[0] = 1;
	g[0] = 0;
	for (int i = 0; i < (1 << n); i ++ ) {
		for (int j = 0; j < n; j ++ ) {
			if (!(i & (1 << j))) {
				if (g[i] + v[j] > w && f[i | (1 << j)] >= f[i] + 1) {
					f[i | (1 << j)] = f[i] + 1;
					g[i | (1 << j)] = min(v[j], g[i | (1 << j)]);
				}
				if (g[i] + v[j] <= w && f[i | (1 << j)] >= f[i]) {
					f[i | (1 << j)] = f[i];
					g[i | (1 << j)] = min(g[i] + v[j], g[i | (1 << j)]);
				}
						
			}
		}
	}
	cout << f[(1 << n) - 1] << endl;
	return 0;
}


```

---

## 作者：Edward_Elric (赞：1)

## 思路
简单状压dp

$N<=18$告诉你这是一个状压或者是爆搜。

首先肯定需要一维状态维，然后好像不需要什么了。很自然的想到用$f[i]$表示状态为i的时候最小分组。用一个$g[i]$表示剩余空间。

首$g[i]$在满足$f[i]$最小同时应该最大,贪心的思想，这样做一定是对的。但是为什么一定要满足$f[i]$最小。其实也很好想。如果$f[i]$比之前小，想到于多了更多剩余空间。所以一定满足最优性

方程就不贴了（其实是latax崩了），看首页的大佬就行了。用的填表更新
## 代码
```cpp
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
using namespace std;
int f[1<<20],g[1<<20];
int a[20];
int n,w;
int s,t;
int main(){
	memset(f,inf,sizeof(f));
	cin>>n>>w;
	t=(1<<n)-1;
	for(int i=0;i<n;i++)cin>>a[i];
	f[0]=0;
	for(int i=1;i<=t;i++){
		for(int j=0;j<n;j++){
			if(!(i&(1<<j)))continue;
			int s=(i^(1<<j));
			if(g[s]>=a[j]&&f[i]>=f[s]){
				if(f[i]==f[s])
				g[i]=max(g[i],g[s]-a[j]);
				else g[i]=g[s]-a[j];
				f[i]=f[s];
			}
			if(g[s]<a[j]&&f[i]>f[s]){
				if(f[i]==f[s]+1)g[i]=max(g[i],max(g[s],w-a[j]));
				else g[i]=max(g[s],w-a[j]);
				f[i]=f[s]+1;
			}
		}
	}
	printf("%d\n",f[t]);
	return 0;
}
```

---

## 作者：Panthera_AFO (赞：1)

先说点题外话，这题没有参考题解，结果查了1h

查错的痕迹就不放出来了...(起码20行

给组海星的数据
```
5 25
8
19
11
12
18
```
好！回到正题

这题我用的填表法

自认为比题解里的一堆刷表法易懂

状态
+ f[i]表示i状态需要的最少分组
+ lftV[i]表示i状态能剩下的最大空间

转移
+ f[i]更新的时候lftV[i]一定更新
+ f[i]不更新的lftV[i]不一定不更新！

详见代码

```
#include<iostream>
#include<cstdio>
#include<cstring>
int const maxn=21,maxm=272144,maxe=501000,inf=0x1f1f1f1f;
int n,V,mx,cv[maxn];
int Pos[maxm];
long long lftV[maxm];int f[maxm];
inline void change(int x)
{
    for(int i=4;i>=0;i--)
        printf("%d",x>>i&1);
}
inline void rin()
//顾名思义
{
    scanf("%d%d",&n,&V);
    for(int i=1;i<=n;i++)
        scanf("%d",&cv[i]);
    return;
}
inline void pretreatment()
//顾名思义
{
    mx=(1<<n)-1;
    Pos[1]=1;
    for(int i=2;i<=n;i++)
        Pos[i]=Pos[i-1]<<1;
        //只选第i位的状态
    memset(f,0x1f,sizeof(f));
    for(int i=1;i<=n;i++)
    {
        lftV[Pos[i]]=V-cv[i];
        f[Pos[i]]=1;
    }
    //把只选一只牛的状态初始化
    return;
}
inline void solve()
//顾名思义
{
    for(int i=0;i<=mx;i++)
    {
        if(f[i]!=inf)
            continue;
         //已经初始化过的就跳过
         for(int j=1;j<=n;j++)
         	if(i&Pos[j])
            //找到i状态的某个1
         	{
         		int y=i^Pos[j];
                //把这个1给揪出来不就是上一个状态啦
                if(lftV[y]-cv[j]>=0)
                {
                    if(f[i]>f[y])
                        f[i]=f[y],lftV[i]=lftV[y]-cv[j];
                    else 
                        if(f[i]==f[y])
                            lftV[i]=std::max(lftV[i],lftV[y]-cv[j]);
                }
                else
                {
         			if(f[i]>f[y]+1)
         				f[i]=f[y]+1,lftV[i]=V-cv[j];
         			else
         				if(f[i]==f[y]+1)
         					lftV[i]=std::max(lftV[i],lftV[y]-cv[j]);
             	}
                //讲讲转移
                //有两种情况
                //第一种：上个状态的剩余空间能装下当前这个牛，这时就不用多分1组了
                //第二种：无法装下，需要再分1组
                //注意要特殊处理f数组不更新的情况，因为可能lftV会更新
             }
    }
    return;
}
inline void write()
//顾名思义
{
//	change(mx);
    printf("%d",f[mx]); 
    return;
}
int main()
{
    rin();
    pretreatment();
    solve();
    write();
    return 0;
}
```

---

## 作者：暮影灰狼 (赞：1)

本题的样例输出有误，只输出分组数即可。

当然，你看到这篇题解的时候，可能输出已经被改正了。

此题并不需要状压DP，迭代加深搜索即可，与P1361完全相同。

我直接把1361的代码复制过来就AC了...出于对USACO的尊重，改了一个变量名...


迭代加深搜索：通过一个循环控制搜索层数，实现剪枝。


```cpp
#include<cstdio>
#include<algorithm>
#include<cmath>
int a[20],box[20],n,w,deep;
bool flag;
void dfs(int cnt,int cc)
{//cnt是电梯数，cc是当前处理到的奶牛序号 
    if(flag)    return;
    if(cc == n)
```
{//搜索到答案，通过flag退出回溯
```cpp
        flag = true;
        return;
    }
    cc ++;
    for(int i = 1;i <= std::min(cnt,cc);++ i)
    {
        if(box[i]+a[cc] <= w)
        {
            box[i] += a[cc];
            dfs(cnt,cc);
            box[i] -= a[cc];
        }
    }
}
int cmp(int a,int b)
{return a > b;}
int main()
{
    scanf("%d%d",&n,&w);
    for(int i = 1;i <= n;++ i)
        scanf("%d",&a[i]);
    std::sort(a+1,a+1+n,cmp);
    //小剪枝：先放重量大的奶牛，减少不必要的搜索 
    while(++deep)
```
{//迭代加深，控制搜索层数
```cpp
        dfs(deep,0);
        if(flag)
        {
            printf("%d\n",deep);
            return 0;
        }
    }
    return 0;
} 

```

---

## 作者：流逝丶 (赞：0)

我不会退火也不会状压DP，但也能过这个题

看一眼数据范围$n\le18$,这题可以爆搜

不过加个优化，给原序列排个序，从大到小排，依次枚

举当前物品在哪个组，或者给它另开一个组，加上最优

性剪枝，妥妥的能过

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int n,w,ans;
int a[20],b[20];
bool cmp(const int &a,const int &b){
	return a>b;
}
void dfs(int now,int tot){
	if(tot>=ans)return ;
	if(now==n+1){
		ans=min(tot,ans);
		return ;
	}
	for(int i=1;i<=tot;++i)
		if(b[i]+a[now]<=w){
			b[i]+=a[now];
			dfs(now+1,tot);
			b[i]-=a[now];
		}
	b[tot+1]=a[now];
	dfs(now+1,tot+1);
	b[tot+1]=0;
}
int main(){
	scanf("%d%d",&n,&w);
	for(int i=1;i<=n;++i)
		scanf("%d",&a[i]);
	sort(a+1,a+1+n,cmp);
	ans=n;
	dfs(1,0);
	printf("%d",ans);
	return 0;
}
```


---

## 作者：RikoHere (赞：0)

线性状压DP的正确性不是很显然，模拟退火也不会写，但我选择写搜索

显然直接全排列的复杂度达到了$O(n!)$甚至更高，是无法解决本题$n \leq 18$的数据，要用一些特殊的方法优化一下搜索

迭代加深搜索的正确性是显然的，假设现在已经使用了$x$个电梯，设还需要使用的电梯为$y$个，当前最优答案为$ans$，剩余奶牛的重量和为$T$，首先显然有$\frac{T}{W} \leq y$，进一步推出当$ans \leq x+\frac{T}{W}$便**无法更新答案**，即可退出搜索

任然担心被卡怎么办？我们可以优化枚举的物品，若是直接枚举奶牛显然效率太低，改为枚举集合，即枚举电梯，一个显然的贪心策略是对于一个电梯我们能塞多少奶牛就塞多少奶牛....接下来又回到状态压缩....设$S$为一个集合，其中所有奶牛重量和小于承载量，显然对**于它的任意一个子集我们在搜索时都没有枚举的必要**

为了得到所有符合要求的集合，我们首先用$O(n2^n)$ 的时间进行枚举状态和进行预处理，已经足够通过本题，部分细节见代码(PS:搜索300ms,dp600ms....)

 - **tip:** 按数据范围来算可能会爆`int`(虽然没爆)
 
 ```
//2019/8/7->Riko->AtNCU->luoguP3052
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
namespace Rikopack {
    bool digit (int ch) { return (ch <= '9' and ch >= '0');}
    inline int in () {
    	int x = 0, ch = getchar(), base = 1;
    	while (!digit(ch)) {
    	    if (ch == '-') base = -1;
    	    ch = getchar();
    	}
    	while (digit(ch)) x = x*10+ch-'0', ch = getchar();
    	return x*base;
    }
    template <typename T> inline void smax (T& x, T y) { if (x < y) x = y;}
    template <typename T> inline void smin (T& x, T y) { if (x > y) x = y;}
    void print (int x) { printf("debug:%d\n", x);}
    const int MAXINT = 2123456789;
    #define LL long long
    //Believing heart is your power
}
using namespace Rikopack;
using namespace std;
const int N = 18;
int n, m, ind, tot, ans;
int w[N+8], in_s[(1<<N)+64], tag[(1<<N)+64], Price[(1<<N)+64];
int getprice (int x) {
	int cnt = 0;
	for (int i = 1; i <= n; ++i) {
		if (x&(1<<(i-1))) cnt += w[i];
	}
	return cnt;
}
int gstate (int x) {
	return ((tot-Price[x])-1)/m+1;
}
void dfs (int x, int step, int head) {
	if (x == (1<<n)-1) {
		smin(ans, step); return;
	}
	if (step+(gstate(x)) >= ans) return;
	for (int i = head; i <= ind; ++i) {
		int y = in_s[i];
		if ((x&y) == y) continue;
		dfs(x|y, step+1, i+1);
	}
}
void work () {
	for (int i = (1<<n)-1; i >= 1; --i) {
		if (Price[i] > m) continue;
		int y = i;
		while (y) {
			int lowbit = y&(-y);
			tag[i^(lowbit)] = true;
			y -= lowbit;
		}
		if (tag[i]) continue;
		in_s[++ind] = i;
	}
	dfs(0, 0, 1);
	printf("%d", ans);
}
void prepare () {
	n = in(); m = in();
	for (int i = 1; i <= n; ++i) {
		w[i] = in();
		tot += w[i];
	}
	sort(w+1, w+n+1);
	for (int i = 1; i < (1<<n); ++i) {
		Price[i] = getprice(i);
	}
	ans = n;
	work();
}
int main () { prepare();}
```


---

## 作者：fmj_123 (赞：0)

看起来本题无从下手，所以我们可以先用$dfs$，我们设$(x,y,z)$的意义是当前选择状态为$x$，当前分了$y$组，最后一组还剩$z$空间。这个状态中，我们并不需要考虑将一个物品放在前面的组中，因为这个等同于在该状态前面就放入了这个物品。则我们在每轮$dfs$中枚举放哪一个物品到最后一组（或新开一组）。

这种做法看起来不太好，我们尝试优化。

我们可以证明在$x,y$相同时，对于$z$和$z'$，若$z>z'$，$(x,y,z)$推出来的答案一定不会比$(x,y,z')$更劣，那我们就不需要$dfs$ $(x,y,z')$的状态了。

因此，我们记录每个$(x,y)$中的最小$z$，若$z'>z$就不$dfs (x,y,z')$。

与此同时，我们在$dfs$中也不需要记录$z$了。因为$z$一定是我们记下的最小的$z$。

然而这样就过了？？？

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[100],ans=2147483647;
int f[262147][20];//记录(x,y,z)中z的最小值，大于则不用再搜
void dfs(int x,int y)
{
    if (x==(1<<n)-1) ans=min(ans,y);//结束状态
	int z=f[x][y];
    for (int i=1;i<=n;i++)
    {
        if (!((x>>(i-1))&1))//当前位没放入任意一组
        {
            int newx=x+(1<<(i-1));
            if (z>=a[i])//放入当前组
            {
                if (z-a[i]>f[newx][y])//优化
                {
                    f[newx][y]=z-a[i];
                    dfs(newx,y);
                }
            }
            else//新开一组
            {
                if (m-a[i]>f[newx][y+1])//优化
                {
                    f[newx][y+1]=m-a[i];
                    dfs(newx,y+1);
                }
            }
        }
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for (int i=0;i<(1<<n);i++)
      for (int j=0;j<=n;j++)
        f[i][j]=-1;
    for (int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
    }
    dfs(0,0);
    cout<<ans<<endl;
    return 0;
}
```
~~原来只要把y按同样方法做就可以加速了~~

按上面的逻辑，显然$x$相同时，$y$越小越好，则我们可以再次优化。

贴上再次优化后代码
```cpp
//除优化了y，其余相同
#include<bits/stdc++.h>
using namespace std;
int n,m,a[100],ans=2147483647;
int f[262147],f1[262147];//f1表示相同状态下最小的y
void dfs(int x)
{
	int y=f1[x];int z=f[x];
    if (x==(1<<n)-1) ans=min(ans,y);
    for (int i=1;i<=n;i++)
    {
        if (!((x>>(i-1))&1))
        {
            int newx=x+(1<<(i-1));
            if (z>=a[i])
            {
            	if (y<=f1[newx])
            	{
			      if (y<f1[newx]) f[newx]=-1;
            	  f1[newx]=y;
                  if (z-a[i]>f[newx])
                  {
                      f[newx]=z-a[i];
                      dfs(newx);
                  }
                }
            }
            else
            {
            	if (y+1<=f1[newx])
            	{
			      if (y+1<f1[newx]) f[newx]=-1;
            	  f1[newx]=y+1;
                  if (m-a[i]>f[newx])
                	{
                    	f[newx]=m-a[i];
                    	dfs(newx);
                	}
            	}
            }
        }
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for (int i=0;i<(1<<n);i++)
        f1[i]=2147483647,f[i]=-1;
    for (int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
    }
    f[0]=-1;f1[0]=0;
    dfs(0);
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：SuperGoodGame (赞：0)

没有用纯爆搜过的吗QWQ ， 思路就是纯爆搜+套路最优化剪枝 ， 还有一个排序的优化 

虽然跑得是挺慢的 ， 但是距离TLE也挺远 ， 可能是数据没卡爆搜吧QAQ

套路最优化剪枝就是  当前组数 + 剩下物品最小组数 > Ans 的话 ，就肯定对Ans没贡献了 ， 愉快剪去 。


代码：

``` C++
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

#define re register

int f[1<<18] , now[20] , a[20];
int w,n , Min=2e9 , ans= 55;

bool cmp(int x,int y){
	return x>y;
}
void dfs(int k,int cnt){
	if(cnt+Min*(n-k+1)/w>ans) return ;
	if(k>n){
		ans=cnt;
		return ;
	}
	for(re int i=1;i<=cnt;i++){
		if(now[i]+a[k]<=w)
			now[i]+=a[k] , dfs(k+1,cnt) , now[i]-=a[k];	
	}
	now[++cnt]=a[k] , dfs(k+1,cnt) , cnt--;
}
int main(){
	cin>>n>>w;
	for(re int i=1;i<=n;i++) 
		cin>>a[i] , Min=min(Min,a[i]);
	sort(a+1,a+n+1,cmp);
	dfs(1,0);
	cout<<ans;
	return 0;
}
```

---

## 作者：zx2003 (赞：0)

```cpp
var
 i,n,ww,l,r,m,s:longint;
 w,a:array[1..18] of longint;
function dfs(x:longint):boolean;
var
 i,j:longint;
 f:boolean;
begin
 if x=n+1 then exit(true);
 for i:=1 to m do
  if a[i]>=w[x] then
  begin
   f:=false;
   for j:=1 to i-1 do
    if a[j]=a[i] then
    begin
     f:=true;
```
break

```cpp
    end;
   if not f then
   begin
    dec(a[i],w[x]);
    if dfs(x+1) then exit(true);
    inc(a[i],w[x])
   end
  end;
 exit(false)
end;
begin
 readln(n,ww);
 for i:=1 to n do
 begin
  readln(w[i]);
  inc(s,w[i])
 end;
 for i:=1 to n-1 do
  for l:=i+1 to n do
   if a[i]>a[l] then
   begin
    m:=a[i];
    a[i]:=a[l];
    a[l]:=m
   end;
 l:=s div ww;
 r:=n;
 while l<r do
 begin
  m:=(l+r) shr 1;
  for i:=1 to m do a[i]:=ww;
  if dfs(1) then r:=m
   else l:=m+1
 end;
 writeln(l)
end.
```
裸搜即可
两个剪枝

1.因为答案是否可行是单调的，所以二分答案；

2.在当前状态，两个相同剩余容量的”组“，没必要重复搜索，可以暴力判重；

另：
1.其实本题样例与实际数据不同，实际上直接输出答案即可，无需输出方案；

2.这题不是贪心、DP之类的题，希望改下标签@kkksc03


---

## 作者：U121570 (赞：0)

 $dfs$思路并不是很难

  这里我们将 $c_i$当成每个物品的体积，$weigh_i$当成每个组已经有的体积，然后依次从$1$~$18$枚举$ans$,如果有办法就马上输出结果，并结束循环
  
然后$dfs$枚举第$i$个物品能放在的地方，如果可以放就进行回溯，枚举第$i+1$个物品，重复如此

如何在函数中结束这个程序呢？

$exit(0)$

------------

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,w,ans;
long long c[30+10],weigh[30+10];
void work(){
	for(int i=1;i<=n;i++){
		if(weigh[i]>w){
			return ;
		}
	}
	printf("%d\n",ans);
	exit(0);
}
bool comp(int x,int y){
	return x>y;
}
void dfs(int num){
	if(num>n)work();
	for(int i=1;i<=ans;i++){
		if(weigh[i]+c[num]<=w){
			weigh[i]+=c[num];
			dfs(num+1);
			weigh[i]-=c[num];
		}
	} 
} 
int main(){
    scanf("%d %d",&n,&w);
    for(int i=1;i<=n;i++){
    	scanf("%lld",&c[i]);
    	ans=ans+c[i];
	}
	sort(c+1,c+n+1,comp);
	ans=1;
	for(;1;){
		memset(weigh,0,sizeof(weigh));
		dfs(1);
		++ans;
	}
	return 0;
}

```


------------

等你提交上去以后，你会发现：为什么 #$5$会$TLE$？

这里我们运用一个贪心思路：$x$个苹果,每个位子里的苹果不能超过$y$个，那么最少有$x/y$个位子，放进去至少要放入$x_i$个，举例：

```cpp
x=10 y=4

```
$x_1$=2 $x_2$=3 $x_3=4$ $x_4$=1

那么至少需要 $x/y$ 即为 $10/4=2$，然而答案为 $3$ 这样$1$就可以不用算了，为了保险起见，我们还是把它i安城$x/y-1$防止算错

---------
```cpp

#include<bits/stdc++.h>
using namespace std;
int n,w,ans;
int c[30+10],weigh[30+10];
bool use[30+10];
void work(){
    for(int i=1;i<=n;i++){
        if(weigh[i]>w){
            return ;
        }
    }
    printf("%d\n",ans);
    exit(0);
}
bool comp(int x,int y){
    return x>y;
}
void dfs(int num){
    if(num>n)work();
    for(int i=1;i<=ans;i++){
        if(weigh[i]+c[num]<=w){
            weigh[i]+=c[num];
            dfs(num+1);
            weigh[i]-=c[num];
        }
    } 
} 
int main(){
    //freopen("3052.in","r",stdin);
    //freopen("3052.out","w",stdout);
    scanf("%d %d",&n,&w);
    for(int i=1;i<=n;i++){
    	scanf("%d",&c[i]);
    	ans=ans+c[i];
    }
    sort(c+1,c+n+1,comp);
    ans=(int(ans/w))-1;
    while(ans++){
        memset(weigh,0,sizeof(weigh));
        dfs(1);
    }
    return 0;
}

```
-------
你又会发现你 #$9$ Wa 了，那么便可以证明公式有错，所以当我们把 $x/y-1$ 改成 $x/y$ 时

-------
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,w,ans;
long long c[30+10],weigh[30+10];
bool use[30+10];
void work(){
	for(int i=1;i<=n;i++){
		if(weigh[i]>w){
			return ;
		}
	}
	printf("%d\n",ans);
	exit(0);
}
bool comp(int x,int y){
	return x>y;
}
void dfs(int num){
	if(num>n)work();
	for(int i=1;i<=ans;i++){
		if(weigh[i]+c[num]<=w){
			weigh[i]+=c[num];
			dfs(num+1);
			weigh[i]-=c[num];
		}
	} 
} 
int main(){
//	freopen("3052.in","r",stdin);
//	freopen("3052.out","w",stdout);
    scanf("%d %d",&n,&w);
    for(int i=1;i<=n;i++){
    	scanf("%lld",&c[i]);
    	ans=ans+c[i];
	}
	sort(c+1,c+n+1,comp);
	ans=int(ans/w);
	for(;1;){
		memset(weigh,0,sizeof(weigh));
		dfs(1);
		++ans;
	}
	return 0;
}

```
你会发现你经过千辛万苦总算对了，毕竟思考过的东西才是自己的吧

---

## 作者：半仙胡小桃 (赞：0)

##题目描述 ：


给出n个物品，体积为w[i]，现把其分成若干组，要求每组总体积<=W，问最小分组。(n<=18)

##思路：

~~虽然标签是DP，但是很明显搜索可过~~

迭代加深搜索+贪心

首先我们计算出所以东西的总和，最少需要 sum/max\_w个组。

然后迭代加深搜索即可

小剪枝 先排大的物品，在排小的。

搜索0msAC，还是比较强的。

##代码：

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
int n;
ll w[30],wight[30],max_w;
bool dfs(int now,int num)
{
    if(now==n+1) return 1;
    //printf("--%d %d--\n",now,num);
    for(int i=1;i<=num;i++)
    {
        if(w[now]+wight[i]>max_w) continue;
        wight[i]+=w[now];
        if(dfs(now+1,num)) return 1;
        wight[i]-=w[now];
    }
    return 0;
}
bool comp(ll x,ll y)
{
    return x>y;
}
int main()
{
    scanf("%d%lld",&n,&max_w);
    int minx=0;
    ll sum=0;
    for(int i=1;i<=n;i++)
    {
        scanf("%lld",w+i);
        sum+=w[i];
        if(w[i]>=max_w) minx++;
    }
    sort(w+1,w+n+1,comp);
    int p=(int)sum/max_w;
    if(sum%max_w!=0) p++;
    minx=max(minx,p);
    //printf("%d\n",minx);
    for(int i=minx;i<=n;i++)
     if(dfs(1,i)) 
     {
         printf("%d",i);
         break;
     }
    return 0;
}
```


---

