# [ABC308G] Minimum Xor Pair Query

## 题目描述

这里有一块你可以写整数的黑板，初始黑板上什么都没有。

现在有 $q$ 个操作/询问，格式如下：

+ 操作 `1 x`：在黑板上写下一个数 $x$。
+ 操作 `2 x`：将**一个**整数 $x$ 从黑板上擦去，保证此时黑板上至少有一个整数 $x$。
+ 询问 `3`：输出黑板上任意两个整数的异或值的最小值，保证此时黑板上至少有两个数。

## 说明/提示

$1\leq q\leq 3\times 10^5,0\leq x<2^{30}$。


**对于样例 1：**

共有 9 个询问。

1. 此时黑板上有整数 $\{2\}$。
2. 此时黑板上有整数 $\{2,10\}$。
3. $2\oplus10=8$ 是黑板上最小的异或值。
4. 此时黑板上有整数 $\{2,3,10\}$。
5. $2\oplus3=1$ 是黑板上最小的异或值。
6. 此时黑板上有整数 $\{3,10\}$。
7. $3\oplus10=9$ 是黑板上最小的异或值。
8. 此时黑板上有整数 $\{3,10,10\}$。
9. $10\oplus10=0$ 是黑板上最小的异或值。

Translate by Ew_Cors.

## 样例 #1

### 输入

```
9
1 2
1 10
3
1 3
3
2 2
3
1 10
3```

### 输出

```
8
1
9
0```

# 题解

## 作者：李至擎 (赞：9)

这是一个神奇的 trie 树做法。

首先，没有删除操作的时候用 trie 你是会的，现在我们来想想怎么维护删除操作。记 $m_u$ 表示在以 $u$ 为根的子树内，任选两数异或的最小值（若凑不满两个则为无穷大），我们考虑类似线段树一样从下往上依次更新答案。

记左右儿子为 $ls,rs$，$c_u$ 表示在以 $u$ 为根的子树内有多少个数，下面开始大力分讨：

- 如果 $c_u<2$，说明凑不满两个数，$m_u=\infty$；

- 如果 $ls$ 不存在，说明我们只能从 $rs$ 转移，$m_u=m_{rs}$，$rs$ 不存在时同理；

- 如果 $\max(c_{ls},c_{rs})\ge 2$，说明我们可以选出两个数使得它们异或起来当前位为 0，这一定是最优的，故 $m_u=\min(m_{ls},m_{rs})$；

- 如果都不成立，说明一定是左右儿子中各有一个数。那我们直接对于这种子树中只有一个数的节点，记录一下这个数具体是多少，记为 $p_u$，有 $m_u=p_{ls}\oplus p_{rs}$。

时间复杂度 $O(n\log V)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ls son[u][0]
#define rs son[u][1]
using namespace std;
const int inf=1e18;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
	while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int tot=1,son[9000005][2],fa[9000005],c[9000005],m[9000005],d[9000005];
