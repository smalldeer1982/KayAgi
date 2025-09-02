# Equate Multisets

## 题目描述

Multiset —is a set of numbers in which there can be equal elements, and the order of the numbers does not matter. Two multisets are equal when each value occurs the same number of times. For example, the multisets $ \{2,2,4\} $ and $ \{2,4,2\} $ are equal, but the multisets $ \{1,2,2\} $ and $ \{1,1,2\} $ — are not.

You are given two multisets $ a $ and $ b $ , each consisting of $ n $ integers.

In a single operation, any element of the $ b $ multiset can be doubled or halved (rounded down). In other words, you have one of the following operations available for an element $ x $ of the $ b $ multiset:

- replace $ x $ with $ x \cdot 2 $ ,
- or replace $ x $ with $ \lfloor \frac{x}{2} \rfloor $ (round down).

Note that you cannot change the elements of the $ a $ multiset.

See if you can make the multiset $ b $ become equal to the multiset $ a $ in an arbitrary number of operations (maybe $ 0 $ ).

For example, if $ n = 4 $ , $ a = \{4, 24, 5, 2\} $ , $ b = \{4, 1, 6, 11\} $ , then the answer is yes. We can proceed as follows:

- Replace $ 1 $ with $ 1 \cdot 2 = 2 $ . We get $ b = \{4, 2, 6, 11\} $ .
- Replace $ 11 $ with $ \lfloor \frac{11}{2} \rfloor = 5 $ . We get $ b = \{4, 2, 6, 5\} $ .
- Replace $ 6 $ with $ 6 \cdot 2 = 12 $ . We get $ b = \{4, 2, 12, 5\} $ .
- Replace $ 12 $ with $ 12 \cdot 2 = 24 $ . We get $ b = \{4, 2, 24, 5\} $ .
- Got equal multisets $ a = \{4, 24, 5, 2\} $ and $ b = \{4, 2, 24, 5\} $ .

## 说明/提示

The first example is explained in the statement.

In the second example, it is impossible to get the value $ 31 $ from the numbers of the multiset $ b $ by available operations.

In the third example, we can proceed as follows:

- Replace $ 2 $ with $ 2 \cdot 2 = 4 $ . We get $ b = \{4, 14, 14, 26, 42\} $ .
- Replace $ 14 $ with $ \lfloor \frac{14}{2} \rfloor = 7 $ . We get $ b = \{4, 7, 14, 26, 42\} $ .
- Replace $ 26 $ with $ \lfloor \frac{26}{2} \rfloor = 13 $ . We get $ b = \{4, 7, 14, 13, 42\} $ .
- Replace $ 42 $ with $ \lfloor \frac{42}{2} \rfloor = 21 $ . We get $ b = \{4, 7, 14, 13, 21\} $ .
- Replace $ 21 $ with $ \lfloor \frac{21}{2} \rfloor = 10 $ . We get $ b = \{4, 7, 14, 13, 10\} $ .
- Got equal multisets $ a = \{4, 7, 10, 13, 14\} $ and $ b = \{4, 7, 14, 13, 10\} $ .

## 样例 #1

### 输入

```
5
4
2 4 5 24
1 4 6 11
3
1 4 17
4 5 31
5
4 7 10 13 14
2 14 14 26 42
5
2 2 4 4 4
28 46 62 71 98
6
1 2 10 16 64 80
20 43 60 74 85 99```

### 输出

```
YES
NO
YES
YES
YES```

# 题解

## 作者：baiABC (赞：14)

首先把集合 $a,b$ 中的元素都除以 $2$ 直到变为奇数，因为有乘 $2$ 除以 $2$ 的操作，所以这样不会影响答案。（其实不处理 $b$ 也可以）

然后对于 $b$ 中的数。操作一定只有除以 $2$ 下取整（因为如果是乘 $2$ 的话还要除回来，如果不除回来就成了偶数，一定不等于 $a$ 中的奇数）。

