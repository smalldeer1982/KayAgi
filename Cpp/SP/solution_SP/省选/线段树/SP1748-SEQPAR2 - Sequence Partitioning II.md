# SEQPAR2 - Sequence Partitioning II

## 题目描述

Given a sequence of _N_ ordered pairs of positive integers (_A $ _{i} $_ , _B $ _{i} $_ ), you have to partition it into several contiguous parts. Let _p_ be the number of these parts, whose boundaries are (_l_ $ _{1} $ , _r_ $ _{1} $ ), (_l_ $ _{2} $ , _r_ $ _{2} $ ), ... ,(_l $ _{p} $_ , _r $ _{p} $_ ), which satisfy _l $ _{i} $_ = _r $ _{i-} $_  $ _{1} $ + 1, _l $ _{i} $_ <= _r $ _{i} $_ , _l_ $ _{1} $ = 1, _r $ _{p} $_ = _n_. The parts themselves also satisfy the following restrictions:

1. For any two pairs (_A $ _{p} $_ , _B $ _{p} $_ ), (_A $ _{q} $_ , _B $ _{q} $_ ), where (_A $ _{p} $_ , _B $ _{p} $_ ) is belongs to the _T $ _{p} $_ th part and (_A $ _{q} $_ , _B $ _{q} $_ ) the _T $ _{q} $_ th part. If _T $ _{p} $_ < _T $ _{q} $_ , then _B $ _{p} $_ > _A $ _{q} $_ .
2. Let _M $ _{i} $_  be the maximum _A_-component of elements in the _i_th part, say
  
  _M $ _{i} $_  = max {_A $ _{li} $_ , _A $ _{li+} $_  $ _{1} $ , ..., _A $ _{ri} $_ }, 1 <= _i_ <= _p_
  
  it is provided that
  
  ![](../../content/crazyb0y:SEQPAR2_1.bmp)  
   where Limit is a given integer.

Let _S $ _{i} $_  be the sum of _B_-components of elements in the _i_th part.

Now I want to minimize the value

max{_S $ _{i} $_ :1 <= _i_ <= p}

Could you tell me the minimum?

## 样例 #1

### 输入

```
4 6
4 3
3 5
2 5
2 4```

### 输出

```
9```

# 题解

## 作者：xiaolilsq (赞：4)

