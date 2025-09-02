# Group Photo 2 (online mirror version)

## 题目描述

Many years have passed, and $ n $ friends met at a party again. Technologies have leaped forward since the last meeting, cameras with timer appeared and now it is not obligatory for one of the friends to stand with a camera, and, thus, being absent on the photo.

Simply speaking, the process of photographing can be described as follows. Each friend occupies a rectangle of pixels on the photo: the $ i $ -th of them in a standing state occupies a $ w_{i} $ pixels wide and a $ h_{i} $ pixels high rectangle. But also, each person can lie down for the photo, and then he will occupy a $ h_{i} $ pixels wide and a $ w_{i} $ pixels high rectangle.

The total photo will have size $ W×H $ , where $ W $ is the total width of all the people rectangles, and $ H $ is the maximum of the heights. The friends want to determine what minimum area the group photo can they obtain if no more than $ n/2 $ of them can lie on the ground (it would be strange if more than $ n/2 $ gentlemen lie on the ground together, isn't it?..)

Help them to achieve this goal.

## 样例 #1

### 输入

```
3
10 1
20 2
30 3
```

### 输出

```
180
```

## 样例 #2

### 输入

```
3
3 1
2 2
4 3
```

### 输出

```
21
```

## 样例 #3

### 输入

```
1
5 10
```

### 输出

```
50
```

# 题解

## 作者：communist (赞：4)

## 贪心
### 枚举最后方案中最大的$h$，设为$maxh$
### 若某个人$i$的$w_i$与$h_i$均大于$maxh$，则此方案不可行
### 若某个人恰有一个属性大于$maxh$，则可确定他是否换属性
### 剩下的人按$w_i-h_i$从大到小排序后贪心选择
## $O(nlogn+n2)$
```
#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int maxn=1010;
int n,w[maxn],h[maxn],hh,ans=1e9,sw;
bool cmp(const int &a,const int &b)
{
	return w[a]-h[a]>w[b]-h[b];		//按wi-hi排序
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&w[i],&h[i]);
		hh=max(w[i],max(hh,h[i])),sw+=w[i];
	}
	for(int maxh=1;maxh<=hh;maxh++)
	{
		int cnt=0,rs=sw;
		vector<int>v;
		for(int i=1;i<=n;i++)	//分类讨论
		{
			if(w[i]>maxh&&h[i]>maxh)
			{
				cnt=1e9;
				break;
			}
			else if(w[i]>maxh&&h[i]<=maxh)
				continue;
			else if(w[i]<=maxh&&h[i]>maxh)
			{
				rs+=h[i]-w[i];
				cnt++;
			}
			else if(w[i]>h[i])
				v.push_back(i);		//把待处理元素放入vector
		}
		if(cnt>n/2)
			continue;
		sort(v.begin(),v.end(),cmp);
		for(int i=0;i<v.size()&&cnt+i<n/2;i++)
			rs+=h[v[i]]-w[v[i]];
		ans=min(ans,rs*maxh);
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Bitter_Tea (赞：3)

基本思路是**贪心+优先队列**

首先，我们发现$h$是一个影响我们答案的重要因素，不好直接处理，并且我们发现$h$值最大只有$1000$，于是我们尝试枚举$h$，进行判断。

**以下把我们枚举的$h$值称为$x$**


首先，我们在进行计算$x$所对应的答案之前需要判断是否可行：

1. 如果所有的$h,w$里没有$x$值，显然是不可以的。

1. 我们用前缀和$s_i$记录出$\le i$的人数。那么如果有$s_{1000}-s_x> \frac{n}{2}$，也就是后面需要躺下的大于$\frac{n}{2}$，那么也是不符合的。

1. 如果某个人的$h,w$都比$x$值大，显然是无法满足的，我们$O(n)$的扫一遍即可。

然后我们的判断工作就完成了，接下来我们需要计算最小值。

1. 如果我们发现每个人$h$中没有$x$值,也就是$x$是一个人的$w$,那么我们需要选取最优的进行躺下操作。

1. 我们对于剩下的人进行贪心的处理：如果一个人的$h$大于$x$，那么必须躺下。否则如果一个人的$w\le x$且$w>h$，那么我们就把$w-h$入堆。最后我们在保证躺下的人$\le \frac{n}{2}$的前提下选取较大的让其躺下即可

### $Code$
```cpp
#include<cstdio>
#include<iostream>
#include<queue>
using namespace std;
const int N=1005,inf=2147483647;
struct D{int w,h;}e[N];
int n,k,h[N],s[N];
bool v[N];
int ans=inf;
void solve(int x)
{
	priority_queue<int> q;//大根堆维护差值 
	int sum=0,ansx=0,c=0,minn=inf;
	if(!h[x])				//如果h没有x，我们寻找一个最优的 
	{
		for(int i=1;i<=n;i++)
		if(e[i].w==x&&e[i].h<inf)
		{
			c=i;
			minn=e[i].h;
		}
		ansx+=minn*x;
		sum++;
	}
	for(int i=1;i<=n;i++)
	{
		if(i==c) continue;
		if(e[i].h>x) {sum++;ansx+=e[i].h*x;continue;}//一定需要躺下 
		ansx+=e[i].w*x;
		if(e[i].w>e[i].h&&e[i].w<=x) 				//可躺可不躺 
		q.push(e[i].w-e[i].h);
	}
	while(q.size()&&sum<k)				//对可躺可不躺的人进行操作 
	{
		sum++;
		int d=q.top();q.pop();
		ansx-=x*d;
	}
	ans=min(ans,ansx);
}
bool judge(int x)
{
	for(int i=1;i<=n;i++)
	if(e[i].h>x&&e[i].w>x) return 0;
	return 1;
}
int main()
{
	scanf("%d",&n);k=n/2;
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&e[i].w,&e[i].h);
		s[e[i].h]++;h[e[i].h]=1;
		v[e[i].w]=1;v[e[i].h]=1;
	}
	for(int i=1;i<=1000;i++)//计算h的前缀和 
	s[i]+=s[i-1];
	for(int i=1;i<=1000;i++)
	{
		if(!v[i]) continue;//是否存在该高度 
		if(s[1000]-s[i]>k) continue;//是否符合躺下的人少于n/2 
		if(!judge(i)) continue;//对应判断的3 
		solve(i);
	}
	printf("%d\n",ans);
	return 0;
}
```

$qwq$









---

## 作者：Happy_mouse (赞：1)

# [Group Photo 2 ](https://www.luogu.com.cn/problem/CF529B) 题解
### 写在前面
CF 的 RemoteJudge 这段时间崩了，在本校 OJ 上测试是 AC，发篇题解~~祭奠~~纪念一下。
## 分析与解答
看到这种题，第一时间肯定会想到贪心或者DP，但发现这题求的是乘积，并非无后效性（两个参数一个变大，一个变小，很难判断乘积的变化）。

考虑固定其中一个参数并进行贪心。

固定哪一个呢？

注意到高度取最大值，而宽度为求和。

显然最大值更好固定，则枚举所有高度，求出该情况的最小面积。

设最大高度为 $high$，每个人分 5 种类型。
1. $h_i>high$ 且 $w_i>high$ 时，无解，不管躺不躺下，都超限。
2.  $h_i\le high$ 且 $w_i>high$ 时，必然站立，否则超限。
3.  $h_i>high$ 且 $w_i\le high$ 时，必然躺下，否则超限。
4.  $h_i\le high$，$w_i\le high$ 且 $w_i>h_i$ 时，必然站立，否则会使宽度变大，面积随之变大。
5.  $h_i\le high$，$w_i\le high$ 且 $w_i\le h_i$ 时，优先选择 $w_i-h_i$ 较大的（也就是说躺下之后缩小宽度更大）。
   
综上，得出代码架构：

`step 1` 求出初始宽度。

`step 2` 枚举最大高度。

`step 3` 对每个人进行遍历。如果为情况 1，无解，直接跳出遍历并枚举下一高度；如果为情况 3，统计必然躺下的人数并记录躺下之后宽度的改变量；如果为情况 5，存入数组，等待排序；如果为情况 2 或 4，不管用他（既不占名额，又不改变宽度）。

`step 4` 对存下来的情况 5 按照躺下之后导致缩小的宽度从大到小排序。

`step 5` 在排完序的数组中选择前【剩下的名额】 个（如果数组里没有那么多就全选），统计改变量并与初始宽度相加。将宽度与 $high$ 相乘，得到此高度的最小面积。注意，此处乘的是 $high$ 而不是选中情况中的最高，毕竟最后在 `step 7` 比较时肯定会被消掉（想想为什么）。

`step 6` 回到 `step 2`，枚举下一高度。

`step 7` 在所有 `step 5` 所求出的面积中取最小，输出。
## 代码
来看代码。

因为已经列出架构，代码中就不过多注释了。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1005;
int w[N],h[N],a[N];
bool cmp(int x,int y){//这个是给情况 5 排序用的
	return w[x]-h[x]>w[y]-h[y];
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n,mh=0,sum=0;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>w[i]>>h[i],mh=max({mh,h[i],w[i]}),sum+=w[i];
	int hfn=n/2,ans=1e9;
	for(int high=1;high<=mh;high++){
		int cnt=0,we=sum,sz=0;
		for(int i=1;i<=n;i++){
			if(h[i]>high&&w[i]>high){//情况 1
				cnt=n+1;//标记
				break;//跳出
			}
			else if(h[i]<=high&&w[i]>high) continue;//情况 2
			else if(h[i]>high&&w[i]<=high) cnt++,we+=h[i]-w[i];//情况 3
			else if(h[i]<w[i]) a[++sz]=i;//情况 5
		}//这里没管情况 4，毕竟本身就没有操作 
		if(cnt>hfn) continue;//判断是否超过允许躺下的人数，无解标记也在这里判了
		sort(a+1,a+sz+1,cmp);
		for(int i=1;i<=min(hfn-cnt,sz)/*前 hfn-cnt，也就是剩余名额，和全选情况（sz）比较*/;i++) we+=h[a[i]]-w[a[i]];
		ans=min(ans,we*high);
	}
	cout<<ans;
	return 0;
}
```
写题解辛苦，路过/认真看过的大佬们都给个赞呗。

