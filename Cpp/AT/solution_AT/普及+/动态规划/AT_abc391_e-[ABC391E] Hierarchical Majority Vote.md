# [ABC391E] Hierarchical Majority Vote

## 题目描述

对于一个长度为 $3^n$ 的 01 字符串 $B = B_1B_2\dots B_{3^n}$，定义一种操作获得长度为 $3^{n-1}$ 的 01 字符串 $C = C_1C_2\dots C_{3^{n-1}}$：

+ 对于 $i = 1,2,\dots,3^{n-1}$，令 $C_i$ 为 $B_{3i}$、$B_{3i-1}$、$B_{3i-2}$ 中出现次数最多的字符。

现给定一个长度为 $3^N$ 的 01 字符串 $A = A_1A_2\dots A_{3^N}$。设 $A'=A'_1$ 是通过 $N$ 次上述操作后得到的长度为 $1$ 的字符串。

请求出最少改变 $A$ 中多少个元素（$0$ 变 $1$，$1$ 变 $0$），以改变 $A'_1$ 。

## 说明/提示

$1 \le N \le 13$，$A$ 为长度为 $3^N$ 的 01 字符串。

## 样例 #1

### 输入

```
2
010011101```

### 输出

```
1```

## 样例 #2

### 输入

```
1
000```

### 输出

```
2```

# 题解

## 作者：gesong (赞：10)

