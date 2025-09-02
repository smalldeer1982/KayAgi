# [ABC289C] Coverage

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc289/tasks/abc289_c

$ 1 $ 以上 $ N $ 以下の整数からなる集合が $ M $ 個あり、順に $ S_1,\ S_2,\ \dots,\ S_M $ と呼びます。  
$ S_i $ は $ C_i $ 個の整数 $ a_{i,\ 1},\ a_{i,\ 2},\ \dots,\ a_{i,\ C_i} $ からなります。

$ M $ 個の集合から $ 1 $ 個以上の集合を選ぶ方法は $ 2^M-1 $ 通りあります。  
このうち、次の条件を満たす選び方は何通りありますか？

- $ 1\ \leq\ x\ \leq\ N $ を満たす全ての整数 $ x $ に対して、選んだ集合の中に $ x $ を含む集合が少なくとも $ 1 $ 個存在する。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10 $
- $ 1\ \leq\ M\ \leq\ 10 $
- $ 1\ \leq\ C_i\ \leq\ N $
- $ 1\ \leq\ a_{i,1}\ \lt\ a_{i,2}\ \lt\ \dots\ \lt\ a_{i,C_i}\ \leq\ N $
- 入力される値は全て整数

### Sample Explanation 1

入力で与えられている集合はそれぞれ $ S_1\ =\ \lbrace\ 1,\ 2\ \rbrace,\ S_2\ =\ \lbrace\ 1,\ 3\ \rbrace,\ S_3\ =\ \lbrace\ 2\ \rbrace $ です。 問題文の条件を満たす集合の選び方は次の $ 3 $ 通りです。 - $ S_1,\ S_2 $ を選ぶ。 - $ S_1,\ S_2,\ S_3 $ を選ぶ。 - $ S_2,\ S_3 $ を選ぶ。

### Sample Explanation 2

問題文の条件を満たす選び方が存在しない場合もあります。

## 样例 #1

### 输入

```
3 3
2
1 2
2
1 3
1
2```

### 输出

```
3```

## 样例 #2

### 输入

```
4 2
2
1 2
2
1 3```

### 输出

```
0```

## 样例 #3

### 输入

```
6 6
3
2 3 6
3
2 4 6
2
3 6
3
1 5 6
3
1 3 6
2
1 4```

### 输出

```
18```

# 题解

## 作者：minVan (赞：3)

**题目大意**

有 $M$ 个集合，其中选出 $k$ 个，使这 $k$ 个集合的并集为 $\{1,2,\dots ,N\}$，求有多少种选法。

**解题思路**

直接深搜，标记每一个选还是不选，最后检查一遍，满足条件就答案加 $1$。

**数据结构**

```cpp
const int N = 15;
int n, m, s[N][N] /*s[i][0]为第 i 个集合的个数*/, ans;
bool vis[N], mp[N]; // vis 为标记每一个选还是不选，1 为选，0 为不选
```

**深搜部分代码**

```cpp
inline void dfs(int x) {
    if(x > m) {
        if(check()) {
            ans++;
        }
        return ;
    }
    vis[x] = 1;
    dfs(x + 1);
    vis[x] = 0;
    dfs(x + 1);
    return ;
}
```

**检查部分代码**

```cpp
inline bool check() {
    memset(mp, 0, sizeof(mp));
    for(int i = 1; i <= m; i++) {
        if(vis[i]) {
            for(int j = 1; j <= s[i][0]; j++) {
                mp[s[i][j]] = 1;
            }
        }
    }
    for(int i = 1; i <= n; i++) {
        if(!mp[i]) {
            return 0;
        }
    }
    return 1;
}
```

**完整代码**

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 15;
int n, m, s[N][N], ans;
bool vis[N], mp[N];
inline bool check() {
    memset(mp, 0, sizeof(mp));
    for(int i = 1; i <= m; i++) {
        if(vis[i]) {
            for(int j = 1; j <= s[i][0]; j++) {
                mp[s[i][j]] = 1;
            }
        }
    }
    for(int i = 1; i <= n; i++) {
        if(!mp[i]) {
            return 0;
        }
    }
    return 1;
}
inline void dfs(int x) {
    if(x > m) {
        if(check()) {
            ans++;
        }
        return ;
    }
    vis[x] = 1;
    dfs(x + 1);
    vis[x] = 0;
    dfs(x + 1);
    return ;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for(int i = 1; i <= m; i++) {
        cin >> s[i][0];
        for(int j = 1; j <= s[i][0]; j++) {
            cin >> s[i][j];
        }
    }
    dfs(1);
    cout << ans;
    return 0;
}

