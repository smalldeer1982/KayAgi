# Secret Letters

## 题目描述

Little W and Little P decided to send letters to each other regarding the most important events during a day. There are $ n $ events during a day: at time moment $ t_i $ something happens to the person $ p_i $ ( $ p_i $ is either W or P, denoting Little W and Little P, respectively), so he needs to immediately send a letter to the other person. They can send a letter using one of the two ways:

- Ask Friendly O to deliver the letter directly. Friendly O takes $ d $ acorns for each letter.
- Leave the letter at Wise R's den. Wise R values free space, so he takes $ c \cdot T $ acorns for storing a letter for a time segment of length $ T $ . The recipient can take a letter from Wise R either when he leaves his own letter at Wise R's den, or at time moment $ t_{n + 1} $ , when everybody comes to Wise R for a tea. It is not possible to take a letter from Wise R's den at other time moments. The friends can store as many letters at Wise R's den as they want, paying for each one separately.

Help the friends determine the minimum possible total cost of sending all letters.

## 说明/提示

One of optimal solutions in the first example:

- At time moment 0 Little P leaves the letter at Wise R's den.
- At time moment 1 Little W leaves his letter at Wise R's den and takes Little P's letter. This letter is at the den from time moment 0 to time moment 1, it costs $ 1 $ acorn.
- At time moment 3 Little P sends his letter via Friendly O, it costs $ 4 $ acorns.
- At time moment 5 Little P leaves his letter at the den, receiving Little W's letter which storage costs 4 acorns.
- At time moment 8 Little P leaves one more letter at the den.
- At time moment 10 Little W comes to the den for a tea and receives the two letters, paying 5 and 2 acorns.

The total cost of delivery is thus $ 1 + 4 + 4 + 5 + 2 = 16 $ acorns.

## 样例 #1

### 输入

```
5 1 4
0 P
1 W
3 P
5 P
8 P
10
```

### 输出

```
16
```

## 样例 #2

### 输入

```
10 10 94
17 W
20 W
28 W
48 W
51 P
52 W
56 W
62 P
75 P
78 P
87
```

### 输出

```
916
```

# 题解

## 作者：strange757 (赞：10)

   考虑寄存第一封信的代价，由于寄存第一封信之后无论如何操作，寄存处始终会有一封信存在，所以对与第一封信，我们特殊考虑。假设第一封寄存的是 $i$ ， 那么我们可以把它的代价设为 $t_{n+1} - t_{i}$ ，对于每次交替寄存，我们可以认为它的代价为 $0$ （第一封信已经把代价算进去了）。
   
   如果寄存处已经有自己的一封信，我们考虑这时候是寄存优还是直接送更优，对于同一个人寄存的第二封以上的信，他的代价可以认为是当前时间到下一次交替的时间，因为下一个人来取信时会取走全部信，却只留下一封，而留下的那一封信的贡献一开始就算了，所以可以直接算出寄存的代价。这时比较寄存和直接送哪个更优就可以。
   
   具体如何实现呢，首先我们先倒序枚举第一封寄存的信的位置，对于交替的位置权值为 $0$ ， 非交替位置的贡献是到下一交替位置寄存的花费和直接取 $min$ ，这样对于每一个位置就可以直接计算出总贡献。
   
   ```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define int long long
using namespace std;
const int N = 1e5 + 5;
int n, c, d, a[N], ans;
char op[N];
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n >> c >> d;
    for(int i = 1; i <= n; i++){
        cin >> a[i] >> op[i];
    }
    cin >> a[n + 1];
    op[n + 1] = 'A';
    ans = n*d;
    int lst = a[n + 1], sum = 0;
    for(int i = n; i >= 1; i--){
        if(op[i] == op[i + 1]){//非交替位置
            sum += min(d, (lst - a[i + 1])*c);
        }else{//交替位置
            lst = a[i + 1];
        }
        ans = min(ans, (a[n + 1] - a[i])*c + sum + d*(i - 1));//计算总花费
    }
    printf("%lld\n", ans);
    return 0;
}  
   ```

