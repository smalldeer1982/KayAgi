# [ABC243D] Moves on Binary Tree

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc243/tasks/abc243_d

頂点数 $ 2^{10^{100}}-1 $ の完全二分木があり、頂点には $ 1,2,...,2^{10^{100}}-1 $ の番号がついています。  
 頂点 $ 1 $ が根であり、各 $ 1\leq\ i\ <\ 2^{10^{100}-1} $ について、頂点 $ i $ は 頂点 $ 2i $ を左の子、頂点 $ 2i+1 $ を右の子として持ちます。

高橋君は最初頂点 $ X $ におり、$ N $ 回移動を行います。移動は文字列 $ S $ により表され、$ i $ 回目の移動は次のように行います。

- $ S $ の $ i $ 番目の文字が `U` のとき、今いる頂点の親に移動する
- $ S $ の $ i $ 番目の文字が `L` のとき、今いる頂点の左の子に移動する
- $ S $ の $ i $ 番目の文字が `R` のとき、今いる頂点の右の子に移動する

$ N $ 回の移動後に高橋君がいる頂点の番号を求めてください。なお、答えが $ 10^{18} $ 以下になるような入力のみが与えられます。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^6 $
- $ 1\ \leq\ X\ \leq\ 10^{18} $
- $ N,X $ は整数
- $ S $ は長さ $ N $ であり、`U`,`L`,`R` のみからなる
- 高橋君が根にいるとき、親に移動しようとすることはない
- 高橋君が葉にいるとき、子に移動しようとすることはない
- 高橋君が $ N $ 回の移動後にいる頂点の番号は $ 10^{18} $ 以下である

### Sample Explanation 1

