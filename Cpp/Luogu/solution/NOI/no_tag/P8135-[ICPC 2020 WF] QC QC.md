# [ICPC 2020 WF] QC QC

## 题目描述

创新可计算质量控制（ICQC）开发了一种突破性的机器，用于执行质量控制。得益于其新颖的深度智能技术，ICQC 质量控制（QC）机器可以以 $100\%$ 的准确率自动检测任何现有机器的制造错误，无论是咖啡机、星际飞船还是量子计算机。

ICQC 现在正在建立其工厂以生产这些 QC 机器。与任何其他制造过程一样，生产的机器中会有一部分出现故障，这些需要被发现并丢弃。幸运的是，ICQC 恰好有产品可以检测故障机器！

显然，ICQC 不应该简单地让 QC 机器自检，因为故障机器可能会错误地将自己分类为正常工作。相反，ICQC 将在夜间让每天生产的 $n$ 台机器相互测试。特别是，在夜间的每个小时，每台 QC 机器可以检查另一台 QC 机器，同时被另一台 QC 机器检查。

如果执行检查的机器是正常的，它将正确报告被测试机器是正常还是故障，但如果执行检查的机器是故障的，它可能报告任一结果。如果机器 A 多次用于测试机器 B，它每次都会返回相同的结果，即使机器 A 是故障的。具体的测试计划不需要提前固定，因此第二小时夜间的机器检查安排可以基于第一小时测试的结果进行。

ICQC 确信每批 $n$ 台 QC 机器中有严格超过一半的机器正常工作，但夜晚只有 $12$ 小时，因此只能进行少量的测试轮次。你能帮助 ICQC 确定哪些 QC 机器出现故障吗？

例如，考虑下面的示例交互 1。在第四个小时后，每台机器都测试了其他所有机器。对于机器 $1$，只有一台其他机器声称它故障，如果它真的故障，那么至少有 $3$ 台其他机器会声称这一点。对于机器 $4$，只有一台其他机器声称它正常，这意味着机器 $2$ 必定是故障的，因为应该有超过一半的机器正常工作。注意，即使机器 $4$ 是故障的，它在这些特定的测试轮次中仍然恰好产生了正确的响应。

