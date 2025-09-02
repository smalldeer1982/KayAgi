# [POI 2008] PLA-Postering

## 题目描述

All the buildings in the east district of Byteburg were built in accordance with the old arbitecture: they stand next to each other with no spacing inbetween. Together they form a very long chain of buildings of diverse    height, extending from east to west.

The mayor of Byteburg, Byteasar, has decided to have the north face of the chain covered with posters. Byteasar ponders over the minimum number of posters sufficient to    cover the whole north face. The posters have rectangular shape with vertical and horizontal sides. They cannot overlap, but may touch each other, i.e. have common points on the sides. Every poster has to entirely adjoin the walls of certain buildings and the whole surface of the north face has to be covered.

Task Write a programme that:

- reads the description of buildings from the standard input, 
- determines the minimum number of posters needed to entirely cover their north faces, 
- writes out the outcome to the standard output.


## 样例 #1

### 输入

```
5
1 2
1 3
2 2
2 5
1 4```

### 输出

```
4```

# 题解

## 作者：假假 (赞：49)

 Solution

1. 考虑如果整个建筑物链是等高的，一张高为链高，宽为整个建筑物宽的海报即可完全覆盖；
2. 若有两个不等高的元素组成建筑物链，那么一定需要两张；
3. 因为题目要求海报不可超出建筑物链，那么我们即可用单调栈维护：初始海报数为建筑物数，入栈建筑物链的高度序列，当栈顶大于即将入栈元素时弹栈，若最后弹栈元素与即将入栈元素等高，需要的海报数-1；
4. 易证明本方法是正确的：当有两个处于一个峰两侧的等高块时，他们可以用一张海报覆盖，所需海报数显然可减少一个；

```
#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm> 
using namespace std;
long long top=0,n,num=0,i,j,k,stack[250100];
int main(){
    scanf("%lld",&n);
    for(i=1;i<=n;++i){
        scanf("%lld%lld",&j,&k);
        while(top>0&&k<=stack[top]){
            if(k==stack[top])num++;
            --top;
        }
        stack[++top]=k;
    }
    printf("%lld\n",n-num);
    return 0;
}
```
关于单调栈其他问题可以参考我的博客：http://www.cnblogs.com/COLIN-LIGHTNING/p/8474668.html

有什么问题欢迎各位dalao指出

---

## 作者：Fairicle (赞：40)

## 这是一道单调栈的经典入门例题.

所谓单调栈，就是维护一个单调递增或递减的栈（可以是严格递增递减，也可以不严格）.

对于这道题，我们可以很轻易的发现可能答案的最大值是n，即**建筑数量**.然后进行了一波~~瞎几把猜测~~观察，我们又可以发现好像出现了**高度相等**的建筑，那么答案就要减一.（建筑宽度~~一斤~~已经被我们踢到了一边）

啊！水题！这也配得上绿题看我秒切！

然后你绞尽了脑汁你也想不出来怎么用简单的做法把这个 **1≤di,wi≤1 000 000 000**给搞定

最后你在错误的道路上越走越远......

~~时光倒流~~到你刚看到这道题的时间点.你的思路一开始走偏了，但是突然瞥见题目难度之后的一抹绿色，你眉头微皱，嘴中喃喃细语.

（跳过以下的一万字）

单调栈听上去似乎有一些抽象，那么我们从一些样例入手.（输入的都是高度，宽度已经被踹到了一旁瑟瑟发抖）

#### 输入 **1 2 3 2 1**    输出 **3**

#### 输入 **2 3 1 3 1**    输出 **4**

#### 输入 **4 5 2 5 4**    输出 **5**

困惑.明明每组数据都是有两对相等的，为什么输出结果不同？

~~容易~~观察得出，样例1中的一对相等数1，1，他们中间的所有数**都不比他们小**，另一对2，2，**中间的数也不比他们小**；对于样例2，相等数对3，3，**中间的1比他们小**，而1，1，**中间的3比他们大**；对于样例3，数对4，4，**中间有一个2比他们小**，5，5同理。

据此我们可以~~瞎几把猜想~~推断出，每有一对相等数，他们中间所有数都比他们大，那么就可以少用一张海报.**可是怎么实现呢？**

这时候自然要请出我们的单调栈了。该题维护的是一个单调不递减的栈（因为如果有一个不单调不递减就不能满足我们推断出的结论）。

