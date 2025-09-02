# JJOOII 2 (JJOOII 2)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joi2020ho/tasks/joi2020ho_b

ビ太郎は友人のビバ子から誕生日プレゼントに `J`，`O`，`I` の $ 3 $ 種類の文字からなる長さ $ N $ の文字列 $ S $ をもらった．

$ K $ を $ 1 $ 以上の整数とする．$ K $ 個の文字 `J`，$ K $ 個の文字 `O`，$ K $ 個の文字 `I` をこの順に並べた文字列を**レベル $ K $ の JOI 文字列**と呼ぶことにする．例えば，`JJOOII` はレベル $ 2 $ の JOI 文字列である．

ビ太郎はレベル $ K $ の JOI 文字列が好きなので，以下の $ 3 $ 種類の操作を任意の回数，任意の順番で行うことで，文字列 $ S $ をレベル $ K $ の JOI 文字列に変換することにした．

- **操作 $ 1 $** 文字列 $ S $ の先頭の文字を消す．
- **操作 $ 2 $** 文字列 $ S $ の末尾の文字を消す．
- **操作 $ 3 $** 文字列 $ S $ の先頭でも末尾でもない文字を消す．

操作 $ 3 $ を行うのは面倒なので，操作 $ 3 $ を行う回数をできるだけ少なくして，文字列 $ S $ をレベル $ K $ の JOI 文字列に変換したい．

長さ $ N $ の文字列 $ S $ と $ 1 $ 以上の整数 $ K $ が与えられたとき，文字列 $ S $ をレベル $ K $ の JOI 文字列に変換するのに必要な操作 $ 3 $ の回数の最小値を出力するプログラムを作成せよ．ただし，どのように操作を行っても文字列 $ S $ をレベル $ K $ の JOI 文字列に変換できない場合は，代わりに $ −1 $ を出力せよ．

- - - - - -

## 说明/提示

### 制約

- $ 3\ \leqq\ N\ \leqq\ 200\,000 $．
- $ 1\ \leqq\ K\ \leqq\ \frac{N}{3} $．
- $ S $ は `J`，`O`，`I` の $ 3 $ 種類の文字からなる長さ $ N $ の文字列である．

### 小課題

1. ($ 1 $ 点) $ N\ \leqq\ 21 $.
2. ($ 12 $ 点) $ N\ \leqq\ 3\,000 $.
3. ($ 87 $ 点) 追加の制約はない.

- - - - - -

### Sample Explanation 1

次のように操作を行うことで，文字列 $ S $ をレベル $ K $ のJOI文字列に変換できる． 1. まず操作 $ 1 $ を行う．文字列 $ S $ は `JIJOIOIIJ` になる． 2. 次に操作 $ 2 $ を行う．文字列 $ S $ は `JIJOIOII` になる． 3. 次に操作 $ 3 $ を行い，先頭から $ 2 $ 文字目を消す．文字列 $ S $ は `JJOIOII` になる． 4. 最後に操作 $ 3 $ を行い，先頭から $ 4 $ 文字目を消す．文字列 $ S $ は `JJOOII` になる． $ 2 $ 回未満の操作 $ 3 $ で変換することは不可能なので，$ 2 $ を出力する． - - - - - -

### Sample Explanation 2

操作を行わなくてもよい． - - - - - -

### Sample Explanation 3

この入力例では，どのように操作を行っても文字列 $ S $ をレベル $ 1 $ の JOI 文字列に変換できない．

## 样例 #1

### 输入

```
10 2
OJIJOIOIIJ```

### 输出

```
2```

## 样例 #2

### 输入

```
9 3
JJJOOOIII```

### 输出

```
0```

## 样例 #3

### 输入

```
9 1
IIIOOOJJJ```

### 输出

```
-1```

# 题解

## 作者：Kano_zyc (赞：3)

## 题目分析

这个问题要求我们找到一个字符串 $S$ 的最短子串，这个子串能够被转换为一个 $K$ 阶 `JOI` 字符串，仅通过删除非首尾的字符。 

