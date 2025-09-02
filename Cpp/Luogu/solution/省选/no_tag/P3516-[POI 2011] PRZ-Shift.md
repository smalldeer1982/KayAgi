# [POI 2011] PRZ-Shift

## 题目描述

**译自 POI 2011 Round 1. D「[Shift](https://szkopul.edu.pl/problemset/problem/n6S4y9QrbGqYUz64e2O-OV7D/site/?key=statement)」**

Byteasar 给他的儿子 Bytie 买了一盒共 $ n $ 块积木，他将这些积木从 $ 1 $ 到 $ n $ 编号，并按照一定的顺序摆成一排。Bytie 要将这些积木按照编号从小到大的顺序重新排列，但他只能做下面两种操作：

* 操作 a：将最后一个积木移到最前面。
* 操作 b：把第三个积木移到最前面。

我们将连续进行 $ k $ 次同一个操作称为「一块操作」，表示为 $ k a $ 或 $ k b $。  
你需要帮助 Bytie 写一个程序，告诉他有没有一个操作序列能够使积木按照编号从小到大的顺序重新排列，并告诉他操作序列。

## 说明/提示

对于 $ 100\% $ 的数据，$ 1 \le n \le 2000 $。

翻译来自于 [LibreOJ](https://loj.ac/p/2158)，checker 来自于 [帖子](https://www.luogu.com.cn/discuss/70755)。

## 样例 #1

### 输入

```
4
1 3 2 4```

### 输出

```
4
3a 2b 2a 2b```

# 题解

## 作者：shadowice1984 (赞：12)

简单构造题

这个写法和标程输出的并不一致，所以需要spj

另外这道题尽管嘤文题面上是puts"NIE DA SIE",但是由于一些历史原因,你需要puts"NIE"才能AC本题

## 本题题解

那么我们来看看我们到底可以干什么操作

操作1的本质是你可以在一个操作块的时间内将这个排列轮换一下

而操作3的本质是你可以在一个操作块的时间内将这个排列的前3位变成$3,1,2$或者$2,3,1$这两种排列

那么如果我们将操作1和操作3同时使用(也就是每次操作完毕之后我们都让这个排列轮换回来)我们就可以实现这样一个操作

将这个排列中任意一个长度为3的区间变成$3,1,2$或者$2,3,1$这个操作

先来说一下我们怎么实现这个操作

比如说我要操作$(3,5)$这个区间,我们先执行a操作n-2次这样我们就将$(3,5)$这个区间轮换到了最前面，然后执行1~2次b操作之后再执行2次a操作使得排列恢复成从1开始的轮换

当然我们发现一次操作需要3个操作块，不过我们如果我们连续的使用这个操作的话我们会发现我们的操作序列是ka,kb,ka,ka,kb,ka..的形式，我们可以将相邻的两个a操作合并起来，这样的话一次操作平摊下来仅仅需要两个操作块了

那么我们有了这个操作之后我们会发现可以实现这两个操作,并且这些操作仅仅改变后面元素的排布情况

1.将任意一个元素(除非他是前两个元素)的位置向前挪两个格子

2.将任意一个元素(除非他是第一个或者最后一个元素)的位置向前挪一个格子

实现方式也十分简单，就是轮换过去做1~2次b接着轮换回来就行了

那么我们就可以借助这个东西实现一个相当无脑的排序方式了

就是我们先把1放在第1位，然后把2放在第2位，然后把3放在第3位……以此类推

假如说我们要将这个元素挪动偶数格的话，我们不停的调用操作1即可

假如说要将这个元素挪动奇数格的话，我们不停的调用操作1，然后最后一下调用操作2即可

然后你发现这个策略在我们让n-1和n-2归位的时候会失效

具体来讲我们可能需要应付这样一个排列

1 2 3 4 5 6 8 7

这种情况是有解的但是无法用我们刚才那种方式构造出来

怎么办呢……？

其实这种情况还是可以抢救一下的，让我们来不断的对8调用1操作试试看

1 2 3 4 8 5 6 7

1 2 8 3 4 5 6 7

8 1 2 3 4 5 6 7

然后我们再做n-1次a操作排列就成了12345678了

当然是奇数的时候就gg了,put"NIE"即可

然后特判一下n=0和2的情况就行了

上代码~

```C
// luogu-judger-enable-o2
#include<cstdio>
#include<algorithm>
using namespace std;const int N=2010;
int n;int a[N];int op[N*N][2];int tp;int pi;
inline void mov(int tw)
{if(tw==pi)return;op[++tp][0]=(pi-tw+n)%n;op[tp][1]=0;pi=tw;}
inline void stp1(int pos)
{mov(pos-1);op[++tp][0]=2;op[tp][1]=1;swap(a[pos],a[pos-1]);swap(a[pos],a[pos+1]);}
inline void stp2(int pos)
{mov(pos-2);op[++tp][0]=1;op[tp][1]=1;swap(a[pos],a[pos-1]);swap(a[pos-1],a[pos-2]);}
int main()
{
    scanf("%d",&n);pi=1;
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    if(n==1){printf("0\n");return 0;}//特判 
    if(n==2)
    {
        if(a[1]<a[2])printf("0\n");
        else printf("1\n1a");return 0;
    }
    for(int i=1;i<=n-2;i++)//挪动元素 
    {
        int pos;
        for(int j=i;j<=n;j++)
            if(a[j]==i){pos=j;break;}
        if(pos==i)continue;
        while(pos-i>1)stp2(pos),pos-=2;
        if((pos-i)&1)stp1(pos),pos--;
    }
    if(a[n-1]==n)//处理特殊情况 
    {
        if(n&1){printf("NIE\n");return 0;}
        int pos=n-1;
        while(pos!=1)stp2(pos),pos-=2;
    }int pos;
    for(int i=1;i<=n;i++)//调整回1开头的排列 
        if(a[i]==1){pos=i;break;}mov(pos);
    printf("%d\n",tp);
    for(int i=1;i<=tp;i++)printf("%d%c ",op[i][0],(op[i][1])?'b':'a');
    return 0;//拜拜程序~ 
}
```




---

## 作者：lovelish (赞：4)

这题很重要的一点：**操作一的本质其实是把这个序列变成了环。**

那么在此基础上，**操作二的本质其实是把一个元素向前移两位。**

这样以来这题就很简单了。从 $2$ 到 $n-1$ 依次枚举每个元素 $x$，使其移到 $x-1$ 的后面，于是这题就做完了。

下面说一些实现细节：

由于每次只能移两位，所以会有 $x-1$ 在 $x$ 左边第 $2$ 个数的情况，这样以来就需要先将 $x$ 右边第一个数左移两位，再将 $x$ 左移两位就可以了。

在最后会出现类似这样的情况：$[1,2,3,4,5,7,6]$，这样以来按照上述方法就会出现问题（$1$ 的位置就乱了），那么当 $n$ 为偶数的时候，可以直接将 $n$ 进行 $\frac{n}{2}-1$ 次左移两位就直接完成了，当 $n$ 为奇数时显然无解。

---

## 作者：Mikudo39 (赞：3)

蒟蒻第一篇题解竟然是黑题呢 ~~（不愧是我~~

在历经3周时间的冥思苦想、更换各种方式后还是用回了最早的方案

### 下面就开始正片吧！

读题，不难看出：

操作($a$)对序列的实际位次没有任何影响，仅仅是改变(b)操作区间的位置

那么，操作($b$)又能够做什么呢？关于这点，我想到了许多不同的用途，但最后我的思路都围绕了一个中心：
# 最值

操作($b$)可以将前三位数的**最小**或**最大**移至$a_{1}$或$a_{3}$，而操作($a$)就可以帮助我们一直将**最小**或**最大**一直移至$a_{1}$或$a_{n}$

所以，本蒟蒻认为冒泡算法（加特判，因为$a_1$和$a_2$无法直接排序 应该是可以做的
~~[（但是，本蒟蒻没调出来](https://www.luogu.org/record/26476627)~~

([@Social_Zhao ](https://www.luogu.org/user/92254)认为冒泡$UKE$的主要原因是虽然时间复杂度只有$O(n^2)$，但对于$SpecialJudge$来说，由于要模拟每一步操作，导致变为$O(n^3)$)

这里，我们采用另一种算法：

---
	while(a[3]不为最大)
		操作(b);
	操作(a);
---
这样，每一次就可以将前三位**最大**的不断向后推了，直到把**最大**的数$n$推至末尾

## 但是，出现$12437658$这类情况不就死循环了吗？
因此，我们就将序列中不和谐的因素变换一下位次，重新推**最大**的即可

---
```cpp
for(int i=n;i>=1;i--)
	if(a[i]!=i){
		while(a[i]不在第三位时)
			操作(a);
		操作(b);
		操作(a);//这里进行操作的目的是防止推的过程中又将a[i]退回原位
   }
```
---
这就是基本算法了，时间复杂度是$O$(玄学)~~（就是不会算啦~~

然后如果我们真的用数组循环去模拟操作($a$)的过程，一定会超时

解决方案有两种：

* 维护操作($b$)区间的位置

* 用空间换时间

第一种不过多解释，有兴趣的神仙可以自己去实现

---

第二种又是什么意思呢？直接上代码吧
```cpp
a[--l]=a[r--];
```
这么简单？

就是开一个超大的数组，从后面开始使用（**注意，不是逆序存储**），每次仅需将$a[l-1]$赋值为$a[r]$，然后$l-1$、$r-1$即可

---

### 最后处理一下$NIE$的情况

由于自己也不知道$NIE$是在什么情况下会发生

但题目中有说$m(m<=n^{2})$，那么当$m>=4000000$时即陷入死循环了，就输出$NIE$即可，如$12354$（这种情况无法排序的原因是因为$n$为奇数，因此无论怎么排，$54$后的两位都会被交换顺序（拆了东墙补西墙

亦或是$321$、$132$、$213$的情况

([@Social_Zhao ](https://www.luogu.org/user/92254)提供:如果进行$n$次操作($a$)或$3$次操作($b$)即认为该序列无法被排序，输出$NIE$)

（这道题并没有特别卡$NIE$的情况，只有第五个测试点$n$为$3$）

---

### 关于特判：
仅需对$1$、$2$、$3$判断即可

---

### 最后说一下优化

操作($a$)进行$n$次相当于没操作

同理，操作($b$)进行$3$次相当于没操作

因此可以进行取**膜**运算

（存储方式请看代码里）

---
最后献上完整代码

---
```cpp
#include<cstdio>
using namespace std;

int n,m,l=4000001,r;
int a[4002010],ans[2][4000010];

int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}

void swap(int &x,int &y){
	x^=y;
	y^=x;
	x^=y;
	return;
}

void move_a(){
	if(((ans[1][m])&&(!ans[0][m]))||(m==0))m++;
	ans[0][m]++;
	a[--l]=a[r--];
	ans[0][m]%=n;
	if(!ans[0][m])m--;
	return;
}

void move_b(){
	if(((ans[0][m])&&(!ans[1][m]))||(m==0))m++;
	ans[1][m]++;
	swap(a[l],a[l+2]);
	swap(a[l+1],a[l+2]);
	ans[1][m]%=3;
	if(!ans[1][m])m--;
	return;
}

int main(){
	scanf("%d",&n);
	r=l+n-1;
	for(int i=l;i<=r;i++)
		scanf("%d",&a[i]);
	if(n==1)printf("0\n");
	else if(n==2){
		if(a[l]<a[l+1])printf("0\n");
		else printf("1\n1a");
	}
	else if(n==3){
		while(!((a[l]<a[l+1]&&a[l+1]<a[l+2])||(a[l]>a[l+1]&&a[l+1]>a[l+2]))) //处理为123或321的情况
			move_a();
		if(a[l]<a[l+1]){
			printf("%d\n",m);
			for(int i=1;i<=m;i++){
				if(ans[0][i])printf("%da ",ans[0][i]);
				else printf("%db ",ans[1][i]);
			}
			printf("\n");
			return 0;
		}
		else{
			printf("NIE\n");
			return 0;
		}
	}
	else{
		while(!(a[l]==n||a[l+1]==n||a[l+2]==n||a[l+3]==n))//为减少操作一开始先将最大的数移至a[1||2||3||4]
			move_a();
		while(1){
			k++;
			while(a[r]!=n){
				while(a[l+1]>a[l+2]||a[l]>a[l+2])
					move_b();
				move_a();
			}
			while(a[l+1]>a[l+2]||a[l]>a[l+2])
				move_b();
			bool f=0;
			for(int i=r,j=n;i>=l;i--,j--){
				if(a[i]!=j){
					int go=a[i];
					f=1;
					while(!(a[l+2]==go))
						move_a();
					move_b();
					move_a();
					break;
				}
			}
			if(!f)break;
			if(m>=4000000){
				printf("NIE\n");
				return 0;
			}
		}
		printf("%d\n",m);
		for(int i=1;i<=m;i++){
			if(ans[0][i])printf("%da ",ans[0][i]);
			else printf("%db ",ans[1][i]);
		}
		printf("\n");
		return 0;
	}
	return 0;
}
```

---

sto感谢观看orz

---

## 作者：yzxoi (赞：2)

## [My Blog](https://yzxoi.top/archives/1779)

## Description

> 题目链接：[P3516](https://www.luogu.com.cn/problem/P3516)

给定一个长度为 $n$ 的排列，有两种操作：

- (a) 将最后一个数移到最前面。

- (b) 把第三个数移到最前面。

连续 $k$ 个操作可以合并成一块，表示为 $ka$ 或 $kb$，要求输出一个长度小于 $n^2$ 操作序列使得进行操作后排列变为 $1,2,3,\dots,n$。

无解输出 `NIE`。

$1\leq n \leq 2000$

## Solution

这里提供一个船新做法，~~可能会跑得快点~~。

考虑在前 $i-1$ 个数字已经有序排列的情况下，如何把数 $i$ 移动到第 $i$ 个位置。

- 第 $i$ 个数字已经在第 $i$ 个位置了，那么不需要动。
- 第 $i$ 个数字必定在第 $j$ 个位置，其中 $j>i$，那么可以先把第 $i$ 个数字移动到位置 $1$，然后每次执行 $2$ 次 a，再做一次 b，这样不断往复就可以把前 $i-1$ 个数字移动到最末尾，此时再做 $i-1$ 次 a 即可。

然后最后可能会尴尬的剩下两个数，比如说下面的数据：

```
8
1 2 3 4 5 6 8 7
```

我们发现：可以做两次 a，然后再做一次 b，即可实现将一个数向左移动两个单位，那么针对上面的数据，如果 $n$ 是奇数，肯定无解，如果是偶数，可以用上面的规律移动即可。

然后细节可能有点多，需要细心点。

## Code

```cpp
#include<bits/stdc++.h>
#define Tp template<typename Ty>
#define Ts template<typename Ty,typename... Ar>
#define W while
#define I inline
#define RI register int
#define LL long long
#define Cn const
#define CI Cn int&
#define gc getchar
#define D isdigit(c=gc())
#define pc(c) putchar((c))
#define min(x,y) ((x)<(y)?(x):(y))
#define max(x,y) ((x)>(y)?(x):(y))
using namespace std;
namespace Debug{
	Tp I void _debug(Cn char* f,Ty t){cerr<<f<<'='<<t<<endl;}
	Ts I void _debug(Cn char* f,Ty x,Ar... y){W(*f!=',') cerr<<*f++;cerr<<'='<<x<<",";_debug(f+1,y...);}
	Tp ostream& operator<<(ostream& os,Cn vector<Ty>& V){os<<"[";for(Cn auto& vv:V) os<<vv<<",";os<<"]";return os;}
	#define gdb(...) _debug(#__VA_ARGS__,__VA_ARGS__)
}using namespace Debug;
namespace FastIO{
	Tp I void read(Ty& x){char c;int f=1;x=0;W(!D) f=c^'-'?1:-1;W(x=(x<<3)+(x<<1)+(c&15),D);x*=f;}
	Ts I void read(Ty& x,Ar&... y){read(x),read(y...);}
	Tp I void write(Ty x){x<0&&(pc('-'),x=-x,0),x<10?(pc(x+'0'),0):(write(x/10),pc(x%10+'0'),0);}
	Tp I void writeln(Cn Ty& x){write(x),pc('\n');}
}using namespace FastIO;
Cn int N=2010;
int n,a[N<<1],b[N],s[5],p[N<<1],h;
#define P pair<int,int>
#define MP make_pair
#define fi first
#define se second
vector<P> Ans,F;
I void Move(CI t,CI x){//模拟移动，把他拉成一个环，做到 O(1) 模拟。
	RI i;if(t==1) (h+=n-x)%=n;
	else{
		for(i=3-x+1;i<=3;i++) p[i-(3-x)]=a[h+i];for(i=1;i<=3-x;i++) p[x+i]=a[h+i];
		for(i=1;i<=3;i++) a[h+i]=p[i];for(i=1;i<=3;i++) a[(h+n+i)%(2*n)]=p[i];
	}
}
int main(){
	RI i,j,k,t;for(read(n),i=1;i<=n;i++) read(a[i]),b[i]=a[i];for(i=n+1;i<=2*n;i++) a[i]=a[i-n];
	for(i=1;i<=n-2;i++){
		for(j=1;j<=n;j++) if(a[h+j]==i) break ; 
		if(j==i) continue ;
		k=i-1,!k&&(k=n),t=0;if(j>1) Ans.push_back(MP(1,n-j+1)),k+=n-j+1,Move(1,n-j+1);
		k%=n,!k&&(k=n),swap(j,k);W(j+2<=n) Ans.push_back(MP(1,2)),Move(1,2),Ans.push_back(MP(2,1)),Move(2,1),j+=2,t++;
		if(j+1<=n) Ans.push_back(MP(1,1)),Move(1,1),Ans.push_back(MP(2,2)),Move(2,2),j++,t++;//注意判断边界
		Ans.push_back(MP(1,i-1)),Move(1,i-1);
	}for(i=n-1;i<=n;i++) s[i-(n-2)]=a[h+i]-(n-2);for(i=1;i<=2;i++) a[i]=s[i];if(a[1]==2&&a[2]==1){
		if(n&1) return puts("NIE"),0;
		for(Ans.push_back(MP(1,2)),i=n/2-1;i>=1;i--) Ans.push_back(MP(1,2)),Ans.push_back(MP(2,1));Ans.push_back(MP(1,n-1));//如果出现最后两个不符情况
	}for(i=0;i<Ans.size();){
		j=i+1;W(j<Ans.size()&&Ans[j].fi==Ans[i].fi) Ans[i].se+=Ans[j].se,j++;if(Ans[i].fi&1) Ans[i].se%=n;else Ans[i].se%=3;
		Ans[i].se&&(F.push_back(Ans[i]),0);i=j;//合并输出
	}writeln(F.size());for(auto i:F) write(i.se),pc(i.fi+'a'-1),pc(' ');
	return pc('\n'),0;
}
```

---

## 作者：Hoks (赞：1)

## 前言
简单好玩题。

摘自 [交互、构造、博弈](https://www.luogu.com.cn/training/676672)。
## 思路分析
题目中的两个操作就分别是循环右移一位，取前三位循环右移一位。

看到题目中给的块数 $m\le n^2$，这启示我们可以让每个数用 $n$ 块操作去完成。

好像不太好下手？

不妨来考虑拆分子问题的思想，如果前 $i$ 个数已经在原位置上了，怎么把第 $i+1$ 个数放到第 $i$ 个数后面。

假设第 $i+1$ 个数和第 $i$ 个数中间隔了 $x$ 个数，那么我们就要将 $i+1$ 这个数向前移 $x$ 位才可以。

这启发我们继续去拆分子问题。

考虑的再简单一点，我们考虑如何将一个数前移 $1$ 位。

假设我们要移动的数在第一位，假设序列为 $a,b,\dots,c$

先把最后一位移到开头，那么序列变成 $c,a,b,\dots$。

然后我们使用两次 $b$ 操作，就可以让序列依次变为：
$$b,c,a,\dots$$
$$a,b,c,\dots$$
所以 $1a~2b$ 即可以将第一个数前移 $1$ 位。

但这样还是有很大问题的。

第一个就是这样的移动会改变 $b,c$ 这两数的相对位置，如果 $b$ 是我们已经排序好 $1$ 那这样移就爆炸了。

第二就是我们每移动一位需要两块操作，总的操作数似乎能被卡到 $2n^2$，有点危险的。

其实和前移 $1$ 位类似，我们可以想到一个更简单的前移 $2$ 位的方式。

那就是 $2a~1b$。

序列变化依次为：
$$a,\dots,b,c$$
$$b,c,a,\dots$$
$$a,b,c,\dots$$
分别是初始状态，操作 $2a$，操作 $1b$。

这个就比刚刚的前移 $1$ 位要好多了。

第一是他只操作到了 $a$ 前面的数，不用担心后面的数是不是有序的会被乱序掉。

第二就是他移动两位只花费了两步，配合上刚刚那个前移 $1$ 位最终卡满也只会用 $n+1$ 块。

这样操作我们就可以先做掉 $1\sim n-2$ 的数了，具体流程大概就是：
1. 把要移动的数用 $a$ 操作移到最前面来。
2. 用刚刚的前移 $1/2$ 位方法把这个数接到前面已经有序的部分上去。
3. 再用 $a$ 操作移回到 $1$ 开头的情况。

为什么 $n-1$ 就不行了呢？

考虑刚刚那个前移 $1$ 位可能存在的问题，要是我们在移动 $n-1$ 时序列为 $n-1,1,2,3,\dots,n-2,n$。

那么我们用那个前移 $1$ 位的方法就会得到 $n-1,1,n,2,3,4,\dots,n-2$。

最后移回去之后就会得到 $n,2,3,\dots,n-2,n-1,1$。

这个显然不是我们想要的，也不符合刚刚拆分子问题的条件，所以 $n-1$ 就是一个边界。

那么我们现在操作完就两种可能性：
1. 已经有序了。
2. $n-1$ 和 $n$ 的位置反了。

$2$ 略显困难。

前移 $n-1$ 这个数已经不可能了，那我们不妨跳过他去前移 $n$ 这个数。

为了让 $n$ 到正确的位置上他需要前移 $n-2$ 次。

如果 $n$ 是偶数，那么一直用前面前移 $2$ 位的方法就可以了。

而如果 $n$ 是奇数，那么我们前移还是无法避开前移 $1$ 位这个坎，自然也就是无解的。

然后就是代码的问题了。

没有看懂别的题解的代码是怎么写的，也都没给解释，猫猫这里给一点带解释的代码。

首先为了写的方便一点，我们不妨先不要考虑相邻块操作种类必须不同的这个条件，先都给扔进 `vector` 里最后再去合并相邻的同种操作块。

实现上我们考虑先把操作都存下来再实际进行操作，这样写复杂度有保证也没有特别多的细节。

考虑前移的位数 $x$ 如果是偶数，那么手玩一下可以发现就是把开头变成了 $1,2,3,\dots,i,i+1$，剩下的数按照原来的顺序抄回来。

比如序列为 $1,2,5,4,3,6,i=3$ 时。

操作后的结果即为 $1,2,3,5,4,6$。

然后是前移奇数位的情况。

首先是先前移偶数位，然后再是前移 $1$ 位。

前面那个已经做掉了，考虑前移一位产生的影响。

其实在上面讨论前移 $1$ 位的时候已经标出来了。

就是把 $i$ 前面的数和后面的数位置换一换。

比如序列为 $1,2,5,4,6,3,i=3$ 时。

先把偶数的操作了就是 $1,2,5,3,4,6$。

然后再前移一位就是 $1,2,3,4,5,6$。

交换了 $3$ 相邻的 $5,4$。

实现上我们可以考虑扫出前两个大于 $i$ 的数，交换这两个数再把剩下的数抄回来就好了。

最后剩下的两个数时就不需要考虑序列的情况了，反正最后肯定是有序的要么就无解。

然后就是输出答案的问题了。

我们先判断和下一位是否相同，相同则直接合并到后一位上去。

需要注意的是块的操作次数不能太大，具体的是 $a$ 操作次数要对 $n$ 取模，$b$ 操作次数要对 $3$ 取模。

最后再扫一遍输出就好了喵。
## 代码

```cpp
#include<bits/stdc++.h>
#define mid ((l+r)>>1)
#define ls (p<<1)
#define rs (ls|1)
using namespace std;
const int N=2e3+10,M=1e5+10,V=3e5,lim=19,mod=167772161,INF=0x3f3f3f3f3f3f3f3f;
int n,k,a[N],b[N];vector<pair<int,int>>ans;
namespace Fast_IO
{
	static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
	#define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
	inline int read()
	{
		int x(0),t(1);char fc(getchar());
		while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
		while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
		return x*t;
	}
	inline void flush(){fwrite(out,1,length,stdout);length=0;}
	inline void put(char c){if(length==9999999) flush();out[length++]=c;}
	inline void put(string s){for(char c:s) put(c);}
	inline void print(int x)
	{
		if(x<0) put('-'),x=-x;
		if(x>9) print(x/10);
		put(x%10+'0');
	}
	inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
	inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
	inline void rd(char s[],int&n)
	{
		s[++n]=getchar();
		while(chk(s[n])) s[n]=getchar();
		while(ck(s[n])) s[++n]=getchar();
		n--;
	}
}
using namespace Fast_IO;
inline void solve()
{
	n=read();for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=n-2;i++)
	{
		int j;for(j=1;j<=n;j++) if(a[j]==i) break;
		if(i==j) continue;ans.emplace_back(1,n-j+1);
		int k=j-i;while(k>=2) ans.emplace_back(1,2),ans.emplace_back(2,1),k-=2;
		if(k) ans.emplace_back(1,1),ans.emplace_back(2,2);
		if(i>1) ans.emplace_back(1,i-1);
		if(!k)
		{
			for(j=1;j<=i;j++) b[j]=j;int tot=i;
			for(j=i;j<=n;j++) if(a[j]>i) b[++tot]=a[j];
			for(j=1;j<=n;j++) a[j]=b[j];continue;
		}int tot=i,x=0,y=0;
		for(j=1;j<=n;j++)
			if(a[j]>i&&!x) x=a[j];
			else if(a[j]>i&&!y) y=a[j];
		for(j=1;j<=i;j++) b[j]=j;b[++tot]=y;b[++tot]=x;
		for(j=1;j<=n;j++) if(a[j]>i&&a[j]!=x&&a[j]!=y) b[++tot]=a[j];
		for(j=1;j<=n;j++) a[j]=b[j];
	}
	if(a[n]!=n)
	{
		if(n&1) return put("NIE DA SIE\n");
		ans.emplace_back(1,2);
		for(int i=1;i<n/2;i++) ans.emplace_back(1,2),ans.emplace_back(2,1);
		ans.emplace_back(1,n-1);
	}vector<pair<int,int>>res;
	for(int i=0;i<ans.size();i++)
	{
		if(i+1<ans.size()&&ans[i].first==ans[i+1].first)
		{
			ans[i+1].second+=ans[i].second;
			continue;
		}auto [x,y]=ans[i];
		if(x==1) y%=n;else y%=3;
		if(y) res.emplace_back(x,y);
	}print(res.size());put('\n');
	for(auto [x,y]:res) print(y),put(x==1?"a ":"b ");
}
signed main()
{
	int T=1;
	//	T=read();
	while(T--) solve();
	genshin:;flush();return 0;
}
```

---

