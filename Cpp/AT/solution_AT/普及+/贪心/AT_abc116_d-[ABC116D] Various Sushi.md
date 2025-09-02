# [ABC116D] Various Sushi

## 题目描述

现有 $N$ 个寿司。每个寿司有两个参数：“寿司种类” $t_i$ 和 “美味程度” $d_i$。您现在需要在这 $N$ 个寿司中选择吃 $K$ 个。您的 “满足感” 会被按照如下标准计算：

- 满足感是 “基础美味程度总和” 和 “多样性加成” 数值的总和。

- “基础美味程度总和” 指的是你吃的所有寿司的美味程度的总和。

- “多样性加成” 是 $x \times x$，其中 $x$ 是你吃的寿司种类 （即一共有多少种 $t$）。

您现在想要得到最大的 “满足感”。找到这个 “满足感” 的最大值。

## 说明/提示

- $1 \leq K \leq N \leq 10 ^ 5$

- $1 \leq t_i \leq N$

- $1 \leq d_i \leq 10 ^ 9$

- 所有输入数据均为整数

### 样例解释 1

吃第 $1,2,3$ 个寿司时，“基础美味程度总和” 为 $9 + 7 + 6 = 22$，“多样性加成” 为 $2 \times 2 = 4$ ，得到 “满足感” 最大值为 $26$ ，可以验证不存在更好的吃法。

### 样例解释 2

吃第 $1,2,3,4$ 个寿司，可以验证不存在更好的吃法。

### 样例解释 3

注意数据可能会爆 $int$

### 样例解释 4、5、6

同上

## 样例 #1

### 输入

```
5 3
1 9
1 7
2 6
2 5
3 1```

### 输出

```
26```

## 样例 #2

### 输入

```
7 4
1 1
2 1
3 1
4 6
4 5
4 5
4 5```

### 输出

```
25```

## 样例 #3

### 输入

```
6 5
5 1000000000
2 990000000
3 980000000
6 970000000
6 960000000
4 950000000```

### 输出

```
4900000016```

# 题解

## 作者：Nightingale_OI (赞：7)

### 大意

有 $ n $ 个物品，每个物品有种类和价值。

要选择 $ k $ 个物品，使得价值和加上不同物品个数和的平方最大。

即如果的物品价值和为 $ x $ ，有 $ y $ 个不同种类的物品，贡献为 $ x + y^2 $ 。

### 思路

按价值降序，枚举选 $ i $ 个种类不同的物品，越靠前越好，再从前往后选择 $ k - i $ 个未选择的。

由于价值降序，则一定在选 $ i $ 个种类不同的物品中最优。

使用数组模拟可以做到线性。

时间复杂度 $ O(n \log_{2}n) $ 。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,s,l;
#define f(i,j,k) for(register int i=j;i<=k;++i)
#define g(i,j,k) for(register int i=j;i>=k;--i)
#define ii pair<int,int>
ii a[101010];
int t[101010];
int v[101010];
long long p,q;
int main(){
    cin>>n>>m;
    f(i,1,n){
        scanf("%d %d",&s,&l);
        a[i]=(ii){-l,s};
    }
    sort(a+1,a+n+1);
    s=1;l=0;
    f(i,1,m)q-=a[i].first;
    p=q;
    f(i,1,n){
        while(s<=n && v[a[s].second])++s;
        if(n<s)break;
        t[s]=v[a[s].second]=1;
        if(m<s){
            while(t[m] && m)--m;
            if(!m)break;
            q+=a[m--].first;
            q-=a[s++].first;
        }
        p=max(p,q+1ll*i*i);
    }
    printf("%lld\n",p);
    return 0;
}
```

---

## 作者：2huk (赞：6)

这是一道贪心问题，首先要做的是把所有寿司按照美味值从大到小排序。

这样做的目的是，在接下来的处理中数据就存在了单调性，不需要再次比较了。

假设排序后每杯寿司的美味值是这样的：

![](https://s1.ax1x.com/2023/04/25/p9nXsw4.png)

对于影响最终答案的 $x$ 和 $y$ 而言，此时的 $x$ 一定是最大的，但是 $y$ 可能会影响最终答案。

我们可以先按照这样求出前 $m$ 杯寿司的恢复值，作为一个基准，也提前预处理出其他东西。

```cpp
sort(a + 1, a + n + 1);		// 按美味值从大到小排序 

