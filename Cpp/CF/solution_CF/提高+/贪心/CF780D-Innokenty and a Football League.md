# Innokenty and a Football League

## 题目描述

Innokenty is a president of a new football league in Byteland. The first task he should do is to assign short names to all clubs to be shown on TV next to the score. Of course, the short names should be distinct, and Innokenty wants that all short names consist of three letters.

Each club's full name consist of two words: the team's name and the hometown's name, for example, "DINAMO BYTECITY". Innokenty doesn't want to assign strange short names, so he wants to choose such short names for each club that:

1. the short name is the same as three first letters of the team's name, for example, for the mentioned club it is "DIN",
2. or, the first two letters of the short name should be the same as the first two letters of the team's name, while the third letter is the same as the first letter in the hometown's name. For the mentioned club it is "DIB".

Apart from this, there is a rule that if for some club $ x $ the second option of short name is chosen, then there should be no club, for which the first option is chosen which is the same as the first option for the club $ x $ . For example, if the above mentioned club has short name "DIB", then no club for which the first option is chosen can have short name equal to "DIN". However, it is possible that some club have short name "DIN", where "DI" are the first two letters of the team's name, and "N" is the first letter of hometown's name. Of course, no two teams can have the same short name.

Help Innokenty to choose a short name for each of the teams. If this is impossible, report that. If there are multiple answer, any of them will suit Innokenty. If for some team the two options of short name are equal, then Innokenty will formally think that only one of these options is chosen.

## 说明/提示

In the first sample Innokenty can choose first option for both clubs.

In the second example it is not possible to choose short names, because it is not possible that one club has first option, and the other has second option if the first options are equal for both clubs.

In the third example Innokenty can choose the second options for the first two clubs, and the first option for the third club.

In the fourth example note that it is possible that the chosen short name for some club $ x $ is the same as the first option of another club $ y $ if the first options of $ x $ and $ y $ are different.

## 样例 #1

### 输入

```
2
DINAMO BYTECITY
FOOTBALL MOSCOW
```

### 输出

```
YES
DIN
FOO
```

## 样例 #2

### 输入

```
2
DINAMO BYTECITY
DINAMO BITECITY
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
3
PLAYFOOTBALL MOSCOW
PLAYVOLLEYBALL SPB
GOGO TECHNOCUP
```

### 输出

```
YES
PLM
PLS
GOG
```

## 样例 #4

### 输入

```
3
ABC DEF
ABC EFG
ABD OOO
```

### 输出

```
YES
ABD
ABE
ABO
```

# 题解

## 作者：Enzyme125 (赞：2)

首先，这道题目说了一个特别限制，明显降低了难度。



# 提供两个思路，三个写法




## 思路一 . 先选第一构造，冲突了选第二构造

一对字符串有两种构造方式
如果第一种可以选，就把它加入一个集合。
如果第一种不能选（集合中已经存在），把原先的取出来加入第二个构造，然后递归操作乱搞一番

当然，乱搞的结果就是码力惊人+ WA

实际情况是，我WA在了第16个点。

下面是WA的代码
```C++
#include<iostream>
#include<string>
#include<set>
#include<map>
using namespace std;
const int maxn = 1000 + 10;
string fir[maxn]; 
string sec[maxn];
map<string,int> mp;
set<string> flag,S;
int chs[maxn]; 
bool ff(string s){ // flag string s
	flag.insert(s);
	if(S.count(s)){
		int id = mp[s];
//		cout << "id = " << id << endl;
		if(id == -1) return false;
		S.erase(s);
		mp[fir[id]] = -1;
		if(S.count(sec[id])){
			
			return false;
		}
		S.insert(sec[id]);
		chs[id] = 1;
		ff(fir[id]);
		
		mp[sec[id]] = -1;
	}
}
int main(){
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	for(int i = 1;i <= n;i++){
		string a,b;
		cin >> a >> b;
		fir[i] = a.substr(0,3);
		sec[i] = a.substr(0,3);
		sec[i][2] = b[0];
	}
	for(int i = 1;i <= n;i++){
		if(S.count(fir[i]) || flag.count(fir[i])){
			ff(fir[i]);
			if(S.count(sec[i])){
				cout << "NO" << endl;
				return 0;
			}
			else S.insert(sec[i]) , chs[i] = 1 , mp[sec[i]] = -1;
		} else {
			chs[i] = 0;
			S.insert(fir[i]);
			mp[fir[i]] = i;
		}
	}
	cout << "YES" << endl;
	for(int i = 1;i <= n;i++){
		if(chs[i]) {
			cout << sec[i];
		} else cout << fir[i];
		cout << endl;
	}
	return 0;
}
```

