# [USACO22JAN] Counting Haybales P

## 题目描述

如同往常一样，奶牛 Bessie 正在 Farmer John 的牛棚里制造麻烦。FJ 有 $N$（$1 \le N \le 5000$）堆草堆。对于每个 $i \in [1,N]$，第 $i$ 堆草堆有 $h_i$（$1 \le h_i \le 10^9$）的草。Bessie 不想让任何的草倒下来，所以她唯一可以执行的操作为：

如果两个相邻的草堆的高度相差恰好为 $1$，她可以将较高的草堆中最上方的草移到较低的草堆之上。

执行有限多次上述操作后，可以得到多少种不同的高度序列，对 $10^9+7$ 取模？两个高度序列被认为是相同的，如果对于所有 $i$，第 $i$ 堆草堆在两者中具有相同数量的草。

## 说明/提示

【样例解释】

对于第一个子测试用例，四个可能的高度序列为：

$(2,2,2,3),(2,2,3,2),(2,3,2,2),(3,2,2,2)$

对于第二个子测试用例，四个可能的高度序列为：

$(2,3,3,1),(3,2,3,1),(3,3,2,1),(3,3,1,2)$

【数据范围】

- 测试点 1-3 满足 $N \le 10$。
- 测试点 4 满足对于所有 $i$，有 $1 \le h_i \le 3$。
- 测试点 5-7 满足对于所有 $i$，有 $|h_i-i| \le 1$。
- 测试点 8-10 满足对于所有 $i$，有 $1 \le h_i \le 4$，且 $N \le 100$。
- 测试点 11-13 满足 $N \le 100$。
- 测试点 14-17 满足 $N \le 1000$。
- 测试点 18-21 没有额外限制。

供题：Daniel Zhang

## 样例 #1

### 输入

```
7
4
2 2 2 3
4
3 3 1 2
4
5 3 4 2
6
3 3 1 1 2 2
6
1 3 3 4 1 2
6
4 1 2 3 5 4
10
1 5 6 6 6 4 2 3 2 5```

### 输出

```
4
4
5
15
9
8
19```

# 题解

## 作者：Sol1 (赞：8)

纪念一下 usaco Pt 首次过两个题，C 完全没往凸包上想（

首先这个操作就是 swap 一对差为 1 的。

手玩一下容易发现如果两个元素差 $\geq 2$ 那么无论如何操作都不能交换它们的相对位置，相同的元素也可以假定不能交换。

那么只需要把不能 swap 的元素都从前往后连上边，就变成了一个 DAG 拓扑序计数问题。

但是一般的 DAG 拓扑序计数是不能做的，需要挖掘图的性质。差恰好为 $1$ 和 $n=5\times 10^3$ 提示奇偶性，发现奇数的拓扑序唯一，偶数一样，所以这个图实际上是两条拓扑序定死的链之间互相连边。

现在就可以 DP 了，设 $f_{i,j}$ 为第一条链选了前 $i$ 个点，第二条链选了前 $j$ 个点，转移的时候看第一条链上的第 $i+1$ 个点的入边是否全都在第一条链以及第二条链的前 $j$ 个点里面，如果是的话转移到 $f_{i+1,j}$；另一条链的扩展同理。

于是做完了，时空复杂度 $O(n^2)$。

