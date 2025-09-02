# [ABC345E] Colorful Subsequence

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc345/tasks/abc345_e

$ N $ 個のボールが左右一列に並んでいます。  
左から $ i $ $ (1\leq\ i\leq\ N) $ 番目のボールは色 $ C_i $ で、価値は $ V_i $ です。

高橋君はこの列から **ちょうど** $ K $ 個のボールを取り除いたうえで、 残ったボールを元の順番で並べたときに同じ色のボールが隣り合わないようにしたいと考えています。 また、その条件のもとで、列に残ったボールの価値の総和をなるべく大きくしたいと考えています。

高橋君が、残ったボールの列において同じ色のボールが隣り合わないように $ K $ 個のボールを取り除くことができるか判定し、 できる場合は列に残ったボールの価値の総和としてあり得る最大の値を求めてください。

## 说明/提示

### 制約

- $ 1\leq\ K\ <\ N\leq\ 2\times\ 10^5 $
- $ K\leq\ 500 $
- $ 1\leq\ C_i\leq\ N $
- $ 1\leq\ V_i\leq\ 10^9 $
- 入力はすべて整数

### Sample Explanation 1

左から、$ 3,5 $ 番目のボールを取り除くと、残ったボールは左から順に色 $ 1,3,1 $ であるため、 どの隣り合う $ 2 $ つのボールの色も異なり、条件をみたしています。 このとき、列に残ったボールの価値の和は $ V_1+V_2+V_4=1+5+4=10 $ です。 他にも $ 5 $ つのボールから $ 2 $ つのボールを取り除く方法であって、同じ色のボールが隣り合わないようにできるものは存在しますが、 $ 3,5 $ 番目のボールを取り除いた時に残ったボールの価値の和は最大となります。 よって、$ 10 $ を出力します。

### Sample Explanation 2

どのようにボールを $ 1 $ つ取り除いても色 $ 1 $ のボールが隣り合ってしまいます。 よって、 $ -1 $ を出力します。

### Sample Explanation 3

必ずちょうど $ K $ 個のボールを取り除く必要があることに注意してください。

## 样例 #1

### 输入

```
5 2
1 1
3 5
3 3
1 4
1 2```

### 输出

```
10```

## 样例 #2

### 输入

```
3 1
1 10
1 10
1 10```

### 输出

```
-1```

## 样例 #3

### 输入

```
3 1
1 1
2 2
3 3```

### 输出

```
5```

# 题解

## 作者：Phartial (赞：17)

设 $f(i,j)$ 表示在前 $i$ 个物品中保留 $j$ 个物品，并钦定保留第 $i$ 个物品的所有合法方案的最大价值。

有转移方程：

$$
f(i,j)=V_i+\max_{p<i,C_p\ne C_i}f(p,j-1)
$$

注意到状态 $(i,j)$ 合法的一个必要条件是 $j\le i\le j+K$，所以对每个 $j$，我们只需要考虑 $\mathcal{O}(K)$ 个状态。于是只需考虑如何 $\mathcal{O}(1)$ 转移。

如果没有 $C_p\ne C_i$ 的限制，就可以通过实时记录最优决策 $p$ 的方式做到 $\mathcal{O}(1)$ 转移。

若 $C_p=C_i$，那么我们需要找到次优的决策 $p'$ 满足 $C_{p'}\ne C_i$，也就是 $C_{p'}\ne C_p$。更新 $p$ 的时候分讨一下 $C_i,C_p,C_{p'}$ 之间的关系顺便更新一下 $p'$ 即可。

总时间复杂度 $\mathcal{O}(NK)$。因为空间是 $\mathcal{O}(N^2)$ 的，需要滚动数组进行优化。

