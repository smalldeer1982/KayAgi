# Maximum Subsequence

## 题目描述

You are given an array $ a $ consisting of $ n $ integers, and additionally an integer $ m $ . You have to choose some sequence of indices $ b_{1},b_{2},...,b_{k} $ ( $ 1<=b_{1}&lt;b_{2}&lt;...&lt;b_{k}<=n $ ) in such a way that the value of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF888E/3a3d2e76b5bca3303d7d35912be232a5cadb1203.png) is maximized. Chosen sequence can be empty.

Print the maximum possible value of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF888E/3a3d2e76b5bca3303d7d35912be232a5cadb1203.png).

## 说明/提示

In the first example you can choose a sequence $ b={1,2} $ , so the sum ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF888E/08d6750b1b23699a8b513ddd01c316f10e6a789c.png) is equal to $ 7 $ (and that's $ 3 $ after taking it modulo $ 4 $ ).

In the second example you can choose a sequence $ b={3} $ .

## 样例 #1

### 输入

```
4 4
5 2 4 1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3 20
199 41 299
```

### 输出

```
19
```

# 题解

## 作者：newbiechd (赞：19)

[Blog](https://www.cnblogs.com/cj-chd)  
早期作品，不喜轻喷。  
切这道题用了好长时间，所以想发篇题解作为纪念  
首先，我们认真观察题目数据（面向数据做题是个好习惯），发现题目的$n$竟然只有$35$，我们顿时感到打暴力的机会来了：  
##### $2^n$枚举？  
是个好办法。  
只可惜我们发现$2^{35}=34359738368$,并不能过掉所有数据点，于是考虑优化。  
### 分治：
考虑把这$n$个数分成两组（当然要尽量平均），对两组数据分别实施暴力，并把结果存起来（事实上是可以存下来的：$2^{18}=262144$)。
```
void dfs1(int i,int sum){
	if(i==b){p[++k]=sum,p[++k]=(sum+a[b])%m; return ;}
	dfs1(i+1,sum),dfs1(i+1,(sum+a[i])%m);
}
void dfs2(int i,int sum){
	if(i==n){q[++t]=sum,q[++t]=(sum+a[n])%m; return ;}
	dfs2(i+1,sum),dfs2(i+1,(sum+a[i])%m);
}
```
这样一来，我们就得到了原序列分成两半的结果，这两个序列中的数两两组合就可以得到我们要的结果。  
等等，两两组合？这样的复杂度不是和纯暴力一样吗？  
这时候就需要我们贪心地看问题了：  
我们发现：对于序列$p$中的每一个数$p_i$，在序列$q$中若能找到一个与之相加小于$m$的最大的数$q_j$,其他所有的与$p_i$的和小于$m$的数都不会比它更优,即$q_j$比序列$q$中所有比它小的数都更优。  
对于$q$中的每一个数，满足相同条件的$p_i$也具有同样的性质。  
我们想到一种对于$p,q$线性的算法：把$p$和$q$排一遍序，把指向$p$数组的指针$i$和指向$q$数组的指针$j$分别按上面所说的条件向右和向左移动，同时更新$ans$。  
这时我们就只剩下$p_i+q_j>m$的情况了，由于在之前已经取过模，$p_i+q_j$必定小于$2m$，所以我们就只需要用$p,q$的最大值之和去更新一下$ans$就好了。  
代码：
```
int main(){
	R int i,j,ans=0;
	n=read(),m=read(),b=n>>1;
	for(i=1;i<=n;++i) a[i]=read();
	if(n==1) printf("%d",a[1]%m),exit(0);
	dfs1(1,0),dfs2(b+1,0),i=0,j=t;
	sort(p+1,p+k+1),sort(q+1,q+t+1);
	while(i<=k){
		while(p[i]+q[j]>=m) --j;
		ans=max(ans,p[i]+q[j]),++i;
	}
	ans=max(ans,p[k]+q[t]-m);
	printf("%d",ans);
	return 0;
}
```
注意这里特判了一下$n=1$的情况，我被这个点坑了一次。  
整段代码：
```
#include<bits/stdc++.h>
#define R register
#define S 300000
using namespace std;
int a[40],p[S],q[S],k,t,n,m,b;
inline int max(int x,int y){return x>y? x:y;}
inline int read(){
	R int f=0;	R char ch=getchar();
	while(ch<48||ch>57) ch=getchar();
	while(ch>47&&ch<58) f=(f<<3)+(f<<1)+(ch^48),ch=getchar();
	return f;
}
void dfs1(int i,int sum){
	if(i==b){p[++k]=sum,p[++k]=(sum+a[b])%m; return ;}
	dfs1(i+1,sum),dfs1(i+1,(sum+a[i])%m);
}
void dfs2(int i,int sum){
	if(i==n){q[++t]=sum,q[++t]=(sum+a[n])%m; return ;}
	dfs2(i+1,sum),dfs2(i+1,(sum+a[i])%m);
}
int main(){
	R int i,j,ans=0;
	n=read(),m=read(),b=n>>1;
	for(i=1;i<=n;++i) a[i]=read();
	if(n==1) printf("%d",a[1]%m),exit(0);
	dfs1(1,0),dfs2(b+1,0),i=0,j=t;
	sort(p+1,p+k+1),sort(q+1,q+t+1);
	while(i<=k){
		while(p[i]+q[j]>=m) --j;
		ans=max(ans,p[i]+q[j]),++i;
	}
	ans=max(ans,p[k]+q[t]-m);
	printf("%d",ans);
	return 0;
}
```

---

## 作者：Youngore (赞：9)

今天听了钟皓曦大神的讲解，扫了一眼题解区，大家都是在论述折半搜索

但是对于排完序之后的数组，进行互相匹配的时候，几乎说的都不是太透彻（个人观点，随便来喷）

于是我决定写一篇较为详细且严谨的题解

考虑当前有一个p属于对于前一半进行dfs得到的数组里面的一个数字，

考虑当前有一个q属于对于后一半进行dfs得到的数组里面的一个数字，

显然，我们知道：$p<m,q<m$，因此可以推出$p+q<2\times m$

我们也知道我们的答案是$(p+q)\;mod\;m$，因此需要来讨论$p+q$的大小对m造成的影响

第一种情况：

-  $m<p+q<2\times m$
-  此时显然$p+q$往大里取最好，因为取的值越大，在$mod\;m$之后所得到的结果越大

第二种情况：

-  $p+q<m$
-  $O(n^2)$匹配来找答案，显然不优，此时需要搞一个双指针来优化

```cpp
sort(sum1 + 1, sum1 + cnt1 + 1), sort(sum2 + 1, sum2 + cnt2 + 1);
l = cnt1, r = 1;
for (r = 1; r <= cnt2; ++ r)
{
   while (sum1[l] + sum2[r] >= mod) -- l;
   res = max(res, sum1[l] + sum2[r]);
}
```

将两个数组排序，初始化的时候l指向sum1数组的末尾（最大值），r指向sum2数组的开头（最小值）

考虑对于sum2数组中的每一个数字，在sum1中找到某一个数字，使得两者加起来在小于m的情况下最大

具体实现见代码。

此外，给出证明：由于sum1与sum2数组是递增序列，所以一遍扫过来，找到的一定是最优解

如果$sum1[l] + sum2[r]>m$，显然，$sum1[l] +sum2[r+1]$也一定是大于m的，l递减显然没有问题

代码此处省略

(博客有[click](https://www.cnblogs.com/yszhyhm/p/13554873.html))

---

## 作者：fls233666 (赞：4)

认真观察数据范围，可以发现此题的入手点在于 $1 \le n \le 35$

考虑枚举每个数选与不选，总时间复杂度为 $O(2^n)$，显然无法通过此题。

进一步思考可以发发现，如果我们**先搜出一半数字的全部选择方案，再搜出另外一半的数字方案** ，时间复杂度会被降为 $O(2^{\frac{n}{2}})$，可以通过此题。

于是我们可以**折半搜索** 。大概的搜索方法就是，先搜出前一半数字选择可能得到的结果，再搜出另一半数字选择可能得到的结果，与前一半的数字选择方案匹配，即可得到答案。

但是，前一半搜出来的方案可能很多。如果一个一个去比较取最大答案，还是存在超时的风险。

因为题目要求最大值，我们考虑哪些方案可能与当前方案（记为 $s$）匹配形成最大值。

由于存在取模，我们要分为当前方案$+s$大于等于 $m$ 和小于 $m$ 两种情况来讨论。

对于 当前方案$+s<m$ 我们发现，我们可以去找一个最大的之前搜到的方案，满足 $<m-s$ 即可。这个查找过程，可以**排序**后用**二分查找**很快完成。

而对于 当前方案$+s \ge m$ ，显然**取之前的最大的方案**与当前方案求和是最优的。

将上述两种情况得到的最大值与当前答案最大值比较，更新答案即可。

最后要记住，要特判一下 $n=1$ 的情况。不然可能会被这个 hack 点卡掉。

下面是代码：

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#define qmx(a,b) a<b?b:a
#define ll long long
#define rgt register int
using namespace std;

vector <ll> pans;

ll m,a[40],ans;
int n;

void dfs1(int x,ll s){
	if(x==n/2){
		pans.push_back(s);  //存储方案
		return;
	}
	dfs1(x+1,s);  //不选
	dfs1(x+1,(s+a[x])%m);  //选
}

void dfs2(int x,ll s){
	if(x>n){
		int tp=lower_bound(pans.begin(),pans.end(),m-s)-1-pans.begin();  
        //lower_bound找到第一个>=m-s的位置，从这个位置-1就是最大的符合<m-s的方案的位置
		ans=qmx(ans,pans[tp]+s);  //情况一，更新答案
		ans=qmx(ans,(pans[pans.size()-1]+s)%m);  //情况二，排序后的最大值在数组末尾，更新答案
		return;
	}
	dfs2(x+1,s);  //不选
	dfs2(x+1,(s+a[x])%m);  //选
}

int main(){

	scanf("%d%lld",&n,&m);
	for(rgt i=1;i<=n;i++)
		scanf("%lld",&a[i]);
        
	if(n==1){  //特判
		printf("%lld",a[1]%m);
		return 0; 
	} 
    
	dfs1(1,0);  //搜索前一半
	sort(pans.begin(),pans.end());  //排序
	dfs2(n/2,0);  //搜索后一半
	printf("%lld",ans);  //得到答案
	return 0;
}
```


---

## 作者：狸狸养的敏敏 (赞：3)

首先讲一讲我对 $Meet\ in\ Middle$ 的理解

对于一个复杂度是 $O(2^n)$ 的搜索算法，我们把他拆成 $O((2^{\frac{n}{2}})^2)$ 的做法，再想办法用一些诸如贪心之类的线性算法，将 $O((2^{\frac{n}{2}})^2)$ 的复杂度降低为 $O(2\times2^{\frac{n}{2}})$  的操作

类似的，对于这道结果可以通过合并来获得答案的题目，我们把搜索的规模减半，即每次搜索一半的组合的结果，这里的复杂度是$O(2\times 2^\frac{n}{2})$

我们思考一下合并的过程，这里需要用到一个小技巧，我们对组合获得的答案对 $m$ 取模后，任何两个数加起来不可能超过 $2m$,**因此，对于相加在 $[m,2m)$ 之间的数，我们直接两部分结果中取最大的两个加起来取模即可，剩下的部分全部可以舍弃。**

**类似的，剩下部分应该全部都是加起来结果在 $[0,m)$ 之间的数**

通过上面的思考过程，引导我们把结果进行排序，并且在两个数组之间设置两个指针，一个指向前 $\frac{n}{2}$ 个数所构成的结果最小的数，另一个指向后 $\frac{n}{2}$ 个数所构成的结果最大的数，通过每次移动右指针和左指针来控制结果，因为剩下部分全都是结果加起来在 $[0,m)$ 之间的数，我们可以利用贪心的思想进行选取，设前部分的结果数组为 $f[]$ ，后部分的结果数组为 $g[]$ ，当 $f(l)+g(r)\ge M$ 时，直接移动右指针，**因为我们只需要和 $f[l]$ 加起来最大的那个数**

这部分的时间复杂度最大为 $O(Size\ of\ Dfs)$，约为 $2^{\frac{n}{2}}$ 的级别

```cpp
#include<bits/stdc++.h>
#define reg register
#define i64 long long
using namespace std;
int read(){int x=0,f=0;char ch=0;while(!isdigit(ch))f|=(ch=='-'),ch=getchar();while(isdigit(ch))(x*=10)+=(ch^48),ch=getchar();return f?-x:x;}
void Ot(int x){if(x<0)putchar('-'),x=-x;if(x>=10)Ot(x/10);putchar(x%10+48);}
void Print(int x,char til='\n'){Ot(x);putchar(til);}
int Max(int x,int y){return x>y?x:y;}
int Min(int x,int y){return x<y?x:y;}
int Abs(int x){return x<0?-x:x;}
const int MAXN=44;
int n,M,a[MAXN],ans;
vector<int>G[2];
int Gmod(int x){return x>=M?x-M:x;}
void dfs(int k,int x,int sum,int n){
	sum=Gmod(sum);
	if(x>n)return G[k].push_back(sum),void();
	dfs(k,x+1,sum,n);
	dfs(k,x+1,sum+a[x],n);
}
signed main(){
	#ifndef ONLINE_JUDGE
		freopen("C:/Users/Administrator/Desktop/data.txt","r",stdin);
		freopen("C:/Users/Administrator/Desktop/out.txt","w",stdout);
	#endif
	n=read();M=read();
	for(reg int i=1;i<=n;i++)a[i]=read()%M;
	dfs(0,1,0,n>>1);
	dfs(1,(n>>1)+1,0,n);
	sort(G[0].begin(),G[0].end());
	sort(G[1].begin(),G[1].end()); 
	int l=0,r=G[1].size()-1;
	ans=Max(ans,Gmod(G[0][l]+G[1][r]));
	while(l<G[0].size()&&r>=0){
		while(G[0][l]+G[1][r]>=M)r--;
		ans=Max(ans,Gmod(G[0][l]+G[1][r]));
		l++;
	}
	Print(ans);
	#ifndef ONLINE_JUDGE
		fclose(stdin);fclose(stdout);
		system("C:/Users/Administrator/Desktop/out.txt");
	#endif
	return 0;
}

```

---

## 作者：jins3599 (赞：3)

折半搜索$+\text{two-pointers}$

我们考虑$n=35$，朴素的搜索无法胜任，但这带给了折半搜索无限生机。

于是我们按照折半搜索的套路，把原序列分两个部分分别进行dfs.

然后我们就会得到两个序列，长度约为$2^{13}$，我们的问题就转化为了在两个序列中，选取两个数使其加和在模$m$意义下最大。

$n^2$枚举？那么我们之前的折半搜索全白费劲了。

一个很显然的特点，如果我们选取的两个最大的数加在一起大于$m$，那么一定选其中最大的两个是最优的。

为什么？因为我们在处理的时候已经进行了模$m$意义下的处理，也就是说，对于一个在序列$a$中的$q$和在序列$b$中的$p$，一定满足$p< m,q< m$，于是$p+q<2m$，因此选取两个最大的是更优的。

那么对于$p+q<m$的情况呢？我们维护两个指针分别指向$a$数组的头和$b$数组的尾，然后对于每一组$(p,q)$,他们对应的$a$变大的过程中，$b$一定不会变大，也就是说，**$b$关于$a$是单调减的**，显然我们可以用双指针线性的维护这个答案。

于是总复杂度$O(2^{\frac{n}{2}}+n)$，跑的很快。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 40;
const int M = 1e6;
int n , mod , mid;
int a[N];
int sum1[M] , cnt1 , sum2[M] , cnt2 , ans = 0;
bool vis[N];

void dfs1(int now, int sum) {
	if(now > mid) {
		sum1[++ cnt1] = sum; return;
	}
	dfs1(now + 1 , sum);
	dfs1(now + 1 , (sum + a[now]) % mod);
}

void dfs2(int now , int sum) {
	if(now > n) {
		sum2[++ cnt2] = sum; return;
	}
	dfs2(now + 1 , sum);
	dfs2(now + 1 , (sum + a[now]) % mod);
}

int main () {
	scanf("%d %d" , &n , &mod);
	for(int i = 1 ; i <= n ; i ++) scanf("%d" , a + i) , a[i] %= mod;
	mid = (n >> 1);
	dfs1(1 , 0);
	dfs2(mid + 1 , 0);
	sort(sum1 + 1, sum1 + cnt1 + 1);
	sort(sum2 + 1 , sum2 + cnt2 + 1);
	ans = max(sum1[cnt1] , sum2[cnt2]);
 
	int l = cnt1 , r = 1;
	for(r = 1 ; r <= cnt2 ; r ++) {
		while(sum1[l] + sum2[r] >= mod) l --;
		ans = max(ans , sum1[l] + sum2[r]);
	}
	ans = max(ans , (sum1[cnt1] + sum2[cnt2]) % mod);
	printf("%d\n" , ans);
	return 0;
}
```

---

## 作者：封禁用户 (赞：3)

这是我 ~~（本小学生）~~ 的第一篇题解(其实就是小学生)

不喜勿喷

e 本题思路为 ~~(裸)~~ 暴力。

>$1<=n<=35$

**是的 那么 打爆力的机会来了**

(裸)暴力代码如下

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[40],n,mod,ans;
int main(){
    scanf("%lld%lld",&n,&mod);
    for(int i=0;i<n;i++){
        scanf("%lld",a+i);
    }
    for(long long st=0;st<(1ll<<n);st++){
        long long te=0;
        for(int i=0;i<n;i++)
            if(st&(1ll<<i))
                te=(te+a[i])%mod;
        ans=max(te,ans);
    }
    printf("%lld",ans);
}
```
时间复杂度 $O(2^n)$

$2^{35}=34359738368$。

AC 率 % 16...

### 考虑优化

咳咳，某大佬也说了 **面向数据是个好习惯**

$n<=35$　$\frac{n}{2}<=18$

$2^{18}=262144$ 这个数是可以接受的



```cpp
for(long long st=0;st<(1ll<<(n/2));st++){
    long long te=0;
    for(int i=0;i<n;i++)
        if(st&(1ll<<i))
            te=(te+a[i])%mod;
    A[st]=te;
}
for(long long st=0;st<(1ll<<(n/2+(n&1)));st++){
    long long te=0;
    for(int i=0;i<n;i++)
        if((st<<(n/2))&(1ll<<i))
            te=(te+a[i])%mod;
    B[st]=te;
}
```
那么 为什么要把这些存起来呢

因为 通过这些**两两组合**可以拼出所有的选则

**问题转化为 从两个集合内各选一个元素 使得它们的和 mod m 后最大！**

$O(n^2)$枚举肯定不行（废话），这时候就需要我们贪心地看问题了

我们发现 对于 $A$ 中的每个 $A_i$ 的最优解 $B_j$ 一定是 $B$ 序列中与 $A_i$ 的和小于 $M$ 中最大的一个。

P.S. 

- 问：为什么最优解不会是与 $A_i$ 的和大于等于 $m$ 且最大的那个。

- 答：$B$ 序列中必有一个 $0$ (什么都不选) 且 $B$ 中的任意元素小于 $m$ , $a+0%m$ 的值为 $a$ 但 $a+(m-1)%m$ 的值为 $a-1$($a<0$) 所以最优解不会是与 $A_i$ 的和大于等于 $m$ 且最大的那个。

**完整思路：将 $A$ 和 $B$ 排序，从小到大枚举 $i$ 按 $A_i$ 向左移动 $j$，同时更新 $ans$。时间复杂度 $O(2^{\frac{n}{2}})$**

AC 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[40],n,mod,ans;
long long A[1<<18],B[1<<18];
int main(){
    scanf("%lld%lld",&n,&mod);
    for(int i=0;i<n;i++){
        scanf("%lld",a+i);
    }
    for(long long st=0;st<(1ll<<(n/2));st++){
        long long te=0;
        for(int i=0;i<n;i++)
            if(st&(1ll<<i))
                te=(te+a[i])%mod;
        A[st]=te;
    }
    for(long long st=0;st<(1ll<<(n/2+(n&1)));st++){
        long long te=0;
        for(int i=0;i<n;i++)
            if((st<<(n/2))&(1ll<<i))
                te=(te+a[i])%mod;
        B[st]=te;
    }
    sort(A,A+(1ll<<(n/2)));
    sort(B,B+(1ll<<(n/2+(n&1))));
    long long j=(1ll<<(n/2+(n&1)))-1;
    for(int i=0;i<(1ll<<(n/2));i++){
    	while(A[i]+B[j]>=mod)j--;
    	ans=max(ans,A[i]+B[j]);
	}ans=max(ans,A[(n/2)-1]+B[(n/2+(n&1))-1]-mod);
    printf("%lld",ans);
}
```

# the end

---

## 作者：ttq012 (赞：1)

**题目简述：给你最多 $35$ 个整数，选出一个子集，让这个子集的和对 $m$ 取模的结果最大，求最大的余数。其中子集代表某一个组合。**

**这道题是一个折半枚举的模板题。**

暴力枚举所有的组合，时间复杂度是 $2^{35}$，不可以接受。

但是我们可以将所有的数字拆成两半，左半边是 $a_1, a_2, a_3, \cdots, a_\frac{n}{2}$，右半边是 $a_{\frac{n}{2}+1}, a_{\frac{n}{2}+2}, a_{\frac{n}{2}+3}, \cdots, a_n$。

分成两半之后，暴力枚举左半边数的所有组合，保存到 $b$ 数组中，并进行排序，复杂度最多为 $2^{18}$。

暴力枚举右半边的所有组合。在 $b$ 数组中找一个数，让这一个数跟某一个组合里面的数 $X$ 之和，并对 $m$ 取模，得数最大。

去 $b$ 数组里查找一个小于等于 $m - 1 - x$ 的最大的数，如果不存在，就直接取 $b$ 数组里面的最大的数。

注意，选的数可能都在左半边或者都在右半边，这种情况是需要特判的。

比如说，$n = 6$，$m = 8$，$a$ 数组是 $1, 3, 5, 6, 9, 11$。应该选的数是：$(6 + 9) \% 8 = 7$。

```cpp
#include <bits/stdc++.h>
using namespace std;

vector <int> a, b;
int tot;

// 对于vector的优化
int t;
inline int getint()
{
    scanf ("%d", &t);
    return t;
}

// 二分查找
int find(int x)
{
    int best = -1;
    int l = 0, r = tot - 1;
    if (b[r] <= x)
        return b[r];
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (b[mid] <= x)
            best = b[mid], l = mid + 1;
        else
            r = mid - 1;
    }
    return best;
}

int main()
{
    int n, mod, m;
    cin >> n >> mod;
    m = n >> 1;
    a.clear();
    b.clear();
    for (int i = 0; i < n; i ++)
        a.push_back(getint() % mod);
    for (int i = 0; i < (1 << m); i ++)
    {
        int tmp = 0;
        for (int j = 0; j < m; j ++)
            if (i & (1 << j))
                tmp = (tmp + a[j]) % mod;
        b.push_back(tmp);
    }
    tot = b.size();
    sort (b.begin(), b.end());
    m = (n - (n >> 1)); // 右半段的起始点
    int mx = 0;
    for (int i = 0; i < (1 << m); i ++)
    {
        int tmp = 0;
        for (int j = 0; j < m; j ++)
            if (i & (1 << j))
                tmp = (tmp + a[j + (n >> 1)]) % mod;
        int x = find(mod - tmp - 1); // 二分查找答案
        mx = max(mx, (x + tmp) % mod);
        if (mx == mod - 1)
            break; // 前文没有提到的优化，如果答案已经是最大值，那么后面的值一定不可能大于当前的值，所以直接跳出枚举
    }
    cout << mx << endl;
    return 0;
}

```



---

## 作者：Bosun (赞：1)

这道题看到35的数据量，条件反射出meet in the middle(折半枚举)

所谓meet in the middle，就是将原集合分为两个大小最多相差1的子集，

在其中一个子集中2^17暴力枚举，然后对于所有枚举的数，在另一个子集

中查找。

具体来说，以5个数为例（mod 3）

1 2 3 4 5

前两个的状态：0，1，2，1+2=3 3mod3=0

后3个就可以暴力枚举了:

对于3来说，最好情况显然是凑起来是2，于是在子集1中找到第3个元素2

对于4来说，最好情况显然是凑起来也是2，于是在子集1中找到第3个元素1

对于5来说，最好情况显然是凑起来也是2，于是在子集1中找到第3个元素0

既然可以凑出mod-1,那答案一定是mod-1(当然还有凑不成的，只能用

lower_bound找最接近的代替了)

完毕
code：
```c
#include<bits/stdc++.h>
using namespace std;
int n,mod,a[1000001];
long long sum[1000001];
int main(){
	cin>>n>>mod;
	int i,j;
	for(i=1;i<=n;i++)scanf("%d",&a[i]);
	int m=n/2,k=n-m;
	for(i=0;i<(1<<m);i++){
		for(j=1;j<=m;j++)sum[i]+=((i>>(j-1))&1)*a[m-j+1];
        //枚举状态
		sum[i]%=mod;
	}
	sort(sum,sum+(1<<m));//排序好二分
	long long ans=0;
	for(i=0;i<(1<<k);i++){
		long long s=0;
		for(j=1;j<=k;j++)s+=((i>>(j-1))&1)*a[n-j+1]; 
		s%=mod;
		long long x=(lower_bound(sum,sum+(1<<m),(mod-1-s))-sum); 
		long long mx=0;
        //本人第一次RE了，这是处理边界问题，不要在意细节。。。。。
		if(x>0&&x<m-1)mx=max((sum[x]+s)%mod,max((sum[x-1]+s)%mod,(sum[x+1]+s)%mod));
		if(x<=0)mx=max((sum[x]+s)%mod,(sum[x+1]+s)%mod);
		if(x>=m-1)mx=max((sum[x]+s)%mod,(sum[x-1]+s)%mod);
		ans=max(ans,mx);
	}
	cout<<ans<<endl;
	return 0;
} 
```


---

## 作者：两年打铁 (赞：1)

# 分析
n=35?想暴搜但是碍于这个35有点难。

我们知道和是可以合并的，那么考虑折半搜索，这样搜索状态的复杂度就降为

$O(2^{(n+1)/2+1})$ 非常优美的复杂度，足以让我们进行下一步。

那么现在问题就变成了这样：

## 给定两个序列，分别从两个序列中选出两个数，使得这两个数的和相加$mod \ \ m$的值最大。

这就是个非常裸的贪心啊...

对于第一个序列的任意一个数$t$ ,我们知道最优的方案肯定是$m-t-1$ 但第二个序列序列中不一定有这个数，所以我们要用最大的小于等于$m-t-1$的数和第二个序列的最大值去更新答案。

查找可以使用upper_bound,窝lower_bound过不了（可能是太菜了）

### 注意所有序列中的数不能大于等于m

奉上代码

```cpp
#include<bits/stdc++.h>
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)
#define int long long 
const int big=0x7fffffff;
using namespace std;
inline void read(int &x)
{
    x=0;char ch=getchar();int pd=1;
    while(ch<'0'||ch>'9'){if(ch=='-')pd=-pd;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    x*=pd;
}
inline void write(const int &x)
{
    char ggg[10001];int s=0;int tmp=x;
    if(tmp==0){putchar('0');return;}
    if(tmp<0){tmp=-tmp;putchar('-');}
    while(tmp>0){ggg[s++]=tmp%10+'0';tmp/=10;}
    while(s>0){putchar(ggg[--s]);}
}

int mid,n,cnt,cc,s[1000010],ss[1000010];
int a[1000010];
int mod;

void dfs(int x,int sum)
{
	if(x==mid+1)
	{
		s[++cnt]=sum;
		return ;
	}
	dfs(x+1,(sum+a[x])%mod);
	dfs(x+1,sum);
}

void dfs2(int x,int sum)
{
	if(x==n+1)
	{
		ss[++cc]=sum;
		return ;
	}
	dfs2(x+1,(sum+a[x])%mod);
	dfs2(x+1,sum);
}


signed main()
{
	read(n);
	read(mod);
	for(register int i=1;i<=n;++i)
	{
		read(a[i]);
		a[i]%=mod;
	}
	mid=(n+1)/2;
	dfs(1,0);
	dfs2(mid+1,0);
	sort(ss+1,ss+cc+1);
	int len=unique(ss+1,ss+cc+1)-ss-1;
	int ans=0;
	for(register int i=1;i<=cnt;++i)
	{
		int j=upper_bound(ss+1,ss+len+1,mod-s[i]-1)-ss-1;
		while(ss[j]>mod-s[i]-1)--j;
		ans=max(ans,(s[i]+ss[len])%mod);
		ans=max(ans,(s[i]+ss[j])%mod);
	}
	write(ans);
	return 0;
}// ck ak ioi
```


---

## 作者：LJB00131 (赞：1)

**题意：给一个数列和m，在数列任选若干个数，使得他们的和对m取模后最大**

$$(1\le n \le 35, 1\le m \le 10^{9} )$$

注意到有
$$n \le 35$$

所以考虑搜索，但因为
$$ 2^{35} = 34359738368 $$
所以并跑不过。

这是我们想到 
$$ 2^{\lceil 35 / 2 \rceil} < 1e8$$ 
可以通过



------------


关于折半搜索：
[luogu P4799](https://www.luogu.org/problem/P4799)

这是一道更简单的题


------------

**折半搜索的难点不在于搜索而在于合并**

这里的题解都选择了用  $ O(n) $  的双指针

但是我更喜欢暴力，所以我选择用二分搜索。

**因为搜索出来的答案可以排序使之单调，所以可以二分**

用一下STL的lower_bound就可以啦

附代码

```cpp
#include<bits/stdc++.h>

using namespace std;

#define N 45
typedef long long ll;

int n, mid;

ll num[N], m;

ll a[1050005], b[1050005], cnt1 = 0, cnt2 = 0;

void dfs1(int x, ll sum)
{
	if(sum > m) return;
	if(x > mid)
	{
		a[++cnt1] = sum;
		return;
	}
	dfs1(x + 1, sum + num[x]);
	dfs1(x + 1, sum);
}

void dfs2(int x, ll sum)
{
	if(sum > m) return;
	if(x > n)
	{
		b[++cnt2] = sum;
		return;
	}
	dfs2(x + 1, sum + num[x]);
	dfs2(x + 1, sum);
}

int main()
{
	scanf("%d%lld", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		scanf("%lld", &num[i]);
	}
	mid = n + 1 >> 1;
	dfs1(1, 0);
	dfs2(mid + 1, 0);
	sort(b + 1, b + cnt2 + 1);
	ll ans = 0;
	for(int i = 1; i <= cnt1; i++)
		ans += upper_bound(b + 1, b + cnt2 + 1, m - a[i]) - b - 1;
	cout << ans << endl;
	return 0;
}
```

---

## 作者：VenusM1nT (赞：1)

$\texttt{Meet in the middle}$。

观察数据范围，$m\leq 35$，一个明显的 “ $\texttt{Meet in the middle}$ 复杂度 ”（也就是直接爆搜要炸，但是一半就不会炸）。

这题也算是比较经典的 $\texttt{Meet in the middle}$ 做法了吧，直接爆搜会超时，考虑先搜前 $\frac{n}{2}$ 个，然后搜后 $\frac{n}{2}$ 个，将得到的所有方案数分别排序，得到两个数组。

两个数组的规模都在 $1e5$ 到 $3e5$之间，直接暴力查找显然会超时，考虑使用一个技巧，也就是 “ $\texttt{two-pointers}$ ” 这一神仙算法，将 $\Theta(n^2)$ 变为 $\Theta(n)$ 就可以过了。

至于 $\texttt{two-pointers}$ 怎么写呢？它的实现就如同它的名字一样，弄两个指针，因为我们的两个数组都是排过序的，所以一个指向第一个数组的头，另一个指向第二个数组的尾，逐位移动即可。

由于我们并不是每一位都要记录答案，而是根据一些条件来移动指针，所以复杂度非常优秀。

```cpp
#include<bits/stdc++.h>
#define MAXN 500005
#define MAXM 55
#define reg register
#define inl inline
using namespace std;
int n,Mod,val[MAXM],a[MAXN],b[MAXN],tot1,tot2,lim,ans;
void Dfs1(reg int s,reg int sum)
{
	if(s>lim)
	{
		a[++tot1]=sum;
		return;
	}
	Dfs1(s+1,sum);
	Dfs1(s+1,(sum+val[s])%Mod);
}
void Dfs2(reg int s,reg int sum)
{
	if(s>n)
	{
		b[++tot2]=sum;
		return;
	}
	Dfs2(s+1,sum);
	Dfs2(s+1,(sum+val[s])%Mod);
}
int main()
{
	scanf("%d %d",&n,&Mod);
	for(reg int i=1;i<=n;i++) scanf("%d",&val[i]);
	if(n==1) return printf("%d\n",val[1]%Mod),0;
	lim=n/2;
	Dfs1(1,0);
	Dfs2(lim+1,0);
	sort(a+1,a+tot1+1);
	sort(b+1,b+tot2+1);
	reg int i=0,j=tot2;
	while(i<=tot1)
	{
		while(a[i]+b[j]>=Mod) j--;
		ans=max(ans,a[i]+b[j]);
		i++;
	}
	ans=max(ans,a[tot1]+b[tot2]-Mod);
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：songhn (赞：1)

## Meet-in-the-middle+贪心
首先我们看到数据范围$n<=35$加上每个数都可能取或不取，这样$2^{35}$的状态量自然是太大了，但对于这种取或不取实现一系列要求有个很常见的作法就是Meet-in-the-middle，也可以当成折半搜索，对于前一半选一些数，再对后一半选一些数，这样就只有$2^{\frac{35}{2}}$瞬间缩小了很多。

但一般这种搜索的瓶颈在于对两半数据合并统计状态，操作不当会导致增加$n^2$复杂度直接回归暴力做法，一般这也有些常用的套路，比如这题和**poj1186方程的解数**一样都是把两边的状态分别存在两个数组里，由于之前枚举时已经全膜过了，所以两个数组里的数都是$<=m$的，这个性质很重要，我们可以靠它来贪心。

首先这两个数组抽任意两个数加起来都是$<=2m$，那么我们将两个数组不下降排序，对于抽出来$>=m的情况，显然两数组中最大的数加起来是最大的，膜m后对于$>=m$情况只有它可能是最优解。

之后我们直接考虑加起来$<=m$,我们可以建立两个指针$i j$一个指向h1数组开头一个指向h2末尾，若当前加起来$>=m$我们便直接让$j$--，显然，因为h1是递增的，所以随着i的增大j只能减少才可能满足$<=m$，这样并不会漏掉答案，这样扫过一边之后在与h1[p]+h2[q]（两数组中最大的数加起来是最大的）取max，这样便是结果。

注意在搜索的时候可以向楼下的题解一样直接dfs，当然也可以和这个代码一样用二进制来枚举子集，比dfs速度要快一些。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=500000;
int n,m,a1[50],a2[50],p,q;
int h1[maxn],h2[maxn],num1=0,num2=0;
void calc()
{
    for(int i=0;i<(1<<p);i++)
    {
        int t=0;
        for(int j=1;j<=p;j++)
        if(i>>(j-1)&1) t=(t+a1[j])%m;
        h1[++num1]=t;
    }
    for(int i=0;i<(1<<q);i++)
    {
        int t=0;
        for(int j=1;j<=q;j++)
        if(i>>(j-1)&1) t=(t+a2[j])%m;
        h2[++num2]=t;
    }
    sort(h1+1,h1+1+num1);
    sort(h2+1,h2+1+num2);
    int i=1,j=num2;
    int ans=0;
    for(int i=1;i<=num1;i++)
    {
        while(h1[i]+h2[j]>=m&&j>0) j--;
        if(j<=0) break;
        ans=max(h1[i]+h2[j],ans);
    }
    ans=max(ans,h1[p]+h2[q]);
    printf("%d\n",ans);
}
int main()
{
    scanf("%d%d",&n,&m);
    p=n/2,q=n-p;
    for(int i=1;i<=p;i++) scanf("%d",&a1[i]);
    for(int i=1;i<=q;i++) scanf("%d",&a2[i]);
    calc();
    return 0;
}
```

---

## 作者：activeO (赞：0)

## 题目大意

给一个数列和 m，在数列任选若干个数，使得他们的和对 m 取模后最大。

## 思路

$ 1 \leq n \leq 35 $，暴力 $ O(2^n) $ 肯定是 AC 不了的。

考虑折半搜索：

对两组数据实施暴力，可以得到两组结果 f 和 b。

可以发现如果 $ b_i $ 可以找到一个 $ f_j $ 满足 $ b_i + f_j \leq m $，那么对于 $ b_k \leq b_i $ 都可以有都不会比它更优。

对于 f 数组也同理。

于是我们将 f 和 b 排序，这样就可以用指向 f 的指针 i 和指向 b 的指针 j 按上面那样线性地更新 ans。

然后考虑 $ f_i + b_j \geq m $ 的情况，由于之前取过模，所以 $ f_i+b_j < 2m $，所以就只用 f,b 的最大值之和更新 ans 就可以了。

## 代码

**注:变量名与上文稍有不同**

```cpp
#include <bits/stdc++.h>//祝大家学习愉快！

using namespace std;

const int maxn=3e5+10;
int a[40],fr[maxn],bk[maxn];
int cnt=0,tot=0,n,mod,mid;

void dfs1(int i,int val){
	if(i==mid){
		fr[++cnt]=val;
		fr[++cnt]=(val+a[mid])%mod;
		return;
	}
	dfs1(i+1,val);
	dfs1(i+1,(val+a[i])%mod);
}
void dfs2(int i,int val){
	if(i==n){
		bk[++tot]=val;
		bk[++tot]=(val+a[n])%mod;
		return;
	}
	dfs2(i+1,val);
	dfs2(i+1,(val+a[i])%mod);
}

int main(){
	
	int ans=0;
	
	scanf("%d %d",&n,&mod);
	
	mid=n>>1;
	
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	
	if(n==1){//特判 n=1 的情况
		printf("%d\n",a[1]%mod);
		return 0;
	}
	
	dfs1(1,0);
	dfs2(mid+1,0);//折半搜索
	
	sort(fr+1,fr+cnt+1);
	sort(bk+1,bk+tot+1);
	
	int i=0,j=tot;
	
	while(i<=cnt){
		while(fr[i]+bk[j]>=mod) j--;
		ans=max(ans,fr[i]+bk[j]);
		i++;
	}
	
	ans=max(ans,fr[i]+bk[j]-mod);
	
	printf("%d\n",ans);
	
	return 0;
}


```


---

## 作者：一只书虫仔 (赞：0)

#### Description

> 给定一个数集 $A$ 与 $m$，求 $A$ 的一个子集 $S$ 使得 $\displaystyle \sum\limits_{p \in S} p$ 最大，输出这个最大值。

#### Solution

每个数设状态为选择或者不选择，考虑暴力折半搜索。

将数集劈成左右两半，如果选择，那么就加上 $A_i$，否则就不加 $A_i$。

经过折半选择会产生出左右分别加和得到的两个序列 $a$ 和 $b$，对 $b_i$ 二分查找最后一个 $a_j+b_i <m$，这样能保证膜完之后是最大的。具体实现方法可以 `lower_bound` 后减掉 $1$ 即可，如果减完之后这个数不存在直接扔到序列尾部就行了。

最后输出所有的 $a_j+b_i \bmod m$ 的最大值即可。

#### Code

```cpp
dfs1(1, 0);
sort(val1 + 1, val1 + cnt1 + 1);
dfs2(mid + 1, 0);
int Max = -1;
for (int i = 1; i <= cnt2; i++) {
	int qwq = lower_bound(val1 + 1, val1 + cnt1 + 1, m - val2[i]) - val1;
	qwq--;
	if (qwq > 0) Max = max(Max, (val1[qwq] + val2[i]) % m);
	else Max = max(Max, (val1[cnt1] + val2[i]) % m);
}
printf("%d", Max);
```

---

## 作者：耶耶小朋友 (赞：0)

## 题解 T3970([CodeForces - 888E]Maximum Subsequence)

### 方法：折半法

这道题的数据为 $1 ≤ n ≤ 35$，那么暴力的话，复杂度最大为 $O(2^{32})$，很明显会超时。

那么我们的折半法就浓重登场啦！

思路：把其分两半，先枚举前一半，再枚举后一半，这样复杂度就可以满足了，顶多 $O(2^{18})$。

先读入数据到 $a$ 数组并取模好。

用二进制表示选与不选，$0$ 表示不选，$1$ 表示选，枚举前一半的各种组合求和并取模后的结果，存到 $b$ 数组。

之后暴力枚举另一半，同理求得各种组合求和并取模后的结果，在 $b$ 数组里找到一个数使这个数加结果取模后的值最大，即在 $b$ 数组内找到小于等于 $mod - 1 - x$ （$x$ 为当前结果）的最大值。

用二分解决。

## Code:

``` cpp
#include<bits/stdc++.h>
using namespace std;
//考虑unsigned long long
typedef long long ll;

const int N = 40;
int a[N]; 
const int M = 1000010;
int b[M];
int cnt = 0;

int findd(int x) {
	//best表示二分的结果 
	int l = 1,r = cnt,best = 0;
	while(l <= r) {
		int mid = (l + r) >> 1;
		if (b[mid] <= x) {
			l = mid + 1;
			best = mid;
		} else {
			r = mid - 1;
		}
	}
	return b[best];
}

int main () {
	std::ios::sync_with_stdio(false);
	int n,mod;
	cin >> n >> mod;
	for (int i = 0;i < n;i++) {
		cin >> a[i];
		a[i] %= mod;
	}
	//获取前一半的长度 
	int m = n / 2;
	//用二进制数表示数的状态 
	for (int i = 0;i < (1 << m);i++) {
		int tmp = 0;
		for (int j = 0;j < m;j++) {
			//选 
			if (i & (1 << j)) {
				//更新答案 
				tmp = (tmp + a[j]) % mod;
			}
		}
		cnt++;
		//存入b数组 
		b[cnt] = tmp;
	}
	//排序便于二分 
	sort(b + 1,b+cnt+1);
	//另一半的长度 
	m = n - n / 2;
	int ans = 0;
	//同理 
	for (int i = 0;i < (1 << m);i++) {
		int tmp = 0;
		for (int j = 0;j < m;j++) {
			if (i & (1 << j)) {
				//注意这里是另一半，需加上之前的长度 
				int k = j + n / 2;
				tmp = (tmp + a[k]) % mod;
			}
		}
		//找到最大值 
		int x = findd(mod - tmp - 1);
		//更新答案 
		ans = max(ans,(x + tmp) % mod);
	}
	cout << ans << endl;
	return 0;
}


```

$The\ end.$



---

## 作者：Plozia (赞：0)

宣传博客->[link](https://blog.csdn.net/BWzhuzehao/article/details/111144143)

首先看完本题，最直接的想法就是——爆搜！

但是， $2^{35}$ 让我们望而却步，因此我们需要考虑一定的优化。

而本题的优化是十分经典的 **折半搜索 （Meet in middle）** 算法。

折半搜索的主要思路就是：将序列裂成两半搜索，然后合并答案。

对于这道题，我们首先对 $[1,\dfrac{n}{2}]$ 做一次暴力搜索， $[\dfrac{n}{2}+1,n]$ 做一次暴力搜索，统计的和存在 $ans1,ans2$ 里面，其中不要忘记取模。

但是这样还是没有用啊？此时就要请出另一利器：**尺取法**。

首先对 $ans1,ans2$ 排个序，然后指定 $pos1=1,pos2=size(ans2)$ 。

由于此时 $ans1,ans2$ 中每个数都在 $[0,m)$ 范围内。因此我们只需要考虑 $ans1_{pos1}+ans2_{pos2} < m$ 的结果即可。为什么不需要考虑大于 $m$ 的？因为最大值 $ans1_{size(ans1)}+ans2_{size(ans2)} < 2n$ ，此时对于大于 $m$ 的和而言，$ans1_{size(ans1)}+ans2_{size(ans2)}$ 一定是最优解，因此不需要考虑。

想清楚后代码就很简单了。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 40 + 10;
int n, m, a[MAXN], ans1[1 << 20], ans2[1 << 20], mid, cnt1, cnt2, ans;

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	while (ch < '0' || ch > '9') {if (ch == '-') fh = -1; ch = getchar();}
	while (ch >= '0' && ch <= '9') {sum = (sum << 3) + (sum << 1) + (ch ^ 48); ch = getchar();}
	return sum * fh;
}

void dfs1(int k, int sum)
{
	if(k == mid + 1) {ans1[++cnt1] = sum; return ;}
	dfs1(k + 1, sum); dfs1(k + 1, (sum + a[k]) % m);
}

void dfs2(int k, int sum)
{
	if(k == n + 1) {ans2[++cnt2] = sum; return ;}
	dfs2(k + 1, sum); dfs2(k + 1, (sum + a[k]) % m);
}

int main()
{
	n = read(); m = read();mid = n >> 1;
	for(int i = 1; i <= n; ++i) a[i] = read();
	dfs1(1, 0); dfs2(mid + 1, 0);
	sort(ans1 + 1, ans1 + cnt1 + 1); sort(ans2 + 1, ans2 + cnt2 + 1);
	int pos1 = 1, pos2 = cnt2;
	while(pos1 <= cnt1 && pos2 >= 1)
	{
		while(ans1[pos1] + ans2[pos2] >= m) pos2--;
		ans = max(ans, ans1[pos1] + ans2[pos2]); pos1++;
	}
	printf("%d\n", max(ans, (ans1[cnt1] + ans2[cnt2]) % m));
	return 0;
}
```

---

## 作者：Remake_ (赞：0)

蒟蒻今天刚看了看$\texttt{Meet-in-the-Middle}$的讲解，然后抱着试一试的心态写了写这道题，竟然过了/fad，来写篇题解。

~~这题绝对是水紫~~

首先我们来考虑将序列$a_i$分成两组，运用分治的思想，我们知道有三种情况：

$1,$所选的$k$个数全在前一组中。

$2,$所选的$k$个数全在后一组中。

$3,$所选的$k$个数有的在前一组中有的在后一组中。

对于前两种情况，我们分别对被分成两组的序列分别进行$\texttt{dfs}$即可，为了时间复杂度的优，我们让两组序列的长度尽可能相近，即都设为$\frac{n}{2}$。

对于后一种情况，怎么搞呢？

我们知道我们可以在$\texttt{dfs}$时将两个序列所能凑出来的数分别找出来。

然后我们分别枚举第一个序列能够凑出来的数，我们想要从另一个序列中所能凑出来的数找出来一个与其配对。

那么显然对于每个数，又分两种情况了：

$1,$从另一个序列中找出来的数与当前的数之和$<m$，显然我们可以使用二分查找查找到满足条件的最大的数与其匹配。

$2,$从另一个序列中找出来的数与当前的数之和$\geq m$，我们知道这个和同时还是$<2m$的，所以这种情况下匹配的对象只可能是另一个序列中的最大值。

时间复杂度：$O(2^{\frac{n}{2}}\log{2^{\frac{n}{2}}})$

于是这道题就做完了，放代码吧qaq：

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n, m, a[50], maxx;
vector<long long> v1, v2, v3, v4;
map<long long, bool> mp;
void dfs(long long sum, long long deep, int type)
{
    if (deep == (type ? v1.size() : v2.size()))
    {
        if (!mp[sum])
        {
            mp[sum] = 1;
            type ? v3.push_back(sum) : v4.push_back(sum);
        }
        return;
    }
    dfs(sum, deep + 1, type);
    dfs((sum + (type ? v1[deep] : v2[deep])) % m, deep + 1, type);
}
int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        i > n / 2 ? v1.push_back(a[i]) : v2.push_back(a[i]);
    }
    dfs(0, 0, 1);
    mp.clear();
    dfs(0, 0, 0);
    sort(v3.begin(), v3.end());
    sort(v4.begin(), v4.end());
    maxx = max(v3[v3.size() - 1], v4[v4.size() - 1]);
    for (int i = 0; i < v3.size(); i++)
    {
        maxx = max(maxx, ((v3[i] + v4[v4.size() - 1]) % m));
        maxx = max(maxx, (v3[i] + *(lower_bound(v4.begin(), v4.end(), m - v3[i]) - 1)) % m);
    }
    cout << maxx;
}
```


---

## 作者：Lumos壹玖贰壹 (赞：0)

#### 折半搜索
##### Problem
给一个长为n($\le35$)的数列和模数m，在数列任选若干个数，使得他们的和对m取模后最大
##### Solution
n$\le35$，典型的搜索数据。再想想其他算法没做法，搜索开题。

1. 35小虽然小，但如果枚举每个子集，复杂度是$O(2^{35})$,T飞。
2. 由于子集具有**可合并性**，那么我们为何不把这个数列分成**两半**，**分别**搜出子集，然后再**合并**两边的子集不就变成**整个数列**的子集了吗。
3. 但合并也是个问题，两边各有$2^{17}$个子集，显然不能一个一个合。我们把每个子集内的数的和算出来%m(答案也是要%m下最大)，那么合并的两个子集一定都$<$m。如果它们$(x$和$y)$两个加起来$\ge$m了，那么还不如其中任意一个子集(对于x相当于加了$y-m$)。所以要在不超过和m的情况下尽可能大。
4. 我们把左右两半数列的所有结果%m后分别计入$l$[ ]和$r$[ ],然后把l和r快排一下。i=1，t=tot，若$l[i]+r[t] \ge m$，让t变小，直到$l[i]+r[t] < m$，用这个来更新答案，然后$i$++

##### Code
一些细节在代码里有注释
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ri register int
using namespace std;
const int maxn=(1<<18);
int l[maxn],r[maxn],a[40],n,mod,cnt=1;
void dfs(int now,int en,int op,int sum){//搜到第now位，结尾是第en位，是在搜哪一半，现在的和是多少
	if(now>en){
		if(op==0) l[++cnt]=sum;
		else r[++cnt]=sum;
		return;
	}
	dfs(now+1,en,op,sum);//不加这个
	dfs(now+1,en,op,(sum+a[now])%mod);//加这个数
}
int main(){
	scanf("%d%d",&n,&mod);
	for(ri i=1;i<=n;i++) scanf("%d",&a[i]);
	cnt=0;dfs(1,n/2,0,0);//搜前一半
	sort(l+1,l+cnt+1);//sort一下
	cnt=0;dfs(n/2+1,n,1,0);//搜后一半
	sort(r+1,r+cnt+1);//sort一下
	int t=cnt,ans=0;
	for(ri i=1;i<=cnt;i++){
		ans=max(ans,(l[i]+r[t])%mod);
		while(l[i]+r[t]>=mod) t--;
		ans=max(ans,(l[i]+r[t])%mod);
	}
	printf("%d\n",ans);
	return 0;
}

```

---

## 作者：cirnovsky (赞：0)

## 题意简述

见翻译

## 题解

记录一下犯下的一个 nt 错误。

首先我们有一个显然的 DFS 暴力，每次两种决策，选或不选，所以时间复杂度为 $\Theta(2^{n})$。

$n$ 的范围是 35，是过不了的，我们可以考虑折半搜索。

关于折半搜索可以看看 [我的折半搜索小计](https://www.luogu.com.cn/blog/161849/gen-hao-sou-suo-xiao-ji)。

暴力搜出 $[1,\lfloor\frac{n}{2}\rfloor],[\lfloor\frac{n}{2}\rfloor+1,n]$ 的所有答案，记录到两个 vector 里面。

这一部分的时间复杂度是 $\Theta(2^{\lfloor\frac{n}{2}\rfloor})$。

考虑合并贡献。

先考虑一个暴力合并贡献的方法。

我们记第一次搜索搜出来的答案序列为 $A_{1}$，同理有 $A_{2}$。

这里的两个答案序列都是在模 $m$ 意义下的。

那么对于每一个 $A_{1,i}$，我们都可以暴力在 $A_{2}$ 中寻找两者相加模 $m$ 的最大值。

那么我们可以分类讨论了，因为序列在模 $m$ 意义下，所以我们对于每一个 $A_{1,i}$ 找到的 $A_{2,j}$ 使得 $(A_{1,i}+A_{2,j})\bmod m$ 最大，都只有两种情况。

一种是 $A_{2,j}$ 在 $A_{2}$ 中值域范围在 $[0,m-A_{1,i}-1]$ 的所有值中最大，一种是在 $A_{2}$ 中值域范围在 $[0,m\times2-A_{1,i}-1]$ 的所有值中最大。

所以我们在这两种情况中取最大即可。

由于我不理解二分做法，所以我用的是动态开点值域线段树。

（flag：动态开点不加引用就【】）

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=35+5;
const int H=99999999;
int n,m,tot=1,root=1,ans,a[N];
struct Tree
{
	int ls,rs,val;
} nodes[(1<<(N>>1))<<3];
vector<int> vec[2];

void dfs(int x,int cur,int lim)
{
	if(x>lim)
	{
		if(lim==(n>>1)) 	vec[0].push_back(cur);
		else	vec[1].push_back(cur);
		return ;
	}
	dfs(x+1,(cur+a[x])%m,lim);
	dfs(x+1,cur,lim);
}

void ins(int &p,int l,int r,int x)
{
	if(p==0)	p=++tot;
	if(l==r)
	{
		nodes[p].val=l;
		return ;
	}
	int mid=(l+r)>>1;
	if(mid>=x)	ins(nodes[p].ls,l,mid,x);
	else	ins(nodes[p].rs,mid+1,r,x);
	nodes[p].val=max(nodes[nodes[p].ls].val,nodes[nodes[p].rs].val);
}

int find(int p,int l,int r,int x,int y)
{
	if(l>y||r<x)	return 0;
	if(l>=x&&r<=y)	return nodes[p].val;
	int mid=(l+r)>>1,ret=0;
	if(mid>=x)	ret=max(ret,find(nodes[p].ls,l,mid,x,y));
	if(mid<y)	ret=max(ret,find(nodes[p].rs,mid+1,r,x,y));
	return ret;
}

void output(int p)
{
	if(nodes[p].ls==0&&nodes[p].rs==0)
	{
		printf("%d ",nodes[p].val);
		return ;
	}
	output(nodes[p].ls);
	output(nodes[p].rs);
}

signed main()
{
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;++i)	scanf("%d",&a[i]);
	dfs(1,0,n>>1);
	dfs((n>>1)+1,0,n);
	sort(vec[0].begin(),vec[0].end());
	sort(vec[1].begin(),vec[1].end());
	for(auto x:vec[1])	ins(root,0,m-1,x);
	for(auto x:vec[0])	ans=max(ans,max(x+find(1,0,m-1,0,m-x-1),(x+find(1,0,m-1,0,m*2-x-1))%m));
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：极寒神冰 (赞：0)

## 折半搜索

1.  将整个数组分成两半

2.  暴力枚举前一半数的所有组合，保存下来进行排序，复杂度最多为2^18

3.  暴力枚举另一半数的所有组合为x，到原先保存的数组中去寻找一个小于等于m-1-x的最大的一个数，如果不存在就取原先数组中最大的一个数。

问题就变成了一个在有序数组中查找某一个数，可以使用二分解决。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=400010;
int ans,m,tot,n,mod;
int a[40],b[N];
inline int check(int x)
{
	int m=n/2;
	int l=0,r=(1<<m)-1,best=0;
	while(l<=r)
	{
		int mid=(l+r)/2;
		if(b[mid]<=x)
		{
			best=b[mid];
			l=mid+1;
		}
		else r=mid-1;
	}
	return best;
}
int main()
{
	scanf("%d%d",&n,&mod);
	for(int i=0;i<n;i++)
	{
		scanf("%d",&a[i]);		
		//a[i]%=mod;
	}		
    m=n/2;
	for(int i=0;i<(1<<m);i++)
	{
		int tmp=0;
		for(int j=0;j<m;j++)
		{
			if(i&(1<<j))
			{
				tmp=(tmp+a[j])%mod;
			}
		}
		b[tot++]=tmp;
		ans=max(tmp,ans);
	}
	sort(b,b+tot);
	m=n-(n/2);
	for(int i=0;i<(1<<m);i++)
	{
		int tmp=0;
		for(int j=0;j<m;j++) 
		{
			if(i&(1<<j))
			{
				int jj=j+n/2;
				tmp=(tmp+a[jj])%mod;
			}
		}
		ans=max(ans,tmp);
		ans=max(ans,tmp+check(mod-tmp-1)); 
	}
	cout<<ans；
} 
```



---

## 作者：Dzhao (赞：0)

# 题解 CF888E

进入本题：

我们先分析数据
>$(n\leq35,m\leq10^9)$

嗯，不用开$long long$，暴力枚举每一种情况肯定会TLE

因为，时间复杂度为$O(2^n)$

$2^{35}=34,359,738,368$

开心吗，喜悦吗，激动吗，兴奋吗

……

进入正题，我们肯定要寻找一种优秀的枚举方法

我们思考了一下，发现 $2^{18}=262144$，小的可怜，于是，我们可以从分治枚举的角度思考，先将$1$~$n/2$和$n/2+1$~$n$的每一种情况枚举好，然后将结果排个序，可以发现加上取得值的和mod m后的值的图像是单调递增的，差不多是这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/9zgct6gh.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

我们现在就将这个问题变成了在第一坨数中选出一个数，使他和第二坨数中的一个数匹配，获得最优秀的一个数。

从第一堆中选出一个数，很简单，$for$循环一遍就好了，复杂度:

$O(SIZE)=O(2^{n/2})$

从第二堆中选出一个数，我们就需要优化了，因为数列具有单调性，我们只需要找出图中所示第一条函数的顶$pos$就行了，然后我们就可以将$pos$这个位置上的值与最后一位比较就行了。

$$tmp1=(sum_{0,i}+sum_{1,pos})modm$$
$$tmp2=(sum_{0,i}+sum_{1,cnt_1})modm$$
$$ans=max(ans,tmp1,tmp2);$$

时间复杂度:
$$O(2^{n/2}+2^{n-n/2}+2^{n/2}*log(2^{n-n/2}))=O(2^{n/2}*n/2)$$
具体请看代码

----------------------------------------------------大家好，我是分割线----------------------------------------------------

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=39;
const int M=300009;
int a[N],sum[2][M],cnt[2],n,m,l[2],r[2];
inline int max(int x,int y) {return x>y?x:y;}
void dfs(int u,int k,int step) //预处理出所有的组合情况 
{
	if(u>r[k])
	{
		sum[k][++cnt[k]]=step;
		return;
	}
	dfs(u+1,k,(step+a[u])%m); //取 
	dfs(u+1,k,step); //不取 
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	l[0]=1,r[0]=n/2;
	l[1]=r[0]+1,r[1]=n;
	dfs(1,0,0);dfs(l[1],1,0);
	sort(sum[1]+1,sum[1]+cnt[1]+1); //排序一下 
	int ans=0;
	for(int i=1;i<=cnt[0];i++)
	{
		int l=1,r=cnt[1],pos=1; 
		while(l<=r) //二分查找第一个和小于m的位置 
		{
			int mid=(l+r)>>1;
			if(sum[1][mid]+sum[0][i]>=m) r=mid-1;
			else l=mid+1,pos=mid;
		}
		ans=max(ans,max((sum[0][i]+sum[1][pos])%m,(sum[0][i]+sum[1][cnt[1]])%m)); //加该位or加末位 
	}
	printf("%d\n",ans);
	return 0;
}
```
他教会了我们如何~~优雅的~~枚举

## [安利下我的博客](https://www.luogu.com.cn/blog/qshjydzh/solution-cf888e)

---

