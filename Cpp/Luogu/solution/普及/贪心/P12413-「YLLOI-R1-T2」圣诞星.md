# 「YLLOI-R1-T2」圣诞星

## 题目背景

![圣诞星](bilibili:BV14Q4y137d1)

## 题目描述

小 Y 在商店里一共要买 $n$ 个商品，第 $i$ 个要买的商品价格为 $a_i$ 元。

在买这些商品前，小 Y 可以买任意多张优惠券，对于每一张优惠券，其价格为 $w$ 元。每有一张优惠券，在买任何商品时可以优惠 $1$ 元，但任何一个商品最低只能优惠到 $0$ 元。（优惠券不算商品）

在付钱过程中，每付完一个商品的钱，小 Y 还能再获得一张优惠券。

现在小 Y 想知道，最少需要多少钱才可以买完自己要买的商品。

注：所有的优惠券都是永久性的。

## 说明/提示

#### 【样例解释#1】

下面展示一种最优方案。

先购买 $3$ 张优惠券，花费 $3\times 3=9$ 元。

接下来使用 $0$ 元购买第 $1$ 个要买的商品（$3$ 张优惠券优惠了 $3$ 元），并再获得一张优惠券。

接下来使用 $0$ 元购买第 $2$ 个要买的商品（$4$ 张优惠券优惠了 $4$ 元），并再获得一张优惠券。

接下来使用 $0$ 元购买第 $3$ 个要买的商品（$5$ 张优惠券优惠了 $5$ 元），并再获得一张优惠券。

接下来使用 $0$ 元购买第 $4$ 个要买的商品（$6$ 张优惠券优惠了 $5$ 元，因为任何一个商品最低只能优惠到 $0$ 元），并再获得一张优惠券。

因此一共花费 $9+0+0+0+0=9$ 元。

#### 【样例解释#2】

下面展示一种最优方案。

先购买 $1$ 张优惠券，花费 $1\times 3=3$ 元。

接下来使用 $2$ 元购买第 $4$ 个要买的商品（$1$ 张优惠券优惠了 $1$ 元），并再获得一张优惠券。

接下来使用 $1$ 元购买第 $3$ 个要买的商品（$2$ 张优惠券优惠了 $2$ 元），并再获得一张优惠券。

接下来使用 $1$ 元购买第 $2$ 个要买的商品（$3$ 张优惠券优惠了 $3$ 元），并再获得一张优惠券。

接下来使用 $0$ 元购买第 $1$ 个要买的商品（$4$ 张优惠券优惠了 $4$ 元），并再获得一张优惠券。

因此一共花费 $3+2+1+1+0=7$ 元。

#### 【数据范围】

**本题采用捆绑测试。**

- Subtask 1（10 pts）：$\forall a_i=i$。
- Subtask 2（10 pts）：$w=1$。
- Subtask 3（20 pts）：$n,a_i,w\le 10$。
- Subtask 4（30 pts）：$n,a_i,w\le 1000$。
- Subtask 5（30 pts）：无特殊限制。

对于全部数据，保证：$1\le n\le 10^5$，$1\le a_i,w\le 10^9$。

## 样例 #1

### 输入

```
4 3
3 4 5 5```

### 输出

```
9```

## 样例 #2

### 输入

```
4 3
4 4 3 3```

### 输出

```
7```

# 题解

## 作者：lovelish (赞：21)

因为不管买哪个商品都会让其他的价格减 $1$，但先买贵的容易让便宜的降为 $0$ 元，使其浪费优惠。因此按照价格从小到大购买一定最优。

现在我们已经确定了这些商品的购买顺序（之后的 `a[i]` 便是排序后的），那么对于商品购买的优惠券的优惠就已经确定，我们可以先把每个商品先计算出优惠后的价格。第 $i$ 个商品会被买前 $i-1$ 个商品的优惠券优惠，即 `a[i]=a[i]-i+1`。

接下来我们就只需要考虑一开始买多少张优惠券最优即可。只要一张优惠券能优惠的钱数大于 $w$，这张优惠券就是值的，那么当价格非 $0$ 的商品不超过 $w$ 时，再买优惠券就不会值了，此时停止购买。

如何求出购买多少张优惠券后价格非 $0$ 的商品会不超过 $w$ 个呢？这里有两种求法。

若购买 $x$ 张价格非 $0$ 的商品会超过 $w$ 个，则购买 $x-1$ 张价格非 $0$ 的商品也一定会超过 $w$ 个，可以发现这是有单调性的，因此我们可以直接二分优惠券数，求出价格非 $0$ 的商品超过 $w$ 个的最大优惠券数即可，总时间复杂度 $\mathcal O(n\log W)$，其中 $W$ 为 $a_i$ 的值域（因为当 $w=1$ 时一直买优惠券直到只剩一个价格非 $0$ 的商品是最优的）。

