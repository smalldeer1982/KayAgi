# [ABC358C] Popcorn

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc358/tasks/abc358_c

AtCoder Land には $ 1 $ から $ N $ までの番号が付けられた $ N $ 個のポップコーン売り場があります。 売られているポップコーンの味には味 $ 1,2,\dots,M $ の $ M $ 種類がありますが、すべての売り場ですべての味のポップコーンを売っているわけではありません。

高橋君は、それぞれのポップコーン売り場でどの味のポップコーンを売っているかの情報を入手しました。 この情報は $ N $ 個の長さ $ M $ の文字列 $ S_1,S_2,\dots,S_N $ によって表され、$ S_i $ の $ j $ 文字目が `o` であるとき売り場 $ i $ が味 $ j $ のポップコーンを売っていることを、 `x` であるとき売っていないことを示します。 どの売り場も最低 $ 1 $ 種類の味のポップコーンを売っており、どの味のポップコーンも最低 $ 1 $ つの売り場で売られています。

高橋君は全種類のポップコーンを食べたがっていますが、あまり何度も移動はしたくありません。 高橋君がすべての味のポップコーンを購入するためには最低何個の売り場を訪れる必要があるか求めてください。

## 说明/提示

### 制約

- $ N,M $ は整数
- $ 1\leq\ N,M\ \leq\ 10 $
- $ S_i $ は `o` および `x` からなる長さ $ M $ の文字列
- すべての $ i\ (1\leq\ i\leq\ N) $ について、$ S_i $ の中には `o` が $ 1 $ つ以上存在する
- すべての $ j\ (1\leq\ j\leq\ M) $ について、$ S_i $ の $ j $ 文字目が `o` であるような $ i $ が $ 1 $ つ以上存在する
 
### Sample Explanation 1

$ 1 $ つめの売り場と $ 3 $ つめの売り場を訪れることで、すべての味のポップコーンを購入することができます。 $ 1 $ つの売り場ですべての味のポップコーンを購入することはできないので、答えは $ 2 $ です。

## 样例 #1

### 输入

```
3 5
oooxx
xooox
xxooo```

### 输出

```
2```

## 样例 #2

### 输入

```
3 2
oo
ox
xo```

### 输出

```
1```

## 样例 #3

### 输入

```
8 6
xxoxxo
xxoxxx
xoxxxx
xxxoxx
xxoooo
xxxxox
xoxxox
oxoxxo```

### 输出

```
3```

# 题解

## 作者：stripe_python (赞：4)

看数据范围一眼暴搜。

用一个 `vis` 记录种类，`p` 记录摊位跑 dfs 即可，需要回溯。

```cpp
#include <bits/stdc++.h>
#define N 15
using namespace std;

int n, m;
char s[N][N];

int res = INT_MAX;
bool vis[N], tag[N], p[N];

inline bool check() {
	for (int i = 1; i <= m; i++) if (!vis[i]) return false;
	return true;
}

void dfs(int step) {
	if (check()) return res = min(res, step), void();
	for (int i = 1; i <= n; i++) {
		if (p[i]) continue;
		p[i] = true;
		unordered_set<int> st;
		for (int j = 1; j <= m; j++) {
			if (s[i][j] == 'o' && !vis[j]) vis[j] = true, st.emplace(j);
		}
		dfs(step + 1);
		p[i] = false;
		for (int j = 1; j <= m; j++) {
			if (s[i][j] == 'o' && st.count(j)) vis[j] = false;
		}
	}
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> (s[i] + 1);
	dfs(0);
	cout << res;
	return 0;
}
```

---

## 作者：zhujiangyuan (赞：4)

简单 DFS。

对于每个爆米花摊位，都有选和不选两种。分两种情况递归即可。

```cpp
int vis[20];
void dfs (int k, int cnt) {
	if (k == n + 1) { // 边界
		bool flag = 0;
		for (int i = 1; i <= m; i++)
			if (!vis[i]) flag = 1; // 该爆米花没有买
		if (!flag) ans = min (ans, cnt); // 更新答案
		return ;
	}
	for (int i = 1; i <= m; i++)
		vis[i] += (s[k][i] == 'o');
	dfs (k + 1, cnt + 1); // 选
	for (int i = 1; i <= m; i++)
		vis[i] -= (s[k][i] == 'o'); // 回溯
	dfs (k + 1, cnt); // 不选
}
```