```cpp
#include <algorithm>
#include <iostream>

using namespace std;
using LL = long long;

const int kN = 2e5 + 1;

int n, k, c[kN], a[kN];
LL f[kN];

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  cin >> n >> k;
  for (int i = 1; i <= n; ++i) {
    cin >> c[i] >> a[i];
  }
  fill_n(f + 1, n, -1e18);
  for (int j = 1; j <= n - k; ++j) {
    LL m = f[j - 1], _m = -1e18;
    int cm = c[j - 1];
    for (int i = j; i <= j + k; ++i) {
      LL _f = f[i];
      if (c[i] != cm) {
        f[i] = m + a[i];
        if (_f >= m) {
          _m = m, m = _f, cm = c[i];
        } else if (_f > _m) {
          _m = _f;
        }
      } else {
        f[i] = _m + a[i];
        if (_f > m) {
          m = _f;
        }
      }
    }
  }
  LL ans = -1;
  for (int i = n - k; i <= n; ++i) {
    ans = max(ans, f[i]);
  }
  cout << ans;
  return 0;
}
```

---

## 作者：KingPowers (赞：16)

官方题解的三维状态做法是什么东西。

设 $f(i,j)$ 表示前 $i$ 个球删除了 $j$ 个，且保留第 $i$ 个球的最大价值，朴素的转移考虑枚举上一个没被删的球，可以做到总复杂度 $O(nk^2)$。

假设 $f(p,q)$ 能够转移到 $f(i,j)$，则需要满足 $i-p-1=j-q$，也就是 $p-q=i-j-1$，即 $p-q$ 是一个定值，同时要满足 $c_p\not =c_i$。

考虑维护每种 $i-j$ 的最大值和次大值，这里要求最大值和次大值颜色不相同，这样就能 $O(1)$ 转移了，总复杂度 $O(nk)$。

一个细节就是，直接输出 $f(n,k)$ 是考虑不到第 $n$ 个球被删除的情况的，因此我们要在序列末尾多加入一个与其他球颜色都不一样的球，令其价值为 $0$ 即可。

[提交记录](https://atcoder.jp/contests/abc345/submissions/51367664)

---

## 作者：HHH6666666666 (赞：10)

注意到 $k$ 相对于 $n$ 很小，考虑如何利用这一点。

考虑 $DP$。一个朴素的想法：令 $f_{i,j,t}$ 表示考虑到第 $i$ 个球，此时最后一个未被删的球颜色为 $j$，且共删了 $t$ 个球时的最大价值。对于每个 $i$， $j$ 最多有 $k$ 种取值，状态数为 $O(nk^2)$。

尝试优化掉一维。我们的思路从依次考虑每个小球变为依次考虑保留的位置。对于每个小球，我们假设该球不被删除，枚举上一个未被删除的位置进行转移。令 $f_{i,j}$ 表示保留第 $i$ 个球，其左侧共删除 $j$ 个球时的最大价值。写出转移方程：

$f_{i,j}=\max\limits_{t<i,c_t \neq c_i}f_{t,j-(i-t-1)}+v_i$。

我们优化了一维状态，代价是转移的复杂度变为 $O(k)$。

优化转移。注意到 $f_{i,j}$ 会造成影响的状态有 $f_{i+1,j},f_{i+2,j+1},f_{i+3,j+2}$ 等。如果不考虑颜色，这些影响是可以与其他数的影响合并的（取最大值）。换句话说，记 $g_{i,j}$ 为 $f_{i,j}$ 转移式中的 $\max\limits_{t<i,c_t \neq c_i}f_{t,j-(i-t-1)}$，则 $g_{i+1,j+1}$ 就由 $g_{i,j}$ 与 $i$ 本身对后面的数造成的影响组成：$g_{i+1,j+1}=\max(g_{i,j},f_{i,j+1})$。实现 $O(1)$ 转移。

加入颜色的限制，在 $g_{i,j}$ 记录三个值：其最大值，令其取到最大值的颜色，以及这个颜色之外的最大值。这样做是因为转移时实际上只会用到最大值以及次大值。对应更新即可。状态数 $O(nk)$，转移 $O(1)$。状态开不下需要滚动。

注意当前节点前小球全部删除和无解、$k=n$ 的情况。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define inf 0x3f3f3f3f3f3f3f3fll

using namespace std;

const int MAXN = 2e5 + 10;
const int MAXK = 510;

int n, k;
int c[MAXN];
ll v[MAXN];
struct MaxSec {
    ll mx, id, sec;
    MaxSec() : mx(-inf), id(0), sec(-inf) {}
    MaxSec(ll mx, ll id) : mx(mx), id(id), sec(-inf) {}
    void insert(ll x, int p) {
        if (id == p) mx = max(mx, x);
        else {
            if (x > mx) sec = mx, mx = x, id = p;
            else if (x > sec) sec = x;
        }
        return;
    }
    ll query(int p) {
        if (p == id) return sec;
        else return mx;
    }
} a[MAXK];      // 对应题解中的 g
ll f[MAXK];

int main() {
    ios:: sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) cin >> c[i] >> v[i];
    memset(f, -0x3f, sizeof f);
    ll ans = -inf;
    a[0] = MaxSec(0, 0);
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= k; ++j) {
            f[j] = a[j].query(c[i]) + v[i];
            if (k - j == n - i) ans = max(ans, f[j]);
        }
        for (int j = k; j; --j) a[j] = a[j - 1];
        a[0] = MaxSec();
        for (int j = 0; j <= k; ++j) a[j].insert(f[j], c[i]);
    }
    if (k == n) ans = 0;
    if (ans < 0) cout << -1 << endl;
    else cout << ans << endl;
    return 0;
}

