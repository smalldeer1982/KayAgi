# [USACO24OPEN] The 'Winning' Gene S

## 题目背景

**注意：本题的内存限制为 512MB，通常限制的 2 倍。**

## 题目描述

在多年举办比赛并看着 Bessie 一次又一次地获得第一名后，Farmer John 意识到这绝非偶然。他得出结论，Bessie 一定将胜利写进了 DNA，于是他开始寻找这种「胜利」基因。

他设计了一个过程来识别这个「胜利」基因的可能候选。他获取了 Bessie 的基因组，为一个长为 $N$ 的字符串 $S$，其中 $1\le N\le 3000$。他选择某个数对 $(K,L)$，其中 $1\le L\le K\le N$，表示「胜利」基因候选的长度将为 $L$，并且将在一个较大的 $K$ 长度子串中进行寻找。为了识别这一基因，他从 $S$ 中取出所有 $K$ 长度的子串，我们将称这样的子串为一个 $K$-mer。对于一个给定的 $K$-mer，他取出其所有长度为 $L$ 的子串，将字典序最小的子串识别为胜利基因候选（如果存在并列则选择其中最左边的子串），然后将该字串在 $S$ 中的起始位置 $p_i$（从 $0$ 开始索引）写入一个集合 $P$。

由于他还没有选定 $K$ 和 $L$，他想知道每对 $(K,L)$ 将有多少个候选。

对于 $1\ldots N$ 中的每一个 $v$，帮助他求出满足 $|P|=v$ 的 $(K,L)$ 对的数量。 

## 说明/提示

### 样例解释 1

在这个测试用例中，输出的第三行为 $5$ 是因为我们发现恰好有 $5$ 对 $K$ 和 $L$ 存在三个「胜利」基因候选。这些候选为（其中 $p_i$ 从 $0$ 开始索引）：

```plain
(4,2) -> P = [0,3,4]
(5,3) -> P = [0,3,4]
(6,4) -> P = [0,3,4]
(6,5) -> P = [0,1,3]
(6,6) -> P = [0,1,2]
```

为了了解 $(4,2)$ 如何得到这些结果，我们取出所有的 $4$-mer

```plain
AGTC
GTCA
TCAA
CAAC
AACG
```

对于每一个 $4$-mer，我们识别出字典序最小的长度为 $2$ 的子串

```plain
AGTC -> AG
GTCA -> CA
TCAA -> AA
CAAC -> AA
AACG -> AA
```

我们取出所有这些子串在原字符串中的位置并将它们添加到集合 $P$ 中，得到 $P=[0,3,4]$。

另一方面，如果我们关注 $(4,1)$ 对，我们会发现这只会得到总共 $2$ 个「胜利」基因候选。如果我们取出所有的 $4$-mer 并识别字典序最小的长度为 $1$ 的子串（用 A，A' 和 A* 来区分不同的 A），我们得到

```plain
AGTC -> A
GTCA' -> A'
TCA'A* -> A'
CA'A*C -> A'
A'A*CG -> A'
```

尽管 A' 和 A* 在最后 3 种情况下字典序均为最小，但最左边的子串优先，因此仅有 A' 在所有这些情况中被视为候选。这意味着 $P=[0,4]$。

### 测试点性质

- 测试点 $2-4$：$N\le 100$。
- 测试点 $5-7$：$N\le 500$。
- 测试点 $8-16$：没有额外限制。

## 样例 #1

### 输入

```
8
AGTCAACG```

### 输出

```
11
10
5
4
2
2
1
1```

# 题解

## 作者：banned_gutongxing (赞：12)

## 思路

建议升蓝。

### 算法一

考虑暴力。

我们先枚举 $K,L$，考虑如何求解。

直接枚举每一个 $K$-mer，再枚举里面的每一个长度为 $L$ 的子串，找到最大的子串并在起始部分打一个标记。最后直接看有几个地方被打标记就行。

时间复杂度：$O(n^4)$。预计能过测试点 $1-4$。

### 算法二

我们可以把选取子串的过程大概画下来。