那么上代码.

```cpp
#include"bits/stdc++.h"
using namespace std;
#define N 250010
int n,x,h[N],s[N],top,ans;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
	scanf("%d%d",&x,&h[i]);//宽度没有P用，直接一个int打发
	for(int i=1;i<=n;++i)
	{
		while(top>0&&h[s[top]]>h[i]) top--;//若接下来的一个建筑高度小于栈顶的建筑高度，就弹出栈顶，一直到栈顶不大于h[i]
		if(h[s[top]]!=h[i]) ans++;//如果栈顶不等于建筑高度，就必定多用一张海报
		s[++top]=i;//加入栈中
	}
	cout<<ans;
	return0;
}
// by Fairicle
```
显而易见地时间复杂度是**O（n）**

最后提一句，这道题还可以边读入边进行操作，能优化不少的时间（但是我懒

---

## 作者：wangyibo201026 (赞：16)

## 一道思维水题

首先，清楚题目理解障碍。

## 理解

题目中的海报是可以这样贴的：

![](https://cdn.luogu.com.cn/upload/image_hosting/0k67h861.png)

注意：画黑色框的是建筑物，红色框的是海报。

从这可以看出海报可以将 $n$ 个建筑物的侧面连起来。

## 题目思路

我们可以显然看出贴满这 $n$ 个建筑物的侧面可以用 $n$ 张海报，因为每个建筑物的侧面都贴一张海报就是 $n$ 张海报了。

那么现在的难点就是如何减少海报的张数。建筑物侧面**有可能**为这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/1dk8rnmt.png)

本来用四张海报贴的用三张海报就贴出来了（我只画了连起来的海报），但是如下不行：

