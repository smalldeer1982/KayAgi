# [AGC044D] Guess the Password

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc044/tasks/agc044_d

**这是一个交互式问题。**

你的任务是猜出一个秘密密码 $S$。密码是一个长度不超过 $L$ 的非空字符串，且密码的每个字符都是小写英文字母（a, b, ..., z）、大写英文字母（A, B, ..., Z）或数字（0, 1, ..., 9）中的一个。

你可以通过发送查询来猜测秘密密码 $S$。每次查询，你需要发送一个满足上述密码要求的字符串 $T$，对于每个查询，你将获得 $S$ 和 $T$ 的编辑距离（允许的操作为删除、插入、替换）的结果作为反馈。你最多可以发送 $Q$ 次查询。

**注意：** 编辑距离（允许的操作为删除、插入、替换）的定义可参考 [Wikipedia 上的此页面](https://en.wikipedia.org/w/index.php?title=Levenshtein_distance&oldid=954598393)。

## 说明/提示

### 限制

- $L = 128$
- $Q = 850$
- 秘密密码 $S$ 在程序与评测机交互开始前已被选定。

### 判定

- **每次输出后必须刷新标准输出。** 如果不这样做，评测结果可能会是 `TLE`。
- 输出你认为的秘密密码后，必须立即终止程序。否则评测结果未定义。
- 如果发送了格式不正确的查询（例如，发送的字符串不满足密码要求，输出行首不是 `?`），程序异常终止，或查询次数超过 $Q$，评测结果未定义（不一定是 `WA`）。

### 输入输出样例

在以下示例中，秘密密码为 `Atcod3rIsGreat`。

| 输入 | 输出 |
| :--- | :--- |
| $?\ AtcoderIsBad$ | $5$ |
| $?\ AtcoderIsGreat$ | $1$ |
| $!\ Atcod3rIsGreat$ |  |

由 ChatGPT 4.1 翻译

# 题解

## 作者：jun头吉吉 (赞：15)

## 前言

vp的时候看到zak没有过以为是大难题，看了题解发现难度并不高，但是为什么我写了 $3$ 个小时（详细解密）。
## 题意
有一个长度 $\le 128$，字符集 $\Sigma=\{\texttt{A},\dots,\texttt{Z},\texttt{a},\dots,\texttt{z},\texttt{0},\dots,\texttt{9}\}$ 的字符串 $S$，你不知道它是什么。

每次询问可以给出一个 $T$，交互库会告诉你 $S$ 和 $T$ 的编辑距离。$T$ 也需要满足长度和字符集的限制。

次数限制 $850$。

## 题解

记 $f(S,T)$ 表示 $S$ 和 $T$ 的编辑距离，$L=128$。

首先枚举 $c\in\Sigma$，然后对于一个长度为 $L$ 的全 $c$ 串，$f(S,\overbrace{cc\dots cc}^{L})$ 就是 $L-$ $c$ 在 $S$ 中出现的次数。

用这个我们可以得到每个字符出现了几次，以及 $|S|$。

然后有一个显然的观察就是，如果 $f(S,T)=|S|-|T|$，那么 $T$ 是 $S$ 的子序列。

然后如果我们记 $g(A)$ 表示 $S$ 只保留 $A$ 中的字符留下的字符串，我们可以用上面的结论用 $|g(A)|+|g(B)|-1$ 次询问得到 $g(A\cup B)(A\cap B=\varnothing)$。我们的目标是求 $g(\Sigma)$，对于 $g(A)(|A|=1)$ 我们是已知的，然后对于 $g(A)(|A|>1)$ 可以分成 $A=L\cup R,L\cap R=\varnothing,||L|-|R||\le 1$，这样合并的复杂度是不超过 $L\lceil\log_2|\Sigma|\rceil-|\Sigma|$ 的。次数 $850$ 次肯定是够的。

然后就是怎么合并 $g(A)$ 和 $g(B)$ 的问题了，维护一个新的串 $r$，然后枚举下一位是 $g(A)$ 的还是 $g(B)$ 的，判断方法就是把 $g(A)$ 的下一位加入 $r$，然后把 $g(B)$ 的剩下部分加入 $r$，如果 $r$ 是 $S$ 的子序列则说明下一位是 $g(A)$ 否则下一位来自 $g(B)$。

整道题就做完了。这种题我是怎么调 $3$ 个小时的呢？

```cpp
cout<<"! "<<get(strs)<<endl;
```

这段代码，会先输出 `! `，然后跑 `get(strs)`。太&#129313;了，希望大家引以为鉴。

## 代码

```cpp
const int L=128;
int S;
int ask(string s){
	cout<<"? "<<s<<endl;
	int x;cin>>x;return x;
}
string merge(string A,string B){
	if(!A.size()||!B.size())return A+B;
	string nw;size_t i=0,j=0;
	while(i<A.size()||j<B.size()){
		if(i==A.size())nw+=B[j++];
		else if(j==B.size())nw+=A[i++];
		else{
			string tmp=nw+A[i]+B.substr(j);
			if((size_t)ask(tmp)==S-tmp.size())nw+=A[i++];
			else nw+=B[j++];
		}
	}
	return nw;
}
string get(vector<string>A){
	if(A.size()==1u)return A[0];
	vector<string>L,R;
	for(size_t i=0;i<A.size()/2;i++)L.pb(A[i]);
	for(size_t i=A.size()/2;i<A.size();i++)R.pb(A[i]);
	return merge(get(L),get(R));
}
vector<char>sigma;
vector<int>val;
vector<string>strs;
signed main(){
	for(int i='a';i<='z';i++)sigma.pb(i);
	for(int i='A';i<='Z';i++)sigma.pb(i);
	for(int i='0';i<='9';i++)sigma.pb(i);
	for(auto x:sigma)
		val.pb(L-ask(string(L,x))),strs.eb(val.back(),x);
	S=accumulate(val.begin(),val.end(),0);
	cout<<("! "+get(strs))<<endl;
}
```

---

## 作者：Felix72 (赞：3)

把字符集编号为 $1$ 到 $62$，出现次数为 $cnt_i$，对一个字符串 $s$ 询问的结果为 $query(s)$。

记 $str_i$ 为 $128$ 个 $c_i$ 连接得到的串，则有 $cnt_i = 128 - query(str_i)$。可以花费 $62$ 次操作得到 $cnt$，并得到 $len = \sum_{i = 1}^{62} cnt_i$。

再考虑增量法构造字符串。假设当前有串 $s$，要插入一个 $s$ 中没有的字符 $c$，并保证插入后 $s$ 是答案串的子序列。我们二分插入的位置 $p$：如果串 $c + s_{[p + 1, |s|]}$ 是答案串的子串，那么 $[1, p]$ 中一定有可以插入 $c$ 的位置。

现在还需要解决插入 $s$ 中已经存在的字符的问题。我们发现上一个过程是找到了最左边的 $c$，那么我们在后面二分时把左边界设为这个位置之后一个位置，即可排除已有字符的影响。

```cpp
/* Good Game, Well Play. */
#include <bits/stdc++.h>
#define lowbit(x) ((x) & (-(x)))
using namespace std;

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
bool test_operation = 0, auto_operation = 0;
namespace Judge
{
	int n, m; string Answer = "Naiad", s;
	int f[256][256];
	inline int get(string t)
	{
		s = ' ' + Answer, t = ' ' + t;
		n = s.length() - 1, m = t.length() - 1;
		memset(f, 0x3f, sizeof(f));
		f[0][0] = 0;
		for(int i = 1; i <= n; ++i) f[i][0] = i;
		for(int i = 1; i <= m; ++i) f[0][i] = i;
		for(int i = 1; i <= n; ++i)
		{
			for(int j = 1; j <= m; ++j)
			{
				if(s[i] == t[j]) f[i][j] = min(f[i][j], f[i - 1][j - 1]);
				f[i][j] = min(f[i][j], f[i - 1][j - 1] + 1);
				f[i][j] = min(f[i][j], f[i - 1][j] + 1);
				f[i][j] = min(f[i][j], f[i][j - 1] + 1);
			}
		}
		return f[n][m];
	}
}

const int N = 135, K = 65;
char c[K], s[N]; int n, m, cnt[K], ps[K];
inline bool cmp(int x, int y) {return cnt[x] > cnt[y];}
int Times;
map < string, int > mp;
inline int query(string s)
{
	if(mp.count(s)) return mp[s];
	++Times;
//	assert(Times <= 850);
	if(test_operation) return Judge::get(s);
	cout << "? " << s << '\n';
	int x; cin >> x; mp[s] = x; return x;
}
inline void get_charnum()
{
	for(int i = 1; i <= 62; ++i)
	{
		string str = "";
		for(int j = 1; j <= 128; ++j) str += c[i];
		cnt[i] = 128 - query(str); n += cnt[i];
	}
}
inline int insert(int lim, int num, char c)
{
	int p = m;
	if(m == 0) s[++m] = c;
	else
	{
		int l = lim, r = m - 1;
		while(l <= r)
		{
			int mid = (l + r) >> 1;
			string str = "";
			for(int j = 1; j <= num + 1; ++j) str += c;
			for(int j = mid + 1; j <= m; ++j) str += s[j];
			if(query(str) == n - str.length()) p = mid, r = mid - 1;
			else l = mid + 1;
		}
		++m;
		for(int i = m; i > p + 1; --i) s[i] = s[i - 1];
		s[p + 1] = c;
	}
//	for(int i = 1; i <= m; ++i) cerr << s[i]; cerr << '\n';
	return p + 1;
}

int main()
{
//	freopen("text.in", "r", stdin);
//	freopen("prog.out", "w", stdout);
//	ios::sync_with_stdio(false);
//	cin.tie(0), cout.tie(0);
	if(auto_operation)
	{
		freopen("text.in", "r", stdin);
		freopen("prog.out", "w", stdout);
		cin >> Judge::Answer;
	}
	for(char i = 'a'; i <= 'z'; ++i) c[i - 'a' + 1] = i;
	for(char i = 'A'; i <= 'Z'; ++i) c[i - 'A' + 27] = i;
	for(char i = '0'; i <= '9'; ++i) c[i - '0' + 53] = i;
	get_charnum();
	for(int i = 1; i <= 62; ++i) ps[i] = i;
	sort(ps + 1, ps + 62 + 1, cmp);
	for(int i = 1; i <= cnt[ps[1]]; ++i) s[++m] = c[ps[1]];
	for(int i = 62; i >= 2; --i)
		for(int j = 1, lst = 0; j <= cnt[ps[i]]; ++j)
			lst = insert(lst, j - 1, c[ps[i]]);
	cout << "! "; for(int i = 1; i <= m; ++i) cout << s[i]; cout << '\n';
	if(test_operation)
	{
		string comp = "";
		for(int i = 1; i <= m; ++i) comp += s[i];
		assert(comp == Judge::Answer);
	}
	if(Times > 850) cerr << Times << '\n';
	return 0;
}
/*

*/
```

---

## 作者：zzzyyyyhhhhh (赞：2)

首先可以询问每个字符重复 128 次的串得到答案 $ans$，那么 $ 128-ans $ 就是这个字符在目标串 $T$ 中的出现次数，全部询问完以后 $|T|$ 也可以确定。

编辑距离很不好刻画，于是我们考虑增量法。现在我们已经有一个串 $S$ 是目标串 $T$ 的子序列，我们加入一个字符 $c$，首先想到枚举 $S$ 中相邻的两个位置（包括第一个字符前面后最后一个字符后面）然后把 $c$ 放在这个位置，如果加入后 $S$ 依然是 $T$ 的子序列，当且仅当询问加入后串的两串编辑距离为 $|T|-|S|$。

但这样询问次数过多了，于是可以枚举每种字符，然后把所有这种字符插入 $S$ 中，这样是 $O(|T||\Sigma|)$ 的，还是过不了。这种做法中我们对于每个字符都要花费 $O(|T|)$ 的代价询问，但 $\displaystyle\sum_i^{\Sigma}cnt_i=|T|$ 是较小的，如果我们可以快速求出合法的插入位置就可以了。考虑每次找到这中字符最后合法的插入位置，可以二分找到一个位置 $p$ 使得 $S_{[1,p]}+c$ 合法而 $S_{[1,p+1]}+c$ 不合法，那么要找的这个位置一定在 $p$ 之后。

代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e3+100;
int n;
int cnt[N];
vector<char> ans;
int cc=0;
inline int ask(int x)
{
	cc++;
	cout<<"? ";
	for(int i=1;i<=128;i++)cout<<char(x);
	cout<<endl;
	int r;
	cin>>r;
	return 128-r;
}
inline bool ask(int pos,int tp,int l)
{
	cc++;
	if(cc>850)assert(0);
	cout<<"? ";
	for(int i=1;i<=pos;i++)cout<<ans[i-1];
	for(int i=1;i<=l;i++)cout<<char(tp);
	cout<<endl;
	int r;
	cin>>r;
	return r+pos+l==n;
}
signed main()
{
	for(int i='0';i<='9';i++)cnt[i]=ask(i),n+=cnt[i];
	for(int i='a';i<='z';i++)cnt[i]=ask(i),n+=cnt[i];
	for(int i='A';i<='Z';i++)cnt[i]=ask(i),n+=cnt[i];
	cerr<<n<<'\n';
	for(int i=1;i<=cnt['0'];i++)ans.push_back('0');
	for(int i='1';i<='9';i++)
	{
		int ls=ans.size();
		for(int j=1;j<=cnt[i];j++)
		{
			int l=0,r=ls,mid,o=0;
			while(l<=r)
			{
				mid=(l+r)>>1;
				if(ask(mid,i,j))o=mid,l=mid+1;
				else r=mid-1;
			}
			ans.insert(ans.begin()+o,char(i));
			ls=o;
		}
	}
	for(int i='a';i<='z';i++)
	{
		int ls=ans.size();
		for(int j=1;j<=cnt[i];j++)
		{
			int l=0,r=ls,mid,o=0;
			while(l<=r)
			{
				mid=(l+r)>>1;
				if(ask(mid,i,j))o=mid,l=mid+1;
				else r=mid-1;
			}
			ans.insert(ans.begin()+o,char(i));
			ls=o;
		}
	}
	for(int i='A';i<='Z';i++)
	{
		int ls=ans.size();
		for(int j=1;j<=cnt[i];j++)
		{
			int l=0,r=ls,mid,o=0;
			while(l<=r)
			{
				mid=(l+r)>>1;
				if(ask(mid,i,j))o=mid,l=mid+1;
				else r=mid-1;
			}
			ans.insert(ans.begin()+o,char(i));
			ls=o;
		}
	}
	assert(ans.size()==n);
	cout<<"! ";
	for(auto i:ans)cout<<i;
	cout<<endl;
}

---

## 作者：drmr (赞：1)

**题意**：字符串 $S$ 是隐藏的，满足 $|S| \le L$。可以询问一个字符串 $T$，交互库会返回 $S$ 和 $T$ 的编辑距离。其中，编辑距离是在 $S$ 中加入、删除、更改字符使其变为 $T$ 的最少操作次数。你需要找到 $S$。$L = 128$，$|\Sigma| = 62$。

尝试得到每一个字符的出现次数。询问交互库一个长度为 $L$，只有字符 $c$ 组成的字符串，若返回的值为 $x$，则 $S$ 中 $c$ 出现了 $L - x$ 次。

当 $|\Sigma| = 2$ 时，容易得出一个平凡做法。假设 $\Sigma = \{\text{a}, \text{b}\}$。依次插入字符，现在需要判断第 $i$ 位的字符。假设其为 $\text{a}$，那么将 $\text{a}$ 加入已知字符串，再加入还没有加入的 $\text{b}$，此时该字符串一定为 $S$ 的子序列。观察发现，若一个字符串 $s$ 位 $t$ 的子序列，则等价于两者的编辑距离为 $|t| - |s|$。询问次数约为 $|S| - 1$。

当 $|\Sigma| = 62$ 时，考虑使用分治来解决问题。假设现在的字符集为 $R$，分裂为两个大小尽量接近的字符集 $P, Q$。设已知只包含 $P$ 或 $Q$ 中的字符，且为 $S$ 的子序列的最长串为 $A, B$，通过前一段的分法合并 $A, B$ 得到只包含 $R$ 且为 $S$ 的子序列的最长串。

因此总询问数的一个上界为 $L\log_2|\Sigma| = 768$ 次。

```cpp
#include <bits/stdc++.h>
using namespace std;

string sig = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
int cnt[90], len;

bool check(string s){
	cout << "? " << s << "\n"; cout.flush();
	int tmp; cin >> tmp;
	return tmp == len - s.size();
}

string solve(int l, int r){
	if(l == r){
		string s;
		for(int i = 1; i <= cnt[l]; i++)
			s.push_back(sig[l]);
		return s;
	}

	int mid = (l + r) >> 1;
	string s = solve(l, mid), t = solve(mid + 1, r), ans = "";
	int p = 0, q = 0;
	while(p != s.size() || q != t.size()){
		if(p == s.size()){ans.push_back(t[q++]); continue;}
		if(q == t.size()){ans.push_back(s[p++]); continue;}
		string mer = ans; mer.push_back(s[p]);
		for(int i = q; i < t.size(); i++) mer.push_back(t[i]);
		if(check(mer)) ans.push_back(s[p++]);
		else ans.push_back(t[q++]);
	}
	return ans;
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	for(int i = 0; i < sig.size(); i++){
		string s = "";
		for(int j = 1; j <= 128; j++)
			s.push_back(sig[i]);
		cout << "? " << s << "\n"; cout.flush();
		cin >> cnt[i]; cnt[i] = 128 - cnt[i], len += cnt[i];
	}

	string s = solve(0, sig.size() - 1);
	cout << "! " << s << "\n"; cout.flush();
	return 0;
}
```

---

## 作者：ganzichen (赞：0)

## 前言：
本人第一次写题解，可能表述会有点~~反人类~~奇怪。  
这是我切的第一道黑题，现在看来感觉这题在黑题里面还是算比较简单的，所以就写篇题解纪念一下吧。  
~~凭什么不给交互库！！！~~
## 题意：
有一个长度小于等于 128 的字符串S，每次给出一个字符串T，交互库会给出 S 和 T 的编辑距离，你有 $$Q = 850$$ 次询问机会，求出 S。

## 题解：
首先我们可以注意到一个显然的性质，对于任意一个 S，S 与 $$T = \texttt{AAA...A}$$ 的编辑距离为 $$siz_T - cnt_A$$,即可以通过一次询问得到 S 中字母 A 的数量，其他字符同理。

还有一个很显然的性质是对于 S 的子序列（不是子串！），S 和 S' 的编辑距离为 $$siz_S - siz_{S'}$$。

