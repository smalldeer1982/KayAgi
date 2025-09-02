# [USACO06FEB] Treats for the Cows G/S

## 题目描述

约翰经常给产奶量高的奶牛发特殊津贴，于是很快奶牛们拥有了大笔不知该怎么花的钱。为此，约翰购置了 $N$（$1 \leq N \leq 2000$） 份美味的零食来卖给奶牛们。每天约翰售出一份零食。当然约翰希望这些零食全部售出后能得到最大的收益，这些零食有以下这些有趣的特性：
+ 零食按照 $1, \ldots, N$ 编号，它们被排成一列放在一个很长的盒子里。盒子的两端都有开口，约翰每天可以从盒子的任一端取出最外面的一个。
+ 与美酒与好吃的奶酪相似，这些零食储存得越久就越好吃。当然，这样约翰就可以把它们卖出更高的价钱。
+ 每份零食的初始价值不一定相同。约翰进货时，第i份零食的初始价值为 $V_i$（$1 \leq V \leq 1000$）。
+ 第 $i$ 份零食如果在被买进后的第 $a$ 天出售，则它的售价是 $V_i \times a$。

$V_i$ 的是从盒子顶端往下的第 $i$ 份零食的初始价值。约翰告诉了你所有零食的初始价值，并希望你能帮他计算一下，在这些零食全被卖出后，他最多能得到多少钱。

## 说明/提示

样例的最优解是：按 $1 \to 5 \to 2 \to 3 \to 4$ 的顺序卖零食，得到的钱数是 $1 \times 1 + 2 \times 2 + 3 \times 3 + 4 \times 1 + 5 \times 5 = 43$。

## 样例 #1

### 输入

```
5
1
3
1
5
2```

### 输出

```
43```

# 题解

## 作者：xun薰 (赞：305)

区间dp

1、
普通的搜索54分。

每一次的抉择是取当前区间的左边还是右边，搜索的边界条件是取到最后只剩下一个元素

代码:




```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,ans,v[2020];
void dfs(int ste,int l,int r,int sum){
    if(l==r){
        ans=max(ans,sum+v[l]*ste);
        return;
    }
    dfs(ste+1,l+1,r,sum+ste*v[l]);
    dfs(ste+1,l,r-1,sum+ste*v[r]);
}
int main(){
    scanf("%d",&n);ans=0;
    for(int i=1;i<=n;i++)scanf("%d",&v[i]);
    dfs(1,1,n,0);
    cout<<ans<<endl;
    return 0;
}
```
2、记忆化搜索
我们发现之前取的抉择可能不完全一样，但是现在面临同样的状态，那么我们就不需要搜索

多遍，开一个f[l][r]数组，表示区间[l,r]能提供的最大价值，边界条件为取完时，即数列为空时。

代码：




```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,ans,v[2020],f[2020][2020];
int dfs(int ste,int l,int r){
    if(r<l)return 0;
    if(f[l][r])return f[l][r];
    f[l][r]=max(dfs(ste+1,l+1,r)+ste*v[l],dfs(ste+1,l,r-1)+ste*v[r]);
    return f[l][r];
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&v[i]);
    dfs(1,1,n);
    printf("%d",f[1][n]);
    return 0;
}
```
3、记忆化搜索中我们已经看出dp转移方程了。
第一层循环枚举区间长度，第二层循环枚举左端点。

代码：


```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int n,f[2017][2017],v[2017];
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&v[i]);
    for(int i=1;i<=n;i++)f[i][i]=v[i]*n;//一开始初始化忘记乘以n 
    for(int i=2;i<=n;i++){
        for(int l=1;l<=n;l++){
            int r=l+i-1;
            if(r>n)break;
            f[l][r]=max(f[l][r-1]+v[r]*(n-i+1),f[l+1][r]+v[l]*(n-i+1));
        }
    }
    printf("%d\n",f[1][n]);
    return 0;
}
```
这篇题解希望能帮助到区间dp入门的同学。

---

## 作者：big_news (赞：146)

# 我来说明一下这个题为什么不能直接贪


~~其实对于很多julao来说这是很明显的事，但是我太蒻了，所以觉得有必要说一下~~

先看一组数据
```
6
9 9 9 1 1 10
```
因为题目没告诉你$v_i$都不重复，所以你完全可以这么造出一个毒瘤测试点

然后我们来分析一下裸的贪心：

$$ sum=9*1+9*2+9*3+1*4+1*5+10*6=123 $$

但是对于这组数据，最优解是：

$$ sum=10*1+1*2+1*3+9*4+9*5+9*6=150 $$

也就是说贪心找到的解不是最优解，进一步说就是**当前的决策可能会影响后面的一些决策**，如果被影响的决策是最优解的一部分，那么你就错了。

所以老老实实写 $ \text{区间DP} $ 吧！

---

## 作者：Kdlyh (赞：94)

由题意可知每次只能取两端的零食。这就可以看出来这是一道区间DP题。

我设计出了一个状态 :

- $f[l][r]$	表示$[l,r]$这个区间最多能得到的钱。

  - 当时我就自以为是的推出了转移方程:
    - $f[l][r]=max(f[l+1][r]+a[l]*(r-l+1),f[l][r-1]+a[r]*(r-l+1))$
    - 这个非常好理解(事先说一句这是错的)，$[l,r]$这个区间的最大值可以由$[l+1,r]$这个区间的最大值或$[l,r-1]$这个区间转移而来。
      但是这个方程有一个明显的问题:拿该题的样例来说,$f[1][5]$是由$1,5,2,3,4$这个顺序得到的。而按照上面的转移方程的话，它只能由$f[1][4]$和$f[2][5]$转移而来，**且这个转移默认了新加上去的那个数是最后一个。**而$f[1][4]$的最大值是由$1,2,3,4$这个顺序得来的，用我这个方程转移的话$f[1][5]$的顺序为$1,2,3,4,5$,$f[2][5]$的最大值是由$5,2,3,4$这个顺序的来的，而用了我这个方程转移后$f[1][5]$的顺序为$5,2,3,4,1$。都没法的出正确的答案，而且可以看到由$f[2][5]$转移后的到的那个顺序还是错的！这一切的错误都得归咎与**且这个转移默认了新加上去的那个数是最后一个。**这个性质。我们可以发现**无论是$a[l]$还是$a[r]$再转移后的顺序中都显然应该是第一个**。
    - **那我们将转移方程修改成默认新加上去的这个数是第一个不就行了吗？**

  - 通过上面一番推导的出的思路，我们继续设计转移方程:

    - **既然新加上去的数默认是第一个，转移时原来的区间的值得被修改。**我们继续那上面那个例子原来$f[2][5]$的顺序是$5,2,3,4$，$f[2][5]$值则是由$a[5]+a[2]*2+a[3]*3+a[4]*4$这样得出的。而转移成$f[1][5]$后，因为默认新加上去的数是第一个。所以$f[1][5]$的顺序是$1,5,2,3,4$。而此时$f[1][5]$的值则是由$a[1]+a[5]*2+a[2]*3+a[3]*4+a[4]*5$的出的。很明显原来的$f[2][5]$和现在$f[1][5]$的算式是有关联的。我们用求$f[1][5]$的值的算式减去求$f[2][5]$的值的算式可得

      $(a[1]+a[5]*2+a[2]*3+a[3]*4+a[4]*5)-(a[5]+a[2]*2+a[3]*3+a[4]*4)$

      $=a[1]+a[5]+a[2]+a[3]+a[4]$

    ​    $=a[1]+\sum_{i=1}^4a_i$

    很明显这个$\sum_{i=1}^4a_i$我们可以通过前缀和预处理得到。

    那么我们就得到了新的转移方程:

    ​	$f[i][j]=max(f[l+1][r]+(s[r]-s[l])+a[l],f[l][r-1]+(s[r-1]-s[l-1])+a[r])$ 

    ​	$s[i]=\sum_{j=1}^ia_j$

    这样一来就可以愉快地$CODE$了

