# [ARC149E] Sliding Window Sort

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc149/tasks/arc149_e

正整数 $ N,\ M,\ K $ が与えられます．正整数列 $ A\ =\ (A_0,\ \ldots,\ A_{N-1}) $ に対する次の操作を考えます．

- $ k=0,\ 1,\ \ldots,\ K-1 $ の順に次を行う．
  - $ A_{k\bmod\ N},\ A_{(k+1)\bmod\ N},\ \ldots,\ A_{(k+M-1)\bmod\ N} $ を昇順にソートする．つまり $ A_{k\bmod\ N},\ A_{(k+1)\bmod\ N},\ \ldots,\ A_{(k+M-1)\bmod\ N} $ を小さい方から順に並べたものを $ (x_0,\ \ldots,\ x_{M-1}) $ とするとき，各 $ 0\leq\ j\ <\ M $ に対して $ A_{(k+j)\bmod\ N} $ を $ x_j $ に置き換える．

$ 1 $ 以上 $ N $ 以下の整数からなる順列 $ B\ =\ (B_0,\ \ldots,\ B_{N-1}) $ が与えられます．正整数列 $ A $ であって，上記の操作を行った結果が $ B $ と一致するものの個数を $ 998244353 $ で割った余りを答えてください．

## 说明/提示

### 制約

- $ 2\leq\ N\leq\ 3\times\ 10^5 $
- $ 2\leq\ M\leq\ N $
- $ 1\leq\ K\leq\ 10^9 $
- $ 1\leq\ B_i\leq\ N $
- $ i\neq\ j $ ならば $ B_i\neq\ B_j $

### Sample Explanation 1

例えば $ A\ =\ (4,1,5,6,2,3) $ が条件を満たします．この $ A $ に対して，操作は次のように進行します． - $ k=0 $ に対する操作により，$ A $ は $ (1,4,5,6,2,3) $ になる． - $ k=1 $ に対する操作により，$ A $ は $ (1,4,5,6,2,3) $ になる． - $ k=2 $ に対する操作により，$ A $ は $ (1,4,2,5,6,3) $ になる． - $ k=3 $ に対する操作により，$ A $ は $ (1,4,2,3,5,6) $ になる． - $ k=4 $ に対する操作により，$ A $ は $ (6,4,2,3,1,5) $ になり，$ B $ に一致する．

### Sample Explanation 2

条件を満たす $ A $ は存在しません．

### Sample Explanation 3

$ 1 $ 以上 $ 20 $ 以下の整数からなる順列がすべて条件を満たします．

## 样例 #1

### 输入

```
6 3 5
6 4 2 3 1 5```

### 输出

```
18```

## 样例 #2

### 输入

```
6 3 5
6 5 4 3 2 1```

### 输出

```
0```

## 样例 #3

### 输入

```
20 20 149
13 14 15 16 17 18 19 20 1 2 3 4 5 6 7 8 9 10 11 12```

### 输出

```
401576539```

# 题解

## 作者：Alan_Zhao (赞：7)

## 题解

硬刚了三个半小时做出来了。

首先考虑 $K>N-M+1$ 的情况。在前 $N-M+1$ 次操作结束后，操作就开始绕圈了。此时一定是序列中的前 $(M-1)$ 大值聚在序列的最后。在接下来的操作中，一定是这 $M-1$ 个数绕着序列循环移动，每次把这一整段和它后面的第一个位置交换。

这个交换操作并不会影响什么，于是先考虑 $K=N-M+1$ 的情况。考虑题目中的操作，相当于：$B_i$ 是 $A_{0\dots (M+i-1)}$ 中删去 $B_0,\dots,B_{i-1}$ 再加入 $A_{M+i}$ 后的最小值。

可以发现：对于 $B$ 中一个是前缀最大值的位置 $i$，$B_i$ 可以填在 $A_{0\dots (M+i-1)}$ 中任意一个没被填过的位置，于是它可以使答案乘上 $M$；否则，一定有 $A_i=B_i$。

