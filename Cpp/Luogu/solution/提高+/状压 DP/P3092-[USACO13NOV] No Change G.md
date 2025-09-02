# [USACO13NOV] No Change G

## 题目描述

Farmer John is at the market to purchase supplies for his farm.  He has in his pocket K coins (1 <= K <= 16), each with value in the range 1..100,000,000.  FJ would like to make a sequence of N purchases (1 <= N <= 100,000), where the ith purchase costs c(i) units of money (1 <= c(i) <= 10,000).  As he makes this sequence of purchases, he can periodically stop and pay, with a single coin, for all the purchases made since his last payment (of course, the single coin he uses must be large enough to pay for all of these).  Unfortunately, the vendors at the market are completely out of change, so whenever FJ uses a coin that is larger than the amount of money he owes, he sadly receives no changes in return!

Please compute the maximum amount of money FJ can end up with after making his N purchases in sequence.  Output -1 if it is impossible for FJ to make all of his purchases.

约翰到商场购物，他的钱包里有K(1 <= K <= 16)个硬币，面值的范围是1..100,000,000。

约翰想按顺序买 N个物品(1 <= N <= 100,000)，第i个物品需要花费c(i)块钱，(1 <= c(i) <= 10,000)。

在依次进行的购买N个物品的过程中，约翰可以随时停下来付款，每次付款只用一个硬币，支付购买的内容是从上一次支付后开始到现在的这些所有物品（前提是该硬币足以支付这些物品的费用）。不幸的是，商场的收银机坏了，如果约翰支付的硬币面值大于所需的费用，他不会得到任何找零。

请计算出在购买完N个物品后，约翰最多剩下多少钱。如果无法完成购买，输出-1


## 说明/提示

FJ has 3 coins of values 12, 15, and 10.  He must make purchases in sequence of value 6, 3, 3, 2, 3, and 7.


FJ spends his 10-unit coin on the first two purchases, then the 15-unit coin on the remaining purchases.  This leaves him with the 12-unit coin.


## 样例 #1

### 输入

```
3 6 
12 
15 
10 
6 
3 
3 
2 
3 
7 
```

### 输出

```
12 
```

# 题解

## 作者：jun1lesszZZ (赞：82)


### 状压$DP$ + 二分
**考虑构成**：$k<=16$所以根据$k$构造状压$dp$，将所有硬币的使用情况进行状态压缩 

**考虑状态**：数组$dp[i]$表示用$i$状态下的硬币可以购买到第几个商品 ，$f[i]$表示状态$i$下的花费   

**考虑转移**：使用当前硬币的状态一定由使用上一个硬币的状态转移而来    

 举个例子：
- 之前状态$x$：$dp[x] = y$， $i = 2 = (010)_2$  
  
- 当前枚举到的状态$i = 3 = (011)_2$ , $dp[i] = (dp[x] + 1$开始能买到哪里$(<=n))$, 相当于状态$x$能购买到$y$号物品，$i$要从$y+1$号开始购买  
  
- $i$状态比$x$状态在二进制的第三位多了1，说明比i状态多用了一个编号为1的硬币，$f[i] = f[x]$ + 硬币$1$的价值   

- 状态转移完成 

**考虑具体做法**：外层循环枚举所有状态，内层循环枚举每一位，若当前状态$i$的第$j$位为$1$，则可以进行转移   

   然后可以进行枚举$n$件物品，考虑每一件是否可以购买，一直到不能购买为止  
              
   因为一种状态可以被更新多次，所以要取$max$，保证$dp$数组存的是能买到的最大编号，然后更新$dp$数组和$f$数组  
   
   如果到第$n$件都可以买，则可以购买全部物品，$ans$记录当前的最小花费，最后用所有硬币的总面值减去最小花费即为答案  
   
   如果$ans$没有被更新过，说明不能购买，输出$-1$  
    
   时间复杂度$O(2^kkn)$，超时  
   
**考虑优化**：发现每次枚举物品统计价值来检查是否能够购买是冗余操作，可以用前缀和预处理一下，然后每次检查的时候进行一次二分就可以了  

时间复杂度$O(2^kklogn)$，可通过本题  

**考虑正确性**：因为外层循环枚举状态是从小到大枚举，所以保证当前状态某一位少$1$(即当前使用硬币数减一)的状态已经被转移过了   

**注意事项**：  
  1.不要错误理解题意，注意每次支付只能支付一枚硬币 ，不能算把硬币凑出来的总钱数然后判断能购买多少，这种错误做法能拿到$93$分的好成绩(大雾)是因为数据太水  
  
   2.二分的时候注意初始的左端点，因为从使用当前硬币的状态转移过来，所以要从使用当前硬币前状态所能购买到的物品$+1$作为左端点进行二分，右端点不会变化一直是$n$  
   
   3.因为二分时要检查的值要与前缀和数组进行比较，所以比较时前缀和数组应该减去左端点之前的前缀   
   
   4.注意二分的边界问题以及最后的返回值   
   
代码：
```cpp
#include <cstdio>
#include <cctype>
#define min(a, b) a < b ? a : b
#define MAXN 100001
#define N 17

int n, m, tot_money, ans = 2147483647;
int dp[1 << N], f[1 << N], sum[MAXN], pay[MAXN], coin[MAXN];

inline int read() {
    int s = 1, w = 0; char ch = getchar();
    for(; ! isdigit(ch); ch = getchar()) if(ch == '-') s = -1;
    for(; isdigit(ch); ch = getchar()) w = w * 10 + ch - '0';
    return s * w;
}
inline int check(int x, int cha) {
	int l = cha, r = n, mid;
	while(l <= r) {
	  mid = (l + r) >> 1;
	  if(sum[mid] - sum[cha - 1] == x) return mid;
	  if(sum[mid] - sum[cha - 1] < x) l = mid + 1;
	  else r = mid - 1;
	}
	return r;
}

int main() {
	m = read(), n = read();
	for(int i = 1; i <= m; i ++) coin[i] = read(), tot_money += coin[i];
	for(int i = 1; i <= n; i ++) pay[i] = read(), sum[i] = sum[i - 1] + pay[i];
	for(int i = 1; i < (1 << m); i ++) {
	  for(int j = 0; j < m; j ++) if(i & (1 << j)) {
	    int x = (i ^ (1 << j)), sum;
      if((sum = check(coin[j + 1], dp[x] + 1)) > dp[i]) 
        dp[i] = sum, f[i] = f[x] + coin[j + 1];
		  if(dp[i] == n) ans = min(f[i], ans);
	  } 
	}
	printf("%d", (tot_money - ans) < 0 ? -1 : tot_money - ans);
	return 0;
} 
```


---

## 作者：Imakf (赞：37)

用状压配上2-pointers更好哦~

我们可以考虑对于每一个硬币 $i$ 预处理一个辅助数组 $f[i][j]$ 

表示第 $i$ 个硬币如果从第 $j$ 个物品开始从左往右买，能最多买到第 $f[i][j]$ 个物品

因为物品价格不能为负数，所以这个东西显然可以用双指针搞，复杂度 $O(nk)$

有了 $f$ 数组，那么对于 $dp$ 状态我们这么设计：

$dp[i]$ 表示硬币选中状态为 $i$ 的方案最多可以买到从左到右第几个

转移直接枚举没有选中的硬币，利用 $f$ 数组 $O(1)$ 转移，复杂度 $O(2^k k)$

总复杂度 $O(nk+2^kk)$

