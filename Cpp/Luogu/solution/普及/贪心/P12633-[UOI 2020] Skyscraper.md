# [UOI 2020] Skyscraper

## 题目背景

1s 256M

## 题目描述

Cossack Vus 住在一座摩天大楼里。

自从他开始从事建筑工作以来，$n$ 位客户委托他建造 $n$ 座摩天大楼。其中一座应距离 Cossack Vus 的摩天大楼 1 公里，另一座应距离 2 公里，第三座应距离 3 公里，以此类推。所有摩天大楼（包括 Cossack 的）必须位于同一条直线上，且他的摩天大楼位于最左侧。

第 $i$ 位客户希望他的摩天大楼高度为 $a_i$。然而，客户并不关心他们的摩天大楼距离 Vus 的摩天大楼有多远。因此，Cossack 可以自行决定其他摩天大楼相对于他的摩天大楼的建造顺序。

Cossack Vus 希望从他的摩天大楼看到的景色尽可能美丽。我们假设某一座摩天大楼的第 $i$ 层只有在没有其他摩天大楼的遮挡时，才能从 Vus 的摩天大楼看到。Cossack Vus 认为第 $i$ 座摩天大楼的每一层的美观度为 $b_i$。因此，他希望从他摩天大楼看到的所有楼层的总美观度尽可能大。

