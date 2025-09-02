# Lanterns

## 题目描述

有 $n$ 个灯笼拍成一排，第 $i$ 个灯笼具有 $p_i$ 的亮度。每个灯笼要么朝向左，照亮左边编号为 $[i - p_i,i - 1]$ 的灯笼，要么朝向右，照亮右边编号为 $[i + 1, i + p_i]$ 的灯笼。

寻找一种方案，为所有的灯笼确定朝向，使得每一个灯笼被至少一个其他灯笼照亮。

## 说明/提示

$1\le t \le 1\times 10^4$。对于每组数据，有 $2\le n\le 3\times 10^5,0\le p_i\le n$。同一个测试点内保证 $\sum n\le 3\times 10^5$。

## 样例 #1

### 输入

```
4
8
0 0 3 1 1 1 1 2
2
1 1
2
2 2
2
0 1```

### 输出

```
YES
RRLLLLRL
YES
RL
YES
RL
NO```

# 题解

## 作者：RiverHamster (赞：37)

设计 DP 状态 $f_i$ 表示前 $i$ 盏灯可以点亮的最长前缀，初值为 $f_0 = f_1 = 0$。

考虑如下几种转移：

- 前 $i - 1$ 盏灯无法覆盖 $i$，直接忽略掉第 $i$ 盏灯，即 $f_i \gets f_{i-1}$；

- 前 $i - 1$ 盏灯可以覆盖 $i$，第 $i$ 盏灯指向右边，即 $f_i \gets \max(f_{i-1}, i + p_i)$ 其中 $f_{i-1} \ge i$。

- 第 $i$ 盏灯指向左边，和之前的一个前缀的灯点亮的前缀拼成一个更大的前缀，中间的全部指向右边。即找到最小的非负整数 $t$，满足 $f_t \ge i - p_i - 1$，就有转移 $f_i \gets \max\{i - 1, t + 1 + p_{t+1}, \dots,i - 1 + p_{i-1}\}$。

  二分出 $t$，用 RMQ 维护 $i + p_i$ 区间最大即可。

最后记录转移位置即可输出方案。复杂度 $\mathcal O(n \log n)$，当然精细实现可以 $\mathcal O(n)$。

```cpp
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

#define LOG(f...) fprintf(stderr, f)

using ll = long long;

template<class T> void read(T &x){
  char ch; x = 0;
  int f = 1;
  while (isspace(ch = getchar()));
  if (ch == '-') ch = getchar(), f = -1;
  do x = x * 10 + ch - '0'; while(isdigit(ch = getchar()));
  x *= f;
}
template<class T, class ...A> void read(T &x, A&... args) { read(x); read(args...); }

const int N = 300005;
int p[N], f[N], from[N];
int n;
int st[20][N];
char res[N];

void buildST() {
  for (int i = 1; i <= n; ++i)
    st[0][i] = i + p[i];
  for (int i = 1, li = __lg(n); i <= li; ++i)
    for (int j = 1; j <= n - (1 << i) + 1; ++j)
      st[i][j] = max(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
}
int range_max(int l, int r) {
  if (l > r) return 0;
  int k = __lg(r - l + 1);
  return max(st[k][l], st[k][r - (1 << k) + 1]);
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  int T;
  read(T);
  while (T--) {
    read(n);
    for (int i = 1; i <= n; ++i) read(p[i]);
    buildST();
    fill(f + 1, f + 1 + n, 0);
    from[1] = 1;
    for (int i = 2; i <= n; ++i) {
      if (!p[i]) { f[i] = f[i - 1]; from[i] = i; continue; }
      int t = lower_bound(f, f + i, i - p[i] - 1) - f;
      from[i] = t;
      if (t == i) f[i] = f[i - 1];
      else {
        f[i] = max(i - 1, range_max(t + 1, i - 1));
        if (f[i - 1] > f[i]) f[i] = f[i - 1], from[i] = i;
        if (f[i - 1] >= i && i + p[i] > f[i]) {
          f[i] = i + p[i];
          from[i] = i;
        }
      }
    }

    if (f[n] < n) puts("NO");
    else {
      puts("YES");
      int cur = n;
      while (cur) {
        if (from[cur] == cur) res[cur] = 'R', --cur;
        else {
          res[cur] = 'L';
          fill(res + from[cur] + 1, res + cur, 'R');
          cur = from[cur];
        }
      }
      res[n + 1] = 0; puts(res + 1);
    }
  }
  return 0;
}
```



---

## 作者：541forever (赞：7)

难度虚高，建议评 蓝 / 紫。

对于此类覆盖所有点的问题，设计状态时不难想到以一个前缀的编号覆盖一段前缀，因此我们可以设 $f_i$ 表示前 $i$ 个灯笼能覆盖的最远前缀到了第 $f_i$ 个灯笼。转移可以考虑将 $i$ 朝左和 $i$ 朝右分开考虑。

1. 当 $i$ 朝右时，若 $f_{i-1} \ge i$，则 $f_i=\max(f_{i-1},i+p_i)$，若 $f_{i-1} < i$，则 $f_i=f_{i-1}$ 。
2. 当 $i$ 朝左时，我们可以发现，只要将前缀覆盖到 $i-p_i$ 的位置，设 $j$ 为第一个满足 $f_j \ge i-p_i$ 的位置，则 $j+1$ 到 $i-1$ 的位置都能向右，所以此时 $f_i=\max_{k=j+1}^{i-1} k+p_k$。可以二分出 $j$，接着用线段树或 ST 表查出 $j+1$ 到 $i-1$ 中的最大值。

是个典题，但实现时可能需要注意一些细节。