所以考察 $a,b$ 中最大的数（设为 $ma, mb$）：
- 如果 $ma > mb$，则由于 $mb$ 只能除以二下取整，所以得不到 $ma$，无解；
- 若 $ma = mb$，则可以贪心地将这两个元素删除；
- 若 $ma < mb$，则删除 $mb$，换为 $\lfloor\frac{mb}{2}\rfloor$ 再插入 $b$。

重复该操作，直到集合为空。

代码也比较容易实现，时间复杂度 $O(Tn\log n\log w)$（$w$ 为值域）。

### 赛时代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
int main()
{
   ios::sync_with_stdio(0); int T;
   cin >> T;
   for(int i = 0; i < T; ++i)
   {
      cin >> n;
      multiset <int> a, b;
      // 用 priority_queue 也可以
      for(int i = 1; i <= n; ++i)
      {
         int x; cin >> x;
         while(x % 2 == 0) x /= 2;
         a.insert(x);
      }
      for(int i = 1; i <= n; ++i)
      {
         int x; cin >> x;
         while(x % 2 == 0) x /= 2;
         b.insert(x);
      }
      bool ok = true;
      while(!b.empty())
      {
         if(*--b.end() > *--a.end())
         {
            int x = *--b.end();
            b.erase(--b.end());
            b.insert(x/2);
         }
         else if(*--b.end() < *--a.end())
         {
            ok = false;
            break;
         }
         else
         {
            b.erase(--b.end());
            a.erase(--a.end());
         }
      }
      cout << (ok?"YES":"NO") << '\n';
   }
   return 0;
}
```

---

## 作者：Jr_Zlw (赞：5)

# 网络最大流

大概是最劣解？但能过嘿嘿。

考虑到对  $b$  中某个值进行操作的时候能取到的值不多大概是  $O(\log^2)$  种，所以想办法处理出这些数然后跟  $a$  里面的数匹配，匹配的话当然是建图跑最大流就好啦。

很遗憾，tle on test 30 ，考虑剪枝：

1. 集合  $a$  和  $b$  中重复的取值压倒一个点里面去，然后流量改成这个取值的数量。
2. 考虑到一个数二进制末尾有  $0$  时，把这些  $0$  干掉不影响存在  $b$  中的值与其匹配，所以直接把二进制末尾的  $0$  全部干掉就好啦，然后发现边数从  $O(\log^2)$  变成了  $O(\log)$  的。
3. 尝试指令集，或更优的网络流模型。

最重要的还是第  $2$  个优化，点数  $O(n)$，边数  $O(n\log n)$，卡过去了。

代码：

```cpp
#include<cstdio>
#include<cstring>
#include<vector>
#include<map>
#include<algorithm>
#define rep(a,b,c) for(int c(a);c<=(b);++c)
#define grep(b,c) for(int c(head[b]);c;c=Nxt[c])
using std::vector;using std::map;
inline void print(const int &p){if(p>9)print(p/10);putchar(p%10+'0');}
inline int read()
{
	int res=0;char ch=getchar();bool flag=0;
	while(ch<'0'||ch>'9')flag^=(ch=='-'),ch=getchar();
	while(ch<='9'&&ch>='0')res=res*10+(ch^48),ch=getchar();
	return flag ? -res : res ;
}
struct Pair
{
	int x,y;inline Pair(int X=0,int Y=0){x=X;y=Y;}
	inline bool operator < (const Pair &Q)const {return x==Q.x?y<Q.y:x<Q.x;}
};
namespace MF
{
	const int N=2e6+10,M=1e7+10,INF=0x3f3f3f3f;
	int head[N],des[M],Nxt[M],cgt=1,s,t,S,dep[N],que[N],cap[M],H,T,h2[N];bool vis[N];
	inline void Clear(){memset(head,0,(S+2)<<2);cgt=1;S=0;}
	inline void ins(const int &x,const int &y,const int &c=1)
	{
		if(!x||!y)return;
		Nxt[++cgt]=head[x];des[head[x]=cgt]=y;cap[cgt]=c;
		Nxt[++cgt]=head[y];des[head[y]=cgt]=x;cap[cgt]=0;
	}
	inline bool bfs()
	{
		memset(dep,0,(S+2)<<2);dep[que[H=T=0]=s]=1;
		while(H<=T){int u=que[H++];grep(u,i)if(cap[i]&&!dep[des[i]])dep[que[++T]=des[i]]=dep[u]+1;} return dep[t];
	}
	inline int dfs(const int &u=s,int in=INF)
	{
		if(u==t)return in;int out=0;
		for(int &i=h2[u];i;i=Nxt[i])
		{
			int v=des[i];if(cap[i]&&dep[v]==dep[u]+1)
			{
				int tmp=dfs(v,cap[i]<in?cap[i]:in);
				out+=tmp;cap[i]-=tmp;cap[i^1]+=tmp;if(!(in-=tmp))break;
			}
		}
		return out?out:dep[u]=0;
	}
	inline int dinic()
	{
		int res=0;while(bfs())memcpy(h2,head,(S+2)<<2),res+=dfs();return res;
	}
	inline void Init(){memset(head,0,(S+2)<<2);S=0;cgt=1;} 
}
using MF::ins;using MF::S;using MF::s;using MF::t;
const int N=2e5+10;int n;map<int,Pair>mp;map<int,int> b;
inline void Solve()
{
	n=read();s=++S;t=++S;mp.clear();int cc=0;b.clear();
	rep(1,n,i)
	{
		int x=read();if(__builtin_popcount(x)==1){++cc;continue;}
		while(!(x&1))x>>=1;Pair &q=mp[x];++q.x;if(q.x==1)q.y=++S;
	}
	rep(1,n,i)++b[read()];
	for(std::pair<int,int> v: b)
	{
		int x=v.first,id=++S;ins(s,id,v.second);
		rep(0,30,i)if(x>>i&1)
		{
			int cur=x>>i;
			if(__builtin_popcount(cur)==1)break;
			if(mp.count(cur))
			{
				ins(id,mp[cur].y,v.second);
			}
		}
	}
	for(std::pair<int,Pair> v:mp)
	{
		Pair tmp=v.second;
		ins(tmp.y,t,tmp.x);
	}
	puts(MF::dinic()==n-cc?"YES":"NO");
	MF::Init();
}
int main()
{
	int T=read();while(T--)Solve();
}
```


---

## 作者：tzyt (赞：5)

题目链接[（CF](https://codeforces.com/problemset/problem/1702/F)，[洛谷）](https://www.luogu.com.cn/problem/CF1702F) | 强烈推荐[博客](https://ttzytt.com/2022/07/CF1702/)中观看。

前言：本题解的解法参考了[这个视频](https://www.youtube.com/watch?v=HIiX3r5n27M)。

## 题意
多重集是一种特殊的集合，其元素可以重复，并且，和集合一样，元素的顺序不重要。如果两个多重集中，每个元素的出现次数都一样，那么这两个多重集就是相等的。

如，$\{2, 2, 4\}$ 和 $\{2, 4, 2\}$ 是相同的。而 $\{1, 2, 2\}$ 和 $\{1, 1, 2\}$ 不是相同的。

现在给你两个多重集 $a$ 和 $b$，每个包含 $n (1 \le 2\cdot 10^5)$ 个整数。

在一次操作中，$b$ 中的一个元素可以被翻倍或是减半（向下取整）。或者说，对于一个 $b$ 中的元素 $x$，你可以做下面两种操作。

- 替换 $x$ 为 $2x$
- 替换 $x$ 为 $\lfloor \frac{x}{2} \rfloor$

注意你不能对多重集 $a$ 做任何操作。

请问你是否能使多重集 $b$ 在经过任意数量的操作后和 $a$ 相等（也可以是 $0$ 个操作）。

## 一些性质
这个 $\times 2$ 和 $\lfloor \div 2 \rfloor$ 可以联系到位运算的左移和右移。如 $5$ 的二进制形式为 $(101)_2$，$5\times 2$ 的二进制形式就为 $(1010)_2$。可以看到相比 $5$，$10$ 的二进制形式在最后加了一个 $0$。而 $10 \div 2$ 就是 $5$，二进制形式下的 $5$ 在最后一位比 $10$ 少了一个 $0$。

所以左移和乘二的运算是等价的，右移和向下取整的除二是等价的。

那么我们就可以发现一个性质，也就是集合（实为多重集，这里为了方便称为集合） $a$ 和 $b$ 中元素的后缀 $0$ 是不重要的。

这里我来解释一下什么是后缀 $0$，以及“不重要”。

现在有一个数，比如 $40$，其二进制形式为 $(101000)_2$。可以看到二进制下的 $40$ 在尾部有 $3$ 个 $0$。那么这三个 $0$ 就是 $40$ 的后缀 $0$。

而不重要的意思是：

如果我们设 $\alpha \in a, \beta \in b$。再设 $\alpha^\prime$ 和 $\beta^\prime$ 分别为 $\alpha$ 和 $\beta$ 去掉后缀 $0$ 的后的数字。那么如果我们能通过提供的两个操作，把 $\beta$ 转换成 $\alpha$ 就一定能把 $\beta^\prime$ 转换为 $\alpha^\prime$。

这是因为可以通过左移和右移操作，在 $\beta^\prime$ 的尾部增加和删去任意数量的 $0$。

这样就可以让 $\beta^\prime$ 变成 $\beta$。而对于 $\beta$， 我们已经知道了可以将其转换成 $\alpha$ 。现在我们再在当前数字上减去一些 $0$，就可以变成 $\alpha^\prime$。

所以为了计算的方便，可以直接在输入的时候去掉元素的后缀 $0$。

接下来，还有一个性质：

当且仅当 $\alpha^\prime$ 在二进制形式下是 $\beta^\prime$ 的前缀，我们可以将 $\beta^\prime$ 转换为 $\alpha^\prime$。

这里先解释一下，什么是二进制形式下的前缀。有两个数字，$9$ 和 $75$。其二进制形式分别是 $(1001)_2$ 和 $(1001011)$。

那么从字符串的角度来看，$\texttt{1001}$ 就是 $\texttt{1001011}$ 的前缀。而能将 $\beta^\prime$ 转换为 $\alpha^\prime$ 是因为右移操作，我们可以把 $\beta^\prime$ 的尾部去掉使其变成自己的任意二进制下的前缀。

并且，显而易见的，如果 $\alpha^\prime > \beta^\prime$， $\alpha^\prime$ 一定不是 $\beta^\prime$ 二进制形式下的前缀。那就自然不能将 $\beta^\prime$ 转换为 $\alpha^\prime$。

## 具体实现

有了这些性质，我们就可以搞出一些奇怪的方法了。

首先我们把集合 $a$ 的元素存到一个数组里，把集合 $b$ 的元素存到一个优先队列里。在存之前，需要先去掉后缀 $0$。

```cpp
vector<int> a(n);
priority_queue<int> b;
for (int i = 0; i < n; i++) { 
    cin >> a[i];
    while ((a[i] & 1) == 0) { // 如果最后一位是 0，那就一直右移来消除后缀 0
        a[i] >>= 1;
    }
}
for (int i = 0; i < n; i++) {
    int temp;
    cin >> temp;
    while ((temp & 1) == 0) {
        temp >>= 1;
    }
    b.push(temp);
}
```

然后再对 $a$ 升序排序，之后就可以搞出一些骚操作了：

```cpp
sort(a.begin(), a.end());
while (b.size()) {
    int lb = b.top();
    b.pop();
    int la = a.back();
    if (la > lb) {
        goto FAIL;
    } else if (la < lb) {
        lb /= 2;
        b.push(lb);
    } else {  // la == lb
        a.pop_back();
    }
}
```

可以看到，在这个 `while` 中，我们每次取出的 $la$ 和 $lb$ 都分别是 $a$ 和 $b$ 中最大的元素。

那么有三种情况。
1. $la > lb$：这种情况下，可以直接输出 NO 了，因为 $la$ 绝对不是 $lb$ 二进制形式下的前缀（见前文）。而 $lb$ 已经是整个集合 $b$ 中最大的元素了，也就是说如果不能让 $lb$ 转换成 $la$，集合 $b$ 中的其他元素就更不可能转换成 $la$ 了。
2. $la = lb$：因为两个元素相等了，所以可以从集合中去掉（集合为空时，我们就可以输出 YES）。所以有 `a.pop_back();` 这句话。
3. $la < lb$：这时我们不知道 $la$ 是否是 $lb$ 的前缀，但是有这个可能性。那我们就直接让 $lb$ 右移一位，变成自己的最长前缀，然后之后再看 $\lfloor \frac{lb}{2} \rfloor$ 是否能跟其他 $a$ 中的元素一样。 

对于第三种情况，如果说直接把 $lb$ 右移了然后放入优先队列中，那是否会造成： $lb$ 本来是可以跟 $a$ 中别的元素匹配，但现在不行了的情况呢？

答案是不会的，因为 $a$ 中最大的元素已经小于 $lb$ 了，那其他元素一定也小于它，所以不会有别的元素等于 $lb$ 了。

## 完整代码 

```cpp
#include <bits/stdc++.h>
using namespace std;
// author: tzyt
// ref: https://www.youtube.com/watch?v=HIiX3r5n27M
int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        priority_queue<int> b;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            while ((a[i] & 1) == 0) { // 如果最后一位是 0，那就一直右移来消除后缀 0
                a[i] >>= 1;
            }
        }
        for (int i = 0; i < n; i++) {
            int temp;
            cin >> temp;
            while ((temp & 1) == 0) {
                temp >>= 1;
            }
            b.push(temp);
        }
        sort(a.begin(), a.end());
        while (b.size()) {
            int lb = b.top();
            b.pop();
            int la = a.back();
            if (la > lb) {
                goto FAIL;
            } else if (la < lb) {
                lb /= 2;
                b.push(lb);
            } else {  // la == lb
                a.pop_back();
            }
        }
    SUCC:
        cout << "YES\n";
        continue;
    FAIL:
        cout << "NO\n";
    }
}
```

最后，希望这篇题解对你有帮助，如果有问题可以通过评论区或者私信联系我。

---

## 作者：Na2PtCl6 (赞：2)

### 分析
先来举例子：

$a_i=$ `10101111000`

$b_i=$ `10101111101010`

把 $b_i$ 进行 $6$ 次操作二，$3$ 次操作一就可以使 $a_i$ 和 $b_i$ 相等。

因此注意到 $a_i$ 的二进制去掉所有在末尾的 $0$ 之后，如果出现在 $b_i$ 二进制的前缀中，就可以从 $b_i$ 变换得来。

CF的机子快，我们直接上暴力：
从大到小枚举所有 $b_i$ 的前缀，如果发现这个前缀在 $a_i$ 中出现了，就让 $b_i$ 变成 $a_i$。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=200004;
char eq[maxn];
int t,n,a,b[maxn],pre[maxn][34];

map < int,int > cnta;

bool solve(){
	cnta.clear();
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		eq[i]=0;
		memset(pre[i],0,sizeof(pre[i]));
	}
	for(int i=1;i<=n;i++){
		scanf("%d",&a);
		while((a&1)==0)
			a>>=1;
		++cnta[a];
	}
	for(int i=1;i<=n;i++){
		scanf("%d",&b[i]);
		while((b[i]&1)==0)
			b[i]>>=1;
	}
	for(int i=1;i<=n;i++){
		int cnt=0;
		while(b[i]>0){
			pre[i][++cnt]=b[i];
			b[i]>>=1;
		}
	}
	for(int j=1;j<=31;j++)
		for(int i=1;i<=n;i++){
			if(cnta[pre[i][j]]&&!eq[i]){
				--cnta[pre[i][j]];
				eq[i]=1;
			}
		}
	for(int i=1;i<=n;i++)
		if(eq[i]==0)
			return 0;
	return 1;
}

int main(){
	scanf("%d",&t);
	while(t--)
		puts(solve()?"YES":"NO");
	return 0;
}
```

