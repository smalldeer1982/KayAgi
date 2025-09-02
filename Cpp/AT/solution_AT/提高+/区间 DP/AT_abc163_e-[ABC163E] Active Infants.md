# [ABC163E] Active Infants

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc163/tasks/abc163_e

$ N $ 人の幼児が左右一列に並んでおり、左から $ i $ 番目の幼児の活発度は $ A_i $ です。

あなたは一回だけ、幼児たちを好きな順番に並び替えさせることができます。

はじめ左から $ x $ 番目に並んでいた幼児が左から $ y $ 番目に移動するとき、うれしさが $ A_x\ \times\ |x-y| $ だけ生じます。

幼児のうれしさの合計が最大でいくつになるか求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2000 $
- $ 1\ \leq\ A_i\ \leq\ 10^9 $
- 入力はすべて整数である。

### Sample Explanation 1

左から $ 1 $ 番目の幼児を $ 3 $ 番目に、$ 2 $ 番目の幼児を $ 4 $ 番目に、$ 3 $ 番目の幼児を $ 1 $ 番目に、$ 4 $ 番目の幼児を $ 2 $ 番目に並ばせると、うれしさの合計は $ 1\ \times\ |1-3|+3\ \times\ |2-4|+4\ \times\ |3-1|+2\ \times\ |4-2|=20 $ になります。

## 样例 #1

### 输入

```
4
1 3 4 2```

### 输出

```
20```

## 样例 #2

### 输入

```
6
5 5 6 1 1 1```

### 输出

```
58```

## 样例 #3

### 输入

```
6
8 6 9 1 2 1```

### 输出

```
85```

# 题解

## 作者：喵仔牛奶 (赞：21)

考虑贪心，把数从大到小排序，每次取最大的数放到两边一定最优。

证明：
- 考虑 $x,y$ 两个位置，满足 $a_x>a_y$。
- 如果两次移动的距离和相等，当然是权值大的移得远好。
- 如果先将 $x$ 移到两边的距离和不如先移 $y$ 大，这个决策一定不是最优解。

这个问题是一个区间 dp 模型。为了方便，我们倒着来，将 $\{A_n\}$ 从小到大排个序，设 $f_{i,j}$ 是将 $A_1\sim A_{j-i+1}$ 填到 $[i,j]$ 的最优解，就有转移方程：

$$f_{i,j}=\max\{f_{i+1,j}+A_{j-i+1}\times|P_{j-i+1}-i|,f_{i,j-1}+A_{j-i+1}\times|P_{j-i+1}-j|\}$$

$P_{i}$ 代表排序后位置 $i$ 的元素原来的位置。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2005;
struct node {
	long long v, p;
	bool operator < (const node& x) const {
		return v < x.v;
	}
} a[N];
long long f[N][N], n;
int main() {
	cin >> n;
	for (int i = 1; i <= n; i ++)
		cin >> a[i].v, a[i].p = i;
	sort(a + 1, a + 1 + n);
	for (int l = 1; l <= n; l ++)
		for (int i = 1; i + l - 1 <= n; i ++) {
			int j = i + l - 1;
			f[i][j] = max(f[i][j], f[i + 1][j] + a[j - i + 1].v * abs(a[j - i + 1].p - i));
			f[i][j] = max(f[i][j], f[i][j - 1] + a[j - i + 1].v * abs(a[j - i + 1].p - j));
		}
	cout << f[1][n] << '\n';
	return 0;
}

