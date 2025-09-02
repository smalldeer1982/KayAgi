# Anna, Svyatoslav and Maps

## 题目描述

The main characters have been omitted to be short.

You are given a directed unweighted graph without loops with $ n $ vertexes and a path in it (that path is not necessary simple) given by a sequence $ p_1, p_2, \ldots, p_m $ of $ m $ vertexes; for each $ 1 \leq i < m $ there is an arc from $ p_i $ to $ p_{i+1} $ .

Define the sequence $ v_1, v_2, \ldots, v_k $ of $ k $ vertexes as good, if $ v $ is a subsequence of $ p $ , $ v_1 = p_1 $ , $ v_k = p_m $ , and $ p $ is one of the shortest paths passing through the vertexes $ v_1 $ , $ \ldots $ , $ v_k $ in that order.

A sequence $ a $ is a subsequence of a sequence $ b $ if $ a $ can be obtained from $ b $ by deletion of several (possibly, zero or all) elements. It is obvious that the sequence $ p $ is good but your task is to find the shortest good subsequence.

If there are multiple shortest good subsequences, output any of them.

## 说明/提示

Below you can see the graph from the first example:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1204C/71cf125b3567a608d3e838a04ba123f82afa0825.png)

The given path is passing through vertexes $ 1 $ , $ 2 $ , $ 3 $ , $ 4 $ . The sequence $ 1-2-4 $ is good because it is the subsequence of the given path, its first and the last elements are equal to the first and the last elements of the given path respectively, and the shortest path passing through vertexes $ 1 $ , $ 2 $ and $ 4 $ in that order is $ 1-2-3-4 $ . Note that subsequences $ 1-4 $ and $ 1-3-4 $ aren't good because in both cases the shortest path passing through the vertexes of these sequences is $ 1-3-4 $ .

In the third example, the graph is full so any sequence of vertexes in which any two consecutive elements are distinct defines a path consisting of the same number of vertexes.

In the fourth example, the paths $ 1-2-4 $ and $ 1-3-4 $ are the shortest paths passing through the vertexes $ 1 $ and $ 4 $ .

## 样例 #1

### 输入

```
4
0110
0010
0001
1000
4
1 2 3 4
```

### 输出

```
3
1 2 4 ```

## 样例 #2

### 输入

```
4
0110
0010
1001
1000
20
1 2 3 4 1 2 3 4 1 2 3 4 1 2 3 4 1 2 3 4
```

### 输出

```
11
1 2 4 2 4 2 4 2 4 2 4 ```

## 样例 #3

### 输入

```
3
011
101
110
7
1 2 3 1 3 2 1
```

### 输出

```
7
1 2 3 1 3 2 1 ```

## 样例 #4

### 输入

```
4
0110
0001
0001
1000
3
1 2 4
```

### 输出

```
2
1 4 ```

# 题解

## 作者：te5555 (赞：8)

## 题意:
给你一个$\text{DAG}$上的路径$p$,保证$p_{i-1}$与$p_i$直接相连.求$p$的子序列$v$,使得v长度最小的同时满足按照$v$的顺序以最短路径遍历图恰好经过路径$p$.

题意的确很难理解,
## 转化:
就是删去$p$里面的若干点,使得访问顺序不变.

考虑什么时候访问顺序会不变(删掉某个点$p_k$)

答案是$p_k$在前一个未被删掉的点和后一个未被删掉的点的最短路上时,不会影响

先用$\text{Floyd}$预处理两点之间最短路

