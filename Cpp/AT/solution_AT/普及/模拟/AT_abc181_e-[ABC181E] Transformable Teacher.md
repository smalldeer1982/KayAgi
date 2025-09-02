# [ABC181E] Transformable Teacher

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc181/tasks/abc181_e

$ N $ 人の児童がおり、 $ i $ 番目の児童の身長は $ H_i $ です。 $ N $ は奇数です。

今から、先生であるあなたを含めた $ N+1 $ 人で $ 2 $ 人 $ 1 $ 組を $ \large\frac{N+1}2 $ ペア組みます。

あなたの目標は、それぞれのペアの身長の差の合計を最小化することです。  
 すなわち、 $ i $ 番目のペアの身長の組を $ (x_i,\ y_i) $ としたとき、 $ \displaystyle\ \sum_{i=1}^{(N+1)/2}|x_i-y_i| $ を最小化したいです。

あなたには $ M $ 個の変身形態があり、 $ i $ 番目の変身形態での身長は $ W_i $ です。

あなたの変身形態とペアの組み方を工夫することで、それぞれのペアの身長の差の合計が最小でいくつにできるか求めてください。

## 说明/提示

### 制約

- 入力はすべて整数
- $ 1\ \leq\ N,\ M\ \leq\ 2\ \times\ 10^5 $
- $ N $ は奇数
- $ 1\ \leq\ H_i\ \leq\ 10^9 $
- $ 1\ \leq\ W_i\ \leq\ 10^9 $

### Sample Explanation 1

身長 $ 8 $ の変身形態を選び、身長が $ (1,\ 2),\ (3,\ 4),\ (7,\ 8) $ のペアを作ると最小になります。

## 样例 #1

### 输入

```
5 3
1 2 3 4 7
1 3 8```

### 输出

```
3```

## 样例 #2

### 输入

```
7 7
31 60 84 23 16 13 32
96 80 73 76 87 57 29```

### 输出

```
34```

## 样例 #3

### 输入

```
15 10
554 525 541 814 661 279 668 360 382 175 833 783 688 793 736
496 732 455 306 189 207 976 73 567 759```

### 输出

```
239```

# 题解

## 作者：HongzheLi (赞：2)

本蒟蒻第一次拿最优解，发篇题解纪念一下。
## 题意
有 $n$ 个儿童，第 $i$ 个儿童的身高是 $h_i$。$n$ 是奇数。老师加入了这 $n+1$ 人中，将他们分成 $\dfrac{n+1}{2}$ 对。求身高差的总和最小值。
## 思路
很明显就是一个贪心，把儿童的身高排好序后插入老师的身高。把老师的每一种变身形态都模拟一遍即可。于是可以二分老师的位置，我们发现如果插入老师的身高后：老师和一个儿童匹配，前面的儿童的组合不变，后面的儿童组合后移。