---

## 作者：luo_shen (赞：1)

**题意**  
有两个元素可以重复的集合 $a,b$，$b$ 中的每个元素 $x$ 都可以进行两个操作： 
- 把 $x$ 变为 $2x$
- 把 $x$ 变为 $\lfloor\frac{x}{2}\rfloor$

问经过若干次操作后能否将 $b$ 变成 $a$。  
**分析**  
因为有第一个操作，所以所有的偶数都是没有意义的。因此，可以将集合 $a,b$ 中的元素全部变成奇数。然后对于两个集合里的数，可以知道：若 $a$ 中最大的元素 $a_{max}$ 大于 $b$ 中最大的元素 $b_{max}$，说明没有任何元素能变成 $a_{max}$，即无论 $b$ 中的元素如何变换，都不可能将 $b$ 变成 $a$；若 $b_{max}$ 等于 $a_{max}$，说明这两个元素已经匹配了，不需要在进行操作了，可以从集合中剔除；若 $a_{max}$ 小于 $b_{max}$，可以将 $\lfloor\frac{b_{max}}{2}\rfloor$ 放入集合中，再重复进行以上操作。  
**代码**
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
int x,t,n;
priority_queue<int>q,p;//用p,q两个堆维护a,b集合中元素的大小关系
int main(){
    cin>>t;
    while(t--){
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>x;
            while(!(x&1)){
                x>>=1;
            }
            q.push(x);
        }//将a集合中的元素变成奇数
        for(int i=1;i<=n;i++){
            cin>>x;
            while(!(x&1)){
                x>>=1;
            }
            p.push(x);
        }//将b集合中的元素变成奇数
        bool f=1;
        while(!q.empty()){//重复操作、判断
            int x=q.top(),y=p.top();
            q.pop(),p.pop();
            if(y<x){
                f=0;
                break;
            }
            else if(y>x){
                q.push(x);
                p.push(y/2);
            }
        }
        if(f){
            puts("YES");
        }
        else{
            puts("NO");
            while(!q.empty()){//如果不行记得清空。
                q.pop();
            }
            while(!p.empty()){
                p.pop();
            }
        }
    }
    return 0;
}
```

---

## 作者：wmrqwq (赞：0)

哎哎哎，题解区里怎么没我的做法啊 /yun。

于是就有了这篇题解。

# 题目链接

[CF1702F Equate Multisets (luogu)](https://www.luogu.com.cn/problem/CF1702F)

[CF1702F Equate Multisets (codeforces)](https://codeforces.com/contest/1702/problem/F)

# 解题思路

首先我们发现，$a$ 序列中的数字的末尾的 $0$ 是无意义的，因此我们可以将 $a$ 序列中的每一个数字一直除以 $2$ 直到这个数字为奇数。

我们发现，将 $b$ 序列的数字一直乘上 $2$ 是一定没有损失的，于是我们首先肯定是通过将 $b$ 序列的数字乘 $2$ 的方式与 $a$ 序列中的数字匹配的。

处理完乘的操作，同样地，我们可以通过一直将 $b$ 序列中的数字一直除以 $2$ 直到匹配的方式来处理除的操作。

无解的情况很好判断，只需要判断是否最终均可以匹配即可。

时间复杂度 $O(n \log_2 V)$，其中 $V$ 为值域。

# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
//#define map unordered_map
#define re register
#define ll long long
#define forl(i,a,b) for(re ll i=a;i<=b;i++)
#define forr(i,a,b) for(re ll i=a;i>=b;i--)
#define forll(i,a,b,c) for(re ll i=a;i<=b;i+=c)
#define forrr(i,a,b,c) for(re ll i=a;i>=b;i-=c)
#define lc(x) x<<1
#define rc(x) x<<1|1
#define mid ((l+r)>>1)
#define cin(x) scanf("%lld",&x)
#define cout(x) printf("%lld",x)
#define lowbit(x) (x&-x)
#define pb push_back
#define pf push_front
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
#define db long double
#define ull unsigned long long
#define lcm(x,y) x/__gcd(x,y)*y
#define Sum(x,y) 1ll*(x+y)*(y-x+1)/2
#define aty cout<<"Yes\n";
#define atn cout<<"No\n";
#define cfy cout<<"YES\n";
#define cfn cout<<"NO\n";
#define xxy cout<<"yes\n";
#define xxn cout<<"no\n";
#define printcf(x) x?cout<<"YES\n":cout<<"NO\n";
#define printat(x) x?cout<<"Yes\n":cout<<"No\n";
#define printxx(x) x?cout<<"yes\n":cout<<"no\n";
ll t;
/*
显然先做乘法再做除法。 
*/
ll n;
ll a[1000010],b[1000010];
map<ll,ll>mp;
ll vis[1000010]; 
void solve()
{
	mp.clear();
	cin>>n;
	forl(i,1,n)
	{
		cin>>a[i];
		while(a[i]%2==0)
			a[i]/=2;
	}
	forl(i,1,n)
		cin>>b[i],vis[i]=0;
	sort(a+1,a+1+n);
	sort(b+1,b+1+n);
	forl(i,1,n)
		mp[a[i]]++;
	forl(i,1,n)
	{
		ll num=b[i],lst=-1;
		while(num<=5e9)
		{
			if(mp[num])
				lst=num;
			num*=2;
		}
		if(lst!=-1)
			mp[lst]--,vis[i]=1;
	}
	forl(i,1,n)
		if(!vis[i])
		{
			ll num=b[i],pd=0;
			while(num>0)
			{
				num/=2;
				if(mp[num])
				{
					pd=1;
					mp[num]--;
					vis[i]=1;
					break;
				}
			}
		}
	forl(i,1,n)
		if(!vis[i])
		{
			cfn;
			return ;
		}
	cfy;
}
int main()
{
	IOS;
	t=1;
 	cin>>t;
	while(t--)
		solve();
	QwQ;
}
```