[Code](https://codeforces.com/contest/1476/submission/210231547)

---

## 作者：hjqhs (赞：5)

水 *3000，甚至没有我昨天 S 模拟赛 T3 难，不如降蓝。  
很典的一道题，一眼动态规划，如果你要让所有点被覆盖，那么状态可以设计成覆盖一段前缀，并且中间不允许出现断点。  
设 $f_i$ 为前 $i$ 盏灯能点亮的最长前缀。  
如果 $i$ 向右照，分两种情况讨论，如果 $f_{i-1}<i$，前面的都覆盖不到自己也没有必要往右覆盖了，直接 $f_i=f_{i-1}$，否则为 $f_i=\max({f_{i-1},i+p_i})$。  
如果 $i$ 向左照，与之前每盏灯的前缀拼成了一个更大的前缀。记这盏灯的编号为 $t$，明显具有单调性，所以可以二分找到 $t$。  
同时用一个 ST 表维护 $i+p_i$ 的最值即可。
ST 表部分：
```cpp
rep(i,1,n)st[i][0]=i+p[i];
for(int j=1;(1<<j)<=n;++j){
   for(int i=1;i+(1<<j)-1<=n;++i){
      st[i][j]=Max(st[i][j-1],st[i+(1<<j-1)][j-1]);
   }
}
int query(int l,int r){
  if(l>r)return 0;
  int mid=__lg(r-l+1);
  return Max(st[l][mid],st[r-(1<<mid)+1][mid]);
}
```  
dp 部分：
```cpp
f[0]=f[1]=g[1]=ans[1]=0;
  rep(i,2,n){
    if(f[i-1]<i)f[i]=f[i-1];
    else f[i]=Max(f[i-1],i+p[i]);
    g[i]=i-1;ans[i]=0;
    int t=lower_bound(f,f+i,i-p[i]-1)-f;
    if(t<i){
      int d=Max(i-1,query(t+1,i-1));
      if(f[i]<=d)f[i]=d,g[i]=t,ans[i]=1;
    }
  }
```
输出答案部分：
```cpp
if(f[n]<n)cout<<"NO"<<'\n';
else cout<<"YES"<<'\n',printans(n),cout<<'\n';
void printans(int cur){
  if(!cur)return;
  printans(g[cur]);
  if(!ans[cur])cout<<"R";
  else{
    rep(i,g[cur]+1,cur-1)cout<<"R";
    cout<<"L";
  }
}
```

---

## 作者：tsqtsqtsq0309 (赞：4)

## 分析

显然是一道极其优美的 dp 题。

定义 $f_i$ 表示前 $i$ 盏灯最多能将 $[1, f_i]$ 的区间全部照亮，转移显然可以分情况讨论：

#### 第 $i$ 盏灯笼向右照

如果 $f_i-1\ge i$，即前 $i-1$ 盏灯笼已经能照亮第 $i$ 盏灯，则有：$f_i=\max\{f_{i-1},i+p_i\}$，否则前 $i-1$ 盏灯笼不能将第 $i$ 盏灯笼照亮，故第 $i$ 盏灯笼只能由之后的灯笼照亮，则有：$f_i=f_{i-1}$。

```c++
            if(f[i - 1] >= i)f[i] = max(f[i - 1], i + p[i]);
            else f[i] = f[i - 1]; // 考虑灯笼向右照的情况
```

#### 第 $i$ 盏灯笼向左照

此时需要找到最小的 $j$ 满足 $f_j\ge i-p_i-1$，即前 $j$ 盏灯笼与第 $i$ 盏灯笼可以完全照亮 $[1,i)$。那么 $[j+1,i-1]$ 的部分必然向右照更优，可以考虑对 $[j+1,i-1]$ 这个区间进行二分，优化时间复杂度。则有 ：$f_i=\max(i-1,\underset{k\in[j+1,i-1]} {\max}\{k+p_k\})$。查找最大值可以使用 st 表维护静态区间最大值进行优化。

```c++
            int left = 0, right = i - 1, mid, res = -1;
            while(left <= right){ // 二分
                mid = left + right >> 1;
                if(f[mid] >= i - p[i] - 1){res = mid;right = mid - 1;} // 往左边寻找更小的 j
                else left = mid + 1; // 如果左边没有就往右边寻找
            }
            if(res != -1)f[i] = max(f[i], max((i - 1), query(res + 1, i - 1))); // 考虑灯笼向左照的情况
```

总的状态转移方程为：
$$
f_i = \begin{cases}
\max\{f_{i-1},i+p_i\}, & f_i-1\ge i \\
f_{i-1}, & f_i-1<i  \\
\end{cases}
$$

$$
f_i=\max(i-1,\underset{k\in[j+1,i-1]} {\max}\{k+p_k\})
$$

暴力转移时间复杂度为 $O(n^3)$，二分可以优化到 $O(n^2\log n)$， st 表维护区间静态最值可以进一步优化到 $O(n\log n)$，数据范围 $2\le n\le 3\times 10^5$，$O(n\log n)$ 可以通过本题。本题输入输出量较大，建议使用读入优化。以下是读入优化模板：

```c++
int read(){ // 读入优化
    int t = 1, x = 0;char ch = getchar(); // t 用于记录读入数字的符号，x 用于记录数字的绝对值
    while(!isdigit(ch)){if(ch == '-')t = -1;ch = getchar();} // 忽略空格部分以及特判负号
    while(isdigit(ch)){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();} //读入数字
    return x * t; //特判负号
}
```

## 推导具体方案

如果 $f_i\ge n$ 则说明存在合法方案符合题意。输出具体方案时递归求解即可。

```c++
void getans(int pos){ // 递归推出具体方案
	if(pos == 0)return; // 边界
	if(f[pos] == f[pos - 1]){
        ans[pos] = 'R';getans(pos - 1);return; // 向右照
    }
	if(f[pos] == pos + p[pos] && f[pos - 1] >= pos){
        ans[pos] = 'R';getans(pos - 1);return; // 向右照
    }
	int left = 0, right = pos - 1, mid, res;
	while(left <= right){ // 二分
		mid = left + right >> 1;
		if(f[mid] >= pos - p[pos] - 1){ // 往左边寻找更小的 j
            res = mid;right = mid - 1;
        }
		else left = mid + 1; // 如果左边没有就往右边寻找
	}
	for(int i = res + 1 ; i < pos ; i ++)ans[i] = 'R'; // 向右照
	ans[pos] = 'L';getans(res); // 向左照
}
```

## 代码

```c++
#include <iostream> // 头文件不解释
#define MAXN 300005 // n 的最大值
using namespace std; // 命名空间不解释
int T, n; // 数据组数
int p[MAXN], f[MAXN]; // 每个灯笼亮度以及 dp 数组
int lg[MAXN], st[MAXN][25];  // st 表维护静态区间最大值
char ans[MAXN]; // 记录答案
int read(){ // 读入优化
    int t = 1, x = 0;char ch = getchar(); // t 用于记录读入数字的符号，x 用于记录数字的绝对值
    while(!isdigit(ch)){if(ch == '-')t = -1;ch = getchar();} // 忽略空格部分以及特判负号
    while(isdigit(ch)){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();} //读入数字
    return x * t; //特判负号
}
int query(int l, int r){ // 查询 st 表
    if(l > r)return 0; // 特判
    int op = lg[r - l + 1];
    return max(st[l][op], st[r - (1 << op) + 1][op]);
}
void getans(int pos){ // 递归推出具体方案
	if(pos == 0)return; // 边界
	if(f[pos] == f[pos - 1]){ans[pos] = 'R';getans(pos - 1);return;} // 向右照
	if(f[pos] == pos + p[pos] && f[pos - 1] >= pos){ans[pos] = 'R';getans(pos - 1);return;} // 向右照
	int left = 0, right = pos - 1, mid, res;
	while(left <= right){ // 二分
		mid = left + right >> 1;
		if(f[mid] >= pos - p[pos] - 1){res = mid;right = mid - 1;} // 往左边寻找更小的 j
		else left = mid + 1; // 如果左边没有就往右边寻找
	}
	for(int i = res + 1 ; i < pos ; i ++)ans[i] = 'R'; // 向右照
	ans[pos] = 'L';getans(res); // 向左照
}
int main(){
    for(int i = 2 ; i < MAXN ; i ++)lg[i] = lg[i >> 1] + 1; // 预处理倍增数组
    T = read(); // 数据组数
    while(T--){  // 循环处理每组数据
        n = read(); // 读入个数
        for(int i = 1 ; i <= n ; i ++)p[i] = read(); // 读入亮度
        for(int i = 1 ; i <= n ; i ++)st[i][0] = i + p[i];
        for(int i = 1 ; i <= lg[n] ; i ++)
            for(int j = 1 ; j <= n - (1 << i) + 1 ; j ++)
                st[j][i] = max(st[j][i - 1], st[j + (1 << (i - 1))][i - 1]); // 预处理 st 表
        for(int i = 1 ; i <= n ; i ++){
            if(f[i - 1] >= i)f[i] = max(f[i - 1], i + p[i]);
            else f[i] = f[i - 1]; // 考虑灯笼向右照的情况
            int left = 0, right = i - 1, mid, res = -1;
            while(left <= right){ // 二分
                mid = left + right >> 1;
                if(f[mid] >= i - p[i] - 1){res = mid;right = mid - 1;} // 往左边寻找更小的 j
                else left = mid + 1; // 如果左边没有就往右边寻找
            }
            if(res != -1)f[i] = max(f[i], max(i - 1, query(res + 1, i - 1))); // 考虑灯笼向左照的情况
        }
        if(f[n] >= n){ // 判断是否存在合法方案
            puts("YES");getans(n); // 存在合法方案输出 YES 并求出具体方案
            for(int i = 1 ; i <= n ; i ++)putchar(ans[i]); // 输出方案
            putchar('\n');
        }
        else puts("NO"); // 不存在合法方案直接输出 NO
    }
    return 0;
} // 完结撒花～
```

---

## 作者：7KByte (赞：4)

神仙 $\rm DP$ 题。

首先，可行性转换为最优性。我们定义状态 $f[i]$ 表示前 $i$ 盏灯能够最多能覆盖区间 $[1,f[i]]$ 中所有的灯。

这是最关键的一步，后面的步骤都比较套路。需要注意细节和边界问题。

对于当前的 $i$ ，只有向左和向右两种选择。

选择向右，如果 $f[i-1]\ge i$ ，则可以扩展一段 $f[i]=\max\{f[i-1],i+p[i]\}$，否则第 $i$ 盏灯无法覆盖，$f[i]=f[i-1]$ 。

如果向左，则考虑最小的 $j$ 满足 $f[j]\ge i-p[i]-1$ ，这是两段能连接起来的充要条件。

此时有 $f[i]=\max\{f[j],\max\limits_{j<k<i}\{k+p_k\}\}$ ，这也不难理解，在 $(j,i)$ 区间内的灯已经被全部覆盖了，全部朝右必定最优。

输出方案直接递归处理即可，时间复杂度 $\mathcal{O}(n\log n)$ 。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 300005
using namespace std;
int n,p[N],f[N],g[N][19],t,ans[N];
int rmq(int l,int r){
	if(l>r)return 0;
	int cur=log2(r-l+1);
	return max(g[l][cur],g[r-(1<<cur)+1][cur]);
}
void calc(int i){
	if(!i)return;
	if(f[i]==f[i-1])calc(i-1);
	else{
		if(f[i]==i+p[i]&&f[i-1]>=i)ans[i]=1,calc(i-1);
		else{
			int l=0,r=i-1,ed=~0;
			while(l<=r){
				int mid=(l+r)>>1;
				if(f[mid]>=i-p[i]-1)ed=mid,r=mid-1;
				else l=mid+1;
			}
			rep(x,ed+1,i-1)ans[x]=1;
			ans[i]=0;calc(ed);
		}
	}
}
void solve(){
	scanf("%d",&n);t=log2(n);
	rep(i,1,n)scanf("%d",&p[i]),g[i][0]=i+p[i];
	rep(j,1,t)rep(i,1,n-(1<<j)+1)g[i][j]=max(g[i][j-1],g[i+(1<<(j-1))][j-1]);
	rep(i,0,n)f[i]=0;
	rep(i,1,n){
		f[i]=f[i-1];
		if(f[i-1]>=i)f[i]=max(f[i],i+p[i]);
		int l=0,r=i-1,ed=~0;
		while(l<=r){
			int mid=(l+r)>>1;
			if(f[mid]>=i-p[i]-1)ed=mid,r=mid-1;
			else l=mid+1;
		}
		if(~ed)f[i]=max(f[i],max(i-1,rmq(ed+1,i-1)));
	}
	if(f[n]>=n)puts("YES");
	else {puts("NO");return ;}
	calc(n);
	rep(i,1,n)if(ans[i])putchar('R');else putchar('L');putchar('\n');
}
int main(){
	int T;scanf("%d",&T);
	while(T--)solve();
	return 0;
}
```

---

## 作者：syzf2222 (赞：3)

摆了一天，深夜写题，直接过了，嘲讽一句，三千就这？

我们称向左的为黑点，向右的为白点。

考察第一个黑点，要求 $i-p_i\leqslant 1$，而 $1$ 到 $i-1$ 全为白点，由这些点覆盖的也染白，染到不变为止，剩下的是一个相似的子结构。

定义 $dp_i$ 表示第 $i$ 个点为黑点时最远能覆盖到的位置，$to_i$ 为白点最远位置。

显然 $to_i$ 可以直接递推求得。

令 $L=\max(1,i-p_i)$，则 $[L,i-1]$ 最远能到的就是 $i+1$ 到这些点跳一步最远处的 $to$ 的最大值。

故影响的只有区间内跳一步的最大值，令 $P$ 为区间最后一个跳一步最大值的位置。

若存在一个 $dp_j\geqslant L-1,j<P$，则这个 $j$ 显然是最优秀的；

否则如果 $dp_P\geqslant L-1$，那么这个 $P$ 也是当下最优秀的；

因为我们发现任意 $P<j<i$ 都不如 $P$ 优秀。

如果 $dp_P$ 小了，由于 $p_j<p_P,j>P$，$j$ 的存在不能解决这个问题；

否则如果 $j,P$ 均为黑，则此时答案显然更劣；

若 $P$ 为白且 $dp_j<j-1$，则存在更小的 $j',dp_j=dp_{j'}$；否则如果 $P+p_P<i$ 则无所谓；否则令 $j$ 为黑点 $i$ 为白点更优。

于是直接 $dp$ 即可。复杂度线对。

```
#include<bits/stdc++.h>
using namespace std;
const int maxn=3e5+10;
const int mod=1e9+7;
#define inf 1e9
#define pb push_back
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
int T,n,m,to[maxn][20],p[maxn],dp[maxn],id[maxn],Mx[maxn],pos[maxn],Ans[maxn],Mxp[maxn][20],lg[maxn];
inline int Qry(int l,int r){
	if(l>r)return 0;int k=lg[r-l+1];
	return max(Mxp[l][k],Mxp[r-(1<<k)+1][k]);
}
inline int query(int l,int r){
	if(l>r)return 0;int k=lg[r-l+1];
	return max(to[l][k],to[r-(1<<k)+1][k]);
}vector<int>P[maxn];
inline void solve(){
	n=read();
	for(int i=1;i<=n;i++){
		for(int j=0;j<=19;j++)to[i][j]=Mxp[i][j]=0;
		dp[i]=id[i]=Mx[i]=pos[i]=Ans[i]=0;
		p[i]=read();P[i].clear();Mxp[i][0]=min(n,i+p[i]);	
	}to[n][0]=n;lg[0]=-1;
	for(int i=1;i<=n;i++)lg[i]=lg[i>>1]+1;
	for(int j=1;j<=19;j++)
		for(int i=1;i+(1<<j)-1<=n;i++)
			Mxp[i][j]=max(Mxp[i][j-1],Mxp[i+(1<<j-1)][j-1]);
	for(int i=1;i<=n;i++)P[Mxp[i][0]].pb(i);
	for(int i=n-1;i>=1;i--){
		to[i][0]=p[i]?query(i+1,min(n,i+p[i])):i;
//		printf("%d ",to[i][0]);
		for(int j=1;i+(1<<j)-1<=n;j++)
			to[i][j]=max(to[i][j-1],to[i+(1<<j-1)][j-1]);
//		P[to[i][0]].pb(i);
	}
	for(int i=2;i<=n;i++){
//		printf("i=%d\n",i);
		if(!p[i]){
			dp[i]=(Mx[i-1]>=i-1?Mx[i-1]:0),pos[i]=id[i-1];
			if(dp[i]>Mx[i-1])Mx[i]=dp[i],id[i]=i;else Mx[i]=Mx[i-1],id[i]=id[i-1];continue;
//			printf("dp=%d pos=%d\n",dp[i],pos[i]);
		}int L=max(1,i-p[i]),Max=Qry(L,i-1);
//		printf("L=%d Max=%d\n",L,Max);
		int tr=lower_bound(P[Max].begin(),P[Max].end(),i)-P[Max].begin()-1;tr=P[Max][tr];//puts("over2");
		int res=(Max<i?i-1:max(i,query(i+1,Max)));
//		printf("%d %d %d %d\n",L,Max,tr,res);
		int Maxx=Qry(tr+1,i-1),ress=(Maxx<i?i-1:max(i,query(i+1,Maxx)));
		if(Mx[tr-1]>=L-1)dp[i]=max(Mx[tr-1],res),pos[i]=id[tr-1];
		if(dp[tr]>=L-1&&dp[i]<max(dp[tr],ress))dp[i]=max(dp[tr],ress),pos[i]=tr;
		if(dp[i]>Mx[i-1])Mx[i]=dp[i],id[i]=i;else Mx[i]=Mx[i-1],id[i]=id[i-1];
//		printf("dp=%d pos=%d\n",dp[i],pos[i]);
	}if(Mx[n]<n)return puts("NO"),void();puts("YES");
	int Pos=id[n];while(Pos)Ans[Pos]=1,Pos=pos[Pos];
	for(int i=1;i<=n;i++)putchar(Ans[i]?'L':'R');puts("");
}
int main(){
	T=read();
	while(T--)solve();
	return 0;
}
```

深深地感到自己的弱小。

---

## 作者：cwfxlh (赞：2)

## [CF1476F](https://www.luogu.com.cn/problem/CF1476F)   
评黑多少是有点逆天了。    

考虑令 $f_i$ 表示前 $i$ 个灯笼能够覆盖的最长前缀，则有三种转移：    

$$f_{i-1}<i:f_i=f_{i-1}$$     
$$f_{i-1}\geq i:f_i=\max(f_{i-1},i+p_i)$$     

前两种转移相对简单，也比较好想，第三种就是说，把 $i$ 的灯笼往左照，让它和之前的某一段 $[1,j]$ 一起，把 $[1,i]$ 全部照掉，然后 $[j+1,i-1]$ 的灯笼全部往右照，尽可能地扩大前缀。    

我们发现 $f_i$ 具有单调性，所以对于上文提到的 $[1,j]$，可以二分出最小的 $j$ 满足 $f_j\geq i-p_i-1$，而对于 $[j+1,i-1]$ 的最大右端点值，随便搞一个 $rmq$ 就可以了，本人用的 ST 表写的（查询是瞎写的）。     

关于是否有方案，如果 $f_n\geq n$，则有方案，否则没方案。方案大概记一下就可以了。          

代码：    

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,p[400003],f[400003][3],mxr[400003],k1,k2,k3,k4,k5,k6,k7,k8,k9;
int ans[400003],rmq[300003][29];
int l,r,mid;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d",&p[i]);
			mxr[i]=i+p[i];
			rmq[i][0]=mxr[i];
		}
		for(int i=1,j=2;j<=n;j*=2,i++){
			for(int u=1;u+j-1<=n;u++){
				rmq[u][i]=max(rmq[u][i-1],rmq[u+(j>>1)][i-1]);
			}
		}
		f[0][0]=0;
		k1=0;
		for(int i=1;i<=n;i++){
			if(f[i-1][0]<i){
				f[i][0]=f[i-1][0];
				f[i][1]=i-1;
				f[i][2]=2;
			}
			else{
				f[i][0]=max(f[i-1][0],mxr[i]);
				f[i][1]=i-1;
				f[i][2]=2;
			}
			if(p[i]!=0){
				l=0;
				r=i-1;
				while(l<r){
					mid=((l+r)>>1);
					if(f[mid][0]>=i-p[i]-1)r=mid;
					else l=mid+1;
				}
				if(f[l][0]>=i-p[i]-1){
					k2=i-1;
					k3=l+1;
					k4=24;
					while(k4>=0){
						if(k3+(1<<k4)-1<i){
							k2=max(k2,rmq[k3][k4]);
							k3+=(1<<k4);
						}
						k4--;
					}
					if(k2>f[i][0]){
						f[i][0]=k2;
						f[i][1]=l;
						f[i][2]=3;
					}
				}
			}
			k1=max(k1,mxr[i]);
		}
		if(f[n][0]>=n){
			puts("YES");
			k1=n;
			while(k1){
				if(f[k1][2]==3){
					for(int i=f[k1][1]+1;i<k1;i++)ans[i]=2;
					ans[k1]=1;
				}
				else for(int i=f[k1][1]+1;i<=k1;i++)ans[i]=f[k1][2];
				k1=f[k1][1];
			}
			for(int i=1;i<=n;i++){
				if(ans[i]==2)printf("R");
				else printf("L");
			}
			printf("\n");
		} 
		else puts("NO");
	}
	return 0;
}
```


---

## 作者：__Star_Sky (赞：1)

## Description
有 $n$ 个灯笼排成一行，每个灯笼有一个亮度 $p$。每个灯笼可以选择朝向左边或朝向右边。亮度为 $p_i$ 的灯笼可以照亮位于 $[i-p_i,i-1]$ 或 $[i+1,i+p_i]$ 的灯笼。注意每个灯笼都不能照亮自己。问是否存在一种方案使得每个灯笼都被至少一个灯笼照亮。如果有，输出任意一种方案。多组数据，$\sum n\le3\times10^5$

## Solution
虽然每个灯笼只有朝左和朝右两种状态，但是 $n$ 达到了 $3\times10^5$ 的级别，如果枚举每个灯笼可能的状态显然会超时。因此可以考虑动态规划。设 $f_i$ 表示前 $i$ 个灯笼最多可以使得从第一个灯笼往右多少个灯笼被照亮。

对于每个 $f_i$，首先有 $f_i=f_{i-1}$，因为前 $i-1$ 个灯笼能照亮的前 $i$ 个灯笼一定也能照亮。接下来考虑第 $i$ 个灯笼的状态。如果第 $i$ 个灯笼朝右，并且已经有 $f_{i-1}\ge i$，即前 $i-1$ 个灯笼已经能够照亮到第 $i$ 个灯笼的位置，那么 $f_i=\max(f_i,i+p_i)$。如果第 $i$ 个灯笼朝向左，那么此时第 $i$ 个灯笼照亮了位于 $[i-p_i,i-1]$ 的灯笼。我们可以找到离 $i$ 最远，并且满足 $j<i,f_j\ge i-p_i-1$ 的 $j$，即前 $j$ 个灯笼已经能够照亮前 $i-p_i-1$ 个灯笼。如果这样的 $j$ 存在，那么此时 $[1,i-1]$ 的所有灯笼都已经被照亮，有 $f_i=\max(f_i,i-1)$。位于 $[j+1,i-1]$ 的灯笼都可以选择朝右，我们可以找到 $\max\limits_{k=j+1}^{i-1}k+p_k$ 来更新 $f_i$，也就是 $f_i=\max(f_i,\max\limits_{k=j+1}^{i-1}k+p_k)$。由于所有 $f_i$ 具有单调性，因此可以二分找出 $j$。对于 $\max\limits_{k=j+1}^{i-1}k+p_k$ 的值的查询，则可以使用线段树或 ST 表。

对于输出方案，我们只需要在每次更新 $f_i$ 时记录最优决策点即可。具体实现可以参考代码。

时间复杂度 $O(n\log n)$。

## Code
```
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+10;
int a[N],f[N],g[N];
char ans[N];
struct trnode{int l,r,lc,rc,c;}tr[N*4];
int trlen=0;
void build_tree(int l,int r)
{
	int now=++trlen;
	tr[now]={l,r,-1,-1,0};
	if(l==r) tr[now].c=a[l]+l;
	else
	{
		int mid=(l+r)/2;
		tr[now].lc=trlen+1;build_tree(l,mid);
		tr[now].rc=trlen+1;build_tree(mid+1,r);
		tr[now].c=max(tr[tr[now].lc].c,tr[tr[now].rc].c);
	}
}
int query(int now,int l,int r)
{
	if(l>r) return 0;
	if(tr[now].l==l&&tr[now].r==r) return tr[now].c;
	int lc=tr[now].lc,rc=tr[now].rc,mid=(tr[now].l+tr[now].r)/2;
	if(l>=mid+1) return query(rc,l,r);
	else if(r<=mid) return query(lc,l,r);
	else return max(query(lc,l,mid),query(rc,mid+1,r));
}
int binary_search(int l,int r,int val)
{
	while(l<r)
	{
		int mid=(l+r)/2;
		if(f[mid]>=val) r=mid;
		else l=mid+1;
	}
	return r;
}
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		memset(f,0,sizeof(f));
		memset(g,-1,sizeof(g));
		int n;
		scanf("%d",&n);
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		trlen=0;
		build_tree(1,n);
		for(int i=1;i<=n;i++)
		{
			f[i]=f[i-1];
			if(f[i-1]>=i) f[i]=max(f[i],a[i]+i); 
			int j=binary_search(0,i,i-a[i]-1);
			if(j==i) continue;//找不到合法的j
			int t=query(1,j+1,i-1);
			if(f[i]<max(t,i-1)) f[i]=max(t,i-1),g[i]=j+1;
		}
		if(f[n]<n) puts("NO");
		else
		{
			puts("YES");
			for(int i=n;i>=1;i--)
			{
				if(g[i]==-1) ans[i]='R';
				else
				{
					for(int j=g[i];j<i;j++) ans[j]='R';
					ans[i]='L';
					i=g[i];
				}
			}
			for(int i=1;i<=n;i++) printf("%c",ans[i]);
			puts("");
		}
	}
	return 0;
}
```

---

## 作者：starrylasky (赞：1)

[体验更佳](https://www.cnblogs.com/lasky/articles/16916604.html)。

~~感觉很水的一道 3000.~~

定义 $f_i$ 表示前 $i$ 个灯能照亮区间 $[1,f_i]$ 的地方，显然这个 $f$ 是单调的。转移分两种情况：
* 若 $i$ 是 `L`，那么找到最小的 $x$ 使的 $f_x \geq i-a_i-1$，$f_i=\max(f_x,i-1,F(x+1,i-1))$，其中 $F(l,r)$ 表示区间 $[l,r]$ 能照到的右端点的最大值，这个搞一个 $\rm st $ 表。最小的是对的原因是因为 $l$ 越小，$F(l+1,i-1)$ 越大。

* 若 $i$ 是 `R`，那么找到最小的 $x$ 使得 $f_x \geq i$，$f_i=\max(F(x+1,i),f_x)$，最小的是对的原因同上。

如果以上两种情况都找不到怎么办，那么最终答案一定和 $i$ 的 `L,R` 无关，直接将 $from_i=i-1$ 就行了。

因为是单调的，所以上面的找最小随便二分一下就行了。发现对于以上两种情况区间 $[x+1,i-1]$ 都是 `R`，所以记一下 $from_i$ 表示是从哪里转移过来的，在记一下当前的 `L,R`，从 $n$ 开始每次跳到 $from_x$，将 $[from_x+1,x-1]$ 全都强制为 `R`。

~~完结撒花~~

---

## 作者：FLAMEs_ (赞：0)

女少口阿。

---

设 $f_i$ 表示前 $i$ 个灯笼最远能够覆盖到距离 $f_i$。每个灯由于只有两种状态（向左/向右），故可以分情况讨论。

- $i$ 朝右。此时转移方程可写成如下形式：

$f_i=\begin{cases}
f_{i-1}  & f_{i-1}< i \\
\text{max}(f_{i-1},i+p_i)  & f_{i-1}\ge i
\end{cases}$

转移显然成立，具体可以手推。

- $i$ 朝左。贪心的考虑最大转移。

这个时候，我们发现只需要让前 $i-p_i$ 位全部被覆盖即可。也就是说，如果一个位置 $j$ 满足 $f_j\ge i-p_i$，那么 $[j+1,i-1]$ 便可以全部向右。可以二分出第一个这样的 $j$。有转移：

$f_i=\text{max}_{k=j+1}^{i-1}k+p_k$

其中，$k+p_k$ 的含义即为位置 $k$ 上的灯向右照了 $p_k$ 格。

---

对于维护最大值，可以采用线段树等数据结构完成。

时间复杂度为 $\Theta(\text{n log n})$ 。

---

## 作者：Yansuan_HCl (赞：0)

往左点灯是从 $i$ 开始向左连续覆盖，于是只需要考虑最左边一个不亮的位置。设 $f(i)$ 表示确定了前 $i$ 个灯的朝向，最多能从 $1$ 开始点亮多少灯。点亮更多的灯一定不会让 $f$ 减少，于是 $f(i)$ 随 $i$ 单调不降。

考虑对 $i$ 的决策：

- 向右：
	- 此时要么 $i$ 不亮，$f(i) \gets f(i-1)$；
    - 要么 $i$ 被左侧的照亮：当 $f(i-1)\ge i$ 时，$f(i) \gets \max\{f(i),i+P_i\}$。
- 向左：
	- 在 $[i-P_i, i-1]$ 中的点不必担心自己的亮暗。
    - 考虑转移。当 $f(j) \ge i-P_i-1$ 时，$[i-P_i,i-1]$ 一段可以**保证是亮的**。所以，**不妨钦点 $[j+1,i-1]$ 所有的灯都向右点**，对答案产生向右的贡献，以避免向左重复照明浪费。
    - $f(i) \gets \max\{f(i),i-1,j+1+P_{j+1},j+2+P_{j+2},\ldots,i-1+P_{i-1}\}$。其中 $i-1$ 一项是防止 $i$ 本身不被照到。
    
于是转移成功地实现了。对于向左的第三种转移，可以二分最大合法的 $j$ 并用树状数组维护 $i+P_i$ 做到 $O(n\log n)$。

---

## 作者：Tyyyyyy (赞：0)

# CF1476F

定义 $dp_i$ 表示前 $i$ 盏灯笼最多能将 $[1,dp_i]$ 的区间全部照亮。

转移分情况讨论：

- 第 $i$ 盏灯笼向右照

	- 如果 $dp_{i-1}\geq i$，即前 $i-1$ 盏灯笼已经能将第 $i$ 盏照亮，则有 $dp_i=\max\{dp_{i-1},i+p_i\}$。

	- 否则，前 $i-1$ 盏灯笼不能将第 $i$ 盏照亮，则第 $i$ 盏灯笼只能由之后的灯笼照亮。此时有 $dp_i=dp_{i-1}$。
    
- 第 $i$ 盏灯笼向左照

	此时需要找到一个最小的 $j$ 满足 $dp_j\geq i-p_i-1$，即前 $j$ 盏灯笼照亮的区域与第 $i$ 盏灯笼照亮的区域完全覆盖了 $[1,i)$。那么 $[j+1,i-1]$ 部分的灯笼肯定向右照最优。此时有 $dp_i=\max(i-1,\displaystyle\max_{k\in[j+1,i-1]}\{k+p_k\})$。
    
上面的式子朴素转移是 $O(n^2)$ 的。用 st 表维护静态区间最值即可做到 $O(n\log n)$。

最后，如果 $dp_n\geq n$ 则说明有合法方案。输出方案时类似递推的过程递归回去即可。

Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+10;
int t,n,p[N];
int dp[N],st[N][20],logn[N];
char ans[N];
int query(int l,int r)
{
	if(l>r)return 0;
	int k=logn[r-l+1];
	return max(st[l][k],st[r-(1<<k)+1][k]);
}
void getans(int pos)
{
	if(!pos)return;
	if(dp[pos]==dp[pos-1]){ans[pos]='R',getans(pos-1);return;}
	if(dp[pos]==pos+p[pos]&&dp[pos-1]>=pos){getans(pos-1),ans[pos]='R';return;}
	int l=0,r=pos-1,mid,res;
	while(l<=r)
	{
		mid=(l+r)>>1;
		if(dp[mid]>=pos-p[pos]-1)res=mid,r=mid-1;
		else l=mid+1;
	}
	for(int i=res+1;i<pos;i++)ans[i]='R';
	ans[pos]='L',getans(res);
}
int main()
{
	for(int i=2;i<N;i++)logn[i]=logn[i>>1]+1;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)scanf("%d",&p[i]),st[i][0]=i+p[i];
		for(int j=1;j<=19;j++)
			for(int i=1;i+(1<<j)-1<=n;i++)
				st[i][j]=max(st[i][j-1],st[i+(1<<j-1)][j-1]);
		for(int i=1;i<=n;i++)
		{
			if(dp[i-1]>=i)dp[i]=max(dp[i-1],i+p[i]);
			else dp[i]=dp[i-1];
			int l=0,r=i-1,mid,res=-1;
			while(l<=r)
			{
				mid=(l+r)>>1;
				if(dp[mid]>=i-p[i]-1)res=mid,r=mid-1;
				else l=mid+1;
			}
			if(res!=-1)dp[i]=max(dp[i],max(i-1,query(res+1,i-1)));
		}
		if(dp[n]>=n)puts("YES");
		else{puts("NO");continue;}
		getans(n);
		for(int i=1;i<=n;i++)putchar(ans[i]);
		puts("");
	}
	return 0;
}
```

---

## 作者：FutaRimeWoawaSete (赞：0)

**sol of CF1476F**

观察，我们发现任意一段前缀灯笼被点亮对应着一段前缀灯笼对其的贡献。（但不一定是该前缀所有灯笼都会贡献）


所以我们设 $dp_i$ 表示 $1 \sim i$ 的灯笼最长贡献到哪个前缀。注意到的是该状态下没有断点的产生，是因为我们知道最后的状态可以表示成若干个将某个前缀完全覆盖的步骤，所以进行了这样的状态定义。

更具体地说，假设我们已知最后的方案从左往右依次加入照亮区间，保留的最长前缀是单调不减的。

然后后面就很简单了：

- 点 $i$ 向右照亮。如果 $dp_{i - 1} < i$ 那么直接令 $dp_i = dp_{i - 1}$，因为中间出现了断点而我们只保留最长前缀；否则 $dp_{i} = \max(dp_{i - 1},i + p_i)$。

- 点 $i$ 向左照亮，我们向前找到最靠左的一个位置 $t$ 使得 $dp_t \geq i - p_i - 1$，那么从 $t + 1 \sim i - 1$ 中间的所有数都应选择向右最大化当前的可行前缀，用 st 表维护该信息即可。

时间复杂度 $O(n \log n)$。

```cpp
/*
设 dp_i 表示 1 ~ i 能照亮的最长前缀。
因为任意一段被照亮的前缀一定可以表示成另一个前缀的照亮方案，而从 i 向 i - 1 的递推是符合了贪心的原则。 
*/
#include "bits/stdc++.h"
using namespace std;
const int Len = 3e5 + 5;
int n,m,dp[Len],p[Len],nxt[Len],md[Len],op[Len],st[25][Len],id[25][Len],lg[Len],cs[Len];
void init()
{
	for(int i = 2 ; i <= n + 1 ; i ++) lg[i] = lg[i >> 1] + 1;
	for(int i = 0 ; i <= n ; i ++) st[0][i] = i + p[i] , id[0][i] = i;
	for(int i = 1 ; i <= lg[n] ; i ++)
		for(int j = 0 ; j + (1 << i) - 1 <= n ; j ++) 
		{
			if(st[i - 1][j] > st[i - 1][j + (1 << (i - 1))]){id[i][j] = id[i - 1][j] , st[i][j] = st[i - 1][j];}
			else{st[i][j] = st[i - 1][j + (1 << (i - 1))] , id[i][j] = id[i - 1][j + (1 << (i - 1))];}
		}
}
int qmx,qid;
inline void Q(int l,int r)
{
	qmx = qid = 0;
	if(l > r) return;
	int k = lg[r - l + 1];
	if(st[k][l] > st[k][r - (1 << k) + 1]){qmx = st[k][l] , qid = id[k][l];}
	else{qmx = st[k][r - (1 << k) + 1] , qid = id[k][r - (1 << k) + 1];}
}
void Print(int x)
{
	if(x < 1) return;
	if(op[x] == 0) cs[x] = 0;
	else if(op[x] == 1) cs[x] = 1;
	else
	{
		for(int i = x ; i > md[x] ; i --) cs[i] = 0;
		cs[md[x]] = 1;
		for(int i = md[x] - 1 ; i > nxt[x] ; i --) cs[i] = 0;
	}
	Print(nxt[x]);
}
int main()
{
	int T;scanf("%d",&T);
	while(T --)
	{
		scanf("%d",&n);
		for(int i = 1 ; i <= n ; i ++) scanf("%d",&p[i]);
		dp[0] = 0;init();
		for(int i = 1 ; i <= n ; i ++)
		{
			int w = p[i] + i , ww = 0 , www = dp[i - 1];
			int l = 0 , r = i - 1 , ass = -1;
			while(l <= r)
			{
				int mid = (l + r) >> 1;
				if(dp[mid] >= i - p[i] - 1) ass = mid , r = mid - 1;
				else l = mid + 1;
			}
			if(ass == -1) ww = 0;
			else{Q(ass + 1 , i - 1);ww = max(i - 1 , qmx);}
			if(dp[i - 1] < i) w = 0;
			if(w == max(ww , max(w , www))) dp[i] = w , nxt[i] = i - 1 , op[i] = 1;
			else if(ww == max(ww , max(w , www))) dp[i] = ww , md[i] = qid , nxt[i] = ass , op[i] = 2;
			else if(www == max(ww , max(w , www))) dp[i] = dp[i - 1] , nxt[i] = i - 1 , op[i] = 0;
			//printf("%d %d %d %d %d %d\n",i,dp[i],ass,w,ww,www);
		}
		if(dp[n] >= n)
		{
			puts("YES");
			Print(n);
			for(int i = 1 ; i <= n ; i ++) putchar(cs[i] ? 'R' : 'L');
			puts("");
		}
		else puts("NO");
	}
	return 0;
}
```

---

## 作者：duyi (赞：0)

# CF1476F Lanterns

每个点 $i$ 对应了两个区间，我们只能选择其中一个去使用，要用选出的区间覆盖所有位置。

设 $\mathrm{dp}(i, t \in\{0, 1\})$ 表示是否存在一种选择方案，满足：

- 已经使用且仅使用了 $1\dots i$ 这些点对应的区间。
- 位置 $[1, i - 1]$ 均被覆盖。
- 位置 $[i + 1, n]$ 均没有被覆盖。
- 位置 $i$ 是否被覆盖（$t = 1$ 表示是，$t = 0$ 表示否）。

初始时 $\mathrm{dp}(0, 1) = 1$。

考虑转移。从一个已经确定的状态 $\mathrm{dp}(i, t) = 1$ 向后面的状态转移。以 $t = 1$ 为例：

因为 $i + 1$ 没有被覆盖，且点 $1\dots i$ 都已经被使用过了，所以 $i + 1$ 肯定是被 $i + 2\dots n$ 中的点覆盖的。设 $i + 2\dots n$ 中**第一个**覆盖了 $i + 1$ 的点为 $j$（$i + 2\leq j\leq n, j - p_j\leq i + 1$）。因为 $j$ 要覆盖 $i + 1$，所以 $j$ 一定是向左。所以 $[i + 1, j - 1]$ 都会被 $j$ 覆盖，并且它们向左是没有意义的，所以它们肯定都向右。

考虑定义一个函数 $\mathrm{jump}(l, r)$，他表示让 $l\dots r$ 里的所有点都向右，$r$ 后面被覆盖到的点也向右，以此类推，最远能覆盖到哪。具体代码如下：

```cpp
int jump(int l, int r) {
	while (1) {
		int mx = 0;
		for (int i = l; i <= r; ++i) {
			ckmax(mx, i + p[i]);
		}
		if (mx >= n)
			return n;
		if (mx == r)
			return r;
		l = r + 1;
		r = mx;
	}
}
```

现在已知 $i + 1\dots j - 1$ 里的点都向右，所以首先他们能覆盖到 $\max_{k = i + 1}^{j - 1}\{p_k + k\}$，设 $x = \max_{k = i + 1}^{j - 1}\{p_k + k\}$。

- 若 $x = j - 1$，那么可以转移到 $\mathrm{dp}(j, 0)$。
- 若 $x = j$，那么可以转移到 $\mathrm{dp}(j, 1)$。
- 若 $x > j$，那么可以转移到 $\mathrm{dp}(\mathrm{jump}(j + 1, x), 1)$。

$t = 0$ 时的转移也是类似的，读者可以自己讨论。

最终答案就是 $\mathrm{dp}(n, 1)$。

时间复杂度 $\mathcal{O}(n^3)$。这个暴力的代码我附在参考代码部分（没写输出方案）。

要输出方案也是比较简单的。记录每个状态是从哪个 $j$ 转移而来的。然后从最终状态 $\mathrm{dp}(n, 1)$ 开始往回找，一路把这些 $j$ 的答案都设为 $\texttt{L}$，其他位置的答案都是 $\texttt{R}$ 即可。

---

优化。以下还是只讨论 $t = 1$ 的转移，$t = 0$ 几乎是同理的，只有边界需要变化。

考虑不枚举 $i$，而是枚举转移点 $j$。那么所有 $j - p_j - 1\leq i\leq j - 2$ 且 $\mathrm{dp}(i, 1) = 1$ 的 $i$ 都可以通过 $j$ 来转移。

下面是一个重要的观察：我们只需要用合法的 $i$ 里**最小的**进行转移。即：只用这个最小的 $i$ 转移，和用所有可能的 $i$ 转移一次，效果是一样的。这是因为 $i$ 对转移的影响，只有 $x = \max_{k = i + 1}^{j - 1}\{p_k + k\}$ 这个式子。我们希望这个式子的值越大越好，所以取最小 $i$ 肯定是最优的。

于是可以把所有 $\mathrm{dp}(i, 1) = 1$ 的 $i$ 用 $\texttt{set}$ 存起来，枚举 $j$ 后，在 $\texttt{set}$ 里 $\texttt{lower_bound}$ 找出最小的 $i$。

时间复杂度 $\mathcal{O}(n^2)$。

---

现在复杂度的瓶颈主要有两个：

1. 求 $x = \max_{k = i + 1}^{j - 1}\{p_k + k\}$。
2. $\mathrm{jump}$ 函数。

第 1 个就是普通的 rmq 问题，可以用 st 表解决。

考虑 $\mathrm{jump}$ 函数。

定义：$f_i$，表示最大的 $j$（$1\leq j \leq i$），满足 $p_j + j > i$。特别地，如果不存在这样的 $j$，那么 $f_i = 0$。

结论：$\mathrm{jump}(l, r)$ 的结果，就等于**最小**的 $x$，满足 $x\geq r$ 且 $f_x < l$。特别地，如果不存在这样的 $x$，那么 $\mathrm{jump}(l, r) = n$。

如何理解？$f_i$ 的实际含义是： $l > f_i$ 时 $i$ 会被“堵死”，即 $\mathrm{jump}$ 函数里，跳到 $i$ 之后就不能再往后跳了。

有了这个结论，求 $f_i$ 和求 $\mathrm{jump}(l, r)$，都可以通过二分 + rmq，在 $\mathcal{O}(\log n)$ 时间内解决。

总时间复杂度 $\mathcal{O}(n\log n)$。

## 参考代码

$\mathcal{O}(n\log n)$ 做法：

实际提交时建议使用读入、输出优化，详见本博客公告。

```cpp
// problem: CF1476F
#include <bits/stdc++.h>
using namespace std;

