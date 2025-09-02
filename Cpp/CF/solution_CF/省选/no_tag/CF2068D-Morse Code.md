# Morse Code

## 题目描述

莫尔斯电码是一种经典的远程通信方式，但存在某些缺陷会增加长消息的传输时间。

在莫尔斯电码中，字母表中的每个字符被分配一个由点（.）和划（-）组成的序列，且没有序列是另一个序列的前缀。传输字符串时，各字符对应的序列按顺序发送。划的传输时间是点的两倍。

你的字母表包含 $n$ 个字符，其中第 $i$ 个字符在你的语言中出现频率为 $f_i$。你的任务是设计一个莫尔斯电码编码方案，为每个字符分配点划序列，以最小化单个字符的期望传输时间。即你需要最小化 $f_1t_1 + f_2t_2 + \cdots + f_nt_n$，其中 $t_i$ 是传输第 $i$ 个字符序列所需的时间。

## 说明/提示

第一个样例中，字母表包含三个字符（例如 $a$, $b$, $c$），频率分别为 $0.3$, $0.6$, $0.1$。在最优方案中，$a$ 对应 `-.`，$b$ 对应 `.`，$c$ 对应 `--`。此时期望传输时间为 $0.3 \cdot 3 + 0.6 \cdot 1 + 0.1 \cdot 4 = 1.9$ 时间单位/字符，这是最优解。

作为对比，若分配 $a\to$ `..`，$b\to$ `-`，$c\to$ `.-`，则期望传输时间为 $0.3 \cdot 2 + 0.6 \cdot 2 + 0.1 \cdot 3 = 2.1$。而分配 $a\to$ `-`，$b\to$ ` .`，$c\to$ `..` 虽然期望传输时间更低，但该方案无效，因为 `.` 是 `..` 的前缀。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3
0.3000 0.6000 0.1000```

### 输出

```
-.
.
--```

## 样例 #2

### 输入

```
3
0.3000 0.4500 0.2500```

### 输出

```
..
-
.-```

# 题解

## 作者：_maojun_ (赞：4)

转化为求一个 $n$ 个叶子二叉树，左儿子边长为 $1$，右儿子边长为 $2$。叶子的权值是 $a$（原题中的 $f$）的一个排列，深度定义为到根的距离，最小化叶子权值距离乘积之和，构造方案。

---

和 QOJ7793 比较像。

显然是 $a$ 从大到小匹配深度从小到大。

比较关心的是当前层和下一层，设 $f_{i,j,k}$ 表示前面已经完成 $i$ 的钦定，当前层有 $j$ 个叶子，下一层有 $k$ 个叶子。层数不重要，在转移到下一层时计算答案。

三维的做法具体可以参考官方题解。

模拟赛时写了一个奇怪的二维状态做法，把前两维合并起来：$f_{i,j}$ 表示当前有 $i$ 个没有 tag 的点，和 $j$ 个 $+1$ tag 的点。

转移是枚举 $i$ 个点中的后 $k$ 个分裂：$f_{i+j,k}\gets f_{i,j}+s_{i-k+1}$，其中 $s_i$ 表示 $a$ 从小到大排序之后 $i$ 的后缀和。

for example：$i=3,j=2,k=2$：

```
O   O   O   |   |
            O   O
```

转移到

```
O  / \     / \      |   |
  O   \   O   \     O   O
       O       O
```

往后推进一层

```
O   O   |   O   |   O   O
        O       O
```

也就是 $i'=5,j'=2$。

选择后 $k$ 个分裂的意思是钦定前 $i-k$ 个不再拓展，而这样 dp 并不能保证在之后钦定的点不再拓展。

而这样的后果是这种不合法转移算出来比实际上大。但所有方案都一定存在一种合法的转移，所以并不会影响答案。

方案按照转移复原出来即可。

```cpp
typedef double db;
const int N=205;
int n,p[N];db a[N],s[N];
string b[N],c[N];