最后输出 $ans$。时间复杂度 $O(2^nm)$。

---

## 作者：chen_tim (赞：2)

### 题意
输入 $N$ 行字符串，每行字符串长度都为 $M$。字符串中只包含 o 或 x 两种字符。问至少选出多少行字符串，其每个对应位置上至少有一个字符 o？
### 思路
因为这题的数据范围很小，所以可以采用 DFS 暴力搜索，从选 $1$ 行到选 $N$ 的所有可能，再在每次 DFS 时判断一下算出的结果是否符合要求。
### AC 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n, m, a[15], p, q, f;
char x[15][15];
void dfs(ll hight, ll last){
    if(hight == q + 1){ //递归出口
        char ans[15];
        ll res = 1;
        //判断
        for(ll i = 1; i <= m; i++) ans[i] = x[a[1]][i];
        for(ll i = 2; i <= q; i++){
            for(ll j = 1; j <= m; j++){
                if(x[a[i]][j] != ans[j]) ans[j] = 'o';
            }
        }
        for(ll i = 1; i <= m; i++) if(ans[i] == 'x') res = 0;
        if(res == 1) f = 1; 
        return;
    }
    for(ll i = last + 1; i <= p; i++){
        a[hight] = i;
        dfs(hight + 1, i); //找下一个
    }
}
int main(){
    cin >> n >> m;
    for(ll i = 1; i <= n; i++){
        for(ll j = 1; j <= m; j++){
            cin >> x[i][j];
        }
    }
    for(ll i = 1; i <= n; i++){
        p = n, q = i, f = 0; //n个里面选i个
        for(ll j = 1; j <= 14; j++) a[j] = 0; //清空a数组
        dfs(1, 0);
        if(f == 1){ //找到了
            cout << i;
            return 0;
        }
    }
    return 0;
}
```

---

## 作者：zzhbpyy (赞：2)

## 思路

考虑到 $n\leq10$ 的数据范围，最多只有 $2^{10}$ 种选取方法，使用 dfs 算法枚举所有情况统计答案即可。

## 完整代码

```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,ans=INT_MAX; 
int vis[15];char a[15][15];
void dfs(int aa,int u){//aa表示进行到枚举第aa个数选或不选，u代表已经选了u个摊位
	if(aa>n){
		for(int i=1;i<=m;i++)if(!vis[i])return;
		return void(ans=min(ans,u));
	}
	dfs(aa+1,u);
	for(int i=1;i<=m;i++){
		if(a[aa][i]=='o')vis[i]++;
	}
	dfs(aa+1,u+1);
	for(int i=1;i<=m;i++)if(a[aa][i]=='o')vis[i]--;
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(nullptr),cout.tie(nullptr);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)cin>>a[i][j];
	}
	dfs(1,0);
	cout<<ans;
}
```

---

## 作者：_xdd_ (赞：2)

考虑 dfs。

- 对于第 $i$ 个小吃摊：
	- 判断每种口味是否吃过，若都吃过了更新答案，返回。
	- 否则，遍历每个小吃摊：
		- 对于遍历到的这个小吃摊，我们把每种口味都吃一遍。
		- dfs 遍历到的这个小吃摊（返回第一步）。
		- 回溯。

```cpp
#include<iostream>
using namespace std;
int n,m,tmp,ans=214748367;
char a[15][15];
bool vis[15],f[15];
void dfs(int x){
    bool flag=1;
    for(int i=0;i<m;i++){
        if(!f[i])
            flag=0;
    }
    if(flag){
		ans=min(ans,tmp);
		return;
	}

    for(int i=0;i<n;i++){
        if(!vis[i]){
            int t[15];
            for(int j=0;j<m;j++){
                t[j]=f[j];
            }
            for(int j=0;j<m;j++){
		        if(a[i][j]=='o' && !f[j]){
		            f[j]=1;
		        }
		    }
            vis[i]=1;
            tmp++;
            dfs(i);
            tmp--;
            vis[i]=0;
            for(int j=0;j<m;j++){
                f[j]=t[j];
            }
        }
    }
}
int main(){
    cin >> n >> m;
    for(int i=0;i<n;i++){
        cin >> a[i];
    }
    dfs(0);
    cout << ans;
    return 0;
}
```

---

## 作者：D0000 (赞：1)

枚举。

将每一个 $S_i$ 变成 01 序列（o 为 1），设 $S$ 为它们的集合。

初始答案 $ans=\infty$。

枚举 $S$ 子集设为 $V$，将其中的每一个 $S_i$ 或起来记为 $B$，判断 $B$ 是否全为 1。若 $B$ 全为 $1$ 更新答案 $ans=\min(ans,|V|)$。时间复杂度 $O(2^n\times n)$

代码：

```cpp
#include<cstdio>
int n,m,ans=99;
char c[15];
bool t[15][15];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%s",c);
		for(int j=1;j<=m;j++)t[i][j]=(c[j-1]=='o');
	}
	for(int i=0;i<=(1<<n)-1;i++){
		int non=0;
		for(int j=1;j<=2048;j<<=1)if(i&j)non++;
		if(non>=ans)continue;
		bool b[15];
		for(int j=1;j<=m;j++)b[j]=0;
		for(int j=1;j<=n;j++){
			if((1<<(j-1))&i){
				for(int k=1;k<=m;k++)b[k]|=t[j][k];
				//if(i==5)printf("%d",j);
			}
		}
		bool flag=1;
		for(int j=1;j<=m;j++)if(!b[j])flag=0;
		if(flag)ans=non;
	}
	
	printf("%d",ans);
} 
```

---

## 作者：nightwatch.ryan (赞：1)

### 思路
我们可以用位运算来做这道题目。

首先，将输入的字符串转换为一个数字，如果字符串的第 $i$ 位是 `o`，则将目标数字在二进制下的第 $i$ 位设为 $1$。

接下来，我们枚举所有的组合，我们用 $p$ 来表示当前组合的口味覆盖情况，然后用 $result$ 记录当前组合要走多少个地方。接下来设 $m$ 是口味总数量，如果 $p=2^m-1$，（$2^m-1$ 的二进制表示就是 $m$ 个 $1$，所以这么判断），我们更新最少要去的地方个数，也就是答案。

最后输出答案。
### 代码
```cpp
#include<map>
#include<iostream> 
#define int long long
#define il inline
il int read(){
 int x=0,t=1;char ch=getchar();
 while(ch<'0'||ch>'9'){if(ch=='-')t=-1;ch=getchar();}
 while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
 return x*t;
}
il void write(int x){
 if(x<0){putchar('-');x=-x;}
 if(x>9)write(x/10);
 putchar(x%10+'0');
}
#define rd read()
int n,m,bit[15];
signed main(){
	n=rd,m=rd;
	for(int i=0;i<n;i++){
		std::string s;std::cin>>s;
		int num=0;
		for(int j=0;j<m;j++)
		if(s[j]=='o')num|=(1<<j);			
		bit[i]=num;
	}
	int ans=n,check=(1<<m)-1; 
	for(int i=1;i<(1<<n);i++){
		int p=0,result=0;
		for(int j=0;j<n;j++)
		if(i&(1<<j))p|=bit[j],result++;
		if(p==check)ans=std::min(ans,result);
	}
	write(ans);
}
```

---

## 作者：LuukLuuk (赞：1)

# 题解：AT_abc358_c [ABC358C] Popcorn

### 题目大意

有 $N$ 个商店，所有商店一共卖 $M$ 种东西。具体地，第 $i$ 个商店卖的东西用一个长为 $M$ 字符串表示，其中第 $j$ 个为 `o` 则代表卖，`x` 代表不卖。现在你要确定最少要走几个商店才能买齐这 $M$ 种东西。

数据范围是 $1 \le N,M \le 10$。

--------------------------
### 题解

我们可以从数据范围很容易地想到暴力枚举所选商店。但是处理字符串较为麻烦，所以我们可以压缩状态，用一个二进制串表示它，卖的为 $1$，不卖的为 $0$。统计所卖物品种类数时全部或一遍就行了，买齐的情况就是全部是 $1$。

同样的，我们也可以类似地压缩我们所枚举商店的方案，选择的为 $1$，没有选择的为 $0$。最优解就是买齐的情况下 $1$ 的个数最少的解。

完整代码：
```cpp

