# [ABC366C] Balls and Bag Query

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc366/tasks/abc366_c

空の袋があります。 クエリが $ Q $ 個与えられるので、順番に処理してください。

クエリは次の $ 3 $ 種類です。

- `1 x` : 整数 $ x $ が書かれたボールを $ 1 $ つ袋に入れる。
- `2 x` : 整数 $ x $ が書かれたボールを $ 1 $ つ袋の中から取り出して外に捨てる。このクエリが与えられるとき、袋の中に整数 $ x $ が書かれたボールが存在することが保証される。
- `3` : 袋の中にあるボールに書かれている整数の種類数を出力する。

## 说明/提示

### 制約

- $ 1\ \leq\ Q\ \leq\ 2\ \times\ 10^{5} $
- $ 1\ \leq\ x\ \leq\ 10^{6} $
- $ 2 $ 種類目のクエリが与えられるとき、袋の中に整数 $ x $ が書かれたボールが存在する。
- $ 3 $ 種類目のクエリが $ 1 $ つ以上存在する。
- 入力はすべて整数
 
### Sample Explanation 1

はじめ、袋の中は空です。 $ 1 $ 番目のクエリ `1 3` で袋の中に $ 3 $ が書かれたボールが $ 1 $ つ入ります。 $ 2 $ 番目のクエリ `1 1` で袋の中に $ 1 $ が書かれたボールが $ 1 $ つ入ります。 $ 3 $ 番目のクエリ `1 4` で袋の中に $ 4 $ が書かれたボールが $ 1 $ つ入ります。 $ 4 $ 番目のクエリ `3` で袋の中に $ 1,\ 3,\ 4 $ の $ 3 $ 種類のボールが入っているため、$ 3 $ を出力します。 $ 5 $ 番目のクエリ `2 1` で袋の中から $ 1 $ が書かれたボールを $ 1 $ つ取り出します。 $ 6 $ 番目のクエリ `3` で袋の中に $ 3,\ 4 $ の $ 2 $ 種類のボールが入っているため、$ 2 $ を出力します。 $ 7 $ 番目のクエリ `1 5` で袋の中に $ 5 $ が書かれたボールが $ 1 $ つ入ります。 $ 8 $ 番目のクエリ `3` で袋の中に $ 3,\ 4,\ 5 $ の $ 3 $ 種類のボールが入っているため、$ 3 $ を出力します。

## 样例 #1

### 输入

```
8
1 3
1 1
1 4
3
2 1
3
1 5
3```

### 输出

```
3
2
3```

## 样例 #2

### 输入

```
8
1 2
1 2
3
2 2
1 4
1 4
2 2
3```

### 输出

```
1
1```

# 题解

## 作者：jiangruibo (赞：4)

### 思路:
首先它对应有**三个操作**，就对于操作 $1$ 和操作 $2$，你要记录每一次的情况，用一个**桶**去维护当前情况每一个数**出现的次数**，我们还需要在操作 $1$ 和操作 $2$ 中维护出**出现的不同数的数量**，就针对第一个操作如果它这个数之前**出现的次数**为 $0$，那么现在出现的不同数的数量就得多一个，同样针对第二个操作如果它这个数之前出现的次数为 $1$，那么现在出现的不同数的数量就得少一个，那么最后在操作 $3$ 输出就行了。

### 代码:

```
#include <bits/stdc++.h>
#define AK 0
#define IOI ;
#define I return
#define lowbit(x) ((x)&-(x))
#define int long long 
#define ull unsigned long long
using namespace std;

int box[1000010];
signed main()
{
	int q;
	cin>>q;
	int cnt=0;
	while(q--)
	{
		int a,x;
		cin>>a;
		if(a==1)
		{
			cin>>x;
			if(box[x]==0)
			{
				cnt++;
			}
			box[x]++;
		}
		if(a==2)
		{
			cin>>x;
			if(box[x]==1)
			{
				cnt--;
			}
			box[x]--;
		}
		if(a==3)
		{
			cout<<cnt<<endl;
		}
	}
	I AK IOI
}
/*
 */
```

---

## 作者：HeYilin (赞：2)

**题意：**