现在还有最大的 $M-1$ 个数没有确定填的位置。由于只剩下了 $M-1$ 个位置可填，所以将答案再乘上 $(M-1)!$ 即可。

再讨论一下 $K>N-M+1$ 的情况。我们只需要求出来在执行这 $K-(N-M+1)$ 次操作前，序列的开头是什么，然后变成 $K=N-M+1$ 的情况即可。可以发现，序列的开头一开始在 $0$，进行一次操作后变成了 $N-2$，此后每 $N-M+1$ 次操作会使得开头的位置循环左移 $M-1$。这样就求出了开头位置。

$K<N-M+1$ 的情况也是好处理的，只需要把序列末尾从来没变过的元素删去，然后把剩下的元素离散化一下，就也变成了 $K=N-M+1$ 的情况。

时间复杂度 $O(N)$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define For(Ti,Ta,Tb) for(int Ti=(Ta);Ti<=(Tb);++Ti)
#define Dec(Ti,Ta,Tb) for(int Ti=(Ta);Ti>=(Tb);--Ti)
#define Debug(...) fprintf(stderr,__VA_ARGS__)
#define range(Tx) begin(Tx),end(Tx)
using ll = long long;
const int N = 3e5 + 5, Mod = 998244353;
int n, m, k, b[N], a[N];
int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr);
	cin >> n >> m >> k;
	For(i, 0, n - 1) cin >> b[i];
	n = min(n, m + k - 1);
	vector<int> disc(b, b + n);
	sort(range(disc));
	For(i, 0, n - 1) b[i] = lower_bound(range(disc), b[i]) - disc.begin() + 1;
	int len = 0;
	ll ans = 1;
	int pos = (m + k - 2) % n;
	for (int i = 1, j = pos; i < m; ++i, j = (j - 1 + n) % n) {
		if (b[j] != n - i + 1) { cout << "0\n"; return 0; }
	}
	k -= n - m + 2;
	int p1 = ((n - m + 1 - 1LL * (m - 1) * (k / (n - m + 1))) % n + n) % n;
	for (int i = 0, j = p1; i < n; ++i, j = (j + 1) % n) {
		if (b[j] <= n - m + 1) a[len++] = b[j];
	}
	For(i, 1, m - 1) (ans *= i) %= Mod;
	int mx = 0;
	For(i, 0, len - 1) if (a[i] > mx) mx = a[i], (ans *= m) %= Mod;
	cout << ans << '\n';
	return 0;
}
```

---

## 作者：syzf2222 (赞：5)

可以把问题看作：有一个集合，一开始往里放 $m-1$ 个数，然后进行 $k$ 次操作，每次取出队首放入堆，然后把堆内最小值放在队尾。

容易发现，当 $k\geqslant n-m+1$ 时，最终的集合内都是最大的 $m-1$ 个数。所以 $n-m+1$ 以后的操作只是在循环移位。令 $R=n-m+1$，则若 $k>R$ 则容易还原为 $k=R$；若 $k<R$，则忽略那些未动过的数字，同样也可看作 $k=R$。

令 $b_1\sim b_k$ 为第 $1\sim k$ 次操作放入队尾的数字。若 $b_i<b_{i-1}$，则 $b_i$ 显然只能由自己产生，也就是 $a_{m-1+i}=b_i$。否则，它可以选择一个集合中的位置使之称为它。

最后还要给集合中的位置安排数字。所以答案为 $(m-1)!m^{\sum [b_i>b_{i-1}]}$。

```
#include<bits/stdc++.h>
using namespace std;
const int maxn=5e5+10;
const int mod=998244353;
#define inf 1e9
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
int n,m,k,R,ans=1,a[maxn],b[maxn];
int main(){
	n=read(),m=read(),k=read();R=n-m+1;
	for(int i=0;i<n;i++)a[i]=read();
	rotate(a,a+k%n,a+n);
	for(int i=m-1;i<n;i++)b[i-m+1]=a[i];
	if(k>R)rotate(b,b+(R-k%R)%R,b+R),k=R;
	for(int i=1;i<m-1;i++)ans&=(a[i]>a[i-1]);
	for(int i=0;i<k;i++)ans&=(a[0]>b[R-i-1]);
	for(int i=1;i<m;i++)ans=1ll*ans*i%mod;
	for(int i=R-k,las=0;i<R;i++)
		if(las<b[i])las=b[i],ans=1ll*ans*m%mod;
	printf("%d\n",ans);
	return 0;
}
```

深深地感到自己的弱小。

---

## 作者：dadaaa (赞：1)

# [AT_arc149_e](https://www.luogu.com.cn/problem/AT_arc149_e)

### 思路

好题，在和 @Bellala 老师的讨论下懂了。

首先看题目，考虑对于一个初始序列 $A$ 是怎么进行操作的。

观察到，在第 $n-m+1$ 轮操作以后，所有点都被考虑过了，此时整个序列最后 $m-1$ 个数一定是最大的 $m-1$ 个数，此后每次操作相当于将除去最大的几个数的数循环位移一格。此时如果我们把最大的 $m-1$ 个数组成的集合拎出来，后续操作就是把剩下的数排成序列，并进行循环位移。

如果操作数不足 $n-m+1$ 个，则剩下的没有进行操作的数是没有办法改变的，因此我们将前面的数离散化后又可以变成 $K=n-m+1$ 的情况了。

现在只需要考虑 $K=n-m+1$ 的情况。

这时候在第 $i$ 轮操作时，我们相当于是携带了 $A_0 \sim A_{m-1+i}$ 的最大的 $m-1$ 个数的集合，然后把 $A_{m+i}$ 加入集合，把集合里的最小元素填进 $B_{i}$。考虑和第一种情况相同的建模方法，我们同样将操作集合拎出来得到一个**新序列**，那么现在的操作就是把序列的第一个数加进操作集合，然后把操作集合的最小数放在序列末尾。

考虑转换成计数。

首先考虑无解的情况，因为你能够得知操作集合的位置了，而操作集合在**原最终序列**中的体现一定是升序的。所以只要不是，就无解。

然后，考虑**新最终序列**上的每一个数 $B_i$。如果这个数前面存在一个 $B_j \gt B_i$ ，那么因为一个更大的数都被弹掉了，所以操作集合中**在加入这个数前**不存在比 $B_j$ 小的数，因此一定是加入后立刻弹出，所以**新初始序列** $A_{i+m}=B_i$。否则，那么说明他可以填在任意一个还未被确定的位置上（有 $m$ 个），所以对答案的贡献是 $m$。

最后在乘上一个最大 $m-1$ 个值的随机排列数即可。

### 总结

可以固定一个动的位置来观测过程。

### 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 3e5 + 10;
const ll P = 998244353;
int n, m, K, b[N];
int tmp[N];
int main() {
	scanf("%d%d%d", &n, &m, &K);
	for (int i = 0; i < n; i++) scanf("%d", b + i);
	if (K < n - m + 1) {
		n = n - (n - m + 1 - K);
		for (int i = 0; i < n; i++) tmp[i] = b[i];
		sort(tmp, tmp + n);
		int cnt = unique(tmp, tmp + n) - tmp;
		for (int i = 0; i < n; i++) b[i] = lower_bound(tmp, tmp + cnt, b[i]) - tmp + 1;
	}//离散化
	int st = K % n, rev = K % (n - m + 1);
	rotate(b, b + st, b + n);
    //还原最后多余的操作
	rotate(b + m - 1, b + n - rev, b + n);
	//构建模型，其中前 m-1 个是操作集合，后面是新序列
	ll ans = 1;
	for (int i = 0; i < m - 1; i++) {
		if (b[i] != n - m + i + 2) {
			printf("0\n");
			return 0;
		}//无解
		ans = ans * (i + 1) % P;
	}
	int mx = 0;
	for (int i = m - 1; i < n; i++) {
		if (b[i] > mx) {
			mx = b[i];
			ans = ans * m % P;
		}
	}
	printf("%lld\n", ans);
	return 0;
}
// AT_arc149_e
```

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/AT_arc149_e)

