# [ABC334F] Christmas Present 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc334/tasks/abc334_f

$ xy $ 平面として表される町があり、サンタさんと、$ 1 $ から $ N $ までの番号が付けられた $ N $ 人の子供が住んでいます。 サンタさんの家の座標は $ (S_X,S_Y) $ であり、子供 $ i\ (1\leq\ i\leq\ N) $ の家の座標は $ (X_i,Y_i) $ です。

サンタさんは、$ N $ 人の子供たちに**番号順に**プレゼントを $ 1 $ 個ずつ配りたいです。 子供 $ i $ にプレゼントを配るためには、プレゼントを $ 1 $ 個以上持った状態で子供 $ i $ の家に行く必要があります。 しかし、サンタさんは同時に $ K $ 個までしかプレゼントを持つことができず、プレゼントを補充するためには一旦自分の家に戻る必要があります（サンタさんの家には十分な数のプレゼントがあります）。

サンタさんが自分の家を出発し、$ N $ 人の子供たち全員にプレゼントを配って、自分の家まで戻ってくるために移動する距離の最小値を求めてください。

## 说明/提示

### 制約

- $ 1\leq\ K\leq\ N\ \leq\ 2\times\ 10^5 $
- $ -10^9\leq\ S_X,S_Y,X_i,Y_i\ \leq\ 10^9 $
- $ (S_X,S_Y)\neq\ (X_i,Y_i) $
- $ (X_i,Y_i)\neq\ (X_j,Y_j)\ (i\neq\ j) $
- 入力は全て整数

### Sample Explanation 1

![](https://img.atcoder.jp/abc334/3c258c2a4866ff2c01dbcdbdfebb4111.png) 

上図において、赤い丸はサンタさんの家、中に数字が書かれた丸はその番号の子供の家を表しています。 サンタさんが以下のように行動することを考えます。 1. プレゼントを $ 2 $ 個持ってサンタさんの家を出る。 2. 子供 $ 1 $ の家に行ってプレゼントを $ 1 $ 個配る。 3. サンタさんの家に戻ってプレゼントを $ 1 $ 個補充する。 4. 子供 $ 2 $ の家に行ってプレゼントを $ 1 $ 個配る。 5. 子供 $ 3 $ の家に行ってプレゼントを $ 1 $ 個配る。 6. サンタさんの家に戻る。 このとき、サンタさんが移動する距離は $ 2+2+1+2+\sqrt{5}=7+\sqrt{5}=9.236\dots $ となり、これが最小です。

## 样例 #1

### 输入

```
3 2
1 1
3 1
1 2
3 2```

### 输出

```
9.236067977499790```

## 样例 #2

### 输入

```
2 1
0 1
-1 1
1 1```

### 输出

```
4.000000000000000```

## 样例 #3

### 输入

```
8 3
735867677 193944314
586260100 -192321079
95834122 802780784
418379342 -790013317
-445130206 189801569
-354684803 -49687658
-204491568 -840249197
853829789 470958158
-751917965 762048217```

### 输出

```
11347715738.116592407226562```

# 题解

## 作者：Eraine (赞：11)

编号：AT_abc334_f

一道挺裸的 $\text{dp}$ 题？

发现是按照顺序进行遍历数组的，所以前面遍历过的位置不会对后面产生影响，故没有后效性。考虑 $\text{dp}$。

这里设从 $l$ 不回到源点 $S$ 一直走到 $r$ 的代价为 $w(l,r)$，从 $S$ 走到 $i$ 单程的代价为 $dis_i$。

易得方程：

$$f_i=\min_{j=0}^{i-1}(f_j+dis_{j+1}+w(j+1,i)+dis_i)(j+k\ge i)$$

暴力是 $\Theta(n^2)$。考虑优化。发现这个方程长得很单调队列优化，瓶颈在 $w$ 数组。发现 $w$ 数组可以前缀和预处理，即 $w(l,r)=pre_r-pre_l$。直接上单调队列优化即可。时间复杂度 $\Theta(n)$。

考场代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,k,sx,sy,x[N],y[N];
double f[N],dis[N],pre[N];
double getdis(int x1,int y1,int x2,int y2){
	return sqrt(double(x1-x2)*(x1-x2)+double(y1-y2)*(y1-y2));
}
int q[N];
int main(){
	scanf("%d%d%d%d",&n,&k,&sx,&sy);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&x[i],&y[i]);
	}
	for(int i=1;i<=n;i++){
		dis[i]=getdis(sx,sy,x[i],y[i]);
	}
	for(int i=2;i<=n;i++){
		pre[i]=pre[i-1]+getdis(x[i],y[i],x[i-1],y[i-1]);
	}
	int head=0,tail=1;
	#define dp(i) f[i]+dis[i+1]-pre[i+1]
	for(int i=1;i<=n;i++){
		while(tail<=head&&dp(i-1)<=dp(q[head])){
			head--;
		}
		q[++head]=i-1;
		while(tail<=head&&q[tail]+k<i){
			tail++;
		}
		int j=q[tail];
		f[i]=dp(j)+pre[i]+dis[i];
	}
	printf("%.9lf\n",f[n]);
	return 0;
}
```

upd：发现挺多人都用了线段树？是线段树更好写吗？还是线段树不容易在边界条件出错？~~或者是因为天天爱跑步？~~

---

## 作者：yydfj (赞：8)

这是本蒟蒻第四十六次写的题解，如有错误点请好心指出！

## 问题简述

在平面直角坐标系中，圣诞老人的家在 $(sx,sy)$ 处，孩子 $i$ 的家在 $(a_i,b_i)$ 处，圣诞老人按孩子数字编号顺序每人送一份礼物，要一次性给 $x$ 个孩子送礼物，圣诞老人必须在家里带出至少 $x$ 份礼物送到他们家。但是，圣诞老人一次性最多只能带出 $m$ 份礼物，而且礼物送出去以后拿不回来，必须回到家补充礼物。

求圣诞老人从家出发，给所有孩子送完礼物后，再回到自己家所需的最小路程。

## 解法综述

记 $s1_i$ 表示从圣诞老人的家到孩子 $i$ 的家的距离，$s2_i$ 表示从孩子 $i-1$ 的家到孩子 $i$ 的家的距离的前缀和，则若圣诞老人一次性给孩子 $l \sim r$ 送礼物，所需的路程为 $s1_l+s1_r+s2_r-s2_l$。

设 $f_i$ 表示给前 $i$ 个孩子送完礼物所需的最小路程，则转移方程为 $f_i=\min \lbrace f_j+s1_{j+1}+s1_i+s2_i-s2_{j+1} \rbrace$，其中 $j$ 的范围为 $\max(0,i-m) \le j \le i-1$。

将确定的常量提出来，则 $f_i=\min \lbrace f_j+s1_{j+1}-s2_{j+1} \rbrace+s1_i+s2_i$，发现 $s1_{j+1}-s2_{j+1}$ 只与枚举的 $j$ 有关系，这样我们就可以使用单调队列优化，时间复杂度为 $O(n)$。

## 代码描述

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod=998244353;
long double sx,sy,a[200005],b[200005],s1[200005],s2[200005],f[200005];
ll n,m,q[200005];
int main()
{
	cin>>n>>m>>sx>>sy;
	for(int i=1;i<=n;i++) cin>>a[i]>>b[i];
	for(int i=1;i<=n;i++) s1[i]=sqrtl((a[i]-sx)*(a[i]-sx)+(b[i]-sy)*(b[i]-sy));//s1[i]表示从圣诞老人的家到孩子i的家的距离
	for(int i=2;i<=n;i++) s2[i]=s2[i-1]+sqrtl((a[i]-a[i-1])*(a[i]-a[i-1])+(b[i]-b[i-1])*(b[i]-b[i-1]));//s2[i]表示从孩子i-1的家到孩子i的家的距离的前缀和
	for(int i=1;i<=n;i++) f[i]=1e16;
	ll l=1,r=0;
	for(int i=1;i<=n;i++)
	{
		while(l<=r&&f[q[r]]+s1[q[r]+1]-s2[q[r]+1]>=f[i-1]+s1[i]-s2[i]) r--;//保证队列为升序
		q[++r]=i-1;
		while(l<=r&&q[l]+m<i) l++;//超出限制让队头出队
		f[i]=min(f[i],f[q[l]]+s1[q[l]+1]+s1[i]+s2[i]-s2[q[l]+1]);//方程转移
	}
	printf("%.7Lf",f[n]);
	return 0;
}
```

---

## 作者：BYR_KKK (赞：4)

