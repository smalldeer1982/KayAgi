# [ABC350F] Transpose

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc350/tasks/abc350_f

英大小文字と `(` 、 `)` からなる文字列 $ S=S_1\ S_2\ S_3\ \dots\ S_{|S|} $ が与えられます。  
 文字列 $ S $ 中の括弧は、対応が取れています。

次の操作を、操作ができなくなるまで繰り返します。

- まず、以下の条件を全て満たす整数組 $ (l,r) $ をひとつ選択する。
  - $ l\ <\ r $
  - $ S_l\ = $ `(`
  - $ S_r\ = $ `)`
  - $ S_{l+1},S_{l+2},\dots,S_{r-1} $ は全て英大文字または英小文字である
- $ T=\overline{S_{r-1}S_{r-2}\ \dots\ S_{l+1}} $ とする。
  - 但し、 $ \overline{x} $ は $ x $ の大文字と小文字を反転させた文字列を指す。
- その後、 $ S $ の $ l $ 文字目から $ r $ 文字目までを削除し、削除した位置に $ T $ を挿入する。
 
詳細は入出力例を参照してください。

上記の操作を使って全ての `(` と `)` を除去することができ、最終的な文字列は操作の方法や順序によらないことが証明できます。  
 このとき、最終的な文字列を求めてください。

  「 $ S $ 中の括弧の対応が取れている」とは? まず、正しい括弧列を次の通り定義します。 - 正しい括弧列とは、以下のいずれかの条件を満たす文字列です。
- 空文字列
- ある正しい括弧列 $ A $ が存在して、 `(`, $ A $, `)` をこの順に連結した文字列
- ある空でない正しい括弧列 $ A,B $ が存在して、 $ A,B $ をこの順に連結した文字列
 
 
 $ S $ 中の括弧の対応が取れているとは、 $ S $ 中の `(` と `)` を順序を保って抜き出した時、それが正しい括弧列となることを指す。

## 说明/提示

### 制約

- $ 1\ \le\ |S|\ \le\ 5\ \times\ 10^5 $
- $ S $ は英大小文字と `(` 、 `)` からなる
- $ S $ 中の括弧は対応が取れている
 
### Sample Explanation 1

$ S= $ `((A)y)x` に対して操作を行います。 - $ l=2,r=4 $ を選択します。このとき削除される文字列は `(A)` で、代わりに `a` が挿入されます。 - この操作の結果、 $ S= $ `(ay)x` となります。 - $ l=1,r=4 $ を選択します。このとき削除される文字列は `(ay)` で、代わりに `YA` が挿入されます。 - この操作の結果、 $ S= $ `YAx` となります。 括弧を除去した結果、文字列は `YAx` となったので、これを出力してください。

### Sample Explanation 2

$ S= $ `((XYZ)n(X(y)Z))` に対して操作を行います。 - $ l=10,r=12 $ を選択します。このとき削除される文字列は `(y)` で、代わりに `Y` が挿入されます。 - この操作の結果、 $ S= $ `((XYZ)n(XYZ))` となります。 - $ l=2,r=6 $ を選択します。このとき削除される文字列は `(XYZ)` で、代わりに `zyx` が挿入されます。 - この操作の結果、 $ S= $ `(zyxn(XYZ))` となります。 - $ l=6,r=10 $ を選択します。このとき削除される文字列は `(XYZ)` で、代わりに `zyx` が挿入されます。 - この操作の結果、 $ S= $ `(zyxnzyx)` となります。 - $ l=1,r=9 $ を選択します。このとき削除される文字列は `(zyxnzyx)` で、代わりに `XYZNXYZ` が挿入されます。 - この操作の結果、 $ S= $ `XYZNXYZ` となります。 括弧を除去した結果、文字列は `XYZNXYZ` となったので、これを出力してください。

### Sample Explanation 3

操作結果が空文字列になる場合もあります。

## 样例 #1

### 输入

```
((A)y)x```

### 输出

```
YAx```

## 样例 #2

### 输入

```
((XYZ)n(X(y)Z))```

### 输出

```
XYZNXYZ```

## 样例 #3

### 输入

```
(((()))(()))(())```