![](https://cdn.luogu.com.cn/upload/image_hosting/uh2smivm.png)

一个 $n=4$ 的例子。

图中展示了一个 $n=4$ 的例子。在 1 公里处建造了一座 2 层的摩天大楼，美观度为 $4$；接着是一座 1 层的摩天大楼，美观度为 $2$；然后是一座 3 层的摩天大楼，美观度为 $1$；最后是一座 4 层的摩天大楼，美观度为 $3$。从 Vus 的摩天大楼只能看到第一座摩天大楼的两层、第三座摩天大楼的第三层和第四座摩天大楼的第四层。因此，这些楼层的总美观度为 $4+4+1+3=12$。注意，这可能不是最优的建造顺序。

帮助他找到可能的最大美观度。

## 说明/提示

- （$10$ 分）$1 \leq n \leq 10$，$1 \leq a_i \leq 10$，$1 \leq b_i \leq 10$；
- （$27$ 分）$1 \leq n \leq 10^3$，$1 \leq a_i \leq 10^3$，$1 \leq b_i \leq 10^3$；
- （$25$ 分）$1 \leq n \leq 10^3$，$1 \leq a_i \leq 10^9$，$1 \leq b_i \leq 10^9$；
- （$38$ 分）无额外限制。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
4
2 1 3 4
4 2 1 3```

### 输出

```
14```

## 样例 #2

### 输入

```
6
1 10 3 9 8 2
8 3 2 4 5 6```

### 输出

```
51```

# 题解

## 作者：Lonely_Peak (赞：3)

## 题目大意
有 $n$ 座大楼需要建造，每座大楼都有两个属性：高度与美观度。这些大楼都建在同一条直线上。我们需要找到一种排序的方法，使得从左往右看这些大楼，所有可见楼层的总美观度最大。

## 解题思路
这道题可以通过贪心法来做，我们只需要找到一种排序方法，使得总美观度最大，然后再计算总美观度即可。

为了最大化总美观度，我最开始想的是尽量让高的摩天大楼在后面，这样前面的摩天大楼较矮，后面的摩天大楼较高，可以让更多的楼层被看见。但是有个问题，要是出现像题中举出的例子中的摩天大楼，被遮挡的部分美观度较小，损失小于回报。

那么应该怎么办呢？经过思考，我猜测最优策略可能是将摩天大楼按照美观度降序排列，如果美观度相同则按高度升序排列。因为这样可以使价值大的先被看见，使得总美观度尽量大。

来通过输入输出样例验证一下：

对于样例输入#1：
- 排序后的大楼为 $(2,4)$，$(4,3)$，$(1,2)$，$(3,1)$。
- 那么总美观度就是 $4\times 2 + 2\times 3 = 14$。正确。
  
对于样例输入#2：
- 排序后的大楼为 $(1,8)$，$(2,6)$，$(8,5)$，$(9,4)$，$(10,3)$，$(3,2)$。
- 那么总美观度就是 $8\times 1 + 6\times 1 + 5\times 6+4\times 1+3\times1 = 51$。正确。

那么，我们的程序应该完成以下内容：
1. 将摩天大楼按照美观度降序排列。如果美观度相同，则按照高度升序排列。
2. 遍历排序后的摩天大楼，对于每个摩天大楼：如果它的高度 $h$ 大于已看到的最大高度 $maxh$，则它的可见楼层数是 $h - maxh$，美观度为 $w \times (h - maxh)$（$w$ 为当前大楼的美观度）。更新 $maxh$ 为当前摩天大楼的高度 $h$。

## 参考代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define Rint register int
#define fast_running ios::sync_with_stdio(false),std::cin.tie(0),std::cout.tie(0)
using namespace std;
const int W = 1e5 + 5;
struct building {
	int high, vis;
} a[W];
int n, ans;
bool cmp(building x, building y) {
	if (x.vis == y.vis) return x.high < y.high;
	else return x.vis > y.vis;
} //首先按照 vis 降序排列。如果 vis 相同，则按照 high 升序排列。
signed main() {
	fast_running;
	cin >> n;
	for (Rint i = 1; i <= n; i++) cin >> a[i].high;
	for (Rint i = 1; i <= n; i++) cin >> a[i].vis;
	sort(a + 1, a + n + 1, cmp);  //使用 cmp 函数对摩天大楼进行排序。 
	int maxn = 0;
	for (Rint i = 1; i <= n; i++) {  //计算总美观度
		if (a[i].high > maxn) {
			ans += a[i].vis * (a[i].high - maxn);
			maxn = a[i].high;
		}
	}
	cout << ans << '\n';
	return 0;
}
```

[~ 完结撒花 ~](https://www.luogu.com.cn/record/218727545)

---

## 作者：guoshengyu1231 (赞：1)

# 题解：P12633 [UOI 2020] Skyscraper
## 题意
这个问题可以抽象为一个关于如何排列摩天大楼以最大化可见层美观度总和的优化问题。我们需要找到一种排列顺序，使得从最左侧的摩天大楼看过去时，未被遮挡的楼层总美观度最大。
## 思路
首先看到“最大”俩字，我们应该第一个想到的就是贪心。很明显，这道题显然可以用贪心来做。 $\\$ 
接下来我们需要考虑如何进行贪心，换句话说就是去明确贪心的依据。经过思考，我们可以找到两种贪心选择方案。 $\\$ 
1. 按照高度从小到大排序：看到这题，大家的第一反应应该是让建筑高度按从小到大排序，因为这样子所有的建筑都可以被看到。有可能这并不是对的，但我们总得去试一下。如果是按照高度从小到大排序，那么输入进行排序后就变成了这样：
    ```cpp
    4
    1 2 3 4
    2 4 1 3
    ```
    如果是这么排的话，那么最终的美观度就等于 $2+4+1+3=10$。与输出不符。 $\\$
   那接下来我们就要思考这是为什么？我们可以观察到，如果按照第一种方案的思想来的话，那无论是好看的还是难看的建筑都为被观察到，而且最好看的建筑只会展示几层的美观度，还有几层还可能被前面难看的建筑给遮住。所以先让好看的建筑多展示几层，那还得让建筑的美观度从大到小排序。

2. 按照美观度从大到小排序：此时输入进行排序后就变成了这样：
    ```cpp
    4
    2 4 1 3
    4 3 2 1
    ```
  如果这么排的话，那么最终的美观度就等于 $2\times 4+2\times 3=14$，与输出相符。当然，大家还可以多测几个数据，可以发现这么贪心确实是正确的。
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long//不开long long见祖宗
int n;
struct node{
	int h;
	int x;
}a[100005];//h记录高度，x记录美观度
bool cmp(node a,node b)
{
	return a.x>b.x;
}
//贪心选择方式
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i].h;
	for(int i=1;i<=n;i++) cin>>a[i].x;
	sort(a+1,a+n+1,cmp);
	int ma=0,ans=0;
  //ma代表i之前最高建筑的高度，ans为最终答案
	for(int i=1;i<=n;i++)
	 {
	 	if(a[i].h<ma) continue;//如果比ma的高度小，就被遮住了，跳过。
	 	ans+=(a[i].h-ma)*a[i].x;//答案加上未被遮住的部分×美观度
	 	ma=a[i].h;//更新最大值
	 }
	cout<<ans;
	return 0;
}
```

---

## 作者：LG086 (赞：1)

$n$ 个房子，第 $i$ 个高 $a_i$，每一层的美观度是 $b_i$。房子间会遮挡。我们需要改变房子建造顺序，求出看到的所有楼层最大的美观度是多少。

为了让美观度最大，我们需要使 $b_i$ 更大的房子尽可能先造。同时因为房子之间会互相遮挡，所以 $a_i$ 小的房子，即更矮的房子应该先造。

为了便于排序，我们需要一个结构体存房子的高度和房子每层的美观度。排序方式就是先按美观度的大小来排列，再按楼房高度排。

排序之后，从头遍历。我们使用 $lst$ 记录在第 $i$ 个房子之前的房子的最大高度，$ans$ 存答案。每到达一个房子，如果 $lst<a_i$，则 $ans$ 的值需要增加 $(a_i-lst)\times b_i$，同时更新 $lst \leftarrow a_i$。

最后输出 $ans$ 即可。

核心代码如下。

```cpp
stable_sort(a+1,a+1+n,B);
for(int _=1;_<=n;_++)
 ans+=max(a[_].h-lst,0ll)*a[_].val,lst=max(lst,a[_].h);
