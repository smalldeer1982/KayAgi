# 「Wdcfr-1」Magical Expression

## 题目描述

妮特莉正在学习后缀表达式。她有一个长度为 $n$ 的不完整后缀表达式 $E$。作为妖怪，她想要找到它的魔法属性。

她的后缀表达式包含按位或运算符（记作 `|`）、按位与运算符（记作 `&`），以及数字 `0` 和 `1`。由于不完整，一些运算符尚未决定，用 `?` 表示。她保证 $E$ **在你完成它之后将成为一个*有效*的后缀表达式**。

在这个问题中，术语*子串*定义为 $E$ 的一个连续片段。**只要位置或长度不同，两个子串就被认为是不同的。**所以 `1?0`，`01?0` 都是 `01?01?|` 的子串，但 `0101` 不是。

妮特莉发现她的表达式的一个子串是*魔法的*，当且仅当满足以下条件：

- 在将 `?` 替换为 `&` 或 `|` 后，可以将其转换为一个*有效*的后缀表达式。
- 在这些转换中，至少能找到一种转换，使得应用后表达式的结果为 $0$，并且至少能找到一种转换，使得应用后表达式的结果为 $1$。

你的任务是找出*魔法的*子串的数量。

## 说明/提示

### 约束条件

$1\le T,n\le 2\times 10^6$。所有测试用例的 $n$ 之和 $\le 2\times 10^6$。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
2
3 01?
7 01?01?|```

### 输出

```
1
3```

# 题解

## 作者：卷王 (赞：7)

## 题目大意

[传送门](https://www.luogu.com.cn/problem/P7941)

给你一段合法后缀表达式，包括 `|`、`&` 和 `?`，以及两个数字 $0,1$，现在请问有多少个 **子串**，满足把 `?` 替换成 `|` 或 `&` 后结果既能是 $0$，也能是 $1$。

## 大体思路

显然是编译原理题了。（建议升绿）

编译原理题的通用思维：

* 中缀转后缀

* 后缀转表达式树

* 表达式树求值

其中这题已经给了后缀，所以第一步可以省略。

又可以发现其中隐藏的贪心：凑成 $0$ 的时候用 `&` 最优，凑成 $1$ 的时候用 `|` 最优。这个应该比较明显。

那不就好了吗？

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
int T;
struct node { int l, r; char x; } a[2000007];
stack<int> st;
int ok[2][2000007];
inline void dfs(int t, bool lxl) { //用大(qing)佬(wa) lxl 的名字作为变量名 
	//lxl 为 1 表示把 ? 替换成 |，为 0 表示替换成 & 
	if(a[t].l == -1) { ok[lxl][t] = a[t].x - '0'; return; }
	dfs(a[t].l, lxl); dfs(a[t].r, lxl); //首先得遍历到底 
	char ch = a[t].x;
	//注意！！外面一定要套一个 ok 数组，a[t].l 不是答案！ 
	int left = ok[lxl][a[t].l];
	int right = ok[lxl][a[t].r];
	if(ch == '&') ok[lxl][t] = left & right;
	if(ch == '|') ok[lxl][t] = left | right;
	if(ch == '?') {
		if(lxl == 0) ok[lxl][t] = left & right;
		else ok[lxl][t] = left | right;
	}
}
int main() {
	speed: std::ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> T;
	while(T--) { //对于每组询问 
		int n; cin >> n;
		string s; cin >> s;
		while(!st.empty()) st.pop(); //多测不清空，爆零两行泪 
		for(int i = 0; i < n; i++) {
			char ch = s[i];
			if(isdigit(ch)) { a[i] = ((node){-1, -1, ch}); st.push(i); continue; }
			a[i].l = st.top(); st.pop(); //否则就是 ? 或 | 或 & 
			a[i].r = st.top(); st.pop(); //弹栈记录两个节点 
			a[i].x = ch; st.push(i);
		} int ans = 0;
		dfs(n - 1, 0); dfs(n - 1, 1);
		//ok 是计算结果 
		for(int i = 0; i < n; i++) if(ok[0][i] != ok[1][i]) ans++;
		cout << ans << "\n";
	}
	return 0;
}
```

---

## 作者：幽云蓝 (赞：6)

此题还存在一种贪心做法。

