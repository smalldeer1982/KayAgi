# Photoshoot for Gorillas

## 题目描述

你非常喜欢大猩猩，于是你决定为它们组织一次拍摄活动。大猩猩生活在丛林中，丛林被表示为一个有 $n$ 行 $m$ 列的网格，有 $w$ 个大猩猩同意参与拍摄，第 $i$ 个大猩猩的身高为 $a_i$ .你希望将所有大猩猩放置在网格的单元格中，并且确保每个单元格中最多只有一只大猩猩。

每种方案的壮观程度等于网格中所有以 $k$ 为边长的子正方形的壮观程度的总和。

子正方形的壮观程度等于其中所有大猩猩的身高的总和。

从所有合适的方案中选出最壮观的方案。

## 样例 #1

### 输入

```
5
3 4 2
9
1 1 1 1 1 1 1 1 1
2 1 1
2
5 7
20 15 7
9
4 1 4 5 6 1 1000000000 898 777
1984 1 1
4
5 4 1499 2004
9 5 5
6
6 7 14 16 16 6```

### 输出

```
21
12
49000083104
3512
319```

# 题解

## 作者：XYzero (赞：4)

## 题意

有一个 $n$ 行 $m$ 列的网格，有 $w$ 只大猩猩，每只大猩猩都有一个高度 $a_i$，现在让你把这 $w$ 只大猩猩放进网格中。

**最大化**边长为 $k$ 的所有子方格的奇观之和，任意一个子方格的奇观之和为子方格中大猩猩的高度之和。

## 分析

### 贪心 + 差分

首先，边长为 $k$ 的子方格，在一般情况下是会有重叠的格子，即一个格子被统计到多个子方格中。

我们考虑要尽可能的让高度更高的大猩猩，放在被统计次数更多的格子里面，这样会让奇观之和尽可能的大。

那如何计算出一个格子被统计的次数呢？

我们可以枚举子方格的左上端点，然后对以其为左上端点的子方格进行**二维差分**。

差分完，再对差分数组进行一遍**二维前缀和**，再把二维数组中的值存进一个一维数组，从大到小排序。

对数组 $a$ 也从大到小排序，最后统计贡献即可。

