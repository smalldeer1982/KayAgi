# The Doctor Meets Vader (Easy)

## 题目描述

Heidi and Doctor Who hopped out of the TARDIS and found themselves at EPFL in 2018. They were surrounded by stormtroopers and Darth Vader was approaching. Miraculously, they managed to escape to a nearby rebel base but the Doctor was very confused. Heidi reminded him that last year's HC2 theme was Star Wars. Now he understood, and he's ready to face the evils of the Empire!

The rebels have $ s $ spaceships, each with a certain attacking power $ a $ .

They want to send their spaceships to destroy the empire bases and steal enough gold and supplies in order to keep the rebellion alive.

The empire has $ b $ bases, each with a certain defensive power $ d $ , and a certain amount of gold $ g $ .

A spaceship can attack all the bases which have a defensive power less than or equal to its attacking power.

If a spaceship attacks a base, it steals all the gold in that base.

The rebels are still undecided which spaceship to send out first, so they asked for the Doctor's help. They would like to know, for each spaceship, the maximum amount of gold it can steal.

## 说明/提示

The first spaceship can only attack the first base.

The second spaceship can attack the first and third bases.

The third spaceship can attack the first, second and third bases.

## 样例 #1

### 输入

```
5 4
1 3 5 2 4
0 1
4 2
2 8
9 4
```

### 输出

```
1 9 11 9 11
```

# 题解

## 作者：Withershine (赞：4)

[大佬的题解](https://270854.blog.luogu.org/solution-cf1184b1)写的太好了，这里给出不同于大佬的做法。

## 思路
读入后，将 $b$ 数组按照关键字 $d$ 从小到大排序，并用前缀和数组记录下前 $i$ 个 $d$ 的总和。在对每个 $a_i$ 进行查询时，二分找出第一个 $a_i$ 不能攻打的城市 $l$，此时说明前 $l-1$ 座城市对于 $a_i$ 来说都能攻打，所得到的黄金数量就是 $q[l-1]$。这里的变量 $b$，$d$，$a$ 均与题目翻译对应。

想要纯暴力的做法是行不通的，即使是四秒的时限，~~别问我怎么知道的~~。

## 代码
PS：自从用了 VsCode 后格式变得有点奇怪，看着有点难受。
```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#include<string>
#include<ctime>
#include<cstring>
#include<algorithm>
#include<climits>
#include<queue>
#include<map>
#include<set>
#include<sstream>
#include<cassert>
#include<stdio.h>
#define ll long long
#define inf 0x3f3f3f3f
#define fr(i , a , b) for(ll i = a ; i <= b ; ++i)
#define fo(i , a , b) for(ll i = a ; i >= b ; --i)
using namespace std;
inline char gchar()
{
    static char buf[1000000] , *p1 = buf , *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf , 1 , 1000000 , stdin) , p1 == p2) ? EOF : *p1++;
}
inline ll read()
{
    ll x = 0 , f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
	  {
        if(ch == '-')
        {
        	f = -1;
		}
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9')
	  {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}
ll s , b , a[100005];
ll q[100005];
struct node
{
    ll d , g;
    bool operator < (const node &x) const
    {
        return d < x.d;
    }
}str[100005];
signed main()
{
    s = read();
    b = read();
    fr(i , 1 , s)
    {
        a[i] = read();
    }
    fr(i , 1 , b)
    {
        str[i].d = read();
        str[i].g = read();
        q[i] = q[i - 1] + str[i].g;
    }
    sort(str + 1 , str + b + 1);
    fr(i , 1 , b)
    {
        q[i] = q[i - 1] + str[i].g;
    }
    fr(i , 1 , s)
    {
        ll l = 1 , r = b , mid;
        while(l <= r)
        {
            mid = (l + r) >> 1;
            if(str[mid].d <= a[i])
            {
                l = mid + 1;
            }
            else
            {
                r = mid - 1;
            }
        }
        printf("%lld " , q[l - 1]);
    }
    system("pause");
    return 0;
}
```


---

## 作者：Ray_yi (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF1184B1)

### 思路：

看到数据范围后，发现暴力是过不了的，所以我们要想其他办法。仔细想想，会发现每艘宇宙飞船只可以攻击所有防御力小于等于其攻击力的飞船，防御力大于它的飞船是攻击不了的。普通思路会把每艘飞船都遍历一遍，会浪费很多时间，我们只需要排序，先让他有序化就可以了。

但是光排序，还是过不了。换一个思路，先把每艘飞船算一下前缀和，再用二分，找防御力小于他的最大值的下标，最后加上这个下标的前缀和就好了。

### 代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
int s,b,a[100005],kl[100005];
struct node{
	int d,g;
}k[100005];
bool cmp(node x,node y){
	if(x.d==y.d) return x.g>y.g;
	return x.d<y.d;
}//按防御力从小到大排序
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>s>>b;
	for(int i=1;i<=s;i++) cin>>a[i];
	for(int i=1;i<=b;i++) cin>>k[i].d>>k[i].g;
	sort(k+1,k+b+1,cmp);
	for(int i=1;i<=b;i++) kl[i]=kl[i-1]+k[i].g;//算前缀和
	for(int i=1;i<=s;i++){
		int l=1,r=b,mid,ans=-1;
		while(l<=r){//二分模板
			mid=(l+r)/2;
			if(k[mid].d<=a[i]){
				ans=max(kl[mid],ans);//找满足条件的最大值
				l=mid+1;
			}
			else r=mid-1; 
		}
		cout<<ans<<" ";
	}
	return 0;
}
```

---

## 作者：Ybll_ (赞：3)

# 前置芝士：
1. [前缀和](https://blog.csdn.net/m0_69323023/article/details/135789840)
2. [二分查找](https://baike.baidu.com/item/%E4%BA%8C%E5%88%86%E6%9F%A5%E6%89%BE/10628618)
# 题意：
相信你看得懂题目，但是每艘飞船一次可以打劫**多个**基地。
# 思路：
`二分查找+前缀和`，先对每个基地的防御力进行**升序排序**，在对每个基地的金子做**前缀和**，然后扫一遍数组 $a$，**二分**去找可以打劫的城市的**最大**防御力，然后输出。
# 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct node
{
	int d,g;
}b[100005];
int n,m,a[100005];
bool cmp(node i,node j)
{
	return i.d<j.d||i.d==j.d&&i.g<j.g;
}
signed main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(int i=1;i<=m;i++)
	{
		cin>>b[i].d>>b[i].g;
	}
	sort(b+1,b+1+m,cmp);
	for(int i=1;i<=m;i++)
	{
		b[i].g+=b[i-1].g;
	}
	for(int i=1;i<=n;i++)
	{
		int l=1,r=m,mid,ans=0;
		while(l<=r)
		{
			mid=l+r>>1;
			if(b[mid].d<=a[i])
			{
				ans=b[mid].g;
				l=mid+1;
			}
			else r=mid-1;
		}
		cout<<ans<<" ";
	}
	return 0;
}
```