题目传送门：[[ABC391E] Hierarchical Majority Vote](https://www.luogu.com.cn/problem/AT_abc391_e)。
# 思路
考虑使用类似动态规划的思想，我们对于每一个结点都维护两个信息：
1. 当前结点的字符。
2. 若要修改的最小操作代价。
![](https://cdn.luogu.com.cn/upload/image_hosting/zqyssnot.png)

如图，其中黑色即为信息 $1$，红色即为信息 $2$。

按照上图方法，我们假设三个儿子的信息 $1$ 与信息 $2$ 的值为 $x_1,x_2,y_1,y_2,z_1,z_2$，当前结点的信息 $1$ 与信息 $2$ 的值为 $a_1,a_2$，按照下面的情况讨论：

- 若这三个结点中 $0$ 的个数为 $3$，显然 $a_1=0$，由于我们需要改变 $a_1$ 我们就需要将三个儿子中两个 $0$ 都修改，于是 $a_2$ 的值即为 $x_2,y_2,z_2$ 中前两小的和。
- 若这三个结点中 $1$ 的个数为 $3$，显然 $a_1=1$，由于我们需要改变 $a_1$ 我们就需要将三个儿子中两个 $1$ 都修改，于是 $a_2$ 的值即为 $x_2,y_2,z_2$ 中前两小的和。
- 若这三个结点中 $0$ 的个数为 $2$，显然 $a_1=0$，由于我们需要改变 $a_1$ 我们就需要将三个儿子中的其中一个 $0$ 更改，于是 $a_2$ 的值即为 $x_2,y_2,z_2$ 中对应的信息 $1$ 为 $0$ 的较小者。
- 若这三个结点中 $1$ 的个数为 $2$，显然 $a_1=1$，由于我们需要改变 $a_1$ 我们就需要将三个儿子中的其中一个 $1$ 更改，于是 $a_2$ 的值即为 $x_2,y_2,z_2$ 中对应的信息 $1$ 为 $1$ 的较小者。

最后按照上述方法 dfs 即可，具体实现可以参考代码。
# 代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
using namespace std;
const int N=3e6+10;
int a[N],n,f[N];
inline int read(){
	char c=getchar();
	int f=1,ans=0;
	while(c<48||c>57) f=(c==45?f=-1:1),c=getchar();
	while(c>=48&&c<=57) ans=(ans<<1)+(ans<<3)+(c^48),c=getchar();
	return ans*f;
}
inline int qpow(int a,int b){
	int s=1;
	while(b){
		if (b&1) s*=a;
		a*=a;
		b>>=1;
	}
	return s;
}
pii dfs(int l,int r){
	if (l==r) return {a[l],1};//边界情况：如果只有一个点，那么信息 1 即为当前点的字符，信息 2 的值一定为 1。
	pii x=dfs(l,l+(r-l+1)/3-1),y=dfs(l+(r-l+1)/3,l+(r-l+1)/3*2-1),z=dfs(l+(r-l+1)/3*2,r);//区间分段。
	int cnt[2]={0,0};
	cnt[x.first]++,cnt[y.first]++,cnt[z.first]++;
    //按照描述中的情况分类讨论。
	if (cnt[0]==3){
		int b[]={x.second,y.second,z.second};
		sort(b,b+3);
		return {0,b[0]+b[1]};
	}
	else if (cnt[1]==3){//其实这种可以和上面合并，由于为了看的更清楚，我将两种情况分开。
		int b[]={x.second,y.second,z.second};
		sort(b,b+3);
		return {1,b[0]+b[1]};
	}
	else if (cnt[0]==2){
		int ans=1e18;
		if (x.first==0) ans=min(ans,x.second);
		if (y.first==0) ans=min(ans,y.second);
		if (z.first==0) ans=min(ans,z.second);
		return {0,ans};
	}
	else if (cnt[1]==2){
		int ans=1e18;
		if (x.first==1) ans=min(ans,x.second);
		if (y.first==1) ans=min(ans,y.second);
		if (z.first==1) ans=min(ans,z.second);
		return {1,ans};
	}
}
main(){
	n=qpow(3,read());
	for (int i=1;i<=n;i++) scanf("%1lld",a+i);
	cout <<dfs(1,n).second;
    return 0;
}
//AtCoder Beginner Contest 391 RP++
//AtCoder Beginner Contest 391 RP++
//AtCoder Beginner Contest 391 RP++
//AtCoder Beginner Contest 391 RP++
//AtCoder Beginner Contest 391 RP++

```

---

## 作者：Awsdkl (赞：5)

### 题目翻译
对于一个长度为 $3^N$ 的二进制字符串 $B$，定义一种操作：将 $B$ 分成每组 $3$ 个字符，取每组的多数值作为新的字符，生成一个长度为 $3^{N-1}$ 的新字符串。  

现在给定一个长度为 $3^N$ 的二进制字符串 $A$，重复上述操作 $N$ 次，最终得到一个长度为 $1$ 的字符串 $A'$，要求找出最少需要修改 $A$ 中的多少个字符（$0$ 变 $1$ 或 $1$ 变 $0$），才能使最终的 $A'$ 值翻转。  
### 思路
可以把原题看成一颗三叉树，每个结点的值可以由它的左、中、右三个孩子得到。对于样例 $1$，我们可以有下图：  
![](https://cdn.luogu.com.cn/upload/image_hosting/s4nhnd85.png)  
类似于一个树形 dp，可以记录在每个结点改变这个结点的值所需要的最小修改次数。  
记当前结点为 $p$，左、中、右儿子分别为 $lp, mp, rp$，可以分为两种情况：  
1. 只需要改其中一个儿子即可修改当前结点。及三个儿子中有一个的值与其他两个不同。
2. 需要修改两个儿子。及三个儿子的值相同。

对于第一种情况，我们只需要求那两个和当前结点的值相同的儿子的答案的最小值。  
对于第二种情况，我们要求三个儿子的答案分别两两相加的最小值。  
转移代码如下：
```cpp
f[p] = 0x3f3f3f3f;
//只需要改一个的情况
if((nowv == 0 && cnt1 == 1) || (nowv == 1 && cnt0 == 1))
{
  if(lpv == nowv) f[p] = min(f[p], f[lp]);
  if(mpv == nowv) f[p] = min(f[p], f[mp]);
  if(rpv == nowv) f[p] = min(f[p], f[rp]);
}
//需要改两个的情况
else
{
  f[p] = min(f[p], f[lp] + f[mp]);
  f[p] = min(f[p], f[lp] + f[rp]);
  f[p] = min(f[p], f[mp] + f[rp]);
}
```
其中 ```nowv``` 为当前结点的值，```cnt0```，```cnt1``` 分别是子节点中值为 $0$ 和 $1$ 的数量。  
### 完整代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

char s[1594323+5];
int n;

int f[(1594323<<2)+5];
int cnt = 1;

/// @param p 当前结点编号
/// @param l 当前结点对应字符串的左端点
/// @param r 右端点
/// @return 未修改时当前结点的值
int dfs(int p, int l, int r)
{
	if(l == r)
	{
		f[p] = 1;
		return s[r] - '0';
	}
	int lp = ++cnt, mp = ++cnt, rp = ++cnt;
	int len = (r - l + 1);
	int lpv = dfs(lp, l, 			l+len/3-1);		//左孩子的值
	int mpv = dfs(mp, l+len/3, 		l+len/3*2-1);	//中孩子的值
	int rpv = dfs(rp, l+len/3*2, 	r);				//右孩子的值
	int cnt0 = 0, cnt1 = 0;
	if(lpv == 0) cnt0++; else cnt1++;
	if(mpv == 0) cnt0++; else cnt1++;
	if(rpv == 0) cnt0++; else cnt1++;
	int nowv = cnt0 > cnt1 ? 0 : 1;					//当前结点的值
	f[p] = 0x3f3f3f3f;
	//只需要改一个的情况
	if((nowv == 0 && cnt1 == 1) || (nowv == 1 && cnt0 == 1))
	{
		if(lpv == nowv) f[p] = min(f[p], f[lp]);
		if(mpv == nowv) f[p] = min(f[p], f[mp]);
		if(rpv == nowv) f[p] = min(f[p], f[rp]);
	}
	//需要改两个的情况
	else
	{
		f[p] = min(f[p], f[lp] + f[mp]);
		f[p] = min(f[p], f[lp] + f[rp]);
		f[p] = min(f[p], f[mp] + f[rp]);
	}
	return nowv;
}

int main()
{
	scanf("%d%s", &n, s+1);
	dfs(1, 1, strlen(s+1));
	printf("%d", f[1]);
	return 0;
}
```

---

## 作者：Ivan422 (赞：4)

~~写的很烂见谅。~~

你重生了，重生到了这个菜狗上。

你发现你正在打 E 题。

点开没有完成的 D 题，大脑一片空白。

你，于是打开了 E。

你发现这个题看起来像一颗满三叉树。

你觉得这题像是一道树形 dp。

但是你早已忘记怎么打树形 dp 了。

你开始尝试着递推。

你觉得可以先求出一个点的子节点的结果。

你设这个值为 $s_{i,j}$，即第 $i$ 层的 $j$ 个节点的答案。

你发现可以推出一个 dp，设 $c_{i,j}$ 为将 $i$ 层 $j$ 节点修改的最小代价。

但是，你又发现，dp 方程十分棘手。

你胡乱地，在画板上画着样例。

![](https://cdn.luogu.com.cn/upload/image_hosting/g2gp1nge.png)

你发现，当 $s_{i-1,j}=0$，我们就要在其子树 $s_{i,3\times j}$、$s_{i,3\times j-1}$ 和 $s_{i,3\times j-2}$ 中转移。

你开心地打出了如下的方程。

$s_{n,i}$ 是原来读入的数组。

当 $s_{i-1,j}=s_{i,3\times j}$，$c_{i,j}=\min(c_{i,j},c_{i-1,3\times j})$。

当 $s_{i-1,j}=s_{i,3\times j-1}$，$c_{i,j}=\min(c_{i,j},c_{i-1,3\times j-1})$。

当 $s_{i-1,j}=s_{i,3\times j-2}$，$c_{i,j}=\min(c_{i,j},c_{i-1,3\times j-2})$。

但是，样例 $2$ 直接把你卡掉了。

你发现，在 $\tt 000$ 这组样例中，我们要在其中至少选出两个转移更改才能改答案。

这下，你的代码变的又臭又长。

当 $|cnt_{i-1,j,0}-cnt_{i-1,j,1}|=3$，这时我们要改变其中两个。

当 $s_{i-1,j}=s_{i,3\times j}$ 且 $s_{i-1,j}=s_{i,3\times j-1}$，$c_{i,j}=\min(c_{i,j},c_{i-1,3\times j}+c_{i-1,3\times j-1})$。

当 $s_{i-1,j}=s_{i,3\times j-1}$ 且 $s_{i-1,j}=s_{i,3\times j-2}$，$c_{i,j}=\min(c_{i,j},c_{i-1,3\times j-1}+c_{i-1,3\times j-2})$。

当 $s_{i-1,j}=s_{i,3\times j}$ 且 $s_{i-1,j}=s_{i,3\times j-2}$，$c_{i,j}=\min(c_{i,j},c_{i-1,3\times j}+c_{i-1,3\times j-2})$。

答案就是 $c_{0,1}$。

你看着这份代码：


```cpp
#include<bits/stdc++.h>
//#include<bits/extc++.h>
using namespace std;
//using namespace __gnu_pbds;
//#define arr array<int,3>
#define int long long
//#define pb push_back
//#define double long double
//#define map unordered_map
//#pragma GCC optimize(2,3,"Ofast","inline")
const int N=17e5+10,M=1010,P=1e9+7,MOD=998244353;
const double PI=3.1415926,EPS=0.00001;
int n,pw[N],cnt[14][N][2],s[14][N],c[14][N];
string st;
signed main(){
	cin>>n;cin>>st;st=" "+st;
	pw[0]=1;
	for(int i=1;i<=n;i++)pw[i]=pw[i-1]*3;
	for(int i=1;i<=pw[n];i++)s[n][i]=st[i]-'0',c[n][i]=1;
	for(int i=n;i>=1;i--){
		for(int j=1;j<=pw[i];j++)cnt[i-1][(j-1)/3+1][s[i][j]]++;
		for(int j=1;j<=pw[i-1];j++){
			s[i-1][j]=(cnt[i-1][j][0]>cnt[i-1][j][1]?0:1);
			if(abs(cnt[i-1][j][0]-cnt[i-1][j][1])==1){
				c[i-1][j]=1e9;
				if(s[i][j*3]==s[i-1][j])  c[i-1][j]=min(c[i-1][j],c[i][j*3])  ;
				if(s[i][j*3-1]==s[i-1][j])c[i-1][j]=min(c[i-1][j],c[i][j*3-1]);
				if(s[i][j*3-2]==s[i-1][j])c[i-1][j]=min(c[i-1][j],c[i][j*3-2]);		
			}else{
				c[i-1][j]=1e9;
				if(s[i][j*3]==s[i-1][j]&&s[i][j*3-1]==s[i-1][j])  c[i-1][j]=min(c[i-1][j],c[i][j*3]+c[i][j*3-1])  ;
				if(s[i][j*3-1]==s[i-1][j]&&s[i][j*3-2]==s[i-1][j])c[i-1][j]=min(c[i-1][j],c[i][j*3-1]+c[i][j*3-2]);
				if(s[i][j*3-2]==s[i-1][j]&&s[i][j*3]==s[i-1][j])c[i-1][j]=min(c[i-1][j],c[i][j*3-2]+c[i][j*3]);	
			}
		}
	}
	cout<<c[0][1];
    return 0;
}
//note:

```

感到十分无语。

你接着去尝试 D，但是却被自己那错误的做法绕了进去。

时间到了，你仍然没有通过。

抽象。

---

## 作者：Pyrf_uqcat (赞：3)

注意到数据较小，其实直接递归即可通过此题。

需要在三者里面有两个较多，只需寻找损失最小的改变方法。注意要把 $1$ 变成 $0$，$0$ 变成 $1$，需要搜两次。

### 赛时已过代码


```cpp
#include <bits/stdc++.h>
#define int long long

#define N 2000005

using namespace std;

string s;

int n,a[N];

int f(int x,int len,int p)
{
	if(len==3)
	{
		int cnt=(a[x]==p)+(a[x+1]==p)+(a[x+2]==p);
		return max(2-cnt,0ll);
	}
	int a=f(x,len/3,p),b=f(x+len/3,len/3,p),c=f(x+2*(len/3),len/3,p);
	return a+b+c-max({a,b,c});
}

signed main()
{
    cin>>n>>s;
    for(int i=0;i<s.size();i++)
    {
		a[i+1]=s[i]-'0';
	}
	int po=pow(3,n);
	cout<<max(f(1,po,1),f(1,po,0))<<endl;
    return 0;
}

```

---

## 作者：Union_Find (赞：2)

有趣的题。

首先我们可以发现，这个序列的操作的结构是一颗满三叉树，并且节点数不超过 $3 \times 10^6$。我们可以先把这棵树建出来，每个结点的权值就是按照题目所述操作得出的值，然后进行处理。

第一步，在建树的同时求出序列原本根节点的权值。

第二步，用树形 dp 求出答案。

我们设 $f_{i,0/1}$ 表示 $i$ 号节点权值为 $0/1$ 时的最少修改次数，就可以 $O(m)$ 的转移了，$m$ 指树上的节点数，大约是 $3 \times 10^6$，可以通过。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define il inline
#define N 3000005
il ll rd(){
	ll s = 0, w = 1;
	char ch = getchar();
	for (;ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') w = -1;
	for (;ch >= '0' && ch <= '9'; ch = getchar()) s = ((s << 1) + (s << 3) + ch - '0');
	return s * w;
}
ll k, n, len, a[N], f[N][2], ls[N], ms[N], rs[N], p[N];
char s[N];
il ll zs(ll x, ll y, ll z){
	if ((x && y) || (y && z) || (x && z)) return 1;
	return 0;
}void dfs(ll u){
	if (!ls[u]) return f[u][a[u] ^ 1] = 1, void(0); 
	dfs(ls[u]), dfs(ms[u]), dfs(rs[u]);
	ll x = f[ls[u]][a[u] ^ 1], y = f[ms[u]][a[u] ^ 1], z = f[rs[u]][a[u] ^ 1];
	f[u][a[u] ^ 1] = min(x + y, min(y + z, x + z));
}
int main(){
	k = rd();
	scanf ("%s", s + 1);
	len = n = pow(3, k); 
	for (int i = 1; i <= n; i++) a[i] = s[i] - '0', p[i] = i;
	for (int i = 1; i <= k; i++){
		for (int j = 1; j + j + j <= len; j++){
			a[++n] = zs(s[j + j + j - 2] - '0', s[j + j + j - 1] - '0', s[j + j + j] - '0');
			ls[n] = p[j + j + j - 2], ms[n] = p[j + j + j - 1], rs[n] = p[j + j + j], p[j] = n;
		}for (int j = 1; j + j + j <= len; j++) s[j] = a[p[j]] + '0';
		len /= 3;
	}dfs(n);
	printf ("%lld\n", f[n][a[n] ^ 1]);
	return 0;
}

```

---

## 作者：_zqh_ (赞：2)

树形 dp。

---

建立起一颗满三叉树，所有的叶子节点权值就是题目中的序列。

每级合并作为父亲的权值，一直这样递归到根节点，像这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/e2js5i7r.png)

（括号外为编号，内为权值）

我们考虑对这棵树做树形 dp。

记 $dp_u$ 为改变编号为 $u$ 的点的点权至少需要改几个点。

因为叶子只需要改自己一个，所以对于任意一个叶子结点 $x$，$dp_x = 1$。

对于任意一个非叶子结点 $u$，如果 $u$ 的左、中、右三个儿子的权值均相等，则：
$$
dp_u = \min\{dp_l+dp_m, dp_l + dp_r, dp_m + dp_r\}
$$
（$l, m, r$ 代表左、中、右三个儿子的编号）

否则就是将任意一个与 $u$ 权值相等的改一下。

这样：
$$
dp_u = \min
\begin{cases}
dp_l+dp_m   & ,   &   v_l = v_m = v_r\\
dp_l+dp_r   & ,   &   v_l = v_m = v_r\\
dp_m+dp_r   & ,   &   v_l = v_m = v_r\\
\min(dp_l, dp_m) &,& v_r = v_u\\
\min(dp_l, dp_r) &,& v_m = v_u\\
\min(dp_m, dp_r) &,& v_l = v_u
\end{cases} 
$$

```cpp
#include <bits/stdc++.h>
// #define int long long
#define pii pair<int, int>
#define FRE(x) freopen(x ".in", "r", stdin), freopen(x ".out", "w", stdout)
#define ALL(x) x.begin(), x.end()
using namespace std;

int _test_ = 1;

const int N = 5000005;

int tot, dp[N];

struct node {
	int v, l, m, r;
} a[N];

void dfs(int u) {
	if (a[u].v == -1 || u == 0) return;
	if (a[u].l == 0) return dp[u] = 1, void();
	dfs(a[u].l), dfs(a[u].m), dfs(a[u].r);
	if (a[a[u].l].v + a[a[u].m].v + a[a[u].r].v != 0 && a[a[u].l].v + a[a[u].m].v + a[a[u].r].v != 3) {
		if (a[a[u].l].v == a[u].v) dp[u] = min(dp[u], dp[a[u].l]);
		if (a[a[u].m].v == a[u].v) dp[u] = min(dp[u], dp[a[u].m]);
		if (a[a[u].r].v == a[u].v) dp[u] = min(dp[u], dp[a[u].r]);
	} else {
		dp[u] = min(dp[u], dp[a[u].m] + dp[a[u].r]);
		dp[u] = min(dp[u], dp[a[u].l] + dp[a[u].r]);
		dp[u] = min(dp[u], dp[a[u].l] + dp[a[u].m]);
	}
}

void init() {}

void clear() {}

void solve() {
	memset(dp, 0x3f, sizeof(dp));
	a[0].v == -1;
	int n, g;
	cin >> n;
	g = pow(3, n);
	for (int i = 1; i <= g; i++) {
		char c;
		cin >> c;
		a[i].v = c - '0';
	}
	tot = g;
	int p = 0;
	int tmp = g / 3;
	while (tmp) {
		for (int i = 1; i <= tmp; i++) {
			a[++tot].l = p + 3 * i - 2;
			a[tot].m = p + 3 * i - 1, a[tot].r = p + 3 * i;
			int t = a[p + 3 * i - 2].v + a[p + 3 * i - 1].v + a[p + 3 * i].v;
			if (t <= 1) a[tot].v = 0;
			else a[tot].v = 1;
		}
		p = p + tmp * 3;
		tmp /= 3;
	}
	dfs(tot);
	cout << dp[tot];
}

signed main() {
//	ios::sync_with_stdio(0);
//	cin.tie(0), cout.tie(0);
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

## 作者：Inzaghi_Luo (赞：2)

看到 $n$ 很小，又显然不好贪心，所以想 DP 去做。设 $f_{i,j}$ 代表在第 $i-1$ 次操作后改变第 $j$ 个数的值所需要的最小操作数。具体转移就枚举上一层对应的三个数，分类讨论其中的众数和个数转移即可。
### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2000005;
char ch[MAXN];
int f[15][MAXN], len[15];
int a[MAXN][15];
int main(){
	int n;
	scanf("%d%s", &n, ch + 1);
	len[n + 1] = 1;
	for(int i = n;i;i--) len[i] = 3 * len[i + 1];
	for(int i = 1;i <= len[1];i++){
		a[i][1] = ch[i] - '0';
		f[1][i] = 1;
	}
	for(int i = 2;i <= n + 1;i++){
		for(int j = 1;j <= len[i];j++){
			int x = 3 * j - 2, y = x + 1, z = y + 1;
			int c0 = 0, c1 = 0;
			if(a[x][i - 1] == 0) c0++;
			else c1++;
			if(a[y][i - 1] == 0) c0++;
			else c1++;
			if(a[z][i - 1] == 0) c0++;
			else c1++;
			if(c0 > c1) a[j][i] = 0;
			else a[j][i] = 1;
			if(c0 == 0){
				f[i][j] = min(min(f[i - 1][x] + f[i - 1][y], f[i - 1][x] + f[i - 1][z]), f[i - 1][y] + f[i - 1][z]);
			}
			else if(c0 == 1){
				if(a[x][i - 1] == 0){
					f[i][j] = min(f[i - 1][y], f[i - 1][z]);
				}
				if(a[y][i - 1] == 0){
					f[i][j] = min(f[i - 1][z], f[i - 1][x]);
				}
				if(a[z][i - 1] == 0){
					f[i][j] = min(f[i - 1][x], f[i - 1][y]);
				}
			}
			else if(c0 == 2){
				if(a[x][i - 1] == 1){
					f[i][j] = min(f[i - 1][y], f[i - 1][z]);
				}
				if(a[y][i - 1] == 1){
					f[i][j] = min(f[i - 1][z], f[i - 1][x]);
				}
				if(a[z][i - 1] == 1){
					f[i][j] = min(f[i - 1][x], f[i - 1][y]);
				}
			}
			else{
				f[i][j] = min(min(f[i - 1][x] + f[i - 1][y], f[i - 1][x] + f[i - 1][z]), f[i - 1][y] + f[i - 1][z]);
			}
		}
	}
	printf("%d", f[n + 1][1]);
	return 0;
}
```

---

## 作者：chenxi2009 (赞：1)

## 思路
考虑一种递推。我们令 $f_{i,j}$ 表示 $A$ 被“压缩”到长度为 $3^i$ 的程度时的 $A_j$，$g_{i,j}$ 表示改变 $f_{i,j}$ 的代价，发现当把三个字符压缩在一起的时候，如果三个字符都一样，改变压缩后字符的代价就是这三个字符改变代价较小两个之和；如果有两个字符一样，代价就是这两个字符的改变代价较小值。综上有递推
$$
tmp\leftarrow[f_{i+1,3j-2}=1]+[f_{i+1,3j-1}=1]+[f_{i+1,3j}=1]\\
f_{i,j}=[tmp>1]\\
g_{i,j}=\begin{cases}
g_{i+1,3j-2}+g_{i+1,3j-1}+g_{i+1,3j}-\max(g_{i+1,3j-2},g_{i+1,3j-1},g_{i+1,3j}),tmp\in\{0,3\}\\
\min(g_{i+1,3j-2},g_{i+1,3j-1}),tmp\in\{1,2\}, f_{i+1,3j-2}=f_{i+1,3j-1}\\
\min(g_{i+1,3j-2},g_{i+1,3j}),tmp\in\{1,2\}, f_{i+1,3j-2}=f_{i+1,3j}\\
\min(g_{i+1,3j-1},g_{i+1,3j}),tmp\in\{1,2\}, f_{i+1,3j-1}=f_{i+1,3j}\\
\end{cases}
$$

初始令 $f_N\leftarrow A,g_{N,i}\leftarrow1$，递推后 $g_{0,1}$ 就是答案。时间复杂度 $O(3^N)$。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,p[15],g[15][2000000];
char f[15][2000000];
int max(int a,int b,int c){
	return max(a,max(b,c));
}
int main(){
	p[0] = 1;
	for(int i = 1;i <= 13;i ++) p[i] = p[i - 1] * 3;//预处理 3 的幂
	scanf("%d",&n);
	scanf("%s",f[n] + 1);
	for(int i = 1;i <= p[n];i ++) g[n][i] = 1;
	for(int i = n - 1;~i;i --){
		for(int j = 1;j <= p[i];j ++){
			int cnt = (f[i + 1][3 * j - 2] == '0') + (f[i + 1][3 * j - 1] == '0') + (f[i + 1][3 * j] == '0');
			int a = g[i + 1][3 * j - 2],b = g[i + 1][3 * j - 1],c = g[i + 1][3 * j];
			if(cnt == 0) f[i][j] = '1',g[i][j] = a + b + c - max(a,b,c);
			else if(cnt == 1){
				f[i][j] = '1';
				if(f[i + 1][3 * j - 2] == '0') g[i][j] = min(b,c);
				else if(f[i + 1][3 * j - 1] == '0') g[i][j] = min(a,c);
				else g[i][j] = min(a,b);
			}
			else if(cnt == 2){
				f[i][j] = '0';
				if(f[i + 1][3 * j - 2] == '1') g[i][j] = min(b,c);
				else if(f[i + 1][3 * j - 1] == '1') g[i][j] = min(a,c);
				else g[i][j] = min(a,b);
			}
			else f[i][j] = '0',g[i][j] = a + b + c - max(a,b,c);
		}
	}
	printf("%d",g[0][1]);
	return 0;
}
```

---

## 作者：内拉组里 (赞：1)

传统 **ABC** 题，考察思维。

# Statement：

> 将一个长 $ 3^n $ 的 $ 01 $ 串每三个字符为一组压缩成一个字符，取三个数的众数。
>
> 以此类推压缩若干轮后只剩一个字符。
>
> 改动最少的字符使得最后剩下的字符改变。
>
> 求改动的字符数。

# Thoughts：

显然是 **dp**，令 $ dp[i][j][0/1] $ 表示压缩 $ i $ 轮后使第 $ j $ 个字符转换为 $ 0/1 $ 的最小代价。

初始状态：若 $ s[i] = 0 $，则 $ dp[0][i][0] = 0,dp[0][i][1] = 1 $，$ s[i] = 1 $ 反之。

转移。

这里以转换为 $ 0 $ 为例，$ 1 $ 者类似。

考虑三个字符要得到一个 $ 0 $，那么只有四种情况：

| 3n   | 3n + 1 | 3n + 2 |
| ---- | ------ | ------ |
| 0    | 0      | 0      |
| 0    | 0      | 1      |
| 0    | 1      | 0      |
| 1    | 0      | 0      |

把三个数对应的代价加起来，再对四种情况取个 $ \min $，

即：
$$
dp[i + 1][j][0] = \min 
\begin{cases}
	dp[i][j \times 3 + 0][0] + dp[i][j \times 3 + 1][0] + dp[i][j \times 3 + 2][0] \\ 
	dp[i][j \times 3 + 0][0] + dp[i][j \times 3 + 1][0] + dp[i][j \times 3 + 2][1] \\ 
	dp[i][j \times 3 + 0][0] + dp[i][j \times 3 + 1][1] + dp[i][j \times 3 + 2][0] \\ 
	dp[i][j \times 3 + 0][1] + dp[i][j \times 3 + 1][0] + dp[i][j \times 3 + 2][0] 
\end{cases}
$$
最后输出 $ \max (dp[n][0][0],dp[n][0][1]) $ 即可。

# Analyses：

> 总时间复杂度 $ \Theta (N) $。
>
> 总空间复杂度 $ \Theta (N) $。

# Code：

```cpp
/* reference : @ATC.Mimo_kare_coding */
#include	<algorithm>
#include	<iostream>
using namespace std;
constexpr int maxn = 16;
constexpr int max3n = 2e6+4;

int n;
string s;
int dp[maxn][max3n][2];	/* cost convert into 0/1 */

signed main (void)
{
	cin >> n >> s;
	int len = s.length();
	for (int i = 0; i < len; i++)
	{
		if (s[i] ^ '0')
		{
			dp[0][i][0] = 1;
			dp[0][i][1] = 0;
		}
		else
		{
			dp[0][i][0] = 0;
			dp[0][i][1] = 1;
		}
	}
	len /= 3;
	for (int i = 0; i < n; i++, len /= 3)
	{
		for (int j = 0; j < len; j++)
		{
			auto d0 = dp[i][j * 3 + 0][0];
			auto d1 = dp[i][j * 3 + 1][0];
			auto d2 = dp[i][j * 3 + 2][0];
			auto p0 = dp[i][j * 3 + 0][1];
			auto p1 = dp[i][j * 3 + 1][1];
			auto p2 = dp[i][j * 3 + 2][1];
			dp[i + 1][j][0] = min ({d0 + d1 + d2,
									d0 + d1 + p2,
									d0 + p1 + d2,
									p0 + d1 + d2});
			dp[i + 1][j][1] = min ({p0 + p1 + p2,
									p0 + p1 + d2,
									p0 + d1 + p2,
									d0 + p1 + p2});
		}
	}
	cout << max (dp[n][0][0], dp[n][0][1]) << endl;
	return 0;
}
```

---

## 作者：crz_qwq (赞：1)

对每一层记录他上一层的每个元素的值 $lst_i$，上一层所有元素改变他的代价 $pre_i$，这一层的元素值 $val_i$，这一层的元素改变他的代价 $cost_i$。

如果有一段 $j \sim j+2$ 被合并了，那么会有以下几种情况。

1. $3$ 个 $0$，这是我们令 $cost_j=\min(pre_j,pre_{j+1},pre_{j+2})$。

2. $2$ 个 $0$，这时我们令 $cost_j=\min_{j\le k \le k+2,lst_k=0}(pre_k)$。

剩余同理。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e6+5,inf=0x3f3f3f3f;
int qpow(int x,int y)
{
    int res=1;
    while(y)
    {
        if(y&1)res=res*x;
        x=x*x;
        y>>=1;
    }
    return res;
}
int lst[N],pre[N],val[N],cost[N];
signed main()
{
    int n;
    string s;
    cin>>n>>s;
    s="#"+s;
    for(int i=1;i<=qpow(3,n);++i)
        lst[i]=s[i]-'0',pre[i]=1;
    for(int i=1;i<=n;++i)
    {
        int len=qpow(3,n-i+1);
        for(int j=1,cur=1;j<=len;j+=3,++cur)
        {
            cost[cur]=inf;
            int cnt0=0,cnt1=0;
            for(int k=j;k<=j+2;++k)
            {
                if(lst[k]==0)cnt0++;
                else cnt1++;
            }
            if(cnt0==3)
                cost[cur]=min({pre[j]+pre[j+1],pre[j]+pre[j+2],pre[j+1]+pre[j+2]});
            else if(cnt0==2)
            {
                for(int k=j;k<=j+2;++k)
                    if(lst[k]==0)
                        cost[cur]=min(cost[cur],pre[k]);
            }
            else if(cnt1==2)
            {
                for(int k=j;k<=j+2;++k)
                    if(lst[k]==1)
                        cost[cur]=min(cost[cur],pre[k]);
            }
            else if(cnt1==3)
                cost[cur]=min({pre[j]+pre[j+1],pre[j]+pre[j+2],pre[j+1]+pre[j+2]});
            if(cnt0>cnt1)
                val[cur]=0;
            else val[cur]=1;
            // cout<<val[cur]<<' ';
        }
        // cout<<'\n';
        for(int j=1;j<=qpow(3,n-i);++j)
            lst[j]=val[j],pre[j]=cost[j];
    }
    cout<<cost[1];
}
```

---

## 作者：M_WC1S_M0 (赞：1)

## AtCoder Beginner Contest 391 E - Hierarchical Majority Vote

### 题目大意

给定一个长度为 $3^n$ 的 `01` 串，每次可以支付 $1$ 的代价修改串中的一个位。

每进行一轮操作时，会将连续的每 $3$ 个数组合成一个新数（取多数值），直到进行 $n$ 轮得到一个数。

求使最终数字为 $0$ 的最小代价。

### 解题思路

考虑使用 DP 自底向上解决。

1. **状态设计**

   - `dp[i][j]`: 下标为 $i$ 的位置产生值 $j$ 的最小代价。
   - 每一轮计算当前轮次的最优解。

2. **转移过程**

   - 枚举每 $3$ 个位置的所有可能取值。
   - 计算多数值并更新下一轮的 `dp` 值。

3. **初始化**

   - 对原始串每个位置，设置对应值代价为 $0$。
   - 修改为相反值代价为 $1$。

### 核心代码

```cpp
vector<vector<ll>> dp(len,vector<ll>(2,INF));

// 初始化
for(int i=0;i<len;i++){
    dp[i][s[i]-'0']=0;
    dp[i][1-(s[i]-'0')]=1;
}

ll curr_size=len;
for(int k=n-1;k>=0;k--){
    curr_size/=3; 
    vector<vector<ll>> new_dp(curr_size,vector<ll>(2,INF));
    
    for(int i=0;i<curr_size;i++){
        for(int x=0;x<2;x++){
            for(int y=0;y<2;y++){
                for(int z=0;z<2;z++){
                    ll cost=0;
                    if(dp[i*3][x]!=INF)cost+=dp[i*3][x];
                    else continue;
                    if(dp[i*3+1][y]!=INF)cost+=dp[i*3+1][y];
                    else continue;
                    if(dp[i*3+2][z]!=INF)cost+=dp[i*3+2][z];
                    else continue;
                    
                    int maj=(x+y+z>=2)?1:0;
                    new_dp[i][maj]=min(new_dp[i][maj],cost);
                }
            }
        }
    }
    dp=new_dp;
}
```

### 复杂度分析

- 时间复杂度：$O(n\cdot 3^n)$。
  - 需要进行 n 次转移。
  - 每次处理 $3^{n-k}$ 个状态。
  - 每个状态需要枚举 8 种可能性。
- 空间复杂度：$O(3^n)$。
  - 需要存储每个位置两种状态的代价。

### 注意事项

1. 初始化时需要设置 `INF` 避免非法转移。

2. 需要特别注意检查每步转移的合法性。

3. 注意使用 `long long` 避免溢出。

4. 最终答案需要判断哪个值为 0。

---

## 作者：Inv_day_in_R (赞：1)

这道题很容易想到按照操作顺序建一颗三叉树，就比如样例一是这样的：（图有点模糊）
![](https://cdn.luogu.com.cn/upload/image_hosting/483ux8mv.png)

很容易发现这棵树和二叉树有类似的性质，任意 $v$ 点的三个子节点编号刚好为 $3v+1$、$3v+2$ 和 $3v+3$。

按上面这棵树说，这里先将原字符串带入所有叶子节点，然后可递归建树，算出每个节点的原始值。

接下来在这棵树上进行树形 DP，令 $\text{dp}_v$ 为改变点 $v$ 的值所需要花费的最小代价。显然，所有叶子节点的值都为 $1$。接下来需要分情况讨论：

1. 如果三个子节点原始值 $000$，那么想改变当前点数值为 $1$，需要改变任意两个子节点。为了方便表示，令三个子节点的 $\text{dp}$ 值为 $x$、$y$ 和 $z$。(子节点原始值 $111$ 同理)
    $$\text{dp}_v=\min\{x+y,y+z,z+x\}$$
2. 如果三个子节点原始值为 $001$，那么想改变当前点数值为 $1$，需要改变任意一个原始值为 $0$ 的子节点。为了方便表示，令两个原始值为 $0$ 的子节点的 $\text{dp}$ 值为 $x$ 和 $y$。（子节点原始值 $010$、$011$、$100$、$101$ 和 $110$ 全都基本同理，具体实现看代码）。
   $$\text{dp}_v=\min\{x,y\}$$
最终答案就是 $\text{dp}_0$。

代码：

```cpp
vector<int>tr;
int TR(int v){//记忆化搜索，算出原始值
	if(tr[v]!=-1)return tr[v];
	int cnt=TR(v*3+1)+TR(v*3+2)+TR(v*3+3);//1的个数
	if(cnt<2)tr[v]=0;
	else tr[v]=1;
	return tr[v];
}
int dp(int v){
	if(v*3+1>=tr.size())return 1;//叶子节点，返回1
	int a=TR(v*3+1),b=TR(v*3+2),c=TR(v*3+3);//计算原始值
	int x=dp(v*3+1),y=dp(v*3+2),z=dp(v*3+3);
	if(a==0&&b==0&&c==0)return min({x+y,x+z,y+z});//000与111，反转ab，ac或bc
	if(a==1&&b==1&&c==1)return min({x+y,x+z,y+z});
	if(a==0&&b==0&&c==1)return min(x,y);//001与110，反转a或b
	if(a==1&&b==1&&c==0)return min(x,y);
	if(a==0&&b==1&&c==1)return min(y,z);//011与100，反转b或c
	if(a==1&&b==0&&c==0)return min(y,z);
	if(a==0&&b==1&&c==0)return min(x,z);//010与101，反转a或c
	if(a==1&&b==0&&c==1)return min(x,z);
}
void solve(){
	int n;
	cin>>n;
	string s;
	cin>>s;
	int x=1,cnt=0;
	for(int i=0;i<=n;i++){
		cnt+=x;//计算总点数，每一层点数为上一层三倍
		x*=3;
	}
	x/=3;//最后一层点数，因为多乘了一次，所以要除掉
	tr.assign(cnt,-1);
	for(int i=cnt-1,j=x-1;j>=0;i--,j--)tr[i]=s[j]-'0';//将原字符串存入最后一层
	cout<<dp(0);
}
```

---

## 作者：StarsIntoSea_SY (赞：1)

初始数列修改改一次值的代价显然为 $1$。

那么变换之后，对应的值的代价显然受变换前的代价影响。

分类讨论：

1. 形如 `1 1 1` 的三个一的情况，变换后为 `1`，此时若要修改变换后的值，最小代价为变换前三个 `1` 中修改代价最小的两个代价之和。
2. 形如 `0 0 0` 的三个零的情况，变换后为 `0`，此时若要修改变换后的值，最小代价为变换前三个 `0` 中修改代价最小的两个代价之和。
3. 形如 `1 1 0` 的有两个一的情况，变换后为 `1`,此时若要修改变换后的值，最小代价为变换前两个 `1` 中修改代价最小的一个代价。
4. 形如 `0 0 1` 的有两个零的情况，变换后为 `0`,此时若要修改变换后的值，最小代价为变换前两个 `0` 中修改代价最小的一个代价。

经过上述变换后，得到最后一个值的修改代价即为最终答案。

![](https://cdn.luogu.com.cn/upload/image_hosting/wh1b2ll5.png)

如上图，黑色为依次变换的数列，红色为对应位置修改的最小代价。

[赛时代码](https://atcoder.jp/contests/abc391/submissions/62300291)太乱，仅供参考。

---

## 作者：xiaoyin2011 (赞：0)

## AT_abc391_e [ABC391E] 分层多数投票 题解

[题目链接](https://www.luogu.com.cn/problem/AT_abc391_e)

### 题目大意

长度为 $3^n$ 的 01 字符串可以进行如下操作变成一个长为 $3^{n - 1}$ 的 01 字符串：

将 01 字符串从头开始，每 $3$ 个字符分为一组，可以知道总共分为 $3^{n - 1}$ 组。对于每一组的三个字符，每个字符可能是 `0` 或者 `1`，显然只有 `0` 的数量多于 `1` 或者 `1` 多于 `0` 两种情况，如果 `0` 更多，则新的字符串中这三个字符对应的一个字符为 `0`，反之为 `1`。可以知道，最后新的字符串长度恰为 $\frac{3^n}{3} = 3^{n-1}$。

现在给定一个长度为 $3^N$ 的 01 字符串 $A$，经过 $N$ 次操作，$A$ 就会变成只有一个字符的字符串，这个字符串就是整个 $A$ 经过层层多数投票得到的结果，我们记为 `res`。题目询问，至少修改 $A$ 中的多少个字符，也就是至少将 $A$ 中多少个 `0` 翻转为 `1`、`1` 翻转为 `0`，使得修改后的字符串层层多数投票得到的一个字符和 `res` 不同（发生改变）。

题目保证 $1 \le N \le 13$。

### 思路

$A$ 逐渐自我合并的过程可以看作是一个满三叉树，树的叶子层顺序看起来就是 $A$。然后树中的非叶子节点的值取决于他的三个儿子。最终答案 `res`，就是根节点的值。

显然对于最终结果 `res`，我们想让其变成另一个结果 `1 - res`，我们只能让更多的 `res` 变成 `1 - res`，而绝不会让 `1 - res` 变回 `res`。

“至少修改多少叶子，使得 `u` 的结果变为 `1 - res`。”如果此处 `u` 是根节点，那么这个问题的答案即为所求。我们设这个问题的答案为 `flip[u]`。

考虑怎么求 `flip[u]`：

如果 `u` 现在的值已经是 `1 - res`，那么 `flip[u] = 0`。反之如果要翻转 `u`，由于结果取决于上一次操作前的三个字符，那么想要翻转结果到 `1 - res`，就要翻转之前的字符，从而把问题推到 `flip[son]`。

这样问题最后会变为叶子节点 `leaf` 的 `flip[leaf]`。此时如果他不是 `1 - res`，翻转他只需要翻转 $A$ 中他自己对应的一个节点，所以 `flip[leaf] = 1`。

假设我们有了 `u` 三个儿子 `ls`、`ms`、`rs` 的翻转代价，设为 `flip[ls]`、`flip[ms]`、`flip[rs]`。那么 `u` 的翻转代价 `flip[u]` 是什么呢？

结论是从 `flip[ls]`、`flip[ms]`、`flip[rs]` 中选择两个最小的，然后求他们的和作为 `flip[u]`。因为 `u` 现在的值的形成，三个子节点必然有 $2 \sim 3$ 个是 `res`，所以我们要翻转 $1 \sim 2$ 个，而如果某个节点已经是 `1 - res` 了，他的 `flip = 0`，所以此处选择两个最小的是无误的。

把上面的基础情况、递推过程和最终结果综合起来看，这其实是一个 DP。

### 实现

可以通过三次 DFS 建树、计算原值、计算翻转代价，事实上可以合并成两次。

赛时代码增加注释：

```cpp
#include <bits/stdc++.h>
using namespace std;
int N; string A;
int cnt = 0, m = 0; // m 是用于调试输出的最大节点编号 
char val[5000005]; // val 表示原值 flip 表示反转代价 
int flip[5000005];
char target; // target = 1 - res
void build(int u, int dep) // 建树 u 是当前节点 dep 是深度 dep 用于判断是否到叶子层 
{
	int ls = u * 3 - 1, ms = u * 3, rs = u * 3 + 1; // ls ms rs 表示三个子节点 根节点设在 1 
	if (dep < N)
	{
		val[u] = '*';
		build(ls, dep + 1);
		build(ms, dep + 1);
		build(rs, dep + 1);
	}
	else if (dep == N)
	{
		val[u] = A[cnt++];
		m = max(m, u);
	}
}
void dfs1(int u, int dep) // 求原值 可以和上面的 build 合并实现 
{
	int ls = u * 3 - 1, ms = u * 3, rs = u * 3 + 1;
	if (dep < N)
	{
		dfs1(ls, dep + 1);
		dfs1(ms, dep + 1);
		dfs1(rs, dep + 1);
		int cnt0 = 0, cnt1 = 0;
		if (val[ls] == '0') cnt0++;
		else cnt1++;
		if (val[ms] == '0') cnt0++;
		else cnt1++;
		if (val[rs] == '0') cnt0++;
		else cnt1++;
		if (cnt0 > cnt1) val[u] = '0';
		else val[u] = '1';
	}
}
void dfs2(int u, int dep) // 求翻转费用 不能和上面合并 
{
	int ls = u * 3 - 1, ms = u * 3, rs = u * 3 + 1;
	if (val[u] == target) // 已经达到目标就可以了
	{
		flip[u] = 0;
		return ;
	}
	if (dep < N)
	{
		dfs2(ls, dep + 1);
		dfs2(ms, dep + 1);
		dfs2(rs, dep + 1);
		vector<int> tmp = {flip[ls], flip[ms], flip[rs]};
		sort(tmp.begin(), tmp.end());
		flip[u] = tmp[0] + tmp[1];
	}
	else if (dep == N)
	{
		flip[u] = 1;
	}
}
int main()
{
	scanf("%d", &N); cin >> A;
	build(1, 0);
	dfs1(1, 0);
	if (val[1] == '0') target = '1';
	else target = '0';
	dfs2(1, 0);
	// 调试输出 
	// for (int i = 1; i <= m; i++)
	//  	printf("%d : %c : %d\n", i, val[i], flip[i]);
	printf("%d\n", flip[1]); // 结果 
	return 0;
}
```

时空复杂度均为 $O(3^N)$。

### AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
int N; string A; int cnt = 0; char target;
char val[5000005];
int flip[5000005];
void dfs1(int u, int dep)
{
	int ls = u * 3 - 1, ms = u * 3, rs = u * 3 + 1;
	if (dep < N)
	{
		dfs1(ls, dep + 1);
		dfs1(ms, dep + 1);
		dfs1(rs, dep + 1);
		int cnt0 = 0, cnt1 = 0;
		if (val[ls] == '0') cnt0++;
		else cnt1++;
		if (val[ms] == '0') cnt0++;
		else cnt1++;
		if (val[rs] == '0') cnt0++;
		else cnt1++;
		if (cnt0 > cnt1) val[u] = '0';
		else val[u] = '1';
	}
	else if (dep == N)
		val[u] = A[cnt++];
}
void dfs2(int u, int dep)
{
	int ls = u * 3 - 1, ms = u * 3, rs = u * 3 + 1;
	if (val[u] == target)
	{
		flip[u] = 0;
		return ;
	}
	if (dep < N)
	{
		dfs2(ls, dep + 1);
		dfs2(ms, dep + 1);
		dfs2(rs, dep + 1);
		vector<int> tmp = {flip[ls], flip[ms], flip[rs]};
		sort(tmp.begin(), tmp.end());
		flip[u] = tmp[0] + tmp[1];
	}
	else if (dep == N)
		flip[u] = 1;
}
int main()
{
	scanf("%d", &N);
	cin >> A;
	dfs1(1, 0);
	if (val[1] == '0') target = '1';
	else target = '0';
	dfs2(1, 0);
	printf("%d\n", flip[1]);
	return 0;
}
```

---

## 作者：D0000 (赞：0)

将构建过程视为一棵树，构建过程形成了一棵 $n+1$ 层（从上至下记作第 $n$ 层至第 $0$ 层）的满三叉树。其中第 $i$ 层是第 $i$ 次操作剩下的序列，对应了原序列的所有起始位置为 $3^n$ 的倍数，长度为 $3^n$ 的区间，如果它不是叶子节点，则它的取值是 $3$ 个儿子的众数。

要求改变根节点的取值的最小操作次数。

我们可以至下而上对树上每个节点求出改变它的取值的最小操作次数 $f$：

- 如果这个节点是叶子节点，则对应的 $f=1$。

- 如果这个节点的三个儿子取值一样，则需要改变 $2$ 个的取值，此时 $f$ 等于儿子节点中较小的两个的 $f$ 的和。

- 如果一个儿子的取值不一样，需要改变另外两个儿子中的一个，$f$ 等于另外两个儿子中最小的一个的 $f$。

- 由于原序列只能为 $0,1$ 不存在 $3$ 个数都不一样的情况。

最后答案就是根节点的 $f$。

### 代码

```cpp
#include<cstdio>
#include<math.h>
#include<algorithm>
int n;
char a[2000005];
int dfs(int l=1,int r=n){
    if(l==r){
        if(a[l]=='0')return -1;
        return 1;
    }
    int len=(r-l+1)/3,o1=l+len-1,o2=o1+len;//if(l<=r)printf("%d %d %d %d %d\n",l,r,o1,o2,len);
    int w[4];w[1]=dfs(l,o1),w[2]=dfs(o1+1,o2),w[3]=dfs(o2+1,r);//printf("%d %d %d\n",w[1],w[2],w[3]);
    std::sort(w+1,w+4);
    if(w[1]<0&&w[2]<0&&w[3]<0)return w[2]+w[3];
    if(w[1]>0&&w[2]>0&&w[3]>0)return w[2]+w[1];
    if(w[2]<0)return w[2];
    return w[2];
}
int main(){
    scanf("%d%s",&n,a+1);
    n=pow(3,n);
    printf("%d",abs(dfs()));
}
```

---

## 作者：OIer_Hhy (赞：0)

# Part 1 前言

![](https://cdn.luogu.com.cn/upload/image_hosting/gdh0hp4s.png)

超常发挥，喜提六杀（可能是这次水了？）。

# Part 2 思路

分治，把一个字符串一分为三，直到长度为 $1$，将 $sum$ 定为 $3$ 个子字符串中众数为 $1$ 的子字符串个数。

此时：

- 若 $sum \ge 2$：返回 $1$。
- 否则返回 $0$。

我们把每个字符串的 $sum$ 存起来。

再作一次分治，返回的是使这个字符串的众数改变的最少改动字符数。仍然将这个字符串一分为三，直到长度为 $1$，再次分类讨论（令这个字符串为 $S$，三个子字符串分别为 $A,B,C$，三个子字符串的返回值为 $res_A,res_B,res_C$）：

- $sum_S = 0$：这时我们要改变其中的两个子字符串的众数，即 $res_S=\min(res_A+res_B,res_A+res_C,res_B+res_C)$
- $sum_S = 1$：有两个众数为 $0$ 的子字符串，我们改变其中一个众数为 $0$ 的子字符串，即 $res_S=\min(res_A(sum_A \le 1),res_B(sum_B \le 1),res_C(sum_C \le 1))$。
- $sum_S = 2$：与$sum_S = 1$ 类似，有两个众数为 $1$ 的子字符串，我们改变其中一个众数为 $1$ 的子字符串，即 $res_S=\min(res_A(sum_A \ge 2),res_B(sum_B \ge 2),res_C(sum_C \ge 2))$。
- $sum_S = 3$：与 $sum_S = 0$ 类似，我们要改变其中的两个子字符串的众数，即 $res_S=\min(res_A+res_B,res_A+res_C,res_B+res_C)$。

最终的结果就是 $res_S$。

时间复杂度：$O(3^n)$。

空间复杂度：$O(3^n)$。

# Part 3 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n,a[N],res;
string s;
map<string,int> mp;
int dfs(string s){
	int len=s.size();
	if(len==1){
		mp[s]=(s[0]-'0')*2;
		return s[0]-'0';
	}
	string a=s.substr(0,len/3);
	string b=s.substr(len/3,len/3);
	string c=s.substr(len/3*2,len/3);
	int res=dfs(a)+dfs(b)+dfs(c);
	mp[s]=res;
	return res>=2;
}
int dfs2(string s){
	int len=s.size();
	if(len==1) return 1;
	string a=s.substr(0,len/3);
	string b=s.substr(len/3,len/3);
	string c=s.substr(len/3*2,len/3);
	int x=mp[s];
	int res1=dfs2(a);
	int res2=dfs2(b);
	int res3=dfs2(c);
	int res=0;
	if(x==3||x==0) res=min(res1+res2,min(res1+res3,res2+res3));
	else if(x==1){
		if(mp[a]>=2) res=min(res2,res3);
		else if(mp[b]>=2) res=min(res1,res3);
		else res=min(res1,res2);
	}else{
		if(mp[a]<2) res=min(res2,res3);
		else if(mp[b]<2) res=min(res1,res3);
		else res=min(res1,res2);
	}
	return res;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>n>>s;
	int res=dfs(s);
	cout<<dfs2(s)<<'\n';
	return 0;
}
```

---

## 作者：Aegleseeker_ (赞：0)

感觉比 [D](https://www.luogu.com.cn/article/jtuoij9t) 简单。

这个 $3^n$ 看起来很奇怪，但是二进制串的限制和数据范围 $n\le 13$ 都在告诉你，可以使用一些简单算法通过本题。

这种「每次把每 $k$ 个数缩成一个并重复执行直到只剩一个数」的操作，我们不难想到使用分治来处理（可能与擂台游戏的暴力部分有相似之处），既把你要处理的当前区间递归成 $k=3$ 份。

定义 $f_{l,r}$ 代表把 $[l,r]$ 这个区间按题目中的要求缩成一个数，这个数是多少。

边界条件：当 $l=r$ 时，$f_{l,r}=a_l$。

否则把 $[l,r]$ 平均分成三份，分别递归求出 $f_{l',r'}$，那么 $f_{l,r}$ 就等于这三份 $f_{l',r'}$ 的众数。

下面将给出非常简单的实现：

```cpp
void init(int l,int r){
	if(l==r){
		mp[l][r]=s[l]-'0';
		return;
	}
	int tmp=r-l+1;
	init(l,l+tmp/3-1),init(l+tmp/3,l+2*tmp/3-1),init(l+2*tmp/3,r);
	int cnt1=0;
	if(mp[l][l+tmp/3-1]==1) cnt1++;
	if(mp[l+tmp/3][l+2*tmp/3-1]==1) cnt1++;
	if(mp[l+2*tmp/3][r]==1) cnt1++;
	if(cnt1>=2) mp[l][r]=1;
}
```

接下来我们考虑题目中问的是什么，既「使 $f_{1,n}$ 不同的最小修改次数」。我们同样考虑分治。

定义 $g_{l,r}$ 代表把 $[l,r]$ 这个区间按题目中的要求缩成一个数并使其不等于 $f_{l,r}$，最小的修改次数。

边界条件：当 $l=r$ 时，$g_{l,r}=1$。

否则把 $[l,r]$ 平均分成三份，分别递归求出 $g_{l',r'}$，那么我们分两种情况进行讨论：

1. 三份中 $f_{l',r'}$ 都相等，这个时候我们需要该其中的两份才能改变 $f_{l,r}$ 的结果，既找最小的两个 $g_{l',r'}$ 加起来。

2. 有一份 $f_{l',r'}$ 不同于其他两份，这个时候我们直接令 $g_{l,r}$ 等于这一份的 $g_{l',r'}$ 即可。

下面将给出同样非常简单的实现：

```cpp
int solve(int l,int r,int type){
	if(l==r){
		return mp[l][r]=1;
	}
	int tmp=r-l+1;
	int tmp1=solve(l,l+tmp/3-1,!mp[l][l+tmp/3-1]);
	int tmp2=solve(l+tmp/3,l+2*tmp/3-1,!mp[l+tmp/3][l+2*tmp/3-1]);
	int tmp3=solve(l+2*tmp/3,r,!mp[l+2*tmp/3][r]);
	if(mp[l][l+tmp/3-1]==mp[l+tmp/3][l+2*tmp/3-1]&&mp[l+2*tmp/3][r]==mp[l][l+tmp/3-1]){
		return tmp1+tmp2+tmp3-max(max(tmp1,tmp2),tmp3);
	}
	if(mp[l][l+tmp/3-1]!=mp[l][r]){
		return min(tmp2,tmp3);
	}
	if(mp[l+2*tmp/3][r]!=mp[l][r]){
		return min(tmp1,tmp2);
	}
	if(mp[l+tmp/3][l+2*tmp/3-1]!=mp[l][r]){
		return min(tmp1,tmp3);
	}
}
```

分析总复杂度的话，大约是 $O(3^n\log 3^n)$（我的实现比较恶劣，带个 `map`）反正显然能过。

submission：https://atcoder.jp/contests/abc391/submissions/62291256

---

## 作者：light_searcher (赞：0)

鲜花：赛时看了一会儿题没看懂，先去看 F 了，结果发现 E 是简单题。

我们可以直接按题意模拟，然后对于第 $i$ 轮第 $j$ 个数维护一个 $f_{i,j}$，表示将这个数取反需要更改的最小个数。这个维护很容易，根据上一轮区间内的 $0$ 和 $1$ 的个数，判断需要将上一轮中的几个数取反，才能将当前区间取反，直接从 $f_{i-1,3j-2} \sim f_{i-1,3j}$ 取几个最小值即可，最后结果是 $f_{n,1}$。初始 $f_{1,j} = 1$。然后我们发现这个式子的第一维可以滚动数组优化，这样空间复杂度就是 $\mathcal O(3^n)$，时间复杂度是 $\mathcal O(3^nn)$。

Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1.6e6;
int n,m=1,p=1,f[2][N];
char s[N],t[2][N];
int main(){
	scanf("%d%s",&n,s+1);
	for(int i=1;i<=n;i++) m*=3;
	for(int i=1;i<=m;i++){
		t[0][i]=s[i];
		f[0][i]=1;
	}
	for(int i=1;i<=n;i++){
		for(int j=1,cnt0=0,cnt1=0;j<=m;j++){
			if(t[p^1][j]=='0') cnt0++;
			else cnt1++;
			if(!(j%3)){
				if(cnt0>cnt1) t[p][j/3]='0';
				else t[p][j/3]='1';
				if(!cnt0||cnt0==3) f[p][j/3]=f[p^1][j-2]+f[p^1][j-1]+f[p^1][j]-max({f[p^1][j-2],f[p^1][j-1],f[p^1][j]});
				else if(cnt0==1){
					int ans=INT_MAX;
					for(int k=j-2;k<=j;k++)
						if(t[p^1][k]=='1') ans=min(ans,f[p^1][k]);
					f[p][j/3]=ans;
				}
				else if(cnt0==2){
					int ans=INT_MAX;
					for(int k=j-2;k<=j;k++)
						if(t[p^1][k]=='0') ans=min(ans,f[p^1][k]);
					f[p][j/3]=ans;					
				}
				cnt0=cnt1=0;
			}
		}
		p^=1;
		m/=3;
	}
	printf("%d",f[p^1][1]);
	return 0;
}

---

## 作者：_wsq_ (赞：0)

我们记 $num_{i,j}$ 为操作到序列只剩 $3^i$ 个元素时第 $j$ 位的值，$dp_{i,j}$ 表示改变这一位置的值的最小代价。初始时，$num_{n,i}=a_i$，$dp_{n,i}=1$。

根据题意，$num_{i,j}$ 等于 $num_{i+1,3j-2}$，$num_{i+1,3j-1}$，$num_{i+1,3j}$ 这三个数中更多的那一个。然后若 $num_{i+1,3j-2}=num_{i+1,3j-1}=num_{i+1,3j}$，那么改变 $num_{i,j}$ 的值就需要改变这三个值中的两个，所以 $dp_{i,j}=dp_{i+1,3j-2}+dp_{i+1,3j-1}+dp_{i+1,3j}-\max(dp_{i+1,3j-2},dp_{i+1,3j-1},dp_{i+1,3j})$；否则我们找到和 $num_{i,j}$ 相同的两个值，这两个值改变其中一个即可（如 $num_{i+1,3j-2}=num_{i+1,3j-1}=0$，$num_{i+1,3j}=1$，则 $dp_{i,j}=\min(dp_{i+1,3j-2},dp_{i+1,3j-1})$）。

答案为 $dp_{0,1}$。

代码：

```cpp
#include <iostream>
#include <cstring>
#include <set>
#include <algorithm>
#include <utility>
#include <cmath>
using namespace std;
#define maxn 1600005
#define int long long
int n,num[15][maxn],dp[15][maxn];
string s;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>s;
    for(int i=1;i<=pow(3,n);i++){
        num[n][i]=s[i-1]-'0';
        dp[n][i]=1;
    }
    for(int i=n-1;~i;i--){
        for(int j=1;j<=pow(3,i);j++){
            if(num[i+1][3*j-2]+num[i+1][3*j-1]+num[i+1][3*j]>1){
                num[i][j]=1;
            }
            else{
                num[i][j]=0;
            }
            if(num[i+1][3*j-2]+num[i+1][3*j-1]+num[i+1][3*j]==0||num[i+1][3*j-2]+num[i+1][3*j-1]+num[i+1][3*j]==3){
                dp[i][j]=dp[i+1][3*j-2]+dp[i+1][3*j-1]+dp[i+1][3*j]-max(dp[i+1][3*j-2],max(dp[i+1][3*j-1],dp[i+1][3*j]));
            }
            else{
                dp[i][j]=0x3f3f3f3f;
                if(num[i+1][3*j-2]==num[i][j]){
                    dp[i][j]=dp[i+1][3*j-2];
                }
                if(num[i+1][3*j-1]==num[i][j]){
                    dp[i][j]=min(dp[i][j],dp[i+1][3*j-1]);
                }
                if(num[i+1][3*j]==num[i][j]){
                    dp[i][j]=min(dp[i][j],dp[i+1][3*j]);
                }
            }
        }
    }
    cout<<dp[0][1];
    return 0;
}
```

---

## 作者：Tairitempest (赞：0)

## [ABC391E] Hierarchical Majority Vote
我们可以通过递归获得这个字符串的属性值。记录每个子串的左端点和长度。如果长度为 $1$，那么显而易见，$1$ 的属性值是 $1$，$0$ 的属性值是 $0$。否则按题目要求分割子串并记录其三个子串的属性值。如果三个属性值中 $1$ 超过 $2$ 个，就意味着该子串属性值为 $1$，否则为 $0$。这样即可得到属性值。

按照相似的思想计算转换代价。我们可以通过递归获得这个字符串的转换代价。如果长度为 $1$，那么显而易见，字符与属性值相同则转换代价为 $0$，否则为 $1$。否则按题目要求分割子串并记录其三个子串的转换代价，求其中最小的两个之和即可（也可以通过总和减去最大值来计算）。

复杂度 $O(3^NN)$，足以通过本题。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll cnt0,cnt1,N,l,power=1;
string s;
ll check(ll lft,ll p){
	if(p==1) return s[lft]-48;
	ll c=p/3;
	ll res=check(lft,c)+check(lft+c,c)+check(lft+c+c,c);
	if(res>=2) return 1;
	else return 0;
}
ll check0(ll lft,ll p){
	if(p==1) return s[lft]-48;
	ll c=p/3;
	ll res1=check0(lft,c);
	ll res2=check0(lft+c,c);
	ll res3=check0(lft+c+c,c);
	return res1+res2+res3-max({res1,res2,res3});
}
ll check1(ll lft,ll p){
	if(p==1) return 49-s[lft];
	ll c=p/3;
	ll res1=check1(lft,c);
	ll res2=check1(lft+c,c);
	ll res3=check1(lft+c+c,c);
	return res1+res2+res3-max({res1,res2,res3});
}
int main(){
	cin>>N>>s;
	l=s.length();
	for(int i=1;i<=N;i++) power*=3;
	ll res=check(0,power);
	if(res==0) cout<<check1(0,power)<<endl;
	else cout<<check0(0,power)<<endl;
	return 0;
}
```

---

## 作者：Chenyichen0420 (赞：0)

## 思路分析

不难发现，这个不断合并的过程非常像是一棵树，因此可以用树形 DP 做。

具体的，我们将他合并的过程对应的树建出来，$dp_{p,0}$ 表示 $p$ 位置值为 $0$ 的最少操作次数，$dp_{p,1}$ 类似。

对于叶子结点，其初始值为其对应的位置的 $0/1$ 值取反者为 $1$，也就是不一样的初值为 $1$，一样的为 $0$。

假设 $p$ 的三个子节点编号分别为 $id_{0/1/2}$。那么有：

$dp_{p,0}=\min(dp_{id_0,0}+dp_{id_1,0}+dp_{id_2,0},dp_{id_0,1}+dp_{id_1,0}+dp_{id_2,0},dp_{id_0,0}+dp_{id_1,1}+dp_{id_2,0},dp_{id_0,0}+dp_{id_1,0}+dp_{id_2,1})$；

$dp_{p,1}=\min(dp_{id_0,1}+dp_{id_1,1}+dp_{id_2,1},dp_{id_0,0}+dp_{id_1,1}+dp_{id_2,1},dp_{id_0,1}+dp_{id_1,0}+dp_{id_2,1},dp_{id_0,1}+dp_{id_1,1}+dp_{id_2,0})$。

显然嘛，合并规则就是这样的。然后就没了。应该不会有~~杂鱼~~人不会算三等分点的位置吧？想推式子的就推嘛，不想推得拿长度去加一个道理。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int>son[4782970];
int n,vl[4782970][2],nid; string s;
inline int build(int p,int l,int r){
	if(l==r){
		vl[p][s[l-1]^49]=1;
		return s[l-1]^48;
	}
	int id[3]={0},sm;
	son[p].emplace_back(id[0]=++nid);
	sm+=build(nid,l,((l-1)*2+r)/3);
	son[p].emplace_back(id[1]=++nid);
	sm+=build(nid,((l-1)+r*2)/3+1,r);
	son[p].emplace_back(id[2]=++nid);
	sm+=build(nid,((l-1)*2+r)/3+1,((l-1)+r*2)/3);
	vl[p][1]=min({
		vl[id[0]][1]+vl[id[1]][1]+vl[id[2]][1],
		vl[id[0]][1]+vl[id[1]][1]+vl[id[2]][0],
		vl[id[0]][1]+vl[id[1]][0]+vl[id[2]][1],
		vl[id[0]][0]+vl[id[1]][1]+vl[id[2]][1]
	});
	vl[p][0]=min({
		vl[id[0]][0]+vl[id[1]][0]+vl[id[2]][0],
		vl[id[0]][0]+vl[id[1]][0]+vl[id[2]][1],
		vl[id[0]][0]+vl[id[1]][1]+vl[id[2]][0],
		vl[id[0]][1]+vl[id[1]][0]+vl[id[2]][0]
	});
	return sm>1;
}
signed main(){
	ios::sync_with_stdio(0);
	cin>>n>>s; 
	int t=build(nid=1,1,pow(3,n));
	cout<<vl[1][!t]<<endl;
	return 0; 
}
```

---

## 作者：Colinxu2020 (赞：0)

很典的分治吧，感觉这场 D>E>F。下面称对于一个序列按题意得到的数为伪众数。

记 $f_{i,j}$ 为 $[A_i,A_j)$ 的伪众数，$g_{i,j,x}$ 为将 $[A_i,A_j)$ 修改尽可能少的元素，使得其伪众数为 $x$ 的最小修改元素数量，分类讨论：

1. $f_{i,j}=x$，此时显然 $g_{i,j,x}=0$；
2. $i=j-1$，此时只有一个元素，答案为 $1$（注意这里的优先级比上一个低）；
3. 我们要修改这个区间的伪众数必须修改它分出来的三个区间中的至少两个，因为分出的区间互不干扰，分别求出 $a=g_{i,i+\frac{j-i}3,x},b=g_{i+\frac{j-i}3,j-\frac{j-i}3,x},c=g_{j-\frac{j-i}3,j,x}$，因此答案为 $\min(a+b,a+c,b+c)$。

综上，最终的答案为 $g_{0, 3^N, f_{0, 3^N}\oplus 1}$，复杂度为 $T(n)=3T(n/3)+O(1)$，由主定理可得复杂度为 $\Theta(n)$，严格线性。

---

## 作者：bszhangzheng (赞：0)

比较简单的动态规划。  
考虑如何让结果从零变为一。我们发现只要在 $x\times 3$， $x\times 3-1$ 和 $x\times 3-2$ 中至少有两个数为一即可。考虑递归，一段区间从零变为一的最小变化数量就为：
$$f_{lson}+f_{midson}+f_{rson}-\max(f_{lson},f_{midson},f_{rson})$$  
从一变为零同理。  
代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a[2000005],mi[15]={1};
string s;
int dfs(int x,int dis)
{
	if(dis==n)
	{
		int now=a[x*3]+a[x*3-1]+a[x*3-2];
		if(!now) return 2;
		if(now==1) return 1;
		return 0;
	}
	int a1=dfs(x*3,dis+1),a2=dfs(x*3-1,dis+1),a3=dfs(x*3-2,dis+1);
	int mx=max(a1,max(a2,a3));
	return a1+a2+a3-mx;
}
int dfs2(int x,int dis)
{
	if(dis==n) return (a[x*3]+a[x*3-1]+a[x*3-2])>=2;
	return (dfs2(x*3,dis+1)+dfs2(x*3-1,dis+1)+dfs2(x*3-2,dis+1))>=2;
}
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	for(int i=1;i<=13;i++) mi[i]=mi[i-1]*3;
	cin>>n>>s,s=" "+s;
	for(int i=1;i<=mi[n];i++) a[i]=(s[i]-'0');
	if(dfs2(1,1)) for(int i=1;i<=mi[n];i++) a[i]^=1;
	cout<<dfs(1,1);
	return 0;
}
```

---