db f[N][N];
inline void main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%lf",&a[i]);
	iota(p+1,p+n+1,1);
	sort(p+1,p+n+1,[&](int x,int y){return a[x]>a[y];});
	for(int i=n;i;i--)s[i]=s[i+1]+a[p[i]];
	for(int i=1;i<=n;i++)for(int j=0;i+j<=n;j++)
		if(i==1&&!j)f[i][j]=0;
		else{
			f[i][j]=1e18;
			for(int k=!j;j+k<=i&&k<i;k++)
				f[i][j]=min(f[i][j],f[i-k][k]+s[i-k-j+1]);
		}
	vector<int>g;
	for(int i=n,j=0;i^1||j;){
		for(int k=!j;j+k<=i&&k<i;k++)
			if(f[i-k][k]+s[i-k-j+1]==f[i][j]){
				g.emplace_back(j);i-=k;j=k;break;
			}
	}
	reverse(g.begin(),g.end());
	int i=1,j=0;for(int k:g){
		for(int t=i+1;t<=i+j;t++)b[t]=c[t-i];
		for(int t=1;t<=k;t++)c[t]=b[i-k+t]+'-';
		for(int t=i-k+1;t<=i;t++)b[t]+='.';
		i+=j;j=k;
	}
	for(int i=1;i<=n;i++)c[p[i]]=b[i];
	for(int i=1;i<=n;i++)cout<<c[i]<<'\n';
}
```

---

## 作者：缪凌锴_Mathew (赞：1)

另一个抽象做法。

---

> 有 $n$ 个 $12$ 串，不存在一个串为另一个串的前缀。
>
> 求 $i$ 的串和乘 $a_i$ 的和的最小值。

显然 $a$ 从大到小匹配串和从小到大，先按 $a$ 排序。

考虑长度为 $i$ 的 $12$ 串的个数：$f_i=f_{i-2}+f_{i-1}$。（斐波那契数列）

考虑直接对着这个 dp：

$dp_{i,j,p,q}$ 表示到 $a_i$，现在和为 $j$，$j$ 剩 $p$ 个未用，$j-1$ 剩 $q$ 个未用（$p,q$ 向 $n$ 取 $\min$）的代价。

$$
\begin{cases}
dp_{i-1,j,p,q+1}+{j\times a_i} \to dp_{i,j,p,q}\\
dp_{i,j,p,q} \to dp_{i,j+1,q,p+q}
\end{cases}
$$

和为 $j$ 的数是 $f_j$ 个，$j$ 为 $O(\log n)$ 级别。

所以现在复杂度是 $O(n^3\log n)$，可过（？），但可以优化。

转移中加了 $j\times a_i$，那么 $a_{i+1\dots n}$ 都至少有 $j$ 倍的贡献，考虑拆成后缀和 $suf$。

$$
\begin{cases}
dp_{i-1,j,p,q+1} \to dp_{i,j,p,q}\\
dp_{i,j,p,q}+suf_{i+1} \to dp_{i,j+1,q,p+q}
\end{cases}
$$

注意到 $j$ 没用了，省掉一维：

注意 $(p,q)$ 转移到 $(q,p+q)$，于是先枚举 $q$ 再枚举 $p$：

$$
\begin{cases}
dp_{i-1,p,q+1} \to dp_{i,p,q}\\
dp_{i,p,q}+suf_{i+1} \to dp_{i,q,p+q}
\end{cases}
$$

时间复杂度即为 $O(n^3)$。

---

[Submission](https://codeforces.com/problemset/submission/2068/312777391)

---

## 作者：gdf_yhm (赞：1)

[CF2068D](https://www.luogu.com.cn/problem/CF2068D)

### 思路

$f$ 升序、$t$ 降序排序，对应位置乘起来。

如何判定一个 $t$ 是否合法。构造一个有根树，每个点有长为 $1$ 和 $2$ 的两条出边，有 $n$ 个叶子，$t$ 数组为叶子的深度。$t$ 中的 $x+1$ 和 $x$ 可以合并为 $x-1$。即从大到小枚举值域 $x$，设有 $j$ 个 $x+1$，$k$ 个 $x$，加入 $c$ 个深度为 $x$ 的叶子，然后 $x$ 减 $1$，有 $k+c-j$ 个 $x+1$ 和 $j$ 个 $x$。只要满足 $cnt_{x+1}\ge cnt_x$ 即可。

所以可以 dp，再设一维 $i$ 表示已经选了前 $i$ 深的叶子，加入 $1$ 个深度为 $x$ 的叶子权值加 $f_i\times x$。对于一个 $x$ 复杂度为 $O(n^3)$，$x$ 是 $\log n$ 级别的，最大可以取到 $20$。

还原方案即模拟构造树的过程。

### code

```cpp
int n,a[maxn],id[maxn];
char c[10];
int dp[21][maxn][maxn][maxn];
void chkmn(int &u,int v){(u>v)&&(u=v);}
pii fa[maxn*15];
int t[21],pos;
vector<char> ans[maxn];
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read(),a[i]=read();
	for(int i=1;i<=n;i++)id[i]=i;
	sort(id+1,id+n+1,[&](int u,int v){return a[u]<a[v];});
	sort(a+1,a+n+1);
	mems(dp,0x3f);dp[20][0][0][0]=0;
	for(int x=20;x;x--){
		for(int i=0;i<n;i++){
			for(int j=0;j<=i;j++){
				for(int k=0;j+k<=i;k++){
					chkmn(dp[x][i+1][j][k+1],dp[x][i][j][k]+a[i+1]*x);
				}
			}
		}
		for(int i=0;i<=n;i++){
			for(int j=0;j<=i;j++){
				for(int k=j;j+k<=i;k++)if(dp[x][i][j][k]<inf){
					chkmn(dp[x-1][i][k-j][j],dp[x][i][j][k]);
				}
			}
		}
	}
	// printf("%lld\n",dp[0][n][0][1]);
	vector<int> val;
	for(int x=0,i=n,j=0,k=1;x<=20;){
		x++,j+=k,swap(j,k);
		while(i&&k&&dp[x][i][j][k]==dp[x][i-1][j][k-1]+a[i]*x){
			i--,k--;
			val.pb(x);
		}
	}
	reverse(val.begin(),val.end());
	for(int x:val)t[x]++;
	vector<int> id1,id2;
	int pos=n;
	for(int x=20,i=1;~x;x--){
		while(t[x]--)id2.pb(i++);
		vector<int> tmp;
		while(id2.size()&&id1.size()){
			++pos,tmp.pb(pos);
			fa[id2.back()]={pos,1},id2.pop_back(),fa[id1.back()]={pos,2},id1.pop_back();
		}
		id1=id2,id2=tmp;
	}
	for(int i=1;i<=n;i++){
		vector<int> res;
		int u=i;
		while(fa[u].fi){
			res.pb(fa[u].se);
			u=fa[u].fi;
		}
		reverse(res.begin(),res.end());
		for(int w:res)ans[id[i]].pb(w==1?'.':'-');
	}
	for(int i=1;i<=n;i++){
		for(char c:ans[i])putchar(c);puts("");
	}
}
```

---

