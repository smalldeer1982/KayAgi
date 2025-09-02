# VIDEO - Video game combos

## 题目描述

 Bessie is playing a video game! In the game, the three letters 'A', 'B', and 'C' are the only valid buttons. Bessie may press the buttons in any order she likes. However, there are only N distinct combos possible (1 <= N <= 20). Combo i is represented as a string S\_i which has a length between 1 and 15 and contains only the letters 'A', 'B', and 'C'.

 Whenever Bessie presses a combination of letters that matches with a combo, she gets one point for the combo. Combos may overlap with each other or even finish at the same time! For example if N = 3 and the three possible combos are "ABA", "CB", and "ABACB", and Bessie presses "ABACB", she will end with 3 points. Bessie may score points for a single combo more than once.

 Bessie of course wants to earn points as quickly as possible. If she presses exactly K buttons (1 <= K <= 1,000), what is the maximum number of points she can earn?

## 样例 #1

### 输入

```
3 7
ABA
CB
ABACB```

### 输出

```
4```

# 题解

## 作者：D_14134 (赞：4)

我们可以先想这道题的暴力解法： **dp**

时间复杂度是 _O （n*3^15）_。

看到多字符串匹配问题，自然想到了ac自动机。于是思路就很清晰了————先用自动ac机跑出trie树，然后跑树上DP。时间复杂度 _O(n*300）_ 。

dp方程也很好想:

f[step+1][i]=max(f[step+1][i],f[step][u]+vis[i]);

ans=max(ans,f[m][i]);
# code
```
#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
using namespace std;
queue<int> q;
char s[30];
int n,m,size=1;
int tree[310][10],vis[310],fail[310],dp[1010][310],f[1010][310];
void insert(char *s,int id){
	int u=1,n=strlen(s);
	for (int i=0;i<n;i++){
		int c=s[i]-'A';
		if(!tree[u][c]) tree[u][c]=++size;
		u=tree[u][c];
	}
	vis[u]=1;
}
void get_fail(){
	int rt=1;
	fail[rt]=1;
	for (int i=0;i<3;i++){
		int u=tree[rt][i];
		fail[u]=rt;
		if(u) {fail[u]=rt;q.push(u);}
		else tree[rt][i]=rt;
	}
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=0;i<3;i++){
			int v=tree[u][i];
			if(v){
				fail[v]=tree[fail[u]][i];
				q.push(v);
			}
			else tree[u][i]=tree[fail[u]][i];
		}
		if(vis[fail[u]]) vis[u]+=vis[fail[u]];
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%s",s);
		insert(s,i);
	}
	get_fail();
	dp[0][1]=1;
	for(int step=0;step<m;step++){
		for(int u=1;u<=size;u++){
			if(dp[step][u]!=0){
				for(int v=0;v<3;v++){
					int i=tree[u][v];
					dp[step+1][i]=dp[step][u];
					f[step+1][i]=max(f[step+1][i],f[step][u]+vis[i]);
				}
			}
		}
	}
	int ans=0;
	for(int i=1;i<=size;i++) ans=max(ans,f[m][i]);
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：ez_lcw (赞：2)

# AC自动机+dp

这道题的思路是**AC自动机+dp**。

首先我们先按照AC自动机的模板，把所有字符串插入到字典树里，并且求出每一个节点的$fail$值。

------------

然后我们设置辅助参数：$num[]$。

**其中$num[i]$表示字典树中节点$i$表示的字符串的后缀中有多少个是题目给的串之一。（此处所指的“后缀”包括这个串本身，下文也一样）**

那我们怎么把$num[]$求出来呢？

其实很简单，**因为$t[u].fail$肯定是$u$的后缀，又因为$bfs$的有序性，即先访问了$t[u].fail$才会访问$u$，**

所以只用在求$fail$的时候在每次$while$循环结尾加这一行字就行了：
```cpp
t[u].num+=t[t[u].fail].num;
```

------------

然后我们设一个$dp[][]$，**其中$dp[i][j]$表示最后输出的串的前$i$个字符中最后一位为节点$j$的情况下的最大分数。**

很显然，$ans=\max(dp[k][1...tot])$，$tot$为trie树上的点数。

那么状态转移方程是：

$$dp[i][ch[j][k]]=\max(dp[i][ch[j][k]],dp[i-1][j]+num[ch[j][k]])$$

~~max()里的第一位应该不用解释了吧~~

$max()$里的第二位意思就是**当前节点的$i-1$位的最大分数+将儿子节点加入字符串所获得的分数**。

------------

那么最后的代码如下：

```cpp
#include<bits/stdc++.h>

#define L 3010
#define K 1010

using namespace std;

struct trie
{
    int ch[4],fail,num;
}t[L];

int tot,n,k;

void insert()
{
    char ch[20];
    scanf("%s",ch);
    int len=strlen(ch),u=0;
    for(int i=0;i<len;i++)
    {
        int v=ch[i]-'A';
        if(!t[u].ch[v])t[u].ch[v]=++tot;
        u=t[u].ch[v];
    }
    t[u].num++;
}

void getfail()
{
    queue<int>q;
    for(int i=0;i<3;i++)if(t[0].ch[i])q.push(t[0].ch[i]);
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        for(int i=0;i<3;i++)
        {
            if(t[u].ch[i])
            {
                t[t[u].ch[i]].fail=t[t[u].fail].ch[i];
                q.push(t[u].ch[i]);
            }
            else t[u].ch[i]=t[t[u].fail].ch[i];
        }
        t[u].num+=t[t[u].fail].num;
    }
}
int dp[K][L];
int query()
{
    int ans=0;
    memset(dp,128,sizeof(dp));
    dp[0][0]=0;
    for(int i=1;i<=k;i++)
    {
        for(int j=0;j<=tot;j++)
        {
            for(int k=0;k<3;k++)
            {
                dp[i][t[j].ch[k]]=max(dp[i][t[j].ch[k]],dp[i-1][j]+t[t[j].ch[k]].num);
            }
        }
    }
    for(int i=1;i<=tot;i++)ans=max(ans,dp[k][i]);
    return ans;
}

