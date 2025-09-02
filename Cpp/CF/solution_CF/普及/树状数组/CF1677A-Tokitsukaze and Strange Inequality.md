# Tokitsukaze and Strange Inequality

## 题目描述

Tokitsukaze has a permutation $ p $ of length $ n $ . Recall that a permutation $ p $ of length $ n $ is a sequence $ p_1, p_2, \ldots, p_n $ consisting of $ n $ distinct integers, each of which from $ 1 $ to $ n $ ( $ 1 \leq p_i \leq n $ ).

She wants to know how many different indices tuples $ [a,b,c,d] $ ( $ 1 \leq a < b < c < d \leq n $ ) in this permutation satisfy the following two inequalities:

 $ p_a < p_c $ and $ p_b > p_d $ . Note that two tuples $ [a_1,b_1,c_1,d_1] $ and $ [a_2,b_2,c_2,d_2] $ are considered to be different if $ a_1 \ne a_2 $ or $ b_1 \ne b_2 $ or $ c_1 \ne c_2 $ or $ d_1 \ne d_2 $ .

## 说明/提示

In the first test case, there are $ 3 $ different $ [a,b,c,d] $ tuples.

 $ p_1 = 5 $ , $ p_2 = 3 $ , $ p_3 = 6 $ , $ p_4 = 1 $ , where $ p_1 < p_3 $ and $ p_2 > p_4 $ satisfies the inequality, so one of $ [a,b,c,d] $ tuples is $ [1,2,3,4] $ .

Similarly, other two tuples are $ [1,2,3,6] $ , $ [2,3,5,6] $ .

## 样例 #1

### 输入

```
3
6
5 3 6 1 4 2
4
1 2 3 4
10
5 1 6 2 8 3 4 10 9 7```

### 输出

```
3
0
28```

# 题解

## 作者：郑朝曦zzx (赞：6)

# 一 题目分析
看到数据范围 $\sum n \le 5000$ 就大体能判断本题正解应该是 $O(n^2)$ 的，暴力枚举 $a, b, c, d$ 显然会 TLE。经过分析，我们只需 $O(N^2) $枚举 $b, c$ 就能 $O(1)$ 计算符合条件的 $a, d$ 组数。

为了计算方便，我先用 $O(n^2)$ 的时间复杂度预处理出 $S_{i,j}$ 和 $L_{i, j}$，分别表示从 $i$ 到 $j$ 的区间中，$num_j$ 为最大值时小于其的数的个数和 $num_i$ 为最大值时小于其的数的个数。

最后我们就可以在枚举 $b, c$ 时用前缀和的方法计算出符合要求的 $a, d$ 组数。
# 二 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
inline int read()
{
	bool flag = true;
	char c = getchar();
	if (c == '-') flag = false;
	while(!(c >= '0' && c <= '9')) c = getchar();
	int x = 0;
	while(c >= '0' && c <= '9')
	{
		x = (x << 3) + (x << 1) + c - '0';
		c = getchar();
	}
	if (flag == true) return x;
	return -x;
}

