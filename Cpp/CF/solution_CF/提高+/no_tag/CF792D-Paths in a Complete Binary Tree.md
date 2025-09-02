# Paths in a Complete Binary Tree

## 题目描述

 $ T $ is a complete binary tree consisting of $ n $ vertices. It means that exactly one vertex is a root, and each vertex is either a leaf (and doesn't have children) or an inner node (and has exactly two children). All leaves of a complete binary tree have the same depth (distance from the root). So $ n $ is a number such that $ n+1 $ is a power of $ 2 $ .

In the picture you can see a complete binary tree with $ n=15 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF792D/653f6c4875f17ae6f17eafa38c499699f6610ec9.png)Vertices are numbered from $ 1 $ to $ n $ in a special recursive way: we recursively assign numbers to all vertices from the left subtree (if current vertex is not a leaf), then assign a number to the current vertex, and then recursively assign numbers to all vertices from the right subtree (if it exists). In the picture vertices are numbered exactly using this algorithm. It is clear that for each size of a complete binary tree exists exactly one way to give numbers to all vertices. This way of numbering is called symmetric.

You have to write a program that for given $ n $ answers $ q $ queries to the tree.

Each query consists of an integer number $ u_{i} $ ( $ 1<=u_{i}<=n $ ) and a string $ s_{i} $ , where $ u_{i} $ is the number of vertex, and $ s_{i} $ represents the path starting from this vertex. String $ s_{i} $ doesn't contain any characters other than 'L', 'R' and 'U', which mean traverse to the left child, to the right child and to the parent, respectively. Characters from $ s_{i} $ have to be processed from left to right, considering that $ u_{i} $ is the vertex where the path starts. If it's impossible to process a character (for example, to go to the left child of a leaf), then you have to skip it. The answer is the number of vertex where the path represented by $ s_{i} $ ends.

For example, if $ u_{i}=4 $ and $ s_{i}= $ «UURL», then the answer is $ 10 $ .

## 样例 #1

### 输入

```
15 2
4
UURL
8
LRLLLLLLLL
```

### 输出

```
10
5
```

# 题解

## 作者：Computer1828 (赞：5)

