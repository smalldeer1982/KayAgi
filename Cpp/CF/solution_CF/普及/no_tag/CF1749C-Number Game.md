# Number Game

## 题目描述

Alice and Bob are playing a game. They have an array of positive integers $ a $ of size $ n $ .

Before starting the game, Alice chooses an integer $ k \ge 0 $ . The game lasts for $ k $ stages, the stages are numbered from $ 1 $ to $ k $ . During the $ i $ -th stage, Alice must remove an element from the array that is less than or equal to $ k - i + 1 $ . After that, if the array is not empty, Bob must add $ k - i + 1 $ to an arbitrary element of the array. Note that both Alice's move and Bob's move are two parts of the same stage of the game. If Alice can't delete an element during some stage, she loses. If the $ k $ -th stage ends and Alice hasn't lost yet, she wins.

Your task is to determine the maximum value of $ k $ such that Alice can win if both players play optimally. Bob plays against Alice, so he tries to make her lose the game, if it's possible.

## 样例 #1

### 输入

```
4
3
1 1 2
4
4 4 4 4
1
1
5
1 3 2 1 1```

### 输出

```
2
0
1
3```

# 题解

## 作者：CENRUIYANG (赞：5)

题目要求我们要最大化 $k$ 的值，发现当 $k$ 变为 $k+1$ 时，相当于先删掉了一个数并且让第二个人操作了一次，这一轮操作之后，与 $k$ 时相同，但是数组中的数字少了，所以 $k$ 增加时是否能赢具有单调性，可以考虑二分答案。

考虑第一个人如何操作，他一定会找到最大的满足条件的点将其删去，因为这个点相比其他满足条件的点会更早变为不满足条件，这样贪心正确性显然。

考虑第二个人如何操作，发现加上 $k-i+1$ 相当于把这个数删了，因为一个数加上这个值之后一定不可能满足条件，这个人显然会贪心从最小的值开始一个一个删。

二分答案的判定就是 $O(n)$ 扫一遍，总时间复杂度 $O(n\log n)$。