### 输出

```
```

## 样例 #4

### 输入

```
dF(qT(plC())NnnfR(GsdccC))PO()KjsiI((ysA)eWW)ve```

### 输出

```
dFGsdccCrFNNnplCtQPOKjsiIwwEysAve```

# 题解

## 作者：_Weslie_ (赞：5)

赛时：一眼平衡树，不会写。

### 思路

模拟。

维护一个 $\tt dfs$，其中 $\texttt{dfs(l,r,f)}$ 表示现在模拟的区间是 $[l,r]$，正序还是倒序。

但是路途中可能会遇到括号，这时我们就要反方向模拟。

因此，我们需要预处理出每个左括号对应的右括号（右括号同理）。

这样，我们就能 $\operatorname{O}(1)$ 地进入下一个模拟。

关于大小写转换，手搓几组样例就不难发现：

- 如果正序输出，大小写不变。
- 如果倒序输出，大小写互换。

这样，我们就能 $\operatorname{O}(n)$ 地解决本题了。

```
#include<bits/stdc++.h>
using namespace std;
string s;
int n,ld[500005],rd[500005];
stack<int>st;
void dfs(int l,int r,int f) {
	if(f==1) {
		for(int i=l; i<=r; i++) {
			if(s[i]=='('){
				dfs(i+1,ld[i]-1,-1);
				i=ld[i];
			} 
			else{
				cout<<s[i];
			}
		}
	}
	else{
		for(int i=r;i>=l;i--){
			if(s[i]==')'){
				dfs(rd[i]+1,i-1,1);
				i=rd[i];
			} 
			else{
				if('a'<=s[i]&&s[i]<='z')cout<<char(s[i]-'a'+'A');
				else cout<<char(s[i]-'A'+'a');
			}
		}
	}
}
int main() {
	cin>>s;
	n=s.length();
	s=' '+s;
	for(int i=1; i<=n; i++) {
		if(s[i]=='(') {
			st.push(i);
		}
		if(s[i]==')') {
			int v=st.top();
			st.pop();
			ld[v]=i;
			rd[i]=v;
		}
	}
	dfs(1,n,1);
	return 0;
}
```

---

## 作者：incra (赞：3)

### Solution
考虑设计输出函数 `print(l,r,k)`，表示输出 $[l,r]$ 区间的字符，$k$ 的奇偶性表示是否要倒着输出。

若 $k\bmod 2\equiv 0$，那么要正着输出。如果遇到括号，直接把括号里的字符倒着输出，即调用 `print(x+1,y-1,k+1)`，其中 $x,y$ 表示这对括号的位置。如果遇到字符直接输出即可。

否则，要倒着输出。如果遇到括号，和上面类似，注意从后往前遇到 `)` 就要调用下一层输出，正确性留给读者自行思考。如果遇到字母，注意大小写反转后在输出。