$K$ 阶 `JOI` 字符串是一个由 $K$ 个 `J`，接着是 $K$ 个  `O`，最后是 $K$ 个 `I` 组成的字符串。我们的目标是最小化这种转换所需的删除操作次数。

## 解题思路

为了解决这个问题，我们首先需要找到一个子串，它包含至少 $K$ 个 `J`、$K$ 个 `O` 和 $K$ 个 `I`，并且这些字符按照 `J`、`O`、`I`的顺序排列。

一旦找到了这样的子串，我们就可以通过删除其中多余的字符来得到一个 $K$ 阶 `JOI` 字符串。

这个问题的关键在于如何高效地找到这样的子串。

我们采用的策略是使用前缀和和二分搜索。首先，我们为每个字符计算其前缀和。

这允许我们快速地计算出任何子串中每个字符的数量。

对于每个可能的子串起始位置，我们使用二分搜索来找到最少包含 $K$ 个 `J` 的位置，然后以这个位置为起点，再次使用二分搜索找到最少包含 $K$ 个 `O` 的位置，最后找到最少包含 $K$ 个 `I` 的位置。这样，我们就找到了一个包含至少 $K$ 个 `J`、$K$ 个 `O` 和 $K$ 个 `I` 的子串。我们重复这个过程，直到覆盖整个字符串。

最后，我们比较所有找到的子串的长度，并选择长度最短的一个。

这个长度最短的子串需要的删除操作次数就是我们的答案。

## AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
int J[N], O[N], I[N];

