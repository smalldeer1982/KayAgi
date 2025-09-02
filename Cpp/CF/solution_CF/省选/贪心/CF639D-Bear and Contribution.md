# Bear and Contribution

## 题目描述

Codeforces is a wonderful platform and one its feature shows how much someone contributes to the community. Every registered user has contribution — an integer number, not necessarily positive. There are $ n $ registered users and the $ i $ -th of them has contribution $ t_{i} $ .

Limak is a little polar bear and he's new into competitive programming. He doesn't even have an account in Codeforces but he is able to upvote existing blogs and comments. We assume that every registered user has infinitely many blogs and comments.

- Limak can spend $ b $ minutes to read one blog and upvote it. Author's contribution will be increased by $ 5 $ .
- Limak can spend $ c $ minutes to read one comment and upvote it. Author's contribution will be increased by $ 1 $ .

Note that it's possible that Limak reads blogs faster than comments.

Limak likes ties. He thinks it would be awesome to see a tie between at least $ k $ registered users. To make it happen he is going to spend some time on reading and upvoting. After that, there should exist an integer value $ x $ that at least $ k $ registered users have contribution exactly $ x $ .

How much time does Limak need to achieve his goal?

## 说明/提示

In the first sample, there are $ 4 $ registered users and Limak wants a tie between at least $ 3 $ of them. Limak should behave as follows.

- He spends $ 100 $ minutes to read one blog of the $ 4 $ -th user and increase his contribution from $ 1 $ to $ 6 $ .
- Then he spends $ 4·30=120 $ minutes to read four comments of the $ 2 $ -nd user and increase his contribution from $ 2 $ to $ 6 $ (four times it was increaded by $ 1 $ ).

In the given scenario, Limak spends $ 100+4·30=220 $ minutes and after that each of users $ 2,3,4 $ has contribution $ 6 $ .

In the second sample, Limak needs $ 30 $ minutes to read a blog and $ 100 $ minutes to read a comment. This time he can get $ 3 $ users with contribution equal to $ 12 $ by spending $ 100+3·30=190 $ minutes:

- Spend $ 2·30=60 $ minutes to read two blogs of the $ 1 $ -st user to increase his contribution from $ 2 $ to $ 12 $ .
- Spend $ 30+100 $ minutes to read one blog and one comment of the $ 3 $ -rd user. His contribution will change from $ 6 $ to $ 6+5+1=12 $ .

## 样例 #1

### 输入

```
4 3 100 30
12 2 6 1
```

### 输出

```
220
```

## 样例 #2

### 输入

```
4 3 30 100
12 2 6 1
```

### 输出

```
190
```

## 样例 #3

### 输入

```
6 2 987 789
-8 42 -4 -65 -8 -8
```

### 输出

```
0
```

# 题解

## 作者：233zhang (赞：1)

# 题意：



有 $n$ 个贡献值 $v_1$，$v_2$，…，$v_n$，将其中一个贡献值 $+5$ 需要花费 $b$，将其中一个贡献值 $+1$ 需要花费 $c$。求需要使其中的 $k$ 个贡献值相等的最小花费。



# 思路：



由于只有两种操作，$+5$ 和 $+1$，我们很容易想到，将贡献值按照 $\bmod 5$ 分类，由于 $+5$ 操作并不会影响分类的改变，我们只需要考虑进行了几次 $+1$ 操作，并且五次 $+1$ 实质上和一次 $+5$ 没区别，对于每一个元素，只会有 $0$~$4$ 次 $+1$ 操作，我们只需要暴力枚举即可。将这（该情况默认 $b \le 5c$，若不满足该条件，一次 $+5$ 可以用五次 $+1$ 代替）。

现在我们考虑 $u \to v$ 的代价，其为 $b \times [(v-u)/5]+c \times [(v-u) \bmod 5]$。但是我们发现，当 $v$ 改变后， $v-u$ 也会改变，导致我们原先选取的元素现在可能并非最优解，这使得我们需要实现随 $v$ 改变，可以实时更新答案。我们想到，如果我们可以预先处理出每个元素的花费，我们只需要选取前 $k$ 小的相加即可。但由于 $v$ 的改变会影响花费，我们必须剔除 $v$ 的影响。我们不难想到，$b \times [(v-u)/5] = b \times (v/5-u/5)$，而后半部分，我们可以用上述暴力枚举 $+1$ 操作预处理出来，我们只需要存下，最后再统一加上 $b \times (v/5)$ 即可。而  $c\times x-b\times b\times (u/5)$ 显然固定，我们只需要拿优先队列存储即可实现需求，代码如下：

