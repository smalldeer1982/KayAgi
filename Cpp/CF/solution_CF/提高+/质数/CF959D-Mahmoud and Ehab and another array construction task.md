# Mahmoud and Ehab and another array construction task

## 题目描述

Mahmoud has an array $ a $ consisting of $ n $ integers. He asked Ehab to find another array $ b $ of the same length such that:

- $ b $ is lexicographically greater than or equal to $ a $ .
- $ b_{i}>=2 $ .
- $ b $ is pairwise coprime: for every $ 1<=i<j<=n $ , $ b_{i} $ and $ b_{j} $ are coprime, i. e. $ GCD(b_{i},b_{j})=1 $ , where $ GCD(w,z) $ is the greatest common divisor of $ w $ and $ z $ .

Ehab wants to choose a special array so he wants the lexicographically minimal array between all the variants. Can you find it?

An array $ x $ is lexicographically greater than an array $ y $ if there exists an index $ i $ such than $ x_{i}>y_{i} $ and $ x_{j}=y_{j} $ for all $ 1<=j<i $ . An array $ x $ is equal to an array $ y $ if $ x_{i}=y_{i} $ for all $ 1<=i<=n $ .

## 说明/提示

Note that in the second sample, the array is already pairwise coprime so we printed it.

## 样例 #1

### 输入

```
5
2 3 5 4 13
```

### 输出

```
2 3 5 7 11 ```

## 样例 #2

### 输入

```
3
10 3 7
```

### 输出

```
10 3 7 ```

# 题解

## 作者：wangbinfeng (赞：2)