~~写完以后我都不想承认这是我写的...~~

代码冗长 + 头脑爆炸 ~~真是烂到极致的代码~~


这Write-only的代码还是别看了。

为了代码可读，我重构了代码

换了一种比较优雅的写法，思路和上面大致相同，但是实现起来要清爽很多 ，原理是用一个map保存出现次数，如果次数大于1就全部变成第二构造。~~时间不是最优秀的...管他呢~~

AC代码:

```C++
#include<iostream>
#include<string>
#include<map>
#include<vector>
using namespace std;
typedef pair<string,string> pss;
vector<pss> v;
map<string,int> m;

int main(){
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	string a,b,x,y;
	for(int i= 0;i < n;i++){
		cin >> a >> b;
		x = a.substr(0,3); y = a.substr(0,2) + b.substr(0,1);
		v.push_back(make_pair(x,y));
	}	
	for(int i = 0;i < n;i++){
		for(int j = 0;j < n;j++) m[v[j].first] ++;
		for(int j = 0;j < n;j++) if(m[v[j].first] > 1) v[j].first = v[j].second;
		m.clear();
	}
	for(int i = 0;i < n;i++){
		m[v[i].first]++;
		if(m[v[i].first] > 1) {
			cout << "NO";
			return 0;
		}
	}
	cout << "YES" << endl;
	for(int i = 0;i < n;i++){
		cout << v[i].first << endl;
	}
	return 0;
}
```


## 思路二:   贪心，优先选择第二构造，再选择第一构造.


这是一个故事，打完这场以后我去翻了翻提交记录，看到一个骚气无比的贪心做法
http://codeforces.com/contest/781/submission/25464818

代码是这样的:
```C++
#include<bits/stdc++.h>
using namespace std;
map<string,int>used,cant;
int n;
int main(){
	cin>>n;
	vector<string>anss;
	for(int i=1;i<=n;i++){
		string ans,a,b;
		cin>>a>>b;
		a=a.substr(0,3);
		b=a.substr(0,2)+b.substr(0,1);

		if(!used[b]){
			used[b]=1;
			ans=b;
		}else{
			if(used[a]||cant[a]){
				puts("NO");
				return 0;
			}else{
				used[a]=1;
				ans=a;
			}
		}
		cant[a]=1;
		anss.push_back(ans);
		//cout<<ans<<endl;
	}
	puts("YES");
	for(auto s:anss)
		cout<<s<<endl;
	return 0;
}
```
并且获得了AC.


我尝试了大力证明贪心正确，随便造了组数据


发现....




hack数据

```
3
XXF CXX
XXB XXX
XXB CXX
```







---

## 作者：sgl654321 (赞：1)

### 题目大意
每一个球队有两个备选名称 $A_i,B_i$，请你们为每个球队确定一个名称，满足下列条件。

- 每个球队的名称都不能相同。
- 如果球队 $i$ 选择了名称 $B_i$，那么另一个球队 $j$ 即不能选择名称 $A_j$，其中 $A_j = A_i$。
- 如果球队 $i$ 选择了名称 $B_i$，那么另一个球队**也可以**选择名称 $B_j$，其中 $B_j = A_i$。

确认是否存在方案，输出方案。

### 解题思路
首先，对于 $A$ 相同的那些球队，它们都只能选择 $B_i$ 这个名称，不然，就会与第一个限制或者第二个限制相冲突。

把这些球队的名称确定之后，还剩下一些 $A$ 独立的球队。再次进行 $n$ 次遍历，每次判断这个球队是否还能定下名称。如果能的话就先定下来。

接着就转化成了一个 2-SAT 模型。你只需要考虑第一个限制就行了。对于每个球队 $i$ 建立两个点 $i$ 和 $i + n$，一个点代表选 $A$，另一个点代表选 $B$。