int num[5010];
int S[5010][5010], L[5010][5010]; 
int main()
{
//	freopen("input.in", "r", stdin);
	int t = read();
	while (t--)
	{
		LL ans = 0ll;
		int n = read();
		for (int i = 1; i <= n; ++i)
			num[i] = read();
		for (int i = n; i >= 1; --i)
		{
			for (int j = i + 1; j <= n; ++j)
			{
				if (num[j] > num[i])
				{
					S[i][j] = S[i + 1][j] + 1;
					L[i][j] = L[i][j - 1];
				}
				else
				{
					S[i][j] = S[i + 1][j];
					L[i][j] = L[i][j - 1] + 1;
				}
			}
		}
		for (int b = 2; b + 2 <= n; ++b)
			for (int c = b + 1; c + 1 <= n; ++c)
				ans += (LL)(S[1][c] - S[b][c]) * (LL)(L[b][n] - L[b][c]);
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				S[i][j] = L[i][j] = 0;
		printf("%lld\n", ans);
	}
    return 0;
}
```
最后请记得开 long long。

---

## 作者：cfkk (赞：3)

### 题面描述：

给一个长度为 $n$ 的排列 $p_1,p_2,\dots,p_n$，求有多少个四元组 $(a,b,c,d)$ 满足 $a<b<c<d$ 和 $p_a<p_c\ p_b>p_d$ 
，$n\le5000,T\le1000$

### 思路 $1$，暴力：

通过四层循环枚举 $a,b,c,d$，复杂度 $O(n^4\times T)$，通过 $4$ 个点。

### 思路 $2$，预处理：

考虑枚举 $b,c$。

在 $b,c$ 固定的情况下，答案就转换为：在 $b$ 左边小于 $p_c$ 的数乘上 $c$ 右边小于 $p_b$ 的数。要是暴力枚举的话又是 $O(n^2)$ 的复杂度，所以我们可以把所有数的左边小于和右边小于的数就可以用 $O(n^2)$ 的复杂度得到答案。

$\color{green} AC$ 代码：
``` cpp
#include<iostream>
#include<cstring>
using namespace std;
typedef long long LL;
const int maxn = 5005, INF = 0x3f3f3f3f;
int a[maxn], sum1[maxn][maxn], sum2[maxn][maxn];
bool v[maxn];
int n;

int main(){
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(0);

    int T;
    cin >> T;
    while(T--){
        cin >> n;
        for(int i = 1; i <= n; i++) cin >> a[i];
        for(int i = 1; i <= n; i++) v[i] = 0;
        for(int i = 1; i <= n; i++){
            int s = 0;
            for(int j = 1; j <= n; j++){
                sum1[i][j] = s;
                s += v[j];
            }
            v[a[i]] = 1;
        }
        for(int i = 1; i <= n; i++) v[i] = 0;
        for(int i = n; i; i--){
            int s = 0;
            for(int j = 1; j <= n; j++){
                sum2[i][j] = s;
                s += v[j];
            }
            v[a[i]] = 1;
        }
        LL res = 0;
        for(int i = 2; i <= n; i++)
            for(int j = i + 1; j <= n - 1; j++)
                res += sum1[i][a[j]] * sum2[j][a[i]];
        cout << res << '\n';
    }
}

```

---

## 作者：timmark (赞：3)

# CF1677A 题解
一道树状数组+暴力题。

类似于 [P1637 三元上升子序列](https://www.luogu.com.cn/problem/P1637) 的方法，考虑实现枚举中间的 $b$ 和 $c$，用树状数组实现下标在 $c$ 前面且 $p_a<p_c$ 的 $a$。

至于怎么实现，考虑树状数组用差分实现的区间加法单点查询的方法，设 $f_i$ 代表在 $i$ 前面且比 $i$ 小的数的个数，可以将从 $i+1$ 到 $n$ 的 $f$ 都 $+1$。

但是这样只能在 $i$ 的时候查询有多少个比 $i$ 大的，只能边处理边计算，我们发现可以暴力的把每一个时刻的 $f_i$ 记录下来，设前 $i$ 个数比 $x$ 小的数的个数为 $f_{i,x}$。

同理，对于在 $b$ 后面的 $d$ 可以处理后缀的情况

然后答案即为 $\sum \limits_{i=2}^{n-2} \sum \limits_{j=i+1}^{n-1} (pre_{i-1,p_j}\times post_{j+1,p_i})$，其中 $pre_{i-1}$ 表示 $1$ 到 $i-1$ 的前缀，$post_{j+1}$ 表示 $j+1$ 到 $n$ 的后缀。

code:
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=5005;
int t,n,a[maxn],op,x,y,k,c1[maxn][maxn],c2[maxn][maxn];
long long ans;
int lowbit(int x){return x & (-x);}
void modify1(int idx,int i,int x){for(;i<=n;i+=lowbit(i)) c1[idx][i]+=x;}
int sum1(int idx,int i){
	long long ret=0;
	for(;i;i-=lowbit(i)) ret+=c1[idx][i];
	return ret;
}void modify2(int idx,int i,int x){for(;i<=n;i+=lowbit(i)) c2[idx][i]+=x;}
int sum2(int idx,int i){
	long long ret=0;
	for(;i;i-=lowbit(i)) ret+=c2[idx][i];
	return ret;
}int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> t ;
	while(t--){
		cin >> n ;
		ans=0;
		for(int i=1;i<=n;i++) cin >> a[i] ;
		memset(c1[0],0,sizeof(int)*(n+3));
		memset(c2[n+1],0,sizeof(int)*(n+3));
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++) c1[i][j]=c1[i-1][j];
			modify1(i,a[i]+1,1);
		}for(int i=n;i;i--){
			for(int j=1;j<=n;j++) c2[i][j]=c2[i+1][j];
			modify2(i,a[i]+1,1);
		}for(int i=2;i<n-1;i++) for(int j=i+1;j<n;j++) ans+=sum1(i-1,a[j])*sum2(j+1,a[i]);
		cout << ans << "\n" ;
	}return 0;
}
```