再看另一种求法，因为最后剩下的价格非 $0$ 的商品一定是价格最高的若干个，所以我们可以直接再次排序，求出价格第 $n-w+1$ 高的价格，那么购买这么多优惠券时每张优惠券一定都是值的，并且再多买一张就不是值的了，总时间复杂度 $\mathcal O(n\log n)$。

求出购买多少张优惠券后，模拟一遍统计答案即可。

---

## 作者：ZaleClover (赞：3)

# P12413 「YLLOI-R1-T2」圣诞星 题解

[更好的阅读体验？](https://www.cnblogs.com/ZaleClover/p/18894716)

## 思路
1. 首先，我们先考虑没有计算优惠券贡献的情况：此时最少钱数即为 $\sum\limits_{i=1}^na_i$ 。
2. 然后再考虑未购买优惠券的情况：\
   由题知每购买完一个商品便会获得一个优惠券，并且优惠券是永久性的，即购买完该商品后，后续购买的所有商品都会收到该优惠券的影响。由于 $a_i$ 较小的商品无法更多的利用优惠券，所以为了让优惠券发挥最大作用，我们需将 $a_i$ 较大的商品放在后面购买，因为优惠券只对 $a_i\ge1$ 的商品有贡献，那么我们可以对 $a_i$ 从小到大排序，并减去前面 $i-1$ 个优惠券的贡献。
3. 最后考虑如何购买优惠券：\
   这时应考虑优惠券如何对答案造成贡献，设 $f(x)$ 为商品 $a_i\ge x$ 的数量。\
   模拟一下不难发现它的贡献为每次购买时商品 $f(1)-w$，由于商品只有 $n$ 个，若 $w>n$，只要购买优惠券肯定就是不优的。\
   那我们只需要考虑 $w\le n$ 时的情况，易知在该情况下，若购买时 $f(1)\ge w$，则可购买优惠券。我们将此过程放到全局来看，若想购买 $k$ 张优惠券且有贡献，则需满足 $f(k)\ge w$。不难发现当 $f(k)\ge w$ 时，$f(k-1)\ge w$ 也必然满足，所以贡献值单调递增。所以当 $f(k)=w$ 时，为 $k$ 的上限。我们可对修改后 $a_i$ 再次排序，方便查找 $f(k)=w$ ，即 $k=a_{n-w}$ 的情况。
> 注意事项：千万不要忘了 $a_i$ 下限是 $0$。
## 代码
$\text{Code}$
```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 100010;

int n, w, num;
int a[N]; 
long long ans, sum;

template <typename type>
void read(type &res) {
	type x = 0, f = 1;
	char c = getchar();
	for (; c < 48 || c > 57; c = getchar()) if (c == '-') f = ~f + 1;
	for (; c > 47 && c < 58; c = getchar()) x = (x << 3) + (x << 1) + (c ^ 48);
	res = f * x;
}

int main() {
	read(n), read(w);
	for (int i = 1; i <= n; i++) read(a[i]); // 分析 2 中的第一次排序
	sort(a + 1, a + 1 + n); 
	for (int i = 2; i <= n; i++) a[i] = max(a[i] - (i - 1), 0), sum += a[i]; // 减去前 i - 1 个优惠券
	if (w > n) return printf("%lld", sum + a[1]), 0; // 不贪小便宜，原价更好
	sort(a + 1, a + 1 + n); // 第二次排序以方便查找 f(k) = w 的情况
    ans += 1ll * a[n - w] * w; // 加上优惠券的价格
    for (int i = 1; i <= n; i++) ans += max(0, a[i] - a[n - w]); // 减去优惠券的优惠
    printf("%lld", ans);
	return 0;
}
```

---

## 作者：seika27 (赞：2)

### 思路
我们手上的优惠卷分为两部分，一部分是一开始买的，一部分是后来送的。

由于后来送的不用花钱我们考虑先排除这一部分的影响，对于第 $i$ 个商品，其价格为 $a_i$ 根据题意得知，我们现在手上会有 $i-1$ 个送的优惠卷，那其实去掉送的优惠卷之后的价格就变成 $a_i-i+1$，我们令其为 $b_i$。

现在我们来看看咋样买最节省。

现在你买了一张优惠卷，其价格为 $w$。对于每一个商品这张优惠卷每次可以便宜一块钱。

那么只要我们的这张优惠卷给 $w$ 个商品省了一块钱，我们就不亏了。更多就赚了，更少就亏了。

我们现在把 $b$ 给从小到大排序。现在有可能出现价格为 $0$ 的商品。对于这些商品，我们的优惠卷是没用的。

根据我们刚刚所说的，只要我们买了一张优惠卷，就至少需要 $w$ 个可优惠的商品，那如果此时我们所省的商品数量小于 $w$ 那还不如直接买不要优惠卷。

反过来，如果此时我们还有 $w$ 个及以上个的商品可以使用优惠卷那我们就应该使用，现在的问题变成了应该使用几张优惠卷。

为了保证每一张优惠券都不浪费，我们应取 $b_{n-w+1}$ 的值作为张数。这样的话就能保证我们上述的要求。

### code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,w;
const int N=1e5+5;
int a[N];
int ans;
int cnt;
signed main()
{
	ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr);
	cin>>n>>w;
	for(int i=1;i<=n;++i)cin>>a[i];
	sort(a+1,a+1+n);
	for(int i=1;i<=n;++i)a[i]=max(a[i]-i+1,0ll);
    sort(a+1,a+1+n);
	cnt=a[max(n-w+1,0ll)];
	for(int i=1;i<=n;++i)ans+=max(0ll,a[i]-cnt);
	cout<<ans+w*cnt;
	return 0;
}
```

---

## 作者：XsIeEiKcEk (赞：2)

先排序，模拟最开始买的券数，进行计算，取出最小值。

然而你会发现会超时，所以我们要用**二分**。

还有一个重点，如果买 $i$ 券要的钱比 $i+1$ 张券时还要便宜，说明后面只会更贵，可以直接跳出，节省时间。

### 计算开始买 $q$ 张券 CODE：
```cpp
int money(int q){
    int _plus=q,plus=0;//_plus为券减的钱，plus为有券后买物品要的钱
    for(int i=0;i<n;i++){
         if(_plus<a[i])plus+=a[i]-_plus;//若商品价格大于券减的钱，需加上减后的钱
        _plus++;//每卖一件物品券增加
    }
    return plus+q*w;//要加上买券的钱
}
```
### 二分 CODE：
```cpp
int l=0,r=1e9;//注意r要为1e9，即商品价格的最大值
while(l<r){
    int mid=(l+r)/2,_ans=money(mid),nans;
    ans=min(ans,_ans);//取小值
    if(mid==n)nans=1e18;//越界特判
    else nans=money(mid+1);
    if(_ans>nans)l=mid+1;
    else r=mid;//若后面的还要小就判断前面的
}
```

---

## 作者：__CJY__ (赞：2)

## 思路
~~我为何要用三分？用二分应该也行吧……~~

假设在购买任何商品之前，小 Y 已经购买了 $k$ 张优惠券，那么，在购买第 $1$ 个商品时，可以使用 $k$ 张优惠券，将价格从 $a_1$ 减少到 $\max(a_1-k,0)$。购买第 $1$ 个商品后，会获得 $1$ 张新的优惠券，因此在购买第 $2$ 个商品时，有 $k+1$ 张优惠券可用。依此类推，购买第 $i$ 个商品时，可用的优惠券数量为 $k+(i-1)$ 张，价格为 $\max(a_i-(k+i-1),0)$。

初始购买 $k$ 张优惠券的成本为 $k \times w$，购买所有商品的总成本为 $\sum\limits_{i=1}^n\max(a_i-(k+i-1),0)$。因此，定义总成本函数为 $\operatorname{C}(k)$，则 $\operatorname{C}(k)=k \times w+\sum\limits_{i=1}^n\max(a_i-(k+i-1),0)$。

我们需要找到一个整数 $k(k \ge 0)$，使得 $\operatorname{C}(k)$ 最小。

我们先分析一下 $\operatorname{C}(k)$ 的性质。

对于固定的 $i$，$\max(a_i-(k+i-1),0)$ 随着 $k$ 的增加是非递增的（因为 $k$ 增加时，$a_i-(k+i-1)$ 减小）。因此，$\sum\limits_{i=1}^n\max(a_i-(k+i-1),0)$ 也是非递增的。而 $k \times w$ 是严格递增的。我们设 $t$ 为非递增部分，则 $\operatorname{C}(k)=k \times w+t$ 是一个先递减后递增的函数（类似单谷函数），存在一个最小值。

由于 $\operatorname{C}(k)$ 是单谷函数，所以可以使用三分法来找到最小值点。因为三分法适用于在有序区间内寻找极值，通过比较两个中间点的函数值来缩小搜索范围。
## Code
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=1e5+5;
ll n,w,a[maxn];
//计算购买 k 张优惠券时的总成本
ll C(ll k){
	ll s=k*w,t=k;//s 表示初始购买 k 张优惠券的成本，t 表示当前可用的优惠券数量
	for(ll i=1;i<=n;i++) s+=max(0ll,a[i]-t),t++;//计算购买第 i 个商品的价格，购买后获得一张新的优惠券
	return s;
}
int main(){
	cin>>n>>w;
	for(ll i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1);
	ll l=1,r=*max_element(a+1,a+n+1),ans=C(l);
	while(l<=r){
		ll mid1=l+(r-l)/3,mid2=r-(r-l)/3;
		ll s1=C(mid1),s2=C(mid2);
		if(s1<s2) r=mid2-1,ans=min(ans,s1);
		else l=mid1+1,ans=min(ans,s2);
	}
	//局部搜索，确保找到最小值
	for(ll i=max(0ll,l-5);i<=l;i++) ans=min(ans,C(i));
	cout<<ans;
}
```
**十年 OI 一场空，不开`long long`见祖宗！**