[![](https://img.shields.io/badge/题目-CF959D_Mahmoud_and_Ehab_and_another_array_construction_task-yellow)
![](https://img.shields.io/badge/难度-提高+/省选−-blue)
![](https://img.shields.io/badge/考点-数学-red)
![](https://img.shields.io/badge/题型-传统题-green)](https://www.luogu.com.cn/problem/CF959D)
[![](https://img.shields.io/badge/作者-wangbinfeng(387009)-purple)](https://www.luogu.com.cn/user/387009)

------------
难得的集训一眼题，写篇题解纪念一下。

题意的话看翻译即可，不再赘述。本题解中定义“冲突”为两个数不互质。

考虑字典序最小，则应当保证最前面的数最小，即在不冲突的前提下尽量不改变前面的数，第一个必须冲突的数改为不冲突的最小的数，其后面的数按数值顺序依次改为与之前的数互质的质数即可。

证明：
1. 在不冲突的前提下尽量不改变前面的数：
>字典序最小。
2. 第一个必须冲突的数改为不冲突的最小的数：
>冲突的话不满足题意，不选最小的数不满足字典序最小。
3. 后面的数按数值顺序依次改为与之前的数互质的质数：
>翻译一下即选取不是之前的数或其质因子的数。一定要保证升序。只选质数因为不冲突的合数一定大于不冲突的质数，因为不冲突的合数等于不少于两个不冲突的质数的乘积，显然更劣。

按照上面的分析构造答案即可。用线性筛预处理下质数，统计一下所有质因数是否已经被占用。如果已经被占用则说明发生了冲突。

[CodeForces AC 提交（代码）](https://codeforces.com/contest/959/submission/274495548)。

---

## 作者：zhaotiensn (赞：1)

我们可以将情况分成两种：一种是b数组之前的数与a数组不相同，所以不管b数组后面怎么填，字典序一定比a数组大，只要考虑如何使b数组满足互质且字典序最小就好了。另一种是b数组前面都与a数组相同，所以还要多考虑一个当前位置填的数一定要大于等于a数组的数。

对于第一种情况，我们可以直接找到没有作为质因子出现过的最小质数就行了。显然不可能有更小的数满足条件。

对弈第二种情况，因为一旦填了一个比a数组大的数，那么后面的情况都是第一种了。所以直接进行暴力，最后填的数等于a数组只需暴力判一次，大于a数组时最坏情况也只要判10万次，因为最多只有填一次大于a数组的，所以复杂度还是可以接受的。

代码：
```
#include <iostream>
#include <cstring>
#include <cstdio>

#define Max 100005

using namespace std;

inline char gc(){
    static char buf[100000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
#define gc getchar
inline int read(){
    int x=0;char ch=gc();bool positive=1;
    for(;!isdigit(ch);ch=gc())if(ch=='-')positive=0;
    for(;isdigit(ch);ch=gc())x=x*10+ch-'0';
    return positive?x:-x;
}

inline void write(int x){
    if(x<0)x=-x,putchar('-');
    if(x>9)write(x/10);putchar(x%10+'0');
}

inline void writeln(int x){
    write(x);puts("");
}//以上皆为没有的快读快输

int n,size,a[Max],b[Max],pri[200005],last[2000005];
bool flag,vis[2000005],use[2000005];

inline bool check(int x){//判断x与b数组中其他数是否互质
    int num[50],size=0;
    while(vis[x]){
        num[++size]=last[x];
        x=x/last[x];
    }
    num[++size]=x;
    for(int i=1;i<=size;i++){
        if(use[num[i]]){
            return false;
        }
    }
    return true;
}

int main(){
    n=read();
    for(int i=1;i<=n;i++)a[i]=read();
    for(int i=2;i<=2000000;i++){//筛素数，一定要筛的够多，不够用回RE的，我这里好像筛出了10万个的样子
        if(!vis[i]){
            pri[++size]=i;
        }
        for(int j=1;j<=size;j++){
            int k=pri[j]*i;
            if(k>2000000)break;
            vis[k]=true;
            last[k]=pri[j];//last记录最小的质因子
            if(i%pri[j]==0){
                break;
            }
        }
    }
    int j=1;
    for(int i=1;i<=n;i++){
        if(flag){
            while(use[pri[j]]){//暴力找最小的为用过的质数
                j++;
            }
            use[pri[j]]=true;
            b[i]=pri[j];
        }else{
            int k=a[i];
            while(!check(k)){//暴力跳
                k++;
            }
            if(k>a[i]){
                flag=true;
            }
            b[i]=k;
            while(vis[k]){//标记哪些质数用过了
                use[last[k]]=true;
                k=k/last[k];
            }
            use[k]=true;
        }
    }
    for(int i=1;i<=n;i++){
        write(b[i]);putchar(' ');
    }
    return 0;
}
```

---

## 作者：mulberror (赞：1)

我的博客：[My blog](http://blog.chhokmah.top/)

先把所有的数都塞到set里  
然后对于每一次操作分两类讨论  
如果前面还都是一样的，那么就要二分找第一个大于等于他的。  
如果前面已经不一样了，那么就去set的shoul首。  
每一次删去掉所有这个数的因子的倍数，就像埃筛一样。  
讲完了

```cpp
#include <cstdio>
#include <algorithm>
#include <set>

using namespace std;

const int N = 2e6 + 5; 

set<int> s; 
int n; 
int a[N], b[N]; 
bool fg; 

inline void del(int x) {
	for (int i = 2; i * i <= x; i ++) {
		if (x % i == 0) {
			for (int j = i; j < N; j += i) if (s.count(j)) s.erase(j); 
			while (x % i == 0) x /= i; 
		}
	}
	if (x > 1) for (int i = x; i < N; i += x) if (s.count(i)) s.erase(i); 
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i ++) scanf("%d", &a[i]); 
	for (int i = 2; i < N; i ++) s.insert(i); 
	for (int i = 1; i <= n; i ++) {
		auto it = fg ? s.begin() : s.lower_bound(a[i]); 
		if (*it > a[i]) fg = 1; b[i] = *it; del(*it); 
	}
	for (int i = 1; i <= n; i ++) printf("%d ", b[i]);
	return 0;
}
```

---

## 作者：zdd6310 (赞：0)

# CF959D

本质上非常简单，只需要枚举就可以了。

可以分三步走。

## 第一步

因为要求字典序最小且字典序大于 $a$，所以 $b$ 要跟 $a$ 尽量贴合才可以。

就是把 $a$ 跟 $b$ 不同的位置放在尽量靠后。

也就是如果 $a$ 在前 $i$ 位都两两互质，那么对于 $x\in [1,i]$，就有 $b_x=a_x$。

因为只关注是否互质，所以可以直接分解质因数，判断每一个质数因子是否出现过。

## 第二步

 现在找到第一个不满足条件的 $a_i$。

需要把 $b_i$ 赋一个大于 $a_i$ 但是尽量接近 $a_i$ 的数。

怎么办？直接枚举。

从 $a_i+1$ 开始不断向后枚举，直到找到一个满足条件的数。

最坏情况下，$a$ 中全部都是质数，会找到下一个质数。

因为在 $2\times 10^6$ 以内已经有超过 $10^5$ 个质数了，所以枚举范围不会超过 $2\times 10^6$。

## 第三步

现在把争议的位置处理好了。

因为 $b_i>a_i$，已经满足字典序大于 $a$ 的要求了，所以后面是往小了填。

证明：现在肯定是填最小的质数。

1. 如果现在有更小的质数可以填，交换更优。
2. 因为这个数是最小的质数，如果你填合数，肯定会比这个质数要大，不然存在更小的质数。

证毕。

所以直接填就可以了。

总的时间复杂度可以接受。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=1e5+5;
int n,a[MAXN],b[MAXN];
const int N=2e6+5;
int ispri[N+5],pri[N+5],tot;
inline void init(){
    ispri[1]=1;
    for(int i=2;i<=N;i++){
        if(!ispri[i])pri[++tot]=i;
        for(int j=1;j<=tot&&i*pri[j]<=N;j++){
            ispri[i*pri[j]]=1;
            if(i%pri[j]==0)break;
        }
    }
    cout<<tot<<'\n';
}
bool vis[N+5];
signed main(){
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);
    cin>>n;init();
    for(int i=1;i<=n;i++)cin>>a[i];
    int ST=0;vector<int>nd;
    int END=0;
    for(int i=1;i<=n;i++){
        int lst=a[i];
        for(int j=1;j<=tot&&pri[j]*pri[j]<=a[i];j++){
            if(lst%pri[j]==0){
                while(lst%pri[j]==0)lst/=pri[j];
                if(vis[pri[j]]){
                    ST=i;break;
                }
                nd.push_back(pri[j]),vis[pri[j]]=1;
            }
        }
        if(ST)break;
        if(lst>1){
            if(vis[lst]){
                ST=i;break;
            }else{
                nd.push_back(lst),vis[lst]=1;
            }
        }
        END=nd.back();
    }
    while(nd.size()&&nd.back()!=END){
        vis[nd.back()]=0;nd.pop_back();
    }
    if(ST==0){
        for(int i=1;i<=n;i++)cout<<a[i]<<" ";
        cout<<"\n";
        exit(0);
    }
    int FIR=0;
    for(int i=a[ST]+1;;i++){
        bool flag=0;
        for(int j:nd)if(i%j==0){
            flag=1;break;
        }
        if(flag==0){
            FIR=i;break;
        }
    }
    for(int i=1;i<ST;i++)b[i]=a[i];
    b[ST]=FIR;
    int lst=b[ST];
    for(int i=2;i*i<=b[ST];i++){
        if(lst%i==0){
            vis[i]=1;
            while(lst%i==0)lst/=i;
        }
    }
    vis[lst]=1;
    int fir=1;
    for(int i=ST+1;i<=n;i++){
        while(vis[pri[fir]])fir++;
        b[i]=pri[fir];vis[pri[fir]]=1;
    }
    for(int i=1;i<=n;i++)cout<<b[i]<<" ";cout<<"\n";
}
```

---

## 作者：LYY_yyyy (赞：0)

最近被虐惨了，写一些简单题找一下自信。

由于我们要求 $b$ 字典序 $\ge a$ 且尽可能小，所以我们肯定尽量保留原数列中前面的数。从前往后枚举原数列，暴力分解质因数计算是否与前面的数不互质。如果不互质，就将这个数改为 $\ge$ 它的最小的与前面都互质的数。由于我们要求字典序尽量小，那么这个数之后的数直接从小到大取没取过的质数即可。由于 1e5 之内的数最多就六七个不同的质因数，所以我们筛出 1e7 之内的质数完全够了。

Code:

```cpp
#include<bits/stdc++.h>
#define pb emplace_back
using namespace std;
int n;
int a[100010];
bitset<10000010> vis;
int primes[1000010];
bitset<10000010> op;
int tot;
void init(int n)
{
	for(int i=2;i<=n;i++){
		if(!vis[i]) primes[++tot]=i;
		for(int j=1;primes[j]*i<=n;j++)
		{
			vis[primes[j]*i]=1;
			if(i%primes[j]==0) break;
		}
	}
}
bool ck(int i)
{
	int now=i;vector<int> s;
	for(int j=1;primes[j]<=sqrt(i);j++)
	{
		if(now%primes[j]==0)
		{
			if(op[primes[j]]) return 0;s.pb(primes[j]);
			while(now%primes[j]==0) now/=primes[j];
		}
	}
	if(now>1) if(op[now]) return 0;
	for(auto o:s) op[o]=1;
	if(now>1) op[now]=1;
	return 1; 
}
int p(int b)
{
	for(int i=b+1;i<=1e7;i++)
	{
		if(ck(i)) return i;
	}
}
int main()
{
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n;init(1e7);
	for(int i=1;i<=n;i++) cin>>a[i];
	int b=n;
	for(int i=1;i<=n;i++)
	{
		vector<int> s;bool f=0;
		int now=a[i];
		for(int j=1;primes[j]<=sqrt(a[i]);j++)
		{
			if(now%primes[j]==0) 
			{
				s.pb(primes[j]);
				if(op[primes[j]]) f=1;
				while(now%primes[j]==0) now/=primes[j];
			}
		}
		if(now>1)
		{
			s.pb(now);
			if(op[now]) f=1;
		}
		if(!f) for(auto o:s) op[o]=1;
		else
		{
			b=i;a[i]=p(a[i]);
			break;
		}
	}
	int now=1;
	for(int i=b+1;i<=n;i++)
	{
		while(op[primes[now]]) now++;
		a[i]=primes[now];op[a[i]]=1;
	}
	for(int i=1;i<=n;i++) cout<<a[i]<<" ";
	return 0; 
} 
```

---

## 作者：LG_ljc2022 (赞：0)

## 题目大意

给定一个长度为 $n$ 的数列 $a$，要求构造一个长度和 $a$ 相同的序列 $b$，使得 $b$ 序列满足任意两个数两两互质，且 $b$ 序列字典序大于等于 $a$ 序列，字典序最小。

## Solution

看到题目中的 **大于等于 $a$ 的字典序且字典序最小**，不难想到应该尽量按照 $a$ 来取，最后剔除不满足条件的数字。

而题目要求 $b$ 数组两两互质，即不能有共同的因子，因此可以先通过欧拉筛法预处理出范围内的所有质数，然后尽量按照 $a$ 数组取数。而为了使字典序大于等于 $a$，因此所选的数字应该大于等于 $a$，第 $i$ 个数字从 $a[i]$ 起依次增大枚举，找到一个合适的就放进 $b[i]$。如果当前数字已经大于 $a[i]$，那么字典序大于等于 $a$ 已经满足，后续直接按照使用信息从小到大选质数填入 $b[i]$ 即可，这样贪心选取可以保证正确性。

注意每一次选完后要标记不能使用的因子，对于每一个数在欧拉筛法中要记录可以被筛的最小的质因子，方便后续统计使用信息。标记使用数组即可。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10, M = 2e6 + 10;
int n, a[N], b[N], prime[N], Min_pr[M];
bool vis[M], vis2[M];

void Euler ()
{
	int cnt = 0;
	for (int i = 2; i <= M - 2; i++)
	{
		if (!vis[i]) prime[++cnt] = i;
		for (int j = 1; j <= cnt && i * prime[j] <= M - 2; j++)
		{
			vis[i * prime[j]] = 1;
			Min_pr[i * prime[j]] = prime[j]; //记录可以被筛的最小的质数
			if (i % prime[j] == 0) break;
		}
	}
}
bool check (int k)
{
	int tx = k;
	if (vis2[tx] == 1) return false;
	while (vis[tx] == 1) //只要还是合数就继续找
	{
		if (vis2[Min_pr[tx]] == 1) return false; //用过就不行
		tx /= Min_pr[tx];
	}
	return true;
}
void Mark (int k) //标记
{
	while (vis[k])
	{
		vis2[Min_pr[k]] = 1;
		k /= Min_pr[k];
	}
	vis2[k] = 1;
}

int main()
{
	
	Euler();
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	bool can = false; //是否满足字典序大于等于a，满足直接找最小的质数
	int snt = 1; //寻找最小质数
	for (int i = 1; i <= n; i++)
	{
		if (can == false)
		{
			int tx = a[i]; //字典序最小，从a[i]开始找
			while (!check(tx)) tx++;
			b[i] = tx;
			Mark(tx);
			if (tx > a[i]) can = true;
		}
		else
		{
			while (vis2[prime[snt]] == 1 || check(prime[snt]) == false) snt++; //用过了就往后找质数
			vis2[prime[snt]] = 1; //标记
			b[i] = prime[snt];
		}
	}
	for (int i = 1; i <= n; i++) printf("%d ", b[i]);
	
	return 0;
}
``````

---

## 作者：Xiao_mo (赞：0)

# Step1
首先考虑 $b[i]$ 和 $a[i]$ 一样的一个一个放，直到找到一个 $a[i]$ 是不与已经记录下来的 $b$ 互质，则暴力枚举可以被放入的数，计入 $b$ 。

此时 {$b_i$} 的字典序已经大于 {$a_i$}，所以只需要从小开始找能放入的数即可。

如果存在一个合数 $x$ 可以放入，那么显然存在至少两个质数可以放入。

所以只要从小开始找没放过的质数。

# Step2
### Tip:质数要多筛点, $10^5$ 以内的质数不够用(因为一个数可能会占用好几个质数)

每个数的质因数可以用 $vetcor$ 预处理出来。
```cpp
for(ll i=2; i<=N*10; i++) {//筛质数 
		if(!vis[i])pri[++m]=i;
		for(ll j=1; j<=m&&i*pri[j]<=N*10; j++) {
			vis[i*pri[j]]=1;
			if(!(i%pri[j]))break;
		}
	}
	for(int i=1; i<=m; i++) {//存每个数可以被哪些质数整除 
		for(int j=pri[i]; j<N; j+=pri[i]) {
			int x=j;
			while(!(x%pri[i])) {
				h[j].push_back(i);
				x/=pri[i];
			}
		}
	}
```
然后照第一步模拟。

# End
贴上代码。
```
#include<bits/stdc++.h>
#define ll long long
#define rg register
using namespace std;
const int N=2e5+10;
inline ll read() {
	register ll s=0,f=0;
	register char ch=getchar();
	while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) s=(s<<1)+(s<<3)+(ch^48),ch=getchar();
	return f?-s:s;
}
int n,a[N>>1],b[N>>1],cnt,flag,m,t;
int pri[2*N];
vector<int>h[N];
bool vis[N*11],vp[2*N];
inline bool prime(int x){
	int k=x;
	for(int i=1;i<=m;i++){
		if(!(k%pri[i])&&vp[i])return 0;
		if(pri[i]>k)break;
	}
	return 1;
}
int main() {
	n=read();
	for(ll i=2; i<=N*10; i++) {//筛质数 
		if(!vis[i])pri[++m]=i;
		for(ll j=1; j<=m&&i*pri[j]<=N*10; j++) {
			vis[i*pri[j]]=1;
			if(!(i%pri[j]))break;
		}
	}
	for(int i=1; i<=m; i++) {//存每个数可以被哪些质数整除 
		for(int j=pri[i]; j<N; j+=pri[i]) {
			int x=j;
			while(!(x%pri[i])) {
				h[j].push_back(i);
				x/=pri[i];
			}
		}
	}
	for(int i=1; i<=n; i++) {
		a[i]=read();
		t=a[i];
		if(flag)break;//如果之前存在过一次b>a,后面就可以一直放质数 
		else {
			for(int j=0; j<h[t].size(); j++) {//检验是否与之前的b互质 
				if(vp[h[t][j]]) {
					flag=1;
					break;
				}
			}
			if(!flag) {//互质则放入 
				for(int j=0; j<h[t].size(); j++)vp[h[t][j]]=1;
			}
			else {//不互质则暴力找一个符合的数 
				while(1){
					++t;
					if(prime(t)){
						for(int j=1;j<=m;j++){
							if(!(t%pri[j]))vp[j]=1;
							if(pri[j]>t)break;
						}
						break;
					}
				}
			}
		}
		cnt++;
		b[i]=t;
	}
	int i=1;
	while(cnt!=n) {//从小找没用过的质数 
		while(vp[i])i++;
		vp[i]=1;
		b[++cnt]=pri[i];
	}
	for(int i=1;i<=n;i++)printf("%d ",b[i]);
	return 0;
}

```


---

