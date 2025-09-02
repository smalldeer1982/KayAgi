# Sagheer and Nubian Market

## 题目描述

Sagheer在去Luxor和 Aswan的旅途中去了Nubian市场给它的朋友和亲戚买纪念品。这个市场有一些奇怪的规则。市场上有$n$件商品，标号为$1$到$n$。第$i$件商品有一个基本花费为$a_{i}$埃及镑。如果Sagheer买了$k$件下标分别为$x_{1},x_{2},...,x_{k}$的商品，那么第$j$件商品的实际花费就是$a_{xj}+x_{j}·k(1 <= j <= k)$换句话说，每件商品的实际花费就是它的基本花费加上(它的下标×总购买件数)

Sagheer想花最多$S$埃及镑来买尽量多的纪念品，注意它只能买同一种物品一件。如果有多种方式使纪念品数量最大，他会选择花费最小的方案。你能帮助他完成他的任务吗？

## 样例 #1

### 输入

```
3 11
2 3 5
```

### 输出

```
2 11
```

## 样例 #2

### 输入

```
4 100
1 2 5 6
```

### 输出

```
4 54
```

## 样例 #3

### 输入

```
1 7
7
```

### 输出

```
0 0
```

# 题解

## 作者：卷王 (赞：5)

## 题目大意

[传送门](https://www.luogu.com.cn/problem/CF812C)

题目写的很清楚。

## 思路

二分购买总件数，然后每次计算一下值，用数组排个序，再累加一下判断是否满足要求就行了。

当然模拟可以，就是慢了点。

代码很清晰，看一下吧。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, S, sum = 0, minn = 1e9;
int a[100007];
int b[100007];
inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9') {
		if(ch == '-') f = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9') {
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * f;
}
inline bool check(int x) {
	for(int i = 1; i <= n; i++)
		b[i] = a[i] + i * x;
	sort(b + 1, b + n + 1);
	sum = 0;
	for(int i = 1; i <= x; i++) {
		sum += b[i];
		if(sum > S) break;
	}
	return sum <= S;
}
int main() {
	n = read(), S = read();
	for(int i = 1; i <= n; i++)
		a[i] = read();
	//二分购买总件数 
	int l = 0, r = n, mid, ans = 0;
	while(l <= r) {
		mid = (l + r) / 2;
		if(check(mid)) l = mid + 1, ans = mid, minn = sum;
		else r = mid - 1;
	}
	cout << ans << " ";
	if(minn == 100000000) cout << 0;
	else cout << minn;
	return 0;
}
```

---

## 作者：xixike (赞：4)

# Description

[洛谷传送门](https://www.luogu.com.cn/problem/CF812C)

# Solution

注意到题目要求我们计算出最多能买多少个纪念品，所以容易想到二分。

我们二分最多能买多少个纪念品，把每个纪念品的实际花费计算出来，从小到大排个序，取出前 $mid$ 个，判断花费是否合法即可。

# Code

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10;
int n, s, cnt, ans, res;
int a[N], b[N];

inline bool check(int mid){
	for(int i = 1; i <= n; i++)
		b[i] = a[i] + i * mid;//计算每个物品的实际花费。
	sort(b + 1, b + 1 + n);
	res = 0;
	for(int i = 1; i <= mid && res <= s; i++)//取前 k 个物品，总花费小于等于 s
		res += b[i];
	return res <= s;
}

int main(){
	scanf("%d%d", &n, &s);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	int l = 0, r = n;
	while(l <= r){
		int mid = (l + r) >> 1;
		if(check(mid)) cnt = mid, ans = res, l = mid + 1;//二分边界向来不好调，合法时直接更新答案即可。
		else r = mid - 1;
	}
	printf("%d %d\n", cnt, ans);
	return 0;
}
```

# End

---

## 作者：Clare613 (赞：3)

