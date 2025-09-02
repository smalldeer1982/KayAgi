# [ABC302C] Almost Equal

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc302/tasks/abc302_c

英小文字からなる長さ $ M $ の文字列 $ N $ 個 $ S_1,S_2,\dots,S_N $ が与えられます。ここで、$ S_i $ は互いに異なります。

これらを並び替えた文字列の列 $ T_1,T_2,\dots,T_N $ であって、以下の条件を満たすものが存在するか判定してください。

- $ 1\ \le\ i\ \le\ N-1 $ を満たす全ての整数 $ i $ に対して、$ T_i $ を $ 1 $ 文字だけ別の英小文字に変えて $ T_{i+1} $ にすることが出来る。

## 说明/提示

### 制約

- $ 2\ \le\ N\ \le\ 8 $
- $ 1\ \le\ M\ \le\ 5 $
- $ S_i $ は英小文字からなる長さ $ M $ の文字列である。$ (1\ \le\ i\ \le\ N) $
- $ S_i $ は互いに異なる。

### Sample Explanation 1

`abcd` , `abed` , `bbed` , `fbed` の順に並び替えると条件を満たします。

### Sample Explanation 2

どのように並び替えても条件を満たすことは出来ません。

## 样例 #1

### 输入

```
4 4
bbed
abcd
abed
fbed```

### 输出

```
Yes```

## 样例 #2

### 输入

```
2 5
abcde
abced```

### 输出

```
No```

## 样例 #3

### 输入

```
8 4
fast
face
cast
race
fact
rice
nice
case```

### 输出

```
Yes```

# 题解

## 作者：没见过AC (赞：4)

简单题。

数据范围极小，直接暴搜顺序，判断是否差一个字母即可。

记得枚举开始的字符串。



```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=10;
string s[N];
int a[N][200],m,n;
bool b[N];
void dfs(int now,int x)//now是当前到哪个字符串，x是搜了几个
{
	if(x==n)
	{
		cout<<"Yes";
		exit(0);
	}
	for(int i=1;i<=n;i++)
	{
		if(!b[i])
		{
			int	sum=0;
			for(int j=0;j<=100;j++)
			{
				sum+=abs(a[now][j]-a[i][j]);
			}
			if(sum==2)//记得是差2
			{
				b[i]=1;
				dfs(i,x+1);
				b[i]=0;
			}
		}
	}
	return;
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>s[i];
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<m;j++)
		{
			a[i][s[i][j]-'a']++;//记录每种字母各有多少
		}
	}
	for(int i=1;i<=n;i++)
	{
		b[i]=1;
		dfs(i,1);
		b[i]=0;
	}
	cout<<"No";
	return 0;
}


```


---

## 作者：2huk (赞：3)

## 题目描述

有 $N$ 个长度都为 $M$ 的字符串 $S_1,S_2,S_3,\dots,S_N$，保证两两不同。

问是否存在一种排列 $S_i$ 的方法使得 $\forall 1 \le i < N$，$S_i$ 和 $S_{i+1}$ 只有一个字符不同。

$2 \le N \le 8,\ 1 \le M \le 5$

## 分析

观察到 $N$ 的范围非常的小，所以考虑暴搜。

可以搜索出每一种 $1 \sim N$ 的排列，然后把这个下标 $i$ 和字符串 $S_i$ 对应起来，依次判断是否满足条件即可。

用 $f_u$ 表示当前排列中第 $u$ 位上的元素。对于每一个 $u$，首先找到一个不在排列的前面出现过的元素，以它进行下一轮的搜索。当搜索深度来到了 $n + 1$，此时所有的元素就已经全部排列完了，判断是否合法即可。

## 代码