题目要求支持三种操作，插入一个元素，删除一个元素，和查询某元素还剩几个，其中保证要求删除的元素至少存在一个。

**做法：**

开一个桶就行，这里用的是 `map` 。

每次插入 $x$ 就在键 $x$ 的位置上加 $1$ 。

每次删除 $x$ 就在键 $x$ 的位置上减 $1$ 。

需要注意的是，若是一个数的值被删成 $0$ ，那么这个键值对还是存在于 `map` 里的，需要手动删除（真正的干掉）。

由于 `map` 太慢，所以一开始我打的时候就是用的 `unordered_map` 。这玩意可是要比 `map` 快好多倍，而且和 `map` 的操作基本一致，所以放心用就可以了。

**代码：**

```cpp
#include<bits/stdc++.h>
typedef long long int ll;
using namespace std;
int n,op,x;
unordered_map<int,int>mp;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(nullptr);cout.tie(nullptr);
	cin>>n;
	while(n--){
		cin>>op;
		if(op==1){
			cin>>x;
			mp[x]++;
		}
		if(op==2){
			cin>>x;
			mp[x]--;
			if(!mp[x])mp.erase(x);
		}
		if(op==3){
			cout<<mp.size()<<"\n";
		}
	}
	return 0;
}
```

---

## 作者：x1489631649 (赞：2)

### [题目链接](https://www.luogu.com.cn/problem/AT_abc366_c)
### 输入 
输入操作次数 $n(1 \le n \le 2 \times 10^5)$，然后下面 $n$ 行每行一个操作符号。
1. 当操作符号为 $1$ 时，加入一个型号为 $x$ 的小球。
2. 当操作符号为 $2$ 时，拿出一个型号为 $x$ 的小球。
3. 当操作符号为 $3$ 时，询问有多少种不同型号的小球。
### 分析
因为 $x$ 的大小很大，再乘上操作次数此时的时间复杂度已经超出了 $2 \times 10^8$，所以我们**不能通过暴力枚举**来完成这道题，然后我们就要思考此时的操作次数肯定不能化简，而可以优化的就只剩下**枚举不同型号的小球**，通过观察可以得知，我们**不需要输出每个不同型号小球的编号**，所以我们没有必要枚举小球。
1. 我们可以通过维护一个变量 $l$ 来记录不同型号小球的数量。
2. 当放入小球时，如果原来这个型号小球的数量为 $0$ 的话，我们就将 $l$ 加一。
3. 当拿出小球时，如果原来这个型号小球的数量为 $1$ 的话，我们就将 $l$ 减一。
### Code
```
#include<bits/stdc++.h>
using namespace std;
int f[1000005];
int main()
{
	int n,l=0;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int x,k;
		cin>>x;
		if(x==1)
		{
			cin>>k; 
			f[k]+=1;
			if(f[k]==1)
				l++;
		}
		else if(x==2)
		{
			cin>>k;
			f[k]--;
			if(f[k]==0)
				l--;
		}
		else cout<<l<<endl;
	}
	return 0;
}
```
### 时间复杂度
时间复杂度为 $O(n)$，显然可以通过。

---

## 作者：Malkin_Moonlight (赞：1)

# 题解：AT_abc366_c [ABC366C] Balls and Bag Query
# 0x00 思路
简单模拟题，前置知识点：桶，`set`。

我们先读入 $n$，再来个 `for` 循环，读入 $n$ 组数据，做判断，如果是 $1$ 那么就把这个数放到 `set` 里，再往桶里的这个数的位置加上 $1$。如果是 $2$，那么我们就把桶里的这个数减去 $1$，但我们需要注意，如果这个数没了，要把 `set` 里的这个数删除。如果是 $3$，那么我们直接输出 `set` 的大小就可以啦。

这里说明一下，使用 `set` 是因为 `set` 可以自动去重，我们拿 `set` 只是为了统计有多少个数字，具体某个数字的数量用桶存。
# 0x01 代码
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
using namespace std;
typedef long long ll;
#define pb emplace_back
#define endl '\n'
const ll MAXN = 1e6 + 5;
const ll MOD = 1e9 + 7;
const ll dx[] = {0, 0, 1, -1};
const ll dy[] = {1, -1, 0, 0};

