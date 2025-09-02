# Potions (Hard Version)

## 题目描述

This is the hard version of the problem. The only difference is that in this version $ n \leq 200000 $ . You can make hacks only if both versions of the problem are solved.

There are $ n $ potions in a line, with potion $ 1 $ on the far left and potion $ n $ on the far right. Each potion will increase your health by $ a_i $ when drunk. $ a_i $ can be negative, meaning that potion will decrease will health.

You start with $ 0 $ health and you will walk from left to right, from first potion to the last one. At each potion, you may choose to drink it or ignore it. You must ensure that your health is always non-negative.

What is the largest number of potions you can drink?

## 说明/提示

For the sample, you can drink $ 5 $ potions by taking potions $ 1 $ , $ 3 $ , $ 4 $ , $ 5 $ and $ 6 $ . It is not possible to drink all $ 6 $ potions because your health will go negative at some point

## 样例 #1

### 输入

```
6
4 -4 1 -3 1 -3```

### 输出

```
5```

# 题解

## 作者：2021sunzishan (赞：4)

小升初蒟蒻的第一篇题解

## 题目大意：

你在一场激烈的战斗之后体力已经消耗一空，好在你来到了补给点。
补给点有一排 $N$ 瓶药剂，药剂编号   $1  \sim   N$（$N  \le  200,000$），喝下第   $i$   瓶药剂会补充你的体力        $a_i$，$a_i$ 可能为负数，这意味着该药剂会消耗你的体力 $a_i$。
起初你的体力为 $0$，你从   $1$   号药剂开始直到   $N$   号药剂，在每一瓶药剂前，你可以选择喝下或忽略药剂（由于药剂口感很好，你希望喝的越多越好）。
注意：在任何时刻，你必须保证自己的体力不能为负。
你能喝的药剂最多是多少瓶？


------------

  看完题目，蒟蒻决定用堆做
 
 

------------


## 思路：

- 定义一个变量 $ans$，记录可以喝的药剂瓶数。

- 定义一个变量记录当前体力和。

- 定义一个大根堆，记录负数的绝对值。

- 读入时，当读到正数就直接累加进体力和中，再把 $ans$ 加上$1$。

- 当读到负数时：
  1. 先把它的绝对值放入堆中，$ans$  加上 $1$，体力加上它（相当于减去他的绝对值）。
  2. 如果体力和小于 $0$ 了，那么从堆中弹出一个最大的绝对值，及为一个最小的负数，恢复体力和，再把 $ans$ 减去 $1$。

- 最后输出 $ans$ 就好了。

 如果还是看不懂，那就看代码吧！

### 切勿抄袭！！！

```
#include <bits/stdc++.h>
using namespace std;
long long n;
priority_queue<long long,vector<long long>,less<long long> >q; //大根堆
int main() {
//	freopen("potions.in","r",stdin);
//	freopen("potions.out","w",stdout);
	cin>>n;
	long long ans=0,s=0;//ans：药剂瓶数 s:当前体力和
	for (int i=1; i<=n; i++) {
		long long x;
		cin>>x;
		if (x<0)
			q.push(-x); //如果为负数，绝对值入堆
		s+=x; //当前体力和加x
		ans++; //药剂瓶数加1
		if(s<0) {  //如果体力值不满足条件了
			long long k=q.top(); //取出堆中最大的绝对值，就是最小的负数
			s+=k; //体力和恢复k
			ans--; //药剂瓶数减1，因为丢弃了一瓶药剂
			q.pop(); 
		}
	}
	cout<<ans;
	return 0;
}
```
这样这道题就解决了!

---

## 作者：Hilte (赞：4)

# 一.算法选择
- 这道题可以使用DP，也可以用贪心。
- 但是DP的时间复杂度为 $O(n^2)$ ，而贪心只有 $O(n\log n)$ 。
- 所以我们最好使用贪心。

