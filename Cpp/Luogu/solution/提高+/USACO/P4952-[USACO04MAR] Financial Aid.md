# [USACO04MAR] Financial Aid

## 题目描述

   人类可以选择很多大学，而奶牛们却没学可上。为解决这个问题，贝西和她的伙伴们创立了一所奶牛大学，取名为哞哞大学。

   为了选拔优秀学生，她们发明了一种奶牛学术能力测试（简称 CSAT） ，这种测试的分数异常精确，每头奶牛的成绩可以用$0$到$2×10^9$之间的一个整数表示，而且可以保证每头奶牛的分数都不同。

   哞哞大学的学费很贵，奶牛们表示负担不起，他们都各自申请了奖学金。政府并没有为奶牛准备奖学金，所有的预算都必须要从学校有限的助学基金中扣除（设基金总额为F)。

   哞哞大学有N间宿舍，N是一个奇数，所以贝西只能接受N头奶牛的申请，她发誓不会让入学的奶牛少于N。此外，她希望新生的 CSAT 成绩表现优异，她以中位数来衡量新生的总体水平。所谓中位数，就是排序后处在最中间的分数，比如3,8,9,7,5的中位数是7。

   今年，共有C头奶牛申请入学，给定每头奶牛的 CSAT 成绩和申请的奖学金数目，以及学校可赞助的总额，确定贝西接受哪些奶牛的申请才可以使成绩的中位数达到最大。

## 说明/提示

贝西接受 CSAT 分数为 5，35，50 的奶牛的申请，中位数为 35，需支付的奖学金总额为18 + 30 + 21 = 69

## 样例 #1

### 输入

```
3 5 70
30 25
50 21
20 20
5 18
35 30```

### 输出

```
35```

# 题解

## 作者：go_bananas (赞：11)

~~这显然是一道关于中位数的水题。~~
# 那么简化问题及为：
要求选出的N头牛的成绩的中位数尽可能大，我们可以考虑依次讨论每头奶牛的成绩是否适合作为中位数。

## 1.先把牛们的分数由小到大排序
那么这个中位数显然在[n/2+1.....c-n/2]中。

## 2.若k位于这个范围[n/2+1...c-n/2]，那么Score[k]是否是一个合理的中位数呢？

在[1...k-1]间定要选出n/2头牛，我们希望选总学费尽量少n/2头奶牛，设该学费总额为Left[k]（left[k]表示在k这头牛左边满足n/2头牛的钱的最小的总和，right同理)

在[k+1...c]间定也要选出n/2头牛，我们也希望选总学费尽量少n/2头奶牛，设该学费总额为Right[k]

如果满足**left[k]+right[k]+money[k]<=F**

那么这就是一种合理的情况

最终找出满足条件 **Left[k]+Right[k]+Money[k]<=F 的最大的一个k，它对应的Score[k]即为答案。**
## 3.求[n/2+1...c-n/2]中每个数对应的left[ ]和right[ ]

建立一个大根堆，把最左边的n/2头牛所要的费用存到堆里面，用sum记下总和。
	设当前讨论到了第k头牛

if(money[k]<堆顶元素)就用money[k]把堆顶元素换掉

继续讨论下一头牛


------------

## right[ ]的求法同left[ ]!

# AC代码
------------

```
#include<stdio.h>
#include<bits/stdc++.h>
using namespace std;
struct node{int fen,money,left,right;}cow[100005];
int C,N,F;
priority_queue<int>q;
bool cmp(node a,node b){return a.fen==b.fen?a.money<b.money:a.fen<b.fen;}
void init(){
	scanf("%d%d%d",&N,&C,&F);
	for(int i=1;i<=C;i++)scanf("%d%d",&cow[i].fen,&cow[i].money);
	sort(cow+1,cow+1+C,cmp); //先要排序
}
void LEFT(){//左边
	int sum=0;
	for(int i=1;i<=N/2;i++){
		q.push(cow[i].money);
		sum+=cow[i].money;
	}//最左边的
	for(int i=N/2+1;i<=C-N/2;i++){
		int t=q.top();
		cow[i].left=sum;
		if(cow[i].money<t){
			q.pop();
			sum=sum-t+cow[i].money;
			q.push(cow[i].money);
		}
	}
	while(!q.empty())q.pop();
}
void RIGHT(){//右边
	int sum=0;
	for(int i=C;i>=C-N/2+1;i--){
		q.push(cow[i].money);
		sum+=cow[i].money;
	}//最右边的
	for(int i=C-N/2;i>=N/2+1;i--){
		int t=q.top();
		cow[i].right=sum;
		if(cow[i].money<t){
			q.pop();
			sum=sum-t+cow[i].money;
			q.push(cow[i].money);
		}//互换
	}
}
int main(){
	int ans=-1;//赋值为-1
	init();
	LEFT();
	RIGHT();
	for(int i=C-N/2;i>=N/2+1;i--){
		if(cow[i].left+cow[i].right+cow[i].money<=F){
			ans=cow[i].fen;
			break;
		}
	}
	printf("%d",ans);
}

```


------------



---

## 作者：ny_zht (赞：6)

一道贪心的题目。

我们通过样例分析就可以简化一下这道题其实就是让我们在 $ C $ 个奶牛中选出 $ N $ 个奶牛，在总花费 $\le F$ 的情况下使得这 $N$ 个牛的中位数最大。

## 分析