#define mk make_pair
#define fi first
#define se second
#define SZ(x) ((int)(x).size())

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;

template<typename T> inline void ckmax(T& x, T y) { x = (y > x ? y : x); }
template<typename T> inline void ckmin(T& x, T y) { x = (y < x ? y : x); }

const int MAXN = 3e5, LOG = 18;
int n, p[MAXN + 5];
int arr[MAXN + 5];
int f[MAXN + 5];

bool dp[MAXN + 5][2]; // dp[i][0/1]: [1,i] 全部都用过了, [i+1,n] 都没用过, i 这个位置有没有被覆盖
pair<pii, int> frm[MAXN + 5][2];
set<int> s[2]; // dp 值为 true 的位置
char ans[MAXN + 5];

struct RangeMaxQuery {
	int _log2[MAXN + 5];
	pii st[MAXN + 5][LOG + 1];
	void build(int* a, int n) {
		_log2[0] = -1;
		for (int i = 1; i <= n; ++i) {
			_log2[i] = _log2[i >> 1] + 1;
			st[i][0] = mk(a[i], i);
		}
		for (int j = 1; j <= LOG; ++j) {
			for (int i = 1; i + (1 << (j - 1)) <= n; ++i) {
				st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]); // *****
			}
		}
	}
	pii rmq(int l, int r) {
		int k = _log2[r - l + 1];
		return max(st[l][k], st[r - (1 << k) + 1][k]); // *****
	}
	int rmq_val(int l, int r) { return rmq(l, r).fi; }
	int rmq_pos(int l, int r) { return rmq(l, r).se; }
	RangeMaxQuery() {}
} RMQ;
struct RangeMinQuery {
	int _log2[MAXN + 5];
	pii st[MAXN + 5][LOG + 1];
	void build(int* a, int n) {
		_log2[0] = -1;
		for (int i = 1; i <= n; ++i) {
			_log2[i] = _log2[i >> 1] + 1;
			st[i][0] = mk(a[i], i);
		}
		for (int j = 1; j <= LOG; ++j) {
			for (int i = 1; i + (1 << (j - 1)) <= n; ++i) {
				st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]); // *****
			}
		}
	}
	pii rmq(int l, int r) {
		int k = _log2[r - l + 1];
		return min(st[l][k], st[r - (1 << k) + 1][k]); // *****
	}
	int rmq_val(int l, int r) { return rmq(l, r).fi; }
	int rmq_pos(int l, int r) { return rmq(l, r).se; }
	RangeMinQuery() {}
} RMQf;


