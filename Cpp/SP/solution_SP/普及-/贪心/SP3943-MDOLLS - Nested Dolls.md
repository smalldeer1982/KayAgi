# MDOLLS - Nested Dolls

## 题目描述

[English](/problems/MDOLLS/en/) [Vietnamese](/problems/MDOLLS/vn/) ```

Dilworth is the world's most prominent collector of Russian nested dolls:
he literally has thousands of them! You know, the wooden hollow dolls of 
different sizes of which the smallest doll is contained in the second smallest,
and this doll is in turn contained in the next one and so forth. One day he
wonders if there is another way of nesting them so he will end up with
fewer nested dolls? After all, that would make his collection even 
more magnificent! He unpacks each nested doll and measures the width 
and height of each contained doll. A doll with width w1 and height h1 will
fit in another doll of width w2 and height h= if and only if w1 < w2 and 
h1 < h2. Can you help him calculate the smallest number of nested dolls 
possible to assemble from his massive list of measurements? 
```

# 题解

## 作者：zjjc1104111 (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/SP3943)

# 思路

### 贪心+二分
我们可以先按照一个参数进行排序，并按照以下规则进行决策：

1. 如果比所有套娃都高，说明目前的套娃都包不住他，那就单独开一个 

```cpp
if(f[ans]<=a[i].h) f[++ans]=a[i].h;
```


2. 二分寻找最小的能包住他的套娃，并替换新的高度

```cpp
f[l]=a[i].h;
```


但由于双重循环容易超时，所以用二分进行优化。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct doll{
	int w,h;
}a[1000001];
int f[1000001];
bool cmp(doll a,doll b){
	if(a.w!=b.w) return a.w<b.w;
	return a.h<b.h;
}
int main(){
	int t,ans=0;
	cin>>t;
	while(t--){
		int m;
		cin>>m;
		for(int i=1;i<=m;i++) cin>>a[i].w>>a[i].h;
		sort(a+1,a+m+1,cmp);//由于是按照宽度排序的，所以就不用再管宽度了
		ans=0;
		for(int i=m;i>=1;i--){//因为是从小到大排的，所以倒着遍历 
			if(f[ans]<=a[i].h) f[++ans]=a[i].h;//
			else{
				int l=1,r=ans,mid;
				while(l<r){
					mid=(l+r)/2;
					if(f[mid]<=a[i].h) l=mid+1;
					else r=mid;
				}
				f[l]=a[i].h; 
			}
		}
		cout<<ans<<"\n";//别忘了换行 
		memset(f,0,sizeof(f));//因为是多组数据，所以记得初始化 
	}
    return 0;
}
```

---

## 作者：Sammy_prime (赞：2)

[SP2943](https://www.luogu.com.cn/problem/SP3943)

# 本题思路

## 贪心

注意本题的排序方法！

找到第一个未用的套娃。

再用一个 $v$ 数组记录一下这个套娃是否用过。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=30005; 
struct Doll{
    int w, h;
}d[N];
int v[N];
bool cmp(Doll p, Doll q){
	if (p.w != q.w) 
		return p.w < q.w;
	return p.h > q.h;
}//按w升序，h降序排序，这是本题的关键之处 
int main(){
    freopen("dolls.in", "r", stdin);
    freopen("dolls.out", "w", stdout);
    int t, n; scanf("%d", &t);
    while (t--){
        scanf("%d", &n);
        for (int i=0; i<n; i++)
            scanf("%d %d", &d[i].w, &d[i].h);
        sort(d, d+n, cmp);
        memset(v, 0, sizeof v);
        int ans=0, tot=0, st;
        while (tot<n){
            for (st=0; v[st]; st++);
		  //找到第一个未用的套娃 
            int hei=d[st].h; 
	   	    v[st]=1; ans++; tot++;
            for (int i=st+1; i<n; i++)
                if (!v[i] && d[i].h>hei) {
                    hei=d[i].h; v[i]=1; tot++;
                }
        }
        printf("%d\n", ans);
    }
    return 0;
}
/*
6
10 2 
10 3
10 4
20 4
20 5
20 6

10 4
10 3
10 2
20 6
20 5
20 4
*/




```


