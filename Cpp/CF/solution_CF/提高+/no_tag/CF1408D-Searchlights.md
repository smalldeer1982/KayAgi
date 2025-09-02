# Searchlights

## 题目描述

There are $ n $ robbers at coordinates $ (a_1, b_1) $ , $ (a_2, b_2) $ , ..., $ (a_n, b_n) $ and $ m $ searchlight at coordinates $ (c_1, d_1) $ , $ (c_2, d_2) $ , ..., $ (c_m, d_m) $ .

In one move you can move each robber to the right (increase $ a_i $ of each robber by one) or move each robber up (increase $ b_i $ of each robber by one). Note that you should either increase all $ a_i $ or all $ b_i $ , you can't increase $ a_i $ for some points and $ b_i $ for some other points.

Searchlight $ j $ can see a robber $ i $ if $ a_i \leq c_j $ and $ b_i \leq d_j $ .

A configuration of robbers is safe if no searchlight can see a robber (i.e. if there is no pair $ i,j $ such that searchlight $ j $ can see a robber $ i $ ).

What is the minimum number of moves you need to perform to reach a safe configuration?

## 说明/提示

In the first test, you can move each robber to the right three times. After that there will be one robber in the coordinates $ (3, 0) $ .

The configuration of the robbers is safe, because the only searchlight can't see the robber, because it is in the coordinates $ (2, 3) $ and $ 3 > 2 $ .

In the second test, you can move each robber to the right two times and two times up. After that robbers will be in the coordinates $ (3, 8) $ , $ (8, 3) $ .

It's easy the see that the configuration of the robbers is safe.

It can be proved that you can't reach a safe configuration using no more than $ 3 $ moves.

## 样例 #1

### 输入

```
1 1
0 0
2 3```

### 输出

```
3```

## 样例 #2

### 输入

```
2 3
1 6
6 1
10 1
1 10
7 7```

### 输出

```
4```

## 样例 #3

### 输入

```
1 2
0 0
0 0
0 0```

### 输出

```
1```

## 样例 #4

### 输入

```
7 3
0 8
3 8
2 7
0 10
5 5
7 0
3 5
6 6
3 11
11 5```

### 输出

```
6```

# 题解

## 作者：HPXXZYY (赞：14)

$\color{blue}{\texttt{[Solution]}}$

~~（自己画的图有点丑陋，请原谅）~~

显然，对于两个探照灯 $(i,j)$，如果 $i$ 在 $j$ 的探照范围内，则 $i$ 是没有用的，可以删去。

于是剩下的有用的探照灯会按照横坐标递增，纵坐标递减的方式存在与坐标轴中，如下图所示：

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210403133315425.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1pIVVlJTkdZRV8xMjM0NTY=,size_16,color_FFFFFF,t_70)


对于任意一个海盗 $i$，可以有以下 $3$ 种方法摆脱**所有**探照灯的监视：

