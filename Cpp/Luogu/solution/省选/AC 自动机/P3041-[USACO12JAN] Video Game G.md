# [USACO12JAN] Video Game G

## 题目描述

Bessie 在玩一款游戏，该游戏只有三个技能键 `A`，`B`，`C` 可用，但这些键可用形成 $n$ 种特定的组合技。第 $i$ 个组合技用一个字符串 $s_i$ 表示。

Bessie 会输入一个长度为 $k$ 的字符串 $t$，而一个组合技每在 $t$ 中出现一次，Bessie 就会获得一分。$s_i$ 在 $t$ 中出现一次指的是 $s_i$ 是 $t$ 从某个位置起的连续子串。如果 $s_i$ 从 $t$ 的多个位置起都是连续子串，那么算作 $s_i$ 出现了多次。

若 Bessie 输入了恰好 $k$ 个字符，则她最多能获得多少分？

## 说明/提示

#### 样例 1 解释

Bessie 如果输入 `ABACBCB`，则 `ABA` 出现了一次，`ABACB` 出现了一次，`CB` 出现了两次，共得到 $4$ 分。可以证明这是最优的输入。

#### 数据规模与约定

对于全部的测试点，保证：

- $1 \leq n \leq 20$，$1 \leq k \leq 10^3$。
- $1 \leq |s_i| \leq 15$。其中 $|s_i|$ 表示字符串 $s_i$ 的长度。
- $s$ 中只含大写字母 `A`，`B`，`C`。

## 样例 #1

### 输入

```
3 7 
ABA 
CB 
ABACB 
```

### 输出

```
4 
```

# 题解

## 作者：yybyyb (赞：23)

这题真的很醉呀。。。。

首先构建出AC自动机

然后在AC自动机上面跑DP

转移很显然从Trie树的节点跳到他的儿子节点

但是要注意一个问题，

在计算的时候，每一个节点加入后能够

造成的贡献

要加上他的子串的贡献

然后就是丑陋的代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<queue>
#include<algorithm>
using namespace std;
#define INF 1000000
int N,K;
int tot=0,ans;
char s[20];
int f[1100][400];
struct Node
{
    int vis[3];
    int p;
    int fail;
}t[5000];
void Add(char *s)
{
    int l=strlen(s);
    int now=0;
    for(int i=0;i<l;++i)
    {
        if(!t[now].vis[s[i]-'A'])
            t[now].vis[s[i]-'A']=++tot;
        now=t[now].vis[s[i]-'A'];
    }
    t[now].p++;
}
void Build()
{
    queue<int> Q;
    for(int i=0;i<3;++i)
        if(t[0].vis[i])Q.push(t[0].vis[i]);
    while(!Q.empty())
    {
        int u=Q.front();Q.pop();
        for(int i=0;i<3;++i)
        {
            if(t[u].vis[i])
            {
                t[t[u].vis[i]].fail=t[t[u].fail].vis[i];
                Q.push(t[u].vis[i]);
            }
            else
                t[u].vis[i]=t[t[u].fail].vis[i];
        }
        t[u].p+=t[t[u].fail].p;
    }
}
void DP()
{
    for(int T=0;T<=K;++T)
        for(int i=1;i<=tot;++i)
            f[T][i]=-INF;
    for(int T=1;T<=K;++T)
    {
        for(int i=0;i<=tot;++i)
        {
            for(int j=0;j<3;++j)
                f[T][t[i].vis[j]]=max(f[T][t[i].vis[j]],f[T-1][i]+t[t[i].vis[j]].p);
        }
    }
    for(int i=0;i<=tot;++i)ans=max(ans,f[K][i]);
}
int main()
{
    scanf("%d%d",&N,&K);
    for(int i=1;i<=N;++i)
    {
        scanf("%s",s);
        Add(s);
    }
    Build();
    DP();
    printf("%d\n",ans);
    return 0;
}

