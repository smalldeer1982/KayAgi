# [ARC170B] Arithmetic Progression Subsequence

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc170/tasks/arc170_b

$ 1 $ 以上 $ \textbf{10} $ 以下の整数からなる長さ $ N $ の数列 $ A $ が与えられます．

$ 1\leq\ l\ \leq\ r\leq\ N $ を満たす整数組 $ (l,r) $ であって，以下の条件を満たすものを良い組と呼びます．

- 数列 $ (A_l,A_{l+1},\ldots,A_r) $ は長さ $ 3 $ の等差数列を（連続とは限らない）部分列として含む．より厳密には，$ l\ \leq\ i\ <\ j\ <\ k\leq\ r $ を満たす整数組 $ (i,j,k) $ であって， $ A_j\ -\ A_i\ =\ A_k\ -\ A_j $ なるものが存在する．
 
良い組の個数を求めてください．

## 说明/提示

### 制約

- $ 3\ \leq\ N\ \leq\ 10^5 $
- $ 1\leq\ A_i\ \leq\ 10 $
- 入力される数値は全て整数
 
### Sample Explanation 1

良い組は $ (l,r)=(1,4),(1,5),(2,5) $ の $ 3 $ つです． 例えば，数列 $ (A_1,A_2,A_3,A_4) $ は $ (5,3,1) $ という長さ $ 3 $ の等差数列を部分列として含むので $ (1,4) $ は良い組です．

### Sample Explanation 2

良い組が存在しない場合もあります．

## 样例 #1

### 输入

```
5
5 3 4 1 5```

### 输出

```
3```

## 样例 #2

### 输入

```
3
1 2 1```

### 输出

```
0```

## 样例 #3

### 输入

```
9
10 10 1 3 3 7 2 2 5```

### 输出

```
3```

# 题解

## 作者：Register_int (赞：4)

枚举左端点 $l$，计算这样的区间有多少种后求和就能求出答案。不难发现右端点为 $r$ 满足条件时 $r+1$ 也满足条件，所以只要找到最小的 $r$，总数即为 $n-r+1$。

显然可以双指针解决，问题变为判定一个区间是否合法。由于值域较小，可以分别枚举 $A_i,A_k$，找出 $A_i$ 第一次出现的位置、$A_k$ 最后一次出现的位置，判断 $\frac{A_i+A_k}2$ 是否有在两数见出现过即可。可以用 `set` 简单实现，时间复杂度 $O(nV^2\log n)$。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 1e5 + 10;

int n, a[MAXN]; ll ans;

set<int> s[11];

inline 
bool check() {
	for (int i = 1; i <= 10; i++) if (s[i].size() >= 3) return 1;
	for (int i = 1, x; i <= 10; i++) {
		if (s[i].empty()) continue; x = *s[i].begin();
		for (int j = 1, k, y; j <= 10; j++) {
			if (i == j || s[j].empty()) continue; y = *s[j].rbegin();
			if ((i + j) % 2) continue; k = i + j >> 1;
			auto it = s[k].lower_bound(x);
			if (it != s[k].end() && *it < y) return 1;
		}
	}
	return 0;
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1, j = 0; i <= n; i++) {
		for (; !check() && j <= n; j++, s[a[j]].insert(j));
		ans += n - j + 1, s[a[i]].erase(i);
	}
	printf("%lld", ans);
}
```

---

## 作者：fcy20180201 (赞：3)

## 题意
给定长度为 $N$ 的序列 $A$，序列中的每个元素在 $1$ 到 $10$ 之间。问有多少个**连续子序列**含有长度为 $3$ 的**等差子序列（可以不连续）**。

## 思路
~~一个难想但显然的思路，只比官方题解复杂那么亿点点。~~

显然，若一个连续子序列的**某一个连续子序列**符合条件，则这个连续子序列也符合条件。所以可以用双指针确定左端点，找到最近的能构成符合条件的连续子序列的右端点，那么**这个右端点右边的右端点**也都能构成符合条件的子序列。

再看看双指针怎么搞。右端点右移很容易，只需要记录区间里出现的数字，记录出现的等差数列的前两位，双指针前**预处理出所有等差数列（只有 $50$ 个）**,再看每个等差数列能不能构成就行了。但左端点右移时，我们并不知道用到左端点的等差数列有几个，~~就很难办~~。

其实，可以贪心地记录每个数字在区间里最右边的位置，每一种等差数列**第一项的位置在区间里最右能在哪里**，这样左端点右移时，如果某个数字或等差数列的第一项最右也只能在这个被移走的左端点上，那这个数字或等差数列就没了，否则就还存在。

设 $V$ 为等差数列的方案数，则时间复杂度 $\mathcal O(VN)$。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
int n,a[100005],sum,fst[55],dif[55],ha1[10],ha2[55],have;
ll ans=0;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),a[i]--;
	//这里把 1-10 变成 0-9
	for(int i=0;i<10;i++)for(int j=-4;j<5;j++)if(i+j+j>=0 && i+j+j<10)fst[sum]=i,dif[sum++]=j;//预处理所有等差数列
	for(int l=1,r=0;l<=n;l++){//双指针
		while(r<n && !have){
			r++;
			for(int i=0;i<sum;i++)if(ha2[i] && a[r]-fst[i]==dif[i]*2)have=max(have,ha2[i]);//更新等差数列第一项最右能在的位置
			for(int i=0;i<sum;i++)if(ha1[fst[i]] && a[r]-fst[i]==dif[i])ha2[i]=max(ha2[i],ha1[fst[i]]);//更新前两个数中的第一个数最右能在的位置
			ha1[a[r]]=r;//更新第一个数最右能在的位置
		}
		if(have)ans+=n-r+1;//计算答案
		if(ha1[a[l]]==l)ha1[a[l]]=0;//如果被移走的左端点上的数在区间里最右出现在左端点（即只有这一个），这个数就没了
		for(int i=0;i<sum;i++)if(ha2[i]==l)ha2[i]=0;
		//同上
		if(have==l)have=0;
	}
	printf("%lld",ans);
	return 0;
}

```

