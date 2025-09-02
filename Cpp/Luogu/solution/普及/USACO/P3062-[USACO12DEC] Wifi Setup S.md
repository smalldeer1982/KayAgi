# [USACO12DEC] Wifi Setup S

## 题目描述

Farmer John's N cows (1 <= N <= 2000) are all standing at various positions along the straight path from the barn to the pasture, which we can think of as a one-dimensional number line.  Since his cows like to stay in email contact with each-other, FJ wants to install Wifi base stations at various positions so that all of the cows have wireless coverage.

After shopping around, FJ learns that the cost of a Wifi base station depends on distance it can transmit: a base station of power r costs A + B\*r, where A is a fixed cost for installing the base station and B is a cost per unit of transmission distance.  If FJ installs such a device at position x, then it can transmit data to any cow located in the range x-r ... x+r.  A base station with transmission power of r=0 is allowed, but this only provides coverage to a cow located at the same position as the transmitter.

Given the values of A and B, as well as the locations of FJ's cows, please determine the least expensive way FJ can provide wireless coverage for all his cows.

给出在同一条直线上的n个点和两个数A，B，现在要在这条直线上放置若干个信号塔，每个信号塔有一个r值，假设它的位置是x，则它能覆盖的范围是x-r~x+r，放置一个信号塔的花费是A+B\*r，问要覆盖所有的点最小的花费是多少。


## 说明/提示

There are 3 cows at positions 7, 0, and 100.  Installation of a base station of power r costs 20 + 5\*r.


The optimal solution is to build a base station at position 3.5 (with power 3.5) and another at position 100 (with power 0).  The first base station covers cows 1 and 2, and the second covers cow 3.


## 样例 #1

### 输入

```
3 20 5 
7 
0 
100 
```

### 输出

```
57.5 
```

# 题解

## 作者：Parat_rooper (赞：3)

# 解题思路：

首先观察题面，不难发现，对于任意一段区间 $[i, j]$，若已知  $[1, i-1]$ 都被覆盖的最小代价时，是可以直接求出覆盖 $[1, j]$  的最小代价的。所以我们不难想到区间动态规划，而这题很明显可以用到收集型的优化。

于是我们令 $cost_i$ 表示以 i 结尾的区间的最小代价，而 $f_{i ,j}$ 表示以区间 $[1, i]$ 从 j 断开，分成 $[1, j - 1]$ 和 $[j, i]$ 两个区间，我们可以写出状态转移方程：
$$f_{i, j} = max(f_{i, j}, cost_j - 1 + money_{j, i})$$
此处 $money_{j, i}$ 算的是在区间 $[i, j]$ 中放一个信号发射器的最小代价。然后根据这个转移方程我们就可以写出代码了。

代码如下

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int kMaxN = 2001;

int n, w[kMaxN], f[kMaxN][kMaxN], cost[kMaxN], a, b;

int main() {
  ios_base::sync_with_stdio(0), cin.tie(NULL), cout.tie(NULL);
  cin >> n >> a >> b;
  for (int i = 1; i <= n; i++) {
    cin >> w[i];
    cost[i] = (1e9 + 1);//cost计算[1,i]的最小代价
  }
  sort(w + 1, w + n + 1);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= i; j++) {
      f[j][i] = cost[j - 1] + (w[i] - w[j]) * b + 2 * a;
      cost[i] = min(cost[i], f[j][i]);
    }
  }
  if (cost[n] % 2) {
    cout << cost[n] / 2 << ".5";
  } else {
      cout << cost[n] / 2;
  }
  return 0;
}
```
虽然这一段代码也能通过，但经过我反复的 ~~看题解~~ 推敲后，我想到了优化状态的方式。

我们发现实际上 f 数组是废的，我们可以直接删掉，因为我们只需要求所有的可以表示为 $[1, i]$ 的区间，而 f 数组也是同样的作用，因此此时我们的状态转移方程可以简化为：
$$cost_i = min(cost_{j-1} + money_{i,j})$$
$money_{i, j}$ 作用同上。

最后同样记得要乘 2 处理，因为题目是要求你在答案为整数时不输出小数部分。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int kMaxN = 2001;

int n, w[kMaxN], cost[kMaxN], a, b;

int main() {
  ios_base::sync_with_stdio(0), cin.tie(NULL), cout.tie(NULL);
  cin >> n >> a >> b;
  for (int i = 1; i <= n; i++) {
    cin >> w[i];
    cost[i] = (1e9 + 1);//cost计算[1,i]的最小代价
  }
  sort(w + 1, w + n + 1);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= i; j++) {
      cost[i] = min(cost[j - 1] + (w[i] - w[j]) * b + 2 * a, cost[i]);
    }
  }
  if (cost[n] % 2) {
    cout << cost[n] / 2 << ".5";
  } else {
      cout << cost[n] / 2;
  }
  return 0;
}
```
完结撒花~~~