```

---

## 作者：Orion545 (赞：17)

# 广告

### [蒟蒻のblog](http://www.cnblogs.com/dedicatus545/p/8907126.html)

# 思路

首先，有一个非常显然的思路就是dp：

设$dp[i][j]$表示前i个字符，最后一个为j

然后发现这个东西有后效性

改！设$dp[i][j]$代表前i个字符，最后15个的状态为j（压缩一下），转移的是候枚举增加那个字符，然后看从谁可以推过来

然后就TLE了，完全无压力

### 怎么优化这个算法？

显然，枚举完增加哪个字符以后，可以用AC自动机来实现多模匹配

然后发现：我们把j的定义变成AC自动机上面的点j，这样一个点就代表一种状态，状态之间互相不重复，而且也没有后效性

这样的定义方法还有一个好处：状态少，从$3^{15}$个变成了$300$个

于是我们得到最终做法：

### 最终算法

对于输入的模板串建立AC自动机

令$dp[i][j]$表示前i个字符，最后一个字符跑到AC自动机的第j位上的最大答案

于是我们只要对于每个$dp[i][j]$枚举下一个是A,B,C,转移到下一个节点j'，然后跳一遍fail指针

对于匹配到的一个长度为k的模板串，$dp[i+1][j']=max\left(dp[i+1][j'],dp[i-k][j]\right)$

最后答案就是$dp[K][i]$的最大值

# Code

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
struct node{
    int num,fail,son[3];
    node(){num=fail=0;memset(son,0,sizeof(son));}
}a[510];int cnt;
void add(char s[]){//插入字符串到trie
    int len=strlen(s),i,cur=0;
    for(i=0;i<len;i++){
        if(!a[cur].son[s[i]-'A']) a[cur].son[s[i]-'A']=++cnt;
        cur=a[cur].son[s[i]-'A'];
    }
    a[cur].num++;
}
void getfail(){//bfs求fail指针
    int u,v,q[510],head=0,tail=0,i;
    for(i=0;i<3;i++){
        if(!a[0].son[i]) continue;
        a[0].fail=0;q[tail++]=a[0].son[i];
    }
    while(head<tail){
        u=q[head++];
        for(i=0;i<3;i++){
            v=a[u].son[i];
            if(v) a[v].fail=a[a[u].fail].son[i],q[tail++]=v;
            else a[u].son[i]=a[a[u].fail].son[i];
        }
    }
}
int m,n,dp[1010][510];bool vis[1010][510];
int proc(int cur,int val){//跳fail指针求值
    while(cur) val+=a[cur].num,cur=a[cur].fail;
    return val;
}
int main(){
    scanf("%d%d",&m,&n);int i,j,k,tmp;char s[20];
    for(i=1;i<=m;i++) scanf("%s",s),add(s);
    getfail();vis[0][0]=1;
    for(i=0;i<n;i++){
        for(j=0;j<=cnt;j++){
            if(!vis[i][j]) continue;
            for(k=0;k<3;k++){
                tmp=a[j].son[k];
                dp[i+1][tmp]=max(dp[i+1][tmp],proc(tmp,dp[i][j]));
                vis[i+1][tmp]=1;
            }
        }
    }
    int ans=0;
    for(i=0;i<=cnt;i++) ans=max(ans,dp[n][i]);
    printf("%d\n",ans);
}
```

---

## 作者：试试事实上吗 (赞：13)

### $AC$自动机$+dp$ 

~~当年被这道题暴打，现在回来复仇~~

#### 1.设计状态
$dp[i][j]$表示长度为$i$，当前在$trie$上的$j$位置时的最大得分

其实AC自动机的题感觉状态都是这样，至少我遇到的都是这样，~~可能是我太菜了~~

#### 2.状态转移方程

