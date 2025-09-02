# Huffman Coding on Segment

## 题目描述

Alice wants to send an important message to Bob. Message $ a=(a_{1},...,a_{n}) $ is a sequence of positive integers (characters).

To compress the message Alice wants to use binary Huffman coding. We recall that binary Huffman code, or binary prefix code is a function $ f $ , that maps each letter that appears in the string to some binary string (that is, string consisting of characters '0' and '1' only) such that for each pair of different characters $ a_{i} $ and $ a_{j} $ string $ f(a_{i}) $ is not a prefix of $ f(a_{j}) $ (and vice versa). The result of the encoding of the message $ a_{1},a_{2},...,a_{n} $ is the concatenation of the encoding of each character, that is the string $ f(a_{1})f(a_{2})...\ f(a_{n}) $ . Huffman codes are very useful, as the compressed message can be easily and uniquely decompressed, if the function $ f $ is given. Code is usually chosen in order to minimize the total length of the compressed message, i.e. the length of the string $ f(a_{1})f(a_{2})...\ f(a_{n}) $ .

Because of security issues Alice doesn't want to send the whole message. Instead, she picks some substrings of the message and wants to send them separately. For each of the given substrings $ a_{li}...\ a_{ri} $ she wants to know the minimum possible length of the Huffman coding. Help her solve this problem.

## 说明/提示

In the first query, one of the optimal ways to encode the substring is to map $ 1 $ to "0", $ 2 $ to "10" and $ 3 $ to "11".

Note that it is correct to map the letter to the empty substring (as in the fifth query from the sample).

## 样例 #1

### 输入

```
7
1 2 1 3 1 2 1
5
1 7
1 3
3 5
2 4
4 4
```

### 输出

```
10
3
3
5
0
```

# 题解

## 作者：tzc_wk (赞：4)

安利个人 blog：https://www.cnblogs.com/ET2006/