---

## 作者：oVo_yangxy (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1184B1)

这题没什么好说的，所以接下来我会带着你们一步一步的从暴力开始优化。
## 题目描述
有 $s$ 艘太空船，每艘都有一定的攻击力 $a$，有 $b$ 个基地，每个基地都有一定的防御能力 $d$ 和一定量的黄金 $g$。只要基地的防御力小于等于飞船的攻击力，那么该基地的所有黄金都会被该飞船盗走。求：每个飞船能盗走的最大黄金。
## 优化过程
我们看到题目，管他三七二十一，先打个暴力再说：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long s,b,a[100005],ans,d[100005],g[100005];
int main(){
	cin>>s>>b;
	for(int i=1;i<=s;i++) cin>>a[i];
	for(int i=1;i<=b;i++) cin>>d[i]>>g[i];
	for(int i=1;i<=s;i++){
		ans=0;
		for(int j=1;j<=b;j++)
			if(d[j]<=a[i]) ans+=g[j];
		cout<<ans<<" ";
	}
	return 0;
}
```
打完一看，这感人的数据范围……

没事，我们先把 $d$，也就是每个基地的防御值排个序，注意一下，这里 $d$ 的值再排序时如果发生变化，$g$ 的值也要跟着变化：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long s,b,a[100005],ans;
struct node{
	long long d,g;
}c[100005];
bool cmp(node a,node b){return a.d<b.d;}
int main(){
	cin>>s>>b;
	for(int i=1;i<=s;i++) cin>>a[i];
	for(int i=1;i<=b;i++) cin>>c[i].d>>c[i].g;
	sort(c+1,c+b+1,cmp);
	for(int i=1;i<=s;i++){
		ans=0;
		for(int j=1;j<=b;j++)
			if(c[j].d<=a[i]) ans+=c[j].g;
		cout<<ans<<" ";
	}
	return 0;
}
```