$AC$代码 记忆化搜索实现

```cpp
#include <cstdio>

#define re register
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))

const int N = 2e3+10;

int n;
int a[N];
int f[N][N];
int s[N];

int dfs(int l,int r) {
	if(f[l][r]) {
		return f[l][r];
	}
	f[l][r]=max(dfs(l+1,r)+(s[r]-s[l])+a[l],dfs(l,r-1)+(s[r-1]-s[l-1])+a[r]);
	return f[l][r];
}

void Input() {
	scanf("%d",&n);
	for(re int i=1; i<=n; ++i) {
		scanf("%d",&a[i]);
		f[i][i]=a[i];
		s[i]=s[i-1]+a[i];
	} 
}

void Solve() {
	printf("%d",dfs(1,n)); 
}

int main(void) {
	Input();
	Solve();
	return 0;
}
```

码字挺累的，望过审。

---

## 作者：Lance1ot (赞：62)

这个题只有左、右端各取元素的个数会对最终结果产生影响，所以将他俩作为状态就可以了。

dp[i][j]表示已经取了i个数，左边取了j个数的最优解。（右边取得个数变可以利用i，j推出来）（受P1004启发，其实并没有什么卵用）

l=i-j；

dp[i][j]=max(dp[i-1][j]【就是左边取j个，右边取i-1-j个】+in[n-l+1]*i【这次取右边右边，后边的就是相反了】,dp[i-1][j-1]+in[j]*i)

真的好暴力呀，真的能叫dp吗？
```
#include<iostream>
using namespace std;
int dp[2010][2010];//dp数组
int in[2010];//输入数组
int main() 
{
	cin.sync_with_stdio(false);//玄学优化
	int n;
	cin>>n;
	for(register int i=1;i<=n;i++)
		cin>>in[i];//数据读入
	for(register int i=1;i<=n;i++)
		for(register int j=0;j<=i;j++)
		{
			register int l=i-j;//推出右边取了多少个
			dp[i][j]=max(dp[i-1][j]+in[n-l+1]*i,dp[i-1][j-1]+in[j]*i);//状态转移
            //n-l+1就是从右边数第l个在in数组中的下标
		}
	int ans=0;
	for(register int i=1;i<=n;i++)
		ans=max(ans,dp[n][i]);//从最终状态中取一个最大值
	cout<<ans;
}
```

---

## 作者：__Watcher (赞：38)

update 2020.1.6 修复BUG & 修改版面

### 方法核心：DP
此题最重要的就是找到dp的状态转移方程。对于某些大佬来说这并不是什么难事，可是只要经过一定量的练习后，这道题可能就显得没有这么难了~~（对于某些大佬来说，这题本身就不难）~~


首先回顾合并果子。那题的状态定义为：$f_{i,j}$ 表示将这堆果子堆在i~j的闭区间内的最大得分。

此题可以效仿。同样f[i][j]表示只剩下i~j的闭区间内的零食是赚到的最多的钱。

接下来是状态转移方程。不难发现，$f_{i,j}$ 的上一个状态是 $f_{i-1,j}$ 或$f_{i,j+1}$ ，这样状态转移方程就写好了：
```cpp
f[i][j]=max(f[i-1][j]+v[i-1]*a,f[i][j+1]+v[j+1]*a);
```
其中，$a$ 表示零食在被买进后的第a天出售，表达式 `a=n-(j-i+1)`。

分析到这里，这道题基本大功告成了。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,f[2010][2010],v[2010];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>v[i];
	}
	for(int i=1;i<=n;i++){
		for(int j=n;j>=i;j--){
			int a=n-(j-i+1);
			f[i][j]=max(f[i-1][j]+v[i-1]*a,f[i][j+1]+v[j+1]*a);//转移
		}
	}
	int maxn=0;
	for(int i=1;i<=n;i++){
		maxn=max(maxn,f[i][i]+v[i]*n);//记得把最后的卖出去
	} 
	cout<<maxn;
}

```

总结：  

这题是一道区间 dp 的好题，建议当做模板题练练，熟悉以处理区间端点作为下标的 dp 类型，再回过头看这一题就显而易见了。



---

## 作者：moongazer (赞：33)

这是一到区间DP,很多初学者会枚举区间开头和结尾来DP,但这是错的,应当先枚举区间长度,再枚举区间的开头,然后可以直接推出区间的结尾。

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<iomanip>
#include<algorithm>
#include<fstream>
using namespace std;
int dp[2005][2005],a[2005];
int main(){
    int n,l,i,j;
    cin>>n;
    for(i=1;i<=n;i++){
        cin>>a[i];
        dp[i][i]=a[i]*n;//初始化:将区间长度为1的情况赋值为最后一个拿(n*a[i])
    }
    for(l=2;l<=n;l++){//枚举长度
        for(i=1;(i+l-1)<=n;i++){//枚举开头点,注意范围(开头点加长度减一不超过总长度)
            j=i+l-1;//推出结束点
            dp[i][j]=max(dp[i+1][j]+a[i]*(n-l+1),dp[i][j-1]+a[j]*(n-l+1));//有两种情况一种是选开头点的那一个最优,一种是选结束点的那一个最优
        }
    }
    cout<<dp[1][n]<<endl;//最后直接输出从开头到末尾的最大值
    return 0;
}
```

---

## 作者：YoungLove (赞：30)

