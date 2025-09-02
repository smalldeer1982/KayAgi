# 出会いと別れ

## 题目描述

[problemUrl]: https://atcoder.jp/contests/zone2021/tasks/zone2021_f

あなたは、スタートアップの新製品として全ての惑星間を行き来出来るようなワープゲートを構築しようとしています。  
 惑星が $ N $ 個あり、$ 0 $ から $ N\ -\ 1 $ までの番号がついています。ここで、ある整数 $ n $ が存在して、$ N\ =\ 2^n $ です。これらの惑星の間を高速に移動するために、$ 2 $ 惑星間を瞬時に移動出来るワープゲートを $ N\ -\ 1 $ 個作成し、全ての惑星間を行き来出来るようなゲート網を作りたいです。しかし、星同士には相性があり、相性が悪い惑星間にはワープゲートを作ることが出来ません。  
 具体的には、相性の悪い惑星は数列 $ A\ =\ (A_1,\ A_2,\ \dots,\ A_M) $ で表され、ある整数 $ i $ が存在して $ a\ \mathrm{xor}\ b\ =\ A_i $ である場合、かつそのときに限り惑星 $ a $ と惑星 $ b $ の間にワープゲートを作ることが出来ません。   
 全ての惑星間を行き来できるようなゲート網を作ることができるか判定し、できる場合は $ N\ -\ 1 $ 個のワープゲートの作り方を求めてください。

 $ \mathrm{xor} $ とは 整数 $ a,\ b $ のビットごとの排他的論理和 $ a\ \mathrm{xor}\ b $ は、以下のように定義されます。

- $ a\ \mathrm{xor}\ b $ を二進表記した際の $ 2^k $ ($ k\ \geq\ 0 $) の位の数は、$ a,\ b $ を二進表記した際の $ 2^k $ の位の数のうち一方のみが $ 1 $ であれば $ 1 $、そうでなければ $ 0 $ である。
 
 例えば、$ 3\ \mathrm{xor}\ 5\ =\ 6 $ となります (二進表記すると: $ 011\ \mathrm{xor}\ 101\ =\ 110 $)。

## 说明/提示

### ストーリー

梯子を登りきり UFO に入ると、そこには捕らえられたムーアと、恐ろしい形相の宇宙人が待ち構えていた。 しかしそれ以上に、見覚えのある缶がうずたかく積まれているのが目に留まった。 間違いない。あれは間違いなく ZONe mad\_hacker ver.1.0.0 だ。 そして mad\_hacker を飲んでいるということは、この宇宙人も別の星で MADHACKING に勤しむエンジニアに違いない、と俺は確信した。 勉強会で初めての相手に話しかける時の如く、俺はやや緊張しながら口を開いた。  
 「...foo」  
 聞くや否や、宇宙人の目が輝いた。  
 「...bar!」

「fizz!」「buzz!」  
 ハッカーたちの魂が、星を超えて交わった。 すっかり意気投合した俺たちは、それぞれの星の言語やプログラミングパラダイムについて一晩中語り明かした。 気に入られ、その場でスカウトされた俺は地球人として初のミルキーウェイ(天の川)のスタートアップで働くことになったのだった。 さようなら、地球。ありがとう、ZONe mad\_hacker。そして、hello, space!

### 制約

- 入力は全て整数
- $ 1\ <\ = n\ <\ =\ 18 $ を満たす整数 $ n $ が存在して、$ N\ =\ 2^n $
- $ 0\ <\ = M\ <\ = N\ -\ 1 $
- $ 0\ <\ A_1\ <\ A_2\ <\ \dots\ <\ A_M\ <\ N $

### Sample Explanation 1

$ 1\ \mathrm{xor}\ 0\ =\ 1,\ 1\ \mathrm{xor}\ 3\ =\ 2,\ 0\ \mathrm{xor}\ 2\ =\ 2 $ であるためワープゲートを作ることができ、$ N\ -\ 1 $ 個のワープゲートで全ての惑星間を行き来できるようになっているので、正解となります。 正解となる出力は他にも多数あります。

