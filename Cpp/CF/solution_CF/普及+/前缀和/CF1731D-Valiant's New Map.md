# Valiant's New Map

## 题目描述

Game studio "DbZ Games" wants to introduce another map in their popular game "Valiant". This time, the map named "Panvel" will be based on the city of Mumbai.

Mumbai can be represented as $ n \times m $ cellular grid. Each cell $ (i, j) $ ( $ 1 \le i \le n $ ; $ 1 \le j \le m $ ) of the grid is occupied by a cuboid building of height $ a_{i,j} $ .

This time, DbZ Games want to make a map that has perfect vertical gameplay. That's why they want to choose an $ l \times l $ square inside Mumbai, such that each building inside the square has a height of at least $ l $ .

Can you help DbZ Games find such a square of the maximum possible size $ l $ ?

## 说明/提示

In the first test case, we can choose the square of side $ l = 2 $ (i. e. the whole grid) since the heights of all buildings are greater than or equal to $ 2 $ .

In the second test case, we can only choose the side as $ 1 $ , so the answer is $ 1 $ .

In the third test case, there are no squares of size $ 2 $ that have all buildings of height at least $ 2 $ , so the answer is $ 1 $ .

## 样例 #1

### 输入

```
4
2 2
2 3
4 5
1 3
1 2 3
2 3
4 4 3
2 1 4
5 6
1 9 4 6 5 8
10 9 5 8 11 6
24 42 32 8 11 1
23 1 9 69 13 3
13 22 60 12 14 17```

### 输出

```
2
1
1
3```

# 题解

## 作者：yeshubo_qwq (赞：9)

## Solution

注意到如果存在边长为 $mid$ 的符合条件的正方形，则一定存在边长 $<mid$ 的符合条件的正方形，可见，此题具有单调性，考虑二分答案。

如何判断是否存在长度为 $mid$ 的符合条件的正方形？先根据每个位置的数值将原矩阵转换为 $01$ 矩阵，然后做前缀和，然后枚举是否存在全 $0$ 的正方形即可。

数据范围 $1\le n \cdot m\le10^6$，数组开不下，使用 `vector`。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int T,n,m,i,j,l,r,mid,ans;
vector <int> a[N],b[N];
bool check(int mid){
	int i,j;
	for (i=1;i<=n;i++)
		for (j=1;j<=m;j++)
			b[i][j]=(a[i][j]<mid);
	for (i=1;i<=n;i++)
		for (j=1;j<=m;j++)
			b[i][j]=b[i][j]+b[i-1][j]+b[i][j-1]-b[i-1][j-1];
	for (i=1;i+mid-1<=n;i++)
		for (j=1;j+mid-1<=m;j++)
			if (b[i+mid-1][j+mid-1]-b[i-1][j+mid-1]-b[i+mid-1][j-1]+b[i-1][j-1]==0)
				return 1;
	return 0;
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>T;
	while (T--) {
		cin>>n>>m;
		b[0].clear();
		for (j=0;j<=m;j++) b[0].push_back(0);
		for (i=1;i<=n;i++){
			a[i].clear(),a[i].push_back(0),b[i].clear(),b[i].push_back(0);
			for (j=1;j<=m;j++)
				cin>>l,a[i].push_back(l),b[i].push_back(0);
		}
		l=1,r=n;
		while (l<=r){
			mid=(l+r)>>1;
			if (check(mid)) l=(ans=mid)+1;
				else r=mid-1;
		}
		cout<<ans<<'\n';
	}
	return 0;
}