---

## 作者：_lmz_ (赞：3)

# 解题思路
首先，看到题目以后，第一反应是 dfs，但再看数据范围，$n \leq 2000$，所以普通 dfs 顶多 20 分。

先抛除其他优化，写出最普通的 dfs。

20 分  Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define ud unsigned double
#define db double
#define ll long long
const int maxn = 1e6,INF=0x7fffffff;
const int X[]={0,1,0,-1},Y[]={-1,0,1,0};
const int N=2010;
int n,a,b,h[N];
int dfs(int n){
	if(n==0) return 0;// 如果n==0表示已经计算结束,0头牛只要0的花费,直接return 0; 
	int mn=-1;      //最小值 
	for(int i=n;i>=1;i--){
		int t=(h[n]-h[i])*b+2*a+dfs(i-1);//因为浮点数运算不方便,而样例只可能是整数或整数+0.5,所以将(距离)/2*b+a乘以2,可得(距离)*b+2*a 
		if(mn==-1||mn>t)
			mn=t;
	} 
	return mn;
}
int main(){
	cin>>n>>a>>b;
	for(int i=1;i<=n;i++) cin>>h[i];
	sort(h+1,h+1+n);
	int ans=dfs(n);
	if(ans&1) cout<<ans/2<<".5";    //&1==1表示是奇数 
	else cout<<ans/2;  //否则为偶数 
	return 0;
}
```


再举个例子，随便就可以让无优化的 dfs 卡掉。

例：```dfs(5)```，要分析 ```dfs(4)``` 到 ```dfs(1)```，而 ```dfs(1)``` 的运算数量是非常可观的。

说道重复计算，第一想到的就是记忆化搜索。

### 那么，什么是记忆化搜索呢？

百度上说：搜索到的一些解用动态规划的那种思想和模式作一些保存。

顾名思义，就是把搜过的存起来，减少了非常多的不必要的时间。

再用上面那个例子，```dfs(5)``` 第一次访问 ```dfs(1)``` 以后，后面的 ```dfs(4)``` 到 ```dfs(1)``` 就不用再访问 ```dfs(1)``` 了。

AC 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define ud unsigned double
#define db double
#define ll long long
const int maxn = 1e6,INF=0x7fffffff;
const int X[]={0,1,0,-1},Y[]={-1,0,1,0};
const int N=2010;
int n,a,b,h[N],f[N];
int dfs(int n){
	if(n==0) return 0;
	if(f[n]!=-1) return f[n];    //已经计算过了,直接返回f[n] 
	for(int i=n;i>=1;i--){
		int t=(h[n]-h[i])*b+2*a+dfs(i-1);
		if(f[n]==-1||f[n]>t)
			f[n]=t;               //标记 
	} 
	return f[n];
}
int main(){
	cin>>n>>a>>b;
	for(int i=1;i<=n;i++) cin>>h[i];
	sort(h+1,h+1+n);
	memset(f,-1,sizeof(f));
	int ans=dfs(n);
	if(ans&1) cout<<ans/2<<".5";
	else cout<<ans/2;
	return 0;
}
```


---

## 作者：yinhee (赞：1)

# [题目传送门](https://www.luogu.com.cn/problem/P3062)

## 解题思路：动态规划

将每头牛坐标排序一遍，对于覆盖每个 $[1,i]$ 的区间花费，将其分为覆盖     $[1,j-1]$ 的最小花费和覆盖 $[j,i]$ 整个区间的花费。故可以写出状态转移方程：