**题目大意**

> 给定 $n,m,k$，对于 $n$ 阶排列 $a_0\sim a_{n-1}$，对于 $i=0,\dots,k-1$，我们依次对 $a{[i\bmod n,i+m\bmod n)}$ 升序排序，求有多少个 $\{a_i\}$ 操作后变成 $\{b_i\}$。
>
> 数据范围：$n\le 3\times 10^5$。

**思路分析**

首先我们观察到，在 $k=n-m+1$ 时性质比较理想：此时 $b_{n-m+1}\sim b_{n-1}$ 恰好是 $n-m+2\sim n$。

而前面的每个 $b_i$ 可以用堆维护，每次把 $a_{i+m-1}$ 插入堆，然后弹出堆中最小值作为 $b_i$。

记 $p=n-m+1$ 那么我们先考虑如何把其他情况转成 $k=p$ 的情况。

首先考虑 $k<p$，此时我们注意到所有操作只影响到了 $i\le k+m-1$ 的元素，可以只保留这段前缀并离散化作为新的 $b_i$。

然后考虑 $k>p$，此时我们要还原出 $p$ 次操作后 $b_i$ 的样子，首先  $n-m+2\sim n$ 在序列中一定占据 $b[k\bmod n,k+m-1\bmod n)$。

然后观察剩下的序列 $B'=B[k+m-1\bmod n,k\bmod n)$，我们发现再操作一次相当于把 $B'$ 向右循环移位一位，那么 $k-p$ 次操作之前的序列 $B'$ 占据 $b[0,p)$ 且相当于最终的 $B'$ 循环左移 $k-p$ 位。

