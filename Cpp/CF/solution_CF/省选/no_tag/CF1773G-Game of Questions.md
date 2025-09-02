# Game of Questions

## 题目描述

Genie 正在参加一个问答比赛。比赛共 $n$ 题，有 $m$ 个参赛者（Genie 为 $1$ 号参赛者）。

比赛的形式如下：先将 $n$ 道题随机排序（即每个排列出现的概率都是 $\dfrac{1}{n!}$），然后按排列的顺序会依次问出这 $n$ 个问题。问一个问题时，若所有人都会或所有人都不会则无事发生，否则不会的人会被淘汰。在 $n$ 个问题都被问完之后，未被淘汰的人就都赢得胜利。

现在给出每个人是否会每道题，请求出 Genie 获胜的概率。

## 说明/提示

样例 $1$ 中，只有一个问题，故问题的顺序只有一种可能。问这个问题后第三、五名参赛者会被淘汰，Genie 和第二、四名选手一起获得胜利，故 Genie 获胜的概率为 $1$。

样例 $2$ 中，不管问题以哪种顺序问出，问的第一个问题会淘汰一个人，问的第二个问题又会淘汰一个人，剩下那个人获胜。则 Genie 获胜的概率等于第一个问题被第三个问出的概率，即 $\frac{1}{3}$。

## 样例 #1

### 输入

```
1 5
11010```

### 输出

```
1.0000000000000000```

## 样例 #2

### 输入

```
3 3
011
101
110```

### 输出

```
0.3333333333333333```

## 样例 #3

### 输入

```
6 4
1011
0110
1111
0110
0000
1101```

### 输出

```
0.1666666666666667```

# 题解

## 作者：Alex_Wei (赞：8)

随着游戏进行，留在场上的人会越来越少，这提供了自然的 DP 转移方向：**枚举子集**。

设 $f_S$ 表示任意时刻恰有集合 $S$ 的人留在场上的概率。对于每道题目 $s_i$，假设它可以第二次被抽到，我们发现它不产生任何影响。因此，转移时，求出 $c$ 表示使得 $S$ 改变的题目数量，即所有使得 $s_i\cap S\neq \varnothing, S$ 的 $s_i$，则这些题目在变成 $S$ 之前一定没有被抽到过，否则剩下的人就不是 $S$ 了。

若 $c = 0$，则 $f_S$ 表示最终结果有 $f_S$ 的概率是 $S$。否则 $S$ 一定会变得更小：枚举第一个使得 $S$ 减小的 $s_j$，因为它在所有 $s_i$ 中第一次出现的概率为 $\frac 1 c$，所以 $\frac {f_S} {c}\to f_{S\cap S_i}$。

注意 $s_j$ 是没有 $S$ 的子集限制的，所以时间复杂度为 $\mathcal{O}(4 ^ n)$，无法接受。

设 $g_{S, T}$ 表示使得 $s_i\cap S = T$ 的 $s_i$ 的数量，则有转移 $g_{S, T} = g_{S \cup \{p\}, T} + g_{S\cup \{p\}, T\cup \{p\}}$，其中 $p$ 是任意不在 $S$ 中的元素。在 $\mathcal{O}(3 ^ n)$ 的时间内求出所有 $g_{S, T}$。

易知 $c = \sum_{T\neq \varnothing, S} g_{S, T}$，转移时直接枚举 $T\neq \varnothing, S$，则 $\frac {f_S g_{S, T}} {c}\to f_T$。