# 二.思路
~~众所周知~~，如果想要喝多点药的话，那么就要拼劲全力去喝。  
**但是**，如果在这道题中喝药喝死了，我们就要将它~~WA的一声~~**吐出来**

1. 设置一个**优先队列** $\mathbf{Q}$ ,按照**从小到大**的顺序出队。
2. 每喝一瓶药就将它压入 $\mathbf{Q}$ 。
3. 如果凉了，就将 $\mathbf{Q}$ 里最小的药吐出来，并设置少喝一瓶药

# 三.代码

```cpp
#include<cstdio>
#include<queue>
using namespace std;
typedef long long ll;
priority_queue<ll,vector<ll>,greater<ll> > q;//从小到大
ll a[200001];

int main()
{
	ll n,cur=1,ans=0,tot=0;
	scanf("%lld",&n);
	for(ll i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	ans=n;//答案
	while(cur<=n)//没有喝到n瓶药
	{
		tot+=a[cur];//将血量增加a[i]
		q.push(a[cur]);//压入Q
		if(tot<0)//如果凉了
		{
			tot-=q.top();//反（后）悔一次，不喝这瓶药
			q.pop();
			ans--;//少喝一瓶药
		}
		cur++;
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：Cutest_Junior (赞：3)

## 题解 CF1526C2 【Potions (Hard Version)】

### 题意

+ 给出长度为 $n$ 的整数序列 $a$；
+ 生命值最初为 $0$，从 $a_1$ 到 $a_n$ 遍历数组，每遇到一个数，可以选择是否把生命值加上这个数，每个数只能被加上一次，但需时刻保证生命值非负，**不可以回头**；
+ 求最多可以加上多少个数；
+ $n\le2\times10^5$，$|a|\le10^9$。

### 做法

首先非负的数字肯定可以选，选后生命值不降且答案增加。

可以用一个数组 $sum$ 来表示走到每个位置时的生命值。

然后选负数 $a_i$，从 $sum_i$ 到 $sum_n$ 都要加上这个数，要保证加上后所有数都非负，则需这段区间中最小值大于等于 $-a_i$。

区间减、区间求最小值，可以用线段树维护。

然后考虑所有负数的选择顺序。

发现所有负数都会影响到 $sum_n$ 的值，而 $sum_n$ 的初值一定，则所有负数按 $a_i$ 从大到小的顺序排，对于每个 $a_i$，判断是否可以选，若可以则选。

### 代码

```cpp
#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long ll;

const ll inf = (1ll << 60) - 1;

const int N = 2e5 + 5;

struct node {
	int x, i;
} a[N];

bool operator < (node a, node b) {
	return a.x == b.x ? a.i > b.i : a.x > b.x;
}

struct Tree {
	Tree *ls, *rs;
	ll minn, lazy;
	
	Tree() {
		minn = 0;
		lazy = 0;
	}
	
	void update(ll x) {
		minn += x;
		lazy += x;
	}
	
	void merge(Tree tl, Tree tr) {
		minn = min(tl.minn, tr.minn);
	}
} seg[N << 1];
int tot;

void build(Tree *t, int l, int r) {
	if (l == r) {
		return;
	}
	int mid = (l + r) >> 1;
	t->ls = &seg[++tot];
	t->rs = &seg[++tot];
	build(t->ls, l, mid);
	build(t->rs, mid + 1, r);
}

void pushdown(Tree *t) {
	t->ls->update(t->lazy);
	t->rs->update(t->lazy);
	t->lazy = 0;
}

void change(Tree *t, int l, int r, int x, int y, ll k) {
//	printf("%d %d %d %d %d\n", l, r, x, y, k);
	if (x <= l && r <= y) {
		t->update(k);
		return;
	}
	int mid = (l + r) >> 1;
	pushdown(t);
	if (x <= mid) {
		change(t->ls, l, mid, x, y, k);
	}
	if (mid < y) {
		change(t->rs, mid + 1, r, x, y, k);
	}
	t->merge(*t->ls, *t->rs);
}