int jump(int l, int r) {
	/*
	while (1) {
		int mx = 0;
		for (int i = l; i <= r; ++i) {
			ckmax(mx, i + p[i]);
		}
		if (mx >= n)
			return n;
		if (mx == r)
			return r;
		l = r + 1;
		r = mx;
	}
	*/
	/*
	for (int i = r; i <= n; ++i) {
		if (f[i] < l) return i;
	}
	return n;
	*/
	int lo = r, hi = n;
	while (lo < hi) {
		int mid = (lo + hi) >> 1;
		if (RMQf.rmq_val(r, mid) < l) {
			hi = mid;
		} else {
			lo = mid + 1;
		}
	}
	return lo;
}

void get_ans(int i, int t) {
	if (i == 0)
		return;
	ans[frm[i][t].se] = 'L';
	get_ans(frm[i][t].fi.fi, frm[i][t].fi.se);
}

void solve_case() {
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> p[i];
		arr[i] = p[i] + i;
	}
	
	RMQ.build(arr, n);
	
	for (int i = 1; i <= n; ++i) {
		int l = 0, r = i;
		while (l < r) {
			int mid = (l + r + 1) >> 1;
			if (RMQ.rmq_val(mid, i) > i) {
				l = mid;
			} else {
				r = mid - 1;
			}
		}
		f[i] = l;
	}
	
	RMQf.build(f, n);
	
	for (int i = 0; i <= n; ++i) dp[i][0] = dp[i][1] = 0;
	s[0].clear();
	s[1].clear();
	
	dp[0][1] = 1;
	s[1].insert(0);
	for (int j = 2; j <= n; ++j) {
		set<int> :: iterator it = s[1].lower_bound(max(0, j - p[j] - 1));
		if (it != s[1].end() && *it <= j - 2) {
			int i = *it;
			int mx = RMQ.rmq_val(i + 1, j - 1);
			ckmin(mx, n);
			assert(mx >= j - 1);
			if (mx == j - 1) {
				dp[j][0] = 1;
				frm[j][0] = mk(mk(i, 1), j);
				s[0].insert(j);
			} else if (mx == j) {
				dp[j][1] = 1;
				frm[j][1] = mk(mk(i, 1), j);
				s[1].insert(j);
			} else {
				int to = jump(j + 1, mx);
				dp[to][1] = 1;
				frm[to][1] = mk(mk(i, 1), j);
				s[1].insert(to);
			}
		}
		
		it = s[0].lower_bound(max(0, j - p[j]));
		if (it != s[0].end() && *it <= j - 2) {
			int i = *it;
			int mx = RMQ.rmq_val(i + 1, j - 1);
			ckmin(mx, n);
			assert(mx >= j - 1);
			if (mx == j - 1) {
				dp[j][0] = 1;
				frm[j][0] = mk(mk(i, 0), j);
				s[0].insert(j);
			} else if (mx == j) {
				dp[j][1] = 1;
				frm[j][1] = mk(mk(i, 0), j);
				s[1].insert(j);
			} else {
				int to = jump(j + 1, mx);
				dp[to][1] = 1;
				frm[to][1] = mk(mk(i, 0), j);
				s[1].insert(to);
			}
		}
		if (dp[j - 1][0] && p[j] >= 1) {
			dp[j][0] = 1;
			frm[j][0] = mk(mk(j - 1, 0), j);
			s[0].insert(j);
		}
	}
	if (!dp[n][1]) {
		cout << "NO" << endl;
		return;
	}
	cout << "YES" << endl;
	for (int i = 1; i <= n; ++i)
		ans[i] = 'R';
	get_ans(n, 1);
	for (int i = 1; i <= n; ++i)
		cout << ans[i];
	cout << endl;
}
int main() {
	int T; cin >> T; while (T--) {
		solve_case();
	}
	return 0;
}
```

---

$\mathcal{O}(n^3)$ 暴力（没有输出方案）：

```cpp
// problem: CF1476F
// O(n^3)暴力, 没有输出方案
#include <bits/stdc++.h>
using namespace std;

