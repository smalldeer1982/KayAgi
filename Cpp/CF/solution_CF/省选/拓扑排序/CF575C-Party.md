# Party

## 题目描述

Note the unusual memory limit for the problem.

People working in MDCS (Microsoft Development Center Serbia) like partying. They usually go to night clubs on Friday and Saturday.

There are $ N $ people working in MDCS and there are $ N $ clubs in the city. Unfortunately, if there is more than one Microsoft employee in night club, level of coolness goes infinitely high and party is over, so club owners will never let more than one Microsoft employee enter their club in the same week (just to be sure).

You are organizing night life for Microsoft employees and you have statistics about how much every employee likes Friday and Saturday parties for all clubs.

You need to match people with clubs maximizing overall sum of their happiness (they are happy as much as they like the club), while half of people should go clubbing on Friday and the other half on Saturday.

## 说明/提示

Here is how we matched people with clubs:

Friday: 1st person with 4th club (4 happiness) and 4th person with 1st club (4 happiness).

Saturday: 2nd person with 3rd club (81 happiness) and 3rd person with 2nd club (78 happiness).

4+4+81+78 = 167

## 样例 #1

### 输入

```
4
1 2 3 4
2 3 4 1
3 4 1 2
4 1 2 3
5 8 7 1
6 9 81 3
55 78 1 6
1 1 1 1
```

### 输出

```
167
```

# 题解

## 作者：YCS_GG (赞：1)

### CF575C Party

题意：有 $n$ 个人和 $n$ 个俱乐部，分两天去俱乐部，每天恰好有一半人去，并且同一天每人去的不相同

每人每天会对每个俱乐部有着不同的满意度，请你确定一种方案使得满意度之和最大

发现如果我们能够确定每天都有谁去，然后人向俱乐部连边，就是一个最大权完美匹配的问题了

而枚举每天谁去加上一遍KM复杂度为 $O(2^nn^3)$ 看起来很大，不过其实跑不满（也许递归的KM会被卡）


```cpp
#include <cstring>
#include <iostream>
using namespace std;
const int N = 25;
int A[N][N], B[N][N];
int lx[N], ly[N], p[N], slack[N], linky[N];
bool visy[N];
int n;
int G[N][N];
int ans;
void bfs(int u) {
    int x, v = 0, vl = 0, mmin;
    for (int i = 1; i <= n; i++) {
        p[i]     = 0;
        slack[i] = 0x7f7f7f7f;
    }
    linky[v] = u;
    do {
        x = linky[v], mmin = 0x7f7f7f7f, visy[v] = 1;
        for (int y = 1; y <= n; y++) {
            if (!visy[y]) {
                if (slack[y] > lx[x] + ly[y] - G[x][y]) {
                    slack[y] = lx[x] + ly[y] - G[x][y];
                    p[y]     = v;
                }
                if (slack[y] < mmin) {
                    mmin = slack[y];
                    vl   = y;
                }
            }
        }
        for (int y = 0; y <= n; y++) {
            if (visy[y]) {
                lx[linky[y]] -= mmin;
                ly[y] += mmin;
            } else {
                slack[y] -= mmin;
            }
        }
        v = vl;
    } while (linky[v]);
    while (v) {
        linky[v] = linky[p[v]];
        v        = p[v];
    }
}
int KM(int s) {
    for (int i = 1; i <= n; i++) {
        memset(visy, 0, sizeof(visy));
        for (int j = 1; j <= n; j++) {
            G[i][j] = ((1 << i - 1) & s) ? A[i][j] : B[i][j];
        }
        bfs(i);
    }
    int res = 0;
    for (int y = 1; y <= n; y++) {
        res += G[linky[y]][y];
    }
    return res;
}
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> A[i][j];
            A[i][0] = max(A[i][0], A[i][j]);
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> B[i][j];
            B[i][0] = max(B[i][0], B[i][j]);
        }
    }
    int S = (1 << n) - 1;
    for (int s = 0; s <= S; s++) {
        if (__builtin_popcount(s) != n / 2) {
            continue;
        }
        for (int i = 1; i <= n; i++) {
            lx[i] = ((1 << (i - 1)) & s) ? A[i][0] : B[i][0];
            ly[i] = visy[i] = linky[i] = 0;
        }
        ans = max(ans, KM(s));
    }
    cout << ans;
    return 0;
}
```
**Asusetic eru quionours**

---

## 作者：rubbishZZZ (赞：0)

## CF575C Party



#### 题意：

- 在 MDCS（Microsoft Development Center Serbia）工作的员工们非常喜欢派对。他们通常会在周五和周六去夜总会。

  MDCS 中有 $n$ 名员工，城市中也有 $n$ 家夜总会。不幸的是，如果同一夜总会有多于一名 Microsoft 员工，派对的酷炫指数就会无限飙升，派对也会结束，所以夜总会的老板们绝不会让超过一名员工**在同一周**进入同一夜总会（为了确保这一点）。

  你负责组织 Microsoft 员工的夜生活，并且你已经收集了关于每个员工对每个夜总会的喜好程度统计数据，这些数据表明每个员工对周五和周六派对的喜爱程度。

  你需要将员工与夜总会配对，使得总体的幸福感总和最大化（员工的幸福感与他们对夜总会的喜好程度成正比），同时保证一半员工在周五去夜总会，另一半员工在周六去。



#### 解法：