for (int i = 1; i <= m; i ++ )			// 先处理前 m 个寿司 
{
    if (!types[a[i].t]) y ++ ;			// 如果没有出现过这个种类的寿司，种类数加 1 
    types[a[i].t] ++ ;		// 这种种类的寿司数加 1 
    x += a[i].d;			// 总美味值加上了当前寿司的美味值 
}

res = x + y * y;		// 初始答案
```

上面的代码中，`a[i]` 存储的每杯寿司啡的信息（种类和美味度），`types[i]` 表示的是第 $i$ 中寿司当前出现的次数，$x$ 和 $y$ 同题意。

显然的是，如果单纯这样做肯定不是标准答案。所以我们考虑尝试寻找更大的答案。

我们已经统计出了当前 $x$ 和 $y$ 的值，那么显然的是，如果要重新选择一杯后面的寿司，删掉前面的寿司时，$x$ 一定是会减少的（也可能不变），因为上面的那条直线是单调递减的。

既然 $x$ 减少了，那么我们尝试将 $y$ 变大。

如果 $y$ 要变大，就说明种类数要加 $1$。如果当前要尝试把第 $i$ 杯寿司选择，那么我们该选择前面的哪一杯寿司来替换呢？

首先要明确的是，如果第 $i$ 杯寿司以前有和它相同种类的，也就是 `types[a[i].t] != 0`，那么第 $i$ 杯寿司是一定不选的。因为这样的 $y$ 不会增大。

接下来，对于前面的第 $k$ 杯寿司，如果要选一杯进行替换，这里进行分类分析：

- 如果第 $k$ 杯寿司的种类只出现过一次，也就是 `types[a[k].t] == 1`，那么如果把它替换了，种类 `a[k].t` 的寿司就不存在了，种类数加上第  $i$ 杯的又减去第 $k$ 杯的，相当于没有变化。所以不可取，
- 如果第 $k$ 杯寿司的种类出现过多次，也就是 `types[a[k].t] > 1`，那么如果把它替换了，种类 `a[k].t` 还是存在的，种类数加上第 $i$ 杯的但不减去第 $k$ 杯的，相当于种类数加了 $1$。符合我们的想法。

所以，如果想要 $y$ 增加就需要找到种类出现过多次的寿司，这样才能满足 $y$ 增大的思路。

如果有多个多个种类的寿司，那么选择那杯与第 $i$ 杯寿司替换呢？显然是要找到最后一个，因为最后一个出现的美味值最小，用它替换会使 $x$ 更大。

这一部分的代码：

```cpp
int k = m;

for (int i = m + 1; i <= n && k; i ++ )
{
	if (types[a[i].t]) continue;			// 如果这个种类前面出现过，就不应该继续处理 
	types[a[i].t] ++ , x += a[i].d;			// 这个种类数量加 1，总美味值加上当前的美味值 
	while (types[a[k].t] <= 1 && k) k -- ;	// 从后向前找到第一个数量出现多次（≥ 2 次）的 
	if (!k) break;							// 如果不存在出现多次的，退出 
	y ++, x -= a[k].d, k -- ;				// 种类加 1，总美味值减去出现多次的寿司的美味值，并在以后只需要在前 k - 1 个寿司中寻找 
	res = max(res, x + y * y);				// 尝试更新答案 
}

cout << res;		// 输出
```

## 代码

```cpp
#include <iostream>
#include <algorithm>

using namespace std;

#define int long long   		// long long

const int N = 1e5 + 10;

struct Node
{
	int t;		// type
	int d;		// delicious
	bool operator <(const Node &D) const		// 按美味值从大到小排序 
	{
		return d > D.d;
	}
}a[N];

int n, m, x, y, res;
int types[N];		// types[i] 表示第 i 种寿司有多少杯 

