# [国家集训队] JZPSTR

## 题目描述

你要对一个字符串进行三种操作：

0. 在位置$x_i$处插入一个字符串$y_i$

1. 删除位置$[x_i, y_i)$的字符串

2. 查询位置$[x_i, y_i)$的字符串包含多少次给定的子串$z_i$

## 说明/提示

第一次操作后，字符串为894894894；

第二次操作，询问的区间为89，不包含任何894；

第三次操作，询问的区间为894894894，包含三个894；

第四次操作后，字符串为8964894894；

第五次操作，询问的区间为896489489，包含一个64；

第六次操作，询问的区间为896489489，包含一个894；

第七次操作后，字符串为894894；

第八次操作，询问的区间为894894，包含两个894。

50%的数据中，询问个数<=100 (不是操作个数)

100%的数据中，插入总长度<=2000000，任何时刻字符串长度<=1000000，插入次数<=1001，删除次数<=1000，询问的z_i的总长度<=10000

来源：2012集训队互测，by gyz

## 样例 #1

### 输入

```
8
0 0 894894894
2 0 2 894
2 0 9 894
0 2 6
2 0 9 64
2 0 9 894
1 2 6
2 0 6 894```

### 输出

```
0
3
1
1
2```

# 题解

## 作者：myee (赞：29)

---
### 引言

这题是Claris教的，说：我两三年前在bzoj做这题时，只有两个提交，一个是出题人自己交的，还有一个是~~交出题人代码的~~。

然后这道原来正解是块状链表+后缀自动机的题目被Claris用bitset暴力匹配吊打了标算。sro Claris！

---
### shift-and算法

