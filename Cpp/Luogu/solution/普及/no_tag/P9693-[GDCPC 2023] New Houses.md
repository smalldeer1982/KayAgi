# [GDCPC 2023] New Houses

## 题目描述

随着广东的建设与发展，越来越多人选择来到广东开始新生活。在一片新建的小区，有 $n$ 个人要搬进 $m$ 栋排成一行的房子，房子的编号从 $1$ 到 $m$（含两端）。房子 $u$ 和 $v$ 相邻，当且仅当 $|u-v|=1$。我们需要为每一个人安排一栋房子，要求所有人入住的房子互不相同。若两个人住进了一对相邻的房子，则这两个人互为邻居。

有的人喜欢自己有邻居，而有的人不喜欢。对于第 $i$ 个人，如果他有至少一位邻居，则他的满意度为 $a_i$；否则如果他没有邻居，则他的满意度为 $b_i$。

您作为小区的规划者，需要最大化所有人的总满意度。

## 样例 #1

### 输入

```
3
4 5
1 100
100 1
100 1
100 1
2 2
1 10
1 10
2 3
100 50
1 1000```

### 输出

```
400
2
1050```

# 题解

## 作者：I_am_AKed_by_NOI (赞：3)



## 题目大意

有 $n$ 个居民，住进 $m$ 个**排成一排**的房子。若第 $i$ 个居民有邻居，分数增加 $a_i$，反之有邻居，分数增加 $b_i$。找到是分数最大的一居住方式，并输出分数。 

## 正解

因为要找到最大的分数，可以考虑动规，发现不可行，转换思路，考虑**贪心**。

我们首先假设每个人都没有邻居，那么幸福指数的总和即为 $\sum\limits_{i=1}^{n} b_i$。如果我们让第 $i$ 个人拥有邻居，那么这个总和将会增加 $a_i-b_i$。为了让总和最大，所以增加的 $a_i-b_i$ 也要尽量的大，于是我们以 $a_i-b_i$ 的值从大到小给数组排序。

数组经过排序后，我们思考如何计算 $x$ 个人拥有邻居时幸福总和最大值为多少。针对这个问题，我们可以让排序后数组中的前 $x$ 个人挨在一起，这样会使得幸福值的总和最大。

此时，总和会增加 $\sum\limits_{i=1}^{x} (a_i-b_i)$ 的幸福值。那么总和就为 

$$\sum\limits_{i=1}^{n} b_i + \sum\limits_{i=1}^{x} (a_i-b_i)=\sum\limits_{i=1}^{n} b_i + \sum\limits_{i=1}^{x} a_i- \sum\limits_{i=1}^{x}b_i=(\sum\limits_{i=1}^{n} b_i- \sum\limits_{i=1}^{x}b_i) + \sum\limits_{i=1}^{x} a_i=\sum\limits_{i=x+1}^{n} b_i + \sum\limits_{i=1}^{x} a_i$$

这里显然可以使用前缀和来优化复杂度。所以我们枚举每一个 $x$，计算最大的总和，更新答案。同时，这里要注意 $x$ 的合法性。什么意思呢，如果有 $x$ 个人要有邻居，房间数最少需要 $x+2\times(n-x)$，所以在枚举 $x$ 的过程中，要判断   $x+2\times(n-x) \le m$，否则不执行计算和更新。