```


---

## 作者：mlvx (赞：7)

这是一篇不需要麻烦思路的题解。

---

显然的，若存在以 $x$ 为边长的正方形，则一定存在边长更小的正方形，故具有单调性，可以二分正方形的边长。

---

考虑 `check` 函数如何实现。

暴力的方法是直接枚举左上端点，确定矩阵，求出矩阵内的最小值。

如果一个子矩阵内的最小值已经 $\ge l$ 了，则这个子矩阵内的所有值都是 $\ge l$ 的。

---

既然是正方形子矩阵查询，而且是静态区间，可以使用二维 st 表来维护。

令 $dp_{i,j,k}$ 表示左上端点为 $(i,j)$，右下端点为 $(i+2^k-1,j+2^k-1)$ 的矩阵的最小值。

显然可以将这个矩阵拆分为左上、左下、右上、右下四个矩阵，再进行分别计算。

---

![](https://cdn.luogu.com.cn/upload/image_hosting/yde2m6yl.png)

几个颜色不同的正方形代表不同的子矩阵。

递推式即为 $dp_{i,j,k}=\min(dp_{i,j,k-1},dp_{i+2^{k-1},j,k-1},dp_{i,j+2^{k-1},k-1},dp_{i+2^{k-1},j+2^{k-1},k-1})$。

---

下图中 $k=\lfloor\log_2c\rfloor$。

![](https://cdn.luogu.com.cn/upload/image_hosting/k17bk4cm.png)

几个颜色不同的正方形代表不同的子矩阵。

左上端点为 $(i,j)$，边长为 $c$ 的正方形内的最小值就是 $\min(dp_{i,j,\lfloor\log_2c\rfloor},dp_{i+c-2^{\lfloor\log_2c\rfloor},j,\lfloor\log_2c\rfloor},dp_{i,j+c-2^{\lfloor\log_2c\rfloor},\lfloor\log_2c\rfloor},dp_{i+c-2^{\lfloor\log_2c\rfloor},j+c-2^{\lfloor\log_2c\rfloor},\lfloor\log_2c\rfloor})$。

---

但是注意到 $mn\le10^6,n\le m$。显然的，$m$ 会大于 $10^3$，所以正常开开不了。

考虑压维。

可将 $dp_{i,j,k}$ 变成 $dp_{(i-1)\times m+j,k}$。

由于 $j\le m$，所以这样压维不会造成冲突。

第一维仅需开到 $10^6$ 即可，因为其最值为 $mn$。

第二维开到 $\lfloor\log_2 n\rfloor$ 就够了，考虑 $dp$ 维护的是正方形，所以边长最大取整个矩阵的短边，即为 $n$。

---

时间复杂度 $O(mn\log\min(m,n))$。

---

AC 代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1010,L=11;
int T,n,m,l,r,mid,lg[N],dp[N*N][L];
int f(int a,int b){return (a-1)*m+b;}//压维函数
int query(int x,int y,int c){
	int k=lg[c];
	return min(min(dp[f(x,y)][k],dp[f(x+c-(1<<k),y)][k]),min(dp[f(x,y+c-(1<<k))][k],dp[f(x+c-(1<<k),y+c-(1<<k))][k]));//查询
}bool check(int c){
	for(int i=1;i<=n-c+1;i++)for(int j=1;j<=m-c+1;j++)if(query(i,j,c)>=c)return 1;
	return 0;
}int main(){
	cin>>T;
	for(int i=2;i<N;i++)lg[i]=lg[i>>1]+1;//预处理 log2，貌似比自带的函数更快
	while(T--){
		cin>>n>>m;
		for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)scanf("%d",&dp[f(i,j)][0]);
		for(int l=1;l<L;l++)
			for(int i=1;i+(1<<l-1)<=n;i++)
				for(int j=1;j+(1<<l-1)<=m;j++)
					dp[f(i,j)][l]=min(min(dp[f(i,j)][l-1],dp[f(i+(1<<l-1),j)][l-1]),min(dp[f(i,j+(1<<l-1))][l-1],dp[f(i+(1<<l-1),j+(1<<l-1))][l-1]));//转移式
		for(l=0,r=min(n,m)+1;l+1<r;check(mid=l+r>>1)?l=mid:r=mid);//二分
		cout<<l<<'\n';
	}return 0;
}
```

---

## 作者：jianhe (赞：6)

