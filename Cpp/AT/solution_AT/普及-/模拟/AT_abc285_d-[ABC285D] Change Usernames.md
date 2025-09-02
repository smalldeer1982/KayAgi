# [ABC285D] Change Usernames

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc285/tasks/abc285_d

あなたの運営する Web サービスには $ N $ 人のユーザがいます。

$ i $ 番目のユーザの現在のユーザ名は $ S_i $ ですが、$ T_i $ への変更を希望しています。  
ここで、$ S_1,\ldots,S_N $ は相異なり、$ T_1,\ldots,T_N $ も相異なります。

ユーザ名を変更する順序を適切に定めることで、以下の条件を全て満たすように、全てのユーザのユーザ名を希望通り変更することができるか判定してください。

- ユーザ名の変更は $ 1 $ 人ずつ行う
- どのユーザもユーザ名の変更は一度だけ行う
- ユーザ名の変更を試みる時点で他のユーザが使っているユーザ名に変更することはできない

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^5 $
- $ S_i,T_i $ は英小文字からなる $ 1 $ 文字以上 $ 8 $ 文字以下の文字列
- $ S_i\ \neq\ T_i $
- $ S_i $ は相異なる
- $ T_i $ は相異なる

### Sample Explanation 1

$ 1 $ 番目のユーザの現在のユーザ名は `b` であり、`m` への変更を希望しています。 $ 2 $ 番目のユーザの現在のユーザ名は `m` であり、`d` への変更を希望しています。 まず、$ 2 $ 番目のユーザのユーザ名を `m` から `d` に変更し、 その後 $ 1 $ 番目のユーザのユーザ名を `b` から `m` に変更することで、条件を満たしながら変更することができます。 最初の時点では $ 2 $ 番目のユーザのユーザ名が `m` なので、$ 1 $ 番目のユーザのユーザ名を同じ `m` に変更することはできません。

### Sample Explanation 2

$ 1 $ 番目のユーザの現在のユーザ名は `a` であり、`b` への変更を希望しています。 $ 2 $ 番目のユーザの現在のユーザ名は `b` であり、`c` への変更を希望しています。 $ 3 $ 番目のユーザの現在のユーザ名は `c` であり、`a` への変更を希望しています。 条件を満たしながらユーザ名の変更を行うことはできません。

## 样例 #1

### 输入

```
2
b m
m d```

### 输出

```
Yes```

## 样例 #2

### 输入

```
3
a b
b c
c a```

### 输出

```
No```

## 样例 #3

### 输入

```
5
aaa bbb
yyy zzz
ccc ddd
xxx yyy
bbb ccc```

### 输出

```
Yes```

# 题解

## 作者：FFTotoro (赞：7)

## 前言

看到了考场上好多人都在用拓扑排序等一类较高级的算法，蒟蒻被震撼了。

## 解法

这篇题解与其他题解的做法不同，不用图论，不用并查集，只需要使用一个简单好想的算法即可。

考虑一些用户什么时候不能更换用户名：显而易见，当且仅当别人的旧用户名与这个用户的新用户名起了冲突，这个人是不能更换的。

首先我们把能更换用户名的人处理出来，此时他们的旧用户名就不会影响其他人了。这个时候，我们再把先前与这些**更换完用户名的人的原用户名**有冲突的人拿出来，再取处理他们。

不断重复上述过程，直到所有人都处理完。在处理的某一个时刻，如果“待处理列表”空了且没有处理完所有人，那么一定无解。

“待处理列表”可以用 `std::set` 存储，“找人”则可以用 `std::map`	实现。

