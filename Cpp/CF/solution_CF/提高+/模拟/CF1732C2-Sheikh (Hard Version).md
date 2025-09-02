# Sheikh (Hard Version)

## 题目描述

This is the hard version of the problem. The only difference is that in this version $ q = n $ .

You are given an array of integers $ a_1, a_2, \ldots, a_n $ .

The cost of a subsegment of the array $ [l, r] $ , $ 1 \leq l \leq r \leq n $ , is the value $ f(l, r) = \operatorname{sum}(l, r) - \operatorname{xor}(l, r) $ , where $ \operatorname{sum}(l, r) = a_l + a_{l+1} + \ldots + a_r $ , and $ \operatorname{xor}(l, r) = a_l \oplus a_{l+1} \oplus \ldots \oplus a_r $ ( $ \oplus $ stands for [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)).

You will have $ q $ queries. Each query is given by a pair of numbers $ L_i $ , $ R_i $ , where $ 1 \leq L_i \leq R_i \leq n $ . You need to find the subsegment $ [l, r] $ , $ L_i \leq l \leq r \leq R_i $ , with maximum value $ f(l, r) $ . If there are several answers, then among them you need to find a subsegment with the minimum length, that is, the minimum value of $ r - l + 1 $ .

## 说明/提示

In all test cases, the first query is considered.

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
2 2
5 10
1 2
2 2
3 3
0 2 4
1 3
1 2
2 3
4 4
0 12 8 3
1 4
1 3
2 4
2 3
5 5
21 32 32 32 10
1 5
1 4
1 3
2 5
3 5
7 7
0 1 0 1 0 1 0
1 7
3 6
2 5
1 4
4 7
2 6
2 7```

### 输出

```
1 1
1 1
2 2
1 1
1 1
2 2
2 3
2 3
2 3
2 3
2 3
2 3
2 3
2 3
3 4
2 4
4 6
2 4
2 4
4 6
2 4
2 4```

# 题解

## 作者：Feyn (赞：6)

一道比较好的题目。

首先有一个结论，如果不限制长度的话，那么把给定的区间选满肯定是更优的。可以假设我们已经有一个异或和是 $x$ 的数列，加进去一个元素 $a$，那么这个数列的价值变化量应该就是 $a+x-(x\oplus a)$。显然这个东西是非负的，所以最优序列的值是可以直接计算得到的，所以对于 C1 可以考虑枚举左端点，然后二分右端点，找到第一个右端点使得这个区间的答案等于计算的最优答案，更新即可。

而对于 C2 而言就需要更具象化的柿子了。考虑上面那个柿子，显然可以按位考虑，分类讨论之后发现对于某一位而言，当 $x$ 和 $a$ 的这一位同时为 $1$ 时，贡献是这一位的两倍；对于其它情况这一位都是没有贡献的（就拿 $1,0$ 举例，$a+x$ 这一位是 $1$，$a\oplus x$ 这一位也是，一减就没了）。然后可以推出假如一个序列某一位上 $1$ 的个数是 $t$，那么这一位的贡献应该是 $\lfloor\frac{t}{2}\rfloor\times 2$ 个该位对应的权值（因为只有第偶数次出现才会有贡献，而每次贡献会贡献两个权值，所以有这个柿子）。

于是可以对区间内每一位 $1$ 的数量分类讨论，如果是偶数的话就很简单，第一个 $1$ 到最后一个 $1$ 之内的数都必须选，这显然是最优且唯一的方案。如果是奇数的话，为了缩短长度我们可以去掉第一个或者最后一个 $1$。最终选择的区间是这些位对应的决策区间的并。

于是问题就变成了有很多个区间，有些区间必须选，有些区间两两配对需要至少选一个，希望最小化这些区间并的大小。考虑到区间数量是很少的，所以可以枚举答案区间的左端点，然后对于剩下的区间贪心即可。设值域为 $[1,S]$，复杂度即是 $O(N\log^2S)$。代码比较好写。

```cpp
#include<bits/stdc++.h>
//#define feyn
const int N=100010; 
using namespace std;
inline void read(int &wh){
    wh=0;char w=getchar();int f=1;
    while(w<'0'||w>'9'){if(w=='-')f=-1;w=getchar();}
    while(w<='9'&&w>='0'){wh=wh*10+w-'0';w=getchar();}
    wh*=f;return;
}
     
int m,a[N],q,sum[N][32],plB[N][32],plA[N][32];
     