```

---

## 作者：OIerBoy (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/AT_abc289_c)
## 翻译
有 $M$ 个集合，每一个集合 $S_i$ 由 $C_i$ 个数组成，求由多少组集合里是数可以构成 $1,2, \cdots ,N$。
## 解析
由于这道题的数据很水，是 $1 \le N,M \le 10$ 的，所以我们可以用桶把 $S_i$ 出现的数记录下来，直接一遍 dfs 做这道题。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1000][1000],n,m,k[1000][1000],v[1000],ans;
void dfs(int now){
	bool t=0;	//标记是否已经构成了1到n
	for(int i=1;i<=n;i++)v[i]+=k[now][i];	//记录有多少个i
	for(int i=1;i<=n;i++)if(v[i]==0){	//判断是否构成1到n
		t=1;
		break;
	}if(t==0)ans++;
	for(int i=now+1;i<=m;i++)dfs(i);	//i一定是i=now+1，不然会重复
	for(int i=1;i<=n;i++)v[i]-=k[now][i];	//dfs回溯
	if(now==m)return ;	//结束条件
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>a[i][0];
		for(int j=1;j<=a[i][0];j++)
        cin>>a[i][j],k[i][a[i][j]]=1;	//统计是否出现过
	}
	dfs(0);
	cout<<ans;
	return 0;
}

```


---

## 作者：liangbob (赞：1)

### AT_abc289_c 题解

#### 思路分析

