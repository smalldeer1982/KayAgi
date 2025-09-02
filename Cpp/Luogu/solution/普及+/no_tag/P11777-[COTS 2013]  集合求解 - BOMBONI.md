# [COTS 2013]  集合求解 / BOMBONI

## 题目描述

存在若干个集合（集合数量未知，不存在空集），给定 $n$，每个集合中元素 $x$ 满足 $1 \le x \le n$，你现在已知 $M$ 个集合内的元素情况。

定义全集 $U=\{1,2,\dots ,n\}$，这若干个集合间满足两个性质：

- 若集合 $A$ 存在，那么 $\complement_UA$ 也存在。
- 对于当前的两个集合 $A,B$，集合 $C=A \cup B$ 也存在。

希望你求出最小的集合数量，把它对 $10^9+9$ 取模的结果。

## 说明/提示

【样例解释】

- 对于第一个样例，集合为 $\{1,2\},\{3\},\{1,2,3\}$。

- 对于第二个样例，另外的 $5$ 个集合为 $\{1, 2, 9, 10\},\{1,2,3,4,7,8,9,10\},\{1,2,3,4,5,6,7,8,9,10\},\{3,4,7,8\},\{1,2,5,6,9,10\}$。

【数据范围与约定】

- 对于 $40\%$ 的数据，满足 $n \le 30$，答案不超过 $5000$。

- 对于 $100 \%$ 的数据，满足 $1\le n \le 2\times 10^5,1\le M \le 50$。

## 样例 #1

### 输入

```
3 
1 
2 1 2```

### 输出

```
3```

## 样例 #2

### 输入

```
10 
2 
6 3 4 5 6 7 8 
2 5 6```

### 输出

```
7```

# 题解

## 作者：Aurelia_Veil (赞：1)

# 题解：P11777 \[COTS 2013] 集合求解 / BOMBONI

什么啊，原来是结论题啊。

这道题我们看样例再手算几个样例，能够猜出，答案或许形式是 $2^k-1$。

我们通过猜出的结论来推理一下。首先，为什么要减 $1$，很容易猜到是排除了空集。其次，就要开始证明了。

我们先证明一个最基础的，就是通过补集和并集是可以得出交集的，证明如下：$\complement_U(\complement_UA \cup \complement_UB)=A \cap B$。

然后，我们发现，如果我们将元素分个块（如果两个元素所在的所有集合都是一样的，就合并），然后我们通过若干个操作，发现我们如何都不能拆分这个块（你可以试试哦），我们求出这些块的个数，再带入我们猜测的公式，却发现答案一模一样，为何？

我们很容易知道，如果有一个块，我们将这个元素所在的所有集合取交集，最终结果就是这个块，这很容易想到了，所以我们取交集后的最小单位就是这些块，所以最终简化为了我们取不取这个块，也就是两个选择，于是排除掉空集答案就是 $2^k-1$（$k$ 为块的个数）。

那块的个数怎么求？我们注意到 $1\le M \le 50$ 我们可以使用二进制存储，再去重即可咩。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+101;
const int mod=1e9+9;
long long q[N];
long long powd(long long x){
	if(!x){
		return 1;
	}
	if(x==1){
		return 2;
	}
	if(x%2==0){
		long long y=powd(x/2)%mod;
		return y*y%mod;
	}else{
		return powd(x-1)*2%mod;
	}
}
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int len;
		scanf("%d",&len);
		long long k=0;
		for(int j=1;j<=len;j++){
			int x;
			scanf("%d",&x);
			q[x]|=(1ll<<i);
		}
	}
	sort(q+1,q+n+1);
	int k=unique(q+1,q+n+1)-q-1;
	printf("%lld\n",((powd(k)-1)%mod+mod)%mod);
	return 0;
}
```

---

## 作者：Lucyna_Kushinada (赞：1)

# P11777 [COTS 2013] 集合求解 / BOMBONI

## 题意

存在若干个集合（集合数量未知，不存在空集），给定 $n$，每个集合中元素 $x$ 满足 $1 \le x \le n$，你现在已知 $M$ 个集合内的元素情况。

定义全集 $U=\{1,2,\dots ,n\}$，这若干个集合间满足两个性质：

- 若集合 $A$ 存在，那么 $\complement_UA$ 也存在。
- 对于当前的两个集合 $A,B$，集合 $C=A \cup B$ 也存在。

求出最小的集合数量，把它对 $10^9+9$ 取模的结果。

## 题解

知识点：集合。

启发：

- 没思路的话先打暴力找规律。

又要求最小，又要计数，仔细思考可以发现问的是所给的集合能通过题中操作产生多少种不同的集合，纯纯的计数题。

结论是过了之后才会证的。

打暴力找规律，发现答案都是形如 $2^k-1$ 的，于是开始往有关这方面的想。

根据高中集合知识可以知道 $A \cap B=\complement_U(\complement_UA\cup\complement_U B)$。

所以虽然题目没给出集合交的操作，但也是可以只用补集和集合并凑出来的。

设 $S_0=U$，$S_1\sim S_m$ 为题中给出集合。

这样题意便转化为了用 $S_0 \sim S_m$ 通过集合交、并操作能凑出多少种不同的集合。

考虑把 $1\sim n$ 划分为 $p$ 个集合，使其全体并集为 $U$，且两两无交，且其任意真子集都不能由 $S_0\sim S_m$ 通过若干次上述操作得到，则答案就是 $2^p-1$。

考虑怎样的集合，满足其任意真子集不能由 $S_0\sim S_m$ 通过若干次上述操作得到，当且仅当存在一个集合 $T$ 满足每个元素 $x$，都有 $\forall k \in T$，$x\in S_k$，也就相当于对于 $i\in [1,n]$ 算出其对应的 $T$，把 $T$ 相同的分到一组，设有 $p$ 组，答案则为 $2^p-1$。

这个过程可以用哈希实现。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define rep(i,l,r) for(int i=(l);i<=(r);++i)
#define per(i,l,r) for(int i=(r);i>=(l);--i)
#define pr pair<int,int>
#define fi first
#define se second
#define pb push_back
#define all(x) (x).begin(),(x).end()
#define sz(x) (int)(x).size()
#define bg(x) (x).begin()
#define ed(x) (x).end()

#define N 202505
#define int unsigned long long

const int mod=1e9+9;
int n,m,ha[N];

inline int qpow(int a,int b){
    int ans=1;

    while(b){
        if(b&1){
            ans=ans*a%mod;
        }
        a=a*a%mod;
        b>>=1;
    }

    return ans;
}

signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);

    cin>>n>>m;
    rep(i,1,m){
        int k,x;
        cin>>k;

        while(k--){
            cin>>x;
            ha[x]=ha[x]*131+i;
        }
    }

    vector<int>tmp;

    rep(i,1,n){
        tmp.pb(ha[i]);
    }

    sort(all(tmp));
    tmp.erase(unique(all(tmp)),ed(tmp));

    cout<<(qpow(2,sz(tmp))-1+mod)%mod;

    return 0;
}
```