放代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
main(){
  ios::sync_with_stdio(false);
  int n,c=0; cin>>n;
  vector<pair<string,string> > a(n);
  vector<bool> b(n);
  map<string,int> x,y;
  for(int i=0;i<n;i++){
    cin>>a[i].first>>a[i].second;
    x[a[i].first]=y[a[i].second]=i+1; // 建立 map 映射，方便“找人”
  }
  set<int> d;
  for(int i=0;i<n;i++){
    if(!x[a[i].second]){
      if(y[a[i].first])d.emplace(y[a[i].first]-1); // 放进列表
      b[i]=true; x[a[i].first]=0; c++;
    }
  } // 第一轮扫描全部的人
  while(1){
    if(c==n){
      cout<<"Yes\n";
      return 0;
    } // 处理完了
    set<int> q;
    for(int i:d){
      if(!b[i]&&!x[a[i].second]){
        if(y[a[i].first])q.emplace(y[a[i].first]-1); // 放进列表
        x[a[i].first]=0; c++;
      }
    } // 把可以处理的拿出来处理
    if(q.empty()&&c<n){
      cout<<"No\n";
      return 0;
    } // 列表空了且还没处理完
    d=q; // 更新列表
  }
  return 0;
}

---

## 作者：zajasi (赞：4)

## 题意
有 $n$ 个人，第 $i$ 人刚开始有一个字符串 $a_i$，想要换成字符串 $b_i$。问 **能不能** 在同一时刻没有两个人手持的字符串相同的情况下完成调换？
## 样例解释
拿第一个样例和第二个样例举个例子。
```
2
b m
m d
```
第一步：将第二个人的 $m$ 换成 $d$。

第二步：将第一个人的 $b$ 换成 $m$。
```
3
a b
b c
c a
```
尝试满足第一个人，但调换后会跟第二个人重复。

尝试满足第二个人，但调换后会跟第三个人重复。

尝试满足第三个人，但调换后会跟第一个人重复。

所以不行。
## 解题思路
赛后，看了一眼同学的代码，发现是拓扑排序。可我觉得这道题是萌萌的深搜咩。

首先用 `map` 记录每个人手持的字符串。再用哈希记录每个人更改过没有。扫一遍，如果发现有一个人没更改过，就开始深搜。

深搜时，分类讨论：如果这个字符串目前还没有人目前有，就直接换掉，更改 `map` 的数据。反之，就继续深搜那一个阻拦他更改的人，直至找到一个人满足前面的条件，就回溯。若发现进入了一个环，那么也就是说是更改不了，也就是 `No`。

不懂？来，上代码。
## AC code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
string a[100010],b[100010];
map<string,int> m;
int h[100010];
map<string,int> id;
void dfs(int x,int dep){
    if(dep>n){//出现环
        cout<<"No";//更改不了这个人，再见
        exit(0);
    }
    if(m[b[x]]){//发现有人阻碍更改
        int y=id[b[x]];
        dfs(y,dep+1);//调查阻碍更改的人
        if(m[b[x]]){//发现还是不行
            cout<<"No";
            exit(0);
        }
        else{//阻碍更改的人没威胁了
            m[a[x]]--;
            m[b[x]]++;//更改
            a[x]=b[x];
            h[x]=1;
            return;
        }        
    }
    else{//没人阻碍更改
        m[a[x]]--;
        m[b[x]]++;//直接更改
        a[x]=b[x];
        h[x]=1;
        return;
    }
}
main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i]>>b[i];
        m[a[i]]++;
        id[a[i]]=i;//记录位置和次数
    }
    for(int i=1;i<=n;i++){
        if(h[i]==0){//没有更改过
            dfs(i,0);//尝试更改
        }
    }
    cout<<"Yes";
    return 0;
}
```

---

## 作者：Fire_flame (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc285_d)

----
## 题意简述

有一个 $n$ 条边的有向图，判断其中是否存在环。如果存在输出 `No`，否则输出 `Yes`。

注意节点编号是一个长度不超过 $8$ 的字符串。

## $\mathtt{Solution}$

这个题目很简单，直接跑一遍拓扑排序即可。

首先用哈希或者 map 将节点编号离散化，连边的过程中记录每一个点的入度。

读完 $n$ 条边以后，将所有入度为零的节点放进一个队列里面，然后跑广搜。

跑广搜的时候将所有与当前节点 $t$ 直接相连的 $v_i$ 的入度减一，将所有入度为零的节点放进一个队列里面……以此类推直到无法操作为止。

如果我们并没有遍历完所有的点，就代表有环，输出 `No`，否则输出 `Yes`。

不会拓扑排序的同学也可以用 dfs，详见代码二。

代码一：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5 + 5, MR = 1e6 + 5;
int n, cnt, num, res, head[MAXN], in[MAXN];
unordered_map<string, int>mp;
struct edge{
	int from, to, nxt;
}e[MR];
void add_edge(int u, int v){
	e[++ cnt] = {u, v, head[u]};
	head[u] = cnt;
} 
int main(){
	scanf("%d", &n);
	for(int i = 1;i <= n;i ++){
		string u, v;
		cin>>u>>v;
		if(!mp[u])mp[u] = ++num;
		if(!mp[v])mp[v] = ++num;
		in[mp[v]] ++;
		add_edge(mp[u], mp[v]);
	}
	queue<int>q;
	for(int i = 1;i <= num;i ++){
		if(in[i] == 0)q.push(i);
	}
	while(!q.empty()){
		int t = q.front();
		res ++;
		q.pop();
		for(int i = head[t];i;i = e[i].nxt){
			int v = e[i].to;
			in[v] --;
			if(in[v] == 0)q.push(v);
		}
	}
	if(res == num)puts("Yes");
	else puts("No");
	return 0;
}
```