首先我们可以先把这 $ C $ 头奶牛按照成绩先从小到大排个序，然后看以第 $i$ 个奶牛作为中位数时，他的最小花费是多少。怎么看呢？我们可以以 $i$ 为分界点，$i$ 左边选 $\frac{ N }{ 2 }$ , $i$ 的右边选 $\frac{ N }{ 2 }$，在中位数一定的情况下在左边那部分中选花费最小的 $\frac{ N }{ 2 }$ 个奶牛，用数组 $L_{ i }$ 来存储，同理，右边的 $R_{i}$ 也是这么的，然后我们从大到小讨论两边的花费加起来在加上中位数 $i$ 的和如果是小于 $F$ 的话那么第一个满足条件的就是我们的答案。

## 具体实现

我们可以用一个大根堆，里面存当前的奶牛，如果出现了更优的奶牛，我们就可以把队首那个最差的奶牛踢出去，把更优的奶牛放入大根堆。举个例子，假设现在堆里有 $ 10 $ 和 $8$ 两头奶牛，接着来了一头 $ 7 $ 的奶牛，那么我们就可以把当前在堆顶的 $ 10 $ 踢出去，把更优的 $ 7 $ 放进来，假设又来了个 $ 11 $ 此时，$ 11 $ 不够优那么就不能放入，最后答案就是 $L_{i} + R_{i} + a_{ i }.money$。
![](https://cdn.luogu.com.cn/upload/image_hosting/b9uezew5.png)![](https://cdn.luogu.com.cn/upload/image_hosting/60lebuq3.png)

## AC 代码

```cpp
#include<cstdio>
#include<iostream>
#include<queue>
#include<algorithm>
#define ll long long
using namespace std;
int n,c,f,ans=-1; 
struct node{
	int cast,money;
}a[100010];
int l[100010],r[100010];
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return f*x;
}
inline void write(int x) {
	if(x<0)putchar('-'),x=-x;
	if(x>9)write(x/10);
	putchar(x%10+'0');
}
bool cmp(node a,node b){
	return a.cast<b.cast;
}
int main(){
	n=read(),c=read(),f=read();
	for(int i=1;i<=c;i++){
		a[i].cast=read(),a[i].money=read();
	}
	sort(a+1,a+1+c,cmp);
	priority_queue<int>q;
	int sum1=0,sum2=0;
	int i;
	for(i=1;i<=n/2;i++){//先将前n/2入堆
		q.push(a[i].money);
		sum1+=a[i].money;//当前的总和
	}
	for(i=n/2+1;i<=c-n/2;i++){
		l[i]=sum1;			
		if(q.top()>a[i].money){//如果当前的比堆顶更优就进行替换
			sum1-=q.top();
			sum1+=a[i].money;			
			q.pop();
			q.push(a[i].money);
		}
	} 
	priority_queue<int>p;//同理求R[i]
	for(i=c;i>=c-n/2+1;i--){
		p.push(a[i].money);
		sum2+=a[i].money;
	}
	for(i=c-n/2;i>=n/2+1;i--){
		r[i]=sum2;	
		if(p.top()>a[i].money){
			sum2=sum2-p.top()+a[i].money; 			
			p.pop();
			p.push(a[i].money);
		}		
	}
	for(i=c-n/2;i>=n/2+1;i--){
		if(l[i]+r[i]+a[i].money<=f){
			printf("%d",a[i].cast);	
			return 0;
		}
	}
	write(-1);
	return 0;
}
```

---

## 作者：Tou_ch (赞：4)

一个简单的~~乱搞~~做法

## 分析

首先我们可以得知，一个序列的中位数与中位数后面的数是无关的。也就是说，无论这个序列是 $[5, 3, 1]$ 还是 $[5, 3, 2]$ 还是 $[5, 3, 3]$ ，中位数都不变。换到这道题，我们可以发现，我们选n头奶牛，那么，后 $\lfloor\frac n 2\rfloor$ 个数是无关紧要的，那么我们怎么选这 $\lfloor\frac n 2\rfloor$ 个数呢？很显然，我们选要钱最少的，这样可以留出钱选前面的优质奶牛。接着把选了的奶牛的钱置为 $0$ ，并扣除我们的总预算。

接着，前 $\lceil\frac n 2\rceil$ 个又该怎么选呢？我们可以先从按成绩高往低排序后选，如果没超预算，那么显然最后选的第 $\lceil\frac n 2\rceil$ 个奶牛的成绩就是最优的。如果超了呢？那么我们知道第 $\lceil\frac n 2\rceil$ 的奶牛作为中位数是不可行的，因此最大也就是第 $(\lceil\frac n 2\rceil+1)$ 个。接着我们看看减去前面选了的最贵的奶牛的钱，再加上第 $(\lceil\frac n 2\rceil+1)$ 个的钱，如果没超，那么就是最优的。如果超了，那我们看看前面最贵的奶牛是否比第 $(\lceil\frac n 2\rceil+1)$ 个奶牛更贵，如果是，那么我们踢出最贵的那头，加入 $(\lceil\frac n 2\rceil+1)$ 的奶牛，接着考虑第 $(\lceil\frac n 2\rceil+2)$ 头奶牛……以此类推。

最后，无解怎么判呢？显然，我们看看按最便宜的选能不能选到 $n$ 头，如果能，那么有解，如果不能，直接输出 $-1$ 即可。

## 参考代码
```cpp
#include <bits/stdc++.h>

using namespace std;

struct cow {
	int CSAT, money;
	bool selected = false;
} cows[100001];

int n, c, f;


int main() {
	scanf("%d%d%d", &n, &c, &f);
	for(int i = 1; i <= c; i++) {
		scanf("%d%d", &cows[i].CSAT, &cows[i].money);
	}
	auto cmp1 = [&](const cow &a, const cow &b) -> bool {return a.money < b.money;};
	sort(cows + 1, cows + c + 1, cmp1); //谁更便宜谁排前面
	int t = 0;
	for(int i = 1; i <= n; i++) {
		t+=cows[i].money;
		if(t > f) {
			printf("-1"); //无解
			return 0;
		}
	}
	for(int i = 1; i <= n / 2; i++) {
		cows[i].selected = true;
		f-=cows[i].money;
		cows[i].money=0;
	} //选最便宜的(n/2)头，腾出预算
	auto cmp2 = [&](const cow &a, const cow &b) -> bool {return a.CSAT > b.CSAT;};
	sort(cows + 1, cows + c + 1, cmp2);
	int cost = 0;
	int ans;
	for(int i = 1; i <= n / 2 + 1; i++) {
		cost+=cows[i].money;
		ans=cows[i].CSAT;
		cows[i].selected=true;
	} //尝试选成绩最好的
	if(cost <= f) { //如果能行
		printf("%d", ans);
		return 0;
	} else { //否则
		for(int i = n/2+2; i <= c; i++) { //往后枚举
			int maxn = -1;
			int maxi;
			for(int j = i - 1; j >= 1; j--) {
				if(cows[j].money > maxn && cows[j].selected) {
					maxn = cows[j].money;
					maxi = j;
				}
			} //找出前面最贵的
			if((cost - maxn + cows[i].money) < f) {
				printf("%d", cows[i].CSAT); //如果踢出最贵的，加入第i头能行
				return 0;
			} else {
				if(cost > (cost - maxn + cows[i].money)) {
					cost = cost - maxn + cows[i].money;
					cows[maxi].selected = false;
					cows[i].selected = true;
				} //看看能不能缩缩预算
			}
		}
	}
	return 0;
}	
```


---

## 作者：末然Ender (赞：2)

# 题解：P4952 [USACO04MAR] Financial Aid

省流：有 $c$ 头牛，每头牛都有一个价值 $C_i$ 和一个费用 $Q_i$，选费用和不超过 $f$ 的 $n$ 头牛，使得这些牛价值的中位数最大。

## 思路

~~水题，建议降黄，听说之前还是个紫，而且你谷还有一个一模一样的题？~~

观察到 $c$ 很小只有 $10^5$，我们考虑可以暴力枚举每一个可能成为中位数的牛作为中位数，然后在其更大更小的牛里各选 $\lfloor \frac n2 \rfloor$ 头花费最小的牛，如果花费在 $f$ 以内，就记录一下这头牛的价值取最大值即可。

所以我们将所有的牛以价值 $C_i$ 进行排序，然后用大根堆分别维护每个点左边和右边的最小的 $\lfloor \frac n2 \rfloor$ 头牛的费用和，记作 $lt_i$ 和 $rt_i$，如果发现堆里元素个数超过了 $\lfloor \frac n2 \rfloor$，就将费用最大的牛即堆顶弹出，这样就能保证堆里存在的是费用最小的 $\lfloor \frac n2 \rfloor$ 头牛。

然后我们不难发现排完序后只有第 $\lfloor \frac n2 \rfloor+1$ 到第 $c-\lfloor \frac n2 \rfloor$ 头奶牛可能作为这 $n$ 个奶牛的中位数，将这些奶牛遍历，初始 $ans=-1$ ，如果发现遍历到一个奶牛 $i$ 的时候 $lt_{i-1}+Q_i+rt_{i+1} \le f$，那么就令 $ans=\max\{ ans,C_i \}$，最后输出答案即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std; 
template<typename T>
void read(T& x){x=0;char ch=getchar();long long f=1;while(!isdigit(ch)){if(ch=='-')f*=-1;ch=getchar();}while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}x*=f;}
template<typename T,typename... Args>
void read(T& first,Args&... args){read(first);read(args...);}
template<typename T>
void write(T arg){T x=arg;if (x<0){putchar('-');x=-x;}if(x>9){write(x/10);}putchar(x%10+'0');}
template<typename T,typename... Args>
void write(T arg,Args... args){write(arg);if(sizeof...(args) !=0){putchar(' ');write(args...);}}
typedef long long ll;
const int N=2e5+5;
ll n,c,f; 
struct cows{
	ll scr,cst;
	friend bool operator<(cows a,cows b){
		return a.scr<b.scr;
	}
}a[N];
ll lt[N],rt[N];
priority_queue<ll> q,q1;
int main(){
	read(n,c,f);
	for(int i=1;i<=c;i++){
		read(a[i].scr,a[i].cst);
	}
	sort(a+1,a+1+c);
	for(int i=1;i<=c;i++){
		lt[i]=lt[i-1]+a[i].cst;
		q.push(a[i].cst);
		if(q.size()>n/2){
			lt[i]-=q.top();
			q.pop();
		}
	}
	
	for(int i=c;i>=1;i--){
		rt[i]=rt[i+1]+a[i].cst;
		q1.push(a[i].cst);
		if(q1.size()>n/2){
			rt[i]-=q1.top();
			q1.pop();
		}
	}
	ll ans=-1;
	for(int i=n/2+1;i<=c-n/2;i++){
		if(lt[i-1]+rt[i+1]+a[i].cst<=f){
			ans=max(ans,a[i].scr);
		}
	}
	write(ans);
	
	return 0;
}