---

## 作者：caidzh (赞：5)

容易观察得到同一个人送信的连续段中的决策分为三个阶段：

第一个阶段是去 R 存信（这种操作在第二阶段前只会用一次）

第二个阶段是一个直接送出信的连续段

第三个阶段是一个存信的连续段

正确性应该比较显然

这样容易想到一个动态规划的做法，考虑 $f_{i,0/1}$ 表示当前连续段是否有第一个阶段的最小花费，朴素的做法是 $\operatorname{O}(n^2)$ 的，可以对其进行斜率优化做到更优秀的复杂度

事实上，此题存在一种更好写的 $\operatorname{O}(n)$ 做法

考虑送信人序列 $\text{P...W...P...}$，如果在第一个 $\text{P}$ 的位置存信，并且之后都不去存信，其带来的贡献是 $t_{n+1}-t_P$

仔细思考过后可以发现第二个人一定会在第一个 $\text{W}$ 的位置去存信，因为这样做可以看做存放的信并没有动，并且可以少掉 $d$ 的花费

于是我们得到一个结论是：第一次存信后，之后切换送信人的位置一定会去存信

于是可以枚举第一次存信的位置 $i$，之前的花费对答案的贡献是 $d(i-1)$，每个连续段中，因为已经知道另一个人下一次取信的时间 $lst$，$j$ 位置上的信对答案的贡献可以直接选取 $\min(d,(lst-t_j)c)$
```cpp
const int maxn=100010,mod=998244353;
int n,c,d,t[maxn];char op[maxn][7];
signed main(){
	n=read();c=read();d=read();
	for(int i=1;i<=n;i++)t[i]=read(),scanf("%s",op[i]+1);
	t[n+1]=read();op[n+1][1]='I';op[n+1][2]='A';op[n+1][3]='K';
	op[n+1][4]='I';op[n+1][5]='O';op[n+1][6]='I';
	int ans=d*n,s=0,lst;
	for(int i=n;i>=1;i--){
		if(op[i][1]==op[i+1][1])s+=min(d,(lst-t[i+1])*c);else lst=t[i+1];
		ans=min(ans,(i-1)*d+s+(t[n+1]-t[i])*c);
	}cout<<ans;return 0;
}
```


---

## 作者：sunzh (赞：2)

~~（思路from V--o_o--V~~

我们考虑某封信它寄存了

设下次另一个人寄存信的时间为$t_j$那么它的花费是$c*(t_j-t_i)$，然后对于$j$那封信同样也要话费$c*(t_k-t_j)$，最终到$t_{n+1}$

也就是说，第$i$封信寄存，后面寄存的花费至少要$c*(t_{n+1}-t_i)$

既然至少要花费这么多，我们可以两个人交替分配一些信“免费寄存”（实质上花费算在$c*(t_{n+1}-t_i)$中了）

每封信的花费我们可以在寄存或直接寄信中选花费小的

分配的时候我们一定会选花费最大的

我们在每次交替时选最后一个即可，因为若寄存它花费最大，若直接寄信他也是花费最大的之一

实现复杂度$O(n)$



---

## 作者：Arghariza (赞：0)

完全观察不到性质。呜呜呜。

考虑如果某个时刻 A 寄存信的话肯定是 B 在这个时刻后第一次去寄存处就拿走这封信最优。所以我们有个倒序考虑的 dp，$f_{i,x,y}$ 表示考虑完 $t_i\sim t_{n+1}$ 的事件，A 最早在 $x$ 时刻去了寄存处，B 最早在 $y$ 时刻去了寄存处。转移是简单的，考虑是直接送出还是寄存即可。以 $t_i$ 时刻 A 送信为例：

