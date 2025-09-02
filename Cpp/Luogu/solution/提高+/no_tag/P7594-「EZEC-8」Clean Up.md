# 「EZEC-8」Clean Up

## 题目描述

有一个宽度为 $n$ 的区间，第 $i$ 个位置上如俄罗斯方块一样堆着 $a_i$ 个方块。

你可以选择任何一个位置，花费 $k$ 点能量清除这个位置上的至多 $k$ 个方块，同时在与选定位置相距为 $d$ 的位置清除至多 $\max(k-d,0)$ 个方块，相邻两个位置的距离为 $1$。请注意，**$k$ 必须是正整数。**

请问最少要多少能量才能清空整个区间的所有方块。

## 说明/提示

**样例解释**

对于第一组样例，一种最佳方案是选择位置 $3$ 花费 $5$ 点能量。

对于第二组样例，一种最佳方案是选择位置 $2$ 花费 $2$ 点能量，再选择位置 $7$ 花费 $2$ 点能量。

-------

**本题采用捆绑测试。**

- Subtask 1（5 points）：$n \leq 2$。
- Subtask 2（20 points）：$n \leq 10^3$，$a_i \neq 0$。
- Subtask 3（20 points）：$a_i \neq 0$。
- Subtask 4（20 points）：$n \leq 10^3$。
- Subtask 5（35 points）：无特殊限制。

对于 $100\%$ 的数据，$1\le n \leq 10^6$，$0 \leq a_i \leq 10^9$。

## 样例 #1

### 输入

```
5
1 4 3 4 1
```

### 输出

```
5
```

## 样例 #2

### 输入

```
8
1 2 1 0 0 1 2 1
```

### 输出

```
4
```

# 题解

## 作者：BurningEnderDragon (赞：15)

