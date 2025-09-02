# [ARC183B] Near Assignment

## 题目描述

给定两个长度为 $n$ 的序列 $A,B$ 以及整数 $k$，可以进行以下操作任意多次（也可以不操作）：

选择两个整数 $i,j$（$1\le i,j\le n$）满足 $|i-j|\le k$，将 $a_i$ 的值变为 $a_j$。

求是否可以将 $A$ 序列变为 $B$ 序列，如果可以，输出 `Yes`，否则输出 `No`。多组询问。

## 说明/提示

样例的第 1 组数据解释：

选择 $i=2,j=3$，则 $a_2\leftarrow a_3=2$，$A$ 变成 $(1,2,2)$。

对于所有数据，满足：$1\le T\le 1.25\times 10^5,1\le k<n\le 2.5\times 10^5,\sum n\le2.5\times 10^5$。保证输入的数都是整数。

## 样例 #1

### 输入

```
4
3 1
1 1 2
1 2 2
5 4
2 4 5 1 3
2 1 3 2 2
13 1
3 1 3 3 5 3 3 4 2 2 2 5 1
5 3 3 3 4 2 2 2 2 5 5 1 3
20 14
10 6 6 19 13 16 15 15 2 10 2 16 9 12 2 6 13 5 5 9
5 9 6 2 10 19 16 15 13 12 10 2 9 6 5 16 19 12 15 13```

### 输出

```
Yes
Yes
No
Yes```

# 题解

## 作者：ケロシ (赞：19)

小清新结论题。

这种题赛时花一点时间还是能想出来的。

首先考虑 $b$ 数组里出现 $a$ 数组里没有的数，那么一定不合法。

其次考虑 $a$ 可以通过什么神秘的方式变成 $b$。

首先考虑 $b$ 可能有很多连续段，那么每个连续段里只需一个位置 $a$ 等于 $b$ 就能以将整个连续段变成 $a$ 等于 $b$ 的，设将连续段缩成一个数后组成的序列为 $e$，长度为 $tot$。

不难发现可以构造一个**交换器**，交换相邻两个元素，但是很明显需要 $k>1$ 且需要有一个额外的位置。

先把 $k=1$ 判掉，这时只能将 $a$ 中的数进行移动，所以需要将 $a$ 中的子序列 $e$ 移动到 $b$ 中的相应位置，此时判断方式即为 $a$ 有没有子序列 $e$。

再考虑 $k>1$ 的情况，此时可以用交换器，但是需要一个额外位置，不难发现有额外位置仅当 $tot<n$。

没有额外位置怎么办？首先是 $a=b$ 的情况直接判掉，否则需要牺牲一个位置，最后牺牲掉的位置必须直接从其它数复制过去。最后一步能够直接复制过去的，仅当存在 $b_i=b_j$ 且 $|i-j| \le k,i\ne j$，这个很好判。

时间复杂度 $O(n)$。

吃了三罚，还不是因为自己不够努力。

```cpp
const int N = 2.5e5 + 5;
int n, k, a[N], b[N], c[N];
int e[N], tot;
vector<int> f[N];
void solve() {
	cin >> n >> k;
	FOR(i, 1, n) cin >> a[i];
	FOR(i, 1, n) cin >> b[i];
	FOR(i, 1, n) c[i] = 0;
	FOR(i, 1, n) c[a[i]]++;
	FOR(i, 1, n) if(!c[b[i]]) {
		cout << "No" << endl;
		return;
	}
	tot = 0;
	FOR(i, 1, n) if(b[i] != b[i - 1]) e[++tot] = b[i];
	if(k == 1) {
		int p = 0;
		FOR(i, 1, n) if(p < tot && a[i] == e[p + 1]) p++;
		cout << (p == tot ? "Yes" : "No") << endl; 
		return;
	}
	bool ok = 1;
	FOR(i, 1, n) if(a[i] != b[i]) ok = 0;
	if(ok || tot < n) {
		cout << "Yes" << endl;
		return;
	}
	FOR(i, 1, n) f[i].clear();
	FOR(i, 1, n) f[b[i]].push_back(i);
	FOR(i, 1, n) if(SZ(f[i]) > 1) {
		REP(j, SZ(f[i]) - 1) {
			if(f[i][j + 1] - f[i][j] <= k) {
				cout << "Yes" << endl;
				return;
			}
		}
	}
	cout << "No" << endl;
}
```

---

## 作者：小超手123 (赞：11)

### 分析：

做法参考了官方题解。

首先特判 $A=B$ 的情况。其次如果 $B$ 中存在了在 $A$ 中没有出现的数字，直接输出“No”。

时光倒流，将操作改为选择相同的 $B_{i},B_{j}(|i-j| \le K)$。然后把 $B_{i}$ 变成 $\ast$（$\ast$ 代表万能数字）。

如果一次都操作不了，直接输出“No”。否则任意操作一次，因此接下来默认 $B$ 中至少存在一个 $\ast$。

可以发现，$B$ 的两个相邻的位置可以互相交换。原因如下：

- 当 $B$ 中存在 $\ast x$ 的情况，把 $\ast$ 变成 $x$，然后操作一次变成 $x \ast$。因此 $\ast$ 可以任意移动。

- 当 $B$ 中存在 $xy$ 的情况，先调一个 $\ast$ 过来，变成 $\ast xy$，然后 $\ast xy(yxy) \to yx \ast$。不过需要满足 $k \ge 2$，因此最后要特判 $k=1$ 的情况。

