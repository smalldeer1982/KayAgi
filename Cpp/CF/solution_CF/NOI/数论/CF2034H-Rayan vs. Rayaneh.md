# Rayan vs. Rayaneh

## 题目描述

为了赢得 Reyhaneh 的芳心，Rayan 宣称自己比计算机（波斯语中称为 Rayaneh）更强。为了验证他的说法，Reyhaneh 请教了 Khwarizmi。Khwarizmi 解释道，一个整数集合如果集合中的任何一个元素都不能表示为其他元素的整数线性组合，则称为整数线性无关。 Rayan 每次收到一个整数集合，他的任务是找出其中一个尽可能大的整数线性无关子集。

值得注意的是，单个元素始终被认为是整数线性无关的子集。

对于整数 $ a_1, \ldots, a_k $，它们的整数线性组合是形式为 $ c_1 \cdot a_1 + c_2 \cdot a_2 + \ldots + c_k \cdot a_k $ 的任何和式，这里 $ c_1, c_2, \ldots, c_k $ 为整数（可以是零、正数或负数）。

## 说明/提示

例子 1 中，集合 $\{4, 6\}$ 是一个整数线性无关的子集。可以证明不存在包含至少 3 个元素的整数线性无关子集。

例子 2 中，集合 $\{35, 21, 30\}$ 是一个整数线性无关的子集，因为任意两个元素的整数线性组合无法生成第三个元素。没有包含至少 4 个元素的整数线性无关子集。