```C++
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N=5e6+5;
const int inf=0x3f3f3f;
const int mod=1e9+7;

priority_queue<ll>q[5];
ll n,k,b,c,a[N],sum[5],ans=1e18;

void work(int x,int y) {
    int z=x%5;ll w=y*c-b*(x/5);
    q[z].push(w);sum[z]+=w;
    if (q[z].size()>k) {
        sum[z]-=q[z].top();q[z].pop();
    }
    if (q[z].size()==k) ans=min(ans,sum[z]+(x/5)*b*k);
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin>>n>>k>>b>>c;
    b=min(b,c*5);
    for (int i=1;i<=n;i++) cin>>a[i],a[i]+=1e9;
    sort(a+1,a+n+1);
    for (int i=1;i<=n;i++)
        for (int j=0;j<5;j++)
            work(a[i]+j,j);

    cout<<ans<<"\n";

    return 0;
}
```

---

## 作者：Eon_Sky (赞：1)

## Change log

- 2023.12.18 修改杂题集链接，修改部分格式。

## 广告

### [$\color{blueviolet}\text{CF 杂题集（点我）}$](https://www.cnblogs.com/Eon-Sky/p/17763683.html)

### [$\color{red}\text{博客内食用效果更佳（点我）}$](https://www.luogu.com.cn/blog/Eon/solution-cf639d)

## 主体思路：按余数分类，队列进行维护

## 复杂度：$O(n \log n)$

瓶颈在于排序，剩余处理常数较大。

## 完整思路

参考了樱雪喵的解法，会补充一些个人认为较难理解的部分。

将 $v$ 进行排序是显然的。

首先**只考虑加一的操作**，枚举最终达到的值 $v_i$，对于排好序的 $v$ 序列，**越靠后的数字花费越少**，所以最终一定选择的是 $v_{i - k +1}$ 至 $v_i$。如果只是这样我们可以直接拿前缀和算，但是其不足以扩展出此题正解，我们考虑劣化整个计算过程。

依然固定最终值 $v_i$，考虑用队列维护选择的元素，在维护过程中加入一个元素，如果目前已经有 $k$ 个元素且这个元素的花费比最大花费要小，那么我们此时去掉最大花费加入此元素一定更优。因为上文提到的**花费单调性**，所以此时队首一定是最大花费元素，直接弹出队首即可。

当存在加五操作时，**花费单调性**将不对整个序列存在（比如上一个元素可以通过加五到达目标值，而当前元素只能通过加一操作达到，此时当前花费可能更大。），因此不能直接用队列维护。考虑到将所有余数相同的数拿出来之后仍然具有单调性，所以可以按照余数分类（对 $5$ 取模），对于每个余数做一个队列，所有队列中元素总个数不超过 $k$，每次尝试从所有队首弹出最大的进行决策。

再考虑加五操作的另一种影响，目标值可能不一定是 $v_i$，也可能是 $v_i + val \quad (0 \le val < 5)$，所以都枚举一遍进行计算即可，带有五倍常数，去掉重复枚举可以减小常数。

注意如果 $b > 5c$ 时 $b \leftarrow 5c$。

## 代码实现需要注意的地方：

- 开 **long long**。

- 存在负数，所以考虑所有数减去最小值进行转非负。


## 参考代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef unsigned UN;
typedef double DB;
//--------------------//
const int N = 2e5 + 5;

int n, k, b, c, v[N];

LL get(int x, int y) { // 计算从 x 到 y 的贡献
    return 1LL * (y - x) / 5 * b + 1LL * (y - x) % 5 * c;
}

int qh[5], qt[5]; // 队首、队尾
vector<int> a[5], q[5];

LL ans = LONG_LONG_MAX;