signed main()
{
	// 读入 
	cin >> n >> m;

	for (int i = 1; i <= n; i ++ )
	{
		int t, d;
		cin >> t >> d;
		a[i] = {t, d};
	}

    sort(a + 1, a + n + 1);		// 按美味值从大到小排序 

    for (int i = 1; i <= m; i ++ )			// 先处理前 m 个寿司 
    {
        if (!types[a[i].t]) y ++ ;			// 如果没有出现过这个种类的寿司，种类数加 1 
        types[a[i].t] ++ ;		// 这种种类的寿司数加 1 
        x += a[i].d;			// 总美味值加上了当前寿司的美味值 
    }

    res = x + y * y;		// 初始答案 
	int k = m;

	for (int i = m + 1; i <= n && k; i ++ )
	{
		if (types[a[i].t]) continue;			// 如果这个种类前面出现过，就不应该继续处理 
		types[a[i].t] ++ , x += a[i].d;			// 这个种类数量加 1，总美味值加上当前的美味值 
		while (types[a[k].t] <= 1 && k) k -- ;	// 从后向前找到第一个数量出现多次（≥ 2 次）的 
		if (!k) break;							// 如果不存在出现多次的，退出 
		y ++, x -= a[k].d, k -- ;				// 种类加 1，总美味值减去出现多次的寿司的美味值，并在以后只需要在前 k - 1 个寿司中寻找 
		res = max(res, x + y * y);				// 尝试更新答案 
	}

	cout << res;		// 输出 

	return 0;
}

---

## 作者：Maxmilite (赞：6)

### Explanation

有 $N$ 个寿司，选 $K$ 个使得满足最大值。

### Solution

#### Solution 1

$N$ 个选 $K$ 个，乍一看就觉得是背包 DP。

按照背包 DP 解法，

用 $f[i]$ 表示在这 $N$ 个寿司选 $i$ 个寿司所产生的最大满足。

一开始先对所有寿司按照类型排个序，以便于算种类数。

然后按照每个物品的重量为 $1$ 直接往上套 01DP 模板、特判一下寿司种类即可。

由于会爆 $int$，记得开 $long \ long$

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n, k, f[100005], val[100005];
struct node
{
    long long t, d;
    bool operator<(const node &x) const
    {
        if (t == x.t)
            return d > x.d;
        return t < x.t;
    }
} a[100005];
int main()
{
    scanf("%lld%lld", &n, &k);
    for (int i(1); i <= n; ++i)
        scanf("%lld%lld", &a[i].t, &a[i].d);
    sort(a + 1, a + n + 1);
    for (int i(1); i <= n; ++i)
    {
        if (a[i].t != a[i - 1].t) //特判寿司种类
            for (int j(k); j; --j)
            {
                if (f[j - 1] + a[i].d + (val[j - 1] + 1) * (val[j - 1] + 1) - (val[j - 1] * val[j - 1]) > f[j]) //dp
                    f[j] = f[j - 1] + a[i].d + (val[j - 1] + 1) * (val[j - 1] + 1) - (val[j - 1] * val[j - 1]), val[j] = val[j - 1] + 1;
            }
        else
            for (int j(k); j; --j)
            {
                if (f[j - 1] + a[i].d > f[j]) //dp
                    f[j] = f[j - 1] + a[i].d, val[j] = val[j - 1];
            }
    }

    printf("%lld\n", f[k]);
    return 0;
}
```

然后因为 $N \leq 10 ^ 5$，所以我们的 $O(n ^ 2)$ 成功地 T 飞了 /kk

#### Solution 2

考虑一下我们的 DP 哪里最耗时间。

对于某些寿司，加到已经有的寿司队列里不会对寿司种类数产生影响，并且他的价值比队列里的所有寿司都低。

所以对于这种寿司，我们要坚决阻止。

所以我们**小小贪心一下，先挑出来 $k$ 个价值最高的寿司，然后去判寿司种类对结果产生的影响**

好的我们开始。

1. 找出来前 $k$ 个价值最高的寿司

这里我们可以用一个优先队列来找出这些寿司。

在部分代码环节，我们不妨用 $tmp$ 来表示寿司。

用 $q$ 大根堆存储所有寿司，用 $rev$ 小根堆存储 $k$ 个寿司，以备后用

伪代码如下

```
struct Sushi
{
  long long t,d;
  bool operator<(const node &x) const
    return d < x.d;
} tmp;

priority_queue<Sushi> q;

priority_queue<Sushi, vector<Sushi>, greater<Sushi> > rev;

while (input tmp)
  q.push(tmp)

for i from 1 to k
  rev.push(q.top())
  q.pop()
