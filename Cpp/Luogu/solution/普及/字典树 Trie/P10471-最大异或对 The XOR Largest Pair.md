# 最大异或对 The XOR Largest Pair

## 题目描述

给定 $N$ 个整数 $A_1.A_2, \cdots, A_N$ 中选出两个进行异或计算，得到的结果最大是多少？

## 说明/提示

对于所有测试数据，$1 \le N \le 10^5$，保证 $0\le A_i<2^{31}$。

## 样例 #1

### 输入

```
3
1 2 3```

### 输出

```
3```

# 题解

## 作者：Atserckcn (赞：25)

## [P10471 最大异或对 The XOR Largest Pair](https://www.luogu.com.cn/problem/P10471) 题解

#### 题目简述：

共给你 $N$​ 个整数，其中任选两数进行**异或运算**，求最大值。

#### 分析算法：

1、枚举

时间复杂度：$O(N^2)$ ，直接排除，OUT。

2、运用字典树进行枚举，具体方法在后面。

#### 知识点梳理：

1、异或：两个数进行按位异或运算，相同为 $0$，不相同为 $1$。

2、字典树：

字典树（trie 树）是一种用于实现**字符串快速检索**的多叉树结构。

trie 树的每个节点都拥有若干个字符指针，若在插入或检索字符串时扫描到一个字符 c，就沿着当前节点的 c 字符指针，走向该指针指向的节点。

#### 思路分析：

上文提到，用枚举肯定超时。

考虑运用字典树对其进行优化。

优化方法：

把每一个数字转换成二进制的 $01$ 字符串插入字典树，再依次遍历整棵字典树。

遍历的时候我们该注意什么？该选择哪一条分支遍历下去？

选择：因为异或运算是相同为 $0$，不相同为 $1$，所以我们考虑贪心，即这一位尽量为 $1$。

给一个更直观的图片，以下即为字典树，存储的是数字 $3$、$2$、$1$、$0$：（别忘了二进制转化）。

