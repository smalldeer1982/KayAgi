# XOR Construction

## 题目描述

You are given $ n-1 $ integers $ a_1, a_2, \dots, a_{n-1} $ .

Your task is to construct an array $ b_1, b_2, \dots, b_n $ such that:

- every integer from $ 0 $ to $ n-1 $ appears in $ b $ exactly once;
- for every $ i $ from $ 1 $ to $ n-1 $ , $ b_i \oplus b_{i+1} = a_i $ (where $ \oplus $ denotes the bitwise XOR operator).

## 样例 #1

### 输入

```
4
2 1 2```

### 输出

```
0 2 3 1```

## 样例 #2

### 输入

```
6
1 6 1 4 1```

### 输出

```
2 3 5 4 0 1```

# 题解

## 作者：SunnyYuan (赞：34)

这个题目赛场上交了 2 发，在赛后又交了 5 发才过，欢迎爆踩。

## 思路

看了一眼题解区，为啥都用了 Trie，（直接）贪心不香吗？

首先，我们都不难想到：

$$
\begin{aligned}
b_1 \oplus b_2 &= a_1\\
b_2 \oplus b_3 &= a_2\\
\cdots\\
b_j \oplus b_{j + 1} &= a_j\\
\end{aligned}
$$

把左右两边都异或起来可以推出：$b_1 \oplus b_{j + 1} = \bigoplus\limits_{i = 1}^{j}a_i$。

记前缀异或和 $sum_x = \bigoplus\limits_{i = 1}^{x}a_i$。

那么 $b_{j + 1} = b_1 \oplus sum_{j}$，那么实际上是只要确定了 $b_1$ 就可以算出所有的 $b_j$。

题目中要求要让 $b$ 在 $0\sim n - 1$ 之内，这实际上实在寻找一个 $b_1$ 使得异或出来的所有值越小越好，所以我们拆位，假设所有数字的第 $i$ 位为 $1$ 的个数大于为 $0$ 的个数，那我们最好异或上一个 $2^i$，这样可以使大部分数字变小。

## 代码

```cpp
/*******************************
| Author:  SunnyYuan
| Problem: D. XOR Construction
| OJ:      Codeforces - Educational Codeforces Round 157 (Rated for Div. 2)
| URL:     https://codeforces.com/contest/1895/problem/D
| When:    2023-11-04 09:06:50
| 
| Memory:  512 MB
| Time:    2000 ms
*******************************/

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 1; i < n; i++) {
        cin >> a[i];
        if (i) a[i] ^= a[i - 1];
    }
    a[0] = 0;
    int ans = 0;
    for (int i = 0; i < 31; i++) {
        int sum1 = 0, sum2 = 0;
        for (int j = 0; j < n; j++) {
            if (a[j] >> i & 1) sum1++;
            else sum2++;
        }
        if (sum1 > sum2) ans |= 1 << i;
    }
    for (int i = 0; i < n; i++) a[i] ^= ans;
    for (int i = 0; i < n; i++) cout << a[i] << ' ';
    return 0;
}

```

---

为什么一定可以到 $0\sim n - 1$，问的人太多了，我截取了我回答的照片：