```

2. 在存 $k$ 个寿司的同时，记录一下目前寿司的种类和总满足

由于 $1 \leq t_i \leq N$ 所以这里我用一个 $num$ 数组来记录每中寿司 $t$ 的数量，用一个 $cnt$ 记录总的寿司种类数，用 $sum$ 记录一下总满足

伪代码如下

```
while rev.push(q.top())

    if num[q.top().t] == 0
        cnt++

    num[q.top().t]++
    sum += q.top().d

```

3. 计算一下当前的总满足

这里我用一个 $ans$ 记录

伪代码如下

```
ans = sum + cnt * cnt
```

4. 开始判断寿司种类

首先什么样的寿司对我们的答案可能有贡献呢？

##### 这个寿司带来的 “多样性加成” 的收益大于 “基础美味程度总和” 的损失。

所以我们的目标就很明确了。

对于带不来 “多样性加成” 的寿司，我们直接扔掉。

对于带的来 “多样性加成” 的寿司，我们去找到现有的 $k$ 个寿司中 **去掉不会对现有种类造成影响且价值最小的** 寿司，将两寿司交换。

伪代码如下

```
while q.size() && rev.size()
    if num[q.top().t] != 0 // 寿司没有带来 “多样性加成”，不能要，去掉
        q.pop()
        continue
    if num[rev.top().t] == 1 // 去掉该寿司会对现有种类造成影响，不能去，找当前的下一个寿司
        rev.pop()
        continue
// 这样可以找到符合要求的两个寿司交换
```

找到了以后，我们进行交换，计算交换后是否满足

>_这个寿司带来的 “多样性加成” 的收益大于 “基础美味程度总和” 的损失。_

且计算新的总满足，和原来的比较。

伪代码如下

```
    num[rev.top().t] --
    num[q.top().t] ++
    cnt ++
    sum -= rev.top().d
    sum += q.top().d
    ans = max (ans, sum + cnt * cnt)
```

最终找到最大的总满足，得到正解。

### AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n, k, ans, cnt, num[100005], sum;

struct node
{
    long long t, d;
    bool operator<(const node &x) const
    { return d < x.d; }
    bool operator>(const node &x) const
    { return d > x.d; }
} tmp;

priority_queue<node> q;
priority_queue<node, vector<node>, greater<node>> rev;

int main()
{
    scanf("%lld%lld", &n, &k);
    for (int i(1); i <= n; ++i)
    {
        scanf("%lld%lld", &tmp.t, &tmp.d);
        q.push(tmp);
    }
    for (int i(1); i <= k; ++i)
    {
        if (num[q.top().t]++ == 0)
            cnt++;
        sum += q.top().d;
        rev.push(q.top());
        q.pop();
    }
    ans = sum + cnt * cnt;
    while (q.size() && rev.size())
    {
        if (num[q.top().t] != 0)
        {
            q.pop();
            continue;
        }
        if (num[rev.top().t] == 1)
        {
            rev.pop();
            continue;
        }
        num[rev.top().t]--;
        num[q.top().t]++;
        cnt++;
        sum -= rev.top().d;
        sum += q.top().d;
        rev.pop();
        q.pop();
        ans = sum + cnt * cnt > ans ? sum + cnt * cnt : ans;
    }
    printf("%lld\n", ans);
    return 0;
}
```


---

## 作者：YuTianQwQ (赞：2)

# 思路和算法

我们的目标是选择 $K$ 个寿司以最大化满足度，满足度由两部分组成：吃到的寿司的美味度总和以及吃到的寿司种类的平方。首先，我们选择最美味的 $K$ 个寿司，如果这些寿司中有重复的种类，我们将其余的最美味寿司存入优先队列，以备后续使用。然后，我们从剩下的寿司中寻找新的种类，并尝试用它们替换掉优先队列中的寿司，以此增加寿司种类的数量。

# 复杂度分析

时间复杂度：由于我们需要对寿司进行排序，并在优先队列中进行插入和删除操作，因此时间复杂度为 $N \log N$。

---

## 作者：TLEWA (赞：1)

如何平衡种类与美味程度的贡献是这题的最大难点，这类题的做法也挺典的，考虑先将美味程度最大化，再在美味程度损失最小的情况下将种类逐渐往大转移。接下来我将结合我的代码来介绍我的思路：