![](https://cdn.luogu.com.cn/upload/image_hosting/jaidvqff.png)

所有节点（样例）的编号在二进制下如上图。

显然 `L` 和 `R` 操作不合法的条件是当前为叶节点，观察上图，叶节点的编号在二进制下最低位（第 $0$ 位）为 $1$。

`U` 操作不合法的条件是当前为根节点，然后又因为 $n$ 为节点数，所以根节点编号是 $\dfrac{n+1}{2}$。

设当前节点编号为 $u$，$u \texttt{ and -} u = 2^k$，观察上图。

对于 `L` 操作，新的 $u' = u \texttt{ xor } 2^k \texttt{ xor } 2^{k-1}$。

对于 `R` 操作，新的 $u' = u \texttt{ xor } 2^{k-1}$。

对于 `U` 操作，新的 $u' = u \texttt{ or } 2^{k+1} \texttt{ xor } 2^k$。

注意在用二进制写 $2^k$ 的时候要写成 `1ll<<k`。

代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n;int q;
inline ll lowbit(ll x){//其实就是找 x&-x = 2^k 的 k
	ll bt = x,ans = 0,tmp = 1;
	while(ans<61 && (bt&tmp) == 0) ans++,tmp *= 2;
	return ans;
}
int main(){
	scanf("%lld%d",&n,&q);
	ll u;char str[100005];
	while(q--){
		scanf("%lld",&u);
		scanf("%s",str);int len = strlen(str);
		//printf("%lld\n",lowbit(u));
		for(int i = 0;i<len;++i){
			ll pos = lowbit(u);
			if(str[i] == 'L'){
				if(u & 1) continue;
				u ^= (1ll<<pos);
				u ^= (1ll<<(pos-1));
			}else if(str[i] == 'R'){
				if(u & 1) continue;
				u ^= (1ll<<(pos-1));
			}else if(str[i] == 'U'){
				if((u<<1) == (n+1)) continue;
				u |= (1ll<<(pos+1));
				u ^= (1ll<<pos);
			}
		}
		printf("%lld\n",u);
	}
	return 0;
}
```

---

## 作者：zdc189 (赞：2)

### 题外话
~和 dalao 思路不太一样，水过。~

~第一次独立做出蓝题，发个题解。~

### 题意简述

给定一棵拥有 $n$ 个节点的满二叉树，第 $i$ 个节点的编号为**对这棵满二叉树做中序遍历的时间戳**。

每次询问给定一个数 $x$ 与一个字符串。字符串中的第 $i$ 位若为 $U$，表示 $x$ 要变成 $x$ 的父节点的编号；若为 $L$，则表示 $x$ 要变成其**左**孩子的编号；若为 $R$，表示 $x$ 要变成其**右**孩子的编号。如果某个字符不合法(比如当前 $x$ 为一个叶节点的编号，而这个字符却是 $L$ 或 $R$ )，就跳过这个操作。

求经过所有操作后，$x$ 的值是多少。


### DFS & 栈 & 模拟
时间复杂度：$O(n+x)$。

第一反应是一道**中序遍历**和**先序遍历**的转换。

仔细观察，这是棵**二叉搜索树（左儿子<父亲<右儿子）**。

然后再看，父亲和儿子的差，样例中：
>（第一层） $ 8-4=4 $ $ 12-8=4 $
>
>（第二层） $ 4-2=2 $ $ 6-4=2 \dots$ 
>
> （第三层） $ 2-1=1 $ $ 3-2=1 \dots $
>

发现刚好是 $2$ 倍！

于是，我们可以先 DFS 出 $ u_i$ 所在的位置，用栈记录路径，然后特判即可。

### 代码

```
#include <bits/stdc++.h>
using namespace std;
#define int long long
stack<char> st;
int dfs(int u, int step, int x) {
	if (u < x) {
		st.push('R');
		return dfs(u + step, step >> 1, x);
	}
	if (u > x) {
		st.push('L');
		return dfs(u - step, step >> 1, x);
	}
	return step;
}
string s;
int n, q;
main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n >> q;
	int root = (n + 1) >> 1, step;
	while (q -- ) {
		int u;
		while (st.size()) st.pop();
		cin >> u >> s;
		step = dfs(root, root >> 1, u);
		for (int i = 0; i < s.size(); i ++ ) {
			if (s[i] == 'L') {
				if (step == 0) continue;
				u = u - step;
				step >>= 1;
				st.push('L');
			}
			else if (s[i] == 'R') {
				if (step == 0) continue;
				u = u + step;
				step >>= 1;
				st.push('R');
			}
			else {
				if (u == root) continue;
				if (!st.size()) continue;
				if (st.top() == 'L') {
					step <<= 1;
					if (step == 0) step = 1;
					u = u + step;
				}
				else {
					step <<= 1;
					if (step == 0) step = 1;
					u = u - step;
				}
				st.pop();
			}
		}
		cout << u << '\n';
	}
	return 0;
}	
```

---

## 作者：hongshixiaobai (赞：2)

# CF792D Paths in a Complete Binary Tree 题解
[传送门](https://www.luogu.com.cn/problem/CF792D)
## 题意

给定一棵拥有 $n$ 个节点的满二叉树，第 $i$ 个节点的编号为**对这棵满二叉树做中序遍历的时间戳**。

每次询问给定一个数 $x$ 与一个字符串。字符串中的第 $i$ 位若为 $U$，表示 $x$ 要变成 $x$ 的父节点的编号；若为 $L$，则表示 $x$ 要变成其**左**孩子的编号；若为 $R$，表示 $x$ 要变成其**右**孩子的编号。如果某个字符不合法（比如当前 $x$ 为一个叶节点的编号，而这个字符却是 $L$ 或 $R$），就跳过这个操作。

求经过所有操作后，$x$ 的值是多少。

## 思路

观察可得，对于每个操作：
- `L`：`ans-=((lowbit(ans))>>1)`
- `R`：`ans+=((lowbit(ans))>>1)`
- `U`：判断当前节点是左儿子还是右儿子，逆运算即可。

其中 `lowbit()` 表示二进制最低位的值。

模拟后输出即可。

## AC 代码
```cpp
#include<bits/stdc++.h>
#define lowbit(x) x&-x
using namespace std;
long long n,q,ans,flag;
char c;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
	cin>>n>>q;
	while(q--)
	{
		cin>>ans;
		while(c != 'L'&&c != 'R'&&c != 'U')c = getchar();
		while(c == 'L'||c == 'R'||c == 'U')
		{
			if(c == 'L')ans-=((lowbit(ans))>>1);
			if(c == 'R')ans+=((lowbit(ans))>>1);
			if(c == 'U'&&ans!=(n+1>>1))
			{
				if(ans&((lowbit(ans))<<1))ans-=lowbit(ans);
				else ans+=lowbit(ans);
			}
			c = getchar();
		}
      cout<<ans<<'\n';
	}
}
```

---

## 作者：Cloud_Umbrella (赞：2)

## 分析

首先，我们用 $lowbit(x)$ 来表示 $x$ 在二进制下最低位的 $1$ 表示的值。举个栗子，十进制数 $5$ 转成二进制数是 $101$，所以 $\operatorname{lowbit}(5)=1$。然后我们结合图片一看，发现 $5$ 就是叶子结点。在一棵树中，有以下几个性质。

$1$.$\operatorname{lowbit}$ 相同的点在同一层上，也就是深度相同。$\operatorname{lowbit}$ 越大的点深度越小（反之亦然）。例如 $8$ 的 $\operatorname{lowbit}$ 是 $8$，所以在图中它是根结点。

$2$.$2\times \operatorname{lowbit}(x)=\operatorname{lowbit}(dad_x)$。表示当前结点的 $\operatorname{lowbit}$ 的两倍是其父亲结点的 $\operatorname{lowbit}$（当且仅当存在父亲结点的时候）。

$3$.$leftson_x=x-\large\frac{\operatorname{lowbit}(x)}{2}$。表示当前结点的左儿子是它减去它的 $\operatorname{lowbit}$ 的二分之一（当且仅当此结点不是叶子结点）。

$4$.$rightson_x=x+\large\frac{\operatorname{lowbit}(x)}{2}$。和性质 $3$ 类似。

$5$.$dad_x=x\pm \operatorname{lowbit}(x)$ 并且要求满足性质 $2$。

细细琢磨这 $5$ 条性质，代码就出来了。

## Code

```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
string s;
int n,T;
int lowbit(int x){return x & -x;}//利用位运算求lowbit
signed main(){
	scanf("%lld%lld",&n,&T);
	while(T--){
		int x,dadx,dady;
		scanf("%lld%s",&x,s);
		int len=s.size();
		for(int i=0;i<len;i++){
			if(s[i]=='U'){
				dadx=x+lowbit(x);//定义两个变量dadx和dady，并判断到底哪个是x的父亲
				dady=x-lowbit(x);
				if(lowbit(dadx)/2==lowbit(x) && dadx<=n) x=dadx;
				else if(lowbit(dady)/2==lowbit(x)) x=dady;
			}
			else if(s[i]=='L') x-=lowbit(x)/2;//性质3
			else x+=lowbit(x)/2;//性质4
		}
		printf("%lld\n",x);
	}
	return 0;//好习惯伴终生
}
```

---

## 作者：registerGen (赞：2)

[可能更好的阅读体验](https://registergen.github.io/post/solution-cf792d/)

# Solution

一看 $\sum |s_i|\le 10^5$，就想到可以暴力地移动 $x$，而移动后的结果可以预处理。

然而，$n\le 10^{18}$，预处理个锤子！

于是我们来找找规律：

- 当前结点编号：$2=(0010)_2$。
- 左儿子的编号：$1=(0001)_2$。
- 右儿子的编号：$3=(0011)_2$。

再来一组：

- 当前结点编号：$12=(1100)_2$。
- 左儿子的编号：$10=(1010)_2$。
- 右儿子的编号：$14=(1110)_2$。

发现什么了吗？

对于一个结点编号 $x$，设它的二进制表示中，最低的为 $1$ 的位为 $pos$（从 $0$ 开始）。则它的左儿子的编号为 $x\oplus (2^{pos}\operatorname{|}2^{pos-1})$，右儿子的编号为 $x\oplus 2^{pos-1}$。

如果 $x$ 的二进制表示中，第 $pos+1$ 位为 $1$，则它的父亲结点编号为 $x\oplus 2^{pos}$，否则为 $x\oplus (2^{pos}\operatorname{|}2^{pos+1})$。

# Code

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>

typedef long long ll;

const int N=1e5;

ll n,m;
char s[N+10];

// x 的二进制表示中第 pos 为是 0 还是 1
inline int getBit(ll x,int pos){return !((x&(1LL<<pos))==0);}

inline void L(ll& x){
	if(x&1)return; // 注意特判没有左儿子的情况
	int pos=0;
	while(pos<60&&getBit(x,pos)==0)pos++;
	x^=((1LL<<pos)|(1LL<<(pos-1)));
}

inline void R(ll& x){
	if(x&1)return; // 注意特判没有右儿子的情况
	int pos=0;
	while(pos<60&&getBit(x,pos)==0)pos++;
	x^=(1LL<<(pos-1));
}

inline void U(ll& x){
	int pos=0;
	while(pos<60&&getBit(x,pos)==0)pos++;
	if(n+1==(1LL<<(pos+1)))return; // 注意特判没有父亲的情况
	if(getBit(x,pos+1)==1)x^=(1LL<<pos);
	else x^=((1LL<<pos)|(1LL<<(pos+1)));
}

int main(){
	scanf("%lld%lld",&n,&m);
	while(m--){
		int len;
		ll x;
		scanf("%lld%s",&x,s+1);
		len=int(strlen(s+1));
		for(int i=1;i<=len;i++){
			if(s[i]=='U')U(x);
			if(s[i]=='L')L(x);
			if(s[i]=='R')R(x);
//			printf("de: %lld\n",x);
		}
		printf("%lld\n",x);
	}
	return 0;
}
```