如果 $A_i = B_j$，那么 $i$ 和 $j$ 连有向边， $j + n$ 和 $i + n$ 连有向边。$A_i=A_j$，$B_i = A_j$，$B_i = B_j$ 都是同理的。这里默认大家都会 2-SAT 了。

这里的时间复杂度为 $O(n ^ 2)$。

### 参考代码
```cpp
#include<bits/stdc++.h>
#define maxn 2010
#define maxm 2000010
using namespace std;
typedef long long ll;

struct node{
	string s, t;
} a[1010];
ll n, c[1010], tot, x;
string s1, s2;
map<string, ll> mp;
map<string, bool> vis; 
vector<ll> ve[1010];
ll kk, poi[maxn], v[maxm], nex[maxm];
ll cnt, dfn[maxn], low[maxn], sta[maxn], nn, color[maxn];
bool insta[maxn];

void add_edge(ll x, ll y){
	kk++; v[kk] = y; nex[kk] = poi[x]; poi[x] = kk; 
} 
void tarjan(ll x){
	cnt++; dfn[x] = low[x] = cnt; tot++; sta[tot] = x; insta[x] = 1;
	ll save = poi[x];
	while(save){
		if(!dfn[v[save]]) tarjan(v[save]), low[x] = min(low[x], low[v[save]]);
		else if(insta[v[save]]) low[x] = min(low[x], dfn[v[save]]); 
		save = nex[save];
	}
	if(dfn[x] == low[x]){
		nn++;
		while(sta[tot] != x){
			color[sta[tot]] = nn;
			insta[sta[tot]] = 0; tot--;
		}
		color[x] = nn; insta[x] = 0; tot--;
	}
}

int main(){
	cin >> n;
	for(int i = 1; i <= n; i++){
		cin >> s1 >> s2;
		a[i].s += s1[0]; a[i].s += s1[1]; a[i].s += s1[2];
		a[i].t += s1[0]; a[i].t += s1[1]; a[i].t += s2[0];
		
		
		
		if(mp.find(a[i].s) != mp.end()) ve[mp[a[i].s]].push_back(i);
		else mp[a[i].s] = ++tot, ve[tot].push_back(i);
	}
	for(int i = 1; i <= tot; i++)
		if(ve[i].size() >= 2)
			for(auto j : ve[i]){
				if(vis.find(a[j].t) != vis.end()){
					cout << "NO\n"; return 0;
				}
				vis[a[j].t] = 1;
				c[j] = 2;
			}
	
	for(int i = 1; i <= tot; i++){
		for(int j = 1; j <= tot; j++)
			if(ve[j].size() == 1 && c[ve[j][0]] == 0){
				x = ve[j][0];
			//	cout << x << endl;
				if(vis.find(a[x].s) != vis.end() && 
				vis.find(a[x].t) != vis.end()){
					cout << "NO\n"; return 0;
				}
				if(vis.find(a[x].s) != vis.end())
					vis[a[x].t] = 1, c[x] = 2;
				else if(vis.find(a[x].t) != vis.end())
					vis[a[x].s] = 1, c[x] = 1;
			}
	}
	
	tot = 0;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			if(c[i] == 0 && c[j] == 0){
				if(a[i].s == a[j].s) add_edge(i, j + n), add_edge(j, i + n);
				if(a[i].s == a[j].t) add_edge(i, j), add_edge(j + n, i + n);
				if(a[i].t == a[j].s) add_edge(i + n, j + n), add_edge(j, i);
				if(a[i].t == a[j].t) add_edge(i + n, j), add_edge(j + n, i);
			}
	for(int i = 1; i <= 2 * n; i++) tarjan(i);
	for(int i = 1; i <= n; i++)
		if(c[i] == 0 && color[i] == color[i + n]){
			cout << "NO\n"; return 0;
		}
	for(int i = 1; i <= n; i++)
		if(c[i] == 0){
			if(color[i] < color[i + n]) c[i] = 1;
			else c[i] = 2; 
		}
	cout << "YES\n";
	for(int i = 1; i <= n; i++)
		if(c[i] == 1) cout << a[i].s << '\n';
		else cout << a[i].t << '\n';
				
	return 0;
}


```

