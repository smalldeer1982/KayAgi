# [IOI 2009] Hiring

## 题目背景

IOI2009 D1T2

## 题目描述

你需要为一个建设项目雇佣一些工人。现在有 $N$ 位候选工人，标号为 $1\sim N$。第 $k$ 个工人要求如果自己被雇佣，则必须得到至少 $S_k$ 美元的工资。每个工人有能力值 $Q_k$。建筑业监管局规定，你必须按工人们的能力值的比例分配他们的工资。例如，如果 $Q_A = 3Q_B$，则你付给 $A$ 的工资必须恰为 $B$ 的三倍。你可以付给你的工人们任意非负实数金额的工资。

你的手上有 $W$ 美元，你想用这些钱雇佣最大数量的工人。你可以决定选用哪些工人以及付给他们的工资，但必须满足每个工人的最低工资要求以及监管局的分配规定，并保证工资总额不超过 $W$。

工人们的能力值和你的项目无关，因此你只想最大化雇佣工人的数量，而不关心他们的能力值。尽管如此，你仍希望最小化你的支出，即如果存在多种方案，则你需要选择支付给工人们的工资总额最小的那一个。如果仍存在多种方案，任意一个都是满足要求的。

**任务**：编写一个程序，给定每个工人的工资要求和能力值，以及你拥有的资金，计算出具体雇佣哪些工人。你必须在最大化工人的数量的前提下最小化支出，并满足上文提到的监管局的要求。

## 说明/提示

### 样例解释

- 样例 1：选择工人 $2$ 和 $3$ 是唯一符合所有要求且雇佣了两个工人的方案。你可以分别付给他们 $80$ 美元和 $8$ 美元，满足 $100$ 美元的预算。

- 样例 2：你可以雇佣三个工人。你可以分别付给他们 $1$ 美元，$1.5$ 美元和 $1.5$ 美元。

### 数据范围与约定

对于任意测试点，如果你的方案满足了所有要求和你的目标，你将获得该测试点的满分。**否则**，如果你的第一行是正确的，即你输出了正确的工人数量 $H$，无论你接下来的输出是否符合格式，你都将获得该测试点 $50\%$ 的分数。

注意，在实际评测中，只有你的输出符合格式，才能获得测试点 $50\%$ 或 $100\%$ 的分数。

- 对于 $50\%$ 的数据，$N\leq 5000$。
- 对于 $100\%$ 的数据，$1\leq N\leq 5\times 10 ^ 5$，$1\leq S_k, Q_k\leq 2\times 10 ^ 4$，$1\leq W\leq 10 ^ {10}$。

注意，$W$ 超出了 $32$ 位整形变量的存储范围。你需要使用 $64$ 位整型变量存储 $W$，例如 C/C++ 中的 `long long` 或 Pascal 中的 `int64`。

## 样例 #1

### 输入

```
4 100
5 1000
10 100
8 10
20 1
```

### 输出

```
2
2
3
```

## 样例 #2

### 输入

```
3 4
1 2
1 3
1 3
```

### 输出

```
3
1
2
3```

# 题解

## 作者：Alex_Wei (赞：3)