一道基础的深搜模板题，建议参考：[P1157 组合的输出](https://www.luogu.com.cn/problem/P1157)。

首先，我们需要先进行选择。由于选择的集合之间没有顺序之分，所以采用组合选取的方式。

那么如何进行组合选取呢？我们每次只需要选择**比前一个选择的集合的编号大的集合**（严格大于）就可以了。这样子的定序枚举就可以保证是组合选取（因为没有顺序之分你就要给他规定一个顺序），接下来就可直接使用深搜解决。

那么进行完组合选取之后又该怎么办呢？就要进行判断。题目要求所选出的集合中从 $1$ 到 $n$ 都得至少有一个，于是可以使用类似桶排序的思想。我们开一个数组记录 $1$ 到 $n$ 记录是否出现过。出现过就记录，最后判断是否都出现就可以了。

按照上述步骤进行实现即可，注意：要选择的集合个数不确定，要逐个枚举选择要选择的集合个数并进行搜索。

#### 代码

```cpp
#include <iostream>
using namespace std;
 
int n, m, a[15][15], t[15], c[15], cnt; //如题意，c 为每个集合的元素个数
bool used[15], pded[15]; //前者为使用数组，后者为判断数组
 
void dfs(int r, int pos)
{
	if(pos > r) //选了 r 个数（r为选择的要选择的集合个数）
	{
		memset(pded, false, sizeof(pded)); //重置判断数组。
		for(int i = 1;i <= r;i++)
		{
			for(int j = 1;j <= c[t[i]];j++) //遍历每个选择的集合
			{
				pded[a[t[i]][j]] = true; //记录该数出现过
			}
		}
		bool pd = pded[1]; //判断 1，为后面的与操作做准备
		for(int i = 2;i <= n;i++)
		{
			pd = pd && pded[i]; //与操作，1 到 n 都要出现。
		}
		cnt += int(pd); //记录个数 
		return;
	}
	for(int i = 1;i <= m;i++) //拓展
	{
	 	if(!used[i] && i > t[pos - 1]) // 如果没选择过而且满足顺序
	 	{ 
	 		t[pos] = i; //选择
	 		used[i] = true; //记录被选择
	 		dfs(r, pos + 1); //进行下一步选择
	 		used[i] = false; //回溯
		}
	}
}
int main()
{
	cin >> n >> m;
	for(int i = 1;i <= m;i++)
	{
		int q;
		cin >> q;
		c[i] = q;
		for(int j = 1;j <= q;j++)
		{
			cin >> a[i][j];
		}
	}
	for(int i = 1;i <= m;i++) dfs(i, 1); //逐个枚举选择要选择的集合个数并进行搜索
	cout << cnt << endl;
	return 0;
}
```



---

## 作者：_dijkstra_ (赞：1)

不怎么难。

## 思路

数据范围非常小，可以直接考虑暴搜。

暴搜时候，记录一个 $tmp_i$ 表示 $i$ 是否有出现过。

深搜里面分两类（选和不选）然后往下递归即可。

时间复杂度 $O(2^m n)$。

## 关键代码

```cpp
bool chk()
{
    for (int i = 1; i <= n; i++)
        if (!tmp[i])
            return false;
    return true;
}
void dfs(int x)
{
    if (x > m)
    {
        if (chk()) ans++;
        return;
    }
    dfs(x + 1);
 
    int ttmp[N] = {};
    for (int i = 1; i <= n; i++) ttmp[i] = tmp[i], tmp[i] |= a[x][i];
    dfs(x + 1);
    for (int i = 1; i <= n; i++) tmp[i] = ttmp[i];
}
void solve()
{
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        int cnt;
        cin >> cnt;
        while (cnt--) {int x; cin >> x; a[i][x] = true;}
    }
    dfs(1), cout << ans;
}
```

---

## 作者：aeiouaoeiu (赞：0)

### 题意

有 $m$ 个集合，第 $i$ 个集合有 $c_i$ 个元素，每个集合里的元素都在 $[1,n]$ 范围内，问有多少种可能的选择，使得选中的集合的交集包括 $[1,n]$ 范围内的所有整数。

### 解法

状态压缩。

我们用一个状态 $S$ 表示选择了哪些集合，如果 $S$ 二进制上的第 $i$ 位为 $1$ 则为选第 $i$ 个集合，否则不选（当然有时候为了方便可以反过来，不影响结果）。

然后我们暴力求这些选中集合的交集，判断 $[1,n]$ 范围内的所有整数是否都在其中即可。

时间复杂度 $\mathcal{O}(2^m(n+m\sum{c_i}))$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=15;
ll n,m,c[maxn],a[maxn][maxn],vis[(1<<maxn)],buc[maxn],ans;
int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=m;i++){
    	cin>>c[i];
    	for(int j=1;j<=c[i];j++) cin>>a[i][j];
	}
	for(int S=0;S<(1<<m);S++){
		for(int t=S,i=1;i<=m;t>>=1,i++) vis[i]=t&1; //每一位是否被选到
		memset(buc,0,sizeof(buc));
		for(int i=1;i<=m;i++){
			if(!vis[i]) continue;
			for(int j=1;j<=c[i];j++) buc[a[i][j]]=1;
		}
		bool flag=1;
		for(int i=1;i<=n;i++){
			if(!buc[i]) flag=0;
		}
		ans+=flag;
	}
	cout<<ans;
    return 0;
}
```


---

## 作者：Mikefeng (赞：0)

# [ABC289C] Coverage

## 题目翻译

给定 $m$ 个集合，要求从中选出任意个集合，使得它们的并集包含 $1$ 到 $n$ 的所有整数。

$1\le n,m\le10$

## 做法

将集合中所有的整数压缩成 $10$ 位 $2$ 进制整数，dp 转移。

时间复杂度 $O(m\cdot2^{2n})$。

## 代码

```cpp
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=x*10+c-48;
		c=getchar();
	}
	return x*f;
}
const int N=2005;
int n,m;
int f[N][N];
int main(){
	n=read();m=read();
	f[0][0]=1;
	F(i,1,m){
		int l=read(),tmp=0;
		F(i,1,l){
			int x=read();
			tmp+=1<<(x-1);
		}
		F(j,0,(1<<n)-1) f[i][j]=f[i-1][j];
		F(j,0,(1<<n)-1) F(k,0,(1<<n)-1) if((k|tmp)==j) f[i][j]+=f[i-1][k];
	}
	printf("%d\n",f[m][(1<<n)-1]);
	return 0;
}
```


---