放[这](https://www.luogu.com.cn/paste/fcq0x0r6)了。


---

## 作者：chlchl (赞：2)

Upddate on 2023.8.10：被 hack，改进做法。

提供一个复杂度更优的解法。

## 题意
给定 $n$ 个长度为 $m$ 的字符串。问是否能将它们重排，使得对于 $1\leq i<n$，将第 $i$ 个字符串**恰好**更改一个字符后可以变成第 $i+1$ 个字符串。

## Solution
由于 $n,m$ 极小，我们可以每两个匹配一次，然后看看它们是不是恰好差一个字符，如果是就打上标记。

接着我们从图论的角度去看，那这样的话打上的标记都是双向边。如果度为 $2$ 的点不超过两个，那么就有解，否则无解。

然鹅赛时交上去 WA 了。我就想，可能有的情况是不符合的。因此我就随便找了一个点进行广搜，如果能搜到所有点那么就有解，否则无解。

然后赛后又被 hack 了，[详见这篇帖子](https://www.luogu.com.cn/discuss/656415)。

既然这样就找一条链呗，这其实等价于在图上找一条哈密尔顿路径。

采用状压 DP 实现的时间复杂度 $O(n^22^n)$，$n\le 8$ 的情况下应该比全排列优那么一点吧。

---

## 作者：FreedomKing (赞：2)

### 题目大意

给定 $n$ 个长度为 $m$ 的字符串，我们定义两个字符串之间字符的差别 $\le 1$ 即为“相似”，问是否可以把这 $n$ 个序列任意排序使得对于任何一个 $1\le i< n$，$S_i$ 相似于 $S_{i+1}$。

------------

### 思路

看一眼题目范围，$2\le N\le 8$，不难想到直接枚举所有排列，即寻找 $S$ 的全排列，然后对其判断，循环即可。

考虑使用 STL 函数 [`next_permutation`](https://blog.csdn.net/qian2213762498/article/details/79683905) 来枚举全排列，第一个参数为起始位置，第二个参数为结尾位置，`next_permutation` 会直接改变 $S$ 的顺序。

注意：`next_permutation` 默认序列已经有序。（~~赛时没排序血的教诲~~）

------------

### AC Code

```
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int n,m,t,k;
string s[N];
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>s[i];
	sort(s+1,s+n+1);
	do{
		bool flag=true;
		for(int i=1;i<n;i++){
			k=0;
			for(int j=0;j<m;j++)
				if(s[i][j]!=s[i+1][j])
					k++;
			if(k>1) flag=false;
		}
		if(flag){
			cout<<"Yes";
			return 0;
		}
	}while(next_permutation(s+1,s+n+1));
	cout<<"No";
	return 0;
}
```

---

## 作者：Elairin176 (赞：1)

[传送门](https://www.luogu.com.cn/problem/AT_abc302_c)       
水题。      
本题中，$2\le n\le 8$，可以枚举全排列。            
我们对 $s$ 进行枚举全排列，枚举出的每个全排列我们都进行检验，如果符合题意就输出 `Yes`。     
如果到最后也找不到就是 `No`。    
注意要先对 $s$ 进行排序。       
总时间复杂度为 $O(n!nm)$，可以通过。         
[CODE](https://www.luogu.com.cn/paste/iag7mumj)

---

## 作者：happybob (赞：1)

由于 $n\leq 8$，所以可以考虑 $O(n!)$ 暴力枚举全排列，并且依次计算是否满足题意要求。

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <set>
#include <map>
#include <unordered_map>
#include <queue>
#include <stack>
#include <vector>
#include <utility>
#include <cstdlib>
#include <string>
using namespace std;

#define ll long long

const int N = 2e5 + 5, INF = 2e9, MOD = 1e9 + 7;

inline int read()
{
	int op = 1, x = 0;
	char ch = getchar();
	while ((ch < '0' || ch > '9') && ch != '-') ch = getchar();
	while (ch == '-')
	{
		op = -op;
		ch = getchar();
	}
	while (ch >= '0' and ch <= '9')
	{
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * op;
}

inline void write(int x)
{
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}

int n, m, t;
string s[9];

int cntdif(string x, string y)
{
	int cnt = 0;
	for (int i = 0; i < m; i++)
	{
		if (x[i] != y[i]) cnt++;
	}
	return cnt;
}

int main()
{
	// freopen("*.in", "r", stdin);
	// freopen("*.out", "w", stdout);
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
	{
		cin >> s[i];
	}
	sort(s + 1, s + n + 1);
	do
	{
		bool f = 1;
		for (int i = 1; i < n; i++)
		{
			if (cntdif(s[i], s[i + 1]) != 1)
			{
				f = 0;
				break;
			}
		}
		if (f)
		{
			printf("Yes\n");
			return 0;
		}
	} while (next_permutation(s + 1, s + n + 1));
	printf("No\n");
	return 0;
}
```


---

## 作者：c1ampy (赞：1)

## 暴力

$ \mathcal{O}(n!) $ 求全排列，对每个排列 $ \mathcal{O}(nm) $ 判断可行性，总时间复杂度为 $ \mathcal{O}(n!nm) $，本题心慈手软，可以暴力通过。

代码如下：

```cpp
#include <iostream>
#include <vector>
using namespace std;

const int max_n = 10;

int n, m;
string s[max_n];
bool chosen[max_n];
vector <int> P;
bool ans = false;

bool judge(const string & a, const string & b);
void dfs(const int cnt);

int main() {

    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> s[i];
    }

    dfs(1);

    cout << (ans ? "Yes\n" : "No\n");

    return 0;
}

bool judge(const string & a, const string & b) {
    int cnt_diff = 0;
    for (int i = 0; i < m; ++i) {
        cnt_diff += a[i] != b[i];
        if (cnt_diff >= 2) {
            return false;
        }
    }
    return true;
}

void dfs(const int cnt) {
    if (cnt == n + 1) {
        bool flag = true;
        for (int i = 1; i < n; ++i) {
            if (judge(s[P[i - 1]], s[P[i]])) {
                continue;
            }
            flag = false;
            break;
        }
        if (flag) {
            ans = true;
        }
        return;
    }
    for (int i = 1; i <= n; ++i) {
        if (chosen[i]) {
            continue;
        }
        chosen[i] = true;
        P.push_back(i);
        dfs(cnt + 1);
        chosen[i] = false;
        P.pop_back();
    }
}
```

## 更优的方法

将字符串之间的关系抽象成图，每个字符串对应一个结点，如果两个字符串仅相差一个字母（即可以放在相邻位置上），则在两个对应的结点间连**无向边**。最后判断整张图是否是**连通图**（即存在一条路径可以遍历所有点）即可。

单次判断两个节点是否可以连边的时间复杂度为 $ \mathcal{O}(m) $，最多有 $ \mathcal{O}(n^2) $ 条边（完全图），则建图的总时间复杂度为 $ \mathcal{O}(n^2m) $。

划分连通块的时间复杂度为 $ \mathcal{O}(n) $，相对于 $ \mathcal{O}(n^2m) $ 建图可忽略。

故总时间复杂度为 $ \mathcal{O}(n^2m) $。

代码如下：

```cpp
#include <iostream>
using namespace std;

const int max_n = 10;

int n, m;
string s[max_n];
int head[max_n];
int dfn = 0;
bool visited[max_n];

struct Edge {
    int next;
    int to;
} edge[max_n * max_n];
int cnt_edge = 0;

bool judge(const string & a, const string & b);
void add_edge(const int from, const int to);
void dfs(const int cur);

int main() {

    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> s[i];
    }

    for (int i = 1; i <= n - 1; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            if (!judge(s[i], s[j])) {
                continue;
            }
            add_edge(i, j);
            add_edge(j, i);
        }
    }

    dfs(1);

    cout << (dfn == n ? "Yes\n" : "No\n");

    return 0;
}

bool judge(const string & a, const string & b) {
    int cnt_diff = 0;
    for (int i = 0; i < m; ++i) {
        cnt_diff += a[i] != b[i];
        if (cnt_diff >= 2) {
            return false;
        }
    }
    return true;
}

void add_edge(const int from, const int to) {
    edge[++cnt_edge].to = to;
    edge[cnt_edge].next = head[from];
    head[from] = cnt_edge;
}

void dfs(const int cur) {
    ++dfn;
    visited[cur] = true;
    for (int i = head[cur]; i; i = edge[i].next) {
        int to = edge[i].to;
        if (!visited[to]) {
            dfs(to);
        }
    }
}
```


---

## 作者：what_can_I_do (赞：0)

[传送门](https://www.luogu.com.cn/problem/AT_abc302_c)

开题先看题意，看完题意看数据范围。

数据范围 $2\le N\le8$，$1\le M\le5$，可以直接考虑对所有字符串进行全排列，然后再判断是否可行。复杂度是 $O(n!nm)$。

其实这题本质上就是暴搜，全排列的话可以看[这题](https://www.luogu.com.cn/problem/P1706)。判断可行性就不用多说了吧，直接暴力一个个字符串去判断就行了。

# CODE:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
bool b[18]={0};
string s[18],t[18];
inline void dfs(int k)
{
	if(k>n)
	{
		for(register int i=2;i<=n;i++)
		{
			int s=0;
			for(register int j=0;j<m;j++)
			{
				if(t[i][j]!=t[i-1][j]) s++;
				if(s>1) break;
			}
			if(s==0||s>=2) return;
		}
		printf("Yes"),exit(0);
	}
	for(register int i=1;i<=n;i++)
	{
		if(b[i]) continue;
		t[k]=s[i],b[i]=1,dfs(k+1),b[i]=0;
	}
}
int main()
{
    scanf("%d%d",&n,&m);
    for(register int i=1;i<=n;i++) cin>>s[i];
    dfs(1);
    printf("No");
    return 0;
}
```

---

## 作者：_zzzzzzy_ (赞：0)

### 思路
首先我们看这道题的数据范围并不大，发现是暴搜。

我们可以类似枚举每一种组成的情况然后判断组成的情况是否合法，如果在枚举的时候找到了合法的输出 `Yes` 然后直接退出就行了。

这里暴搜的时候我用了 STL 法，在 STL 里面有一个函数叫做 `next_permutation`，他能够将一个序列变成下一个字典序仅次于它的序列，我们只要保证最初的序列是有序的，那么我们就能够不漏的枚举完每一种情况了。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
const int maxn = 1000;
int n, m;
char s[maxn][maxn];
int st[maxn];
vector<int>vec;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> (s[i] + 1);
	}
	for (int i = 1; i <= n; i++) {
		vec.push_back(i);
	}
	do{
		int flag = 0;
		for (int i = 0; i < vec.size() - 1; i++) {
			int cnt = 0;
			for (int j = 1; j <= m; j++) {
				if (s[vec[i]][j] != s[vec[i + 1]][j]) {
					cnt++;
				}
			}
			if (cnt != 1 && cnt != 0){
				flag = 1;
			}
		}
		if (flag == 0){
			cout << "Yes\n";
			return 0;
		}
	}
	while(next_permutation(vec.begin(), vec.end()));
	cout << "No\n";
	return 0;
}
```

---

## 作者：hellolin (赞：0)

## AtCoder Beginner Contest 302 - C - Almost Equal

[洛谷题面](https://www.luogu.com.cn/problem/AT_abc302_c) | [AtCoder 题面](https://atcoder.jp/contests/abc302/tasks/abc302_c) | [AC 记录](https://www.luogu.com.cn/record/111041076) | $\texttt{\color{f2b373}*469}$

要求全排列，我们可以用标准库函数 `prev_permutation`（求前一个）和 `next_permutation`（求后一个），接受参数 `first` 和 `last`，也可以带比较函数 `comp`。

这两个函数会返回将 `[first, last)` 范围内所有以 `<`（或 `comp`）比较的字典序的上/下一个排列，若存在则返回 `true` 并变换排列，若已是第一个/最后一个排列，返回 `false`，并变换排列为最后一个/第一个排列。

``` cpp
vector<int>a;
...
// 若要使用 next_permutation，先保证这个范围是第一个排列（也就是升序）
sort(a.begin(),a.end());
// 要使用 do while 循环，因为第一个排列也是排列
do{
    ...
}while(next_permutation(a.begin(),a.end()));
```

判断是否成立是 $O(NM)$ 的复杂度，所以总结下来时间复杂度为 $O(NM\cdot N!)$，可以通过本题。

（题解文本部分参考了 [cppreference](https://zh.cppreference.com/w/cpp/algorithm/next_permutation)）

``` cpp
// 珍爱账号，拒绝贺题
#include <bits/stdc++.h>
using namespace std;
#define int long long

vector<string>s;
int n,m;
bool f;
bool judge(){
    for(int i=0;i<s.size()-1;i++){
        int p=0;
        for(int j=0;j<s[i].size();j++){
            p+=s[i][j]!=s[i+1][j];
        }
        if(p!=1)return 0;
    }
    return 1;
}
void solve(){
    cin>>n>>m;
    s.resize(n);
    for(string&i:s)cin>>i;
    sort(s.begin(),s.end());
    do{
        if(judge()){
            cout<<"Yes"<<endl;
            return;
        }
    }while(next_permutation(s.begin(),s.end()));
    cout<<"No"<<endl;
}

int32_t main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();

    return 0;
}
```


---

## 作者：lilong (赞：0)

### 题意

有 $n$ 个字符串，它们的长度都为 $m$。问能否通过改变它们的顺序，使得后一个字符串能由前一个字符串**只改变一个字母**而得到？
### 思路

本题数据范围 $ 2 \le N \le 8 $，非常小，因此可以考虑全排列枚举所有的情况，最后检验是否存在符合要求的顺序即可。

代码如下：
```cpp
#include <iostream>
#include <cstdio>

