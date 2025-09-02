# Bitwise Operation Wizard

## 题目描述

This is an interactive problem.

There is a secret sequence $ p_0, p_1, \ldots, p_{n-1} $ , which is a permutation of $ \{0,1,\ldots,n-1\} $ .

You need to find any two indices $ i $ and $ j $ such that $ p_i \oplus p_j $ is maximized, where $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

To do this, you can ask queries. Each query has the following form: you pick arbitrary indices $ a $ , $ b $ , $ c $ , and $ d $ ( $ 0 \le a,b,c,d < n $ ). Next, the jury calculates $ x = (p_a \mid p_b) $ and $ y = (p_c \mid p_d) $ , where $ | $ denotes the [bitwise OR operation](https://en.wikipedia.org/wiki/Bitwise_operation#OR). Finally, you receive the result of comparison between $ x $ and $ y $ . In other words, you are told if $ x < y $ , $ x > y $ , or $ x = y $ .

Please find any two indices $ i $ and $ j $ ( $ 0 \le i,j < n $ ) such that $ p_i \oplus p_j $ is maximum among all such pairs, using at most $ 3n $ queries. If there are multiple pairs of indices satisfying the condition, you may output any one of them.

## 说明/提示

In the first test case, the hidden permutation is $ p=[0,3,1,2] $ .

For the query "? 0 2 3 1", the jury return "&lt;" because $ (p_0 \mid p_2) = (0 \mid 1) =1 < (p_3 \mid p_1) = (2 \mid 3) = 3 $ .

For the query "? 1 1 2 3", the jury return "=" because $ (p_1 \mid p_1) = (3\mid 3)= 3 = (p_2 \mid p_3) = (1 \mid 2)=3 $ .

For the query "? 1 2 0 3", the jury return "&gt;" because $ (p_1 \mid p_2) = (3 \mid 1) = 3 > (p_0 \mid p_3) = (0\mid 2)=2 $ .

The answer $ i = 3 $ and $ j = 2 $ is valid: $ (p_3 \oplus p_2) = (2 \oplus 1) = 3 $ is indeed equal to the maximum possible value of $ p_i \oplus p_j $ . Another valid answer would be $ i=0 $ and $ j=1 $ . As the number of queries does not exceed $ 3n=12 $ , the answer is considered correct.

In the second test case, $ n = 2 $ , so $ p $ is either $ [0, 1] $ or $ [1, 0] $ . In any case, $ p_0 \oplus p_1 = 1 $ is maximum possible.

## 样例 #1

### 输入

```
2
4

&lt;

=

&gt;

2```

### 输出

```
? 0 2 3 1

? 1 1 2 3

? 1 2 0 3

! 3 2

! 0 1```

# 题解

## 作者：Wf_yjqd (赞：7)

总感觉会有更优的做法。

------------

我们一开始不需要往最优想，先考虑找出一种 $\operatorname{O}(n)$ 的解。

显然对于一个排列，任意两项的最大异或和是固定的，即二进制下每位都为 $1$。

也就是说我们需要构造一对异或和最大的数并在序列中找到他们的位置。

发现 $a=b$ 时 $(p_a\ |\ p_b)=p_a$，$c,d$ 同理。这样我们就能 $n-1$ 次求出最大值 $n-1$ 的位置了。

显然 $n-1$ 次确定一个位置很划算，考虑和 $n-1$ 异或和最大的数，在二进制下每位都与 $n-1$ 相反。

所以他俩的按位或也是最大的，刚好此题支持按位或后比大小，那我们再花 $n-1$ 次求出与 $n-1$ 按位或最大的所有数。

这些数都是在异或和最大的数身上将若干 $0$ 变成 $1$ 造成的。

那么其中最小的数一定是和 $n-1$ 异或和最大的数。

所以我们花费和 $n-1$ 按位或最大的数的个数 $-1$ 次求出另一个数的位置。

刚好能满足 $\le 3n$，那就不用考虑优化了。

------------

其实代码没啥好放的。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e4+26;
int T,n,mx,mn,st[maxn],top;
char s[26],res;
inline char Q(int a,int b,int c,int d){
    printf("? %d %d %d %d\n",a,b,c,d);
    fflush(stdout);
    scanf("%s",s);
    return s[0];
}
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        mx=0;
        for(int i=1;i<n;i++)
            mx=(Q(mx,mx,i,i)=='<'?i:mx);
        st[top=1]=mx;
        for(int i=0;i<n;i++)
            if(i!=mx){
                if((res=Q(i,mx,st[top],mx))=='=')
                    st[++top]=i;
                else if(res=='>')
                    st[top=1]=i;
            }
        mn=st[1];
        for(int i=2;i<=top;i++)
            mn=(Q(mn,mn,st[i],st[i])=='>'?st[i]:mn);
        printf("! %d %d\n",mx,mn);
        fflush(stdout);
    }
    return 0;
}
```

---

## 作者：Missa (赞：1)

注意到答案就是 $2^{\lceil \log_{2}(n-1) \rceil+1}-1$。注意到 $(n-1) \operatorname{xor} ans < n-1$，先找到 $n-1$ 的位置再去找那个对应数 $x$ 的位置即可。 

首先注意到 $x \operatorname{or} x = x$，这意味着我们可以比大小，也就可以用 $n-1$ 次比较找到 $n-1$ 的位置。

注意到 $x$ 和 $n-1$ 的数位恰好构成补集，且 $x \operatorname{or} (n-1)=ans$。在此基础上，所有满足 $y \operatorname{or} (n-1)=ans$ 的 $y$ 一定是 $x$ 的超集，即不小于 $x$。那么找到所有最大化了 $y \operatorname{or} (n-1)$ 的 $y$ 并找到它们的最小值即可。

从 $n$ 个数中寻找极值需要 $n-1$ 次比较，因此总共进行不超过 $3n-3$ 次比较。

```cpp
#include <bits/stdc++.h>

