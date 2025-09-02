# [USACO17DEC] Greedy Gift Takers P

## 题目描述

Farmer John 的死对头 Farmer Nhoj 有 $N$ 头奶牛（$1 \leq N \leq 10^5$），编号为 $1 \dots N$。它们意外地出现在 Farmer John 的农场，因此一贯礼貌的 Farmer John 试图给它们送礼物。

为此，Farmer John 拿出了他无限的礼物供应，Nhoj 的奶牛在他面前排成一队，奶牛 $1$ 在队首，奶牛 $N$ 在队尾。Farmer John 原本以为，在每一时刻，队首的奶牛会从 Farmer John 那里拿走一份礼物，然后走到队尾。然而，他刚刚意识到 Nhoj 的奶牛并不那么礼貌！每头奶牛在收到礼物后，可能不会走到队尾，而是可能会插队到队尾的某些奶牛前面。具体来说，奶牛 $i$ 总是会插队到恰好 $c_i$ 头奶牛前面（$0 \leq c_i \leq N-1$）。

Farmer John 知道有些奶牛可能会收到多份礼物；由于他有无限的礼物供应，这并不让他担心。但他担心的是，如果有些奶牛没有收到任何礼物，它们可能会变得不开心。

请帮助 Farmer John 找出无论送出多少礼物，都无法收到任何礼物的奶牛数量。

## 样例 #1

### 输入

```
3
1 2 0```

### 输出

```
1
```

# 题解

## 作者：QwQcOrZ (赞：34)

显然如果一头牛拿不到礼物，那么他后面的牛也都拿不到礼物

那么就可以考虑二分第一个拿不到礼物的牛的位置，最后计算拿不到礼物的牛的个数并输出

如何 check 当前位置能否拿到礼物？考虑下述做法：

- 方便起见，我们称当前二分到的牛为 `牛1437` ，设该牛的位置为 $now$
- 将当前位置之前的牛（即第 $1$ 到第 $now-1$ 头牛）按插入的位置从后到前排序（即降序排序）
- 将所有牛依次插入到其应该插入的位置（按之前排序的顺序），并改变 `牛1437` 的位置（$now\gets now-1$），如果插入到了 `牛1437` 的前面，那么 `牛1437` 就不可能获得礼物了，返回 $\operatorname{false}$
- 如果所有牛都插入到了 `牛1437` 的位置之后，说明此牛能拿到礼物，返回 $\operatorname{true}$

经过思考，我们会发现这个做法是对的

显然二分的 check 需要满足他是个充分必要条件，那么考虑证明此做法的充要性

先证明必要性：因为只有满足所有在 `牛1437` 前的牛都插入到 `牛1437` 之后了，`牛1437` 才能拿到礼物。而上述插入方式显然是最容易满足条件的，所以该条件有必要性

然后是充分性：显然当满足必要性的情况下，如果 `牛1437` 不能拿到礼物当且仅当 `牛1437` 之前的牛没有机会拿到礼物，以至于它不会插入到 `牛1437` 之后

而这种情况发生的唯一条件是 `牛1437` 之前的牛前面已经形成循环节了

又因为这题有单调性，也就是越前面的牛越容易合法。所以这里在 `牛1437` 之前的牛如果拿不到礼物，那么 `牛1437` 也拿不到礼物。如果由此迭代到第一个拿不到礼物的牛，就能发现在那个位置判也是不合法的（不能拿到礼物的）。而后面的牛显然不可能比前面的牛优（也就是更容易合法），所以 `牛1437` 也是不会合法的

故此有充分性

时间复杂度 $O(nlog^2n)$，用桶排可以优化到 $O(nlogn)$

$Code\ Below$

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;

int read()
{
	int s=0;
	char c=getchar(),lc='+';
	while (c<'0'||'9'<c) lc=c,c=getchar();
	while ('0'<=c&&c<='9') s=s*10+c-'0',c=getchar();
	return lc=='-'?-s:s;
}
void write(int x)
{
	if (x<0)
	{
		putchar('-');
		x=-x;
	}
	if (x<10) putchar(x+'0');
	else
	{
		write(x/10);
		putchar(x%10+'0');
	}
}
void print(int x,char c='\n')
{
	write(x);
	putchar(c);
}
int a[N],b[N],n;
bool check(int now)
{
    //因为题目给出的位置是从后往前数的，所以这里的位置都是以从最后一个向前的若干个的形式表示
	for (int i=1;i<now;i++) b[i]=a[i];
	sort(b+1,b+now);
	int tmp=n-now;//牛1437的位置
	for (int i=1;i<now;i++)
	{
		if (b[i]>tmp) return 0;
		tmp++;
	}
	return 1;
}