综上，时空复杂度均为 $\mathcal{O}(3 ^ n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1 << 17;
int n, m, c[N], p[17], lab[N], K[N];
double f[N], ans;
vector<int> s[N];

int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  #ifdef ALEX_WEI
    FILE* IN = freopen("1.in", "r", stdin);
    FILE* OUT = freopen("1.out", "w", stdout);
  #endif
  cin >> n >> m;
  for(int i = 1; i <= n; i++) {
    int S = 0;
    for(int j = 0; j < m; j++) {
      char s;
      cin >> s;
      if(s == '1') S |= 1 << j;
    }
    c[S]++;
  }

  f[(1 << m) - 1] = 1;
  for(int i = (1 << m) - 1; i; i--) {
    if(i & 1 ^ 1) continue;

    int ppc = 0;
    for(int j = 0; j < m; j++) if(i >> j & 1) p[j] = ppc++;
    s[i].resize(1 << ppc), lab[0] = 0;
    for(int _ = (i - 1) & i; ; _ = (_ - 1) & i) {
      int S = i ^ _, low = 31 - __builtin_clz(S & -S);
      lab[S] = lab[S ^ (1 << low)] | (1 << p[low]);
      K[lab[S]] = S;
      if(!_) break;
    }

    int low = 31 - __builtin_clz((~i) & -(~i));
    int _i = i ^ (1 << low);
    for(int j = 0; j < 1 << ppc; j++) {
      if(i + 1 == (1 << m)) {
        s[i][j] = c[j];
        continue;
      }
      int T = (j & ((1 << low) - 1)) | ((j >> low) << low + 1);
      s[i][j] = s[_i][T] + s[_i][T | (1 << low)];
    }

    int sum = 0;
    for(int j = 1; j + 1 < 1 << ppc; j++) sum += s[i][j];
    if(!sum) ans += f[i];
    else {
      double pro = f[i] / sum;
      for(int j = 1; j + 1 < 1 << ppc; j++) f[K[j]] += s[i][j] * pro;
    }
  }
  printf("%.12lf\n", ans);
  return 0;
}
/*
g++ G.cpp -o G -std=c++14 -O2 -DALEX_WEI
*/
```

---

## 作者：hhhqx (赞：5)

模拟赛中的题是求排列数，不过改为求排列数是纯诈骗，需要从求概率的角度来看这题。

先来考虑 $O(3^m)$ 的做法：

- ~~**这一部分去看其他题解可能更好**~~
- 首先注意到一个题目第二次考不会影响当前集合。
- $dp_S$ 表示集合 $S$ 中的人都活着（且其他人死了）的概率。
- 统计可以将 $S$ 改变为 $T$ 的题目数量 $c$。（满足 $T \ne S$ 且 $T \ne \varnothing$）
- 然后依次转移，转移到 $T$ 的概率就是 $dp_S$ 乘可以转移到 $T$ 的题目数，再除以 $c$。
- 这样正推求概率 dp 是没有问题的，而且 $T \ne S$ 且 $T \ne \varnothing$ 所以是有单调性的，且所有都会到达最终状态。
- 因为要枚举子集，所以复杂度 $O(3^m)$。

考虑 $O(m^2 2^m)$ 的做法。

- 改写一下转移，设 $g_T$ 表示 $T$ 在 $n$ 个集合中的出现次数少。
	- $\frac{dp_S}{c_S} \times g_T \to dp_{S \cap T}$（要求 $0 < |S \cap T| < |S|$）。集合 $T$ 不再是目标状态了，是转移。
- 发现实际上 $0 < |S \cap T|$ 这个限制实际是不需要的，因为 $dp_0$ 并不会对答案产生任何贡献。
	- 所以实际转移是：$\frac{dp_S}{c_S} \times g_T \to dp_{S \cap T} (|S \cap T| < |S|)$。
- 求 $c_S$。
	- 首先一个普通容斥，变为求包含 $S$ 的 $T$，和完全不包含 $S$ 的 $T$。
   - 普通高维前缀和。
- 由于 $|S \cap T| < |S|$ 这个限制，我们考虑枚举 popcount 从 $m$ 到 $0$，由 popcount $> i$ 的状态转移到 popcount $= i$ 的状态。这样那个限制就没有了。
- 优化转移。
	- 考虑一个普通容斥，$dp_S$ 可以先加上每对 $S \in S',T$ 的贡献，然后减去那些 $S' \cap T \ne S$ 且 $S \in S' \cap T$ 的总和。
   - 第一步可以高维前缀和，第二步需要高维差分。

### Code:
```cpp
#include <bits/stdc++.h>