---

## 作者：tZEROちゃん (赞：1)

本题的简单版本是 [CF524B](https://www.luogu.com.cn/problem/CF524B)。

考虑简单版本的做法，就是直接贪心，能选小宽就选小宽，具体见简单版题解。

但这个题给了一个躺下的不能超过 $\lfloor \dfrac n 2\rfloor$ 的抽象限制，所以不能直接贪。

我们延续简单版本的做法，枚举高度限制，然后换一种方式贪心。

首先，如果存在一个人，他两个长度都比限制大，那这个情况显然无解，因为你怎么转都放不下，很没素质。

然后你考虑有哪些人需要躺下来，如果一个人的高度超出限制，但宽度没超出，那就躺下来。

然后你记录一下躺下来的人数 $cnt$，如果 $cnt > \lfloor \dfrac n 2\rfloor$，那也显然无解。

这样就一定有合法解了，我们怎么样才能使得答案尽可能优秀呢？

我们可以考虑哪些人是可以改方向的，对于不躺下的人，如果他躺下也没有超出限制，那这个人就可以自由变化！

然后你用一个 `priority_queue` 维护一下 $w_i - h_i$ 的值，把所有躺下更优的躺下来。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define rep(i, l, r) for(auto i = (l); i <= (r); ++i)
#define per(i, r, l) for(auto i = (r); i >= (l); --i)
#define pb push_back
#define fi first
#define se second
#define i64 long long

const int N = 1e3 + 10;
pair<int, int> p[N];
bool v[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n; cin >> n;
  rep (i, 1, n) {
    cin >> p[i].fi >> p[i].se;
  }

  auto calc = [&](i64 lim) -> i64 {
    memset(v, 0, sizeof v); // 0-> 不躺，1-> 躺下
    rep (i, 1, n) {
      if (min(p[i].fi, p[i].se) > lim) return 1e18;
    } // 不合法

    i64 b = 0, cnt = 0; // cnt: 躺下的人数
    rep (i, 1, n) {
      if (p[i].se > lim) {
        b += p[i].se; // 高度超限，所以躺下
        ++cnt;
        v[i] = 1;
      }
    }
    if (cnt > n / 2) return 1e18;
    priority_queue<int> q;
    rep (i, 1, n) if (v[i] == 0) { // 不躺下的人看它躺下来会不会更优
      if (p[i].fi <= lim) q.push(p[i].fi - p[i].se);
      b += p[i].fi;
    }

    i64 f = n / 2 - cnt;
    while (f-- && q.size()) {
      int x = q.top(); 
      if (x < 0) break;
      q.pop();
      b -= x;
    }
    return (i64)b * lim;
  };

  i64 ans = 1e18;
  rep (a, 1, 1008) {
    ans = min(ans, calc(a));
  }
  cout << ans << '\n';
  return ~~(0 ^ 0);
}
```

---

