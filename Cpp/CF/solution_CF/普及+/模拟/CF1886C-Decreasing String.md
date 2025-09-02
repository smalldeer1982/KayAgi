# Decreasing String

## 题目描述

Recall that string $ a $ is lexicographically smaller than string $ b $ if $ a $ is a prefix of $ b $ (and $ a \ne b $ ), or there exists an index $ i $ ( $ 1 \le i \le \min(|a|, |b|) $ ) such that $ a_i < b_i $ , and for any index $ j $ ( $ 1 \le j < i $ ) $ a_j = b_j $ .

Consider a sequence of strings $ s_1, s_2, \dots, s_n $ , each consisting of lowercase Latin letters. String $ s_1 $ is given explicitly, and all other strings are generated according to the following rule: to obtain the string $ s_i $ , a character is removed from string $ s_{i-1} $ in such a way that string $ s_i $ is lexicographically minimal.

For example, if $ s_1 = \mathrm{dacb} $ , then string $ s_2 = \mathrm{acb} $ , string $ s_3 = \mathrm{ab} $ , string $ s_4 = \mathrm{a} $ .

After that, we obtain the string $ S = s_1 + s_2 + \dots + s_n $ ( $ S $ is the concatenation of all strings $ s_1, s_2, \dots, s_n $ ).

You need to output the character in position $ pos $ of the string $ S $ (i. e. the character $ S_{pos} $ ).

## 样例 #1

### 输入

```
3
cab
6
abcd
9
x
1```

### 输出

```
abx```

# 题解

## 作者：LittleDrinks (赞：11)

# [CF1886C Decreasing String](https://www.luogu.com.cn/problem/CF1886C)

## 如何从 $s_{i-1}$ 得到 $s_i$

记 $s[i]$ 表示字符串 $s$ 中的第 $i$ 个字符（下标从 1 开始），与题目中的 $s_i$ 区分。

我们先观察：当 $s[i]$ 被删去时，后方所有的字符都将向前移动一个位置，其字典序的变化情况如下：

- 当 $s[i]$ 不是字符串 $s$ 中最后一个字符时：
	- 如果 $s[i]>s[i+1]$，那么删去 $s[i]$，字符串 $s$ 的字典序**必然减小，并且 $i$ 越小，减小得越多**；
	- 如果 $s[i]=s[i+1]$，字典序的变化取决于后方的字符（**对于相等的情况，需要看后方的字符，所以在当前这个位置可以直接不用管**）；
	- 如果 $s[i]<s[i+1]$，那么在字符串 $s$ 的字典序**必然增大**；
- 当 $s[i]$ 是字符串 $s$ 中的最后一个字符时，删去它，字符串 $s$ 的字典序**必然减小，但应该是上一种情况中减少得多**。

比如对于 `daacb`，从左向右遍历：

- 由于 `'d'>'a'`，所以删去 `'d'` 必然会使字典序变小；
- 由于 `'a'='a'`、又因为第二个 `'a'<'c'`，所以删去第一个 `'a'`，得到的 `'dacb'` 字典序会变大；
- 由于 `'a'<'c'`，所以删去第二个 `'a'` 会使字典序变大。此外，删去第二个 `'a'` 和删去第一个 `'a'` 得到的结果一样；
- 删去末尾字符 `'b'` 会使字典序变小，但不如删去 `'d'` 来得小。

又因为想要得到字典序最小的 $s_i$，需要从 $s_{i-1}$ 中删去一个字符，使得字典序减小得最多。所以可以得到从 $s_{i-1}$ 构造 $s_i$ 的方法：**扫描 $s_{i-1}$，找到最小的 $k<s.length()$，满足 $s[k]>s[k+1]$，把 $s[k]$ 删去。如果没有，那么删去末尾字符。**



## 实现方式

注意每次删去后字符串都会变化，【每找到一个 $k$ 就从头扫描】的朴素实现时间复杂度是 $O(n^2)$。

假设此时扫描到 $s[i]$，所有可以删去的 $j\ (j<i)$，都满足：

- $s[j]$ 尚未被删去；
- $s[j]>s[i]$。

满足这种条件，我们可以用**单调栈**进行维护。

具体而言，设当前的字符串长度为 $n$，此时仍然需要向后延伸的位置为 $p$。从左向右枚举 $s[i]$：

