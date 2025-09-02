# Rollbacks (Easy Version)

## 题目描述

这是该问题的简单版本。唯一的区别在于，你需要在在线模式下解决困难版本。只有当你同时解决了两个版本的问题时，才能进行 hack。

你有一个初始为空的数组 $a$。你需要处理以下几种类型的操作：

- ```+ x``` —— 将整数 $x$ 添加到数组 $a$ 的末尾。
- ```- k``` —— 从数组 $a$ 的末尾移除最后 $k$ 个数。
- ```!``` —— 撤销上一次有效的更改（即使数组 $a$ 恢复到更改前的状态）。在本题中，只有前两种类型（+ 和 -）的操作被视为更改。
- ```?``` —— 查询当前数组 $a$ 中不同数字的个数。

## 说明/提示

在第一个样例中，数组 $a$ 的变化如下：

1. 第一次操作后，$a=[1]$。
2. 第二次操作后，$a=[1,2]$。
3. 第三次操作后，$a=[1,2,2]$。
4. 第四次操作时，数组 $a$ 中有 $2$ 个不同的整数：$1$ 和 $2$。
5. 第五次操作后，$a=[1,2]$（撤销了 +2 的更改）。
6. 第六次操作后，$a=[1,2,3]$。
7. 第七次操作后，$a=[1]$。
8. 第八次操作时，数组 $a$ 中只有一个 $1$。
9. 第九次操作后，$a=[1,1]$。
10. 第十次操作时，数组 $a$ 中只有两个 $1$。

在第二个样例中，数组 $a$ 的变化如下：