1. 一直向上走，直到纵坐标比所有探照灯的纵坐标都大
2. 一直向右走，直到横坐标比所有探照灯的横坐标都大
3. 向上走一段路后，再向右走一会儿，如下图中的点 $\texttt{G}$ 的移动方式：
  ![在这里插入图片描述](https://img-blog.csdnimg.cn/20210403133535888.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1pIVVlJTkdZRV8xMjM0NTY=,size_16,color_FFFFFF,t_70)

当然了，如果已经摆脱了探照灯的控制，那么接下来再动也无所谓了。

最复杂的是第 $3$ 种方法，但是我们可以知道，最优秀的方案应该是走到和某个探照灯等高（即纵坐标相等）时，不停地向右走，直到横坐标大于该探照灯。而全局最优方案下至少有一个点满足这个方案（除非最优解是第 $1,2$ 种方案）。

所以我们开一个数组 $f_{x}$ 表示所有的海盗先统一向上走了 $x$ 步后，最少需要向右走几步。最后的答案就是 $\max \{ i+f_{i} \}$。

考虑到 $n,m \leq 2000$，所以我们可以用一个 $O(nm)$ 的枚举来求出 $f_{x}$。

最后记得是倒序更新答案。

$\color{blue}{\texttt{[code]}}$

```cpp
const int N=2e3+100;
const int M=1e6+100;
int ans,n,m,f[M],limit;
int a[N],b[N],c[N],d[N];
inline void ckmax(int &a,int b){
	a=a<b?b:a;//让 a 取到 a,b 间较大值 
}
inline void ckmin(int &a,int b){
	a=a>b?b:a;//让 a 取到 a,b 间较小值 
}
int main(){
	freopen("t1.in","r",stdin);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&a[i],&b[i]);
	for(int i=1;i<=m;i++)
		scanf("%d%d",&c[i],&d[i]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			if (d[j]<b[i]) continue;
			ckmax(limit,d[j]-b[i]);
			ckmax(f[d[j]-b[i]],c[j]-a[i]+1);
		}
	ans=limit+1;//只向右边走,走出边界 
	for(int i=limit,maxn=0;i>=0;i--){
		ckmax(maxn,f[i]);ckmin(ans,i+maxn);
	}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：tommymio (赞：8)

观察题目，我们发现，对于一个确定的劫匪 $i$ 和确定的探照灯 $j$，我们只会选择：

- 向上走 $d_j-b_i+1$ 步。
- 向右走 $c_j-a_i+1$ 步。
- 先向上走 $d_j-b_i$ 步，再向右走 $c_j-a_i$ 步，最后向上 $/$ 向右走一步。
- 或者走了多于上述方案的步数，但走出了范围。

为什么存在第 $4$ 种走法呢？因为对劫匪的移动是一次整体移动，可能存在某些劫匪多走了步数的情况。

这就启迪我们枚举其中向上走的步数 $x$，对于每个 $x$ 求出最少需要向右走能够 $\text{reach a safe configuration}$ 的步数，不妨将这个步数记作 $f_x$。答案就为 $\min\limits_{0 \leq L\leq lim+1}\{\max_{L\leq i\leq lim+1} f_i+L\}$，其中 $lim$ 为最大的需向上走的步数。为什么后缀最大值就可以了呢？因为在更新 $f_x$ 的时候我们只会用从 $a_i$ 向上走 $x$ 步恰好达到 $c_j$ 的劫匪 $i$ 和探照灯 $j$ 来更新。

时间复杂度为 $O(nm+\max\{d_i-b_i\})$，可以通过本题。

```cpp
#include<cstdio>
int a[2005],b[2005],c[2005],d[2005],f[1000005];
inline int read() {
	register int x=0,f=1;register char s=getchar();
	while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
	while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
	return x*f;
}
inline int min(const int &x,const int &y) {return x<y? x:y;}
inline int max(const int &x,const int &y) {return x>y? x:y;}
int main() {
	int n=read(),m=read(),lim=0;
	for(register int i=1;i<=n;++i) {a[i]=read();b[i]=read();}
	for(register int i=1;i<=m;++i) {c[i]=read();d[i]=read();}
	for(register int i=1;i<=n;++i) {
		for(register int j=1;j<=m;++j) {
			if(d[j]<b[i]) continue;
			lim=max(lim,d[j]-b[i]);
			f[d[j]-b[i]]=max(f[d[j]-b[i]],c[j]-a[i]+1);
		}
	}
	int mx=0,ans=lim+1;
	for(register int i=lim;i>=0;--i) {mx=max(mx,f[i]); ans=min(ans,i+mx);}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：RedLycoris (赞：4)

考虑dp。

令 $f_i$ 表示向左移动 $i$ 格时，向上移动的最小格数。

对于数据预处理完后，倒着去一边取 $max$ 即可。（因为它要大于它后面所有的）

```cpp
#include<bits/stdc++.h>
#define ll long long
#define reg register
#define mp make_pair
#define ri register int
#define ld long double
using namespace std;
const int mxn=1e6+6;
int n,m;
int a[mxn],b[mxn],c[mxn],d[mxn];
int l[mxn],u[mxn];
inline void solve(){
	cin>>n>>m;
	for(int i=1;i<=n;++i)cin>>a[i]>>b[i];
	for(int i=1;i<=m;++i)cin>>c[i]>>d[i];
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			if(c[j]>=a[i] and d[j]>=b[i]){//预
				l[c[j]-a[i]]=max(l[c[j]-a[i]],d[j]-b[i]+1);
			}
		}
	}
	for(int i=1000001;~i;--i)l[i]=max(l[i],l[i+1]);//总
	int ans=100000001;
	for(int i=0;i<=1000001;++i)ans=min(ans,i+l[i]);//比较
	cout<<ans<<'\n';
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int T=1;//cin>>T;
	for(;T--;)solve();
}
```

---

## 作者：s_r_f (赞：3)

记坐标整体右移的距离为 $X$ , 整体上移的距离为 $Y$ .

枚举每一对点 $(a,b)$ $(c,d)$ , 它给答案的贡献就是对于一段 $X$ 的前缀 , $Y$ 必须 $\geq$ 一个值的限制。 

对限制做个后缀 $max$ 即可。

$\Theta(nm+max(a_i,b_i,c_i,d_i))$

code :
```cpp
#include <bits/stdc++.h>
using namespace std;
template <typename T> void read(T &x){
	static char ch; x = 0,ch = getchar();
	while (!isdigit(ch)) ch = getchar();
	while (isdigit(ch)) x = x * 10 + ch - '0',ch = getchar();
}
inline void write(int x){if (x > 9) write(x/10); putchar(x%10+'0'); }
const int N = 2005,M = 2005;
int n,m,ax[N],ay[N],bx[M],by[M],ans = 2000000,mx[1000005];
int main(){
	int i,j;
	read(n),read(m);
	for (i = 1; i <= n; ++i) read(ax[i]),read(ay[i]);
	for (i = 1; i <= m; ++i) read(bx[i]),read(by[i]);
	for (i = 1; i <= n; ++i)
	for (j = 1; j <= m; ++j) if (ax[i] <= bx[j] && ay[i] <= by[j])
		mx[bx[j]-ax[i]] = max(mx[bx[j]-ax[i]],by[j]-ay[i]+1);
	for (i = 1000000; i ; --i) mx[i-1] = max(mx[i-1],mx[i]);
	for (i = 0; i <= 1000000; ++i) ans = min(ans,i+mx[i]);
	cout << ans << '\n';
	return 0;
}
```

---

## 作者：7KByte (赞：3)

不需要任何高级的算法，我们只用优化枚举即可。

对于每个劫匪，预处理出当它向右移动$x$个位置后，还需要向上移动多少个位置。

我们暴力枚举每个劫匪和探照灯。

然后用每个向右的移动距离加上对应向上的移动距离更新答案。

时间复杂度$\rm O(NM+max\{c\})$

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 2000005
using namespace std;
int n,m;
struct node{
	int x,y;
}a[N],b[N];
vector<int>c[N];
void solve(){
	scanf("%d%d",&n,&m);
	rep(i,1,n)scanf("%d%d",&a[i].x,&a[i].y);
	rep(i,1,m)scanf("%d%d",&b[i].x,&b[i].y);
	int mx=0;
	rep(i,1,n)rep(j,1,m){
		mx=max(mx,b[j].x-a[i].x);
		if(b[j].x>=a[i].x)c[b[j].x-a[i].x].push_back(b[j].y-a[i].y+1);
	}
	int ans=0x7fffffff,now=0;
	pre(k,mx+1,0){
		for(int i=0;i<(int)c[k].size();i++)now=max(now,c[k][i]);
		ans=min(ans,now+k);
	}
	printf("%d\n",ans);
}
int main(){
	solve();
	return 0;
} 
```

---

## 作者：RockyYue (赞：1)

### 1408D

$n$ 个人 $m$ 盏灯，人 $i$ 坐标 $(a_i,b_i)$，灯 $i$ 为 $(c_i,d_i)$，坐标非负，每次操作可以将所有人右移或上移 $1$，求最少的操作次数使得不存在灯在人右上（非严格，即 $a_i\le c_j$ 且 $b_i\le d_j$）的情况，要求 $O(nm+V)$，$V$ 为坐标值域。

### Sol

- 这种题，对每一对限制分别考虑：若如题中 $(i,j)$ 不满足限制，需要向上走 $c_j-a_i+1$ 或向右走 $d_j-b_i+1$，对全局这两个要求必满足一个。
- 这个或很难考虑，不妨改变形式：向上走步数 $\le c_j-a_i$ 时则向右走至少 $d_j-b_i+1$，于是记录 $f_i$ 为向上走恰 $i$ 步时向右至少要走多少步，答案为 $\min_{i=0}^{V}\{i+f_i\}$。
- 于是上述要求表现在 $f$ 中，即 $f_{0\dots c_j-a_i}\stackrel{\max}\longleftarrow d_j-b_i+1$，可以只更新 $c_j-a_i$ 位，得到 $f'$，最终更新 $f_i=\max_{j=0}^{i}\{f'_i\}$。

---

## 作者：Lily_White (赞：1)

要让一个人是安全的，那么对于任意 $(i, j)$，下面的两个条件，至少要满足一个：
$$
\begin{cases}
x+a_i>c_j\\
y+b_i>d_j
\end{cases}
$$

如果我们把一个人移动到 $(x, y)$ 这个位置上，且 $x \le c_j - a_i$，也就是这个人能够横着被看到，那么我们就不能让他被竖着看到，所以，$y_i \ge d_j - b_i + 1$。

这样，我们就能预处理所有 $x$ 对应的最小 $y$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 2020, R = 1e6 + 10;
int a[N], b[N], c[N], d[N], n, m;
int r[R];
void chmax(int &x, int y) { x = max(x, y); }
void chmin(int &x, int y) { x = min(x, y); }
int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) cin >> a[i] >> b[i];
  for (int i = 1; i <= m; i++) cin >> c[i] >> d[i];
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      if (c[j] >= a[i] && d[j] >= b[i]) {
        chmax(r[c[j] - a[i]], d[j] - b[i] + 1);
      }
  int ans = 0x3f3f3f3f;
  for (int i = 1000001; i >= 0; i--) chmax(r[i], r[i + 1]);
  for (int i = 0; i <= 1000001; i++) chmin(ans, i + r[i]);
  cout << ans << endl;
  return 0;
}
```

---

## 作者：F_Mu (赞：1)

**题意**

在二维平面有$n$个海盗，$m$个探照灯，你有两种操作

+ 将所有海盗往上走一步
+ 将所有海盗往右走一步

设海盗为$(a_i,b_i)$，探照灯为$(c_j,d_j)$，当且仅当$a_i\leq c_j$且$b_i\leq d_j$时，海盗在探照灯范围内，问最少多少次操作可以将所有海盗移动到所有探照灯范围外

**分析**

将题意抽象一下，找到一个二元组$(x,y)$，$x$表示向上走的步数，$y$表示向右走的步数，然后对于任何海盗$(a_i,b_i)$，都满足加上$(x,y)$后，对于任何探照灯$(c_j,d_j)$要么$a_i+x>c_j$，要么$b_i+y>d_j$，且$x+y$最小

那么我们$O(nm)$处理，找到海盗和探照灯之间的关系，若海盗在探照灯范围内，得到二元组$(x,y)$，有$a_i+x>c_j$且$b_i+y>d_j$，得到所有二元组后，按照第一维排序

此时发现，遍历二元组，遍历到第$i$个二元组时，如果取该二元组的$x$，那么$y$最小即为剩余二元组的最大值，这样可以满足前部分探照灯向上走即可脱离，剩余探照灯向右走即可脱离，注意答案初始值是只往右走时的答案

```cpp
#pragma GCC optimize(3, "Ofast", "inline")

#include <bits/stdc++.h>

#define start ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define ll long long
#define int ll
#define ls st<<1
#define rs st<<1|1
#define pii pair<int,int>
#define rep(z, x, y) for(int z=x;z<=y;++z)
#define repd(z, x, y) for(int z=x;z>=y;--z)
#define com bool operator<(const node &b)const
using namespace std;
mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());
const int maxn = (ll) 3e5 + 5;
const int mod = 998244353;
const int inf = 0x3f3f3f3f;
int T = 1;
pii a[2005], b[2005];
int maxx[2005 * 2005];

void solve() {
    int n, m;
    cin >> n >> m;
    rep(i, 1, n)cin >> a[i].first >> a[i].second;
    rep(i, 1, m)cin >> b[i].first >> b[i].second;
    vector<pii > v;
    rep(i, 1, n) {
        rep(j, 1, m) {
            if (b[j].first < a[i].first || b[j].second < a[i].second)
                continue;
            v.push_back({max(b[j].first + 1 - a[i].first, 0ll), max(0ll, b[j].second + 1 - a[i].second)});
        }
    }
    if (v.empty()) {
        cout << 0;
        return;
    }
    sort(v.begin(), v.end());
    for (int i = v.size() - 1; i >= 0; --i)maxx[i] = max(maxx[i + 1], v[i].second);
    int ans = maxx[0];
    for (int i = 0; i < v.size(); ++i)ans = min(ans, v[i].first + maxx[i + 1]);
    cout << ans;
}


signed main() {
    start;
    while (T--)
        solve();
    return 0;
}
```


---

## 作者：ql12345 (赞：1)

# 瞎搞+单调栈

看这题在CF真是什么标签都有。。。

### [题面](https://codeforces.com/problemset/problem/1408/D)

### Solution：

- 首先明确一点：

	对于一个确定的向上和向右步数，不管怎么排列走的方案，都是等价的，所以只需要令终态合法即可

- **先O(nm)扫出每个海盗对每个能找到他的探照灯需要向右多少步和向上多少步（当做这个海盗的两个限制）**

	一个合法的策略即满足：
    
    对于每一个海盗，他的两个限制至少满足一个
    
- 考虑将这个问题变得更直观一点：将两个限制分别作为横纵坐标，将每个海盗表示为坐标系中的一个点

	于是有了以下一个图：
    
```
|
|   ·1
|
|    ·2
|
|     ·4  ·5        ·6
| ·3           ·7      ·8
|________________________
```

问题转化为：在坐标系中找到一个点，满足：这个点右边（横坐标严格大于）的点都不比他高

- 最符合我们第一反应的，显然是如果一个点横纵坐标都小于等于一个点，那这个点是没用的

	如：3的横纵坐标都小于2，所以这个点没用，具体而言：如果2符合了条件，3一定符合，那我们就把3删去
    
    **实现上，在之前找出所有点的时候，用一个桶，只记录每个涉及到的横坐标处最高的点，然后扫描横坐标的值域（1~1000000），用单调栈维护一个数值递减的纵坐标**
    
    删完之后，我们得到这个图：
    
```
|
|   ·1
|
|    ·2
|
|                   ·6
|                      ·8
|________________________
```

形状上类似凸包，但实际上不是，可以看到6，可以说是相对2->8“凹”进去了，但在本题中，他仍有贡献

- 最后一步了，**因为不是凸包，所以我们要得到最终的这个点只能暴力扫描一遍（实际上复杂度一点也不高）**

	**如何扫描？对一个点，他的贡献即为“他左边一个点的横坐标加上他的纵坐标”和“他右边一个点的纵坐标加上他的横坐标”**
    
    ~~笔者在写到这里的时候秃然发现似乎重复了？但反正不会让答案错误 /kk~~
    
    为什么价值是这个？
    
    看图：
    
```
|
|   ·1
|   
|----·2
|    |
|    |               ·6
|    |                  ·8
|____|__________________
```

当一个点的纵坐标确定为2的纵坐标之后，显然对于2及后面的点已经满足了，而对于2前面的点，需要满足他们的横坐标，2的上一个点的横坐标是最好的选择

另一边同理

- #### 致歉：一些因为笔者菜才出现的东西：

	1. 最明显的：笔者不会往题解里放图，用的符号，带来诸多不便
    
    2. 笔者在CF爆了几次，就把一些数组和循环开到了远远不需要的大小（读者可自行修改，不必在评论指出）
    
    3. 笔者还将minn赋了一个初值，它的含义为：如果选第一个点，只需满足纵坐标，横坐标大可为0，如果选择最后一个点，同理

### 实现：

有关代码的，都已经在上文加粗标注出来了，读者应该可以得到一个比较完整且清晰的代码流程，具体的话没什么细节，也都是板子

### Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[2020],b[2020],c[2020],d[2020];
int tot,bin[2000010],stk[2000010],top;
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;++i)cin>>a[i]>>b[i];
	for(int i=1;i<=m;++i)cin>>c[i]>>d[i];
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			if(c[j]-a[i]>=0&&d[j]-b[i]>=0)
				bin[c[j]-a[i]+1]=max(bin[c[j]-a[i]+1],d[j]-b[i]+1);
	for(int i=0;i<=2000001;++i){
		if(!bin[i])continue;
		while(bin[i]>=bin[stk[top]]&&top)--top;
		stk[++top]=i;
	}
	if(!top)return puts("0");
	int minn=min(stk[top],bin[stk[1]]);
	for(int i=1;i<=top;++i)
		if(bin[stk[i]])minn=min(minn,min(bin[stk[i]]+stk[i-1],bin[stk[i+1]]+stk[i]));
	cout<<minn;
	return 0;
}
```


---

## 作者：钓鱼王子 (赞：0)

比较妙的一道题~~~

首先一个感觉很对的思路：

枚举向右走几步，再二分需要向上走几步 $O(nm\times 10^6\log 10^6)$ 不是很多。

考虑到一个关键点：对于一个人和灯的组合 $(i,j)$，在向右 $\max(0,x_j-x_i) $ 之前，需要向上 $\max(0,y_j-y_i)$ 步，之后就不需要了。

也就是说，花费中间只会变化一次。

把变化点存起来，按照 $x$ 之差顺序从大到小排序，就可以直接计算了！

记得多插入一个 $0$，否则会出现 Wa on $7,8,10$ 等其他情况。

```cpp
#include<bits/stdc++.h>
#define re register
using namespace std;
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
}
int n,m,a[2002],b[2002],c[2002],d[2002],mx,ans,cnt,ss,mxx;
struct node{
	int x,y;
	bool operator<(const node &a)const{
		return x==a.x?y<a.y:x>a.x;
	}
}p[4000002];
int main(){
	n=read(),m=read();
	for(re int i=1;i<=n;++i)a[i]=read(),b[i]=read();
	for(re int i=1;i<=m;++i)c[i]=read(),d[i]=read();
	for(re int i=1;i<=n;++i)for(re int j=1;j<=m;++j){if(c[j]>=a[i]&&d[j]>=b[i])p[++cnt]=(node){c[j]-a[i]+1,d[j]-b[i]+1};
	if(d[j]>=b[i])mxx=max(mxx,d[j]-b[i]+1);
	}p[++cnt]=(node){0,mxx};
	sort(p+1,p+cnt+1);ans=1e9;
	for(re int i=1;i<=cnt;++i)ans=min(ans,mx+p[i].x),mx=max(mx,p[i].y);
	printf("%d",ans);
}
```


---

## 作者：Little09 (赞：0)

根据题意，对于每个强盗和每盏灯的关系，我们列出 $n*m$ 个条件，第 $i$ 个条件是满足 $x>a_i$ 或 $y>b_i$。我们列出所有条件，按 $a_i$ 排个序，枚举一下可以满足哪几个条件，然后更新答案就可以了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,ans=2100000000; 
struct point
{
	int x,y;
}q[4200001],a[2001],b[2001];
bool cmp(point x,point y)
{
	return x.x>y.x;
}
int main()
{
	cin >> n >> m;
	for (int i=1;i<=n;i++)
	{
		cin >> a[i].x >> a[i].y;
	}
	for (int i=1;i<=m;i++)
	{
		cin >> b[i].x >> b[i].y;
	}
	int cnt=0;
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=m;j++)
		{
			point u;
			if (a[i].x>b[j].x) continue;
			u.x=b[j].x-a[i].x+1;
			if (a[i].y>b[j].y) continue;
			u.y=b[j].y-a[i].y+1;
			q[++cnt]=u;
		}
	}
	sort(q+1,q+cnt+1,cmp);
	int maxy=0;
	for (int i=1;i<=cnt;i++)
	{
		ans=min(ans,q[i].x+maxy);
		maxy=max(maxy,q[i].y);
	}
	ans=min(ans,maxy);
	cout << ans;
	return 0;
}
```