[Youngsc](http://youngscc.github.io/)

裸裸的区间DP。

我们定义$f[i][j]$为卖掉$i$到$j$之间的临时得到的最大收益。

另外对与临时的价格我们做一个前缀和。

转移方程就应该是$f[i][j]=max(f[i][j-1],f[i+1][j])+dis[j]-dis[i-1]$貌似跟楼下的不是很一样。

这是什么意思呢

既然是买点$i$到$j$之间的，那么这一天卖掉的一定是$i$或$j$，同时因为多了一天，所以我之前卖的应该滞后一天卖，也就是说每一个物品再增加一个单价，同时加上我现在卖出去的$i$或$j$，去一个较大值就可以了。


## 代码在这里。

```cpp
# include <algorithm>
# include <iostream>
# include <cstring>
# include <cstdio>
# include <queue>
# include <cmath>
# define R register
# define LL long long

using namespace std;

int n,m,f[2010][2010],dis[2010],a[2010];

inline void in(R int &a){
    R char c = getchar();R int x=0,f=1;
    while(!isdigit(c)){if(c == '-') f=-1; c=getchar();}
    while(isdigit(c)) x = (x<<1)+(x<<3)+c-'0',c = getchar();
    a = x*f;
}

inline int yg(){
    in(n);
    for(R int i=1; i<=n; ++i) in(a[i]),dis[i]=a[i]+dis[i-1];
    for(R int i=n; i>=1; --i)
        for(R int j=i; j<=n; ++j)
            f[i][j]=max(f[i][j-1],f[i+1][j])+dis[j]-dis[i-1];
    printf("%d",f[1][n]);
    return 0;
}

int youngsc = yg();
int main(){;}
```
（减少代码复制，共创美好洛谷）


---

## 作者：Lucaster_ (赞：12)

[题目传送门](https://www.luogu.org/problemnew/show/P2858)

```cpp
#include<cstdio>
#include<iostream>
#define N 2002
using namespace std;
int i,j,k,n,len,a[N],f[N][N];
int main()
{
	scanf("%d",&n);
	for(i=1;i<=n;i++) scanf("%d",&a[i]);
	for(i=1;i<=n;i++) f[i][i]=a[i]*n;
	for(len=1;len<n;len++)
	 for(i=1;i+len<=n;i++)
	 {
	 	j=i+len;
	 	k=n-len;
	 	f[i][j]=max(f[i+1][j]+a[i]*k,f[i][j-1]+a[j]*k);
	 }
	printf("%d",f[1][n]);
	return 0;
}
```

```latex
这道题非常不错的
一开始想开个三维数组f[i][j][k]表示i到j区间已经取完并且当前取到了第k个（用于计算权值）
2000^3，会M掉的

深思熟虑
想不出来换题吧

才怪
似乎不需要第三维啊
中间i到j这段区间一定是连续的（由题可得）
所以用n-已经取过的区间长度就是当前取得第几个
```

又因为这是一道区间dp
连续的区间

开两层循环控制开头结尾，直接去dp就好

```cpp
核心部分：
for(len=1;len<n;len++)
 for(i=1;i+len<=n;i++)
 {
	j=i+len;
	k=n-len;
	f[i][j]=max(f[i+1][j]+a[i]*k,f[i][j-1]+a[j]*k);
 }
```
k就是我刚才说的，用总数－区间长度，就是当前取到了第几个

用k*a[i or j]就是本次的价值

每次不是从开头取就是结尾

开头取的价值：f[i+1][j]+a[i]*k;

结尾取的价值：f[i][j-1]+a[j]*k;

dp一下就好了

等等还没结束

注意这里：

for(i=1;i<=n;i++) f[i][i]=a[i]*n;

不加这个还真过不了

为啥嘞？

```latex
因为当你取到最后一个的时候，区间起点等于重点，且当前是最后一个取的，即第n个
所以f[i][i]就等于a[i]*n

大家都能看懂吧
```

完结撒花[~~~]

To管理大大：楼上大佬们都没有讲转移方程的原理，希望通过我这篇题解让更多人看到转移方程的原理

---

## 作者：混沌 (赞：8)

看了一下和楼下做的好像不同

这里的dp[i][j]表示的是 还剩下区间[i,j]中没卖出 时已赚钱的最大值。




```cpp
#include<cstdio>
#include<algorithm>
#include<iostream>
using namespace std;
int n;
int v[2100];
int dp[2100][2100];
int main(){
    //freopen("A.in","r",stdin);
    //freopen("A.out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&v[i]);//记录价值
    dp[1][n]=0;//初始时什么都没卖出 所以是0
    for(int i=n-1;i>=0;i--){//枚举区间长度
        for(int j=1;j+i<=n;j++){//枚举左端点
            int g=j+i;//右端点
            dp[j][g]=max(dp[j-1][g]+v[j-1]*(n-g+j-1),dp[j][g+1]+v[g+1]*(n-g+j-1));//区间[i,j]是由区间[i-1,j]或区间[i,j+1]转移来的，切记dp[i][j]是未售出的区间。
        }
    }
    for(int i=1;i<=n;i++) dp[i][i]+=n*v[i];//dp[i][i]表示除i以外的物品都售出了 最后售出i 所以加上v[i]*n
    int ans=0;
    for(int i=1;i<=n;i++) ans=max(ans,dp[i][i]);//比较出最大值
    printf("%d",ans);
    return 0;
}
```

---

## 作者：李若谷 (赞：5)

**看来看题解，基本上是区间DP的，我来发一个不是区间DP的~~（我太蒻推不出区间DP）~~**

dp(l,r)表示取l次左边的，r次右边的。

那么，天数就是l+r。

我们可以发现dp(l,r)能从dp(l-1,r)和dp(l,r-1)来
从(l-1,r)来就是说当前这一天选的是第l件，dp(l,r-1)同理，也就是第n-r+1件。


代码：

```cpp
#include <iostream>
using namespace std;
int a[2001];
int maxx = -1;
int n;
int dp[2001][2001];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	dp[0][0] = 0;
	for(int i=1;i<=n;i++)
	{
		dp[0][i] = i*a[n-i+1] + dp[0][i-1];  //初始化
		dp[i][0] = i*a[i] + dp[i-1][0];
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n-i;j++)
		{
			dp[i][j] = max(dp[i-1][j] + (i+j)*a[i],dp[i][j-1]+(i+j)*a[n-j+1]);
			maxx = max(maxx,dp[i][j]);  //因为这个dp是取l件左边的，r件右边的，所以不止一个终止的状态。只要l+r = n 就代表取完了所有的了，所以每一次要记录最大的。
		}
	}
	cout<<maxx<<endl;
	return 0;
}
```


---

## 作者：EarthGiao (赞：4)

## 【思路】
区间DP     
### 【题目大意】   
每次都从左端点或者右端点选择一个零食    
获得的价值是这个零食的价值乘以是第几个选择的     

### 【核心思路】 
可以设置一个状态f(i,j)      
表示选取了i个零食，在左边选取了j个      
这个状态可以由前面选取了i - 1个零食    
在左边选取j个零食或者在左边选取了j-1个零食
意思就是：     
之前选取了i-1个零食    
现在选取的第i个零食    
分别在左边选的还是在右边选的情况转移过来     

### 【DP方程式】
$$f[i][j] = max(f[i - 1][j] + a[n - i + 1 + j] * i,f[i - 1][j - 1] + a[j] * i)$$      

## 【完整代码】
```cpp
#include<iostream>
#include<cstdio>

using namespace std;
const int Max = 2005;
int a[Max];
int f[Max][Max];

int main()
{
	int n;
	cin >> n;
	for(register int i = 1;i <= n;++ i)
		cin >> a[i];
	for(register int i = 1;i <= n;++ i)
		for(register int j = 0;j <= i;++ j)
			f[i][j] = max(f[i - 1][j] + a[n - i + 1 + j] * i,f[i - 1][j - 1] + a[j] * i);
	int M = 0;
	for(register int i = 0;i <= n;++ i)
		M = max(M,f[n][i]);
	cout << M << endl;
	return 0; 
}
```

---

## 作者：ez_lcw (赞：3)

# 神奇的dp

这是一道很典型的区间dp题。

具体思路如下：

**我们用$dp[i][j]$来表示从第i份零食到第j份零食所能获得的最大钱数。**

**那么不难想到，假设我们现在要求$dp[i][j]$，那么我们就考虑第一天从最左边开始取，还是从最右边开始取。若从最左边开始取，则获得的钱数为**

**$money[i]$（最左边零食的价值）+**

**$dp[i+1][j]$（除去最左边外能取得的最大值）+**

**$sum[i+1][j]$（因为取最左边的是第一天，所以取$i+1$~$j$时都要推迟一天，那么获得的总价值就要加上从$i+1$加到$j$的一天能获得的钱数）**

那么状态转移方程就显而易见了：

$$dp[i][i+len]=max(dp[i][i]+dp[i+1][i+len]+(sum[i+len]-sum[i]),dp[i+len][i+len]+dp[i][i+len-1]+(sum[i+len-1]-sum[i-1]));$$

其中，$sum$是用前缀和实现的。

具体代码如下：
```cpp
#include<cstdio>
#include<iostream>

#define N 2001

using namespace std;

int n,sum[N],dp[N][N];

int main()
{
	scanf("%d",&n);
	for(int i=1; i<=n; i++)
	{
		scanf("%d",&dp[i][i]);//dp[i][i]就是这个位置的零食
		sum[i]=sum[i-1]+dp[i][i];//前缀和
	}
	for(int len=1; len<=n; len++)
	{
		for(int i=1; i+len<=n; i++)
		{
			dp[i][i+len]=max(dp[i][i]+dp[i+1][i+len]+(sum[i+len]-sum[i]),dp[i+len][i+len]+dp[i][i+len-1]+(sum[i+len-1]-sum[i-1]));//状态转移方程
		}
	}
	printf("%d\n",dp[1][n]);//输出从1到n能获取的最多的钱数
	return 0;
}
```

---

## 作者：Mint_Flipped (赞：3)

我来分析下这题为什么是用区间DP，而不是贪心，并且怎么区间DP。

一眼看题以为是贪心，但这一题如果用贪心，我们要先考虑一个问题：你这一步是最优决策，但是你能保证你下一步甚至下下一步一定也是最优决策吗？

所以这道题不是贪心，应该用区间DP。

那么区间DP怎么写？

先来分析下样例：5 1 3 1 5 2 和题目所给的分析：1x1 + 2x2 + 3x3 + 4x1 + 5x5 = 43 ，n = 5 ,每个值分别用了1 2 3 4 5 次，即拿了1 2 3 4 5次。

写这个题的区间DP，我们又要回到前面的贪心，即最优决策，且我们每次都要取最优决策，我不知道什么时候是最优决策，所以用DP来处理，1次到5次逐渐往上推。

比如 :
x1是决策1，ans=x1，x1用了1次，x2是决策2，ans+=x1+x2，x1用了2次，x2用了一次............完美实现了目标。

代码如下：
```cpp
#include <bits/stdc++.h>
#define ll long long
#define mem(a,b) memset(a,b,sizeof(a))
#define fo1(a,b) for(int a=0;a<b;++a)
#define fo2(a,b) for(int a=1;a<=b;++a)
#define inf 0x3f3f3f3f
using namespace std;
const int maxn=2e3+5;
const int mod=1e9+7;
int a[maxn],b[maxn],f[maxn][maxn];
int main()
{
    int n;
    cin>>n;
    fo2(i,n){
        scanf("%d",&a[i]);
        b[i]=b[i-1]+a[i]; 
    }
    for(int i=n;i>=1;--i){ //倒序逐渐扩大范围，即1到n
        for(int j=i;j<=n;++j)
            f[i][j]=max(f[i][j-1],f[i+1][j])+b[j]-b[i-1];
    }
    printf("%d\n",f[1][n]);
    return 0;
}
```


---

## 作者：maorui_cow (赞：3)

两种方法

1.dp

以dp[i][j]为左边用到第i个，右边用到第j个，所得到的钱。

显然，dp过程为

```
for(int i=1;i<=n;i++)
{
	for(int j=n;j>=i;j--)
	{
		int d=(i-1+n-j);
		dp[i][j]=max(dp[i-1][j]+a[i-1]*d,dp[i][j+1]+a[j+1]*d);
	}
}
```

(其中d为已过天数，a数组为输入数组）

但是到最后，会推到i==j

但是还少算了一个数，即a[i]

所以特判一下


```
if(i==j)
{
	ans=max(ans,dp[i][j]+a[i]*n);
}
```
至此结束



2.记忆化搜索

设置函数fun(i,j)，表示剩余i到j可以卖的钱。

添加一个dp数组，做记忆化。

```
int fun(int i,int j)
{
	if (i>j) return 0;
	if (i==j) 
	{
	//	printf("%d %d %d\n",i,j,a[i]*n);
		return a[i]*n;
	}
	int d=(i+n-j);
	int ans1,ans2;
	if(dp[i+1][j])
	{
		ans1=dp[i+1][j]+a[i]*d;
	}
	else
	{
		ans1=fun(i+1,j)+a[i]*d;
		//dp[i+1][j]=ans1;
	}
	if(dp[i][j-1])
	{
		ans2=dp[i][j-1]+a[j]*d;
	}
	else{
		ans2=fun(i,j-1)+a[j]*d;
		//dp[i][j-1]=ans2;
	}
	int ans = max(ans1,ans2);
	if(i==j)
	{
		ans+=a[i]*n;
	}
	dp[i][j]=ans;
	//	printf("%d %d %d\n",i,j,ans);
	return ans;
		
}
```

至此结束


---

## 作者：封禁用户 (赞：3)

### 穿着衣服的DP
``` pascal
var
  n,ij,j:longint;//ij代表i+j。
  a:array[-1..2005] of longint;
  f:array[-1..2005,-1..2005] of longint;//f[i,j]为约翰第i+j天卖掉从上面拿i个，从下面拿j个最多拿到的钱。
function max(a,b:longint):longint;begin if a>b then exit(a) else exit(b);end;
began//故意改一下，防止抄袭
  readln(n);
  for ij:=1 to n do
    readln(a[ij]);
  for ij:=0 to n do
    for j:=0 to ij do
      f[ij-j,j]:=max(f[ij-j-1,j]+ij*a[ij-j],f[ij-j,j-1]+ij*a[n-j+1]);
  j:=0;
  for ij:=0 to n do
    j:=max(j,f[ij,n-ij]);
  writeln(j);
end.
```
[AC记录](https://www.luogu.org/record/show?rid=7995613)
可以申请转C++，需要10个赞

---

## 作者：lvyijia44 (赞：2)

作为一只刚入门的萌新,只好挑了个区间DP第一页最简单的那个了

首先看到题目，我们知道，我们每天都选一个，而且只在两个端点处取，那我们可以用一个day表示第几天，用lef和rig表示左右端点取到第几个了，那么dp[day][lef][rig]就可以表示第几天，左端点取到第lef个，右端点取到第rig个的最大价值。

BUT，这样铁定MLE

怎么解决呢？

我们发现因为每天都选一个，所以lef+rig=day，我们就可以去掉一维，然后我把rig去了(QWQ)

完整代码如下
```
#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;
const int maxn=1e4+5;
int n,v[maxn],dp[maxn][maxn];//第i天 从左边拿j个
inline int read(){//普通而且没啥卵用的快读
    int ans=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9'){
        if(ch=='-')f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9'){
        ans=(ans<<3)+(ans<<1)+ch-'0';
        ch=getchar();
    }
    return ans*f;
}
int main(){
    n=read();
    for(int i=1;i<=n;i++)
        v[i]=read();
    //初始化
    
    for(int day=1;day<=n;day++)
        for(int lef=0;lef<=day;lef++)
            dp[day][lef]=max(
            dp[day-1][lef]+v[n-day+lef+1]*day,
            (lef) ? dp[day-1][lef-1]+v[lef]*day : v[lef]*day);
            //注意lef=0时要特判，其实我也不知道需不需要，为了保险
    int maxv=0;
    for(int lef=0;lef<=n;lef++)
        maxv=max(maxv,dp[n][lef]);
    printf("%d",maxv);
    return 0;
}
```

A了怎么了，我还可以更优

突然想起01背包优化，感觉很像，尝试写了写，居然A了

双手奉上AC代码
```
#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;
const int maxn=1e4+5;
int n,v[maxn],dp[maxn];//第i天 从左边拿j个
inline int read(){
    int ans=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9'){
        if(ch=='-')f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9'){
        ans=(ans<<3)+(ans<<1)+ch-'0';
        ch=getchar();
    }
    return ans*f;
}
int main(){
    n=read();
    for(int i=1;i<=n;i++)
        v[i]=read();
    for(int day=1;day<=n;day++)
        for(int lef=day;lef>=0;lef--)
            dp[lef]=max(dp[lef]+v[n-day+lef+1]*day,(lef) ? dp[lef-1]+v[lef]*day : v[lef]*day);
    int maxv=0;
    for(int lef=0;lef<=n;lef++)
        maxv=max(maxv,dp[lef]);
    printf("%d",maxv);
    return 0;
}
```


---

## 作者：innocent__ (赞：2)

看了看dp的比较多，就写下搜索吧。~~dp不会~~  
其实搜索得分很容易，搜一下先拿左边的，再搜一下右边，用l表示左边的位置，r表示右边的位置，dep表示层数（也就是时间） ~~别问我为啥不打全拼，本人懒~~ ，在搜到底时更新数据，看看能不能得到更多的 MONEY 
### 注意，
当left==right时，还有一份零食，不能直接判断，还有再搜下去  
所以可以得到
```
void dfs(int l,int r,int mo,int dep)
{
	if(l>r)
	{
		ans=max(mo,ans);
		return ;
	}
	dfs(l+1,r,mo+dep*a[l],dep+1);
	dfs(l,r-1,mo+dep*a[r],dep+1);
}
```
一段代码；  

但肯定不行，有2000个数据，若这样，2^2000 ~~多大自己算去~~ ，不炸才怪；所以一般的搜索肯定是不行的，要用
## 记忆化
用 f 数组来进行记忆化，f【left】【right】表示当剩下的下标为 left-right 时最多可买的钱；
很显然，当剩下标为 left-right 时有两种可能   
1.从左边拿走一块   
2.从右边拿走一块
所以可得到      
f【left】【right】= max（f【left-1】【right】+dep*v【left-1】，f【left】【right+1】+dep *v【right+1】）
有了这个，整个程序就很简单了  
搜索便是
```
int dfs(int l,int r,int dep)
{
    if(f[l][r])return f[l][r];
    if(r<l)return 0;
    f[l][r]=max(dfs(l+1,r,dep+1)+dep*a[l],dfs(l,r-1,dep+1)+dep*a[r]);
    return f[l][r];
}
```
这么一段代码，有了它，动态转移方程也可以推出来了
 ~~好吧，我会dp~~  
主程序应该也很简单了，dp也可以试下
### 谢谢
~~溜~~



---

## 作者：cqsbz_rwb (赞：2)

#          区间DP
### 化简题意
####  一个数列，可以取最前面的数或者最后面的数，取的代价为vi*第几个取的
### 转移
#### 每次取一个数次无非两种可能，取最前面的或者取最后面的。
### 实现
#### dp（i，j）代表取i个时，上面的取了j个。
#### 如果取的上面的，则dp（i，j）=dp（i-1，j-1）+代价。
#### 如果取的下面的，则
#### dp（i，j）=dp（i-1，j）+代价
## 代码
```c++
#include<bits/stdc++.h>
using namespace std;
const int N=2006,inf=1e9;
int ans,n;
int arr[N],dp[N][N];//取i个时，上面取j个，下面取n-j个 
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	  scanf("%d",&arr[i]);
	for(int len=1;len<=n;len++)//最开始拿一个 
	{
		for(int i=0;i<=len;i++)
			{
				int l=len-i;//下面拿多少个 
                dp[len][i]=max(dp[len-1][i]+arr[n-l+1]*len,dp[len-1][i-1]+arr[i]*len);
                //两种决策:上面拿，下面拿 
		}
	}
	for(int i=0;i<=n;i++)
	  ans=max(ans,dp[n][i]);
	printf("%d\n",ans);
	return 0;
}
```



---

## 作者：一只野生蒟蒻 (赞：2)

这题说简单也不简单，说难也不难~

这题就是一个普通的区间DP，非常适合区间DP入门的同学。我们设dp[i][j]表示售出第i份零食到第j份零食所能获得的最大价值。

于是状态转移方程就很好推了：dp[i][j]=max(dp[i+1][j]+a[i]*t,dp[i][j-1]+a[j]*t)(这里的a[i]就是第i份零食的初始售价，t就是这份零食是第几天售出的)

接下来就是这题的唯一的难点了：当前这份零食是在第几天被售出的呢？（t=?）

这个问题在初次做这题时的确很难，但当你把dp[i][j]和题目连起来一想，它就迎刃而解了——一共有n份零食，要把它们在n天内售出，而dp[i][j]的跨度l刚好就是售出了l份零食，所以就可以得到t=n-l+1

有了这一点，剩下的就只剩板子了

参考代码:
```
#include <bits/stdc++.h>
using namespace std;
int n,a[2004],dp[2004][2004];
int main()
{
	cin>>n;
	for (int i=1;i<=n;i++)
	{
		cin>>a[i];
		dp[i][i]=a[i]*n;
		//初始化：第i份零食能获得的最大价值就是把它留到第n天卖 
	}
	for (int l=2;l<=n;l++)//枚举区间跨度 
		for (int i=1;i+l-1<=n;i++)//起点 
		{
			int j=i+l-1;//终点 
			dp[i][j]=max(dp[i+1][j]+a[i]*(n-l+1),dp[i][j-1]+a[j]*(n-l+1));
		}
	cout<<dp[1][n];//输出1~n 
	return 0;
}
```
做完这题，有余力的同学可以去做一下[P1005 矩阵取数游戏](https://www.luogu.org/problem/P1005)，和这题基本没什么区别

---

## 作者：Manjusaka丶梦寒 (赞：2)

毫无疑问区间dp。

！[区间dp入门](https://www.cnblogs.com/rmy020718/p/9515963.html)

我们定义dp[i][j]表示从i到j的最大收益，显然我们需要利用比较小的区间来推出更大的区间。

初始化dp[i][i]=单价，这里先不考虑第几天卖。

现在我们来确定小区间与大区间的关系，继而写出递推方程式。

每一个区间长度为一的块，想要扩大区间长度，那么只需要考虑对于现区间的左右端点的相邻点，我们可以通过比较确定是取左邻点还是右邻点(i，j分别表示左右端点)。

$$dp[i][j]=max(dp[i-1][j],dp[i][j-1])[i,j]$$

现在我们不管取左边的点还是右边的点，没有动过的点卖的天数县比与上一个状态晚卖了一天，所以每一个物品要加一次单价。

那么需要(a[k]表示单价)

$$dp[i][j]+=\sum_{k=i}^{k<=j}a[k]$$

为了简便$\sum_{k=i}^{k<=j} a[k]$提前用前缀和统计一下就好了。

所以外层循环枚举区间长度，内层循环枚举左端点。

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <queue>
#include <map>
using namespace std;
#define LL long long
#define mod int(1e9+7)
#define wlz 1234567890
int n,ans1,ans2;
int a[2110],sum[2110],dp[2110][2110];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        dp[i][i]=a[i];
        sum[i]=sum[i-1]+a[i];
    }
    for(int len=2;len<=n;len++) 
    {
        for(int i=1;i<=n;i++) 
        {
            int j=i+len-1;
            if(j>n)break;
            dp[i][j]=max(dp[i+1][j],dp[i][j-1]);
            dp[i][j]+=(sum[j]-sum[i-1]);
        }
    }
    printf("%d",dp[1][n]);
}
```

---

## 作者：ljc20020730 (赞：2)

区间dp？下面dalao们写的很详细，我还是不用区间dp吧

状态：
- F[i][j][0]表示前i天（向上）卖出j份，向下卖出i-j份，且第i天为向上卖；
- F[i][j][1]表示前i天（向上）卖出j份，向下卖出i-j份，且第i天为向下卖。

转移：
- f[i][j][0]=max(f[i-1][j-1][0],f[i-1][j-1][1])+i*v[j];
- f[i][j][1]=max(f[i-1][j][0],f[i-1][j][1])+i*v[n-i+j+1]；

答案：
- max(f[n][i][0],f[n][i][1]);

程序（加了滚存这里默认你们看得懂）：

```
# include <cstdio>
# include <cstring>
# include <iostream>
using namespace std;
const int MAXN=2005;
int n,v[MAXN],f[2][MAXN][2];
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&v[i]);
	memset(f,0,sizeof(f));
	int p=1;
	for (int i=1;i<=n;i++,p^=1) 
	 for (int j=0;j<=i;j++) {
	 	if (j-1<=i) f[p][j][0]=max(f[p^1][j-1][0],f[p^1][j-1][1])+i*v[j];
		f[p][j][1]=max(f[p^1][j][0],f[p^1][j][1])+i*v[n-i+j+1];
	 }
	int ans=0;
	for (int i=1;i<=n;i++) ans=max(ans,max(f[n&1][i][0],f[n&1][i][1]));
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：高铁1号 (赞：2)

# 一道记忆化搜索

### 状态转移方程1：p=max(p,dfs(l+1,r,x+1)+v[l]\*x)

### 状态转移方程2：p=max(p,dfs(l,r-1,x+1)+v[r]\*x)

### 代码附上：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>//头文件准备
using namespace std;
int n;
int v[2005],f[2005][2005];
//记忆化搜索开始
int dfs(int l,int r,int x)
{
    int p=0;
    if (x>n)
        return 0;//判断边界1
    if (f[l][r]!=-1)
        return f[l][r];//判断是否计算过
    if (l>r)
        return 0;//判断边界2
    p=max(p,dfs(l+1,r,x+1)+v[l]*x);//状态转移方程1
    p=max(p,dfs(l,r-1,x+1)+v[r]*x);//状态转移方程2
    return f[l][r]=p;//记忆
}
//记忆化搜索结束
int main()
{
    scanf("%d\n",&n);
    for (int i=1;i<=n;i++)
        scanf("%d\n",&v[i]);//读入
    memset(f,-1,sizeof(f));//初始化
    printf("%d\n",dfs(1,n,1));
    return 0;
}

```
### 此为我的第2篇题解，如有不足，请各位dalao指出，谢谢！


---

## 作者：Dr_殇 (赞：2)

#这题很简单，是一个简单的DP，其动态转移方程是：ans[i][j]=max(ans[i+1][j]+a[i]\*(n-j+i),ans[i][j-1]+a[j]\*(n-j+i));只要按着这个动态转移方程套就行了。


##千万不要直接抄程序，什么都学不到的，先想想这个动态转移方程是怎么来的。


##代码如下：





```cpp
#include <cmath>
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>//头文件准备
using namespace std;
int n,a[2005];
int ans[2005][2005];
int main(){
    freopen ("2858.in","r",stdin);
    freopen ("2858.out","w",stdout);
    scanf ("%d",&n);//读入n
    for (int i=1;i<=n;i++){
        scanf ("%d",&a[i]);//读入每个零食的价值
    }
    for (int i=n;i>=1;i--){
        for (int j=i;j<=n;j++){
            ans[i][j]=max(ans[i+1][j]+a[i]*(n-j+i),ans[i][j-1]+a[j]*(n-j+i));//动态转移方程
        }
    }
    printf ("%d\n",ans[1][n]);//最后输出答案
        while (1);//反抄袭
    return 0;
}
```
#珍爱生命，拒绝抄袭！

##小心晚上会有人来找你。


---

## 作者：何卓然 (赞：2)

我们发现，对于这个序列的每一部分，如果已经取到了这种状态，所得到的当前最优值，只于上一步 从头取的数字，还是从尾取的数字有关，我们可以采取区间DP的方式：

f[l][r] 表示 取到了左边为 l ， 右边为 r 的区间，可以得到的最优值。

可以得到状态转移方程为： f[l][r] = max(f[l-1][r] + (n-i-1) \* a[l-1],f[l][r+1] + (n-i-1) \* a[r+1])

我们最终的答案就是 max(f[i][i] + n \* a[i])


值得注意的是，我们的转移方程要求， f[l-1][r] 和 f[l][r+1] 已经被计算过，所以我们可以采取外层循环枚举区间长度的方式，这样可以保证，计算到的每一个小区间，它所需要的，比他稍大的区间都已经计算过，这是利用区间DP解决问题的一个要点。


**Code**






    
    

```cpp
#include<bits/stdc++.h>
#define REP(i,a,b) for (int i=(a);i<(b);++i)
typedef long long LL;
using namespace std;
LL n,a[2005],l,r,d = 1, ans = 0;
LL f[2005][2005];
LL max(LL a,LL b){
    return a > b ? a : b;
}
int main()
{
    scanf("%d",&n);
    REP(i,0,n) scanf("%d",&a[i]);
    f[0][n-1] = 0;
    for (int i = n - 2; i >= 0; i--)
    {
        for (int l = 0; l + i < n; l++)
        {
            int r = l + i;    
            if (l == 0) f[l][r] = f[l][r+1] + (n - i - 1) * a[r + 1];
            else if (r == n - 1) f[l][r] = f[l-1][r]    + (n - i - 1) * a[l - 1];
            else f[l][r] = max(f[l-1][r] + (n-i-1) * a[l-1],f[l][r+1] + (n-i-1) * a[r+1]);
        }
    }    
    REP(i,0,n) ans = max(ans,f[i][i] + n * a[i]);
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：Kirito_Sans_桐衫 (赞：1)

嗯……今天我们就来讲一下这一题……

首先，看题目，题目的大意是有一个长度为n的数列，数列的第i项为a[i]，在第j天你可以卖掉目前剩下的数列的最左边或者最右边，这时你的money就会加上你卖掉的数×j的积，每一天只能卖一个，求最大的总钱数……

那么，设f[i][j]表示从i买到j的最优价格~~（欲购从速！）~~，那么
……明显这是个区间ＤＰ对吧？

区间ＤＰ的思想就是：设f[i][j]表示从i到j的最优值，然后由一个小的区间枚举到一个大的区间，这样一步一步的选，最终求出f[1][n]的值。

这道题直接打动归很麻烦，所以我们可以考虑一下记忆化……？

记忆化相信大家都听说过，就是“搜索的模样，动归的心”，最大的优点就是能避免重复计算，使得效率大大加快。

首先从1,n,d开始递归，这里设放进递归的第一个数为l（数列的最左边），第二个数是r（数列的最右边），第三个数是d（当前第几天），然后……看代码去！
```
#include<cstdio>
int n;
int a[2001],f[2001][2001];
int dfs(int l,int r,int d)
{
	if(r<l)return 0;
	if(l==r)return a[l]*d;
	if(f[l][r])return f[l][r];
	f[l][r]=f[l][r]>dfs(l+1,r,d+1)+a[l]*d?f[l][r]:dfs(l+1,r,d+1)+a[l]*d;
	f[l][r]=f[l][r]>dfs(l,r-1,d+1)+a[r]*d?f[l][r]:dfs(l,r-1,d+1)+a[r]*d;
	return f[l][r];
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	printf("%d",dfs(1,n,1));
}
```

---

## 作者：zhouwc (赞：1)

## c++
本次题解已经过修改，加上了代码注释。


其实我觉得USACO挺不错的，就是有的时候这个翻译什么的有点不懂。。。（其实是我看不懂。。）

这道题我一开始以为可以用贪心（两端只取最小的，把大的留到后面）做，后来发现用贪心是不行的，比如这个数据 6 1 1 5 5 1 就不行了，如果用贪心答案是71，而正确答案是75。


好吧，言归正传。

这道题的正解应该是**区间dp**，然而我是用**记忆化搜索**做的。

 
对于一个区间【l，r】（即l到r的位置），会存在一个最优解（最大值）。而在普通的搜索中，这个区间中的最大值会重复搜索计算，所以在这个时候我们就需要用记忆化，把最大值记录下来，避免下次重复搜索。


具体AC代码如下


```cpp
    #include<stdio.h>
    #include<iostream>
    using namespace std;
    int n,a[2005],f[2005][2005],ans;
    //其中f数组表示在l,r区间中的最大值，a数组为读入//的数组，ans用来存储最后值（不用也行）
    int dfs(int k,int l,int r)//记忆化开始
    //k代表已经卖掉了几个零食（也可表示为层次）
    {
        int p=0;
        if (k>n) return 0;//边界
        if (f[l][r]!=-1) return f[l][r];
        //如果已经搜索过，则不需要再次搜索，return
        if (l>r) return 0;//边界
        p=max(p,dfs(k+1,l+1,r)+a[l]*k);//计算
        p=max(p,dfs(k+1,l,r-1)+a[r]*k);//计算
        f[l][r]=p;//存储当前最优解
        return p;
    }
    int main()
    {
        scanf("%d",&n);
        for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++)
        f[i][j]=-1; //赋初值标记是否搜索过
        for (int i=1;i<=n;i++)
        {
            scanf("%d",&a[i]);
        }
        ans=dfs(1,1,n);//记忆化
        printf("%d",ans);
    } 
如有错误，还请指出
```

---

## 作者：雪颜 (赞：1)

既然楼下都是DP 那我来写个记忆化搜索好了

设f[i][j]表示现在的零食盒子里以i开头，以j结尾，那么我们只要看从哪边那最划算就ok了

```cpp
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
const int ML=2005;
int f[ML][ML],a[ML],n;
int DFS(int i,int j,int num){
    if(num>n) return 0;
    if(f[i][j]!=-1) return f[i][j];
    f[i][j]=max(DFS(i+1,j,num+1)+a[i]*num,DFS(i,j-1,num+1)+a[j]*num);//这句话相当于DP的状态转移方程
    return f[i][j];
}
int main(){
    scanf("%d",&n);
    int i;
    for(i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    memset(f,-1,sizeof(f));//初始化，一定要初始化！
    printf("%d",DFS(1,n,1));
    return 0;
}
```

---

## 作者：Honor誉 (赞：1)

关于这道题，我有个很大的疑问。

为什么各位大佬写的都是DP，这题可以用暴搜加记忆化过掉。

我们可以记录头和尾再加一个卖了的零食数目，如果头超过尾就return 0。

如果遇到需要重复使用的数，（也就是不为零的d数组）就直接return d[tuo][wei]。

如果没有，就取卖头一个与最后一个的最大值，并记录下来。

代码也有注释，具体可以自己看。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[2001],d[2001][2001];
int dfs(int gong,int tuo,int wei)
{
	if(tuo>wei)
	{
		return 0;//返回
	}
	if(d[tuo][wei])
	{
		return d[tuo][wei];//运用记忆化
	}
	return d[tuo][wei]=max(dfs(gong+1,tuo+1,wei)+gong*a[tuo],dfs(gong+1,tuo,wei-1)+gong*a[wei]);//运用记忆化
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	cout<<dfs(1,1,n)<<endl;//输出
	return 0;
}
```

---

## 作者：hhhw (赞：1)

其实写这篇博客的原因只是想简单学用一下```$L^a$$$T_e$$$X$```，emmm...

而且本蒟蒻水平极低，只能写写普及题...

用```$d_{i,j}$```表示目前剩下第i~j份零食所已经卖出的最大价值

可以推出

```$d_{i,j}$ $=$ $max$$$($$$d_{i-1,j}$ $+$ $v_{i-1}$$$\times$$$(n+i-j-1)$, $d_{i,j+1}$ $+$ $v_{j+1}$$$\times$$$(n+i-j-1))$;```

```
//被某谷TeX语法弄蒙了orz...
```

然后采用i顺序,j倒序的方式遍历的

```cpp
#include <bits/stdc++.h>
#define qwq(i,a,b) for(register int i=a;i<=b;++i)
#define qmq(i,b,a) for(register int i=b;i>=a;--i)
using namespace std;

typedef long long ll;
inline ll read(){
	register ll x=0,f=1; register char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1; ch=getchar();}
	while(isdigit(ch)){x=(x<<3)+(x<<1)+(ch^48); ch=getchar();}
	return x*f;
}
int n,d[2010][2010],v[2010],ans;
int main(){
	n=read(); qwq(i,1,n) v[i]=read();
	qwq(i,1,n)qmq(j,n,i){
		d[i][j]=max(d[i-1][j]+v[i-1]*(n+i-j-1), d[i][j+1]+v[j+1]*(n+i-j-1));
	}
	qwq(i,1,n) ans=max(ans,d[i][i]+v[i]*n); //别忘了还要卖最后一份
	cout << ans << endl;
	return 0;
}
```

---

## 作者：Jigsaw_Killer (赞：1)

/\*一道简单的记忆华搜索。a数组表示这个零食的钱，之后分两种情况：取首或者取尾。取首的话钱是a[i]\*（i+n-j），i+n-j就是当前天数；取尾的话钱是a[j]\*(i+n-j),然后两者取最大，不断递归，f[i][j]就是ans

\*/

```cpp
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#include <cstdio>
int n,a[2003],f[2003][2003];
void init()
{
    scanf("%d",&n);
    for (int i=0;i<n;i++) scanf("%d",a+i);
    return;
}
int ma(int a,int b){return a>b?a:b;}
int dp(int i,int j)
{
    if (i>j) return 0;
    if (f[i][j]) return f[i][j];
    int tmp=0;
    tmp=ma(a[i]*(i+n-j)+dp(i+1,j),a[j]*(i+n-j)+dp(i,j-1));
    return f[i][j]=tmp;
}
void work()
{
    printf("%d",dp(0,n-1));
    return;
}
int main()
{
    //freopen("trt.in","r",stdin);
    //freopen("trt.out","w",stdout);
    init();work();
    return 0;
}

```

---

## 作者：gary2005 (赞：0)

我的dp方程非常简单，和大家的完全不同

dp[l][r][d]>>在第d天剩下[l,r]所得的最大值

for(d:n-1~1)

for(l:1~d+1)

r=l+(n-d)-1

dp[l][r][d]=max(dp[l][r+1][d-1]+v[r+1]× d,dp[l-1][r][d-1]+v[l-1]× d);//显而易见

但是我们定义dp数组时得定义三维到了2000，显然是编译不过了。

但是，我发现l的值永远小于r的值，所以数组并没有全部用上，指针数组大法好

定义一个 二维指针数组 long long* dp[MAXN][MAXN];
仔细推敲调换下下标位置就ok了

现在上AC代码

```cpp
//14/02/19 10:46
#include<bits/stdc++.h>
#define debugp(x) //cout<<"第"<<__LINE__<<"行的调试："<<#x<<"值为:"<<x<<endl; 
using namespace std;
const int MAXN=2000+10;
long long* dp[MAXN][MAXN];
int n,v[MAXN];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>v[i];
	for(int i=n-1;i>=0;i--){
		for(int j=n-i;j<=n;j++){
			int k=0;
			dp[j][i]=new long long [++k+4];//大小不同
		}	
	}
	dp[n][0][1]=0;
	for(int d=1;d<=n-1;d++){
		for(int l=1;l<=d+1;l++){
			int r=l+n-d-1;
			debugp(l);//请忽视*-*
			debugp(r);
			debugp(d);
			dp[r][d][l]=0;
			if(r+1<=n) dp[r][d][l]=max(dp[r][d][l],dp[r+1][d-1][l]+v[r+1]*d);//防止越界
			if(l-1>=1) dp[r][d][l]=max(dp[r][d][l],dp[r][d-1][l-1]+v[l-1]*d);
		}
	}
	long long maxans=0;
	for(int i=1;i<=n;i++){//找出最大值
		maxans=max(maxans,dp[i][n-1][i]+v[i]*n);
	}
	cout<<maxans<<endl;
	return 0;
} 
```

---

## 作者：孙广宸 (赞：0)

挺常规的一个区间dp，不过就是不用枚举分割点了，直接枚举长度和左端点就好了
```cpp
#include <cstdio>
using namespace std;
int n,a[2010];
int f[2010][2010];
int max(int x,int y){return x>y?x:y;}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)f[i][i]=a[i]*n;
    for(int len=2;len<=n;len++){
        for(int l=1;l<=n;l++){
            int r=len+l-1;
            if(r>n)continue;
            f[l][r]=max(f[l][r-1]+a[r]*(n-len+1),f[l+1][r]+a[l]*(n-len+1));
        }
    }
    printf("%d",f[1][n]);
    return 0;
}
```
初始化f[i][i]=a[i]∗nf[i][i]=a[i]∗n如果只有这一个当然是放到最后一天卖赚最多

然后转移的时候，从更小的那个区间更新就可以了，天数其实就是n−len+1n−len+1，因为我们的区间其实是剩下的区间，也就是已经取了n−len+1n−len+1天

方程：f[l][r]=max(f[l][r−1]+a[r]∗(n−len+1),
					f[l+1][r]+a[l]∗(n−len+1))

---

## 作者：Krystalove (赞：0)

很简单嘛，从最后一天往前数，dp[left][right]表示从left到right区间内的答案，预处理就是dp[i][i]为自己第一天被取也就是v[i]\*n，尝试往左右拓展即可







```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define maxn 2010
ll dp[maxn][maxn],a[maxn],n;
ll inline day(ll l,ll r){
    return n-(r-l)-1;
}
int main(){
    scanf("%lld",&n);
    for(register ll i=1;i<=n;i++) scanf("%lld",&a[i]),dp[i][i]=a[i]*n;
    for(register ll dis=0;dis<=n;dis++)
        for(register ll left=1;left+dis<=n;left++){
            ll right=left+dis;
            if(left!=1) dp[left-1][right]=max(dp[left-1][right],dp[left][right]+a[left-1]*day(left,right));//试着往左边拓展答案
            if(left+dis!=n) dp[left][right+1]=max(dp[left][right+1],dp[left][right]+a[right+1]*day(left,right));//试着往右边拓展答案
        }
    printf("%lld",dp[1][n]);
    return 0;
}
```

---

## 作者：睿屿青衫 (赞：0)

直接上DP代码，加入了读入优化（read自定义函数就是），需要仔细想一下状态转移方程，代码如下

、、、cpp

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 2020
using namespace std;
int read()
{
    int x=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') ch=getchar();
    while(ch>='0'&&ch<='9')
     {
         x=x*10+ch-'0';
         ch=getchar();
     }
    return x;
}
int n,v[maxn],tot=0,f[maxn][maxn];
int main()
{
    n=read();
    for(int i=1;i<=n;++i)
     {
         v[i]=read();
     }
    for(int i=n;i>=1;--i)
     for(int j=i;j<=n;++j)
      {
          f[i][j]=max(f[i+1][j]+v[i]*(n-j+i),
          f[i][j-1]+v[j]*(n-j+i));
      }
    printf("%d\n",f[1][n]);
    return 0;
}
、、、
```