[代码](https://codeforces.com/contest/1749/submission/180187422)

---

## 作者：whdywjd (赞：4)

先分析博弈策略。

Alice 在倒数第 $i$ 回合，可以删掉数列中的一个 $\leq i$ 的数。而 Bob 把数列中已有的一个数加 $i$ 后，这个数至少为 $i+1$ ，对 Alice 以后的回合失去意义，相当于删去。

对于任意 $x$ ，Alice 可以在倒数第 $x$ 回合及以前删掉它。因此，数越小，适用范围越广，越有价值。可以感性理解，在倒数第 $i$ 回合，Alice 一定会删掉 $\leq i$ 的最大的数，Bob 会删掉最小的数（也就是对最小的数 $+i$）。

我们来看 $k$ 应满足的条件。

方便起见，设 $sum_i$ 为当前数列中 $\leq i$ 的数的数量。

### 1、$sum_1\geq k$ 。

如果 $sum_1\leq k-1$，则 Bob 完全可以在前 $k-1$ 回合把数列里的 $1$ 删光，让 Alice 最后 $1$ 回合无法操作。

这个约束有什么意义呢？它使得 Bob 每一回合都只能删去 $1$ ，且 Alice 最后一回合可以操作。

因此，我们只需关心 Alice 前 $k-1$ 回合是否可以操作，不再需要考虑 Bob 操作的干扰。

### 2、对于任意 $i$，$sum_i\geq k+i-1$ 。

归纳说明。

如果 $i\leq x-1$ 时都满足上式是最后 $x-1$ 个回合可操作的充要条件，则 $i\leq x$ 时都满足上式是最后 $x$ 个回合可操作的充要条件。

首先 $i=1$ 成立。

当 $sum_x\geq k+x-1$ 时，若 $sum_x\ne sum_{x-1}$ ，可以拿走 $x$，不影响后面取数。否则拿走最大的数 $m$，而 $sum_m=sum_{x-1}=sum_x\geq k+x-1$ ，取走 $m$ 后，$sum_{x-1}$ 减少 $1$ ，因原来有 $sum_{x-1}=sum_x\geq k+x-1$，减少后仍有 $sum_{x-1}\leq k+x-2$ ，符合要求。同理，受影响的从 $m$ 到 $x-2$ 的所有 $sum$ 仍符合要求，不影响之后回合操作。

得出结论后，我们从 $1$ 向 $(n+1)/2$ 遍历，取变量 $maxk=min(maxk,sum_i+1-i)$ ，若 $maxk\geq i$ ，则 $k=i$ 符合条件，可以玩 $i$ 轮；否则不可以，输出 $i-1$ 。

复杂度 $O(tn)$ 。

代码：

```cpp
#define Happy_New_Year 2023
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAX_N 104

using namespace std;

int read() //快读
{
    int x = 0;
    char c;
    bool v = 0;
    do
    {
        c = getchar();
        if(c == '-')
            v = 1;
    } while(c < '0' || c > '9');
    do
    {
        x = (x << 3) + (x << 1) + c - '0';
        c = getchar();
    } while(c >= '0' && c <= '9');
    return v ? -x : x;
}

int n, sum[MAX_N];

int main()
{
    int T = read();
    while(T--)
    {
        memset(sum, 0, sizeof(sum));
        int n = read();
        for(int i = 1; i <= n; i++)
            sum[read()]++;
        for(int i = 2; i <= n; i++)
            sum[i] += sum[i - 1]; //累加求sum
        int mxk = n + 1 >> 1, ans = 0;
        for(int i = 1; i <= n + 1 >> 1; i++)
        {
            mxk = min(mxk, sum[i] + 1 - i);
            if(mxk < i)
                break;
            ans = i; //保存最大的可行k
        }
        printf("%d\n", ans);
    }
    return 0;
}
```

---

## 作者：Strelitzia_ (赞：3)

## 题目大意

两个人在玩游戏。

有一个序列 $\{a_n\}$ 和一个操作次数 $k$，对于第 $i$ 次操作：第一个人必须选择一个 $\{a_n\}$ 中的数 $x$ 使得 $x\le k-i+1$，随后把这个数移除；然后，第二个人必须选择一个 $\{a_n\}$ 中的数 $x$ 将其加上 $k-i+1$。在 $k$ 次操作中，若第一个人有一次不能操作了，第一个人输；否则第一个人胜。

现在给出这个序列，要求输出最大的 $k$ 使得第一个人必胜。假设两人都会选择最优策略。

------------
## 思路

先想一下两者的最优策略分别是什么。

首先，对第一个人而言，选择当前符合要求的最大的 $x$ 一定最优。如果我们选了更小的数，到下一轮 $x$ 可能就不能选了；否则到下一轮更小的那个数可能还能选。于是我们保证了最大的操作次数。

对第二个人而言，我们应该选择最小的符合下一轮要求的 $x$ 加上 $k-i+1$。如果我们选择了更大的数，可能按照第一个人的策略这个数本来就不该选，于是加上 $k-i+1$ 就没意义了。于是我们保证了使第一个人能有最小的操作次数。

考虑如何求 $k_{\min}$。我们无法直接求出，但注意到，若我们目前考虑的是 $k_1$，那么当 $k_1$ 变为 $k_1+1$ 时，我们最多可以多来一次操作，也有可能不能操作。也就是说，$k$ 越大，操作的余地越小。

那么我们就可以二分答案了。观察样例就可以知道 $k_{\max}\in [0,n]$，每一次检查 $k$ 是否可行可以 $O(n^2)$ 模拟，总复杂度 $O(tn^2\log n)$，稳过。代码如下：

```cpp
int t,n,a[N],vis[114],b[N];bool check(int nowk){
	memset(vis,0,sizeof(vis));for(int i=1;i<=n;i++) b[i]=a[i];
	for(int cntk=1;cntk<=nowk;cntk++){
		int nowmx=-1,nowid=-1;for(int i=1;i<=n;i++)
			if(!vis[i]&&b[i]<=nowk-cntk+1){
				if(nowmx<b[i]) nowmx=b[i],nowid=i;
			}
		if(nowmx==-1) return 0;
		vis[nowid]=1;nowid=-1;nowmx=1145141919810;
		for(int i=1;i<=n;i++) if(b[i]<nowmx&&!vis[i]&&b[i]<=nowk-cntk) nowmx=b[i],nowid=i;
		b[max(0ll,nowid)]+=nowk-cntk+1;
	}return 1;
}
signed main(){
	t=read();for(int nowt=1;nowt<=t;nowt++){
		n=read();for(int i=1;i<=n;i++) a[i]=read();
		int l=-1,r=n;while(l<=r){
			int mid=(l+r)>>1;if(check(mid)) l=mid+1;
			else r=mid-1;
		}printf("%lld\n",r);
	}return Strelitzia_H;
}
```

---

## 作者：Allanljx (赞：2)

## 思路
设当前可以选的数的可重集为 $s$。那么 Alice 一定会取最大的数因为大的数会更早被弹出集合，Bob 一定会给最小的数加上 $k-i+1$ 因为不论给哪个数加这个数都会被弹出集合，而大的数有可能 Alice 还没取就弹出集合，不用手动加。知道两个人的思路后就是模拟了，我用 multiset 实现的，细节见代码。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n;
int a[105];
multiset<int> s;
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--)
	{
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i];
		int ans=0;
		for(int k=1;k<=n;k++)
		{
			s.clear();
			for(int i=1;i<=n;i++) s.insert(a[i]);
			int f=0;
			for(int i=1;i<=k;i++)
			{
				while(s.upper_bound(k-i+1)!=s.end()) s.erase(*s.upper_bound(k-i+1));
				if(!s.size())
				{
					f=1;
					break;
				}
				multiset<int>::iterator it=s.upper_bound(k-i+1);
				it--;
				s.erase(it);
				if(!s.empty())
				{
					int x=*s.begin();
					s.erase(s.begin());
				}
			}
			if(!f) ans=k;
		}
		cout<<ans<<'\n';
	}
}
```

---

## 作者：zhangxiaohan007 (赞：0)

## 题目分析
有两个人玩游戏，总共 $k$ 轮。每轮两人分别操作，如果每轮第一个人都能操作，他就赢了，否则他输。求最大的 $k$。
## 思路
对于第一个人来说，每轮肯定选最大能选的那个数，不然后面可能就选不了了，最大化操作次数；而对于第二个人，选择最小的数，让最小的数变得选不了，最小化第一个人操作的次数。通过分析得出，$0 \le k \le n$，所以直接二分答案。
## 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
#define db double
#define inf 2e9
#define mod 1e6
using namespace std;
int a[150],n,maxa,b[150];
bool check(int k)
{
	int s=0,l=1,r=0;
	for(int i=1;i<=n;i++)
	{
		if(a[i]>k) break;//已经选不了就索性不选
		b[i]=a[i];
		r=i;
	}
	b[0]=0;
	for(int i=1;i<=k;i++)
	{
		while(b[r]>k-i+1) r--;
		if(r<l) return false;
		r--;
		
		l++;
		
	}
	return true;
}
void solve()
{
	scanf("%d",&n);
	maxa=0;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		maxa=max(maxa,a[i]);
	}
	sort(a+1,a+n+1);
	int l=0,r=n,mid,ans;
	while(l<=r)
	{
		mid=(l+r)/2;
		if(check(mid))
		{
			ans=mid;
			l=mid+1;
		} 
		else r=mid-1;
	}
	printf("%d\n",ans);
}
int main()
{
	int t=1;
	cin>>t;
	while(t--)
	{
		solve();
	}
	return 0;
}

```