## 样例 #1

### 输入

```
4 1
3```

### 输出

```
1 0
1 3
0 2```

## 样例 #2

### 输入

```
8 0```

### 输出

```
1 0
1 3
1 5
6 7
6 4
6 2
3 2```

## 样例 #3

### 输入

```
8 7
1 2 3 4 5 6 7```

### 输出

```
-1```

# 题解

## 作者：Register_int (赞：4)

先判断是否有解。不妨以 $0$ 为生成树的根。$0$ 与 $u$ 联通，当且仅当存在一条路径 $0\to u_1\to u_2\to\cdots\to u_k\to u$。也即 $0\oplus u_1,u_1\oplus u_2,\cdots,u_k\oplus u$。都不在 $A$ 内。容易发现这些数异或起来为 $u$，所以能得到 $0$ 与 $u$ 联通的充要条件：

- 存在一些不属于 $A$ 中的自然数，使得他们的异或和为 $u$。

暴力将不属于 $A$ 的数建线性基即可。若线性基能组成的数不满 $n$，则说明无解。

然后考虑如何构造答案。此时已经得到了线性基，而我们希望构造出一条链，而每次只改动一个二进制位来遍历所有点。容易想到格雷码，就做完了。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 1 << 18;

int p[18], b[18], cnt; bool vis[MAXN];

inline 
void insert(int x) {
	for (int i = 17, k = x; ~i; i--) {
		if (~k >> i & 1) continue;
		if (!p[i]) { p[i] = k, b[i] = x, cnt++; break; } k ^= p[i];
	}
}

int n, m, u, v;

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1, x; i <= m; i++) scanf("%d", &x), vis[x] = 1;
	for (int i = 1; i < n; i++) if (!vis[i]) insert(i);
	if (cnt != __lg(n)) return puts("-1"), 0;
	for (int i = 1; i < n; i++) v = u ^ b[__lg(i & -i)], printf("%d %d\n", u, v), u = v;
}
```

---

## 作者：cosf (赞：2)

## [Zone2021F](https://www.luogu.com.cn/problem/AT_zone2021_f)

第一眼：不会。第二眼：线性基板子。

我们对 $\{1, 2, \dots, N\} - A$ 求一个线性基 $b_0, \dots, b_{n-1}$，并且记录 $b_0, \dots, b_{n-1}$ 分别是由什么数推出来的（$o_0, \dots, o_{n - 1}$）。

具体的，我们给线性基加数的函数是长这样：

```cpp
void add(int x)
{
    int ox = x;
    // ...
    b[i] = x;
    o[i] = ox;
    // ...
}
```

那么，如果有 $b_i$ 是空的，原图就连不成树。

反之，对于所有 $0 \lt i \le N$，假设 $i$ 的最高位为第 $l_i$ 位，则让 $i$ 连向 $i \oplus o_{l_i}$。这样连一定是对的。

正确性证明（反证法）：假设 $i$ 由 $f_i = i\oplus o_{l_i}$ 异或 $o_{l_i}$ 得来（$o_{l_i}$ 不一定小于 $i$）。若 $f_i$ 又由 $i$ 异或得来，由线性基性质，有 $f_i$ 一定由 $i$ 异或 $o_{l_i}$ 得来，因为 $o_{l_i}$ 不可能表示为其他的 $o$ 的异或和。那么，有 $l_{f_i} = l_i$，即 $f_i$ 与 $i$ 位数相等。但 $l_{o_{l_i}}$ 显然不会小于 $l_i$，所以 $i \oplus o_{l_i}$ 的位数不可能为 $l_i$，即 $l_{f_i} \not= l_i$，矛盾。

## 代码

```cpp
#include <iostream>
using namespace std;

#define MAXN 20

int n, m;

int base[MAXN];
int ob[MAXN];

int l = 1;

void add(int x)
{
	int ox = x;
	for (int i = l - 1; ~i; i--)
	{
		if ((x & (1 << i)))
		{
			if (!base[i])
			{
				base[i] = x;
				ob[i] = ox;
				return;
			}
			else
			{
				x ^= base[i];
			}
		}
	}
}

