# Sheikh (Easy version)

## 题目描述

This is the easy version of the problem. The only difference is that in this version $ q = 1 $ .

You are given an array of integers $ a_1, a_2, \ldots, a_n $ .

The cost of a subsegment of the array $ [l, r] $ , $ 1 \leq l \leq r \leq n $ , is the value $ f(l, r) = \operatorname{sum}(l, r) - \operatorname{xor}(l, r) $ , where $ \operatorname{sum}(l, r) = a_l + a_{l+1} + \ldots + a_r $ , and $ \operatorname{xor}(l, r) = a_l \oplus a_{l+1} \oplus \ldots \oplus a_r $ ( $ \oplus $ stands for [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)).

You will have $ q = 1 $ query. Each query is given by a pair of numbers $ L_i $ , $ R_i $ , where $ 1 \leq L_i \leq R_i \leq n $ . You need to find the subsegment $ [l, r] $ , $ L_i \leq l \leq r \leq R_i $ , with maximum value $ f(l, r) $ . If there are several answers, then among them you need to find a subsegment with the minimum length, that is, the minimum value of $ r - l + 1 $ .

## 说明/提示

In the first test case, $ f(1, 1) = 0 - 0 = 0 $ .

In the second test case, $ f(1, 1) = 5 - 5 = 0 $ , $ f(2, 2) = 10 - 10 = 0 $ . Note that $ f(1, 2) = (10 + 5) - (10 \oplus 5) = 0 $ , but we need to find a subsegment with the minimum length among the maximum values of $ f(l, r) $ . So, only segments $ [1, 1] $ and $ [2, 2] $ are the correct answers.

In the fourth test case, $ f(2, 3) = (12 + 8) - (12 \oplus 8) = 16 $ .

There are two correct answers in the fifth test case, since $ f(2, 3) = f(3, 4) $ and their lengths are equal.

## 样例 #1

### 输入

```
6
1 1
0
1 1
2 1
5 10
1 2
3 1
0 2 4
1 3
4 1
0 12 8 3
1 4
5 1
21 32 32 32 10
1 5
7 1
0 1 0 1 0 1 0
1 7```

### 输出

```
1 1
1 1
1 1
2 3
2 3
2 4```

# 题解

## 作者：c202201 (赞：6)


## C1(easy version)

#### 题意

定义 $sum(l,r) = \sum\limits_{i=l}^r a_i$，$xor(l,r) = \bigoplus_{i=l}^r a_i$，$f(l,r) = sum(l,r) - xor(l,r)$。

q 次询问，每次询问给出一组 $L,R$，求出一组 $ L \leq l \leq r\leq R $，使得 $f(l,r)$ 最大且 $r-l+1$ 最小。

保证 $q=1,L_1=1,R_1=n$。 

$t$ 组数据。

#### 思路

暴力很好想，对于每一次询问，暴力枚举 $l$ 和 $r$ 即可。

考虑正解。

考虑 $f$ 的值是怎么变化的。

显然 $\forall x,y$，有 $x+y \geq x \oplus y$ ，那么有 $xor(l-1,r) - xor(l,r) \leq a_{l-1} ,sum(l-1,r) - sum(l,r) = a_{l-1} $，所以 $ f(l-1,r) = sum(l-1,r) - xor(l-1,r) \geq sum(l,r) + a_{l-1} - xor(l,r) -a_{l-1} $，所以 $ f(l-1,r) \geq f(l,r) $，那么当 $ r $ 确定时，$ f $ 的值存在单调性，其图像画出来就长成下面这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/ege1cee4.png)

那么对于每一个 $r$ 的答案就是图中 $A$ 点。因为满足单调性，可以二分求得。那就只需枚举 $r$ 在比较就行了。时间复杂度为 $O(n \log n)$。

代码放最后了。

## C2(hard version)

#### 题意 

将 C1 的保证 $q=1$ 改为了保证 $q=n$。

#### 思路

那么原本的二分就不行了，由于单调性依旧存在，所以我们可以换一种思路，考虑什么时候 $f$ 的值会变小。

若当前异或和中 $x$ 的所有1位都为零，则 $x$ 的值一定会增大异或和，那么 $f$ 的值就变小了。

利用这个性质可以将原本的暴力优化很多，考虑一下优化后的时间复杂度。

至多枚举 $\log V$ 个数 $f$ 的值就会减小（$V$ 是值域），因为把 $V$ 的二进制为全每枚一遍一定会遇到一个数使得 $f$ 减小。

那么 $l$ 至多 $\log V$ 个，$r$ 至多 $\log V$ 个，加上 $q$ 次询问，时间复杂度就是 $O(n \log^2 V)$，可以过掉这题。

但其实还有一个坑，就是当 $a$ 数组中有 $0$ 时，会变成恐怖的 $O(n^3)$，但 $0$ 显然不会影响答案，可以直接不理它，那再搞个链表就行了。

## 代码

talking is cheap,show me your code.

### C1

```cpp
#include <bits/stdc++.h>
#define il inline
#define int long long
using namespace std;
const int N=1e5+5,inf=1e15+7;
int n,a[N],sum[N],xr[N],ans,ansl,ansr,l,r;
il int calc(int l,int r) {return sum[r]-sum[l-1]-(xr[r]^xr[l-1]);}
il void work(){
	scanf("%lld%*lld",&n);
	for(int i=1;i<=n;++i) scanf("%lld",a+i),sum[i]=sum[i-1]+a[i],xr[i]=(xr[i-1]^a[i]);
	scanf("%*lld%*lld"),ans=calc(1,n),ansl=l=1,ansr=r=n;
    int mn=inf;
    for (int i=l;i<=r;++i){
        int ll=i,rr=r,pos=r;
        while(ll<=rr){
            int mid=(ll+rr)>>1;
            if(calc(i,mid)<ans) ll=mid+1;
            else rr=mid-1,pos=mid;
        }
        if(calc(i,pos)<ans) ++pos;
        if(pos==r+1) continue;
        if(mn>pos-i+1) mn=pos-i+1,ansl=i,ansr=pos;
    }
    printf("%lld %lld\n",ansl,ansr);
}
signed main(){
	int T;
	scanf("%lld",&T);
	while(T--) work();
	return 0;
}
```

