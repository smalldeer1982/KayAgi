# [ABC399E] Replace

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc399/tasks/abc399_e

给定一个正整数 $N$ 以及两个长度为 $N$ 的小写英文字母字符串 $S$ 和 $T$。  
请判断是否可以通过重复以下操作（允许 0 次操作）将 $S$ 变为 $T$。若可能，还需输出所需的最小操作次数。

**操作**：  
选择两个小写英文字母 $x$ 和 $y$，将 $S$ 中 **所有** 出现的 $x$ 替换为 $y$。

## 说明/提示

### 约束条件

- $1 \leq N \leq 2 \times 10^5$
- $N$ 为整数
- $S$ 和 $T$ 均为长度为 $N$ 的小写英文字母字符串

### 样例解释 1

通过以下 4 次操作可将 $S$ 变为 $T$：
1. 选择 $x=$ `b`, $y=$ `c`，操作后 $S=$ `afcfda`
2. 选择 $x=$ `a`, $y=$ `b`，操作后 $S=$ `bfcfdb`
3. 选择 $x=$ `f`, $y=$ `k`，操作后 $S=$ `bkckdb`
4. 选择 $x=$ `d`, $y=$ `b`，操作后 $S=$ `bkckbb`（与 $T$ 一致）

由于无法在 3 次或更少操作内完成，最小操作次数为 4。

### 样例解释 2

$S$ 与 $T$ 初始时已一致，无需任何操作。

### 样例解释 3

无论如何操作，都无法将 $S$ 变为 $T$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
6
afbfda
bkckbb```

### 输出

```
4```

## 样例 #2

### 输入

```
4
abac
abac```

### 输出

```
0```

## 样例 #3

### 输入

```
4
abac
abrc```

### 输出

```
-1```

## 样例 #4

### 输入

```
4
abac
bcba```

### 输出

```
4```

# 题解

## 作者：star_field (赞：8)

[原题传送门](https://atcoder.jp/contests/abc399/tasks/abc399_e)

### 题意简述

有两个字符串 $S,T$ (由英文小写字母组成)，将一次操作定义为将 $S$ 中的所有字母 $a$ 转换为字母 $b$（ $a,b$ 可代指任何字母，下同），问 $S$ 需要经过多少次操作才能转化为 $T$。

###  解题思路

既然是将所有字母 $a$ 转化为字母 $b$，考虑构造有向图，由 $a$ 向 $b$ 建边。

### 样例解释

这里解释一下样例 1、3 和 4。

对于样例 1，我们可以构造一个这样的图：

![](https://cdn.luogu.com.cn/upload/image_hosting/nqk25yvq.png)

显然，需要 $b\Rightarrow c,a\Rightarrow b,d\Rightarrow b,f\Rightarrow k$ 四次操作。

对于样例 3：

![](https://cdn.luogu.com.cn/upload/image_hosting/adbm18gw.png)

（这里吐槽一下 csacademy 的画图工具竟然不能画自环，只能手动补全了）

我们注意到 $a$（这里就是指 $a$）既要转换成 $a$（就是不转换），又要转换成 $r$ ，显然无解。

对于样例 4：

![](https://cdn.luogu.com.cn/upload/image_hosting/c1nisjse.png)

这是一个环，所以我们需要一个中转点，可以用 $d$：

![](https://cdn.luogu.com.cn/upload/image_hosting/p7yo3f9a.png)

这样相当于把环拆开了(原来的 $c$ 转化成 $d$)，所以共4步：

1. $c\Rightarrow d$，字符串变为`abad`。
2. $b\Rightarrow c$，字符串变为`acad`。
3. $a\Rightarrow b$，字符串变为`bcbd`。
4. $d\Rightarrow a$，字符串变为`bcba`。

但是这里要注意一种特殊情况：因为题目要求只能用小写字母，所以在 $26$ 个字母全在环里的情况下，我们不能找出其他中转点，此种情况无解。

### code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 35;
int n, to[N], dg[N], ans;
string s, t;
bool vis[N],f;
void dfs(int p) {
	if (vis[p]) return;
	vis[p] = true;
	if (to[p] != -1)
		dfs(to[p]);
}
int main() {
	cin >> n >> s >> t;
	memset(to, -1, sizeof(to));
	for (int i = 0; i < n; i++) {
		int x = s[i] - 'a';
		int y = t[i] - 'a';
		if (to[x] != -1 && to[x] != y){  //如果出现了一个字母指向了两个字母，直接输出-1
			cout << -1;
			return 0;
		}
		to[x] = y;
	}
	for (int i = 0; i < 26; i++){ // 计算基础边数
		if (to[i] != -1){ //如果该字母出现了并且指向某个字母
			ans += (to[i] != i); //如果指向其他字母
			dg[to[i]]++;
		}
	}
	for (int i = 0; i < 26; i++) // 查找空闲节点
		if (to[i] == -1 || dg[i] == 0)
			f = true;
	for (int i = 0; i < 26; i++) // 处理链和自环
		if (dg[i] == 0 || to[i] == i)
			dfs(i);
	for (int i = 0; i < 26; i++){ // 处理剩余的环
		if (!vis[i]) {
			ans++;
			dfs(i);
			if (!f) {
				cout << -1;
				return 0;
			}
		}
	}
	cout << ans;
	return 0; //蒟蒻的第一篇题解，求过qwq
}

```