#include <algorithm>
#include <cstdio>
using namespace std;

char s[110][110];
int num[110];
int cnt, ans;
int n, m, t;

int main() {
	ans = 0x3f3f3f3f;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		scanf("%s", s[i] + 1);
		for (int j = 1; j <= m; ++j) {//将输入字符串转化为二进制 
			num[i] <<= 1;
			if (s[i][j] == 'o') {//卖的话就是1 
				num[i] += 1; 
			}
		} 
	}
	for (int i = 0; i <= (1 << n) - 1; ++i) {
		cnt = 0;//当前情况所访问的商店个数 
		t = 0;//所买到的物品种数 
		for (int j = 0; j < n; ++j) {//枚举商店（二进制是从0开始的，所以从0开始枚举） 
			if (i & (1 << j)) {//访问了该商店 
				cnt++;//商店个数加1 
				t |= num[j + 1];//统计时或一下（有的不管，没有的加上） 
			}
		}
		if (t == ((1 << m) - 1)) {//齐了就是m个1 
			ans = min(ans, cnt);//更新最小值 
		}		
	}
	printf("%d", ans);
	return 0;
}

```

---

## 作者：OPEC (赞：1)

# [[ABC358C] Popcorn](https://www.luogu.com.cn/problem/AT_abc358_c)

这题看见 $n\le10$ 时，就能想到 $O(2^n)$ 暴力。枚举每个摊位选不选，然后判断可行不可行，取最小值即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define int long long
const int N=10+10,M=2e6+10;
const int INF=0x3f3f3f3f3f3f3f3f;
const int P=998244353;//3221225477
int n,m,ans=INF;
string s[N];
int a[N];
bool check()
{
	int p[N];
	memset(p,0,sizeof(p));
	for(int i=0;i<n;i++)
	{
		if(a[i])
		{
			for(int j=0;j<m;j++)
			{
				if(s[i][j]=='o')
					p[j]=1;
			}
		}
	}
	for(int i=0;i<m;i++)
	{
		if(!p[i])
			return 0;
	}
	return 1;
}
void dfs(int d,int y)
{
	if(d==n)
	{
		if(check())
			ans=min(ans,y);
		y--;
		return;
	}
	for(int i=0;i<=1;i++)
	{
		a[d]=i;
		if(i==1)
			y++;
		dfs(d+1,y);
	}
	y--; 
}
signed main()
{
	fst
	cin>>n>>m;
	for(int i=0;i<n;i++)
	{
		cin>>s[i];
	}
	dfs(0,0);
	cout<<ans;
	return 0;
}

```