**这是一道很简单的二分。**
# 前置知识
二分查找：就是不断的砍半，相信大家都了解过，在此就不多说了。
# 思路
看到这道题时，不难想到暴力做法，也就是利用两重循环来枚举所有可能，但是 $1 \le n \le 10^5$，所以只能用二分做法。\
这里我主要讲一下 $\operatorname
{check}$ 函数，$\operatorname
{check}$ 函数需要计算 $k$ 的时候的特殊数组，也就是说需要重新算一遍，排一下序，选最小的，判断和是否小于 $s$ 即可。
# code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,s,a[100005],b[100005];
bool check(int x){
	for(int i=1;i<=n;i++){
		b[i]=a[i]+i*x; 
	}
	sort(b+1,b+n+1);
	int sum=0;
	for(int i=1;i<=x&&sum<=s;i++) sum+=b[i];
	return sum<=s;
}
int main(){
	cin>>n>>s;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	int l=1,r=n;
	while(l<r){
		int mid=(l+r+1)/2;
		if(check(mid)) l=mid;
		else r=mid-1;
	}
	if(check(l)==0){
		cout<<"0 0";
		return 0;
	}
	cout<<l<<" ";
	for(int i=1;i<=n;i++){
		b[i]=a[i]+i*l; 
	}
	sort(b+1,b+n+1);
	int sum=0;
	for(int i=1;i<=l;i++) sum+=b[i];
	cout<<sum;
	return 0;
} 
```

---

## 作者：2021hych (赞：2)

# 题意化简
给定一个长度为 $n$ 的序列 $a$。定义在选取的 $k$ 个数中选择其中下标为 $j$ 的数的代价为 $a_j+j \times k$。整个选取集合的代价为集合中每个数的代价之和。求出最大的 $k$ 使得选取代价不超过 $S$ 并求出此时的最小选取代价。
# 思路
我们发现，求的是代价不超过 $S$ 的最大的 $k$，二分答案经典模型。将左右边界设为 $0$ 到 $n$。至于判断，假设当前二分到的数为 $x$。则我们可以处理出序列 $a$ 每个数此时的代价，把代价从小到大排序一下，选出前 $x$ 个，累计选取代价。此时求出的是，选 $x$ 个数的最小代价。如果此时的代价不超过 $S$，二分右区间，否则二分左区间。

第二问显然与二分判断的函数结构类似，具体参考代码理解。
# 参考代码
```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int N=100010;
int n,S;
int a[N],b[N];
int l,r,ans1,ans2;
bool check(int x) {
	int sum=0;
	for(int i=1;i<=n;i++) b[i]=a[i]+i*x;
	sort(b+1,b+n+1);
	for(int i=1;i<=x;i++) sum+=b[i];
	return sum<=S;
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>S;
	for(int i=1;i<=n;i++) cin>>a[i];
	l=0;
	r=n;
	while(l<=r) {
		int mid=l+r>>1;
		if(check(mid)) {
			l=mid+1;
			ans1=mid;
		}
		else r=mid-1;
	}
	for(int i=1;i<=n;i++) b[i]=a[i]+i*ans1;
	sort(b+1,b+n+1);
	for(int i=1;i<=ans1;i++) ans2+=b[i];
	cout<<ans1<<" "<<ans2;
	return 0;
}