int qry(int a, int b, int c, int d) {
  printf("? %d %d %d %d\n", a, b, c, d);
  fflush(stdout);
  char t; scanf(" %c", &t);
  return t == '<' ? -1 : t == '=' ? 0 : 1;
}

void solve() {
  int n; scanf("%d", &n);
  std::vector<int> id(n);
  std::iota(id.begin(), id.end(), 0);
  int p = *std::max_element(id.begin(), id.end(), [&](int x, int y) {
    return qry(x, x, y, y) == -1;
  });
  std::vector<int> mx{0};
  for (int i = 1; i < n; i++) {
    int t = qry(mx[0], p, i, p);
    if (t == -1) 
      mx = std::vector<int>{i};
    else if (t == 0)
      mx.push_back(i);
  }
  int q = *std::min_element(mx.begin(), mx.end(), [&](int x, int y) {
    return qry(x, x, y, y) == -1;
  });
  printf("! %d %d\n", p, q);
  fflush(stdout);
}

int main() {
  int t; scanf("%d", &t); while (t--) {
    solve();
  }
}
```

---

## 作者：XYQ_102 (赞：0)

# C. Bitwise Operation Wizard

> **This is an interactive problem.**
> 
> There is a secret sequence $p_0, p_1, \ldots, p_{n-1}$, which is a permutation of $\{0,1,\ldots,n-1\}$.
> 
> You need to find any two indices $i$ and $j$ such that $p_i \oplus p_j$ is maximized, where $\oplus$ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).
> 
> To do this, you can ask queries. Each query has the following form: you pick arbitrary indices $a$, $b$, $c$, and $d$ ($0 \le a,b,c,d \lt n$). Next, the jury calculates $x = (p_a \mid p_b)$ and $y = (p_c \mid p_d)$, where $|$ denotes the [bitwise OR operation](https://en.wikipedia.org/wiki/Bitwise_operation#OR). Finally, you receive the result of comparison between $x$ and $y$. In other words, you are told if $x \lt y$, $x \gt y$, or $x = y$.
> 
> Please find any two indices $i$ and $j$ ($0 \le i,j \lt n$) such that $p_i \oplus p_j$ is maximum among all such pairs, using at most $3n$ queries. If there are multiple pairs of indices satisfying the condition, you may output any one of them.
> 
> $1 \le n \le 10^4$。

场上不会 C 的小丑。

  

发现直接讨论两个数是非常不好做的，所以我们可以一个一个来。

考虑我们可以通过 $O(n)$ 次询问找到 $n-1$，每次询问都是通过 $a,a,b,b$ 的形式，而在答案中选 $n-1$ 一定是不劣的。

进一步，我们可以通过与 $n-1$ 的或来找到一些与 $n-1$ 或起来最大的数 $id$，这些数满足他们在 $n-1$ 为 $0$ 的位置一定为 $1$，而异或中，我们还要求 $n-1$ 为 $1$ 的位置不能为 $1$，所以我们再在这些数中找到最小的那个就可以了。

后两次的操作也都可以在 $\Theta(n)$ 次询问内完成，于是我们就做完了。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N=1e5+5;
int id[N],tmp1,tmp2,cnt=0,n,T;
char ch;

void sol(){
  scanf("%d",&n);
  tmp1=cnt=0;tmp2=-1;
  for(int i=1;i<n;i++){
  	printf("? %d %d %d %d\n",tmp1,tmp1,i,i);
  	fflush(stdout);
  	ch=getchar();
  	while(ch!='='&&ch!='<'&&ch!='>') ch=getchar();
  	if(ch=='<') tmp1=i; 
  }
  for(int i=0;i<n;i++){
    if(i==tmp1) continue;
    if(!cnt){id[++cnt]=i;continue;}
    printf("? %d %d %d %d\n",tmp1,id[cnt],tmp1,i);
    fflush(stdout);
    ch=getchar();
    while(ch!='='&&ch!='<'&&ch!='>') ch=getchar();
    if(ch=='<') id[cnt=1]=i;
    else if(ch=='=') id[++cnt]=i;
  }
  tmp2=id[1];
  for(int i=2;i<=cnt;i++){
    printf("? %d %d %d %d\n",tmp2,tmp2,id[i],id[i]);
    fflush(stdout);
    ch=getchar();
    while(ch!='='&&ch!='<'&&ch!='>') ch=getchar();
    if(ch=='>') tmp2=id[i];
  }
  printf("! %d %d\n",tmp1,tmp2);
  fflush(stdout);
}

int main(){
  scanf("%d",&T);
  while(T--) sol();
  return 0;
}
```

