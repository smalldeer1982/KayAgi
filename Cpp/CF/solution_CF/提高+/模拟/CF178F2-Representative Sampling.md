# Representative Sampling

## 题目描述

The Smart Beaver from ABBYY has a long history of cooperating with the "Institute of Cytology and Genetics". Recently, the Institute staff challenged the Beaver with a new problem. The problem is as follows.

There is a collection of $ n $ proteins (not necessarily distinct). Each protein is a string consisting of lowercase Latin letters. The problem that the scientists offered to the Beaver is to select a subcollection of size $ k $ from the initial collection of proteins so that the representativity of the selected subset of proteins is maximum possible.

The Smart Beaver from ABBYY did some research and came to the conclusion that the representativity of a collection of proteins can be evaluated by a single number, which is simply calculated. Let's suppose we have a collection $ {a_{1},...,a_{k}} $ consisting of $ k $ strings describing proteins. The representativity of this collection is the following value:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF178F2/c7b3873e6751582bb5e2ad2c1deb58138ab9c543.png)where $ f(x,y) $ is the length of the longest common prefix of strings $ x $ and $ y $ ; for example, $ f( $ "abc", "abd" $ )=2 $ , and $ f( $ "ab", "bcd" $ )=0 $ .

Thus, the representativity of collection of proteins $ { $ "abc", "abd", "abe" $ } $ equals $ 6 $ , and the representativity of collection $ { $ "aaa", "ba", "ba" $ } $ equals $ 2 $ .

Having discovered that, the Smart Beaver from ABBYY asked the Cup contestants to write a program that selects, from the given collection of proteins, a subcollection of size $ k $ which has the largest possible value of representativity. Help him to solve this problem!

## 样例 #1

### 输入

```
3 2
aba
bzd
abq
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4 3
eee
rrr
ttt
qqq
```

### 输出

```
0
```

## 样例 #3

### 输入

```
4 3
aaa
abba
abbc
abbd
```

### 输出

```
9
```

# 题解

## 作者：lfxxx (赞：2)

简单题，这里给一种不依赖字典序特性的解法，考虑设计状态 $dp_{u,i}$ 表示考虑以点 $u$ 为根的子树，这个子树中选了 $i$ 个字符串的贡献。

显然转移是一个背包形式的 $\max +$ 卷积，由于 dp 第二维最大是子树单词节点数量，所以用上界优化后是 $O(n^2)$ 的，转移方程是简单的：$dp_{u,i} \gets \sum_{j} dp_{u,j} + dp_{v,i-j} + i \times (i-j) \times dep_u$。

不过你发现一个很不好的东西，你的空间是 $O(n^2 |S_i|)$ 的，直接爆了。

考虑重剖优化空间，具体来说只给需要正在处理的节点分配 dp 数组编号，在执行对点 $u$ 的 dp 时，进行以下步骤：

1. 找出重儿子 $hson$。

2. 对重儿子进行 dp，并在其结束后将数组合并到 $u$ 上，继承重儿子的 dp 数组编号。

3. 对轻儿子进行 dp。合并后回收轻儿子 dp 数组编号。因为在这之后不会再用到。

4. 结束时如果点 $u$ 是一个单词节点则分配一个编号。