void calc(int now) {
    for (int i = 0; i < 5; i++)
        qh[i] = 0, qt[i] = -1;
    int cnt = 0, las = 0; LL sum = 0;
    for (auto x : q[now]) { // 枚举所有目标值
        sum += 1LL * cnt * ((x - las) / 5) * b; // 加上与上次的差值，抵消贡献
        for (int i = 0; i < 5; i++) {
            while (qt[i] + 1 < a[i].size() && a[i][qt[i] + 1] <= x) { // 尝试插入当前值
                if (cnt == k) {
                    LL mx = 0;
                    for (int j = 0; j < 5; j++) // 寻找最大值尝试弹出
                        if (qh[j] <= qt[j])
                            mx = max(mx, get(a[j][qh[j]], x));
                    if (mx > get(a[i][qt[i] + 1], x)) // 如果更优就弹出
                        for (int j = 0; j < 5; j++)
                            if (qh[j] <= qt[j] && mx == get(a[j][qh[j]], x)) {
                                // printf("del %lld\n", mx);
                                cnt--, sum -= mx, qh[j]++;
                                break;
                            }
                }
                if (cnt == k) // 如果没有弹出最大值说明没必要再加入元素了
                    break;
                // printf("ins %lld\n", get(a[i][qt[i] + 1], x));
                cnt++, sum += get(a[i][qt[i] + 1], x), qt[i]++; // 加入当前元素
            }
        }
        if (cnt == k)
            ans = min(ans, sum); // 更新答案
        las = x;
    }
}
//--------------------//
int main() {
    scanf("%d%d%d%d", &n, &k, &b, &c);
    b = min(1LL * b, 5LL * c);
    for (int i = 1; i <= n; i++)
        scanf("%d", &v[i]);
    sort(v + 1, v + n + 1);
    for (int tem = v[1], i = 1; i <= n; i++)
        v[i] -= tem; // 转非负
    for (int i = 1; i <= n; i++) {
        a[v[i] % 5].push_back(v[i]);
        for (int j = 0; j < 5; j++)
            if (i == n | v[i] + j < v[i + 1])
                q[(v[i] + j) % 5].push_back(v[i] + j); // 枚举所有可能目标值
    }
    for (int i = 0; i < 5; i++)
        calc(i);
    printf("%lld", ans);
    return 0;
}
```

---

## 作者：樱雪喵 (赞：1)

## Description

有 $n$ 个贡献值 $v_1,v_2,\dots,v_n$，将其中一个贡献值 $+5$ 需要花费 $b$，将其中一个贡献值 $+1$ 需要花费 $c$。  
求需要使其中的 $k$ 个贡献值相等的最小花费。  
$2\le n,k\le 2\times 10^5$，$1\le b,c\le 2000$，$|v_i|\le 10^9$。

## Solution

将 $v_i$ 升序排序，从小到大枚举 $k$ 个数相等后的值 $x$。

发现如果没有第一种操作，那么每个数增加到 $x$ 的代价是单调的，令至少 $k$ 个数变成 $a_i$ 的最优方案一定是修改 $a_{i-k+1}$ 到 $a_i$ 这一段。

而第一种操作会对单调性造成影响。但是可以发现，对于所有 $\bmod\ 5$ 的值相同的 $v_i$，它们之间不会被 $+5$ 的操作改变单调性。  
同理，我们也可以得到 $+5$ 操作对可能成为答案的数的影响：所有 $v_i+j(j\in [0,4])$ 都可能成为最后的答案。

把 $v_i$ 按 $\bmod\ 5$ 的值分组，同时把询问也按此分组。那么同组的 $v_i$ 之间单调；同组的询问之间也单调。  
对每组分别维护属于答案的队列，每次新增元素时删除 $5$ 组中代价最大的那个队首即可。

时间复杂度 $O(n\log n)$，瓶颈在排序。

```cpp
#define int long long
const int N=2e5+5,inf=1e18;
int n,k,b,c,v[N];
vector<int> a[5],q[5];
int ans=inf,st[5],ed[5];
il int get(int x,int y) {return (y-x)/5*b+(y-x)%5*c;}
void solve(int id)
{
    for(int i=0;i<5;i++) st[i]=0,ed[i]=-1;
    int sum=0,now=0;
    for(int I=0;I<q[id].size();I++)
    {
        int x=q[id][I],lst=I?q[id][I-1]:id;
        now+=sum*((x-lst)/5)*b;
        for(int i=0;i<5;i++) 
        {
            while(ed[i]+1<a[i].size()&&a[i][ed[i]+1]<=x) 
            {
                if(sum==k)
                {
                    int mx=0;
                    for(int j=0;j<5;j++)
                        if(st[j]<=ed[j]) mx=max(mx,get(a[j][st[j]],x));
                    if(mx>get(a[i][ed[i]+1],x))
                    for(int j=0;j<5;j++)
                        if(st[j]<=ed[j]&&get(a[j][st[j]],x)==mx) {now-=mx,sum--,st[j]++;break;}
                }
                if(sum<k) sum++,ed[i]++,now+=get(a[i][ed[i]],x);
                else break;
            }
        }
        if(sum==k) ans=min(ans,now);
    }
}
signed main()
{
    n=read(),k=read(),b=read(),c=read();
    b=min(b,5*c);
    for(int i=1;i<=n;i++) v[i]=read();
    sort(v+1,v+n+1); 
    int mn=abs(v[1]);
    for(int i=1;i<=n;i++) v[i]+=mn;
    for(int i=1;i<=n;i++) 
    {
        a[v[i]%5].push_back(v[i]);
        for(int j=0;j<5;j++) if(i==n||v[i]+j<v[i+1]) q[(v[i]+j)%5].push_back(v[i]+j);
    }
    for(int i=0;i<5;i++) solve(i);
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：SFlyer (赞：0)

首先 $1,5$ 这个显然是着手点。如果 $b>5c$ 则令 $b=5c$，否则一次性选 $5$ 个就没有意义了。现在 $u\rightarrow v$ 的代价是 $b\times [(v-u)/5]+c\times ((v-u)\bmod 5)$。但是发现 $v\gets v+1$ 的之后这个 $\bmod$ 也会动，很讨厌。因此按照 $v$ 的 $\pmod 5$ 分类，这样只有前面的会动。

那么现在哪些 $x$（题面中的）是有意义的呢？显然只有 $t_i+[0,5)$ 是有意义的。现在已经可以写程序了。

但是很难写啊。从大到小枚举这些数，还有一个性质：我们因为要给 $b\times [...]$ 中的数加一，我们其实可以前面减去再加回去（就是移项），这样就更好写了。用一个 set 维护前 $k$ 小，每次只会加入一个数。

代码很简单啊。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 2e5+5;

ll n,k,b,c,a[N],sum[5],ans=1e18;
multiset<ll> s[5];

void sol(ll x,ll fr){
	int mod=x%5;
	ll it=(x-fr)*c-b*(x/5);
	s[mod].insert(it),sum[mod]+=it;
	if (s[mod].size()>k){
		auto pr=s[mod].end(); pr--;
		sum[mod]-=*pr;
		s[mod].erase(pr);
	}
	if (s[mod].size()==k){
		ans=min(ans,sum[mod]+(x/5)*b*k);
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin>>n>>k>>b>>c;
	b=min(b,c*5);
	for (int i=1; i<=n; i++){
		cin>>a[i];
		a[i]+=1e9;
	}
	sort(a+1,a+1+n);
	for (int i=1; i<=n; i++){
		for (int j=0; j<5; j++){
			sol(a[i]+j,a[i]);
		}
	}
	cout<<ans<<"\n";
	return 0;
}
```

---

## 作者：johnsmith0x3f (赞：0)

## 0x00 Outline

- 给定 $n$ 个数和两种操作：

1. 花费 $b$ 的代价使一个数 $+5$。

2. 花费 $c$ 的代价使一个数 $+1$。

- 求若干操作后存在至少 $k$ 个数相等的最小代价。

## 0x01

- 考虑只有第二种操作的简化版问题。

- 设最后相等的 $k$ 个数中，操作前最大的数为 $y$。

- 此时必有 $x = y$，否则 $x \gets x - 1$ 即为一组更优解。

- 于是可以将 $\{ a_n \}$ 升序排序，枚举 $x = a_i \ (1 \le i \le n)$，此时若要使 $a_j \gets a_i \ (1 \le j \le i)$，显然花费的代价随着 $j$ 的增大而减小。

- 可维护一线性表，存储当前解，表中的元素满足代价单调不增，当 $i \gets i+1$ 时，若表中元素未达 $k$ 个，则直接加入表中；否则可删除表中代价最大的元素，根据**单调性**，该元素即为表头元素。

## 0x02

- 对于原问题，考虑将 $a_i \gets a_i + 5 - a_i \bmod 5$，则转化为与简化版类似的问题。

- 唯一不同的是，此时只有 $a_i \equiv a_j \ (\bmod \ 5)$ 的数之间才存在 0x01 中的**单调性**。

- 按模 $5$ 的余数维护 $5$ 个线性表，类似 0x01，删除时改为从 $5$ 个表头里选一个代价最大的删除即可。

---

## 作者：user52992 (赞：0)

**问题描述:**

有$n​$个贡献值$v_1, v_2 ,…, v_n​$，将其中一个贡献值$+5​$需要花费$b​$，将其中一个贡献值$+1​$需要花费$c​$。求需要使其中的$k​$个贡献值相等的最小花费。$2≤n,k≤200000​$，$1≤b,c≤2000​$，$|v_i|≤10^9 ​$

**AC代码**

```cpp
/* 朴素 */
struct node
{
    LL val;
    int add_tag;
};
node arr[200010];// 候选aim的集合
int main()
{
    int n, k;
    LL b, c;
    cin >> n >> k >> b >> c;
    b = min(b, 5 * c);// 细节, c的性价比严格不比b优
    for(int i = 1; i <= n; ++i)
    {
        cin >> arr[i].val;
        arr[i].val += 1e9;// >= 0
    }
    LL res = 4e17;// 由2e5 * 1e3 * 2e9得
    for(int r = 0; r <= 4; ++r)// 余数
    {
        for(int i = 1; i <= n; ++i)
        {
            int j = 0;
            while((arr[i].val + j) % 5 != r)j++;
            arr[i].add_tag = j;// 末端对齐
        }
        for(int i = 1; i <= n; ++i)
        {
            LL aim = arr[i].val + arr[i].add_tag;// 枚举aim
            priority_queue<LL, vector<LL>, greater<LL> > pq;// 小顶堆
            for(int j = 1; j <= n; ++j)
                if(arr[j].val + arr[j].add_tag <= aim)// 只+不-, 故需小于等于aim
                    pq.push(c * arr[j].add_tag +
                            b * (aim - (arr[j].val + arr[j].add_tag)) / 5);
            if(pq.size() < k)// 找不出k个
                continue;
            LL sum = 0;
            int cnt = k;
            while(cnt--)// 最小的k个花费
            {
                sum += pq.top();
                pq.pop();
            }
            res = min(res, sum);// 更新
        }
    }
    cout << res << endl;
    return 0;
}
/* 高效 */
struct node
{
    LL val;
    int add_tag;
};
node arr[200010];// 候选aim的集合
bool cmp(const node& a, const node& b)
{
    return a.val + a.add_tag < b.val + b.add_tag;
}
int main()
{
    int n, k;
    LL b, c;
    cin >> n >> k >> b >> c;
    b = min(b, 5 * c);// 细节, c的性价比严格不比b优
    for(int i = 1; i <= n; ++i)
    {
        cin >> arr[i].val;
        arr[i].val += 1e9;// >= 0
    }
    LL res = 4e17;// 由2e5 * 1e3 * 2e9得
    for(int r = 0; r <= 4; ++r)// 余数
    {
        for(int i = 1; i <= n; ++i)
        {
            int j = 0;
            while((arr[i].val + j) % 5 != r)j++;
            arr[i].add_tag = j;// 末端对齐
        }
        sort(arr + 1, arr + n + 1, cmp);// 排序, 单调递增!
        priority_queue<LL> pq;// 大顶堆
        LL sum = 0;
        for(int i = 1; i <= n; ++i)
        {
            LL aim = arr[i].val + arr[i].add_tag;// 枚举aim
            LL temp = c * arr[i].add_tag - b * (arr[i].val + arr[i].add_tag - r) / 5;
            sum += temp;
            pq.push(temp);
            if(pq.size() == k)
            {
                res = min(res, sum + b * (aim - r) / 5 * k);// 更新
                sum -= pq.top();// 反悔
                pq.pop();// 把堆内最大的花费弹出
            }
        }
    }
    cout << res << endl;
    return 0;
}
```

**算法描述:**

设最终的目标是`aim`.

`{arr[i] + 0, arr[i] + 1, arr[i] + 2, arr[i] + 3, arr[i] + 4,}`.

$\exist arr_i,st.arr_i \le aim \le arr_i+4$.

实现"**末端对齐**": `+1`操作,花费`c`.

设`r = aim % 5`,其他的数字一定是到$arr_i+p(0 \le p \le 4)$,使得$(arr_i + p)\% 5 = r$,再加上若干个`5`到`aim`.

"只差整数倍的`5`".

---

朴素:时间复杂度$O(n^2logn)$.

枚举`r`,再枚举`aim`,维护最小的`k`个花费.

---

高效:时间复杂度$O(nlogn)$

我们考虑优化枚举`aim`的过程.

对于一个`aim`,花费为:
$$
\Sigma  c \times add\_tag + b \times\lfloor\frac{aim - (val + add\_tag)}{5} \rfloor
$$
因为`aim`在$\Sigma$中,我们不得不每枚举一个`aim`就计算一次$\Sigma$.

考虑把`aim`从$\Sigma$中提出.

拆取下整符号: 想到$(aim-r)\% 5 =0$且$(val +add\_tag-r) \% 5 = 0$,花费为:
$$
k \times b \times \frac{aim - r}{5}+\Sigma  c \times add\_tag + b \times\frac{val + add\_tag-r}{5} 
$$
我们可以维护一个大小为`k`的大顶堆,当大顶堆的大小为`k`时,我们更新答案.

更多的细节详见代码.





---