![](https://cdn.luogu.com.cn/upload/image_hosting/kqs5mf6o.png)

**~~晚上11点临时画的，画技不好勿喷~~**

#### 代码实现：

字典树的代码实现：

```cpp
struct EDGE{//结构体存字典树 
	ll son[2];
}node[MAXN];
```

没错，就这么简单。`node[p].son[t]` 表示在字典树的 $p$ 号节点的第 $t$ 个分支（$t$ 为 $0$ 或 $1$）。

将一个数字插入操作：

```cpp
void insert(ll num)//插入数字num 
{
	now=0;
	for(int i=31;i>=0;i--)//一定是i>=0!!不是i;（血泪的教训，调到了晚上11点）
	{
		t=(num>>i)&1;//取该位
		if(!node[now].son[t]) node[now].son[t]=++cnt;//创建新的字典树节点 
		now=node[now].son[t];//更新现在所处的节点 
	}
	return;
}
```

查询操作：

```cpp
ll find(ll num)//查询数字num 
{
	ans=now=0;
	for(int i=31;i>=0;i--)//一定是i>=0!!不是i;（血泪的教训，调到了晚上11点） 
	{
		t=(num>>i)&1;
		if(!node[now].son[t^1])
			now=node[now].son[t];
		else
		{
			now=node[now].son[t^1];
			ans=ans^(1<<i);
		}
	}
	return ans;
}
```

好啦，接下来主函数很简单的，直接上完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,sum,ans,now;
bool t;
const int MAXN=1e7+5;
ll a[MAXN];
struct EDGE{//结构体存字典树 
	ll son[2];
}node[MAXN];
ll cnt;
inline void read(ll &num)//快读，不会的同学可忽略 
{
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') num=-num;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		num=(num<<1)+(num<<3)+(ch-'0');
		ch=getchar();
	}
	return;
}
void insert(ll num)//插入数字num 
{
	now=0;
	for(int i=31;i>=0;i--)//一定是i>=0!!不是i;（血泪的教训，调到了晚上11点）
	{
		t=(num>>i)&1;
		if(!node[now].son[t]) node[now].son[t]=++cnt;//创建新的字典树节点 
		now=node[now].son[t];//更新现在所处的节点 
	}
	return;
}
ll find(ll num)//查询数字num 
{
	ans=now=0;
	for(int i=31;i>=0;i--)//一定是i>=0!!不是i;（血泪的教训，调到了晚上11点） 
	{
		t=(num>>i)&1;
		if(!node[now].son[t^1])
			now=node[now].son[t];
		else
		{
			now=node[now].son[t^1];
			ans=ans^(1<<i);
		}
	}
	return ans;
}
int main(){
	read(n);
	for(int i=1;i<=n;i++)
	{
		read(a[i]);
		insert(a[i]);
	}
	for(int i=1;i<=n;i++)
		sum=max(sum,find(a[i]));//打擂台 
	printf("%lld\n",sum);
	return 0;
}
```

**[AC 记录](https://www.luogu.com.cn/record/161540694)**

**附：如果你会了本题，建议去做双倍经验[P4551 最长异或路径](https://www.luogu.com.cn/problem/P4551)**

---

## 作者：xiaoshumiao (赞：12)

首先 $\mathcal O(N^2)$ 模拟肯定会 TLE。

考虑建立一棵 01 Trie（不会的人请左转 P8306）。

然后我们对于每个数，对于每个数位进行分拆（一定要从高到低，否则不一定最大）。因为异或的性质就是两位不同的时候为 $1$，否则为 $0$，所以我们尽可能的挑不一样的数位在 Trie 上往下走，这样能取到最优答案。
```cpp
#include<cstdio>
using namespace std;
const int N=1e5+10; int a[N],son[N*31][2],idx;
void insert(int x) {//Trie 插入
  int p=0;
  for(int i=30;i>=0;i--) {
    int u=(x>>i)&1;
    if(!son[p][u]) son[p][u]=++idx;
    p=son[p][u];
  }
}
int query(int x) {//如果 x 是其中一个数，求最大异或值。
  int p=0,ans=0;
  for(int i=30;i>=0;i--) {//从高到低枚举数位，类似插入
    int u=(x>>i)&1;
    if(son[p][!u]) ans=ans*2+1,p=son[p][!u];//尽量取不一样的数位，这样异或后的结果是 1
	else ans*=2,p=son[p][u];
  }
  return ans;
}
int main() {
  int n;
  scanf("%d",&n);
  for(int i=1;i<=n;i++) scanf("%d",&a[i]),insert(a[i]);
  int ans=0;
   for(int i=1;i<=n;i++)
     if(query(a[i])>ans) ans=query(a[i]);
  printf("%d",ans);
  return 0;
}
```

---

## 作者：luobotianle (赞：4)

显然，我们要将每个数转换成一个 32 位二进制数，并建立一颗 01 trie，同时枚举每一个 $a_i$，从后往前扫，尽量走不同的节点并跳到该节点上并在答案末尾添加一个 $1$，如果实在没有就走另一边并添加一个 $0$，没有节点了就更新 $ans$ 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e7+5;
ll n,a[N];
ll son[N][2],tot;
void insert(const ll &s){
	int now=0;
	for(int i=31;i>=0;i--){
		int ch=(s>>i)&1;
		if(!son[now][ch]){
			son[now][ch]=++tot;
		}
		now=son[now][ch];
	}
}
ll query(const ll &s){
	int now=0,ans=0;
	for(int i=31;i>=0;i--){
		ll ch=(s>>i)&1;
		if(!son[now][ch^1]){
			now=son[now][ch];
		}
		else{
			now=son[now][ch^1];
			ans=ans^(1<<i);
		}
	}
	return ans;
}
ll ans=0;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		insert(a[i]);
	}
	for(int i=1;i<=n;i++){
		ans=max(ans,query(a[i]));
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：StarsIntoSea_SY (赞：3)

# Solution 

前置知识：字典树。

（如果你对异或、与运算、非运算、左移右移等不熟悉，本篇题解也许会帮到你。）

## 运算类（可以直接跳过）

### 异或
异或通常使用 $\land$ 或 $\oplus$ 来表示，相同为 $0$，不同为 $1$。

![](https://cdn.luogu.com.cn/upload/image_hosting/hyevpi82.png)

### 与运算

与运算通常使用 $ \And $ 来表示，同时为 $1$ 时结果为 $1$，任意一方为 $0$ 结果为 $0$。

![](https://cdn.luogu.com.cn/upload/image_hosting/ojsf1flj.png)

### 非运算

这个就比较简单，通常使用 $!$ 来表示，表示取反。


$!$ $1=0$，$!$ $0=1$。

### 左移右移

左移通常使用 $\ll$ 来表示，右移则用 $\gg$ 来表示。

如 $ 1 \ll 2 $ 就表示把 $1$ 向左移动 $2$ 位，即 $100$ （二进制）。

$10100 \gg 3 $ 就表示把 $10100$ 向右移动 $3$ 位，即 $10$。 

## 思路

由于 $ n \le 10^5$，直接 $O(n^2)$ 暴力枚举肯定是不行的，这时候就可以依据字典树把所有数转换为二进制来解决。

我们可以把每个数转化为二进制，这样就变成了一定长度的 $01$ 二进制串，进行字典树存储。因为 $A_i $ 在 int 的范围内，可以得出每个串的长度为 $31$（虽然实际上没有那么多）。

但是如何把数转换为二进制串呢？

```cpp
for(int i=30;i>=0;i--)
		int j=x>>i&1;
