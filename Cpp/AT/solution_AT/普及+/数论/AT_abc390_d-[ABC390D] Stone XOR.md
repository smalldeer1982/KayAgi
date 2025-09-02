# [ABC390D] Stone XOR

## 题目描述

有编号为袋 $1$, 袋 $2$, $\ldots$, 袋 $N$ 的 $N$ 个袋子。  
袋 $i$ $(1 \leq i \leq N)$ 中包含 $A_i$ 个石子。

高桥君可以重复以下操作任意次数（包括 $0$ 次）：

> 选择两个袋 A 和 B，将袋 A 中的 **所有** 石子转移到袋 B 中。

请计算操作结束后，以下值可能的不同取值数量：

- 设袋 $i$ 中的石子数量为 $B_i$，计算 $B_1 \oplus B_2 \oplus \cdots \oplus B_N$ 的值。  
  其中 $\oplus$ 表示异或。

异或的定义如下：对于非负整数 $a, b$，$a \oplus b$ 的二进制的 $2^k$ 位（$k \geq 0$）为 $1$ 当且仅当 $a$ 和 $b$ 的二进制表示中该位恰好有一个为 $1$，否则为 $0$。

例如，$3 \oplus 5 = 6$（二进制表示为 $011 \oplus 101 = 110$）。  
一般地，$k$ 个非负整数 $x_1, x_2, \ldots, x_k$ 的异或 $x_1 \oplus x_2 \oplus \cdots \oplus x_k$ 定义为 $(\cdots((x_1 \oplus x_2) \oplus x_3) \oplus \cdots \oplus x_k)$，且与运算顺序无关（已证明）。注意：在本题约束下，操作结束后可能的不同异或值数量是有限的（已证明）。


## 说明/提示

### 约束条件

- $2 \leq N \leq 12$
- $1 \leq A_i \leq 10^{17}$
- 输入均为整数

### 样例解释 1

例如，若高桥君选择袋 $1$ 和袋 $3$ 进行操作，则袋 $1, 2, 3$ 中的石子数量分别变为 $0, 5, 9$。此时异或值为 $0 \oplus 5 \oplus 9 = 12$。其他可能的异或值包括 $0$ 和 $14$。因此共有 $3$ 种可能值，输出 $3$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3
2 5 7```

### 输出

```
3```

## 样例 #2

### 输入

```
2
100000000000000000 100000000000000000```

### 输出

```
2```

## 样例 #3

### 输入

```
6
71 74 45 34 31 60```

### 输出

```
84```

# 题解

## 作者：_JF_ (赞：12)

[Link](https://www.luogu.com.cn/problem/AT_abc390_d)

先 E 后 D，我还是太唐了。

你真的会搜索吗？不错的搜索剪枝题。

我们考虑这样的一种搜索方式，相当于有 $n$ 个盒子，我们把这 $n$ 个数随便扔到某个盒子里面去，然后计算答案。

这样时间复杂度大概是 $O(n\times n^n)$ 状物，非常倒闭。

但是我们注意到不少状态是重复的。

我们可以注意到对于第一个数，我们放在任意一个盒子，是同一个效果，所以我们钦定放在第一个，第二个数只有放在第一个或第二个才有效果。

所以我们对于第 $i$ 个数，只用枚举放在前 $i$ 个盒子里面。这样我们就优化到了 $O(n\times n!)$，还是不够。

其实还能再优化一下，我们只能放到第一个为 $0$ 的位置，往后放效果都是一样的。

计算一次答案是 $O(n)$ 级别的，还是很浪费时间。继续考虑优化，就是你边加数边计算，根据 $x \oplus x=0$ 性质即可。

然后标记数字直接用 umap 即可，我开始用 map 没过。

然后就过了，经过最后一次的优化后，方案数是贝尔数级别的，$n=12$ 可以通过，~~虽然我不知道为啥。~~


这就是实现精细些的巨大效果。如何呢。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =1e3+10;
#define int long long 
double eps=1e-7;
vector<int> g[N];
int a[N],Ans,n,Now[N];
unordered_map<int,int> mp;
void dfs(int dis,int preans){
	if(dis==n+1){
		if(!mp.count(preans))	Ans++,mp[preans]=true;
		return ;
	}
	for(int i=1;i<=n;i++){
		if(Now[i]==0&&Now[i-1]==0)	break;
		int lst=preans;
		preans^=Now[i],Now[i]+=a[dis],preans^=Now[i];
		dfs(dis+1,preans);
		Now[i]-=a[dis],preans=lst;
	}
}
signed main(){
	cin>>n,Now[0]=100;
	for(int i=1;i<=n;i++)	cin>>a[i];
	dfs(1,0);
	cout<<Ans<<endl;
	return 0;
}

```

---

## 作者：pengluochen1227 (赞：4)

[Link](https://www.luogu.com.cn/problem/AT_abc390_d)

### 题意

把 $n$ 个数分成若干组，求每组数之和的异或和。

### 思路

看到数据范围 $2 \leq n \leq 12$ 很容易就能想到 dfs 。

数组记录每一堆的和，每次搜完把结果存到 `unordered_map` 里面（ `map` 会超），最后输出 `unordered_map` 里面数的个数就是答案。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, a[20], b[20];// b 记录每一堆的和。
unordered_map<int, bool> mp;// 记录答案。
void dfs(int s, int cnt, int v){// s 当前搜的位置，cnt 记录当前堆数，v 记录当前异或和。
	if (s > n){
		mp[v] = 1;// 搜完了记录答案。
		return;
	}
	for (int i = 1; i < cnt; i ++){// 加在有数的堆里面。
		int now = v ^ b[i];// 去掉原来的异或值。
		b[i] += a[s];
		dfs(s + 1, cnt, now ^ b[i]);// 加上现在的。
		b[i] -= a[s];// 回溯。
	}
	b[cnt] = a[s];
	dfs(s + 1, cnt + 1, v ^ a[s]);// 新一堆。
	b[cnt] = 0;
}
signed main(){
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i ++){
		cin >> a[i];
	}
	dfs(1, 1, 0);
	cout << mp.size();
	return 0;
}
``````

---

## 作者：灵茶山艾府 (赞：4)

问题相当于把 $a$ 划分成若干个集合。

用回溯实现，对于 $a_i$：

- 单独形成一个集合。
- 加到前面的某个集合中。

用一个数组 $b$ 存储每个集合的元素和。

AC 代码（Golang）：

```go
package main
import ."fmt"

func main() {
	var n int
	Scan(&n)
	a := make([]int, n)
	for i := range a {
		Scan(&a[i])
	}

	ans := map[int]bool{}
	b := []int{}
	var dfs func(int, int)
	dfs = func(i, xor int) {
		if i == n {
			ans[xor] = true
			return
		}
		v := a[i]
		// a[i] 单独组成一个集合
		b = append(b, v)
		dfs(i+1, xor^v)
		b = b[:len(b)-1]
		// a[i] 加到前面的集合中
		for j := range b {
			b[j] += v
			dfs(i+1, xor^(b[j]-v)^b[j])
			b[j] -= v
		}
	}
	dfs(0, 0)
	Print(len(ans))
}
```

---

## 作者：Emplace (赞：3)

## 思路
其实这道题就是一个暴搜。

可以给搜索的每一层定义为 $A$ 数组中的每一个数。然后这个数可以选择加入当前 $B$ 中已有石子的袋子中，也可以选择单开一个。然后搜完以后，将 $B$ 数组中的所有石子数异或一下，最后检查有没有出现过就行（用 ```unordered_map``` 储存）。

## Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[20],b[20],m,ans;
unordered_map<int,int> mm;
void dfs(int x,int m){
//	cout<<x<<" "<<m<<endl;
	if(x==n+1){
		int x_or=0;
		for(int i=1;i<=m;i++){
			x_or^=b[i];
//			cout<<b[i]<<" ";
		}
	//	cout<<endl<<x_or<<endl;
		if(!mm.count(x_or)){
			mm[x_or]=1;
			ans++;
		}
		return ;
	}
	for(int i=1;i<=m;i++){
		b[i]+=a[x];
		dfs(x+1,m);
		b[i]-=a[x];
	}
	b[m+1]=a[x];
	dfs(x+1,m+1);
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	dfs(1,0);
	cout<<ans;
	return 0;
}

```

---

## 作者：sodalyghat (赞：3)

### 思路
这种题又有加又有异或，是不好去维护的，但是它的数据范围给的这么小，复杂度是阶乘都是可以过的，所以就直接搜索了。注意实现，在去重的时候用快一点的东西，不然会被卡常。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
namespace Luo_ty{
	const int MAXN = 1005;
	int a[MAXN];
	int sum[MAXN], cnt, xsum, ans;
	unordered_map<int, bool> t;
	int n;
	void dfs(int now){
		if(now == n + 1){
			if(!t[xsum]){
				t[xsum] = 1;
				ans++;
			}
			return ;
		}
		sum[++cnt] = a[now];
		xsum ^= a[now];
		dfs(now + 1);
		cnt--;
		xsum ^= a[now];
		for(int i = 1;i <= cnt;i++){
			xsum ^= sum[i];
			sum[i] += a[now];
			xsum ^= sum[i];
			dfs(now + 1);
			xsum ^= sum[i];
			sum[i] -= a[now];
			xsum ^= sum[i];
		}
	}
	int main(){
		scanf("%lld", &n);
		for(int i = 1;i <= n;i++){
			scanf("%lld", &a[i]);
		}
		dfs(1);
		printf("%lld", ans);
		return 0;
	}
} 
signed main(){
	return Luo_ty::main();
}//International Milan is the best team.
```

---

## 作者：Ybll_ (赞：2)

# 思路：
$n$ 范围较小，考虑**爆搜**。

拿一个数组存每个袋子内有多少石头，一个变量存一共多少个袋，最后搜完直接遍历这个数组，全部异或一遍，然后把答案存下来。

这里搜的时候每次有两个选择：

1. 把这袋石子加入到另一袋；
2. 让这袋石子单独一袋。

用 `set` 存答案过不了，`TLE` 了三个点，改成 `unordered_set` 就行了。
# 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[13],b[13];
unordered_set<int>s;
void dfs(int x/*处理到第几袋石头了*/,int m/*多少袋*/)
{
    if(x==n)
    {
        int sum=0;
        for(int i=0;i<=m;i++)//异或和 
        {
        	sum^=b[i];
		}
        s.insert(sum);
        return;
    }
    for(int i=0;i<=m;i++)
    {
        b[i]+=a[x];//倒石头 
        if(i<m)dfs(x+1,m);//加到另一袋
        else dfs(x+1,m+1);//自己一袋，不加到其他袋子 
        b[i]-=a[x];//还原 
    }
}
signed main()
{
    cin>>n;
    for(int i=0;i<n;i++)
    {
    	cin>>a[i];
	}
    dfs(0,0);
    cout<<s.size();//答案 
    return 0;
}
```

---

## 作者：Ivan422 (赞：2)

代码：我们发现，可以整一个动态的数组，我们可以选择在已有的 $c$ 个位置增加，或者可以新开一个空间。这样就可以动态求任意合并的结果。

但是我们超时了。

考虑将记录答案的 `map` 改成 `unordered_map`，再将存在性查询换成 `count`，才能过。

这里放下的我观测记录。

我们通过改进，将递归次数压缩到了可接受范围内。

经过测试，复杂度是一个类似杨辉三角的递推式。复杂度可以接受，但是我证明炸了，这几天过年有时间我证明一下，放讨论区。

|$p=1$|$p=2$|$p=3$|$p=4$|$p=5$|$p=6$|$p=7$|$p=8$|$p=9$|$p=10$|$p=11$|$p=12$|$p=13$|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|$1$|$1$|$2$|$5$|$15$|$52$|$203$|$877$|$4140$|$21147$|$115975$|$678570$|$4213597$|

这显然是不会超时的。

证明到时候写。

我们设 $f_{i,j}$ 为访问 $i$ 层开了 $j$ 个空间的访问次数。

上表即 $g_p=\sum_{j=1}^i f_{p,j}$。

易得 $f_{i,j}=f_{i-1,j-1}+f_{i-1,j}\times j$。

发现这就是开空间加上使用原先 $j$ 空间的转移方法。

复杂度约为 $\mathcal O(2^n)$。

代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define umap unordered_map
const int N=1e3+10;
int n,xo,a[N],b[N],re;
umap<int,int>ans;
void dfs(int p,int c){
	if(p>n){
		xo=0;
		for(int i=1;i<=c;i++)xo^=b[i];
		if(ans.count(xo)==0){
			ans[xo]=1;
			re++;
		}
		return;
	}
	for(int i=1;i<=c;i++){
		b[i]+=a[p];
		dfs(p+1,c);
		b[i]-=a[p];
	}
	b[c+1]=a[p];
	dfs(p+1,c+1);
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	dfs(1,0);
	cout<<re;
	return 0;
}
```

---

## 作者：lzyqwq (赞：2)

对于操作结束后所有有石子的包，她内部的石子一定是由若干个原先的包中的石子组成的。因此原题等价于将序列划分成若干个不交的子集，求所有划分方案中本质不同的子集和异或和个数。

考虑爆搜。记录当前划分的子集个数，考虑当前元素划分到之前的子集还是新开一个子集。记第 $i$ 个元素划分到的子集为 $a_i$，那么搜完之后每个位置给 $a_i$ 的子集和贡献 $A_i$。最后把所有子集和异或起来得到这一种划分方案的异或和。接下来需要去重。把所有异或和扔到数组里排序然后 `unique` 即可。

精细实现之后爆搜部分时间复杂度为划分方案数。考虑计算这个东西。

设 $f_{i,j}$ 表示前 $i$ 个元素划分成 $j$ 个子集的方案，有 $f_{i,j}=f_{i-1,j}\times j+f_{i-1,j-1}$。$N$ 个元素的划分方案数即为 $\sum\limits_{i=1}^Nf_{N,i}$。打完这个 dp 之后得到当 $N=12$ 时方案数 $S=4213597$。

因此爆搜可以接受。

时间复杂度为 $\mathcal{O}(S\log S)$。$\log S$ 来自排序。空间复杂度为 $\mathcal{O}(S)$。