---

## 作者：XiaoQuQu (赞：1)

提供一个奇妙的做法。

显然这道题我们应该尽可能选第一种命名，问题在于如何决策每个球队的命名方式。

我们可以优先处理多个重复了第一命名的球队，显然他们都应该被选择为第二命名。

接下来，我们处理那些第一命名并没有重复的球队，但是由于我们在之前令有些球队选择了第二命名，所以这里第一命名有可能重复，也就是这里也要选择第二命名。如果按照顺序依次选择第一命名到第二命名，有可能会出现当前球队的第一命名占用了后续球队的第二命名，导致原本 `YES` 的答案被我们判定为 `NO`。

于是我们可以先让只有一种选择方案的球队先选，接着处理两种都可以选择的球队。这个过程只有一次显然不够，于是我们可以多重复几次这个过程。实测在重复次数 $t\ge 30$ 的时候已经足以通过本题。

```cpp
const int MAXN = 1e3 + 5;
string s[MAXN][2], ans[MAXN];
map<string, int> mp;
set<string> st;
vector<int> v[MAXN];
int n, tot;

void work() {
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> s[i][0] >> s[i][1];
	for (int i = 1; i <= n; ++i) {
		string s1 = s[i][0].substr(0, 3), s2 = s[i][0].substr(0, 2) + s[i][1][0];
		if (mp.find(s1) == mp.end()) mp[s1] = ++tot;
		v[mp[s1]].push_back(i);
	}
	for (int i = 1; i <= tot; ++i) {
		if (v[i].size() > 1) {
			for (auto x:v[i]) {
				string s1 = s[x][0].substr(0, 3), s2 = s[x][0].substr(0, 2) + s[x][1][0];
				if (st.find(s2) != st.end()) return cout << "NO" << endl, void();
				st.insert(s2);
				ans[x] = s2;
			}
		}
	}
	int times = 30; // 控制重复次数
	while (times--) {
		for (int i = 1; i <= tot; ++i) if (v[i].size() == 1) {
			string s1 = s[v[i][0]][0].substr(0, 3), s2 = s[v[i][0]][0].substr(0, 2) + s[v[i][0]][1][0];
			if (ans[v[i][0]] != "") continue;
			if (st.find(s1) == st.end() && st.find(s2) == st.end()) continue;
			if (st.find(s1) == st.end()) st.insert(s1), ans[v[i][0]] = s1;
			else if (st.find(s2) == st.end()) st.insert(s2), ans[v[i][0]] = s2;
			else return cout << "NO" << endl, void();
	 	}
	}
	for (int i = 1; i <= tot; ++i) if (v[i].size() == 1) {
		string s1 = s[v[i][0]][0].substr(0, 3), s2 = s[v[i][0]][0].substr(0, 2) + s[v[i][0]][1][0];
		if (ans[v[i][0]] != "") continue;
		if (st.find(s1) == st.end()) st.insert(s1), ans[v[i][0]] = s1;
		else if (st.find(s2) == st.end()) st.insert(s2), ans[v[i][0]] = s2;
		else return cout << "NO" << endl, void();
	}
	cout << "YES" << endl;
	for (int i = 1; i <= n; ++i) cout << ans[i] << endl;
}
```


---

## 作者：__mcx_ (赞：0)


2-SAT 板子题

设 $S_{i,0},S_{i,1}$ 表示第 $i$ 个人通过两种构造方式得到的字符串。

考虑冲突情况。

令 $i\neq j,p,q\in\{0,1\}$ 分别表示 $i,j$ 选择哪种构造方式，其中 $0$ 表示选取第一种构造方式，$1$ 表示选取第二种构造方式。

当 $S_{i,p}=S_{j,q}$ 时，两者矛盾，这个时候只有 $i$ 选 $p$ 且 $j$ 选 $\neg q$ 或者 $i$ 选 $\neg p$ 且 $j$ 选 $q$ 两种情况。

把第 $i$ 个人拆成 $i$ 和 $i+n$ 两个点分别表示第 $i$ 个人选第一种构造/第二种构造。