using namespace std;

string s[101],c[101];
int a[101],n,m,pd;

void dfs( int k )
{
	for( int i = 1 ; i <= n ; i ++ )
	{
		if( a[i] == 0 )
		{
			a[i] = 1;
			c[k] = s[i];
			if( k == n )
			{
				int fg = 0,cnt = 0;
				for( int j = 1 ; j < n ; j ++ )
				{
					cnt = 0;
					for( int k = 0 ; k < m ; k ++ )
						if( c[j][k] != c[j + 1][k] )
							cnt ++;
					if( cnt != 1) fg = 1;
				}
				if( !fg ) pd = 1;
			}
			else dfs( k + 1 );
			a[i] = 0;
			c[k] = "";
		}
	}
}

int main()
{
	cin >> n >> m;
	for( int i = 1 ; i <= n ; i ++ )
		cin >> s[i];
	dfs(1);
	if( pd ) cout << "Yes";
	else cout << "No";
	return 0;
}
```


---

## 作者：ran_qwq (赞：0)

注意到 $n$ 和 $m$ 都非常小，可以用 dfs 枚举字符串的所有排列，判断每相邻两个字符串不同字符数是否都恰好为 $1$ 即可。如果有一种排列可以，输出 `Yes`。如果都不行输出 `No`。

时间复杂度 $O(n!m)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=10,INF=0x3f3f3f3f;
int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
void Write(int x){if(x<0){putchar('-'),Write(-x);return;}if(x<10){putchar(x+'0');return;}Write(x/10),putchar(x%10+'0');}
void write(int x,char *s){Write(x),printf("%s",s);}
int n,m,p[N],vis[N];
string s[N];
void dfs(int k)
{
	if(k>n)
	{
		int fg=1;
		for(int i=2;i<=n;i++)
		{
			int cnt=0;
			for(int j=0;j<m;j++) cnt+=s[p[i]][j]!=s[p[i-1]][j];
			if(cnt!=1) fg=0;
		}
		if(fg) puts("Yes"),exit(0);
		return;
	}
	for(int i=1;i<=n;i++)
		if(!vis[i]) vis[i]=1,p[k]=i,dfs(k+1),vis[i]=0;
}
void solve()
{
	n=read(),m=read();
	for(int i=1;i<=n;i++) cin>>s[i];
	dfs(1),puts("No");
}
signed main()
{
	int T=1;
	while(T--) solve();
}

```

---

## 作者：guanyf (赞：0)

### 题意
- 给定 $N$ 个长度为 $M$ 字符串，问能否改变这些字符串的位置，使得俩俩字符串恰好仅一个位置上的字母不同。

- $2 \le N \le 8,1 \le M \le 5$。

### 思路
直接枚举每个字符串所在的位置，在暴力判断就行了。

时间复杂度：$\operatorname{O}(N!\times NM)$。

#### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, id[10];
string s[10];
bool check() {
  for (int i = 1; i < n; i++) {
    int cnt = 0;
    for (int j = 0; j < m; j++) {
      cnt += s[id[i]][j] != s[id[i + 1]][j];
    }
    if (cnt != 1) {
      return 0;
    }
  }
  return 1;
}
int main() {
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> s[i], id[i] = i;
  }
  do {
    if (check()) {
      cout << "Yes", exit(0);
    }
  } while (next_permutation(id + 1, id + 1 + n));
  cout << "No";
  return 0;
}

```


---