$$
f_{i+1,x,y}+d\to f_{i,x,y}
\\
f_{i+1,x,y}+c(t_y-t_i)\to f_{i,i,y}
$$
直接做复杂度是 $O(n^3)$ 的，然而我们发现 $x,y$ 两维的转移都相对独立，于是我们直接拆开。重新令 $f_{i,x}$ 为考虑到 $t_i$，A 最早在 $x$ 时刻去了寄存处；$g_{i,y}$ 同理。还是以 $t_i$ 时刻 A 送信为例，有转移：
$$
g_{i,y}=g_{i+1,y}+\min(d,c(t_y-t_i))
\\
f_{i,x}=f_{i+1,x}+d(x\neq i)
\\
f_{i,i}=\min\limits_{y}g_{i+1,y}+c(t_y-t_i)
$$
为了方便，我们令 $f'_{i,x}=f_{i,x}+c\cdot t_x,g'_{i,y}=g_{i,y}+c\cdot t_y$：
$$
g'_{i,y}=g'_{i+1,y}+\min(d,c(t_y-t_i))
\\
f'_{i,x}=f'_{i+1,x}+d(x\neq i)
\\
f'_{i,i}=\min\limits_{y}g'_{i+1,y}
$$
直接做是 $O(n^2)$ 的。

对于 $f'$ 的转移，只需要维护 $f'$ 的区间加、$g'$ 的最小值；$g'$ 的转移，容易发现满足 $c(t_y-t_i)\le d$ 的 $y$ 为一段区间，二分出这个区间后只需要维护 $g'$ 的区间加以及对位加（给位置 $y$ 加 $c\cdot t_y$）。B 的情况和 A 是对称的。KTT 即可做到 $O(n\cdot\text{poly}(\log n))$。

