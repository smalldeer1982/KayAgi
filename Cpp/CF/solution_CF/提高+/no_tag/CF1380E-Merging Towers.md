# Merging Towers

## 题目描述

有 $n$ 个唱片，第 $i$ 个唱片半径是 $i$，最开始他们被摆放在 $m$ 个塔。每个塔的唱片高度由下到上递减，也就是半径大的唱片摆在塔的下面。

你的目标是把所有唱片摆放到某个塔上，你可以选择两个**非空**的塔，取出一个塔的上层某些(可以是所有的)唱片并摆放到另一个塔上，注意摆放完不能破坏塔的从下到上递减的性质。这个操作会产生 $1$ 的代价。

给出 $m-1$ 个操作，第 $i$ 个给出序号为 $a_i$ 和 $b_i$ 的塔。你需要在第 $i$ 个询问时回答：前 $i$ 次操作执行完之后，合并当前所有塔需要的最小代价。

## 说明/提示

$2\le m\le n\le 2\cdot 10^5$

$1\le a_i,b_i\le m$ ，保证操作前 $a_i,b_i$ 塔存在唱片

$t_i$ 保证 $[1,m]$ 的数每个都会出现

## 样例 #1

### 输入

```
7 4
1 2 3 3 1 4 3
3 1
2 3
2 4```

### 输出

```
5
4
2
0```

# 题解

## 作者：LMB_001 (赞：3)

vector启发式合并+并查集
（vp的时候把启发式合并写反了，结果没T，MLE了……调了半天

```cpp
int n,m,a[MAXN],ans,fa[MAXN];
vector<int> v[MAXN];

int findfa(int x){if(fa[x]==x) return x;return fa[x]=findfa(fa[x]);}

int main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++) a[i]=read(),v[a[i]].push_back(i);
	for(int i=1;i<=m;i++) fa[i]=i;
	for(int i=1;i<n;i++) if(a[i]!=a[i+1]) ++ans;
	printf("%d\n",ans);
	for(int i=1;i<m;i++){
		int x=read(),y=read();
		x=findfa(x),y=findfa(y);
		if(v[x].size()>v[y].size()) swap(x,y);
		fa[x]=y;
		for(int j:v[x]){
			if(a[j-1]==y) --ans;
			if(a[j+1]==y) --ans;
			v[y].push_back(j);
		}
		for(int j:v[x]) a[j]=y;
		printf("%d\n",ans);
	}
	return 0;
}
```


---

## 作者：linyihdfj (赞：2)

