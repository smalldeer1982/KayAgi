# Money Buys Less Happiness Now

## 题目描述

You can never buy enough happiness, so here we go again! In this version, you can only buy $ h_i = 1 $ unit of happiness each month, but the number of months is hugely increased. We are in the realm of quantum happiness and time dilation.

Being a physicist, Charlie likes to plan his life in simple and precise terms.

For the next $ m $ months, starting with no money, Charlie will work hard and earn $ x $ pounds per month. For the $ i $ -th month $ (1 \le i \le m) $ , there'll be a single opportunity of paying cost $ c_i $ pounds to obtain one unit of happiness. You cannot buy more than one unit each month.

Borrowing is not allowed. Money earned in the $ i $ -th month can only be spent in a later $ j $ -th month ( $ j>i $ ).

Since physicists don't code, help Charlie find the maximum reachable units of happiness.

## 样例 #1

### 输入

```
6
3 3
2 2 2
6 5
2 2 8 2 6 8
6 4
4 10 3 8 6 10
2 1
1 1
4 1
4 1 3 1
4 2
1 3 4 3```

### 输出

```
2
4
3
1
2
1```

# 题解

## 作者：DrAlfred (赞：5)

摘要：反悔贪心

[传送门：https://www.luogu.com.cn/problem/CF1974G](https://www.luogu.com.cn/problem/CF1974G)

## 题意

你是一个物理学家。一开始你没有钱，每个月的末尾你会得到 $x$ 英镑。在第 $i$ 个月里，你可以付出 $c_i$ 英镑，获取 $1$ 个单位的幸福。

在任何时刻你都不能欠钱，问你在 $m$ 个月过后最多能获得多少幸福。

## 分析思路

反悔贪心板子题。

我们维护当前有的钱 $sum$ 和一个大根堆，记录用了哪些 $c_i$。

每次先试图获得当前月的幸福，$sum \gets sum - c_i$，并把 $c_i$ 放入堆中。如果当前 $sum < 0$，则需要进行反悔操作。我们希望剩下的钱尽可能多，而且每个月获得的幸福值都是一样的，所以我们只要从大根堆中取出最大的 $c_j$，并 $sum \gets sum + c_j$。容易发现只需要取出一个值就能保证 $sum \geq 0$。

在每个月的末尾，我们使 $sum \gets sum + x$。

最终堆的大小即为答案，总时间复杂度 $O\left(m \log m\right)$，可以通过本题。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
i64 t, m, x, c, sum;
inline void solve(void) {
    cin >> m >> x, sum = 0;
    priority_queue<i64> heap;
    for (int i = 1; i <= m; i++) {
        cin >> c, heap.push(c), sum -= c;
        if (sum < 0) {
            sum += heap.top(), heap.pop();
        }
        sum += x;
    }
    cout << heap.size() << '\n';
}
inline void optimizeIO(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
}
int main(int argc, char const *argv[]) {
    optimizeIO(), cin >> t;
    while (t--) solve();
    return 0;
}

```

---

## 作者：Malkin_Moonlight (赞：2)

## 题解：CF1974G Money Buys Less Happiness Now
## 思路
**反悔贪心板子题**。

维护当前拥有的钱 $money$ 和一个大根堆。
每次都试图买下当天的幸福并把价钱 $c_i$ 放进大根堆里，如果发现钱数小于零，就从大根堆里挑一个价值最大的 $c_j$ 并反悔，也就是不买 $c_j$ 了。可以看出只要取出一个值就可以让钱数 $money$ $\ge $ $0$。

## 代码
```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
#define pb emplace_back
const int MAXN=1e5+5;
const int Mod=1e9+7;
ll T,m,x,i,j;
ll c[1005];
int main()
{
	//freopen("xxx.in","r",stdin);
	//freopen("xxx.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>T;
	while(T--)
	{
	    cin>>m>>x;
	    for(i=1;i<=m;i++) cin>>c[i];
        priority_queue<ll> pq;
	    ll money=0;
	    for(i=1;i<=m;i++)
		{
	        pq.push(c[i]);
			money-=c[i];
	        if(money<0)
	        {
	        	money+=pq.top();
				pq.pop();
			}
	        money+=x;
	    }
	    cout<<pq.size()<<endl;
	}
	return 0;
}

```

---

## 作者：JOE_ZengYuQiao_0928 (赞：2)

### [先看题](https://www.luogu.com.cn/problem/CF1974G)
### 思路分析
我们可以分以下两种情况来分析这个问题：
- 当月买得起幸福，肯定直接购买。
- 当月买不起幸福，那么我们就可以考虑删除之前的一次购买，将删除这次购买所返回的钱归入总钱数，并再次购买此月的幸福。那么删除的那次购买必须是之前的最大值，才能保证留下来的钱最多。找最大值的过程可用**优先队列**优化。

既然在选择过程中，已经将相对小的钱都付了，那么结果一定最优。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,qian,zongqian,val[N];
priority_queue<int> q;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int T;
	cin>>T;
	while(T--){
		zongqian=0;
		while(q.size()!=0)q.pop();
		cin>>n>>qian;
		for(int i=1;i<=n;i++)cin>>val[i];
		for(int i=1;i<=n;i++){
			if(zongqian>=val[i]){
				zongqian-=val[i];
				q.push(val[i]);
			}
			else if(q.size()!=0&&q.top()>val[i]){
				zongqian+=q.top();
				zongqian-=val[i];
				q.pop();
				q.push(val[i]);
			}
			zongqian+=qian;
		}
		cout<<q.size()<<"\n";
	}
	return 0;
}
```

---

## 作者：hanss6 (赞：1)

# 前言：
此题与 [CF1974E](https://www.luogu.com.cn/problem/CF1974E)
唯一区别就是，每个月的贡献不是 $1$ 就是 $0$ 所以 dp 完全没必要。
 
这是本蒟蒻第一次写题解顺便复习一下反悔贪心的~~板子~~思想了。

# **思路**：
那么很容易想到贪心，只选代价小的，但是题目中说到在任何时刻你都不能欠钱，所以直接排序计算是会出现问题的，由于贡献值均为 $1$ 可以进行反悔贪心。
# 实现：
反悔贪心的精髓就是**堆**~~我认为~~。

先将这个月加入答案， $now$ 减去该答案的代价，如果手中的金钱 $now<0$ 了，那就把当前已加入的答案中代价最大的拿出来即可， $now$ 加回这个最大代价，每次循环末尾增加 $x$ ，最后堆的大小（乘上贡献 $1$ ）即为答案。

# 代码:
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,m,a[200005],x;
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--){
		priority_queue<int> q;//大根堆，堆顶是最大值
		cin>>m>>x;
		int now=0;
		for(int i=1;i<=m;i++){
			cin>>a[i];
			q.push(a[i]);//先将答案扔进堆
			now-=a[i];
			if(now<0){
				now+=q.top();//加上最大代价
				q.pop();//弹出当前最大代价
			}
			now+=x;//加上每月固定收入
		} 
		cout<<q.size()<<endl;
	}
	return 0;
}
```
#### 稍复杂一丢丢板子：
[建筑抢修P4053](https://www.luogu.com.cn/problem/P4053)。

---

## 作者：sLMxf (赞：1)

## 简述题意
对于第 $i$ 个月，你可以**选择**执行：$m\gets m-c_i,ans\gets ans+1$。每个月后，你**必须**执行：$m\gets m+x(x>0)$。

问 $ans$ 的最大值。
## 算法分析
### subtask1
枚举每个月是否交钱。时间复杂度 $O(2^n n)$。
### subtask2
我们肯定很想每次都交钱，故可以考虑每一次先交钱。

交完钱之后呢？如果亏了钱，就在之前交钱的最多的一次删去。

>Q1：怎么维护呢？  
>A1：插入、求最大值、删除最大值——堆（优先队列）！
>
>Q2：那会不会删去后还亏了钱？  
>A2：因为你删去的是堆顶，而你付的是在这个堆中的，不可能大于堆顶。
>
>Q3：凭什么此时最优？  
>A3：因为此时堆中元素都小于堆外元素，不可能一个堆中元素出去之后能放两个堆外元素进来。

最后输出堆的大小即可。
## 代码实现
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int c[200005];
priority_queue<int>q;
signed main()
{
	int T;
	cin>>T;
	while(T--)
	{
		while(!q.empty()) q.pop();
		int n,x,ys,my=0,ans=0;
		cin>>n>>x;
		for(int i=1;i<=n;i++) cin>>c[i];
		for(int i=1;i<=n;i++)
		{
			my-=c[i];
			q.push(c[i]);
			if(my<0) my+=q.top(),q.pop();
			my+=x;
		}
		cout<<q.size()<<endl;
	}
	return 0;
}
```
P.S：记得清空优先队列。