```

---

## 作者：Kratos_Charger (赞：1)

## P12633 [UOI 2020] Skyscraper 题解

### 题目大意

有 $n$ 座摩天大楼需要建造，每座大楼有一个高度 $a_i$ 和每层的美观度 $b_i$。这些大楼必须建在一条直线上，距离起点分别为 $1$ 到 $n$ 公里。现在要安排它们的建造顺序，使得从起点能看到的所有楼层的美观度之和最大。一座大楼的某一层能被看到，当且仅当它没有被前面的大楼遮挡（即它的高度严格大于前面所有大楼的高度）。

### 思路

贪心。

为了使总美观度最大化，需要尽量让那些 $b_i$ 大的大楼尽可能多地贡献它们的楼层。如果一个大楼的 $b_i$ 很大，应该尽量让它不被前面的高楼遮挡，这样它的所有楼层都能被看到。

按照 $b_i$ 从大到小的顺序来处理大楼。对于每个大楼，如果它的高度大于之前所有大楼的最大高度，那么它能贡献 $(a_i - \text{当前最大高度}) \times b_i$ 的美观度。

### Code

推荐使用结构体。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=100005;
int n;
struct build{int a,b;}a[N];
bool cmp(build p,build q){
    if(p.b!=q.b) return p.b>q.b;
    return p.a>q.a;
}
signed main(){
    scanf("%lld",&n);
    for(int i=0;i<n;i++) scanf("%lld",&a[i].a);
    for(int i=0;i<n;i++) scanf("%lld",&a[i].b);
    sort(a,a+n,cmp);
    int maxl=0;
    int ans=0;
    for(int i=0;i<n;i++){
        if(a[i].a>maxl){
            ans+=(a[i].a-maxl)*a[i].b;
            maxl=a[i].a;
        }
    }
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：Eden_star (赞：1)

## 思路
不难想到将单个美丽值最高的放在最前面。

来简单地证明一下。当美丽值最高地在前面时，它所挡住的房子的美丽值总和一定小于它。

所以只需要将输入的数据按照每个楼的美丽值进行排序，在把每栋楼能看到的美丽值总和加起来就行了。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5;
int n;
struct kk{
	int h,s;
}lou[N];
bool cmp(kk x,kk y){
	return x.s>y.s;
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>lou[i].h;
	}
	for(int i=1;i<=n;i++){
		cin>>lou[i].s;
	}
	sort(lou+1,lou+n+1,cmp);
	int ans=0,nh=0;//nh记录当前高度
	for(int i=1;i<=n;i++){
		ans+=max(0LL,lou[i].h-nh)*lou[i].s;
		nh=max(nh,lou[i].h);
//		cout<<ans<<"\n";
	}
	cout<<ans;
	return 0;
}
```
## 注意事项
$1 \leq n \leq 10^3$, $1 \leq a_i \leq 10^9$，$1 \leq b_i \leq 10^9$。