```cpp
#include <bits/stdc++.h>
using namespace std;

const long long mod = 1000000007;
long long dp[5005][5005];
int n, a[5005], pre[5005], pos[5005], idx[2][5005];

inline void Read() {
	cin >> n;
	for (int i = 1;i <= n;i++) cin >> a[i];
}

inline void Solve() {
	int cnt[2] = {0};
	memset(pre, 0, sizeof(pre));
	memset(pos, 0, sizeof(pos));
	memset(idx, 0, sizeof(idx));
	for (int i = 1;i <= n;i++) {
		pos[i] = ++cnt[a[i] & 1];
		idx[a[i] & 1][cnt[a[i] & 1]] = i;
		for (int j = i;j >= 1;j--) {
			if (((a[i] ^ a[j]) & 1) && abs(a[i] - a[j]) != 1) {
				pre[i] = j;
				break;
			}
		}
	}
	for (int i = 0;i <= cnt[0];i++) {
		for (int j = 0;j <= cnt[1];j++) dp[i][j] = 0;
	}
	dp[0][0] = 1;
	for (int i = 0;i <= cnt[0];i++) {
		for (int j = 0;j <= cnt[1];j++) {
			if (pre[idx[0][i + 1]] <= idx[1][j]) dp[i + 1][j] = (dp[i + 1][j] + dp[i][j]) % mod;
			if (pre[idx[1][j + 1]] <= idx[0][i]) dp[i][j + 1] = (dp[i][j + 1] + dp[i][j]) % mod;
		}
	}
	cout << dp[cnt[0]][cnt[1]] << endl;
}

int main() {
	int t; cin >> t;
	while (t--) {
		Read();
		Solve();
	}
	return 0;
}

```

---

## 作者：UltiMadow (赞：3)

挺有意思的一个计数（

题面里面移动干草块其实就是对于相邻的两个数，如果差的绝对值等于 1，则可以交换（为了方便假设相同的数不能交换）

注意到序列中所有的奇数的相对位置都不会改变，所有的偶数相对位置也不会改变（奇偶性相同的数差要么大于 1，要么为零）

于是就可以用一个 dp 解决了

设 $f_{i,j}$ 表示选了前 $i$ 个奇数，选了前 $j$ 个偶数的方案数

用奇数转移的时候只要验证一段区间内的偶数的最大值和最小是是不是和当前奇数差 1 即可，偶数同理，可以用 st 表维护

时间复杂度 $\mathcal O(n^2)$

code:
```cpp
#include<bits/stdc++.h>
#define MAXN 5010
#define p 1000000007
using namespace std;
int T,n,a[MAXN],lg[MAXN];
int f[MAXN][MAXN];
int ev[MAXN],ce,od[MAXN],co;
int pe[MAXN],po[MAXN];
struct min_ST_Table{
	int st[MAXN][15];
	min_ST_Table(){memset(st,0x3f,sizeof(st));}
	void clear(){memset(st,0x3f,sizeof(st));}
	void build(int *x,int len){
		for(int i=1;i<=len;i++)st[i][0]=x[i];
		for(int k=1;k<=13;k++)
			for(int i=1;i<=len;i++)
				st[i][k]=min(st[i][k-1],st[i+(1<<(k-1))][k-1]);
	}
	int query(int l,int r){
		int len=r-l+1,bit=lg[len];
		return min(st[l][bit],st[r-(1<<bit)+1][bit]);
	}
}mne,mno;
struct max_ST_Table{
	int st[MAXN][15];
	max_ST_Table(){memset(st,0,sizeof(st));}
	void clear(){memset(st,0,sizeof(st));}
	void build(int *x,int len){
		for(int i=1;i<=len;i++)st[i][0]=x[i];
		for(int k=1;k<=13;k++)
			for(int i=1;i<=len;i++)
				st[i][k]=max(st[i][k-1],st[i+(1<<(k-1))][k-1]);
	}
	int query(int l,int r){
		int len=r-l+1,bit=lg[len];
		return max(st[l][bit],st[r-(1<<bit)+1][bit]);
	}
}mxe,mxo;
int main(){
	scanf("%d",&T);
	for(int i=2;i<=5005;i++)lg[i]=lg[i>>1]+1;
	while(T--){
		scanf("%d",&n);co=ce=0;
		memset(pe,0,sizeof(pe));memset(po,0,sizeof(po));
		mne.clear();mno.clear();mxe.clear();mxo.clear();
		int pree=0,preo=0;
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			if(a[i]&1)po[++co]=pree,od[co]=a[i],preo=co;
			else pe[++ce]=preo,ev[ce]=a[i],pree=ce;
		}
		mne.build(ev,ce);mxe.build(ev,ce);
		mno.build(od,co);mxo.build(od,co);
		memset(f,0,sizeof(f));f[0][0]=1;
		for(int i=0;i<=ce;i++)
			for(int j=0;j<=co;j++){
				if(i<ce){
					int pre=pe[i+1],num=ev[i+1];
					if(j>=pre||(mno.query(j+1,pre)>=num-1&&mxo.query(j+1,pre)<=num+1))
						f[i+1][j]=(f[i+1][j]+f[i][j])%p;
				}if(j<co){
					int pre=po[j+1],num=od[j+1];
					if(i>=pre||(mne.query(i+1,pre)>=num-1&&mxe.query(i+1,pre)<=num+1))
						f[i][j+1]=(f[i][j+1]+f[i][j])%p;
				}
			}
		printf("%d\n",f[ce][co]);
	}
	return 0;
}
```