struct node{int l,r;}s[50],ll[50],rr[50];
int x,y;//x-s y-ll&rr
     
int ans,al,ar;
inline void check(int l){
    int mxr=0;
    for(int i=1;i<=x;i++)if(s[i].l<l)return;else mxr=max(mxr,s[i].r);
    for(int i=1;i<=y;i++){
    	if(ll[i].l<l){
    		if(rr[i].l<l)return;
    		else mxr=max(mxr,rr[i].r);
    	}
    	else mxr=max(mxr,ll[i].r);
    }
    if(ans<=mxr-l+1)return;
    ans=mxr-l+1;al=l,ar=mxr;
}
inline void work(){
    x=0;y=0;int l,r;read(l);read(r);ans=1e9;
    for(int i=0;i<=31;i++){
    	int nowSum=sum[r][i]-sum[l-1][i];
    	if(nowSum<=1)continue;
    	int aa=plA[l][i],bb=plB[r][i];
    	if(nowSum&1){
    		int aaa=plA[aa+1][i],bbb=plB[bb-1][i];
    		y++;rr[y]=(node){aaa,bb};ll[y]=(node){aa,bbb};
    	}
    	else s[++x]=(node){aa,bb};
    }
    if(x==0&&y==0)return printf("%d %d\n",l,l),void();
    for(int i=1;i<=x;i++)check(s[i].l);
    for(int i=1;i<=y;i++)check(ll[i].l),check(rr[i].l);
    return printf("%d %d\n",al,ar),void();
}
void solve(){
    read(m);read(q);
    for(int i=1;i<=m;i++)for(int j=0;j<=31;j++)sum[i][j]=plB[i][j]=plA[i][j]=0;
    for(int i=1;i<=m;i++){read(a[i]);for(int j=0;j<=31;j++)sum[i][j]=sum[i-1][j]+(((1<<j)&a[i])>0);}
    for(int i=1;i<=m;i++)for(int j=0;j<=31;j++)if((1<<j)&a[i])plB[i][j]=plA[i][j]=i;
    for(int i=1;i<=m;i++)for(int j=0;j<=31;j++)if(plB[i][j]==0)plB[i][j]=plB[i-1][j];
    for(int i=m;i>=1;i--)for(int j=0;j<=31;j++)if(plA[i][j]==0)plA[i][j]=plA[i+1][j];
    while(q--)work();
}
     