![](https://cdn.luogu.com.cn/upload/image_hosting/e3vxx63d.png)

我们发现每一次都会往后面都会多一个子串，我们可以考虑一个数据结构，可以删除最前面的数据，而且可以往后面加入一个数据，并动态求最值。我在这里选择的数据结构为**单调队列**。

时间复杂度：$O(n^3)$，预计能过测试点 $1-7$。

#### 代码

实践后：

![](https://cdn.luogu.com.cn/upload/image_hosting/lnxy96ls.png)

（~~常数写大了，超了 0.07秒~~）

```cpp
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
//#define int long long
namespace gtx{
//	Fast IO
	void read(int &x){
		x = 0;int h = 1;char tmp;
		do{tmp=getchar();if(tmp=='-')h*=-1;}while(!isdigit(tmp));
		while(isdigit(tmp)) x*=10,x+=tmp-'0',tmp=getchar();
		x*=h;
	}
	void read(char &x){do{x=getchar();}while(x==' '||x=='\n'||x=='\r');}
	void write(char x){putchar(x);}
	void write(int x){
		if(x<0) putchar('-'),x=-x;int st[200]={0},tot=0;
		do{st[++tot]=x%10,x/=10;} while(x);
		while(tot){putchar(st[tot--]+'0');};
	}
	void write(int x,char y){write(x);write(y);}
	const int MAXN = 3100;
	int n,ans,t[MAXN];
	char a[MAXN];
	signed main(){
		read(n);
		for(int i = 1;i<=n;i++) read(a[i]);
		for(int K = 1;K<=n;K++){
			for(int L = 1;L<=K;L++){
				deque<pair<int,string>> st;
				string now;
				for(int i = 1;i<=L;i++) now += a[i];
				st.push_back({1,now});
				for(int i = 2;i<=K-L+1;i++){
					now.erase(now.begin());
					now += a[i+L-1];
					while(!st.empty()&&st.back().second>now) st.pop_back();
					st.push_back({i,now});
				}
				bitset<MAXN> b;
				b.set(st.front().first);
				for(int i = K-L+2;i<=n-L+1;i++){
					if(st.front().first==i-(K-L)-1) st.pop_front();
					now.erase(now.begin());
					now += a[i+L-1];
					while(!st.empty()&&st.back().second>now) st.pop_back();
					st.push_back({i,now});
					b.set(st.front().first);
				}
				t[b.count()]++; 
			}
		}
		for(int i = 1;i<=n;i++) write(t[i],'\n');
		return 0;
	}
}
signed main(){
//	freopen("gene.in","r",stdin);
//	freopen("gene.ans","w",stdout);
//	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int T = 1;
//	gtx::read(T);
	while(T--) gtx::main();
	return 0;
}
```

### 算法三

我们在上面的代码中发现其实 $K$ 有没有都几乎没有什么区别，于是可以想一想定长的 $L$ 可以对哪些答案产生的贡献。

记录前面第一个比这个子串大的子串的起始位置为 $left_i$，后面第一个比这个子串大的子串的起始位置为 $right_i$。那么对于一个子串来说，如果这个子串能产生贡献 $K$ 最大应该的值的区间应该是这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/x6ql402t.png)

所以产生的最大的 $K$ 为 $right_i+L-2-left_i$。最小的 $K$ 应该就是这个子串的长度，那么这个子串就会对这些 $K$ 产生答案。我们可以用差分解决。

时间复杂度：$O(n^2)$。预计得分：$100pts$。

### AC代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
//#define int long long
namespace gtx{
//	Fast IO
	void read(int &x){
		x = 0;int h = 1;char tmp;
		do{tmp=getchar();if(tmp=='-')h*=-1;}while(!isdigit(tmp));
		while(isdigit(tmp)) x*=10,x+=tmp-'0',tmp=getchar();
		x*=h;
	}
	void read(char &x){do{x=getchar();}while(x==' '||x=='\n'||x=='\r');}
	void write(char x){putchar(x);}
	void write(int x){
		if(x<0) putchar('-'),x=-x;int st[200]={0},tot=0;
		do{st[++tot]=x%10,x/=10;} while(x);
		while(tot){putchar(st[tot--]+'0');};
	}
	void write(int x,char y){write(x);write(y);}
	const int MAXN = 3100;
	int n,t[MAXN],ans[MAXN][MAXN],left[MAXN],right[MAXN];
	char a[MAXN];
	signed main(){
		read(n);
		for(int i = 1;i<=n;i++) read(a[i]);
			for(int L = 1;L<=n;L++){
				stack<pair<int,string>> st;
				string now;
				for(int i = 1;i<=L;i++) now += a[i];
				st.push({1,now});
				for(int i = 1;i<=n-L+1;i++) left[i] = 0;
				for(int i = 1;i<=n-L+1;i++) right[i] = 0;
				left[1] = 1;
				for(int i = 2;i<=n-L+1;i++){
					now.erase(now.begin());
					now += a[i+L-1];
					while(!st.empty()&&st.top().second>now) st.pop();
					left[i] = st.empty()?1:st.top().first+1;
					st.push({i,now});
				}
				while(!st.empty()) st.pop();
				now="";
				for(int i = n-L+1;i<=n;i++) now+=a[i];
				right[n-L+1] = n;
				st.push({n-L+1,now});
				for(int i = n-L;i>=1;i--){
					now.erase(--now.end());
					now = a[i]+now;
					while(!st.empty()&&st.top().second>=now) st.pop();
					right[i] = st.empty()?n:st.top().first+L-2;
					st.push({i,now});
				}
				for(int i = 1;i<=n-L+1;i++){
					if(right[i]-left[i]+1<L) continue;
					ans[L][L]++;
					ans[right[i]-left[i]+2][L]--;
				}
//				cout << L << endl;
//				for(int i = 1;i<=n;i++) cout << left[i] << " " << right[i] << endl;
			}
		for(int j = 1;j<=n;j++){
			for(int i = j;i<=n;i++){
				ans[i][j] += ans[i-1][j];
				t[ans[i][j]]++;
			}
		}
		for(int i = 1;i<=n;i++) write(t[i],'\n');
		return 0;
	}
}
signed main(){
//	freopen("gene.in","r",stdin);
//	freopen("gene.out","w",stdout);
//	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int T = 1;
//	gtx::read(T);
	while(T--) gtx::main();
	return 0;
}
```

---

## 作者：EnofTaiPeople (赞：11)

考虑如何快速通过银组。

枚举 $L$，容易发现，对于每个下标 $p$，$K$ 越小越容易在 $P$ 中出现，具体地，考虑它往左走第一个**小于**它和往右走第一个**小于等于**它的字符串和它的距离，这就是它的极限。

考虑如何比较字符串，可以先后缀排序，然后对于两个下标 $p,q,rk_p<rk_q$，如果 $\operatorname{lcp}(sa_{rk_p},sa_{rk_p+1},\dots,sa_{rk_q})\ge L$，则 $p$ 和 $q$ 相等，此时该后缀数组区间的所有后缀均相等。

这相当于对后缀数组进行了重标号，但需要快速地求出 $\operatorname{lcp}$，显然这需要求的就是 height 数组，以上操作均可以 $O(n)$ 求出，不过为了方便，我使用 Z 函数处理出所有后缀的 $\operatorname{lcp}$，然后直接 `std:sort` 来后缀排序，$O(n^2+n\log n)$。

重标号之后，正反跑两次单调栈，求出一个下标的极限区间之后前缀加，这里直接打标记，最后后缀和一下，更新答案就可以了。

时空复杂度 $O(n^2)$：
```cpp
int n,m,Z[N],g[3005][3005],K,w[N],a[N],v[N],stk[N],tp,L[N],R[N],ans[N];
string s;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int i,j,k,l,r,x,y,z;ll v1,v2;
    cin>>n>>s,s='b'+s+' ';
    for(z=1;z<=n;++z){
        for(x=z+1,l=z;x<=n;++x){
            if(x<l+Z[l])Z[x]=min(l+Z[l]-x,Z[z+x-l]);
            else Z[x]=0;
            while(s[z+Z[x]]==s[x+Z[x]])++Z[x];
            g[z][x]=g[x][z]=Z[x];
            if(x+Z[x]>l+Z[l])l=x;
        }
    }
    for(x=1;x<=n;++x)a[x]=x;
    sort(a+1,a+n+1,[&](int x,int y){
        int k=g[x][y];
        return s[x+k]<s[y+k];
    });
    for(K=1;K<=n;++K){
        v[a[1]]=1,m=n-K+1;
        for(x=2;x<=n;++x)
            v[a[x]]=v[a[x-1]]+(g[a[x]][a[x-1]]<K);
        stk[tp=0]=0;
        for(x=1;x<=m;++x){
            while(tp&&v[stk[tp]]>v[x])--tp;
            L[x]=stk[tp]+1,stk[++tp]=x;
        }
        stk[tp=0]=m+1;
        for(x=m;x;--x){
            while(tp&&v[stk[tp]]>=v[x])--tp;
            R[x]=stk[tp]-1,stk[++tp]=x;
        }
        for(x=1;x<=m;++x)w[x]=0;
        for(x=1;x<=m;++x)++w[R[x]-L[x]+1];
        for(x=m-1;x;--x)w[x]+=w[x+1];
        for(x=1;x<=m;++x)++ans[w[x]];
    }
    for(x=1;x<=n;++x)printf("%d\n",ans[x]);
    return 0;
}
```

---

## 作者：Epi4any (赞：7)

分析样例后不难发现对于每个 $L$，都会有一组完全不同的字符串，我们对其进行标号，下表为对于 $L=2$ 的情况下样例中每一个子串可能得出的答案：

| | AG | GT | TC | CA | AA | AC | CG | tot |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| id | 3 | 6 | 7 | 4 | 1 | 2 | 5 |  |
| 1 | + | + | + | + | + | + | + | 7 |
| 2 | + | + |  | + | + | + |  | 5 |
| 3 | + |  |  | + | + |  |  | 3 |
| 4 | + |  |  |  | + |  |  | 2 |
| 5 |  |  |  |  | + |  |  | 1 |
| 6 |  |  |  |  | + |  |  | 1 |
| 7 |  |  |  |  | + |  |  | 1 |

每一个字符串的出现次数就是左侧第一个比他序号小的字符串和右侧第一个序号比他小的字符串的距离，左侧与右侧分别用一个单调栈解决，复杂度 $O(n^2)$。

然后解决子串排序，$f[i][j]$ 为 $i$ 开头字符串与 $j$ 开头字符串的最长公共子串长度，转移：若 $s_i$ 与 $s_j$ 相等，则 $f[i][j]=f[i+1][j+1]+1$，否则 $f[i][j]=0$。排序时与子串长度比较即可。

---

## 作者：masonpop (赞：4)

简单题。

考虑枚举 $L$，然后考虑串 $S_{i\sim i+L-1}$ 何时能出现。找到左边第一个比他小的串和右边第一个比他小的串，那么当且仅当 $k$ 小于等于某个特定的值时才会被计算。找左右第一个更小的可以单调栈套字符串哈希。最后后缀和一下即可。

注意题目说相同的串选择最左边的，因此左边的应该是小于等于，右边的是严格小于。

复杂度是 $O(n^2\log n)$ 的。[代码](https://www.luogu.com.cn/record/152968514)。

---

## 作者：cff_0102 (赞：3)

建议升蓝。

考虑直接枚举 $K$ 和 $L$，已经确定 $K$ 和 $L$ 的情况下，可以使用一个单调队列。这里在滑动一个长度为 $K-L+1$ 的“大窗口”的同时需要存下每个长度为 $L$ 的“小窗口”的字符串，比较的时候直接比较两个字符串的字典序。本质上还是滑动那个 $K-L+1$ 的窗口，用来比较大小的值变成了一个长度为 $L$ 的字符串。复杂度是 $O(n^3)$，期望得分是 $42$，不过会被第 $5$ 个点卡常卡到 $36$ 分。因为不是正解所以也不特意去卡进两秒了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int ans[3005];
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int n;cin>>n;
	string s;cin>>s;
	for(int k=1;k<=n;k++){
		for(int l=1;l<=k;l++){
			bool t[3005];for(int i=0;i<=n;i++)t[i]=0;
			deque<pair<int,string>>q;
			string nw=s.substr(0,l);
			q.push_back({0,nw});
			if(k==l)t[q.front().first]=1;
			for(int i=1;i<=n-l;i++){
				nw.erase(nw.begin());nw+=s[i+l-1];
				while(!q.empty()&&q.back().second>nw)q.pop_back();
				q.push_back({i,nw});
				while(!q.empty()&&q.front().first+k<i+l)q.pop_front();
				if(k<=i+l)t[q.front().first]=1;
			}
			int cnt=0;
			for(int i=0;i<n;i++)if(t[i])cnt++;
			ans[cnt]++;
		}
	}
	for(int i=1;i<=n;i++)cout<<ans[i]<<endl;
	return 0;
}
```