```

---

## 作者：离散小波变换° (赞：1)

## 题解

这里提供一个比较简单，容易实现的**二分**做法。

由于我们希望在花费的金额最少的情况下，让中位数最大，那么我们可以**直接二分**这个中位数，然后想办法计算出这个中位数下最少的钱。一个容易想到的做法是，对于二分的中位数 $x$，将超过它的所有数排个序，不超过它的所有数再排一个序，两边分别取 $\frac{1}{2}n$ 个最小值。但仔细想想，这样对吗？

但正如 @Kewth 神仙所说，可能存在某两个方案，其中一个**中位数更大但花费更小**（也就不满足单调性了）。因为可能存在这样一种情况：某个 $\verb!CSAT!$ 值**不低于** $x$ 的奶牛（不妨称为优等生），所需的奖学金**低于**另外一个 $\verb!CSAT!$ 值低于 $x$ 的奶牛（不妨称为劣等生）。因此，我们选择了劣等生，反而花费了更多钱。

具体解决办法很简单：把多余的优等生“滥竽充数”填补到劣等生里，重新排序。

可能你会有疑问：这样选出来的方案，它的中位数不就大于 $x$ 了吗？事实确实如此。但是当 $x$ 取得最大值时，**必然存在这样的合法方案**（否则，我们总能取一个更大的 $x$）。因为这种二分方法是满足单调性的。随着 $x$ 的不断增大，优等生的条件变得更加苛刻，于是优等生的价格越来越贵；而劣等生本来就是用来填补价格空位的。优等生价格上涨，表现在决策上就是本来最贵的劣等生（或者拉来替补的优等生）被换成了最贵的优等生。

当然，还有一些细节。如果我们能选出的优等生还没有 $\frac{n}{2}+1$ 个，那么显然选不出这么多人；我们先把所有牛按照费用从小到大排序后，就不需要二分后再进行排序了。此外，下方代码直接二分了中位数的值而非按照  $\verb!CSAT!$ 值排序后，取得中位数的牛的编号，但可以证明这样没有问题。

时间复杂度 $\mathcal O(n\log w)$，常数应该小于平衡树和堆。

此外，由于作者的个人原因（指到今天还不会写纯正的二分……）所以下面的代码其实是倍增写法（或者说是倍减？）但是 $\verb!check!$ 函数与一般的二分相同。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define up(l,r,i) for(int i=l,END##i=r;i<=END##i;++i)
#define dn(r,l,i) for(int i=r,END##i=l;i>=END##i;--i)
using namespace std;
const int MAXN=2e5+3;
int n,c,f,p,C[MAXN],Q[MAXN],I[MAXN]; bool T[MAXN];
bool chk(int x){
    int w=0,t=0; memset(T,0,sizeof(T));
    up(1,c,i) if(C[I[i]]>=x &&t<n/2+1) T[i]=1,w+=Q[I[i]],++t;
    if(t<n/2+1) return false; t=0;
    up(1,c,i) if(T[i]==false&&t<n/2  )        w+=Q[I[i]],++t;
    return w<=f;
}
int qread(){
    int w=1,c,ret;
    while((c=getchar())> '9'||c< '0') w=(c=='-'?-1:1); ret=c-'0';
    while((c=getchar())>='0'&&c<='9') ret=ret*10+c-'0';
    return ret*w;
}
bool cmp(int a,int b){return Q[a]<Q[b];}
int main(){
    n=qread(),c=qread(),f=qread();
    up(1,c,i) C[i]=qread()+1,Q[i]=qread(),I[i]=i;
    sort(I+1,I+1+c,cmp);
    dn(30,0,i) if(chk(p|(1<<i))) p|=1<<i;
    printf("%d\n",p==0?-1:p-1);
    return 0;
}
```


