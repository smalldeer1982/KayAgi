# [USACO06OPEN] County Fair Events S

## 题目背景

题目是经过简写保证不改变原有题意的题目。

## 题目描述

FJ 参加活动。 

他想参加尽可能多的 $N$ 个活动，参加完某个之后可以立刻参加下一个。 

给定 FJ 可参加的活动列表、其开始时间 $T$ 和持续时间 $L$ ，求 FJ 可以参加的最大活动数。 

FJ 每个活动都不会提早离开。

## 说明/提示

$1\le T,L\le 10^5$

$1\le N\le 10^4$

## 样例 #1

### 输入

```
7
1 6
8 6
14 5
19 2
1 8
18 3
10 6```

### 输出

```
4```

# 题解

## 作者：HsKr (赞：8)

贪心。

考虑：结束越早，留给后面的时间就越多，就能参加更多的活动。

思路：将结束时间（即$t_i+l_i$）排序，遍历，如果该活动能参加就参加，不能就拉倒。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
int n;
struct node{//记录t[i]和l[i] 
	int t,l;
}a[10010];
bool cmp(node a,node b){//结束时间早的优先 
	return a.t+a.l<b.t+b.l;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){//输入 
		cin>>a[i].t>>a[i].l;
	}
	sort(a+1,a+n+1,cmp);//按结束时间早的排序 
	int end=a[1].t+a[1].l,ans=1;//总得参加一个吧 
	//end记录最晚的一项的结束时间 
	for(int i=2;i<=n;i++){
		if(a[i].t>=end){//可以参加，即下一项开始时间比上一项结束时间晚 
			ans++;//可以参加 
			end=a[i].l+a[i].t;//这是最晚的结束时间 
		}
	}
	cout<<ans<<endl;
	return 0;
}