![](https://cdn.luogu.com.cn/upload/image_hosting/d0b8tksd.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

这很好解决，把奇数位与其后面的偶数位的差值和偶数位与其后面奇数位的差值的前缀和预处理出来就可以了。身高差的总和就是不变的前缀和加上变化后的前缀和加上老师和那个儿童的差值。

时间复杂度 $O(m \log n)$。

## 实现

```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const ll inf=1E18+7;
const ll N=2E5+10;
ll n,m,h[N],w[N],qzh0[N],qzh1[N],l,Max=inf,res,r,to[N],q;
void init(){
	cin>>n>>m;
	to[0]=1;
	for(ll i=1;i<=n;i++){
		cin>>h[i];
		to[i]=to[i-1]+((i&1)&&(i>1));
	}
	to[n+1]=(n+1)/2;
	sort(h+1,h+n+1);
	for(ll i=1;i<=n;i++){
		qzh0[i]=qzh0[i-1];
		qzh1[i]=qzh1[i-1];
		if(!(i&1)){
			qzh0[i]+=(h[i]-h[i-1]);
			qzh1[i]+=(h[i+1]-h[i]);
		}
	}
	for(ll i=1;i<=m;i++){
		cin>>w[i];
	}
	sort(w+1,w+m+1);
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	init();
	for(ll i=1;i<=m;i++){
		l=lower_bound(h+1,h+n+1,w[i])-h;
		q=to[l];
		if(l==n+1)res=abs(w[i]-h[n]);
		else{
			res=abs(w[i]-h[q*2-1]);
		}
		res+=qzh0[q*2-2];
		res+=qzh1[n]-qzh1[q*2-2];
		Max=min(Max,res);
	}
	cout<<Max<<endl;
	return 0;
}
```
这是第四次写这题的题解，前三次写态度不端正，本蒟蒻深刻认识到自己的错误，认真的读了[题解审核及反馈要求](https://www.luogu.com.cn/discuss/174934)，认认真真的写的这篇题解，求求管理员让我通过吧。

---

## 作者：ForgetOIDuck (赞：1)

### 思路：
显然，加入这个人之后位置相邻的两个人两两配对是最优的。

所以有暴力做法：每次把 $B_i$ 加到 $A$ 里排序遍历一遍，算出答案求最小值。但这时间复杂度是 $O(N\times M\log N)$ 的。

然后我们发现可以先提前把还没有加人的 $A$ 排序，$B_i$ 在 $A$ 中即将添加的位置是确定的。

所以首先我们可以使用二分查找，找到 $B_i$ 在 $A$ 中即将添加的位置 $p$。

然后 $p$ 左右两边已经配对完的答案是可以直接用前缀和 / 后缀和预处理出来的。

记得判断一下 $B_i$ 是与 $a_{p+1}$ 还是与 $a_{p-1}$ 配对。

最后全部加起来统计入答案。

时间复杂度 $O(M\log N)$。

### AC 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n, m, a[500004], su[500004], us[500004], anss = 0x3f3f3f3f;
int main() {
	cin >> n >> m;
	for (ll i = 1; i <= n; i ++ ) cin >> a[i];
	sort(a + 1, a + n + 1);
	for (ll i = 2; i <= n; i += 2) su[i] = su[i - 2] + a[i] - a[i - 1];
	for (ll i = n - 1; i; i -= 2) us[i] = us[i + 2] + a[i + 1] - a[i];
	for (ll x; m --;) {
		cin >> x;
		ll l = 1, r = n, ans = 0;
		while (l <= r) {
			ll mid = l + r >> 1;
			if (a[mid] <= x) l = mid + 1, ans = mid;
			else r = mid - 1;
		} 
		if (ans % 2) anss = min(anss, su[ans - 1] + us[ans + 1] + x - a[ans]);
		else anss = min(anss, su[ans] + us[ans + 2] + a[ans + 1] - x);
	}
	cout << anss;
}
```

---

## 作者：LiJinLin_AFO (赞：1)

# AT_abc181_e 题解

~~快把我调疯了~~

首先我们要弄清楚这个点到底放在哪儿。

假设数轴上有这么几个点（如下图）。

![无标题5.png](https://pic.ziyuan.wang/user/guest/2024/02/无标题5_c63f16c6ec42b.png)

有这么几种 $\sum |x_i-y_i|$ 的情况。

1. 按从左到右顺序两两搭配。如下。

![pFGMg3j.png](https://s11.ax1x.com/2024/02/15/pFGMg3j.png)

2. 另外的一些情况，例如这几种。

![无标题5.png](https://pic.ziyuan.wang/user/guest/2024/02/无标题5_22e701ea09a0a.png)

![无标题5.png](https://pic.ziyuan.wang/user/guest/2024/02/无标题5_c43d649a824eb.png)

~~看都可以看出来~~第一种情况的 $\sum |x_i-y_i|$ 是最小的。

所以，我们可以先将输入的数组 $H$ 从小到大排序，在数组 $H$ 中寻找第一个大于等于 $W_i$ 的位置，插入这个数，再按照最优情况计算和值，求出最小值并输出，或许可以。

不过，用脚指头算算都知道可能会超时，所以我们需要对程序进行一些优化，就真正的大功告成了。

1. 二分法寻找第一个大于等于 $W_i$ 的位置。注意，不能使用 `lower_bound` 函数，否则连样例都过不了。

2. 前缀、后缀优化。这是这道题的重头戏。这免去了一遍遍循环求解。

这样，时间复杂度就从 $O(MN)$ 降到了 $O(M\log{N})$。

```cpp
#include<stdio.h>
#include<algorithm>
using namespace std;
#define int long long
int n,m,ans=1e18;
int a[200005],sum1[200005],sum2[200005];
signed main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	sort(a+1,a+1+n);
	for(int i=2;i<=n;i+=2) sum1[i]=sum1[i-2]+abs(a[i]-a[i-1]);
	for(int i=n-1;i>=2;i-=2) sum2[i]=sum2[i+2]+abs(a[i]-a[i+1]);
	for(int i=1,x;i<=m;i++){
		scanf("%lld",&x);
		int l=1,r=n,yu=1;
		while(l<=r){
			int mid=(l+r)/2;
			if(x>=a[mid]) l=mid+1,yu=mid; 
			else r=mid-1;
		}
		if(yu%2==1) ans=min(ans,sum1[yu-1]+abs(a[yu]-x)+sum2[yu+1]);
		else ans=min(ans,sum1[yu]+abs(a[yu+1]-x)+sum2[yu+2]);
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：Tian36309 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc181_e)

**题目描述:**

给定一个有奇数个数字的数组 $A$ ，以及一个数组 $B$ ，要求在 $B$ 数组中找出一个数塞进 $A$ 数组里面，然后将 $A$ 数组中的数字两两组合，每组中大数减小数，再将结果相加，最小化这个结果。

**思路：**

首先，我们假设已经找到了一个数塞进 $A$ 数组里，并将 $A$ 数组从小到大排序，设这时 $A$ 数组中有 $x$ 个数，分别为：

$$A_1,A_2,A_3 \dots A_{x-1},A_nx$$

首先我们要找出一种最好的组合方法，大致是这样的：

以 $x = 4$ 为例，假设这组数据是这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/a553xhsw.png)

那么，我们将 $A_1$ 和 $A_2$ 配对， $A_3$ 和 $A_4$ 配对，那么答案大概是这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/a13xbkqp.png)

