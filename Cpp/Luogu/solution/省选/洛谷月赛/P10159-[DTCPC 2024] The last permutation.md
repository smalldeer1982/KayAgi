# [DTCPC 2024] The last permutation

## 题目背景

**本题题目背景不均为虚构，不影射任何人**。

小 L 是小 L 初中时的白月光。

有一天，小 L 在朋友圈说要玩农，小 L 火速研究怎么下载王者。

第二天，小 L 在朋友圈说要玩吃鸡，小 L 火速研究怎么下载 pubg。

但小 L 很快就和小 L 分手了，小 L 最后的情思化作一个排列。遗憾的是，小 L 并不情愿告诉大家。

不过在你的不断追问下，小 L 还是同意回答几个关于排列的问题。

## 题目描述

现存在一个长度为 $n$ 的隐藏排列 $p$。你可以进行如下询问若干次：选择三元组 $(l,r,k)$，满足 $1\leq l\leq r\leq n$，$1\leq k\leq r - l + 1$，交互库会返回下标在 $[l,r]$ 内的第 $k$ 大值。

对于一次询问操作，其代价为 $\frac{1}{r-l+1}$，你需要在不超过 $11.8$ 的代价内得出排列。

交互库不自适应，也就是说，你所需得到的排列在交互开始前就已经确定。

## 样例 #1

### 输入

```
1
5

2

3

1

4

```

### 输出

```


? 1 1 1

? 2 2 1

? 3 3 1

? 4 4 1

! 2 3 1 4 5```

# 题解

## 作者：Cocoly1990 (赞：2)

官方题解

考虑从序列从前向后确定每个值，对 $[1,i-1]$ 二分 $rank$ 可以得到 $i$，代价为 $\sum \frac{1}{i}\log i$，代价大约 $34$。

考虑值域从大到小确定每个值，当求出前 $x$ 大时，很容易设计一个比较器，使得在一次询问内求出区间 $[l,r]$ 内是否包含第 $x+1$ 大。

一个有趣的发现：将序列分两份，我们可以用一次询问来确定 $x$ 在序列的左侧还是右侧，之后每次二分的时候我们都保证了询问区间长度 $>\frac{n}{2}$。

这样可以容易做到 $n\times \frac{2}{n}\times (\log n+1)$。大约是 $22$ 次。

考虑结合两个做法，把序列分两段，用 $1$ 的代价确定两块的构成，然后运用做法一，可以做到 $\sum \frac{1}{\max\{i,n-i\}}\log i$，大约是 $14$ 次。

还能不能再给力一点！注意到 $\log i$ 实现的精细一点可以做到 $\log \min\{i,n-i+1\}$，这样理论分析就可以做到 $<11.8$ 次。

经过构造可以把标算卡到基本满。

---

## 作者：waauto (赞：2)