容易发现把所有 `?` 换成 `|` 结果最有可能是 $1$，都换成 `&` 结果最有可能是 $0$。直接建出表达式树然后进行两次 dfs 即可。

代码如下：

```cpp
#include <bits/stdc++.h>
#define Mashu cout << "UUZ has eaten it." << endl
#define ll long long
using namespace std;

struct qwq{
	char x;
	int ls, rs;
}node[2000010];

int stk[2000010];
int top = 0;
int v[2][2000010];

void dfs0(int now){
	if (node[now].ls != -1){
		dfs0(node[now].ls);
		dfs0(node[now].rs);
		switch(node[now].x){
			case '|':{
				v[0][now] = v[0][node[now].ls] | v[0][node[now].rs];
				break;
			}
			case '&':{
				v[0][now] = v[0][node[now].ls] & v[0][node[now].rs];
				break;
			}
			case '?':{
				v[0][now] = v[0][node[now].ls] & v[0][node[now].rs];
				break;
			}
		}
	}
	else{
		v[0][now] = node[now].x - '0';
	}
}

void dfs1(int now){
	if (node[now].ls != -1){
		dfs1(node[now].ls);
		dfs1(node[now].rs);
		switch(node[now].x){
			case '|':{
				v[1][now] = v[1][node[now].ls] | v[1][node[now].rs];
				break;
			}
			case '&':{
				v[1][now] = v[1][node[now].ls] & v[1][node[now].rs];
				break;
			}
			case '?':{
				v[1][now] = v[1][node[now].ls] | v[1][node[now].rs];
				break;
			}
		}
	}
	else{
		v[1][now] = node[now].x - '0';
	}
}


int main(){
	int t;
	cin >> t;
	while (t--){
		int n;
		string s;
		cin >> n >> s;
		top = 0;
		for (int i = 0; i < n; i++){
			node[i].x = s[i];
			if (s[i] == '0' || s[i] == '1'){
				node[i].ls = -1;
				node[i].rs = -1;
				stk[++top] = i;
			}
			else{
				node[i].ls = stk[top];
				top--;
				node[i].rs = stk[top];
				top--;
				stk[++top] = i;
			}
		}
		dfs0(n - 1);
		dfs1(n - 1);
		int ran = 0;
		for (int i = 0; i < n; i++) if (v[0][i] != v[1][i]) ran++;
		cout << ran << endl;
	}
	return 0;
	Mashu;
}
```

---

## 作者：lmgoat (赞：4)

### 题意
给出一个合法后缀表达式，包含 0,1,\&,|,? 。| 表示或运算，\& 表示与运算， ? 两者都可。问有多少段合法子串的值既能为 1 又能为 0 。
### 思路
既然是后缀表达式，就可以想到用栈模拟。又因为一个子串的信息是由它的子串推出，就可以想到树形 DP 。

考虑建树：栈模拟的时候，每遇到一个表达式，就赋予这个表达式一个新的编号，如果是单独的一个值就给这个编号打个标记。如果有符号的就把它的编号与栈顶的两个表达式的编号分别连一条边，连边的时候记录一下是哪种符号。

显然这棵树一定是一棵二叉树，所以 DP 部分就很简单了。$f[i][0/1]=0/1$ 表示编号为 i 的表达式能/不能为 0/1 。$op=0/1/2$ 表示这条边的符号为 |/\&/? ，x 为当前节点编号，y 为左儿子编号， z 为右儿子编号，转移如下：

```cpp
if(op==0) {
	if(f[y][0]&&f[z][0]) f[x][0]=1;
	if(f[y][1]||f[z][1]) f[x][1]=1;
}
else if(op==1) {
	if(f[y][0]||f[z][0]) f[x][0]=1;
	if(f[y][1]&&f[z][1]) f[x][1]=1;
}
else {
	if(f[y][0]||f[z][0]) f[x][0]=1;
	if(f[y][1]||f[z][1]) f[x][1]=1;
}
```

如果 $f[x][0]=f[x][1]=1$ 那么 $ans+1$ 。

