# [GDCPC 2023] New but Nostalgic Problem

## 题目描述

给定 $n$ 个字符串 $w_1, w_2, \cdots, w_n$，请选出恰好 $k$ 个字符串，最小化字符串 $v$ 的字典序，并输出这个最优的字符串 $v$。其中 $v$ 满足以下条件：$v$ 是被选出的字符串中，某两个编号不同的字符串的最长公共前缀。而且，$v$ 是所有满足条件的字符串中，字典序最大的字符串。

更正式地，令 $\mathbb{S}$ 表示一个大小为 $k$ 的集合，集合中的元素均为从 $1$ 到 $n$ 的整数（含两端），且没有重复的元素。令 $\text{lcp}(w_i, w_j)$ 表示字符串 $w_i$ 和 $w_j$ 的最长公共前缀，您需要找到一个集合 $\mathbb{S}$ 以最小化下述字符串 $v$ 的字典序，并输出这个最优的字符串 $v$。

$$
v = \max\limits_{i \in \mathbb{S}, j \in \mathbb{S}, i \ne j} \text{lcp}(w_i, w_j)
$$

上式中的 $\max$ 通过字典序比较两个字符串。

请回忆：
- 称字符串 $p$ 是字符串 $s$ 的前缀，若可以在 $p$ 的末尾添加若干个字符（包括零个字符）将它变成 $s$。特别地，空字符串是任意字符串的前缀。
- 字符串 $s$ 和 $t$ 的最长公共前缀是一个最长的字符串 $p$，满足 $p$ 既是 $s$ 的前缀，又是 $t$ 的前缀。例如，``abcde`` 与``abcef`` 的最长公共前缀为 ``abc``，而 ``abcde`` 与 ``bcdef`` 的最长公共前缀为空字符串。
- 称字符串 $s$ 的字典序小于字符串 $t$（$s \ne t$），若
  - $s$ 是 $t$ 的前缀，或
  - $s_{|p| + 1} < t_{|p| + 1}$，其中 $p$ 为 $s$ 和 $t$ 的最长公共前缀，$|p|$ 为 $p$ 的长度，$s_i$ 表示字符串 $s$ 的第 $i$ 个字符，$t_i$ 表示字符串 $t$ 的第 $i$ 个字符。
- 特别地，空字符串是字典序最小的字符串。

## 样例 #1

### 输入

```
2
5 3
gdcpc
gdcpcpcp
suasua
suas
sususua
3 3
a
b
c```

### 输出

```
gdcpc
EMPTY```

# 题解

## 作者：OrangeRainee (赞：3)

### Solution

Trie。

假设此时已经确定答案前三位为 $\texttt{abc}$，接下来确定第四位。

要求字典序最小，从 $\texttt{a} \sim \texttt{z}$ 枚举第四位。

假设当前枚举到字母 $\texttt{e}$：

1. 对于 $\forall \texttt{abc}_{\texttt{a} \sim \texttt{e} } \dots$ 可选。因为他们 LCP 一定小于等于 $\texttt{abce} \dots$。
2. 对于 $\texttt{abc}_{\texttt{f} \sim \texttt{z}} \dots$，如果存在那么每个顶多选一个。

> 举个例子：
>
> 如果我们选择大于等于两个 $\texttt{abcf} \dots$，那么此时最大 LCP 成为 $\texttt{abcf} \dots$，不再是 $\texttt{abce} \dots$。

3. 剩下字符串可选情况维持原状。

以上，在合法情况下我们一定尽量多选。

如果此时我们已经可以选至少 $k$ 个字符串，那么第四位确定为 $\texttt{e}$，否则继续向下枚举。

在确定第四位时，我们需要确定答案是否就为四位。

考虑我们现在已经确定答案为 $\texttt{abce}$，那么：

1. 所有 $\texttt{abce}_{\texttt{a} \sim \texttt{z}} \dots$ 字符串，我们每种只能最多选择一个。否则答案大于当前确定的答案。
2. 剩下字符串可选情况维持原状。