例子 3 中，集合 $\{2, 3, 6\}$ 并不是一个整数线性无关的子集，因为 6 可以表示为 $ 6 \cdot 2 + (-2) \cdot 3 $，这是 $\{2, 3\}$ 的整数线性组合。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3
5
2 4 6 8 10
5
12 15 21 30 35
3
2 3 6```

### 输出

```
2
4 6
3
35 21 30
2
2 3```

# 题解

## 作者：ForgotMe (赞：5)

很棒的一个题目啊。如果你尝试往线性代数方面去想的话，反而可能会被卡住，因为这个题的组合系数要求是整数意义下，与平常线代学习的内容有所不同。

首先思考对于一个确定的集合 $S=\{x_1,x_2,\cdots,x_n\}$，如何判断其是**线性无关**的。

形式化的将其写成方程，那就是对于 $\forall i$，整数意义下的不定方程 $\sum_{j\ne i}c_jx_j=x_i$ 无解，根据裴蜀定理，可以知道其无解的充要条件就是 $\gcd_{j\ne i}\{x_j\}\nmid x_i$。

但是这个条件并不好直接刻画，考虑转化条件 $\gcd_{j\ne i}\{x_j\}\nmid x_i$，其等价于 $\exist p_i^{q_i}$，满足 $p_i^{q_i}\nmid x_i$，且 $p_i^{q_i}\mid x_j(j\ne i)$。这个条件不太直观，用文字来描述就是存在一个质数 $p$ 满足 $p$ 在 $x_i$ 中的幂次是**严格**最小的！显然如果不存在这样的一个质数 $p$，那么一定会有 $\gcd_{j\ne i}\{x_j\}\mid x_i$。

于是就可以反过来思考了，如果现在已知每个数对应的这个质数的幂次 $p_i^{q_i}$，能不能找到一组合法的 $x$ 呢？令 $G=p_1^{q_1}p_2^{q_2}\cdots p_n^{q_n}$，那么有解当前仅当 $f_{\frac{G}{p_i^{q_i}}}>f_G$，其中 $f_x$ 表示 $a$ 中是 $x$ 的倍数的个数。

剩下的部分就很好做了，考虑令 $M$ 为值域，$p_1^{q_1}<p_2^{q_2}<\cdots <p_n^{q_n}$，在 $n>2$ 的情况下，显然会有 $p_1^{q_1}<\sqrt{M}$，且 $\frac{G}{p_1^{q_1}}\le M$，否则 $f_{\frac{G}{p_1^{q_1}}}$ 一定是 $0$，那么就会无解。

于是直接枚举 $p_1^{q_1},\frac{G}{p_1^{q_1}}$ 检查是否有解即可，注意在 $\sqrt{M}$ 以内质数的幂次数量级别根据积分可知是 $\mathcal{O}(\frac{\sqrt{M}}{\log M})$ 级别的，于是总复杂度就是 $\mathcal{O}(T\frac{M\sqrt{M}K}{\log M}+TnK+TM\log M)$ 的，其中 $K$ 是答案的大小级别，根据上述推导可知，$K$ 不可能超过 $6$，因为 $2\times 3\times 5\times 7\times 11\times 13\times 17>10^5$。

注意要加一些剪枝，不然会跑的很慢，不知道根号级别，开 $100$ 组数据是怎么想的。

放个代码：https://www.luogu.com.cn/paste/q7q1oaik 。

---

## 作者：EuphoricStar (赞：1)

考虑一个集合 $c_1, c_2, \ldots, c_k$ 合法的充要条件。根据裴蜀定理可得：
$$
\forall i \in [1, k], \gcd\limits_{j \ne i} \{c_j\} \nmid c_i
$$
对每个数分解质因子，条件可以看成是，给 $c_i$ 选择一个质数的若干次方 $p_i^{e_i}$，使得 $p_i$ 互不相同，且 $c_i$ 中 $p_i$ 的指数 $< e_i$，而其他数的 $p_i$ 的指数 $\ge e_i$。

考虑先判掉答案集合大小 $\le 2$ 的情况：集合大小 $= 1$ 就随便选一个数，$= 2$ 相当于集合中的两个数不为倍数关系，把所有数排序后看相邻两个数是否为倍数关系即可。那么只用考虑集合大小 $\ge 3$ 的情况了。

考虑直接枚举所有可能的 $(p_1^{e_1}, p_2^{e_2}, \ldots, p_k^{e_k})$，那么相当于对于所有 $i \in [1, k]$，要在 $a$ 中找一个数，使得其被 $\prod\limits_{j \ne i} p_j^{e_j}$ 整除而不被 $\prod\limits_{j = 1}^k p_j^{e_j}$ 整除。预处理出 $f_x$ 表示 $a$ 中有多少个数是 $x$ 的倍数，那么这个条件是容易判断的。

发现 $(p_1^{e_1}, p_2^{e_2}, \ldots, p_k^{e_k})$ 一定要满足 $\forall i \in [1, k], \prod\limits_{j \ne i} p_j^{e_j} \le 10^5$，所以 $k \le 6$（极端情况是 $(2, 3, 5, 7, 11, 13)$）。因为只用考虑 $k \ge 3$ 的情况，爆搜出来所有可能的 $(p_1^{e_1}, p_2^{e_2}, \ldots, p_k^{e_k})$ 发现只有大概 $8.6 \times 10^5$ 种。那么直接枚举即可。

令 $T$ 为所有可能的 $(p_1^{e_1}, p_2^{e_2}, \ldots, p_k^{e_k})$ 的 $k$ 的和，那么时间复杂度为 $O(t (V \log V + T))$，其中 $V \log V$ 是预处理 $f_x$ 的复杂度。

```cpp
// Problem: H. Rayan vs. Rayaneh
// Contest: Codeforces - Rayan Programming Contest 2024 - Selection (Codeforces Round 989, Div. 1 + Div. 2)
// URL: https://codeforces.com/contest/2034/problem/H
// Memory Limit: 512 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define pb emplace_back
#define fst first
#define scd second
#define mkp make_pair
#define uint unsigned
#define mems(a, x) memset((a), (x), sizeof(a))

using namespace std;
typedef long long ll;
typedef double db;
typedef unsigned long long ull;
typedef long double ldb;
typedef pair<int, int> pii;

const int maxn = 100100;
const int N = 100000;

int n, a[maxn], pr[maxn], tot, f[maxn];
bool vis[maxn], mk[maxn];

pii b[852200][6];
int stk[9], top, len[852200], K;

void dfs(int d, ll x, ll mn) {
	if (top >= 3) {
		++K;
		len[K] = top;
		for (int i = 0; i < top; ++i) {
			b[K][i] = mkp(1, stk[i]);
			for (int j = 0; j < top; ++j) {
				if (j != i) {
					b[K][i].fst *= stk[j];
				}
			}
		}
	}
	for (int i = d; i <= tot && x * pr[i] <= 31700000 && x * pr[i] / min(mn, 1LL * pr[i]) <= N; ++i) {
		ll y = pr[i];
		while (y <= N && x * y <= 31700000 && x * y / min(mn, y) <= N) {
			stk[top++] = y;
			dfs(i + 1, x * y, min(mn, y));
			--top;
			y *= pr[d];
		}
	}
}