## 说明/提示

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
1
5
10101
01110
10101
10101
10101
```

### 输出

```
test 5 4 2 1 3
test 4 5 1 3 2
test 2 3 4 5 1
test 3 1 5 2 4
answer 10101```

## 样例 #2

### 输入

```
2
4
1111
7
0001100
----11-```

### 输出

```
test 2 3 4 1
answer 1111
test 2 3 4 5 6 7 1
test 0 0 0 0 2 4 0
answer 0101110```

# 题解

## 作者：Alex_Wei (赞：5)

> *[P8135 [ICPC2020 WF] QC QC](https://www.luogu.com.cn/problem/P8135)*
>
> 两种人，$1$ 或 $0$。$1$ 只说真话，$0$ 对于询问相同的人的状态的回答相同。进行不超过 $12$ 轮询问，每轮询问形如向第 $i$ 个人问第 $p_i$ 个人的状态。需保证 $p_i$ 互不相同且 $i \neq p_i$。已知 $1$ 的人数严格大于 $0$ 的人数，试确定每个人的状态。

高妙构造题。

首先，我们只能从回答的结果反推出每个人的状态，且一定是让两个人相互询问。若不相互询问，我们难以确定任何一个人的状态，因此导致获得的信息完全无用。

考虑两个 $1$ 相互询问，回答必然是 $1, 1$。$1, 0$ 相互询问，回答 **至少有一个** $0$。两个 $0$ 相互询问，回答可能是任何结果。容易发现若回答为 $1, 1$，则两个人的状态必然相同。

根据上述结论，我们考虑将所有人划分为若干 **等价类**，每个等价类内部所有人的状态均相同。一开始，每个人都是一个等价类。称为 **一型等价类**。

接下来，将所有一型等价类两两配对并互相询问。若询问结果不是 $1, 1$，说明它们当中必然 **至少有一个** $0$。将这些 **大小相同** 的 **等价类对** 两两丢到一边，称为 **二型等价类**。

每次配对的过程中，可能有单独的一型等价类剩余。丢到一边，称为 **三型等价类**。

- 性质 1：任何时候任何一型等价类和三型等价类的大小均为 $2$ 的幂。
- 性质 2：不会出现大小相同的三型等价类。
- 性质 3：一型等价类和三型等价类的 $1$ 的个数严格大于 $0$ 的个数。这是因为二型等价类中 $0$ 不少于 $1$（关键性质）。

考虑配对的最终结果。显然，若一型等价类个数 $\geq 2$，则还可以继续配对。若一型等价类个数等于 $1$，则看做三型等价类。

因此，最终不剩余任何一型等价类。根据上述三条性质，容易发现必然存在三型等价类，且最大的的三型等价类必然为 $1$。若不然，根据小于 $2 ^ K$ 的不同的 $2$ 的幂之和最大为 $2 ^ K - 1$ 这一事实，与性质 3 矛盾。

现在我们用较少的步数确定了至少一个 $1$。只需要用这个 $1$ 去 **倍增** 确定所有二型等价类的类型即可。倍增的思想体现为每确定一个等价类的类型，若该等价类为 $1$，则每次能够确定的等价类的类型会增加该等价类的数量。

除非运气特别差，$12$ 次询问足以确定所有人的状态，因为最差结果是问出来的结果都是二型等价类，唯一的三型等价类大小为 $1$，且一开始用三型等价类问二型等价类的状态，得到的结果全是 $0$。这种情况在加入适当随机化之后出现概率可以视为 $0$。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define vint vector <int>
#define pb push_back

string query(vint p) {
	string res;
	cout << "test ";
	for(int it : p) cout << it << " ";
	cout << endl, cin >> res;
	return res;
}

const int N = 100 + 5;
int n;
vector <int> id[N], t1, t2, t3, fix;

void merge(vint &x, vint y) {for(int it : y) x.push_back(it);}
void solve() {
	cin >> n, t1.clear(), t2.clear(), t3.clear(), fix.clear();
	for(int i = 1; i <= n; i++) id[i].clear(), id[i].pb(i), t1.pb(i);
	while(t1.size()) {
		vector <int> p(n), nt1;
		for(int i = 0; i + 1 < t1.size(); i += 2) p[t1[i] - 1] = t1[i + 1], p[t1[i + 1] - 1] = t1[i];
		if(t1.size() & 1) t3.pb(t1.back());
		string res = query(p);
		for(int i = 0; i + 1 < t1.size(); i += 2) {
			int x = t1[i], y = t1[i + 1];
			if(res[x - 1] == '1' && res[y - 1] == '1') merge(id[x], id[y]), nt1.pb(x);
			else t2.pb(x), t2.pb(y);
		} t1 = nt1;
	}
	
	int bk = t3.back(), cur = 0;
	merge(fix, id[bk]), t3.pop_back();
	vector <int> p(n);
	for(int it : t3) p[id[bk][cur++] - 1] = it;
	string res = query(p); cur = 0;
	for(int it : t3) if(res[id[bk][cur++] - 1] == '1') merge(fix, id[it]);
	
	while(t2.size()) {
		int lim = min(fix.size(), t2.size());
		vector <int> p(n), nfix = fix;
		for(int i = 0; i < lim; i++) p[fix[i] - 1] = t2.back(), t2.pop_back();
		string res = query(p);
		for(int i = 0; i < lim; i++) if(res[fix[i] - 1] == '1') merge(nfix, id[p[fix[i] - 1]]);
		fix = nfix;
	}
	
	string ans;
	for(int i = 0; i < n; i++) ans += '0';
	for(int it : fix) ans[it - 1] = '1';
	cout << "answer " << ans << endl;
}

int main() {
	int T; cin >> T;
	while(T--) solve();
}
```

