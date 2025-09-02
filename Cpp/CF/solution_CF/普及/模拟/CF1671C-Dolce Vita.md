# Dolce Vita

## 题目描述

Turbulent times are coming, so you decided to buy sugar in advance. There are $ n $ shops around that sell sugar: the $ i $ -th shop sells one pack of sugar for $ a_i $ coins, but only one pack to one customer each day. So in order to buy several packs, you need to visit several shops.

Another problem is that prices are increasing each day: during the first day the cost is $ a_i $ , during the second day cost is $ a_i + 1 $ , during the third day — $ a_i + 2 $ and so on for each shop $ i $ .

On the contrary, your everyday budget is only $ x $ coins. In other words, each day you go and buy as many packs as possible with total cost not exceeding $ x $ . Note that if you don't spend some amount of coins during a day, you can't use these coins during the next days.

Eventually, the cost for each pack will exceed $ x $ , and you won't be able to buy even a single pack. So, how many packs will you be able to buy till that moment in total?

## 说明/提示

In the first test case,

- Day 1: prices are $ [2, 1, 2] $ . You can buy all $ 3 $ packs, since $ 2 + 1 + 2 \le 7 $ .
- Day 2: prices are $ [3, 2, 3] $ . You can't buy all $ 3 $ packs, since $ 3 + 2 + 3 > 7 $ , so you buy only $ 2 $ packs.
- Day 3: prices are $ [4, 3, 4] $ . You can buy $ 2 $ packs with prices $ 4 $ and $ 3 $ .
- Day 4: prices are $ [5, 4, 5] $ . You can't buy $ 2 $ packs anymore, so you buy only $ 1 $ pack.
- Day 5: prices are $ [6, 5, 6] $ . You can buy $ 1 $ pack.
- Day 6: prices are $ [7, 6, 7] $ . You can buy $ 1 $ pack.
- Day 7: prices are $ [8, 7, 8] $ . You still can buy $ 1 $ pack of cost $ 7 $ .
- Day 8: prices are $ [9, 8, 9] $ . Prices are too high, so you can't buy anything.

 In total, you bought $ 3 + 2 + 2 + 1 + 1 + 1 + 1 = 11 $ packs.In the second test case, prices are too high even at the first day, so you can't buy anything.

In the third test case, you can buy only one pack at day one.

In the fourth test case, you can buy $ 2 $ packs first $ 500 $ days. At day $ 501 $ prices are $ [501, 501] $ , so you can buy only $ 1 $ pack the next $ 500 $ days. At day $ 1001 $ prices are $ [1001, 1001] $ so can't buy anymore. In total, you bought $ 500 \cdot 2 + 500 \cdot 1 = 1500 $ packs.

## 样例 #1

### 输入

```
4
3 7
2 1 2
5 9
10 20 30 40 50
1 1
1
2 1000
1 1```

### 输出

```
11
0
1
1500```

# 题解

## 作者：Rnfmabj (赞：4)

做题背景：第一次场切C不吃罚时，撰题解以祭之。



------------
## 题意

有 $n$ 家糖果店，第 $i$ 家糖果店的糖果的初始价格为 $a_i$ 。

每家糖果店一天只会卖一颗糖，且糖果每天涨价，第 $i$ 天每家店的糖果价格都会上涨 $x-1$ 元。

你每天都会获得 $x$ 元的资金，只能当天消费，剩余的钱不能留到第二天。

显然，这样涨价下去你迟早会一个糖都买不起，求在此之前你一共能买多少糖果。



------------
## 思路

- “我会暴力！”

先对初始价格排序。

可以按题意每天涨价，然后扫一遍能买多少个。

复杂度 $O(nv)$ ， $v$ 为值域。

然而 $ 1≤a_i≤10^9 $ ，CF的少爷机也救不了。

- “我会费用提前计算！”

根据题意，在对初始价格升序排序后，一定是价格较高的糖果店先贵得买不起。

因为所有店涨的价格都是一样的，所以如果某天第 $k$ 个店我们买不起了，那么比它贵的店我们照样买不起（废话）。

所以我们可以维护初始价格的前缀和数组 $b$ ，以及所涨价格的累加值 $sum$ 。