（考场代码写的很丑/kk）

---

## 作者：ETHANK (赞：3)

题意：给一个长度为 $N$ 的数组 $a$ ，相邻两项若差不大于 $1$ 则可以交换，问能得到的不同 $a$ 个数，答案模 $10^9+7$ 。

数据范围：$1\le N\le 5000,1\le a_i\le10^9$ 

计数问题基本就是 dp 了。发现从上一题中的不大于 $K$ 变成了不大于 $1$ ，必然有猫腻。由于差大于 $1$ 的数很多，所以大部分数之间是不能够对换位置的，考虑从这一点入手解决问题。

然后此时如果观察到了奇数之间不可能调换位置（除非两数相同，但是这样的调换没有意义），偶数也同理。于是设计 dp 状态为 $dp[i][j]$ 表示当前确定了前 $i+j$ 个位置，有 $i$ 个奇数，$j$ 个偶数。对每个数，预处理它最远能与它不同奇偶性的哪个数交换即可。转移是简单的。

时间复杂度：$O(N^2)$ 。

```cpp
#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
#define pii pair<int,int>
#define vi vector<int>
#define fi first
#define se second
#define pb push_back
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define ALL(x) x.begin(),x.end()
#define sz(x) int(x.size())
#define ll long long
using namespace std;
inline ll read(){
    ll x=0,f=1;char ch=getchar();
    while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
    while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
    return x*f;
}
const int N=5e3+5,P = 1e9+7;
int n,a[N],pos[N];
void add(int &x,const int y){x += y;if(x > P)x -= P;}
void sub(int &x,const int y){x -= y;if(x < 0)x += P;}
void solve(){
    n = read();
    vector <int> even,odd;
    rep(i,1,n){
        a[i] = read();
        if(a[i] & 1){
            pos[i] = sz(odd);
            odd.pb(i);
        }else{
            pos[i] = sz(even);
            even.pb(i);
        }
    }
    vector <int> pre(n+1);
    rep(i,1,n){
        if(a[i] & 1)pre[i] = sz(even);
        else pre[i] = sz(odd);
        rep(j,i+1,n)if(((a[i] - a[j]) & 1) && abs(a[i] - a[j]) > 1){
            pre[i] = min(pre[i],pos[j]);
        }
    }
    vector <vi> dp(sz(even) + 1,vi(sz(odd) + 1));
    dp[0][0] = 1;
    rep(i,0,sz(even))rep(j,0,sz(odd)){
        if(!dp[i][j])continue;
        if(i < sz(even) && j <= pre[even[i]])
            add(dp[i+1][j],dp[i][j]);
        if(j < sz(odd) && i <= pre[odd[j]])
            add(dp[i][j+1],dp[i][j]);
    }
    cout << dp[sz(even)][sz(odd)] << '\n';
}
int main(){
    int T = read();
    while(T--)solve();
    return 0;
}
``` 

---

## 作者：封禁用户 (赞：2)

### 题面

### 思路
发现交换 $i,j$ 的条件是 $|i-j|=1,|a_i-a_j|=1$，稍稍想一下就知道，只要 $i+1$ 到 $j$ 的与 $i$ 奇偶性不同的数都可以和 $i$ 换，则 $j$ 可以和 $i$ 换。发现交换的两个数奇偶性不同，对于奇数、偶数分别的排列顺序没改变。

考虑 dp。