using namespace std;
using LL = long long;

const int MAXM = (1ll << 20) + 3;

int n, m, pc[MAXM];
double c[MAXM], c1[MAXM], c2[MAXM]; // c 数组
double g[MAXM]; // g 数组
double f[MAXM], tmp[MAXM], _f[MAXM]; 

void ADD(double &x, double w){ x += w; }

void hdi_suf(double *A){
	for(int i = 0; i < m; i++){
		for(int s = 0; s < (1ll << m); s++) if((s >> i) & 1) ADD(A[s ^ (1ll << i)], A[s]);
	}
}
void _hdi_suf(double *A){ // 高维后缀差分
	for(int i = 0; i < m; i++){
		for(int s = 0; s < (1ll << m); s++) if((s >> i) & 1) ADD(A[s ^ (1ll << i)], - A[s]);
	}
}
void hdi_pre(double *A){
	for(int i = 0; i < m; i++){
		for(int s = 0; s < (1ll << m); s++) if((s >> i) % 2 == 0) ADD(A[s ^ (1ll << i)], A[s]);
	}
}

int main(){
  ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> m;
	int R = (1ll << m) - 1;
	for(int s = 0; s < (1ll << m); s++){
		for(int i = 0; i < m; i++) pc[s] += (s >> i) & 1;
	}
	for(int i = 1; i <= n; i++){
		int S = 0;
		for(int j = 0; j < m; j++){
			char ch; cin >> ch, S += (ch == '1') * (1ll << j);
		}
		g[S]++, c1[S]++, c2[S]++;
	}
	hdi_pre(c1), hdi_suf(c2);

  for(int s = 0; s < (1ll << m); s++){
		c[s] = (s == 0 ? 0 : n - c1[s ^ R] - c2[s]);
		if(c[s] < 0) return 1;
	}

	f[R] = 1;
	hdi_suf(g); // 先对 g 做一遍后缀和
	for(int i = m - 1; i >= 1; i--){
		for(int s = 0; s < (1ll << m); s++) tmp[s] = f[s], f[s] = (c[s] == 0 ? 0 : f[s] / c[s]);
		hdi_suf(f);
		for(int s = 0; s < (1ll << m); s++) _f[s] = f[s] * g[s];
		_hdi_suf(_f);

		for(int s = 0; s < (1ll << m); s++){
			if(pc[s] > i) f[s] = tmp[s];
			if(pc[s] == i) f[s] = _f[s];
			if(pc[s] < i) f[s] = 0;
		}
	}
	vector<double> ans(m, 0);
	for(int s = 1; s < (1ll << m); s++){
	  if(c[s] != 0) continue; // 只统计最终状态的概率 
		for(int i = 0; i < m; i++) if((s >> i) & 1) ADD(ans[i], f[s]);
	}
  cout << fixed << setprecision(10) << ans[0] << "\n";
	return 0;
}
```

---

## 作者：lsj2009 (赞：5)

### Problem

状压 dp 绝世好题。

看到 $m$ 非常小，我们考虑压一手，设 $f_S$ 为剩余选手为 $S$ 时 Genie 获胜得概率。

但是现在有个问题是，我们肯定要选择一个问题让 $S$ 转移到 $T$，但是我们不知道这个问题之前有没有被选过，如果重复选择不就寄了，如果再开一维记录问题得状态，$2^{2\cdot 10^5}$ 也寄了，怎么办？

这里用到了 UOJ370 的 trick：如果某个问题被重复选择，则集合 $S$ 在问完这个问题后不会发生变化，因为不会这个问题的人都寄了。

接下来考虑如何转移。我们设 $g_{S,T}$ 表示为可以令参赛者状态从 $S$ 转移到 $T$ 问题个数，显然 $T\subset S$，所以 $g$ 的空间是 $\Theta(3^n)$ 的，可以存的下。然后显然易得的是转移方程 $f_S=\frac{\sum\limits_{T\subset S} f_T\cdot g_{S,t}}{n-g_{S,\emptyset}-g_{S,S}}$，那么问题在于如何求 $g$。

$g$ 的转移也比较显然：我们考虑在集合 $S$ 中加入 $x$ 这个人，然后再提前 ban 掉他，也就是 $g_{S,T}=g_{S\cup x,T}+g_{S\cup x,T\cup x}$，$x$ 可以取任意不属于 $S$ 的值。

然后就做完了，复杂度 $\Theta(nm+3^m)$。

### Code

```cpp
#include<bits/stdc++.h>
//#define int long long
#define ll long long
#define ull unsigned long long
#define ld long double
#define PII pair<int,int>
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define chkmax(a,b) a=max(a,b)
#define chkmin(a,b) a=min(a,b)
#define rep(k,l,r) for(int k=l;k<=r;++k)
#define per(k,r,l) for(int k=r;k>=l;--k)
#define cl(f,x) memset(f,x,sizeof(f))
using namespace std;
const int N=2e5+5,N1=17,M=1<<17;
vector<PII> g[M];
int tmp[N];
ld f[N];
char s[N1];
signed main() {
    int n,m;
    scanf("%d%d",&n,&m);
    int tot=(1<<m)-1;
    rep(S,0,tot) {
        int len=1<<__builtin_popcount(S);
        g[S].resize(len);
        for(int T=S;;T=(T-1)&S) {
	        g[S][--len].first=T; 
            if(T==0)
                break;
        }
    }
    rep(i,1,n) {
        scanf("%s",s);
        int res=0;
        rep(j,0,m-1) {
            if(s[j]=='1')
                res|=1<<j;
        }
        ++g[tot][res].second;
    }
    per(S,tot-1,0) {
        int k=-1;
        rep(i,0,m-1) {
            if(!((S>>i)&1)) {
                k=i; break;
            }
        }
        int t=S|(1<<k);
        for(auto x:g[S])
            tmp[x.first]=0;
        for(auto x:g[t])
            tmp[S&x.first]+=x.second;
        for(auto &x:g[S])
            x.second=tmp[x.first];
    }
    rep(S,0,tot) {
        if((S+1)&1)
            continue;
        int cnt=n-g[S][0].second-g[S][(int)g[S].size()-1].second;
        if(cnt==0)
            f[S]=1.0;
        else {
            for(auto x:g[S]) {
				int T=x.first;
                if(T!=0&&T!=S)
                    f[S]+=f[T]*x.second;
            }
            f[S]/=cnt;
        }
    }
    printf("%.12Lf\n",f[tot]);
    return 0;
}
```

---

## 作者：Leasier (赞：2)

《关于内存限制 1GB 但是我用了 1002.7MB 这回事》

------------

注意到 $m \leq 17$，考虑状压参赛者，但这里有一个问题：现在未被淘汰参赛者固定时，题目集合不一定固定。

发现一道题第二次被抽到实际上不会改变这个集合，于是我们忽略这个问题。

设 $T_i$ 表示答对第 $i$ 道题的参赛者集合，$cnt(P, Q) = \displaystyle\sum_{i = 1}^n [P \cap T_i = Q]$。

考虑 dp，设 $dp_S$ 表示现在未被淘汰的参赛者集合为 $S$ 时，Genie 最终胜利的概率。

初值：$dp_S = 1$，其中 $S$ 满足 $cnt(S, \emptyset) + cnt(S, S) = n$。

转移：$dp_S = \dfrac{\displaystyle\sum_{T \subseteq S, T \neq \emptyset} dp_T cnt(S, T)}{n - cnt(S, \emptyset) - cnt(S, S)}$。

答案：$dp_{\{1, 2, \cdots, m\}}$。

最后的问题是我们应该如何快速计算 $\forall Q \subseteq P, cnt(P, Q)$。

考虑递推。若我们从一个 $P \cup \{x\}$ 出发（其中 $x \notin P$）尝试递推出 $P$，则 $cnt(P, Q) = cnt(P \cup \{x\}, Q) + cnt(P \cup \{x\}, Q \cup \{x\})$。

枚举子集即可。时间复杂度为 $O(nm + 3^m)$。

代码：
```cpp
#include <stdio.h>