[CF1731D Valiant's New Map](https://www.luogu.com.cn/problem/CF1731D)
题解

### 算法：二分和二维前缀和

思路：用二维前缀和数组来存储是否符合条件。

考虑在一个矩阵中，如何计算从 $ ( 1 , 1 ) $ 到 $ ( x , y ) $ 这一部分的和呢？可以用 $ f_{i,j} $ 表示从 $ ( 1 , 1 ) $ 到 $ ( i ,j ) $ 的总和，则 $ f_{i,j} \gets f_{i-1,j} + f_{i,j-1} - f_{i-1,j-1} + a_{i,j} $，中间之所以要减去是因为重复计算了。

因为并不确定 $ n $ 和 $ m $ 的值，所以要用 `vector`，注意要先动态开空间之后才能当作数组使用。

### 代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=1e6+10;
ll T,n,m,ans,t,l,r,mid;
vector<ll> a[N],f[N];
bool check(ll p){
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			f[i][j]=a[i][j]<mid;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			f[i][j]+=f[i-1][j]+f[i][j-1]-f[i-1][j-1];
	for(int i=1;i+p<=n;i++)
		for(int j=1;j+p<=m;j++)
			if(!(f[i+p][j+p]+f[i-1][j-1]-f[i-1][j+p]-f[i+p][j-1]))
				return 1;
	return 0;
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
		cin>>n>>m;
		f[0].clear();
		for(int i=0;i<=m;i++) f[0].push_back(0);		
		for(int i=1;i<=n;i++){
			a[i].clear();
			a[i].push_back(0);
			f[i].clear();
			f[i].push_back(0);
			for(int j=1;j<=m;j++){
				cin>>t;
				a[i].push_back(t);
				f[i].push_back(0);
			}
		}
		l=1,r=n;
		while(l<=r){
			mid=l+r>>1;
			if(check(mid-1)) l=mid+1,ans=mid;
			else r=mid-1;
		}
		cout<<ans<<"\n";
    }
	return 0;
}