```  cpp
#include<cstdio>
#include<cstring>
#include<ctime>
#include<cstdlib>

#define rg register
#define il inline
#define MX (100000 + 5)

int max(int a ,int b){return a > b ? a : b;}
int read();

int far[17][MX];
int coin[17] ,cost[MX];
int dp[1 << 17];

int main(){
	int k = read() ,n = read();
	for(rg int i = 1 ; i <= k ; ++i)	coin[i] = read();
	for(rg int i = 1 ; i <= n ; ++i)	cost[i] = read();
	for(rg int i = 1 ; i <= k ; ++i){	// 预处理 f 数组 
		int All = 0 ,r = 1;
		// All 是[j ,r)的总和 ,r 是双指针的右端点 
		for(rg int j = 1 ; j <= n ; ++j){
			while(r <= n && All + cost[r] <= coin[i])	All += cost[r++];
			far[i][j] = r - 1;	// 实际上第 r 个是选不到的
			if(All)	All -= cost[j];	// 左端点右移
		}
	}	
	for(rg int i = 0 ; i < (1 << k) ; ++i){
		for(rg int j = 1 ; j <= k ; ++j){
			if((1 << (j - 1)) & i)	continue;
			if(dp[i] >= n)	continue;
			dp[i | (1 << (j - 1))] = max(dp[i | (1 << (j - 1))] ,far[j][dp[i] + 1]);
		}
	}
	int Ans = -1;
	for(rg int i = 0 ; i < (1 << k) ; ++i){
		if(dp[i] < n)	continue;	// 没能买完所有的东西 
		int tmp = 0;
		for(rg int j = 1 ; j <= k ; ++j){	// 没有选硬币面值的就是答案 
			tmp += ((~i) & (1 << (j - 1))) ? coin[j] : 0;
		}
		Ans = max(Ans ,tmp);
	}
	printf("%d\n" ,Ans);
	return 0;
}

int read(){
	rg char k = getchar();
	while(k < '0' || k > '9')	 k = getchar();
	int x = 0;
	while(k >= '0' && k <= '9'){
		x = x * 10 + k - '0';
		k = getchar();
	}
	return x;
}
```

---

## 作者：Tyher (赞：24)