```

从第一位开始，右移后再进行对 $1$ 的与运算，这样就能从高到低进行取二进制串的操作（看不懂的可以在纸上模拟算一遍）,即使数比较小，会插入一堆 $0$ ，但不会影响结果。

接着就是查询答案的操作。

考虑枚举 $A_i$ ，每一位就在字典树中查找对应的位置来判断，因为我们需要找到尽可能大的结果，所以对于每一位要找的数，就需要查找它**相反的结果**，即进行非运算的结果。因为异或运算时不同的结果为 $1$，这就类似于贪心（~~所以你会发现代码中没有异或符号~~)。

时间复杂度约 $O(kn)$ ，$k=62$ 。

代码里有说明。

# Code

```cpp
#include <stdio.h>
const int N=100005;
int n,idx=0;
int a[N],trie[N*31][2];
int max(int a,int b){return a>b?a:b;}
void insert(int x){
	int p=0;
	for(int i=30;i>=0;i--){
		int j=x>>i&1;       //从高到低位插入
		if(!trie[p][j])	trie[p][j]=++idx;
		p=trie[p][j];
	}
}
int query(int x){
	int p=0,ans=0;
	for(int i=30;i>=0;i--){
		int j=x>>i&1;   
		if(trie[p][!j]){ //非运算，找不同的
			ans+=1<<i;  //如果有就累加，这里相当于2^i，涉及到二进制转十进制运算
			p=trie[p][!j];
		}
		else p=trie[p][j];
	}
	return ans;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%d",&a[i]),insert(a[i]);
	int ans=0;
	for(int i=1;i<=n;++i)
		ans=max(ans,query(a[i]));
	printf("%d\n",ans);
}
```

---

## 作者：jiangjiangQwQ (赞：2)

### 思路
字典树的经典运用，对给定的 $n$ 个数的**二进制形式**依次插入到字典树中，最后通过查询字典树中这个数异或值最大的那个数，更新答案。根据贪心，尽量走**与当前这个数的这位二进制相反的结点**，拆分完二进制后输出结点对应的值，就是这个数匹配到的异或结果最大的那个数。
### 代码
```cpp
#include<iostream>
#include<vector>
#include<string>
#include<cstring>
#include<algorithm>
#include<cmath> 
using namespace std;
#define For(i,j,k) for(int i=j;i<=k;i++)
#define Rep(i,j,k) for(int i=j;i>=k;i--)
#define ls(c) c<<1
#define rs(c) c<<1|1
#define int long long
#define lowbit(x) ((x)&(-x))
template<typename type>
inline void read(type &x){
    x=0;bool flag(0);char ch=getchar();
    while(!isdigit(ch)) flag^=ch=='-',ch=getchar();
    while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    flag?x=-x:0;
}
template<typename type>
inline void write(type x){
    x<0?x=-x,putchar('-'):0;
    static short Stack[50],top(0);
    do Stack[++top]=x%10,x/=10;while(x);
    while(top) putchar(Stack[top--]|48);
}
inline char read(char &ch){return ch=getchar();}
inline char write(const char &ch){return putchar(ch);}
template<typename type,typename ...T>
inline void read(type &x,T&...y){read(x),read(y...);}
template<typename type,typename ...T>
inline void write(type x,T...y){write(x),putchar(' '),write(y...),sizeof...(y)^1?0:putchar('\n');}
const int N=2e6+5,Mod=1e9+7;
int n,a[N],tr[N<<2][2],idx,End[N<<2];
void insert(int x){
	int p=0;
	for(int i=32;i>=0;i--){
		int c=(x>>i)&1;
		if(!tr[p][c]) tr[p][c]=++idx;
		p=tr[p][c];
	}End[p]=x;return;
}
int query(int x){
	int p=0;
	for(int i=32;i>=0;i--){
		int c=(x>>i)&1;
		if(tr[p][1-c]) p=tr[p][1-c];
		else p=tr[p][c];
	}return End[p];
}
signed main(){
	read(n);
	For(i,1,n) read(a[i]),insert(a[i]);
	int ans=0;
	For(i,1,n) ans=max(ans,query(a[i])^a[i]);
	write(ans);
	return 0;
}
```

---

## 作者：Mystic_dragon (赞：2)

嗯？算是 01-Trie 模版题了吧。

思路就是将每个 $a_i$ 化为 $31$ 位的二进制数，对于每一位采用贪心策略，如果当前字典树节点只有一个子节点，很明显只能走下去，如果有两个子节点，就选一个和自己不同的走下去。因为只有避免和相同的数异或，才能避免互相抵消的情况，构造尽可能多的答案位 $1$，使异或和尽可能大。

比较异或和大小的过程在输入时就可以同步完成，总时间复杂度为 $O(n\log{K})$，$K$ 为数据范围上限，至于为什么是将每个数化为 $31$ 位二进制数也是数据范围的约束。


------------
```cpp
#include<bits/stdc++.h>
#include<cstdio>
using namespace std;
typedef long long i64;
i64 n;
i64 a[5000010];
i64 Trie[5000010][2];
i64 res=-1e18;
i64 tot;
void insert(i64 value){
    i64 x=0;
    for(int i=(1<<30);i;i>>=1){
        i64 a=bool(value & i);
        if (!Trie[x][a]) Trie[x][a] = ++tot;
        x=Trie[x][a];
    }
    return ;
}
i64 query(i64 value){
    i64 ans=0,x=0;
    for(int i=(1<<30);i;i>>=1){
        i64 a=bool(value & i);
        if(Trie[x][!a]){
            x=Trie[x][!a];
            ans=(ans<<1) + !a;
        }else{
            x=Trie[x][a];
            ans=(ans<<1) + a;
        }
    }
    return ans;
}
int main(){
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>a[i];
        insert(a[i]);
        i64 value=query(a[i]);
        res=max(res,a[i] ^ value);
    }
    cout << res;
    return 0;
}
```


------------
附上双倍经验:

[P4551 最长异或路径](https://www.luogu.com.cn/problem/P4551)


------------
部分语言参考深进字典树一章。

---

## 作者：Lele_Programmer (赞：1)

# P10471 题解

## 思路

对于每一个数字，把它转换成二进制的形式，采用贪心的思路，为了使异或值最大，那么在枚举一个数的二进制位的时候，遇到 $0$ 则尽量寻找 $1$，使得异或值为 $1$，遇到 $1$ 就找 $0$，如果无法找到上述情况，则按照已存在的另一条边走。

为了方便，把每个数字转换成二进制后都补成刚好 $32$ 位的形式，除去第一个数之外，其余每个数在插入之前都搜一遍，求最大值即可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N=3500005;
const int M=2;

int n;
int tr[N][M];
int tot;
int ans;

void insert(string s) {
    int u=0;
    for (int i=0;i<s.size();++i) {
        int c=s[i]-'0';
        if (!tr[u][c]) tr[u][c]=++tot;
        u=tr[u][c];
    }
}

int query(string s) {
    int u=0;
    int ans=0;
    for (int i=0;i<s.size();++i) {
        int c=s[i]-'0';
        if (tr[u][c^1]) {
            u=tr[u][c^1];
            ans<<=1;
            ans|=1;
        } else {
            u=tr[u][c];
            ans<<=1;
        }
    }
    return ans;
}

int main() {
    scanf("%d",&n);
    for (int i=1;i<=n;++i) {
        int k;
        scanf("%d",&k);
        string s;
        while (k) {
            s.push_back((k&1)+'0');
            k>>=1;
        }
        while (s.size()<32) s.push_back('0');
        reverse(s.begin(),s.end());
        if (i!=1) ans=max(ans,query(s));
        insert(s);
    }
    printf("%d",ans);
    return 0;
}
```