// 二分搜索找到最小的r，使得区间[l, r]包含至少k个目标字符
int findMinIndex(int l, int k, int n, int prefixSum[]) {
    int left = l, right = n, ans = n + 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (prefixSum[mid] - prefixSum[l - 1] >= k) {
            ans = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return ans;
}

int main() {
    int n, k;
    string s;
    cin >> n >> k >> s;

    // 计算前缀和
    for (int i = 1; i <= n; ++i) {
        J[i] = J[i - 1] + (s[i - 1] == 'J');
        O[i] = O[i - 1] + (s[i - 1] == 'O');
        I[i] = I[i - 1] + (s[i - 1] == 'I');
    }

    int ans = INT_MAX;
    for (int l = 1; l <= n; ++l) {
        int endJ = findMinIndex(l, k, n, J);
        if (endJ > n) break;
        int endO = findMinIndex(endJ, k, n, O);
        if (endO > n) break;
        int endI = findMinIndex(endO, k, n, I);
        if (endI > n) break;

        // 更新答案
        ans = min(ans, endI - l + 1 - 3 * k);
    }

    if (ans == INT_MAX) {
        cout << "-1\n";
    } else {
        cout << ans << "\n";
    }

    return 0;
}

```

---

## 作者：small_turtle (赞：3)

可以发现一个 $K$ 阶串确定 `J` 的左端点后，之后 `J` 的数量是单调不减的，于是可以使用二分确定 `J` 的右端点，也可以这样找到 `O`，`I` 的右端点。我们可以用前缀和统计区间字符数量，枚举左端点，二分串的右端点，最后答案为右端点下标减去左端点下标的最小值减去 $3k$（本应该有的），就为需要删除的数量，二分可以采用 `lower_bound()` 解决。
```cpp
//Time:2023.5.19
#include <bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
const ll inf=0x3f3f3f3f,N=2e5+5;
const double eps=1e-6;
using namespace std;


inline ll read()
{	
	ll x=0;bool f=0;char c=getchar();
	while(!isdigit(c))f|=(c=='-'),c=getchar();
	while(isdigit(c))x=x*10+(c&15),c=getchar();
	return f?-x:x;
} 

int n,k,J[N],O[N],I[N];
int ans=inf;
char s[N];

int main()
{
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>n>>k;
	cin>>s+1;
	
	for(int i=1;i<=n;++i)
	{
		J[i]=J[i-1],O[i]=O[i-1],I[i]=I[i-1];
		if(s[i]=='J')++J[i];
		if(s[i]=='O')++O[i];
		if(s[i]=='I')++I[i];
	}
	
	for(int i=1;i<=n;++i)
	{
		if(s[i]!='J')continue;
		int x=lower_bound(J+1, J+n+1, J[i-1]+k)-J;
		int y=lower_bound(O+1, O+n+1, O[x-1]+k)-O;
		int z=lower_bound(I+1, I+n+1, I[y-1]+k)-I;
		if(x>n||y>n||z>n)break;
		ans=min(ans, z-i+1);
	}
	
	if(ans>=inf)cout<<-1;
	else cout<<ans-k*3;
	return 0;
}
```

---

## 作者：saixingzhe (赞：1)

# 分析

首先将题意转化为求 $S$ 中含有子序列为 $K$ 阶 `JOI` 串的最短子串。

我们可以使用 `vector` 记录每个字母出现的位置，维护两个指针为 `O` 能取到第一个数在 `vector` 中的下标和 `I` 能取到第一个数在 `vector` 中的下标。我们枚举 `J` 能取到第一个数在 `vector` 中的下标并维护指针即可，答案为子串长度减 $3 \times k$，复杂度为 $\mathcal O(n)$。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,O,I,ans=INT_MAX;
string s;
vector<int>q[3];
int main(){
	cin>>n>>k>>s;
	for(int i=0;i<s.size();i++){
		if(s[i]=='J')	q[0].push_back(i);
		if(s[i]=='O')	q[1].push_back(i);
		if(s[i]=='I')	q[2].push_back(i);
	}
	for(int J=0;J<=q[0].size()-k;J++){
		while(O<=q[1].size()-k&&q[0][J+k-1]>q[1][O])	O++;
		while(I<=q[2].size()-k&&q[1][O+k-1]>q[2][I])	I++;
		if(O<=q[1].size()-k&&I<=q[2].size()-k)	ans=min(ans,q[2][I+k-1]-q[0][J]+1-3*k);
		else	break;
	}
	if(ans==INT_MAX)	ans=-1;
	printf("%d",ans); 
	return 0;
}
```

---

## 作者：封禁用户 (赞：1)

我首先想到的是DP。当你冷静下来你就会看到它。

### 问题摘要 
给出一个长度为 $N$ 的字符串 $S$，仅由 ```J```、```O``` 和 ```I``` 组成。顺便说一句，$K$ 级的 JOI 字符串指的是 ```JJ...JOO...OII...I```（每个 $K$ 个字符）。对字符串 $S$ 执行以下操作，使其成为级别 $K$ 的 JOI 字符串。找出为此所需的最低成本。如果不可能，则打印 ```-1```。删除第一个字符（Cost 0）删除最后一个字符（Cost 0）删除第一个和最后一个字符以外的字符（Cost 1）。

### 思考

将问题改写如下：变成那样```OJIJOIOIIJOOOOOJJOJIJI``` 这样的字符串的连续区间，其中：
* 从左起有 $K$ 个 ```J```。
* 从左起有 $K$ 个 ```O```。
* 从左起有 $K$ 个 ```I```。

可以说，问题就是找到“最小长度段”在哪里。上例中，例如 ``` O | JIJOIOII | JOOOOOJJOJIJI```，这样  ```|``` 之间的间隔就是最小长度。

### 固定起点“J” 
当起始点 $J$ 固定时，可以从左边求解贪心。在这种情况下，如果能够快速找到每个 $i$ 的下一个值，那就太好了。

* 对于每个 $i$ 使得 $S_i = $ ```J```，从那里重复  ```J```，$K$ 次后第一个 $O$ 的索引 $S_j = $ ```O```。 

* 对于每个 $j$ 使得 ，重复 ```O```，$K$ 次后的第一个 ```I```。这可以使用 ```lower_bound``` 或 ```shakutori``` 方法找到。使用二分查找时计算量为 $O(N\log{N})$，使用对角线法时为 $O(N)$。

### 代码（二分）

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
	int N, K;
	string S;
	cin >> N >> K >> S;
	vector<int> ij, io, ii;
	for (int i = 0; i < N; ++i) {
		if (S[i] == 'J') ij.push_back(i);
		else if (S[i] == 'O') io.push_back(i);
		else ii.push_back(i);
	}
	int res = N + 1;
	for (int i = 0; i + K - 1 < ij.size(); ++i) {
		int from = ij[i];
		auto j = lower_bound(io.begin(), io.end(), ij[i + K - 1]) - io.begin();
		if (j + K - 1 >= io.size()) continue;
		auto k = lower_bound(ii.begin(), ii.end(), io[j + K - 1]) - ii.begin();
		if (k + K - 1 >= ii.size()) continue;
		int to = ii[k + K - 1] + 1;
		res = min(res, to - from - K * 3);
	}
	cout << (res <= N ? res : -1) << endl;
}
```


---

## 作者：Aoharu_shiroko (赞：1)

# 题目描述
构造一个长度为 $3K$，且 `J` `O` `I` 的长度分别为 $K$ 的字符串，顺序为先 `J` 在 `O` 最后是 `I`。
# 思路点拨
首先，我们要找到像样例一样的 $K$ 阶字串。

怎么找最高效？

我们可以运用前缀和和二分进行查找，二分不用说为了让时间复杂度更高效。

用前缀和是为什么呢？

因为它可以允许我们更高效的统计字符出现了多少次。

现在正式开始解题！

枚举每个字串的起始位置，用二分和前缀和依次找到 $K$ 阶的 `J` `O` `I` 的右端点。

遍历完整个字符串的同时，求出 $ans$ 的最小值就是答案。

Ps：这里的二分采用 [lower_bound](https://blog.csdn.net/qq_37529913/article/details/125139815) 来求位置。

# AC CODE
```cpp
#include <bits/stdc++.h>
using namespace std;

