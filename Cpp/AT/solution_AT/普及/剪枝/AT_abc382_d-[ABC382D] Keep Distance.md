# [ABC382D] Keep Distance

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc382/tasks/abc382_d

整数 $ N $ と $ M $ が与えられます。

以下の条件をすべて満たす長さ $ N $ の整数列 $ (A_1,\ A_2,\ \ldots,\ A_N) $ を辞書順にすべて出力してください。

- $ 1\ \leq\ A_i $
- $ 2 $ 以上 $ N $ 以下の各整数 $ i $ に対して $ A_{i\ -\ 1}\ +\ 10\ \leq\ A_i $
- $ A_N\ \leq\ M $
 
  数列の辞書順とは長さ $ N $ の数列 $ S\ =\ (S_1,\ S_2,\ \ldots,\ S_N) $ が長さ $ N $ の数列 $ T\ =\ (T_1,\ T_2,\ \ldots,\ T_N) $ より**辞書順で小さい**とは、ある整数 $ 1\ \leq\ i\ \leq\ N $ が存在して下記の $ 2 $ つがともに成り立つことをいいます。

- $ (S_1,\ S_2,\ \ldots,\ S_{i-1})\ =\ (T_1,\ T_2,\ \ldots,\ T_{i-1}) $
- $ S_i $ が $ T_i $ より（数として）小さい。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 12 $
- $ 10N\ -\ 9\ \leq\ M\ \leq\ 10N $
- 入力される値はすべて整数
 
### Sample Explanation 1

$ (1,\ 11,\ 21),\ (1,\ 11,\ 22),\ (1,\ 11,\ 23),\ (1,\ 12,\ 22),\ (1,\ 12,\ 23),\ (1,\ 13,\ 23),\ (2,\ 12,\ 22),\ (2,\ 12,\ 23),\ (2,\ 13,\ 23),\ (3,\ 13,\ 23) $ の $ 10 $ 個の数列が条件を満たします。

## 样例 #1

### 输入

```
3 23```

### 输出

```
10
1 11 21
1 11 22
1 11 23
1 12 22
1 12 23
1 13 23
2 12 22
2 12 23
2 13 23
3 13 23```

# 题解

## 作者：dg114514 (赞：3)

# [abc382d Keep Distance](https://www.luogu.com.cn/problem/AT_abc382_d) 题解

## 题意
给你 $n,m$，求所有满足以下规则的数列并输出个数：

- 有 $n$ 项。
- 对于 $1 \le i < n$，有 $a_i +10 \le a_{i+1}$。
- $a_n \le m$。