---

## 作者：Special_Tony (赞：0)

[洛谷传送门](/problem/CF1702F) & [CF 传送门](//codeforces.com/problemset/problem/1702/F)
# 思路
初看这一题，这题难搞的地方就在于有两种操作，所以我们可以考虑先做完一种操作，再去单独地做第二种。我们可以发现，先把 $x$ 替换成 $2x$，再把 $x$ 替换为 $\lfloor\frac x2\rfloor$ 时，操作前和操作后的 $x$ 值不变，因为这时的向下取整不起作用；但先把 $x$ 替换为 $\lfloor\frac x2\rfloor$，再把 $x$ 替换成 $2x$ 后，操作前后的 $x$ 就不一定相等了。所以，我们就可以考虑先做第一种操作，再做第二种操作。

第一种操作并不是单纯地把 $b_i$ 不断乘 $2$，而是把所有 $a_i$ 和 $b_i$ 都不断除以 $2$，直到所有数变为奇数为止。这时候，我们的第二种操作就可以开始了。

第二种操作也不能普通操作，否则太慢了。我们需要操作的是所有 $b_i$ 中最大的一个 $y$。我们需要拿 $a_i$ 中最大的数 $x$ 与它作比较，分类考虑：
1. 当 $x>y$ 时，由于这时 $y$ 是单调不减的了，所以直接无解；
1. 当 $x<y$ 时，我们直接把 $y$ 进行一次操作（除以 $2$）即可；
1. 当 $x=y$ 时，这时候我们直接把 $x$ 和 $y$ 都删掉即可。

这里每次要求 $x$ 和 $y$，我们可以使用 STL 的优先队列 $O(\log n)$ 快速解决。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
int t, n, m, x;
priority_queue <int> q1, q2;
void clear (priority_queue <int>& q) {
	while (! q.empty ())
		q.pop ();
	return ;
}
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> t;
	while (t --) {
		cin >> n;
		clear (q1), clear (q2); //手动清空优先队列
		for (int i = 0; i < n; ++ i) {
			cin >> x;
			while (! (x & 1)) //不断除以 2
				x >>= 1;
			q1.push (x);
		}
		for (int i = 0; i < n; ++ i) {
			cin >> x;
			while (! (x & 1))
				x >>= 1;
			q2.push (x);
		}
		while (! q1.empty ())
			if (q1.top () < q2.top ())
				q2.push (q2.top () >> 1), q2.pop (); //记得 pop
			else if (q1.top () > q2.top ()) {
				cout << "NO\n";
				goto END; //goto 是个好东西，可以直接跳转到 END 继续执行
			} else
				q1.pop (), q2.pop ();
		cout << "YES\n"; //有解
END: ;
	}
	return 0;
}
```

---

## 作者：qwq___qaq (赞：0)

### Update

2022.7.13 使题解更加详细。

首先，因为可以乘 $2$，所以我们把 $a$ 和 $b$ 中的 $2$ 全部除掉，这样可以得到一堆奇数，用桶记录 $a$ 的元素。

考虑 $b_i$：

对于乘法，直接在桶中查找 $b_i$，如果有，那么可以将 $b_i$ 乘 $2$ 或除 $2$，改变 $2$ 的个数，就可以得到 $a_i$；

对于除法，先 $b_i\gets\lfloor\dfrac{b_i}{2}\rfloor$，然后将 $b_i$ 中的 $2$ 除掉，然后在桶中查询 $b_i$，如果有，那么可以将 $b_i$ 乘 $2$ 或除 $2$，改变 $2$ 的个数，就可以得到 $a_i$。

---

## 作者：SUNCHAOYI (赞：0)

对于一个 $a_i$ 若可以表示成 $k \times 2^p$ 的形式，那一定可以由 $k$ 进行若干次第一个乘 $2$ 的操作得到。所以我们将所有的 $a_i$ 预处理，使其变成奇数。然后使用 `map <int,int> p` 统计 $a_i$ 的分布，$p_i$ 的值就相当于处理 $b$ 后该数需要出现的次数。

对于每一个 $b_i$，若 $p_{b_i}$ 大于 $0$，那么就说明 $b_i$ 可以变成某个 $a_j$。因此将 $p_{b_i} - 1$ 以作更新；否则将 $b_i$ 除以 $2$ 后向下取整，直至为 $0$。最后只要更新的次数为 $n$，就说明每一个 $b_i$ 都能分别对应一个不同的 $a_j$，此时答案为 `YES`。

代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <map>
#define init(x) memset (x,0,sizeof (x))
#define ll long long
#define ull unsigned long long
#define INF 0x3f3f3f3f
using namespace std;
const int MAX = 2e5 + 5;
const int MOD = 1e9 + 7;
inline int read ();
int t,n,cnt,a[MAX],b[MAX]; 
map <int,int> p;
int main ()
{
	//freopen (".in","r",stdin);
	//freopen (".out","w",stdout);
	t = read ();
	while (t--)
	{
		n = read ();
		cnt = n;
		p.clear ();//多测要清空！！！
		for (int i = 1;i <= n;++i)
		{
			a[i] = read ();
			while (a[i] % 2 == 0) a[i] /= 2;//处理 a_i
			++p[a[i]];//存入 map 中
		}
		for (int i = 1;i <= n;++i)
		{
			int x = read ();
			while (x)
			{
				if (p[x])//只要存在就更新
				{
					--p[x],--cnt;
					break;
				}
				x /= 2;//不断除以 2 直到变为 0
			}
		}
		if (!cnt) printf ("YES\n");//处理了 n 次使得 cnt 变为 0
		else printf ("NO\n");
	} 
	return 0;
}
inline int read ()
{
    int s = 0;int f = 1;
    char ch = getchar ();
    while ((ch < '0' || ch > '9') && ch != EOF)
	{
        if (ch == '-') f = -1;
        ch = getchar ();
    }
    while (ch >= '0' && ch <= '9')
	{
        s = s * 10 + ch - '0';
        ch = getchar ();
    }
    return s * f;
}
```

---