> [P9113 [IOI2009] Hiring](https://www.luogu.com.cn/problem/P9113)

考虑选择一些工人后怎么分配工资。根据监管局的要求，所有人的工资 $W_i$ 和其能力值的比值 $Q_i$ 相同。设 $c = \frac {W_i} {Q_i}$，则对于任意选择的工人 $i$，$Q_ic \geq S_i$。由此可知 $c\geq \max\frac {S_i}{Q_i}$。为了让总工资最小，$c = \max \frac {S_i} {Q_i}$。我们将该比值最小的工人称为 “基准工人”。

将所有工人按 $\frac {S_i} {Q_i}$ 从大到小排序，如果我们钦定基准工人为 $i$，则只能选择编号在 $i$ 之后的工人。设选择的集合为 $T$，总工资即 $\frac {S_i\sum_{j \in T} Q_j} {Q_i}$。$S_i$ 和 $Q_i$ 都是定值，所以为了选择尽可能多的工人，按 $Q_j$ 从小到大选择。

因此，问题转化为：每次插入一个数 $Q_i$，然后查询最多选出多少个 $Q_j$，使得它们的和不超过 $\frac {WQ_i} {S_i}$。插入用线段树或树状数组维护，查询用线段树二分或树状数组二分即可。注意两个相同的 $Q_j$ 需要插入不同的位置，或者在查询时特判（因为可能没取完相同的 $Q_j$）。

输出方案也是容易的。记录 $\max |T|$ 和工资以及对应的 $i$，选择 $i\sim n$ 中 $Q_j$ 最小的 $|T|$ 个工人。

时间复杂度 $\mathcal{O}(n\log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

bool Mbe;
constexpr int N = 5e5 + 5;

ll W;
int n, b[N], buc[N];
struct worker {
  int s, q, id;
  bool operator < (const worker &z) const {
    return s * z.q > q * z.s;
  }
} w[N];

ll c[N];
int d[N];
void add(int x, int v) {
  while(x <= n) c[x] += v, d[x]++, x += x & -x;
}
pair<ll, int> query(ll lim) {
  ll sc = 0, sd = 0, p = 0;
  for(int i = 18; ~i; i--) {
    int np = p + (1 << i);
    if(np > n) continue;
    if(sc + c[np] > lim) continue;
    sc += c[p = np], sd += d[p];
  }
  return make_pair(sc, sd);
}

bool Med;
int main() {
  fprintf(stderr, "%.3lf MB\n", (&Mbe - &Med) / 1048576.0);
  #ifdef ALEX_WEI
    FILE* IN = freopen("1.in", "r", stdin); 
    FILE* OUT = freopen("1.out", "w", stdout);
  #endif
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n >> W;
  for(int i = 1; i <= n; i++) {
    cin >> w[i].s >> w[i].q, buc[w[i].q]++, w[i].id = i;
  }
  sort(w + 1, w + n + 1);
  for(int i = 1; i < N; i++) buc[i] += buc[i - 1];
  int pos = 0, ans = -1;
  ll nu, de;
  for(int i = n; i; i--) {
    int p = buc[w[i].q]--;
    add(p, w[i].q);
    auto t = query(W * w[i].q / w[i].s);
    ll sq = t.first, cnt = t.second;
    ll nu1 = w[i].s * sq, de1 = w[i].q;
    if(cnt > ans || cnt == ans && nu1 * de < nu * de1) {
      ans = cnt, pos = i, nu = nu1, de = de1;
    }
  }
  sort(w + pos, w + n + 1, [&](auto x, auto y) {
    return x.q < y.q;
  });
  cout << ans << "\n";
  for(int i = 0; i < ans; i++) cout << w[pos + i].id << "\n";
  cerr << 1e3 * clock() / CLOCKS_PER_SEC << " ms\n";
  return 0;
}
```

---

## 作者：Miss_SGT (赞：1)

令 $sum$ 为选定工人能力值的和，则工人 $i$ 可以选中当且仅当 $\frac{Q_i}{sum}\times W \ge S_i$，移项得 $\frac{W}{sum} \ge \frac{S_i}{Q_i}$。

所以当我们将工人按 $\frac{S}{Q}$ 从小到大排序后，固定 $\max \frac{S}{Q}$，可以选的工人得集合是一个前缀，且对于 $sum$ 有一个上界。枚举这个前缀，$sum$ 肯定越小越好，则一定是取前缀内 $Q$ 最小的几个，使用线段树二分就已经可以通过了。

注意到答案不大，可以双指针，需要动态维护 $Q$ 前 $ans$ 小的 $Q$ 的和。用两个堆分别维护即可。

很烦人的是，题目需要在个数最多的情况下花费最小。显然对于 $i$ 有 $W \ge \frac{S_i\times sum}{Q_i}$，所以花费为右边一坨的最大值。因为我们已经确定了可能成为答案的几个前缀，对于每个前缀 $sum$ 是固定的，而 $\frac{S}{Q}$ 的最大值一定是前缀的末尾，则直接取最小值即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
#define ll long long
int n,ans,id;
ll W,sum,sumi;
struct node{
	int x,y,i;
	inline bool operator<(node b)const{return x*b.y<b.x*y;}
}a[N];
inline bool cmp(node x,node y){return x.y<y.y;}
priority_queue<int> h1;
priority_queue<int,vector<int>,greater<int> >h2;
int main(){
	read(n),read(W);
	for(int i=1;i<=n;++i) read(a[i].x),read(a[i].y),a[i].i=i;
	sort(a+1,a+n+1);
	for(int i=1;i<=n;++i){
		if(!h1.empty()&&h1.top()>a[i].y){
			h2.push(h1.top()),sum-=h1.top(),h1.pop();
			h1.push(a[i].y),sum+=a[i].y;
		}else h2.push(a[i].y);
		if(W*a[i].y>=sum*a[i].x){
			if(sumi*a[id].x*a[i].y>sum*a[i].x*a[id].y) id=i,sumi=sum;
		}
		while(ans<i&&W*a[i].y>=(sum+h2.top())*a[i].x){
			++ans;
			id=i;
			sum+=h2.top();sumi=sum;
			h1.push(h2.top()),h2.pop();
		}
	}
	print(ans),pc('\n');
	sort(a+1,a+id+1,cmp);
	for(int i=1;i<=ans;++i) print(a[i].i),pc('\n');
	flush();
	return 0;
}
```

---

## 作者：不知名用户 (赞：1)

题意：你要招聘一些工人，工人的工资 $p_i$ 与工资比例系数（输入给出）$q_i$ 要满足 $\frac{p_i}{q_i}$ 相等。同时每个工人有最低工资限制 $s_i$（输入给出）。你有 $w$ 元，最大化工人数量同时最小化你的花费，输出招聘的工人。

如果你要招聘一些工人，花费最小肯定是满足 $\frac{s_i}{q_i}$ 最大的工人后按比例分配。把工人按照 $\frac{s_i}{q_i}$ 排序后枚举要选取的 $\frac{s_i}{q_i}$ 的工人，剩下的工人不段取 $q_i$ 小的直到没钱。可以用线段树维护 $q_i$ 的前缀和，线段树二分出结果。

```cpp
#include<bits/stdc++.h>
#define int long long
#define lf long double
using namespace std;

const int N = 5e5 + 10;

int s[N], q[N], p[N], pp[N], x[N];
int cnt[N*4], sum[N*4];
inline void upd(int p){cnt[p]=cnt[p*2]+cnt[p*2+1];sum[p]=sum[p*2]+sum[p*2+1];}

void ch(int p, int L, int R, int x, int y)
{
	if(L==R) return cnt[p]++, sum[p] += y, void();
	int mid = L + R >> 1;
	if(x<=mid) ch(p*2,L,mid,x,y);
	else ch(p*2+1,mid+1,R,x,y);
	upd(p);
}

pair<int,int>find(int p, int L, int R, int rest)
{
	if(L==R) return make_pair(0,0);
	int mid = L + R >> 1;
	if(sum[p*2]<=rest)
	{
		pair<int,int> a = find(p*2+1,mid+1,R,rest-sum[p*2]);
		a.first += cnt[p*2], a.second += sum[p*2];
		return a; 
	}
	return find(p*2,L,mid,rest);
}

signed main()
{
	int n, w, i, ans = 0, u = 0;
	lf anp = 0;
	scanf("%lld%lld", &n, &w);
	for(i=1;i<=n;i++) scanf("%lld%lld", &s[i], &q[i]);
	for(i=1;i<=n;i++) p[i] = x[i] = i;
	sort(&p[1],&p[n]+1,[](int a,int b){return q[a]<q[b];});
	for(i=1;i<=n;i++) pp[p[i]] = i;
	for(i=1;i<=n;i++) p[i] = pp[i];
	sort(&x[1],&x[n]+1,[](int a,int b){return (lf)s[a]/q[a]<(lf)s[b]/q[b];});
	for(i=1;i<=n;i++)
	{
		if(s[x[i]]<=w)
		{
			pair<int,int>a = find(1,1,n+1,(w-s[x[i]])/((lf)s[x[i]]/q[x[i]]));
			lf se = (lf)a.second * s[x[i]] / (lf)q[x[i]];
			if(a.first+1>ans||(a.first+1==ans&&se+s[x[i]]<anp)) ans = a.first + 1, anp = se + s[x[i]], u = i;
			ch(1,1,n+1,p[x[i]],q[x[i]]);
		}
	}
	printf("%lld\n", ans);
	printf("%lld", x[u]);
	sort(&x[1],&x[u-1]+1,[](int a,int b){return q[a]<q[b];});
	for(i=1;i<=ans-1;i++) printf("\n%lld", x[i]);
	return 0;
}
```

---