```cpp
#include <bits/stdc++.h>
#define int long long
template<class T> void read(T &x) {
    x = 0; T f = 1; char c = getchar();
    for (; c < 48 || c > 57; c = getchar()) if (c == 45) f = -1;
    for (; c >= 48 && c <= 57; c = getchar()) x = (x << 3) + (x << 1) + c - 48;
    x *= f;
}
template<class T> void write(T x) {
    if (x > 9) write(x / 10); putchar(x % 10 + 48);
}
template<class T> void print(T x, char ed = '\n') {
    if (x < 0) putchar('-'), x = -x; write(x), putchar(ed);
}
using namespace std; const int N = 15;
int n, c[5000000], cnt, a[N], tmp[N], b[N];
void dfs(int d, int s) {
    if (d > n) {
        memset(tmp, 0, sizeof tmp);
        for (int i = 1; i <= n; ++i) tmp[a[i]] += b[i];
        int k = 0;
        for (int i = 1; i <= s; ++i) k ^= tmp[i];
        c[++cnt] = k; return;
    }
    for (int i = 1; i <= s; ++i) a[d] = i, dfs(d + 1, s);
    a[d] = s + 1; dfs(d + 1, s + 1);
}
signed main() {
    /*n = 12;
    f[0][0] = 1;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= i; ++j)
            f[i][j] = f[i - 1][j] * j + f[i - 1][j - 1];
    int ans = 0;
    for (int i = 1; i <= n; ++i)
        ans += f[n][i];
    print(ans);*/
    read(n);
    for (int i = 1; i <= n; ++i) read(b[i]);
    dfs(1, 0);
    stable_sort(c + 1, c + cnt + 1);
    cnt = unique(c + 1, c + cnt + 1) - c - 1;
    print(cnt);
    return 0;
}
```

---

## 作者：canwen (赞：2)

