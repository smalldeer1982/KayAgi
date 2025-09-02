# [ABC314D] LOWER

## 题目描述

给定一个由英文字母大写和小写字母组成的长度为 $N$ 的字符串 $S$。

接下来，将对字符串 $S$ 进行 $Q$ 次操作。第 $i$ 次操作（$1 \le i \le Q$）由两个整数和一个字符组成的三元组 $(t _ i, x _ i, c _ i)$ 表示，每种操作的含义如下：

- 当 $t _ i = 1$ 时，将 $S$ 的第 $x _ i$ 个字符修改为 $c _ i$。
- 当 $t _ i = 2$ 时，将 $S$ 中的所有大写字母全部转为小写（$x _ i$ 和 $c _ i$ 在此操作中不使用）。
- 当 $t _ i = 3$ 时，将 $S$ 中的所有小写字母全部转为大写（$x _ i$ 和 $c _ i$ 在此操作中不使用）。

输出经过 $Q$ 次操作后的字符串 $S$。

## 样例 #1

### 输入

```
7
AtCoder
5
1 4 i
3 0 a
1 5 b
2 0 a
1 4 Y```

### 输出

```
atcYber```

## 样例 #2

### 输入

```
35
TheQuickBrownFoxJumpsOverTheLazyDog
10
2 0 a
1 19 G
1 13 m
1 2 E
1 21 F
2 0 a
1 27 b
3 0 a
3 0 a
1 15 i```

### 输出

```
TEEQUICKBROWMFiXJUGPFOVERTBELAZYDOG```

# 题解

## 作者：guanyf (赞：4)

### 题意
 给定长度为 $N(1 \le N \le 5 \times 10 ^ 5)$ 的大小写英文字符串 $S$。有 $Q(1 \le Q \le 5 \times 10 ^ 5)$ 次操作，第 $i$ 次操作给定三元组 $(t_i, x_i, c_i)$，$t_i$ 和 $x_i$ 是整数，$c_i$ 是字符，然后：
- 如果 $t_i = 1$，将第 $x_i$ 个字符变为 $c_i$。
- 如果 $t_i = 2$，将 $S$ 中的所有大写字母变成小写字母。 
- 如果 $t_i = 3$，将 $S$ 中的所有小写字母变成大写字母。

请输出最终的 $S$。

### 思路
暴力就不需要说了吧。可以发现，真正改变字符串的是每次的第一种操作还有**最后一次 $2,3$ 操作**，因为对于当前的 $2,3$ 操作，那么如果它后面还有同样的 $2,3$ 操作，那么它就会被覆盖掉。接下来直接模拟就可以了。

时间复杂度：$\operatorname{O}(N+M)$。

