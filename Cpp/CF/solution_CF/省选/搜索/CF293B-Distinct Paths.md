# Distinct Paths

## 题目描述

You have a rectangular $ n×m $ -cell board. Some cells are already painted some of $ k $ colors. You need to paint each uncolored cell one of the $ k $ colors so that any path from the upper left square to the lower right one doesn't contain any two cells of the same color. The path can go only along side-adjacent cells and can only go down or right.

Print the number of possible paintings modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 样例 #1

### 输入

```
2 2 4
0 0
0 0
```

### 输出

```
48
```

## 样例 #2

### 输入

```
2 2 4
1 2
2 1
```

### 输出

```
0
```

## 样例 #3

### 输入

```
5 6 10
0 0 0 0 0 0
0 0 0 0 0 0
0 0 0 0 0 0
0 0 0 0 0 0
0 0 0 0 0 0
```

### 输出

```
3628800
```

## 样例 #4

### 输入

```
2 6 10
1 2 3 4 5 6
0 0 0 0 0 0
```

### 输出

```
4096
```

# 题解

## 作者：naive_wcx (赞：9)

# Description
给出$n×m(n,m≤1000)$的格子和$k(k≤10)$种颜色，一些格子有颜色，一些格子没有。询问有多少种染色方案可以使得从左上角走到右下角的每一条道路都没有相同的颜色。
# Solution
首先可以意识到，$n,m≤1000$的范围是假的。。

因为当$n+m-1>k$时，显然无解。

那么$n,m$的范围就很小了，可以考虑搜索+剪枝。

剪枝有两种：

$1.$可行性剪枝，当剩余颜色比步数少就返回。

$2.$对于每一个格子，如果没有放过颜色，那么从剩下的颜色中随便放一种本质是相同的，计算一次后直接累加答案即可。

一些细节：

第一个剪枝很好想但是很重要。。。没加之前T了一发。。

判断当前颜色状态用状压实现。

可以预处理出$log$的值，取模用减法等方法卡常数。

~~然后就卡到了62ms……~~

# Code
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
const int mod = 1e9 + 7;
int lg[1030], n, m, k, a[20][20], f[20][20], v[20];

int dfs(int x, int y) {
    if(y == m + 1) x++, y = 1;
    if(x == n + 1) return 1;
    int s = f[x - 1][y] | f[x][y - 1], calc = -1, ret = 0;
    int S = ~s & ((1 << k) - 1);
    if(n + m - x - y + 1 > lg[S]) return 0;
    for(int tmp = 0; tmp < k; tmp++) if(S & (1 << tmp)) {
        if(a[x][y] == 0 || a[x][y] == tmp + 1) {
            v[tmp + 1]++;
            f[x][y] = s | (1 << tmp);
            if(v[tmp + 1] == 1) {
                if(calc == -1) calc = dfs(x, y + 1);
                ret += calc;
            }
            else ret += dfs(x, y + 1);
            if(ret >= mod) ret -= mod;
            v[tmp + 1]--;
        }            
    }
    return ret;
}

int main()
{
    for(int i = 1; i < 1024; i++) lg[i] = lg[i >> 1] + (i & 1);
    scanf("%d %d %d", &n, &m, &k);
    if(n + m - 1 > k) {
        puts("0");
        return 0;
    }
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++) {
            scanf("%d", &a[i][j]);
            v[a[i][j]]++;
        }
    printf("%d\n", dfs(1, 1));
    return 0;
}
```

---

## 作者：e4fsrc2e4fsrc2 (赞：5)

## [Distinct Paths](https://www.luogu.com.cn/problem/CF293B)
## 思路分析
可以发现，当 $n+m-1>k$ 时，显然无解，经过的颜色肯定超过了两种及其以上的颜色。
1. 合法的 $n,m$ 范围比较小，可以使用搜索。
2. 使用状压的方式记录当前使用的颜色，$f_{x,y}$ 表示搜索到 $(x, y)$ 使用的颜色集合。

**剪枝优化**：
1. 可行性剪枝：剩下的步数大于可用的颜色数，结束。
2. 排除等效冗余：如果当前有 $k$ 种颜色还未使用，对于空白格子染任何一种染色的贡献都是相同的，只需要选择一种颜色计算，其他颜色累加即可。

## AC 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
#define R register int
using namespace std;
const int N=11,mod=1e9+7;
int mp[N][N],f[N][N],n,m,k;
int vis[N];
int dfs(int x,int y){
	if(y>m)x++,y=1;
	if(x>n)return 1;
	int now=f[x-1][y]|f[x][y-1],cnt=k-__builtin_popcount(now);
	if(cnt<n+m-x-y+1)return 0;
	int rt=-1,ans=0;
	for(R i=1; i<=k; i++){
		if((mp[x][y]&&mp[x][y]!=i)||((now>>i-1)&1))continue;
		f[x][y]=now|(1<<i-1);
		vis[i]++;
		if(vis[i]==1){
			if(rt==-1)rt=dfs(x,y+1);
			ans=(ans+rt)%mod;
		}else ans=(ans+dfs(x,y+1))%mod;
		ans%=mod;
		vis[i]--;
	}
	return ans;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>m>>k;
	if(n+m-1>k)return cout<<0,0;
	for(R i=1; i<=n; i++)
		for(R j=1; j<=m; j++)
			cin>>mp[i][j],vis[mp[i][j]]++;
	cout<<dfs(1,1);
	return 0;
}

```

---

## 作者：Eraine (赞：4)

编号：CF293B

tag：状态压缩，dp

难度：*2700

题解区里似乎都是搜索的题解，这里提供一篇状态压缩 + dp 的题解。

请勿将此题解理解为轮廓线 dp，本文涉及的 dp 状态与轮廓线没有关系。

