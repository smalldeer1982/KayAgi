# Brooklyn Round 1 & NNOI Round 1 A - Flying Flower

## 题目背景

飞花令启动！

#### 请注意本题特别的时间限制。

**数据中存在 $k$ 不是质数的情况，对于这样的询问回答 `Z`。**

## 题目描述

小 X 和小 Z 玩了飞花令，想要将其变成数学，一共进行 $q$ 轮，规则如下：

+ 开始时选择质数 $k$ 作为关键数。

+ 小 X 有一个长度为 $n$ 的序列 $a$，小 Z 有一个长度为 $m$ 的序列 $b$。

+ 小 X 先手，小 Z 后手。

+ 两人要从自己的序列中选择一个数满足其质因子含有 $k$ 且比上一个人报的数大的数报出（第一个数可以是质因子含有 $k$ 的任何一个数）。

+ 无数可报的人输。

他想问你，如果两个人都采用最优策略，以这些 $k$ 作为关键数，谁能胜利？



## 说明/提示

**本题采用捆绑测试。**

+ Subtask 1（40pts）：$1 \le n,m,q \le 10^3，1 \le a_i,b_i,k \le 10^3$。

+ Subtask 2（20pts）：$k \le 10$。

+ Subtask 3（20pts）：$q = 1$。

+ Subtask 4（20pts）：无特殊限制。

对于 $100\%$ 的数据，$1 \le n,m,q \le 5 \times 10^5,1 \le a_i,b_i,k \le 8 \times 10^6$。

## 样例 #1

### 输入

```
5 5 2
10 20 30 40 50
5 10 15 20 25
5
11
```

### 输出

```
X
Z```

# 题解

## 作者：_hud (赞：5)

# [题解：P12677 Brooklyn Round 1 & NNOI Round 1 A - Flying Flower](https://luogu.com.cn/problem/P12677)

## 题目大意

给定两个序列 $a$（长度为 $n$）和 $b$（长度为 $m$），进行 $q$ 次游戏，每次游戏给定一个整数 $k$。规则如下：双方轮流报数，报的数必须来自自己对应的序列，且该数的质因子要包含 $k$，并且严格大于对方上一个人报的数。小 X 先手，小 Z 后手。若某人无数可报则该人输。若 $k$ 不是质数，直接判定小 Z 获胜。

对于每个查询 $k$，在两人都采用最优策略的前提下，判断哪方必胜。

## 思路分析

首先，对于给定的整数 $k$，分别定义：

$$
A_k \;=\;\{\,a_i\mid k\mid a_i\,\},\quad B_k \;=\;\{\,b_i\mid k\mid b_i\,\},
$$

即 $A_k$ 和 $B_k$ 分别是序列 $a$ 与 $b$ 中所有能被 $k$ 整除的元素集合。

分析题意，分类讨论：

1. $k$ 不是质数。直接输出 `Z` 即可。
2. $A_k$ 为空，即序列 $a$ 中没有一个数满足其质因子含有 $k$。直接输出 `Z` 即可。
3. $A_k$ 不为空时，若：
   - $\max(A_k)\ge \max(B_k)$，小 X 可以第一步直接报出 $\max(A_k)$。由于 $\max(A_k)\ge \max(B_k)$，小 Z 在 $B_k$ 中找不到大于 $\max(A_k)$ 的数，故只能认输，小 X 获胜。
   - 反之同理，若 $\max(A_k)<\max(B_k)$，则无论小 X 第 一步报出哪一个 $x\in A_k$，由于 $x\le \max(A_k)<\max(B_k)$，小 Z 都可以直接报出 $\max(B_k)$，此时小 X 无法报出大于 $\max(B_k)$ 的数，小 Z 获胜。