---

## 作者：Grow2011 (赞：1)

# 题目大意：

你一开始没有钱，你可以在第 $i$ 个月花费 $c_i$ 元获得 $1$ 个单位的幸福，每个月结束后会获得 $x$ 元，且你不能欠钱，问最多可以获得的幸福数量。

# 题目分析：

由于数据范围很大，所以我们不能进行 dp，考虑贪心。

对于每个月，我们都要尽可能的买幸福，所以我们要统计剩余的钱数。如果钱不够了要怎么做呢？有两种办法，一种是放弃该次幸福，一种是取消一次之前的购买。

由于不管花多少钱，买到的都是 $1$ 个单位的幸福，所以我们要尽可能地买花费少的幸福，所以对于第二种情况的处理已经很明显了，就是用之前买的最贵的幸福换这个幸福。

有了第二种情况的策略做铺垫，第一种情况的策略就显而易见了：一旦之前买的最贵的幸福都没有这个贵，就放弃这个。因为如果换了，还不如买一开始那个便宜。

那怎样处理出之前买的最贵的幸福值多少钱呢？

当然就用**优先队列**啦。

# AC Code:

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
inline int read(){
    register char c = getchar();
	register int f = 1,x = 0;
    while(c<'0'||c>'9'){
    	if(c=='-')f = -1;
		c = getchar();
	}
    while(c>='0'&&c<='9')x = (x<<3)+(x<<1)+c-'0',c = getchar();
    return x*f;
}
inline void write(register int x){
    register int cnt = 20,st[25];
    if(x==0)putchar('0');
	while(x){
		st[cnt--] = char(x%10+'0');
		x/=10;
	}
	while(cnt<20)putchar(st[++cnt]);
	putchar('\n');
	return;
}
//快读快输
int t,m,x,c,sum;
priority_queue<int>q;
//统计买了那几个幸福
signed main(){
	cin >> t;
	while(t--){
		m = read();
		x = read();
		while(!q.empty())q.pop();
		sum = 0;
      //初始化
		for(int i = 1;i<=m;i++){
			c = read();
			if(sum>=c){
				sum-=c;
				q.push(c); 
              //钱够就买
			}
			else if(!q.empty()&&q.top()>=c){
				sum+=q.top();
				q.pop();
				sum-=c;
				q.push(c);
              //如果钱不够且之前买过最贵的幸福比这个幸福贵就换
			}
			sum+=x;
		}
		cout << q.size() << "\n";//输出买了几个幸福
	}
	return 0;
}
```

---

## 作者：lihongqian__int128 (赞：1)

# CF1974G Money Buys Less Happiness Now题解
反悔贪心。

反悔贪心，意思为可以反悔的贪心。在此题中，每月所能获得的幸福都为 $1$，是一样的，所以想到一个贪心思路：

- 首先，若该月能支出钱获取幸福，则一定支出。

- 其次，若该月不能支出（钱不够了），则选取之前花费最大的一个月不获取幸福。

最终得到的结果一定最优。

使用大根堆维护最大值。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std ;
int t , m , x , c ;
priority_queue <int> p , cl ;
void _main()
{
	p = cl ;
	cin >> m >> x ;
	int s = 0 , ans = 0 ;
	for(int i = 1 ; i <= m ; i++)
	{
		cin >> c ;
		s -= c ;
		p.push(c) ;
		ans++ ;
		if(s < 0)	s += p.top() , p.pop() , ans-- ;
		s += x ;
	}
	cout << ans << '\n' ;
	return ;
}
signed main()
{
	cin >> t ;
	while(t--)	_main() ;
	return 0 ;
}
```