## 代码
**注意！！！这不是 AC 代码！！！！**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
struct node
{
	int a;
	int b;
}data[N];
int sum1[N],sum2[N],ans;
int T,n,m;
bool cmp(node x1,node x2) //以 a_i - b_i 从大到小排序 
{
	return x1.a-x1.b>x2.a-x2.b;
}
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>n>>m;
		for(int i=1;i<=n;i++) cin>>data[i].a>>data[i].b;
		sort(data+1,data+n+1,cmp); //贪心，将数组排序 
		for(int i=1;i<=n;i++)
		{
			sum1[i]=sum1[i-1]+data[i].a; //a 的前缀和 
			sum2[i]=sum2[i-1]+data[i].b; //b 的前缀和 
		}
		2*n-1<=m?ans=sum2[n]:ans=0;
		for(int x=2;x<=n;x++) //枚举 x 
		{
			if(2*n-x<=m) //判断是否合法 
			{
				ans=max(sum1[x]+sum2[n]-sum2[x],ans); //计算答案同时更新 
			}
		}
		cout<<ans<<endl;
	}
} 
```

**十年 OI 一场空，不开 long long 见祖宗！！！**

下面是 AC 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=1e6+10;
struct node
{
	ll a;
	ll b;
}data[N];
ll sum1[N],sum2[N],ans;
ll T,n,m;
bool cmp(node x1,node x2) //以 a_i - b_i 从大到小排序 
{
	return x1.a-x1.b>x2.a-x2.b;
}
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>n>>m;
		for(int i=1;i<=n;i++) cin>>data[i].a>>data[i].b;
		sort(data+1,data+n+1,cmp); //贪心，将数组排序 
		for(int i=1;i<=n;i++)
		{
			sum1[i]=sum1[i-1]+data[i].a; //a 的前缀和 
			sum2[i]=sum2[i-1]+data[i].b; //b 的前缀和 
		}
		2*n-1<=m?ans=sum2[n]:ans=0;
		for(int x=2;x<=n;x++) //枚举 x 
		{
			if(2*n-x<=m) //判断是否合法 
			{
				ans=max(sum1[x]+sum2[n]-sum2[x],ans); //计算答案同时更新 
			}
		}
		cout<<ans<<endl;
	}
} 
```


---

## 作者：Zaku (赞：3)