$dp[i][tr[j][k]]=max(dp[i-1][j]+is[tr[j][k])$

即用父亲更新儿子，因为本题要求求最大值，所以取max。

~~接下来就是你们最喜欢的代码~~

## $Code$

```cpp
#include <cstdio>
#include <iostream>
#include <string>
#include <queue>
#include <cstring>
using namespace std;
const int maxl=1e3+5,maxn=15*20+5;
int tr[maxn*25][3],fail[maxn*25],tot,is[maxn*25];
int dp[maxl*2][maxn*2],n,k;

inline void insert(string s)
{
    int len=s.length(),u=0;
    for(int i=0;i<len;i++)
    {
        int &v=tr[u][s[i]-'A'];
        u=v?v:v=++tot;
    }
    is[u]++;
}

void get_fail()
{
    queue<int> que;
    for(int i=0;i<3;i++)
        if(tr[0][i]) que.push(tr[0][i]);
    while(!que.empty())
    {
        int u=que.front();que.pop();
        for(int i=0;i<3;i++)
        {
            int &v=tr[u][i];
            if(v){
                fail[v]=tr[fail[u]][i];
                que.push(v);
            }
            else v=tr[fail[u]][i];
        }
        is[u]+=is[fail[u]];//要加上fail[u]的is，因为走到u后马上会转移到fail[u]
    }
}

int main()
{
    ios::sync_with_stdio(false);
    string s;
    cin>>n>>k;
    for(int i=1;i<=n;i++)
    {
        cin>>s;insert(s);
    }
    get_fail();
    memset(dp,-0x3f,sizeof(dp));//初始化dp
    for(int i=0;i<=k;i++) dp[i][0]=0;//初始化dp
    for(int i=1;i<=k;i++)
        for(int j=0;j<=tot;j++)
            for(int k=0;k<3;k++)
                dp[i][tr[j][k]]=max(dp[i][tr[j][k]],dp[i-1][j]+is[tr[j][k]]);
    int ans=-0x3f3f3f3f;
    for(int i=0;i<=tot;i++)
        ans=max(ans,dp[k][i]);//记得取max
    cout<<ans<<endl;
    return 0;
}
```
码字不容易，求过qwq


---

## 作者：lgswdn_SA (赞：13)

[[USACO12JAN]视频游戏的连击Video Game Combos](https://www.luogu.com.cn/problem/P3041)


~~看别的题解写的都不很完善，自己作死发一篇~~

拿到题目，一看，字符串啊，而且还有后缀的影响，最优化问题，果断一个 AC 自动机+ DP 上去

好吧，这是我的第一道 AC+DP 。闲话少说，直接解释。

## AC 自动机
[AC Automation模板题](https://www.luogu.com.cn/problem/P3808)

这道题每个节点都有一些关键的要素
```cpp
struct node{
	int ch[4],//Trie树上的孩子节点
    	nxt, //失败指针
    	fin, //是多少个模式串的结尾
   	val; //所能给最后的字符串带来的价值
}tr[N];
```
```ch,nxt,fin```都是 AC 自动机模板里的东西，那么```val```怎么算呢？

显然，加入一个字符所能带来的代价，是有**多少个字符串以它结尾**。  

我们发现，根据 AC 自动机的特性，Trie 树上的根到$\operatorname{nxt}_u$ 的路径所形成的字符串，应该是 Trie 树上根到 $u$ 的路径所形成的字符串的一个**后缀**

这也就意味着，一旦加入了节点$u$，那么我们不但能获得```tr[u].fin```的价值，还能获得```tr[tr[u].nxt].val```的价值

那不就是一个类似于 DP 的东西嘛

所以在计算 ```nxt``` 的时候我们也可以顺带把 ```val```给算出来

```cpp
struct node{
	int ch[4],nxt,fin,val;
}tr[2009]; int tot=1;
void ins(string s){ //Trie  
	int u=1;
	for(int i=0;i<s.size();i++){
		if(!tr[u].ch[s[i]-'A']) tr[u].ch[s[i]-'A']=++tot;
		u=tr[u].ch[s[i]-'A'];
	}
	tr[u].fin++;
} 
void ac(){ //nxt 和 val （AC Automation正常操作） 
	for(int i=0;i<3;i++) tr[0].ch[i]=1;
	queue<int>q; q.push(1); tr[1].nxt=0;
	while(!q.empty()){
		int u=q.front(); q.pop();
		for(int i=0;i<3;i++)
			if(!tr[u].ch[i]) tr[u].ch[i]=tr[tr[u].nxt].ch[i];
			else{
				q.push(tr[u].ch[i]); int v=tr[u].nxt;
				while(v&&!tr[v].ch[i]) v=tr[v].nxt;
				tr[tr[u].ch[i]].nxt=tr[v].ch[i];
			}
		tr[u].val=tr[u].fin+tr[tr[u].nxt].val;
	}
}
```

## DP
```f[i][u]```表示为长度为$i$的字符串，且当前已计算的节点是 Trie 上的编号为$u$的节点的最大得分

决策：$u$到孩子的边，选 A 还是 B 还是 C

转移方程：```f[i][tr[u].ch[k]]=max(f[i][tr[u].ch[k]],f[i-1][u]+tr[tr[u].ch[k]].val)```

```cpp
	memset(f,0xaf,sizeof(f));
	f[0][1]=0;
	for(int i=1;i<=m;i++){ //dp
		for(int u=1;u<=tot;u++){
			for(int k=0;k<3;k++){
				f[i][tr[u].ch[k]]=
					max(f[i][tr[u].ch[k]], f[i-1][u]+tr[tr[u].ch[k]].val);
			}
		}
	}
```


# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int ch[4],nxt,fin,val;
}tr[2009]; int tot=1;
void ins(string s){ //Trie  
	int u=1;
	for(int i=0;i<s.size();i++){
		if(!tr[u].ch[s[i]-'A']) tr[u].ch[s[i]-'A']=++tot;
		u=tr[u].ch[s[i]-'A'];
	}
	tr[u].fin++;
} 
void ac(){ //nxt 和 val （AC Automation正常操作） 
	for(int i=0;i<3;i++) tr[0].ch[i]=1;
	queue<int>q; q.push(1); tr[1].nxt=0;
	while(!q.empty()){
		int u=q.front(); q.pop();
		for(int i=0;i<3;i++)
			if(!tr[u].ch[i]) tr[u].ch[i]=tr[tr[u].nxt].ch[i];
			else{
				q.push(tr[u].ch[i]); int v=tr[u].nxt;
				while(v&&!tr[v].ch[i]) v=tr[v].nxt;
				tr[tr[u].ch[i]].nxt=tr[v].ch[i];
			}
		tr[u].val=tr[u].fin+tr[tr[u].nxt].val;
	}
}
int n,m,f[2009][409],ans;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){string s;cin>>s;ins(s);}
	ac();
	memset(f,0xaf,sizeof(f));
	f[0][1]=0;
	for(int i=1;i<=m;i++){ //dp
		for(int u=1;u<=tot;u++){
			for(int k=0;k<3;k++){
				f[i][tr[u].ch[k]]=
					max(f[i][tr[u].ch[k]], f[i-1][u]+tr[tr[u].ch[k]].val);
			}
		}
	}
	for(int u=1;u<=tot;u++) ans=max(ans,f[m][u]);
	printf("%d",ans);
	return 0;
}
```


于是就[**AC**](https://www.luogu.com.cn/record/30615418)自动机了

---

## 作者：Refined_heart (赞：4)

第一道$AC$自动机$+DP.$

首先，一个自动机上$DP$的套路是设$dp[i][j]$表示长度为$i$匹配到$j$节点的最优得分。

那么，由于我们已经建好了$Trie$图，我们就应该提前把走到节点$j$的所有连击操作处理出来。

有一条显然结论：如果在$fail$树上经过了这个串结尾节点中子树中的任意一点，则这次匹配一定会包含这个串。

换句话说，我们在对每一个节点更新$fail$的时候，其分值应该直接把其$fail$的分值加上。

于是我们进行$dp.$

首先初始值都是$-inf,$但对于匹配节点在根的情况应该是$0.$

至于为什么$dp[0][*]$不能赋值为$0,$是因为根本不可能存在这种状态。匹配长度为$0$不可能匹配到其他节点。

但初始时，不管哪一个节点和$0$匹配，其一定不会有任何分数。根节点本身是一个空节点。

解决初始值问题，我们可以进行$dp.$

枚举长度，枚举节点，再枚举字符。对于一个状态，我们应该取所有能到达这个状态的$dp$值的$\max.$因为我**只能**输入$k$个字符。

剩下的就是模板了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int dp[5000][2000];
const int MAXN=4000;
int pos[MAXN],cnt[MAXN];
int tot,n;
char st[MAXN];
struct Tree{
	int ch[3],fail;
}T[MAXN];
vector<int>to[MAXN];
int num[MAXN];
int insert(char *str,int len){
	int u=0;
	for(int i=0;i<len;++i){
		int x=str[i]-'A';
		if(!T[u].ch[x])T[u].ch[x]=++tot;
		u=T[u].ch[x];
	}
	num[u]++;return u;
}
void bfs(){
	queue<int>q;
	for(int i=0;i<3;++i){
		if(T[0].ch[i]){
			int v=T[0].ch[i];
			T[v].fail=0;
			q.push(v);
		} 
	}
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=0;i<3;++i){
			if(T[u].ch[i]){
				int v=T[u].ch[i];
				T[v].fail=T[T[u].fail].ch[i];
				q.push(v);
			}
			else T[u].ch[i]=T[T[u].fail].ch[i];
		} 
		to[T[u].fail].push_back(u);
		num[u]+=num[T[u].fail];
	}
}
int K;

int main(){
	scanf("%d%d",&n,&K);
	for(int i=1;i<=n;++i){
		scanf("%s",st);
		int L=strlen(st);
		pos[i]=insert(st,L);
	}
	bfs();
	memset(dp,128,sizeof(dp));
	for(int i=0;i<=K;++i)dp[i][0]=0;
	for(int i=1;i<=K;++i){
		for(int j=0;j<=tot;++j){
			for(int k=0;k<3;++k){
				dp[i][T[j].ch[k]]=max(dp[i][T[j].ch[k]],dp[i-1][j]+num[T[j].ch[k]]); 
			}
		}
	}
	int ans=0;
	for(int i=0;i<=tot;++i)ans=max(ans,dp[K][i]);
	printf("%d\n",ans);
	return 0;
} 
```