## Code:


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
ll T,n,m,k,w,h[N],num[N],pos,ans;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin >> T; 
	while(T --){
		pos = 0,ans = 0;
		cin >> n >> m >> k;
		ll c[n + 10][m + 10],pre[n + 10][m + 10]; 
		memset(c,0,sizeof(c));
		memset(pre,0,sizeof(pre));//多测要清空 
		cin >> w;
		for(int i = 1;i <= w;i++){
			cin >> h[i];
		} 
		for(int i = 1;i <= n - k + 1;i++){
			for(int j = 1;j <= m - k + 1;j++){
				int x = i,y = j,X = min(n,i + k - 1),Y = min(m,j + k - 1);
				c[x][y] ++;
				c[X + 1][Y + 1] ++;
				c[x][Y + 1] --;
				c[X + 1][y] --;//二维差分模版 
			} 
		}
		for(int i = 1;i <= n;i++){
			for(int j = 1;j <= m;j++){
				pre[i][j] = (pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1] + c[i][j]);
				// 二维前缀和模版 
			} 
		}
		for(int i = 1;i <= n;i++){
			for(int j = 1;j <= m;j++){
			    num[++pos] = pre[i][j];
			} 
		}
		sort(num + 1,num + 1 + pos,greater<ll>());
		sort(h + 1,h + 1 + w,greater<ll>());//从大到小排序 
		for(int i = 1;i <= w;i++){
			ans += 1ll * h[i] * num[i];//统计贡献 
		}
		cout << ans << "\n"; 
	}
	
	return 0;
} 
```

---

## 作者：liuzhengtao (赞：1)

## 分析
考虑贪心，很显然，高度更高的大猩猩，在更多的子方格中（即被计算更多次），壮观的和会越大。（其实就是往中间站）

而计算被计算次数可以用前缀和和差分做，用 ```sort``` 排序即可。

思路已有，代码略。

---

## 作者：__youzimo2014__ (赞：1)

# CF2000E Photoshoot for Gorillas

## 整体思路

我们可以想象一个边长为 $k$ 的正方形，在一个 $n$ 行 $m$ 列的矩阵上扫。

声明：以下称“矩阵”为长度为 $k$ 的矩阵。

我们定义一个二位数组 $f$，$f_{i,j}$ 表示 $(i, j)$ 这个位置矩阵扫到的次数，扫到的次数越高，把越高的大猩猩放进去，壮观程度越大。

对于一个格子 $(i, j)$，扫到的次数是**横向扫到的次数**乘**纵向扫到的次数**。


## 怎么求纵向扫到的次数和横向扫到的次数

现在我们要想的是，怎么求纵向扫到的次数，横向扫到的次数和纵向扫到的次数可以使用类似的方法。

为了方便，我们说矩阵是从上往下扫。

很容易发现，扫的时候，第一次扫到 $i$ 时，矩阵最下边的位置是 $\max(i, k)$，而最后一次扫到 $i$ 时，矩阵最下面的位置是 $\min(i+k-1, n)$。

现在就很简单了，我们只需要用矩阵最后一次扫到的位置减去矩阵第一次扫到的位置，然后加 $1$，就可以得到答案了。

## 最后的细节

$f$ 数组现在求出来了，怎么知道最大的几个呢？

我们需要给矩阵排序，怎么做？

其实我们没必要开一个二维数组，直接开一个 $n \times m$ 的一位数组，就可以了。

下标就是 $(i-1)\times m + (j-1)$。

## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int read() {
    int res = 0;
    char ch;
    while (true) {
        ch = getchar();
        if (ch == -1 || ch == ' ' || ch == '\n') break;
        if (ch >= '0' && ch <= '9') {
            res *= 10;
            res += ch-'0';
        }
    }
    return res;
}
signed main() {
    int t = read();
    while (t--) {
        int n = read(), m = read(), k = read(), w = read();
        vector<int> a(w+1, 0ll);
        for (int i = 0; i < w; i++) {
            a[i] = read();
        }
        vector<int> f(n*m, 0ll);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                int direction =  min(i+k-1, n) - max(i, k) + 1;
                int transverse = min(j+k-1, m) - max(j, k) + 1;
                f[(i-1)*m+j-1] = direction * transverse;
            }
        }
        sort(f.begin(), f.end(), greater<int>());
        sort(a.begin(), a.end(), greater<int>());
        int ans = 0;
        for (int i = 0; i < a.size(); i++) {
            ans += a[i] * f[i];
        }
        cout << ans << endl;
    }
    return 0;
}

```

---

## 作者：CNS_5t0_0r2 (赞：0)

一个显然的贪心策略是让身高高的大猩猩往中间站，这样其能包含在更多的子正方形中。

剩下的问题就是如何统计了。

首先我们得解决每个方格被多少个子正方形包含，这个可以用前缀和 + 差分解决（由于 $n \times m \leq 2 \times 10 ^ 5$ 但 $n,m \leq 2 \times 10 ^ 5$），所以数组要开在 ``main`` 函数内。

