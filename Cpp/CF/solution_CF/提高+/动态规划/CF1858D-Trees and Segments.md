# Trees and Segments

## 题目描述

# 树木与区间


夏季信息学学校的教师们决定在一排中种植 $ n $ 棵树，而且决定只种植橡树和冷杉树。为此，他们制定了一个计划，可以用长度为 $ n $ 的二进制字符串 $ s $ 表示。如果 $ s_i = 0 $，则第 $ i $ 棵树应该是橡树，如果 $ s_i = 1 $，则第 $ i $ 棵树应该是冷杉树。

树木种植的日子就是明天，后天一个督察将来到学校。督察非常喜欢大自然，他将根据以下方式评估这一排树的美丽程度：

- 首先，他将计算 $ l_0 $，作为该计划 $ s $ 中连续的橡树的最大数目（计划 $ s $ 中由零构成的最大子串）。如果树行中没有橡树，则 $ l_0 = 0 $。
- 然后，他将计算 $ l_1 $，作为该计划 $ s $ 中连续的冷杉树的最大数目（计划 $ s $ 中由一构成的最大子串）。如果树行中没有冷杉树，则 $ l_1 = 0 $。
- 最后，他将计算树行的美丽程度为 $ a \cdot l_0 + l_1 $，其中 $ a $ 是督察最喜欢的数。

教师们知道参数 $ a $ 的值，但出于安全原因，他们不能告诉你。他们只告诉你 $ a $ 是从 $ 1 $ 到 $ n $ 的整数。

由于树木尚未种植，教师们决定在不超过 $ k $ 棵树上更改树的类型（即在计划中从 $ 0 $ 更改为 $ 1 $ 或从 $ 1 $ 更改为 $ 0 $），以便根据督察的计算来最大化树行的美丽程度。

对于从 $ 1 $ 到 $ n $ 的每个整数 $ j $ 独立回答以下问题：

- 如果督察最喜欢的数为 $ j $，则在不超过 $ k $ 次更改的情况下，教师们可以通过更改树的类型来实现树行的最大美丽程度是多少？

## 说明/提示

在第一个测试用例中，不允许进行任何更改，因此始终满足 $ l_0 = 0 $ 和 $ l_1 = 3 $。因此，不管 $ a $ 的值如何，树行的美丽程度都将是 $ 3 $。

在第二个测试用例中，对于 $ a \in \{1, 2\} $，教师们可以将计划 $ s $ 更改为 $ 0111 $（通过更改 $ s_4 $），对于 $ a \in \{3, 4\} $，他们可以将计划 $ s $ 更改为 $ 0010 $（通过更改 $ s_2 $）。在这种情况下，每个 $ a $ 的树行的美丽程度计算如下：

- 对于 $ a = 1 $：$ l_0 = 1 $，$ l_1 = 3 $。树行的美丽程度为 $ 1\cdot 1 + 3 = 4 $。
- 对于 $ a = 2 $：$ l_0 = 1 $，$ l_1 = 3 $。树行的美丽程度为 $ 2\cdot 1 + 3 = 5 $。
- 对于 $ a = 3 $：$ l_0 = 2 $，$ l_1 = 1 $。树行的美丽程度为 $ 3\cdot 2 + 1 = 7 $。
- 对于 $ a = 4 $：$ l_0 = 2 $，$ l_1 = 1 $。树行的美丽程度为 $ 4\cdot 2 + 1 = 9 $。

可以证明，上述更改对于所有 $ a $ 从 $ 1 $ 到 $ 4 $ 都是最优的。

## 样例 #1

### 输入

```
5
3 0
111
4 1
0110
5 0
10000
6 2
101101
7 1
0001101```

### 输出

```
3 3 3 
4 5 7 9 
5 9 13 17 21 
6 9 13 17 21 25 
7 10 13 17 21 25 29```

# 题解

## 作者：苏联小渣 (赞：13)

为什么这个题能有 *2200 啊。。。

题目大意就是 $01$ 序列翻转不超过 $k$ 个，使得最长 $0$ 的连续段长度 $\times a$ 加上最长 $1$ 的连续段长度最大。

考虑枚举最长 $0$ 的连续段，记作 $[l,r]$，那么此时我们用的翻转次数就是 $[l,r]$ 中 $1$ 的个数，剩余的翻转次数记作 $k'$。那么此时我们需要在 $[1,l-1]$ 或 $[r+1,n]$ 中选一个区间 $[l',r']$，使得 $[l',r']$ 中 $0$ 的个数 $\le k'$ 且 $r'-l'+1$ 最大。

记录 $f_{i,j}$ 表示以 $i$ 为起点的一段子串，满足 $0$ 的个数 $\le j$ 的最大长度。对于同一个 $i$，很显然 $f_{i,j}$ 是满足单调性的，可以双指针求出。这部分复杂度 $O(n^2)$。

同理，记录 $g_{i,j}$ 表示以 $i$ 为结尾的一段子串，满足 $0$ 的个数 $\le j$ 的最大长度，用同样的方法可以 $O(n^2)$ 求出。

那么当我们枚举了 $[l,r]$ 作为 $0$ 的连续段，这个 $[l',r']$ 的最大长度就是：

$$\max\{\max_{i=r+1}^n f_{i,k'},\max_{i=1}^{l-1} g_{i,k'}\}$$

我们对相同 $j$ 的 $f_{i,j},g_{i,j}$ 分别统计一个后缀 $\max$，前缀 $\max$ 即可。

那么，此时我们就处理出了对于一个区间 $[l,r]$ 作为 $0$ 的连续段，最长的 $1$ 的连续段的长度。此时我们可以处理出 $ans_{i}$ 表示当 $0$ 的连续段长度为 $i$ 时，最长的 $1$ 的连续段的长度，那么对于一个询问 $a$，其答案就是 $\max\{a \cdot i+ans_i\}$。

需要注意的细节：

- 处理出 $ans_0$；

- 判断 $ans_i$ 是否可以取到，若无法取到要直接跳过；

- 多测清空。

时间复杂度 $O(n^2)$。

### Code：

赛时用乱搞的号写的，代码会比较丑。