但是，如果我们偏要反其道而行之，将 $A_2$ 和 $A_3$ 配对，那么答案就会变成这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/o6gcdbd8.png)

很明显前者更优。

因此我们可以得出结论：最优的配对方式就是前后两两配对。

那么接下来，我们来解决选数问题。

我们将 $A,B$ 数组都排好序后，可以使用双指针来快速定位 $B$ 数组中某个数在 $A$ 数组中的位置，以这组样例为例：

```
输入：
5 3
2 4 6 8 9
3 5 10

输出：
4
```

很明显，如果每个数塞进去后都 $O(n)$ 的求答案，是会超时的，那么怎么办呢？

先画张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/zt3yo5fl.png)

在 $A$ 数组中找到第一个比 $B$ 数组中当前数字大的数，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/nmg6l69q.png)

求出此时答案（方法后面会讲），然后将 $B$ 数组的指针指向下一位，并继续将 $A$ 指针右移直接至遇到比当前 $B$ 数组的指针指向的数字大的数，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/62toxf7e.png)

看到这里，细心的同学应该发现了，在加入数字位置之前的 $A$ 数组元素都是按照奇偶奇偶（这里的奇偶指的是在 $A$ 数组中的位置，下面同理）的顺序组合的，而指针指向的这个数字就是和新数字结合的数字，后面的则是按照偶奇偶奇的顺序组合的，那是不是意味着我们可以把所有的情况先预处理好，然后就可以 $O(1)$ 解决了？

正确！但其实还是要分情况的，比如我们看上上张图，和这个 $3$ 配对的并不是指针指向的 $4$ ，而是前面的 $2$ 。但总体而言，思路是正确的，后面的代码实现就比较简单了。

