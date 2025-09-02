# Ilya and Two Numbers

## 题目描述

Ilya has recently taken up archaeology. He's recently found two numbers, written in the $ m $ -based notation. Each of the found numbers consisted of exactly $ n $ digits. Ilya immediately started looking for information about those numbers. He learned that the numbers are part of a cyphered code and the one who can decypher it can get the greatest treasure.

After considerable research Ilya understood that to decypher the code, he should do the following:

- Rearrange digits in the first number in some manner. Similarly, rearrange digits in the second number in some manner. As a result of this operation, the numbers can get leading zeroes.
- Add numbers, digit by digit, modulo $ m $ . In other words, we need to get the third number of length $ n $ , each digit of the number is the sum of the respective numbers of the found numbers. For example, suppose there are two numbers recorded in the ternary notation, 001210 and 012111, then if you add them to each other digit by digit modulo 3, you will get number 010021.
- The key to the code is the maximum possible number that can be obtained in the previous step.

Help Ilya, find the key to the code.

## 样例 #1

### 输入

```
4 7
5 4 3 2
5 6 5 4
```

### 输出

```
6 4 2 1 
```

## 样例 #2

### 输入

```
5 5
2 4 4 1 3
1 0 1 2 4
```

### 输出

```
4 4 4 3 2 
```

# 题解

## 作者：MyukiyoMekya (赞：5)

读完题第一个想法就是先给 $a_i$ 和 $b_i$ 分别从小到大排序，对于每个 $a_i$ ，显然 $b_i$ 就被分为了两部分：

$b_1,b_2,\cdots,b_j \le m-1-a_i$ ，剩下的加上 $a_i$ 都会 $\ge m$ ，导致要减掉 $m$ ，我们把对于当前 $a_i$ 的 $b_{1\sim j}$ 称为 $L$ ，剩下的称为 $R$

撕烤一下，把 $a_i$ 从小到大排序，从 $a_i$ 变为 $a_{i+1}$ 的时候，$L$ 中最大的一些数会到 $R$ 那里去。

我们贪心让每个 $a_i$ 取 $L$ 中最大的，那么显然会有一些 $b_i$ 被取多次，那么就从大到小枚举 $b_i$，多个 $a_i$ 想取这个 $b_i$ 就给最大的，然后最后会发现剩下没配对上的 $a_i,b_i$ 加起来总是 $\ge m$ ，直接排个序两两配对减去 $m$ 就行了。

实现起来不用那么麻烦，开两个桶和一个栈就好了：

```cpp
// This code wrote by chtholly_micromaker(MicroMaker)
#include <bits/stdc++.h>
#define reg register
#define ALL(x) (x).begin(),(x).end()
#define ln std::puts("")
#define lsp std::putchar(32)
#define pb push_back
template <class t> inline void read(t &s){s=0;
reg int f=1;reg char c=getchar();while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
while(isdigit(c))s=(s<<3)+(s<<1)+(c^48),c=getchar();s*=f;return;}
template<class t,class ...A> inline void read(t &x,A &...a){read(x);read(a...);}
template <class t> inline void write(t x){if(x<0)putchar('-'),x=-x;
int buf[21],top=0;while(x)buf[++top]=x%10,x/=10;if(!top)buf[++top]=0;
while(top)putchar(buf[top--]^'0');return;}
const int MaxN=1e5+50;
int a[MaxN],b[MaxN],S[MaxN],top,n,m;
signed main(void)
{
	read(n,m);
	reg int x;
	for(int i=1;i<=n;++i)read(x),++a[x];
	for(int i=1;i<=n;++i)read(x),++b[x];
	std::vector<int> ans;
	for(int i=0;i<m;++i)
	{
		while(a[i]--)S[++top]=i;
		while(b[m-i-1]&&top)ans.pb(S[top--]+m-i-1),--b[m-i-1];
	}
	for(int i=m-1;~i;--i)while(b[i]&&top)ans.pb(S[top--]+i-m),--b[i];
	std::sort(ALL(ans)),std::reverse(ALL(ans));
	for(auto i:ans)write(i),lsp;ln;
	return 0;
}
```



