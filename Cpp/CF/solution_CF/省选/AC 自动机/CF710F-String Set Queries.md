# String Set Queries

## 题目描述

You should process $ m $ queries over a set $ D $ of strings. Each query is one of three kinds:

1. Add a string $ s $ to the set $ D $ . It is guaranteed that the string $ s $ was not added before.
2. Delete a string $ s $ from the set $ D $ . It is guaranteed that the string $ s $ is in the set $ D $ .
3. For the given string $ s $ find the number of occurrences of the strings from the set $ D $ . If some string $ p $ from $ D $ has several occurrences in $ s $ you should count all of them.

Note that you should solve the problem in online mode. It means that you can't read the whole input at once. You can read each query only after writing the answer for the last query of the third type. Use functions fflush in C++ and BufferedWriter.flush in Java languages after each writing in your program.

## 样例 #1

### 输入

```
5
1 abc
3 abcabc
2 abc
1 aba
3 abababc
```

### 输出

```
2
2
```

## 样例 #2

### 输入

```
10
1 abc
1 bcd
1 abcd
3 abcd
2 abcd
3 abcd
2 bcd
3 abcd
2 abc
3 abcd
```

### 输出

```
3
2
1
0
```

# 题解

## 作者：唐一文 (赞：58)

[题目传送门](https://www.luogu.com.cn/problem/CF710F)

下文令 $\text{len}=\sum|s|$。

首先在查询时一个很暴力的思路就是枚举模板串的所有子串，并统计在集合中的出现次数，用哈希优化。复杂度 $O(\text{len}^2)$。

而优化这个暴力的方法很简单，只枚举集合中的字符串的长度作为子串的长度即可。复杂度 $O(\text{len}\sqrt{\text{len}})$。

因为在最坏情况下，集合中的字符串长度各不相同。当字符串最多时，长度一定是 $1,2,3,...$ 一直到某个长度 $t$。而 $1+2+\cdots+t\leq \text{len}$，所以 $t\leq \sqrt{2\text{len}}$，最多只会有 $\sqrt{2\text{len}}$ 个不同的长度。所以复杂度为 $O(\text{len}\sqrt{\text{len}})$。

注意此题卡自然溢出，但是没卡非自然溢出的单哈希（

[Code](https://www.luogu.com.cn/paste/138aah6y)

---

## 作者：super蒟蒻 (赞：29)

解法：二进制分组 + AC自动机

啥是二进制分组？

就是把所有的操作按二进制分组，每一组里面就开个数据结构维护。

怎么分组呢？

因为是在线算法，所以这个东西有点像一个叫2048的游戏。

假设之前已经分好两组，每组的大小为 4，2（大小就是里面包含了多少个操作）。

加一个操作，那么就有三组 4，2，1；如果再加一个操作，就是 4，2，1，1。

此时有两个 1，就要把那两组暴力重构，合并成一组，得到 4，2，2；再合并 ...... 最终剩余一组，大小为 8 。

可以得到，如果有 n 个操作，那么至多会分为 $\log n$ 组，因为它分得的组数恰好就是 n 在二进制的表示下 1 的个数。（例如上面的 7 个操作被分成了 3 组）

那么暴力重构的时间复杂度呢？

考虑**每个点**会被重构多少次，如果把合并的过程画出来的话（如下图），你会发现这很像是一棵线段树，那么每个点至多被重构 $\log n$ 次。

![](https://cdn.luogu.com.cn/upload/image_hosting/l242p5zc.png)

最后乘上用数据结构维护对应的复杂度就是重构的复杂度了。

回到这题，首先得会 `AC自动机` 并 A 了这道模板题：[【模板】AC自动机（二次加强版）](https://www.luogu.com.cn/problem/P5357)

然后你会发现这题反而简单点的，模板题是求每个模式串的贡献，这题只需求所有模式串的总贡献。

模板题并没有每次暴力跳 $fail$ 边而是打了个标记，那我们也无需暴力求，像弄个前缀和一样在建树时沿着 $fail$ 边累加就行。

对于插入操作，对它进行二进制分组，**每个组建一个AC自动机**，到时候查询就是把 $\log n$ 个AC自动机 $search$ 一遍就好了。

最后就是删除操作，可以发现贡献**具有可减性**。

什么意思？

就是我们可以求出所有串的贡献，用它减去已删除串的贡献，得到的就是答案。

这样一来只要对插入，删除的字符串**各自**进行二进制分组，然后相减即可。

AC自动机的建树是 $O(n)$ 的，所以时间复杂度是 $O(len \log n)$ ， $len$ 表示输入的总串长。

第一次写写丑了，常数有点大。

如果用了 $printf$ 的话在后面记得加上这句话：`fflush(stdout);` ~~我也不知道为什么~~

$code:$

```cpp
// 二进制分组 + AC自动机
#include <cstdio>
#include <string>
#include <cstring>
#include <queue>
using namespace std;
const int maxn = 300005;
struct Group {
    string data[maxn];
    int tot,ch[maxn][26],cnt[maxn],n;
    void insert(int r,char *s) {
        int d=s[1]-'a',len=strlen(s+1),_r=r;
        for(int i=1;i<=len;d=s[++i]-'a') {
            if(ch[r][d]==_r) {
                ch[r][d]=++tot;
                for(int j=0;j<26;j++) ch[tot][j]=_r;
            }
            r=ch[r][d];
        } ++cnt[r];
    }
    int fail[maxn];
    void build(int r) {
        fail[r]=r;
        queue<int>q;
        for(int i=0;i<26;i++)
            if(ch[r][i]>r) q.push(ch[r][i]),fail[ch[r][i]]=r;
        while(!q.empty()) {
            int u=q.front(); q.pop();
            for(int i=0;i<26;i++) {
                int v=ch[u][i];
                if(v==r) ch[u][i]=ch[fail[u]][i];
                else {
                    fail[v]=ch[fail[u]][i];
                    cnt[v]+=cnt[ch[fail[u]][i]];
                    q.push(v);
                }
            }
        }
    }
    int search(int r,char *s) {
        int d=s[1]-'a',len=strlen(s+1),res=0;
        for(int i=1;i<=len;d=s[++i]-'a')
            r=ch[r][d],res+=cnt[r];
        return res;
    }
    int stk[maxn],fr[maxn],size[maxn],N;
    void merge() {
        --N,size[N]<<=1;
        for(int i=stk[N];i<=tot;i++) {
            cnt[i]=fail[i]=0;
            for(int j=0;j<26;j++) ch[i][j]=0;
        }
        tot=stk[N];
        for(int i=0;i<26;i++) ch[tot][i]=tot;
        for(int L=fr[N];L<=n;L++) insert(stk[N],&data[L][0]);
        build(stk[N]);
    }
    void Insert(char *s) {
        stk[++N]=++tot;
        for(int i=0;i<26;i++) ch[tot][i]=tot;
        size[N]=1;
        insert(tot,s),build(stk[N]);
        int len=strlen(s+1);
        data[fr[N]=++n]=" ";
        for(int i=1;i<=len;i++) data[n]+=s[i];
        while(size[N]==size[N-1]) merge();
    }
    int Count(char *s) {
        int ans=0;
        for(int i=1;i<=N;i++)
            ans+=search(stk[i],s);
        return ans;
    }
}Add,Sub;
char tmp[maxn];
int main() {
    int T;
    scanf("%d",&T);
    for(int i=1;i<=T;i++) {
        int opt;
        scanf("%d%s",&opt,tmp+1);
        if(opt==1) Add.Insert(tmp);
        else if(opt==2) Sub.Insert(tmp);
        else printf("%d\n",Add.Count(tmp)-Sub.Count(tmp));
        fflush(stdout);
    }
    return 0;
}
```

---

## 作者：SDqwq (赞：17)

没看懂其他题解为什么要建两个 $\texttt{ACAM}$ /yun

## 思路

如果先是一串操作，后是一串询问，就是 $\texttt{ACAM}$ 的模板题。

可以建出一个 $\texttt{ACAM}$，把所有加和删的字符串插进去。加串权值为 $1$，删串权值为 $-1$。查询的时候直接在 $\texttt{ACAM}$ 上走一遍这个串就可以统计出答案。

现在强制在线了，我们需要重新考虑。

每次插入一个串就必须要重构 $\texttt{fail}$ 树，这样肯定会超时。

很容易想到根号分治，每个 $\texttt{ACAM}$ 最多保存 $\sqrt{m}$ 个串的信息，最多会建出 $\sqrt{m}$ 个 $\texttt{ACAM}$。每次查询到每个 $\texttt{ACAM}$ 中查询并求和即可。这种做法需要卡常。

进一步地，我们考虑二进制分组。比如当前插入了 $21$ 个串，$21=(10101)_2$，所以当前有 $3$ 个 $\texttt{ACAM}$，分别存了 $1$ 个、$4$ 个、$16$ 个串。

在代码中体现为：每新插入一个串，先建出一个只存了当前串的新 $\texttt{ACAM}$，如果存在另一个与当前 $\texttt{ACAM}$ 大小相同的 $\texttt{ACAM}$ 就不断合并。

每次查询在每个 $\texttt{ACAM}$ 查之后求和即可。

因为最多有 $\log m$ 个 $\texttt{ACAM}$，所以查询复杂度是 $\mathcal{O}(n\log m)$。

再来看插入，每个串一定只会经历 $\log m$ 次合并，因为每次合并大小一定会 $\times2$。所以每个串最多被重构了 $\log m$ 次 $\texttt{fail}$ 指针。所以插入复杂度是 $\mathcal{O}(n\log m)$。

总复杂度 $\mathcal{O}(n\log m)$，有个 $26$ 的常数。

## 代码

```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
const int N = 2e6 + 5, S = 26;

int n, type, lstans;
char s[N];

int idx, tot, rt[N], siz[N], ch[N][S], go[N][S], fa[N], ed[N], sum[N];
void ins(char *s, int val, int st) {
	int u = st, len = strlen(s + 1);
	for (int i = 1; i <= len; i++) {
		int c = s[i] - 'a';
		if (!ch[u][c]) ch[u][c] = ++idx;
		u = ch[u][c];
	}
	ed[u] += val;
}
void build(int st) {
	queue<int> q;
	fa[st] = st;
	for (int i = 0; i < S; i++) {
		if (ch[st][i]) {
			go[st][i] = ch[st][i];
			fa[go[st][i]] = st;
			q.push(go[st][i]);
		}
		else go[st][i] = st;
	}
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		sum[u] = sum[fa[u]] + ed[u];
		for (int i = 0; i < S; i++) {
			if (ch[u][i]) {
				go[u][i] = ch[u][i];
				fa[go[u][i]] = go[fa[u]][i];
				q.push(go[u][i]);
			}
			else go[u][i] = go[fa[u]][i];
		}
	}
}
int merge(int p, int q) {
	if (!p || !q) return p ^ q;
	ed[p] += ed[q];
	for (int i = 0; i < S; i++) ch[p][i] = merge(ch[p][i], ch[q][i]);
	return p;
}
void upd(char *s, int val) {
	rt[++tot] = ++idx;
	siz[tot] = 1;
	ins(s, val, rt[tot]);
	while (siz[tot] == siz[tot - 1]) {
		tot--;
		siz[tot] += siz[tot + 1];
		rt[tot] = merge(rt[tot], rt[tot + 1]);
	}
	build(rt[tot]);
}
int query(char *s, int st) {
	int u = st, len = strlen(s + 1), res = 0;
	for (int i = 1; i <= len; i++) {
		int c = s[i] - 'a';
		u = go[u][c];
		res += sum[u];
	}
	return res;
}

int main() {
	scanf("%d", &n);
	while (n--) {
		int op;
		scanf("%d %s", &op, s + 1);
		if (op == 1) upd(s, 1);
		if (op == 2) upd(s, -1);
		if (op == 3) {
			int res = 0;
			for (int i = 1; i <= tot; i++) res += query(s, rt[i]);
			cout << res << endl;
			lstans = res;
		}
	}
	return 0;
}
```

---

## 作者：FelFa_1414666 (赞：9)

本蒟蒻来介绍一下三种方法吧

[codeforces 传送门](https://codeforces.com/contest/710/problem/F) & [洛谷传送门](https://www.luogu.com.cn/problem/CF710F)

---

## Solution 1（暴力&哈希）

第一种方法比较暴力，它的关键点在于：

> 所有字符串的总长不超过 $m=3\times10^5$，不难想到最多有不超过        $2\sqrt m$ 种不同的长度。大概是不超过 800 的。所以遍历子串时只需要遍历 $\operatorname O(\sqrt m)$ 种长度的子串就行了。

根据这一结论，我们可以暴力地维护 $\operatorname O(\sqrt m)$ 个 set，里面存所有对应长度字符串的哈希值。

- 插入&删除：对该长度的 set 进行相应操作。$\operatorname O(\log m)$.
- 询问：暴力的遍历文本串 $s$ 所有出现过的长度的子串，用滚动哈希每次去对应 set 里查找哈希值。$\operatorname O(\sqrt m \log m)$.

这样一来就能暴力的解决。注意一下哈希的细节，最好开双哈希避免冲突，~~因为这题数据很强（真实体会）~~。

- 时间复杂度：$\operatorname O(m\sqrt m \log m)$

- 空间复杂度：$\operatorname O(m)$

### Code

```cpp
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define pii pair<int,int>
#define mp make_pair
#define F first
#define S second
using namespace std;
const ll p1=37,M1=998244353,p2=97,M2=1610612741;//双哈希常数&模数
int q,id[300005],sz[805],num;
ll pw1[300005],pw2[300005];
set<ll> se[805];//存不同长度哈希值的set
int main()
{
	ios::sync_with_stdio(false),cin.tie(nullptr);
	cin>>q;
	memset(id,-1,sizeof(id));
	pw1[0]=pw2[0]=1ll;
	for(int i=1;i<=300000;i++)//预处理哈希常数的幂
	{
		pw1[i]=pw1[i-1]*p1%M1;
		pw2[i]=pw2[i-1]*p2%M2;
	}
	while(q--)
	{
		int tp;string s;
		cin>>tp>>s;
		int len=s.size();
		if (tp==1)
		{
			ll H1=0ll,H2=0ll;
			for(int i=0;i<len;i++)//求双哈希值
			{
				H1=(H1*p1+(ll)(s[i]-'a'))%M1;
				H2=(H2*p2+(ll)(s[i]-'a'))%M2;
			}
			if (id[len]==-1)
			{
				sz[num]=len;
				id[len]=num++;
			}
			se[id[len]].insert(H1<<31|H2);//插入
		}
		else if (tp==2)
		{
			ll H1=0ll,H2=0ll;
			for(int i=0;i<len;i++)
			{
				H1=(H1*p1+(ll)(s[i]-'a'))%M1;
				H2=(H2*p2+(ll)(s[i]-'a'))%M2;
			}
			se[id[len]].erase(H1<<31|H2);//删除
		}
		else
		{
			int n=s.size(),res=0;
			for(int i=0;i<num;i++)//枚举长度
			{
				int len=sz[i];
				if (len>n)
					continue;
				ll H1=0ll,H2=0ll;
				for(int j=0;j<len;j++)
				{
					H1=(H1*p1+(ll)(s[j]-'a'))%M1;
					H2=(H2*p2+(ll)(s[j]-'a'))%M2;
				}
				res+=se[i].count(H1<<31|H2);
				for(int j=len;j<n;j++)//滚动哈希遍历
				{
					H1=(H1*p1+(ll)(s[j]-'a')+M1-pw1[len]*(ll)(s[j-len]-'a')%M1)%M1;
					H2=(H2*p2+(ll)(s[j]-'a')+M2-pw2[len]*(ll)(s[j-len]-'a')%M2)%M2;
					res+=se[i].count(H1<<31|H2);
				}
			}
			cout<<res<<endl;cout.flush();
		}
	}
	return 0;
}
```

---

## Solution 2 （暴力&trie 树&KMP）

这个方法不是我想的，是另一位巨佬写出来的。当时看的我大为震撼。

他的暴力思路是：将较小的模式串都插入到 **trie 树**中，较大的模式串单独扔在一遍用 **KMP** 匹配。

每次查询时，对文本串的所有后缀扔到 **trie** 里查询子串匹配个数，求总和。再把文本串与所有较大模式串单独 **KMP**。

~~看到这个方法能过的时候，我甚至开始思考 AC 自动机解法有什么存在的必要。~~

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 300010;

struct Trie{//trie树的构体
public:
	static const int maxn = 300010, maxc = 26;
    int child[maxn][maxc], value[maxn];
	int cnttrie, root;
	
    int newnode(){
        cnttrie++; value[cnttrie] = 0;
        memset(child[cnttrie], -1, sizeof(child[cnttrie]));
        return cnttrie;
    }
    
public:
	void init(){
        cnttrie = root = 0; value[root] = 0;
        memset(child[root], -1, sizeof(child[root]));
    }
    void insert(char *s,int val){
        int x = root;
        for (int i = 0; s[i]; i++){
            int d = s[i] - 'a';
            if (child[x][d] == -1){
                child[x][d] = newnode();
            }
            x = child[x][d];
        }
        value[x] += val;
    }
    int search(char *s){
        int sum = 0, x = root;
        for (int i = 0; s[i]; i++){
            int d = s[i] - 'a';
            if (child[x][d] == -1){
                break;
            }
            x = child[x][d];
            sum += value[x];
        }
        return sum;
    }
}trie;

class KMP{//KMP匹配的板子
private:
	static const int maxn = 300010;
    int next[maxn];
    void getnext(string s, int len){
        memset(next, 0, sizeof(next));
        int i = 0, j = -1; next[0] = -1;
        while (i < len){
            if (j == -1 || s[i] == s[j]){
                next[++i] = ++j;
            }else{
                j = next[j];
            }
        }
    }
public:
    int search(string s, char *str){
        int ret = 0, j = 0;
		int lens = s.size(), lenstr = strlen(str);
        getnext(s, s.size());
        for (int i = 0; i < lenstr; i++){
            while (j > 0 && s[j] != str[i]){
                j = next[j];
            }
            if (s[j] == str[i]){
                j++;
            }
            if (j == lens){
                ret++; j = next[j];
            }
        }
        return ret;
    }
}kmp;

string lib[50];
char str[maxn];
int cnt, cntx[50];

int main(){
	int T = 1; //cin >> T;
    int t, m;
	int len, val;
    while (T--){
    	cin >> m;
        trie.init();
		cnt = 0; memset(cntx, 0, sizeof(cntx));
        for (int i = 1; i <= m; i++){
            scanf("%d%s", &t, str);
            len = strlen(str);
            if (t == 1 || t == 2){
                val = (t == 1 ? 1 : -1);//字符串权值，插入为1，删除为-1
                if (len <= 1000){//模式串长度<=1000，插入trie
                    trie.insert(str, val);
                }else{//长度>1000,单独扔到一边
                    lib[cnt] = string(str);
                    cntx[cnt++] = val;
                }
            }else{
                long long ans = 0;
                for (int i = 0; i < len; i++){//对所有后缀在trie上查找
                    ans += trie.search(str + i);
                }
                for (int i = 0; i < cnt; i++){//对所有单独的模式串KMP
                    if (lib[i].length() > len){ continue; }
                    ans += kmp.search(lib[i], str)*cntx[i];
                }
                printf("%lld\n", ans);
                fflush(stdout);
            }
        }
    }
    return 0;
}
```

- 关于时间复杂度，大概是因为这里以 1000 为标准线分类的设计比较巧妙，能很好的控制 trie 上操作和 KMP 的复杂度都不会很高。

- 空间复杂度：$\operatorname O(26m)$

---

## Solution 3 （二进制分组 &AC 自动机）

这个解法是最常规的，其他题解介绍的也差不多了。大致思想就是因为 **AC 自动机**比较难支持在线的修改查询，那样每次都要重新构造 fail 指针，复杂度会很大。所以考虑维护不超过 $\log m$ 个 AC 自动机。第 $i$ 个自动机储存 $2^i$ 个模式串，如下：

> $8,4,1$
>
> 插入一个新模式串，就新建一组 AC 自动机。
>
> $8,4,1,1$
>
> 然后只要前一个自动机大小与当前新自动机相等，就不断向前暴力合并。
>
> $8,4,2$
>
> 如果再插入:
>
> $8,4,2,1$
>
> $8,4,2,1,1\rightarrow 8,4,2,2\rightarrow 8,4,4\rightarrow 8,8 \rightarrow 16$

至于合并的方式，对每个 AC 自动机维护一个 vector 容器存里面所有的模式串，然后只要前面可以合并，就将其中所有模式串拿出来向前合并即可。每次合并结束只需要对最后一个被合并的 AC 自动机重新构建 fail 指针。

> 删除操作：可以视为插入了一个权值为 -1 的字符串，同样用新建自动机向前合并的方式。
>
> 查询操作：遍历所有 AC 自动机，进行匹配，答案为匹配个数总和。

可以看出一个模式串最多被向前合并 $\log m$ 次，且最多存在 $\log m$ 组 AC 自动机。

- 时间复杂度：$\operatorname O(m\log m)$

- 空间复杂度：$O(26m)$

一些细节 ~~（血的教训）~~：

1. 如果每个 AC 自动机都是用数组的形式，那么空间复杂度是 $\operatorname O(26m\log m)$，是会 **MLE** 的。所以这里要用**动态开点**的 AC 自动机，用 vector 存储数据。
2. 合并的过程要注意保证每个字符串只被拷贝一次，否则复杂度没法控制。
3. 因为本题数据较强，AC 自动机部分的代码一定要控制常数。
4. AC 自动机查询的函数中，不能暴力跳 fail 指针，负责会被第 27 组数据卡掉。要注意在构建 fail 指针的过程中，预处理一个点以及它 fail 指针后面的所有点权值总和，这样能避免跳 fail，保证每个点查询过程中只被遍历一次。

### Code

```cpp
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define pii pair<int,int>
#define mp make_pair
#define F first
#define S second
using namespace std;
int m,pr;
struct AC//AC自动机结构体
{
	int trienum;
	vector<int> cnt,tot,son[30],fail;//动态开点数组
	vector<pair<string,int> > v; //储存内部所有字符串及其权值的 vector
	void init()//初始化
	{
		v.clear();
		cnt.clear(),fail.clear(),tot.clear();
		trienum=0;
		cnt.pb(0),fail.pb(0),tot.pb(0);
		for(int i=0;i<26;i++)
		{
			son[i].clear();
			son[i].pb(0);
		}
	}
	void ins(string t,int x)//插入
	{
		v.pb(mp(t,x));
		int p=0;
		for(int i=0;i<(int)t.size();i++)
		{
			if (son[t[i]-'a'][p]<=0)
			{
				for(int j=0;j<26;j++)
					son[j].pb(0);
				cnt.pb(0),fail.pb(0),tot.pb(0);
				son[t[i]-'a'][p]=++trienum;
			}
			p=son[t[i]-'a'][p];
		}
		cnt[p]+=x;
	}
	void build()//bfs构建fail指针
	{
		tot.clear();
		tot.resize(trienum+1,0);
		queue<int> q;
		for(int i=0;i<26;i++)
			if (son[i][0]>0)
			{
				q.push(son[i][0]);
				tot[son[i][0]]=cnt[son[i][0]];
			}
		while(!q.empty())
		{
			int u=q.front();
			q.pop();
			for(int i=0;i<26;i++)
				if (son[i][u]>0)
				{
					fail[son[i][u]]=abs(son[i][fail[u]]);
					tot[son[i][u]]=cnt[son[i][u]]+tot[fail[son[i][u]]];//cnt是单点权值，tot是这个点和fail指针之后的所有点权值总和
					q.push(son[i][u]);
				}
				else//这一步是构造trie图，能方便失配时一步到达fail指针的位置，但是这里用负数标记，表示实际上这个儿子是不存在的
					son[i][u]=-abs(son[i][fail[u]]);
		}
	}
	ll query(string t)//查询
	{
		int u=0;
		ll res=0ll;
		for(int i=0;i<(int)t.size();i++)
		{
			u=abs(son[t[i]-'a'][u]);
			res+=tot[u];//避免了跳fail的过程
		}
		return res;
	}
}ac[25];
int main()
{
	int tp;
	char s[300005];
	scanf("%d",&m);
	while(m--)
	{
		scanf("%d%s",&tp,s);
		if (tp<3)
		{
			int val=(tp==1?1:-1);//字符串权值，插入为1，删除为-1
			int cur=0,lst=pr;
			ac[pr].init();
			ac[pr].ins(s,val);
			while(pr&&(int)ac[pr-1].v.size()==(int)ac[pr].v.size()+cur)//向前合并
				cur+=(int)ac[pr--].v.size();
			for(int i=pr+1;i<=lst;i++)
				for(auto p:ac[i].v)
					ac[pr].ins(p.F,p.S);
			ac[pr++].build();
		}
		else
		{
			ll res=0ll;
			for(int i=0;i<pr;i++)
				res+=ac[i].query(s);
			printf("%lld\n",res);
			fflush(stdout);
		}
	}
	return 0;
}
```

---

## 作者：Taduro (赞：8)

首先要用AC自动机跑匹配。

然后就是删除非常容易，只要再开一个AC自动机记录被删除得到串，然后在两个AC自动机中跑两次得到两个答案减一下就好了。

设总串长是S，操作数是m，之后就有很多的做法了：

1. 根号分治：把长度大于$\sqrt{S}$的串用hash匹配，其他的串插到一个trie里，之后hash暴力匹配长的串，而trie的深度不超过$\sqrt{S}$，再暴力枚举后缀匹配trie就做完了。
2. 根号重构：每$\sqrt{m}$个串开一个AC自动机，攒够$\sqrt{m}$个就新加进来一个，直接做。
3. AC自动机+二进制分组，考虑当前串的个数是n，对于n在二进制下的第i位数字$s_i$，就维护一个有$s_i\times 2^i$个串的trie，加入的时候从第0位开始做二进制加法，给n加一。进位的时候把当前位上的trie拿出来和上一位上来的trie合并，之后加到下一位，直到有一位是0，就停在这里，把一路合并上来的trie建成AC自动机。 查询的时候每一位跑一遍，由于每个串最多被重构$log\ n$次所以复杂度是对的。

为了复习AC自动机，我写了第三种做法，发现AC自动机全忘了。。。

由于要把trie树合并，所以以往直接在ch数组上补trie图的方法行不通了，不过可以另开一个ch2数组专门用于补trie图，因为zz翻译把串长从3e5错写成4e6，所以空间开的下。

```c++
#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
struct trie{
	int ch[26],fail,cnt,ch2[26],sum;
}t[300001];
char ch[300001];
int root[2][300001],tot,num[2],n,q;
int head,tail,team[300001],dg[2][300001];
inline void build_trie(int x,int z){
	root[z][x]=++tot; int u=tot;
	for (int i=1; i<=n; i++){
		if (!t[u].ch[ch[i]-'a'])
			t[u].ch[ch[i]-'a']=++tot;
		u=t[u].ch[ch[i]-'a'];
	}
	t[u].cnt++;
}
int merge(int u,int v){
	if (!u||!v) return u|v;
	t[u].cnt+=t[v].cnt;
	for (int i=0; i<26; i++)
		t[u].ch[i]=merge(t[u].ch[i],t[v].ch[i]);
	return u;
}
inline void get_fail(int rt){
	head=1,tail=0;
	for (int i=0; i<26; i++)
		if (t[rt].ch[i]){
			t[rt].ch2[i]=t[rt].ch[i];
			t[t[rt].ch[i]].fail=rt;
			team[++tail]=t[rt].ch[i];
		}
		else t[rt].ch2[i]=rt;
	while (head<=tail){
		int x=team[head];
		for (int i=0; i<26; i++){
			if (t[x].ch[i]){
				t[x].ch2[i]=t[x].ch[i];
				t[t[x].ch[i]].fail=t[t[x].fail].ch2[i];
				team[++tail]=t[x].ch2[i];
			}
			else t[x].ch2[i]=t[t[x].fail].ch2[i];
		}
		t[x].sum=t[x].cnt+t[t[x].fail].sum;
		head++;
	}
}
void insert(int z){
	build_trie(++num[z],z); dg[z][num[z]]=1;
	while (dg[z][num[z]]==dg[z][num[z]-1]&&num[z]>1){
		num[z]--; dg[z][num[z]]+=dg[z][num[z]+1];
		root[z][num[z]]=merge(root[z][num[z]],root[z][num[z]+1]);
	}
	get_fail(root[z][num[z]]);
}
int query(int z){
	int ans=0;
	for (int i=1; i<=num[z]; i++){
		int u=root[z][i];
		for (int j=1; j<=n; j++){
			u=t[u].ch2[ch[j]-'a'];
			ans+=t[u].sum;
		}
	}
	return ans;
}
int main(){
	int op;
	scanf("%d",&q);
while (q--){
	scanf("%d",&op);
	scanf("%s",ch+1); n=strlen(ch+1);
	if (op==1||op==2) insert(op-1);
	if (op==3) printf("%d\n",query(0)-query(1));
	fflush(stdout);
}
	return 0;
}
```


---

## 作者：tzc_wk (赞：6)

[题面传送门](https://codeforces.ml/contest/710/problem/F)

题意：强制在线的 AC 自动机。
$n,\sum|s|\leq 3\times 10^5$

[安利个人 AC 自动机学习笔记](https://www.cnblogs.com/ET2006/p/ACAM.html)

如果不是强制在线那此题就是道 sb 题，加了强制在线就不那么 sb 了。

这里介绍两种做法：

1. 根号分治

考虑到 KMP 擅长处理单个字符串匹配的情况，但对于多模式串的情况复杂度就不那么优秀了。

而 AC 自动机擅长处理多模式串匹配的情况，但预处理复杂度是线性的，每加进来一个字符串都预处理一遍复杂度显然吃不消。

考虑将二者结合，设一个临界值 $B$，每 $B$ 个串建一个 AC 自动机。剩余的若干个串暴力跑 KMP。

算下复杂度，最多要在 AC 自动机上匹配 $\frac{n}{B}$ 次，每次匹配都是 $|s|$ 的，故 AC 自动机部分的复杂度是 $\frac{n}{B}\times \sum|s|$。

再考虑 KMP，单次 KMP 是 $\mathcal O(n+m)$ 的，每个模式串最多跟 $B$ 个询问串匹配，而每个询问串也最多跟 $B$ 个模式串匹配，所以贡献为 $B\sum|s|$。

最后是删除操作，众所周知，AC 自动机是不支持删除操作的，但发现一加一减，贡献可以抵消掉，所有我们可以建两个 AC 自动机，一个处理所有 $1$ 操作加入进来的字符串，一个处理所有 $2$ 操作删除的字符串，二者相减即可。

总复杂度 $\mathcal O(\sum|s|(B+\frac{n}{B}))$，$3\times 10^5$ $n\sqrt{n}$ 大约是 $2\times 10^8$ 级别，理论上是可以的，可惜我没卡过去 qwq。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fz(i,a,b) for(int i=a;i<=b;i++)
#define fd(i,a,b) for(int i=a;i>=b;i--)
#define ffe(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
template<typename T1,typename T2> void chkmin(T1 &x,T2 y){if(x>y) x=y;}
template<typename T1,typename T2> void chkmax(T1 &x,T2 y){if(x<y) x=y;}
typedef pair<int,int> pii;
typedef long long ll;
template<typename T> void read(T &x){
	char c=getchar();T neg=1;
	while(!isdigit(c)){if(c=='-') neg=-1;c=getchar();}
	while(isdigit(c)) x=x*10+c-'0',c=getchar();
	x*=neg;
}
const int BLK=548;
const int MAXN=3e5+5;
const int ALPHA=26;
char buf[MAXN+5];
string reads(){
	scanf("%s",buf+1);int len=strlen(buf+1);
	string ret;for(int i=1;i<=len;i++) ret+=buf[i];
	return ret;
}
class solver{
public:
	struct ACAM{
		int rt[BLK+5];
		int ch[MAXN+BLK+5][ALPHA+2],fail[MAXN+BLK+5],cnt[MAXN+BLK+5],ncnt=0;
		void insert(int r,string s){
			int cur=r;
			for(int i=0;i<s.size();i++){
				if(!ch[cur][s[i]-'a']) ch[cur][s[i]-'a']=++ncnt;
				cur=ch[cur][s[i]-'a'];
			} cnt[cur]++;
		}
		void getfail(int r){
			queue<int> q;
			for(int i=0;i<ALPHA;i++){
				if(ch[r][i]) q.push(ch[r][i]),fail[ch[r][i]]=r;
				else ch[r][i]=r;
			}
			while(!q.empty()){
				int x=q.front();q.pop();
				for(int i=0;i<ALPHA;i++){
					if(ch[x][i]) fail[ch[x][i]]=ch[fail[x]][i],q.push(ch[x][i]),cnt[ch[x][i]]+=cnt[fail[ch[x][i]]];
					else ch[x][i]=ch[fail[x]][i];
				}
			}
		}
		int query(int r,string s){
			int cur=r,ret=0;
			for(int i=0;i<s.size();i++){
				cur=ch[cur][s[i]-'a'];ret+=cnt[cur];
			} return ret;
		}
	} a;
	int fail[MAXN+5];
	int getkmp(string s,string t){
		int ls=s.size(),lt=t.size();s=" "+s;t=" "+t;
		int pos=0,ret=0;
		for(int i=2;i<=lt;i++){
			while(pos&&t[pos+1]!=t[i]) pos=fail[pos];
			if(t[pos+1]==t[i]) pos++;fail[i]=pos;
		} pos=0;
		for(int i=1;i<=ls;i++){
			while(pos&&t[pos+1]!=s[i]) pos=fail[pos];
			if(t[pos+1]==s[i]) pos++;
			if(pos==lt) ret++;
		} return ret;
	}
	string ss[MAXN+5];
	int num=0,pre=0,cnt=0;
	void insert(string s){
		ss[++num]=s;
		if(num%BLK==0){
			a.rt[++cnt]=++a.ncnt;
			for(int i=pre+1;i<=num;i++) a.insert(a.rt[cnt],ss[i]);
			a.getfail(a.rt[cnt]);pre=num;
		}
	}
	int query(string s){
		int ret=0;
		for(int i=1;i<=cnt;i++) ret+=a.query(a.rt[i],s);
		for(int i=pre+1;i<=num;i++) ret+=getkmp(s,ss[i]);
		return ret;
	}
} s1,s2;
int T;
int main(){
	scanf("%d",&T);
	while(T--){
		int opt;string s;scanf("%d",&opt);s=reads();
		if(opt==1) s1.insert(s);
		else if(opt==2) s2.insert(s);
		else printf("%d\n",s1.query(s)-s2.query(s)),fflush(stdout);
	}
	return 0;
}
```

2. 二进制分组
感觉这应该是正解吧，本题官方题解给的就这个做法。

还是将加入的字符串分成若干组，每组建一个 AC 自动机。

不过与之前不同的是这次我们按**二进制**分组，即每组的大小都是 $2$ 的整数次幂。

那么这玩意儿怎么支持插入操作呢？假设我们插入字符串 $s$，我们先建一个只有一个串的 AC 自动机，然后不断与前面的 AC 自动机像合并堆一样合并。最后暴力重构一发。

是不是有点抽象？打个形象的比喻，2048，假设我们现在有 $23$ 个串，那么会分为 $4$ 组，大小分别为 $16,4,2,1$，此时你再加入一个串，就变为 $16,4,2,1,1$，最后两个 $1$ 合并，变为一个 $2$；最后两个 $2$ 合并，变为一个 $4$……以此类推。最后会得到 $16,8$。

算下复杂度，暴力重构复杂度是 $\sum|s|$ 的，而我们每个字符串最多被重构 $\log n$ 次，故插入的总复杂度是 $n\log n$ 的，而查询的时候你最多在 $\log n$ 个 AC 自动机中查询，故总复杂度为 $n\log n$，碾压算法 1。
实测 1s，可能因为有个 $26$ 的常数吧。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fz(i,a,b) for(int i=a;i<=b;i++)
#define fd(i,a,b) for(int i=a;i>=b;i--)
#define ffe(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
template<typename T1,typename T2> void chkmin(T1 &x,T2 y){if(x>y) x=y;}
template<typename T1,typename T2> void chkmax(T1 &x,T2 y){if(x<y) x=y;}
typedef pair<int,int> pii;
typedef long long ll;
template<typename T> void read(T &x){
	char c=getchar();T neg=1;
	while(!isdigit(c)){if(c=='-') neg=-1;c=getchar();}
	while(isdigit(c)) x=x*10+c-'0',c=getchar();
	x*=neg;
}
const int MAXN=3e5;
const int LOG_N=19;
const int ALPHA=26;
class solver{
public:
	int sz[LOG_N+3],rt[LOG_N+3],cnt=0;
	int oc[MAXN*2+5][ALPHA+2],ch[MAXN*2+5][ALPHA+2],ncnt=0,ed[MAXN*2+5],val[MAXN*2+5],fail[MAXN+5];
	void insert(char *s,int r){
		int len=strlen(s+1),cur=r;
		for(int i=1;i<=len;i++){
			if(!oc[cur][s[i]-'a']) oc[cur][s[i]-'a']=++ncnt;
			cur=oc[cur][s[i]-'a'];
		} ed[cur]++;
	}
	void getfail(int r){
		queue<int> q;
		for(int i=0;i<ALPHA;i++){
			if(oc[r][i]){
				fail[oc[r][i]]=r;q.push(oc[r][i]);
				val[oc[r][i]]=ed[oc[r][i]];ch[r][i]=oc[r][i];
			} else ch[r][i]=r;
		}
		while(!q.empty()){
			int x=q.front();q.pop();
			for(int i=0;i<ALPHA;i++){
				if(oc[x][i]){
					ch[x][i]=oc[x][i];
					fail[oc[x][i]]=ch[fail[x]][i];
					val[oc[x][i]]=val[fail[oc[x][i]]]+ed[oc[x][i]];
					q.push(oc[x][i]);
				} else ch[x][i]=ch[fail[x]][i];
			}
		}
	}
	int merge(int x,int y){
		if(!x||!y) return x+y;
		ed[x]+=ed[y];
		for(int i=0;i<ALPHA;i++) oc[x][i]=merge(oc[x][i],oc[y][i]);
		return x;
	}
	void insert(char *s){
		sz[++cnt]=1;rt[cnt]=++ncnt;insert(s,rt[cnt]);
		while(sz[cnt]==sz[cnt-1]){
			rt[cnt-1]=merge(rt[cnt-1],rt[cnt]);
			sz[cnt-1]<<=1;sz[cnt]=0;cnt--;
		} getfail(rt[cnt]);
	}
	int query(char *s,int r){
		int len=strlen(s+1),cur=r,ret=0;
		for(int i=1;i<=len;i++){
			cur=ch[cur][s[i]-'a'];
			ret+=val[cur];
		} return ret;
	}
	int query(char *s){
		int ret=0;
		for(int i=1;i<=cnt;i++) ret+=query(s,rt[i]);
		return ret;
	}
} s1,s2;
char buf[MAXN+5];
int main(){
	int T;scanf("%d",&T);
	while(T--){
		int opt;scanf("%d%s",&opt,buf+1);
		if(opt==1) s1.insert(buf);
		else if(opt==2) s2.insert(buf);
		else printf("%d\n",s1.query(buf)-s2.query(buf)),fflush(stdout);
	}
	return 0;
}
```

---

## 作者：cyffff (赞：4)

[$\text{Link}$](https://www.luogu.com.cn/problem/CF710F)

这个题应该至少有 *2700 吧/kel

## 题意
维护一个字符串集合，支持三种操作共 $q$ 次：
1. 加入字符串 $s$
2. 删除已有字符串 $s$
3. 查询集合中的所有字符串在给出的模板串 $s$ 中出现的次数

强制在线。

$q,\sum|s|\le10^6$.
## 思路
老师要我写题解。

删除是假的，可以看为两个集合分别代表加入和删除，求两个集合的答案差。

考虑询问形式很像 $\text{ACAM}$，如果没有强制在线，直接把所有的加入串拉出来建出 $\text{ACAM}$，加入就是子树加，查询就是在 $\text{Fail}$ 树上这个字符串对应的路径的点权和。

现在强制在线了，但如果我们知道之前所有的操作构成的 $\text{ACAM}$ 和对应的权值便可以简单查询。

考虑建立 $S$ 个 $\text{ACAM}$，当某个 $\text{ACAM}$ 达到某特定大小时不再加入字符串，新开一个 $\text{ACAM}$，否则将次串加入 $\text{ACAM}$ 并重构。每次询问遍历所有 $\text{ACAM}$ 求对应答案。发现每个字符串只会在重构中出现 $O(\dfrac{n}S)$ 次，询问有 $O(S)$ 个 $\text{ACAM}$，令 $S=O(\sqrt n)$ 则复杂度是 $O(n\sqrt n)$，无法达到~~我的~~要求。

考虑将大小相同的 $\text{ACAM}$ 合并，每次合并暴力合并 $\text{Trie}$，重建 $\text{Fail}$ 树并计算子树加带来的贡献，加入字符串时直接建立大小为 $1$ 的 $\text{ACAM}$。可以发现，每个 $\text{ACAM}$ 大小为 $2^i$，且 $i$ 互不相同。每个字符串只会合并 $O(\log n)$ 次，同时只会出现 $O(\log n)$ 个 $\text{ACAM}$。时间复杂度为 $O(n\log n)$，可以通过。

一般称这种方法为**二进制分组**，有时会有强大的作用。

代码（强制在线方法与题目描述不同，仅供参考）：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
namespace IO{//by cyffff
	
}
const int N=1e6+10;
struct ACAM{
	int cnt,rts,tr[N][26],tr2[N][26];
	int rt[N],fail[N],val[N],siz[N];
	int delcnt,del[N];
	ll tmp[N];
	inline int newnode(){
		return delcnt?del[delcnt--]:++cnt;
	}
	inline void insert(char *s,int &rt){
		if(!rt) rt=newnode();
		int n=strlen(s+1);
		int cur=rt;
		for(int i=1;i<=n;i++){
			int c=s[i]-'a';
			if(!tr[cur][c])
				tr[cur][c]=newnode();
			cur=tr[cur][c];
		}
		val[cur]++;
	}
	inline void makefail(int rt){
		queue<int>q;
		fail[rt]=rt;
		for(int i=0;i<26;i++)
			if(tr[rt][i]){
				tr2[rt][i]=tr[rt][i];
				fail[tr[rt][i]]=rt;
				q.push(tr[rt][i]);
			}else{
				tr2[rt][i]=rt;
			}
		while(!q.empty()){
			int cur=q.front();
			q.pop();
			tmp[cur]=val[cur]+tmp[fail[cur]];
			for(int i=0;i<26;i++)
				if(tr[cur][i]){
					tr2[cur][i]=tr[cur][i];
					fail[tr[cur][i]]=tr2[fail[cur]][i];
					q.push(tr[cur][i]);
				}else{
					tr2[cur][i]=tr2[fail[cur]][i];
				}
		}
	}
	inline int merge(int x,int y){
		if(!x||!y) return x+y;
		val[x]+=val[y];
//		tmp[y]=0;
//		del[++delcnt]=y;
		for(int i=0;i<26;i++)
			tr[x][i]=merge(tr[x][i],tr[y][i]);//,tr[y][i]=0;
		return x;
	}
	inline void insert(char *s){
		siz[++rts]=1;
		insert(s,rt[rts]);
		while(siz[rts-1]==siz[rts]){
			siz[rts-1]+=siz[rts];
			rt[rts-1]=merge(rt[rts-1],rt[rts]);
			rt[rts]=0;
			rts--;
		}
		makefail(rt[rts]);
	}
	inline ll query(char *s){
		int n=strlen(s+1);
		ll ans=0; 
		for(int i=1;i<=rts;i++){
			int cur=rt[i];
			for(int j=1;j<=n;j++){
				cur=tr2[cur][s[j]-'a'];
				ans+=tmp[cur];
			}
		}
		return ans;
	}
}add,del; 
int q;
char str[N];
ll last;
/*
6
1 . 25
1 ab 2
3 abcab 2
2 ab 0
1 ab 2
3 ababab 0
*/
int main(){
	q=read();
	while(q--){
		int opt=read();
		readstr(str);
		int n=strlen(str+1);
		if(n==1&&str[1]=='.') n=0; 
		ll tmp=read()^last;
		str[n+1]=tmp+'a',str[n+2]=0;
		if(opt==1) add.insert(str);
		if(opt==2) del.insert(str);
		if(opt==3) write(last=add.query(str)-del.query(str)),putc('\n');
	}
	flush();
}
```
再见 qwq~

---

## 作者：warzone (赞：4)

## 题目大意

维护一个字符串集合 $S$，初始为空。$m$ 次操作：

- `1 s` 插入字符串 $s$ 到 $S$ 中。保证此时 $s$ 不在 $S$ 中。
- `2 s` 删除字符串 $s$。保证此时 $s$ 在 $S$ 中。
- `3 s` 询问 $S$ 中的串在 $s$ 中总共出现多少次。

$\texttt{Data Range:} m,\sum|s|\le 3\times 10^5,s$ 均为小写字母，**强制在线**。

## 题解

除了 AC 自动机 + 二进制分组，本题还有一个 广义 SAM + LCT 的做法。

类似 [P5212 SubString](https://www.luogu.com.cn/problem/P5212)，用广义 SAM 维护输入的所有串，用 LCT 维护 SAM 的 fail 树。

于是 $1,2$ 操作变成 LCT 上单点修改，

$3$ 操作变为查询若干个点到根的路径的权值和。

然后就做完了。时间复杂度 $\Theta((\sum|s|)\log(\sum|s|))$。

因为基本都是板子，所以思维难度较低。



```cpp
/*
this code is made by warzone.
2021.11.19 11:38
*/
#include<stdio.h>
#include<string.h>
typedef unsigned long long ull;
typedef unsigned int word;
const word siz=600010;
struct splay{
	splay *l,*r,*fa;
	word tag,val,sum;
	inline void rev(word id){
		tag=(tag&1)^id;}
	inline void pushup(){
		sum=val;
		if(l) sum+=l->sum;
		if(r) sum+=r->sum;
	}
	inline void pushdown(){
		if(l) l->rev(tag);
		if(r) r->rev(tag);
		if(tag&1){
			splay *swap=l;
			l=r,r=swap,tag&=~1;
		}
	}
	inline void linepush(){
		if(fa) fa->linepush();
		pushdown();
	}
}p[siz];
#define cyc(root,l,r) [&](){			\
	splay *rt=root,*l=rt->l,*lr=l->r;	\
	l->fa=rt->fa,(root)=l;				\
	l->r=rt,rt->fa=l;					\
	if((rt->l=lr)) lr->fa=rt;			\
	rt->pushup();						\
}()//旋转
#define lcyc(root) cyc(root,l,r)
#define rcyc(root) cyc(root,r,l)
#define dbcyc() (rff->l==root->fa?							\
	(rff->l->l==root? lcyc(rff):rcyc(rff->l)),lcyc(rff):	\
	(rff->r->r==root? rcyc(rff):lcyc(rff->r)),rcyc(rff))//双旋
#define pos(p) ((p)->fa->l==(p)? (p)->fa->l:(p)->fa->r)
inline void Splay(splay *root){//伸展
	for(root->linepush();root->fa;)
		if(root->fa->fa)
			if(root->fa->fa->fa){
				splay *&rff=pos(root->fa->fa);dbcyc();
			}else{splay *rff=root->fa->fa;dbcyc();}
		else if(root->fa->l==root)
			root=root->fa,lcyc(root);
		else root=root->fa,rcyc(root);
	root->pushup();
}
inline void access(word id){
	splay *root=0,*next;
	for(;next=p+id,id;id=next->tag>>1){
		Splay(next),next->pushdown();
		if(next->r) next->r->rev(id<<1),next->r->fa=0;
		if((next->r=root)) root->fa=next;
		next->pushup(),root=next;
	}
}
struct SAM{
	word next[siz][26];
	word floor[siz],fail[siz];
	word size,last;
	inline SAM(){
		fail[1]=0xffffffff;
		size=last=1;
	}
	#define split()	[&](){								\
		word old=*num;									\
		floor[++size]=floor[last]+1;					\
		memcpy(next[size],next[old],sizeof(next[0]));	\
		access(old),Splay(p+old),p[old].pushdown();		\
		if((p[size].l=p[old].l)) p[size].l->fa=p+size;	\
		p[size].r=p+old,p[old].fa=p+size;				\
		p[old].l=p[old].r=0;							\
		p[old].pushup(),p[size].pushup();				\
		fail[size]=fail[old],fail[old]=size;			\
		for(;last!=0xffffffff;last=fail[last])			\
			if(*(num=next[last]+c)==old) *num=size;		\
			else break;									\
	}()//分裂结点
	inline void operator+=(char c){//SAM 插入结点
		word *num;
		if(*(num=next[last]+c)){
			if(floor[*num]==floor[last]+1)
				return void(last=*num);
			return split(),void(last=size);
		}
		floor[++size]=floor[last]+1;
		for(;last!=0xffffffff;last=fail[last])
			if(*(num=next[last]+c)==0) *num=size;
			else if(floor[*num]==floor[last]+1)
				return p[size].rev((fail[last=size]=*num)<<1);
			else return split(),p[size-1].rev(
				(fail[last=size-1]=size)<<1);
		return p[size].rev((fail[last=size]=1)<<1);
	}
}sam;
word m;
char s[siz];
int main(){
	scanf("%u",&m);
	for(word opt;m;--m){
		scanf("%u%s",&opt,s);
		if(opt==3){
			ull out=0;sam.last=1;
			for(char c:s)
				if('a'<=c&&c<='z'){
					sam+=c-'a',access(sam.last);
					Splay(p+sam.last),p[sam.last].pushdown();
					out+=p[sam.last].sum;
				}else break;//查询若干点到根路径的权值和
			printf("%llu\n",out),fflush(stdout);
		}else{
			sam.last=1;
			for(char c:s)
				if('a'<=c&&c<='z') sam+=c-'a';
				else break;
			access(sam.last),Splay(p+sam.last),p[sam.last].pushdown();
			if(opt==1) p[sam.last].val++,p[sam.last].sum++;
			else p[sam.last].val--,p[sam.last].sum--;
		}//单点修改
	}
	return 0;
}

```

---

## 作者：5k_sync_closer (赞：3)

字符串？哈希！

容易发现 $|s_i|$ 的长度有 $O(\sqrt{\sum|s_i|})$ 种。

匹配模板串 $S$ 时，考虑其所有**长度为** $k|\exists s_i,|s_i|=k$ 的子串（而非所有子串） $T$（$O(\sum|s_i|\sqrt{\sum|s_i|})$ 种），累计 $T$ 在集合中出现的次数。

注意此算法复杂度基于 $k$ 的种类数 $O(\sqrt{\sum|s_i|})$，而不是 $S$ 的子串长度种类数 $O(\sum|s_i|)$，达到优化目的。
```cpp
#include <cstdio>
#include <cstring>
#include <unordered_map>
#define B 233ll
#define M 1000000007
using namespace std;
char s[300050];
long long b[300050];
int n, m, o, x, z, f[300050], d[300050], r[300050];
unordered_map<int, int> c[650];
int main()
{
    scanf("%d", &m);
    for (int i = b[0] = 1; i <= 300000; ++i)
        b[i] = b[i - 1] * B % M;
    while (m--)
    {
        scanf("%d%s", &o, s + 1);
        n = strlen(s + 1);
        for (int i = 1; i <= n; ++i)
            f[i] = (f[i - 1] * B + s[i]) % M;
        switch (o)
        {
        case 1:
            r[x = d[n] ? d[n] : d[n] = ++z] = n;
            ++c[x][f[n]];
            break;
        case 2:
            --c[d[n]][f[n]];
            break;
        case 3:
            x = 0;
            for (int p = 1; p <= z; ++p)
                for (int l = 1, k; l + r[p] - 1 <= n; ++l)
                    x += c[p].count(k = (f[l + r[p] - 1] + M - f[l - 1] * b[r[p]] % M) % M) ? c[p][k] : 0;
            printf("%d\n", x);
            fflush(stdout);
        }
    }
    return 0;
}
```


---

## 作者：foreverlasting (赞：2)

题解同步发在[博客](https://foreverlasting1202.github.io/)里哦。

AC自动机+二进制分组。

对于插入建二进制分组的AC自动机。

考虑如何合并块，直接暴力重构再合并就行了，这样的复杂度因为块是$log$级别的所以也是一个$log$的。删除和插入是独立的，所以对于删除也建二进制分组的AC自动机，然后询问的时候插入的减去删除的就好了。

最后这一道题莫名其妙输出要加上$fflush(stdout)$，我也不知道为什么。

code:
```
//2018.11.21 by ljz
#include<bits/stdc++.h>
using namespace std;
#define res register int
#define LL long long
#define inf 0x3f3f3f3f
#define eps 1e-15
inline int read(){
    res s=0;
    bool w=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=1;ch=getchar();}
    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=getchar();
    return w?-s:s;
}
inline void _swap(res &x,res &y){
    x^=y^=x^=y;
}
inline int _abs(const res &x){
    return x>0?x:-x;
}
inline int _max(const res &x,const res &y){
    return x>y?x:y;
}
inline int _min(const res &x,const res &y){
    return x<y?x:y;
}
const int N=3e5+10;
namespace MAIN{
    char str[N];
    int Q;
    struct AC{
        struct Ac{
            int vis[26],fail,num,tot,son[26];
        }ac[N];
        int rt[N],top,cnt,siz[N];
        int merge(const res &x,const res &y){
            if(!x||!y)return x+y;
            ac[x].tot+=ac[y].tot;
            for(res i=0;i<26;i++)ac[x].son[i]=merge(ac[x].son[i],ac[y].son[i]);
            return x;
        }
        int q[N*26],he,ta;
        inline void get_fail(const res &rt){
            he=1,ta=0;
            for(res i=0;i<26;i++){
                if(ac[rt].son[i])ac[ac[rt].vis[i]=ac[rt].son[i]].fail=rt,q[++ta]=ac[rt].vis[i];
                else ac[rt].vis[i]=rt;
            }
            while(he<=ta){
                res u=q[he++];
                for(res i=0;i<26;i++){
                    if(ac[u].son[i])ac[ac[u].vis[i]=ac[u].son[i]].fail=ac[ac[u].fail].vis[i],q[++ta]=ac[u].vis[i];
                    else ac[u].vis[i]=ac[ac[u].fail].vis[i];
                }
                ac[u].num=ac[u].tot+ac[ac[u].fail].num;
            }
        }
        inline void insert(const char *str){
            rt[++top]=++cnt,siz[top]=1;
            res now=rt[top];
            for(res i=0,len=strlen(str);i<len;i++){
                res x=str[i]-'a';
                if(!ac[now].son[x])ac[now].son[x]=++cnt,now=cnt;
                else now=ac[now].son[x];
            }
            ac[now].tot=1;
            while(siz[top]==siz[top-1])top--,rt[top]=merge(rt[top],rt[top+1]),siz[top]+=siz[top+1];
            get_fail(rt[top]);
        }
        inline int query(const char *str){
            res ret=0,len=strlen(str);
            for(res i=1;i<=top;i++)
                for(res j=0,now=rt[i];j<len;j++)now=ac[now].vis[str[j]-'a'],ret+=ac[now].num;
            return ret;
        }
    }A,B;
    inline void MAIN(){
        Q=read();
        while(Q--){
            res opt=read();
            scanf("%s",str);
            if(opt==1)A.insert(str);
            if(opt==2)B.insert(str);
            if(opt==3)printf("%d\n",A.query(str)-B.query(str));
        }
    }
}
int main(){
    MAIN::MAIN();
    return 0;
}
```

---

## 作者：too_later (赞：2)

[题面戳这里](https://www.luogu.com.cn/problem/CF710F)

### 题意

给你一个字符串集合，支持插入，删除，查询给定字符串在给出的模板字符串出现的次数。

$\sum\limits_{i = 1}^t |si| \le 3e5$

### 思路

多模式匹配字符串首选 `AC 自动机` 。

删除：从原来的 AC 自动机里删除一个串很难，那么可以考虑再开一个 AC 自动机记录删除的串，两个 query 的结果相减即可。

插入：每次插入都要改 fail 指针，这意味着我们每次插入需要 `O(n)`，怎么办嘞？

每次插入都会消耗 AC 自动机的节点个数逃不掉的，不能从求 fail 指针优化入手，那么只能优化每次插入对应 AC 自动机的节点个数。

考虑二进制优化。

将串的个数以二进制分开，加入一个串的时候如果块的大小与前面大小一样就与前面合并，最后再 `getfail` 。（楼下说类似 2048 很形象的比喻）

二进制思想核心：保证每个节点**更新次数只有 $logn$ 次**，**维护 $logn$ 个块**。

注意点：

1.  发现在 `getfail` 的时候一部分 trie 被修改过，被修改过的无法参与接下来的 getfail。 那么开两个 trie， 一个是原来的 trie，一个是 getfail 的时候修改过的 trie。

2. 可能每个点 root 编号会与之后的重复，我这里开大了 cnt 的大小。

对我的码风应该还是~~比较自信~~的：

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 6e5 + 5;

class Aho_C_Automaton{
private:
	int tot, val[N], sum[N], fail[N], c[N][26], ch[N][26];
	int id, cnt, rt[N], sz[N];
	
public:
	void init(){
		tot = 3e5; cnt = id = 0;
		memset(c, 0, sizeof(c));
		memset(ch, 0, sizeof(ch));
		memset(fail, 0, sizeof(fail));
		memset(val, 0, sizeof(val));
		memset(sum, 0, sizeof(sum));
	}
	
	void ins(char *s, int len, int k){
		int now = k;
		for(int v, i = 1; i <= len; i++){
			if(!c[now][v = s[i] - 'a'])
				c[now][v] = ++tot;
			now = c[now][v];
		}
		val[now]++;
	}
	
	void get_fail(int s){
		fail[s] = s;
		queue<int> q;
		for(int i = 0; i < 26; i++)
			if(c[s][i])
				q.push(c[s][i]), fail[ch[s][i] = c[s][i]] = s;
			else ch[s][i] = s;
		while(!q.empty()){
			int k = q.front(); q.pop();
			for(int i = 0; i < 26; i++){
				if(c[k][i]){
					ch[k][i] = c[k][i];
					fail[c[k][i]] = ch[fail[k]][i];
					q.push(c[k][i]);
				}
				else ch[k][i] = ch[fail[k]][i];
			}
			sum[k] = val[k] + sum[fail[k]];
		}
	}
	
	int merge(int x, int y){
		if(!x || !y) return x | y;
		val[x] += val[y];
		for(int i = 0; i < 26; i++)
			c[x][i] = merge(c[x][i], c[y][i]);
		return x;
	}
	
	void insert(char *s, int len){
		rt[++cnt] = ++id; sz[cnt] = 1;
		ins(s, len, rt[cnt]);
		while(sz[cnt] == sz[cnt - 1]){
			sz[--cnt] <<= 1;
			rt[cnt] = merge(rt[cnt], rt[cnt + 1]);
		}
		get_fail(rt[cnt]);
	}
	
	int query(char *s, int len){
		int now = 0, ans = 0;
		
		for(int i = 1; i <= cnt; i++){
			now = rt[i];
			for(int j = 1; j <= len; j++)
				ans += sum[now = ch[now][s[j] - 'a']];
//				cout << now << ' ' << j << ' ' << val[now] << endl;
		}
		return ans;
	}
	
} A, B;

int T, op, len;
char c[N];

int main(){
	A.init(), B.init();
	scanf("%d", &T);
	while(T--){
		scanf("%d%s", &op, c + 1);
		len = strlen(c + 1);
		if(op == 1) A.insert(c, len);
		if(op == 2) B.insert(c, len);
		if(op == 3) cout << A.query(c, len) - B.query(c, len) << endl;
	}
	printf("too_late 永远可爱！\n");
	return 0;
}
```

---

too_late 永远可爱！

---

## 作者：orz_z (赞：1)

[更好的阅读体验](https://www.cnblogs.com/orzz/p/15201535.html)

我的第一篇黑题题解，应该好好庆祝。

# 题目大意

给定一个字符串集合，支持的操作有插入，删除和查询给定字符串在给出的模板字符串出现的次数。

操作数 $m \leq 3 \times 10^5$，输入字符串总长度 $\sum |s_i| \leq 3\times 10^5$。

本题强制在线。

# 解题思路

首先看到多模式匹配字符串应该想到 `AC` 自动机。

关于 `AC` 自动机，可以参考我的博客，点[这里](https://blog.csdn.net/qq_46258139/article/details/119918655)。

先考虑删除操作，再开一个 `AC` 自动机记录删除的串，两个 `query` 的结果相减即可（满足相减性）。

再考虑插入操作，每次插入都要改 `fail` 指针，这意味着我们每次插入需要 $O(n)$，怎么办？

考虑优化每次插入对应 `AC` 自动机的节点个数，可将 `AC` 自动机进行二进制分组。

例，已经插入 $15$ 个字符串，则有 $5$ 个 `AC` 自动机，每个 `AC` 自动机对应的字符串个数分别为 $8$，$4$，$2$，$1$。

假设现在又要插入一个字符串，则 `AC` 自动机会合并成 $1$ 个，对应的字符串个数为 $16$。

说实话这有点像那个 $2048$ 小游戏。

因为二进制分组保证了每个节点的更新次数只有 $\log n$ 次，最多维护 $\log n$ 个块，顾时间复杂度为 $O(m n \log n)$。

# AC CODE

小细节：应在每次输出后调用 `fflush(stdout)`（然而我也不知道为什么）

```cpp
#include <bits/stdc++.h>
using namespace std;

const int _ = 6e5 + 5;

struct AC
{
    int tot, val[_], sum[_], fail[_], c[_][26], ch[_][26];
    int id, cnt, rt[_], siz[_];

    void ins(char *s, int len, int k)
    {
        int now = k;
        for (int i = 0; i < len; i++)
        {
            int v = s[i] - 'a';
            if (!c[now][v])
                c[now][v] = ++tot;
            now = c[now][v];
        }
        val[now]++;
    }

    void get_fail(int s)
    {
        fail[s] = s;
        queue<int> q;
        for (int i = 0; i < 26; i++)
            if (c[s][i])
            {
                ch[s][i] = c[s][i];
                q.push(c[s][i]);
                fail[ch[s][i]] = s;
            }
            else
                ch[s][i] = s;
        while (!q.empty())
        {
            int k = q.front();
            q.pop();
            for (int i = 0; i < 26; i++)
            {
                if (c[k][i])
                {
                    ch[k][i] = c[k][i];
                    fail[c[k][i]] = ch[fail[k]][i];
                    q.push(c[k][i]);
                }
                else
                    ch[k][i] = ch[fail[k]][i];
            }
            sum[k] = val[k] + sum[fail[k]];
        }
    }

    int merge(int x, int y)
    {
        if (!x || !y)
            return x + y;
        val[x] += val[y];
        for (int i = 0; i < 26; i++)
            c[x][i] = merge(c[x][i], c[y][i]);
        return x;
    }

    void insert(char *s, int len)
    {
        rt[++cnt] = ++id;
        siz[cnt] = 1;
        ins(s, len, rt[cnt]);
        while (siz[cnt] == siz[cnt - 1])
        {
            cnt--;
            siz[cnt] *= 2;
            rt[cnt] = merge(rt[cnt], rt[cnt + 1]);
        }
        get_fail(rt[cnt]);
    }

    int query(char *s, int len)
    {
        int now = 0, ans = 0;
        for (int i = 1; i <= cnt; i++)
        {
            now = rt[i];
            for (int j = 0; j < len; j++)
            {
                now = ch[now][s[j] - 'a'];
                ans += sum[now];
            }
        }
        return ans;
    }

} A, B;

int T, op, len;
char c[_];

signed main()
{
    A.tot = B.tot = 3e5 + 1;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%s", &op, c);
        len = strlen(c);
        if (op == 1)
            A.insert(c, len);
        if (op == 2)
            B.insert(c, len);
        if (op == 3)
            printf("%d\n", A.query(c, len) - B.query(c, len));
        fflush(stdout);
    }
    return 0;
}
```

---

## 作者：MikukuOvO (赞：1)

首先我们发现答案具有可减性，不难想到对于插入和删除的字符串分别建$AC$自动机。

但是$AC$自动机并不支持在线的操作，我们考虑二进制分组，每次暴力重构，注意由于有合并操作，我们不能直接搞出$trie$图，我们在原有的$ch$数组上在新增一个数组即可。

```cpp
const int N=3e5+5;
const int S=26;

int T;
char s[N];

struct ac
{
    int tot,top;
    int ch[N][S],tr[N][S],fail[N],cnt[N],end[N],rt[N],siz[N];

    void getfail(int x)
    {
        queue<int>q;
        for(int i=0;i<26;++i)
        {
            int v=ch[x][i];
            if(v) fail[tr[x][i]=ch[x][i]]=x,q.push(v);
            else tr[x][i]=x;
        }
        while(!q.empty())
        {

            int u=q.front();
            q.pop();
            for(int i=0;i<26;++i)
            {
                int v=ch[u][i];
                if(v)
                {
                    tr[u][i]=v,fail[v]=tr[fail[u]][i];
                    q.push(v);
                }
                else tr[u][i]=tr[fail[u]][i];
            }
            cnt[u]=end[u]+cnt[fail[u]];
        }
    }
    int merge(int x,int y)
    {
        if(!x||!y) return x|y;
        end[x]+=end[y];
        for(int i=0;i<26;++i) ch[x][i]=merge(ch[x][i],ch[y][i]);
        return x;
    }
    void insert(char *s)
    {
        rt[++top]=++tot,siz[top]=1;
        int cur=rt[top],n=strlen(s+1);
        for(int i=1;i<=n;++i)
        {
            int c=s[i]-'a';
            if(!ch[cur][c]) ch[cur][c]=++tot;
            cur=ch[cur][c];
        }
        end[cur]=1;
        while(top&&siz[top]==siz[top-1])
        {
            --top;
            rt[top]=merge(rt[top],rt[top+1]);
            siz[top]+=siz[top+1];
        }
        getfail(rt[top]);
    }
    int query(char *s)
    {
        int res=0,n=strlen(s+1);
        for(int i=1;i<=top;++i)
        {
            int cur=rt[i];
            for(int j=1;j<=n;++j)
            {
                cur=tr[cur][s[j]-'a'];
                res+=cnt[cur];
            }
        }
        return res;
    }
}T1,T2;
int main()
{
    fio();
    gi(T);
    while(T--)
    {
        int op;
        gi(op),scanf("%s",s+1);
        if(op==1) T1.insert(s);
        else if(op==2) T2.insert(s);
        else print(T1.query(s)-T2.query(s)),pc(10),fflush(stdout);
    }
    end();
}
```

---

## 作者：__Hacheylight__ (赞：1)

很容易想到AC自动机，但是却发现不怎么支持删除 (我太菜了)

完蛋，怎么办？

思考如何优化暴力

有两种暴力：一种是kmp，一种是trie


trie时间复杂度优秀，但空间不行；

kmp时间不行

那么我们可以互补一下

对于长度小于 $sqrt$ 的，我们加入 $trie$ 中，否则暴力 $kmp$，这样能够维持时间复杂度，因为总长不大

分块思想真妙！

```cpp
#include <map>
#include <set>
#include <ctime>
#include <queue>
#include <stack>
#include <cmath>
#include <vector>
#include <bitset>
#include <cstdio>
#include <cctype>
#include <string>
#include <numeric>
#include <cstring>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <functional>
using namespace std ;
//#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define per(i, a, b) for (int i = (a); i >= (b); i--)
#define loop(s, v, it) for (s::iterator it = v.begin(); it != v.end(); it++)
#define cont(i, x) for (int i = head[x]; i; i = e[i].nxt)
#define clr(a) memset(a, 0, sizeof(a))
#define ass(a, sum) memset(a, sum, sizeof(a))
#define lowbit(x) (x & -x)
#define all(x) x.begin(), x.end()
#define ub upper_bound
#define lb lower_bound
#define pq priority_queue
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define iv inline void
#define enter cout << endl
#define siz(x) ((int)x.size())
#define file(x) freopen(#x".in", "r", stdin),freopen(#x".out", "w", stdout)
typedef long long ll ;
typedef unsigned long long ull ;
typedef pair <int, int> pii ;
typedef vector <int> vi ;
typedef vector <pii> vii ;
typedef queue <int> qi ;
typedef queue <pii> qii ;
typedef set <int> si ;
typedef map <int, int> mii ;
typedef map <string, int> msi ;
const int N = 300010 ;
const int Sqrt = 500 ;
const int M = N / Sqrt + 10 ;
const int INF = 0x3f3f3f3f ;
const int iinf = 1 << 30 ;
const ll linf = 2e18 ;
const int MOD = 1000000007 ;
const double eps = 1e-7 ;
void print(int x) { cout << x << endl ; exit(0) ; }
void PRINT(string x) { cout << x << endl ; exit(0) ; }
void douout(double x){ printf("%lf\n", x + 0.0000000001) ; }
template <class T> void chmin(T &a, T b) { if (a > b) a = b ; }
template <class T> void chmax(T &a, T b) { if (a < b) a = b ; }
void upd(int &a, int b) { (a += b) %= MOD ; }
void mul(int &a, int b) { a = 1ll * a * b % MOD ; }

char s[N] ;
string st[M] ;
int cost[M] ;
int trie[N][29], value[N], nxt[N] ;
int Q, op, tot = 1, cnt, len ;

signed main(){
//	freopen("test.in", "r", stdin) ;
//	freopen("test.out", "w", stdout) ;
	scanf("%d", &Q) ;
	while (Q--) {
		scanf("%d %s", &op, s) ;
		len = strlen(s) ;
		if (op < 3) {
			if (len <= Sqrt) {
				int now = 1 ;
				rep(i, 0, len - 1) {
					int c = s[i] - 'a' ;
					if (!trie[now][c]) trie[now][c] = ++tot ;
					now = trie[now][c] ;
				}
				value[now] += 3 - 2 * op ;
			} else {
				st[cnt] = "" ;
				rep(j, 0, len - 1) st[cnt] += s[j] ;
				st[cnt] += '{' ;
				cost[cnt] = 3 - 2 * op ;
				cnt++ ;
			}
		} else {
			ll ans = 0 ;
			rep(j, 0, len - 1) {
				int now = 1 ;
				rep(k, j, len - 1) {
					int c = s[k] - 'a' ;
					if (!trie[now][c]) break ;
					now = trie[now][c] ;
					ans += value[now] ;
				}
			}
		//	cout << ans << endl ;
			rep(id, 0, cnt - 1) {
				int Len = siz(st[id]) - 1 ; // 有一个结尾符
				if (Len > len) continue ;
				nxt[1] = 0 ;
				for (int i = 2, j = 0; i <= Len; i++) {
					while (j && st[id][i - 1] != st[id][j]) j = nxt[j] ;
					if (st[id][i - 1] == st[id][j]) j++ ;
					nxt[i] = j ;
				}
				for (int i = 1, j = 0; i <= len; i++) {
					while (j && s[i - 1] != st[id][j]) j = nxt[j] ;
					if (s[i - 1] == st[id][j]) j++ ;
					if (j == Len) ans += cost[id] ;
				}
			}
			cout << ans << endl ;
		}
	}
	return 0 ;
}

/*
写代码时请注意：
	1.ll？数组大小，边界？数据范围？
	2.精度？
	3.特判？
	4.至少做一些
思考提醒：
	1.最大值最小->二分？
	2.可以贪心么？不行dp可以么
	3.可以优化么
	4.维护区间用什么数据结构？
	5.统计方案是用dp？模了么？
	6.逆向思维？
*/



```

---

## 作者：_lbw_ (赞：0)

首先这个操作很难不想到 AC 自动寄，直接建出来两个 AC 自动寄，1 操作的和 2 操作的，然后相减寄可。

接下来转化为每次加入一个串，维护 AC 自动寄。

但是发现我们每次都要加一个串到 AC 自动寄里面去非常麻烦，复杂度直接爆炸。

首先要知道的是合并两个 AC 自动寄的时间是两个自动寄的大小之和，我们实际上是把一个 $k-1$ 的自动寄和 $1$ 的自动寄合并了起来，非常的亏啊。

于是我们能联想到分治 FFT，就是把它分成一半再合并，这个可以达到复杂度最小化。

但是问题又来了，这个要动态加入，怎么办呢。

我们有一个聪明的办法，叫做二进制分组，可以每 $2^k$ 维护一个自动寄。

就比如说现在 是第 $(1011)_2+1$ 次加入，我们的自动寄就是 $1$ 到 $2^3$ 一组，$2^3+1$ 到 $2^3+2^1 $ 一组，$2^3+2^1+1$ 到 $2^3+2^1+2^0$ 一组（这个还挺难想）。

那怎么加入呢，我们想到二进制加法，你底下加 1 怎么办，是不是一个一个进位上去知道这位是 0 进不了位对吧，于是我们模拟这个操作。

接下来我们考虑为什么复杂度对了，我们不算每一次加入的复杂度，而是考虑一个点会被合并几次，其实只会从下到上 $\log n$ 次就行了。

而在查询的时候只会有 $\log n $ 个 AC 自动寄，所以复杂度为 $\mathcal{O}(m\log n)$。



---

## 作者：Star_Cried (赞：0)

## CF710F String Set Queries

### 题意

动态支持加入删除字符串和字符串匹配

### 思路

~~动态 AC自动机~~

先不考虑动态情况。对于加入一个字符串，直接插入到自动机即可。

考虑删除。发现对于答案具有可减性，意思是对于同一个匹配串，答案可以表示为在自动机中匹配的答案减去删去的所有串匹配的答案。那我们考虑给所有删除的串也开一个 AC 自动机，每次询问在两个自动机中匹配将答案相减即可。

现在考虑动态情况。因为强制在线，且 AC 自动机是离线的，我们每插入一个字符串相当于重新建了一个自动机，每次在所有自动机中匹配结果的和即为答案。减少时间消耗的唯一途径是对 AC 自动机进行合并。

考虑如何合并时间复杂度有保证且优秀。有很多办法，比如根号重构、二进制分组等。后者比较优秀也比较好写。

### 实现

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cctype>
#include<cstring>
#include<cmath>
#include<string>
using namespace std;
namespace star
{
	const int maxn=3e5+10;
	struct ACmation{
		int tot,son[maxn][26],val[maxn],fail[maxn],st[maxn],N,n,siz[maxn],beg[maxn];
		string S[maxn];
		inline void ins(string s,int ro){
			int x=ro;
			for(auto t:s){
				t-='a';
				if(son[x][t]==ro){
					son[x][t]=++tot;
					for(int j=0;j<26;j++) son[tot][j]=ro;
				}
				x=son[x][t];
			}
			val[x]++;
		}
		inline void build(int ro){
			fail[ro]=ro;
			static int q[maxn];
			int hd=0,tl=1;
			q[tl]=ro;
			while(hd<tl){
				int x=q[++hd];
				for(int t=0;t<26;t++){
					int u=son[x][t];
					if(u!=ro){
						fail[u]=x==ro?x:son[fail[x]][t];
						if(son[fail[x]][t]!=u) val[u]+=val[son[fail[x]][t]];
						q[++tl]=u;
					}else son[x][t]=son[fail[x]][t];
				}
			}
		}
		inline int query(string s,int x){
			int ans=0;
			for(auto t:s)
				x=son[x][t-'a'],ans+=val[x];
			return ans;
		}
		inline void merge(){
			siz[--N]<<=1;
			for(int i=st[N];i<=tot;i++){
				val[i]=fail[i]=0;
				for(int j=0;j<26;j++) son[i][j]=0;
			}
			tot=st[N];
			for(int i=0;i<26;i++) son[tot][i]=tot;
			for(int i=beg[N];i<=n;i++) ins(S[i],st[N]);
			build(st[N]);
		}
		inline void insert(string s){
			st[++N]=++tot;
			for(int i=0;i<26;i++) son[tot][i]=tot;
			siz[N]=1;
			ins(s,tot),build(st[N]);
			S[beg[N]=++n]=s;
			while(siz[N]==siz[N-1]) merge();
		}
		inline int query(string s){
			int ans=0;
			for(int i=1;i<=N;i++) ans+=query(s,st[i]);
			return ans;
		}
	}a,b;
	inline void work(){
		int m;cin>>m;
		while(m--){
			int op;string s;
			cin>>op>>s;
			switch(op){
				case 1:a.insert(s);break;
				case 2:b.insert(s);break;
				case 3:cout<<a.query(s)-b.query(s)<<endl;break;
			}
		}
	}
}
signed main(){
	star::work();
	return 0;
}
```





---

## 作者：NaCN (赞：0)


一个集合支持三种操作
+ 插入字符串
+ 删除字符串
+ 查询该字符串中集合内字符串出现次数




删除和插入可以建两个$AC$自动机，相减即可。如果查询少，就查询的时候建立$AC$自动机。如果插入少就可以暴力每次建立多个AC自动机。

可是这道题需要动态的，考虑二进制分组。比如$11=1+2+8$,有$11$个字符串的就可以根据有$1$个串的$AC$自动机+有$2$个串的$AC$自动机+有$8$个串的$AC$自动机。插入的时候考虑二进制加法的形式，进位即合并前后**字典树**。然后暴力建立$AC$自动机。

### 复杂度
由于$\sum |S|\leq4\times 10^5$，合并$O(|S_i|\log |S_i|)$。查询$O(S_q \log |S_i|)$



  
```c++

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cmath>
#include <cstring>
#include <vector>
#include <map>
#include <stack>
using namespace std;
typedef long long ll;
#define pii pair<int, int>
#define mk make_pair
const int N = 1e6 + 10;
const int mod = 1e9 + 7;

const int AN = 3e5 + 100;
struct ACAM
{
    int nxt[N][26], tmp[N][26], fail[AN], rt[30], end[N], sum[N], siz[30];
    int top, acnt;
    ACAM() { top = acnt = 0; }
    void getfail(int root)
    {
        queue<int> q;
        for (int i = 0; i < 26; i++)
        {
            int to = tmp[root][i];
            if (!to)
                nxt[root][i] = root;
            else
            {
                nxt[root][i] = to;
                fail[to] = root;
                q.push(to);
            }
        }
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            sum[u] = end[u] + sum[fail[u]];
            for (int i = 0; i < 26; i++)
            {
                int to = tmp[u][i];
                if (!to)
                    nxt[u][i] = nxt[fail[u]][i];
                else
                {
                    nxt[u][i] = to;
                    fail[to] = nxt[fail[u]][i];
                    q.push(to);
                }
            }
        }
    }
    int merge(int x, int y)
    {
        if (!x || !y)
            return x | y;
        end[x] += end[y];
        for (int i = 0; i < 26; ++i)
            tmp[x][i] = merge(tmp[x][i], tmp[y][i]);
        return x;
    }
    void insert(char *t)
    {
        int len = strlen(t + 1);
        rt[++top] = ++acnt;
        siz[top] = 1;
        int u = acnt;
        for (int i = 1; i <= len; i++)
        {
            int id = t[i] - 'a';
            if (!tmp[u][id])
                tmp[u][id] = ++acnt;
            u = tmp[u][id];
        }
        end[u] = 1;
        while (top && siz[top] == siz[top - 1])
        {
            top--;
            rt[top] = merge(rt[top], rt[top + 1]);
            siz[top] += siz[top + 1];
            siz[top + 1] = rt[top + 1] = 0;
        }
        getfail(rt[top]);
    }
    int query(char *s)
    {
        int res = 0, n = strlen(s + 1);
        for (int i = 1; i <= top; ++i)
        {
            int cur = rt[i];
            for (int j = 1; j <= n; ++j)
            {
                cur = nxt[cur][s[j] - 'a'];
                res += sum[cur];
            }
        }
        return res;
    }

} t1, t2;

int main()
{
    int q;
    scanf("%d", &q);
    while (q--)
    {
        int op;
        char t[N];
        scanf("%d %s", &op, t + 1);
        if (op == 1)
            t1.insert(t);
        else if (op == 2)
            t2.insert(t);
        else
        {
            printf("%d\n", t1.query(t) - t2.query(t));
        }
        fflush(stdout);
    }
}


---

