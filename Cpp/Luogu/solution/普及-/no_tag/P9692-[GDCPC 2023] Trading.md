# [GDCPC 2023] Trading

## 题目描述

二十年前，广州的北京路步行街北段出土了自唐代直到民国时期的十一层路面，南段则发掘出宋代至明清时期共五层的拱北楼建筑基址，佐证了北京路自宋代以来作为商业步行街的悠久历史；同时第一届广东省大学生程序设计竞赛也在位处广州的中山大学举办。二十年后的今天，北京路步行街已成为广州最负盛名的景点和购物胜地之一，而广东省大学生程序设计竞赛也迎来了自己的二十岁生日。

在步行街中，有 $n$ 间商店买卖同一种商品，第 $i$ 间商店一件商品的收购价和出售价均为 $a_i$ 元。为了防止过度交易，步行街有一个规定：您在第 $i$ 间商店最多进行 $b_i$ 次交易（一次买或一次卖均计为一次交易），且每次只能交易一件商品。

您准备通过在步行街中买卖这种商品来赚钱。假如初始时有无限的金钱（也就是说，不会因为钱不够而买不了一件商品），您最多能在步行街中赚到多少总利润？具体来说，``利润``指的是卖出商品获得的金钱总额，减去购买商品花费的金钱总额。

## 样例 #1

### 输入

```
2
4
10 2
30 7
20 4
50 1
2
1 100
1 1000```

### 输出

```
100
0```

# 题解

## 作者：what_could_I_do (赞：4)