[题目链接：P7594 「EZEC-8」Clear Up](https://www.luogu.com.cn/problem/P7594)

## 题面解释

清除方法为：在任意一个位置花费一定能量，清除以当前位置为中心的一个**金字塔型区域**的方块（在每个位置消除的方块数量沿中心向两边递减）。

## Subtask 1

当 $n=1$ 时，显然答案为这个位置上的方块数量。

当 $n=2$ 时，显然存在以下几种情况：

- 若两个位置上的方块数量均为 $0$，则不需要进行消除，答案为 $0$；
- 若两个位置上的方块数量相同且不为 $0$ ，则最优的消除方式为在其中**任意一个位置**花费相当于 $($ 当前位置上的方块数量 $+1)$ 的能量，消除这两个位置上的所有方块，答案为 $($ 任意一个位置上的方块数量 $+1)$；
- 若两个位置上的方块数量不相同，则最优的消除方式为在**方块数量较多的位置**花费相当于当前位置上的方块数量的能量，消除这两个位置上的所有方块，答案为方块数量较多的位置上的方块数量。

时间复杂度为 $O(1)$

[代码（题解篇幅有限）](https://www.luogu.com.cn/paste/u5s5ya7s)

## Subtask 2

**结论：对于一个不包含 $0$ 的区间，选择一个位置花费能量消除整个区间一定是最优解。**

**举例说明：**

对于以下这组数据：

```plains
8
1 2 3 2 1 1 2 1
```
可以作出以下图像：

![](https://cdn.luogu.com.cn/upload/image_hosting/tasp1iz9.png)

如图所示，有以下两种最优的消除方式：

1. 在位置 $3$ 消耗 $3$ 点能量消除位置 $1 \sim 3$ 的方块（红色区域），在位置 $7$ 消耗 $2$ 点能量消除位置 $6 \sim 8$ 的所有方块（绿色区域）。
2. 在位置 $5$ 消耗 $5$ 点能量消除位置 $1 \sim 8$ 的方块（蓝色区域）。

事实上，第二种消除方式可以覆盖位置 $1 \sim 9$。显然上述结论成立。

对于 Subtask 2，$n \le 10^3$，可以暴力枚举在每个位置花费能量消除所有的方块所需要的能量，时间复杂度为 $O(n^2)$；

对于 Subtask 3，则需要以下的优化技巧。

## Subtask 3

**结论：若当前选择在位置 $u$ 花费 $w$ 点能量消除一个区间的所有方块，则选择在位置 $u+1$ 花费 $w+1$ 点能量仍然可以消除这个区间的所有方块。**

正确性是显然的。

盗一张 pocafup 的图（

![](https://cdn.luogu.com.cn/upload/image_hosting/uufsejpq.png)

做法为初始化 $u=1$，$w=1$，从左到右枚举每个位置 $i$，若当前的 $u$ 和 $w$ 无法消除位置 $i$ 上的所有方块，则令 $u=u+1$，$w=w+1$，直到 $u$ 和 $w$ 可以消除位置 $i$ 上的所有方块，**或 $u=i$。若 $u=i$ 时当前的 $u$ 和 $w$ 仍然无法消除位置 $i$ 上的所有方块，则令 $w=a_i$。**

时间复杂度为 $O(n)$。

[代码（题解篇幅有限）](https://www.luogu.com.cn/paste/c41f5sr5)

## Subtask 4

**结论：**

- **对于一个存在 $0$ 的区间，选择一个位置花费能量消除整个区间不一定是最优解。**
- **对于两个相邻或相交的区间 $A$ 和 $B$，它们合并后的区间记为 $A \bigcup B$，消除区间 $A$，$B$，$A \bigcup B$ 的所有方块的最小花费记为 $w_A$，$w_B$，$w_{A \bigcup B}$，若 $w_{A \bigcup B} \le w_A + w_B$，则可以合并区间 $A$ 和 $B$。** 

正确性也是显然的。

初始时，可以对每个位置 $i$ 构造一个单独的区间，区间花费的能量 $w=a_i$，中心位置 $m=i$，左端点 $l=i-(a_i-1)$，右端点 $r=i+(a_i-1)$。

然后暴力枚举任意两个区间判断是否可以合并，即可得出答案。时间复杂度为 $O(n^2)$。

同理，对于 Subtask 5，需要优化合并方式。

## Subtask 5

**结论：因为每个区间都是金字塔型的，所以对于两个满足 $m_A < m_B$ 的区间，这两个区间可以合并当且仅当 $r_A \le l_B - 2$，即两个区间之间至少间隔 $1$ 个位置。** 

**下面这张图片可以说明问题：**

![](https://cdn.luogu.com.cn/upload/image_hosting/dt9iirxv.png)

可以建立一个栈来进行合并。

做法如下：

1. 对于每个位置 $i$ ，若 $a_i \not= 0$，则构造一个单独的区间，将其入栈。
2. 每构造完一个区间并入栈后，取出栈顶的两个区间，并尝试合并，若可以合并，则删除栈顶的两个区间，并将合并后的区间入栈，直到栈中只有一个区间或者栈顶的两个区间无法合并。

对于两个区间 $A$ 和 $B$，它们合并后的区间 $A \bigcup B$ 的左端点 $l_{A \bigcup B} = \min(l_A,l_B)$，右端点 $r_{A \bigcup B} = \max(r_A,r_B)$，中心位置 $m_{A \bigcup B} = \dfrac{l_{A \bigcup B} + r_{A \bigcup B}}{2}$，花费的能量 $w_{A \bigcup B} = \left\lceil \dfrac{r_{A \bigcup B} - l_{A \bigcup B}}{2} \right\rceil + 1 = \left\lfloor \dfrac{r_{A \bigcup B} - l_{A \bigcup B} + 3}{2} \right\rfloor$。容易发现，实际计算出的 $m_{A \bigcup B}$ 可能不是整数，但在实现中并不需要处理 $m_{A \bigcup B}$。

由于 $i$ 从左到右扫描，所以可以保证栈中所有区间的中心位置 $m$ 始终单调递增，即使合并后也是如此。**所以最终栈中任意的两个区间，一定是不能合并的。**

因为区间个数为 $n$，合并最多发生 $n-1$ 次，所以时间复杂度为 $O(n)$。

**完整AC代码如下：**

```cpp
#include <cstdio>
#include <stack> 

inline int Min(const int x,const int y)  //据说手写比 STL 快一点 
{
	return x<=y?x:y;
}

inline int Max(const int x,const int y)  //据说手写比 STL 快一点 
{
	return x>=y?x:y;
}

struct Area  //存储一个区间可以覆盖的左右端点 
{
	int left,right;
};

template <typename type>
class Stack  //手写栈，比 STL 常数小，并且操作方便 
{
private:
	static const int STACK_MAX=1000000;
	int head;
	type v[STACK_MAX];
public:
	Stack()  //初始化栈顶指针为 0 
	{
		head=0;
	}
	inline bool empty()  //返回栈是否为空 
	{
		return head==0;
	}
	inline int size()  //返回栈中的元素个数 
	{
		return head;
	}
	inline void push(const type x)  //向栈中插入一个元素 
	{
		v[head++]=x;
		return ;
	}
	inline void pop()  //删除栈顶的元素 
	{
		--head;
		return ;
	}
	inline type top(const int x)  //返回栈顶的元素 
	{
		return v[head-1-x];
	}
};
Stack<Area> st;

int n,a,ans=0;

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
	{
		scanf("%d",&a);  //还是连数组都不用开 
		if(a)
		{
			st.push(Area{i-(a-1),i+(a-1)});  //初始时，每个方块个数不为 0 的位置可以构造出一个区间，构造出这个区间并将其入栈 
			while(st.size()>1 && st.top(1).right>=st.top(0).left-2)  //栈内至少有两个区间，且栈顶的两个区间相邻或相交，此时可以合并 
			{
				register int l=Min(st.top(0).left,st.top(1).left),r=Max(st.top(0).right,st.top(1).right);
				st.pop();  //栈顶的两个区间出栈 
				st.pop();
				st.push(Area{l,r});  //新区间入栈 
			}
		}
	}
	while(!st.empty())  //统计答案 
	{
		register int l=st.top(0).left,r=st.top(0).right;
		ans+=(r-l+3)/2;  //对于每个区间，计算这个区间花费的能量 
		st.pop();
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：unputdownable (赞：13)

由于进行一个消耗能量为 $k$ 的操作最多可以消除的方块是 $k^2$ 级别的，所以容易想出下面的结论：

> 考虑两个操作同时对某个位置造成影响的情况，此时必然有只用一个操作的做法，使这个操作所需能量小于等于原来两个操作之和，且对于每一位的贡献大于等于原贡献。

通俗的讲：两个有交集的操作不如一个操作。

对于有交集的两个操作，以下将消耗能量大的称为黑操作，小的称为红操作，我们考虑将红操作放在右边：

若红操作消耗能量的点（即中心竖线）在黑操作内，则下图的紫操作就是一个更优的操作：

![](https://z3.ax1x.com/2021/05/05/gKSfld.png)

否则，下图的紫操作就是一个更优的操作：

![](https://z3.ax1x.com/2021/05/05/gKSWSH.png)

以上两图中紫操作消耗的能量都为原先两操作消耗能量之和。

更准确的说，如果我们以 $p$ 来表示一个操作的位置，$k$ 来表示能量值，设 $l=p-k$，$r=p+k$，则造成影响的区间是 $(l,r)$（实际有影响的整数区间是 $[l+1,r-1]$），如果 $(l_1,r_1) \bigcap (l_2,r_2) \ne \varnothing$，那么他们可以合并。

特别的，当两个区间刚好相邻时，合并后答案不变，但是当 $r-l \equiv 1 \mod 2$ 时，并不能精准达到（这样算出来能量带 $0.5$），所以这样子合并后可能更优，故这种也合并即可。

所以，最终的答案操作一定呈这个亚子，任意两个未合并的操作之间一定存在一个 $0$：

![](https://z3.ax1x.com/2021/05/05/gKSh6A.png)



自然而然的，如果不存在 $0$，那么必然整个区间只由一个操作消除，随便搜搜即可。

---------

有另一个结论：假设操作 $(l_1,r_1)$ 是可一次消除序列中某些点的集合 $A$ 中消耗能量最小的，操作 $(l_2,r_2)$ 是对应集合 $B$ 中消耗能量最小的且他们两可合并，那么操作 $(\min(l_1,l_2),\max(r_1,r_2))$ 是对应集合 $A \bigcup B$ 中消耗能量最小的。

这个也易证吧。

所以先对每段非 $0$ 的构造出最小的操作，然后用栈存储，每次加入时从栈顶将所有可合并的合并，然后压栈即可，由于压入前栈中操作都是不可合并且最优的，可以证明每次压栈后操作都是不可合并且最优，则最后维护出来的答案也是最优的。

对于每段非 $0$ 的构造，标算中采用了一种更易写的构造：对于每个非零位消耗 $a_i$ 的能量，那么这些操作合并起来一定也是这个非零段中最优的操作。

--------

总体复杂度 $O(n)$。

- Code

``` c++
#include<bits/stdc++.h>
using namespace std;
inline int read(void) {
	register int x=0;
	register short sgn=1;
	register char c=getchar();
	while(c<48||57<c) {
		if(c==45) sgn=0;
		c=getchar();
	}
	while(47<c&&c<58) {
		x=(x<<3)+(x<<1)+c-48;
		c=getchar();
	}
	return sgn? x:-x;
}
inline void write(int x) {
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
const int N=5000002;
int n,m,ans,top,x,l,r;
int skl[N>>1],skr[N>>1];//最终维护出的答案最多只有 n/3 个
signed main() {
    n=read();
    register int L=0,R=0;
    for(register signed i=1; i<=n; ++i) {
        x=read();
        if(x==0) continue;
        l=i-x,r=i+x;
        if(l>R) {
            ++top;
            skl[top]=L,skr[top]=R;
            L=l,R=r;
        } else {
            L=min(L,l),R=max(R,r);
            while(top>0&&L<=skr[top]) {
                L=min(L,skl[top]);
                --top;
            }
        }
    }
    ++top;
    skl[top]=L;
    skr[top]=R;
    for(register int i=1; i<=top; ++i) ans+=(skr[i]-skl[i]+1)>>1;
    write(ans),puts("");
	return 0;
}
```

---

## 作者：Legitimity (赞：6)

考场降智，对于带 0 的数据打了一个不知道是什么鬼东西的算法，还调挂了（



------------

对于这些方块，我们把它们看成是 $n$ 个平面上的点 $(i,a_i)$，那么样例 $1$ 就长这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/5gqjolvz.png)

样例 $2$ 就长这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/kh64qdg3.png)

我们发现就可以转换为这样一个问题：找到若干对直线 $y1_i= x  +b1_i$ 和 $y2_i=-x  +b2_i$，并使得 $\sum (b1_i+b2_i)$ 最小（即截距之和最小），最后答案就是：
$\sum \lceil\frac{(b1_i+b2_i)}{2}\rceil$ 。

长得有点像线性规划？（考场上就一直往线性规划上想，最后只有 45 pts），但其实没有那么复杂。

考虑这样一个结论：两对直线 $y1_a,y2_a$ 和 $y1_b,y2_b$ ，其中第一对直线交点 $x_1$ 小于第二对直线交点 $x_2$，若 $y2_a$ 与 $y1_b$ 的交点的 $y$ 坐标 $\geq 0$，则这两对直线可以合并成一对直线 $y1_c=x+max(y1_a,y1_b),y2_c=-x+max(y2_a,y2_b)$。

为什么？来感性理解一下，看这张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/yvrgb1qh.png)

如图，两对黑色的直线（这里为了好看，画成射线）是原本的两队直线，红色（$HR$ 和 $HT$）的是合并后的一对直线，我们发现，这样的一对橙色线可以完美盖住两对黑色线的部分，还多盖住了标出的矩形的位置；并且，我们多画几个就会发现总是满足：$\frac{b1_c+b2_c}{2}\leq \frac{b1_a+b2_a}{2}+\frac{b1_b+b2_b}{2}$，极限情况是交点在 $x$ 轴上，此时 $\frac{b1_c+b2_c}{2}= \frac{b1_a+b2_a}{2}+\frac{b1_b+b2_b}{2}$。

那么只有有两对这样满足条件的直线，合并就一定更优。


------------


具体做法有很多中，这里提供一个简单的做法：

我们发现可合并的直线对一定是相邻的，那么就可以这样：首先开一个栈记录从前向后的直线对。对于每个点，我们把它单独视为一个区间，两条直线分别为：$y1_i=x+a_i-i$ 和 $y2_i=-x+a_i+i$。每新加入一个区间（点），从栈顶向下一直与可合并的区间合并，然后将合并完的新区间放到栈顶。最后扫一遍栈统计答案就行了。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define rg register
#define inf 0x3f3f3f3f3f3f3f3f
#define ll long long
inline int read(){
	rg int ret=0,f=0;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=1;ch=getchar();}
    while(isdigit(ch)){ret=ret*10+ch-48;ch=getchar();}
    return f?-ret:ret;
}
struct node{
	ll b1,b2;
}st[1000005],now;  //开栈。 
int n,top;
ll a[1000005],ans;  
inline node merge(node a,node b){
	node ret;
	ret.b1=max(a.b1,b.b1); ret.b2=max(b.b2,a.b2);
	return ret;
} //合并直线（区间）。 
signed main(){
	n=read();
	for(rg int i=1;i<=n;++i){
		a[i]=read(); now.b1=a[i]-i; now.b2=a[i]+i;  //将新加入的点视为一个已处理好的区间。 
		while(((st[top].b2+now.b1)>>1>=0)&&top) 
			now=merge(st[top--],now);   //不断 merge 并 pop。 
		st[++top]=now;    
	}
	while(top){
		if((st[top].b2+st[top].b1)&1) ans+=(st[top].b2+st[top].b1+1)>>1;
		else ans+=(st[top].b2+st[top].b1)>>1;
		--top;
	} //统计答案。 
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：zcz0263 (赞：5)

## 题意
第 $i$ 个位置有 $a_i$ 个块，每次可以选择一个金字塔形删除（不需要所有删除的位置之前都有块），求删除所有块后所有金字塔形高度和的最小值。
## 做法
先给每个 $i$ 预定一次操作，即为以 $i$ 为中心消除一个高为 $a_i$ 的金字塔形，然后我们发现相邻的操作可能会有很多重叠部分，考虑尝试合并这些操作。

在一个栈里维护每次操作的左右端点，合并操作的前提是两个操作对应的金字塔形相邻或有交，合并时直接把左端点取 $\min$ 右端点取 $\max$，对于每次操作一直和栈顶合并直到无法合并，然后加入栈里。

但是这样并没有做完，对于这种情况可能会合并出宽为偶数的金字塔形，不符合题意。

比如当以这种方式合并两个中心位置相邻，高度相同的操作时，就会出现一个宽度为之前宽度 $+1$ 的操作，这是不合法的情况，我们需要在计算时把它的宽度扩展为奇数。

考虑怎么扩展能使要合并的两个操作最接近，当宽度为偶数的操作尝试和栈顶合并时，此时更优的情况是向左扩展一格；当宽度为偶数的操作作为栈顶要被尝试合并时，则为向右更优。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define vi vector<int>
#define pii pair<int,int>
#define vpii vector<pair<int,int>>
#define _max(x,y) (((x)>(y))?(x):(y))
#define _min(x,y) (((x)<(y))?(x):(y))
#define max(...) max({__VA_ARGS__})
#define min(...) min({__VA_ARGS__})
#define tomx(x,...) ((x)=max((x),__VA_ARGS__))
#define tomn(x,...) ((x)=min((x),__VA_ARGS__))
#define pb push_back
#define pob pop_back
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define fi first
#define se second
vpii st;
int n,ans;
#define N 1000005
vi a(N); 
main(){
	ios::sync_with_stdio(0),cin.tie(nullptr);
	cin>>n;
	rep(i,1,n) cin>>a[i];
	rep(i,1,n){
		if(!a[i]) continue;
		pii now{i-a[i]+1,i+a[i]-1};
		int ext=0;
		for(;st.size()&&st.back().se+1>=now.fi;st.pob()){
			tomn(now.fi,st.back().fi);
			tomx(now.se,st.back().se);
			if((now.se-now.fi+1)%2==0){
				ext=1;
				now.fi--;
			}else ext=0;
		}
		if(ext) now.fi++,now.se++;
		st.pb(now);
	}
	for(auto&[l,r]:st) ans+=(r-l+1)/2+1;
	cout<<ans;
}


```

---

## 作者：pocafup (赞：4)

这是一句无意义废话

- $n \le 2$

结论：答案为两数的最大值。如果两数相同且不为零则需要加一。

证明略。

- $n\le 10^3,a_i \neq 0$

结论：在一个位置放置必然最优。

证明：懒得画了盗个图（

![](https://z3.ax1x.com/2021/05/05/gKSWSH.png)

图源 unputdownable 的题解。

文字化描述：对于两个相邻/相交的区间覆盖，令 $(u_1,w_1)$表示左边的一组在位置 $u_1$ 放置进行覆盖，价值为 $w_1$，右边的为 $(u_2,w_2)$。我们可以在 $[u_1,u_2]$ 之间选择一个点构造 $(u_3,w_1+w_2)$，使得 $u_3$ 跟 $u_1$ 的距离不大于 $w_2$，跟 $u_2$ 的距离不大于 $w_1$。因为这两个区间相邻，$u_1$ 和 $u_2$ 之间的距离不大于 $w_1+w_2$，因此 $u_3$ 必然存在。

因此，对于任何一个相邻的区间，如果他的高度不为 0，那么我们都可以合并。

$a_i \neq 0$已经告诉我们不存在高度为 0 的区间，所以只选一个点必然最优。

对于这个 sub，我们只需要暴力枚举这个选点并向两边判断，最后取最小值即可。复杂度 $O(n^2)$


- $a_i \neq 0$

做法同下一个 subtask 的预处理方法，但只需要处理 $pre[1][n]$ 即可，这里不详细分析。


- $n\le 10^3$

~~讲评的时候我咋没想到这个方法~~

考虑动态规划。

不观察性质也可以发现，答案必然是在几个位置放置能量，然后让他去覆盖旁边的。

于是，我们可以预处理在区间只用一个覆盖全部的代价。$pre[i][j]$ = min cost to cover $[i,j]$。直接枚举区间中间每个点即可做到 $O(n^3)$

结论：

若点 $u$ 在 $pre[i][j]$ 选点的左侧，那么他也必然不是 $pre[i][j+k]$ 的选点。

证明：

设 $pre[i][j]$ 的选点为 $v(v>u)$。若点 $u$ 无法用最小代价覆盖 $[i,j]$，则我们可以认为当 $j$ 增大，无论节点 $u$ 价值增大多少才能覆盖区间，节点 $v$ 都可以增大同样的数量达到相同效果。因此这种方法不成立。


因此，我们只需要根据这个单调性存选点的位置，记录 $pre[i][j]$ 的时候更新选点即可。

接下来开始动态规划。 $dp[i]$ 表示覆盖 $[1,i]$ 的最小代价，转移为 $dp[i] = dp[j] + pre[j+1][i]$，枚举 $j$ 即可。

答案为 $dp[n]$。复杂度 $O(n^2)$。

- 无特殊限制

刚才讲了，如果一对二元组$(u_1,w_1)$，$(u_2,w_2)$ 所产生区间有交集，那么我们合并必然优于不合并。

因此，我们可以考虑化点为区间。初始将序列拆为小区间，第 $i$ 个数 $a_i$覆盖区间 $(i-a_i,i+a_i)$。于是题目转化为判断区间交。我们可以存下一个栈，从左到右处理小区间。每次处理时将栈顶有交点的区间跟小区间进行合并，然后将合并后的区间加入栈。最后答案即为站内所有区间的价值和。复杂度 $O(n)$

---

## 作者：zero4338 (赞：2)

### 该做法为乱搞，更强的数据也许能卡  
首先证明一个引理 :
>
最优解中每个位置只会被一个操作所影响 .      
证明 :
	假设有一个位置 $p$  , 这个位置受到了两次操作的影响 , 设这两次操作的位置分别为 $x_1,x_2$ , 花费能量分别为 $v_1,v_2$ , 其中 $x_1<x_2$ .  
>> 首先证明 $x_1$ 和 $x_2$ 在 $p$ 的同一侧的情况  
   	这里证明都在右侧的情况 , 都在左侧的情况与之类似   
    考虑单独在 $x_2$ 花费 $v_1+v_2$ 的能量.   
    设一个点的坐标为 $x$ .  
    若 $x<x_1$ , $x$ 原受影响为 $v_1+x_1-x+v_2+x_2-x$ , 现受影响为 $v_1+v_2+x_2-x$ ,后式大于前式 , 其所受影响变大 .  
    $x_1\le x \le x_2$ 和 $x\ge x_2$ 的情况与上面类似 , 均可以说明所受影响不减 .  
    而合并两次操作与单独进行两次操作锁花费能量相同 , 故合并操作一定比分开操作优 .  
    分别在两侧的情况与同一侧的证明类似 ,  这种情况下更优的操作为在 $p$ 处花费 $v_1+v_2$ 能量 . 
 >
通过上面的讨论可知 , 若当前解中有一个点被两个以上的操作影响 , 我们就可以两两合并这些操作来得到一个更优的解 , 故引理得证 .  

由以上引理可推出 : 
> 
对于一个位置 $x$ ,它和区间 $[x-a_x+1 ,x+a_x-1]$ 一定是一起被删除的 .   
证明 :
	因为 $x$ 只能受到一次操作 , 所以这次操作在传递到 $x$ 时至少影响为 $a_x$ , 故这次操作一定会波及 $[x-a_x+1 ,x+a_x-1]$ , 而这些区间里的数也只能受到一次操作 , 故它们也必定在本次操作中被删除 .

接下来就很好做了 , 计算出每个必须一起被删除的区间 , 如果$[x-a_x+1 ,x+a_x-1]$ 之间有重合的话要进行合并 , 设 $f_i$ 为删除前 $i$ 个区间的最小花费 , 就有转移 $f_i=min(f[j]+cost(j+1,i))$ , 其中 $cost(j+1,i)$ 表示将第 $j+1$ 到 $i$ 个区间用一次操作全部消除的最小花费 , 由于有了只能进行一次操作的限制 , 这个值非常好求 , 看代码中的 $solve(l,r)$ 函数应该就能理解 .  
但这样可能被卡 , 因为可能有数据使得划分出的区间和 $n$ 同阶 , 可以想到转移时的 $j$ 离 $i$ ~~不会太远~~ , 故在转移时只需要枚举和 $i$ 较近的区间就可以 , 本题数据中只需枚举 $[i-5,i]$ .  
代码
```
#include<iostream>
#include<cstdio>
using namespace std;
const int maxn=1e6+5;
const int inf=1e9+1e6;
int read()
{
    int ret=0;
    char c=getchar();
    while(c>'9'||c<'0')c=getchar();
    while(c>='0'&&c<='9')
    {
        ret=(ret<<3)+(ret<<1)+(c^48);
        c=getchar();
    }
    return ret;
}
int n;
int a[maxn];
int mark[maxn];
int lc[maxn],rc[maxn];
int solve(int l,int r)//计算将 l ~ r 一次操作全部清楚的最小花费
{
    int maxl=-inf;
    bool flag=0;
    for(int i=l;i<=r;i++)
    {
        if(a[i])flag=1,maxl=max(maxl,a[i]-i);
        if(flag)lc[i]=maxl+i;//lc[i]表示在i处进行操作，将i左边的位置全部清除的最小花费
    }
    int maxr=-inf;
    flag=0;
    for(int i=r;i>=l;i--)
    {
        if(a[i])flag=1,maxr=max(maxr,a[i]+i);
        if(flag)rc[i]=maxr-i;//rc[i]表示在i处进行操作，将i右边的位置全部清除的最小花费
    }
    int ret=inf;
    for(int i=l;i<=r;i++)ret=min(ret,max(lc[i],rc[i]));
    return ret;
}
int el[maxn],er[maxn],tot;//分别记录区间左右端点和区间数
int f[maxn];
int main()
{
    n=read();
    for(int i=1;i<=n;i++)a[i]=read();
    for(int i=1;i<=n;i++)
    {
        if(!a[i])continue;
        int l=i-a[i]+1,r=i+a[i]-1;
        l=max(1,l);r=min(n,r);
        mark[l]++;mark[r+1]--;//区间记录成左闭右开，不然无法处理单独的1
    }
    int now=0,nl=0,nr=0;
    for(int i=1;i<=n+1;i++)
    {
        now+=mark[i];
        if(!nl&&now>0)nl=i,el[++tot]=nl;
        if(now==0&&nl)
        {
            nr=i-1;
            er[tot]=nr;
            nl=0;
        }
    }
    for(int i=1;i<=tot;i++)f[i]=inf;
    for(int i=1;i<=tot;i++)
        for(int j=i-1;j>=max(0,i-5);j--)f[i]=min(f[i],f[j]+solve(el[j+1],er[i]));
    printf("%d",f[tot]);
    return 0;
}
```


---

## 作者：Maystern (赞：1)

点 $i$ 施加 $k$ 的能量值后影响区间$[i-k,i+k]$，有等腰直角三角形性质的信息。

因此，本题有一个形象且等价化的表述：

> 有$n(1\leq n\leq 10^6)$个由同一数轴上整点构成的底边的**等腰直角三角形**，尝试用若干个底边仍由该数轴上整点构成的三角形框住，最小化这些直角三角形**底边上高的和**。

我们认为两个由同一数轴上整点构成的底边的**等腰直角三角形**有三种关系：相离（完全没有公共点）、相切（恰有一个公共点）、相交（有无数个公共点）。

**等腰直角三角形底边上的高之和**不够简洁，我们尝试将二维问题一维化，将**等腰直角三角形底边上的高和**等于**等腰直角三角形底边长和的一半**。

- 当两个直角三角形相切的时候（共顶点），将外侧两条边延长，可以构造成一个新的等腰直角三角形，通过计算可知，这个新三角形底边上高与原两个等腰直角三角形底边上的高之和相等。

- 当两个直角三角形相离的时候，将外侧两条边延长，可以构造成一个新的等腰直角三角形，通过计算可知，这个新三角形底边上高大于原两个等腰直角三角形底边上的高之和。

- 当两个直角三角形相交的时候，将外侧两条边延长，可以构造成一个新的等腰直角三角形，通过计算可知，这个新三角形底边上高小于原两个等腰直角三角形底边上的高之和。

将问题转化到一维数轴上时，我们发现，本题的实质是一个线段覆盖问题：

>有 $n(1\leq n\leq 10^6)$ 条线段$[l_i,r_i]$，求线段覆盖总长度。

有一个**细节**需要注意：

> 每个线段单独计算，若是奇数则需要除以 $2$ 后上取整；若是偶数则直接除以$ 2 $ , 无需上取整操作。

下面程序时间复杂度是$O(n log_2 n)$，仅仅提供一个新思路，希望有抛砖引玉的效果，如有疏漏还请多多指教。



```cpp
# include <bits/stdc++.h>
# define int long long
using namespace std;
const int N = 1e6 + 10;

struct rec {
	int l, r;
};
rec a[N];

bool cmp(rec x, rec y) {
	if (x.l != y.l)
		return x.l < y.l;
	else
		return x.r > y.r;
}

inline int read() {
	int X = 0, w = 0;
	char c = 0;
	while (!(c >= '0' && c <= '9'))
		w |= c == '-', c = getchar();
	while (c >= '0' && c <= '9')
		X = (X << 1) + (X << 3) + (c ^ 48), c = getchar();
	return w ? -X : X;
}

signed main() {
	int n = read();
	for (int i = 1; i <= n; i++) {
		int x = read();
		a[i].l = i - x, a[i].r = i + x;
	}
	sort(a + 1, a + 1 + n, cmp);
	int nowl = a[1].l, nowr = a[1].r, ans = 0;
	for (int i = 2; i <= n; i++) {
		if (a[i].r <= nowr)
			continue;
		if (a[i].l <= nowr) {
			nowr = a[i].r;
			continue;
		}
		ans += (nowr - nowl) / 2;
		if ((nowr - nowl) % 2 == 1)
			ans++;
		nowl = a[i].l, nowr = a[i].r;
	}
	ans += (nowr - nowl) / 2;
	if ((nowr - nowl) % 2 == 1)
		ans++;
	printf("%lld\n", ans);
	return 0;
}
```



---

