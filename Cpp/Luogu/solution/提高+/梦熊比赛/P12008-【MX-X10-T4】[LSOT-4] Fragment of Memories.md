# 【MX-X10-T4】[LSOT-4] Fragment of Memories

## 题目背景

甜与苦的一体两面。

## 题目描述

苏珊在昏迷前度过了 $m$ 天。从第一天起，苏珊会有一个基准记忆 $x$，第 $i$（$1\le i\le m$）天的记忆为 $x+i-1$。这 $m$ 天的记忆按顺序依次拼接，得到了一串长为 $m$ 的记忆。

在梦境中，这段记忆被按顺序重复了 $k$ 遍。在这之后，为了唤醒苏珊，露薇娅进入了梦境，记忆被插入了一些不属于苏珊的记忆，最终变为了一个长度为 $n$ 的序列 $a_1, \ldots, a_n$。

现在给你这个序列和 $k$。露薇娅不知道一开始的基准记忆 $x$ 是多少，所以他想知道对于所有的 $1\le x\le V$，$m$ 的值最大可能是多少。若对于一个 $x$ 不存在合法的记忆，输出 $0$。

## 说明/提示

**【样例解释 #1】**

当 $x=2$、$m=3$ 时，苏珊的记忆是 `2 3 4`。重复了 $k=2$ 次变成了 `2 3 4 2 3 4`。在位置 $1$ 和位置 $2$ 中间、位置 $3$ 和位置 $4$ 中间、位置 $5$ 和位置 $6$ 中间分别插入了一个数后变成了原序列。

类似地，`2`、`3`、`4`、`2 3`、`3 4` 都是符合要求的记忆。

**【数据范围】**

**本题采用捆绑测试。**

- 子任务 1（13 分）：$n\le 100$。
- 子任务 2（21 分）：$n\le 3000$。
- 子任务 3（23 分）：$n\le 3\times10^4$。
- 子任务 4（25 分）：$n\le 5\times10^5$。
- 子任务 5（18 分）：无特殊性质。

对于全部的数据，$1\le k\le n\le 2\times 10^6$，$1\le a_i\le V\le n$。

## 样例 #1

### 输入

```
9 2 5
2 1 3 4 5 2 3 2 4```

### 输出

```
0 3 2 1 0```

## 样例 #2

### 输入

```
30 3 8
3 4 5 5 1 2 8 4 5 3 6 4 5 7 5 6 6 7 6 8 7 1 8 2 3 2 7 3 7 8```

### 输出

```
0 2 1 2 1 2 2 1```

# 题解

## 作者：UniGravity (赞：5)

鲜花：Milthm 真的很好玩！111