[传送门](https://www.luogu.com.cn/problem/P9692)

很明显的贪心。

我们需要用尽可能少的价钱买下尽可能多的物品并用尽可能多的价钱卖出。

所以我们要先对题目给的序列进行排序，接下来用 $i$ 和 $j$ 表示序列的头尾两端，然后如果 $i$ 的交易次数比 $j$ 多，那么卖出的物品数量就是 $j$ 的次数，让 $j$ 减 $1$。如果 $j$ 的交易次数比 $i$ 多，那么卖出的物品数量就是 $i$ 的次数，$i$ 加 $1$。如果 $i$ 的价格已经与 $j$ 相同，就没必要交易了，退出。

# CODE:
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int n;
struct aaa
{
	long long a,b;
}c[100010];
inline bool cmp(aaa x,aaa y)
{
	return x.a<y.a;
}
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		long long ans=0;
		scanf("%d",&n);
		for(register int i=1;i<=n;i++) scanf("%lld%lld",&c[i].a,&c[i].b);
		sort(c+1,c+n+1,cmp);
		int j=1,k=n;
		while(1)
		{
			if(c[j].a==c[k].a) break;
			if(c[j].b>c[k].b) ans+=(c[k].a-c[j].a)*c[k].b,c[j].b-=c[k].b,k--;
			else ans+=(c[k].a-c[j].a)*c[j].b,c[k].b-=c[j].b,j++;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：DFbd (赞：4)

想要利润更多，就一定是在最便宜的地方买入，最贵的地方卖出，所以我们按 $a_i$ 从小到大排序，然后用 $l$ 表示 $b_l > 0$ 的 $a_l$ 最小的商店，$r$ 表示 $b_l > 0$ 的 $a_r$ 最大的商店。

如果当前 $b_r < b_l$，那就把利润加上在 $r$ 商店卖出 $b_r$ 个商品获得的钱，减去在 $l$ 商店买入 $b_r$ 个商品使用的钱。

如果当前 $b_l \le b_r$，那就把利润加上在 $r$ 商店卖出 $b_l$ 个商品获得的钱，减去在 $l$ 商店买入 $b_l$ 个商品使用的钱。

如果 $l$ 或 $r$ 商店没有交易次数了，就移动指针。

直到 $l = r$ 的时候，再交易就是在同一个商店买入和卖出，利润不会增加，直接结束。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
struct node {
  int b, c;
} a[100005];
int t, n, ans;
bool cmp(node a, node d) {
  return a.b < d.b;
}
signed main() {
  cin >> t;
  while (t--) {
    ans = 0;
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i].b >> a[i].c;
    }
    sort(a + 1, a + n + 1, cmp);
    int l = 1, r = n;
    while (l < r) {
      while (a[l].c > 0 && l <= r) {
        if (a[l].c < a[r].c) {
          ans += a[l].c * a[r].b - a[l].c * a[l].b;
          a[r].c -= a[l].c;
          a[l].c = 0;
        } else {
          ans += a[r].c * a[r].b - a[r].c * a[l].b;
          a[l].c -= a[r].c;
          r--;
        }
      }
      l++;
    }
    cout << ans << "\n";
  }
  return 0;
}
```

---

## 作者：jiangjiangQwQ (赞：2)

### 思路
需要明确的是，对于一件商品，我们从赚取利润的角度去考虑，肯定是卖给比这件商品买来的价格更高的店。比如买了两件价格为 $1$，卖给一个能交易两次，价格为 $4$ 的店。那么我赚取的利润为 $2\times(4-1)=6$ 元。这种思想就是贪心。
### 优化
按照上述思路编写代码，会发现最后一个点超时了。有可能是你的程序再将低价格商品卖给高价格的店时，高价格的店已经没有交易次数可用，那么这个店之后也不能再交易，将它排除，以免后面又从它开始交易，但这个店没有实际意义了。这是一个优化。
### 代码
```cpp
#include<bits/stdc++.h>
#include<algorithm>
using namespace std;
#define int long long
#define re register
#define For(i,l,r) for(re int i=l;i<=r;i++)
#define Rep(i,l,r) for(re int i=l;i>=r;i--)
#define ls(c) c<<1
#define rs(c) c<<1|1
const int N=3e5+5;
inline void fast(){
	   ios::sync_with_stdio(false);
	   cin.tie(0);cout.tie(0);
}
inline void read(int &x){
	   x=0;int f=1;
	   char c=getchar();
	   while(!isdigit(c)){
			if(c=='-') f=-1;
			c=getchar();
	   }while(isdigit(c)){
			x=x*10+c-'0';
			c=getchar();
	   }x*=f;
}
inline void write(int x){
	   if(x<0){x=-x;putchar('-');}
	   if(x>9) write(x/10);
	   putchar(x%10+'0');
}int t;
int n;
struct node{
	int a,b;
}k[N];
bool comp(node x,node y){
	return x.a<y.a;
}
signed main(){
	fast();
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>k[i].a>>k[i].b;		
		}sort(k+1,k+n+1,comp);//按价格排序
		int ans=0,last=n;
		for(int i=1;i<=n;i++){
			if(k[i].b==0) continue;
			for(int j=last;j>i;j--){//last是从哪个店开始交易
				if(k[i].b==0) break;
				int t=min(k[j].b,k[i].b);
           //t为这两个店的最大交易次数
				ans+=t*(k[j].a-k[i].a);
				k[j].b-=t;k[i].b-=t; 
				if(k[j].b==0) last--;//不能再次交易
			}
		}
//		for(int i=1;i<=n;i++){
//			cout<<k[i].a<<' '<<k[i].b<<'\n';
//		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：2c_s (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P9692)

## 思路

贪心。

读入数据后按照价钱从大到小排序。之后用双指针查找用哪个店买、哪个店卖。从价格低的店买，价格高的店卖。之后再加模拟即可。

- 如果两个店剩余的交易次数相等，那么用交易次数乘两个店的差价就是这两个店的最大利益。之后两个店的指针都向数列中间移动。

- 如果两个店剩余的交易次数不相等，那么用两个店中较小的交易次数乘这两个店的差价就是最大利益。之后把交易次数较小的那个店的指针向数列的中间移动，并且让较大交易次数的店的剩余交易次数 $-$ 交易次数较小的店的交易次数。

当两个指针相等或卖出的指针比买入的指针小的时候跳出循环。最后输出最大总利益即可。

- 数据范围较大，别忘开 long long。

