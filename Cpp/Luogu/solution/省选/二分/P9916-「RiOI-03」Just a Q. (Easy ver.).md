# 「RiOI-03」Just a Q. (Easy ver.)

## 题目背景

「Yes, I am Q.」

面前的小 R 莞尔一笑。

+ 保证本题的任何合理的部分分或正解的 std + spj 均可以在当前数据下，$400$ ms 的时间限制、$32$ MB 的空间限制内正确运行并获得 AC 状态。
+ 本题不添加仅为无意义地卡满 spj 运行时间的 hack 数据。

**请注意，本题只有约束范围与困难版不同，且两个版本的约束范围并不完全重叠。**

## 题目描述

**这是一道交互题。**

小 R 有一个变量 $Q$。$Q$ 初始为 $0$。

小 R 有 $n$ 个隐藏的整数 $q_1 \dots q_n$，满足 $1 \leq \lvert q_i \rvert \leq V$，且有且仅有一个 $i$ 满足 $q_i \lt 0$，而面前的你，需要得出这个满足 $q_i \lt 0$ 的下标 $i$。

小 R 承诺不会让你以仅仅 $\frac{1}{n}$ 的几率盲猜，所以她可以允许你进行最多 $k$ 次询问。每次询问，你可以向小 R 给出**可重**正整数集合 $S$ 满足 $0 \leq \lvert S \rvert \leq S_{\max}$ 且 $\forall i \in S, i \leq n$，她会计算 $M = \prod\limits_{i\in S}q_i$，然后让 $Q \leftarrow Q + M$。特殊地，若 $S$ 为空集，则 $M = 1$。

一次询问后，小 R 会向你给出此时的 $\text{sgn}(Q)$（为 `+`，`-` 或 `0`），表示 $Q$ 的符号。具体地，若 $Q \gt 0$，小 R 返回 `+`；若 $Q \lt 0$，小 R 返回 `-`；否则返回 `0`。

请你在不超过 $k$ 次询问后，找到那个满足 $q_i \lt 0$ 的下标 $i$。

**保证对于所有数据，满足 $q_i \lt 0$ 的下标 $i$ 是在 $[1, n]$ 内均匀随机选取的。请注意报告下标属于一次询问。**

## 说明/提示

### 样例解释 1

$q = \{-1, 1, 4, 5, 1, 4\}$。

### 数据规模与约定

**本题采用捆绑测试。**

+ Subtask 0（5 pts）：$q_i \neq 1$ 且 $q_i \neq -1$。
+ Subtask 1（10 pts）：$q_i \neq -1$，$k = 2n$。
+ Subtask 2（10 pts）：$q_i \neq 1$，$k = 2n$。
+ Subtask 3（9 pts）：$n = 13$，$k = 5000$。
+ Subtask 4（11 pts）：$n = 13$，$k = 2500$。
+ Subtask 5（20 pts）：$k = 2n$。
+ Subtask 6（35 pts）：无特殊限制。

对于每组数据，$1 \leq n \leq 200$，$1 \leq V \leq 10^6$，$n \leq k \leq 5\times 10^3$，$S_{\max} = n$。

对于每个测试点，$1 \leq T \leq 500$，$\sum n^2 \leq 2\times 10^5$，$\sum k \leq 2\times 10^5$。

## 样例 #1

### 输入

```
1
6 6 6

-

-

-

+

0


```

### 输出

```


? 1 1

? 5 1 2 3 4 5

? 3 2 4 6

? 1 4

? 3 1 5 6

! 1```

# 题解

## 作者：FFTotoro (赞：13)

## 前言

Div.2 Rank $13$ 获奖了，题目也好评。

## 解法

从 Subtask $3$ 出发，考虑构造 $\prod(a_i+1)$ 这种形式，因为它可以便利地在加入一个新数维护当前乘积的正负性，进而推出该数的正负性；加入一个新数时只需枚举遍历过的每一个子集，对该子集加入该数后形成的集合作询问并存储，可以过 Subtask $3$。如果把 $a_1+1$ 换成 $a_1$（即一开始不询问那个空集）那么就能把询问次数除以 $2$，可以过 Subtask $4$。