### C2

```cpp
#include <bits/stdc++.h>
#define il inline
using namespace std;
const int N=1e5+5;
il int read(){
	int x(0);
	char ch(getchar());
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) x=(x<<3)+(x<<1)+(ch&15),ch=getchar();
	return x;
}
int a[N],sum[N],xr[N],nxt[N],lst[N],ans,ansl,ansr;
il void work(){
	int L,R,ln0=0;
	int n=read(),Q=read();
	for(int i=1;i<=n;++i){
		a[i]=read(),sum[i]=sum[i-1]+a[i],xr[i]=(xr[i-1]^a[i]);
		if(a[i]) lst[i]=ln0,nxt[ln0]=i,ln0=i;
		else lst[i]=ln0;
	}
	nxt[n]=ln0=n+1;
	for(int i=n;i;--i){
		if(a[i]) ln0=i;
		else nxt[i]=ln0;
	}
	while(Q--){
		int L=read(),R=read(),ans=(xr[R]^xr[L-1]),ansl=L,ansr=R;
		if(L==R){
			printf("%d %d\n",L,L);
			continue;
		}
		if(nxt[L]>R&&!a[L]){
			printf("%d %d\n",L,L);
			continue;
		}
		if(!a[L]) L=nxt[L]; if(!a[R]) R=lst[R];
		for(int l=L;l<=R;l=nxt[l]){
			int r=R,now=ans;
			while(l<=lst[r]&&(now|a[r])==now) now^=a[r],r=lst[r];
			if(r-l<ansr-ansl) ansl=l,ansr=r;
			if((ans|a[l])>ans) break;
			ans^=a[l];
		}
		printf("%d %d\n",ansl,ansr);
	}
}
int main(){
	int T;
	scanf("%d",&T);
	while(T--) work();
	return 0;
}
```

不会有人不知道 C2 的代码可以把 C1 过了吧。

写完力qwq。



---

## 作者：MoyunAllgorithm (赞：5)

## 题意
给你一个 $N (1 \le N \le 10^5)$ 的非负数组 $a$。定义 $sum_{i,j}= a_i + a_{i+1}+\cdots +a_j,xor_{i,j}=a_i \oplus a_{i+1} \oplus \cdots \oplus a_j$。 定义 $f(i,j)= sum_{i,j}-xor_{i,j}$。进行 $1$ 次询问，给定 $l=1,r=N$，求区间 $[l,r]$ 的所有子区间 $[l_1,r_1]$ 中，$f(l_1,r_1)$ 最大的前提下长度最短的那一个。

## 分析

发现对于区间 $[l,r]$，$f(l,r+1) \ge f(l,r)$。

**证明**

$f(l,r+1)-f(l,r)$

$=sum_{l,r+1}-xor{l,r+1}-sum_{l,r}+xor_{l,r}$

$=a_{r+1}- xor_{l,r+1}+ xor_{l,r}$。

因为 $ xor_{l,r+1}- xor_{l,r} \le a_{r+1}$ (因为异或是不进位加法)

所以得到 $f(l,r+1)-f(l,r) \ge 0$。同理可证 $f(l-1,r) \ge  f(l,r)$。

这说明：**答案区间的 $f$ 值一定与询问区间的 $f$ 值相等；当区间的左端点固定，当它的右端点向右移动时，$f$ 值是单调不减的**。

这启示我们进行二分。

## 具体做法

对于每个询问 $(l,r)$，

首先我们求出 $goal=f(l,r)$。运用前缀和和前缀异或可以 $O(1)$ 求 $f$ 值。

定义 $ansl=l,ansr=r$，因为 $[l,r]$ 一定是一个满足要求的子区间。

枚举答案区间的左端点 $l_1$ (代码中命名为 $i$)。对于每个 $i$，二分答案区间的右端点 $j( i \le j \le r)$。如果 $j$ 满足 $f(i,j)=goal$，则该区间符合要求，缩小 $j$； 反之增加 $j$。如果存在符合要求的 $j$,则对 $ansl$ 和 $ansr$ 进行更新。

