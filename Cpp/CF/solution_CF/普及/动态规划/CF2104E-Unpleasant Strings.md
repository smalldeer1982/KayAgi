# Unpleasant Strings

## 题目描述

我们称一个字母是允许的，当且仅当它是小写字母且属于拉丁字母表的前 $k$ 个字母。

给定一个长度为 $n$ 的字符串 $s$，它仅由允许的字母组成。

我们称一个字符串 $t$ 是愉快的，当且仅当 $t$ 是 $s$ 的子序列。

给定 $q$ 个字符串 $t_1, t_2, \dots, t_q$，它们都仅由允许的字母组成。对于每个字符串 $t_i$，计算最少需要在它的右侧追加多少个允许的字母，才能使其不再愉快。

序列 $t$ 是序列 $s$ 的子序列，当且仅当 $t$ 可以通过从 $s$ 中删除若干个（可以是零个或全部）任意位置的元素得到。

## 说明/提示

在第一个样例中：

1. 字符串 cc 已经是不愉快的，因此不需要追加任何字母；
2. bcb 是愉快的，因此至少需要在右侧追加一个字母：bcba 仍然会保持愉快，但 bcbb 和 bcbc 是不愉快的；
3. 对于 b，至少需要追加两个字母，因为 ba、bb 和 bc 都是愉快的。例如，我们可以得到一个不愉快的字符串 bbb。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
7 3
abacaba
3
cc
bcb
b```

### 输出

```
0
1
2```

## 样例 #2

### 输入

```
5 1
aaaaa
6
a
aa
aaa
aaaa
aaaaa
aaaaaa```

### 输出

```
5
4
3
2
1
0```

# 题解

## 作者：Eous (赞：7)

看到 $\sum|t_i| \le 1 \times 10^6$，看能不能搞出一种 $O(\sum|t_i|)$ 的算法。

我们想到预处理 $s$ 串上每个下标 $i$ 的 $ans_i$，表示以 $i$ 结尾的子序列最少还要加多少个字符才能不再成为悦耳字符串。

考虑如何预处理。$i$ 从后往前枚举，记录一个 $lst_i$ 表示字符 $i$ 最后出现的地方。我们枚举每个字符。有显然的转移：$ans_i = \min\{ans_{lst_i} + 1\}$，表示在这个点后面接每个字符的方案。$lst$ 初始全为 $n + 1$，且 $ans_{n + 1} = 0$。再记录一个 $son_{i,j}$，每次都把 $lst$ 给 `memcpy` 进 $son_i$。转移完了再更新 $lst$。最后把 $lst$ `memcpy` 进 $son_0$。

考虑如何处理询问。就像字典树一样，我们记录一个 $rt$ 表示当前跳到了 $rt$ 这个点。枚举 $t$ 里每个字符 $t_i$，每次跳到 $son_{rt,t_i}$。如果说跳着跳着直接跳到 $n + 1$ 了，就说明它本就不是悦耳字符串，$ans$ 置为 $0$ 并 `break`。反之如果跳到了 $t$ 的结尾了都没跳出去，就说明这是一个悦耳字符串，答案即为 $ans_{rt}$。

code:

```cpp
#include<bits/extc++.h>
#define inf 0x3f3f3f3f
using namespace std;
const int maxn = 1e6 + 5;
int n,k,q;
char t[maxn],s[maxn];
int son[maxn][26],ans[maxn];
signed main()
{
    scanf("%d%d%s",&n,&k,t + 1);
    fill(son[0],son[0] + k,n + 1);// 这里直接把 son[0] 当 lst 用了
    fill(ans + 1,ans + n + 1,inf);// ans 初始化 inf
    for (int i = n; i >= 1; i--)
    {
        memcpy(son[i],son[0],sizeof(int) * k);// 把 lst memcpy 进 son[i]
        for (int j = 0; j < k; j++)
            ans[i] = min(ans[i],ans[son[0][j]] + 1);// 转移
        son[0][t[i] - 'a'] = i;// 更新 lst
    }
    scanf("%d",&q);
    while (q--)
    {
        scanf("%s",s + 1);
        int rt = 0,len = strlen(s + 1);
        for (int i = 1; i <= len && rt <= n; i++)
            rt = son[rt][s[i] - 'a'];// 每次跳，如果跳出去了就说明本就不是悦耳字符串。
        printf("%d\n",ans[rt]);
    }
    return 0;
}
```

---

## 作者：_O_v_O_ (赞：2)

你家 edu E 就这？？？？？？？？？？

本文令 $i$ 号字符为字母表中第 $i$ 的小写字母。

考虑贪心。

我们设 $nxt_{i,j}$ 为 $i$ 后面，第一次出现 $j$ 号字符的位置，若没有，则 $nxt_{i,j}$ 为 $n+1$。

那么我们初始维护一个变量 $u=0$，遍历 $t$，每次令 $u\leftarrow nxt_{u,t_i}$，那么最后 $u$ 就是 $t$ 作为子序列出现在 $s$ 中第一个子序列的末尾的下标。

那么我们需要求出最短的序列 $t_0$ 使得 $t_0$ 未出现 $u$ 后面。

这个是很简单的，我们拿一个 `std::set` 维护一下 $u$ 后面总共有多少个出现了多少轮 $1\sim k$ 号字符，最终答案就是这个。

---

## 作者：ZhaoV1 (赞：1)

首先思考对于所给的 $t$ 字符串，如果它是 $s$ 字符串的子序列，那么需要几次操作才能使他不再是 $s$ 的子序列。经过模拟探索得知，先消去 $t$ 的最后一个字符在 $s$ 字符串中出现的尽可能最早的位置左边的一切字符，剩余该位置右边的所有字符。对于剩余的字符，运用贪心的思维，每 $1$ 到 $k$ 的字符出现过最少一次后，操作次数加 $1$，这一操作可以提前预处理出来到 $dp$ 数组中。

除此之外，还需检查给定 $t$ 字符串是否是 $s$ 字符串的子序列，于是考虑用 $ind$ 数组存放每个字符在 $s$ 中出现的位置，如 $ind_{i,j}$ 表示字符第 $j$ 个字符 $i$ 出现在的下标。由此可以遍历 $t$ 做对字符 $t_i$ 的位置做二分操作，保证前一个字符 $t_{i-1}$ 的位置在 $t_i$ 左侧。由此可以得到最后一个位置，配合 $dp$ 数组得到答案。若非子序列输出 $0$。

Code
---


```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
#define INF 0x3f3f3f3f3f3f3f3f
const int N = 2e5+5;
const int M = 1e6+5;
const int MOD = 1e9+7;
int n,k,q;
string s;
string a[N];
int dp[M], b[30], ind[30][M], cnt[30];
int find(int last,char x){
    int num = x-'a'+1;
    int left = 0,right = cnt[num]+1;
    while(left + 1 < right){
        int mid = (left + right) >> 1;
        if(ind[num][mid] > last) right = mid;
        else left = mid;
    }
    if(right == cnt[num]+1) return -1;
    else return ind[num][right];
}
void solve(){
	cin >> n >> k;
    cin >> s;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=26;j++){
            if(s[i-1] == (char)(j-1+'a')) 
                ind[s[i-1]-'a'+1][++cnt[s[i-1]-'a'+1]] = i-1;
        }
    }
    dp[n] = 0;
    for(int i=1;i<=k;i++) b[i] = n;
    for(int i=n-1;i>=0;i--){
        int Max = 0;
        for(int j=1;j<=k;j++){
            Max = max(Max,b[j]);
        }
        dp[i] = dp[Max]+1;
        b[s[i]-'a'+1] = i;
    }
    cin >> q;
    for(int i=1;i<=q;i++){
        cin >> a[i];
        bool flag = false;
        int last = -1;
        for(int j=0;j<(int)a[i].size();j++){
            int index = find(last,a[i][j]);
            if(index == -1){//找不到，已经不是子序列了
                flag = true;
                cout << 0 << '\n';
                break;
            }else last = index;
        }
        if(!flag) cout << dp[last] << '\n';//是子序列
    }
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int _;
	_ = 1;
	while(_--){
		solve();
	}
	return 0;
}
```

---

## 作者：znzryb (赞：1)

## 思路讲解
首先贪心地想，我们在每个位置上总归想跳的最远，且在每个位置上都跳的最远，得到的一定是最少跳跃次数的。

那么这个每个位置上通过加一个字母能够一次跳到的最远位置怎么得到的那？其实就是所有合法字母中上一次出现的位置最远的字母的位置（如果有一个合法字母前面没出现过，那我们就认为他直接跳出去结束了）。

```cpp
	ROF(i,N-1,0){
		FOR(j,0,K-1){
			if(Pos[j].empty()){
				JumpFar[i]=N;
				JumpCh[i][j]=N;
			}else{
				JumpFar[i]=max(Pos[j].back(),JumpFar[i]);
				JumpCh[i][j]=Pos[j].back();
			}
		}
		Pos[S[i]-'a'].pb(i);
	}