---

## 作者：yxy666 (赞：1)

搞了 $1$ 小时，终于做出来了！细节好烦啊！

题意：给我们 $C$ 头牛的成绩以及花费，我们只能挑选 $N$ 头牛去上学，并且这 $N$ 头牛的花费不能超过 $F$，问我们如何使选的 $N$ 头牛中的成绩的中位数最大。

想法：我们先将所有奶牛的数据用结构体存下来，然后按照成绩排一趟序，然后定义 $i$ 表示以当前这个数作为中位数，$l[i]$ 是从 $1$ 至 $i-1$ 之间最小的 $N/2$ 头牛的花费的总和， $r[i]$ 是从 $i+1$ 至 $n$ 之间所有最小的 $N/2$ 头牛的花费的总和，那么我们就可以借助上一次的 $l[i-1]$ 和 $r[i+1]$ 拿来算这一次的 $l[i]$ 和 $r[i]$ 啊。首先我们需要先判断一下，如果我当前的花费比之前选中的 $N/2$ 头奶牛中花费最高的还高，那我们肯定不要啊，那这一次的结果就等于上一次的结果。否则就更新答案啊。注意： $l[i]$ 是拿来正刷的，而 $r[i]$ 是拿来反刷的。 如何从之前选中的奶牛中挑出花费最高的那一小子呢？很显然，我们用大根堆就好了。

$code $ :

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=100005;
struct yxy{
	int x,w;bool operator<(const yxy b)const{return x<b.x;}//重载小于号 
}a[maxn];//x表示成绩，w表示花费 
long long m,n,size,hep[maxn];//m表示要取m头奶牛上学，n表示奶牛总个数 
long long f,l[maxn],r[maxn];//l[i] 是从 1 至 i-1 之间最小的 N/2 头牛的花费的总和，r[i] 是从 i+1 至 n 之间所有最小的 N/2 头牛的花费的总和
void put(int x){
	hep[++size]=x;int son=size;
	while(son>1&&hep[son]>hep[son/2])swap(hep[son],hep[son/2]),son/=2; 
}//把这个小子塞进去 
int get(){
	int x=hep[1],fa=1,son;hep[1]=hep[size--];
	while(fa*2<=size){
		if(fa*2+1>size||hep[fa*2]>hep[fa*2+1])son=2*fa;else son=fa*2+1;
		if(hep[fa]<hep[son])swap(hep[fa],hep[son]),fa=son;else break;
	}
	return x;
}//取最大那一小子 ，并重新排一遍 
inline int read(){
	int ret=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
	while(isdigit(ch))ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}//快读 