诶~这里的 $ans$ 不就是个前缀和嘛。那我们在循环外再加一行做数组 $g$ 前缀和的，程序就会变成这样：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long s,b,a[100005],ans;
struct node{
	long long d,g;
}c[100005];
bool cmp(node a,node b){return a.d<b.d;}
int main(){
	cin>>s>>b;
	for(int i=1;i<=s;i++) cin>>a[i];
	for(int i=1;i<=b;i++) cin>>c[i].d>>c[i].g;
	sort(c+1,c+b+1,cmp);
	for(int i=1;i<=b;i++) c[i].g+=c[i-1].g;
	for(int i=1;i<=s;i++){
		ans=0;
		for(int j=1;j<=b;j++)
			if(c[j].d<=a[i]) ans=c[j].g;
			else break;
		cout<<ans<<" ";
	}
	return 0;
}
```
还没完，如果仅仅是这样，必然会 $T$。现在我们来想想，嗯……前缀和是依次递增的……只需要找到该飞船能盗的金币的最大值……这不用个二分查找就好了嘛！

所以！我们把循环内找金币最大值的部分换成二分就行了！代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long s,b,a[100005],ans;
struct node{
	long long d,g;
}c[100005];
bool cmp(node a,node b){return a.d<b.d;}
int main(){
	cin>>s>>b;
	for(int i=1;i<=s;i++) cin>>a[i];
	for(int i=1;i<=b;i++) cin>>c[i].d>>c[i].g;
	sort(c+1,c+b+1,cmp);
	for(int i=1;i<=b;i++) c[i].g+=c[i-1].g;
	for(int i=1;i<=s;i++){
		ans=0;
		int l=1,r=b,mid;
		while(l<=r){
			mid=(l+r)/2;
			if(c[mid].d<=a[i] && c[mid+1].d>a[i]){
				ans=c[mid].g;
				break;
			}else if(c[mid].d<a[i]) l=mid+1;
			else if(c[mid].d>a[i]) r=mid-1;
		}
		cout<<ans<<" ";
	}
	return 0;
}
```
最后再完善一下：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long s,b,a[100005],ans;
struct node{
	long long d,g;
}c[100005];
bool cmp(node a,node b){return a.d<b.d;}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>s>>b;
	for(int i=1;i<=s;i++) cin>>a[i];
	for(int i=1;i<=b;i++) cin>>c[i].d>>c[i].g;
	sort(c+1,c+b+1,cmp);
	for(int i=1;i<=b;i++) c[i].g+=c[i-1].g;
	for(int i=1;i<=s;i++){
		ans=0;
		int l=1,r=b,mid;
		while(l<=r){
			mid=(l+r)/2;
			if(c[mid].d<=a[i] && c[mid+1].d>a[i]){
				ans=c[mid].g;
				break;
			}else if(c[mid].d<a[i]) l=mid+1;
			else if(c[mid].d>a[i]) r=mid-1;
		}
		cout<<ans<<" ";
	}
	return 0;
}
```
## 总结
此篇题解涉及到了[前缀和](https://www.baidu.com/s?wd=c%2B%2B%E4%BB%80%E4%B9%88%E6%98%AF%E5%89%8D%E7%BC%80%E5%92%8C&rsv_spt=1&rsv_iqid=0x9dfe7997004064b5&issp=1&f=8&rsv_bp=1&rsv_idx=2&ie=utf-8&rqlang=cn&tn=88093251_115_hao_pg&rsv_enter=1&rsv_dl=tb&rsv_btype=t&inputT=10000&rsv_t=605e2eywg3XZPQPg4a%2BiqdfU1XWdCoGV7ccKkmV2uMpmLHk5TIQrYpGzLL4WdJRfK5hnAO3ie3pmHw&oq=c%252B%252B%25E5%2589%258D%25E7%25BC%2580%25E5%2592%258C&rsv_pq=d0d751ea00491c80&rsv_sug3=20&rsv_sug1=31&rsv_sug7=100&rsv_sug2=0&prefixsug=c%252B%252B%25E4%25BB%2580%25E4%25B9%2588%25E6%2598%25AF%25E5%2589%258D%25E7%25BC%2580%25E5%2592%258C&rsp=2&rsv_sug4=13491)，[二分查找](https://yr7ywq.smartapps.baidu.com/?_chatQuery=c%2B%2B%E4%BA%8C%E5%88%86%E6%9F%A5%E6%89%BE%E6%B3%95&searchid=13392621164751780800&_chatParams=%7B%22agent_id%22%3A%22c816%22%2C%22content_build_id%22%3A%2228cad32%22%2C%22from%22%3A%22q2c%22%2C%22token%22%3A%22UGlGZHdpN0lzYXNVbS9Gb1JoeVNNWXRmOGI3Q0R2VFNVZlJSWlMzOW9STHlhbkU4cHB4dkhUdjdaczFUU0xEbEhFZmxOd0llRjlYVXdqeXRsVzR1WDdtSjVnNlZNMEhqN0g5ZEc4UjA5SEpSRU5Sa2o2bmRHWDNGTDJoMW5pczBRM3JKdnI0d1gwd0xzRS92czRUU0pRPT0%3D%22%2C%22chat_no_login%22%3Atrue%7D&_swebScene=3711000610001000)和[结构体的排序](https://www.baidu.com/s?ie=utf-8&f=8&rsv_bp=1&rsv_idx=2&tn=88093251_115_hao_pg&wd=c%2B%2B%E7%BB%93%E6%9E%84%E4%BD%93%E7%9A%84%E6%8E%92%E5%BA%8F&rsv_spt=1&oq=c%252B%252B%25E4%25BB%2580%25E4%25B9%2588%25E6%2598%25AF%25E5%2589%258D%25E7%25BC%2580%25E5%2592%258C&rsv_pq=ce0668c1002ceaa1&rsv_t=7af4znmNoDpInMUlc563bsDCyTh4trW%2FgNTLBV20HAVdSAr3%2BHvlQIrDLpjDKjdblyWqQpleU2K%2BBQ&rqlang=cn&rsv_dl=tb&rsv_enter=1&rsv_sug3=31&rsv_sug1=21&rsv_sug7=100&rsv_sug2=0&rsv_btype=t&inputT=16352&rsv_sug4=17454)，在做题时往往我们会采用一步步优化的方案来解决问题，如果遇到不能一眼就看出方法的题目，这就是一个很好的选择。

~~给蒟蒻点个赞吧。~~

---

## 作者：zlqwq (赞：2)

非常正常的二分题目！

将数组从小到大排序，然后建一个前缀和数组 $sum$，因为二分一定是在数组有序的前提下进行的。

然后我们暴力枚举数组，对于每个 $a_i$ 进行非常套路的二分，找到前边第一个比他大的数，设其索引为 $tmp$，然后直接输出 $sum_{tmp}$ 即可。

---

## 作者：二叉苹果树 (赞：2)

对于每一个宇宙飞船，我们要给出所有防御力小于该飞船攻击力的基地的金币数的总和。发现攻击力与防御力的数值较大，故排序后进行离散化即可。

```cpp
#include <bits/stdc++.h>
#define MAXN 100005