```

---

## 作者：Jsxts_ (赞：7)

一个神秘贪心，不太会证但赛时过了。

考虑贪心地删，直到删了 $k$ 个：

- 有相邻相同，找到其中满足和相邻相同并且权值最小的。

- 删掉一个后左右会相同就将其中的最小值一起删掉，并记这类权值最小值为 $w_2$。

- 否则只需删掉一个，记这类权值最小值为 $w_1$。

然后进行判断：

- 若第一类存在，则优先删第一类。

- 否则若只能删 $1$ 个，则删 $w_1$。

- 否则判断：若 $w_2<2w_1$，则删掉那两个，否则删一个。

用链表维护即可。

$O(nk)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5;
const int inf = 2e9;
const ll INF = 1e18;
ll read() {
	ll s = 0,f = 1;char ch = getchar();
	while (!isdigit(ch)) f = ch == '-'? -1 : 1, ch = getchar();
	while(isdigit(ch)) s = s * 10 + ch - '0', ch = getchar();
	return s * f;
}
const int mod = 998244353;
int qpow(int a,int b) {
	int res = 1;
	while (b) {
		if (b & 1) res = 1ll * res * a % mod;
		b >>= 1, a = 1ll * a * a % mod;
	}
	return res;
}
int getmod(int x) {
	return x - (x >= mod) * mod;
}
#define x first
#define y second
pair<int,int> a[N + 10];
int pre[N + 10],nxt[N + 10];
void del(int x) {
	pre[nxt[x]] = pre[x];
	nxt[pre[x]] = nxt[x];
}
int main() {
	int T = 1;
	while (T -- ) {
		int n = read(),k = read(),ss = 0;
		ll sum = 0;
		for (int i = 1;i <= n;i ++ ) a[i].x = read(), a[i].y = read(), sum += a[i].y, pre[i] = i - 1, nxt[i] = i + 1, ss += a[i].x == a[i - 1].x;
		if (ss > k) {
			puts("-1");
			continue;
		}
		nxt[0] = 1;
		ll ans = 0;
		while (k -- ) {
			pair<int,int> mn1 = {inf,0},mn2 = {inf,0},mn3 = {inf,0};
			for (int i = 0;i != n + 1;i = nxt[i]) {
				if (!i) continue;
				//cout << "i:" << i << endl;
				if (a[i].x == a[pre[i]].x || a[i].x == a[nxt[i]].x) mn1 = min(mn1,{a[i].y,i});
				else if (a[pre[i]].x == a[nxt[i]].x) mn2 = min(mn2,{a[i].y + min(a[pre[i]].y,a[nxt[i]].y),i});
				else mn3 = min(mn3,{a[i].y,i});
			}
			if (mn1.y != 0) del(mn1.y), ans += mn1.x;//, cout << "!!" << mn1.y << endl;
			else if (mn3.x * 2 < mn2.x || k == 0) del(mn3.y), ans += mn3.x;
			else {
				int p = mn2.y;
//				cout << "!!" << p << endl;
				del(a[pre[p]].y < a[nxt[p]].y ? pre[p] : nxt[p]);
				del(p);
				ans += mn2.x;
				k --;
			}
		}
		
		cout << sum - ans;
	}
	return 0;
}
```