## AC Code

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define pb push_back
#define pf push_front
#define pob pop_back
#define pof pop_front
#define pii pair<int,int>
#define pli pair<ll,int>
#define pll pair<ll,ll>
#define pil pair<int,ll>
#define fi first
#define se second
using namespace std;
inline ll read(){//快读。
	ll k=0,flag=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')flag=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		k=(k<<1)+(k<<3)+(c^48);
		c=getchar();
	}
	return k*flag;
}
inline void print(ll x){//快写。
    if(x<0){
        putchar('-');
        x=-x;
    }
    ll y=10,len=1;
    while(y<=x){
        y=(y<<1)+(y<<3);
        len++;
    }
    while(len--){
        y/=10;
        putchar(x/y+48);
        x%=y;
    }
}
const int N=1e5+10;
int n;
struct node{
	ll pri;
	int num;
}a[N];
inline bool cmp(node a,node b){
	return a.pri>b.pri;//注意从大到小排序。
}
int main(){
	int T;
	cin>>T;
	while(T--){
		n=read();
		for(int i=1;i<=n;++i)a[i].pri=read(),a[i].num=read();
		sort(a+1,a+1+n,cmp);
		int i=1,j=n;
		ll ans=0;
		while(i<j){
			if(a[i].num==a[j].num){
				ans+=1ll*a[i].num*(a[i].pri-a[j].pri);//用 1ll 乘是为了转化为 long long 类型。
				++i,--j;
			}
			else if(a[i].num<a[j].num){
				a[j].num-=a[i].num;
				ans+=1ll*a[i].num*(a[i].pri-a[j].pri);
				++i;
			}
			else{
				a[i].num-=a[j].num;
				ans+=1ll*a[j].num*(a[i].pri-a[j].pri);
				--j;
			}
		}
		print(ans);
		putchar('\n');//别忘输出回车。
	}
	return 0;
}
```

[已 AC](https://www.luogu.com.cn/record/127405474)

---

## 作者：skyskyCCC (赞：1)

## 前言。
赛时罚时 $2$ 次，一道贪心题。
## 分析。
因为利润指的是卖出商品获得的金钱总额，减去购买商品花费的金钱总额。所有想要使总体利益最大，那么一定要以更低的价格买进商品，然后以更高的价格卖出商品。

可以简单证明一下：这种商品，有 $a_i$ 与 $a_j$ 两种买入价格，其中 $a_i<a_j$ 成立，在购买个数 $b$ 相同的情况下，对于一种较高的卖出价格 $a_k$ 而言，因为 $a_i \times b$ 一定小于 $a_j \times b$ 的情况成立，所以整体的买入价格越小，即减数越小，在被减数 $b$ 不变的情况下，结果越大，所以得到以上的贪心策略。

可以用双指针模拟这一操作。

首先将商店按价格从低到高排序，一个指针从前往后搜，一个从后往前搜，直到指针重叠。在每次更新后，比较可以交易的数量，因为我们不能亏钱，所以我们不能多买，所以直接买较小的数量就可以了，然后用较大的卖出价格减去较小的价格，最后乘买进的数量就行了。

因为我们排过序，所以我们这样模拟指针，每次更新一定能取到当前最优解。

在每次更新完答案后，对于进行操作的两家商店的 $b_i$ 都要减去买入的数量，如果其中一家不能买了，或不能卖了，就将指针移动，否则就不移动。如果不移动，那我们就可以继续用**当前**最大的价格卖出或最低的价格买入。

当然考虑数据范围，我们考虑极端数据，即 $a_i$ 取 $1$ 且 $a_j$ 取 $10^6$ 时，并且 $b_i=b_j=10^6$ 的情况出现，此时即使 $n=2$ 也就是仅仅只有这两家店，总利润也达到了 $\left(10^6-1\right) \times 10^6$ 元，所以要扩大数据类型。

代码如下，仅供参考：
```
#include<iostream>
#include<algorithm>
//双指针维护 
using namespace std;
int t,n/*,a[100005],b[100005]*/;
struct node{
	int a;
	int b;
}s[100005];//用结构体存。
bool cmp(node x,node y){
    return x.a<y.a;
}
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		for (int i=1;i<=n;i++){
			cin>>s[i].a>>s[i].b;
		}
		sort(s+1,s+1+n,cmp);//排序。
		//for (int i=1;i<=n;i++){
		//	cout<<s[i].a<<s[i].b<<"\n";
		//}
		long long ans=0;
		for (int i=1,zz=n;i<zz;){
			//cout<<"yep!\n";
			int minn=min(s[i].b,s[zz].b);
			ans=ans+1ll*(s[zz].a-s[i].a)*minn;//这里是强制类型转化。
			s[i].b-=minn;
			s[zz].b-=minn;
			if(s[i].b==0){
				i++;
			}
			if(s[zz].b==0){
				zz--;
			}//指针操作。
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：CNS_5t0_0r2 (赞：1)

这题用贪心的做法，我们想让价值最大，就应用最小的成本卖最高的价。

所以我们先按价值排序，再用双指针法模拟，最后输出答案即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5 + 9;
int t,n;
struct item{
	int cost,cnt;
} a[N];
bool cmp(item i1,item i2){
	return i1.cost == i2.cost ? i1.cnt < i2.cnt : i1.cost < i2.cost;
}
signed main(){
	scanf("%lld", &t);
	for(;t;t--){
		scanf("%lld", &n);
		for(int i = 1;i <= n;i++)
			scanf("%lld%lld", &a[i].cost, &a[i].cnt);
		sort(a + 1,a + n + 1,cmp);
		int l = 1,r = n;
		int ans = 0;
		while(l < r){
			int Min = min(a[l].cnt,a[r].cnt);
			ans += (long long)(Min * (a[r].cost - a[l].cost));
			a[l].cnt -= Min;
			a[r].cnt -= Min;
			if(!a[l].cnt)
				l++;
			if(!a[r].cnt)
				r--;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：Κarrу5307 (赞：1)

按照 $a_i$ 进行排序后贪心。由于想要让买卖的差价尽量大，所以尽量从最小的 $i$ 买进，最大的 $i$ 卖出。维护两个指针 $l,r$，初始 $l=1,r=n$，表示在排序后的 $l$ 商店购入，$r$ 商店卖出，此时可以交易 $t=\min\{b_l,b_r\}$ 次，每次的利润都是 $a_r-a_l$。交易后 $b_l\gets b_l-t,b_r\gets b_r-t$。若一个位置的 $b$ 变为了 $0$，则移动指针（若是 $l$ 则右移，若是 $r$ 则左移）。若两个指针相撞，则退出循环。

---

## 作者：Yun_Mengxi (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P9692)

## 分析

双指针，加贪心来实现，双指针转移和贪心可以看下面这段代码：

```cpp
if (sp[i].num < sp[j].num) {      // i 买的没 j 卖的多
    sp[j].num -= sp[i].num;       // 把能买的买了
    ans += sp[i].num * (sp[j].val - sp[i].val);
    i++;                         // 买的地方只能往更贵的地方走
} else if (sp[i].num > sp[j].num) {  // i 买的比 j 多
    sp[i].num -= sp[j].num;        // 把能卖的卖了
    ans += sp[j].num * (sp[j].val - sp[i].val);
    j--;                          // 卖的地方只能往更便宜的地方走
} else {                          // 相等
    ans += sp[i].num * (sp[j].val - sp[i].val);          // 卖了赚差价（雾
    i++, j--;
}
```

## 代码

```cpp
#include <bits/stdc++.h>

#define int long long  // 不开____见____

using namespace std;

struct Edge {
  int val, num;
} sp[100005];

int t;
int n, ans;

signed main() {
  cin >> t;
  while (t--) {
    cin >> n;
    ans = 0;
    for (int i = 1; i <= n; i++) {
      cin >> sp[i].val >> sp[i].num;
    }
    sort(sp + 1, sp + n + 1, [](const Edge &a, const Edge &b) { return a.val < b.val; });
    for (int i = 1, j = n; i < j;) {
      if (sp[i].num < sp[j].num) {
        sp[j].num -= sp[i].num;
        ans += sp[i].num * (sp[j].val - sp[i].val);
        i++;
      } else if (sp[i].num > sp[j].num) {
        sp[i].num -= sp[j].num;
        ans += sp[j].num * (sp[j].val - sp[i].val);
        j--;
      } else {
        ans += sp[i].num * (sp[j].val - sp[i].val);
        i++, j--;
      }
    }
    cout << ans << "\n";
  }
  return 0;
}
```

---