记录 $f_{i,j}$ 表示选了 $i$ 个奇数、$j$ 个偶数的合法种数。转移思路很简单，就是一个数 $i$ 可以贡献到他最前面到最后面能换的不同奇偶性的数，因为前面的数肯定要贡献到他上面，就只用管后面的，用 $O(n^2)$ 预处理就行了。

### 代码
```cpp
#include<bits/stdc++.h>
#define mod 1000000007 
#define int long long 
#define Maxn 5005 
using namespace std;
int a[Maxn],id[Maxn],suf[Maxn],f[Maxn][Maxn];
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t,n; cin>>t;
    while(t--) {
        cin>>n;
        memset(f,0,sizeof(f));
        vector<int> p,q,z;
        for(int i=1;i<=n;i++) {
            cin>>a[i];
            if(a[i] & 1)id[i] = q.size(),q.push_back(i);
            else id[i] = p.size(),p.push_back(i);
        }
        for(int i=1;i<=n;i++) {
            if(a[i] & 1)suf[i] = p.size();
            else suf[i] = q.size();
            for(int j=i+1;j<=n;j++)
            if((a[i] & 1) != (a[j] & 1)&&abs(a[i]-a[j]) > 1) {
                suf[i] = min(suf[i],id[j]); break;
            }
        } f[0][0] = 1;
        for(int i=0;i<=q.size();i++)
            for(int j=0;j<=p.size();j++) {
                if(i < q.size()&&j <= suf[q[i]])
                    f[i+1][j] = (f[i+1][j]+f[i][j])%mod;
                if(j < p.size()&&i <= suf[p[j]])
                    f[i][j+1] = (f[i][j+1]+f[i][j])%mod;
            } cout<<f[q.size()][p.size()]<<"\n";
    }
    return 0;
}
```

---

## 作者：Colinxu2020 (赞：1)

感觉洛谷题解都好意识流啊，交一个详细一些的题解。

首先把题目里面的一个 $+1$ 一个 $-1$ 变成选两个差为 $1$ 的相邻数，之后把他们交换。

观察：任意两个不同的奇偶性相同的数的相对位置关系不变。

证明：考虑两个数什么时候相对位置关系会发生变化，当且仅当这两个数发生了交换，而因为数值不同且奇偶性相同，所以至少差 $2$，一定无法交换。

考虑最终序列的值，由上面的结论可知必然是由原数列的前若干个奇数和若干个偶数混合而成，而我们能否加一个数只和已经加的数有关，设 $dp_{i,j}$ 为最终序列的前 $i+j$ 项，由原数列的前 $i$ 个奇数和前 $j$ 个偶数构成的方案数，显然初始值为 $dp_{0,0}=1$，答案为 $dp_{x,y}$，其中 $x,y$ 分别为奇数数量和偶数数量。

设所有偶数所在的下标构成的序列为 $even$，所有奇数所在的下标构成的序列为 $odd$。

什么时候可以往后面加一个奇数比较复杂，考虑什么时候不能加，当且仅当有一个差较大的偶数挡在了这个奇数和上一个奇数之间，即 $\exists x,odd_{i-1} \lt even_x \lt odd_i,\lvert height_{odd_i}-height_{even_x}\rvert \gt 1$，因为这时候凑不到一起。偶数同理。

考虑怎么优化这个东西，发现式子里大部分东西都只和 $odd_{i}$ 相关，因此设 $f_{0/1,i}$ 为偶数/奇数中，所有下标 $\lt even_i/odd_i$ 的中满足不可交换的最大的下标，在奇数/偶数序列中的位置，转移条件可以变成 $i \geq f_{0,j}$ 或 $j \geq f_{1,i}$ 的时候才可以从 $dp_{i,j-1}/dp_{i-1,j}$ 转移，也就是说这个挡路的必须被包含进去了。

这样可以做到 $\Theta(n^2)$，USACO 上说可以做到 $\Theta(n \log n)$，但还是太神秘了。

参考代码：