---

## 作者：Coinred001 (赞：0)

# CF1936A. Bitwise Operation Wizard

好玩的交互。

> 题意：
> 给定 $0,1,\dots,n-1$ 的一个排列  每次可以选取四个数 $0 \leq a,b,c,d \leq n-1$，查询 $(p_a~|~p_b)$ 与 $(p_c~|~p_d)$ 之间的大小关系。要求在 $3n$ 次查询内找到两个数 $i,j$，使得 $p_i \oplus p_j$ 最大。
> 
首先考虑如何使两个数的异或最大。根据位运算的性质，我们不难得出:
$$
\begin{equation}
\max_{0\leq i,j <n}\left\{i \oplus j\right\} = 2^k-1\quad(2^{k-1} \leq n < 2^k)
\end{equation}
$$
在 $i,j$ 的第 $1 \sim k$ 位都不相同时取到该最大值。
$$
\begin{equation}
\max_{0\leq i,j <n}\left\{i~|~j\right\} = 2^k-1\quad(2^{k-1} \leq n < 2^k)
\end{equation}
$$
在 $i,j$ 的第 $1 \sim k$ 位都不为 $0$ 时取到该最大值。可以推出 $(1)$ 式取到最大值时 $(2)$ 式也取到最大值。

因为我们必然要使答案的第 $k$ 位为 $1$，那么我们要先找到一个第 $k$ 位为 $1$ 的数。因为我们能够查询大小关系，所以我们考虑找到排列中最大的一个数即 $n-1$ 的位置。

由 $a~|~a=a$ 可知，比较 $(p_a~|~p_a)$ 与 $(p_b~|~p_b)$ 的大小关系等价于查询 $p_a$ 与 $p_b$ 的大小关系。所以我们可以很容易的通过这样 $n-1$ 次比较找到最大值的位置。