---

## 作者：rainbow_cat (赞：1)

~~不知道为什么这道题和导弹拦截的第二问类似~~  
处理：结构体：
```cpp
struct node{int w,h;}a[200010];
```
### 主要思路：贪心
贪心策略：我们可以先对于高度和宽度中的一个参数进行排序，那么此时我们就不用对这个参数进行考虑。接下来对于每个娃娃，选择一个娃娃套入，为使解最优，我们选择高比他大的娃娃中高最小的（可以理解为让剩余的空间尽可能的大）。为了避免超时，我们可以使用二分算法进行优化：
```cpp
while(l<r)//二分模版
{
    int mid=(l+r)/2;
    if(h[mid]<=a[i].h)l=mid+1;
    else r=mid;
}		
```
在找到合适的娃娃后更新他的高度：```h[l]=a[i].h; ```  
如果没有合适的娃娃则独自成为一个娃娃：```if(h[ans]<=a[i].h)h[++ans]=a[i].h;```    
（注意：由于是多组答案所以数组与答案要进行清空！！！）  
——————————————————————分割线———————————————————————   
完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{int h,w;}a[200010];//定义结构体
int t,n,h[200010],ans;//h[i]代表每个套娃的高度
bool cmp(node x,node y)
{
	if(x.w!=y.w)return x.w<y.w;//这里选择先按宽度排序
	return x.h>y.h;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--)
	{
		ans=0;
		memset(h,0,sizeof(h));//清空
		cin>>n;
		for(int i=1;i<=n;i++)cin>>a[i].w>>a[i].h;//输入，先宽后高
		sort(a+1,a+n+1,cmp);
		for(int i=n;i>=1;i--)
		{
			if(h[ans]<=a[i].h)h[++ans]=a[i].h;
			else
			{
				int l=1,r=ans;
				while(l<r)//二分
				{
					int mid=(l+r)/2;
					if(h[mid]<=a[i].h)l=mid+1;
					else r=mid;
				}			 
				h[l]=a[i].h;//更新高度
			}
		}
		cout<<ans<<'\n';//输出要加换行	
	}	
	return 0;
}
```

---

## 作者：封禁用户 (赞：1)

## 题目描述

[洛谷传送门](https://www.luogu.com.cn/problem/SP3943)

[SPOJ 传送门](https://www.spoj.com/problems/MDOLLS/)

## 算法思路

**贪心+二分**

先按 $w$ 从大到小排序，再按 $h$ 从小到大排序，维护 $h$ 的非降序列。$dp$ 数组是盒子。对每个元素有两种决策：

1：如果当前 $h$ 大于等于右端点，所以没有能放的下的，只能新增一个盒子。

```cpp
dp[++ans]=a[i].h;
```

2：当前 $h_i$ 小于右端点，就是说盒子序列中有能放的下的，考虑放入现在盒子中的某个位置。我们可以想到贪心，放入第一个比它大的盒子里，因为放左边绝对不比放右边的差，我们让大盒子留着。

于是二分出第一个大于 $h$ 的 $dp_l$。

```cpp
dp[l]=a[i].h;
```

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;//日常开long long 
struct st
{
	ll w,h;
	bool operator < (const st &u)const//重载运算符 
	{
		if(w==u.w)//如果w相等 
		{
			return h<u.h;//h小的先 
		}
		return w>u.w;//w大的先 
	}
};
const ll N=20010;
ll t,n,dp[N],l,r,mid,ans;//ans存答案 
st a[N];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);//输入输出优化 
	cin>>t;//t组数据 
	while(t--)
	{
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i].w>>a[i].h;
		}
		sort(a+1,a+n+1);//排序 
		memset(dp,-1,sizeof(dp));//每次赋值为-1 
		ans=0;//ans归零 
		for(int i=1;i<=n;i++)
		{
			if(dp[ans]<=a[i].h)//如果a[i].h比dp数组的所有值都大 
			{
				dp[++ans]=a[i].h;//复制 
			}
			else
			{
				l=1;//二分 
				r=ans;
				while(l<r)
				{
					mid=(l+r)/2;
					if(dp[mid]<=a[i].h)
					{
						l=mid+1;
					}
					else
					{
						r=mid;
					}
				}
				dp[l]=a[i].h;
			}
		}
		cout<<ans<<"\n";//输出（记得要加换行） 
	}
	return 0;
}
```