```


---

## 作者：Silence_water (赞：7)

[题目传送门](https://www.luogu.com.cn/problem/AT5242)

---

$Analyse$

为了使答案尽可能的大，$a_i$ 越大的数要移动到当前没有数被填入的区间的两端。若该区间为 $[l,r]$，该区间对答案的最大贡献值为 $dp[l][r]$，当前要填的数的值为 $val$，原位置为 $id$，那么每次就是决策将 $val$ 填在位置 $l$ 还是 $r$。由此设计出状态转移方程：

$$dp[l][r]=\max(dp[l+1][r]+abs(id-l)\times val,dp[l][r-1]+abs(id-r)\times val)$$

---

$Solution$

这里采用记忆化搜索版的区间 dp 实现。其中 $a$ 数组按照 $val$ 从大到小排序。

```cpp
ll dp[M][M];
ll dfs(int now,int l,int r)
{
    if(l>r)return 0;
    if(dp[l][r]!=-1)return dp[l][r];
    if(now>n)return 0;
    ll le=dfs(now+1,l+1,r)+abs(a[now].id-l)*a[now].val;
    ll ri=dfs(now+1,l,r-1)+abs(a[now].id-r)*a[now].val;
    return dp[l][r]=max(le,ri);
}
```

---

$The$ $end$

感谢您的观看！如有不足，请麻烦指正哦。

---

## 作者：Superiority (赞：6)

# 思路
我们要使答案尽可能的大，显然我们要使较大的数字移动的越远贡献值就越大，所以我们使较大的数字移动到区间的两边，可以直接用区间 DP 来求解。我们可以定义 $dp_{l,r}$ 为区间 $l \sim r$ 最大的贡献值。将每个 $a_i$ 的下标用 $idx_i$ 记录下来，对 $a_i$ 进行排序，以便找出较大的数字。在转移前我们要先进行初始化，由定义可知 $dp_{i,i} = a_1 \times | i - idx_1 |$。因为要使 $ i $ 的贡献值最大，我们选择移动到头部，因此是 $| i - a_1 |$。接下来我们可以推出动态转移方程：

$$dp_{l,r} = \max ( dp_{l,r} , \max ( dp_{l+1,r} + a_{r-l+1} \times | idx_{r-l+1}-l |,dp_{l,r-1}+a_{r-l+1} \times | idx_{r-l+1}-r | $$

整个代码就完成了。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=3e3;
const int INF=1e9;
#define zjj long long
int n;
struct S{
	zjj x;
	int idx;
}s[MAXN];
zjj a[MAXN];
zjj dp[MAXN][MAXN];
bool cmp(S a,S b){
	return a.x<b.x;
}
int main(){
    ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s[i].x;
		s[i].idx=i;
	}
	sort(s+1,s+n+1,cmp);
	for(int i=1;i<=n;i++){
		dp[i][i]=s[1].x*abs(i-s[1].idx);
	}
	for(int i=1;i<=n;i++){
		for(int l=1;l<=n-i+1;l++){
			int r=l+i-1;
			dp[l][r]=max(dp[l][r],max(dp[l+1][r]+s[r-l+1].x*abs(s[r-l+1].idx-l),dp[l][r-1]+s[r-l+1].x*abs(s[r-l+1].idx-r)));
		}
	}
	cout<<dp[1][n]<<endl;
    return 0;
}
```

---

## 作者：hanzhongtlx (赞：5)

~~水点贡献分~~

有 $n$ 个人，每个人有一个价值 $c_i$ ，把他们打乱，假设从前的位置是 $a_i$，现在的位置是 $b_i$，最大化 $\sum\limits_{i=1}^nc_i|a_i-b_i|$。   
贪心，优先放置 $c$ 小的人。   
为什么呢？   

由于我们在记录状态时无法大范围看全局，先选择影响小的人。   
我们设 $dp_{i,j}$ 为选 $j-i+1$个人放在 $i$ 到 $j$ 的区间上的最大贡献。   
我们以此为基础扩大区间，即判断先一个应该放左边还是右边。   

这里转移方程易得为：

$$dp_{i,j}=\max\{\max(dp_{i+1,j}+c_{j-i+1}|a_{j-i+1}-l|,dp_{i,j-1}+c_{j-i+1}|a_{j-i+1}-r|)\}$$   
## $Code$:
```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;

#define ll long long 
#define read(x) scanf("%d",&x)

struct node
{
	int id,val;
}a[2005];
ll dp[2005][2005];
int n;

bool cmp(node n,node m){return n.val<m.val;}

int main()
{
	read(n);
	for(int i=1;i<=n;i++) read(a[i].val),a[i].id=i;
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++) dp[i][i]=1ll*a[1].val*abs(a[1].id-i);
	for(int i=2;i<=n;i++)
	{
		for(int l=1;l+i-1<=n;l++)
		{
			int r=l+i-1;
			dp[l][r]=0;
			dp[l][r]=max(dp[l][r],max(dp[l+1][r]+1ll*a[i].val*abs(a[i].id-l),dp[l][r-1]+1ll*a[i].val*abs(a[i].id-r)));
		}
	}
	printf("%lld\n",dp[1][n]);
}

---

## 作者：allqpsi (赞：4)

#### 思路：

第一眼看到这道题，认为是一个贪心。随便从大到小排序了一下数组，每次看移到最左边更远还是最右边更远，然后移到那。不多说，明显 WA 了。

仔细一想，居然贪心是错的，那正解应该就是 dp 了。再一想，这题就是区间 dp 嘛！从贪心来思考，我们可以对左右端点分别放几个数 dp 这样思路就来了。可这未免也太麻烦了。

反过来想，我们可以枚举中间一段。将数组从小到大排，依次放入中间。设 $ f_{i,j} $ 是指将最小的数依次插入，从 $i$ 到 $j$ 最优解，得转移方程：

```cpp
f[j][t]=max(f[j][t],max(f[j+1][t]+vi[t-j+1].x*abs(vi[i].id-j),f[j][t-1]+vi[t-j+1].x*abs(vi[i].id-t)));
```

(本人 LATEX 打的有点烦，用代码形式展示公式，请谅解。)

#### 最后贴上代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct node{
	int x,id;
};
int f[2005][2005],n,t,ans=0;
node vi[2005];
bool cmp(node a,node b){
	return a.x<b.x;
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>vi[i].x;
		vi[i].id=i;
	}
	sort(vi+1,vi+1+n,cmp);
	for(int i=1;i<=n;i++){
		for(int j=1;j+i-1<=n;j++){
			t=i+j-1;
			f[j][t]=max(f[j][t],max(f[j+1][t]+vi[t-j+1].x*abs(vi[i].id-j),f[j][t-1]+vi[t-j+1].x*abs(vi[i].id-t)));
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			ans=max(ans,f[i][j]);
		}
	}
	cout<<ans;
}
```