```
然后知道了在这个位置上最远能跳多远，那么我们知道最多要跳多少次呢？可以通过记忆化搜索。

```cpp
ll dfs(ll x){
	if(x>=N) return 0;
	if(dp[x]!=0) return dp[x];
	return dfs(JumpFar[x])+1;
}

	ROF(i,N-1,0){
		dp[i]=dfs(i);
	}
```

最后这个串需要用多少位原串需要跳跃处理，否则会 TLE，因为最坏 $O(NQ)$ 时间复杂度。

```cpp
// idxs是原串的下标，idx是这个输入进来的串的下标
		while(idxs<N){
			if(idx>=SZ(s)) {
				break;
			}
			// assert(idx<SZ(s));
			if(s[idx]==S[idxs]){
				bp=idxs;
				++idx;
				idxs=JumpCh[idxs][s[idx]-'a'];
			}else{
				idxs=JumpCh[idxs][s[idx]-'a'];
			}
		}
```

## AC 代码
https://codeforces.com/contest/2104/submission/317799371
```cpp
// Problem: E. Unpleasant Strings
// Contest: Codeforces - Educational Codeforces Round 178 (Rated for Div. 2)
// URL: https://codeforces.com/contest/2104/problem/E
// Memory Limit: 512 MB
// Time Limit: 2000 ms
// by znzryb
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define fi first
#define se second
#define pb push_back
#define SZ(a) ((int) a.size())
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define ROF(i, a, b) for (int i = (a); i >= (b); --i)

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef __int128 i128;
typedef pair<ll,ll> pll;
typedef array<ll,3> arr;
typedef double DB;
typedef pair<DB,DB> pdd;
typedef pair<ll,bool> plb;
constexpr ll MAXN=static_cast<ll>(1e6)+10,INF=static_cast<ll>(5e18)+3;
constexpr ll mod=static_cast<ll>(1e9)+7;