int n,k;
string s;
int J[1000005],O[1000005],I[1000005];


int main()
{
	scanf("%d%d",&n,&k);
	cin >> s;
	for (int i=1;i<=n;i++)
	{
		J[i]=J[i-1];
		O[i]=O[i-1];
		I[i]=I[i-1];
		if (s[i-1]=='J') ++J[i];
		if (s[i-1]=='O') ++O[i];
		if (s[i-1]=='I') ++I[i];
	}
	int ans=0x3f3f3f3f;
	for (int i=1;i<=n;i++)
	{
		if(s[i-1]!='J') continue;
        	//好好想想为什么左端点要减一，在通过前缀和+lower_bound去取右端点
		int x=lower_bound(J+1,J+1+n,J[i-1]+k)-J;
		int y=lower_bound(O+1,O+1+n,O[x-1]+k)-O;
		int z=lower_bound(I+1,I+1+n,I[y-1]+k)-I;
		if (x>n||y>n||z>n)
		{
			break;
		}
		ans=min(ans,z-i+1);
	}
	if (ans==0x3f3f3f3f)
	{
		cout << -1 << endl;
	}
	else{
		cout << ans-k*3 << endl;
	}
	return 0;
}
```

---

## 作者：huangrenheluogu (赞：0)

四指针，对于左端点、`J` 和 `O` 的分界点、`O` 和 `I` 的分界点、右端点指针维护，要求中间字母的数量 $\ge k$，删掉中间的数量是这部分的总长度减 $3k$。

上面这个东西用前缀和和指针维护一下是简单的。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int a[N], n, cnt[N][3], ans, k;
char s[N];
inline void chkmin(int &x, int y){
    if(x > y) x = y;
}
int main(){
    // freopen("data.in", "r", stdin);
    // freopen("code.out", "w", stdout);
    scanf("%d%d%s", &n, &k, s + 1);
    for(int i = 1; i <= n; i++){
        if(s[i] == 'J') a[i] = 0;
        if(s[i] == 'O') a[i] = 1;
        if(s[i] == 'I') a[i] = 2;
        for(int j : {0, 1, 2}){
            cnt[i][j] = cnt[i - 1][j];
        }
        cnt[i][a[i]]++;
    }
    ans = n + 1;
    for(int i = 0, i1 = 0, i2 = 0, i3 = 0; i <= n; i++){
        while(cnt[i1][0] - cnt[i][0] < k && i1 <= n) i1++;
        while(cnt[i2][1] - cnt[i1][1] < k && i2 <= n) i2++;
        while(cnt[i3][2] - cnt[i2][2] < k && i3 <= n) i3++;
        if(max({i1, i2, i3}) > n) break;
        chkmin(ans, i3 - i - 3 * k);
    }
    if(ans == n + 1) ans = -1;
    printf("%d\n", ans);
    return 0;
}
```