然后如果$dis[i][j]>dis[i][k]+dis[j][k]$,$k$就不能删,如果删掉$k$,那么从$i\to j $的距离就比原来小了,也就是不经过$k$了.
## Code
``` cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
inline int read()
{
    int res = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
        res = res * 10 + ch - 48, ch = getchar();
    return res * f;
}
int n, m;
const int maxn = 105;
int g[maxn][maxn], dis[maxn][maxn];
int p[1000066];
vector<int> v;
char s[maxn];
int vis[maxn];
signed main()
{
    n = read();
    for (register int i = 1; i <= n; i++)
    {
        cin >> s + 1;
        for (register int j = 1; j <= n; j++)
        {
            g[i][j] = s[j] - '0';
            dis[i][j] = g[i][j];
            if (dis[i][j] == 0)
                dis[i][j] = 0x7f7f7f7f;
            if (i == j)
                dis[i][j] = 0;
        }
    }
    m = read();
    for (register int i = 1; i <= m; i++)
        p[i] = read();
    for (register int k = 1; k <= n; k++)
    {
        for (register int i = 1; i <= n; i++)
        {
            for (register int j = 1; j <= n; j++)
            {
                dis[i][j] = min(dis[i][k] + dis[k][j], dis[i][j]);
            }
        }
    }
    v.push_back(p[1]);
    int las = p[1];
    int cur = 0;
    for (register int i = 2; i <= m; i++)
    {
        cur += dis[p[i - 1]][p[i]];
        if (dis[las][p[i]] < cur)
            las = p[i - 1], v.push_back(las), cur = dis[las][p[i]];
    }
    v.push_back(p[m]);
    cout << v.size() << endl;
    for (auto x : v)
        cout << x << ' ';
    return 0;
}
```

---

## 作者：兮水XiShui丶 (赞：8)

(个人感觉比$D$难$QAQ...$)  
让你在给定的序列$P$中求一个子序列,使得在图中按照该子序列进行最短路径移动时可以完整经过原序列$P$.  
乍一看一点思路都没有.但是仔细思考可以发现一点点思路.我们可以从题目中给出的起点(也就是一号点)开始进行移动,然后在原序列$P$中如果需要经过$P_{i}$和$P_{i+1}$,那么我们显然可以得到$P_i$与$P_{i+1}$一定是直接相连的(因为题目中没有给出无解的情况).那么我们可以扩展一下,假设我们现在在$P_j$号点,我们要走到$P_k$号点.那么如果$dis[P_j][P_k]==j-k$,那么在有解的情况下,一定是有$P_j$经过了所有的$j<i<k$的点(可以自己画个图证明一下).在这种情况下,我们就可以选择扩展答案了.

(感觉还是放一下代码比较好qwq) 

```cpp
#include<bits/stdc++.h>
using namespace std;
const int oo = 0x3f3f3f3f;
const int N = 105;
const int M = 1e6 + 10;
int n,m,idx;
char mp[N][N];
int G[N][N],point[M],ans[M];
int qu[M<<1];
int head=1,tai=0;
int main(){
	memset ( G , 0x3f3f3f3f , sizeof ( G ) );
	scanf ( "%d" , &n );
	for ( int i = 1 ; i <= n ; i++ ) 
		scanf ( "%s" , mp[i] + 1 );
	for ( int i = 1 ; i <= n ; i++ ) {
		for ( int j = 1 ; j <= n ; j++ ) 
			if ( mp[i][j] == '1' ) 
				G[i][j] = 1;
		G[i][i] = 1;
	}
	for ( int k = 1 ; k <= n ; k++ ) 
		for ( int i = 1 ; i <= n ; i++ ) 
			for ( int j = 1 ; j <= n ; j++ ) 
				G[i][j] = min ( G[i][j] , G[i][k] + G[k][j] );
	scanf("%d",&m);
	for ( int i = 1 ; i <= m ; i++ )
		scanf ( "%d" , &point[i] );
//	for(int i=1;i<=n;i++){
//		for(int j=1;j<=n;j++)
//			printf("%d " ,G[i][j]);
//		puts("");
//	}
	int st=1,now=2;
	while(now<=m){
		int diss=now-st;
		if(diss==G[point[st]][point[now]]){
			if(head<=tai)
				head++;
			qu[++tai]=now;
			now++;
		}
		else {
			ans[++idx]=point[st];
			if(head<=tai)
				st=qu[head++];
		}
	}
	ans[++idx]=point[st];
	if(ans[idx]!=point[m])
		ans[++idx]=point[m];
	printf("%d\n",idx);
	for(int i=1;i<=idx;i++)
		printf ("%d ",ans[i]);
	return 0;
}
```