signed main(){
	
    #ifdef feyn
    freopen("in.txt","r",stdin);
    #endif
    	
    int test;read(test);
  	while(test--)solve();

   	return 0;
}
```

---

## 作者：c202201 (赞：4)


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

## 作者：星星与辰 (赞：4)

## 题意
给出一个数列 $A$，我们定义一个区间 $[l,r]$ 的价值为 ${\sum_{i=l}^rA_i}-{\bigoplus_{i=l}^{r}A_i}$，现在给出 $Q$ 次询问，每次询问会给出一个区间 $[L,R]$，你要求出该区间的所有子区间中价值最大的那个区间并输出，若有多个价值相同且最小的区间，我们应输出其中区间长度（即 $l-r+1$）最短的那个。

## 思路
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

## 作者：MoyunAllgorithm (赞：2)

## 题意
给你一个 $N (1 \le N \le 10^5)$ 的非负数组 $a$。定义 $sum_{i,j}= a_i + a_{i+1}+\cdots +a_j,xor_{i,j}=a_i \oplus a_{i+1} \oplus \cdots \oplus a_j$。 定义 $f(i,j)= sum_{i,j}-xor_{i,j}$。进行 $N$ 次询问，给定 $l,r$，求区间 $[l,r]$ 的所有子区间 $[l_1,r_1]$ 中，$f(l_1,r_1)$ 最大的前提下长度最短的那一个。

## 分析

发现对于区间 $[l,r]$，$f(l,r+1) \ge f(l,r)$。

**证明**

$f(l,r+1)-f(l,r)$

$=sum_{l,r+1}-xor{l,r+1}-sum_{l,r}+xor_{l,r}$

$=a_{r+1}- xor_{l,r+1}+ xor_{l,r}$。

因为 $ xor_{l,r+1}- xor_{l,r} \le a_{r+1}$ (因为异或是不进位加法)

所以得到 $f(l,r+1)-f(l,r) \ge 0$。同理可证 $f(l-1,r) \ge  f(l,r)$。

这说明：**答案区间的 $f$ 值一定与询问区间的 $f$ 值相等；当区间的一端点固定，当它的另一端点向远移动时，$f$ 值是单调不减的**。

这启示我们**在询问区间的基础上进行删减**。

如何判断一个元素被删掉之后，原来区间的 $f$ 不会变小？

首先，如果它是 $0$，随便删；

其次，如果这个数在加和方面的贡献和在异或和方面的贡献相同，可以删。

具体地，如果**加上这个数不会造成加法进位，也就是这个数上的每一个 $1$ 对应的位置原来都是 $0$**，那么这时异或它和加它的结果相同，可以删除。那么有多少个这样的数？因为加上这个数之后至少有一个原来的 $0$ 位变成了 $1$，所以说二进制下 $f(l,r)$ 有多少个 $1$，这样的数就最多有多少个。可以发现数量是 $\log$ 级别。

故我们先**删除所有是 $0$ 的数**，之后枚举删掉一些数之后的左右端点即可。单次询问复杂度 $O(\log^2 N)$。

### AC CODE

```cpp
// LUOGU_RID: 97435153
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=1e5+5;
int Read()
{
	int f=1,x=0;
	char ch=getchar();
	while(!isdigit(ch))
	{
		if(ch=='-') f=-1;
		ch=getchar();
 	}
 	while(isdigit(ch))
 	{
 		x=(x<<1)+(x<<3)+(ch^48);
 		ch=getchar();
	}
	return f*x;
}
int T,N,Q;
long long psum[MAXN],pxor[MAXN];
int a[MAXN];
int b[MAXN];
long long Func(int l,int r)
{
	return psum[r]-psum[l-1]-(pxor[r]^pxor[l-1]);
}
signed main()
{
	T=Read();
	while(T--)
	{
		N=Read(),Q=Read();
		int M=0;
		for(int i=1;i<=N;i++) 
		{
			a[i]=Read();
			if(a[i]) b[++M]=i;//b 为去除0 后的数组
		}
		for(int i=1;i<=M;i++)
		{
			psum[i]=psum[i-1]+a[b[i]];
			pxor[i]=pxor[i-1]^a[b[i]];
		}
		while(Q--)
		{
			int l=Read(),r=Read();
			int x=l;
			l=lower_bound(b+1,b+M+1,l)-b;
			r=upper_bound(b+1,b+M+1,r)-b-1;
			long long goal=Func(l,r);
			int ansl=l,ansr=r;
          //这里其实是去除0工作
	//		printf("RANGE%lld %lld\n",l,r);
			if(l>r||M==0)
			{
				printf("%lld %lld\n",x,x);
				continue;
			}
			for(int i=l;i<=min(l+30,r);i++)//左
			{
				for(int j=max(r-30,l);j<=r;j++)//右
				{
					if(i<=j&&Func(i,j)==goal&&b[j]-b[i]+1<b[ansr]-b[ansl]+1) 
					{
						ansl=i;
						ansr=j;
					}
				}
			}
			printf("%lld %lld\n",b[ansl],b[ansr]);
		}
	}
	return 0;
}
```


---

## 作者：linyihdfj (赞：2)

## CF1732C2 Sheikh (Hard Version)
想要更优质的阅读体验，就来[这里](https://www.cnblogs.com/linyihdfj/p/16893607.html)吧。
### 题目分析：
这种题一般都会考虑这样的一个性质：$a + b \ge a \oplus b$
因为异或本质上是不进位加法，显然不可能进位加法大。

我们显然可以考虑前缀和以及前缀异或，设 $sum_i$ 为 $[1,i]$ 的和，$xor_i$ 为 $[1,i]$ 的异或。

那么区间 $[l,r]$ 的价值就是 $sum_r - sum_{l-1} - xor_r \oplus xor_{l-1}$，考虑假设我们新添加了一些数，满足这些数的和为 $x$，异或为 $y$，那么新区间的价值就是：$sum_r - sum_{l-1} + x - xor_r \oplus xor_{l-1} \oplus y$。
根据上面的性质带入一下会发现，新区间的价值一定大于等于原区间的价值。

所以其实对于一个询问 $[L,R]$，最大的价值一定等于 $[L,R]$ 对应的区间的价值。

那么就是找到一个尽可能短的区间使得价值与 $[L,R]$ 相等了。
不进位加法与普通加法相比就是进位的不同啊，所以只要不进位就一定是合法的，我们最多只有 $30$ 位，所以根据鸽巢原理我们能选择的数一定不超过 $30$ 个。

所以就是直接枚举左边删多少个右边删多少个，算一下新区间的答案就好了。

但是需要注意的是我们删 $30$ 个是指的每一个至少含有一个 $1$ 的情况下，所以应该先把 $0$ 全部去掉再做。

### 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 5e6+5;
int sum[N],xo[N],b[N],a[N];
int calc(int l,int r){return sum[r] - sum[l-1] - (xo[r] ^ xo[l-1]);}
signed main(){
	int t;
	scanf("%lld",&t);
	while(t--){
		int tot = 0;
		int n,q;scanf("%lld%lld",&n,&q);
		for(int i=1; i<=n; i++){
			scanf("%lld",&a[i]);
			if(a[i] != 0) 	b[++tot] = i;
		}
		n = tot;   //直接把零去掉 
		for(int i=1; i<=n; i++)	sum[i] = sum[i-1] + a[b[i]];
		for(int i=1; i<=n; i++)	xo[i] = xo[i-1] ^ a[b[i]];
		while(q--){
			int l,r;scanf("%lld%lld",&l,&r);int tmp = l;
			l = lower_bound(b+1,b+n+1,l) - b;
			r = upper_bound(b+1,b+n+1,r) - b - 1;
			if(l > r || n == 0){  //都是零就无所谓了 
				printf("%lld %lld\n",tmp,tmp);
				continue;
			}
			int ansl = l,ansr = r;
			for(int i=l; i<=min(l+30,r); i++){  //最多一边删三十个 
				for(int j=r; j>=max(r-30,l); j--){
					if(i <= j && calc(l,r) == calc(i,j) && b[j] - b[i] < b[ansr] - b[ansl]){
						ansl = i,ansr = j;
					}
				}
			}
			printf("%lld %lld\n",b[ansl],b[ansr]);
		}
	}
}
```