感谢 @[良心WA题人](https://www.luogu.com.cn/user/132424) 指出了题解复杂度分析的错误。重写了复杂度分析。

首先有一种 $O(n^2\log n)$ 的做法：对于每个基准 $x$ 都二分出最大的 $m$。发现 check 时每次贪心找最前面的某个值配对，这样单次 check 是 $O(n)$ 的。

考虑优化单次 check 的复杂度，一次快速跳一整个长度为 $m$ 的段。发现我们可以预处理某个数 $x$ 后第一个 $x+1$ 的位置，通过倍增即可找出某个数后最小合法的 $x+m-1$ 的位置。同时再通过倍增找出 $x+m-1$ 后下一个 $x$ 的位置。这样 check 就是 $O(c\log n)$ 的（$c$ 是本次 check 合法的段数，因此实现时如果碰到不合法的就立即跳出）。

然后观察 $c$ 和什么有关，发现 $c$ 为 $\min(\min_{i=x}^{x+m-1}cnt_i,k)$，其中 $cnt_i$ 代表值 $i$ 的出现次数。

考虑双指针加上 check 判断。假设当前的区间为 $[x,x+m-1]$，则发现每次 check 后左右端点至少会有一个向右移动：
* 如果 check 失败，则已经找到了 $x$ 的答案，接下来 $x\gets x+1,m\gets m-1$。发现左端点右移，右端点不变。
* 如果 check 成功，则变成 $m\gets m+1$，右端点向右。

若每次 check 复杂度只和**上次区间移动时变化的端点**的出现次数（即 $cnt_l$ 或 $cnt_r$）有关（这样显然比 $\min(\min_{i=x}^{x+m-1}cnt_i,k)$ 的限制松），因为 $\sum_{i=1}^ncnt_i=n$，且 $cnt_i$ 最多只会在 $l,r$ 移动到的时候扫两遍，因此所有的 check 的 $c$ 之和的上界为 $O(n)$。

于是做完了。时间复杂度 $O(n\log n)$。

```cpp
const int N=2000005;
int n,k,V,a[N],nxt[22][N],nv[22][N],pre[N];

il bool check(int bs,int m){
    int p=pre[bs],c,p1,p2;if(!p)return 0;
    // cerr<<"check "<<bs<<' '<<m<<'\n';
    forto(i,1,k){
        c=m-1,p1=p;
        forbk(t,21,0)if((1<<t)<=c)c-=1<<t,p1=nxt[t][p1];//,cerr<<t<<','<<p1<<' ';cerr<<'\n';
        // cerr<<p<<' '<<m<<' '<<p1<<'\n';
        if(!p1)return 0;
        if(i==k)return 1;
        p2=p;
        forbk(t,21,0)if(nv[t][p2]&&nv[t][p2]<=p1)p2=nv[t][p2];
        p2=nv[0][p2];if(!p2)return 0;
        p=p2;
    }
    return 1;
}

signed main(){
    n=read(),k=read(),V=read();
    forto(i,1,n)a[i]=read();
    forbk(i,n,1)nv[0][i]=pre[a[i]],nxt[0][i]=pre[a[i]+1],pre[a[i]]=i;
    // forto(i,1,n)cerr<<nxt[0][i]<<' ';cerr<<'\n';
    forto(t,1,21)forto(i,1,n)nxt[t][i]=nxt[t-1][nxt[t-1][i]],nv[t][i]=nv[t-1][nv[t-1][i]];
    int ans=0;
    forto(i,1,V){
        while(check(i,ans+1))ans++;
        printf("%d ",ans);
        if(ans)ans--;
    }
    puts("");
    return 0;
}
```

---

## 作者：qqqaaazzz_qwq (赞：2)

你说得对，但是 $\Theta(n \log^2 n)$ 的做法是可以通过 $n=2\times 10^6$ 的！！

考虑怎么求 $ans_i$。先二分，就变成了能不能让 $ans_i \geq c$。

把 $a$ 中等于 $i$ 的位置拎出来，从小到大贪心考虑，每次找到最左边可以用的 $i$，然后往后倍增跳 $c-1$ 步，然后再找到下一个可以用的 $i$，如此循环。如果最后能做到 $k$ 步就是 ok 的。

二分+倍增往后跳就是两只 $\log$。有几点优化：

1. 倍增往后跳的时候可以提前把 $c$ 二进制拆分。
2. 有 $ans_i \geq ans_{i-1}-1$，所以左边界就确定了。
3. 可以用一种更快的二分方式，见代码。

无需卡常。赛时一遍过了。

```cpp
#include <bits/stdc++.h>
#define FAST ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
using namespace std;
int n,k,V;
int a[2000010];
int st[2000010][23];
int ans[2000010];
int lst[2000010];
vector<int> v[2000010];

bool check(int X,int Y){
	//X 能不能拓展出来 Y ？
	--Y;
	vector<int> qwq;
	for (int i=21;i>=0;i--){
		if(Y>=(1<<i)){
			Y -= (1<<i);
			qwq.push_back(i);
		}
	}
	int cur = 0,sum = 0;
	for (auto i : v[X]){
		if(i<=cur) continue;
		int now = i;
		for (auto j : qwq) now = st[now][j];
		if(now==0) return false;
		cur = now,++sum;
		if(sum==k) return true;
	}
	return false;
}

signed main()
{
    FAST;
	cin >> n >> k >> V;
	for (int i=1;i<=n;i++){
		cin >> a[i];
		v[a[i]].push_back(i);
	}
	for (int i=n;i>=1;i--){
		st[i][0] = lst[a[i]+1];
		lst[a[i]] = i;
	}
	for (int j=1;j<=21;j++){
		for (int i=1;i<=n;i++){
			st[i][j] = st[st[i][j-1]][j-1];
		}
	}
	for (int x=1;x<=V;x++){
		if(ans[x-1]!=0) ans[x] = ans[x-1]-1;
		int p = 1;
		while(p){
			if(check(x,ans[x]+p)){
				ans[x] += p;
				p *= 2;
			}
			else p /= 2;
		}//这里是一种更快的二分
		cout << ans[x] << " ";
	}
	return 0;
}
```

---

## 作者：AxB_Thomas (赞：2)

# 一. 题面：[点这里](https://www.luogu.com.cn/problem/P12008)
# 二. 思路：
首先需要感谢 **良心WA题人** 巨佬提供的复杂度证明思路，好人一生平安。

首先考虑答案的性质，发现答案具备单调性，所以考虑二分答案 $m$ 。然后对于朴素的 check 你可以做到每一次都是 $O(n)$ 的。然后枚举每一个记忆的起始数字，总复杂度 $O(n^2\log n)$。

考虑优化，显然枚举每一个记忆起始数字这个部分是每一次的答案贡献，我们很难优化，那么考虑 check 的部分，思考具体的过程。每一次 check 我们都是扫一遍，遇到最近的 $x+1$ 就作为最后答案序列的一部分，这个贪心的正确性是显然的。然后你发现这就形成了一个跳跃的过程，那么我们考虑是否可以预处理维护。然后就发现这个其实是可以线性维护预处理的（细节看代码）。但是如果连续段很稠密，你发现复杂度还是会退化成朴素做法，但是因为形成了跳跃的过程，有经验的选手就会发现这显然是可以倍增的，所以搞一个倍增数组 $f_{i,j}$ ，意义不再阐述，而 $f_{i,0}$ 就是我们刚才预处理的东西。那么你发现我们现在就可以在 $O(\log n)$ 的复杂度下去处理上述贪心了。所以一次 check 的复杂度就变成了 $O(k\log n)$ 。具体的，你可以枚举每个起始值 $x$ 的位置，然后暴力往后跳。你发现枚举起始值 $x$ 的过程是均摊线性的。所以总时间复杂度由 枚举+二分+check 三部分组成，最终总时间复杂度为：$O(n\log^2n)$ 。

到目前为止，我们已经可以拿到 82pts 了，但是还可以更加优化。注意到一个性质，若起始值为 $x$ 的答案记作 $ans$ ，那么起始值为 $x+1$ 的答案至少为 $\max\{0,ans-1\}$ ，所以我们考虑维护一个双指针，左端点为 $x$ ，右端点为 $x+ans-1$ 。然后再去利用上述的 check 去做，这样的话就省去了二分的过程，效率会更优化，但是我们希望可以量化这个复杂度（再次感谢巨佬 **良心WA题人**）。和第一次的优化相仿的，我们不妨采取均摊复杂度分析。考虑双指针维护的某一个区间 $[l,r]$ ，我们记他们分别在原序列中的 $cnt$ 有一个比较显然的性质就是区间 $[l,r]$ 的出现次数一定不会超过 $\min\{cnt_l,cnt_r\}$ 然后你发现双指针的本质就是我们按照区间 $[l,r]$ 的出现次数扫那么也是均摊线性的，所以本质上我们就去掉了二分答案中的那一层 $\log$ 。

在最终实现上还有对代码运行速度的优化，所以建议读者阅读本人的代码以作参考。
# 三. Code:

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<vector>
inline int read() {
	int x=0,f=1;char ch=getchar();
	while(ch > '9' || ch < '0'){if(ch == '-'){f = -1;}ch = getchar();}
	while(ch >= '0'&&ch <= '9'){x = x * 10 + ch - 48; ch = getchar();}
	return x * f;
}

void write(int x) {
    if (x > 9) {
        write(x / 10);
    }
    putchar(x % 10 + 48);
}

const int N = 2e6 + 10,LOGN = 24;
std::vector<int> pos[N];
int n,k,V,f[N][LOGN],tmp[N],a[N],Log[N];

int retn_pos(int id,int v)
{
	if(id > n && v > V) return n + 1;
	return *std::upper_bound(pos[v].begin(),pos[v].end(),id);
}

int lowbit(int x){return x & (-x);}
bool check(int num,int m)
{
	--m;
	int ps = 0;
	int tp[21];
	ps = retn_pos(ps,num);
	int cnt = 0,j;
	while(m)
	{
		j = lowbit(m);
		m -= j;
		j = Log[j];
		ps = f[ps][j];
		tp[++cnt] = j;
		if(ps == n + 1) return false;
	}
	if(ps == n + 1) return false;
	
	for(int i = 1;i <= k - 1;++i)
	{
		ps = retn_pos(ps,num);
		for(int j = 1;j <= cnt;++j)
		{
			ps = f[ps][tp[j]];
			if(ps == n + 1) return false;
		}
		if(ps == n + 1) return false;
	}
	return true;
}

int main()
{
 	n = read(),k = read(),V = read();
 	for(int i = 2;i <= n;++i) Log[i] = Log[i >> 1] + 1;
 	for(int i = 1;i <= n;++i)
 	{
 		a[i] = read();
 		pos[a[i]].push_back(i);
	}
	for(int i = 1;i <= V;++i) pos[i].push_back(n + 1);
	
	for(int i = n;i >= 1;--i)
	{
		if(!tmp[a[i] + 1]) f[i][0] = n + 1;
		else f[i][0] = tmp[a[i] + 1];
		tmp[a[i]] = i;
	}
	
	f[n + 1][0] = n + 1;
	for(int j = 1;j <= 20;++j)
		for(int i = 1;i <= n + 1;++i)
			f[i][j] = f[f[i][j - 1]][j - 1];
	
	int ans = 0;
	for(int i = 1;i <= V;++i)
	{
		ans = std::max(0,ans - 1);
		while(check(i,ans + 1)) ++ans;
		write(ans);
		putchar(32);
	}
	return 0;
}
```

---

## 作者：modfish_ (赞：2)

## 思路
题意简单来说就是给定一个序列，对于每种值 $x$，求出最大的 $m$，满足 $\{x,x+1,\dots,x+m-1\}$ 复制 $k$ 次后是原序列的子序列。

考虑记 $f_i$ 表示 $i$ 后面第一个值为 $a_i+1$ 的位置，从后往前扫一遍容易维护。

接下来倍增地处理，记 $f_{i,j}$ 表示以 $i$ 开头的、连续递增的、长度为 $2^j+1$的子序列（即 $\{a_i,a_i+1,a_i+2,\dots,a_i+2^j\}$）的最后一位的位置的下标至少是多少。

不妨直接枚举每种值，设某种值所在的位置分别为 $c_1,c_2,\dots,c_p$，不妨倍增地求解答案。具体地，先尝试令答案加上 $2^{\lfloor\log_2 n\rfloor}$，检验是否可行，可行就令答案加上 $2^{\lfloor\log_2 n\rfloor}$，否则不变，再考虑令答案加上 $2^{\lfloor\log_2 n\rfloor-1}$，同样地检验，直到枚举至 $2^0$，就可以得到答案。

用预处理的 $f_{i,j}$ 容易维护每一个数向后跳若干步后到达的点，问题在于如何检验。注意到如果我们选择 $c_i$ 作为子序列的一部分，那么令此时 $c_i$ 所在连续序列的结尾为 $e_i$，于是 $[c_i,e_i]$ 之间不能存在别的子序列。更具体地，选了 $c_i$，那么所有 $c_j\in [c_i,e_i]$ 都不可以选。

考虑设 $dp_i$ 表示选择 $c_i$ 的情况下，并且已考虑 $c_i,c_{i+1},\dots,c_p$ 是否选择时，能选出的最多的子序列数量。容易得出转移：

$$dp_i=\max_{c_j>e_i} dp_j+1$$

使用一个指针即可线性维护转移点 $j$。

求出最大的 $dp_i$，若其大于等于 $k$，说明可行，否则不行。

这样就做完了。时间复杂度 $O(n\log n)$。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e6 + 5;

int pre[maxn], st[maxn][25];
int a[maxn];
vector<int> V[maxn];
int now[maxn], dp[maxn];
int n, k, v;

int solve(int c){
    int m = V[c].size();
    if(m < k) return 0;
    for(int i = 0; i < m; i ++) now[i] = V[c][i];
    int res = 0;
    for(int j = 21; j >= 0; j --){
        int p = m - 1;
        for(int i = m - 1; i >= 0; i --){
            if(!st[now[i]][j]){
                dp[i] = -1;
                continue;
            }
            while(p - 1 > i && st[now[i]][j] < V[c][p - 1]) p --;
            dp[i] = 1;
            if(st[now[i]][j] >= V[c][p] || dp[p] == -1) continue;
            dp[i] = dp[p] + 1;
        }
        int mx = 0;
        for(int i = 0; i < m; i ++) mx = max(mx, dp[i]);
        if(mx >= k){
            for(int i = 0; i < m; i ++) now[i] = st[now[i]][j];
            res += (1 << j);
        }
    }
    return res + 1;
}

int main(){
    scanf("%d %d %d", &n, &k, &v);
    for(int i = 1; i <= n; i ++) scanf("%d", &a[i]), V[a[i]].push_back(i);
    for(int i = n; i >= 1; i --){
        st[i][0] = pre[a[i] + 1];
        pre[a[i]] = i;
    }
    for(int j = 1; j <= 21; j ++) for(int i = 1; i <= n; i ++) st[i][j] = st[st[i][j - 1]][j - 1];
    for(int i = 1; i <= v; i ++) printf("%d ", solve(i));
    printf("\n");
    return 0;
}
```

---

## 作者：良心WA题人 (赞：2)

$O(n^2\log n)$ 的做法是容易的，考虑二分答案，则序列是确定的。预处理出来每个位置最近的某种数，每次贪心跳最近的一个看能不能跳完即可。

考虑优化。首先肯定是不能预处理每个位置最近的某种数的。改为动态把每个数出现了的位置塞到一个集合里每次 `lower_bound` 查询。注意到，对于枚举的每一个 $x$，他在序列中出现次数的和是均摊 $O(n)$ 的。那么，我们只要保证每次二分的检验都最多只会扫描序列中出现的所有 $x$ 时间复杂度就是 $O(n\log^2 n)$。不难发现，只需要对于每种 $m$，快速求出 $i$ 每种情况下向后跳值域连续的最近的 $m$ 个就行。此时，每个 $i$ 的后继都是最近的值为 $a_i+1$ 的位置，考虑倍增即可。需要注意，如果跳出序列了就要立刻退出，否则时间复杂退化为 $O(n\times k\log n)$。

这样还是无法通过。发现如果 $x=i$ 时答案为 $m$，则 $x=i+1$ 时答案至少为 $m-1$。则我们考虑按照类似的方法进行双指针。这样做每次的时间复杂度至多为 $\min(cnt_l,cnt_r)$。我们在每次移动左端点的时候认为本次计算了 $cnt_l$ 次，否则认为计算了 $cnt_r$ 次，这样的次数总和就是 $O(n)$ 的。但是这样计算一定不少于原本的情况，所以时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace fastio
{
    const int bufl=1<<20;
    const double base1[16]={1,1e-1,1e-2,1e-3,1e-4,1e-5,1e-6,1e-7,1e-8,1e-9,1e-10,1e-11,1e-12,1e-13,1e-14,1e-15};
    const double base2[16]={1,1e1,1e2,1e3,1e4,1e5,1e6,1e7,1e8,1e9,1e10,1e11,1e12,1e13,1e14,1e15};
    struct IN{
        FILE *IT;char ibuf[bufl],*is=ibuf,*it=ibuf;
        IN(){IT=stdin;}IN(char *a){IT=fopen(a,"r");}
        inline char getChar(){if(is==it){it=(is=ibuf)+fread(ibuf,1,bufl,IT);if(is==it)return EOF;}return *is++;}
        template<typename Temp>inline void getInt(Temp &a){a=0;int b=0,c=getChar();while(c<48||c>57)b^=(c==45),c=getChar();while(c>=48&&c<=57)a=(a<<1)+(a<<3)+c-48,c=getChar();if(b)a=-a;}
        template<typename Temp>inline void getDouble(Temp &a){a=0;int b=0,c=getChar(),d=0;__int128 e=0,f=0;while(c<48||c>57)b^=(c==45),c=getChar();while(c>=48&&c<=57)e=(e<<1)+(e<<3)+c-48,c=getChar();if(c==46){c=getChar();while(c>=48&&c<=57)d++,f=(f<<1)+(f<<3)+c-48,c=getChar();}a=e+base1[d]*f;if(b)a=-a;}
        IN& operator>>(char &a){a=getChar();return *this;}
        IN& operator>>(char *a){do{*a=getChar();}while(*a<=32);while(*a>32)*++a=getChar();*a=0;return *this;}
        IN& operator>>(string &a){char b=getChar();while(b<=32)b=getChar();while(b>32)a+=b,b=getChar();return *this;}
        IN& operator>>(int &a){getInt(a);return *this;}
        IN& operator>>(long long &a){getInt(a);return *this;}
        IN& operator>>(__int128 &a){getInt(a);return *this;}
        IN& operator>>(float &a){getDouble(a);return *this;}
        IN& operator>>(double &a){getDouble(a);return *this;}
        IN& operator>>(long double &a){getDouble(a);return *this;}
    };
    struct OUT{
        FILE *IT;char obuf[bufl],*os=obuf,*ot=obuf+bufl;int Eps;long double Acc;
        OUT(){IT=stdout,Eps=6,Acc=1e-6;}OUT(char *a){IT=fopen(a,"w"),Eps=6,Acc=1e-6;}
        inline void ChangEps(int x=6){Eps=x;}
        inline void flush(){fwrite(obuf,1,os-obuf,IT);os=obuf;}
        inline void putChar(int a){*os++=a;if(os==ot)flush();}
        template<typename Temp>inline void putInt(Temp a){if(a<0){putChar(45);a=-a;}if(a<10){putChar(a+48);return;}putInt(a/10);putChar(a%10+48);}
        template<typename Temp>inline void putLeading(Temp a,int b){if(!b)return;putLeading(a/10,b-1);putChar(a%10+48);}
        template<typename Temp>inline void putDouble(Temp a){if(a<0){putChar(45);a=-a;}__int128 b=a;putInt(b);a-=b;a*=base2[Eps];b=a+Acc;putChar(46);putLeading(b,Eps);}
        OUT& operator<<(char a){putChar(a);return *this;}
        OUT& operator<<(char *a){while(*a>32)putChar(*a++);return *this;}
        OUT& operator<<(string a){for(auto c:a)putChar(c);return *this;}
        OUT& operator<<(int a){putInt(a);return *this;}
        OUT& operator<<(long long a){putInt(a);return *this;}
        OUT& operator<<(__int128 a){putInt(a);return *this;}
        OUT& operator<<(float a){putDouble(a);return *this;}
        OUT& operator<<(double a){putDouble(a);return *this;}
        OUT& operator<<(long double a){putDouble(a);return *this;}
        ~OUT(){flush();}
    };
}
using fastio::IN;
using fastio::OUT;
IN fin;
OUT fout;
const int NN=2e6+4;
int a[NN],up[24][NN],n,m,V;
vector<int>p[NN];
int find_ne(int x,int v)
{
	if(v>V||x>n)
		return n+1;
	return *upper_bound(p[v].begin(),p[v].end(),x);
}
bool check(int x,int l)
{
	l--;
	int u=0;
	for(int i=1;i<=m;i++)
	{
		u=find_ne(u,x);
		for(int j=0;j<=20;j++)
			if(l>>j&1)
				u=up[j][u];
		if(u==n+1)
		    return false;
	}
	return true;
}
int main()
{
	fin>>n>>m>>V;
	for(int i=1;i<=n;i++)
	{
		fin>>a[i];
		p[a[i]].push_back(i);
	}
	for(int i=1;i<=V;i++)
		p[i].push_back(n+1);
	for(int i=1;i<=n;i++)
		up[0][i]=find_ne(i,a[i]+1);
	up[0][n+1]=n+1;
	for(int i=1;i<=20;i++)
		for(int j=1;j<=n+1;j++)
			up[i][j]=up[i-1][up[i-1][j]];
	for(int i=1,w=0;i<=V;i++)
	{
		w=max(0,w-1);
		while(check(i,w+1))
			w++;
		fout<<w<<' ';
	}
	return 0;
}
```

---

## 作者：ln001 (赞：1)

## 题意
给定数 $k$ 和长度为 $n$ 值域 $[1, m]$ 的序列 $a_i$，对于每个 $ask \in [1, m]$，求最大的 $len$ 满足序列 $b \times k$  是 $a$ 的**子序列**，其中 $b_i = ask + i - 1(i \in [1, len])$，$b \times k$ 表示将 $k$ 个序列 $b$ 头尾相接组成的新序列，无解时 $len \gets 0$。

## 思路

对于最大化问题，不难想到二分求解，对每一组询问，二分 $len$，并 $O(n)$ 扫描序列检查答案的正确性。时间复杂度 $O(n ^ 2 \log n)$。

对二分中的 check 进行优化，令 $next_i$ 表示 $i$ 后面第一个值为 $a_i + 1$ 的位置的下标，每次 check 时不断跳 $next$ 即可，时间复杂度并没有很大的进步。发现 $next$ 可以倍增优化以实现快速向后跳，为了方便计算时间复杂度，check 在循环进行倍增时改为循环遍历提前预处理好的每个值对应的下标集合并记录当前跳到的位置，由于下标集合的大小之和为 $n$ 所以对所有 check 函数此处的循环次数的和为 $O(n\log n)$，在循环中我们倍增向后跳的单次复杂度 $O(\log n)$，可分析得到目前时间复杂度 $O(n\log^2 n)$。

令 $ans_i$ 表示对于 $ask = i$ 询问的答案，check 函数内的优化貌似已经没有前途了，考虑对 check 外部进行优化。感性思考可以想到除无解外 $ans_{i - 1} \approx ans_i$ 更进一步得到 $ans_{i - 1} - 1 \approx ans_i$，再进一步的由于 $ask$ 改变导致答案序列左端点位置增多，除继承上一次答案序列外还会产生一些新的答案序列，所以得到 $ans_{i-  1} - 1 \leq ans_i$，将其设为二分边界可以获得更优复杂度，另外我们发现由于该边界的设定，用指针代替二分是可行的。若指针不可向左移动，则总时间复杂度 $O(n)$，但受答案下界中 $-1$ 的影响，每次指针可能向左移动 $1$ 次，则总向左移动次数不超过 $O(n)$ 即算法的总时间复杂度 $O(n\log n)$。

---

## 作者：_lqs_ (赞：1)

P12008。

只写了这题，然而卡了半小时才过。

首先考虑一个暴力：枚举 $i$，那么这个答案显然可以二分，再暴力求是否存在 $k$ 组循环。这个做法是 $O(n^2 \log n)$ 的，过不去。

我们考虑在 check 这部分优化。设 check 的区间是 $[x,y]$，暴力是为了找是否存在按顺序的 $k$ 组区间，那么容易想到 $[x,y]$ 出现次数均 $\ge k$ 是一个必要条件，然而没什么用。

难点在于**按顺序**这个点。我们想到类似链表的思路记录 $a_{i}$ 的下一个点 $a_{i}+1$ 的最近位置。然后我们暴力枚举 $k$ 组区间可以变成暴力跳 $nxt$ 数组。

然后你注意到这个暴力跳的过程完全可以倍增优化，于是你找一组 $[x,y]$ 的时间复杂度优化到一只 $\log$，具体地，枚举每一个 $x$ 的位置，再倍增跳。枚举 $x$ 均摊是线性的。

视 $n,V$ 同阶，于是我们有了一个 82 pts 的做法。我们考虑再优化。

优化 1：对于二分部分，假设当前 $i$ 的答案右端点为 $ans$，那么 $i+1$ 的答案右端点也至少为 $ans$，则我们可以压缩二分的左边界。

优化 2：若一个数出现次数小于 $k$ 则一定无效，则可根据这个压缩二分的右边界。

优化 3：想想发现有相当一部分时间浪费在了倍增中枚举无用的跳点，实际有用的跳点只是二进制下所有 1 的位置，由此我们想到 lowbit 优化倍增。

时间复杂度 $O(n \log^2 n)$。至此已经是可以过的了。

然而有可能会被卡掉，其实我们可以发现，如果思考对象是判断区间是否合法而不是区间长度的话，答案要么为 $0$，要么区间右端点单调不降。简单而言，如果 $[x,y]$ 是一个合法区间，那么 $[x+1,y]$ 也必然合法，这个是显然的。所以每次 check 只需往右边扩展即可。这样可以做到 $O(n \log n)$。

下面是 $O(n \log^2 n)$ 的写法。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 2000005
#define pb push_back
#define lowbit(x) x&(-x)
int n,m,i,j,ans,k,v,b[N],cnt[N],sv,a[N],mp[N],w[N],f[N][25],flag[N],cf[N],Log[N],lst[N];
std::vector<int>G[N];
int l,r,mid,pw,len,res,p,gg;
bool check(int x,int y){
	len=0;
	for(int z:G[y]) w[z]=++len;
	for(int i=1;i<=len;i++) flag[i]=0,cf[i]=0;
    int mx=0;
	for(int z:G[x]){
        if(z<=mx) continue;
		p=z,gg=y-x;
        while(gg){
            p=f[p][Log[lowbit(gg)]];
            gg-=lowbit(gg);
        }
		if(a[p]==y) mx=p,flag[w[p]]=1,++cf[w[p]+1];
	}
	for(int i=1;i<=len;i++){
		cf[i]+=cf[i-1];
		if(flag[i] && cf[i]+1>=k) return true;
	}
	return false;
}
int main(){
	scanf("%d%d%d",&n,&k,&v);
	for(i=2;i<=n;i++) Log[i]=Log[i>>1]+1;
	for(i=1;i<=n;i++) scanf("%d",&a[i]);
	for(i=1;i<=n;i++) G[a[i]].pb(i);
	for(i=n;i>=1;i--) f[i][0]=mp[a[i]+1],mp[a[i]]=i,++cnt[a[i]];
	for(i=1;i<=n;i++) if(cnt[a[i]]<k) b[++sv]=a[i],cnt[a[i]]=-1;
	b[++sv]=v+1;
	sort(b+1,b+1+sv);
	for(j=1;j<=20;j++){
		for(i=1;i+(1<<j)-1<=n;i++) f[i][j]=f[f[i][j-1]][j-1];
	}
	for(i=1;i<=v;i++){
		pw=lower_bound(b+1,b+1+sv,i)-b;
		l=max(i,lst[i-1]),r=b[pw]-1,res=0;
		while(l<=r){
			mid=(l+r)>>1;
			if(check(i,mid)) res=mid,l=mid+1;
			else r=mid-1;
		}
		if(!res) printf("%d ",res);
		else printf("%d ",res-i+1);
		lst[i]=res;
	}
	return 0;
}
```

---

## 作者：Lele_Programmer (赞：0)

# P12008 题解

赛时想到或许是 $\mathcal{O}(n \log n)$ 做法，但想来想去没想到倍增。

参考了其它题解的一些内容。

## 思路

从后往前扫一遍，对于 $i$，可以得到下一个 $i+1$ 的位置，于是通过倍增可以初始化出每一个 $i$ 分别到下一个 $i+1, i+2, i+4, \cdots$ 的位置。

把每个相同数字出现的位置单独拆开，假设某个数字出现的位置，从小到大下标分别为 $a,b,c,d,e,f,\cdots$，让其作为基准记忆 $x$，再假设度过了 $m+1$ 天，也就是对于每一个 $x$ 的起点，要往后走 $m$ 个数（不算自己）。从 $a$ 加上 $m$ 个数得到的结束点的位置，在这个位置之前的数字 $x$ 就不能接下去了，因为会出现交叉，形如 $2,3,4,2,5,3,4,5,\cdots$，所以对于每一个点，先求得在它前面的它能够接上去的链，这个值是单调递增的，所以从左到右枚举的时候，可以一边更新这个值。能够接上去的链，当然选越靠后的越好。

## 代码

```cpp
const int N=2000005;
const int M=25;

int n,k,v;
int a[N];
vector<int> vec[N];
int las[N];
int f[N][M];
int g[N],bk[N];
int s[N];

bool check(int x) {
    if (!g[1]) return false;
    int m=vec[x].size()-1;
    int j=1;
    s[1]=1;
    int mx=1;
    _rep(i,2,m) {
        if (!g[i]) break;
        if (g[j]>vec[x][i]) {
            s[i]=1;
            continue;
        }
        while (j+1<i && g[j+1]<vec[x][i] && g[j+1]) ++j;
        s[i]=s[j]+1;
        mx=max(mx,s[i]);
    }
    return mx>=k;
}

int main() {
    read(n),read(k),read(v);
    _rep(i,1,N-1) vec[i].emplace_back(-1);
    _rep(i,1,n) read(a[i]),vec[a[i]].emplace_back(i);
    _rrep(i,n,1) {
        f[i][0]=las[a[i]+1],las[a[i]]=i;
        _rep(j,1,M-1) f[i][j]=f[f[i][j-1]][j-1];
    }
    // puts("TEST:");
    // _rep(i,1,n) _rep(j,0,M-1) if (f[i][j]) printf("f[%d][%d] = %d\n",i,j,f[i][j]);
    _rep(x,1,v) {
        if (vec[x].size()-1<k) {
            writesp(0);
            continue;
        }
        int m=vec[x].size()-1;
        _rep(i,1,m) g[i]=vec[x][i];
        int ans=0;
        _rrep(p,M-1,0) {
            _rep(i,1,m) bk[i]=g[i];
            _rep(i,1,m) g[i]=f[g[i]][p];
            // if (x==3) {
            //     printf("TEST: %d %d: ",x,ans+p);
                // printf("g: ");
                // _rep(i,1,m) writesp(g[i]); putchar(10);
                // printf("bk: "); _rep(i,1,m) writesp(bk[i]); putchar(10);
            // }
            if (check(x)) ans+=(1<<p);
            else _rep(i,1,m) g[i]=bk[i];
        }
        writesp(ans+1);
    }
    return 0;
}
```

---