---

## 作者：ttq012 (赞：2)

提供一个线段树做法。

容易发现这个题目可以转化成“枚举两个数 $a$，$b$，求有多少个在区间 $[a, b]$ 里的数 $c$ 满足 $a$ 位置的数小于 $c$ 位置的数的 $c$ 的个数乘求有多少个在区间 $[b, n]$ 里的数 $d$ 满足 $b$ 位置的数小于 $d$ 位置的数的 $d$ 的个数”的值。

时间复杂度为 $\mathcal O(T\cdot n^2\cdot \log^2n)$。

代码略。


---

## 作者：Sellaris (赞：2)

- **题意** ： 逆序对计数变形

- **TIP** ： 模板题

- **前置知识** ： 树状数组

- **思路** ： 对于类逆序对计数，观察到给定排列，于是考虑树状数组维护前缀。对于数组中的数，按照经典 TRICK 按次序插入值域树状数组并维护前缀和，模拟计数符合条件的四元组。然后累加答案即可。

- **代码** ：

```cpp
///*****Sellaris*****///
#include <bits/stdc++.h>
#include <bits/extc++.h>

#define ll long long

using namespace std;
using namespace __gnu_pbds;

const ll maxn=1e5+10;

inline int read(){
    int ret=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
    while(isdigit(ch)){ret=ret*10+ch-'0';ch=getchar();}
    return ret*f; //x=(x<<1)+(x<<3)+(ch^48);
}

ll tre[maxn]={0};

inline ll lowbit(ll x){return x&(-x);}

inline void add(ll k,ll num,ll n){
	for(int i=k;i<=n;i+=lowbit(i)) tre[i]+=num;
}

inline ll query(int k){
	ll ans=0;
	for(int i=k;i>0;i-=lowbit(i)) ans+=tre[i];
	return ans;
}

inline void solve(){
	int n=read();int a[maxn]={0};
	memset(tre,0,sizeof(tre));
	register ll res=0;
	for(int i=1;i<=n;i++) a[i]=read();
	add(a[1],1,n);
	for(ll i=2; i<=n-2; i++){
		ll reg=query(a[i+1]);
		for(ll j=i+2; j<=n; j++){
			if(a[i]>a[j]){
				res+=reg;
			}
			reg+=query(a[j]);
		}
		add(a[i],1,n);
	}
	printf("%lld\n" ,res);
	return ;
}
signed main(){
	int t=read();
	while(t--){solve();}
	return 0;
}

```


---

## 作者：johnsmith0x3f (赞：1)

## 0x00 Outline

给定 $\{ 1, 2, \ldots , n \}$ 的一个排列 $\{ p_n \}$，求四元组 $(a, b, c, d)$ 的个数，满足 $p_a < p_c$ 且 $p_b > p_d$，$1 \le a < b < c < d \le n$.

## 0x01

从四个数里选两个枚举，怎么选？肯定选 $b$ 和 $c$.

此时需要维护 $p_{1 \ldots b-1}$ 中小于 $p_c$ 的数的个数，以及 $p_{c+1 \ldots n}$ 中小于 $p_b$ 的数的个数.

对于前者，维护 $\{ leq_n \}$，其中 $leq_i$ 表示 $p_{1 \ldots b-1}$ 中不大于 $i$ 的数的个数，对于后者，边枚举 $c$ 边修改贡献.

## Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