从后往前扫描前缀和，对于第 $i$ 家店以及当前时间 $t$ ，如果 $b_i+sum × t ≤x$ 那么就可以开买，根据定义可以维持 $(x-b_i-sum×t)/t+1$ 天“购买前 $i$ 家店”的状态。

接着将这个天数累加进答案即可，时间复杂度 $O(n)$ 。



------------
## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define db double
#define R read()
#define file(a) freopen(#a".in","r",stdin),freopen(#a".out","w",stdout)
using namespace std;
inline ll read() {
	ll s=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {
		if(ch=='-')f*=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		s=s*10+ch-'0';
		ch=getchar();
	}
	return s*f;
}
inline void write(ll x) {
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10),x%=10;
	putchar('0'+x);
}//Don't use it for CF.
inline void wk(ll x){write(x);putchar(' ');}
inline void we(ll x){write(x);putchar('\n');}
ll T;
ll a[200005],b[200005];
signed main(){
	T=R;
	while(T--){
		ll n=R,x=R;
//		memset(a,0,sizeof(a));
//		memset(b,0,sizeof(b)); 我就是多测不清空！
		for(ll i=1;i<=n;i++)a[i]=R;
		sort(a+1,a+n+1);//对初始价格排序
		for(ll i=1;i<=n;i++)b[i]=b[i-1]+a[i];//前缀和
		ll sum=0,ans=0;
		for(ll i=n;i>=1;i--){
			if(b[i]+sum*i>x){
				continue;//买不起直接走人
			}
			ll res=(x-b[i]-sum*i)/i+1;//还能买几天
			ans+=res*i;
			sum+=res;
		}
		we(ans);
	}
	return 0;
}