---

## 作者：Liyunze123 (赞：5)

# 1.题目大意
你有 $n$ 个球，每个球有颜色 $c_i$ 和权值 $a_i$。你可以拿掉 $k$ 个球，使得剩下的球中相邻的颜色不相同，问你剩下权值最大是多少。如果不能使得剩下的球中相邻的颜色不相同，输出 $-1$。
# 2.解题思路
设 $dp_{i,j}$ 表示前 $i$ 个球，保留 $j$ 个，规定保留第 $i$ 个，最大的权值。

发现 $j \le i \le j+K$（最多扔掉 $K$ 个），所以时间复杂度是 $O(NK)$ 的。前提是 $O(1)$ 的转移。

转移方程：$dp_{i,j}=\max{dp_{p,j-1} + a_i}$，满足 $c_p \neq c_i$。解释：前 $p$ 个保留 $j-1$ 个，最后一个保留的是 $i$，多保留一个 $i$。但最后两个保留的（$p$ 和 $i$）颜色必须不等。

我们可以存一下最大的 $dp_{p,j-1}$，但是为了避免那个 $p$ 和 $i$ 颜色相等，再存一个次大值 $dp_{q,j-1}$ 满足 $c_q \neq c_i$。

接下来分情况讨论：如果 $c_i \neq c_p$，直接更新 $dp_{i,j},p,q$。否则拿 $q$ 去做，但因为 $c_p = c_i$，只能更新 $q$。
# 3.注意事项
数组太大，可以用滚动数组，因为第二维只用到 $j$ 和 $j-1$。

枚举时，$j$ 只能枚举到 $n-k$，因为要删 $k$ 个。

一开始，$dp$ 数组要初始化成负无穷，避免答案出现 $-1$。

综上述所说，答案为 $\max{dp_{i,n-k}}$ 满足 $n-k \le i \le n$。