那么有什么优化的方法呢？

注意到在上面的代码中我们需要滑动不同长度的窗口，但实际上判断子串，包括 `q` 里面存的等等都和 $K$ 没关系，考虑直接计算出每个子串对不同 $K$ 的贡献，而不是枚举每个 $K$ 再重复取几遍这些子串。

首先不去管长度为 $L$ 的字符串，假设这些都是数字，我们要做的是求出每个位置对 $K$ 产生了多少贡献（对于每个 $K$，要么是 $1$，要么是 $0$），也就是看哪些 $K$ 可能会选取这个数字为连续 $K$ 个数的最小值。那么对于每个数只要知道它左边第一个小于等于它的数和右边第一个小于它的数的位置（记为 $l_i,r_i$），那么对应的 $K$ 的范围就是 $1$ 到 $r_i-l_i-1$，这个数就需要让 $1$ 到 $r_i-l_i-1$ 的这些 $K$ 的“候选数字数量”（意义见题面）全部加上 $1$。区间加一，求出最后所有数的值，可以用差分数组实现。

把上面提到的数字改成字符串，就可以完美解决本题的情况。还是一样，对于每个长度为 $L$ 的子串，记录下左边第一个字典序小于等于它的子串位置 $l_i$ 和右边第一个字典序小于它的子串位置 $r_i$，那么要加的 $K$ 的范围就是 $L$ 到 $(r_i+L-1)-l_i-1=L+r_i-l_i-2$，其中 $r_i+L-1$ 是右边那个字符串的结束位置。