```


---

## 作者：如履薄冰 (赞：3)

# 解法
考虑使用**贪心算法**，我们对给出的糖价进行从小到大排序。每次从小到大判断你是否买得起这包糖，如果买得起，就用你今天还剩余的钱来买这包糖，并且将答案(你最终可以买到的糖数)加 $1$。如果买不起，直接退出循环，因为后面的糖只会更贵。如果你在这一天一包糖都买不起，直接输出答案，因为以后糖还会涨价。最后再将所有糖价加 $1$，你就能做对了。
# 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[1100000];
signed main(){
    ios::sync_with_stdio(false);
    int t;
    cin>>t;
    while(t--){
        int n,x,ans=0,xx;
        bool f=0;
        cin>>n>>x;
        xx=x;
        for(int i=1;i<=n;i++){
            cin>>a[i];
        }
        sort(a+1,a+n+1);
        while(true){
        	x=xx;
            f=0;
            for(int i=1;i<=n;i++){
                if(x>=a[i]){
                    x-=a[i];
                    ans++;
                    f=1;
                }else{
                    break;
                }
            }
            for(int i=1;i<=n;i++){
                a[i]++;
            }
            if(!f){
                break;
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：fish_love_cat (赞：2)

**题意**：

有 $n$ 个糖果店，每个糖果店每天会出售一个糖果，第 $i$ 个店第 $j$ 天出售的糖果价格为 $a_i+j-1$。你每天能拿到 $x$ 元零花钱，问你最多能买多少糖？

---

我们可以把糖价格从小到大排，然后做一个前缀和，从后往前计贡献。

因为你今天买不了的，以后一定买不了，所以忽略掉买不了的进行优化。

时间复杂度 $O(n \log n)$，瓶颈在于排序。

---

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int qzh[200005],a[200005];
signed main(){
    int t;
    cin>>t;
    while(t--){
        int n,k;
        cin>>n>>k;
        for(int i=1;i<=n;i++)
        cin>>a[i];
        sort(a+1,a+1+n);
        for(int i=1;i<=n;i++)
        qzh[i]=qzh[i-1]+a[i];
        int ans=0,x=0;
        for(int i=n;i>=1;i--){
            while(qzh[i]+x*i>k)i--;
            if(i==0)break;
            int flc=(k-qzh[i]-x*i)/i+1;
            x+=flc;
            ans+=flc*i;
        }
        cout<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：jiangtaizhe001 (赞：1)

[可能更好的阅读体验](https://www.cnblogs.com/jiangtaizhe001/p/16196330.html)
### 题目大意
摘自洛谷的翻译：  
动乱的时代就要来了，因此你决定储备一些糖。有 $n$ 个商店卖糖：第 $i$ 个商店一包糖要 $a_i$ 硬币，但每人每天只能买一包。所以你为了买多几包糖，你得去好几家商店。  
另外一个问题就是糖价每天都在上涨：第一天 $a_i$ 硬币一包，第二天 $a_i+1$ 硬币一包，第三天 $a_i+2$ 硬币一包。对于每家商店都是如此。  
然而，你每天的预算只有 $x$ 硬币。也就是说，你每天花在糖上的钱不能超过 $x$ 硬币。如果你一天的预算没有花完，第二天也不能花前一天剩下来的钱。  
最终，每包糖的价格都会超过 $x$，你将一包糖都买不起。所以，在那之前，你最多能买多少包糖？  
$1\le n\le 2\times10^5,1\le x\le 10^9,1\le a_i\le10^9$
### 题目解析
不难想到每天肯定买便宜的糖，由于每天所有糖涨价的速度是一样的，所以相对的大小不会变。  
所以首先我们需要排序。  
然后直接暴力做显然是不可行的。  
我们可以先做一次前缀和，枚举 $i$ 从 $1$ 到 $n$，然后直接二分出最小的 $s$ 使得第 $s$ 天不买不起 $i$ 包糖。  
复杂度 $\Theta\left(n\log x\right)$。

参考代码：
```cpp
void work(){
	n=read(); x=read(); int i; for(i=1;i<=n;i++) a[i]=read(); sort(a+1,a+n+1); ans=0;
	for(i=1;i<=n;i++) a[i]+=a[i-1];
	for(i=1;i<=n;i++){
		l=-1,r=x+10;
		while(l+1<r){
			mid=(l+r)>>1;
			if(a[i]+(ll)mid*(ll)i<=x) l=mid; else r=mid;
		} ans+=l+1;
	} print(ans),pc('\n');
}
```

---

## 作者：Henry_C (赞：1)

# 题意
$\qquad n(1 \le n \le 2 × 10^5)$ 个商店，每个商店的售卖一种糖果，一开始第 $i$ 个商店的糖果价格为 $a_i(1 \le a_i \le 10^9)$ 每袋，此后每天每袋糖果涨价1块钱。你每天的预算是 $x(1 \le x \le 10^9)$ 元,商店的糖果限量供应，每个商店每人每天限购1袋糖果，求最多可以买到多少袋糖果？
# 解题思路
$\qquad$随着天数增加，每天能买到的糖果数量会逐渐减少；此外，捡便宜的糖果买，可以得到更多的糖果，因此对糖果按价格升序排序。考虑到商店的数量 $n(1 \le n \le 2 × 10^5) $，可以从大到小枚举商店数量，商店数量为$i$时，不考虑时间影响，需要 $\text{sum}_i=\sum_{j=1}^i a_j$ 元，可以购买的天数为 $t_i=\frac{(x-\text{sum}_i)}{i}+1$ ，此时对糖果购买量的贡献为 $(t_i-t_{last})*i$ ，$ t_{last} $为上一次计算的可以购买的天数，$t_{last}$ 不一定是 $t_{i-1}$ 。

$\qquad$$\text{sum}_i=\sum_{j=1}^i a_j$ 的计算可以用前缀和，也可以在倒着枚举的时候减去当前商店糖果价格。 $\text{sum}_i=\sum_{j=1}^i a_j$ 的计算将超出 int 范围，因此需要使用 long long 类型。


# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int Nmax = 2e5+5;
int t,n;
LL x;
LL a[Nmax];

struct pre1D{
    LL s[Nmax];

    void init(int n){
        for(int i=0; i<=n; i++)
            s[i] = 0;
        for(int i=1; i<=n; i++)
            s[i] = s[i-1] + a[i];
    }

    LL getRange(int l, int r){
        return s[r]-s[l-1];
    }
};

pre1D preSum;

int main() {
//    freopen("1.in","r",stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> t;
    while(t--){
        cin >> n >> x;
        for(int i=1; i<=n; i++)
            cin >> a[i];
        sort(a+1, a+n+1);
        preSum.init(n); //前缀和

        LL lastDay = 0, sum = 0;
        for(int i=n; i>=1; i--){
            LL res = x - preSum.getRange(1, i);
            if(res<0) continue;
            else{
                LL day = res/i + 1; //可以购买的天数, 要算上之前第1天
                sum += (day - lastDay)*i; //新增的购买量
                lastDay = day; //更新时间
            }
        }
        cout << sum << endl;
    }
    return 0;
}
```