```

---

## 作者：Diamiko (赞：6)

## 核心算法：贪心

### 贪心策略

对每个活动依据结束时间进行升序排序，每次选择当前结束时间最早的并且做完上一个活动还可以接着做这个活动的活动（有些拗口，好好理解一下）。

也就是只要放得下，就继续放。

为什么？因为结束时间越靠前，它耽误的时间就越少，那么能留给下一个活动的时间就越多，就越有可能尽量多的参加活动。

现在有两个区间，$end_1<end_2$

那么考虑两种$start_1$和$start_2$的关系

1.$start_1>start_2$


那么两个区间如下图

![](https://cdn.luogu.com.cn/upload/pic/7996.png)

那么选择上面的区间一定是划算的

2.因为已经排除第一种情况，所以所有区间的关系如下：

$start_1<start_2<start_3<...<start_n$

![](https://cdn.luogu.com.cn/upload/pic/7997.png)

如果区间2和区间1不相交，那没有影响

如果相交了，仍然是选第一个

因为如果不选第二个，红色部分的长度是没有影响的

因为它不与任何一个区间相交，区间1的有效部分只剩下灰色部分

而灰色部分又被区间2所包含，成为了第一种情况

所以无论如何，选择第一个总是有利的

选择第一个后，还要标记所以与它相交的区间（不能选了）

事实上，这就是典型的线段覆盖问题。

（以上有部分内容摘自刘汝佳的紫书和 @codesonic 的博客）

### 代码实现

（详见注释）

```cpp
#include<cmath>
#include<cstdio>
#include<algorithm>
using namespace std;
struct Activity
{
    int Start;
    int Last;
    int End;
    //分别是开始时间，持续时间，结束时间
    friend bool operator<(Activity x,Activity y)
    {
        return x.End==y.End ? x.Start<y.Start : x.End<y.End;
        /*
        这里用了三目运算符简化代码
        相当于
        if(x.End==y.End)
            return x.Start<y.Start;
        ekse
            return x.End<y.End;
         */
    }
    //重载运算符以便对结构体进行排序
}ac[10005];
int n;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",&ac[i].Start,&ac[i].Last);
        ac[i].End=ac[i].Start+ac[i].Last;
        //计算出结束时间
    }
    sort(ac+1,ac+n+1);
    //排序
    int ans=1,r=ac[1].End;
    //一定至少会选择一个活动，所以ans初值为1
    //r表示当前活动的结束时间
    //所以一开始就是第一个活动的End
    for(int i=2;i<=n;i++)
    {
        if(r<=ac[i].Start)
        {
            //r<=Start，说明可以进行这个活动
            r=ac[i].End;
            ans++;
            //ans++，活动数加一
            //更新r为这个活动的结束时间
        }
    }
    printf("%d\n",ans);
    return 0;
}
```
题解到这就结束了。

如果还有不理解的地方可以at我或私信我，我会尽力解答。

---

## 作者：Dovuq (赞：3)

这是本蒟蒻的第 $002$ 篇题解，求过。

Updated on 03-29-2020: 修复一些小问题

Updated on 03-30-2020: 增加一些解释并增加一个方案

我们考虑，每次选择怎样的活动才能使最后参加的活动最多呢？

## 方案一：选择开始最早的。

错误。反例：

```
3
1 10000
5 1
9 1
```

正确答案：$2$。参加活动 $2$ 和 $3$。

错误答案：$1$。参加活动 $1$。

开始最早的活动可能持续非常长的时间，不划算。

## 方案二：选择持续时间最短的且按照时间顺序。

错误。反例：

```
3
1 1000
2000 1000
2500 1
```

正确答案：$2$。参加活动 $1$ 和 $2$ 或 $1$ 和 $3$。

错误答案：$1$。参加活动 $3$。

持续时间最短的活动可能非常晚，也不划算。

## 方案三：选择持续时间最短的但不按照时间顺序选。

本人太菜了，想不出反例来，也证明不了它是正确的。哪位大佬如果举出反例或证明正确，可以在评论区留言。

但是，就算它是正确的，也很难实现，如果实现不好就会 $\colorbox{black}{\color{white}TLE}$。所以，我还是建议大家使用方案四。

## 方案四：选择结束最早的。

正确。反例：没有。（还是废话）

选择结束最早的可以为后面的活动留下时间。

下面是 $\colorbox{green}{\color{white}AC}$ 代码，细节见注释。

```cpp
#include <bits/stdc++.h> //万能头文件真好用
using namespace std;
int n,now,ans;
struct event
{
	int start,end; //英文不解释
	void read () //输入不解释
	{
		int a;
		scanf ("%d%d",&start,&a);
		end=start+a;
	}
};
event t[10005];
bool operator< (event a,event b) //天哪，为什么都写 cmp？重载小于号不香吗？
                                 //重载了小于号可以直接使用 sort 排序
{
	return a.end<b.end; //按照结束时间排序
}
int main ()
{
	scanf ("%d",&n);
	for (int i=0;i<n;i++)
		t[i].read();
	sort (t,t+n); //排序
	for (int i=0;i<n;i++)
	{
		if (t[i].start<now) continue; //太早了，不能选
		now=t[i].end; //参加活动
		ans++;
	}
	printf ("%d",ans);
	return 0; //养成好习惯
}
```

---

## 作者：xrdrsp (赞：2)

这是本人的第 $002$ 篇题解。

---

## 1 题意简述

有 $n$ 个事件，要求在时间不冲突的情况下完成尽量多的事件。（完成一个事件后可以立即开始下一个事件。）

## 2 思路分析

这道题就是个贪心题。

贪心，是一种**仅考虑当前决策、不顾全大局**的思想，与 DP（动态规划）正好相反。正因为如此，许多贪心代码很短，许多贪心代码都是错的。

在这道题上，我们该根据什么贪心呢？下面有几个选择，我们需要选出正确的。判别贪心正确与否的方法是找反例和证明。

1. 先做早开始的事件。
1. 先做持续时间短的事件。
1. 先做早结束的事件。

或许你认为还有别的可能性，但这里只列举 $3$ 个。

下面是这三种贪心的证明过程。

### 2.1 先做早开始的事件

表面看看很正确，但如果一个事件开始的时间很早，而持续时间很长，那这个算法就爆炸了。**举出反例**：

输入：

```
3
1 100
2 1
3 1
```

正确的输出：

```
2
```

对“先做早开始的事件”贪心的输出：

```
1
```

所以明显地 `WA` 了。应该先做 `2`，再做 `3`，而根据这个算法，程序认为 `1` 开始的时间早，这样 $100$ 时间过去了，只做了一个事件，忽略了 `2` 和 `3`。所以这种算法是错误的。

### 2.2 先做持续时间短的事件

吸取了上一次的教训，发现事件的持续时间很重要。那么，先做持续时间短的事件是否可行呢？

看看也十分正确，但仍然可以轻松举出反例。

输入：

```
4
1 100
2 2
4 1
5 2
```

正确的输出：

```
3
```

对“先做持续时间短的事件”贪心的输出：

```
2
```

所以又明显地 `WA` 了。应该先做 `2`，再做 `3`，再做 `4`，而根据这个算法，程序认为 `3` 持续的时间短，但先做 `2` 就多做了一件事情。所以这种算法是错误的。

### 2.3 先做结束时间早的事件

吸取了上一次的教训，发现事件的结束时间很重要。那么，先做结束时间早的事件是否可行呢？

看看也十分正确，实际上也十分正确。

为什么呢？

当一个事件结束得较早时，它便为下一个事件留下了更多的时间，就能做更多的事件。所以明显正确。

也举不出反例了。（读者可以自己试试。）

## 3 算法流程

清晰明了。有了 1 的阅读基础，可以得出：先按照结束时间排序，再一个个地判断能否参加。

## 4 代码实现

```c++
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1e4 + 10;