## 考场代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=1e5+5;
int Read()
{
	//快读省略
}
int T,N,Q;
long long psum[MAXN],pxor[MAXN];
int a[MAXN];
long long Func(int l,int r)
{
	return psum[r]-psum[l-1]-(pxor[r]^pxor[l-1]);
}//给区间求f
signed main()
{
	T=Read();
	while(T--)
	{
		N=Read(),Q=Read();
		for(int i=1;i<=N;i++) a[i]=Read();
		for(int i=1;i<=N;i++)
		{
			psum[i]=psum[i-1]+a[i];
			pxor[i]=pxor[i-1]^a[i];
		}
		int l=Read(),r=Read();
		long long goal=Func(l,r);
		int ansl=l,ansr=r;
		for(int i=l;i<=r;i++)
		{
			int lb=i,rb=r;
			int pos=0;//记录最优的 mid
			while(lb<=rb)
			{
				int mid=(lb+rb)/2;
				if(Func(lb,mid)!=goal) lb=mid+1;
				else 
				{
					rb=mid-1;
					pos=mid;
				}
			}
			if(pos==0) continue;//没有符合条件的右端点
			if(ansr-ansl+1>pos-i+1) ansr=pos,ansl=i;
		}
		printf("%lld %lld\n",ansl,ansr);
	}
	return 0;
}
```

考场代码**无法通过**这道题。但如果你认真阅读了这篇题解，你可以找到该代码的**一处错误**。（但比赛期间我并没有找到qwq）

**错误：** 二分时，候选的答案区间是 $[i,mid]$。 代码中写成了 $[lb,mid]$。~~非常智障啊~~ 将 `Func(lb,mid)` 改为 `Func(i,mid)` 即可通过本题。





---

## 作者：truekun (赞：3)

**题意**：给出一个数组 $a_1...a_n$，$q$ 次询问，每次求 $[L,R]$ 内任意子区间的和减去。该区间的异或值得到的差的最大值，若有多个最大值，取区间长度最短的，若仍有多个区间，任取一个输出即可。在简单版本中，保证 $q=1,L=1,R=n,n\le2\times10^5$。




**分析**：什么时候异或和会比直接求和小？当两个 $2k$ 异或抵消掉的时候。

虽然还有一些性质可以挖掘，但在 Easy version 中，我们只需要注意到，随着区间变长，这种“抵消”只会越来越多，所有差值也只会越来越大，换言之，答案随区间长度具有单调性。

所有最大答案就是整个区间的结果，至于最短的区间，我们可以固定左端点，则答案关于右端点单调，可以进行二分找到使得答案仍不小于整个区间答案的前提下，最短的长度。

所以只需要前缀和求+枚举左端点+二分长度即可。


**注意判断越界，要不 check 函数会挂**。




时间复杂度 $\operatorname O(n\log n)$。






~~附代码（码风清奇，不喜勿喷~~~~）~~

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int unsigned long long
int a[100001];
int sum[100001];//求和 
int ans[100001];//异或和 
int cha;
bool check(int m,int l,int n){
	int r=l+m-1;
	int summ=sum[r]-sum[l-1];
	int anss=ans[r]^ans[l-1];
	if(summ-anss==cha){
		return true;
	}else{
		return false;
	}
}
signed main(){
	freopen("a.txt","r",stdin);
	int t;
	cin>>t;
	while(t--){
		memset(sum,0,sizeof(sum));
		memset(ans,0,sizeof(ans));
		int n,q;
		int mmin=1e18;
		int ansl,ansr;
		cin>>n>>q;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			sum[i]=sum[i-1]+a[i];
			ans[i]=ans[i-1]^a[i];
		}
		cha=sum[n]-ans[n];
		while(q--){
			int s,e;
			cin>>s>>e;
			for(int i=1;i<=n;i++){
				int l=1,r=n-i+2;
				while(l<r){
					int mid=(l+r)>>1;
					if(check(mid,i,n)){
						r=mid;
					}else{
						l=mid+1;
					}
				}
				if(i+l-1>n) continue;
				if(l<mmin){
					mmin=l;
					ansl=i,ansr=i+l-1;
				}
			}
			cout<<ansl<<" "<<ansr<<endl;
		}
	}
	return 0; 
} 
```

---

## 作者：kernel_panic (赞：3)

## 题目大意
给你 $1$ 个长度为 $n$ 的序列 $\{a_i\}$，我们定义 $1$ 个区间 $a_{l\cdots r}$ 的价值为 $\sum_{i=l}^{r}a_i-\bigoplus_{i=l}^{r}a_i$。

你需要选择 $1$ 个区间 $a_{l\cdots r}$，最大化价值的同时，最小化区间长度。

其中 $\oplus$ 代表按位异或运算。

## 思路
由于异或可以看作 $2$ 进制不进位加法，我们可以发现当区间长度增加 $1$ 时，其价值必然单调不减。

那么最后的最大价值必然是 $a_{1\cdots n}$ 的价值，所以我们只需要最小化区间长度。

只有 $1$ 组询问，可以想到枚举最终的区间。而答案具有单调性，所以我们可以枚举区间左端点，二分区间右端点，每次 `check` 检查当前区间的价值是否仍然等于 $a_{1\cdots n}$ 的价值即可。

预处理前缀和即可 $O(1)$ 进行每次的 `check`。

总时间复杂度 $O(n\log n)$。

## 代码
```cpp
#include <cstdint>
#include <iostream>

using i64 = int64_t;
constexpr size_t N = 1 << 20;

int T, n, q, L, R;
i64 ss[N], sx[N], a[N];

bool check(int l, int r, i64 ans) { return (ss[r] - ss[l - 1]) - (sx[r] ^ sx[l - 1]) == ans; }

int main() {
    std::ios::sync_with_stdio(false);
    std::cin >> T;
    while (T--) {
        std::cin >> n >> q;
        for (int i = 1; i <= n; i++) std::cin >> a[i];
        for (int i = 1; i <= n; i++) ss[i] = ss[i - 1] + a[i], sx[i] = sx[i - 1] ^ a[i];
        std::cin >> L >> R;
        i64 ans = (ss[R] - ss[L - 1]) - (sx[R] ^ sx[L - 1]);
        int cl = L, cr = R;
        for (int i = L; i <= R; i++) {
            int l = i, r = R, res = 0;
            while (l <= r) {
                int mid = (l + r) / 2;
                if (check(i, mid, ans)) r = mid - 1, res = mid;
                else l = mid + 1;
            }
            if (res == 0) continue;
            if (cr - cl + 1 > res - i + 1) cl = i, cr = res;
        }
        std::cout << cl << " " << cr << "\n";
    }
    return 0;
}
```

---

## 作者：星星与辰 (赞：3)

## 题意
给出一个数列 $A$，我们定义一个区间 $[l,r]$ 的价值为 ${\sum_{i=l}^rA_i}-{\bigoplus_{i=l}^{r}A_i}$，现在给出 $Q$ 次询问，每次询问会给出一个区间 $[L,R]$，你要求出该区间的所有子区间中价值最大的那个区间并输出，若有多个价值相同且最小的区间，我们应输出其中区间长度（即 $l-r+1$）最短的那个。

## 思路
~~没有去想能过C1却不能过C2的做法~~

先思考价值的实际含义，看到异或，我们会想到不进位加法，也就是说它与真正的加法的差别在于不进位，决定区间价值的实际上是区间异或时被不进位卡掉的值的和。显然地，我们发现，对于任意一个可以左右扩展的区间 $[l,r]$，它的贡献一定小于等于 $[l-1,r]$ 和 $[l,r+1]$（因为可以导致更多可能的进位被卡掉）。于是我们知道区间 $[L,R]$ 它本身就一定是价值最大的子区间之一。这时我们如果我们尝试删去区间中没有贡献的数的话，我们就能求到更短的那个区间。