---

## 作者：LHQing (赞：1)

#### 思路分析

将异或理解为不进位加法。可以得到一个显然的结论：$a+b\ge a\operatorname{xor} b$。

因此，区间越大越好，即 $f(l,r)$ 最大。此题即为求 $f(p,q)$ 使得 $f(p,q)=f(l,r)$ 的同时 $q-p$ 最小。

考虑到 $a+b=a\operatorname{xor} b$ 的必要条件是 $a$ 与 $b$ 二进制上的位不相同。于是有起始时 $p=l,q=r$，两边最多缩小 $30$ 次，最多枚举 $900$ 次。足够通过此题。

坑点：要将序列中的 $0$ 去掉。

#### 题解代码

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

struct ios {
    inline char read() {
        static const int inlen = 1 << 18 | 1;
        static char buf[inlen], *s, *t;
        return (s == t) && (t = (s = buf) + fread(buf, 1, inlen, stdin)), s == t ? -1 : *s++;
    }
    template<typename T> inline ios& operator>> (T &x) {
        static char c11, boo;
        for (c11 = read(), boo = 0; !isdigit(c11); c11 = read()) {
            if (c11 == -1) return *this;
            boo |= c11 == '-';
        }
        for (x = 0; isdigit(c11); c11 = read()) x = x * 10 + (c11 ^ '0');
        boo && (x = -x);
        return *this;
    }
} fin;

struct exios {
    template<typename _CharT, typename _Traits = char_traits<_CharT>>
    struct typ {
        typedef basic_ostream<_CharT, _Traits>& (* end) (basic_ostream<_CharT, _Traits>&);
    };

    template<typename T> friend exios &operator<<(exios &out, T num) {
        if (num < 0) putchar('-'), num = -num;
        if (num >= 10) out << num / 10;
        putchar(num % 10 + '0');
        return out;
    }

    friend exios &operator<<(exios &out, const char * s) { printf("%s", s); return out; }
    friend exios &operator<<(exios &out, string s) { cout << s; return out; }
    friend exios &operator<<(exios &out, typ<char>::end e) { puts(""); return out; }
} fout;

const int maxn = 1e5 + 10;
typedef pair<int, int> pii;

int t, n, q;
int a[maxn];
int b[maxn];
int c[maxn];

int f(int l, int r) {
    return (a[r] - a[l - 1]) - (b[r] ^ b[l - 1]);
}

