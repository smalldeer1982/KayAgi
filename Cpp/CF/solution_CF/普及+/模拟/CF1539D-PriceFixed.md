# PriceFixed

## 题目描述

Lena is the most economical girl in Moscow. So, when her dad asks her to buy some food for a trip to the country, she goes to the best store — "PriceFixed". Here are some rules of that store:

- The store has an infinite number of items of every product.
- All products have the same price: $ 2 $ rubles per item.
- For every product $ i $ there is a discount for experienced buyers: if you buy $ b_i $ items of products (of any type, not necessarily type $ i $ ), then for all future purchases of the $ i $ -th product there is a $ 50\% $ discount (so you can buy an item of the $ i $ -th product for $ 1 $ ruble!).

Lena needs to buy $ n $ products: she must purchase at least $ a_i $ items of the $ i $ -th product. Help Lena to calculate the minimum amount of money she needs to spend if she optimally chooses the order of purchasing. Note that if she wants, she can buy more items of some product than needed.

## 说明/提示

In the first example, Lena can purchase the products in the following way:

1. one item of product $ 3 $ for $ 2 $ rubles,
2. one item of product $ 1 $ for $ 2 $ rubles,
3. one item of product $ 1 $ for $ 2 $ rubles,
4. one item of product $ 2 $ for $ 1 $ ruble (she can use the discount because $ 3 $ items are already purchased),
5. one item of product $ 1 $ for $ 1 $ ruble (she can use the discount because $ 4 $ items are already purchased).

In total, she spends $ 8 $ rubles. It can be proved that it is impossible to spend less.

In the second example Lena can purchase the products in the following way:

1. one item of product $ 1 $ for $ 2 $ rubles,
2. two items of product $ 2 $ for $ 2 $ rubles for each,
3. one item of product $ 5 $ for $ 2 $ rubles,
4. one item of product $ 3 $ for $ 1 $ ruble,
5. two items of product $ 4 $ for $ 1 $ ruble for each,
6. one item of product $ 1 $ for $ 1 $ ruble.

In total, she spends $ 12 $ rubles.

## 样例 #1

### 输入

```
3
3 4
1 3
1 5```

### 输出

```
8```

## 样例 #2

### 输入

```
5
2 7
2 8
1 2
2 4
1 8```

### 输出

```
12```

# 题解

## 作者：Acc_Robin (赞：7)

题外话：做完这题，感觉自己不会买东西了

#### 题意：

市场上有 $n$ 种商品，每种商品的价格都是 $2$。现在你需要买第 $i$ 种商品 $a_i$ 件。但是对于第 $i$ 种商品有一个属性 $b_i$，意味着如果你已经买了 $b_i$ 件商品（不一定是这一种商品），那么此商品打折，价格会降到 $1$。

你需要最小化你的代价。

其中 $1\le n \le 1\times 10^5,1\le a_i,b_i\le 1\times 10^{14}$。

#### 题解：

数据范围太大，考虑贪心：

我们把每种商品按 $b_i$ 升序排序，现在面临两种局面：

1. 有一种商品可以 $1$ 元买下

此情况下，直接买完这种商品。

注意，如果满足此情况，那么 $b_i$ 最小的商品必然可以 $1$ 元买下。

2. 没有商品可以 $1$ 元买下

此情况下，我们购买 $b_i$ 最大的商品，直到**这种商品买够 $a_i$ 个**或者发现**有新的商品开始打折**。

这个贪心为什么是对的？

第一种情况下，购买这种商品显然不会使答案更劣。

问题出在第二种情况：为何要购买 $b_i$ 最大的商品？

因为如果购买 $b_i$ 小的商品，会发现我们一直买，买完这件商品，后面的商品都未必打折。而购买 $b_i$ 较大的商品很有可能引起前面的物品打折。

#### 复杂度

排序为瓶颈，复杂度 $O(n\log n)$。

#### 代码实现