ll N,M,Q,K,T;
char S[MAXN];
// ll Cnt[MAXN][35];
ll JumpFar[MAXN];
ll JumpCh[MAXN][35];
ll dp[MAXN];
vector<ll> Pos[35];

ll dfs(ll x){
	if(x>=N) return 0;
	if(dp[x]!=0) return dp[x];
	return dfs(JumpFar[x])+1;
}


inline void solve(){
	cin>>N>>K;
	FOR(i,0,N-1){
		cin>>S[i];
		// ++Cnt[S[i]-'a'];
	}
	// ROF(i,N-1,0){
		// FOR(j,0,30){
			// Cnt[i][j]=Cnt[i+1][j];
		// }
		// ++Cnt[i][S[i-1]-'a'];
	// }
	
	// JumpFar[N-1]=1;
	// Pos[S[N-1]-'a'].pb(N-1);
	ROF(i,N-1,0){
		FOR(j,0,K-1){
			if(Pos[j].empty()){
				JumpFar[i]=N;
				JumpCh[i][j]=N;
			}else{
				JumpFar[i]=max(Pos[j].back(),JumpFar[i]);
				JumpCh[i][j]=Pos[j].back();
			}
		}
		Pos[S[i]-'a'].pb(i);
	}
	ROF(i,N-1,0){
		dp[i]=dfs(i);
// #ifdef LOCAL
    // cerr << "i:"<<i<<" dp:"<<dp[i] << '\n';
// #endif
	}
	
// #ifdef LOCAL
    // FOR(i,0,N-1){
    	// cerr<<dp[i]<<" ";
    // }
    // cerr<<"\n";
// #endif

	cin>>Q;
	while(Q--){
		// 要在末尾加几个合法字母，才能让这个字符串s不是S的子集
		string s;
		cin>>s;
		if(SZ(s)>N){
			cout<<0<<"\n";
			continue;
		}
		ll idx=0,idxs=0,bp=-INF;
		while(idxs<N){
			if(idx>=SZ(s)) {
				break;
			}
			// assert(idx<SZ(s));
			if(s[idx]==S[idxs]){
				bp=idxs;
				++idx;
				idxs=JumpCh[idxs][s[idx]-'a'];
			}else{
				idxs=JumpCh[idxs][s[idx]-'a'];
			}
		}
		if(idx<SZ(s)){
			cout<<"0\n";
			continue;
		}
		
// #ifdef LOCAL
    // cerr << "Q: "<<Q<<" bp:"<<bp<<" idx:"<<idx << '\n';
// #endif

		cout<<dp[bp]<<"\n";
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	// cin>>T;
	// while(T--){
		// solve();
	// }
	solve();
	return 0;
}
/*
AC
https://codeforces.com/contest/2104/submission/317799371
*/
```

---

## 作者：zhangli828 (赞：0)

## 题目思路
你可以在 $t$ 后面加多少个字符使得 $t$ 不再为 $t$ 的子序列。
## 题目解法
我们可以先处理每一个字符后面一个字符在什么位置，这样方便处理出 $t$ 最后的字符的位置。

如果直接暴力处理后面要加多久个字符串的话会超时（本人因为犯了这处错误，在比赛是吃了罚时），所以可以从后往前预处理要加多久个字符串才不是子序列。
## 题目代码
```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int kMaxN = 1e6 + 10;

int p[kMaxN][26], st[kMaxN], cnt[26], n, k, q;
string s, t;

signed main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n >> k >> s, st[n - 1] = 1, cnt[s[n - 1] - 'a'] = 1;
  for (int j = 0; j < k; j++) {
    for (int i = n - 1, w = -1; i >= 0; i--) {
      p[i][j] = w, (s[i] - 'a' == j) && (w = i);
    }
  }
  for (int i = n - 2; i >= 0; i--) {
    int flag = 0;
    for (int j = 0; j < k; j++) {
      flag |= cnt[j] == 0;
    }
    if (flag) {
      st[i] = st[i + 1];
    } else {
      st[i] = st[i + 1] + 1, memset(cnt, 0, sizeof(cnt));
    }
    cnt[s[i] - 'a'] = 1;
  }
  for (cin >> q; q--;) {
    cin >> t;
    int w, i;
    for (i = 1, w = s[0] == t[0] ? 0 : p[0][t[0] - 'a']; i < t.size() && w >= 0; i++) {
      w = p[w][t[i] - 'a'];
    }
    if (w < 0) {
      cout << "0\n";
      continue;
    }
    cout << st[w] << '\n';
  }
  return 0;
}
```

---

