# [COTS 2018] 题日 Zapatak

## 题目背景


译自 [Izborne Pripreme 2018 (Croatian IOI/CEOI Team Selection)](https://hsin.hr/pripreme2018/) D1T2。$\texttt{1s,1G}$。

关于题目名：原文如此（「题目」的克罗地亚语是「zadatak」）。

## 题目描述


定义长度均为 $k$ 的数列 $[a_1,a_2,\ldots,a_k]$ 和 $[b_1,b_2,\ldots,b_k]$ **几乎相等**，当且仅当存在**恰好一个** $1\le p\le k$，使得 $a_p\neq b_p$。

定义长度均为 $k$ 的数列 $[a_1,a_2,\ldots,a_k]$ 和 $[b_1,b_2,\ldots,b_k]$ **相似**，当且仅当可以通过重排使得 $a,b$ **几乎相等**。

给定长度为 $n$ 的数列 $[a_1,a_2,\ldots,a_n]$。$m$ 次询问，每次询问给定 $l_1,r_1,l_2,r_2$，问 $[a_{l_1},a_{{l_1}+1},\ldots,a_{r_1}]$ 与 $[a_{l_2},a_{{l_2}+1},\ldots,a_{r_2}]$ 是否相似。

## 说明/提示



对于 $100\%$ 的数据，保证：

- $1\le n,m\le 10^5$；
- $0\le a_i\le 10^9$；
- $1\le l_1\le r_1\le n$，$1\le l_2\le r_2\le n$；
- $r_1-l_1=r_2-l_2$。


| 子任务编号 | $n\le $ |  $m\le $ | $a_i\le$   | 得分 |  
| :--: | :--: | :--: | :--: |  :--: |    
| $ 1 $    | $ 1\, 000 $    |  $1\, 000$ | $ 10^9$ | $ 10 $   |  
| $ 2 $    | $ 5\times 10^4 $   |  $5\times 10^4$ | $30$ | $ 15 $   |  
| $ 3 $    | $ 10^5$ | $10^4$ | $10^9$  | $ 30 $   |  
| $ 4 $    | $ 10^5$ | $10^5$ | $10^9$ | $  45 $   |    


## 样例 #1

### 输入

```
6 4
1 3 2 3 1 2
1 1 2 2
2 3 3 4
2 3 4 5
1 3 2 4```

### 输出

```
DA
NE
DA
DA```

## 样例 #2

### 输入

```
10 5
3 3 3 1 2 2 1 2 2 1
2 3 5 6
9 10 5 6
5 6 4 5
5 8 3 6
3 7 5 9```

### 输出

```
NE
DA
DA
DA
NE```

# 题解

## 作者：xfrvq (赞：15)

简单哈希。

考虑给定一对**相似**的序列 $a_n,b_n$，我们如何找出不同的唯一一对 $a_x,b_y$。

注意到 $\sum\limits_{i=1}^n a_i-\sum\limits_{i=1}^n b_i=a_x-b_y$。

同理可构造 $\sum\limits_{i=1}^n {a_i}^2-\sum\limits_{i=1}^n {b_i}^2={a_x}^2-{b_y}^2$。

根据**平方差公式**，后式除以前式可得 $a_x+b_y$ 的值。$a_x,b_y$ 也就都可以解出来了。

解出来后，验证两个序列**分别除去 $a_x,b_y$ 后是否本质相同**。采用 random hashing，即为每个数赋一个随机权，两序列本质相同**仅当其随机权和相等**。

区间和，区间平方和都可以前缀和维护。

```cpp
#include<bits/stdc++.h>
using namespace std;

using ll = long long;
using LL = __int128;

const int N = 1e5 + 5;

int n,m,a[N],b[N];
LL s1[N],s2[N];
ll h[N];
map<int,ll> H;
mt19937 rnd(20081229);

int main(){
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;++i){
		scanf("%d",a + i);
		s1[i] = s1[i - 1] + a[i];
		s2[i] = s2[i - 1] + LL(a[i]) * a[i];
		if(!H[a[i]]) H[a[i]] = rnd();
		h[i] = h[i - 1] + H[a[i]];
	}
	for(int l1,r1,l2,r2;m--;){
		scanf("%d%d%d%d",&l1,&r1,&l2,&r2);
		LL v1 = s1[r1] - s1[l1 - 1] - s1[r2] + s1[l2 - 1];
		LL v2 = s2[r1] - s2[l1 - 1] - s2[r2] + s2[l2 - 1];
		if(v1 == 0 || v2 % v1){ puts("NE"); continue; }
		v2 /= v1;
		ll a = (v1 + v2) / 2,b = (v2 - v1) / 2;
		ll h1 = h[r1] - h[l1 - 1],h2 = h[r2] - h[l2 - 1];
		puts(h1 - H[a] == h2 - H[b] ? "DA" : "NE");
	}
	return 0;
}
```

---

## 作者：ccxswl (赞：4)

哈希好题。

---

## 题意

给定一个序列，每次询问给定两个长度相等的区间，问这两个区间是否只有一个数不一样。

## 思路

发现我们要求的信息只与数的出现次数有关，自然想到桶。那么如果有两个区间合法，那这两个区间的桶只有两个位置不同且桶内的值均相差 $1$。

维护每个区间的桶不太能直接做，且信息明显可差分，直接套一个主席树。

在树上二分找不同的位置进行判断即可。

如果当前区间完全相等那么不满足条件，左右都不相等的情况只能出现一次不然不合法，左右只有一个不相等递归那边不相等的即可。

## 代码

我的实现需要注意的细节还是挺多的。

复杂度 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ubt = unsigned long long;

const int maxN = 1e5 + 7;

int n, m, Q;
int sor[maxN];
int a[maxN], T[maxN];

const ubt Base = 13331;
ubt B[maxN];

int top[maxN], tot;
struct dat {
  int l, r;
  int len;
  ubt H;
} t[maxN * 20];
void upd(int p) {
  t[p].H = B[t[t[p].l].len] * t[t[p].r].H + t[t[p].l].H;
}
void build(int l, int r, int &p) {
  p = ++tot;
  t[p].len = r - l + 1;
  if (l == r) return;
  int mid = (l + r) >> 1;
  build(l, mid, t[p].l);
  build(mid + 1, r, t[p].r);
  upd(p);
}
void insert(int &p, int w, int K, int l, int r) {
  p = ++tot;
  t[p] = t[w];
  if (l == r) {
    t[p].H = T[K];
    return;
  }
  int mid = (l + r) >> 1;
  if (K <= mid) insert(t[p].l, t[w].l, K, l, mid);
  else insert(t[p].r, t[w].r, K, mid + 1, r);
  upd(p);
}

ubt get(int l, int r) {
  return t[r].H - t[l].H;
}
bool Flag;
bool check(int x0, int y0, int x1, int y1, int l, int r) {
  auto t0 = get(x0, y0), t1 = get(x1, y1);
  if (t0 == t1) return false;
  if (l == r) {
    auto res = abs((int)t0 - (int)t1) == 1;
    return res;
  }
  auto L = get(t[x0].l, t[y0].l) != get(t[x1].l, t[y1].l);
  auto R = get(t[x0].r, t[y0].r) != get(t[x1].r, t[y1].r);
  int mid = (l + r) >> 1;
  if (L && R) {
    if (Flag) return false;
    Flag = true;
    return check(t[x0].r, t[y0].r, t[x1].r, t[y1].r, mid + 1, r)
      && check(t[x0].l, t[y0].l, t[x1].l, t[y1].l, l, mid);
  }
  return R ? check(t[x0].r, t[y0].r, t[x1].r, t[y1].r, mid + 1, r)
    : check(t[x0].l, t[y0].l, t[x1].l, t[y1].l, l, mid);
}

int main() {
  ios::sync_with_stdio(false), cin.tie(nullptr);

  cin >> n >> Q;
  for (int i = 1; i <= n; i++)
    cin >> a[i];

  for (int i = 1; i <= n; i++)
    sor[i] = a[i];
  sort(sor + 1, sor + n + 1);
  m = unique(sor + 1, sor + n + 1) - sor - 1;
  for (int i = 1; i <= n; i++)
    a[i] = lower_bound(sor + 1, sor + m + 1, a[i]) - sor;

  B[0] = 1;
  for (int i = 1; i <= m; i++) 
    B[i] = B[i - 1] * Base;

  build(1, m, top[0]);
  for (int i = 1; i <= n; i++) {
    T[a[i]]++;
    insert(top[i], top[i - 1], a[i], 1, m);
  }

  while (Q--) {
    int l, r, a, b;
    cin >> l >> r >> a >> b;
    Flag = false;
    bool res = check(top[l - 1], top[r], top[a - 1], top[b], 1, m);
    puts(res ? "DA" : "NE");
  }
}

```

---

## 作者：_Ch1F4N_ (赞：4)

非常好的哈希题。

考虑随机 $100$ 次，每次给每个数附上 $0$ 或者 $1$ 的随机权值，然后考察两个区间的哈希值（区间内数的权值和）差的绝对值，如果这 $100$ 次中两个区间的哈希值差的绝对值只出现了 $1$ 和 $0$ 并且一定出现了 $1$ 就认为其合法。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+114;
int answer[maxn],l[maxn][2],r[maxn][2];
int ans[maxn];
int pre[maxn];
int a[maxn],b[maxn],n,m;
int w[maxn];
mt19937 rd(time(0));
void work(){
	for(int i=1;i<=n;i++) w[i]=rd()%2;
	for(int i=1;i<=n;i++) pre[i]=pre[i-1]+w[a[i]];
	for(int i=1;i<=m;i++){
		int sum1=pre[r[i][0]]-pre[l[i][0]-1],sum2=pre[r[i][1]]-pre[l[i][1]-1];
		if(abs(sum1-sum2)>1) answer[i]=1;
		if(abs(sum1-sum2)==1) ans[i]=1;
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0); 
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i],b[i]=a[i];
	sort(b+1,b+n+1);
	for(int i=1;i<=n;i++){
		int l=1,r=n+1;
		while(l+1<r){
			int mid=(l+r)>>1;
			if(a[i]>=b[mid]) l=mid;
			else r=mid;
		}
		a[i]=l;
	}
	for(int i=1;i<=m;i++) cin>>l[i][0]>>r[i][0]>>l[i][1]>>r[i][1];
	for(int i=1;i<=100;i++) work();
	for(int i=1;i<=m;i++){
		if(ans[i]==0||answer[i]==1) cout<<"NE\n";
		else cout<<"DA\n";
	}
	return 0;
}
```

考虑下为什么这是正确的，不妨令两个区间内的数构成的可重集合分别为 $S_1,S_2$，每次从两个集合中同时删去一个相同的数直到两个集合无交，此时我们要判断的就是 $|S_1|$ 是否恰好为 $1$，显然当 $|S_1|$ 恰好为 $1$ 时每次有 $\frac{1}{2}$ 的概率哈希值差为 $0$，有 $\frac{1}{2}$ 的概率哈希值差为 $1$，当 $|S_1|$ 为 $0$ 时每次哈希值必会相同，当 $|S_1| \geq 2$ 时至少有 $\frac{1}{8}$ 的概率使得哈希值差大于 $1$，因此随机 $100$ 次后错误概率降到了极低的范围。

---

## 作者：chenxumin1017 (赞：3)

暴力四维莫队。

维护一个桶 $cnt$，$cnt_i$ 表示 $i$ 在 $[a_{l_1},a_{l_1 + 1},\cdots,a_{r_1}]$ 的出现次数减去 $i$ 在 $[a_{l_2},a_{l_2 + 1},\cdots,a_{r_2}]$ 的出现次数。

两序列相似时 $cnt$ 中一定有 $1$ 个 $-1$ 和 $1$ 个 $1$，其余全是 $0$，只有这时 $(\sum\limits^{V}_{i = 1} \lvert cnt_i \rvert) = 2$，我们的莫队只要维护 $\sum\limits^{V}_{i = 1} \lvert cnt_i \rvert$ 就可以了。

记得要离散化。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int n, m, a[N], B, ans, anss[N], vis[N];
struct Node{
  int l, r, l2, r2, id;
}b[N];
bool cmp(Node i, Node j){
  if(i.l / B == j.l / B){
    if(i.r / B == j.r / B){
      if(i.l2 / B == j.l2 / B){
        return i.r2 < j.r2;
      }
      return i.l2 < j.l2;
    }
    return i.r < j.r;
  }
  return i.l < j.l;
}
void add(int x){
  ans += (vis[x] < 0 ? -1 : 1);
  vis[x]++;
}
void del(int x){
  ans += (vis[x] > 0 ? -1 : 1);
  vis[x]--;
}
void add2(int x){
  ans += (vis[x] > 0 ? -1 : 1);
  vis[x]--;
}
void del2(int x){
  ans += (vis[x] < 0 ? -1 : 1);
  vis[x]++;
}
int read(){
  int k = 0, f = 1;
  char c = getchar();
  while(c < '0' || c > '9'){
    if(c == '-')f = -1;
    c = getchar();
  }
  while(c >= '0' && c <= '9')k = k * 10 + c - '0', c = getchar();
  return k * f;
}
signed main(){
  n = read(), m = read();
  B = pow(n, 0.75);
  vector<int> v;
  for(int i = 1; i <= n; i++){
    a[i] = read();
    v.push_back(a[i]);
  }
  sort(v.begin(), v.end());
  for(int i = 1; i <= n; i++)a[i] = lower_bound(v.begin(), v.end(), a[i]) - v.begin() + 1;
  for(int i = 1; i <= m; i++){
    b[i].l = read();
    b[i].r = read();
    b[i].l2 = read();
    b[i].r2 = read();
    b[i].id = i;
  }
  sort(b + 1, b + m + 1, cmp);
  int l = 1, r = 0, l2 = 1, r2 = 0;
  for(int i = 1; i <= m; i++){
    while(l > b[i].l)add(a[--l]);
    while(r < b[i].r)add(a[++r]);
    while(l < b[i].l)del(a[l++]);
    while(r > b[i].r)del(a[r--]);
    while(l2 > b[i].l2)add2(a[--l2]);
    while(r2 < b[i].r2)add2(a[++r2]);
    while(l2 < b[i].l2)del2(a[l2++]);
    while(r2 > b[i].r2)del2(a[r2--]);
    anss[b[i].id] = ans;
  }
  for(int i = 1; i <= m; i++)(anss[i] == 2 ? (putchar('D'), putchar('A')) : (putchar('N'), putchar('E'))), putchar('\n');
  return 0;
}
```

---

## 作者：H3PO4 (赞：3)

**不需要哈希的莫队做法！**

注意到每次询问的两个区间长度是一样的，所以一次询问可以用两个区间的左端点和区间长度来描述。考虑莫队，维护一个桶 $cnt$，用来统计每个数**在第一个区间中的出现次数减去在第二个区间中的出现次数**。询问的区间相似（即答案为是）当且仅当 $cnt$ 中只有一个 $1$、一个 $-1$，其他全为 $0$。只需再维护桶中 $1$ 的个数和 $0$ 的个数即可。

时间复杂度分析类似带修莫队，块长取 $n^{2/3}$ 时达到最优时间复杂度 $O(n^{5/3})$。实测块长取 $2500$ 时可以通过，但是时间还是卡得很紧，喜提最劣解。

```cpp
#include<bits/stdc++.h>
using I=int;
template<class T,I N>using A=std::array<T,N>;
I read(){
  int c;while(!isdigit(c=getchar()));
  I x=c-'0';while(isdigit(c=getchar()))x=x*10+c-'0';
  return x;
}
int main(){
  const I N=1e5,M=1e5;
  I n,m;std::cin>>n>>m;
  static I a[N],b[N];for(I i=0;i<n;i++)b[i]=a[i]=read();
  std::sort(b,b+n);I bz=std::unique(b,b+n)-b;
  for(I i=0;i<n;i++)a[i]=std::lower_bound(b,b+bz,a[i])-b;
  static A<I,4>qr[M];
  for(I i=0;i<m;i++){
    I l1=read()-1,r1=read(),l2=read()-1,r2=read();
    qr[i]={l1,l2,r1-l1,i};
  }
  I blk=2500;
  std::sort(qr,qr+m,[&](auto&&x,auto&&y){
    return x[0]/blk!=y[0]/blk?x[0]<y[0]:x[1]/blk!=y[1]/blk?x[1]<y[1]:x[2]<y[2];
  });
  I l1=0,l2=0,k=0,w0=bz,w1=0;
  static I cnt[M];
  auto add=[&](I x){I&c=cnt[a[x]];w0+=(c==-1)-(c==0);w1+=(c==0)-(c==1);c++;};
  auto del=[&](I x){I&c=cnt[a[x]];w0+=(c==1)-(c==0);w1+=(c==2)-(c==1);c--;};
  static I ww[M];
  for(I i=0;i<m;i++){
    auto[ql1,ql2,qk,qi]=qr[i];
    for(;k>qk;k--)del(l1+k-1),add(l2+k-1);
    for(;l1<ql1;l1++)add(l1+k),del(l1);
    for(;l1>ql1;l1--)add(l1-1),del(l1+k-1);
    for(;l2<ql2;l2++)del(l2+k),add(l2);
    for(;l2>ql2;l2--)del(l2-1),add(l2+k-1);
    for(;k<qk;k++)add(l1+k),del(l2+k);
    ww[qi]=w1==1&&w0==bz-2;
  }
  for(I i=0;i<m;i++)puts(ww[i]?"DA":"NE");
  return 0;
}
```

---

## 作者：ArisakaMashiro (赞：2)

**另一种不需要哈希的莫队做法！**

简单翻译题干，即求这两个区间中是否仅有一个不同的数字。

我们令第一个区间所包含的所有数所组成的多重集为 $A$，第二个区间所包含的所有数所组成的多重集为 $B$，则原问题可以转化为下面这个式子的判定：

$$|A \cap B| = |A| - 1$$

注意到这个式子的形式与[P4688](https://www.luogu.com.cn/problem/P4688)中求三个区间交集的形式如出一辙，我们可以使用与 P4688 中相同的套路解决此题。

具体地，我们首先对数列进行离散化。但与寻常离散化不同的是，一个数离散化后的值为原数列 $a$ 中比它要小的数的数量（其实就是不去重）。

若将离散化之后得到的值当作下标，数组中会将连续一段区间中的值保留，它们皆代表同一个值。也就是说，我们相当于为一种数保留了一个区间。

我们将一个数加入莫队时，将其放到离散化为其保留的区间中最靠前的那一个空位，那么一种数在这段区间内就是连续的。从莫队中删除时同理，只需将最靠右的那个数删去即可。

那么求两个数组的交集也便非常简单了，只需从头到尾扫一遍，如果两个数组上的该位置都有数，则取交之后的数组的该位置上亦有值。

但是使用数组内存会爆炸，所以使用 bitset 优化空间复杂度。同时因为 bitset 本身就支持按位与操作，也能帮我们省下一些代码。

当然，就算换成 bitset，$n,m \le 10^5$ 也会 MLE。

这个时候就要用到分组询问了：我们把 $10^5$ 次询问拆成两个 $5 \times 10^4$ 的询问，这样就可以减少一半的内存开销。

时间复杂度近似 $O(n \sqrt{n})$，但带着比较大的常数，最大的点跑了950ms，建议搭配卡常技巧食用。

代码如下（本人代码习惯不是很好）：


```cpp
#include<algorithm>
#include<iostream>
#include<unordered_map>
#include<bitset>
#include<cstring>
#include<cmath>
using namespace std;
unordered_map<int, int> umap;
bitset<100010> aka[51000], pre;
int n, m, val[300000], alln[300000], eve, lst;
int app_cnt[300000], siz, ans[300000], vis[300000];
struct que{
    int l, r, id;
    bool operator <(const que a)const{
        if(a.l / siz == l / siz){
            return a.r > r;
        }
        return a.l / siz > l / siz;
    }
} alla[2000000];
void add_q(int x){
    pre[x + app_cnt[x]] = 1;
    app_cnt[x]++;
}
void minus_q(int x){
    app_cnt[x]--;
    pre[x + app_cnt[x]] = 0;
}
void work(int t){
    siz = sqrt(t * 2);
    for(int i = 1; i <= t; i++){
        cin >> alla[i * 2].l >> alla[i * 2].r >> alla[i * 2 - 1].l >> alla[i * 2 - 1].r;
        alla[i * 2].id = alla[i * 2 - 1].id = i;
        ans[i] = alla[i * 2].r - alla[i * 2].l;
    }
    pre.reset();
    memset(vis, 0, sizeof(vis));
    memset(app_cnt, 0, sizeof(app_cnt));
    sort(alla + 1, alla + 1 + t * 2);
    int l = 1, r = 0;
    for(int i = 1; i <= t * 2; i++){
        //注意，此处莫队必须先执行add操作再执行minus操作，否则可能出现 l > r 的情况导致bitset炸掉
        while(l > alla[i].l){
            l--;
            add_q(val[l]);
        }
        while(r < alla[i].r){
            r++;
            add_q(val[r]);
        }
        while(l < alla[i].l){
            minus_q(val[l]);
            l++;
        }
        while(r > alla[i].r){
            minus_q(val[r]);
            r--;
        }
        if(!vis[alla[i].id]){
            aka[alla[i].id] = pre;
            vis[alla[i].id] = 1;
        }
        else{
            aka[alla[i].id] &= pre;
        }
    }
    for(int i = 1; i <= t; i++){
        if(aka[i].count() == ans[i]){
            cout << "DA" << '\n';
        }
        else{
            cout << "NE" << '\n';
        }
    }
}
int main(){
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        cin >> val[i];
        alln[i] = val[i];
    }
    sort(alln + 1, alln + 1 + n);
    lst = m;
    for(int i = 1; i <= n; i++){
        if(alln[i - 1] != alln[i]){
            umap[alln[i]] = i;
        }
    }
    for(int i = 1; i <= n; i++){
        val[i] = umap[val[i]];
    }
    while(lst){
        if(lst > (m / 2) + 1){
            work((m / 2) + 1);
            lst -= (m / 2) + 1;
        }
        else{
            work(lst);
            lst = 0;
        }
    }
}
```

---

## 作者：xiezheyuan (赞：2)

## 简要题意

定义两个长度相等的序列 $A,B$ 是相似的，当且仅当将 $A$ 任意重排后，$A$ 与 $B$ 恰好只有一位不同。

给定一个长度为 $n$ 的序列 $a$，有 $m$ 次询问，每次询问给出两个区间 $[l_1,r_1],[l_2,r_2]$，你需要求出两个区间代表的序列是否相似。

$1\leq n,m\leq 10^5,\mathbf{0}\leq a_i\leq 10^9$。

## 思路

小清新 DS 题。

首先考虑我们如何转换题意让问题可以方便地用数据结构维护。不妨先思考另外一个问题，我们如何判断两个区间代表的序列是否重排后相同。

对于这类问题，我们通常的方法是哈希，这里我们需要设计一个顺序无关的哈希方法。一种比较简单的方法是构建一个映射 $f:\mathbb{N}\to \mathbb{N}$，具体映射关系可以通过随机数实现。则一个序列 $a$ 的哈希可以表示成 $\sum_{k\in a}f(k)\bmod 2^{64}$。这个哈希用线段树就可以维护。

回到本题，我们发现这个哈希并不能很好的刻画恰好一位不同这一性质，但是我们同时发现这个哈希方法和值域息息相关，可以考虑一些关于值域的做法。

我们建立可持久化权值线段树，回答询问的时候维护四个点（两个右端点和左端点的上一个点），我们要求恰好相差两个数，可以在权值树上二分，如果两个区间哈希值都相等，那么差 $0$ 个数，如果是叶子节点取两个区间这个值的数量之差的绝对值，如果有一边（左节点或右节点）相等就递归另一边，否则先递归一边，如果一边就相差不小于 $2$，就没必要继续递归了，否则递归下一边。

时间复杂度 $O((n+m)\log V)$，其中 $V$ 为值域。

## 代码

```cpp
#include <bits/stdc++.h>
//#define int long long
#define mid ((l + r) >> 1)
using namespace std;

