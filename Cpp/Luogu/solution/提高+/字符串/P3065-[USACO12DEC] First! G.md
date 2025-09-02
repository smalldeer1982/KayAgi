# [USACO12DEC] First! G

## 题目描述

Bessie has been playing with strings again. She found that by changing the order of the alphabet she could make some strings come before all the others lexicographically (dictionary ordering).

For instance Bessie found that for the strings "omm", "moo", "mom", and "ommnom" she could make "mom" appear first using the standard alphabet and that she could make "omm" appear first using the alphabet

"abcdefghijklonmpqrstuvwxyz".  However, Bessie couldn't figure out any way to make "moo" or "ommnom" appear first.

Help Bessie by computing which strings in the input could be lexicographically first by rearranging the order of the alphabet.  To compute if string X is lexicographically before string Y find the index of the first character in which they differ, j.  If no such index exists then X is lexicographically before Y if X is shorter than Y.  Otherwise X is lexicographically before Y if X[j] occurs earlier in the alphabet than Y[j].

Bessie 一直在研究字符串。她发现，通过改变字母表的顺序，她可以按改变后的字母表来排列字符串（字典序大小排列）。

例如，Bessie 发现，对于字符串 $\texttt{omm},\texttt{moo},\texttt{mom}$ 和 $\texttt{ommnom}$，她可以使用标准字母表使 $\texttt{mom}$ 排在第一个（即字典序最小），她也可以使用字母表 $\texttt{abcdefghijklonmpqrstuvwxyz}$ 使得 $\texttt{omm}$ 排在第一个。然而，Bessie 想不出任何方法（改变字母表顺序）使得 $\texttt{moo}$ 或 $\texttt{ommnom}$ 排在第一个。

接下来让我们通过重新排列字母表的顺序来计算输入中有哪些字符串可以排在第一个（即字典序最小），从而帮助 Bessie。

要计算字符串 $X$ 和字符串 $Y$ 按照重新排列过的字母表顺序来排列的顺序，先找到它们第一个不同的字母 $X_i$ 与 $Y_i$，按重排后的字母表顺序比较，若 $X_i$ 比 $Y_i$ 先，则 $X$ 的字典序比 $Y$ 小，即 $X$ 排在 $Y$ 前；若没有不同的字母，则比较 $X$ 与 $Y$ 长度，若 $X$ 比 $Y$ 短，则 $X$ 的字典序比 $Y$ 小，即 $X$ 排在 $Y$ 前。

## 说明/提示

The example from the problem statement.

Only "omm" and "mom" can be ordered first.

样例即题目描述中给出的例子，只有 $\texttt{omm}$ 和 $\texttt{mom}$ 在各自特定的字典序下可以被排列在第一个。

## 样例 #1

### 输入

```
4
omm
moo
mom
ommnom
```

### 输出

```
2
omm
mom
```

# 题解

## 作者：Heartlessly (赞：31)

## Description

给定 $n\ (1 \leq n \leq 3 \times 10^4)$ 个总长不超过 $m\ (1 \leq m \leq 3 \times 10^5)$ 的互不相同的字符串，现在你可以任意指定字符之间的大小关系。问有多少个串可能成为字典序最小的串，并输出这些串。

## Solution

看到与字典序有关的问题，很容易想到建一棵 **Trie(字典树)** 。

对于每一个字符串，我们可以设它的字典序是所有字符串中最小的。

也就是说，这个字符串的第 $i$ 个字母 在 **Trie** 的第 $i$ 层（根节点算第 $0$ 层）的所有字母中 字典序最小。

设这个字符串的第 $i$ 个字母为 $u$，我们可以连单向边 $u \to v$，表示我们指定了 $u$ 的字典序比 $v$ 小，其中 $v$ 是第 $i$ 层的其它字母。若这个字符串是其它某个字符串的前缀，则这个字符串不可能成为字典序最小的串，比如说 $abba$ 的字典序一定比 $ab$ 大。当 $26$ 个字母间的关系形成环时，也一定不能成为字典序最小的串。

怎么判断是否形成环呢？可以用 $\rm tarjan$ 或者 **拓扑排序** 。