---

## 作者：kkxacj (赞：1)

#### 思路

发现 $n,m \le 10$，考虑爆搜。

对于每一个爆米花亭，考虑买与不买，然后如果每一种爆米花，我选的爆米花亭至少有一个卖，那么就合法，去最小值即可。


赛时赶时间，打的有点急，码丑勿喷。

**code**
```cpp
#include<bits/stdc++.h>
using namespace std;
namespace IO
{
	template<typename T>
	void read(T &_x){_x=0;int _f=1;char ch=getchar();while(!isdigit(ch)) _f=(ch=='-'?-1:_f),ch=getchar();while(isdigit(ch)) _x=_x*10+(ch^48),ch=getchar();_x*=_f;}
	template<typename T,typename... Args>
	void read(T &_x,Args&...others){Read(_x);Read(others...);}
	const int BUF=20000000;char buf[BUF],top,stk[32];int plen;
	#define pc(x) buf[plen++]=x
	#define flush(); fwrite(buf,1,plen,stdout),plen=0;
	template<typename T>inline void print(T x){if(!x){pc(48);return;}if(x<0) x=-x,pc('-');for(;x;x/=10) stk[++top]=48+x%10;while(top) pc(stk[top--]);}
}
using namespace IO;
int n,m,ans = 20,v[20];
string s[20],s1[20];
void dfs(int x,int y)
{
	if(y >= ans) return;
	if(x > n)
	{
		for(int i = 1;i <= m;i++)
		{
			int l = 0;
			for(int j = 1;j <= y;j++)
			{
				if(s1[j][i-1] == 'o')
				{
					l = 1;
					break;
				}
			}
			if(!l) return;
		}
		ans = y;
	}
	s1[y+1]=s[x],dfs(x+1,y+1);
	dfs(x+1,y);
}
signed main()
{
	read(n),read(m);
	for(int i = 1;i <= n;i++) cin >> s[i];
	dfs(1,0);
	cout << ans;
	return 0;
}

```

---

## 作者：Cosine_Func (赞：1)

十分钟场切的 dfs 水题。

数据范围极小，考虑暴力。先存下爆米花的编号，在每次搜索过程中有选择当前店铺和不选择两种决策，如果选择，那么将计数数组中含有的对应爆米花加一，然后搜索完后回溯（减一）。搜完后检验是否包括所有爆米花，如果是，更新答案。

