# Tensor

## 题目描述

This is an interactive problem.

You are given an integer $ n $ .

The jury has hidden from you a directed graph with $ n $ vertices (numbered from $ 1 $ to $ n $ ) and some number of edges. You additionally know that:

- The graph only contains edges of the form $ i \leftarrow j $ , where $ 1 \le i < j \le n $ .
- For any three vertices $ 1 \le i < j < k \le n $ , at least one of the following holds $ ^\dagger $ : 
  - Vertex $ i $ is reachable from vertex $ j $ , or
  - Vertex $ i $ is reachable from vertex $ k $ , or
  - Vertex $ j $ is reachable from vertex $ k $ .

You want to color each vertex in either black or white such that for any two vertices $ i $ and $ j $ ( $ 1 \le i < j \le n $ ) of the same color, vertex $ i $ is reachable from vertex $ j $ .

To do that, you can ask queries of the following type:

- ? i j — is vertex $ i $ reachable from vertex $ j $ ( $ 1 \le i < j \le n $ )?

Find any valid vertex coloring of the hidden graph in at most $ 2 \cdot n $ queries. It can be proven that such a coloring always exists.

Note that the grader is not adaptive: the graph is fixed before any queries are made.

 $ ^\dagger $ Vertex $ a $ is reachable from vertex $ b $ if there exists a [path](https://en.wikipedia.org/wiki/Path_(graph_theory)) from vertex $ b $ to vertex $ a $ in the graph.

## 说明/提示

The hidden graph in the first test case:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1977E/d9f22ee8ab749a5ad0bef404d190145b53c9cc18.png)The hidden graph in the second test case:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1977E/eba30883018cd14dec28ecbab62d3af607fa7b41.png)The interaction happens as follows:

SolutionJuryExplanation2There are $ 2 $ test cases.4In the first test case, the graph has $ 4 $ vertices.? 1 2 YESThe solution asks if vertex $ 1 $ is reachable from vertex $ 2 $ , and the jury answers YES.? 2 3 YESThe solution asks if vertex $ 2 $ is reachable from vertex $ 3 $ , and the jury answers YES.? 1 3 YESThe solution asks if vertex $ 1 $ is reachable from vertex $ 3 $ , and the jury answers YES.? 1 4 NOThe solution asks if vertex $ 1 $ is reachable from vertex $ 4 $ , and the jury answers NO.? 2 4 NOThe solution asks if vertex $ 2 $ is reachable from vertex $ 4 $ , and the jury answers NO.? 3 4 NOThe solution asks if vertex $ 3 $ is reachable from vertex $ 4 $ , and the jury answers NO.! 0 0 0 1The solution has somehow determined a valid coloring and outputs it. Since the output is correct, the jury continues to the next test case.5In the second test case, the graph has $ 5 $ vertices.! 1 1 0 1 0The solution has somehow determined a valid coloring, and outputs it. Since the output is correct and there are no more test cases, the jury and the solution exit.Note that the line breaks in the example input and output are for the sake of clarity, and do not occur in the real interaction.

## 样例 #1

### 输入

```
2
4

YES

YES

YES

NO

NO

NO

5```

### 输出

```
? 1 2

? 2 3

? 1 3

? 1 4

? 2 4

? 3 4

! 0 0 0 1

! 1 1 0 1 0```

# 题解

## 作者：sunkuangzheng (赞：6)

笑点解析：