### 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 5e5 + 5;
struct node {
  int op, x;
  char y;
} a[MAXN];
int n, q, lt;
string s;
signed main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> s >> q, s = ' ' + s;
  for (int i = 1; i <= q; i++) {
    cin >> a[i].op >> a[i].x >> a[i].y;
    if (a[i].op != 1) lt = max(lt, i); // 找到最后一次 2,3 操作
  }
  for (int i = 1; i <= q; i++) { // 模拟
    if (a[i].op == 1) {
      s[a[i].x] = a[i].y;
    } else if (i == lt) {
      for (int j = 1; j <= n; j++) {
        if (a[i].op == 2) {
          if (s[j] >= 'A' && s[j] <= 'Z') {
            s[j] += 'a' - 'A';
          }
        } else {
          if (s[j] >= 'a' && s[j] <= 'z') {
            s[j] += 'A' - 'a';
          }
        }
      }
    }
  }
  cout << s.substr(1, n);
  return 0;
}
```

### 其他
其实，~~这道题还可以用线段树~~。

```cpp
#include <bits/stdc++.h>
#define int long long
#define ls (rt << 1)
#define rs (rt << 1 | 1)
#define mid (l + r >> 1)
using namespace std;
const int MAXN = 5e5 + 5;
char y;
int n, q, lt, op, x;
string s;
struct Sgt_Tree {
    int l, r, tag; // 0 ：大写     1 ：小写
    char v;
} a[MAXN << 2];
void change(bool v) { a[1].tag = v; }
void push_down(int rt) {
    if (a[rt].tag != -1) a[ls].tag = a[rs].tag = a[rt].tag, a[rt].tag = -1;
}
void build(int rt, int l, int r) {
    a[rt].l = l, a[rt].r = r, a[rt].tag = -1;
    if (l == r) {
        a[rt].v = s[l], a[rt].tag = (s[l] >= 'a');
        return;
    }
    build(ls, l, mid), build(rs, mid + 1, r);
}
void update(int rt, int x, char y) {
    int l = a[rt].l, r = a[rt].r;
    if (l == r) {
        a[rt].v = y, a[rt].tag = (y >= 'a');
        return;
    }
    push_down(rt);
    if (x <= mid) update(ls, x, y);
    if (mid < x) update(rs, x, y);
}
void print(int rt) {
    int l = a[rt].l, r = a[rt].r;
    if (l == r) {
        int t = (a[rt].tag ? 'a' - 'A' : 'A' - 'a'), x = (a[rt].v >= 'a');
        cout << char(a[rt].v + t * (x != a[rt].tag));
        return;
    }
    push_down(rt);
    print(ls), print(rs);
}
signed main() {
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> n >> s >> q, s = ' ' + s;
    build(1, 1, n);
    for (int i = 1; i <= q; i++) {
        cin >> op >> x >> y;
        if (op == 1) {
            update(1, x, y);
        } else {
            change((op == 2 ? 1 : 0));
        }
    }
    print(1);
    return 0;
}
```


---

## 作者：Failure_Terminator (赞：3)

## Solution

由于暴力是 $\Theta(n^2)$ 的，对于 $2,3$ 操作，我们可以想到用一个 `tag` 来记录变化。

对于 $1$ 操作，我们直接进行修改。

最后根据 `tag` 进行大小写转换。

但是这样就出现了一个问题：在最后的 $2, 3$ 操作后若还有 $1$ 操作，则后面的 $1$ 操作会被覆盖。

因此，我们考虑在操作时记录上一次被操作的时间，以及上一次执行 $2,3$ 操作的时间。

最后进行大小写转换操作时，若该字符的操作时间在 $2,3$ 操作时间之后，则不进行大小写转换。

时间复杂度 $\Theta(N + Q)$。

具体细节见下面代码。

## Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int now=0,nev=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')nev=-1;c=getchar();}
	while(c>='0'&&c<='9'){now=(now<<1)+(now<<3)+(c&15);c=getchar(); }
	return now*nev;
}

const int N = 5e5 + 5;
int lst[N], pl;
string s;
int n, m, rev = 0;

signed main()
{
	n = read(); cin >> s;
	m = read();
	for (int i = 1; i <= m; i ++){
		int op = read();
		int x; char y;
		x = read(); cin >> y;
		if (op == 2)
			rev = 1, pl = i;
		if (op == 3)
			rev = 2, pl = i;
		if (op == 1)
			s[x - 1] = y, lst[x - 1] = i;
	}
	for (int i = 0; i < s.size(); i ++){
		if (lst[i] > pl){
			cout << s[i];
			continue;
		}
		if (rev == 1 && s[i] >= 'A' && s[i] <= 'Z') s[i] += 32;
		if (rev == 2 && s[i] >= 'a' && s[i] <= 'z') s[i] -= 32;
		cout << s[i];
	} 
    return 0;
}
```

---

## 作者：Larry76 (赞：1)

## 前言

因为本人尚菜，所以本题解没有用到非题目上的数学符号。

## 题目分析

首先，暴力做肯定是 GG 的，因为此时时间复杂度达到了无法接受的 $O(n^2)$，无法接受。