那么那些数没有贡献，假设当前区间的异或和为 $now$，而我们判断能不能删的端点的值为 $x$，于是我们发现只要 $x$ 当前能让区间的异或和进位，那么它就对价值有贡献，就不能删，否则就可以删。异或里面进了位的位数为 $0$，只要 $now$ 和与 $x$ 在二进制下的某一位使得 $x$ 上是 $1$，而 $now$ 上不是，则说明有贡献，不能删。那不就要保证 $x$ 上对应的位数是 $1$ 嘛，于是我们可以简单地把判断是否能删写成这样的式子 $[now|x>=now]$。在此基础上，我们发现每当我们删掉一个数（$0$ 除外）时，一定会减少异或和在二进制下为 $1$ 的位数，于是很容易发现最多会删掉 $\log_2now$（即每一位 $1$ 都要花费一个数去删）次。

现在维护删数，发现区间左右两边都能删，而且可能不能贪心地选，那就考虑固定区间左端点不变，从最右端开始删右端点，暴力判断是否能删，删完后判断是否为更优的答案，这样做就可以做到 $\Theta(n+q\log_2^2V)$ 的时间复杂度，其中 $V={\bigoplus _2{\max_{i=L}^{i=R}{A_i}}})$
，空间复杂度为 $O(n)$，已经可以过了~~没想到CF竟然没逼我优化~~。

特殊地，因为 $0$ 不会去除任何一位的 $1$，所以我们在删数时可以直接省略掉，可以直接维护一个链表，保证链表上没有 $0$，然后在链表上条就行了。
## Code
```cpp
//私人所有，禁止抄袭
//PS:log方的写法
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int num=0;
	char ch=getchar();
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))num=(num<<1)+(num<<3)+(ch&15),ch=getchar();
	return num;
}
int a[100010],las[100010],nxt[100010],xorsum[100010];
int main(){
	int T=read()+1;
	while(--T){
		int n=read(),Q=read()+1,syc=0;
		//syc为上一个非0的数
		for(int i=1;i<=n;++i){
			a[i]=read();
			xorsum[i]=xorsum[i-1]^a[i];
			if(a[i])las[i]=syc,nxt[syc]=i,syc=i;
			else las[i]=syc;
			//为了方便跳，让0单向地加入链表
		}
		syc=n+1;
		for(int i=n;i>0;--i){
			if(a[i])syc=i;
			else nxt[i]=syc;
		}
		while(--Q){
			int l=read(),r=read();
			if(l==r){
				printf("%d %d\n",l,r);
				continue;
			}
			//这里实际上是特判区间全为0的情况
			if(nxt[l]>r&&!a[l]){
				printf("%d %d\n",l,l);
				continue;
			}
			if(!a[l])l=nxt[l];if(!a[r])r=las[r];
			int maxn=xorsum[r]^xorsum[l-1],prel=l,prer=r,ansl=l,ansr=r;
			//维护左端点，删右端点
			while(prel<=r){
				int now=maxn;
				prer=r;
				while(las[prer]>=prel&&(now|a[prer])<=now)now^=a[prer],prer=las[prer];
				if(ansr-ansl>prer-prel)ansl=prel,ansr=prer;//判断答案是否更优
				if(nxt[prel]<=r&&(maxn|a[prel])<=maxn)maxn^=a[prel],prel=nxt[prel];
				else break;
			}
			printf("%d %d\n",ansl,ansr);
		}
	}
	return 0;
}
//(。・∀・)ノ
```
## Another Solution
在此基础上，我们是否能尝试优化这样的做法，我们发现当左端点右移时，能到达的最左的右端点也会右移，（左边删得少时，右边会删得可能更多），那直接写个双指针，左指针指向左端点，右指针指向右端点，然后时间复杂度就变为了 $\Theta(n+q\log_2V)$。这是一个优秀的解法~~但我没去写~~！

~~这部分是后面后头补的，因为有一个我教的人交了发跟我代码很像的题解，心里不太踏实。~~

然后我们发现了这个解法的不足之处，我们得先在不删左端点时，跑一遍右端点最远跑哪，然后还发现在维护右指针右移时非常麻烦，因为右移左指针时要将所有可能更改的右指针的位置都算上一遍，显然所有删除的左端点最多会带来 $\log_2 V$ 个这样的位置（因为右端点现在是加回来，如果在左右两边同时删除了这个位置上的 $1$，显然右边的位置就不合法了，那必须保证这个位置在区间中），因为每一位的 $1$ 在第一次只删右端点的过程中只会被一个 $A_i$ 删掉，我们可以记录下来，然后回头看自己会加回哪个位置，就把它们加回来，可以事先记录每一个 $A_i$ 二进制下会改变哪个位置。