[link](https://atcoder.jp/contests/abc334/tasks/abc334_f)

**思路**

注意到题目中走的顺序是按照编号走的。

所以我们实质上就是选几个间隔不超过 m 的点，在这些点回家。

考虑 dp 。

令 $dp_i$ 表示**走完** $i$ 号点后的最少步数。

考虑枚举前一个回家的点，显然这个点应该在 $i-m\sim i-1$ 之间，这里本质上是枚举点 $j$ ，使得走完 $j$ 以后回家，所以我们不应该枚举到 $i$ 。

令 $dis(i,j)$ 表示从 $i$ **按照编号顺序**走到 $j$ 的最短路程。

有：

$$dp_i=\min_{i-m}^{i-1}(dp_j+a_j+a_{j+1}+dis(j+1,i))$$

于是我们有了一个 $O(nm)$ 的做法。

我们发现这个式子除了 $dis(j+1,i)$ 这部分以外全都只和 $j$ 有关。

所以我们尝试把 $dis(j+1,i)$ 变得只和 $j$ 有关。

于是：

$$dp_i=\min_{i-m}^{i-1}(dp_j+a_j+a_{j+1}+dis(1,i)-dis(1,j+1)$$

$$dp_i=dis(1,i)+\min_{i-m}^{i-1}(dp_j+a_j+a_{j+1}-dis(1,j+1))$$

这样我们可以 $O(n)$ 地维护后面的部分，用单调队列或线段树均可，但是线段树是 $O(n\log n)$ 的。

**code**

```cpp

#include<bits/stdc++.h>
#define int long long
#define pii std::pair<int,int>
#define mk(P,Q) std::make_pair((P),(Q))
#define rep(j,k,z) for(int i=j;i<=k;i+=z)
#define per(j,k,z) for(int i=j;i>=z;i-=z)
#define fi first
#define se second
#define ok std::printf("OrzSouthern_Dynasty\n")
//#define double long double

int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9') x=x*10+(int)(c-'0'),c=getchar();
	return x*f;
}

const int maxn=2e5+10;

const double dinf=1000000000000000000.0;

pii b[maxn];//存储每个点的位置 

double a[maxn],d[maxn],dp[maxn];//a[i] 表示从家到 i 的最短路程，d[i] 表示从家按顺序走到 i 的最短路程

double dis(pii a,pii b){
	//求从 a 到 b 的欧氏距离 
	return std::sqrt(std::pow(a.fi-b.fi,2)+std::pow(a.se-b.se,2));
}

double calc(int j){
	if(j==0) return 0;
	return dp[j]+a[j]+a[j+1]-d[j+1];
}

std::deque<int>q;//优先队列中存的是下标 

signed main(){
	int n=read(),k=read();
	b[0]={read(),read()};
	for(int i=1;i<=n;i++){
		b[i]={read(),read()};
		a[i]=dis(b[0],b[i]);
		d[i]=d[i-1]+dis(b[i-1],b[i]);
	}	
	dp[1]=d[1];
	q.push_back(0);
	while(q.size()&&q.front()<=1-k) q.pop_front();
	q.push_back(1);
//	q.push_back(0);
//	std::printf("&&%.8f",dp[1]);
	for(int i=2;i<=n;i++){
		dp[i]=calc(q.front())+d[i];
//		std::printf("%lld %lld\n",i,q.front());
		while(q.size()&&q.front()<=i-k) q.pop_front();
		double c=calc(i);
		while(q.size()&&calc(q.back())>=c) q.pop_back();
		q.push_back(i);
//		std::printf("%.8f\n",dp[i]);
	}
	std::printf("%.20f",dp[n]+a[n]);//注意最后还得回家 
	return 0;
}

```

注意要先放一个 $0$ 到队列中，因为前面一些数可以先不回家。

---

## 作者：Register_int (赞：3)

设 $dp_i$ 为送完前 $i$ 个礼物的最小代价。转移时，我们要分出来一个长度小于等于 $m$ 的段，强制让圣诞老人回去补礼物再回来。设 $i$ 号点到家的距离为 $a_i$，从 $1$ 号点按顺序走到 $i$ 号点的距离为 $d_i$，则有转移：

$$dp_i=\min^{i-1}_{j=i-m}(dp_j+(a_j+a_{j+1})+(d_i-d_{j+1}))$$

变形一下：

$$dp_i=d_i+\min^{i-1}_{j=i-m}(dp_j+a_j+a_{j+1}-d_{j+1})$$

取 $\min$ 部分只和 $j$ 有关，可以用单调队列优化，时间复杂度 $O(n)$。由于圣诞老人还得回家，答案为 $dp_n+a_n$。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef double db;

const int MAXN = 2e5 + 10;

inline 
db dist(db a, db b, db c, db d) {
	return sqrt((a - c) * (a - c) + (b - d) * (b - d));
}

int n, m; db sx, sy, x[MAXN], y[MAXN];

db dp[MAXN], a[MAXN], d[MAXN];

inline 
db calc(int i) {
	return dp[i] + a[i] + a[i + 1] - d[i + 1];
}

deque<int> q;

int main() {
	scanf("%d%d%lf%lf", &n, &m, &sx, &sy), q.push_back(0);
	for (int i = 1; i <= n; i++) {
		scanf("%lf%lf", &x[i], &y[i]);
		a[i] = dist(sx, sy, x[i], y[i]), d[i] = d[i - 1] + dist(x[i - 1], y[i - 1], x[i], y[i]);
	}
	for (int i = 1; i <= n; i++) {
		dp[i] = dp[q[0]] + a[q[0]] + a[q[0] + 1] + d[i] - d[q[0] + 1];
		for (; !q.empty() && q[0] <= i - m; q.pop_front());
		for (; !q.empty() && calc(q.back()) >= calc(i); q.pop_back()); q.push_back(i);
	}
	printf("%.20lf", dp[n] + a[n]);
}
```

---

## 作者：rui_er (赞：3)

设 $f_i$ 表示假设只有编号为 $1\sim i$ 的点，此时的答案。$f_n$ 即为所求。

显然有：

$$
f_i=\min\limits_{i-k\le j < i}\{f_j+dis(s\to j+1\to j+2\to\cdots\to i)\}+dis(i\to s)
$$

当 $i\to i+1$ 时，大括号内部全局增加 $dis(i\to i+1)$，可以全局打标记后单调队列维护。

时间复杂度 $O(n)$。

```cpp
// Problem: F - Christmas Present 2
// Contest: AtCoder - UNIQUE VISION Programming Contest 2023 Christmas (AtCoder Beginner Contest 334)
// URL: https://atcoder.jp/contests/abc334/tasks/abc334_f
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x, y, z) for(int x = (y); x <= (z); ++x)
#define per(x, y, z) for(int x = (y); x >= (z); --x)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do {freopen(s".in", "r", stdin); freopen(s".out", "w", stdout);} while(false)
#define endl '\n'
using namespace std;
typedef long long ll;

mt19937 rnd(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
int randint(int L, int R) {
    uniform_int_distribution<int> dist(L, R);
    return dist(rnd);
}

template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}

template<int mod>
inline unsigned int down(unsigned int x) {
	return x >= mod ? x - mod : x;
}

template<int mod>
struct Modint {
	unsigned int x;
	Modint() = default;
	Modint(unsigned int x) : x(x) {}
	friend istream& operator>>(istream& in, Modint& a) {return in >> a.x;}
	friend ostream& operator<<(ostream& out, Modint a) {return out << a.x;}
	friend Modint operator+(Modint a, Modint b) {return down<mod>(a.x + b.x);}
	friend Modint operator-(Modint a, Modint b) {return down<mod>(a.x - b.x + mod);}
	friend Modint operator*(Modint a, Modint b) {return 1ULL * a.x * b.x % mod;}
	friend Modint operator/(Modint a, Modint b) {return a * ~b;}
	friend Modint operator^(Modint a, int b) {Modint ans = 1; for(; b; b >>= 1, a *= a) if(b & 1) ans *= a; return ans;}
	friend Modint operator~(Modint a) {return a ^ (mod - 2);}
	friend Modint operator-(Modint a) {return down<mod>(mod - a.x);}
	friend Modint& operator+=(Modint& a, Modint b) {return a = a + b;}
	friend Modint& operator-=(Modint& a, Modint b) {return a = a - b;}
	friend Modint& operator*=(Modint& a, Modint b) {return a = a * b;}
	friend Modint& operator/=(Modint& a, Modint b) {return a = a / b;}
	friend Modint& operator^=(Modint& a, int b) {return a = a ^ b;}
	friend Modint& operator++(Modint& a) {return a += 1;}
	friend Modint operator++(Modint& a, int) {Modint x = a; a += 1; return x;}
	friend Modint& operator--(Modint& a) {return a -= 1;}
	friend Modint operator--(Modint& a, int) {Modint x = a; a -= 1; return x;}
	friend bool operator==(Modint a, Modint b) {return a.x == b.x;}
	friend bool operator!=(Modint a, Modint b) {return !(a == b);}
};

const int N = 2e5 + 5;

int n, k, sx, sy, x[N], y[N];
double dp[N], tag;
deque<tuple<int, double>> dq;

inline double sq(double x) {return x * x;}
inline double dis(double ax, double ay, double bx, double by) {return sqrt(sq(ax - bx) + sq(ay - by));}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> k >> sx >> sy;
    rep(i, 1, n) cin >> x[i] >> y[i];
    x[0] = sx; y[0] = sy;
    dq.emplace_back(0, dis(sx, sy, x[1], y[1]));
    rep(i, 1, n) {
        while(!dq.empty()) {
            auto [id, pt] = dq.front();
            if(i - id > k) dq.pop_front();
            else break;
        }
        auto [id, pt] = dq.front();
        pt += tag;
        dp[i] = pt + dis(x[i], y[i], sx, sy);
        tag += dis(x[i], y[i], x[i + 1], y[i + 1]);
        while(!dq.empty()) {
            auto [id, pt] = dq.back();
            if(pt + tag > dp[i] + dis(sx, sy, x[i + 1], y[i + 1])) dq.pop_back();
            else break;
        }
        dq.emplace_back(i, dp[i] + dis(sx, sy, x[i + 1], y[i + 1]) - tag);
    }
    cout << fixed << setprecision(15) << dp[n] << endl;
    return 0;
}
```

---

## 作者：Genius_Star (赞：3)

### 题意：

有一个以 $xy$ 平面表示的小镇，圣诞老人和 $N$ 个编号为 $1$ 至 $N$ 的孩子住在那里。

圣诞老人的家在坐标 $(S_x,S_y)$ 处，第 $i$ 个孩子的家在 $(X_i,Y_i)$，圣诞老人想按数字顺序给 $N$ 个孩子每人送一份礼物。

要给第 $i$ 个孩子送礼物，圣诞老人必须带着至少一份礼物去第 $i$ 个孩子的家，但是，圣诞老人一次最多只能带 $K$ 件礼物，而且他必须回到自己家补充礼物（圣诞老人家有足够的礼物）。

求圣诞老人离开家，给所有 $N$ 个孩子送礼物，再返回家的最小路程。

### 思路：

考虑动态规划算法，定义 $dp_i$ 表示给前 $i$ 个孩子送完礼物的最小路程，然后枚举一个回家取礼物的中转点 $j$，则状态转移方程为：

$$dp_i=\min\limits_{j=i-m}^{i-1} dp_j + dist(S,H_j) + dist(S,H_{j+1}) + S(j+2,i)$$

其中 $S$ 表示圣诞老人的家，$H_i$ 表示第 $i$ 个孩子的家，$dist(X,Y)$ 表示两点之间的路程长度，$S(l,r)$ 表示从第 $l$ 个孩子走到底 $r$ 个孩子的路程长度。

那么设 $S_i$ 表示从第 $1$ 个孩子家到第 $i$ 个孩子家的路程长度，则：

$$S(l,r)=S_r-S_{l-1}$$

那么状态转移方程化为：

$$dp_i=\min\limits_{j=i-m}^{i-1} dp_j + dist(S,H_j) + dist(S,H_{j+1}) + S_i - S_{j+1}$$

然后将其必须项提下来：

$$dp_i=S_i + \min\limits_{j=i-m}^{i-1} dp_j + dist(S,H_j) + dist(S,H_{j+1}) - S_{j+1}$$

后面完全跟 $j$ 自己相关，则直接线段树优化一下即可。

最后因为圣诞老人还要回家，所以答案为：

$$dp_n+dist(S,H_n)$$

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const ll N=200200,INF=1e17;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
struct St{
	db x,y;
}a[N];
struct Node{
	ll l,r;
	db data;
}X[N<<2];
ll n,k,x,y;
db s[N],dp[N];
db dist(ll x,ll y){
	return sqrt((a[x].x-a[y].x)*(a[x].x-a[y].x)+(a[x].y-a[y].y)*(a[x].y-a[y].y));
}
void pushup(ll k){
	X[k].data=min(X[k<<1].data,X[k<<1|1].data);
}
void build(ll k,ll l,ll r){
	X[k].l=l,X[k].r=r;
	X[k].data=INF;
	if(l==r)
	  return ;
	ll mid=(l+r)>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
}
void add(ll k,ll i,db v){
	if(X[k].l==i&&i==X[k].r){
		X[k].data=v;
		return ;
	}
	ll mid=(X[k].l+X[k].r)>>1;
	if(i<=mid)
	  add(k<<1,i,v);
	else
	  add(k<<1|1,i,v);
	pushup(k);
}
db qurey(ll k,ll l,ll r){
	if(X[k].l==l&&r==X[k].r)
	  return X[k].data;
	ll mid=(X[k].l+X[k].r)>>1;
	if(r<=mid)
	  return qurey(k<<1,l,r);
	else if(l>mid)
	  return qurey(k<<1|1,l,r);
	else
	  return min(qurey(k<<1,l,mid),qurey(k<<1|1,mid+1,r));
}
int main(){
	n=read(),k=read();
	for(int i=0;i<=n;i++){
		x=read(),y=read();
		a[i]={(db)x,(db)y};
	}
	for(int i=1;i<=n;i++)
	  s[i]=s[i-1]+dist(i-1,i);
	build(1,0,n);
	dp[0]=0;
	add(1,0,0);
	for(int i=1;i<=n;i++){
		ll l=max(0ll,i-k),r=i-1;
		dp[i]=s[i]+qurey(1,l,r);
		add(1,i,dp[i]+dist(0,i)+dist(0,i+1)-s[i+1]);
//		printf("%.6lf\n",dp[i]);
	}
	printf("%.6lf\n",dp[n]+dist(0,n));
	return 0;
}
```