不难发现这样做在进行对点 $u$ 的 dp 时存在的 dp 数组是被点 $u$ 到根的路径上所有切换轻重链的节点的父亲（在重链上）所占用，根据重剖的结论，这样的点至多有 $\log n$ 个，因此这么做空间就被优化到了 $O(n \log n + n \log |S_i|)$ 而时间还是 $O(n |S_i| + n^2)$ 的。

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long inf = 1e18+114;
const int maxn = 1e6+114;
const int maxlg = 25;
int cnt[maxn],sz[maxn],dep[maxn];
long long dp[maxlg][2014];
int pos[maxn],node[maxn];
int n,rt,tot,K;
int C;
int son[maxn][26];
void ins(string s){
    int u=rt;
    for(char c:s){
        sz[u]++;
        if(son[u][c-'a']==0) son[u][c-'a']=++tot;
        u=son[u][c-'a'];
    }
    cnt[u]++;
    sz[u]++;
    return ;
}
void dfs(int u){
    int hson=0;
    for(int i=0;i<26;i++) if(sz[son[u][i]]>sz[hson]) hson=son[u][i];
    if(hson!=0){
        dep[hson]=dep[u]+1;
        dfs(hson);
        pos[u]=pos[hson];
        node[pos[u]]=u;
    }
    for(int i=0;i<26;i++){
        if(son[u][i]==hson) continue;
        if(son[u][i]==0) continue;
        dep[son[u][i]]=dep[u]+1;
        int lst=C;
        dfs(son[u][i]);
        for(int j=sz[u]-sz[son[u][i]];j>=0;j--)
            for(int k=sz[son[u][i]];k>=0;k--) dp[pos[u]][j+k]=max(dp[pos[u]][j+k],dp[pos[u]][j]+dp[pos[son[u][i]]][k]+1ll*j*k*dep[u]);
        //轻儿子使用完就全部回收
        for(int j=lst+1;j<=C;j++){
            for(int k=1;k<=sz[node[j]];k++) dp[j][k]=-inf;
            dp[j][0]=0;
        }
        C=lst;
    }
    if(pos[u]==0&&cnt[u]>0) pos[u]=++C,node[C]=u;
    for(int i=sz[u]-cnt[u];i>=0;i--){
        for(int j=cnt[u];j>=0;j--) dp[pos[u]][i+j]=max(dp[pos[u]][i+j],dp[pos[u]][i]+1ll*j*(j-1)/2*dep[u]+1ll*i*j*dep[u]);
    }
}
int main(){
    cin>>n>>K;
    rt=++tot;
    for(int i=1;i<=n;i++){
        string s;
        cin>>s;
        ins(s);
    }
    dfs(rt);
    cout<<dp[pos[rt]][K]<<'\n';
    return 0;
}
```

---

## 作者：xhabc66 (赞：2)

# 思路

对于**前缀问题**，就可以考虑建字典树。

题目中说的答案和 $f$ 相关，所以可以再求出每个节点的 $f$ 值。

具体来说，每个节点的 $f$ 值就是以当前节点开始的字符串的**所有** $f$ 之和。（如样例中的 `ab` 节点的 $f$ 值就是 $f($ `ba`,`bq` $)$）。

这样的话，$f_u=\sum_{v是u的子节点}(f_v)+\frac{n(n+1)}{2}$，其中 $n$ 是经过节点 $u$ 的字符串个数。

于是，即可把“经过节点 $u$ 的字符串个数”当作“重量”，把 $f_u$ 当作“权值”，进行背包。

别忘了特判所有字符串均相等的情况。

# AC code
```
#include<bits/stdc++.h>
using namespace std;
#define oo 0x3f3f3f3f
 
struct Node
{
    int child[26];
    int size;
    bool last;
    int f;
    char v;
    int dp[2023];
}zds[10000];
 
int cnt=-1;
 
int newNode(char v)
{
    cnt++;
    for(int i=0;i<26;i++)zds[cnt].child[i]=-1;
    zds[cnt].size=0;
    zds[cnt].v=v;
    return cnt;
}
 
void add(int n,string s)
{
    //cout<<"add:"<<n<<','<<s<<'\n';
    zds[n].size++;          
    if(zds[n].child[s[0]-'a']==-1)zds[n].child[s[0]-'a']=newNode(s[0]);
    if(s.size()==1)zds[zds[n].child[s[0]-'a']].last=1,zds[zds[n].child[s[0]-'a']].size++;
    else add(zds[n].child[s[0]-'a'],s.substr(1,s.size()-1));
}
 
void print(string a,int n)
{
    if(n==-1)return;
    a=a+zds[n].v;
    cout<<n<<':'<<a<<';';
    printf("size:%d;f:%d",zds[n].size,zds[n].f);
    for(int i=0;i<5;i++)printf("dp[%d]:%d;",i,zds[n].dp[i]);
    cout<<'\n';
    for(int i=0;i<26;i++)print(a,zds[n].child[i]);
}
 
void jisuan(int n)
{
    if(n==-1)return;
    for(int i=0;i<26;i++)jisuan(zds[n].child[i]);
    zds[n].f=0;
    for(int i=0;i<26;i++)
    {
        int child=zds[n].child[i];
        if(child==-1)continue;
        zds[n].f+=zds[child].f;
    }
    if(n)zds[n].f+=zds[n].size*(zds[n].size-1)/2;
}
 