由于懒，用的是C++自带的std::bitset。这是道黑题，其具体用法就挂个[链接](https://oi-wiki.org/lang/csl/bitset/)了。

记 $m=10$。考虑到字符集只有 $10$ 位，开 $m$ 个bitset储存各个位置，即 `std::bitset<1000005>B[10];`

对于 $0,1$ 修改操作利用位运算暴力改，复杂度大约是 $O(\frac{nm} w)$ 的。但 $0$ 操作还涉及增加串长度，不过这可以用插入总长度复杂度抛掉。

对于 $2$ 查询操作则用shift-and算法，对长度为 $l$ 的模式串C，设答案可取位对应的bitset初值为 `00011111000` 式的（仅对答案可能存在的 $[x,y)$ 赋一）的p，则反复 `p=(p<<1)&B[C[j]-'0']` 即可。把p左移就相当于把文本串右移。注意第一次不必左移。复杂度大约是 $O(\frac{nl}w)$。

---
### Code

人傻常数大，开了O2才过。

代码轻微压行，不到1KB，比较短。

```cpp
#include <bitset>
#include <stdio.h>
typedef long long llt;
typedef unsigned uint;typedef unsigned long long ullt;
typedef bool bol;typedef char chr;typedef void voi;
typedef double dbl;
std::bitset<1000005>B[10],p;chr C[1919810];
int main()
{
	uint q=0,op,num1,num2,f;scanf("%u",&q);
	while(q--)
	{
		scanf("%u%u",&op,&num1);
		if(op)
			if(op==1)
			{
				scanf("%u",&num2);
				for(uint i=0;i<10;i++)p=(B[i]>>num2)<<num2,B[i]^=((B[i]>>num1)<<num1)^(p>>(num2-num1));
			}
			else
			{
			    scanf("%u%s",&num2,C),p=std::bitset<1000005>();
                for(f=0;C[f];f++);
                p=((~p)<<num1)^((~p)<<(num2-f+1));
                for(uint j=0;j<f;j++)p=(j?(p<<1):p)&B[C[j]-'0'];
                printf("%d\n",(int)p.count());
			}
		else
		{
			scanf("%s",C);
			for(f=0;C[f];f++);
			for(uint i=0;i<10;i++)p=(B[i]>>num1)<<num1,B[i]^=p^(p<<f);
			for(uint i=0;i<f;i++)B[C[i]-'0'][num1+i]=true;
		}
	}
	return 0;
}
```
---
### 后记

第一次写黑题题解，有所勘误恳请指出。

bitset在字符串匹配上有所应用，一般不超过 $100000$ 且字符集较小的可以代替kmp。

Claris：这题究竟没有躲过暴力。

还是sro Claris！

---
### END


---

## 作者：Water_Flower (赞：5)

# [P4465 [国家集训队] JZPSTR 题解](https://www.luogu.com.cn/problem/P4465)

分块 + SAM

[博客园题解链接](https://www.cnblogs.com/water-flower/p/18874547)

### 闲话

某机房大佬在分享 SAM 时讲了这个题，用疑似就是出题人的做法。但这个题由于数据范围不大，可以直接用 bitset 屮过去，而且只有 bitset 的题解，所以几乎所有人都在用 bitset 乱搞，我甚至在提交记录里面翻了好几页，没有找到本做法。我~~作为新一代的吃食专家，~~ 为了发扬 SAM 神教神威，用该做法和此题大战约 $12$ 小时，暴写 $9$ KB 代码，终于通过了此题，故写题解纪念。

![img](https://cdn.luogu.com.cn/upload/image_hosting/z0n8iqoh.png)

## 题目描述

你要对一个字符串进行三种操作：

0. 在位置 $x_i$ 处插入一个字符串 $y_i$

1. 删除位置 $[x_i, y_i)$ 的字符串

2. 查询位置 $[x_i, y_i)$ 的字符串包含多少次给定的子串 $z_i$

## 正文

就是序列分块。先考虑怎么处理询问。

模式串 $z_i$ 在原串的区间 $[x_i,y_i)$ 中匹配成功，可以主要分为三种情况：

1. 在最左边或最右边的散块中匹配成功；

2. 在一个整块中匹配成功；

3. 这个模式串横跨了两个块，可以理解为经过了缝的情况。

   ![](https://cdn.luogu.com.cn/upload/image_hosting/k1ton72v.png)

假设模式串 $t$ 长为 $S$，块长为 $B$，块的个数为 $C$。

对于第一种，直接把散块和 $t$ 跑字符串匹配（KMP 和 SAM 均可），$O(B + S)$。

第三种情况和第一种类似，就是把缝前面的块的最后 $S - 1$ 个字符，和缝后面的块的前 $S - 1$ 个字符拼起来，然后和 $t$ 跑字符串匹配，$O(C\times S)$。

对于第二种情况，考虑在每个块内部维护 SAM，在 SAM 上和 $t$ 跑字符串匹配，$O(C \times S)$。

所以匹配一次的复杂度是 $O(B + C \times S)$。

最复杂的询问被搞定了，接下来考虑插入和删除的操作。

总体思路是用链表维护每个块。

考虑插入，找到插入位置对应的块（可以直接遍历所有块来找），把这个块分裂成两个块，然后把这个字符串分成一个一个的块插入。

考虑删除，找到左右端点对应的块，把这两个块分裂了，然后把中间的所有块踢出链表。

每次插入删除最多增加 $O(1)$ 个块，设总插入长度为 $L$，插入操作一共会产生 $O({L\over B})$ 个块。

认为 $T$，$L$，$\sum S$ 等同阶，发现把块长设为 $\sqrt L$ 的时候复杂度就是 $O(L\sqrt L)$ 的。

## 实现需要注意的地方

因为代码有点难写，所有我在这里要强调一些细节，方便读者调试和查错用。

拼接字符串可以用 STL 的 string 构造函数，`string(const string & str,string size_type n = npos)` 将 string 对象初始化为对象 str 中从位置 pos 开始的 n 个字符。用这个函数疑似会比手写快。

题目中的字符串从 $0$ 开始，左闭右开，建议一开始就决定好你维护的串要不要从 $0$ 开始，左闭右开等细节。

可能有些块的长度甚至不到模式串的长度 $S$，拼接字符串要对块长取最小值。

可能会卡空间，块内 SAM 用的数组可能需要用 vector 来存，或者使用回收节点。

如果用 SAM 来做字符串匹配，要保证本次用到的 SAM 内部数组开够了空间，如果这种 SAM 用块内封装的 SAM 来实现可能会导致数组不够。

遍历块的时候，不要冲动地写 `++` 来遍历，而应该用链表的 `nxt` 数组来遍历。

字符集是数字，不要写成处理字符集是小写字母的 SAM。

插入和删除操作，可以把分裂出来的散块拼接到要插入的串上，疑似会快一点。

询问操作，可能需要特判掉左右端点所在块相同或相邻的情况，不然处理缝的时候可能会很麻烦。

## 代码

本人第一版代码其实还是比较可读的，但是调试的时候越改越丑，最后就成了这个鬼样子，见谅一下。

我正确性调对以后就 AC 了，一发就到了最优解第一页，懒得卡常了，块长也是随便给的，卡常和霸占最优解的重任就交给众多读者吧～

```cpp
//分块SAM 神教万岁！万岁！万万岁！
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e6+6, BN=1e3, M = N / BN + 10; int B = BN - 5;// B 可调
//我的字符串编号统一从 1 开始
struct blk{
    string s;
    inline operator string() const {return s;}
    int siz, tot, lst, epd, lsz = 0;
	vector < short > f, len, lnk;
	vector < vector < short > > ch;
	void rsz(short x) {
		len.resize(x), f.resize(x), lnk.resize(x), ch.resize(x);
		for(short i = lsz; i < x; ++i) ch[i].resize(10);
		lsz = x;
	}
	//SAM 基本初始化操作
	void ins(short c) {
		short cur = ++ tot, p = lst;
		len[cur] = len[lst] + 1; 
		while(p != -1 && !ch[p][c]) ch[p][c] = cur, p = lnk[p];
		if(p == -1) lnk[cur] = 0;
		else {
			short q = ch[p][c];
			if(len[p] + 1 == len[q]) lnk[cur] = q;
			else {
				short cpy = ++ tot; 
				len[cpy] = len[p] + 1, lnk[cpy] = lnk[q], lnk[q] = lnk[cur] = cpy;
				for(short i = 0; i <= 9; ++i) ch[cpy][i] = ch[q][i];
				while(p != -1 && ch[p][c] == q) ch[p][c] = cpy,	p = lnk[p];
			}
		}
		lst = cur, f[cur] = 1;
	}//只是利用了在 SAM 上跳是 O(询问) 的优势罢了
	vector < vector < short > > edge;
	void dfs(short u) {for(auto v : edge[u]) dfs(v), f[u] += f[v];}
	void sto() {
		edge.resize(tot + 1);
		for(short i = 1; i <= tot; ++i) edge[lnk[i]].push_back(i);
		dfs(0);
		edge.clear();// of no use
	}	
	void init() {
		siz = s.size(); rsz(siz * 1.2 + 2); lnk[0] = -1, tot = 0;
		for(short i = 0; i < siz; ++i) {
			ins(s[i] ^ 48); // char is 0~9 in this problem
			if(tot >= epd - 3) epd += ((siz - i) * 1.2 + 2), rsz(min(1 * epd, siz << 1));
		}
		sto();
	}
	void clear() {
		s.clear(), f.clear(), len.clear(), lnk.clear(), ch.clear();
		siz = tot = lsz = lst = epd = 0;
	}
	short count(string t) {
		short cur = 0;
		for(char cx : t) {
			if(ch[cur][cx ^ 48]) cur = ch[cur][cx ^ 48];
			else return 0;
		}
		return f[cur];
	}//count the times of t occur in s 
}b[M * 2];
int cnt, pre[M], nxt[M], rbs[M], tp;
int nwb(const string &s) {// 加上 const & 不知道会不会快一点
	int cur = tp ? rbs[tp--] : ++ cnt;
	b[cur].s = s, b[cur].init();
	return cur;
}//卡空间的话可以改为节点回收
inline void ins(int pr, int id) {nxt[id] = nxt[pr], pre[id] = pr, pre[nxt[pr]] = id, nxt[pr] = id;}
inline void drp(int id) {nxt[pre[id]] = nxt[id], pre[nxt[id]] = pre[id]; pre[id] = nxt[id] = 0, b[id].clear(); rbs[++ tp] = id;}
int match(const string &s, const string &t) {
    int n = s.size(), m = t.size(), count = 0;
    if (m == 0 || n < m) return 0;
    vector < int > fail(m, 0);
    for (int i = 1, j = 0; i < m; ++i) {
        while (j > 0 && t[i] != t[j]) j = fail[j - 1];
        if (t[i] == t[j]) ++j;
        fail[i] = j;
    }
    for (int i = 0, j = 0; i < n; ++i) {
        while (j > 0 && s[i] != t[j]) j = fail[j - 1];
        if (s[i] == t[j]) ++ j;
        if (j == m) ++ count, j = fail[j - 1];
    }
    return count;
} // KMP
int find(int &p, int id = 0) {
	while (b[id].siz < p) p -= b[id].siz, id = nxt[id];
    return id;
}
void insert(int id, const string &s) {
	for(int i = id, n = (int)s.size() - 1, l = 0, r; l <= n; l = r + 1, i = nxt[i]) // i = cnt, not ++ i, 下面也错了
		r = min(n, l + B - 1), ins(i, nwb(string(s, l, r - l + 1)));// the third one is size
}
void add(int p, string s) { // s start from p + 1
	int id = find(p);
	if(p == b[id].siz) insert(id, s);
	else {
		int pr = pre[id];
		s = string(b[id].s, 0, p) + s + string(b[id].s, p, b[id].siz - p);
		drp(id), insert(pr, s);
	}
}//mind! str start from 0!
void del(int l, int r) { // [l, r]
	int idl = find(l), idr = find(r), p = pre[idl]; // 卡常空间
	string s = string(b[idl].s, 0, l - 1) + string(b[idr].s, r, b[idr].siz - r);
	for(int i = idl; ; ) {
		int tmp = i;
		i = nxt[i], drp(tmp); 
		if(tmp == idr) break;
	}
	insert(p, s);
}
int query(int l, int r, const string &t) {
	int S = t.size(), idl = find(l), idr = find(r);
	if(idl == idr) return match(string(b[idl].s, l - 1, r - l + 1), t);
	if(nxt[idl] == idr) return match(string(b[idl].s, l - 1, b[idl].siz - l + 1) + string(b[idr].s, 0, r), t); // 特判掉这两种情况，下面写着就更方便
	if(S <= B / 2) {
		int res = 0;
		//deal idl
			if(b[idl].siz - l >= S) res += match(string(b[idl].s, l - 1, b[idl].siz - l + 1), t);
			int tpl = max(b[idl].siz - S + 1, l - 1);
			string tmp = string(b[idl].s, tpl, b[idl].siz - tpl) + string(b[nxt[idl]].s, 0, min(b[nxt[idl]].siz, S - 1));
			res += match(tmp, t);
		//deal idr
			if(r >= S) res += match(string(b[idr].s, 0, r), t);
			tpl = max(0, b[pre[idr]].siz - S + 1);
			tmp = string(b[pre[idr]].s, tpl, b[pre[idr]].siz - tpl) + string(b[idr].s, 0, min(S - 1, r));
			res += match(tmp, t);
		
		for(int i = nxt[idl]; i != idr; i = nxt[i]) if(b[i].siz >= S) res += b[i].count(t);// wa on nxt, not ++ i
		for(int i = nxt[idl]; i != pre[idr]; i = nxt[i]) //deal the gap
			res += match(string(b[i].s, max(0, b[i].siz - S + 1), min(b[i].siz, S - 1)) + string(b[nxt[i]].s, 0, min(b[nxt[i]].siz, S - 1)), t);// re *1
		return res;
	} else {
		string s = string(b[idl].s, l - 1, b[idl].siz - l + 1);
		for(int i = nxt[idl]; i != idr; i = nxt[i]) s += b[i].s;
		s += string(b[idr].s, 0, r);
		return match(s, t);
	}
}
string s;
int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T; cin >> T;
	while(T--) {
		int op, l, r;
        cin >> op;
		if(op == 0) {
			cin >> l >> s;
			add(l, s);
		} else if(op == 1) {
            cin >> l >> r;
			del(l + 1, r);
		} else {
			cin >> l >> r >> s;
            cout << query(l + 1, r, s) << '\n';
		}
	}
	return 0;
}
```

（如果有大佬把我代码 hack 掉了，求求你直接私信我，我会悔改的！不要去艾特管理员了，谢谢你）

最后我还有一个不太成型的想法：既然 SAM 只是用来快速处理整块询问，那可不可以把这个块的询问先记录下来，然后等到销毁这个块或者等到最后处理完所有操作的时候，对这些询问串建一个 AC 自动机来统计答案。相当于把 SAM 换成离线的 AC 自动机。如果有感兴趣的同学可以尝试一下。

---

## 作者：int_R (赞：4)

[P4465 [国家集训队] JZPSTR](https://www.luogu.com.cn/problem/P4465)

[更好的阅读体验](https://www.cnblogs.com/int-R/p/P4465.html)

莪怺逺禧歡仳特噻特。

5k 爷很早以前就让我写这个 `bitset` 水题。 

在一个字符串中插入字符串，删除字符串，查询给定子串出现次数。

插入，删除，字符集大小小，$z_i$ 总长度小。这不妥妥 `bitset`！

关于 `bitset` 匹配：

我们对于每一种字符 $c$ 开一个 `bitset` $b_c$，然后将 $b_{s_i}$ 的第 $i$ 位设置为 $1$，也就是对于每种字符记录出它在 $s$ 中所有的出现位置。

对于一个字符串 $t$，与 $s$ 进行字符串匹配。我们开一个记录答案的 `bitset` $ans$，意义是每一个为 $1$ 的位都是 $t$ 在 $s$ 中的**起始位置**(有些写法是结束位置)。初始时将 $ans$ 每一位都赋值为 $1$。举个例子：

$s:abcdabacd$

$t:abcd$

$ans:1\ 1\ 1\ 1\ 1\ 1\ 1\ 1\ 1$

我们遍历 $t$ 的每一位，使 $ans\gets ans\operatorname{bitand} (b_{y_i}\operatorname{>>}i)$（字符串向左移，但是 `bitset` 中是右移）。

$s:\ \ \ \ {\color{red} a}\ b\ c\ d\ {\color{red} a}\ b\ {\color{red} a}\ c\ d$

$ans:1\ 0\ 0\ 0\ 1\ 0\ 1\ 0\ 0$

$s:\ \ \ \ {\color{red} b}\ c\ d\ a\ {\color{red} b}\ a\ c\ d$

$ans:1\ 0\ 0\ 0\ 1\ 0\ 0\ 0\ 0$

$\cdots $

最后得到的就是所有起始位置，匹配的时间复杂度是 $O(\dfrac{|s|\sum |t_i|}{\omega})$。

回到这道题上，查询操作已经迎刃而解，插入删除怎么做？多运用位运算思想。

我们定义一个全 $1$ 的 `bitest` k。

提取出 $b$ 的第 $x$ 位及以后可以表示为 `b&(k<<x)`，那同理提取出 $b$ 的第 $x$ 位以前就可以表示为 `b&(~(k<<x))`。

那么对于每个 $b_c$。

对于插入操作，提取出 $x$ 位及以后，左移 $|t|$ 位，或上 $x$ 位以前，插入的部分正常遍历处理一遍。

对于删除操作，提取出 $y$ 位及以后，右移 $y-x$ 位，或上 $x$ 位以前。

```cpp
#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<string>
#include<bitset>
using namespace std;
const int MAXN=1e6+10;
int q,n;bitset <MAXN> b[10],ans,k,r;
int main()
{
#ifdef ONLINE_JUDGE
    cin.tie(0),cout.tie(0);
    ios::sync_with_stdio(0);
#endif
    cin>>q;
    while(q--)
    {
        int opt;cin>>opt;k.set();
        if(!opt)
        {
            int x;string t;cin>>x>>t;r=~(k<<x);
            for(register int i=0;i<=9;++i)
                b[i]=((b[i]&(k<<x))<<t.size())|(b[i]&r);
            for(register int i=0;i<t.size();++i)
                b[t[i]-'0'].set(x+i);
        }
        if(opt==1)
        {
            int x,y;cin>>x>>y;r=~(k<<x);
            for(register int i=0;i<=9;++i)
                b[i]=((b[i]&(k<<y))>>(y-x))|(b[i]&r);
        }
        if(opt==2)
        {
            int x,y;string t;cin>>x>>y>>t;ans.set();
            for(register int i=0;i<t.size();++i) ans&=b[t[i]-'0']>>i;
            if(y-x<t.size()) cout<<"0\n";
            else cout<<(ans>>x).count()-(ans>>y-t.size()+1).count()<<'\n';
        }
    }
    return 0;
}
```

---

## 作者：5k_sync_closer (赞：2)

bitset 乱搞字符串匹配经典题。设原串为 $s$ 串。

维护 $p_i$ 表示 $i$ 字符的出现位置集合，这个在修改时容易用位运算做到。

考虑怎么匹配 $z$ 串。扫描 $z$ 串，设当前扫到第 $i$ 位，维护 $u$ 表示能匹配前 $i$ 位的结束位置集合。

考虑从 $i-1$ 位扫到 $i$ 位时，怎么更新 $u\gets u'$。

首先如果 $x$ 能匹配前 $i$ 位，那么 $x-1$ 一定能匹配前 $i-1$ 位，即 $x\in u'\Rightarrow x-1\in u$。

其次如果 $x$ 能匹配前 $i$ 位，那么 $s_x=z_i$，即 $x\in u'\Rightarrow x\in p_{z_i}$。

所以 $u'=\{i+1|i\in u\}\cap p_{z_i}$，更新 $u\gets u'$ 即可。容易位运算做到。

最终 $u$ 就是能匹配 $z$ 串的位置集合。

诶我怎么最优解了

```cpp
#include <bitset>
#include <cstdio>
#include <cstring>
using namespace std;
int m, o, x, y, z;
char s[1000050];
bitset<1000001> u, v, p[10];
int main()
{
    scanf("%d", &m);
    while (m--)
    {
        scanf("%d%d", &o, &x);
        switch (o)
        {
        case 0:
            scanf("%s", s + x);
            y = strlen(s + x);
            u.set();
            u <<= x;
            v = ~u;
            for (int i = 0; i < 10; ++i)
                p[i] = p[i] & v | (p[i] & u) << y;
            for (int i = x; i < x + y; ++i)
                p[s[i] - '0'].set(i);
            break;
        case 1:
            scanf("%d", &y);
            u.set();
            v = ~(u << x);
            u <<= y;
            for (int i = 0; i < 10; ++i)
                p[i] = p[i] & v | (p[i] & u) >> y - x;
            break;
        case 2:
            scanf("%d%s", &y, s);
            z = strlen(s);
            u.set();
            u = u << x & ~(u << y);
            v = p[s[0] - '0'] & u;
            for (int i = 1; i < z; ++i)
                v = v << 1 & p[s[i] - '0'];
            printf("%d\n", (v & u).count());
            break;
        }
    }
    return 0;
}
```


---