```cpp
#include<iostream>
#include<vector>
using namespace std;

const int maxn=5000+10,mod=1e9+7;
int n,dp[maxn][maxn],ai[maxn],pos[maxn],post[2][maxn];
vector<int> odd,even;

int main(){
    int T; cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>ai[i];
            if(ai[i]%2)odd.push_back(ai[i]),pos[i]=odd.size();
            else even.push_back(ai[i]),pos[i]=even.size();
        }
        for(int i=1;i<=n;i++)post[0][i]=post[1][i]=0;
        for(int i=1;i<=n;i++)for(int j=i+1;j<=n;j++)if(ai[i]%2!=ai[j]%2&&abs(ai[i]-ai[j])>1){
            post[ai[j]%2][pos[j]]=max(post[ai[j]%2][pos[j]],pos[i]);
        }
        for(int i=0;i<=odd.size();i++)for(int j=0;j<=even.size();j++){
            dp[i][j]=(!i&&!j);
            if(i>0&&post[1][i]<=j)dp[i][j]=(dp[i][j]+dp[i-1][j])%mod;
            if(j>0&&post[0][j]<=i)dp[i][j]=(dp[i][j]+dp[i][j-1])%mod;
        }
        cout<<dp[odd.size()][even.size()]<<endl;
        even.clear(); odd.clear();
    }
}
```

---

## 作者：AxDea (赞：1)

考虑暴力做法，每次设一个状态你都必须要知道上一个状态中序列与它不能交换的最后面的节点的位置是什么，无论怎么搞都只有 $\mathcal O (n ^ 3)$。

然后找性质，按照第一题的想法，把所有必须满足当前前后关系的二元组连边，发现，高度为奇数和偶数的就互相连边了，这就完成了一个 **分类** 操作。

那么如果知道前面状态中最后面的和它同奇偶的点的位置，再处理出最后面与他不同奇偶的点但不满足交换条件的位置，就可以转移了。

对于不同奇偶点的位置，可以通过暴力求出。

现在又有一个很好的发现，因为分成了互不相交的两类，所以最后一个位置必然是一个奇数或偶数。

所以就可以很开心的设 $dp_{i, j}$ 表示最后一个奇数的位置为 $i$，最后的一个偶数的位置为 $j$ 的方案数，这样 $\sum dp_{i, n} + dp_{n, i}$ 就是答案。

转移分类讨论一下当前位置的奇偶和上一个状态最后一个位置的奇偶就行了，最后上一个前缀和就可以做到 $\mathcal O (N ^ 2)$ 了。

```cpp
#include <bits/stdc++.h>
#define forn(i,s,t) for(int i = (s); i <= (t); ++i)
#define form(i,s,t) for(int i = (s); i >= (t); --i)
#define rep(i,s,t) for(int i = (s); i < (t); ++i)
using namespace std;
inline void solve() {
    cin >> n;
    forn(i, 1, n) cin >> h[i];
    rep(i, 1, n) {
        num[h[i] & 1] ++ ;
        forn(j, i + 1, n) if (h[j] != h[i] + 1 && h[j] != h[i] - 1)
            pre[h[i] & 1][j] = num[h[i] & 1];
    }
    //  forn (i, 1, n) cout << pre[0][i] << " \n"[i == n];
    //  forn (i, 1, n) cout << pre[1][i] << " \n"[i == n];
    dp[0][0] = Mint(1);
    num[0] = num[1] = 0;
    forn(i, 1, n) {
        num[h[i] & 1] ++ ;
        row[0] = dp[i - 1][0];
        rep(j, 1, i) row[j] = row[j - 1] + dp[i - 1][j];
        cal[0] = dp[0][i - 1];
        rep(j, 1, i) cal[j] = cal[j - 1] + dp[j][i - 1];

        if (h[i] & 1) { // front
            rep(j, 0, i) dp[i][j] += dp[i - 1][j];
            int lim = max(0, i - (num[0] - pre[0][i]) - 1);

            if (!pre[0][i])
                lim = 0;

            rep(j, lim + 1, i) {
                // dp[j][i]
                dp[j][i] += cal[j - 1];
                //              rep (k, 0, j) dp[j][i] += dp[k][i - 1];
            }
            rep(k, 0, i - 1) dp[i][i - 1] += dp[k][i - 1];
        } else { // back
            rep(j, 0, i) dp[j][i] += dp[j][i - 1];
            int lim = max(0, i - (num[1] - pre[1][i]) - 1);

            if (!pre[1][i])
                lim = 0;

            rep(j, lim + 1, i) {
                // dp[i][j]
                dp[i][j] += row[j - 1];
                //              rep (k, 0, j) dp[i][j] += dp[i - 1][k];
            }
            rep(k, 0, i - 1) dp[i - 1][i] += dp[i - 1][k];
        }
    }
    //  forn (i, 0, n) forn (j, 0, n) cout << dp[i][j].res << " \n"[j == n];
    Mint res(0);
    forn(i, 0, n) res += dp[n][i] + dp[i][n];
    cout << res.res << '\n';
}
```