代码二：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, i, j, k;
char a[15], b[15];
string s[100050];
map <string, int> v;//记忆和数组
map <string, string> f;//存储单向边
void dfs(string a){
    if(f.find(a) == f.end()) return;
    v[a] = 1;//搜索中
    string b = f[a];
    if(!v[b]) dfs(b);//搜过不再搜
    else if(v[b] == 1) m = 1;//环
    v[a] = -1;//搜索完
}
int main(){
    scanf("%d", &n);
    for(i=1; i<=n; i++){
        scanf("%s%s", a, b);
        f[a] = b, s[i] = a;
    }
    for(i=1; i<=n; i++){
        if(!v[s[i]]) dfs(s[i]);
    }//无环则行，否则不行
    printf("%s\n", m?"No":"Yes");
    return 0;
}
```


---

## 作者：sto_5k_orz (赞：1)

`2023.1.20` 添加了更详细的解释，为什么是判环。

这道题本蒟蒻题没读懂，但是 AC 了。

蒟蒻理解的题意：

每两个字符串连成一条边，问有没有环。

现在有了翻译，我们就可以证明一下：

我们想象成两个字符串连成一条边。

假设有一个环，形同 $a$ 至 $b$，$b$ 至 $c$，$c$ 至 $a$。

那么如果我先让 $a$ 改名，$a$ 改不了，因为有人叫作 $b$。

如果我先让 $b$ 改名，$b$ 也改不了，因为有人叫作 $c$。

如果我先让 $c$ 改名，$c$ 也改不了，因为有人叫作 $a$。

也就是说，想要 $s_i$ 改名，必须要没有人叫作 $t_i$。换句话讲，就是 $t_i$ 的入度为 $0$。

其实就是判环。

我们先用 map 存储，用编号代替每个字符串。

然后跑一遍拓扑排序就可以了。

注意：有环输出 $\texttt{No}$，没环才是 $\texttt{Yes}$。

那么我们要用 map 存储编号，尽量不要像 C 一样转换，这样比较大。

我的转换方式是输入之后，如果该字符串有编号，就用它本来的编号。否则，编号 $+1$，字符串的编号等于新的编号。

这样简单，节约内存。

```cpp
I void Add(string s) {
	if(id.count(s)) return ; // 如果 s 有编号了，就跳过
	id[s] = ++n; // 新建编号
}
```

加边只需要连接 $id_s,id_t$ 即可。

拓扑排序就不需要多讲了，就是个模板。

注意：不要手滑建成双向边！

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define CI const int
#define gc getchar
#define Mt(a, b) memset(a, b, sizeof a)
#define pc putchar
#define W while
#define I inline
CI N = 200010; map<string, int> id; int n, m; // 注意，最多会产生二十万个编号。
I void Add(string s) {
	if(id.count(s)) return ;
	id[s] = ++n;
}
int h[N], to[N], nxt[N], idx, in[N];
I void add(int a, int b) {to[++idx] = b; nxt[idx] = h[a]; h[a] = idx; in[b]++;}
I bool topo() {
	int cnt = 0;
	queue<int> q; for(int i = 1; i <= n; i++) if(!in[i]) q.push(i);
	W(!q.empty()) {
		int u = q.front(); q.pop(); cnt++;
		for(int i = h[u]; i; i = nxt[i]) {
			int v = to[i]; in[v]--;
			if(!in[v]) q.push(v);
		}
	}
	return cnt == n;
}
signed main() {
	cin >> m;
	W(m--) {
		string s, t;
		cin >> s >> t;
		Add(s), Add(t);
		add(id[s], id[t]);
	}
	if(topo()) puts("Yes"); else puts("No");
	return 0;
}
```