---

## 作者：wrongaaa (赞：0)

## 思路
虚拟参赛的时候一眼二分答案，思路和代码实现都很简单。\
创建一个 $a$ 数组记录 $x$ 元素在序列中的个数。二分答案的初始边界值为 $1$ 和 $n$，随后我们创建一个 $b$ 数组，初始化成 $a$，满足后面需要。\
此时我们不难看出：爱丽丝第一次可以删 $a_1$ 到 $a_k$ 之内所有元素，第二次是 $a_1$ 到 $a_{k-1}$ 之内所有元素，爱丽丝为了保证后面有数删，肯定得先删 $k-i+1$ 的元素，因为过了此轮就不能删这个元素了，将 $a_{k-i+1}$ 减掉 $1$。可是如果 $a_{k-i+1}$ 为零真么办？我们就一直往后找，知道找到符合的 $a_{k-x+1}$ 或者 $x$ 为零。$x$ 为零就代表没数可以删，间接的意味着这个答案太大了，退出循环并且 $r$ 缩小至 $mid-1$。另外一种情况，直接将 $a_{k-x+1}$ 减去 $1$。\
对于鲍勃，他的最优解是：先改变元素小的，让爱丽丝后面无法删数，如果为零，就往大的遍历，代码实现与爱丽丝的差不多。\
单次时间复杂度：$O(n^2\log n)$。
## Code
```
#include <bits/stdc++.h>
using namespace std;

int t;
int n,a[105];

int main() {
	cin >> t;
	while (t--) {
		memset(a,0,sizeof(a));//多测要清空
		cin >> n;
		for (int i = 1; i <= n; i++) {
			int x;
			cin >> x; 
			a[x] += 1;//统计
		}
		int l = 0,r = n,ans;
		while (l <= r) {
			int mid = (l + r) / 2;
			bool flag = true;
			int b[105];
			for (int i = 1; i <= n; i++)
				b[i] = a[i];//初始化b数组
			for (int i = mid; i >= 1; i--) {
				if (b[i])
					b[i] -= 1;//上述的第二种情况
				else {//第一种
					int k = i - 1;
					while (!b[k] && k > 0)
						k -= 1;//找符合条件的元素
					if (k == 0) {
						flag = false;
						break;
					}//没有，直接退出循环，并且将flag设为false
					else
						b[k] -= 1;//有，就将它减一
				}
				int k = 1;
				while (!b[k])
					k += 1;
				b[k] -= 1;//对于鲍勃的最优操作
			}
			if (flag)
				ans = mid,l = mid + 1;//判断，符合条件就向上调整
			else
				r = mid - 1;//不符合向下调整
		}
		cout << ans << endl;//输出
	}
	return 0;
}
```