要记录一个数（字符串）两侧第一个小于等于或严格小于它的数（字符串），可以使用单调栈。

```cpp
#include<bits/stdc++.h>
using namespace std;
int ans[3005],l[3005],r[3005],a[3005];
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int n;cin>>n;
	string s;cin>>s;
	for(int L=1;L<=n;L++){
		for(int i=0;i<=n;i++)a[i]=0,l[i]=-1,r[i]=n-L+1;
		stack<pair<int,string>>st;
		string nw=s.substr(0,L);
		st.push({0,nw});
		for(int i=1;i<=n-L;i++){
			nw.erase(nw.begin());nw+=s[i+L-1];
			while(!st.empty()&&st.top().second>nw)st.pop();
			if(!st.empty())l[i]=st.top().first;
			st.push({i,nw});
		}
		while(!st.empty())st.pop();
		nw=s.substr(n-L,L);
		st.push({n-L,nw});
		for(int i=n-L-1;i>=0;i--){
			nw.erase(nw.end()-1);nw=s[i]+nw;
			while(!st.empty()&&st.top().second>=nw)st.pop();
			if(!st.empty())r[i]=st.top().first;
			st.push({i,nw});
		}
		for(int i=0;i<=n-L;i++){
			a[L]++;
			a[L+r[i]-l[i]-1]--;//(L+r[i]-l[i]-2)+1
		}
		for(int k=L;k<=n;k++){
			a[k]+=a[k-1];
			ans[a[k]]++;
		}
	}
	for(int i=1;i<=n;i++)cout<<ans[i]<<endl;
	return 0;
}
```