---

## 作者：Zskioaert1106 (赞：2)

题目传送门：[P12413 「YLLOI-R1-T2」圣诞星](https://www.luogu.com.cn/problem/P12413)

~~你家优惠券可以无限次用~~

### 题目分析

因为优惠券不会被消耗，所以只会越来越多，因此先买便宜的东西肯定是最优的。因此在接下来的分析中，默认 $a$ 数组是升序排序的。

之后我们要找出最划算的优惠券数，那就要先减去因为付款而得到的优惠券。具体地，如果只算这类优惠券的话，买 $a_i$ 时可以减免 $i-1$ 元。

此时答案已经呼之欲出了。只要一张优惠券能在大于等于 $w$ 件商品上起效果，那买优惠券就是不亏的。所以我们找到减免 $i-1$ 元后的 $a$ 数组第 $w$ **小**的值即是我们可以买的优惠券数。由于 $w$ 可能大于 $n$，此时买优惠券就是（不聪明的）行为，所以要判断。

求出优惠券数后，将减免自动券后的 $a$ 数组再减去买的优惠券数，再加上买优惠券的钱即为答案。

### 代码实现

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
const int N=100005;
int n,s,a[N];
long long w,ans;
int main(){
	cin>>n>>w;
	for(int i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+1+n);
	for(int i=1;i<=n;i++)a[i]-=min(a[i],i-1);
	sort(a+1,a+1+n);
	if(w>n)s=0;
	else s=n-w+1;
	for(int i=1;i<=n;i++)
		if(a[i]>a[s])ans+=a[i]-a[s];
	cout<<ans+a[s]*w;
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/216011298)。

---

## 作者：ylzpl (赞：2)

这题恶心。难度建议：黄。  
考查算法：二分，贪心。

-------------------------------------------
题目描述如下：
-  **预售购券**：结算前可购买任意数量现金券，每张券花费 $w$ 元。
-  **即时抵扣**：每持有 $1$ 张券，结算时可对**单件商品**抵扣 $1$ 元。    
-  **买一赠一**：每完成一件商品的支付，立即获赠 $1$ 张新券。  

请计算购齐所有商品的最小总花费（包含购买现金券的费用）。

---------------------------------------

思路:  
我们可以根据样例来画一张图：
![https://cdn.luogu.com.cn/upload/image_hosting/fb37opc1.png](https://cdn.luogu.com.cn/upload/image_hosting/fb37opc1.png)
不难发现，我们的花费并非满足单调性，而优惠券满足单调性。那么我们使用二分来求解呢？我们可以发现，费用是一个 `U` 字形，那么我们可以找出一个线段（用蓝色标出）：
![https://cdn.luogu.com.cn/upload/image_hosting/k2d3nydj.png](https://cdn.luogu.com.cn/upload/image_hosting/k2d3nydj.png)
这一段的花费一定满足 $b_{i-1}=b_i$，那么我们可以找到这一段。我们定义 $f$ 为买 $i$ 张票的花费，$h$ 为买 $i+1$ 张优惠券的花费。那么如果 $f<h$ 就是右端点，否则就暂时成为左端点。此时，我们二分的就是优惠券的张数。最后，我们再输出一开始买 $rt$ 张优惠券的花费即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e6+5;
int a[maxn],n,w;
int check(int x){
	int ans=x*w;
	int y=x;
	for(int i=1;i<=n;i++){
		ans+=max(a[i]-y,0ll);
		y++;
	}
	return ans;
}
signed main(){
	cin>>n>>w;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+1+n);
	int lt=-1,rt=1e9;
	while(lt+1<rt){
		int mid=(lt+rt)/2;
		if(check(mid)<check(mid+1)){
			rt=mid;
		}
		else{
			lt=mid;
		}
	}
	cout<<check(rt);
	return 0;
}
```
说句实在的，这题用三分会好些很多。感兴趣的同学可以肝一下。

---

## 作者：Na1L0n9 (赞：2)

# Solution
## 思路
读完题后，因为如果先购买价格高的商品，那么价格低的商品就可能被优惠至 $0$ 元，这样优惠券产生的贡献就小了，所以，我们可以按商品价格从小到大排序，这样我们就会得到最优的购买顺序。此时我们会发现，在购买第 $i$ 件商品时，一定已经购买了前 $i-1$ 件商品，那么第 $i$ 件商品的真实价格，即不额外花钱购买优惠券的为 $\max(a_i-i+1,0)$ 元。

经过上文操作后，我们获得优惠券的方式只有花 $w$ 元购买了。所以现在我们只需要计算出需要买几张优惠券，这道题我们就解决了。


当 $w>n$ 时，因为一张优惠券最多也只会给总价值减少 $n$ 元，购买优惠券一定劣于不购买优惠券，所以最优策略是不购买优惠券。

否则，我们买优惠券就有可能会是更优的方案，我们要思考的问题是，什么时候买优惠券是更优的。一个商品的价格如果已经是 $0$ 元了，那么优惠券对它就没有作用了。所以优惠券造成的贡献就是用 $n$ 减去当前 $0$ 元商品的个数，只要这个值大于 $w$，买优惠券就会更优。很明显，真实价格越低的商品肯定越早变为 $0$ 元。考虑将商品的真实价格从小到大排序，求出商品中第 $n-w$ 高的真实价格，就是应该买的优惠券次数，因为此时 $0$ 元商品的个数为正好就是 $n-w$，而 $w=n-(n-w)$，只要再多买一张优惠券，就是不划算的。

最后统计总和即可，就这样我们就解决了这道题。
## Code
```c++
#include <bits/stdc++.h>
#define Write ios::sync_with_stdio(0);
#define by cin.tie(0);
#define AquaDaMean1e cout.tie(0);
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 1e5 + 10;
const int MOD = 998244353;
ll n, ans, w, a[N], cnt, tot;
int main() {
	Write by AquaDaMean1e
	cin >> n >> w;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; i++) {
		a[i] = max(0ll, a[i] - (i - 1));
	}
	sort(a + 1, a + n + 1);
	if (w < n) {
		cnt = a[n - w];
	}
	else {
		cnt = 0ll;
	}
	//cout << cnt << " ";
	for (int i = 1; i <= n; i++) {
		ans += max(0ll, a[i] - cnt);
	}
	cout << ans + w * cnt;
	return 0;
}
```

---

## 作者：iChen (赞：1)

瞅（qio）一眼算法标签：  
二分什么成分？？？

**不用二分的猎奇做法（纯贪心）**

## Part 1 贪心分析

#### 优先买什么商品？

对于买的第 $i$ 个商品，假设我们不买任何优惠券，那么我们手上也会有 $i - 1$ 张优惠券，所以我们在不考虑商品降价最低降到 $0$ 的情况下，总共能获得：

$减价=\displaystyle\sum^{n}_{i=1}(i-1)=0 + 1 + 2 + \dots + (n - 1) = \dfrac{(n - 1)\times n}{2}$

但这仅是不考虑降价限制的结果。如果第 $i$ 个商品的价格小于 $i - 1$，那么就会造成减价的浪费。所以我们需要尽可能避免这种情况。

又考虑到后买的商品降价更多，为了让后买的商品有更大的价格去吃掉分配给它的降价，所以应该把价格大的商品放在后面，减小浪费。

#### 什么时候买优惠券？

对于任意一张优惠券，它在被购买后只能对它后面买的商品起作用。我们肯定希望它能为更多的商品降价，所以这优惠券不买则已，要买就在最开始买，让它给所有商品都降价。

#### 买多少张优惠券？

当我们买了一张优惠券，显然可以对当前实际价格（减价后的价格）不为 $0$ 的商品减去 $1$ 元的开支，假设这种商品有 $k$ 个，那么就会有 $k$ 元的减价。但是我们买一张优惠券需要 $w$ 元，所以只要此时 $k > w$，那么再购买优惠券是更优的。  
所以找到第 $n - w + 1$ 个商品的价格，即为需购买的优惠券数量。

## Part 2 思路总结

分析完上述内容后，思路也就比较明了了：  
1. 将所有商品按从小到大的顺序排序。
2. 把第 $i$ 个商品减去 $i - 1$ 的价格，排掉赠送的优惠券的影响。
3. 再进行排序，寻找第 $n - w + 1$ 个商品的价格，这就是我们需要买的优惠券数量。
4. 模拟计算最终花销。

## Part 3 Code

```cpp
#include <iostream>
#include <algorithm>
#define int long long

using namespace std;

const int N = 1e5 + 5;
int n, w, a[N];

signed main () {
	cin >> n >> w;
	for (int i = 1; i <= n; i ++) cin >> a[i];
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; i ++) a[i] = max(a[i] - i + 1, 0ll);
	int k = max(n - w + 1, 0ll);
	int need = a[k];
	int ans = need * w;
	for (int i = 1; i <= n; i ++) ans += max(0ll, a[i] - need);
	cout << ans;
	return 0;
}
```

**不开 `long long` 见祖宗！**

---

## 作者：Objective (赞：1)

## 思路与算法

前一段时间，我们学校教练带我们连了小数据量的餐巾计划问题。所以比赛的时候我便想到了如下的思路：

这道题我们**反过来**看：既然我们要找最少的总钱数，那我们不妨通过**枚举**的方式，一个一个枚举，找到最少花费。我这里最开始将枚举的最大值设为了所有商品中最贵的商品的价格（还能凹）。

好的，开开心心打代码。打完一交，诶？怎么只有 50 分？噢～原来是 TLE 了（[Record](https://www.luogu.com.cn/record/215913684)）。

于是我快乐地加上了一些条件（剪枝）：
```cpp
if (cost >= min_cost) {
    break;
}
```
然后又快乐地交了上去，果不其然，又是 TLE（[Record](https://www.luogu.com.cn/record/215916384)）。但是，60 分的结果告诉我优化是可行的。只不过，我们需要找到一些高效的优化策略。  
这里我把计算的部分模块化地放出来（方便调试、修改）：
```cpp
long long compute_cost(int x, int w, const vector<int>& a) {
    long long cost = x * 1LL * w;
    int coupons = x;
    for (int i = 0; i < a.size(); ++i) {
        int discount = min(a[i], coupons);
        cost += max(a[i] - discount, 0);
        coupons += 1;
        if (cost >= (1LL << 60)) {
            break; 
        }
    }
    return cost;
}
```
然后，再使用三分法，逐步缩小搜索范围：
```cpp
while (left <= right) {
    int mid1 = left + (right - left) / 3;
    int mid2 = right - (right - left) / 3;
    long long cost1 = compute_cost(mid1, w, a);
    long long cost2 = compute_cost(mid2, w, a);
    if (cost1 < cost2) {
        right = mid2 - 1;
        min_cost = min(min_cost, cost1);
    } else {
        left = mid1 + 1;
        min_cost = min(min_cost, cost2);
    }
}
```
最后，在局部进行小的优化，找出最优解（避免三分遗漏）：
```cpp
for (int x = max(left - 5, 0); x <= min(right + 5, max_a + n); ++x) {
    long long cost = compute_cost(x, w, a);
    if (cost < min_cost) {
        min_cost = cost;
    }
}
```
最终，我们把代码从 $O(maxcost \times n)$ 优化到了 $O(n \times \log maxcost)$（$maxcost$ 指最贵的商品价格）。

# 代码
## C++
```cpp
#include <bits/stdc++.h>
using namespace std;

