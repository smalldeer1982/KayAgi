# [USACO08NOV] Buying Hay S

## 题目描述

Farmer John is running out of supplies and needs to purchase H (1 <= H <= 50,000) pounds of hay for his cows.

He knows N (1 <= N <= 100) hay suppliers conveniently numbered 1..N. Supplier i sells packages that contain P\_i (1 <= P\_i <= 5,000) pounds of hay at a cost of C\_i (1 <= C\_i <= 5,000) dollars. Each supplier has an unlimited number of packages available, and the packages must be bought whole.

Help FJ by finding the minimum cost necessary to purchase at least H pounds of hay.

约翰的干草库存已经告罄，他打算为奶牛们采购 $H(1 \leq H \leq 50000)$ 磅干草。

他知道 $N(1 \leq N\leq 100)$ 个干草公司，现在用 $1$ 到 $N$ 给它们编号。第 $i$ 公司卖的干草包重量为 $P_i (1 \leq P_i \leq 5,000)$ 磅，需要的开销为 $C_i (1 \leq C_i \leq 5,000)$ 美元。每个干草公司的货源都十分充足， 可以卖出无限多的干草包。

帮助约翰找到最小的开销来满足需要，即采购到至少 $H$ 磅干草。

## 说明/提示

FJ can buy three packages from the second supplier for a total cost of 9.


## 样例 #1

### 输入

```
2 15 
3 2 
5 3 
```

### 输出

```
9 
```

# 题解

## 作者：CCF_zkskyer (赞：346)

## 一、看题
  很明显，这是一道~~USACO~~的原题，所以我们得先看题面，小心被坑（本蒟蒻就被坑了！！！）
  
 广大群众都看出来这是一道完完全全的完全背包，但还是有些不一样，这里不是单一的装入，还要考虑什么什么情况下有特殊情况（下面会说明）
 
## 二、构思
大部分朋友听到这里后就不会做了，这恰好就中了出题人的下怀，其实啊，我们不妨直接按题目中的条件去试试，没准就过了呢（AC的魔力）

这道题的坑在于，当重量大于等于h，小于等于h与价格最大值的和时，最小值都有可能出现，不仅存于重量等于h时！

所以，根据题面所说的，可以看出状态转移方程，其实这道题蛮单纯的

**状态转移方程**如下：

$$f[j]=min(f[j],f[j-weight[i]]+val[i]);$$

即少载i头奶牛再加上载i头奶牛的时间

## 三、AC代码呈现

```cpp
#include <bits/stdc++.h> //万能的头文件 
using namespace std;

const int maxn=55005; // maxn是用来存数组大小的，可以忽视 
const int Max=5000; // Max是考虑有可能买更多的干草包但花费的钱却更小，只需加上单个开销的最大值即可 

int weight[105],val[105]; //weight数组相当于是存这种干草包有多少磅，val数组存这种干草包一袋花费多少钱 
int f[maxn]; //当需要i磅时，最小花费是多少 
int Min=0x3f3f3f3f; //最小值首先赋成无穷大，以免出错 
int n,h; 

int main()
{
    scanf("%d%d",&n,&h);
    
    for (register int i=1;i<=n;i++) //日常卡常 
    {
    	scanf("%d%d",&weight[i],&val[i]);
	}
	
	for (register int i=1;i<=h+Max;i++)
	{
		f[i]=Min; //先把每个赋成无穷大，由此可见，Min一箭双雕 
	}
	
	for(register int i=1;i<=n;i++)
    {
    	for(register int j=weight[i];j<=h+Max;j++) //典型的完全背包 
        {
        	f[j]=min(f[j],f[j-weight[i]]+val[i]); //美丽的状态转移方程！ 
		}
	}
	
	for (register int i=h;i<=h+Max;i++)
	{
		Min=min(Min,f[i]); //在合理范围内找最小花费 
	}
	
	printf("%d",Min);
	return 0;
}


```

## 四、请求
本人是中学生，这是我第三次发题解，请大家多多支持，留下你们宝贵的赞，顶我！！！


---

## 作者：Egg_eating_master (赞：29)

## 本人新奇做法

跟各位的做法都不一样呢

此题各位大佬都是把重量当限制条件，把花费当价值的么

本蒟蒻介绍一下自己的做法，即**把重量当价值，把花费当限制条件**

然后跑完全背包，最大限制开多一点