void add(int x,int k){
	int u=1;
	for(int i=29;i>=0;i--){
		int o=(x>>i)&1ll;c[u]+=k;
		if(!son[u][o])son[u][o]=++tot,fa[son[u][o]]=u;
		u=son[u][o];
	}
	c[u]+=k,m[u]=((c[u]>=2)?0:inf),d[u]=((c[u]==1)?x:0),u=fa[u];
	while(u){
		if(c[u]<2)m[u]=inf;
		else if((ls>0)+(rs>0)==1)m[u]=((ls>0)?m[ls]:m[rs]);
		else if(max(c[ls],c[rs])==1)m[u]=d[ls]^d[rs];
		else m[u]=min(m[ls],m[rs]);
		if(c[ls]+c[rs]==1)d[u]=((c[ls]==1)?d[ls]:d[rs]);
		else d[u]=0;
		u=fa[u];
	}
}
signed main(){
	int q=read();
	while(q--){
		int op=read();
		if(op==1)add(read(),1);
		else if(op==2)add(read(),-1);
		else printf("%lld\n",m[1]);
	}
	return 0;
}
```


---

## 作者：zac2010 (赞：8)

## 思路

本题的线段树分治做法显然：维护每个元素存在的时间段，然后每进入线段树的一个节点时在 Trie 树上花 $\log V$ 的时间求出已有元素与它的最小异或值，放入一个堆中。离开一个节点时在堆中删除之前加入的最小异或值。

可删除堆实际上要用两个普通堆维护，代码如下：

```cpp
struct Large_Root_Heap{
    priority_queue<ll> q, d; ll sz, s;
    void upd(){while(!d.empty() && q.top() == d.top()) d.pop(), q.pop();}
    ll top(){upd(); return q.top();}
    void ins(ll x){q.push(x), s += x, sz++;}
    void del(ll x){d.push(x), s -= x, sz--;}
} h[N];
```

------

另一个做法就是纯可重集做法，重在发现性质。

> 对于三个非负整数 $x,y,z(x < y < z)$，有 $\min(x \bigoplus y,y\bigoplus z)<x\bigoplus z$。

* 证明

  从二进制最高位开始 $i=\log V$，对 $x,y,z$ 进行如下操作：

  1. 若它们的当前位都两两相同，继续跳到下一位 `i--`。

  2. 根据三个数的大小关系，可以得到两种情况：

     1.  $x_i=0,y_i=0,z_i=1$

        显然，这时有 $x\bigoplus y<x\bigoplus z$。

     2. $x_i=0,y_i=1,z_i=1$

        有 $y\bigoplus z<x\bigoplus z$。

有了上述性质，我们只需要维护大小相邻的数的异或和就行了。

开两个可重集。可重集 $s$ 记录黑板上当前有哪些元素；另一个可重集 $ans$ 记录 $s$ 中相邻元素的异或值。

插入删除操作在维护 $s$ 的同时维护一下 $ans$ 即可。

## 代码

```cpp
#include <bits/stdc++.h>
#define L(i, a, b) for(int i = (a); i <= (b); i++)
#define R(i, a, b) for(int i = (a); i >= (b); i--)
using namespace std;
const int N = 3e5 + 10;
int q;
multiset<int> s, ans;
int main(){
	scanf("%d", &q);
	while(q--){
		int op, x; scanf("%d", &op);
		if(op == 1){
			scanf("%d", &x), s.insert(x);
			if(s.size() > 1){
				auto it = s.find(x), pre = it, nxt = it, it2 = s.end(); it2--;
				if(it == s.begin()) nxt++, ans.insert((*nxt) ^ x);
				else if(it2 == it) pre--, ans.insert((*pre) ^ x);
				else{
					pre--, nxt++, ans.erase(ans.find((*pre) ^ (*nxt)));
					ans.insert((*pre) ^ x), ans.insert((*nxt) ^ x);
				}
			}
		}
		if(op == 2){
			scanf("%d", &x);
			if(s.size() > 1){
				auto it = s.find(x), pre = it, nxt = it, it2 = s.end(); it2--;
				if(it == s.begin()) nxt++, ans.erase(ans.find((*nxt) ^ x));
				else if(it2 == it) pre--, ans.erase(ans.find((*pre) ^ x));
				else{
					pre--, nxt++, ans.insert((*pre) ^ (*nxt));
					ans.erase(ans.find((*pre) ^ x)), ans.erase(ans.find((*nxt) ^ x));
				}
			}
			s.erase(s.find(x));
		}
		if(op == 3) printf("%d\n", (*ans.begin()));
	}
	return 0;
} 
```

---

## 作者：elbissoPtImaerD (赞：5)

没意思。

一眼丁真，鉴定为 Trie。  
有删除，线段树分治一下。  
很快啊！

$\uparrow$ 学 ds 学的。$\uparrow$

不需要这样。

如果我们直接维护所有异或和那是平方级别的。  
我们需要将维护的信息规模缩小。

结合 Trie 树的做法，不难想出结论：若 $x<y<z$，那么 $\min\{x\operatorname{xor}y,y\operatorname{xor}z\}<x\operatorname{xor}z$。

从最长相同前缀的角度不难理解。

那么我们只需要维护在值域上相邻的两数异或和即可！

由于需要支持动态插入删除，求前驱后继，求最小值，我们选择 `multiset`。

具体地，考虑维护两个 `multiset`：$S_1,S_2$。  
$S_1$ 维护黑板上的数，$S_2$ 维护异或和。

每次更改，只需在 $S_1$ 找到 $x$ 的位置，对应地更改 $S_2$ 即可。

查询更容易。

注意边界的细节。

```cpp
void Solve()
{
  int q,o,x;
  for(rd(q);q--;)
  {
    rd(o);
    if(o^3)
      if(o^1) // D
      {
        rd(x);
        auto it=S_1.find(x);
        bool tg_1=it==begin(S_1),tg_2=it==sd prev(end(S_1));
        if(tg_1)
          if(tg_2);
          else S_2.erase(S_2.find(x^*sd next(it)));
        else 
          if(tg_2) S_2.erase(S_2.find(x^*sd prev(it)));
          else
          {
            int y=*sd next(it),z=*sd prev(it);
            S_2.erase(S_2.find(x^y)),S_2.erase(S_2.find(x^z)),S_2.insert(y^z);
          }
        S_1.erase(it);
      }
      else // I
      {
        rd(x);
        auto it=S_1.upper_bound(x);
        bool tg_1=it==begin(S_1),tg_2=it==end(S_1);
        if(tg_1)
          if(tg_2);
          else S_2.insert(x^*it);
        else
          if(tg_2)
          {
            int y=*sd prev(it);
            S_2.insert(x^y);
          }
          else
          {
            int y=*sd prev(it);
            S_2.erase(S_2.find(y^*it)),S_2.insert(x^*it),S_2.insert(x^y);
          }
        S_1.insert(x);
      }
    else wrt(*begin(S_2),'\n');
  }
  return;
}
```

[$\color{green}{\checkmark}$](https://atcoder.jp/contests/abc308/submissions/43907749)。

---

## 作者：EuphoricStar (赞：4)

考虑没有删除操作怎么做。可以动态维护 $ans$，新加进来一个 $x$，我们计算 $\min\limits_{y \in S} x \oplus y$。对 $S$ 建 01Trie，然后从高位往低位按位贪心，在 01Trie 上优先往与 $x$ 这一位相同的方向走，但是前提是它的子树内有数，对于 01Trie 上的每个点维护一个 $sz_u$ 表示以 $u$ 为根的子树内数的个数即可判断。

加上删除操作，容易线段树分治。对所有 $3$ 操作建线段树，把一个数有效的范围对应到线段树上 $\log$ 个区间，然后最后 dfs 一遍即可知道每个 $3$ 操作时哪些数有效。退出线段树当前结点时的撤销，就维护之前的答案，对于这个数对应的叶子到根的路径的所有点 $u$，将 $sz_u$ 减去 $1$ 即可。

时间复杂度 $O(q \log q \log V)$。

[code](https://atcoder.jp/contests/abc308/submissions/43208911)

--------

官方题解的做法挺强的。注意到对于 $x < y < z$，$\min(x \oplus y, y \oplus z) < x \oplus z$，于是我们只用维护值域相邻的数的 $\oplus$ 最小值即可。

---

## 作者：TKXZ133 (赞：2)

[Minimum Xor Pair Query](https://www.luogu.com.cn/problem/AT_abc308_g)

### 题目大意

维护一个序列，支持动态插入，删除，查询最小异或对。

### 思路分析

看到查询最小异或对首先想到 01Trie，但 01Trie 不支持删除，考虑暴力套一个线段树分治。

需要预处理出每个元素的存活区间，这里使用了 `map<int,vector<int>>`。注意，有的元素会存活到最后，需要特判。

时间复杂度为 $O(n\log n\log V)$，其中 $V$ 是值域。

这个做法有较强的可扩展性，非常无脑。

### 代码

代码非常好写，只有 2k。

```
#include <iostream>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;
const int N=300300,M=10001000;
#define inf 2147483647