int main(){
	m=read();n=read();scanf("%lld",&f);//注意,f可能超过int类型 
	for(int i=1;i<=n;i++)a[i].x=read(),a[i].w=read();
	sort(a+1,a+1+n);//按照成绩排序 
	for(int i=1;i<=m/2;i++)l[m/2+1]+=a[i].w,put(a[i].w);//因为l[m/1+1]没得选择，所有先统统塞进堆里 
	for(int i=m/2+2;i<=n-m/2;i++){
		int x=get();if(x<=a[i-1].w)put(x),l[i]=l[i-1];//如果这次的花费还没有之前最大个的小子比较，就不变结果 
		else l[i]=l[i-1]-x+a[i-1].w,put(a[i-1].w);//否则的话就跟新结果，把这个使用的小子丢进堆里 
	}
	memset(hep,0,sizeof hep);size=0;//重新做一遍，刷r[i] 
	for(int i=n,j=1;j<=m/2;j++,i--)r[n-m/2]+=a[i].w,put(a[i].w);//因为l[n-m/1]没得选择，所有先统统塞进堆里 
	for(int i=n-m/2-1;i>m/2;i--){
		int x=get();if(x<=a[i+1].w)put(x),r[i]=r[i+1];//如果这次的花费还没有之前最大个的小子比较，就不变结果 
		else r[i]=r[i+1]-x+a[i+1].w,put(a[i+1].w);//否则的话就跟新结果，把这个使用的小子丢进堆里
	} 
	for(int i=n-m/2;i>m/2;i--){
		if(a[i].w+l[i]+r[i]<=f){
			printf("%lld\n",a[i].x);
			return 0;
		}//因为我按照成绩排过了，从后面往前看，如果可以就直接输出，结束程序 
	}
	printf("-1\n");//否则的话就是一种可行方案都没有 
	return 0;
}
```


---

## 作者：Vocanda (赞：1)

## 分析

数据范围这么大，直接枚举区间当然是不可行的，所以我们用一个很巧妙的优化:大根堆。中位数ai
必须满足  $\frac {n} {2} +1 \le i \le c-\frac {n} {2}$


$i={n\over2}+1$时，肯定要选前$n\over2$个分数低且钱少的猪，所以我们可以枚举每一个中位数，用一个维护奖金的大根堆，每枚举完一个中位数，如果当前的奖金比堆顶的小，则交换，维持堆里有n2个数，用一个数组 f[i] 维护如果选 $a_i$ 为中位数，前 $n\over2$个数的最小奖金。


同上，倒序维护，求出 $g[i]$ 表示，如果选 $a_i$ 为中位数，则后 $n\over2$ 个数最小奖金。
所以答案为满足 $f[i]+g[i]+a[i].money≤F$ 的最大的 $a[i].fenshu$


具体细节见代码注释

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5+210;
priority_queue<int>q;//大根堆
struct Node{
    int lev,moy;
}a[maxn];//lev为分数，moy为钱数。
int n,c,F;
int sum = 0;
bool cmp(const Node &a,const Node &b){//sort的排序函数
    return a.lev < b.lev;
}
int f[maxn],g[maxn];
int main(){
    cin>>n>>c>>F;
    for(int i=1;i<=c;++i){
        cin>>a[i].lev>>a[i].moy;
    }
    sort(a+1,a+c+1,cmp);
    for(int i=1;i<=n/2;++i){//成绩前n/2的人入队
        sum += a[i].moy;//sum记录前二分之i个里的奖金数。大根堆放入。
        q.push(a[i].moy);
    }
    for(int i=n/2+1;i<=c;++i){//f[i]:表示以i为中位数前n/2人的最小奖金
        f[i] = sum;
        int top = q.top();
        if(top>a[i].moy){//奖金小于堆顶则换掉，因为越小越好。
            q.pop();
            sum -= top;
            sum += a[i].moy;
            q.push(a[i].moy);
        }
    }
    sum = 0;
    for(int i=c;i>=c-n/2+1;--i){//成绩后n/2入队
        sum += a[i].moy;
        q.push(a[i].moy);
    }
    for(int i=c-n/2;i>=1;--i){//g[i]是i为中位数是后n/2人最小奖金
        g[i] = sum;
        int top = q.top();
        if(top>a[i].moy){//同上，如果小，就换
            q.pop();
            sum -= top;
            sum += a[i].moy;
            q.push(a[i].moy);
        }
    }
    for(int i=c-n/2;i>=n/2+1;--i){//枚举每一种中位数的可能
        if(g[i]+f[i]+a[i].moy <= F){//因为是从大到小枚举的，所以满足情况就直接输出结束。
            cout<<a[i].lev<<endl;
            return 0;
        }
    }
    printf("-1\n");//没有合法情况就输出-1
}

```

---

## 作者：Sata_moto (赞：1)