优化：注意到当且仅当最后一次合并时，将偶数个大小为 $2 ^ K$ 的一型等价类两两（**组成一对**）丢到二型等价类时，最大三型等价类较小，不大于 $2 ^ {K - 1}$，且三型等价类大小总和小于 $2 ^ K$。但注意到此时对于所有最大的二型等价类 **对** $x, y$，必然恰有一个为 $1$，恰有一个为 $0$。因为若两个都为 $0$，则可以推出 $1$ 的个数不大于 $0$ 的个数，与题意矛盾。这样一来，每次我们必然能成功获得一个较大的为 $1$ 的等价类，优化显著。

一个乱搞方法（来源于 LOJ 第一篇提交）：考虑每次将两个等价类合并。对于所有不同的等价类对 $(x, y)$，按 $\max(sz_x, sz_y)$ 从大到小排序，并优先选择能操作的等价类对询问。在不超过 $8$ 次询问内能得到答案，此时大小最大的等价类即为 $1$，其它等价类均为 $0$（若为 $1$ 就被最大等价类合并了）。

启示：构造题当中 $2$ 的幂一般很有性质。

---

## 作者：SnowTrace (赞：1)

> 有 $n,(n\le100)$ 个机器，每个机器可以测定别的机器有没有故障。如果一个机器有故障，他不一定会返回正确结果，但是对于相同机器的询问返回的结果相同，如果一个机器没有故障就可以正确判断别的机器是否故障。现在已知 $n$ 个机器中有大于一半的机器没有故障，在 $12$ 次让每台机测定定另一台机器的操作中找到没有故障的机器。

稍微感受一下，一次询问能够获得的信息量实际上相当少，因为你完全不能判定当前用的这台机器是否说的是真话。我们考虑在让 $x$ 查 $y$ 的同时让 $y$ 也查 $x$，此时如果回答是 $1,1$，则机器 $x$ 和 $y$ 的状态是相同的，否则 $x$ 和 $y$ 中至少有一台机器是故障的，这样我们就至少获取了一点点信息。

我们发现一个事实是，如果 $x$ 和 $y$ 中至少有一台机器故障，则把 $x$ 和 $y$ 两个机器都删掉，仍然满足无故障的机器数量大于一半。

我们可以设计这样一个算法：维护若干个已经确定状态全相同的等价类，每次取两个等价类出来，让这两个等价类互相查，如果查出来是 $1,1$ 就合并成一个新的等价类，否则就把两个等价类都删掉。

显然这样做最后会剩下恰好一个等价类，根据上面的论述，这个等价类里面的机器肯定全部都合法。

既然我们知道了一个没有故障的机器，就能用这个数问出来剩下所有的情况。从而我们在不限操作次数的情况下解决了这个问题。

接下来考虑如何改进操作的次数，首先前面的合并等价类的过程，采用合并果子的方法，很容易做到 $\log n$ 次操作。

在第二步中我们通过找到的若干个没有故障的机器去确定后面的机器，然而在确定机器的时候我们可以得到更多无故障的机器，这些机器可以在后续也用来测定别的机器，所以可以做一个类似倍增的过程。由于这个题交互库不是自适应的，可以在一开始随机打乱机器的顺序，这样我们每一次查询一个机器时它的状态可以视作是均匀随机的，所以这一部分也是 $\log n$ 次操作。

