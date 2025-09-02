# Magnets

## 题目描述

This is an interactive problem.

Kochiya Sanae is playing with magnets. Realizing that some of those magnets are demagnetized, she is curious to find them out.

There are $ n $ magnets, which can be of the following $ 3 $ types:

- N
- S
- - — these magnets are demagnetized.

Note that you don't know the types of these magnets beforehand.

You have a machine which can measure the force between the magnets, and you can use it at most $ n+\lfloor \log_2n\rfloor $ times.

You can put some magnets to the left part of the machine and some to the right part of the machine, and launch the machine. Obviously, you can put one magnet to at most one side (you don't have to put all magnets). You can put the same magnet in different queries.

Then the machine will tell the force these magnets produce. Formally, let $ n_1,s_1 $ be the number of N and S magnets correspondently on the left and $ n_2,s_2 $ — on the right. Then the force between them would be $ n_1n_2+s_1s_2-n_1s_2-n_2s_1 $ . Please note that the force is a signed value.

However, when the absolute value of the force is strictly larger than $ n $ , the machine will crash into pieces.

You need to find all magnets of type - (all demagnetized ones), without breaking the machine.

Note that the interactor is not adaptive. The types of the magnets are fixed before the start of the interaction and do not change with queries.

It is guaranteed that there are at least $ 2 $ magnets whose type is not -, and at least $ 1 $ magnet of type -.

## 说明/提示

The empty lines in the sample are just for you to better understand the interaction process. You're not required to print them.

In the sample, the types of the magnets are NN--.

At first, you put the third magnet on the left and the fourth one on the right. Both of them have type -, thus no force is produced.

Then you put the first magnet on the left and the second and third one on the right. The third magnet has type -, while the other two magnets are of type N, so the force produced is $ 1 $ .

In the following two queries, the force is $ 0 $ since there is only a magnet with property - on the right.

Then we can determine that the magnets of type - are the third and the fourth one, so we should print ! 2 3 4 and exit.

## 样例 #1

### 输入

```
1
4



0



1



0



0```

### 输出

```
? 1 1
3
4

? 1 2
1
2 3

? 1 1
1
4

? 1 1
1
3

! 2 3 4```

# 题解

## 作者：AC_Evil (赞：9)

## Problem

你有 $n$ 个磁铁，每个磁铁有属性，为下列三种之一

- `N`、`S`、`-`（表示无磁性）

一次操作你可以选择不相交的两个磁铁的子集 $S$ 和 $T$，假设 $S$ 中有 $n_1$ 个 `N`，$s_1$ 个 `S`， $T$ 中有 $n_2$ 个 `N`，$s_2$ 个 `S`。这些你都不知道。通过交互库你可以得到 $n_1n_2-n_1s_2-n_2s_1+s_1s_2$（化简得到：$(n_1-s_1)(n_2-s_2)$ ）。得到的数值可能 $<0$。

你可以花费不超过 $n+\lfloor\log_2n\rfloor$ 次操作找出所有没有磁性的磁铁。

多组数据 $T\leq 100$，每次 $n\leq 2000$，$\sum n\leq 2000$。**保证至少两个有磁极的磁铁和一个无磁极的磁铁**。

## Sol

如果我们能找到一个有磁极的磁铁，那么问题将非常简单。

然而要想找出一个有磁极的磁铁，必须借助另外至少一个有磁极的磁铁。

假象一种极端的边界：如果只有两块磁铁有磁极怎么办？只能硬着头皮一个一个找呗。

于是得到一种方案：每次查询 $S=\{i\}$，$T=\{1,\cdots,i-1\}$。当遇到第二块有磁极的磁铁之前，答案一定为 $0$（因式有一项必为 $0$）。当 $i$ 是第二块有磁极的磁铁时，答案会变成 $\pm 1$，以此我们就能找出一块有磁极的磁铁了！

利用这块磁铁找出 $>i$ 位置的无磁性的磁铁，这样总查询次数为 $n-1$。

但是第一块有磁性的磁铁我们还没有找到，如果找到了剩下的都是无磁性的磁铁。这时不必要一次一次找，~~观察题目~~使用技巧知道要二分找出来。于是继续构造 $S=\{i\}$，$T=\{1,\cdots,j\}$ 来判断前缀 $j$ 的磁铁中有没有有磁性的磁铁，然后二分，这部分查询次数为 $\lceil\log_2n\rceil$。

综上，总次数 $=n-1+\lceil\log_2n\rceil\leq n+\lfloor\log_2n\rfloor$。时间复杂度为 $\mathcal O(Tn^2)$。

## Code

```cpp
#include <bits/stdc++.h>
using std::vector;
const int N = 2005;
int T, n, F;
int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 2; i <= n; i++) {
			printf("? 1 %d\n%d\n", i - 1, i);
			for (int j = 1; j < i; j++) printf("%d ", j);
			puts(""); fflush(stdout);
			scanf("%d", &F);
			if (F) {
				vector<int> ans;
				for (int j = i + 1; j <= n; j++) {
					printf("? 1 1\n%d\n%d\n", i, j);
					fflush(stdout);
					scanf("%d", &F);
					if (!F) ans.push_back(j);
				}
				int l = 1, r = i - 1;
				while (l <= r) {
					int mid = l + r >> 1;
					printf("? 1 %d\n%d\n", mid, i);
					for (int j = 1; j <= mid; j++) printf("%d ", j);
					puts(""); fflush(stdout);
					scanf("%d", &F);
					if (F) r = mid - 1; else l = mid + 1;
				}
				for (int j = 1; j < i; j++)
					if (j != r + 1) ans.push_back(j);
				printf("! %d ", ans.size());
				for (int j = 0; j < ans.size(); j++) printf("%d ", ans[j]);
				puts(""); fflush(stdout); break;
			}
		}
	}
	return 0;
}
```

---

## 作者：serverkiller (赞：7)

这里是官方题解。

考虑每次询问一侧放第 $i(i>1)$ 颗磁铁，一侧放之前的 $i-1$ 颗磁铁。

这样，你问到的第一个非 $0$ 值一定表示这颗磁铁是第 $2$ 颗有磁性的。

你可以借此找到所有有磁性的磁铁：第 $1$ 颗可以二分，后面的磁铁可以通过与当前找到的有磁性的磁铁询问来判断。

询问次数 $n-1+\lceil \log_2 n \rceil$，在限制的 $n + \lfloor \log_2n \rfloor$ 范围内。

---

## 作者：gyh20 (赞：3)

好久没写题解了。

假设我们已经知道某一块磁铁有磁性，那么我们可以进行 $n-1$ 次询问找到其他磁铁是否有磁性，也就是说，我们需要在 $\log$ 的次数找到一个有磁性的点。

观察到限制答案不能超过 $n$，可以猜想有一边只放一个点。

每次询问 $i$ 和 $i+1\sim n$，如果返回值非 $0$ 则 $i$ 处磁铁有磁性。

但考虑一种特殊情况： $\text{--N--NS}$，此时询问 $2$ 时虽然这个地方有磁铁，但没有找到。

也就是说，在第一个非 $0$ 点之前，还可能有一个磁铁，此时可以二分，询问非零点 $pos$ 与区间 $1\sim mid$ 得到答案。

总次数 $n+\lceil{\log_2n\rceil}$，多了一次。

注意到知道 $1\sim n-1$ 的答案后可以直接算出 $n$ 的答案，于是询问次数减少了 $1$。

```cpp
#include<bits/stdc++.h>
#define re register
using namespace std;
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
}
const int M=998244353;
inline void add(re int &x,re int y){(x+=y)>=M?x-=M:x;}
inline int ksm(re int x,re int y){
	re int s=1;
	while(y){
		if(y&1)s=1ll*s*x%M;
		x=1ll*x*x%M,y>>=1;
	}
	return s;
}
struct edge{int to,next;}e[2000002];
int t,n,m,a[1000002],cnt,head[1000002],b[1000002],lst,ans[1000002],vis[2002],sss,VV;
inline int ask(re int x,re int l,re int r){
	printf("? %d %d\n",1,r-l+1);
	printf("%d\n",x);
	for(re int i=l;i<=r;++i)printf("%d ",i);
	puts("");
	fflush(stdout);
	re int s=0;
	scanf("%d",&s);
	++sss;
	if(sss>n+log2(n))exit(1);
	return s;
}
inline void print(re int pos){
	re int num=0;
	ans[++num]=pos;
	if(pos^lst)ans[++num]=lst;
	re int xx=0;
	for(re int i=lst+1;i<n;++i){
		re int xxx=ask(lst,i,i);
		xx+=xxx;if(xxx!=0)ans[++num]=i;
	}
	if(xx!=VV)ans[++num]=n;
	memset(vis,0,sizeof(vis));
	for(re int i=1;i<=num;++i)vis[ans[i]]=1;
	num=0;
	for(re int i=1;i<=n;++i)if(!vis[i])ans[++num]=i;
	printf("! %d ",num);
	for(re int i=1;i<=num;++i)printf("%d ",ans[i]);
	puts("");
	fflush(stdout);
}
inline void bs(re int l,re int r){
	re int pos=0;
	while(l<=r){
		re int mid=l+r>>1;
		if(ask(lst,1,mid)!=0)r=mid-1,pos=mid;
		else l=mid+1;
	}
	if(!pos)print(lst);
	else print(pos);
}
signed main(){
	t=read();
	while(t--){
		sss=0;
		n=read();
		re int pos=1,la=ask(1,2,n);
		if(la!=0){VV=la;
			lst=1;
			print(1);
			continue;
		}
		for(re int i=2;i<=n;++i){
			re int x=ask(i,i+1,n);VV=x;
			lst=i;
			if(x!=0){bs(1,i-1);break;}
		}
	//	printf("aaa%d\n",sss);
	}
}

```


---

## 作者：EXODUS (赞：2)

# Part 1：前言
纪念一下自己在考场上过的第一道交互题。

~~感谢洛谷翻译让我成功看懂了题面。~~

下文中，我们把有磁性的磁铁称为 **好磁铁** ,反之则是 **坏磁铁**
# Part 2：思路
首先我们可以 ~~瞪着样例看两眼然后口胡~~ 推出两个个性质，对于任意的情况，磁力检测仪器返回值不为 $0$ 的必要条件是 $([n_1\neq 0] \vee [s_1\neq 0])\land([n_2\neq 0] \vee [s_2\neq 0])$,且在 $n_1$ 和 $s_1$ 中有一个 $1$，一个 $0$，$n_2$ 和 $s_2$ 中有一个 $1$，一个 $0$ 的情况下一定返回值不为 $0$。

那么有一个很 navie 的想法是找出一块有磁力的磁铁，然后拿它跟其它所有挨个比较，返回值为 $0$ 则说明该磁铁坏掉了。

如果形式化的表述，设第 $i$ 块磁铁是好的为 $b_i=1$，则有
$$\forall j\in [1,n],j\neq i,b_j=1\Leftrightarrow query(i,j)\neq 0,b_i=1$$

那么现在的问题就是怎么找出一个有磁力的磁铁。

看一看第一个性质，我们发现，可以考虑每次对于第 $i$ 块磁铁，把 $j\in[1,i-1],j\neq i$ 的磁铁 $j$ 丢到左盘，把 $i$ 丢到右盘，如果返回值是 $1$ 或 $-1$，则说明该磁铁一定是好的。

考虑一下找到磁铁的位置，对于第一块好的磁铁，返回值一定为 $0$（有 $n_1=s_1=0,[n_2=1] \vee [s_2=1]$），而对于第二块，才会返回值为 $1$。

那么我们可以考虑先找到第二块，然后记第二块位置为 $pos$ ，把 $i\in[pos+1,n]$ 的磁铁 $i$ 与它比较，然后就可以判断出 $pos$ 到 $n$ 的坏磁铁数量与位置。

分析一下当前使用次数，找到位置在 $pos$ 的好磁铁需要的比较次数是 $pos-1$ ，在找到后比较次数是 $n-pos$，共用了 $n-1$ 次。

~~好的现在压力来到了找第一块磁铁这里。~~

~~我会暴力找！~~

通过 ~~理性分析~~ 看到 $n+\lfloor\log_2n\rfloor$ 的次数限制，容易想到二分算法。

~~经过漫长的口胡~~，我们想到了第一个结论。

>对于任意的情况，磁力检测仪器返回值不为 $0$ 的必要条件是 $([n_1\neq 0] \vee [s_1\neq 0])\land([n_2\neq 0] \vee [s_2\neq 0])$

如果第一块好磁铁位置为 $pos'$，那么对 $pos'$ 以前的磁铁和一块好磁铁进行询问，答案一定为 $0$。

形式化的说，设第 $k$ 块磁铁是第一块满足 $b_k=1$ 的磁铁，第 $l$ 块磁铁是第二块满足 $b_l=1$ 的磁铁，则有

$$\forall j\in [1,k),query(\{1,2,...,j\},k)=0$$
$$\forall j\in [k,l),query(\{1,2,...,j\},k)\neq0$$

那么对第一块磁铁位置进行二分即可（这一块如果还不懂可以参照代码），次数为 $O(\log_2 n)$（注：由于本人太菜，不知道这里是下取整还是上取整，望评论区指出，但是由于上文询问次数只有 $n-1$，所以这里无论上下取整总次数均小于等于 $n+\lfloor\log_2 n\rfloor$） 。

最后分析一下检测仪会不会爆掉，由于每次左右盘最多有一块好磁铁，所以返回值只会是 $\pm1$，肯定炸不掉。

# Part 3：代码
```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/priority_queue.hpp>
#define re register
#define il inline
#define pb push_back
#define POS(i,l,r) for(re int i(l);i<=r;i=-~i)
#define REV(i,r,l) for(re int i(r);i>=l;i--)
#define ls(k) k<<1
#define rs(k) k<<1|1
#define np pair<int,int>
#define mp make_pair
#define nb(k) bitset<k>
#define rev reverse
using namespace std;
using namespace __gnu_pbds;
typedef long long ll;
il int read(){
	int ans=0,flag=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')flag=-1;ch=getchar();}
	while(isdigit(ch))ans=(ans<<3)+(ans<<1)+(ch^48),ch=getchar();
	return ans*flag;
}
il string reads(){
	string ans="";char ch=getchar();
	while(!isalpha(ch))ch=getchar();
	while(isalpha(ch))ans+=ch,ch=getchar();
	return ans;
}
il char readc(){
	char ch=getchar();
	while(!isalpha(ch))ch=getchar();
	return ch;
}
il int sqr(int x){return x*x;}
void write(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)write(x/10);
	putchar(x%10+'0');
	return;
}
int t;
int n,posi;
int a[100010];
int cnt;
int main(){
	t=read();
	while(t--){
		n=read();cnt=0;
		for(int i=1;i<=n;i++){
			printf("? %d %d\n",n-1,1);
			for(int j=1;j<=n;j++){
				if(j!=i)printf("%d ",j);
			}
			puts("");
			printf("%d\n",i);
			fflush(stdout);
			int x=read();
			if(x!=0){posi=i;
				for(int j=i+1;j<=n;j++){
					printf("? 1 1\n%d\n%d\n",i,j);
					fflush(stdout);
					int y=read();
					if(y==0){
						a[++cnt]=j;
					}
				}
				break;
			}
		}
		int l=1,r=posi-1,ans=0;
		while(l<=r){
			int mid=l+r>>1;
			printf("? %d %d\n%d\n",1,mid,posi);
			for(int i=1;i<=mid;i++){
				printf("%d ",i);
			}
			puts("");
			fflush(stdout);
			int y=read();
			if(y==0) l=mid+1;
			else ans=mid,r=mid-1;
		}
		while(!ans);
		printf("! %d ",posi-1-(bool)(ans)+cnt);
		//cout<<ans<<endl;
		for(int i=1;i<posi;i++){
			if(i!=ans)printf("%d ",i);
		}
		for(int i=1;i<=cnt;i++){
			printf("%d ",a[i]);
		}
		fflush(stdout);
	}
	return 0;
}

```

# Part 4：后文
~~啊啊啊啊啊啊考场上因为 ans 写错罚了一发啊啊啊啊。~~

求个赞呗（逃~

# $εnd$

---

## 作者：lalaouye (赞：0)

首先这题的式子藏了个比较显然的因式分解，这是必须要注意到的，即 $(n_1-s_1)(n_2-s_2)$。

不妨将原问题看成只有 $1/-1,0$ 的序列，题目要求找到所有的 $0$。

然后我就走偏了。这题看起来非常像先 $\log n$ 次找到一个非 $0$ 的数，再线性 check。并且我忘了乘起来绝对值有限这件事，我直接开冲随机化然后被卡飞了。

于是便转换思路，考虑对于每个数与其它所有数做一次查询所带来的信息量，发现信息量巨大，大多数情况下如果结果为 $0$ 则这个数就是 $0$，对于序列和不为 $1$ 或 $-1$ 的序列直接做就做完了。但如果和为 $1$ 或 $-1$ 咋办？我们在每次查询时直接删掉之前查询结果为 $0$ 的位置即可。这样在这些数中顶多只有一个数有值，其它全是 $0$，可以二分去找它。

但是你发现你超限了，这个题的 $\log n$ 是向下取整的。那么我们希望减少一步。发现我们可以根据前面的信息推测出 $n$ 位置是否为 $0$，然后分讨推测即可。

---