建立两个列表 $s1,s2$ 分别存储一奇一偶的组合以及一偶一奇的情况。再通过**前缀和**快速求和，最后分类讨论即可。细节会在代码中注明。

时间复杂度 $O(n+m)$ ，可以通过此题。

这里插一嘴，别的题解讲的好像都是二分求 $B_i$ 的插入位置，但实际上没必要，因为给 $B$ 数组排序后，找完 $B_1$ 的插入位置开始找 $B_2$ 的插入位置时可以保证 $B_2$ 的插入位置在 $B_1$ 的右边，所以直接一路往右找即可。这就是为什么楼上题解时间复杂度是 $O((n+m)log\ n)$ ，但我的是 $O(n+m)$ 。

$AC\ Code:$
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,A[200005],B[200005],s1[100005],s2[100005],point,ans,cnt1,cnt2;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&A[i]);
	}
	for(int i=1;i<=m;i++){
		scanf("%d",&B[i]);
	}
	sort(A+1,A+n+1);
	sort(B+1,B+m+1); //记得排序
	for(int i=1;i<=n;i+=2){
		cnt1++;
		s1[cnt1] = A[i+1] - A[i];
		s1[cnt1] += s1[cnt1-1];
	}
	for(int i=n;i>=3;i-=2){//这里倒着存是为了后面方便
		cnt2++;
		s2[cnt2] = A[i] - A[i-1];
		s2[cnt2] += s2[cnt2-1];
	}
	point = 1;
	ans = 1998244353;//注意这个要最大值设大一点不然会WA
	for(int i=1;i<=m;i++){//求出所有情况，找最小值
		if(B[i] >= A[n]){//当B中的当前元素已经大于A中最大的元素时，选后面的肯定不如选这个，所以选这个就行了，后面的不用再搜
			ans = min(ans,B[i]-A[n]+s1[n/2]);
			break;
		}
		while(A[point] < B[i])point++;
		if(point % 2 == 0){//分情况讨论
			ans = min(ans,B[i] - A[point-1] + s1[(point-2)/2] + s2[(n-point+1)/2]);//这个被加号分成三段的式子分别表示：新数字与A中元素组合结果，数组前半段组合结果，数组后半段组合结果
		}
		else{
			ans = min(ans,A[point]-B[i] + s1[point/2] + s2[(n-point)/2]);//同理，但公式略有不同
		}
	}
	printf("%d",ans);
	return 0;//完美收尾
}
```

---

## 作者：Iron_Spade (赞：0)

显然将数组 sort 之后两两挨着组队是最优的。

所以考虑将每个 $w_i$ 插入 $h$ 中。


插入的过程可以采用二分实现，具体地，我们找到第一个比其大的（也就是找出有多少个比它小的，记为 $id$），然后插入在这个数的前面。

求贡献的话比较显然，因为是两两差分，所以不能直接朴素做差分，考虑算出原数组奇数位前缀和和偶数位前缀和，然后考虑分类讨论。

- $id$ 是奇数：那么插入的数就是第偶数个。
- $id$ 是偶数：那么插入的数就是第奇数个。

前缀和求区间和即可。时间复杂度 $O(N\log N)$。


```cpp
#include <bits/stdc++.h>
#define FASTIO ios::sync_with_stdio(0), cin.tie(nullptr), cout.tie(nullptr)
#define rep(i, j, k) for (int i = j; i <= k; ++i)
#define pre(i, j, k) for (int i = j; i >= k; --i)
#define pb push_back
#define inf 0x3fffffff
#define PII pair<int, int>
#define fi first
#define se second
#define int long long

using namespace std;

const int N = 2e5 + 5;
const int mod = 1e9 + 7;

int n, m, k, res = mod, a[N], b[N], d[N];
int p[N][2];