---

## 作者：Richard_H (赞：4)

这个题首先肯定可以想到贪心，第一想法肯定是先把所有数字由大到小遍历，然后每次都把它移动到离它最远的一边，结果就是连样例都过不了。于是题解区里面大部分都是区间 dp，然而事实上这个题贪心并非一无是处，我们可以用贪心对 dp 进行一定的优化。

首先，根据我们的数学直觉，在题目条件下，大的数字放在外面更有可能使答案更大，举个栗子：

假设 $a < b$，原序列是 `* * * a b`，经过对比可以发现，`b a * * *` 的答案是比 `a b * * *` 的答案优的（虽然并不一定是最优的）。

于是，我们依然按照原来的思路，从大到小枚举每个数字，但是我们并不直接放到最远的地方，而是左右两边二选一，看看放哪边最优，思路类似区间 dp，但空间复杂度从 $\mathcal{O(n^2)}$ 优化到了 $\mathcal{O(n)}$，时间上的只有一捏捏常数的优化。

说完解题思路，再讲具体代码思路：

1. 将数字从大到小排序，要带上下标，方便后面计算。
2. 遍历所有数字（为了方便表示，假设现在遍历到了第 $k$ 大的数字），用 $f_i$ 表示数组最左边已经放了 $i$ 个数字，最右边已经放了 $k - i$ 个数字的情况下的最大答案。
3. 遍历 $f$ 数组取最大值。

贴代码 ~

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long lol;
typedef pair<lol, int> pli;

const int N = 2005;
int n;
lol f[N];
pli a[N];

bool cmp (pli a, pli b) 
{return a.first > b.first;}

int main () {
    scanf ("%d", &n);
    for (int i = 1; i <= n; ++ i ) 
        scanf ("%lld", &a[i].first), a[i].second = i;
    
    sort (a + 1, a + n + 1, cmp);

    for (int i = 1; i <= n; ++ i ) 
        for (int j = i; ~j; -- j ) 
            f[j] = max (j == i ? 0 : f[j] + a[i].first * abs (n - i + j + 1 - a[i].second), 
                            !j ? 0 : f[j - 1] + a[i].first * abs (j - a[i].second));

    lol maxn = 0;
    for (int i = 0; i <= n; ++ i ) 
        maxn = max (maxn, f[i]);
    printf ("%lld\n", maxn);

    return 0;
}
```


---

## 作者：Laoshan_PLUS (赞：2)

想了半天贪心，贪的是不死心，最后被 @[No0Chenquanlin](https://www.luogu.com.cn/user/751575) 同志一句话点醒：

**“娃子可以给左也可以给右，有后效性，这是不能贪心的根本原因。” ——@[No0Chenquanlin](https://www.luogu.com.cn/user/751575)**

于是乖乖打区间 DP 了……

------------

将 $a$ 排个序，排序前存下每个元素的原位置，记为 $\textit{id}_i$。设 $\textit{dp}(i,j)$ 表示将 $a_1$ 到 $a_{j-i+1}$ 变到 $[i,j]$ 的最大贡献值。

初始化 $\textit{dp}(i,i)=a_1\lvert \textit{id}_1-i\rvert$，以此为基础扩大区间，则有：
$$
\textit{dp}(i,j)=\max\left(\textit{dp}(i+1,j)+a_{j-i+1}\lvert \textit{id}_{j-i+1}-i\rvert,\textit{dp}(i,j-1)+a_{j-i+1}\lvert \textit{id}_{j-i+1}-j\rvert\right)
$$

### Talk is cheap. Show me the code.

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

constexpr int MAXN = 2e3 + 5;
int n, dp[MAXN][MAXN];
struct Node {
	int val, id;
	friend bool operator < (Node a, Node b) {
		return a.val < b.val;
	}
} a[MAXN];

signed main() {
	ios::sync_with_stdio(0);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i].val;
		a[i].id = i;
	}
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; i++) dp[i][i] = a[1].val * abs(a[1].id - i);
	for (int len = 2; len <= n; len++)
		for (int i = 1; i + len - 1 <= n; i++) {
			int j = i + len - 1;
			dp[i][j] = max(dp[i + 1][j] + a[len].val * abs(a[len].id - i), dp[i][j - 1] + a[len].val * abs(a[len].id - j));
		}
	cout << dp[1][n] << '\n';

	return 0;
}
```