对 $b_i$ 排序之后，我们可以维护一个**碰撞指针**，从两侧向中间逼近。左、右指针的处理分别对应上述的$1/2$两种情况。

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace Acc{
	const int N = 1e5+10;
#define int long long
	struct node{int a,b;}a[N];
	int z,n;
	void work(){
		cin>>n;
		for(int x,y,i=1;i<=n;i++)cin>>x>>y,a[i]={x,y};
		sort(a+1,a+n+1,[](node x,node y){return x.b<y.b;});
		for(int l=1,r=n,s=0,x;l<=r;)
            if(a[l].b<=s)s+=a[l].a,z+=a[l].a,l++;
			else{
				s+=(x=min(a[r].a,a[l].b-s)),z+=x*2,a[r].a-=x;
				if(!a[r].a)r--;
			}
		cout<<z<<'\n';
	}
#undef int
}
int main(){
	return Acc::work(),0;
}
```

---

## 作者：StayAlone (赞：5)

这道题目还是有一定思考难度的，虽然代码很短，但不一定很好理解。

### 题意

有 $n$ 个商品$(1\leqslant n \leqslant 100000)$，每个需要 $2$ 元，给定 $a_i,b_i(1\leqslant i\leqslant n)$，表示第 $i$ 个商品需要买 $a_i$ 个，而当你**总共**买到 $b_i$ 个商品时，每个商品 $i$ 会降价至 $1$ 元。  

请你输出购买完所有所需商品后，至少需要花多少元。

### 思路

这道题是一道贪心题，贪心策略如下：  

先将数组以 $b$ 为第一关键字排序，这时我们不难想到，先买 $b$ 大的，因为这些商品很可能打不了折，直到满足某些 $b$ 小的商品可以打折。这样买完，可以保证需要花的钱最少。  

在实现时我们使用**双指针**，由于我是从大到小排序，故 $l$ 表示用原价购买的，$r$ 表示打折购买的，我们需要用原价购买 $l$ 使得 $r$ 尽可能地打折购买。  

为了方便解释，我直接将所有代码放上来，大佬可能一读就懂了。。。我呢还是逐字逐句地解释一下(当时我做的时候想到脑子爆炸)

```cpp
#include <bits/stdc++.h>
#define ll long long
#define fr(i, l, r) for (int i = l; i <= r; ++i)
using namespace std;
int n; ll prsum;
struct node
{
	ll a, b;
}vn[100010];

bool cmp(const node &x, const node &y)
{
	return x.b > y.b;
}

int main()
{
	scanf("%d", &n);
	ll nd = 0, t = 0;
	fr(i, 1, n) scanf("%lld%lld", &vn[i].a, &vn[i].b), nd += vn[i].a;
	sort(vn + 1, vn + 1 + n, cmp);
	int l = 1, r = n;
	while (t^nd)
	{
		if (t >= vn[r].b) t += vn[r].a, prsum += vn[r].a, r--;
		else if (t + vn[l].a >= vn[r].b) vn[l].a -= vn[r].b - t, prsum += (vn[r].b - t) * 2, t = vn[r].b;
		else t += vn[l].a, prsum += vn[l].a * 2, l++;
	}
	printf("%lld", prsum);
	return 0;
}
```  

用 $t$ 表示当前买的商品的数量，$nd$ 表示需要的总数量，$prsum$ 是当前花了多少钱，所以 $\texttt{while}$ 条件是 $t \ne nd$ 时循环。这里不能写 $l < r$ 或者写 $l \ne r$，因为 $l$ 和 $r$ 可能重合，如样例 $2$。  

第一种情况：

```cpp
if (t >= vn[r].b)
    t += vn[r].a, prsum += vn[r].a, r--;
```
如果已经购买的比 $r$ 所需即可打折的数量大或相等，则将所有 $r$ 需要的以 $1$ 元价格购买，并 $r - 1$，因为 $r$ 商品已经购买完毕。这时 $t$ 也要更新，因为**又购买了 $a_r$ 样商品。**  

第二种情况：
```cpp
else if (t + vn[l].a >= vn[r].b)
    vn[l].a -= vn[r].b - t, prsum += (vn[r].b - t) * 2, t = vn[r].b;