const int N = 1e5 + 5, BD = 1e9;
int n, m, a[N];
using ui64 = unsigned long long;

struct node{
    ui64 v;
    int l, r, cnt;
} t[N << 5];
int root[N], tot;

void update(int p, ui64 v, int &i, int l, int r){
    t[++tot] = t[i]; i = tot;
    t[i].v += v, t[i].cnt++;
    if(l == r) return;
    if(p <= mid) update(p, v, t[i].l, l, mid);
    else update(p, v, t[i].r, mid + 1, r);
}

int query(int l1, int r1, int l2, int r2, int l, int r){
    auto judge = [&](int a, int b, int c, int d){
        return (t[b].v - t[a].v) == (t[d].v - t[c].v);
    };
    if(judge(l1, r1, l2, r2)) return 0;
    if(l == r) return abs((t[r1].cnt - t[l1].cnt) - (t[r2].cnt - t[l2].cnt));
    if(judge(t[l1].l, t[r1].l, t[l2].l, t[r2].l)) return query(t[l1].r, t[r1].r, t[l2].r, t[r2].r, mid + 1, r);
    if(judge(t[l1].r, t[r1].r, t[l2].r, t[r2].r)) return query(t[l1].l, t[r1].l, t[l2].l, t[r2].l, l, mid);
    int tmp = query(t[l1].r, t[r1].r, t[l2].r, t[r2].r, mid + 1, r);
    if(tmp >= 2) return tmp + 1;
    return tmp + query(t[l1].l, t[r1].l, t[l2].l, t[r2].l, l, mid);
}

mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> n >> m; map<int,ui64> mp;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        if(!mp.count(a[i])) mp[a[i]] = rnd();
    }
    for(int i=1;i<=n;i++){
        root[i] = root[i - 1], update(a[i], mp[a[i]], root[i], 0, BD);
    }
    while(m--){
        int l1, r1, l2, r2;
        cin >> l1 >> r1 >> l2 >> r2;
        cout << ((query(root[l1 - 1], root[r1], root[l2 - 1], root[r2], 0, BD) == 2) ? "DA" : "NE") << '\n';
    }
    return 0;
}

// Written by xiezheyuan
```

---

## 作者：MightZero (赞：2)

本题解参考了官方题解的解法。

### Solution

首先，对于判断两个序列重排后能否相等，可以使用和哈希；即对于序列 $A=\{a_1,a_2,\cdots,a_n\}$，设 $H(A)=\sum_{i=1}^{n}{a_i^M}$，$M$ 为常量；在不考虑碰撞的情况下，$A=B$ 当且仅当 $H(A)=H(B)$。

对于题目给出的查询，先假设两个序列相似；由于两个相似的序列重排后最多只有一个元素不同，可以设重排后两个序列分别为 $A=\{a_1,a_2,\cdots,a_{L-1},x\}$ 和 $B=\{a_1,a_2,\cdots,a_{L-1},y\}$。考虑求出 $A$ 与 $B$ 中所有元素的异或和，由于异或的性质，最终的结果必定是 $x\oplus y$。因为 $x\neq y$，$x\oplus y$ 的二进制表示中必然有某一位为 $1$；考虑这个 $1$ 的意义：它只会出现在 $x$ 与 $y$ 二者之一中。那么为了得到 $x$ 或 $y$ 之一，只需要任取 $x\oplus y$ 中某个为 $1$ 的二进制位，求 $A$ 和 $B$ 中所有这一个二进制位为 $1$ 的数的异或和，同样由于异或的性质，所有的 $a_i$ 都会被消去，而由于 $x$ 与 $y$ 中只有一个数的这一个二进制位的值为 $1$，最后剩下的就是 $x$ 或 $y$ 之一。将结果与前面得到的 $x\oplus y$ 异或即可得到另一个数。

得到 $x$ 和 $y$ 后，判定剩余的数是否相等就很简单了：判断 $H(A)-H(\{x\})$ 是否等于 $H(B)-H(\{y\})$ 即可。由于求出的 $x,y$ 顺序不固定，需要交换两者再做一次判定。（异或和本身也可以当作哈希来判定相等，但是碰撞概率比较高）

具体实现上可以通过预处理前缀异或和将单次查询复杂度优化到近似 $O(1)$。

### Code

```cpp
#include<bits/stdc++.h>
#define loop(x,l,r) for(ll (x) = (l);(x)<=(r);++(x))
#define rloop(x,l,r) for(ll (x) = (r);(x)>=(l);--(x))
#define elif else if
using namespace std;
using ll = long long;
using ull = unsigned ll;
inline ll read()
{
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x*=10;x+=ch-'0';ch=getchar();}
    return x*f;
}
inline void write(ll x)
{
    if(x<0){putchar('-');x=-x;}
    if(x%10==x){putchar(x+'0');return;}
    write(x/10);putchar(x%10+'0');
}
const ll N=2e5+5,M=7,C=32;
ll n,q,a[N];
ull ph[N];
ll pxc[N][C],px[N];
ull mpw(ll a,ll x)
{
    ull res=1,tmp=a;
    while(x)
    {
        if(x&1)res=res*tmp;
        tmp=tmp*tmp,x>>=1;
    }
    return res;
}
signed main()
{
    n=read(),q=read();
    loop(i,1,n)a[i]=read();
    loop(i,1,n)
    {
        ph[i]=ph[i-1]+(mpw(a[i],M));
        px[i]=px[i-1]^a[i];
        loop(j,0,C-1)
        {
            pxc[i][j]=pxc[i-1][j];
            if(a[i]&(1LL<<j))pxc[i][j]^=a[i];
        }
    }
    while(q--)
    {
        ll la=read(),ra=read(),lb=read(),rb=read();
        ll xr=px[ra]^px[la-1]^px[rb]^px[lb-1];
        if(!xr)
        {
            puts("NE");
            continue;
        }
        ll va,vb;
        loop(j,0,C-1)if(xr&(1LL<<j))
        {
            va=pxc[ra][j]^pxc[la-1][j]^pxc[rb][j]^pxc[lb-1][j];
            break;
        }
        vb=xr^va;
        ull pwa=mpw(va,M),pwb=mpw(vb,M);
        if((ph[ra]-ph[la-1]-pwa==ph[rb]-ph[lb-1]-pwb)||(ph[ra]-ph[la-1]-pwb==ph[rb]-ph[lb-1]-pwa))puts("DA");
        else puts("NE");
    }
    return 0;
}
```

---

## 作者：Super_Cube (赞：1)

# Solution

超级唐氏做法。

两个区间相似的条件可以转化为把这两个区间内的所有数分别放入两个桶中，这两个桶有且仅有两个位置不同，且其中一个位置的值只相差 $1$。

如何取出一个区间对应的桶？主席树板子。

找到最左边的不同位置？对主席树维护的桶打哈希，在主席树上二分。找最右边的不同位置同理。

如果这两个位置相等那不符合条件。如果找不到也不符合条件。找到这两个位置之后，判断这两个位置间的哈希值是否相等，如果不等说明存在第三个不同位置，还是不合法。

现在只用随便选一个位置判断两个桶中该位置的值是否相差 $1$ 即可。

# Code

```cpp
#include<bits/stdc++.h>
typedef unsigned long long ull;
const int inf=1e9;
std::mt19937_64 rnd(time(0));
struct segment{
	int lc,rc;
	int cnt;ull hash;
}t[3200005];
int root[100005],idx;
void add(int&p,int q,int L,int R,int x,ull y){
	t[p=++idx]=t[q];
	++t[p].cnt;t[p].hash+=y;
	if(L==R)return;
	int mid=L+R>>1;
	if(x<=mid)add(t[p].lc,t[q].lc,L,mid,x,y);
	else add(t[p].rc,t[q].rc,mid+1,R,x,y);
}
ull ask(int p,int q,int L,int R,int x){
	if(L==R)return t[p].hash-t[q].hash;
	int mid=L+R>>1;
	if(x<=mid)return ask(t[p].lc,t[q].lc,L,mid,x);
	return t[t[p].lc].hash-t[t[q].lc].hash+ask(t[p].rc,t[q].rc,mid+1,R,x);
}
int getL(int p1,int q1,int p2,int q2,int L,int R){
	if(L==R)return t[p1].hash-t[q1].hash==t[p2].hash-t[q2].hash?-1:L;
	int mid=L+R>>1;
	if(t[t[p1].lc].hash-t[t[q1].lc].hash!=t[t[p2].lc].hash-t[t[q2].lc].hash)return getL(t[p1].lc,t[q1].lc,t[p2].lc,t[q2].lc,L,mid);
	return getL(t[p1].rc,t[q1].rc,t[p2].rc,t[q2].rc,mid+1,R);
}
int getR(int p1,int q1,int p2,int q2,int L,int R){
	if(L==R)return t[p1].hash-t[q1].hash==t[p2].hash-t[q2].hash?-1:L;
	int mid=L+R>>1;
	if(t[t[p1].rc].hash-t[t[q1].rc].hash!=t[t[p2].rc].hash-t[t[q2].rc].hash)return getR(t[p1].rc,t[q1].rc,t[p2].rc,t[q2].rc,mid+1,R);
	return getR(t[p1].lc,t[q1].lc,t[p2].lc,t[q2].lc,L,mid);
}
int at(int p,int q,int L,int R,int x){
	if(L==R)return t[p].cnt-t[q].cnt;
	int mid=L+R>>1;
	if(x<=mid)return at(t[p].lc,t[q].lc,L,mid,x);
	return at(t[p].rc,t[q].rc,mid+1,R,x);
}
std::map<int,ull>mp;
int n,m;
int main(){
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);std::cout.tie(0);
	std::cin>>n>>m;
	for(int i=1,x;i<=n;++i){
		std::cin>>x;
		if(!mp.count(x))mp[x]=rnd();
		add(root[i],root[i-1],0,inf,x,mp[x]);
	}
	for(int l1,r1,l2,r2;m--;){
		std::cin>>l1>>r1>>l2>>r2;
		int L=getL(root[r1],root[l1-1],root[r2],root[l2-1],0,inf);
		if(L==-1){
			std::cout<<"NE\n";
			continue;
		}
		int R=getR(root[r1],root[l1-1],root[r2],root[l2-1],0,inf);
		if(R==L){
			std::cout<<"NE\n";
			continue;
		}
		if(ask(root[r1],root[l1-1],0,inf,R-1)-ask(root[r1],root[l1-1],0,inf,L)!=ask(root[r2],root[l2-1],0,inf,R-1)-ask(root[r2],root[l2-1],0,inf,L)){
			std::cout<<"NE\n";
			continue;
		}
		std::cout<<(std::abs(at(root[r1],root[l1-1],0,inf,L)-at(root[r2],root[l2-1],0,inf,L))==1?"DA":"NE")<<'\n';
	}
	return 0;
}
```

---

## 作者：_LiWenX_ (赞：1)

神秘做法，和别人聊天的时候想到的，最开始没太觉得对，结果写出来 A 了。

肯定是考虑哈希，具体怎么做呢？

首先定义一个常数 $B$，然后构造一个映射 $f(x)\in[1,B],(1\le x\le 10^9)$，然后 $a_i$ 赋值成 $f(a_i)$。

再构造一个映射 $g(x)\in[1,10^9],(1\le x\le B)$，把 $a_i$ 赋值成 $g(a_i)$。

我们令 $B$ 不是很大，记录 $g(i)-g(j)$ 两两的差，全部存到一个集合 $S$ 里面。

接下来考虑询问。

求出两个对应区间的 $a$ 的和，记为 $s1,s2$，然后如果 $s1-s2\in S,s1\not =s2$，我们就认为合法，否则必然不合法，这是显然的。

当然如果构造的不够好，我们显然不能区分出来两个不同的数字。所以我们使用随机化，将 $f,g$ 变成随机映射，然后我们多做几次，凭借数学直觉告诉我，估计做 $\log_B n$ 次就期望可以把所有数字两两区分了，所以就做这么写了一下，过了，时间复杂度为 $O(\log_B n(n+q+B^2))$，实际实现中 $B$ 取了 $100$。

但是我完全不会证明这为啥是对的，只能说是提供一种思路吧，如果有人会证明或者会卡这个做法欢迎找我讨论。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,m;
int a[100005];unordered_map<int,int> A;int tot;
ll sum[100005];
int l1[100005],l2[100005],r1[100005],r2[100005];
int ans[100005],t[100005];
mt19937 rd(time(NULL));
int to[105];
int ma[100005];
void solve(){
	for(int i=1;i<=100;i++){
		to[i]=rd()%1000000000;
	}
	unordered_map<ll,bool> vis;
	for(int i=1;i<=100;i++){
		for(int j=1;j<=100;j++){
			vis[to[i]-to[j]]=1;
		}
	}
	for(int i=1;i<=tot;i++) ma[i]=0;
	for(int i=1;i<=n;i++){
		if(!ma[a[i]]){
			ma[a[i]]=rd()%100+1;
		}
		sum[i]=sum[i-1]+to[ma[a[i]]];
	}
	for(int i=1;i<=m;i++){
		ll s1=sum[r1[i]]-sum[l1[i]-1];
		ll s2=sum[r2[i]]-sum[l2[i]-1];
		if(vis[s1-s2]==0){
			ans[i]=0;
		}
		if(s1!=s2) t[i]=1;
	}
} 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(!A[a[i]]) A[a[i]]=++tot;
		a[i]=A[a[i]];
	}
	for(int i=1;i<=m;i++){
		ans[i]=1;
		cin>>l1[i]>>r1[i]>>l2[i]>>r2[i];
	}
	for(int i=1;i<=3;i++){
		solve();
	}
	for(int i=1;i<=m;i++){
		if(ans[i]&&t[i]){
			cout<<"DA\n";
		}
		else{
			cout<<"NE\n";
		}
	}
}
```