signed main()
{
	n=read();
	for (int i=1;i<=n;i++) a[i]=read();
	int l=1,r=n;
	while (l<=r)
	{
		int mid=(l+r)/2;
		if (check(mid)) l=mid+1;
				   else r=mid-1;
	}
	print(n-r);

	return 0;
}
```



---

## 作者：llzzxx712 (赞：23)

# P4090

**前言：大致的思路 1 楼的大佬已经说了，但是在细节和代码上还不是非常清晰，本篇题解进行进一步解释。**

## 题意简述

- 有 n 头牛排成一排，每次的队首—第 i 头牛拿了礼物后会被放到第 $n-c_i$ 的位置上
- 问有几头牛当不了队首（拿不到礼物）

## 题目分析

如其它题解所说，一头牛不能拿到礼物一定因为前面的牛构成循环。

可以二分这个形成循环的长度，然后判断这个循环是过短还是过长。

接下来是本篇题解的重点了，**如何判断这个循环过短还是过长？**

先放代码，边看代码边理解：

```cpp
bool check(int now){//循环长度
	if(now==1) return 1;//排在第一个的牛肯定能拿到礼物 
	for(int i=0;i<now;i++) b[i]=a[i];
	sort(b+1,b+now);//从小到大排序，此时我们不关注哪一头牛被放到了后面，我们关注是否有牛被放到二分的循环长度之外 
	int limit=n-now;//拿不到牛的数量 
	for(int i=1;i<now;i++){
		if(b[i]>limit) return 0;//这个循环中有拿不到礼物的牛，因为即使轮到它后它可以排到很前面，但因为前面已经成循环了，所以轮不到它 
		limit++;//有牛被放到循环后面了，后面的牛都可以往前移动一格 
	}
	return 1;
}
```

我们现在二分了一个循环长度 $now$ ，如果这个循环过长，实际上的循环更短，那么一种情况就是这一个循环中被放到最后面的元素仍在一些元素前面，那么这些元素即使拿礼物后可以放到比较前面，但他们没有拿礼物的机会（前面自成一个循环）。

为什么是一种情况呢？因为就算会被放在最后面的元素在循环外，还可能有放到倒数第二后面的元素在一些元素前面。（暂时没理解没关系，先往下看，下面有图片辅助理解）

所以我们可以将他们按 $c_i$（的副本） 排序。（这虽然暂时破坏了牛的编号与位置的对应关系，但是我们此时关注哪一头牛被放到了后面，我们关注是否有牛被放到二分的循环长度之外）然后逐个考虑。

```cpp
if(b[i]>limit) return 0;
```

看这行代码，你可能现在不理解为什么要 $limit++$ , 没关系，我们先看 i=1的时候。（$b[i]$ 的位置是不一定的，我们现在假设这堆牛中 $c$ 最小的是在这个位置）

![](https://cdn.luogu.com.cn/upload/image_hosting/j7n2t8ux.png)

黄线是第 $now$ 头牛，也就是当前循环的最后一头牛。如果 $b[1]>limit$ ，就代表 $b[1]$ 被放到了黄线前面，则循环内至少有一头牛 $now$ 在循环外，返回 0，缩短循环长度。

现在来看假如 $b[1]$ 在黄线后面的情况，

![](https://cdn.luogu.com.cn/upload/image_hosting/9zxqk6oe.png)

因为 $b[1]$ 放到了黄线后面，所以 $b[1]$ 后的那些牛都要往前一格，相当于黄线左移了一格，也就是 $"limit++"$ 。

然后把 $b[2]$ 当成新的 $b[1]$ 处理，如果这一段处理完都没有出现过短的情况，那么我们的循环长度就可能小了，应该记录答案然后判断更长的 $now$ 。

## 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
void read(int &x){
	int f=1;x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')  {x=x*10+ch-'0'; ch=getchar();}
	x*=f;
}
#define N 100010
int n,a[N],b[N],ans;
bool check(int now){
	if(now==1) return 1;//排在第一个的牛肯定能拿到礼物 
	for(int i=0;i<now;i++) b[i]=a[i];
	sort(b+1,b+now);//从小到大排序，此时我们不关注哪一头牛被放到了后面，我们关注是否有牛被放到二分的循环长度之外 
	int limit=n-now;//拿不到牛的数量 
	for(int i=1;i<now;i++){
		if(b[i]>limit) return 0;//这个循环中有拿不到礼物的牛，因为即使轮到它后它可以排到很前面，但因为前面已经成循环了，所以轮不到它 
		limit++;//有牛被放到循环后面了，后面的牛都可以往前移动一格 
	}
	return 1;
}
int main(){
	read(n);
	for(int i=1;i<=n;i++) read(a[i]);
	int le=0,r=n;
	while(le<=r){
		int mid=(le+r)>>1;
		if(check(mid)){
			ans=mid; 
			le=mid+1;
		}
		else r=mid-1;//这个循环内部有拿不到礼物的牛，实际上能拿到礼物的牛更少 
	}
	printf("%d\n",n-ans);
	return 0;
}
```