---

## 作者：Sol1 (赞：2)

这题的话，首先看到$n \leq 10^{18}$，知道直接遍历是没逃了。不过我们可以发现一个有趣的性质：对于一个$k$层的满二叉树，第$i$层的节点编号的$lowbit$（$lowbit(x)= \arg \max 2^k|x$）等于$2^{k-i}$。此时，就可以这样遍历：

设节点编号为$x$。

如果我们遇到一个`L`：

如果此时有$lowbit(x)=1$，那么忽略这个字符。

否则，$x$更新为$x-\frac{lowbit(x)}{2}$。

如果我们遇到一个`R`：

如果此时有$lowbit(x)=1$，那么忽略这个字符。

否则，$x$更新为$x+\frac{lowbit(x)}{2}$。

如果我们遇到一个`U`：

如果$x=\frac{n+1}{2}$，那么忽略这个字符。

否则，计算$x_1=x-lowbit(x)$和$x_2=x+lowbit(x)$的$lowbit$，得到$l_1$和$l_2$。

然后判定：如果$l_1=2\times lowbit(x)$，那么$x$更新为$l_1$；否则，$x$更新为$l_2$。

实测这个方法可以通过。

```cpp
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
using namespace std;

int q;
long long n;

inline long long LowBit(long long x) {
    return x & -x;
}

long long Process(long long x, string s) {
    int len = s.length();
    for (int i = 0;i < len;i++) {
        switch (s[i]) {
            case 'L':
                if (LowBit(x) != 1) {
                    x -= LowBit(x) / 2;
                }
                break;
            case 'R':
                if (LowBit(x) != 1) {
                    x += LowBit(x) / 2;
                }
                break;
            case 'U':
                if (x != (n + 1 >> 1)) {
                    long long k1 = x + LowBit(x), k2 = x - LowBit(x);
                    if (LowBit(k1) == LowBit(x) << 1) {
                        x = k1;
                    } else {
                        x = k2;
                    }
                }
                break;
        }
    }
    return x;
}

void Solve() {
    for (int i = 1;i <= q;i++) {
        long long x;
        string s;
        scanf("%lld", &x);
        cin >> s;
        printf("%lld\n", Process(x, s));
    }
}

int main() {
    scanf("%lld%d", &n, &q);
    Solve();
    return 0;
}
```