---

## 作者：Starrykiller (赞：3)

困难题。

考虑枚举 $L$，计算每一个 $S(i,i+L-1)$ 的贡献。

记左边第一个**非严格**小于 $S(i,i+L-1)$ 的子串起始位置为 $L(i)$，右边第一个**严格**小于 $S(i,i+L-1)$ 的子串的起始位置为 $R(i)$。那么，在 $i$ 有贡献的区间 $[L,R]$ 中，左端点的限制条件为 $L\in (L(i),i]$，右端点的限制条件为 $R\in [i+L-1, R(i)+L-1)$。

从中解出 $K$ 的取值范围为 $[L,R(i)-L(i)+L-2]$。做一个前缀和就好了。而 $L(i)$ 和 $R(i)$ 可以通过排序+单调栈求出。总时间复杂度 $\Theta(N^2\log N)$，瓶颈在排序。

```cpp
struct node { string s; int pos; };
bool operator<(const node& a, const node& b) { 
    if (a.s!=b.s) return a.s<b.s;
    return a.pos<b.pos;
}
int f[MAXN][MAXN]; // f[l][k]

void work(int l) {
    vector<node> v; for (int i=1; i+l-1<=n; ++i) v.push_back({s.substr(i,l),i});
    sort(begin(v),end(v));
    for (int i=0; i<v.size(); ++i) rnk[v[i].pos]=i;
    vector<int> stk; vector<int> L(n+1), R(n+1,n-l+2);
    for (int i=1; i+l-1<=n; ++i) {
        while (stk.size()&&rnk[stk.back()]>rnk[i]) stk.pop_back();
        if (stk.size()) L[i]=stk.back();
        stk.push_back(i);
    }
    stk.clear();
    for (int i=n-l+1; i; --i) {
        while (stk.size()&&rnk[stk.back()]>rnk[i]) stk.pop_back();
        if (stk.size()) R[i]=stk.back();
        stk.push_back(i);
    }
    for (int i=1; i+l-1<=n; ++i) {
        int x=l, y=R[i]-L[i]+(l-1)-1;
        f[l][x]++; f[l][y+1]--;
    }
}
```