如果此时我们能够选至少 $k$ 个字符串，那么答案确定只有四位，否则向下枚举第五位。

重复直到可判定答案合法。

以上策略保证答案最优，即 LCP 最小。若存在比当前枚举的答案更优的合法方案，一定会在之前被枚举到。

在 Trie 上进行这一过程，时间复杂度为 $O(c \times \sum len(s))$，其中 $c$ 为字符集大小。

#### Code

```cpp
#include <bits/stdc++.h>

using namespace std;

int t;

#define maxn 1000005

int ed[maxn], cnt[maxn];

int tr[maxn][27], tot = 1;

void add(char *s, int len) {
    int p = 1;
    ++cnt[p];
    for (int i = 1; i <= len; ++i) {
        int u = s[i] - 'a' + 1;
        if (!tr[p][u]) {
            tr[p][u] = ++tot;
            memset(tr[tot], 0, sizeof tr[tot]); // 插入时顺便清空 trie
        }
        p = tr[p][u];
        ++cnt[p]; // 记录经过当前位置的字符串个数
    }
    ++ed[p]; // 记录从当前位置结束的字符串个数
    return;
}

char s[maxn];

void sol() {
    // 多测记得清空
    tot = 1;
    for (int i = 1; i <= 26; ++i)
        tr[1][i] = 0; // 清空首层
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++i) {
        scanf("%s", s + 1);
        int len = strlen(s + 1);
        add(s, len); 
    }
    int p = 1;
    // 题解大部分写的是 dfs，这里用简单循环实现
    while (1) {
        int sum = ed[p];
        for (int i = 1; i <= 26; ++i)
            if (cnt[tr[p][i]])
                ++sum; // 下一位每个字符串最多选一个
        if (sum >= k) {
            // 判定答案合法
            for (int i = 1; i <= tot; ++i) {
                ed[i] = 0;
                cnt[i] = 0;
            }
            if (p == 1) // 在首层，即答案为空字符串
                printf("EMPTY");
            putchar('\n');
            // 已经找到最优合法答案，结束程序即可
            return;
        }
        for (int i = 1; i <= 26; ++i) {
            if (!cnt[tr[p][i]])
                continue;
            sum += cnt[tr[p][i]] - 1;
            // 之所以减一，因为上面已经每个算了一个
            if (sum >= k) {
                // 确定下一位字母
                k -= (sum - cnt[tr[p][i]]);
                // 把当前可选所有字符串数从 k 中减掉
                putchar((char)('a' + i - 1));
                // 已确定，直接输出即可
                p = tr[p][i];
                break; // 进入下一位的枚举
            }
        }
    }
    return;
}

int main() {
    scanf("%d", &t);
    while (t--) 
        sol();
    return 0;
}
```

---

## 作者：lfxxx (赞：2)

去年我写的什么逆天题解，现在看完全一团浆糊，重写下。

Trie 上从小到大枚举答案串，问题变成判定能否选出 $k$ 个字符串满足要求。

然后你发现只用判定能否选出 $k$ 个字符串使得它们最大的最长公共前缀小于等于答案串即可，因为假若小于答案串并合法，一定会在之前枚举到。

然后我们思考下怎么判定，假设当前答案串在 Trie 上对应节点为 $u$，那么 $u$ 到根的链上的所有节点代表的所有字符串都是可以选的，令这些节点集合为 $T$。

对于节点 $u$ 的儿子，不难发现每个儿子子树至多选择一个串。

对于 $T$ 中除了 $u$ 以外的节点，发现对于已经枚举过的儿子（即这个儿子节点代表的字符串字典序小于答案串）那么儿子子树随便选都没问题，对于还没有枚举的儿子，还是只能在子树中选择至多一个字符串。

