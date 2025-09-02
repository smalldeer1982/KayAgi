# Eating

## 题目描述

有 $n$ 个史莱姆排成一行，第 $i$ 个史莱姆的体重为 $w_i$。当史莱姆 $i$ 满足 $w_i \geq w_j$ 时，它可以吃掉史莱姆 $j$；之后，史莱姆 $j$ 会消失，史莱姆 $i$ 的体重将变为 $w_i \oplus w_j$ $^{\text{∗}}$。

史莱姆国王希望进行一个参数为 $x$ 的实验，步骤如下：
- 在行的最右端（第 $n$ 个史莱姆之后）新增一个体重为 $x$ 的史莱姆。
- 这个新史莱姆会不断尝试吃掉左侧相邻的史莱姆（如果可能的话），并移动到被吃掉的史莱姆的位置。当左侧没有史莱姆或其左侧史莱姆的体重大于自身时，该过程停止。（此过程中不会有其他史莱姆被吃掉）
- 该实验的得分为被吃掉的史莱姆总数。

史莱姆国王将向你提出 $q$ 次询问。每次询问给定一个整数 $x$，你需要计算以该参数进行实验的得分。

注意这些询问是假设性的，并不会实际改变史莱姆的初始状态（即查询是非持久化的）。

 $^{\text{∗}}$ 此处 $\oplus$ 表示[按位异或运算](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)。

## 说明/提示

第二个测试用例的第一个查询：
- 新增体重为 $8$ 的史莱姆后，数组变为 $[1, 5, 4, 11, \color{red}8]$。
- 新增史莱姆体重小于左侧史莱姆，无法吃掉，最终得分为 $0$。

第二个测试用例的第二个查询：
- 新增体重为 $13$ 的史莱姆后，数组变为 $[1, 5, 4, 11, \color{red}{13}]$。
- 新增史莱姆吃掉左侧史莱姆，体重变为 $13 \oplus 11 = 6$，数组变为 $[1, 5, 4, \color{red}{6}]$。
- 新增史莱姆继续吃掉左侧史莱姆，体重变为 $6 \oplus 4 = 2$，数组变为 $[1, 5, \color{red}{2}]$。
- 此时无法继续吃掉左侧史莱姆，最终得分为 $2$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3
1 1
5
6
4 4
1 5 4 11
8
13
16
15
10 9
10 4 3 9 7 4 6 1 9 4
2
6
5
6
9
8
6
2
7```

### 输出

```
1
0 2 4 2
0 1 1 1 3 3 1 0 1```

# 题解

## 作者：chenxi2009 (赞：6)

## 思路
考虑先按位分讨，手玩 $0\le w_i,x\le1$，发现一个神奇的性质：$x$ 一定不能吃掉两个 $w_i=1$。因为 $x$ 初始最大是 $1$，吃掉一个就变成 $0$ 了，所以吃不了第二个 $1$。

类比一下，把这个 $0\le w_i\le1$ 放在最高位上，就有一个结论：令 $a$ 为最大的整数使 $2^a\le x$（也即 $x$ 的最高位），则 $x$ 只有能力吃一个 $w_i\ge 2^a$，因为吃掉它以后，$x\leftarrow x\oplus w_i$，最高位就变成零了，$a$ 随之变小。

所以考虑按位从高位到低位、从右往左跳，对于 $i=\log x,\cdots,3,2,1$，每次找当前位置左边最近的 $w_j\ge2^i$，如果 $x\ge2^i$ 那么它显然可以一路吃到 $w_j$ 右边的，然后再判断是否能吃掉 $w_j$，吃掉之后肯定有 $x<2^i$，到碰到 $w_j>x$ 或 $x$ 吃掉所有的史莱姆为止。

建议结合代码理解，时间复杂度 $O((n+q)\log x)$。

看官解学到一个函数 `__lg(x)`，可以取出 $x$ 最大的二进制位，返回值为最大的整数 $a$ 使得 $x\ge2^a$，特别地，$x=0$ 时值为 $-1$。据说复杂度为常数。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,q,w[300000],s[300000],x,pre[300000][32],mxb,now,nxt;
int main(){
	scanf("%d",&T);
	while(T --){
		scanf("%d%d",&n,&q);
		for(int i = 1;i <= n;i ++) scanf("%d",&w[i]);
		for(int i = 1;i <= n;i ++) s[i] = s[i - 1] ^ w[i];
		for(int i = 1;i <= n;i ++){//pre_{i,j} 记录 w_{1,2,3,...,i} 中最靠右的 w_i>2^j 的位置 
			for(int j = 0;j <= __lg(w[i]);j ++) pre[i][j] = i;
			for(int j = __lg(w[i]) + 1;j < 31;j ++) pre[i][j] = pre[i - 1][j];
		}
		for(int i = 1;i <= q;i ++){
			scanf("%d",&x);
			now = n;//now 记录 x 现在面前还没吃掉的是哪一只史莱姆 
			for(int j = 30;~j;j --){
				if(x < 1 << j) continue;//x 比这一位小，跳过 
				nxt = pre[now][j];
				x ^= s[now] ^ s[nxt],now = nxt;//x 比这一位大，一路走吃掉 w_{nxt+1,...,now} 	
				if(!now || w[now] > x) break;//如果吃完了或吃不掉 w_now 就结束 
				x ^= w[now --];//吃掉 w_now 
			}
			printf("%d ",n - now);
		}
		printf("\n");
	}
	return 0;
}
```