令 $ dp _ i$ 表示覆盖 $[1,i]$ 的区间花费最小值，$ cost_{i,j}$ 表示覆盖 $[i,j]$ 整个区间的花费，则：

$ dp_i= \min( dp_j+ cost_{j+1,i})$

当然也别忘了 $ dp_i= cost_{1,i}$ 这种情况。

最后，题目要求答案为整数时不输出小数部分，则做 $\times2$ 处理，最后再除回来。

代码：

```cpp
#include<cstdio>
#include<algorithm>
#define max(a,b) a>b?a:b
#define min(a,b) a<b?a:b
using namespace std;
typedef long long ll;
const int maxn=2e3+7;
int n,A,B,e[maxn],dp[maxn];
inline int cost(int l,int r){//计算区间花费 
	return 2*A+(e[r]-e[l])*B;
}
int main(){
	scanf("%d%d%d",&n,&A,&B);
	for(int i=1;i<=n;i++)scanf("%d",&e[i]);
	sort(e+1,e+n+1);
	for(int i=1;i<=n;i++){
		dp[i]=cost(1,i);
		for(int j=1;j<=i-1;j++){
			dp[i]=min(dp[i],dp[j]+cost(j+1,i));
		}
	}
	if(dp[n]&1)printf("%.1lf",(double)dp[n]/2);
	else printf("%d",dp[n]/2);
}

```

蒟蒻的第一篇题解，如有不足请见谅！

---

## 作者：信守天下 (赞：1)

## [洛谷传送门](https://www.luogu.com.cn/problem/P3062)
## 思路 $1$：贪心
我们可以记录上一个建信号塔的位置 $l$。

对于一个点 $r$：

在 $l$ 和 $r$ 之间建信号塔的代价低于在 $r$ 建 $1$ 个新信号塔的代价时。

选择在中间建信号塔。

否则计算从 $l$ 到 $r - 1$ 所需代价，累加答案，再移动 $l$ 到 $r$。

### 时间复杂度
排序 $O(n \log n)$。

求解 $O(n)$。

共 $O(n \log n)$。
### 贪心 code
~~~cpp
#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
const int kMaxN = 2001;
int n, a, b;
double ans;
int cow[kMaxN];
int main() {
  cin >> n >> a >> b;
  for (int i = 1; i <= n; i++) {
    cin >> cow[i];
  }
  sort(cow + 1, cow + 1 + n);
  double num = a;                        //当前费用
  for (int i = 1, j = 2; j <= n; j++) {  //左边界,右边界
    if (num <= (cow[j] - cow[i]) * 1.0 * b / 2) {
      i = j;       //移动边界
      ans += num;  //累加答案
      num = a;
    } else {
      num = a + (cow[j] - cow[i]) * 1.0 * b / 2;
    }
  }
  ans += num;
  if (abs((int)ans - ans) <= 1e-5) {  //注意精度误差
    printf("%d", (int)ans);
  } else {
    printf("%.1f", ans);
  }
  return 0;
}
~~~
## 思路 $2$：动态规划
由于区间总是覆盖连续的一段，所以我们先将点按照坐标排序。

然后可以考虑按顺序进行覆盖，由此得到状态可以使用的拓扑序。

考虑用动态规划求解。

用当前覆盖到的点、当前总代价作为状态，其中总代价是最优化属性。

枚举下一个区间的右边界是转移，左边界就是下一个要覆盖的点。
### 时间复杂度
状态数量 $O(n)$。

每个状态的转移数量 $O(n)$。

总共 $O(n^2)$。
### 动态规划 code
~~~cpp
#include <algorithm>
#include <cstdio>
#include <iostream>

using namespace std;

const int kMaxN = 2001;

int p[kMaxN], dp[kMaxN];
int n, a, b;

