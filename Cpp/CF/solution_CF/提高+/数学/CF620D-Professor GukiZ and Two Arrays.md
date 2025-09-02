# Professor GukiZ and Two Arrays

## 题目描述

Professor GukiZ has two arrays of integers, a and b. Professor wants to make the sum of the elements in the array a $ s_{a} $ as close as possible to the sum of the elements in the array b $ s_{b} $ . So he wants to minimize the value $ v=|s_{a}-s_{b}| $ .

In one operation professor can swap some element from the array a and some element from the array b. For example if the array a is $ [5,1,3,2,4] $ and the array b is $ [3,3,2] $ professor can swap the element $ 5 $ from the array a and the element $ 2 $ from the array b and get the new array a $ [2,1,3,2,4] $ and the new array b $ [3,3,5] $ .

Professor doesn't want to make more than two swaps. Find the minimal value $ v $ and some sequence of no more than two swaps that will lead to the such value $ v $ . Professor makes swaps one by one, each new swap he makes with the new arrays a and b.

## 样例 #1

### 输入

```
5
5 4 3 2 1
4
1 1 1 1
```

### 输出

```
1
2
1 1
4 2
```

## 样例 #2

### 输入

```
5
1 2 3 4 5
1
15
```

### 输出

```
0
0
```

## 样例 #3

### 输入

```
5
1 2 3 4 5
4
1 2 3 4
```

### 输出

```
1
1
3 1
```

# 题解

## 作者：Loop1st (赞：7)

### CF620D Professor GukiZ and Two Arrays
$0$ 次操作直接给两个数组求和作差去绝对值就行，$1$ 次操作我们可以暴力枚举交换 $a_i,b_j$，记原本的 $s_a=s_1,s_b=s_2$，那么 $s_a=s_1-a_i+b_i,s_b=s_2-b_i+a_i,|s_a-s_b|=|s1+2b_i-2a_i-s2|$。
两次操作我们同样可以枚举 $a$ 数组中交换过去的 $a_i,a_j$，假设 $b$ 数组换 $b_x,b_y$，则 $s_a=s_1-a_i-a_j+b_x+b_y,s_b=s_2-b_x-b_y+a_i+a_j,|s_a-s_b|=|s_1-s_2+2(b_x+b_y)-2(a_i+a_j)|$，要使 $|s_a-s_b|$ 最小，$2(b_x+b_y)$ 要最接近 $2(a_i+a_j)-(s1-s2)$，我们可以提前预处理所有 $2(b_x+b_y)$，然后找到第一个 $\ge 2(a_i+a_j)-(s1-s2)$ 的和第一个 $< 2(a_i+a_j)-(s1-s2)$ 的，和答案取 min。

时间复杂度 $O(n^2 \log n)$。