int n,op,in1;
int ans[N],type[N];

map<int,vector<int>> mp;//用于预处理元素存活区间

struct Trie{//递归版 Trie
    #define c (x>>bit&1)
    int a[M][2],num[M];
    int tot;
    void insert(int p,int bit,int x){
        if(!~bit) return ;
        if(!a[p][c]) a[p][c]=++tot;
        insert(p=a[p][c],bit-1,x);
        num[p]++;
    }
    void del(int p,int bit,int x){
        if(!~bit) return ;
        del(p=a[p][c],bit-1,x);
        num[p]--;
    }
    int query(int p,int bit,int x){
        if(!~bit) return 0;
        bool f=!num[a[p][c]];
        return query(a[p][c^f],bit-1,x)+f*(1<<bit);
    }
}trie;

struct ST{//线段树
    #define mid ((l+r)>>1)
    vector<int> a[N<<2];
    void add(int p,int l,int r,int x,int y,int k){//增加元素
        if(x<=l&&r<=y){a[p].push_back(k);return ;}
        if(x<=mid) add(p<<1,l,mid,x,y,k);
        if(y>mid) add(p<<1|1,mid+1,r,x,y,k);
    }
    void dfs(int p,int l,int r,int res){//遍历全树
        for(auto it:a[p]){
            res=min(res,trie.query(0,30,it));
            trie.insert(0,30,it);
        }
        if(l==r) ans[l]=res;
        else{
            dfs(p<<1,l,mid,res);//答案下传
            dfs(p<<1|1,mid+1,r,res);
        }
        for(auto it:a[p]) trie.del(0,30,it);
    }
}tree;

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&op);
        if(op==1){
            scanf("%d",&in1);
            mp[in1].push_back(i);
        }
        if(op==2){
            scanf("%d",&in1);
            tree.add(1,1,n,mp[in1].back(),i-1,in1);
            mp[in1].pop_back();
        }
        if(op==3) type[i]=1;
    }
    for(auto it:mp)
        for(auto it2:it.second)
            tree.add(1,1,n,it2,n,it.first);//特判最后的元素
    tree.dfs(1,1,n,inf);
    for(int i=1;i<=n;i++)
        if(type[i]) cout<<ans[i]<<'\n';
    return 0;
}
```

---

## 作者：tZEROちゃん (赞：2)

本文中的集合均指可重集。

注意到异或有一个性质：

> 对于 $x, y, z(x < y < z)$，$\min\{x\ {\rm{xor}}\ y, y\ {\rm{xor}}\ z\}< x\ {\rm{xor}}\ z$。



然后就很好做了。


根据这个性质，假如这个序列是排好序的，那么答案肯定是相邻两项 $\rm xor$ 的最小值。

那我们用一个 `std::multiset` 来维护这些相邻两数的 $\rm xor$ 值，然后答案在这个 `std::multiset` 里找就可以了。

维护一个候选数的 `std::multiset`。对于插入，每次在这个集合里找到和输入数相邻的两个数，把这两个插到答案集合里，然后再从答案集合里把原来的相邻两个数的 $\rm xor$ 删掉；对于删除，我们把这个数和它相邻的数的 $\rm xor$ 从答案里删掉，注意这里有两个，一个是它和比它小的，一个是比它大的，这个可以在候选集合中二分找到，然后再把那个比它小的和那个比它大的放到答案集合里。

显然，答案就是答案集合中最小的数，即 `*answer.begin()`。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

#define rep(i, l, r) for(auto i = (l); i <= (r); ++i)
#define per(i, r, l) for(auto i = (r); i >= (l); --i)

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  #define con1 it != candidate.end()
  #define con2 it != candidate.begin()
  multiset<int> candidate, answer;
  int m; cin >> m; while (m--) {
    int C2H5OH; cin >> C2H5OH; 
    if (C2H5OH == 1) {
      int pain; cin >> pain;
      auto it = candidate.lower_bound(pain);
      if (con1) {
        answer.insert((*it) ^ pain); 
      }
      if (con2) {
        auto it2 = it; --it2;
        answer.insert((*it2) ^ pain);
      }
      if (con1 && con2) {
        auto it2 = it; --it2;
        answer.erase(answer.find((*it) ^ (*it2)));
      }
      candidate.insert(pain);
    }

    if (C2H5OH == 2) {
      int pain; cin >> pain; 
      candidate.erase(candidate.find(pain));
      auto it = candidate.lower_bound(pain);
      if (con1) {
        answer.erase(answer.find((*it) ^ pain)); 
      }
      if (con2) {
        auto it2 = it; --it2;
        answer.erase(answer.find((*it2) ^ pain)); 
      }
      if (con1 && con2) {
        auto it2 = it; --it2;
        answer.insert((*it2) ^ (*it));
      }
    }

    if (C2H5OH == 3) {
      cerr << "> "; 
      cout << *answer.begin() << '\n';
    }
  }
  return ~~(0 ^ 0);
}
```