---

## 作者：markding (赞：0)

对不同的 $L$ 分别考虑，此时有 $N-L+1$ 个长度为 $L$ 的子串，我们将这些子串按字典序大小离散化为一个整数数组。

我们观察 $K$ 为多少时，某个子串（离散化后的整数）$a_i$ 是胜利基因候选。此时需要存在一个位置 $t\{t\le i\le t+K-1\}$ 使得 $a_j> a_i$ 对于 $t\le j<i$ 且 $a_j\ge a_i$ 对于 $i<j\le t+K-1$。所以可得若存在一个 $K$ 满足题意，$K'<K$ 显然也满足。

于是我们只需要求出对于每个 $a_i$，对应的最大 $K$ 值是多少。这一点可以通过左右两边分别通过单调栈求出最左边的第一个小于等于 $a_i$ 的值所在位置以及最右边的第一个小于 $a_i$ 的值所在位置来实现。（实现时可默认两头的数为 $-\inf$）

求完之后，我们可以使用前缀和累计答案。此时数组代表着当前 $L$ 固定，不同 $K$ 值的情况下，$|P|$ 的值。最后再更新到桶数组里，桶数组内的计数次数即为最终答案。

最后大致讲一下子串离散化的方法（具体见代码）：

假设我们已经离散好了所有长度为 $L-1$ 的子串。

对于所有长度为 $L$ 的子串，我们会发现这些子串相对顺序基本不变，只是会多出一个字母的区别。

于是可以想到对于所有长度为 $L$ 的子串，以“该子串去除末尾字符的相对顺序”为第一关键字，“该子串末尾的字符”为第二关键字排序，最后由小到大即可。（注意排序要把子串的位置一同丢进去）

```cpp
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int N=3005;
struct _{int x,y,z;}mem[N];
int hp,tp,top,n,f[N][N],lp[N],rp[N],sum[N],ans[N];
string s;pair<int,int> q,stk[N];
int main()
{
	cin>>n>>s,s=' '+s;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;i+j-1<=n;j++)
			mem[j]={f[i-1][j],s[i+j-1],j};
		sort(mem+1,mem+(n-i+1)+1,[](_ u,_ v){
			return u.x!=v.x?u.x<v.x:u.y!=v.y?u.y<v.y:u.z<v.z;
		});
		for(int j=1,nw=1;i+j-1<=n;j++)
		{
			if(j!=1 && (mem[j-1].x!=mem[j].x || mem[j-1].y!=mem[j].y))nw++;
			f[i][mem[j].z]=nw;
		}
	}
	for(int i=1;i<=n;i++)
	{
		stk[top=0]={-1,0};
		for(int j=1;j<=n-i+1;j++)
		{
			while(stk[top].first>f[i][j])top--;
			lp[j]=stk[top].second;
			stk[++top]={f[i][j],j};
		}
		stk[top=0]={-1,n-i+2};
		for(int j=n-i+1;j>=1;j--)
		{
			while(stk[top].first>=f[i][j])top--;
			rp[j]=stk[top].second;
			stk[++top]={f[i][j],j};
		}
		memset(sum,0,sizeof sum);
		for(int j=1;j<=n-i+1;j++)
			sum[rp[j]-lp[j]-1]++;
		for(int j=n-i+1;j>=1;j--)
			sum[j]+=sum[j+1];
		for(int j=1;j<=n-i+1;j++)
			ans[sum[j]]++;
	}
	for(int i=1;i<=n;i++)cout<<ans[i]<<endl;
}
```