---

## 作者：andychen_2012 (赞：1)

你如果多手模几个例子，你会发现，似乎答案的形式都为 $2^k-1$。

细细思考，你会发现这容易理解。对于两个元素 $x,y$，如果它们所出现的集合位置是相同的话，那么这两个元素可以看作同一类。因此对于每一类元素，其在一个集合中要么出现要么不出现，而且由于一个集合和它的补集都存在。所以集合数量就是 $2^k-1$，其中 $k$ 为元素种类数，而 $-1$ 对应着空集。

主要代码如下：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
ll mod=1e9+9;
int n,m;
ll a[200005];
int main(){
	n=read(),m=read();
	while(m--){
		int b=read();
		while(b--) a[read()]|=1ll<<m;
	}
	sort(a+1,a+n+1);
	n=unique(a+1,a+n+1)-(a+1);
	printf("%lld\n",fp(2,n)-1);
    return 0;
}
```

---

## 作者：buowen123 (赞：0)

手玩几个样例，可以发现如下并不显然的性质：
- 答案为 $2^q-1$ 的形式；
- 对于当前的两个集合 $A,B$，集合 $C=\complement_U(\complement_UA\cup\complement_UB)=A \cap B$ 也存在（也就是你可以取交）。
- 如果多个数所在的集合的编号构成的集合相同，这多个数可以看作同一类，不妨设有 $k$ 类。可以观察到 $q=k$。

稍微证明一下第三点。对于同一类数构成的集合 $X$，你给这些数所在的所有集合取交集，结果应该是 $X$ 本身。

这样你就可以得到所有同一类数构成的集合，将这些集合任意取并，你就可以得到 $2^k-1$ 个集合（此即为何 $q=k$）。减一是因为排除掉空集。

只需要判断每个数在哪些集合出现即可，因为 $M\le50$ 所以可以用一个 long long 存下来。时间复杂度 $O(nM+n\log n)$。

```cpp
#include <bits/stdc++.h>
#define add(x,y) (x+=y)>=p&&(x-=p)
using namespace std;
typedef long long ll;
const int maxn=2e5+5,p=1e9+9;
int n,m;
ll a[maxn];
void solve(){
	cin>>n>>m;
	for(int i=1,k,x;i<=m;i++){
		cin>>k;
		while(k--) cin>>x,a[x]|=(1ll<<i);
	}
	sort(a+1,a+n+1);
	int len=unique(a+1,a+n+1)-(a+1),res=1;
	while(len--) add(res,res);
	cout<<(res+p-1)%p;
}
signed main() {
	/* freopen("BOMBONI.in", "r", stdin); */ /* freopen("BOMBONI.out", "w", stdout); */
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int Hifumi = 1, Mika = 1; /* cin >> Hifumi; */ /* cin >> Mika; */
	/* assert(Hifumi >= 0 && Hifumi <= 10); */ while (Mika--) solve(); return 0;
}
```

---