---

## 作者：robinyqc (赞：2)

### 题意简述

可重集合 $A$ 最开始是空的。然后你需要支持三种操作：

1. 加入一个数 $x$；
2. 删除一个数 $x$（保证 $x$ 当前一定存在）；
3. 查询从集合中选两个数异或的最小值（保证当前集合中至少存在两个数）。

如果你没有看懂第三个操作的意思，可以**简单理解为**求：
$$
\min_{1\leq i<j\leq n} \{A_i\oplus A_j\}
$$
其中 $\oplus$ 表示按位异或操作。



### 解题思路

第一眼想必大家都想过 01trie 或者线性基。但是删除操作和全局询问实在是不好维护。听机房大佬说可以线段树分治 $O(n\log^2 n)$ 做，但显然这不是一个好的方法（~~而且我不会~~）。又听说一个机房大佬 01trie 类似线段树一样直接搞，很有道理，思路很简单，但是这里讲的并不是这个做法。

此题的关键其实是找到异或的一个性质：若 $x< y< z$，则 $x\oplus z> \min\{x\oplus y,y\oplus z\}$。

***

#### 证明

设 $v_n$ 表示 $v$ 在二进制表示下从低往高数第 $n+1$ 位，比如 $v_0$ 表示最低位（第一位）。

设 $x$ 和 $z$ 二进制表示下 $k+1$ 位及以后完全相同。那么第 $k$ 位，由于 $x<z$，必定满足 $x_k=0$，$z_k=1$。因此 $(x\oplus z)_k=1$ 并且 $\forall 0<j<k,(x\oplus z)_j=0$。因此 $2^k\leq x\oplus z<2^{k+1}$。