---

## 作者：nxd_oxm (赞：1)

# 思路

首先我们发现 $n \le 2000$，对于如果可以暴力贪心的题不可能范围这么小，划掉。

我们可以思考，对于每一个状态贪心：

- 选取最大的数首先放置。

- 如果最大数不在最边上，还为最优情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/2ptbyxs8.png)

- 那一定可以与最边上的数交换，因为交换后总贡献会加上最大数的值，而不管与最大的数交换的数（本图中 $a_n$）交换后会导致总贡献减了还是加了，操作一定会让总贡献增加。因为本图中 $a_{n-1}$ 为最大的数，设原贡献为 $q$，那现在的贡献应该为 $q+a_{i-1}-a_i$ 或 $q+a_{i-1}+a_i$，因为 $a_i \le a_{i-1}$，所以总贡献一定是加了。矛盾。

- 最大数放在最左侧同理。

- 综上，最大数应放在最左端或最右端。

首先先把数组排序，写个结构体存一下每个数的原位值。

所以我们可以给出 dp 的定义：$f_{i,j}$ 表示 $a_1 \sim a_{j-i+1}$ 这些数填到 $i \sim j$ 的最大值。

转移方程：

设 $p_i$ 为现在排序后在 $i$ 位置的数的原位置，则：

$$f_{i,j} = \max(f_{i,j-1}+(j-p_{j-i+1})_ \times a_{j-i+1},f_{i+1,j}+(p_{j-i+1}-i) \times a_{j-i+1})$$

最终答案应为 $f_{1,n}$。

## AC code
```cpp
#include<bits/stdc++.h>
#define int long long
#define f(i,j,n) for(int i=j;i<=n;i++)
using namespace std;
int n;
struct abc{
	int a;
	int i;
	friend bool operator <(abc a,abc b){
		return a.a<b.a;
	}
}a[2001];
int dp[2001][2001];
signed main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	cin>>n;
	f(i,1,n){
		cin>>a[i].a;
		a[i].i=i;
	}
	sort(a+1,a+1+n);
	for(int i=1;i<=n;i++)cout<<a[i].i<<" ";
	f(lon,1,n){
		for(int i=1;i+lon-1<=n;i++){
			int j=i+lon-1;
			dp[i][j]=max(dp[i][j-1]+(j-a[j-i+1].i)*a[j-i+1].a,dp[i+1][j]+(a[j-i+1].i-i)*a[j-i+1].a);
		}
	}
//	f(lon,1,n){
//		for(int i=1;i+lon-1<=n;i++){
//			int j=i+lon-1;
//			cout<<"--"<<i<<" "<<j<<"--\n";
//			cout<<dp[i][j]<<endl;
//		}
//	}
	cout<<dp[1][n]<<endl;
	return 0;
}
```

---

## 作者：CQ_Bab (赞：1)

# 思路
我们可能会第一时间觉得这时一个贪心但是我们发现这是错的，因为我们的 $a_i$ 后还跟了一个系数而有可能系数会决定所有而不一定是 $a_i$。然后我们来想 dp，我们定义 $f_{i,l}$ 为将前 $i$ 个数填到 $l\sim l+i-1$ 的最大值，但是我们可以发现这样的话我们需要枚举第 $i$ 个数填在哪里，那么这样无法通过此题，所以我们用一个贪心，先将 $a_i$ 排序，那么我们因为 $a_i$ 越大所以我们就只能将 $a_i$ 往 $l$ 和 $l+i-1$ 上方才会最大。

所以我们便可以得到一个状态转移方程为 $f_{i,l}=\max(f_{i-1,l}+a_{i}\times |i-wei_i|,f_{i-1,l+1}+a_{i}\times|(i+l-1)-wei_i|)$ 这里的 $wei_i$ 存的是在原数组中 $a_i$ 的位置。