按照上述分别向对应点连边。

特殊地，对于题面中 $S_{i,0}=S_{j,0}$ 的情况 我们从 $i$ 到 $j+n$，$j$ 到 $i+n$ 连边，表示如果 $i$ 选第二种构造方式，那么 $j$ 也必须选第二种构造方式。

tarjan 缩点后，对某个人判断 $p$ 和 $\neg p$ 是否在同一强连通分量，如果在，则无解。

至于有解时输出，由前面可知,$p$ 和 $\neg p$ 不在同一个强连通分量中,固定一种偏序关系输出即可。

[code](https://www.luogu.com.cn/paste/r9qqb074)

---

## 作者：wgyhm (赞：0)

# CF780D Innokenty and a Football League 题解

首先将第 $i$ 对字符串的两种构造方式预处理出来，分别为 $A_i,B_i$。

**对于“二选一”，考虑 **$2-SAT$ 。

设函数 $opp(x)=\begin{cases}i+n&1\le i\le n\\i-n&n+1\le i\le 2n\end{cases}$

* 对于特别限制，设 $A_i=A_j,i\not= j$，所以如果选择 $B_i$ ，那么必须选择 $B_j$ 。连边 $(i+n,j+n),(j+n,i+n)$。
* 对于所有构造都不同这个限制，设 $A_{i+n}=B_i,1\le i\le n$ ，如果 $A_i=A_j,i\not= j$ ，那么选择 $A_i$ 就必须选择 $A_{opp(j)}$ ；选择 $A_j$ ，就必须选择 $A_{opp(i)}$ 。所以连边 $(i,opp(j)),(j,opp(i))$。

然后上板子。复杂度 $O(n+m)=O(n^2)$

$Code:$

```cpp
int dfn[maxn],low[maxn],stac[maxn],vis[maxn],scc[maxn],sccnum,times,tot;
int n,h[maxn],head=1;
struct yyy{
	int to,z;
	inline void add(int x,int y){
		to=y;z=h[x];h[x]=head;
	}
}a[maxn*20];
inline void ins(int x,int y){
	a[++head].add(x,y);
	a[++head].add(y,x);
}
string s[2][maxn];
struct node{string s;int id;}f[maxn*2];
inline bool cmp(node x,node y){return x.s<y.s;}
//tarjan你们应该都会
inline int opp(int x){return x>n?x-n:x+n;}
signed main(){
    rg int i,j,k,l;
	rg string s1,s2;
    read(n);
    for (i=1;i<=n;i++){
    	cin>>s1>>s2;
		f[i].s=s1[0];f[i].s+=s1[1];f[i].s+=s1[2];f[i].id=i; 
		s[0][i]=s1[0];s[0][i]+=s1[1];s[0][i]+=s1[2];
		s[1][i]=s1[0];s[1][i]+=s1[1];s[1][i]+=s2[0];
	}//预处理
	sort(f+1,f+1+n,cmp);
	for (i=1;i<n;i++){
		for (j=i;j<n;j++)
		    if (f[j].s!=f[j+1].s) break;
		for (k=i;k<=j;k++)
		    for (l=k+1;l<=j;l++)
		        ins(f[k].id+n,f[l].id+n);
		i=j;
	}
	for (i=1;i<=n;i++) f[i].s=s[0][i],f[i].id=i,f[i+n].s=s[1][i],f[i+n].id=i+n;
	sort(f+1,f+1+2*n,cmp);
	for (i=1;i<n*2;i++){
		for (j=i;j<n*2;j++)
		    if (f[j].s!=f[j+1].s) break;
		for (k=i;k<=j;k++)
		    for (l=k+1;l<=j;l++)
		        a[++head].add(f[k].id,opp(f[l].id)),
	    	    a[++head].add(f[l].id,opp(f[k].id));
	    i=j;
	}//建边
	for (i=1;i<=2*n;i++) if (!dfn[i]) tarjan(i);
    for (i=1;i<=n;i++) if (scc[i]==scc[i+n]) return puts("NO"),0;//判无解
    for (puts("YES"),i=1;i<=n;i++) cout<<s[scc[i]>scc[i+n]][i]<<endl; 
	return 0;
}
```



---