int size[131077], temp[131077], *v1[131077], *v2[131077];
double dp[131077];
char s[27];

int main(){
	int n, m, full;
	scanf("%d %d", &n, &m);
	full = (1 << m) - 1;
	for (int i = 0; i <= full; i++){
		int pos = size[i] = 1 << __builtin_popcount(i);
		v1[i] = new int[size[i]];
		v2[i] = new int[size[i]];
		for (int j = i; ; j = i & (j - 1)){
			v1[i][--pos] = j;
			if (j == 0) break;
		}
	}
	for (int i = 0; i <= full; i++){
		v2[full][i] = 0;
	}
	for (int i = 1; i <= n; i++){
		int state = 0;
		scanf("%s", &s[1]);
		for (int j = 1; j <= m; j++){
			if (s[j] == '1') state |= 1 << (j - 1);
		}
		v2[full][state]++;
	}
	for (int i = full - 1; i >= 0; i--){
		int pos, x;
		for (int j = 1; j <= m; j++){
			if (!(i >> (j - 1) & 1)){
				pos = j;
				break;
			}
		}
		x = i | (1 << (pos - 1));
		for (int j = 0; j < size[i]; j++){
			temp[v1[i][j]] = 0;
		}
		for (int j = 0; j < size[x]; j++){
			temp[v1[x][j] & i] += v2[x][j];
		}
		for (int j = 0; j < size[i]; j++){
			v2[i][j] = temp[v1[i][j]];
		}
	}
	for (int i = 1; i <= full; i += 2){
		int cnt = n - v2[i][0] - v2[i][size[i] - 1];
		if (cnt == 0){
			dp[i] = 1.0;
		} else {
			for (int j = 1; j + 1 < size[i]; j++){
				dp[i] += dp[v1[i][j]] * v2[i][j];
			}
			dp[i] /= cnt;
		}
	}
	printf("%.12lf", dp[full]);
	return 0;
}
```

---

## 作者：Purslane (赞：1)

# Solution

考虑模拟询问的过程中幸存的人的变化，必定形如 $S_0 \to S_1 \to \cdots \to S_t$，其中 $S_i \subset S_{i-1}$。

这件事情的概率是什么？设 $S_i \to S_{i+1}$ 有 $c_i$ 种方法，而有 $t_i$ 种比赛使得其作用在 $S_i$ 上有变化，那么 $S_i \to S_{i+1}$ 等价于限制了这 $t_i$ 个数中第一个数的类型，即 $\dfrac{c_i}{t_i}$。很容易发现所有的限制是独立的，因此可以直接将概率乘起来。

转移其实是在线按位与卷积，只需要按照 $\text{popcount}$ 转移即可，复杂度 $O(m^2 2^m)$，足以通过本题。

```cpp
#include<bits/stdc++.h>
#define ld long double
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2e5+10;
int n,m,s[MAXN],pre1[MAXN],pre2[MAXN],cnt[MAXN];
ld ans,dp[MAXN];
void fwt(ld* f) {
	ffor(i,1,m) ffor(j,0,(1<<m)-1) if(j&(1<<i-1)) f[j-(1<<i-1)]+=f[j];
	return ;	
}
void ifwt(ld* f) {
	ffor(i,1,m) ffor(j,0,(1<<m)-1) if(j&(1<<i-1)) f[j-(1<<i-1)]-=f[j];
	return ;
}
ld f[MAXN],g[MAXN];
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	ffor(i,1,n) {
		string S;
		cin>>S;
		ffor(j,1,m) if(S[j-1]=='1') s[i]|=(1<<j-1);	
		pre1[s[i]]++,pre2[(1<<m)-1-s[i]]++;
		f[s[i]]++,cnt[s[i]]++;
	}
	fwt(f);
	ffor(i,1,m) ffor(j,0,(1<<m)-1) if(j&(1<<i-1)) pre1[j]+=pre1[j-(1<<i-1)];	
	ffor(i,1,m) ffor(j,0,(1<<m)-1) if(j&(1<<i-1)) pre2[j]+=pre2[j-(1<<i-1)];	
	dp[(1<<m)-1]=1;
	roff(i,m,1) {
		memset(g,0,sizeof(g));
		ffor(j,0,(1<<m)-1) if(__builtin_popcount(j)==i) {
			int deg=n-pre1[(1<<m)-1-j]-pre2[(1<<m)-1-j];
			if(deg) g[j]=dp[j]/deg;
			else if(j&1) ans+=dp[j];
		}
		fwt(g);
		ffor(j,0,(1<<m)-1) g[j]=g[j]*f[j];
		ifwt(g);
		ffor(j,1,(1<<m)-1) if(__builtin_popcount(j)<i) dp[j]+=g[j];
	}
	cout<<fixed<<setprecision(10)<<ans;
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：0)