[题目链接](https://www.luogu.com.cn/problem/SP1748)

首先，我们看一下题目要求：

第一个要求，可以比较简单地实现，若$B_i<A_j(i<j)$，则$i$和$j$必须分为同一个部分，此时我们可以把$i$到$j$范围内的所有数对进行合并，使之成为

$$(max(A_{i...j}),\sum_{k=i}^{j}B_k)$$

我们可以注意到，这样是不会影响后面关于每部分$A$的最大值的总和的计算和$B$的总和的计算，而合并操作只需一个栈即可完成，时间复杂度$O(n)$

读者可自行思考如何操作，也可参考以下代码（代码不作过多解释）：


```cpp
#define pll pair<long long,long long>
pll q[50005];
long long mn[50005];
void read(void){
	int t=0;
	while(n--){
		long long a,b;
		read(a),read(b);
		if(t==0||a<mn[t-1]){
			if(t!=0)mn[t]=mn[t-1];
			else mn[t]=LL_MAX;
			mn[t]=min(mn[t],b);
			q[t++]=pll(a,b);
		}
		else{
			long long MN=min(mn[t-1],b),A=a,B=b;
			while(t>0&&a>=mn[t-1]){
				A=max(A,q[t-1].first);
				B=B+q[t-1].second;
				--t;
			}
			mn[t]=MN;
			q[t++]=pll(A,B);
		}
	}
}
```

第一个要求实现了，关键是第二个要求，令$M_i$为第$i$部分$A$的最大值，$S_i$为第$i$部分$B$的总和，要在$\sum M_i<=limit$的前提下要求$max(S_i)$最小

题意有点长，要仔细理解才行

首先想到暴力，我们可以记录当前的$\sum M$和$max(S)$来进行下一步递归，这时可自然而然地想到记录转移，然后再$dp$一波

~~你当我傻吗，limit的范围这么大？？？~~

~~可以用map啊~~

怎么办？

我们反过来考虑一下，如果告诉你$max(S_i)$，可能可以比较方便地求出$min(\sum M_i)$，由于答案满足单调性，我们便想到二分答案

我们先二分出一个$max(S_i)$，此时题目就变为：有$N$对有序正整数对，给定一个数$max(S_i)$，将这些正整数对分为几段，判断在每段的$\sum B$小于等于$max(S_i)$的情况下能否使得每段最大的$A$之和小于$limit$

我们可以想到用$dp$去实现，记$dp_i$表示前$1...i$已经分好，能达到的最小的$\sum max(A)$，不难想出以下转移方程：

$$dp_i=min(dp_j+max(A_{j+1...i}))(j<i\&\&\sum_{k=j+1}^iB_k<=S_i)$$

复杂度$O(n^2)$，最后返回值为$dp_n<=limit$

太好了，这样我们就可以将时间复杂度降为$O(n^2log_2limit)$

~~可还是不能过啊~~

没关系，再次考虑优化$dp$，看到这个转移方程，我想到了另一道题：[POJ 3017 Cut the Sequence](http://poj.org/problem?id=3017)

题意就是给你$n$个数和一个$limit$，要求将这$n$个数分为几段，使得每段总和不大于$limit$，求每段的最大值的总和最小为多少

是不是和这题很像，简直一模一样，大家可以去看看这题题解，也可参考以下分析

首先我们可以发现$dp_i$是不严格单调递增的，即有$dp_j<=dp_i(j<i)$（为什么？），所以如果$max(A_{k+1...i})=max(A_{j+1...i}),k<j$，则我们一定会用$dp_k$去转移，即在满足$max(A)$相等的情况下，我们会选尽量靠前的，于是我们便考虑用单调队列维护一个单调递减的$A$，再用一个指针指向最往前能到哪儿来判断队列中的数是否满足条件，则当前的$dp_i$只会由$dp_{q[k]}+A_{q[k+1]}$（记$q$为单调队列）和$dp_{ad}+A_{q[head]}$（记$ad$为最左端的指针）转移过来（为什么？），可以用堆和平衡树实现，堆只需每次取堆顶时判断是否满足条件即可，平衡树即可在弹出时删除即可（当然手写的堆也可删除）

读者可自行思考，可参考以下代码（平衡树）：

```cpp
struct forgirl{
	long long A,B;
}x[50005];
int num;
long long dp[50005],limit,fl[50005];
multiset<long long>s;
bool judge(long long now){
	s=multiset<long long>();
	int ad=0,head=0,tail=0;//清空 
	for(int i=1;i<=num;++i){
		while(ad<i&&x[i].B-x[ad].B>now)++ad;//最左端的指针 
		if(ad==i)return 0;//不可能满足要求 
		while(head<tail&&fl[head]<=ad){
			if(head+1<tail){
				s.erase(dp[fl[head]]+x[fl[head+1]].A);
			}++head;
		}//队首弹出 
		while(head<tail&&x[fl[tail-1]].A<=x[i].A){
			if(head+1<tail){
				s.erase(dp[fl[tail-2]]+x[fl[tail-1]].A);
			}--tail;
		}//队尾弹出 
		fl[tail++]=i;
		if(head+1<tail)
			s.insert(dp[fl[tail-2]]+x[fl[tail-1]].A);
		dp[i]=dp[ad]+x[fl[head]].A;
		if(head+1<tail){
			dp[i]=min(dp[i],*s.begin());//转移 
		}
	}
	return dp[num]<=limit;
}
```
堆优化：

```cpp
#define pii pair<int,int>
struct forgirl{
	long long A,B;
}x[50005];
long long dp[50005],fl[50005],limit;
int ok[50005],num;
struct cmp{
	bool operator () (const pii a,const pii b)const{
		return dp[a.first]+x[a.second].A>dp[b.first]+x[b.second].A;
	}
};
priority_queue<pii,vector<pii>,cmp>s;
bool judge(long long now){
	s=priority_queue<pii,vector<pii>,cmp>();
	memset(ok,0,sizeof ok);
	int ad=0,head=0,tail=0;
	for(int i=1;i<=num;++i){
		while(ad<i&&x[i].B-x[ad].B>now)++ad;
		if(ad==i)return 0;
		while(head<tail&&fl[head]<=ad)ok[fl[head++]]=false;
		while(head<tail&&x[fl[tail-1]].A<=x[i].A)ok[fl[--tail]]=false;
		fl[tail++]=i;ok[i]=true;
		if(head+1<tail)s.push(pii(fl[tail-2],fl[tail-1]));
		dp[i]=dp[ad]+x[fl[head]].A;
		if(!s.empty()){
			pii temp=s.top();
			while(!s.empty()&&(!ok[temp.first]||!ok[temp.second])){
				s.pop();
				if(!s.empty())
					temp=s.top();
			}
			if(!s.empty()){
				dp[i]=min(dp[i],dp[temp.first]+x[temp.second].A);
			}
		}
	}
	return dp[num]<=limit;
}
```


附上$AC$代码：

```cpp
#include<iostream>
#include<set>
#include<cstring>
#include<cstdio>
#include<algorithm>
#define pll pair<long long,long long>
#define LL_MAX 1e14+7
using namespace std;
template<typename T>void read(T &x){
	x=0;int f(1);char c(getchar());
	for(;!isdigit(c);c=getchar())if(c=='-')f=-f;
	for(; isdigit(c);c=getchar())x=(x<<3)+(x<<1)+c-'0';
	x*=f;
}
template<typename T>void write(T x){
	if(x<0)putchar('-'),x=-x;
	if(x/10)write(x/10),x=x%10;
	putchar(x+'0');
}
struct forgirl{
	long long A,B;
}x[50005];int num;
long long mn[50005],dp[50005],limit,fl[50005];
pll q[50005];multiset<long long>s;
bool judge(long long now){
	s=multiset<long long>();
	int ad=0,head=0,tail=0;//清空 
	for(int i=1;i<=num;++i){
		while(ad<i&&x[i].B-x[ad].B>now)++ad;//最左端的指针 
		if(ad==i)return 0;//不可能满足要求 
		while(head<tail&&fl[head]<=ad){
			if(head+1<tail){
				s.erase(dp[fl[head]]+x[fl[head+1]].A);
			}++head;
		}//队首弹出 
		while(head<tail&&x[fl[tail-1]].A<=x[i].A){
			if(head+1<tail){
				s.erase(dp[fl[tail-2]]+x[fl[tail-1]].A);
			}--tail;
		}//队尾弹出 
		fl[tail++]=i;
		if(head+1<tail)
			s.insert(dp[fl[tail-2]]+x[fl[tail-1]].A);
		dp[i]=dp[ad]+x[fl[head]].A;
		if(head+1<tail){
			dp[i]=min(dp[i],*s.begin());//转移 
		}
	}
	return dp[num]<=limit;
}
int main(){ 
//	freopen("forgirl.in","r",stdin);
//	freopen("forgirl.out","w",stdout);
	int n;read(n),read(limit);
	int t=0;
	while(n--){//合并 
		long long a,b;
		read(a),read(b);
		if(t==0||a<mn[t-1]){
			if(t!=0)mn[t]=mn[t-1];
			else mn[t]=LL_MAX;
			mn[t]=min(mn[t],b);
			q[t++]=pll(a,b);
		}
		else{
			long long MN=min(mn[t-1],b),A=a,B=b;
			while(t>0&&a>=mn[t-1]){
				A=max(A,q[t-1].first);
				B=B+q[t-1].second;
				--t;
			}
			mn[t]=MN;
			q[t++]=pll(A,B);
		}
	}
	long long r=0,l=0;
	while(t){
		++num;
		x[num].A=q[t-1].first;
		x[num].B=q[t-1].second;
		l=max(l,x[num].B);
		r=r+x[num].B;
		x[num].B+=x[num-1].B;//前缀和优化 
		--t;
	}
	while(l+1<r){//二分 
		long long mid=l+r>>1;
		if(judge(mid)){
			r=mid;
		}
		else{
			l=mid;
		}
	}
	if(judge(l))write(l);
	else write(l+1);
	putchar('\n');
	return 0;
}
```

这一题很好地把$dp$隐藏在二分答案里，是一道很考验能力的题

---