---

## 作者：XYstarabyss (赞：1)

前情提要：整个机房的人集思广益，搞出了这个有点像 dp 的做法。

# 思路

我们设一个数组 $nxt_{i,j}$，表示原数列下标大于 $i$ 的数中值等于 $j$ 且下标最小的那个数的下标。$nxt$ 数组的计算可以在输入数据的时候完成。

然后我们再枚举左端点 $A_i$，同时枚举点 $A_j$ 的大小。此时 $nxt$ 数组就展现了它的作用：可以快速找到 $A_j$ 的位置，同时根据 $A_i,A_j$ 的大小算出的 $A_{k_{min}}$ 就可以找到 $A_{k_{min}}$ 的位置。这样，我们就能得到右端点的下标最小值。

最后我们只要根据不同左端点时右端点的下标的最小值统计 $(l,r)$ 数对的个数就可以了。

# code


```cpp
#include <bits/stdc++.h>
using namespace std;
#define dbug(x) cerr<<(#x)<<':'<<x<<' ';
#define ent cerr<<'\n';
#define f(n,m,i) for (int i = n;i <= m;i ++)
#define fc(n,m,i) for (int i = n;i >= m;i --)
#define max(a,b) ((a)>(b))?(a):(b)
#define min(a,b) ((a)<(b))?(a):(b)
void C(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0),cerr.tie(0);
}
long long n,ans(0);
long long l[15];
long long r[100005];//右端点
long long a[100005];//数列
long long nxt[100005][15];//表示下标大于i，值等于j且下标最小的A的下标
int main(){
    C();
    cin >> n;
    f(1,10,i){
        l[i] = 1;
    }
    f(1,n,i){
        cin >> a[i];
        f(l[a[i]],i - 1,j){
            nxt[j][a[i]] = i;
        }
        l[a[i]] = i;
    }
    f(1,n,i){//枚举左端点A_i
        r[i] = 1e9;
        f(1,10,j){//枚举A_j的大小
            long long p(nxt[i][j]);//A_j的位置
            long long q((j << 1) - a[i]);//A_k的大小
            if(p && q >= 1 && q <= 10){
                p = nxt[p][q];//A_k的位置
                if(p){
                    r[i] = min(r[i],p);//最小右端点
                }
            }
        }
    }
    r[n + 1] = 1e9;
    fc(n,1,i){
        if(r[i + 1] != 1e9){
            r[i] = min(r[i],r[i + 1]);//右端点取最小（因为我们左端点枚举的是A_i，有可能更大的A_i可以配出更小的最小右端点
        }
        if(r[i] != 1e9){
            ans += n - r[i] + 1;//统计答案
        }
    }
    cout << ans << endl;
    return 0;
}
/*
g++ arc170b.cpp -o code
./code

9

10 10 1 3 3 7 2 2 5

*/
```

