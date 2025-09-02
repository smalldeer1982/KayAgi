# Minimum path

## 题目描述

给你一个n×n的全是小写字母的矩阵,你能改变k个字母

你要从左上角走到右下角,且每步只能移动到右边或下边的字母上。

对于每一条路径都会得到一个由你经过的所有字母组成的字符串。当然,他的长度是2×n-1.

在你最多改动k个字母的情况下,找到一个得到字符串字典序最小的路径.

一个字符串a如果字典序比字符串b小,那他们第一个不同的字符在a中小于b.

## 样例 #1

### 输入

```
4 2
abcd
bcde
bcad
bcde
```

### 输出

```
aaabcde
```

## 样例 #2

### 输入

```
5 3
bwwwz
hrhdh
sepsp
sqfaf
ajbvw
```

### 输出

```
aaaepfafw
```

## 样例 #3

### 输入

```
7 6
ypnxnnp
pnxonpm
nxanpou
xnnpmud
nhtdudu
npmuduh
pmutsnz
```

### 输出

```
aaaaaaadudsnz
```

# 题解

## 作者：2344b (赞：1)

## 一个简单的dp
 这题打比赛的时候用BFS实现被卡了内存很是难受,赛后十分钟改成dp写法就过了此题。
 
[我的CSDN](https://blog.csdn.net/qq_41851959/article/details/83305496)
### 解法
先考虑没有修改。
因为要答案字典序最小，所以对于每一步能取最小的字母就取最小的。
又因为只能往下或者往右走，所以在走的步数一定时，走到的位置就可知。
既然这样，我们只要保证能更新答案的状态的字母是相同步数中最小的，就能保证取到最小的字典序。
就像下面这样。
```cpp
for(int step=1;step<n*2;step++){
    for(int j=max(1,step-n+1);j<=min(step,n);j++){
        int x=j,y=step-j+1;
        if(node[x-1][y].vis&&node[x-1][y].v==Min[step-1])
            node[x][y].vis=1;
        if(node[x][y-1].vis&&node[x][y-1].v==Min[step-1])
            node[x][y].vis=1;
        if(!node[x][y].vis)continue;
        Min[step]=min(Min[step],Map[x][y]);
    }
}
```
但是，cf加了一个修改的操作。
乍一看很难以操作，但是我们可以发现，改动的最优贡献肯定是把前缀非 "a" 的字母改为 "a"。
而此时前缀字母都相等时，最优的状态不就是有最少修改次数的情况嘛。
于是只需要对上面的代码小改一下。
```cpp
for(int step=1;step<n*2;step++){
    for(int j=max(1,step-n+1);j<=min(step,n);j++){
        int x=j,y=step-j+1;
        if(node[x-1][y].vis&&node[x-1][y].v==Min[step-1]){
            if(!node[x][y].vis){
                node[x][y].vis=1;
                node[x][y].f=node[x-1][y].f;
            }else{
                node[x][y].f=min(node[x][y].f,node[x-1][y].f);
            }
        }
        if(node[x][y-1].vis&&node[x][y-1].v==Min[step-1]){
            if(!node[x][y].vis){
                node[x][y].vis=1;
                node[x][y].f=node[x][y-1].f;
            }else{
                node[x][y].f=min(node[x][y].f,node[x][y-1].f);
            }
        }
        if(!node[x][y].vis)continue;
        if(node[x][y].f!=k&&node[x][y].Map!='a')node[x][y].f++,node[x][y].v='a';
        else node[x][y].v=node[x][y].Map;
        Min[step]=min(Min[step],node[x][y].v);
    }
}
```
这样就可以处理修改的操作了。
完整代码
```cpp
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<iostream>
using namespace std;
int n,k;
struct Node{
    int f;
    bool vis;
    char Map,v;
}node[2005][2005];
char Min[5000];
void Dp(){
    for(int step=1;step<n*2;step++){
        for(int j=max(1,step-n+1);j<=min(step,n);j++){
            int x=j,y=step-j+1;
            if(node[x-1][y].vis&&node[x-1][y].v==Min[step-1]){
                if(!node[x][y].vis){
                    node[x][y].vis=1;
                    node[x][y].f=node[x-1][y].f;
                }else{
                    node[x][y].f=min(node[x][y].f,node[x-1][y].f);
                }
            }
            if(node[x][y-1].vis&&node[x][y-1].v==Min[step-1]){
                if(!node[x][y].vis){
                    node[x][y].vis=1;
                    node[x][y].f=node[x][y-1].f;
                }else{
                    node[x][y].f=min(node[x][y].f,node[x][y-1].f);
                }
            }
            if(!node[x][y].vis)continue;
            if(node[x][y].f!=k&&node[x][y].Map!='a')node[x][y].f++,node[x][y].v='a';
            else node[x][y].v=node[x][y].Map;
            Min[step]=min(Min[step],node[x][y].v);
        }
    }
}
int main(){
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++){
        getchar();
        for(int j=1;j<=n;j++){
            scanf("%c",&node[i][j].Map);
            node[i][j].f=n*n;
        }
    }
    for(int i=1;i<n*2;i++)Min[i]='z';
    node[1][0].vis=node[0][1].vis=1;
    Dp();
    for(int i=1;i<n*2;i++)printf("%c",Min[i]);
}
```

---

## 作者：Piwry (赞：1)

试中写了个假的字符串比较调了半天...最后 10min 才发现自己写假了

dp 的状态感觉挺妙的...直接避免了比较字符串的问题

## 解析

首先能发现字符修改肯定是尽量早的用

于是设 $f(i, j)$ 表示从 $(0, 0)$（左上角）到达 $(i, j)$，经过的最少的非 `a` 的字符个数（包含 $(i, j)$）。这个随便 dp 下就行了

如果 $f(n-1, n-1)\leq k$，显然我们可以构造出一个全为 `a` 的路径，这一定是任何可能路径中字典序最小的；如果 $f(n-1, n-1)> k$，我们考虑找到所有满足 $f(x, y)=k$ 的位置 $\{(x_k, y_k)\}$

一种想法是考虑 dp 出每个位置 $(i, j)$ 到达 $(n-1, n-1)$（右下角）经过的字典序最小的路径中，$(i, j)$ 是向右走还是向下走；这样我们只需一一比较每个 $(x_k, y_k)$ 的 dp 的答案就行了。但发现转移时若出现 $(i+1, j), (i, j+1)$ 的字符相同的情况，我们就要比较后面路径的字典序；这等价于比较两个字符串的大小，很难优化（其实在刚才统计 $(x_k, y_k)$ 的 dp 答案时就有这个问题了）

我们考虑换一个状态。设 $dp(i)$ 表示从 $x_0, y_0$（一个指定的点）出发去往 $(n-1, n-1)$，经过长度为 $i$ 的最小字典序的路径的最后一个位置；注意该位置可能有多个（我们可以用 `vector` 存）。从 $dp(i)$ 转移到 $dp(i+1)$ 时，我们只需比较从 $dp(i)$ 的位置向下或向右走得到的位置上的字符大小，取字符最小的位置（也可能有多个）放入 $dp(i+1)$ 即可

由于 $dp(i)$ 中的位置的字符大小都应该是一致的，因此每次转移时，某个位置被多次放入 $dp(i+1)$ 是没有意义的。我们可以用一个 `vis` 数组记录，这样复杂度就是 $O(n^2)$ 的

至于答案，在 dp 时顺便输出即可

（一些实现细节没怎么提，具体可见代码）

## CODE

注意在从 $dp(i)$ 转移到 $dp(i+1)$ 时，代码中没有显式的去掉那些字符不是最小的位置；而是在下一次从 $dp(i+1)$ 转移到 $dp(i+2)$ 时，直接跳过那些字符不是最小的位置

```cpp
#include <cstdio>
#include <iostream>
#include <vector>
#define fi first
#define se second
using std::vector;
using std::pair;
using std::min;
typedef pair<int, int> pad;

const int MAXN =2e3+20;

char map[MAXN][MAXN];

int dp[MAXN][MAXN];/*从左上角到达每个点，( 含当前 ) 经过的最少的不为 a 的字符的个数*/
bool vis[MAXN][MAXN];

int main(){
	int n, k;
	scanf("%d%d", &n, &k);
	for(int i =0; i < n; ++i)
		scanf("%s", map[i]);
	
	for(int i =0; i < n; ++i)
		for(int j =0; j < n; ++j){
			if(i == 0 && j == 0)
				dp[i][j] =(int)(map[i][j] != 'a');
			else if(i == 0)
				dp[i][j] =dp[i][j-1]+(int)(map[i][j] != 'a');
			else if(j == 0)
				dp[i][j] =dp[i-1][j]+(int)(map[i][j] != 'a');
			else
				dp[i][j] =min(dp[i][j-1], dp[i-1][j])+(int)(map[i][j] != 'a');
		}
	
	if(dp[n-1][n-1] <= k){
		for(int i =0; i < 2*n-1; ++i)
			putchar('a');
	}
	else{
		int ans_len =0;
		vector<pad> nw;
		nw.push_back(pad(0, 0));
		for(int i =0; i < n; ++i)
			for(int j =0; j < n; ++j)
				if(dp[i][j] == k){
					if(i+j+1 > ans_len){
						{
							vector<pad> tmp;
							tmp.swap(nw);
						}
						ans_len =i+j+1;
						if(i < n-1)
							nw.push_back(pad(i+1, j));
						if(j < n-1)
							nw.push_back(pad(i, j+1));
					}
					else if(i+j+1 == ans_len){
						if(i < n-1)
							nw.push_back(pad(i+1, j));
						if(j < n-1)
							nw.push_back(pad(i, j+1));
					}
				}
		
		for(int i =0; i < ans_len; ++i)
			putchar('a');
		for(pad j:nw)
			vis[j.fi][j.se] =1;
		for(int i =0; i < 2*n-1 - ans_len; ++i){
			int mn =30;
			for(pad j:nw)
				if(map[j.fi][j.se]-'a' < mn)
					mn =map[j.fi][j.se]-'a';
			putchar('a'+mn);
			vector<pad> net;
			for(pad j:nw)
				if(map[j.fi][j.se]-'a' == mn){
					if(j.fi < n-1)
						if(!vis[j.fi+1][j.se]){
							net.push_back(pad(j.fi+1, j.se));
							vis[j.fi+1][j.se] =1;
						}
					if(j.se < n-1)
						if(!vis[j.fi][j.se+1]){
							net.push_back(pad(j.fi, j.se+1));
							vis[j.fi][j.se+1] =1;
						}
				}
			nw.swap(net);
		}
	}
}
```

---

## 作者：redegg (赞：1)

这题。。。不应该是黄题么。

优先队列+宽搜。

我们首先选择最短步数的走，这样可以保证步数一致，然后我们考虑相同步数里面选择字典序最小的走，走了后我们在相同步数下对比字典序，一部分字典序大的直接剪掉不走。对于字典序一样的我们选择改变数字量最少的走，这样可以保证最优的走法。

用一个标记数组，如果我已经走过一个点，那个走法一定是最优秀的，没有必要再走一遍。

```
#include <bits/stdc++.h>
using namespace std;

int n,m,k;

char in[2005];
int a[2005][2005];
int an[2005][2005];
int ans[4005];
bool vis[2005][2005];

struct ha
{
    int l,r,v,s,u;
    bool operator < (const ha &aa)const
    {
        if(s==aa.s&&v==aa.v)return u<aa.u;
        if(s==aa.s)return v<aa.v;
        return (s)<(aa.s);
    }
    bool operator > (const ha &aa)const
    {
        if(s==aa.s&&v==aa.v)return u>aa.u;
        if(s==aa.s)return v>aa.v;
        return (s)>(aa.s);
    }
};

priority_queue<ha,vector<ha>,greater<ha> > p;

bool check(int now,int x,int y)
{
    if(k-now>0&&a[x][y]!=0)
        return 1;
    else
        return 0;
}

int z[3]={1,0};

void bfs()
{
    for(int i=1;i<=2*n-1;i++)
        ans[i]=-1;
    ha first;
    first.l=1;
    first.r=1;
    first.s=1;
    first.u=0;
    if(check(0,1,1))
    {
        first.u=1;
        ans[1]=0;
    }
    else
        ans[1]=a[1][1];
    first.v=ans[1];
    p.push(first);

    while(!p.empty())
    {
        ha x=p.top();
        p.pop();
        if(ans[x.s]!=-1&&ans[x.s]<x.v)continue;
        if(ans[x.s]==-1){ans[x.s]=x.v;
        }
        for(int i=0;i<=1;i++)
        {
            int nx=x.l+z[i];
            int ny=x.r+z[1-i];
            ha nxt;
            if(nx>n||ny>n)continue;
            if(vis[nx][ny])continue;
            vis[nx][ny]=1;
            bool ok=check(x.u,nx,ny);
            nxt.l=nx;
            nxt.r=ny;
            nxt.s=x.s+1;
            nxt.u=x.u;
            if(ok)
            {
                nxt.u++;
                nxt.v=0;
            }
            else
                nxt.v=a[nx][ny];
            p.push(nxt);
        }
    }
}

int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
    {
        scanf("%s",in+1);
        for(int j=1;j<=n;j++)
        {
            a[i][j]=in[j]-'a';
        }
    }
    bfs();
    for(int i=1;i<=2*n-1;i++)
        printf("%c",ans[i]+'a');
    printf("\n");
    return 0;
}

```

---

## 作者：素质玩家孙1超 (赞：1)

[题目](https://codeforces.com/problemset/problem/1301/D)

挺有趣的一道题。

题意：给你一个$n*m$ 的方格，你在左上角。相邻之间的格子可以互相到达，每条路只能走一次，每个格子可以到达多次。问是否有方式可以精确走$k$步，有则输出方法。

列如一个$3*4$的方格

![](https://cdn.luogu.com.cn/upload/image_hosting/okv3dtuy.png)

---

稍微走走我们可以发现:

- 对于一个$n*m$的方格，我们一定可以找到若干方法走最多 (4nm−2n−2m) 步。

事实上我们只要想出一个可行的走法就好了。

走法不唯一，我的方法如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/vezhf9u1.png)

之后就是~~大~~模拟了。

我觉得模拟还是要多写写，像我这么菜的话比赛时就要花好多时间精力。

下面贴以下我的200行的~~垃圾~~代码（比赛时写的）

~~~cpp

#include<bits/stdc++.h>
using namespace std;
#define int long long 
struct step
{
	int f;
	char op[4];
	int l;
}a[100003];
inline int R()
{
	char c;int sign=1,res=0;
	while((c=getchar())>'9'||c<'0') if(c=='-') sign=-1;res+=c-'0';
	while((c=getchar())>='0'&&c<='9') res=res*10+c-'0';
	return res*sign;	
}
int n,m,k,s;
signed main()
{
	n=R();m=R();k=R();
	s=4*n*m-n-n-m-m;
	if(k>s)
	{
		puts("NO");
		return 0;
	}
	puts("YES");
	int now=0,top=0;
	if(k<m)
	{
		printf("1\n",1);
		printf("%d R",k);
		return 0;
	}
	if(m==1)
	{
		if(n-1>=k)
		{
			++top;
			a[top].f=k;
			a[top].op[0]='D';
			a[top].l=1;
			now=k;
		}
		else
		{
			++top;
			a[top].f=n-1;
			a[top].op[0]='D';
			a[top].l=1;
			now=n-1;
			
			++top;
			a[top].f=k-now;
			a[top].op[0]='U';
			a[top].l=1;
		}
		printf("%d\n",top);
		for(int i=1;i<=top;i++)
		{
//			A+=a[i].f*a[i].l;
			printf("%d ",a[i].f);
			for(int j=0;j<a[i].l;j++)
			{
				putchar(a[i].op[j]);
			}
			puts("");
		}
		return 0;
	} 
	now=m-1;
	++top;
	a[top].f=m-1;
	a[top].op[0]='R';
	a[top].l=1;
	int i=1;
	while(1)
	{
		if(now>=k) break;
		if(i==n)
		{
			if(now+(m-1)>=k)
			{
				++top;
				a[top].f=k-now;
				a[top].op[0]='L';
				a[top].l=1;
				now=k;
				break;
			}
			++top;
			a[top].f=m-1;
			a[top].op[0]='L';
			a[top].l=1;
			now+=m-1;
			
			++top;
			a[top].f=k-now;
			a[top].op[0]='U';
			a[top].l=1;
			now=k;
			break;
		}
		
		if(now+(m-1)>=k)
		{
			++top;
			a[top].f=k-now;
			a[top].op[0]='L';
			a[top].l=1;
			now=k;
			break;
		}
		if(m>1)
		{
			if(now+(m-1)*4<=k)
			{
				++top;
				a[top].f=m-1;
				a[top].op[0]='L';
				a[top].l=1;
				now+=m-1;
				
				++top;
				a[top].f=m-1;
				a[top].op[0]='D';
				a[top].op[1]='R';
				a[top].op[2]='U';
				a[top].l=3;
				now+=(m-1)*3;
				if(now+1<=k)
				{
					++top;
					a[top].f=1;
					a[top].op[0]='D';
					a[top].l=1;
					++i;
					++now;
				}
			}
			else
			{
				if(now+(m-1)>=k)
				{
					++top;
					a[top].f=k-now;
					a[top].op[0]='L';
					a[top].l=1;
					now=k;
					break;
				}
				else
				{
					++top;
					a[top].f=m-1;
					a[top].op[0]='L';
					a[top].l=1;
					now+=m-1;
					++top;
					a[top].f=(k-now)/3;
					a[top].op[0]='D';
					a[top].op[1]='R';
					a[top].op[2]='U';
					a[top].l=3;
					now+=a[top].f*3;
					if(now<k)
					{
						++top;
						a[top].f=1;
						a[top].op[0]='D';
						a[top].l=1;
						++now;
						if(now<k)
						{
							++top;
							a[top].f=1;
							a[top].op[0]='R';
							a[top].l=1;
							++now;
						}
					}
				}
			}
		}
	}
	int A=0;
	
	printf("%d\n",top);
	for(int i=1;i<=top;i++)
	{
//		A+=a[i].f*a[i].l;
		printf("%d ",a[i].f);
		for(int j=0;j<a[i].l;j++)
		{
			putchar(a[i].op[j]);
		}
		puts("");
	}
//	printf("%d\n",A);
}

~~~


---

## 作者：ThisIsLu (赞：0)

首先可以发现操作肯定用在前面，当然如果本身就为 `a` 就不用施法了。

所以定义 $g_{i,j}$ 从第 $1$ 行第 $1$ 列走到第 $i$ 行第 $j$ 列最少经过多少个非 `a` 字母。

下面设原矩阵的第 $i$ 行第 $j$ 列 为 $s_{i,j}$。

转移：
$$g_{i,j}=\min(g_{i,j-1},g_{i+1,j})+[s_{i,j}\not=\texttt{a}]$$

然后可以发现如果 $g_{i,j} \le k$，不妨把 $s_{i,j}$ 设为 `a`。

这样一来就消除 $k$ 的影响了。

然后接下来要求字典序最小的路径。

令 $dp_{i,j}$ 表示是否存在一条路径到第 $i$ 行第 $j$ 列的路径满足在所有以第 $1$ 行第 $1$ 列出发的经过 $i+j-1$ 个点的路径中字典序最小。

那么如果 $dp_{i,j-1}$ 和 $dp_{i-1,j}$ 都为否，则 $dp_{i,j}$ 也为否。

然后 $s_{i,j}$ 要在满足 $x+y=i+j$ 且 $dp_{x,y-1}$ 和 $dp_{x-1,y}$ 其中至少有一个成立的 $s_{x,y}$ 中最小。

除此之外就都是不成立的了。

最后算答案时从终点反过来走一遍就行了。

code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
const int N=2e3;
char s[N+5][N+5];
int g[N+5];
int dp[N+5][N+5];
int read(){
    int x=0;char ch;
    do{ch=getchar();} while(ch<'0'||'9'<ch);
    do{x=x*10+ch-'0';ch=getchar();} while('0'<=ch&&ch<='9');
    return x;
}
char ans[(N<<1)];
int main(){
    n=read();
    k=read();
    for(int i=0;i<=n;i++) g[i]=0x3f3f3f3f;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            do{s[i][j]=getchar();} while(s[i][j]<'a'||'z'<s[i][j]);
            if(i==1&&j==1) g[j]=(s[i][j]>'a');
            else g[j]=min(g[j-1],g[j])+(s[i][j]>'a');
            if(g[j]<=k) s[i][j]='a';    
        }
    }
    for(int i=0;i<=n;i++) dp[0][i]=dp[i][0]=0;
    dp[1][1]=1;
    for(int len=3;len<=(n<<1);len++){
        char minn='z';
        for(int i=max(1,len-n);i<min(n+1,len);i++){
            int j=len-i;
            if(dp[i-1][j]||dp[i][j-1]) minn=min(minn,s[i][j]);
        }
        for(int i=max(1,len-n);i<min(n+1,len);i++){
            int j=len-i;
            dp[i][j]=(s[i][j]==minn&&(dp[i-1][j]||dp[i][j-1]));
        }
    }
    int x=n,y=n;
    for(int i=(n<<1)-1;i>=1;i--){
        ans[i]=s[x][y];
        if(dp[x][y-1]) y--;
        else x--;
    }
    for(int i=1;i<(n<<1);i++) putchar(ans[i]);
    return 0;
}
```

---

## 作者：osfly (赞：0)

### some interesting things

哥们写破防了。

### 正文

若 $k>0$，容易发现最小的字典序一定是有 $\texttt{aaaaa....}$ 这样的前缀。

考虑 dp，处理出从 $[1,1]$ 走到 $[i,j]$ 路径上最少的非 $\texttt{a}$ 字符的数量。

容易得出：

$$
dp_{i,j}=\min\{dp_{i-1,j},dp_{i,j-1}\}+[s_{i,j}\not=\texttt{a}]
$$

其中，若命题 $p$ 成立，则 $[p]=1$，否则 $[p]=0$。

转移的时候请注意边界问题。

显然，把 $k$ 次替换操作用在前缀更优，所以我们先求出 $dp_{i,j}=k$ 且 $i+j-1$ 最大的那些点。（因为从 $[1,1]$ 走到这些点一定有最长的全 $a$ 前缀），将这些点塞入队列中。接下来暴力扩展。

枚举队列中的点所能到达的所有点，找出所有可达点最小的那个（这里的最小指字典序最小），将其塞入新的队列中。

显然，这种扩展至多进行 $2n-2-maxn$ 次，每次扩展至多扩展出 $n$ 个点所以时间复杂度是 $O(n^2)$ 的。这里 $maxn$ 指 $dp_{i,j}=k$ 的所有点中的 $\max\{i+j-1\}$。

至于输出，扩展的时候只需要把扩展的点标记一下，然后从 $[n,n]$ 一直走标记过的点倒推回 $dp=k$ 的点即可。这样时间复杂度是 $O(n)$ 的。

注意有两种情况：

1. $dp_{n,n}\leq k$，这时候输出全 $a$ 即可。

2. $k=0$，只需要将 $dp_{1,1}$ 更改为 $0$ 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define pa pair<string,pair<int,int> >

const int N=2010;

char s[N][N];
int dp[N][N];
int n,k;
int maxn;

int lstx[N*N],lsty[N*N],lst;
int nowx[N*N],nowy[N*N],now;
int vis[N][N];
int chk[N][N];

char str[N*N];
int tot;
int flag;
void dfs(int x,int y)
{
	if(dp[x][y]==k)
	{
		if(k) for(int i=1;i<=x+y-1;i++) printf("a");
		else printf("%c",s[x][y]);
		for(int i=tot;i>=1;i--) printf("%c",str[i]);
		return ;
	}
	str[++tot]=s[x][y];
	if(vis[x-1][y]) dfs(x-1,y);
	else if(vis[x][y-1]) dfs(x,y-1);
}

int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			scanf(" %c",&s[i][j]);
			dp[i][j]=s[i][j]!='a';
			if(i==1&&j==1) continue;
			else if(i==1) dp[i][j]+=dp[i][j-1];
			else if(j==1) dp[i][j]+=dp[i-1][j];
			else dp[i][j]+=min(dp[i-1][j],dp[i][j-1]);
		}
	if(dp[n][n]<=k)
	{
		for(int i=1;i<=n*2-1;i++) printf("a");
		return 0;
	}
	if(k==0) dp[1][1]=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(dp[i][j]==k)
			{
				chk[i][j]=1;
				maxn=max(maxn,i+j-1);
			}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(dp[i][j]==k&&i+j-1==maxn) lstx[++lst]=i,lsty[lst]=j,vis[i][j]=1;
	for(int i=1;i+maxn<2*n-1;i++)
	{
		now=0;
		int over=0;
		char minn='z';
		for(int i=1;i<=lst;i++)
		{
			int x=lstx[i],y=lsty[i];
			if(x<n) minn=min(minn,s[x+1][y]);
			if(y<n) minn=min(minn,s[x][y+1]);
		}
		for(int i=1;i<=lst;i++)
		{
			int x=lstx[i],y=lsty[i];
			if(x==n&&y==n) continue;
			if(x<n&&s[x+1][y]==minn&&!chk[x+1][y])
			{
				nowx[++now]=x+1,nowy[now]=y,vis[x+1][y]=1;
				chk[x+1][y]=1;
			}
			if(y<n&&s[x][y+1]==minn&&!chk[x][y+1])
			{
				nowx[++now]=x,nowy[now]=y+1,vis[x][y+1]=1;
				chk[x][y+1]=1;
			}
		}
		lst=now;
		for(int i=1;i<=now;i++) lstx[i]=nowx[i],lsty[i]=nowy[i];
	}
	dfs(n,n);
	return 0;
}
```