最后的答案就是 $f_{n,1}$。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std ;
#define int long long
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define rep1(i,x,y) for(int i=x;i>=y;i--)
#define fire signed
#define kong putchar(' ')
#define end putchar('\n')
#define in(x) scanf("%lld",&x)
#define lcm(x,y) x*y/__gcd(x,y)
#define w(x)  while(x--)
#define il inline
il void print(int x) {
	if(x>=10) print(x/10);
	putchar(x%10+'0');
}
struct node{
	int x,id;
}s[1010100];
int n;
bool cmp(node a,node b) {
	return a.x<b.x;
} 
int f[2100][2100];
fire main() {
	in(n);
	rep(i,1,n) in(s[i].x),s[i].id=i;
	sort(s+1,s+1+n,cmp);
	f[0][0]=1;
	rep(l,1,n) {
		for(int i=1;i+l-1<=n;i++) {
			f[l][i]=max(f[l-1][i]+s[l].x*abs(s[l].id-(l+i-1)),f[l-1][i+1]+s[l].x*abs(s[l].id-i)); 
		}
	}
	cout<<f[n][1];
	return false;
}

```

---

## 作者：Eric_jx (赞：1)

## 思路详解

首先，我们很容易想到一个贪心的思想，就是把 $a_i$ 最大的数移到离他最远的位置。显然，这是错误的。

考虑区间 dp。先按照 $a_i$ 由小到大排序，设 $dp_{i,j}$ 表示将前 $j-i+1$ 个数移动到区间 $[l,r]$ 的最大贡献。

初始化：$dp_{i,j}=0$。 

考虑将第 $l$ 个数移到 $i$ 和 $j$ 上，设 $pos_i$ 表示排序后位置 $i$ 原来的位置，则可得到状态转移方程： 

$dp_{i,j}=\max(dp_{i,j-1}+a_l\times|pos_l-j|,dp_{i+1,j}+a_l\times|pos_l-i|)$ 

注意区间 dp 在程序实现中要先枚举长度，接着枚举左端点，计算出右端点，再状态转移。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct Node{
    long long v,pos;
}a[20005];
bool cmp(Node x,Node y){
	return x.v<y.v;
}
long long f[2005][2005];
int main(){
    long long n;
    cin>>n;
    for(long long i=1;i<=n;i++){
        scanf("%lld",&a[i].v);
        a[i].pos=i;
    }
    sort(a+1,a+n+1,cmp);
    for(long long l=1;l<=n;l++){
        for(long long i=1;i+l-1<=n;i++){
            long long j=i+l-1;
            f[i][j]=max(f[i][j],f[i+1][j]+a[l].v*abs(a[l].pos-i));
            f[i][j]=max(f[i][j],f[i][j-1]+a[l].v*abs(a[l].pos-j));
        }
	}
    cout<<f[1][n];
    return 0;
}
```

---

## 作者：BMTXLRC (赞：1)

### 题目大意：

有 $n$ 个数 $a_i$，将 $a_i$ 放到第 $j$ 个位置上会获得 $a_i\times\lvert j-i\rvert$ 分，一个位置只能放一个数，问最大可以获得多少分。

### 错解（简单介绍）：

考虑把第 $i$ 个数与第 $j$ 个位置都连起来，容量为 $1$，费用为 $-a_i\times\lvert j-i\rvert$（取负数是方便跑费用流）。

源点和汇点的连边就不说了，跑费用流可以获得 TLE。

### 正解：

设 $dp_{l,r}$ 表示选 $r-l+1$ 个数，将他们移到 $[l,r]$ 中的最大分数。

先把 $a$ 排序，$a_i$ 越小则带来的影响就越小，$a_i$ 越大应该移动的越远，就尽可能地往区间的两端移动，因此我们可以考虑的区间只有一个（这是由于数要移动地尽可能远）。

因此我们假设第 $i$ 个数移到了 $l$ 上，则 $dp_{l,r}=dp_{l+1,r}+a_i\times \lvert pos_i-l\rvert$，如果移到了 $r$ 上，则 $dp_{l,r}=dp_{l,r-1}+a_i\times\lvert r-pos_i\rvert$。

于是我们可以得到总状态转移方程：

$$
\begin{cases}
dp_{l,r}=\max(dp_{l,r},dp_{l+1,r}+a_i\times\lvert pos_i-l\rvert,dp_{l,r-1}+a_i\times \lvert r-pos_i\rvert)\\
dp_{i,i}=a_1\times \lvert i-pos_1\rvert
\end{cases}
$$