按照搜索正解的思路，在图中从上到下从左到右按格转移。考虑限制条件，即从 $(1,1)$ 到 $(x,y)$ 的任意一条路径都满足不存在两个相同颜色的节点。转化一下条件，也就是若 $(x,y)$ 染色为 $col$，那么 $r=[1\dots x],c=[1\dots y]$ 的所有格子除了 $(x,y)$ 均不能染色为 $col$。考虑在转移的时候如何利用这个条件。之前染色过的格子（即 $r=[1\dots c-1],c=[1\dots m]$ 和 $r=x,c=[1\dots y-1]$）中所有染色会 $col$ 的格子构成的集合 $S$ 会对接下来的格子产生影响，所有 $x\in[x_{S_i},m]$ 的格子都不能被染色为 $col$。贪心的想，只需要考虑 $\min x_{S_i}$ 即可。所以对于每一个颜色，维护其出现过的 $x$ 最小的位置即可。状态 $S$ 表示为各个颜色维护 $x$ 最小的位置的集合，这里由于 $S$ 过大，建议使用 $\text{unordered\_map}$。其他写法与普通状压 dp 一样。

实现方式请参考 $\color{red}{\text{tomasz.kociumaka}}$ 的提交记录：[submission](https://codeforces.com/contest/293/submission/3605831)。

若有疑问和错误请指出，虚心接受您的意见。

---

## 作者：GFyyx (赞：3)

## 解题思路
深搜 + 状压。

可以发现，当 $n+m-1>k$ 时，经过的颜色超过了两种及其以上的颜色。

实际上，存在合法解的 $n,m \leq 10$，支持 DFS。

### 剪枝
利用颜色 $col_i$ 与颜色 $col_j$ 的先后次序相反，本质上性质相同，搜索时如果搜到是第一次时计算，其他时候累加即可。

### 状压
搜索的数据较小，考虑用状压 $dp$ 数组记录当前已使用的颜色的集合。

```dp[x][y]=(p[x-1][y]|dp[x][y-1])|(1<<(i-1));```

其中 $x,y$ 表示当前搜到点的坐标，$i$ 表示枚举的第 $i$ 种颜色。

~~状压 DP 写惯了，一时半会儿没改。~~

## AC Code
```cpp
#include<iostream>
using namespace std;
int n,m,k;
int mp[10][10],dp[10][10];
int abv[10];
inline int dfs(int x,int y){
	if(y>m) x++,y=1;
	if(x>n) return 1;
	int s=dp[x-1][y]|dp[x][y-1],cnt=k;
	for(register int i=1; i<=k; i++)
		cnt-=(s>>(i-1))&1;
	if(cnt<=(n-x)+(m-y)) return 0;
	int t=-1,res=0;
	for(register int i=1; i<=k; i++){
		if((mp[x][y]&&mp[x][y]!=i)||((s>>(i-1))&1))
			continue;
		dp[x][y]=s|(1<<(i-1));
		if(abv[i]) res=(res+dfs(x,y+1));
		else{
			abv[i]=1;
			if (t==-1) t=dfs(x,y+1);
			res+=t;
			abv[i]=0;
		}
	}
	return res;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin >> n >> m >> k;
	if(n+m-1>k){putchar('0');return 0;}
	for(register int i=1; i<=n; i++)
		for(register int j=1; j<=m; j++){
			cin >> mp[i][j];
			abv[mp[i][j]]=1;
		}
	cout << dfs(1,1) << endl;
	return 0;
}
```


---

## 作者：yzxoi (赞：3)

# CF293B Distinct Paths
## 题意
给定一个$n\times m$的矩形色板，有kk种不同的颜料，有些格子已经填上了某种颜色，现在需要将其他格子也填上颜色，使得从左上角到右下角的任意路径经过的格子都不会出现两种及以上相同的颜色。路径只能沿着相邻的格子，且只能向下或者向右。

计算所有可能的方案，结果对 $1000000007 (10^9 + 7)$
## 输入及输出格式
### 输入格式
第一行，三个整数$ n, m, k (1 \le n, m \le 1000, 1 \le k \le 10)$；

接下来$n$行，每行包含$m$个整数，表示颜色。其中$0$表示未涂色，非$0$表示颜色的编号， 颜色编号为$1$到$k$。
### 输出格式
一行，一个整数，表示涂色方案对$ 1000000007 (10^9 + 7)$求模的结果。
## 样例
此处就不挂了：[传送门](https://www.luogu.org/problemnew/show/CF293B)

## 思路

看似数据很大：$ n, m, k (1 \le n, m \le 1000, 1 \le k \le 10)$，但是，$k<n+m-1$时，可以直接输出0。因为无法走完一条路径（一条路径长度为$n+m-1$，因为是只能向下、向右走）。

那么实际数据范围很小，大概是$n+m-1 \le 10$左右吧。

这么小的范围很容易就可想到$dfs$。这里有两个优化，一个是如果搜到一半，发现剩下的颜色不够用了就直接$return$。还有一个就是利用颜色$A$与颜色$B$的先后次序问题，路径$AB$与路径$BA$并不是同一种方案，所以搜索时如果搜到是第一次时，就可以直接乘$now$就可以省去很多$dfs$。

代码很丑，勿喷。
```C++
#include<algorithm>
#include<bitset>
#include<complex>
#include<deque>
#include<exception>
#include<fstream>
#include<functional>
#include<iomanip>
#include<ios>
#include<iosfwd>
#include<iostream>
#include<istream>
#include<iterator>
#include<limits>
#include<list>
#include<locale>
#include<map>
#include<memory>
#include<new>
#include<numeric>
#include<ostream>
#include<queue>
#include<set>
#include<sstream>
#include<stack>
#include<stdexcept>
#include<streambuf>
#include<string>
#include<typeinfo>
#include<utility>
#include<valarray>
#include<vector>
#include<cstring>
#include<cmath>
#define MOD 1000000007
using namespace std;//恶心的头文件
inline int read(){
	char ch=getchar();int res=0,f=1;
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') res=res*10+ch-'0',ch=getchar();
	return res*f;
}//读入优化
inline void write(int zx){
	if(zx<0) zx=-zx,putchar('-');
	if(zx<10) putchar(zx+'0');
	else{
		write(zx/10);
		putchar(zx%10+'0');
	}
}//输出优化
int n,m,k,cnt[50],a[50][50],sum,f[30][30],ps,ans,vv;
int dfs(int x,int y){
	if(y==m+1){return dfs(x+1,1);}
	if(x==n+1) return 1;
	int S=0,num=0,mar=0,res=0,las=0;
	f[x][y]=f[x-1][y]|f[x][y-1];
	for(int i=1;i<=k;i++){
		if(!(f[x][y]&(1<<i-1))) ++num;
	}
	if(num<n+m-x-y+1) return 0;//第一个优化
	if(a[x][y]==0){
		for(int i=1;i<=k;i++){
			if(!(f[x][y]&(1<<i-1))){
				if(cnt[i]==0){
					if(mar) res+=las,res%=MOD;//第二个优化
					else{
						mar=1;
						cnt[i]++;
						f[x][y]|=1<<i-1;
						las=dfs(x,y+1);
						f[x][y]^=1<<i-1;
						cnt[i]--;
						res+=las;
						res%=MOD;
					}
					continue ;
				}
				cnt[i]++;
				f[x][y]|=1<<i-1;
				res+=dfs(x,y+1);
				f[x][y]^=1<<i-1;
				cnt[i]--;
				res%=MOD;
			}
		}
	}else{
		if(!(f[x][y]&(1<<a[x][y]-1))){
			f[x][y]|=1<<a[x][y]-1;
			res+=dfs(x,y+1);
			f[x][y]^=1<<a[x][y]-1;
			res%=MOD;
		}
	}
	return res;
}
int main(){
	n=read();m=read();k=read();
	vv=n+m-1;
	if(k<vv){//开始先特判
		puts("0");
		return 0;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			a[i][j]=read();
			cnt[a[i][j]]++;
		}
	}
	ans=dfs(1,1);
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：orpg (赞：2)

### 题目大意

给一个 $N \times M$ 的矩阵（有些已染色），$K$ 种颜色。现在让你给这个矩阵上色，使从左上角到右下角的任意一条路不会出现相同颜色。

### 做法分析

合法的 $n$，$m$ 很小，$N+M-1>k$ 无解。

因为数据较小，所以我们考虑暴力搜索。但我们又要在 dfs 中维护当前颜色的使用情况，所以我们想到了状压。

$f_{x,y}$ 表示搜索到 $(x,y)$ 的集合。

但是这样，显然时间复杂度较高。
### 优化

1. 当剩余步数大于可用颜色数时，结束。

2. 如果当前有 $k$ 种颜色还未使用，对于空白格子染任何一种染色的贡献都是相同的，只需要选择一种颜色计算，其他颜色累加即可。

### 上代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
int state[1030],n,m,k;
int mp[20][20],f[20][20],c[20];
void init(){
	for(int i=1;i<1024;i++)
		state[i]=state[i>>1]+(i&1);
}
int dfs(int x,int y){
    if(y>m) x++,y=1;
    if(x==n+1) return 1;
    int st=f[x-1][y]|f[x][y-1],calc=-1,ret=0;
    int sum=~st&((1<<k)-1);
    if(n+m-x-y+1>state[sum]) return 0;
    for(int i=0;i<k;i++) {
		if(sum&(1<<i)){
	        if(mp[x][y]==0||mp[x][y]==i+1){
	            c[i+1]++;
	            f[x][y]=st|(1<<i);
	            if(c[i+1]==1){
	                if(calc==-1)
                        calc=dfs(x,y+1);
	                ret+=calc;
	            }
	            else
                    ret+=dfs(x,y+1);
	            ret%=mod;
	        	c[i+1]--;
	        }
	    }
	}
    return ret;
}
main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
	init();
    cin>>n>>m>>k;
    if(n+m-1>k){
        cout<<0;
        goto End;
    }
    for(int i=1;i<=n;i++){
	    for(int j=1;j<=m;j++){
	        cin>>mp[i][j];
	        c[mp[i][j]]++;
	    }
    }
    cout<<dfs(1,1);
    goto End;
    End:;
}
```


---

## 作者：傅思维666 (赞：2)


## 题解：

~~2019.10.29模拟赛T2 20分场~~

一开始毫无思路。

后来发现？咦？如果左上和右下的数（非零）一模一样的话，那就可以直接输出0了。

再后来发现？咦？如果矩阵长宽减一小于$k$，那么也显然不合法。

那这题会不会太简单了？~~绝壁不会~~

询问出题人被一顿惨$Diss$，坚定了我的看法~~一般猜到出题人的小心思出题人都会Diss~~

所以用两个特判加一个错误的搜索拿了20分。

正确的搜索加剪枝应该是：

如果搜索到一半，发现步数比颜色还多，那么就直接return。

可如果你只这么做，你就会发现：两个颜色的先后次序也会决定方案数的不同。

所以我们在搜索的时候直接进行排列的乘法，就可以剪掉很多枝桠。

就是：**可行性剪枝+排除等效冗余**

关于剪枝方式，有兴趣了解更多的小伙伴可以参考本蒟蒻的这篇博客：

[关于剪枝的方式](https://www.cnblogs.com/fusiwei/p/11759489.html)

代码如下：

```cpp
#include<cstdio>
using namespace std;
const int mod=1e9+7;
const int maxn=1010;
int n,m,k,ans;
int map[maxn][maxn],cnt[20];
int f[50][50];
int dfs(int x,int y)
{
    if(y==m+1)
        return dfs(x+1,1);
    if(x==n+1)
        return 1;
    int num=0,flag=0,ret=0,last=0;
    f[x][y]=f[x-1][y]|f[x][y-1];
    for(int i=1;i<=k;i++)
        if(!(f[x][y]&(1<<i-1)))
            num++;
    if(num<n+m-x-y+1)
        return 0;
    if(!map[x][y])
    {
        for(int i=1;i<=k;i++)
        {
            if(!(f[x][y]&(1<<i-1)))
            {
                if(!cnt[i])
                {
                    if(flag)
                        ret=(ret+last)%mod;
                    else
                    {
                        flag=1;
                        cnt[i]++;
                        f[x][y]|=1<<i-1;
                        last=dfs(x,y+1);
                        f[x][y]^=1<<i-1;
                        cnt[i]--;
                        ret=(ret+last)%mod;
                    }
                    continue;
                }
                cnt[i]++;
                f[x][y]|=1<<i-1;
                ret+=dfs(x,y+1);
                f[x][y]^=1<<i-1;
                cnt[i]--;
                ret%=mod;
            }
        }
    }
    else
    {
        if(!(f[x][y]&(1<<(map[x][y]-1))))
        {
            f[x][y]|=1<<map[x][y]-1;
            ret+=dfs(x,y+1);
            f[x][y]^=1<<map[x][y]-1;
            ret%=mod;
        }
    }
    return ret;
}
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    if(n+m-1>k)
    {
        puts("0");
        return 0;
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            scanf("%d",&map[i][j]);
            cnt[map[i][j]]++;
        }
    ans=dfs(1,1);
    printf("%d",ans);
    return 0;
}
```



---

## 作者：麻省理工学院 (赞：1)

这个$n，m≤1000$明显是唬人的，我们经过研究后可以发现，当$n + m - 1>k$时就无解了。因此我们发现，n,m的实际范围是非常小的，因此考虑dfs。
但是单纯的dfs时间复杂度仍不足以通过此题，我们考虑优化：

1.可行性剪枝。若剩下步数大于可用颜色就剪掉

2. 对称性剪枝。如果当前是第一次填颜色x，那么把x换成其他第一次填的颜色结果不变

这样就使的搜索量大大减少，即使棋盘相当稀疏也能瞬间出解

**Code**
```cpp
#include <cstdio>
#include <cstring>
#define lowbit(x) ((x) & (-(x)))
#define Int register int
using namespace std;

const int MOD = 1000000007;

int rc[1007][1007] , n , m , k , ans;
int rec[1007][1007] , used[1000007];

inline int dfs(Int x , Int y) 
{
    if (y > m) y = 1 , ++ x;
    if (x == n + 1) return 1;
    int now = rec[x - 1][y]|rec[x][y-1],tmp=-1;
    int ret = 0 , tot = 0;
    for (Int i = 1 ; i <= k ; ++ i) tot += !((1 << i - 1) & now);
    if (n + m - x - y + 1 > tot) return 0;
    for (Int i = 1 ; i <= k ; ++ i) 
	{
        if ((1 << i - 1) & now) continue;
        if (!rc[x][y] || rc[x][y] == i) 
		{
            rec[x][y] = now | (1 << i - 1);
            if (++ used[i] == 1) 
			{
                if (tmp == -1) tmp = dfs(x , y + 1);
                ret += tmp;
            } else ret += dfs(x , y + 1);
            ret %= MOD;
            -- used[i];
        }
    }
    return ret;
}

int main(void) 
{
    int cnt = 0; 
	scanf("%d%d%d" , &n , &m , &k);
    if (n + m - 1 > k) {putchar('0'); return 0;}
    for (Int i = 1 ; i <= n ; ++ i)
		for (Int j = 1 ; j <= m ; ++ j)
		{
        	scanf("%d",&rc[i][j]);
        	cnt += (!rc[i][j]); 
			++ used[rc[i][j]];
    	}
    printf("%d\n" , dfs(1 , 1));
    return 0;
}
```


---

## 作者：Alice2012 (赞：0)

搜索+剪枝+状压。

首先发现当 $n+m-1>k$ 时，一定不存在合法路径。于是这个诈骗的数据范围 $n,m\leq 1000$ 缩到很小。接下来考虑暴力搜索。又考虑到 $k\leq 10$，可以设 $dp_{x,y}=st$ 记录当前状态，表示搜到 $(x,y)$，颜色被染的状态是 $st$。然后一行一行的搜索，最后如果搜到了最后一格 $(n,m)$，则答案加 $1$。

当然这样做时间仍然跑不过。需要考虑剪枝。

首先，设当前走到 $(x,y)$，状态为 $st$，那么剩下需要染的格子数是 $cnt=n-m-x-y+1$。如果 $st$ 中 $0$ 的个数已经小于 $cnt$ 了，那么一定走不到终点，可以直接退出。

接下来是最重要的剪枝。若当前搜到 $(x,y)$，且 $(x,y)$ 没有被钦定颜色，那么从剩下的颜色中任意选一种的贡献都是相同的。换句话说，我们只需要搜索其中的某一个颜色并记录答案 $tmp$，对于其他剩下的颜色，直接加上贡献 $tmp$ 即可。这样大大减少了我们搜索等效冗余的时间。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=35,mod=1e9+7;
int n,m,k,c[N],a[N][N],dp[N][N];
int dfs(int x,int y){//dfs使用int类型方便记录答案 
	if(x==n+1)return 1;
	int st=dp[x-1][y]|dp[x][y-1];
	if(n+m-x-y+1>k-__builtin_popcount(st))return 0;//剪枝1:可行性剪枝 
	int tmp=-1,res=0;//tmp记录第一次搜索的答案,res统计总方案数 
	for(int i=1;i<=k;i++){//i枚举该格子填充的颜色 
		if(a[x][y]&&a[x][y]!=i)continue;//该格子已经被钦定颜色 
		if(st&(1<<i-1))continue;//之前已经填充过i这个颜色,不能重复填 
		dp[x][y]=st|(1<<i-1),c[i]++;//可以填i 
		if(c[i]==1){//如果是剩余的颜色(在后面没有出现过(被钦定过))
			if(tmp==-1)tmp=(y==m?dfs(x+1,1):dfs(x,y+1));//第一个这种颜色,搜索并记录答案tmp 
			res+=tmp,res%=mod;//不是第一次的话直接加答案就行了 
		}
		else res+=(y==m?dfs(x+1,1):dfs(x,y+1)),res%=mod;
		c[i]--;//回溯 
	}
	return res;
}
signed main(){
	cin>>n>>m>>k;
	if(n+m-1>k){cout<<0;return 0;}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>a[i][j],c[a[i][j]]++;//c:辅助第二个剪枝 
	cout<<dfs(1,1);
	return 0;
}
```

---

## 作者：1234567890sjx (赞：0)

这个哪有 $*\red{2700}$【表情】

很容易发现任意一条路径上都必然恰好经过 $n+m-1$ 个格子，**所以说若 $n+m-1>k$ 则一定无解。**

然后问题的范围立即缩小到 $n+m\le 11$。此时根据均值不等式 $n\times m\le 30$。因此考虑暴力 dfs 出每一个格子的颜色，但是可能会 T。

考虑剪枝：

+ 若当前是第一个格子那么填每一个颜色都是等价的，直接钦定第一个格子填第一个颜色然后把答案乘上 $k$ 即可。同理任意一个格子若没有填上颜色，则在剩下**没有用过**的颜色中任意选择一种都是本质相同的。
+ 若当前剩下的可用颜色不足以染色路径那么直接返回。
+ `#pragma GCC optimize(3)`。

然后就可以高兴的氵过一道紫 + $*\red{2700}$ 了。

---

## 作者：qfy123 (赞：0)

# CF293B
[传送门](https://www.luogu.com.cn/problem/CF293B)
## 题意
一个 $n \times m$ 的矩阵，让你把矩阵上所有为 $0$ 的点选一种颜色 $i$ 涂上，其中 $i \in [1,k]$，使从左上角到右下角的所有路径上，一种颜色**能且仅能**出现一次，求涂色方案数，对 $10^9 + 7$ 取模（注：每一步只能向下或者向右走）。

- $1 \leq k \leq 10$；
- $1 \leq n,m \leq 10^3$。
## 思路
首先看到 $1 \leq n,m \leq 10^3$，感觉不太可做。但细想一下，由于从左上到右下的任意路径每种颜色都只能出现一次，而一个从左上到右下的路径最短长度为 $n+m-1$，如果这个最短长度大于颜色的种类数，就必然没法满足题目要求，直接特判输出 $0$ 即可。

现在，我们发现 $n,m$ 满足 $2 \leq n+m \leq 11$ 时才有解。因为**一种颜色在一条路径上只能出现一次**且数据范围较小，所以不难想到状压和爆搜。用状压的思想记录当前状态：对于 $\forall_{1 \leq x \leq n,1 \leq y \leq m}(x,y)$，将**之前路径上已经经过的颜色所表示的状态**记为 $s(x,y)$，**该点的状态**记为 $S(x,y)$，则 $s(x,y) = S(x,y-1) \operatorname{or} S(x-1,y)$，$S(x,y) = s(x,y)\operatorname{or}2 ^{i-1}$，其中 $i \in [1,k]$ 且满足当前**能够选择**颜色 $i$，详情见代码。

接下来考虑爆搜，但此时复杂度能达到 $O((nm)^k)$，最大能到 $30^{10}$，显然不能通过，于是考虑剪枝。可以想到两种剪枝方案：
- 假设剩下没选的颜色数量少于到达终点所需的最小步数，则一定没法达到终点，于是返回方案数为 $0$ 即可。
- 一个没上色的点无论选哪种**在整个矩阵中没有被使用过的颜色**上色，对答案的贡献都一样，因此只要算一次贡献并记录下来，这样在后面涂上另一种**同样满足上述要求**的颜色的时候，只要加上这个贡献就可以了，无须再 dfs 算一遍答案。

加上这两种剪枝方案，即可通过本题。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;
const int C = 15;
int S[C][C],ma[C][C],v[C],n,m,k;
int dfs(int x,int y){
	if(y == m + 1) y = 1, ++x;//按照先从上到下再从左到右的顺序
	if(x == n + 1) return 1;//如果到达终点，方案数加一
	int ret = 0;
	int curs = S[x][y-1] | S[x-1][y];
	/*
	为何此时的状态是这两个值的按位或呢？
		题目要求任意路径上的颜色不能重复出现
		对于一个点来说，从左边来的路径和从上面来的路径中已经经过的颜色都不能再选了
		假设k=10，有一个没有上色的点上面来的路径经过了颜色1 3 5 7，左边来的路径经过了2 4 6 8，那这个点只能选9或10了
		此时上面来的状态可以看作00 0101 0101(2) 左边来的状态看作00 1010 1010(2) 按位或就是00 1111 1111(2)，
		即为当前的状态。
	*/
	int mem = -1;
	int col = k - __builtin_popcount(curs);// 求前面路径中未经过颜色种类的个数
   //__builtin_popcount():求一个数在二进制表示中1的个数
	if (n + m - x - y + 1 > col) return 0; // 第一个剪枝
	for(int i=1;i<=k;i++){
		if(!((curs >> (i - 1)) & 1)){//颜色i没有在之前的路径中出现过
			if(!ma[x][y] || ma[x][y] == i){//(x,y)这个点能够上色或者这个点的颜色就是i
				++v[i]; 
            	S[x][y] = curs | 1 << (i - 1);
            	//记录这个点的状态，表示之前路径上已经经过的颜色加上这个点所选的颜色的状态
            	if(v[i] == 1){
                	if(mem == -1) mem = dfs(x,y + 1); // 第二个剪枝
                	ret = (ret + mem) % mod; 
            	}else ret = (ret + dfs(x,y + 1)) % mod;
            	--v[i];
			}
		}
	}
	return ret; 
}
int main(){
	scanf("%d%d%d",&n,&m,&k);
	if(n + m - 1 > k){//n + m - 1 > k，即最少步数大于颜色种类，必定无解，输出0即可
		printf("0\n");
		return 0;
	}
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) scanf("%d",&ma[i][j]),v[ma[i][j]]++;// 记录各个颜色出现的次数
	printf("%d\n",dfs(1,1));
	return 0;
}
```
[AC记录](https://www.luogu.com.cn/record/166058250)

---

## 作者：james1BadCreeper (赞：0)

要求所有路径上的颜色都不相同，路径长度最大为 $k$，而 $k$ 最大只有 $10$，所以这实际上是个大暴力题。

考虑枚举所有没涂色的格子的颜色，并状压经过的路上的颜色。但是这样状态数干到了 $O((nm)^k)$ 的等级。

想一想为什么会算这么多。因为，我们计算了很多无用状态！所以：

- 如果还剩的颜色已经不能够填满接下来的路径，那么直接再见。
- 如果当前颜色是全局中唯一填的，那么填其它全局也没有出现的颜色是等效的，只需要算一次就可以了。

```cpp
#include <bits/stdc++.h>
using namespace std; 
const int P = 1000000007; 

int n, m, k; 
int a[1005][1005], f[1005][1005], v[15]; 

int dfs(int x, int y) {
    if (y == m + 1) ++x, y = 1; 
    if (x == n + 1) return 1; 
    int ans = 0, s = f[x - 1][y] | f[x][y - 1], tmp = -1; 
    if (n + m - x - y + 1 > k - __builtin_popcount(s)) return 0; 
    for (int i = 0; i < k; ++i) if (!(s >> i & 1))
        if (!a[x][y] || a[x][y] == i + 1) {
            ++v[i + 1]; 
            f[x][y] = s | 1 << i; 
            if (v[i + 1] == 1) {
                if (tmp == -1) tmp = dfs(x, y + 1); 
                ans += tmp; 
            } else ans += dfs(x, y + 1); 
            if (ans >= P) ans -= P; 
            --v[i + 1]; 
        }
    return ans; 
}

int main(void) {
    ios::sync_with_stdio(0); 
    cin >> n >> m >> k; 
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) cin >> a[i][j], ++v[a[i][j]]; 
    if (n + m - 1 > k) return cout << "0\n", 0; 
    return cout << dfs(1, 1) << "\n", 0; 
}
```

---

## 作者：lmy_2011 (赞：0)

### 首先说明：
本文转载于[此](https://www.cnblogs.com/812-xiao-wen/p/10307025.html)
### 基本思路：
首先我们根据一条路径上不能有两个相同颜色的格子可以得出：
对于两个格子 $(x_1,y_1)$ 和 $(x_2,y_2)$ 必须满足其中一条：
- $x_1<x_2$ 且 $y_2<x_2$ 
- $x_1>x_2$ 且 $x_1<y_2$

然后按此思路进行遍历，然后枚举即可。
### 剪枝优化：
根据上面的枚举方法，我们发现以下方式进行遍历会快的多： 
$$ (1,1)-(n,n)-(1,2)-(2,1)-(n,n-1)-(n-1,n)-\cdots $$ 

现在，我们把初始棋盘中没有出现过的颜色称作自由颜色:

- 如果我们有两个自由颜色：$a$ 和 $b$。假设我们找到了一个可行的最终棋盘，然后把所有的 $a$ 换成 $b$，所有的 $b$ 换成 $a$。容易发现得到的棋盘依然是可行的。

- 将把自由颜色排序，如果我们当前没有用过第 $i$ 个自由颜色，那么我们就不枚举第 $i+1$ 个自由颜色。到最后计算结果的时候，如果我们用了 $x$ 个自由颜色，而总共有 $y$ 个自由颜色，那么答案就是 $y$ 个数中去取 $x$ 个组成有序排列的数目。

```cpp
#include<iostream>
#include<cstdio>
#include<iomanip>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<vector>
#include<queue>
#include<map>
#include<set>

#define ll long long
#define db double
#define inf 0x7fffffff
#define rg register int
#define mod 1000000007
#define end {puts("0");return 0;}

using namespace std;

struct su{
    int x,y;
}b[13],c[13],d[11][11];

ll ans;
int n,m,l,k,ti,top,sss;
int se[11],to[11];
int tot[11];
int P[11];
int a[10][10];
int ss[10][10];
bool s[10][10];

inline int qr(){
    char ch;
    while((ch=getchar())<'0'||ch>'9');
    int res=ch^48;
    while((ch=getchar())>='0'&&ch<='9')
        res=res*10+(ch^48);
    return res;
}

inline void add(int t,int x,int y){
    d[t][++tot[t]].x=x;
    d[t][tot[t]].y=y;
}

inline bool check(int i,int x,int y){
    for(rg j=1,p,q;j<=tot[i];++j){
        p=d[i][j].x;q=d[i][j].y;
        if(x>=p&&y>=q)return 0;
        if(x<=p&&y<=q)return 0;
    }return 1;
}

inline void dfs(int t){
    if(t>n*m){
        ans+=P[to[0]+sss-k];
        return ;
    }
    rg x=b[t].x,y=b[t].y;
    if(s[x][y]){dfs(t+1);return ;}
    for(rg i=1;i<=to[0];++i){
        if(check(i,x,y)){
            add(i,x,y);
            ss[x][y]=i;
            dfs(t+1);
            --tot[i];
        }
    }
    if(to[0]==k)return ;
    add(++to[0],x,y);
    ss[x][y]=to[0];
    dfs(t+1);
    tot[to[0]]=0;--to[0];
    return ;
}

inline void bfs(){
    for(rg o=1,i=0,j=1;o<=l;++o){
        c[o].x=((i==n)?i:++i);
        c[o].y=((i>=n)?j++:j);
    }
    for(rg o=0,r,i,j;o<l;++o){
        r=o&1?l-o/2:o/2+1;
        i=c[r].x;j=c[r].y;
        for(;i&&j<=m;--i,++j)
            b[++top].x=i,b[top].y=j;
    }
}

int main(){
    n=qr(),m=qr(),k=qr();
    if((l=n+m-1)>k) end;
    for(rg i=1;i<=n;++i)
        for(rg j=1;j<=m;++j){
            ti=a[i][j]=qr();
            if(ti){
                s[i][j]=1;
                if(se[ti]){
                    ti=se[ti];
                    ss[i][j]=ti;
                }
                else{
                    ti=se[ti]=++to[0];
                    to[ti]=a[i][j];
                    ss[i][j]=ti;
                }
				if(!check(ti,i,j)){
					puts("0");
					return 0;
				}
				add(ti,i,j);
            }
        }
    sss=k-to[0];P[0]=1;
    for(rg i=0;i<sss;++i)
        P[i+1]=P[i]*(sss-i);
	if(l==k){
		printf("%d\n",P[sss]);
		return 0;
	}
    top=0; bfs(); dfs(1);
    printf("%lld\n",ans%mod);
    return 0;
}


```


---

## 作者：max67 (赞：0)

# 题解 CF293B 【Distinct Paths】
## **——by max67**
## 前(~~废~~)话
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;当初做题看了一个下午也没看懂题解在干啥，虽然懂方法，取不懂写法。为此，我特意~~复制~~老师的代码来给大家讲讲，不至于像我一样蒙。
## 题面
[题目传送门](https://www.luogu.com.cn/problem/CF293B)  
**题意概述**  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;给定一个$n*m$($1<=n,m<=1000$)的矩阵,里面有一些数，代表颜色编号，其中有一些数为0，也就是无色。现给定k（$k<=10$)种颜色,需要使矩阵内数全部不为0（都有色），且满足从（1,1）到（n,m)的所有路径(按向下走n-1格，向右走m-1格的标准)都满足经过的格子中的数字不相等(颜色不相同),问有多少种方法,按$1e9+7$取模.
## 分析思路
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;首先看数据范围$k<=10$,$1<=n,m<=1000$。可以肯定这是为了坑人。因为路径总共经过（$n+m-1$）个格子。
 ![](https://cdn.luogu.com.cn/upload/image_hosting/phauf9o6.png)
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;根据抽屉原理([不懂点我](https://www.baidu.com/link?url=H-fZCWxTNq3EkPApU3tQmuFG_ucdOZ1DBtQ81JfD_SriaBV0Jup8LT7eNQD_Lv7F1g6scETZ_yii6ptW_sBijXntufCbbndIBaa5DAZ4-VQXLUs6dAmRaCk9iWp78mgN&wd=&eqid=b7502b7000029001000000065fc24332))，必然需要（$n+m-1$）种颜色才不会重复，所以$n+m<=10,1<=n,m<=9$.  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;那么小的数据，想到的肯定是dfs爆搜,用状压数组储存已经有的颜色做dfs,但这样还是回超......  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;思路大致方向是对的，那么只需要小的优化就可以了，我们想到dfs的剪枝  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**1**.~~很明显~~，剪枝可以从可行性剪枝去考虑(算比较常见的）,那么由上文的抽屉原理~~易~~联想到扫到当前状态(dfs(i,j)）剩下的颜色必须满足小于剩下的步数，否则就会重复，所以要剪去。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**2**.可以从颜色的种类考虑，只要当前颜色满足放的条件，必然其他的颜色也可以满足，因为我们的操作并未涉及到要分不同的颜色讨论(固定的颜色除外)的情况。假设当前可以放1和2，现在放了1，接下去就放2，那么与现在放2，接下去放1的方案数贡献是一样的。
## 代码分析
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;我们有的结构肯定由以下结构组成  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**1**.读入  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**2**.特判  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**3**.爆搜(dfs)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**4**.输出  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;详细思考爆搜(dfs)由哪几部分组成  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**1**.判断终点累加  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**2**.剪枝  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**3**.循环枚举并累加答案
那么怎么打呢？
因为我们要判断是否重复，所以读入部分需要记录颜色出现  
```cpp
	 scanf("%lld%lld%lld",&n,&m,&k);
	 if(n+m-1>k)return puts("0");
          //剪枝
	 for(int i=1;i<=n;i++)
	    for(int j=1;j<=m;j++)
	       {
	       	     scanf("%lld",&a[i][j]);
	       	  ```cpp
	printf("%lld\n",ans);
                 //记录出现次数
		   }
```
然后是输出
```cpp
	printf("%lld\n",ans);
```
dfs部分
```cpp
void dfs(int x,int y)
{
	if(x==n+1)
	{
		ans=(ans+1)%p;
		return;
	}
	f[x][y]=f[x-1][y]|f[x][y-1];
	int XX=1,YY=k,s=0,sum=-1,pre;
	for(int i=f[x][y];i;i-=i&-i) s++;
	if(n+m-x-y>=k-s)return;
	if(a[x][y])XX=YY=a[x][y];
	for(int i=XX;i<=YY;i++)
	{
		if((f[x][y]&(1<<(i-1)))==0)
		{ 
		  if(!cnt[i])
		  {
			if(sum>=0)
			{
			  ans=(ans+sum)%p;
			  continue;
		     }
		  pre=ans;
	     }
		  f[x][y]^=(1<<(i-1));
		  cnt[i]++;
		  if(y==m)dfs(x+1,1);
		  else dfs(x,y+1);
		  f[x][y]^=(1<<(i-1));
		  cnt[i]--;
		  //递归下去 
		  if(!cnt[i])sum=(ans-pre)%p;
	   }
   }
}
```
我们来逐步分析

```cpp
if(x==n+1)
	{
		ans=(ans+1)%p;
		return;
	}
```
当跑到终点时累加答案
```cpp
f[x][y]=f[x-1][y]|f[x][y-1];
```
f[x][y]代表在x,y时累计的数量，用二进制存储。因为最多有10种颜色，可以由1024




---

## 作者：ImmortalWatcher (赞：0)

**Description**

给你 $n*m(n,m\leq 1000)$ 个格子和 $k(k\leq 10)$ 种，有些格子有颜色，让你在没有颜色的格子上涂色。

问有多少种涂色方法使得从左上角到右下角的所有可能路径经过格子的颜色都不同。

**Solution**

我第一眼就看到 $n,m\leq 1000$，然后觉得，这道题可能是DP什么的，想了半天没一点头绪，回头再读了一下题。

从左上角到右下角的路径一共经过 $n+m-1$ 个格子，所以要使路径上的每个格子的颜色都不同，那么 $k$ 就必须 $\geq$ 路径长度，也就是 $k\geq n+m-1$，否则无解，那这样 $n,m$ 的范围就缩小了很多了， $k\leq 10$，那么 $n,m\leq 6$，这不就是爆搜+剪枝的范围嘛。

于是立刻想到两个剪枝。

1、可行性剪枝。

如果剩下的颜色不足以填完路径上还未走完的格子，那么退出。

2、对称性剪枝。

如果这个颜色是第一次选，那么其他颜色第一次选和这个颜色第一次选的本质是一样的，所以直接加上这个颜色的贡献。

于是我们就可以顺利 $AC$ 了！！

**Code**

```cpp
#include<cstdio>
using namespace std;
const int mo=1000000007;
int n,m,k,a[11][11],f[12][1101],bz[11];
int dg(int x,int y)
{
	if (y>m) x++,y=1;
	if (x>n) return 1;
	int ans=0,flow,s=0;
	bool bj=false;
	f[x][y]=f[x-1][y]|f[x][y-1];
	for (int i=1;i<=k;i++)
		if (f[x][y]&(1<<(i-1))) s++;
	if (n+m-x-y+1>k-s) return 0;
	s=f[x][y];
	if (a[x][y])
	{
		if (!(s&(1<<(a[x][y]-1))))
		{
			f[x][y]=s|(1<<(a[x][y]-1));
			ans=(ans+dg(x,y+1))%mo;
		}
		return ans;
	}
	for (int i=1;i<=k;i++)
		if (!(s&(1<<(i-1))))
		{
			f[x][y]=s|(1<<(i-1));
			bz[i]++;
			if (bz[i]==1)
			{
				if (!bj) flow=dg(x,y+1),bj=true;
				ans=(ans+flow)%mo;
			}
			else ans=(ans+dg(x,y+1))%mo;
			bz[i]--;
		}
	return ans;
}
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	if (n+m-1>k)
	{
		printf("0");
		return 0;
	}
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			scanf("%d",&a[i][j]),bz[a[i][j]]++;
	printf("%d",dg(1,1));
	return 0;
}
```


---

## 作者：WOL_GO (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/solution/CF293B)

真服了 CF 的 RemoteJudge 评测，交了好几发都是 UKE，有相同情况的同学可以交到[原题](https://codeforces.com/problemset/problem/293/B)评测。

+ 可以发现，当 $n+m-1>k$ 时，显然无解，且经过的颜色肯定超过了两种及其以上的颜色。

+ 合法的 $n$,$m$ 范围比较小，可以使用搜索。

+ 使用状压的方式记录当前使用的颜色，$\mathit{f}_{x,y}$ 表示搜索到 $(x,y)$ 使用的颜色集合。

+ 剪枝优化：

1. 可行性剪枝：当剩下的步数大于可用的颜色数时，可以直接结束搜索。

2. 排除等效冗余：如果当前有 $k$ 种颜色还使用，对于空白格子染任何一种染色的贡献都是相同的，只需要选择一种颜色计算，其他颜色累加即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+5;
void read(int &xx){
    register char ch=getchar();
    register int ans=0;
    char t=0;
    while(!isdigit(ch))t|=ch=='-',ch=getchar/*_unlocked*/();
    while(isdigit(ch))ans=(ans<<3)+(ans<<1)+(ch^48),ch=getchar/*_unlocked*/();
    xx=t?-ans:ans;
    return ;
}
void write(int x){
    if(x<0){
        putchar('-');
        x*=-1;
    }
    char wr[18];
    int cnt=1;
    if(x==0){
        putchar('0');
        putchar('\n');
        return ;
    }
    while(x){
        wr[cnt++]=x%10+'0';
        x/=10;
    }
    for(cnt--;cnt;cnt--){
        putchar(wr[cnt]);
    }
    putchar('\n');
    return;
}
const int dx[2]={1,0},dy[2]={0,1},mod=1e9+7;
int a[1005][1005];
long long f[1005][1005];
int ans[1005][1005];
int n,m,k;
bool use[maxn];
int dfs(int x,int y){//1<<(i-1)
    if(y>m){
        x++,y=1;
    }
    if(x>n)return 1;
    int s=f[x-1][y]|f[x][y-1];
    int sum=0;
    int left=0;
    for(int i=1;i<=k;i++){
        if(!(s&(1<<(i-1))))left++;
    }
    if(n+m-x-y+1>left) return 0;
    int now=-1;
    for(int i=1;i<=k;i++){
        if((a[x][y]&&a[x][y]!=i)||((s>>(i-1))&1))continue;
        f[x][y]=s|1<<(i-1);
        if(!use[i]){
            use[i]=1;
            if(now==-1){
                now=dfs(x,y+1);
            }
            sum+=now;
            sum%=mod;
            use[i]=0;
        }
        else sum+=((dfs(x,y+1))%mod),sum%=mod;
    }
    // cout<<sum<<"\n";
    return sum;
}
int main(){
    read(n);
    read(m);
    read(k);
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)read(a[i][j]),use[a[i][j]]=1;
    if(n+m-1>k){
        puts("0");
        return 0;
    }
    write(dfs(1,1)%mod);
    return 0;
}
```



---