struct Node {           // 定义结构体，存储的是每个事件
    int start;          // 事件的开始时间
    int end;            // 事件的结束时间
    int last;           // 事件的持续时间
} event[N];

bool operator<(Node i, Node j) {
    // 重载运算符，用来对结构体排序。
    // 除此之外，常用的对结构体排序的方法还有自定义比较函数。不懂的可以百度。
    return i.end < j.end;
}

int n;

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {  // 读入
        scanf("%d%d", &event[i].start, &event[i].last);
        event[i].end = event[i].start + event[i].last;  // 计算结束时间
    }
    sort(event + 1, event + n + 1); // 排序
    // 下面遍历每个事件，判断开始时间是否在做的上一个事件的结束时间后。
    int cur = event[1].end;         // 做完这些选择的事件的结束时间。第一个事件肯定做。
    int ans = 1;
    for (int i = 2; i <= n; i++) {
        if (event[i].start >= cur) {// 判断。
            ans++;
            cur = event[i].end;
        }
    }
    cout << ans;
    return 0;
}
```

## 5 总结

这道题用了贪心的思想。这个思想不能随便用，需要证明其正确性或举出反例。这样才能保证不出错。

贪心的思维过程很重要。您在必要的时候可以画图或列式子。如本题，您可以把每个事件的开始和结束的时间连起来简化成线段，一起画到数轴上，整体地观看便于思考。

## 6 其他

这篇题解纯手打（废话），如有任何错误或不妥之处请评论。谢谢。

---

## 作者：Instudy (赞：2)

本题首$ A $者来写题解：

~~开小号来上分~~

这道题就是活动安排（贪心裸题）其实就是求对应数轴选择尽可能多的不相交线段。

于是我们想到一种贪心策略：按照每个活动的结束时间从小到大排序，每次选择最早的结束时间，于是代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct AKIOI{
	int st;
	int ed;
}
a[10010];
bool cmp(AKIOI zhen,AKIOI jia)
{
	return zhen.ed<jia.ed;
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	 {
	 	int T;
	 scanf("%d%d",&a[i].st,&T);
	 a[i].ed=a[i].st+T;
}
	 sort(a+1,a+n+1,cmp);
	 int t=a[1].ed;
	 int ans=1;
	 for(int i=2;i<=n;i++)
	  if(a[i].st>=t)
	  {
	  	ans++;
	  	t=a[i].ed;
	  }
	  printf("%d\n",ans);
	return 0;
}
```


---

## 作者：_zy_ (赞：1)

题目大意：

给定每个活动的时间段，不可重复，求可参加的最大活动数。

--------


- 考虑以起点贪心：

Hack ：
```cpp
3
1 100
2 3
3 4

right 2 (2,3)
wrong 1 (1)
```
显而易见，当起点靠前但是占有的时间也很多时，就会导致后续活动无法再参加。

- 考虑以时间贪心：

Hack：
```cpp
2
1 2
2 1

right 2 (1,2)
wrong 1 (2)
```

对于时间短的而言，如果起始的时间比较靠后，很可能导致前面的活动也无法参加。

- 考虑以终点贪心：

**正确**

证明：

假设两种活动结束时间为 $end1,end2$ ,对于$end1 $ $<$ $ end2 $，如果两种活动没有交叉，选择一种很明显不亏，如果不交叉就可以多选一个。