分析完思路，再来讲讲如何实现。我们可以用线性筛预处理出所有质数，然后再对每一个序列 $a$ 和序列 $b$ 中的数进行质因数分解，计算出 $A_k$ 和 $B_k$ 即可。具体可以看代码。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
struct IO { // 不重要的快读快写
    #define SIZE (1 << 20)
    #define isd(x) ((x) > 47 && (x) < 58)
    char buf[SIZE], pbuf[SIZE], *p1, *p2, *pp;
    IO() : p1(buf), p2(buf), pp(pbuf) {}
    ~IO() { fwrite(pbuf, 1, pp - pbuf, stdout); }
    inline int gc() {
        if(p1 == p2) p2 = (p1 = buf) + fread(buf, 1, SIZE, stdin);
        return p1 == p2 ? ' ' : *p1++;
    }
    inline int read(int &x) {
        x = 0; char c;
        for(c = gc(); !isd(c); c = gc());
        for(; isd(c); c = gc()) x = (x << 1) + (x << 3) + (c & 15);
        return x;
    }
    inline void push(const char &c) {
        if(pp - pbuf == SIZE) {
            fwrite(pbuf, 1, SIZE, stdout);
            pp = pbuf;
        }
        *pp++ = c;
    }
} io;
const int M = 8e6 + 10;
bitset<M> isp;        // isp[i] 标记 i 是否为质数
int pn[M >> 1], cnt;  // pn[] 存储所有质数，cnt 为质数个数
int maxa[M], maxb[M]; // maxa[p] 表示序列 a 中能被质因子 p 整除的数的最大值，maxb 同理
signed main() {
    // 线性筛求质数
    isp.set();
    isp[0] = isp[1] = 0;  // 0、1 不是质数
    for(int i = 2; i < M; ++i) {
        if(isp[i]) pn[++cnt] = i;
        for(int j = 1; j <= cnt && 1ll * i * pn[j] < M; ++j) {
            isp[i * pn[j]] = 0;
            if (i % pn[j] == 0) break;
        }
    }
    int n, m, q; io.read(n), io.read(m), io.read(q);
    // 处理序列 a，更新 maxa[p]
    for(int i = 1; i <= n; ++i) {
        int raw, tmp; raw = io.read(tmp);
        // 质因数分解
        for(int j = 1; 1ll * pn[j] * pn[j] <= raw; ++j)
            if(tmp % pn[j] == 0) {
                tmp /= pn[j]; 
                // 如果 pn[j] 是 raw 的一个质因子，则更新 maxa[pn[j]]
                maxa[pn[j]] = max(maxa[pn[j]], raw);
                while(tmp % pn[j] == 0) tmp /= pn[j]; // 去除该质因子所有次幂
            }
        if(tmp > 1) maxa[tmp] = max(maxa[tmp], raw);
        
    }
    // 处理序列 b，更新 maxb[p]
    for(int i = 1; i <= m; ++i) {
        int raw, tmp; raw = io.read(tmp); 
        for(int j = 1; 1ll * pn[j] * pn[j] <= raw; ++j)
            if(tmp % pn[j] == 0) {
                tmp /= pn[j], maxb[pn[j]] = max(maxb[pn[j]], raw);
                while (tmp % pn[j] == 0) tmp /= pn[j];
            }
        if(tmp > 1) maxb[tmp] = max(maxb[tmp], raw);
    }
    while(q--) {
        int k; io.read(k);
        if(!isp[k] || !maxa[k]) { io.push('Z'), io.push('\n'); continue; }
        io.push(maxa[k] >= maxb[k] ? 'X' : 'Z'), io.push('\n');
    }
    return 0; // 完结撒花
}
```

---

## 作者：wyyinput (赞：2)

## 转化题意
不难想到，小 X 和小 Z 在最开始时就报出最大的满足要求的数肯定最优，因为数可以重复使用。所以题目就是让我们比较他们两个人谁的符合要求的数更大。具体地，只要小 X 满足要求的数大于等于小 Z 满足要求的数，小 X 赢。否则，小 Z 赢。
## 80pts 做法
我们可以对于每一组 $k$ 暴力在序列 $a$ 和序列 $b$ 中找到最大的满足要求的数，可以先对序列 $a$ 和序列 $b$ 排序，这样可以快一点。时间复杂度为 $O(q \times (n+m))$。~~不过对于 Subtask 4 也无济于事。~~
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5;
int n,m,q,k;
int x[N],z[N];
bool isprime(int n){
    for(int i=2;i*i<=n;i++)
        if(n%i==0)
            return  false;
    return true;
}
int main(){
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=n;i++)
        scanf("%d",x+i);
    for(int i=1;i<=m;i++)
        scanf("%d",z+i);
    sort(x+1,x+n+1);
    sort(z+1,z+m+1);
    while(q--){
        scanf("%d",&k);
        if(!isprime(k)){
            puts("Z");
            continue;
        }
        int xmax=INT_MIN,zmax=0;
        for(int i=n;i>0;i--){
            if(x[i]%k==0){
                xmax=x[i];
                break;
            }
        }
        for(int i=m;i>0;i--){
            if(xmax>=z[i])
                break;
            if(z[i]%k==0){
                zmax=z[i];
                break;
            }
        }
        if(xmax>=zmax){
            puts("X");
        }
        else{
            puts("Z");
        }
    }
    return 0;
}
```
## 100pts 做法
时间复杂度里的 $q$ 肯定优化不了。所以只能优化 $(n+m)$。我们可以分别对序列 $a$ 和序列 $b$ 中 $8 \times 10^6$ 以内的数找到最大的倍数，即满足要求的数。对于每一组 $k$，只用比较两个最大值即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=8e6;
int n,m,q,k,a;
int x[N],z[N];
void fx(int n){
    int yn=n;
    for(int i=2;i*i<n;i++){
        if(n%i==0)
            x[i]=max(x[i],yn);
        while(n%i==0)
            n/=i;
    }
    if(n>1){
        x[n]=max(x[n],yn);
    }
    return;
}
void fz(int n){
    int yn=n;
    for(int i=2;i*i<n;i++){
        if(n%i==0)
            z[i]=max(z[i],yn);
        while(n%i==0)
            n/=i;
    }
    if(n>1){
        z[n]=max(z[n],yn);
    }
    return;
}
int main(){
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=n;i++){
        scanf("%d",&a);
        fx(a);
    }
    for(int i=1;i<=m;i++){
        scanf("%d",&a);
        fz(a);
    }
    while(q--){
        scanf("%d",&k);
        if(x[k]&&x[k]>=z[k]){
            puts("X");
        }
        else{
            puts("Z");
        }
    }
    return 0;
}
```
~~为什么暴力做法在前三个子任务快那么多呀。~~

---

## 作者：yzc1125 (赞：2)

# 思路
其实一次一次的报数可以不必，最终是取决有最大的那个。所以每次找到序列中是 $k$ 的倍数中最大的，然后进行比较。
## 80分做法
我们可以在每个询问中找到 $k$ 的倍数中最大的，进行比较。注意，要特判没有的情况。
## 100分做法
我们可以先预处理处理，而找到每个数的质因子根据算术基本定理，代码如下：

```cpp
for (int i=2;i*i<=n;i++)
{
    if (n%i==0)
    {
        while (n%i==0) n/=i;
        cout<<i<<" ";
    }
}
```
在我们分解每个质因子后，我们可以将这个数赋值质数的倍数的最大值，在询问比较大小输出即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+100;
const int M=8e6+100;
int a[N],b[N];
int k1[M],k2[M];
bool is_prime(int x)//判断是不是质数
{
	if (x==1) return 0;
	for (int i=2;i*i<=x;i++)
	{
		if (x%i==0) return 0;
	}
	return 1;
}
int main()
{
	int n,m,q;
	cin>>n>>m>>q;
	for (int i=1;i<=n;i++) cin>>a[i];
	for (int i=1;i<=m;i++) cin>>b[i];
	for (int i=1;i<=n;i++)
	{
		int x=a[i];
		for (int j=2;j*j<=x;j++)//分解质因数
		{
			if (x%j==0)
			{
				while (x%j==0) x/=j;
				k1[j]=max(k1[j],a[i]);
			}
			if (x>1)
			{
				k1[x]=max(k1[x],a[i]);
			}
		}
	}
	for (int i=1;i<=m;i++)
	{
		int x=b[i];
		for (int j=2;j*j<=x;j++)
		{
			if (x%j==0)
			{
				while (x%j==0) x/=j;
				k2[j]=max(k2[j],b[i]);
			}
			if (x>1)
			{
				k2[x]=max(k2[x],b[i]);
			}
		}
	}
	while (`q--)
	{
		int k;
		cin>>k;
		if (!is_prime(k)) cout<<"Z"<<endl;
		else//比较输出
		{
			if (k1[k]==0) cout<<"Z"<<endl;
			else if (k1[k]>=k2[k]) cout<<"X"<<endl;
			else cout<<"Z"<<endl; 
		}
	}
}
```

---

## 作者：CSP_S_2023_T2 (赞：2)

### 思路

以下默认 $k$ 为质数。

容易发现：

- 若 $a$ 中没有一个数能被 $k$ 整除，则小 Z 获胜。

- 若 $a$ 中有至少一个数能被 $k$ 整除且 $b$ 中没有一个数能被 $k$ 整除，则小 X 获胜。

- 若能被 $k$ 整除的 $a_i$ 的最大值 $\ge$ 能被 $k$ 整除的 $b_i$ 的最大值，则小 X 直接选择这个最大值即可获胜。

- 反之，无论小 X 出什么，小 Z 都可以出最大值获胜。

那么实现就简单了。

先跑一遍 $8 \times 10^6$ 以内的线性筛。

定义 $f(x)$ 为能被 $x$ 整除的 $a_i$ 的最大值（若没有，则 $f(x)=0$），$g(x)$ 为能被 $x$ 整除的 $b_i$ 的最大值（若没有，同上）。

对于每一个 $a_i$，分解质因数，对于 $a_i$ 的每一个质因子 $t$，将 $f(t)$ 更新为 $\max \{f(t),a_i \}$ 即可。

对于每一个 $b_i$，同上。

这样我们就得到了所有的 $f(x)$ 和 $g(x)$。

回到题目：

- 若 $f(k)=0$，则小 Z 获胜。

- 反之，若 $f(k) \ge g(k)$，则小 X 获胜。

- 反之，小 Z 获胜。

### 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+10,maxx=8e6+10;
int n,m,q,k,a[N],b[N],ma[maxx],mb[maxx];
bool isPrime[maxx];
vector<int> primes;
void init(){  //线性筛
	isPrime[1]=1;
	for(int i=2;i<maxx;i++){
		if(!isPrime[i]){
			primes.push_back(i);
			for(int j=0;j<primes.size();j++){
				if(i*primes[j]<maxx) isPrime[i*primes[j]]=1;
				else break;
			}
		}
		else{
			for(int j=0;j<primes.size();j++){
				if(i*primes[j]<maxx) isPrime[i*primes[j]]=1;
				else break;
				if(i%primes[j]==0) break;
			}
		}
	}
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    init();
    cin>>n>>m>>q;
    for(int i=1;i<=n;i++){
    	cin>>a[i];
    	int x=a[i];
    	for(int j=0;primes[j]*primes[j]<=a[i];j++){  //质因数分解
    		while(x%primes[j]==0){
    			ma[primes[j]]=max(ma[primes[j]],a[i]);
    			x/=primes[j];
			}
		}
		if(x!=1) ma[x]=max(ma[x],a[i]);  //这一步不要忘了
	}
    for(int i=1;i<=m;i++){
    	cin>>b[i];
    	int x=b[i];
    	for(int j=0;primes[j]*primes[j]<=b[i];j++){
    		while(x%primes[j]==0){
    			mb[primes[j]]=max(mb[primes[j]],b[i]);
    			x/=primes[j];
			}
		}
		if(x!=1) mb[x]=max(mb[x],b[i]);
	}
    while(q--){
    	cin>>k;
    	if(isPrime[k]) cout<<'Z';  //判断 k 为合数的情况
    	else{
    		if(!ma[k]) cout<<'Z';             //小 X 没有符合条件的数，小 Z 获胜
    		else if(ma[k]>=mb[k]) cout<<'X';  //小 X 的最大值比小 Z 大（或小 Z 没有符合条件的数），小 X 获胜
    		else cout<<'Z';                   //小 X 的最大值比小 Z 小，小 Z 获胜
		}
		cout<<'\n';
	}
    return 0;
}
```