---

## 作者：wwxxbb (赞：1)

## 题意

>  给定 $n$ 个整数 $a_1.a_2, \cdots, a_n$ 中选出两个进行异或计算，问得到的结果最大是多少。

## 思路

我们先从暴力讲起，先枚举 $n$ 个数，再枚举 $n$ 个数算一下取个最大值。

发现一开始的枚举是省略不去的，即我们需要 $\mathcal{O}(n\log{n})$ 的做法。

考虑异或的性质，两个相同的数异或起来的值为零。假如我们选了一个数，将它转成 $31$ 位二进制数，要想让与另一个数的异或值最大，就要从最高位开始，**尽可能的让这个数的在二进制下的每一位都与枚举的数不同**，如果不能满足，那就相同。

那么怎么实现呢？用 Trie 维护每个数的二进制位，建字典树，剩下的就是模版了。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 100010, M = N * 31;

int n, a[N];
int son[M][2], idx;

void insert(int x) {
    int p = 0;
    for (int i = 31; ~i; i--) { // ~i 等价于 i >= 0
        int &s = son[p][x >> i & 1]; // x >> i & 1 表示这个数二进制下第 i 位的数
        if (!s) s = ++idx;
        p = s;
    }
}

int query(int x) {
    int p = 0, res = 0;
    for (int i = 31; ~i; i--) {
        int bit = x >> i & 1;
        if (son[p][!bit]) { // 如果有不一样的就跳
            res += 1 << i; // 加上贡献
            p = son[p][!bit];
        } else p = son[p][bit]; // 没有满足的就跳到一样的上面
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        insert(a[i]);
    }

    int ans = INT_MIN;
    for (int i = 1; i <= n; i++) 
        ans = max(ans, query(a[i]));
    return cout << ans, 0;
}
```

推荐一下y总的[视频](https://www.acwing.com/video/63/)，讲得更好。

---

## 作者：Clique (赞：1)

考虑使用 $01$-Trie 进行解题。我们从左到右枚举需要选的第一个数，在已经插入的数中按照高位到低位的顺序在 Trie 上查找，如果有一个位存在与查询数不同的情况，那么将答案加上这一位对应的二进制数；在查询之后再将该数插入 Trie 即可。

以及本题数据范围有错误，实际值域可能 $>n$，需要注意。

参考代码（GNU C++14）：

```cpp
#include <bits/stdc++.h>
using namespace std;
class trie {
private:
    int B;
    vector<array<int, 2>> S;

public:
    trie(int b) { B = b, S = {{-1, -1}}; }
    inline void insert(int x) {
        for (int i = B - 1, p = 0; ~i; i--) {
            int b = x >> i & 1;
            if (~S[p][b])
                p = S[p][b];
            else {
                p = S[p][b] = S.size();
                S.push_back({-1, -1});
            }
        }
    }
    inline int max_xor(int x) {
        int c = 0;
        for (int i = B - 1, p = 0; ~i; i--) {
            int b = x >> i & 1;
            if (~S[p][!b])
                c |= 1 << i, p = S[p][!b];
            else
                p = S[p][b];
        }
        return c;
    }
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, c = 0;
    cin >> n;
    vector<int> a(n);
    trie t(31);
    for (auto &i : a)
        cin >> i, t.insert(i);
    for (int i : a)
        c = max(c, t.max_xor(i));
    cout << c << endl;
    return 0;
}
```

---

## 作者：leiaxiwo (赞：1)

# 题解：P10471 最大异或对 The XOR Largest Pair
## 字典树（模板）
### [传送门](https://www.luogu.com.cn/problem/P10471)
### 题意分析
此题题目给的比较明显，给定 $a_1\sim a_n$，求 $\max a_i \operatorname{xor} a_j$，其中 $1\le i \le j  \le n$；

我们考虑用字典树完成此题。

显然，我们有个简单的贪心策略。

每个数转换成一个 $32$ 位二进制数，并建立一颗 01 trie，同时枚举每一个 $a_i$；

尽量走不同的节点并跳到该节点上并在答案末尾添加一个 $1$，如果实在没有就走另一边并添加一个 $0$，没有节点了就更新 $ans$。
### 代码部分
#### Trie 结构体
```cpp
struct __Trie{
	void insert(const int &x){
	int p=0;
	for(int i=31;i>=0;i--){
		int y=(x>>i)&1;
		if(!trie[p][y]){
			trie[p][y]=++tot;
		}
		p=trie[p][y];
	}
	return ;
    }
    int query(const int &x){
	    int p=0,ans=0;
	    for(int i=31;i>=0;i--){
		    int y=(x>>i)&1;
		    if(!trie[p][y^1]){
		 	    p=trie[p][y];
		    }
		    else{
			    p=trie[p][y^1];
			    ans=ans^(1<<i);
		    }
     	}
    	return ans;
    }
}liver_trie;
```
#### 主函数
```cpp
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",&A[i]);
		liver_trie.insert(A[i]);
	}
	for(int i=1;i<=n;i++){
		ans=max(ans,liver_trie.query(A[i]));
	}
	printf("%lld",ans);
	return 0;
}
```
#### 完整参考代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1e7+5;
int n,tot,ans;
int A[maxn],trie[maxn][2];
struct __Trie{
	void insert(const int &x){
	int p=0;
	for(int i=31;i>=0;i--){
		int y=(x>>i)&1;
		if(!trie[p][y]){
			trie[p][y]=++tot;
		}
		p=trie[p][y];
	}
	return ;
    }
    int query(const int &x){
	    int p=0,ans=0;
	    for(int i=31;i>=0;i--){
		    int y=(x>>i)&1;
		    if(!trie[p][y^1]){
		 	    p=trie[p][y];
		    }
		    else{
			    p=trie[p][y^1];
			    ans=ans^(1<<i);
		    }
     	}
    	return ans;
    }
}liver_trie;
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",&A[i]);
		liver_trie.insert(A[i]);
	}
	for(int i=1;i<=n;i++){
		ans=max(ans,liver_trie.query(A[i]));
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：HasNoName (赞：1)

### 思路

考虑字典树。

将每个数的二进制按从高到低存储起来。

对于每一个数，如果高位能让异或值为 $1$ 则一定最优。

因为如果是 $0$ 就算后面全部都是 $1$ 也没有高位异或值为 $1$ 的更大。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100005;
int son[20*N][2],idx,a[N];//Trie树
string get(int x)//将整数转化成二进制字符串
{
    string s,t;
    for(int i=1;i<=35;i++)
    {
        s+=char((x&1)+'0');
        x>>=1;
    }
    for(int i=0;i<35;i++)
        t+=s[35-1-i];
    return t;
}
void myin(string s)//插入字符串
{
    int c=0;
    for(int i=0;i<35;i++)
    {
        int t=s[i]-'0';
        if(!son[c][t])
            son[c][t]=++idx;
        c=son[c][t];
    }
}
int xormax(string s)//用贪心思想得到答案
{
    int c=0,ans=0;
    for(int i=0;i<35;i++)
    {
        int t=s[i]-'0';
        if(son[c][!t])
        {
            c=son[c][!t];
            ans+=1<<(35-i-1);
        }
        else
        {
            c=son[c][t];
        }
    }
    return ans;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        myin(get(a[i]));
    }
    int maxn=0;
    for(int i=1;i<=n;i++)
    {
        maxn=max(maxn,xormax(get(a[i])));
    }
    cout<<maxn<<'\n';
    return 0;
}
```