```cpp
#include <bits/stdc++.h>
#define eb emplace_back
#define mp make_pair
#define fi first
#define se second
#define F(i, x, y) for (int i = (x); i <= (y); i++)
#define R(i, x, y) for (int i = (x); i >= (y); i--)
#define FIO(FILE) freopen(FILE".in", "r", stdin), freopen(FILE".out", "w", stdout)
#define int long long

using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
bool Mbe;

const int N = 1e5 + 5;
const int inf = 0x3f3f3f3f3f3f3f3f;

int n, c, d;
int t[N];
char op[N];

struct Seg {
	
	int k, b;
	
	Seg () { }
	Seg (int _k, int _b) : k(_k), b(_b) { }
	
	bool operator < (const Seg &r) const {
		if (b != r.b) {
			return b < r.b;
		}
		return k < r.k;
	}

};

int its(Seg p, Seg q) {
	if (p.k < q.k) {
		swap(p, q);
	}
	if (p.k == q.k || p.b >= q.b) {
		return inf;
	}
	int b = q.b - p.b, k = p.k - q.k;
	return (b + k - 1) / k; 
}

struct Toptree {
	
	struct Tag {
		
		int x, b;
		
		Tag () { }
		Tag (int _x, int _b) : x(_x), b(_b) { }
		
		Tag operator + (const Tag &r) const {
			return Tag(x + r.x, b + r.b);
		}
		
	} lz[N << 2];
	
	struct Info {
		
		Seg p;
		int ir;
		
		Info () { }
		Info (Seg _p, int _ir) : p(_p), ir(_ir) { }
		
		Info operator + (const Info &r) const {
			return Info(p < r.p ? p : r.p, min({ ir, r.ir, its(p, r.p) }));
		}
		
		Info operator + (const Tag &r) const {
			return Info(Seg(p.k, p.b + p.k * r.x + r.b), ir - r.x);
		}
		
	} tr[N << 2];
	
	#define ls (x << 1)
	#define rs (x << 1 | 1)
	#define mid ((l + r) >> 1)
	
	void pup(int x) {
		tr[x] = tr[ls] + tr[rs];
	}
	
	void plz(int x, Tag c) {
		tr[x] = tr[x] + c;
		lz[x] = lz[x] + c;
	}
	
	void pdn(int x) {
		if (!lz[x].x && !lz[x].b) {
			return;
		}
		plz(ls, lz[x]);
		plz(rs, lz[x]);
		lz[x] = Tag(0, 0);
	}
	
	void reb(int l, int r, int x) {
		if (l == r || tr[x].ir > 0) {
			return;
		}
		pdn(x);
		reb(l, mid, ls);
		reb(mid + 1, r, rs);
		pup(x);
	}
	
	void bld(int l, int r, int x) {
		lz[x] = Tag(0, 0);
		tr[x] = Info(Seg(0, inf), inf);
		if (l == r) {
			return;
		}
		bld(l, mid, ls);
		bld(mid + 1, r, rs);
	}
	
	void ins(int l, int r, int p, Seg c, int x) {
		if (l == r) {
			tr[x] = Info(c, inf);
			return;
		}
		pdn(x);
		if (p <= mid) {
			ins(l, mid, p, c, ls);
		} else {
			ins(mid + 1, r, p, c, rs);
		}
		pup(x);
	}
	
	void addx(int l, int r, int s, int t, int c, int x) {
		if (s <= l && r <= t) {
			plz(x, Tag(c, 0));
			reb(l, r, x);
			return;
		}
		pdn(x);
		if (s <= mid) {
			addx(l, mid, s, t, c, ls);
		} 
		if (t > mid) {
			addx(mid + 1, r, s, t, c, rs);
		}
		pup(x);
	}
	
	void addb(int l, int r, int s, int t, int c, int x) {
		if (s <= l && r <= t) {
			plz(x, Tag(0, c));
			return;
		}
		pdn(x);
		if (s <= mid) {
			addb(l, mid, s, t, c, ls);
		}
		if (t > mid) {
			addb(mid + 1, r, s, t, c, rs);
		}
		pup(x);
	}
	
	int qry(int l, int r, int s, int t, int x) {
		if (s <= l && r <= t) {
			return tr[x].p.b;
		}
		pdn(x);
		if (s > mid) {
			return qry(mid + 1, r, s, t, rs);
		} else if (t <= mid) {
			return qry(l, mid, s, t, ls);
		} else {
			return min(qry(l, mid, s, t, ls), qry(mid + 1, r, s, t, rs));
		}
	}
	
	int ans(int l, int r, int x) {
		if (l == r) {
			return tr[x].p.b - c * t[l];
		}
		pdn(x);
		return min(ans(l, mid, ls), ans(mid + 1, r, rs));
	}
	
	void b() {
		bld(1, n + 1, 1);
	}
	
	void i(int p, int k, int b) {
		ins(1, n + 1, p, Seg(k, b), 1);
	}
	
	void ax(int l, int r, int c) {
		if (l > r) {
			return;
		}
		addx(1, n + 1, l, r, c, 1);
	}
	
	void ab(int l, int r, int c) {
		if (l > r) {
			return;
		}
		addb(1, n + 1, l, r, c, 1);
	}
	
	int q(int l, int r) {
		return qry(1, n + 1, l, r, 1);
	}
	
	int a() {
		return ans(1, n + 1, 1);
	}
	
} F, G;

void solve() {
	cin >> n >> c >> d;
	F (i, 1, n) {
		cin >> t[i] >> op[i];
	}
	cin >> t[n + 1];
	F.b(), G.b();
	F.i(n + 1, t[n + 1], c * t[n + 1]);
	G.i(n + 1, t[n + 1], c * t[n + 1]);
	R (i, n, 1) {
		if (op[i] == 'W') {
			F.ab(i + 1, n + 1, d);
			F.i(i, t[i], G.q(i + 1, n + 1));
			int p = upper_bound(t + i + 1, t + n + 2, t[i] + 1. * d / c) - t - 1;
			if (p > n + 1) {
				G.ab(i + 1, n + 1, d);
				continue;
			}
			G.ab(p + 1, n + 1, d);
			G.ax(i + 1, p, c);
			G.ab(i + 1, p, - c * t[i]);
		} else {
			G.ab(i + 1, n + 1, d);
			G.i(i, t[i], F.q(i + 1, n + 1));
			int p = upper_bound(t + i + 1, t + n + 2, t[i] + 1. * d / c) - t - 1;
			if (p > n + 1) {
				F.ab(i + 1, n + 1, d);
				continue;
			}
			F.ab(p + 1, n + 1, d);
			F.ax(i + 1, p, c);
			F.ab(i + 1, p, - c * t[i]);
		}
	}
	cout << F.a() << '\n';
}

bool Med;
signed main() {
	// FIO("");
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cerr << (&Mbe - &Med) / 1048576.0 << " MB\n";
	int T = 1;
	// cin >> T;
	while (T--) solve();
	cerr << (int)(1e3 * clock() / CLOCKS_PER_SEC) << " ms\n";
	return 0;
}
```