一对括号的位置用栈处理就行了，这里不赘述了，有需要自行查找资料。
### Code
[Link](https://atcoder.jp/contests/abc350/submissions/52603786)。

---

## 作者：guanyf (赞：2)

### 题意

给定一个字符串 $S(1 \le |S| \le 5 \times 10 ^ 5)$，$S$ 是由一堆匹配了的括号和大小写英文字母组成的。

接下来重复以下操作，直到不能再进行操作为止：

- 选定一对匹配了的括号，把括号内的所有字母大小写反转，然后把括号内的整个字符串前后翻转，最后删除这对括号。

确定最终的字符串。

#### 举个例子

` (ATcoder) 最终会变成 REDOCta `

### 提示 1

题目中已经说了：**可以证明，使用上述操作可以删除字符串中的所有 `(` 和 `)`，最终的字符串与操作的方式和顺序无关。**

### 提示 2

先考虑大小写问题。每遇到一个括号就要把括号内的所有字符反转一遍，因此我们可以记录每个字符被反转的次数，最后再进行处理。这个问题可以看作区间加，每次把括号内的所有字母的反转次数加一，这可以用差分解决，也可以直接在下文提到的分治中解决（就是多记录了整个区间的大小写反转次数）。

### 提示 3

接下来只剩下区间翻转问题了。先感性理解一下：一个括号只可能包着其他几个括号，接着继续往下分。因此，和括号有关的一类问题大多可以用分治解决。假设当前是第一层括号，那么把一个括号内的字符串区间翻转，就等于**从后往前输出每个字符，如果遇到括号，就继续分治去求**，对于第二层括号来说，因为第一层的这层括号决定了它是从后往前输出，但因为它自己也是一层括号，就应该再翻转一下，变成从前往后输出。

### 提示 4

先求出每个括号的与它匹配的括号的位置。接着分治。从 $[1,n]$ 开始分治。用 $c$ 记录当前**前后翻转的状态**，0 表示从左往右，1 表示从右往左，初始时 $c = 0$，接着按照 $c$ 所表示的顺序遍历当前的区间，遇到字符就输出，遇到括号就继续分治，往下分时 $c$ 要 01 反转。

时间复杂度：$\operatorname{O}(|S|)$。

### 提示 5

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e6 + 5;
string s;
int n, it[MAXN], cf[MAXN];
stack<int> sk;
void fz(int l, int r, int c) {
  if (l > r) return;
  if (c) {  // 从右往左
    for (int i = r; i >= l; i--) {
      if (it[i]) {
        fz(it[i] + 1, i - 1, c ^ 1), i = it[i];
      } else {
        cout << s[i];
      }
    }
  } else {  // 从左往右
    for (int i = l; i <= r; i++) {
      if (it[i]) {
        fz(i + 1, it[i] - 1, c ^ 1), i = it[i];
      } else {
        cout << s[i];
      }
    }
  }
}
signed main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> s;
  n = s.size(), s = ' ' + s;
  for (int i = 1; i <= n; i++) {  // 记录每个括号的与它匹配的括号的位置
    if (s[i] == '(') {
      sk.push(i);
    } else if (s[i] == ')') {
      it[sk.top()] = i, it[i] = sk.top();
      sk.pop();
      cf[it[i]]++, cf[i + 1]--;
    }
  }
  for (int i = 1, c = 0; i <= n; i++) {
    c += cf[i];
    if (c & 1 && !it[i]) {
      s[i] += 32 * (s[i] >= 'a' ? -1 : 1);  // 大小写反转
    }
  }
  fz(1, n, 0);
  return 0;
}
```

---

## 作者：FReQuenter (赞：1)

考虑把整个操作分三步进行：找括号，反转排列，反转大小写。

关于找括号：使用栈，栈顶元素为上一个左括号的坐标，遇到右括号就可以弹出栈顶进行操作。

反转排列：使用类似链表的思想，记录每个数的后驱以及是正向遍历还是反向。

反转大小写：使用差分，在每个括号处打上差分标记，最后遍历每个数的后驱的时候一并计算。

```cpp
#include<bits/stdc++.h>
using namespace std;
char cgg(char a){
	if(a>='a'&&a<='z') return a+'A'-'a';
	return a-'A'+'a';
}
int a[500005],cg[500005];
signed main(){
	string s,ans="";
	cin>>s;
    int n=s.length();
    stack<int> st;
    for(int i=0;i<n;i++){
        if(s[i]=='(') st.push(i);
        if(s[i]==')'){
            int fr=st.top();
            cg[st.top()]++;
			st.pop();
            a[i]=fr,a[fr]=i;
            cg[i]--;
        }
    }
    int idx=0,step=1,ss=0;
    while(idx<n){
        if(s[idx]=='('||s[idx]==')'){
			ss+=cg[idx];
            idx=a[idx];
            step=-step;
        }
        else ans+=(ss%2?cgg(s[idx]):s[idx]);
        idx+=step;
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：FFTotoro (赞：1)

ABC AKed。感觉这个题比暴力可过的 G 更有意义一点。

对于这种题考虑不正经做法。显然对于每个一开始连着的字符串我们需要考虑其大小写与翻转，即考虑它要“出”几次括号，即左边未匹配的括号数。出一次括号大小写变一次，所以它的大小写会变当且仅当其左边有奇数个未匹配的左括号。

发现翻转不好简单地维护，于是考虑暴力。把所有**字母**确定大小写后抽出来形成一个字母串 $L$，然后跑括号匹配，匹配到一对就把 $L$ 对应区间抽出来翻转。如何快速翻转字符串？考虑文艺平衡树，但是我不会，所以考虑 `__gnu_cxx::rope` 暴做（可参考文艺平衡树题解区）。事实证明 $5\times 10^5$ 400ms 无压通过。

放代码：

```cpp
#include<bits/stdc++.h>
#include<bits/extc++.h>
using namespace std;
using namespace __gnu_cxx;
main(){
  ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  string S; int n=0; cin>>S;
  rope<char> s,d;
  auto rev=[&](int l,int r){
    if(l==r)return; l++,r++;
    rope<char> t=s.substr(s.begin()+l-1,s.begin()+r);
    s=s.substr(s.begin(),s.begin()+l-1)+d.substr(n-r+d.begin(),n-l+d.begin()+1)+s.substr(s.begin()+r,s.end());
    d=d.substr(d.begin(),n-r+d.begin())+t+d.substr(n-l+d.begin()+1,d.end());
  }; // 翻转
  auto ch=[&](char c){
    if(isupper(c))return tolower(c);
    return toupper(c);
  }; // 变大小写
  stack<int> t;
  vector<int> mp(S.length()+1);
  for(int i=0;i<S.length();i++)
    if(isalpha(S[i]))mp[i]=n++; // 抽出字母
  mp[S.length()]=n;
  for(int i=S.length()-1;~i;i--)
    if(!isalpha(S[i]))mp[i]=mp[i+1];
  for(int i=0;i<S.length();i++){
    if(S[i]=='(')t.emplace(i);
    else if(S[i]==')')t.pop();
    else if(t.size()&1)S[i]=ch(S[i]);
  } // 跑第一遍匹配确定大小写
  for(char i:S)
    if(isalpha(i))s.append(i);
  for(int i=S.length()-1;~i;i--)
    if(isalpha(S[i]))d.append(S[i]);
  for(int i=0;i<S.length();i++){
    if(S[i]=='(')t.emplace(i);
    else if(S[i]==')')rev(mp[t.top()],mp[i]-1),t.pop();
  } // 跑第二遍匹配进行翻转
  for(char i:s)cout<<i;
  cout<<endl;
  return 0;
}
```

---

## 作者：__Floze3__ (赞：1)

## 思路简介

~~AT 不会出题可以不出，放个板子什么意思？~~

很显然，如果我们不需要考虑每个字符的大小写，这就是一道文艺平衡树的板子题，只需要一边进行括号匹配，一边翻转区间即可。对于大小写的处理，我们注意到，只有当一个字符被奇数个匹配括号对包围时才需要改变大小写，那么我们可以利用差分的方式统计包围每个位置的匹配括号对数，最后中序遍历输出答案即可。

## 代码

由于头文件过于冗长，这里只放实际有效的代码。

```cpp
int sum[N], cnt, root;
char c[N];

std::stack<int> st;

struct node {
    int ls, rs, tag, val, pri, siz;

    #define ls(x) tree[x].ls
    #define rs(x) tree[x].rs
    #define pri(x) tree[x].pri
    #define val(x) tree[x].val
    #define siz(x) tree[x].siz
    #define tag(x) tree[x].tag
} tree[N];

il int create(int x) {
    siz(++cnt) = 1, ls(cnt) = rs(cnt) = tag(cnt) = 0;
    val(cnt) = x, pri(cnt) = rand();
    return cnt;
}

il void pushdown(int p) {
    if (tag(p)) {
        swap(ls(p), rs(p));
        tag(ls(p)) ^= 1, tag(rs(p)) ^= 1;
        tag(p) = 0;
    }
    return ;
}

il void pushup(int p) { siz(p) = siz(ls(p)) + siz(rs(p)) + 1; }

void split(int u, int rnk, int &L, int &R) {
    if (!u) {
        L = R = 0;
        return ;
    }
    pushdown(u);
    if (rnk >= siz(ls(u)) + 1) {
        L = u;
        split(rs(u), rnk - siz(ls(u)) - 1, rs(u), R);
    }
    else {
        R = u;
        split(ls(u), rnk, L, ls(u));
    }
    pushup(u);
    return ;
}

int merge(int L, int R) {
    if (!L || !R) return L + R;
    if (pri(L) < pri(R)) {
        pushdown(L);
        rs(L) = merge(rs(L), R);
        pushup(L);
        return L;
    }
    else {
        pushdown(R);
        ls(R) = merge(L, ls(R));
        pushup(R);
        return R;
    }
}

void print(int p) {
    if (!p) return ;
    pushdown(p);
    print(ls(p));
    if (c[val(p)] != '(' && c[val(p)] != ')') write << c[val(p)];
    print(rs(p));
    return ;
}

signed main() {
    read >> (c + 1);
    int len = strlen(c + 1);
    srand(time(NULL));
    _FOR(i, 1, len) root = merge(root, create(i));
    _FOR(i, 1, len) {
        if (c[i] == '(') st.push(i);
        else if (c[i] == ')') {
            int l = st.top(); st.pop();
            ++sum[l], --sum[i + 1];
            int L, R, A;
            split(root, i, L, R);
            split(L, l - 1, L, A);
            tag(A) ^= 1;
            root = merge(merge(L, A), R);
        }
    }
    _FOR(i, 1, len) {
        sum[i] += sum[i - 1];
        if (sum[i] & 1) {
            if (c[i] >= 'a' && c[i] <= 'z') c[i] += 'A' - 'a';
            else if (c[i] >= 'A' && c[i] <= 'Z') c[i] += 'a' - 'A';
        }
    }
    print(root);
    return 0;
}
```

---

## 作者：_determination_ (赞：1)

文艺平衡树板子。

写个栈跑括号匹配来得到操作序列，然后文艺平衡树基本操作。标记下传的时候注意一下变大小写即可。

```cpp
#include<bits/stdc++.h>
#define int long long
#define debug puts("Genshin Imapct")
#define inf (int)1e18
#define endl '\n'
using namespace std;
mt19937 rnd(time(0));
struct node{
    int ls,rs,key,siz,tag;
    char ch;
}t[500010];
stack<int>st;
vector<pair<int,int> >q;
int tot,root;
int new_node(char ch)
{
    tot++;
    t[tot].ls=t[tot].rs=0;
    t[tot].key=rnd();
    t[tot].siz=1;
    t[tot].tag=0;
    t[tot].ch=ch;
    return tot;
}
int lc(char ch)
{
    return 'a'<=ch&&ch<='z';
}
int uc(char ch)
{
    return 'A'<=ch&&ch<='Z';
}
void pd(int x)
{
    if(t[x].tag)
    {
        t[x].tag=0;
        swap(t[x].ls,t[x].rs);
        t[t[x].ls].tag^=1;
        if(lc(t[t[x].ls].ch))t[t[x].ls].ch=t[t[x].ls].ch-'a'+'A';
        else if(uc(t[t[x].ls].ch))t[t[x].ls].ch=t[t[x].ls].ch+'a'-'A';
        t[t[x].rs].tag^=1;
        if(lc(t[t[x].rs].ch))t[t[x].rs].ch=t[t[x].rs].ch-'a'+'A';
        else if(uc(t[t[x].rs].ch))t[t[x].rs].ch=t[t[x].rs].ch+'a'-'A';
    }
}
void pu(int x)
{
    t[x].siz=t[t[x].ls].siz+t[t[x].rs].siz+1;
}
void split(int x,int siz,int &l,int &r)
{
    if(!x)return l=r=0,void();
    pd(x);
    if(t[t[x].ls].siz+1<=siz)
    {
        l=x;
        split(t[x].rs,siz-t[t[x].ls].siz-1,t[x].rs,r);
        pu(x);
    }else{
        r=x;
        split(t[x].ls,siz,l,t[x].ls);
        pu(x);
    }
}
int merge(int l,int r)
{
    if(!l||!r)return l+r;
    if(t[l].key<t[r].key)
    {
        pd(l);
        t[l].rs=merge(t[l].rs,r);
        pu(l);
        return l;
    }else{
        pd(r);
        t[r].ls=merge(l,t[r].ls);
        pu(r);
        return r;
    }
}
void print(int x)
{
    if(!x)return;
    pd(x);
    print(t[x].ls);
    if(t[x].ch!='('&&t[x].ch!=')')
    {
        cout << t[x].ch;
    }
    print(t[x].rs);
}
signed main()
{
    string s;
    cin >> s;
    for ( int i = 0 ; i < s.size() ; i++ )
    {
        if(s[i]=='(')
        {
            st.push(i+1);
        }else if(s[i]==')')
        {
            q.push_back({st.top(),i+1});
            st.pop();
        }
    }
    for ( int i = 0 ; i < s.size() ; i++ )
    {
        root=merge(root,new_node(s[i]));
    }
    for ( auto v:q )
    {
        int l=v.first,r=v.second;
        int L,R,M;
        split(root,r,L,R);
        split(L,l-1,L,M);
        t[M].tag^=1;
        if(lc(t[M].ch))t[M].ch=t[M].ch-'a'+'A';
        else if(uc(t[M].ch))t[M].ch=t[M].ch+'a'-'A';
        L=merge(L,M);
        root=merge(L,R);
    }
    print(root);
    return 0;
}
```

---

## 作者：EmptyAlien (赞：0)

# 思想

看上去是一个字符串大毒瘤题，一般来讲带括号的都是分治。

但是直接分治不太好做，考虑把分治的结构记下来，形成一棵树，记录他的儿子们，从左到右记。

这样输出的时候记录深度，如果深度是奇数就从左向右遍历，否则从右向左遍历。

可以把括号的每一段都记下来当成叶子，这样只要遍历到叶子就可以按照深度进行输出，但是注意，如果是两边被括号包围或就是整个字符串的时候，就要按照深度加一来输出。

具体来讲，记录第 $i$ 位以前有多少个括号，这样只要比对左端点与右端点的数量是否相等就是这一段是否是叶子。

为了保证复杂度，我们记录每一位下一个括号是什么，还有每个左括号对应哪个右括号，这样我们在分治的时候只需要用一个指针跳来跳去就可以了。

# 代码

```cpp
// Coded by LightningCreeper
#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 5e5 + 5;

string a[MAXN];

string s;
int to[MAXN], x[MAXN], nxt[MAXN], tot;

struct Node {
    vector<int> sons;
    int l, r;
} tr[MAXN * 5];

void build(int k, int l, int r) {
    tr[k].l = l;
    tr[k].r = r;
    if (x[l] == x[r])
        return;
    int left = l, right = nxt[l - 1] - 1;
    // cerr << left << " " << right << endl;
    while (right <= r && left <= r) {
        if (left <= right) {
            tot++;
            tr[k].sons.push_back(tot);
            build(tot, left, right);
        }

        left = right + 2;
        if (to[left - 1])
            right = to[left - 1] - 1;
        else
            right = nxt[left - 1] - 1;
    }
}
int n;

void read(int k, int dep) {
    // cerr << k << " " << dep << endl;
    if (x[tr[k].l] == x[tr[k].r]) {
        if (s[tr[k].l - 1] == '(' && s[tr[k].r + 1] == ')' || tr[k].l == 1 && tr[k].r == n)
            dep++;
        if (dep % 2 == 0) {
            for (int i = tr[k].l; i <= tr[k].r; i++)
                cout << s[i];
        } else {
            for (int i = tr[k].r; i >= tr[k].l; i--) {
                if (isupper(s[i]))
                    cout << (char)tolower(s[i]);
                else
                    cout << (char)toupper(s[i]);
            }
        }
        return;
    }
    if (dep % 2 == 1)
        for (int i = 0; i < tr[k].sons.size(); i++) {
            read(tr[k].sons[i], dep + 1);
        }
    else
        for (int i = tr[k].sons.size() - 1; i >= 0; i--) {
            read(tr[k].sons[i], dep + 1);
        }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> s;
    n = s.size();
    s = " " + s;
    stack<int> st;
    for (int i = 1; i <= n; i++) {
        if (s[i] == '(') {
            x[i]++;
            st.push(i);
        } else if (s[i] == ')') {
            x[i]++;
            int j = st.top();
            st.pop();
            to[j] = i;
        }
    }

    for (int i = 1; i <= n; i++)
        x[i] += x[i - 1];

    int now = n + 1;
    for (int i = n; i >= 0; i--) {
        nxt[i] = now;
        if (s[i] == ')' || s[i] == '(')
            now = i;
    }

    tot = 1;
    build(1, 1, n);
    read(1, 1);

    return 0;
}
// Everyone cannot copy this code to judge
```

---

## 作者：fuxiheng (赞：0)

### 题意
给你一个序列，每次可以寻找一个合法括号对满足其中没有括号，且字母要么都是大写，要么都是小写。翻转这个括号对间的字母并且大小写互换并删除两遍的括号。求最后的结果是什么。
### 分析
由于题目保证了不管按照什么顺序操作都可以得到相同的结果，那么就正常按照括号序列做。用一个栈来找匹配的括号对，每次翻转这个区间的字母，用平衡树做就可以了。其实就是模拟题意。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
namespace Luo_ty{
	random_device R;
	mt19937 G(R());
	int rd(int l, int r){
		return uniform_int_distribution<int>(l, r)(G);
	}
	const int MAXN = 500005, inf = 0x7fffffff / 2;
	char ch[MAXN];
	int id[MAXN];
	struct node{
		int lson, rson, pri, rev, sz;
		char v;
	}treap[MAXN];
	void change_val(char &c){
		if('A' <= c && c <= 'Z') c = c - 'A' + 'a';
		else c = c - 'a' + 'A';
	}
	void pushdown(int x){
		if(!treap[x].rev) return ;
		int ls = treap[x].lson, rs = treap[x].rson;
		treap[ls].rev ^= 1;
		swap(treap[ls].lson, treap[ls].rson);
		change_val(treap[ls].v);
		treap[rs].rev ^= 1;
		swap(treap[rs].lson, treap[rs].rson);
		change_val(treap[rs].v);
		treap[x].rev = 0;
	}
	void pushup(int x){
		treap[x].sz = treap[treap[x].lson].sz + treap[treap[x].rson].sz + 1;
	}
	void split(int x, int &lroot, int &rroot, int sz){
		if(!x){
			lroot = rroot = 0;
			return ;
		}
		if(treap[treap[x].lson].sz + 1 <= sz){
			lroot = x;
			pushdown(x);
			split(treap[x].rson, treap[lroot].rson, rroot, sz - treap[treap[x].lson].sz - 1);
		}
		else{
			rroot = x;
			pushdown(x);
			split(treap[x].lson, lroot, treap[rroot].lson, sz);
		}
		pushup(x);
	} 
	void merge(int &x, int lroot, int rroot){
		if(!lroot || !rroot){
			x = lroot | rroot;
			return ;
		}
		if(treap[lroot].pri >= treap[rroot].pri){
			x = lroot;
			pushdown(x);
			merge(treap[x].rson, treap[lroot].rson, rroot);
		}
		else{
			x = rroot;
			pushdown(x);
			merge(treap[x].lson, lroot, treap[rroot].lson);
		}
		pushup(x);
	}
	void print(int x){
		if(!x) return ;
		pushdown(x);
		print(treap[x].lson);
		printf("%c", treap[x].v);
		print(treap[x].rson);
	}
	int stk[MAXN], top, cnt, pre[MAXN], nxt[MAXN];
	int main(){
		scanf("%s", ch + 1);
		int len = strlen(ch + 1);
		int tmp = 0, Rt = 0;
		for(int i = 1;i <= len;i++){
			if(ch[i] == '(' || ch[i] == ')') continue;
			id[i] = ++tmp;
			treap[++cnt] = (node){0, 0, rd(1, inf), 0, 1, ch[i]};
			merge(Rt, Rt, cnt);
		}
		if(!id[1]) id[1] = 1;
		if(!id[len]) id[len] = len;
		pre[1] = 1;
		for(int i = 2;i <= len;i++){
			if(ch[i] != '(' && ch[i] != ')') continue;
			if(ch[i - 1] != '(' && ch[i - 1] != ')') pre[i] = i - 1;
			else pre[i] = pre[i - 1];
		}
		nxt[len] = len;
		for(int i = len - 1;i;i--){
			if(ch[i] != '(' && ch[i] != ')') continue;
			if(ch[i + 1] != '(' && ch[i + 1] != ')') nxt[i] = i + 1;
			else nxt[i] = nxt[i + 1];
		}
//		for(int i = 1;i <= len;i++) printf("%d %d %d\n", i, pre[i], nxt[i]);
		for(int i = 1;i <= len;i++){
			if(ch[i] == '('){
				stk[++top] = i;
			}
			if(ch[i] == ')'){
				int l = id[nxt[stk[top--]]], r = id[pre[i]];
				int rt1, rt2, rt3, rt4;
				split(Rt, rt1, rt2, r);
				split(rt1, rt3, rt4, l - 1);
				treap[rt4].rev ^= 1;
				swap(treap[rt4].lson, treap[rt4].rson);
				change_val(treap[rt4].v);
				merge(rt1, rt3, rt4);
				merge(Rt, rt1, rt2);
			}
//			print(Rt);
//			puts("");
		}
		print(Rt);
		return 0;
	}
} 
int main(){
	return Luo_ty::main();
}
```

---

## 作者：UniGravity (赞：0)

## Solution AT_abc350_f [ABC350F] Transpose
可以作为很好的一道 [文艺平衡树](https://www.luogu.com.cn/problem/P3391) 练习题。

~~当然这题还有一些线性做法，不过本文主要讲解文艺平衡树相关做法。~~

---

看到 $T=\overline{S_{r-1}S_{r-2}\ \dots\ S_{l+1}}$ 的形式，其实就是将 $(l,r)$ 区间翻转并改变大小写。

区间翻转？直接上文艺平衡树板子。

---

关于实现，不仅要维护区间翻转还要维护大小写改变。直接在维护时将 `val[i]` 的值翻转一下即可。
```cpp
inline void pushdown(int x) {
	if (!lazy[x]) return;
	lazy[x] = 0, lazy[ch[x][0]] ^= 1, lazy[ch[x][1]] ^= 1;
	val[x] = -val[x]; // 多加的一行
	swap(ch[x][0], ch[x][1]); 
}
```

为了方便处理 `(` 和 `)`，将字母拎出来塞进另一个序列，记录一下它们原来在哪里即可。

这样只需要对 `(` 和 `)` 开个栈跑括号序列，跳栈时在新序列上进行翻转操作。

```cpp
scanf("%s", s + 1); m = strlen(s + 1); n = 0;
for (rnt i = 1; i <= m; i++) {
    if (s[i] != '(' && s[i] != ')') {s2[++n] = s[i];}
    idxx[i] = n;
}
a[1] = -INF, a[n + 2] = INF;
for (int i = 2; i <= n + 1; i++) a[i] = i - 1;
root = build(0, 1, n + 2);
stack< int > stk;
for (rnt i = 1; i <= m; i++) {
    if (s[i] == '(') {
        stk.push(i);
    } else if (s[i] == ')') {
        rnt v = stk.top(); stk.pop();
        rev(idxx[v] + 1, idxx[i]);
    }
}
print(root);
for (rnt i = 2; i <= n + 1; i++) {
    char tmp = s2[abs(a[i])];
    if (a[i] < 0) {
        if ('a' <= tmp && tmp <= 'z') tmp += 'A' - 'a';
        else tmp += 'a' - 'A';
    }
    putchar(tmp);
}
```

---

## 作者：Starrykiller (赞：0)

题目很良心地给了性质：无论按照何种顺序操作，结果是不变的。那么我们利用栈可以在 $\Theta(|S|)$ 的时间内确定一个操作序列。

然后你发现操作其实就是：

- 将 $[l,r]$ 翻转（reverse）；
- 将 $[l,r]$ 内的大小写互换。

你发现这就是文艺平衡树（多了一个 tag）。完全不需要考虑括号，因为你可以最后不输出括号，这样就可以简化操作。

于是时间复杂度是 $\Theta(n\log n)$ 的。

[My implementation](https://atcoder.jp/contests/abc350/submissions/52592300).

---