---

## 作者：Tomle (赞：0)

# 思路

二进制 01 字典树模板题。

将 $A_i$ 都以二进制的形式存入字典树中。

存入方法与普通字典树类似，考虑到本题的特殊性，在结束位置存 $cnt$ 表示**这个点代表什么数字**。

当 $A_{1\sim i-1}$ 都已加入字典树中，可以通过以下步骤求出 $\max\limits_{1\le j \lt i}\{A_i\bigoplus A_j\}$：
- 输入 $A_i$。
- 从根出发，分别取 $A_i$ 的 $0\sim31$ 二进制位取反为 $r$（`int r = a[i] >> k - 1 & 1 ^ 1;`，取反：$0$ 变 $1$，$1$ 变 $0$），如果能走这一条路，就走这条路（$r$），否则走另一条路（$r\bigoplus1$）。
- 返回当前节点的 $cnt$。
- 用 $A_i$ 异或返回值，就是 $\max\limits_{1\le j \lt i}\{A_i\bigoplus A_j\}$。
- 最后不要忘记插入 $A_i$。

然后将 $n$ 次查询的结果取最大值，就是答案。

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, t[3100005][2], cnt[2000005], tot, a[100005], ans;

void read(int &a, int ch = 0) {
	while (!isdigit(ch = getchar()));
	for (a = 0; isdigit(ch); ch = getchar()) a = (a << 3) + (a << 1) + (ch ^ 48);
}
int query(int n) {
	int p = 0;
	for (int i = 31; i >= 0; i--) {
		if (t[p][n >> i & 1 ^ 1]) p = t[p][n >> i & 1 ^ 1];
		else p = t[p][n >> i & 1];
	}
	return cnt[p];
}
void insert(int n) {
	int p = 0;
	for (int i = 31; i >= 0; i--) {
		if (!t[p][n >> i & 1]) t[p][n >> i & 1] = ++tot;
		p = t[p][n >> i & 1];
	}
	cnt[p] = n;
}
int main() {
	read(n);
	for (int i = 1; i <= n; i++) {
		read(a[i]);
		if (i > 1) ans = max(ans, a[i] ^ query(a[i]));
		insert(a[i]);
	}
	cout << ans;
	return 0;
}
```

---

## 作者：sansesantongshun (赞：0)

~~大水题~~
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100005],ans=0;
int main()
{
	cin>>n;
	for (int i=1;i<=n;++i)
	{
		scanf("%d",&a[i]);
		for (int j=1;j<i;++j)
		ans=max(ans,a[i]^a[j]);
	}
	cout<<ans;
}
```
显然这个算法答案是正确的，但是这个时间复杂度不对，遇到大数据直接 T 飞。