**代码如下：**
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
#include<map>
#define N 10010
using namespace std;
int re() {
	int p=0,f=1; char i=getchar();
	while(i<'0'||i>'9')	{if(i=='-')  f=-1;i=getchar();}
	while(i>='0'&&i<='9')	p=p*10+i-'0',i=getchar();
	return f*p;
}
int n,ans;
struct zy{	 
	int sta;
	int lst;
	int end;
}e[N];
bool cmp(zy x,zy y) {
	return x.end<y.end;
}
int main()
{
	n=re();
	for(int i=1;i<=n;i++) {
		e[i].sta=re();
		e[i].lst=re();
		e[i].end=e[i].sta+e[i].lst;
	}
	sort(e+1,e+n+1,cmp);
	int now=e[1].end,ans=1; 
	for(int i=2;i<=n;i++)
	if(e[i].sta>=now)  {
		ans++; 
		now=e[i].end;
	}
	cout<<ans<<endl;
	return 0;
}
```
如有不妥，请不要吝啬您的建议.

$qwq$

---

## 作者：Zmr_ (赞：1)

这是本蒟蒻的第一篇题解哦~~~

好了，回归正题

#### 这是一道很不错的区间贪心题，建议学了区间贪心的同学们都去做一做。

--------------------

我们先来了解一下区间贪心：

区间贪心有两种

- 第一种：【算法分析】

算法模型：给你n个闭区间[ai,bi]，在数轴上选尽量少的点，使每个区间内至少有一个点。

算法：首先按b1<=b2<=b3<=···<=bn（都是结束时间）排序。每次标记当前区间的右端点x，并右移当前区间指针，直到当前区间不包含x，再重复上述操作。

如图，选蓝色点不如选红色点（本蒟蒻画画不好，请多多包涵）：

![如图](https://cdn.luogu.com.cn/upload/image_hosting/fbmdchqh.png)
-----

- 第二种：【算法分析】

算法模型：给n个开区间[begini,endi]，选择尽量多的区间，使得两两不交。

做法：首先按照end1<=end2<=......<=endn（都是结束时间）的顺序排序，依次考虑各个活动，如果没有和已经选择的活动冲突，就选，否则就不选。

正确性：如果不选end1，假设第一个选择的是endi，则如果endi和end1不交叉则多选一个end1更划算；如果交叉就把endi换成end1不影响后续选择。

-------------------------

经过了上面的算法分析，我们再来看一看题目：

FJ想参加许多活动，但是一些活动因为时间冲突不可以参加。

他想参加尽可能多的活动，并且参加完一个可以立刻参加下一个。

于是他给你活动的开始时间和持续时间，请你帮忙求他最多可以参加多少活动。

【题目分析】

这一题很明显是第二种区间贪心。

本题给你了开始时间和持续时间，结束时间可以自己直接求出来。

结束时间是很重要的，因为我上面说了，区间贪心首先都是要按结尾时间排序的。

求出了结束时间就可以直接排序，然后轻松解决这道题。

-----------------------------------------

有了上面的分析，代码很容易就写出来了。

下面是我的AC代码：
```cpp
#include<iostream>//输入输出头文件。
#include<algorithm>//sort排序的头文件。
using namespace std;
struct node {
	int t, k;
}b[100001];//结构体。
bool w(node a, node b) 
{ 
	return a.t + a.k < b.t + b.k; 
}//一个自定义函数，修改sort排序的顺序。
int main()
{
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> b[i].t >> b[i].k;
	sort(b + 1, b + n + 1, w);//sort排序。
	int ans = 1;//初始化是1！！这是一个坑点。
	int e = b[1].t + b[1].k;//第一个结束时间。
	for (int i = 1; i <= n; i++)
		if (b[i].t >= e) 
		{ 
			ans++;//可以参加活动的数量。
			e = b[i].t + b[i].k;//更新后面的结束时间。
		}
	cout << ans << endl;//输出结果。
	return 0;//好习惯。
}

---

## 作者：do_while_false (赞：1)

【题目思路】

要想使所参加的活动数更多，我们可以用贪心的思路解决。

首先先按照 E 的值从小到大排序，然后从小到大依次选择最小的可以选择的 E 值，每选一个计数器的值就 $+1$ ，最后输出这个计数器即可。

【代码实现】