---

## 作者：Isshiki_Hugh (赞：0)

dp思想，用数组的下标来维护其中一个维度的权值。

$dp[i][j]$表示向右移动$i$步的时候至少还需要向上移动$j$步，只需要在最后统计最小值就行了

转移方程：`dp[ no.x-now.x ] = std::max(dp[ no.x-now.x ] , no.y - now.y + 1);`

```cpp
//头文件略
const int N = 1e6+9;
const int inf = 1e9+9;
const double eps = 1e-7;
int _,n,m,a[2*N],cnt,cntt,dp[2*N],ans,tmp,lim;

struct node{
    int x,y;
}rob[2*N],lig[2*N],q[2*N],safe[2*N];
inline bool cmp(node x,node y){return x.x < y.x;}

int main(){
    std::ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    #ifdef LOCAL //use "g++ xxx.cpp -DLOCAL"
        freopen("in.in", "r", stdin);
    #endif
    cin >> n >> m;
    rep(i,1,n) cin >> rob[i].x >> rob[i].y;
    rep(i,1,m) cin >> lig[i].x >> lig[i].y;
    rep(i,1,std::max(n,m)) lim = std::max({lim,rob[i].x,rob[i].y,lig[i].x,lig[i].y});
    rep(i,1,m){
        node no = lig[i];
        rep(j,1,n){
            node now = rob[j];
            if(no.x >= now.x && no.y >= now.y)
            dp[ no.x-now.x ] = std::max(dp[ no.x-now.x ] , no.y - now.y + 1);
        }
    }
    ans = inf , tmp = 0;
    per(i,lim,0){
        tmp = std::max(tmp,dp[i]);
        ans = std::min(tmp+i,ans);
        // cout << tmp << " " << i << "\n";
    }
    cout << ans << "\n";
    return 0;
}

```

---