---

## 作者：Ame_wiki (赞：0)

题目传送门：[link](https://www.luogu.com.cn/problem/CF1974G)。

题意：见题面，写的很清楚。

思路：考虑反悔贪心，首先尝试先将当前快乐买下，将所有买过的 $c_i$ 丢进一个大根堆里，若当前出现负债，就将之前买过最大的一个作废，容易证明操作后一定不是负债。最后输出堆元素数量。

记得操作后加 $x$。

## code


```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define endl "\n"
const int N=1145140+1919810,M=3005,inf=1e18;

int n,x,a[N];

void solve(){
	int ans=0;
	priority_queue<int> qu;
	cin>>n>>x;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		ans-=a[i];
		qu.push(a[i]);
		if(ans<0){
			ans+=qu.top();
			qu.pop();
		}
		ans+=x;
	} 
	cout<<qu.size()<<endl;
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int t;
	cin>>t;
	while(t--) solve();
	return 0;
}
/*  idea By CCF_NOI
	*/
```

提交记录[见此](https://codeforces.com/problemset/submission/1974/276735268)。

时间复杂度 $O(n \log n)$。~~良心出题人放个板子。~~

---

## 作者：liyp (赞：0)

## 思路
### 理论
反悔贪心。

和它的[弱化版](https://www.luogu.com.cn/problem/CF1974E)相比，这道题的数据范围明显就不能动态规划，但是好在，这一题变成了通过 $c_i$ 英镑购买 $1$ 个单位的幸福。很明显就可以进行贪心。

但这一道题直接用贪心存在一个问题，就是金钱总数并不是固定的，而是每个月一点一点发，存在一定的后效性。这时我们可以考虑反悔贪心。

反悔贪心的过程是这样的：和普通的贪心一样，我们在每一个月份依然能购买幸福就购买幸福。但是当我们没有钱购买时，我们可以从之前购买幸福每一次花费的英镑数中取一个最大值，如果最大值比我们此刻购买需要花费的英镑数多，则我们可以实现“退货”，把我们的英镑余额加上最大值。这时就可以购买本月的幸福了。

注意：在“退货”的过程中，我们先将幸福值减去 $1$，随后又加上 $1$，因此幸福值总数不变，但是余额增加了。当我们不进行“退货”直接购买时，幸福值总数才会加 $1$。

### 实现
这道题具体实现起来是这样的：

首先我们开一个大根堆，用于对每一次花费自动取最大值：
```cpp
priority_queue<int>q;
```

接下来输入部分，然后按照理论来做。

当我们的余额可以直接购买幸福时：
```cpp
if (sum >= c[i]) {
    sum -= c[i];
    q.push(c[i]);
    ans++;
}

```
当我们要执行退货时：
```cpp
else if (!q.empty()) {
    if (q.top() > c[i]) {
        sum += q.top();
        q.pop();
        sum -= c[i];
        q.push(c[i]);
    }
}
```

这道题就完成了！

## 完整代码
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN = 2e5 + 10;
int c[MAXN];
void solve()
{
    priority_queue<int>q;
    int m, x, sum = 0;
    int ans = 0;
    cin >> m >> x;
    for (int i = 1; i <= m; i++) cin >> c[i];
    for (int i = 1; i <= m; i++) {
        if (sum >= c[i]) {
            sum -= c[i];
            q.push(c[i]);
            ans++;
        }
        else if (!q.empty()) {
            if (q.top() > c[i]) {
                sum += q.top();
                q.pop();
                sum -= c[i];
                q.push(c[i]);
            }
        }
        sum += x;
    }
    cout << ans<<endl;
    return;
}
signed main()
{
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}

```

---

## 作者：FXLIR (赞：0)

### 做法

考虑使用反悔贪心解决。

第 $i$ 天的花费可分为两种情况：

- 若现在的钱数大于等于 $c_i$，则花费 $c_i$ 英镑获取 $1$ 个单位的幸福；

- 否则，若第 $i$ 天之前某一天的花费大于 $c_i$ ，则将那一天的花费取消并花费 $c_i$ 英镑获取 $1$ 个单位的幸福。

对于第二种情况，可以用大根堆 `priority_queue` 进行维护。具体地，把花费的所有 $c_i$ 全部丢进堆里，当第一种情况不符合且堆非空时，取堆顶（记作 $top$）与第 $i$ 天所需的花费进行比较，进而判断是否属于第二种情况。

那么，具体做法就十分清晰了：对于第 $i$ 天来说，若目前的钱数大于等于 $c_i$ 英镑（即符合第一种情况），就花费 $c_i$ 英镑获取 $1$ 个单位的幸福并把 $c_i$ 丢到堆中；否则，若 $top$ 大于 $c_i$，则将 $top$ 取出，使钱数增加 $top$ 英镑，然后把 $c_i$ 丢到堆里并使钱数减少 $c_i$。最后堆中的元素数量就是最后可以获得的幸福数。

### AC code
```
#include<queue>
#include<iostream>
#define int long long
using namespace std;
int t,m,x,c,money;
signed main(){
	cin>>t;
	while(t--){
		priority_queue<int> q;
		cin>>m>>x;
		money=0;
		for(int i=1;i<=m;i++){
			cin>>c;
			if(money>=c){
				q.push(c);
				money-=c;
			}else if(!q.empty()&&q.top()>c){
				money+=q.top();
				q.pop();
				money-=c;
				q.push(c);
			}
			money+=x;
		}
		cout<<q.size()<<"\n";
	}
	return 0;
}
```

---

## 作者：Mystic_dragon (赞：0)

贪心策略就是花更少的代价得到更多的价值。简单来说就是将每个数丢进堆里，不够钱了就将花费代价最大的丢出来。~~似乎叫做什么高深莫测的反悔贪心~~。那这个操作显然就可以用堆来维护。


------------

```cpp
#include<bits/stdc++.h>
#include<cstdio>
using namespace std;
typedef long long i64;
i64 T;
i64 n,x;
i64 a[500010];
int main(){
    scanf("%lld",&T);
    while(T--){
        priority_queue<i64> q;
        i64 tot=0;
        scanf("%lld%lld",&n,&x);
        for(int i=1;i<=n;++i) scanf("%lld",&a[i]);
        for(int i=1;i<=n;++i){
            q.push(a[i]);
            tot-=a[i];
            if(tot<0){
                tot+=q.top();
                q.pop();
            }
            tot+=x;
        }
        printf("%lld\n",q.size());
    }   
	return 0;
}
```

反悔贪心双倍经验：[P9749 [CSP-J 2023] 公路](https://www.luogu.com.cn/problem/P9749)

---

## 作者：Bc2_ChickenDreamer (赞：0)

## CF1974G

### Sol

第一次做反悔贪心的题，写篇题解。

这道题目不用担心幸福值的问题，只需处理价格问题即可。我们知道，在每个月购买 $1$ 幸福值时，我们肯定想尽量的获取这个月的幸福值。所以，我们考虑每个月都尝试买下幸福值并把价格放到一个大根堆里。由于我们不能欠钱，所以当每次钱不够时（也就是小于 $0$），我们需要取出最贵的那个月并且把钱加回来。为什么要取最贵的呢？因为我们肯定要把剩余的钱做到尽量多。哪把钱加回来保证剩余的钱不是负数吗？保证，因为就算这个月买的是最贵的，我们也会加到 $0$。

最后，我们需要在处理完这些后加上工资。答案为大根堆的元素数量。

### Code

```cpp
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <queue>

using namespace std;

using ll = long long;

const int kMaxN = 2e5 + 20, kInf = (((1 << 30) - 1) << 1) + 1;
const ll kLInf = 9.22e18;

ll m, x, c[kMaxN];

int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int t;
  for (cin >> t; t; -- t) {
    ll coin = 0; // 剩余的钱
    priority_queue<int> pq; // 大根堆
    cin >> m >> x;
    for (int i = 1; i <= m; ++ i) {
      cin >> c[i];
    }
    for (int i = 1; i <= m; ++ i) {
      coin -= c[i]; // 买下这个月的幸福值
      pq.push(c[i]); // 记得入队
      if (coin < 0) { // 如果 < 0
        coin += pq.top(), pq.pop(); // 提取最贵
      }
      coin += x; // 别忘了加工资
    }
    cout << pq.size() << '\n';
  }
  return 0;
}
```

---

## 作者：tanzexiaodezhonghao (赞：0)

## 思路
贪心与维护优先队列。搞个临时变量 $temp$，作用是记录当前钱数。第 $i$ 天我们把队头设为 $top$，如果用剩下的钱能买就入队，$temp$ 减少 $top$，否则就把队头变成 $c_i$。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
typedef long long ll;
int m,x;
int c[maxn];
void solve(){
	scanf("%d%d",&m,&x);
	for(int i=1;i<=m;i++){
		scanf("%d",&c[i]);
	}
	priority_queue<int> q;
	int s=0;
	for(int i=1;i<=m;i++){
		if(s>=c[i]){
			s-=c[i];
			q.push(c[i]);
 
		}else{
			if(!q.empty()&&q.top()>c[i]){
				s+=q.top();
				q.pop();
				s-=c[i];
				q.push(c[i]);
 
			}
		}
		s+=x;
	}
	printf("%d\n",int(q.size()));
}
int main(){
	int _;
	scanf("%d",&_);
	while(_--){
		solve();
	}
	return 0;
}
```

---

## 作者：Weekoder (赞：0)

### 思路

反悔贪心。每次都考虑买下当天的幸福并把价钱丢到大根堆里，如果发现钱变成负数了，就从大根堆里挑一个价值最大的并反悔，也就是不买这个幸福了。而至于为什么要用大根堆，当然是因为返回的时候要拿回来尽量多的钱。最后，堆里还有几个元素，就可以买多少幸福。

代码：

```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 2e5 + 5;

int T, m, x, c[N], money;

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> T;
	while (T --) {
	    cin >> m >> x;
	    for (int i = 1; i <= m; i++)
	       cin >> c[i];
        priority_queue<int> pq;
	    money = 0;
	    for (int i = 1; i <= m; i++) {
	        pq.push(c[i]), money -= c[i];
	        if (money < 0)
	           money += pq.top(), pq.pop();
	        money += x;
	    }
	    cout << pq.size() << "\n"; 
	}
	return 0;
}
```

---

## 作者：__vector__ (赞：0)

因为二模没打这场比赛，结果 vp 无伤 AK 了，哈哈。  
### 想法 1
考虑 dp。  
但是，可以发现无论如何都无法设计状态，使得状态总数在一个可控的范围内，故抛弃 dp。  
### 想法 2  
考虑这个问题的一个解，该怎么优化，才能使其变得更优秀。  

注意到，如果某天以 $d$ 的代价购买了一个单位，那么如果后面某天单价 $e \lt d$，但是由于这天购买所花费的钱，而导致那天无法购买，那么肯定是不优的。   

所以做法：维护一个优先队列，记录目前的购买状态。  

从 $1$ 到 $m$ 天遍历，如果第 $i$ 天可以用剩余的钱直接购买，那么算进答案并加入队列；否则，看第 $i$ 天是否能替代掉队列中的一个元素。  

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
typedef long long ll;
int m,x;
int c[maxn];
void solve(){
	scanf("%d%d",&m,&x);
	for(int i=1;i<=m;i++){
		scanf("%d",&c[i]);
	}
	priority_queue<int> q;
	int s=0;
	for(int i=1;i<=m;i++){
		if(s>=c[i]){
			s-=c[i];
			q.push(c[i]);
 
		}else{
			if(!q.empty()&&q.top()>c[i]){
				s+=q.top();
				q.pop();
				s-=c[i];
				q.push(c[i]);
 
			}
		}
		s+=x;
	}
	printf("%d\n",int(q.size()));
}
int main(){
	int _;
	scanf("%d",&_);
	while(_--){
		solve();
	}
	return 0;
}
```

---