### 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e3+5;
int dp[N][N],n;
struct people{int x,node;}a[N];
bool cmp(people x,people y){return x.x<y.x;}
signed main(){
    scanf("%lld",&n);
    for(register int i=1;i<=n;i++) scanf("%lld",&a[i].x),a[i].node=i;
    sort(a+1,a+n+1,cmp);
    for(register int i=1;i<=n;i++) dp[i][i]=a[1].x*abs(a[1].node-i);
    for(register int i=2;i<=n;i++){
        for(register int l=1;l+i-1<=n;l++){
            int r=l+i-1;
            dp[l][r]=max(dp[l][r],max(dp[l+1][r]+a[i].x*abs(a[i].node-l),dp[l][r-1]+a[i].x*abs(r-a[i].node)));
        }
    }
    printf("%lld",dp[1][n]);
}
```

---

## 作者：fly_x (赞：0)

# 思路

这题很多人可能会当成**贪心**来做，即：尽量把大的数移到尽量远的位置（最左或最右），但是你很快会发现这种方法是错误的，于是考虑 **dp**。

那么不妨**把贪心作为 dp 的一种优化**：
1. 从大到小枚举每个数；
2. 分别考虑放在最左/右的情况。

这样的话只需要开**一维数组**，大大压缩了空间。

此时的状态转移方程为（其中原先处于第 $i$ 个下标数 $a_i$ 的下标用 $id_i$ 表示）：

$$f_j = \max(f_j+a_i\times(n-i+j-id_i),f_{j-1}+a_i\times(j-id_i))$$

# 代码
具体实现上，需要注意的有：
1. 不开 long long 见祖宗；
2. 因为要对输入的数重新排序，又要记录它们的下标，所以可以使用结构体或 pair 等数据结构；
3. 不能把数放在原先的位置上；
4. 注意下标越界。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long // 注意事项 1
ll n, x, y, ans, f[2005];
struct _data{ll num, id;} a[2005]; // 直接写 data 会 CE
bool cmp(_data x, _data y){return x.num > y.num;}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i].num);
	for (int i = 1; i <= n; i++) a[i].id = i;
	sort(a + 1, a + n + 1, cmp);
	for (int i = 1; i <= n; i++)
		for (int j = n; j >= 0; j--){
			if (i == j) x = 0; // 注意事项 3
			else x = f[j]+a[i].num*abs(n-i+j+1-a[i].id);
			if (j == 0) y = 0; // 注意事项 4
			else y = f[j-1]+a[i].num*abs(j-a[i].id);
			f[j] = max(x, y);
		}
	for (int i = 1; i <= n; i++) ans = max(f[i], ans);
	cout << ans;
	return 0;
}

```

---

## 作者：zhangxiaohan007 (赞：0)

## 思路
题目要求最大的值，所以我们要让大的的尽量往两边放，这样就可以让它最大化，因为大的要让它重排移动的距离越大越好。所以我们考虑可以用区间动规来实现。

对于动态规划来说，最重要的三要素：

+ 设计状态
+ 动态转移方程
+ 初始化

区间动态规划的状态很好设计，对于这道题来说 $dp_{i,j}$ 就表示区间 $i$ 到 $j$ 的最大权值。有了状态，转移方程就比较好想了，以下就将转移方程给大家呈现出来：

$dp_{i,j}=\max(dp_{i,j-1}+a_{j-i+1}\times \operatorname{abs}(x-j) ,dp_{i+1,j}+a_{j-i+1}\times \operatorname{abs}(x-i))$

其中 $\operatorname{abs}(x)$ 表示 $x$ 的绝对值。

有了状态转移方程，代码应给就很好写了，这里就不呈现出来了。注意，这里的区间动规没有了最里面那层循环。因为有两层循环，所以时间复杂度就是$O(n^2)$

---

## 作者：wth2026 (赞：0)

# 题目大意
给定 $n$ 个数，现在要将其重排。

如果 $a_i$ 于重排前在第 $i$ 个位置，现在移动到了第 $j$ 个位置，那么对答案的贡献就是 $|j-i|\times a_i$。

现在，你需要让答案尽可能大。
# 题目思路
其实感觉挺好想的。

首先可以轻易的证明，权值大的肯定比权值小的更优先。而且如果移动的话，肯定是移动到头。

先用一个数组 $f_{l,r}$ 表示还有 $l$ 到 $r$ 的区间是未安排的，当前所能产生的最大权值。

使用一个函数进行计算，每一次传入 $l$、$r$、$x$，分别表示当前已经选择到了 $l$ 到 $r$ 的区间，选择到了第 $x$ 个数，按照上面给的思路模拟即可。
# AC Code
```cpp
#include <bits/stdc++.h>

#define endl '\n'
#define float double
#define int long long
#define inf 0x3f3f3f3f

using namespace std;

int n, f[2005][2005];

struct z {
	int a, id;
} a[2005];

bool cmp(z q, z w) {
	return q.a > w.a || (q.a == w.a && q.id < w.id);
}

int ans(int l, int r, int x) {
	if (l > r) {
		return 0;
	}
	
	if (f[l][r] != 0) {
		return f[l][r];
	}
	
	if (x > n) {
		return 0;
	}
	
	int m[2];
	m[0] = ans(l + 1, r, x + 1) + abs(a[x].id - l) * a[x].a;
	m[1] = ans(l, r - 1, x + 1) + abs(r - a[x].id) * a[x].a;
	f[l][r] = max(m[0], m[1]);
	return f[l][r];
}

void init() {
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	init();
	
	cin >> n;
	
	for (int i = 1; i <= n; ++ i) {
		cin >> a[i].a;
		a[i].id = i;
	}
	
	sort(a + 1, a + n + 1, cmp);
	cout << ans(1, n, 1);
	return 0;
}
```