inline void init() {
	for (int i = 2; i <= N; ++i) {
		if (!vis[i]) {
			pr[++tot] = i;
		}
		for (int j = 1; j <= tot && i * pr[j] <= N; ++j) {
			vis[i * pr[j]] = 1;
			if (i % pr[j] == 0) {
				break;
			}
		}
	}
	dfs(1, 1, 1e18);
}

void solve() {
	scanf("%d", &n);
	mems(mk, 0);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		mk[a[i]] = 1;
	}
	n = 0;
	for (int i = 1; i <= N; ++i) {
		if (mk[i]) {
			a[++n] = i;
		}
	}
	vector<int> ans(1, a[1]);
	for (int i = 1; i < n; ++i) {
		if (a[i + 1] % a[i]) {
			vector<int>(1, a[i]).swap(ans);
			ans.pb(a[i + 1]);
			break;
		}
	}
	mems(f, 0);
	for (int i = 1; i <= N; ++i) {
		for (int j = i; j <= N; j += i) {
			f[i] += mk[j];
		}
	}
	int mx = -1, p = -1;
	for (int i = 1; i <= K; ++i) {
		bool fl = 1;
		int cnt = 0;
		for (int j = 0; j < 6 && b[i][j].fst && fl; ++j) {
			int k = (b[i][j].fst * b[i][j].scd <= N ? f[b[i][j].fst * b[i][j].scd] : 0);
			fl &= (f[b[i][j].fst] != k);
			++cnt;
		}
		if (fl && cnt > mx) {
			mx = cnt;
			p = i;
		}
	}
	if (p != -1) {
		vector<int>().swap(ans);
		for (int i = 0; i < mx; ++i) {
			int x = b[p][i].fst, y = b[p][i].scd;
			for (int j = 1; j <= n; ++j) {
				if (a[j] % x == 0 && a[j] % y) {
					ans.pb(a[j]);
					break;
				}
			}
		}
	}
	printf("%d\n", (int)ans.size());
	for (int i = 0; i < (int)ans.size(); ++i) {
		printf("%d%c", ans[i], " \n"[i == (int)ans.size() - 1]);
	}
}

int main() {
	init();
	int T = 1;
	scanf("%d", &T);
	while (T--) {
		solve();
	}
	return 0;
}