---

## 作者：wth2026 (赞：0)

# 题目思路
~~总所周知，（有一种算法叫做双指针）。~~

但是这道题使用双指针答案会委掉，所以我们要多定义两个指针。

定义四个下标 $L$、$l$、$r$、$R$ 分别指向一个 $K$ 阶 `JOI` 串的第一个 `J` 之前的第一个下标，第一个 `O` 之前的第一个下标（也是最后一个 `J` 的下标），第一个 `I` 之前的第一个下标（也是最后一个 `O` 的下标）和最后一个 `I` 的下标。

使用前缀和记录一下前 $i$ 个字符里分别有每种字符多少个即可。
# [AC Code](https://atcoder.jp/contests/joi2020ho/submissions/58584833)
```cpp
#include <cstring>
#include <iostream>
#include <algorithm>

#define endl '\n'
#define int long long
#define inf 0x3f3f3f3f
#define lnf 0x3f3f3f3f3f3f3f3f

const bool Debug = false;

#define Debug true

using namespace std;

const int N = 200000 + 5;

int n, k;
char s[N];
int L, l, r, R;
int _Sm[N][3];
int _Ans;

bool Chck () {
	if (l > n) {
		return 1;
	}
	
	if (_Sm[l][0] - _Sm[L][0] < k) {
		return 0;
	}
	
	return 1;
}

bool _Chck () {
	if (r > n) {
		return 1;
	}
	
	if (_Sm[r][1] - _Sm[l][1] < k) {
		return 0;
	}
	
	return 1;
}

bool _Chck_ () {
	if (R > n) {
		return 1;
	}
	
	if (_Sm[R][2] - _Sm[r][2] < k) {
		return 0;
	}
	
	return 1;
}

signed main () {
	_Ans = lnf;
	ios :: sync_with_stdio (Debug);
	cin.tie (0);
	cout.tie (0);
	
	cin >> n >> k;
	
	for (register int i = 1; i <= n; ++ i) {
		cin >> s[i];
		_Sm[i][0] = _Sm[i - 1][0];
		_Sm[i][1] = _Sm[i - 1][1];
		_Sm[i][2] = _Sm[i - 1][2];
		
		switch (s[i]) {
			case 'J' : {
				++ _Sm[i][0];
				break ;
			}
			
			case 'O' : {
				++ _Sm[i][1];
				break ;
			}
			
			case 'I' : {
				++ _Sm[i][2];
				break ;
			}
		}
	}
	
	L = -1;
	
	while (L <= n && l <= n && r <= n && R <= n) {
		++ L;
		
		while (! Chck ()) {
			++ l;
		}
		
		if (l > n) {
			break ;
		}
		
		while (! _Chck ()) {
			++ r;
		}
		
		if (r > n) {
			break ;
		}
		
		while (! _Chck_ ()) {
			++ R;
		}
		
		if (R > n) {
			break ;
		}
		
		_Ans = min (_Ans, R - L - k * 3/* + 1*/);
	}
	
	cout << ((_Ans > (lnf >> 1)) ? (-1) : (_Ans)) << endl;
}
```

---

## 作者：rainygame (赞：0)

老师讲过的题目，感觉是黄左右。

我们发现我们可以通过求出一个子串 $S[l,r]$，使得 $S[l,r]$ 只需要通过操作 $3$ 就可以化为 $K$ 阶字符串。显然答案即为 $(r-l+1)-3k$。

考虑把 `J`、`O`、`I` 的坐标分别存进三个 `vector` 里面，然后枚举第一个 `J` 的位置（即 $l$），然后求出最后一个 `J` 的位置；在往后找到 $k$ 个 `O`，求出最后一个 `O` 的位置；再通过最后一个 `O` 的位置求出第一个 `I` 的位置……