```
/*
     k<=16，我们考虑状压dp吧
     
     因为硬币的个数较小，我们可以将硬币的选择情况压成状态pi，对于pi上从各位开始的第i位，为货币ci可选与否
     
     第i位当然是二进制下的啦
     
     dp[i]中，i表示当前使用的货币状态，dp[i]表示使用这些货币可以到达的商品位置
     
     那么我们枚举所有的可选状态，对于每一个状态枚举当前选择的货币
     
     对于状态pi，假设我们枚举当前选择的货币ci，则有
     
     dp[pi]=max(dp[pi],find(sum[dp[pi^(1<<ci)]]+coin[ci]));
     
     其中，sum[i]表示从第一个商品到第i个商品的前缀和，可以用一个数组简单计算一下
  
     coin[ci]为ci货币的价值，题目已经给出
  
     find(x)表示价值为x的货币可以从1连续购买到的最大商品的下标
     
     对于find(x)函数我们怎么解决呢？
     
     因为我们期望得到的x已经确定，而前缀和是具有单调性的，我们可以二分查找
     
     那么状态转移方程的问题我们已经解决了
     
     接下来是统计答案
     
     对于某一个状态pi而言，当且仅当dp[pi]==n的时候，pi才会被我们算进答案
     
     那么我们应当如何知道最终剩余的钱呢?
     
     我们对于状态pi可以统计到第i位是否可选，那么判断其他没有选中的位置，及为ci货币没有被选择
     
     那么最终对于每个合法状态pi可以统计到剩余的钱ansi，全部取max就可以了。
*/

#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define il inline
#define rg register
#define ll long long
#define N 20
#define M 100010
#define inf 2147483640
using namespace std;
int k,n;
ll coin[N],cost[M],sum[M],dp[M],ans=-1;
il int read()
{
	rg int data=0;rg char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9')data=(data<<3)+(data<<1)+c-'0',c=getchar();
	return data;
}
int find(rg int lim){
	rg int le=1,ri=n,pos=0;
	while(le<=ri){
		int mid=((le+ri)>>1);
		if(sum[mid]<=lim)le=mid+1,pos=mid;
		else ri=mid-1;
	}
	return pos;
}
int main()
{
	freopen("s.in","r",stdin);
	k=read(),n=read();
    for(rg int i=0;i<k;++i)
		coin[i]=read();
	for(rg int i=1;i<=n;++i)
		cost[i]=read(),sum[i]=sum[i-1]+cost[i];

	for(rg int p=0;p<(1<<k);++p){//枚举所有状态
		for(rg int i=0;i<k;++i){
			if(!(p&(1<<i)))continue;//如果当前货币i没有被选则跳过
			ll res=dp[p^(1<<i)];//p^(1<<j)表示状态pi去掉ci货币时得到的新状态
			//那么res表示新状态可以到达的最末商品
			ll pos=find(sum[res]+coin[i]);
            //我们期望查找到的是从商品1到res的价值并加上货币ci价值的总和pos
			//二分查找到最后一个小于等于的商品下标
			dp[p]=max(dp[p],pos);
			//取最大值
		}
	}
	for(rg int p=0;p<(1<<k);++p){
		if(dp[p]==n){
			ll cnt=0;
			for(rg int j=0;j<k;++j){
				if(!(p&(1<<j)))cnt+=coin[j];
				//如果当前位置没有货币，统计答案
			}
			ans=max(ans,cnt);
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：QSWei (赞：18)

楼下是Pascal，我来发c++；

   

这是我做的第一题状压，所以写了很详细的过程。



都在代码后面~


/\*Miroerwf\_Q\*/

```cpp
#include<iostream>
//#include<cstdio>
//#include<cstring>
#include<cmath>
#include<algorithm>
//#include<queue>
//#define LL long long
using namespace std;
int m,n,a[100001];/*物品数组*/int sum[100001];/*前缀和*/int c[17]/*硬币*/;
int b[17];/*每个硬币的状态*/int f[(1<<16)+10];/*在某个状态下购买的物品数*/
int maxx;/*用二进制表示状态时的最大值*/int ans=-1;/*结果*/int tot;/*总钱数*/
int main()
{
    cin>>m>>n;
    for(int i=1;i<=m;i++){
        cin>>c[i];
        tot+=c[i];/*记录总钱数*/
    }
    for(int i=1;i<=n;i++){
        cin>>a[i];
        sum[i]=sum[i-1]+a[i];/*记录前缀和*/
    }
    b[1]=1;
    for(int i=2;i<=m;i++){
        b[i]=b[i-1]<<1;/*二进制(十进制)：b[1]=1(1),b[2]=10(2),b[3]=100(4),b[4]=1000(8),*/
    }        /*b[5]=10000(16),------,b[m]=100---00(2的m-1次方),表示只选第i个硬币的状态。*/
    maxx=(1<<m)-1;
    for(int i=0;i<=maxx;i++)
        for(int j=1;j<=m;j++)
            if((i&b[j])){/*如果i&b[j]不等于零,也就是选第j个硬币.*/
                int tmp=f[i^b[j]];/* i^b[j]是不选第j个硬币的状态,tmp即是不用第j个硬币可以购买的物品数.*/
                tmp=upper_bound(sum+1,sum+n+1,sum[tmp]+c[j])-sum;/*upper_bound是c++STL库的函数,解释在上面.*/
                /*            此时的tmp就是第一个大于(额...是前缀和大于)sum[tmp](这是原先买物品花的钱)+c[j](这是这个硬币的面值)的物品的位置.*/
                /*         那么tmp之前的物品都买过了(不包括他自己).*/
                f[i]=max(f[i],tmp-1);/*tmp-1就是已经买的物品,拿来更新f[i];*/
            }
    for(int i=0;i<=maxx;i++)/*从最小状态到最大状态(是用来表示状态的数最小(大),不是状态最小(大),2333)时,有多种购买方法,枚举一遍进行处理.*/
        if(f[i]==n){/*状态为i时买了全部的n个物品,也就是此状态是一种购买方案.*/
            int cnt=0;/*记录用掉的总钱数*/
            for(int j=1;j<=m;j++)/*枚举硬币，看看哪一个硬币使用了.*/
                if(i&b[j])/*   i&b[j]不为零,即j这个硬币使用了.*/
                    cnt+=c[j];
        ans=max(ans,tot-cnt);/*求最多剩余的钱.*/
        }
        if(ans<0)/*判断是不是买不起,但为什么不直接等于零呢?,因为Fj可能正好买完所有物品二没硬币剩余~(Ovo)*/
        cout<<-1;
    else
        cout<<ans;
    return 0;
}
```

---

## 作者：UltiMadow (赞：15)

其实这题代码真的很短

我们来换一种dp方式（当然这种dp方式题解里好像有，但是讲的不太详细，于是我来补充一下）

仍然是状压dp

令 $f[st]$ 为当前硬币使用状态为 $st$ 时多买到几号物品

我们考虑 $f[i]$ 能转移到那些地方

显然，$f[i]\rightarrow f[j]$ 当 $j=i+2^k$ 且 $2^k\&i=0$ 的时候可以转移

其中，$\&$ 表示按位与运算

接下来，考虑转移多少

设当前转移使用的硬币是第 $k$ 个硬币，价值为 $w_k$

那么，我们可以写出转移方程：$f[i\ xor \ (2^k)]=\max(f[i\ xor\ (2^k)],p)$ 其中 $p$ 为满足 $\sum_{i=f[i]}^{p}val_i\leq w_k$ 的最大值

注：xor 为按位异或运算，$val_i$ 为 $i$ 商品的价值

接下来，我们用前缀和优化，发现还可以用二分查找找到这个 $p$ 于是这题就作完啦

时间复杂度：$O(2^kk\log n)$

附上我简短的代码：
```cpp
#include<bits/stdc++.h>
#define MAXN 100010
using namespace std;
int n,K,ans;
int sum[MAXN],mon[MAXN];
int f[1<<17];
int find(int l,int r,int s)//二分查找
{
	int now=sum[l],ret=l;
	while(l<=r)
	{
		int mid=l+r>>1;
		if(sum[mid]-now<=s)ret=mid,l=mid+1;
		else r=mid-1;
	}
	return ret;
}
int fl=0;
int main()
{
	scanf("%d%d",&K,&n);
	for(int i=1;i<=K;i++)scanf("%d",&mon[i]);
	for(int i=1;i<=n;i++)scanf("%d",&sum[i]),sum[i]+=sum[i-1];
	int max_state=(1<<K)-1;
	for(int i=0;i<=max_state;i++)
	{
		for(int j=1;j<=K;j++)
		{
			if((i>>j-1)&1)continue;
			f[i|(1<<j-1)]=max(f[i|(1<<j-1)],find(f[i],n,mon[j]));//转移
		}
		if(f[i]==n)
		{
			int a=i,cnt=0;fl=1;
			for(int j=1;j<=K;j++)
			{
				if((i>>j-1)&1)continue;
				cnt+=mon[j];
			}
			ans=max(ans,cnt);
		}
	}
	if(!fl)printf("-1");
	else printf("%d",ans);
	return 0;
}
```
还有一个转移顺序问题，我想了好长时间，但是后来想想是我考虑多了。

我们考虑状态 $st$，能转移到它的一定是它的一个子集 $st'$ 所以，很明显 $st>st'$ 于是当我们从小到大枚举时，枚举到 $st$ 时 $st$ 一定被转移完了，也就是到达最终状态了，我们就可以放心的用状态 $st$ 来转移其他的状态啦~

---

## 作者：灵乌路空 (赞：9)

## 知识点 : 状压DP   

### [原题面](https://www.luogu.org/problem/P3092)  

### 分析题意:   
- 由于 **每次只能花费一枚硬币** , 且硬币数 $\le 16$   
  则可以使用 一二进制串 , 表示硬币的花费状况   

- 为什么会导致 无法完成购买 ?   
  可以发现 ,  若花费完所有硬币后, 还无法买到第n个物品   
  则 导致无法完成购买.    
  
  则对于每一个 硬币花费状态,      
  都需要最大化其 能购买的物品编号    
  考虑 状压 $DP$ .    
 
- 设计状态:   
  设 $f[i]$  : 花费状态 i 的硬币 ,  能买到的最远的物品 .   
  显然有: $f[0] = 0$ ;   
  
 - 设将第 $j$ 个硬币, 价值为 $w[j]$ ,  添加到状态i中,     
    则有状态转移方程 为:   
    $f[i + 2^j] = max(f[i + 2^j] , f[i] + k)\ \ (sum[f[i] +1 \sim k] \le  w[j])$   
    - $sum[l,r]$ 为 $[l,r]$ 内 物品的价值总和   
  	可以使用前缀和进行维护, 并 $O(1)$ 查询   
    
	 - 如何快速查询 最优的 位置增量 $k (sum[f[i] +1 \sim k] \le w[j])$ ?   
	   由于前缀和 单调递增 ,  则可以进行 二分查找   
	   在 $\log n$ 的时间内 求得最优的 位置增量 $k$    
  	 
  - 终止条件 :     
    若出现 $f[i] = n$ ,  花费说明状态 $i$ 的硬币, 已经可以购买所有物品   
    统计其价值 ,  并取最大值为答案 即可   


---

```cpp
#include<cstdio>
#include<ctype.h>
#define max(a,b) (a>b?a:b)
#define ll long long
const int MARX = 1e5+10;
const int MARXALL = 131080;
//=============================================================
int k, n, all, coin[20], c[MARX], f[MARXALL];;
ll ans = -1, sum[MARX];
//=============================================================
inline int read()
{
    int s=1, w=0; char ch=getchar();
    for(; !isdigit(ch);ch=getchar()) if(ch=='-') s =-1;
    for(; isdigit(ch);ch=getchar()) w = w*10+ch-'0';
    return s*w;
}
int upper_search(int value, int l1, int r1)//找到区间[l1,r1] 大于value的第一个位置 
{
	int pos = r1 + 1;
	for(int l = l1, r = r1; l<=r;)
	{
	  int mid = (l + r) >> 1;
	  if(sum[mid] - sum[l1 -1] > value)  pos = mid,r = mid-1;
	  else l = mid + 1;
	}
	return pos;
}
//=============================================================
signed main()
{
	k = read(), n = read(); all = (1 << k) -1;//构造全集 
	for(int i = 1; i <= k; i ++) coin[i] = read();//读入并维护前缀和 
	for(int i = 1; i <= n; i ++) c[i] = read(), sum[i] = sum[i-1] + c[i];
	
	for(int i = 0; i <= all; i ++)
	{
	  if(f[i] == n)//状态满足条件, 统计答案 
	  {
	  	ll sum1 = 0;
	  	for(int j = 0; j < k; j ++) sum1 += (!(1 << j & i))*coin[j+1];//求得 未使用的硬币总和 
	  	ans = max(ans,sum1);//取最大值 
	  	continue;
	  }
	  
	  int l = f[i] + 1, r = n, now = 1;//构造二分查找边界, 与当前枚举到的硬币编号 
	  for(; ; )
	  {
		for(;(1 << (now-1) & i) && now <= k;) now++;//循环枚举 ,直到 一个未被使用的硬币 
		if(now > k) break;
		
		int pos = upper_search(coin[now],l,r) - 1;//查找 最大增量 
		f[i | (1 << (now-1))] = max(f[i | (1 << (now-1))], pos);//转移 
	    now ++;//编号++ 
	  }
	}
	printf("%lld",ans);
}
```

---

## 作者：zjy111 (赞：5)

萌新刚学习了状压dp, 发一篇题解强化一下

拿到这道题, 先看一下数据范围: 嗯, $k<=16$, 非常的状压......

众所周知, 状压大部分情况下是将一个状态转移为一个二进制数来保存

## bitset大法吼啊 ! ! !

所以复杂度肯定是 $2^n$ 系列的

既然和二进制有关, 那么为什么不用$bitset$呢? 

反正我觉得$bitset$代码虽然看着长了一些, 但比满屏的&|^更清楚

先讲一下这道题的思路

首先, 我们要状态压缩的肯定是硬币数$k$

那么我们就可以用一个$k$位二进制数来保存状态, 

每一位对应的$0$为不用这枚硬币, 1为用这枚硬币

令$dp[i]$表示使用硬币状态为$i$时顺序购买最多可以买几件商品

那么对于每一个状态, 都肯定是由比当前状态少支付一个硬币的状态转化而来的

那么用$bitset$表示就是

```
对于当前状态
for i=1~k枚举该状态每一位
	if (该位为1){
    	    原状态=现状态将该位设为0;
            现状态=max(现状态, 原状态+第i个硬币可以购买的物品数)
    	}