蒟蒻写题解不易，给个赞呗。

---

## 作者：Clu3ter (赞：9)

# P4090  题解

代码别的题解都贴出来了，这里主要补充讲解一下思路。

**结论1 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;最终的情况必然是整个序列被分成两部分，前一部分进入循环并且获得礼物，后一部分在循环之外，没有礼物。**

（即最前面进入循环中的牛必然拿到礼物，后面的牛必然拿不到礼物）

未进入循环的牛显然无法到达第一个位置，因而拿不到礼物。

**结论2 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;第 $\boldsymbol{n} $ 头牛至少在第 $\boldsymbol{n} $ 次时拿到礼物。**

由于每次变换后，对于除了这次拿到礼物的牛外其他的牛，要么它的位置前进一个空位(拿到礼物的牛移到了它后面)，要么保持原地不动(拿到礼物的牛移到了它前面)。因此在第 $n$ 次之前，第 $n$ 头牛不可能拿到礼物。

---

接下来讲讲算法的具体步骤。由结论1可以发现满足单调性，因此使用**二分查找**，假定牛$k$是最后面能拿到礼物的牛，判断是否可行。

然后我们面临的问题就是如何判断前面的牛能否进入循环？

```cpp
int check(int k){
	for(int i=1;i<k;i++){
		b[i]=a[i];
	}//将所需要的数组复制一份
	sort(b+1,b+k);//排序
	int bound=n-k;
	for(int i=1;i<k;i++){
		if(b[i]>bound) return 0;
		bound++;
	}
	return 1;
}
```
由上面的结论不难看出，一头牛是否在循环中，只与它前面的牛有关。牛 $k$ 能够到达第一，说明前面所有的牛都会到牛 $k$ 的后方，将其挤到第一位。

而我们假定牛 $k$ 及前面所有的牛都会到达第一并重新归队，所以在我们的假设中每头牛**不论顺序如何都会到达牛$\boldsymbol{k}$后方**。然后我们用贪心，优先让新位置靠后的牛先入队，尽量把牛 $k$ 往前挤。

每次一头牛到达后方，能把牛 $k$ 往前挤的位置范围就扩大了，因此```bound++``` 。而如果发现这头牛无法把牛 $k$ 往前挤，即 ```b[i]>bound``` ，那么牛 $k$ 就不可能再前进到达第一位了，因为排序之后的牛的新位置只可能在更前面,于是 ```return 0;``` 。而如果牛 $k$ 前方所有的牛都能顺利到达它的后面，则牛 $k$ 能够到达第一位,故```return 1;``` 。

题解就到此为止了，欢迎补充和纠错~☆

完

---

---

## 作者：依依 (赞：6)

解：

如果一头牛在最前面拿到糖果，他之后所去的位置是确定的。

什么样的牛拿不到糖果呢？ 它前面所有的牛形成了一个循环，将它挡住了。

那么我们二分形成循环的牛的位置，判断在他之前是否形成了一个循环即可。

怎么判断循环呢，出现在前i个位置的牛有多于i头，则这i头牛就会一直卡在这前i个位置。