然后把每个格子被子正方形包含的个数降序排列，执行贪心策略即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 9;
int n,m,k,w;
int a[N];
bool cmp(int x,int y){
	return x > y;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int T;
	cin >> T;
	while(T--){
		ll ans = 0;
		cin >> n >> m >> k;
		ll c[n + 9][m + 9],s[n + 9][m + 9];//差分,前缀和数组
		memset(c,0,sizeof c);//不要忘了清空
		memset(s,0,sizeof s);
		vector<ll> vec;//s中的所有元素 
		cin >> w;
		for(int i = 1;i <= w;i++)
			cin >> a[i];
		sort(a + 1,a + w + 1,cmp);
		for(int i = 1;i <= n - k + 1;i++){
			for(int j = 1;j <= m - k + 1;j++){
				int x1 = i,y1 = j,x2 = min(n,i + k - 1),y2 = min(m,j + k - 1);
				c[x1][y1]++;
				c[x2 + 1][y2 + 1]++;
				c[x1][y2 + 1]--;
				c[x2 + 1][y1]--;
			} 
		}
		for(int i = 1;i <= n;i++)
			for(int j = 1;j <= m;j++){
				s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + c[i][j];
				vec.push_back(s[i][j]);
			}
		sort(vec.begin(),vec.end(),cmp);
		for(int i = 1;i <= w;i++)
			ans += vec[i - 1] * a[i];
		cout << ans << '\n';
	}
	return 0;
}
```

---

## 作者：dutianchen1 (赞：0)

# CF2000E Photoshoot for Gorillas

### 题意概括

在 $n \times m$ 的矩阵中选 $w$ 格放入给定的权值之一，使得所有大小为 $k \times k$ 的子矩阵中权值和的和最大。

### 思路简析

我们想要让所有子矩阵权值和最大，一个显然的贪心策略就是把权值较大的放在计算次数多的格子中。

那么我们只需要二维差分加上前缀和，求出整个大矩阵中，每个点在 $k \times k$ 的子矩阵中出现了几次。

然后我们把每个节点出现次数存下来，倒序排列。选择其中出现次数最多的 $w$ 个填入值，就可以得到我们要求的最大权值和。

代码如下：



```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e3+5;
inline ll read()
{
	ll x=0,f=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
ll t;
ll n,m,k;
ll w,res,cnt;
ll num[N*N];
ll ans[N*N];
bool cmp(ll x,ll y){
	return x>y;
}
int main()
{
	t=read();
	while(t--){
		n=read();m=read();k=read();
		ll cha[n+5][m+5];
		ll sum[n+5][m+5];
		w=read();
		for(int i=0;i<=n+1;i++)for(int j=0;j<=m+1;j++){cha[i][j]=0;sum[i][j]=0;}
	//	memset(ans,0,sizeof(ans));
		cnt=res=0;
		for(int i=1;i<=w;i++)num[i]=read();
		sort(num+1,num+1+w,cmp);
		for(int i=1;i<=n-k+1;i++){
			for(int j=1;j<=m-k+1;j++){
				ll X=min(n,i+k-1),Y=min(m,j+k-1);
				cha[i][j]++;cha[X+1][Y+1]++;
				cha[X+1][j]--;cha[i][Y+1]--;
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+cha[i][j];
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				ans[++cnt]=sum[i][j];//记录每个地块被计算次数 
			}
		}
		sort(ans+1,ans+1+cnt,cmp);
		for(int i=1;i<=w;i++){
			res+=(1ll*ans[i]*num[i]);
		}
		cout<<res<<'\n';
	}


	return 0;
}
 
```

---

## 作者：hanser520 (赞：0)

# CF2000E Photoshoot for Gorillas
## 题意理解
你被给出了一个 $n \times m$ 的矩阵 $w$ 只大猩猩，每只大猩猩有一个高度 $a_i$ 你需要将大猩猩分配至矩阵中，以最大化每一个 $k \times k$ 的子矩阵中大猩猩高度之和的总和。
## 算法分析
观察到，一个矩阵的单元有时会被不止一次地被拍摄到，易得出贪心思路：使高度大的大猩猩尽可能多地被拍摄到。

酱紫，这道题就成为了一道纯粹的数学题，只需要求出每个单元格被拍摄的次数，此后贪心匹配。

### 最Naive的朴素算法
观察到，我会枚举！对于枚举每一个子矩形的左上角，我们可以对每个子矩形中的元素进行一次自增运算，从而得到每个单元的拍摄次数。

蛋柿，很明显嗷，整个运算过程需要枚举一次点，每次自增需要修改 $k^2$ 个节点，时间复杂度来到了丧心病狂的 $O(nmk^2)$ 。绝对会TLE掉的。

### 朴素算法的树状数组优化
这个 $k^2$ 看着可以好好优化一下，于是掏出二维树状数组进行区间修改，单点查询，的确优化成 $\log^2k$ 了。

不过，还是太麻烦了，不如直接推柿子 $O(1)$ 解决。
### 最终解法
对于每一个单元，计算左右上下相距 $k$ 格的空间内能塞下几个 $k \times k$ 的子矩阵。最终时间复杂度为 $O(nm \log w)$。

这时候，聪明的小伙伴就要问了：为什么多出一个$\log w$？

当然是因为贪心匹配需要排序啦。
### Talk is cheap, show your code.

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
template<class T>
void write(T x){
    if(x < 0)putchar('-'),x = -x;
    if(x > 9)write(x / 10);
    putchar(x % 10 + '0');
}
template<class T>
inline T read(){
    T x = 0, f = 1;char ch = getchar();
    while(ch < '0'||ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
    return x * f;
}
template<class T> inline T read(T &x){ return x = read<T>();}
template<class T, class... Args> inline void read(T &x, Args&... args){ read(x), read(args...);}
const int N = 2e5 + 10;
ll n, m, k, v, ans;
priority_queue<ll> q;
priority_queue<ll> t;
int main(){
    ll T = read<int>();
    while(T--){
        while(!q.empty())q.pop();
        while(!t.empty())t.pop();
        ans = 0;
        read(n, m, k);
        for(ll i = 1; i <= min(n, k); i++){
            for(ll j = 1; j <= min(m, k); j++)
                q.push(min(i * j, min(n - k + 1, i) * min(m - k + 1, j)));
            for(ll j = k + 1; j <= m; j++)
                q.push(min(i * min(m - j + 1, k), min(n - k + 1, i) * min(m - k + 1, min(m - j + 1, k))));
        }
        for(ll i = k + 1; i <= n; i++){
            for(ll j = 1; j <= min(m, k); j++)
                q.push(min(min((n - i + 1), k) * j, min(n - k + 1, min((n - i + 1), k)) * min(m - k + 1, j)));
            for(ll j = k + 1; j <= m; j++)
                q.push(min(min((n - i + 1), k) * min(m - j + 1, k), min(n - k + 1, min((n - i + 1), k)) * min(m - k + 1, min(m - j + 1, k))));
        }
        read(v);
        for(int i = 1; i <= v; i++)t.push(read<ll>());
        while(!t.empty())ans += q.top() * t.top(), q.pop(), t.pop();
        write(ans);
        putchar('\n');
    }
    return 0;   
}//赛时A完这题被拖下去睡觉了（悲）
```

---

## 作者：_dbq_ (赞：0)

## 前言
没有读题的同学可以点击[这里](https://www.luogu.com.cn/problem/CF2000E)或[这里](https://codeforces.com/problemset/problem/2000/E)读题。

本题使用知识点：**数学**、**贪心**。

## 思路
我们可以把子矩阵理解成一个边长为 $k$ 的方框，方框在矩阵上扫动，但不能超出边界。

定义 $cnt_{x,y}$ 为第 $x$ 行、第 $y$ 列的方格被扫到的次数。

注意到，当 $cnt_{x,y}$ 越大，将越高的猩猩放进去收益越大。

因此我们应先计算 $cnt_{x,y}$，其次贪心计算收益。

每一个方格被扫到的次数等于**横向扫到的次数**与**纵向扫到的次数**之**积**，且不能超出边界，所以我们可以得到一个位于第 $x$ 行、第 $y$ 列的方格 $\text{横向扫到的次数}=\min(y+k-1,m)-\max(y,k)+1$、$\text{纵向扫到的次数}=\min(x+k-1,n)-\max(x,k)+1$。

最后得出 $cnt_{x,y}=(\min(x+k-1,n)-\max(x,k)+1)\times(\min(y+k-1,m)-\max(y,k)+1)$。

## 代码

```cpp
#include<iostream>
#include<iomanip>
#include<algorithm>
#include<cmath>
#include<string>
#include<stdlib.h>
#include<cstdio>
#include<cstring>
#include<queue>
#include<stack>
#include<vector>
#define LL long long
#define ULL unsigned long long
#define cint const int 
using namespace std;
cint INTINF=0x7f7f7f7f;
const LL LLINF=9e18;
cint N=2e5+10;
LL a[N],tmp;
int b[N];
inline LL read(){
    LL x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-'){
            f=-1;
        }
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}
void write(LL x){
    if(x<0){
        putchar('-');
        x=-x;
    }
    if(x>9){
        write(x/10);
    }
    putchar(x%10+'0');
    return ;
}
void put(LL num){
    write(num);
    putchar('\n');
}
bool cmp(LL a,LL b)
{
    return a>b;
}
void solve()
{
    cint n=read(),m=read(),k=read();
    for(int i=1;i<=n;i++)//hang
    {
        for(int j=1;j<=m;j++)//lie
        {
            a[++tmp]=1ll*(min(i+k-1,n)-max(i,k)+1)*(min(j+k-1,m)-max(j,k)+1);
            //将最后得到的公式带入，为了后面排序方便，我直接扔进数组里了
        }
    }
    //排序后直接贪心
    sort(a+1,a+1+tmp,cmp);
    cint w=read();
    for(int i=1;i<=w;i++)
        b[i]=read();
    sort(b+1,b+1+w,cmp);
    LL ans=0;
    for(int i=1;i<=w;i++)
    {
        //最大值相乘
        ans+=(1ll*a[i]*b[i]);
    }
    put(ans);
    return ;
}
int main()
{
    #ifdef dbq
    freopen("1.in","r",stdin);
    freopen("1.out","w",stdout);
    #endif
    int T=read();
    while(T--)
    {
        tmp=0;//要清空
        solve();
    }
    return 0;
}
```

---

## 作者：Ke_scholar (赞：0)

# [Photoshoot for Gorillas](https://codeforces.com/contest/2000/problem/E)

## 前言

赛时的时候看成 $1\le n,m\le 1\times 10^5$ 了，一直在想着怎么 $O(1)$ 的计算，后来发现是 $1\le n\cdot m\le 1\times 10^5 $，那么直接无脑二维前缀和即可。

## 思路

前置知识，推荐先学习二维差分前缀和通过此题练手 [P3397 地毯](https://www.luogu.com.cn/problem/P3397) 。

回到此题，我们可以二维差分处理出所有长度为 $k$ 的正方形的覆盖范围，然后再用二维前缀和计算每个格子被覆盖的次数，最后将覆盖的值取出和 $a$ 数组一样从大到小排序，对应相乘取前 $w$ 个的和即可。

## 代码

```c++
#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

void solve() {

    i64 n, m, k, w;
    cin >> n >> m >> k >> w;

    vector<i64> a(w);
    for (int i = 0; i < w; i ++) {
        cin >> a[i];
    }

    sort(a.begin(), a.end(), greater<>());


    vector v(n + 2, vector<int>(m + 2));
    auto sum = v;
    for (int i = 1; i + k <= n + 1; i ++) {
        for (int j = 1; j + k <= m + 1; j ++) {
            v[i][j] ++, v[i][j + k] --;
            v[i + k][j]--, v[i + k][j + k]++;
        }
    }

    vector<i64> d;
    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= m; j ++) {
            v[i][j] += v[i - 1][j] + v[i][j - 1] - v[i - 1][j - 1];
            d.push_back(v[i][j]);
        }
    }

    sort(d.begin(), d.end(), greater<>());

    i64 ans = 0;
    for (int i = 0; i < w; i ++) {
        ans += d[i] * a[i];
    }

    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
```

---