---

## 作者：health235 (赞：0)

#### 题目概述：

给定一个字符串 $S$，我们要考虑所有长度为 $K$ 的子串（称为 $K-mer$）以及这些子串中每个可能的长度为 $L$ 的子串的字典序最小的子串。对于每个 $(K, L)$ 对，我们要输出满足一定条件的 $(K, L)$ 对数量。这些条件与字典序、最左子串以及子串出现的位置相关。

#### 分析

- 对于每个 $(K, L)$ 对，我们从字符串 $S$ 中提取所有 $K$ 长度的子串，然后对每个子串，找出其字典序最小的 $L$ 长度子串。
- 对于每个 $K-mer$，找到字典序最小的子串后，记录其在原字符串中的所有出现位置。
- 我们最终需要计算出每对 $(K, L)$ 中有多少个候选基因出现次数等于 $v$，其中 $v$ 从 1 到 N。


1. **子串的生成与字典序最小子串的计算**：
    - 对于每个 $K$ 和 $L$，我们生成所有 $K$ 长度的子串。
    - 对于每个 $K$ 长度的子串，从中找出所有可能的 $L$ 长度子串，并确定字典序最小的子串。
    
2. **记录出现位置**：
    - 每次找到字典序最小的 $L$ 长度子串后，记录其出现的所有位置。
    - 使用集合来去重这些位置，以避免重复计算。

3. **统计**：
    - 统计所有 $(K, L)$ 对的出现位置集合的大小，记录每种大小的出现次数。
    
4. **优化**：
    - 使用单调栈来高效地找到每个子串的字典序最小值的位置。
    - 使用哈希值来优化比较字典序的操作。

#### 解题思路：

1. **哈希优化字典序比较**：
    - 对于每个 $L$ 长度的子串，使用滚动哈希来计算子串的哈希值，并通过哈希值来进行字典序的比较。
    - 这样可以避免直接进行字符逐个比较，从而提高效率。

2. **单调栈**：
    - 使用单调栈来维护当前的字典序最小的子串的位置，分别从左到右和从右到左进行扫描。
    - 左边扫描可以找到第一个字典序小于当前子串的子串的位置，右边扫描则可以找到第一个字典序大于当前子串的子串的位置。

3. **区间更新与统计**：
    - 使用区间更新方法来统计每个出现的大小，从而计算最终结果。

#### 代码示例

```cpp
#include<bits/stdc++.h>
using namespace std;
auto mread = [](){int x;scanf("%d", &x);return x;};

const int N = 3005, p = 127, MOD = 998244353;
int n = mread(), sum[N][N], ha[N][20], pw[N], ans[N], l[N], r[N];
char s[N];

// 比较两个长度为 l 的子串 s[x:x+l-1] 和 s[y:y+l-1] 字典序的大小
int bal(int x, int y, int l){
    int sum = 0;
    for(int i = __lg(l); i >= 0; i--){
        if(sum + (1 << i) <= l && ha[x][i] == ha[y][i]){
            x += 1 << i;
            y += 1 << i;
            sum += 1 << i;
        }
    }
    if(sum == l) return 0;
    return (s[x] > s[y]) ? -1 : 1;
}

signed main(){
    pw[0] = 1;
    for(int i = 1; i < N; i++){
        pw[i] = pw[i - 1] * p % MOD;
    }
    
    scanf("%s", s + 1);
    
    // 计算前缀哈希
    for(int i = 1; i <= n; i++){
        ha[i][0] = (s[i] - 'A' + 1);
    }
    
    for(int j = 1; j <= 15; j++){
        for(int i = 1; i <= n - (1 << j) + 1; i++){
            ha[i][j] = (1ll * ha[i][j - 1] * pw[1 << j - 1] % MOD + ha[i + (1 << j - 1)][j - 1]) % MOD;
        }
    }
    
    stack<int> st;
    
    // 对于每个 L，计算字典序最小子串的左右区间
    for(int i = 1; i <= n; i++){
        while(!st.empty()){
            st.pop();
        }
        
        for(int j = 1; j <= n - i + 1; j++){
            while(!st.empty()){
                int tmp = bal(st.top(), j, i);
                if(tmp == -1){
                    st.pop();
                }
                else{
                    break;
                }
            }
            if(st.empty()){
                l[j] = 0;
            } else {
                l[j] = st.top();
            }
            st.push(j);
        }
        
        while(!st.empty()){
            st.pop();
        }
        
        for(int j = n - i + 1; j >= 1; j--){
            while(!st.empty()){
                int tmp = bal(j, st.top(), i);
                if(tmp == 1 || tmp == 0){
                    st.pop();
                } else {
                    break;
                }
            }
            if(st.empty()){
                r[j] = n + 1;
            } else {
                r[j] = st.top() + i - 1;
            }
            st.push(j);
        }
        
        // 计算出现次数
        for(int j = 1; j <= n - i + 1; j++){
            sum[i][i]++;
            sum[i][r[j] - l[j] - 1 + 1]--;
        }
    }
    
    // 进行区间累加并统计答案
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            sum[i][j] += sum[i][j - 1];
            ans[sum[i][j]]++;
        }
    }
    
    // 输出结果
    for(int i = 1; i <= n; i++){
        printf("%d\n", ans[i]);
    }

    return 0;
}
```