接下来考虑找到数 $t=(2^k-1)\oplus(n-1)$ 的位置。容易知道 $t\oplus(n-1)=t~|~(n-1)=2^k-1$。
则 $t$ 与 $n-1$ 满足 $(1)(2)$ 两式的最大值条件。而在满足 $x~|~(n-1)=2^k-1$ 的 $x$ 中，$t$ 一定是最小的那个数（因为在 $n-1$ 取 $1$ 的位上 $t$ 一定取 $0$）。

所以我们考虑取出使得 $(n-1)|p_i$ 取最大值的所有位置，然后在这些位置中找到最小的数的位置，这个位置的数就是 $t$。可以知道比较的次数不会超过 $2(n-2)$。

最后我们就在 $3n$ 步内得到了 $n-1$ 与 $t$ 的位置，输出即可。

以上针对 $n \geq 4$，注意 $n=2$ 与 $n=3$ 的边界情形。

```cpp
inline char query(int p1_1,int p1_2, int p2_1,int p2_2)
{
	cout<<"? "<<p1_1-1<<' '<<p1_2-1<<' '<<p2_1-1<<' '<<p2_2-1<<endl;
	char op; cin>>op;
	return op; 
}
inline int ans_out(int p1,int p2)
{
	cout<<"! "<<p1-1<<' '<<p2-1<<endl;
	return 0;
} 
 
inline int Solve()
{
	#ifdef DEBUG
	printf("Debuging...\n");
	#endif
 
	cout.flush();
	cin>>n;
	char op;
	if(n==2) return ans_out(1,2);
	if(n==3)
	{
		op=query(1,2, 1,3);
		int k=(op=='>')?2:3;
		op=query(1,k, k,k^1);
		int l=(op=='>')?1:k^1;
		return ans_out(k,l);
	}
	
	int k=1;
	for(int i=2;i<=n;i++)
	{
		op=query(k,k, i,i);
		if(op=='<') k=i; 
	}
	
	vector<int> com;
	int l=(k==1)?2:1;
	com.push_back(l);
	for(int i=1;i<=n;i++)
	{
		if(i==k || i==l) continue;
		op=query(k,l, k,i);
		if(op=='<')
		{
			vector<int>().swap(com);
			l=i;
			com.push_back(l);
		}
		else if(op=='=')
			com.push_back(i);
	}
	l=com[0];
	for(int i=1;i<com.size();i++)
	{
		op=query(l,l, com[i],com[i]);
		if(op=='>') l=com[i];	
	}
	ans_out(k,l);
 
	return 0;
}
```

---

## 作者：modfisher (赞：0)

## 思路
我们发现，最大的异或值是固定的。设 $k$ 满足 $2^k\le n<2^{k+1}$，则结果一定为 $2^{k+1}-1$，且选择 $n-1$ 之后一定存在 $0\le a<n$，满足 $a\oplus (n-1)=2^{k+1}-1$。

证明：

即证 $0\le a=(n-1)\oplus(2^{k+1}-1)<n$。

因为 $n-1$ 和 $2^{k+1}-1$ 的二进制最高位都为 $2^k$，所以异或后，$2^k$ 位必定为 $0$，故 $a<2^k\le n-1<n$。$a>0$ 显然，得证。

所以我们可以先找 $n-1$ 的位置。如果我们询问 $a,a,b,b$，可以得到 $p_a\mid p_a$ 与 $p_b\mid p_b$ 的大小关系，即 $p_a$ 和 $p_b$ 的大小关系。因为 $n-1$ 恰好为原序列最大值，所以，可以通过 $n-1$ 次询问得到 $n-1$ 的位置。具体地，记录 $ans1$ 表示答案，如果 $p_{ans1}<p_i$，则将 $ans1$ 更新为 $i$。

接下来，我们要找到 $a$，即 $(n-1)\oplus(2^{k+1}-1)$ 的位置。

显然 $(n-1)\mid a=2^{k+1}-1$，且 $a$ 是满足该条件的数中最小的。换言之，要找到 $ans2$，使得 $p_{ans2}\mid p_{ans1}$ 最大且 $p_{ans2}$ 最小。与之前同理，只需 $2(n-1)$ 次询问。