int query(int x)
{
	for (int i = l - 1; ~i; i--)
	{
		if ((x & (1 << i)))
		{
			return x ^ ob[i];
		}
	}
	return 114514;
}

bool aa[1 << MAXN];

int main()
{
	cin >> n >> m;
	while ((1 << l) < n)
	{
		l++;
	}
	for (int i = 1; i <= m; i++)
	{
		int a;
		cin >> a;
		aa[a] = true;
	}
	for (int i = 1; i < n; i++)
	{
		if (!aa[i])
		{
			add(i);
		}
	}
	for (int i = 0; i < l; i++)
	{
		if (!base[i])
		{
			cout << -1 << endl;
			return 0;
		}
	}
	for (int i = 1; i < n; i++)
	{
		cout << i << ' ' << query(i) << endl;
	}
	return 0;
}

```


---

## 作者：xie_lzh (赞：1)

给一个不要线性基的做法。

注意到一个结论，若对于一个不在 $A$ 中的数，它能连边，则它可以使连通块个数除以 $2$。

证明是简单的。

我们观察加边的过程，若我们已经加入了一些边，则现在已经有了一些连通块。若我们此时加入了边 $(a,b)$ 则我们发现对于一个之前考虑过的不在 $A$ 中的数 $x$，边 $(a\ \mathrm{xor}\ x,b\ \mathrm{xor}\ x)$ 没有意义，因为我们以及考虑过同个连通块的 $(a,b)$ 了。由此发现我们只需要对于每个连通块考虑一个点即可。

继续观察，我们发现联通块具有相似性。具体而言，若对于一个连通块，我们枚举到的不再 $A$ 中的 $x$ 可以使其连出一条边，则其他所有连通块均可连出一条边。

由此我们可以得出做法：枚举不在 $A$ 中的数，尝试加边，维护连通块，由于每次不能加边时可以直接判掉，能加边时连通块个数除以 $2$ 则枚举连通块的总复杂度时线性的。

整体复杂度为 $\Theta(n\times \alpha(n))$ 瓶颈在并查集。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+5;
int n,m,a[N],fa[N],cnt;
bool vis[N],rvis;
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
#define pii pair<int,int>
pii ans[N];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=m;i++) cin>>a[i],vis[a[i]]=1;
    vector<int> vec;
    // n=(1<<n);
    for(int i=0;i<n;i++) vec.push_back(i);
    iota(fa,fa+n,0);
    for(int i=1;i<n;i++)
    {
        if(!vis[i])
        {
            if(find(vec[0])==find(vec[0]^i)) continue;
            for(int p:vec)
            {
                if(find(p^i)!=find(p))
                    ans[++cnt]={p,p^i},fa[find(p^i)]=find(p);
            }
            for(int i=0;i<vec.size();i++)
            {
                if(find(vec[i])!=vec[i])
                {
                    swap(vec[i],vec.back());
                    vec.pop_back();
                    i--;
                }
            }
        }
    }
    if(vec.size()==1)
        for(int i=1;i<=cnt;i++)
            cout<<ans[i].first<<' '<<ans[i].second<<'\n';
    else cout<<"-1\n";
}

```

---

## 作者：Ming_dao (赞：0)

**思路：线性基**

考虑枚举所有点的异或是不可行的，但是题目只需要判断和给出一组答案，显然考虑用线性基。

如果线性基无法满足从最高位到最低为都有可以异或的数，显然输出 $-1$。

考虑构造答案。

只需要记录所找的数的最大位上异或的数的原数，并将其异或即可。

**代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
//线性基

#define N 19
const int maxn=1<<19;

int p[N];
int frm[maxn];
int a[maxn];
int cnt=0;

void add(int x){
	int orn=x;
	for(int i=N;~i;i--){
		if(x&(1<<i)){
			if(!p[i]){
				cnt++;
				p[i]=x;
				frm[i]=orn;
				return;
			}
			else x^=p[i];
		}
	}
}