[通过记录](https://atcoder.jp/contests/abc390/submissions/62139110)。

## Solution

考虑搜索剪枝，但是鉴于赛时忽略了异或的性质写出了一些奇怪东西而且拼尽全力无法通过。

可以看做把 $n$ 个数随意分进长度为 $n$ 的数列 $res$，最后计算 $res$ 中所有元素之间的异或值。

异或的性质：

$$x \operatorname{xor} x = 0$$

所以我们可以边搜边记录答案。

如何剪枝？

显然对于 $res_i = res_j(i \ne j)$ 我同样丢进一个数后结果会是重复的，考虑剪掉这部分情况，我们可以只搜 $res_i$ 这部分并保证顺序枚举使得 $j>i$，当 $res_i = res_j$ 的时候直接 `continue`，**从而保证后面也不出现重复的情况**。想想为什么？

最好用 `unordered_map` 和 `.count()`，怕卡普通 `map`。
## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define _rep(i,a,b) for(int i=(a);i<=(b);++i)
#define _reps(i,a,b,c) for(int i=(a);i<=(b);c)
#define _rrep(i,a,b) for(int i=(a);i>=(b);--i)
#define _rreps(i,a,b,c) for(int i=(a);i>=(b);c)
#define _graph(i) for(int i=head[u];i;i=e[i].nxt)
#define FRR(file) freopen(file,"r",stdin)
#define FRW(file) freopen(file,"w",stdout)
#define pb push_back
#define mk make_pair
#define fst first
#define snd second
#define pc putchar('\n')
int in(){
	int k=0,kk=1;char a=getchar();
	while(!isdigit(a)){
		if(a=='-') kk=-1;
		a=getchar();
	}
	while(isdigit(a))
		k=(k<<3)+(k<<1)+a-'0',a=getchar();
	return k*kk;
}
void put(int a){
	if(a<0) putchar('-'),a=-a;
	if(a>9) put(a/10);
	putchar('0'+a%10);
}

int n,a[13],s[13], cnt;
unordered_map <int,int> m;
void dfs(int id,int x){
	if(id == n+1){
		if(m.count(x) == 0){
			++cnt, ++m[x];
		}
		return;
	}
	_rep(i,1,n){
		if(i!=1&&s[i]==s[i-1]){
			continue;
		}
		x ^= s[i];
		int l = s[i];
		s[i] = s[i] + a[id];
		dfs(id+1,x ^ s[i]);
		s[i] = l;
		x ^= l;
	}
}
signed main(){
	n=in();
	_rep(i,1,n) a[i]=in();
	dfs(1,0);
	put(cnt);
	pc;
	return 0;
}
```

---

## 作者：xyx404 (赞：1)

## 题意：
给定 $N$ 个袋子，每个袋子里有若干石子。每次操作可以选择两个袋子，将其中一个的所有石子倒入另一个。求所有操作结束后，各袋子石子数的异或和有多少种不同的可能值。

## 思路：
观察发现最终异或和的值仅与分组方式有关。每次合并操作相当于将两个袋子的石子合并为一个新的袋子，最终的分组可以看作将初始的 $N$ 个袋子划分成若干非空子集，每个子集的石子总和构成最终的异或和。

可以通过动态规划逐步生成所有可能的分组方式。

处理每个石子堆时，对当前所有可能的状态进行扩展：
1. 新增分组，将当前石子堆作为独立分组。
2. 合并到已有分组，将当前石子堆合并到任意一个已有分组中。

最后进行去重统计。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define itn int
#define ull unsigned long long
int n;
vector<LL>A(20);
vector<pair<vector<LL>,LL> >cur;
unordered_set<LL>ans;
int main(){
	cin>>n;
	for(int i=0;i<n;i++)cin>>A[i];
	cur.emplace_back(vector<LL>{A[0]},A[0]);
	for(int i=1;i<n;i++){
		vector<pair<vector<LL>,LL> >tamp;
		for(auto g:cur){
			vector<LL>zhu=g.first;
			LL v=g.second;
			// 新增分组
			vector<LL>newg=zhu;
			newg.emplace_back(A[i]);
			LL nv=v^A[i];
			tamp.emplace_back(newg,nv);
			// 合并到已有分组
			for(int j=0;j<zhu.size();j++){
				vector<LL>temp(zhu);
				temp[j]+=A[i];
				LL val=v^zhu[j]^temp[j];
				tamp.emplace_back(temp,val);
			}
		}
		cur=tamp;
	} 
	for(auto g:cur){
		LL v=g.second;
		ans.insert(v);
	}
	cout<<ans.size();
	return 0;
}


```
[AC 记录](https://atcoder.jp/contests/abc390/submissions/62352793)。

---

## 作者：xzy_AK_IOI (赞：1)

### 思路分析
提供一种状压 dp 的写法。

首先发现 $N \le 12$，可以状压，将每个袋子中石子的状态压入一个集合中，其中若第 $i$ 位状态为 0，则表示该袋子中石子已被倒入其他袋子中，反之则没有。

设 $dp_s$ 为石子的集合 $s$ 的状态可以得到的所有异或值，这里 dp 数组用 unordered_map 存储。

则可以写出状态转移方程：

$$dp_{s-j}.insert(dp_s \oplus sum_j)(j \isin s)$$


方程意为：集合 $s-j$ 中的石子未倒入其他袋子中的状态可以由集合 $s$ 的石子的状态 $\oplus$ 集合 $j$ 的石子数量和得到。

例如样例 3：

```
71 74 45 34 31 60
```



`001100`可由`001111` $\oplus$ `000011`得到。

[代码](https://atcoder.jp/contests/abc390/submissions/62154516)

可以发现这种写法会 TLE 五个点，所以要考虑优化。

具体优化是，在枚举集合 $s$ 的子集时，我们可以指定集合 $s$ 的第一位石子数不为 0 的袋子必须被倒掉，以此来减少转移的时间。

比如在枚举集合`111100`的子集时，我们会枚举到`101000`这个子集，但其实这个子集也可以被集合`111000`所转移到，且这两种转移是一样的。

### 完整代码


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define F(i,k,n) for (int i=k;i<=n;i++)
#define db long double
const int N=13;
int sum[1<<N];
unordered_set<int>dp[1<<N];
int a[N];
int n;
unordered_set<int>::iterator it;
signed main(){
	cin>>n;
	F(i,0,n-1) cin>>a[i];
	F(s,0,(1<<n)-1) F(i,0,n-1) if ((s>>i)&1) sum[s]+=a[i];//预处理sum
	dp[(1<<n)-1].insert(0);
	for (int s=(1<<n)-1;s;s--){
		int gh=s&(-s);//取出集合s中第一位为1的位置
		for (int j=s;j;j=(j-1)&s){
			if ((j|gh)!=j) continue;//优化，判断子集j是否包含gh
			for (it=dp[s].begin();it!=dp[s].end();it++){
				dp[s-j].insert((*it)^sum[j]);
			}
		}
	}
	cout<<dp[0].size();
	return 0;
}
```

---

## 作者：Swirl (赞：1)

dfs + 剪枝。

---

首先，暴力搜索 $a$ 中哪两个数相加显然不够优秀，会 T 飞，我们考虑换一种搜索方式。

对于每一个数 $a_i$，找到一个 $b_j$，将 $a_i$ 加到 $b_j$ 上，最后统计 $b$ 的异或和也可以达到与题目相符的同样的结果（$b$ 数组可以看作我们新定义的初始为空的数组）。

但是他仍然 T 飞了。

冷静分析，发现每一次搜索没必要搜 $n$ 个位置，只需要搜到 $b$ 中第一个为 $0$ 的位置即可，这样也可以做到不重不漏。

不过同样的优化我们也需要放在统计 $b$ 的异或和的循环里。

~~卡卡常~~就能过了。

```
#include <bits/stdc++.h>
#define int long long
#define pii pair<int, int>
#define FRE(x) freopen(x ".in", "r", stdin), freopen(x ".out", "w", stdout)
#define ALL(x) x.begin(), x.end()
using namespace std;

int _test_ = 1;

const int N = 14;

int n, a[N], b[N], ans;
unordered_map<int, int> mp; // 补药用 map，会 T

void dfs(int u) {
	if (u == n + 1) {
		int g = 0;
		for (int i = 1; i <= n; i++) {
  			if (b[i] == 0) break; // 如果当前位置为 0 直接跳出循环
			g ^= b[i];
		}
		if (mp[g] == 0) // 又多了一个答案
			ans++, mp[g] = 1;
	}
	bool zero = false;
	for (int i = 1; i <= n; i++) {
		zero = b[i] == 0;
		b[i] += a[u];
		dfs(u + 1);
		b[i] -= a[u];
		if (zero) break; // 如果当前位置为 0 直接跳出循环
	}
}

void init() {}

void clear() {}

void solve() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	dfs(1);
	cout << ans;
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
//	cin >> _test_;
	init();
	while (_test_--) {
		clear();
		solve();
	}
	return 0;
}
```

---

## 作者：sto__Liyhzh__orz (赞：1)

[传送门](https://www.luogu.com.cn/problem/AT_abc390_d)

~~一道怎么都不可能评绿的大水题。~~

根据题目范围可知，此题为搜索题。

题目说可以无限次移动石头堆，所以相当于有 $n$ 个坑（方便区别），将每一堆随便放在一个坑里就可以了。

证明很简单，举个例子：你有一个坑，里面放了三堆石头，就相当于把其中两堆加入了另一堆中。

记得开 `long long`。

小小优化：

1. 在查询异或值是否重复时，可使用 `unordered_map`。

2. 再对于每个堆放入那个坑时，如果这个坑还没有石头，就不要再往后面的坑放了，因为情况一致。

3. （非必要）`O3` 优化。

```cpp
#pragma GCC optimize(3,"Ofast","inline")
#include<bits/stdc++.h>
#include<unordered_map>
#define endl '\n'
#define lowbit(x) ((x)&-(x))
#define pii_small priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>
#define ll_small priority_queue<long long,vector<long long>,greater<long long>>
using namespace std;

typedef long long ll;
typedef double db;
typedef __int128 III;
const db eqs=1e-6;
const int inf=1e9;
void ll_cmax(ll &a,ll b){a=a>b?a:b;}
void ll_cmin(ll &a,ll b){a=a<b?a:b;}
void int_cmax(int &a,int b){a=a>b?a:b;}
void int_cmin(int &a,int b){a=a<b?a:b;}
bool db_eq(db a,db b){return fabs(a-b)<eqs;}
bool minuscule(char ch){return ch>='a' && ch<='z';}
bool number(char ch){return ch>='0' && ch<='9';}

const int MAXN=15;
ll a[MAXN],n,cnt,x[MAXN];
unordered_map<ll,int>mp;

void dfs(int k)
{
	if(k>n)
	{
		ll sum=0;
		for(int i=1;i<=n;i++) 
		{
			if(x[i]==0) break;
			sum^=x[i];
		}
		if(mp.find(sum)==mp.end())
		{
			++cnt;
			mp[sum]=cnt;
		}
		return ;
	}
	for(int i=1;i<=n;i++)
	{
		x[i]+=a[k];
		dfs(k+1);
		x[i]-=a[k];
		if(x[i]==0) break; 
	}
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	dfs(1);
	cout<<cnt<<endl;
	return 0;
}

```

---

## 作者：PUTONGDEYITIREN (赞：1)

# 思路

## 题面分析

这道题给了我们 $n$ 个数，叫我们把其中的一些数加起来，求最后的异或和有多少种不同的答案，看到这里，大家应该还没有思路，但一看数据范围，就会发现，他的这个 $n$ 给的特别小，因此我们可以考虑一个阶乘级的带剪枝的搜索。

## 搜索细节

在搜索的过程中，为了去掉最后统计答案的时间复杂度，我们采取边搜索边统计答案的方式。每次都从当前数的前面找要合并起来的数，而且要找的是其它数没有找到的。考虑他给的 $a_i$ 特别大，最后去重还要用到 umap。这样勉强能卡过。

# code

```
#include<bits/stdc++.h>
using namespace std;
long long n,a[200005],,f,ans;
unordered_map<long long,long long> mp;
void dfs(long long x,long long an){
	if(x>n){
		if(mp[an]==0) ans++;
		mp[an]++;
		return;
	}
	dfs(x+1,an^a[x]);
	for(int i=1;i<x;i++){
		if(a[i]!=0){
			long long y=a[i];
			a[i]=0;a[x]+=y;
			dfs(x+1,an^a[x]^y);
			a[i]=y;a[x]-=a[i]; 			
		}
	}
	return;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	dfs(1,0);
	cout<<ans<<endl;
	return 0;
}

```

---

## 作者：jinbaohan (赞：1)

本题是一道搜索加剪枝题。

先考虑直接爆搜，搜索当前堆的石子要被移动到哪一堆。

由于向前移和向后移本质上是一样的，所以我们只要考虑向后移就可以了。

可是这样还过不了，考虑剪枝。发现如果第一堆石子先被移到第二堆，又从第二堆被移到第三堆，那和直接移到第三堆没有区别。

所以我们记录每堆石子有没有收到其他堆给的石子，如果收到了就不再移动它，这样就可以避免重复了。

用 unordered_map 给答案去重，最慢点跑了 1846 毫秒。 

具体实现见代码。 
```
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,a[15],ans,p[15];//p:有几堆石子被移动到此堆 
unordered_map <int,int> mp;
void dfs(int k){
	if(k == n + 1){
		int x = 0;
		for(int i = 1; i <= n; i++) x ^= a[i];
		if(!mp[x]){
			mp[x] = 1;
			ans++;
		}//统计答案 
		return;
	}
	dfs(k + 1);//不移动该堆石子 
	if(p[k]) return;//剪枝，如果有其他石子被移动到此堆，则此堆不能再移动 
	for(int i = k + 1; i <= n; i++){
		int f = a[k];
		a[i] += f;a[k] = 0;p[i]++;//操作 
		dfs(k + 1);
		p[i]--;a[k] = f;a[i] -= f;//回溯 
	}
}
signed main(){
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i];
	dfs(1);
	cout << ans;
	return 0;
}
```

---

## 作者：xiaoyin2011 (赞：1)

## AT_abc390_d [ABC390D] 石头异或 题解

[题目链接](https://www.luogu.com.cn/problem/AT_abc390_d)

### 题目大意

给出 $N$ 袋石头，每袋 $A_i$ 个。进行若干次合并操作后剩余的每袋石头数为 $B$，此时分数为 $B_1 \oplus B_2 \oplus \cdots \oplus B_N$，问多少种不同的分数。

### 思路

$N \le 12$，大家都能看出来阶乘级算法不会超时，$12! = 479001600 \approx 4.8 \times 10^8$。我意识到这是一个 DFS 题目，但是我的 DFS 方法是 $12^{12} \approx 9 \times 10^{12}$。

所以为什么答案不会达到 $12^{12}$ 呢？这个问题困惑了我很久。我的方法是，对于每个袋子，选择它最后去到哪个袋子。显然复杂度达到 $O(N^N)$。这个方法会选择出一些不可能实现的情况，比如 $1$ 去了 $2$、$2$ 去了 $1$，而只有这两个袋子是无法实现的。

所以为什么 $12!$ 级别的算法能实现呢？对于从 $1$ 开始决定归宿的袋子，第一个袋子进入第 $2$ 组是可能产生重复的情况，因为有可能后面没有一个进入 $1$ 组。

有一个数字叫做**贝尔数**（Bell Number），表示大小为 $N$ 的可重几何有多少种分配进入不限数量的组的方法。而 $B(12) = 4213597 < 5 \times 10^6$。

至于这道题 DFS 的实现，所有题解应该都说了。传递目前是哪一个袋子和已经有多少组，每次考虑分进以前的组或者新开一组，最后统计答案即可。

### 实现

虽然复杂度是在范围内，可是如果要得到分并不是很简单。首先需要使用 `unordered_set` 而不是 `set`，可以少一个 $\log$，这个不必多说。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll N, A[15], g[15], sum[15], ans;
unordered_set<ll> st;
void dfs(ll now, ll gcnt)
{
	if (now == N + 1)
	{
		memset(sum, 0, sizeof(sum));
		ans = 0;
		for (int i = 1; i <= N; i++)
			sum[g[i]] += A[i];
		for (int i = 1; i <= gcnt; i++)
			ans ^= sum[i];
		st.insert(ans);
		return ;
	}
	for (int i = 1; i <= gcnt; i++)
	{
		g[now] = i;
		dfs(now + 1, gcnt);
	}
	g[now] = gcnt + 1;
	dfs(now + 1, gcnt + 1);
}
int main()
{
	scanf("%lld", &N);
	for (int i = 1; i <= N; i++)
		scanf("%lld", &A[i]);
	dfs(1, 1);
	printf("%lld\n", st.size()); 
	return 0;
}
```

上面是根据思路写出来的代码，$g_i$ 表示 $i$ 袋分入哪一组，$sum_i$ 表示分配后 $i$ 组有多少石子，$ans$ 是答案。但是这个代码提交上去你会荣获 TLE，因为 $12!$ 已经接近 $5 \times 10^8$，如果我们达到 $O(N \times N!)$，就会 TLE。

因此我们考虑在修改 $g_i$ 的同时更新 $sum_i$ 和 $ans$。$sum_i$ 很显然可以通过加减进行更新和回溯，$ans$ 则可以通过异或的性质——连续两次异或一个数字则会消去它，先异或原 $sum_i$，再异或新 $sum_i$ 即可。这样，DFS 结尾我们只需要把 $ans$ 扔进 `unordered_set` 里。

### AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll N, A[15], sum[15], ans;
unordered_set<ll> st;
void dfs(ll now, ll gcnt)
{
	if (now == N + 1)
	{
		st.insert(ans);
		return ;
	}
	for (int i = 1; i <= gcnt; i++)
	{
		ans ^= sum[i];
		sum[i] += A[now];
		ans ^= sum[i];
		dfs(now + 1, gcnt);
		ans ^= sum[i];
		sum[i] -= A[now];
		ans ^= sum[i];
	}
	sum[gcnt + 1] = A[now];
	ans ^= sum[gcnt + 1];
	dfs(now + 1, gcnt + 1);
	ans ^= sum[gcnt + 1];
	sum[gcnt + 1] = 0;
}
int main()
{
	scanf("%lld", &N);
	for (int i = 1; i <= N; i++)
		scanf("%lld", &A[i]);
	dfs(1, 1);
	printf("%lld\n", st.size()); 
	return 0;
}
```

---

## 作者：gavinliu266 (赞：1)

# 思路
我们发现数的顺序不影响最后结果，于是可以考虑深搜，在每一层枚举子集，将原数组划分成多个集合。

注意为了尽量减小时间复杂度，我们应该保证枚举的子集必须包含原集合中 $a$ 中下标最大的那一个。

对于每个集合，将该集合内所有数加到该集合中任意一个数上，则集合 $G=\{a_{p_1},a_{p_2},\cdots,a_{p_m}\}$ 对答案贡献（使答案异或上的数）为 $\left(\bigoplus \limits _{i=1}^m a_{p_i} \right)  \oplus \sum \limits _{i=1} ^m a_{p_i}$。

因为所有答案都会异或上 $\bigoplus \limits _{i=1}^n a_i$，所以统计数量时可以不异或这个值。

最后，用 `set` 判重会 TLE 掉，将 `set` 改为 `unordered_set` 可获得大多数情况下更快的判重算法，可 AC。

# 代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
unordered_set<ll> st;
ll a[15], id[15];
int n;
ll ans;
void dfs(int h, ll k) {
    st.insert(ans);
    if(h == n + 1 || !k)
        return;
    ll tk = 1 << __lg(k);  // 下标最大的
    dfs(h + 1, k ^ tk);
    for(ll i = k; i; i = (i - 1) & k) {  // 枚举子集
        if(i < tk) break;
        // 防止出现 {1,2} {3,4} 与 {3,4} {1,2} 两种等价的情况搜索多次
        ll t = i;
        ll tans1 = 0, tans2 = 0;
        while(t) {
            ll lb = t & -t;
            ll rk = __lg(lb) + 1;  // 在原数组中的下标
            tans1 += a[rk], tans2 ^= a[rk];
            t -= lb;
        }
        ans ^= tans1 ^ tans2;
        dfs(h + 1, k ^ i);
        ans ^= tans1 ^ tans2;
    }
}
int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) 
        scanf("%lld", &a[i]);
    dfs(1, (1ll << n) - 1);
    printf("%llu\n", st.size());
}
```

---

## 作者：YBJ1006 (赞：1)

暴搜即可，记得用 unordered_set 。

对于这袋子，考虑分组。可以将这个袋子放入之前的任意一组，或者新开一组。


```cpp
#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
#include <unordered_set>
using namespace std;
typedef long long ll;
const int N = 1e2 + 10;
ll n,a[N],b[N];
unordered_set<ll>st;
void dfs(int dep, int k)//深度 有几组
{
    if (dep == n + 1)
    {
        ll s = 0;
        for (int i = 1; i <= k; i++)
        {
            s ^= b[i];
        }
        st.insert(s);
        return;
    }
    for (int i = 1; i <= k + 1; i++)
    {
        //放到i组
        b[i] += a[dep];
        if (i == k + 1)
            dfs(dep + 1, k + 1);
        else
            dfs(dep + 1, k);
        b[i] -= a[dep];//回溯
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    dfs(1, 0);
    cout << st.size();
    return 0;
}
```

---

## 作者：hjyowl (赞：1)

### 题目大意

可以选择把一个袋子里所有球放到另一个袋子，求出结束后袋子所有球的和的异或和的值的不同数量。

### 转换

首先我们知道零是不影响异或的。

所以说，问题可以转换为下面这样的。

有一堆数，把他们丢到很多个集合，求所有方案下每个集合的和的异或和的数量。

### 思路

因为 $n$ 很小，所以说我们只需要用暴力搜索即可解决这个问题。

也就是暴力枚举即可。

但是请注意不要直接用系统自带的带排序集合，要用不带排序集合。

好做完了。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const long long N = 20;
long long n;
long long a[N], s[N];
unordered_set<long long> ss;
long long tt = 0;
void dfs(long long u, long long k) {
	if (u == n) {
		ss.insert(tt);
		return;
	}
	for (long long i = 0; i < k; i++) {
		tt ^= s[i];
		s[i] += a[u];
		tt ^= s[i];
		dfs(u + 1, k);
		tt ^= s[i];
		s[i] -= a[u];
		tt ^= s[i];
	}
	tt ^= s[k];
	s[k] = a[u];
	tt ^= s[k];
	dfs(u + 1, k + 1);
	tt ^= s[k];
	s[k] = 0;
	tt ^= s[k];
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for (long long i = 0; i < n; i++) {
		cin >> a[i];
	}
	dfs(0, 0);
	cout << ss.size();
	return 0;
}

```

---

## 作者：xxxalq (赞：1)

[洛谷题目链接](https://www.luogu.com.cn/problem/AT_abc390_d) & [Atcoder 题目链接](https://atcoder.jp/contests/abc390/tasks/abc390_d)


# 题意简述

有 $n$ 个数，你可以把它们任意分组，求每组数之和的异或和有多少种。

# 思路

看到 $n\le 12$ 时间是比较宽裕的。

可以先枚举分的组数然后直接爆搜看每个数在哪一组。

有一个可行性剪枝是如果当前剩的所有数都单独组成一组还是达不到要求的组数就停止搜索。这样保证每个状态只被搜索到一次。

像这种状态的级别是贝尔数，$12$ 的贝尔数是 $4213597$。所以搜索完我们需要保证统计答案需要在 $O(1)$ 时间内完成。其实就是用线性的时间对一些数进行去重。

比赛时我写的是数字哈希，找到一个比较大的质数 $10^7+19$ 记为 $p$，然后根据每个数模 $p$ 的值进行分类，由于数值较大且较为随机所以总体期望可以做到线性的时间复杂度。

# 代码：


```cpp
//code by xxxalq
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int mod=10000019;

int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch>57||ch<48){
		if(ch==45){
			f=-1;
		}
		ch=getchar();
	}
	while(ch>=48&&ch<=57){
		x=(x<<1)+(x<<3)+(ch-48);
		ch=getchar();
	}
	return x*f;
}