---

## 作者：ryanright (赞：1)

对于某一天的策略就是贪心地选择糖价最便宜的一些商店去购买，直到预算不够花。最笨的方法就是模拟每天，寻找最便宜的一些商店。但这样做的单组数据最坏时间复杂度为 $O(xn\log n)$，每天都排序。

发现所有商店的糖价都是一块上涨的，而且每天都上涨 $1$ 硬币。因此原来便宜的商店，涨价之后还是较为便宜的。糖价上涨只是把糖价贵的一些商店给排除掉，剩下的还是要照样买，而且不会有新的选择。所以我们只需要排一遍序，然后每次记录当前最多能卖的商店数目。单组数据最坏时间复杂度 $O(n\log n+xn)$，还是不够。

我们都排序了，于是考虑使用前缀和。设 $s_i=\sum_{j=1}^ia_j$，那么我们每次就只需要 $O(1)$ 时间判断当前状态会不会改变。单组数据最坏时间复杂度 $O(n\log n+x)$。但 $x$ 实在是太大了。

上正解吧。

我们并不需要枚举每一天，因为经过上面的一波分析，会有相当长的一段时间状态都是一样的。因此我们可以直接计算还有多少天状态就会改变：

$$\Delta d=\max\bigg(\bigg\lfloor\frac{x-s_p}{p}\bigg\rfloor-d+2,0\bigg)$$

其中，$\Delta d$ 指的是这种状态还能持续多少天，$p$ 指的是当前最多能去多少家商店（也就是当前状态），$d$ 指的是当前是第几天。下面给出推导过程：

根据定义，在第 $d+\Delta d-1$ 天时，预算还能够支持去买 $p$ 家店的糖，但是第 $d+\Delta d$ 天就不可以了。即

$$\begin{cases}s_p+p(d+\Delta d-2)\leqslant x\\s_p+p(d+\Delta d-1)>x\end{cases}$$

解得

$$\Delta d=\bigg\lfloor\frac{x-s_p}{p}\bigg\rfloor-d+2$$