注意清空数组的时候不要用 memset , 因为 t 的数据范围很大，所以用多少清多少，不然会 TLE。
 
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pr;
int read() {
	int x=0,f=0;
	char ch=getchar();
	while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
	return f?-x:x;
}
const int N=2000005;
int t,n,a[N];
int sta[N<<1],top,tot,cnt,root,ans,p[N<<1];
char s[N];
bool f[N<<1][2];
vector<pr> g[N<<1];
map<char,int> mp;
void dfs(int x,int fa) {
	if(p[x]) {
		f[x][a[p[x]]]=1;
		return;
	}
	int y,z,op,siz=g[x].size();
	y=g[x][siz-2].first,z=g[x][siz-1].first,op=g[x][siz-1].second;
	dfs(y,x),dfs(z,x);
	if(op==0) {
		if(f[y][0]&&f[z][0]) f[x][0]=1;
		if(f[y][1]||f[z][1]) f[x][1]=1;
	}
	else if(op==1) {
		if(f[y][0]||f[z][0]) f[x][0]=1;
		if(f[y][1]&&f[z][1]) f[x][1]=1;
	}
	else {
		if(f[y][0]||f[z][0]) f[x][0]=1;
		if(f[y][1]||f[z][1]) f[x][1]=1;
	}
	if(f[x][0]&&f[x][1]) ++ans;
}
signed main() {
	t=read();
	mp['|']=0,mp['&']=1,mp['?']=2;
	while(t--) {
		n=read();
		scanf("%s",s+1);
		cnt=0;
		for(int i=1,x,y,op;i<=n;++i) {
			if(s[i]=='0'||s[i]=='1') ++tot,p[++cnt]=tot,sta[++top]=cnt,a[tot]=s[i]-'0';
			else {
				x=sta[top],y=sta[top-1],op=mp[s[i]],--top;
				sta[top]=++cnt;
				g[cnt].push_back(pr(x,op)),g[cnt].push_back(pr(y,op));
			}
		}
		root=cnt,ans=0;
		for(int i=1;i<=cnt;++i) f[i][0]=f[i][1]=0;
		dfs(root,0);
		for(int i=1;i<=cnt;++i) p[i]=0;
		printf("%d\n",ans);
	}
	return 0;
}
```


---

## 作者：__LePetitPrince__ (赞：3)

看这题各位 dalao 的方法都是 dfs 或者 dp 阿，而且代码都是做的表达式树比较复杂，我这里提供一种比较新奇的思路。

首先这里有一个我苦苦思考得出 ~~dalao 秒出~~的规律：

在一个合法的后缀表达式里，如果一位是符号位，那么一定存在一个唯一的子串以这一位为结尾，使得这个子串是一个合法的后缀表达式。

这个结论我在现有题解里都没翻到，证明本质上就是根据后缀表达式解析的唯一性（就是一个后缀表达式对应一个唯一的表达式树），如果一个符号位对应了不止一个子串那解析出来就不合法或者会引发歧义了，但显然一个合法的后缀表达式解析过程肯定是合法的并且有唯一的结果。

贪心过程其他题解都提到了，让 `?` 都变成 `&` 可以让结果为 $0$ 的概率最大，让 `?` 都变成 `|` 可以让结果为 $1$ 的概率最大，我就不多说了。

题目中给的是后缀表达式，实际上已经是一个表达式树了，用一个栈就很好解析了，不一定非要把真正的树结构建出来。

实现贪心用 $2$ 个栈记录，一个栈记录 `?` 全填 `&` 的情况，另一个记录全填 `|` 的情况。

显然只有一个符号位才可能作为一个后缀表达式的结尾，于是我们可以遍历一遍整个字符串，遇到符号位先计算，然后判断两个栈里面是不是一个是 $0$ 一个是 $1$。

时间复杂度 $O(n)$，符合题目要求。

细节可以看代码：

```
#include <iostream>
#include <string>
#include <stack> 
using namespace std;
int T, n;
string s;
void sol() {
	cin >> n >> s;
	stack<int> ast, ost;
	// ast: and stack, ? 填 & 的情况 
	// ost: or stack, ? 填 | 的情况
	// 解析过程：如果当前位是数字，放进栈里；如果是符号，提出栈顶俩数字，算完了再压进栈，因为都符合交换律，不用管顺序 
	int t1, t2, ans = 0;
	for (auto c : s) {
		if (c == '0' || c == '1') ast.push(c - '0'), ost.push(c - '0'); // 数字位 
		else if (c == '?') {
			t1 = ast.top(); ast.pop();
			t2 = ast.top(); ast.pop();
			ast.push(t1 & t2); // ? 填 & 
			t1 = ost.top(); ost.pop();
			t2 = ost.top(); ost.pop();
			ost.push(t1 | t2); // ? 填 | 
			if (ast.top() ^ ost.top()) ans++; // xor: 两者不同为 1；即俩栈顶一个是 1 一个是 0，是符合要求的子串 
		} else if (c == '|') {
			t1 = ast.top(); ast.pop();
			t2 = ast.top(); ast.pop();
			ast.push(t1 | t2); // 已经给成 | 了，所以 and 也要按或算 
			t1 = ost.top(); ost.pop();
			t2 = ost.top(); ost.pop();
			ost.push(t1 | t2);
			if (ast.top() ^ ost.top()) ans++;
		} else if (c == '&') {
			t1 = ast.top(); ast.pop();
			t2 = ast.top(); ast.pop();
			ast.push(t1 & t2);
			t1 = ost.top(); ost.pop();
			t2 = ost.top(); ost.pop();
			ost.push(t1 & t2); // 已经给成 & 了，所以 or 也要按与算 
			if (ast.top() ^ ost.top()) ans++;
		}
	}
	cout << ans << endl;
}
int main() {
	cin >> T;
	while (T--) sol();
	return 0;
} 
// turn all ? to |, the largest probability for being 1
// turn all ? to &, the largest probability for being 0
// imo, an operator can only be the end of a single substring
// 11 01?01??01??
```

第一次写题解希望能过 UwU

---

## 作者：yzy1 (赞：2)

首先考虑什么样的表达式是一个结果一定为 $0$，什么样的一定为 $1$，什么样的既可以为 $0$ 也可以为 $1$。

- 如果运算符为 `?`，则如果左操作数和右操作数确定且相同，则结果一定为左操作数。否则结果可以是 $0$ 或 $1$。
- 如果运算符为 `&`，且左右操作数中至少有一个确定为 $0$，则结果一定为 $0$。否则如果两个操作数均确定，则结果为两操作数按位与的结果。否则结果可以是 $0$ 或 $1$。
- 如果运算符为 `|`，且左右操作数中至少有一个确定为 $1$，则结果一定为 $1$。否则如果两个操作数均确定，则结果为两操作数按位或的结果。否则结果可以是 $0$ 或 $1$。

我们可以先建立出表达式树，从叶子节点到根节点依次转移即可。

```cpp
char s[N], typ[N];
int n, ls[N], rs[N], tp, ans[N];