完全二分木は次のような構造をしています。 !\[図\](https://img.atcoder.jp/ghi/9e199e154f481af436c8eaec9c487e2c.png) 各移動により、高橋君がいる頂点の番号は $ 2\ \to\ 1\ \to\ 3\ \to\ 6 $ と変化します。

### Sample Explanation 2

移動の途中過程において、高橋君がいる頂点の番号が $ 10^{18} $ を超えることもあります。

## 样例 #1

### 输入

```
3 2
URL```

### 输出

```
6```

## 样例 #2

### 输入

```
4 500000000000000000
RRUU```

### 输出

```
500000000000000000```

## 样例 #3

### 输入

```
30 123456789
LRULURLURLULULRURRLRULRRRUURRU```

### 输出

```
126419752371```

# 题解

## 作者：wizardMarshall (赞：2)

[原题传送门](https://atcoder.jp/contests/abc243/tasks/abc243_d)

本蒟蒻的第一篇题解。

题目意思楼上讲得很清楚了，这里不再赘述。

### 思路：

我们知道最终答案坑定是小于 $10^{18}$ 的，唯一要担心的就是中途走很长一段路（连续的 `L` 或 `R` ）然后再连续一串 `U` 返回。这样做虽然答案也是 $<10^{18}$ 的，但是中途不能保证。

所以，我们要把全部的 `U` 都删光，只剩下 `LR`。这个时候就可以随便走而不会出界了。

我们要删光 `LR`，~~最简单的~~方法就是将它们的坐标放进栈里，每次遇到 `U` 就出栈并删除它。

注意：`U` 不会全部删光，如果当前栈空或者它是开头的U就不会删。

### 代码：

```c
#include <bits/stdc++.h>
using namespace std;
stack <int> q;
signed main() {
	long long n, x;
	cin >> n >> x;
	string s;
	cin >> s;
	int len = s.size();
	for (int i = 0; i < len; i++) {
		if (s[i] == 'U') {//如果当前是U就出栈，把上一个L或R删掉
			if (!q.empty()) {
				s[q.top()] = 0;q.pop();s[i] = 0;
			}
		}else {//否则就入栈
			q.push(i);
		}
	}for (int i = 0; i < len; i++) {
		if (s[i] == 'L')x *= 2;
		else if (s[i] == 'R')x = x * 2 + 1;
		else if (s[i] == 'U')x /= 2;//一开始的U不会删，所以还是要算
	}cout << x;
	return 0;
}
```

---

## 作者：IGA_Indigo (赞：1)

## 题意分析
这道题的意思就是在一个非常非常大的完全二叉树之中，你在一个点 $x$ 上，每次可以向左下 `L`、向右下 `R` 或向上 `U` 走，问你在 $n$ 次移动后的位置，而且保证答案不会超过 $10^{18}$。
## 大体思路
因为中间路程可能会超过 $10^{18}$，但是答案却不会，我们观察到一个 `U` 操作和一个 `L` 或 `R` 是可以抵消的，所以我们可以在操作中先消掉这些可能会超 $10^{18}$ 的操作，方法是用一个栈来记录每一个 `L` 或 `R` 操作，如果遇到 `U` 操作就退栈，把这些操作化简完后再模拟。

代码中有详细的注释。
## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
long long read(){
	long long x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-'){
			f=-1;
		}
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}
void write(long long x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9){
		write(x/10);
	}
	putchar(x%10+'0');
	return ;
}
stack<int> q;
int main(){
	long long n,x;
	n=read();
	x=read();
	string s;
	cin>>s;//先把所有操作记录下来
	s=' '+s; 
	for(int i=1;i<=n;i++){
		if(s[i]=='L'||s[i]=='R'){//如果是L或R操作，入栈
			q.push(i);
		}
		else{//如果是U操作，分情况讨论 
			if(!q.empty()){//如果之前没有过L或R操作，就不能抵消
				int hh=q.top(); 
				s[hh]=' ';//删掉上一个L或R操作 
				q.pop();
				s[i]=' ';//删掉这一个U操作 
			}
		}
	}
	for(int i=1;i<=n;i++){//最后正常模拟即可 
		if(s[i]=='L'){
			x*=2;
		}
		else if(s[i]=='R'){
			x=x*2+1;
		}
		else if(s[i]=='U'){
			x/=2;
		}
	}
	write(x);
	return 0;
}
```

---

## 作者：chengning0909 (赞：1)

# abc 243 d

[AT 链接](https://atcoder.jp/contests/abc243/tasks/abc243_d)

[洛谷链接](https://www.luogu.com.cn/problem/AT_abc243_d)

## 题意

有一个有着 $2 ^ {10 ^ {100}} - 1$ 个结点的完全二叉树，每个结点编号为 $1, 2, \dots, 2 ^ {10 ^ {100}} - 1$。$1$ 号结点是根结点，对于 $1 \le i < 2 ^ {10 ^ {100}} - 1$ 中的每个 $i$，结点 $i$ 有两个子节点：左儿子 $2i$ 和右儿子 $2i + 1$。

Takahashi 从顶点 $X$ 开始执行 $N$ 次移动，用字符串 $S$ 表示。第 $i$ 次移动如下：

- 如果 $S$ 的第 $i$ 个字符为 `U`，则转到他现在所在顶点的父节点。

- 如果 $S$ 的第 $i$ 个字符为 `L`，则转到他现在所在顶点的左孩子。

- 如果 $S$ 的第 $i$ 个字符为 `R`，则转到他现在所在顶点的右孩子。

找到 $N$ 次移动后 Takahashi 所在的结点编号，保证答案最多为 $10 ^ {18}$。

## 思路

### 暴力

若当前是第 $i$ 次操作，并且在 $A$ 号结点上，那么：

- 如果 $S_i = $ `U`，$A \rightarrow \lfloor \frac{A}{2} \rfloor$。

- 如果 $S_i = $ `L`，$A \rightarrow 2 \times A$。

- 如果 $S_i = $ `R`，$A \rightarrow 2 \times A + 1$。

最后输出即可。

### 正解

由于题目并没有保证在移动的过程中的结点编号最多为 $10 ^ {18}$，所以，肯定不能直接模拟。

#### 做法 1

栈。

如果先做了 `L` 或 `R` 操作，再做了 `U` 操作，实际上还是在这个点上。

那么，我们只要将所有的 `L` 和 `R` 存入栈中，每次遇到一个 `U` 就弹出栈顶即可。

最后，将剩下的操作全部模拟即可。

时间复杂度为 $O(N)$。

#### 做法 2

二进制。

先将 $X$ 转成二进制，用一个 01 串 $A$ 表示。

若当前是第 $i$ 次操作，那么：

- 如果 $S_i = $ `U`，$A$ 的长度减少 1。 

- 如果 $S_i = $ `L`，在 $A$ 的末尾加上 $0$。

- 如果 $S_i = $ `R`，在 $A$ 的末尾加上 $1$。

时间复杂度为 $O(N + \log X)$。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 1e7 + 10;

int n, x[N], len;
string s;
int top, stk[N];

void F() {
  long long p;
  cin >> p;
  while (p) {
    x[len++] = p % 2, p /= 2;
  }
  for (int i = len - 1; i >= 0; i--) {
    stk[++top] = x[i];
  }
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  F(); // 转二进制
  cin >> s;
  for (int i = 0; i < s.size(); i++) {
    if (s[i] == 'U') {
      top--;
    } else if (s[i] == 'L') {
      stk[++top] = 0;
    } else {
      stk[++top] = 1;
    }
  }
  long long ans = 0;
  for (long long i = 1; top; top--, i *= 2) {
    ans += stk[top] * i; // 转回十进制
  }
  cout << ans;
  return 0;
}
```