```c++
#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n, k, a[3010], pre[3010][3010], suf[3010][3010], ans[3010], vis[3010];
char ch[3010];
signed main(){
	scanf ("%lld", &t);
	while (t --){
		scanf ("%lld%lld%s", &n, &k, ch+1);
		for (int i=1; i<=n; i++){
			a[i] = ch[i] - '0';
			ans[i] = vis[i] = 0;
		}
		a[n+1] = 0;
		for (int i=0; i<=k; i++) suf[n+1][i] = 0;
		for (int i=1; i<=n; i++){
			int now = 0, x = i-1;
			for (int j=0; j<=k; j++){//找i右边第j+1个0的位置，没有就是n+1
				while (now < j+1 && x <= n){
					x ++;
					if (a[x] == 0) now ++;
				}
				suf[i][j] = x - i;
			}
		}
		for (int i=n; i>=1; i--){
			for (int j=0; j<=k; j++){
				suf[i][j] = max(suf[i][j], suf[i+1][j]);
			}
		}
		for (int i=n; i>=1; i--){
			int now = 0, x = i+1;
			for (int j=0; j<=k; j++){
				while (now < j+1 && x >= 1){
					x --;
					if (a[x] == 0) now ++;
				}
				pre[i][j] = i - x;
			}
		}
		for (int i=1; i<=n; i++){
			for (int j=0; j<=k; j++){
				pre[i][j] = max(pre[i][j], pre[i-1][j]);
			}
		}
		vis[0] = 1;
		ans[0] = max(pre[n][k], suf[1][k]);
		for (int i=1; i<=n; i++){
			int tot = 0;
			for (int j=i; j<=n; j++){
				if (a[j] == 1) tot ++;
				if (tot > k) break;
				ans[j-i+1] = max(ans[j-i+1], suf[j+1][k-tot]);
				ans[j-i+1] = max(ans[j-i+1], pre[i-1][k-tot]);
				vis[j-i+1] = 1;
			}
		}
		for (int i=1; i<=n; i++){
			int now = 0;
			for (int j=0; j<=n; j++){
				if (!vis[j]) continue;
				now = max(now, i*j + ans[j]);
			}
			printf ("%lld ", now);
		}
		puts ("");
	}
	return 0;
}
```

---

## 作者：Hisaishi_Kanade (赞：10)

场上没做出来，比较好笑。

$n\le 3000$，所以大概是 $n^2$ 量级的。

对于 $a\times l_0+l_1$ 这个式子，我们不如钦定 $l_0$，然后算此时的 $l_0$ 能取得的最大 $l_1$ 是多少。

那么我们枚举区间的左端点 $l$，则 $r$ 可以确定为 $l+l_0-1$ 了。接下来需要求解的是 $[1,l)$ 或者 $(r,n]$ 这两个区间能做到最大的 $l_1$ 是多少。

我们不妨设 $pre_{i,j}$ 表示前 $i$ 个数 $j$ 次操作能能做到最大的 $l_1$ 是多少，同理设 $suf_{i,j}$。我们转移 $pre_i$ 时，从 $i$ 开始往前扫，因为一个区间变成 $1$ 的代价是 $0$ 的个数，那么转移就变得简单了。

我们在扫的过程中记录目前 $0$ 的个数，则可以用这 $0$ 的个数做到目前区间长度的 $l_1$。注意不一定要在 $i$ 结束，所以先 $pre_{i,j}\gets pre_{i-1,j}$。$suf$ 则是类似的。

那么接下来统计答案，设已经钦定了区间 $[l,r]$，则将之变成 $0$ 区间则需要之中 $1$ 的个数 $x$，那么还能操作 $(k-x)$ 次留给 $l_1$，则 $l_1$ 为 $\max(pre_{l-1,k-x}, suf_{r+1,k-x})$。枚举一下 $a$ 求 $\max$ 即可。

```cpp
#include <bits/stdc++.h>
#define rep(i, l, r) for(i=l; i<=r; ++i)
#define req(i, r, l) for(i=r; i>=l; --i)
using namespace std;
int t, n, k, i, j, cnt;
const int N=3005, K=3005, inf=-(1<<29);
int a[N], pre[N][K], suf[N][K], f[N], ans[N];
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d %d", &n, &k); rep(i, 1, n) scanf("%1d", a+i);
		rep(i, 0, n) f[i]=ans[i]=inf;
		rep(i, 0, n+1) rep(j, 0, n) pre[i][j]=suf[i][j]=0;
		rep(i, 1, n)
		{	cnt=0;
			rep(j, 0, n) pre[i][j]=pre[i-1][j];
			req(j, i, 1)
			{
				if(a[j]==0) ++cnt;
				pre[i][cnt]=max(pre[i][cnt],i-j+1);
			}
		} f[0]=pre[n][k];
		req(i, n, 1)
		{	cnt=0;
			rep(j, 0, n) suf[i][j]=suf[i+1][j];
			rep(j, i, n)
			{
				if(a[j]==0) ++cnt;
				suf[i][cnt]=max(suf[i][cnt], j-i+1);
			}
		} 
		rep(i, 1, n)
		{	cnt=0;
			rep(j, i, n)
			{
				if(a[j]) if(++cnt>k) break;
				f[j-i+1]=max(f[j-i+1], max(pre[i-1][k-cnt], suf[j+1][k-cnt]));
			}
		}
		rep(i, 1, n) rep(j, 0, n) ans[i]=max(ans[i], i*j+f[j]);
		rep(i, 1, n) printf("%d ", ans[i]); puts("");
	}
}
```

---

## 作者：CuCl4Loliko (赞：3)

### Preface

我这个做法有点奇怪。。

### Problem

给你一个长度为 $n (1 \leq n \leq 3000)$ 的 01 串，定义 $len_1$ 为其中最长的 1 的连续段长度，$len_0$ 为其中最长的 0 的连续段长度，整个 01 串的价值为 $a \times len_0 + len_1$。

你可以进行一些操作，每次操作可以将某个位置的数字取反。

现在你需要对于所有的 $a$ 的取值 $(1 \leq a \leq n)$，求出**至多**操作 $k$ 次后 01 串的最大价值。

### Solution

问题有些复杂，考虑先进行一些转化。

注意到数据范围允许 $O(n^2)$ 的操作，我们可以先枚举所有子区间，求出将这些区间全部变为 0 或 1 需要多少次操作，并记录下来。

定义 $l_{1,i,j}$ 为将 $[1,i]$ 这个区间操作 $j$ 次后最多可以出现多长的 1 连续段，$r_{1,i,j}$ 为将 $[i,n]$ 这个区间操作 $j$ 次后最多可以出现多长的 1 连续段，$l_{0,i,j}$ 和 $r_{0,i,j}$ 同理。