inline int And(int x, int y) { return (x == 0 || y == 0) ? 0 : max(x, y); }
inline int Or(int x, int y) { return (x == 1 || y == 1) ? 1 : max(x, y); }

int Dfs(int x) {
  if (x <= 0) return -x;
  int l = Dfs(ls[x]), r = Dfs(rs[x]);
  if (typ[x] == '&') return ans[x] = And(l, r);
  if (typ[x] == '|') return ans[x] = Or(l, r);
  return ans[x] = ((And(l, r) == Or(l, r)) ? And(l, r) : 2);
}

signed main() {
  int T;in(T);while(T--) {
    vector<int> vec;
    in(n)(s + 1);
    re (i, n) {
      if (s[i] == '0' || s[i] == '1')
        vec.push_back(-(s[i] - '0'));
      else
        typ[++tp] = s[i], ls[tp] = vec.back(), vec.pop_back(), rs[tp] = vec.back(), vec.back() = tp;
    }
    Dfs(tp);
    int res = 0;
    re (i, tp)
      if (ans[i] == 2) ++res;
    out(res)('\n');
    rep (i, 0, n + 1)
      s[i] = 0, typ[i] = 0, ls[i] = 0, rs[i] = 0, ans[i] = 0;
    tp = 0, n = 0;
  }
  return 0;
}
```

---

## 作者：lin_A_chu_K_fan (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P7941)
# 题意
给一个合法的后缀表达式，包括 `|`、`&`、`?`，以及数字 $0$ 和 $1$。现在问其有多少个子串满足把 `?` 替换成 `|` 或 `&` 后这个表达式的值既能为 $0$ 又能为 $1$。
# 思路
可以贪心。

可以发现结果最可能为 $0$ 的情况是所有的 `?` 全都变成 `&`，最可能为 $1$ 的情况是全都变成 `|`，所以可以建表达式树然后 dfs 即可。

代码就不放了，求关~

---

## 作者：Binaerbaka (赞：1)

## 蒟蒻版描述
##### 只有可怜四篇题解且上树处理不是很懂，故肝此解。
~~为了给蒟蒻讲用不复杂的处理 故肝此解。~~

[纯享版](https://www.luogu.com.cn/blog/Binaerbaka/p7941-ti-xie)

## 题意
在给定的后缀表达式中，找出能使运算数既为 $1$ 又为 $0$ 的可行子串。

## 理解
- 当 ```&``` 左右只要有一个 $0$ 另外一个既可以为 $0$ 又可以为 $1$。
- 当 ```|``` 左右只要有一个 $1$ 同上。

若假设所有子串都是可行的，则只需要找到那些不可行的子串即可 也就是上述的逆定理。

**tips：每个子串的运算符只能是 ```& |``` 所以不妨搜索时搜索两次可以包含所有情况的极端。**
## 思路

先构建一个简单的表达式树，运算符左右孩子是运算数，值为运算结果，运算数值为本身。

进行搜索，搜索整颗树中有多少格式符合要求的子串。

进行两次搜索，减去树中不符合的子串数。
## Main std
#### 建树：
```cpp
char s;
cin>>s;
if(s=='0'||s=='1'){
	stk.push(++cnt);
	node[cnt]={0,0,s-'0'}; //运算数节点是叶结点且值为本身。
}
else{
	int now1,now2; //取出顶部的两个节点，因为是后序输入。
	now1=stk.top();
	stk.pop();
	now2=stk.top();
	stk.pop();
	stk.push(++cnt); //创建一个运算符节点。
	node[cnt]={now1,now2,s};
}
```

#### 预搜索：
```cpp
void Pre(int x){ //搜索所有方案预处理。
	if(x==0)return;
	if(!node[x].lc&&!node[x].rc){
		val[x]=node[x].v;
		return ;
	} //如果是运算数节点则停止，且值为本身。
	Pre(node[x].lc); //根左右的先序遍历。
	Pre(node[x].rc);
	ans++; //假设子串可行。
}
```

#### 搜索全是 ```&``` 的不可行发案
```cpp
void dfsAnd(int x){ //搜索所有 ? 为 & 的方案。
	if(x==0)return ;
	if(!node[x].lc&&!node[x].rc)return;
	 //因为要先求出运算符的子节点的值，所以要先算到底
	dfsAnd(node[x].lc);
	dfsAnd(node[x].rc);
	if(node[x].v=='|')val[x]=val[node[x].lc]||val[node[x].rc]; //本身是 | 运算。
	else val[x]=val[node[x].lc]&&val[node[x].rc]; //本身是 & 或 ? 假设是 & 后运算。
	if(val[x]==1)ans--; //说明 && 两边都是 1 不是可行方案。
}
```
**搜索 ```|``` 与上相似，反转即可。**

然后就输出结果即可。

祝大家早日通过。




---

## 作者：tzl_Dedicatus545 (赞：1)

因为这道题让求一个表达式，我们很容易可以想到上树处理，如下：

- 对于全 $1$ 的情况，容易发现无论如何将 $\texttt{?}$ 替换成 $\texttt{|}$ 是比较划算的，原因显然。

- 对于全 $0$ 的情况，容易发现无论如何将 $\texttt{?}$ 替换成 $\texttt{\&}$ 是比较划算的，原因同样显然。

因此我们做两次 dfs 后统计满足两个条件的答案即可，代码：

```cpp
//By: Luogu@⚡炭治郎⚡(a.k.a. Kamado_Tanjiro)(LuoguID:308854)
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int INF=(sizeof(int)==4?0x3f3f3f3f:0x3f3f3f3f3f3f3f3f);
const int MOD=998244353;
const long double EPS=1e-7;