[Codeforces 题目传送门](https://codeforces.com/contest/700/problem/D) & [洛谷题目传送门](https://www.luogu.com.cn/problem/CF700D)

~~好家伙，刚拿到此题时我连啥是 huffman 编码都不知道~~

一种对 $k$ 个字符进行的 huffman 编码的方案可以看作一个由 $k$ 个叶节点组成的二叉树，从根节点开始走到左儿子相当于在字符串后面添一个 $0$，走到右儿子相当于在字符串后面添一个 $1$，那么一个叶子节点就对应着一个字符的编码。

huffman 编码的一个很经典的问题是，我们现在对每个字符定义了一个频率 $f_i$，我们需构造出一棵有 $k$ 个叶子节点的二叉树并将每个字符与一个叶子节点对应，假设第 $i$ 种字符对应的叶子节点的深度为 $d_i$，现在我们需最小化 $\sum\limits_{i=1}^kf_id_i$。

这个问题可以用贪心+堆来解决，我们考虑初始 $k$ 个点都单独成一棵森林，每次要合并两个节点，也就是新建一个节点，左右儿子分别是待合并的两个节点，新节点的权值为两个节点的权值和。由于两个节点进行了一次合并，它们的深度都增加了 $1$，故答案增加了两个节点的点权之和。如此操作下去，合并 $k-1$ 次之后就可以得到一棵二叉树。显然根据贪心的思想，每次合并的两个节点应当为所有点点权值最小的两个节点。这个过程可以用堆优化，复杂度 $k\log k$。

代码大概长这样：

```cpp
while(q.size()>1){
	int x=q.top();q.pop();
    x+=q.top();q.pop();
	ret+=x;q.push(x);
}
```

---

回到本题来，显然求出区间内每个数的出现次数是必须求出的，这可以用莫队维护，复杂度 $m\sqrt{n}$。假设 $cnt_i$ 为 $i$ 出现的次数。本题的难点就在于知道每个数的出现次数之后怎样计算答案，显然每次询问都重复一遍上面的操作复杂度最坏可达 $qn\log n$，会炸。不过 $cnt$ 数组有一个很好的性质，那就是 $\sum cnt_i=r-l+1$，也就是说所有 $cnt_i$ 的总和不会太大，这启发我们用根号分治的思想，我们设一个阈值 $B$，然后考虑这样两个暴力：

- 对于 $cnt_i>B$ 的数，这样的数至多只有 $\dfrac{n}{B}$ 个，对于这样的数我们暴力跑一遍上面的过程即可。
- 对于 $cnt_i\leq B$ 的数，这样的数可能很多，不过这些数的出现次数只有 $\mathcal O(B)$ 级别，故我们转而枚举出现次数 $c$，我们建立一个桶 $b_c$ 表示出现次数为 $c$ 的数有多少个（$b$ 数组可以在莫队 push/pop 的过程中 $\mathcal O(1)$ 求出）。假设我们现在枚举到出现次数为 $c$ 的数，我们将这 $b_c$ 个数两两配对并合并成 $2c$，显然会合并出 $\lfloor\dfrac{b_c}{2}\rfloor$ 个 $2c$，对答案产生 $\lfloor\dfrac{b_c}{2}\rfloor·2c$ 的贡献。由于经过我们这么一合并，出现次数为 $2c$ 的数多了 $\lfloor\dfrac{b_c}{2}\rfloor$，故令 $b_{2c}\leftarrow b_{2c}+\lfloor\dfrac{b_c}{2}\rfloor$，特别地，如果 $2c>B$，那么我们就暴力把这 $\lfloor\dfrac{b_c}{2}\rfloor$ 个 $2c$ 插入优先队列，到时候与原本出现次数就大于 $B$ 的数一起合并。另外，如果 $b_c$ 为奇数，那么意味着会有一个落单的 $c$，我们实时维护一个变量 $pre$ 记录落单的值是什么，我们扫描到 $c$ 时如果发现临时变量不为 $0$ 就首先拎出一个 $c$ 出来与 $pre$ 合并成 $pre+c$，即如果 $pre+c\leq B$ 就令 $b_{pre+c}\leftarrow b_{pre+c}+1$，否则将 $pre+c$ 压入优先队列。细节有亿点多，具体见代码罢。

算下复杂度，对于 $cnt_i>B$ 的数，复杂度显然是 $\dfrac{n}{B}\log\dfrac{n}{B}$ 的，毫无疑问。对于 $cnt_i\leq B$ 的数扫描一遍也是 $\mathcal O(B)$ 的。重点在于每次把这 $\lfloor\dfrac{b_c}{2}\rfloor$ 个 $2c$ 插入优先队列，最多会插多少次。不难发现我们每次合并前后，$\sum c·b_c$ 始终是定值，为 $r-l+1$，也就是说当我们合并完出现次数 $\leq B$ 的数后依旧有 $\sum c·b_c=r-l+1$，故插入优先队列的数还是 $\dfrac{n}{B}$ 级别的，复杂度即为 $B+\dfrac{n}{B}\log\dfrac{n}{B}$

取 $B=\sqrt{n\log n}$ 即可实现 $\sqrt{n\log n}$ 实现询问，总复杂度 $m\sqrt{n}+m\sqrt{n\log n}=m\sqrt{n\log n}$，可通过此题。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
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
namespace fastio{
	#define FILE_SIZE 1<<23
	char rbuf[FILE_SIZE],*p1=rbuf,*p2=rbuf,wbuf[FILE_SIZE],*p3=wbuf;
	inline char getc(){return p1==p2&&(p2=(p1=rbuf)+fread(rbuf,1,FILE_SIZE,stdin),p1==p2)?-1:*p1++;}
	inline void putc(char x){(*p3++=x);}
	template<typename T> void read(T &x){
		x=0;char c=getchar();T neg=0;
		while(!isdigit(c)) neg|=!(c^'-'),c=getchar();
		while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=getchar();
		if(neg) x=(~x)+1;
	}
	template<typename T> void recursive_print(T x){if(!x) return;recursive_print(x/10);putc(x%10^48);}
	template<typename T> void print(T x){if(!x) putc('0');if(x<0) putc('-'),x=~x+1;recursive_print(x);}
	void print_final(){fwrite(wbuf,1,p3-wbuf,stdout);}
}
const int MAXN=1e5;
const int MAX_BLK=316;
const int MAX_BLK2=1400;
int n,qu,a[MAXN+5],cnt[MAXN+5],cnt_cnt[MAXN+5],tmp[MAX_BLK2+5];
int blk,blk_cnt,blk_v,L[MAX_BLK+2],R[MAX_BLK+2],bel[MAXN+5];
vector<int> tt;ll ret[MAXN+5];
void ins(int v){cnt_cnt[cnt[v]]--;cnt[v]++;cnt_cnt[cnt[v]]++;}
void del(int v){cnt_cnt[cnt[v]]--;cnt[v]--;cnt_cnt[cnt[v]]++;}
ll deal(){
	priority_queue<int,vector<int>,greater<int> > q;
	for(int i=0;i<tt.size();i++) if(cnt[tt[i]]>blk_v) q.push(cnt[tt[i]]);
	for(int i=1;i<=blk_v;i++) tmp[i]=cnt_cnt[i];int pre=0;ll ret=0;
	for(int i=1;i<=blk_v;i++) if(tmp[i]){
		if(pre){
			ret+=pre+i;tmp[i]--;
			if(pre+i<=blk_v) tmp[pre+i]++;
			else q.push(pre+i);
			pre=0;
		} ret+=1ll*i*(tmp[i]/2*2);
		if(i+i<=blk_v) tmp[i+i]+=tmp[i]/2;
		else for(int j=1;j<=tmp[i]/2;j++) q.push(i+i);
		if(tmp[i]&1) pre=i;
	}
	if(pre) q.push(pre);
	while(q.size()>1){
		int x=q.top();q.pop();x+=q.top();q.pop();
		ret+=x;q.push(x);
	} return ret;
}
struct query{
	int l,r,id;
	bool operator <(const query &rhs){
		if(bel[l]!=bel[rhs.l]) return bel[l]<bel[rhs.l];
		return r<rhs.r;
	}
} q[MAXN+5];
int main(){
	scanf("%d",&n);for(int i=1;i<=n;i++) scanf("%d",&a[i]),cnt[a[i]]++;
	blk=(int)pow(n,0.5);blk_v=(int)sqrt(n*log(n)/log(2));blk_cnt=(n-1)/blk+1;
	for(int i=1;i<=MAXN;i++) if(cnt[i]>blk_v) tt.pb(i);memset(cnt,0,sizeof(cnt));
	for(int i=1;i<=blk_cnt;i++){
		L[i]=(i-1)*blk+1;R[i]=min(i*blk,n);
		for(int j=L[i];j<=R[i];j++) bel[j]=i;
	} scanf("%d",&qu);
	for(int i=1;i<=qu;i++) scanf("%d%d",&q[i].l,&q[i].r),q[i].id=i;
	sort(q+1,q+qu+1);int cl=1,cr=0;
	for(int i=1;i<=qu;i++){
		while(cr<q[i].r) ins(a[++cr]);
		while(cl>q[i].l) ins(a[--cl]);
		while(cl<q[i].l) del(a[cl++]);
		while(cr>q[i].r) del(a[cr--]);
		ret[q[i].id]=deal();
	}
	for(int i=1;i<=qu;i++) printf("%lld\n",ret[i]);
	return 0;
}
```



---

## 作者：Trimsteanima (赞：4)

### Description

给定一段序列$a$，有$q$个询问，每次询问给定$l$和$r$，求$a_l..a_r$的$Huffman$编码长度。

### Solution
很明显的Huffman
核心代码

#### 哈夫曼核心代码

```cpp
while (q.size() > 1) {
        x = q.top();
        q.pop();
        x += q.top();
        q.pop();
        q.push(x);
        sum += x;
    }
```

以每个字符出现的次数为点权，边权为$1$建一棵$Huffman$树，$WPL$就是这段字符串的$Huffman$编码长度，所以可以用莫队维护每个字符出现的次数，然后建$Huffman$树，然后发现这样会$TLE$，于是可以把出现次数小于等于$sqrt(n)$次的处理掉，剩下大于$sqrt(n)$的再建$Huffman$树。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10, M = 315;
struct Node {
    int l, r, id;
} tr[N];
priority_queue<int, vector<int>, greater<int> > q;
vector<int> v;
int n, m, l, r, a[N], f[N], f1[N], aa[N], ans[N];
inline int read() {
    char ch; bool f = false; int res = 0;
    while (((ch = getchar()) < '0' || ch > '9') && ch != '-');
    if (ch == '-') f = true; else res = ch - '0';
    while ((ch = getchar()) >= '0' && ch <= '9') res = (res << 3) + (res << 1) + ch - '0';
    return f? ~res + 1 : res;
}
inline bool cmp(Node a, Node b) {
    return a.l / M == b.l / M ? a.r < b.r : a.l < b.l;
}
inline void Build (int x, int y) {
    --f[f1[x]], f1[x] += y, ++f[f1[x]];
}
inline int solve() {
    for (int i = 0; i < v.size(); i++)
        if (f1[v[i]] > M)
            q.push(f1[v[i]]);
    for (int i = 1; i <= M; i++)
        a[i] = f[i];
    int ans = 0, j = 0;
    for (int i = 1; i <= M; i++)
        if (a[i]) {
            if (j) {
                if (i + j > M) q.push(i + j); else ++a[i + j];
                --a[i], ans += i + j, j = 0;
            }
            if (a[i] & 1) --a[i], j = i;
            ans += a[i] * i;
            if ((i << 1) > M)
                for (int p = a[i] >> 1; p; --p) q.push(i << 1);
            else a[i << 1] += a[i] >> 1;
        }
    if (j)
        q.push(j);
    while (!q.empty()) {
        int x = q.top(); 
        q.pop();
        if (q.empty()) break;
        x = x + q.top();
        q.pop();
        ans += x;
        q.push(x);
    }
    return ans;
}
int main() {
    n = read();
    for (int i = 1; i <= n; i++)
        ++f1[aa[i] = read()];
    for (int i = 1; i <= N - 10; i++)
        if (f1[i] > M) v.push_back(i);
    for (int i = 1; i <= N - 10; i++)
        f1[i] = 0;
    m = read(), l = 1, r = 0;
    for (int i = 1; i <= m; i++)
        tr[i].l = read(), tr[i].r = read(), tr[i].id = i;
    std::sort(tr + 1, tr + m + 1, cmp);
    for (int i = 1; i <= m; i++) {
        while (r < tr[i].r) Build(aa[++r], 1);
        while (l > tr[i].l) Build(aa[--l], 1);
        while (r > tr[i].r) Build(aa[r--], -1);
        while (l < tr[i].l) Build(aa[l++], -1);
        ans[tr[i].id] = solve();
    }
    for (int i = 1; i <= m; i++)
        printf("%d\n", ans[i]);
    return 0;
}
```

[蒟蒻博客](https://www.cnblogs.com/wjnclln/p/11070208.html)qwq

---