那么正解是什么呢？

我们发现外层的枚举是避免不了的，而我们需要做的，是在较短时间内求出一个数对于一些数的最大异或和。

这里可以使用 01 trie 来做，我们需要把数按照二进制分成 $30$ 位，依次插入字典树中。查询的话，按照二进制从高位到低位枚举，如果有和这位不一样的数，就把答案加上这一位，否则直接从这位跳过，不累加答案。

当输入一个数时，先查询这个数和之前的数的最大异或和，然后插入这个数。

这样就能通过本题了。

AC 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m=-1,a[35],num,x,cnt=0,aans,ans=0;
bool k;
struct node
{
	int next[2];
} trie[10000005];//01trie
int main()
{
	cin>>n;
	m=30;
	a[0]=1;
	for (int i=1;i<=m;++i)
	a[i]=a[i-1]<<1;//预处理倍增数组
	cin>>num;
	x=0;
	for (int i=m;i>=0;--i)
	{
		k=num&a[i];
		trie[x].next[k]=++cnt;
		x=trie[x].next[k];
	}//先插入一个数
	for (int i=1;i<n;++i)
	{
		scanf("%d",&num);
		x=0;
		aans=0;
		for (int j=m;j>=0;--j)
		{
			k=num&a[j];
			if (trie[x].next[!k])//有不一样的数
			{
				x=trie[x].next[!k];
				aans|=a[j];//累加答案
			}
			else
			x=trie[x].next[k];//跳过
		}//查询最大异或和
		ans=max(ans,aans);
		x=0;
		for (int j=m;j>=0;--j)
		{
			k=num&a[j];
			if (trie[x].next[k]==0)
			trie[x].next[k]=++cnt;
			x=trie[x].next[k];
		}//插入
	}
	cout<<ans;
}
```

---

## 作者：Melo_qwq (赞：0)

01 trie 板子。
 
#  题目大意

略。

刚开始数组开到 $10^5$ 直接 RE 了，然后看到了[这篇帖子](https://www.luogu.com.cn/discuss/822263)，才知道题目又锅了，乐。

# 题目实现

根据上面帖子的实际范围，我们要开 $31$ 位的二进制数建 trie。

考虑一个贪心，根据异或的定义（我们假设当前的数是 $a$），那么我们要想找到最大的 $b$ 使得 $a\oplus b$ 最大，那么我们尽量让 $b$ 的每一位和 $a$ 都不同，然后在树上跑就行。

关于数据范围：本人卡到了 $3\times10^6$。但是建议开大一点。

## 代码

```cpp
#include <bits/stdc++.h>
#define rep(i ,m ,n ,x) for (int i = (m) ;i <= (n) ;i += (x))
using namespace std ;
#define int long long
const int N = 3e6 + 7 ;
int n ,a[N] ,son[N][2] ,maxx = LONG_LONG_MIN ,tot ;
namespace shin {
	template <typename T> inline void read (T &x) {
		x = 0 ;
		char ch = getchar () ;
		while (! isdigit (ch)) {
			ch = getchar () ;
		}
		while (isdigit (ch)) {
			x = (x << 1) + (x << 3) + (ch xor 48) ;
			ch = getchar () ;
		}
	}
	inline void insert (int a) {
		int x = 0 ;
		for (int i = (1 << 30) ;i ;i >>= 1) {
			int f = bool (a & i) ;
			if (! son[x][f]) son[x][f] = ++ tot ;
			x = son[x][f] ;
		}
	}
	inline int find (int a) {
		int x = 0 ,ans = 0 ;
		for (int i = (1 << 30) ;i ;i >>= 1) {
			int f = bool (a & i) ;
			if (son[x][! f]) {
				x = son[x][! f] ;
				ans = (ans << 1) + (! f) ;
			}
			else {
				x = son[x][f] ;
				ans = (ans << 1) + f ;
			}
		}
		return ans ;
	}
}
signed main () {
	shin :: read (n) ;
	rep (i ,1 ,n ,1) {
		shin :: read (a[i]) ;
		shin :: insert (a[i]) ;
		int a2 = shin :: find (a[i]) ;
		maxx = max (maxx ,a[i] xor a2) ;
	}
	cout << maxx << '\n' ;
	return 0 ;
}
//kafka & かみや & やえみこ
```

---

## 作者：CNS_5t0_0r2 (赞：0)

两两枚举肯定是很慢的，这里我们采取这么一个贪心策略：

我们需要最高位尽可能多的 $1$。

所以，我们枚举 $a_i$，然后使用 01-Trie，每次查找当前是否存在第 $i$ 位相反的节点，如果有，跳到这个节点上并将答案末尾添加一个 $1$；否则跳到另一个节点上并将答案末尾添加一个 $0$。

这部分代码长这样：

```cpp
int query(int x){
	int u = 0,ans = 0;
	for(int i = 31;i >= 0;i--){
		int c = (x >> i) & 1;
		if(trie[u].child[!c]){
			u = trie[u].child[!c];
			ans = (ans << 1) | 1;
		}
		else{
			u = trie[u].child[c];
			ans <<= 1;
		}
	}
	return ans;
}
```

### 完整代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 9,M = 32,K = N * M;
struct node{
    int child[2];//所有子节点，编号为i的子节点表示字符对应的ASCII码编号 
} trie[K];
int node_cnt;//节点总数
int n,a[N],ans;
void insert(int x){//插入
    int u = 0;//u表示当前节点的指针，从空节点0开始 
    for(int i = 31;i >= 0;i--){
        int c = (x >> i) & 1;
        if(!trie[u].child[c])//如果节点不存在
            trie[u].child[c] = ++node_cnt;//新建节点
        u = trie[u].child[c];//指向子节点
    }
}
int query(int x){
	int u = 0,ans = 0;
	for(int i = 31;i >= 0;i--){
		int c = (x >> i) & 1;
		if(trie[u].child[!c]){
			u = trie[u].child[!c];
			ans = (ans << 1) | 1;
		}
		else{
			u = trie[u].child[c];
			ans <<= 1;
		}
	}
	return ans;
}
int main(){
	scanf("%d", &n);
	for(int i = 1;i <= n;i++){
		scanf("%d", &a[i]);
		insert(a[i]);
	}
	for(int i = 1;i <= n;i++)
		ans = max(ans,query(a[i]));
	printf("%d",ans);
	return 0;
}
```