---

## 作者：liuyi0905 (赞：0)

# [[ABC243D] Moves on Binary Tree](https://www.luogu.com.cn/problem/AT_abc243_d) 题解
### 思路：
方法1：

直接模拟，答案高达 $2^{10^6}$ 或更多，溢出。

方法2：

每次走到左子节点（或右子节点），再走到父节点，将会回到原节点，所以 `U` 操作可以和 `L` 或 `R` 操作抵消。

考虑用**栈**维护每次的操作，当遇到一个 `U`，若栈不为空，就将栈 `pop`；否则直接将 $X$ 除以 $2$。

最后从栈底向上遍历一遍栈，依题意计算答案即可。

记得开 `long long`。

~~继承 yl 优良传统，不用 STL！~~
### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e6+5;
ll n,x,m,tp;
char c,s[N];
int main(){
  cin>>n>>x;
	for(int i=1;i<=n;i++)
    cin>>c,c=='U'?(tp?tp--:x/=2):(s[++tp]=c,1);
  for(int i=1;i<=tp;i++)
    x=2*x+(s[i]=='R');
  cout<<x;
}
```

---

## 作者：zcr0202 (赞：0)

## 题目大意

给你一个很大的二叉树，让你执行一串序列，求此时在哪个点。

## 解题思路

我们可以发现，$u$ 操作其实就是倒退操作，那么我们可以创建一个数组，里面记录实际要执行的操作，也就是去重操作之后的串，之后我们就可以正常模拟了。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define fre(a) freopen(#a".in", "r", stdin), freopen(#a".out", "w", stdout);
#define up(i, a, b) for(int i = a; i <= b; i++)
#define down(i, a, b) for(int i = a; i >= b; i--)
using namespace std;
const int N = 1e6 + 5;
const int mod = 1e9 + 9;
int n, x;
string s;
int a[N], d;
signed main() {
    cin >> n >> x >> s;
    s = ' ' + s;
    up(i, 1, n) {
        if (s[i] == 'L' || s[i] == 'R') {
            a[++d] = i;
        }
        else {
            if (d != 0) {
                s[a[d]] = ' ';
                a[d] = 0;
                d--;
                s[i] = ' ';
            }
        }
    }
    up(i, 1, n) {
        if (s[i] == 'L') {
            x *= 2;
        }
        else if (s[i] == 'R') {
            x = x * 2 + 1;
        }
        else if(s[i] == 'U'){
            x /= 2;
        }
    }
    cout << x;
    return 0;
}
```

