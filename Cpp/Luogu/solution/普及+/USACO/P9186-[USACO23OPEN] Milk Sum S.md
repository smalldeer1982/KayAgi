# [USACO23OPEN] Milk Sum S

## 题目描述

**注意：本题的时间限制为 4 秒，是默认时间限制的 2 倍。**

Farmer John 的 $N$ 头奶牛的产奶量为整数 $a_1, \dots, a_N$。也就是说，第 $i$ 头奶牛每分钟产 $a_i$ 单位的牛奶。

每天早上，Farmer John 会将所有 $N$ 头奶牛连接到谷仓的挤奶机上。他需要依次断开连接，将奶牛送去进行日常锻炼。第一头奶牛在挤奶 1 分钟后被断开连接，第二头奶牛在再挤奶 1 分钟后被断开连接，依此类推。由于第一头奶牛（假设是奶牛 $x$）只在挤奶机上停留了 1 分钟，她总共贡献了 $a_x$ 单位的牛奶。第二头奶牛（假设是奶牛 $y$）在挤奶机上停留了总共 2 分钟，因此贡献了 $2a_y$ 单位的牛奶。第三头奶牛（假设是奶牛 $z$）贡献了 $3a_z$ 单位的牛奶，依此类推。设 $T$ 表示 Farmer John 以最优顺序断开奶牛连接时，可以收集到的最大总牛奶量。

Farmer John 很好奇，如果某些奶牛的产奶量发生变化，$T$ 会如何变化。对于每个由两个整数 $i$ 和 $j$ 指定的 $Q$ 个查询，请计算如果将 $a_i$ 设置为 $j$，新的 $T$ 值会是多少。注意，每个查询都是独立的临时变化，即在考虑下一个查询之前，$a_i$ 会恢复为原始值。

## 说明/提示

对于第一个查询，$a$ 将变为 $[1,1,4,2,6]$，此时 $T = 1 \cdot 1 + 2 \cdot 1 + 3 \cdot 2 + 4 \cdot 4 + 5 \cdot 6 = 55$。

对于第二个查询，$a$ 将变为 $[1,8,4,2,6]$，此时 $T = 1 \cdot 1 + 2 \cdot 2 + 3 \cdot 4 + 4 \cdot 6 + 5 \cdot 8 = 81$。

对于第三个查询，$a$ 将变为 $[1,10,4,5,6]$，此时 $T = 1 \cdot 1 + 2 \cdot 4 + 3 \cdot 5 + 4 \cdot 6 + 5 \cdot 10 = 98$。

$1 \leq N \leq 1.5 \cdot 10^5$，$0 \leq a_i \leq 10^8$，$1 \leq Q \leq 1.5 \cdot 10^5$，$0 \leq j \leq 10^8$。

- 输入 2-4：$N, Q \leq 1000$。
- 输入 5-11：没有额外限制。

## 样例 #1

### 输入

```
5
1 10 4 2 6
3
2 1
2 8
4 5
```

### 输出

```
55
81
98
```

# 题解

## 作者：DreamLand_zcb (赞：12)

# 超详细的图解题解！！

~~你肯定看得明白的，对吧~~

## 简要题意

给定数组 $a_1,...,a_N$ 在数组中依次选出一个元素构成排列 $b_1,...,b_N$ 。定义 $T = \sum _{i=1} ^N i \times b_i $ 。现在给出 $Q$ 个操作，每个操作有两个数 $x$ 和 $y$ 表示将 $a_x$ 替换成 $y$ ，对于每一个操作求出操作后的 $T$ 的最大值，每次操作后数组还原成原样。

## 思路

不难发现， $T$ 的最大值是将 $a$ 排序后得到的 $\sum _{i=1} ^N i \times b_i$ ，因此，我们可以先将 $a$ 的元素赋给 $b$ ，然后 `sort(b)` ，记 $P_{a_i}$ 表示 $a$ 数组排序 $a_i$ 后所在位置下标，并算出不进行操作时的最大值，用变量 $sum$ 储存。