![](https://cdn.luogu.com.cn/upload/image_hosting/agvr9k3m.png)

虽然第一栋楼的高度和第四栋楼的高度一样，但是中间的楼比这两栋楼要矮，所以不能这么贴。

所以，当从第 $i$ 栋楼开始，可以一直贴到高度不大于（小于等于）第 $i$ 栋楼的楼。

那么怎样新开一张海报呢？无非只有两种情况：

1. 第一栋楼**一定**需要一张海报。

2. 当这栋楼的高度大于前一栋楼的高度或者小于前一栋楼的高度（或者说，当不能再覆盖的时候）。

所以，套进去算就可以了。

## 代码实现

如何写代码呢？首先，开一个栈，存楼的高度，如果栈不为空并且能够覆盖下一栋楼时，就将栈里的元素 pop 到不能再覆盖的楼的。如果可以新开的话，就答案加加，继续查询能否覆盖，别忘记无论如何都要存下这栋楼的高度。

代码很短，关键是把上面的搞懂：

```cpp
#include<bits/stdc++.h>

using namespace std;

stack<int> stk;
int n, a[250005], sum;

int main(){
	cin >> n;
	for(int i = 1; i <= n; i++){
		int x;
		cin >> x >> a[i];   //别忘记输入宽
	}
	for(int i = 1; i <= n; i++){
		while(!stk.empty() && stk.top() > a[i]){   //如果能覆盖下一栋楼
			stk.pop();   //那就pop掉
		}
		if(stk.empty() || stk.top() != a[i]){   //如果要新开一张海报
			sum++;
		}
		stk.push(a[i]);    //这栋楼的高度一定
	}
	cout << sum;
	return 0;
}
```

## 补充

1. 以上思路中始终没提宽一下，可能很多人猜到了，这题跟宽没关系。

2. 为什么本题用栈，因为要记录覆盖的楼，而正好符合栈先进后出的性质。

3. 拒绝抄袭题解，共创美好洛谷。

---

## 作者：_Spectator_ (赞：11)


[可能更好的食用体验](https://www.luogu.com.cn/blog/523641/solution-p3467) $|$ 
[题目传送门](https://www.luogu.com.cn/problem/P3467) $|$ [我的其他题解](https://www.luogu.com.cn/blog/523641/#type=题解)

---
#### ${\color{SkyBlue}\mathtt{Analysis}}$ 
```txt
5
1 2
1 3
2 2
2 5
1 4
```
![](https://cdn.luogu.com.cn/upload/image_hosting/pick1fy8.png)

(上图为题目样例的海报摆法。)

由此，我们可以发现：其实就是一层一层的摆，如果这个高度在之前已经出现，那么当前建筑就不需要增添一张海报。（其实第一个值 $d_i$ 是没什么用的 ，只是在题目中用来描述位置的。）

---
#### ${\color{SkyBlue}\mathtt{Ideas}}$

那么，这就是典型的 **维护单调队列（栈）** 的题啦！

- 既然是维护单调队列，那就要考虑：是维护**单调上升**？还是维护**单调下降**？


可以通过分析题目来得出答案：

如果是单调下降，那么这张海报则可能**把更矮的建筑上方的空白**也覆盖掉，那么就违背了题意！！

由此可知，本题需要维护的是**单调上升序列**。

如果还不会单调队列，那么就应该先去学习一下[这道模板题](https://www.luogu.com.cn/problem/P1886)

---
#### ${\color{SkyBlue}\mathtt{Code}}$
```cpp
#include<iostream>
#include<cmath>
#include<cstdio>
#include<stack>
using namespace std;
stack<int> t;
int n,p,a,ans=0;
int main()
{
	scanf("%d",&n);
	for(int i=1; i<=n; i++)
	{
		scanf("%d %d",&p,&a);
		while(!t.empty() && t.top()>a) 
			t.pop();
		//弹出比a大的数，从而保证a进栈后t仍旧单调上升。
		if(t.empty() || t.top()!=a)
			ans++,t.push(a);
	}
	printf("%d",ans);
 	return 0;
}
```
---
说明：By Xin。本人乃2016级小学生，思路比较简单，题解如有写的不好的地方请指正，谢谢。

---

## 作者：lemonaaaaa (赞：10)

**这道题是单调栈的入门经典题**

我们发现：答案与宽度是没有关系的，于是我们只需要按高度维护一个单调递增的栈。

如果发现当前高度已经在栈中，就不需要另外一张海报了。

于是用一个ans变量记录一下，最后用总海报数减去不需要另外的海报数便是答案。

代码如下：

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=250005;
long long n,a[maxn],stack[maxn],top=0,ans=0;
int main()
{
    scanf("%lld",&n);
    for(int i=1,x;i<=n;i++) scanf("%d%lld",&x,&a[i]);
    for(int i=1;i<=n;i++)
    {
        while(top&&stack[top]>a[i]) top--;
        if(stack[top]==a[i]) ans++;
        stack[++top]=a[i];
    }
    printf("%lld\n",n-ans);
    return 0;
}
```

---

## 作者：寒冰大大 (赞：9)

## 咦，怎么没有STL_Stack的题解？

### 解释：玄学RE

因为手工模拟栈的过程中，即使栈内元素个数为0，也会有
$s[top] == 0$ 这种情况存在，因此不会继续满足s的顶元素比插入的元素大

而在STL的情况下，由于元素个数为0，因此访问$s.top()$是非法的，解决的方法很简单，只要最开始在栈首插入一个小于等于0的元素就可以解决了。

不得不说印度女工真的办不好事，我第一次谢了10行头文件都被撤回了

```cpp
#include<cstdio>
#include<stack>

using namespace std;

int ans,n;
stack <int> s;

int main()
{
    int i,j;
    scanf("%d",&n);
    int t1,t2;
    s.push(-100);
    scanf("%d %d",&t1,&t2);
    s.push(t2);
    for(i=2;i<=n;i++)
    {
        scanf("%d %d",&t1,&t2);
        while(s.top()>=t2)
        {
            int t=s.top();
            if(t==t2) ans++;
            s.pop();
        }
        s.push(t2);
    }
    printf("%d",n-ans);
}
```


---

## 作者：Masna_Kimoyo (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P3467)

## 思路

### 1. 

粗略地看了看这道题，我们立马可以发现，宽其实对题目没有任何影响，在代码里，只需要输入打发一下，真正在题目里有作用的只有每个建筑物的长度

### 2.

再接下来仔细地看看题目，我们又可以轻松想出贴海报的过程，就拿样例来说，具体是这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/zl1jw0x5.png)

我们看得出来，取的顺序其实是从下往上，按道理来说应该是要贴 $5$ 张海报的，但实际上只贴了 $4$ 张，我们看得出来，有两个长度为 $2$ 的建筑物，中间只需要一张海报，所以可以减少一张，这个时候，我们可以得出一个看似正确的结论：

#### 只需要看有几个相同的数，如果发现相同的，在这个循环中答案不增加 

至于为什么是错的，我们来看这种情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/enhukizn.png)

我们把第二个数据的长从 $3$ 改到了 $1$ ，这个时候，我们发现，答案又有了不同，用眼睛看一看，我们知道，现在的答案是 $5$

为什么会这样呢？

经过观察，我们发现两个 $2$ 中间，只有高度比它低，答案才能少 $+1$ 

我们通过栈的思想来做这道题，就可以得出以下一段代码：

```cpp
while(top!=0 && st[top]>w)	--top;
```

只要高度比当下的建筑低，我们就停止继续往前搜，如果像之前在上面讲的那样，碰到两个一样的，我们就不加答案，否则 $ans++$ ，由此可以得出这一段代码：

```cpp
if(w!=st[top])	++ans; 
```

在最后的最后，我们还需要将当前的 $w$ 加入栈中，代码如下：

```cpp
st[++top]=w;
```

## 代码

经过上面对题目的分析，我们可以得出这一段代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=250005;
int n,d,w,top=1,ans;
int st[N];
inline int read()
{
	int x=0;
	bool w=0;
	char c=getchar();
	while(!isdigit(c))
		w|=c=='-',c=getchar();
	while(isdigit(c))
		x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return w?-x:x;
}
signed main()
{
	n=read();
	for(register int i=1;i<=n;++i)
	{
		d=read(),w=read();
		while(top!=0 && st[top]>w)	--top;
		if(w!=st[top])	++ans; 
		st[++top]=w;
	}
	printf("%d",ans);
	return 0;
}
```

[AC记录](https://www.luogu.com.cn/record/46077865)

## 题解不易，望管理大大通过！

---

## 作者：Haphyxlos (赞：2)

# P3467 [POI2008]PLA-Postering
[题目传送门](https://www.luogu.com.cn/problem/P3467)

首先，我们理解一下题意，就能得到本题输入的宽与解题无关。

接着，我们来考虑一下什么样的图形会对结果有什么影响。

举个例子，对于```1 2 1```这种“凸”字形，我们最少只需要$2$个。

而对于```2 1 2```这种这种“凹”字形，我们最少则需要$3$个。

相信大家已经看出来了，**单调栈**是本题解题的关键，即维护一个单调递增的栈。

我们简单地分析一下易得，每次栈顶位置的高度与当前高度不同，则$ans$增加，若栈顶高度高于当前高度，则我们考虑一下“凸”字形，只需出栈即可。

此外，若当前栈为空，显然，$ans$也需增加。

详见代码注释：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=1e9+7;
const double eps=1e-8;
const int INF=0x3f3f3f3f;
const int maxn=2e6+5;
const int maxm=1e6+5;
int n,a[maxn],ans;
stack<int>s;
int main(int argc,char const *argv[]){
	std::ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1,x;i<=n;++i){
		cin>>x>>a[i];
		//本题中宽度无用 
	}
	for(int i=1;i<=n;++i){
		while(!s.empty()&&a[s.top()]>a[i]){ 
			//若当前栈不为空且栈顶位置的高度大于当前高度，就出栈
			s.pop();
		}
		if(s.empty()||a[s.top()]!=a[i]){
			//若当前栈为空或栈顶位置的高度和当前高度不等，ans++ 
			ans++;
		}
		s.push(i);
	}
	cout<<ans;
	return 0;
}
```
本篇题解就到此结束了，如果喜欢，还请点个赞吧。



---

## 作者：XL4453 (赞：1)

题目分析：

考虑贪心。

首先发现建筑物的宽度什么用都没有，题目没有限制海报的大小或者宽度，所以只需要考虑高度即可。

一般来讲，如果建筑的高度两两不相等，那么一定需要恰好 $n$ 幅海报，而观察样例发现，如果有两个等高建筑在中间没有比起更矮的建筑的情况下是可以减少一组海报使用的，这样的一个贪心思路应该很好想。（感觉和 NOIP2018 提高组的 Day1T1 有点像。）

然后考虑如何维护，发现~~标签里有栈~~要维护的一定是一个单峰序列，一旦有一个值比之前的某一个值要小，那么之前的那一个值就再也不会用到了，想到用单调栈维护这样一个单峰序列，每当遇到比要加入栈中的元素大的就直接弹掉，直到遇到一个比其小的或相等的，若相等，还需要将需要的海报数减一（将需要的海报数初始设立为 $n$）。

------------
代码：

```
#include<cstdio>
using namespace std;
int st[250005],n,tot,top,meiyongdekuandu,x;
int main(){
	scanf("%d",&n);tot=n;
	for(int i=1;i<=n;i++){
		scanf("%d%d",&meiyongdekuandu,&x);
		while(st[top]>x&&top>=1)top--;
		if(st[top]==x)tot--;
		else st[++top]=x;
	}
	printf("%d",tot);
	return 0;
}
```


---

## 作者：Doqin07 (赞：1)

#### 一道单调栈的题

我们考虑用单调栈维护，那么很显然只会有三种情况

1. 遇到比当前高的，继续向前延申，但要多加一张海报
2. 遇到比当前矮的，无法延申
3. 若一样高，继续向前

#### Code：
```cpp
/*Coder:DongYinuo*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int mod = 1e9 + 7;
#define F(i,l,r) for (int i = l; i <= r; ++i)
#define REP(i,r,l) for (int i = r; i >= l; --i)
#define mem(a,b) memset(a, b, sizeof(a));
#define MP make_pair
#define PB push_back
#define PII pair<int, int>
#define PLL pair<ll, ll>
#define all(a) a->begin(),a->end()
#define sz(a) ((int)a.size())
#define lson ind * 2 
#define rson ind * 2 + 1
namespace Pre_work{
    int readNum(){
        char c; int x = 0, f = 1;
        while (c = getchar()){ if (c == '-') f = -1;if (isdigit(c)) break;}
        while (isdigit(c)){ x = (x << 1) + (x << 3) + (c ^ 48), c = getchar();}
        return x * f;
    }
    template <typename T>
    void Rd(T& arg){
        arg = readNum();
    }
    template <typename T,typename...Types>
    void Rd(T& arg,Types&...args){
        arg = readNum();
        Rd(args...);
    }
}
using namespace Pre_work;

#define test 

namespace Solve{
    stack<int> st;
    int n, ans = 0;
    void main(){
        Rd(n);
        F (i, 1, n){
            int x, y;
            Rd(x, y);
            while (!st.empty() && st.top() > y){
                st.pop();
            } if (st.empty() || st.top() < y){
                ans++;
            }
            st.push(y);
        }
        printf("%d\n", ans);
    }
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    Solve::main();
    return 0;
}
```


---

## 作者：Forever1507 (赞：1)

# [传送门](https://www.luogu.com.cn/problem/P3467)
说真的难点在怎么做而不是怎么写代码，想出方法来之后只要会单调栈就随随便便了吧。

前置知识：单调栈([不了解的话就接受一下我的安利吧](https://www.luogu.com.cn/blog/359614/dan-diao-dui-lie-dan-diao-zhan-xue-xi-bi-ji))

思路：
- 首先非常容易发现，最坏情况下一定是贴 $n$ 张的，一栋楼就贴一张。
- 看图:
![QAQ](https://cdn.luogu.com.cn/upload/image_hosting/rqoyw7d0.png)
首先研究第 $1\sim3$ 个建筑，发现 $1$号 和 $3$号 等高，发现可以省一张海报（把 $1,2,3$号 高为 $5$ 的部分覆盖掉，然后 $2$号 多出来的盖一下）。

可以发现，若两个等高的建筑中间没有比他们矮的就可以省一张，但是如果有比他们矮的就会盖住空气，显然不行。

那么我们如何用单调栈去实现呢？

显然，我们可以维护一个存建筑高度的单调栈，只要栈顶比现在元素高就一直 $pop$ 同时查看有没有相等，如果有就说明还能省一张，$ans++$ 。

最后只要用 $n$ 减去 $ans$ 就可以了。

$Code\text{(STL大法好！！！)}:$
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans;
stack<int>stk;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		int x,y;//其实宽度是无用的
		scanf("%d%d",&x,&y);
		while(!stk.empty()&&y<=stk.top()){//维护单调性
            if(stk.top()==y)ans++;//看看能不能省一张
            stk.pop();
        }
        stk.push(y);
	}
	cout<<n-ans;//最后用总量减去最多能省的就行了
	return 0;
}
```


---

## 作者：大菜鸡fks (赞：1)

这题一开始想的是线段树，复杂度貌似可以过，但是实现十分麻烦。

可以注意到的是，厚度是无用的，并且每一次从下覆盖，先往左延伸尽量长，再往上延伸尽量长这样是最优的。

答案最大是n，考虑如何优化答案。如：5 5 6 中间3个用1个覆盖就可以节省一个海报。变为0 0 1，可以用单调栈实现这一过程

```cpp
#include<cstdio>
using namespace std;
inline int read(){int x=0,f=1,ch=getchar(); while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();} while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();} return x*f;}
inline void write(int x){if (x<0) putchar('-'),x=-x; if (x>=10) write(x/10); putchar(x%10+'0');}
inline void writeln(int x){write(x); puts("");}
const int N=250005;
int n,q[N],t,ans;
int main(){
	n=read(); ans=n;
	for (int i=1;i<=n;i++){
		int y=read(),x=read();
		while (t&&q[t]>x) t--;
		if (q[t]==x) ans--;
		q[++t]=x;
	}
	writeln(ans);
	return 0;
}
```

---

## 作者：cscst (赞：1)

## **策略**
1.遇到比自己高的，可以继续向前延续，但必须再开一张；

2.遇到比自己矮的，这张海报就不能向前延续；

3.遇到和自己同样高的，继续向前延续；

# code
```c
#include<bits/stdc++.h>
using namespace std;
int n, ans = 0;
stack<int> stk;

int main()
{
    cin >> n;
    for(int i = 1; i <= n; i++)
    {
	int t, h;
	cin >> t >> h;
	while(stk.empty() == false && stk.top() > h)
	    stk.pop();
        if(stk.empty() == true || stk.top() < h)
            ans++;
        stk.push(h);
    }
	
    cout << ans;
    return 0;
}
```

---

## 作者：DEADFISH7 (赞：1)

被老师说这个题一看就是单调队列，我慌了

因为我完全就没有往单调队列那里想，所以强行过来做一波

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstdlib>
using namespace std;
#define N 270000
#define int long long 
int n;
int ans=0,top=0;
int stack[N];
int w[N],h[N];
signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++) scanf("%lld%lld",&w[i],&h[i]);
	for(int i=1;i<=n;i++)
	{
		while(top&&stack[top]>h[i]) top--;
		if(stack[top]==h[i]) ans++;
		stack[++top]=h[i];
	}
	printf("%lld",n-ans);
	return 0;
}
```
显然宽度是没用的。

首先 我们假设最坏情况（恰好是个楼梯的形状）答案是n 即每一栋都贴一个广告

然后我们必须得想清楚一件事如果两个楼不一样搞，很显然要两个广告

所以要想减少要贴的广告的数量，必须是两个相等的楼层

因此从最坏的结果里减去  最多的  能减少的就是我们最终的答案

因此我们就可以维护一个单调的队列，不符合的弹出——因为他不能减少答案，符合加进来保证后续操作的正确性，然后记录相等的，最后总的减去相等的就ok了

至于为什么是单调递增的 我们可以比较一下一个按照“凸”摆放的楼层“凹”摆放的楼层，显然单调递减中“凹”是不合法的。

---

## 作者：神眷之樱花 (赞：0)

#### 简述
这是一道单调栈的模板题，挺适合刚学单调栈的人来练手。

题意很简单，稍加分析我们就能发现其中的规律，答案与宽度是没有关系的，所以其实我们只需要按高度维护一个单调递增的栈。

本人亲测了一下，不加快读跑了 $162ms$，加了之后跑了 $81ms$。所以没学快读的朋友们快学一手哦。但可以再优化一下边读边算，但本人太菜了，试了一下没搞出来。

------------

```cpp
#include<bits/stdc++.h>
using namespace std;
const int  N=250005;
int n,nb,top,ans;
int h[N],s[N];
inline int read()
{
	int x=0,flag=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')flag=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-'0');ch=getchar();}
	return x*flag;
}
int main()
{
	n=read();
	for(int i=1;i<=n;i++)
	nb=read(),h[i]=read();
	for(int i=1;i<=n;i++)
	{
		while(top>0&&h[s[top]]>h[i]) top--;
		if(h[s[top]]!=h[i]) ans++;
		s[++top]=i;
	}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：Plozia (赞：0)

~~无耻的~~宣传一波博客：[link](https://blog.csdn.net/BWzhuzehao/article/details/109826385)

这道题首先可以发现，宽度是完全没有用处的，所以可以忽略不计。

然后在贴海报时，可以发现：如果某一个点与前面某一个点相同，而且这两个点中间没有比他们低的点，那么可以节省一张海报。

啥意思？比如说：

`1 4 2 1 2 3`

处理时，由于两个 1 中间没有比 1 低的，那么他们可以共享一张海报（使用公共边），而两个 2 之间就不行，因为里面有一个搞事情的 1 ，使得两个 2 不能共用一张海报。

而此时问题就变成了如何处理两个 2 中间的 1 ？其实当出现了一个 1 的时候，前面的所有比 1 大的数全部没有用处了，而这个操作恰好可以使用单调栈维护。

我们维护一个单调递增栈，栈内元素单调递增，加入新数据时弹栈完毕后只需要判断一下当前栈顶元素是否与加入元素相等就可以了，如果是相等的，不需要新增一张海报，否则需要新增一张海报。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int MAXN=250000+10;
int n,h[MAXN],p,ans,sta[MAXN];

int read()
{
	int sum=0,fh=1;char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') fh=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') {sum=(sum<<3)+(sum<<1)+ch-'0';ch=getchar();}
	return sum*fh;
}

int main()
{
	n=read();
	for(int i=1;i<=n;i++) {read();h[i]=read();}
	p=0;
	for(int i=1;i<=n;i++)
	{
		ans++;
		while(p!=0&&h[sta[p]]>h[i]) p--;
		if(h[sta[p]]==h[i]) ans--;
		sta[++p]=i;
	}
	cout<<ans<<"\n";
	return 0;
}
```

---

## 作者：__gcd (赞：0)

很容易构造出一组显然可行但可能不是最优的解：每栋楼贴上一张海报。在此基础上，我们要考虑尽可能减少海报的数量。

讨论当前大楼可以由前面大楼海报完全覆盖的情况。需要满足以下两个条件：

* 与前面大楼等高。

* 中间大楼必须比这两栋大楼都高，保证覆盖前一栋大楼的海报能覆盖到当前大楼。

这个可以使用**单调栈**来维护。维护一个高度单调递增的大楼序列。每加入一个数，就使单调栈中所有比它大的数弹出。如果出现与它等高的大楼，则减少 $1$ 个答案（以之前构造出的答案为基础），并用它替换栈中的大楼（相当于不变），否则，则把它压入栈中。

另外，代码中的统计答案是另一种方式。可以证明，当当前元素出现后，栈中比它高的大楼都不可能减少答案，那么直接统计到 $ans$ 里面去。循环一遍后，将栈中的元素再统计一遍答案。

参考代码如下：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define db double
using namespace std;
inline int read()
{
	int x = 0; bool op = false;
	char c = getchar();
	while(!isdigit(c))op |= (c == '-'), c = getchar();
	while(isdigit(c))x = (x << 1) + (x << 3) + (c ^ 48), c = getchar();
	return op ? -x : x; 
}
const int N = 250010;
int n;
int h[N];
stack<int> s;
int main()
{
	n = read();
	for(int i = 1; i <= n; i++)
	{
		int useless = read(); h[i] = read();
	}
	int ans = 0;
	for(int i = 1; i <= n; i++)
	{ 
		while(s.empty() == false && s.top() > h[i]){ans++; s.pop();}
		if(s.empty() == true || s.top() != h[i])s.push(h[i]);
	}
	printf("%d", ans + s.size());
	return 0;
} 
```

update 10.12：修正了不严谨的用词

---

## 作者：cyl2019 (赞：0)

```cpp
/*
题号：P3467
题目简述：N个矩形,排成一排. 用尽量少的矩形覆盖它们.
数据范围：N<=250005(注意数据范围！我就是因此RE了) 
		  （O(NlogN)或许可行？线性更好）
数据结构：单调栈
		  单调:单调递增或单调递减（元素随下标持续缩小/扩大） 
		  （顺便说一句，答案满足单调性的题目可以考虑二分） 
		  栈？？是一个先进后出（FILO）的数据结构(就像洗盘子，先洗的叠在下面，拿的时候先拿上面的)
		  栈的基本操作： 入栈，出战
		  展示用的两种方式：1.STL:stack<int> st; 定义一个元素类型为int的栈 
		  						  empty() 栈为空则返回真
		  						  pop() 移除栈顶元素
		  						  push() 在栈顶增加元素
		  						  size() 返回栈中元素数目
		  						  top() 返回栈顶元素(不删除) 
		  					2.手写栈:int stack[N];  定义一个元素类型为int的栈 
		  						  top==0 栈为空则返回真
		  						  top-- 移除栈顶元素
		  						  st[++top]=a 在栈顶增加元素
		  						  top 返回栈中元素数目
		  						  st[top] 返回栈顶元素(不删除)
		  由此可以看出，手写栈其实写起来并不困难，甚至十分简单，建议使用 （当然也可以用STL） 
基本思路： 分析题目，容易得出如果两个建筑物高度相等，那么只需要一张海报
		   还记得单调栈吗？我们围欧胡一个单调不减（注意，这里并不是严格单调递增，可以相等） 的单调栈,
		    			   如当前的高度与栈顶的元素相等时，需要的海报数量-1就行了 (O(N)搞定)
*/ 				
#include<bits/stdc++.h>//万能头，再也不用写一大堆头文件啦 
using namespace std;//命名空间 
const int N=250005;//N<=250005 
int stack[N];//定义一个手写栈 
int top=0,n,rubbish,ans;
//top是栈顶，n是建筑个数，ans表示最少需要几张海报,rubbish顾名思义就是垃圾数据，比如建筑物的高w 
int main()//主函数 
{
	int ans=n;//先假设每一个建筑物都需要贴海报 
	scanf("%d",&n);//输入建筑个数 
	scanf("%d%d",&rubbish,&stack[0]);//输入第一个建筑的高，初始化栈 
	for(int i=1,h;i<n;i++)//依次输入高（这里i<n是因为我的下表是从0开始的） 
	{
		//在线操作 
        scanf("%d%d",&rubbish,&h);//输入建筑物的高（scanf比cin快，建议使用） 
        while(top>0&&stack[top]>h) top--;//为了维持单调性，我们必须把小于h的所有栈内元素都弹出 
	    if(h==stack[top])	ans--;//当有两个建筑等高时，原来的两张海报可以替换为一张海报，海报数量就可以减少一个了 
	    stack[++top]=h;//h加入队列 
	}
	printf("%d",ans);//输出answer 
	return 0;//善始善终，retrun 0返回0不可或缺
}
```


---

## 作者：_Album_ (赞：0)

更好的阅读体验：[传送门](https://payphone-x.top/2019/11/02/luoguP3467/)

------------------------------

## 分析

单调栈入门经典必做题。

考虑所有建筑都一样高时的做法。很显然，当所有建筑高度一致时，我们仅需要一张海报即可覆盖所有的建筑。

再考虑最坏情况的答案。最坏的做法也就是每一个建筑上都挂一张海报，这时的答案为$n$。也就是说，我们的答案一定不会超过$n$。

考虑如何减少海报数量。

不难发现，若有两个不等高的建筑物，则我们所需的海报数量至少为$2$张。

而如果有一个建筑物，它左右的建筑物都比他低，则可以省下一张海报

因此我们可以维护一个单调栈，若栈顶高度大于当前入栈的元素，则弹栈，若等于，则将需要的海报数$-1$。直到小于为止。

剩下的见代码注释。

--------------------------------------------------

## Code[Accepted]

```Cpp
#include <bits/stdc++.h>

#define ll long long
#define I inline

using namespace std;


ll n , k , l;
ll ans;
stack<ll> S;

int main(){
    cin >> n;
    ans = n;
    S.push(-0x3f3f3f3f);    //防止非法访问
    cin >> k >> l;
    S.push(l);
    for(int i = 2; i <= n; i ++){
        cin >> k >> l;
        while(S.top() >= l){
            if(S.top() == l){
                ans --;
            }
            S.pop();
        }
        S.push(l);
    }
    cout << ans << "\n";
    return 0;
}
```

---------------------------------------

# THE END



---

