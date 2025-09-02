# [ICPC 2021 Macao R] Shortest Path Fast Algorithm

## 题目描述

最近，宝宝学习了最短路径快速算法（SPFA，或更正式地说，贝尔曼-福特-摩尔算法）以有效地解决最短路径问题。他意识到，如果用优先队列代替先进先出队列，该算法看起来与 Dijkstra 算法非常相似，并向你展示了下面的伪代码。

![](https://cdn.luogu.com.cn/upload/image_hosting/yunmac9g.png)

选择 $Q$ 中最佳顶点意味着选择具有最小优先级值的顶点（如果有多个顶点具有最小优先级值，则选择其中索引最大的顶点）。

作为未来的计算机科学家，你发现宝宝修改后的 SPFA 算法在某些精心构造的图中运行速度非常慢。然而，宝宝确信他的算法很好，除非你向他展示一个简单的无向图，在该图中，SPFA 函数中的变量 $\tt{cnt}$ 在某个时刻不少于某个 $k$。为方便起见，SPFA 函数的源顶点被指定为顶点 $1$。

就给他个教训吧！

## 说明/提示

为方便起见，你可以从比赛网站上复制与给定伪代码对应的 $\tt{C++}$ 代码。将代码保存为 $\tt{spfa.cpp}$，使用 $\text{g++ spfa.cpp -O2 -o spfa}$ 进行编译，你将得到一个名为 $\tt{spfa}$ 的可执行文件。运行 $\tt{spfa}$，将你的输出提供给它的标准输入，它将打印出 $\tt{cnt}$ 的 $\textbf{最终}$ 值。给出示例输出后，它将打印出 $4$，这意味着示例输出不足以通过秘密测试用例。

注意，给定的代码不会检查你的输出的有效性（例如，它不会检查你的输出是否真的是一个简单图）。即使可执行文件打印出一个很大的值，如果你的输出无效，你仍然可能失败测试。

翻译来自于：[ChatGPT](https://chatgpt.com/)。

## 样例 #1

### 输入

```
1```

### 输出

```
4 6
1 2 1
2 3 2
3 4 3
4 1 4
1 3 5
2 4 6```

# 题解

## 作者：Mashiroqwq (赞：6)

考虑每次入队一个点之后这一个点在优先队列中的权值知道它弹出来都不会变化。

怎么利用这个性质呢？

考虑现在如果有 $4$ 个点 $1,2,3,4$，如果我们连边 $(1,2,v_1)$，$(1,3,1)$，$(3,2,1)$，$(3,4,v_2)$，$(2,4,1)$。

其中 $v_1,v_2$ 都是很大的数，且 $v_2 < \dfrac{v_1}{2}$。

那么我们可以做到弹堆顺序为 $1,3,4,2,4$，你会发现在这一个结构中 $4$ 会被弹出两次。

那么如果我们能构造出 $16$ 个这样的结构，那么我们就可以使得弹出次数 $\geq  k=10^5$。

类似于上述构造方法构造即可，需要注意下点的弹出顺序之类的。

代码中的 $a,b,c,d$ 可以看做对应一个结构中的 $1,2,3,4$。

```cpp
//code by Emissary
#include<bits/stdc++.h>

#define fi first
#define se second
#define vc vector
#define db double
#define ll long long
#define mk make_pair
#define pb push_back
#define PI pair<int,int>
#define ull unsigned long long
#define err cerr << "   -_-   " << endl
#define debug cerr << " ------------------- " << endl

#define input(x) freopen(#x".in","r",stdin)
#define output(x) freopen(#x".out","w",stdout)

#define NO puts("No")
#define YES puts("Yes")

//#define int long long

using namespace std;

namespace IO{
	inline int read(){
		int X=0, W=0; char ch=getchar();
		while(!isdigit(ch)) W|=ch=='-', ch=getchar();
		while(isdigit(ch)) X=(X<<1)+(X<<3)+(ch^48), ch=getchar();
		return W?-X:X;
	}
	inline void write(int x){
		if(x<0) x=-x, putchar('-');
		if(x>9) write(x/10);
		putchar(x%10+'0');
	}
	inline void sprint(int x){write(x), putchar(32);}
	inline void eprint(int x){write(x), putchar(10);}
}using namespace IO;

const int inf = 1e6;

signed main(){
	freopen("SPFA.in","w",stdout);
	cout << 100 << ' ' << 16*5 << endl;
	int las=1, now=1e6;
	for(int i=1;i<=16;++i){
		int a=las, b=a+1, c=b+1, d=c+1;
		now--;
		cout << a << ' ' << b << ' ' << now << endl;
		now>>=1; now-=5;
		cout << a << ' ' << c << ' ' << 1 << endl;
		cout << c << ' ' << b << ' ' << 1 << endl;
		cout << c << ' ' << d << ' ' << now << endl;
		cout << b << ' ' << d << ' ' << 1 << endl;
		las=d;
	}
	return 0;
}
```

---

## 作者：luobotianle (赞：0)

题目要求我们构造一个只有 $100$ 个点的图，使得给出的“优先队列优化 SPFA”所有点的出队次数总和超过 $10^5$；

那么，我们一定是要构造一种结构，使得其在有 $n$ 个点的情况下会有至少 $n+1$ 个出队操作，然后把这些结构嵌套起来；

观察给出的代码，我们发现它和 Dijistra 的区别就在于一个点在优先队列中的权值不会发生变化；

考虑如何利用这个性质。

假设现在有两个点 $a,b$，我们要让 $b$ 点被重复出队，那么也就是说要：
- $b$ 点出队；
- $a$ 点出队，松弛 $b$ 点，并将 $b$ 点入队；
- $b$ 点出队。

那么问题来了：如果 $b$ 点先于 $a$ 点出队，那么 $a$ 点如何松弛 $b$ 点呢？

这就到了利用性质的时候了：**一个点在优先队列中的权值不会发生变化。**

也就是说，我们可以先将 $b$ 点以一个较小值入队，将 $b$ 点以一个较大值入队，随后在弹出 $b$ 点之前用一个其它的点来松弛 $a$；

此时，在队列中的 $a$ 的权值是“假的”，实际上 $a$ 的权值是小于 $b$ 的，但我们仍然会先弹出 $b$ 再弹出 $a$，然后让 $a$ 松弛 $b$。

更通俗地说，我们要实现这样一个结构：

![](https://cdn.luogu.com.cn/upload/image_hosting/rkmx3bcn.png)

在这个图中，发生的事大概是这样：

1.  点 $c$ 入队；
2.  点 $c$ 松弛 $a,d$，此时 $a$ 以 $inf$ 的权值进队；
3.  点 $d$ 松弛 $a,b$，此时 $b$ 以 $inf-1$ 的权值进队，$b$ 点在堆顶，但有 $dis_a<dis_b$；
4.  点 $b$ 出队；
5.  点 $a$ 出队，松弛点 $b$，点 $b$ 进队；
6.  点 $b$ 出队。

这样，我们就做到了让 $4$ 个点进出队 $5$ 次。

接下来我们只需要简单地把这个结构套几层，就行了……吗？

显然不行。我们希望通过嵌套的方式使出队次数指数级增长，所以我们需要考虑边权的设定，使它能够做到一种“先处理子结构再处理父结构”的情况。

也就是说，如果我们有两个这样的结构 $x,y$
，那么我们希望它先处理 $x$ 的第一步，再处理 $y$，再处理 $x$ 的第二步，再处理 $y$，而不是先把 $x$ 搞好在去看 $y$。

解决办法也很简单：只要让结构 $y$ 中的点的权值小于 $x$ 中第一次被推入的 $a$ 就好了。

为了达到这个效果，我们应该把上图中 $b,d$ 间的边权改为 $\frac{inf}{2}-1$，这样才能保证其子结构中的点权会被优先处理。

通过这种方式我们最多可以搞出 $17$ 个这样的子结构，能把 $55$ 个点卡到 $917501$ 次出入队。

所以尽量还是不要用已死算法吧，总有一种方法能卡掉你。


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int tot=1;
struct node{int u,v,w;};
vector<node> v;
int maxn=1000000;
int main(){
	while(tot<100){
		int a=tot,b=++tot,c=++tot,d=++tot;
		v.push_back({a,b,1});
		v.push_back({a,c,maxn});
		v.push_back({b,c,1});
		v.push_back({b,d,maxn/2});
		v.push_back({c,d,1});
		maxn=maxn/2-1;
		if(maxn/2-1<=0)break;
	}
	cout<<tot<<" "<<v.size()<<"\n";
	for(auto &i:v)cout<<i.u<<" "<<i.v<<" "<<i.w<<"\n";
	return 0;
}
```

---