// 计算购买 x 张优惠券后，买完所有商品的总花费
// 参数 x: 初始购买的优惠券数量
// 参数 w: 每张优惠券的价格
// 参数 a: 商品价格数组
long long compute_cost(int x, int w, const vector<int>& a) {
    long long cost = x * 1LL * w; // 优惠券总花费
    int coupons = x; // 拥有优惠券数量
    for (int i = 0; i < a.size(); ++i) {
        int discount = min(a[i], coupons); // 当前商品的最大优惠
        cost += max(a[i] - discount, 0); // 计算商品实际花费
        coupons += 1; // 获得一张优惠券
        if (cost >= (1LL << 60)) { // 剪枝
            break; 
        }
    }
    return cost; // 返回总花费
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // 输入 n: 商品数量, w: 每张优惠券的价格
    int n, w;
    cin >> n >> w;
    // 输入商品价格数组
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    // 将商品价格排序，优先处理价格较低的商品
    sort(a.begin(), a.end());
    int max_a = a.back(); // 商品的最高价格
    long long min_cost = 1LL << 60; // 初始化最小花费为2^60（反正挺大）
    // 使用三分法搜索最优的初始优惠券数量
    int left = 0;
    int right = max_a + n; // 理论上优惠券数量的最大值
    while (left <= right) {
        int mid1 = left + (right - left) / 3; // 三分点 1
        int mid2 = right - (right - left) / 3; // 三分点 2
        long long cost1 = compute_cost(mid1, w, a); // 计算三分点 1 的总花费
        long long cost2 = compute_cost(mid2, w, a); // 计算三分点 2 的总花费
        if (cost1 < cost2) { // 如果三分点 1 的花费更低
            right = mid2 - 1; // 缩小右边界
            min_cost = min(min_cost, cost1); // 更新最小花费
        } else { // 如果三分点 2 的花费更低
            left = mid1 + 1; // 缩小左边界
            min_cost = min(min_cost, cost2); // 更新最小花费
        }
    }
    // 三分法
    for (int x = max(left - 5, 0); x <= min(right + 5, max_a + n); x++) {
        long long cost = compute_cost(x, w, a); // 计算总花费
        if (cost < min_cost) { // 更新最小花费
            min_cost = cost;
        }
    }
    cout << min_cost << '\n';
    return 0;
}
```

## Java
```java
import java.util.*;