最后一个循环+判断输出就行了
```
#include<bits/stdc++.h>
using namespace std;
int n,m;
int w[101],val[101];
int dp[100001];//dp[i]表示以i为花费上限能买到的最大重量
int main(){
	cin>>n>>h;
	for(int i=1;i<=n;i++)
	    cin>>val[i]>>w[i];//敲黑板，把重量当价值，把花费当限制条件
	for(int i=1;i<=n;i++)
	    for(int j=w[i];j<=100000;j++)
	        dp[j]=max(dp[j],dp[j-w[i]]+val[i]);//开大限制，跑完全背包
	for(int i=1;i<=100000;i++)
	    if(dp[i]>=h){//如果以i为花费上限，可以买到比h重量多的干草
	    	cout<<i<<endl;//那么i就是答案了
	    	return 0;//拜拜了您嘞
		}
	return 0;//Happy ending~
}
```
话说这题貌似跟[P1510 精卫填海](https://www.luogu.com.cn/problem/P1510)很像欸

---

## 作者：flyfree (赞：21)

看到各位dalao都是+5000，那就让我来介绍一种清奇的思路叭

这题坑点很明显就是“至少”，怎么办呢？我的想法简单粗暴：

完全背包模板题中，f[i]的含义是“**花费为i时能获取的最大的价值**”，放到这题中f[i]就是“**买质量为i的干草花费的最小钱数**”。那么，“至少”怎么办呢？很简单，把f[i]的意义直接改为“买**至少**质量为i的干草花费的最少钱数”。

具体到代码中，就是一般我们在枚举质量j的时候都是直接从第i个公司的干草包重量开始枚举，因为至少要放一个嘛。但这题不一样，由于f[i]的意义变了，我们就可以**从1开始枚举，如果当前枚举的j<当前枚举的第i个公司的干草包重量，那就直接f[j]=min(f[j],c)就好啦。（c意义如题）**

上代码~


```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int m,f[50001],n,p,c;
int main()
{
    scanf("%d %d",&n,&m);
    memset(f,0x3f,sizeof(f));
    for(int i=1;i<=n;i++)
    {
        scanf("%d %d",&p,&c);
        for(int j=1;j<=p;j++)
        f[j]=min(f[j],c);
//由于我没有给f[0]赋0，所以f[p]必须在上面更新。若f[0]==0，则上下无所谓。
        for(int j=p+1;j<=m;j++)
        f[j]=min(f[j],f[j-p]+c);
    }
    printf("%d",f[m]);
    return 0;
}
```


---

## 作者：zybnxy (赞：17)

[题目传送门](https://www.luogu.org/problem/show?pid=P2918#sub)

很明显本题就是一个完全背包，只不过最多变成了最少，完全背包的方程如下:

$f[j]=min(f[j],f[j-c[i]]+w[i]);$

代码如下
```cpp
#include<cstdio>
#define INF 1e9
int main()
{
	for (i=1;i<=55000;i++)f[i]=INF;
    scanf ("%d%d",&n,&v);
    for(i=1;i<=n;i++)cin>>c[i]>>w[i];
    for(i=1;i<=n;i++)
        for(j=c[i];j<=v+5000;j++)
            f[j]=min(f[j],f[j-c[i]]+w[i]);
    for(i=v;i<=v+5000;i++)ans=min(ans,f[i]);
    printf("%d\n",ans);
	return 0;
}

    
```

---

## 作者：Pine (赞：8)

突然发现都用的是往后再开一定的体积然后取最优


其实根本不需要往后开体积


我们可以枚举体积让当前枚举的体积去扩展别的


如果 当前的体积+第i个物品的体积>需要的体积 就可以截取多余的


也就是说 对于≥所需体积的方案我么可以结合到所需体积方案上


这样最终输出答案时就可以直接输出f[h]了


/\* 语言能力不是很强  大佬勿喷 \*/


```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <queue>
#define LL long long
#define Max(x, y) (x >= y ? x : y)
#define Min(x, y) (x <= y ? x : y)
#define F(i, x, y) for(register int i=x; i<=y; i++)
#define R(i, x, y) for(register int i=x; i>=y; i--)
using namespace std;
inline void in(int &x)
{
    static int ch; static bool flag;
    for(flag=false, ch=getchar(); ch<'0'||ch>'9'; ch=getchar()) flag |= ch=='-';
    for(x=0; isdigit(ch); ch=getchar()) x = (x<<1) + (x<<3) + ch - '0';
    x = flag ? -x : x;
}
int n, h, p[105], c[105]; 
int f[50005];
inline int work()
{
    memset(f, 127/3, sizeof(f));
    in(n); in(h); F(i, 1, n) in(p[i]), in(c[i]);
    f[0]=0;
    F(i, 1, n) {
        F(j, 0, h) {
            int k = j+p[i];
            if (k > h) k=h;
            f[k] = Min(f[k], f[j]+c[i]);
        }
    }
    printf("%d\n", f[h]);
    return 0;
}
int TAT = work();
int main() {;}
```

---

## 作者：EarthGiao (赞：7)

## 【思路】
完全背包    
很有意思的一道背包题目    

### 【题目大意】
给你干草重量和花费，每种都是无限买     
买不少于h 镑干草花最少的钱     

### 【题目分析】
很显然是可以用完全背包来做的   
数据范围5000*100完全没有问题    
然后就可以按照完全背包的模板来跑了、   
bb[i]表示i镑干草花的最少的钱    
是可以由i-a[x]的情况推过来的   
（a[x]表示任意一种干草）    
是bb[i-a[x]]+c[x]的最小情况推过来的   
然后发现只有30分    

### 【错误原因】
至少H镑干草这一点很又迷惑性    
会情不自禁忽略掉他    
但其实这才是最重要的一个地方    
至少H那就是可以买比H镑多的干草    
但是比H镑多又有一种限制    
因为一捆干草最多是5000镑    
所以最多不能超过H+5000镑   
**为什么呢？？**     
因为如果超出了5000镑    
那一定有一捆干草是完全多余出来的   
也就是可以拿掉任意一捆干草之后还是满足至少H镑干草的     
因为任意一捆干草都是小于5000镑的    
H加上一个大于等于5000的数之后再减去一个小于等于5000的数     
还是满足至少H镑干草的     
所以多出5000之后的范围那就是没有必要的了     
所以跑完全背包的时候跑H+5000     
然后最后答案也是H-H+5000这个范围内的最小值     
 
## 【完整代码】
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int Max = 55004;
int bb[Max],p[105],c[105];

int main()
{
	int n,h;
	cin >> n >> h;
	memset(bb,999999,sizeof(bb));
	for(register int i = 1;i <= n;++ i)
		cin >> p[i] >> c[i];
	bb[0] = 0;
	for(register int i = 1;i <= n;++ i)
		for(register int j = p[i];j <= h + 5000;++ j)
			bb[j] = min(bb[j],bb[j - p[i]] + c[i]);
	int M = 0x7fffffff;
	for(register int i = h;i <= h + 5000;++ i)
		M = min(M,bb[i]);
	cout << M << endl;
	return 0;
}
```

---

## 作者：Licykoc (赞：4)

这题是个多重背包的裸题，但有一点不同，即：

**多重背包**的$F[j]$代表在不超过$j$磅的干草下，最小的开销

而**本题**的$F[j]$表示用$(\ge F[j])$磅干草的最小开销

这看起来有点麻烦，但其实只需将多重背包的程序稍稍改下即可

```pascal
  for j := 0 to h do //从前往后
    f[min(a[i] + j, h)] := min(f[min(a[i] + j,h)], f[j] + b[i]); 
    //对于每一个F[a[i]+j],都由F[j]推导而来，并且因题目所说，从0循环至h

```

这样本题就愉快AC啦：

```pascal
uses math;
var
  n,h,i,j,a,b:longint;
  f:array[0..500001] of longint;
begin
  read(n,h);
  filldword(f,length(f),maxint);
  f[0]:=0; 
  for i:=1 to n do begin
    read(a,b);
	for j:=0 to h do f[min(j+a,h)]:=min(f[min(j+a,h)],f[j]+b);
  end;
  write(f[h]);
end.

```

---

## 作者：Dr_殇 (赞：3)

#一道完全背包题。

#完全背包是除了01背包之外最简单的动规了，这道题和疯狂的采药很像，不过不一样，而且还有坑。

##注：这里你可以买比所需多的干草，只要达到数量就行了。

#动态转移方程：f[j]=min(f[j],f[j-c[i]]+w[i]);

##注：由于这里是要求花的钱最少，所以用min。


##代码如下：





```cpp
#include <ctime>
#include <cmath>
#include <cstdio>
#include <string>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>//头文件准备
using namespace std;
const int INF=1e9;
int c[105],w[105],f[55005],n,v,ans=INF;
int main(){
    for (int i=1;i<=55000;i++){//初始化，也可以直接写在全局变量里：f[55005]={INF};
        f[i]=INF;
    }
    scanf ("%d %d",&n,&v);
    for (int i=1;i<=n;i++){
        cin>>c[i]>>w[i];//注意：在这题里，干草的价值是重量，所需的英镑才是价值
    }
    for (int i=1;i<=n;i++){
        for (int j=c[i];j<=v+5000;j++){
            f[j]=min(f[j],f[j-c[i]]+w[i]);//动态转移方程
        }
    }
    for (int i=v;i<=v+5000;i++){
        ans=min(ans,f[i]);//穷举最小值，一定要从v开始穷举！
    }
    printf ("%d\n",ans);
    while (1);//反抄袭
    return 0;
}
```
完成！
#其实这题只要理解了就很简单，把干草数量当成重量，把钱当成价值，然后穷举小的就可以了。


#珍爱生命，拒绝抄袭！


---

## 作者：YosemiteHe (赞：1)

本题是在[完全背包](https://www.luogu.com.cn/problem/P1616)的基础上略微改动。

完全背包方程：

$$dp_j = \max(dp_j, dp_{j - a_i} + b_i)$$

而本题要求的是最小值，将 $\max$ 改为 $\min$：

$$dp_j = \min(dp_j, dp_{j - a_i} + b_i)$$

因为买 $h$ 磅时不一定是最优答案，所以内层循环的循环条件为 $j \leq h + 5000$。

**注意：因为是求最小值，所以 $dp$ 数组要初始为最大值。**

Code:
```cpp
#include <iostream>
#include <cstring>
using namespace std;
int n, h, a[105], b[105], dp[100005], ans = 0x3f3f3f;
int main(void) {
    cin >> n >> h;
    for (int i = 1; i <= h + 5000; ++i){
        dp[i] = ans;//初始化 dp 数组
    }
    for (int i = 1; i <= n; ++i) {
    	cin >> a[i] >> b[i];
	}
    for (int i = 1; i <= n; ++i) {
    	for (int j = a[i]; j <= h + 5000; ++j) { //注意循环条件
    		dp[j] = min(dp[j], dp[j - a[i]] + b[i]);
		}
	}
    for (int i = h; i <= h + 5000; ++i) {
    	ans = min(ans, dp[i]);
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：wanyaxin (赞：1)

**思路** 看到这道题，我首先想到了有一道题叫“神奇的四次方数”，其实，这两道题本质上都是一样的。

**解法** 完全背包，把开销C当成价值，然后取最小值。但是，要注意有个地方特别坑
~~让本蒟蒻卡在30分~~，就是题目说“采购到**至少**H镑干草”，那么也就是说，干草的数量可以超过H，那么就应该在H到H+5000之间枚举一下最小值。- 

**代码如下：**
```cpp
#include<bits/stdc++.h>
using namespace std;
int p[120];
int c[120];
int f[55010];
int main()
{
	int n,h,i,j;
	cin>>n>>h;
	for(i=1;i<=n;i++)
	{
		scanf("%d%d",&p[i],&c[i]);
	}
	memset(f,0x7f,sizeof(f));
	f[0]=0;
	for(i=1;i<=n;i++)
	{
		for(j=p[i];j<=h+5005;j++)
		{
			f[j]=min(f[j],f[j-p[i]]+c[i]);
		}
	}
	int ans=f[h];
	for(i=h+1;i<=h+5005;i++)
	{
		ans=min(ans,f[i]);
	}
	cout<<ans;
}
```

---

## 作者：ahawzlc (赞：0)

思路：完全背包

----

这个题就是一个完全背包的板子题，甚至在本校是完全背包的例题。

完全背包用来解决一类背包问题。这种背包问题中物品可以无限次取，求最优方案。一维优化过的完全背包空间复杂度：$O(n)$ 时间复杂度：$O(n^2)$。

完全背包的解决需要两重循环，第一重循环枚举选用的物品，第二重循环枚举当前的背包容量，$dp$ 数组存的是背包容量。转移方程 $dp[j]=\max{dp[j],dp[j-w[i]]+c[i]}$

在本题中，干草可以随便取，每一包干草都有自己的价值和重量，妥妥的完全背包问题。只不过本题中需要求最小值，那么需要将 $dp$ 数组预处理成 $inf$ ， $dp[0]=0$ （没有物品时质量为 0，价值为 0 应当是好理解的QAQ）

本题还有一个特性，这里的背包容量没有上限，所以可能在容量范围内没有最优解，处理的方式是强行将背包容量扩大。具体见代码。

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<stack>
#include<cmath>
#include<queue>
#include<set>
#include<map>
#define int long long
#define re register
#define pi pair<int,int>
#define F first
#define S second
#define mp make_pair
using namespace std;
const int N=100005;
inline int read() {
	int sum=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {
		if(ch=='-') w=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		sum=(sum<<3)+(sum<<1)+ch-'0';
		ch=getchar();
	}
	return sum*w;
}
int w[N],c[N],dp[N];
signed main() {
	int n=read(),m=read(),ans=0x7f7f7f7f;
	memset(dp,0x3f,sizeof dp);
	dp[0]=0;
	for(int i=1;i<=n;i++) w[i]=read(),c[i]=read();
	for(int i=1;i<=n;i++) 
		for(int j=w[i];j<=m+5000;j++) //强行扩大上限 
			dp[j]=min(dp[j],dp[j-w[i]]+c[i]);
	for(int i=m;i<=m+5000;i++) ans=min(ans,dp[i]);
	printf("%lld\n",ans);
	return 0;
}

```

---

## 作者：Sunbread (赞：0)

一样的代码，不一样的理解
```cpp
#include <bits/stdc++.h>

using namespace std;

/*
问题思路：
这道题很多地方都像背包问题，因此我们考虑以背包问题的范式求解
干草总数H对应背包容量
干草包重量P对应单个物品所占容量
干草包开销C对应单个物品价值
可以卖出无限多的干草包对应每个物品可以选无数次
“采购至少H单位干草使开销最小”对应“选择总占容量至少为H的一组物品使总价值最小”
乍一看这不符合背包问题的定义，然而我们可以用如下思路将其转化为背包问题来解
首先求出以H开始的一系列容量下严格装满背包的背包问题的解，然后在这一系列解中择出最优
按照这个思路求解，需要解决的一个问题是这一系列容量以何结束
为了解决这个问题，我们需要知道：给定物品总数，自由选取物品可得的最小价值会随着物品总数的增长而增长
上面的命题非常显然，因为C是正的，无论怎么选取物品对价值的影响都是增大
而当背包容量超过H+Pmax时为了严格装满背包，选定物品显然会比最优解所选物品多出至少一个，最小价值自然增大
基于上述理由，我们只需要求以H开始以H+Pmax结束的一系列容量下的解就可以了
*/

int dp[55005];

int main()
{
    // 读入
    int n, h; cin >> n >> h;
    // 接下来求解一个严格装满背包的求最小价值的无界（完全）背包问题
    memset(dp, 0x3f, sizeof(dp)); // 因为是求最小值我们需要设无效状态为正无穷，与背包九讲中刚好相反
    dp[0] = 0;
    for (int i = 0; i < n; ++i)
    {
        int p, c; cin >> p >> c; // 在线求解
        for (int j = p; j <= h + 5000; ++j) // 单个物品所占最大容量为5000
            dp[j] = min(dp[j], c + dp[j - p]); // 状态转移方程
    }
    // 接下来在得出的一系列最小价值中选出最小的
    int ans = INT_MAX;
    for (int i = h; i <= h + 5000; ++i)
        ans = min(ans, dp[i]);
    // 输出
    cout << ans << endl;
    return 0;
}
```


---

## 作者：Hiraeth (赞：0)

本来以为是模板 

然后很愉快地被虐了…

~~我太菜了~~

最后还是结合题解理解的…

USACO 果真是好题很多啊 老师一直推荐做的 但是鉴于本人太懒emmm

来一下题目哈：

#### 每个干草公司的货源都十分充足， 可以卖出无限多的干草包.

看到这句话应该容易就可以想到是完全背包问题（每种物品可以放无限次数）

再往下看：

#### 帮助约翰找到最小的开销来满足需要，即采购到至少H镑干草.

懵了… 这什么玩意儿啊 我只会求最大值啊啊啊

这种求最小值的我没搞过…

~~还想到改成负数搞一搞的 然后果断放弃了~~

其实状态转移方程还是很好想的

$f[j]=min(f[j],f[j-p[i]]+c[i])$

每种物品取或者不取 然后更新花费最小值 

对于给定的每一堆的质量的花费应该是确定的 其余应该更新为inf  然后dp

代码是这样的：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,p[105],c[105],h,f[500090];
int main(){
    scanf("%d%d",&n,&h);
    memset(f,0x3f3f3f3f,sizeof(f));
    for(int i=1;i<=n;i++) {
        scanf("%d%d",&p[i],&c[i]);
        f[p[i]]=c[i];
    }
    for (int i=1;i<=n;i++)
        for (int j=1;j<=h;j++)
    if (j-p[i]>=0) f[j]=min(f[j],f[j-p[i]]+c[i]);
    printf("%d\n",f[h]);
    return 0;
} 
```

~~[然后只有30分](https://www.luogu.org/recordnew/show/16447611)~~

再来分析一下题目：

#### 帮助约翰找到最小的开销来满足需要，即采购到至少H镑干草.

有两个字 

### 至少.

也就是在保证我们购买物品的数量足够的情况下 总购买量是可以溢出的 要求的是最小的开销 

所以关键在于开销最小 买的东西多一点点是无所谓滴~

所以第二重循环的结束点不应该在h 而应该在h+5000 因为每一堆干草的最大数目是5000 

你卖的再多总不可能再多买一堆吧…

然后最后再有$f[h]$开始至$f[h+5000]$更新最小值 最后的ans即为所求答案

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,p[105],c[105],h,ans=0x3f3f3f3f,f[500090];
int main(){
    scanf("%d%d",&n,&h);
    memset(f,0x3f3f3f3f,sizeof(f));
    for(int i=1;i<=n;i++) {
        scanf("%d%d",&p[i],&c[i]);
        f[p[i]]=c[i];
    }
    for (int i=1;i<=n;i++)
        for (int j=1;j<=h+5000;j++)
    if (j-p[i]>=0) f[j]=min(f[j],f[j-p[i]]+c[i]);
   	for (int j=h;j<=h+5000;j++) ans=min(ans,f[j]);
   	printf("%d\n",ans);
    return 0;
} 
```



---

## 作者：3269224138刘 (赞：0)

只需要将每一个公司可以买得干草数量枚举一遍,如果在这个公司买的价格比原来小就换过来,因为可能买比H多的干草花费的钱比买H的干草花费的钱更少,所以把购买的数量算到2倍购买的干草,最后再取最小数就行了.(H是输入的需要购买的干草的数量）


```cpp
uses math;
var
  n,m,ans,i,j,v:Longint;
  f:array[-12..100012] of Longint;
  w,cost:array[-12..50012] of Longint;
begin
  readln(n,v);
  for i:=1 to n do
    readln(w[i],cost[i]);
  fillchar(f,sizeof(f),$7f);
  f[0]:=0;
  for i:=1 to n do
    for j:=w[i] to v*2 do
      f[j]:=min(f[j],f[j-w[i]]+cost[i]);
  ans:=maxLongint;
  for i:=v to v*2 do
    ans:=min(ans,f[i]);
  writeln(ans);
end.
```

---

## 作者：QwQ2000 (赞：0)

完全背包裸题 不是很清楚这道题为什么没有人做又难度评价很高

完全背包算是最基础的问题了吧 没什么好说的 看代码就好

这个题需要注意的一个问题就是买到的干草可以多于h

所以算的时候体积的最大范围不是h而是h+p

[codec]





```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
const int N=100,H=50000,P=5000,INF=1e9;
int n=0,h=0;
int c[N+5],w[N+5],f[H+P+5];
int main(void) {
    for (int i=1;i<=H+P;++i)
        f[i]=INF;
    scanf("%d %d",&n,&h);
    for (int i=1;i<=n;++i)
        scanf("%d %d",c+i,w+i);
    for (int i=1;i<=n;++i)
        for (int v=c[i];v<=h+P;++v)
            f[v]=min(f[v],f[v-c[i]]+w[i]);
    int ans=INF;
    for (int i=h;i<=h+P;++i)
        ans=min(ans,f[i]);
    printf("%d\n",ans);
    return 0;
}
[/codec]
```

---