然后考虑在 dfs 的过程中把满足要求，可以选进集合的字符串数量记下来，判断是否大于等于 $k$ 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e6+114;
struct Node{
	int son[26];
	int sz,cnt;
}tr[maxn];
int n;
int tot=1;
int rt;
queue<char> s;
void insert(int &u){
	if(u==0){
		u=++tot;
		tr[u].sz=tr[u].cnt=0;
		for(int i=0;i<26;i++) tr[u].son[i]=0;
	}	
	if(s.size()==0){
		tr[u].sz++;
		tr[u].cnt++;
		return ;	
	}
	tr[u].sz++;
	char ch=s.front();
	s.pop();
	insert(tr[u].son[ch-'a']);
}
int k;
string Out;
bool flag;
void dfs(int u,int lst){
	if(u==0) return ;
	int sum=0;
	for(int i=0;i<26;i++){
		sum+=min(1,tr[tr[u].son[i]].sz);
	}
	if(sum+lst+tr[u].cnt>=k){
		if(u==1){
			cout<<"EMPTY\n";
			flag=true;
			return ;
		}
		else{
			cout<<Out<<'\n';
			flag=true;
			return ;
		}
	}
	int pre=0;
	for(int i=0;i<26;i++){
		Out.push_back('a'+i);
		dfs(tr[u].son[i],sum+lst+pre+tr[u].cnt-1);	
		if(flag==true) return ;
		Out.pop_back();
		pre+=tr[tr[u].son[i]].sz;
		if(tr[tr[u].son[i]].sz>=1) pre--;
	}
}
void work(){
	while(Out.size()>0) Out.pop_back();
	rt=tot=0;
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		string str;
		cin>>str;
		for(char x:str) s.push(x);
		insert(rt);
	}
	flag=false;
	dfs(rt,0);
	return ;
}
int t;
int main(){
	cin>>t;
	while(t--) work();
}
```

---

## 作者：N0_1 (赞：1)

首先在 trie 树上统计以某个子串为前缀的大小，并标记词尾。

假设当前答案前三位为 ```abc```，接下来要确定第四位。为了让字典序尽可能小，需要从 ```a``` 到 ```z``` 枚举第四位。

假设已经枚举到了 ```d```，考虑答案为 ```abcd*``` 时，与答案 ```abc*``` 相比，供选择字符串数量的变化如下：

1. 所有的 ```abc[a-d]``` 都可以选择，因为他们的 lcp 一定小于等于  ```abcd*```。
1. 所有的 ```abc[e-z]*``` 的字符串，在原来答案为 ```abc``` 时均可选择，现在每个 ```abc[e-z]*``` **最多只能选择一个**，例如：选择了一个 ```abcea``` 和 ```abceb```，那答案至少就是 ```abce>abcd``` 了。
1. 其余字符串可选情况不变。

考虑以上情况在 trie 树上 dfs 即可。
代码参考了这位大佬[链接](https://www.luogu.com.cn/blog/520748/sdcpc2023-e-ti-xie)。
```cpp
#include<bits/stdc++.h>
#define RI register int

using namespace std;

const int N = 1e6 + 10;
int trie[N][26], ed[N], sum[N], tot = 0;
int n, k;
string ans = "";
bool ok = 0;

void Insert(string s) {
	int rt = 0;
	for (auto &ch: s) {
		if (!trie[rt][ch - 'a']) trie[rt][ch - 'a'] = ++ tot;
		rt = trie[rt][ch - 'a'];
		sum[rt] ++;
	}
	ed[rt] ++;
}

void dfs(int u, int last) {
	if (ok) return ;
	
	int s = 0;
	for (int v: trie[u]) s += min(1, v);
	
	if (s + last + ed[u] >= k) {
		cout << (u ? ans: "EMPTY") << "\n";
		ok = 1;
		return ;
	}
	
	int pre = 0;
	for (int i = 0; i < 26; i++) {
		if (!trie[u][i]) continue ;
		
		ans.push_back('a' + i);
		dfs(trie[u][i], last + s + pre + ed[u] - 1);
		ans.pop_back();
		pre = pre + sum[trie[u][i]] - 1;
		
	}
}