所以，我们通过 $3n-3$ 此询问得到了答案。

## 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int T;
	cin >> T;
	while(T --){
		int n;
		cin >> n;
		int ans1 = 0;
		for(int i = 1; i < n; i ++){
			char res;
			cout << "? " << ans1 << " " << ans1 << " " << i << " " << i << endl;
			cin >> res;
			if(res == '<') ans1 = i;
		}
		int ans2 = 0;
		for(int i = 1; i < n; i ++){
			char res1, res2;
			cout << "? " << ans1 << " " << ans2 << " " << ans1 << " " << i << endl;
			cin >> res1;
			cout << "? " << ans2 << " " << ans2 << " " << i << " " << i << endl;
			cin >> res2;
			if(res1 == '<' || (res1 == '=' && res2 == '>')) ans2 = i;
		}
		cout << "! " << ans1 << " " << ans2 << endl;
	}
	return 0;
}
```

---

## 作者：huangrenheluogu (赞：0)

首先先考虑如何获得解。

发现这个交互是可以用来比较大小的。具体地，如果想比较 $a,b$ 之间的大小关系，只需要调用 `? a a b b` 即可。

考虑这个异或之后的最大值是容易求得的，所以不放确定一个数，然后寻找另外一个数就可以了。这个最后 $p_x\oplus p_y$ 的值我记作 $ans$。

确定哪一个数好呢？发现用比较大小的操作容易获得一个区间的最大值，不放我们取了这个区间的最大值，就是 $n-1$ 的位置 $x$，剩下的，就需要找到 $y,s.t.p_y\oplus (n-1)=ans$，其中 $ans$ 是需要的答案。

这时候，$p_y$ 是可以计算出来的了。我们就可以找一个排列的第 $k$ 大值，这个东西是 $O(n)$ 的。

细想其实是错误的，因为这里我们期望是平分序列的长度，期望是 $O(n)$ 的，这个比较次数的期望是 $2n$ 的，这样刚好达标，如果某一次随机偏了一点就不可行了。

考虑我们这个算法在求第 $k$ 大值的时候是不稳定的 $2n$ 次，结合求最大值的经验，发现求一个最值显然是 $n-1$ 次。

考虑我们要求的 $p_y$ 满足什么性质，二进制写开，发现正好是与 $p_x$ “互补”的。

于是，可以思考 $p_y$ 是否满足一些最值的性质呢？

有的，$p_y|p_x$ 刚刚好是 $ans$，而其他的 $p_z|p_x=ans$ 的值都满足 $p_z\ge p_y$。

我们只需要找出 $\{i|p_i\operatorname{or}p_x=ans\}$ 的集合就可以用 $n-1$ 次操作求出 $y$ 了。

考虑 $p_i|p_x$ 中，$ans$ 是最大值，又是一个最值，因此，可以用不超过 $3n-3$ 次的询问找到这个 $y$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e4 + 5;
int T, n, maxid, S, id[N], t, maxpos;
char res;
inline void query(int a, int b, int c, int d){
	printf("? %d %d %d %d\n", a, b, c, d);
	fflush(stdout);
	cin >> res;
}
inline void solve(){
	maxid = 0;
	S = 1;
	t = 0;
	while(S < n) S <<= 1;
	for(int i = 1; i < n; i++){
		query(maxid, maxid, i, i);
		if(res == '<') maxid = i;
	}
	maxpos = 0;
	id[t = 1] = 0;
	for(int i = 1; i < n; i++){
		query(maxid, maxpos, maxid, i);
		if(res == '<'){
			id[t = 1] = i;
			maxpos = i;
		}
		if(res == '='){
			id[++t] = i;
		}
	}
	maxpos = id[1];
	for(int i = 2; i <= t; i++){
		query(maxpos, maxpos, id[i], id[i]);
		if(res == '>') maxpos = id[i];
	}
	printf("! %d %d\n", maxpos, maxid);
	fflush(stdout);
}
signed main(){
	scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		solve();
	}
	return 0;
}
```

---