---

## 作者：truly_handsome (赞：2)

做法：单调队列优化 dp。

令 $f_i$ 表示以 $i$ 为最后一个点的答案，$dis(i,j)$ 代表从 $i$ 走到 $j$ 的路径长度。

可以想到一个朴素的 $n^2$ 做法。

$f_i = dis(st,i)+min(f_j+dis(st,j+1)+dis(j+1,i))$ 其中 $i-j \lt k$。

因为 $f_i$ 表示以 $i$ 为最后一个点的答案，所以计算距离要从 $j+1$ 开始。

观察到该式子满足单调性，就可以使用单调队列优化它。

```
# include <bits/stdc++.h>
# define pb push_back
# define int long long
# define db long double
using namespace std;

int n, k;

db s[200005], f[200005], x[200005], y[200005], sx, sy;

// dis(st,id)
db dis(int id){
	return sqrtl((x[id]-sx)*(x[id]-sx) + (y[id]-sy)*(y[id]-sy));
}

// dis(l,r)
db w(int l, int r){
	return s[r] - s[l];
}

signed main(){
	scanf("%lld%lld%Lf%Lf", &n, &k, &sx, &sy);
	x[0] = sx; y[0] = sy;
	for (int i = 1;i <= n;i++){
		scanf("%Lf%Lf", &x[i], &y[i]);
		s[i] = s[i-1] + sqrtl((x[i]-x[i-1])*(x[i]-x[i-1]) + (y[i]-y[i-1])*(y[i]-y[i-1]));
	}
	x[n+1]=x[n]; y[n+1]=y[n];
	f[0] = 0.0;
	deque <int> q;
	q.pb(0);
	for (int i = 1;i <= n;i++){
		if (q.front()+k < i) q.pop_front();
		int j = q.front();
		f[i] = f[j] + dis(j+1) + w(j+1, i) + dis(i);
		while (q.size() && f[q.back()]+dis(q.back()+1)+w(q.back()+1, i+1) > f[i]+dis(i+1)) q.pop_back();
		q.pb(i);
	}
	printf("%.6Lf", f[n]);
	return 0;
}

```


---

## 作者：035966_L3 (赞：2)

先考虑最坏情况：送一个礼物，回去取一次。

接下来定义 $e_i$ 为：送完第 $i$ 个礼物后，直接去送第 $i+1$ 个礼物（而不回去取）所少走的路程。