```cpp
#include<bits/stdc++.h>
#define MAXN 10000 + 10
using namespace std;
struct node{
	int st;
	int ed;
}a[MAXN];
int n,t,x,ans=1;
bool cmp(node a,node b) {
	return a.ed<b.ed;
}
inline int read() {
	int r=0;bool flag=true;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') flag=false;ch=getchar();}
	while(ch>='0'&&ch<='9'){r=(r<<3)+(r<<1)+(ch^48);ch=getchar();}
	return flag==true?r:~r+1;
}
int main(void) {
	n=read();
	for(int i=1;i<=n;i++) {
	 	a[i].st=read();x=read();
		a[i].ed=a[i].st+x;
	}
	sort(a+1,a+n+1,cmp);
	t=a[1].ed;
	for(int i=2;i<=n;i++)
		if(a[i].st>=t) {
	  		ans++;
	  		t=a[i].ed;
	  	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：lingfunny (赞：1)

# 题意理解
在一个数轴上，有$N$条线段，每条线段的起点为$T$，长度为$L$，求不相交的线段最多有几条。
# 算法分析
很简单的贪心。假设我们每次要选择终点为$E$的线段，当然是要使这个$E$尽可能小。因为当$E$最小的时候，你能选择的线段肯定会更多。
# 代码构造
分析过后，很明显我们要按结束时间从小到大排序。然后记录下上一次选择线段的终点，然后依次对比起点。
# 代码
```cpp
#include <iostream>
#include <algorithm> 		//sort要用
using namespace std;
struct node{
	int strat;
	int end;				//这是终点，而不是长度
};							//结点结构体
bool cmp(node x,node y){
	return x.end<y.end;		//按照刚才分析的，要选择终点尽可能小的
}
node f[10005];
int n;
int ans;					//总共能选择多少条
int end;					//上一次选择线段的终点
int main(){
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>f[i].strat;
		cin>>f[i].end;
		f[i].end+=f[i].strat;//将长度转化为终点
	}
	sort(f+1,f+n+1,cmp);	//排序
	ans=1;					//首先肯定要选择重点最近的那个，也就是f[i]
	end=f[1].end;			//终点设置
	for(int i=2;i<=n;++i){
		if(end<=f[i].strat){//如果之前选择的的终点小于等于现在的起点，也就是这两条线段不相交
			++ans;			//选择了
			end=f[i].end;	//更新end
		}
	}
	cout<<ans;
	return 0;
}
```
比较简单的一题贪心，稍加思考就可以想出来。

完结撒花✿

---

## 作者：zilingheimei (赞：0)

题目：[P6244 [USACO06OPEN]County Fair Events S](https://www.luogu.com.cn/problem/P6244)

### 首先，我们要知道：

- 当一个活动结束时间越早，说明它越可能跟后面的活动相接

- 我们不管在什么情况下，至少得取一个活动

- 结束时间=开始时间+持续时间

- 最早的活动不代表结束时间最早，如：

3

1 2000

2 10

11 10

显而易见，选起始时间最早的并不是最优解，相比之下，比较结束时间就可以达到结果

##### 因此，我们可以将结束时间排序并比较所选的活动的结束时间与当前的活动的开始时间的大小，当满足更早即可

### 说了这么多，还是贴代码吧，注释代码有：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans=1;//必须选一个，所以ans初始化为1 
struct point {
	int s,e,l;//start开始时间 end结束时间 last持续时间 
}a[10010];
bool cmp(point x,point y){
	return x.e<y.e;
} 
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].s>>a[i].l;
		a[i].e=a[i].s+a[i].l;//结束时间=开始+持续 
	}
	sort(a+1,a+n+1,cmp);//排序 
	int now=a[1].e;//不论如何，得选一个，因此选择结束时间最早的 
	for(int i=1;i<=n;i++){
		if(a[i].s>=now){//当满足更早 
			now=a[i].e;//更换当前的活动 
			ans++;//计算器+1 
		}
	}
	cout<<ans;
	return 0;
}

```


---

## 作者：DWT8125 (赞：0)