Code:
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e3 + 10;
typedef long long ll;
typedef pair<int, int> pii;
template <class T>
T cabs(T x) { return x > 0 ? x : -x; }
int n, m, tot;
ll s1, s2, ans0, a[N], b[N];
pair<ll, pii> ans1;
pair<ll, array<int, 4>> ans2;
struct Node {
    ll x;
    int u, v;
    bool operator < (const Node &A) const {
        return x < A.x;
    }
};
set<Node>st;
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%lld", &a[i]), s1 += a[i];
    scanf("%d", &m);
    for (int i = 1; i <= m; i++) scanf("%lld", &b[i]), s2 += b[i];
    ans0 = cabs(s1 - s2);
    ans1.first = 1ll << 60; ans2.first = 1ll << 60;
    for (int i = 1; i <= n; i++) 
        for (int j = 1; j <= m; j++) {
            ll p = cabs(s1 - (a[i] << 1) + (b[j] << 1) - s2);
            if (p < ans1.first) { ans1 = {p, {i, j}}; }
        }
    for (int i = 1; i <= m; i++) 
        for (int j = i + 1; j <= m; j++) 
            st.insert(Node{(b[i] + b[j]) * 2ll, i, j});
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (st.empty()) break;
            auto it = st.lower_bound({(a[i] + a[j]) * 2ll - (s1 - s2), 0, 0});
            if (it == st.end()) it--;
            if (cabs((*it).x + s1 - s2 - (a[i] + a[j]) * 2) < ans2.first) {
                ans2.first = cabs((*it).x + s1 - s2 - (a[i] + a[j]) * 2);
                ans2.second = {i, (*it).u, j, (*it).v};
            }
            if (it != st.begin()) it--;
            if (cabs((*it).x + s1 - s2 - (a[i] + a[j]) * 2) < ans2.first) {
                ans2.first = cabs((*it).x + s1 - s2 - (a[i] + a[j]) * 2);
                ans2.second = {i, (*it).u, j, (*it).v};
            }
        }
    }
    ll ans = min(ans0, min(ans1.first, ans2.first));
    printf("%lld\n", ans);
    if (ans0 == ans) {
        puts("0");
    } else if (ans1.first == ans) {
        puts("1");
        printf("%d %d\n", ans1.second.first, ans1.second.second);
    } else {
        puts("2");
        printf("%d %d\n%d %d\n", ans2.second[0], ans2.second[1], ans2.second[2], ans2.second[3]);
    }
    return 0;
}
```

---

## 作者：hxhhxh (赞：2)

## 大意

给定两个长度分别为 $n,m$ 的数组 $a,b$ ，一次操作可以选择 $a$ 数组里的一个元素和 $b$ 数组里的一个元素交换。求进行最多两次操作后最小的

$$\lvert\sum_{i=1}^n a^\prime_i-\sum_{i=1}^m b^\prime_i\rvert$$

及方案。

## 思路

记 $S_a=\sum_{i=1}^n a_i $，$ S_b = \sum_{i=1}^m b_i $（均为操作前）。

分情况讨论：

### 操作 $0$ 次

$$ans_0=\lvert S_a-S_b \rvert$$ 

### 操作 $1$ 次

$$ ans_1=\min_{i=1}^n\min_{j=1}^m\lvert S_a-2\times a_i+2\times b_j-S_b\rvert $$

这里可以直接枚举 $i,j$ 来求出答案；

### 操作 $2$ 次

首先，选的四个元素互不相同，证明如下：

设选 $a_i,a_j,b_p,b_q$。

若有一对相同，不妨设 $i=j$。

$a_i$ 与 $b_p$ 交换， $b_p$ （现在在 $a_i$ 的位置）与 $b_q$ 交换，等价 $a_i$ 与 $b_q$ 交换，在操作 $1$ 次处讨论过；

两对相同相当与对同样的两个数交换了两次，等价于没有交换，在操作 $0$ 次处讨论过，证毕。

下面仍然设交换了 $a_i,b_p$ 和 $a_j,b_q$。可以看出，答案为 $\lvert S_a-S_b+2\times(b_p+b_q-a_p-a_q)\rvert$。

首先 $O(m^2)$ 可以枚举出 $p,q$ 的选择，存入一个数组 $B$ 并按权值（$b_p+b_q$）排序。$O(n^2)$ 枚举 $i,j$，设$a_i+a_j=u$，此时我们再考察 $B$ 数组中的选择，答案是 $\min_{k} \lvert S_a-S_b+2\times(B_k-u)\rvert$，形如 $\min_k\lvert V+2B_k\rvert$。可以看出，答案只会在最接近 $-\frac{V}{2}$ 的 $B_k$ 中取到。那么我们可以在 $B$ 中二分出大于 $-\frac{V}{2}$ 但最小的元素，答案一定在它和它的前面一个元素中产生。直接更新答案即可。

## 代码

注意使用 `long long`。代码实现与上面略有不同。

```cpp
#include<bits/stdc++.h>
#define int long long
#define inf 1000000000000000
#define fi first
#define se second
using namespace std;
int n,m,a[2005],b[2005],sa,sb,ansn,anso=inf,anst=inf,cnta,cntb,ca,cb,cca,ccb,ccc,ccd;
pair<int,pair<int,int> >aa[2000006],bb[2000006];
bool fflg=false;
void ckans(int i,int j){
	if(j<=0||j>cntb) return;
	int res=abs(sa-sb-2*aa[i].fi+2*bb[j].fi);
	if(res<anst){
		anst=res;
		cca=aa[i].se.fi;
		ccc=aa[i].se.se;
		ccb=bb[j].se.fi;
		ccd=bb[j].se.se;
	}
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]),sa+=a[i];
	cin>>m;
	for(int i=1;i<=m;i++) scanf("%lld",&b[i]),sb+=b[i];
	ansn=abs(sa-sb);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(abs(sa-sb-a[i]*2+b[j]*2)<anso){
				anso=abs(sa-sb-a[i]*2+b[j]*2);
				ca=i;
				cb=j;
			}
		}
	}
	if(n>1&&m>1){
		for(int i=1;i<=n;i++) for(int j=i+1;j<=n;j++) aa[++cnta]={a[i]+a[j],{i,j}};
		for(int i=1;i<=m;i++) for(int j=i+1;j<=m;j++) bb[++cntb]={b[i]+b[j],{i,j}};
		sort(bb+1,bb+cntb+1);
		for(int i=1;i<=cnta;i++){
			int l=1,r=cntb,mid;
			while(l<r){
				mid=l+r>>1;
				if(bb[mid].fi*2+sa-sb-2*aa[i].fi<0) l=mid+1;
				else r=mid;
			}
			mid=l+r>>1;
			ckans(i,mid);
			ckans(i,mid-1);
		}
	}
	int ans=min(anso,min(ansn,anst));
	if(ansn==ans) printf("%lld\n0",ansn);
	else if(anso==ans) printf("%lld\n1\n%lld %lld",anso,ca,cb);
	else if(anst==ans) printf("%lld\n2\n%lld %lld\n%lld %lld",anst,cca,ccb,ccc,ccd);
}
```

---

## 作者：smoothset (赞：2)

[欢迎来看我的博客](https://blog.csdn.net/qq_43537070/article/details/107590705)
#### 思路
因为这个交换次数很少，只有$2$，以及这个$n$的值同样很小，只有$2000$，所以我们将这个问题拆开来看：

1.考虑不交换，直接输入的时候累加一个$suma$和$sumb$，然后做一个减法，$fabs$一下即可。

2.考虑只交换一次的情况，我们直接$n^2$暴力枚举$a_i$，$b_j$即可。

3.考虑交换两次的情况，我们可以用$n^2$的暴力枚举出来在$a$数组中任取两位所有的值，$b$数组同理，然后再用一个双指针更新答案即可。

#### 代码
具体实现见代码
~~~cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cctype>
#include <algorithm>
#include <vector>
namespace OI
{
    #define pk putchar(' ')
    #define ph puts("")
    #define fi first
    #define se second
    template<class T>
    T Fabs(T x)
    {
        return x < 0 ? -x : x;
    }
    template<class T>
    void rd(T &x)
    {
        x = 0;
        int f = 1;
        char c;
        while (!isdigit(c = getchar())) if (c == '-') f = -1;
        do
        {
            x = (x << 3) + (x << 1) + (c ^ 48);
        } while (isdigit(c = getchar()));
        x *= f;
    }
    template<class T>
    void pt(T x)
    {
        if (x < 0)
            putchar('-'), x = -x;
        if (x > 9)
            pt(x / 10);
        putchar(x % 10 ^ 48);
    }
}
using namespace OI;
using namespace std;
typedef long long ll;
const int N = 2005;
int n, m, a[N], b[N], kind;
ll sa, sb;
vector<pair<int, pair<int, int> > > suma, sumb;
pair<int, int> ans[2];
int main()
{
    rd(n);
    for (int i = 1; i <= n; i++)
        rd(a[i]), sa += a[i];
    rd(m);
    for (int i = 1; i <= m; i++)
        rd(b[i]), sb += b[i];
    for (int i = 1; i < n; i++)
        for (int j = i + 1; j <= n; j++)
            suma.push_back({a[i] + a[j], {i, j}});
    for (int i = 1; i < m; i++)
        for (int j = i + 1; j <= m; j++)
            sumb.push_back({b[i] + b[j], {i, j}});
    sort(suma.begin(), suma.end());
    sort(sumb.begin(), sumb.end());
    ll minx = Fabs(sa - sb);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            ll tmp = Fabs(sa - sb + 2ll * b[j] - 2ll * a[i]);
            if (tmp < minx)
            {
                minx = tmp;
                kind = 1;
                ans[0] = {i, j};
            }
        }
    for (int i = 0, j = 0; i < (int)suma.size() && j < (int)sumb.size();)
    {
        ll tmp = (sa - sb + 2ll * sumb[j].fi - 2ll * suma[i].fi);
        if (Fabs(tmp) < minx)
        {
            minx = Fabs(tmp);
            kind = 2;
            ans[0] = {suma[i].se.fi, sumb[j].se.fi};
            ans[1] = {suma[i].se.se, sumb[j].se.se};
        }
        if (tmp > 0)
            i++;
        else
            j++;
    }
    pt(minx), ph, pt(kind), ph;
    for (int i = 0; i < kind; i++)
        pt(ans[i].fi), pk, pt(ans[i].se), ph;
    return 0;
}
~~~
#### 谢谢

---

## 作者：wizardMarshall (赞：1)

## 题意

最多交换 $a$ 序列与 $b$ 序列中的两个数，要求最终两序列和的绝对值最小。

## 思路

对于操作数 $k=0$ 的时候直接计算即可，答案为 $|s_a-s_b|$（$s$ 表示序列的和）。

$k=1$ 的时候可以枚举 $a$ 与 $b$ 中要交换哪两个数，答案变为 $|(s_a-a+b)-(s_b-b+a)|=|s_a-s_b-2a+2b|$（$a$ 与 $b$ 即为交换的两个数）。

$k=2$ 的时候，式子变为 $|(s_a-a_1-a_2+b_1+b_2)-(s_b-b_1-b_2+a_1+a_2)|=|s_a-s_b-2a_1-2a_2+2b_1+2b_2|$（同样的，$a_1$ 与 $a_2$ 等表示交换的数，下标是为了**表区分**，并不是**真正的下标**）。

我们可以考虑只枚举 $a_1$ 与 $a_2$，这样式子中 $s_1-s_2-2a_1-2a_2$ 的部分就变成了定值，考虑剩余 $2b_1+2b_2$ 即可。

容易发现我们要让 $2b_1+2b_2$ 尽量与 $-(s_1-s_2-2a_1-2a_2)$ 接近，这样计算的答案才能更接近 $0$。而 $2b_1+2b_2$ 所有的值都是可以预处理得到的。

于是预处理出所有 $2b_1+2b_2$，丢进一个数组里并排序，这样每次二分就可以做到 $O(n^2\log n)$ 的复杂度。

这里尽量用数组而不用 set 等自带大常数的工具，同时预处理的时候也要注意 $b_1$ 与 $b_2$ 的**下标不同**。

## 代码

```
#include <bits/stdc++.h>
using namespace std;
#define int long long 
int a[2005], b[2005];
int len;
pair <int, int> ans[5];
pair <int, pair <int, int> > st[4000005];
signed main() {
	srand(time(NULL));
	int n, m;
	
	cin >>n;
	int s1 = 0;
	for (int i=  1; i <= n; i++) {
		scanf("%lld", &a[i]);
		s1 += a[i];
	}
	cin >>m;
	int s2 = 0;
	for (int i =1; i <= m; i++) {
		scanf("%lld", &b[i]);
		s2 += b[i];
	}
	len = 0;
	int res = abs(s1 - s2);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (abs(s1 - s2 - 2 * a[i] + 2 * b[j]) < res) {
				res = abs(s1 - s2 - 2 * a[i] + 2 * b[j]);
				len = 1;
				ans[1] = {i, j};
			}
		}
	}
	int E = 0;
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= m; j++) {
			if (i == j)continue;
			st[++E] = {2ll * b[i] + 2ll * b[j], {i, j}};
		}
	}
	sort(st + 1, st + E + 1);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (i == j)continue;
			int v = s1 - s2 - 2 * a[i] - 2 * a[j];
			int l = 1, r = E, temp = E + 1;
			while (l <= r) {
				int mid = (l + r) / 2;
				if (st[mid].first >= -v) {
					temp = mid;
					r = mid - 1;
				}else {
					l = mid + 1;
				}
			}
			if (temp != E + 1) {
				if (abs(v + st[temp].first) < res) {
					res = abs(v + st[temp].first);
					len = 2;
					ans[1] = {i, st[temp].second.first};
					ans[2] = {j, st[temp].second.second};
				}
			}
			if (temp != 1) {
				temp--;
				if (abs(v + st[temp].first) < res) {
					res = abs(v + st[temp].first);
					len = 2;
					ans[1] = {i, st[temp].second.first};
					ans[2] = {j, st[temp].second.second};
				}
			}
		}
	}cout << res << endl << len <<endl;
	for (int i = 1; i <= len; i++) {
		cout << ans[i].first << " " << ans[i].second << "\n";
	}
	return 0;
}
```

---

## 作者：Crazyouth (赞：0)

## 分析

注意到最多只能进行 $2$ 次操作，我们分类讨论：

- $0$ 次操作。此时答案为两数组和的差的绝对值。
- $1$ 次操作。此时枚举两数组交换的位置算一下即可。
- $2$ 次操作。设交换的数对分别为 $(a_i,b_x)$，$(a_j,b_y)$，$a$ 数组的和为 $s_1$，$b$ 数组的和为 $s_2$，则交换后两数组差为 $s_1-s_2-2\times(a_i+a_j)+2\times(b_x+b_y)$，不难发现我们需要的是找到两组 $b_x,b_y$ 分别使 $2\times(b_x+b_y)$ 刚好大于等于和刚好小于前面那一堆式子，所以可以预处理并二分。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int a[2010],b[2010],s1,s2;
struct node
{
	int val,p1,p2;
	bool operator<(const node x)const
	{
		if(val!=x.val)
		return val<x.val;
		else return p1<x.p1;
	}
}sum[4000010];
signed main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],s1+=a[i];
	int m;
	cin>>m;
	for(int i=1;i<=m;i++) cin>>b[i],s2+=b[i];
	int ans1=abs(s1-s2),ans2=1e18,ans3=1e18;
	int pos2a,pos2b;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	{
		if(abs(s1-s2-2*a[i]+2*b[j])<ans2)
		{
			ans2=abs(s1-s2-2*a[i]+2*b[j]);
			pos2a=i;
			pos2b=j;
		}
	}
	int cnt=0;
	if(min(n,m)==1) goto E;
	for(int i=1;i<=m;i++)
	for(int j=i+1;j<=m;j++) sum[++cnt]={2*(b[i]+b[j]),i,j};
	sort(sum+1,sum+cnt+1,[](node x,node y){return x.val<y.val;});
	int pos3a1,pos3a2,pos3b1,pos3b2;
	for(int i=1;i<=n;i++)
	for(int j=i+1;j<=n;j++)
	{
		int now=2*(a[i]+a[j])+s2-s1;
		auto nowb=lower_bound(sum+1,sum+cnt+1,(node){now,0,0});
		if(nowb==sum+cnt+1) goto F;
		if(abs(nowb->val-now)<ans3)
		{
			ans3=abs(nowb->val-now);
			pos3a1=i;
			pos3a2=j;
			pos3b1=nowb->p1;
			pos3b2=nowb->p2;
		}
		F:;
		nowb=(lower_bound(sum+1,sum+cnt+1,(node){now,0,0})-1);
		if(abs(nowb->val-now)<ans3)
		{
			ans3=abs(nowb->val-now);
			pos3a1=i;
			pos3a2=j;
			pos3b1=nowb->p1;
			pos3b2=nowb->p2;
		}
	}
	E:;
	if(ans1==min({ans1,ans2,ans3}))
	{
		cout<<ans1<<"\n0";
	}
	else if(ans2==min({ans1,ans2,ans3}))
	{
		cout<<ans2<<"\n1\n"<<pos2a<<' '<<pos2b;
	}
	else
	{
		cout<<ans3<<"\n2\n"<<pos3a1<<' '<<pos3b1<<'\n'<<pos3a2<<' '<<pos3b2;
	}
}

---

## 作者：mango2011 (赞：0)

观察发现题目中的 $n\le2000$，而最多操作两次，说明我们的解法的时间复杂度应该在 $O(n^2)$ 左右。

我们考虑怎样的交换可能会得到正确答案：

1) 不交换，这一类情形是平凡的。

2) 交换一次，这一种情形下我们枚举 $i(1\le i\le n),j(1\le j\le m)$，尝试交换
$a_i,b_j$ 即可，复杂度 $O(n^2)$。

3) 交换两次，这一种情形比较难以处理，下文终点描述这一情形。

如果设 $e_1,e_2$ 是从 $a$ 到 $b$ 的；$f_1,f_2$ 是从 $b$ 到 $a$ 的，则显然存在一种最优方案使得 $e_1,e_2,f_1,f_2$ 互不相同。由于在同一个序列中处理问题更方便，所以我们可以考虑枚举序列 $a$（其实 $b$ 也可以，不过笔者习惯分析 $a$）中需要向 $b$ 交换的两个位置 $p_1,p_2(1\le p_1<p_2\le n)$。

令 $s_1=a_{p_1}+a_{p_2}$，同时令 $b$ 中交换到 $a$ 的元素和为 $s_2$，$x=\sum a_i,y=\sum b_i$。则操作过后 $x_0$ 变成 $x+s_2-s_1$；$y_0$ 变成 $x+s_1-s_2$，拆绝对值：

1) 若 $x_0\ge y_0$，即 $x+s_2-s_1\ge y+s_1-s_2$，移项得到 $2s_2\ge y-x+2s_1$，于是预处理出所有可能的 $s_2$ 并排序就可以用二分做到总复杂度 $O(n^2\log n)$。

2) 若 $x_0\le y_0$，类似上面发现 $2s_2\le y-x+2s_1$，同样可以预处理并排序后通过二分解决。

至于输出方案，只需要在更新答案的时候记录一下即可。

于是我们就做完了这一道题目，总复杂度 $O(n^2\log n)$，可以通过。

[评测链接](https://codeforces.com/contest/620/submission/272935110)

---

## 作者：ademik (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF620D)

>  给定 长度为 $n$ 的序列 $A$， 长度为 $m$ 的序列 $B$， 设定一个序列的权值 $f(X) = \sum_{i = 1}^{k}X_i$。 你可以进行最多两次操作， 每次操作交换 $A$ 和 $B$ 中的任意两个元素，最小化 $|f(A) - f(B)|$。

记初始情况 $f(A) = A, f(B) = B$。
考虑进行一次操作，枚举我们要交换序列 $A$ 中的元素 $x$，要交换 $B$ 中的元素 $y$，那么此时所得的结果为 $|A - B - 2 \times (x - y)|$。我们想让该式子经可能得接近 $0$，即 $A - B - 2 \times (x - y) = 0$，$2 \times y = A - B - 2 \times x$，也就是说，当 $x$ 确定时 $y$ 越接近 这个值越优。

我们考虑将序列 $B$ 预先排序，这样可以通过二分 $\log m$ 内得到 $y$。

再考虑进行两次操作的情况，我们可以直接将 $A, B$ 中的元素两两组成一对，表示同时这两个元素同时和另一个序列中的两个元素交换，这样就可以仿照上述做法解题。 

时间复杂度为 $O(n^2 \log m^2) = O(n^2 \log m)$

```cpp
# include <bits/stdc++.h>
# define TIME 1e3 * clock() / CLOCKS_PER_SEC
using namespace std;
typedef long long i64;
typedef pair < int, int > pii; 
const int N = 2005; 
i64 n, m, a[N], b[N];
i64 mark[4], id; 
i64 A, B, ans;
void get_ans(int typ)
{
	if(typ == 1) { 
		for(int i = 1; i <= n; i ++) {
			for(int j = 1; j <= m; j ++) {
				i64 x = A - a[i] + b[j], y = B - b[j] + a[i]; 
				if(ans > abs(x - y)) {
					ans = abs(x - y); 
					mark[0] = i; mark[1] = j;
					id = 1;  
				}
			}
		}
	} else {
		vector < pair < i64, pii > > vec; 
		for(int i = 1; i <= n; i ++) {
			for(int j = 1; j < i; j ++) {
				vec.push_back(make_pair(2 * a[i] + 2 * a[j], make_pair(i, j))); 
			}
		}
		sort(vec.begin(), vec.end()); 
		for(int i = 1; i <= m; i ++) {
			for(int j = 1; j < i; j ++) {
				i64 now = A - B + 2 * b[i] + 2 * b[j]; 
				int pos = lower_bound(vec.begin(), vec.end(), make_pair(now, make_pair(0, 0))) - vec.begin();
				if(pos < vec.size()) {
					pair < i64, pii > x = vec[pos]; 
					if(ans > abs(x.first - now)) {
						ans = abs(x.first - now); 
						mark[0] = x.second.first; mark[1] = i; 
						mark[2] = x.second.second; mark[3] = j; 
						id = 2; 
					}
				}
				if(pos > 0) {
					pos --; pair < i64, pii > x = vec[pos]; 
					if(ans > abs(x.first - now)) {
						ans = abs(x.first - now); 
						mark[0] = x.second.first; mark[1] = i; 
						mark[2] = x.second.second; mark[3] = j;
						id = 2;  
					}
				}
			}
		}
	}
}
int main()
{
	ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0); 
	cin >>n; for(int i = 1; i <= n; i ++) cin >>a[i], A += a[i]; 
	cin >>m; for(int i = 1; i <= m; i ++) cin >>b[i], B += b[i];
	ans = abs(A - B); 
	get_ans(1); get_ans(2); 
	cout <<ans <<endl; 
	cout <<id <<endl; 
	for(int i = 0; i <= id * 2 - 1; i ++) {
		cout <<mark[i] <<(i & 1 ? "\n" : " "); 
	}	
	return 0; 
	
}
``` 

---

## 作者：我梦见一片焦土 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF620D)

------------
# 思路：
由于 $k \leq 2$，那么可以分类讨论，$0$ 可以直接算，$1$ 可以暴力枚举。

对于 $2$，我们可以把两个绑在一起交换，可以预处理出 $B$ 所有的组合，枚举 $A$，可以 ```lower_bound``` 找出对他最优的 $B$（前后都考虑），设 $A$ 和 $B$ 的差值为 $x$，$A$ 的枚举值为 $y$，那么找的值应该是最接近 $t - x \div 2$ 的。

代码：
```cpp
#include <cstdio>
#include <algorithm>
#include <set>
using namespace std;
#define int long long
const int M = 2005;
int read()
{
	int x=0,f=1;char c;
	while((c=getchar())<'0' || c>'9') {if(c=='-') f=-1;}
	while(c>='0' && c<='9') {x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
int n,m,sa,sb,ans,tp,c[4],a[M],b[M];
struct node
{
	int v,x,y;
	bool operator < (const node &b) const
	{
		if(v==b.v && x==b.x) return y<b.y;
		if(v==b.v) return x<b.x;
		return v<b.v;
	}
};set<node> s;
int Abs(int x)
{
	return x>0?x:-x;
}
signed main()
{
	n=read();
	for(int i=1;i<=n;i++)
	{
		a[i]=read();
		sa+=a[i];
	}
	m=read();
	for(int i=1;i<=m;i++)
	{
		b[i]=read();
		sb+=b[i];
	}
	ans=Abs(sa-sb);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			sa+=(b[j]-a[i]);
			sb+=(a[i]-b[j]);
			if(Abs(sa-sb)<ans)
			{
				ans=Abs(sa-sb);
				tp=1;c[0]=i;c[1]=j;
			}
			sa-=(b[j]-a[i]);
			sb-=(a[i]-b[j]);
		}
	for(int i=1;i<=m;i++)
		for(int j=i+1;j<=m;j++)
			s.insert(node{b[i]+b[j],i,j});
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
		{
			if(s.empty()) continue;
			int x=sa-sb,y=a[i]+a[j];
			set<node>::iterator it=s.lower_bound(node{y-x/2,0,0});
			if(it==s.end()) it--;
			int t=Abs(sa+2*((*it).v)-sb-2*y);
			if(t<ans)
			{
				ans=t;tp=2;
				c[0]=i;c[1]=(*it).x;
				c[2]=j;c[3]=(*it).y;
			}
			if(it!=s.begin()) it--;
			t=Abs(sa+2*((*it).v)-sb-2*y);
			if(t<ans)
			{
				ans=t;tp=2;
				c[0]=i;c[1]=(*it).x;
				c[2]=j;c[3]=(*it).y;
			}
		}
	printf("%lld\n%lld\n",ans,tp);
	if(tp==1) printf("%lld %lld\n",c[0],c[1]);
	if(tp==2) printf("%lld %lld\n%lld %lld\n",c[0],c[1],c[2],c[3]);
}
```

---

## 作者：Create_Random (赞：0)

[D. Professor GukiZ and Two Arrays](https://codeforces.ml/problemset/problem/620/D)

解法：

交换次数最大只有 $2$ 次，所以我们可以进行分类讨论：

1. 无论怎样交换都无法改变两个序列

2. 交换一次后即可将差值最小

3. 交换两次后使得差值最小

对于第 $1$ 、第 $2$ 种情况，我们可以枚举每个数，

使其在求和后的差值小于最初求和后的差值时即更新，

同时统计交换的点。

如果没有交换过一次即为第 $1$ 种情况，

否则就将其最优解存储，与交换两次的最优解比较取更优解。

对于第 $3$ 种情况，我们不能简单贪心直接进行两次交换，

而是将这两个序列中的每两个数进行捆绑后交换，

因为两个序列每个最多只有 $4\times 10^6$ 个数字，

所以就可以将两个序列变成有序的，

随后二分找到交换两个序列求和后的最小差值即可。

时间复杂度 $O(n^2 \log (n^2))$ .

~~复杂度相对其他题解略高但依然可过~~

$Code$:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
long long a[2010],b[2010],aa[2010],bb[2010];
long long sum1,sum2;
long long ans;
long long l[5],r[5];
int le,re;
int l1,r1,l2,r2;
long long cnt,cnt2;
struct node
{
	int l,r;
	long long v;
}aaa[4000010],bbb[4000010];
bool flag;
bool cmp(node a,node b)
{
	return a.v<b.v;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		aa[i]=a[i];
		sum1+=a[i];
	}
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%lld",&b[i]);
		bb[i]=b[i];
		sum2+=b[i];
	}
	long long cnt=abs(sum1-sum2);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(abs(abs(sum1-a[i]+b[j])-abs(sum2-b[j]+a[i]))<cnt)
			{
				cnt=abs(abs(sum1-a[i]+b[j])-abs(sum2-b[j]+a[i]));
				flag=1;
				le=i;
				re=j;
			}
		}
	}
	if(flag==0)
	{
		printf("%lld\n",cnt);
		printf("0");
		return 0;
	}
	swap(a[le],b[re]);
	sum1=sum2=0;
	for(int i=1;i<=n;i++)
	{
		sum1+=a[i];
	}
	for(int i=1;i<=m;i++)
	{
		sum2+=b[i];
	}
	cnt=abs(sum1-sum2);
	sum1=sum2=0;
	for(int i=1;i<=n;i++)
	{
		sum1+=aa[i];
	}
	for(int i=1;i<=m;i++)
	{
		sum2+=bb[i];
	}
	cnt2=abs(sum1-sum2);
	int x=0,y=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=i+1;j<=n;j++)
		{
			aaa[++x].v=aa[i]+aa[j];
			aaa[x].l=i;
			aaa[x].r=j;
		}
	}
	for(int i=1;i<=m;i++)
	{
		for(int j=i+1;j<=m;j++)
		{
			bbb[++y].v=bb[i]+bb[j];
			bbb[y].l=i;
			bbb[y].r=j;
		}
	}
	sort(aaa+1,aaa+x+1,cmp);
	sort(bbb+1,bbb+y+1,cmp);
	for(int i=1;i<=x;i++)
	{
		int l=1,r=y;
		while(l<=r)
		{
			int mid=(l+r)/2;
			if((sum1-aaa[i].v+bbb[mid].v)-(sum2-bbb[mid].v+aaa[i].v)==0)
			{
				printf("0\n");
				printf("2\n");
				printf("%d %d\n",aaa[i].l,bbb[mid].l);
				printf("%d %d\n",aaa[i].r,bbb[mid].r);
				return 0;
			}
			else if((sum1-aaa[i].v+bbb[mid].v)-(sum2-bbb[mid].v+aaa[i].v)<0)
			{
				if(abs((sum1-aaa[i].v+bbb[mid].v)-(sum2-bbb[mid].v+aaa[i].v))<cnt2)
				{
					cnt2=abs((sum1-aaa[i].v+bbb[mid].v)-(sum2-bbb[mid].v+aaa[i].v));
					l1=aaa[i].l;
					r1=bbb[mid].l;
					l2=aaa[i].r;
					r2=bbb[mid].r;
				}
				l=mid+1;
			}
			else
			{
				if(abs((sum1-aaa[i].v+bbb[mid].v)-(sum2-bbb[mid].v+aaa[i].v))<cnt2)
				{
					cnt2=abs((sum1-aaa[i].v+bbb[mid].v)-(sum2-bbb[mid].v+aaa[i].v));
					l1=aaa[i].l;
					r1=bbb[mid].l;
					l2=aaa[i].r;
					r2=bbb[mid].r;
				}
				r=mid-1;
			}
		}
	}
	if(cnt<=cnt2)
	{
		printf("%lld\n",cnt);
		printf("1\n");
		printf("%d %d",le,re);
	}
	else
	{
		printf("%lld\n",cnt2);
		printf("2\n");
		printf("%d %d\n",l1,r1);
		printf("%d %d\n",l2,r2);
	}
	return 0;
}
```


---

## 作者：Mihari (赞：0)

# 题目

[传送门](https://www.luogu.com.cn/problem/CF620D)

# 题解

对于**不交换**和**只交换一次**这两种情况，我们都可以直接暴力做，前者 $\mathcal O(n)$ 输入时预处理，后者直接 $\mathcal O(nm)$ 暴力扫即可。

对于交换两次，我们可以将数组中任意两个数绑在一起，分别组成 $\frac{n^2}{2}$ 的数组和 $\frac{m^2}{2}$ 的数组，然后在这两个数组中，将任意一个排序，在另一个中枚举一个 $x$，在有序数组中二分寻找与 $x$ 最接近的数，然后与答案进行比较即可。

# 代码

```cpp
https://www.cnblogs.com/Arextre/p/13379675.html
```


---