struct Tree
{
	int lc,rc,val;
}pool[3000000];
int nowid=0;
bool vals[3000000];
int sum=0;

void dfsPre(int u)
{
	if(u==0)
		return ;

	if(pool[u].lc==0 && pool[u].rc==0)
	{
		vals[u]=pool[u].val;
		return ;
	}

	dfsPre(pool[u].lc);
	dfsPre(pool[u].rc);

	sum++;
}

void dfsAnd(int u)
{
	if(u==0)
		return ;

	if(pool[u].lc==0 && pool[u].rc==0)
	{
		return ;
	}

	dfsAnd(pool[u].lc);
	dfsAnd(pool[u].rc);

	if(pool[u].val=='|')
		vals[u]=vals[pool[u].lc] || vals[pool[u].rc];
	else
		vals[u]=vals[pool[u].lc] && vals[pool[u].rc];

	if(vals[u]!=0)
		sum--;
}

void dfsOr(int u)
{
	if(u==0)
		return ;

	if(pool[u].lc==0 && pool[u].rc==0)
	{
		return ;
	}

	dfsOr(pool[u].lc);
	dfsOr(pool[u].rc);

	if(pool[u].val=='&')
		vals[u]=vals[pool[u].lc] && vals[pool[u].rc];
	else
		vals[u]=vals[pool[u].lc] || vals[pool[u].rc];

	if(vals[u]!=1)
		sum--;
}