signed main() {
    fin >> t;
    while (t--) {
        fin >> n >> q;
        int cnt = 0;
        for (int i = 1, x; i <= n; i++) {
            fin >> x;
            a[i] = b[i] = x;
            if (x != 0) {
                c[++cnt] = i;
            }
        }
        for (int i = 1; i <= n; i++) {
            a[i] += a[i - 1];
            b[i] ^= b[i - 1];
        }
        while (q--) {
            int l, r;
            fin >> l >> r;
            int m = f(l, r);
            int ansl = l, ansr = r;
            int posl = lower_bound(c + 1, c + 1 + cnt, l) - c;
            int posr = upper_bound(c + 1, c + 1 + cnt, r) - c - 1;
            if (posl > posr || !cnt) {
                fout << l << " " << l << endl;
                continue;
            }
            // cout << posl << " " << posr << " ";
            for (int i = posl; i <= min(cnt, posl + 30); i++) {
                for (int j = posr; j >= max(1ll, posr - 30); j--) {
                    if (i > j) continue;
                    if (f(c[i], c[j]) == m && c[j] - c[i] < ansr - ansl) {
                        ansl = c[i];
                        ansr = c[j];
                    }
                }
            }
            fout << ansl << " " << ansr << endl;
        }
    }
    return 0;
}
```

---

## 作者：ZLCT (赞：0)

# CF1732C2 Sheikh (Hard Version)
## 形式化题意
给定一个数组 $a$，每次给定 $L,R$，需要找出一个区间 $[l,r]$ 满足 $L\le l\le r\le R$ 并使 $(\sum\limits_{i=l}^{r}a_i)-\oplus_{i=l}^{r}a_i$ 最大。若有多组解则输出 $r-l+1$ 最小的任意一组解。
## 思路分析
题目既然要求我们找一组长度最小的解，那我们可以先从这里下手，分析长度最小的用意。\
因为我们知道 $a+b\ge a\oplus b$，所以我们如果选取了 $[x,y]$，那么继续选取 $[x,y+1]$ 一定不会使答案变得更劣，所以我们的答案就是 $[L,R]$ 区间的答案。这也就说明了为什么题目要求输出长度最小的解，否则直接输出 $[L,R]$ 就完事了。\
我们设 $[L,R]$ 区间加和为 $sumadd$，异或和为 $sumxor$ 那我们的问题就变成了在 $[L,R]$ 区间中删除若干数，使得新区间的答案为 $sumadd-sumxor$。\
由于要构成一个新区间，所以原问题也可以进一步转化为 $[L,R]$ 区间删除最长前后缀使得新区间答案为 $sumadd-sumxor$。\
那么我们接下来考虑删除什么元素不会使答案变小（因为根据上面的推论，如果答案变小则变不回来了）。\
因为我们对于加法比较熟悉，那就先从加法角度看删除 $a_l$ 的影响，很显然影响就是 $sumadd\leftarrow sumadd-a_l$。根据等式的基本性质，如果要使 $sumadd=sumxor$，那么删除 $a_l$ 对于 $sumxor$ 的影响也一定是 $sumxor\leftarrow sumxor-a_l$。我们现在知道 $a_l$ 对于 $sumxor$ 的影响从定义上看是 $sumxor\leftarrow sumxor\oplus a_l$，那二者等价就意味着 $sumxor-a_l=sumxor\oplus a_l$。\
这是个经典的讨论，对于每一个二进制位，除了减数与被减数的该位分别为 $0,1$ 时异或才不等于减，具体分讨情况如下：
- $1,1$：$1\oplus1=0=1-1$
- $1,0$：$1\oplus0=1=1-0$
- $0,1$：$0\oplus1=1\ne0-1$
- $0,0$：$0\oplus0=0=0-0$

那么我们则可以发现若一个区间内的正整数可以被删除，那么至少会把 $sumadd-sumxor$ 带走一个二进制上的 $1$，所以我们暴力枚举左右分别减多少个数的复杂度只有 $O(\log^2n)$。\
但是观察数据范围会发现有 $a_i\ge0$ 这个麻烦的设定。\
俗话说七步之内必有解药，它麻烦的地方正是解决它的办法。\
它麻烦就麻烦在无论有多少 $0$，都不会对 $sumadd-sumxor$ 有任何影响，那我们不妨直接利用这点把 $0$ 忽略即可。\
这个忽略 $0$ 的时候有很多细节，尤其对于边界处理要格外注意。\
算法还有一个容易想到的错贪心，就是分别从两侧能删则删，并取其中长度最小的一组。那这里给出一组 hack：$a=[1,2,12,12,3,3,4,8],L=1,R=8$。
## code
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e5+666;
int n,q;
ll sumadd,sumxor;
ll a[N],pres[N],prex[N];
int b[N];
void solve(){
    memset(pres,0,sizeof(ll)*(n+5));
    memset(prex,0,sizeof(ll)*(n+5));
    memset(b,0,sizeof(ll)*(n+5));
    cin>>n>>q;
    b[0]=0;
    for(int i=1;i<=n;++i){
        cin>>a[i];
        pres[i]=pres[i-1]+a[i];
        prex[i]=prex[i-1]^a[i];
        if(a[i])b[++b[0]]=i;
    }
    while(q--){
        int l,r;cin>>l>>r;
        if(b[0]==0){
            cout<<l<<' '<<l<<'\n';
            continue;
        }
        int ansl=l,ansr=r;
        l=int(lower_bound(b+1,b+1+b[0],l)-b);
        r=int(upper_bound(b+1,b+1+b[0],r)-b-1);
        sumadd=pres[b[r]]-pres[b[l]-1];
        sumxor=prex[b[r]]^prex[b[l]-1];
        if(l>=r){
            cout<<ansl<<' '<<ansl<<'\n';
            continue;
        }
        for(int dl=0;dl<=31;++dl){
            for(int dr=0;dr<=31;++dr){
                if(l+dl>r-dr)break;
                if(l+dl>b[0]||r-dr<1)continue;
                int stl=b[l+dl],str=b[r-dr];
                ll stsum=pres[str]-pres[stl-1];
                ll stxor=prex[str]^prex[stl-1];
                if(stsum-stxor!=sumadd-sumxor)continue;
                if(ansr-ansl>str-stl){ansl=stl;ansr=str;}
            }
        }
        cout<<ansl<<' '<<ansr<<'\n';
    }
}
signed main(){
    int T;cin>>T;
    while(T--)solve();
    return 0;
}
```
## code by `KrK`
```cpp
#include <bits/stdc++.h>
using namespace std;

const int Maxn = 100005;

int T;
int n, q;
int seq[Maxn], slen;
int a[Maxn];
int xr[Maxn];
int L, R;
int l, r;
int wth, bl, br;

void checkRight(int i, int cur2)
{
    for (int j = r; j > i && (cur2 & a[seq[j]]) == a[seq[j]]; j--) {
        cur2 ^= a[seq[j]];
        if (i + 1 == j) { wth = 0; bl = L; br = L; }
        else if (seq[j - 1] - seq[i + 1] < wth) {
            wth = seq[j - 1] - seq[i + 1];
            bl = seq[i + 1];
            br = seq[j - 1];
        }
    }
}

int main()
{
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d", &n, &q);
        slen = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
            xr[i] = (a[i] ^ xr[i - 1]);
            if (a[i]) seq[slen++] = i;
        }
        while (q--) {
            scanf("%d %d", &L, &R);
            l = lower_bound(seq, seq + slen, L) - seq;
            r = upper_bound(seq, seq + slen, R) - seq - 1;
            if (l > r) { printf("%d %d\n", L, L); continue; }
            wth = seq[r] - seq[l]; bl = seq[l]; br = seq[r];
            int cur = (xr[R] ^ xr[L - 1]);
            checkRight(l - 1, cur);
            for (int i = l; i <= r && (cur & a[seq[i]]) == a[seq[i]]; i++) {
                cur ^= a[seq[i]];
                if (i == r) { wth = 0; bl = L; br = L; }
                else if (seq[r] - seq[i + 1] < wth) {
                    wth = seq[r] - seq[i + 1];
                    bl = seq[i + 1];
                    br = seq[r];
                }
                checkRight(i, cur);
            }
            printf("%d %d\n", bl, br);
        }
    }
    return 0;
}
```
看到这份代码会惊奇地发现 `KrK` 竟然没有维护区间加和，那他是如何判断可否删除呢？\
实际上我们考虑 $\oplus,+,\land$ 之间的关系，我们会发现对于每一个二进制位，$a+b=(a\oplus b)+(a\land b)$。具体原理是因为异或是不进位加法，与运算就充当了进位。\
由于我们只关注每一位的奇偶性，那么原来的 $sumadd-sumxor$ 其实就相当于 $sumadd\land sumxor$。