---

## 作者：Jerry_heng (赞：0)

（一）

[更佳的体验。](https://www.cnblogs.com/Jh763878/p/18387514)

因为 $a_i$ 较小，那么可以对每一个 $i$，求出它右边离他最近的值为 $j$ 的位置。

枚举左端点和中间那个数 $a_j$，那么可以求出最小的 $k$。

这样就求出了每个左端点可以取到的最小的 $k$，记为 $b_i$ 再从右到左 $b_i=\min(b_i,b_{i+1})$。

（二）

AC 代码。

```cpp
#include<bits/stdc++.h>
#define db double
#define pb push_back
#define fi first
#define se second
#define mkp make_pair
#define pii pair<int,int>
#define int long long
using namespace std;
inline int read(){
    int x=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-f;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    return x*f; 
}
int n,a[100010],las[100010],pos[100010][11];
signed main(){
    #ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    #endif
    n=read();
    for(int i=1;i<=n;i++)
    	a[i]=read(),las[i]=n+1;
    las[n+1]=n+1;
    for(int i=1;i<=10;i++)
    	pos[n][i]=pos[n+1][i]=n+1;
    for(int i=n-1;i>=1;i--){
    	for(int j=1;j<=10;j++)
    		pos[i][j]=pos[i+1][j];
    	pos[i][a[i+1]]=i+1;
    }
    for(int i=1;i<=n;i++){
    	for(int j=1;j<=10;j++){
    		if(j*2-a[i]<1||j*2-a[i]>10||pos[i][j]>n)continue;
    		int z=pos[pos[i][j]][j*2-a[i]];
    		if(z>n)continue;
    		las[i]=min(las[i],z);
    	}
    }
    for(int i=n;i>=1;i--)
    	las[i]=min(las[i],las[i+1]);
    int res=0;
    for(int i=1;i<=n;i++)
    	res+=n-las[i]+1;
    printf("%lld\n",res);
    return 0;
}
```

---

## 作者：Xiphi (赞：0)

A>>>>>>B。

傻逼题。赛时挂了几个细节。

首先枚举 $j$，然后枚举公差（只在 $-4$ 到 $4$ 之间），就可以确定 $a_i$ 与 $a_k$ 的值，然后对每种数开桶子，里边记录下标，然后就可以二分找到最接近 $j$ 的 $a_i$ 与 $a_k$。

另设 $L_i$ 表示以 $i$ 开头最小的且满足条件的结尾 $j$，然后就可以在前边的计算过程中算出所有的 $L_i$，答案就是 $\sum_{i=1}^nn-L_i+1$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n;
int a[100005],L[100005];
set<int> s[50];
signed main(){
//	freopen("test.in","r",stdin);
//	freopen("test.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
	cin>>n;
	memset(L,0x3f,sizeof L);
	for(int i=1;i<=n;++i){
		cin>>a[i];
		s[a[i]].insert(i);
	}
	for(int i=1;i<=10;++i){
		s[a[i]].insert(0);
		s[a[i]].insert(n+1);
	}
	long long ans=0;
	for(int i=1;i<=n;++i){
		int y=a[i];
		for(int j=-10;j<=10;++j){//公差
			int x=y-j;
			int z=y+j;
			if(x>10||z>10||z<1||x<1) continue;
			auto it=s[z].upper_bound(i);
			if(it==s[z].end()||*it==n+1){
				continue;
			}
			auto it1=s[x].lower_bound(i);
			if(*it1==0) continue;
			--it1;
			if(*it1==0) continue;
			if(*it1<i&&i<*it) L[*it1]=min(*it,L[*it1]);
		}
	}
	for(int i=n;i>=1;--i){
		L[i]=min(L[i+1],L[i]);
	}
	for(int i=1;i<=n;++i){
		if(L[i]<=n&&L[i]-i+1>=3&&L[i]>=1)
		ans+=n - L[i]+1;
//		cout<<L[i]<<'\n';
	}
	cout<<ans;
	return 0;
}




```

---

## 作者：Mikran (赞：0)

# AT_arc170_b [ARC170B] Arithmetic Progression Subsequence

发现如果有一个对 $(l,r)$ 是好的，那么 $(x\in[1,l],y\in[r,n])$ 都是好的对。

那么有一个贪心的思路，我们考虑求出所有最小的 $(l,r)$，再计算答案。

怎么求呢？考虑设计DP，$dp[i][k][c]$ 表示满足存在 $i_0,i_1,\dots,i_k,i_{k+1}(i_0 < i_1 < \dots < i_k < i_{k+1}=i)$，使得任意 $i_{j\in[0,k]}$ 有$a[i_{j+1}]-a[i_j]=c$ 时 $i_0$ 的最大值。

求解 $dp[i][k][c]$ 时还需要一个辅助数组 $mx[v][k][c]$，表示 $\max_{a[i]=v}dp[i][k][c]$。

容易得到：
$$
\begin{equation}  
\left\{  
     \begin{array}{lr}  
  		dp[i][k][c]=i,k=0\\
  		dp[i][k][c]=mx[a[i]-c][k-1][c],k\in(0,3)\\

     \end{array}  
\right.  
\end{equation}
$$
然后在设一个 $l[i]=\max_{c\in[-9,9]}dp[i][2][c]$。

很明显 $(l[i],i)$ 就是一个最小的 $(l,r)$。

最后就可以求答案了（注意不要算重了）。

```cpp
#include <bits/stdc++.h>
#define int long long
#define __int32 int
#define __int64 long long
#define db long double
#define eps 1e-12
const int N = 2e5 + 10, M = 2e5 + 10, inf = 1e9 + 10;
inline int read() {
    int x = 0, f = 1; char ch = getchar();
    for (; ! isdigit(ch); ch = getchar()) if (ch == '-') f = -1;
    for (; isdigit(ch); ch = getchar()) x = (x << 3) + (x << 1) + (ch ^ 48);
    return x *= f;
}
using namespace std;
int n;
int a[N];
int dp[N][3], mx[11][3], l[N];
signed main() {
	n = read();
	for ( int i = 1; i <= n; i ++) a[i] = read();
	for ( int c = -9; c <= 9; c ++) {
		for ( int i = 1; i <= 10; i ++) for ( int k = 0; k < 3; k ++) mx[i][k] = 0;
		for ( int i = 1; i <= n; i ++) for ( int k = 0; k < 3; k ++) dp[i][k] = 0;
		for ( int i = 1; i <= n; i ++) {
			for ( int k = 2; k >= 0; k --) { //倒序枚举k是为了满足总是从[1,i-1]转移过来
				if (k == 0) dp[i][k] = i, mx[a[i]][k] = max(mx[a[i]][k], i);
				else if (a[i] - c >= 1 && a[i] - c <= 10) dp[i][k] = max(dp[i][k], mx[a[i] - c][k - 1]), mx[a[i]][k] = max(mx[a[i]][k], dp[i][k]);
			}
		}
		for ( int i = 1; i <= n; i ++) l[i] = max(l[i], dp[i][2]);
	}
	int mx = 0, ans = 0;
	for ( int i = 1; i <= n; i ++) if (l[i] > mx) ans += (l[i] - mx) * (n - i + 1), mx = l[i] ;
	cout << ans;
}

```

---

## 作者：rsy_ (赞：0)

ARC 最简单的一集。

直接求发现其实不是很好求。

所以这里考虑算出每一种方案，把所有的方案求出来去并集就可以了。

因为有一个就可以，那么对于每一个位置的每一个公差，求出一个最近的就行了。

所以可以预处理一个数组，表示这个数后面的第一个为 $x$ 的位置。

那么只需要枚举位置和公差就行了，因为 $0\le a_i\le 10$，所以公差 $d$ 是 $-4\le d\le 4$，假设这个区间是 $[l,r]$，那么可行的区间就是左端点为 $[1,r]$，右端点为 $[r,n]$ 的所有区间，那么只需要维护一个数组表示以 $l$ 为左端点的最小的 $r$ 的值。

最后 $\mathcal O(n)$ 统计一下就可以了。

总时间复杂度 $\mathcal O(n\log n)$，常数较大，正解是 $\mathcal O(n)$ 的，但是 $\mathcal O(n\log n)$ 也可以过。

[赛事通过记录](https://atcoder.jp/contests/arc170/submissions/49552396)

---