这道题简直和[P1803](https://www.luogu.com.cn/problem/P1803)一模一样，我们也可以用同样的做法。

## 思路
本题是典型的贪心，本人想到了以下三种做法：

1. 找时间最短的。这是错误做法，如果时间最短的比赛在最后，前面的时间就会白白浪费掉。

1. 找开始时间最早的。这也是错误做法，如果最早开始的比赛时间太长，中间囊括的所有比赛都会错过。

1. 找结束时间最早的。这是正解，如果结束时间越早，后面可能参加的比赛就会越多。

总结：前两种错解都不能保证给后面的比赛留下足够长的时间。特别是第一种方法，留下的时间有一部分是比赛后的，**但还有一部分是比赛前的（又没说能时空穿梭）**。

## 代码
为了您不被棕，请不要抄袭！

（此代码为题解诞生时的[最优解](https://www.luogu.com.cn/record/list?pid=P6244&orderBy=1&status=&page=1)）

```cpp
//P6244 AC代码
#include<cstdio>
#include<algorithm>
using namespace std;
struct race{
	int st,en;
}a[10001];
bool cmp(race a,race b){return a.en<b.en;} //选最早结束的在前
int main(){
	int n,cnt=0,nowtime=0,t; scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&a[i].st,&t);
		a[i].en=a[i].st+t; //计算结束时间
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++) //nowtime是此时此刻的时间（要先置0）
		if(nowtime<=a[i].st){nt=a[i].en; cnt++;}
	printf("%d",cnt);
	return 0; //别忘了
}
```


---

## 作者：EDqwq (赞：0)

### 思路：

考虑贪心。

我们将每一个活动当作一个线段。

可以发现，对于两个线段（前面的开头端点在前面，后面的在这个的后面），如果他们的头和尾没有重合部分，说明他们不相交（在这个题中，端点可以重合）。

仔细观察，对于每一个线段，只要他的头大于上一个我们取的线段的尾，说明它可以取，这就是我们的贪心策略。

但是直接杂乱无章地取，会发现完全错误。

所以需要排序，由于我们要用后面一个线段的头和上一个的尾做对比（大于对比），按照尾巴从小到大来排序。

我们用一个end变量存上一个我们取的线段的尾巴，如果现在这个大于end，直接ans ++，end更新。

于是问题便解决了。

***

### 注意事项：

1. 注意，输入的L是**持续时间**，千万别搞成区间结尾，我卡了挺久的。。。

1. end要赋初始值，为第一个的末尾。

1. 要从第二个开始循环判断，而不是第一个，因为第一个默认选择。

另外，

#### end是不能用作全局变量名的！！！

***

### 代码：

```cpp
#include<bits/stdc++.h>
 
#define int long long
 
using namespace std;
 
int read(){
   int s = 0,w = 1;
   char ch = getchar();
   while(ch < '0' || ch > '9'){if(ch == '-')w = -1;ch = getchar();}
   while(ch >= '0' && ch <= '9')s = s * 10 + ch - '0',ch = getchar();
   return s * w;
}
 
struct node{
    int x;
    int y;
}a[1000010];
 
bool cmp(node x,node y){
    return x.y < y.y;
}
 
int n;
int ans = 1;
int endd;
 
signed main(){
    cin>>n;
    for(int i = 1;i <= n;i ++){
    	int x;
    	a[i].x = read();
    	x = read();
    	a[i].y = a[i].x + x;
	}
    sort(a + 1,a + n + 1,cmp);
    endd = a[1].y;
    for(int i = 2;i <= n;i ++){
        if(a[i].x >= endd){
            endd = a[i].y;
            ans ++;
        }
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：tobie (赞：0)

[一道类似的题](http://ybt.ssoier.cn:8088/problem_show.php?pid=1323)

贪心。

按照常识来理解，结束得越早，留给后面的活动的时间就越多。

所以我们可以想出这样一种贪心方案：

将每一个活动的结束时间（$T+L$）从小到大进行排序。

接下来记录一个`last`值，记录上一个选中的活动的结束时间。

那么如果我们遍历到的这个活动的开始时间大于`last`值，就可以选择这个活动，同时更新`last`值。

于是我们就可以写出代码了。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
struct node{
	int l,r;
}a[10009];
int n,x,y;
int ans=0,last=-1;
bool cmp(node x,node y)//将结束时间排序
{
	return x.r<y.r;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&x,&y);
		a[i].l=x,a[i].r=x+y;//保存这个活动的开始和结束时间。
	}
	sort(a+1,a+n+1,cmp);//排序
	for(int i=1;i<=n;i++)//贪心主要过程
	if(a[i].l>=last)
	{
		ans++;
		last=a[i].r;
	}
	printf("%d",ans);
	return 0;//好习惯
}
```

---

## 作者：bystander_silent (赞：0)

这题和P1803很像。我的思路是用贪心。先把所有的活动按结束时间排序，保证完成这个任务后剩的时间最多，就可以保证最后得到的是最大值。
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
struct node{
	int l;
	int r;
}a[1000005];
bool cmp(const node &a,const node &b)
{
	return a.r<b.r;
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d %d",&a[i].l,&a[i].r);
		a[i].r+=a[i].l; 
	}
	sort(a+1,a+n+1,cmp);
	int left=-1;//看区间从多少开始
    int cnt = 0;
    for(int i = 1; i <= n; i++) 
        if(a[i].l >= left) 
		{
            left = a[i].r;
            //a数组已按右端点递增排序 
            cnt ++;
        }
    printf("%d", cnt);
	return 0;
}
```


---

## 作者：ezyannn9 (赞：0)

算法：**贪心**

------------
即：**永远从可参加的活动中找到最早结束的**

------------
用结构体排序出结束时间，同时保留开始时间，当可执行时按结束早晚顺序执行

------------
贪心讲究的就是每一步都取当时最优解，对于总体来说就自动是最优解，放到这里就是，我每一步结束得越早，可选择的下一项活动自然越多，而不管选择什么活动权值都是加一，如果每个活动权值不同就得DPorDFS了

------------

证明可以用反证法：大致就是假设ai项并非最早结束，往后也不可能执行更多的项目

------------

```c
#include<stdio.h>
struct class{
int ag;//开始时间
int ov;//结束时间
}a[10005];
int cmp(const void *x,const void *y){
     struct class xx = *(struct class*)x;
      struct class yy = *(struct class*)y;
      return xx.ov-yy.ov;
  }//快排结束时间
int main()
{
    int n=0,i=0,j=0,k=0;
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        scanf("%d %d",&a[i].ag,&k);
        a[i].ov=a[i].ag+k;//输入每一项结束时间
    }
    qsort(a, n, sizeof(a[0]), cmp);//结构体快排
    j=a[0].ov;k=1;//从第一步开始
    for(i=0;i<n;i++)
    {if(a[i].ag>=j)//可执行，则自动执行最早结束
        {k++;//计数
            j=a[i].ov;}
    }
    printf("%d",k);
    return 0;
}