int T,n,a[20],target;

bool mk[20];

int tmp[20],tot;

vector<int>ans[10000020];

void insert(int x){//数字哈希
	int p=x%mod;
	for(int u:ans[p]){
		if(u==x){
			return;
		}
	}
	ans[p].push_back(x);
	tot++;
	return;
}

void dfs(int x,int cnt){
	if(x>n){
		int res=0;
		for(int i=1;i<=target;i++){
			res^=tmp[i];
		}
		insert(res);
		return;
	}
	if(cnt<target){
		tmp[cnt+1]+=a[x];
		dfs(x+1,cnt+1);
		tmp[cnt+1]-=a[x];		
	}
	if(target-cnt<n-x+1){//剪枝优化
		for(int i=1;i<=cnt;i++){
			tmp[i]+=a[x];
			dfs(x+1,cnt);
			tmp[i]-=a[x];
		}
	}
	return;
}

void solve(){
	for(int i=1;i<=n;i++){//枚举组数
		target=i;
		dfs(1,0);
	}
	return;
}

signed main(){
	T=1;
	while(T--){
		n=read();
		for(int i=1;i<=n;i++){
			a[i]=read();
		}
		solve();
		cout<<tot<<'\n';
	}
	return 0;
}
```

---

## 作者：player_1_Z (赞：0)

###  先来理解题目

[atcoder 原题](https://atcoder.jp/contests/abc390/tasks/abc390_d)

###  思路

首先，$N \le 12$，所以可以用暴力，那么果断拿出 [set](https://blog.csdn.net/qq_50285142/article/details/122304728)（不用排序去重），然后写一个 `dfs` 函数暴力搜索（具体看注释）。注意：要用
`unordered_set`。
### 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
long long n,m,a[15],b[15];
unordered_set<ll> s;
void dfs(ll x,ll y){
    if(x==n+1){//n 袋石子操作完毕 
        ll sum=0;
        for(ll i=1;i<=y;i++) sum^=b[i];//计算当前石子异或后的值 
        s.insert(sum);//存进 set 
        return;
    }
    for(ll i=1;i<=y;i++){
        b[i]+=a[x];//把 x 袋子里的石子倒进目前的 i 袋子里 
        if(i<y) dfs(x+1,y);
        else dfs(x+1,y+1);//不倒进其它袋子里 
        b[i]-=a[x];//回溯 
    }
}
int main(){
    cin>>n;
    for(ll i=1;i<=n;i++) cin>>a[i];
    dfs(1,1);
    cout<<s.size();//set 会去重，直接输出 
    return 0;
}
```