---

## 作者：_ANIG_ (赞：0)

[Secret Letters ](https://www.luogu.com.cn/problem/CF1120F)

枚举第一封信是什么时候寄存的。

若另一方来取信，则会再次寄存一个。

所以可以看作一个信从一开始寄存到了结尾。

这样，第一次取信就可以看作是免费的。

贪心地，每次能取信就取信。

这样每个信在什么时候取就固定了，每个信寄存的代价也固定了，直接和 $d$ 取个 $\min$ 就是对答案的贡献。

后缀和预处理一下就可以 $O(n)$。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e5+5;
int p[N],op[N],n,w1,w2,res,eds,nxt[N],hz[N];
signed main(){
    cin>>n>>w1>>w2;
    for(int i=1;i<=n;i++){
        char c;
        scanf("%lld %c",&p[i],&c);
        op[i]=c=='P';
    }
    cin>>p[n+1];op[n+1]=2;
    for(int i=n;i>=1;i--){
        if(op[i+1]!=op[i])nxt[i]=i+1;
        else nxt[i]=nxt[i+1];
        hz[i]=hz[i+1];
        if(op[i]==op[i-1])hz[i]+=min(w2,w1*(p[nxt[i]]-p[i]));
    }
    res=n*w2;
    for(int i=1;i<=n;i++)res=min(res,w1*(p[n+1]-p[i])+hz[i+1]+(i-1)*w2);
    cout<<res;
}
```


---

## 作者：Otomachi_Una_ (赞：0)

## C. Secret Letters

蒟蒻不会线性，想要线性左转。

考虑倒过来，从后往前枚举。$f_{i,p,q}$ 表示当前枚举到 $t_i$，两个人上一次去 WiseR 的时间分别是 $t_p,t_q$ 的最小代价。

转移有三种：

- 直接寄走：$\operatorname{chkmin}(f_{i,p,q},f_{i+1,p,q}+d)$。
- 交给 WiseR：
  - 如果当前是 `P`，$\operatorname{chkmin}(f_{i,i,q},f_{i+1,p,q}+c(t_p-t_i))$。
  - 如果当前是 `W`，$\operatorname{chkmin}(f_{i,p,i},f_{i+1,p,q}+c(t_q-t_i))$。

这样子复杂度达到了惊人的 $\mathcal O(n^4)$，考了优化。我们先把 $f_{i,p,q}$ 改写为 $f_{i,p,q}+t_p+t_q$，这样有利于后面两个式子的转移。

首先，后面两个转移表达我们只关心每个 $f_{i,*,q}$，$f_{i,p,*}$ 的最小值，我们用 $g_{i,q},h_{i,p}$ 维护。

我们发现我们已经不关心 $f$ 了，三个转移式可以写成：

- $g_{i,*},h_{i,*}$ 赋值 $g_{i+1,*}+d,h_{i+1,*}+d$。
- 如果当前为 `P`，$f_{i,i,*}$ 向 $\min f_{i+1,?,*}=g_{i+1,*}$ 取 $\min$，转到 $g,h$ 上就是 $h_{i,i}$ 变成 $g_{i+1,*}$ 取 $\min$，$g_i$ 向 $g_{i+1}$ 取 $\min$。
- 当前为 `W` 是同理的。

然后我们可以把 $i$ 这一位用时间代替（类似于闹钟那道题），对 $g,h$ 用点数据结构维护就可以了。

我不明白我为什么写 KTT。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define MP make_pair
#define int long long
mt19937 rnd(time(0));
const int MAXN=1e5+5;
const int MR=1e6+5;
const ll inf=1e12;
ll n,c,d,m;// c: 穴内一秒，d: 丢掉 
ll t[MAXN],op[MAXN];
ll f[MAXN][2];// 左/右端点 上一个在 i 的最小代价 
struct line{ll a,b;};// ax+b 
bool operator < (line x,line y){return (x.b!=y.b?x.b<y.b:x.a<y.a);} 
ll inter(line x,line y){
	if(x.a>y.a) swap(x,y);
	y.a-=x.a;y.b-=x.b;
	if(y.a==0||y.b>=0) return inf;
	return (y.b+y.a-1)/y.a;
}
struct segt{
// 维护区间加，区间下标加，区间最小值（KTT?）
ll laz1[MR<<2],laz0[MR<<2],intr[MR<<2];
line minn[MR<<2]; 
// x 的懒标记，b 的懒标记，minn 最小线段，intr 最小改变时间
void pushdown(int id){
	for(int son:{id<<1,id<<1|1}){
		laz1[son]+=laz1[id];laz0[son]+=laz0[id];
		intr[son]-=laz1[id];
		minn[son].b+=laz1[id]*minn[son].a+laz0[id];
	}
	laz1[id]=laz0[id]=0;
	return;
} 
void pushup(int id){
	minn[id]=(minn[id<<1]<minn[id<<1|1]?minn[id<<1]:minn[id<<1|1]);
	intr[id]=min({intr[id<<1],intr[id<<1|1],inter(minn[id<<1],minn[id<<1|1])});
}
void rebuild(int id){
	if(intr[id]>=0) return;
//	cout<<"Rebuild "<<id<<' '<<intr[id]<<endl;
	pushdown(id);
	rebuild(id<<1);rebuild(id<<1|1);
	pushup(id);
}
void add_b(int L,int R,ll d,int id=1,int l=0,int r=m){
	if(L>R) return;
	if(L<=l&&r<=R){
		laz0[id]+=d;minn[id].b+=d;
		return;
	}
	pushdown(id);
	int mid=l+r>>1;
	if(L<=mid) add_b(L,R,d,id<<1,l,mid);
	if(mid<R) add_b(L,R,d,id<<1|1,mid+1,r);
	pushup(id);
	return;
}
void add_x(int L,int R,ll d,int id=1,int l=0,int r=m){
	if(L>R) return;
	if(L<=l&&r<=R){
		laz1[id]+=d;minn[id].b+=minn[id].a*d;
		intr[id]-=d;
		if(intr[id]<0) rebuild(id);
		return;
	}
	pushdown(id);
	int mid=l+r>>1;
	if(L<=mid) add_x(L,R,d,id<<1,l,mid);
	if(mid<R) add_x(L,R,d,id<<1|1,mid+1,r);
	pushup(id);
	return;
}
void set(int x,line v,int id=1,int l=0,int r=m){
	if(l==r){minn[id]=v;return;}
	pushdown(id);
	int mid=l+r>>1;
	if(x<=mid) set(x,v,id<<1,l,mid);
	else set(x,v,id<<1|1,mid+1,r);
	pushup(id);
	return; 
}
ll ask(int L,int R,int id=1,int l=0,int r=m){
	if(L>R) return inf;
	if(L<=l&&r<=R) return minn[id].b;
	pushdown(id);
	int mid=l+r>>1;ll ans=inf; 
	if(L<=mid) ans=min(ans,ask(L,R,id<<1,l,mid));
	if(mid<R) ans=min(ans,ask(L,R,id<<1|1,mid+1,r));
	return ans;
}
void build(int id=1,int l=0,int r=m){
	minn[id]=(line){inf,inf};intr[id]=inf;
	if(l==r) return;
	int mid=l+r>>1;
	build(id<<1,l,mid);
	build(id<<1|1,mid+1,r);
	pushup(id);
	return;
}
}T[2];
signed main(){
	ios::sync_with_stdio(false);
	cin>>n>>c>>d;
	for(int i=1;i<=n;i++){
		char c;cin>>t[i]>>c;
		op[i]=(c=='P');
	}
	cin>>t[n+1];m=t[n+1];
	memset(f,0x3f,sizeof(f));
	T[0].build();T[1].build();
	T[0].set(t[n+1],(line){t[n+1],c*t[n+1]});
	T[1].set(t[n+1],(line){t[n+1],c*t[n+1]});
//	f[n+1][0]=f[n+1][1]=c*t[n+1]; 
	for(int i=n;i>=1;i--){
//		cout<<"solve "<<i<<' '<<T[!op[i]].ask(t[i+1],m)<<endl;
		T[op[i]].set(t[i],(line){t[i],T[!op[i]].ask(t[i+1],m)});
		T[!op[i]].add_x(t[i+1],d/c+t[i],c);T[!op[i]].add_b(t[i+1],d/c+t[i],-c*t[i]);
		T[!op[i]].add_b(d/c+t[i]+1,m,d);
		T[op[i]].add_b(t[i+1],t[n+1],d);
//		for(int j=i+1;j<=n+1;j++) f[i][op[i]]=min(f[i][op[i]],f[j][!op[i]]);
//		for(int j=i+1;j<=n+1;j++) f[j][!op[i]]+=min(d,c*(t[j]-t[i])),f[j][op[i]]+=d;
	}
	ll ans=inf;
	for(int i=1;i<=n+1;i++) for(int j:{0,1})
		ans=min(ans,T[j].ask(t[i],t[i])-c*t[i]);
	cout<<ans<<endl;
	return 0; 
}
```

---

## 作者：Kaenbyou_Rin (赞：0)

校内模拟赛做到的题。学长非常良心的给了很多档部分分：

对于所有测试数据，保证 $1\leq n \leq 10^6$，$1 \leq c \leq 10^2$，$1 \leq d \leq 10^8$，$t_i<t_{i+1}$。

| 测试点编号       | $n\le$  | 特殊性质                    |
|:-------------:|:-------:|:-----------------------:|
| $1,2,3$       | $1000$  |                         |
| $4,5,6$       |         | $\forall p_i,p_i = p_1$ |
| $7,8$         |         | $d<c$                   |
| $9,10,11,12$  | $20000$ |                         |
| $13,14,15,16$ | $10^5$  |                         |
| $17,18,19,20$ |         |                         |

由于我很菜，所以先考虑特殊性质。$d<c$ 的档很好想，直接输出 $ d \times n $ 即可。这也给了我们提示，$ ans $ 的最大值不超过 $ d \times n $。

重点是这条性质 $\forall p_i,p_i = p_1$。
我们想到，如果全部由同一人送信，必然存在一个 $i$，使得第 $i$ 次往后全部寄存，往前直接送出。

于是，我们可以想到，对于 $\left \{ p_i \mid  p_i = p_l , i \in  \left [ l , r \right ]  \right \} $，我们对这段进行扫描，得到分割点即可。


还有一个需要注意的是，每当换一个人送信时，他必须先去寄存信，以便他取回上一个人寄存的信件。很明显这不会使答案更劣。

从后往前扫更新答案，做完了。时间复杂度 $  O\left ( n \right ) $。



---