一种比较直观的方法是我们用线段树维护一个「单点修改，全局修改大小写」的操作，复杂度 $O(n \log n)$，可以接受。

但是这样做有一点大材小用了，且该题远远没有难到需要写线段树的情况，于是我们继续思考，发现，对于每一个位置，只有最后一次修改是有用的，对于全局而言，只有最后一次大小写转换才是有用的。

所以我们不难想到倒着执行操作，如果碰到大小写转化操作，则记录最终转变的大小写状态，并忽略后续遍历时遇到的大小写转化操作；对于单点修改，如果没有确定最终转变的大小写状态，则保留操作中提供的大小写，否则依照最终转变的大小写状态来赋值，如果待修改的地方已经被修改过，则忽略此时的操作。时间复杂度 $O(n+m)$。

## 代码实现

由于当时比赛时脑袋比较晕，所以这里给出的代码不是最优的实现。

在这里只给出了关键部分的代码实现，其余部分还恳请读者自行实现其余部分。

```cpp
struct OPT{
	int opt;
	int p;
	char c;
};
vector<OPT> opts;
char changed[MAX_SIZE];
void main() {
	int n = read();
	string s;
	cin>>s;
	int m =read();
	int finstate = -1;
	for(int i = 1;i<=m;i++){
		int opt = read();
		int x = read();
		char c;
		cin>>c;
		opts.push_back((OPT){opt,x,c});
		if(opt==2){
			finstate = 1;
		} else if(opt==3){
			finstate = 0;
		}
	}
	int nowstate = -1;
	for(int i=m-1;i>=0;--i){
		auto &buf = opts[i];
		if(buf.opt == 1){
			if(changed[buf.p])
				continue;
			if(nowstate == -1){
				changed[buf.p] = buf.c;
			} else if(nowstate == 1){
				changed[buf.p] = tolower(buf.c);
			} else {
				changed[buf.p] = toupper(buf.c);
			}
		} else if(buf.opt == 2 && nowstate == -1){
			nowstate = 1;
		} else if(buf.opt == 3 && nowstate == -1) {
			nowstate = 0;
		}
	}
	for(int i=0;i<n;i++){
		if(!changed[i+1]){
			if(finstate == -1){
				putchar(s[i]);
			} else if(finstate == 1){
				putchar(tolower(s[i]));
			} else {
				putchar(toupper(s[i]));
			}
		} else {
			putchar(changed[i+1]);
		}
	}
    return void();
}
```

---

## 作者：Loser_Syx (赞：1)

对每个操作进行单独的讨论。

- 操作一：单点修改，没啥好说的。

- 操作二：修改全部字母的大小写到大写，一种通俗易懂的方法就是暴力，但是会发现 $1 \leq N \leq 5 \times 10^5$，数据范围不允许，那么此处考虑优化，**我先不操作**，单独开一个变量记录所有的统一转大写的在什么时候。但由于操作一更改了，于是我们需要单独开一个数组 $change_i$ 表示以 $i$ 为下标的最后是在什么时候更改的。

- 操作三类似操作二，只不过是把转大写改成了转小写。