#### 时间复杂度

- 计算哈希值的时间复杂度为 $O(n \log n)$。
- 单调栈的操作复杂度为 $O(n)$。
- 由于我们处理了所有 $K$ 和 $L$ 对，所以总的时间复杂度为 $O(n^2)$。

由于题目保证 $N$ 最大为 3000，且时间限制为 3 秒，因此该解法在时间上是可行的。

---

## 作者：fydj (赞：0)

## 思路

枚举 $L$，把所有长度为 $L$ 的子串取出来，排序，如果两个子串完全相同就按照它们的起始位置排序，求出起始位置在 $0$ 到 $N-L$ 之间的子串排名 $kth_i$ 。这部分可以利用后缀数组和 ```height``` 数组求。

对于一个以 $i$ 为起点的 ```K-mer```，它里面字典序最小的子串的起点是从 $i$ 开始向右 $k=K-L+1$ 个位置中，$kth$ 最小的位置。

对于每一个长度为 $L$ 的子串的起点 $i$，用单调栈分别求出在它前面和后面离它最近并且 $kth$ 小于它的位置 $L$ 和 $R$。那么，$k$ 小于等于 $R-L-1$ 时，起点 $i$ 会被放到集合中，相当于起点 $i$ 对 $k \le R-L-1 $ 的二元组 $(K,L)$ 生成的集合大小产生了 $1$ 的贡献。用差分数组维护。然后直接把二元组 $(K,L)$ 累加进答案即可。

## 代码

省略求后缀数组和 ```height``` 数组的过程。

```cpp
for(L=1;L<=n;++L) {
	memset(suf,0,(n+10)<<2),list[0]=0;
	for(i=1;i<=n;i=j+1) {
		j=i; while(j<n&&height[j+1]>=L) ++j;
		plan[0]=0; for(p=i;p<=j;++p) if(sa[p]<=n-L+1) plan[++plan[0]]=sa[p];
		sort(plan+1,plan+plan[0]+1);
		for(p=1;p<=plan[0];++p) list[++list[0]]=plan[p];
	}
	for(i=1;i<=list[0];++i) kth[list[i]]=i;
	zhan[0]=0; for(i=1;i<=n-L+1;++i) { while(zhan[0]&&kth[zhan[zhan[0]]]>kth[i]) --zhan[0]; lst[i]=zhan[zhan[0]],zhan[++zhan[0]]=i; }
	zhan[0]=0; for(i=n-L+1;i;--i) { while(zhan[0]&&kth[zhan[zhan[0]]]>kth[i]) --zhan[0]; nxt[i]=zhan[zhan[0]],zhan[++zhan[0]]=i; }
	for(i=1;i<=n-L+1;++i) if(!nxt[i]) nxt[i]=n-L+2;
	for(i=1;i<=n-L+1;++i) ++suf[nxt[i]-lst[i]-1];
	for(i=n;i;--i) suf[i]+=suf[i+1];
	for(i=1;i<=n;++i) ++ans[suf[i]];
}
```

---