---

## 作者：Exp10re (赞：1)

好题。

## 解题思路

记 $dep_i$ 表示标号为 $i$ 的点的深度（根节点为 $1$），$fa_i$ 表示标号为 $i$ 的点的父亲，$l_i$ 和 $r_i$ 分别表示标号为 $i$ 的点的左右儿子。

另记 $m=\log_2 (n+1)$（即最大深度）。

手玩一下注意到完全二叉树上中序遍历的编号有如下性质，其中 $x$ 表示标号为 $x$ 的点：

- $\operatorname{lowbit}(x)=2^{m-dep_x}$。

由此进行观察可以推出以下结论：

- $l_x=x-2^{m-dep_x}+2^{m-dep_{l_x}}=x-2^{m-dep_x}+2^{m-dep_x+1}$。
- $r_x=x+2^{m-dep_{r_x}}=x+2^{m-dep_x+1}$。

结合以上两个结论再手玩一下可以推出以下结论：

- $fa_x=(x\color{red}\operatorname{bitor}\color{black}2^{m-dep_x-1})-2^{m-dep_x}$。这里使用 $\operatorname{bitor}$ 是因为如果 $x$ 为右儿子的话 $x\color{red}\operatorname{bitand}\color{black}2^{m-dep_x-1}$ 是不为 $0$ 的，因此使用 $\operatorname{bitor}$。

考虑不合法的操作：一个操作 $opt$ 不合法的情况如下：

- $dep_x=1$ 且 $opt=U$。
- $dep_x=m$ 且 $opt=L,R$。