设 $x$ 和 $y$ 在 $i+1$ 位及以后相同，同理 $2^i\leq x\oplus y<2^{i+1}$；设 $y$ 和 $z$ 在 $l+1$ 位及以后相同，同理 $2^l\leq y\oplus z<2^{l+1}$。

因为 $x<y<z$，显然 $i,l\leq k$。并且，若 $y$ 第 $k$ 位为 $1$（即 $i=k$)，那么 $l<k$；若 $y$ 第 $k$ 位为 $0$（即 $l=k$)，那么 $i<k$。也就是，$(i<k)\lor (l<k)$ 恒成立。那么 $(2^{i+1}\leq 2^k)\lor (2^{l+1}\leq2^k)$ 恒成立。因为 $x\oplus y<2^{i+1}$，$y\oplus z<2^{l+1}$ 且 $2^k\leq x\oplus z$。那么不等式的放缩是可行的，$(x\oplus y< x\oplus z)\lor (y\oplus z< x\oplus z)$ 恒成立。也即 $x\oplus z> \min\{x\oplus y,y\oplus z\}$。

证毕。

***

以上的证明可能相对冗长，但是一定详细。相信你已经看懂了。

我们首先把当前存在的数排序，去重，得到一个序列 $B$，根据刚才提到的性质，发现，对于两个不相邻的数 $B_i,B_j$，显然存在：
$$
B_i\oplus B_j>\min\{B_i\oplus B_{j-1},B_{j-1}\oplus B_j\}\geq \min\{B_i\oplus B_{j-2},B_{j-2}\oplus B_{j-1},B_{j-1}\oplus B_j\}\geq\dots\geq \min_{i<k\leq j} \{B_k\oplus B_{k-1}\}
$$
也就是两个不相邻的数异或起来一定不优于某两个相邻的数异或起来！用 `set` 维护一下插入删除，这道题就被解决了！