public class Main {
    // 计算购买 x 张优惠券后，买完所有商品的总花费
    // 参数 x: 初始购买的优惠券数量
    // 参数 w: 每张优惠券的价格
    // 参数 a: 商品价格数组
    static long computeCost(int x, int w, List<Integer> a) {
        long cost = (long) x * w; // 优惠券总花费
        int coupons = x; // 拥有优惠券数量
        for (int price : a) {
            int discount = Math.min(price, coupons); // 当前商品的最大优惠
            cost += Math.max(price - discount, 0); // 计算商品实际花费
            coupons += 1; // 获得一张优惠券
            if (cost >= (1L << 60)) { // 剪枝
                break;
            }
        }
        return cost; // 返回总花费
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        // 输入 n: 商品数量, w: 每张优惠券的价格
        int n = scanner.nextInt();
        int w = scanner.nextInt();
        // 输入商品价格数组
        List<Integer> a = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            a.add(scanner.nextInt());
        }
        // 将商品价格排序，优先处理价格较低的商品
        Collections.sort(a);
        int maxA = a.get(a.size() - 1); // 商品的最高价格
        long minCost = 1L << 60; // 初始化最小花费为2^60（反正挺大）
        // 使用三分法搜索最优的初始优惠券数量
        int left = 0;
        int right = maxA + n; // 理论上优惠券数量的最大值
        while (left <= right) {
            int mid1 = left + (right - left) / 3; // 三分点 1
            int mid2 = right - (right - left) / 3; // 三分点 2
            long cost1 = computeCost(mid1, w, a); // 计算三分点 1 的总花费
            long cost2 = computeCost(mid2, w, a); // 计算三分点 2 的总花费
            if (cost1 < cost2) { // 如果三分点 1 的花费更低
                right = mid2 - 1; // 缩小右边界
                minCost = Math.min(minCost, cost1); // 更新最小花费
            } else { // 如果三分点 2 的花费更低
                left = mid1 + 1; // 缩小左边界
                minCost = Math.min(minCost, cost2); // 更新最小花费
            }
        }
        // 三分法
        for (int x = Math.max(left - 5, 0); x <= Math.min(right + 5, maxA + n); x++) {
            long cost = computeCost(x, w, a); // 计算总花费
            if (cost < minCost) { // 更新最小花费
                minCost = cost;
            }
        }
        System.out.println(minCost);
    }
}
```

---

## 作者：zhanghy123 (赞：1)

## 思路
首先一个显然的性质：按商品初始价格从小到大购买，可以使赠送的优惠券贡献尽可能大，也就是使答案更优。因此开始时先将商品价格升序排序。

观察题目，易知随着优惠券数量的增加，最终花费呈现先降后升的 ``v`` 字形趋势。三分答案即可。

因此，经过稍稍的思考和转化，这道题已经变成了一道三分答案的板子题。
## 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e5+5;
ll n,k,m[N],ans=1e15,low,p;
ll check(ll t){//t张券 
	ll sum=0;
	for(int i=1; i<=n; i++)
		sum+=max(0ll,m[i]-t);
	return sum+k*t;
}
int main()
{
	
	cin>>n>>k;
	for(int i=1; i<=n; i++)
		cin>>m[i];
	sort(m+1,m+n+1);
	for(int i=1; i<=n;i++){
		m[i]=max(0ll,m[i]-i+1);
	}
	ll l=0,r=1e9,m1,m2;
	while(r-l>2)//三分答案
	{
		m1=l+(r-l)/3;
		m2=r-(r-l)/3;
		if(check(m1)>check(m2))
			l=m1;
		else
			r=m2;
	}
	cout<<min(min(check(m1),check(m2)),min(check(l),check(r)));//保险起见挑一个最小的
	return 0;
}

```