考虑 $dp_S$ 表示 $S$ 子集里的人存活的概率。

考虑转移，当我们考虑到 $S$ 子集时，$S$ 中的人都会做/都不会做的题目是对目前状态没有意义的。考虑将 $S$ 转移到 $T$，其中 $T\subset S$。也就是说，我们希望 $O(1)$ 计算出 $S\oplus T$ 中所有人都不会，$T$ 中所有人都会，其余人任意的题目数量。

考虑三进制预处理，每一个人 $0/1/2$ 分别表示钦定其会，钦定其不会和可以会也可以不会。可以在 $O(3^m)$ 或 $O(3^mm)$ 复杂度处理出对应的符合要求的题目数量。

然后转移就变得容易了。设对于当前状态有意义的题目数量为 $x$，转移到 $T$ 对应的题目数量为 $y$，转移的系数就是 $\frac{y}{x}$（即 $x$ 个题目的所有排列中某 $y$ 个题目之一排在最前面的概率）。

总复杂度 $O(3^mm)$，实现精细可以做到 $O(3^m)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
#define mid ((l+r)>>1)
using namespace std; 
double dp[1000005];
int val[1000005],to3[1000005];
signed cnt[129140163];
int pw3[20],tag[1000005];
signed main(){
	pw3[0]=1; for(int i=1;i<=19;i++) pw3[i]=pw3[i-1]*3;
	int n,m; cin>>n>>m;
	for(int i=1;i<=n;i++){
		int tmp=0;
		for(int j=0;j<m;j++){
			char c; cin>>c;
			val[i]|=(1<<j)*(c-'0');
			if(c-'0') tmp+=pw3[j];
		}
		cnt[tmp]++;
	}
	for(int i=0;i<(1<<m);i++){
		for(int j=0;j<m;j++){
			to3[i]+=((i>>j)&1)*pw3[j];
		}
	}
	for(int i=0;i<pw3[m];i++){
		int tmp=i;
		for(int j=0;j<m;j++){
			if(tmp%3==2){
				cnt[i]=cnt[i-2*pw3[j]]+cnt[i-pw3[j]];
				break;
			}
			tmp/=3;
		}
	}
	dp[(1<<m)-1]=1;
	for(int i=(1<<m)-1;i>=1;i--){
		if(!(i&1)) continue;
		int pre=0;
		for(int j=0;j<m;j++) if(!((i>>j)&1)) pre+=2*pw3[j];
		int tot=n-(cnt[pre]+cnt[pre+to3[i]]);
		if(!tot){
			tag[i]=1;
			break;
		}
		for(int j=i&(i-1);j;j=(j-1)&i){
			dp[j]+=dp[i]*cnt[pre+to3[j]]/tot;
		}
	}
	double tot=0;
	for(int i=1;i<(1<<m);i++) if(tag[i]) tot+=dp[i];
	cout<<fixed<<setprecision(10)<<tot;
	return 0;
}
```

---

## 作者：Graphcity (赞：0)

对于一个排列，我们定义关键问题为淘汰了人的问题，非关键问题为没有淘汰人的问题。

假设我们已经钦定了关键问题组成的子序列 $p_{1\cdots k}$，那么对于剩下的问题，它们一定在某一个时刻后变成非关键问题。令在 $p_i$ 被问到后变成非关键问题的有 $c_i$ 个，考虑问问题先后组成的偏序关系，可以发现这个偏序关系形成了一棵树。这棵树的主干是 $p_i\to p_{i+1}$，表示第 $i$ 个关键问题要在第 $i+1$ 个关键问题前被问到。同时 $p_i$ 还有 $c_i$ 个儿子，表示只有第 $i$ 个问题问完后这些问题才能变成非关键问题。

注意到树的拓扑序计数只跟每个点的子树大小相关。这道题中，它只跟关键问题的子树大小相关。设 $f_S$ 表示当前还剩下集合 $S$ 中的人时，仅考虑当前的关键问题，组成的拓扑序方案数。我们枚举 $S$ 的子集 $T$，令 $val_{S,T}$ 表示剩余 $S$ 中的人时能够淘汰成 $T$ 的问题数量（可以枚举子集做到 $O(3^m)$），$cnt_S$ 表示还剩 $S$ 中的人时，关键问题的数量。转移就是 $f_S\gets f_T\times val_{S,T}\div cnt_S$。

当没有关键问题，也就是 $cnt_S=0$ 时，有 $f_S=1$。总时间复杂度 $O(3^m)$。

```cpp
#include<bits/stdc++.h>
#define double long double
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=2e5;