当然，有一个码量上的优化(?)。发现 `std::set` 自带去重，插入更简单了，但是删除起来不是很方便，还容易 RE。

我们发现不去重并不影响答案：若存在不相邻的两个数相同，则必定存在相邻的相同的两个数。因此不去重，用 `multiset` 维护一下即可。可能会慢点，但绝对好写！



### 代码实现

```cpp
#include<iostream>
#include<cstdio>
#include<cctype>
#include<vector>
#include<cstring>
#include<algorithm>
#include<set>
using namespace std;

// bb 储存原始数据，xo 储存异或后的数据
multiset<int> bb,xo;

signed main() {
    ios::sync_with_stdio(false);
    int q,t,x;
    cin>>q;
    while(q--) {
        cin>>t;
        if(t==1) {
            cin>>x;
            auto it=bb.insert(x);
            if(bb.size()>=2) { // 注意各种边界！
                if(it==bb.begin()) xo.insert(*it^*next(it));
                else if(it==prev(bb.end())) xo.insert(*it^*prev(it));
                else {
                    xo.insert(*it^*next(it));
                    xo.insert(*it^*prev(it));
                    xo.erase(xo.find(*prev(it)^*next(it)));
                }
            }
        }
        else if(t==2) {
            cin>>x;
            auto it=bb.find(x);
            if(bb.size()>=2) {
                if(it==bb.begin()) xo.erase(xo.find(*it^*next(it)));
                else if(it==prev(bb.end())) xo.erase(xo.find(*it^*prev(it)));
                else {
                    xo.erase(xo.find(*it^*next(it)));
                    xo.erase(xo.find(*it^*prev(it)));
                    xo.insert(*prev(it)^*next(it));
                }
            }
            bb.erase(it);
        }
        else cout<<*xo.begin()<<endl;
    }
    return 0;
}
```



#### 题外话