inline int read(){
	int x = 0, f = 1; char c = getchar();
	while(isdigit(c)^1) f &= (c!=45), c = getchar();
	while(isdigit(c)) x = (x<<1) + (x<<3) + (c^48), c = getchar();
	return f ? x : -x;
}

const int maxn = 5005;
int n, ans, p[maxn], leq[maxn];

signed main(){
#ifndef ONLINE_JUDGE
	freopen("test.in", "r", stdin);
#endif
	for(int t=read(); t; --t){
		n = read(), ans = 0, memset(leq, 0, sizeof(leq));
		for(int i=1; i<=n; ++i) p[i] = read();
		for(int i=1, num=0; i<=n; ++i){
			for(int j=i+1; j<=n; ++j) num += (p[i]>p[j]);
			for(int j=i+1; j<=n; ++j) num -= (p[i]>p[j]), ans += leq[p[j]-1] * num;
			for(int j=p[i]; j<=n; ++j) ++leq[j];
		}
		printf("%lld\n", ans);
	}
	return 0;
}
```

---

## 作者：daitangchen2008 (赞：0)

## 分析  
直接枚举为 $O(n^{4})$ 的，不可接受。我们考虑优化枚举的过程。  
我们枚举 $b$ 和 $c$。我们只需在 $b$ 和 $c$ 确定的情况下找到满足条件的 $a$ 和 $d$ 即可。这个过程就可以用前缀和优化处理。时间复杂度为 $O(n^{2})$。  
## 代码  

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e3+10;
int a[N];
int b[N][N];
int c[N][N];
signed main()
{
	int T;
	cin>>T;
	while(T--)
	{
		int n;
		cin>>n;
		long long ans=0;
		for(int i=1;i<=n;i++)
			cin>>a[i];
		for(int i=0;i<=n+1;i++)
			for(int j=0;j<=n+1;j++)
				b[i][j]=c[i][j]=0;
		for(int i=1;i<=n;i++)
			for(int j=1;j<i;j++)
				if(a[j]<a[i])
					b[j][i]=b[j-1][i]+1;
				else
					b[j][i]=b[j-1][i];
		for(int i=n;i>=1;i--)
			for(int j=n;j>i;j--)
				if(a[j]<a[i])
					c[j][i]=c[j+1][i]+1;
				else
					c[j][i]=c[j+1][i];
		for(int i=1;i<=n;i++)
			for(int j=i+1;j<=n;j++)
				ans+=(long long)b[i-1][j]*(long long)c[j+1][i]; 
		cout<<ans<<endl; 
	}
	return 0;
}
```

---

## 作者：Fubaogege (赞：0)

给定一个长度为 $n$ 的序列，问一共有多少个四元组 $a,b,c,d$，我们只需要满足 $a<b<c<d$ 且 $p_a<p_c,p_b>p_d$ 就行。

这道题可以运用枚举法，直接枚举 $b,c$，且让 $a<b,p_a<p_c$，利用前缀和即可求出。

对于数 $d$ 同样用以上方法，最终就可以得出答案四元组的数量了。

---

## 作者：zhengzidu (赞：0)

#  CF1677A Tokitsukaze and Strange Inequality 题解
## 树状数组的原理介绍（知道的大佬请跳过）