但是这个做法常数比前面的大很多，CF上实测较慢，事实上前面的做法很难跑遍全部的 $A_i$ 的二进制上有啥，~~主要是出题人每组数据都这么卡没意思~~，在预处理时会慢很多，但是在询问很大时可能会更快。
## Another Code
```cpp
//私人所有，禁止抄袭
//PS:log的写法
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int num=0;
	char ch=getchar();
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))num=(num<<1)+(num<<3)+(ch&15),ch=getchar();
	return num;
}
inline int Max(const int& x,const int& y){return x<y?y:x;}
int a[100010],las[100010],nxt[100010],xorsum[100010],bit[40];
vector<int>A[100010];
int main(){
	int T=read()+1;
	while(--T){
		int n=read(),Q=read()+1,syc=0;
		//syc为上一个非0的数
		for(int i=1;i<=n;++i){
			a[i]=read();
			xorsum[i]=xorsum[i-1]^a[i];
			if(a[i])las[i] = syc,nxt[syc] = i,syc = i;
			else las[i] = syc;
			A[i].clear();
			//为了方便跳，让0单向地加入链表
		}
		nxt[syc]=n+1;
		syc=n+1;
		for(int i=n;i>0;--i){
			if(a[i])syc=i;
			else nxt[i]=syc;
		}
		
		//预处理每个A_i二进制上有啥
		for(int k=1,ch=1;k<=30;++k,ch<<=1){
			for(int i=1;i<=n;++i){
				if(a[i]&ch) A[i].push_back(k);
			}
		}
		while(--Q){
			int l=read(),r=read();
			if(l==r){
				printf("%d %d\n",l,r);
				continue;
			}
			//这里实际上是特判区间全为0的情况
			if(nxt[l]>r&&!a[l]){
				printf("%d %d\n",l,l);
				continue;
			}
			if(!a[l])l=nxt[l];if(!a[r])r=las[r];
			int maxn=xorsum[r]^xorsum[l-1],prel=l,prer=r,ansl,ansr,now=maxn;
			for(int i=1;i<=30;++i)bit[i]=l;
			//先跑一遍最远跑多远
			while(las[prer]>=l&&(now|a[prer])<=now){
				for(int i=0;i<A[prer].size();++i){
					bit[A[prer][i]]=prer;
				}
				now^=a[prer],prer=las[prer];
			}
			ansl=l,ansr=prer;
			now=maxn;
			//维护左端点，删右端点
			if(nxt[l]<=r&&(now|a[prel])==now){
				now^=a[prel];
				for(int i=0;i<A[prel].size();++i){
					prer=Max(prer,bit[A[prel][i]]);
					//取最右边的该加入区间的位置
				}
				prel=nxt[prel];
				while(prel<=r){
					if(prer<=prel){
						ansl=l,ansr=l;
						break;
					}
					if(ansr-ansl>prer-prel)ansl=prel,ansr=prer;//判断答案是否更优
					if(nxt[prel]<=r&&(now|a[prel])==now){
						for(int i=0;i<A[prel].size();++i){
							prer=Max(prer,bit[A[prel][i]]);
						}
						now^=a[prel],prel=nxt[prel];
					}
					else break;
				}
			}
			printf("%d %d\n",ansl,ansr);
		}
	}
	return 0;
}
//(。・∀・)ノ
```


---

## 作者：littleqwq (赞：2)

# CF1732C1 Sheikh (Easy version) 题解

#### 大致意思： 

$q$ 次询问，每次求 $l$ ~ $r$ 的区间和减去区间异或值得到差的最大值，若有多个最大值，去取区间长度最短的，若仍然有多个区间，输出其中一个即可，保证 $q = 1, L = 1, R = n$。

#### 大致思路：

算出 $sum[i]$ 为前 $i$ 个数之和， $xor[i]$ 为前 $i$ 个数的异或值。

- 二分，不详讲，大致就是根据定义 $f(i, j) = sum_{i,j} - xor_{i,j}$，发现对于区间 $[l,r]$ ，$f(l,r+1) ≥ f(l,r)$。

#### 证明：

感谢一楼大佬的证明，让我对这道题更加印象深刻，更加理解。

$f(i, j + 1) - f(i, j)$
$= sum_{i, j + 1} - xor_{i, j + 1} - sum_{i, j} + xor_{i, j}$

最后得出等于 $ar_{j + 1} - xor_{i, j + 1} + xor_{i, j}$，证明出 $f(i, j + 1) - f(i, j) ≥ 0$。

这说明了当左端点固定时，右端点向右移动时， $f(i, j)$ 是单调不减的，具有单调性，显然二分。

#### 代码实现：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5 + 10;
inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-'){
			w = -1;
		}
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}
int n, q, ar[N], sum[N], g[N];//sum：前缀和 g：前缀异或 
int get_sum(int l, int r)
{
	return sum[r] - sum[l - 1] - (g[r] ^ g[l - 1]);//计算差值 
}
signed main()
{
	int _;
	_ = read();
	while (_ --)
	{
		n = read(), q = read();for(int i = 1;i <= n; ++ i) ar[i] = read(), sum[i] = sum[i - 1] + ar[i], g[i] = g[i - 1] ^ ar[i];
		int l = read(), r = read();
		int res = get_sum(l, r);
		int ll = l, rr = r;
		for(int i = 1;i <= r; ++ i)//枚举左端点
		{
			int Left = i, Right = r, now = 0;
			while(Left <= Right)
			{
				int mid = (Left + Right) >> 1;
				if(get_sum(i, mid) != res) Left = mid + 1;
				else Right = mid - 1, now = mid;
			}
			if(now > 0 && rr - ll + 1 > now - i + 1) ll = i, rr = now;  
		}
		cout << ll << " " << rr << "\n";
	}
	return 0;
}
```

- 双指针，定义 $get\_sum(l, r)$ 为 $l$ ~ $r$ 的区间和异或之差，我们可以使用尺取法， $l, r$ 指针开始均为 $1$ ，枚举 $l$ ，在定义一个 $res$ 存最大的 $get\_sum(n, n)$ ，如果 $get\_sum(l, r)  < res$ 且 $r$ 没有超过 $n$，那么明显 $r$ 可以往后移动，最后再看看当前选择区间是否合法，合法即为目前最优区间。

#### 代码实现：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e6 + 10;
inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-'){
			w = -1;
		}
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}
int n, q, ar[N], sum[N], g[N];//sum：前缀和 g：前缀异或 
int get_sum(int l, int r)
{
	return sum[r] - sum[l - 1] - (g[r] ^ g[l - 1]);//计算差值 
}
signed main()
{
	int _;
	_ = read();
	while (_ --)
	{
		n = read(), q = read();for(int i = 1;i <= n; ++ i) ar[i] = read(), sum[i] = sum[i - 1] + ar[i], g[i] = g[i - 1] ^ ar[i];
		int l = 1, r = 1;
		int res = sum[n] - g[n];
		int ll = read(), rr = read();
		for(int i = 1;i <= n; ++ i)//枚举左端点
		{
			if(r < i) r = i;
			while(r <= n && get_sum(i, r) < res)
			{
				++ r;
			}
            if(r > n) break;
			if(rr - ll + 1 > r - i + 1) ll = i, rr = r;  
		}
		cout << ll << " " << rr << "\n";
	}
	return 0;
}
```

这样这道题就完成啦！！！

---

## 作者：xujingyu (赞：1)

本题暴力有分

**正解：**