---

## 作者：lzyqwq (赞：1)

[更好的阅读体验](https://www.cnblogs.com/MnZnOIerLzy/articles/17055155.html)

# $\texttt{Description}$

[AtCoder Link](https://atcoder.jp/contests/abc285/tasks/abc285_d)

[洛谷 Link](https://www.luogu.com.cn/problem/AT_abc285_d)

> - 有 $n$ 个人，第 $i$ 个人有名字 $s_i$ 和理想名字 $t_i$。你每次可以将一个人的名字改成理想名字，前提是理想名字目前没人使用。每个人只可以改一次名字。
>
> - $1\le n\le 10^5$，$s_i\ne t_i$，$s_i$ 互不相同，$t_i$ 互不相同。

# $\texttt{Solution}$

结论：将 $s_i$ 连边向 $t_i$，若图无环则有解，否则无解。

证明：若图无环，则在拓扑序中存在出度为 $0$ 的点，这些点是没人占用的。所以可以按照拓扑排序中的层次**从后至前**依次更改名字。

否则，每个名字都有人占用，没有人可以让出自己的名字，无解。

因此拓扑判环，遍历的点数是否等于总点数（**不是 $n$**）即可。

注意字符串用 `map` 映射一下。

时间复杂度为 $\mathcal{O}(n\log_2 n)$，空间复杂度为 $\mathcal{O}(n)$。

# $\texttt{Code}$

```cpp
#include<bits/stdc++.h>
#define N 200005//坑点
using namespace std;
int n,rd[N],tot,has,q[10*N],h=1,t=0;
vector<int>g[N];
map<string,int>mp;
string a,b;
int main(){
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>a>>b;
        if(!mp[a]){
            mp[a]=++has;
        }
        if(!mp[b]){
            mp[b]=++has;
        }
        g[mp[a]].push_back(mp[b]);
        ++rd[mp[b]];
    }
    for(int i=1;i<=has;++i){
        if(!rd[i]){
            q[++t]=i;
        }
    }
    while(h<=t){
        int u=q[h++];
        ++tot;
        for(int v:g[u]){
            if(!--rd[v]){
                q[++t]=v;
            }
        }
    }
    if(tot^has){
        cout<<"No";
    }else{
        cout<<"Yes";
    }
}
```

---

## 作者：YBaggio (赞：1)

## 题意
有 $N$ 个人想改名，第 $i$ 个人要从 $S_i$ 改成 $T_i$，当一个用户想要改的名字没有人在使用的时候，这个用户可以成功改名。问是否所有用户都可以成功改名。
## 思路
我们考虑如果一个用户 $i$ 要改名的话，需要他想要改成的名字 $T_i$ 的主人 $j$ 改名，然后 $j$ 要改名有需要 $T_j$ 的主人 $k$ 改名……这样走下去，如果一个人想要改成的名字没有人再用，那么这些人就都可以改名了。但是如果走出了个环，也就是说 $i$ 要改名之前需要 $i$ 改名，这是不可能达到的。所以如果我们建立 $N$ 调边，第 $i$ 条边由 $S_i$ 指向 $T_i$ 最后我们只需要判断图中是否环就行了。

判环可以使用拓扑排序。
```cpp
#include<map>
#include<iostream>
#include<cstring>
#include<string>
#include<queue>
using namespace std;
const int maxn=200010;
int n,m,cnt,rd[maxn],head[maxn];
map<string,int>p;
queue<int>q;
struct E{
    int to,next;
}edge[maxn];
void add(int u,int v){
    edge[++cnt].to=v;edge[cnt].next=head[u];head[u]=cnt;
}
int main(){
    ios::sync_with_stdio(false);
    std::cin.tie(0);std::cout.tie(0);
    cin>>m;
    for(int i=1;i<=m;i++){
        string s,t;int x,y;
        cin>>s>>t;
        if(p.find(s)!=p.end())x=p[s];
        else p[s]=x=++n;
        if(p.find(t)!=p.end())y=p[t];
        else p[t]=y=++n;
        add(x,y);rd[y]++;
    }
    for(int i=1;i<=n;i++)if(!rd[i])q.push(i);
    int sum=0;
    while(!q.empty()){
        int x=q.front();q.pop();sum++;
        for(int i=head[x];i;i=edge[i].next){
            int y=edge[i].to;
            if(--rd[y]==0)q.push(y);
        }
    }if(sum!=n)cout<<"No";
    else cout<<"Yes";
    return 0;
}
```

---

## 作者：PerssonBrown (赞：0)

## 解决方案

对于每一次的改名操作（将 $u$ 改成 $v$），可以想到从 $u$ 连一条有向边到 $v$。

对于每个样例按照以上方法建图之后，会发现当图中**有环**时就**无法**完成改名。

那么这道题就变成了：给一张图，判断其中是否有环。

如果有环，那么 该图的强连通分量 $\neq$ 节点数量。

思路到此已经很清晰了，
最后只需要解决“将输入的字符串映射到数字”即可。

这可以用 `std::map<std::string, int>` 解决。

```cpp
std::map<std::string, int> user;
int inputCnt;

int query(std::string str) {
    if (user.find(str) == user.end()) {
        user[str] = ++inputCnt;
    }
    return user[str];
}
```

## 参考代码

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <map>
using std::cin;
using std::cout;

const int userLimit= 1e6 + 3;

std::vector<int> graph[userLimit];

std::map<std::string, int> user;
int inputCnt;

int query(std::string str) {
    if (user.find(str) == user.end()) {
        user[str] = ++inputCnt;
    }
    return user[str];
}

int dfn[userLimit], low[userLimit], dfnCnt;
int sccCnt, isStack[userLimit];
std::stack<int> s;

int min(int a, int b) {
    if (a < b) {
        return a;
    }
    return b;
}

void tarjan(int node) {
    low[node] = dfn[node] = ++dfnCnt;
    isStack[node] = 1;
    s.push(node);
    for (int nextNode : graph[node]) {
        if (!dfn[nextNode]) {
            tarjan(nextNode);
            low[node] = min(low[node], low[nextNode]);
        } else if (isStack[nextNode]) {
            low[node] = min(low[node], dfn[nextNode]);
        }
    }

    if (dfn[node] == low[node]) {
        ++sccCnt;
        while (true) {
            int t = s.top();
            isStack[t] = 0;
            s.pop();
            if (t == node) {
                break;
            }
        }
    }
}

int main() {
    int userCnt;
    cin >> userCnt;
    for (int i = 1; i <= userCnt; ++i) {
        std::string u, v;
        cin >> u >> v;
        graph[query(u)].push_back(query(v));
    }

    for (int i = 1; i <= inputCnt; ++i) {
        if (!dfn[i]) {
            tarjan(i);
        }
    }

    if (sccCnt != inputCnt) {
        cout << "No\n";
    } else {
        cout << "Yes\n";
    }

    return 0;
}
```

---

## 作者：Butterfly___qwq (赞：0)

# ABC285D 题解：
## 题意：
有 $n$ 个人要更改用户名，你可以调整他们更改的顺序，问是否能更改成功。
## 思路：
如何才能更改不成功？我们可以思考一下。以下情况会出现不成功：
- 甲希望将 $s1$ 更改为 $s2$。
- 乙希望将 $s2$ 更改为 $s3$。
- 丙希望将 $s3$ 更改为 $s1$。   

以上情况不成功，无论如何改变顺序都不行。这是三个人的情况，像以上的情况，四个人、五个人及以上都不行。想一想，这像什么？像不像一个环？我们想到了图。用图保存起来，判断里面有没有环，就可以了。问题又来了，如何判断一个图有没有环？我们可以使用并查集来判断一个图中是否存在环：
- 对于无向图来说，在遍历边时，如果结点 $u$ 和结点 $v$ 的“父亲”相同，那么结点 $u$ 和结点 $v$ 在同一个环中。
- 对于有向图来说，在遍历边时，如果结点 $u$ 的“父亲”是结点 $v$，那么结点 $u$ 和结点 $v$ 在同一个环中。
## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
map < string , int >m;
int fa[1000001];
int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}
int main(){
	int cnt=0,n;
	cin>>n;
	for(int i=1;i<=2*n;i++)fa[i]=i;
	for(int i=1;i<=n;i++){
		string a,b;cin>>a>>b;
		if(m[a]==0)m[a]=++cnt;
		if(m[b]==0)m[b]=++cnt;
		int x=find(m[a]),y=find(m[b]);
		if(fa[x]==y)
		{
			cout<<"No";
			return 0;
		}
		fa[y]=x;
	}
	cout<<"Yes";
	return 0;
}
```

---

## 作者：Otue (赞：0)

## 题目大意
给定 $n$ 条边，由字符串 $a$ 连向字符串 $b$，判断最后图存不存在环。
## 思路
考虑字符串连边比较复杂，则将其映射成一个数值（点的编号），方便建边。

映射方式也很简单，记录变量 $idx$，即为点的数量。每次输入一个字符串，如果此字符串没有在之前出现过，记录编号 `++idx` 。

建完边后，只需要对图进行判环，通常做法是进行拓扑排序，如果最后队列中元素的数量为点的数量，那么就无环，反之。
## 代码
```c++
#include <bits/stdc++.h>
using namespace std;

#define int long long
const int N = 2e5 + 5;
int n, idx, q[N];
map<string, int> vis;

int en, first[N], in[N];
struct edge {
    int e, next;
}ed[N];

void add_edge(int s, int e) {
    en++;
    ed[en].e = e;
    ed[en].next = first[s];
    first[s] = en;
}

signed main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        string x, y;
        cin >> x >> y;
        if (!vis[x]) vis[x] = ++idx;
        if (!vis[y]) vis[y] = ++idx;
        // idx 相当于点的数量
        add_edge(vis[x], vis[y]);
        in[vis[y]]++;
    }
    int hh = 0, tt = -1;
    for (int i = 1; i <= idx; i++) {
        if (in[i] == 0) q[++tt] = i;
    }
    while (hh <= tt) {
        int u = q[hh++];
        for (int p = first[u]; p; p = ed[p].next) {
            int e = ed[p].e;
            in[e]--;  
            if (in[e] == 0) q[++tt] = e;
        }
    }
    if (hh == idx) puts("Yes");  // 无环
    else puts("No");
}
```

---

## 作者：Lyu_echo (赞：0)

## 题意

给定 $N$ 对字符串 $S_i, T_i (1 \le i \le N)$。

第 $i$ 个人原名 $S_i$，可以改为 $T_i$。

问改名过程中会不会出现重名情况。

## 解题思路

第 $i$ 个人从 $S_i$ 改名成为 $T_i$，我们就将 $S_i$ 与 $T_i$ 间连接一条单向边。

若连接的图有环，这必定会重名。

使用拓扑排序判环即可。

## 代码实现

```cpp
int n, cnt;
int in_degree[100010];
string s[100010], t[100010];
vector<int> g[100010];
map<string, int> rnk;
set<string> st;
bool topo_sort() {
    queue<int> q;
    for (int i = 1; i <= cnt; i++) {
        if (in_degree[i] == 0) q.push(i);
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        cnt--;
        for (auto &v : g[u]) {
            in_dgree[v]--;
            if (in_degree[i] == 0) q.push(v);
        }
    }
    return cnt == 0;
}
void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> s[i] >> t[i];
        st.insert(s[i]);
        st.insert(t[i]);
    }
    for (auto &it : st) rnk[i] = ++cnt;
    for (int i = 1; i <= n; i++) {
        int u = rnk[s[i]];
        int v = rnk[t[i]];
        in_degree[v]++;
        g[u].push_back[v];
    }
    if (topo_sort) cout << "Yes" << endl;
    else cout << "No" << endl;
    return ;
}
```



---