1. 第一次操作后，$a=[1]$。
2. 第二次操作后，$a=[1,1\,000\,000]$。
3. 第三次操作时，数组 $a$ 中有 $2$ 个不同的整数：$1$ 和 $1\,000\,000$。
4. 第四次操作后，$a=[1]$（撤销了 +1000000 的更改）。
5. 第五次操作后，$a=[]$（撤销了 +1 的更改）。
6. 第六次操作时，数组 $a$ 中没有整数，因此答案为 $0$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
10
+ 1
+ 2
+ 2
?
!
+ 3
- 2
?
+ 1
?```

### 输出

```
2
1
1```

## 样例 #2

### 输入

```
6
+ 1
+ 1000000
?
!
!
?```

### 输出

```
2
0```

# 题解

## 作者：Hisaishi_Kanade (赞：6)

对于 ez version，我们发现可以使用建操作树来解决。

具体地，设 $F_i$ 表示操作 $i$ 后的序列，$f(i,k)$ 表示树上 $i$ 的 $2^k$ 级祖先。我们维护一个 $p$ 指针表示目前维护的序列长度。

+ 对于 `+` 操作，直接将 $f(i,0)$ 设为 $p$，因为显然是在 $p+1$ 这个位置添加 $x$。然后简单的维护 $f(i,k)$。
+ 对于 `-` 操作，由于我们已经维护了这个倍增的东西，我们直接用 $\log$ 的复杂度向前跳，跳到 $x$ 个之前。
+ 对于撤销操作，我们维护一下 `+` 和 `-` 操作的一个栈和操作 $i$ 结束后的 $p$，这样可以快速回溯到上一个 `+` 和 `-` 操作之前。
+ 对于查询操作，我们发现加减一个数字可以 $O(1)$ 维护数字种类的（类似莫队的 `void del(int x)` 和 `void add(int x)`）。

```cpp
#include <bits/stdc++.h>
#define clr() fflush(stdout);
#define rep(i, l, r) for(i=l; i<=r; ++i)
#define req(i, r, l) for(i=r; i>=l; --i)
using namespace std;
const int K=25, N=1e6+5;
//#define int long long
int ret;
vector<int> e[N]; char op[N];
int cnt[N], ans[N], v[N], x[N], f[N][K], pos[N];
int Q, cq, jmp, i, k;
inline void add(int id) {if(!cnt[id]) ++ret; ++cnt[id]; return ;}
inline void del(int id) { --cnt[id]; if(!cnt[id]) --ret; }
inline void dfs(int id)
{
    if(id) add(v[id]);
    ans[id]=ret;
    for(auto nxt : e[id]) dfs(nxt); del(v[id]);
    return ;
}
stack<int> q;
signed main()
{
    scanf("%d", &Q);
    rep(i, 1, Q)
    {
        scanf(" %c", op+i);
        if(op[i]=='+')
        {
            scanf("%d", x+i);
            f[++cq][0]=jmp;
            rep(k, 1, 21) f[cq][k]=f[f[cq][k-1]][k-1];
            jmp=cq;
            v[cq]=x[i]; q.push(i);
        }else if(op[i]=='-')
        {
            scanf("%d", x+i);
            rep(k, 0, 21) if(x[i]&(1<<k)) jmp=f[jmp][k];
            q.push(i);
        }
        else if(op[i]=='!') jmp=pos[q.top()-1], q.pop();
        pos[i]=jmp;
//      puts("ok");
    }
    rep(i, 1, cq) e[f[i][0]].emplace_back(i);
    dfs(0);
    rep(i, 1, Q) if(op[i]=='?') printf("%d\n", ans[pos[i]]);
    return 0;
}
```

对于 hard version，我们发现 ez version 写的完全不适用了，因为我们是离线下来做才能保证复杂度的。

我们重新思考一下怎么做这个题，对于一个序列其颜色种类数等价于问有多少个数在这个序列中**第一次出现**。我们发现这个东西是可以维护的。

还记得刚刚的 $p$ 吗？这个东西现在依然很有用。

+ 对于 `+` 操作，我们直接在末尾 $p+1$ 处加上一个数。如果他是第一次出现则计数器加一。
+ 但是我们只是这样维护计数器会发现删除这样的操作很难实现，思考，会发现不如我们利用 `p` 实现**一种“假”删除**，考虑后面的查询操作，本质相当于问 $a_1, a_2, \cdots, a_p$ 这些数中第一次出现的数的个数。所以删除操作直接 $p\gets p-x$。为了方便查询，我们将计数器加一改为在 $p+1$ 的位置加一，查询也变成求前缀和。
+ 对于回溯操作，还是直接动 $p$，然后类似 ez version 的维护一个栈即可。
+ 对于查询操作，我们发现目前只需要解决两个问题：如何知道这个数是不是第一次出现？如何快速求前缀和？我们对每个数维护一个 `std::set` 记录其出现的情况，前缀和则直接树状数组解决就好了。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e6+5, Pn=1e6;
int tr[N], a[N]; int ret;
int n, Q, i, j, cnt, x;
int lsq[N], lsp[N], lsv[N]; char lsop[N];
inline void add(int x, int k)
{ while (x<=Pn) tr[x]+=k, x+=x&-x; return ;}
inline int ask(int x)
{ ret=0; while (x) ret+=tr[x], x-=x&-x; return ret;}
set<int> q[N]; char op;
inline void chg(int pos, int nxt)
{
    if(!q[a[pos]].empty())
    {
        add(*q[a[pos]].begin(), -1);
        q[a[pos]].erase(pos);
        if(!q[a[pos]].empty()) add(*q[a[pos]].begin(), 1);
    }
    if(!q[nxt].empty()) add(*q[nxt].begin(), -1);
    a[pos]=nxt; q[nxt].insert(pos);
    add(*q[nxt].begin(), 1);
}
int main()
{   int q=0;
    scanf("%d", &Q); while(Q--)
    {
        scanf(" %c", &op);
        if(op=='!') 
        {
            q=lsq[cnt];
            if(lsop[cnt]=='+') chg(lsp[cnt], lsv[cnt]);
            --cnt;
        }else if(op=='?') printf("%d\n", ask(q)), fflush(stdout);
        else if(op=='+')
        {
            scanf("%d", &x);
            ++cnt; lsq[cnt]=q; lsop[cnt]='+'; lsp[cnt]=q+1; lsv[cnt]=a[q+1]; ++q;
            chg(q, x);
        }else
        {
            scanf("%d", &x);
            ++cnt; lsq[cnt]=q; lsop[cnt]='-';
            q-=x;
        }
//      printf("%d\n", q);
//      for(int i=1;i<=q;++i) printf("%d\n", a[i]);
//      puts("");
    }
    return 0;
}
```