$∵f(l,r)-f(l,r-1)$

$=sum(l,r)-xor(l,r)-sum(l,r-1)+xor(l,r-1)$

$=a_{r}-(xor(l,r)-xor(l,r-1))$

又 $∵xor(l,r)-xor(l,r-1)\le a_{r}$（一路异或过来肯定不如加法啊，异或就是没进位的加法）

（此步骤也可以理解为：$∵sum(l,r)\ge xor(l,r)$，并且 $sum(l,r-1)\ge xor(l,r-1)$，$∴xor(l,r)-xor(l,r-1)\le sum(l,r)-sum(l,r-1)$。）

$∴$ 原式 $>0$，即 $f(l,r)\ge f(l,r-1)$。

也就是说当区间长度增加，价值也会随之增加（或相等）。

那么**最大的就是** $\texttt{f(1,n)}$ 咯，将区间最小化即可。

左端点枚举 $n$ 次，右端点二分，对于每次`while`，`check()`当前区间的价值是否仍然等于最大价值即可。

时间复杂度 $\texttt{O(n}\ \texttt{log}\ \texttt{n)}$。

**注意,那些我踩过的坑:**

* 要开`long long`！
* 若要写 $xo_i=xo_{i-1}⊕a$ 的话，记得加括号！（即`xo[i] = (xo[i - 1] ^ a)`）
* 变量没初始化（刚犯完）

```php
#include <bits/stdc++.h>
#define int long long
using namespace std;

int n,a,sum[100001],xo[100001],t,l,r,ll,rr;
int xxxxx;//输入一个1
int ansl,ansr;
int mostmid;

int f(int l,int r)//题目中的f
{
	return sum[r] - sum[l - 1] - (xo[r] ^ xo[l - 1]);//计算f(l,r)
}

signed main()
{
	scanf("%lld",&t);
	while(t--)
	{
		scanf("%lld%lld",&n,&xxxxx);//在本题没用的xxxxx呵呵
		for(int i = 1;i <= n;i++)
		{
			scanf("%lld",&a);
			sum[i] = sum[i - 1] + a;
			xo[i] = (xo[i - 1] ^ a);
		}
		scanf("%lld%lld",&l,&r);
		int x = f(l,r);//所有最大!
		ansl = l,ansr = r;
		for(int i = l;i <= r;i++)
		{
			ll = i,rr = r;
			mostmid = 0;//最优的mid
			while(ll <= rr)
			{
				int mid = (ll + rr) / 2;
				if(f(i,mid) == x)//达到最优,即可以缩小右端点范围
				{
					rr = mid - 1;
					mostmid = mid;
				}
				else ll = mid + 1;
			}
			if(!mostmid) continue;//没更新右端点
			if(ansr - ansl + 1 > mostmid - i + 1)//长度更小
			{
				ansr = mostmid;//更新最优答案
				ansl = i;
			}
		}
		//printf("这是输出!");
		printf("%lld %lld\n",ansl,ansr);
	}
	return 0;
}
```

---

## 作者：ny_Dacong (赞：0)

# 思路

先来看一个定理：

>**定理**：对于自然数 $a,b$，$a+b \ge a \oplus b$。
>
>**证明**：将 $a$ 二进制下的第 $i$ 位（从低到高）记为 $a_i$。$b$ 同理。
>
>进行分讨：
>
>- $a_i = 0,b_i = 0$，那么 $a_i+b_i = a_i \oplus b_i$。
>- $a_i = 0,b_i = 1$，那么 $a_i+b_i = a_i \oplus b_i$。
>- $a_i = 1,b_i = 0$，那么 $a_i+b_i = a_i \oplus b_i$。
>- $a_i = 1,b_i = 1$，那么 $a_i+b_i > a_i \oplus b_i$。
>
>关键就在于两个都为 $1$ 的情况。由于加法可以进位，而异或不可以，所以 $a+b \ge a \oplus b$。

有了这些之后，就可以推出本题中最重要的结论了：

>**结论**：$f(l,r) \le f(l-1,r)$。
>
>**证明**：
>
>对 $f(l-1,r)$ 进行转化。
>
>$$\begin{aligned} & f(l-1,r) \\ = & \operatorname{sum}(l-1,r)-\operatorname{xor}(l-1,r) \\ = & a_{l-1} + \operatorname{sum}(l,r) - (a_{l-1} \oplus \operatorname{xor}(l,r))\end{aligned}$$
>
>要比较两数的大小，可以让两数相减。因此：
>
>$$\begin{aligned} & f(l,r)-f(l-1,r) \\ = & \operatorname{sum}(l,r)-\operatorname{xor}(l,r) - (a_{l-1} + \operatorname{sum}(l,r) - (a_{l-1} \oplus \operatorname{xor}(l,r))) \\ = & \operatorname{sum}(l,r)-\operatorname{xor}(l,r) - a_{l-1} - \operatorname{sum}(l,r) + (a_{l-1} \oplus \operatorname{xor}(l,r)) \\ = & -a_{l-1}+(a_{l-1} \oplus \operatorname{xor}(l,r)) - \operatorname{xor}(l,r) \\ = & a_{l-1} \oplus \operatorname{xor}(l,r) - (a_{l-1}+\operatorname{xor}(l,r)) \end{aligned}$$
>
>根据上面的定理，$a_{l-1} \oplus \operatorname{xor}(l,r) \le a_{l-1}+\operatorname{xor}(l,r)$，所以 $a_{l-1} \oplus \operatorname{xor}(l,r) - (a_{l-1}+\operatorname{xor}(l,r)) \le 0$。
>
>因此 $f(l,r) \le f(l-1,r)$。得证。

根据这个结论，当我们固定右端点，左端点在询问区间内滑动时，$f(i,r)(l \le i \le r)$ **单调不增**。因此 $\max(f(i,r)(l \le i \le r)) = f(l,r)$。

当然题目还要求长度最小，所以二分枚举最右边的 $i$ 且满足 $f(i,r) = f(l,r)$。

在实际实现中，我们知道，**异或有结合律**，并且**异或的逆运算是再异或一遍同样的数**，所以题目中：