---

## 作者：ylch (赞：1)

# SP3943 MDOLLS - Nested Dolls 题解

[-题目传送门-](https://www.luogu.com.cn/problem/SP3943)

看到楼上大佬都在提 LIS，蒟蒻不会，只能带来最浅显的贪心思想供大家参考。

### 题意简述

给你 $n$ 个俄罗斯套娃，每个的宽度是 $w_i$，高度是 $h_i$。同时有若干个盒子，只有 $w_x < w_y$ 与 $h_x < h_y$ 时，$x$ 和 $y$ 两个套娃才可以合并。求合并后最少有多少个套娃？

### 解题思路

这道题肯定是一个**贪心**没有错。

贪心的策略就是创造若干个盒子，因为嵌套娃娃也可以理解为把娃娃放到盒子里，同时保证一个盒子里的娃娃满足大小有序的原则。

然后开始合并，根据贪心主要的“无后效性”思想，合并时总是把当前的娃娃放到第一个比它大的盒子里（因为要保证盒子是有序的）；如果没有比它大的盒子，则新开辟一个盒子存储。直到所有娃娃放置完毕为止。

最后因为放置是要看大小的，要先把娃娃从小到大排序。排序时先按照 $w$ 从大到小排序，再按照 $h$ 从小到大排序，这样保证 $h$ 是从小到大的，维持了贪心策略。

### 函数介绍

排序：sort 函数。

```cpp
template<typename _RAIter, typename _Compare>
    _GLIBCXX20_CONSTEXPR
    void
    sort(_RAIter __first, _RAIter __end, _Compare __cmp);
```
__first：排序范围起始（迭代器）。

__end：排序范围结束（迭代器）。

__cmp：排序规则函数，默认为升序。

------------

寻找数列中第一个大于某个元素的位置：lower_bound 函数。

```cpp
template<typename _FIter, typename _Tp, typename _Compare>
    _GLIBCXX20_CONSTEXPR
    _FIter
    lower_bound(_FIter __first, _FIter __end, const _Tp& __x, _Compare __cmp);
```

__first：查找范围起始（迭代器）。

__end：查找范围结束（迭代器）。

__x：寻找的参考元素。

__cmp：大小比较函数，默认为等于。

lower_bound 函数返回的是迭代器，别忘了减去首地址，得到位置下标。

提示：STL 中迭代器都是左闭右开，即 $[a,b)$ 这样。

----------

### AC 代码

```cpp
#include <iostream>
#include <cstring>
using namespace std;

struct Doll
{
	int width, height;
	bool operator < (Doll &d)
	{
		if(width != d.width)
			return width > d.width;
		else
			return height < d.height;
	}
}a[20005];

int t[20005];
int main()
{
	int T,n;
	cin >> T;
	while (T--)
	{
		cin >> n;
		for (int i=1; i<=n; i++)
		{
			cin >> a[i].width >> a[i].height;
		}
		sort(a+1, a+n+1);
		memset(t, -1, sizeof t);
		
		int p = 0;
		for (int i=1; i<=n;i++)
		{
			if (t[p] <= a[i].height)
				t[++p] = a[i].height;
			else
			{
				int l = lower_bound(t+1, t+p+1, a[i].height) - t;
				t[l] = a[i].height;
			}
		}
		cout << p << endl;
	}
	return 0;
}
```

End
---------------

管理员大大辛苦啦~

谢谢大家！我们一起学习，一起 $rp++$！

---

## 作者：Igallta (赞：1)

题意：一共有 $n$ 个俄罗斯套娃，每个的宽度是 $w_i$，高度是 $h_i$。当且仅当 $w_a < w_b$ 而且 $h_a < h_b$ 就可以合并他们俩。

做法：贪心 + 二分。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int INF=0x3f3f3f3f;
const int maxn=20001;
template<typename T>inline T read(T&x){//任意类型的快读
    T data=0;
	int w=1;
    char ch=getchar();
    while(ch!='-'&&!isdigit(ch))
        ch=getchar();
    if(ch=='-')
        w=-1,ch=getchar();
    while(isdigit(ch))
        data=10*data+ch-'0',ch=getchar();
    return x=data*w;
}
struct doll{//根据题意
	int width,height;//分别代表：宽，高。
	bool operator <(doll& d)const
	{
		if(width!=d.width)
			return width>d.width;
		else
			return height<d.height;
	}
}a[maxn];
int f[maxn],ans;
int main(){
	int t,m;
	read(t);
	while(t--){
		read(m);
		for(int i=1;i<=m;++i){
			read(a[i].width);
			read(a[i].height);
		}
		sort(a+1,a+m+1);//进行排序，方便合并
		memset(f,-1,sizeof(f));//初始化
		ans=0;
		for(int i=1;i<=m;++i){
			int&h=a[i].height;
			if(f[ans]<=h)f[++ans]=h;	
			else{
				int l=1,r=ans,mid;
				while(l<r){//二分部分
					mid=(l+r)/2;
					if(f[mid]<=h)l=mid+1;	
					else r=mid;	
				}
				f[l]=h;
			}
		}
		printf("%d\n",ans);//输出答案
	}
    return 0;
}
```

---

## 作者：xujingyu (赞：0)

洛谷上一直 UKE，只好自己去 SPOJ 测了……

## 思路：

本题标签是：

* 贪心；
* 二分；
* 排序。

所以根据此来思考。

首先排序，先根据 $w$ 从小到大排序，再根据 $h$ 从大到小排序，（反过来亦可）为后面的贪心。

接下来，逆序枚举 $n$ 到 $1$，判断如果塞不进去（`all[tot] <= a[i].h`），就再加一组。否则二分寻找最优的。

## 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

int t,n,all[20001],tot;
struct doll
{
	int w,h;
}a[20001];
bool cmp(doll x,doll y)
{
	if(x.w != y.w) return x.w < y.w;
	return x.h > y.h;
}

signed main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		for(int i = 1;i <= n;i++) scanf("%d%d",&a[i].w,&a[i].h);
		tot = 0;//一定要清空!
		memset(all,0,sizeof(all));
		sort(a + 1,a + n + 1,cmp);//排序
		for(int i = n;i >= 1;i--)
		{
			if(all[tot] <= a[i].h) all[++tot] = a[i].h;//找不到可以放的,加一组
			else
			{
				int l = 1,r = tot;//二分
				while(l < r)
				{
					int mid = (l + r) >> 1;
					if(all[mid] <= a[i].h) l = mid + 1;
					else r = mid;
				}
				all[l] = a[i].h;
			}
		}
		printf("%d\n",tot);
	}
	return 0;
}
```


---

## 作者：zhang_Jimmy (赞：0)

这题不需要二分，贪心+模拟就可以了。

我们可以建立一个结构体来保存套娃的高度和长度，然后按照如下规则排序：

- 高度相同，长度大的排在前面（因为能套后面更多的套娃）

- 否则，高度小的排在前面。

然后建立一个 `vis` 数组，来保存每个套娃有没有用过。

再比较每个套娃的高度，如果大于他最外面套的套娃，那么就可以成为一组套娃，答案加一。

代码如下：

```
#include <bits/stdc++.h>
using namespace std;
int t, n;
struct doll{
	int w, h;
}a[30010];
bool vis[30010];
bool cmp(doll x, doll y){
	if(x.w == y.w) return x.h > y.h;
	return x.w < y.w;
}
int main(){
 	freopen("dolls.in", "r", stdin);
	freopen("dolls.out", "w", stdout);
	scanf("%d", &t);
	while(t --){
		memset(vis, 0, sizeof vis);//多测不清空，爆零两行泪
		scanf("%d", &n);
		for(int i = 1; i <= n; i ++){
//			cin >> a[i].w >> a[i].h;
			scanf("%d%d", &a[i].w, &a[i].h);
		}
		sort(a + 1, a + n + 1, cmp);
		int tot = 0, ans = 0;
		while(tot < n){
			int H = -10000;
//			cout << tot << ' ';
			ans ++;
			for(int i = 1; i <= n; i ++){
//				cout << H;
				if(vis[i] == 0 && H < a[i].h){
//					cout << H;
					tot ++;
					H = a[i].h;
					vis[i] = 1;
				}
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
```


---

## 作者：autoint (赞：0)

# 题意
## 现在n（<=20000）个俄罗斯套娃，每个都有宽度wi和高度hi（均小于10000），要求w1<w2并且h1<h2的时候才可以合并，问最少能剩几个。
# zhyfzy的题解原话这么说的
```cpp
“  【LIS】乍一看跟【这题】类似，但是仔细看是有区别的，其实就相当于上一题多次求LIS，每次求完LIS后把得到的序列删去，然后重新求LIS，最后输出求LIS的次数，我一开始这样写，果然就TLE了。还是要另辟蹊径。

首先用贪心思想，先按照wi从大到小排序，wi相等的情况下hi从小到大，然后求最长不下降子序列（注意可以等于）。输出其长度即可。

想想为什么，如果有i和j这两个点满足wi>wj，hi>hj，显然是满足条件的，直接合并即可（所求序列长度不变），但是如果wi>wj，hi<=hj不可合并，那么序列长度就要增加。

如果wi==wj，那么无论hi与hj的关系如何都不可以合并，为了方便求最长不下降序列，可以假设hi<=hj，这样序列长度也会增加。因此wi相等的情况下hi要从小到大排序。

还有一个问题是LIS中二分查找的写法问题，我是卡在了这里，在网上看了看别人的代码后，把lower_bound改成了upper_bound竟然AC了！

lower_bound是返回序列中大于等于key值的第一个数

upper_bound是返回序列中严格大于key值的第一个数

显然最长上升子序列是严格递增的，因此每次更新后都不可以出现两个数相同的情况，因此使用lower_bound（比如1,2,3,4，新输入的数是3，使用lower_bound返回第三个数，即把3改成3，如果使用upper_bound返回第四个数，把4改成3，则会出现两个3，不符合条件）。而最长不下降子序列存在多个数相同的情况，因此使用upper_bound，这里解释同上。 ”
```
# 下面我要说的才是重点
### 先声明这题跟LIS半点关系都没有，只是求法类似。（贪心+二分）
### 题意并不能转化为求最长非降子序列（我怎么看都是最短答案），
### 只是算法分析出来求法跟LIS一样。
### 我记得zhyfzy说两题“类似”，所以网上很多题解都说这题是LIS。
### 现在想来他们都是没看懂zhyfzy的思路。
## 证明LIS做法正确性
### 总的来看先按width从大到小排序，再按height从小到大排序，维护height的非降序列。f[]是盒子。对每个元素有两种决策：
### 1、如果当前h[i]比右端点大（等于），因为没有放的下的，所以只能新增一个盒子。
f[++ans]=h[i];
### 2、当前h[i]小于右端点，意思是说盒子序列中有能包含它的，烤炉放入已有盒子中的某个。该放哪个呢？我们贪心，放入第一个比它大的盒子里。因为放左边绝对不比放右边的差，我们坚信物尽其用，大盒子留着。
于是二分出第一个大于h[i]的f[l]，
f[l]=h[i];
## 最后一个细节
### 有w[i]==w[j]的情况，此时无论h[i],h[j]关系如何，i都不应放入j中，于是我们要特判。但是如果排序时“按height从小到大排序”，那么i肯定不会放到j中去。因为j先出现，且h[j]<h[i]，1、2步骤都会自动判定不能放入。这样就减少了特判开销。（不知是哪位大佬第一次想出这种办法的，在此膜拜）
## 综上，该算法保证了正确性。
#### 但是它的确跟LIS半毛钱关系都没有。是的，做法一模一样，思路截然不同。或许这题正好解释了映射原理。
# 下面给出代码
```cpp
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<ctime>
#include<iostream>
#include<string>
#include<vector>
#include<list>
#include<deque>
#include<stack>
#include<queue>
#include<map>
#include<set>
#include<algorithm>
//#pragma GCC optimize(2)
using namespace std;
typedef long long ll;
const int INF=0x7fffffff;
template<class T> inline T read(T&x){
    T data=0;
	int w=1;
    char ch=getchar();
    while(ch!='-'&&!isdigit(ch))
        ch=getchar();
    if(ch=='-')
        w=-1,ch=getchar();
    while(isdigit(ch))
        data=10*data+ch-'0',ch=getchar();
    return x=data*w;
}

const int maxn=2e4+10;
struct doll
{
	int width,height;
	bool operator <(doll& d)const
	{
		if(width!=d.width)
			return width>d.width;
		else
			return height<d.height;
	}
}a[maxn];
int f[maxn],ans;
int main()
{
//  freopen(".in","r",stdin);
//  freopen(".out","w",stdout);
	int t,m;
	read(t);
	while(t--)
	{
		read(m);
		for(int i=1;i<=m;++i)
		{
			read(a[i].width);
			read(a[i].height);
		}
		sort(a+1,a+m+1);
		memset(f,-1,sizeof(f));
		ans=0;
		for(int i=1;i<=m;++i)
		{
			int&h=a[i].height;
			if(f[ans]<=h)
				f[++ans]=h;
			else
			{
				int l=1,r=ans,mid;
				while(l<r)
				{
					mid=(l+r)>>1;
					if(f[mid]<=h)
						l=mid+1;
					else
						r=mid;
				}
				f[l]=h;
			}
		}
		printf("%d\n",ans);
	}
//  fclose(stdin);
//  fclose(stdout);
    return 0;
}

```

---

## 作者：king_xuan (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/solution/SP3943)

# 题意

$n$ 个俄罗斯套娃，每个宽 $w[i]$，高  $h[i]$。若干个盒子，当 $w[x]<w[y]$ 和 $h[x]<h[y]$ 时，两个套娃（$x$，$y$）才能合并。求的是合并之后最少有多少个套娃。

# 思路

### 贪心，二分

升序和降序排序都有，然后判断一下（是否所有套娃都低于，如果是，说明目前的套娃不包含，单独开一个）；再用二分查找（找最小可以包含住的套娃，如果有，更新高度和用来记录套娃是否用过的数组）

### 注意：本题使用了三层嵌套循环，会超时，要使用二分优化

# 代码

```
#include<bits/stdc++.h>//万能头 
using namespace cntd;
#define int long long//建议大家都写上,毕竟"十年OI一场空,不开long long见祖宗"
struct re{
    int w,h;
}a[50010];
int n,b[50010];
bool cmp(re x,re y){
	if(x.w!=y.w){
		return x.w<y.w;
	}
	return x.h>y.h;
}
signed main(){//记得将int换成signed
    ios::sync_with_cntdio(false);
    int t;
	cin>>t;
    while(t--){
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>a[i].w>>a[i].h;
        }
        sort(a,a+n,cmp);
        memset(b,0,sizeof(b));
        int ans=0,sum=0,cnt;
        while(sum<n){
            for(cnt=0;b[cnt];cnt++){
            　　int now=a[cnt].h; 
	   	        b[cnt]=1;
			    ans++;
			    sum++;
			}
            for(int i=cnt+1;i<n;i++){
                if(!b[i]&&a[i].h>now){
                    now=a[i].h;
					b[i]=1;
					sum++;
                }
            }
        }
        cout<<ans<<endl;
    }
    return 0;//养成好习惯 
}
```

---