[$ \large{}\color {#6495ED} \mathcal{MyBlog} $](https://xjx885.coding-pages.com/)

---

$
$

### 前言：


$\quad \quad$ 闲着没事做随机跳题系列。

---

$
$

### 题目大意：

$\quad \quad$ 给定一个长为 $C$ 的序列，序列中每个数都有一个权值 $d$ 和一个代价 $q$，要求拿出 $n$ 个数，使得在它们的代价和不大于 $F$ 的前提下，它们的权值的中位数最大。

$\quad \quad$ 数据范围： $n\le C\le 1e5\  ,\ n\le 19999\ ,\ n\bmod 2 =1\ ,\ q\le1e5\ ,\ F\le2e9$ 。

---


$
$
### 思路分析:

$\quad \quad$ 题目思路很显然：我们没办法直接维护中位数，所以考虑按权值排序后枚举中位数。

$\quad \quad$ 假如我们以排序后 $k$ 位置的元素的权值为中位数，那么，我们所花费的最小代价为： $\text{mincost}(1,k-1,(n-1)/2)+\text{mincost}(k+1,C,(n-1)/2) + cost(k)$ 。

$\quad \quad$ 其中 $\text{mincost}(a,b,c) $ 表示： 在 $[a,b]$ 区间内，前 $c$ 小的代价的和是多少。

$\quad \quad$ 如果我们可以在 $logn$ 的时间内求出 $\text{mincost}$ ，我们就可以 $O(nlogn)$ 通过本题。

$\quad \quad$ 显然，求 $\text{mincost}$ 的方法很多。

$\quad \quad$ 比如说堆，比如说平衡树。

$\quad \quad$ 不过它们都把 $\text{mincost}$ 的维护转化为插入+维护两部分，其实不需要一个数一个数的插入，主席树可以做到直接维护。

$\quad \quad$ $\text{mincost}$ 的求法显然是主席树的基础操作了，这里不仔细讲了。

---

$
$

### 代码：

```cpp
#include <bits/stdc++.h>

using namespace std;

inline int read();

const int N = 2e5 + 10;
const int M = 2e5 + 10;

int n, C, F, tot;
int rt[M], size[M << 5], son[M << 5][2];
long long sum[M << 5];

pair <int , int > stu[N];

#define mid ((l+r)>>1)
#define lc (son[root][0])
#define rc (son[root][1])

inline int read();

void Build(int & root, int l, int r)
{
	root = ++tot;
	if(l == r) return ;
	Build(lc, l, mid);
	Build(rc, mid + 1, r);
}

int Update(int Root, int x, int l, int r)
{
	int root = ++tot;
	sum[root] = sum[Root] + x;
	size[root] = size[Root] + 1;
	lc = son[Root][0], rc = son[Root][1];

	if(l == r) return root;

	if(x <= mid) lc = Update(lc, x, l, mid);
	else rc = Update(rc, x, mid + 1, r);
	return root;
}

typedef long long ll;

ll Query(int root, int Root, int l, int r, int x)
{
	if(x == 0) return 0;
	if(l == r) return 1ll * l * x;

	int l_size = size[son[Root][0]] - size[lc];
	if(l_size <= x)
		return sum[son[Root][0]] - sum[lc] + Query(rc, son[Root][1], mid + 1, r, x - l_size);
	return Query(lc, son[Root][0], l, mid, x);
}

signed main()
{
	Build(rt[0], 0, 1e5);
	n = read(), C = read(), F = read();
	for(register int k = 1; k <= C; k++)
	{
		int d = read(), Q = read();
		stu[k] = make_pair(d, Q);
	}
	sort(stu + 1, stu + 1 + C);
	for(register int k = 1; k <= C; k++)
		rt[k] = Update(rt[k - 1], stu[k].second, 0, 1e5);

	int ans = -1;
	for(register int k = C - (n - 1) / 2; k >= (n + 1) / 2; k--)
	{
		ll Sum = Query(rt[0], rt[k - 1], 0, 1e5, n / 2) + Query(rt[k], rt[C], 0, 1e5, n / 2) + stu[k].second;
		if(Sum <= F)
		{
			ans = max(ans, stu[k].first);
			break;
		}
	}

	printf("%d", ans);

	return 0;
}

inline int read()
{
	int fh = 1, x = 0, ch = '~';

	while(!(ch >= '0' && ch <= '9')) fh = ch == '-' ? -1 : 1, ch = getchar();
	while(ch >= '0' && ch <= '9') x = (x << 3) + (x << 1), x += ch - '0', ch = getchar();

	return x * fh;
}


```


---

$
$

### 结语：

$\quad \quad$ 双倍经验入口： [P3963 [TJOI2013]奖学金](https://www.luogu.com.cn/problem/P3963)。

---

$$ \large{END}$$

---

## 作者：Kewth (赞：1)

一开始以为是二分，  
后来发现不满足单调性（可能有方案中位数更大而且代价更小），又以为是线段树，  
又发现线段树维护不了，才发觉是 Splay 。

先按分数排一遍序，从大到小枚举中间的奶牛，  
对于该奶牛，为了保证它是中位数，要在它左边选一半，在右边选一半，
然后希望代价最小（序列中最小的 n / 2 个数的和），  
用 2 颗 Splay 维护其左边和右边的所有奶牛的最小代价即可。

做完之后看题解，woc 用优先队列爆搞也可以。

CODE for splay:

```cpp
#define NDEBUG
#include <bits/stdc++.h>

int input() { int x; scanf("%d", &x); return x; }

class Splay {
private:
	int val, sum;
	int times, size;
	Splay *son[2], *fa;
	void update();
	void rotate();
	Splay *Kth(int);
public:
	Splay *splay(Splay *);
	Splay *insert(int);
	Splay *range(int, int);
	Splay *find(int);
	Splay *erase();
	int get_sum();
	Splay(int, Splay*);
};

void Splay::update() {
	size = times;
	sum = val * times;
	if(son[0]) {
		size += son[0] -> size;
		sum += son[0] -> sum;
	}
	if(son[1]) {
		size += son[1] -> size;
		sum += son[1] -> sum;
	}
}

void Splay::rotate() {
	assert(fa);
	bool id = fa -> son[0] == this;
	Splay *const p = fa -> fa, *const f = fa, *const s = son[id];
	if(p) p -> son[p -> son[1] == f] = this;
	f -> son[! id] = s;
	this -> son[id] = f;
	if(s) s -> fa = f;
	this -> fa = p;
	f -> fa = this;
	f -> update();
	this -> update();
}

Splay *Splay::Kth(int k) {
	int lsize = son[0] ? son[0] -> size : 0;
	assert(k > 0);
	if(k <= lsize) return son[0] -> Kth(k);
	if(k <= lsize + times) return this;
	if(k <= size) return son[1] -> Kth(k - lsize - times);
	exit(13);
}

Splay *Splay::splay(Splay *top) {
	while(fa != top) {
		assert(fa);
		if(fa -> fa == top)
			rotate();
		else if((fa -> fa -> son[0] == fa) == (fa -> son[0] == this)) {
			fa -> rotate();
			rotate();
		} else {
			rotate();
			rotate();
		}
	}
	return this;
}

Splay *Splay::insert(int v) {
	Splay *res;
	bool id = v > val;
	res = son[id] ? son[id] -> insert(v) : son[id] = new Splay(v, this);
	update();
	assert(res);
	return res;
}

Splay *Splay::range(int l, int r) {
	splay(nullptr);
	Splay *L = Kth(l - 1) -> splay(nullptr);
	assert(L);
	Splay *R = L -> Kth(r + 1) -> splay(L);
	assert(R);
	return R -> son[0];
}

Splay *Splay::find(int v) {
	if(v == val) return this;
	bool id = v > val;
	assert(son[id]);
	return son[id] -> find(v);
}

Splay *Splay::erase() {
	assert(times);
	times --;
	update();
	return this;
}

int Splay::get_sum() {
	return sum;
}

Splay::Splay(int val, Splay *fa):
	val(val), sum(val), times(1), size(1), fa(fa) {
		son[0] = son[1] = nullptr;
	}

const int maxn = 100050;
typedef std::pair<int, int> par;
par cow[maxn], tmp[maxn];

int main() {
	using std::clog;
	using std::endl;
	int n = input() >> 1, m = input(), mon = input();
	for(int i=0; i<m; i++) {
		cow[i].first = input();
		cow[i].second = input();
	}
	std::sort(cow, cow + m);
	Splay *left = (new Splay(INT_MIN >> 2, nullptr)) ->
		insert(INT_MAX >> 2) -> splay(nullptr);
	Splay *right = (new Splay(INT_MIN >> 2, nullptr)) ->
		insert(INT_MAX >> 2) -> splay(nullptr);
	for(int i=0; i<m-n; i++)
		left = left -> insert(cow[i].second) -> splay(nullptr);
	for(int i=m-n+1; i<m; i++)
		right = right -> insert(cow[i].second) -> splay(nullptr);
	for(int i=m-n-1; i>=n; i--) {
		assert(left);
		assert(right);
		right = right -> insert(cow[i + 1].second) -> splay(nullptr);
		left = left -> find(cow[i].second) -> splay(nullptr) -> erase();
		assert(left);
		assert(right);
		left = left -> range(2, n + 1);
		right = right -> range(2, n + 1);
		assert(left);
		assert(right);
		int now = left -> get_sum() + right -> get_sum() + cow[i].second;
		/* clog << left -> get_sum() << ' ' */
		/* 	<< cow[i].second << ' ' */
		/* 	<< right -> get_sum() << endl; */
		if(now <= mon) {
			printf("%d\n", cow[i].first);
			return 0;
		}
		left = left -> splay(nullptr);
		right = right -> splay(nullptr);
	}
	puts("-1");
}
```

---

## 作者：muller (赞：1)

这道题我们对于小数据直接枚举中位数

但是数据较大

我们考虑二分

%%%%%%%%% dtkjd

tql

首先我们需要二分中位数

然后就有一个check函数

但是check函数中有许多细节

要注意一下

剩下的是就是sort一边，求第k大即可

然后主意中位数必须满足条件

当前他左右有k/2-1个数，否则一定return false
qwq 曾经调了好长时间

于是就可以避免细节a题了

奉上两年前写的代码：
```cpp
// luogu-judger-enable-o2
#include<bits/stdc++.h>
using namespace std;
const int maxn=100001;
int n,c,f;
struct Node{
	int result,mon;
	inline friend bool operator<(Node a,Node b){
		return a.result<b.result;
	}
}a[maxn];
Node b[maxn],t[maxn];
bool mycmp(Node a,Node b){
	return a.mon<b.mon;
}
bool chec(){
	int s=0;
	sort(a+1,a+c+1,mycmp);
	for(int i=1;i<=n;++i)s+=a[i].mon;
	return s>f?0:1;
}
bool ok(int mid){
	int s=a[mid].mon,cnt=0;
	for(int i=1;i<=c;++i)b[i].result=a[i].result,b[i].mon=a[i].mon;
	sort(b+1,b+mid,mycmp);
	for(int i=1;i<=n/2;++i)if(b[i].result==b[mid].result)return 0;else s+=b[i].mon;
	for(int i=mid+1;i<=c;++i)cnt++,t[cnt].result=a[i].result,t[cnt].mon=a[i].mon;
	sort(t+1,t+cnt+1,mycmp);
	for(int i=1;i<=n/2;++i)if(t[i].result==a[mid].result)return 0;else s+=t[i].mon;
	return s>f?0:1;
}
int main(){
	ios::sync_with_stdio(0);
	cin>>n>>c>>f;
	for(int i=1;i<=c;++i)cin>>a[i].result>>a[i].mon;
	if(!chec()){puts("-1");return 0;}
	sort(a+1,a+c+1);
	int l=n/2,r=c-n/2+1;
	while(l+1<r){
		int mid=(l+r)>>1;
		if(ok(mid))l=mid;
		  else r=mid;
	}
	printf("%d\n",a[l]);
	return 0;
}

```

---

## 作者：RayAstRa_ (赞：0)

## Description

有一个容量为 $f$ 的背包和 $n$ 个物品，每个物品有重量 $m_i$ 和价值 $v_i$，问在背包中恰好装 $m$ 个物品（$m$ 为奇数），权值能达到的中位数最大值。

## Idea

首先由中位数最大联想到最小值最大的二分做法：将所有价值排序后按该价值能否成为中位数二分查找。

如何验证一个值 $x$ 能否成为中位数？将所有 $v_i\lt x$ 的 $v_i$ 视作 $0$，其余视作 $1$。然后将物品按重量排序，贪心选取 $m$ 个重量最小且满足 $\sum v_i \geq \frac{m+1}{2}$ 的物品即为最佳选取方案。

时间复杂度 $O(n \log n)$。

## Code

```cpp
#include<bits/stdc++.h>
#define reg int
using namespace std;
template<class T>inline void read(T &k){
	k=0;char c=0;
	while(!isdigit(c))c=getchar();
	while(isdigit(c))k=(k<<3)+(k<<1)+(c^48),c=getchar();
}
template<class T>inline void print(T k){
	if(k>9)print(k/10);
	putchar('0'+(k%10));
}
namespace Main{
const int N=100005;
int n,m,f,v[N];
struct node{
	int v,m;
	friend bool operator<(node x,node y){
		return x.m<y.m;
	}
}a[N];
inline bool check(int x){
	int use=0,tot=0,les=0;//use：使用的背包容量 ，tot：背包内物品数，les：背包内 v 小于 v[x] 的物品数 
	for(reg i=1;i<=n;i++){
		if(a[i].v>=v[x]){
			tot++;use+=a[i].m;
		}else if(les<m/2){
			les++;tot++;use+=a[i].m;
		}
		if(use>f)return 0;
		if(tot==m)return 1;
	}
	return 0;
}
void Main(){
	read(m);read(n);read(f);
	for(reg i=1;i<=n;i++)
		read(v[i]),read(a[i].m),a[i].v=v[i];
	sort(a+1,a+1+n);
	sort(v+1,v+1+n);
	int l=1,r=n,mid,ans=l;
	while(l<=r){
		mid=(l+r)>>1;
		if(check(mid))l=mid+1,ans=mid;
		else r=mid-1;
	}
	if(ans==1)puts("-1");
	else cout<<v[ans];
}
}
signed main(){
	Main::Main();
	return 0;
}
```

目前最优解，58 ms。

---

## 作者：scp020 (赞：0)

# P4952 [USACO04MAR] Financial Aid 题解

模拟赛考到的题，放到第二题的位置我不是很理解。

## 解法

一眼二分。因为我们要使中位数最大，所以满足单调性，大答案比小答案更优，可以二分答案。注意到中位数的特点，我们只需要保证在 $n$ 个数中，有 $\lfloor \dfrac{n}{2} \rfloor$ 个数比中位数小，$\lfloor \dfrac{n}{2} \rfloor$ 个数比中位数大就可以了。所以我们按照每头奶牛的分数从小到大排序，二分这个中位数是什么，假设这个中位数对应的奶牛是 $x$，我们把 $1,2 \cdots x-1$ 这些位置的奶牛拿出来，把 $x+1,x+2 \cdots c$ 这些位置的奶牛拿出来，在两部分里分别选取 $\lfloor \dfrac{n}{2} \rfloor$ 个所需奖学金最少的奶牛，加起来看这 $n$ 头奶牛所需奖学金是否不超过 $f$。

为什么要取所需奖学金最少的奶牛？我们只需考虑中位数为 $x$ 的情况是否存在，如果设取所需奖学金最少的奶牛时奖学金总数为 $w$，如果 $w \le f$，则中位数为 $x$ 的情况存在，反之，中位数为 $x$ 的情况不存在。

如果不这样做，我们任意选了 $n$ 头奶牛奖学金总数为 $q$，这里有 $w \le q$，如果 $q \le f$，则中位数为 $x$ 的情况存在，反之，则并不说明中位数为 $x$ 的情况不存在。因为如果 $q > f$，不能说明 $w > f$。

所以我们要取所需奖学金最少的奶牛。

无解条件特判一下就可以了。

## 代码

```cpp
int n,c,f,l,r,mid,ans;
struct cow
{
	int score,money;
	inline bool operator<(const cow &rhs) const
	{
		return money<rhs.money;
	}
};
cow a[100010],tmp[100010];
inline bool cmp(const cow &lhs,const cow &rhs)
{
	return lhs.score<rhs.score;
}
inline bool judge(int x)
{
	int sum=a[x].money;
	for(int i=1;i<=x;i++) tmp[i]=a[i];
	sort(tmp+1,tmp+x);
	for(int i=1;i<=n/2;i++) sum+=tmp[i].money;
	for(int i=x+1;i<=c;i++) tmp[i-x]=a[i];
	sort(tmp+1,tmp+c-x+1);
	for(int i=1;i<=n/2;i++) sum+=tmp[i].money;
	if(sum>f) return false;
	return true;
}
int main()
{
	read(n),read(c),read(f),l=n/2+1,r=c-n/2;
	for(int i=1;i<=c;i++) read(a[i].score),read(a[i].money);
	sort(a+1,a+c+1);
	for(int i=1,sum=0;i<=n;i++)
	{
		sum+=a[i].money;
		if(sum>f)
		{
			cout<<-1;
			return 0;
		}
	}
	sort(a+1,a+c+1,cmp);
	while(l<=r)
	{
		mid=(l+r)/2;
		if(judge(mid)) ans=mid,l=mid+1;
		else r=mid-1;
	}
	cout<<a[ans].score;
	return 0;
}
```


---