```
如果把 $l$ 所需要的买完或一部分就足够使得 $r$ 商品打折，商品 $l$ 所需要的会减少 $b_r - t$ 个，即要再原购买 $l$ 商品 $b_r - t$ 个，而 $prsum$ 就要加上这个数量乘 $2$。  

到这里，我要插一句，牢记~~党的嘱托~~ $l$ 和 $r$ 的意义，这样才好弄明白，这里我说得简洁一些，忘记的可以再翻到前面看看：

- $l$ 是通过原价购买尽量满足 $r$ 打折购买的商品！  

第三种情况：
```cpp
else
    t += vn[l].a, prsum += vn[l].a * 2, l++;
```  
如果把 $l$ 买完都不够让 $r$ 打折，也就只好买完，$t$ 要加上 $l$ 商品的所有剩余所需，$prsum$ 也跟着变化，且 $l + 1$。  

到这里，终于逐字逐句地讲完了整个过程，可能需要多看几遍才能真正理解。  

[AC code记录](https://www.luogu.com.cn/record/52052297)

完整代码已在前面给出。

---

## 作者：nalemy (赞：2)

分析题目不难发现，每一**件**商品对于我们来说是**平等的**。不同的只是商品的降价时间。所以，为了最小化代价，我们需要让**更多的商品降价**。

我们的目标已经很明确了，接下来就是怎么做的问题。

我们分两种情况分析：

1. 如果当前**有已经有降价的商品**，显然此时直**接把它买完**是最优选择。

   因为这个商品你迟早要买它，直接把它买完还可以给**后面商品降价的机会**

2. 如果当前**没有降价的商品**，那么买谁呢？

   我们需要买的**商品总量**，也就是 $\sum a_i$ 是固定的，所以 $b_i$ **越小**，这个商品降价的**越早**。

   所以，在两件商品都没有降价的时候，我们显然更喜欢 $b_i$ **小**的那一个，因为在某一时刻它**更有可能降价**。

   所以我们要怼着 $b_i$ **大**的那一个买，让 $b_i$ 小的那一个**留着等降价**。要记住，我们的目标是让**降价的商品更多**。

总结一下：

1. 如果有**已降价**的商品，我们**直接把它买完**；
2. 如果没有，我们就不停地买 $b_i$ 最大的那个商品，直到回到情况 1。

接下来我们想想怎么实现。我们看看我们的需求：

1. 尽量快地获取 $b_i$ **最小**的商品；
2. 尽量快地获取 $b_i$ **最大**的商品；
3. 尽量快地更新**某个商品**的个数。

很明显，我们可以维护两个**碰撞指针**。从我们的策略可知，我们买东西只可能从两端买。因此我们用两个指针标记没有买过的商品的左右两个端点。买完某种商品后将两个指针向中间靠拢。

时间复杂度分析：快速排序是瓶颈，复杂度为 $O(n\log n)$

代码如下：

```C++
#include<iostream>
#include<algorithm>
#define N 100000
#define a second
#define b first
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;