![](https://cdn.luogu.com.cn/upload/image_hosting/8moxg6wt.png)

--- 

显然图的形态只有两种可能：

- 弱连通。
- 两条不连通的链，可能有额外边。

第二种情况由于图是 dag 非常好做。

考虑第一种情况，我们对图拓扑排序后一层最多有 2 个点，那么原图可以用两条链覆盖，现在我们需要找到它们。

我们首先找到两条链的链头，钦定第一条链链头是 $1$，容易找到第一个分叉，可以找到第二条链头 $y$，此时第一条链尾是 $x = y - 1$。

考虑依次加入 $x+1,\ldots,n$，有一个很 naive 的思路是对于点 $i$ 如果 $x$ 能到 $i$ 就加入第一条链，否则第二条。但是会被以下图卡掉：$1 \to 3,2 \to 3,1 \to 4$。此时如果你将点 $3$ 划给链 $1$ 则 $2$ 号点和 $4$ 号点不可达。因此，我们需要额外维护**公共可达链**，记为 $3$ 号链，链尾为 $z$。（请注意，$3$ 号链是一条**链**，也不能存在分叉）

然后我们又有一个 naive 的思路：如果点 $i$ 从 $x,y$ 都可达，就加入链 $3$，否则加入到不了的点。但是考虑图 $1 \to 3,2 \to 3,3 \to 4,4 \to 5,4 \to 6$，按照这个算法得到的链 $3$ 并不是链。

问题在于我们想要知道点 $i$ 对于 $x,y,z$ 三个点的可达性，但我们只有 $2n$ 次询问机会。分讨一些情况，发现有一次询问是可以省略的：

- 如果链 $3$ 为空，则：
   - 如果 $x,y$ 只有一个点可以到 $i$，则直接划入对应的链。
   - 否则，加入链 $3$。
- 否则，
   - 如果 $z$ 可以到达 $i$，加入链 $3$。
   - 否则，
      - 如果 $x$ 可以到达 $i$，将链 $3$ 全部划入链 $2$，并将 $i$ 划入链 $1$。
      - 否则，将链 $3$ 全部划入链 $1$，并将 $i$ 划入链 $2$。
      
容易发现以上做法的询问次数不超过 $2n$，且正确性较为显然。


[赛时 AC 记录](https://codeforces.com/contest/1977/submission/262773921)。

---

## 作者：haochengw920 (赞：4)

先考虑分成两种颜色的正确性，将 `可达` 看作一种偏序关系，题目的条件就是告诉我们反链长度的最大值小于等于二。根据 [Dilworth 定理](https://en.wikipedia.org/wiki/Dilworth's_theorem) ，该偏序集能划分的最少全序集小于等于二。

再考虑怎么利用题目中的关系，考虑使用增量构造法，将两种颜色的结点存到两个栈里。容易发现，如果每一时刻这两种颜色的栈顶均 **互不可达** ，那么新加的结点一定可以连接到某一种颜色里。

根据上面的正确性证明，如果不存在某一时刻新加结点与两个栈顶均可达，即每一时刻新增结点须涂的颜色是固定的，那么构造方法一定成立。唯一要处理的是与两个栈顶都可达的 case ，因为这时候加到任意一个颜色的栈里都会破坏 `每一时刻这两种颜色的栈顶均互不可达` 这种关系。

考虑再用一个栈存下来这些结点，容易发现栈里这条链可以连接到任意颜色里去。如果某一时刻新加的结点与栈顶不可达，那把这点和这条链加入不同的颜色栈里（容易发现此时黑白栈顶是互不可达的，也就是新结点一定可以加到某一个栈里），那么就可以满足不可达关系了。

这个构造还是蛮巧妙的，要先思考增量构造法，再将题目条件转换成两者不可达则必有两者之一与第三者可达，还要处理与两个栈顶都可达的情况。具体实现上的细节看代码。

```cpp
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

const int MAXN = 1005;

int T, n, col[MAXN];
vector<int>st, st1, st2;

char s[5];
inline bool Query(int x, int y) {
	printf ("? %d %d\n", x, y);
	fflush(stdout); scanf ("%s", s);
	return s[0] == 'Y';
}
inline void Solve() {
	scanf ("%d", &n);
	st1.emplace_back(1);
	for (int i = 2; i <= n; ++ i) 
		if (st2.empty()) {
			if (Query(st1.back(), i)) st1.emplace_back(i);
			else st2.emplace_back(i); 
		} else {
			if (st.empty()) {
				bool fg1 = Query(st1.back(), i), fg2 = Query(st2.back(), i);
				if (!fg1) st2.emplace_back(i);
				else if (!fg2) st1.emplace_back(i);
				else st.push_back(i);   
			} else {
				if (Query(st.back(), i)) st.emplace_back(i);
				else if (Query(st1.back(), i)) {
					st1.emplace_back(i);
					for (int u : st) st2.emplace_back(u);
					st.clear();  
				} else {
					st2.emplace_back(i);
					for (int u : st) st1.emplace_back(u);
					st.clear();  
				}
			}
		}
	for (int x : st) st1.emplace_back(x);
	for (int x : st1) col[x] = 0;
	for (int x : st2) col[x] = 1;
	st.clear();  st1.clear(); st2.clear(); printf ("! ");
	for (int i = 1; i <= n; ++ i)
		printf ("%d ", col[i]); puts("");
	fflush(stdout);
}

signed main()
{
	scanf ("%d", &T);
	while (T --) Solve();
	return 0;
}
```

---

## 作者：yshpdyt (赞：3)

## 题意
$n$ 个节点的有向图，只存在编号大的点连向编号小的点的有向边，任意三个点之间至少有一对点之间有路径。

现在你可以使用不超过 $2n$ 次询问某两个点之间是否存在路径，交互库回答 `YES` 或 `NO`，请你将整个图染成最多两种颜色，使得同种颜色的点之间，编号大的点与编号小的点之间都存在路径。

## Sol
喵喵题，参考了官方题解。

首先证明一下两种颜色就足够了，假设最少只能有三个颜色 $A,B,C$，取三个颜色各自编号最大的点为 $a,b,c$，根据题意，$a$ 对于任意颜色 $A$ 的点存在路径，且 $a$ 到 $B$，$C$ 颜色的顶点不全有路径，$b,c$ 同理。

根据任意三个点之间至少有一对点之间有路径，则 $a,b,c$ 之间至少存在两个点之间有路径，假设在 $a,b$ 之间，$b$ 到所有颜色 $B$ 的点有路径，$a$ 到 $b$ 有路径，则 $a$ 到所有颜色 $B$ 的点有路径，与假设相矛盾，所以对于三个颜色的情况，总是能变成两个颜色的情况。对于更多颜色，同理可得。

接下来正式解题，注意到最多 $2n$ 次询问，猜测对于每个点最多询问两次，根据刚才的证明，启发我们记录一下两种颜色的编号最大点，只需要查询 $i$ 与两个最大点的关系，就能知道 $i$ 是否可以属于某种颜色，这也符合我们每次查询两次的限制。

我们记两种颜色分别为 $A,B$，编号最大点为 $a,b$，查询函数记作 $f(color,id)$，进行分类讨论，注意函数需要满足 $color<id$，否则询问不合法。

0. $a=b=0$，放入 $A$ 颜色，不查询。
1. 若 $f(a,i)=1$，放入 $A$，否则放入 $B$。

还有别的情况吗？当然，~~不然也太水了~~。

我们考虑这样的情况，$f(a,i)=f(b,i)=1$，$i$ 放到 $A$，如果存在 $j=i+1$ 使得 $f(i,j)=0$ 且 $f(b,j)=0$，那么 $j$ 就无处放了，又 $f(b,i)=1$，所以这种情况是可能的。

这种情况下，只有把 $i$ 放到 $B$ 里面才符合题意，即一定存在 $j$ 到 $a$ 的路径，证明不难： $f(a,b)=0$，$f(b,j)=0$，所以 $f(a,j)=1$ 一定成立。

由于 $f(a,i)=f(b,i)=1$ 的染色情况取决与后续点，不妨先暂时开个颜色 $C$，先不管这个点。

对于颜色 $C$ 空的情况，和之前一样判断即可，这样我们可以保证任意时刻，$f(a,b)=0$。

对于颜色 $C$ 非空的情况，若 $f(c,i)=1$，说明 $i$ 对两种颜色的各个点都有路径，情况和 $c$ 一样，继续放入 $C$ 即可。
否则，一定只能放一种颜色，$f(a,i)=1$ 放入 $A$ 即可，同时根据刚才的结论，把 $C$ 的所有元素移入 $B$ 即可，此时仍然满足 $f(a,b)=0$，或者对应为 $f(c,i)=0$。对于颜色 $B$ 是否还需再查询一次？再查询一次就变成三次了，不符合单个位置最多查两次的限制，注意到 $f(a,i)=0,f(a,b)=0$，所以 $f(b,i)=1$，也就是说 $f(a,i)=0$ 即可判断。

整理一下思路，完善分类讨论：

0. $a=b=0$，放入 $A$，不查询。
1. $a>b=0$：
 	- $f(a,i)=1$，放入 $A$。
   - $f(a,i)=0$，放入 $B$。
2. $c=0$：
 	- $f(a,i)=1$ 且 $f(b,i)=1$，放入 $C$。
 	- $f(a,i)=1$，放入 $A$。
 	- $f(b,i)=1$，放入 $B$。
3. $c>0$：
	- $f(c,i)=1$，放入 $C$。
   - $f(a,i)=1$，放入 $A$，将 $C$ 内所有元素移入 $B$。
   - $f(a,i)=0$，放入 $B$，将 $C$ 内所有元素移入 $A$。

实现上，$A$，$B$ 只需要记录编号最大的点即可，$C$ 由于需要移出染色操作，需要后进先出的数据结构，实现起来没什么难度，记得最后 $C$  非空时要拉出来随便染色。

时间复杂度 $O(n)$。

##  Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ul unsigned long long
#define N 300005
#define endl "\n" 
#define fi first
#define se second
using namespace std;
const ll mod=1e9+7;
const ll inf=1e18;
const double eps=1e-6;
ll n,col[N],black,white;
stack<ll>gray;
string s;
bool ask(ll i,ll j){//i<j
    cout<<"? "<<i<<" "<<j<<endl;
    cin>>s;
    fflush(stdout);
    return s[0]=='Y';
}
void sol(){
    cin>>n;
    black=1,col[1]=1;
    white=0;
    for(int i=2;i<=n;i++){
        bool fl1=0,fl2=0,fl3=0;
        if(!white){
            fl1=ask(black,i);
            if(fl1)col[i]=1,black=i;
            else col[i]=0,white=i;
            continue;
        }
        if(gray.empty()){
            fl1=ask(black,i),fl2=ask(white,i);
            if(fl1&&fl2)gray.push(i);
            else {
                if(fl1)col[i]=1,black=i;
                else col[i]=0,white=i;
            }
        }else{
            fl3=ask(gray.top(),i);
            if(fl3)gray.push(i);
            else{
                fl1=ask(black,i);
                if(fl1){
                    col[i]=1,black=i;
                    while(!gray.empty()){
                        col[gray.top()]=0;
                        white=max(white,gray.top());
                        gray.pop();
                    }
                }else{
                    col[i]=0,white=i;
                    while(!gray.empty()){
                        col[gray.top()]=1;
                        black=max(black,gray.top());
                        gray.pop();
                    }
                }
            }
        }
    }
    while(!gray.empty()){
        col[gray.top()]=0;
        gray.pop();
    }
    cout<<"! ";
    for(int i=1;i<=n;i++)cout<<col[i]<<" ";
    cout<<endl;
    fflush(stdout);
    return ;
}
int main(){
    ll ttt;
    cin>>ttt;
    while (ttt--)sol();
    return 0;
}

```

---

## 作者：hcywoi (赞：2)

根据 Dilworth 定理，该图能被两条互不相交的链覆盖。

从小到大加点。我们现在需要维护两个栈，每个栈维护每条链的点。

若两个栈头没有连边，那么对于新加入的点，一定可以放到其中一个栈。

现在唯一的问题是，新加入的点可能可以放入两个栈。

我们可以再开一个栈三，用来维护以上述点为头的链。

对于一个新加入的点，分以下情况：

- 若栈三为空。分别与前两个栈的栈头询问。分情况加入三个栈即可。

- 若栈三不为空。先询问是否与栈三的栈头相连。若相连，则加入栈三。否则，加入前两个栈头与其相连的栈中（若有两个，任选一个即可）。然后将栈三的所有元素加入到与其相反的栈中。

容易发现，这样构造一定能使得前两个栈的栈头不相连。对于每个点，最多询问 $2$ 次。所以总的询问次数不多于 $2n$。

```cpp
#include <bits/stdc++.h>

using i64 = long long;

int ask(int a, int b) {
    std::cout << "? " << a + 1 << " " << b + 1 << std::endl;
    std::string s;
    std::cin >> s;
    return s == "YES";
}

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> c(n);
    std::vector<int> stk[3];
    stk[0].push_back(0);
    for (int i = 1; i < n; i ++ ) {
        if (stk[1].empty()) {
            if (ask(stk[0].back(), i)) {
                stk[0].push_back(i);
            } else {
                stk[1].push_back(i);
            }
        } else {
            if (stk[2].empty()) {
                int x = ask(stk[0].back(), i);
                int y = ask(stk[1].back(), i);
                if (!x) {
                    stk[1].push_back(i);
                } else if (!y) {
                    stk[0].push_back(i);
                } else {
                    stk[2].push_back(i);
                }
            } else {
                if (ask(stk[2].back(), i)) {
                    stk[2].push_back(i);
                } else if (ask(stk[0].back(), i)) {
                    stk[0].push_back(i);
                    for (auto j : stk[2]) {
                        stk[1].push_back(j);
                    }
                    stk[2].clear();
                } else {
                    stk[1].push_back(i);
                    for (auto j : stk[2]) {
                        stk[0].push_back(j);
                    }
                    stk[2].clear();
                }
            }
        }
    }

    for (auto i : stk[1]) {
        c[i] = 1;
    }

    std::cout << "!";
    for (int i = 0; i < n; i ++ ) {
        std::cout << " " << c[i];
    }
    std::cout << std::endl;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t -- ) {
        solve();
    }

    return 0;
}
```

---

## 作者：daniEl_lElE (赞：2)

我们希望开两个栈，每次用将新加入的点看一下是否跟两个栈的顶端连边，然后放到跟顶端连边的那一边。

然而如果两个栈顶端之间有边，那么两个顶端有概率都不能到达新加入的点。

不难发现，两个栈顶端之间有边的情况出现在新加的点跟两个栈顶端都有边的时候。在这种情况下，我们开一个新的栈，凡是出现这种情况就把点压入新的栈。

如果新的栈不为空，那么优先将新加入点跟栈顶确定是否连边，连边就加入，否则我们发现可以将新栈的扔到某个原来的栈的后面，将新的点扔到另一个栈的后面，即可再次达成栈顶不一样的局面。

总复杂度 $O(n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1)
using namespace std;
vector<int> s1,s2,tp;
bool qry(int i,int j){
	if(i==0||j==0) return 1;
	cout<<"? "<<j<<" "<<i<<"\n"; fflush(stdout);
	string s; cin>>s;
	return (s=="YES");
}
int col[100005];
signed main(){
	int t; cin>>t;
	while(t--){
		s1.clear(),s2.clear(),tp.clear();
		s1.push_back(0),s2.push_back(0);
		int n; cin>>n;
		int sta=1;
		for(int i=n;i>=1;i--){
			if(sta==1){
				int o1=qry(s1.back(),i),o2=qry(s2.back(),i);
				if(o1&o2){
					tp.push_back(i);
					sta^=1;
				}
				else if(o1){
					s1.push_back(i);
				}
				else if(o2){
					s2.push_back(i);
				}
			}
			else{
				int o=qry(tp.back(),i);
				if(o){
					tp.push_back(i);
				}
				else{
					int p1=qry(s1.back(),i);
					if(p1){
						s1.push_back(i);
						for(auto v:tp) s2.push_back(v);
						tp.clear();
					}
					else{
						s2.push_back(i);
						for(auto v:tp) s1.push_back(v);
						tp.clear();
					}
					tp.clear();
					sta^=1;
				}
			}
		}
		for(auto v:s1) col[v]=0;
		for(auto v:tp) col[v]=0;
		for(auto v:s2) col[v]=1;
		cout<<"! ";
		for(int i=1;i<=n;i++) cout<<col[i]<<" ";
		cout<<"\n"; fflush(stdout); 
	}
	return 0;
}
```

---

## 作者：_•́へ•́╬_ (赞：2)

## 思路

考虑一个最简单的思路：从 $n-1$ 到 $1$，问 $i$ 和 $i+1$ 之间有没有边，有就放一个集合，没有就放另一个。

交上去 [wa4](https://codeforces.com/contest/1977/submission/262752814)。冷静一下发现以下的 case：

![](https://cdn.luogu.com.cn/upload/image_hosting/txcv6rn9.png)

遇到图中 4 和 2 这种两边都能放的点，放错了会导致后面的点决策失败。

考虑加入倒车（反悔）操作：在试图加入形如图中 3 和 1 这种两边都不能放的点时，往后倒车，从 4 开始往回询问是否能加入另一个集合，并把尽可能多的点加入另一个集合。例如图中 5 不能加入另一个集合，就只反悔掉 4。

然后就没有然后了。显然一个点只会被反悔至多一次，他被反悔的时候会被询问第二遍，询问次数 $2n$。注意实现细节，如图中 3，在第二次反悔操作中，并没有被反悔但是也会被询问到，这多出来的一个点可能是触发上一次反悔操作的点，即两边都不能放的点，这个点会被询问三次，其中两次询问是一样的，记一下即可。

## code

```cpp
#include<stdio.h>
#include<vector>
#include<map>
#define pr pair<int,int> 
using namespace std;
#define nc getchar
inline void read(int&x)
{
	char c=nc();for(;c<'0'||'9'<c;c=nc());
	for(x=0;'0'<=c&&c<='9';x=(x<<3)+(x<<1)+(c^48),c=nc());
}
map<pr,char>mmp;
inline char qry(int u,int v)
{
	if(u>v)u^=v^=u^=v;
	if(mmp[(pr){u,v}])return mmp[(pr){u,v}];
	printf("? %d %d\n",min(u,v),max(u,v));fflush(stdout);
	char c;for(;c=nc(),(c^'Y')&&(c^'N'););
	return mmp[(pr){u,v}]=c;
}
int t,n;bool ans[111];vector<int>a[2];
struct __readt__{inline __readt__(){read(t);}}_readt___;
main()
{
	read(n);a[0].clear();a[1].clear();a[0].emplace_back(n);ans[n]=0;mmp.clear();
	for(int i=n-1;i;--i)
		if(qry(i,i+1)=='Y')ans[i]=ans[i+1],a[ans[i]].emplace_back(i);
		else
		{
			int u=ans[i+1],v=u^1;
			if(a[v].empty()||qry(i,a[v].back())=='Y')
				{ans[i]=v;a[v].emplace_back(i);continue;}
			for(int j=a[u].size()-1;;--j)if(qry(a[u][j],a[v].back())=='N')
			{
				for(int k=j+1;k<a[u].size();++k)
					a[v].emplace_back(a[u][k]),ans[a[u][k]]=v;
				for(;a[u].size()>j+1;a[u].pop_back());
				ans[i]=u;a[u].emplace_back(i);break;
			}
		}
	printf("! ");
	for(int i=1;i<=n;++i)printf("%d ",ans[i]);
	putchar('\n');fflush(stdout);
	if(--t)main();
}
```

---

## 作者：Priestess_SLG (赞：1)

首先有一个经典结论：连通性具有传递性。具体来说，图上若 $a$ 可以到达 $b$ ，$b$ 可以到达 $c$ ，那么 $a$ 就必然可以到达 $c$ 。在给定的图中，因为边总是从小编号连向大编号的，因此只需要判断编号相邻的两个点是否都连通，就可以知道是否整个集合内所有点都连通了。

考虑维护两个栈 $S_1,S_2$ ，其中 $S_1$ 为所有黑点按照编号从小到大组成的集合， $S_2$ 为所有白点按照编号从小到大组成的集合。那么若当前考虑到 $1\sim i-1$ 的所有点都已经按照条件放入 $S_1,S_2$ 两个栈中了，当前要将 $i$ 放入其中的一个，则考虑构造出一个合法的策略：

+ 若 $S_1$ 栈为空，那么将 $i$ 放入 $S_1$ 栈的栈顶。
+ 若 $S_2$ 栈为空，那么将 $i$ 放入 $S_2$ 栈的栈顶。
+ 若 $S_1$ 栈栈顶元素和 $i$ 连通，那么将 $i$ 放入 $S_1$ 栈的栈顶。
+ 若 $S_2$ 栈栈顶元素和 $i$ 连通，那么将 $i$ 放入 $S_2$ 栈的栈顶。
+ 若上述四个简单的条件均不满足，则考虑一直暴力的将 $S_1$ 栈栈顶的元素丢入栈 $S_2$ 的栈顶，直到栈 $S_1$ 为空，或 $S_1$ 栈顶元素和 $i$ 连通为止。此时将 $i$ 放入 $S_1$ 栈的栈顶。

下面来证明这个看似胡编乱造的策略的正确性：

**一、交互次数**

首先可以简单发现前两种操作不会耗费任何询问次数，三、四种操作只会耗费一次询问次数。问题在于五操作。若对每一次询问的答案进行记忆化处理，则可以发现，此时 $S_2$ 栈中所有元素都不会参与询问，而 $S_1$ 栈中所有元素最多被询问一次，就会被扔入 $S_2$ 栈中，因此总共最多耗费 $n$ 次询问。合起来就不超过 $2n$ 次询问。因此交互次数正确。

**二、时间复杂度**

交互次数是对的，那么因为时间复杂度完全等同于交互次数，所以为 $O(n)$ ，可以通过。

**三、正确性分析**

若不存在最后一种操作，则因为 $S_1,S_2$ 栈中所有元素编号必然在所在栈中相邻，且相邻两个元素都连通。根据连通的传递性可知 $S_1,S_2$ 两个栈中所有元素必然两两可达。

问题在于最后一个操作。考虑到该图的特殊性，任意三个点 $a,b,c$ 都必然有至少两个点之间存在可达关系。因此考虑三个元素 $i,t1,t2$ ，其中 $t1$ 为 $S_1$ 栈的栈顶元素， $t2$ 为 $S_2$ 栈的栈顶元素。因为 $i$ 和 $t1,t2$ 之间都没有可达关系，所以此时必有 $t1,t2$ 之间存在可达关系。因此 $t1$ 和栈 $S_2$ 中所有结点都具有可达关系，可以将 $t1$ 丢入栈 $S_2$ 中。

但是此时无法保证 $S_2$ 栈的单调性。有一种可行的策略是用 `set` 来提到栈维护 $S_1,S_2$ 两个点集合，但是其实没有必要。同样由于连通具有传递性，而且图中任意三个点都必然有至少两个点存在可达关系，所以其实没有必要要求 $S_2$ 栈顶为 $S_2$ 栈中编号最小的元素，任意一个元素都可以满足条件。因此直接按照上述方法模拟即可，时间复杂度为 $O(n)$ 可以解决问题。

```cpp
#pragma GCC optimize(3, "Ofast", "inline")
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 110;
int res[N], n, vis[N][N];
int ok(int i, int j) {
    if (vis[i][j] == 1) return 1;
    if (vis[i][j] == 0) return 0;
    cout << "? " << i << ' ' << j << endl;
    string o; cin >> o;
    return vis[i][j] = vis[j][i] = (o == "YES");
}
signed main() {
    // cin.tie(0)->sync_with_stdio(false);
    cout << fixed << setprecision(15);
    cerr << fixed << setprecision(5);
    int T;
    cin >> T;
    while (T--) {
        memset(vis, -1, sizeof vis);
        cin >> n;
        stack<int> s1, s2;
        for (int i = 1; i <= n; ++i) {
            if (s1.empty()) s1.emplace(i);
            else if (s2.empty()) s2.emplace(i);
            else if (ok(s1.top(), i)) s1.emplace(i);
            else if (ok(s2.top(), i)) s2.emplace(i);
            else {
                while (s1.size() && !ok(s1.top(), i)) s2.emplace(s1.top()), s1.pop();
                s1.emplace(i);
            }
        }
        while (s1.size()) res[s1.top()] = 0, s1.pop();
        while (s2.size()) res[s2.top()] = 1, s2.pop();
        cout << "! ";
        for (int i = 1; i <= n; ++i) cout << res[i] << ' ';
        cout << endl;
    }
    return 0;
}
```

---

## 作者：2022dyx (赞：0)

题解中似乎绝大部分都是用 Dilworth 定理推的，这里我给出一个均摊分析的做法。

题目性质指的是在任何一种按拓扑序删点的过程中，不存在超过两个零入度点的时刻。也就是说，按编号倒序处理时能用来加点的点最多只有两个。这提醒我们分类讨论。

当没有可用点，也就是最开始的时候，由于只有 $n$ 号点，所以不需要询问，而这 $2$ 次询问后面也用不到，所以可以省掉。

当只有一个可用点的时候，我们直接问 $i$ 和可用点，此时若连通则可直接连边，只花费 $1$ 的代价，留下 $1$ 用来后面均摊，而若不连通又分两种情况，如下图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/k230rmxm.png)

这是最初分开的情况，蓝圈中的部分使用累计下来的均摊次数，红圈是 $i$ 真正使用的 $1$ 次。由于后面的分析不需要此时剩余的 $1$ 次询问，所以这次询问可以省掉。

![](https://cdn.luogu.com.cn/upload/image_hosting/2gxkmj8r.png)

这时第二种情况，之前已经分开过。此时蓝圈中的部分依然可以使用累计下来的均摊次数，而后面只有 $k$，$x_1$ 和 $x_2$ 能够增加出度，直接让 $i$ 没有入度也不行，否则都会导致违反性质，因此红圈中的 $3$ 个位置只有 $2$ 个需要验证，都不是就意味着是最后一个，这两次直接计到 $i$ 的头上正好够用。

而有两个可用点的时候可以直接分别问一次，花费 $2$ 次询问，也可以直接计到 $i$ 的头上.

综上所述，全程使用询问不超过 $2n$。具体地，若全程只有一条链则只需要 $n-1$ 次询问，否则最开始 $n$ 的两次和分裂时省下的一次都一定存在，只需 $2n-3$ 次询问。由于 $n \ge 3$ 时后者一定大于前者，故此算法最多使用 $2n-3$ 次询问即可完成。

---

## 作者：PTqwq (赞：0)

首先考虑 Dilworth 定理，最小链覆盖等于最长反链，由题目中的限制可以得到最长反链 $\leq 2$，所以至多用 $2$ 种颜色就够了。

然后考虑维护两个栈，每次查询当前点 $i$ 可以加入哪个栈顶（可达），如果只有一个可以加入那就直接加入，否则我们随便加入，但是会有一种情况就是两个都加不了。

考虑我们的问题出在哪，如果我们思考一下就会发现其实问题就是出在有多个栈可以加的地方，如果都确定那么就根据开头说的定理就可以推出一定合法，我们考虑用第三个栈维护一下有两种情况的点，分几种情况讨论：

- 第三个栈为空：
- - 如果可达的只有一个：那就加。
  - 否则加入第三个栈。
  - 最多用 $2$ 次询问。
- 否则：
- - 如果可达第三个栈的栈顶：加入第三个栈。
  - 那么显然第三个栈中的数形如 $x, x + 1, \dots, u - 1$，$u$ 是当前点，我们考虑查询 $u$ 可不可以插入第一个栈，如果不可以就直接插入第二个栈，这样不可能不合法，证明参考 Dilworth 定理，否则就插入第一个栈，把第三个栈中的所有点都插入第二个栈，容易证明剩下的点最大可达的一定 $\geq x$，我们可以不关心剩下的点是啥，显然这样插入哪个栈都无所谓。
- 也是最多用 $2$ 次询问。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

namespace PTqwq {

int readqwq() {
    int x = 0;
    bool f = false;
    char c = getchar();
    for (; c < '0' || c > '9'; c = getchar()) f |= (c == '-');
    for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c - '0');
    if (f) {
        x = -x;
    }
    return x;
}

ll readllqwq() {
    ll x = 0;
    bool f = false;
    char c = getchar();
    for (; c < '0' || c > '9'; c = getchar()) f |= (c == '-');
    for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c - '0');
    if (f) {
        x = -x;
    }
    return x;
}

// 这个三个栈的构造真厉害。

vector<int> a[3];
int ans[115];
char buf[16];

bool query(int u, int v) {
    printf("? %d %d\n", u, v);
    fflush(stdout);
    scanf("%s", buf);
    if (buf[0] == 'Y') {
        return true;
    } else {
        return false;
    }
}

int Query(int i, int u) {
    if (a[i].empty()) {
        return 1;
    } else {
        bool t = query(a[i].back(), u);
        if (t) {
            return 1;
        } else {
            return 0;
        }
    }
}

int n;

void solve() {
    n = readqwq();
    a[0].clear();
    a[1].clear();
    a[2].clear();
    for (int i = 1; i <= n; ++ i) {
        ans[i] = -1;
        if (a[2].empty()) {
            int u = Query(0, i);
            int v = Query(1, i);
            if (u == 1 && v == 1) {
                a[2].push_back(i);
            } else if (u == 1) {
                a[0].push_back(i);
            } else {
                a[1].push_back(i);
            }
        } else {
            bool t = query(a[2].back(), i);
            if (t) {
                a[2].push_back(i);
            } else {
                int u = Query(0, i);
                if (u == 0) {
                    a[1].push_back(i);
                    for (auto j : a[2]) {
                        a[0].push_back(j);
                    }
                    a[2].clear();
                } else {
                    a[0].push_back(i);
                    for (auto j : a[2]) {
                        a[1].push_back(j);
                    }
                    a[2].clear();
                }
            }
        }
    }
    for (auto i : a[2]) {
        a[0].push_back(i);
    }
    for (auto i : a[0]) {
        ans[i] = 0;
    }
    for (auto i : a[1]) {
        ans[i] = 1;
    }
    printf("! ");
    for (int i = 1; i <= n; ++ i) {
        printf("%d%c", ans[i], i == n ? '\n' : ' ');
    }
    fflush(stdout);
}

void Solve() {
    int T = readqwq();
    for (int i = 1; i <= T; ++ i) {
        solve();
    }
}

}

int main() {
    PTqwq::Solve();

    return 0;
}
```

---

## 作者：happybob (赞：0)

题意：

**这是一道交互题。**

有一个 $n$ 个点的隐藏的 DAG，保证对于任意边 $i \rightarrow j$ 都有 $i > j$。对于任意三个点 $1 \leq i < j < k \leq n$，$k$ 能到 $i$，$k$ 能到 $j$，与 $j$ 能到 $i$ 三个条件至少有一个为真。你每次可以询问两个点 $i <j$，交互库返回 $j$ 能否到 $i$。你需要在 $2n$ 次询问内将图黑白染色，使得任意同色的两个不同的点 $i<j$ 满足 $j$ 能到 $i$。 

多测，$3 \leq n \leq 100$，$\sum n \leq 1000$。

解法：

首先可以证明必然有解。

具体地，考虑到达关系是偏序集，给定的条件告诉我们反链长度不超过 $2$，根据 Dilworth 定理，最小链覆盖不超过 $2$，所以必然有解。

构造方面，尝试枚举一些构造方式。考虑能不能增量。具体地，枚举 $i$ 从 $1$ 到 $n$，动态维护两种颜色的集合，每次判定这个点属于哪个集合。显然对于每种颜色。只需要记录这个颜色集合中最大的那个数。考虑现在加入点 $i$，两个集合最大数分别为 $a,b$。假设 $a<b$。若 $b$ 不能到 $a$，根据题意，点 $i$ 必然可以直接加入其中一个集合。但是若 $b$ 能到 $a$，可能 $i$ 无法到 $a$ 且 $i$ 无法到 $b$。考虑这样的情况为什么会出现。在每次加入 $i$ 进入某个集合时，若 $i$ 能同时到 $a,b$，则加入后就会产生这种情况。此时我们发现 $i$ 可以选入任意一个集合，我们并无法确定，于是我们再开一个集合维护这样的点。我们称这个集合为蓝集合。每次加入 $i$ 时，若 $i$ 能到蓝集合最大编号的点，则将 $i$ 加入蓝集合。否则 $i$ 必然能加入黑或白中的一个，我们将 $i$ 加入到任一个可能的集合，然后将蓝集合的点全都加入另一个集合即可。询问次数不超过 $2n$，复杂度 $O(n)$。

[Submission Link.](https://codeforces.com/problemset/submission/1977/294900443)

---

## 作者：Otomachi_Una_ (赞：0)

**【题意简述】**

有一个隐藏的 DAG，满足三点中必有两点可达。你可以问交互库 $2n$ 次两点之间是否可达。把 $n$ 个点分为两组使得组内点两两可达。

$n\leq 100$。

**【解题思路】**

用 $i\to j$ 表示 $i$ 能达到 $j$。

注意到如果 $i<j<k$，$i\to j,j\to k$，那么 $i\to k$。于是我们只需要组内排序后相邻点可达即可。

考虑维护两个栈 $S_1,S_2$。枚举 $i=1,2,\dots,n$，进行以下过程：

- 如果 $S_1$ 为空或者 $S_1$ 栈顶可达 $i$，把 $i$ 丢入 $S_1$。
- 如果 $S_2$ 为空或者 $S_2$ 栈顶可达 $i$，把 $i$ 丢入 $S_2$。
- 否则不断把 $S_1$ 栈顶元素丢入 $S_2$，直到 $S_1$ 为空或者 $S_1$ 栈顶可达 $i$，把 $i$ 丢入 $S_1$。

正确性的证明：首先 $S_1,S_2$ 维护过程中相邻元素必然两两可达。我们对这里步骤 $3$ 进行说明：因为步骤 $1,2$ 均失败，所以 $i\not\to top(S_1),i\not\to top(S_2)$，所以必然有 $top(S_1)\to top(S_2)$，所以这样是合法的。

加上一些小优化（比如如果已经询问过，或者能推断出）加上势能分析容易证明不会超过 $2n$ 次必然有结果。

**【参考代码】**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define MP make_pair
mt19937 rnd(time(0));
const int MAXN=105;
bool ans[MAXN];int vis[MAXN][MAXN],n;
bool ask(int i,int j){
	if(vis[i][j]!=-1) return vis[i][j];
	for(int t=1;t<=n;t++) if(vis[i][t]==0&&vis[t][j]==0) return vis[i][j]=1;
	cout<<"? "<<i<<' '<<j<<endl;
	string s;cin>>s;
	return vis[i][j]=vis[j][i]=(s[0]=='Y');
}
void solve(){
	cin>>n;
	memset(vis,-1,sizeof(vis));
	deque<int> q1,q2;
	q1.push_back(1);
	for(int i=2;i<=n;i++){
		if(ask(q1.back(),i)) q1.push_back(i);
		else if(q2.empty()||ask(q2.back(),i)) q2.push_back(i);
		else{
			while(!q1.empty()&&!ask(q1.back(),i)){
				q2.push_back(q1.back());
				q1.pop_back();
			}
			q1.push_back(i);
		}
	}
	while(!q1.empty()) ans[q1.front()]=0,q1.pop_front();
	while(!q2.empty()) ans[q2.front()]=1,q2.pop_front();
	cout<<"! ";
	for(int i=1;i<=n;i++) cout<<ans[i]<<' ';
	cout<<endl;
}
int main(){
	int _;cin>>_;
	while(_--) solve();
	return 0;
}
```

---