- 观察到数据范围较小，先考虑枚举一个集合的人去周五，剩余去周六，解决枚举后的问题。

  这很明显是二分图匹配问题。我们建立二分图，左部点为员工，右部点为夜总会，枚举的集合为 $S$，$|S|=\frac{n}{2}$。

  对于 $i\in S$，向右部点 $j$ 连周五 $i$ 对 $j$ 的喜爱值，否则连周六 $i$ 对 $j$ 的喜爱值，那么二分图最大权完美匹配即为这个集合的答案。

  枚举 $S$ 再做 KM，复杂度 $O(2^nn^3)$。但由于 $|S|=\frac{n}{2}$，可行的 $S$ 不到 $200000$ 个，可以卡时通过。

- 进一步发掘 KM 的性质，KM 加入单个点复杂度是 $O(n^2)$。因此枚举 $S$ 的过程可以改成搜索，每次判断第 $k$ 个员工是周五去还是周六去，再 $O(n^2)$ 的跑 KM，继续搜索，这样的复杂度是 $O(2^nn^2)$。



#### 代码：

```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <map>
#include <ctime>
#include <random>
#include <cassert>
#include <numeric>
#include <cmath>
#include <bitset>
#include <ext/pb_ds/assoc_container.hpp>
#define pii pair<int, int>
#define fi first
#define se second
#define MP make_pair
#define ep emplace
#define eb emplace_back
#define int long long
#define rep(i, j, k) for (int i = (j); i <= (k); i++)
#define per(i, j, k) for (int i = (j); i >= (k); i--)
typedef double db;
typedef long double ldb;
typedef long long ll;
//typedef __int128 lll;
typedef unsigned long long ull;
typedef unsigned int ui;
using namespace std;
using namespace __gnu_pbds;
bool Mbe;

//char buf[1<<20],*p1,*p2;
//#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,1<<20,stdin), p1 == p2) ? 0 : *p1++)
int read() {
	int s = 0, f = 1;
	char c = getchar();
	while (c < '0' || c > '9') f ^= (c == '-'), c = getchar();
	while (c >= '0' && c <= '9') s = s * 10 + c - '0', c = getchar();
	return f ? s : -s;
}
template<typename T>void chkmax(T&x,const T&y){if(x<y)x=y;}
template<typename T>void chkmin(T&x,const T&y){if(x>y)x=y;}
const int N=45,INF=0x3f3f3f3f3f3f3f3f;
int n,m,vis[N],s[N],pre[N],d[N][N],use[N],mat[N],w[N];
void bfs(int x){
	memset(vis,0,sizeof(vis));
	memset(s,0x3f,sizeof(s));
	memset(pre,0,sizeof(pre));
	int cur=0,pn=0;
	mat[0]=x;
	while(1){
		x=mat[cur];
		int dis=INF;
		vis[cur]=1;
		for(int i=n+1;i<=n+n;i++){
			if(vis[i])continue;
			int tmp=w[i]+w[x]-d[x][i-n];
			if(tmp<s[i])s[i]=tmp,pre[i]=cur;
			if(s[i]<dis)dis=s[i],pn=i;
		}
		w[mat[0]]-=dis,w[0]+=dis;
		for (int i=n+1;i<=n+n;i++){
			if(vis[i])w[i]+=dis,w[mat[i]]-=dis;
			else s[i]-=dis;
		}
		cur=pn;
		if(!mat[cur])break;
	}
	while(cur){
		mat[cur]=mat[pre[cur]];
		cur=pre[cur];
	}
	return;
}
int a[2][N][N];
bool Med;
signed main() {
	fprintf(stderr,"%.3lfMb\n",(&Mbe-&Med)/1024./1024.);
	m=n=read();
	rep(o,0,1){
		rep(i,1,n){
			rep(j,1,n){
				a[o][i][j]=read();
			}
		}
	}
	db pre=1.*clock()/CLOCKS_PER_SEC;
	int Ans=0;
	per(S,(1<<n)-1,1)if(__builtin_popcount(S)==n/2&&1.*clock()/CLOCKS_PER_SEC-pre<=1.95){
		memset(d,~0x3f,sizeof d);
		memset(w,0,sizeof w);
		memset(vis,0,sizeof vis);
		memset(use,0,sizeof use);
		memset(mat,0,sizeof mat);
		rep(i,1,n){
			if(S>>(i-1)&1)rep(j,1,n)d[i][j]=a[0][i][j];
			else rep(j,1,n)d[i][j]=a[1][i][j];
		}
		rep(i,1,n)rep(j,1,n)chkmax(w[i],d[i][j]);
		rep(i,1,n)if(!vis[i])bfs(i);
		int ans=0;
		rep(i,1,n+n)ans+=w[i];
		chkmax(Ans,ans);
	}
	printf("%lld\n",Ans);
	return 0;
}
```

---

## 作者：Lynkcat (赞：0)

首先有个很暴力的 $O(2^nn^3)$ 的做法，是枚举哪些点选择第一种权值的边，然后暴力跑 KM。

但是实际上利用 KM 算法的增量特点，每次加一个点进去更新的复杂度是 $O(n^2)$ 的。因此把枚举集合跟 KM 一起跑，类似 dfs 一样每次枚举这一位是 0 还是 1，然后每次加一个点就跑 KM 更新。这样就能做到 $O(2^nn^2)$ 的复杂度，实际应该能分析更紧。

---