dfs 部分如下：
```cpp
int n,m,ans=0x7fffffff;
char c[N][N];
bool b[N];
int vis[N];
void dfs(int j,int k){
	if(j>n){
		for(int i=1;i<=m;i++)
			if(b[i] and vis[i]==0)
				return;
		ans=min(ans,k);
		return;
	}
	dfs(j+1,k);
	for(int i=1;i<=m;i++)
		if(c[j][i]=='o')
			vis[i]++;
	dfs(j+1,k+1);
	for(int i=1;i<=m;i++)
		if(c[j][i]=='o')
			vis[i]--;
}
```
主函数很简单，就不放了。放个[代码链接](https://atcoder.jp/contests/abc358/submissions/54577680)。

---

## 作者：luobotianle (赞：1)

首先由于 $m \le 10$，所以我们可以用一个二进制数来记录每个摊位出售的爆米花种类；

然后发现 $n \le 10$，所以直接搜就行了。这里使用了 STL 中的 `next_permutation` 来实现全排列。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int a[15];
int b[15];
int ans=INT_MAX;
int n,m;
string s;
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)a[i]=i;
	for(int i=1;i<=n;i++){
		cin>>s;
		for(int j=0;j<s.size();j++){
			if(s[j]=='o')b[i]|=(1<<j);
		}
	}
	do{
		int now=0;
		for(int i=1;i<=n;i++){
			now|=b[a[i]];
			if(now==(1<<m)-1){
				ans=min(ans,i);
				break;
			}
		}
	}while(next_permutation(a+1,a+1+n));
	cout<<ans;
	return 0;
}
```

---

## 作者：yegengghost (赞：1)

一看数据范围，直接暴力好吧。

这里的代码暴力表示所有可能的摊位组合，并检查每种组合是否能覆盖所有爆米花口味。

每一次循环看下当前组合答案是否最小，之后再把对答案贡献最小的答案更新即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,ans=INT_MAX;
char ch[15][15];
int read()
{
    int f=1,x=0;char ch;
    do{ch=getchar();if(ch=='-')f=-1;}while(ch<'0'||ch>'9');
    do{x=x*10+ch-'0';ch=getchar();}while(ch>='0'&&ch<='9');
    return f*x;
}
int main()
{
	n=m=read();
	for(int i=1;i<=n;i++)
		scanf("%s",ch[i]);
	for(int i=1;i<(1<<n);i++)
	{
		int k[15],num=0;
		bool flag=1;
		//k用来标记是否所有口味都被当前的摊位组合覆盖。 
		//num为当前组合中选择摊位的数量。 
		//flag判断当前情况是否成立，如果是变更新最小答案。 
		for(int j=0;j<m;j++)
			k[j]=0;
		for(int j=1;j<=n;j++)
			if((1<<(j-1))&i)
			{
				num++;
				for(int l=0;l<m;l++)
					if(ch[j][l]=='o')
						k[l]=1;
			}
		for(int j=0;j<m;j++)
			if(k[j]==0)
			{
				flag=0;
				break;
			}
		if(flag)
			ans=min(ans,num);
	}
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：lucasincyber (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc358_c)
## 思路
我用的是 dfs 搜索。每一次选若干个摊位去买（因为要最优，所以每一个摊位的每一种口味都要买），最后判断是否满足条件。答案就是所有的方案中的最优方案。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

int n, m, ans = 0x3f3f3f3f, mt;
int vis[15];
bool vis1[15];
string s[15];

void dfs(int u, int k)
{
	int cnt = 0;
	for (int i = 0; i < m; i++)
		if (vis[i] > 0) cnt++;
	if (cnt >= mt)
	{
		ans = min(ans, k);
		return;
	}
	for (int i = u + 1; i <= n; i++)
	{
		int tmp = 0;
		for (int j = 0; j < s[i].size(); j++)
			if (s[i][j] == 'o')
				vis[j]++;
		dfs(i, k + 1);
		for (int j = 0; j < s[i].size(); j++)
			if (s[i][j] == 'o') vis[j]--;
	}
}

int main()
{
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
	{
		cin >> s[i];
		for (int j = 0; j < s[i].size(); j++)
			if (s[i][j] == 'o')
				vis1[j] = true;
	}
	for (int i = 0; i < m; i++)
		if (vis1[i]) mt++;
	dfs(0, 0);
	cout << ans;
	return 0;
}
```