![](https://cdn.luogu.com.cn/upload/image_hosting/kizcyi4q.png)

---

## 作者：_sunkuangzheng_ (赞：16)

$\Large \textbf{1. Hints}$

$\textbf{1.1 Hint 1}$

当 $b_1$ 确定时，$b_2 \sim b_n$ 都是已经确定的。

$\textbf{1.2 Hint 2}$

$b_1 \oplus b_2 = a_1,b_2 \oplus b_3 = a_2$，尝试合并相邻的式子，观察结果。

$\textbf{1.3 Hint 3}$

你只需要关心 $b$ 的最大值。

$\Large \textbf{2. Solution}$

由题目中的式子可知，$b_2 = b_1 \oplus a_1,b_3 = b_2 \oplus a_2,\ldots$，当 $b_1$ 确定时，整个 $b$ 数组都已经确定。

设 $c$ 是 $a$ 的前缀异或和数组，我们合并前缀式子，得到 $b_i = b_1 \oplus c_{i-1}$。显然的，如果存在 $i,j(i \ne j)$ 使得 $c_i = c_j$，那么必然无解。而题目保证有解，即 $c$ 数组互不相同且 $c_i \ne 0$，也即对于任何 $b_1$ 都满足 $b$ 所有元素互不相同，我们只需要考虑 $b_i \le n-1$ 这一限制。

我们发现所有 $b_i \le n-1$ 等价于 $\max\{b_i\} \le n-1$，因此你只需要枚举 $b_1$ 的值，将 $c_1 \sim c_{n-1}$ 插进 01-trie，每次查询 $b_1 \oplus c_i$ 的最大值即可。时间复杂度 $\mathcal O(n \log V)$。

$\Large \textbf{3. Code}$

```cpp
/**
 *    author: sunkuangzheng
 *    created: 03.11.2023 23:00:09
**/
#include<bits/stdc++.h>
using namespace std;
const int N = 6e6+5;
int t,n,ch[N][2],tot,val[N],a[N],b[N],ans;
void ins(int x){
    int s = 0;
    for(int i = 22;i >= 0;i --){
        val[s] ++;
        if(!ch[s][(x >> i) & 1]) ch[s][(x >> i) & 1] = ++tot;
        s = ch[s][(x >> i) & 1];
    }val[s] ++;
}int qry(int x){
    int s = 0,ans = 0;
    for(int i = 22;i >= 0;i --){
        int k = (x >> i) & 1;
        if(ch[s][!k]) s = ch[s][!k],ans += (1 << i);
        else s = ch[s][k];
    }return ans;
}
int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    cin >> n;
    for(int i = 1;i < n;i ++) cin >> a[i],b[i] = a[i] ^ b[i-1],ins(b[i]);
    for(int i = 0;i < n;i ++) if(qry(i) < n) {ans = i;break;}
    cout << ans << " ";
    for(int i = 1;i < n;i ++) cout << (ans ^ b[i]) << " ";
}
```

---

## 作者：Wf_yjqd (赞：10)

好久没场切 D 了，罚时好多啊。

是一种比较特别的做法。

------------

发现 $b$ 中 $0$ 的位置极为重要，是一个突破点。

$0$ 相当于把 $b$ 分成两部分（可能没有）。

前一部分的 $b$ 为 $0$ 之前 $a$ 的后缀异或和，后一部分的 $b$ 为 $0$ 之后 $a$ 的前缀异或和。

------------

拓展：

赛时没好好读题，想了半天无解的情况（题目保证没有）。

如果 $a$ 中存在一个区间异或和为 $0$，无论 $b$ 中的 $0$ 放在哪里，都一定会出现两个相同的数。（简单的分讨）

所以只要有解，$0$ 放在任意位置都不会有两个相同的 $b$。

------------

我们只需要找到一个合适的位置放入 $0$，使得相应的 $b$ 中没有大于等于 $n$ 的数。

考虑这样的一个位置需要满足什么。

显然只需要以他为结尾的最大后缀异或和小于等于 $n$，且以他为开头的最大前缀异或和小于等于 $n$。

用 01Tire 维护即可。

------------

赛后发现有极其简单的做法。

好像也有其他 01Trie 的做法，但比我这个难理解（反正我没理解）。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+84;
int n,a[maxn],sum,cnt;
struct Point{
    int son[2],cnt,id;
    inline void clear(){
        son[0]=son[1]=cnt=id=0;
        return ;
    }
}Trie[maxn*26];
struct Trie_Tree{
    inline void Modify(int x){
        int id=1,t;
        for(int i=21;i>=0;i--){
            t=(x>>i)&1;
            if(!Trie[id].son[t])
                Trie[id].son[t]=++cnt;
            id=Trie[id].son[t];
            Trie[id].cnt++;
        }
        Trie[id].id=x;
        return ;
    }
    inline int Find(int x){
        int id=1,t;
        for(int i=21;i>=0;i--){
            t=(x>>i)&1;
            if(Trie[Trie[id].son[t^1]].cnt)
                id=Trie[id].son[t^1];
            else
                id=Trie[id].son[t];
        }
        return Trie[id].id^x;
    }
}Sherry;
bitset<maxn> ablE;//i和i+1之间能不能放0
int main(){
    scanf("%d",&n);
    for(int i=1;i<n;i++)
        scanf("%d",&a[i]);
    cnt=1;
    sum=0;
    Sherry.Modify(0);
    for(int i=1;i<n;i++){
        sum^=a[i];
        Sherry.Modify(sum);
        if(Sherry.Find(sum)>=n)
            ablE[i]=1;
    }
    for(int i=0;i<=cnt+2;i++)
        Trie[i].clear();
    cnt=1;
    sum=0;
    Sherry.Modify(0);
    for(int i=n-1;i>=1;i--){
        sum^=a[i];
        Sherry.Modify(sum);
        if(Sherry.Find(sum)>=n)
            ablE[i-1]=1;
    }
    for(int i=0;i<n;i++)
        if(!ablE[i]){
            for(int j=i-1;j>=1;j--)
                a[j]^=a[j+1];
            for(int j=i+2;j<n;j++)
                a[j]^=a[j-1];
            for(int j=1;j<=i;j++)
                printf("%d ",a[j]);
            printf("0");
            for(int j=i+1;j<n;j++)
                printf(" %d",a[j]);
            break;
        }
    return 0;
}
```


---

## 作者：xxxxxxxb (赞：4)

不难想到把题目式子从差分的形式写成前缀和，即：

$b_i = b_{i-1} \oplus a_i $

发现 $b_i$ 差不多就是把 $a_i$ 进行前缀和，那么唯一不知道的就是 $a_0$。

记 $\bigoplus_1^i a_i = c_i$，就是不包含 $a_0$ 异或前缀和

首先想到可以枚举 $a_0$，然后把每一项都异或一遍看看是否超出 $n$，时间复杂度为 $O(n^2)$。

想到这是一个异或问题求极值，可以使用[01trie](https://www.luogu.com.cn/problem/P4551)解决。

对每一个数进行拆位，然后放在字典树上，求异或最大值就尽量每次向和这个数当前一位不同的地方走。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
int read() {
	int res = 0,f = 1;
	char c = getchar();
	while(!isdigit(c)) {
		if(c== '-') f = -1;
		c = getchar();
	}
	while(isdigit(c)) {
		res = res * 10 + c - '0';
		c = getchar();
	}
	return res*f;
}
const int N = (int)2e6+7;
int n,pre[N],cnt; //pre就是文中的c
bool vis[N],be[N];
int net[N][2];
void ins(int x) {
	int p = 0;
	for(int i = 30;i >= 0;--i) {
		bool to = x & (1 << i);
		if(!net[p][to]) net[p][to] = ++cnt;
		p = net[p][to];
	}
}
int chk(int x) {
	int p = 0,res = 0;
	for(int i = 30;i >= 0;--i) {
		bool to = x & (1 << i);
		if(net[p][!to]) {
			res |= (1 << i);
			p = net[p][!to];
		} else {
			p = net[p][to];
		}
	}
	return res;
}
int main() {
	n = read();
	ins(0);
	for(int i = 1;i <= n-1;++i) {
		pre[i] = pre[i-1] ^ read();
		ins(pre[i]);
	}
	for(int i = 0;i <= n-1;++i) {
		if(chk(i) < n) {
			printf("%d ",i);
			for(int j = 1;j <= n-1;++j) {
				printf("%d ",i^pre[j]);
			}
			return 0;
		}
	}
	return 0;
}
```

---

## 作者：CQ_Bob (赞：3)

## 分析

对于异或，有性质 $a \oplus b = c,a \oplus c =b,a \oplus a =0$。则对于 $a_i \oplus a_{i+1}$，其表示的结果就是 $b_{i}  \oplus b_{i+2}$。做一个前缀异或和，就能够得到 $b_1$ 与 $b_2,b_3,\dots,b_n$ 的异或结果。

考虑枚举 $b_1$，因为在有解的情况下 $b_1  \oplus b_i$ 的结果都互不相同。所以我们只需要找到一个 $j$，使 $b_1  \oplus b_j$ 最大。若这个值 $\ge n$，则不满足；若这个值 $\le n-1$，则 $b_1$ 枚举的这个值满足，输出此时的 $b$ 即可。

找最大异或对，使用 Trie 就可以了。

## 代码

[Link](https://codeforces.com/contest/1895/submission/231179335)

---

## 作者：cjh20090318 (赞：3)

作为一个 Div. 2 的 D 题，不是很难的题。

## 题意

标签：字典树，贪心。

给你 $n-1$ 个正整数 $a_1,a_2,\dots,a_{n-1}$。

你需要构造一个序列 $b_1,b_2,\dots,b_n$ 满足下列要求：

- $0 \sim n-1$ 中的每个整数刚好在 $b$ 中出现一次。
- $\forall i\in [1,n) \cap \mathbb{N}^{*},b_i \oplus b_{i+1} = a_i$。

输出任意一组解即可，保证有解。

## 分析

设 $s_i = a_1 \oplus a_2 \oplus \dots \oplus a_i$。

于是 $b_i = b_1 \oplus a_1 \oplus a_2 \oplus \dots \oplus a_i = b_1 \oplus s_{i-1}$。

保证有解很显然的一个性质是 $\forall i \in [1,n),s_i \neq 0$。

如果 $s$ 存在一个值为 $0$，就会导致 $b$ 数组中会有两个元素相同，将不满足每个数刚好出现一次。

数字重复出现我们就不需要考虑了，接下来需要考虑 $b$ 的范围。

下界是很容易满足的，只要 $b_1 \ge 0$，那么 $b$ 都会大于等于 $0$。

接下来考虑上界，第一个条件要让 $b_i < n$ 恒成立，其实就是让 $(b_1 \oplus s_{i-1})_{\max} < n$ 恒成立。

所以说直接枚举 $b_1 \in [0,n)$，利用字典树可以在 $O(\log n)$ 的时间内求出 $(b_1 \oplus s_{i-1})_{\max}$，判断如果符合条件直接输出就行了。

时间复杂度 $O(n \log n)$，空间复杂度 $O(n \log n)$。

## 代码

```cpp
//the code is from chenjh
#include<cstdio>
#define MAXN 200002
using namespace std;
int n;
int a[MAXN];
int tot=1,trie[MAXN<<5][2];//字典树空间要开够。
void ins(const int x){//字典树插入。
	int u=1;
	for(int i=20;i>=0;i--){
		bool v=(x>>i)&1;
		if(!trie[u][v]) trie[u][v]=++tot;
		u=trie[u][v];
	}
}
int ask(const int x){//查找和 x 异或能得到最大值的数。
	int u=1,ret=0;
	for(int i=20;i>=0;i--){
		bool v=(x>>i)&1;
		if(trie[u][v^1]) u=trie[u][v^1],ret|=(v^1)<<i;
		else if(trie[u][v]) u=trie[u][v],ret|=v<<i;
	}
	return ret;
}
int main(){
	scanf("%d",&n);
	for(int i=2;i<=n;i++) scanf("%d",&a[i]),a[i]^=a[i-1],ins(a[i]);//直接前缀和，省去 s 数组。
	for(int b=0;b<n;b++)if((b^ask(b))<n){//满足上界，直接输出答案。
		for(int i=1;i<=n;i++) printf("%d ",b^a[i]);
		return 0;
	}
	return 0;
}
```

---

## 作者：Fgighkcgrfox (赞：1)

# CF1895D XOR Construction 题解

[题目链接](https://www.luogu.com.cn/problem/CF1895D)

## 思路

假设 $b_i=0$。

由 $a_i=b_i\oplus b_{i+1}\Rightarrow b_{i+1}=b_i\oplus a_i$，可以把 $b$ 数组全部算出来了。这个时候 $b$ 数组一定是满足题目中第 $2$ 个条件的，只需在异或不变的情况下把它变成一个满足题意的排列即可。

然后我们考虑 $b_0$ 中如果有一位改变了，那么为了保证异或不变，后面的 $b_i$ 的相同一位都要改变。我们统计一下从 $1$ 到 $n$ 每一位 $1$ 的数量，在看一下目前 $b$ 数组中每一位 $1$ 的数量。如果说不相同，就对 $b$ 数组中所有的元素的这一位取反。

由于题目保证了一定存在解，所以可以证明这样得出来的是正确的答案。

首先就是很显然 $b$ 中不存在相同的元素。不然无论 $b_0$ 怎么改变，一定存在相同的元素,不符合题意。

然后就是判断会不会存才 $b_i\ge n$ 的情况。可以根据每一位 $0$ 和 $1$ 的个数是否相同讨论一下。如果不同，答案一定是唯一的。如果 $n$ 是偶数，那么 $0$ 和 $1$ 换一下不会有影响。证毕。

## CODE

```cpp
n=read();logg=ceil(log(n*2.0)/log(2.0)); 
for(int i=1;i<n;i++){
	a[i]=read();b[i]=b[i-1]^a[i];
	for(int j=0;j<=logg;j++){
		if(b[i]&(1<<j))tong[j]++;
		if(i&(1<<j))tong[j]--;
	}
}
for(int i=logg;i>=0;i--)
	if(tong[i])ans^=(1<<i);
for(int i=0;i<n;i++)printf("%d ",b[i]^ans);
```

---

## 作者：Leeb (赞：1)

### 题意简述

去看[题面](https://www.luogu.com.cn/problem/CF1895D)上的翻译，说的很清楚，这里不做赘述。

### 解题思路

这题我想了挺久的。

根据题目给的 $a_i=b_i\oplus b_{i+1}$ 可以知道，$a_1\oplus a_2=(b_1\oplus b_2)\oplus(b_2\oplus b_3)=b_1\oplus b_3$，进而推导出 $a_1\oplus a_2\oplus a_3\oplus\dots\oplus a_i=(b_1\oplus b_2)\oplus(b_2\oplus b_3)\oplus(b_3\oplus b_4)\oplus\dots\oplus(b_i\oplus b_{i+1})=b_1\oplus b_{i+1}$，那么我们就可以设 $s_i$ 为 $a_i$ 的前缀异或和，即 $s_i=a_1\oplus a_2\oplus a_3\oplus\dots\oplus a_i$，则 $s_i=b_1\oplus b_{i+1}$，进而得出 $b_{i+1}=b_1\oplus s_i$ 和 $b_1=b_{i+1}\oplus s_i$。

由此，我们可以知道：只需要确定 $b_1$ 的值，就能确定整个 $b$ 数组的值。

如何确定 $b_1$ 的值？

我们可以通过确定 $b_1$ 的每一个二进制位来确定他，即通过 $b_i$ 和 $s_i$ 的每一位是 $0$ 还是 $1$ 来确定 $b_1$。（下述第 $i$ 位为二进制从右往左数第 $i$ 位）

我们知道，异或运算法则是相同为 $0$，不同为 $1$，且 $b_i\in [0,n-1]$，那么我们就可以统计 $[0,n-1]$ 中有多少个数第 $i$ 位为 $1$ ，记其为 $cnt1_i$，和 $s_i$ 中有多少个数第 $i$ 位为 $1$（注意：$s_i$ 当中的 $i$ 和第 $i$ 位的 $i$ 不是同一个 $i$），记其为 $cnt2_i$，如果对于第 $i$ 位，$cnt1_i=cnt2_i$，则说明 $b_1$ 的第 $i$ 位为 $0$，反之为 $1$，这样我们就可以确定下 $b_1$。

下面说说如何判断一个数 $x$ 的第 $i$ 位为 $1$ 还是 $0$。

其实很简单，只要判断 $x\&2^i$ 是否为 $0$，如果为 $0$ 说明 $x$ 的第 $i$ 位为 $0$，如果不是 $0$ 则说明 $x$ 的第 $i$ 位为 $1$。

### 参考代码

```cpp
// -- More and More vegetales, what should I do?
// -- AFO! AFO YYDS!
// Code Author : Leeb
// #include <bits/stdc++.h>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 300005
#define M 25
#define inf 0x3f3f3f3f
#define endl '\n'
#define elif else if
// #define int long long 
#define ll long long
#define mem(a, x) memset(a, x, sizeof(a))
using namespace std;
int n, a[N], s[N], b[N], cnt1[M], cnt2[M];
inline int in() {
    int a = 0; bool f = 0; char ch = getchar();
    while (ch < '0' || ch > '9')
        {if (ch == '-') f = 1; ch = getchar();}
    while (ch >= '0' && ch <= '9')
        a = (a << 1) + (a << 3) + (ch ^ 48), ch = getchar();
    if (f) return ~a + 1;   
    return a;
}
inline void init() {
    n = in();
    for (int i = 1; i < n; ++i) a[i] = in();
    for (int i = 1; i < n; ++i) s[i] = s[i - 1] ^ a[i];
}
inline int pow(int a, int b) {
    int ans = 1;
    while (b) {
        if (b & 1) ans = ans * a;
        a = a * a;
        b >>= 1;
    }
    return ans;
}
inline void work() {
    for (int i = 0; i < n; ++i) 
        for (int j = 0; j <= 19; ++j)
            if (i & pow(2, j)) cnt1[j]++;
    for (int i = 1; i < n; ++i)
        for (int j = 0; j <= 19; ++j)
            if (s[i] & pow(2, j)) cnt2[j]++;
    for (int i = 0; i <= 19; ++i) 
        if (cnt1[i] == cnt2[i]) continue;   
        else b[1] += pow(2, i);
    for (int i = 2; i <= n; ++i) b[i] = b[1] ^ s[i - 1];
    for (int i = 1; i <= n; ++i)
        printf("%d ", b[i]);
}
signed main() {
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    int t = 1;
    while (t--) {
        init();
        work();
    }
    return 0;
}
```





---

## 作者：Sumikura (赞：1)

位运算相关，所以考虑对于每一位拆开来看，我们记 $cnt_i$ 表示对于 $1$ ~ $N$ 的数中，第 $i$ 位上 $1$ 的数量。那么题意化解为：

> 给定一个长度为 $N - 1$ 的 $01$ 串 $a_i$，让你构造出一个长度为 $N$ 的 $01$ 串 $b_i$ 使得 $b_i$ 为 $a_i$ 的异或差分数组，并且 $\sum b_{i, j} = cnt_i$。

> 注：下文的 $a$ 和 $b$ 都是转化题意后的含义了。

这就是个很简单的问题了，我们考虑 $a_{i, j}$ 的含义：

- 若 $a_{i, j} = 1$，则 $b_{i, j} = b_{i, j + 1}$； 

- 若 $a_{i, j} = 0$，则 $b_{i, j} \not= b_{i, j + 1}$。

那么所有的 $a_{i, j} = 1$ 把 $b_i$ 分成了 $\sum a_{i, j}$ 个连续段。要求连续段内所有数的值必须相同，相邻连续段的值不能相同。也就是说 $b_i$ 要么是 $000 \dots 0111 \dots 1000 \dots$ 的形式，要么是 $111 \dots 1000 \dots 0111\dots$ 的形式。既然 $\sum b_{i, j} = cnt_i$，那么两种分别试一下就可以了。

问题来了，如果两种形式都满足 $\sum b_{i, j} = cnt_i$，怎么办？

我们发现这种情况的出现当且仅当 $2 ^ i | n$，那么对于这种情况，必然是 $0$ 覆盖一半，$1$ 覆盖另一半，对于一个位置两种形式要么是 $1$ 要么是 $0$，不存在两种形式下都是 $0$ 的位置。也就是说：**两种形式要么都合法要么都不合法**，而题目保证有解，所以两种形式随便填都可以。

[代码](https://codeforces.com/contest/1895/submission/231201809)很好写，就不写注释了。

---

## 作者：LYY_yyyy (赞：1)

我们发现我们可以通过求前缀异或和得到 $b_1$ 和 $b_{2\cdots n}$ 之间的关系。我们开一个 $cnts$ 数组，$cnts_i$ 表示 $[0,n-1]$ 中第 $i$ 位 $1$ 的个数。我们考虑枚举 $b_1$ 的每一位。我们先将 $a$ 数组做前缀异或和，于是对于 $i\in [2,n]$，就有 $b_1 \oplus b_i=a_{i-1}\Rightarrow b_1 \oplus a_{i-1}=b_i$。对于 $b_1$ 的第 $i$ 位（从0开始），我们算出 $j \in [1,n-1]$， 这一位上 $a_j$ 为 $1$ 的数量，记为 $cnt_i$。若 $cnt_i=cnts_i$，则 $b_1$ 的这一位为 $0$。否则因为一定有解，$b_1$ 的这一位为 $1$。求出 $b_1$ 之后反推出 $b$ 数组就好了。于是本题就做完了。时间复杂度 $O(n\log V)$。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int a[200010];
int cnts[21];
int main()
{
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=2;i<=n;i++) cin>>a[i],a[i]^=a[i-1];
	for(int i=0;i<=20;i++) for(int j=0;j<n;j++) if((j>>i)&1) cnts[i]++;
	int ans=0;
	for(int j=0;j<=20;j++)
	{
		int cnt=0;
		for(int i=2;i<=n;i++) if((a[i]>>j)&1) cnt++;
		if(cnt!=cnts[j]) ans+=(1<<j); 
	}
	cout<<ans<<' ';for(int i=2;i<=n;i++) cout<<(ans^a[i])<<' ';
	return 0;
}
```


---

## 作者：ax_by_c (赞：1)

# 题目描述

给出一个长度为 $n-1$ 的数列 $a$，保证 $0 \le a_i \le 2\times n$。

你需要构造一个长度为 $n$ 的数列 $b$，保证 $0 \le b_i \le n-1$，且每个数只出现一次，使得 $b_i \oplus b_{i+1}$ 的结果等于 $a_i$。

保证有解。

# 解题思路

首先，不考虑限制的情况下，后缀异或和显然是合法的，设为 $s$。

备注：最后一个位置放零。

如果有两个相同的后缀异或和，就不符合要求了，并且没有办法让它们变得不同。

既然有解，则肯定没有这样的情况。

但是还有一个范围限制，不能超过 $n-1$，怎么办？

显然，每个位置同时异或上一个数结果不变。

所以有一个朴素的做法，枚举异或上的那个数，设为 $x$。

因为这个数实质上就是最后一个数，所以可以确定范围。

然后一个个判断是否有 $s_i \oplus x \ge n$，有则不合法，没有则合法。

找到一个合法的 $x$ 后推出答案即可。

但是这个做法是 $O(n^2)$ 的，考虑优化 $x$ 的判断过程。

首先，每个判断是没有意义的，可以直接判断 $\max(s_i \oplus x) \ge n$。

那么问题就变成了求前面的东西。

那不就是最大异或值吗？用一个字典树即可。

综上所述，判断过程被优化到了 $O(\log_2 n)$，总时间复杂度 $O(n \log_2 n)$

---

## 作者：carp_oier (赞：0)

## advertisement

这位靓仔，你都来看我的题解了，为什么不来[我的博客](https://www.cnblogs.com/carp-oier/p/CF1895D.html)看看呢。

## analysis

看到这个类似差分的样子，想着对它进行转化，通过对题目给出的式子进行变形，我们可以得到下面的式子。

$$a_i = b_i \bigoplus b _ {i + 1} $$

$$\begin{aligned} b_{i+ 1} &= b_i \bigoplus a_i \\ &= b_ {i - 1} \bigoplus a_{i - 1} \bigoplus a_i  \\ &= (\bigoplus_{j = 1}^{i} a_j) \bigoplus b_1 \end{aligned}$$

记 $c_i$ 为 $\bigoplus _ {j = 1}^{i} a_j$。

得到原式：$b_i = c_{i - 1} \bigoplus b_1$。

所以我们要关心的只有 $b_1$ 这一个值。然后我们可以想到要维护异或最大值，不难想到用 01-trie 解决它。

## code time
flush 是因为我用的快读快写中的 getchar 和 putchar 是自己手写的，所以有这个函数，大家可以直接忽略。（想了想还是得放一下我这 for 家族，不然看不懂。/lh）

```cpp
#define ll long long
#define rl register ll
#define fom(i, a) for(rl i=a; i; -- i)
#define foa(i, a, b) for(rl i=a; i < b; ++ i)
#define fos(i, a, b) for(rl i=a; i <= b; ++ i)
#define fop(i, a, b) for(rl i=a; i >= b; -- i) 

const ll N = 2e6 + 10;

ll n, idx, tr[2][N], a[N], s[N];

inline void insert(ll x)
{
    ll p = 0;
    fop(i, 30, 0)
    {
        bool u = x & (1 << i);
        if(!tr[u][p]) tr[u][p] = ++ idx;
        p = tr[u][p];
    }
}

inline ll check(ll x)
{
    ll p = 0, res = 0;
    fop(i, 30, 0)
    {
        bool u = x & (1 << i);
        if(tr[!u][p]) res |= (1 << i), p = tr[!u][p]; else p = tr[u][p];
    }
    return res;
}

int main()
{
   // freopen("1.in", "r", stdin); 
    read(n); insert(0); foa(i, 1, n) read(a[i]); foa(i, 1, n) s[i] = s[i - 1] ^ a[i], insert(s[i]);
    foa(i, 0, n) if(check(i) < n) { ww(i), ws; foa(j, 1, n) ww(i ^ s[j]), ws; return flush(), 0; }
    return flush(), 0;
}
```

---

## 作者：Feryquitous (赞：0)

记 $c$ 为 $a$ 数组的前缀异或数组。

那么 $b_1 \operatorname{xor} b_i=c_{i-1}$。

即 $b_i=b_1 \operatorname{xor} c_{i-1}$。

可以枚举 $b_1$，如果当前 $b_1$ 合法，即可构造。

注意题目保证有解，所以合法当且仅当 $\max \{b_1 \operatorname{xor} c_{i-1}\}<n$。

这个限制可以用字典树维护。

---

## 作者：DerrickLo (赞：0)

考虑拆位。

拆完位后转换为另外一个问题：

> 给定一个数组 $a'$，要求构造一个数组 $b'$ 使得 $b'[i]\oplus b'[i+1]=a'[i]$，并且 $a'$ 和 $b'$ 中每个数都是 $0$ 或 $1$。

那么我们知道：

- 如果 $a'[i]$ 为 $0$，那么 $b'[i]=b'[i+1]$

- 如果 $a'[i]$ 为 $1$，那么 $b'[i]\ne b'[i+1]$

显然我们如果知道 $b'[1]$ 的值就能知道 $b'$ 所有数的值。

那么我们统计 $0$ 到 $n-1$ 中这一位有多少个是 $0$，多少个是 $1$，记为 $cnt$，然后将 $b'[1]$ 赋值为 $0$ 后算出 $b'$ 所有的值，判断 $b'$ 中的 $1$ 的个数是否等于 $cnt$，如果不等就将 $b'$ 中的所有数取反。

这样就能构造出原数组了。

```cpp
#include<bits/stdc++.h> 
#define int long long 
using namespace std;
int n,a[200005],ans[200005],cnt[2005],mx[200005];
signed main(){
	cin>>n;
	for(int i=1;i<n;i++)cin>>a[i];
	for(int i=1;i<n;i++){
		int noww=i,cntt=1;
		while(noww){
			if(noww%2==1)cnt[cntt]++;
			cntt++;
			noww/=2;
		}
	}
	int hl=__lg(n)+1;
	for(int i=hl;i;i--){
		int hv=1<<(i-1);
		mx[1]=1;
		for(int j=2;j<=n;j++)if(a[j-1]&hv)mx[j]=mx[j-1]^1;else mx[j]=mx[j-1];
		int cntt=0; 
		for(int j=1;j<=n;j++)if(mx[j])cntt++;
		if(cntt==cnt[i]){
			for(int j=1;j<=n;j++)if(mx[j])ans[j]+=hv;
			continue;
		}
		cntt=0;
		mx[1]=0;
		for(int j=2;j<=n;j++)if(a[j-1]&(1<<(i-1)))mx[j]=mx[j-1]^1;else mx[j]=mx[j-1];
		for(int j=1;j<=n;j++)if(mx[j])cntt++;
		if(cntt==cnt[i]){
			for(int j=1;j<=n;j++)if(mx[j])ans[j]+=hv;
		}
	}
	for(int i=1;i<=n;i++)cout<<ans[i]<<" ";
	return 0;
} 
```

---