---

## 作者：__Ship_ (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/AT_abc390_d)

## 思路

观察 $n$ 我们能发现 $n ≤ 12$。

考虑搜索，怎么搜呢。

我们将倒石子的问题抽象成两个袋子里的石子合并成一个袋子，由于我们每个合并后的袋子不能再使用了，所以我们还需要一个变量表示我处理了第几袋，在枚举我当前石子要加到我已合并的哪个袋子，或者新增加一个袋子来合并。

最后枚举完后将整个数组异或一遍，答案放入 ```unordered_set``` 来去重就好了，放入 ```set``` 会超时。
 

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,ans=1,a[13],b[13];
unordered_set<int> s;
void dfs(int now,int m){//now表示处理了几个袋子，m代表合并了几个袋子 
	if(now>n){
		int sums=b[1];
		for(int i = 2 ; i <= m ; i++){
			sums^=b[i];
		}
		s.insert(sums);
		return;
	}
	for(int i = 1 ; i <= m ; i++){
		b[i]+=a[now];
		if(i<m){
			dfs(now+1,m); 
		}
		else{
			dfs(now+1,m+1); 
		}
		b[i]-=a[now];
	}
}
signed main(){
	cin>>n;
	for(int i = 1 ; i <= n ; i++){
		cin>>a[i];
	}
	dfs(1,1);
	cout<<s.size();
	return 0;
}