int main() {
  cin >> n >> a >> b;
  for (int i = 1; i <= n; i++) {
    cin >> p[i];
  }
  sort(p + 1, p + 1 + n);
  for (int i = 1; i <= n; i++) {                                  // 枚举阶段
    dp[i] = 0x7fffffff;                                           // 初始化答案
    for (int j = 1; j <= i; j++) {                                // 枚举当前段左边界
      dp[i] = min(dp[i], dp[j - 1] + (p[i] - p[j]) * b + 2 * a);  // 计算代价更新答案
    }
  }
  cout << dp[n] / 2 << (dp[n] % 2 ? ".5" : "");  // 有小数则输出
  return 0;
}

~~~

---

## 作者：scp233 (赞：1)

看到没人写贪心来写一个~~（逃）~~  
首先要做的，自然是将读进来的点按位置从左到右进行排序；  
排序完以后，我们先设定一个l指针，记录当前要拉近WiFi区的点是哪一个（一开始自然是1啦）  


对于一个点，我们的想法是这样的：  

先把一座塔建在这个点脸上，塔的辐射区为0，记录代价（我们用w储存）。 

然后再搞一个r指针，一个个向右试探，我们先假设这个点会在我们这次建信号塔的时候包含进来，那么很显然塔是建在l和r中间的地方辐射区的所需半径最小，然后我们算出这样的代价（A+B*(a[r]+a[l])/2），这玩意就是我们要建WiFi包含l到r所需的代价，然后我们与之前储存的（w+A）进行比较，（w+A）表示我们建一个信号塔包含l到（r-1），再在r脸上建一个信号塔的代价。  

如果我们发现强行在l,r之间建信号塔还不如造上两个，那我们就先在l和（r-1）之间造他一个，并把l赋成r，继续之前的操作。

否则r就继续向右试探

代码，如果你看到一些奇怪的格式请不要在意，我已经对洛谷的题解系统绝望了
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<string>
#include<cstring>
#include<cmath>
#include<map>
#define rep(a,b,c) for(int a=b;a<=c;a++)
#define drp(a,b,c) for(int a=b;a>=c;a--)
#define HY 200002
#define lo long long
#define qword unsigned long long
#define mod 1000000007
#define maxlongint 2147483647
#define INF 0x3f3f3f3f
#define PI 3.141592653589793238462643383279
#define mi 18
using namespace std;

int a[2002],n,x,y,l=1,r,k;  
double w,s;  

int main(){  
  cin>>n>>x>>y; //读入，这里我们用x,y代替A,B  
   rep(i,1,n) scanf("%d",&a[i]);  
   sort(a+1,a+n+1);//排序一下  
   
   while(l<=n){  
    w=x; r=l+1; //w储存当前代价  
     while(r<=n&&((double)(a[r]-a[l])*y/2+x)<=(w+x)){  
	  w=(double)(a[r]-a[l])*y/2+x; r++; //判断哪个比较赚  
	 }  
	s+=w; l=r; //s储存总代价，做完后l赋为r  
   }  
 if(abs((int)s-s)<(1e-2)) printf("%d",(int)s);  
 else printf("%.1lf",s);  //这是为了防止浮点数神奇的精度问题  
return 0;  
}  
```

---

## 作者：404Not_Found (赞：0)

只会 $O(n^2)$ 的 dp。

考虑先把点按坐标排序，按顺序进行覆盖。那么状态就很好设。

设 $f(i)$ 为将 $[1,i]$ 覆盖的最小代价，$cost(i,j)$ 为在 $i$ 和 $j$ 之间覆盖的花费，则有状态转移方程

$$f(i)=\min_{j=1}^{i} \{f(j-1)+cost(j,i)\}$$

但是题目要求答案不是小数时只保留整数部分，因此可以先把答案 $\times2$ 处理，最后 $\div2$ 时有小数再输出小数部分。

时间复杂度 $O(n^2)$。

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1005;
int f[MAXN],p[MAXN];
int n,a,b;
int main()
{
	scanf("%d%d%d",&n,&a,&b);
	for(int i=1;i<=n;i++) scanf("%d",&p[i]);
	sort(p+1,p+n+1);
	for(int i=1;i<=n;i++)
	{
		f[i]=1e9;
		for(int j=1;j<=i;j++)
			f[i]=min(f[i],f[j-1]+(p[i]-p[j])*b+2*a);
	}
	printf("%d",f[n]/2);
	if(f[n]&1) puts(".5");
	return 0;
}
```

