# Renting Bikes

## 题目描述

A group of $ n $ schoolboys decided to ride bikes. As nobody of them has a bike, the boys need to rent them.

The renting site offered them $ m $ bikes. The renting price is different for different bikes, renting the $ j $ -th bike costs $ p_{j} $ rubles.

In total, the boys' shared budget is $ a $ rubles. Besides, each of them has his own personal money, the $ i $ -th boy has $ b_{i} $ personal rubles. The shared budget can be spent on any schoolchildren arbitrarily, but each boy's personal money can be spent on renting only this boy's bike.

Each boy can rent at most one bike, one cannot give his bike to somebody else.

What maximum number of schoolboys will be able to ride bikes? What minimum sum of personal money will they have to spend in total to let as many schoolchildren ride bikes as possible?

## 说明/提示

In the first sample both schoolchildren can rent a bike. For instance, they can split the shared budget in half (5 rubles each). In this case one of them will have to pay 1 ruble from the personal money and the other one will have to pay 2 rubles from the personal money. In total, they spend 3 rubles of their personal money. This way of distribution of money minimizes the amount of spent personal money.

## 样例 #1

### 输入

```
2 2 10
5 5
7 6
```

### 输出

```
2 3
```

## 样例 #2

### 输入

```
4 5 2
8 1 1 2
6 3 7 5 2
```

### 输出

```
3 8
```

# 题解

## 作者：Allanljx (赞：1)