[BLOG](https://www.luogu.com.cn/article/b75mv46d)

## Solution

接下来讲讲上述与本题的关系。

可以先看这题 [P1637 三元上升子序列
](https://www.luogu.com.cn/problem/P1637)。

与那题相同的，作为一个四元序列，我们很容易想到枚举中间的元素。

对于类逆序对计数，观察到给定排列，于是考虑树状数组维护前缀与后缀。对于数组中的数，按次序插入值域树状数组并维护。

在 $b,c$ 固定的情况下，统计答案：$b$ 左边小于 $p_c$ 的数乘上 $c$ 右边小于 $p_b$ 的数（简单计数原理）。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
	x=x*10+ch-'0';
	ch=getchar();
}
	return x*f;
}
void write(int x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
		write(x/10);
	putchar(x%10+'0');
	return;
}
int n;
int tree[100001];
int a[100001];
int cnt;
int lowbit(int x){
	return x&(-x);
}
void update(int x,int d){
	while(x<=n){
		tree[x]+=d;
		x+=lowbit(x);
	}
}
int query(int x){
	int res=0;
	while(x){
		res+=tree[x];
		x-=lowbit(x);
	}
	return res;
}
signed main(){
	int t=read();
	while(t--){
		n=read();
		memset(tree,0,sizeof(tree));
		cnt=0;
		for(int i=1;i<=n;i++) a[i]=read();
		update(a[1],1);
		for(long long i=2;i<=n-2;i++){
			long long tree_array=query(a[i+1]);
			for(long long j=i+2;j<=n;j++){
				if(a[i]>a[j]){
					cnt+=tree_array;
				}
				tree_array+=query(a[j]);
			}
			update(a[i],1);
		}
		write(cnt);
		printf("\n");
	}
	return 0;
}
```

---

## 作者：intel_core (赞：0)

$n\le 5000$，明显是 $O(n^2)$ 的做法。

一个四元组 $(a,b,c,d)$，现在要枚举两个值快速确定剩下两个的数量。

一种显而易见的做法是枚举 $b,c$，现在对 $a$ 的要求就是 $a<b,p_a<p_c$，用一下前缀和就可以求出个数；对于 $d$ 同理，最后乘法原理求出给定 $(b,c)$ 时四元组的数量。

复杂度 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NR=5e3+10;
#define int long long
int n,a[NR],f[NR][NR];

void solve(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		for(int j=1;j<=a[i];j++)f[i][j]=f[i-1][j]+1;
		for(int j=a[i]+1;j<=n;j++)f[i][j]=f[i-1][j];
	}
	int ans=0;
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			ans+=(i-1-f[i-1][a[j]])*(n-j-(f[n][a[i]]-f[j][a[i]]));
	cout<<ans<<endl;
}

signed main(){
	int T;cin>>T;
	while(T--)solve();
	return 0;	
}
```

---

## 作者：yanhao40340 (赞：0)

### 题意
给定一个 $1$ 到 $n$ 的排列 $p$，求有多少个四元组 $(a,b,c,d)$ 满足 $a<b<c<d \land p_a<p_c \land p_b>p_d$。
### 分析
枚举四个肯定超时。题目要求 $n \leq 5000$，说明我们只可以枚举 $2$ 个。

显然，枚举 $b$ 和 $c$ 是最好的选择。因为这样可以最方便的确定 $a$ 和 $d$ 的选择方法的数量，而枚举其他的字母都无法达到此效果。

维护二维数组。$f_{i,j}$ 表示在前 $i$ 个数有多少个小于 $j$ 的数。暴力预处理计算 $f$ 即可。

那么当 $b$ 和 $c$ 确定后，$a$ 的可选数目就为 $f_{b-1,C}$。

同理 $d$ 的可选数目是 $B-1-f_{c,B}$。

其中大写字母 $B$ 表示 $p_b$，$C$同理。（主要是双重下标会看不清楚）

根据乘法原理，$b$ 和 $c$ 在确定位置时对答案的贡献是
$$f_{b-1,C} \times (B-1-f_{c,B})$$
，统计即可。

该算法的时间复杂度和空间复杂度均是 $O(n^2)$ 的，可以通过。

最后一定要注意，四元组的个数是 $n^4$ 级别的，不开 $\texttt{long long}$ 泪千行啊！
### 代码
代码中用 $a$ 数组代替了排列 $p$，将就着看吧。
```cpp
#include <iostream>
using namespace std;
typedef long long ll;
const int maxn=5002;
int a[maxn],f[maxn][maxn];
int main(){
	int t,n;scanf("%d",&t);
	while (t--){
		scanf("%d",&n);
		for (int i=1;i<=n;++i) scanf("%d",&a[i]);
		for (int i=1;i<=n;++i){
			for (int j=1;j<=n;++j) f[i][j]=f[i-1][j];
			for (int j=n;j>a[i];--j) ++f[i][j];
		}
		ll ans=0;
		for (int b=1;b<=n;++b)
			for (int c=b+1;c<=n;++c)
				ans+=1ll*f[b-1][a[c]]*(a[b]-1-f[c][a[b]]);
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