Tree query(Tree *t, int l, int r, int x, int y) {
	if (x <= l && r <= y) {
		return *t;
	}
	int mid = (l + r) >> 1;
	pushdown(t);
	Tree ans;
	ans.minn = inf;
	if (x <= mid) {
		ans.merge(ans, query(t->ls, l, mid, x, y));
	}
	if (mid < y) {
		ans.merge(ans, query(t->rs, mid + 1, r, x, y));
	}
	return ans;
}

ll sum[N];

int main() {
	int n;
	scanf("%d", &n);
	int cnt = 0;
	build(&seg[0], 1, n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &a[i].x);
		sum[i] = sum[i - 1];
		if (a[i].x >= 0) {
			sum[i] += a[i].x;
			++cnt;
		}
		change(&seg[0], 1, n, i, i, sum[i]);
		a[i].i = i;
//		printf("%d ", sum[i]);
	}
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; ++i) {
		if (a[i].x >= 0) {
			continue;
		}
//		printf("%d ", a[i].i);
		ll minn = query(&seg[0], 1, n, a[i].i, n).minn;
//		printf("%d ", minn);
		if (minn + a[i].x >= 0) {
			change(&seg[0], 1, n, a[i].i, n, a[i].x);
			++cnt;
//			printf("%d ", a[i].i);
		}
	}
	printf("%d\n", cnt);
}
```

---

## 作者：_Winham_ (赞：1)

题目意思：

现在我们有一个空背包，现在我们要经过一条路。这条路有 $n$ 个物品，其中这条路每个物品的价值为 $a_{i}$。现在我们要走着一条路，问捡起这些物品不仅要保持价值总和不是负数且物品数量要最大。

----

思路：

我们看数据能知道，数据会有负数，但不是是负数就得扔掉，我们得判断现在背包价值总和是不是加上这个负数就为负数，若果是就不要，如果不是就丢掉。

而我们丢弃也不是盲目丢弃，而应该丢掉价值最小的物品。而用来存背包价值最小可以用优先队列来存。

---
讲完了，上代码吧。

```cpp
#include<iostream>
#include<string>
#include<cctype>
#include<cmath>
#include<cstdlib>
#include<cstring>
#include<vector>
#include<algorithm>
#include<map>
#include<set>
#include<iomanip>
#include<queue>
using namespace std;
#define int long long
const int N = 2e5+10;
const int INF = 0x3f3f3f3f;
int n,a[N]; 
priority_queue<int,vector<int>,greater<int>>q;//从小到大优先队列 
signed main(){
	//freopen("","r",stdin);
	//freopen("","w",stdout);
	cin>>n;
	int cnt=0,sum=0;
	for(int i=1,x;i<=n;i++){
		cin>>x;
		cnt+=x;
		q.push(x);
		if(cnt<0){
			cnt-=q.top(),sum--;//我们要把背包里最没用的东西丢掉 
			q.pop();
		}
		sum++;
	}
	cout<<sum<<endl;
	return 0;
}

```

---

## 作者：_zzzzzzy_ (赞：1)

# 思路
对于正数我们显然是要加进去的。

对于负数我们可以强制加进去。

如果加进去之后和为负数，那么我们可以在前面选了的里面选个最大的，然后删掉就可以了。

我们在这里选最大值可以用优先队列或 `set`。

这里我们用 `set`。

这里说的可能不算太详细，如果看不懂思路看一下代码就懂了。

# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
priority_queue <i64, vector<i64>, less<i64>> qp;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, ans = 0;
	i64 sum = 0;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		i64 x;
		cin >> x;
		sum += x;
		ans++;
		if (x < 0) {
			qp.push(-x);
		}
		if (sum < 0) {
			sum += qp.top();
			ans--;
			qp.pop();
		}
	}
	cout << ans;
	return 0;
}
```