## 思路
对于第一个问题，二分能租到的最多的车，然后贪心。将自己的钱比较多的人和比较便宜的车进行匹配，然后让钱少的人买便宜的车。第二个问题和匹配顺序没有关系，可以用总钱数减去公共的钱。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,k,ans;
int b[100005];
int p[100005];
bool check(int x)
{
	sort(b+1,b+x+1);
	int sum=0;
	for(int i=1;i<=x;i++)//便宜的车和钱少的人匹配 
	{
		sum+=max(0ll,p[i]-b[i]);
	}
	if(sum>k) return 0;
	else return 1;
}
signed main()
{
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>b[i];
	}
	for(int i=1;i<=m;i++)
	{
		cin>>p[i];
	}
	sort(p+1,p+m+1);
	int l=0,r=min(n,m);
	while(l<=r)//二分 
	{
		sort(b+1,b+n+1,greater<int>());
		int mid=(l+r)/2;
		if(check(mid)) ans=mid,l=mid+1;
		else r=mid-1;
	}
	cout<<ans<<' ';
	int sum=0;
    for(int i=1;i<=ans;i++) sum+=p[i];
    cout<<max(0ll,sum-k);
}
```

---

## 作者：pengzy (赞：0)

### 思路
第一问显然是 二分和贪心。因为答案具有单调性，我们二分可以买的车辆数，写一个判断函数。先对车价进行排序，显然要买的是最便宜的 $x$ 辆车，然后我们用钱最多的 $x$ 个人去花。

第二问这个翻译不太能理解。题意就是让你尽可能多得去使用公共的钱，用总钱减一下就行。

这个做法比一些每次去排序的代码会少乘一个 $\log n$。

代码：

```cpp
int n,m,a,p[Max],b[Max],l,r,ans1,ans2,t;
bool cmp(int x,int y)
{
	return x>y;
}
bool judge(int x)
{
	int sum=a,pos=x;
	for(int i=1;i<=x;i++) {
		if(b[i]<p[pos--])sum=sum+b[i]-p[pos+1];
		if(sum<0)return 0;
	}
	return sum>=0?1:0;
}
int main()
{
	n=read(),m=read(),a=read();
	for(int i=1;i<=n;i++)b[i]=read();
	for(int i=1;i<=m;i++)p[i]=read();
	sort(p+1,p+1+m);
	sort(b+1,b+1+n,cmp);
	l=0,r=min(n,m);
	while(l<=r) {
		int mid=(l+r)>>1;
		if(judge(mid))l=mid+1,ans1=mid;
		else r=mid-1;
	}
	for(int i=1;i<=ans1;i++)t+=p[i];
	ans2=max(0,t-a);
	cout<<ans1<<' '<<ans2;
	return 0;
}
```

---

## 作者：Loser_Syx (赞：0)

直接贪心很难做，不如考虑二分出一个答案 $x$。

首先 $x$ 肯定是具有单调性的，如果 $s$ 辆车能满足条件那么 $s-1$ 一定满足。

于是可以考虑对于每个 $x$ 进行 `check` 操作，我们如果 $x$ 可行租的一定可以是最便宜的 $x$ 个，而因为要使 $x$ 最大，所以我们让自己钱最多的 $x$ 人从多到少依次租最贵的，不够再用共享的钱。

发现这样可以得知共享的钱使用总数，比较即可。

得到第一个答案 $x$ 之后就知道一定是可以付完排序后的 $b_1 \sim b_x$ 的，记录总和然后再分掉共享的钱就好了。

---

## 作者：tallnut (赞：0)

这题曾经的题解说的挺不清晰的，我就再来写一篇吧。
# 思路
## 第一问
二分答案应该是显而易见的。贪心地选择钱最多的人，匹配花费最少的车，这样可以保证尽可能多的车被选择。

曾经的题解就是不清晰在这里。为什么有时说钱最多的人，有时说钱最少的人呢？

我们为了让车数最大化，需要选择钱最多的人们匹配。但是在这些“富有”的人中，应该让“富者”中的“贫者”匹配开销少的车，免得让最富有的人的钱被浪费。

这就好比“田忌赛马”中的田忌，如果他用上等马去对齐威王的下等马，那他还能取得全盘的胜利吗？
## 第二问
我们现在已经求出了车数的最大值。仍然采用贪心，贪心地选择开销最小的车，把这些车的花费之和与公用部分进行比较即可。
# AC 代码
[AC 记录](https://www.luogu.com.cn/record/140031869)，代码中有注释。
```
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1e5 + 10;
int n,m,a,l,r,mid,ans;
int b[N],tmpb[N],p[N];
bool check(int x)
{
	//把钱最多的x个人进行从小到大排序，钱最多的k个人中钱比较少的与便宜的车匹配
	sort(b + 1,b + x + 1);
	long long sum = 0;
	for (int i = 1;i <= x;i++)
		if (p[i] > b[i]) sum += p[i] - b[i];
	return sum <= a;
}
//从大到小排序
bool cmp(int c,int d) { return c > d; }
int main()
{
	cin >> n >> m >> a;
	for (int i = 1;i <= n;i++)
		cin >> b[i];
	for (int i = 1;i <= m;i++)
		cin >> p[i];
	//对每辆车的价格从小到大排序，贪心地选择
	sort(p + 1,p + m + 1);
	//对每个人的钱数从大到小排序，贪心地选择
	for (int i = 1;i <= n;i++)
		tmpb[i] = b[i];
	sort(tmpb + 1,tmpb + n + 1,cmp);
	//二分模板
	l = 0;
	r = min(n,m);
	while (l <= r)
	{
		//还原到从大到小排序的状态
		for (int i = 1;i <= n;i++)
			b[i] = tmpb[i];
		mid = (l + r) >> 1;
		if (check(mid))
		{
			ans = mid;
			l = mid + 1;
		}
		else r = mid - 1;
	}
	cout << ans << ' ';
	//求解第二问
	long long sum = 0;
	for (int i = 1;i <= ans;i++)
		sum += p[i];
	if (sum > a) cout << sum - a;
	else cout << 0;
}
```

---

## 作者：Doubeecat (赞：0)

> [CF363D Renting Bikes](https://www.luogu.com.cn/problem/CF363D)
> 
> 有 $n$ 个学生要租车，一共有 $m$ 辆车，每辆车有一个价钱 $p_i$，每个学生有自己的钱 $b_i$，并且他们的钱**只能自己用**，每个人只能租一辆车。他们有 $a$ 公用的钱，求出
> 
> 1. 最多有多少个人能租到车
> 
> 2. 在保证尽量多的人租到车的前提下，每个人出的自己的钱总和最小是多少。
>
> $n \leq 10^5$
<!-- more -->

## 解题思路：

二分 + 贪心

这两个问题其实可以分开来解决，我们首先考虑第一个问题。

记最多有 $x$ 个人可以租到车，显然这个 $x$ 满足单调性，所以考虑二分解决。

现在问题转化成了，如何判断是否能让 $x$ 个人租到车？

这里的问题看上去范围就不是很好 DP，所以我们考虑贪心。

一个错误的贪心思路是：先尽量用班级的钱，花到不能买下整个时再去拼凑后面的车。样例 2 就可以 hack 掉。

然而，我们依然可以从这里得到一些对我们有意义的东西。**拼凑**一辆车是一个非常重要的思路，为了尽量多，我们要对于每辆车思考一下如何拼凑。

显然，我们选择的 $x$ 辆车必定是最便宜的 $x$ 辆车，这个证明十分简单，~~当然也可以感性理解~~。

接下来就是考虑人的问题了，因为每个人对于整个答案的贡献都是 1，所以哪个人选哪个车对答案是没影响的。同理，我们也想一下如何让人选车最优。

一个不那么显然但是正确的方案：让钱最多的 $x$ 个人，按照从少到多的顺序来买车。

证明：

我们有 $k$ 个男孩 $a_1 \dots a_k$ 和 $k$ 个自行车 $b_1 \dots b_k$，是否有其他方案让我们用更少的钱。

取一组 $i,j(i < j)$，令 $a_i$ 买 $b_i$， $a_j$ 买 $b_j$ 然后讨论是否需要交换他们（也就是$a_j$ 买 $b_i$， $a_i$ 买 $b_j$）

情况1. 若 $a_i \geq b_i$，则有 $a_i,a_j \geq b_i$,所以这里肯定用 $a_i$ 买 $b_i$，$a_j$ 买 $a_j$ 最好，不用交换。

情况2. 若 $a_i < b_i$，则不论 $b_i > a_j$ 还是 $b_i \leq a_j$，交换都不会让结果变得更好，所以不用交换。

所以，我们可以用这个结论写出 check

```cpp