```

---

## 作者：LiamZou (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc390_d)

题目大意：有 n 个石子的集合，合并集合后求合并后每个集合石字数相异或值的所有可能数量。

题目题解：先看数据范围，$2\leq N\leq 12$，说明这是一道暴力搜索提。

问题来了：怎么搜呢，对于每个石子的集合，我们可以枚举每个其他的集合，把那个集合合并到这个集合里，或者是一点都不变。

配合代码理解一下吧：


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long//记住，一定要开 long long (警钟敲爆)  
int n, a[1000005], temp;
unordered_set<int> st;//对答案进行统计和去重(注意：如果这个 set 不是 unordered ，也就是不排序的，就会 TLE ！)
void dfs(int id, vector<int> cur, int used)//id表示搜索到了编号为id的集合， cur 表示当前的集合状态 
{
	if (id == n)//如果遍历完了，就统计答案 
	{
        temp = 0;
        for (int i = 0; i < cur.size(); i++)
        {
        	temp ^= cur[i];
		}
        st.insert(temp);//记录答案 
        return;
    }
    for (int i = 0; i < used; i++)//枚举可合并的其他集合 
	{
        int lst = cur[i];
        cur[i] += a[id];//改变状态 
        dfs(id + 1, cur, used);
        cur[i] = lst;//回溯 
    }
    if (used < n)
	{
        cur[used] = a[id];
        dfs(id + 1, cur, used + 1);
        cur[used] = 0;
    }
}
signed main()
{
    cin >> n;
    for (int i = 0; i < n; i++)//输入 
	{
        cin >> a[i];
    }
    vector<int> cur(n);
    dfs(0, cur, 0);
    cout << st.size() << endl;//输出就是去重后的答案了 
    return 0;//华丽结束awa
}
```

---

## 作者：Beihai_Jiang (赞：0)

# [ABC390D] Stone XOR