令 $n=N-1$，$k=K-1$（大写字母表示本题的数据），于是我们看到了 [P2627](https://www.luogu.com.cn/problem/P2627)。

将最坏情况的距离减去最多省去的距离，就结束了！

**AC Code：**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
long double aa[200012],bb[200012];
long double dis(int x,int y)
{
    long double res=sqrt((aa[y]-aa[x])*(aa[y]-aa[x])+(bb[y]-bb[x])*(bb[y]-bb[x]));
    return res;
}
long double f[200012],hz[200012],b[200012],a[800012];
int n,k;
const int PTA=262143;
long double fm(int l,int r,int ii,int aa,int xb)
{
    while(1)
    {
	    if(l==ii&&r==aa) return a[xb];
	    int lmid=(ii+aa)>>1,rmid=lmid+1;
	    if(l>=rmid) {ii=rmid,xb<<=1,xb++;continue;}
	    if(r<=lmid) {aa=lmid,xb<<=1;continue;}
	    if(r==aa) return max(a[(xb<<1)+1],fm(l,lmid,ii,lmid,(xb<<1)));
	    if(l==ii) return max(a[(xb<<1)],fm(rmid,r,rmid,aa,(xb<<1)+1));
	    return max(fm(l,lmid,ii,lmid,(xb<<1)),fm(rmid,r,rmid,aa,(xb<<1)+1));
    }
}
void gn(int pos,long double nval)
{
	int vpos=PTA+pos,spos=vpos;
	a[vpos]=nval;
	while(spos>1) spos>>=1,a[spos]=max(a[(spos<<1)],a[(spos<<1)+1]);
}
void qs(int p)
{
	gn(p%(k+1)+1,f[p]+hz[p+1]);
}
signed main()
{
	cin>>n>>k>>aa[0]>>bb[0];
    for(int i=1;i<=n;i++)
        cin>>aa[i]>>bb[i];
    long double ans=0;
    for(int i=1;i<=n;i++)
        ans+=2*dis(0,i);
	for(int i=1;i<=n-1;i++)
		b[i+1]=dis(0,i)+dis(0,i+1)-dis(i,i+1);
    // b[1] = 0，默认不选
    k--;
	for(int i=n;i>=1;i--)
		hz[i]=hz[i+1]+b[i];
	for(int i=2;i<=k+1;i++)
		f[i]=f[i-1]+b[i-1];
	for(int i=1;i<=k+1;i++)
		qs(i);
	for(int i=k+2;i<=n+1;i++)
	{
		f[i]=fm(1,PTA+1,1,PTA+1,1)-hz[i];
		qs(i);
	}
	cout<<fixed<<setprecision(50)<<ans-f[n+1];
	return 0;
}
```

---

## 作者：lizicheng3042 (赞：2)

说实话时间够的话应该能做出来，可惜 B 题浪费了很多时间，~~而且我 B 题还没做出来~~。  
好了，下面我们开始说这道题。
## 题目简述
给定 $n$ 个点，要求从原点（即 $0$ 号节点）开始依次经过这些点，并最终回到原点。  
特殊的是，你被要求每经过至多 $k$ 个点就必须回到原点一次，然后才能继续经过下面的点。    
## 思路分析   
这道题的首先一眼看上去，发现是可以写成动态规划的。我们假设 $dp[i][j]$ 表示到达第 $i$ 个点，还能再经历 $j$ 个点的最小代价，那么可以写出一个转移方程 ：
$$dp[i][j]=dp[i-1][j+1]+dis(i-1,i)$$
$$dp[i][k-1]=\min(dp[i-1][j])+dis(i-1,0)+dis(i,0)$$
显然，这个式子是正确的（对于第二个式子，达到 $i+1$ 后也要留下一个礼物）。  
但是我们看一眼时间复杂度，发现这个做复杂度为 $O(nk)$，而对于一个 $1\le n,k\le 2\times 10^5$ 的数据来说，这是远远不够的，并且空间也会爆掉。所以，我们需要考虑对这个转移进行优化。  
考虑到如果在转移状态里加上还能经历几个点一定是会爆掉的，我们只能试着把这个信息压在第一维里。  
这时，我们就想到可以用 $dp[i]$ 来表示到达第 $i$ 个节点后回到原点一次的最小代价，然后，我们再预处理距离的前缀和（设从原点以及经过个点直到达到 $i$ 的距离为 $pred_i$），这样我们就得到一个空间复杂度更优秀的转移方程：
$$dp[i]=dp[i-j]+dis(i-j,0)+dis(i-j+1,0)+pred[i-1]-pred[i-j](1\le j\le k)$$
然而现在时间复杂度仍然为 $O(nk)$。经过观察，我们发现，当某个位置要回原点的时候，实际上是把 $dis(i,i+1)$ 变为了 $dis(i,0)+dis(i+1,0)$，而不会影响其他位置，这提醒我们这道题可以维护一个代价的最小值。由此，我们想到拿单调队列来维护这个信息。
## 最终实现
综上所述，我们可以用单调队列来维护使 $dp[i]$最小的转移值。比如转移到 $i$ 时，我们先从队头排出编号小于 $i-k$ 的点，然后取队首作为最佳转移点，接着我们再把 $i$ 位置加进队列里，作为一个决策点。最后我们可以求出 $dp[n]$，本题结束。
## 代码实现
```cpp
#include<cstdio>
#include<cmath>
using namespace std;
typedef long long ll;
int n,k;
ll posx[200005],posy[200005],tm[200005],head=1,tail;
double dp[200005],val[200005],pre[200005];
double dis(int a)//即dis(a,0)
{
	if(a==0)
	return 0;
	return sqrt((posx[0]-posx[a])*(posx[0]-posx[a])+(posy[0]-posy[a])*(posy[0]-posy[a]));
}
int main()
{
	scanf("%d%d",&n,&k);
	for(int a=0;a<=n;a++)
	{
		scanf("%lld%lld",&posx[a],&posy[a]);

	}
	for(int a=0;a<n;a++)
	{
		val[a]=sqrt((posx[a]-posx[a+1])*(posx[a]-posx[a+1])+(posy[a]-posy[a+1])*(posy[a]-posy[a+1]));
		if(a)
		val[a]+=val[a-1];		
//		printf("(%lf)",val[a]);
	}
	tail=1;
	for(int a=1;a<=n;a++)
	{
		while(tm[head]<a-k&&head<=tail)
			head++;
		if(a==tm[head]+1)
		dp[a]=dp[a-1]+dis(a-1)+dis(a);
		else
		dp[a]=dp[tm[head]]+val[a-1]-val[tm[head]]+dis(tm[head])+dis(tm[head]+1);
		while(head<=tail&&dis(a+1)+dis(a)+dp[a]<=dis(tm[tail])+dis(tm[tail]+1)+dp[tm[tail]]+val[a]-val[tm[tail]])
			tail--;
		tm[++tail]=a;
	}
	printf("%.6lf",dp[n]+dis(n));
	return 0;
}
/*

*/
```

  

---

## 作者：osfly (赞：1)

### some interesting things

赛时因为 B 题卡了半小时导致最后没时间调 F /fn

赛后 10min 就调出来了。

### 正文

考虑 dp。

设 $f_i$ 为从起点按照顺序走到 $i$ 号点并返回的路径长度。

那么我们就有：

$f_i=f_j+\text{dis}_{1\rightarrow j+1}+\text{dis}_{j+1\rightarrow j+2}+...+\text{dis}_{i-1\rightarrow i}+\text{dis}_{i\rightarrow 1}(i-j\leq k)$

可以使用前缀和预处理所有的 $\text{dis}$。

直接转移是 $O(nk)$ 的，用线段树加速转移过程可以做到 $O(n\log n)$。

也可以使用单调队列加速到 $O(n)$，但是因为本人每一次写单调队列都会炸所以使用了线段树。

转移的时候请注意边界问题。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define lb long double

const int N=2e5+10;
const lb inf=1e18;

int n,k;

lb dis(lb x,lb y,lb xx,lb yy)
{
	return sqrt((x-xx)*(x-xx)+(y-yy)*(y-yy));
}

lb sx,sy;
lb x[N],y[N];
lb back[N],go[N];

lb f[N];

struct seg
{
	struct node
	{
		int l,r;
		lb val;
	}t[N<<2];
	#define ls (k<<1)
	#define rs (k<<1|1)
	#define L t[k].l
	#define R t[k].r
	#define mid ((L+R)>>1)
	void pushup(int k)
	{
		t[k].val=min(t[ls].val,t[rs].val);
	}
	void build(int k,int l,int r)
	{
		L=l,R=r;
		if(l==r)
		{
			t[k].val=inf;
			return ;
		}
		build(ls,l,mid);
		build(rs,mid+1,r);
		pushup(k);
	}
	void update(int k,int x,lb num)
	{
		if(L==R)
		{
			t[k].val=num;
			return ;
		}
		if(x<=mid) update(ls,x,num);
		if(x>mid) update(rs,x,num);
		pushup(k);
	}
	lb query(int k,int l,int r)
	{
		if(l<=L&&R<=r) return t[k].val;
		lb res=inf;
		if(l<=mid) res=min(res,query(ls,l,r));
		if(r>mid) res=min(res,query(rs,l,r));
		return res;
	}
	#undef ls
	#undef rs
	#undef L
	#undef R
	#undef mid
}tree;

int main()
{
	scanf("%d%d",&n,&k);
	scanf("%Lf%Lf",&sx,&sy);
	for(int i=1;i<=n;i++) scanf("%Lf%Lf",&x[i],&y[i]),back[i]=dis(sx,sy,x[i],y[i]);
	x[0]=sx,y[0]=sy;
	for(int i=1;i<=n;i++) go[i]=go[i-1]+dis(x[i-1],y[i-1],x[i],y[i]);
	tree.build(1,0,n);
	tree.update(1,0,0);
	f[1]=back[1]*2;
	tree.update(1,1,f[1]-go[2]+back[2]);
	for(int i=2;i<=n;i++)
	{
		f[i]=tree.query(1,max(0,i-k),i-1)+go[i]+back[i];
		tree.update(1,i,f[i]-go[i+1]+back[i+1]);
	}
	printf("%.10Lf",f[n]);
	return 0;
}
```

---

## 作者：yanhao40340 (赞：1)

## 前言

考场上 B 题浪费了太多时间了，导致 F 题赛后 10 分钟才写完 QWQ。

## 题意

给定平面上 $n$ 个目标点 $a_{1,2,\cdots,n}$ 和一个起始点 $S$。当连续到达最多 $k$ 个目标点时就要返回 $S$ 点。要求从 $S$ 点出发，顺次到达每一个目标点，最后回到 $S$ 点。求最小路程。

数据范围：$1 \le n,k \le 2 \times 10^5$。

## 分析

如果不考虑 $k$ 的限制，那么直接顺次到达每一个目标点的方案一定是最优的，将这个路程记为 $S_0$。

记到达第 $i$ 个目标点后返回 $S$ 点时的**额外代价**为 $f_i$，那么有

$$f_i=\operatorname{dist}(S,a_i)+\operatorname{dist}(S,a_{i+1})-\operatorname{dist}(a_i,a_{i+1})$$

其中 $\operatorname{dist}(a,b)$ 表示 $a$ 到 $b$ 的距离。根据三角不等式知，$f_i \ge 0$。

考虑动态规划。

记 $dp_i$ 表示到达第 $i$ 个目标点后返回的**额外代价**，那么有

$$dp_i=\min^{i-1}_{j=i-k} dp_j+\operatorname{dist}(a_i,a_{i+1})$$

直接求是 $\Theta(n^2)$ 的。

考虑用线段树优化取 $\min$ 的过程，可以达到 $\Theta(n \log n)$ 的时间复杂度。

## 代码

```cpp
//已省略快读快输
#include <iostream>
#include <cmath>
#define ls (o<<1)
#define rs (o<<1|1)
#define mid (L+R>>1)
using namespace std;
const int maxn=2e5+5;
struct node{int x,y;} a[maxn];
double dis[maxn],f[maxn],dp[maxn],tr[maxn<<2];
double calc(double xx,double yy,double xxx,double yyy){
	return sqrt((xx-xxx)*(xx-xxx)+(yy-yyy)*(yy-yyy));
}
void update(int o,int L,int R,int x,double k){
	if (L==R){
		tr[o]=k;
		return;
	}
	if (x<=mid) update(ls,L,mid,x,k);
	else update(rs,mid+1,R,x,k);
	tr[o]=min(tr[ls],tr[rs]);
	return;
}
double query(int o,int L,int R,int l,int r){
	if (l<=L&&R<=r) return tr[o];
	double ans=1e18;
	if (l<=mid) ans=min(ans,query(ls,L,mid,l,r));
	if (r>mid) ans=min(ans,query(rs,mid+1,R,l,r));
	return ans;
}
int main(){
	int n=read(),k=read();
	for (int i=0;i<=(n+1<<2);++i) tr[i]=1e18;
	int tx=read(),ty=read();
	for (int i=1;i<=n;++i)
		a[i].x=read()-tx,a[i].y=read()-ty;
	for (int i=1;i<=n;++i) dis[i]=calc(a[i].x,a[i].y,0,0);
	for (int i=1;i<n;++i) f[i]=dis[i]+dis[i+1]-calc(a[i].x,a[i].y,a[i+1].x,a[i+1].y);
	double sum=calc(a[1].x,a[1].y,0,0)+calc(a[n].x,a[n].y,0,0);
	for (int i=1;i<n;++i) sum+=calc(a[i].x,a[i].y,a[i+1].x,a[i+1].y);
	dp[0]=0;update(1,1,n+1,1,0);
	for (int i=1;i<=n;++i){
		dp[i]=query(1,1,n+1,max(1,i-k+1),max(1,i))+f[i];
		update(1,1,n+1,i+1,dp[i]);
	}
	printf("%.12lf",dp[n]+sum);
	return 0;
}
```

## 后记

据说单调队列可以做到 $\Theta(n)$ 的复杂度？

---

## 作者：cjh20090318 (赞：1)

有一定难度的 ABC F。

## 题意

翻译很清楚。

标签：动态规划、线段树。

## 分析

设 $f_i$ 表示到第 $i$ 个点后回到原点（即 $0$ 号）的最小距离。

在第 $i$ 个点时，第 $i-1$ 个点才回到原点，需要重新出发，即加上 $0$ 号点到 $i$ 号点的距离；而对于 $\forall j \in[i-k,i-1)$，这些点已经出发到了第 $i-1$ 个点，即加上 $i-1$ 号点到 $i$ 号点的距离。

区间加和，区间查询，这个直接用线段树维护即可。

时间复杂度 $O(n \log n)$。

## 代码

```cpp
//the code is from chenjh
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#define MAXN 200002
using namespace std;
typedef long long LL;
typedef unsigned int ui;
using cu=const unsigned int;
int n,k;
int X[MAXN],Y[MAXN];
double dis(const int X1,const int Y1,const int X2,const int Y2){return sqrt((LL)(X1-X2)*(X1-X2)+(LL)(Y1-Y2)*(Y1-Y2));}//求两个坐标之间的距离。
#define lson (rt<<1)
#define rson (rt<<1|1)
double mn[MAXN<<2],lazy[MAXN<<2];//线段树维护最小值。
void pd(cu rt,cu l,cu r){
	mn[lson]+=lazy[rt],lazy[lson]+=lazy[rt];
	mn[rson]+=lazy[rt],lazy[rson]+=lazy[rt];
	lazy[rt]=0;
}
void update(cu rt,cu l,cu r,cu L,cu R,const double&val){
	if(L<=l && r<=R){mn[rt]+=val,lazy[rt]+=val;return;}
	pd(rt,l,r);
	ui mid=(l+r)>>1;
	if(L<=mid) update(lson,l,mid,L,R,val);
	if(mid<R) update(rson,mid+1,r,L,R,val);
	mn[rt]=min(mn[lson],mn[rson]);
}
double query(cu rt,cu l,cu r,cu L,cu R){
	if(L<=l && r<=R) return mn[rt];
	pd(rt,l,r);
	ui mid=(l+r)>>1;
	double ret=1e18;
	if(L<=mid) ret=min(ret,query(lson,l,mid,L,R));
	if(mid<R) ret=min(ret,query(rson,mid+1,r,L,R));
	return ret;
}
int main(){
	scanf("%d%d",&n,&k);
	for(int i=0;i<=n;i++) scanf("%d%d",&X[i],&Y[i]);
	for(int i=1;i<=n;i++){
		if(i>1) update(1,0,n,max(i-k,0),i-2,dis(X[i-1],Y[i-1],X[i],Y[i]));//回到原点后又出发的点，
		update(1,0,n,i-1,i-1,dis(X[0],Y[0],X[i],Y[i]));//才回到原点的再出发。
		update(1,0,n,i,i,query(1,0,n,max(i-k,0),i-1)+dis(X[0],Y[0],X[i],Y[i]));//寻找距离最小值然后回到原点。
	}
	printf("%.6lf\n",query(1,0,n,n,n));
	return 0;
}
```



---

## 作者：FiraCode (赞：1)

## 思路:

由于是按顺序来发礼物，那么显然可以考虑 DP。

那么设 $f_{i}$ 表示发了前 $i$ 个，并且当前在 $0$ 的最小的距离花费，$dist(i,j)$ 表示第 $i$ 个点和第 $j$ 个点的距离，第 $0$ 个点表示起点，$cost(i, j)$，表示 $i$ 按顺序走到 $j$ 点的距离和。

那么 $f_{i} = \min \{f_j + dist(0,j + 1) + cost(j + 1, i) + dist(i, 0)\}$。

然后因为 $cost$ 既有 $i$ 也有 $j$ 不太好维护，所以考虑拆成前缀和：

$f_{i} = \min \{f_j + dist(0,j + 1) + sum_i-sum_j + dist(i, 0)\}$。

然后把与 $i$ 有关的提出来：

$f_{i} = \min \{f_j + dist(0,j + 1)-sum_j\} + dist(i, 0) + sum_i$。


于是 $\min$ 中的直接用线段树做即可（其实也可以单调队列滑动窗口）。

## Code：

```cpp
#include <bits/stdc++.h>

using namespace std;

int n, k;
pair<double, double> a[200010];
double f[200010], s[200010];
double tr[800010];

void modify(int u, int l, int r, int x, double d) {
    if (l == r) {
        tr[u] = d;
        return;
    }

    int mid = (l + r) >> 1;

    if (x <= mid) modify(u << 1, l, mid, x, d);
    else modify(u << 1 | 1, mid + 1, r, x, d);

    tr[u] = min(tr[u << 1], tr[u << 1 | 1]);
}

double query(int u, int l, int r, int ql, int qr) {
    if (l >= ql && r <= qr) return tr[u];

    int mid = (l + r) >> 1;
    double res = 1e18;

    if (ql <= mid) res = min(res, query(u << 1, l, mid, ql, qr));
    if (qr > mid) res = min(res, query(u << 1 | 1, mid + 1, r, ql, qr));

    return res;
}

double dist(pair<double, double> a, pair<double, double> b) {
    return sqrt((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second));
}

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 0; i <= n; ++i) scanf("%lf%lf", &a[i].first, &a[i].second);

    for (int i = 0; i <= n; ++i) f[i] = 1e18;
    for (int i = 1; i <= n; ++i) s[i] = s[i - 1] + dist(a[i - 1], a[i]);

    f[0] = 0;
    modify(1, 0, n, 0, f[0] + dist(a[0], a[1]) - s[1]);

    for (int i = 1; i <= n; ++i) {
        f[i] = query(1, 0, n, max(0, i - k), i - 1) + s[i] + dist(a[i], a[0]);
        if (i < n) modify(1, 0, n, i, f[i] - s[i + 1] + dist(a[i + 1], a[0]));
    }

    printf("%.15lf\n", f[n]);
    return 0;
}
```

---

## 作者：hycqwq (赞：1)

小蒟蒻想不出 $O(n)$ 的解法，来交一发二维 dp 加优化的题解。

## Problem

圣诞老人要按顺序给 $n$ 个人送礼物，每个人（包括它自己）家都有一个坐标，而圣诞老人手上最多只能拿 $k$ 个礼物（这就意味着他可能要在送完某些人之后回家补充礼物），求他给所有人送完礼物**再回到自己家**所需要走的最短距离。

## Solution

考虑 $dp_{i, j}$ 表示当前已经送完了前 $i$ 个人的礼物，（送完第 $i$ 个人之后）手上还有 $j$ 个礼物，当前在第 $i$ 个人的家中，需要走的最短路程。

我们用 $dis(a, b)$ 表示第 $a, b$ 个人的家之间的距离，其中第 $0$ 个人是圣诞老人。

同时，一个数组的下标为负数 $-i$，表示这个数组的倒数第 $i$ 个元素。

为了方便，我们认为圣诞老人每次补充礼物都会将礼物数量补充到 $k$ 个。

### 1. 初值

对于任意 $1 \le i \le n, 1 \le j \le k$ 有 $dp_{i, j} = +\infty$。

另外，$dp_{1, k - 1} = dis(0, 1)$。

### 2. 递推

在前往第 $i$ 个人家送礼物时，有两种选择：

1. 直接从第 $i - 1$ 个人家去送，此时对于任意 $1 \le j \le k - 1$ 有：
   $$dp_{i, j - 1} = \min(dp_{i, j - 1}, dp_{i - 1, j} + dis(i - 1, i))$$
2. 先回家补充礼物再去送，此时对于任意 $0 \le j \le k - 1$ 有：
   $$dp_{i, k - 1} = \min(dp_{i, k - 1}, dp_{i - 1, j} + dis(i - 1, 0) + dis(0, i))$$

注：

1. 这里的 $j$ 表示**上一次**送完礼物后（即在送本次礼物之前），手上还有的礼物数量。
2. 当 $j = 0$ 时，必须先回家补充礼物（这不是废话吗）。

### 3. 答案

由于我们增加了「我们认为圣诞老人每次补充礼物都会将礼物数量补充到 $k$ 个」这一限制，所以在计算答案时需要枚举所有可能的礼物数量，取路程的最小值，最后加上圣诞老人回家的路程，即

$$ans = (\min_{j = 0}^{k - 1} dp_{n, j}) + dis(n, 0)$$

### 4. 优化

现在我们的这个算法的复杂度为 $O(nk)$，显然是会超时的（当然还有内存超限，但是用个滚动数组就可以解决），于是我们要考虑一下优化方法。

我们发现，（在 $i$ 相等时）当存在剩余礼物比当前更多，而所需的最小路程比当前更小或相等时，我们没有必要对其最小路程进行计算，因为我们已经可以确定当前方案一定不是最优的方案。

所以我们设定数组 $v_i$ 来从大到小（请记住这一性质，后续优化会用到）存储送完前 $i$ 个人后，可能是最优方案的剩余礼物数 $j$。

换句话说，只有 $dp_{i, v_{i, 1}}, dp_{i, v_{i, 2}}, \cdots, dp_{i, v_{i, -1}}$ 可能是最优的答案，所以对于下一次的递推我们也只对 $v_i$ 中的 $j$ 进行递推。

特别地，$v_1 = \{k - 1\}$。

为了实现这个优化，我们在更新 $dp_i$ 时需按照 $j$ 从大到小的顺序进行更新。

关于数组 $v_i$ 的具体求法，请参考代码。

---

接下来我们又要回到最开始的问题上：初值。

为什么要在这个时候考虑初值的问题呢？我们在上面提到了：

> 当然还有内存超限，但是用个滚动数组就可以解决

于是这样就出现了一个新的问题：如果对于每个 $i$，都要对 $dp_i$ 中的所有位置赋初值 $+\infty$，那么时间复杂度不就又变成了 $O(nk)$ 吗？

要解决这个问题，我们需要考虑我们对 $dp$ 数组的更新。

我们再次回到上文。（省略了一些无关紧要的部分，下同）

> 1. ……，此时对于任意 $1 \le j \le k - 1$ 有：
>    $$dp_{i, \color{red}{j - 1}} = \cdots$$
> 2. ……，此时对于任意 $0 \le j \le k - 1$ 有：
>    $$dp_{i, \color{red}{k - 1}} = \cdots$$

请注意上面的标红部分。可以发现，对于所有 $1 \le j \le k - 1$，$dp_{i, j - 1}$ 只会被更新**一次**，只有 $dp_{i, k - 1}$ 会被更新多次。

所以我们只需要对 $dp_{i, k - 1}$ 设置初值 $+\infty$ 即可。

---

（下面是一个很小的优化，如果不加不会对时间复杂度构成太大的影响，但还是希望各位看一下，代码中也加上了这个优化）

但是，真的到此为止了吗？

我们对于第二种情况的状态转移方程是：

> 2. ……，此时对于任意 $0 \le j \le k - 1$ 有：
>    $$dp_{i, k - 1} = \min(dp_{i, k - 1}, dp_{i - 1, j} + dis(i - 1, 0) + dis(0, i))$$

我们可以将这里的状态转移方程改写为：

$$dp_{i, k - 1} = \min(dp_{i, k - 1}, (\min_{j = 0}^{k - 1} dp_{i - 1, j}) + dis(i - 1, 0) + dis(0, i))$$

而对于最小的 $dp_{i, j}$，一定有 $j$ 最小，因为比它更小的一定会被排除，不会用于本轮更新。

所以我们可以得到：

$$dp_{i, k - 1} = \min(dp_{i, k - 1}, dp_{i - 1, v_{i - 1, -1}} + dis(i - 1, 0) + dis(0, i))$$

于是，我们把 $dp_{i, k - 1}$ 的更新也减少到了 $1$ 次。

---

加了这三个优化后，代码跑得飞快，最慢的点只需约 $115\text{ms}$ 即可通过此题。

## Code

```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cstring>
#include <cctype>
#include <cmath>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <map>
#include <set>
#include <iomanip>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
const int infi = 0x3f3f3f3f;
const ll infl = 0x3f3f3f3f3f3f3f3fll;
#define elif else if
#define il inline

int n, k;
ll sx, sy;
ll x[200005], y[200005];
double dp[2/*200005*/][200005]; // dp[i][j] 表示送完前i个人，手上还有j礼物，最少要走多远（当前在i号人的家中）
vector<int> v[2/*200005*/]; // v[i] 表示送完前i个人，只可能剩多少个礼物（如果被完爆，即当存在剩下礼物更多，而走的路可以更少或相同时，就不计入）

double dis(ll x1, ll y1, ll x2, ll y2)
{
    return sqrtl((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

int main()
{
    cin >> n >> k >> sx >> sy;
    for (int i = 1; i <= n; i++)
        cin >> x[i] >> y[i];
    dp[1][k - 1] = dis(sx, sy, x[1], y[1]);
    v[1].push_back(k - 1);
    for (int i = 2; i <= n; i++)
    {
        double mnd = infl; // 目前剩余礼物比j多的情况中，最少需要走多少路
        dp[i % 2][k - 1] = infl;
        v[i % 2].clear();
        // 当前有j个礼物，在(x[i-1],y[i-1])
        // 如果先回家拿
        int j = v[(i - 1) % 2].back(); // 剩余礼物最少的，走的路一定是最少的，因为如果走的路更多一定会被排除
        dp[i % 2][k - 1] = min(dp[i % 2][k - 1], dp[(i - 1) % 2][j] + dis(x[i - 1], y[i - 1], sx, sy) + dis(sx, sy, x[i], y[i]));
        mnd = min(mnd, dp[i % 2][k - 1]);
        v[i % 2].push_back(k - 1);
        // 如果直接从这里去送
        for (auto j : v[(i - 1) % 2])
            if (j > 0) // 必须还有礼物才行，不然没礼物送了
            {
                dp[i % 2][j - 1] = dp[(i - 1) % 2][j] + dis(x[i - 1], y[i - 1], x[i], y[i]);
                if (mnd > dp[i % 2][j - 1]) // 如果剩余礼物更少，走的路却没有更少，就被“完爆”了，一定不是最优
                    v[i % 2].push_back(j - 1);
                mnd = min(mnd, dp[i % 2][j - 1]);
            }
    }
    double ans = infl;
    for (auto j : v[n % 2])
        ans = min(ans, dp[n % 2][j]);
    cout << fixed << setprecision(15) << ans + dis(x[n], y[n], sx, sy) << endl; // 最后还要回家
    return 0;
}
```

---

## 作者：1234567890sjx (赞：1)

很简单的题。设 $f_i$ 表示圣诞老人送前 $i$ 个小朋友所需要的最小的花费。那么可以发现，$f_i$ 即为送前 $\max(0,i-k)$ 个小朋友之后再一起送中间这一段的小朋友礼物，取花费的最小值。

发现是一个区间求最小值的形式，所以呼上一个线段树即可。

时间复杂度 $O(n\log n)$，代码稍微有一点点细节。

---

## 作者：Fire_flame (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc334_f)

我超我把 a 写成 b 导致没有赛时 AC。

## $\mathtt{Solution}$

考虑 DP。

令 $f_i$ 表示圣诞老人送完 $1\sim i$ 的最小代价，$s_i$ 表示从圣诞老人的家按照顺序一直走到 $i$ 的距离。

考虑上一次拿礼物的点 $d$，那么可以得到：

$$f_i=\min\limits_{d=i-k}^{i-1}\{f_d+\operatorname{dist}\{a_d,b_d,sx,sy\}+\operatorname{dist}\{a_{d+1},b_{d+1},sx,sy\}+s_i-s_{d+1}\}$$

由于 $s_i$ 只与 $i$ 有关，所以使用线段树维护其余的部分，求最小值即可。

注意，当 $1\le i\le k$ 时，圣诞老人可以不回家拿礼物，初始值 $f_i=s_i$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define left rt * 2
#define right rt * 2 + 1
#define LD long double
using namespace std;
int read(){
	int s = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){s = s * 10 + (ch - '0');ch = getchar();}
	return s * f;
}
void write(int x){
    if(x < 0){putchar('-'); x = -x;}
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
const int MAXN = 2e5 + 5, MR = 8e5 + 5;
int n, m;
LD ans, tx, ty, f[MAXN], a[MAXN], b[MAXN], s[MAXN];
LD distant(LD sx, LD sy, LD ex, LD ey){
	return sqrt((sx - ex) * (sx - ex) + (sy - ey) * (sy - ey));
}
struct Segment_tree{
	int lf[MR], rf[MR];
	LD num[MR];
	void push_up(int rt){num[rt] = min(num[left], num[right]);}
	void build(int rt, int l, int r){
		num[rt] = 1e17, lf[rt] = l, rf[rt] = r;//要记得初始化成无穷大
		if(l == r)return ;
		int mid = (l + r) / 2;
		build(left, l, mid);
		build(right, mid + 1, r);
	}
	void change_node(int rt, int x, LD y){
		if(lf[rt] > x || rf[rt] < x)return ;
		if(lf[rt] == x && rf[rt] == x){
			num[rt] = y;
			return ;
		}
		change_node(left, x, y);
		change_node(right, x, y);
		push_up(rt);
	}
	LD query(int rt, int l, int r){
		if(rf[rt] < l || lf[rt] > r)return 1e17;
		if(l <= lf[rt] && rf[rt] <= r)return num[rt];
		return min(query(left, l, r), query(right, l, r));
	}
}tr;
signed main(){
	n = read(), m = read();
	scanf("%Lf%Lf", &tx, &ty);
	for(int i = 1;i <= n;i ++)scanf("%Lf%Lf", &a[i], &b[i]);
	s[1] = distant(a[1], b[1], tx, ty);
	for(int i = 2;i <= n;i ++)s[i] = s[i - 1] + distant(a[i], b[i], a[i - 1], b[i - 1]);
	tr.build(1, 0, n);//从圣诞老人的家（0号点）开始
	tr.change_node(1, 0, 0);
	for(int i = 1;i <= n;i ++){
		f[i] = s[i] + tr.query(1, max(i - m, 0ll), i - 1);//转移方程
		tr.change_node(1, i, f[i] + distant(tx, ty, a[i], b[i]) + distant(tx, ty, a[i + 1], b[i + 1]) - s[i + 1]);//用线段树维护最小值
//		printf("%lld %.12Lf %.12Lf\n", i, f[i], tr.query(1, max(i - m, 0ll), i - 1));
	}
	printf("%.12Lf", f[n] + distant(a[n], b[n], tx, ty));//记得圣诞老人要回家
	return 0;
}

```


---

## 作者：FReQuenter (赞：1)

令 $f_i$ 表示当前发放礼物到第 $i$ 个点并回到原点的最小路程。

那么转移显然：

$$f_{i}=\min\{f_{j}\}(i-j\le k)+v_i$$

其中 $v_i$ 是在这个点回到原点再前往下一个点的代价。

发现这个式子非常好维护。用单调队列和线段树等方式都可以。

```cpp
#include<bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
double dist(double x1,double y1,double x2,double y2){
    return sqrtl((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
double sx,sy,ans,x[200005],y[200005],c[200005],f[200005];
int n,k;
signed main(){
    cin>>n>>k>>x[0]>>y[0];
    for(int i=1;i<=n;i++) cin>>x[i]>>y[i];
    x[n+1]=x[0],y[n+1]=y[0];
    for(int i=1;i<=n;i++){
        ans+=dist(x[i-1],y[i-1],x[i],y[i]);
        c[i]=dist(x[i-1],y[i-1],x[0],y[0])+dist(x[i],y[i],x[0],y[0])-dist(x[i-1],y[i-1],x[i],y[i]);
    }
    ans+=dist(x[n],y[n],x[n+1],y[n+1]);
    list<int> q;
    q.push_back(0);
    for(int i=1;i<=n;i++){
		while(!q.empty()&&q.back()<i-k) q.pop_back();
		f[i]=f[q.back()]+c[i+1];
		while(!q.empty()&&f[i]<=f[q.front()]) q.pop_front();
		q.push_front(i);
	}
    cout<<fixed<<setprecision(15)<<ans+f[n];
    return 0;
}
```

---

## 作者：forgotmyhandle (赞：0)

非常好 dp，使我线段树旋转。

[原题传送门](https://atcoder.jp/contests/abc334/tasks/abc334_f)

[你谷传送门](https://www.luogu.com.cn/problem/AT_abc334_f)
## 分析
首先由于两点之间~~直线~~线段最短，我们肯定是希望从头一直送到尾，最后回家。但是有了 $k$ 的限制，就麻烦了。

考虑一个 dp。我们设 $dp[i]$ 表示刚送完第 $i$ 个孩子时所要跑的最短距离。转移的时候我们枚举上一次回家是在送完哪一个孩子**之后**。设 $d[i]$ 表示第 $i$ 个孩子的位置到第 $i - 1$ 个孩子的位置的距离，$d_0[i]$ 表示从家到第 $i$ 个孩子的位置的距离，$S$ 为 $d$ 的前缀和，则我们有

$dp[i] = \min\limits_{i - k \le j < i} \{ dp[j] + d_0[j] + d_0[j + 1] - d[j + 1] + S[i] - S[j]\}$

即在第 $j$ 个孩子送完之后回家，后面一直送到 $i$。发现这个 dp 可以使用线段树进行优化，具体来说就是到了 $i$，先把他前面所有 dp 值加上 $d[i]$，然后区间查最小值作为 $dp[i]$，再把 $dp[i] + d_0[i] + d_0[i + 1] - d[i + 1]$ 放到线段树里。这样就搞完了。

听说这个题也可以单调队列搞，反正我现在还没会。

## 代码
```
#include <iostream>
#include <iomanip>
#include <math.h>
#define int long long
using namespace std;
int x[200005], y[200005];
double dist(int x1, int y1, int x2, int y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}
double d[200005];
double d0[200005];
double dp[200005];
struct Segment_Tree {
    double mn[800005], tg[800005];
    void tag(int o, double x) { mn[o] += x, tg[o] += x; }
    void pushdown(int o) {
        tag(o << 1, tg[o]);
        tag(o << 1 | 1, tg[o]);
        tg[o] = 0;
    }
    void Add(int o, int l, int r, int L, int R, double x) {
        if (L <= l && r <= R) {
            tag(o, x);
            return;
        }
        pushdown(o);
        int mid = (l + r) >> 1;
        if (L <= mid) 
            Add(o << 1, l, mid, L, R, x);
        if (R > mid)
            Add(o << 1 | 1, mid + 1, r, L, R, x);
        mn[o] = min(mn[o << 1], mn[o << 1 | 1]);
    }
    void Change(int o, int l, int r, int x, double y) {
        if (l == r) {
            mn[o] = y;
            tg[o] = 0;
            return;
        }
        pushdown(o);
        int mid = (l + r) >> 1;
        if (x <= mid) 
            Change(o << 1, l, mid, x, y);
        else 
            Change(o << 1 | 1, mid + 1, r, x, y);
        mn[o] = min(mn[o << 1], mn[o << 1 | 1]);
    }
    double Query(int o, int l, int r, int L, int R) {
        if (L <= l && r <= R) 
            return mn[o];
        int mid = (l + r) >> 1;
        pushdown(o);
        if (R <= mid) 
            return Query(o << 1, l, mid, L, R);
        else if (L > mid) 
            return Query(o << 1 | 1, mid + 1, r, L, R);
        else 
            return min(Query(o << 1, l, mid, L, R), Query(o << 1 | 1, mid + 1, r, L, R));
    }
} seg;
signed main() {
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n + 1; i++) {
        cin >> x[i] >> y[i];
        d[i] = dist(x[i - 1], y[i - 1], x[i], y[i]);
        d0[i] = dist(x[1], y[1], x[i], y[i]);
    }
    seg.Change(1, 1, n + 1, 1, 0);
    for (int i = 2; i <= n + 1; i++) {
        seg.Add(1, 1, n + 1, 1, i - 1, d[i]);
        dp[i] = seg.Query(1, 1, n + 1, max(1ll, i - k), i - 1);
        seg.Change(1, 1, n + 1, i, dp[i] + d0[i] + d0[i + 1] - d[i + 1]);
    }
    cout << fixed << setprecision(10) << dp[n + 1] + d0[n + 1];
    return 0;
}
```


---

## 作者：FXT1110011010OI (赞：0)

第一次进前 $500$ 名，写个题解纪念一下。

这场的题目顺序很神秘啊 QAQ。

## 思路

显然是一个 DP。状态设计可以想到：设 $f_{i, j}$ 表示当前在第 $i$ 个小朋友家，手上有 $j$ 个礼物的最短路程。但是这样空间都不够，更不用说时间的优化了。考虑优化状态。

我们可以认为圣诞老人每次出门都带了 $k$ 个礼物，但是不用全部送出去，可以带剩下的礼物回家，在家装满 $k$ 个，再重新出发，所以只要连续去的小朋友家不超过 $k$ 个就行了。

这样，我们就可以省略第二维，设 $f_i$ 表示考虑前 $i$ 个小朋友的最短路程，转移方程如下（这里设 $0$ 号点为圣诞老人的家）：

$$f_i = \max_{j = i - k}^{i - 1} \{ f_j + dist(0 \to j + 1) + dist(j + 1 \to j + 2 \to j + 3 \to \dots \to i) + dist(i \to 0) \}$$

但是这样的时间复杂度还是 $O(nk)$ 的，需要优化。这里我用的是线段树优化 DP。

将式子中与 $i$ 有关的提到外面，就变为了：

$$f_i = \max_{j = i - k}^{i - 1} \{ f_j + dist(0 \to j + 1) + dist(j + 1 \to j + 2 \to j + 3 \to \dots \to i) \} + dist(i \to 0)$$

那么 $f_j + dist(0 \to j + 1)$ 这一部分可以在求 $f_j$ 时直接存到线段树里。$dist(j + 1 \to j + 2 \to j + 3 \to \dots \to i)$ 这一部分在求 $f_i$ 之前将 $dist(i - 1 \to i)$ 加到对应的 $j$ 下标上即可。然后就是一个板子的线段树了。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
const double INF = 1e18;

int x[N], y[N];
double f[N];
struct node
{
	int l, r;
	double mn, add;
}tr[N << 2];

double get(int i, int j)
{
	int dx = x[i] - x[j], dy = y[i] - y[j];
	return sqrt(1.0 * dx * dx + 1.0 * dy * dy);
}

void pushup(int u) {tr[u].mn = min(tr[u << 1].mn, tr[u << 1 | 1].mn);}

void pushdown(int u)
{
	if (tr[u].add != 0)
	{
		tr[u << 1].mn += tr[u].add, tr[u << 1].add += tr[u].add;
		tr[u << 1 | 1].mn += tr[u].add, tr[u << 1 | 1].add += tr[u].add;
		tr[u].add = 0.0;
	}
}

void build(int u, int l, int r)
{
	tr[u] = {l, r, INF, 0.0};
	if (l == r)
	{
		if (l == 0) tr[u].mn = get(0, 1);
		return;
	}
	int mid = l + r >> 1;
	build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
	pushup(u);
}

void modify(int u, int l, int r, double v)
{
	if (l <= tr[u].l && r >= tr[u].r)
	{
		tr[u].mn += v, tr[u].add += v;
		return;
	}
	pushdown(u);
	int mid = tr[u].l + tr[u].r >> 1;
	if (l <= mid) modify(u << 1, l, r, v);
	if (r > mid) modify(u << 1 | 1, l, r, v);
	pushup(u);
}

void modify2(int u, int x, double v)
{
	if (tr[u].l == tr[u].r)
	{
		tr[u].mn = v, tr[u].add = 0.0;
		return;
	}
	pushdown(u);
	int mid = tr[u].l + tr[u].r >> 1;
	if (x <= mid) modify2(u << 1, x, v);
	else modify2(u << 1 | 1, x, v);
	pushup(u);
}

double query(int u, int l, int r)
{
	if (l <= tr[u].l && r >= tr[u].r) return tr[u].mn;
	pushdown(u);
	int mid = tr[u].l + tr[u].r >> 1; double res = INF;
	if (l <= mid) res = min(res, query(u << 1, l, r));
	if (r > mid) res = min(res, query(u << 1 | 1, l, r));
	return res;
}

int main()
{
	int n, k; scanf("%d%d", &n, &k);
	for (int i = 0; i <= n; i ++ ) scanf("%d%d", &x[i], &y[i]);
	x[n + 1] = x[0], y[n + 1] = y[0];
	build(1, 0, n);
	for (int i = 1; i <= n; i ++ )
	{
		if (i > 1) modify(1, max(0, i - k), i - 2, get(i - 1, i));
		f[i] = query(1, max(0, i - k), i - 1) + get(i, 0);
		modify2(1, i, f[i] + get(0, i + 1));
	}
	printf("%.8lf\n", f[n]);
	return 0;
}
```

---