[代码](http://www.cnblogs.com/adelalove/p/8572115.html)

---

## 作者：xtx1092515503 (赞：5)

现行所有题解用的都是二分……这里介绍一种**线段树**做法。

首先，光在头脑里面想是想不出什么的。因此，我打了几组表（打表的具体内容不需要太在意，关键是后面的总结）：

```
输入：
10
6 2 7 3 7 8 1 0 4 7
最终循环的元素编号：
3 5 6
```

它最终在```3 5 6```三个元素处产生了循环；它们的$c$值为```7 7 8```，最小值为$7$，一共$3$个数，两值和为$n$。

```
输入：
10
2 5 3 4 1 6 0 4 2 3
最终循环的元素编号：
1 2 3 4 6 8 9 10
```

珂以看到，最终是```1 2 3 4 6 8 9 10```陷入循环，它们的$c$值为```2 5 3 4 6 4 2 3```，最小值是$2$，一共$8$个数，两值和为$n$。

事实上，如果我们多打几张表，就会发现终局情况一定是这样，即$k$**个数，它们中的$\min$值**$\geq n-k$，且这是这种情况的**第一次出现**。

这还是比较容易理解的，因为要想形成循环，必须保证**这$k$个数都刷新在前$k$个位置里面**，并且一定是**第一次**，不然会有更早的循环形成（感性证明一下）。

因此我们就珂以想出一种解法，即枚举前缀，对于每个值$k$，维护前缀中$c_i\geq k$的个数，如果发现该个数$\geq n-k+1$，则出现了循环。

我们珂以用线段树维护每个$k$还**缺少**多少个数就能形成循环。当往前缀中增加一个数后，对线段树执行**前缀减**，因为这个$c_i$能对所有$\leq c_i$的$k$做贡献。当什么时候线段树中的全局最小值$\leq0$了，就意味着满足条件，出现循环，珂以结束程序了。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define lson x<<1
#define rson x<<1|1
#define mid ((l+r)>>1)
int n,c[100100];
struct SegTree{
	int mn,tag;
}seg[400100];
void pushdown(int x){
	seg[lson].mn-=seg[x].tag,seg[rson].mn-=seg[x].tag;
	seg[lson].tag+=seg[x].tag,seg[rson].tag+=seg[x].tag;
	seg[x].tag=0;
}
void pushup(int x){
	seg[x].mn=min(seg[lson].mn,seg[rson].mn);
}
void build(int x,int l,int r){
	if(l==r){seg[x].mn=n-l+1;return;}
	build(lson,l,mid),build(rson,mid+1,r),pushup(x);
}
void add(int x,int l,int r,int P){
	if(l>P)return;
	if(r<=P){seg[x].mn--,seg[x].tag++;return;}
	pushdown(x),add(lson,l,mid,P),add(rson,mid+1,r,P),pushup(x);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&c[i]),c[i]++;
	build(1,1,n);
	for(int i=1;i<=n;i++){
		add(1,1,n,c[i]);
		if(seg[1].mn<=0){printf("%d\n",n-i);return 0;}
	}
	puts("0");
	return 0;
} 
```


---

## 作者：miaokehao (赞：5)

首先如果一只牛他一直得不到礼物，那么他后面的牛也不可能得到，因为相对顺序不变

所以这给了我们二分的条件。

那么如何验证答案呢?

既然那只牛得不到礼物，那么说明那只牛前面的牛构成了循环，可以考虑一种贪心，每次把得到礼物后排在最后方的牛取出来，以便于让二分的牛排名上升

看代码
```
#include <bits/stdc++.h>
#define res register int
#define N 100005
using namespace std;
int a[N],b[N],ans,n;
inline int read() {
    int X=0,w=0;
    char ch=0;
    while(!isdigit(ch)) {
        w|=ch=='-';
        ch=getchar();
    }
    while(isdigit(ch)) X=(X<<3)+(X<<1)+(ch^48),ch=getchar();
    return w?-X:X;
}
inline bool check(res now){
	if(now==1) return 1;
	for(res i=0;i<now;i++)
	  b[i]=a[i];
	sort(b+1,b+now);
	res limit=n-now;
	for(res i=1;i<now;i++){
		if(b[i]>limit) return 0;
		limit++;
	}
	return 1;
}
int main(){
	n=read();
	for(res i=1;i<=n;i++)
	  a[i]=read();
	res l=0,r=n;
	for(;l<=r;){
		res mid=l+r>>1;
		if(check(mid)) ans=mid,l=mid+1;
		else r=mid-1;
	}
	printf("%d\n",n-ans);
	return 0;
}
```

---

## 作者：cccgift (赞：3)

## pascal的题解好少……

这道题曾被我们学校当作过模拟题，当时看过去根本没有思路……

考虑一头牛拿不到礼物的条件，当然是它前面的牛形成了一个循环，可是怎么样才能形成循环呢？

考虑该头牛位置$k$和前面的每一个位置$i$（$1≤i<k$），倘若在前$k-1$头牛中有超过$i$头牛领到礼物后会进入第$i$个位置或更前面，这会导致第$i$个位置的牛之后再也不可能领到礼物！（因为接下来，在它前面的牛会越来越多或不变，它就不可能到达第一位）

于是，我们可以二分答案，求编号最小的领不到礼物的牛，设为$tot$，那么最后答案就是$n-tot+1$。

时间复杂度为$O(nlogn)$，其中二分答案$O(logn)$，判断只要$O(n)$就行了。

#### 代码如下：

```pascal
var a,f:array[0..100000] of longint;
    n,i,l,r,mid,tot:longint;