---

## 作者：Purslane (赞：0)

# Solution

显然限制为：两个数 $i$ 和 $j$ 满足 $i < j$ 且 $|p_i - p_j| \neq 1$，则这两个数在最终序列中的顺序 $i'$ 和 $j'$ 应当满足 $i'<j'$。实际上我们在求一个 DAG 的拓扑序数。

发现我们只需要保证对于每个数 $i$，满足 $j < i$ 且 $p_j \le p_i$ 且 $p_j \neq p_i - 1$ 的 $j$ 的个数在变换前后不变即可。（这个相当于给拓扑序一个更加容易判断的形式。）

注意到对于所有的奇数，两两之间必然有连边，所以奇数的顺序实际上是确定的，对于偶数也是如此。

所以你把两条链归并一下就行了，随便 DP。复杂度 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=5000+10,MOD=1e9+7;
int T,n,h[MAXN],pre[MAXN][MAXN],dp[MAXN][MAXN],ori[MAXN],scnt[MAXN];
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--) {
		cin>>n;
		ffor(i,1,n) cin>>h[i],ori[i]=0,scnt[i]=-1;
		ffor(i,0,n) ffor(j,0,n) pre[i][j]=dp[i][j]=0;
		dp[0][0]=1;
		ffor(i,1,n) ffor(j,1,i-1) if(h[j]<=h[i]&&h[j]!=h[i]-1) ori[i]++;	
		vector<int> jid,oid;
		jid.push_back(0),oid.push_back(0);
		ffor(i,1,n) {
			if(h[i]%2==0) {
				for(auto p:oid) if(h[p]<=h[i]) scnt[i]++;
				oid.push_back(i);	
			}
			else {
				for(auto p:jid) if(h[p]<=h[i]) scnt[i]++;
				jid.push_back(i);	
			}
		}
		ffor(i,1,n) {
			if(h[i]%2==1) ffor(j,1,oid.size()-1) pre[i][j]=pre[i][j-1]+(h[oid[j]]<h[i]-1);
			else ffor(j,1,jid.size()-1) pre[i][j]=pre[i][j-1]+(h[jid[j]]<h[i]-1);
		}
		ffor(i,0,oid.size()-1) ffor(j,0,jid.size()-1) {
			if(i&&pre[oid[i]][j]+scnt[oid[i]]==ori[oid[i]]) dp[i][j]=dp[i-1][j];
			if(j&&pre[jid[j]][i]+scnt[jid[j]]==ori[jid[j]]) dp[i][j]=(dp[i][j]+dp[i][j-1])%MOD;
		}
		cout<<dp[oid.size()-1][jid.size()-1]<<'\n';
	}
	return 0;
}
```

---

## 作者：Anonymely (赞：0)

操作可以看为只能交换两个绝对值相差 $1$ 的数，对于不能交换的数从前向后连边，变为了拓扑序计数。

但是一般 DAG 拓扑序计数没法做，发现这个图性质：奇偶性相同的数一定连边，也就是这个图是两条链然后相互连边。

那就直接 $f_{i,j}$ 表示选完了第一条链前 $i$ 个和第二条链前 $j$ 个，转移 $i+1$ 要满足它的所有入边都在 $j$ 之前，预处理下即可做到 $O(n^2)$。

[submission](https://www.luogu.com.cn/record/176616558)

---