当我们枚举到 $[i,j]$ 这个区间时，假设这个区间中有 $m$ 个 1，那么我们就更新数组 $l_{0,j,m} = (j-i+1)$，同理也可以更新其他四个数组。

然后做一个小 DP，更新出 $l$ 和 $r$ 数组的所有状态。

正序枚举 $i$，更新 $l$ 数组。

$$l_{0,i,j} = \max(l_{0,i,j},l_{0,i-1,j},l_{0,i,j-1})$$
$$l_{1,i,j} = \max(l_{1,i,j},l_{1,i-1,j},l_{1,i,j-1})$$

逆序枚举 $i$，更新 $r$ 数组。

$$r_{0,i,j} = \max(r_{0,i,j},r_{0,i+1,j},r_{0,i,j-1})$$
$$r_{1,i,j} = \max(r_{1,i,j},r_{1,i+1,j},r_{1,i,j-1})$$

接着枚举断点 $i$，即枚举最长 0/1 连续段出现的位置，有两种情况。第一个是 $[1,i]$ 中包含 0 的最长连续段，$[i+1,n]$ 中包含 1 的最长连续段。另一个是 $[1,i]$ 中包含 1 的最长连续段，$[i+1,n]$ 中包含 0 的最长连续段。

同时在内层枚举使用次数 $j$，即在 $[1,i]$ 中操作 $j$ 次，在 $[i+1,n]$ 中操作 $k-j$ 次。

定义 $ans_i$ 表示如果出现了一个长度为 $i$ 的 0 的连续段，剩下的操作还能在此基础上出现一个多长的 1 的连续段。

在枚举断点时即可求出 $ans$ 数组。假设枚举到断点 $i$，左区间操作 $j$ 次，那么 

$$ans_{l_{0,i,j}} = \max(ans_{l_{0,i,j}},r_{1,i+1,k-j})$$
$$ans_{r_{0,i+1,k-j}} = \max(ans_{r_{0,i+1,k-j}},l_{1,i,j})$$

现在我们枚举每个 $a$ 的取值 $i$，再枚举 0 连续段的长度 $j$，那么答案就是 $\max(i \times j + ans_j)$。

### Code 

赛时写了一大坨，调了半小时。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=3e3+5,INF=1e8;
int f1[maxn][maxn],f2[maxn][maxn],s[maxn];
char a[maxn];
int l1[maxn][maxn],l2[maxn][maxn],r1[maxn][maxn],r2[maxn][maxn];
int ans[maxn];

signed main()
{
	int T;
	cin>>T;
	while(T--)
	{
		int n,k;
		cin>>n>>k;
		scanf("%s",a+1);
		for(int i=1;i<=n;i++)
		{
			s[i]=s[i-1];
			if(a[i]=='1') s[i]++;
		}
		for(int i=0;i<=n+1;i++)
		{
			for(int j=0;j<=n+1;j++)
				l1[i][j]=l2[i][j]=r1[i][j]=r2[i][j]=ans[i]=0;
		}
		for(int i=1;i<=n;i++)
			for(int j=i;j<=n;j++)
			{
				f1[i][j]=s[j]-s[i-1];
				f2[i][j]=(j-s[j])-(i-1-s[i-1]);
				l1[j][f1[i][j]]=max(l1[j][f1[i][j]],j-i+1);
				l2[j][f2[i][j]]=max(l2[j][f2[i][j]],j-i+1);
				r1[i][f1[i][j]]=max(r1[i][f1[i][j]],j-i+1);
				r2[i][f2[i][j]]=max(r2[i][f2[i][j]],j-i+1);
			}
		for(int i=1;i<=n;i++)
			for(int j=0;j<=min(k,i);j++)
			{
				l1[i][j]=max(l1[i][j],l1[i-1][j]);
				l1[i][j]=max(l1[i][j],l1[i][j-1]);
				l2[i][j]=max(l2[i][j],l2[i-1][j]);
				l2[i][j]=max(l2[i][j],l2[i][j-1]);
			}
		for(int i=0;i<=k;i++)
			r1[n+1][i]=0;
		for(int i=n;i>=0;i--)
			for(int j=0;j<=min(k,n-i+1);j++)
			{
				r1[i][j]=max(r1[i][j],r1[i+1][j]);
				r1[i][j]=max(r1[i][j],r1[i][j-1]);
				r2[i][j]=max(r2[i][j],r2[i+1][j]);
				r2[i][j]=max(r2[i][j],r2[i][j-1]);
			}
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				ans[i]=-INF;
		for(int i=0;i<=n;i++)
			for(int j=0;j<=k;j++)
			{
				ans[l1[i][j]]=max(ans[l1[i][j]],r2[i+1][k-j]);
				ans[r1[i+1][j]]=max(ans[r1[i+1][j]],l2[i][k-j]);
			}
		for(int i=1;i<=n;i++)
		{
			int res=0;
			for(int j=0;j<=n;j++)
				res=max(res,ans[j]+i*j);
			cout<<res<<" ";
		}
		cout<<endl;
	}
	return 0;
}