通过这两个性质我们可以手玩一下：  
$$S = \texttt{abbababbaab}$$  
首先可以得到 $$cnt_a = 5,cnt_b = 6$$，  
先插入全部的 a，得到 $$T = \texttt{aaaaa}$$，  
再考虑如何插入 b，根据第二个性质可以得到 T 中的 a 和 b 相对位置不能改变，否则会使编辑距离大于 $$siz_S - siz_{S'}$$，即 T 不为 S 的子序列，  
所以可以在每个位置尝试添加 b，若编辑距离大于 $$siz_S - siz_{S'}$$，则此位置的 b 满了，到下一个位置，否则继续添加 b。

容易证明，这么每个字母依次添加的方法是对的，那么计算询问次数：  
对于每个字母，在最坏情况下需要把原字符串过完，即每次都在最后添加，则会有 $$L \times 62\text{(字符个数)} = 7936$$ 次询问操作，~~显然是过不去的~~。

#### 于是！！
就有了伟大的分治。

可以发现，上述操作可以对 S 的任意两个不交子序列 T1，T2 操作。  
只需要保证相对位置正确，就可以把 T2 顺着插入 T1，使其成为一个新的子序列，具体操作如下：  
$$T1 = T1_1 T1_2 T1_3 ... T1_{d1}$$
$$T2 = T2_1 T2_2 T2_3 ... T2_{d2}$$
两个指针i，j，每次尝试将 $$T2_j$$ 插入到 $$T1_{i-1} - T1_i$$ 之间如果编辑距离大于 $$siz_S - siz_{S'}$$，则i增加一，否则插入后j增加一。

有了合并操作我们就可以分支啦$\sim$

初始有 62 个子序列：  
$$S_1 = \texttt{00\dots0}$$  
$$S_2 = \texttt{11\dots1}$$  
$$\cdots$$  
$$S_{62} = \texttt{zz\dots{z}}$$

显然这些子序列互相不交，可以合并。

### 询问次数：
显然，每次合并 T1 和 T2，询问次数为 $$siz_{T1} + siz_{T2}$$，则分治的每一层询问次数为 L，  
底层有 62 个子序列，则层数为 7，  
最开始查询每个字符出现次数，查询了 62 次，  
则总查询次数为 $$(7-1) \times L + 62 = 830 < 850$$ 可以通过。

## 代码：
```
#include<bits/stdc++.h>
using namespace std;
int cnt[128],L=128,len,op,le;
char p[200];
string s;
int ask(string s){
    cout<<"? "<<s<<endl;
    int x;cin>>x;
	return x;
}
//合并两个字符串
string merge(string A,string B){
    if(!A.size()||!B.size()){
        return A+B;
    }
    string nw;
    int i=0,j=0;
    while(i<A.size()||j<B.size()){
        if(i==A.size()){
            nw=nw+B[j++];
        }else if(j==B.size()){
            nw=nw+A[i++];
        }else{
            string tr=nw+A[i]+B.substr(j);
            if(ask(tr)==len-tr.size()){
                nw=nw+A[i++];
            }else{
                nw=nw+B[j++];
        	}
        }
    }
    return nw;
}
//分治求解
string sort(int l,int r){
	if(l==r){
		string ans;
		for(int i=1;i<=cnt[p[l]];i++){
			ans+=char(p[l]);
		}
		return ans;
	}
	string lt=sort(l,(l+r)>>1);
	string rt=sort((l+r)/2+1,r);
	return merge(lt,rt);
}
int main()
{
    for(int i='a';i<='z';i++){
    	p[++le]=char(i);
        cout<<"? ";
        for(int j=1;j<=128;j++){
            cout<<char(i);
        }cout<<endl;
        cin>>cnt[i];
        cnt[i]=L-cnt[i];
    }
    for(int i='A';i<='Z';i++){
    	p[++le]=char(i);
        cout<<"? ";
        for(int j=1;j<=128;j++){
            cout<<char(i);
        }cout<<endl;
        cin>>cnt[i];
        cnt[i]=L-cnt[i];
    }
    for(int i='0';i<='9';i++){
    	p[++le]=char(i);
        cout<<"? ";
        for(int j=1;j<=128;j++){
            cout<<char(i);
        }cout<<endl;
        cin>>cnt[i];
        cnt[i]=L-cnt[i];
    }
    for(int i=0;i<128;i++){
        len+=cnt[i];
        for(int j=1;j<=cnt[i];j++){
            s=s+char(i);
        }    
    }
    s=sort(1,le);
    cout<<"! "<<s;
    return 0;
}
```

---

## 作者：while_0 (赞：0)

~~这是我写过最短的黑题~~

## 题目描述

交互题，有一个未知串 $S$，可以询问串 $T$ 与 $S$ 的编辑距离，要求确定 $S$。

## 思路

编辑距离是一个性质不太好的字符串二元函数，不够简单。所以我们考虑将编辑距离化为更简洁有用的信息。

设 $cnt(S,c)$ 表示字符 $c$ 在字符串 $S$ 中的出现次数。

- 串 $S$ 中某个字符 $c$ 的出现次数：询问 $128$ 个 $c$，编辑距离为 $128-cnt(S,c)$。因为其他字符对应位置、超出串长的部分都要被替换或删除。
- 串 $T$ 是否为 $S$ 的子序列：若回答为 $|S|-|T|$，则是子序列（编辑距离即为添上不在对应子序列中字符）；反之则不是。

## 解法

首先求出所有字符在 $S$ 中出现次数，顺便求出串长。

考虑将字符一种一种加入答案串。当加入一种字符 $c$ 时，要插入 $cnt(S,c)$ 次。

假设插入前的 $S$ 长度为 $m$，要插入 $k$ 个 $c$。我们要做的就是求出序列 $\{p_1,p_2,...,p_k\}$，代表第 $i$ 个 $c$ 在之前的 $|S|$ 的第几位之后。我们可以使用二分求解 $b$ 序列，即询问当前 $S$ 的第 $i$ 位后面能否匹配 $j$ 个 $c$。这样可以求出右起第 $j$ 个 $c$ 处于原本 $S$ 中什么位置。这样就可以用 $O(\log n)$ 次询问得到一个字符的位置。细节见代码（很短）。

询问次数 $O(n\log n+|\Sigma|)$。

## 代码

```
#include<bits/stdc++.h>
using namespace std;
int cnt[128];
signed main()
{
	string s,u;
	for(int i='0';i<='9';i++)u+=char(i);
	for(int i='a';i<='z';i++)u+=char(i);
	for(int i='A';i<='Z';i++)u+=char(i);
	int n=0;
	for(int i=0;u[i];i++)
	{
		cout<<"? ";
		for(int ii=0;ii<128;ii++)cout<<u[i];
		cout<<endl;
		cin>>cnt[i];cnt[i]=128-cnt[i];
		n+=cnt[i];
	}
	for(int i=0;u[i];i++)
	{
		int r=s.length()+1;
		for(int j=1;j<=cnt[i];j++)
		{
			int l=0;
			while(l<r-1)
			{
				int mid=l+r>>1;
				cout<<"? ";
				for(int i=0;i<mid;i++)cout<<s[i];
				for(int ii=0;ii<j;ii++)cout<<u[i];
				cout<<endl;
				int x;cin>>x;
				if(x==n-(mid+j))l=mid;
				else r=mid;
			}
			s=s.substr(0,l)+u[i]+s.substr(l);
//			cout<<s<<endl;
		}
	}
	cout<<"! "<<s<<endl;
}
```

---

## 作者：Missa (赞：0)

本文为 atcoder 官方题解第二个做法的翻译。

与另一个做法一样，首先求出每种字符的出现次数，借其和算出 $|S|$。对每种字符 $c$，询问一个长度为 $L > |S|$ 的全 $c$ 串 $T$，则 $c$ 出现 $|T|-ans$ 次，其中 $ans$ 为编辑距离。

对于 $0 \leq l \leq r < |S|$，定义 $f(c, l, r)$ 为 $S[l \dots r]$ 中 $c$ 的个数。由于 $f(*, 0, |S|-1)$ 是容易求得的，我们进行分治。具体而言，若 $f(*, 0, l-1),  f(*,l, r), f(*, r+1, |S|-1)$ 均已知，我们找到区间中点 $m$，求出所有 $f(*, l, m), f(*, m+1, r)$ 并递归。

注意到对于形如 `aaaaabbbbb` 的串，其中共有 $t$ 个 `a`，且长度为 $|S|$，其与 $S$ 的编辑距离为 $|S| - f(a, 0, t-1) - f(b, t, |S|-1)$。

注意到 $f(a, 0, m) - f(a, 0, l-1) = f(a, l, m)$，只需求 $f(a, 0, m)$ 即可。

选择一个在 $[l, r]$ 中出现过的 $z$，对于其它所有在 $[l, r]$ 中出现过的字母 $c$，询问后容易得到 $f(c, 0, m) + f(z, m+1, |S|-1)$，进而得到 $f(c, l, m) + f(z, m+1, r)$。解关于 $f(z, m+1, r)$ 的一元一次方程 $\sum_{c \neq z} f(c, l, m) + f(z, l, m) = m-l+1$ 容易求出 $f(z, m+1, r)$，进而得到所有 $f(c, l, m)$，进而可以分治两边。

处理 $[l, r]$ 的复杂度为 $\min(r-l+1, 62)-1$，其中 $62$ 为字符集大小。精确的次数估计为 $62+61+2\cdot61+4\cdot31+8\cdot15+16\cdot7+32\cdot3+64\cdot1=761$。

另一个做法对字符集分治，这个做法对原串分治。后面的查询本质上都在查两个串的差异程度，即只用到了编辑距离中的修改操作。

[官方题解参考代码](https://atcoder.jp/contests/AGC044/submissions/13463830)

~~应该没人去写吧~~

fun fact：另一篇题解在 `cout << "! " << solve(1, n)` 上调了三小时，我 `priority_queue` 的小于号重载反调了一小时。

---