---

## 作者：OIer_Tan (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc358_c)

经典搜索/状压 + `bitset` 题。

## 题意

有 $n$ 个长度为 $m$ 且只含有 `o` 和 `x` 的字符串，求最小选几个之后所有对应位置都有至少一个 `o`。

## 思路

数据范围 $1\le n,m\le10$，考虑状压。

然后再用 `bitset` 按位或合并答案，总时间复杂度 $O(2^{n}nm)$。

## 代码

```cpp
#include <bits/stdc++.h>

#ifndef CRT
#define endl '\n'
#endif

using namespace std ;

typedef long long ll ;
typedef unsigned long long ull ;
typedef long double ld ;

const ll N = 15 ;

bitset <N> s [N] ;

ll n , m , ans = 1e18 ;

int main ()
{
	ios::sync_with_stdio ( 0 ) ;
	cin.tie ( 0 ) ;
	cout.tie ( 0 ) ;
	cin >> n >> m ;
	for ( ll i = 1 ; i <= n ; i ++ )
	{
		string a ;
		cin >> a ;
		for ( ll j = 0 ; j < m ; j ++ )
		{
			if ( a [j] == 'o' )
			{
				s [i] [j] = 1 ;
			}
		}
	}
	for ( ll i = ( 1 << n ) - 1 ; i ; i -- )
	{
		bitset <N> andi ;
		ll cnt = 0 ;
		for ( ll j = 1 ; j <= n ; j ++ )
		{
			if ( ( i >> ( j - 1 ) ) & 1 )
			{
				andi = andi | s [j] ;

				cnt ++ ;
			}
		}
		if ( andi.count () == m )
		{
			ans = min ( ans , cnt ) ;
		}
	}
	cout << ans << endl ;
	
	return 0 ;
}
```

---

## 作者：qhr2023 (赞：0)

## 题意

有 $N$ 个摊位，它们有 $M$ 种不同口味的爆米花，给出每个摊位的销售信息，求至少要去多少个摊位才能买到所有口味的爆米花。

## 思路

数据范围太小了，直接暴力枚举所有可能。每次搜索，可以买，可以不买，$x$ 是到第几个摊位，$y$ 是买了几次，$t$ 存在哪几个摊位买了，$vis$ 标记，每搜完一种情况，检查是否符合条件，如果符合再和结果取最小值。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, m, ans=0x3f3f3f3f, t[11], vis[11];
char a[11][11];
void dfs(int x, int y){
	if(x==n){
		memset(vis, 0, sizeof vis);
		for(int i=0; i<y; i++)
			for(int j=0; j<m; j++)
				if(a[t[i]][j]=='o')
					vis[j]=1;
		for(int j=0; j<m; j++)
			if(!vis[j])
				return ;
		ans=min(ans, y);
		return ;
	}
	t[y]=x;
	dfs(x+1, y+1);
	dfs(x+1, y);
}
int main(){
	cin >> n >> m;
	for(int i=0; i<n; i++)
		cin >> a[i];
	dfs(0, 0);
	cout << ans;
	return 0;
}
```

---

## 作者：T_TLucas_Yin (赞：0)

遇到这种题，首先看数据范围。

$$1\le n\le 10$$

众所周知，在 $10$ 个不同元素中任意选择，共有 $2^{10}=1024$ 种选法（每个元素都有选或不选两种情况）。这个数量很小，意味着我们可以直接枚举所有不同摊位的选择情况，对于每种情况，把在选中的摊位上能买到的所有爆米花种类记录下来。如果发现这些种类包含了所有的爆米花，就更新选中的最少摊位数。枚举完所有的情况后，输出最少的摊位数即可。

注意本题中一个摊位都不选的情况肯定是不可能的，所以不用考虑。对于枚举的过程，由于不需要任何剪枝，我们可以直接用循环按顺序枚举 $1$ 到 $2^n-1$ 的所有整数，用每个整数的二进制位来代表摊位的选择情况即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,minn;
char c[15][15];
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) cin>>c[i][j];//摊位出售情况
	int q=pow(2,n);
	int minn=0x3f3f3f3f;
	for(int i=1;i<q;i++){//枚举范围内所有情况
		int p=i,cnt=0;
		char f[15]={0};
		for(int j=1;j<=n;j++){//查看当前情况
			if(p&1){
				cnt++;
				for(int k=1;k<=m;k++) if(c[j][k]=='o') f[k]='o';//把每个摊位能买的种类叠加起来
			}
			p>>=1;//看下一位
		}
		bool flag=1;
		for(int j=1;j<=m;j++) if(f[j]!='o') flag=0;
		if(flag) minn=min(minn,cnt);//能买全种类了就更新答案
	}
	cout<<minn;
	return 0;
}
```