---

## 作者：TruchyR (赞：0)

讲个笑话，有人又不会证贪心。  

观前提醒：

- 本题解记录了我对这一题的全部思考过程。  
- 所以介绍的是是冗长的 $O(n\log^2{m})$ 的做法，更简洁的做法见另一篇题解。  

分别开两个数组 $a$ 和 $b$，$a_i$ 与 $b_i$ 分别代表 $A$ 与 $B$ 中对 $m$ 取模余 $i$ 的数的数量。  

要求字典序最大，所以考虑从大往小枚举配对的值 $p$，尽可能地配对。  

列一个表格 $T$，$T_{i,j}$ 代表 $p=i$ 时 $a_j$ 与 $b_{T_{i,j}}$ 匹配。  

- 上方是 $i$ 的值，左侧是 $j$ 的值。

![](https://cdn.luogu.com.cn/upload/image_hosting/4wmca9bb.png)

发现了一些神秘的规律。  

如果将 $b$ 反转，那么 $T_{i,j}=(j-i-1)\bmod{m}$，此式在从大往小枚举的时候更好推。  

至此，我们可以打出一份最坏 $O(nm)$ 的代码。  

如何优化？  

下文记迭代为 $p\rightarrow p-1$。

由于总共配对次数只有 $n$ 次，可以考虑记录每个 $a_i$ 下一次配对还需要几次迭代，记为 $Next_i$。  

 - 这里 $a_i$ 配对的要求是 $a_i>0$ 且 $b_{T_{p,i}}>0$。

考虑用线段树维护 $b$ 和 $Next$：

 - $b$ 支持单点修改，区间查询最大值。  
 - $Next$ 支持全局修改，区间查询最小值；如果 $a_i=0$，则 $Next_i=\inf$。

可以设计出配对过程如下： 

 - 如果 $\min_{i=0}^{m-1} Next_i>0$，进行一次迭代并将 $Next$ 全局减去 $1$。  
 - 否则通过二分找到一个满足 $Next_i=0$ 的整数 $i$，记 $j=T_{p,i}$。  
 - $a_i\rightarrow a_i-1$，$b_j\rightarrow b_j-1$。  
 - 通过二分，找到 $b$ 中从 $b_j$ 开始往后和往前连续的最多的 $0$。  
 - 往后的 $0$ 的个数是要更新的数值，往前的 $0$ 对应**回**的位置是要更新的位置。  
 - 若没有在线段树上二分，时间复杂度 $O(n\log^2 m)$。

AC 代码：  

 - 代码中 $a$ 和 $b$ 的大小写颠倒。  
 - 部分实现与上文略有不同。  

```cpp
#include<bits/stdc++.h>
#define int long long
#define INF 1000000000
#define MX 100005
using namespace std;int read();
int n,m,a[MX],b[MX],c,d,e;
class SegmentTree{
    public:
    int t[MX*4],lazy[MX*4];
    void build(int k,int l,int r){
    	if(l==r){t[k]=b[l];return;}
    	int mid=(l+r)>>1;
    	build(k*2,l,mid);
    	build(k*2+1,mid+1,r);
    	t[k]=max(t[k*2],t[k*2+1]);
    }
    void add(int k,int v){lazy[k]+=v;t[k]+=v;}
    void pd(int k){
    	if(!lazy[k]){return;}
    	add(k*2,lazy[k]);
    	add(k*2+1,lazy[k]);
        lazy[k]=0;
    }
    int sumN(int k,int l,int r,int x,int y){
    	if(x<=l && y>=r){return t[k];}
    	int mid=(l+r)>>1,ans=INF;pd(k);
    	if(x<=mid) ans=min(ans,sumN(k*2,l,mid,x,y));
    	if(y>mid) ans=min(ans,sumN(k*2+1,mid+1,r,x,y));
    	return ans;
    }
    int sumX(int k,int l,int r,int x,int y){
    	if(x<=l && y>=r){return t[k];}
    	int mid=(l+r)>>1,ans=-1;pd(k);
    	if(x<=mid) ans=max(ans,sumX(k*2,l,mid,x,y));
    	if(y>mid) ans=max(ans,sumX(k*2+1,mid+1,r,x,y));
    	return ans;
    }
    void changeN(int k,int l,int r,int x,int y,int v){
    	if(x<=l && y>=r){add(k,v);return;}
    	int mid=(l+r)>>1;pd(k);
    	if(x<=mid) changeN(k*2,l,mid,x,y,v);
    	if(y>mid) changeN(k*2+1,mid+1,r,x,y,v);
        t[k]=min(t[k*2],t[k*2+1]);
    }
    void changeX(int k,int l,int r,int x,int y,int v){
    	if(x<=l && y>=r){add(k,v);return;}
    	int mid=(l+r)>>1;pd(k);
    	if(x<=mid) changeX(k*2,l,mid,x,y,v);
    	if(y>mid) changeX(k*2+1,mid+1,r,x,y,v);
        t[k]=max(t[k*2],t[k*2+1]);
    }
};SegmentTree Next,B;
int check(int L,int j){
	int R=L+j;
	if(R<=m) return B.sumX(1,1,m,L,R);
	else return max(B.sumX(1,1,m,L,m),B.sumX(1,1,m,1,R-m));
}
int check2(int R,int j){
	int L=R-j;
	if(L>=1) return B.sumX(1,1,m,L,R);
	else return max(B.sumX(1,1,m,L+m,m),B.sumX(1,1,m,1,R));
}
signed main(){
	n=read();m=read();
	for(int i=1;i<=n;i++) a[read()+1]++; 
	for(int i=1;i<=n;i++) b[m-read()]++; B.build(1,1,m);
	for(int i=1;i<=m;i++){
		if(!a[i]) Next.changeN(1,1,m,i,i,INF);
		else{
			int l=0,r=m;
			while(l<r){
				int mid=(l+r)>>1;
				if(check(i,mid)) r=mid;
				else l=mid+1;
			}
			Next.changeN(1,1,m,i,i,l);
		}
	}
	int py=0;
	for(int i=1;i<=n;i++){
		if(Next.t[1]){
			Next.changeN(1,1,m,1,m,-1);
			i--,py++;continue;
		}
		printf("%lld ",m-1-py);
		int l=1,r=m;
		while(l<r){
			int mid=(l+r)>>1;
			if(Next.sumN(1,1,m,1,mid)) l=mid+1;
			else r=mid;
		}
		int j=r+py;if(j>m) j-=m; 
		a[r]-=1;B.changeX(1,1,m,j,j,-1);
		if(!B.sumX(1,1,m,j,j)){
			int L=0,R=m;
			while(L<R){
				int mid=(L+R+1)>>1;
				if(check(j,mid)) R=mid-1;
				else L=mid;
			}
			int addW=L+1;
			L=0,R=m;
			while(L<R){
				int mid=(L+R+1)>>1;
				if(check2(j,mid)) R=mid-1;
				else L=mid;
			}
			int st=r-L;
			if(st>=1) Next.changeN(1,1,m,st,r,addW);
			else{Next.changeN(1,1,m,1,r,addW);Next.changeN(1,1,m,st+m,m,addW);}
		}
		if(!a[r]) Next.changeN(1,1,m,r,r,INF);
	}
	return 0;
}
int read(){
	int Ca=0;char Cr=' ';int Cf=1;
	while(Cr<'0' || Cr>'9'){Cr=getchar();if(Cr=='-'){Cf=-1;}}
	while(Cr>='0' && Cr<='9'){Ca=Ca*10+Cr-48;Cr=getchar();}
	return Ca*Cf;
}
```

---