接下来考虑操作时的 $T$ 变化情况。以样例一的第三次操作举例：
![](https://huatu.98youxi.com/markdown/work/uploads/upload_aa8ca29e0e502d93679a9842c9d1afb2.png)

![](https://huatu.98youxi.com/markdown/work/uploads/upload_857c8350b963af34f66caaa7a03e70ab.png)

先用二分找到新插入的 $y$ 在数组 $b$ 中应该在的位置，记 `pos=upper_bound(b, y)` 。**注意一定要用 `upper_bound` 而不是 `lower_bound` 不然找到的下标不一致！！（也就是无论 $b$ 中之前有没有 $y$ 这个元素，我们都要找到从左往右第一个严格大于 $y$ 的元素下标）**

![](https://huatu.98youxi.com/markdown/work/uploads/upload_d75f0df191e3cb508d4485d68351aade.png)

操作后：

![](https://huatu.98youxi.com/markdown/work/uploads/upload_85e338e9d6f4e5b2ace13e5219352578.png)

可以发现，此时的 $T$ 比原来减少了 $a_x \times  P_{a_x}$ 也正是被替换掉的元素 $a_x$ 乘 $a_x$ 在 $b$ 中的下标。

此时再把 $P_{a_x}$ 以后的元素向左移动一个下标（不包括 $P_{a_x}$ ），也就是将 $T$ 减去 $P_{a_x}$ 以后的数的和，这里用前缀和数组 $s$ 优化后 $T$ 就比原来小了 $s_n - s_{P_{a_x}}$ ：

![](https://huatu.98youxi.com/markdown/work/uploads/upload_cbc5b868802673eb01701026d7e3033d.png)



那么如何计算把新加入的元素 $y$ 插入 $pos$ 后 $T$ 的变化呢？很简单，首先把 $y$ 插入后的 $T$ 的值求出来， $T$ 比原来大了 $y \times pos$ █ **但是一定要注意，如果 $pos$ 在 $P_{a_x}$ 右边（不包含 $P_{a_x}$ ） $T$ 就要变大 $y \times (pos-1)$ ，因为 $P_{a_x}$ 被删掉后， $pos$ 一定也会向左平移一个下标！！！**

然后将 $pos$ 以后（包括 $pos$ ）的所有数向右平移一个下标， $T$ 就比原来大了 $s_n - s_{pos-1}$ **这里也要注意，如果 $pos$ 在 $P_{a_x}$ 左边，（包括 $P_{a_x}$ ） $T$ 就要减小 $b_{P_{a_x}}$ 因为当 `pos <= p[a[x]]` 时将 $T$ 增加 $s_n - s_{pos-1}$ 会把曾经已经删除的 $b_{P_{a_x}}$ 加回来，然而它已经被删除了，就要减回去。**


![](https://huatu.98youxi.com/markdown/work/uploads/upload_639e7b86347969931c603c24992de9ef.png)


~~如果你没看懂上面的就来看这个吧~~

形式化的，对于该样例：

$$ T = 1 \times b_1 + 2 \times b_2 + 3 \times b_3 + 4 \times b_4 + 5 \times b_5 $$

先删除 $a_4$ ，也就是删除 $b_{P_{a_4}} = b_2$：

$$ T = 1 \times b_1 + 3 \times b_3 + 4 \times b_4 + 5 \times b_5 $$

可以发现 $T$ 减少了 $2 \times b_2$ 也就是 $2 \times b_{P_{a_x}}$ 及 `T-=2*b[P[a[x]]];`

然后将 $P_{a_{x}}$ 后的所有数的系数减一（相当于向左平移一个下标），得到：

$$ T = 1 \times b_1 + 2 \times b_3 + 3 \times b_4 + 4 \times b_5 $$

利用前缀和优化，发现 $T$ 减少了 $s_n - s_{P_{a_x}}$

用 `upper_bound` 找到 $pos = 4$ 然后计算出插入 $y$ 之后 $T$ 的变化：

$$ T =  1 \times b_1 + 2 \times b_3 + 3 \times b_4 + pos \times y + 4 \times b_5$$

$$ =1 \times b_1 + 2 \times b_3 + 3 \times b_4 + 4 \times y + 4 \times b_5 $$

$T$ 比原来大了 $pos \times y$ ，**注意这里要进行判断，具体判断方法参照黑色方框处（█）。**

最后将 $pos$ 右面的所有系数加一（相当于向右平移一个下标），得到：

$$ T = 1 \times b_1 + 2 \times b_3 + 3 \times b_4 + 4 \times y + 5 \times b_5 $$

$T$ 比原来大了 $s_n - s_{pos-1}$ ，**这里同样要注意特判，参照上方黑色方框处。**

最后得到的结果就是：

```cpp
T-=a[x]*P[a[x]];
T-=s[n]-s[P[a[x]]];
T+=y*(pos-(pos > P[a[x]]));
T+=s[n]-s[pos-1];
if(pos <= P[a[x]])	ans-=b[P[a[x]]];
```

## 代码（代码中的 $ans$ 就是 $T$ ）
忽略掉前面的快排，最终时间复杂度 $\Theta(Q \log n)$


```cpp
#include <bits/stdc++.h>
#define ll long long
#define setp setprecision
#define mem(a, m) memset(a, m, sizeof(a));
using namespace std;

ll n; 
ll Q;
ll a[150005];
ll b[150005];
ll s[150005];
ll sum=0;
map<ll, ll> P;//排序后a[i]的位置，记得要开map，因为a[x]最大可以达到1e8
int main()
{
	ios::sync_with_stdio(false);
	cin >> n;
	for(ll i=1;i<=n;i++)	cin >> a[i], b[i]=a[i];
	sort(b+1, b+n+1);
	for(ll i=1;i<=n;i++)	sum+=b[i]*i, s[i]=b[i]+s[i-1], P[b[i]]=i;
	cin >> Q;
	while(Q--)
	{
		ll x, y;
		cin >> x >> y;
		ll pos=upper_bound(b+1, b+n+1, y)-b;//用upper_bound找pos
		ll ans=sum;
		ans-=a[x]*P[a[x]];//减去被删掉的元素
		ans-=s[n]-s[P[a[x]]];//P[a[x]]右边的所有元素向左移一个下标
		ans+=y*(pos-(pos > P[a[x]]));//加上插入的元素y，记得要判断pos减不减一
		ans+=s[n]-s[pos-1];//pos右边的所有元素向右移一个下标
		if(pos <= P[a[x]])	ans-=b[P[a[x]]];//判断向右移动时有没有算上P[a[x]]，算上了就减去
		cout << ans << endl;
	}
	return 0;
}
```

# 十年 OI 一场空，不开 long long 见祖宗！！

别问我为什么知道的

[代码极速版](https://www.luogu.com.cn/paste/az3cvkxe)

---

## 作者：Nuyoah_awa (赞：7)

### 题目分析
#### 思路一：
暴力，每回排序，改数，计算。

时间复杂度 $\mathcal O(n ^ 2 \times \log n)$。

#### 思路二：

我们可以将改数操作分为两种：
1. 将一个数 $a_k$ 改大。

观察每次改数：原始根据数值排序后数组为 $a_1, a_2, a_3, a_4, a_5$。答案可以表示为：

$$ans1 = a_1 \times 1 + a_2 \times 2 + a_3 \times 3 + a_4 \times 4 + a_5 \times 5$$

如果将数 $a_5$ 更改，使得改完后数值为第 $2$ 小，更改后数组应为 $a_1, a_5, a_2, a_3, a_4$，答案表示为：

$$ans2 = a_1 \times 1 + a_5 \times 2 + a_2 \times 3 + a_3 \times 4 + a_4 \times 5$$

不难看出：$ans2 = ans1 + (a_2 + a_3 + a_4) - a_5 \times 5 + a_5 \times 2$。

于是我们可以先求出 $ans1$，再求出要更改的数 $a_k$ 原来第 $u$ 小，后来第 $v$ 小，通项公式为：

$$ ans2 = ans1 + \sum ^{i \le v} _{i = u}a_i - a_k \times (u - v)$$

2. 将一个数 $a_k$ 改小。

原始数组：$a_1, a_2, a_3, a_4, a_5$。

$$ans1 = a_1 \times 1 + a_2 \times 2 + a_3 \times 3 + a_4 \times 4 + a_5 \times 5$$

将 $a_2$ 改为第 $5$ 小的后，数组为：$a_1, a_3, a_4, a_5, a_2$。

$$ans2 = a_1 \times 1 + a_3 \times 2 + a_4 \times 3 + a_5 \times 4 + a_2 \times 5$$

同样先求出 $ans1$，原来第 $u$ 小，现在第 $v$ 小，通项公式为：

$$ans2 = ans1 - \sum ^{i \le v} _ {i = u} a_i + a_k \times (v - u)$$

于是，我们可以先 $O(n)$ 预处理出 $ans1$ 和原来每个数对应第几小，再对于每次询问以预处理出 $u$，二分求出 $v$，在利用通项公式计算，时间复杂度为 $\mathcal O(n \log n)$。

> PS：记得开 long long。
>
> 小心二分别写挂（尤其是第二种情况）

### code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e5 + 5;
struct node{
	int val, id;
}a[N];
int n, s[N], pos[N];
bool cmp(node x, node y)
{
	return x.val < y.val;
}
signed main(){
	ios::sync_with_stdio(false);

	cin >> n;
	for (int i = 1; i <= n; i ++)
		cin >> a[i].val, a[i].id = i;
	sort(a + 1, a + n + 1, cmp);
	for (int i = 1; i <= n; i ++)
		s[i] = s[i - 1] + a[i].val,
		pos[a[i].id] = i;
	int ans = 0;
	for (int i = 1; i <= n; i ++)
		ans += a[i].val * i;
	int T; cin >> T;
	while (T --)
	{
		int opt, x;
		cin >> opt >> x;
		opt = pos[opt];
		if (x == a[opt].val)
			cout << ans << "\n";
		if (x < a[opt].val)
		{
			//改小了，往opt以左（1 ~ opt - 1）二分找 <= x的第一个数 
			if (a[opt - 1].val < x) //x > a[opt - 1].val时，位置不变
			{
				int value = ans - (a[opt].val - x) * opt;
				cout << value << "\n";
				continue;
			}
			int l = 1, r = opt - 1;
			while (l < r)
			{
				int mid = (l + r) / 2;
				if (a[mid].val >= x) //大于等于了，就从这里开始往左 
					r = mid;
				else //小于了，就从下一个开始往右 
					l = mid + 1; 
			} 
			//a[l]为所求，让l ~ opt - 1的所有牛都晚一分钟 
			//即：加上l ~ opt - 1的区间和 
			//注意！！！要减去原有的a[opt] * opt，加上改的x * l
			int value = ans + (s[opt - 1] - s[l - 1]);
			value = value - a[opt].val * opt + x * l;
			cout << value << "\n";
		}
		if (x > a[opt].val)
		{
			//改大了，往opt以右（opt + 1 ~ n）二分找 < x 的最后一个数 
			if (x < a[opt + 1].val) //x < a[opt + 1].val时，位置不变 
			{
				int value = ans + (x - a[opt].val) * opt;
				cout << value << "\n";
				continue;
			}
			int l = opt + 1, r = n;
			while (l < r) 
			{
				int mid = (l + r + 1) / 2;
				if (a[mid].val < x) //小了，就从这里开始往右  
					l = mid;
				else //大于等于了，就从前一个开始往左 
					r = mid - 1; 
			} 
			//a[l]为所求，让opt + 1 ~ l的所有牛都早一分钟 
			//即：减去opt + 1 ~ l的区间和 
			//注意！！！要减去原有的a[opt] * opt，加上改的x * l
			int value = ans - (s[l] - s[opt + 1 - 1]);
			value = value - a[opt].val * opt + x * l;
			cout << value << "\n";
		}
	} 

	return 0;
}


```
### 附带一组较强数据
```
input:
20
110 120 130 199 200 200 200 201 201 201 210 220 230 240 250 260 270 280 290 300
5
1 1
20 1
1 900
2 200
3 201
output:
50804
48926
64601
51144
51131
```


---

## 作者：_Above_the_clouds_ (赞：5)

# 思路：
二分查找 $a_x$ 在 排序好的 $a$ 数组里的位置，再查找 $y$ 的位置，$s$ 为前缀和，$sum$ 记录原数组 $T$ 的最大值，然后分类讨论。

- 当 $a_x$ 大于等于 $y$ 时，$sum$ 减去 $a_x$ 在数组中的值，再加上 $y$ 的值，最后加上 $a_x$ 和 $y$ 之间的前缀和。

- 当 $a_x$ 小于 $y$ 时，和之前的情况基本一样，只是去掉 $a_x$ 时，数组整体会往前移一位，所以 $y$ 所在的位置减一，最后加上 $y$ 和 $a_x$ 间的前缀和。

# 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,q,x,y,l,r,p;
long long sum;
long long a[150005],tmp[150005],s[150005];
int main(){
	//freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],tmp[i]=a[i];
	cin>>q;
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++) sum+=a[i]*i,s[i]=s[i-1]+a[i];
	while(q--){
		cin>>x>>y;
		l=1,r=n;
		while(l<=r){
			int mid=(l+r)/2;
			if(a[mid]>tmp[x]) r=mid-1;
			else l=mid+1;
		}
		p=l-1;
		l=1,r=n;
		while(l<=r){
			int mid=(l+r)/2;
			if(a[mid]>y) r=mid-1;
			else l=mid+1;
		}
		if(p>=l) cout<<sum-tmp[x]*p+l*y+s[p-1]-s[l-1]<<"\n";
		else cout<<sum-tmp[x]*p+(l-1)*y-s[l-1]+s[p]<<"\n";
	}
	return 0;
}
```


---

## 作者：Nwayy (赞：2)

简要题意：给定一个长度为 $n$ 的初始序列，$q$ 次操作，每次给定下标 $opt$ 与 $k$，表示将 $a_{opt}$ 更改为 $k$，每次可以将序列任意排序，使得 $\sum\limits_{i=1}^n a_i \times i$ 最大，询问间相互独立。

显然我们要把大的往后放，这样对答案的贡献最大，即最优情况是更改后把数组升序排序。

考虑预处理：把初始序列用结构体记下编号后排序，$s$ 数组表示排序后 $a$ 的前缀和，$qp$ 数组表示排序后 $a$ 的答案前缀和。由于 $q$ 次询问中给出的下标是排序前的，所以开个 $poi_{i}$ 表示排序前下标为 $i$ 的数现在在 $poi_{i}$ 的位置。
 
我们假设原序列为 ```1 2 4 6 10```，替换后的数小到大排序后应更新在数组的第 $p$ 个位置。每次的 $p$ 是容易通过二分得到的。

大力分讨：

1. 替换后的数仍能使数组升序。可能的一种情况是把 $4$ 换成 $3$，可见左右两边排列位置不会受到影响，所以答案为 $ans=qp_{p-1}+qp_{n}-qp_{p}+p \times k$。其中 $k$ 为给定数值。

1. 替换后的数所在位置 $p$ 比原来位置小。可能的情况是把 $6$ 换成 $3$，它就会移到 $2$ 与 $4$ 之间去。此时 $p$ 值为 $3$，可见 $p$ 左边的数的位置不会影响，原数右边的也不会影响，只有中间的部分相当于往右移了一位，也就是答案要加上这一段的和，所以答案为 $ans=qp_{p-1}+qp_{n}-qp_{poi_{opt}}+qp_{poi_{opt}-1}-qp_{p-1}+s_{poi_{opt}-1}-s_{p-1}+k \times p$。

1. 替换后的数所在位置 $p$ 比原来位置大。可能的情况是把 $2$ 换成 $8$，它就会移到 $6$ 与 $10$ 之间去。此时 $p$ 值为 $4$，可见 $p$ 右边的数的位置不会影响，原数左边的也不会影响，只有中间的部分相当于往左移了一位，也就是答案要减去这一段的和，所以答案为 $ans=qp_{poi_{opt}-1}+qp_{n}-qp_{p}+qp_{p}-qp_{poi_{opt}}-(s_{p}-s_{poi_{opt}})+k \times p$。

以上式子可以化简，但是为了清晰呈现各部分数量关系就没有弄。

时间复杂度是 $\mathcal {O}((n+q) \log n)$ 的，分别是排序的时间和二分的时间。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,i,j,ans,q,opt,k;
int poi[150005],s[150005],qp[150005];
struct ren{
	int a,id;
}d[150005];
bool cmp(ren x,ren y){
	return x.a<y.a;
}
int check(int x){
	int l=1,r=n,sum;
	if(x>d[n].a) return n+1;
	while(l<=r){
		int mid=(l+r)>>1;
		if(d[mid].a>=x){
			sum=mid;
			r=mid-1;
		}
		else l=mid+1;
	}
	return sum;
}
signed main(){
	scanf("%lld",&n);
	for(i=1;i<=n;i++){
		scanf("%lld",&d[i].a);
		d[i].id=i;
	}
	sort(d+1,d+1+n,cmp);
	for(i=1;i<=n;i++) poi[d[i].id]=i;
	for(i=1;i<=n;i++){
		s[i]=s[i-1]+d[i].a;
		qp[i]=qp[i-1]+i*d[i].a;
	} 
	scanf("%lld",&q);
	while(q--){
		scanf("%lld%lld",&opt,&k);
		int p=check(k)-1;
		if(p<poi[opt]) ans=qp[p]+(qp[poi[opt]-1]-qp[p]+s[poi[opt]-1]-s[p])+qp[n]-qp[poi[opt]]+k*(p+1);
		else if(p==poi[opt]) ans=qp[p-1]+qp[n]-qp[p]+p*k;
		else ans=qp[poi[opt]-1]+qp[n]-qp[p]+qp[p]-qp[poi[opt]]-s[p]+s[poi[opt]]+k*p;
		printf("%lld\n",ans); 
	}
	return 0;
} 

```


---

## 作者：Timmy_ (赞：1)

# 前言

经过四次来自银组的折磨，我 USACO 终于过了！！！

# 算法一

作为 USACO 的 T1，我个人认为思维量还是偏简单的。

对于这道题，我们很快可以发现一个推论。

$ b_1\leq \cdots \leq b_n$  时。

$T = \sum _{i=1} ^N i \times b_i $ 最大。（易证
 
得出来这条结论之后，对于每个询问直接修改排序，之后暴力计算。
 
代码过于简单，我就不放了~~懒得写了~~。

时间复杂度 $O(n \times q \times \log n )$。

# 算法二

如何优化这个算法呢。
 
首先先想个问题，如果修改一个其中一个值会怎么样呢。
 
那么大概率会出现这三种情况。
 
（假设修改之后的值为 $y$）
 
第一种，修改 $b_i$ 后的值依旧 $b_{i-1}\leq y \leq b_i$，直接修改当前值然后输出就可以了，总值加上 $(y-b_i) \times i$。
 
第二种，修改当前值之后，需要插入在 $k$ 这个位置（$1 \leq k \leq i-1$），我们加上的值是 $\sum _{j=k} ^{i-1} b_j +y \times k - b_i \times i$。
 
第三种，修改当前值之后，需要插入在 $k$ 这个位置（$i+1 \leq k \leq n$），我们加上的值是 $ y\times k-\sum _{j=i+1} ^{k} b_j - b_i \times i$。
 
那么，修改 $Q$ 次也是同理，我们可以通过前缀和快速计算加和，利用二分快速找到 $k$ 最终实现 $O(q \times \log n)$。
 
## AC CODE

```cpp
#include <iostream>
#include <algorithm>
using namespace std;
const int N=15e4+5;
long long n,q;
struct node
{
	long long val;
	long long id;
}s[N];
long long a[N],pre[N];
long long at[N];
long long ans;
bool cmp(node x,node y)
{
	return x.val<y.val;
}
int main()
{
	int i,j;
	cin>>n;
	for(i=1; i<=n; i++)
		cin>>s[i].val,s[i].id=i;
	sort(s+1,s+n+1,cmp);
	for(i=1; i<=n; i++)
	{
		at[s[i].id]=i;
		a[i]=s[i].val;
		pre[i]=pre[i-1]+s[i].val;
		ans+=s[i].val*i;
	}
	cin>>q;
	for(i=1; i<=q; i++)
	{
		long long u,v;
		cin>>u>>v;
		u=at[u];
		long long pos=lower_bound(a+1,a+n+1,v)-a;
		long long temp=ans;
		if(pos>u)
		{
			temp-=a[u]*u;
			temp-=pre[pos-1]-pre[u];
			temp+=v*(pos-1);
		}
		if(pos==u)
		{
			temp-=a[u]*u;
			temp+=v*pos;
		}
		if(pos<u)
		{
			temp-=a[u]*u;
			temp+=pre[u-1]-pre[pos-1];
			temp+=v*(pos);
		}
		cout<<temp<<endl;
	} 
	return 0;
}
```

 



---

## 作者：small_john (赞：1)

## 前言

简单的二分题。

## 思路

由于每次操作没有后效性，考虑二分加前缀和。

要让 $T$ 最大，数组单调不减即可，用交换法可以证。

先给原数组排序，设第 $i$ 个数排序后的位置为 $id_i$，目前最大总和为 $ans$。

二分出第一个大于等于 $y$ 的数，位置为 $end$，分两种情况讨论：

1. $a_x\ge y$：排序后此数位置为 $end$，从 $id_x-1$ 到 $end$ 都往后移一位，则 $T=ans-a_{x}\times id_{x}+y\times end+s_{id_{x}-1}-s_{end-1}$。

2. $a_x<y$：排序后此数位置为 $end-1$，从 $end-1$ 到 $id_x+1$ 都往前移一位，则 $T=ans-a_x\times id_x+y*(end-1)-(s_{end-1}-s_{id_x})$。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5+5e4+5;
int n,a[N],id[N],_id[N],q,x,y,ans,s[N];
bool cmp(int x,int y)
{
	return a[x]<a[y]; 
}
signed main()
{
	cin>>n;
	for(int i = 1;i<=n;i++)
		cin>>a[i],id[i] = i;
	sort(id+1,id+n+1,cmp);
	for(int i = 1;i<=n;i++)
		s[i] = s[i-1]+a[id[i]],ans+=a[id[i]]*i,_id[id[i]] = i;
	cin>>q;
	while(q--)
	{
		cin>>x>>y;
		int l = 1,r = n,end = n+1;
		while(l<=r)
		{
			int mid = (l+r)/2;
			if(a[id[mid]]>=y) r = mid-1,end = mid;
			else l = mid+1;
		}
		if(a[x]>=y) cout<<ans-a[x]*_id[x]+y*end+(s[_id[x]-1]-s[end-1])<<'\n';
		else cout<<ans-a[x]*_id[x]+y*(end-1)-(s[end-1]-s[_id[x]])<<'\n';
	}
	return 0;
}
```

---

## 作者：Sirkey (赞：1)

这道题如何分析？

看，要得到最大值一定要排序。得，二分！

每一次更改会使一段的值更改。前缀和！

再看，每一次都是临时更改。前缀和都不需要维护了。

那不就直接 $A$ 了吗？

但是我们看回来，二分什么。

我们二分第一个大于我们修改的点的值，把他的位置找到。

前缀和把这个点更改后的位置 $($ 上面枚举的 $)$ 与更改前的位置的差就是我们前缀和要的。

这里分情况，如果改后到了后面去，就减。如果到了前面去，就加。

因为是临时更改嘛，所以就把值算一遍，后面直接想上述更改就好了。


```cpp
#include<bits/stdc++.h>
#define ll long long
#define FOR(i,a,b) for(ll i=(a); i<=(b); ++i)
#define ROF(i,a,b) for(ll i=(a); i>=(b); --i)
#define tell(ans) out(ans),printf("\n");
#define say(ans) out(ans),printf(" ");
#define pb push_back
/*
5
1 10 4 2 6
3
2 1 
2 8
4 5
*/
using namespace std;
inline ll read() {
    ll f=0,t=0;
    char c=getchar();
    while(!isdigit(c)) t|=(c=='-'),c=getchar();
    while(isdigit(c)) f=(f<<3)+(f<<1)+c-48,c=getchar();
    return t?-f:f;
}
inline void out(ll x) {
    if(x<0) putchar('-');
    if(x>9) out(x/10);
    putchar('0'+x%10);
}
const int MX=2e5+10;
ll a[MX],tmp[MX],past[MX],ans=0;
int main() {
	ll n=read();
	FOR(i,1,n)  tmp[i]=a[i]=read();
	sort(tmp+1,tmp+n+1);
	FOR(i,1,n) ans+=tmp[i]*i,past[i]=past[i-1]+tmp[i];
	ll q=read();
	FOR(i,1,q){
		ll x=read(),y=read();
		ll r=n,l=1,k,p;
		while(r>=l) {
			ll mid=(l+r)/2;
			if(tmp[mid]>a[x]) r=mid-1;
			else l=mid+1;
		}	
		p=l-1;
		r=n,l=1;	
		while(r>=l) {
			ll mid=(l+r)/2;
			if(tmp[mid]>y) r=mid-1;
			else l=mid+1;
		}
		if(p>=l) printf("%lld\n",ans-past[l-1]+past[p-1]-a[x]*p+y*l);
		else printf("%lld\n",ans-past[l-1]+past[p]-a[x]*p+y*(l-1));
	}
    return 0;
}
```
——end——

---

## 作者：technopolis_2085 (赞：0)

分析：

首先，我们知道，当 $b$ 数组为不降序排列时 $T$ 最高。

这很好证明，我们知道如果在数组 $b$ 中有两个数，满足：
$i < j$ 且 $b_i > b_j$，则交换 $i$ 和 $j$ 两个数会更优。

所以可以考虑把 $a$ 数组排序，并预处理出不做修改的 $T$。

同时求出来排好序的 $b$ 数组的前缀和。


接着，对于每一个询问，我们分两种情况讨论：

情况一：修改后数变小了。

此时这个数应该插入到某一个数 $best$ 的前面，且插入到 $best$ 前面会是最优的。

我们考虑求这个 $best$。

一个一个的枚举肯定会超时，又因为数组是有序的，所以可以考虑二分。

此时 $best$ 应该是 **大于** $y$ 的第一个数的位置。二分求出来即可。

答案为 $T$ 加上 $best$ 到 $x-1$ 的和（因为第 $x$ 个元素已经插入到 $best$ 前面，所以第 $best$ 个数到第 $x-1$ 个数都整体往后移动了一个位置，而这对答案的贡献为 $best$ 到 $x-1$ 的和），减去 $b_x$ 乘 $x$，在加上 $best$ 乘 $y$。 

情况二：修改后数变大了。

同上，我们要二分找出 **小于等于** $y$ 的最后一个位置 $best$。

答案为 $T$ 减去 $x+1$ 到 $best$ 的和（因为这些数整体往左移动了一个位置），减去 $b_x$ 乘 $x$，在加上$best$ 乘 $y$。 

元素的大小达到了 $10^8$，所以要开 long long。

总时间复杂度趋近于 $O(n \log n)$。

code：
```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
const int maxn=3e5+10;
int a[maxn],b[maxn];
int sum[maxn];
map<int,int> pos;

signed main(){
	int n;
	scanf("%lld",&n);
	
	for (int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		b[i]=a[i];
	}
	
	sort(b+1,b+1+n);
	
	int ans=0;
	for (int i=1;i<=n;i++){
		ans+=b[i]*i;
		sum[i]=sum[i-1]+b[i];
		pos[b[i]]=i;
	}
	
	int q;
	scanf("%lld",&q);
	
	while (q--){
		int x,y;
		scanf("%lld%lld",&x,&y);
		
		if (a[x]==y){
			printf("%lld\n",ans);
			continue;
		}
		
		x=pos[a[x]];
		
		if (y>b[x]){
			int l=x+1,r=n;
			int best=x+1;
			
			if (b[x+1]>y){
				printf("%lld\n",ans+(y-b[x])*x);
				continue;
			}
			
			while (l<=r){
				int mid=(l+r)/2;
				
				if (b[mid]>y) r=mid-1;
				else{
					best=mid;
					l=mid+1;
				}
			}
			
			int tmp=ans;
			tmp-=sum[best]-sum[x];
			tmp-=x*b[x];
			tmp+=best*y;
			printf("%lld\n",tmp);
		}else{
			if (b[x-1]<y){
				printf("%lld\n",ans-(b[x]-y)*x);
				continue; 
			} 
			
			int l=1,r=x-1;
			int best=1;
			while (l<=r){
				int mid=(l+r)/2;
				
				if (b[mid]>y){
					best=mid;
					r=mid-1;
				}else l=mid+1;
			}
			
			int tmp=ans;
			tmp+=sum[x-1]-sum[best-1];
			tmp-=x*b[x];
			tmp+=best*y;
			printf("%lld\n",tmp);
		}
	}
	return 0;
}
```


---