---

## 作者：Air2011 (赞：7)

### 背景

这把报了 UnRated 从 E 开始看，于是非常惨烈的只拿下了 E。

![](https://cdn.luogu.com.cn/upload/image_hosting/3y4fishd.png)

这个 2054 难度的题居然只有绿。

----------

## E - Replace

### 题意

给你两个字符串 $s,t$，你每次可以把 $s$ 中的一种字符换成另一种，求把 $s$ 变成 $t$ 的最小操作数，可能无解。

### 思路

我们先考虑无解怎么判：可以得到无解的一个充分不必要条件是 $s$ 串中存在一个字符，他需要变成多种字符，这种情况显然无解。

于是我们记录一个 $com$ 数组，$com_i$ 表示字符 $i$ 需要变成什么字符，**如果不在 $s$ 串中出现** 计为 $com_i=0$，否则即使该字符要变成其本身，也得记录 $com_i=i$。

之后我们考虑建图，我们从 $i \to com_i$ 连一条有向边，如果 $com_i=0$ 则不连，这样构成的图一定是个由树和内向基环树祖成的图。

我们先考虑 $ans$ 一定大于等于什么，很显然是需要改变的字符数量。

之后我们考虑对于中间的环，而非自环而言，有两类情况：

* 只由一个独立的环构成，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/1rk3txex.png)

我们把这种环叫做 第一类环，这种情况我们需要找一个空节点（不在**当前的** $s$ 串中出现的字符）来辅助他（样例 $4$），我们可以先将环上任意一个节点变为该辅助节点，之后按顺序变，之后在将辅助节点变回来，代价为环长 $+1$，下面是~~口胡的~~样例 $4$ 解释：

```
abac
xbxc
xbxa
xcxa
bcba
```

那么问题来了，如果我们找不到辅助节点，那就无解，如连成一个长度为 $26$ 的环，这也无解。

* 这个环外面有与其直接相连的