---

## 作者：zhicheng (赞：2)

### 思路

~~直接把E2题解搬过来~~

看到有加数，减数，回滚，不同数字个数，加强版要求在线，马上想到可持久化权值线段树。因为回滚不会回滚之前的回滚操作而只会回滚加减，因此我们要维护一个数组存储所有的加减操作，每次回滚从后面弹掉一个。我们还要维护每个状态时数列的长度 $len$，每次删除时回到最后的一个长度为 $len-k$ 的状态，回滚时删除现在这个 $len$ 的状态。

然鹅直接交会喜提 MLE，考虑优化。因为没有区间查询不同数字个数，所以只需每个版本记录一下不同数字个数即可。每次加入新的数也只需用到叶子结点是否有值这个信息，所以也可以用一个 `map` 记录。然后就可以 AC 了。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int now,rt[1000010],cnt,len[1000010],g[1000010],ans[1000010];
vector<int>f[1000010];  //每个len的编号集
map<int,bool>mapp;
struct ss{
	int l,r;  //结构体只用开左右儿子
}tr[21000000];
void update(int &i,int j,int l,int r,int c){
	int mid=(l+r)>>1;
	i=++cnt;
	tr[i]=tr[j];
	if(l==r){
		if(mapp[i]==0&&mapp[j]==0){
			ans[now]++;  //用map判断是否有值
		}
		mapp[i]=1;
		return;
	}
	if(c<=mid){
		update(tr[i].l,tr[j].l,l,mid,c);
	}
	else{
		update(tr[i].r,tr[j].r,mid+1,r,c);
	}
}
int main(){
	ios::sync_with_stdio(0);
	int n,m,las=0;
	char c;
	cin>>n;
	f[0].push_back(0);  //最先len=0
	for(int i=1;i<=n;i++){
		cin>>c;
		if(c=='+'){
			cin>>m;
			now++;
			ans[now]=ans[now-1];  //先复制再更新
			update(rt[now],rt[now-1],1,1e6,m);
			len[now]=len[now-1]+1;
			f[len[now]].push_back(now);
			g[++las]=now;  //记录
		}
		else if(c=='-'){
			cin>>m;
			++now;
			len[now]=len[g[las]]-m;
			ans[now]=ans[f[len[now]].back()];  //找到继承对象
			rt[now]=rt[f[len[now]].back()];
			f[len[now]].push_back(now);
			g[++las]=now;
		}
		else if(c=='!'){
			++now;
			f[len[g[las]]].erase(f[len[g[las]]].end()-1);  //删除
			las--;
			ans[now]=ans[g[las]];
			len[now]=len[g[las]];
			rt[now]=rt[g[las]];  //继承，注意回滚不用记录len
		}
		else{
			cout<<ans[now]<<"\n";
		}
	}
}
```

---

## 作者：Xy_top (赞：1)

赛时没做出来，晚上补了一下，发现是一种很好玩的 数据结构。

由于可以离线又要支持删除后 $k$ 个又要支持撤销操作，不会写主席树只能选择操作树。

对序列按照时间建成一颗操作树，处于某个点的回合时，这个序列的样子就是它以及它的祖先。

来依次考虑某个操作，设当前是序列的末尾是 $p$ 号元素。

加操作，直接在 $p$ 下面挂一个儿子，然后 $p$ 变成它即可。

减操作，此时我们发现需要跳 $k$ 级祖先，就需要倍增了，这个操作于是解决。

撤销操作，其实可以实时记录加减操作的一个栈，这个时候把栈顶弹出，把 $p$ 变成现在的栈顶即可。

询问操作，留到最后建完表达式树再做。

我们发现询问就是问每个点向上构成的序列中的元素个数，可以用类似莫队的方法解决，但是这一部分是 $O(n)$ 的，于是就过了，代码：

```cpp
#include <bits/stdc++.h>
#define For(i, a, b) for (int i = (a); i <= (b); i ++)
#define foR(i, a, b) for (int i = (a); i >= (b); i --)
using namespace std;
stack <int> st;
int p, q, x, cnt, res;
int f[1000005][20], val[1000005];
int b[1000005], ans[1000005], pos[1000005];
char op[1000005];
vector <int> G[1000005];
void add (int x) {
	b[x] ++;
	if (b[x] == 1) ++ res;
}
void rem (int x) {
	b[x] --;
	if (b[x] == 0) -- res;
}
void dfs (int u) {
	if (u) add (val[u]);
	ans[u] = res;
	for (int v : G[u]) dfs (v);
	if (u) rem (val[u]);
}
signed main () {
	st.push (0);
	scanf ("%d", &q);
	For (i, 1, q) {
		op[i] = getchar ();
		while (op[i] == ' ' || op[i] == '\n') op[i] = getchar ();
		if (op[i] == '+') {
			scanf ("%d", &x);
			f[++ cnt][0] = p;
			val[cnt] = x;
			For (j, 1, 20) f[cnt][j] = f[f[cnt][j - 1] ][j - 1];
			p = cnt;
		} else if (op[i] == '-') {
			scanf ("%d", &x);
			foR (j, 20, 0) {
				if (x >= (1 << j) ) {
					x -= (1 << j);
					p = f[p][j];
				}
			}
		} else if (op[i] == '!') {
			st.pop ();
			p = st.top ();
		}
		pos[i] = p;
		if (op[i] != '?' && op[i] != '!') st.push (p);
	}
	For (i, 1, cnt) G[f[i][0] ].push_back (i);
	dfs (0);
	For (i, 1, q) if (op[i] == '?') cout << ans[pos[i] ] << '\n';
	return 0;
}
```


---

## 作者：Unnamed114514 (赞：1)

赛时做出来的 \*2500，记录一下。

我们可以考虑建出每个操作的决策树，考虑记录一下当前的节点 $now$，最开始的时候只有一个根节点 $0$。

- 插入

直接给 $now$ 加一条边，指向一个新的节点，边权表示加入这个数。

- 删除

那么相当于撤销 $k$ 次插入操作，那么我们直接跑 $now$ 的 $k$ 级祖先即可，这里需要动态插入节点，所以可以用倍增来维护。

- 查询

显然，我们查询的是 $now$ 到 $0$ 的不同边权的数量，这个东西我们可以离线下来最后一次 dfs 即可。

- 撤销

考虑记录一下 $now$ 的变化，很显然这里需要的是上一次的 $now'$，因为满足栈后进先出的性质，所以直接用 `std::stack` 维护即可。

最后再来说下离线怎么处理吧：我们可以记录在每个节点上的询问，我们令每个边权 $x$ 是否出现记作 $vis_x$，那么因为 dfs 是可以回溯的，所以我们可以知道，我们到达节点 $u$ 的时候，本质上，$vis$ 中只有 $u$ 到 $0$ 的所有边，那么我们直接考虑查询即可，记答案为 $ans$。

此时呢假设我们是这样一条边：$(u,v,w)$，那么就是从 $u$ 转移到 $v$，由于如上的性质，显然 $u$ 中只有 $u$ 到 $0$ 的边，那么我们插入 $w$ 的时候，若 $vis_w=1$，那么此时 $(u,v,w)$ 这条边对答案无影响，$ans$ 不变；否则就多了一条边权为 $w$ 的边，$ans\gets ans+1$。

回溯的时候呢，如果原来的 $vis_w=1$，那么很显然 $(u,v,w)$ 并不影响答案，所以不变；否则 $vis_w=0,ans\gets ans-1$。

***

代码中用的 $cnt_w$ 表示 $w$ 的出现次数，那么就在插入前若 $cnt_w=0$，$ans\gets ans+1$；若删除后 $cnt_w=0,ans\gets ans-1$。$cnt$ 就像正常的桶一样加加减减即可，实现起来是要比 $vis$ 方便一点。

[分享一下赛时的丑陋代码](https://codeforces.com/contest/1858/submission/218976114)

---