这里我采用了 **拓扑排序**  。我们从入度为 $0$ 的点开始，不断删去与它相连的边，并修改其它点的入度，将新的入度为 $0$ 的点加入队列。若队列已空，但还存在入度不为 $0$ 的点，则说明图存在环，反之则有解。

时间复杂度为 $O(26m)$ 。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

template <class T>
inline void read(T &x) {
    x = 0;
    char c = getchar();
    bool f = 0;
    for (; !isdigit(c); c = getchar()) f ^= c == '-';
    for (; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
    x = f ? -x : x;
}

template <class T>
inline void write(T x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    T y = 1;
    int len = 1;
    for (; y <= x / 10; y *= 10) ++len;
    for (; len; --len, x %= y, y /= 10) putchar(x / y + 48);
}

const int MAXN = 3e4, MAXM = 3e5;
int n, ans;
string s[MAXN + 5];
bool ok[MAXN + 5];
struct Trie {
    int tot, in[26], e[26][26], ch[MAXM + 5][26];
    bool ed[MAXM + 5];
    queue<int> q;
    
    inline void insert(string x) {
        int u = 1, len = x.size();
        for (int i = 0; i < len; ++i) {
            int v = x[i] - 'a';
            if (!ch[u][v]) ch[u][v] = ++tot;
            u = ch[u][v];
        }
        ed[u] = 1;
    }//插入 
    inline void topoSort() {
        for (; !q.empty(); q.pop());
        for (int i = 0; i < 26; ++i)
            if (!in[i]) q.push(i);
        for (; !q.empty(); ) {
            int u = q.front();
            q.pop();
            for (int v = 0; v < 26; ++v)
                if (e[u][v]) {
                    --in[v];
                    if (!in[v]) q.push(v);
                }
        }
    }//拓扑排序 
    inline bool find(string x) {
        int u = 1, len = x.size();
        memset(e, 0, sizeof (e));
        memset(in, 0, sizeof (in));
        for (int i = 0; i < len; ++i) {
            if (ed[u]) return 0;//是其它字符串的前缀，无解
            int v = x[i] - 'a';
            for (int j = 0; j < 26; ++j)
                if (v != j && ch[u][j] && !e[v][j]) {
                    e[v][j] = 1;//与同一层其它字母连边 
                    ++in[j];//统计入度 
                }
            u = ch[u][v];
        }
        topoSort();
        for (int i = 0; i < 26; ++i)
            if (in[i]) return 0;//存在环，无解 
        return 1;
    }//检验字符串 
} tr;

int main() {
    read(n);
    tr.tot = 1;
    for (int i = 1; i <= n; ++i) {
        cin >> s[i];
        tr.insert(s[i]);//插入到 Trie 中 
    }
    for (int i = 1; i <= n; ++i)
        if (tr.find(s[i])) {
            ++ans;//统计个数 
            ok[i] = 1;//标记合法字符串 
        }
    write(ans);
    putchar('\n');
    for (int i = 1; i <= n; ++i)
        if (ok[i]) cout << s[i] << '\n';
    return 0;
}
```



---

## 作者：littleming (赞：17)

拿到rk1了(\*￣▽)u┌┐ｄ(▽￣\*)

trie树+拓扑排序

很裸
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
int n;
string s[30008];
int ch[300008][28],num,ind[28];
bool vis[300008],used[28][28],f;
int ans[30008],num_ans;
int nume,head[28],to[908],nxt[908];
deque<int> q;
inline void addedge(int x,int y)
{
    ++nume;to[nume]=y;nxt[nume]=head[x];head[x]=nume;
}
inline void update(string x)
{
    int u=0,t;
    for(int i=0;i<x.size();i++){
        t=x[i]-'a';
        if(!ch[u][t]){
            ch[u][t]=++num;
        }
        u=ch[u][t];
    }
    vis[u]=1;
}
inline void solve(string x)
{
    int u=0,t;
    for(int i=0;i<x.size();i++){
        t=x[i]-'a';
        if(vis[u]){
            f=1;
            return;
        }
        for(int j=0;j<26;j++){
            if(ch[u][j]&&j!=t&&!used[t][j]){
                used[t][j]=1;
                addedge(t,j);
                ind[j]++;
            }
        }
        u=ch[u][t];
    }
}
inline bool ok()
{
    for(int i=0;i<26;i++){
        if(!ind[i])    q.push_back(i);
    }
    while(!q.empty()){
        int now=q.front();q.pop_front();
        for(int i=head[now];i;i=nxt[i]){
            ind[to[i]]--;
            if(!ind[to[i]]){
                q.push_back(to[i]);
            }
        }
    }
    for(int i=0;i<26;i++){
        if(ind[i]){
            return 0;
        }
    }
    return 1;
}
int main()
{
    ios::sync_with_stdio(false);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>s[i];
        update(s[i]);
    }
    for(int i=1;i<=n;i++){
        nume=0;
        q.clear();
        f=0;
        memset(head,0,sizeof(head));
        memset(ind,0,sizeof(ind));
        memset(used,0,sizeof(used));
        solve(s[i]);
        if(f)    continue;
        if(ok())    ans[++num_ans]=i;
    }
    printf("%d\n",num_ans);
    for(int i=1;i<=num_ans;i++){
        printf("%s\n",s[ans[i]].c_str());
    }
    return 0;
}
```

---

## 作者：liuxu (赞：9)

原文在此 https://www.jianshu.com/p/6fb17406b66d[](https://www.jianshu.com/p/6fb17406b66d) 原文有图，luogu不会插图。。。。

因为涉及到字典序的问题，那么应该能想到字典树。很显然字符串s1如果比字符串s2的字典序小的话，只有两种情况，s1是s2的前缀；以及他们有相同的前缀单在相同前缀后面的部分那一部分s1的优先级更大；

所以将所以字符串建成一棵字典树，然后再在字典树上遍历每一串字符串，如果有字符串已经是他的前缀，无论怎么改变26个字母的排列也无济于事，否则判断优先级，及上一段所说的情况二； 判断优先级有个很巧的办法---->


如图手画的十分丑陋不要介意哈

字符串s1 为 mma
字符串s2 为 mmb

现在要使mmb的优先级大于mma的优先级，那如何判断通过26个字母的变换后mmb能否优先于mma呢，应该一眼看出把a，b交换位置后s2的字典序就小于s1了，那么接下来就是要找到一种证明的方法；

他们都有相同的mm前缀，那么要使s2的优先级大，就要使b的优先级大，及相同前缀后面部分的优先级大，跟之前所说的一样。

设计到优先级的问题我们绞尽脑汁后应该能想到一个叫拓扑序的神奇的东西，那么再上一张丑图hh


构造这样的图，此时a，b在拓扑排序后的顺序是在同一层的，所以可以瞎把a，b交换位置都可以，故可以将a，b交换位置使得s2的优先级大于s1；

再来一个反例加深理解


无法构成拓扑序，因为a，b无论怎么交换位置，mmab都在mmba前面

应该很清楚了吧！！

如果还不理解建议自己多画几个，一定要勇于动手！！

下面上代码喽！！
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<string>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;
struct Node{
	int son[27],end;
}N[300010];
vector<int> E[27];
int n,cnt=1,ind[30010],ans_sum,used[27][27];
string ans[30010],s[30010];
void insert(string s){
	int now=1;
	for(int i=0;i<s.length();i++){
		if(!N[now].son[s[i]-'a']) N[now].son[s[i]-'a']=++cnt;
		now=N[now].son[s[i]-'a'];
	}
	N[now].end++;
}
int work(string s){
	int now=1;
	for(int i=0;i<s.length();i++){
		int t=s[i]-'a';
		if(N[now].end) return 0;
		for(int j=0;j<26;j++){
			if(N[now].son[j]&&t!=j){
				E[t].push_back(j);
				ind[j]++;
			}
		}
		now=N[now].son[t];
	}
	return 1;
}
int check(){
	queue<int> q;
	for(int i=0;i<26;i++) if(!ind[i]) q.push(i);
	while(!q.empty()){
		int u=q.front(); q.pop();
		for(int i=0;i<E[u].size();i++){
			ind[E[u][i]]--;
			if(!ind[E[u][i]]) q.push(E[u][i]);
		}
	}
	for(int i=0;i<26;i++) if(ind[i]) return 0;
	return 1;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		cin>>s[i];
		insert(s[i]);//建字典树 
	}
	for(int i=1;i<=n;i++){
		memset(used,0,sizeof(used));
		memset(ind,0,sizeof(ind));
		for(int j=0;j<27;j++) E[j].clear(); 
		if(!work(s[i])) continue;//如果有人是它的前缀返回0，直接不干了，如果没有，顺便建好图，准备接下来拓扑排序 
		if(check()) ans[++ans_sum]=s[i];//如果符合拓扑序 记录答案 
 	}
 	printf("%d\n",ans_sum);
 	for(int i=1;i<=ans_sum;i++) cout<<ans[i]<<endl; 
	return 0;
}
```

---

## 作者：Daidly (赞：7)

一种不同的方法。

- 如何求一棵字典树上的最小字符串？

从上往下，对于每一位都取当前字典序中可取到的最小的字母。如果遍历到一个字符串的末尾标记，就返回即可求得。

- 考虑一种正确但复杂度较高的做法：

先把每个字符串插入到字典树中。

对于一个字符串 $s$，想要判断它是否能够通过改变字典序变成最小字符串，我们可以枚举字典序，然后在字典树中查询字典序最小的字符串，看是否等于 $s$。但是，显然这是 $O(26!\times 26n)$ 的，不可能通过。

- 我们考虑不进行枚举，直接赋值：

对于一个字符串 $s$，将它的每个字母按照先后顺序分别标上优先级，相同字符以靠前的优先级为标准。

然后从根节点开始搜在字典树上的最小字符串，判断是否等于 $s$。复杂度 $O(26n)$。

- 但是，虽然复杂度优化了那么多，但正确性能保证吗？

此做法能得到 48 分：https://www.luogu.com.cn/record/83708604 ，连 #2 中 $n=30000,ans=30000$ 都能过。

考虑字符串 $\texttt{cjjk}$ 和 $\texttt{cjkk}$，我们想让 $\texttt{cjkk}$ 成为字典序最小的字符串，定义 $c=0,j=1,k=2$ 其他都等于 $26$ ，但是这样的赋值方法并不能使其比 $\texttt{cjjk}$ 大，我们遗漏了一些正确的项，所以我们考虑一种调整方法。

![](https://cdn.luogu.com.cn/upload/image_hosting/y72e0gts.png)

- 若当前节点字典序最小的子节点和 $s$ 上该位的字符不一样，我们将这两个字符的优先级交换。重新从根节点跑一遍。

对于上图 $j,k$ 冲突，我们将 $j,k$ 的优先级交换为 $j=2,k=1$。

可以发现，若 $j<k$，那么 $j$ 一定在 $s$ 中 $k$ 出现之前出现过，也就是相当于改变了 $s$ 中 $k$ 前字符的优先级。

而如此重复，若 $s$ 是正确的项，即可以变成字典序最小的字符串，则一定能在有限次数内重置 $s$ 中 $k$ 及之前的字符优先级使得此前缀是最小的，然后可以继续向下求解。次数的上限可以考虑以 $k$ 结尾的 $s$ 前缀中不同字符个数为 $K,K\leq 26$，对于任意一个字符最多交换 $K-1$ 次，上限一定小于 $K(K-1)=650$，但实际次数远小于此。

如果有同学能求出极为精确的交换次数，可以在评论区留言哦（

所以，我们记录一个字符串在求解过程中交换的次数 $P$，并在时间允许范围内进行判断是否能变成最小字符串。时间复杂度最高为 $O(26nP)$。

$P>30$ 时判定为不可能，可以获得 $91$ 分的高分：https://www.luogu.com.cn/record/83712651

$P>50$ 时判定为不可能，可以获得 $100$ 分的高分：https://www.luogu.com.cn/record/83712776

此时最慢一个点用时为 172ms。此时已经能过掉绝大部分随机或构造的数据。

$P>100$ 时判定为不可能，可以获得 $100$ 分的高分：https://www.luogu.com.cn/record/83714408

此时最慢一个点用时为 285ms。

$P>400$ 时判定为不可能，可以获得 $100$ 分的高分：https://www.luogu.com.cn/record/83714750

此时最慢一个点用时为 998ms，已经接近 TLE 的边缘，但此代码几乎不可能卡掉（我也拍了一中午没卡掉）。因为 $P=400$ 在几乎任何数据下都已经超过交换次数的上限（还是那句话，如果有同学能求出极为精确的交换次数，一定要在评论区留言哦！）

- 这是一个根据交换次数而定的具有正确性的方法。

完结撒花！

---

## 作者：wanghanjun (赞：7)

先考虑一个字符串（不妨设其为aaba）在什么排序下会排在第一个

- 不能有任何字符串是他的前缀（例如aa是，ba不是）。

- 对于每个其他字符串（如abcd），找到与原字符串第一个不同的字母，这里是第二位a和b不同，所以a要排在b前面，以此类推，如果出现这样的一个循环（如a在b前,b在a前），则该字符串不能排在第一个，否则可以。

判断前缀可以用trie，判断循环可以用拓扑排序

然后就是代码了：
```cpp
#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
#include <string.h>
using namespace std;