```cpp
cin >> n >> k;
for(int i=1;i<=n;++i) {
	cin >> arr[i].t >> arr[i].d;
}

sort(arr+1,arr+1+n,cmp);

long long num=0;
long long now_ans=0,ans=0;
for(int i=1;i<=k;++i) {
	if(!t[arr[i].t]) ++num;
	else sta.push(arr[i].d);
	++t[arr[i].t];
	now_ans+=arr[i].d;
}
```
先把原数组给排序，在选取前 $k$ 美味的食物作为初始的食物选择，$num$ 这个变量是当前的种类数量。注意到我开了一个栈 $sta$ 来记录该种类已经出现过的食物的美味程度，后面转移这个 $sta$ 会用到。

```cpp
ans=now_ans+num*num;

for(int i=k+1;i<=n;++i) {
	if(!t[arr[i].t]&&!sta.empty()) { //可以增加种类数 
		++t[arr[i].t];
		now_ans+=(arr[i].d-sta.top());
		++num;
		ans=max(ans,now_ans+num*num);
		sta.pop();
	}
}
```

从第一个初始没有选择的食物开始循环，如果这个种类的食物没有被选过说明可以增加种类数，贪心地想，我们拿种类出现两次以上的美味程度最低食物与这个食物作替换，损失的美味程度最低。这个时候我们直接从 $sta$ 里面取数就可以了，但是替换完后的总满足感不一定更大，所以需要取一个最大值输出。

完整 AC 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,k;

struct Node {
	long long t,d;
}arr[100005];
int t[100005]; //

bool cmp(Node a,Node b) {return a.d>b.d;}

stack<int> sta;
int main() {
	cin >> n >> k;
	for(int i=1;i<=n;++i) {
		cin >> arr[i].t >> arr[i].d;
	}
	
	sort(arr+1,arr+1+n,cmp);
	
	long long num=0;
	long long now_ans=0,ans=0;
	for(int i=1;i<=k;++i) {
		if(!t[arr[i].t]) ++num;
		else sta.push(arr[i].d);
		++t[arr[i].t];
		now_ans+=arr[i].d;
	}
	
	ans=now_ans+num*num;
	
	for(int i=k+1;i<=n;++i) {
		if(!t[arr[i].t]&&!sta.empty()) { //可以增加种类数 
			++t[arr[i].t];
			now_ans+=(arr[i].d-sta.top());
			++num;
			ans=max(ans,now_ans+num*num);
			sta.pop();
		}
	}
	
	cout << ans;
	return 0;
}