function check(k:longint):boolean;
var i,s:longint;
begin
  fillchar(f,sizeof(f),0);s:=0;
  for i:=1 to k-1 do inc(f[a[i]]); //记录每个位置会进入多少头牛
  for i:=1 to k-1 do begin s:=s+f[i];
  if s>=i then exit(true); //这里就是实现上文分析中的内容
  end;
  exit(false);
end;
begin
  readln(n);
  for i:=1 to n do begin read(a[i]);a[i]:=n-a[i];end; //这里改成记录每头牛领到礼物后进入的位置，方便处理。
  l:=1;r:=n;
  while l<=r do //二分答案
  begin
    mid:=(l+r) div 2;
    if check(mid) then begin tot:=mid;r:=mid-1;end
    else l:=mid+1;
  end;
  writeln(n-tot+1);
end.
```

---

## 作者：_Memory (赞：2)

## 一、前言

这道题是朋友推荐的一道水蓝，但是它并不水……前后写了一个小时，凌晨一点多 AC 的。理解了一个点就应该是可以敲对的，接下来来看看解题思路吧。

## 二、思路

这道题是一道二分题，二分去找牛。首先我们要查找的范围就是这个队列的长度，所以去循环就可以了。这里也是要特判一下，因为如果这头牛在队首的话，那它就一定是拿得到礼物的。接下来就把拿不到的牛算出来，即总数减拿得到的牛。每次查完一头牛的情况之后就从下一头牛开始枚举，这里枚举的是在二分循环之外的牛，如果一旦找到这个牛，那么不论循环多少次，它都拿不到礼物，直接排除，那么后面的牛就往前进一位。

主函数部分就是打一个二分去找牛，找到的牛是可以拿到礼物的牛，那么结果是要找拿不到礼物的牛，就用总牛数减去能拿到礼物的牛的数量就可以了。

## 三、核心代码

```cpp
bool qwq(int changdu){//这个就是队列循环查找的长度
	if(changdu==1) return 1;//特判它在队伍开头的情况，就一定拿得到
	for(int i=0;i<changdu;i++){
		b[i]=a[i];
	}
//	sort(b+1,b+changdu);
	ans=n-changdu;//拿不到的牛
	for(int i=1;i<changdu;i++){//从下一个开始枚举
		if(b[i]>ans) return 0;//找的是在二分循环之外的牛，如果他在循环之外，那不管他排的有多靠前，都轮不到他直接废。
		ans+=1;//那这头牛不就去队伍末尾了吗，那前面的牛的位置不就往前进一个咯。
	}
	return 1;
}
```

```cpp
int l=0,r=n,sum=0;
	while(l<=r){
		int mid=(l+r)>>1;
		if(qwq(mid)){
			sum=mid;
			l=mid+1;
		}
		else r=mid-1;
	}//直接二分找牛
	cout<<n-sum;//输出再循环之外的拿不到礼物的牛的数量