```

---

## 作者：cwfxlh (赞：1)

# [CF2034H](https://www.luogu.com.cn/problem/CF2034H)           

令 $m=100000$，即值域大小。

一个集合能且仅能表示集合内所有数 $\gcd$ 的倍数。           

考虑对于每个质数，取 $\gcd$ 看成指数取 $\min$ 的形式，一个集合是线性独立的，当且仅当每个元素都至少在一个质数的指数上取到了集合内的唯一最小值。         

考虑每个元素取最小值的质数位置，多个位置只保留一个，写成 $p_1^{q_1},p_2^{q_2},\dots p_k^{q_k}$ 的形式，那么其他位置暂且忽略。对于一组 $p_1^{q_1},p_2^{q_2},\dots p_k^{q_k}$，则这一组合法的充要条件就是对于每个 $i\in[1,k]$，都存在至少一个 $a_x$ 满足其是 $\prod_{j\not=i}{p_j^{q_j+1}}$ 的倍数，但是不是 $\prod {p_j^{q_j+1}}$ 的倍数。含义就是只对 $p_i$ 这个质数产生贡献。判断有没有这个数可以 $O(m\log m)$ 预处理。             

接下来需要求出的就是 $k$ 最大的一组合法的 $p_1^{q_1},p_2^{q_2},\dots p_k^{q_k}$。            

如果枚举的话，$\prod{p_i^{q_i+1}}$ 可能很大，但是发现，其除掉一个 $p_i^{q_i+1}$ 必定小于等于 $m$，所以 $(\min{p_i^{q_i+1}})^{k-1}\le m$，当 $k>2$ 的时候，考虑枚举最小的那个质数幂，再枚举 $[1,m]$ 作为其他幂的乘积，check 的时候 $O(k)$ 枚举每个质数幂即可。           

这里有个性质，就是答案不会超过 6，因为考虑最小的 7 个质数的乘积，除掉 2 后仍然超过了 $m$。        

分析一下上面的复杂度，有上界 $O(TmK\frac{\sqrt{m}}{\log m})$，此处 $k=6$。           

剩余的情况是 $k=1$ 和 $k=2$。$k=1$ 是简单的，$k=2$ 时，如果两个数 $x$ 和 $y$ 能成为答案，则 $x\nmid y$ 且 $y\nmid x$。因为 $a$ 不重，所以答案为 1 的序列长度不超过 $\log m$，于是在前 20 个数里枚举配对即可。           

代码：         


```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,a[100003],ans1,ans2,ans3;
int pri[100003],isp[100003],totp,pm[100003],mnv[100003],k1,k2,k3,k4,k5,k6,k7,k8,k9,flg;
int plst[100003][11],plst2[100003][11];
int stk[11][100003];
int tot[11];
vector<int>ys[100003];
int num[100003];
int getcnt(int X){
    if(X<=100000)return num[X];
    return 0;
}
int pwr(int X,int Y){
    if(Y==1)return X;
    return X*pwr(X,Y-1);
}
void sol(){
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=100000;i++)num[i]=0;
    for(int i=1;i<=n;i++){
        for(auto j:ys[a[i]])num[j]++;
    }
    ans1=ans2=ans3=-1;
    for(int oo=3;oo<=6;oo++){
        for(int i=2;;i++){
            if(pm[i]>1)continue;
            if(pwr(i,oo-1)>100000)break;
            if(ans1==oo)break;
            for(int jj=1;jj<=tot[oo-1];jj++){
                int j=stk[oo-1][jj];
                if(j%i==0)continue;
                if(i>mnv[j])continue;
                if((i*j/mnv[j])>100000)continue;
                k1=getcnt(i*j);
                flg=(getcnt(j)!=k1);
                for(int u=1;u<=pm[j]&&flg;u++)flg&=(num[i*j/plst2[j][u]]!=k1);
                if(flg){
                    ans2=i;
                    ans3=j;
                    ans1=oo;
                    break;
                }
            }
        }
    }
    if(ans1>2){
        cout<<ans1<<'\n';
        for(int i=1;i<=n;i++){
            if(a[i]%(ans2*ans3)==0)continue;
            if(a[i]%ans3==0){
                cout<<a[i]<<' ';
                break;
            }
        }
        for(int u=1;u<=pm[ans3];u++){
            for(int i=1;i<=n;i++){
                if(a[i]%(ans2*ans3)==0)continue;
                if(a[i]%(ans2*ans3/plst[ans3][u])==0){
                    cout<<a[i]<<' ';
                    break;
                }
            }
        }
        cout<<'\n';
        return;
    }
    for(int i=1;i<=min(n,25);i++){
        for(int j=i+1;j<=min(n,25);j++){
            if(a[i]%a[j]==0||a[j]%a[i]==0)continue;
            cout<<2<<'\n'<<a[i]<<' '<<a[j]<<'\n';
            return;
        }
    }
    cout<<1<<'\n'<<a[1]<<'\n';
    return;
}
signed main(){
    ios::sync_with_stdio(false);
    for(int i=2;i<=100000;i++){
        if(!isp[i]){
            pri[++totp]=i;
            for(int j=1;j*i<=100000;j++){
                pm[j*i]++;
                plst[j*i][pm[j*i]]=i;
            }
        }
        for(int j=1;j<=totp;j++){
            if(pri[j]*i>100000)break;
            isp[pri[j]*i]=1;
            if(i%pri[j]==0)break;
        }
    }
    for(int i=1;i<=100000;i++){
        stk[pm[i]][++tot[pm[i]]]=i;
        mnv[i]=i;
        for(int j=1;j<=pm[i];j++){
            int u=i;
            while(u%plst[i][j]==0)u/=plst[i][j];
            mnv[i]=min(mnv[i],(i/u));
            plst2[i][j]=i/u;
        }
        for(int j=1;j*i<=100000;j++)ys[j*i].emplace_back(i);
    }
    cin>>T;
    while(T--)sol();
    return 0;
}
```

---