[题目链接](https://www.luogu.com.cn/problem/P10159)

提供一个随机扰动下复杂度一定正确的简单做法。

首先考虑一个 trivial 的操作。

我们想要求出一个点 $a_n$，我们可以先对答案二分，然后 check 一下 $[1,n-1]$ 这个区间的该排名，就可以知道是否大了或者小了，从而收敛上下界，可以二分，依次确定每一位，消耗次数 $\sum\frac{\log(n-i)}{i}$ 显然不行。

我们考虑一个更加厉害的操作。

我们发现次数瓶颈在于后面需要消耗的次数实在是太多了。

于是我们可以在询问 $[1,\frac{n}{2}]$ 的时候考虑用后面那段区间进行二分，例如询问 $a_1$ 的时候使用 $[2,n]$ 即可。

这个时候你直接拍一个代码上去就已经可以 AC 了。

但是可以被卡掉，具体来说因为 $\sum\frac{\lceil\log_2 i\rceil}{max(i,n-i)}$ 大约是一个 $12.5$ 左右的东西，所以可以用卡二分的方式卡掉。

也就是说我们需要干掉这个 ceil 就行了，那么你在收敛两边区间长度不同的时候随机扰动一下，这样次数就对了，赢。

部分细节可以看看代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define S cerr << "SYT AK IOI" <<endl;
#define M cerr << "MKF AK IOI" <<endl;
#define CONNECT_BASE(x,y) x##y
#define CONNECT(x,y) CONNECT_BASE(x,y)
#define DEBUG_BASE(x) cerr<<#x<<'='<<x<<' '
#define DEB_1(x) DEBUG_BASE(x)
#define DEB_2(x,y) DEB_1(x),DEB_1(y)
#define DEB_3(x,y,z) DEB_1(x),DEB_2(y,z)
#define DEB_4(x,y,z,w) DEB_1(x),DEB_3(y,z,w)
#define DEB_5(a,b,c,d,e) DEB_1(a),DEB_4(b,c,d,e)
#define DEB_6(a,b,c,d,e,f) DEB_1(a),DEB_5(b,c,d,e,f)
#define COUNT_BASE(_1,_2,_3,_4,_5,_6,x,...) x
#define COUNT(...) COUNT_BASE(__VA_ARGS__,6,5,4,3,2,1,0)
#define D(...) std::cerr << "[In Line " << __LINE__ << "]: ",CONNECT(DEB_,COUNT(__VA_ARGS__))(__VA_ARGS__) , cerr << '\n'
#define NAME(x) #x
#define INNAME(x) NAME(x)
using ll=long long;
using lll=__int128;
using pii=pair<int,int>;
using uint=unsigned int;
using ull=unsigned long long;
mt19937 rd(0^(*new int));
//#define int long long                                             //use it if possible
#define pb(x) push_back(x)
#define F(i,a,b) for(int i=(a),i##end=(b);i<=(i##end);++i)
#define UF(i,a,b) for(int i=(a),i##end=(b);i>=(i##end);--i)
#define gc() getchar()
#define ret return
#define pc putchar
#define popcount(x) __builtin_popcount(x)

inline void init();
inline void IO();
const int N=1005;
int a[N],n;
bool del[N];
inline void out(){
	cout<<"! ";F(i,1,n)cout<<a[i]<<" ";
	cout<<endl;
}
vector<int>v;
int unsolve;
inline bool ck(int to,int pos){
	int rk=n-to+1;
	if(pos<=n/2){
		F(i,1,pos-1)if(a[i]>to)--rk;
		
		cout<<"? "<<pos+1<<" "<<n<<" "<<rk<<endl;
		int qwq;
		cin>>qwq;
		//		D(to,qwq);
		ret qwq==to;
	}
	else {
		UF(i,n,pos+1)if(a[i]>to)--rk;
		cout<<"? "<<1<<" "<<pos-1<<" "<<rk<<endl;
		int qwq;
		cin>>qwq;
		ret qwq==to;
	}
}
inline void solve(int x){
	//	D(x);
	if(v.size()==2){
		a[x]=v[1];
		--unsolve;
		ret;
	}
	int l=1,r=unsolve;
	int ans;
	while(r>=l){
		int mid=(l+r+(rd()%2))>>1;
		if(l==r)mid=l;
		if(mid==unsolve and l==r){
			a[x]=v[unsolve];
			--unsolve;
			v.pop_back();
			ret;
		}
		else if(mid==unsolve)--mid;
		if(ck(v[mid],x)){
			l=mid+1;
		}
		else r=mid-1,ans=mid;
	}
	//	ans=l;
	//	D(v.size(),unsolve,ans);
	if(ans-1>v.size())while(1);
	a[x]=v[ans];
	//	D(x,a[x]);
	v.erase(v.begin()+ans);
	unsolve--;
}
inline void mian(){
	memset(a,0,sizeof(a));
	memset(del,0,sizeof(del));
	//	memset(p,0,sizeof(p));
	cin>>n;
	v.clear();
	v.push_back('0');
	unsolve=n;
	UF(i,n,1)v.push_back(i);
	
	F(i,1,n){
		if(i&1)solve(i/2+1);
		else solve(n-(i/2)+1);
	}
	out();
}
signed main(){
	//	cin.tie(nullptr)->sync_with_stdio(false);
	int T=1;
#define multitest 1
#ifdef multitest
	cin>>T;
#endif
//	IO();
	init();
	
	while(T--)mian();
	return 0;
}


inline void init(){
	
}
//#define FILEIO data
inline void IO(){
#ifdef FILEIO
	freopen(INNAME(FILEIO)".in","r",stdin),freopen(INNAME(FILEIO)".out","w",stdout);
#endif
}
```

---