---

## 作者：Engulf (赞：4)

需要一点脑子。

考虑现在能否吃掉某个 $a_t$，若 $a_t\le x$ 就能吃掉，把这个条件转化一下，记 $\textrm{msb}(x)$ 表示 $x$ 的 **最高有效位** 即最高位的 $1$ 的位置。如 $\textrm{msb}(1011) = 3$。

- 若 $\textrm{msb}(a_t) < \textrm{msb}(x)$，肯定能吃掉，且 $\textrm{msb}(x)$ 不变。
- 若 $\textrm{msb}(a_t) = \textrm{msb}(x)$，需要判断 $a_t$ 和 $x$ 的大小关系，且 $\textrm{msb}(x)$ 变小。
- 若 $\textrm{msb}(a_t) > \textrm{msb}(x)$，肯定吃不掉，结束。

预处理 $\textrm{lef}_{i, j}$ 为使得 $\forall p \in [k, i], \textrm{msb}(a_p)<j$ 的最小的 $k$。若 $\textrm{msb}(a_i) \ge j$，$\textrm{lef}_{i, j} = 0$。

一样是考虑 $x$ 能否吃掉 $a_t$，初始 $t = n$。
- 若 $\textrm{msb}(a_t) < \textrm{msb}(x)$，因为 $\textrm{msb}(x)$ 不变，所以可以一直吃到 $\textrm{lef}_{t, \textrm{msb}(x)}$，更新 $t$ 和 $x$。
- 若 $\textrm{msb}(a_t) = \textrm{msb}(x)$，判断 $a_t$ 是否 $\le x$，若满足就让 $t$ 减 $1$ 并更新 $x$。这会使 $\textrm{msb}(x)$ 至少减小 $1$，所以这样的操作不超过 $30$ 次。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

const int N = 2e5 + 5;

int n, q;
int a[N];
int lef[N][30];
int pre[N];