```

同时, 因为$n<=10^5$, 我们如果暴力的去枚举每一个物品是否可以买, 很明显会超时, 

所以我们可以用前缀和数组去维护, 利用二分查找前缀和数组以达到$logn$的复杂度

然后这题就做好啦~~~

献上码风奇特的代码(注意事项详见注释)

```cpp
#include <bits/stdc++.h>
using namespace std;
#define r register
int k,n,arr[100005],sum[100005],coin[18],dp[65550];
unsigned long stat; //bitset不能直接作为数组下标, 于是用一个无符号长整型间接表示状态
bitset<18>x; //一个18位的bitset
int main() {
	cin>>k>>n;
	for(r int i=1;i<=k;i++) scanf("%d",&coin[i]);
	for(r int i=1;i<=n;i++){
		scanf("%d",&arr[i]);
		sum[i]=sum[i-1]+arr[i]; //前缀和处理
	}
	for(r int i=0;i<(1<<k);i++){ //枚举每一个当前状态i
		x=i; //将i的值赋予这个bitset容器x
		for(r int j=1;j<=k;j++){ 
			if(x[j-1]){ //我习惯用bitset时从0开始所以要减1
				x[j-1]=0;//找到不花费这枚硬币时的原价值
				stat=x.to_ulong(); //将bitset转成unsigned long类型的函数
				dp[i]=max(dp[i]+0ll,upper_bound(sum+1,sum+n+1,coin[j]+sum[dp[stat]])-sum-1ll); 
        //状态转移, 注意二分查找的是第一个不大于总花费的, 所以要减1; 另外所查找的总花费是sum数组中原状态可以购买的物品个数对应的值加上这个硬币的价值
				x[j-1]=1; //注意转移完了需要重置状态, 不然就没法正确转移
			}
		}
	} 
	int ans=-1,res=0; //因为无解输出-1, 所以ans初始化为-1
	for(r int i=0;i<(1<<k);i++){
		x=i;
		if(dp[i]==n){ //当前状态可以购买所有物品
			res=0;
			for(r int j=1;j<=k;j++)
				if(!x[j-1])res+=coin[j]; //统计当前状态剩余钱数
			ans=max(ans,res); //答案取最大值
		}
	}
	cout<<ans;
	return 0;
}
```
P.S. 对于这道题而言$bitset$的好处可能不是那么明显, 

但是对于有些状压题, 状态转移时方程和该状态二进制中1的个数有关,

这时用$bitset$就不需要预处理, 直接使用$x.count()$函数即可

---

## 作者：Y_B_Y (赞：4)

一道比较综合的状态压缩DP

什么是状态压缩呢,我们知道,[一个十进制数可以转化为二进制](https://www.cnblogs.com/web-record/p/11132861.html),二进制数是由0和1组成,如$(11)_{10}=(1011)_{2}$我们可以用,这些1和0来表示一些信息,而因为它是数所以可以存在用于DP的数组里,并且可以通过位运算来进行快速的计算.

这里介绍几种位运算

按位与"$\&$",$1\& 1 =1$,$1\& 0 =0$,$0\& 1 =0$,$0\& 0 =0$,如果是一个多位的二进制数则按位计算,如$(1011)_{2} \& (0110)_2 = (0010)_{2} =(10)_2=(2)_{10}$

按位或"$|$" $1| 1 =1$,$1| 0 =1$,$0| 1 =1$,$0| 0 =0$ 计算方法同上

按位异或"$⊕$" $1⊕ 1 =0$,$1⊕ 0 =1$,$0⊕ 1 =1$,$0⊕ 0 =0$,计算方法同上(注这个位运算在C++代码中用"^"符号表示)

右移"$<<$",就是将一个数的二进制串整体像右移,如$(13)_{10}<<3=(1101)_2<<3=(1101000)_2=(104)_{10}$,并且$a<<k=a\times 2^k$

左移"$>>$",类似.

那位运算如何进行,比如我们用二进制的第$i$位表示硬币$i$是否花掉,那么我们如果要看第硬币$3$是否被花掉了,设现在的状态位$(110010)_2$我们可以直接$(110010)_2 \& (1<<(3-1))=(110010)_2 \& (100)_2=0$,等于0,说明硬币$3$还没被花掉,那如果我们要判断硬币$k$,设状态为$j$,那么就可以判断$j\&(1<<(k-1))$,如果为1即花掉

由于这一题涉及的位运算不多这里就不深究

现在我们来推状态转移方程,因为题目要求按顺序买,设$f[j]$为状态为$j$时最多买到第几个商品

那么如果$j\&(1<<(k-1))==1$

$f[j]=max(f[j],f[j-(1<<(k-1))]+maxn(f[j-(1<<(k-1))],m[k]))$

其中$maxn(f[j-(1<<(k-1))],m[k])$表示从第$f[j-(1<<(k-1))]+1$商品开始买,用面值$m[k]$的硬币$k$最多能买到第几个商品

这个方程的意思是,一个硬币$k$已经花掉的状态最多能买到的商品序号,其实就等于除了$k$没花掉其他都一样的状态($f[j-(1<<(k-1))]$,这里减法是为了使第k位为0)最多能买到的商品序号$x$+从第$x+1$个商品开始买用面值$m[k]$的硬币$k$最多能买几个商品,再枚举k取最大值

现在有一个问题$maxn(f[j-(1<<(k-1))],m[k])$,怎么求,因为商品的价格均为正,所以从商品$f[j-(1<<(k-1))]+1$买到商品$r$,要花的钱就是$sum[r]-sum[f[j-(1<<(k-1))]]$其中$sum[i]$表示从第一个商品买到第$i$个商品要花的总钱数,可以一开始用$O(n)$求出来,然后我们发现随着$r$越来越大,得到的值也越来越大,由于我们要求最大的$r$所以可以用二分来找.

所以我们先从$0$到$1<<k-1$(都没花到都花了)枚举状态$j$,再枚举$k$,因为$j-(1<<(k-1))<j$所以$f[j-(1<<(k-1))]$是已经求出来的,再通过二分求$r$

最后再通过枚举所有状态来找能够买$n$个商品的状态,统计没有花的硬币面值,如果没找到输出-1

时间复杂度为$O(2^k\times k \times log_2 N)$

细节看代码吧

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll n,k,f[(1<<17)],m[17],ans=-1,s[100001];//s为上面的sum,k,n的意义看题目,其他同上面
inline long long read()//快读
{
    char c=getchar();long long sum=0,f=1;
    while(!(c>='0'&&c<='9')) {if(c=='-') f=-1;c=getchar();}
    while(c>='0'&&c<='9') {sum=((sum<<1)+(sum<<3))+(c-'0');c=getchar();}
    return sum*f;
}
ll gt(ll x,ll y)//求maxn(x,y)
{
	ll l=x+1,r=n,sum=0;
	while(l<=r)//二分
	{
		ll mid=(l+r)/2;
		if(s[mid]-s[x]<=y) sum=mid-x,l=mid+1;
		else r=mid-1; 
	}
	return sum;//返回最多能买几个
}
int main()
{
	k=read();n=read();
	for(int i=1;i<=k;i++) m[i]=read();
	for(int i=1;i<=n;i++) s[i]=s[i-1]+read();//求sum[i]
	for(int i=0;i<(1<<k);i++)//枚举上文的"j"
	for(int j=0;j<k;j++) //枚举上文的"k",这里j表示的其实是j+1位(因为下面是1<<j)
	if(i&(1<<j)&&f[i]<n)//如果第j+1位为1,且f[j]不为n(为n没必要更新)  f[i]=max(f[i],f[i^(1<<j)]+gt(f[i^(1<<j)],m[j+1]));//更新最大值
	for(int i=0;i<(1<<k);i++)//找最大余额
	if(f[i]==n)
	{
		ll sum=0;
		for(int j=0;j<k;j++) if(!(i&(1<<j))) sum+=m[j+1];//统计
		if(sum>ans) ans=sum;//更新ans
	}
	return printf("%lld",ans),0;//输出和return 0
}
```