---

## 作者：FiraCode (赞：1)

[题目链接](https://www.luogu.com.cn/problem/CF1526C2)
## 题意
从一个长度为 $n$ 的序列中选出任意个，使这个序列的和非负，求这个序列的长度。
## 解题思路
输入，如果这个数就是非负整数，那么就加上这个数，否则就判断加上这个数是否为负数，如果不是负数，就将序列之和加上这个数，否则如果之前选的数比现在选这个数损失大，那么就把损失大的改成这个数。

[AC code](ehttps://www.luogu.com.cn/record/63797504)
## 废话少说，上代码：
```cpp
#include <bits/stdc++.h>//万能头
using namespace std;
#define ll long long
inline int read() {//快读模板 
	register char k = getchar();
	register int x = 0 , flg = 1;
	while (k < '0' || k > '9') {
		if (k == '-')flg = -1;
		k = getchar();
	}
	while (k >= '0' && k <= '9') {
		x = x * 10 + k - '0';
		k = getchar();
	}
	return x * flg;
}
inline void print(ll num) {//快输模板 
	if (num < 0)putchar('-') , num = -num;
	if (num > 9)print(num / 10);
	putchar(num % 10 + '0');
} 
int n;//有n个数 
int main() {
	n = read();
	priority_queue <int> q;//大根堆 
	ll sum = 0 , ans = 0;//sum是当前序列的和，ans是序列的长度 
	for (int i = 1 , a; i <= n; ++ i) {//循环 
		a = read();//输入 
		if (a >= 0) ++ans , sum += a;//如果当前这个数本来就是非负的，那么就加上这个数，序列长度加一 
		else {
			if (abs(a) <= sum) {//如果当前的和加上a还是非负的， 那么就加上这个数，序列长度加一 
				sum -= abs(a);//减去个数 
				q.push(abs(a));//加入大根堆 
				++ ans;//序列长度加一 
			}else {
				if (!q.empty() && q.top() > abs(a)) {//如果大根堆非空且之前选的数比这个负数小，就改成这个数 
					ll f = q.top();q.pop(); 
					sum += f - abs(a);//换，因为是覆盖掉之前选的数，所以序列长度不加 
					q.push(abs(a));//把当前更好的方案入堆 
				}
			}
		}
	}
	print(ans);//输出序列长度 
	return 0;
}
```
第一篇题解，请求审核通过，同时如果有哪里有错请大佬指出。

---

## 作者：Morax2022 (赞：0)

# CF1526C2 题解
**思路**

本题要求喝的药越多越好，所以我们可以假设每瓶都喝，但如果喝这瓶药导致了死亡，就选择先喝此药，后将答案减一并将毒性最大的药吐出来，最后加回体力。

**那如何实现呢？**

可以构造一个大根堆，每喝一瓶药就存进大根堆里，当喝死时就将队首弹出，而此时的队首一定是最毒的，将此瓶消耗你的体力再加回就行了。

# AC Code
```c
#include <bits/stdc++.h>
#define ll long long 
using namespace std;
priority_queue<ll, vector<ll>, greater<ll> >q;//大根堆 
ll a[200001], n, cnt = 0, ans = 0, tot = 0;
int main()
{
	cin >> n;
	for(ll i = 1; i <= n; i++) cin >> a[i];
	ans = n;//假设全喝 
	while(cnt <= n)
	{
		cnt++;
		tot += a[cnt];//来了就喝 
		q.push(a[cnt]);
		if(tot < 0)//喝死了 
		{
			tot -= q.top(); q.pop();//弹出最毒的并加回体力 
			ans--;//因为假设全喝，现在吐出一瓶，故减一 
		}
	}
	cout << ans;
}
```
希望本题解能给大家带来帮助！

---

## 作者：_Revenge_ (赞：0)

与简单版的思路完全一致，只需要改一下范围。   
可以去看我简单版本的博客。

### 题目简化和分析：

给您一个数组，在其中选择若干个数使得：

- 任意前缀和  $\ge 0$
- 数量尽可能的大   

我们可以使用**贪心**策略，策略如下：

- 如果当前数为**非负**，必喝。
- 而毒药尽可能的多喝，如果喝没了，就把最小的吐了。   

以上操作可以采用优先队列去优化。    
**重载运算符**
```cpp
struct node{
	ll v;
	bool operator <(const node &x)const{
		return x.v<v;
	}
};

priority_queue<node> q;
```

既然理解了思路可以动手了。

### Solution:

```cpp
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef double db;

const int N=2e5+50;
const int M=1e5+50;

inline ll read(){
    ll x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}

ll n;
ll a[N];

struct node{
	ll v;
	bool operator <(const node &x)const{
		return x.v<v;
	}
};

priority_queue<node> q;

int main()
{
	n=read();
	for(int i=1;i<=n;++i) a[i]=read();
	ll ans=n,res=1,cnt=0;
	while(res<=n)
	{
		cnt+=a[res];
		q.push((node){a[res]});
		if(cnt<0){
			node tmp=q.top();
			cnt-=tmp.v;
			q.pop();
			--ans;
		}
		++res;
	}
	printf("%lld\n",ans);	
	return 0;
}
```

---

## 作者：_Andy_Lin_ (赞：0)

[在博客园食用更佳](https://www.cnblogs.com/andy-lin102/p/16320649.html)

打了 vp 后打算来写一篇题解。

感觉我的思路还是比较特殊。

将正值的药称为保健品，负值的药称为毒药。

首先保健品是肯定要喝的。毒药的要尽量多喝。

要多喝毒药，就要尽量喝毒性弱的（也就是绝对值小的）。

可以倒序循环，找到毒药就将其放入一个堆中，堆中毒性弱的在上。

找到保健品时，努力将其透支。用保健品的效果从毒性的弱到强吃毒药。如果保健品不足以将毒药吃掉，那么用保健品将毒药的毒性削弱。

可以证明：此时的保健品只能用于此时堆中的毒药，方法一定最优。

如果没看懂，请看代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 200001
int n,a[N],t[N],num,ans;
priority_queue<int>heap;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d",a+i);
		if(a[i]>=0)++ans;
	}
	for(int i=n;i>=1;--i){
		if(a[i]<0)heap.push(a[i]);
		if(a[i]>0){
			while(!heap.empty()&&a[i]>=-heap.top()){
				a[i]+=heap.top();heap.pop();++ans;
			}
			if(!heap.empty()){
				int x=heap.top();heap.pop();
				x+=a[i];heap.push(x);
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Fa1thful (赞：0)

### 一.题意
给你一串数，求从这串数中最多取出多少个数（按顺序但不一定连续），可以使得取出来的数按取出顺序构成的数列的所有前缀和都大于等于 `0` 。

### 二.分析
首先这道题一看到题就很容易想到一个 $n^2$ 的暴力，就是可以从头到尾每个都试着取一遍，如果发现取这个数使得取出来的数的前缀和小于 `0` 了，那么就从这一位往前枚举到最开始，去掉最小的数，不取这个最小的数。因为取越大的数就越有可能使取出来的数的前缀和大于等于 `0` 的情况下取出的数更多。但是很显然 $n\le2*10^5$ 的数据范围并不允许我们这样做，所以我们必须思考出一种 $n \log n$ 或者更低时间复杂度的算法。

那么我们继续顺着这个暴力想，因为枚举一遍取出来的数是一定不可以省去的，而且扔掉一个数也不可能在 $O(1)$ 的时间复杂度中完成，所以可以初步确定这个算法的时间复杂度是 $O(n \log n)$ 的。我们继续看从前面所有的数中找到最小的数扔掉这个操作，既然要在 $ \log n$ 的复杂度下完成，那么肯定是一个数据结构。什么数据结构可以在 $\log n$ 的复杂度内完成找到之前最小的数呢？很显然就是小顶堆。至此，思路已经清晰，那么代码也就可以打了。

### 三.代码
```cpp
# include <bits/stdc++.h>
# define int long long     //不开long long见祖宗，就这个卡了我半个小时QWQ
using namespace std;
int a[2000005];
priority_queue <int> q;       //优先队列（默认是大顶堆）
signed main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        a[i] = -a[i];      //注意这里，我们把a[i]取相反数，因为相反数越大的数就越小，所以这里是为了将大顶堆变成小顶堆
    }
    int sm = 0;     //当前的数值
    int ans = 0;     //记录取的个数
    for (int i = 1; i <= n; i++)
    {
        q.push(a[i]);      //入队
        sm += -a[i];       //加上相反数的相反数，就是加上原来的数
        ans++;    //加上了一个数 
        if (sm < 0)    //如果发现了问题
        {
            sm += q.top();      //加上堆顶的数的相反数，就是减去这个数，说明不要取这个最小的数
            q.pop();         //把这个数pop掉
            ans--;           //取的数个数--
        }
    }
    cout << ans << endl;
    return 0;
}
```

### 四.关于这道题的启发
这道题教会了我们做题不要不屑去打暴力，可能正解就隐含在暴力当中。我们要积极地去打暴力，不仅考场上可以拿一点分数，而且还有可能可以通过 `STL` 优化拿到满分。当然我们也多学多用 `STL`，虽然它看起来并没有 `dp` 之类的算法思想重要，但是在关键时刻能够帮助你优化暴力，帮你拿到满分。

### 五.关于这题的一个小变式
学习信息要有举一反三的能力，那么我们来思考如果这题不仅要我们输出最多取多少个，而且也要输出取那几个数怎么办？

其实我们发现在这个算法中，那个小顶堆每次不行就弹出最小的数，这说明这个堆存的数是所有数里面最大的数，这就说明这个优先队列模拟的就是取出来的数构成的数组，所以这个问题的代码是：
```cpp
# include <bits/stdc++.h>
# define int long long 
using namespace std;
int a[2000005];
priority_queue <int> q;  
signed main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        a[i] = -a[i]; 
    }
    int sm = 0;    
    int ans = 0;    
    for (int i = 1; i <= n; i++)
    {
        q.push(a[i]);     
        sm += -a[i];    
        ans++; 
        if (sm < 0)
        {
            sm += q.top(); 
            q.pop();        
            ans--;          
        }
    }
    cout << ans << endl;
    while (!q.empty())
    {
        cout << -q.top() << " ";
        q.pop();
    }
    return 0;
}
```


------------

谢谢观赏

---

## 作者：Need_No_Name (赞：0)

# 题意：

给定一个序列，从序列中选取一些数字，使得它们的和为非负。请问最多选多少个？

# 分析：

这道题完全可以直接扫一遍，用一个 $sum$ 作为当前选的数的和不停的将当前选的数加进去，计算出 $sum$ 为负数时变将序列中最小的数弹出，这样下去。那最小值我们就容易想到用一个优先队列来维护区间最小值，做一个小顶堆，即可做出来。

# 代码：

```cpp
# include <bits/stdc++.h>
# define int long long
using namespace std;
const int N = 2e5 + 10;
priority_queue<int, vector<int>, greater<int> > que;
int pos = 1;
int sum = 0;
int ans = 0;
int n;
int a[N];
signed main()
{
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i];
	ans = n;
	while(pos <= n)
	{
		sum += a[pos];
		que.push(a[pos]);
		if(sum < 0)
		{
			sum -= que.top();
			que.pop();
			ans--;
		}
		pos++;
	}
	cout << ans << endl;
	return 0;
 } 
```


---