int msb(int x) {for (int i = 29; i >= 0; i--) if (x >> i & 1) return i; return -1;}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt;
    cin >> tt;
    while (tt--) {
        cin >> n >> q;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            pre[i] = pre[i - 1] ^ a[i];
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= msb(a[i]); j++)
                lef[i][j] = 0;
            for (int j = msb(a[i]) + 1; j < 30; j++) {
                lef[i][j] = lef[i - 1][j];
                if (!lef[i][j]) lef[i][j] = i;
            }
        }

        while (q--) {
            int x;
            cin >> x;
            int cur = n;
            while (cur >= 1 && a[cur] <= x) {
                if (msb(a[cur]) < msb(x)) {
                    x ^= pre[cur] ^ pre[lef[cur][msb(x)] - 1];
                    cur = lef[cur][msb(x)] - 1;
                } else {
                    x ^= a[cur];
                    cur--;
                }
            }
            cout << n - cur << " ";
        }
        cout << "\n";
    }
    return 0;
}
```

---

## 作者：hbhz_zcy (赞：1)

题意：有 $n$ 个数排成序列 $\omega_i$，我们假设往最右端添加一个数 $x$，$x$ 不断判断左边的数 $a_i$，若 $x \ge a_i$ 则 $x$ 异或上 $a_i$ 然后删去 $a_i$，否则停止并结束。有 $q$ 次这样的假设。  
观察数据范围，显然暴力是行不通的。容易发现 $2^{30}$ 有特殊的含义，提示二进制按位考虑。  
假定只看某一位，即使 $\omega_i,x \in \{0,1\}$，当 $x$ 为 $0$ 时遇到 $1$ 结束。为 $1$ 时遇到两次 $1$ 结束。  
再额外考虑这一位下面有更低位，则 $x$ 为 $0$ 需要依靠更低位判断，但为 $1$ 时第一次必须遇到 $1$（与更低位无关），若判断出 $x \ge a_i$，$x$ 化归为这一位为 $0$ 的情况，否则直接结束。  
再额外考虑这一位无法排出上面有更高位，则上述判断额外增添更高位还有数的情况。  
综合一下得出更简易的判别方法：设 $x$ 最高二进制位为 $t$，则找到剩余序列最靠右的 $a_i \ge 2^t$。在之前 $[i+1,N]$ 里中途不会停止，于是 $x$ 异或上这些值（可以用前缀异或和处理），再与 $a_i$ 进行比较。如果没有停止，$a_i$ 一定最高位也为 $t$，故作异或 $x$ 最高二进制位一定下降。  

设 $\max(x,\argmax{a_i})$ 为 $M$。  
通过 $\Theta(N\log M))$ 预处理出 $f_{i,t}$ 表示 $[1,a_i]$ 中最靠右的、值不小于 $2^t$ 的元素下标。  
然后对于每个询问，显然至多经过 $\log M$ 次跳转。总体复杂度为 $\Theta(Q\log M)$。  
综上所述，空间复杂度为 $\Theta(N\log M)$，时间复杂度为 $\Theta((N+Q)\log M)$。  
```cpp
//g++ d.cpp -o d -g -std=c++14 -O0 -Wall
#include<iostream>
#include<cstdio>
#define LL long long
using namespace std;
int qd(){
	int ng=0,rt=0;char c=getchar();
	while(c<'0'||c>'9')  ng^=c=='-',c=getchar();
	while('0'<=c&&c<='9')  rt=(rt<<3)+(rt<<1)+c-48,c=getchar();
	return ng?-rt:rt;
}
const int maxn=2e5+10,maxlgn=31;
int N,Q,a[maxn],sum[maxn],f[maxn][maxlgn];
int main(){
	freopen("in.txt","r",stdin);
	int T=qd();
	while(T--){
		N=qd(),Q=qd();for(int i=1;i<=N;i++)  sum[i]=sum[i-1]^(a[i]=qd());
		for(int i=1;i<=N;i++)  for(int j=0;j<maxlgn;j++)  f[i][j]=(a[i]>=(1<<j)?i:f[i-1][j]);
		while(Q--){
			int x=qd(),p=N;
			while(1){
				int t=x?__lg(x):0;if(!f[p][t]){printf("%d ",N);break;}
				x^=sum[f[p][t]]^sum[p];//f[p][t]+1~p
				p=f[p][t];
				if(a[p]>x){printf("%d ",N-p);break;}
				x^=a[p],p--;
			}
		}
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：Mr_Az (赞：1)

# [CF2064D Eating](https://www.luogu.com.cn/problem/CF2064D)

### Algorithm:

模拟 + 拆位。

### Solution:

对于 `xor` 的问题，首先按位进行考虑。由于我们能干掉的史莱姆权值都比我们小，所以可以很显然的观察到他们的最高位一定是小于等于我们的，并且我们的最高位在合并史莱姆的过程中**只会下降**。

这启示我们观察到可能使当前结束的点，最高位是大于等于当前值的最高位的。所以我们用 $\text{O}(N\log V)$ 的时间预处理出一个 $pre_{i,j}$ 数组用来存储**离当前点 $i$ 最近的最高位大于等于当前值的最高位 $j$ 的下标**。而且每次跳转我们要么直接结束，要么最高位至少下降 $1$ 位，所以每次询问的复杂度是 $\text{O}(\log V)$ 的。

时间复杂度 $\text{O}((N+Q) \log V)$。

### Code:

```cpp
const int N=2e5+8;
int n,q;
int a[N],nxt[N][32],sum[N];
inline int get(int l,int r){return sum[r]^sum[l-1];}
inline void solve(){
    read(n,q);
    for(rint i=1;i<=n;i++) read(a[i]);
    for(rint i=1;i<=n;i++) sum[i]=sum[i-1]^a[i];
    for(rint i=1;i<=n;i++){
        for(rint j=0;j<=30;j++){
            if(j<=__lg(a[i])) nxt[i][j]=i;
            else nxt[i][j]=nxt[i-1][j];
        }
    }
    while(q--){
        int x,now=n;read(x);
        while(now>=1&&x>0){
            int pos=nxt[now][__lg(x)];
            if(pos==0){now=0;break;}
            x^=get(pos+1,now);
            now=pos;
            if(x<a[pos]) break;
            x^=a[pos];
            now--;
        }
        printf("%lld ",n-now);
        end:;
    }
    puts("");
}
```

---

## 作者：Defy_HeavenS (赞：0)

首先有一个性质，在最高位不会吃掉两个 $1$。这个很明显，吃掉第一个 $1$ 后最高位就为 $0$ 了。

赛时依靠这个性质做，但是当时是把每一位分开来考虑，试图推出每一位对于答案的贡献，而不考虑位与位之间的关系，所以很麻烦，没写出来。

赛后补题也是依靠这个性质，但考虑的是从高位到低位往前推进，再运用这个性质来优化 $\mathcal{O}(\log V)$ 地推进。

具体地，设 $pre_{i,j}=\max\{k|1\le k\le i,w_k>=2^j\},sum_{i}=\oplus_{j=1}^{i}w_j$、当前能吃到的是 $id$、$x$ 是异或上吃掉的这些史莱姆的 $x$。从高到低枚举每一位 $d$，若 $x\ge 2^j$，那么一定能走到 $pre_{id,d}-1$，用 $sum$ 更新一下 $x$，若 $x>w_{pre_{id,d}}$ 则能吃掉这个，就吃掉。

求 $pre$ 只需枚举每一个 $w$，然后每次更新一下比当前 $w$ 小的幂的 $pre$ 即可。

```cpp
#include<bits/stdc++.h>
#define umap unordered_map
#define uset unordered_set
#define mset multiset
#define yes cout<<"Yes\n"
#define no cout<<"No\n"
#define fi first
#define se second
#define pb push_back
#define mkp make_pair
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()
#define tmax(a,b) (a)=max((a),(b))
#define tmin(a,b) (a)=min((a),(b))

using namespace std;
typedef long long LL;
typedef pair<int,int> PII;

const int N=2e5+5;
int n,q,pw[N],w[N],sum[N],pre[N][35];

void solve(){
	cin>>n>>q;
	for(int i=1;i<=n;i++){
		cin>>w[i];
		sum[i]=sum[i-1]^w[i];
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<=__lg(w[i]);j++){
			pre[i][j]=i;
		}
		for(int j=__lg(w[i])+1;j<=31;j++){
			pre[i][j]=pre[i-1][j];
		}
	}
	while(q--){
		int x,id=n;cin>>x;
		for(int i=__lg(x);~i;i--){
			if(x<1ll<<i) continue;
			int to=pre[id][i];
			x^=sum[id]^sum[to],id=to;
			if(!id||x<w[id]) break;
			x^=w[id--];
		}
		cout<<n-id<<" ";
	}
	cout<<"\n";
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int t=1;cin>>t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：迟暮天复明 (赞：0)

我秉持着一向观察不到性质的作风，使用暴力方法通过了此题。

对于所有询问建出字典树，就可以知道一次异或操作之后最小的数是谁。每次不断删除最小的数直到比下一个史莱姆的权值大即可。

时间复杂度 $O((n+q)\log V)$。

---

## 作者：Asedwai (赞：0)

来个离线做法。  
## 思路
  直接无脑 01 trie，将所有的询问按二进制位从大到小都插入字典树中。接下来对于 $i$ 从 $n$ 到 $1$，依次将 $a_i$ 在字典树中按位从高到低进行比较，记当前访问的节点为 $p$，它的儿子为 $s_{p,0}$ 和 $s_{p,1}$，若 $a_i$ 当前位为 $1$，那么就要将 $s_{p,0}$ 子树中的所有询问都求解为 $n-i$，随后删去这颗子树。  
  
  接下来考虑如何将所有的询问对 $a_i$ 异或，如果模拟这个过程，就是对于二进制下 $a_i$ 的每一个为 $1$ 的位置，将树上所对的表示相同位置的节点的左右儿子互换。这样做显然会 TLE。我们可以参考线段树区间修改的方法，也就是将所有的信息在根节点打下一个懒标记，在更新的时候往下传递。懒标记可以使用 `bitset` 维护。  

  时间复杂度 $O((n+q) \log V)$，其中 $V$ 是 $a_i$ 与 $x$ 的值域大小，本题的程序实现中 $\log V$ 改为了固定的常数 $30$。当然空间开得越大越好。   
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define endl "\n"
#define fer(i, a, b) for(int i = (a); i <= (b); i ++)
#define fel(i, a, b) for(int i = (a); i >= (b); i --)
#define LL long long
const int N = 2e5 + 10; 
int T; 
int n, q; 
LL a[N]; 
int tot; 
int s[10000001][2]; 
vector <int> fg[10000001]; 
bitset<30> lz[10000001]; 
void insert(int id, LL x) {
	int p = 0; 
	fel(i, 29, 0) {
		int f = ((x >> i) & 1); 
		if(!s[p][f]) s[p][f] = ++ tot; 
		p = s[p][f]; 
	}
	fg[p].push_back(id); 
}
int ans[N]; 
void del(int id, int p) {
	if(!fg[p].empty()) {
		for(auto const &t : fg[p]) ans[t] = id - 1; 
		fg[p].clear(); 
	}
	if(s[p][0]) {
		del(id, s[p][0]); 
		s[p][0] = 0; 
	}
	if(s[p][1]) {
		del(id, s[p][1]); 
		s[p][1] = 0; 
	}
}
void solve(int id, LL x) {
	int p = 0; 
	fel(i, 29, 0) {
		if(s[p][0]) lz[s[p][0]] ^= lz[p]; 
		if(s[p][1]) lz[s[p][1]] ^= lz[p]; 
		if(lz[p][i]) swap(s[p][0], s[p][1]); 
		lz[p] = 0; 
		int f = ((x >> i) & 1); 
		if(f && s[p][0]) {
			del(id, s[p][0]); 
			s[p][0] = 0; 
		}
		if(!s[p][f]) return ; 
		p = s[p][f]; 
	}
}
signed main() { 
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr); 
	cin >> T; 
	while(T --) {
		fer(i, 0, tot) {
			fg[i].clear(); 
			s[i][0] = s[i][1] = 0; 
			lz[i] = 0; 
		}
		tot = 0; 
		cin >> n >> q; 
		fer(i, 1, n) cin >> a[i]; 
		LL x; 
		fer(i, 1, q) {
			cin >> x; 
			ans[i] = -1; 
			insert(i, x); 
		}
		reverse(a + 1, a + n + 1); 
		fer(i, 1, n) {
			solve(i, a[i]); 
			fer(j, 0, 29) {
				if((a[i] >> j) & 1) {
					if(!lz[0][j]) lz[0][j] = 1; 
					else lz[0][j] = 0; 
				}
			}
		}
		fer(i, 1, q) {
			if(ans[i] == -1) cout << n; 
			else cout << ans[i]; 
			if(i < q) cout << ' '; 
			else cout << endl; 
		}
	}
	return 0; 
}
```

---

## 作者：cxjy (赞：0)

~~菜麻了，场上没调出来~~。





* 首先注意到每次吃掉的过程是 $\oplus$ 操作，于是想到拆位。
* 对于所有已存在的史莱姆和新加入的史莱姆的二进制的最高位开始讨论：
  * 如果新加入的史莱姆存在这样的最高位，那么它**可能**可以吃到倒数第二个存在该最高位的怪之前（不包括倒数第二个，如果不存在倒数第二个，就代表可能可以全部吃掉），它**必定**可以吃到倒数第一个存在该最高位的怪之前（不包括该怪）。
  * 如果新加入的史莱姆不存在这样的最高位，那么它**可能**可以吃到第一个存在这样的最高位之前（不包括该怪）。
* 对此，我们使用 $l , r$ 维护 $ (l , r )$ 这样的区间，这个区间内部的史莱姆代表是可能被吃掉的史莱姆，$i \ge r$ 之后的代表已经被吃掉的史莱姆，$i \le l$  代表不可以被吃的史莱姆。从最高位开始枚举，对于每一个最高位，在 $( l , r )$ 进行之前的讨论即可。因为每次在 $(l , r)$ 的史莱姆都代表高位的贡献已经被抵消，能不能吃掉取决于当前位或者更低位。
* 为了方便查找前一个存在二进制某一位的数的位置，我们可以进行拆位，然后根据每个数在该位是 0 或 1 建立前缀和，然后用二分查找来找到前一个最高位的位置。其实这里可以使用动态规划直接在数组中记录前一个二进制某一位为 1 的坐标，这样可以把查找复杂度由 $O(\log n)$ 转化成 $O(1)$ 。使用二分查找的时间复杂度为 $O(n \log W +  q (\log n) (\log W) )  $ 。



```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
#define int long long 
#define debug(x)    std::cerr << #x << '=' << x << "\n"
#define println(...)  std::cerr << format(__VA_ARGS__) << std::endl
void solve() {
    int n;
    int q ,x;
    std::cin >> n >> q;

    std::vector<int> a(n + 2) , sum(n + 2,0);
    for(int i = 1;i <= n;i++) std::cin >> a[i], sum[i] = sum[i - 1] + a[i];


    std::vector<int> b[31];
    for(int i = 0;i<= 30;i++) {
        b[i] = std::vector<int>(n + 2 , 0);
    }
    for(int _ = 0;_<= 30;_++) {
        for(int i = 1;i <= n;i++) {
            b[_][i] = b[_][i - 1] + ((a[i] >> _) & 1);
        }
    }
    for(int i =1 ;i <= q;i++) {
        std::cin >> x;
        a[n + 1] = x;
        int ans = 0, rank = n + 1, _l = 0 , _r = n + 1;
        for(int j = 30;j>= 0 ;j--) {
            
            int k1 =(x & (1 << j)) > 0; 
            int k2 = k1 + b[j][n] - b[j][rank - 1];
            
            if(k2 & 1) {

                int t1 = lower_bound(b[j].begin() + _l ,b[j].begin() + _r,b[j][rank - 1]) - b[j].begin();
                _l = lower_bound(b[j].begin() + _l , b[j].begin() + _r ,b[j][rank - 1] - 1) - b[j].begin();
                
                rank = t1 + 1;
                _r = t1 + 1;

            } else {
                _l = lower_bound(b[j].begin() + _l , b[j].begin() + _r ,b[j][_r - 1]) - b[j].begin();
            }
            
        }
        rank = std::min(rank , _l + 1);
        std::cout << n + 1 - rank << " \n"[i == n];
    }
}

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
#ifdef  CXTEST
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);

#endif
    int t;
    std::cin >> t;
    while (t--)
        solve();
    return 0;
}
```

---

## 作者：yvbf (赞：0)

![](bilibili:BV19cAaeVEme?t=1373)

---

## 作者：Redshift_Shine (赞：0)

好题。

暴力往前吃显然无法符合时间限制，考虑优化。

考虑位运算的性质。

$x>y$ 的充分不必要条件是 $\operatorname{highbit}(x)>\operatorname{highbit}(y)$。

$x<y$ 的充分不必要条件是 $\operatorname{highbit}(x)<\operatorname{highbit}(y)$。

$x=y$ 的必要不充分条件是 $\operatorname{highbit}(x)=\operatorname{highbit}(y)$。

分情况讨论。

如果碰到一个 $\operatorname{highbit}$ 更大的数，显然无法吃掉，停下。

如果碰到一个 $\operatorname{highbit}$ 更小的数，显然可以吃掉，吃下。

如果碰到一个 $\operatorname{highbit}$ 相同的数，判断大小关系决定是否可以继续。

由此，可以对每个 $\operatorname{highbit}$ 预处理出前缀 $\operatorname{highbit}$ 更大或相同的最大位置，每次从 $\operatorname{highbit}$ 更大或相同的位置中选一个更大的往前跳即可。

时间复杂度 $O((n+q)\log v)$。

```c++
// #define Redshift_Debug
#ifdef Redshift_Debug
#define debug(...) fprintf(stderr, __VA_ARGS__)
#include <chrono>
#else
#define debug(...)
#endif
#include <cstdio>

using namespace std;
const int N = 2e5 + 10;
int hb[N], ps[N], idx;
int n, a[N], pfx[N], pfp[30][N], pfpeq[30][N], q;
void init_global()
{
}
void init_local()
{
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", a + i);
		pfx[i] = (pfx[i - 1] ^ a[i]);
		for (int j = 29; ~j; j--)
		{
			if (a[i] & (1 << j))
			{
				hb[i] = j;
				break;
			}
		}
	}
	for (int i = 0; i < 30; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			pfp[i][j] = pfp[i][j - 1];
			if (hb[j] > i)
				pfp[i][j] = j;
		}
	}
	for (int i = 0; i < 30; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			pfpeq[i][j] = pfpeq[i][j - 1];
			if (hb[j] == i)
				pfpeq[i][j] = j;
		}
	}
}
void run()
{
	for (int i = 1, x, thb, flg; i <= q; i++)
	{
		scanf("%d", &x);
		flg = 0;
		for (thb = 29; (~thb) and (x >> thb & 1 ^ 1); thb--)
			;
		for (int j = n; j; j--)
		{
			if (thb == -1)
			{
				printf("%d%c", n - j, " \n"[i == q]);
				flg = 1;
				break;
			}
			if (pfpeq[thb][j] > pfp[thb][j])
			{
				if (pfpeq[thb][j] != j)
					x ^= (pfx[j] ^ pfx[pfpeq[thb][j]]);
				if (x < a[pfpeq[thb][j]])
				{
					printf("%d%c", n - pfpeq[thb][j], " \n"[i == q]);
					flg = 1;
					break;
				}
				x ^= a[pfpeq[thb][j]];
				j = pfpeq[thb][j];
			}
			else
			{
				printf("%d%c", n - pfp[thb][j], " \n"[i == q]);
				flg = 1;
				break;
			}
			for (; (~thb) and (x >> thb & 1 ^ 1); thb--)
				;
		}
		if (flg)
			continue;
		printf("%d%c", n, " \n"[i == q]);
	}
}
int main()
{
#ifdef Redshift_Debug
	auto st = chrono::high_resolution_clock::now();
#endif
	int T = 1;
	scanf("%d", &T);
	init_global();
	while (T--)
	{
		init_local();
		run();
	}
#ifdef Redshift_Debug
	auto ed = chrono::high_resolution_clock::now();
	fprintf(stderr, "%.9lf\n", (ed - st).count() / 1e9);
#endif
}
```

---