正解需要一个 trick：先前一个一个数的做法询问次数很多，考虑把一些数一起询问。具体地，使用二分，令 $m$ 为二分中点，每次将 $q_{[l,m)}$（这里 $m=\left\lceil\frac{l+r}{2}\right\rceil$）绑在一起进行询问。如果 $Q=0$，那么仿照上面 Subtask $4$ 对 $a_1$ 的处理方法把当前集合清空并仅加入 $[l,m)$，正负性直接询问；否则考虑这一段的乘积正负性只需将其询问的最终结果的符号 $\mathrm{sgn}(Q')$ 与上一次的结果的符号 $\mathrm{sgn}(Q)$ 比较，如果相同则这一段乘积为正，否则为负。

原来的集合可以用 `std::vector` 存储 `std::pair` 实现。

放代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
char ask(vector<pii> a){
  vector<int> v; char c;
  for(auto [l,r]:a)
    for(int j=l;j<=r;j++)
      v.emplace_back(j);
  cout<<"? "<<v.size()<<' ';
  for(int i:v)cout<<i<<' ';
  cout<<endl,cin>>c;
  return c;
} // 单次询问
int main(){
  ios::sync_with_stdio(false);
  int t; cin>>t;
  while(t--){
    int n,k; cin>>n>>k>>n;
    int l=1,r=n; bool f=true; char s='+';
    vector<vector<pii> > a;
    while(l<r){
      int m=l+r+1>>1; char c;
      if(f){
        s='+',a={{make_pair(l,m-1)}};
        c=ask(a[0]),f=false;
      } // Q=0 时
      else{
        vector<vector<pii> > b;
        for(auto i:a){
          vector<pii> v=i;
          v.emplace_back(l,m-1);
          b.emplace_back(v);
          c=ask(v);
        } // 遍历并询问
        a.insert(a.end(),b.begin(),b.end());
        // 将产生的新集合加入 a 中
      }
      if(c==s)l=m; // 贡献为正，负数在右
      else if(c==48)r=m-1,f=true;
      else s=c,r=m-1; // 贡献为非正数，负数在左
    }
    cout<<"! "<<l<<endl;
  }
  return 0;
}
```

---

## 作者：irris (赞：6)

枚举题意想出来的 adhoc。看到交互题先想二分。

因为我们的操作 **不会重置 $\bm Q$**，而且你也不知道 $Q$ 到底是啥，所以比起给 $Q$ 加上一个数，我们可能更偏向于 **给 $\bm Q$ 乘上一个数**。

但是 Subtask 3 & 4 非常有启发性。因为你看到 $k$ 是 $2^{n-1}$ 或者 $2^{n-2}$ 这样的形式，考虑如何 **在指数时间内** 给 $Q$ 乘上一个数。

事实上，我们可以时刻把 $Q$ 写成 $(a_1 + 1)(a_2 + 1)\dots(a_k + 1)$ 的形式。通过枚举 $1 \sim k$ 的每个子集再并上 $\{k + 1\}$，我们可以用 $2^k$ 的询问次数把 $Q$ 从 $(a_1 + 1)(a_2 + 1)\dots(a_k + 1)$ 变为 $(a_1 + 1)(a_2 + 1)\dots(a_{k+1} + 1)$，**它的高妙之处就在于把前面加上去的信息当做最后 $\bm Q$ 因式分解结果的一个 $\bm{1\times}$ 项**。如果某一次结束后（注意需要读取中间的冗杂信息）$Q$ 是非正数，那么可以直接断定上一个乘上去的因式 $\leq 0$，输出这个数即可。直接暴力做 $k = 2^n$，但是注意到如果答案不在 $1 \sim (n - 1)$ 内那就是 $n$，所以可以 $k = 2^{n-1}$ 拿到 $9$ 分。

接着优化，我们发现 $(a_1 + 1)$ 的 $+1$ 毫无必要，初始不需要询问任何空集。所以可以 $k = 2^{n-2}$ 拿到 $9 + 11 = 20$ 分。

Subtask 5 是给那些 $k = 2^{n-1}$ 而非 $k = 2^{n-2}$ 的人留的。Subtask 1, 2 也可以同时通过，其实我不知道这两个包怎么乱搞。

$20$ 分做法是一个巨大的浪费，因为每次只判定 $1$ 个数，并且没有利用可重集的条件。想到我们每次可以判定若干个数，把它们的乘积 **看做一个整体** 再套用之前的做法即可。所以可以二分这个数所在的位置范围。注意如果 $Q$ 变成 $0$ 了需要重置一下。

因此，最大交互次数不大于 $2^{\lceil\log_2 n\rceil - 1} \leq n$，最大集合大小不大于 $n$，可以获得满分。注意集合大小这里需要好好考虑。

```cpp
void rec_solve(int l, int r, int ped = 1) {
	if (l == r) return (void)(std::cout << "! " << l << std::endl);
	int mid = l + r - 1 >> 1;
	Cl[ped] = l, Cr[ped] = mid, len[ped] = mid - l + 1;
	if (ped == 1) sign = '+', std::cout << "? " << mid - l + 1 << ' ', fout(l, mid, true);
	for (int stat = 1; stat < (1 << ped - 1); stat += 2) {
		int tot = len[ped];
		for (int u = 1; u < ped; ++u) if ((stat >> u - 1) & 1) tot += len[u];
		std::cout << "? " << tot << ' ';
		for (int u = 1; u < ped; ++u) if ((stat >> u - 1) & 1) fout(Cl[u], Cr[u]);
		fout(Cl[ped], Cr[ped], true); if (stat + 1 != (1 << ped - 1)) res();
	}
	char t = res();
	if (t == sign) rec_solve(mid + 1, r, ped + 1);
	else if (t == '0') rec_solve(l, mid);
	else sign = t, rec_solve(l, mid, ped + 1);
}
```

---

## 作者：MaxBlazeResFire (赞：5)

来一个赛时想到，但没完全想到的一个不太一样的做法。

假设我们现在一个一个判定，给出一个构造：依次往 $Q$ 中加入 $a_1,2a_1a_2,4a_1a_2a_3,8a_1a_2a_3a_4,\cdots$，第一次出现 $<0$ 时，该数就是答案。

证明考虑数学归纳法：前 $i$ 个 $a$ 都是正数，$S_i=a_1(1+2a_2(1+2a_3(\cdots)))$ 为正数，而 $S_{i+1}$ 形如在 $S_i$ 最里层添加项 $1+2a_{i+1}$。来自如果该项发生突变，可以通过之前都是正数推得每个内嵌的括号内部都为非负数，说明 $a_{i+1}<0$。为什么要 $2$ 的系数？如果只有 $1$ 的系数的话，我们发现推几项只能依次得到括号内部 $\geq 0,\geq -1,\geq -2,\cdots$ 的弱结论，这显然是不够的。

这个构造消耗的询问次数很显然为 $2^t-1$，其中 $t$ 为项数。而最后一项不用检查，可以优化到 $2^{t-1}-1$。

注意到可以利用可重集的性质直接将一串数打包为一个新集合，从而我们可以构造新的检测序列 $a$，缩小 $t$ 来得到更优的解。具体来说，我们可以每次将待检查的区间从中间劈开，取一半数的乘积作为新的 $a$，并立即判定答案出现在区间的左侧或右侧。这样就可以做到 $O(n)$ 次询问，但是最坏情况下会有 $2n$ 次操作，因为 $t=2^{\lceil\log n\rceil}$，这个上取整直接让我们的梦想破灭，于是赛时死磕在 $60$ 分走不下去了。

赛后猛然发现，完全可以将构造改为 $a_1,a_1a_2,2a_1a_2a_3,4a_1a_2a_3a_4,\cdots$，只是在判定左右侧时额外加入一些细节，其它完全无伤大雅。询问数量砍掉一半，可以通过。

~~（赛时怎么就没想到呢？）~~ 

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,k,lst;
char s[2];

vector<int> S;

inline void Q(){ printf("? %d",(int)S.size()); for( int ele : S ) printf(" %d",ele); puts(""); fflush( stdout ); }

void conquer( int l , int r , int f , int rcnt ){
	if( l == r ){ printf("! %d\n",l); fflush( stdout ); return; }
	int mid = ( l + r ) >> 1;
	for( int i = mid + 1 ; i <= r ; i ++ ) S.emplace_back( i );
	for( int i = 1 ; i <= ( f == -1 ? 1 : ( 1 << f ) ) ; i ++ ) Q(),scanf("%s",s + 1);
	int cp = s[1] == '+' ? 1 : ( s[1] == '0' ? 0 : -1 );
	if( cp > lst || ( cp == lst && cp == 1 ) ){ lst = cp; if( rcnt == -1 ) conquer( mid + 1 , r , f + 1 , 1 ); else conquer( l , mid , f + 1 , 1 ); }
	else{ lst = cp; if( rcnt == 1 ) conquer( mid + 1 , r , f + 1 , -1 ); else conquer( l , mid , f + 1 , -1 ); }
}

inline void solve(){
	scanf("%d%d%d",&n,&k,&n);
	lst = 1; S.clear(); conquer( 1 , n , -1 , 1 );
}

signed main(){
	int testcase; scanf("%d",&testcase);
	while( testcase -- ) solve();
	return 0;
}
```

---

## 作者：听取MLE声一片 (赞：4)

验题人题解。

考虑到我们要在一个整个区间内找到一个负数，很自然想到二分。

设当前询问区间的左右端点分别为 $l$，$r$，$mid=\frac{l+r}{2}$。二分成两个区间 $[l,mid]$ 和 $[mid+1,r]$，分别称为左区间和右区间。设左区间的区间乘积为 $x$，考虑判断 $x$ 的符号来判断负数的位置。

我们知道区间内包含一个负数的充要条件是区间乘积为负，全是正数的充要条件是乘积为正，考虑通过这个性质来二分。

如果当前 $Q=0$，那么直接询问 $x$ 的正负性即可确定负数在左区间还是右区间。如果 $x$ 为负，则负数在左区间，反之在右区间。

所以问题就变成如何处理 $Q$ 在非零时的情况。

对于等式 $a\times b=c$，如果我们知道 $a$ 和 $c$ 的符号，那么我们就可以知道 $b$ 的符号。具体的，如果 $a$，$c$ 同号，则 $b$ 为正；如果 $a$，$c$ 异号，则 $b$ 为负。

这样，我们就可以通过类似于 $Q$ 乘上 $x$ 来确定 $x$ 的符号。

我们把之前询问的所有操作都再拼上一个当前询问左区间，那么这些的贡献就是 $Q\times x$。再加上原来就有的 $Q$，也就是 $Q'=Q+Q\times x=Q\times (x+1)$，我们可以查询 $Q'$ 的正负性。

已知 $Q$ 和 $Q'$ 的正负性，就可以推出 $x$ 的正负性了。

推断出 $x$ 的正负性就可以继续二分了。

另外的，如果 $Q'=0$，因为 $Q$ 非零，所以 $x+1=0$，这说明左区间为负，同时再按照 $Q=0$ 继续处理即可。

分析一下操作次数，第 $i$ 层的个数是前 $i-1$ 层的个数和。其中第 $1$ 层对应 $Q=0$，其个数为 $1$，所以前 $i$ 层的个数总和即为 $2^{i-1}$。

设 $t=\lceil \log_2 n \rceil$，最劣情况是层数卡满为 $t$，总操作数最大值即为 $2^{t-1}$。

对于操作集合，最大情况是每个二分区间都取到，打表发现这个值为 $n-1$。

```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
#include<queue>
#include<stack>
#include<vector>
#include<map>
#include<set>
#include<bitset>
#include<ctime>
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N=201;
void print(int l,int r,int fl=0){
	for(int i=l;i<=r;i++)cout<<i<<' ';
	if(fl)cout<<endl; 
}
char get(){
	char ch;
	cin>>ch;
	return ch;
}
int L[N],R[N],len[N],sum;
char sign;
vector<vector<int>>e,E;
int n,k,sm;
void push(vector<int>u){
	int sum=0;
	for(int v:u)
		sum+=len[v];
	cout<<"? "<<sum<<endl;
	for(int v:u)
		print(L[v],R[v]);
	cout<<endl;
}
void solve(int l,int r,int d){
	if(l==r){
		cout<<"! "<<l<<endl;
		return;
	}
	vector<int>ret;
	E.clear();
	int mid=(l+r-1)>>1;
	L[d]=l;
	R[d]=mid;
	len[d]=R[d]-L[d]+1;
	if(d==1){
		e.clear();
		ret.clear();
		ret.push_back(1);
		e.push_back(ret);
		cout<<"? "<<len[1]<<endl;
		print(L[1],R[1],1);
		sign=get();
		if(sign=='-')
			solve(l,mid,d+1);
		else solve(mid+1,r,d+1);
		return;
	}
	char ch;
	for(vector<int> u:e){
		u.push_back(d);
		E.push_back(u);
		push(u);
		ch=get();
	}
	for(vector<int> u:E)
		e.push_back(u);
	if(ch==sign){
		sign=ch;
		solve(mid+1,r,d+1);
		return;
	}
	if(ch=='0'){
		sign=ch;
		solve(l,mid,1);
		return;
	}
	sign=ch;
	solve(l,mid,d+1);
}
void Solve(){
	cin>>n>>k>>sm;
	solve(1,n,1);
}
int main()
{
	int T;
	cin>>T;
	while(T--)
		Solve();
	return 0;
}

// orz nrd

```

---

## 作者：Erica_N_Contina (赞：1)

## 思路

这里换一种说法讲解 MLE 的做法。

---

考虑二分判断。首先我们知道最优一个负数，那么我们就知道负数所在的那个区间的区间积为负。但是有一点不太好处理，就是 $Q$ 是在旧 $Q$ 上修改的，所以我们需要处理 $Q$ 的值的变化。

那么我们分类讨论。

- $Q=0$。

此时我们在当前查询的区间 $[l,r]$ 划分出 $mid$，直接查询 $[l,mid]$ 的区间积，如果 $Q<0$ 那么目标就是在 $[l,mid]$ 了；反之亦然。这样就可以缩小二分区间。

- $Q≠0$。

这个时候就有一点麻烦了。我们记 $Q_i$ 为之前进行的第 $i$ 次询问的结果（即那一次询问的区间积），那么就知道 $Q=\sum\limits_{T} Q_i$（$T$ 为当前查询的总次数）。那么假设我们现在要判断 $[l,mid]$ 中是否含有目标，怎么办呢？

我们知道，如果对于 $a\times b=c$，我们知道了 $a,c$ 的正负性，那么我们就知道了 $b$ 的正负性。

那么我们也发现一点——假设 $M<0,M = \prod\limits_{i\in[l,r]}q_i$，那么 $Q\times M$ 和 $Q$ 的正负相反。考虑乘法分配律，就可以是 $Q=\sum\limits_{T} (Q_i\times M)$。

于是设第 $i$ 次询问的集合为 $S_i$，那么我们重新对每一个 $i$ 询问一次 $S_i\cup [l,mid]$，这样就让 $Q_{T+1}=\sum\limits_{i\in[1,T]} (Q_i\times M+Q_i)=\sum\limits_{i\in[1,T]} (Q_i\times (M+1))=Q_T\times (M+1)$。

好了，对比 $Q_T$ 和 $Q_{T+1 }$ 的正负，现在我们知道了 $M+1$ 的正负性了，分类讨论：

- $M+1=0$，那么 $M<0$，下一步二分 $[l,mid]$ 区间。

- $M+1>0$，首先题目保证没有 $q_i=0$，所以 $M+1>1$，那么 $M>0$，下一步二分 $[mid+1,r]$ 区间。

- $M+1<0$，那么 $M<0$，下一步二分 $[l,mid]$ 区间。

所以这道题就愉快的写掉了。

---

代码和 MLE 的同，不放了。

---

## 作者：Wf_yjqd (赞：0)

要是直接给出每次询问结果就好了，直接二分即可。

要是给的是询问的结果的乘积就好了，只需要记录一下符号的变化，还是一样做。

---

好吧于是她给了询问结果的和（的正负号）。

尝试继承上面想象中的做法，那么我们只能将加法转化为乘法。

这好像并不难，由于没法直接相乘，考虑求每个集合的乘积 $+1$ 的乘积。

直接展开，此处应有演草。

可以得出，每次新增一个集合求乘积时，都需要枚举先前每个集合所在的式子中与 $1$ 相乘还是与集合乘积相乘，那么第 $k$ 个集合所需询问次数为 $2^{k-1}$。

这里写一下式子或许更好理解？假设第 $i$ 个集合的乘积为 $a_i$，则前 $i$ 个集合后我们希望得到的 $Q_i=\prod\limits_{j=1}^i(a_j+1)$。

将相邻两项求差 $Q_i-Q_{i-1}=a_i\times\prod\limits_{j=1}^{i-1}(a_j+1)$。

所以询问方案显然，枚举先前每个集合是否统计即可。这就是题目允许询问有重复元素的集合的原因。

考虑能否二分解决，显然通过记录正负号变化，先前的区间不会产生影响。

而二分最坏层数为 $\lceil\log_2n\rceil$，所以还需要一些卡常。

发现我们统计第一个集合时，并不需要考虑前面剩下的 $Q$，所以不需要 $+1$，于是最坏询问次数降到了 $n$ 以内（等比数列求和可知）。

式子影响不大就不重推了。

---

注意若过程中出现 $Q=0$ 的情况需要特判符号变化。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+26;
int T,n,ql[maxn],qr[maxn],qtop,S,st[maxn],top;
char s[26];
inline int Query(){
	if(qtop==1){
		printf("? %d",qr[1]-ql[1]+1);
		for(int i=ql[1];i<=qr[1];i++)
			printf(" %d",i);
		putchar('\n');
		fflush(stdout);
		scanf("%s",s);
		return s[0]=='+'?1:(s[0]=='-'?-1:0);
	}
	S=1<<(qtop-2);
	for(int i=0;i<S;i++){
		printf("?");
		top=0;
		for(int k=ql[1];k<=qr[1];k++)
			st[++top]=k;
		for(int j=2;j<qtop;j++)
			if(i>>(j-2)&1)
				for(int k=ql[j];k<=qr[j];k++)
					st[++top]=k;
		for(int k=ql[qtop];k<=qr[qtop];k++)
			st[++top]=k;
		printf(" %d",top);
		for(int j=1;j<=top;j++)
			printf(" %d",st[j]);
		putchar('\n');
		fflush(stdout);
		scanf("%s",s);
	}
	return s[0]=='+'?1:(s[0]=='-'?-1:0);
}
inline void Solve(int l,int r,int op){
	if(!op){
		qtop=0;
		op=1;
	}
	if(l==r){
		printf("! %d\n",l);
		fflush(stdout);
		return ; 
	}
	int mid=l+r-1>>1,res;
	ql[++qtop]=l;
	qr[qtop]=mid;
	res=Query();
	if(res!=op)
		Solve(l,mid,res);
	else
		Solve(mid+1,r,op);
	return ;
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%*d%*d",&n);
		Solve(1,n,0);
	}
	return 0;
}
```

---

## 作者：TernaryTree (赞：0)

发现加和不好处理，考虑怎么将 $Q$ 将和变为积的形式。

考虑怎么判断一个区间是否为负数。如果我们能让 $Q$ 乘上和这个区间乘积有关的一个数，那么就太好了！单纯的乘积显然无法实现，我们考虑在每一个因式后面加上一个数 $1$，原理是：

$$(a+1)(b+1)=ab+a+b+1$$

我们让 $Q$ 满足一个 $\prod (1+\prod q_{S_i})$ 的形式，思考如何让 $Q$ 再乘上一个 $1+\prod q_{S_i}$。

若想让 $Q$ 从 $(a_1+1)(a_2+1)\dots (a_m+1)$ 变为 $(a_1+1)(a_2+1)\dots (a_m+1)(a_{m+1}+1)$，增加的简单乘积式为 $\{a_1,\dots a_m\}$ 内挑选若干个并上 $a_{m+1}$，这一步的操作是 $\Theta(2^m)$ 的。

到这里就有一个明显的部分分做法了：从 $1$ 到 $n$ 枚举，每次乘上当前位置 $+1$，如果哪一次操作完变为负数或者 $0$ 就退出。

此处的优化：$n$ 不用枚举了，$n-1$ 之前都没有就退出输出 $n$。操作次数是 $2^{n-1}$ 以内的。

[$k=2^{n-1}$ Code](https://www.luogu.com.cn/paste/0m4am79r)

接下来显然就是二分的优化。这一步可能是因为我太菜刚看这题理解了很久，所以下面给出一个解释：

以 $n=8,q_1<0$ 为例：

$$
   \begin{aligned}
   &q_1q_2q_3q_4+1\quad &(-)\\
   \to \ \ &(q_1q_2q_3q_4+1)(q_1q_2+1)\quad &(+) \\
   \to \ \ &(q_1q_2q_3q_4+1)(q_1q_2+1)(q_1+1)\quad &(-)
   \end{aligned}
$$

注意到第一个因式的 $+1$ 是没有必要的，可以省去，会节省操作次数。

在递归二分过程中注意如果 $Q=0$ 就不需要了，重置就完事了。

加上一点小优化就过了。



---