int n,m,lim,cnt[Maxn+5],h[Maxn+5]; double f[Maxn+5];
vector<pair<int,int>> mp[Maxn+5];

int main()
{
    cin>>n>>m; lim=(1<<m)-1;
    For(i,1,n)
    {
        string s; cin>>s;
        For(j,0,m-1) if(s[j]=='1') h[i]|=(1<<j);
        cnt[lim]++,cnt[h[i]]--,cnt[lim^h[i]]--;
    }
    For(j,0,m-1) For(i,0,lim) if(!(i&(1<<j))) cnt[i]+=cnt[i|(1<<j)];
    For(i,1,n) mp[lim].emplace_back(h[i],1); f[lim]=1;
    Rof(i,lim,0) if(i&1 && cnt[i])
    {
        static int val[Maxn+5];
        for(auto [j,k]:mp[i]) val[j]+=k;
        vector<pair<int,int>>().swap(mp[i]);
        for(int j=(i-1)&i;j;j=(j-1)&i) if(val[j])
        {
            int res=val[j]; if(j&1) f[j]=(f[j]+f[i]*res/::cnt[i]);
            Rof(k,m-1,0)
            {
                if(!(i&(1<<k))) break;
                mp[i^(1<<k)].emplace_back((i^(1<<k))&j,res);
            }
        }
        for(int j=(i-1)&i;j;j=(j-1)&i) val[j]=0;
    } double ans=0;
    For(i,0,lim) if(i&1 && !cnt[i]) ans+=f[i];
    printf("%.12Lf\n",ans);
    return 0;
}
```

---