void init() {
	for (int i = 0; i <= tot; i++) {
		memset(trie[i], 0, sizeof trie[i]);
		ed[i] = sum[i] = 0;
	}
	tot = 0;
	ok = 0;
	ans = "";
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int t; cin >> t;
	while (t --) {
		cin >> n >> k;
		for (int i = 1; i <= n; i++) {
			string s; cin >> s;
			Insert(s);
		}
		dfs(0, 0);
		init();
	}

	return 0;
 }
 ```

---

## 作者：SICKO (赞：0)

trie 树好题

### 1. 分析题目

首先观察一下题目，题目给了我们 $n$ 个字符串，要我们选择 $k$ 个字符串，使得选出字符串的**两两最长公共前缀**字典序**最大**者尽可能**小**。我们需要输出这个最小值。

捕捉到关键词**最大值最小**，马上想到~二分答案~我们可以对所有字符串建一个 trie 树，然后我们在树上跳树的节点判断这个节点是否满足条件。

### 2. 思路

我们现在来思考一下，建成一个 trie 树后，满足条件的答案如何计算。

![](https://cdn.luogu.com.cn/upload/image_hosting/a7jw7lda.png)

我们假设我们现在遍历到了红色节点，首先我们发现所有该节点的所有大于**祖先**的值都可以选一个，也就是右边的内容；所有字典序小于等于自己的字符串可以全选，也就是左边的内容。所以我们可以先预处理出每个节点的度 $siz$，每个节点的经过该节点字符串数量 $cnt$，以及以该节点为结尾的字符串的数量 $ed$，当前节点可选数量就为：

$$rtnum_x + siz_x + ltnum_x + ed_x;$$

递归子节点时，初始左右值就变成了：

$$rtnum_{son} = siz_x + rtnum_x - 1$$

$$ltnum_{son} = ed[x] + ltnum_x$$

每递归一个子节点，这个子节点内所有点都变得可选，也就是：

$$ltnum_{son} += cnt_{son}$$

$$rtnum_{son} -= 1$$

按如上方法递归求解，找到的第一个可以满足 $k$ 的节点就是答案。时间复杂度的大小依赖 trie 树的大小，也就是 $O(26\sum|w_i|)$。

### 3. 代码

```c++
#include <bits/stdc++.h>
//#define int long long
using namespace std;
const int N = 1e6+6;
int n, k;
int trie[N][27], idx;
int cnt[N], siz[N], ed[N], fa[N];
char id[N];
bool find_res;
int final_res;
void insert(const string& x) {
    int p = 1;
    for(auto &s : x) {
        int j = s - 'a' + 1;
        if(!trie[p][j]) {
            trie[p][j] = ++idx;
            id[idx] = s;
            memset(trie[idx], 0, sizeof trie[idx]);
        }
        cnt[p] += 1; fa[trie[p][j]] = p; p = trie[p][j];
    }
    cnt[p] += 1; ed[p] += 1;
}
void dfs1(int x) {
    for(int i=0; i<27; i++) {
        if(trie[x][i] == 0) continue;
        dfs1(trie[x][i]);
        siz[x] += 1;
    }
}
void dfs2(int x, int lt_num, int rt_num) {
    if(find_res) return;
    int res = rt_num + siz[x] + lt_num + ed[x];
    if(res >= k) {
        final_res = x;
        find_res = true;
        return;
    }
    int the_num_of_lt = ed[x] + lt_num, the_num_of_rt = siz[x] + rt_num - 1;
    for(int i=1; i<=26; i++) {
        if(!trie[x][i]) continue;
        int rt = the_num_of_rt, lt = the_num_of_lt;
        dfs2(trie[x][i], lt, rt);
        the_num_of_rt -= 1;
        the_num_of_lt += cnt[trie[x][i]];
    }
}
void solve() {
    idx = 1;
    for(int i=0; i<=26; i++) trie[1][i] = 0;
    find_res = false;
    final_res = 0;
    cin>>n>>k;
    for(int i=1; i<=n; i++) {
        string x; cin>>x;
        insert(x);
    }
    dfs1(1);
    dfs2(1, 0, 0);
    if(final_res != 1) {
        string res;
        while(final_res!=1) {
            res.push_back(id[final_res]);
            final_res = fa[final_res];
        }
        for(int i=(int)res.size()-1; i>=0; i--) cout<<res[i];
        cout<<"\n";
    }
    else cout<<"EMPTY\n";
    for(int i=0; i<=idx; i++) siz[i] = cnt[i] = ed[i] = id[i] = 0;
}

signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int T = 1;
    cin >> T;
    for (int i = 1; i <= T; i++) solve();
    return 0;
}
```

---

## 作者：RDFZchenyy (赞：0)

| 时间限制 | 空间限制 | 链接 |
| :----------: | :----------: | :----------: |
| 2.00s | 1.00GB | [link](https://www.luogu.com.cn/problem/P9694) |

**【题意简述】**

给定一组字符串 $s_1,s_2,\cdots,s_n$，请从中选出 $k$ 个，即选一组 $\{a_1,a_2,\cdots,a_k\}$，使得  $\max\limits_{1\le i,j\le k,i\not = j}^{}\operatorname{lcp}(s_{a_i},s_{a_j})$ 最小。

其中 $\operatorname{lcp}(p,q)$ 是字符串 $p$ 和字符串 $q$ 的最长公共前缀，字符串的大小即为其字典序的大小。

数据范围：$2\le k\le n\le 10^6$ 且 $\sum |s_i|\le 10^6$。

**【解法分析】**

我们不妨来考虑这样的一个事情，对于一个给定的答案字符串，我们至多可以选出多少个字符串使他们做上述运算后得到的答案小于等于这个这个字符串。

对于这个问题，我们容易想到把字符串计入一个 Trie 来处理。对于与这个答案字符串对应的节点来说，我们可以发现，从这个节点及其祖先节点出发的，不继续前往给定字符串的下一个字符的所有子树中必定只能产生一个。小于等于这个字符串的所有串都可以选取。

故我们按照字典序从小到大枚举每一个节点，直到找到一个节点对应的字符串可让我们选取大于等于 $k$ 个字符串，这个字符串即为所求。

**【代码示例】**

```cpp
#include<bits/stdc++.h>
using namespace std;

#define MAXN 1000005

int T;
int n,k;
string s[MAXN];

struct Node{
    int p[26];

    int psz,tag;
    Node(){
        memset(p,0,sizeof(p));
        psz=tag=0;
    }
};
int nc=0,nrt;

Node t[MAXN];

int nnode(){
    nc++;
    return nc;
}

void insert(int rt,string s){
    int now=rt;
    for(int i=0;i<=s.size()-1;i++){
        if(!t[now].p[s[i]-'a']){
            t[now].p[s[i]-'a']=nnode();
            t[now].psz++;
        }
        now=t[now].p[s[i]-'a'];
    }
    if(!t[now].tag){
        t[now].psz++;
    }
    t[now].tag++;
    return;
}

// 所有字典序小于这个的
// 字典序大于这个的每个外节点多一个

stack<int> ans,tmp;
bool flag=false;
int all=0,sub=0;
void solve(int id){
    all=all+t[id].tag;
    sub=sub+t[id].psz-(t[id].tag!=0);
    if(all+sub>=k){
        flag=true;
    }
    for(int i=0;i<=25;i++){
        if(!t[id].p[i]){
            continue;
        }

        sub--;
        if(!flag){
            ans.push(i);
        }
        solve(t[id].p[i]);
        if(!flag){
            ans.pop();
        }
    }

    return;
}

void run(){
    all=sub=0;
    nrt=nnode();
    flag=false;
    while(!ans.empty()){
        ans.pop();
    }

    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>s[i];
        insert(nrt,s[i]);
    }
    solve(nrt);

    if(ans.empty()){
        cout<<"EMPTY"<<endl;
    }else{
        while(!ans.empty()){
            tmp.push(ans.top());
            ans.pop();
        }
        while(!tmp.empty()){
            cout<<(char)(tmp.top()+'a');
            tmp.pop();
        }
        cout<<endl;
    }

    return;
}

int main(){
    ios::sync_with_stdio(false);

    cin>>T;
    for(int i=1;i<=T;i++){
        run();
    }

    return 0;
}
```

---