pii o[N];
int main() {
    ll n, ans = 0; cin >> n;
    for (int i=0; i<n; i++) cin >> o[i].a >> o[i].b; sort(o, o+n);
    for (ll l=0, r=n-1, cnt=0, t; l<=r; o[r].a ? 0 : r--)
        if (o[l].b > cnt)
            cnt += t=min(o[l].b-cnt, o[r].a), ans += 2*t, o[r].a -= t;
        else cnt += t=o[l++].a, ans += t;
    return cout << ans, 0;
}
```



---

## 作者：MikukuOvO (赞：1)

首先考虑最简单的贪心，按照 $b_i$ 从大到小的顺序进行购买，但我们发现 $sample~2$ 很好的举出了反例，在此情境下，我们通过先买已经可以半价的 $b_i$ 较小商品从而使得 $b_i$ 较大的商品可以半价。

不难得出：先购买 $b_i$ 较大的商品，但若目前可以购买半价的商品，就先进行购买半价商品，可以通过 $two~pointers$ 进行实现。

关于正确性的证明：贪心的正确性不难理解，先购买已经打折的商品一定不会使答案更劣，并且 $b_i$ 越大的物品能打折的可能性越小，但问题在于原题提到的购买多余物品的必要性。这样就有了一种通过半价购买多余物品从而使得原本不能打折的物品进行打折的做法，但我们发现如果将这些半价多余物品的花费转移到本应购买的物品上，加上之后半价购买这些物品的花费和直接原价购买这些物品的花费是等价的，故正确性得证。

```cpp
#include<bits/stdc++.h>

using namespace std;

#define ll long long

const int N=1e5+5;

int n;
pair<ll,ll>s[N];

bool cmp(pair<ll,ll> x,pair<ll,ll> y)
{
    return x.second>y.second;
}
int main()
{
    cin>>n;
    for(int i=1;i<=n;++i) cin>>s[i].first>>s[i].second;
    sort(s+1,s+n+1,cmp);
    int l=1,r=n;
    ll res=0,ans=0;
    while(l<=r)
    {
        if(s[l].first+res<=s[r].second) res+=s[l].first,ans+=s[l].first*2,++l;
        else
        {
            ll num=s[r].second-res;
            res=s[r].second,ans+=num*2;
            s[l].first-=num;
        }
        while(l<=r&&s[r].second<=res)  res+=s[r].first,ans+=s[r].first,--r;
    }
    cout<<ans<<endl;
}
```

---

## 作者：IGA_Indigo (赞：0)

## 题目大意
给定 $n$ 种商品，每种商品你需要买 $a_i$ 个，这种商品买够 $b_i$ 个可以打折变成一块，否则按原价两块。问怎么样买完所有这些商品所需的钱数最少。
## 大体思路
我们首先想到贪心，先排序，需要购买数最多才能打折的商品我们需要先买，因为他们是最有可能打不了折的，一旦遇到可以打折的商品，我们就疯狂购买，因为这已经是最低价了，还能购买个数，何乐而不为。

这样的话我们可以维护头指针和尾指针存储打折所需要购买数最多和打折所需要购买数最少的商品的下标，每次判断即可。

代码也是十分好写，通俗易懂，全篇注释。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	long long a,b;
}w[100005];
bool cmp(node aa,node bb){
	return aa.b>bb.b;
}//贪心的排序 
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>w[i].a>>w[i].b;
	}
	sort(w+1,w+1+n,cmp);
	long long sum=0,ans=0;
	int l=1,r=n;
	while(r>=l){//尾指针一定不比头指针小 
		long long g=w[r].b;
		if(w[l].a+sum<=g){//分类讨论，如果加上这一件的数量之后还不能打折拿下当前需要最少已购买商品数目才能打折的商品的话 
			sum+=w[l].a;//全款拿下所有这种商品 
			ans+=(w[l].a*2);
			w[l].a=0;
			l++;
		}
		else{//如果能大于 
			long long m2=g-sum;//我们只需要全款买一直到可以打折买下需要最少购买数打折的商品 
			w[l].a-=m2;
			sum+=m2;
			ans+=(m2*2);
		}
		while(r>=l&&w[r].b<=sum){//最后判断，如果可以打折买一种 
			ans+=w[r].a;//就一直买所需要购买数量最少的商品一直到不行 
			sum+=w[r].a;
			w[r].a=0;
			r--;
		}
	}
	cout<<ans;//输出答案 
    return 0;
}
```

---

## 作者：Vii_Truly (赞：0)

考虑贪心，想要总话费最少，那么自然是购买时价格为 $1$ 的商品占的数量多。