代码十分丑陋。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
vector<int>id[105];
int pp[105];
char a[105];
int res[105];
void query(vector<int>p){
	cout << "test ";for(auto x:p)cout << x+1<< " ";cout << endl;
	for(int i = 0;i<n;i++)cin >> a[i];
}
void merge(vector<int>&a,vector<int> b){for(auto x:b)a.push_back(x);}
void solve(){
	vector<int>p1,p2,p3,P;
	cin >> n;
	for(int i = 0;i<n;i++)res[i] = 0;
	for(int i = 0;i<n;i++)pp[i] = i;random_shuffle(pp+1,pp+1+n);
	for(int i = 0;i<n;i++)id[i].clear();
	for(int i = 0;i<n;i++)id[i].push_back(i);
	for(int i = 0;i<n;i++)p1.push_back(i);
	while(p1.size()){
		if(p1.size()&1){p3.push_back(p1.back());p1.pop_back();}
		if(p1.empty())break;
		vector<int>p;p.resize(n,-1);
		for(int i =0 ;i+1<p1.size();i+=2){
			p[p1[i]] = p1[i+1];
			p[p1[i+1]] = p1[i];
		}
		query(p);
		vector<int>pp1;
		for(int i =0;i+1<p1.size();i+=2){
			if(a[p1[i]]!='1' or a[p1[i+1]]!='1'){
				p2.push_back(p1[i]),p2.push_back(p1[i+1]);
			}else{
				merge(id[p1[i]],id[p1[i+1]]);

				pp1.push_back(p1[i]);
			}
		}
		p1 = pp1;
	}
	merge(P,id[p3.back()]);
	if(p3.size()>1){
		vector<int>p;p.resize(n,-1);
		for(int i =0;i+1<p3.size();i++){
			p[P[i]] = p3[i];
		}
		query(p);
		for(int i = 0;i+1<p3.size();i++){
			if(a[P[i]]=='1'){
				merge(P,id[p3[i]]);
			}
		}
	}
	reverse(p2.begin(),p2.end());
	while(p2.size()){
		int cc = min(p2.size(),P.size());
		vector<int>p;p.resize(n,-1);
		for(int i =0;i<cc;i++)p[P[i]] = p2[i];
		query(p);
		for(int i =0;i<cc;i++){
			if(a[P[i]]=='1'){
				merge(P,id[p2[i]]);
			}
		}
		vector<int>pp2;
		for(int i = cc;i<p2.size();i++)pp2.push_back(p2[i]);
		p2 = pp2;
	}
	for(auto x:P)res[x] = 1;
	cout << "answer ";for(int i = 0;i<n;i++)cout << res[i];
	cout << endl;
}
signed main(){
	srand(time(0));
	int t;cin >> t;/
	while(t--)solve();
	return 0;
}
/*
O.o
*/
```

---

## 作者：yyyyxh (赞：1)

有 $n$ 个人，有些人只会说真话有些人不一定，多于一半的人说真话，你需要进行不超过 12 轮询问确定哪些人一定说真话，每轮可以问每个人另一个人是不是一定说真话。

离谱题目，就要用离谱做法。这个题其实可以压到 6 轮的！

$1$ 代表一定说真话，$0$ 代表不一定。考虑只询问二元环，也就是每一对人互相问，这样的话如果返回 $1,1$ 那么说明这两个人要么是 $(1,1)$ 要么是 $(0,0)$。那么直接把这两个人的状态合并起来就行了。

接下来一个想法是如果经历若干轮之后所有的 $1$ 都合并起来了，那么绝对众数的那个连通块就是答案。但是你发现你很难合理安排策略使得很大概率能全部合并。

考虑一些启发式的想法，第一个想法是我们询问同一个连通块的边或者同一轮询问询问同一对连通块的边一定是不优的，所以说我们只需要考虑连通块之间连边。第二个观察是真连通块趋向于很大而且能连很多边，所以说我们启发式地每次拿大点的连通块优先连。

写一个这样的算法：每次拿一个最大的连通块随机与一个没连边的其它连通块相连，发现这能过不一定话的人随机返回的交互库，但是当不一定说真话的人一直说真话时，最大的连通块并不倾向于是真的，我们需要更多的信息。

考虑我们询问一条边，如果结果是 $1,1$ 就连边，否则说明这一对连通块间永远不可能连边了。于是你存储所有询问失效的边，然后你就可以得出所有不能问的连通块对，每次随机选取时忽略这些连通块对。这个乱搞特牛，6 轮就可以以极大概率完成操作。

添加 `LOCAL` 宏用于交互库本地测试。直到我写完了这题代码，zhy 才告诉我 LOJ 上有 python 交互库可以用。

```cpp
#include <map>
#include <cstdio>
#include <vector>
#include <random>
#include <cassert>
#include <algorithm>
using namespace std;
mt19937 rng(random_device{}());
int read(){
	char c=getchar();int x=0;
	while(c<48||c>57) c=getchar();
	do x=x*10+(c^48),c=getchar();
	while(c>=48&&c<=57);
	return x;
}
const int N=103;
int n,rk;
int f[N],w[N];
vector<int> vec[N];
int rt(int x){
	if(f[x]==x) return x;
	return f[x]=rt(f[x]);
}
int tp,sx[N],sy[N];
inline void add(int u,int v){++tp;sx[tp]=u;sy[tp]=v;}
int p[N];bool q[N],ans[N];
bool res[N],mp[N][N];
bool anti[N][N],non[N][N];
inline void sol(){
	for(int i=1;i<=n;++i) p[i]=0;
	for(int i=1;i<=tp;++i) p[sx[i]]=sy[i],p[sy[i]]=sx[i];
	printf("test");
	for(int i=1;i<=n;++i) printf(" %d",p[i]);
	putchar('\n');
	fflush(stdout);
#ifdef LOCAL
	for(int i=1;i<=n;++i)
		if(p[i]) q[i]=mp[i][p[i]];
		else q[i]=1;
#else
	char cc=getchar();
	while(cc!='0'&&cc!='1'&&cc!='-') cc=getchar();
	for(int i=1;i<=n;++i) q[i]=cc^48,cc=getchar();
#endif
	for(int i=1;i<=tp;++i)
		if(q[sx[i]]&&q[sy[i]]) f[rt(sx[i])]=rt(sy[i]);
		else anti[sx[i]][sy[i]]=1;
}
int arr[N];
void solve(){
	n=read();
	for(int i=1;i<=n;++i) f[i]=i,ans[i]=0;
#ifdef LOCAL
	int cnt;
	do{
		cnt=0;
		for(int i=1;i<=n;++i) cnt+=(res[i]=rng()&1);
	}while(cnt*2<=n);
	for(int i=1;i<=n;++i)
		if(res[i]) for(int j=1;j<=n;++j) mp[i][j]=res[j];
		else for(int j=1;j<=n;++j) mp[i][j]=1;
#endif
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j) anti[i][j]=0;
	for(int it=0;it<6;++it){
		tp=0;rk=0;
		for(int i=1;i<=n;++i){
			vec[i].clear();
			if(f[i]==i) w[rk++]=i;
		}
		for(int i=1;i<=n;++i) vec[rt(i)].emplace_back(i);
		for(int i=1;i<=n;++i)
			for(int j=1;j<=n;++j)
				non[i][j]=0;
		for(int i=1;i<=n;++i)
			for(int j=1;j<=n;++j)
				if(anti[i][j]) non[rt(i)][rt(j)]=non[rt(j)][rt(i)]=1;
		sort(w,w+rk,[](int x,int y){return vec[x].size()>vec[y].size();});
		for(int i=0;i<rk;++i){
			int x=w[i],sz=0;
			if(vec[x].empty()) continue;
			for(int j=i+1;j<rk;++j) if(!vec[w[j]].empty()&&!non[x][w[j]]) arr[sz++]=w[j];
			for(int j=0;j<sz&&!vec[x].empty();++j){
				add(vec[x].back(),vec[arr[j]].back());
				vec[x].pop_back();vec[arr[j]].pop_back();
			}
		}
		sol();
	}
	for(int i=1;i<=n;++i) vec[i].clear();
	for(int i=1;i<=n;++i) vec[rt(i)].emplace_back(i);
	for(int i=1;i<=n;++i)
		if(vec[i].size()*2>n) for(int x:vec[i]) ans[x]=1;
	printf("answer ");
	for(int i=1;i<=n;++i)
		printf("%d",ans[i]);
	putchar('\n');
	fflush(stdout);
#ifdef LOCAL
	for(int i=1;i<=n;++i) assert(ans[i]==res[i]);
#endif 
}
int main(){
	int tc=read();
	while(tc--) solve();
	return 0;
}
```

---