int s, b, a[MAXN];
std::map<int, int> sum;
struct node
{
	int w, v;
}x[MAXN];

bool cmp(node a, node b)
{
	return a.w < b.w;
}
int main()
{
    std::cin >> s >> b;
    std::vector<int> e;
 	for (int i = 1; i <= s; i++)
 	{
	    std::cin >> a[i];
	    e.push_back(a[i]);
	}
	for (int i = 1; i <= b; i++)
	{
	    std::cin >> x[i].w >> x[i].v;
	    e.push_back(x[i].w);
	}
    std::sort(e.begin(), e.end());
    e.erase(std::unique(e.begin(), e.end()), e.end());
    for (int i = 1; i <= s; i++)
        a[i] = std::lower_bound(e.begin(), e.end(), a[i]) - e.begin();
    for (int i = 1; i <= b; i++)
        x[i].w = std::lower_bound(e.begin(), e.end(), x[i].w) - e.begin();
    for (int i = 1; i <= b; i++)
        sum[x[i].w] += x[i].v;
    for (int i = 0; i < e.size(); i++)
        sum[i] += sum[i - 1];
    for (int i = 1; i <= s; i++)
        std::cout << sum[a[i]] << " ";
    std::cout << std::endl;
    return 0;
}
```


---

## 作者：_qumingnan_ (赞：1)

[题目跳楼机](https://www.luogu.com.cn/problem/CF1184B1)

# 正文开始

## 阅读理解

有 $s$ 艘太空船，第 $i$ 艘的飞船的战力为 $a_i$；有 $b$ 个基地，第 $j$ 个基地的防御力为 $d_j$，攻击力为 $g_j$。

现在，第 $i$ 艘飞船可以拿走防御力小于等于 $a_i$ 的所有基地的黄金，但这些基地的黄金并不会消失。

请问每个飞船可以拿多少黄金？

## 思路

拿到题后，首先考虑暴力，按题意模拟:
```cpp
#include<bits/stdc++.h>
using namespace std;
int s,a[100005];
int b;
struct node{int d,g;}c[100005];
int ans[100005];
bool cmp(node x,node y){return x.d<y.d;}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>s>>b;
	for(int i=1;i<=s;i++)cin>>a[i];//攻击力 
	for(int i=1;i<=b;i++)cin>>c[i].d>>c[i].g;//防御力与黄金 
	sort(c+1,c+1+b,cmp);//排序 
	for(int i=1;i<=s;i++)
		for(int j=1;j<=b;j++)
			if(c[j].d<=a[i])ans[i]+=c[j].g;//如果满足条件，就让这个基地变成 a[i] 的囊中之物 
			else break;
	for(int i=1;i<=s;i++)cout<<ans[i]<<' ';
	return 0;
}
```

很明显，这串代码最劣为 $O(sb)$（真的不是在骂人，题目给出的就这两个变量），是过不了的。

我们可以发现，$a$ 数组和 $d$ 与 $g$ 数组是互不干涉的，那就可以给 $a$ 数组也排个序。

**注**：排序时需带上编号

给 $a$ 排完序后，我们可以发现，由于 $a$ 和 $d$ 都是单调不下降的序列，于是对于每一个 $i(i\geq2)$，都有一个性质：$a_i$ 能获得的黄金数量一定也是大于等于 $a_{i-1}$ 所能获得的黄金数量的。

既然三个能影响答案的因素都是单调的，那你能想到什么算法呢？那就是**双指针**。

我们可以用一个变量 $r$ 来存储第 $i-1$ 艘飞船最多可以击破第几个基地的防御，然后从它开始枚举，再记录一个前缀和，里面存储击破 $1\sim i$ 的基地可以获得多少黄金。

## 代码实现：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int s;
struct nod{int x,id;}a[100005];
int b;
struct node{int d,g;}c[100005];
int qz[100005],ans[100005];
bool cmp1(nod x,nod y){return x.x<y.x;}
bool cmp2(node x,node y){return x.d<y.d;}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>s>>b;
	for(int i=1;i<=s;i++)cin>>a[i].x,a[i].id=i;
	for(int i=1;i<=b;i++)cin>>c[i].d>>c[i].g;
	sort(a+1,a+1+s,cmp1);sort(c+1,c+1+b,cmp2);
	for(int i=1;i<=b;i++)qz[i]=qz[i-1]+c[i].g;
	int r=1;
	for(int i=1;i<=s;i++){
		for(;r<=b;r++)
			if(c[r].d>a[i].x)break;
		ans[a[i].id]=qz[r-1];
	}
	for(int i=1;i<=s;i++)cout<<ans[i]<<' ';
	return 0;
}
```
```

---

## 作者：JCT_addyi (赞：1)

### 题目大意：

有 $s$ 艘太空船，有 $b$ 个基地，给你每艘太空船的攻击力，每个基地的防御能力和金币量，每艘飞船可以攻击防御力小于等于这艘飞船的攻击力的基地，从而获取这个基地的所有金币，问每艘飞船可以拿走的最大金币值。

### 思路：

1. 暴力，但这是道黄题会超时。
2. 排序，一点优化。
3. 最后想到了前缀和，就不用一次一次加金币了。
4. 二分加前缀和。

我们这道题用结构体排序会简单一点，把基地的防御力能力从小到大排序，如果防御能力相同就按金币大小排序，再求金币前缀和，最后二分。

### 代码如下：

详细看代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
int s,b,a[100005],l[100005];//a是攻击力 l是前缀和 
struct node{
	int d,g;//d是防御 g是黄金 
}k[100005];//k 是基地 
bool cmp(node x,node y){
	if(x.d==y.d) return x.g>y.g;//防御相等金币从大到小比 
	return x.d<y.d;//按防御比 
}//按防御力从小到大排序
int main(){
	cin>>s>>b;//s是太空船数量 b是基地数量 
	for(int i=1;i<=s;i++) cin>>a[i];
	for(int i=1;i<=b;i++) cin>>k[i].d>>k[i].g;
	sort(k+1,k+b+1,cmp);
	for(int i=1;i<=b;i++) l[i]=l[i-1]+k[i].g;//前缀和
	for(int i=1;i<=s;i++){
		int l=1,r=b,mid,ans=-1;
		while(l<=r){//二分
			mid=(l+r)/2;
			if(k[mid].d<=a[i]){//查找防御比攻击小的基地 
				ans=max(l[mid],ans);//找满足条件的最大值
				l=mid+1;
			}
			else r=mid-1; 
		}
		cout<<ans<<" ";//输出 
	}
	return 0;
}
```