---

## 作者：Minakami_Yuki (赞：4)

考场没做出来，身败名裂

看到没什么人写用栈做，我来写一写qwq

# 题目链接

[(Luogu)CF1204C Anna, Svyatoslav and Maps](https://www.luogu.org/problem/CF1204C)

# 题意简述

给你一张图和一个序列，要求找出其最短的子序列，满足两个序列首尾元素相同，并且子序列中每个点都在原序列最短路径上（好像没说清楚


# 解题思想

看到这个$n$很小，我们考虑`Floyd`先求出最短路。

然后对于原序列，我们**贪心**地考虑每三个点：
如果中间的点在另外两个点的**最短路径**上，我们就可以去掉它。

这个可以通过`Floyd`后得到的距离进行判断。

所以，我们需要维护一下这三个点：
对于每一个被去掉的点，显然不用考虑，然后当前用来更新的点肯定是完成的序列中最后一个被更新的，所以我们只需要维护答案队列的首。

考虑使用栈：
对于每一个原序列的元素，取出它与后一个元素与栈顶元素进行比较更新：
若答案符合上述要求，则将**中间元素**加入栈中，否则跳过。

需要注意的是，序列的`N`与图的`N`不是同一个，数组要开够。

# 参考代码

```c++
#include <cstdio>
#include <cctype>

namespace FastIO {
	inline int read() {
		char ch = getchar(); int r = 0, w = 1;
		while(!isdigit(ch)) {if(ch == '-') w = -1; ch = getchar();}
		while(isdigit(ch)) {r = r * 10 + ch - '0', ch = getchar();}
		return r * w;
	}
	void _write(int x) {
		if(x < 0) putchar('-'), x = -x;
		if(x > 9) _write(x / 10);
		putchar(x % 10 + '0');
	}
	inline void write(int x) {
		_write(x);
		puts("");
	}
}

using namespace FastIO;

const int N = 110;
const int M = 1e6 + 6;

template <typename T> inline T min(T a, T b) {return a < b ? a : b;}

int n, m, a[M];
int f[N][N];
char mp[N][N];
int s[M], stop;

int main() {
	n = read();
	for(register int i = 1; i <= n; i++) {
		scanf("%s", mp[i] + 1);
	}
	for(register int i = 1; i <= n; i++) {
		for(register int j = 1; j <= n; j++) {
			if(mp[i][j] == '0') f[i][j] = 0x3f3f3f3f;
			else f[i][j] = 1;
		}
	}
	for(register int i = 1; i <= n; i++) {
		f[i][i] = 0;
	}
	m = read();
	for(register int i = 1; i <= m; i++) {
		a[i] = read();
	}
	for(register int k = 1; k <= n; k++) {
		for(register int i = 1; i <= n; i++) {
			for(register int j = 1; j <= n; j++) {
				f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
			}
		}
	}
	s[++stop] = a[1];
	for(register int i = 2; i <= m; i++) {
		if(f[s[stop]][a[i + 1]] != f[s[stop]][a[i]] + f[a[i]][a[i + 1]]) s[++stop] = a[i];
	}
	printf("%d\n", stop);
	for(register int i = 1; i <= stop; i++) printf("%d ", s[i]);
	return 0;
}
```



---

## 作者：CHU2 (赞：2)

大家的做法都踩爆我的做法啊QAQ

Floyd先预处理出最短路。然后设$f[i]$表示dp到位置$i$时最短的序列长度。$j(j<i)$能转移到$i$当且仅当$dis[a[j]][a[i]]==i-j$

又注意到最短路长度最长为$n$，于是就得到了一个跑得巨慢无比但能通过本题的做法。时间复杂度$O(nm)$

代码：
```cpp
#include <bits/stdc++.h>
#define N 105
#define M 1000005
#define For(i,x,y) for(register int i=(x);i<=(y);++i)
#define Rof(i,x,y) for(int i=(x);i>=(y);--i)
using namespace std;
int a[M],g[N][N],f[M],trans[M],ans[M];
char s[N];
inline void rd(int &x){
	int y=0;char c=getchar();
	while(c<'0'||c>'9') c=getchar();
	while(c>='0' && c<='9') y=y*10+c-'0',c=getchar();
	x=y;
}
int main(){
	int n,m,cnt=0;scanf("%d",&n);
	memset(g,0x3f,sizeof(g));
	memset(f,0x3f,sizeof(f));
	For(i,1,n){
		scanf("\n%s",s+1);
		For(j,1,n)
			if(s[j]=='1') g[i][j]=1;
	}
	rd(m);
	For(i,1,m) rd(a[i]);
	For(k,1,n) For(i,1,n) For(j,1,n) g[i][j]=min(g[i][k]+g[k][j],g[i][j]);
	For(i,1,n) g[i][i]=0;
	f[1]=1;
	For(i,1,m)
		For(j,max(i-n,1),i-1)
			if(i-j==g[a[j]][a[i]] && f[i]>f[j]+1) f[i]=f[j]+1,trans[i]=j;
	printf("%d\n",f[m]);
	for(register int i=m;i;i=trans[i]) ans[++cnt]=a[i];
	Rof(i,cnt,1) printf("%d ",ans[i]); 
}
```

---

## 作者：寒鸽儿 (赞：2)

[在窝的博客阅读](https://froldh.github.io/2019/08/21/OI/codeforcesPlan/R581/1204C)  
[在窝的luogu博客阅读](https://www.luogu.org/blog/oldherd/solution-cf1204C)  
题意简述:以邻接矩阵的形式给定一张有向无环图无权图,1表示有边0表示没有。然后给定一条路径(不一定为简单路径),按照遍历的点的顺序给出。(路径依次通过这些结点并不额外地通过其他节点)要求:尝试在路径中删除尽可能多的点,使得要按顺序走完剩余的结点(可以经过其他结点)所走的最短路径长度等于原路径长度。  
一个点能够被删除的条件是什么？如果前面一个保留的点到这个点后一个点的最短路径等于前面一个点经过这个点到这个点后面一个点的最短路径相等,那么这个点可以被删除。换言之,在路径$p_1$ $p_2$ ... $p_k$ ... $p_i$ $p_{i+1}$ ...$p_m$ 我们的决策已经进行到$p_i$,上一个没有被删除的点是$p_k$，那么$p_i$能被删除的条件是:从$p_k$按原路径走到$p_{i+1}$的长度等于从$p_k$走到$p_{i+1}$的最短路径长度。其中,$p_k$按原路径走到$p_{i+1}$的路径长度等于$i-k$，而$p_k$到$p_{i+1}$的最短路径长度窝们可以采用floyd O($n^3$)预处理出来。而如果后者小于前者,则$p_i$不能被删除。  
代码:  
```cpp
#include <cstdio>

using namespace std;

char buf[2000000], *p1 = buf, *p2 = buf;
inline char gc() { return p1==p2&&(p2=(p1=buf)+fread(buf,1,2000000,stdin), p1==p2)?EOF:*p1++; }
inline void read(int &x) {
    x = 0;
    char ch = gc();
    while(ch < '0' || ch > '9') ch = gc();
    while(ch >= '0' && ch <= '9') x = (x<<3)+(x<<1)+(ch&15), ch = gc();
}

const int maxn = 110, maxm = 1000010;
int dis[maxn][maxn], p[maxm], ans[maxm];

int main() {
	register int n;
	register char ch;
	read(n);
	for(register int i = 1; i <= n; i++)
		for(register int j = 1; j <= n; j++) {
			ch = gc();
			while(ch != '0' && ch != '1') ch = gc();
			dis[i][j] = ch=='1'?1:-1;
		}
	for(register int k = 1; k <= n; k++)
		for(register int i = 1; i <= n; i++)
			for(register int j = 1; j <= n; j++) {
				if(i==j || j==k || k==i || dis[i][k]==-1 || dis[k][j]==-1) continue;
				if(dis[i][j]==-1 || dis[i][j] > dis[i][k]+dis[k][j]) dis[i][j] = dis[i][k] + dis[k][j];
			}
	register int m, au = 1;
	read(m);
	for(register int i = 1; i <= m; i++) read(p[i]);
	ans[0] = p[1];
	int la = 1;
	for(register int i = 2; i < m; i++)
		if(dis[ans[au-1]][p[i+1]] < i+1-la)
			ans[au++] = p[i], la = i;
	ans[au++] = p[m];
	printf("%d\n", au);
	for(register int i = 0; i < au; i++) printf("%d ", ans[i]);
	printf("\n");
	return 0;
}

```

---

## 作者：robin12138 (赞：2)

### ~~这题不就是一个裸的贪心吗~~

**题意**

对于一个$n(n \leqslant 100)$个点的有向无环图，给出一个由$m(m \leqslant 10^6)$个点组成的的路径$p$(不保证是简单路径)，
要求从$p$中选出一个最短的子序列$v$(假设长度为$k$)，满足$v_1=p_1,v_k=p_m$，并且$p$是按顺序经过$v$的最短路径之一


**思路**

看到$n$这么小，~~而且题目直接给了邻接矩阵~~，我们显然可以先用$floyd$求出任意两点之间的距离，假设存在$d$数组里

然后除了$p_1$和$p_n$必选之外，我们一个一个点考虑，

设上一个选了的点为$p_x$，当前节点为$p_i$，那么当且仅当$p_x$与$p_i$之间的最短距离$d[p_x,p_i]$小于按路径$p$上的顺序走$p_x$与$p_i$的距离，我们才需要选中$p_i$，扫一遍即可


```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <cctype>
#include <queue>
#include <stack>
#include <map>
#include <set>
using namespace std;

#define inf 0x3f3f3f3f
typedef long long LL;
#define cls(x) memset(x,0,sizeof(x))
#define For(i,j,k) for(register int i=(j);i<=(k);++i)
#define Rep(i,j,k) for(register int i=(j);i>=(k);--i)
#define rint register int
#define il inline

const int N=100+5,M=1e6+5;
LL d[N][N],dis;
int n,m,p[M];
int tot,ans[M];

int main()
{
    scanf("%d",&n);
    for(rint i=1;i<=n;++i)
        for(rint j=1;j<=n;++j)  
        {
            scanf("%1lld",&d[i][j]);
            if(!d[i][j]&&(i!=j)) d[i][j]=inf;
        }

    for(rint k=1;k<=n;++k)
        for(rint i=1;i<=n;++i)
            for(rint j=1;j<=n;++j)
                d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
    
    scanf("%d",&m);
    for(rint i=1;i<=m;++i) scanf("%d",&p[i]);

    int x=p[1]; ans[++tot]=x;
    for(rint i=2;i<=m;++i)
    {
        dis+=d[p[i-1]][p[i]]; 
        if(d[x][p[i]]<dis) x=p[i-1],ans[++tot]=x,dis=d[x][p[i]];
    }
    ans[++tot]=p[m];
    printf("%d\n",tot);
    for(rint i=1;i<=tot;++i) printf("%d ",ans[i]);
    return 0;
}
```

---

## 作者：songhn (赞：1)

~~写完才发现题目读错是一种怎样的体验~~

首先题目的大致意思是题目会给出一个图和一条路径 用路径上每个点的序号形成的序列来表示这个路径 我们要求该序列的一个子序列 使得从子序列的每一点到下一点走最短路径形成的序列就是原序列

我们可以先用$floyd$求出两两最短路 之后读入路径 我们设$pos$为当前选到的点  $i$为下一个将被选到的点 $pos$范围自然是$1\cdots m-1$

让$i$从$pos+1$开始枚举 当从$p_{pos}$到$p_i$的最短路径不等于$i-pos$时我们将$p_{i-1}$加入答案 同时令$pos=i-1$ 当$i$已经枚举到$m$时 我们直接将$p_m$加入答案并退出即可

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<vector>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
int n,a[110][110],m;
int s,t,tt[1000050];
string c[110];
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++) cin>>c[i];	
    for(int i=1;i<=n;i++)
    {
    	for(int j=1;j<=n;j++)
    	{
    		a[i][j]=c[i][j-1]-'0';
    		if(a[i][j]==0) a[i][j]=inf;
    	}
    }
    for(int i=1;i<=n;i++) a[i][i]=0;
    cin>>m;
    for(int i=1;i<=m;i++) cin>>tt[i];	
    
    for(int k=1;k<=n;k++)
    	for(int i=1;i<=n;i++)
    		for(int j=1;j<=n;j++)
    		a[i][j]=min(a[i][j],a[i][k]+a[k][j]);
    	
    vector<int> ans;
    ans.push_back(tt[1]);
    for(int pre=1;pre<m;)
    {
    	for(int i=pre+1;i<=m;i++)
    	{
    		if(a[tt[pre]][tt[i]]!=i-pre)
    		{
    			ans.push_back(tt[i-1]);
    			pre=i-1;
			}
			else if(i==m)
			{
				ans.push_back(tt[m]);
				pre=m;
			}
		}
	}
    cout<<ans.size()<<endl;
    for(int i=0;i<ans.size();i++) cout<<ans[i]<<" ";
    return 0;
}
```


---

## 作者：引领天下 (赞：1)

这个题其实还是挺简单的，但我还是想了很久~~而且还被hack了一次~~

思路：floyd+two-pointer+贪心

先floyd预处理出所有点之间的最短路，然后对于每个i找最靠后的j，满足$dis[p[i]][p[j+1]]>=dis[i][j]+1$，即**由p[i]到p[j+1]的最短路必过p[j]**

然后把退出循环的p[j]塞进答案数组，因为这个p[j]必须要去一次。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,p[1000005],a[105][105];
char x;
vector<int> ans;
int main(){
    ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
    cin>>n;
    for (int i=1;i<=n;i++)
    for (int j=1;j<=n;j++)a[i][j]=1926817;//初始化
    for (int i=1;i<=n;i++)
    for (int j=1;j<=n;j++){
        cin>>x;
        if(x=='1')a[i][j]=1;//读入图
    }
    for (int i=1;i<=n;i++)a[i][i]=0;
    for (int k=1;k<=n;k++)
    for (int i=1;i<=n;i++)
    for (int j=1;j<=n;j++)a[i][j]=min(a[i][j],a[i][k]+a[k][j]);//Floyd求最短路
    cin>>m;
    for (int i=1;i<=m;i++)cin>>p[i];
    int i=1,j=2;ans.push_back(p[1]);//p[1]是必到的
    for (;i<=m&&j<=m;){
        while(j<m&&a[p[i]][p[j+1]]>=a[p[i]][p[j]]+1)j++;//j<m保证了下标不越界，我们要找能满足p[i]到p[j+1]的最短路必过p[j]的最后一个j
        ans.push_back(p[i=j++]);//p[j]要停一次，不然的话可能下一次最短路不过p[j]
    }
    cout<<ans.size()<<endl;
    for (vector<int>::iterator it=ans.begin();it!=ans.end();it++)cout<<*it<<' ';//输出
}

---

## 作者：快斗游鹿 (赞：0)

## 思路

首先，考虑什么时候 $j$ 能成为 $i,k$ 间最短路的**必经点**，必经点的定义为存在一条 $i$ 到 $k$ 的最短路径经过 $j$。显然应当满足 $dis_{i,k}=dis_{i,j}+dis_{j,k}$，$j$ 才能成为必经点。接下来有一个结论，如果 $j$ 是 $i,k$ 的必经点，$k$ 是 $i,p$ 的必经点，则 $j,k$ 一定都是 $i,p$ 的必经点。为什么呢？因为 $dis_{i,k}=dis_{i,j}+dis_{j,k}$，$dis_{i,p}=dis_{i,k}+dis_{k,p}$，则有 $dis_{i,p}=dis_{i,j}+dis_{j,k}+dis_{k,p}$，这满足最短路的定义。所以该结论成立。

因此先跑一遍最短路，然后用两个指针不断按照上述结论判断即可。具体实现可参考代码。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=105;
const int M=1e6+5;
int n,a[N][N],f[N][N],m,c[M],d[M],cnt;
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
signed main(){
	freopen("std.in","r",stdin);
	memset(f,0x3f,sizeof(f));
	n=read();
	for(int i=1;i<=n;i++){
		string s;cin>>s;
		for(int j=1;j<=n;j++){
			a[i][j]=s[j-1]-'0';
			if(a[i][j])f[i][j]=a[i][j];
		}
	}
	m=read();
	for(int i=1;i<=m;i++)c[i]=read();
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
			}
		}
	}
	int lst=1;d[++cnt]=c[1];
	for(int i=2;i<=m;i++){
		//cout<<c[lst]<<" "<<c[i]<<" "<<c[i+1]<<" "<<f[c[lst]][c[i+1]]<<" "<<f[c[lst]][c[i]]<<" "<<f[c[i]][c[i+1]]<<endl;
		if(f[c[lst]][c[i+1]]==f[c[lst]][c[i]]+f[c[i]][c[i+1]]&&c[lst]!=c[i+1]){
			
		}
		else{
			d[++cnt]=c[i];lst=i;
		}
	}
	cout<<cnt<<endl;
	for(int i=1;i<=cnt;i++)cout<<d[i]<<" ";
	return 0;
}


```


---

## 作者：Otomachi_Una_ (赞：0)

## 题目简述

- 给你一个 DAG 上面的一条路径 $\{p_m\}$。
- 求 $p$ 上面包含 $p_1,p_m$ 的最短点列 $v$。
- $v$ 满足经过 $v$ 的最短路径为 $p$。
- $n\leq10^2,m\leq10^6$。

## 解题思路

$v$ 任意两点之间最短路径经过 $p$，即 $v_i(=p_x),v_{i+1}(=p_y)$ 间最短路为 $y-x$。

那也就是说我们要一个个去查，假设当前加入 $v$ 序列的队尾是 $v'(=p_x)$。那么当 $dis(v',p_i)\not = i-x$ 时必须选上 $p_{i-1}$。模拟即可。

## 参考代码

```cpp
#include<iostream>
#include<vector>
#include<cstdio>
using namespace std;
const int MAXN=1e2+5;
const int MR=1e6+5;
int dis[MAXN][MAXN];int n;
int p[MR];int m;
vector<int> v;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			scanf("%1d",&dis[i][j]);
			if(!dis[i][j])
				dis[i][j]=1e9;
			}
		dis[i][i]=0;
	}
	cin>>m;
	for(int i=1;i<=m;i++)
		cin>>p[i];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			for(int k=1;k<=n;k++)
				dis[j][k]=min(dis[j][k],dis[j][i]+dis[i][k]);
	v.push_back(p[1]);int lst=1;
	for(int i=2;i<=m+1;i++){
		if(dis[p[lst]][p[i]]!=i-lst)
			v.push_back(p[i-1]),lst=i-1; 
	}
	cout<<v.size()<<endl;
	for(int i=0;i<v.size();i++)
		cout<<v[i]<<" ";
	return 0;
}
```

---

