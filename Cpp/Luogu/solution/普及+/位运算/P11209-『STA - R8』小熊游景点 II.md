# 『STA - R8』小熊游景点 II

## 题目描述

给定序列 $\{a_n\},\{b_n\}$，有 $m$ 次询问，

每次询问给定 $k$，求 $\sum\limits_{i=1}^n[(a_i\oplus k)\le b_i]$，其中 $\oplus$ 是按位异或。

**本题部分测试点强制在线。**

## 说明/提示

**本题采用捆绑测试。**

| Subtask | $n,m$ | $a_i,b_i,k$ | $T$ | 分数 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| $1$ | $\le 10^3$ | $<2^{30}$ | $=1$ | $10$ |
| $2$ | $\le 5\times 10^5$ | $<2^{10}$ | $=1$ | $10$ |
| $3$ | $\le 5\times 10^5$ | $<2^{30}$ | $=0$ | $40$ |
| $4$ | $\le 5\times 10^5$ | $<2^{30}$ | $=1$ | $40$ |

对于 $100\%$ 的数据，$1\le n,m\le 5\times 10^5$，$0\le a_i,b_i,k<2^{30}$，$T\in\{0,1\}$。

## 样例 #1

### 输入

```
1 1 1
1
1
1```

### 输出

```
1```

## 样例 #2

### 输入

```
0 5 5
3 1 4 0 2
3 7 2 5 1
0
2
3
5
7```

### 输出

```
3
4
4
3
1```

## 样例 #3

### 输入

```
1 5 5
3 1 4 0 2
3 7 2 5 1
0
1
7
1
4```

### 输出

```
3
4
4
3
1```

# 题解

## 作者：Solwek (赞：18)

## 题意：
给定长度为 $n$ 的序列 $a,b$。

一共 $q$ 次询问，每次询问给定 $k$，你需要输出有多少 $i$ 满足 $a_i \oplus k\le b_i$。

## 题解：
对于异或问题，考虑字典树。

我们把关于 $a_i$ 和 $b_i$ 的 $k$ 放到字典树上，考虑 $k$ 在什么情况下会使得满足条件。

从高到低枚举位，

- 前 $j-1$ 位都一样，并且第 $j$ 位的 $b_i$ 是 $1$
  
我们发现只要 $k$ 与 $a_i$ 异或值为 $0$ 便一定满足条件，那么可以对这个节点打一个 $+1$ 的标记，只要询问的 $k$ 经过这里，那么就一定会产生这个贡献，并且已经不用再往下深入了，因为只要到了这个点就有贡献，与子树无关。

但是还要考虑如果这位的 $k$ 与 $a_i$ 异或也为 $1$ 的话那么就还需要继续考虑后面的位数，继续去看其他的节点是否可行。

-  前 $j-1$ 位都一样，并且第 $j$ 位的 $b_i$ 位是 $0$

那么此时只有当异或值位 $0$ 时才有可能能产生贡献，而异或值为 $1$ 时则一定不行，所以只需要考虑 $0$ 的情况即可。

并且我们需要对最后移位特判，因为等于这种情况也是可行的。

对于查询只需要按照 $k$ 的二进制从上往下走一遍将打的标记加起来就行了。


### 当 $a_i=0111$ 和 $b_i=0101$ 时举个例子。