ll n, op, x;
ll tong[MAXN];
set<ll> s;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> op;
		if (op == 1) {
			cin >> x;
			s.insert(x);
			tong[x]++;
		} else if (op == 2) {
			cin >> x;
			tong[x]--;
			if (tong[x] == 0) s.erase(x);
		} else if (op == 3) {
			cout << s.size() << endl;
		}
	}
	return 0;
}
```

---

## 作者：Elysian_Realme (赞：1)

## 常规思路
我们可以开一个大小为 $10^6$ 的桶，每次加入或删除时都判断是否由 $1$ 减少到 $0$，或从 $0$ 增加到 $1$，时间复杂度 $O(Q)$。

```
// Problem: C - Balls and Bag Query
// Contest: AtCoder - AtCoder Beginner Contest 366
// URL: https://atcoder.jp/contests/abc366/tasks/abc366_c
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// By：lmq
// AC Time：2024-08-12 07:57:42

#include <bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
inline void print(int x){
	static int s[20],t=0;
	do s[++t]=x%10,x/=10;while(x);
	while(t) putchar(s[t--] + '0');
}
const int N=1e6+5;
int n,ct;
int b[1000006];
signed main(){
	cin>>n;
	while(n--){
		int t=read();
		if(t==1&&++b[read()]==1)
			ct++;
		else if(t==2&&--b[read()]==0)
			ct--;
		else if(t==3)cout<<ct<<"\n";
	}
	return 0;
}
// 某一日，祂从天坠落。人们抬头仰望，于是看见了星空。
// 星月送来神的女儿，她愿成为人的伴侣。
// 长风化作她的轺车，四海落成她的园圃。鸟雀衔来善的种子，百花编织爱的颂歌。
// 她便是这样降生于世，行于大地，与人类一同长大，与世界一起发芽。
// 而今，「终焉」之时将至。
// 而今，「归去」之时已至。
// 就此告别吧，美丽的世界。
// 此后，将有「群星」闪耀，因为我如今来过。
// 此后，将有「百花」绽放，因为我从未离去。
// 请将我的箭、我的花、与我的爱，织成新生的种子，带向那枯萎的大地。
// 然后，便让它开出永恒而无瑕的…「人性之华」吧。
// 「我名为爱莉希雅……」
// 「最初的律者，人之律者。」
```

## 加强
考虑，如果此题 $x$ 的值域开到 $10^9$ 级别呢？显然，由于查询次数很少，所以我们可以先离散化，再用上面的思路来解决。

代码和上面大同小异，就不放了

## 再加强
当然这题也可以用平衡树做，每次新建节点时计数器加一，清空节点时计数器减一。

```
// Problem: C - Balls and Bag Query
// Contest: AtCoder - AtCoder Beginner Contest 366
// URL: https://atcoder.jp/contests/abc366/tasks/abc366_c
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// By：lmq
// AC Time：2024-08-12 07:57:42