---

## 作者：pengzhining (赞：0)

[题目](https://www.luogu.com.cn/problem/P12413)。

## 题意理解
有 $n$ 个物品，标价为 $a_i$，实际会优惠 $i-1$ 元，有优惠券可以付出 $w$ 的代价使所有商品实际价格减一，但所有商品的实际价格 $a_i \geq 0$，求最少花费。

## 思路
看完题目之后，我们可以很快想到：由于优惠券会递增，我们要尽量让优惠券发挥出更多的作用，所以我们首先应该让价格低的商品在前面（因为 $a_i$ 将会减去 $i-1$ 元，所以我们要将大的 $i$ 减到大的 $a_i$ 上）。考虑使用贪心解决此题。

## 做法
我们先将商品排序，计算不用优惠券所需的钱，并计算不用优惠券时每个商品的实际价格，再算出优惠券的个数，求出每增加一个优惠券对花费的贡献，当贡献比花费少时，我们就可以得到优惠券的个数，再将其带回原来的顺序并求出最少的花费。

这里有个假做法，就是计数并求优惠券的贡献以及花费（反正就是会遍历 $a_i$ 或只是微处理了一下），思路本身没有问题，但是 $a_i \leq 1\times 10^9$ 会 MLE 或 TLE（TLE 的情况就是遍历了 $1$ 到 $a_i$ 导致时间被彻底卡爆，但我还没遇到 TLE 就已经 MLE 了）。

## 注意
1. 这道题有人处理实际花费时没有注意到 $a_i \geq 0$，也就是没有特判负数，这样会 WA 在最后 4 个点上。
2. 这道题有的数据中 $w>n$，这个时候肯定不要用优惠券了，花费比贡献大。

# code
码风有点丑请见谅，时间复杂度大概是 $O(n\log n)$（雾），可以通过此题。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n,m;
long long w[N],ne[N];
long long res; //表示优惠券的最多数量
long long num; //表示优惠券的价格(可以不要，但是后来会用来特判 n<w 的情况)
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>w[i];
    }
    sort(w+1,w+n+1); //这里是为了求最小实际代价
    for(int i=1;i<=n;i++){
        if(w[i]>i-1){
            ne[i]=w[i]-i+1;
        }else{
            ne[i]=0;
        }
    }
    sort(ne+1,ne+n+1); //这里是为求优惠券个数作准备
    for(int i=n;i>=1;i--){
        if(num>=m){ //使优惠券的影响最大
            break;
        }
        num++;
        res=ne[i]; //得出优惠券的个数，这里不用担心n<m;
    }
    long long ans=0;
    for(int i=1;i<=n;i++){
        if(w[i]>res+i-1){
            ans+=w[i]-res-i+1;//用优惠券后的实际代价
        }
    }
    ans+=res*num; //这里不要乘m因为n可能小于w。n>m时这里是加上优惠券的代价,n<m时这里是补差价
    cout<<ans;
}
/*
in
5 100
1 1 1 1 1
out
1
*/
```
[AC](https://www.luogu.com.cn/record/215974726)

如果 $n < w$ 的话，这个代码与直接算最小实际花费和（也就是不买券）是等价的。

---

## 作者：lllyyykkk (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/P12413)

很明显的贪心题。

首先，看到优惠券可以重复使用，先对价格排序，让价格高的获得更大的优惠，这样可以解决掉买个物品送一张优惠券的烦人条件。

接下来，问题转化成一开始可以买优惠券，将所有物品的价格都下调一，问最小的代价。  
考虑每多买一张优惠券，都会有相应个数的减少，且效果是单调不增的（当一个物品不要钱了你优惠券再多也没用），所以价格曲线应该是一个凸函数。  
对于这个凸函数，你可以暴力三分，但仔细思考一下，当可以优惠的个数比优惠券的价值小时，再购买优惠券就没有必要了。

代码注意一下负数与边界的特判。
### Code
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e5+10;
int n,w;
int a[N];
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>w;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++) a[i]=max(0,a[i]-i+1);
	sort(a+1,a+n+1);
	if(w>n){
		ll sum=0;
		for(int i=1;i<=n;i++) sum+=a[i];
		cout <<sum<<'\n';
		return 0;
	}
	ll sum=1ll*w*a[n-w+1];
	for(int i=n-w+2;i<=n;i++) sum+=a[i]-a[n-w+1];
	cout <<sum;
	return 0;
}
``````

---