![](https://cdn.luogu.com.cn/upload/image_hosting/qbpo4zm4.png)

那我们可以把要变成 $a$ 的都集中到不在环上的，这样我们就多出来一个可以用来辅助别的环的点，这样我们所需要的代价是联通块长。

-----

那么现在问题来了：如何通过操作造出来一个可以辅助第一类环的点，那么像第二类的环，就可以造出来一个这样的点，我们把这样的点叫做空闲点。

我们注意到如果本身就一个在 $s$ 串中未出现的字符 $i$，即 $com_i=0$，这张图本身就有空闲点。而如果这单纯只是一个自环，那么这个自环造不出空闲点，反之，我们提前把要变成形成自环的那个字符的字符，先变成其要变的字符，这样我们就多出来一个空闲点，而代价不增加。

### 总结

我们需要做如下事情：

* 建图，并判断第一类无解。
* 找环。
* 判断是否需要空闲点，即找有无第一类环。
* 按上述过程造空闲点，不需要则无所谓。
* 如果需要空闲点，但造不出来，则无解。
* 反之则有解，对于每个一类环，额外算一个贡献。
* 答案为需要改变的符号加上上一步算的额外贡献。

最终代码：[Submission-64367352](https://atcoder.jp/contests/abc399/submissions/64367352)

---

## 作者：Dream_poetry (赞：5)

### 思路：

考虑感性建图。

让 $s_i$ 指向 $t_i$，在 $s_i$不等于 $t_i$ 情况下，由 $s_i$ 向 $t_i$ 连边，然后考虑：

1. 如果 $s_i$ 同时指向了多个结果，显然输出 -1 结束。

2. 如果存在一个环，例如 $a$ 指向 $b$，$b$ 指向 $c$，$c$ 又指向 $a$，则显然我们需要再找到一个没有被用过的字符，把他这个环先破掉，然后再把它改回去，显然这会对答案的贡献产生 $1$ 的影响。

对于情况二，我们考虑若此时 $26$ 个字符全都被用过了且 $s\ne t$，则必然无法成功。

然后在有解的情况下，我们考虑对于每一条边，都会产生 $1$ 的贡献。

参上，每一个环，都会额外产生 $1$ 的贡献。

直接 dfs 找到非环点，在去跑环有多少个就行了。

另：原题：**P9013 [USACO23JAN] Find and Replace S**。

### 代码：


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
char mp[128];
bool f[128];
bool v[128];
int n;
string s,t;
int rt;
int ans;

vector<int>in[128];

inline void dfs(int x){
	if(x==0){
		return;
	}
	if(v[x]){
		if(x==rt){
			ans++;
		}
		return;
	}
	v[x]=1;
	dfs(mp[x]);
}


signed main(){
	cin>>n;
	cin>>s>>t;
	s=' '+s;
	t=' '+t;
	for(int i=1;i<=n;i++){
		if(mp[s[i]] && mp[s[i]]!=t[i]){
			cout<<-1;
			return 0;
		}
		mp[s[i]]=t[i];
		f[t[i]]=1;
	}
	int cnt=0;
	for(int i='a';i<='z';i++){
		cnt+=f[i];
	}
	if(cnt==26 && s!=t){
		cout<<-1;
		return 0;
	}
	for(int i='a';i<='z';i++){
		if(mp[i]==i){
			mp[i]=0;
		}
		ans+=(bool)(mp[i]);
		in[mp[i]].push_back(i);
	}
	
	for(int i='a';i<='z';i++){
		if(in[i].size()>=2){
			if(!v[i]){
				dfs(i);
			}
		}
	}
	
	for(int i='a';i<='z';i++){
		if(!v[i]){
			rt=i;
			dfs(i);
		}
	}
	cout<<ans;
	return 0;
}

```

---

## 作者：2023lpx (赞：3)

# AT_abc399_e [ABC399E] Replace 题解

## 思路

和 [P9013](https://www.luogu.com.cn/problem/P9013) 不能说一模一样，只能说有点类似。

将每个 $S_i$ 向 $T_i$ 连一条边，显然一个点只能有最多一个出度。

此时形成的一个图。

定义 $m$ 为连的边数。

显然，基础的贡献为 $m$。

考虑什么时候会有额外的贡献。

- 对于一颗树，从下到上依次更改即可，不产生额外贡献。
  
- 对于一个环，需要有额外一个点将其破环成链，额外贡献为 $1$。
  
- 对于一个基环树，可以将环上的一点连到叉出去的树上，破环成链，连出去的点随树的更改而更改，不产生额外贡献。
  

故我们只需要找到纯环的个数，并查集判断即可。

---

## 作者：Inv_day_in_R (赞：2)

这道题其实可以将抽象的字符串修改变成清晰易懂的图上操作，一共 $26$ 个点，也就是 $26$ 个字符。每条边从 $S_i$ 连到 $T_i$。很显然，每个点的出度最多为一，否则需要把一个字符变成多个字符，显然不可能。在每一条边的起点上都有一块石头，它们需要移动到这条边的终点，但是每次移动必须把点上所有石头一起移动。这时可能会有以下几种联通块：

1. 孤立点

    根本没有石头。

2. 自环

    你需要移动它吗？

3. 环

    这个看似无解，实际上只需要额外的一个孤立点即可。把环上任意一个石头扔到孤立点上，其它依次移动即可，最后再从孤立点移回来。

4. 树（操作完产生孤立点）

    按深度从浅到深移动即可。

5. 根上带有自环的树（操作完产生孤立点）

    同上。

6. 普通基环树（操作完产生孤立点）

    这个就比较复杂了，看图：

![](https://cdn.luogu.com.cn/upload/image_hosting/jw4b7yc0.png)

将 b 点上的石头移到 d 点上去，之后 a 到 b，c 到 a 等等。也就是把环上一石移到与它有相同目的地的石头所在点。

这时就能发现，除了第三种以外都可以独立解决，所以如果只有环和自环的话，无解！其他情况分类计算即可。

代码：

```cpp
namespace AC{
int a,as[26],bs[26],d,vis[26],e,deg[26];
string b,c;
void dfs(int p){
	vis[p]=1;
	if(as[p]==-1||vis[as[p]])return;
	dfs(as[p]);
}
void solve(){
	cin>>a>>b>>c;
	for(int i=0;i<26;i++)as[i]=-1;
	if(b==c){
		cout<<0;
		return;
	}
	for(int i=0;i<a;i++){
		if(as[b[i]-'a']!=-1&&as[b[i]-'a']!=c[i]-'a'){
			cout<<-1;
			return;
		}
		if(as[b[i]-'a']==-1&&b[i]!=c[i]){
			e++;
			deg[c[i]-'a']++;
		}
		as[b[i]-'a']=c[i]-'a';
		d+=1-bs[c[i]-'a'];
		bs[c[i]-'a']=1;
	}
	if(d==26){
		cout<<-1;
		return;
	}
	for(int i=0;i<26;i++)if(!vis[i]&&!deg[i])dfs(i);
	for(int i=0;i<26;i++)if(!vis[i])dfs(i),e++;
	cout<<e;
}
}
```

---

## 作者：封禁用户 (赞：2)

省流：有图题解见 P9013。

没错，abc 出 USACO 原题而且还一模一样。

## Solution

首先 $s=t$ 时操作数为 $0$。

考虑把 $s_i \to t_i$ 看成限制，首先如果两个相同的字符对应不同的字符，那么一定无解，这个判下出度即可。

于是最后就剩下了好几个基环树状物，考虑到对于一个环可以通过加一个外部点的方式来断环成链，这样操作数 $+1$，如果没有外部点（$t$ 中不存在的点）就无解。

但是这样是过不了的，因为我们还忘记了一种情况。

如果一个环的某个点 $v$ 有其他入边 $(x,v)$，那么可以通过第一步将 $v$ 在环上的上一个点 $u$ 向 $x$ 连边（操作），从而不花费额外的操作数完成对环的操作。

## Code

写得有点长了，实际上好像也没法再短多少。

```cpp
int n,in[200],out[200];
string s,t;
char to[200];
bitset <200> vis,isr,tt;

il int dfs(int u)
{
	if(!u) return 0;
	if(vis[u]) 
	{
		isr[u]=1;
		return in[u]>=2 ? 2 : 1;
	}
	vis[u]=1;
	
	int lty=dfs(to[u]);
	if(!lty) return 0;
	
	isr[u]=1;
	return in[u]>=2 ? 2ll : lty;
}

signed main()
{
    read(n),read(s,t),s="$"+s,t="$"+t;

    rep(i,1,n)
    {
        if(to[s[i]] && to[s[i]]!=t[i]) return cout<<-1,0;
        to[s[i]]=t[i];
    }
    rep(i,'a','z') to[i] && (++out[i],++in[to[i]]);
    
    {
	    rep(i,1,n) tt[t[i]]=1;
	    int tot=0;
	    rep(i,'a','z') tot+=tt[i];
	    if(tot==26) return cout<<(s==t ? 0 : -1),0;
    }
    
    int ans=0;
    rep(i,'a','z')
    {
        if(out[i]>1) return cout<<-1,0;
        ans+=(out[i] && to[i]!=i);
    }
    
    int qwq;
    rep(i,'a','z') if(!isr[i] && to[i]!=i && in[i])
    {
    	vis=0,qwq=dfs(i);
    	ans+=qwq==1;
    }
    
    write(ans);

    return 0;
}
```

---

华风夏韵，洛水天依！

---

## 作者：2012_Zhang_ (赞：2)

## 思路解析
首先我们分析一下这题，很快就得出两个结论。  
1. 当有一种字母同时需要转化为多种字母时，判为无解。  
2. 当 $t$ 中出现所有字母时，若 $s \ne t$ 时，判为无解。

接下来我们再思考一下如何得出答案，将字母映射成点，对于 $s$ 与 $t$ 中，对于未出现的 $s_i$ 向 $t_i$ 连一条有向边。  
则 $Ans$ 的初始值为图中的边数，然后注意到图上如果形成环，那么需要用未出现的字母打破环，$Ans$ 就要加一。  
所有的情况考虑完了，所以 $Ans= \text{边数}+\text{环数}$。

代码奉上：
## AC CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e6+5;
const double eps=1e-6;
int n,cnt;
string s,t;
int vis[maxn],to[maxn],sum,r[maxn],ans,f[maxn];
void dfs(char c){
	vis[c]=1;
	if(!vis[to[c]]) dfs(to[c]);
}
queue<int>q;
set<char>st;
void topu(){
	for(char i='a';i<='z';i+=1)
		if(!r[i]) q.push(i);
	while(!q.empty()){
		int x=q.front();
		vis[x]=1;
		q.pop();
		if(!vis[to[x]]) r[to[x]]=0,q.push(to[x]);
	}
}
signed main(){
	cin>>n>>s>>t;
	for(int i=0;i<n;i++){
		if(to[s[i]]&&to[s[i]]!=t[i]){
			cout<<-1;
			return 0;
		}
		if(!to[s[i]]&&s[i]!=t[i]) ans++,r[t[i]]++;
		st.emplace(t[i]);
		to[s[i]]=t[i];	
	}
	if(st.size()==26){
		int f=0;
		for(int i=0;i<n;i++) f+=(s[i]!=t[i]);
		if(f) cout<<-1;
		else cout<<0;
		return 0;
	}
	topu();
	for(char i='a';i<='z';i+=1)
		if(!vis[i]) ans++,dfs(i);
	cout<<ans;
	return 0;
}

---

## 作者：ran_qwq (赞：2)

原：P9013。

因为操作是对一个字符进行的，如果 $s$ 的一个字符对应 $t$ 中两个或以上字符，无解。

每对字符 $(s_i,t_i)$ 的位置和出现的次数已经不重要了，我们只关心有没有出现，所以可以把它转化为图论问题，连有向边 $s_i\to t_i$。

一个 $s_i$ 对应多个 $t_i$ 的无解情况被判掉了，现在连出来的图是树或者基环树的森林：

![](https://cdn.luogu.com.cn/upload/image_hosting/ukjqemf5.png)

具体来说，每个弱连通分量有三种情况：一条链、一个环、一棵不是环的基环树，分别对应上图的 abc、def、ghijk。

对于一条链（以 abc 为例），先将 b 变成 c，再将 a 变成 b，最小操作次数是边数。

对于一个环（以 def 为例），我们第一步不能替换两个环内字符（这样字符种数会减少，无法达成目标），需要从外面找一个字符（假设它是 z）。先将 d 变成 z，再将 f 变成 d，再将 e 变成 f，最后将 d 变成 e，最小操作次数是边数 $+1$。

对于一棵不是环的基环树（以 ghijk 为例），可以使用某个分叉作为“突破口”（相当于环的“从外面找一个字符”），把环上的点都搞定，再去处理每个分叉，最小操作次数是边数。

容易发现，答案就是边数加环数。把环找出来可以从每个没有入度的点开始 dfs 并标记点，对于没被标记的点数弱连通分量个数即可。

```cpp
#define il inline
const int N=30;
int n,id,as,hd[N],b[N],in[N],ot[N],vs[N],mp[N][N]; string s,t; queue<int> q;
struct EDGE {int to,ne;} e[N*N];
il void add(int u,int v) {e[++id]={v,hd[u]},hd[u]=id,ot[u]++,in[v]++;}
void dfs(int u) {vs[u]=1; for(int i=hd[u],v;i;i=e[i].ne) if(!vs[v=e[i].to]) dfs(v);}
void QwQ() {
	n=rd(),cin>>s>>t;
	if(s==t) return wr(0,"\n");
	for(int i=0;i<n;i++) mp[s[i]-'a'][t[i]-'a']=1;
	for(int i=0;i<26;i++) for(int j=0;j<26;j++) if(mp[i][j])
		if(i!=j) add(i,j),as++;
		else ot[i]++;
	for(int i=0;i<26;i++) if(ot[i]>1) return wr(-1,"\n");
	for(int i=0;i<n;i++) b[t[i]-'a']=1;
	if(count(b,b+26,1)==26) return wr(-1,"\n");
	for(int i=0;i<26;i++) if(!in[i]) q.push(i);
	for(;q.size();) {
		int u=q.front(); q.pop(),vs[u]=1;
		for(int i=hd[u],v;i;i=e[i].ne) if(!vs[v=e[i].to]) q.push(v);
	}
	for(int i=0;i<26;i++) if(!vs[i]) as++,dfs(i);
	wr(as,"\n");
}
```

---

## 作者：joe_zxq (赞：0)

[此题解建议配合视频讲解食用。](https://www.bilibili.com/video/BV1q3ZrYfEcV/)

可以转换成一个图论问题，每个字符为一个节点。将所有 $S_i$ 和 $T_i$ 连边。

无解的情况分为两种：

- $S_i$ 有多个映射导致冲突。
- $T_i$ 的字符集为所有 $26$ 个字符，且 $S \neq T$。

考虑到对于每一种连通块的类型，不考虑自环，设边数为 $e$。如果是一个单一的环，则需要一个外部节点来进行辅助，易证需要 $e+1$ 步。如果是其它结构，如树或树与环的组合等，可以每一步让子节点向父节点传递，也都能易证只需要 $e$ 步。

于是答案即为抛去自环之外的边数加上单一环的连通块数量。

[你们要的代码。](https://atcoder.jp/contests/abc399/submissions/64401410)

---

## 作者：zjc5 (赞：0)

[题目链接](https://www.luogu.com.cn/problem/AT_abc399_e)

**思路：**

记录 $T$ 中的每一个字母对应的 $S$ 中的字母，设字母 $i$ 对应的个数为 $c_i$。

若两个不同的字母对应一个相同的字母，显然无解。

考虑将每个字母对应的变成同一个字母 $j$，然后再修改为 $i$。

对于 $T$ 中的一个字母 $i$，若它所对应的字母中存在 $i$，此时 $i=j$，花费 $c_i-1$ 次操作，同时设 $c_i$ 为 $0$。

其余 $j$ 修改为 $i$ 花费 $c_i$ 次操作，从后往前考虑。

接着每次对于一个字母 $i$，查找是否存在对应的字母 $j$ 使得 $c_j=0$，选它为最后一个可以保证不与之前冲突，并设 $c_i$ 为 $0$，以保证其不在影响之前的操作。

容易发现最后的仍无法匹配的 $i$ 的 $c_i$ 一定为 $1$。将 $i$ 连向它对应的字母后会形成若干个环。

观察样例 4 可以发现大小为 $L$ 的环，需要花费 $L+1$ 次操作。注意要保证 $T$ 中至少不包含一个字母，否则显然无解。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200010;
int T,n;
char s[N],t[N];
int ct[26];
bool bc[26];
int fa[26],sz[26];
int find(int x){
	return x==fa[x]?x:fa[x]=find(fa[x]);
}
signed main(){
	cin>>n>>(s+1)>>(t+1);
	for(int i=1;i<=n;i++)
		ct[t[i]-'a']|=1<<(s[i]-'a');
	bool bl=1,cntt=0;
	for(int i=0;i<26;i++){
		for(int j=i+1;j<26;j++)
			if(ct[i]&ct[j]) bl=0;
		if(!ct[i]) cntt=1;
	}
	if(!bl){
		puts("-1");
		return 0;
	}
	int ans=0;
	for(int i=0;i<26;i++)
		if(ct[i]&&((ct[i]>>i)&1)){
			int cnt=0;
			for(int j=0;j<26;j++)
				if((ct[i]>>j)&1) cnt++;
			ans+=cnt-1;
			ct[i]=0;
		}
	for(int _=0;_<26;_++){
		for(int i=0;i<26;i++)
			if(ct[i]){
				int cnt=0;
				for(int j=0;j<26;j++)
					if((ct[i]>>j)&1) cnt++;
				bool b=0;
				for(int j=0;j<26;j++)
					if(((ct[i]>>j)&1)&&!ct[j]) b=1;
				if(b) {
					ans+=cnt;
					ct[i]=0;
				}
			}
	}
	for(int i=0;i<26;i++){
		fa[i]=i;
		sz[i]=1;
	}
	for(int i=0;i<26;i++)
		if(ct[i]){
			int p=find(i),q;
			for(int j=0;j<26;j++)
				if((ct[i]>>j)&1){
					q=find(j);
					break;
				}
			if(p!=q){
				fa[p]=q;
				sz[q]+=sz[p];
			}
		}
	bool in=0;
	for(int i=0;i<26;i++)
		if(ct[i]){
			int p=find(i);
			ans+=sz[p]+1;
			sz[p]=-1;
			in=1;
		}
	if(!cntt&&in) puts("-1");
	else cout<<ans<<"\n";
	return 0;
}
```

---