- 如果栈中为空，或者 $s[i]$ 大于等于栈顶元素，那么直接入栈；
- 如果 $s[i]$ 比栈顶元素小，那么不断出栈，每出栈一次，相当于进行一次上文所说的【删除 $s[k]$ 的操作】，$p\leftarrow p-n,\ n\leftarrow n-1$。如果某次出栈后 $p<n$，那么就找到了题目中所求的 $pos$ 所在的字符串，输出答案即可。

不要忘记在枚举完后将栈中所有元素取出，即上文所说的【找不到满足条件的 $k$，删除末尾字符】。

为了方便最后一步取出，实现时可以用 `vector` 模拟 `stack`。

[AC 代码提交记录](https://www.luogu.com.cn/record/129302311)

```cpp
#include <bits/stdc++.h>

using namespace std;

int t;
long long p, n;
string s;

int main()
{
	cin >> t;
	while (t--) {
		cin >> s >> p;
		n = s.length();
		s = " " + s + " ";
		vector <char> stk;
		bool done = (p<=n);
		for (int i = 1; i <= s.length()+1; ++i) {
			while ( (!done) && (!stk.empty()) && (stk.back() > s[i]) ) {
				stk.pop_back();
				p -= (n--);
				done = (p<=n);
			}
			stk.push_back(s[i]);
		}
		cout << stk[p-1];
	}
	return 0;
}
```

---

## 作者：Wf_yjqd (赞：3)

一开始没想到栈，整了个并查集耗了不少时间，还罚了一发。

------------

显然可以根据 $t$ 推出询问的是删了几个字符后的第几个字符。

本人不会推式子，于是二分了一下。

考虑如何维护删掉字符。

发现暴力删除时，每次从前到后找到第一个大于下一个位置的字符，并把他删去。

转换为对于每个数，删去前面连续比他大的字符，用栈维护之前没被删去的字符即可。

复杂度 $\operatorname{O}(n\log n)$。

------------

语言描述不是很清楚，可以看代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll maxn=1e6+84;
ll T,p,n,k,l,r,mid,cnt,top,st[maxn];//栈
char s[maxn];
bitset<maxn> ab;//是否被删除
inline char Find(ll x){
    cnt=0;
    for(ll i=1;i<=n;i++)
        if(!ab[i]){
            cnt++;
            if(cnt==x)
                return s[i];
        }
    return 'C';
}
int main(){
    scanf("%lld",&T);
    while(T--){
        scanf("%s%lld",s+1,&p);
        n=strlen(s+1);
        l=0;
        r=n+1;
        // (n+n-k+1)*k/2<p<=(n+n-k)*(k+1)/2
        while(l<=r){
            mid=l+r>>1ll;
            if((n*2-mid+1)*mid/2<p){
                k=mid;
                l=mid+1;
            }
            else
                r=mid-1;
        }
        ab.reset();
        cnt=top=0;
        for(ll i=1;i<n;i++){
            if(cnt==k)
                break;
            st[++top]=i;
            while(top&&s[st[top]]>s[i+1]){
                ab[st[top]]=1;
                top--;
                cnt++;
                if(cnt==k)
                    break;
            }
        }
        putchar(Find(p-(n*2-k+1)*k/2));
    }
    return 0;
}
```


---

## 作者：TernaryTree (赞：2)

瞎补补最近的 CF，感觉这场的 C>D，怎么会是呢。

首先看到字典序最小直接贪，如果哪一位是最靠前的能让字典序变小的那么就删它。怎么让字典序变小呢，这个字符的后面第一个不与这个字符相同的字符如果比它小就行。暴力模拟这个过程，复杂度是 $\Theta(n^2)$ 的。

考虑优化找最靠前的这个字符的过程，注意到如果把相同且相邻的字符缩成一段，那么至多找 $\Sigma=26$ 次就能找到。怎么模拟删除呢，使用链表即可。

记得删除时要时刻维护相邻两块字符不相同，不然复杂度是假的。

总复杂度 $\Theta(n\Sigma)$。

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int maxn = 1e6 + 10;

struct node {
	char ch;
	int cnt;
	node() = default;
	node(char ch, int cnt): ch(ch), cnt(cnt) {}
};

int T, n, m, k;
char s[maxn];
node p[maxn];
int lst[maxn], nxt[maxn];

void del(int u) {
	if (lst[u] != -1) nxt[lst[u]] = nxt[u];
	if (nxt[u] != -1) lst[nxt[u]] = lst[u];
	lst[u] = nxt[u] = -1;
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> T;
	while (T--) {
		cin >> (s + 1), n = strlen(s + 1);
		cin >> k;
		if (k <= n) {
			cout << s[k];
			continue;
		}
		k -= n;
		m = 0;
		for (int i = 1; i <= n; i++) {
			if (s[i] != s[i - 1]) p[++m] = node(s[i], 1);
			else p[m].cnt++;
		}
		for (int i = 0; i < m; i++) nxt[i] = i + 1;
		for (int i = 1; i <= m; i++) lst[i] = i - 1;
		nxt[m] = lst[0] = -1;
		for (int i = n - 1; i; i--) {
			int u = nxt[0];
			while (u) {
				if (nxt[u] == -1 || p[nxt[u]].ch < p[u].ch) {
					p[u].cnt--;
					if (!p[u].cnt) {
						if (lst[u] != -1 && nxt[u] != -1 && p[lst[u]].ch == p[nxt[u]].ch) {
							p[lst[u]].cnt += p[nxt[u]].cnt;
							del(nxt[u]);
						}
						del(u);
					}
					break;
				}
				u = nxt[u];
			}
			if (k <= i) {
				u = nxt[0];
				while (u) {
					if (k <= p[u].cnt) {
						cout << p[u].ch;
						break;
					} else k -= p[u].cnt;
					u = nxt[u];
				}	
				break;
			} else {
				k -= i;
			}
		}
	}
	return 0;
}
```

---

## 作者：caoshuchen (赞：1)

# [Decreasing String](https://www.luogu.com.cn/blog/caoshuchen/decreasing-string-zhong-zhuai)

## **思路**

### 删除字符

首先我们需要贪心的思路来删除字符，怎么贪心呢？很简单，只需要删去最左端的一个字符 $s_i$，这个字符满足：$s_i>s_{i+1}$ 若没有此类字符，则删除末尾字符。

为什么这样可以呢，我们发现，删掉这样的字符，字符串前缀不变，但后面全部变小，则整体变小，若删除其前面某个字符，那么我们说这个前缀是以非降排列的，所以它的字典序会变大，若删除后面某个字符，那么我们发现，它一定没有删除 $s_i$ 好，因为 $s_{i+1}<s_i$。可以在纸上写几个例子方便理解。

如果找到了 $s_i=s_{i+1}$ 是否删除？不删，因为如果删的话有几种情况：

 - 后面所有字符都相同，则可以直接从后往前删，不用在中间删，不必
 - 后面有 $s_j>s_{j+1}$，
   - $s_{i \to j}$ 均相同，则可以直接删 $s_j$，不必
   - 不是都相同，很显然 $s_i < s_j$ 则删 $s_i$ 会让大字符前移，不可
 - 后面非降排列，删完了，大的字符依然会前移，不可
 
 所以不删。

### 查询 pos

既然可以这么删除，那怎么快速求 $S_{pos}$ 呢？我的方法是：预处理每一次删除的是哪一个字符，然后进行遍历，找到 $pos$ 是在哪一次删除前的字符串所包含的字符，最后输出即可。

### 预处理每一次删除的字符

我们可以使用单调栈，进行预处理，当当前栈顶字符大于准备加入栈的字符时，删除栈顶，并记录这一次删除的字符为栈顶元素。

最后会有一些元素残留于栈，则依次删除并记录即可。

## **细节**

注意！！$pos$ 要开 long long ！！

## **Code**

```c++
#include <bits/stdc++.h>
using namespace std;

int t;
int w[1000005];
bool f[1000005];
char ans[1000005], s[1000005];

int main() {
	cin >> t;
	int tt = t;
	while (t--) {
		memset(w, 0, sizeof(w));
		memset(f, 0, sizeof(f));
		long long pos;
		scanf("%s", s + 1);
		cin >> pos;
		int n = strlen(s + 1);
		stack<int> st;
		int cur = 0;
		for (int i = 1; i <= n; i++) {
			while (!st.empty() && s[st.top()] > s[i])
				w[++cur] = st.top(), st.pop();
			st.push(i);
		}
		while (!st.empty())
			w[++cur] = st.top(), st.pop();
		for (int i = 1; i <= n; i++) {
			if (pos > n - i + 1)
				pos -= n - i + 1, f[w[i]] = true;
			else {
				for (int j = 1; j <= n; j++) {
					if (!f[j]) {
						if (pos == 1) {
							ans[tt - t] = s[j];
							break;
						}
						else
							pos--;
					}
				}
				break;
			}
		}
	}
	for (int i = 1; i <= tt; i++)
		cout << ans[i];
	return 0;
}
```

---

## 作者：Demeanor_Roy (赞：1)

- [原题链接](https://www.luogu.com.cn/problem/CF1886C)

------------

看了一眼没有我的做法。来水篇题解。

考虑求出 $t_i$ 表示第 $i$ 个字符是什么时候被删的。显然求出 $t_i$ 后题目就变成了简单模拟。

思考如何求 $t_i$。我们不妨倒序考虑整个操作，即：有 $n$ 个字符，每次你可以选择一个未被选择的字符，每次你都需要保证所选字符顺次构成的字符串字典序最小。

显然最开始是把字符串里最小的字符选完，这样一来整个字符串会被划分为若干段。然后显然是倒着一段一段考虑按同样的方法考虑，可以递归解决。

由于每次我们要找到最小字符的下标集合，每一段最多考虑字符集次。故时间复杂度为 $O(n \log n + n \Sigma)$。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=1e6+10;
int T,n,tmp,t[N];
char s[N];
long long sum;
vector<int> pos[30];
inline void solve(int l,int r,int c,int &now)
{
	int x=lower_bound(pos[c].begin(),pos[c].end(),l)-pos[c].begin(),R=x;
	if(pos[c][x]>r) return solve(l,r,c+1,now);
	for(int i=x;i<(int)pos[c].size();i++) if(pos[c][i]>r){R=i-1;break;}
	for(int i=x;i<=R;i++) t[pos[c][i]]=now--; 
	if(pos[c][R]!=r) solve(pos[c][R]+1,r,c+1,now);
	for(int i=R-1;i>=x;i--) if(pos[c][i]<pos[c][i+1]-1) solve(pos[c][i]+1,pos[c][i+1]-1,c+1,now);
	if(pos[c][x]!=l) solve(l,pos[c][x]-1,c+1,now);
}
inline void solve()
{
	scanf("%s%lld",s+1,&sum);n=strlen(s+1);
	for(int i=0;i<=25;i++) pos[i].clear();
	for(int i=1;i<=n;i++) pos[s[i]-'a'].emplace_back(i);
	for(int i=0;i<=25;i++) pos[i].emplace_back(n+1);
	solve(1,n,0,tmp=n);
	int x=n;
	while(sum>x) sum-=x--;
	for(int i=1,y=0;i<=n;i++) 
		if(t[i]>n-x)
		{
			++y;
			if(y==sum){putchar(s[i]);break;}
		}
}
int main()
{
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```


---

## 作者：Jerrycyx (赞：0)

前置知识：链表

-----

首先，每次删除的一定是比后一个字符大且位置最靠前的字符，例如 `cadb` 下一次删除的是第一个 `c`。

证明：

+ 如果当前字符比后面字符大，删掉这个字符并让后面向前移动一位一定会使字典序变小（这个位置被更小的后一个字符替代）；
+ 如果有多个字符满足上述条件，那么删掉最前面的一个可以使字典序减小的位置最靠前（比如 `cadb` 删 `c` 是在第一个位置减小字典序，删 `d` 是在第三个位置减小字典序），而根据字典序的定义，小字符越靠前，字典序越小。

综上所述，每次删除第一个比后一个字符大的字符是最优的。

-----

有了这个结论，我们就可以求字符串中各个字符被删除的顺序了，但是直接求是 $O(N^2)$ 的，考虑如何优化。

观察下面的删字符过程：

```plaintext
abandon
a_andon
a_a_don
a_a_d_n

a_a_d__
a_a____
a______
```

可以发现，删字符的过程是从前往后删掉所有的逆序，字符串变成不下降以后再从后往前依次删除。

其实把 $s_{n+1}$ 看作 $0$ 的话，上面的两步可以合并成一步，都是在删逆序。

再来看一个例子：

```plaintext
acdcbb
ac_cbb
ac__bb
a___bb
a___b_
a_____
```

这个就稍微有所不同了，在第 $3$ 步和第 $4$ 步之间，很明显是往前删了的，不符合“从前往后删除逆序”的结论，所以不能通过单扫一下就找出删除顺序（我做的时候真想这么干）。

但是，有一个结论：当删除字符 $x$ 的时候，它的前面所有字符都一定小于等于 $x$（否则第一个逆序就不该是 $x$ 了），只有删除了 $x$ 以后，如果前面的字符与 $x$ 相等，接替了 $x$ 的位置与后一个字符形成逆序，才会造成“往前退了一位合并”的情况。

所以，我们**在每次删除成功后将位置向前移动一位**（只有这一位可能回退形成新的逆序），尝试删除，这样就可以解决删除顺序回退的问题了。

同时，最后从后往前删的问题也能通过这种方式解决，删完最后一个以后回退一位（该字符是末尾字符，所以此时再尝试删除一定成功）即可做到从后往前删除。

-----

然而，直接向前找没被删掉的字符，时间复杂度是 $O(N^2)$ 的，如何快速地找字符串的上一个字符？

回想一下，我们要实现**快速删除元素和找前驱后继**的操作，而这正是**链表**干的事情（终于有一道链表题了）。

（不过这个似乎用栈也可以维护，但是用链表要更加直观一些。）

通过上述过程，我们 $O(N)$ 求出来了字符串内字符被删除的顺序。

-----

接下来，直接 $O(N)$ 暴力找出 $pos$ 所在 $S$ 的哪一部分，即找出 $pos$ 所在字符串所删字符数量 $part$。（其实也可以用二分 $O(\log N)$ 求，不过没必要还容易错）

设 $pos$ 在这个部分中位置为 $pos'=pos-\frac{(2n-(part-1)) \times ((part-1)+1)}{2}$，在字符串内找还没被删掉的字符（被删除的时间晚于 $part$ 的）的第 $pos'$ 个即为所求。

-----

[AC 记录](https://codeforces.com/contest/1886/submission/292261777)

完整代码：

```cpp
#include<cstdio>
#include<cstring>
using namespace std;

const int N=1e6+5;
int n; long long pos;
char s[N];
int order[N],oidx;

struct BJ{
	int pre,nxt;
}ls[N];
inline void del(int x)
{
	ls[ls[x].pre].nxt=ls[x].nxt;
	ls[ls[x].nxt].pre=ls[x].pre;
	return;
}

int main()
{
	int T; scanf("%d",&T);
	while(T--)
	{
		scanf("%s%lld",s+1,&pos);
		n=strlen(s+1);
		
		for(int i=1;i<=n;i++)
			ls[i]={i-1,i+1};
		oidx=0;
		for(int i=1;i<=n;)
		{
			if(s[i]>s[ls[i].nxt])
			{
				order[i]=++oidx;
				del(i);
				i=ls[i].pre;
			}
			else i=ls[i].nxt;
		}
		
		int part=0; long long tot=0;
		for(int i=0;i<=n;i++)
		{
			tot+=n-i;
			if(tot>=pos)
			{
				part=i;
				break;
			}
		}
		
		int real_pos=pos-1ll*(n*2-(part-1))*((part-1)+1)/2;
		int sidx=0;
		char ans='-';
		for(int i=1;i<=n;i++)
			if(order[i]>part)
			{
				sidx++;
				if(sidx==real_pos)
				{
					ans=s[i];
					break;
				}
			}
		putchar(ans);
	}
	return 0;
}
```

---

## 作者：2huk (赞：0)

> - 给出字符串 $s_1$ 和 一个整数 $pos$。
> - 以下列规则得到字符串 $ S $：
>   - 从 $ s_{i - 1} $ 中删除一个字符，字典序最小的记为 $ s_i $。
>   - $S = s_1 + s_2 + \dots + s_n $。
> - 输出字符串 $ S $ 第 $pos$ 个位置上的字符（即 $ S_{pos} $）。

每个字符串都的长度比上一个字符串少 $1$。我们可以轻易地求出 $S_{pos}$ 是哪个小字符串的哪个位置。

不难发现每次删除的是满足 $s[i] > s[i + 1]$ 的最靠前的位置 $i$。若不存在这样的位置则删除最后一个。

删除操作可以用双向链表。具体地，若 $i$ 没被删除，令 $l_i$ 表示 $i$ 左边第一个没有被删除的位置，$r_i$ 表示右边。维护 $f_i = s_i - s_{r_i}$，若 $i$ 被删除则 $f_i = -\infty$，若 $i$ 是没被删除的位置中的最后一个则 $f_i = +\infty$。那么删除的第一个满足 $f_i > 0$ 的位置。

用线段树维护 $f$。那么找第一个满足 $f_i > 0$ 的位置可以维护区间最大值，然后二分递归找。

```cpp
int n, k;
char s[N];
int l[N], r[N];

void del(int x) {
	r[l[x]] = r[x];
	l[r[x]] = l[x];
}

struct Tree {
	struct Node {
		int l, r, v;
	}tr[N << 2];
	
	void build(int u, int l, int r) {
		tr[u].l = l, tr[u].r = r, tr[u].v = 0;
		if (l != r) {
			int mid = l + r >> 1;
			build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
		}
	}
	
	void modify(int u, int x, int d) {
		if (tr[u].l == tr[u].r) tr[u].v = d;
		else {
			int mid = tr[u].l + tr[u].r >> 1;
			modify(x <= mid ? (u << 1) : (u << 1 | 1), x, d);
			tr[u].v = max(tr[u << 1].v, tr[u << 1 | 1].v);
		}
	}
	
	void modify(int x, int d) {
		modify(1, x, d);
	}
	
	int query(int u) {
		if (tr[u].l == tr[u].r) return tr[u].l;
		if (tr[u << 1].v > 0) return query(u << 1);
		return query(u << 1 | 1);
	}
	
	int query() {
		return query(1);
	}
}T;

bitset<N> st;

char solve() {
	scanf("%s%lld", s + 1, &k);
	n = strlen(s + 1);
	
	if (k <= n) return s[k];
	
	for (int i = 1; i <= n; ++ i ) {
		l[i] = i - 1, r[i] = i + 1;
	}
	
	T.build(1, 1, n);
	for (int i = 1; i < n; ++ i ) {
		T.modify(i, s[i] - s[i + 1]);
	}
	T.modify(n, INF);
	
	int a, b, sum = 0;
	for (int i = 1; i <= n; ++ i )
		if (n - i + 1 + sum >= k) {
			a = i;
			b = k - sum;
			break;
		}
		else sum += n - i + 1;
	
	st.reset();
	
	int end = n;
	for (int i = 2; i <= a; ++ i ) {
		int pos = T.query();
		del(pos);
		T.modify(pos, -INF);
		if (l[pos]) T.modify(l[pos], r[pos] == n + 1 ? INF : s[l[pos]] - s[r[pos]]);
		if (pos == end) T.modify(end = l[pos], INF);
		st[pos] = true;
	}
	
	int cnt = 0;
	for (int i = 1; i <= n; ++ i ) {
		cnt += !st[i];
		if (cnt == b) return s[i];
	}
}
```

---

## 作者：huanglihuan (赞：0)

## 思路:
你有一个字符串 $s$ 你每一个从中删掉一个字符，记录下删掉一个后字典序最小的字符串，然后将这些记录的字符串拼接在原字符串的后面，并且给出当前 $pos$ 位置上的字母是什么。

本题我们可以创建一个字符函数判断位置，这样即可通过。
## 代码实现（详见注释）：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int arr [105];

char cz (vector <bool> &del,string &s,int pos)
{
	//一个个位置找过去，如果当前这个位置被删除那么跳过 
	for (int i = 0;i < s.size ();i ++)
	{
		if (del [i]) continue;
		pos --;
		if (!pos) return s [i];
	}
}
void sovle ()
{
	string s;
	cin >> s;
	int pos;
	cin >> pos; 
	int n = s.size ();
	//没被取走的数 
	vector <int> stk;
	vector <bool> del (n);
	if (pos <= n)
	{
	    cout << cz (del,s,pos);
	    return ;
	}
	int rn = n; //统计string中的数量 
	for (int i = 0;i < n;i ++)
	{ //找出前一位大于后一位的情况 
		//没被取走的数的数组不为空，需要判断 
		while (!stk.empty () && s [stk.back ()] > s [i])
		{
			pos -= rn;
			del [stk.back ()] = 1;
			stk.pop_back ();
			rn --;
			if (pos <= rn)
			{
				cout << cz (del,s,pos);
				return ;
			}
		}
		//当前这个位置的数没有被取走
		stk.push_back (i); 
	}
	//从末尾开始剔除 
	while (pos > rn)
	{
		pos -= rn;
		del [stk.back ()] = 1;
		stk.pop_back ();
		rn --;
		if (pos <= rn)
			{
				cout << cz (del,s,pos);
				return ;
			}
	 } 
}

signed main ()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int T;
	cin >> T;
	while (T --)
	{
		sovle ();
	}
	return 0;
}

```


---

## 作者：cyrxdzj (赞：0)

### 一、思路

首先，我们想想，应该怎么删除字符，才能让删除后的字典序最小。

可以发现，应该删除最早出现的 $s_i$，这个 $s_i$ 满足 $s_i>s_{i+1}$。特别地，如果不存在满足要求的，那么就删最后一个字符。

反证法。如果删除的 $s_i$ 符合条件 $s_i\le s_{i+1}$，那么原来的 $s_{i+1}$ 成为 $s_i$ 后，字典序一定不会减小，甚至很可能增大。

而如果删除的 $s_i$ 满足 $s_i>s_{i+1}$ 但却不是最早出现的，字典序确实会减小，但明显不是最优的。

但 $n$ 高达 $10^6$，直接一个一个删，时间复杂度肯定会爆炸。因此，我们可以借助模拟链表。维护每个字符的前驱和后继，将 $s_{n+1}$ 特别定义为 `\0`。

然后，每次判断一下 $pos$ 有没有小于等于当前长度。如果没有，那么按照上面提到的规则删去字符。如果有，那就输出答案即可。

### 二、代码

```cpp
// Author: cyrxdzj
// Problem: Decreasing String
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1886C
// Memory Limit: 250 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=1e6;
int t;
int n;
char s[MAXN+5];
int nxt[MAXN+5],lst[MAXN+5];
long long pos;
int nowlen;
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        scanf("%s",s+1);
        n=strlen(s+1);
        s[0]=s[n+1]=0;
        for(int i=0;i<=n;i++)//初始化链表
        {
            nxt[i]=i+1;
        }
        for(int i=1;i<=n+1;i++)
        {
            lst[i]=i-1;
        }
        nowlen=n;
        scanf("%lld",&pos);
        int now=1;//当前所在的节点。
        while(true)
        {
            if(pos<=nowlen)
            {
                int p=0;
                while(pos--)
                {
                    p=nxt[p];
                }
                printf("%c",s[p]);
                break;
            }
            while(s[now]>=s[lst[now]])
            {
                now=nxt[now];
            }
            int the_last=lst[lst[now]];//真正要删去的其实是 lst[now] 号节点
            nxt[the_last]=now;
            lst[now]=the_last;
            pos-=nowlen;
            nowlen--;//长度减小
        }
    }
    printf("\n");
    return 0;
}
```

---

## 作者：_Only_this (赞：0)

### CF1886C Decreasing String 题解

------------

这道 C 其实挺一眼的，可惜当时没写完。

容易发现的规律是，$s_i$ 比 $s_{i-1}$ 少的是第一个字典序逆序的字母的上一个字母。

这个东西可以用单调栈处理。

然后考虑用二分来求所求的 $pos$ 是在 $s_?$ 中，然后单调栈模拟出 $s_?$，输出对应的 ${s_?}_{pos}$ 即可。

贴个代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll maxn = 1e6+5;
ll T,k,Tp;
string s;
ll st[maxn];
inline void Solve(){
	cin>>s;
	scanf("%lld",&k);
	Tp=0;
	ll l=0,r=s.size(),mid,re;
	
	while(l<=r){
		mid=l+r>>1;
		if((s.size()-mid+1+s.size())*mid/2<k){
			l=mid+1,re=mid;
		}
		else{
			r=mid-1;
		}
	}
	
	k-=((s.size()-re+1+s.size())*re/2);
	bool flag=0;
	int loc=-1;
	
	for(ll i=0;re && i<s.size();i++){
		flag=1;
		while(re && Tp && st[Tp]>s[i]-'a'){
			Tp--,re--;
		}
		st[++Tp]=s[i]-'a';
		loc=i;
	}
	
	for(int i=loc+1;i<s.size();i++){
		st[++Tp]=s[i]-'a';
	}
	
	Tp-=re;
	
	if(!flag){
		for(int i=0;i<s.size();i++){
			st[++Tp]=s[i]-'a';
		}
	}
	
	printf("%c",char(st[k]+'a'));
	
	return ;
}
int main(){
	scanf("%lld",&T);
	
	while(T--){
		Solve();
	}
	
	return 0;
}
```

完结散花。

---