---

## 作者：chenlongli (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc358_c)
### 思路
我们可以用枚举全排列的方式枚举每分钟拿第几个货架的爆米花，但是和枚举全排列不同的是，每拿一种爆米花，我们都要判断是否已经达成条件，如果分钟已经超过了爆米花总数或者已经达成条件，我们就回溯。
### code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int g=100,y;
char a[11][11];
int k[11];
int p[11];
int q[10000000][11],zc=0;
void dfs(int h)
{
	int qq=0;
	for (int i=0;i<m;i++)
	{
	    //cout<<k[i]<<" ";
		if (k[i]==0)
		{
			qq=1;
			//break;
		}
	}
	//cout<<h<<endl;
	if (qq==0)
	{
		g=min(g,h);
		return;
	}
	if (h>=n)
	{
		return;
	}
	for (int i=0;i<n;i++)
	{
		if (p[i]==0)
		{
			p[i]=1;
			y=y+1;
			for (int j=0;j<m;j++)
			{
				q[zc][j]=k[j];
				if (a[i][j]=='o')
				{
					k[j]=1;
				}
			}
			int ls=zc;
			zc=zc+1;
			dfs(h+1);
			for (int j=0;j<m;j++)
			{
				k[j]=q[ls][j];
			}
			y=y-1;
			p[i]=0;
		}
	}
	return;
}
int main()
{
	cin>>n>>m;
	for (int i=0;i<n;i++)
	{
		for (int j=0;j<m;j++)
		{
			cin>>a[i][j];
		}
	}
	dfs(0);
	cout<<g<<endl;
}
```

---

## 作者：201012280925LSY (赞：0)

## 题意
有 $N$ 个店铺，同时有 $M$ 种商品。现在给出每个店铺出售的商品情况，求最少要去多少个店铺，才能买下所有的商品。

## 思路
观察数据范围 $N\le10$，$M\le10$，所以我们可以直接暴力枚举每一种去商店的组合，最后从所有组合求出合法的组合并且取最小值。

所以应该如何枚举呢？显然我们可以用递归枚举，但是这里提供另一种方法：二进制枚举。

放在这道题中，二进制枚举通过把整数转化成二进制数，之后每一个数位如果是 $0$，表示不取，是 $1$ 表示取。这个方法的正确性读者可以自行验证。

具体见代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,answer=1e18,temp;
string a[15];
bool cmp[15];
string zhuan(long long ans)//转化成二进制数
{
	temp=0;//记录选中了几个商店
	string st="";
	while(ans)
	{
		temp+=ans%2;
		st=char(ans%2+48)+st;
		ans/=2;
	}
	while(st.size()<n)st='0'+st;//把位数补充完整
	return st;
}
int main()
{
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=(1<<n)-1;i++)
	{
		string st=zhuan(i);
//		cout<<st<<"\n";
		for(int j=1;j<=m;j++)cmp[j]=0;//清零
		for(int j=0;j<st.size();j++)
		{
			if(st[j]=='1')//选中
			{
				for(int k=0;k<m;k++)//记录能够买的商品
				{
					if(a[j+1][k]=='o')cmp[k+1]=1;
				}
			}
		}
		long long sum=0;
		for(int j=1;j<=m;j++)sum+=cmp[j];
		if(sum==m)answer=min(answer,temp);//满足所有商品都能买到
	}
	printf("%lld",answer);
	return 0;
}

```

---

## 作者：xzz_0611 (赞：0)

[题目传送门](/problem/AT_abc358_c)
## 题目翻译
在 AtCoder 乐园里，有 $N$ 个爆米花摊位，有 $M$ 种不同口味的爆米花，第 $i$ 种爆米花的编号为 $i$。

高桥知道每个摊位售卖的爆米花有哪些，用 $N$ 个长度为 $M$ 的字符串表示 $S$，若 $S_i$ 为：
- `o`：说明这个摊位出售第 $i$ 种爆米花。
- `x`：说明这个摊位不出售第 $i$ 种爆米花。