```


---

## 作者：ycy1124 (赞：0)

### 题意
你有 $n$ 个寿司，每个寿司有一个美味值 $d_i$，和一个种类 $t_i$。当你选了 $x$ 种不同口味的寿司时能额外得到 $x^2$ 的美味值。现在你需要选择其中的 $n$ 个寿司使得总美味值最大。
### 思路
考虑贪心。发现最后选的每种寿司中一定会选同种中 $d_i$ 最大的，于是先按 $d_i$ 从大到小排个序。然后发现变成了一道类似返反悔贪心的题目。我们首先取最大的 $k$ 个作为初始假定的答案。接下来考虑如何转变到正确的答案。发现此时如果我们要额外选一个非初始答案的寿司那么这个寿司一定是未被选过的种类中最大的一个。至于为什么，我们发现如果选了一个被选过的种类，那么无论换掉哪一个寿司都一定更劣，选择其他种类中非最大的，换成最大的肯定更好。并且我们一定不会把初始答案中的某一种寿司换完。于是我们模拟这个过程，每换一个寿司统计一次答案。
### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
#define Max(a,b) a>b?a:b
#define flush() fwrite(obuf,1,O-obuf,stdout)
#define putchar(x) ((O==obuf+(1<<21))&&(flush(),O=obuf)),*O++=x
char buf[1<<23],*p1=buf,*p2=buf,obuf[1<<23],*O=obuf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
__inline__ int read(){
	register int x=0,f=1;
	register char ch=getchar();
	while(!(ch>='0'&&ch<='9'))
		ch=getchar();
	while(ch>='0'&&ch<='9')
		x=x*10+(ch^48),ch=getchar();
	return x*f;
}
__inline__ void write(register int x){
    (x>9)?write(x/10):void();
    putchar((x%10)^48);
}
struct Flush{
    ~Flush(){flush();}
}_;
struct Node{
    int t,d;
}a[100005];
bool bj[100005];
inline bool cmp(Node x1,Node x2){
    return x1.d>x2.d;
}
stack<int>q;
signed main(){
    int sum=0,ans=0,js=0,n=read(),k=read();
    for(int i=1;i<=n;i++){
        a[i].t=read(),a[i].d=read();
    }
    sort(a+1,a+n+1,cmp);//排序
    for(int i=1;i<=k;i++){
        sum+=a[i].d;//记录初始答案
        if(!bj[a[i].t]){
            sum-=js*js;
            js++;
            sum+=js*js;
            bj[a[i].t]=1;
        }
        else{//如果并非唯一一个这种种类的寿司并且并不是最大的，那么可以被替换，压入栈中
            q.push(a[i].d);
        }
    }
    ans=Max(ans,sum);
    for(int i=k+1;i<=n&&!q.empty();i++){
        if(!bj[a[i].t]){//未出现过的种类
            sum-=js*js;
            sum-=q.top();//将贡献最小的替换掉
            q.pop();
            js++;
            sum+=a[i].d;
            sum+=js*js;
            ans=Max(ans,sum);//统计最大答案
            bj[a[i].t]=1;//别忘记已经出现了
        }
    }
    write(ans);
    return 0;
}
```
[AC 记录](https://www.luogu.com.cn/record/204951829)。

---

## 作者：copper_ingot (赞：0)

使用贪心思想。

首先我们给寿司按美味程度从大到小排序，这样先选的寿司美味程度会高。

先选择前 $k$ 个寿司，计算这些寿司的“满足感”。此时这些寿司的美味程度之和是最高的，但是种类数不一定多。于是枚举后面的每一个寿司，尝试将其加入 $k$ 个寿司中。

当现在枚举到第 $i$ 个寿司，如果第 $i$ 个寿司的种类在 $k$ 个寿司中已经有了，那么选它并不会增加种类数，跳过。

否则我们找到**有同种类的寿司**且**美味程度最小**的寿司，将其删除换成第 $i$ 个寿司就行了。最后把现在的答案和以前的取 $\max$。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
struct sushi{int t, d;}a[100001];
bool cmp(sushi a, sushi b){return a.d > b.d;}
int n, k, cnt[100001], dn, tn, ans;
signed main(){
	scanf("%lld%lld", &n, &k);
	for (int i = 1; i <= n; i++) scanf("%lld%lld", &a[i].t, &a[i].d);
	sort(a + 1, a + n + 1, cmp);
	for (int i = 1; i <= k; i++){
		dn += a[i].d;
		if (!cnt[a[i].t]) tn++;
		cnt[a[i].t]++;//cnt存种类出现次数
	}//计算初始答案
	int pos = k; ans = dn + tn * tn;
	for (int i = k + 1; i <= n; i++){
		if (cnt[a[i].t]) continue;
		cnt[a[i].t]++;
		while (pos > 0 && cnt[a[pos].t] <= 1) pos--;//从后往前找
		if (!pos) break;
		cnt[a[pos].t]--;
		dn = dn - a[pos].d + a[i].d; tn++;
		ans = max(ans, dn + tn * tn);//计算并更新答案
		pos--;
	}//枚举每个寿司
	printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：Kyl_in_2024 (赞：0)

### 前言

学校赛时没做出来，然后调了一个小时，发现原来代码加上一个 `sort(a+1,a+n+1,cmp)` 就对了，难蚌。

### 思路

一开始想的是把基础美味度和多样性分开来算，后来又发现其实究竟到底是哪个类别和答案没关系，只需要知道一不一样就行了，然后就想到了贪心。

先把全部寿司按照美味度排序，把前 $k$ 个寿司先吃掉，作为最初的答案。然后开始逐步考虑多样性。

我们在前 $k$ 个里面选一个踢掉不吃，再在不与之前 $k$ 个寿司重复的情况下选择一个最好吃的寿司吃掉，然后记录答案。

可以发现，那个要被踢掉的寿司肯定得从最后往前选，因为是按照美味度降序排序。

但是如果这个里面只有它一种的话肯定不能踢，因为后来选的那个寿司肯定小于等于它，踢了的话种类一加一减，没变，总的美味度还有可能更小，肯定亏了。

### 代码

我使用的是一个 `bool` 数组 `fst` 来判断是不是只有一种的。也可以用别的方式比如记录出现次数。注意可能会爆 `int`。

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
struct sushi{
	int t,d;
}a[100005];
bool cmp(sushi a,sushi b){
	if(a.d==b.d) return a.t<b.t;//这一整行加不加随意 
	return a.d>b.d;
}
bool vis[100005];//这个种类吃过没 
bool fst[100005];//是不是第一个有它的 
signed main(){
	int n,k,sum=0,type=0,ans;
	cin >> n >> k;
	for(int i=1;i<=n;i++){
		cin >> a[i].t >> a[i].d;
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=k;i++){//先把前面k个吃掉 
		sum+=a[i].d;
		if(!vis[a[i].t]){
			type++;
			fst[i]=1;
		}
		vis[a[i].t]=1;
	}
	ans=sum+type*type;//记录答案
	int j=k+1;
	for(int i=k;i>=1&&j<=n;i--){//复杂度是O(n)，不是O(nk)。因为j>n就结束了
		if(fst[i]==1) continue;//因为如果它的这类品种是第一个出现的，而且sort了，那么丢掉它去后面找比它小的而且种类一样肯定不划算
		sum-=a[i].d;
		while(vis[a[j].t]&&j<=n) j++;//找没被吃过的新种类寿司
		if(j<=n){ 
			vis[a[j].t]=1;
			sum+=a[j].d;
			type++;//更新种类数量
			ans=max(ans,sum+type*type);
		}
	}
	cout<<ans;
	return 0;
}
```

[AC 记录](https://atcoder.jp/contests/abc116/submissions/51913319)

---

## 作者：_shine_ (赞：0)

首先可以肯定的是，如果不考虑“寿司种类”一栏，则最优方案就是把美味程度前 $k$ 大的加起来。

那么现在如果加上了“寿司种类”，则有可能会有美味程度次优秀并且和之前的“寿司种类”不同的把其中美味程度前 $k$ 大的替换掉，但在这里显而易见的是不应该替换已经选中并且“寿司种类”唯一的寿司（因为新加上一个种类的美味程度不比美味程度前 $k$ 大的优秀，并且同样“寿司种类”在当前均唯一），应该考虑的是替换掉那些美味程度在选中的最后并且“寿司种类”在当前不唯一的。

但与此同时这也有可能不是最优的，所以每次替换后的结果与最先处理的应该选择其中最大的一个。

注意要进行排序，同时那些选择寻找找替换的寿司的“寿司种类”应该唯一。

注意 ```now_cnt``` 再循环中要减小（具体见代码）。
#### code
~~存在人工修改错误，切勿抄袭。~~
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>
#define lx first
#define ly second
const int maxn=1e5+10;
int n,k;pii a[maxn];int cnt;
map<int,int>p;int now_cnt;int num;
int all_cnt,ans;
signed main(){
	scanf("%lld%lld",&n,&k);
	for(int i=1;i<=n;++i)scanf("%lld%lld",&a[i].ly,&a[i].lx);
	sort(a+1,a+n+1,[](pii x,pii y){return x.lx>y.lx;});
	for(int i=1;i<=k;++i){
        if(p[a[i].ly]==0)cnt++;
        p[a[i].ly]++,all_cnt+=a[i].lx;
    }
	ans=all_cnt+cnt*cnt;
    // cout << all_cnt << " " << cnt << endl;
	now_cnt=k;for(int i=k+1;i<=n&&now_cnt;++i){if(p[a[i].ly])continue;
		while(p[a[now_cnt].ly]<=1 && now_cnt>=1){now_cnt--;}
        all_cnt+=a[i].lx,p[a[i].ly]++;
        if(now_cnt==0)break;
		p[a[now_cnt].ly]--,all_cnt-=a[now_cnt].lx,cnt++;now_cnt--;
		ans=max(ans,all_cnt+cnt*cnt); 
		// cout << all_cnt << " " << cnt << endl;
	}
//	cout << all_cnt << " " << cnt << endl;
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：_Gabriel_ (赞：0)

### 思路

题意是在 $N$ 个寿司中选择吃 $K$ 个，并让“满足感”最大。

虽然看起来是 `dp`，但 `dp` 的 $n^2$ 算法是过不了这题的，接下来分析其他方法。

每个寿司都有种类和美味程度，根据题目意思，每个寿司的贡献值为 $t_i^2+d_i$。

按每个寿司的贡献值排序，选 $p$ 个种类不同的寿司，再从前往后选之前没选过的 $K-p$ 个寿司，这样可以让“满足感”达到最大。

### 代码

```c++
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e5 + 10;
struct node {
	int t, d;
}a[N];
bool vis[N];
vector<int> b;
int n, k;
ll sum, cnt, ans;

bool cmp(node x, node y) {
	return x.d > y.d;
}

int main() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
    	cin >> a[i].t >> a[i].d;
	}
	sort(a + 1, a + n + 1, cmp);
	for (int i = 1; i <= k; i++) {
		sum += a[i].d;
		if (vis[a[i].t]) {
			b.push_back(a[i].d);
		} else {
			vis[a[i].t] = 1;
			cnt++;
		}
	}
	ans = sum + cnt * cnt;
	for (int i = k + 1; i <= n && b.size(); i++) {
		if (vis[a[i].t]) {
			continue;
		}
		sum += a[i].d - b.back();
		b.pop_back();
		vis[a[i].t] = 1;
		cnt++;
		ans = max(ans, sum + cnt * cnt);
	}
	cout << ans;
    return 0;
}
```

---

## 作者：Melo_DDD (赞：0)

事实证明，宏定义纵使有万般不好，也不会让你挂掉。
# 题目大意

描述得很清楚，略。

# 题目实现

首先咱们按美味程度由大到小排列（记住这一点），然后按题意算出这时前 $K$ 个的满足感。

需要注意的是后面我们更换寿司时它的美味程度不可能更大，所以只能在多样性上做做文章。

所以要预处理出前 $K$ 个寿司每个的种类以及出现次数。

然后再暴力枚举后 $N-K$ 个（我们记这个寿司为 $a$），此时我们讨论被选中的 $K$ 个寿司哪个可以被替换（我们记它为 $b$）：

- 若 $a$ 的种类已经出现过了，你用它替换种类不会增加，美味程度减少，不可行。

- 若 $b$ 寿司的种类只出现了 $1$ 次，如果把它替换掉，种类没变，美味程度还减少了，肯定不行。

- 所以只有在 $b$ 出现超过一次的情况下它才有可能被替换，这时算出替换前后的最大值即可。

具体细节见下：

## 代码

```cpp
#include <bits/stdc++.h>
#define f(i ,m ,n ,x) for (int i = (m) ;i <= (n) ;i += (x))
using namespace std ;
#define int long long
const int N = 1e5 + 7 ;
int n ,k ,app[N] ;
struct sushi {
	int t ;
	int d ;
	bool operator < (const sushi &cmp) const { return d > cmp.d ; }
} s[N] ;
int ans ;
template <typename T> inline void read (T &x) {
	x = 0 ;
	char ch = getchar () ;
	while (! isdigit (ch)) {
		ch = getchar () ;
	}
	while (isdigit (ch)) {
		x = (x << 1) + (x << 3) + (ch ^ 48) ;
		ch = getchar () ; 
	}
}
signed main () {
	read (n) ,read (k) ;
	f (i ,1 ,n ,1) {
		read (s[i].t) ,read (s[i].d) ;
	}
	sort (s + 1 ,s + n + 1) ;
	int x = 0 ;
	int y = 0 ;
	f (i ,1 ,k ,1) {
		if (! app[s[i].t]) {
			y ++ ;
		}
		app[s[i].t] ++ ;
		x += s[i].d ;
	} // 预处理
	ans = x + y * y ;
	int m = k ;
	f (i ,k + 1 ,n ,1) {
		if (app[s[i].t]) goto her ;
		app[s[i].t] ++ ;
		while (m && app[s[m].t] <= 1) m -- ;
		if (! m) goto her_ ;
		x += s[i].d - s[m].d ;
		y ++ ;
		m -- ;
		ans = max (ans ,x + y * y) ; 
		her : ;
	}
	her_ : ;
	cout << ans << '\n' ;
	return 0 ;
}
```

---