#include <bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
inline void print(int x){
	static int s[20],t=0;
	do s[++t]=x%10,x/=10;while(x);
	while(t) putchar(s[t--] + '0');
}
const int N=1e6+5;
struct Splay{
	int rt,tp,num;
	int fa[N],ch[N][2];
	int ct[N],sz[N],val[N];
	int get(int x){
		return ch[fa[x]][1]==x;
	}
	void push_up(int x){
		sz[x]=ct[x]+sz[ch[x][0]]+sz[ch[x][1]];
	}
	void link(int f,int c,int k=-1){
		fa[c]=f;
		if(f){
			if(k==-1)
				ch[f][val[c]>val[f]]=c;
			else ch[f][k]=c;
		}else rt=c;
	}
	void rotate(int x){
		int y=fa[x],z=fa[y];
		int k=get(x),t=get(y);
		link(y,ch[x][k^1],k);
		link(x,y),link(z,x,t);
		push_up(y),push_up(x);
	}
	void splay(int x){
		while(fa[x]){
			int y=fa[x],z=fa[y];
			if(z)rotate(get(x)==get(y)?y:x);
			rotate(x);
		}
		rt=x;
	}
	int find(int x){
		int u=rt;
		if(!u)return rt;
		while(ch[u][x>val[u]]&&val[u]!=x)
			u=ch[u][x>val[u]];
		splay(u);
		return rt;
	}
	void insert(int x){
		int u=rt,f=0;
		while(u&&val[u]!=x){
			f=u,sz[u]++;
			u=ch[u][x>val[u]];
		}
		if(u)ct[u]++;
		else{
			num++;
			u=++tp;
			val[u]=x,sz[u]=ct[u]=1;
			link(f,u);
		}
		splay(u);
	}
	int qry_lst(int x){
		find(x);
		if(val[rt]<x)return val[rt];
		int u=ch[rt][0];
		while(ch[u][1])
			u=ch[u][1];
		return val[u];
	}
	void del(int x){
		int y=qry_lst(x);
		int u=find(x);
		if(!--ct[u]){
			num--;
			if(ch[u][0]){
				link(0,ch[u][0]);
				find(y);
				link(rt,ch[u][1],1);
			}else link(0,ch[u][1]);
		}
	}
	int size(){
		return num;
	}
}sp;
int n;
signed main(){
	cin>>n;
	while(n--){
		int t=read();
		if(t==1)
			sp.insert(read());
		else if(t==2)
			sp.del(read());
		else if(t==3)
			cout<<sp.size()<<"\n";
	}
	return 0;
}
// 某一日，祂从天坠落。人们抬头仰望，于是看见了星空。
// 星月送来神的女儿，她愿成为人的伴侣。
// 长风化作她的轺车，四海落成她的园圃。鸟雀衔来善的种子，百花编织爱的颂歌。
// 她便是这样降生于世，行于大地，与人类一同长大，与世界一起发芽。
// 而今，「终焉」之时将至。
// 而今，「归去」之时已至。
// 就此告别吧，美丽的世界。
// 此后，将有「群星」闪耀，因为我如今来过。
// 此后，将有「百花」绽放，因为我从未离去。
// 请将我的箭、我的花、与我的爱，织成新生的种子，带向那枯萎的大地。
// 然后，便让它开出永恒而无瑕的…「人性之华」吧。
// 「我名为爱莉希雅……」
// 「最初的律者，人之律者。」
```

---

## 作者：__qp__ (赞：1)

### 题面简述

你有一个空袋子。给你 $Q$ 个查询，必须按顺序处理。

有三种查询。

- `1 x`：将一个写有整数 $x$ 的球放入袋子中。
- `2 x`：从袋子中取出一个写有整数 $x$ 的球并丢弃。当给出此查询时，保证袋子中有一个写有整数 $x$ 的球。
- `3`: 打印袋中写有不同整数的球的个数。

### 思路

直接用 STL 的 `map` 模拟即可，也可用数组模拟。

```cpp
#include <iostream>
#include <map>
using namespace std;
int q;
map<int, int> a;
int main() {
    cin >> q;
    while(q--){
        int type, x;
        cin >> type;
        switch(type){
            case 1:
                cin >> x;
                a[x]++;
                break;
            case 2:
                cin >> x;
                if(a[x] > 0){
                    a[x]--;
                    if(a[x] == 0){
                        a.erase(x);
                    }
                }
                break;
            case 3:
                cout << a.size() << '\n';
                break;
            default:
                break;
        }
    }
    return 0;
}