---

## 作者：zhouyiran_2011 (赞：0)



## 思路

看到这个题，很容易想到贪心，但经过~~暴算~~仔细分析后可发现，贪心连样例都过不了。

所以，我们来考虑动态规划：

先将所有数按从小到大排序，设 $dp_{l,r}$ 表示将 $r-l+1$ 这些数放入 $[l,r]$ 这一区间的最优解，那么对于每一个数，放到这个区间的两端肯定是最优的。因此我们可以得到转移方程（$a_{i}$ 表示这个数的贡献，$p_{i}$ 表示这个数原来的位置）：

$$dp_{l,r}=\max(dp_{l+1,r}+a_{i}×|p_{i}-l|,dp_{l,r-1}+a_{i}×|r-p_{i}|)$$

最终结果为 $dp_{1,n}$。

## 代码:


------------

```
#include<bits/stdc++.h>
#define ll long long //记得开long long 
using namespace std;
ll dp[2005][2005];
ll n;
struct node{ //可以用结构体存储 
	ll p, v;
}a[2005];
bool cmp(node a, node b){
	return a.v<b.v;
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].v;	
		a[i].p=i;
	}
	sort(a+1, a+n+1, cmp);//排序
	for(int i=1;i<=n;i++)
	{
		for(int l=1;l+i-1<=n;l++)
		{
			ll r=l+i-1;
			dp[l][r]=max(dp[l+1][r]+a[i].v*abs(a[i].p-l),dp[l][r-1]+a[i].v*abs(r-a[i].p));//我是用结构体存储的，可能与上面的dp式子不太一样
		}
	}
	cout<<dp[1][n]; 
	return 0;
}

```

### 完结撒花！


---

## 作者：君のNOIP。 (赞：0)

### 贪心+dp

------------

一开始，首先想到贪心，很明显要优先挪 $a_i$ 最大的人，并移到两端。

我一开始也是这样想，每次将 $a_i$ 最大的挪到离他距离最大的那边。结果样例都没过，最后发现并不是这样最优。

于是我们考虑**区间 dp**。

设 $dp_{i,j}$ 为将区间 $[i,j]$ 排好后的最大值，我们只需先按 $a_i$ 从小到大排序，枚举第 $i$ 个人和左端点即可，由于区间长度确定，右端点也是确定的。

转移方程：
```
dp[l][r] = max(dp[l][r-1] + ma * abs(t - r), dp[l+1][r] + ma * abs(t - l));
```

其中 $t$ 表示当前该人原来的位置， $ma$ 表示该人的 $a_i$。

Code：
```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
#define G() Cr = getchar()
int Xr, Fr; char Cr;
inline int rd() {
	Xr =0 , Fr = 1, G();
	while(Cr < '0' || Cr > '9') {if(Cr == '-') Fr = -1; G();}
	while(Cr >='0' && Cr <= '9') Xr = (Xr<<1) + (Xr<<3) + (Cr&15), G();
	return Xr * Fr;
}
#define MAX_N 2005
#define LL long long
int n;
LL ans;
LL dp[MAX_N][MAX_N];
struct node {
	int pos;
	LL va;
}e[MAX_N];
bool comp(node x,node y) {
	return x.va < y.va;
}
int main() {
	n = rd();
	for(int i = 1; i <= n; i++) e[i].va = rd(), e[i].pos = i;
	sort(e+1,e+1+n,comp);
	for(int i = 1; i <= n; i++) {
		LL ma = e[i].va, t = e[i].pos;
		for(int l = 1, r = l + i - 1; r <= n; l++, r++)
			dp[l][r] = max(dp[l][r-1] + ma * abs(t - r), dp[l+1][r] + ma * abs(t - l));
	}
	cout<<dp[1][n]<<endl;
}
```


---

## 作者：Furina_Saikou (赞：0)

~~教练正好讲了这题，题解正好开着，我就来水咕力。~~

这题其实不蓝（谐音梗扣钱），别被颜色吓着了。

# 思路

先说思路，遇到动规先想贪心，或多或少有所收获。

因为每个点移动玩的价值为它的值乘上移动距离，显然越大的数要移的越远，毕竟 $n\le2000$，贪心可不是这数据范围，我们可以用区间动规。

我们先从小到大排序 $a$ 数组，用结构体以便保存下标，接着我们定义 $dp_{l,r}$ 表示将 $a_{r-l+1}$ 填到区间 $[l,r]$ 所得到的最大价值，因为我们排过序，所以只需要考虑将 $a_{r-l+1}$ 填到区间的两边就能达成局部最优。