```


---

## 作者：揽月摘星辰 (赞：2)

这道题目看懂了题，发现求最多的商品数量，那么便自然想到二分答案。在二分答案后，我们便可以求出每个商品实际的花费p[i]，即p[i]=a[i]+x*k，k表示编号，x表示数量，然后判断时sort后贪心即可。




------------


------------
代码：
```
#include<bits/stdc++.h>
using namespace std;
int n,m,a[100005],p[100005],num,ans=0;
bool check(int x)//判断可行性
{
	int i;
	num=0;
	for(i=1;i<=n;i++)
	{
		p[i]=a[i]+i*x; //求实际花费
	}
	sort(p+1,p+1+n);   //排序
	for(i=1;i<=n;i++)
	{
		num+=p[i];
		if(num>m){
			return 0;
		}
		if(i==x)return 1;
	}          //贪心判断是否可行，贪心应该都懂吧
}
int main()
{
	scanf("%d%d",&n,&m);
	int i,j;
	for(i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	int l=0,r=n;
	while(l<r)
	{
		int mid=l+r+1>>1; //注意二分界限判断
		if(check(mid))
		{
			ans=num;
			l=mid;
		}
		else r=mid-1;    //注意界限判断
	}
	printf("%d %d",l,ans);
	return 0;
}
```


---

## 作者：ridewind2013 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF812C)

## 思路

题目让计算出最多能买多少个纪念品，可以想到二分答案。

要将左右边界设为 $0$ 到 $n$。

二分时，把每个纪念品的实际花费计算出来，升序排序，取出前 $mid$ 个，判断总和是否比 $S$ 小，如果可以，将答案 $ans$ 变为 $mid$。


最后，计算总花费，将买 $ans$ 个纪念品时每个纪念品的花费计算出来，升序排序，将前 $ans$ 个累加起来。

## AC Code


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,s,a[100010],c[100010];
bool check(int x){//判断是否可以 
	int sum=0;
	for(int i=1;i<=n;i++)c[i]=a[i]+i*x;
	sort(c+1,c+n+1);
	for(int i=1;i<=x;i++)sum+=c[i];
	return sum<=s;
}
int main(){
	cin>>n>>s;
	for(int i=1;i<=n;i++)cin>>a[i];
	int l=0,r=n,ans=0,sum=0;
	while(l<=r){//二分 
		int mid=l+r>>1;
		if(check(mid)){
			ans=mid;
			l=mid+1;
		}else r=mid-1;
	}
	for(int i=1;i<=n;i++)c[i]=a[i]+i*ans;
	sort(c+1,c+n+1);
	for(int i=1;i<=ans;i++)sum+=c[i];
	cout<<ans<<" "<<sum;//输出答案 
	return 0;
}
```

---

## 作者：AntonyD (赞：1)

[CF812C Sagheer and Nubian Market传送门](https://www.luogu.com.cn/problem/CF812C)

~~这道题听说很水~~ 但是这不妨碍本蒟蒻不会(逃

毕竟是熬了很久，所以来发篇题解纪念一下

## 解题思路

这道题目是一道二分搜索的题目。我们需要找到一个最大的数 $k$，使得购买 $k$ 个物品的总花费不超过 $S$。我们可以使用二分搜索来找到这个 $k$。我们将 $k$ 的可能值的范围设定在 $0$ 到 $n$，然后在这个范围内进行二分搜索。

在进行二分搜索的过程中，我们需要一个函数来检查对于当前的 $k$，是否存在一种购买方案使得总花费不超过 $S$。我们可以通过计算每个物品的实际花费（即基本花费加上它的下标乘以 $k$），然后取最小的 $k$ 个物品的花费总和，来检查是否存在这样的购买方案。

如果存在这样的购买方案，那么我们就可以尝试增大 $k$ 的值；如果不存在这样的购买方案，那么我们就需要减小 $k$ 的值。通过这样的方式，我们可以找到最大的满足条件的 $k$。

## 代码解析

首先，我们定义了一些变量和数组来存储输入的数据和中间结果。`itemCount` 和 `totalCost` 分别用来存储物品数量和总预算。`itemCost` 数组用来存储每个物品的基本花费。`actualCost` 数组用来存储每个物品的实际花费。

`check` 函数用来检查对于当前的 $k$，是否存在一种购买方案使得总花费不超过 $S$。它首先计算每个物品的实际花费，然后对实际花费进行排序。然后，它取最小的 $k$ 个物品的花费总和，如果这个总和不超过 $S$，那么就返回 `true`，否则返回 `false`。

在 `main` 函数中，我们首先读入输入的数据。然后，我们在 $0$ 到 $n$ 的范围内进行二分搜索，找到最大的满足条件的 $k$。在二分搜索的过程中，我们使用 `check` 函数来检查当前的 $k$ 是否满足条件。如果满足条件，那么我们就尝试增大 $k$ 的值；如果不满足条件，那么我们就减小 $k$ 的值。最后，我们输出找到的 $k$ 和对应的最小总花费。

## 以下是 AC 代码并附上详细的注释

```c++
#include <iostream>
#include <algorithm>
using namespace std;

const int MAX = 1e5 + 10;
int itemCount, totalCost, count, answer, totalSpent;  // 定义全局变量
int itemCost[MAX], actualCost[MAX];  // 定义全局数组

// 定义一个检查函数，通过二分查找的方式，来检查中间值是否满足条件
inline bool check(int middle){
    // 计算每个商品的实际花费
	for(int i = 1; i <= itemCount; i++)
		actualCost[i] = itemCost[i] + i * middle;
    // 对实际花费进行排序
	sort(actualCost + 1, actualCost + 1 + itemCount);
	totalSpent = 0;
    // 计算购买 middle 件商品的总花费
	for(int i = 1; i <= middle && totalSpent <= totalCost; i++)
		totalSpent += actualCost[i];
    // 如果总花费小于等于预算，则返回 true
	return totalSpent <= totalCost;
}

int main(){
    // 输入商品数量和预算
	cin >> itemCount >> totalCost;
    // 输入每个商品的基本花费
	for(int i = 1; i <= itemCount; i++)
		cin >> itemCost[i];
	int left = 0, right = itemCount;
    // 通过二分查找，找出最大的满足条件的商品数量
	while(left <= right){
		int middle = (left + right) / 2;
        // 如果中间值满足条件，则更新答案，并将左边界移动到中间值的右边
		if(check(middle)){
            count = middle, answer = totalSpent, left = middle + 1;
        }
        // 否则将右边界移动到中间值的左边
		else right = middle - 1;
	}
    // 输出最大的商品数量和最小的总花费
	cout << count << " " << answer << endl;
	return 0;
}

```

---

## 作者：傅思维666 (赞：1)


## 题解：

[博客食用口味更佳](https://www.cnblogs.com/fusiwei/p/11775563.html)

~~2019.11.1模拟赛T1 60分场~~

感谢出题人给我一次重新再来的机会改到了100分。

一开始看到这道题，往DP那里想了想，后来发现明显不行，因为这道题还需要统计最多拿多少件以及拿这些件的钱数。这些信息仅用DP是维护不了的。

然后考虑贪心。贪心思路是从$n-1$枚举，反复更新当前状态下所有物品的实际价值，然后排序判断合法与否，如果合法，那么当前状态一定是最优解，直接输出$exit$就好。

时间复杂度的话应该是$O(n^2+nlogn)$（把排序算上了）过不了全部数据，只能拿60分。

后来出题人@zcs0724友情提示是二分。

所以这道题一下子就显得没难度了。我们二分的对象是**最多拿多少个**（这是显然的，因为最多拿多少个决定了钱数）。那么我们二分的区间就是$0-n$，注意要考虑0的情况（样例3不是特判过的）。然后$check()$函数的写法思路是和暴力思路一样的。退出二分的时候统计当前状态（最优解状态）的答案即可。

简单总结一下，我们的暴力思路是枚举判断，正解思路是二分判断，显然二分可以优化枚举的效率。这道题也是因此而把复杂度降到了log级别，然后得以AC的。所以与其把这道题说成贪心+二分，还不如说成暴力枚举的优化。（当初和七哥@littleseven讨论的时候说起了Log级别的算法，硬是没想到二分，我太菜了）

代码：

```cpp
#include<cstdio>
#include<algorithm>
#define int long long
using namespace std;
const int maxn=1e5+1;
int n,s,temp,ans;
int l,r;
struct node
{
    int a,t,order;
}p[maxn];
bool cmp(node a,node b)
{
    return a.t<b.t;
}
bool check(int x)
{
    temp=0;
    for(int j=1;j<=n;j++)
        p[j].t=p[j].a+p[j].order*x;
    sort(p+1,p+n+1,cmp);
    for(int j=1;j<=x;j++)
        temp+=p[j].t;
    if(temp<=s)
        return 1;
    return 0;
}
signed main()
{
    scanf("%lld%lld",&n,&s);
    for(int i=1;i<=n;i++)
    {
        scanf("%lld",&p[i].a);
        p[i].order=i;
    }
    l=0,r=n;
    while(l<r)
    {
        int mid=(l+r+1)/2;
        if(check(mid))
            l=mid;
        else
            r=mid-1;
    }
    printf("%lld ",l);
    for(int i=1;i<=n;i++)
        p[i].t=p[i].a+p[i].order*l;
    sort(p+1,p+n+1,cmp);
    for(int i=1;i<=l;i++)
        ans+=p[i].t;
    printf("%lld",ans);
    return 0;
}
```



---

## 作者：wangchuyue (赞：0)

## CF812C题解
#### 题意：

在一个长度为 $n$ 的数组中选 $k$ 个数，使得选出的数加数的下标乘 $k$ 的和小于 $S$ 的方案中 $k$ 最大，和最小的方案。

#### 题目难点：

这题于一般的选数题不同在于多了下标乘个数的和，用一般的排序后直接从小开始加不同，这题的数直接排会出现 $A_x > A_y$ 但因为 $x < y$ 所以 $k$ 一旦很大就要优先选 $A_x$ 的情况。 

#### 解决方法:

既然 $k$ 的大小会影响排序结果，我们不妨用二分答案二分 $k$ ，知道了 $k$ 的大小，这题就转变成了普通的选数题，直接排序 $+$ 累加即可。

###### 说了那么多，该上代码了。
#### 代码:
```
#include<bits/stdc++.h>
#define int long long
#define f(i,x,y) for(int i=x;i<=y;i++)
#define d(i,x,y) for(int i=x;i>=y;i--)
using namespace std;
int n,s,sum,ans=LONG_LONG_MAX,cnt,a[500001],b[500001];
bool check(int k)
{
    sum=0;
    memset(b,0,sizeof b);
    f(i,1,n)b[i]=a[i]+i*k;
    sort(b+1,b+n+1);
    f(i,1,k)sum+=b[i];
    if(sum<s)
    {
        ans=sum;
        return true;
    }
    else return false;
}//排序+累加
signed main()
{
//  freopen("b.in","r",stdin);
//  freopen("b.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>s;
    f(i,1,n)cin>>a[i];
    int l=1,r=n;
    while(l<=r)
    {
        int mid=(l+r)/2;
        if(check(mid))cnt=mid,l=mid+1;
        else r=mid-1;
    }//二分答案
    if(ans==LONG_LONG_MAX)cout<<0<<' '<<0;
    else cout<<cnt<<' '<<ans<<endl;
    return 0;
}
```
##### 谢谢观看

---

## 作者：WaterSky (赞：0)

# [CF812C Sagheer and Nubian Market](https://www.luogu.com.cn/problem/CF812C)
## 前言：
写题解的时候突发~~恶疾~~奇想，想到了一种新颖的题解格式，所以可能有点非主流。

## 前置知识：
二分查找也称折半查找，它是一种效率较高的查找方法。但是，折半查找要求线性表必须**采用顺序存储结构**，而且表中元素按关键字**有序排列**。

其前提条件是：
- 顺序性：二分查找要求被查找的数据必须是按某种顺序（升序或降序）排列的。
- 单调性：数据的单调性（即序列可以是单调不减或单调不增）也是进行二分查找的一个重要前提。这意味着序列中的元素要么严格递增，要么严格递减。
## 简要题面：
给出 $n$ 个数，如果选择 $k$ 个数，对于其中每一个数而言其代价为**自身的价值加上下标乘购买总数**即 $k$。要求在代价不超过 $S$ 的情况下选择更多的数，求可选择最多的数量以及在最多数量的情况下最小的代价。

## 问答式讲解：
- 问：是怎么想到用二分的？
> 答：在题目中的：“要求在代价不超过 $S$ 的情况下选择更多的数，求可选择最多的数量以及在最多数量的情况下最小的代价。”得出启发。
- 问：二分什么？
> 答：题目所求的值是选择最多的数量，其次是这种情况下的最小代价，通过尝试可以发现，二分数量会更加容易。
- 问：在二分的判断程序中怎么选择最优？
> 答：对于不同的数而言由于不同的选择数量有不同的价值，所以可以再开一个数组 $b$，使 $b$ 数组记录每一次二分后每一个商品的价值，再进行升序排序，最后的选择就是本次二分最优的结果。 
## 代码：
```
#include<bits/stdc++.h>
using namespace std;
long long n,S;
long long a[100005],b[1000005];//b数组记录每一次二分后的价值
long long check(long long x)//判断函数，这里建议别用bool，这样可以让第二问更加容易实现。
{
	long long t=0;
	for(int i=1;i<=n;i++)
		b[i]=a[i]+i*x;
	sort(b+1,b+1+n);//降序排序以保证最优
	for(int i=1;i<=x;i++)
		 t+=b[i];
	return t;
}
int main()
{
	cin>>n>>S;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	long long start=0,finish=n+1,mid;//二分模板
	while(start+1<finish)
	{
		mid=(start+finish)/2;
		if(check(mid)<=S) start=mid;
		else finish=mid;
	}
	cout<<start<<" "<<check(start);
	return 0;
}
```
## 总结：
这是一道二分答案的基础题，应该一次过。

最后感谢管理员的审核。

---

## 作者：kanzaki (赞：0)

## 题目分析
题目输入商品总数  $n$ 和最大钱数 $s$，要求算出最大购买的纪念品数量和最小总花费。


## 思路
求最大和最小的数，优先考虑使用二分算法。

观察题目，可以通过二分算出最大纪念品数量。

二分时设置一个变量用于单独存储最小总花费即可满足题目要求。

想要买到最多的商品数，就要从单价最低的商品开始买。求完所有商品单价后从小到大排序即可。

需要注意的是，本题商品价格不是输入的价格，需要再次计算得出。


## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define maxn 100005
int a[maxn],b[maxn],cost,n,s,mid,num,ans;
bool check(int mid){
	cost=0;//cost代表当前花费 
	for(int i=1;i<=n;i++){
		b[i]=a[i]+mid*i;//b数组存储实际价钱 
	}
	sort(b+1,b+n+1);
	for(int i=1;i<=mid&&cost<=s;i++){
		cost+=b[i];
	}
	return cost<=s;
}
int main(){
	cin>>n>>s;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	int l=1,r=n;
	while(l<=r){//二分求出最大数量和最小价钱 
		mid=l+(r-l)/2;
		if(check(mid)){
			l=mid+1;
			num=mid;
			ans=cost;
		}
		else r=mid-1;
	}
	cout<<num<<" "<<ans;
	return 0;
} 
```

---