---

## 作者：BillYang (赞：2)

建立AC自动机后Dp水过

注意tot和child对于失败标记的处理

```cpp
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<vector>
#include<cstdio>
#include<cmath>
#include<queue>
using namespace std;
inline const int Get_Int() {
    int num=0,bj=1;
    char x=getchar();
    while(x<'0'||x>'9') {
        if(x=='-')bj=-1;
        x=getchar();
    }
    while(x>='0'&&x<='9') {
        num=num*10+x-'0';
        x=getchar();
    }
    return num*bj;
}
const int maxn=30000;
struct Tree {
    int child[26],fail,tot; //fail失败指针
    void clear() {
        memset(child,0,sizeof(child));
        fail=0;
        tot=0;
    }
};
int root=1;
struct Aho_Corasick_Automaton { //AC自动机
    int cnt;
    Tree tree[maxn];
    void init() {
        cnt=1;
        memset(tree,0,sizeof(tree));
    }
    void insert(string s) {
        int now=root,len=s.length();
        for(int i=0; i<len; i++) {
            int j=s[i]-'A';
            if(!tree[now].child[j]) {
                tree[++cnt].clear();
                tree[now].child[j]=cnt;
            }
            now=tree[now].child[j];
        }
        tree[now].tot++;
    }
    void buildfail() { //Bfs构造Fail指针
        queue<int>Q;
        Q.push(root);
        while(!Q.empty()) {
            int Now=Q.front();
            Q.pop();
            for(int i=0; i<3; i++) {
                int Next=tree[Now].child[i];
                if(Next==0) { //儿子不存在
                    if(tree[tree[Now].fail].child[i])tree[Now].child[i]=tree[tree[Now].fail].child[i];
                    else tree[Now].child[i]=root;
                    continue;
                }
                Q.push(Next);
                int fatherfail=tree[Now].fail; //父亲的失败指针
                while(fatherfail&&!tree[fatherfail].child[i])fatherfail=tree[fatherfail].fail; //寻找可退回点
                if(fatherfail)tree[Next].fail=tree[fatherfail].child[i]; //如果存在满足条件的点则设置失败指针
                else tree[Next].fail=root; //否则指回root
                tree[Next].tot+=tree[tree[Next].fail].tot;
            }
        }
    }
};
Aho_Corasick_Automaton ac;
int n,k,f[1005][3005],ans=-0x7fffffff/2;
int main() {
    ios::sync_with_stdio(false);
    cin>>n>>k;
    ac.init();
    for(int i=1; i<=n; i++) {
        string s;
        cin>>s;
        ac.insert(s);
    }
    ac.buildfail();
    for(int i=0; i<=k; i++)
        for(int j=1; j<=ac.cnt; j++)
            f[i][j]=-0x7fffffff/2;
    f[0][1]=0;
    for(int i=1; i<=k; i++)
        for(int j=1; j<=ac.cnt; j++)
            for(int k=0; k<3; k++)
                f[i][ac.tree[j].child[k]]=max(f[i][ac.tree[j].child[k]],f[i-1][j]+ac.tree[ac.tree[j].child[k]].tot);
    for(int i=1; i<=ac.cnt; i++)ans=max(ans,f[k][i]);
    cout<<ans<<endl;
    return 0;
}

```