```
求过

---

## 作者：WxjzKK (赞：0)

$$\Huge{\text{P6244 [USACO06OPEN]County Fair Events S}}$$

**这是一道贪心好题，但是对于贪心初学者来说，还是有一定的难度的**

## 1.贪心原则

我们把占用一个时间段的$party$看成时间轴上的一根线：

        3---------------------------------------12
                         7------------------11
           4------------------------------------12

很明显，参加2号$party$要比一号和三号划算
那是不是只要比它短就要优先呢，显然不是，看看[这里](https://www.luogu.com.cn/paste/ypc9xl4d)就知道结果了
我们举个例子:

        3----------------7
                     6------8
                            8-------------------12

那，什么贪心方法才是正确的呢？？？大家请看：

        3--------------------------------8
                                         8---------------14

如果要是两个$party$能够都参加，那么两个$party$就不能在同一时间段，必须满足一个$party$的开始时间必须要大于等于另一个的结束时间，也就是说，$party$的结束时间会决定是否可以参加此$party$。

那我们再思考，是否$party$结束时间越小，能加入的$party$就越多呢？确实是的，如果你不信，[这个](https://www.luogu.com.cn/paste/al5y68kf)可以证明。

那么，我们的方式已经确定好了。

## 2.算法流程

首先我们要排序一下，排序方式就是上面推出的。

```cpp
bool comp(node a,node b)
{
	return a.end==b.end?a.start>b.start:a.end<b.end;
}
```
接着，就可以一个一个贪心去寻找了。

## 3.代码实现
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<iomanip>
#include<string>
#include<stack>
#include<queue>
#include<vector>
using namespace std;
struct node
{
	int start,end;
}activ[10001];//结构体排序更方便
bool comp(node a,node b)
{
	return a.end==b.end?a.start>b.start:a.end<b.end;//排序
}
int main()
{
	int n,l,time,ans=1;//time表示party结束时间，ans表示最多能参加party数
	cin>>n;
	for (int i=1;i<=n;++i)
	{
		cin>>activ[i].start>>l;activ[i].end=activ[i].start+l;
	}
	sort(activ+1,activ+n+1,comp);//快排
	time=activ[1].end;
	for (int i=2;i<=n;++i)
		if (activ[i].start>=time)
		{
			++ans;time=activ[i].end;//贪心
		}
	cout<<ans;
	return 0;
}
//严禁抄袭代码
```


---