这样就可以求出最后一个 `I` 的位置（即 $r$），然后算更新答案即可。

注意若找不到 $k$ 个 `O` 或 `I` 就需要结束查找。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

int n, k, ans(INT_MAX);
vector<int> cntj, cnto, cnti;
vector<int>::iterator itj, ito, iti;
string str;

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> k >> str;
    for (int i(0); i<str.size(); ++i){
        if (str[i] == 'J') cntj.push_back(i);
        else if (str[i] == 'O') cnto.push_back(i);
        else cnti.push_back(i);
    }
    ito = cnto.begin();
    iti = cnti.begin();

    for (auto it(cntj.begin()); it+k-1!=cntj.end(); ++it){
        auto itj(it+k-1);
        while (*itj > *ito && ito != cnto.end()) ++ito;
        if (cnto.end()-ito < k) break;
        ito += k-1;
        while (*ito > *iti && iti != cnti.end()) ++iti;
        if (cnti.end()-iti < k) break;
        ito -= k-1;
        ans = min(ans, *(iti+k-1)-*it+1-3*k);
    }
    if (ans == INT_MAX) cout << -1;
    else cout << ans;

    return 0;
}

```


---

## 作者：makerlife (赞：0)

[更好的阅读体验](https://blog.makerlife.top/post/solution-P6878) | [Problem Link](https://www.luogu.com.cn/problem/AT_joi2020ho_b)

## Explanation

给定一个只包含 $\tt J$、$\tt O$、$\tt I$ 三种字符、长度为 $N$ 的字符串 $S$ 和一个正整数 $K$。定义 $K$ 阶 $\tt JOI$ 串为由恰好 $K$ 个 $\tt J$ 、$K$ 个 $\tt O$ 、$K$ 个 $\tt I$ 依次拼接而成的字串。如 $2$ 阶 $\tt JOI$ 串为 $\tt JJOOII$ 。你可以对 $S$ 进行任意次以下操作以将 $S$ 变为 $K$ 阶 $\tt JOI$ 串：

1. 删除 $S$ 的第一个字符
2. 删除 $S$ 的最后一个字符
3. 删除 $S$ 的任意一个字符

要求最小化并输出第三种操作的次数。如果不能将 $S$ 变为 $K$ 阶 $\tt JOI$ 串，输出 `-1` 。

## Solution

可以发现只要定位到了最前端的 $\tt J$ 的位置，那么就可以确定一个最短的 $\tt JOI$ 串。

即我们可以暴力从前向后扫 $\tt J$ 的位置，然后依次找到 $K$ 个 $\tt O$ 和 $\tt I$ 即可。

可以对上面的算法进行优化，我们记录每个 $\tt J$、$\tt O$、$\tt I$ 的位置为 `cj`、`co`、`ci`，那么一段 $\tt J$ 的开始位置即为 $cj_j$，结束位置为 $cj_{j+k-1}$，$\tt O$，$\tt I$ 同理。

## Core Code

```cpp
int n,k;
char s[N];
int cj[N],co[N],ci[N];
int totj,toto,toti;
int ans=INF;
int main()
{
	n=read();k=read();
	scanf("%s",s+1);
	for(int i=1;i<=n;i++)
	{
		if(s[i]=='J') cj[++totj]=i;
        if(s[i]=='O') co[++toto]=i;
        if(s[i]=='I') ci[++toti]=i;
	}
    for(int i=1;i<=totj;i++)
    {
        if(i+k-1>totj) break;//后面不足 k 个 j，下面 o,i 同理
        int ed=cj[i+k-1];//一段 j 的结束，下面 o,i 同理
        int pos=1;
        while(co[pos]<=ed && pos<=toto) pos++;//o 的起始位置，下面 i 同理
        if(pos+k-1>toto) break;
        ed=co[pos+k-1];
        pos=1;
        while(ci[pos]<=ed && pos<=toti) pos++;
        if(pos+k-1>toti) break;
        ed=ci[pos+k-1];
        ans=min(ans,ed-cj[i]+1-3*k);//答案为枚举的区间长度与 3*k 的差
    }
    printf("%d\n",(ans==INF)?-1:ans);
	return 0;
}
```



---

## 作者：User_Artist (赞：0)

# [JOI 2020 Final] JJOOII 2

## 审题

 中文题面就看 [P6878 [JOI 2020 Final] JJOOII 2](https://www.luogu.com.cn/problem/P6878)。

 概括：希望修改一个长度为 $N$ 的字符串 $S$，依次得到连续 $K$ 个 `J`、$K$ 个 `O` 和 $K$ 个 `I`（也就是形如 `JJOOII`），其中有以下三种修改操作：删头、删尾、中间删除。

 其中，题目求：完成修改的操作 $3$ 的最小数量。
 
------------

 那么，方法**很简单**：

1. 从头循环对于每 $K$ 个 `J` 去匹配后面的 $K$ 个 `O` 和 $K$ 个 `I`，不够匹配就跳出循环 。**特别地**，对于 `J` 后面的 `O` 和 `I`，只要分别找到**最近的**一组相同字符片段就能使操作 $3$ 的总数最小了。
```
	if(gj + k > cj) break;
	while(O[go] <= J[gj + k - 1] && go < co) ++ go;
	if(go + k > co) break;
	while(I[gi] <= O[go + k - 1] && gi < ci) ++ gi;
	if(gi + k > ci) break;