接下来只需要把 $B$ 中相同的元素放在一堆 $xxx$，操作成 $x\ast \ast$。然后把 $B$ 中非 $\ast$ 的匹配到 $A$，剩下的 $\ast$ 直接变。所以直接输出“Yes”。

如果 $k=1$，分别把 $A,B$ 相邻的相同的元素合并成一个，操作后称为 $A{'},B^{'}$。那么 $A$ 能操作成 $B$ 当且仅当 $B^{'}$ 是 $A^{'}$ 的子序列。原因是显然的。

时间复杂度 $O(Tn)$。

### 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 300005
using namespace std;

int T, n, k;
int a[N], b[N], A[N], B[N];
vector<int>p[N];
bool z[N];
void Sol() {
    cin >> n >> k;
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= n; i++) cin >> b[i];
    bool flag = 1;
    for(int i = 1; i <= n; i++)
        if(a[i] != b[i]) {
            flag = 0;
            break;
        }
    if(flag) {
        cout << "Yes" << endl;
        return;
    }
    if(k == 1) {
        int cnt1 = 0, cnt2 = 0;
        for(int i = 1; i <= n; i++) {
            if(a[i] != a[i - 1]) A[++cnt1] = a[i];
            if(b[i] != b[i - 1]) B[++cnt2] = b[i];
        }
        int now = 0;
        for(int i = 1; i <= cnt1; i++) {
            if(A[i] == B[now + 1]) {
                now++;
                if(now == cnt2) break;
            }
        }
        if(now == cnt2) cout << "Yes" << endl;
        else cout << "No" << endl;
    }
    else {
        for(int i = 1; i <= n; i++) p[i].clear(), z[i] = 0;
        for(int i = 1; i <= n; i++) z[a[i]] = 1;
        for(int i = 1; i <= n; i++) {
            if(!z[b[i]]) {
                cout << "No" << endl;
                return;
            }
            p[b[i]].push_back(i);
        }
        for(int i = 1; i <= n; i++) {
            int len = p[i].size();
            for(int j = 0; j < len - 1; j++)
                if(p[i][j + 1] - p[i][j] <= k) {
                    cout << "Yes" << endl;
                    return;
                }
        }
        
        cout << "No" << endl;
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> T;
    while(T--) Sol();

    return 0;
}
```

---

## 作者：Take_A_Single_6 (赞：3)

好神秘的题。  
第一眼看过去没啥想法，参考了别的题解。  
这道题的切入点就是观察到如果 $k>1$ 且有一个位置可以随便用就可以交换相邻的两个数，推广一下我们就可以任意排列 $A$ 序列，然后针对这个性质补充其他情况就可以了。  
- 显然我们不可能得到 $A$ 序列中不存在的字符，所以我们先用桶判掉这种情况。
- 显然对于重复的一段序列我们可以由一个字符复制，那么我们可以将序列 $B$ 缩成序列 $B'$，当 $k = 1$ 时判断 $B'$ 是否是 $A$ 的子序列即可。
- 显然两个序列一样是可以的。
- 显然 $\lvert B' \rvert < \lvert B \rvert$ 时肯定有位置是可以随便用的，如果一个位置的字符可以由另一个位置复制过来那么这个位置也可以随便用。

代码不难写，注意多测清空。

```cpp
#include<bits/stdc++.h>
#define int long long
#define db double
#define maxn 1000005
#define mod 998244353
#define fir first
#define sec second
#define pr pair<int,int>
#define mk make_pair
#define inf 10000000000000000
using namespace std;
inline int read()
{
    int SS=0,WW=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
	{
        if(ch=='-')WW=-1;
        ch = getchar();
    }
    while(ch>='0'&&ch<='9')
	{
        SS=(SS<<1)+(SS<<3)+(ch^48);
        ch=getchar();
    }
    return SS*WW;
}
inline void write(int XX)
{
    if(XX<0)putchar('-'),XX=-XX;
    if(XX>9)write(XX/10);
    putchar(XX% 10 + '0');
}
int n,k,T,ans,a[maxn],b[maxn],c[maxn],sub[maxn],cnt;
bool ok;
vector<int>pos[maxn];
signed main()
{
	for(T=read();T;T--)
	{
		n=read(),k=read(),ok=1,cnt=0;
		for(int i=1;i<=n;i++)a[i]=read(),c[a[i]]++;
		for(int i=1;i<=n;i++)b[i]=read();
		for(int i=1;i<=n;i++)
			if(!c[b[i]])
			{
				ok=0,puts("No");
				break;
			}//判断得不到某个字符的情况
		for(int i=1;i<=n;i++)c[a[i]]--;//用a[i]清空桶，避免多测超时
		if(!ok)continue;
		for(int i=1;i<=n;i++)if(b[i]!=b[i-1])sub[++cnt]=b[i];//缩成B'
		if(k==1)//特判k=1
		{
			int s=1;
			for(int i=1;i<=n;i++)if(s<=cnt&&a[i]==sub[s])s++;
			puts(s>cnt?"Yes":"No");
			continue;
		}
		for(int i=1;i<=n;i++)if(a[i]!=b[i])ok=0;
		if(ok||cnt<n)//一样或者缩段了
		{
			puts("Yes");
			continue;
		}
		for(int i=1;i<=n;i++)pos[i].clear();
		for(int i=1;i<=n;i++)pos[b[i]].push_back(i);
		for(int i=1;i<=n&&!ok;i++)
			for(int j=0;j<(int)pos[i].size()-1;j++)
				if(pos[i][j+1]-pos[i][j]<=k)//判断能不能从另一个位置得到
				{
					puts("Yes"),ok=1;
					break;
				}
		if(!ok)
		puts("No");
	}
    return 0;
}
```

---