const int MAXN=300005;
struct trie{
	int next[27];
	int rank;
}t[MAXN];
int h[27][27],a[27],cnt=1,tot=0,n,ans=0;
string p[MAXN];
char s[MAXN];
bool c[MAXN];
queue <int> q;

void addtrie(int r){
	int id=1;
	for(int i=0;s[i];i++){
		if(!t[id].next[s[i]-96]){
			cnt++;
			t[id].next[s[i]-96]=cnt;
		}
		id=t[id].next[s[i]-96];
	}
	t[id].rank=r;
}


void dfs1(int d,int id){
	if(!s[d]){
		return;
	}
	for(int i=1;i<=26;i++){
		if(t[id].next[i]){
			if(i!=s[d]-96){
				h[s[d]-96][i]=1;
			}
			else{
				dfs1(d+1,t[id].next[i]);
			}
		}
	}
}

bool check(){
	int res=26;
	memset(h,0,sizeof(h));
	memset(a,0,sizeof(a));
	while(!q.empty()) q.pop();
	tot++;
	dfs1(0,1);
	for(int i=1;i<=26;i++){
		for(int j=1;j<=26;j++){
			if(h[i][j]){
				a[j]++;
			}
		}
	}
	for(int i=1;i<=26;i++){
		if(!a[i]){
			q.push(i);
		}
	}
	while(!q.empty()){
		int u=q.front();q.pop();
		res--;
		for(int i=1;i<=26;i++){
			if(h[u][i]){
				a[i]--;
				h[u][i]=0;
				if(a[i]==0){
					q.push(i);
				}
			}
		}
	}
	return res==0;
}

void dfs2(int d,int id){
	if(t[id].rank){
		if(check()){
			ans++;
			c[t[id].rank]=1;
		}
		return;
	}
	for(int i=1;i<=26;i++){
		if(t[id].next[i]){
			s[d]=i+96;
			dfs2(d+1,t[id].next[i]);
			s[d]=0;
		}
	}
}

int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		scanf("%s",s);
		p[i]=s;
		addtrie(i);
	}
	memset(s,0,sizeof(s));
	dfs2(0,1);
	cout<<ans<<endl;
	for(int i=1;i<=n;i++){
		if(c[i]){
			cout<<p[i]<<endl;
		}
	}
	return 0;
}
```


---

## 作者：cghAndy (赞：4)

一A啊 开心O(∩\_∩)O~~

如果一个字符串想要是字典序最小 首先没有别的串是他的前缀

然后 对于有共同前缀的 其他的下一个字母的优先级一定要比此串下一个字母后

上面的过程就用trie树来搞定√

所以连一条边拓扑排序一下 如果全部排完那就可以咯

不如大家来刷刷访问量吧~   http://blog.csdn.net/cgh\_andy/article/details/53023269


---