模拟操作即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,q;
long long Dep(long long x)
{
	long long l=1,r=n,mid,cnt=0;
	while(l<=r)
	{
		cnt++;
		mid=(l+r)/2;
		if(mid==x)
		{
			return cnt;
		}
		if(x<mid)
		{
			r=mid-1;
		}
		else
		{
			l=mid+1;
		}
	}
	return cnt;
}
void del(long long &x,long long dep)
{
	if(x&(1ll<<(m-dep)))
	{
		x-=(1ll<<(m-dep));
	}
	return;
}
void add(long long &x,long long dep)
{
	if(!(x&(1ll<<(m-dep))))
	{
		x+=(1ll<<(m-dep));
	}
	return;
}
int main()
{
	char c;
	long long i,j,t,dep,x,pre,pdep;
	scanf("%lld%lld",&n,&q);
	t=n+1;
	while(t>1)
	{
		m++;
		t/=2;
	}
	for(i=1;i<=q;i++)
	{
		scanf("\n%lld\n",&x);
		dep=Dep(x);
		scanf("%c",&c);
		for(;c!='\n';)
		{
			pre=x;
			pdep=dep;
			if(c=='U')
			{
				if(dep!=1)
				{
					del(x,dep);
					dep--;
					add(x,dep);
				}
			}
			if(c=='L')
			{
				if(dep!=m)
				{
					del(x,dep);
					dep++;
					add(x,dep);
				}
			}
			if(c=='R')
			{
				if(dep!=m)
				{
					dep++;
					add(x,dep);
				}
			}
			if(x<=0||x>=n+1)
			{
				x=pre;
				dep=pdep;
			}
			scanf("%c",&c);
		}
		printf("%lld\n",x);
	}
	return 0;
}
```

---

## 作者：hgzxwzf (赞：0)

### D
提供一个不用位运算的做法。

$ls_i$ 表示 $i$ 节点的左儿子的编号，$rs_i$ 表示 $i$ 节点的右儿子的编号，$h_i$ 表示 $i$ 点的深度。

如果设 $siz_i$ 表示以 $i$ 节点为根的子树内节点的个数，根据完全二叉树的性质可知，$siz_i=2^{h_i}-1$。

遍历到了 $ls_i$ 后，需要遍历完以 $rs_{ls_i}$ 为根的子树，再遍历到 $i$，所以 $i=ls_i+2^{h_i-2}$，因此 $ls_i=i-2^{h_i-2}$。

同理，$rs_i=i+2^{h_i-2}$。

首先需要得到 $x$ 点的深度（深度定义为**树高减去根到该点的简单路径经过的点的个数**）。

设 $p$ 表示当前点的编号，深度为当前的位置 $h$，显然，根节点的编号为 $\frac{n+1}{2}$，所以初始 $p=\frac{n+1}{2}$。

如果 $p=x$，那么说明 $h$ 就是 $x$ 的深度；

否则如果 $p>x$，那么说明 $x$ 在 $p$ 的左子树内，到 $ls_p$ 去。

否则，到 $rs_p$ 去。

这样可以在线性时间内求出 $x$ 的深度，同时解决了 $\verb!L!$ 操作和 $\verb!R!$，只需要解决 $\verb!U!$ 操作，如果得到了 $i$ 是 $fa_i$ 的左儿子还是右儿子，就可以得到 $fa_i$。

观察发现，$h_i$ 层中编号最小的节点是 $2^{h_i-1}$，编号第 $k$ 小的节点编号减去第 $k-1$ 小的节点编号等于 $2^{h_i}$，如果 $\frac{i-2^{h_i-1}}{2^{h_i}}$ 是奇数，则说明 $i$ 是右儿子，否则是左儿子。
```cpp
char s[N];
int c2[N];

signed main()
{
	int n,q;
	scanf("%lld%lld",&n,&q);
	int h=log2(n+1),rt=(n+1)/2;
	c2[0]=1;
	rep(i,1,h) c2[i]=c2[i-1]*2;
	while(q--)
	{
		int m,x;
		scanf("%lld %s",&x,s+1);
		m=strlen(s+1);
		int p=rt,nh=h;
		while(p!=x)
		{
			if(x>p)
			{
				p+=c2[nh-2];
			}
			else
			{
				p-=c2[nh-2];
			}
			nh--;
		}
		rep(i,1,m)
		{
			if(s[i]=='U') 
			{
				if(nh==h) continue;
				int l=c2[nh-1];
				if((x-l)/c2[nh]%2==0) x+=c2[nh-1];
				else x-=c2[nh-1];
				nh++;
			}
			else if(s[i]=='R')
			{
				if(nh==1) continue;
				x+=c2[nh-2];
				nh--;
			}
			else 
			{
				if(nh==1) continue;
				x-=c2[nh-2];
				nh--;
			}
		}
		printf("%lld\n",x);
	}
	return 0;
}
```


---