然后考虑 $k=p$ 时的答案，首先我们只要考虑 $b[0,n-m]$ 中的元素。

首先如果 $b_{i-1}>b_i$，那么一定有 $a_{i+m-1}=b_i$，否则第 $i-1$ 次就会把 $b_i$ 弹出，然后我们就可以删掉这些 $b_i$，并不会影响整个过程中堆的变化。

然后我们在删除后的序列依然可以进行这样的操作，不停操作直到 $b_i$ 递增，此时从前往后每个 $b_i$ 都能随便填，每个数恰有 $i+m-1-(i-1)=m$ 种方法。

设原来的 $B'$  中 Localmax 有 $x$ 个，答案就是 $(m-1)!m^x$，其中 $(m-1)!$ 表示 $b[n-m+1,n)$ 可以随意填。

时间复杂度 $\mathcal O(n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=3e5+5,MOD=998244353;
int a[MAXN];
signed main() {
	int n,m,k;
	scanf("%d%d%d",&n,&m,&k);
	for(int i=0;i<n;++i) scanf("%d",&a[i]);
	n=min(n,k+m-1);
	vector <int> vals;
	for(int i=0;i<n;++i) vals.push_back(a[i]);
	sort(vals.begin(),vals.end());
	for(int i=0;i<n;++i) a[i]=lower_bound(vals.begin(),vals.end(),a[i])-vals.begin()+1;
	rotate(a,a+k%n,a+n);
	for(int i=0;i<m-1;++i) if(a[i]!=n-m+2+i) return puts("0"),0;
	for(int i=m-1;i<n;++i) a[i-m+1]=a[i];
	int p=n-m+1;
	if(k>n-m+1) rotate(a,a+(p-k%p)%p,a+p);
	int ans=1;
	for(int i=1;i<m;++i) ans=1ll*ans*i%MOD;
	for(int i=0,v=0;i<p;++i) if(a[i]>v) ans=1ll*ans*m%MOD,v=a[i];
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Feyn (赞：0)

[更多的 ARC 题目](https://www.cnblogs.com/Feyn/p/16977678.html)

相对有趣的题目，是不是 D 太难了搞得 E 难度评分特别高啊。

毛估估一个关键的时间点，比如说 $k=n-m+1$ 之后，整个数列中最大的 $m-1$ 个数被排列到了数组的最后，剩下的数以某种比较奇妙的方式排列在前面。之后的操作似乎变得无聊起来，由于当前窗口内的数是最大的那些了，所以它会让所有遇到的数放到尾巴后面，于是乎数列整体的架构（也就是较小的那些数的相对位置）是不会发生变化的，所以可以直接回溯到上面所述的那个时间点，思考有多少合法序列满足条件。

令此时希望得到的数列是 $a$，原来的数列是 $b$，那么画图发现如果 $a_x<a_{x-1}$，那么说明 $b_{x+m-1}$ 应该恰好等于 $a_x$。否则条件等价于前缀未确定的数中存在一个 $a_x$，并且其它的数都大于 $a_x$。而 $k=x-1$ 时也应该有一个所有数大于 $x$ 的限制，两相对比就能得到一些情况下 $a_x$ 的位置也是可以确定的。顺着做就可以了，把每个值可能选到的位置乘起来再乘上最后尾巴上一点数的决策就是答案了。

至于没有到达关键时间点的询问只需要把前缀当成一整个序列即可。

```cpp
#include<bits/stdc++.h>
// #define feyn
#define int long long
using namespace std;
const int N=300010;
const int mod=998244353;
inline void read(int &wh){
    wh=0;int f=1;char w=getchar();
    while(w<'0'||w>'9'){if(w=='-')f=-1;w=getchar();}
    while(w<='9'&&w>='0'){wh=wh*10+w-'0';w=getchar();}
    wh*=f;return;
}

int m,n,ti,a[N],b[N],qc[N],cnt;
inline int pre(int wh){return wh==1?m:wh-1;}
inline int suf(int wh){return wh==m?1:wh+1;}

signed main(){
	
	#ifdef feyn
	freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    #endif

    read(m);read(n);read(ti);
    for(int i=1;i<=m;i++)read(a[i]);
    
    if(ti<m-n+1){
        for(int i=1;i<=ti+n-1;i++)qc[++cnt]=a[i];
        sort(qc+1,qc+cnt+1);
        for(int i=1;i<=ti+n+1;i++)a[i]=lower_bound(qc+1,qc+cnt+1,a[i])-qc;
        m=ti+n-1;
    }
    else{
        int px=0,py=0;ti-=(m-n+1);
        for(int i=1;i<=m;i++){
            if(a[i]==m)py=i;
            if(a[i]==m-n+2)px=i;
        }
        if((py+m-px)%m!=n-2)return puts("0"),0;
        for(int i=1;i<=m-n+1;i++){
            int num=ti/(m-n+1)+(ti%(m-n+1)>=i);
            int np=((i-1-num*(n-1))%m+m)%m+1;
            b[i]=a[np];
        }
        int cnt=m-n+1;
        for(int i=px;cnt<=m;i=suf(i))b[++cnt]=a[i];
        for(int i=1;i<=m;i++)a[i]=b[i];
    }

    for(int i=1;i<=m;i++)b[i]=a[i];
    sort(b+1,b+m+1);
    for(int i=1;i<=m;i++){
        if(b[i]!=i)return puts("0"),0;
    }
    for(int i=m-n+2;i<=m;i++){
        if(a[i]!=i)return puts("0"),0;
    }
    int preMin=a[1],ans=n;
    for(int i=2;i<=m-n+1;i++){
        int now=a[i];
        if(a[i]<preMin)continue;
        ans=ans*n%mod;
        preMin=max(preMin,now);
    }
    for(int i=1;i<n;i++)ans=ans*i%mod;
    printf("%lld\n",ans);

    return 0;
}
```

---