- 对于最高位，只有 $k$ 这位等于 $0$ 才可能产生贡献，所以只建立一个 $0$ 的节点。
![](https://cdn.luogu.com.cn/upload/image_hosting/r1r9dlmz.png)

- 对于第二位，当 $k$ 这位等于 $1$ 时一定可行，所以在 $1$ 那里 $+1$。当 $k$ 这位等于 $0$ 时也可能可行，所以也要建立一个节点。
![](https://cdn.luogu.com.cn/upload/image_hosting/cevbr2w0.png)


- 对于第三位，只有 $k$ 这位等于 $1$ 时可能可行，所以往 $1$ 建立节点。
![](https://cdn.luogu.com.cn/upload/image_hosting/kw7hcy24.png)


- 对于最后一位，我们发现 $k$ 这位等于 $0$ 或 $1$ 都能产生贡献，所以都打一个 $+1$ 的标记。
![](https://cdn.luogu.com.cn/upload/image_hosting/5k8l0sgp.png)

当 $k=15$ 时，$ans=0$。
![](https://cdn.luogu.com.cn/upload/image_hosting/q0zyyevm.png)

当 $k=7$ 时，$ans=1$。
![](https://cdn.luogu.com.cn/upload/image_hosting/0dj3c9te.png)

当 $k=2$ 时，$ans=1$。
![](https://cdn.luogu.com.cn/upload/image_hosting/z87a6o3g.png)

## 复杂度：
建立节点时我们最多只会往一边去建立节点，所以是 $\log$ 的，而查询时也是只会走 $\log$ 层的，所以时间复杂度 $O(n\log v)$。

## code:
```cpp
#include<bits/stdc++.h>
using namespace std;

int tot;
int a[500010],b[500010];
struct Tree{
	int ch[2],val;
	Tree(){
		memset(ch,0,sizeof(ch));
	}
}tr[16000010];
int f=0;
void insert(int x,int y){
	int p=0;
	for(int i=31;i>=0;i--){
		int k1=(x>>i)&1,k2=(y>>i)&1,q;
		if(i==0){
			if(k2==0){
				q=k1;
				if(tr[p].ch[q]==0)
					tr[p].ch[q]=++tot;
				tr[tr[p].ch[q]].val++;	
			}else{
				q=k1;
				if(tr[p].ch[q]==0)
					tr[p].ch[q]=++tot;
				tr[tr[p].ch[q]].val++;	
				q=k1^1;
				if(tr[p].ch[q]==0)
					tr[p].ch[q]=++tot;
				tr[tr[p].ch[q]].val++;	
			}
			
			continue;
		}
		if(k2==1){
			q=k1;
			if(tr[p].ch[q]==0)
				tr[p].ch[q]=++tot;
			tr[tr[p].ch[q]].val++;
			q=k1^1;
			if(tr[p].ch[q]==0)
				tr[p].ch[q]=++tot;
			p=tr[p].ch[q];
		}else{
			q=k1;
			if(tr[p].ch[q]==0)
				tr[p].ch[q]=++tot;
			p=tr[p].ch[q];
		}
	}
}
int query(int x){
	int p=0,ans=0;
	for(int i=31;i>=0;i--){
		int q=(x>>i)&1;
		if(tr[p].ch[q])ans+=tr[tr[p].ch[q]].val,p=tr[p].ch[q];
		else break;
	}
	return ans;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int T,n,q;
	cin>>T>>n>>q;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)cin>>b[i],insert(a[i],b[i]);
	int lst=0;
	while(q--){
		int k;
		cin>>k;
		k=k^(lst*T);
		lst=query(k);
		cout<<lst<<'\n';
	}
	return 0;
} 
```

---

## 作者：jijidawang (赞：10)

在 0-1 Trie 上依次插入每个 $(a_i,b_i)$。插入 $(a_i,b_i)$ 时，对于第 $k$ 位的结点 $u$，按 $a_i\oplus b_i$ 的第 $k$ 位划分左右儿子。同时在结点 $u$ 记录它子树内 $(a_i,b_i)$ 这一位 $4$ 种分布的元素个数。

查询的时候如果 $k$ 的对应位是 $0$，讨论 $(a_i,b_i)$ 对应位的取值：$(0,0),(1,1)$ 需要递归下去判断，这里只需要进入一侧儿子。对于 $(0,1)$ 只需要返回子树内的元素个数（这个已经预处理出来了），对于 $(1,0)$ 不可能产生贡献。对于 $k$ 对应位为 $1$ 的情况是类似的。

时间复杂度 $O((n+m)\log V)$ 可以通过。

可以看一下代码：
```cpp
const int N = 1e6 + 233;
int n, q, a[N], b[N];
struct Trie
{
	int tr[N * 30][2], cnt[N * 30][4], ed[N * 30], cc;
	inline void insert(int x, int y)
	{
		int u = 0;
		for (int i=30; i>=0; i--)
		{
			int c = x >> i & 1, d = y >> i & 1; ++cnt[u][c * 2 + d];
			if (!tr[u][c ^ d]) tr[u][c ^ d] = ++cc;
			u = tr[u][c ^ d];
		}
		++ed[u];
	}
	inline int query(int x)
	{
		int u = 0, ans = 0; bool sv = true;
		for (int i=30; i>=0; i--)
		{
			int c = x >> i & 1; ans += ed[u] + cnt[u][c * 2 + 1];
			if (tr[u][c]) u = tr[u][c];
			else{sv = false; break;}
		}
		return ans + sv * ed[u];
	}
	Trie() : cc(0){}
}T;
int main()
{
	int t; scanf("%d%d%d", &t, &n, &q);
	for (int i=1; i<=n; i++) scanf("%d", a+i);
	for (int i=1; i<=n; i++) scanf("%d", b+i);
	for (int i=1; i<=n; i++) T.insert(a[i], b[i]);
	int k = 0, lst = 0;
	while (q--)
	{
		scanf("%d", &k); k ^= lst * t;
		printf("%d\n", lst = T.query(k));
	}
	return 0;
}
```

---

## 作者：ZRZ0818 (赞：4)

由异或和不难想到 trie。

发现不好直接维护 $a_i$ 异或 $k$ 的值，于是考虑在插入时维护所有使得 $a_i \oplus k \le b_i$ 的 $k$。

设 $a_{i,j}$ 为 $a_i$ 的第 $j$ 位二进制 （进制位从大到小），同时 $k_{i,j}$ 为第 $i$ 次询问的第 $j$ 位二进制，$p$ 为当前节点编号。

- 当 $b_{i,j}$ 为 1 时，发现 $k_{i,j}$ 无论取 0,1 都可以产生贡献。

  - 当 $k_{i,j} = a_{i,j}$ 时异或得 0 可以直接贡献答案而不用往下查找；
  
  - 当 $k_{i,j} \not = a_{i,j}$ 时异或为 1，不能直接贡献答案且需要继续往下查找，此时需要查找 $p$ 的另一个子节点（儿子编号为 $1 \oplus a_{i,j}$）。

- 当 $b_{i,j}$ 为 0 时，只有 $k_{i,j} \oplus a_{i,j} =0$ 时才会贡献答案，此时需要往下查找 $p$ 的子节点 $a_{i,j}$。

注意当到达最后一位（枚举到 $i=0$ 时）时需要判断 $a_i \oplus k =b_{i}$ 也能贡献答案，此时 $b_{i,j}=1$ 且 $a_{i,j} \not = k_{i,j}$ 或 $b_{i,j}=0$ 且 $a_{i,j}=k_{i,j}$ 时都可以贡献答案。

建完 trie 后就可以直接查询了。

---

## 作者：Hisy (赞：4)

## 分析
看到了 $\oplus$ 符号，基本上往 01Trie 上面去想是没有问题的。

一开始想到的是离线做法，由于 $b_i$ 都不相同，但是对于单个 $i$ 是相同的，所以把所有 $i$ 拆分开来，录入所有的 $k$，然后用 01Trie 计算答案。但是**本题部分测试点强制在线**打破了我所有念想。

之后推了一下，发现可以成对将 $a_i$ 和 $b_i$ 压入 01Trie，和我们学校之前的一场考试 T3 很像（当时数组开小加没开 ```long long``` 的双重 buf 保灵了）。

首先，设 $\forall k=0$，那么只考虑 $a_i$ 的贡献，且仅当存在一位 $d$，满足 $a_i$ 和 $b_i$ 前 $d-1$ 位均为 $0$，但是 $b_i$ 的第 $d$ 位为 $1$。

首先，考虑使用 $res_{root,bit}$ 表示这一组 $\{a_i,b_i\}$ 这一位下标为 $root$，$a_i$ 这一位为 $bit$，$b_i$ 这一位为 $1$ 的个数。在 ```insert``` 的时候不断加即可。

怎么 ```query``` 呢？每跳到一个 $root$，可以加上当前 $root$ 下的 $res_{root,bit}$，表示当前 $k$ 的这一位为 $bit$，需要往 $1$ 去加。到了最后，不要忘记加上 $end_{root}$，取等也可以。
## 坑点
- RE 这东西防不胜防，本人现在都没有搞明白 Trie 的保守数组大小，这一道题目应该是 $5\times 10^5\times 30$。
- ```query``` 函数内部要判断 ```root``` 归零的情况。
- ```end``` 变量名报错了，尽量用别的变量名代替。
- $T=0$ 的情况不用异或！我猜不会有人犯和我一样的错……
## 代码
```cpp
#include<bits/stdc++.h>
#define MAXN 500005
using namespace std;
int t,n,m,k,cnt=1,a[MAXN],b[MAXN],tree[MAXN*31][2],eof[MAXN*31],res[MAXN*31][2];
inline void insert(int a,int b){
	int root=1;
	for(int i=30;i>=0;--i){
		int x=a>>i&1,y=b>>i&1;
		if(y){
			++res[root][x];
		}
		if(!tree[root][x^y]){
			tree[root][x^y]=++cnt;
		}
		root=tree[root][x^y];
	}
	++eof[root];
}
inline int query(int a){
	int root=1,ans=0;
	for(int i=30;i>=0&&root;--i){
		int x=a>>i&1;
		ans+=res[root][x];
		root=tree[root][x];
	}
	return ans+eof[root];
}
int main(){
	scanf("%d %d %d",&t,&n,&m);
	for(int i=1;i<=n;++i){
		scanf("%d",&a[i]);
	}
	for(int i=1;i<=n;++i){
		scanf("%d",&b[i]);
		insert(a[i],b[i]);
	}
	int lastans=0;
	while(m--){
		scanf("%d",&k);
		if(t){
			k^=lastans;
		}
		printf("%d\n",lastans=query(k));
	}
	return 0;
}
```

---

## 作者：5k_sync_closer (赞：3)

对每次询问数点对没啥前途，考虑对每个点对考虑其能贡献哪些询问。

点对 $(a_i,b_i)$ 可以贡献到 $a_i\oplus k\le b_i$ 的所有 $k$，考虑在 01Trie 上找到这些 $k$，

具体地，从高位到低位考虑，发现就是一个在 01Trie 上行走的问题，

假设当前要找 $a_i\oplus k$ 的前 $p-1$ 位与 $b_i$ 相同的所有 $k$，此时走到的点为 $u$，$a_i$ 的第 $p$ 位为 $x$，

若 $b_i$ 的第 $p$ 位为 $1$，则 $u$ 的 $x$ 孩子的子树中所有值都是合法的 $k$，在另一个孩子的子树中继续找，

若 $b_i$ 的第 $p$ 位为 $0$，则 $u$ 的非 $x$ 孩子的子树中所有值都不是合法的 $k$，在 $x$ 孩子的子树中继续找。

每个点对只会给 $O(\log V)$ 个子树答案加一，每次询问只需单点查询，复杂度 $O((n+m)\log V)$。

---

## 作者：jzl_1210 (赞：1)

这道题目能想到正解还是不容易的。  
首先看数据范围：$1 \le n,m \le 5 \times 10^5$。如果暴力做肯定超时。
# 前置知识

字典树，[模板题传送门](https://www.luogu.com.cn/problem/P8306)。

# 具体过程

那么看到题目中的异或运算，我们可以试着往字典树的方向来思考题目。  
建一个只有 $0$ 和 $1$ 的字典树，对于每个结点都有一个标记 $x$，表示从根结点到这个结点所形成的二进制数 $k$ 能满足 $x$ 个 $i$ 使得 $(a_i\oplus k)\le b_i$，其中 $\oplus$ 是按位异或。

完成定义后，就开始来思考，进行分类讨论：

1.  如果在二进制下这一位的 $b_i$ 是 $1$，这个时候异或的结果可以有两种情况，如果异或的结果为 $0$，则一定满足条件，$k$ 的这一位就要等于 $a_i$ 的这一位，这时就不用往下走了，直接给那个结点的标记 $+ 1$。如果异或的结果为 $1$，则还需要考虑后面的位数，于是就继续往下走。需要注意的是，如果到了最后一位，异或的结果为 $1$ 时也能满足条件，也要给更新标记。
2.   如果在二进制下这一位的 $b_i$ 是 $0$，这个时候异或的结果只能有一种情况，那就是 $0$，这个时候 $k$ 的这一位等于 $a_i$ 的这一位。然后还需要继续往下走，同样要特判最后一位。

这样就基本解决完了。在计算答案时，把 $k$ 的二进制在字典树上走一遍，把一路上的标记都相加即可。

# 代码

理解透了代码就很好写。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 5, MX = 15000005;
int n, T, trie[MX][3], a[N], b[N], Q, lst, jd[MX], cnt;
void ins(int num, int num2){
	int now = 0;
	for(int i = 29;i >= 0;i--){
		int zh = ((num >> i) & 1), zh2 = ((num2 >> i) & 1);
		if(zh2){
			//如果没有这个结点就新建一个结点
			if(trie[now][zh] == 0) trie[now][zh] = ++cnt; 
			jd[trie[now][zh]]++;
			if(trie[now][zh ^ 1] == 0) trie[now][zh ^ 1] = ++cnt;
			now = trie[now][zh ^ 1];
			if(i == 0) jd[now]++;//特判i==0 
		} else{
			if(trie[now][zh] == 0) trie[now][zh] = ++cnt;
			now = trie[now][zh];
			if(i == 0) jd[now]++;
		}
	}
}
int fin(int num){
	int now = 0, ans = 0;
	for(int i = 29;i >= 0;i--){
		int zh = ((num >> i) & 1);
		if(trie[now][zh] == 0) break;
		now = trie[now][zh];
		//把k的二进制在字典树上走一遍，把所有标记相加
		ans += jd[now];
	}
	return ans;
}
int main(){
    scanf("%d%d%d", &T, &n, &Q);
    for(int i = 1;i <= n;i++) scanf("%d", &a[i]);
    for(int i = 1;i <= n;i++){
    	scanf("%d", &b[i]);
    	ins(a[i], b[i]);
	}
    while(Q--){
    	int k;
    	scanf("%d", &k);
    	k = k ^ (lst * T);
    	int da = fin(k);
    	printf("%d\n", da);
    	lst = da;
	}
	return 0;
}
```

---

## 作者：zhuangzhihe (赞：1)

这道题是一道非常简单的 trie。  
（注：本题默认已了解如何使用 01 字符树，因此若不了解请先完成 P2580 和 P4551 两题。）  
~~首先我们先完成这道题最困难的部分——输入！（ 不是~~。  
先输入 $a_i$ 和 $b_i$，然后建树。  
判断 $b_i$ 的二进制状态下某一位是否为 $1$，（记为 $uy$，$a_i$ 的对应位记为 $ux$。$k$ 的对应位记为 $uk$。）因为只有当这一位为 $1$ 时， $ux⊕uk$ 才有可能小于 $uy$。当 $uy$ 为 $1$ 时，仅 $ux=uk$ 时，异或值才小于 $uy$，此时若 $uk$ 的值能够匹配这一位，则接下来不论 $ux⊕uk$ 的值为多少，$a_i⊕k$ 必然小于 $b_i$。因此向 $ux$ 建边。同时，这条边我们仅会保存这一个节点，因此我们要使用一个 $value$ 数组来记录它，表示这个点本应有一棵树，但被我们省略了。当 $k$ 的对应位匹配到此处时，可以直接跳过，并增加对应的 $value$ 值。  
然后向 $ux⊕uy$ 的方向建边，代表此处需要继续判断，因为当 $uk=ux⊕uy$ 时，我们仍需要继续判断，看它是否能够满足条件。当这棵树建到最后时，代表 $k⊕a_i=b_i$，满足条件，因此对应的 $value$ 值也增加。  
接下来就是简单的查询了。代码如下。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 500005
int k,ans,t,n,m,a[N],b[N],trie[N*35][2],value[N*35],tot;
void insert(int x,int y){
	int p=0;
	for(int i=30;i>=0;i--){
		int ux=(x>>i)&1,uy=(y>>i)&1;//这个地方把y写成了x硬控我一个小时
		int u=ux^uy;
		if(uy==1){
			if(!trie[p][ux]) trie[p][ux]=++tot;
			value[trie[p][ux]]++;
		}
		if(!trie[p][u]) trie[p][u]=++tot;
		p=trie[p][u];
	}
	value[p]++;
}
int ask(int x){
	int p=0,an=0;
	for(int i=30;i>=0;i--){
		int u=(x>>i)&1;
		p=trie[p][u];
		if(!p) return an;
		an+=value[p];
	}
	return an;
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>t>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		cin>>b[i];
		insert(a[i],b[i]);
	}
	for(int i=1;i<=m;i++){
		int x;
		cin>>x;
		k=x^(ans*t);
		ans=ask(k);
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：foglake (赞：0)

本篇题解主要更详细的推导为怎么一步步想到并解决问题，对于代码实现思路并没有过多介绍。

## P11209 『STA - R8』小熊游景点 II
对于这种**位运算加查询**的问题，很自然想到**字典树**。
### 前置芝士：字典树
不会的童鞋可以先做模板题：[【模板】字典树](https://www.luogu.com.cn/problem/P8306)。

### 解析
我们可以发现，对于位运算很容易想到把每个整数用二进制表示，然后将每个数类比为字符串用字典树存储就好。

但这个题有 $a_i$, $b_i$ 和 $k$。不可能按板子直接套就能 AC。

第一想法是用异或交换律，但好像只在等式中成立呢（超小声）。不过再一看不管 $k$ 怎么变，式子中 $a_i$ 和 $b_i$ 始终是对应的。那么我们就可以先将一对 $(a_i,b_i)$ 按某种关系存入字典树！

不过到底是什么关系？查询时该怎么办？观察到在询问中还有一个变量 $k$。有两个变量是不好处理的（根据前面的思路，我们将 $(a_i,b_i)$ 视作一个变量），就像解一元二次方程一样，我们也**要在 $k$ 与 $(a_i,b_i)$ 之间建立联系**。

再看到这个式子$\sum\limits_{i=1}^n[(a_i\oplus k)\le b_i]$。又由于 $k$ 是查询变量，所以考虑对于 $(a_i,b_i)$ 什么样 $k$ 的满足 $(a_i\oplus k)\le b_i$。

至于对于 $(a_i,b_i)$ 和 $k$ 应满足的约束在其他题解中已有详细介绍，可以看代码。

#### 字典树空间
由于字典树是棵树所以每层节点个数始终是单调不下降的。而对于本题，保守空间大概是 $30 \times n$ 的样子。不过实际上前 $log_2n$ 层是一个满二叉树，所以实际空间为 $13 \times n$，但我的~~后现代~~写法在每个节点下又开了两个节点所以开了 2 倍空间。
### 代码

```
#include <cstdio>
#include <vector>
using namespace std;
const int maxn = 5e5 + 10;
int s[26 * maxn][2], sum[26 * maxn], a[maxn], b[maxn];
int len;
void insert(int a, int b) {
	int u = 0;
	for (int i = 30; i > 0; i--) {
		int bita = (a >> (i - 1)) & 1, bitb = (b >> (i - 1)) & 1;
		if (!s[u][0]) s[u][0] = ++len;
		if (!s[u][1]) s[u][1] = ++len;
		if (bitb) {
			if (i == 1) {
				sum[s[u][0]] ++;
				sum[s[u][1]] ++;//因为是小于等于，所以最后要算上等于	
			} else {
				sum[s[u][bita]] ++;// 自己异或自己为 0，一定小于 1。
				u = s[u][bita ^ 1];// 否则继续讨论
			}
		} else {
			if (i == 1) sum[s[u][bita]] ++;
			else u = s[u][bita];
		}		
	}
}
int query(int k) {
	int u = 0, ans = 0;
	for (int i = 30; i > 0; i--) {
		if (!s[u][(k >> (i - 1)) & 1]) break;
		u = s[u][(k >> (i - 1)) & 1];
		ans += sum[u];
	}
	return ans;
}
int main() {
	int n, q, T;
	scanf("%d%d%d", &T, &n, &q);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	for (int i = 1; i <= n; i++) scanf("%d", b + i);
	for (int i = 1; i <= n; i++) insert(a[i], b[i]);
	int la = 0;
	for (int i = 1; i <= q; i++) {
		int k;
		scanf("%d", &k);
		k = (la * T) ^ k;
		la = query(k);
		printf("%d\n", la);
	}
}
```

---