---

## 作者：ForgotMe (赞：0)

被自己唐住了。

第一眼看上去这不是原题吗？今年 NOI 现考的。似乎就是一个普通的 sum hash 问题。
首先如果不是相似而是完全相同，这是一个非常经典的问题，给每个值随机赋权，使用 sum hash 即可。

关键在于这个唯一不同的元素该如何处理？然后我就不会了，开始往数据结构方向思考/kx。很快得到了一个 $\mathcal{O}(q\sqrt{n})$ 的莫队做法，但是查看其他人的 AC 记录发现跑的超级快，那么说明肯定想错了。

下面直接讲正确思路。如果能够直接把两个区间中分别多出来的数找出来，那么问题就得到了解决。考虑一个非常甜菜的想法，使用二进制拆位，对于一个集合 $S$，维护 $F(S,i)=\sum_{x\in S}[2^i\in x]x$，$[2^i\in x]$ 表示 $x$ 二进制下第 $i$ 位为 $1$，类似的，定义 $G(S,i)=\sum_{x\in S}[2^i\notin x]x$。

由于知道了两个区间分别只多出来了一个数，其多出来的这个数不一样。设询问的两个区间形成的可重集合分别为 $S,T$，那么一定存在一个 $i\in [0,30]$，满足 $F(S,i)\ne F(T,i),G(S,i)\ne G(T,i)$，而且多出来的这两个数可以直接算出来，就是 $|F(S,i)-F(T,i)|$，$|G(S,i)-G(T,i)|$。那么使用 sum hash check 去除这两个数后剩下的可重集合是否相同即可。

时间复杂度 $\mathcal{O}((n+q)\log V)$。

代码：https://www.luogu.com.cn/paste/6baoa765

---