[代码](https://atcoder.jp/contests/abc314/submissions/44510778)

---

## 作者：kkxacj (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc314_d)

#### 思路

不难想到，如果题目让你先全部转成大写在全部转成小写，就等价于直接转成小写，于是我们可以在最后在转，所以我们只需要记录每个被更改的字符更改的时间，如果在它之后没有变大写或变小写的操作，他就不变，没被更改的字符把时间记为 $0$，操作完输出即可。

#### code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,x,y,u,bj[800010],l;
string s;
char z;
int main()
{
	scanf("%d",&n); 
	cin >> s;
	scanf("%d",&q);
	for(int i = 1;i <= q;i++)
	{
		scanf("%d%d",&x,&y); cin >> z;
		y--;
		if(x == 1)
		{
			s[y] = z;
			bj[y] = i;//标记更改的时间
		}
		else if(x == 2) u = 1,l = i;
		else if(x == 3) u = 0,l = i;//l为当前时间
	}
	for(int i = 0;i < s.size();i++)
	{
		if(bj[i] < l)//在它之后有变大写或变小写的操作
		{
			if(u == 0 && 'a' <= s[i] && s[i] <= 'z') s[i] = s[i] - 'a' + 'A'; 
			else if(u == 1 && 'A' <= s[i] && s[i] <= 'Z') s[i] = s[i] - 'A' + 'a'; 
		}
      		//否则不管
	}
	cout << s;//输出
   	return 0;
}

```


---

## 作者：markding (赞：1)

### 题目大意

给定一个长度为 $N$ 的字符串 $S$，再给定 $Q$ 次询问，每次询问给定两个正整数 $t,x$，以及一个字符 $c$：

- 若 $t=1$，将 $S$ 的第 $x$ 个字符修改为 $c$

- 若 $t=2$，将 $S$ 的所有字符全部大写

- 若 $t=3$，将 $S$ 的所有字符全部小写

### 题目分析

若将 $S$ 的所有字符全部大写之后又全部小写，实际上原先的“全部大写”操作就没有用了。

继续思考，不管之前字符的大小写属性，如果遇到了一次 $t\ge2$ 的操作，以前字符的大小写属性就都不重要了。

因此，我们可以设计一个算法，使得我们**只关心最后一次的 $t\ge2$ 的操作**。

我们可以记录这一次操作的位置 $pos$，对于 $pos$ 之前的 $t=1$ 的操作，照常修改，对于其他的操作不予理会。

然后，根据 $pos$ 位置的操作，将 $S$ 的所有字符全部大写或小写。

$pos$ 位置之后的操作只可能是 $t=1$，直接修改即可。

### 题目代码

这是本人赛时的代码。

```cpp
#include<iostream>
#define LOWER 1
#define upper 2
using namespace std;string s;char c[500005];
int pos,state,n,q,t[500005],x[500005];
int main()
{
	cin>>n>>s>>q;
	for(int i=1;i<=q;i++)
	{
		cin>>t[i]>>x[i]>>c[i];
		if(t[i]==2)state=LOWER,pos=i;
		if(t[i]==3)state=upper,pos=i;
	}
	for(int i=1;i<pos;i++)
		if(t[i]==1)s[x[i]-1]=c[i];
	if(state==LOWER)for(char& c:s)c=tolower(c);
	if(state==upper)for(char& c:s)c=toupper(c);
	for(int i=pos+1;i<=q;i++)
		if(t[i]==1)s[x[i]-1]=c[i];
	cout<<s;
}
```

---

## 作者：封禁用户 (赞：1)

## 分析

一眼题。

很显然，我们在每次操作时都去更新是不可行的。所以考虑在最后统一处理。记第 $i$ 次操作的时间为 $i$，则我们有：

1. 若第 $x$ 个字符的最后一次单个修改（操作 $1$）的时间大于操作 $2,3$ 的最后一次修改的时间，则任意的操作 $2,3$ 对于 $x$ 最终的形态无影响，结果与修改后的字符相同。

2. 若第 $x$ 个字符的最后一次单个修改的时间小于操作 $2,3$ 的最后一次修改时间，则第 $x$ 个字符的最终形态为最后一次单个修改后，变成的字符依照操作 $2,3$ 中，最后的时间较大的那个所对应的要求修改后的字符。

我们可以定义 $\mathit{vis}_{i,j}$ 表示第 $i$ 个字符在时间 $j$ 所变成的字符，其中 $\mathit{vis}_{i,0}$ 与初始字符相同。分别记录操作 $2,3$ 的最大时间，再依照上面的结论，与每个字符的最大时间相比较，输出最终状态的修改后的字符即可。

## 代码
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10;
int n,m;
string s;
int k1,k2;
map<int,map<int,char> > vis;
int maxtim[N];
int maxtim1,maxtim2;
void solve(){
	cin>>n>>s>>m;
	for(int i=0;i<s.size();i++){
		vis[i][0]=s[i],maxtim[i]=0;
	}
	int now_tim=0;//当前时间
	while(m--){
		int t,x;
		char c;cin>>t>>x>>c;
		if(t==1) bmaxtim[x-1]=++now_tim,vis[x-1][maxtim[x-1]]=c;//maxtim[i]表示第i个字符最大的修改时间
		else if(t==2) k1=1,maxtim1=++now_tim;
		else if(t==3) k2=1,maxtim2=++now_tim;
	}
	if(!k1&&!k2){
		for(int i=0;i<s.size();i++) cout<<vis[i][maxtim[i]];
	}
	else if(maxtim1>maxtim2){//全小写
		for(int i=0;i<s.size();i++)
			if(maxtim[i]>maxtim1) cout<<vis[i][maxtim[i]];
			else if(vis[i][maxtim[i]]>='a'&&vis[i][maxtim[i]]<='z')cout<<vis[i][maxtim[i]];
			else cout<<char(vis[i][maxtim[i]]-'A'+'a');
	}
	else{//全大写
		for(int i=0;i<s.size();i++)
			if(maxtim[i]>maxtim2) cout<<vis[i][maxtim[i]];
			else if(vis[i][maxtim[i]]>='A'&&vis[i][maxtim[i]]<='Z')cout<<vis[i][maxtim[i]];
			else cout<<char(vis[i][maxtim[i]]-'a'+'A');
	}
}
signed main(){
	solve();return 0;
}
```


---

## 作者：icypenguin (赞：0)

## 题目分析

操作进行了多次大小写转换操作，我们发现最后一次这种操作才是有意义的，所以忽略前面所有的这种操作。我们设最后一次这种操作是在第 $i$ 次，如果不存在这样的 $i$，那我们直接运行 $Q$ 次修改即可。如果存在这样的 $i$，我们完成前 $i - 1$ 项所有的修改操作，其他的操作忽略。我们再完成这一次大小写转换，我们再完成 $i + 1 \sim Q$ 次的修改操作。

时间复杂度是 $O(n + Q)$ 的，因为最多大小写转换一次，最多修改 $Q$ 次。

## 代码实现

```cpp
#include <iostream>
#define ll long long
using namespace std;
ll n, m, id[1000005], a[1000005];
char s[1000005], b[1000005];
int main(){
    cin >> n;
    for (ll i = 1; i <= n; i++){
        cin >> s[i];
    }
    cin >> m;
    for (ll i = 1; i <= m; i++){
        cin >> id[i] >> a[i] >> b[i];
    }
    ll ti = 0;
    for (ll i = m; i >= 1; i--){
        if (id[i] == 2 || id[i] == 3){
            ti = i;
            break;
        }
    }
    if (ti == 0){
        for (ll i = 1; i <= m; i++){
            s[a[i]] = b[i];
        }
        for (ll i = 1; i <= n; i++){
            cout << s[i];
        }
        return 0;
    }
    for (ll i = 1; i <= ti - 1; i++){
        if (id[i] == 1){
            s[a[i]] = b[i];
        }
    }
    if (id[ti] == 2){
        for (ll i = 1; i <= n; i++){
            if (s[i] >= 'A' && s[i] <= 'Z'){
                s[i] += 'a' - 'A';
            }
        }
    }else{
        for (ll i = 1; i <= n; i++){
            if (s[i] >= 'a' && s[i] <= 'z'){
                s[i] -= 'a' - 'A';
            }
        }
    }
    for (ll i = ti + 1; i <= m; i++){
        s[a[i]] = b[i];
    }
    for (ll i = 1; i <= n; i++){
        cout << s[i];
    }
    return 0;
}
// AtCoder
//
```


---

## 作者：Escapism (赞：0)

[原题链接](https://atcoder.jp/contests/abc314/tasks/abc314_d)

这个 ``D`` 的难度其实挺低的。

# 题意

给你一个长度为 $n$ 的字符串，有 $m$ 次操作，操作共有 $3$ 种：

- 操作一：将字符串中的第 $x_i$ 个字符修改为 $c_i$。

- 操作二：将字符串中的所有大写字母修改为小写的。

- 操作三：将字符串中的所有小写字符修改为大写的。

# 思路

不难发现，对于所有种类的操作，所有不是最后一次操作的结果都会被“覆盖”掉。因而无论进行多少次操作，与最后的结果有关的只有最后一次。

所以我们只要记录最后一次操作二或操作三的时间，以及这次操作是操作二还是三就可以的。

对于操作一，为了方便修改，我们使用字符数组方便访问下标。我们记录其最后一次操作一的时间，如果晚于最后一次操作二或三的时间，就不修改其大小写，反之则修改其大小写。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
 
const int MAXN = 5 * 1e5 + 5;
int n,m;
char s[MAXN];
bool flag;
int r = 0;
int a[MAXN];
 
int main(){
    cin>>n>>s>>m;
    int cnt = 0;
    while(m--){
        int type,pla;
        char c;
        cin>>type>>pla>>c; 
        if (type == 1) s[pla - 1] = c,a[pla - 1] = ++cnt; //记录位置和操作时间
        if (type == 2 || type == 3){
            r = ++cnt; //最后一次更改大小写的时间
            flag = type % 2; //记录操作类型
        }
    }
    for (int i = 0;i < n;i++){
        if (a[i] < r){ //如果对于某个位置的字符，最后一次操作一的时间晚于最后一次操作二或三的情况
            if (flag == 0 && s[i] >= 'a') cout<<s[i];
            if (flag == 0 && s[i] <= 'Z') cout<<char(s[i] - 'A' + 'a');
            if (flag == 1 && s[i] >= 'a') cout<<char(s[i] - 'a' + 'A');
            if (flag == 1 && s[i] <= 'Z') cout<<s[i];           
        }
        else cout<<s[i];
    }
}
```


---

## 作者：tbdsh (赞：0)

# 题意简述
[更好的阅读体验](https://www.luogu.com.cn/blog/tianbiandeshenghuo11/solution-at-abc314-d)

[AtCoder 原题面](https://atcoder.jp/contests/314/tasks/abc314_d)

[洛谷原题面](https://www.luogu.com.cn/problem/at_abc314_d)

给定长度为 $N$ 的大小写英文字符串 $S$，下标分别为 $1,2,3,\dots,N$。有 $Q$ 次操作，第 $i$ 次操作给定三元组 $(t_i, x_i, c_i)$，$t_i, x_i$ 是整数，$c_i$ 是字符，然后进行如下操作：

1. 如果 $t_i = 1$，则将 $S$ 的第 $x_i$ 个字符变为 $c_i$。
2. 如果 $t_i = 2$，则将 $S$ 中的所有大写字母变成小写字母。
3. 如果 $t_i = 3$，则将 $S$ 中的所有小写字母变成大写字母。

输出最终的 $S$。
# 分析
首先考虑暴力的做法：每次读入，如果 $t_i=1$，则直接修改。否则遍历整个字符串，根据 $t_i$ 更新每个字符。

但这样的时间复杂度是 $O(N\times Q)$ 的，会超时。

不难发现，如果操作是类似这样的：
```plain
2 0 a
1 1 a
1 1 a
.
.
.
3 0 a
```

那么第一次进行的修改操作，在很多次之后被覆盖。

所以，我们前面进行的很多操作都是无用的。

事实上，最后的字符串 $S$ 的大小写变换只和最后一次操作 $2$ 和操作 $3$ 有关。

但同时，如果我们直接最后全部更新是有误的。

如果有类似这样的样例：
```plain
5
abcde
6
3 0 a
1 1 a
1 2 b
1 3 c
1 4 d
1 5 e
```
答案应该是 `abcde`。但如果按照刚才的思路去写，输出的将是 `ABCDE`。

所以我们就可以发现，最后一次操作 $2$、$3$ 只会影响在此之前进行的操作 $1$ 和未进行操作位置的字符。

那么，我们记录最后一次操作 $2$、$3$ 是 $2$ 还是 $3$ 和其对应第几次操作（下记其为 $p$），每个字符的最后一次操作 $1$ 是第几次操作（下记其为 $q_{x_i}$）。

每次操作 $1$ 都直接更新。

最后扫一遍字符串，看是否满足 $q_i\le p$。是就按照最后一次操作更新大小写即可。

时间复杂度：$O(N+Q)$。

空间复杂度：$O(N)$。
# Code
```cpp
#include<bits/stdc++.h>

using namespace std;
const int MAXN = 5e5 + 5;
int n, m, x, y;
string s;
int cg[MAXN];
int f = -1, op = -1;
int main(){
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n >> s >> m;
  s = ' ' + s;
  for (int i = 1; i <= m; i++){
    int a, b;
    char p;
    cin >> a >> b >> p;
    if (a == 1){
      s[b] = p;
      cg[b] = i;
    }else if (a == 2){
      f = 0;
      op = i;
    }else {
      f = 1;
      op = i;
    }
  }
  for (int i = 1; i <= n; i++){
    if (cg[i] <= op){
      if (f && 'a' <= s[i] && s[i] <= 'z'){
        s[i] += 'A' - 'a';
      }else if (f == 0 && 'A' <= s[i] && s[i] <= 'Z'){
        s[i] += 'a' - 'A';
      }
    }
  }
  cout << s;
  return 0;
}
```

---

## 作者：Crazyouth (赞：0)

**翻译**

给定一个 $n$ 个字符的串 $S$，与正整数 $q$，接下来 $q$ 个操作，每次给定两个正整数 $t,x$，与字符 $c$，如果

- $t=1$，$S_x\leftarrow c$。
- $t=2$，请忽略 $x,c$，把整个 $S$ 变成大写。
- $t=3$，请忽略 $x,c$，把整个 $S$ 变成小写。

求最后的串 $S$。

**分析**

赛时把 $2,3$ 操作看成对特定区间变成大写，想了 $10$ min。

套路题。对于操作 $1$，直接暴力修改。对于操作 $2,3$，只需要记录当前的字符串是大写还是小写即可。这时候想到对于操作 $2,3$ 后面还会跟着操作 $1$ 的情况，我们就得对执行操作 $1$ 的时候，开一个 map 记录当前字符是否需要被“覆盖”为大写或小写。然后就做完了。其实理论上是不用 map 的，赛场上想到要存下意识写了 map。

**AC Code**
```cpp
#include <bits/stdc++.h>
using namespace std;
map<int,int> mp;
string s;
char capital(char c)//返回c的大写形式
{
	if(c>='a'&&c<='z') return c;
	else return c-'A'+'a';
}
char lower(char c)//返回c的小写形式
{
	if(c>='A'&&c<='Z') return c;
	else return c-'a'+'A';
}
int main()
{
	int cap,n,q;
	string s;
	cin>>n;
	cin>>s;
	cin>>q;
	s=' '+s;
	for(int i=1;i<=n;i++) mp[i]=1;//一开始全部都不用“覆盖”
	while(q--)
	{
		int t,x;
		char c;
		cin>>t>>x>>c;
		if(t==1)
		s[x]=c,mp[x]=1;//修改，标记为“不覆盖”
		else if(t==2)
		{
			mp.clear();//清空“不覆盖”
			cap=1;//大写
		}
		else//同上
		{
			mp.clear();
			cap=0;
		}
	}
	for(int i=1;i<=n;i++)
	{
		if(mp[i])//“不覆盖”
		{
			cout<<s[i];
			continue;
		}
		if(cap==0) cout<<lower(s[i]);//小写
		else cout<<capital(s[i]);//大写
	}
	return 0;
}

---