---

## 作者：CodingOIer (赞：0)

## CF1749C Number Game

### 思路分析

一道博弈论问题。

先分析规则，我们发现其中可以进行两种操作：

- 删除一个数。
- 给一个数加上一个值。

这两中操作有一个性质：对于一个 $x > k$，其不可能在经过若干次操作后满足 $x < k$。

所以第一个人会删除最大的满足条件的数，因为其即将不满足条件。

分析一下第二种操作，发现下一次第一个人删除时的条件要求比现在的大 $1$，所以操作可以转化为删除一个数。对于第二个人来说，必定是删除最小的数贡献最大。

整理下思路：

- 对于第一个人，删除最大的一个 $x,x \le k - i + 1$。
- 对于第二个人，删除最小的一个 $x$。

本题的 $t,n \le 100$，枚举 $k$ 轻松跑过，优化可以考虑二分答案。

### 代码实现

Tips：
- `std::multiset` 包含于 `set` 头文件中，可以理解为不去重的 `set`。
- `std::multiset` 的 `erase()` 删除操作如果传递一个值则会删除所有该值的数，而如果传入迭代器（`find()` 的返回值）后只会删除此迭代器指向的元素。
- `begin()` 返回第一个元素的迭代器，`rbegin()` 返回最后一个元素的迭代器。

```cpp
#include <cstdio>
#include <set>
constexpr int MaxN = 1e2 + 5;
int t;
int n;
int p[MaxN];
std::multiset<int> set;
void solve()
{
    scanf("%d", &n);
    set.clear();
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &p[i]);
    }
    for (int k = 1; k <= n; k++)
    {
        set.clear();
        for (int i = 1; i <= n; i++)
        {
            set.insert(p[i]);
        }
        int accept = true;
        for (int i = 1; i <= k; i++)
        {
            for (; !set.empty() && !(*set.rbegin() <= k - i + 1);)
            {
                set.erase(*set.rbegin());
            }
            if (set.empty())
            {
                accept = false;
                break;
            }
            set.erase(set.find(*set.rbegin()));
            if (set.empty())
            {
                if (i == k)
                {
                    break;
                }
                else
                {
                    accept = false;
                    break;
                }
            }
            set.erase(set.find(*set.begin()));
        }
        if (!accept)
        {
            printf("%d\n", k - 1);
            return;
        }
    }
    printf("%d\n", n);
}
int main()
{
    scanf("%d", &t);
    for (int i = 1; i <= t; i++)
    {
        solve();
    }
    return 0;
}
```

---