于是我们就获得了状态转移方程：$dp_{l,r}=\max(dp_{l+1,r}+a_{len_{val}}\times \left|a_{len_{id}}-l\right|,dp_{l,r-1}+a_{len_{val}}\times \left| a_{len_{id}-r}\right|)$。

其中，$len$ 表示区间长度，相当于 $r-l+1$，$id$ 是对应 $a_i$ 排序前的下标。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2001;
struct node{
	int id,val;
}a[N];
int n,dp[N][N];
bool cmp(node a,node b)
{
	return a.val<b.val;//实现结构体 sort
}
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].val;
		a[i].id=i;//记录值与下标
	}
	sort(a+1,a+1+n,cmp);
	for(int len=1;len<=n;len++)
	{
		for(int l=1,r=len;r<=n;l++,r++)
		{
			dp[l][r]=max(dp[l+1][r]+a[len].val*abs(a[len].id-l),dp[l][r-1]+a[len].val*abs(a[len].id-r));
		}
	}
	cout<<dp[1][n];//当范围扩展到[1,n]时就能概括全局
	return 0;
}
```

---

## 作者：ZBH_123 (赞：0)

## 题目分析

显然，要使总贡献最大，需要让大的数尽量移动得多，换句话说就是要让大的数填入未填数的区间的两端。假设当前区间为 $[l,r]$，则第 $r-l+1$ 小的数需要填入 $l$ 或 $r$。因此，我们可以使用区间 DP。定义 $dp_{l,r}$ 表示将 $[l,r]$ 填完能得到的最大贡献，$p_i$ 表示第 $i$ 小的数在原序列的位置，$b_i$ 表示第 $i$ 小的数，则我们可以推出下面的状态转移方程：

$$dp_{l,r}=\max{(dp_{l,r-1}+|p_{r-l+1}-r| \cdot b_{r-l+1},dp_{l+1,r}+|p_{r-l+1}-l| \cdot b_{r-l+1})}$$

接下来是初始化，按照区间 DP 的模板，我们应该初始化每一个 $dp_{i,i}$。回顾状态的定义，我们可以得出 $dp_{i,i}=b_1 \cdot |p_1-i|$。

综上所述，这样做的时间复杂度为 $O(n^2+n)=O(n^2)$，能够通过本题。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int n;
ll dp[2005][2005];
struct node{
	int v,id;
}a[2005];

bool cmp(node x,node y){
	return x.v<y.v;
}

void solve(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].v;
		a[i].id=i;
	}
	
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++) dp[i][i]=1ll*a[1].v*abs(a[1].id-i);
	for(int len=2;len<=n;len++){
		for(int l=1;l+len-1<=n;l++){
			int r=l+len-1;
			dp[l][r]=max(dp[l][r-1]+1ll*a[len].v*abs(a[len].id-r),dp[l+1][r]+1ll*a[len].v*abs(a[len].id-l));
		}
	}
	
	cout<<dp[1][n]<<'\n';
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int T=1;
//	cin>>T;
    while(T--) solve();
    return 0;
}
```

---

## 作者：cloud2764scallop_eve (赞：0)

## 思路
第一次看题很快就能想到贪心。一个大的值无非放到左边和右边，哪边增加的多放到哪边。但是有可能存在两边增加的一样的情况，同时不同的选择会影响以后的数值，所以贪心是错误的。

既然是对后面的数值有影响，那就是明显的 DP。先排个序，从大到小，然后每次先选未选过的最大的，枚举其在左右的两种情况。

DP 方程如下：
$$dp_{l,r} = \max(dp_{l + 1, r} + a_{now} \times |pos_{now} - l|,dp_{l, r - 1} + a_{now} \times |pow_{now} - r|)$$

## 代码
重要的事情说三遍：  
一定要开 `long long`！  
一定要开 `long long`！  
一定要开 `long long`！
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2005;
int n;
pair<int, int> a[N];
int f[N][N];
signed main() {
	scanf("%lld", &n);
	for (int i = 0; i < n; i++) {
		scanf("%lld", &a[i].first);
		a[i].second = i;
	}
	sort(a, a + n, greater<pair<int, int>>());
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= i; j++) {
			int k = i - j;
			f[j + 1][k] = max(f[j + 1][k], f[j][k] + a[i].first * abs(a[i].second - j));
			f[j][k + 1] = max(f[j][k + 1], f[j][k] + a[i].first * abs(n - k - 1 - a[i].second));
		}
	}
	int ans = 0;
	for (int i = 0; i <= n; i++)
		ans = max(ans, f[i][n - i]);
	printf("%lld", ans);
	return 0;
}
```

---