```
2. 对于每次枚举的总区间大小减去总区间减去所保留的 $K$ 个 `J` $K$ 个 `O`、$K$ 个 `I` 就是本次枚举所删除的数量。
```
	ans = min(ans, I[gi + k - 1] + 1 - J[gj] - 3 * k);
``` 

3. 经过分析，复杂度为 $O(N)$，可行。

------------

### 直接上代码

```cpp
#include <stdio.h>
#define min(a, b) a < b ? a : b
int n, k, ans = 2147483647; //预设为int最大值 
int cj, co, ci, gj, go, gi; //J O I位置数组の首尾端点 
int J[200005], O[200005], I[200005]; //J O I分别记录出现位置 
char s[200005];
int main() {
	scanf("%d %d\n%s", &n, &k, s); 
	for(int i = 0; i < n; ++ i)
		s[i] == 'J' ? J[cj ++] = i : (s[i] == 'O' ? O[co ++] = i : (s[i] == 'I' ? I[ci ++] = i : 0));
	for(gj; gj < cj; ++ gj) { //枚举每一个J 
		if(gj + k > cj) break; //不够k个J
		while(O[go] <= J[gj + k - 1] && go < co) ++ go; //向后匹配第一个O 
		if(go + k > co) break; //不够k个O 
		while(I[gi] <= O[go + k - 1] && gi < ci) ++ gi; //向后匹配第一个I 
		if(gi + k > ci) break; //不够k个I 
		ans = min(ans, I[gi + k - 1] + 1 - J[gj] - 3 * k); //总区间减去保留的J*k、O*k、I*k就是中间删掉的 
	}
	printf("%d\n", ans == 2147483647 ? -1 : ans);
}
```

------------

### 双倍经验

 这是两道一样的题：

 -	[P6878 [JOI 2020 Final] JJOOII 2](https://www.luogu.com.cn/problem/P6878)
 
 - [JJOOII 2 (JJOOII 2)](https://www.luogu.com.cn/problem/AT_joi2020ho_b)

### 完结撒花
 欢迎提出疑惑和进行题目上的交流！

---

## 作者：banned_wanyb (赞：0)

很明显，这个 $k$ 阶 `JOI` ，我们只需确定第一个 `J` 和最后一个 `I` 的位置，再来计算长度，最后减去 $3 \times k$ 即可算出中间的。

那么我们就把这个问题转换成了一个区间的问题，于是，可以**定一求一**，先对于一个为 `J` 的位置，注意到 `JOI` 数量前缀和数组单调递增，于是我们从当前这个位置到最后一个位置二分上一个位置 `J` 的数量加上 $k$，再以这个二分到的位置作为 `O` 开始，再找到 `O` 的结尾，最后找到 `I` 的结尾。

最后按照最上面的办法就可以计算以每个 `J` 开头的答案了，所有的值取最小。


---