---

## 作者：WaterSun (赞：0)

[更好的阅读体验](https://watersun.top/%5B%E9%A2%98%E8%A7%A3%5DCF1732C2%20Sheikh%20(Hard%20Version))

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

## 作者：赵悦岑 (赞：0)

## 题意

定义一个序列的价值为其元素的和减去异或和。给出长度为 $n$ 的序列和 $q=n$ 个询问，每次询问 $[l,r]$ 中价值最大的前提下长度最短的子段。

## 分析

首先因为异或运算是不进位加法，有 $x \oplus y \leq x+y$，所以$x_1+y -(x_2 \oplus y) \geq x_1-x_2$，即向一个序列中加入一个数，价值不降，所以选取整个区间的价值就是最大的。

考虑求出长度最小的区间，按位考虑：假如原来的异或和为 $1$，加入 $1$，会产生 $2$ 的价值，使异或和变为 $0$；假如原来的异或和为 $0$，加入 $1$，会产生 $0$ 的价值，使异或和变为 $1$；而加入 $0$ 不会对价值和异或和产生影响。可以发现，只有一个 $1$ 前面有奇数个 $1$ 时才会产生 $2$ 的贡献。因此一个含有 $x$ 个 $1$ 的序列对价值的贡献为 $2\lfloor \frac{x}{2} \rfloor$，又要保证这个价值刚好等于整个序列的价值，所以每一位的贡献都必须相同，所以当整个序列某一位的价值 $x$ 为偶数时，$x' = x$；否则 $x' = x,x-1$。即长度为偶数时包含的 $1$ 的个数和总共的个数相等，否则可以去掉最左边或最右边的 $1$。

现在我们有了 $\log$ 对区间，每一对中必须选择一个，使得所有区间并起来最小，显然最后并起来的左端点一定是某一个区间左端点，而区间个数是 $\log$ 级别的，我们可以枚举左端点，如果尽量选靠左的区间，但要保证所有区间的左端点不超过钦定的左端点，然后得到的右端点最小即可。

## code

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=200001,M=32;
int n,m,a[N],b[N][M][2],c[N][M];
struct str
{
    int l,r;
}d[M][2];
int check(int x)
{
    int s=x;
    for(int i=0;i<=30;++i)
    {
        if(d[i][0].l==-1) continue;
        if(d[i][0].l>=x) s=max(s,d[i][0].r);
        else if(d[i][1].l>=x) s=max(s,d[i][1].r);
        else return 1e9;
    }
    return s;
}
void abc()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        for(int j=0;j<=30;++j)
        {
            c[i][j]=c[i-1][j]+((a[i]&(1<<j))!=0);
        }
    }
    for(int i=0;i<=n+1;++i)
    {
        for(int j=0;j<=30;++j) b[i][j][0]=b[i][j][1]=0;
    }
    for(int i=n;i>=1;--i)
    {
        for(int j=0;j<=30;++j)
        {
            if((a[i]&(1<<j))!=0) b[i][j][0]=i;
            else b[i][j][0]=b[i+1][j][0];
        }
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=0;j<=30;++j)
        {
            if((a[i]&(1<<j))!=0) b[i][j][1]=i;
            else b[i][j][1]=b[i-1][j][1];
        }
    }
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        for(int j=0;j<=30;++j)
        {
            if(c[y][j]-c[x-1][j]<=1)
            {
                d[j][0]=d[j][1]=(str){-1,-1};
                continue;
            }
            if((c[y][j]-c[x-1][j])%2!=0)
            {
                d[j][0]=(str){b[x][j][0],b[b[y][j][1]-1][j][1]};
                d[j][1]=(str){b[b[x][j][0]+1][j][0],b[y][j][1]};
            }
            else
            {
                d[j][0]=d[j][1]=(str){b[x][j][0],b[y][j][1]};
            }
        }
        int s=check(x)-x+1,q=x;
        for(int j=0;j<=30;++j)
        {
            if(d[j][0].l==-1) continue;
            int z=check(d[j][0].l)-d[j][0].l+1;
            if(z<s) s=z,q=d[j][0].l;
            z=check(d[j][1].l)-d[j][1].l+1;
            if(z<s) s=z,q=d[j][1].l;
        }
        printf("%d %d\n",q,q+s-1);
    }
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--) abc();
    return 0;
}
```

---