```



---

## 作者：Gao_yc (赞：3)

# Solution：

首先发现进行更改后 $0$、$1$ 连续段一定不重合。

于是考虑预处理出对于每个前后缀，使用不超过 $i$ 次修改后的最长 $0$、$1$ 连续段长度。

然后枚举分界中心，以及左边和右边分到的修改次数，便可得到更改后 $0$ 连续段长度为 $i$ 时，$1$ 连续段的最长长度 $mx_i$。

利用 $mx$ 数据更新最终答案便好了。

复杂度 $\mathcal{O}(n^2)$。

具体代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3010;
int n,k,mx[N];
int a[N],sa[N];
char s[N];
int anszl[N][N],anszr[N][N],ansol[N][N],ansor[N][N];
int main(){
	int T;scanf("%d",&T);
	while(T--){
		scanf("%d%d%s",&n,&k,s+1);
        for(int i=1;i<=n;++i) a[i]=s[i]-'0',sa[i]=a[i]+sa[i-1],mx[i]=-1;
        for(int i=0;i<=n+1;++i) 
            for(int j=0;j<=k;++j)
                anszl[i][j]=anszr[i][j]=ansol[i][j]=ansor[i][j]=0;
        for(int i=1;i<=n;++i){
            for(int j=0;j<=k;++j){
                int l=0,r=i,res=i;
                while(l<=r){
                    int mid=(l+r)>>1;
                    if((i-mid)-(sa[i]-sa[mid])<=j) res=mid,r=mid-1;
                    else l=mid+1;
                }
                ansol[i][j]=max(i-res,ansol[i-1][j]);
            }
        }
        for(int j=0;j<=k;++j) ansor[n+1][j]=0;
        for(int i=n;i;--i){
            for(int j=0;j<=k;++j){
                int l=i-1,r=n,res=i-1;
                while(l<=r){
                    int mid=(l+r)>>1;
                    if((mid-i+1)-(sa[mid]-sa[i-1])<=j) res=mid,l=mid+1;
                    else r=mid-1;
                }
                ansor[i][j]=max(res-i+1,ansor[i+1][j]);
            }
        }

        for(int i=1;i<=n;++i){
            for(int j=0;j<=k;++j){
                int l=0,r=i,res=i;
                while(l<=r){
                    int mid=(l+r)>>1;
                    if(sa[i]-sa[mid]<=j) res=mid,r=mid-1;
                    else l=mid+1;
                }
                anszl[i][j]=max(i-res,anszl[i-1][j]);
            }
        }
        for(int j=0;j<=k;++j) anszr[n+1][j]=0;
        for(int i=n;i;--i){
            for(int j=0;j<=k;++j){
                int l=i-1,r=n,res=i-1;
                while(l<=r){
                    int mid=(l+r)>>1;
                    if(sa[mid]-sa[i-1]<=j) res=mid,l=mid+1;
                    else r=mid-1;
                }
                anszr[i][j]=max(res-i+1,anszr[i+1][j]);
            }
        }
        for(int i=0;i<=n;++i){
            for(int j=0;j<=k;++j){
                // printf("%d %d  %d %d\n",anszl[i][j],ansor[i+1][k-j],ansol[i][j],anszr[i+1][k-j]);
                mx[anszl[i][j]]=max(mx[anszl[i][j]],ansor[i+1][k-j]);
                mx[anszr[i+1][k-j]]=max(mx[anszr[i+1][k-j]],ansol[i][j]);
            }
            // puts("");
        }
        // for(int i=1;i<=n;++i) printf("%d ",mx[i]);puts("");
        for(int i=1,res;i<=n;++i){
            res=ansol[n][k];
            for(int j=1;j<=n;++j) if(~mx[j]) res=max(res,i*j+mx[j]);
            printf("%d ",res);
        }
        puts("");
	}
    return 0;
}
```


---

## 作者：Jie_Xu_Sheng (赞：2)

### 题意

给你一个 $01$ 串，你可以更改至多 $k$ 个字符。

询问在 $a=1,2,… n$ 时，$a$ 乘上最长 $0$ 串的长度再加上最长 $1$ 串的长度。

### 思路

考虑最终最长 $0$ 串和最长 $1$ 串的位置。

预处理 $dp1[i][j]$ 表示在第 $i$ 位及以后改至多 $j$ 个所能够改出的最长 $1$ 串的长度。$dp0[i][j]$ 同理。再预处理出前缀 $0$ 的个数和前缀 $1$ 的个数。

设 $mx[i]$ 表示在最长 $0$ 串的长度位 $i$ 的情况下最长 $1$ 串的最长长度。

枚举两个串中前面的串最后一个字符的位置 $x$ ，假设最长 $0$ 串在前，最长 $1$ 串在后。

最长 $1$ 串在前，最长 $0$ 串在后的情况同理。

那么再枚举 $pos$ 属于 $1$ 到 $x$ ,表示将 $pos$ 到 $x$ 的位置全部改为 $0$ 。需要的次数 $p$ 可以用前缀 $1$ 的个数算出。然后可以用 $dp1[x+1][k-p]$ 来更新 $mx[x-pos+1]$。

最后再枚举 $1$ 到 $n$ ，算出 $a$ 在每一个值时的答案。

总体复杂度是在 $n^2$ 级别的，足以通过本题。

### 细节

1. 清空两个 $dp$ 数组时一定要清空到 $n+1$, 否则会 WA on test 5。

2. 数组一定要开到 $n+2$ (因为要清空到 $n+1$ )，否则会 WA on test 8。

### Code