---

## 作者：Chenyichen0420 (赞：0)

## 思路分析

看到数据范围，想时间复杂度：$O(kn)$ 或者 $O(n\log n)$。

像这种东西，不太可能带 $\log$，毕竟是异或，排序不大可能有用。

这时，我们注意到，一个数只需要往前找，不需要往后找，因为后面的单向奔赴就够了。能快速地找到最匹配（能使其最大）的项就成了关键。

我们可以想到用 01trie。将每个数查询后存入其中（注意数据范围，这里存 $20$ 位就够）。查询时，将每一位取反进行查询。如果这一位没有就将就一下向另一个方向先走，毕竟有总比没有好。

复杂度 $O(kn)$，$k<100$。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, a[3100001], ans;
int tri[3100001][2], k;
inline void get(int val) {
	bitset<31>vl; register int pos = 0;
	vl.reset(); vl = val;
	for (register int i = 30; i >= 0; i--) {
		if (!tri[pos][vl[i]]) tri[pos][vl[i]] = ++k;
		pos = tri[pos][vl[i]];
	}
}
inline int retv(int val) {
	bitset<31>vl; int pos = 0, as = 0;
	vl.reset(); vl = val;
	register int ws = log2(val);
	for (register int i = ws; i >= 0; i--) vl[i] = 1 - vl[i];
	for (register int i = 30; i >= 0; i--) {
		if (!tri[pos][vl[i]]) vl[i] = 1 - vl[i];
		pos = tri[pos][vl[i]];
	}
	for (register int i = 0; i <= 30; ++i) as += vl[i] * (1 << i);
	return as;
}
int main() {
	ios::sync_with_stdio(0);
	cin >> n;
	for (register int i = 1; i <= n; ++i)
		cin >> a[i],
		get(a[i]);
	for (register int i = 1; i <= n; ++i)
		ans = max(ans, a[i] ^ retv(a[i]));
	cout << ans << endl;
	return 0;
}
```

---

## 作者：__Sky__Dream__ (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/P10471)

## 题目大意
给定一对数，使得异或值最大。

## 解题思路
异或运算**按位进行且不进位**，可以想到转化为二进制数进行操作，对每一位分别处理。

把每个整数看做长度为 $32$ 的 $01$ 串构建字典树，最低位为字典树的叶子结点。对于数 $a_i$，在字典树中检索一次，每次都尝试沿着“与 $a_i$ 当前位相反的字符”向下访问。若存在这样的字符指针，令答案加上当前位代表的二进制数即可。由于二进制下第 $i$ 位比第 $0$ 位到第 $i-1$ 位之和都大，所以保证了贪心正确。

**注意数组大小开 $N$ 的 $32$ 倍。**

## AC Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int ans,n,sum=1,tree[N<<5][2];
void yh1(int x)
{
    int y,p=1;
    for(int i=31;i>=0;i--)
	{
        y=(x>>i)&1;
        if(!tree[p][y]) tree[p][y]=++sum;
        p=tree[p][y];
    }
}
int yh2(int x)
{
    int y,p=1,res=0;
    for(int i=31;i>=0;i--)
	{
        y=((x>>i)&1)^1;
        if(tree[p][y]) res+=(1<<i),p=tree[p][y];
        else p=tree[p][y^1];
        if(!p) break;
    }
    return res;
}
int main()
{
    cin>>n;
    int x;
    for(int i=1;i<=n;i++)
	{
        cin>>x;
        ans=max(ans,yh2(x));
        yh1(x);
    }
    cout<<ans;
    return 0;
}
```

拜拜！

---