[Link.](https://www.luogu.com.cn/problem/P9693)

$\mathrm{Sol:}$

为了使问题简单化，我们首先假设所有人都没有邻居。

$$t \gets \sum_{i=1}^{n} b_i$$

然后考虑 $i$ 有了邻居，他的满意度会增加 $(a_i - b_i)$。

所以将 $(a_i - b_i)$ 从大到小排序，并考虑 $k$ 个人有邻居时的总满意度。

我们首先要考虑所有人都没有邻居，即 $k=0$ 的情况。请注意，只有 $2n-1\le m$ 时才有这种可能，否则房子就不够了。此时总满意度为 $t$。

然后考虑 $k$ 个人有邻居时的情况。这时只有 $2n-k \le m$ 才能考虑。理由同上。这时我们假设有邻居的人都住在左边，没邻居的都隔着一栋房子住在右边。如图。

![](https://cdn.luogu.com.cn/upload/image_hosting/i9nec0cy.png)

此时总满意度是 $t+{\sum\limits_{i=1}^{k}}(a_i-b_i)$。

最后在 $k=2,3,\cdots n$ 的情况中取 $\max$ 即可。

~~希望没有人提出 $k$ 为什么不能等于 $1$。~~

时间复杂度 $\mathcal{O}(n\log n)$。

$\mathrm{Code:}$
```cpp
const int N = 5e5 + 5;
int a[N], b[N], c[N];
void solve(){
	int n, m;
	cin >> n >> m;
	ll t = 0;
	for (int i = 1; i <= n; i ++ ){
		cin >> a[i] >> b[i];
		t += b[i];
	}
	for (int i = 1; i <= n; i ++ )
		c[i] = a[i] - b[i];
	sort (c + 1, c + 1 + n, greater<int>());
	ll ans = 0;
	if (2 * n - 1 <= m) 
		ans = t;
	t += c[1];
	for (int k = 2; k <= n; k ++ ){
		t += c[k];
		if (2 * n - k <= m)
			ans = max(ans, t);
	}
	cout << ans << '\n';
}
```

---

## 作者：断清秋 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P9693)

好烦人啊。

注意到每个人的贡献与他的邻居是谁无关，所以我们只关心没有邻居的人的数量。

假设所有人初始都有邻居，那么每个人的权重就是 $b_i-a_i$。

然后考虑如果有 $k$ 个人没有邻居，那么必然有 $2k+(n-k) \le m$，即 $k\le m-n$。

然后直接按每个人的权重排序，贪心取前 $\le k$ 个最大的正值即可。

但是需要考虑一些 corner case。首先是 $n=1$ 的情况答案是 $b_1$，然后注意 $n-k \neq 1$。

时间复杂度 $O(n \log n)$。

---

## 作者：sfqxx1 (赞：2)

## 题目大意

有 $n$ 个居民，$m$ 个连成一片的房子，第 $i$ 个居民如果他没有邻居，幸福指数为 $b_i$，如果有邻居（左或右邻居），幸福指数为 $a_i$。

安排这 $n$ 个居民的居住，使得总幸福指数最大化。

## 思路

这道题可以用贪心解决。
 
如果居民的幸福指数 $b_i \le a_i$，则让他拥有邻居；否则，考虑让他独居。

## 代码

```
#include <iostream>

#include <vector>

#include <algorithm>

using namespace std;

int main() {

    int t;

    cin >> t;

    for(int _ = 0; _ < t; _++) {

        int n, m;

        cin >> n >> m;

        long long a = 0, b = 0, d = 0, e = 0;

        vector<pair<long long, long long>> c;

        for(int _ = 0; _ < n; _++) {

            long long x, y;

            cin >> x >> y;

            if(x >= y) {

                a += x;

                d = x;

                e = y;

                b++;

            } else {

                c.push_back(make_pair(y - x, x));

            }

        }

        sort(c.rbegin(), c.rend());//进行排序

        int f = c.size();

        int g = m - n;

        int h = min(f, g);

        if(b == 1 && h >= f) {

            if(f && d - e > c[f - 1].first) {

                a -= c[f - 1].first;

            } else {

                a = e;

            }

        }

        for(int i = 0; i < h; i++) {

            a += c[i].first + c[i].second;

        }

        for(int i = h; i < f; i++) {

            a += c[i].second;

        }

        if(b == 0 && f - h == 1) {

            a += c[h].first;

        }

        cout << a << "\n";

    }

    return 0;

}
```


---

## 作者：ZJle (赞：2)

纯纯的一眼贪心题。

如果居民有邻居的时候的满意值 $a_i$ **大于**没有邻居时的满意值  $b_i$，则让他拥有邻居。

对于 $a_i<b_i$ 的情况，因为独居需要花费 $2$ 个房子的空间大小。

所以我们贪心的去想，优先让 $b_i-a_i$ 大的居民去独居。

```
#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10;
struct syf
{
    int x, y;
} q[N];
#define int long long
int n, m, now;
bool cmp(syf a, syf b) { return (a.x - a.y) > (b.x - b.y); }
void solve1()
{
    if (q[1].x + q[2].x >= q[1].y + q[2].y)
    {
        int cnt = max(2ll, now);
        int c = 2 * (n - cnt);
        if (c + cnt <= m)
        {
            int num = 0;
            for (int i = 1; i <= n; ++i)
            {
                if (i <= cnt)
                    num += q[i].x;
                else
                    num += q[i].y;
            }
            cout << num << "\n";
            return;
        }
        else
        {
            int num = 0;
            int cnt = 2 * n - m;
            for (int i = 1; i <= n; ++i)
            {
                if (i <= cnt)
                    num += q[i].x;
                else
                    num += q[i].y;
            }
            cout << num << "\n";
            return;
        }
    }
}
void solve2()
{
    if (2 * n - 1 <= m)
    {
        int num = 0;
        for (int i = 1; i <= n; ++i)
            num += q[i].y;
        cout << num << '\n';
        return;
    }
    else
    {
        int num = 0;
        int cnt = 2 * n - m;
        for (int i = 1; i <= n; ++i)
        {
            if (i <= cnt)
                num += q[i].x;
            else
                num += q[i].y;
        }
        cout << num << "\n";
        return;
    }
}
void solve()
{

    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
    {
        cin >> q[i].x >> q[i].y;
    }
    sort(q + 1, q + n + 1, cmp);
    if (n == 1)
    {
        cout << q[1].y << '\n';
        return;
    }
    now = 0;
    for (int i = 1; i <= n; ++i)
    {
        if (q[i].x - q[i].y >= 0)
            now++;
    }
    if (q[1].x + q[2].x >= q[1].y + q[2].y)
        solve1();
    else
        solve2();
}
auto main() -> signed
{
    int t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}

```

---

## 作者：Flaw_Owl (赞：1)

# P9693 [GDCPC2023] New Houses 题解

题目链接：[P9693 [GDCPC2023] New Houses](https://www.luogu.com.cn/problem/P9693)

## 题目分析

题目类型有点像高中时期做过的排列组合题，将 $n$ 个人安置在 $m$ 个“格子”中。我们考虑放置的过程，发现“独居”的人一次至少要占两个格子（才能保证左右都没人），而不独居的人只要一个格子就够了。因此，我们应该**先安置独居的人**，其他的人安排在剩下的格子即可。

接着考虑我们**最多让多少人独居**。按照上面的思路，假设最多 $k$ 个人独居，那么有

$$ 2k + (n-k) = m $$

即 $k = m - n$。

然后考虑我们安排独居的顺序。显然，$b > a$ 的人应该先安排独居。但如果满足独居条件的人超过 $k$，那么我们就要考虑优先让谁独居。如果一个人独居和不独居的满意度差不多，那么他就可以放在后面安排。因此，我们令 $c = b - a$，它表示某个人的独居收益。将 $c$ 进行排序，就得到了安排的顺序。

同时，如果满足独居条件的人不足 $k$，那剩下的人也应该安排不独居。由此，我们得到了安排独居的条件：$c > 0$ 且在排序后的前 $k$ 位。

### 细节和特判

- 当 $n = 1$ 时，它只能独居，因此需要特判。
- 当 $n - 1$ 个人都安排独居，那么最后一个人也只能独居。此时我们需要比较让其独居和让其与前一个人成为邻居的收益。

## 参考代码

```cpp
#include <iostream>
#include <cctype>
#include <algorithm>
#define ll long long

using namespace std;

ll read()
{
    ll x = 0, f = 1;
    char ch = 0;
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (isdigit(ch))
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int maxN = 5e5 + 5;

ll T;
ll n, m;
ll ans;

struct node
{
    ll a, b, c;
} p[maxN];

bool cmp(node a, node b)
{
    return a.c > b.c;
}

int main()
{
    T = read();
    while (T--)
    {
        ans = 0;
        n = read(), m = read();
        for (int i = 1; i <= n; i++)
        {
            p[i].a = read(), p[i].b = read();
            p[i].c = p[i].b - p[i].a;
        }
        if (n == 1)
        {
            printf("%lld\n", p[1].b);
            continue;
        }
        sort(p + 1, p + 1 + n, cmp);
        ll now = 1;
        while (now <= m - n && now <= n && p[now].c > 0)
            ans += p[now++].b;
        if (now == n)
        {
            if (-p[now - 1].c < p[now].c)
                ans += p[now].b;
            else
                ans = ans - p[now - 1].c + p[now].a;
        }
        else
            for (int i = now; i <= n; i++)
                ans += p[i].a;
        printf("%lld\n", ans);
    }
    return 0;
}
```

---

## 作者：Vsinger_洛天依 (赞：1)

- 题意：长度为 $m$ 的序列内放入 $n$ 个数，当每个数有与之相邻的数时这个数为 $a_i$，没有相邻的数时这个数为 $b_i$，求这 $n$ 个数的最大和

- 思路：贪心，记录 $b_i-a_i$ 并从大到小排序，让 $b_i-a_i$ 大的优先独居

- 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
inline long long read(){
    long long s=0,w=1;char ch=getchar();
    while(ch<'0'||ch>'9'){ if(ch=='-') w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){ s=s*10+ch-'0';ch=getchar();}
    return s*w;
}
void read1(){
    long long a=read(),b=read(),tot=0,ans=0;
	for(int i=1;i<=a;i++){
		x[j]=read();
		y[j]=read();
		tot=tot+y[j];
	}
}
void solve(){
    if(2*a-1<=b)
			ans=tot;
		tot+=z[1];
	for(int j=2;j<=a;j++){
		tot+=z[j];
		if(b>=2*a-j){
			ans=max(ans,tot);
		}
	}
}
long long a,b,tot,ans;
long long a,x[0x66ccff]={0},y[0x66ccff]={0},z[0x66ccff]={0};
int main(){
	int n=read();
	for(int i=1;i<=n;i++){
		read1();
		for(int j=1;j<=a;j++){
			z[j]=x[j]-y[j];
		}
		sort(z+1,z+1+a,greater<int>());
		solve();
		cout<<ans<<endl;
	}
}
```

---

## 作者：minVan (赞：1)

我们假设初始时每个人都没有邻居，即总满意度为 $\sum{b_i}$，而让某个人有邻居，则增加 $a_i-b_i$，所以将所有人按 $a_i-b_i$ 从大到小排序。

若要使所有人都没邻居，需满足 $2\times n-1\le m$。

令有 $k$ 个人有邻居（$k\ge 2$），则至少需要 $2\times(n-k)+k=2\times n-k$ 栋房子，所以需要满足 $2\times n-k\le m$，此时总满意度为 $\sum\limits_{i=1}^k{a_i}+\sum\limits_{i=k+1}^n{b_i}$，可以用前缀和来处理。

**AC 代码，请勿抄袭**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 5e5 + 5;
struct node {
	int a, b;
} a[N];
int n, m, suma[N], sumb[N];
inline bool cmp(node x, node y) {
	return x.a - x.b > y.a - y.b;
}
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while(t--) {
		int ans = -1;
		cin >> n >> m;
		for(int i = 1; i <= n; i++) {
			cin >> a[i].a >> a[i].b;
		}
		sort(a + 1, a + n + 1, cmp);
		for(int i = 1; i <= n; i++) {
			suma[i] = suma[i - 1] + a[i].a;
			sumb[i] = sumb[i - 1] + a[i].b;
		}
		if(2 * n - 1 <= m) {
			ans = sumb[n];
		}
		for(int k = 2; k <= n; k++) {
			if(2 * n - k <= m) {
				if(ans < suma[k] + sumb[n] - sumb[k]) {
					ans = suma[k] + sumb[n] - sumb[k];
				}
			}
		}
		cout << ans << '\n';
	}
	return 0;
}
```

---

## 作者：skyskyCCC (赞：1)

## 前言。
赛时罚时 $2$ 次，貌似出了下标的问题。
## 分析。
本篇题解不以数组为重，以下均用变长数组为例。

如果不知道什么是变长数组，建议先[右转](https://oi-wiki.org/lang/csl/sequence-container/)了解再食用该题解。

首先我们考虑一种比较简单的情况：所有人都不是邻居，即所有人都独居，此时最终答案就是 $b_i$ 的总和。我们以此为切入点，进行进一步考虑。如果目前我们要使 $i$ 个人为邻居，那么就相当于把原先分离的这 $i$ 个人合并，此时这 $i$ 个人的满意度就是 $a_i$ 但是 $a_i$ 不保证一定大于 $b_i$ 所以如果强制某个人成为邻居，不一定是最优解。

如果我们合并房子，产生邻居，那么就相当于把他们从独居变成拼房，此时他们的满意度之差就是 $\left(b_i-a_i\right)$ 的值。我们可以先预处理出独居时的满意度之和，然后进行合并，每次取上述式子最大的 $i$ 个人变成有邻居的即可。 

找到最大满意度之差可以用排序解决。

最后考虑一下其它的情况：

以下的有人房用 $1$ 代替，无人房用 $0$ 代替。
- 能用上面的方式解决的情况时，至少应有多少房子？在人数房子正正好时，我们将有人房统一放在左边，然后隔一个空房子放一个独居的人，即 $\begin{matrix}\underbrace{111\cdots111}\\i\end{matrix} \begin{matrix}\underbrace{0101\cdots0101}\\2 \times \left(n-i\right)\end{matrix}\left(i+2 \times \left(n-i\right)= m\right)$ 的式子成立。同时若房子多则需要 $\leq m$ 的条件，然后在后边补 $0$ 即可。则至少需要 $2n-i$ 个房子，得到有解情况为 $2n-i\leq m$ 成立，所以只有这时我们才能更新答案。
- 所有人都没有邻居的情况，则反过来就行。当人数正正好时，若要使人数最少就让第一栋房子住人然后空一座房子再住人，即 $\begin{matrix}\underbrace{1010\cdots101}\\n\times2-1\end{matrix}$ 成立。即这种情况为 $2n-1\leq m$ 成立。

解释一下 $n \times 2-1$ 的原因：因为一个住房旁有一个无人房，所以 $n$ 个人住 $n\times2$ 个房，但最后一个人因为后面不会再住人，所以可以省略后面的无人房，所以总体上就是 $n \times 2-1$ 的式子。

代码如下，仅供参考：
```
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<vector>
using namespace std;
int t,n,m;
//刚才C数组貌似有什么问题，但是调不出来。
int /*c[500005],*/a[500005],b[500005];
vector<int> g;
int main(){
	cin>>t;
	while(t--){
		long long ans=0,sum=0;
		g.clear();
		cin>>n>>m;
		for (int i=1;i<=n;i++){
			cin>>a[i]>>b[i];
			sum+=b[i];
		}
		for (int i=1;i<=n;i++){
			//c[i]=a[i]-b[i];
			g.push_back(a[i]-b[i]);
		}
		sort(g.begin(),g.end());
        if(2*n-1<=m){
        	ans=sum;
        }
        sum+=g[n-1];
        //邻居起码有2个。
        for (int i=2;i<=n;i++){
            sum+=g[n-i];
            if (2*n-i<=m){
                ans=max(ans,sum);
            }
        }
        cout<<ans<<"\n";
	}
	return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：pioneer2000 (赞：0)

### 思路：
  这种考虑排布的方式，考虑使用贪心。

  首先我们可以把所有人分成两类：一类是更喜欢独居的人，而另一类是更喜欢有邻居的人。

  因为一共有 $n$ 个人和 $m$ 栋房子，所以能够独居的人数是固定的，假设一共 $k$ 个人可以独处，那么房间数就是 $(2\times k)+(n-k)=m$ ，即 $k=m-n$ ，那么可以独居的人就确定了。

  此时分类讨论，若独居人数小于 $k$ 则直接将独居的人独居，群居的人群居，否则这让独居比群居幸福度更大的人先独居，这题就算是基本解决了。

  **但是**，还需要注意的是有两种特殊情况：如果只有一个人那么只能选择独居；而如果只有一个人是群居的，就要将他独居与和最不想独居的那个人群居的幸福度作比较，得出结果。

  ### 代码：
  
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll t,n,m;
struct node{
	ll x,y,z;
}a[500005];
bool cmp(node x,node y){
	return x.z<y.z;
} 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0); 
	cin>>t;
	while(t--){
		ll ans=0;
		cin>>n>>m;
		for(int i=1;i<=n;i++){
			cin>>a[i].x>>a[i].y;
			a[i].z=a[i].x-a[i].y;
		}
		if(n==1){
			cout<<a[1].y<<'\n';
			continue;
		}
		sort(a+1,a+n+1,cmp);
		ll cnt=1;
		while(cnt<=m-n&&cnt<=n&&a[cnt].z<0){
			ans+=a[cnt++].y;
		}
		if(cnt==n){
			if(-a[cnt-1].z>a[cnt].z){
				ans+=a[cnt].y;
			}else{
				ans+=a[cnt].x+a[cnt-1].z;
			}
		}else{
			for(int i=cnt;i<=n;i++){
				ans+=a[i].x;
			}
		}
		cout<<ans<<'\n';
	}
	return 0;
}

```

---

## 作者：RAY091016 (赞：0)

### 1. 题目解释

有 $n$ 个人要住进 $m$ 栋房子里，每个人独居和有邻居的满意度分别为 $a_i$，$b_i$，求最大满意度。

### 2. 思路

先考虑每个人都有邻居时的情况，此时的满意度为 $\sum\limits_{i=1}^n b_i$。

然后我们按照 $b_i-a_i$ 的大小排序，如果一个人能够独居且 $b_i-a_i>0$，就优先让 $b_i-a_i$ 大的人独居。

而如果一个人独立出其所在群体后，所需房屋数量会加一，直到房屋数量达到 $m$，因此最多有 $m-n$ 个人能够独居。

这样做一下就可以了。

---

## 作者：ilibilib (赞：0)

### 思路：

**贪心**思想

我们先让他们都相邻地住在一起，这样一定住得下。

然后可以计算出可以腾出几间没邻居的房间。

按照**无邻居的满意度**减去**有邻居的满意度**排序，然后从大到小知道住不下或者满了就行了。

### code：

```cpp
#include<bits/stdc++.h>
#define endl putchar('\n')
using namespace std;
inline int read(){int x=0;char ch=getchar();while(ch>'9'||ch<'0')ch=getchar();while(ch<='9'&&ch>='0')x=10*x+ch-48,ch=getchar();return x;}
void write(long long x){if(x>9)write(x/10);putchar(x%10^48);return;}
struct pp{long long a, b;};
pp p[500010];
bool mcmp(const pp &a,const pp &b)
{
	return a.b-a.a>b.b-b.a;//自定义排序，无邻居的满意度减去有邻居的满意度
}
signed main()
{
	int T,n,m,x,y;
	long long ans;
	T=read();
	while(T--)
	{
		ans=0;
		n=read(),m=read();
		x=m-n,y=1;
		for(int i=1;i<=n;++i)
			p[i].a=read(),p[i].b=read(),ans+=p[i].a;
		if(n==1) {write(p[1].b);endl;continue;}//n等于1时特判
		sort(p+1,p+n+1,mcmp);
		for(y=1;y<=x&&y<=n;++y)
			if(p[y].b<p[y].a) break;
			else ans+=p[y].b-p[y].a;
			if(y==n) ans-=min(p[y-1].b-p[y-1].a,p[y].a-p[y].b);
			write(ans);
			endl;
	}
}
```

---

## 作者：违规用户名U1075140 (赞：0)



### 题意

将 $n$ 个元素放入长度为 $m$ 的空序列中，每个元素有邻元素时值为 $a_i$，没有时为 $b_i$，求全部值的最大和。

### 思路

经典贪心，首先一个没有邻元素的元素所占长度是 $2$，所以最多能放 $m-n(+1)$ 个无邻元素。直接取 $c_i=b_i-a_i$ 再根据 $c_i$ 对元素进行排序，将最大的元素依次放入空无邻位。

但这里有一点要注意，如果 $c_i\le0$ 那么要将其放在有邻位而不是无邻位，这样才能保证结果最大。




### 代码实现

```
#include<bits/stdc++.h>
#define int long long
#define mmm 0xbb2200
using namespace std;
inline long long read;
long long a,you[0xbb2200],mei[0xbb2200],cha[0xbb2200];//定义有、没邻居的满意度和差值
signed main()
{
	int n=read();
	for(int i=1;i<=n;i++)
	{
		long long a=read(),b=read(),hutaowansui=0,zuihou=0;//见变量名知成分 
		for(int j=1;j<=a;j++)
		{
			you[j]=read();
			mei[j]=read();
			hutaowansui=hutaowansui+mei[j];//存储有、没邻居的满意度和差值
		}
		for(int j=1;j<=a;j++){
			cha[j]=you[j]-mei[j];//差值 
		}
		sort(cha+1,cha+1+a,greater<int>());//排序 
		if(2*a-1<=b)
		{
			zuihou=hutaowansui;
		}
		hutaowansui+=cha[1];
		for(int j=2;j<=a;j++)
		{
			if(cha[j]>0)
			{
				hutaowansui+=cha[j];
			}
			if(b>=2*a-j)
			{
				zuihou=hutaowansui;
			}
		}//等同于取正值 
		cout<<zuihou<<endl;//输出解 
	}
}
inline long long read(){
    long long s=0,w=1;char ch=getchar();
    while(ch<'0'||ch>'9'){ if(ch=='-') w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){ s=s*10+ch-'0';ch=getchar();}
    return s*w;
}//快读 

---

## 作者：Qiu_chen (赞：0)

## 思路

这一题可以用贪心算法。

可以这么想，如果居民的 $a_i≥b_i$，则让他拥有邻居；否则，就考虑让他独居。

接着考虑 $b_i>a_i$的情况，由于独居，需要花费 $2$ 个房子的空间大小。我们要优先让 $b_i-a_i$ 大的居民去独居。

注意要考虑 $a_i≥b_i$ 的居民数量，为 $1$ 和为 $0$ 的情况。

## 代码

以下为 C++ 参考代码


```cpp
#include<bits/stdc++.h>
using namespace std;
#define pi pair <int,int>
#define int long long
#define inf 2000000009
const int maxn = 500010;
const int mod = 1e9+7;
int n, m;
int x, y;
void solve() {
	cin >> n >> m;
	int sum = 0;
	int tot = 0; 
	int tmpy, tmpx;
	vector< pi > ve;
	for (int i = 0; i < n; ++i) {
		cin >> x >> y;
		if (x >= y) {
			sum += x;
			tmpx = x;
			tmpy = y;
			++tot;
		} else {
			ve.push_back({y - x, x});
		}
	}
	sort(ve.rbegin(), ve.rend());
	int sz = ve.size(); 
	int left = (m - n); 
	int mn = min(sz, left);
	if (0) {
		printf("sum:%lld sz: %d left: %d\n", sum, sz, left);
	}
	if (tot == 1 && mn >= sz) { 
		if (sz && tmpx - tmpy > (ve[sz-1].first)) { 
			sum -= ve[sz-1].first;
		} else {
			sum = tmpy;
		}
	}
	for (int i = 0; i < mn; ++i) {
		sum += ve[i].first + ve[i].second;
	}
	for (int i = mn; i < sz; ++i) {
		sum += ve[i].second;
	}
	if (!tot && sz - mn == 1) { 
		sum += ve[mn].first;
	}
	cout << sum << endl;
} 
signed main() {
	int t = 1, cas = 1;
	scanf("%d", &t);
	while (t--) {
		if(0)  printf("case :%d\n", cas++);
		solve();
	}
	return 0;
}
//AC PLEASE
```




---

## 作者：cff_0102 (赞：0)

[题解纠错处](https://www.luogu.com.cn/paste/84w4vbc1)。

设 $c_i=b_i-a_i$ 为某个人对自己没有邻居的倾向度。要让一个人没有邻居，那么让他贴边住，至少也会浪费掉两个房子的位置，所以说要优先考虑对自己没有邻居的倾向程度更大的人，他们更需要“独居”（实际上独居不是这个意思，但是看大家都在用这个词，那我也用吧）。

将所有人按照 $c_i$ 从大到小排序，接着让前 $k$ 个人“独居”，剩下的人挨着。那么要满足 $m\ge n+k$。那么，就可以直接令 $k=m-n$，最终的答案是 $c_i$ 排名前 $k$ 的人的 $b_i$ 与剩下的人的 $a_i$ 之和。

不过，还要考虑一点，如果一个人的 $a_i\ge b_i$，那也不需要让他“独居”。所以在算 $c_i$ 的时候，还要考虑 $c_i$ 的正负性。最终答案的 $k$ 实际上应该是满足 $c_i>0$ 的 $i$ 的个数和 $m-n$ 的最小值。

---