---

## 作者：cxq2002 (赞：0)

# 果断DP

**转移方程：f[i][j]=max(f[i+1][j]+a[i]\*(n-j+i),f[i][j-1]+a[j]\*(n-j+i),); **

上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n,sum=0;
    cin>>n;
    int a[n],dp[n+1][n+1];
    for(int i=0;i<n;i++)
        cin>>a[i];
    memset(dp,0,sizeof(dp));
    for(int i=n-1;i>=0;i--)
        for(int j=i;j<n;j++)
            dp[i][j]=max(dp[i+1][j]+a[i]*(n-j+i),dp[i][j-1]+a[j]*(n-j+i));
    cout<<dp[0][n-1];
}
```

---

## 作者：mengdai (赞：0)

这题类似于矩阵取数

不过更加简单，不用高精度了\(^o^)/~

我们看题目可列出f[i][j][k]

表示左边取到第i个，右边取到第j个时，已经取了k个的最大值

但是可以用(n-j+i)来表示现在取的是第k个

所以可以降维用f[i][j]表示表示左边取到第i个，右边取到第j个时的最大值

转移方程

f[i][j]=max(f[i+1][j]+a[i]\*(n-j+i),f[i][j-1]+a[j]\*(n-j+i),);

f[i][i]=a[i]\*n;

代码如下：

        
```cpp
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
int n,i,j;
long long ans;
long long jiyi[2003][2003];
int a[2003];
int dp(int x,int y){
    long long& fanhui=jiyi[x][y];
    if(fanhui!=-1){
        return fanhui;
    }else{
        if(x==y){
            fanhui=a[x]*n;
        }else{
            fanhui=max(dp(x+1,y)+a[x]*(x-1+n-y+1),dp(x,y-1)+a[y]*(x-1+n-y+1));
        }
    }
    return fanhui;
}
int main(){
    cin>>n;
    for(i=1;i<=n;i++){
        cin>>a[i];
    }
    for(i=0;i<=n+1;i++){
        for(j=0;j<=n+1;j++){
            jiyi[i][j]=-1;
        }
    }
    ans=dp(1,n);
    cout<<ans;
    return 0;
}
//此题数据貌似有错，这程序样例试过了但是爆蛋
```

---