---

## 作者：Violet___Evergarden (赞：0)

动态规划的做法，设 $dp_i$ 表示将前 $i$ 只奶牛用 wifi 覆盖所要得最小花费，$money_{i,j} (i \le j)$表示在第 $i$ 头和第 $j$ 头牛之间装一个信号塔要用的花费。

对于每一个 $i$，我们可以在前 $j(j<i)$ 头牛被覆盖的基础上，在 $j+1$ 到 $i$ 头牛之间再装一个信号塔。

那么转移方程就出来了：
$$ dp_i = \min(dp_i,dp_j+money_{j+1,i})$$

由于输出是小数，直接用小数变量存会因为玄学原因只能拿 $70$ 分，可以先将计算价格的 $2$ 倍，最后再变回来。
```cpp
#include<iostream>
#include<algorithm>
#define int long long
using namespace std;
const int kMaxN=2001;
int cow[kMaxN],n,a,b;
int money[kMaxN][kMaxN],dp[kMaxN];
signed main()
{
//freopen("wifi.in","r",stdin);
//freopen("wifi.out","w",stdout);
cin>>n>>a>>b;
for(int i=1;i<=n;i++)
{
  cin>>cow[i];
  dp[i]=1e10;
}
sort(cow+1,cow+n+1);
for(int i=1;i<=n;i++)
{
  for(int j=1;j<=i;j++)
  {
    money[j][i]=a*2+(cow[i]-cow[j])*b;//预处理money数组
    //cout<<j<<" "<<i<<" "<<money[j][i]<<"\n";
  }
}
for(int i=1;i<=n;i++)
{
  for(int j=0;j<=i;j++)
  {
    dp[i]=min(dp[i],dp[j]+money[j+1][i]);//转移
  }
}
if(dp[n]%2==0)
{
  cout<<dp[n]/2;
}
else
{
  cout<<dp[n]/2<<".5";
}
return 0;
}
```

---

## 作者：lmz_ (赞：0)

# 题目思路：

首先，我们要了解一个很基础的算法：dfs，它对于这题很合适，但是因为 dfs 的时间复杂度一般不会太低，所以我们需要加上一些优化。

先写出 TLE 即 $20$ 分 dfs：

```cpp
int dfs(int n){
	if(n==0) return 0;
	int mn=-1;
	for(int i=n;i>=1;i--){
		int x=(h[n]-h[i])*b+2*a+dfs(i-1);
		if(mn==-1||mn>x)
			mn=x;
	}
	return mn;
}
```
然后，我们就需要一些优化了。

先举个例子：`dfs(10)`，计算它需要调用 $9+8+7+6+5+……+1$ 次 `dfs(1)`。

`dfs(1)`被调用的次数非常可观，所以，我们要加上一个优化，那就是记忆化搜索。

什么是记忆化搜索呢？顾名思义，就是把每一次搜索的结果存下来，第二次使用的时候就不用再次调用了。

我们定义一个计数器 $f$，$f_i$ 表示 `dfs(i)` 的结果，如果 dfs 的传参的 $i$ 已经被计算过了，就直接返回 $f_i$ 的值，否则就正常计算，把这个结果存下来。

代码：太丑，不放了。

---

## 作者：Expecto (赞：0)

dp
f[i]表示0~i-1的最小费用\*2

```cpp
f[i]=min(f[i],f[j]+2*a+(x[i-1]-x[j])*2);
#include<bits/stdc++.h>
using namespace std;
long long x[2111];
long long f[2111];
int main(){
    long long n,a,b;
    cin>>n>>a>>b;
    for (int i=0;i<n;i++) cin>>x[i];
    sort(x,x+n);
    f[0]=0;
    for (int i=1;i<=n;i++){
        f[i]=6666666666;
        for (int j=0;j<i;j++)
            f[i]=min(f[i],f[j]+2*a+(x[i-1]-x[j])*b);
    }
    if (f[n]%2) cout<<f[n]/2<<".5";
    else cout<<f[n]/2;
    return 0;
}
```

---