所以 $ans$ 可以达到 $10^{12}$。一定要记得开 $long$ $long$。

---

## 作者：AnOIer (赞：0)

### Solution

不难想到这样一个贪心，我们将美观度最大的楼放在前面，当美观度相等时，两栋楼无论怎么摆放其美观度的和不变，所以可以跳过。

因为被遮住的楼不计入美观度，所以在统计美观度时，设 $i$ 以前的楼高度最大值为 $maxn$，若第 $i$ 栋楼高度大于 $maxn$ 则其贡献的美观度为 $(a_i-maxn)\times b_i$，否则没有贡献。

### Code

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
struct bd{
	int a,b;
}a[100010];
bool cmp(bd a,bd b) {
	return a.b>b.b;
}
signed main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i].a;
	for(int i=1;i<=n;i++) cin>>a[i].b;
	sort(a+1,a+1+n,cmp);
	int ans=a[1].a*a[1].b;
	int maxn=a[1].a;
	for(int i=2;i<=n;i++) {
		if(a[i].a>maxn) {
			ans+=(a[i].a-maxn)*a[i].b;
			maxn=a[i].a; 
		}	
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：W_C_B_H (赞：0)

通过观察样例，我们不难发现：为了让总美观度最大，应该让 $b_i$ 大的楼被建在前面。所以可以使用贪心解决这道题：开一个结构体数组来存放每栋楼的高度和每层的美观度，在将其按照每层美观度降序排序后，按顺序枚举每栋楼，若其高度 $a_i$ 大于其之前的每栋楼的高度的最大值 $h_{\max}$，则将答案增加 $(a_i-h_{\max})\times b_i$，并使 $h_{\max}\gets a_i$ 即可。

时间复杂度 $O(n\log n)$，可以通过本题。记得开 `long long`。

Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define N 100005
int n,ans=0;
struct pos    // 摩天大楼
{
    int h,w;    // 高度, 美观度
}a[N];
bool cmp(pos x,pos y)    // 用于结构体排序的比较函数
{
    return x.w > y.w;
}
signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i].h;
    }
    for(int i=1;i<=n;i++)
    {
        cin>>a[i].w;
    }
    sort(a+1,a+1+n,cmp);
    for(int i=1, maxh=0; i<=n; i++)
    {
        if(a[i].h > maxh)
        {
            ans+=(a[i].h-maxh)*a[i].w;
            maxh=a[i].h;
        }
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：封禁用户 (赞：0)

## 题目大意
[题目传送门](https://www.luogu.com.cn/problem/P12633)
## 题目分析
希望审核大大给过。

这是一道贪心题，也不知道为什么是黄题。

我们可以将 $a$ 数组和 $b$ 数组合起来成为一个结构体，并排序，将美观度高的排在前面，如下：
```cpp
struct node{
	int x,y;
}a[100001];
bool cmp(node a,node b){
	return  a.y>b.y;
}

sort(a+1,a+n+1,cmp);
```
其中一个样例的解法为：
```
4
2 1 3 4
4 2 1 3
```
改为：
```cpp
4 2 //第一个数字为建筑美观度，第二个为建筑高度
3 4
2 1
1 3
```
也就是 $4 \times 2 + 3 \times (4 - 2) + 2 \times 0 + 1 \times 0 = 14$（答案不唯一）

很容易证明**将建筑美观度高的排在前面会增加更多的整体美观度**。最后再将结构体 $a$ 进行循环查找，如果 $a_i$ 的**高度**大于 $\max(a_1 , a_2 , \dots a_{i-1})$，那么就将最大值改为 $a_i$ 的**高度**，再 $(a_i - \max(a_1 , a_2 , \dots a_{i-1})) \times b_i$ 计算美观度总和即可。（$a$ 为建筑高度，$b$ 为建筑美观度）

下面是代码。
## 题目[代码](https://www.luogu.com.cn/record/218746697)
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define uint unsigned long long
#define speed ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
int n,sum;
struct node{
	int x,y;
}a[100001];
bool cmp(node a,node b){
	return  a.y>b.y;
}
signed main(){
	speed
	cin>>n;
	int maxx=0;
	for(int i=1;i<=n;i++)cin>>a[i].x;
	for(int i=1;i<=n;i++)cin>>a[i].y;
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++){
		if(a[i].x>maxx){
			sum+=(a[i].x-maxx)*a[i].y;
			maxx=a[i].x;
		}
	}
	cout<<sum;
	return 0; 
}
```

---

## 作者：Manchester_City_FC (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P12633)

### 题意
有 $n$ 座大楼，每座大楼都有两个属性：高度与美观度。这些大楼都建在同一条直线上。求一种排序的方法，使得从左往右所有可见楼层的总美观度最大。

### 做法
显然的贪心是把美观度高的放前面。证明如下：
+ 首先，如果不是按照美观度降序排列，就肯定有一种更优的排列使得美观度之和更高。
+ 其次，对于美观度相同的大楼，我们无需考虑高度的问题，因为无论如何最高的大楼一定会把后面较低的全部挡住。

贴下代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+1;
int n,ans,t;
struct node{
	int a,b;
}x[N];
bool cmp(node x,node y){
	return x.b>y.b;
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>x[i].a;
	for(int i=1;i<=n;i++) cin>>x[i].b;
	sort(x+1,x+n+1,cmp);
	for(int i=1;i<=n;i++){
		ans+=((x[i].a>t)?x[i].a-t:0)*x[i].b;
		t=max(t,x[i].a);
	}
	cout<<ans;
}
```

---

## 作者：CCY20130127 (赞：0)

## 题目大意：
[Skyscraper](https://www.luogu.com.cn/problem/P12633)

题目传送门！

## 题目分析：
这道题看一眼就知道是贪心！

要想总美观度最大，则美观度高的则要排在前面，所以要将美观度从大到小排序。由题意可知，被遮到的是不算入总美观度的，所以定义 $cnt$ 为当前第 $i$ 个没有被遮到的高度，$maxh$ 为目前为止的最大高度。则 $cnt \times b_i$ 就是第 $i$ 个摩天大楼的美观度，$cnt$  就是 $a_i-maxh$ 没有被遮到的高度。

## 正解：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e5+10;
struct node{
	int he,se; 
}a[N];
int n,maxh,ans,cnt;
bool cmp(node a,node b){
	return a.se>b.se;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i].he;
	for(int i=1;i<=n;i++) cin>>a[i].se;
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=n;i++){
		int k=a[i].he-maxh;
		if(k>0) cnt=k;
		else cnt=0;
		ans+=cnt*a[i].se;
		maxh=max(maxh,a[i].he);
	}
	cout<<ans<<"\n";
	return 0;
}
```

---

## 作者：StarTwinkleTwinkle (赞：0)

## P12633 [UOI 2020] Skyscraper

### Problem

有 $n$ 栋大厦，每栋大厦都有一个高度 $a_i$ 和每层的美观度 $b_i$，所有大厦都在同一直线上，美观度之和为从左向右看能看见的楼层的美观度之和，构造一种这些大厦的排列方式使得美观度之和最大，输出美观和即可。

### Solution
贪心。

考虑答案为每层能看到的加起来，对于每一层只能出一个大厦，对于每个大厦，放在最左面一定都能看见，因为每一层都会有一个美观度，所以直接按照每栋大厦的美观度降序排序，维护前缀最大值，最后算答案即可。


```cpp
#include <bits/stdc++.h>
#define int long long
constexpr int maxn = 1e6 + 7;
int a[maxn], b[maxn], n, Ans, maxx[maxn], p[maxn];
struct node{
	int a, b;
}A[maxn];
inline bool cmp(node a, node b){
	return a.b > b.b;
}
int32_t main(){
	std::cin >> n;
	for(int i = 1; i <= n; i++){
		std::cin >> A[i].a;
	}
	for(int i = 1; i <= n; i++){
		std::cin >> A[i].b;
	}
	std::sort(A + 1, A + n + 1, cmp);
	for(int i = 1; i <= n; i++){
		maxx[i] = std::max(maxx[i - 1], A[i].a);
	}
	for(int i = 1; i <= n; i++){
		Ans += std::max(0ll, A[i].a - maxx[i - 1]) * A[i].b;
	}
	std::cout << Ans << '\n';
	return 0;
} 
```

---