如果说当前买的商品数量还不够，每一样商品都要花费 $2$ 才能够得，那这个时候，是买 $b_i$ 大的商品还是买 $b_i$ 小的商品呢？

显然买 $b_i$ 大的更好，因为 $b_i$ 大说明想要用价格为 $1$ 这种商品之前需要买的商品就更多，也就是折扣门槛高。

这样这道题的做法就有了：先把所有商品按 $b_i$ 进行排序，如果现在已经有能打折的商品，就把能以折扣价购买的商品全部买光；没有可以以折扣价购买的商品，就去买 $b_i$ 大的，直到能有以折扣价购买的商品，细节参见代码：

```cpp
#include <bits/stdc++.h>

using namespace std;
int n;
pair<long long, long long>p[100100];

int main() {
//    freopen("in", "r", stdin);
    scanf("%d", &n);
    for (int i = 0;i < n; i++) scanf("%lld %lld", &p[i].second, &p[i].first);
    sort(p, p + n); //按b_i从小到大排序
    long long l = 0, r = n - 1, sum = 0, ans = 0; //sum是已经购买的商品数量
    while (l <= r) {
        while (sum < p[l].first && l <= r) { //不能以折扣价购买
            if (sum + p[r].second <= p[l].first) { //把当前b_i最大的买完，也不能有折扣
                sum += p[r].second; // 那就买完
                ans += p[r--].second * 2;
            } else { //买一部分就能有折扣
                p[r].second -= p[l].first - sum; //把这部分买了，就有折扣了
                ans += (p[l].first - sum) * 2; 
                sum = p[l].first;
            }
        }
        while (sum >= p[l].first && l <= r) { //将能以折扣价买的都买了
            sum += p[l].second;
            ans += p[l].second;
            l++;
        }
    }
    printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：Frevotops (赞：0)

很长时间以前打的一场比赛，当时 D 没想出来。今天，终于一波操作之后，过了这题！

眼看数据范围较大，这还只是 Div.2 D，应该是贪心。我左思又想，找到了一种思路：如果当前买的物品数量可以让买某种物品时打五折，那就把那种物品赶快买掉。反正过一会儿也是 $1$ 块钱，现在买还能让当前买的物品数量变多。

但是，开局买啥？我想来想去，觉得可以按照 $b_i$ 降序排序，买 $b_i$ 大的。因为 $b_i$ 最大的物品，它想要打折要求很高，其它的能打到折的希望比它大，那就先疯狂买它。记录一个右端点 $rht$，这个右端点初始是 $n+1$,并不断向左移。如果发现当前买的数量够让第 $rht-1$ 个物品优惠了，那赶紧买它，买光光，然后 $rht$ 向左移一格。由于我们排过序了，就可以设这个右端点了。右端点（含）之后的物品都被我们以 $1$ 元的价格买了下来。

如果我们发现，第一个物品买够了，怎么办？不要浪费地还买第一个，那就去买第二个，相当于也设立一个左端点不停向右移。当我们发现左右端点重合，意味着买完了。

如果我们发现，当前物品要买的数量太多了，太多了，太多了，以至于它后面的所有物品都能优惠了，连它自己都可以优惠了，那么我们需要特判一下。

代码实现呢，细节还是很多。贪心都这样。

当时为啥没想出来 /kk。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n;
struct Node{
    ll a,b;
}node[100005];
bool cmp(Node A,Node B){
    return A.b>B.b;
}
int main(){
    cin>>n;
    for(ll i=1;i<=n;i++) cin>>node[i].a>>node[i].b;
    sort(node+1,node+n+1,cmp);
    ll rht=n+1, now=0, fei=0;
    for(ll lft=1;lft<=n;lft++){
        if(lft>=rht) break;
        ll res=node[lft].a;
        while(rht>i && res>=max(node[rht-1].b-now,0ll)){
            ll consts=max(node[rht-1].b-now,0ll); // 花掉这个差价，当前买的物品数量就能到 node[rht-1].b 了。也可能已经到了。
            res-=consts; // 买这些，花 2 元。
            now+=consts;
            fei+=consts*2;
            rht--; // 右端点左移。
            // 现在可以以 1 元的价格买第 rht 个物品。
            if(rht!=lft) now+=node[rht].a,fei+=node[rht].a;
            else{
                now+=res, fei+=res;
                res=0;
            }
        }
        fei+=2*res;
        now+=res;
        // 把剩下要买的一买，走人。只能花 2 元了。
    }
    cout<<fei<<endl;
}
```