```

---

## 作者：tribool4_in (赞：2)

讲一种线段树做法。此做法与另一篇线段树题解思路基本一致，但代码实现有所不同。

首先为了方便起见，将 $c_i$ 变为 $n-c_i$，即从队头数。

考虑什么时候这个过程将会结束（陷入死循环），一些牛拿不到礼物。显然，陷入死循环应当是在某一个时刻之后，前 $x$ 头牛将会不断地循环，导致后面的牛永无翻身之时。也就是说，当某一个时刻，有 $x$ 满足 $i\in [1,x],\ c_i\le x$，则会形成循环。

因此可以想出一种做法：枚举所有前缀 $1-i$，如果这段前缀中满足有 $x$ 个数的 $c_i\le x$，则这些数会形成循环，答案即为 $n-i$（未到过队头的）。因为在前 $i$ 个数中 $c_i>x$ 的都已经插到后面去了，经过几轮后就会形成前面所说的死循环情况。

然后就是如何实现计算前缀中是否满足有 $x$ 个数的 $c_i\le x$。考虑维护一个数组 $a$，$a_i$ 表示在当前前缀中，当 $x=i$ 时还差多少个数就可以满足有 $x$ 个数 $\le x$。

显然，初始值 $a_i=i$，每往后递推一步时，要将 $a_{[c_i, n]}$ 全部 -1（对于 $x=[c_i, n]$ 区间均有贡献），当 $a$ 数组最小值为 0 时就表示已经满足形成循环的条件了。显然可以用线段树维护。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 4e5 + 10;
inline int read() {
    int s=0, w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
    return s*w;
}
int n, m, a[N];
struct node {
    int l, r, s, lazy;
} t[N];
int len(int p) { return t[p].r - t[p].l + 1; }
void push_up(int p) { t[p].s = min(t[p * 2].s, t[p * 2 + 1].s); }
void push_down(int p) {
    int lazy = t[p].lazy;
    if (lazy) {
        t[p * 2].s += lazy;
        t[p * 2].lazy += lazy;
        t[p * 2 + 1].s += lazy;
        t[p * 2 + 1].lazy += lazy;
        t[p].lazy = 0;
    }
}
void build(int p, int l, int r) {
    t[p].l = l, t[p].r = r;
    if (l == r) {
        t[p].s = l;
        return;
    }
    int mid = (l + r) >> 1;
    build(p * 2, l, mid);
    build(p * 2 + 1, mid + 1, r);
    push_up(p);
}
int query(int p, int x, int y) {
    int l = t[p].l, r = t[p].r;
    if (x <= l && r <= y) {
        return t[p].s;
    }
    int mid = (l + r) >> 1, sum = 0x7fffffffffffffff;
    push_down(p);
    if (x <= mid) sum = min(query(p * 2, x, y), sum);
    if (mid < y) sum = min(query(p * 2 + 1, x, y), sum);
    return sum;
}
void update(int p, int x, int y, int v) {
    int l = t[p].l, r = t[p].r;
    if (x <= l && r <= y) {
        t[p].s += v;
        t[p].lazy += v;
        return;
    }
    int mid = (l + r) >> 1;
    push_down(p);
    if (x <= mid) update(p * 2, x, y, v);
    if (mid < y) update(p * 2 + 1, x, y, v);
    push_up(p);
}
signed main() {
    n = read();
    build(1, 1, n + 1);
    for (int i = 1; i <= n; i++) a[i] = n - read();
    for (int i = 1; i <= n; i++) {
        update(1, a[i], n, -1);
        if (query(1, 1, n) == 0) {
            printf("%d\n", n - i);
            return 0;
        }
    }
}
```

------