int query(int x){
	for(int i=N;~i;i--){
		if(x&(1<<i)){
			return x^frm[i];
		}
	}
}

inline int read(){
	int r(0),w(1);char ch;
	while(ch=getchar(),ch>=58 || ch<=47)w=(ch=='-'?-1:1);r=(r<<3)+(r<<1)+ch-48;
	while(ch=getchar(),ch<=57 && ch>=48)r=(r<<3)+(r<<1)+ch-48;
	return r*w;
}

int main(){
	int n=read(),m=read();
	for(int i=1;i<=m;i++){int in=read();a[in]=1;}
	for(int i=0;i<n;i++)if(!a[i])add(i);
	if(cnt!=__lg(n)){cout<<"-1";return 0;}
	for(int i=1;i<n;i++)cout<<i<<" "<<query(i)<<'\n';
	return 0;
}
```

---

## 作者：wflhx2011 (赞：0)

多个数异或，不难想到线性基，[模版](https://www.luogu.com.cn/problem/P3812)在这里。

[线性基性质及思路代码](https://www.cnblogs.com/ereoth/p/17535552.html)

线性基模版学会之后，这道题其实相当于板子题，首先，如果给定数列的线性基不能组成所有数，代表有的不能加入，一定无解。

否则，就在这个数和这个数为 $1$ 的最高位的原数连一条路。

赛时试了几组样例观察出来的，~~证明真的不会~~，去看
[这篇题解](https://www.luogu.com.cn/article/trljqk0b)吧。

代码就是这样：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[1<<19],p[1<<19],pos[1<<19],cnt[1<<19],ans,n,m,x;
void ins(long long x) 
{
	long long k=x;
	for(int i=19;i>=0;i--) 
	{
		if(!(x&(1ll<<i))) 
			continue;
		if(!p[i])
		{
			p[i]=x;
			pos[i]=k;
			break;
		}
		x^=p[i];
	}
}
long long ch(long long x)
{
	for(int i=19;~i;i--)
		if(x&(1ll<<i))
			return x^pos[i];
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		cin>>a[i];
		cnt[a[i]]++;
	}
	for(int i=1;i<n;i++)
		if(!cnt[i])
			ins(i);
	for(int i=19;i>=0;i--)
		if((1<<i)<=n)
		{
			x=i;
			break;		
		}
	for(int i=0;i<x;i++)
		if(!p[i])
		{
			cout<<-1;
			return 0;
		}
	for(int i=1;i<n;i++)
		cout<<i<<" "<<ch(i)<<endl;
	return 0;
}
```

---

## 作者：Crazyouth (赞：0)

## 分析

注意到本题与异或有关，并且涉及到关于很多个数的异或结果，想到线性基。把 $1\sim N$ 除 $a_i$ 之外的全部加入线性基，并且存下线性基 $p_i$ 的“原 $x$”$ori_i$，于是如果存在线性基没有值，输出 $-1$，因为这代表有岛连不上。否则输出它和它最大的位数上的原 $x$。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1<<19;
int cnt[N],p[N],ori[N];
void insert(int x)
{
	int tp=x;
	for(int i=19;~i;i--)
	{
		if(x&(1<<i))
		{
			if(!p[i])
			{
				p[i]=x;
				ori[i]=tp;
				return;
			}
			else x^=p[i];
		}
	}
}
int check(int x)
{
	for(int i=19;~i;i--)
	{
		if(x&(1<<i))
		{
			return x^ori[i];
		}
	}
}
int main()
{
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		int x;
		cin>>x;
		cnt[x]++;
	}
	for(int i=1;i<n;i++) if(!cnt[i]) {insert(i);}
	int l;
	for(int i=19;~i;i--) if((1<<i)<=n)
	{
		l=i;
		break;
	}
	for(int i=0;i<l;i++) if(!p[i])
	{
		cout<<-1;
		return 0;
	}
	for(int i=1;i<n;i++) cout<<i<<' '<<check(i)<<endl;
	return 0;
}