#define mk make_pair
#define fi first
#define se second
#define SZ(x) ((int)(x).size())

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;

template<typename T> inline void ckmax(T& x, T y) { x = (y > x ? y : x); }
template<typename T> inline void ckmin(T& x, T y) { x = (y < x ? y : x); }

const int MAXN = 3e5;
int n, p[MAXN + 5];
bool dp[MAXN + 5][2]; // dp[i][0/1]: [1,i] 全部都用过了, [i+1,n] 都没用过, i 这个位置有没有被覆盖
int jump(int l, int r) {
	while (1) {
		int mx = 0;
		for (int i = l; i <= r; ++i) {
			ckmax(mx, i + p[i]);
		}
		if (mx >= n)
			return n;
		if (mx == r)
			return r;
		l = r + 1;
		r = mx;
	}
}
void solve_case() {
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> p[i];
	}
	for (int i = 0; i <= n; ++i) dp[i][0] = dp[i][1] = 0;
	dp[0][1] = 1;
	for (int i = 0; i < n; ++i) {
		if (dp[i][1]) {
			for (int j = i + 2; j <= n; ++j) {
				if (j - p[j] <= i + 1) {
					int mx = 0;
					for (int k = i + 1; k < j; ++k) {
						ckmax(mx, k + p[k]);
					}
					ckmin(mx, n);
					assert(mx >= j - 1);
					if (mx == j - 1) {
						dp[j][0] = 1;
					} else if (mx == j) {
						dp[j][1] = 1;
					} else {
						dp[jump(j + 1, mx)][1] = 1;
					}
				}
			}
		}
		if (dp[i][0]) {
			for (int j = i + 1; j <= n; ++j) {
				if (j - p[j] <= i) {
					if (j == i + 1) {
						dp[i + 1][0] = 1;
						continue;
					}
					
					int mx = 0;
					for (int k = i + 1; k < j; ++k) {
						ckmax(mx, k + p[k]);
					}
					ckmin(mx, n);
					assert(mx >= j - 1);
					if (mx == j - 1) {
						dp[j][0] = 1;
					} else if (mx == j) {
						dp[j][1] = 1;
					} else {
						dp[jump(j + 1, mx)][1] = 1;
					}
				}
			}
		}
	}
	if (dp[n][1]) {
		cout << "YES" << endl;
	} else {
		cout << "NO" << endl;
	}
}
int main() {
	int T; cin >> T; while (T--) {
		solve_case();
	}
	return 0;
}
```



---