```

---

## 作者：hank0402 (赞：4)

显然，答案具有单调性，故考虑二分答案。

那么问题转化为判定性的，我们可以将矩阵中大于等于 $mid$ 的设置为 `1`，否则设置为 `0`，观察到 $n\times m\leq 10^6$，故我们可以枚举左上端点，由于知道矩阵大小，我们可以利用二维前缀和很快求出 01 矩阵的子矩阵的数字和，若存在这个和为 $mid^2$，也就是全部为 `1` 的，便是一个符合条件的子矩阵。

复杂度为 $\Theta\left(nm\log \max\{n,m\}\right)$ 的，足以通过本题。

[Code](https://codeforces.com/contest/1731/submission/188818942)

---

## 作者：slzx2022YuYihan (赞：3)

# Solution

容易发现，答案具有**单调性**，于是想到**二分**。

因为只知道 $n\times m\le10^6$，所以用一维数组代替二维数组。

对于每次二分，可以设一个 $b$ 数组，若 $a$ 数组中这个数小于 $mid$，$b$ 数组对应的位置为 $\mathbb{1}$；反之为 $\mathbb{0}$。

然后对 $b$ 数组进行二维前缀和，记为 $sum$ 数组。然后对 $mid\times mid$ 的各个区间进行判断是否全为 $\mathbb{0}$。如果是，$l=mid+1$；否则，$r=mid-1$。

还要注意一些细节，在前缀和访问时可能会访问到负数，所以一律加上 $10^6+5$ 才能保证不会RE。

------------
# Code

```cpp
/*
ID:YuYihan
LANG:C++11
PROG:
*/
#include<bits/stdc++.h>
#define IOS ios :: sync_with_stdio(false), cin.tie(0), cout.tie(0);
#define int long long
using namespace std;
inline int read(){
    int s = 0, w = 0;
    char ch = getchar();
    while  (!isdigit(ch))   w |= (ch == '-'), ch = getchar();
    while (isdigit(ch)) s = (s << 1) + (s << 3) + (ch ^ 48), ch = getchar();
    if (w)  return ~(s - 1);
    return s;
}
const int N = 2e6 + 5;
const int NN = 1e6 + 5;
int a[N], b[N], sum[N];
int T, n, m;
signed main(){
    //freopen(".in", "r", stdin), freopen(".out", "w", stdout);
    //IOS
    T = read();
    while (T--){
        n = read(), m = read();
        for (int i = 1; i <= n * m; i++)    a[i + NN] = read();
        int l = 1, r = min(n, m), ans;
        while (l <= r){
            int mid = (l + r) >> 1;
            for (int i = 1; i <= n * m; i++)
                if (a[i + NN] < mid)    b[i + NN] = 1;
            	else    b[i + NN] = 0;
            for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                sum[(i - 1) * m + j + NN] = sum[(i - 2) * m + j + NN] + sum[(i - 1) * m + j - 1 + NN] - sum[(i - 2) * m + j - 1 + NN] + b[(i - 1) * m + j + NN];
            bool flag = 0;
            for (int i = mid; i <= n; i++){
                for (int j = mid; j <= m; j++)
                    if (sum[(i - 1) * m + j + NN] - sum[(i - mid - 1) * m + j + NN] - sum[(i - 1) * m + j - mid + NN] + sum[(i - mid - 1) * m + j - mid + NN] == 0){
                        l = mid + 1;
                        flag = 1;
                        ans = mid;
                        break;
                    }
                if (flag)   break;
            }
            if (!flag)  r = mid - 1;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
```

---

## 作者：yinhee (赞：2)

[题目传送门](https://codeforces.com/contest/1731/problem/D)

## 解题思路：二分+前缀和

尽管限制了正方形边长，$l$ 的取值还是满足单调性的，故可以二分。每次 check 时，将 $\geq mid$ 的位置设为 $1$，反之为 $0$。这样问题就转换为了是否存在一个 $mid\times mid$ 的全为 $1$ 的正方形。二维前缀和解决即可。

code：

```cpp
int n,m,h[N],sum[N];
inline int get_id(int x,int y){return x*m+y+1;}
bool check(int k){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			sum[get_id(i,j)]=sum[get_id(i-1,j)]+sum[get_id(i,j-1)]-sum[get_id(i-1,j-1)]+(h[get_id(i,j)]>=k);
		}
	}
	for(int i=k;i<=n;i++){
		for(int j=k;j<=m;j++){
			if(sum[get_id(i,j)]+sum[get_id(i-k,j-k)]-sum[(get_id(i-k,j))]-sum[get_id(i,j-k)]==k*k)return true;
		}
	}
	return false;
}
void solve(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			scanf("%d",&h[get_id(i,j)]);
		}
	}
	int l=1,r=1e6,ans=1;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid))l=mid+1,ans=mid;
		else r=mid-1;
	}
	printf("%d\n",ans);
}
signed main(){
	int t=1;
	scanf("%d",&t);
	while(t--)solve();
}
```

---

## 作者：tZEROちゃん (赞：2)

dp + 二分答案。

考虑转化为一个经典问题：

> 给定一个只包含 $0$ 和 $1$ 的矩阵，选择一个正方形，使得正方形内只含有 $1$，求最大边长。

设 $dp_{i, j}$ 表示以 $(i,j)$ 为右下角，可构成的最大正方形的边长，不难写出状态转移方程：

$$dp_{i, j}=\min\{dp_{i-1,j-1},dp_{i-1,j},dp_{i,j-1}\}+1 \ (a_i = 1)$$


答案是 $dp$ 数组的最大值。

显然，这道题目的要求与本题类似，假设我们已知要求的最低高度，那么显然直接把状态转移里的限制 $a_i = 1$ 改为 $a_i \ge one$，其中 $one$ 是我们希望的最低高度。


如何得到 $one$ 呢？考虑二分答案，把上面这个 $dp$ 扔到判断是否是合法解的函数里，若 $dp$ 出来的答案满足 $ans\ge one$，则返回 `true`，否则返回 `false`。

赛时代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

int q;

int n, m;

bool check(int one, vector<vector<int>> a) {
   int ans = 0;
   vector<vector<int>> dp(n + 1, vector<int> (m + 1));
   for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= m; ++j) {
         if (a[i][j] < one) continue;
         dp[i][j] = min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]}) + 1;
      }
   }
   for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= m; ++j) {
         if (dp[i][j] > ans) ans = dp[i][j];
      }
   }
   return (ans >= one);
}

void solve() {
   cin >> n >> m;
   vector<vector<int>> a(n + 1, vector<int> (m + 1));
   for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= m; ++j) {
         cin >> a[i][j];
      }
   }
   int l = 1, r = min(n, m), ans;
   while (l <= r) {
      int mid = (l + r) >> 1;
      if (check(mid, a)) {
         ans = mid, l = mid + 1;
      } else {
         r = mid - 1;
      }
   }
   cout << ans << '\n';
}

int main() {
   cin >> q;
   while (q--) {
      solve();
   }
}
```