---

## 作者：yanchengzhi (赞：1)

# 总结
[P3041 [USACO12JAN]Video Game G](https://www.luogu.com.cn/problem/P3041)
```cpp
/*
相当于是已知多个模式串求主串
用AC自动机预处理
设dp[i][j]表示前i个字符中选择一些 位于trie树中第j号节点的最大值
每次选择0 1 2(A B C)三个方向 计算val取max

注:trie树的指针的初始值是1 
*/
#include<bits/stdc++.h>
using namespace std;
const int inf=1e9;
struct AC{
	int ch[26],end,fail;
}a[305];
int n,m,point=1,dp[1005][305];//point must be 1
string s;
void build_trie(){
	int u=1;
	for(int i=0;i<s.size();i++){
		if(!a[u].ch[s[i]-'A'])a[u].ch[s[i]-'A']=++point;
		u=a[u].ch[s[i]-'A'];
	}
	a[u].end++;
}
void build_ac(){
	queue<int>q;
	for(int i=0;i<=2;i++)
		a[0].ch[i]=1;
	q.push(1);
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int i=0;i<=2;i++)
			if(!a[u].ch[i])a[u].ch[i]=a[a[u].fail].ch[i];
			else{
				a[a[u].ch[i]].fail=a[a[u].fail].ch[i];
				q.push(a[u].ch[i]);
			}
	}
}
int get_val(int v){
	int val=0;
	while(v>1)val+=a[v].end,v=a[v].fail;
	return val;
}
void DP(){
	for(int i=0;i<=m;i++)
	for(int j=0;j<=point;j++)
		dp[i][j]=-inf;
	dp[0][1]=0;
	for(int i=0;i<m;i++)
	for(int j=1;j<=point;j++){
		if(dp[i][j]==-inf)continue;
		for(int k=0;k<=2;k++){
			int val=get_val(a[j].ch[k]);
			dp[i+1][a[j].ch[k]]=max(dp[i+1][a[j].ch[k]],dp[i][j]+val);
		}
	}
	int ans=-inf;
	for(int i=1;i<=point;i++)
		ans=max(ans,dp[m][i]);
	cout<<ans;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>s;
		build_trie();
	}
	build_ac();
	DP();
	return 0;
}
```


---

## 作者：FREEH (赞：1)

P3041总结

【题目大意】
给出n个字典单词，问长度为k的字符串最多含有多少个字典单词。

【解题思路】
建立一个AC自动机，每一个节点要统计一串fail指针连接的节点的数量，因为一串字符串的分数必然包含其前缀的数量。然后用DP统计答案，动态转移明显是父节点转移到子节点，增加的数量是当前节点统计的总数。

【参考程序】
```
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;

char st[1000005],p[1000005];
struct TRIE{
    int son[4];
    int val;
}trie[1000005];
int fail[1000005],f[1005][1005];
int L;

void Fill_in(char *st,int rank)
{
    int len=strlen(st),u=0;
    for (int i=0;i<len;i++)
    {
        int v=st[i]-'A';
        if (!trie[u].son[v])
            trie[u].son[v]=++L;
        u=trie[u].son[v];
    }
    trie[u].val++;
}
void Build()
{
    queue <int> q;
    for (int i=0;i<3;i++)
        if (trie[0].son[i])
        {
            q.push(trie[0].son[i]);
            fail[trie[0].son[i]]=0;
        }
    while (!q.empty())
    {
        int now=q.front();q.pop();
        for (int i=0;i<3;i++)
        {
            if (trie[now].son[i])
            {
                fail[trie[now].son[i]]=trie[fail[now]].son[i];
                q.push(trie[now].son[i]);
            }else
            trie[now].son[i]=trie[fail[now]].son[i];
    		
		}
		trie[now].val+=trie[fail[now]].val;
	}
}
int main()
{
    int n,k;
    scanf("%d%d",&n,&k);
    for (int i=1;i<=n;i++)
    {
        scanf("%s",st);
        Fill_in(st,i);
    }
    Build();
    int ans=0;
    memset(f,-127,sizeof f);
    f[0][0]=0;
    for (int i=1;i<=k;i++)
    	for (int j=0;j<=L;j++)
    		for (int s=0;s<3;s++)
    		{
    			f[i][trie[j].son[s]]=
				max(f[i][trie[j].son[s]],f[i-1][j]+trie[trie[j].son[s]].val);
			}
	for (int i=0;i<=L;i++)
		ans=max(ans,f[k][i]);
	printf("%d\n",ans);
    return 0;
}

---