---

## 作者：fls233666 (赞：0)

想要最小化总代价，只有一个办法：**尽可能让较多的商品降价为 $1$** 。显然，我们需要决定一个合理的商品购买顺序，以让更多的商品降价。

由于商品是否能降价为 $1$ 取决于商品的自身属性 $b$，我们处理买商品的顺序时肯定要按 $b$ 的大小来处理。于是我们考虑先买 $b$ 的值大的商品还是先买 $b$ 小的商品方案更优。

如果先买 $b$ 值小的商品来满足 $b$ 值大的商品的降价条件，我们就需要花 $2$ 的代价买很多的商品才能使一小部分的商品降价。由于大部分的商品购买代价都是 $2$，这样购买商品显然不优。反过来，如果我们先买 $b$ 值大的商品来满足 $b$ 值小的商品降价条件，则我们不用买很多商品就可以产生降价，显然更优。

于是我们要做的第一件事，就是**把所有商品按 $b$ 的大小排序**。下面我们来考虑排序后如何处理买商品的这个过程。

按照我们在上文得出的结论，我们先买 $b$ 值大的商品，当有 $b$ 值小的商品降价时，为了让更多商品降价，我们应该**停下来去买降价的商品**。因为买降价的商品，同样也能让我们已经买的商品总数量增多，而花的代价更少。这样才能让更多的商品的 $b$ 值被满足，达到降价的目的。

把上述过程转换到代码实现中，我们可以使用**双指针**。将指针 $l$ 指在排序后商品的第一个【 $b$ 值最小的商品】，指针 $r$ 指在排序后商品的最后一个【 $b$ 值最大的商品】，记我们已经买的商品总数为 $cnt$。考虑以下情况：

- 当 $cnt < b_l$ 时，此时商品数量不足以降价。考虑购买指针 $r$ 指向的商品来降价。进一步分类讨论：
	- 当 $cnt+a_r < b_l$ 时，此时把指针 $r$ 指向是商品全买下都不能降价。这时就把指针 $r$ 指向的商品全买掉，并移动指针 $r$。
    - 当 $cnt+a_r \ge b_l$ 时，此时不用把指针 $r$ 指向是商品全买下就能降价。这时把指针 $r$ 指向的商品买下一部分，不移动指针 $r$。
- 当 $cnt \ge b_l$，此时商品数量可以降价，直接把指针 $l$ 指向的商品全买下，并移动指针 $l$。

于是我们就在 $O(n)$ 的时间里模拟了整个买商品的过程。算上排序的时间复杂度，总时间复杂度为 $O(n \log(n))$，可以通过此题。

下面放上代码：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define ll long long
#define rgt register int
using namespace std;

const int mxn = 1e5+5;

int n;
struct items{
	ll ai;
	ll bi;
}m[mxn];
ll ans,cnt;

inline bool cmp(struct items m1,struct items m2){
	return m1.bi<m2.bi;
}