---

## 作者：251Sec (赞：0)

首先令 $A \gets \complement_{U}A$，其中 $U = \{x \in \mathbb{Z}|0 \le x < N\}$。这样我们就得到了异或为哪些值的边是可以连的。那么显然地存在一种方案使得图连通当且仅当集合 $A$ 的秩为 $n$。这是容易 $O(Nn)$ 求的。

考虑如何构造方案，只要除了 $0$ 以外，每个点都往外连一条边且不存在环即可。考虑把每个数看成线性基的组合作为一个新的二进制数，例如若线性基集合为 $\{3,1\}$，则我们把二进制数 $10$ 看作 $11$，因为它等于 $1 \oplus 3$，二进制数 $11$ 则是 $10$，因为它等于 $3$。

这样转化之后，我们直接将每个数往它将转化后任何一位 $1$ 变成 $0$ 后的数的原数连边（这里代码实现选择了最高位），这样显然不存在环，因为所有边都是按转化后的值从大到小连的。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, m, lg;
bool v[263005];
int f[18], g[18];
int main() {
	scanf("%d%d", &n, &m), lg = __lg(n);
	for (int i = 1, w; i <= m; i++) scanf("%d", &w), v[w] = true;
	for (int i = 0; i < n; i++) {
		if (v[i]) continue;
		int w = i;
		for (int j = lg - 1; ~j; j--) {
			if (!(w >> j & 1)) continue;
			if (f[j]) w ^= f[j];
			else { f[j] = w, g[j] = i; break; } 
		}
	}
	for (int i = 0; i < lg; i++) if (!f[i]) return puts("-1"), 0;
	for (int i = 1; i < n; i++) printf("%d %d\n", i, i ^ g[__lg(i)]);
	return 0;
}
```

---

## 作者：Inexistented (赞：0)

## 题目意思

有 $N$ 个节点 ，从 $0$ 到 $N-1$ 编号。有 $M$ 个递增正整数 $A_i$ ，如果两个节点 $u$ ，$v$ 满足 $ u\ \mathrm{xor}\ v\ =\ a_i$ ，则这两个节点之间没有连边，否则就是有边。

判断这个无向图是否连通：

如果是，请给出一棵最小生成树。

如果不是，输出 $-1$ 。

## 解析

我们可以把构造出的一个树看出以 $0$ 为根节点的树 ， $ 0\ \mathrm{xor}\ i\ =\ i$ ，所以被异或出来的和要包含所有的 $0-i$ 这个路径。

所以，此线性基题的有解情况为 $[1,N)$ 满秩。

线性基里的数字可以凑出 $1\sim2^n-1$ 的所有数字，当然也可以凑出对应的原数。

最后保留那些边权为“原数”的边，剩下的图也仍然连通。

构造可以使用的方法很多，你可以使用并查集，也可以使用我~~作者偷懒，并不想搞个并查集，于是随便乱写~~的方法。

## 代码
```c
#include <bits/stdc++.h>
using namespace std;

int main()
{
	int i,j,n,m;
	
	cin>>n>>m;
	
	vector<int> a(m),b,c;
	
	for(auto && v:a)
	{
		cin>>v;
	} 
	
	for(i=0,j=0;i<n;i++)
	{
		while(j<m && a[j]<i)
		{
			j++;
		}
		
		if(j<m && a[j]==i)
		{
			j++;
			continue;
		}
		
		int v=i;
		
		for(auto && e:c)
		{
			v=min(v,v^e);
		}
		if(v)
		{
			b.push_back(i);
            c.push_back(v);
		}
	}
	
	if(__lg(n)!=b.size())
	{
		cout<<"-1"<<endl;
		return 0;
	}
	
	int XOR=0;
	
	for(i=1;i<n;i++)
	{
		cout<<XOR<<' ';
		
		XOR^=b[__lg(i&-i)];
		
		cout<<XOR<<'\n';
	}
}
```

总结：~~作者真的太蒻了，不仅CE还WA了~~还算较水的蓝题。

---