但是单单这么算，$\Delta d$ 可能会小于 $0$，因此要和 $0$ 取 $\max$，便有了我们的结论。由于最多只有 $n$ 种状态，所以这个算法的单次时间复杂度为 $O(n\log n+n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int a[200005], s[200005];
signed main() {
	int T;
	cin >> T;
	while (T--) {
		int n, x, day = 1;
		cin >> n >> x;
		for (int i = 1; i <= n; i++)
			cin >> a[i];
		sort(a + 1, a + n + 1);
		int now = -1, ans = 0;
		for (int i = 1 ; i <= n; i++) {
			s[i] = s[i - 1] + a[i];//计算前缀和
			if (s[i] > x && now == -1)//找出初始状态
				now = i - 1;
		}
		if(now == -1)//一开始全部都能买
			now = n;
		while (now) {
			int nday = max((x - s[now]) / now - day + 2, 0ll);//计算Δd
			ans += nday * now;
			day += nday;
			now--;
		}
		cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：zcxxnqwq (赞：1)

**题目大意：**

给定一个长度为 $n$ 的序列 $a$，每天 $a$ 中每个元素的值加一，每天选取的元素的 $ai$ 之和不能超过 $x$，求最多选取多少个元素。

**思路：**

首先想到贪心，将 $a$ 从小到大排序，每次从价格最小的开始选，而由于每天每个元素增加量相同，所以自始至终各元素之间的大小关系不变。

对于初始的数组 $a$，枚举一遍找到最多能选取的元素数记为 $len$ 及前 $len$ 个元素和 $tot$，那么对于当前 $len$ 个元素在代价总和不超过 $x$ 的情况下还能继续选 $cnt = (x-tot)/len$ 天，再过一天就最多只能选 $len-1$ 个了，而要舍弃的元素必定是代价最大的元素 $a[len]$。

再考虑在这 $cnt$ 天内 $tot$ 的变化。 $len$ 个物品共涨价 $len*cnt$，而舍弃第 $len$ 个物品减小的代价为 $a[len]+sum$，其中 $sum=Σcnt$。

然后这道题就可以完美结束了。
```cpp
#include<cstdio>
#include<algorithm>
#define int long long
using namespace std;
inline int read(){
	register int x=0,f=1;
	register char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}
const int N=2e5+5;
int T,n,x,a[N];
signed main(){
	T=read();
	while(T--){
		n=read(),x=read();
		for(register int i(1);i<=n;++i) a[i]=read();
		sort(a+1,a+n+1);
		if(a[1]>x){printf("0\n");continue;}
		int tot=0,len=n,ans=0,sum=0;//不要忘了初始化 
		for(register int i(1);i<=n;++i){
			tot+=a[i];
			if(tot>x){tot-=a[i],len=i-1;break;}//当前i不符合条件，不算 
		}
		ans+=len;
		while(len>=1){
			int cnt=(x-tot)/len;
			ans+=cnt*len,sum+=cnt;
			tot=tot+cnt*len-(a[len]+sum);
			len--;
		}
		printf("%lld\n",ans);		
	}
	return 0;
}
```


---

## 作者：Toorean (赞：1)

## 题意
每天你有 $x$ 元钱，$n$ 件物品，第 $i$ 件物品价钱为 $p_i$，第 $k$ 天第 $i$ 中物品的价格是 $p_i+k-1$，求当买不起任何物品时你已经购买的物品数。

## 思路
显然本题不可直接暴力。由于每天的价格都会提高，所以物品数也在相应递减。我们仅需计算每一天的可购买的物品数，即可求出答案。将其转化一下，则我们须求**相对应物品数可购买到的天数**，之后将不同天数且物品量**最大**的物品量相加并减去重复天数的差即可求出答案。

下面是。不难发现，每天每件物品所需价格之和会增长 $n$。不妨使价格便宜的物品放在前面，以便于求本日可购买的物品数。即以字典序排序 $p$ 序列。之后用 $f_i$ 表示第一天购买 $i$ 件物品的价钱，不难推导出买 $i$ 件物品可持续的天数 $days_i$ 为 $\begin{cases}1+\lfloor\dfrac{(x-f_i)}{i}\rfloor,&f_i\leq x\\0,&f_i>x\end{cases}$，此时，我们仅需从大到小来计算可购买的物品量即可。

## AC Code
```cpp
#define ffor(_INDEX,l,r) for (int _INDEX = (l); _INDEX <= (r); _INDEX++)
#define rfor(_INDEX,l,r) for (int _INDEX = (l); _INDEX >= (r); _INDEX --)

void solve () {

    memset (arr, 0, sizeof (arr));
    memset (f, 0, sizeof (f));

    LL cheap = INF, ans = 0;
    read (n, x);
    ffor (i, 1, n) {
        read (arr[i]);
        cheap = min (cheap, arr[i]);
    }
    
    if (cheap > x) {
        puts ("0");
        return ;
    }
    
    std :: sort (arr + 1, arr + n + 1);
    
    ffor (i, 1, n) {
        f[i] = f[i - 1] + arr[i]; 
        days[i] = (f[i] <= x) + (f[i] <= x ? ((x - f[i]) / i) : 0);
    }

    ans = days[n] * n;
    rfor (i, n, 2) {
        LL add = (days[i - 1] - days[i]) * (i - 1);
        ans += add;
    }
    
    printf ("%lld\n", ans);
}
```

---

## 作者：xiaobeng_0912 (赞：0)

## $\mathbf{Knowledge}$

1. 贪心

## $\mathbf{Solution}$

因为要求**最多能买多少包糖**，所以可以考虑到贪心。

首先对糖价从小到大排序，然后模拟你每天买糖的过程：

按糖价从小到大来看每一包糖，如果买得起，就直接买。而后，将你最终可以买到的糖数（答案）加一。

如果你买不起这包糖，就结束这一天的买糖活动。因为从小到大排序后，你买不起这包糖，那后面的糖你也买不起。

如果某天你连一包糖都买不起了，就不再买糖，直接输出答案。因为之后的糖价持续上涨，你更买不起了。

## $\mathbf{Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n,m,a[200001],tmp,sum,flag;
signed main(){
    scanf("%d",&t);
    while(t--){
    	sum=0;
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
        }
        sort(a+1,a+n+1);
        while(1){//模拟买糖过程
        	tmp=m;
            flag=0;
            for(int i=1;i<=n;i++){//模拟当天买糖过程
            	if(tmp>=a[i]){//如果可以买就买
            		flag=1;
            		tmp-=a[i];
            		sum++;
				}else{//如果买不起就结束这一天的买糖活动
					break;
				}
				a[i]++;//糖价上涨
			}
			if(flag==0){//如果这一天你连一包糖都买不起了就不再买糖
				break;
			}
        }
        printf("%d\n",sum);
    }
    return 0;
}
```

---

## 作者：guoxinda (赞：0)

## 思路
我们先将每家店刚开始要卖的钱数从低到高排序，然后用前缀和。\
然后按题意遍历直到最便宜的一家店 $\le x$ 跳出循环。\
在这个过程中，我们要找到前缀和数组中第一个 $>x$ 的数的下标 $-1$ 的数，因为这样可以找到 $\le x$ 的最大的糖袋数。\
发现可以用 upper_bound。
- 有没有特殊情况呢？\
有。当数组中没有比 $x$ 大的数时，这个函数会返回 $n+1$。但这种情况可以用上述方法计算。
注意，前缀和每次遍历的第 $i$ 项要 $+i$，因为前缀共有 $i$ 家店。
## code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,x,a[100010],ans,s;
signed main(){ 
	ios::sync_with_stdio(0);
	cin>>n;
	while(n--){
		ans=0;
		memset(a,0,sizeof(a));//初始化 
		cin>>m>>x;
		for(int i=1;i<=m;i++){
			cin>>a[i];
		}
		sort(a+1,a+m+1);
		for(int i=1;i<=m;i++){
			a[i]+=a[i-1];//前缀和
		}
		while(a[1]<=x){
			s=upper_bound(a+1,a+m+1,x)-a-1;
			ans+=s;
			for(int i=1;i<=m;i++){
				a[i]+=i;//前i家店+i 
			}
		}
		cout<<ans<<endl;
	}
}
```

---

## 作者：浮光掠影 (赞：0)

### 解题思路

假设预算 $x$ 能够在每家商店都买一包糖，那么每天就可以买 $n$ 包，直到有一天每家商店的价格之和超过 $x$ 了，那么根据贪心的思想，我们不买最贵的那家，选择剩下的 $n-1$ 家，这样每天就能买 $n-1$ 包，直到 $n-1$ 家商店的价格之和也超过 $x$，以此类推。

那么我们先将每家商店的初始价格从大到小排好序，设 $\text{days}[i]$ 表示除去前 $i-1$ 家商店，每天购买第 $i$ 到 $n$ 家商店的 $n-i+1$ 包糖最多能买到第几天而不会超过预算 $x$。

因此在 $1 \sim \text{days}[1]$ 天每天能购买 $n$ 包糖，在 $\text{days}[1] \sim \text{days}[2]$ 天每天能购买 $n-1$ 包糖，以此类推，即 $\text{res} = \text{days}[1] \times n + (\text{days}[2] - \text{days}[1]) \times (n-1) + \cdots + (\text{days}[n] - \text{days}[n-1])$。

### Code


```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long LL;
const int N = 200010;
int a[N], days[N];
int n, x;

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        cin >> n >> x;
        LL sum = 0, res = 0;
        for (int i = 0; i < n; i++) cin >> a[i], sum += a[i];
        sort(a, a + n, greater<int>());
        for (int i = 0; i < n; i++)
        {
            if (sum > x) days[i] = 0;
            else days[i] = (x - sum) / (n - i) + 1;
            sum -= a[i];
        }
        for (int i = 0; i < n; i++)
        {
            if (!i) res += days[i] * n;
            else res += (days[i] - days[i - 1]) * (n - i);
        }
        cout << res << endl;
    }
    return 0;
}

```

---