int main(){
	scanf("%d",&n);
	for(rgt i=1;i<=n;i++)
		scanf("%lld%lld",&m[i].ai,&m[i].bi);
	sort(m+1,m+1+n,cmp);  //读入，按 bi 排序
    
	int l=1,r=n;
	while(l<=r){  //双指针统计答案
		if(cnt<m[l].bi){
			if(cnt+m[r].ai<m[l].bi){
				cnt+=m[r].ai;
				ans+=m[r].ai*2;
				r--;  //需要把商品 r 全买下
			}else{
				ans+=(m[l].bi-cnt)*2;
				m[r].ai-=m[l].bi-cnt;
				cnt=m[l].bi;
			}  //把商品 r 买一部分
		}else{
			ans+=m[l].ai;
			cnt+=m[l].ai;
			l++;
		}  //把商品 l 全买下
	}
    
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：hfee (赞：0)

不知道为什么所有题解都要双指针取 $b_i$ 最大的...

实际上根本没有任何影响，反正总可以从某些不优的 $b_i$ 来填补目前的缺口，所以直接按 $b_i$ 排序后一个个模拟取即可

```
#include<bits/stdc++.h>
#define N 100005
#define int long long
using namespace std;
int n, s, p, ans;
struct D{
	int a, b;
}x[N];
bool cmp(D r, D t){
	return r.b < t.b;
}
signed main(){
	cin >> n;
	for(int i = 1; i <= n; ++i){
		cin >> x[i].a >> x[i].b;
		s += x[i].a;
	}
	sort(x + 1, x + 1 + n, cmp);
	for(int i = 1; i <= n; ++i){
		if(p < x[i].b){
			ans += (min(x[i].b, s) - p) * 2;
			p = min(x[i].b, s);
		}
		ans += min(x[i].a, s - p);
		p += min(x[i].a, s - p);
		if(p == s) break;
	}
	cout << ans;
	return 0;
}

```


---

## 作者：Booksnow (赞：0)

# PriceFixed

## 题目大意

市场上又 $n$ 种商品，每种商品的价格都是 $2$ 。对于第 $i$ 种商品 $a_i$ 件。对于商品 $i$ 给出一个值 $b_i$ ，如果你已经购买了 $b_i$ 种商品（购买所有商品的综合），那么你购买这种商品，价格为 $1$ 。

求最小代价。

## 分析

**出题人特意标注：每种商品不一定只能购买 $a_i$ 件。**

在引导我们往哪个地方想？——我们可以通过刷已经打折的商品来达到让没有打折的商品打折。

**这其实是个坑……**

仔细想想，你白花了 $1$ 点代价，即使打折了，你再买，也根本不会变优。其实无非也就两种情况，你花费一个 $1$ ，赚到了一个购买量，如果到了 $b_i$ ，你买，相当于你还是花了 $2$ ，如果没到，反而你还花了 $3$ ，将这个例子带到整个里面来看，把一个商品看成“一段”商品，是一样的，这种买法**不可能更优**。

那接下来我们怎么买呢？

**贪心！**

将每种商品按照 $b_i$ 排序，$b_i$ 越大我们越优先买，因为他最不可能打折，接下来按照以下程序：

- 如果当前 $b_i$ 最大的商品我们还没有买够，就买，同时注意目前没有买完的商品中 $b_i$ 最小的数量。

- 一旦购买量达到任意一个商品的 $b_i$ ，马上将这种商品买完。

不难证明这种方法一定是最优的。

## CODE

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') { if(ch=='-') w*=-1; ch=getchar(); }
	while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
	return s*w;
}
struct node{
	int a,b;
}p[N];
int n,ans;
inline bool cmp(node x,node y) { return x.b>y.b; }
signed main()
{
	n=read();
	for(register int i=1;i<=n;i++) p[i].a=read(),p[i].b=read();
	sort(p+1,p+n+1,cmp);
	int l=1,r=n,sum=0;
	while(l<=r){
		if(sum<p[r].b){
			bool AA=false,BB=false;
			int temp1=sum;
			ans+=2*min(p[l].a,p[r].b-sum); //算价格
			if(p[l].a<=p[r].b-sum) BB=true;
			else AA=true;
			sum+=min(p[l].a,p[r].b-sum);
			if(BB) l++;
			if(AA) p[l].a-=(p[r].b-temp1);
		}
		else { ans+=p[r].a,sum+=p[r].a; r--; }
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