## E.Merging Towers ##
[博客食用效果更佳](https://www.cnblogs.com/linyihdfj/p/16450318.html)
### 题目描述： ###
[原题面](https://codeforces.com/problemset/problem/1380/E)
### 题目描述： ###
因为每一座塔的盘从上到下都是从小到大的，所以我们每一次移动都一定可以在原有的基础上至少多匹配一个，所以我们所谓的困难值也就是大小相邻却不在同一座塔的圆盘的对数。

那么这样剩下的思路就好想了，每一次合并也就是判断某个塔里是否包含与当前塔里的圆盘的大小相邻的圆盘，也就是暴力将一座塔合并到另一座塔上。

因为无论谁合并到谁上对答案的影响相同所以我们就考虑将小的合并的大的上面，也就是使用启发式合并的思想，这样就能将复杂度降到 $O(\log n)$，也就是说每个点的被合并次数是最多 $\log n$ 次，所以复杂度就是 $O(n \log n)$
### 代码详解： ###
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
int place[MAXN],fa[MAXN];
vector<int> v[MAXN];
int find(int x){
	if(fa[x] == x)	return x;
	return fa[x] = find(fa[x]);
}
int main(){
	int n,m;
	cin>>n>>m;
	int ans = n-1;
	for(int i=1; i<=n; i++){
		cin>>place[i];
		fa[i] = i;
		v[place[i]].push_back(i);
	}
	for(int i=2; i<=n; i++){
		if(place[i] == place[i-1]){  //一开始就有不需要移动的 
			ans--;
		} 
	}
	cout<<ans<<endl;
	for(int i=1; i<m; i++){
		int x,y;
		cin>>x>>y;
		x = find(x); y = find(y);
		if(v[x].size() > v[y].size()){  //贪心的选择最小的合并所以就是个 log 的复杂度 
			swap(x,y);
		} 
		for(int i=0; i<v[x].size(); i++){
			int now = v[x][i];  //now 是 x 里的点 
			if(find(place[now-1]) == y)  //now 与 now-1 靠在了一起所以答案减一 
				ans--;
			if(find(place[now+1]) == y) // now 与 now+1 靠在了一起所以答案减一 
				ans--;
			v[y].push_back(now);
		}
		fa[x] = y;
		cout<<ans<<endl;
	} 
	return 0;
}
```

---

## 作者：鲤鱼江 (赞：1)

[link](https://www.luogu.com.cn/problem/CF1380E)

一个很好写的小清新题目，提供一个双 $\log$ 的做法。

先证明一个结论：我们约定同一塔内一段值域连续的区间是一个颜色段，则答案是颜色段数减一。

首先发现答案至少是这么多，因为我们每次只能操作塔顶，所以每一次只能消除一个颜色段。然后又发现答案最多这么多，因为从塔底到塔顶是单调的，所以每一次操作都可以删去一个颜色段。综上，结论成立。

然后就可以通过一些手段维护颜色段，我选择了启发式合并 set，来暴力做，还是很快。

```cpp
#include<bits/stdc++.h>

using namespace std;

namespace Fread {
	const int SIZE=1<<21;char buf[SIZE],*S,*T;
	inline char getchar() {if(S==T){T=(S=buf)+fread(buf,1,SIZE,stdin);if(S==T)return '\n';}return *S++;}
}
namespace Fwrite {
	const int SIZE=1<<21;
	char buf[SIZE],*S=buf,*T=buf+SIZE;
	inline void flush(){fwrite(buf,1,S-buf,stdout);S=buf;}
	inline void putchar(char c){*S++=c;if(S==T)flush();}
	struct POPOSSIBLE{~POPOSSIBLE(){flush();}}ztr;
}
#define getchar Fread :: getchar
#define putchar Fwrite :: putchar
namespace Fastio{
	struct Reader{
	    template<typename T>
    	Reader& operator >> (T& x) {
        	char c=getchar();
        	while(c<'0'||c>'9') c=getchar();x=0;
        	while(c>='0'&&c<='9'){x=x*10+(c-'0');c=getchar();}
	        return *this;
    	}
	    Reader(){}
	}cin;
	struct Writer{
	    template<typename T>
	    Writer& operator << (T x) {
	        if(x==0){putchar('0');return *this;}
	        if(x<0){putchar('-');x=-x;}
	        static int sta[45];int top=0;
	        while(x){sta[++top]=x%10;x/=10;}
	        while(top){putchar(sta[top]+'0');--top;}
	        return *this;
    	}
    	Writer& operator << (char c) {putchar(c);return *this;}
    	Writer(){}
	}cout;
}
#define fi first
#define endl '\n'
#define sec second
#define mk make_pair
#define cin Fastio :: cin
#define cout Fastio :: cout
typedef pair<int,int> pii;

/*
	考虑答案为颜色段数-1.
	使用set启发式合并维护颜色段及其个数，可以做到双log。
	时空较为充裕。
*/

const int N=2e5+10;
set < pii > s[N];
int n,cnt,m;

inline void ins(set<pii> &s,int x,int y){
	auto it=s.lower_bound(pii(x,y));
	if(it!=s.begin()){
		auto tmp=it;--tmp;
		if(tmp->sec+1==x) {
			x=tmp->fi;--cnt;
			s.erase(tmp);
		}
	}
	if(it!=s.end()){
		if(it->fi==y+1){
			y=it->sec;--cnt;
			s.erase(it);
		}
	}
	s.emplace(x,y);
}

int main(){
	cin>>n>>m;cnt=n;
	for(int i=1,x;i<=n;++i){cin>>x;ins(s[x],i,i);}
	cout<<cnt-1<<endl;
	for(int i=1,x,y;i<m;++i){
		cin>>x>>y;
		if(s[x].size()<s[y].size()) swap(s[x],s[y]);
		for(auto tmp:s[y]) ins(s[x],tmp.fi,tmp.sec);
		s[y].clear();cout<<cnt-1<<endl;
	}
	return 0;
}
```

---

## 作者：wtyqwq (赞：1)

- 题意翻译（本题还没有翻译，望添加）：
	- 有 $n$ 个圆盘，第 $i$ 个圆盘半径为 $i$。
	- 有 $m$ 个塔，初始时每个塔上至少有一个圆盘。在**任意**时刻，每个塔上的圆盘半径自底向上从大到小**递减**。
	- 定义一次**移动**操作为选择两个塔 $i,j(i\neq j)$，将 $i$ 自顶向下的若干圆盘移到塔 $j$ 的顶端，顺序不变。需保证操作完后局面**仍合法**。
	- 定义一次**合并**操作为对于两个塔 $i,j(i\neq j)$，通过若干次移动操作，将塔 $j$ 上的圆盘全部移到塔 $i$ 上。
	- 定义一个局面的**困难值**为将所有塔上的圆盘移到一个塔上所需进行的移动操作数的最小值。
	- 给定 $(m-1)$ 次合并操作，对于 $\forall k\in[0,m-1]$，求出做完前 $k$ 次合并操作后，当前局面的困难值。
	- $2\le n,m\le 2\times 10^5$。 

- 首先有一个很妙的结论：一个局面的困难值为满足半径为 $i(1\le i<n)$ 和 $i+1$ 的圆盘不在同一个塔上的 $i$ 的个数。证明：
	1. 困难值不可能小于这个值。对于每一个满足条件的 $i$，必然至少需要进行一次移动操作，将 $i$ 和 $i+1$ 移到同一个塔上。
	2. 困难值也不会大于这个值。我们可以按照 $1\rightarrow 2$，$1,2\rightarrow 3$，$1,2,3\rightarrow 4$，$1,2,3,\cdots,n-1\rightarrow n$ 的顺序进行移动操作，故最坏情况下操作数不超过 $(n-1)$ 次。显然，如果有一对 $(i,i+1)$ 在同一个塔上，对应的操作就不用进行了。
    
- 考虑如何处理询问。这里介绍两种方法：
	1. 启发式合并 DSU。对于每次合并操作，我们将圆盘少的塔 $y$ 合并到圆盘多的塔 $x$，遍历 $y$ 中的每个圆盘更新答案。注意还要记一个数组 $id_i$ 表示初始编号为 $i$ 的桶当前的编号。每个圆盘最多被合并 $\mathcal O(\log_2 n)$ 次，故复杂度为 $\mathcal O(m\log_2 n)$。
    
	2. 转化为树上问题 LCA。我们发现，每个圆盘 $i(1\le i<n)$ 对的答案的贡献为 $1$ 或 $0$。初始贡献为 $0$ 的 $i$ 就不用考虑了。我们要对初始贡献为 $1$ 的 $i$ 快速求出其贡献变为 $0$ 的合并操作的编号。我们建出一棵有 $2m-1$ 个节点的树，节点 $1\sim m$ 表示初始的每个塔，节点 $m+1\sim 2m-1$ 表示每次合并操作新建的节点，并且有 $2$ 个儿子，表示它合并的两个塔所对应的节点。显然，节点 $2m-1$ 便是根。考虑到如果节点 $x$ 是节点 $y$ 的祖先，那么 $x$ 一定包含了 $y$ 的所有圆盘。记录每个节点的高度 $h_x$（叶子的高度为 $0$）。记 $t_i$ 表示半径为 $i$ 的圆盘初始所在的塔的编号，那么令 $p=\text{LCA}(t_i, t_{i+1})$。显然 $p$ 就是高度最小的并且同时包含圆盘 $i$ 和 $i+1$ 的节点。所以 $h(p)$ 就是我们要求的了。复杂度 $\mathcal O(n\log_2 m)$。
    
- 后记：第一步的结论非常重要，移动操作的形式非常多样，需要我们去归纳这些操作里共有的性质，从而发现真正有效的操作，具有一定思维难度。之后方法二的转化也非常优美和自然，难度评分 *2300 也合理。综上所述，这是这场 edu 中不可多得的好题。

---

## 作者：quest_2 (赞：1)

## 题意稍加描述：
给出半径为 $1\cdots n$ 的 $n$ 个圆环和 $m$ 个塔，要求每个塔上圆环的**半径始终从底向上递减**，一次操作可以将一个塔顶部的若干个盘子移动到另一个塔的顶部，我们定义某一情形下的复杂度为**将所有圆环移动到同一个塔上所需要的最小操作数**。题目给出 $m-1$ 次询问，每次询问时输出**当前塔状态的复杂度**并**合并**两个塔上的圆环到同一个塔上。

------------
## 思路？

我们可以先手玩一下样例～：

```latex
7 4
1 2 3 3 1 4 3
3 1
2 3
2 4
```

$7$ 个圆环， $4$ 个塔。

$1$ 号塔上有 $1,5$ ， $2$ 号塔上有 $2$ ， $3$ 号塔上有 $3,4,7$  ， $4$ 号塔上有 $6$

我们以第一次询问为例：原初情况，$1$ 一定是先花费一步，去找 $2$ ，因为他们两个最后肯定（也只能）贴贴（~~雾~~）。

为什么能找到？想想看，除了 $1$ 以外，谁还能顶替他的位置做吊车尾，只能是 $2$（~~这或许是他们贴贴的原因~~）。

那 $2$ 不得不在最上层。找到 $2$ 以后再找 $3$ ，并以相同的原因找到他。

再找 $4$ ，这时候我们发现一个问题，这个 $4$ 早就已经和 $3$ 贴贴了。怎么样，还需要额外一步让他们贴贴吗？不需要了！

我们大可以跳过 $4$ 去找 $5$ ，而因为 $1$ 的移开我们再回到 $1$ 塔时塔顶已是 $5$ 了，我们找到 $5$ ，再找 $6$ ，再找 $7$ ，大功告成。

这样一波下来，我们发现，本来如果是七个分散的圆环，我们需要 $7-1=6$ 次操作把他们合并，但由于 $3$ 和 $4$ 的**提前贴贴**，导致我们**少用一次操作**，只需要 $5$ 次即可。我们或许可以通过观察归纳法得出一个结论了，我们需要的移动次数 $sum$ ，应该等于最劣移动次数 $m-1$ ，减去提前贴贴的圆环组数 $x$ ，即 $sum=m-1-x$ ，很好理解的吧（~~心虚~~）。

------------
## 实现？
首先，我们如何知道有几组提前贴贴的圆环，这好办，对于一个 $i$ 圆环，看看 $i-1$ 和 $i+1$ 是不是和他一个塔的就是了。

为什么？两个**相邻编号**的圆环要是在一个塔上，他们一定是贴贴的，这很好证，这两个之间再也插不进任何一圆环了（可谓是紧密贴贴）。

我们还需要解决怎么合并的问题，两个塔拖家带口合并，逐个插入，再来个 $\operatorname{sort}$ 必然是 $T$ 到飞起。

怎么解决这种下属很多的两个东西的合并问题？**并查集**就完事辣！最初所有塔的父亲都是自己，合并时只要把两个塔的**祖先合并**，查询时用个 $\operatorname{find()}$ 查这个环在哪个塔， $O(1)$ 合并，爽到。

由于圆环之间的贴贴关系是随着塔的合并而不断更新的，也就是说，如果我们每一次合并都扫一遍 $1\cdots N$，时间复杂度是 $O(nq)$ ，极大可能爆炸，怎么办？我们看看我们扫一遍的这种想法慢在哪。

我们在扫的时候，考虑了一些**位置根本没有改动**的圆环，但毫无疑问的，他们之前是怎么样，现在一样。为什么他们位置没有改动？因为他们压根就不在这次合并的两个塔上。那我们该如何解决？

考虑记录初始状态时，每个塔上都有哪些圆环，由于 $m,n$ 会很大但是圆环总数就那么点， $\mathtt{vector}$ 是个很好的选择。用 $\mathtt{vector[i]}$ 存第 $i$ 个塔上最开始时候的圆环们。合并的时候就把一个 $\mathtt{vector}$ 里的元素全部倒进另一个 $\mathtt{vector}$ 里，由于圆环有限，这里的操作撑死也就运行 $2\cdot 10^5$ 次，不影响大体时间复杂度。

知道了哪个塔上有什么，观察圆环是否贴贴的时候，我们就只用看这个塔上有什么，只对**这次合并的塔上的圆环**讨论即可。

我看到有 $dalao$ 说这是什么**启发式合并**的思想，我太蒻了，一道题目做完才知道用的是这思想。

我还看到有 $dalao$ 采用**线段树合并**的方法碾过去，我太蒻了，只听说过这东西，从来就不会打。

我还是太蒻了。

------------

## 代码？（~~随缘加点注释~~）
```cpp
#include <bits/stdc++.h>
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
using namespace std;
const int MAX = 2e5 + 7;
int N, M, tower[MAX], 


/*并查集组件*/
int fa[MAX];
inline int find(int n)
{
     if (n == fa[n])
          return n;
     return fa[n] = find(fa[n]);
}
inline void merge(int x, int y)
{
     fa[find(x)] = find(y);
}

/*vector 组件*/
vector<int> son[MAX];
void swap_int(int &a, int &b)
{
     int tmp = a;
     a = b;
     b = tmp;
}

int main()
{
     ios::sync_with_stdio(false);
     cin >> N >> M;
     int sum = N - 1;
     for (register int i = 1; i <= N; i++)
     {
          int tt;
          cin >> tt;
          tower[i] = tt;//i是这个塔的
          fa[i] = i;//并查集处理
          son[tt].push_back(i);//这个塔上有个i
     }
     for (register int i = 2; i <= N; i++)
     {
          if (tower[i] == tower[i - 1])
               sum--;//先看看初始状态总共有多少贴贴
     }
     cout << sum << endl;
     for (register int k = 1; k <= M - 1; k++)
     {
          int x, y;
          cin >> x >> y;
          int fx = find(x);
          int fy = find(y);//先抓到祖先
          if (son[fx].size() > son[fy].size())
          {
               swap_int(fx, fy);//偏偏处理size小的，贪一把
          }
          for (register int i = 0; i < son[fx].size(); i++)
          {
               int v = son[fx][i];
               if (find(tower[v - 1]) == fy)
                    sum--;//他的上位在塔里，sum--
               if (find(tower[v + 1]) == fy)
                    sum--;//他的下位在塔里，sum--
               son[fy].push_back(v);//倒出vector
          }
          merge(fx, fy);//合并
          cout << sum << endl;
     }
}
```


---