---

## 作者：张鑫杰 (赞：4)

观摩了一下题解区的全部题解,我深深地为诸位大佬的高超的技术而佩服.然而,诸位大佬去忽略了一个有效的提速手段----初始化.

首先我们对K进行状态压缩,然后预处理每一枚硬币,用二分搜索得出哪个硬币开始从哪个物品开始买能买到第几个.
```cpp
    F(i,1,k){
        F(j,1,n){
            int now=value[i];
            if(now>=buy[j]){
                int right=n+1,left=j,mid=(right+left)>>1;
                while(right-1>left){
                    if(add[mid]-add[j-1]<=now){
                        left=mid;
                    }else{
                        right=mid;
                    }
                    mid=(right+left)>>1;
                   //cout<<left<<" "<<right<<endl;
                }
                sum[i][j]=left+1;
            }else{
                sum[i][j]=j;
            }
            //cout<<i<<" "<<j<<" "<<sum[i][j]<<endl;
        }
    }
```
如上代码,i表示第几个硬币,j表示从j开始取能取到f[i][j],即范围为[i,j).

依靠此预处理,效果如下(O2优化)
![](https://cdn.luogu.com.cn/upload/pic/33370.png)
以下是全部代码:

```cpp
const int MAXN=100000+1;
const int INF=0x3f3f3f3f;
inline int read(){
    int x = 0, y = 1, c = getchar();
    while (c>'9' || c<'0') { if (c == '-')y = -1; c = getchar(); }
    while (c >= '0'&&c <= '9') { x = x * 10 + c - '0'; c = getchar(); }
    return x * y;
}

static int value[18],buy[MAXN],maxn,f[1<<18],coin[18],sum[18][MAXN],add[MAXN];
signed main(){
    int k=read(),n=read();
    F(i,1,k){
        value[i]=read();
    }
    F(i,1,n){
        buy[i]=read();
        add[i]=add[i-1]+buy[i];
    }
    coin[1]=1;
    //cout<<"coin"<<endl;
    F(i,2,k){
        coin[i]=coin[i-1]<<1;
        //cout<<coin[i]<<endl;
    }
    //while(1);
    F(i,1,k){
        F(j,1,n){
            int now=value[i];
            if(now>=buy[j]){
                int right=n+1,left=j,mid=(right+left)>>1;
                while(right-1>left){
                    if(add[mid]-add[j-1]<=now){
                        left=mid;
                    }else{
                        right=mid;
                    }
                    mid=(right+left)>>1;
                   //cout<<left<<" "<<right<<endl;
                }
                sum[i][j]=left+1;
            }else{
                sum[i][j]=j;
            }
            //cout<<i<<" "<<j<<" "<<sum[i][j]<<endl;
        }
    }
    //while(1);
    maxn=(1<<k)-1;
    f[0]=1;
    F(i,1,maxn){
        F(j,1,k){
            if((coin[j]&i)){
                f[i]=max(sum[j][f[i-coin[j]]],f[i]);
                //cout<<i<<" "<<f[i]<<endl;
            }
        }
    }
    int ans=0,now=0;
    bool flag=true;
    F(i,1,maxn){
        if(f[i]==n+1){
            flag=false;
            now=0;
            F(j,1,k){
                if((i&coin[j])==0){
                    now+=value[j];
                }
            }
            ans=max(ans,now);
        }
    }
    if(flag){
        printf("-1");
        return 0;
    }
    printf("%lld",ans);
    return 0;
}

```


---

## 作者：MZ_CXQ (赞：3)

[${\color{Cyan}{>>Question}}$](https://www.luogu.org/problem/P3092)

[**>>配合博客食用更佳**](https://www.cnblogs.com/mzg1805/p/11360291.html)

一道状压好题(少有的没看题解一遍$AC$的不是水题(自认为)的题(看来是我太菜了))

首先看到$k\leqslant 16$,$emm$,要么暴搜,要么状压

再看$n\leqslant 10^5$,$emm$,状压实锤了,但这$n$太大,显然其中状压$dp$的状态和转移中都不能有$n$(一有就炸了)

看范围先想一维,令$f[i]$表示状态$i$下的什么

有[P4329 [COCI2006-2007#1] Bond](https://www.cnblogs.com/mzg1805/p/11359475.html)的经验,我们知道状态并不只表示了其中的选或不选,还可以表示选了多少个和选了哪些

在这道题下,选了哪些就尤为重要了(因为就可以统计答案了),那差的就是能不能买到$n$个或者说能买多少个

试着令$f[i]$表示状态$i$下最多能买多少个,枚举当前用哪个硬币(假设是第$j$号硬币)

那之前的状态为$f[i-\left \{ j \right \}]$(也就是说$j$号硬币要从$f[i-\left \{ j \right \}]+1$号物品开始买),

那现在的问题就只剩下$j$号硬币从某处开始最多能买多少个物品,这可以用前缀和$+$二分提前预处理出来

令$cnt[i][j]$表示$i$号硬币从$j$处开始最多买多少个,$r$表示最远的那个编号

显然有
$$sum[r]-sum[j-1]\leqslant val[i]$$

即
$$r=upperbound(val[i]+sum[j-1])-1$$

如此,转移就出来了
$$f[i] = max\left \{ f[i-\left \{ j \right \}]+cnt[j][f[i-\left \{ j \right \}]+1] \right \}$$

上代码(写得好累啊$QwQ$)
```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#define ll long long
using namespace std; 

template <typename T> void in(T &x) {
    x = 0; T f = 1; char ch = getchar();
    while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
    while( isdigit(ch)) {x = 10 * x + ch - 48; ch = getchar();}
    x *= f;
}

template <typename T> void out(T x) {
    if(x < 0) x = -x , putchar('-');
    if(x > 9) out(x/10);
    putchar(x%10 + 48);
}
//-------------------------------------------------------

const int N = 1e6+5,M = 17;

int k,n;
int val[M],cst[M],cnt[M][N];
ll sum[N];
int f[1<<M];
ll ans = -1;

int main() {
	int i,j;
	in(k); in(n);
	for(i = 1;i <= k; ++i) in(val[i]);
	for(i = 1;i <= n; ++i) in(cst[i]),sum[i] = sum[i-1]+cst[i];
	for(i = 1;i <= k; ++i) {
		for(j = 1;j <= n; ++j) {
			cnt[i][j] = upper_bound(sum+1,sum+n+1,val[i]+sum[j-1])-sum-1-j+1;//r-j+1//debug val -> cst
		}
	}//预处理出i硬币在位置j向后延伸的最长长度
	memset(f,~0x3f,sizeof(f));
	f[0] = 0;
	for(i = 1;i < (1<<k); ++i) {
		for(j = 1;j <= k; ++j) {
			if(i&(1<<(j-1))) f[i] = max(f[i],f[i^(1<<(j-1))]+cnt[j][f[i^(1<<(j-1))]+1]);
		}
		if(f[i] >= n) {
			ll res = 0;
			for(j = 1;j <= k; ++j) if(!(i&(1<<(j-1)))) res += val[j];
			ans = max(res,ans);
		}
	}
	out(ans);
	return 0;
}
```


---

## 作者：_____hzf_____ (赞：3)

### 题目描述
约翰到商场购物，他的钱包里有K(1 <= K <= 16)个硬币，面值的范围是1..100,000,000。

约翰想按顺序买 N个物品(1 <= N <= 100,000)，第i个物品需要花费c(i)块钱，(1 <= c(i) <= 10,000)。

在依次进行的购买N个物品的过程中，约翰可以随时停下来付款，每次付款只用一个硬币，支付购买的内容是从上一次支付后开始到现在的这些所有物品（前提是该硬币足以支付这些物品的费用）。不幸的是，商场的收银机坏了，如果约翰支付的硬币面值大于所需的费用，他不会得到任何找零。

请计算出在购买完N个物品后，约翰最多剩下多少钱。如果无法完成购买，输出-1
### 输入输出格式
#### 输入格式：
* Line 1: Two integers, K and N.

* Lines 2..1+K: Each line contains the amount of money of one of FJ's coins.

* Lines 2+K..1+N+K: These N lines contain the costs of FJ's intended purchases.

#### 输出格式：
* Line 1: The maximum amount of money FJ can end up with, or -1 if FJ cannot complete all of his purchases.


### 输入输出样例
#### 输入样例#1：
3 6 
12 
15 
10 
6 
3 
3 
2 
3 
7 
#### 输出样例#1： 复制
12 
### 说明
FJ has 3 coins of values 12, 15, and 10. He must make purchases in sequence of value 6, 3, 3, 2, 3, and 7.

FJ spends his 10-unit coin on the first two purchases, then the 15-unit coin on the remaining purchases. This leaves him with the 12-unit coin.


题目大意：

给出k个硬币，n个商品，可以调整使用硬币的顺序，依次购买商品，每次不会找零，求最后剩下的最大钱数，如不能买全，输出-1

因为$k\leq16$，考虑状压

设$dp_{sta}$表示状态为$sta$时（二进制，表示哪些硬币使用了，哪些没使用），从一号物品开始能购买的物品数量

显然有

当使用当前状态中未使用的一个硬币时

$dp[new\_sta]=max(dp[new\_sta],k)$

其中$new\_sta$是转移后的新状态

用$sum_k$表示前$i$个物品的总售价

则k为$sum_k$能够支付起是的最大物品数量（最优性）

二分一下即可求出k

代码：
```
#include<bits/stdc++.h>
#define ll long long
#define INF 2147483647
#define mem(i,j) memset(i,j,sizeof(i))
#define F(i,j,n) for(register int i=j;i<=n;i++)
#define lowbit(i) i&(-i)
using namespace std;
int k,n,c[20],p[100010],dp[1100000],sum[100010];
inline int read(){
	int datta=0;char chchc=getchar();bool okoko=0;
	while(chchc<'0'||chchc>'9'){if(chchc=='-')okoko=1;chchc=getchar();}
	while(chchc>='0'&&chchc<='9'){datta=datta*10+chchc-'0';chchc=getchar();}
	return okoko?-datta:datta;
}
int main(){
	k=read();n=read();
	F(i,1,k)
		c[i]=read(),c[0]+=c[i];
	F(i,1,n)
		p[i]=read(),sum[i]=sum[i-1]+p[i];
	mem(dp,-1);
	dp[0]=0;
	int ans=2147483647;
	F(sta,0,(1<<k)-1){
		if(dp[sta]==-1)
			continue;
		if(dp[sta]==n){
			int _ans=0;
			F(i,1,k)
				if(sta&(1<<(i-1)))
					_ans+=c[i];
			ans=min(ans,_ans);
			continue;
		}
		F(i,1,k){
			if(sta&(1<<(i-1)))
				continue;
			int l=dp[sta]+1,r=n,mid,_ans=-1;
			while(l<=r){
				mid=(l+r)>>1;
				if(sum[mid]<=sum[dp[sta]]+c[i])
					l=mid+1,_ans=mid;
				else
					r=mid-1;
			}
			if(_ans==-1)
				continue;
			dp[sta|(1<<(i-1))]=max(dp[sta|(1<<(i-1))],_ans);
		}
	}
	printf("%d\n",ans==2147483647?-1:c[0]-ans);
	return 0;
}
```

---

## 作者：asuldb (赞：3)

其实我是点单调队列的标签进来的，之后看着题就懵逼了

于是就去题解里一翻，发现楼上楼下的题解说的都好有道理，
f[j]表示一个再使用一个硬币就能到达i的某个之前状态，b[now]表示使用那个能使状态j变到i的硬币的面值，find表示这些花费可以到达的最大距离，由于前缀和保持单调可以用二分求解，方程不就是f[i]=max(f[i],find(p[f[j]]+b[now]))吗

但这道题怎么用单调队列优化呢

我们观察这个方程你会发现无论是b[now]，p[f[j]]都跟i没有什么关系，而只要是p[f[j]]+b[now]越大，相应的find的值也就越大

于是我们就可以愉快的单调队列优化这个dp了，用一个单调队列把每次的p[f[j]]+b[now]存起来，每次有新元素入队时维护队列的单调性，之后当所有元素入队完，直接用队首的最大值进行一遍find就好了，这样就可以避免进行多次find了

尽管单调队列是用常数奇大的deque实现的，但开了O2能跑到120 ms，轻松卡到最优解第一
```cpp
#include<iostream>
#include<queue>
#include<cstring>
#include<cstdio>
#define re register
#define int long long
#define maxn 100001
using namespace std;
int f[65540],a[maxn],b[17],n,m,num,p[maxn];
int c[17];
inline void check(int x)
{
    memset(c,0,sizeof(c));
    int pp=m;
    while(x)
    {
        if(x&1) c[pp]=1;
        pp--;
        x>>=1;
    }
}
inline int read()
{
    char c=getchar();
    int x=0;
    while(c<'0'||c>'9') c=getchar();
    while(c>='0'&&c<='9')
      x=(x<<3)+(x<<1)+c-48,c=getchar();
    return x;
}
inline int find(int x)
{
    int l=1,r=n,tot=0;
    while(l<=r)
    {
        int mid=l+r>>1;
        if(p[mid]<=x) l=mid+1,tot=mid;
        else r=mid-1;
    }
    return tot;
}
signed main()
{
    m=read();
    n=read();
    for(re int i=1;i<=m;i++) b[i]=read(),num+=b[i];
    for(re int i=1;i<=n;i++) a[i]=read();
    p[1]=a[1];
    for(re int i=2;i<=n;i++) p[i]=p[i-1]+a[i];
    for(re int i=0;i<=(1<<m)-1;i++)
    {
    	deque<int> q;
    	for(re int j=1;j<=m;j++)
    	{
        	if(!(i&(1<<(m-j)))) continue;//这里跟楼上楼下几篇题解不太一样，这个状态转成二进制后左边第一位表示的是第一个硬币是否被选择
        	int k=i^(1<<(m-j));
        	while(q.size()&&q.back()<p[f[k]]+b[j]) q.pop_back();//跟队尾元素比较，如果比队尾大就弹出队尾，维护单调队列单调性
        	q.push_back(p[f[k]]+b[j]);//入队
 		}
        //其实这里不用单调队列优化也是可以的，我们只需要存储一下最大值就好了，这样应该还能快一些，但是用单调队列优化dp的这种思路还是比较重要的
 		f[i]=find(q.front());//只用一遍find就好了
    }
 	int ans=-1;
 	for(re int i=0;i<=(1<<m)-1;i++)
 	{
 		if(f[i]!=n) continue;//当前状态根本到不了n，就直接下一个
 		check(i);//将当前的状态转成二进制数
 		int tot=0;
 		for(re int j=1;j<=m;j++)
 		if(c[j]==0) tot+=b[j];
        //如果没有被选择，那么就把它加上
 		if(tot>ans) ans=tot; 
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：jins3599 (赞：2)

思路比较妙的一道状压。

看到题解里面有很多用二分来优化复杂度的，其实没必要，多了一个log不是很优美。

我们完全可以通过预处理来切掉这道状压$dp.$

我们考虑设计方程$f(i)$代表，已经使用了集合$i$内的硬币，能买完的最多的物品。

我们考虑枚举$i$中每一个没有用过的硬币，然后再向后枚举看看他能够延申多少，复杂度$O(2^k*nk)$，对于本题的范围无法AC。

我们考虑优化一下，这个硬币在当前位置能向后延申多少位，是否可以预处理出来然后进行$O(1)$的查询？

考虑到整个序列都是整数，结果显然满足单调性，我们可以用$\text{two-pionters}$把这个进行$O(nk)$的预处理。

然后再进行查询的时候，我们的复杂度就骤降到了$O(k*2^k)$，因为瓶颈不是在预处理而是在$dp$中，其实跑的是要比二分快的。

$Code:$

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

int g[20][N] , k , n;// g(i,j) 代表第i个硬币从j开始能买的最多的东西 
int w[N] , c[N];
int f[(1 << 20) + 4]; // 选中状态为i的硬币，能到达的最右的物品 

int main () {
	scanf("%d %d" , &k , &n);
	for(int i = 1 ; i <= k ; i ++) scanf("%d" , w + i); // 硬币的价值 
	for(int i = 1 ; i <= n ; i ++) scanf("%d" , c + i); // 货物的价值 
	for(int i = 1 ; i <= k ; i ++) {
		int l = 1, r = 0;
		int rsum = 0;
		for(l = 1 ; l <= n ; l ++) {
			while(r <= n && rsum + c[r] <= w[i]) rsum += c[r ++];
			g[i][l] = r - l;
			rsum -= c[l];
		}
	}// two points 
//	for(int i = 1 ; i <= k ; i ++)
//		for(int j = 1 ; j <= n ; j ++) printf("g[%d][%d] = %d\n" , i , j , g[i][j]);
	for(int i = 0 ; i < (1 << k) ; i ++) {
		for(int j = 1 ; j <= k ; j ++) {
			if(i & (1 << (j - 1))) continue;
			f[i | (1 << (j - 1))] = min(n , max(f[i | (1 << (j - 1))] , f[i] + g[j][f[i] + 1]));
		}
	}
//	for(int i = 0 ; i < (1 << k) ; i ++) printf("f[%d] = %d\n" , i , f[i]);
	int ans = 0x3f3f3f3f;
	for(int i = 0 ; i < (1 << k) ; i ++) {
		if(f[i] == n) {
			int rsum = 0;
			for(int j = 1 ; j <= k ; j ++) {
				if(i & (1 << (j - 1))) rsum += w[j];
			}
			ans = min(ans , rsum);
		}
	}
	int tot = 0;
	for(int i = 1 ; i <= k ; i ++) tot += w[i];
	if(ans == 0x3f3f3f3f) puts("-1");
	else printf("%d\n" , tot - ans);
	return 0;
}
```

---

## 作者：InnovatorNZ (赞：2)

本代码和原置顶题解代码逻辑其实是一模一样的，不过又在关键地方加了些注释便于理解，并且我自认为我的这份代码的变量命名及使用比那份题解更清晰易懂。
另，注意，前缀和数组必须从1开始计数，否则会使得当选硬币状态为全不选时却发现仍然可以买东西(因为sum[0]!=0)，因此需保证sum[0]=0。否则会WA到你怀疑人生。
附代码:
```
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
#define maxn 100001
#define maxk 17
const int INF = 1<<30; 
int n,k;
int value[maxk], price[maxn], sum[maxn];
int maxans = -1;
int dp[1<<maxk];
//dp[i]表示当前硬币选择状态为i时，能买到的最大商品数 
inline bool ChoosedCurrent(int state, int current){ 	
return state & (1<<current);
} 
inline int StateNotChooseCurrent(int state, int current){ 	
return state ^ (1<<current);
} 
inline int find(int value){ 	
return upper_bound(sum+1, sum+n+1, value)-sum-1;
} 
int main(){ 	
cin>>k>>n;
for(int i=0;i<k;i++)  	
cin>>value[i]; 	
for(int i=1;i<=n;i++){  	
cin>>price[i];  
//求商品价格前缀和  	
sum[i] = sum[i-1]+price[i]; 	
}   	
for(int state=1; state<=(1<<k)-1; state++){  	
for(int current=0; current<k; current++){   	
if(ChoosedCurrent(state, current)){  
dp[state] = max(dp[state], find( \     	
sum[dp[StateNotChooseCurrent(state, current)]]+value[current]));    	
//在前缀和中查找第一个大于 sum[若不选该硬币我能买到的商品数]+value[当前硬币面额]    	
//find函数返回的值就是我们当前硬币状态所能买到的最大商品数   	
}  	
} 	
} 	
for(int state=1; state<=(1<<k)-1; state++){  	
if(dp[state]==n)	//买完了  	
{  
int ans=0;   	
for(int current=0; current<k; current++){    	
if(!ChoosedCurrent(state, current)){     	
//我们要的是剩余面额而非总花费，因此要加没选上的     	
ans += value[current];   
}   
}   	
maxans = max(ans, maxans);  
} 
}   	
cout<<maxans<<endl;   	
return 0;
}
```

---

## 作者：zx2003 (赞：2)

看到k<=16，状压dp不解释

需要预处理每个硬币从每个物品开始连续购买最多能购买到第几个。

```cpp
uses math;
var
 l:array[1..16,0..100010] of longint;
 f:array[0..1 shl 16-1] of longint;
 c:array[1..100000] of longint;
 co:array[1..16] of longint;
 i,w,j,n,k,s,ans,ss:longint;
begin
 readln(k,n);
 for i:=1 to k do
 begin
  readln(co[i]);
  inc(ss,co[i])
 end;
 for i:=1 to n do readln(c[i]);
 for i:=1 to k do
 begin
  w:=1;
  s:=0;
  for j:=1 to n do
  begin
   while (w<=n)and(s+c[w]<=co[i]) do
   begin
    inc(s,c[w]);
    inc(w)
   end;
   l[i,j]:=w-1;
   dec(s,c[j])
  end;
  l[i,0]:=l[i,1]
 end;    {
 for i:=1 to k do
 begin
  for j:=1 to n do write(l[i,j],' ');
```
writeln
```cpp
 end      }
 s:=1 shl k-1;
 ans:=1 shl 30;
 for i:=1 to s do
 begin
  w:=0;
  if i=4 then
  begin
   w:=w
  end;
  for j:=1 to k do
   if i and (1 shl (j-1))>0 then
   begin
    f[i]:=max(f[i],l[j,f[i xor (1 shl (j-1))]+1]);
    inc(w,co[j])
   end;
  if f[i]=n then ans:=min(ans,w)
 end;
 if ans=1 shl 30 then writeln(-1)
  else writelN(ss-ans)
end.

```

---

## 作者：lqhsr (赞：0)

## 这篇题解主要总结一下遇到的几个坑而且笔者自认为码风比较友好

先总结一下几个坑吧

```
1.查找当前货币能买多少货物时应用二分查找否则TLE

2.二分查找mem初始值为-1

3.f应初始化为-1而非0

4.最后应该找一遍所有可能的方案的最大值

5.找之前maxn初始值为-1
```

首先看完题目瞄一眼数据范围->16 显然是状压DP啦(套路)

于是考虑设状态,本来想设f[i][j]表示用了i个(二进制),买了j个货物后来一想不对啊,难道你可以用同一枚硬币多买一件货物难道你还去浪费他???

于是直接抛弃第二维

**用f[i]表示i状态下能最多买到多少物品(注意题目要求按顺序购买)**

于是欢快的打完了代码交上去23pts

下了第一个点一看是m太大了,**add函数太费时了**

**于是自然想到二分查找**

又码了一波交上去,没T但是WA了

于是用std拍出了一组小数据

**发现是没有找到最大值就输出了**

**于是枚举所有可能的方案取max**

交上去85pts WA on #4 #5

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int n,m,a[1000005],b[100005],f[233333],sum[100005];
int read(){
	int x=0;char ch=getchar();
	while(ch>'9'||ch<'0')ch=getchar();
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return x;
}
int add(int k,int now){
	int l=now+1,r=m-1,mem=0;
	while(l<=r){
		int mid((l+r)>>1);
		if(sum[mid]-sum[now]<=a[k]){mem=mid;l=mid+1;}
		else {r=mid-1;}
	}
	return mem;
}
	int maxn=0;
void print(int k){
	int ans(0);
	for(int i=0;i<n;i++){
		if((((k>>i)&1))==0){
			ans+=a[i];
		}
	}
	maxn=max(maxn,ans);
}
//f[i]表示i状态下买的最大编号是多少
signed main(){
	n=read(),m=read();
	for(int i=0;i<n;i++)a[i]=read();
	for(int i=0;i<m;i++){b[i]=read();sum[i]=sum[i-1]+b[i];}
	memset(f,-1,sizeof(f));
	sort(a,a+n);
	for(int i=0;i<(1<<n);i++){
		for(int j=0;j<n;j++){
			if(((i>>j)&1)){
				f[i]=max(f[i],add(j,f[i^(1<<j)]));
			}
		}
	}
	for(int i=0;i<(1<<n);i++){
		if(f[i]==m-1){
			print(i);
		}
	}
	if(maxn)cout<<maxn<<endl;
	else cout<<"-1"<<endl;
}
```

**是maxn的锅,如果答案为0,那个if就会判断为无解**

于是修改后交上去啦

## 终于AC啦

**然而就在这时,一个坏消息来了,在AC的同时,对拍程序停下来了**

我的程序貌似把几个货币拼起来买货物了

[详情戳我](https://www.luogu.org/discuss/show/162293)

再送大家一组更小的数据

```
3 3
71
622
234
84
97
91
```

**是mem的初始值的问题,如果这个货币一件也买不了返回值应为-1而非0(再次友情提示:下标从0开始)**

修改后对拍程序直到我写完这篇题解还没休息过~~~

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int n,m,a[1000005],b[100005],f[233333],sum[100005];
int read(){
	int x=0;char ch=getchar();
	while(ch>'9'||ch<'0')ch=getchar();
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return x;
}
int add(int k,int now){
	int l=now+1,r=m-1,mem=-1;
	while(l<=r){
		int mid((l+r)>>1);
		if(sum[mid]-sum[now]<=a[k]){mem=mid;l=mid+1;}
		else {r=mid-1;}
	}
	return mem;
}
	int maxn=-1,ans;
void print(int k){
	ans=0;
	for(int i=n-1;i>=0;i--){
		if((((k>>i)&1))==0){
			ans+=a[i];
		}
	}
	maxn=max(maxn,ans);
}
//f[i]表示i状态下买的最大编号是多少
signed main(){
	n=read(),m=read();
	for(int i=0;i<n;i++)a[i]=read();
	for(int i=0;i<m;i++){b[i]=read();sum[i]=sum[i-1]+b[i];}
	memset(f,-1,sizeof(f));
	sort(a,a+n);
	for(int i=0;i<(1<<n);i++){
		for(int j=0;j<n;j++){
			if(((i>>j)&1)){
				f[i]=max(f[i],add(j,f[i^(1<<j)]));
			}
		}
	}
	for(int i=0;i<(1<<n);i++){
		if(f[i]==m-1){
			print(i);
		}
	}
	if(maxn)cout<<maxn<<endl;
	else cout<<"-1"<<endl;
}
```

---

## 作者：Edward_Elric (赞：0)

## 思路

把题看成，可以随机选择商品购买，然后卡住了，后来一看发现商品是连续的。那么这就是个很基础（思博）的状压dp。一维的很容易想出来该怎么搞。设$f[s]$表示状态为$s$的最大的商品数。因为连续我们可以二分这个最大转移


使用$lowbit$优化。但常数较大，空间开销也稍大。（没什么卵用）。也只能谢谢水题才能过过日子
## 代码
```cpp
#include<bits/stdc++.h>
#define lowbit(x) (x&(-x))
using namespace std;
int f[1<<16];
int sum[100000+5],k[1<<17];
int n,m,st;
int ans=-1; 
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return x*f;
} 
int main(){
	n=read(),m=read();
	st=1<<n;
	for(int i=0;i<n;++i)k[1<<i]=read(),k[1<<n]+=k[1<<i];
	for(int i=1;i<=m;++i){
		int x=read();
		sum[i]=sum[i-1]+x;
	}
	for(int i=0;i<st;++i)
        for(int j=i,x=lowbit(j);j;j^=x,x=lowbit(j)){
			int s=i^x;
			int l=1,r=m,pos=0;
			while(l<=r){
				int mid=(l+r)>>1;
				if(sum[mid]<=sum[f[s]]+k[x]){
					l=mid+1;pos=mid;
			}
			else r=mid-1; 
		}
		f[i]=max(f[i],pos);
	  }
	for(int i=0;i<(1<<n);++i){
		if(f[i]==m){
			int res=k[1<<n];
			for(int j=i,x=lowbit(j);j;j^=x,x=lowbit(j))
			res-=k[x];
			ans=max(res,ans); 
		}
	}
	printf("%d\n",ans);
	return 0;
}
```


---