---

## 作者：ziyistudy (赞：0)

无需栈的做法。

发现答案不会超过 $10^{18}$，又发现 $2^{60}=1152921504606846976 \approx 10^{18}$ 且不会爆精度。所以得到这棵树有 $2^{60}-1$ 个点，共 $60$ 层。

那么如果这个点的儿子不会爆精度，则直接求得儿子的编号。否则记录往下几个（注意：不用记录往左还是往右，因为这是最后一层，超过这一层点具体是多少已经不重要了，最重要的是记录它在第几层）。如果是回到父亲，则使数组减少。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define eb emplace_back
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
typedef vector<int> VI;
typedef long long ll;
typedef pair<int,int> PII;
const ll MOD=998244353;
// head
const int MAXN=1152921504606846975/2;
signed main() 
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

	int n,x;cin>>n>>x;
	string s;cin>>s;
	int now=x;
	int cnt=0;
	for(int i=0;i<s.length();i++){
		if(s[i]=='U'){
			if(cnt==0) {
				if(now%2) now=(now-1)/2;
				else now=now/2;
			}
			else cnt--;
		}
		else {
			if(now<=MAXN) {
				if(s[i]=='L') now*=2;
				else now=now*2+1;
			}
			else cnt++;
		}
	}
	cout<<now<<endl;
}
```

---

## 作者：MA_tian (赞：0)

# 前言

讲一种~~偷懒一点的~~做法。

最简单的方式就是暴力模拟，可是写完暴力后一交——wa 了！这是因为在模拟的过程中，你的 `long long` 爆了。

顺带一提，这题正解是二进制。

可我就是想写暴力，怎么办呢？当然是优化。

# 正文

我们通过观察可以发现，假设当前节点为 `x`，那么当字母 `U` 时，$x=x/2$，当字母为 `L` 时，$x=x\times 2$，当字母为 `R` 时，$x=x\times 2+1$。

聪明的你一定发现了，`U` 和 `L` 可以抵消。而且题目中有保证，最终的输出一定小于 $10^9\times10^9$，正好是 `long long` 的范围！

接下来直接用栈，遇到 `U` 就判断，如果有 `LR` 就删除，没有就存着。

上代码。
```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	int n;
	stack<int>u;
	long long x;
	cin>>n>>x;
	string s;
	cin>>s;
	for(int i=0;i<n;i++){
		if(s[i]=='U'){
			if(!u.empty()){
				s[u.top()]=0;
				u.pop();
				s[i]=0;
			}
		}else{
			u.push(i);
		}
	}
	for(int i=0;i<n;i++){
		if(s[i]=='L'){
			x*=2;
		}else if(s[i]=='R'){
			x*=2;
			x++;
		}else if(s[i]=='U'){
			x/=2;
		}
	}
	cout<<x;
	return 0;
}
```
完结撒花！

~~最后夹带点私货~~

自我踏上这土地，邪恶便不该存在！

---

## 作者：mojoege (赞：0)

## 题意
有一棵无限大的完全二叉树，根结点为 $1$，结点 $i$ 的左子结点为 $2i$，右子结点为 $2i+1$。  

高桥君从结点 $X$ 开始进行 $N$ 次移动，每次移动用一个字符表示：  

- `U`：移动到当前结点的父结点。 
- `L`：移动到当前结点的左子结点。
- `R`：移动到当前结点的右子结点。

移动序列为一个长度为 $N$ 的字符串 $S$。给定 $N,X,S$，求按照 $S$ 依次进行 $N$ 次移动后高桥所处的结点编号。

## 分析

有思维，但不多。

读题很容易发现 `L` 和 `R` 操作是可以和 `U` 操作抵消掉的（必须是 `U` 在 `L` 和 `R` 的后面），那就可以先按括号匹配的方式处理一遍，接着模拟输出。具体的，遇到 `L` 或 `R` 就入；如果是 `U` 且栈空，那么将 `U` 加入栈内，否则将栈顶弹出（抵消）。**在抵消的时候要判断栈内要抵消的那个元素是不是 `U`，如果是就不操作**。

注意，最终操作序列是上面记录的栈中从栈底到栈顶的序列。

但是为什么这样做不会越界？模拟一遍，我们发现最终操作序列中肯定是一堆 `U` 后面跟着 `L` 和 `R`，先上再下肯定不会炸（题目保证最终答案不会炸）。

## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int n, x;
string s;
stack<char> st, stk;

signed main(){
	cin >> n >> x >> s;
	for (int i = 0; i < s.size(); i++){
		if (s[i] == 'U'){
			if (!st.empty() && (st.top() == 'L' || st.top() == 'R')) st.pop();//判断是否栈空 & 是否是 L 或 R
			else st.push(s[i]);
		}
		else st.push(s[i]);
	}
	while (!st.empty()) stk.push(st.top()), st.pop();//求最终操作序列
	while (!stk.empty()){//模拟一遍
		char c = stk.top(); stk.pop();
		if (c == 'U') x /= 2;
		if (c == 'L') x *= 2;
		if (c == 'R') x = x * 2 + 1;
	}
	cout << x;
	return 0;
}
```