谢谢大家！

---

## 作者：pyz51 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1184B1)

[CF传送门](https://codeforces.com/problemset/problem/1184/B1)

[AC记录](https://codeforces.com/contest/1184/submission/298415728)
# 题意简述
给定序列 $a$。    
求 $d$ 序列中比 $a_i(1\le i\le s)$ 小的数的价值之和。
# 题解
首先暴力 $O(n^2)$ 显然不太行。  
因此我们可以将遍历 $d$ 序列的过程改为二分，在此之前先将 $d$ 序列排序。  
然后就可以找出 $d$ 中比 $a_i$ 小的最大的数，位置为 $pos$。  
那么 $1 \sim pos$ 的价值和即为所求，为了 $O(1)$ 求出，预处理前缀和。
# AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
const int M=2e5+5;
const int inf=2147483647;
const long long lof=9223372036854775807;
#define ll long long
#define bug cout<<"...here...\n"
#define mem(a,b) memset(a,b,sizeof a)
#define CLOSE ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define F first
#define S second
#define lowbit(x) x&-x
inline ll read(){
	ll x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
int Stack[105];
inline void print(ll x){
    int cnt=0;
    if(x<0) putchar('-'),x=-x;
    while(x){
    	Stack[++cnt]=x%10;
    	x/=10;
    }
    while(cnt--) putchar((char)Stack[cnt+1]+'0');
    return;
}
int s,b,a[N],sum[N];
pair<int,int> d[N];
int main(){
    CLOSE
    cin>>s>>b;
    for(int i=1;i<=s;i++) cin>>a[i];
    for(int i=1;i<=b;i++) cin>>d[i].F>>d[i].S;
    sort(d+1,d+1+b);//排序
    for(int i=1;i<=b;i++) sum[i]=d[i].S+sum[i-1];//预处理前缀和
    for(int i=1;i<=s;i++){
    	int l=0,r=b;
    	while(l<r){
    		int mid=l+r+1>>1;
    		if(a[i]>=d[mid].F) l=mid;
    		else r=mid-1;
		}
        //二分求出pos
		cout<<sum[l]<<' ';
	}
    return 0;
}
```

---

## 作者：_Violet_Evergarden (赞：1)

看到题解有些空缺，来发一发。
# 题意
在一个序列中，找到所有比他小的数，加上他们给定的价值。

# 思路
初看这道题，相信大佬们都会发现这是一道浅显易懂的二分题，我们只需将原序列进行一次从小到大的排序，然后对于每一个太空飞船进行一次二分查找，找到第一个比它大的数，将它前面的数的总和输出出来即可，而前面的数的总和可以用前缀和来维护。

# 代码如下

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int d,g;
}e[1000001];
int s;
int b;
int a[1000001];
long long ans[1000001];
int cmp(node q,node w){
	return q.d<w.d;
}
int find(int x){
	int l=0;
	int r=b;
	while(l<r){
		int mid=(l+r+1)>>1;
		if(a[x]>=e[mid].d){
			l=mid;
		}
		else{
			r=mid-1;
		}
	}
	return l;
}
int main()
{
	cin>>s>>b;
	for(int i=1;i<=s;i++){
		cin>>a[i];
	}
	for(int i=1;i<=b;i++){
		cin>>e[i].d>>e[i].g;
	}
	sort(e+1,e+1+b,cmp);
	for(int i=1;i<=b;i++){
		ans[i]=ans[i-1]+e[i].g;
	}
	for(int i=1;i<=s;i++){
		cout<<ans[find(i)]<<" ";
	}
	return 0;
}
```


---

## 作者：BVVD_FM (赞：1)


# Solution
其实很好想，一艘飞船能抢来所有防御力比它攻击力小的基地的黄金，所以我们就将基地按防御力从小到大排序，每个飞船能攻击的基地就是序列中的飞船攻击力在的位置以前的所有基地。

但是基地有很多，一个一个加上肯定很慢，既然飞船能攻击的基地是其攻击力以前的所有基地，不如我们就直接一次前缀和求出到第 $n$ 个位置的黄金之和。

还要注意的一点是，由于飞船能攻击到所有的小于等于攻击力的基地，所以在查找时要用 ```upperbound()``` 查找大于飞船攻击力的位置，在这个基地位置前的基地是可以攻击到的（用 ```lowerbound()``` 会漏下等于飞船攻击力的基地）。
# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
#define int long long
int n,m,a[N],sum[N];
struct node{
	int b,g;
}d[N];
int di[N];
bool cmp(node a,node x){
	return a.b<x.b;
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=m;i++){
		cin>>d[i].b>>d[i].g;
	}
	sort(d+1,d+m+1,cmp);//排序
	for(int i=1;i<=m;i++){
		di[i]=d[i].b;
		sum[i]=sum[i-1]+d[i].g;//前缀和
	}
   
	for(int i=1;i<=n;i++){
		int dex=upper_bound(di+1,di+m+1,a[i])-di-1;
		cout<<sum[dex]<<" ";
	}
	return 0;
}
```


---

## 作者：QAQ2012 (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/CF1184B1)

## 思路

因为我们能显著的发现，$b$ 个基地的防御力排序是不影响答案的。同时，排好序后，我们能发现，**对于任意一个攻击力为 $a_i$ 的飞船，如果大于等于 $b_i$ 的防御力的基地，那么小于等于他的基地金块都会被盗走。**

我们能发现，只要用**二分**来找到最大的小于等于这个飞船攻击力的就行了，再将每一个基地排序后对金块做最前缀和就行了。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m;
struct node{
	int b,g;
}b[100050];
long long a[100050],l,r;
bool cmp(node x,node y){
	return x.b<y.b;
}
int main(){
	cin>>n>>m;
	for(int i = 1 ; i <= n ; i++){
		cin>>a[i];
	}
	for(int i = 1 ; i <= m ; i++){
		cin>>b[i].b>>b[i].g;
	}
	sort(b+1,b+m+1,cmp);
	for(int i = 1 ; i <= m ; i++){
		b[i].g+=b[i-1].g;
	}
	for(int i = 1 ; i <= n ; i++){
		int ret=0;
		l=1;
		r=m;
		while(l<=r){
			int mid=(l+r)/2;
			if(b[mid].b<=a[i]){
				ret=mid;
				l=mid+1;
			}
			else{
				r=mid-1;
			}
		}
		cout<<b[ret].g<<" ";
	}
	return 0;
}

```

---

## 作者：jubaoyi2011 (赞：0)

好久没写二分了，来 CF 练练手。

 ~~s，b 看起来有点怪怪的~~

先对数组 $d$ 排序，然后对 $d_i$ 二分查找，本来其实只用一个 ```sort()``` 就行，但它就恶心在 $d$ 和 $g$ 下标必须一致，所以就只能手写排序或用结构体。于此同时维护一个 $g_i$ 的前缀和数组，当 $d_i < a_i$ 时，输出前缀和即可。

## Code


```cpp
#include<bits/stdc++.h>

using namespace std;

int s,b,a[100005],d[100005],g[100005];
long long ans[100005];

void pop_sort(){//d和g的下标必须一致，所以只对d排序，e的下标随d变化
	for (int i=1;i<=b;i++)
		for (int j=1;j<b;j++)
			if (d[j]>d[j+1]){
				swap(d[j],d[j+1]);
				swap(g[j],g[j+1]);
			}
}

main(){
	cin>>s>>b;
	for(int i=1;i<=s;i++)cin>>a[i];
	for(int i=1;i<=b;i++)cin>>d[i]>>g[i];
	pop_sort();//排序
	for(int i=1;i<=b;i++){//前缀和
		ans[i]=ans[i-1]+g[i];
	}
	for(int i=1;i<=s;i++){//对每组数据进行二分查找
		int l=0,r=b;
		while(l<r){
				int mid=(l+r+1)>>1;
			if(a[i]>=d[mid]){
				l=mid;
			}
			else{
				r=mid-1;
			}
		}
		cout<<ans[l]<<' ';
	}
}
```

---

## 作者：copper_ingot (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1184B1)

首先分别按照攻击力和防御力从小到大给飞船和基地排序。

然后对于每个飞船找出它可以攻击的最大防御力的基地。

可以用一个 $pos$ 维护当前的基地编号，表示当前的飞船最多可以拿到 $pos$ 号基地的金子。

因为排序后飞船的攻击力是严格不降的，所以排序后 $i$ 号飞船可以拿到的金子，$i + 1$ 号飞船也可以拿到。

对基地的金子数做一个前缀和 $pre$，则 $i$ 号飞船可以拿到的金子数是 $pre_{pos}$。

最后按照原编号输出飞船拿到的金子数。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int b, s, a[100001], pre[100001], pos = 1;
struct base{int d, g;}c[100001];
struct ship{int a, id, ans;}d[100001];//结构体分别存储基地和飞船的信息
bool cmp(base x, base y){return x.d < y.d;}
bool cmp1(ship x, ship y){return x.a < y.a;}
bool cmp2(ship x, ship y){return x.id < y.id;}
signed main(){
	scanf("%lld%lld", &s, &b);
	for (int i = 1; i <= s; i++){scanf("%lld", &d[i].a); d[i].id = i;}
	for (int i = 1; i <= b; i++) scanf("%lld%lld", &c[i].d, &c[i].g);
	sort(c + 1, c + b + 1, cmp); sort(d + 1, d + s + 1, cmp1);//分别排序
	for (int i = 1; i <= b; i++) pre[i] = pre[i - 1] + c[i].g;//求前缀和
	for (int i = 1; i <= s; i++){
		while (c[pos].d <= d[i].a && pos <= b) pos++;
		pos--;//维护pos
		d[i].ans = pre[pos];//得到答案
	}
	sort(d + 1, d + s + 1, cmp2);//按原编号重新排序
	for (int i = 1; i <= s; i++) printf("%lld ", d[i].ans);
	return 0;
}
```

---

## 作者：rainygame (赞：0)

随便抽了一道 \*1400 的题，没想到就抽到了这个。

这道题正解是二分，所以考虑把 $d$ 和 $g$ 封装到一个结构体里，然后再以 $d$ 为关键字来排序。

然后对于每个 $a$，就可以二分查找其位置了！注意，这里需要用 `upper_bound` 并 $-1$，不然如果有多个 $d$ 相同的话就会出现错误。

然后对于求和，我们维护一个前缀和即可。

**注意：`lower_bound` 和 `upper_bound` 都需要重载 `<` 运算符。**

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define MAXN 100001

int n, m, pos;
int a[MAXN], sum[MAXN];

struct Node{
	int d, g;
	bool operator<(const Node b)const{
		return d < b.d;
	}
}nodes[MAXN];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	cin >> n >> m;
	for (int i(1); i<=n; ++i) cin >> a[i];
	for (int i(1); i<=m; ++i) cin >> nodes[i].d >> nodes[i].g;
	sort(nodes+1, nodes+m+1);
	for (int i(1); i<=m; ++i) sum[i] = sum[i-1] + nodes[i].g;
	
	for (int i(1); i<=n; ++i){
		pos = upper_bound(nodes+1, nodes+m+1, Node{a[i], 0})-nodes-1;
		cout << sum[pos] << ' ';
	}
	
	return 0;
}

```


---