最后很重要的一句：**不开 long long 见祖宗！**
# 4.标程代码
```
//滚动数组，代码中省略题解中的第二维
//肯定有人写类似思路，但没我写的详细
//不许抄袭
#include<bits/stdc++.h>
using namespace std;
int n,k,a[200010],b[200010];
long long dp[200010],ans=-1;
int main(){
    scanf("%d%d",&n,&k);
    for(int w=1;w<=n;w++)scanf("%d%d",&a[w],&b[w]),dp[w]=-1e18;
    for(int x=1;x<=n-k;x++){
        long long m=dp[x-1],sm=-1e18,c=a[x-1];
        for(int w=x;w<=x+k;w++){
            long long f=dp[w];
            if(a[w]!=c){
                dp[w]=m+b[w];
                if(f>=m)sm=m,m=f,c=a[w];
                else if(f>sm)sm=f;
            }else{
                dp[w]=sm+b[w];
                if(f>m)m=f;
            }
        }
    }
    for(int w=n-k;w<=n;w++)ans=max(ans,dp[w]);
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：zrl123456 (赞：3)

一眼 dp ~~（贪心）~~。  
### 部分分 ~~（有吗）~~：
我们通过思考发现贪心策略是不行的，那么我们考虑 dp。  
#### 设状态：
我们设 $f_{i,j}$ 为循环到第 $i$ 个球且选中了第 $i$ 个球，并有 $j$ 个球被删除能所得的最大价值（若取不到值便为负无穷）。  
边界条件是 $f_{0,0}=0$，最后的答案是什么我们还需要思考一下：  
![](https://cdn.luogu.com.cn/upload/image_hosting/vslf5kv7.png)
故最后答案为：  
$$ans=\max_{i=n-k}^n(f_i)$$
#### 设状态转移方程：
那么我们可以寻找一个球 $p\ (j-1\le p\le i-1)$ 和一个值 $f_{p,j-1}$，也就是说我们假设倒数第二个没有被删除的球为 $p$，易得转移方程：  
$$f_{i,j}=\max_{p=j-1,c_p\ne c_i}^{i-1}(f_{p,j-1})+v_i$$
这样时间复杂度就是 $O(nk^2)$，考虑优化。  
### 优化：
如果没有 $c_p\ne c_i$ 的限制的话，这道题就变得非常简单，只需要边维护 $f$ 数组，边计算最大值即可。  
但这只是假设，有了这条限制我们该怎么办呢？  
解决方法当然有，我们找到一个次大值 $p'$，使 $c_{p'}\ne c_p$ 即可。  
为什么呢？  
- 若 $c_p=c_i$，则 $c_{p'}\ne c_i$，$c_{p'}$ 为最优解。  
- 若 $c_p\ne c_i$，则 $c_p$ 本身就为最优解。  

那么问题又来了，如何转移（定义最大值为 $fmax$，次大值为 $smax$，结尾 $c$ 值为 $lst$，由于空间复杂度较大，故后面 $f$ 压掉第一维）？  
- 若 $lst\ne c_j$，则：  
$f_j=fmax+v_j$，更新 $f_j$。  
若**以前的** $f_j\ge fmax$：$smax=fmax,fmax=f_j,lst=c_j$。  
若 $f_j\ge smax$：$smax=f_j$。  
- 若 $lst=c_j$，则：  
$f_j=smax+v_j$，更新 $f_j$。  
若 $f_j\ge fmax$：$fmax=f_j$。  

这样，时间复杂度为 $O(nk)$，空间复杂度为 $O(n)$，可以通过。  
代码：  
```cpp
#include<bits/stdc++.h>
#define int long long
#define inl inline
#define INF 214748364721474836
#define fst ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define rep(i,x,y) for(int i=x;i<=y;++i)
#define rer(i,x,y,cmp) for(int i=x;i<=y&&cmp;++i)
#define T set<string>::iterator
using namespace std;
const int N=2e5+5;
int n,k,c[N],v[N],f[N],ans=-INF;
signed main(){
	fst;
	memset(f,-0x3f,sizeof(f));
	f[0]=0;
	cin>>n>>k;
	rep(i,1,n) cin>>c[i]>>v[i];
	rep(i,1,n-k){
		int first_max=f[i-1],second_max=-INF,copyc=c[i-1];
		rep(j,i,i+k){
			int copyf=f[j];
			if(c[j]!=copyc){
				f[j]=first_max+v[j];
				if(copyf>=first_max){
					second_max=first_max;
					first_max=copyf;
					copyc=c[j];
				}else if(copyf>=second_max) second_max=copyf;
			}else{
				f[j]=second_max+v[j];
				if(copyf>=first_max) first_max=copyf;
			}
		}
	}
	rep(i,n-k,n) ans=max(ans,f[i]);
	if(ans>=0) cout<<ans;
	else cout<<-1;
    return 0;
}
```

---

## 作者：appear_hope (赞：3)

看完题目考虑状态设计。

状态：$(i, j, sum)$ 表示选择第 $i$ 个元素，已经移除了 $j$ 个元素的价值和 $sum$。

转移（收集型）：$(k, j - i + k + 1, sum) \rightarrow (i, j, sum + V_i)$，其中 $k < i, 0 \le j - i + k + 1 \le k, C_i \ne C_k$。

此时直接去做转移的时间复杂度：$O(N \times K^2)$。

拿这个样例举例：（这个样例中的 $C$ 序列是 $N$ 的全排列）

```cpp
4 4
1 1
2 1
3 1
4 1
```

我们做一遍最上面写的动态规划，你可以发现如下特点：

我先把所有状态列出来：

```cpp
dp[1][0] dp[1][1] dp[1][2] dp[1][3] dp[1][4]
dp[2][0] dp[2][1] dp[2][2] dp[2][3] dp[2][4]
dp[3][0] dp[3][1] dp[3][2] dp[3][3] dp[3][4]
dp[4][0] dp[4][1] dp[4][2] dp[4][3] dp[4][4]
```

以 $dp_{4, 4}$ 为例，它可以以 $dp_{3, 4}, dp_{2, 3}, dp_{1, 2}$ 转移而来，在上图我们可以很明显的看出这是 $(1, 2)$ 到 $(3, 4)$ 的一条斜线，在这条斜线上的任何一个点的差值都是统一的。（记 $(a, b)$ 为在网格图上的二维坐标，而这里的差值指的是 $a - b$ 或 $b - a$。）

那么我们继续去想如果 $C$ 序列不是 $N$ 的全排列如何快速转移，稍作思考再往下看。

为了处理 $C_i$ 相等的情况，我们可以记录对于一条斜线上的 $dp$ 的最大值和次大值，计这最大值为 $dp_{i, j}$，次大值为 $dp_{x, y}$，其中 $1 \le i, x \le N, 0 \le j, y \le K$，我们找到的最大值和次大值还要满足 $C_x \ne C_i$，然后对于每一条斜线由于这条斜线上的差值是固定的，由于可能出现负数，可以让这个差值全部加上 $N$，这样就不会出现负数下标就可以用数组存了。

代码如下：

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;
const long long INF = 1e15;

bool flag = 1;
int id[3 * N];
pair<int, int> a[N];
long long n, k, f, dp[N], maxx[3 * N][2];

void Insert(int x, long long num, int color){
  if(num >= maxx[x][0]){
    maxx[x][1] = (id[x] == color ? maxx[x][1] : maxx[x][0]), maxx[x][0] = num, id[x] = color;
  }
  else if(color != id[x] && num > maxx[x][1]){
    maxx[x][1] = num;
  }
}

int main(){
  cin >> n >> k;
  for(int i = 1; i <= n; i++){
    cin >> a[i].first >> a[i].second;
  }
  for(int i = 0; i <= k; i++){
    maxx[1 - i + n][0] = maxx[1 - i + n][1] = -INF;
  }
  for(int j = 1; j <= k; j++){
    dp[j] = -INF;
  }
  dp[0] = a[1].second;
  Insert(1 + n, a[1].second, a[1].first);
  for(int i = 2; i <= n; i++){
    for(int j = 1; j <= k; j++){
      dp[j] = (a[i].first != id[i - 1 - j + n] ? maxx[i - 1 - j + n][0] : maxx[i - 1 - j + n][1]) + a[i].second;
      dp[j] = max(dp[j], (j == i - 1 ? a[i].second + 0ll : -INF));
      Insert(i - j + n, dp[j], a[i].first);
    }
    maxx[i + n][0] = maxx[i + n][1] = -INF;
    flag &= (a[i].first != a[i - 1].first);
    if(flag){
      dp[0] += a[i].second;
      Insert(i + n, dp[0], a[i].first);
    }
    dp[0] = (!flag ? -INF : dp[0]);
  }
  cout << (maxx[2 * n - k][0] < 0 ? -1 : maxx[2 * n - k][0]);
  return 0;
}
```