保证每个摊位至少出售一种爆米花，每种爆米花至少会在一个摊位中出售。

请问高桥最少去多少个摊位才能买到所有种类的爆米花。
## 题目分析
可以用 dfs 解决。

为了使高桥去的摊位尽可能小，这个摊位的所有种类的爆米花他肯定都要买（如果已经买了的可以不用），如果用字符串 $a$ 表示高桥可以买到的爆米花的种类，那么对于任意一个摊位，若 $S_i$ 为：
- `o`：那么将 $a_i$ 设置为 `o`。
- `x`：不进行改动。

当 $a$ 的全部字符都是 `o` 时就刷新一遍答案，最后输出即可。
## Code
```cpp
#include<iostream>
using namespace std;
int n,m,ans=10;
string str[10];
void dfs(int x,int num,string s) {//dfs 深搜
	if(x>=n) return;
	bool flag=true;
	string ss=s;
	for(int i=0;i<m;++i) {
		if(str[x][i]=='o') s[i]='o';
		if(s[i]=='x') flag=false;
	}
	if(flag) ans=min(ans,num+1);//刷新答案
	else dfs(x+1,num+1,s);//如果已经达成目标了就不需要继续去其他摊位
	dfs(x+1,num,ss);//如果不到这个摊位去买
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=0;i<n;++i) cin>>str[i];
	dfs(0,0,"xxxxxxxxxx");//初始要全部是x
	cout<<ans;
	return 0;
}
```

---

## 作者：int_stl (赞：0)

一道子集枚举题。

我们用 $N$ 位二进制数来表示高桥买了哪些摊位的爆米花，然后检查一下，如果合法，答案取二进制数 $1$ 的个数的最小值即可。

时间复杂度 $O(2^N \times (N+M))$。

代码如下：

```cpp
int n, m;
string str[13];
int popcount(int x) {
	if (x == 0) return 0;
	return popcount(x >> 1) + (x & 1);
}
int main() {
	cin >> n >> m;
	FORL(i, 1, n, 1) {
		cin >> str[i];
	}
	int ans = 19;
	FORL(i, 1, (1 << n) - 1, 1) {
		string s = "";
		FORL(j, 1, m, 1) s += " ";
		FORL(j, 0, n - 1, 1) {
			if ((i >> j) & 1) {
				int now = n - j;
				FORL(k, 0, m - 1, 1) {
					if (str[now][k] == 'o') {
						s[k] = 'o';
					}
				}
			}
		}
		int cnt = 0;
		FORL(j, 0, m - 1, 1) {
			if (s[j] == 'o') ++cnt;
		}
		if (cnt == m) {
			ans = min(ans, popcount(i));
		}
	}
	write(ans);
}
```

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc358_c)

## 思路

看到 $1\le N,M\le 10$，很容易想到搜索。

读入数据后直接进行搜索，每次搜索枚举每个店，如果这个店来过就跳过，否则判断如果这个店出售某种糖果就标记为这个点的编号，**不要覆盖之前的标记**。之后进行下一轮搜索。搜索时传的是总共买到的口味数和当前走过几个店。

回溯时删除来过此店的标记和此店买到糖果的标记即可。如果总共买到的口味数等于 $M$ 说明买完了，更新最小值。**剪枝**：如果当前走的店铺比最小值大，跳出。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
char readc(){
	char c=getchar();
	while(c=='\n'||c=='\r'||c==' ')c=getchar();
	return c;
}
const int N=20;
int n,m,ans=1e9;//ans 记得赋个极大值。
bool a[N][N],ok[N];
int f[N];
void dfs(int cnt,int cho){
	if(cho>ans)return ;//剪枝。
	if(cnt==m){
		ans=min(ans,cho);
		return ;
	}
	for(int i=1;i<=n;++i){
		if(ok[i])continue;
		ok[i]=1;//标记来过。
		int num=0;
		for(int j=1;j<=m;++j){
			if(f[j])continue;//买过这种不再买。
			else if(a[i][j]){//没买过且有售就标记。
				f[j]=i;
				++num;
			}
		}
		dfs(cnt+num,cho+1);
		ok[i]=0;//删除来过的标记和糖果的标记。
		for(int j=1;j<=m;++j)if(f[j]==i)f[j]=0;
	}
    return ;
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			char c=readc();
			if(c=='o')a[i][j]=1;
		}
	}
	dfs(0,0);
	cout<<ans;
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/162289291)

---