[sol_1](https://atcoder.jp/contests/abc308/submissions/43157346) 和 [sol_2](https://atcoder.jp/contests/abc308/submissions/43209332) 两份提交没有任何实质上的区别，但是却差了 400ms （（（

---

## 作者：CarroT5656 (赞：1)

**题目大意**

给你一个初始为空的序列，你要支持以下操作：

* 插入一个数 $x$。

* 删除一个数 $x$。

* 查询最小的异或数对的值。

**解题思路**

对于任意非负整数 $x<y<z$，有：

> $\min{(x\oplus y,y\oplus z)}<x\oplus z$。

证明：

> 令 $k$ 为 $x$ 与 $z$ 在二进制下不同的最高位。
>
> 则 $x$ 的第 $k$ 位为 $0$，$z$ 的第 $k$ 位为 $1$。
>
> 如果 $y$ 的第 $k$ 位为 $0$，则显然有 $x\oplus y<x\oplus z$。
>
> 如果 $y$ 的第 $k$ 位为 $1$，则有 $y\oplus z<x\oplus z$。
>
> 即 $\min{(x\oplus y,y\oplus z)}<x\oplus z$。证毕。

回到原来的问题，我们就可以知道最小的异或值一定在排序后相邻的两个数之间产生。

所以就有一种方法：每次使用一个数据结构来维护整个数列，再用一个数据结构来维护相邻两个数的异或值的最值。

每次最多只会改变一个数，可以用 `multiset` 解决。

时间复杂度为 $O(q\log q)$，可以通过。

**Code**

```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 300005
#define INF 2147483647
using namespace std;
ll q;
multiset<ll> S,P;
void ins(ll x){
	S.insert(x);
	multiset<ll>::iterator it=S.find(x);
	multiset<ll>::iterator it1=it,it2=it;
	it1--,it2++;
	if(*it1!=-1&&*it2!=INF) P.erase(P.find((*it1)^(*it2)));
	if(*it1!=-1) P.insert(x^(*it1));
	if(*it2!=INF) P.insert(x^(*it2));
	return ;
}
void del(ll x){
	multiset<ll>::iterator it=S.find(x);
	multiset<ll>::iterator it1=it,it2=it;
	it1--,it2++;
	if(*it1!=-1) P.erase(P.find(x^*it1));
	if(*it2!=INF) P.erase(P.find(x^*it2));
	if(*it1!=-1&&*it2!=INF) P.insert(*it1^*it2);
	S.erase(S.find(x));
}
ll qry(){return *P.begin();}
int main(){
	S.insert(-1),S.insert(INF);
	scanf("%lld",&q);
	while(q--){
		ll opt,x;
		scanf("%lld",&opt);
		if(opt!=3) scanf("%lld",&x);
		if(opt==1) ins(x);
		else if(opt==2) del(x);
		else printf("%lld\n",qry());
	}
	return 0;
}
```

---

## 作者：ケロシ (赞：0)

# 题意

有一个可重集合，有三种操作。

1. 在集合中添加 $x$。

2. 在集合中删除 $x$。 

3. 求出集合中两个数最小的异或值。

# 解题思路

这道题有一个不是很明显的结论。

两个数最小的异或值一定在集合排序后相邻的两个值的异或。

这个不难理解，因为排完序后，相邻的两个数的高位基本相同，可以使异或尽可能小，

所以出现了用两个 $\mathrm{multiset} $ 维护的方法。

一个维护集合的数，另一个维护集合相邻两个数的异或，

这样查询就是第二的集合中最小的数，添加和删除操作都比较简单，看代码就行了。

# 代码
```cpp
#define REP(i, n) for(int i=0;i<(n);i++)
void solve() {
    int q;
    cin >> q;
    multiset<int> S, X;
    REP(i, q) {
        int opt, x;
        cin >> opt;
        if(opt == 1) {
            cin >> x;
            auto it = S.lower_bound(x);
            int l = -1, r = -1;
            if(it != S.end()) {
                X.insert(*it ^ x);
                r = *it;
            }
            if(it != S.begin()) {
                it--;
                X.insert(*it ^ x);
                l = *it;
            }
            if(l != -1 && r != -1) {
                X.erase(X.find(l ^ r));
            }
            S.insert(x);
        }
        if(opt == 2) {
            cin >> x;
            S.erase(S.find(x));
            auto it = S.lower_bound(x);
            int l = -1, r = -1;
            if(it != S.end()) {
                X.erase(X.find(*it ^ x));
                r = *it;
            }
            if(it != S.begin()) {
                it--;
                X.erase(X.find(*it ^ x));
                l = *it;
            }
            if(l != -1 && r != -1) {
                X.insert(l ^ r);
            }
        }
        if(opt == 3) {
            cout << *X.begin() << endl;
        }
    }
}
```


---

## 作者：djh0314 (赞：0)

[**传送门**](https://www.luogu.com.cn/problem/AT_abc308_g)

### 题意

有 $m$ 个操作，分三个种类：     
1. 加入 $x$。
2. 删除 $x$。
3. 在现有的数中两个数的最小的异或值的。
   
### 分析

很明显，我们的难点在于计算，    
我们可以得到这样的性质：
最小异或值，必然产生于两个相邻的数中。        

#### 证明：    

设当前的数为 $x$，与其形成的最小异或值的值为 $z$，$z$ 与 $x$ 不相邻。    
$x$ 与 $z$ 必然是从某个位置（二进制位上）（令其为 $id$ 位）开始不同，否则两个就是相同的数，也可以看做相邻。   
继续分析，必然存在某个数在 $x$ 与 $z$ 的中间，令这个数为 $y$。     
由于 $x$ 与 $z$ 是从 $id$ 位开始不同，所以他们的前几位必然都相同。   
而 $y$ 作为两个数之间的数，前几位也与其相同。      
由于 $y$ 的 $id$ 位必然为 $0$ 或 $1$，     
因此 $y$ 的 $id$ 位必然与 $x$ 或 $z$ 相同，由此 $\min \left \{ y\oplus z,y\oplus x \right \} < x \oplus z$。        
由此必然产生于两个相邻的数。

#### 至于代码，我们可以使用 set 维护。

---