[CF1858D Trees and Segments](https://codeforces.com/contest/1858/submission/219033488)

---

## 作者：Palbudir (赞：2)

## 思路：
通过观察 $n$ 的范围（$n\leq3000$）可以猜到，本题解法大概是 $\Theta(n^2)$ 的时间复杂度。

而直接做的话是 $\Theta(n^3)$ 的，肯定不行，那就应该要进行一些预处理。

## 解法：

将区间 $[1,i]$ 内，改变 $j$ 个数所能产生的最长 $0$ 串和 $1$ 串，分别记为 $l_{0,i,j}$ 和 $l_{1,i,j}$，以及区间 $[i,n]$ 内，改变 $j$ 个数所能产生的最长 $0$ 串和 $1$ 串，分别记为 $r_{0,i,j}$ 和 $r_{1,i,j}$。

先预处理出 $l_{0,i,j}$，$l_{1,i,j}$，$r_{0,i,j}$ 和 $r_{1,i,j}$。预处理完了这 $4$ 个数组，就可以通过枚举 $k$ 个操作的分配给 $0$ 和 $1$ 的方案所产生的最长 $0$ 串长度 $l_0$，和最长 $1$ 串长度 $l_1$，算出对于任意 $l_0$ 改变最多 $k$ 个数所得到的最大 $l_1$，记为 $f_{l_0}$。

然后，分别枚举 $a$ 和 $l_0$，对于每个 $a$，找到能使 $a\cdot l_0+f_{l_0}$ 最大的 $l_0$，再用个 $max$ 存答案就可以了。

## 注意：
我觉得这题的重点在预处理 $4$ 个数组那里，细节太多了，晚上想不完，没写出来，第二天起来做也是交了好几次才对。

题目给的时空间限制也很紧，因为用到的数组比较多，$N$ 就不能开太大，每个测试开始的初始化也要尽量少。

## 代码：

```cpp
#include<iostream>
#include<cmath>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
#define N 3005
inline int read(){
	int n=0;char c=0;
	while(c<48||c>57) c=getchar();
	while(c>47&&c<58) n=(n<<3)+(n<<1)+(c^48),c=getchar();
	return n;
}
int a[N];
int l0[N][N];
int l1[N][N];
int r0[N][N];
int r1[N][N];
int p0[N],n0;
int p1[N],n1;
int k01[N];
signed main(){
	int t;
	t=read();
	while(t--){
		n0=0,n1=0;
		int n,m,len0=0,len1=0,maxn=0;
		string s;
		n=read(),m=read();
		cin>>s;
		for(int i=1;i<=n;++i){
			a[i]=s[i-1]-'0';
			if(a[i]==0) p0[++n0]=i;
			if(a[i]==1) p1[++n1]=i;
		}
		p0[0]=0,p1[0]=0;
		p0[n0+1]=n+1;p1[n1+1]=n+1;
		for(int i=0;i<=m;++i) l0[0][i]=l1[0][i]=0;
		for(int i=1,k0=0,k1=0;i<=n;++i){
			for(int j=0;j<=m;++j) l0[i][j]=l0[i-1][j];
			for(int j=0;j<=m;++j) l1[i][j]=l1[i-1][j];
			if(a[i]==0){
				for(int j=0;j<=k1;++j){
					l0[i][j]=max(l0[i][j],i-p1[k1-j]);
				}
				++k0;
				for(int j=0;j<k0;++j){
					l1[i][j]=max(l1[i][j],i-p0[k0-j-1]-1);
				}
				l1[i][k0]=i;
			}
			if(a[i]==1){
				for(int j=0;j<=k0;++j){
					l1[i][j]=max(l1[i][j],i-p0[k0-j]);
				}
				++k1;
				for(int j=0;j<k1;++j){
					l0[i][j]=max(l0[i][j],i-p1[k1-j-1]-1);
				}
				l0[i][k1]=i;
			}
		}
		for(int i=0;i*2<=n0;++i) swap(p0[i],p0[n0-i+1]);
		for(int i=0;i*2<=n1;++i) swap(p1[i],p1[n1-i+1]);
		for(int i=0;i<=m;++i) r0[n+1][i]=r1[n+1][i]=0;
		for(int i=n,k0=0,k1=0;i;--i){
			for(int j=0;j<=m;++j) r0[i][j]=r0[i+1][j];
			for(int j=0;j<=m;++j) r1[i][j]=r1[i+1][j];
			if(a[i]==0){
				for(int j=0;j<=k1;++j){
					r0[i][j]=max(r0[i][j],p1[k1-j]-i);
				}
				++k0;
				for(int j=0;j<k0;++j){
					r1[i][j]=max(r1[i][j],p0[k0-j-1]-i-1);
				}
				r1[i][k0]=n+1-i;
			}
			if(a[i]==1){
				for(int j=0;j<=k0;++j){
					r1[i][j]=max(r1[i][j],p0[k0-j]-i);
				}
				++k1;
				for(int j=0;j<k1;++j){
					r0[i][j]=max(r0[i][j],p1[k1-j-1]-i-1);
				}
				r0[i][k1]=n+1-i;
			}
		}
		for(int i=0;i<=n+1;++i){
			for(int j=1;j<=m;++j){
				l0[i][j]=max(l0[i][j],l0[i][j-1]);
				l1[i][j]=max(l1[i][j],l1[i][j-1]);
				r0[i][j]=max(r0[i][j],r0[i][j-1]);
				r1[i][j]=max(r1[i][j],r1[i][j-1]);
			}
		}
		for(int i=0;i<=n;++i) k01[i]=-N*N;
		for(int i=0;i<=n;++i){
			for(int k=0;k<=m;++k){
				len0=l0[i][k],len1=r1[i+1][m-k];
				k01[len0]=max(k01[len0],len1);
				len0=r0[i+1][k],len1=l1[i][m-k];
				k01[len0]=max(k01[len0],len1);
			}
		}
		for(int i=1;i<=n;++i){
			maxn=0;
			for(int j=0;j<=n;++j) maxn=max(maxn,i*j+k01[j]);
			cout<<maxn<<" ";
		}
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：EuphoricStar (赞：2)

美丽度的式子可以写成 $(a - 1) \times l_0 + (l_0 + l_1)$，注意到 $a \ge 1$，也就是我们若固定了 $l_0 + l_1$，$l_0$ 越大就越优。

于是我们可以预处理出对于所有的 $p = l_0 + l_1$，$l_0$ 的最大值，设其为 $g_p$。回答时枚举 $p = l_0 + l_1$，贡献即为 $(a - 1) g_p + p$。

考虑如何预处理。我们分类讨论 $0$ 的最大区间在 $1$ 的最大区间的左或者右。以在左边为例（右边类似），我们考虑枚举 $1$ 最大区间的左右端点 $[l, r]$，前缀和计算出要改 $t$ 次，然后随着 $l$ 往右移动，我们可以处理出所有右端点在 $l$ 左侧的 $0$ 最大区间，并得到 $f_i$ 为用不超过 $i$ 次修改 $0$ 最大区间长度。然后 $1$ 最大区间对 $g$ 的贡献即为：

$$g_{r - l + 1 + f_{k - t}} \gets \max(g_{r - l + 1 + f_{k - t}}, f_{k - t})$$

注意一下 $l_1 = 0$ 的 corner case。

时间复杂度 $O(n^2)$。赛时被这题卡了近 1h，没话说了。

[code](https://codeforces.com/contest/1858/submission/219030192)

---

## 作者：Xy_top (赞：1)

为什么这道题能有 *2200 啊？

枚举连续的 $0$ 的区间，假设是 $[i,j]$，那么连续 $1$ 的区间在 $[1,i-1]$ 和 $[j + 1,n]$ 中，求这个可以使用 DP。

考虑如果统计答案，设 $f_{i, j}$ 为 $[1,i]$ 中改小于等于 $j$ 个位置最多的连续 $1$，$g_{i,j}$ 是后缀。

再令 $mx_i$ 为经过修改后有连续 $i$ 个 $0$ 时，最多连续的 $1$，这个直接枚举连续 $0$ 的区间就可以求。

最后当 $a=j$ 时，答案为 $\max\limits_{i=1}^n{a*i+mx_i}$。刚开始以为直接枚举会超时还用了斜率优化。。。

代码：


```cpp
#include <bits/stdc++.h>
#define int long long
#define For(i, a, b) for (int i = (a); i <= (b); i ++)
#define foR(i, a, b) for (int i = (a); i >= (b); i --)
using namespace std;
int n, k;
int f[3005][3005], g[3005][3005];
int a[3005], mx[3005];//当 l0 = i 时，最大的 l1
char s[3005];
/*
case1：枚举橡树连续区间
case2：计算最大 l1，放进 vector
 
f[i][j] 1 ~ i 修改 j 个，最多的连续 1
 
g[i][j] i ~ n 修改 j 个，最多的连续 1
 
求 a * l0 + l1
*/
void solve () {
	cin >> n >> k >> s + 1;
	For (i, 0, n + 1) For (j, 0, n + 1) f[i][j] = g[i][j] = 0;
	For (i, 1, n) a[i] = a[i - 1] + s[i] - 48;
	For (i, 0, n) mx[i] = -10000000000000000LL;
	mx[0] = 0;
	For (i, 1, n) {
		For (j, i, n) if (j - i + 1 - a[j] + a[i - 1] <= k) mx[0] = max (mx[0], j - i + 1);
	}
	For (i, 1, n) {
		For (j, 0, i) {
			if (s[i] == '1') f[i][j] = f[i - 1][j] + 1;
			else if (j) f[i][j] = f[i - 1][j - 1] + 1;
		}
	}
	For (i, 1, n) For (j, 1, i) f[i][j] = max (f[i][j], f[i][j - 1]);
	For (i, 1, n) For (j, 0, i) f[i][j] = max (f[i][j], f[i - 1][j]);
	foR (i, n, 1) {
		For (j, 0, n - i + 1) {
			if (s[i] == '1') g[i][j] = g[i + 1][j] + 1;
			else if (j) g[i][j] = g[i + 1][j - 1] + 1;
		}
	}
	foR (i, n, 1) For (j, 1, i) g[i][j] = max (g[i][j], g[i][j - 1]);
	foR (i, n - 1, 1) For (j, 0, n - i + 1) g[i][j] = max (g[i][j], g[i + 1][j]);
	For (i, 1, n) {
		For (j, i, n) {
			int cnt = a[j] - a[i - 1];
			if (cnt > k) continue;
			mx[j - i + 1] = max (mx[j - i + 1], f[i - 1][k - cnt]);
			mx[j - i + 1] = max (mx[j - i + 1], g[j + 1][k - cnt]);
		}
	}
	int curr = 0;
	For (i, 1, n) {
		int ans = 0;
		For (j, 0, n) ans = max (ans, i * j + mx[j]);
		cout << ans << ' ';
	}
}
signed main () {
	int _ = 1;
	cin >> _;
	while (_ --) {
		solve ();
		cout << '\n';
	}
	return 0;
}
```

---

## 作者：Disjoint_cat (赞：1)

从[我的博客](https://www.cnblogs.com/No-play-Yes-splay/p/codeforces-round-893-div2-sol.html)搞过来的。

# [CF1858D Trees and Segments](https://www.luogu.com.cn/problem/CF1858D)

DP 好题。赛时没做出来。

记 $pre_{i,j}$ 为前 $i$ 个字符，最多修改 $j$ 次，所能得到的最长连续的 $0$ 的数量。同理定义 $suf_{i,j}$，表示从 $i$ 到末尾，其余同 $pre$。

然后这两个东西是好转移的。

考虑令最长连续 $1$ 的区间为 $[l,r]$，我们可以求出需要修改的位置数量（假设为 $t$）。那么此时，最长连续的 $0$ 的数量就是 $\max\{pre_{l-1,k-t},suf_{r+1,k-t}\}$，然后再去更新答案（当然如果 $t>k$ 也就不用更新）。

直接这样做是 $\Theta(n^3)$ 的。

注意到对于固定的长度，我们只需求出连续 $0$ 的最大长度就可以了。然后对于相邻长度相等的两个区间，要修改的个数也只需要 $\Theta(1)$ 转移。

于是我们枚举长度 $len$，再扫一遍长度为 $len$ 的所有区间（这只需要 $\Theta(n)$），可以求出此时连续 $0$ 的最大长度。然后我们用其来更新答案即可。

总复杂度 $\Theta(n^2)$。听说还能优化到 $\Theta(nk)$。

**多测不清空，WA 两行泪。**

### 代码实现

```cpp
const int N=3005;
int n,k,pre[N][N],suf[N][N],ans[N];
string st;
void Solve()
{
	cin>>n>>k>>st;st="$"+st;
	for(int i=1;i<=n;i++)
		for(int j=0;j<=k;j++)
			if(st[i]=='1')
			{
				if(j)pre[i][j]=pre[i-1][j-1]+1;
				else pre[i][j]=0;
			}
			else pre[i][j]=pre[i-1][j]+1;
	for(int i=1;i<=n;i++)
		for(int j=0;j<=k;j++)
			pre[i][j]=max(pre[i][j],max(pre[i-1][j],j?pre[i][j-1]:0));
	for(int i=n;i;i--)
		for(int j=0;j<=k;j++)
			if(st[i]=='1')
			{
				if(j)suf[i][j]=suf[i+1][j-1]+1;
				else suf[i][j]=0;
			}
			else suf[i][j]=suf[i+1][j]+1;
	for(int i=n;i;i--)
		for(int j=0;j<=k;j++)
			suf[i][j]=max(suf[i][j],max(suf[i+1][j],j?suf[i][j-1]:0));
	for(int i=0;i<=n;i++)
	{
		int d=-1,c=k;
		for(int j=1;j<i;j++)if(st[j]=='0')c--;
		for(int j=1;j<=n-i+1;j++)
		{
			if(st[j-1]=='0')c++;
			if(st[j+i-1]=='0')c--;
			if(c<0)continue;
			d=max(d,max(pre[j-1][c],suf[j+i][c]));
		}
		if(~d)for(int j=1;j<=n;j++)ans[j]=max(ans[j],d*j+i);
	}
	for(int i=1;i<=n;i++)cout<<ans[i]<<sp_el(i,n);
}
```

---

## 作者：__vector__ (赞：1)

本题解作者是一个赛时没看题面，赛后一眼秒掉的小丑。  
## Sol  
我们先扔掉那些乱七八糟的情况，只考虑长度最长的那个连续 $0$ 子串。  

我们需要枚举所有可能的最长连续 $0$ 子串。  

具体做法是，枚举长度 $l_0$，然后枚举所有 $l,r$ 满足 $r-l+1 = l_0$。  

判断 $l$ 到 $r$ 形成的子串能否改造成满足要求的子串。  

如果可以，那我们计算当前状态下，$l_1$ 最多是多少。  

算出来这个，自然也就可以得知同一个 $l_0$ 对应的最大 $l_1$ 是多少。  

本题即迎刃而解。  

现在解决这个问题：如何算出当前状态下，$l_1$ 最多是多少。  

设 $l$ 到 $r$ 的子串改造费用为 $cost$，那么 $l$ 到 $r$ 以外的字符还有 $k-cost$ 次机会改造。  

然后对于前后缀分别 dp，这个是 dp 初学者就会的，不用说了。  

[Code](https://codeforces.com/contest/1858/submission/219199771)  

---

## 作者：Mashu77 (赞：0)

考虑 dp，设 $f_{i,0/1}$
 表示考虑到前 $i$
 位，且第 $i$
 位填入 A/B 可能的答案集合，显然地朴素转移时间复杂度 $O(n^2)$。

试分析 dp 性质，观察发现所有 dp 中得到的集合为区间内抠去至多一个点。

证明：

我们首先来观察转移过程是怎样的。第一种是第二行中 $i-1$
 填入的字母与第一行中 $i$
 填入的字母相同的情况，此时根据我们填入的字母与其相同与否，集合会整体平移 $0$
 或 $-2$；第二种是不同的情况，此时无论我们如何填入字母，集合都会整体平移 $1$。由于我们只关心集合的相对位置关系，我们可以将转移视为将 $f_{-1,0/1}$
 固定不动，将 $f_{i-1,1/0}$
 平移 $1$
 以及 $-1$，分别进行取或操作，得到 $f_i$。
首先容易发现，$f_i$
 的两个集合两侧端点的差的绝对值分别不超过 $2$。这是由于这两个集合是由一个固定的集合或上另外一个集合平移 $1/-1$
 得到的。现在，我们可以归纳说明一个更强的结论：$f_i$
 的两个集合中至多存在一个集合中存在且恰存在一个空位。

显然 $1$
 满足条件。假设 $i-1$
 满足此条件。由于区间过小时的情况比较神秘，我们在此只讨论 $r-l+1\ge5$
 的情况。对于区间更小的情况打表可证。在这种情况下，最坏是 $f_{i-1,x}$
 为 $[l,r]$
 抠去 $p(p\in(l,r)),f_{i-1,1-x}$
 为 $[l+2,r-2]$。此时，若 $i$
 不满足此条件，则存在一个 $p$
 使得 $[l+2,r-2]$
 无论平移 $1$
 还是 $-1$
 都无法覆盖到，而这显然无解。

故证毕。证得比原结论更强的结论，故原结论也证毕。

所以说对于每个 $f_{i,0/1}$
 只需要维护 $(l,r,p)$，即（左端点，右端点，中间挖去的点）

时间复杂度 $O(n)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int NN = 2e5 + 8;
int T;
int n,k;
char s[NN],S[NN];
struct Node{
	int l,r,p;
	Node operator + (int x){
		return {l+x,r+x,p==-1?-1:p+x};
	}
	bool ckin(int x){
		return l <= x && x <= r && x != p;
	}
}f[NN][2];
Node operator ^ (Node a, Node b){
	if(a.l > b.l) swap(a,b);
	Node res = {min(a.l,b.l),max(a.r,b.r),-1};
	if(a.r + 2 == b.l) res.p = a.r + 1;
	else{
		if(a.p != -1 && !b.ckin(a.p)) res.p = a.p;
		if(b.p != -1 && !a.ckin(b.p)) res.p = b.p;
	}
	return res;
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&k);
		scanf("%s",s+1);
		for(int i = 1; i < n; ++i) k -= (s[i]!=s[i+1]);
		if(k < 0){puts("NO");continue;}//判第一行
		int type = s[1] - 'A';
		f[1][type^1] = {1,1,-1}; f[1][type] = {0,0,-1};
		
		int ty;
		for(int i = 2; i <= n; ++i){
			ty = s[i]-'A';
			f[i][ty] = f[i-1][ty] ^ f[i-1][ty^1]+1;
			f[i][ty^1] = f[i-1][ty]+2 ^ f[i-1][ty^1]+1;
		}
		
		ty = -1;
		if(f[n][0].ckin(k)) ty = 0;
		if(f[n][1].ckin(k)) ty = 1;
		if(ty == -1) {puts("NO");continue;}
		puts("YES");
		for(int i = n; i; --i){
			S[i] = 'A' + ty;
			if(i == 1) break;
			k -= (S[i]!=s[i]);
			if(f[i-1][ty].ckin(k)) continue;//只要有答案就走 
			ty ^= 1, --k;
		}
		printf("%s\n",S+1);//ans collecting
		for(int i = 1; i <= n; ++i) S[i] = '\000';
	}
}

---

## 作者：Zimo_666 (赞：0)

## D. Trees and Segments

我们考虑可以通过操作从而实现最长的 $0$ 连续段区间 $[L,R]$，此时我们已经用了 $cnt_{0}(\text{from }L\text{ to }R)$。

设 $ans_i$ 表示当 $0$ 的连续段长度为 $i$，最长的 $1$ 的连续段的长度。

设 $suf_{i,j}$ 表示 $i$ 起点的一段区间的子串，满足 $cnt_0\le j$ 的最大长度。

设 $pre_{i,j}$ 表示 $i$ 结尾的一段区间的子串，满足 $cnt_0\le j$ 的最大长度。

$suf_{i,j}$、$pre_{i,j}$ 均可以用双指针 $O(n^2)$ 求出。

我们枚举 $[L,R]$，$ans_{R-L+1}=\max\{\max\limits_{i=r+1}^{n} suf_{i,k_{left}},\max\limits_{i=1}^{l-1} pre_{i,k_{left}}\}$。

最后别忘了求答案的时候看看 $ans_{R-L+1}$ 存不存在。

[Code](https://codeforces.com/contest/1858/submission/232044728)

---

## 作者：intel_core (赞：0)

假设我们现在钦定了最长的 $0$ 的区间是 $[l,r]$，用了 $x$ 次操作。那么我们只需要在补集中再找一段尽量长的区间使得其中的 $0$ 不超过 $k-x$ 个。

那我们可以用双指针与前缀和预处理出以右端点不超过/左端点不小于 $i$ 并且区间中的 $0$ 至多 $j$ 个的区间长度的最大值 $f_{i,j}/g_{i,j}$。

所以钦定 $[l,r]$ 后，对答案的贡献就是 $r-l+1+\max\{f_{l-1,k-x},g_{r+1,k-x} \}$。

然后我们可以暴力枚举上面钦定的 $[l,r]$，求出 $maxlen_i$ 表示满足 $r-l+1=i$ 的所有区间，对应情况下能选出的连续 $1$ 段长度的最大值。

最后对于询问 $x$，答案就是 $\max\{i\times x+maxlen_i \}$。

复杂度 $O(n^2)$。

---

## 作者：MaxBlazeResFire (赞：0)

赛场上就差一个前后缀 $\max$ 就做完了，十分可惜。

---

记 $f_{i,j}$ 表示考虑字符段 $[1,i]$，得到长度为 $j$ 的连续 $0$ 段需要花费的最小代价，可以通过枚举长度，枚举连续 $0$ 段起点求得。

记 $g_{i,j}$ 表示考虑字符段 $[i,n]$，花费 $j$ 的代价能够得到的最长连续 $1$ 的长度。可以通过枚举长度，枚举 $1$ 段起点然后对代价取 $\max$ 求得。

记 $r_i$ 表示保证当序列中出现极长的连续 $0$ 段长度为 $i$ 时，连续 $1$ 段的长度最长为多少。

有 $\displaystyle r_j=\max_{i,f_{i,j}\leq k}g_{i+1,k-f_{i,j}}$。

然后把上面两个数组的意义倒过来考虑以处理极长段 $0$ 在极长段 $1$ 后方的问题。

求答案的时候直接用 $r$ 数组即可。

然后你交上去之后就会 $\rm WA\ on\ pretest\ 3$。

原因在于，$g_{i,j}$ 统计的是所有起点恰好位于 $i$ 的连续 $1$ 段的贡献，因此还要在第一维上倒序枚举取后缀 $\rm max$。倒过来后要处理前缀 $\rm max$。

于是就做完了，注意多测清空。复杂度 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define MAXN 3005
#define INF 1e9

int n,k,a[MAXN],cnt[2][MAXN];
int f[MAXN],pre[MAXN][MAXN],suf[MAXN][MAXN];
int Ans[MAXN];
char s[MAXN];

inline void solve_pre(){
	for( int i = 1 ; i <= n ; i ++ ){
		for( int l = 1 ; l + i - 1 <= n ; l ++ ){
			int r = l + i - 1,cost = i - ( cnt[0][r] - cnt[0][l - 1] );
			if( cost <= k ) pre[r][i] = min( pre[r][i] , cost );
		}
	}
	for( int i = 1 ; i <= n ; i ++ ){
		for( int r = n ; r - i + 1 >= 1 ; r -- ){
			int l = r - i + 1,cost = i - ( cnt[1][r] - cnt[1][l - 1] );
			if( cost <= k ) suf[l][cost] = max( suf[l][cost] , i );
		}
	}
	for( int j = 0 ; j <= n ; j ++ )
		for( int i = n ; i >= 0 ; i -- ) suf[i][j] = max( suf[i][j] , suf[i + 1][j] );
	for( int i = 0 ; i <= n ; i ++ )
		for( int len = 0 ; len <= n ; len ++ )
			if( pre[i][len] <= k )
				f[len] = max( f[len] , suf[i + 1][k - pre[i][len]] );
}

inline void solve_suf(){
	for( int i = 1 ; i <= n ; i ++ ){
		for( int l = 1 ; l + i - 1 <= n ; l ++ ){
			int r = l + i - 1,cost = i - ( cnt[1][r] - cnt[1][l - 1] );
			if( cost <= k ) pre[r][cost] = max( pre[r][cost] , i );
		}
	}
	for( int j = 0 ; j <= n ; j ++ )
		for( int i = 0 ; i <= n ; i ++ ) pre[i][j] = max( pre[i][j] , pre[i - 1][j] );
	for( int i = 1 ; i <= n ; i ++ ){
		for( int r = n ; r - i + 1 >= 1 ; r -- ){
			int l = r - i + 1,cost = i - ( cnt[0][r] - cnt[0][l - 1] );
			if( cost <= k ) suf[l][i] = min( suf[l][i] , cost );
		}
	}
	for( int i = 0 ; i <= n ; i ++ )
		for( int len = 0 ; len <= n ; len ++ )
			if( suf[i][len] <= k )
				f[len] = max( f[len] , pre[i - 1][k - suf[i][len]] );
}

inline void solve(){
	scanf("%d%d",&n,&k);
	scanf("%s",s + 1);
	for( int i = 1 ; i <= n ; i ++ ) a[i] = s[i] - '0';
	for( int i = 0 ; i <= n ; i ++ ) f[i] = -1;
	for( int i = 1 ; i <= n ; i ++ )
		for( int j = 0 ; j < 2 ; j ++ )
			cnt[j][i] = cnt[j][i - 1] + ( a[i] == j );
	for( int i = 0 ; i <= n + 1 ; i ++ )
		for( int j = 1 ; j <= n + 1; j ++ ) pre[i][j] = INF;
	for( int i = 0 ; i <= n + 1 ; i ++ ) pre[i][0] = 0;
	for( int i = 0 ; i <= n + 1 ; i ++ )
		for( int j = 0 ; j <= n + 1 ; j ++ ) suf[i][j] = 0;
	solve_pre();
	for( int i = 0 ; i <= n + 1 ; i ++ )
		for( int j = 1 ; j <= n + 1 ; j ++ ) suf[i][j] = INF;
	for( int i = 0 ; i <= n + 1 ; i ++ ) suf[i][0] = 0;
	for( int i = 0 ; i <= n + 1 ; i ++ )
		for( int j = 0 ; j <= n + 1 ; j ++ ) pre[i][j] = 0;
	solve_suf();
	for( int i = 1 ; i <= n ; i ++ )
		for( int j = 0 ; j <= n ; j ++ )
			if( ~f[j] ) Ans[i] = max( Ans[i] , i * j + f[j] );
	for( int i = 1 ; i <= n ; i ++ ) printf("%d ",Ans[i]);
	puts("");
	for( int i = 1 ; i <= n ; i ++ ) Ans[i] = 0;
	for( int i = 1 ; i <= n ; i ++ ) a[i] = 0;
	for( int i = 1 ; i <= n ; i ++ )
		for( int j = 0 ; j < 2 ; j ++ ) cnt[j][i] = 0;
}

signed main(){
	int testcase; scanf("%d",&testcase);
	while( testcase -- ) solve();
	return 0;
}
```

---