---

## 作者：龙之吻—水货 (赞：0)

# 1031D - Minimum path
## 题目描述
### [传送门](http://codeforces.com/problemset/problem/1031/D)
## 题目大意
给你一个$n \times n$的只有小写字母的字符矩阵，你要从$1,1$走到$n,n$，只能往下，往右走，同时你可以改变这个矩阵中的$k$个字符，问你走到$n,n$所经过的路径的最小字典序是多少。
$1 \le n \le 2000$
## Solution
宣传一下自己的博客QwQ [传送门](https://blog.csdn.net/graygoods/article/details/83274471)

比赛的时候最后5分钟才过去，保我上蓝QwQ
- 首先这道题要求字典序最小，所以我们改变这个矩阵中的字符，一定是把不是$a$的字符改成$a$，而且我们走一条路径的时候，一定是把所有机会全用到（如果$k$过大就可以全是$a$），并且尽可能地要让前面变成$a$。
所以我们设$f[i][j]$表示从$1,1$走到$i,j$全走$a$至少要改变多少次，由于只能向下和向右走，所以$f[i][j]$只可能从$f[i - 1][j], f[i][j - 1]$转移过来。DP复杂度$O(n^2)$。
- 之后，我们把$f[i][j] \le k$点找出来，找出所有走得最远的点，作为接下来$BFS$的起点（特别地，如果$k = 0$就需要把$1,1$选出来当作起点）。
- 进行BFS，我们看图说话：

![在这里插入图片描述](https://img-blog.csdn.net/20181022160123337?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2dyYXlnb29kcw==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)


- 假设红色的点为现在的起点，那么黄色箭头表示现在的的起点能前往的格子，我们找出现在能到达的格子中最小的字符，然后把带有最小字符的格子（也就是上图中的蓝色格子）存起来（同时给这个格子打一个标记，说明这个格子可以当作答案的一步），当作下一次的起点，重复上树的操作知道到达$n,n$，由于我们每进行一次操作，都相当于走了一步，所以最多进行$n$次这样的操作。

![在这里插入图片描述](https://img-blog.csdn.net/20181022160947477?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2dyYXlnb29kcw==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

- 看起来似乎状态是呈指数级增长的，BFS会爆掉，但实际上，我们发现，最坏的情况就是上图的情况，但是每层的情况数最多也只会达到$n$个，所以，BFS的复杂度为$O(n^2)$
- 至于输出答案，我们可以从$n,n$进行DFS，这个点上面或者左面哪一个点被打过标记，就往那边走，一直走到最初的起点。
之后输出$a$和找到的路径即可。

PS：这题解我改了又改，没想到把CSDN上自己的博客移植过来会有这么多锅QAQ，感谢管理员神仙的不辞辛劳QwQ。

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>

const int maxn = 2e3 + 7;

class Solution{
private :
    int n, k, cnt;
    char s[maxn][maxn];
    int f[maxn][maxn];
    bool vis[maxn][maxn];
    
    char ans[maxn * 2];
    int tot;

    struct Node{
        int x, y;

        Node (int x, int y) :
            x(x),
            y(y) {}
    };
    
    int now, last;
    std :: queue<Node> q[2], tmp;

    void Make() {
        for (register int i = 1; i + cnt < n + n; i++) {
            char z = 'z' + 1;
            while (!q[last].empty()) {
                Node nd = q[last].front();
                tmp.push(nd);
                q[last].pop();
                if (nd.x < n) {
                    z = std :: min(z, s[nd.x + 1][nd.y]);
                }
                if (nd.y < n) {
                    z = std :: min(z, s[nd.x][nd.y + 1]);
                }
            }
            while (!tmp.empty()) {
                Node nd = tmp.front();
                tmp.pop();
                if (nd.x < n) {
                    if (s[nd.x + 1][nd.y] == z && !vis[nd.x + 1][nd.y]) {
                        vis[nd.x + 1][nd.y] = 1;
                        q[now].push(Node(nd.x + 1, nd.y));
                    }
                }
                if (nd.y < n) {
                    if (s[nd.x][nd.y + 1] == z && !vis[nd.x][nd.y + 1]) {
                        vis[nd.x][nd.y + 1] = 1;
                        q[now].push(Node(nd.x, nd.y + 1));
                    }
                }
            }
            std :: swap(now, last);
        }
    }
    
    void DFS(int x, int y) {
    	if (x <= 0 || y <= 0) {
    		return;
		}
    	if (x + y == cnt) {
    		return;
		}
		ans[++tot] = s[x][y];
		if (vis[x - 1][y]) {
			DFS(x - 1, y);
		} else {
			DFS(x, y - 1);
		}
	}
    
public :
    Solution() {
        now = 1;
        last = 0;
        Get();
        Solve();
    }

    void Get() {
        scanf("%d %d", &n, &k);
        for (register int i = 1; i <= n; i++) {
            scanf("%s", s[i] + 1);
        }
    }

    void Solve() {
        memset(f, 0x3f, sizeof(f));
        f[1][1] = s[1][1] == 'a' ? 0 : 1;
        for (register int i = 1; i <= n; i++) {
            for (register int j = 1; j <= n; j++) {
            	if (i == 1 && j == 1) {
            		continue;
				}
                f[i][j] = std :: min(f[i - 1][j], f[i][j - 1]);
                if (s[i][j] != 'a') {
                    f[i][j]++;
                }
            }
        }
        for (register int i = 1; i <= n; i++) {
            for (register int j = 1; j <= n; j++) {
                if (f[i][j] <= k && i + j > cnt) {
                    cnt = i + j;
                }
            }
        }
        for (register int i = 1; i <= n; i++) {
            for (register int j = 1; j <= n; j++) {
                if (i + j == cnt && f[i][j] <= k) {
                    vis[i][j] = 1;
                    q[last].push(Node(i, j));
                }
            }
        }
        if (q[last].empty()) {
        	vis[1][1] = 1;
        	q[last].push(Node(1, 1));
		}
        Make();
        DFS(n, n);
        for (register int i = 1; i < cnt; i++) {
        	putchar('a');
		}
		for (register int i = tot; i >= 1; i--) {
			putchar(ans[i]);
		}
		putchar('\n');
    }
};
Solution sol;

int main() {}
```

---

## 作者：Haworthia (赞：0)

敲了4个小时终于过了啊……CF上交了16遍才过，必须发篇题解慰劳一下自己……

下面我来说一下我拿到这题的思路吧，题目上说是可以修改$k$个字符，显然就是改成$a$,而地图中已经是$a$的就不用改了，所以路径中$a$越多越好。

1.从左上角开始搜，遇到不是字符$a$就步数加1，是$a$就不加，找到步数为$k$的点。定义它们的$dis$=横纵坐标相加再减一，那么，在答案的字符串中，第1~$dis$个字符都是$a$了，显然$dis$越大越好。

2.以第一步找到的步数为$k$的点为第二次搜索的起点，对于每一条路径，用数组$s$记录每一个点的值（即Map[fx][fy]，详细见代码），最后判断$s$的字典序是否小于已有的$ans$,如果是就更新$ans$。

$A$了以后我发现，其实我的思路是基本正确的，只是采用的算法太过拙劣：第一步采用的是$bfs$，于是就$T$了（而且第4个点就$T$了，n才100）。不知悔改的我$T$了四遍，一直想怎么剪枝，最后终于$MLE$了。

于是我终于翻了大佬们的题解，才知道第一步可以用$dp$代替第一步的搜索。于是终于不$T$了，然而$WA$在了第八个点。因为我只看了题解的思路，没看代码所以细节处理失误，又$WA$了七遍……

还是看代码吧：

```
#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int n,k,mx,dx[]={0,1},dy[]={1,0};
int dp[2010][2010],mn[4010];//mn存的是答案，mn[i]表示字典序最小的路径在x+y-1(即dis)==i时的值 
bool vis[2010][2010];
char Map[2010][2010];//存地图的 
struct node
{
	int x,y,step;
};
queue<node>q;
void bfs()//第二步的搜索，dfs按理应该也行 
{
	if(q.empty())//拙劣的特判1，处理k==0的情况，就只将(1,1)入队列 
	{
		q.push((node){1,1,1});
		mn[1]=Map[1][1]-'a';//同理mn数组的第一个值就是Map[1][1]了 
	}
	while(!q.empty())
	{
		node now=q.front();
		q.pop();
		int x=now.x,y=now.y,step=now.step;
		if(Map[x][y]-'a'>mn[step]||step<mx)//如果bfs到的点的Map值大于答案数组，直接出队列不再扩展 
			continue;
		for(int i=0;i<2;++i)
		{
			int fx=x+dx[i],fy=y+dy[i];
			if(fx<=n&&fy<=n&&mn[step+1]>=Map[fx][fy]-'a'&&!vis[fx][fy])
			{
				vis[fx][fy]=1;
				mn[step+1]=Map[fx][fy]-'a';//当前点的Map值小于等于答案数组，则更新 
				q.push((node){fx,fy,step+1});
			}
		}
	}
}
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;++i)
		scanf("%s",Map[i]+1);
	memset(mn,0x3f,sizeof mn);//mn初始化为最大 
	memset(dp,0x3f,sizeof dp);
	dp[1][0]=dp[0][1]=0;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
		{
			dp[i][j]=min(dp[i-1][j],dp[i][j-1])+(Map[i][j]=='a'?0:1);//第一步的内容，dp[i][j]表示该点的步数 
			if(dp[i][j]==k&&mx<=i+j-1)//如果步数恰好为k，且i+j-1(即dis)越大越好
			{
				mx=i+j-1;//更新dis的最大值mx 
				vis[i][j]=1;
				q.push((node){i,j,i+j-1});//入队列 
			}
		}
	bfs();
	if(dp[n][n]<k)//拙劣的特判2，答案全部为a的情况 
	{
		for(int i=1;i<2*n;++i)
			printf("a");
		return 0;
	}
	for(int i=1;i<=mx;++i)//前mx个都是a 
		printf("a");
	for(int i=mx+1;i<2*n;++i)//后面的答案存在mn数组里了 
		printf("%c",mn[i]+'a');//因为mn存的是int，所以加回来 
	return 0;
}
```


---