[AC记录](https://www.luogu.com.cn/record/219135187)

（其实本题时限可以压缩至 $1.5s$）

---

## 作者：篮网总冠军 (赞：2)

官方题解。

我们可以发现，既然每一个人要报的数都要比上一个人大，那么报自己最大的数一定是对于两方来说的最优方案。

那么我们只要对于 $a,b$ 序列每个数的所有质因子枚举，对于每个存在的质因子取最大值即可。

考虑埃筛给每个数分解出质因数。

代码：


```cpp
#include <bits/stdc++.h>
using namespace std;

vector<int>s[8000005];
bool vis[8000005];
void init(){
	for(int i=2;i<=8000000;i++){
		if (vis[i]==0){
			s[i].push_back(i);
			for(int j=i+i;j<=8000000;j+=i){
				s[j].push_back(i);
				vis[j]=1;
			}
		}
	}
}
int a[500005],b[500005],ma1[8000005],ma2[8000005];
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	int n,m,q;
	cin>>n>>m>>q; 
	init();
	for(int i=1;i<=n;i++){
		cin>>a[i];
		for(int j=0;j<s[a[i]].size();j++){
			ma1[s[a[i]][j]]=max(a[i],ma1[s[a[i]][j]]);
		}
	}
	for(int i=1;i<=m;i++){
		cin>>b[i];
		for(int j=0;j<s[b[i]].size();j++){
			ma2[s[b[i]][j]]=max(b[i],ma2[s[b[i]][j]]);
		}
	}
	while(q--){
		int k;
		cin>>k;
		if (ma1[k]==0) cout<<"Z"<<endl;
		else if (ma1[k]>=ma2[k]) cout<<"X"<<endl;
		else cout<<"Z"<<endl; 
	}
	return 0;
}

```

---

## 作者：hlb44 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P12677)

~~调了好久……~~

题目需要我们判断小 X 和小 Z 谁能够在使用最优策略的情况下获胜。

如果只暴力对每个数进行质因子的计算，不能够通过，我们需要使用预处理的思想进行优化，具体如下：

例子：

给定长度为 $n$ 的序列 $A$ 和固定数字 $k$，要求在序列中找出满足 $A_{i} + A_{j} = k$ 的不同的 $i,j$ 个数，暴力的时间复杂度为 $O (n ^ 2)$，在 $n$ 较大时不能够通过。

我们可以在输入序列的同时用一个布尔型桶数组 $T$，其中，$T_{i}$ 表示 $i$ 元素是否在序列中出现过。

接着，我们找序列中的每一个数 $i$，判断 $k-a_{i}$ 是否出现过，即判断 $T_{k-a_{i}}$ 是否为真，为真则计数器加 $1$。

在这道题中，我们对所有可能出现的数字都提前计算各自的质因子，再记录序列中质因子包含 $k$ 的最大数最后判断输出即可。

并且，容易发现假设一个数是 $n$ 的倍数，则这个数不是质数，当然，$n$ 不为 $0$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
// s[i]存i的质因子
vector<int>s[8000005];
int n,m,q,a[500005],b[500005];
// f[k]:小X序列中质因子含k的最大数
// g[k]:小Z序列中质因子含k的最大数
int f[8000005],g[8000005];
// 判断质数,jz[i]表示i是否为质数
bool jz[8000005];
int main() {
	cin>>n>>m>>q;
	// 求每个数的所有质因子
	for(int i=2; i<=8000000; i++) {
		if(jz[i]==0) { // i是质数
			s[i].push_back(i);
			for(int j=i+i; j<=8000000; j+=i) {
				s[j].push_back(i);
				jz[j]=1;  // 倍数标记为非质数
			}
		}
	}
	// 每个质因子对应的最大值
	for(int i=1; i<=n; i++) {
		cin>>a[i];
		//更新f[k]
		for(int j=0; j<s[a[i]].size(); j++) {
			f[s[a[i]][j]]=max(a[i],f[s[a[i]][j]]);
		}
	}
	for(int i=1; i<=m; i++) {
		cin>>b[i];
		//更新g[k]
		for(int j=0; j<s[b[i]].size(); j++) {
			g[s[b[i]][j]]=max(b[i],g[s[b[i]][j]]);
		}
	}
	while(q--) {
		int k;
		cin>>k;
		// 如果k不是质数,或者小X没有可用的数,输出Z
		if(jz[k] || f[k]==0)cout<<"Z"<<endl;
		// 小X的最大数大于等于小Z的最大数,小X胜
		else if(f[k]>=g[k])cout<<"X"<<endl;
		// 否则小Z胜
		else cout<<"Z"<<endl;
	}
	return 0;
}
```

---

## 作者：__CJY__ (赞：1)

## 思路
我们使用埃筛统计每个数的所有质因数，存储在数组 $p$ 中，即  $p_i$ 保存的是数字 $i$ 的所有质因数。

* 我们设 $ma1_k$ 为序列 $a$ 中所有能被质数 $k$ 整除的数的最大值。
* 我们设 $ma2_k$ 为序列 $b$ 中所有能被质数 $k$ 整除的数的最大值。

通过遍历每个数，分解其质因数，并更新对应质数的最大值。

接下来，对于每一次询问：
* 如果 $ma1_k=0$，即小 X 没有能被 $k$ 整除的数，直接输出 `Z`。
* 如果 $ma1_k \ge ma2_k$，即小 X 的最大可用数不小于小 Z 的最大可用数，小 X 胜，输出 `X`。
* 否则，小 Z 可以回应小 X 的任何选择并最终获胜，输出 `Z`。

这个时间复杂度有点高，主要是因为埃筛要跑 $8 \times 10^6$ 次，还好题目给了 $4$ 秒，可以卡过。

---

## 作者：lwj54joy (赞：1)

#### 题目
给定两个数组 $a$ 和 $b$，以及多个查询 $k$（默认 $k$ 为质数），判断在以下规则下，小 X 和小 Z 谁会获胜：
1. 小 X 从 $a$ 中选一个能被 $k$ 整除的数。
2. 小 Z 从 $b$ 中选一个能被 $k$ 整除的数。
3. 比较两者选的数的大小，大的一方获胜。

#### 思路
- 使用线性筛预处理所有质数。
- 对于每个 $a[i]$ 和 $b[i]$，分解其质因数，并记录每个质因数对应的最大数。
   - 如果 $a$ 中没有数能被 $k$ 整除，小 Z 获胜。
   - 如果 $a$ 中有数能被 $k$ 整除，且 $b$ 中没有，小 X 获胜。
   - 否则，比较 $a$ 和 $b$ 中能被 $k$ 整除的最大数，大的一方获胜。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+10, MAX=8e6+10;
int n, m, q, a[N], b[N], max_a[MAX], max_b[MAX];
bool che[MAX];
vector<int> pri;

// 线性筛预处理质数
void init() {
    for(int i=2; i<MAX; i++) {
        if(!che[i]) pri.push_back(i);
        for(int p : pri) {
            if(i*p >= MAX) break;
            che[i*p] = true;
            if(i%p == 0) break;
        }
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    init();
    cin >> n >> m >> q;
    
    // 处理数组a，记录每个质因数对应的最大值
    for(int i=1; i<=n; i++) {
        cin >> a[i];
        int x = a[i];
        for(int p : pri) {
            if(p*p > x) break;
            if(x%p == 0) {
                max_a[p] = max(max_a[p], a[i]);
                while(x%p == 0) x /= p;
            }
        }
        if(x > 1) max_a[x] = max(max_a[x], a[i]);
    }
    
    // 处理数组b，同理
    for(int i=1; i<=m; i++) {
        cin >> b[i];
        int x = b[i];
        for(int p : pri) {
            if(p*p > x) break;
            if(x%p == 0) {
                max_b[p] = max(max_b[p], b[i]);
                while(x%p == 0) x /= p;
            }
        }
        if(x > 1) max_b[x] = max(max_b[x], b[i]);
    }
    
    // 处理查询
    while(q--) {
        int k; cin >> k;
        if(che[k]) cout << "Z\n";  // k为合数，直接小Z获胜
        else {
            if(max_a[k] == 0) cout << "Z\n";  // a中无数能被k整除
            else if(max_b[k] == 0 || max_a[k] >= max_b[k]) cout << "X\n";  // a的最大值更大或b中无数
            else cout << "Z\n";  // b的最大值更大
        }
    }
    return 0;
}
```

---

## 作者：Tjaweiof (赞：1)

# P12677 题解
[题目传送门](https://www.luogu.com.cn/problem/P12677)

设 $a$ 中最大的 $k$ 的倍数的数为 $x$，$b$ 中最大的 $k$ 的倍数的数为 $z$。那么：若 $x\ge z$，则小 $X$ 可以在第一次选择 $x$ 并直接获得胜利；若 $x<z$，则无论小 $X$ 第一次选择什么数，小 $Z$ 总可以在他的第一次选择 $z$ 并直接获得胜利。

考虑依次将序列 $a$ 中所有数字质因数分解，并用一个数组记录每个质数在 $a$ 中的所有倍数的最大值，$b$ 同理，询问时直接判断就行了。

需要判断特殊情况：若 $a$ 中没有 $k$ 的倍数，则小 $Z$ 可以直接胜利。

# Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define FILE(x) freopen(x".in", "r", stdin);freopen(x".out", "w", stdout);
int n, m, q, fa[8000001], fb[8000001];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int x, tmp;
	cin >> n >> m >> q;
	for (int i = 1; i <= n; i++){
		cin >> x;
		tmp = x;
		for (int j = 2; j * j <= tmp; j++){
			if (!(tmp % j)){
				fa[j] = max(fa[j], x);
			}
			while (!(tmp % j)){
				tmp /= j;
			}
		}
		if (tmp > 1){
			fa[tmp] = max(fa[tmp], x);
		}
	}
	for (int i = 1; i <= m; i++){
		cin >> x;
		tmp = x;
		for (int j = 2; j * j <= tmp; j++){
			if (!(tmp % j)){
				fb[j] = max(fb[j], x);
			}
			while (!(tmp % j)){
				tmp /= j;
			}
		}
		if (tmp > 1){
			fb[tmp] = max(fb[tmp], x);
		}
	}
	while (q--){
		cin >> x;
		if (fa[x] >= fb[x] && fa[x]){
			cout << "X\n";
		} else {
			cout << "Z\n";
		}
	}
	return 0;
}

```

---

## 作者：e_zhe (赞：1)

### 题目链接

<https://www.luogu.com.cn/problem/P12677>

### 思路分析

易于想到，为使对方尽可能难以报出下一个数，自己应该报出可行的最大数。

我们可以分别记录二人的数列中含有某个质因子的最大数。比较它们的大小，拥有较大数者获胜。

注意一下 $k$ 为合数和二人均无合法数的特殊情况。

### Code

```cpp
#include <bits/stdc++.h>

using namespace std;

template <typename T>
void read_arr(int n, T *arr) {
	for (int i = 1; i <= n; ++ i) cin >> arr[i];
	return;
}

constexpr int N = 5e5 + 5, M = 8e6 + 5;

int n, m, q, a[N], b[N], lst_a[M], lst_b[M];

int main() {
	ios::sync_with_stdio(false),
	cin.tie(nullptr), cout.tie(nullptr);
	
	cin >> n >> m >> q; read_arr(n, a), read_arr(m, b);
	
	sort(a + 1, a + n + 1), sort(b + 1, b + m + 1);
	
	// 分解质因数，记录含有某个质因子的最大数 
	for (int i = 1; i <= n; ++ i) {
		int num = a[i];
		for (int j = 2; j * j <= num; ++ j)
			if (num % j == 0) {
				lst_a[j] = a[i];
				
				while (num % j == 0) num /= j;
			}
		if (num != 1) lst_a[num] = a[i];
	}
	
	for (int i = 1; i <= m; ++ i) {
		int num = b[i];
		for (int j = 2; j * j <= num; ++ j)
			if (num % j == 0) {
				lst_b[j] = b[i];
				
				while (num % j == 0) num /= j;
			}
		if (num != 1) lst_b[num] = b[i];
	}
	
	// lambda 表达式，相当于轻型函数 
	auto check_prime = [](int x) -> bool {
		if (x <= 1) return true;
		for (int i = 2; i * i <= x; ++ i)
			if (x % i == 0) return false;
		return true;
	};
	
	for (int _ = 0; _ < q; ++ _) {
		int x1; cin >> x1;
		
		if (check_prime(x1) == false) cout << "Z\n"; // k 为合数，依题目要求输出 'Z' 
		else if (lst_a[x1] == 0 && lst_b[x1] == 0) cout <<"Z\n"; // 两人均无数可报 
		else cout << "XZ"[lst_a[x1] < lst_b[x1]] << '\n'; // 拥有较大数者获胜 
	}
	return 0;
}
```

---

## 作者：CleverSea (赞：0)

~~时间限制这么**别样**的题，还真是第一次见……~~

### 题意简述

本题是一个博弈论问题，模拟飞花令游戏的数学版本。游戏规则如下：

- 给定质数 $k$（若 $k$ 非质数则直接判定小Z获胜）。
- 小 X 和小 Z 分别拥有序列 $a$（长度 $n$）和 $b$（长度 $m$）。
- 小 X 先手，从 $a$ 中选择一个能被 $k$ 整除的数。
- 随后双方轮流选择，每次选择的数必须大于对方上一轮选择的数，且必须能被 $k$ 整除。
- 无法选择数的一方失败。

对于 $q$ 次询问，每个询问给出一个 $k$，判断在双方均采用最优策略时，小 X（先手）是否能获胜。

### 解题思路

我们可以使用线性筛法预处理 $1$ 到 $8\times 10^6$ 的所有质数，并记录每个数的最小质因子。

为每个质数 $p$ 构建一个列表，存储序列 $a$ 和 $b$ 中能被 $p$ 整除的数及其类别（$a$ 中的数标记为 $0$，$b$ 中的数标记为 $1$）。

#### 对于每次询问：

   - 若 $k$ 不是质数，输出 `Z`。
   - 若 $k$ 是质数，但对应的列表为空（即序列 $a$ 和 $b$ 中均无能被 $k$ 整除的数），则小 X 无法开局，输出 `Z`。
   - 否则，对列表中的数按值降序排序，并按数值分组处理。

#### 博弈状态计算：
   - 从大到小处理每个数值的组：

     - 记录当前组内是否存在 $a$ 类数（`hasA`）和 $b$ 类数（`hasB`）。
     - 根据大于当前数值的组中是否存在必败态，计算当前组的必败态。
     - 更新全局状态（`has_fail_A` 和 `has_fail_B`），表示当前及更大的数中是否存在 $a$ 类或 $b$ 类必败节点。

   - 若最终 `has_fail_A` 为真，则小 X 存在必胜策略（输出 `X`），否则小 Z 获胜（输出 `Z`）。

### $Code$

~~不用`vector`代码就爆了，不知道为什么。~~

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

const int N = 8e6 + 10;

vector<int> primes;
int minn[N + 1];
bool is_prime[N + 1];

// 线性筛法预处理质数及最小质因子
void sieve() {
    for (int i = 0; i <= N; i++) {
        is_prime[i] = true;
        minn[i] = 0;
    }
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= N; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            minn[i] = i;
        }
        for (int j = 0; j < primes.size(); j++) {
            int p = primes[j];
            if (i * p > N) break;
            is_prime[i * p] = false;
            minn[i * p] = p;
            if (i % p == 0) break;
        }
    }
}

// 存储每个质数对应的列表：存储序列中能被该质数整除的数及其类别（0：来自a，1：来自b）
vector<pair<int, int>> lists[N + 1];
// 缓存结果：'X' 或 'Z'，初始化为 -1 表示未计算
char res[N + 1];

int main() {
    sieve(); // 筛法预处理
    int n, m, q;
    scanf("%d %d %d", &n, &m, &q);
    vector<int> a(n);
    vector<int> b(m);
    // 读入序列 a
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    // 读入序列 b
    for (int i = 0; i < m; i++) {
        scanf("%d", &b[i]);
    }
    // 初始化缓存
    memset(res, -1, sizeof(res));
    // 预处理序列 a：分解每个数的质因子，并加入对应质数的列表
    for (int i = 0; i < n; i++) {
        int x = a[i];
        if (x == 1) continue; // 1 没有质因子
        vector<int> fac;
        int temp = x;
        // 分解质因子（去重）
        while (temp > 1) {
            int p = minn[temp];
            fac.push_back(p);
            while (temp % p == 0)
                temp /= p;
        }
        // 将数加入其每个质因子的列表，标记为 0（来自 a）
        for (int p : fac) {
            lists[p].push_back({x, 0});
        }
    }
    // 预处理序列 b：同理
    for (int i = 0; i < m; i++) {
        int x = b[i];
        if (x == 1) continue;
        vector<int> fac;
        int temp = x;
        while (temp > 1) {
            int p = minn[temp];
            fac.push_back(p);
            while (temp % p == 0)
                temp /= p;
        }
        for (int p : fac) {
            lists[p].push_back({x, 1});
        }
    }
    // 处理每个询问
    while (q--) {
        int k;
        scanf("%d", &k);
        // 若 k 超出范围或非质数，输出 'Z'
        if (k > N || !is_prime[k]) {
            printf("Z\n");
        } else {
            // 若结果已缓存，直接输出
            if (res[k] != -1) {
                printf("%c\n", res[k]);
            } else {
                // 若该质数对应的列表为空，则小X无法开局，小Z获胜
                if (lists[k].empty()) {
                    res[k] = 'Z';
                    printf("Z\n");
                } else {
                    // 获取列表并按数值降序排序
                    auto& vec = lists[k];
                    sort(vec.begin(), vec.end(), [](const pair<int, int>& x, const pair<int, int>& y) {
                        return x.first > y.first;
                    });
                    bool hfA = false; // 是否存在 A 类必败节点
                    bool hfB = false; // 是否存在 B 类必败节点
                    int i = 0;
                    int totsize = vec.size();
                    // 按数值分组处理
                    while (i < totsize) {
                        int j = i;
                        // 找到相同数值的组
                        while (j < totsize && vec[j].first == vec[i].first)
                            j++;
                        // 保存当前状态（大于当前数值的节点状态）
                        bool csfA = hfA;
                        bool csfB = hfB;
                        bool hasA = false, hasB = false;
                        // 统计组内是否有 A 类或 B 类节点
                        for (int idx = i; idx < j; idx++) {
                            if (vec[idx].second == 0)
                                hasA = true;
                            else
                                hasB = true;
                        }
                        bool gfA = false;
                        bool gfB = false;
                        // 计算 A 类节点的必败态：若存在 A 类节点且大于当前数的 B 类节点无必败态，则当前 A 类节点为必败
                        if (hasA && !csfB)
                            gfA = true;
                        // 计算 B 类节点的必败态：若存在 B 类节点且大于当前数的 A 类节点无必败态，则当前 B 类节点为必败
                        if (hasB && !csfA)
                            gfB = true;
                        // 更新全局状态
                        if (gfA)
                            hfA = true;
                        if (gfB)
                            hfB = true;
                        i = j; // 移动到下一组
                    }
                    // 若存在 A 类必败节点，小X可选择该节点使小Z面临必败，故小X获胜
                    if (hfA) {
                        res[k] = 'X';
                        printf("X\n");
                    } else {
                        res[k] = 'Z';
                        printf("Z\n");
                    }
                }
            }
        }
    }
    return 0;
}
```

### 现在，分析一下时间复杂度

~~这应该是我做的最复杂的时间复杂度分析了qwq。~~

1. **筛法求质数**：$O(MAXV)$，其中 $MAXV = 8 \times 10^6$。

2. **构建质数对应的列表**：对于每个数 $x$，分解其质因子的时间复杂度为 $O(\log x)$，总时间复杂度为 $O((n + m) \log \max(a_i, b_i))$，其中 $n$ 和 $m$ 分别为序列 $a$ 和 $b$ 的长度，$\max(a_i, b_i) \leq 8 \times 10^6$。

3. **处理每个询问**：

    - 质数判断 $O(1)$（因为已经筛好了，直接查表）。
    - 排序列表 $O(s_k \log s_k)$，其中 $s_k$ 为质数 $k$ 对应的列表大小。
    - 扫描列表 $O(s_k)$。
    - 处理询问的总时间复杂度：$\sum_{k \text{为质数}} O(s_k \log s_k)$（对所有质数 $k$，处理其对应的列表 $s_k$ 的时间复杂度的总和。）

4. **得出结论**：总时间复杂度为：

   $$O(MAXV + (n + m) \log \max(a_i, b_i) + \sum_{k \text{为质数}} s_k \log s_k)$$

   其中 $MAXV = 8 \times 10^6$，$s_k$ 为质数 $k$ 对应的列表大小。但实际中 $s_k$ 不会总是 $n + m$，因此均摊复杂度会更优。

---

## 作者：StarTwinkleTwinkle (赞：0)

赛事大号差 12s 首 A，亏麻了，然后就不想打了。

考虑每个人出自己最大的数，尽量让对方出不出来即可。则：

- 当序列 $a$ 中不存在 $k$ 的倍数时，小 Z 胜；

- 当序列 $a$ 中存在 $k$ 的倍数且序列 $b$ 中不存在 $k$ 的倍数时，小 X 胜；

- 序列 $a$ 中存在 $k$ 的倍数且序列 $b$ 中存在 $k$ 的倍数时，比较两个序列含质因子 $k$ 的数中的最大值。若 $a$ 中含质因子 $k$ 的数中的最大值不小于 $b$ 中含质因子 $k$ 的数中的最大值，小 X 胜；反之，小 Z 胜。

看一下数据范围，发现 $O(n\log n)$ 很有可能过不去，考虑用 $O(n\log\log n)$ 的埃氏筛或 $O(n)$ 的欧拉筛，预处理出来每个质因子所对应的最大值。这样的话，总时间复杂度均为 $O(n+m+q+V\log\log V)$。

似乎应该没有 $O(n+m+q+V)$ 的解法，设 $f(n)$ 表示为序列中含质因子 $n$ 的数的最大值，发现 $f(n)$ 不是积性函数，这里不能用欧拉筛同时预处理最大值。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,q,a[500005],b[500005];
int ca[8000006],cb[8000006];
int sa[8000006],sb[8000006];
bool vis[20000005];
int pr[5000006];
int phi[20000005],cnt;
inline void init(int N){
    cnt=0;phi[1]=1;
    for(register int i=2;i<=N;++i){
        if(!vis[i]){
            pr[++cnt]=i;
            phi[i]=i-1;
        }
        for(register int j=1;j<=cnt;++j){
            int t=i*pr[j];
            if(t>N)break;
            vis[t]=1;
            if(i%pr[j]==0)break;
        }
    }
}
const int M=8e6;
signed main()
{
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<=n;++i)scanf("%d",&a[i]),ca[a[i]]++;
	for(int i=1;i<=m;++i)scanf("%d",&b[i]),cb[b[i]]++;
	init(M);
	for(int i=2;i<=M;++i){
		if(!vis[i]){
			for(int j=i;j<=M;j+=i){
				if(ca[j])sa[i]=j;
				if(cb[j])sb[i]=j;
			}
		}
	}
	for(int i=1,k;i<=q;++i){
		scanf("%d",&k);
		if(sa[k]==0)printf("Z\n");
		else if(sa[k]>=sb[k])printf("X\n");
		else printf("Z\n");
	}
	return 0;
}
```

---