int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)insert();
    getfail();
    printf("%d\n",query());
    return 0;
}
```

###### [双倍经验点这里](https://www.luogu.org/problemnew/show/P3041)

---

## 作者：ZHR100102 (赞：1)

弱智紫题，20min 一眼了，dp 思路非常板。

多模式串一看肯定就是要建出 AC 自动机，然后在 fail 树里下传标记，预处理每个节点到达后的得分。

然后设计 $dp_{i,j}$ 表示第 $i$ 个字符，AC 自动机里匹配节点在 $j$ 的最大答案，刷表法转移即可：

$$dp_{i+1,ch_{j,c}} \gets \max(dp_{i+1,ch_{j,c}},dp_{i,j}+con_{ch_{j,c}})$$

时间复杂度 $O(nk\left|S\right|)$。

# 代码

```cpp
#include <bits/stdc++.h>
#define fi first
#define se second
#define lc (p<<1)
#define rc ((p<<1)|1)
#define eb(x) emplace_back(x)
#define pb(x) push_back(x)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ldb;
using pi=pair<int,int>;
int n,m;
int ch[305][5],idx=0,ne[305],tot[305],dp[1005][305],ans=0;
char s[20];
vector<int>g[305];
void insert(char *s)
{
    int p=0;
    for(int i=1;s[i];i++)
    {
        int c=s[i]-'A';
        if(ch[p][c]==0)ch[p][c]=++idx;
        p=ch[p][c];
    }
    tot[p]++;
}
void build()
{
    queue<int>q;
    for(int i=0;i<3;i++)
    {
        if(ch[0][i])q.push(ch[0][i]);
    }
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        for(int i=0;i<3;i++)
        {
            int v=ch[u][i];
            if(v)ne[v]=ch[ne[u]][i],q.push(v);
            else ch[u][i]=ch[ne[u]][i];
        }
    }
}
void dfs1(int u)
{
    for(auto v:g[u])
    {
        tot[v]+=tot[u];
        dfs1(v);
    }
}
void init()
{
    for(int i=1;i<=idx;i++)g[ne[i]].push_back(i);
    dfs1(0);
}
int main()
{
    //freopen("sample.in","r",stdin);
    //freopen("sample.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        cin>>s+1;
        insert(s);
    }
    build();
    init();
    memset(dp,-0x3f,sizeof(dp));
    dp[0][0]=0;
    for(int lv=0;lv<m;lv++)
    {
        for(int p=0;p<=idx;p++)
        {
            for(int i=0;i<3;i++)
            {
                int v=ch[p][i];
                dp[lv+1][v]=max(dp[lv+1][v],dp[lv][p]+tot[v]);
            }
        }
    }
    for(int i=0;i<=idx;i++)ans=max(ans,dp[m][i]);
    cout<<ans;
    return 0;
}
```

---

## 作者：Charlie_ljk (赞：1)

- 多倍经验 [P3041](https://www.luogu.com.cn/problem/P3041)。

相当板的 AC 自动机优化 DP。

把 AC 自动机建出来，设 $f_{i,j}$ 表示处理到第 $i$ 位，当前处于 AC 自动机上的节点 $j$ 时的最大值。那么显然有转移：

$$f_{i,son_p}=\max(f_{i,son_p},f_{i-1,p}+sum_{son_p})$$

最终答案为 $\max\limits_{i=0}^{tot}\{f_{k,i}\}$。

建 AC 自动机的时候节点 $p$ 继承 $fail_p$ 的 $sum$ 即可，注意 DP 初始化为极小值。

```cpp
#include<bits/stdc++.h>
#define ll long long 
#define endl '\n'
#define sort stable_sort
#define son(p,c) trie[p].son[c]
#define fail(p) trie[p].fail
#define end(p) trie[p].end
using namespace std;
const int N=25;
template<typename Tp> inline void read(Tp&x)
{
	x=0;register bool z=true;
	register char c=getchar();
	for(;c<'0'||c>'9';c=getchar()) if(c=='-') z=0;
	for(;'0'<=c&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	x=(z?x:~x+1);
}
template<typename T,typename ...Tp> inline void read(T &x,Tp &...y){read(x);read(y...);}
template<typename Tp> inline void wt(Tp x)
{if(x>9)wt(x/10);putchar((x%10)+'0');}
template<typename Tp> inline void write(Tp x)
{if(x<0)putchar('-'),x=~x+1;wt(x);}
template<typename T,typename ...Tp> inline void write(T x,Tp ...y){write(x);putchar(' ');write(y...);}
int n,m,tot,ans,f[2][N*N];
struct aa {int son[3],fail,end;}trie[N*N];
void insert(char s[])
{
	int p=0;
	for(int i=0,c;s[i];i++) 
	{
		c=s[i]-'A';
		if(!son(p,c)) son(p,c)=++tot;
		p=son(p,c);
	}
	end(p)++;
}
void build()
{
	queue<int>q;
	for(int i=0;i<3;i++) if(son(0,i)) q.push(son(0,i));
	while(!q.empty())
	{
		int x=q.front(); q.pop();
		for(int i=0,y,z;i<3;i++)
		{
			y=son(x,i),z=fail(x);
			if(!y) {son(x,i)=son(z,i); continue;}
			fail(y)=son(z,i);
			end(y)+=end(fail(y));
			q.push(y);
		}
	}
}
signed main()
{
	read(n,m); char s[N];
	for(int i=1;i<=n;i++) scanf("%s",s),insert(s);
	build(); memset(f,128,sizeof(f)),f[0][0]=0;
	for(int i=1;i<=m;i++)
	{
		memset(f[i&1],128,4*(tot+1));
		for(int p=0;p<=tot;p++) 
			for(int c=0,y=son(p,0);c<3;c++,y=son(p,c))
				f[i&1][y]=max(f[i&1][y],f[(i-1)&1][p]+end(y));
	}
	for(int i=0;i<=tot;i++) ans=max(ans,f[m&1][i]);
	write(ans);
}
```

---

## 作者：Engulf (赞：1)

在阅读之前确保您已经掌握 AC 自动机。

## 思路

这是一道非常经典的题目，**AC 自动机上 dp**。

由于 combo 串很多，而答案又跟单词 **是否出现** 有关，这启发我们可以使用 AC 自动机来处理。

而最终的答案又是个最大化问题，显然可以使用 dp 来解决。

我们构建出所有 combo 的 AC 自动机，然后进行 dp。

## 状态表示

$f_{i, j}$ 表示长度为 $i$ 的字符串，处于状态 $j$（可以理解为 trie 上的 $j$ 号节点）的最大分数。

## 状态计算

首先需要解决一个问题：如何确定当前转移到的节点能否为答案增加贡献？

一般这些东西都能在构建 AC 自动机的时候完成。

对于节点 $p$，他的 fail 指针指向的节点结尾的那段前缀一定是 $p$ 的其中一段后缀，又根据 bfs 的层次性和 fail 指针的定义，fail 的贡献一定已经被计算好了，此时直接累加答案即可。

此时状态转移方程很好推了：

$f_{i + 1, p} = \max\{f_{i + 1, p}, f_{i, j} + c_p\}$。

$p$ 是当前枚举到的节点。

## 边界问题

这是一个小问题。

一开始把 $f$ 初始化为 $-\infty$，$f_{0, 0} = 0$ 即可。

如果我们不把 $f$ 初始化为 $-\infty$，就有可能出现从一些非法的状态转移过来。

## 时间复杂度

构建 AC 自动机 $\mathcal{O}(\sum|s_i|)$，dp $\mathcal{O}(k)$。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define sz(v) (int)v.size()
#define pb push_back
#define ppb pop_back
#define allarr(v, len) v.begin() + 1, v.begin() + len + 1

typedef long long LL;
typedef pair<int, int> PII;

const int inf = 0x3f3f3f3f;
const LL infLL = 0x3f3f3f3f3f3f3f3fLL;

const int N = 305;
int n, m;
int tr[N][3], cnt[N], fail[N], idx;

char s[20];

int f[1005][N];

void insert(char *str)
{
	int p = 0;
	for (int i = 0; str[i]; i ++ )
	{
		if (!tr[p][str[i] - 'A']) tr[p][str[i] - 'A'] = ++ idx;
		p = tr[p][str[i] - 'A'];
	}
	cnt[p] ++ ;
}
void build()
{
	queue<int> q;
	for (int i = 0; i < 3; i ++ ) if (tr[0][i]) q.push(tr[0][i]);
	while (sz(q))
	{
		int p = q.front(); q.pop();
		for (int i = 0; i < 3; i ++ )
			if (!tr[p][i]) tr[p][i] = tr[fail[p]][i];
			else
			{
				fail[tr[p][i]] = tr[fail[p]][i];
				cnt[tr[p][i]] += cnt[fail[tr[p][i]]];
				q.push(tr[p][i]);
			}
	}
}

int main()
{
	ios::sync_with_stdio(false), cin.tie(nullptr);
	cin >> n >> m;
	for (int i = 1; i <= n; i ++ )
		cin >> s, insert(s);
	build();
	memset(f, -inf, sizeof f);
	f[0][0] = 0;
	for (int i = 0; i < m; i ++ )
		for (int j = 0; j <= idx; j ++ )
			for (int k = 0; k < 3; k ++ )
			{
				int p = tr[j][k];
				f[i + 1][p] = max(f[i + 1][p], f[i][j] + cnt[p]);
			}
	int res = 0;
	for (int i = 0; i <= idx; i ++ ) res = max(res, f[m][i]);
	cout << res << "\n";
	return 0;
}
```

---

## 作者：一铭君一 (赞：1)

题解区逛了一圈，发现我的转移和大家不太一样，于是跑来发个题解。

## 题意

给你 $N$ 个模式串，你需要构造一个长度为 $k$ 的文本串，使得所有模式串在文本串中出现次数总和最多，求这个最多的次数。

## Solution

首先看到多模式串匹配不难想到 AC 自动机。

因为本题的文本串需要我们构造，但是一共有 $3^k$ 种文本串，如果直接枚举的话肯定炸了。

其实很多文本串都是没啥用的，因为它和给出的模式串相去甚远。我们不如直接在 AC 自动机上统计答案，考虑 DP 。

### 方程

PS：AC 自动机+DP 的题一般挺套路的，大部分是设 $f[i][j]$ 表示当前构造了长度为 $i$ 的文本串，走到了自动机上的节点 $j$ ，转移则一般是从 Trie 上从父亲转移到儿子。

回到本题，我们设 $f[i][j]$ 表示长度为 $i$ 的文本串，匹配到节点 $j$ 时能产生的最大匹配次数。

这时通过向每一个状态之后添加字母就可以转移到下一个状态了。枚举下一位填什么字母（枚举当前状态所在节点 $j$ 的所有儿子），于是可以写出转移方程：

$$f[i+1][v]=\max(f[i+1][v],f[i][j]+val[v])$$

其中 $val[v]$ 表示走到节点 $v$ 可以匹配上几个模式串。

一般的做法是从 $v$ 跳 fail 到根，统计路径上模式串末尾标记之和。为了快速转移，我们预处理 $val[v]$ 表示节点 $v$ 到 fail 树根的路径上模式串末尾标记之和，这样就可以 $O(1)$ 转移。

### 初始状态与目标状态

初始状态当然是空串的时候啦，即 $f[0][j]=0$ 。

我们需要的是长度为 $k$ 的时候的最大匹配次数，即 $\max_i^{cnt} f[k][i]$ ，其中 $cnt$ 为自动机中节点数。

### 转移

我们的方程可以从长度为 $i$ 转移到长度为 $i+1$ ，枚举长度，按照长度依次转移。

对于每个点，它都可以从它转移到它的某个儿子，枚举每个节点的所有儿子，按照上面的方程转移。

于是我写出了这样的代码：

```cpp
for(int i=0;i<=_k;++i)
    for(int j=0;j<=siz;++j)
      for(int k=0;k<3;++k){
        int v=tr[j].ch[k];
        f[i+1][v]=std::max(f[i+1][v],f[i][j]+tr[v].tag);
      }
```

~~然后发现这货连样例也过不了。~~

一顿调试之后，发现我们的状态出了点小问题。

我们在枚举从每个节点开始转移的时候，有些节点是位于模式串末尾的。这些节点转移的时候会把该模式串记录答案。

但是有时候我们正在构造的文本串比它所属的模式串短，也就是这个模式串实际上还没有出现在文本串中，但是已经被统计上了。那么刚才的方法会导致答案变大。

拿样例举个例子吧：

![](https://cdn.luogu.com.cn/upload/image_hosting/s4upc56c.png)

这样我们从 $f[2][0]=0$ 转移的时候，会转移出这样一个状态：$f[1][3]=1$，也就是我们只花了 1 的长度就构造出了 'ABA' 这个模式串，这样显然不合法。~~（我愿称这张图为帕金森自动机）~~

记录每个节点在 Trie 中的深度，只有正在构造的文本串长度 $i$ 比这个节点在 Trie 中的深度大，才有可能在 $i$ 个字符之内走到这个节点。否则这个状态就不合法，我们拒绝转移它。

转移的时候先特判一下，如果这个状态合法再转移。

## Code

```cpp
int n,_k;
char ch[15];
int f[1005][305];

int siz,dep[305];
std::vector<int>to[305];
struct Trie{
  int tag,fail;
  int ch[4];
}tr[305];
void Build_Trie(){
  int len=std::strlen(ch),u=0;
  for(int i=0;i<len;++i){
    int s=ch[i]-'A';
    if(!tr[u].ch[s]) tr[u].ch[s]=++siz;
    dep[tr[u].ch[s]]=dep[u]+1;
    u=tr[u].ch[s];
  }
  ++tr[u].tag;//正常往 Trie 树中塞字符串，记录深度
}
void make_fail(){
  std::queue<int>q;
  for(int i=0;i<3;++i)
    if(tr[0].ch[i]){
      tr[tr[0].ch[i]].fail=0;
      q.push(tr[0].ch[i]);
      to[0].push_back(tr[0].ch[i]);
    }
  while(q.size()){
    int u=q.front();
    q.pop();
    for(int i=0;i<3;++i){
      int v=tr[u].ch[i];
      if(v){
        tr[v].fail=tr[tr[u].fail].ch[i];
        to[tr[v].fail].push_back(v);
        q.push(v);
      }else tr[u].ch[i]=tr[tr[u].fail].ch[i];
    }//求 fail 同时构造 fail 树
  }
}
void dfs(const int x){
  for(int i=0;i<to[x].size();++i){
    int y=to[x][i];
    tr[y].tag+=tr[x].tag;
    dfs(y);
  }
}//预处理 上面说的val[]数组

signed main(){
  // freopen("simple.txt","r",stdin);
  read(n),read(_k);
  for(int i=1;i<=n;++i){
    scanf("%s",ch);
    Build_Trie();
  }
  make_fail();
  dfs(0);
  for(int i=0;i<=_k;++i)
    for(int j=0;j<=siz;++j)
      for(int k=0;k<3;++k){
        int v=tr[j].ch[k];
        if(dep[v]<=i+1) f[i+1][v]=std::max(f[i+1][v],f[i][j]+tr[v].tag);
        //记得特判
      }
  int ans=0;
  for(int i=0;i<=siz;++i)
    ans=std::max(ans,f[_k][i]);//从所有最终状态取最大的
  write(ans),putchar('\n');
  return 0;
}
```

---

## 作者：Monad (赞：1)

### 题意
大意：给你一些关键词 `S[]`，然后让你构造一个指定长度的字符串 `T`（都只有 `ABC` 三种字符），使每个 `S[i]` 在 `T` 中的出现次数的和最大，并且输出这个数值。  

### 做法
首先这道题可以用 DP，因为我们肯定要枚举 `T` 的长度，所以我们可以把 `f` 加一维 `i`，用 `f[i]` 表示前 `i` 个字符。  
然后因为每个 `S` 的长度不超过 `15`，为了转移，我们要把这 `15` 个字符记录为一个状态，总数为 $3^{15}$ 个，也就是用 `f[i][j]` 表示在前 `i` 个字符中，以 `j` 结尾的最大匹配次数为多少。  
这样的状态我相信你们随便推一推就可以推出来，所以这里不细讲了。

### 优化
如果真的按照上面那种做法的话，那么时间复杂度便是 $O(n \times 3^{15} \times 3)$，非常危险（空间也是）。可不可以优化一下呢？  
我们可以想，要优化 `DP` 无非就是要削减状态数或是优化转移方程两种方法而已。转移方程每次只要考虑 `3` 种字符的情况即可，优化空间较小。  
但是转移方程记录那么多真的有用吗？不一定。  

---

我们可以想，记录 $3^{15}$ 的状态真的有用吗？拿样例来举例子吧，例如：  
```
3 7
ABC
CB
ABBCB
```
假如我们有一个状态是 `CCCCC`，记那么多有用吗？显然没有，因为 `CCCCC` 在现在和将来都不能对答案有贡献，也就是不能构成新的串，所以 `CCCCC` 是一点用都没有的。  
既然有一些状态没有用，所以我们就可以想：哪些状态是有用的呢？  
显然，能在以后对答案有贡献的状态都是有用的。而且，能在以后组成 `S` 的状态一定都是 `S` 的前缀，对于样例，`A`、`ABAC`、`C` 都可能对答案有贡献。所以我们的状态就可以压缩成非常小。  

---

然后，我们如何转移呢？  
我们考虑一个状态：`AB`，再加一个字符就可以组成 `ABA`、`ABB`、`ABC`。  

1. 对于 `ABA`，`ABA` 本身（整个）是不能对答案有贡献的，所以它的后缀 `A` 可能对答案有贡献（`ABC` 或 `ABBCB`），所以我们就去掉 `AB`，保留后缀 `A`，让 `A` 成为一个新的状态；  
2. 对于 `ABB`，它可以对 `ABBCB` 有贡献，所以我们要保留整个 `ABB`；  
3. 对于 `ABC`，与 1 同理，只用剩下 `C` 即可。  

这样做就可以大幅减少时间和空间使用了。

#### AC 自动机？
看完上面整个过程，有些人可以觉得与 AC 自动机有些类似。  
没错！它就是 AC 自动机，上面保留前缀的过程就是 AC 自动机上的点，抛弃无用的前缀则与 AC 自动机的匹配过程非常类似。  
所以我们可以用 `f[i][j]` 表示在前 `i` 个字符中，在 `j` 节点时的最大匹配次数为多少。然后转移就是想 AC 自动机匹配时那样转移即可。  
最后统计 `f[k][i]` （`i` 为所有节点）的和即可。  
  
  
  
原文链接：[\[SPOJ\] Video game combos](https://blog.monad.ga/2018/05/17/Trie-optimize-DP/)

---

## 作者：lhz2022 (赞：0)

我们考虑 dp。

我们知道，trie 树上的一个点到根节点的路径可以表示一个字符串，于是我们设 $dp_{i,j}$ 代表已经按下 $i$ 个按键，当前在 trie 树上第 $j$ 个端点的最大值。特别的，当 $j=0$ 时，代表在根节点上。

转移为 $dp_{i,tr_{j,k}}=\max(dp_{i,tr_{j,k}},dp_{i-1,j}+val_{tr_{j,k}})$。

其中，$tr_{j,k}$ 的含义是 trie 树上第 $j$ 个节点的儿子种表示字符 $k$ 的节点，$val$ 数组代表了在 trie 树上每个节点是多少种连招的结尾。容易发现，$val$ 数组可以在构建 AC 自动机时求出。

那么按照如上方式进行 DP 即可，答案即为 $\max_{i=1}^{tot} dp_{k,i}$，$tot$ 代表 trie 树的节点数目。

[代码](https://www.luogu.com.cn/paste/9tjnclj9)

---

## 作者：cff_0102 (赞：0)

解法：AC 自动机 + dp。
 
首先先把 AC 自动机建出来，接着进行 dp。设 $dp_{i,j}$ 表示输入 $i$ 个字符，输入完最后一个字符后停在自动机的 $j$ 点时最多获得几分。转移就枚举下一步输入的字母，并且对应看输入下一个字母后会多出几个能加分的后缀子串，加上相应的得分即可。最后的答案就是所有 $dp_{k,i}$ 取最大值。
 
注意 dp 数组的初始化。
 
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=309,K=1010;
int tr[N][3],cnt=0,pre[N],ed[N];
void ins(string s){
    int nw=0;
    for(int i=0;i<s.length();i++){
        int c=s[i]-'A';
        if(tr[nw][c]==0)tr[nw][c]=++cnt;
        nw=tr[nw][c];
    }
    ed[nw]++;
}
void build(){
    queue<int>q;
    for(int i=0;i<3;i++)if(tr[0][i])q.push(tr[0][i]);
    while(!q.empty()){
        int x=q.front();q.pop();
        for(int y=0;y<3;y++){
            if(tr[x][y]==0)tr[x][y]=tr[pre[x]][y];
            else{
                pre[tr[x][y]]=tr[pre[x]][y];
                q.push(tr[x][y]);
            }
        }
        ed[x]+=ed[pre[x]];//记得加上沿着 fail 边往上跳能跳到多少个字符串的末尾
    }
}
int dp[K][N];//输入 i 个字符，最后停在 AC 自动机的点 j 时能获得几分
void solve(int kk){
    for(int i=0;i<=kk;i++)dp[i][0]=0;
    for(int i=0;i<kk;i++){
        for(int j=0;j<=cnt;j++){
            for(int k=0;k<3;k++){//接下来往哪走呢 
                dp[i+1][tr[j][k]]=max(dp[i+1][tr[j][k]],dp[i][j]+ed[tr[j][k]]);
            }
        }
    }
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int n,k;cin>>n>>k;
    for(int i=1;i<=n;i++){
        string s;cin>>s;
        ins(s);
    }
    build();
    memset(dp,-0x3f,sizeof(dp));
    solve(k);
    int ans=0;
    for(int i=0;i<=cnt;i++){
//      cout<<dp[k][i]<<" ";
        ans=max(ans,dp[k][i]);
    }
    cout<<ans;
    return 0;
}
```
 
AC 记录：<https://www.luogu.com.cn/record/178447532>。

---

## 作者：hzoi_Shadow (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/SP10502)

# 前置知识

[AC 自动机](https://oi-wiki.org//string/ac-automaton/)

# 解法

多模式串匹配考虑 AC 自动机。

令 $f_{i,j}$ 表示前 $i$ 个字符，当前运行到 AC 自动机的状态 $j$ 时的最大得分。状态转移方程为 $f_{i,k}=\max\limits_{k \in Son(j)} \{ f_{i-1,j}+sum_{k} \}$，其中 $sum_{k}$ 表示 fail 树上以 $k$ 结尾的字符串个数。

最终，有 $\max\limits_{i=0}^{tot} \{ f_{m,i} \}$ 即为所求。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define ull unsigned long long
#define sort stable_sort 
#define endl '\n'
int trie[1000][5],fail[1000],sum[1000],f[2000][1000],tot=0;
char s[1000];
int val(char x)
{
	return x-'A'+1;
}
void insert(char s[],int len)
{
	int x=0,i;
	for(i=1;i<=len;i++)
	{
		if(trie[x][val(s[i])]==0)
		{
			tot++;
			trie[x][val(s[i])]=tot;
		}
		x=trie[x][val(s[i])];
	}
	sum[x]++;
}
void build()
{
	int x,i;
	queue<int>q;
	for(i=1;i<=3;i++)
	{
		if(trie[0][i]!=0)
		{
			fail[trie[0][i]]=0;
			q.push(trie[0][i]);
		}
	}
	while(q.empty()==0)
	{
		x=q.front();
		q.pop();
		for(i=1;i<=3;i++)
		{
			if(trie[x][i]==0)
			{
				trie[x][i]=trie[fail[x]][i];
			}
			else
			{
				fail[trie[x][i]]=trie[fail[x]][i];
				sum[trie[x][i]]+=sum[fail[trie[x][i]]];
				q.push(trie[x][i]);
			}
		}
	}
}
int main()
{
	int n,m,ans=0,i,j,k;
	cin>>n>>m;
	memset(f,-0x3f,sizeof(f));
	for(i=1;i<=n;i++)
	{
		cin>>(s+1);
		insert(s,strlen(s+1));
	}
	build();
	f[0][0]=0;
	for(i=1;i<=m;i++)
	{
		for(j=0;j<=tot;j++)
		{
			if(f[i-1][j]>=0)
			{
				for(k=1;k<=3;k++)
				{
					f[i][trie[j][k]]=max(f[i][trie[j][k]],f[i-1][j]+sum[trie[j][k]]);
				}
			}
		}
	}
	for(i=0;i<=tot;i++)
	{
		ans=max(ans,f[m][i]);
	}
	cout<<ans<<endl;
	return 0;
}	
```

# 后记

多倍经验：[luogu P3041 [USACO12JAN] Video Game G](https://www.luogu.com.cn/problem/P3041)

---

## 作者：PigNotFound (赞：0)

本题是一道 AC 自动机上的 dp。
首先不难想到状态定义 $f_{i,j}$ 表示仅考虑前 $i$ 个位置，第 $i$ 个字符是 $j$ 的分数，但无法转移，所以考虑将 $j$ 这一维转化为表示 AC 自动机上的点。

再定义 $val_i$ 表示以 $i$ 结尾的所有技能种数，则转移方程为 $f_{i,j}=\max(f_{i,j},f_{i-1,father_j}+val_j)$。

现在问题转化为求 $val$。求 $val$ 的话在求 AC 自动机的 $fail$ 指针那部分里来求，转移式为 $val_i=end_i+val_{fail_i}$，其中 $end_i$ 表示以 $i$ 结尾的字符串数。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int Pig = 1e3 + 10;
int f[Pig][Pig];
struct ac_automaton{
    int tr[Pig][4], end_[Pig], fail[Pig], cnt = 0, val[Pig];
    ac_automaton() {
        memset(tr, 0, sizeof(tr));
        memset(end_, 0, sizeof(end_));
        memset(val, 0, sizeof(val));
        memset(fail, 0, sizeof(fail));
    }
    void insert(string n) {
        int p = 0;
        for (auto v : n) {
            if (!tr[p][v - 'A'])
                tr[p][v - 'A'] = ++cnt;
            p = tr[p][v - 'A'];
        }
        end_[p]++;
    }
    void build() {
        queue<int> q;
        for (int i = 0; i < 3; i++) {
            if (tr[0][i])
                q.emplace(tr[0][i]);
        }
        while (!q.empty()) {
            int p = q.front();
            q.pop();
            for (int i = 0; i < 3; i++) {
                if (tr[p][i]) {
                    fail[tr[p][i]] = tr[fail[p]][i];
                    q.push(tr[p][i]);
                } else {
                    tr[p][i] = tr[fail[p]][i];
                }
            }
            val[p] = end_[p] + val[fail[p]];
        }
    }
};
ac_automaton tr;
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        string cur;
        cin >> cur;
        tr.insert(cur);
    }
    tr.build();
    memset(f, -0x3f3f3f3f, sizeof(f));
    for (int i = 0; i <= k; i++)
        f[i][0] = 0;
    int ans = 0;
    for (int i = 1; i <= k; i++) {
        for (int j = 0; j <= tr.cnt; j++) {
            for (int l = 0; l < 3; l++) {
                f[i][tr.tr[j][l]] = max(f[i][tr.tr[j][l]], f[i - 1][j] + tr.val[tr.tr[j][l]]);
            }
        }
    }
    for (int i = 0; i <= tr.cnt; i++)
        ans = max(ans, f[k][i]);
    cout << ans;
    return 0;
}

```

---

## 作者：liugh_ (赞：0)

[SP10502 VIDEO - Video game combos](https://www.luogu.com.cn/problem/SP10502) 

一道类似的题：[P4052 [JSOI2007] 文本生成器](https://www.luogu.com.cn/problem/P4052)

---

套路地想到 ACAM + dp。设 $f(u,i)$ 为当前在 ACAM 上的点 $u$，当前串长为 $i$ 时的最大价值。

考虑转移。注意到 ACAM 中 fail 的作用实质上是跳到包含最长公共后缀的点，且跳到的点深度一定不增。由此想到设 $sum(u)$ 为点 $u$ 在跳 fail 的过程中会遇到的模式串尾的个数，在求 fail 的时候顺带求出，即
$$
sum(ch(u,s))\gets sum(ch(u,s))+sum(fail(ch(u,s)))
$$
故转移方程为
$$
f(ch(u,s),i+1)\gets \max(f(ch(u,s),i+1),f(u,i)+sum(ch(u,s)))
$$
显然答案为 $ans=\max_{u\in V} f(u,k)$。

注意初始化，为保证整个模式串被包含，只能以根为起点，ACAM 中其余结点开始的状态是不合法的，即将除 $f(0,0)$ 外的所有 $f$ 都初始化为 $-\infty$。

```cpp
struct Ac {
	struct Node {int ch[3], sum, fail; void clear() {fill(ch, end(ch), 0); sum = fail = 0;}} node[Maxn * Maxn];
	int tot; Ac() {tot = 0;}
	#define ch(u, c) node[u].ch[c - 65]
	#define sum(u) node[u].sum
	#define fail(u) node[u].fail
	void insert(const char* S, int u = 0) {
		for (int i = 0; S[i]; u = ch(u, S[i]), ++i)
			if (!ch(u, S[i])) ch(u, S[i]) = ++tot, node[tot].clear();
		++sum(u);
	}
	void work() {
		static queue<int> q; for (int i = 'A'; i <= 'C'; ++i) if (ch(0, i)) q.push(ch(0, i));
		while (q.size()) {
			int u = q.front();
			q.pop();
			for (int i = 'A'; i <= 'C'; ++i) {
				if (!ch(u, i)) {ch(u, i) = ch(fail(u), i); continue;}
				fail(ch(u, i)) = ch(fail(u), i);
				q.push(ch(u, i));
				sum(ch(u, i)) += sum(fail(ch(u, i)));
			}
		}
	}
	int dp() {
		fill(*begin(f), *end(f), -INF);
		f[0][0] = 0;
		// 只能以0为起点，从ACAM中其余结点开始的状态是不合法的
		for (int i = 0; i < K; ++i)
			for (int u = 0; u <= tot; ++u)
				for (int s = 'A'; s <= 'C'; ++s)
					f[i + 1][ch(u, s)] = max(f[i + 1][ch(u, s)], f[i][u] + sum(ch(u, s)));
		int res = 0;
		for (int u = 0; u <= tot; ++u) res = max(res, f[K][u]);
		return res;
	}
} ac;
```

---

## 作者：w9095 (赞：0)

[SP10502 VIDEO - Video game combos](https://www.luogu.com.cn/problem/SP10502)

AC 自动机上的动态规划。

由题目中这句话，不难想到 AC 自动机：

>$s_i$ 在 $t$ 中出现一次指的是 $s_i$ 是 $t$ 从某个位置起的连续子串。如果 $s_i$ 从 $t$ 的多个位置起都是连续子串，那么算作 $s_i$ 出现了多次。

考虑到每个位置有多种转移情况，且满足最优子结构性质，使用动态规划。观察后发现确定一个位置需要两个参数：目前是主串的的 $i$ 个字符，目前在 AC 自动机中的位置 $j$。易得转移方程：

$$dp[i+1][trie[j][k]]=\max(dp[i+1][trie[j][k]],dp[i][j]+h[trie[j][k]])$$

这里 $k$ 是枚举 AC 自动机中的出边，$h[i]$ 表示在 AC 自动机中的位置 $i$ 匹配可以得到的分数。实质上，这是一个根据现在的状态推出后面状态的方程，所以 $\max$ 里会有 $dp[i+1][trie[j][k]]$ 这一项，而后面一项则是目前枚举的状态转移之后的得分。

这里把 $h[i]$ 预处理出来了，实际上不预处理应该也是可以的。

注意状态需要初始化为负无穷，很明显是不能从不可能的状态转移的。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,k,ans,trie[310][3],ap[310],fail[310],que[310],f[1010][310],h[310],cnt=0;
char str[310];
void insert(char str[])
{
	int l=strlen(str),root=0;
	for(int i=0;i<l;i++)
	    {
	    	int id=str[i]-'A';
	    	if(!trie[root][id])trie[root][id]=++cnt;
	    	root=trie[root][id];
	    }
	ap[root]++;
}

void build_ac()
{
	int head=0,tail=0;
	fail[0]=0;
	for(int i=0;i<3;i++)
	    if(trie[0][i])que[tail++]=trie[0][i];
	while(head<tail)
	   {
	   	int now=que[head];
	   	for(int i=0;i<3;i++)
	   	    if(trie[now][i])fail[trie[now][i]]=trie[fail[now]][i],que[tail++]=trie[now][i];
	   	    else trie[now][i]=trie[fail[now]][i];
		head++;
	   }
}

int main()
{
	scanf("%d%d",&n,&k);
	for(int i=0;i<n;i++)
	    {
	    	scanf("%s",str);
	    	insert(str);
		}
	build_ac();
	for(int i=0;i<=cnt;i++)
	    for(int j=i;j!=0;j=fail[j])h[i]+=ap[j];
	for(int i=0;i<=k;i++)
	    for(int j=0;j<=cnt;j++)
	        f[i][j]=-99999999;
	f[0][0]=0;
	for(int i=0;i<k;i++)
	    for(int j=0;j<=cnt;j++)
	        for(int k=0;k<3;k++)
	            f[i+1][trie[j][k]]=max(f[i+1][trie[j][k]],f[i][j]+h[trie[j][k]]);
	for(int i=0;i<=cnt;i++)
	    ans=max(ans,f[k][i]);
	printf("%d",ans);
	return 0;
}
```

---

## 作者：凤年 (赞：0)

[题目链接](https://www.luogu.com.cn/problem/SP10502)

经典的 AC自动机 上的 DP 题，一般这种 DP 都比较套路，都是设 $f_{ij}$ 表示匹配了长度为 $i$ 的串，且当前匹配到了 $j$ 节点。

建自动机的时候正常建即可，宽搜处理失配边的时候最后加上一句 `cnt[now] += cnt[fail[now]];` 即可，因为如果最后答案出现 $now$ 代表的串那么也同样表示出现了 $fail_now$ 代表的串，所以要让 $fail_now$ 的分数加到 $now$ 上。

其他细节都在代码里。

```cpp
#include <bits/stdc++.h>
#define N 310
#define K 1010
using namespace std;

int n, k, ans;
string s;

int tot = 0;
int fail[N], trie[N][3], cnt[N];
int f[K][N];//f[i][j]表示已匹配长度为i，当前在节点j上

void add(string s) {
	int p = 0;
	for(int i = 0, len = s.size(); i < len; ++i) {
		int num = s[i] - 'A';
		if(!trie[p][num]) trie[p][num] = ++tot;
		p = trie[p][num];
	}
	++cnt[p];
}
void getFail() {
	queue<int> q;
	fail[0] = 0;
	for(int i = 0; i < 3; ++i) {
		if(trie[0][i]) {
			fail[trie[0][i]] = 0;
			q.push(trie[0][i]);
		}
	}
	while(!q.empty()) {
		int now = q.front();
		q.pop();
		for(int i = 0; i < 3; ++i) {
			if(trie[now][i]) {
				fail[trie[now][i]] = trie[fail[now]][i];
				q.push(trie[now][i]);
			} else {
				trie[now][i] = trie[fail[now]][i];
			}
		}
        cnt[now] += cnt[fail[now]];//分数顺着fail边叠加
	}
}
int main() {
	cin >> n >> k;
	for(int i = 1; i <= n; ++i) {
		cin >> s;
		add(s);
	}
	getFail();
    memset(f, -0x3f, sizeof(f));
    for(int i = 0; i <= k; ++i) f[i][0] = 0;
    for(int i = 1;i <= k; ++i)//枚举长度
        for(int j = 0;j <= tot; ++j) //转移节点
            for(int l = 0;l < 3; ++l)
                f[i][trie[j][l]] = max(f[i - 1][j] + cnt[trie[j][l]], f[i][trie[j][l]]);

    for(int i = 0;i <= tot; ++i) ans = max(ans, f[k][i]);
    printf("%d", ans);
	return 0;
}
```


---

## 作者：wcyQwQ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/SP10502)

[可能更好的阅读体验](https://chenyu-w.github.io/2022/07/07/SP10502%20VIDEO/)

## 前言

ACAM + DP 入门题目。

### 前置芝士

ACAM


## 分析

看到题目中这种多模式串匹配问题，第一反应是建出 ACAM，然后我们维护每个节点的贡献 $cnt[p]$，在建立 ACAM 的过程中可以顺便加上他的子串的贡献。

然后我们来考虑如何 DP，设 $f[i][j]$ 表示当前串长为 $i$ 走到了节点 $j$ 上的最大长度，那么我们显然可以由 $f[i][j]$ 来转移到它的每个儿子，具体方程为:
$$
f[i][t[j][k]] = \max_{0\le k < 3}\{f[i - 1][j] + cnt[t[j][k]]\}
$$
最后的答案取个最大值就行了。

## 代码

```c++
#include <bits/stdc++.h>

using namespace std;
const int N = 30, M = 20, K = 1e3 + 10;
int t[N * M][3], fail[N * M], cnt[N * M], idx;
char s[M];
int f[K][N * M];

inline void insert()
{
    int p = 0;
    for (int i = 1; s[i]; i++)
    {
        int c = s[i] - 'A';
        if (!t[p][c]) t[p][c] = ++idx;
        p = t[p][c];
    }
    cnt[p]++;
}

inline void build()
{
    queue<int> q;
    for (int i = 0; i < 3; i++)
        if (t[0][i])
            q.push(t[0][i]);
    while (q.size())
    {
        int p = q.front();
        q.pop();
        for (int i = 0; i < 3; i++)
        {
            int c = t[p][i];
            if (!c) t[p][i] = t[fail[p]][i];
            else fail[c] = t[fail[p]][i], q.push(c);
        }
        cnt[p] += cnt[fail[p]];
    }
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%s", s + 1);
        insert();
    }
    build();
    memset(f, 0xcf, sizeof f);
    for (int i = 0; i <= m; i++) f[i][0] = 0;
    for (int i = 1; i <= m; i++)
        for (int j = 0; j <= idx; j++)
            for (int k = 0; k < 3; k++)
            {
                int c = t[j][k];
                f[i][c] = max(f[i][c], f[i - 1][j] + cnt[c]);
            }
    int res = 0;
    for (int i = 1; i <= idx; i++) res = max(res, f[m][i]);
    printf("%d\n", res);
    return 0;
}
```



---

## 作者：SunsetSamsara (赞：0)

## 前置知识
AC 自动机，dp
## 分析
首先，多个字符串，子串，马上就能联想到 AC 自动机。

于是，题目相当于求 AC 自动机上的长度为 $k$ 的路径，使得走完的子串个数最多。

接下来是 AC 自动机 + dp 的老套路了：

+ 定义状态数组 $dp_{i,j}$ 为当前走了 $j$ 个到节点 $i$ 的走完的串个数的最大值，

+ 转移方程显然为：$dp_{sons[i][k],j} = max \big \{dp_{sons[i][k],j}, dp_{i, j - 1} + \small\text{sons[i][k]\space 经过的串个数}\big \}$

+ 答案是 $dp_{i,m}$ 的最大值

最后只需要求 $\small\text{sons[i][k]\space 经过的串个数}$ 了。容易发现可以从两个方向转移：自己和自己的 $fail$ 指针。在建 AC 自动机的途中转移即可。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int tot;
struct node {
	int sons[3];
	int vis;
	int fail;
} T[10001];
int dp[401][10001];
void insert(const char *str) {
	int cur = 0;
	for (int i = 0; str[i]; ++ i) {
		if (!T[cur].sons[str[i] - 'A'])
			T[cur].sons[str[i] - 'A'] = ++ tot;
		cur = T[cur].sons[str[i] - 'A'];
	}
	++ T[cur].vis;
}
void build() {
	queue<int> q;
	for (int i = 0; i < 3; ++ i)
		if (T[0].sons[i])
			q.push(T[0].sons[i]);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (int i = 0; i < 3; ++ i) {
			if (T[u].sons[i]) {
				T[T[u].sons[i]].fail = T[T[u].fail].sons[i];
				q.push(T[u].sons[i]);
			} else T[u].sons[i] = T[T[u].fail].sons[i];
		}
		T[u].vis += T[T[u].fail].vis; // 两个方向转移 
	}
}
int n, m;
char str[101];
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++ i) {
		scanf("%s", str);
		insert(str);
	}
	build();
	for (int i = 0; i <= m; ++ i)
		for (int j = 1; j <= tot; ++ j)
			dp[j][i] = -0x3f3f3f3f; // 写反，写反，老是写反！！！ 
	for (int i = 1, j, k; i <= m; ++ i)
		for (j = 0; j <= tot; ++ j)
			for (k = 0; k < 3; ++ k)
				dp[T[j].sons[k]][i] = max(dp[T[j].sons[k]][i], dp[j][i - 1] + T[T[j].sons[k]].vis); // dp 的转移 
	int ans = 0;
	for (int i = 0; i <= tot; ++ i)
		ans = max(ans, dp[i][m]);
	printf("%d\n", ans);
}
```

---