附：此做法来自 @[Killer_Bunny](https://www.luogu.com.cn/user/307090)，让我们一起膜拜他！

---

## 作者：极寒神冰 (赞：2)

有一个很显然的结论就是如果某一头奶牛从未收到礼物，那么在它前面的奶牛数量不会变。

这还告诉提醒我们有以下这个结论:

- 在它之后的奶牛都无法收到礼物,因为在它后面的奶牛不可能越过这头奶牛拿到礼物。

因此，实际上没有拿到礼物的奶牛实际上是所有奶牛的一段后缀，而我们的答案为奶牛的总数减去这段后缀的长度。

考虑第一只从未收到礼物的奶牛。它的名次永远不可能到达$0$（这里的名次指前面奶牛的数量），因此，再经过足够长的时间之后它将到达最低的名次$k$。根据第一个结论，它将永远地留在这个位置。

所以我们可以发现能拿到礼物的牛实际上再也不会跳到后面。但是这些牛总会在某个时刻拿到礼物，因为它是第一个没有拿到礼物的牛。因此，在它前面所有的$k$只牛的跳过数字至少为$N-k$，换句话说，前面的所有的$k$只奶牛的排名最多为$k$。在初始的奶牛排列中，这些$k$只奶牛（可能还有一些其他的奶牛）必须在它的前面，因为它们不可能越过这只奶牛。	

因此，对于任何从未收到礼物的奶牛，都会存在一个正整数$k$，使得在它前面的$k$只奶牛的跳跃数字最多为$k$次。事实证明，这种情况也足以让一只奶牛收不到礼物。假设有一只奶牛名为$Moomoo$收到了礼物，但在其前面有$k$只奶牛跳跃数最大为$k$。我们可以通过归纳法，在任意时间，$Moomoo$之前都是$k$只奶牛，且跳跃数最大为$k$。假设这$k$头奶牛中的一只已经拿到了礼物，这只奶牛将跳到最多排名为$k$处，但是根据我们的假设$Moomoo$的排名至少为$k$。因此这只牛将留在$Moomoo$的前面。通过归纳，可以发现$Moomoo$永远不能拿到礼物（排名永远不会小于$k$）。

因此，现在我们只需要找到第一只奶牛，假设其在初始序列中的位置为$k$，满足在它前面的$k$只奶牛最大的跳跃数为$k$，其中母牛$i$的跳跃数只有$N-c_i$。我们可以使用在$O(N\log N)$的时间复杂度做到这一点：二分搜索第一只这样的奶牛。检查当前奶牛是否满足条件，计算每个在当前奶牛前面奶牛数量为$k$

然后对于每个$k$，其部分和至少为$k$。

代码：

```c++
#include<bits/stdc++.h>
#define ld long double
#define tset puts("qwq");
#define test puts("QAQ");
#define pb(a) push_back(a)
#define pii pair<int,int> 
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define ull unsigned long long
#define int long long
#define R(i,a,b) for(int i=(a),i##E=(b);i<=i##E;i++)
#define L(i,a,b) for(int i=(b),i##E=(a);i>=i##E;i--)
#define clr(f,n) memset(f,0,sizeof(int)*(n))
#define cpy(f,g,n) memcpy(f,g,sizeof(int)*(n))
#define Swap(x,y) (x^=y^=x^=y)
template <typename T> bool ckmax(T &x, T y) { return x<y?x=y,true:false;}
template <typename T> bool ckmin(T &x, T y) { return x>y?x=y,true:false;}
using namespace std;

int n,x;
int c[222222];
int cnt[222222];
bool check(int k)
{
	clr(cnt,n+5);
	R(i,1,k-1) cnt[c[i]]++;
	int tot=0;
	R(i,1,n) 
	{
		tot+=cnt[i];
		if(tot>=i) return 0;
	}
	return 1;
}

signed main()
{
	n=read();
	R(i,1,n) c[i]=n-read();
	int l=1,r=n+1,best=1;
	while(l<=r) 
	{
		int mid=(l+r)>>1;
		if(check(mid)) best=mid,l=mid+1;
		else r=mid-1;
	}
	printf("%lld\n",n-best);
}
```



---

## 作者：zhanghao233 (赞：2)

# 题目大意
- 第一个人插到从队尾数第 $c_i+1$ 的位置。

- 求不动的牛有多少个。

# 思路
显然的我们可以把这个序列分成两段，一段是循环，一段是完全不动的。

我们没有必要根据每个 $c_i$ 来实现 $O(n)$ 的算法，而且用字符串映射来去重加上链表，是一种很难实现的数据结构。

我们考虑二分最后一个动的牛即可。接下来就是 ```check``` 函数。

我们假设当前的牛是最后一个动的牛，则我们这一个牛一定能到达队头，否则这个就不是最后一个动的牛。

我们需要优化。

如果这个牛一定能到达队头，那么这头牛的前面的牛一定会把它往前面推。因为有些牛它会**暂时**阻碍这头牛的前进，时间复杂度会增加，我们需要每一头牛只做一次操作，可以进行一次排序？

- 排序不会影响结果。如果你要到后面你总会到后面的，还不如让可以直接到后面的先走一步，这样你也可以直接到后面。

- 排序可以直接判断合法性。如果这个插入后在你前面，那么后面的全部牛都会插入到前面，所以我们选的牛不会到队头。

最后时间复杂度 $O(n \log^2 n)$。

```cpp
bool check(int x){
	int t[N];
	for(re int i=1;i<x;i++) t[i]=a[i];
	sort(t+1,t+x);
	
	int num=n-x;
	for(re int i=1;i<x;i++){
		if(t[i]<=num)
			num++;
		else
			return 0;
	}
	return 1;
}
```

---