---

## 作者：majoego (赞：0)

显然，如果直接暴力去做，显然会炸，或许高精度是可以的？

但是，我们有更巧妙的方式。

因为题目说了，保证最后的答案在 long long 范围。我们发现往上走和往下走以互相消除的，所以我们只需要保证每一次操作都是往下走，那就不会炸。所以我们可以维护一个栈，然后对于一个往上走的操作，我们就把栈顶（往下走）的操作抵消掉，类似于括号匹配。这样就可以成功消除所以的往上走。但是，如果此时栈顶为空咋办？很好办，我们直接暴力把此时的位置除以 $2$。等到最后，栈里面只有一堆往左还是往右的数，所以，直接往下暴力的跳即可。

[link](https://atcoder.jp/contests/abc243/submissions/51177734)。

---

## 作者：_qingshu_ (赞：0)

# 题意：

给定一颗有 $2^{10^{100}}-1$ 个结点的完全二叉树，有 $N$ 次操作，每一次操作可以走向当前位置的一个相邻的节点，问最后所在的结点编号。

# 思路：

首先，这个令人惊惧的 $2^{10^{100}}$ 应该是存疑的，我们最多有 $10^6$ 次操作，每一次操作对多扩张至 $2 \times x +1$。粗略计算（忽视 $+1$ ）那么我们最多扩展到 $10^{18} \times 2^{10^{6}}$ 个点。显然，我们依旧无法存下它。

继续考虑可以操作的变量，发现操作数仅有 $10^6$。那么我们就可以考虑操作路径。

既然这个数已经是按位存数组都存不下的大小了，那么一定可以优化路径，也就是不需要到达路径最大值。

首先，我们考虑什么情况是可以合并的。易证仅有前一个操作是（忽略被弹出的操作）向儿子走的情况且本次操作是向父亲走是可以被合并的。不理解的可以手模一下。

既然确定了可以合并的路径，那么我们用数组模拟下栈就好了。

时间复杂度 $O(N)$。

# code：

```cpp
#include<bits/stdc++.h>
using namespace std;
char ton[5200010];
long long tot;
long long n;
long long x;
char s;
int main(){
	cin>>n>>x;
	for(long long i=1;i<=n;i++){
		cin>>s;
		if(s=='U'){
			if(tot&&ton[tot]!='U'){
				tot--;
			}
			else{
				ton[++tot]=s;
			}
		}
		else{
			ton[++tot]=s;
		}
	}
	for(long long i=1;i<=tot;i++){
		if(ton[i]=='U'){
			x/=2;
		}
		else if(ton[i]=='R'){
			x*=2;
			x++;
		}
		else{
			x*=2;
		}
	}
	cout<<x;
}
```

---

## 作者：_shine_ (赞：0)

#### 法一
首先能想到一件事情：字符 ```U``` 与字符 ```L``` 或 ```R``` 是可以相抵消的。

随后不难想到，虽然运算过程中可能会大于 $10^{18}$，但如果尽量的把字符 ``` U``` 去跟 ```L``` 和 ```R``` 相抵消，那就可以保证整个运算尽量的小。

但是要注意的是，```U``` 是不能全部相抵消的，比如说像 ```UL``` 或 ```UR``` 的情况下可能会走到另一个儿子，这是只需要正常操作即可。
#### 法二
稍加思考就可以发现，这个就很像一个二叉树的形式，$0$ 代表 ```L```，$1$ 代表 ```R```，每次执行 ```U``` 操作是只需要删除最后一位就好了。

个人认为这种方法较为好懂。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn=1e6+10;
stack<int>s;
int n;
ll x;
string p;
signed main(){
    scanf("%d%lld",&n,&x);
    cin >> p;
    for(int i=0;i<p.size();++i){
        if(p[i]=='U'){if(s.size()!=0)s.pop();else x/=2;}
        else if(p[i]=='L')s.push(1);
        else s.push(0);
    }
    stack<int>q;
    while(s.size()!=0){q.push(s.top());s.pop();}
    while(q.size()!=0){if(q.top()==0)x=x*2+1;else x=x*2;q.pop();}
    printf("%lld\n",x);
    return 0;
}
```


---

## 作者：yhylivedream (赞：0)

考虑用二进制来解。

## 【思路】

我们可以按照题意来模拟，不过，题目只保证答案在 $10^{18}$ 以内，不保证过程在 $10^{18}$ 内，所以我们可以考虑先将 $X$ 转为二进制，对 $X$ 进行操作，再将 $X$ 转为十进制。

对于三种操作：

1. $S_i$ 为 `U`：去掉 $X$ 末尾的数，对应位运算中的右移 $1$。

1. $S_i$ 为 `L`：在 $X$ 的末尾添上 $0$，对应位运算中的左移 $1$。

1. $S_i$ 为 `R`：在 $X$ 的末尾添上 $1$，对应位运算中的右移 $1$ 加 $1$。

十进制转二进制用短除法，二进制转十进制按位展开，就不废话了。

时间复杂度分析：因为我们要对 $X$ 做 $N$ 次操作，而十进制转二进制复杂度为 $O(\log X)$，总复杂度为 $O(N + \log X)$。

另外啰嗦一句，短除法的时间复杂度为 $O(\log_N X)$，其中 $N$ 为进制，$X$ 为要转进制的数。

## 【代码】：

代码很容易实现，不贴了。

完结撒花啦！！！

---

## 作者：c20231020 (赞：0)

### 题目链接
[luogu](https://www.luogu.com.cn/problem/AT_abc243_d)

[atcoder](https://atcoder.jp/contests/abc243/tasks/abc243_d)

### 题目大意

有一个完全二叉树，有 $2^{10^{100}}-1$ 个节点，编号为 $1,2,\dots,2^{10^{100}}-1$。

节点 $1$ 是根。对于每个 $i$ $\forall$ $[1,2^{10^{100}})$，节点 $i$ 有两个子节点：左儿子 $2i$ 和右儿子 $2i+1$。


高桥从节点 $X$ 并执行 $N$ 个移动，由字符串 $S$ 表示。第 $i$ 步遵循如下规则：

+ 如果 $S$ 中第 $i$ 个字符是 `U`，转到他现在所在节点的父节点。
+ 如果 $S$ 中第 $i$ 个字符是 `L`，转到他现在所在节点的左儿子。
+ 如果 $S$ 中第 $i$ 个字符是 `R`，转到他现在所在节点的右儿子。


找到高桥在 $N$ 次移动后所在节点的编号。在给定的情况下，可以保证答案最多为 $10^{18}$。

### 思路

读完题后，发现**答案最多为 $10^{18}$**，但是高桥在移动过程中会到编号大于 $10^{18}$ 的节点？

例如：

```
1000000 1000000000000000000
RRRRRRRR ... RRUU ... UUUUUUUU
```

如果操作列表中有类似 `RU` 或 `LU` 的情况，那么可以将它们去掉（重复操作）。

但是，不能去掉 `UR` 或 `UL`！！！因为可能从一个儿子走到另一个儿子。（反正不处理也不会溢出）

所以，对于上面那个极端数据，将字符放入一个栈里面，每次读到 `U` 是判断栈顶是否是 `L` 或 `R`，是的话就退一次栈，最后按照栈中的字符模拟一遍即可。

复杂度很优秀，$O(N)$。

#### code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,x,p;
char c,st[1000100];
//st是栈，p是栈指针
int main(){
	scanf("%lld %lld\n",&n,&x);
	for(ll i=1;i<=n;i++){
		scanf("%c",&c);
		if(i!=1){//防止RE
			if(c=='U'&&(st[p-1]=='L'||st[p-1]=='R')){
				p--;//出现RU或LU情况，退栈
			}else{
				st[p]=c;//否则入栈
				p++;
			}
		}else{
			st[p]=c;
			p++;
		}
	}
	for(ll i=0;i<p;i++){
		if(st[i]=='U')x/=2;
		else if(st[i]=='L')x=x*2;
		else if(st[i]=='R')x=x*2+1;
	}//直接模拟即可
	printf("%lld",x);
	return 0;
}
```

---

## 作者：中缀自动机 (赞：0)

题意：

- 有一棵 $2^{10^{100}}-1$ 个点的完全二叉树，每个点的编号依次为 $1,2,3,...,2^{10^{100}}-1$。对于树上任意一个非叶子节点 $i$，满足其左儿子编号为 $2 \times i$，其右儿子编号为 $2 \times i+1$。现在给定树上的一个点 $X$ ，对其进行 $N$ 次移动，每次走到它的父亲、左儿子或右儿子。询问 $N$ 次操作后，它所到达的点的编号。

- $1 \leqslant N \leqslant 10^{6}$
 
- $1 \leqslant X \leqslant 10^{18}$
 
- $S$ 为一个长度为 $N$ 的 $ULR$ 数组，表示它的移动方向。

- 数据保证合法 

- 答案不会超过long long范围


------------

思路:

用 deque 存储移动操作。枚举 $S$ 字符串，若队列为空或队尾元素为 $U$ 或当前字符为 $L$ 或 $R$，将当前字符加入队尾；否则当前字符为 $U$，队尾元素为 $L$ 或 $R$ 时，可以用 $U$ 来抵消 $L$ 或 $R$ 的操作，将队尾元素出队。
这样做可以保证 $U$ 操作在整个队列的前端，而 $L$ 或 $R$ 操作在整个队列后端，可以保证移动过程中点编号不会超出 $\operatorname{long long}$范围。
最后依次将队头出队，每次对 $X$ 进行移动操作即可。


------------
代码：
```cpp
#include<iostream>
#include<string>
#include<deque>
using namespace std;
string s;
deque<char>q;
long long n,x;
bool vis[8];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>x>>s;
    for(int i=0;i<s.size();i++){
        if(s[i]=='L'||s[i]=='R'||q.empty()||q.front()=='U') q.push_front(s[i]);
        else q.pop_front();
    }
    while(!q.empty()){
        if(q.back()=='U') x/=2;
        if(q.back()=='L') x*=2;
        if(q.back()=='R') x=x*2+1;
        q.pop_back();
    }
    cout<<x;
    return 0;
}
```


---