---

## 作者：loser_seele (赞：1)

前置知识：单调队列，建议先学习后完成。另外二维 ST 表和朴素 dp 应该也能过。

不难发现答案具有显然的单调性，因为如果区间扩大原来不符合条件的区间现在一定仍然不符合条件。

于是考虑二分答案 $ l $，每次判断每个 $ l \times l $ 的区间内最小值是否都 $ \geq l $ 即可。

问题转化为：给定 $ n \times m $ 的矩阵，求所有 $ l \times l $ 的矩阵内的最小值。这就是一个经典问题了，用单调队列实现，具体见 [P2216](https://www.luogu.com.cn/problem/P2216)。

总时间复杂度 $ \mathcal{O}(nm\log{\min(n,m)}) $，可以通过。代码就不贴了。

---

## 作者：FiraCode (赞：0)

显然的，答案有单调性，可以二分。

然后对于二分的值 $l$，我们把原矩阵所以值 $a_{i,j}$ 变为 $\min(a_{i,j},l)$。

然后就是枚举周长为 $l$ 的正方形的右下角，然后看区间和是不是 $l^3$ 即可。

```cpp
#include <bits/stdc++.h>

using namespace std;

int T;
int n, m;
vector<vector<int>> a, s;

bool check(int l) {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + min(l, a[i][j]);
        }
    }

    for (int i = l; i <= n; ++i) {
        for (int j = l; j <= m; ++j) {
            if (s[i][j] - s[i - l][j] - s[i][j - l] + s[i - l][j - l] >= l * l * l) return true;
        }
    }

    return false;
}

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        a.resize(n + 1);
        s.resize(n + 1);
        for (int i = 0; i <= n; ++i) a[i].resize(m + 1), s[i].resize(m + 1);

        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                scanf("%d", &a[i][j]);

        int l = 1, r = min(n, m);
        while (l < r) {
            int mid = (l + r + 1) >> 1;

            if (check(mid)) l = mid;
            else r = mid - 1;
        }

        printf("%d\n", l);
    }

    return 0;
}
```

---

## 作者：YuYuanPQ (赞：0)

# CF1731D Valiant's New Map 题解

## 题目大意

给定一个带权值的 $n×m$ 网格，你可以选取一块边长为 $l$ 的正方形区域当且仅当该区域的所有权值都大于等于 $l$，问可以选取的最大正方形区域的边长。

## 分析

前置知识：二维前缀和。

发现答案具有单调性，于是上二分（二分的是正方形区域的边长）。

怎么判断该区域的所有权值都大于等于 $l$ 呢？那么此时设 $1$ 个 $s$ 数组，当 $d_{i,j}$ $<$ $l$ 时，$s_{i,j}$ $=$ $1$；否则 $s_{i,j}$ $=$ $0$。

通过二维前缀和，我们可以 $\mathcal{O}{(1)}$ 快速判断该区域的值是否全为 $1$（也就是该区域的所有权值都大于等于 $l$）。

完结撒花~

## 注意

- $1 \leq n \cdot m \leq 10^6$ ，要用 `vector`。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define MAXN 1000010
using namespace std;
int T,n,m;
vector<int>d[MAXN],s[MAXN];
int ans;
int qread()
{
	int sum=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') {sum=(sum<<1)+(sum<<3)+ch-48;ch=getchar();}
	return sum*f;
}
void qprint(int x)
{
	if(x>9) qprint(x/10);
	putchar(x%10+48);
	return;
}
void qp(int x)
{
	if(x<0) x=-x,putchar('-');
	qprint(x);
	return;
}
void qprintll(ll x)
{
	if(x>9) qprintll(x/10);
	putchar(x%10+48);
	return;
}
void qpll(ll x)
{
	if(x<0) x=-x,putchar('-');
	qprintll(x);
	return;
}
void cl(int l)
{
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			s[i][j]=(d[i][j]<l);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			s[i][j]+=s[i][j-1]+s[i-1][j]-s[i-1][j-1];
	return;
}
int itmin(int x,int y){return x<y?x:y;}
bool check(int l)
{
	cl(l);
	for(int i=1;i+l-1<=n;i++)
		for(int j=1;j+l-1<=m;j++)
			if(!(s[i+l-1][j+l-1]+s[i-1][j-1]-s[i+l-1][j-1]-s[i-1][j+l-1]))
				return 1;
	return 0;
}
void ef()
{
	int l=1,r=itmin(n,m),mid=0;//r取min(n,m)
	while(l<=r)
	{
		mid=l+r>>1;
		if(check(mid))
			l=mid+1,ans=l-1;
		else r=mid-1;
	}
	return;
}
int main()
{
	T=qread();
	while(T--)
	{
		n=qread();
		m=qread();
		for(int i=0;i<=n;i++) d[i].clear(),s[i].clear();//初始化第0~n行
		for(int i=0;i<=m;i++) s[0].push_back(0);//初始化第1行
		for(int i=1;i<=n;i++) d[i].push_back(0),s[i].push_back(0);//初始化第0个位置
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				d[i].push_back(qread()),s[i].push_back(0);//输入
		ef();//二分
		qp(ans);
		putchar('\n');
	}
	return 0;
}
```

## 附

- [题目链接](https://www.luogu.com.cn/problem/CF1731D)
- [我的提交记录](https://www.luogu.com.cn/record/list?pid=CF1731D&user=1029900)

---

## 作者：WAis_WonderfulAnswer (赞：0)

##  二分 + 二维前缀和

答案明显符合单调性，所以考虑二分。

每次二分 $l$，对于原数组 $a$ 构造一个新数组 $s$，如果 $a _ {i,j} \ge l$，则 $s _ {i,j} = 1$，否则 $s _ {i,j} = 0$。然后对 $s$ 求一个二维前缀和，然后双重循环遍历边长为 $l$ 的矩形，通过二维前缀和求出这个矩形所对应的 $01$ 矩阵的这个矩形的数字和，显然如果这个和为 $l ^ 2$，也就是这个矩形全为 $1$，说明里面每个元素都 $\ge l$，符合要求，所以返回 ```true```。

**注意事项**：因为 $n \cdot m \leq 10 ^ 6$，所以需要用 ```vector``` 存储。其次不要开 ```long long```，会内存超限。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int>a[1000010],s[1000010];
int _,n,m;
bool check(int x)
{
	for (int i=1;i<=n;i++) s[i].clear();
	for (int i=1;i<=m;i++) s[0].push_back(0);
	for (int i=1;i<=n;i++) s[i].push_back(0);
	for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) s[i].push_back((int)(a[i][j]>=x));
   //预处理前缀和
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=m;j++)
		{
			s[i][j]=s[i-1][j]+s[i][j-1]-s[i-1][j-1]+s[i][j];
		}
	}
  //遍历所有边长为x的矩形
	for (int i=1;i+x-1<=n;i++)
	{
		for (int j=1;j+x-1<=m;j++)
		{
			int x_1=i,y_1=j,x_2=i+x-1,y_2=j+x-1;
			int sm=s[x_2][y_2]-s[x_2][y_1-1]-s[x_1-1][y_2]+s[x_1-1][y_1-1];
			if (sm%x==0&&sm/x==x) return true;
		}
	}
	return false;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>_;
	while (_--)
	{
		cin>>n>>m;
		for (int i=1;i<=n;i++) a[i].clear();
		for (int i=1;i<=m;i++) a[0].push_back(0);
		for (int i=1;i<=n;i++) a[i].push_back(0);
		for (int i=1;i<=n;i++)
		{
			for (int j=1;j<=m;j++)
			{
				int x;
				cin>>x;
				a[i].push_back(x);
			}
		}
  		//二分
		int l=1,r=1000000,best=-1;
		while (l<=r)
		{
			int mid=(l+r)/2;
			if (check(mid))
			{
				best=mid;
				l=mid+1;
			}
			else
			{
				r=mid-1;
			}
		}
		cout<<best<<'\n';
	}
	return 0;
}
```

---

## 作者：tallnut (赞：0)

一道适合练手的二分+二维前缀和题目。
# 思路
## 二分答案部分
二分答案 $l$ 并依次检查 $l$ 是否能做到。这一部分套二分板子即可。关键是如何实现 check() 函数。

对于没学过二分的人：二分就是说一开始设定一个区间
$$[l,r]$$
依次判断 $mid$（也就是
$$(l+r)/2$$
）是否符合要求，符合要求则更新答案 $ans$，并
$$l \gets mid + 1$$
（省略 $mid$ 前面的部分）；否则
$$r \gets mid - 1$$
。（这是求最大值，最小值的倒过来即可）
## 检查 $l$ 部分
提示：像这种“找一个最大正方形/长方形使得它满足一些有关数字比较的条件”的题目经常会用二维前缀和。

这一部分强烈建议去做 P1387，思路和这一部分几乎完全一样。~~话说 P1387 不是动规题吗，但我却用二维前缀和水过了。~~

在存储数值的数组 $a$ 之外再添一个存储二维前缀和的数组 $b$，如果该位置的数据小于 $l$ 则将这个点的值记为 $1$，否则记为 $0$。对于每个位置取二维前缀和，在 check() 函数里枚举每一个正方形，判断：如果这个正方形的二维前缀和等于 $l$ 的平方说明这个正方形合法，返回 true；否则返回 false。
## 细节
~~由于我这人太懒了不愿意用一维数组~~，普通的二维数组又会爆全局变量空间，于是我使用了动态 new 和 delete。
# AC代码
[AC记录](https://www.luogu.com.cn/record/125238020)，代码中有注释。
```
#include <iostream>
using namespace std;
int t,n,m,l,r,mid,ans,tmp,k,o,tmpmid;
//太大了，普通数组开不下，使用动态数组
int** a;
int** b;
//申请动态数组
void require()
{
	a = new int*[n + 1];
	for (int i = 0;i <= n;i++)
		a[i] = new int[m + 1];
	b = new int*[n + 1];
	for (int i = 0;i <= n;i++)
		b[i] = new int[m + 1];
}
//释放动态数组
void release()
{
	for (int i = 0;i <= n;i++)
		delete [] a[i];
	delete [] a;
	for (int i = 0;i <= n;i++)
		delete [] b[i];
	delete [] b;
}
//写入前缀和
void write()
{
	for (int i = 1;i <= n;i++)
		for (int j = 1;j <= m;j++)
		{
			tmp = a[i][j] >= mid;
			//二维前缀和板子
			b[i][j] = b[i - 1][j] + b[i][j - 1] - b[i - 1][j - 1] + tmp;
		}
}
//检查该mid行不行
bool check()
{
	tmpmid = mid * mid;
	for (int i = 1;i <= (n - mid + 1);i++)
		for (int j = 1;j <= (m - mid + 1);j++)
		{
			k = i + mid - 1;
			o = j + mid - 1;
			//二维前缀和板子
			tmp = b[k][o] - b[i - 1][o] - b[k][j - 1] + b[i - 1][j - 1];
			if (tmp == tmpmid) return true;
		}
	return false;
}
int main()
{
	cin >> t;
	while (t--)
	{
		cin >> n >> m;
		require();
		for (int i = 0;i <= n;i++)
			for (int j = 0;j <= m;j++)
			{
				if (i == 0 || j == 0) a[i][j] = 0;
				else cin >> a[i][j];
				b[i][j] = 0;
			}
		//二分板子
		l = 1;
		r = min(n,m);
		ans = 0;
		while (l <= r)
		{
			mid = (l + r) >> 1;
			write();
			if (check())
			{
				l = mid + 1;
				ans = mid;
			}
			else r = mid - 1;
		}
		cout << ans << '\n';
	}
}
```
我这个代码跑的很慢，数据量最大的测试点用了 1.4s，有什么提高运行效率的方法请私信作者。

---

## 作者：Gaode_Sean (赞：0)

看到“使边长最大”，很容易想到用二分判定的方式来解决此题。

很显然，只用二分是行不通的，于是考虑用 dp 作为二分判定的内容。

设 $dp_{i,j}$ 表示以 $(i,j)$。右下角，可构成的最大正方形的边长，不难写出状态转移方程：$dp_{i,j}=\min\{dp_{i-1,j},dp_{i,j-1},dp_{i-1,j-1}\}+1(mid \leq a_{i,j})$

若 dp 数组中的最大值大于等于 $mid$，返回 ```true```，否则返回 ``false``。

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
vector<int> vec[N],f[N];
int T,n,m;
bool check(int len)
{
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(vec[i][j]>=len) f[i][j]=min(f[i-1][j],min(f[i-1][j-1],f[i][j-1]))+1;
			else f[i][j]=0; ans=max(ans,f[i][j]);
		}
	}
	return ans>=len;
}
void solve()
{
	scanf("%d%d",&n,&m);
	for(int i=0;i<=n;i++)
	{
		vec[i].resize(m+1),f[i].resize(m+1);
		if(!i) continue;
		for(int j=1;j<=m;j++) scanf("%d",&vec[i][j]);
	}
	int l=1,r=min(n,m);
	while(l<r)
	{
		int mid=(1+l+r)>>1;
		//cout<<mid<<endl;
		if(check(mid)) l=mid;
		else r=mid-1;
	}
	printf("%d\n",l);
}
int main()
{
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```

---

## 作者：Withers (赞：0)

~~蒟蒻第二次做出D~~

可以发现最后的答案具有单调性，考虑二分

每次二分需要判断是否存在一个边长为 $x$ 的正方形矩阵，其中所有的数都大于 $x$

我们可以使用二维st表来解决，枚举矩阵左上角，用st表预处理出 $(i,j)$ 到  $(i+2^k-1,j+2^k-1)$ 的最小值，然后查询时类似普通st表处理。时间复杂度 
 $ \mathcal{O}(nm \log \max(n,m))$

code：
```cpp
	rd(n);
    rd(m);
    int g[n + 1][m + 1];
    //rep(i,1,n) g[i].resize(m+10);
    rep(i, 2, max(n, m)) Log2[i] = Log2[i / 2] + 1;
    int f2[n + 1][m + 1][Log2[max(n, m)] + 2];
    rep(i, 1, n) {
        rep(j, 1, m) {
            rd(g[i][j]);
            f2[i][j][0] = g[i][j];
        }
    }

    for (int k = 1; k <= Log2[max(m, n)]; k++) {
        for (int i = 1; i + (1 << k) - 1 <= n; i++) {

            for (int j = 1; j + (1 << k) - 1 <= m; j++) {
                int d = 1 << (k - 1);
                f2[i][j][k] = min(min(f2[i][j][k - 1], f2[i + d][j][k - 1]),
                                  min(f2[i][j + d][k - 1], f2[i + d][j + d][k - 1]));
            }
        }
    }

    int l = 1, r = min(n, m);

    while (l <= r) {
        int mid = (l + r) / 2;
        bool flg = 0;
        int x = mid;
        rep(i, 1, n - x + 1) {
            rep(j, 1, m - x + 1) {
                int k = Log2[x], d = x - (1 << k);

                if (min(min(f2[i][j][k], f2[i][j + d][k]),
                        min(f2[i + d][j][k], f2[i + d][j + d][k])) >= x) {
                    flg = 1;
                    break;
                }
            }

            if (flg)
                break;
        }

        if (flg)
            l = mid + 1;
        else
            r = mid - 1;
    }

    cout << r << endl;
```




---