$$\begin{aligned} & \operatorname{xor}(l,r) \\ =  & (\operatorname{xor}(1,l-1) \oplus \operatorname{xor}(1,l-1)) \oplus \operatorname{xor}(l,r) \\ = & \operatorname{xor}(1,l-1) \oplus (\operatorname{xor}(1,l-1) \oplus \operatorname{xor}(l,r)) \\ = & \operatorname{xor}(1,l-1) \oplus \operatorname{xor}(1,r) \end{aligned}$$

这样我们就转换成类似于前缀和的形式了。搭配上用前缀和预处理出的 $\operatorname{sum}$，我们可以快速求得 $f(l,r) = \operatorname{sum}(1,r)-\operatorname{sum}(1,l-1)-(\operatorname{xor}(1,r) \oplus \operatorname{xor}(1,l-1))$。

最后分析时间复杂度：枚举左端点 $O(n)$，查询分界点 $O( \log n)$。单次询问 $O(n \log n)$。

# AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t;
long long n,ql,qr,Max,len,asl;
long long num[100005],sum[100005],x[100005];
long long erfen(long long l,long long r){
	long long mid,rr;
	rr = r;
	while(l <= r){
		mid = l+((r-l)>>1);
		if(sum[rr]-sum[mid-1]-(x[rr]^x[mid-1]) < sum[rr]-sum[ql-1]-(x[rr]^x[ql-1])){
			r = mid-1;
		}else{
			l = mid+1;
		}
	}
	return r;
}
int main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld%*d",&n);
		Max = -1,len = 0x3f3f3f3f3f3f3f3f;
		asl = 0;
		memset(x,0,sizeof(long long)*(n+3));
		memset(num,0,sizeof(long long)*(n+3));
		memset(sum,0,sizeof(long long)*(n+3));
		for(long long i = 1; i <= n; i++){
			scanf("%lld",&num[i]);
			sum[i] = sum[i-1]+num[i];
			x[i] = x[i-1]^num[i];
		}
		scanf("%lld%lld",&ql,&qr);
		for(long long i = ql; i <= qr; i++){
			static long long tp;
			tp = erfen(ql,i);
			if(Max == sum[i]-sum[tp-1]-(x[i]^x[tp-1])){
				if(i-tp+1 < len){
					len = i-tp+1;
					asl = tp;
				}
			}else if(Max < sum[i]-sum[tp-1]-(x[i]^x[tp-1])){
				Max = sum[i]-sum[tp-1]-(x[i]^x[tp-1]);
				len = i-tp+1;
				asl = tp;
			}
		}
		printf("%lld %lld\n",asl,asl+len-1);
	}
	return 0;
}
```

---

## 作者：xiaoxiaoxia (赞：0)

# 题意简述
$q$ 每次求 $L$ 到 $R$ 内任意子区间的和减去该区间的异或值得到的差的最大值。若有多个最大值，取区间长度最短的，若仍有多个区间，任取一个输出即可。
# 思路介绍
这道题我用的是一开始先使用前缀和计算异或的值以及和，然后用尺取法不断地查找最优解。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 100005
int n,q,a[N],x[N];
long long s[N];

int main(){
	int t;
	for(scanf("%d",&t);t;t--){//多组数据
		scanf("%d%d",&n,&q);
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			s[i]=s[i-1]+a[i];//前缀和记录
			x[i]=x[i-1]^a[i];
		}
		long long ans=s[n]-x[n];//先取一个初始值
		int ansl,ansr,l,r=1;
		scanf("%d%d",&ansl,&ansr);//答案区间
		for(l=1;l<=n;l++){
			if(r<l)r=l;//可以省略
			while(s[r]-s[l-1]-(x[r]^x[l-1])<ans&&r<=n){//尺取法
				r++;
			}
			if(r>n)break;//越界了
			if(r-l<ansr-ansl){//更改答案
				ansl=l;
				ansr=r;
			}
		}
		printf("%d %d\n",ansl,ansr);//输出
	}
	return 0;
}
```

---

## 作者：FireRain (赞：0)

# 思路

首先证明一下当序列扩大时答案一定不劣。考虑 $f(l,r)$ 到 $f(l,r + 1)$ 的变化。

$$
\begin{aligned}
f(l,r) - f(l,r + 1) &= s_{l,r} - xs_{l,r} - s_{l,r + 1} + xs_{l,r + 1}\\
                    &= xs_{l,r + 1} - xs_{l,r} - a_{r + 1}\\
                    &\leq 0
\end{aligned}
$$

同理可证 $f(l,r) \geq f(l - 1,r)$。因此上述猜想成立。

那么问题转变为找到最小的 $r' - l'$ 使得 $f(l',r') = f(l,r)$。

显然，被我们去掉的数一定满足 $\sum x = \oplus x$，根据抽屉原理这种数不超过 $30$ 个（提前处理掉 $0$）。

直接暴力枚举即可。

# Code

```cpp
#include <bits/stdc++.h>
#define re register
#define int long long

using namespace std;

const int N = 2e5 + 10;
int n,q;
int arr[N],s[N],xs[N];

inline int read(){
    int r = 0,w = 1;
    char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        r = (r << 3) + (r << 1) + (c ^ 48);
        c = getchar();
    }
    return r * w;
}

inline void solve(){
    int len;
    vector<int> v;
    n = read(),q = read();
    for (re int i = 1;i <= n;i++){
        arr[i] = read();
        s[i] = s[i - 1] + arr[i];
        xs[i] = xs[i - 1] ^ arr[i];
        if (arr[i] > 0) v.push_back(i);
    }
    len = v.size();
    while (q--){
        int l,r,p;
        l = p = read(),r = read();
        int ansl = l,ansr = r,Min = r - l + 1;
        l = lower_bound(v.begin(),v.end(),l) - v.begin();
        r = upper_bound(v.begin(),v.end(),r) - v.begin() - 1;
        if (!len || l > r){
            printf("%lld %lld\n",p,p); continue;
        }
        for (re int i = l;i <= l + 30;i++){
            for (re int j = r - 30;j <= r;j++){
                if (i > j || i >= len || j >= len || j < 0) continue;
                int L = v[i],R = v[j];
                if ((s[R] - s[L - 1]) - (xs[R] ^ xs[L - 1]) == (s[v[r]] - s[v[l] - 1]) - (xs[v[r]] ^ xs[v[l] - 1])){
                    if (R - L + 1 < Min){
                        Min = R - L + 1;
                        ansl = L; ansr = R;
                    }
                }
            }
        }
        printf("%lld %lld\n",ansl,ansr);
    }
}

signed main(){
    int T; T = read();
    while (T--) solve();
    return 0;
}
```