signed main() {
    FASTIO;
    cin >> n >> m;
    rep(i, 1, n) cin >> a[i], ++mp[a[i]];
    rep(i, 1, m) cin >> b[i];
    sort(a + 1, a + 1 + n);
    rep(i, 1, n) {
        p[i][0] = p[i - 1][0];
        p[i][1] = p[i - 1][1];
        p[i][i & 1] += a[i];
    }
    //	rep(i, 1, n) cout << p[i][0] << ' ';
    //	cout << '\n';
    //	rep(i, 1, n) cout << p[i][1] << ' ';
    //	cout << '\n';

    rep(i, 1, m) {
        if (b[i] >= a[n]) {
            res = min(res, p[n][0] - p[n][1] + b[i]);
            continue;
        }
        int id = lower_bound(a + 1, a + 1 + n, b[i]) - a;
        //		cout << b[i] << ' ' << id << '\n';
        --id;
        //		cout << id << '\n';
        if (id % 2 == 0) {
            res = min(res, p[id][0] - p[id][1] + p[n][1] - p[id][1] - p[n][0] + p[id][0] - b[i]);
            //			cout << "!" << b[i] << '\n';
            //			cout << p[id][0] - p[id][1] << ' ' << p[n][1] - p[id][1] - p[n][0] + p[id][0] - b[i] <<
            //'\n';
        } else {
            res = min(res, p[id][0] - p[id][1] + b[i] + p[n][1] - p[id][1] - p[n][0] + p[id][0]);
        }
    }
    cout << res;

    return 0;
}
```

---

## 作者：Expert_Dream (赞：0)

比较简单的一道题。

最小化？必定是排完序后是最小化了。

对于答案，可以拆成三个部分的和。分别为：插入数前的所有贡献，插入数后的所有贡献，插入数所产生的贡献。

前面的贡献和后面的贡献可以用前缀和和后缀和来预处理。

然后枚举选哪些数，二分一下他应该插在哪？计算一下他与他前面或者是他与他后面的贡献。

然后输出所有情况中最小的即可。

---

## 作者：loser_seele (赞：0)

首先如果插入的人身高确定了，那么最优的方案显然是排序后按顺序两两分组。

证明：用邻项交换法，设四个数为 $ a,b,c,d $，满足 $ a\leq b \leq c \leq d $，比较 $ \mid a-b \mid + \mid c-d \mid $ 和 $ \mid a-c \mid + \mid b-d \mid $ 的大小，由大小关系不难得到前式等于 $ d-a+b-c $，后式等于 $ d-a+c-b $，因为 $ b \leq c $，所以排序后不会使得结果更差。

但是暴力将所有人插入后统计答案显然会超时，考虑优化：插入位置只会影响前缀和在插入位置前后的奇偶性，所以预处理出奇次项和偶次项的前缀和即可，找到插入位置可以直接二分查询。

所以总时间复杂度 $ \mathcal{O}((n+m)\log{n}) $，可以通过。

代码：

```cpp
#import <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=2e5+5,inf=1e18;
ll n,m,a[N],h[N],sum[N],ans=inf;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i) 
    scanf("%d",&a[i]);
	for(int i=1;i<=m;++i) 
    scanf("%d",&h[i]);
	sort(a+1,a+n+1);
	sort(h+1,h+m+1);
	sum[1]=a[1];
	sum[2]=a[2];
	for(int i=3;i<=n;++i) 
    sum[i]=sum[i-2]+a[i];
	for(int i=1;i<=n;++i)
    {
		ll res=0;
		if(i&1)
        {
			res+=sum[i-1]-sum[i-2];
			res+=sum[n]-sum[i]-sum[n-1]+sum[i-1];
		}
		else
        {
			res+=sum[i-2]-sum[i-3];
			res+=sum[n]-sum[i-3]-sum[n-1]+sum[i-1]+a[i-1];
		}
		ll pos=lower_bound(h+1,h+m+1,a[i])-h;
		if(pos>1) 
        ans=min(ans,res+abs(h[pos-1]-a[i]));
		if(pos<=m) 
        ans=min(ans,res+abs(h[pos]-a[i]));
		if(pos<m) 
        ans=min(ans,res+abs(h[pos+1]-a[i]));
	}
	printf("%lld",ans);
}
```


---