## 思路
看到 $n \le 12$，一眼搜索。\
你打好了[普通搜索](https://www.luogu.com.cn/paste/da0q9sc6)。

试试 `12 120` 的数据，居然 T 了。你很快想到了原因。程序大概运行了 $\prod^{x\div10}_{i=1} 10i = 12!\times 10^{12}$ 次，显然超时。

此时，你注意到 $10n-9 \le m \le 10n$，显然，中间的差一定不大于 $20$，只需要把 `m` 改成 `min(m,x+20)` 即可。 再加一个剪枝，当数即使每次只加 $10$ 最后依然超过 $m$ 时直接回溯。

你又试了一遍 `12 120`，这回没过一会就跑出了结果。遂交，AC。你加上运行计数器，又跑了一遍，计数器大概只有 $10^6$ 量级，可以过。\
[code](https://www.luogu.com.cn/paste/xbirvluf)

---

## 作者：ThomasNO1 (赞：2)

## Problem
[Problem](https://www.luogu.com.cn/problem/AT_abc382_d)
## Solution
首先，我们可以先从 $n$ 下手，因为 $n$ 最多只有 $12$，而 $m$ 最多也只有 $120$，完全可以用暴力搜索。

为了保证不会超时，我们可以加一个小剪枝。当 `a[pos - 1] + 10 * (n - pos) > m`，就直接 `return`。

注意，因为有剪枝，并且要满足 $1 \le A_i$，所以 $A_0$ 要初始化为 $-9$，不然 $A_1$ 就会大于等于 $10$，答案就会出错。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,ans = 0,a[13];
vector<int> A;
void dfs(int pos){
	if(pos > n){
		for(int i = 1;i <= n;i++)
			A.push_back(a[i]);
		ans++;
		A.push_back(-1);
		return;
	}
	if(a[pos - 1] + 10 * (n - pos) > m) return;
	for(int i = a[pos - 1] + 10;i <= m - 10 * (n - pos);i++){
		a[pos] = i;
		dfs(pos + 1);
	}
}
int main(){
	scanf("%d%d",&n,&m);
	a[0] = -9;
	dfs(1);
	printf("%d\n",ans);
	for(auto x : A){
		if(x == -1) printf("\n");
		else printf("%d ",x);
	}
	return 0;
}
```

---

## 作者：_zqh_ (赞：2)

首先我们可以构造出一组最初始的数据：
$$
A = (1, 11, 21, 31, \dots, 10k + 1, \dots, 10(N - 1) + 1)
$$
如果 $10(N - 1) + 1 \gt M$，就无法凑出任何合法序列，输出 `0`。

观察到 $N \le 12$，大概率是一道搜索。

但直接在序列 $A$ 上搜索显然不方便（因为修改任意一个 $A_i$，那么 $A_{i + 1}, A_{i + 2},\dots, A_{N}$ 都要随之修改）。

考虑将序列差分，得：
$$
B = (1, 10, 10, 10, \dots, 10)
$$
此时有：
$$
A_N = \sum_{i = 1}^{N} B_i
$$
那么问题就转化成在 $B$ 数组中任意加数，使得 $B$ 数组的和不超过 $M$。

此时就可以通过一个简单的暴力搜索解决问题。

- 时间复杂度：$\mathcal{O}(n^k)$，其中 $k = M - 10(N - 1) - 1$。
- 空间复杂度：$\mathcal{O}(n)$。

---

```cpp
namespace zqh {
	const int N = 100;
	int n, m;
	vector<int> a;  // 原数组
	vector<vector<int>> b;  // 用双重 vector 存答案
	
	void dfs(int u, int sum) {
		if (sum > m) return;
		if (u == n + 1) {
			b.push_back(a);  // 合法
			return;
		}
		for (int i = 0; i <= m; i++) {
			a[u] += i;
			dfs(u + 1, sum + i);
			a[u] -= i;
		}
	}
	
	void init() {
		cin >> n >> m;
		a = vector<int>(n + 1);
		a[1] = 1;
		for (int i = 2; i <= n; i++) {  // 构造原始数组
			a[i] = 10;
		}
		if ((n - 1) * 10 + 1 > m) return cout << "0", void();
		m -= (n - 1) * 10 + 1;
	}
	
	void solve() {
		dfs(1, 0);
		cout << b.size() << "\n";
		for (int i = 0; i < b.size(); i++) {
			int t = 0;
			for (int j = 1; j <= n; j++) {  // 边输出边将原序列前缀和
				t += b[i][j];
				cout << t << " ";
			}
			cout << "\n";
		}
	}
	
	void main() {
		init();
		solve();
	}
}
```

---

## 作者：cqbzcjh (赞：2)

这道题的数据范围极小，所以直接暴搜。

但这样直接暴搜会超时。我们有一个剪枝，如果当前情况预计最小的 $A_n$（以后每一个数都只间隔 $10$）都大于 $M$，就一定是不合法的。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=20,M=2e5+5;
int n,m,a[N],ans,res[M][N];
void dfs(int x,int pre){//pre为前一个数加10
	if(x==n+1){
		if(a[n]<=m){//判断是否合法
			ans++;
			for(int i=1;i<=n;i++)
				res[ans][i]=a[i];
		}
		return;
	}
	for(int i=pre;;i++){
		if(i+(n-x)*10/*计算预计最小的A[n]*/<=m){
			a[x]=i;
			dfs(x+1,i+10);
			a[x]=0;
		}else break;
	}
}
int main(){
	ios::sync_with_stdio(NULL);
	cin.tie(NULL);cout.tie(NULL);
	cin>>n>>m;
	dfs(1,1);
	cout<<ans<<"\n";
	for(int i=1;i<=ans;i++){
		for(int j=1;j<=n;j++)
			cout<<res[i][j]<<" ";
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：Zskioaert1106 (赞：1)

题目传送门：[[ABC382D] Keep Distance](https://www.luogu.com.cn/problem/AT_abc382_d)

本题考察简单的搜索。

### 题目分析

拿到题后发现可以枚举每一位的可能性，逐步向上的过程中缩小范围。到 $N$ 层后看看满不满足边界的条件（即当前 $A_N$ 是否不大于 $M$），如果是就将这种结果输出。然后返回前一层再看。

### 做题过程

上述方法如果每层都从小到大枚举，那么只有当前字母的可能性试完了才会尝试下一个——字典序比自己大 $1$ 的。所以满足了题目要求。

设搜索到当前第 $i$ 层时的 $A_i$ 值为 $d$，则下一层的可能性是 $d+10$ 到 $M-10(n-i)$。我们将这些可能性枚举深搜下一层，用一个 $k$ 数组来存当前的状态，这样到 $N$ 层时如果条件满足就将 $k$ 的 $N$ 个元素存入答案，否则直接返回，下一次的搜索会覆盖原先的 $k_i$。

文字有些抽象，看代码和注释理解吧。

### 代码编写

你知道吗，我赛时由于 $ans$ 数组开小了一直没调出来（看到仅 WA 的四个点还以为是忘判了什么边界）。

这份代码其实没有到 $N$ 的时候判断，因为不满足条件的都不会进入下一层所以当 $i>n$ 时直接存就好了。

```cpp
#include<iostream>
using namespace std;
int n,m,sum,ans[1000000][13],k[13];
void dfs(int i,int d){
	if(i>n){
		sum++;//存数量，等同题目的 X
		for(int j=1;j<=n;j++)
			ans[sum][j]=k[j];
	}
	else{
		for(int j=d;j+(n-i)*10<=m;j++){//条件枚举
			k[i]=j;//存状态
			dfs(i+1,j+10);//搜索下一层
		}
	}
}
int main(){
	ios::sync_with_stdio(0),cout.tie(0);
	cin>>n>>m;
	dfs(1,1);
	cout<<sum<<'\n';
	for(int i=1;i<=sum;i++){
		for(int j=1;j<=n;j++)
			cout<<ans[i][j]<<' ';
		cout<<'\n';
	}
    return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/192598400)。

---

## 作者：TSY48 (赞：1)

**解题思路**

枚举第一位，后面 dfs 的时候每次从比前一位大 $10$ 的位置开始枚举，上界为 $m$。

具体细节看代码注释。

**代码**
---

```cpp
int n,m;
int loc=0;
vector<int> ans[Maxn];
vector<int> v;
inline void sve(){
    ans[++loc]=v;
}
inline void dfs(int pre,int now,int stp){
    if(stp==n && pre<=m){
        sve(); // 满足条件的直接放到ans里面
        return ;
    }
    if(((n-stp)*10+pre)>m) return ; // 剪枝，如果下面每个都取最小（就是每个都比前一位大10），但最后一个还是>m，就可以直接return
    for(int nxt=pre+10;nxt<=m;nxt++){
      	// 从比前一位大10的地方开始枚举
        vector<int> f;f=v;
        v.pb(nxt);
        dfs(nxt,now-nxt,stp+1);
        v=f; // 回溯
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
      	// 枚举第一位
        v.clear();
        v.pb(i);
        dfs(i,m-i,1);
    }
    printf("%d\n",loc);
    for(int i=1;i<=loc;i++){
        for(int l:ans[i]) printf("%d ",l);
        printf("\n");
    }
    return 0;
}
```

---

## 作者：Beacon_wolf (赞：1)

## 题目思路
从第一个数开始扩展，扩展到 $n$ 个数，可以画出一棵树。

以样例为例，首先可以扩展出 $\left \{ 1 \right \}$，然后由它扩展出 $\left \{ 1,11 \right \}$、$\left \{ 1,12 \right \}$、$\left \{ 1,13 \right \}$，再由它们可以扩展出 $\left \{ 1,11,21 \right \}$、$\left \{ 1,11,22 \right \}$、……（假设上一个数是 $x$，请注意当前的数最多只能扩展到 $m - (n - x - 1) \times 10$。如此例中分别最多只能扩展到 $3$、$13$、$23$。）

由此递归到树的第 $n$ 层，如果解合法则输出。

## AC 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
vector<int> cnt[15];
int n,m,ans[15];
void g(int a,int b){
  //a 代表当前是第几个数，b 代表目前这个数的扩展最大值。
	if(a == n && b <= m){
		for(int i = 0;i < n;i++){
			cnt[i].push_back(ans[i]);
		}
		return;
	}
	for(int i = b + 10;i <= m - (n - a - 1) * 10;i++){
		ans[a] = i;
		g(a + 1,i);
		ans[a] = 0;
	}
} 
int main(){
	cin >> n >> m;
	for(int i = 1;i <= m - (n - 1) * 10;i++){
		ans[0] = i;
		g(1,i);
	}
  //这里存储答案的 cnt 是竖着存储的，如第一个数都存在 cnt[0] 里，第二个数都存在 cnt[1] 里，……
	cout << cnt[0].size() << endl;
	for(int i = 0;i < cnt[0].size();i++){
		for(int j = 0;j < n;j++){
			cout << cnt[j][i] << " "; 
		}
		cout << endl;
	}
	return 0;
}
```

---

## 作者：hjyowl (赞：1)

### 思路

普通的搜索。

每一次，对于当前 $u$ 的位置而言，从 $a_{u-1}+10$ 到 $m$ 之间枚举，然后对于 $u$ 选择范围内的某一个数，然后搜索完了过后记录一下即可。

但是这个做法实际上会超时，我们可以想办法做一个剪枝，如果后面的差值全部都是 $10$ 但是已经超过了 $m$，我们可以把它给舍弃掉，即必须满足 $a_u+(n-u) \times 10 \le m$ 才可以继续搜索下去，这个剪枝让效率提高，代码就可以通过了。

### 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const long long N = 1000010;
long long n,m;
int a[15];
int b[N][15];
int cnt = 0;
void dfs(int u){
	if (u == n + 1){
		cnt ++ ;
		for (int i = 1; i <= n; i ++ ){
			b[cnt][i] = a[i];
		}
		return ;
	}
	for (int i = a[u - 1] + 10; i <= m; i ++ ){
		a[u] = i;
		if (a[u] + (n - u) * 10 <= m){
			dfs(u + 1);
		}
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin >> n >> m;
	a[0] = -9;
	dfs(1);
	cout << cnt << "\n";
	for (int i = 1; i <= cnt; i ++ ){
		for (int j = 1; j <= n; j ++ ){
			cout << b[i][j] << " ";
		}
		cout << "\n";
	}
	return 0;
}
```

---

## 作者：xyx404 (赞：1)

## 思路：
题目要求求出所有的方案，考虑 dfs 找出每个方案。

利用深度优先搜索找出所有方案，遇到可能方案时存下来，并使我们用来记录一共有几个可能结果的变量加一，最后输出有几种可能和所有可能的方案。

注意 dfs 里要按从小到大的顺序搜。

## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define itn int
#define ull unsigned long long
int n,m;
int ans[15],cnt;
vector<int>anss;
void print(){
	cnt++;
	for(int i=1;i<=n;i++){
		anss.push_back(ans[i]);
	}
//	anss+="\n";
	return ;
}
void dfs(int now,int v){
//	cout<<v
	if(now==n+1){
		print();return;
	}
	if(v>m)return;
	for(int i=v;i<=m-(n-now)*10;i++)ans[now]=i,dfs(now+1,i+10);
	return ;
}
int main(){
	cin>>n>>m;
	dfs(1,1);
	cout<<cnt<<"\n";
	for(int i=0;i<anss.size();i++){
		cout<<anss[i]<<" ";
		if(i%n==n-1)cout<<"\n";
	}
	return 0;
}
```
[AC 记录](https://atcoder.jp/contests/abc382/submissions/60336066)。

---

## 作者：_colin1112_ (赞：1)

## 思路



1. 确定每个位置的取值范围：

   - 初始元素 $A_1$：

     - 最小值：$A_1 \geq 1$。
     - 最大值：由于后续每个元素至少需要比前一个元素大 $10$，且最终元素 $A_N \leq M$，因此 $A_1$ 的最大值为 $M - 10 \times (N - 1)$。
     - 因此，$A_1$ 的取值范围为 $[1, M - 10 \times (N - 1)]$。

   - 后续元素 $A_i$（$2 \leq i \leq N$）：

     - 最小值：$A_i \geq A_{i-1} + 10$。
     - 最大值：考虑剩余的元素还需要占用的最小值，即每个剩余元素至少需要占用 $10$ 的增量，总共需要 $10 \times (N - i)$，因此 $A_i$ 的最大值为 $M - 10 \times (N - i)$。
     - 因此，$A_i$ 的取值范围为 $[A_{i-1} + 10, M - 10 \times (N - i)]$。

2. 递归构造序列（深度优先搜索 DFS）：

   - 状态定义：当前位置 `pos`（从 $0$ 开始，即 $A_{pos+1}$），当前已构造的序列 `seq`。
   - 递归边界：当 `pos == N` 时，表示序列已构造完毕，将其加入答案集合。
   - 递归过程：
     - 在当前位置，根据取值范围遍历可能的值。
     - 将当前值加入序列 `seq`，继续递归下一位置 `pos + 1`。
     - 递归返回后，需回溯（即从序列中移除当前值）以尝试下一个可能的值。

3. 剪枝优化：

   - 取值范围不合法时提前返回：如果当前计算得到的取值范围为空（即左边界大于右边界），则无需继续递归，直接返回。
   - 保证字典序：由于我们总是从小到大尝试可能的值，递归生成的序列天然按照字典序排列，无需额外排序。

最后输出 `ans.size` 和 ans 内的内容即可。

## Code

```cpp
#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;
const int E = 1e6 + 5;
ll n, m;
vector<vector<ll>> ans;
inline void solve(ll pos, vector<ll> &seq)
{
    if (pos == n)
    {
        ans.push_back(seq);
        return;
    }
    ll l;
    if (pos == 0)
        l = 1;
    else
        l = seq[pos - 1] + 10;
    ll r = m - 10 * (n - pos - 1);
    for (int i = l; i <= r; i++)
    {
        seq.push_back(i);
        solve(pos + 1, seq);
        seq.pop_back();
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    vector<ll> seq;
    solve(0, seq);
    cout << ans.size() << endl;
    for (auto &s : ans)
    {
        for (auto v : s)
            cout << v << ' ';
        cout << endl;
    }
    return 0;
}
```

---

## 作者：sherry_lover (赞：0)

# AT_abc382_d [ABC382D] Keep Distance 题解

[题目传送门](https://www.luogu.com.cn/problem/AT_abc382_d)

## 思路

看到如此大的时限和如此小的数据范围，不难想到暴搜。

枚举第一个数，然后每次暴搜下一个数加几，注意要判断范围，否则会 TLE，但是赛时居然过了。

TLE Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[15],tot;
vector<int> ans[500005];
void dfs(int k,int x)
{
    if(k == n+1)
    {
    	tot++;
    	for(int i = 1;i <= n;i++) ans[tot].push_back(a[i]);
        return;
    }
    for(int i = 10;;i++)
    {
        if(x+i > m) break;
        a[k] = x+i;
        dfs(k+1,x+i);
    }
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
    cin >> n >> m;
    for(int i = 1;i <= m-10*(n-1);i++)
    {
        a[1] = i;
        dfs(2,i);
    }
    cout << tot << "\n";
    for(int i = 1;i <= tot;i++)
    {
    	for(auto j:ans[i]) cout << j << " ";
    	cout << "\n";
	}
	return 0;
} // TLE on #29，赛时 AC，见 Submission #60332483
```

AC Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int read()
{
	int x = 0,w = 1;
	char ch = 0;
 	while(ch < '0' || ch > '9')
	{
		if(ch == '-') w = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9')
	{ 
    	x = x*10 + (ch-'0');
    	ch = getchar();
  	}
  	return x*w;
}
void write(int x)
{
  	static int sta[35];
  	int top = 0;
  	do{
  		sta[top++] = x % 10, x /= 10;
  	}while(x);
  	while(top) putchar(sta[--top]+48);
}
int n,m,a[15],tot,ans[400005][20];
void dfs(int k,int x)
{
    if(k == n+1)
    {
    	tot++;
    	for(int i = 1;i <= n;i++) ans[tot][i] = a[i];
        return;
    }
    for(int i = 10;x+i <= m;i++)
    {
		if(x+i+10*(n-k-1) > m) break; //判断后面是否存在可行的方案
        a[k] = x+i;
        dfs(k+1,x+i);
    }
}
int main()
{
	n = read();
	m = read();
    for(int i = 1;i <= m-10*(n-1);i++)
    {
        a[1] = i;
        dfs(2,i);
    }
    write(tot);
    putchar('\n');
    for(int i = 1;i <= tot;i++)
    {
    	for(int j = 1;j <= n;j++)
    	{
    		write(ans[i][j]);
    		putchar(' ');
		}
    	putchar('\n');		
	}
	return 0;
}
```

---

## 作者：linjinkun (赞：0)

简单搜索题。

就是正常的搜索就行了，但是有几个点需要注意：

- 对每一位进行搜索的时候，不能搜无用的，否则可能会超时（我没试过），具体就是从上一位的数加上 $10$ 开始搜索。

- 还有，对每一位进行搜索，当发现 $i+(n-x) \times 10 > m$ 时，$i$ 是当前这一位要设置的数，$x$ 是当前位数，停止继续找其他的数，因为如果按照这个数进行下去的话，最末尾的数，也就是 $a_n$，将会大于 $m$，是不满足题目要求的。

搜索的流程就是设置一个 dfs 函数，然后一位一位的去填就好了。

这里给个框架（对于此类题目）：
```cpp
void dfs(int x,此处还可以自由添加其它参数)
{
    if(x == n+1)//n位全部设置好
    {
      记录;
      return;
    }
  遍历所有解
     {
       if(此解合法)
       {
         记录这一位填的数;
         dfs(x+1,根据上面设置的函数);
       }
     }    
}
```
然后再给代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int M = 20;
const int N = 1e7+5;//这个1e7是瞎开的，因为输出量肯定不会大于1e7，否则输出就超时了
int a[M];
int b[N][M];
int n,m;
int cnt;
void dfs(int x,int last)//last表示上一个数
{
	if(x == n+1)
	{
     //记录
		cnt++;
		for(int i = 1;i<=n;i++)
		{
			b[cnt][i] = a[i];
		}
		return;
	}
	for(int i = last+10;i+(n-x)*10<=m;i++)//遍历解
	{
      //因为这所有的i都是合法解，就不需要判断了
		a[x] = i;//记录
		dfs(x+1,i);
	}
}
signed main()
{
	scanf("%d %d",&n,&m);
	dfs(1,-9);//这里last是-9主要是方便，因为-9+10 = 1，第一位刚好就是从1开始
	printf("%d\n",cnt);//输出个数
	for(int i = 1;i<=cnt;i++)
	{
		for(int j = 1;j<=n;j++)
		{
			printf("%d ",b[i][j]);
		}
		printf("\n");
	}
	return 0;
}
```
最后说一下怎么证明搜索不会超时，因为我们这个搜索它每一次遍历的解不会有非法解，所以只需要知道最多会有几个合法解就行了，因为输出把所有合法解都打印了，那合法解的数量就不会太多，否则输出就会超时，证毕。

---

## 作者：Liuhy2996 (赞：0)

## 思路
DFS，用 $sum$ 记录每个 $a_i$ 比 $a_{i-1}+10$ 多的值的和，最终让 $sum\le m-10n+9$ （$a_i$ 最小为 $10i-9$）。既然要求字典序从小到大，那 DFS 时从小到大枚举 $a_i$ 即可。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=4e6+10;
int n,m,t,a[N];
vector<int>ans[N];
void dfs(int p,int sum){
	if(p>n){
		++t;
		for(int i=1;i<=n;++i) ans[t].push_back(a[i]);
		return;
	}
	for(int i=0;sum+i<=m-10*n+9;++i) a[p]=a[p-1]+10+i,dfs(p+1,sum+i);
}
signed main(){
	cin>>n>>m;
	a[0]=-9,dfs(1,0);
	cout<<t<<endl;
	for(int i=1;i<=t;++i){
		for(int j:ans[i]) printf("%d ",j);
		puts("");
	}
	return 0;
}
```

---

## 作者：Allen_yang (赞：0)

## 题目描述
你需要求出所有长度为 $n$，且满足以下条件的序列的个数，并按照字典序输出：
首项大于等于 $1$， 每一项比前一项至少大 $10$，最后一项小于等于 $m$。
## 题目分析
爆搜，用 vector 存储答案和个数，输出。
## 代码实现
```cpp
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
struct Node{
	int a[15];
};
vector<Node> res;
int ans[15];
int n, m;
void dfs(int step){
	if(step == n + 1){
		if(ans[n] > m)return;
		Node x;
		for(int i = 1; i <= n; i ++){
			x.a[i] = ans[i];
		}
		res.push_back(x);
		return;
	}
	int low;
	if(step > 1)low = ans[step - 1] + 10;
	else low = 1;
	for(int i = low; i <= m - (n - step) * 9; i ++){
		ans[step] = i;
		dfs(step + 1);
	}
}
int main(){
	cin >> n >> m;
	dfs(1);
	cout << res.size() << "\n";
	for(auto it : res){
		for(int i = 1; i <= n; i ++){
			cout << it.a[i] << " ";
		}
		cout << "\n";
	}
	return 0;
}
```

---

## 作者：JXR_Kalcium (赞：0)

## 题目大意

给定两个数 $N,M$，需以字典序升序输出满足条件的长度为 $N$ 的序列 $A_1,A_2,\cdots,A_N$ 并求出它们的个数，这个序列满足条件当且仅当：

- $A_1\ge 1$；
- 对于每一个 $2\le i\le N$ 都有 $A_{i-1}+10\le A_i$；
- $A_N\le M$。

数据范围 $N\le 12,M\le 10N$。

## 解题思路

因为 $N$ 极小，且最终满足条件的序列个数不会超过 $\textrm{C}_{21}^{9}=293930$，所以考虑使用 DFS 暴力求解。对于每一位 $i$，首先置初值 $res$ 为 $A_{i-1}+10$（若 $i=1$ 则初值为 $1$），于是考虑贪心，后面的每一位都填最小值，即 $A_{i-1}+10$，则易得若最终的 $A_N\le M$ 则必须满足 $res+10(N-i)\le M$，枚举所有的 $res$ 转移即可。

## AC 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define endl putchar(10)
#define spc putchar(32)
#define R register
using namespace std;
#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x << " = " << x, endl
#endif

inline ll read()
{
    ll x=0,f=1; char c=getchar();

    while(c<48 || c>57)
    {
        if(c=='-') f=-1;
        c=getchar();
    }

    while(c>47 && c<58)
    x=(x<<1)+(x<<3)+c-48, c=getchar();
    return x*f;
}

inline void write(ll x)
{
    static ll sta[41]; ll top=0;
    if(x<0) putchar('-'), x=-x;
    do sta[top++]=x%10, x/=10; while(x);
    while(top) putchar(sta[--top]+48);
}

ll n,m,cnt,a[21],ans[1000001][21];

void dfs(ll x)
{
    if(x==n+1)
    {
        ++cnt;
        for(R int i=1; i<=n; ++i)
        ans[cnt][i]=a[i]; return;
    }

    ll res=x<2?1:a[x-1]+10;
    while(res+(n-x)*10<=m)
    a[x]=res++, dfs(x+1); a[x]=0;
}

int main()
{
    n=read(); m=read();
    dfs(1); write(cnt); endl;
    
    for(R int i=1; i<=cnt; ++i)
    {
        for(R int j=1; j<=n; ++j)
        write(ans[i][j]), spc; endl;
    }

    return 0;
}
```

---

## 作者：wht_1218 (赞：0)

### 题面简述：

生成一个长度为 $N$ 的序列 $A$，满足 $A_i-A_{i-1}\ge 10,1<i\le N$，且 $A_1\ge 1,~A_n\le M$。求这种序列的总个数以及所有的这种序列。

### 解法：

由于 $N$ 较小故选择全部枚举，使用搜索算法

。

如果是不剪枝的搜索大概是过不了~~要不然就不会放在这里了~~，我们在搜索时增加可行性剪枝即可。（判断每次增加 $10$ 是否可以使最后一个数 $\le M$。）

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[15];
int n,m;
vector<vector<int> > ans;
void dfs(int now,int lv) {
    if (now==n+1) {
    	vector<int> p;
        for(int i=1;i<=n;++i)p.push_back(a[i]);
        ans.push_back(p);
		return;
    }
    int nxt=lv+10;
    while (nxt+(n-now)*10<=m) {//最重要的地方
        a[now]=nxt;
        dfs(now+1,nxt);
        a[now]=0;
        nxt++;
    }return;
}

int main() {
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>n>>m;
	dfs(1,-9);
	cout<<ans.size()<<"\n";
	for(auto x:ans){
		for(auto y:x)cout<<y<<" ";
		cout<<"\n";
	} 
    return 0;
}
```

---

## 作者：long_long__int (赞：0)

# 题目翻译：

让你数出 $n$ 个数，最后一个不大于 $m$，使从第二个数开始的每个数都比前一个数多 $10$ 以上的方案总数及具体方案。

# 题目解法

首先，看到方案总数就可以想到 DFS，但是因为要先输出方案总数，所以可以把答案存起来，等到最后在输出。

DFS 的时候要注意：

1. 不能让总和超过 $n$。
2. 可以加一个剪枝，如果上一个加上还要分几个乘 $10$ 大于 $m$ 就 `return` 掉，即 `if(last+(n-step)*10>m) return;`。
3. 从上一个加 $10$ 开始枚举！不要搞错了！~~我就在这卡了半天。~~

代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m;
int a[100];
int ans[1000500][105];
int cnt=0;
void dfs(int now,int step){
//	cout<<now<<" "<<step<<"\n";
	a[step]=now;
	if(now+(n-step)*10>m){
//		cout<<now+(n-step)*10<<" "<<now<<" "<<step<<"\n";
		return;
	}
	if(step>=n){
		++cnt;
		for(int i=1;i<=n;i++){
			ans[cnt][i]=a[i];
		}
//		puts("");
		return;
	}
	for(int i=now+10;i<=m;i++){
		dfs(i,step+1);
	}
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		dfs(i,1);
//		puts("");
	}
	printf("%lld\n",cnt);
	for(int i=1;i<=cnt;i++){
		for(int j=1;j<=n;j++){
			cout<<ans[i][j]<<" ";
		}
		puts("");
	}
	return 0;
}

```

---

## 作者：T_TLucas_Yin (赞：0)

注意到既然要输出所有方案，所以方案肯定是要全部枚举一遍的。因此我们直接暴力 DFS 找出所有答案即可。

要注意边界条件的判断。对于 $A_i$，根据题目要求，由于它至少比 $A_{i-1}$ 大 $10$，所以这个数可能取值的左端点即为 $A_{i-1}+10$。同理，由于每一个元素都要比前一个元素大 $10$，所以 $A_i$ 必须满足 $A_i+10(N-i)\le M$，才能让 $A_N\le M$。枚举时，若 $A_i$ 已不满足条件就结束枚举即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,top;
int a[15],f[1000005][15];
void print(){
	++top;
	for(int i=1;i<=n;i++) f[top][i]=a[i];
}
void dfs(int k,int x){
	if(k==n+1){ print();return; }
	for(int i=x;i+(n-k)*10<=m;i++){
		a[k]=i,dfs(k+1,i+10);
	}
}
int main(){
	scanf("%d %d",&n,&m);
	dfs(1,1);
	printf("%d\n",top);
	for(int i=1;i<=top;i++){
		for(int j=1;j<=n;j++) printf("%d ",f[i][j]);
		printf("\n");
	}
	return 0;
}
```

---

## 作者：Imerance1018 (赞：0)

### Description

[传送门](https://atcoder.jp/contests/abc382/tasks/abc382_d)

### Solution

注意到 $n \le 12$，直接暴力进行搜索。

提醒：考虑极限情况 $n=12$，$m=120$，此时方案约有 $3 \times 10^5$ 种，数组别开小了。（实在不行跑两遍 dfs 也能过，毕竟给了 5 秒）

### Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m;
int a[20],ans;
void dfs1(int x)
{
	if(x==n)
	{
		if(a[n]<=m)
		{
			ans++;
		}
		return;
	}
	for(int i=10;i<=m-a[x]-(n-x-2)*10;i++)
	{
		a[x+1]=a[x]+i;
		if(a[x+1]<=m)dfs1(x+1);
		a[x+1]=0;
	}
}
void dfs2(int x)
{
	if(x==n)
	{
		if(a[n]<=m)
		{
			for(int i=1;i<=n;i++)cout<<a[i]<<" ";
			cout<<endl;
		}
		return;
	}
	int sum=0;
	for(int i=10;i<=m-a[x]-(n-x-2)*10;i++)
	{
		a[x+1]=a[x]+i;
		if(a[x+1]<=m)dfs2(x+1);
		a[x+1]=0;
	}
}
signed main()
{

	cin>>n>>m;
	for(int i=1;i<=m/n;i++)
	{
		a[1]=i;
		dfs1(1);
		a[1]=0;
	}
	cout<<ans<<endl;
	for(int i=1;i<=m/n;i++)
	{
		a[1]=i;
		dfs2(1);
		a[1]=0;
	}
	return 0;
}
``````

---

## 作者：maurisehu (赞：0)

我们先来看如何生成所有满足条件的序列。因为要按字典序排列，首先要找“最小”的一个可行序列。根据要求，第一位至少是1；之后每一位至少比前一位增加10，由此得到：

- $(1, 11, 21, ..., 10N-29, 10N-19, 10N-9)$ 。

根据数据的范围条件，这里最后一位 $10N-9 \leq M$， 肯定是一个可行的序列。排在它后面的应该是前面 $N-1$ 位不变，最后一位依次增加 1 所形成的序列，直到最后一位增加到 $M$ ：

- $(1, 11, 21, ..., 10N-29, 10N-19, 10N-9)$ 
- $\vdots$
- $(1, 11, 21, ..., 10N-29, 10N-19, M)$ 。

现在最后一位已经不能增大了，所以需要倒数第二位增加1。和普通的整数类似的，倒数第二位增加1之后，最后一位应当先变成其允许的最小值，再逐渐增加到允许的最大值：

- $(1, 11, 21, ..., 10N-29, 10N-18, 10N-8)$ 
- $\vdots$
- $(1, 11, 21, ..., 10N-29, 10N-18, M)$ 。

当然为了让这一组序列不为空，显然我们需要有 $10N-8 \leq M$ 成立才行。再考虑倒数第二位能够到达的最大值。由于最后一位最大能够达到 $M$，那么倒数第二位最大能够到达 $M-10$。这样如果我们保持前 $N-2$ 位不变的前提下，能够达到的最大序列应当是：

- $(1, 11, 21, ..., 10N-29, M-10, M)$ 。

此时需要将倒数第三位加1，并将后面两位置为最小值。再重复此过程并类推下去，直到最终每一位都不能增大为止。

总结一下。我们可以将这个序列视为一个 $N$ 位的“数”。其最小可以取到上面给出的  $(1, 11, 21, ..., 10N-29, 10N-19, 10N-9)$ 。之后的序列可以按照下面的方式生成：
- 首先尝试将第 $N$ 位加一；
- 若第 $N$ 位超过其最大值 $M$ ，则向上一位（即第 $N-1$ 位）“进位”，让上一位加一；
- 若进位后第 $N-1$ 位超过其最大值 $M-10$，则再向上一位“进位”。如此一直向左侧进行。
  - 若找到一个第 $i$ 位，在获得“进位”后没有超过其最大值 $M-10(N-i)$，则终止进位的流程，并按照 $A_{j+1} = A_{j} + 10$ 的规则重新第 $i+1, ..., N$ 位；
  - 否则，若第 1 位都获得“进位”后并且超过其可能的最大值 $M-10(N-1)$，则已经没有更大的可行序列了。

然后我们来看可行序列的个数。对于每一个可行的序列 $(A_1, ..., A_N)$， 我们引入一个新的序列 $(B_1, B_2, ..., B_N, B_N+1)$ 来辅助计算，这里：
- $B_1 = A_1 - 1$ ；
- 对 $i=2, ..., N$， $B_i = A_i - (A1_{i-1}+10)$ ；
- $B_{N+1} = M - A_N$ 。

显然这里 $B_1, B_2, ..., B_N$ 可以分别视为 $A_1, ..., A_N$ 各自比该位置上当前可以取得的最小值要大多少。而对齐求和有

$$
B_1 + B_2 + ... + B_N + B_{N+1} 
= (A_1-1) + (A_2-A_1-10) + ... + (A_N-A_{N-1}-10) + (M-A_N)
= -1 - 10*(N-1) + M = M - 10N + 9.
$$

因此我们可以视为总体有 $(M-10N+9)$ 个“点”，$B_1, ..., B_N$ 的值就是将这些“点”分配加到 $A_1, ..., A_N$ 上去，最后 $B_{N+1}$ 中是剩下没有用到的“点”。不同的加“点”方式对应不同的有效序列。而 $(M-10N+9)$ 个“点” 加到 $N+1$ 个 $B_i$ 上，可以视为在 $N+1$ 个 $B_i$ 中选择 $(M-10N+9)$ 次，允许重复选择的组合数。如果是 $u$ 个数中选 $v$ 个的允许重复组合，其组合数量是 $C_{u+v-1}^v = C_{u+v-1}^{u-1}$。因此我们这里可行的序列数就是 $C_{M-9N+9}^N$ 。这里的组合数还是可以通过杨辉三角形递推求得。

（实际上在比赛中也可以不用推导这个可行数量怎么计算，有了前面生成所有可行序列的方法之后跑两遍，第一遍计数，第二遍输出具体方案，时间上也是可以过得去的，毕竟组合数最后也得做二维循环来递推。）

```cpp
#include<bits/stdc++.h>
using namespace std;

int va[15];

int64_t comb(int u, int v) {
    // calculate C(u, v)
    int ii, jj;
    vector<int64_t> vec;
    vec.resize(v+1);
    vec[0]=1;
    for (ii=1 ; ii<=u ; ++ii) {
        if (ii<=v) { vec[ii]=1; }
        for (jj=min(ii-1, v) ; jj>0 ; --jj) {
            vec[jj] += vec[jj-1];
        }
    }
    return vec[v];
}

int main() {
    int n, m, ii;
    int64_t resu;
    cin >> n >> m;

    // cerr << " chk: C(" << m+9-9*n << ", " << n << ")" << endl;
    cout << comb(m+9-9*n, n) << endl;

    va[1]=1; 
    for (ii=2 ; ii<=n ; ++ii) { va[ii] = va[ii-1] + 10; }
    while (true) {
        for ( ; va[n]<=m ; va[n]+=1) {
            for (ii=1 ; ii<=n ; ++ii) { cout << va[ii] << " "; }
            cout << endl;
        }
        for (ii=n-1 ; ii>0 ; --ii) {
            if (va[ii]<m-10*(n-ii)) { break; }
        }
        if (ii==0) { return 0; }
        va[ii] += 1; ++ii;
        for ( ; ii<=n ; ++ii) { va[ii] = va[ii-1] + 10; }
    }

    return 0;
}
```

---

## 作者：Guoguo2013 (赞：0)

这次 D 题好水啊，感觉 D 严格小于 C。
### 题意简介：
给你 $N$ 和 $M$，定义一个长度为 $N$ 的序列 $A$ 是“好的”当且仅当对于每个 $A_i(i \geq 2)$ 都有 $A_i - A_{i-1} \geq 10$，并且 $A_N \leq M$。

问：对于指定的 $N$ 和 $M$，有多少个序列是“好的”，把它们都给输出出来。

### 思路：
两遍 DFS，一遍搜数量，一边搜具体数列，只要加剪枝，就不会爆时间，具体实现看代码。

### 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
#define PII pair< int, int >

using namespace std;

const int N = 1e5 + 5, mod = 998244353;
int n, m, ans, a[N];

template< typename T >inline void read(T &x){bool f=1;x=0;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=!f;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}x=(f?x:-x);return;}
template< typename T, typename ... L > void read(T &a , L && ... b) { read(a); read(b ...); }
int ksm(int a, int b, int p){int ans = 1;while(b){if(b & 1)ans =(ans*a)%p;b >>= 1;a = (a*a) % p;}return ans;}
void dfs1(int i, int dn){
	if (dn == n){
		ans++;
		return ;
	}
	for (int j = i + 10; ; j++){
		if (m < j + (n - dn - 1) * 10) break; // 即使每一步都压到最小，最后也会大于 M。
		dfs1(j, dn + 1);
	}
}
void dfs2(int i, int dn){
	if (dn == n){
		for (int j = 1; j <= n - 1; j++) printf("%lld ", a[j]);
		printf("%lld\n", i);
		// 输出答案
		return ;
	}
	a[dn] = i; // 记录答案
	for (int j = i + 10; ; j++){
		if (m < j + (n - dn - 1) * 10) break; // 见上
		dfs2(j, dn + 1);
	}
}
signed main(){
//	freopen("a.in", "r", stdin);
//	freopen("a.out","w",stdout);
	read(n, m);
	for (int i = 1; i <= m - 10 * (n-1); i++) dfs1(i, 1); // 跟 if (m < j + (n - dn - 1) * 10) break; 一个道理。
	printf("%lld\n", ans);
	for (int i = 1; i <= m - 10 * (n-1); i++) dfs2(i, 1);
	return 0;
}

```
\|  
\| 最后能点个赞吗，球球了。  
v

---

