# Vasya and Good Sequences

## 题目描述

Vasya has a sequence $ a $ consisting of $ n $ integers $ a_1, a_2, \dots, a_n $ . Vasya may pefrom the following operation: choose some number from the sequence and swap any pair of bits in its binary representation. For example, Vasya can transform number $ 6 $ $ (\dots 00000000110_2) $ into $ 3 $ $ (\dots 00000000011_2) $ , $ 12 $ $ (\dots 000000001100_2) $ , $ 1026 $ $ (\dots 10000000010_2) $ and many others. Vasya can use this operation any (possibly zero) number of times on any number from the sequence.

Vasya names a sequence as good one, if, using operation mentioned above, he can obtain the sequence with [bitwise exclusive or](https://en.wikipedia.org/wiki/Exclusive_or) of all elements equal to $ 0 $ .

For the given sequence $ a_1, a_2, \ldots, a_n $ Vasya'd like to calculate number of integer pairs $ (l, r) $ such that $ 1 \le l \le r \le n $ and sequence $ a_l, a_{l + 1}, \dots, a_r $ is good.

## 说明/提示

In the first example pairs $ (2, 3) $ and $ (1, 3) $ are valid. Pair $ (2, 3) $ is valid since $ a_2 = 7 \rightarrow 11 $ , $ a_3 = 14 \rightarrow 11 $ and $ 11 \oplus 11 = 0 $ , where $ \oplus $ — bitwise exclusive or. Pair $ (1, 3) $ is valid since $ a_1 = 6 \rightarrow 3 $ , $ a_2 = 7 \rightarrow 13 $ , $ a_3 = 14 \rightarrow 14 $ and $ 3 \oplus 13 \oplus 14 = 0 $ .

In the second example pairs $ (1, 2) $ , $ (2, 3) $ , $ (3, 4) $ and $ (1, 4) $ are valid.

## 样例 #1

### 输入

```
3
6 7 14
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4
1 2 1 16
```

### 输出

```
4
```

# 题解

## 作者：开始新的记忆 (赞：16)

题目大意：现在有n个数，你可以进行任意次如下操作：将二进制下的一个数中的两个位置交换，问你一番操作后能不能使得这n个数的异或和为0，求出有多少个序列。

大致思路：首先我们看一下异或和为0需要什么条件。不难发现，只有当每一位上1的个数为偶数个的时候那这一位的异或和就是0，由此推出，这n个数转为二进制后1的个数为偶数个。于是我们可以利用前缀和来维护，每次O（1）的查询。

但是，仅仅是这样是不够的，因为还有一种情况，比如4 63 2 2 3这组数据如果按照刚刚的算法看是可行的，但是没法操作，因为63的1的个数为6，其他为1 1 2，于是我们又知道了一个条件：一段数中的最大的1的个数不超过总共1的个数/2。

因为每个数都至少可以提供一个在二进制下的1的个数，所以每次我们查询最大值都只需要在前64个数里面找，如果超过了64那么就只需要满足1的个数为偶数即可。

```
#include <bits/stdc++.h>
using namespace std;
int n,anss[300010],num[300010],cnt[2]={1};
long long ans=0;

int main() 
{	cin>>n;
	for(int i=1;i<=n;++i)
	{
		long long x;
		cin>>x;
		while(x>0)
		{
			num[i]+=(x%2);
			x/=2;
		}
		anss[i]=anss[i-1]+num[i];
		ans+=cnt[anss[i]%2];
		for(int j=i,k=i+1,maxn=0;j>=1 && j>=i-64;--j)
		{
            while(k>j) 
				maxn=max(maxn,num[--k]);
            if(maxn*2>anss[i]-anss[j-1] && anss[i]%2==anss[j-1]%2) 
				--ans;
        }
        ++cnt[anss[i]%2];
	}
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：蒟酱 (赞：6)

题意：给定一个序列，你可以对每个数字二进制位上的 $1$ 进行任意排布，问有多少子串满足异或和为 $0$。  
因为可以任意排布，所以只需要保留二进制下 $1$ 的数量即可。满足异或和为 $0$，就要保证这个子串的二进制下 $1$ 的数量之和为偶数，才能让每一个 $1$ 相互抵消。另外，最多的那个 $1$ 的数量不能超过子串二进制下 $1$ 的数量之和的一半，因为不能把最大的数的 $1$ 移动到别的数上，这样无法抵消全部的 $1$。  
如果只考虑偶数，直接枚举每个子串的复杂度是 $\mathcal O(n^3)$ 的，切换枚举顺序可以到 $\mathcal O(n^2)$，采用前缀和可以到 $\mathcal O(n)$。前缀和优化的意思是如果 $\sum_{i=1}^np_i$ 和 $\sum_{j=1}^np_j$ 在模 $2$ 意义下同余，那么 $\sum_{k=i+1}^jp_k$ 模 $2$ 一定是 $0$，$[i+1,j]$ 就满足了偶数的性质，开个记录前缀余数的桶扫一遍就行了。  
但是还要考虑最大不超过一半这个限制，题目保证 $a_i\ge1$ 也就是说每个数的二进制下 $1$ 的数量至少是 $1$，又因为 $a_i\le 10^{18}$，每个数的二进制下 $1$ 的数量最多才 $59$，只需要枚举所有长度小于 $60$ 的子串，如果这个子串的二进制下 $1$ 的数量正好是偶数并且满足最大超过一半，那么就把答案减去 $1$ 即可，长度大于等于 $60$ 的子串，就算一个数拉满二进制下 $1$ 的数量是 $59$，别的数摆烂是 $1$，也是符合要求的。
复杂度根据 `__builtin_popcount` 的实现，复杂度是 $\mathcal O(60n+n\log\log w)$ 到 $\mathcal O(60n)$。  
放个代码：（感觉比题解里的简短）
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cassert>
#define siz(x) int((x).size())
#define cauto const auto
#define all(x) (x).begin(),(x).end()
using std::cin;using std::cout;
using loli=long long;
using venti=__int128_t;
using pii=std::pair<int,int>;
constexpr int kN=3e5+1;
int n,a[kN],cnt[]={1,0},sum;
loli ans;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);cin.tie(nullptr);
	cin>>n;
	for(int i=1;i<=n;i++){loli x;cin>>x;a[i]=__builtin_popcountll(x);}
	for(int l=1;l<=n;l++){
		ans+=cnt[(sum+=a[l])&1]++;
		for(int r=l,max=0,num=0;r<=std::min(n,l+58);r++)
			max=std::max(max,a[r]),
			ans-=(num+=a[r])%2==0&&2*max>num;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Itst (赞：3)

考虑到能够交换两个二进制位，那么一个数产生的贡献就只和它的二进制的$1$的个数相关，我们将$a$数组转化为$b$数组，其中$b_i$为$a_i$的二进制位数，而$sum_i$为$b_i$的前缀和。

然后我们考虑统计答案。显然我们需要统计区间和为偶数的区间，也就是$\sum\limits_i \sum\limits_{j=0}^{i-1} [sum_i \% 2 == sum_j \% 2]$。我们需要求一个前缀和：$cnt_{i,0/1}$表示$sum_1$到$sum_i$中$mod \, 2 = 0/1$的数量，这样就可以$O(64N)$计算上面的式子了。但是我们少考虑了一个问题：如果区间满足和为偶数，但是其中有一个数的二进制位数很大，以至于其他的二进制数加起来都抵不过它（即$\max\limits_{k=i+1} ^ j {b_k} \times 2 > sum_j-sum_i$），意味着这个区间不合法，但是我们统计进去了。

那么就有两种解决办法：

①因为与最大值相关，所以考虑最大值分治。设$right_{i,j}$表示使得$sum_x - sum_{i-1} > 2 \times j$的最小的$x$，不存在则为$N+1$，又设$left_{i,j}$表示使得$sum_i - sum_{x - 1} > 2 \times j$的最大的$x$，用双指针预处理这两个数组。每一次在当前解决的区间上找到最大值，分治下去，对于当前的这一段区间，找大小比较小的那一段，利用$left,right,cnt$可以$O(1)$得到与$i$匹配的左/右端点的数量。复杂度$O(N(logN+64))$，时空无一被爆踩，唯一的优越性可能就在于可以做$a_i=0$的情况吧（强行安慰自己qwq）

②可以发现最大的元素不会大于$64$。那么对于每一个点，当它为右端点时，实际上最多只会有$64$个左端点有可能不合法，暴力把这$64$个端点扫一遍就行了。复杂度$O(64N)$

第②种解法代码直接去看$Tutorial$吧，下面放一下第①中做法的$Code$，毕竟跟我一样整天想着奇奇怪怪的算法把简单的题目搞得很难的人应该也不少吧（再次强行安慰自己）

```cpp
#include<bits/stdc++.h>
#define ull unsigned long long
using namespace std;

inline ull read(){
    ull a = 0;
    char c = getchar();
    while(!isdigit(c))
        c = getchar();
    while(isdigit(c)){
        a = (a << 3) + (a << 1) + (c ^ '0');
        c = getchar();
    }
    return a;
}

const int MAXN = 3e5 + 10;
int num[MAXN] , rig[MAXN][65] , lef[MAXN][65] , cnt[MAXN][2] , sum[MAXN] , ST[21][MAXN] , logg2[MAXN] , N;
long long ans;

inline int cmp(int a , int b){
    return num[a] > num[b] ? a : b;
}

void init_st(){
    for(int i = 2 ; i <= N ; ++i)
        logg2[i] = logg2[i >> 1] + 1;
    for(int i = 1 ; 1 << i <= N ; ++i)
        for(int j = 1 ; j + (1 << i) - 1 <= N ; ++j)
            ST[i][j] = cmp(ST[i - 1][j] , ST[i - 1][j + (1 << (i - 1))]);
}

inline int query(int x , int y){
    int t = logg2[y - x + 1];
    return cmp(ST[t][x] , ST[t][y - (1 << t) + 1]);
}

void solve(int l , int r){
    if(l > r)
        return;
    if(l == r){
        ans += num[l] == 0;
        return;
    }
    int k = query(l , r);
    //cout << l << ' ' << r << ' ' << k << endl;
    solve(l , k - 1);
    solve(k + 1 , r);
    if(k - l < r - k)
        for(int i = k ; i >= l ; --i)
            ans += cnt[r][sum[i - 1] & 1] - cnt[min(max(k - 1 , rig[i][num[k]] - 1) , r)][sum[i - 1] & 1];
    else
        for(int i = k ; i <= r ; ++i)
            if(lef[i][num[k]] >= l)
                ans += cnt[min(k - 1 , lef[i][num[k]] - 1)][sum[i] & 1] - (l == 1 ? 0 : cnt[l - 2][sum[i] & 1]);
    //cout << l << ' ' << r << ' ' << ans << endl;
}

int main(){
    N = read();
    cnt[0][0] = 1;
    for(int i = 1 ; i <= N ; ++i){
        ull a = read();
        while(a){
            if(a & 1)
                ++num[i];
            a >>= 1;
        }
        sum[i] = sum[i - 1] + num[i];
        cnt[i][0] = cnt[i - 1][0] + !(sum[i] & 1);
        cnt[i][1] = cnt[i - 1][1] + (sum[i] & 1);
        ST[0][i] = i;
        //cout << num[i] << ' ';
    }
    for(int i = 0 ; i <= 64 ; ++i){
        int p = 0;
        for(int j = 1 ; j <= N ; ++j)
            while(p < j && sum[j] - sum[p] >= i << 1)
                rig[++p][i] = j;
        while(p < N)
            rig[++p][i] = N + 1;
        for(int j = N ; j ; --j)
            while(p >= j && sum[p] - sum[j - 1] >= i << 1)
                lef[p--][i] = j;
    }
    init_st();
    //cout << endl;
    solve(1 , N);
    cout << ans;
    return 0;
}

```
欢迎来踩我的[blog](https://www.cnblogs.com/Itst/p/10089568.html) qaq

---

## 作者：WZKQWQ (赞：1)

首先，因为我们可以随意排列 $1$，所以只和 $1$ 的个数有关而与位置无关。然后，一段区间异或和为 $0$ 那么这段区间 $1$ 的个数一定是偶数，并且不能有一个数的 $1$ 的个数超过一半（超过了就消不了）。

然后还是不会做，我们考虑正难则反，求异或和不可能为 $0$ 的， 我们可以先求 $1$ 的个数为奇数的区间个数，这个可以简单 DP 求得，然后我们发现 $1\le a_i \le 10^{18}$，所以每个 $a_i$ 至少包含一个 $1$，至多包含 $60$ 个 $1$，所以区间长度超过 $120$ 的包含偶数个 $1$ 的区间一定合法，所以我们暴力判断区间长度 $\le120$ 的包含偶数个 $1$ 的区间合不合法即可。

复杂度 $O(n\log V)$，代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 300005;
int n,a[N],f[N][2],cnt;
typedef long long ll;
ll ans;
pair<int,int> o[N];
int main(){
	scanf("%d",&n);
	a[0] = a[n + 1] = 1;
	for(int i = 1;i <= n;++i){
		long long x;
		scanf("%lld",&x);
		while(x){
			if(x & 1) ++a[i];
			x >>= 1;
		}
		if(a[i - 1] % 2 == 0) f[i][0] = f[i - 1][0] + 1;
		else f[i][0] = 1;
	} 
	for(int i = n;i;--i) if(a[i + 1] % 2 == 0) f[i][1] = f[i + 1][1] + 1;
	else f[i][1] = 1;
	for(int i = 1;i <= n;++i) if(a[i] & 1) o[++cnt] = {f[i][0],f[i][1]};
	ll tmp[2];
	tmp[0] = tmp[1] = 0;
	for(int i = 1;i <= cnt;++i){
		tmp[i & 1] += o[i].first;
		ans += o[i].second * tmp[i & 1];
	}
	//cout << ans << endl;
	for(int i = 1;i <= n;++i){
		int sum = 0,mx = 0;
		for(int j = 1;j <= 128;++j){
			if(i + j - 1 > n) break;
			sum += a[i + j - 1];
			mx = max(mx,a[i + j - 1]);
			if(sum % 2 == 0 && mx > sum / 2) ++ans;
		}
	}
	cout << (ll)n * (n + 1) / 2 - ans << endl;
	return 0;
}
```


---

## 作者：Jsxts_ (赞：1)

套路题。

一个结论：设第 $i$ 个数 $1$ 的个数为 $a_i$，一个区间的数操作后异或和为 $0$，当且仅当这个区间 $a$ 的和 $sum$ 为偶数且 $a$ 中最大的数不超过 $sum$ 的一半。

看到最大值，考虑一个经典套路：预处理 $a_i$ 作为最大值的区间 $[L,R]$，然后枚举短区间，另一边双指针扫到和 $\ge a_i\times 2$ 的位置。假设枚举的是左区间，右边满足 $sum\ge a_i\times2$ 的区间为 $[x,R]$，此时和可以表示为 $pre[x]-pre[j-1]$ （$j$ 是左区间枚举的位置），那只要维护区间中 $pre$ 为奇数、偶数的个数就可以计算答案，枚举右区间同理。

时间复杂度 $O(n\log n)$（枚举短区间是 $O(n\log n)$ 的，因为本质上是笛卡尔树上跑 $\text{dsu on tree}$）。目前最优解。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
inline ll read() {
	ll s = 0,f = 1;char ch = getchar();
	while (!isdigit(ch)) f = ch == '-' ? -1 : 1, ch = getchar();
	while (isdigit(ch)) s = (s << 3) + (s << 1) + ch - '0', ch = getchar();
	return s*f;
}
int n,a[300010],pre[300010][3];
int st[300010],top,L[300010],R[300010];
int main() {
	n = read();
	pre[0][0] = 1;
	for (int i = 1;i <= n;i ++ ) {
		a[i] = __builtin_popcountll(read());
		while (top && a[st[top]] < a[i]) R[st[top--]] = i;
		L[i] = st[top], st[++top] = i;
		pre[i][2] = pre[i-1][2] + a[i];
		pre[i][0] = pre[i-1][0] + (pre[i][2] % 2 == 0);
		pre[i][1] = pre[i-1][1] + (pre[i][2] % 2 == 1);
	}
	while (top) L[st[top]] = st[top-1], top --;
	for (int i = 1;i <= n;i ++ ) if (!R[i]) R[i] = n + 1;
//	for (int i = 1;i <= n;i ++ ) cout << a[i] << ' ' << L[i] << ' ' << R[i] << endl;
	ll ans = 0;
	for (int i = 1;i <= n;i ++ ) {
		int l = L[i] + 1,r = R[i] - 1;
		if (i - l < r - i) {
			int x = i;
			for (int j = l;j <= i;j ++ ) {
				int t = pre[j - 1][2] % 2;
				while (x < r && pre[x][2] - pre[j - 1][2] < a[i] * 2) x ++;
				if (pre[x][2] - pre[j - 1][2] >= a[i] * 2) ans += pre[r][t] - pre[x-1][t];
			}
		}
		else {
			int x = i;
			for (int j = r;j >= i;j -- ) {
				int t = pre[j][2] % 2;
				while (x > l && pre[j][2] - pre[x - 1][2] < a[i] * 2) x --;
				if (pre[j][2] - pre[x - 1][2] >= a[i] * 2) ans += pre[x-1][t] - (l > 1 ? pre[l-2][t] : 0);
			}
		}
	}
	cout << ans;
	return 0;
}
```


---

## 作者：cike_bilibili (赞：0)

# 思路
很明显答案与每个数的二进制下 $1$ 的个数 $cnt$ 有关，考虑一个区间合法的条件。

很多个数异或其实可以看作都为 $1$ 的数位进行抵消，所以一个区间合法必须满足区间内每个数的 $cnt$ 之和是偶数，但这还不够。我们将区间 $[l,r]$ 之间的 $cnt$ 最大值记为 $mcnt$，显然必须满足 $\sum_{i=l}^{r} cnt_i - mcnt \ge mcnt$，可以理解为除开 $mcnt$ 以外的 $cnt$ 必须能够覆盖 $mcnt$ 才行，移项后得 $\sum_{i=l}^{r} cnt_i \ge 2 \cdot mcnt$。

区间和容易想到前缀和，式子变为 $pre_r-pre_l \ge 2 \cdot max_{i=l+1}^{r} cnt_i $，区间最大值贡献问题，考虑笛卡尔树上定一求一，每次枚举子树较小的一棵子树，根据启发式合并的证明，这是 $O(n \log n)$ 的。我们开两棵值域线段树，一棵维护 $pre$ 是奇数的个数，另一棵维护偶数，每次回溯时线段树合并即可。

时间复杂度 $O(n\log n \log V)$，其中 $V$ 是值域范围，空间复杂度 $O(n \log V)$。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ls tree[i].lson
#define rs tree[i].rson
using namespace std;
inline ll read(){
	ll ans=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		ans=(ans<<1)+(ans<<3)+ch-'0';
		ch=getchar();
	}
	return w*ans;
}
const int V=19200000;
int n,m;
ll a[300005];
int pre[300005]; 
struct Stack{
	ll val,id;
}stk[300005];
int top;
int L[300005],R[300005],fa[300005];
int rt;
int Root[300005][2];
struct Segment_tree{
	struct tree{
		int lson;
		int rson;
		int val;
	}tree[7000005];
	int tim;
	void pushup(int i){
		tree[i].val=tree[ls].val+tree[rs].val;
	}
	void add(int &i,int l,int r,int pos,int val){
		if(!i)i=++tim;
		if(l==r){
			tree[i].val+=val;
			return ;
		}
		int mid=l+r>>1;
		if(mid>=pos)add(ls,l,mid,pos,val);
		else add(rs,mid+1,r,pos,val);
		pushup(i);
	}
	int ask(int i,int l,int r,int L,int R){
		if(l>R||r<L)return 0;
		if(l>=L&&r<=R)return tree[i].val;
		int mid=l+r>>1;
		return ask(ls,l,mid,L,R)+ask(rs,mid+1,r,L,R);
	}
	int merge(int x,int y,int l,int r){
		if(!x||!y)return x|y;
		if(l==r){
			tree[x].val+=tree[y].val;
			return x;
		}
		int mid=l+r>>1;
		tree[x].lson=merge(tree[x].lson,tree[y].lson,l,mid);
		tree[x].rson=merge(tree[x].rson,tree[y].rson,mid+1,r);
		pushup(x);
		return x;
	}
}T[2];
ll ans=0;
int sz[300005];
void calc(int x,int rt,int opt){
	if(!x)return;
	calc(L[x],rt,opt),calc(R[x],rt,opt);
	if(opt==1){
		ans+=T[pre[x]%2].ask(Root[L[rt]][pre[x]%2],0,V,0,pre[x]-2*a[rt]);
	}else{
		ans+=T[pre[x]%2].ask(Root[R[rt]][pre[x]%2],0,V,pre[x]+2*a[rt],V);
	}
}
void dfs(int x){
	if(!x)return;
	sz[x]=1;
	dfs(L[x]),dfs(R[x]);
	sz[x]+=sz[L[x]]+sz[R[x]];
	if(sz[L[x]]>sz[R[x]]){
		calc(R[x],x,1);
		ans+=T[pre[x]%2].ask(Root[L[x]][pre[x]%2],0,V,0,pre[x]-2*a[x]);
		ans+=T[pre[x-sz[L[x]]-1]%2].ask(Root[R[x]][pre[x-sz[L[x]]-1]%2],0,V,pre[x-sz[L[x]]-1]+2*a[x],V);
		if(sz[L[x]]&&pre[x]%2==pre[x-sz[L[x]]-1]%2&&pre[x]-pre[x-sz[L[x]]-1]>=2*a[x])++ans;
	}else{
		calc(L[x],x,0);
		ans+=T[pre[x]%2].ask(Root[L[x]][pre[x]%2],0,V,0,pre[x]-2*a[x]);
		ans+=T[pre[x-sz[L[x]]-1]%2].ask(Root[R[x]][pre[x-sz[L[x]]-1]%2],0,V,pre[x-sz[L[x]]-1]+2*a[x],V);
		if(sz[L[x]]&&pre[x]%2==pre[x-sz[L[x]]-1]%2&&pre[x]-pre[x-sz[L[x]]-1]>=2*a[x])++ans;
	}
	T[pre[x]%2].add(Root[x][pre[x]%2],0,V,pre[x],1);
	Root[x][0]=T[0].merge(Root[x][0],Root[L[x]][0],0,V);
	Root[x][0]=T[0].merge(Root[x][0],Root[R[x]][0],0,V);
	Root[x][1]=T[1].merge(Root[x][1],Root[L[x]][1],0,V);
	Root[x][1]=T[1].merge(Root[x][1],Root[R[x]][1],0,V);
}
signed main(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++){
		ll x=a[i];
		ll cnt=0;
		while(x){
			if(x%2ll==1ll)++cnt;
			x>>=1ll;
		}
		a[i]=cnt;
		pre[i]=pre[i-1]+a[i];
	}
	for(int i=1;i<=n;i++){
		while(top&&a[i]>stk[top].val)L[i]=stk[top--].id;
		if(top)R[stk[top].id]=i;
		stk[++top]={a[i],i};
	}
	for(int i=1;i<=n;i++)fa[L[i]]=fa[R[i]]=i;
	for(int i=1;i<=n;i++)if(!fa[i])rt=i;
	dfs(rt);
	cout<<ans<<'\n';
} 
```
# 后记
一道绿题是怎么想出来这么麻烦还这么劣的做法的。

---

## 作者：Lyccrius (赞：0)

考虑什么样的区间是合法的。

由于我们可以进行无数次操作，因此我们不关心二进制上的每个一分别在哪，而只关心一的个数。

如果一个区间内一的个数为奇数，那么不论怎么挪都无法使异或和为 $0$。

再来看看个数为偶数时，如果有一个元素的一的个数超过了这一段区间一地个数的一半，那么也是不合法的。

统计一的个数可以用前缀和做到 $\mathcal O(1)$，但是区间内最大值不行。

我们还注意到一个平平无奇但确实存在的性质，$1 \le a_i$，那么每个 $a_i$ 至少有一个 $1$。

而且 $a_i$ 在二进制下一共有 $64$ 位，那么最大值的上限就是 $64$。

结合以上两条，可以得出一个结论，当区间长度大于 $64$ 是无需考虑最大值的影响。

那么对于每一个区间的左（右）端点，最多有 $64$ 个对立端点可能是受最大值影响而不合法的，依次检查就行了，虽然常数很大但是不影响。

时间复杂度 $\mathcal O(n)$。

---

## 作者：Graphcity (赞：0)

容易发现答案只和每个数字中二进制 1 的个数有关。

考虑序列 $a_{1\dots n}$，每个数的二进制 1 的个数分别为 $b_{1\dots n}$。

每次异或相当于取不同的两个数的一位，配对后抵消。这是个经典的贪心问题，匹配次数至多为 $\min(\lfloor \dfrac{sum}{2}\rfloor,sum-\max b_i)$。证明如下：

- 如果最大值大于和的一半，那么根本匹配不完这个数，答案为 $sum-\max b_i$。
- 否则，根据摩尔投票法，每次将当前的最大值与随便一个数匹配，这样一定能够尽量匹配完，答案为 $\lfloor \dfrac{sum}{2}\rfloor$。

根据这个结论，我们可以发现，一个序列能够匹配完，当且仅当最大值小于等于和的一半且和为偶数。

又因为 $a_i>0$，且 $\max b_i\le 64$，所以序列长度 $>128$ 时必然不存在超过和的一半的最大值，这个时候应用前缀和计算即可。序列长度 $\le 128$ 时直接暴力算。时间复杂度 $O(n)$，带了个 $128$ 的常数。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=3e5;

inline ll read()
{
    char ch=getchar();
    ll f=1,x=0;
    while(ch>'9' || ch<'0')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

int n,pop[Maxn+5],all[Maxn+5][2];
ll val[Maxn+5],ans;

int main()
{
    n=read();
    For(i,1,n)
    {
        val[i]=read();
        For(j,0,61) if(val[i]&(1ll<<j)) pop[i]++;
    }
    int res=0;
    For(i,1,n) res+=pop[i],all[i][res&1]++;
    For(i,1,n) For(j,0,1) all[i][j]+=all[i-1][j]; 
    For(i,1,n)
    {
        int sum=0,mx=0;
        For(j,1,128)
        {
            if(i+j-1>n) break;
            sum+=pop[i+j-1],mx=max(mx,pop[i+j-1]);
            if(sum%2==0 && mx*2<=sum) ans++;
        }
    }
    res=0;
    For(i,1,n-128)
    {
        ans+=(all[n][res]-all[i+127][res]);
        res=(res+pop[i])&1;
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