---

## 作者：ZBH_123 (赞：0)

## 题目分析
### 基本公式
先来看一个式子：$a-b \le a \oplus b \le a+b$。在 $a \oplus b$ 最小的情况下，$a \oplus b$ 会和 $a-b$ 相等；在最大的情况下 $a \oplus b$ 会和 $a+b$ 相等。因此原式得证。
### 思路解析
设 $\operatorname{sum}(l,r)$ 为 $[l,r]$ 的和，$\operatorname{xor}(l,r)$ 为 $[l,r]$ 的异或和，$f(l,r)=\operatorname{sum}(l,r)-\operatorname{xor}(l,r)$，则 $f(l,r)$ 和 $f(l,r+1)$ 的关系可以如下推导：
$$\begin{aligned} f(l,r+1)-f(l,r) &= \operatorname{sum}(l,r+1)-\operatorname{sum}(l,r)-\operatorname{xor}(l,r+1)+\operatorname{xor}(l,r) \\ &= a_{r+1}-(\operatorname{xor}(l,r+1)-\operatorname{xor}(l,r)) \end{aligned}$$
设 $\operatorname{xor}(l,r)$ 为 $A$，$a_{r+1}$ 为 $B$，由上面提到的基本公式可得 $0 \le a_{r+1}-(\operatorname{xor}(l,r+1)-\operatorname{xor}(l,r)) \le 2 \cdot a_{r+1}$。所以，当区间的左端点固定时，右端点向右移动时，$f(l,r)$ 不会减少，这样我们就可以进行二分查找。先将最终答案 $ans$ 设为 $f(1,n)$，接着从前往后扫一遍数组，并对当前扫到的元素之后的元素进行二分查找。下面是二分查找部分的示范代码：
```cpp
pos=0;
l=i,r=n;
while(l<=r){
	int mid=(l+r)/2;
	if(f(i,mid)==ans){
		pos=mid,r=mid-1;
	}
	else{
		l=mid+1;
	}
}
```
**AC code：**
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn=1e5;
int t,n,q,L,R;
ll a[maxn+5],s[maxn+5],xs[maxn+5];
ll f(int l,int r){
	return s[r]-s[l-1]-(xs[r]^xs[l-1]);
}
int main(){
	cin>>t;
	while(t--){
		memset(s,0,sizeof s);
		memset(xs,0,sizeof xs);
		int l,r,pos,ansl,ansr;
		ll ans;
		cin>>n>>q;
		ansl=1,ansr=n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			s[i]=s[i-1]+a[i],xs[i]=xs[i-1]^a[i];
		}
		ans=f(1,n);
		cin>>L>>R;
		for(int i=1;i<=n;i++){
			pos=0;
			l=i,r=n;
			while(l<=r){
				int mid=(l+r)/2;
				if(f(i,mid)==ans){
					pos=mid,r=mid-1;
				}
				else{
					l=mid+1;
				}
			}
			if(pos==0){
				continue;
			}
			if(pos-i+1<=ansr-ansl+1){
				ansl=i,ansr=pos;
			}
		}
		cout<<ansl<<' '<<ansr<<endl;
	}
	return 0;
}
```

---

## 作者：_sunkuangzheng_ (赞：0)

**【题目大意】**

给定序列 $a$，选取一段子区间 $[l,r]$，满足：

- $f(l,r) = \sum\limits_{i=l}^r a_i - \oplus_{i=l}^r a_i$ 最大。

- 在满足上一条限制的前提下，$r-l+1$ 最小。

求出任意一组 $[l,r]$。

**【题目分析】**

- $\textbf{Hint 1}$

考虑问题的弱化版：如果不要求 $r-l+1$ 最小，答案是什么？

- $\textbf{Hint 2}$

枚举左端点 $l$，答案是否具有单调性？

- $\textbf{Hint 3}$

尝试二分。

- $\textbf{Solution}$

注意到 $a+b \ge a \oplus b$，只考虑值的情况下最优解一定是 $[1,n]$。

同样的，由上面的结论易得，$f(l,r) \le f(l,r+1)$。那么当 $l$ 固定时 $f(l,r)$ 的值是单调不降的，可以二分端点 $r$。

预处理前缀**异或和**和**和**，我们只需要枚举 $l$ 即可。时间复杂度 $\mathcal O(n \log n)$。

**【代码】**

注意输入格式需要读入询问组数 $q$ 和范围限制 $L,R$，但在本题里这些值是固定的（$q=1,L=1,R=n$），代码里用变量 $useless$ 表示。

```cpp
int sum(int n,int i){return c[n] - c[i-1] - (b[n] ^ b[i-1]);}
int fd(int x){
    int l = x,r = n,re = -1;
    while(l <= r){
        int mid = (l + r) / 2;
        if(sum(mid,x) == sum(n,1)) re = mid,r = mid - 1;
        else l = mid + 1;
    }return re;
}
void work(){
    cin >> n >> useless;int ql = 1,qr = n,mr = 1e9;
    for(int i = 1;i <= n;i ++) cin >> a[i],b[i] = b[i-1] ^ a[i],c[i] = c[i-1] + a[i];
    cin >> useless >> useless;
    for(int i = 1;i <= n;i ++){
        if(sum(n,i) != sum(n,1)) break;
        int j = fd(i);if(j - i + 1 < mr) mr = j - i + 1,ql = i,qr = j;
    }cout << ql << " " << qr << "\n";
}
```



---