```

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc366_c)

## 思路

看到题意是统计序列内不同数字的个数，且 $1\le x\le 10^6$，立马想到用一个桶在线统计，也就是和莫队的增加与删除函数相同的操作。只不过本题是单点改，莫队是区间改。

增加的时候把数字加入桶，如果这个桶内增加后只有一个数，那么说明这种数字是新加的，计数器 $+1$。

删除的时候把数字拿出桶，如果这个桶内删除后没数了，说明这种数字不存在了，计数器 $-1$。

每次查询时输出计数器的值即可。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll read(){
	ll k=0;bool flag=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')flag=0;c=getchar();}
	while(isdigit(c)){k=(k<<1)+(k<<3)+(c^48);c=getchar();}
	if(flag)return k;return -k;
}
const int N=1e6+10;
int n,tom[N],cnt;
signed main(){
	cin>>n;
	while(n--){
		int op=read();
		if(op==1){
			int x=read();
			if(!tom[x]++)++cnt;//等同于 ++tom[x]==1。
		}
		if(op==2){
			int x=read();
			if(!--tom[x])--cnt;
		}
		if(op==3)printf("%d\n",cnt);
	}
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/172092226)

---

## 作者：TemplateClass (赞：0)

### 题意简述

有一个空袋子，$Q$ 次操作，每次可以往里边插入（$op = 1$ 时）或删除（$op = 2$ 时）一个编号为 $x$ 的球，或查询袋子里一共有多少个不一样的球（$op = 3$ 时）。

$1 \le Q \le 2 \times 10 ^ 5$，$1 \le x \le 10 ^ 6$。

### 题解

注意到 $x$ 的数据范围并不大，我们可以开一个数组来表示这个袋子，每次将下标为 $x$ 的元素的值增加或减少即可。但这样做的话操作 $3$ 的速度会很慢。

所以我们再添加一个线段树，再该线段数中，非零元素都为 $1$，每次一个球的数量从无到有和从有到无的变化作为线段树的更改条件。这样，线段树就能通过区间求和来计算出操作 $3$ 了。

空间开得下。

```cpp
#define mid ((l + r) >> 1)

const int N = 1e6 + 1;

int nums[N], tree[N << 2], lazy[N << 2];

int x, y;
 
void pushdown(int i, int l, int r) {
    tree[i << 1] = (mid - l + 1) - tree[i << 1];
    tree[(i << 1) + 1] = (r - mid) - tree[(i << 1) + 1];
     
    lazy[i << 1] ^= 1;
    lazy[(i << 1) + 1] ^= 1;
    lazy[i] ^= 1;
}
 
int modify(int i, int l, int r) {
    if(x > r || y < l) return tree[i];
    if(x <= l && r <= y) {
        lazy[i] ^= 1;
        return tree[i] = (r - l + 1) - tree[i];
    }
     
    if(lazy[i]) pushdown(i, l, r);
     
    return tree[i] = 
        modify(i << 1, l, mid) + 
        modify((i << 1) + 1, mid + 1, r);
}
 
int query(int i, int l, int r) {
    if(x > r || y < l) return 0;
    if(x <= l && r <= y) return tree[i];
     
    if(lazy[i]) pushdown(i, l, r);
     
    return
        query(i << 1, l, mid) + 
        query((i << 1) + 1, mid + 1, r);
}

void solve(){
	int q; std::cin >> q;
	while(q--) {
		int op; std::cin >> op;
		if(op == 3) {
			x = 1, y = N - 1;
			std::cout << query(1, 1, N - 1) << "\n";
		} else {
			int p; std::cin >> p;
			if(op == 1) {
				if(nums[p]) ++nums[p];
				else {
					nums[p] = 1, x = y = p;
					modify(1, 1, N - 1);
				}
			} else {
				--nums[p];
				if(!nums[p]) {
					x = y = p;
					modify(1, 1, N - 1);
				}
			}
		}
	}
}
```

---

## 作者：ma_niu_bi (赞：0)

### 题意

有三种操作。将一个数放入口袋，将一个数拿出口袋，问口袋中有几种数。

### 思路

维护一个数组，$a_i$ 表示数 $i$ 出现的次数，维护答案 $ans$。

当加入一个数 $x$ 时，将 $a_x$ 加一。若 $x$ 是第一次出现，即 $a_x=1$，将 $ans$ 加一。

当拿出一个数 $x$ 时，将 $a_x$ 减一。若 $x$ 没有了，即 $a_x=0$，将 $ans$ 减一。

询问时输出 $ans$ 即可。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 5;
int a[N];
void solve() {
    int n, ans = 0;
    cin >> n;
    for (int i = 1; i <= n; i ++) {
        int op;
        cin >> op;
        if (op == 1) {
            int x;
            cin >> x;
            a[x] ++;
            if (a[x] == 1) ans ++;
        }
        if (op == 2) {
            int x;
            cin >> x;
            a[x] --;
            if (!a[x]) ans --;
        }
        if (op == 3) cout << ans << "\n";
    }
}
int main() {
    int T = 1;
    // cin >> T;
    while (T --) solve();
    return 0;
}
```

---