signed main()
{
	int T;

	cin>>T;

	while(T--)
	{
		nowid=0;
		sum=0;

		int n;
		stack<int> s;

		cin>>n;

		for(int i=1;i<=n;i++)
		{
			char op;

			cin>>op;

			if(op=='0' || op=='1')
			{
				s.push(++nowid);
				pool[nowid]={0,0,op-'0'};
			}
			else
			{
				int rc=s.top();
				s.pop();
				int lc=s.top();
				s.pop();

				s.push(++nowid);

				pool[nowid]={lc,rc,op};
			}
		}

		int root=s.top(),ans=0;

		s.pop();

		dfsPre(root);

		//cout<<sum<<endl;

		dfsAnd(root);
		dfsOr(root);

		cout<<sum<<endl;
	}



	return 0;
}
```



---

## 作者：Ruiqun2009 (赞：0)

首先要讲 逻辑运算符的短路 性质。

今年 CSP-J2022 T3 考到了这个性质。在你谷题目编号为 [P8815](https://www.luogu.com.cn/problem/P8815)。

原文：

> 此外，在 C++ 等语言的有些编译器中，对逻辑表达式的计算会采用一种“短路”的策略：在形如 $a\&b$ 的逻辑表达式中，会先计算 $a$ 部分的值，如果 $a = 0$，那么整个逻辑表达式的值就一定为 $0$，故无需再计算 $b$ 部分的值；同理，在形如 $a \mid b$ 的逻辑表达式中，会先计算 $a$ 部分的值，如果 $a = 1$，那么整个逻辑表达式的值就一定为 $1$，无需再计算 $b$ 部分的值。

~~这个东西在卡常时有用~~ 交换两个逻辑表达式的顺序可能会让性能有巨大的提升。

那么我们就只需要对表达式树进行搜索，看有多少个节点在将所有 `?` 替换成 `|` 和将所有 `?` 替换成 `&` 时的值不相同。这次搜索可以并行处理。

其次，对于后缀表达式建表达式树就是用一个栈模拟，然后看到一个运算符就去出栈顶的两个元素然后将构建好的节点再次入栈。最后取出栈顶作为根节点就大功告成了。

代码：（写的指针版表达式树，~~为防止内存泄漏~~ 用的 `unique_ptr`，使用函数指针传函数 ~~lambda 表达式可以用 `std::function` 传进去，可以看 [浅谈珂朵莉树](https://www.luogu.com.cn/blog/_post/446071)~~）
```cpp
#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;
template <typename _CharT = char>
class expression_tree {
    struct node { // 我真的想写 class，但是那样管理太烦
        char c;
        bool value1, value2;
        node *left, *right;
        node() = default;
        node(char ch = '\0', bool v1 = false, bool v2 = false, node *l = 0, node *r = 0)
            : c(ch), value1(v1), value2(v2), left(l), right(r) {}
        inline void pushup(bool(*func1)(bool, bool), bool(*func2)(bool, bool)) {
            switch (c) {
                case '|': {
                    value1 = left->value1 || right->value1;
                    value2 = left->value2 || right->value2;
                    break;
                }
                case '&': {
                    value1 = left->value1 && right->value1;
                    value2 = left->value2 && right->value2;
                    break;
                }
                case '?': {
                    value1 = func1(left->value1, right->value1);
                    value2 = func2(left->value2, right->value2);
                    break;
                }
            }
        }
        inline void dfs(bool(*func1)(bool, bool), bool(*func2)(bool, bool)) {
            if (left) {
                left->dfs(func1, func2);
                right->dfs(func1, func2);
                pushup(func1, func2);
            }
            else value1 = value2 = c & 1;
        }
        template <typename _Ostream>
        friend inline _Ostream& operator<<(_Ostream& os, node* o) {
            if ((long long)(o->left) > 0) os << o->left;
            os << o->value1 << ' ' << o->value2 << ' ';
            if ((long long)(o->right) > 0) os << o->right;
            return os;
        }
    };
public:
    node *root;
    inline void dfs(bool(*func1)(bool, bool), bool(*func2)(bool, bool)) { root->dfs(func1, func2); }
    inline size_t count_nequal() const {
        struct __DFS__ {
            inline size_t dfs(node *nd) {
                if (!nd) return 0;
                size_t ans = 0;
                if (nd->value1 != nd->value2) ++ans;
                ans += dfs(nd->left);
                ans += dfs(nd->right);
                return ans;
            }
            inline __DFS__() {}
        };
        static __DFS__ dfs_helper;
        return dfs_helper.dfs(root);
    }
    inline void suffix_build(const basic_string<_CharT>& str)
    {
        vector<unique_ptr<node> > stk;
        for (size_t i = 0, iend = str.size(); i < iend; i++) {
            if (str[i] == '0' || str[i] == '1') stk.emplace_back(new node(str[i], str[i] & 1, str[i] & 1, 0, 0));
            else {
                node *ltmp = stk.back().release();
                stk.pop_back();
                node *rtmp = stk.back().release();
                stk.pop_back();
                stk.emplace_back(new node(str[i], str[i] & 1, str[i] & 1, ltmp, rtmp));
            }
        }
        root = stk.back().release();
    }
};
bool func1(bool a, bool b) { return a || b; }
bool func2(bool a, bool b) { return a && b; }
void solve() {
    string s;
    int n;
    cin >> n >> s;
    expression_tree<char> tree;
    tree.suffix_build(s);
    tree.dfs(func1, func2);
    cout << tree.count_nequal() << endl;
}
int main() {
    cin.tie(0)->sync_with_stdio(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--) solve();
    cout << flush;
}
```
`unique_ptr` 是一种行为类似 `auto_ptr` 的智能指针，但是将内部所有操作变为移动语义。`auto_ptr` 被废弃的原因就是因为没有使用移动语义。这个可以看 `move()`（即移动）和 `forward()`（即完美转发）。虽然内部只是一个 `static_cast`，但是与迭代器搭配使用时可以提高很多效率（例如 `std::sort`（内部使用 `move()` 赋值）比直接赋值的手写内省排序快约 $3\%$）。

这里顺便说一下 `unique_ptr` 的用法：（有对数组的特化，只需要将 `operator new` 和 `operator delete` 改成 `operator new[]` 和 `operator delete[]`）

- 构造函数：过于复杂，可以看 [cppreference 上关于 `unique_ptr` 的构造函数的简介](https://zh.cppreference.com/w/cpp/memory/unique_ptr/unique_ptr)。
- 析构函数：若内部存储的指针不为 `nullptr` 则删除这个指针（默认使用 `operator delete`）。
- 赋值运算符：接受一个 `unique_ptr&&`（注意，只支持移动语义）或一个 `nullptr`（不进行任何操作，即调用 `reset(nullptr)`）。首先将内部存储的指针变为给定的 `unique_ptr` 内部存储的指针，然后将给定的 `unique_ptr` 析构。
- `release()`：返回指向的内存。返回后会将内部存储的指针设为 `nullptr`。
- `get()`：返回指向的内存，但是不将内部存储的指针设为 `nullptr`。
- `reset(ptr)`：将原指针所指的内存删除（默认使用 `operator delete`），然后替换为 `ptr`。
- `operator bool`：顾名思义，将 `unique_ptr` 变成一个 `bool` 类型。作用为查看内部存储的指针是否为 `nullptr`（即 `get() == nullptr`）。

对于指针版本：
- `operator*()`、`operator->()`：和普通指针相同。

对于数组版本：
- `operator[]`：和普通数组一样。

---