bool check(int x) {
    int nk = k;//当前剩下的通用钱数
    int pos = x;//从第x小到最小枚举
    for (int i = 1;i <= x;++i) {
        if (b[i] < p[pos--]) {//如果钱不够，就用通用钱去填
            nk = nk + b[i] - p[pos+1] ;
        }
        if (nk < 0) return 0;//如果发现坑太大，填不上了，则说明 x 不行
    }
    //if (nk >= 0) printf("ans:%d\n",x);
    return nk >= 0 ? 1 : 0 ;//最后记得再判断一次
}

```

对于第二问，从第一问的贪心中我们可以发现我们怎么选择的并不重要，只要考虑最后的结果就行，

记选择车辆的总价钱为 $p_{total}$ , 答案就是 $p_{total} - k$

## 代码：

```cpp
inline bool cmp(int x,int y) {return x > y;}

bool check(int x) {
    int nk = k,pos = x; 
    for (int i = 1;i <= x;++i) {
        if (b[i] < p[pos--]) {
            nk = nk + b[i] - p[pos+1] ;
        }
        if (nk < 0) return 0;
    }
    return nk >= 0 ? 1 : 0 ;
}

int main() {
    read(n,m,k);
    for (int i = 1;i <= n;++i) read(b[i]);
    for (int i = 1;i <= m;++i) read(p[i]);
    sort(b+1,b+1+n,cmp);sort(p+1,p+1+m);
    int l = 0,r = min(n,m),ans = 0;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (check(mid)) ans = mid,l = mid + 1;
        else r = mid - 1;
    }
    int sum = 0;
    for (int i = 1;i <= ans;++i) sum += p[i];
    printf("%d %d",ans,max(0,sum - k));
    return 0;
}
```




---

## 作者：流绪 (赞：0)

两个问题:第一最多买几辆车,第二买这么多车花的最少个人的钱是多少
(翻译有点不准确)

第一个问题很显然可以二分来解决

买最多的车,先不管第二个问题,我们考虑让每个人的钱都尽可能的使用
那么我们先对每个人的钱从大到小排,对车价从小到大排
然后二分找到每一个可能的买车量,对此进行判断能不能够成立
求出最多买几辆车后,设它是n,我们贪心地把最便宜的 n 辆车买了并且把共有的钱全用了,所以买车的钱减去共有的钱就是花的最少个人的钱了

一些细节注释在代码里了

下面是 AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 100010
int b[maxn],c[maxn];
int n,m,a;
bool check(int x)
{
	int sum = a;
	int p=x;//最富的 x 个人买 p 辆车
	for(int i=1;i<=x;i++)
	{
		if(sum <0)
			return 0;//还没买 x 辆,共有的钱就不够用了,所以不行
		if(b[i] < c[p])
			sum-=c[p]-b[i];//共有的钱补给差价
		p--;
	}
	if(sum >= 0)
		return 1;//够用
	return 0;
}
bool cmp(int a,int b)
{
	return a>b;
}
int main()
{
	ios::sync_with_stdio(false);
	cin >> n>> m >>a;
	for(int i=1;i<=n;i++)
		cin >> b[i];
	for(int i=1;i<=m;i++)
		cin >> c[i];
	sort(b+1,b+1+n,cmp);
	sort(c+1,c+1+m);
	int l=0,r=min(n,m),mid;
	while(l<=r)
	{
		mid = (l+r)/2;
		if(check(mid))
			l=mid+1;
		else
			r=mid-1;
	}
	int sum = 0;
	for(int i=1;i<=l-1;i++)
		sum+=c[i];
	cout << l-1 << " " << max(sum-a,0);
}
```


---