---

## 作者：roger_yrj (赞：1)

# [ABC345E] Colorful Subsequence
## 前言
![](https://cdn.luogu.com.cn/upload/image_hosting/i6ydvsgn.png)
就差 $3s$ 啊……
## 题意
有 $N$ 个球，每一个球有一个颜色 $C_i$ 和价值 $V_i$，现在要删除其中的 $K$ 个球，使得剩下的球没有相邻的两个球颜色相等。求剩下的球的最大价值总和。
## 题解
首先根据题目很容易就能想出一个 DP：

设 $f_{i,j}$ 表示前 $i$ 个球中删去 $j$ 个球（第 $i$ 个球不能删）最大价值总和是多少。

转移方程为 $f_{i,j}=\max\limits_{\max(i-K-1,0)\le k<i,C_k\not=C_i}f_{k,j-(i-k-1)}$

时间复杂度 $O(NK^2)$，显然过不了。

考虑优化。

设 $maxx_i$ 表示剩余 $i$ 个球最大价值总和是多少。

$f_{i,j}=maxx_{i-j-1}$？

显然错误，因为没有考虑颜色。

由于取到最大值时，最后一个球的颜色可能与第 $i$ 个球的颜色相等，所以我们再统计一个次大值，并保证与最大值颜色不同。这样的话，如果取最大值时颜色相等，那就取次大值就行了。

时间复杂度 $O(NK)$。

## 代码
```cpp
void add(ll x,int y,int z){
	if(x>maxx[y])swap(x,maxx[y]),swap(c1[y],z);
	if(x>se[y]&&z!=c1[y])se[y]=x,c2[y]=z;
}
void solve(){
	memset(f,-0x3f,sizeof(f));
	memset(maxx,-0x3f,sizeof(maxx));
	memset(se,-0x3f,sizeof(se));
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		c[i]=read(),v[i]=read();
	}
	maxx[0]=0;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=min(i-1,k);j++){
			if(maxx[i-1-j]>=0&&c1[i-1-j]!=c[i]){
				f[i][j]=maxx[i-1-j]+v[i];
				add(f[i][j],i-j,c[i]);
			}else if(se[i-1-j]>=0){
				f[i][j]=se[i-1-j]+v[i];
				add(f[i][j],i-j,c[i]);
			}
		}
	}
	ll ans=-1;
	for(int i=1;i<=n;i++){
		if(k-(n-i)<0)continue; 
		ans=max(ans,f[i][k-(n-i)]);
	}
	cout<<ans;
}
```

---

## 作者：M1saka16I72 (赞：1)

# AtCoder Beginner Contest 345 [E - Colorful Subsequence](https://atcoder.jp/contests/abc345/tasks/abc345_e) 题解

## 题意

有 $N$ 个球，每一个球有一个颜色 $C_i$ 和价值 $V_i$，现在要删除其中的 $K$ 个球，使得剩下的球没有相邻的两个球颜色相等。求剩下的球的最大价值总和。

### 数据范围

- $1\leq K < N \leq 2\times 10^5$
- $K \leq 500$

## 思路

考虑 dp。

设计状态 $f_{i,j}$ 代表不删除第 $i$ 个球，在前面删除 $j$ 个球时最大的价值总和。

则 $f_{i,j}$ 一定由前面的第 $k$ 个球删除 $(k,i)$ 之间的全部 $i-k-1$ 个球转移而来，状态转移方程为 $f_{i,j}=\max\{f_{k,j-(i-k-1)}\}(j\leq K,i-j-1\leq k<i,c_i≠c_k)+v_i$。

这样转移是 $\mathcal{O}(nk^2)$ 的，实测会超时，考虑优化。

## 优化

发现转移过来的状态里，第一维和第二维的差总是相等，于是我们可以维护一个 $g_x=\max\{f_{j,j-x}\}$，$f_{i,j}$ 的转移就可以优化到 $\mathcal{O}(1)$。

当时把我卡住的难点在于如何保证当前最优解 $g_{i-j}$ 的颜色与当前的 $c_i$ 不同。

方法则是维护两个**颜色不同**的最优解和次优解，这样如果当前的 $c_i$ 与最优解的颜色相同，就可以从次优解转移过来。

细节详见[代码](https://atcoder.jp/contests/abc345/submissions/51395251)。

---

## 作者：ykzzldz (赞：1)

拿到题目，可以发现这是一道 $dp$，可以比较容易设出一个状态（以下分析与代码使用 $m$ 代替题目中的 $k$）。$f_{i,j}$ 表示前 $i$ 个点选 $j$ 个点（第 $i$ 个点必选）的最大价值，$f_{i,j}=\max f_{k,j-1}(c_k\ne c_i,j\in[i-m,i],k\in[i-m-1,i-1])$，到这里，复杂度为 $O(nm^2)$，考虑优化。

可以发现，上述式子中就算 $k$ 的范围拓展到 $[1,i-1]$，对结果也不会产生影响，考虑可以 $O(1)$ 求出这个 $k$。由于颜色的限制只对于不同颜色产生影响，所以对于前缀的每个 $j$，我们都只需要考虑 $f_{k,j}$ 的最大值和次大值就可以了（当然，这两个值所对应的最后一个颜色不能相同），这一部分代码难度不大，只需注意一些细节即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int n,m,c[N],w[N],f[N],max1[N],jl[N],max2[N];
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>c[i]>>w[i];
		max1[i]=max2[i]=-1e18;
	}
	for(int i=1;i<=n;i++){
		if(w[i]>=max2[1]&&w[i]<max1[1]&&c[i]!=jl[1]){
			max2[1]=w[i];
		}
		else if(w[i]>=max1[1]){
			if(c[i]!=jl[1])max2[1]=max1[1];
			max1[1]=w[i];
			jl[1]=c[i];
		}
		for(int j=max(2ll,i-m);j<=min(i,n-m);j++){
			if(c[i]==jl[j-1]){
				f[j]=max2[j-1]+w[i];
			}
			else{
				f[j]=max1[j-1]+w[i];
			}
			if(f[j]>=max2[j]&&f[j]<max1[j]&&c[i]!=jl[j]){
				max2[j]=f[j];
			}
			else if(f[j]>=max1[j]){
				if(c[i]!=jl[j])max2[j]=max1[j];
				max1[j]=f[j];
				jl[j]=c[i];
			}
		}
	}
	if(max1[n-m]<0){
		cout<<-1;
		return 0;
	}
	cout<<max1[n-m];
	return 0;
}
```

---

## 作者：Drimpossible (赞：1)

官方题解做法。

先考虑一个暴力 $O(N^2K)$ 的 DP，设 $f_{i,j,k}$ 表示当前选到第 $i$ 个，删除了 $j$ 个，最后一个的颜色为 $k$ 的最大剩余代价，转移显然：
$$
f_{i,j,k}=f_{i-1,j-1,k}
\\
f_{i,j,c_i}=\max_{k\ne c_i}f_{i-1,j,k}+v_i
$$

仔细观察这个转移式子，发现普遍都是由上一个直接继承过来的，只有在不删除当前这一个的时候才会去找其他颜色转移过来。注意到只有可能是上一个的最大值或者次大值（在最大值颜色和 $c_i$ 相同的时候取次大）才会被用到，所以我们只需要记录最大和次大的 $k$ 和 DP 值就行了，$k$ 这一维被压成 $2$，时间复杂度降到 $O(NK)$。

细节：
1. $O(NK)$ 的空间开不下，要滚动数组。
1. 对于 $j=0$ 的转移要特殊处理。
1. 转移的时候一定要保证最大值和次大值的颜色不同。

## code：
```cpp
void solution(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>c[i]>>a[i];
	/*f记录颜色，g记录代价*/
	memset(g,-0x3f,sizeof(g));
	g[0][0]=0;
	
	for(int i=1;i<=n;i++){
		for(int j=m;j;j--){
			if(f[j][0]!=c[i]){
				f[j][0]=c[i];
				g[j][0]+=a[i];
			}
			else g[j][0]=g[j][1]+a[i];
			f[j][1]=g[j][1]=-1e18;
			for(int t=0;t<2;t++){
				if(g[j-1][t]>=g[j][0]){
					if(f[j-1][t]!=f[j][0]){
						f[j][1]=f[j][0];
						g[j][1]=g[j][0];
					}
					f[j][0]=f[j-1][t];
					g[j][0]=g[j-1][t];
				}
				else if(g[j-1][t]>g[j][1]&&f[j-1][t]!=f[j][0]){//保证次大和最大的颜色不同
					f[j][1]=f[j-1][t];
					g[j][1]=g[j-1][t];
				}
			}
		}
		if(c[i]!=f[0][0])
			f[0][0]=c[i],g[0][0]+=a[i];
		else g[0][0]=-1e18;
	}
	
	if(g[m][0]>=0)cout<<g[m][0];
	else cout<<-1;
}
```

---