void dp(int n)
{
    if(n==-1)return;
    for(int i=0;i<26;i++)dp(zds[n].child[i]);
    for(int i=0;i<2023;i++)zds[n].dp[i]=-oo;
    zds[n].dp[0]=0;
    for(int i=0;i<26;i++)
    {
        int child=zds[n].child[i];
        if(child==-1)continue;
        for(int j=zds[n].size;j>0;j--)
            for(int i=j;i>0;i--)
                if(zds[n].dp[j]<zds[n].dp[j-i]+zds[child].dp[i])
                {
                    //printf("relax:%d %d %d %d %d %d %d\n",n,child,i,j,zds[n].dp[j],zds[n].dp[j-i],zds[child].dp[i]);
                    zds[n].dp[j]=max(zds[n].dp[j],zds[n].dp[j-i]+zds[child].dp[i]);
                }
    }
    for(int i=0;i<2023;i++)zds[n].dp[i]+=i*(i-1)/2;
    zds[n].dp[zds[n].size]=max(zds[n].dp[zds[n].size],zds[n].f);
}
 
int main()
{
    int n,k;
    cin>>n>>k;
    newNode(32);
    string a,b;
    bool flag=1;
    cin>>a,add(0,a);
    for(int i=1;i<n;i++)
	{
		b=a,cin>>a,add(0,a);
		if(b!=a)flag=0;
	}	
	if(flag)return cout<<k*(k-1)/2*a.size(),0;
    jisuan(0);
    dp(0);
    //print("",0);
    cout<<zds[0].dp[k]-k*(k-1)/2;
    return 0;
}
```

---

## 作者：wosile (赞：0)

题意略。Duel 到这道题写了 45 分钟被暴打了。

让求 LCP，就建一棵 Trie 好了。

既然要选 $k$ 个字符串求最大值，很明显我们应该在 Trie 上跑树上背包。对于 Trie 的一条边而言，如果我们选择的字符串中有 $x$ 个在 Trie 上经过了这条边，那么这条边就会产生 $\frac{x(x-1)}{2}$ 的贡献。

直接背包的时间复杂度似乎是 $O(k\sum|a_i|)$ 的，但借用虚树的思想，只有一个孩子的节点我们可以很简单的处理它的答案。从而实际需要计算的节点只有 $O(n)$ 个，时间复杂度是 $O(kn)$。代码里使用了 `tag[i]` 记录虚点 $i$ 到当前位置的深度，在需要用到 $i$ 点的 dp 值的时候用 `tag[i]` 更新 dp 值即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
string s[2005];
int n,K;
int tr[1000005][30],buc[1000005],tot=0;
int f[4005][2005],sz[4005],tag[4005],id[1000005];
void upd(int v){
	for(int i=0;i<=sz[v];i++)f[v][i]+=tag[v]*(i-1)*i/2;
	tag[v]=0;
}
int main(){
	cin>>n>>K;
	for(int i=0;i<n;i++)cin>>s[i];
	for(int i=0;i<n;i++){
		int cur=0;
		for(int j=0;j<(int)s[i].size();j++){
			if(tr[cur][s[i][j]-'a']==0)tr[cur][s[i][j]-'a']=++tot;
			cur=tr[cur][s[i][j]-'a'];
		}
		buc[cur]++;
	}
	int qwq=0;
	for(int i=tot;i>=0;i--){
		int cnt=0,son=0;
		for(int j=0;j<26;j++)if(tr[i][j]){
			++cnt,++tag[id[tr[i][j]]];
			son=tr[i][j];
		}
		if(cnt==0)id[i]=++qwq;
		else if(cnt==1)id[i]=id[son];
		else{
			id[i]=++qwq;
			for(int j=0;j<26;j++)if(tr[i][j]){
				int v=id[tr[i][j]];
				upd(v);
				for(int k=sz[qwq];k>=0;k--)for(int l=0;l<=sz[v];l++)f[qwq][k+l]=max(f[qwq][k+l],f[qwq][k]+f[v][l]);
				sz[qwq]+=sz[v];
			}
		}
		if(buc[i]>0){
			upd(id[i]);
			for(int j=sz[id[i]];j<sz[id[i]]+buc[i];j++)f[id[i]][j+1]=max(f[id[i]][j+1],f[id[i]][j]);
			sz[id[i]]+=buc[i];
		}
	}
	for(int i=0;i<=n;i++)f[qwq][i]+=tag[qwq]*i*(i-1)/2;
	printf("%d",f[qwq][K]);
	return 0;
}
```

---