[[ABC390D] Stone XOR - 洛谷 | 计算机科学教育新生态](https://www.luogu.com.cn/problem/AT_abc390_d)

## 问题陈述

有 $N$ 个袋子，分别标有袋子 $1$、袋子 $2$、$\ldots$、袋子 $n$。  
袋子 $i$。（$1 \leq i \leq N$）装有 $A_i$ 颗宝石。

高桥可以进行以下任意次数的运算，可能为零：

> 选择两个袋子 $A$ 和 $B$，将 $A$ 袋中的所有棋子移入 $B$ 袋。

在重复操作后，求以下不同可能值的个数。

- $B_1 \oplus B_2 \oplus \cdots \oplus B_N$，其中 $B_i$ 是袋子 $i$ 中石头的最终数量。  
    这里，$\oplus$ 表示位向 $XOR$。
  
可以证明，在这个问题的约束条件下，可能的值是有限的。

## 100pts

**搜索+剪枝**

观察数据范围 $2\le N \le 12$，容易想到暴搜。

高桥进行若干次操作后会剩下若干个袋子，因此我们可以枚举每个袋子在操作后是哪个袋子。

具体地，对于一个袋子 $i$，枚举它在操作后的编号为 $j$，相同的 $j$ 合并为同一袋，$j\in[1,N]$。

比如，我们有 $5$ 个袋子，分别为袋子 $1$、袋子 $2$、袋子 $3$、袋子 $4$、袋子 $5$，它们操作后的编号 $j$ 分别为 $1,1,2,3,3$，

则袋子 $1$、袋子 $2$ 合并为一袋，袋子 $3$ 自为一袋，袋子 $4$、袋子 $5$ 合并为一袋。

时间复杂度 $O(n^nn)$，在本题的数据范围显然过不了。

考虑剪枝。

容易发现在上述做法中，我们枚举很多重复情况，如 $1,1,2,3,3$ 和 $2,2,3,4,4$ 其实是同一种情况。

因此，我们可以限制对于袋子 $i$，其操作后的编号 $j$ 的取值范围为 $[1,i]$。

此时的时间复杂度为 $O(n!n)$。

进一步地，我们发现 $1,1,2,3,3$ 和 $1,1,3,4,4$ 是同一种情况。

于是，对于袋子 $i$，我们用变量 $maxx$ 记录袋子 $1$ 到 $i-1$ 的 $j$ 的最大值，则袋子 $i$ 的 $j$ 的取值范围为 $[1,maxx+1]$。

至此，我们成功完成本题！

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=15,MAXN=2.6e7;
int n;
int a[N],b[N];
int opt[N];
int ans[MAXN],cnt;
void dfs(int dep,int maxx){
	if(dep==n){
		memset(b,0,sizeof(b));
		for(int i=1;i<=n;i++){
			b[opt[i]]+=a[i];
		}
		int res=0;
		for(int i=1;i<=n;i++){
			res^=b[i];
		}
		ans[++cnt]=res;
		return;
	}
	for(int i=1;i<=maxx+1;i++){
		opt[dep+1]=i;
		dfs(dep+1,max(i,maxx));
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	opt[1]=1;
	dfs(1,1);
	sort(ans+1,ans+cnt+1);
	cnt=unique(ans+1,ans+cnt+1)-ans-1;
	cout<<cnt;
	return 0;
}
```

完结撒花，感谢陪伴*★,°*:.☆(￣▽￣)/$:*.°★*

---

## 作者：JXR_Kalcium (赞：0)

~~为什么感觉 E 比 D 难（反正我 E 题赛时没调出来）~~。

## 题目大意

给定一个长度为 $N$ 的序列 $A_i$，可以进行任意次以下操作：选定一个 $j$，然后 $B_j\leftarrow B_j+A_i,B_i\leftarrow B_i-A_i$，问最后的 $B_1\oplus B_2\oplus\cdots\oplus B_N$ 有多少种不同的值，数据范围 $N\le 12$。

## 解题思路

看到 $N$ 这么小，不难想到用搜索实现，于是就能写出一个朴素的搜索：DFS 到第 $x$ 个点，然后枚举 $i\in [1,N]$ 表示将 $A_x$ 移到 $B_i$，当 $x>N$ 的时候计算异或的值，用 `unordered_map` 统计答案即可。这样的时间复杂度为 $O(N\times N^N)$，实际因为常数问题，在 $3\text{s}$ 的时限下只能通过 $N\le 8$ 的点。

考虑剪枝（官方题解用 `set`，我不会 QWQ），首先枚举范围可以调成 $i\in [1,x]$，因为前面移到后面和后面移到前面是一样的，这样时间复杂度就降为 $O(N\times N!)$，可以通过 $N\le 11$ 的点。考虑继续优化，发现当 $B_j=0$ 时把 $A_i$ 移到 $B_j$ 的操作无意义（只是换了个位置），所以转移时可以特判一下，这样就能用 $1.5\text{s}$ 完美通过本题。时间复杂度为 $O(NB(N))$，其中 $B(N)$ 表示 $N$ 的贝尔数，最大为 $4213597$，虽然常数较大，但足以通过本题。

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

ll n,a[21],p[21],res,ans;
unordered_map<ll,ll> bz;

void dfs(ll x)
{
    if(x>n)
    {
        res=0;
        for(R int i=1; i<=n; ++i) res^=p[i];
        if(!bz[res]) bz[res]=1, ++ans; return;
    }

    for(R int i=1; i<=x; ++i)
    {
        if(!p[i]) continue;
        p[i]+=a[x]; p[x]-=a[x]; dfs(x+1);
        p[i]-=a[x]; p[x]+=a[x];
    }
}

int main()
{
    n=read();
    for(R int i=1; i<=n; ++i)
    a[i]=read(), p[i]=a[i];
    dfs(1); write(ans);
    return 0;
}
```

---

## 作者：OI_StarGod (赞：0)

# 题意简述

给定 $n$ 袋石头，放进任意个盒子里，求最终这些盒子的异或和为多少。

# 解法

看到 $2 < N \le 12$ 就应该知道这题是深搜了。

那么具体怎么搜？

首先我们很容易证明一点，对于 $a_i = 0$ 的情况，$a_i$ 不会对结果造成任何贡献。这随便举个栗子就能证明，所以不加证明了。

然后 $a_i$ 我们把它放到第 $i$ 个盒子里和放进第 $i + 1$ 个盒子里其实本质上是相同的。所以这里我们可以做出一个优化，就是对于 $a_i$，我们只需要搜索把 $a_i$ 放到前 $i$ 个盒子里面就可以了。

但是这样时间复杂度还是太高，因为计算结果还需要一部分时间，所以我们干脆边搜边计算结果。

# AC code


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long //个人习惯开long long
const int N = 15; // 数组略微开大一点点
int n;
int a[N];
int now[N];
int val = 0;
unordered_set<int> ans; //用set存算出来的所有结果，因为set具有去重特性，所以最终直接输出set的大小即可
void dfs(int x) { //深搜
	if (x > n) { //如果每个袋子都搜完了
		ans.insert(val); //存结果
		return; //结束
	}
	for (int i = 1; i <= n; ++i) { //考虑放到哪个袋子里面
		if (now[i] == 0 && now[i - 1] == 0) { //浅浅剪枝一下
			break;
		}
		val ^= now[i];
		now[i] += a[x];
		val ^= now[i]; //计算把a_x放到第i个盒子的异或和
		dfs(x + 1);
		val ^= now[i]; //回溯
		now[i] -= a[x];
		val ^= now[i];
	}
}
signed main() {
	cin >> n; //平平无奇的输入
	now[0] = 1; //防止剪枝的时候再x=1时就减掉
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}
	dfs(1);
	cout << (int)(ans.size());//输出set的大小
	return 0;
}

防抄袭行 //敢不看直接就复制代码必定CE
```

---

## 作者：Yuexingfei_qwq (赞：0)

赛时差一点就过了。
## 思路  
看到 $2 \le n \le 12$ 容易想到暴力，直接枚举即可。  
[但是交上去发现 TLE 了。](https://atcoder.jp/contests/abc390/submissions/62066103)

接下来考虑如何优化。  
搜索最经典的优化就是记忆化，所以直接套个记忆化上去。  
[然后发现又 TLE 了。](https://atcoder.jp/contests/abc390/submissions/62069376)  

本想用 `unordered_map<vector<int>, int>` 来记录不同数组状态下的答案，发现[ CE 了](https://atcoder.jp/contests/abc390/submissions/62085425)。改成 `map` 显然会 TLE，所以放弃这种想法。  

发现可以在递归函数里多加一个参数，表示到目前的答案，这样既不需要多用一个函数计算数组的异或和，也能解决如何合理地写递归终止条件的问题。  

讲到这里，代码就很清晰了。
## AC CODE
```cpp
#include <bits/stdc++.h>
#define el "\n"
#define sp " "
#define fi first
#define se second
#define inf 1e18
#define r0 return 0
#define int long long
#define F(i, a, b, c) for (int i = a; i <= b; i += c)
#define debug printf ("bug is in here\n")
#define TheEnd continue
#define base(s) s = sp + s
#define lcm(a, b) a * b / __gcd(a, b)
#define setp(x) fixed << setprecision(x)

using namespace std;

typedef long long ll;
typedef string str;
using ull = unsigned ll;

int n;
int a[20];
std::bitset<20> f;
std::unordered_map<int, bool> m;

inline bool dfs(int x, int ans) {
	if (x == n + 1) {
		m[ans] = 1;
		r0;
	}
	dfs(x + 1, ans ^ a[x]);
	F(i, x + 1, n, 1) {
		if (f[i]) {
			TheEnd;
		}
		f[i] = 1;
		a[i] += a[x];
		dfs(x + 1, ans);
		a[i] -= a[x];
		f[i] = 0;
	}
	r0;
}

signed main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);
	cin >> n;
	F(i, 1, n, 1) {
		cin >> a[i];
	}
	dfs(1, 0);
	cout << m.size() << el;
	r0;
}
```

[AC 记录](https://atcoder.jp/contests/abc390/submissions/62048830)

---
完结~~不~~散花。

---

## 作者：DengStar (赞：0)

看数据范围，显然搜索。但直接按照题目给出的操作过程来搜索，代码不好实现，且时间复杂度也没有保证。我们可以把题目转化成：把集合 $\{1, 2, \cdots, N\}$ 划分成若干个不交的集合，每种划分方式对应一个权值（即每个子集的和的异或和），求不同的权值的数量。因此枚举集合的划分方式即可。

代码实现上，用 dfs 枚举划分方式，用一个数组记录每个子集当前的和：

```cpp
void dfs(int cur, int k, i64 sum) { // 枚举到第 cur 个数，划分出 k 个子集
    if(cur == n + 1) {
        s.insert(sum);
        return;
    }
    for(int i = 1; i <= k + 1; i++) {
        i64 nxt = sum ^ val[i] ^ (val[i] + a[cur]);
        val[i] += a[cur];
        if(i == k + 1) { // 划分到新的子集
            dfs(cur + 1, k + 1, nxt);
        } else { // 划分到原有的子集
            dfs(cur + 1, k, nxt);
        }
        val[i] -= a[cur];
    }
}
```

**时间复杂度分析**：

我们要做两件事，第一件事是计算集合划分的数量，第二件事是证明每种划分方式只会被访问一遍。

1. 关于集合划分的数量，数学上早有研究，大小为 $n$ 的集合的划分数量被记为[**贝尔数**](https://oi-wiki.org/math/combinatorics/bell/) $B_n$。

   贝尔数满足递推公式：
   $$
   B_{n + 1} = \sum_{i = 0}^{n} \dbinom{n}{i} B_{i}
   $$
   这个公式在 OI wiki 上有足够清晰的证明，这里不再赘述。

   本题中，当 $N = 12$ 时，$B_N$ 大约为 $4 \times 10^6$，完全可以通过。（实际上，即使不知道这个公式，也可以搜一发试试。）

2. 证明每种划分方式只会被访问一遍：

   在集合的划分中，各子集是无序的，即 $\{\{a_1, a_3\}, \{a_2\}\}$ 和 $\{\{a_2\}, \{a_1, a_3\}\}$ 是同一个划分，但是是同一划分的不同“表示方法”。我们希望每种划分只被访问一次，也就是要保证对于一个划分，它的所有表示方法中，只有一个被访问。

   上文的 dfs 代码实际上保证了：每个子集的下标最小元素的下标升序排列。（在 $\{\{a_1, a_3\}, \{a_2\}\}$ 这个例子中：第一个子集的编号最小元素为 $a_1$，第二个子集为 $a_2$，它们的下标确实升序排列。）显然，对于任意一个划分，只有一种表示方法使得子集的最小下标升序排列，因此我们证明了每个划分只会被访问一次。

   实际上这是保证 dfs 时间复杂度的常用方法：枚举无序的元素组合时，我们常常钦定一个特定的顺序，使得每个元素组合只被访问一次。例如枚举正整数的拆分时，我们通常钦定拆分出的数单调不降，这就保证了每种拆分方式只会被访问一次。

---

