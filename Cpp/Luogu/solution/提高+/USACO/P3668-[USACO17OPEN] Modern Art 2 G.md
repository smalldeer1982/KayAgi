# [USACO17OPEN] Modern Art 2 G

## 题目描述

伟大的牛艺术家 Picowso 对标准的二维艺术作品感到厌倦（同时也对其他人抄袭她的作品感到沮丧），于是决定转向一种更极简主义的一维风格。

尽管她的画作现在可以用一个长度为 $N$（$1 \leq N \leq 100,000$）的一维颜色数组来描述，但她的绘画风格保持不变：她从一个空白画布开始，并在其上叠加一系列“矩形”颜料，而在这种一维情况下，这些矩形仅仅是区间。她使用每种颜色 $1 \ldots N$ 恰好一次，尽管和以前一样，某些颜色最终可能会被完全覆盖。

令 Picowso 非常沮丧的是，她的竞争对手 Moonet 似乎已经找到了如何复制这些一维画作的方法，使用的策略与之前的问题类似：Moonet 会绘制一组不相交的区间，等待它们干燥，然后再绘制另一组不相交的区间，依此类推。在整个过程中，Moonet 只能为每种颜色绘制最多一个区间。请计算 Moonet 复制给定的一维 Picowso 画作所需的最少轮数。

## 说明/提示

在这个例子中，颜色 1 的区间必须在颜色 4 和 5 的区间之前绘制，因此至少需要两轮。

## 样例 #1

### 输入

```
7
0
1
4
5
1
3
3```

### 输出

```
2```

# 题解

## 作者：qiianr (赞：14)

[洛谷传送门](https://www.luogu.org/problemnew/show/P3668)

**题目大意**

每次对一段连续区间进行染色，可以染不同的颜色，但每种颜色每次只能染一段连续区间而且每种颜色染的区间要连续而不相交，求最少染几次能染成目标状态？

**解析**

记录每一种颜色的起始点以及终点，可以想象，如果染色次数要最少，那么最外一层的颜色要最先涂(如下图)

![](http://a4.qpic.cn/psb?/V12DWXjw1jCGFo/ESgznlQsC8ymZN5XaZCG5ffzOySCINDHVonEoywgWlg!/b/dDMBAAAAAAAA&ek=1&kp=1&pt=0&bo=QAZiA0AGYgMBACc!&tl=1&tm=1539846000&sce=0-12-12&rf=viewer_311)

左边的情况显然红色先染，绿色后染，覆盖前面的红色，是可行的

右边的情况显然是不可行的

可以想象出一个栈,当前点的的起始位置加入栈，如果这一段有颜色不同于这个点的，就不可能，如上图右边，碰到当前点的终止位置，就出栈，最大染色次数就是栈最大的size,可以画个图试一下，当size 变化为 1 2 3 2 1 1 2 3 2 1 时，两边明显是可同时进行的，所以答案应该只要记录最大值

0是不填颜色，所以它的出栈位置记录为n+1，先让0入栈，并让其最后出栈，但是这并不会记录进染色次数，所以答案要-1

```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=1e5+5;
int n,a[maxn],book[maxn],ans,top;
int s[maxn],e[maxn],stack[maxn];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d",&a[i]);
		if(!s[a[i]]) s[a[i]]=i;
		e[a[i]]=i;
	}
	e[0]=n+1;a[n+1]=0;//不填的位置结束在n+1 
	for(int i=0,x;i<=n+1;++i){//i从0开始使0入栈
		x=a[i];
		if(i==s[x])stack[++top]=x,ans=max(ans,top);
		if(x!=stack[top]){printf("-1");return 0;}
		if(i==e[x])top--;
	}
	printf("%d",ans-1);
	return 0;
}
```

---

## 作者：LEle0309 (赞：6)

[题目传送门](https://www.luogu.com.cn/problem/P3668)

这题评蓝虽然有点偏高，~~但淼一道蓝题还是不错的~~。

思路类似楼顶题解，但本蒟蒻想解释的更详细一点，~~而且楼顶图炸了~~。

蒟蒻第一篇蓝题题解，大佬轻喷。

#### 题目大意：

给一条布条染色，每次可以染一个**连续的区间**，要求**每种颜色只能染一次**，颜色可以覆盖，但**一块布条上第二次涂色要等一天**（今天染了，明天才能染）。

#### 分析：

随时记录一种颜色的起点和终点，然后**按出现顺序**开始**从头到尾**染色。遇到一种不同的颜色就扔进栈里，染完了就扔出来，并更新最大值。

如果当前碰到了和栈顶不同的颜色，则说明这种颜色之前染过，**因为是按顺序的**。

举例：

数据 `1 1 2 1 2 1`

第一遍，全染 $ 1 $，然后把第 $ 3 $ 至 $ 5 $ 条染成 $ 2 $，第三遍再第 $ 4 $ 个布条处再次出现 $ 1 $，程序结束。

[AC 记录](https://www.luogu.com.cn/record/114976007)

上代码：
```cpp
#include<iostream>
#include<cstdio>
#include<stack>
using namespace std;
int n,a[100005],ed[100005],i,st[100005],sta[100005],ans,tp;//STL栈不知道为什么寄了，故换手打栈
int read()//教练said要开快读
{
	int res=0,flag=0;
	char ch;
	if((ch=getchar())=='-')flag=1;
	else if(ch>='0'&&ch<='9')res=ch-'0';
	while((ch=getchar())>='0'&&ch<='9')res=res*10+ch-'0';
	return flag?-res:res;
}
int main()
{
    n=read();
    for(i=1;i<=n;i++)
    {
        a[i]=read();
        if(st[a[i]]==0)st[a[i]]=i;//如果该颜色尚未出现，则记录开始
        ed[a[i]]=i;//随时记录结束（每一次出现都可能是结束）
    }
    ed[0]=n+1,a[n+1]=0;//把0考虑成一种颜色
    //所以0再第n+1个布条处结束
    //自然而然a[n+1]是0的结束点，所以a[n+1]=0
    for(i=0;i<=n;i++)
    {
        int x=a[i];
        if(i==st[x])
        {
            sta[++tp]=x;//把新颜色x压栈
            ans=max(ans,tp);//更新最大值
        }
        if(x!=sta[tp])
        //碰到了和栈顶不一样的颜色
        //因为是按第一次出现顺序枚举的，所以栈顶都是还没结束的颜色
        //而碰到了不一样的颜色，则该颜色在之前已经涂完了
        //则说明这个颜色需第二遍染色，所以直接退出
        {
            cout<<-1;
            return 0;
        }
        if(i==ed[x])tp--;//结束了，更新栈顶
      	  //我原以为这里会影响ans,后来才发现ans是在之前更新的，所以不影响	
    }
    cout<<ans-1;//0需染颜色，故减1
    return 0;//水了道蓝题！！！
}
```

---

## 作者：zhousy (赞：3)

不必考虑这么复杂

**每种颜色只能用一次，所以，假设在涂红色的时候，必须一笔涂到最后一个红色的格子**

因为可以同时涂色，用栈来维护花费的时间即可

```cpp
#include<iostream>
#include<cstring>
#include<cmath>
#include<stack>
#include<algorithm>
using namespace std;

class ppp{public: int k;int j;int shi;
};//开始位置，结束位置，消耗时间 
stack <ppp> zsy;
int n;
int se[100005] = {0}; //最后一个颜色i出现的位置 
int tu[100005] = {0}; //储存图 

int main()
{
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++)
	{
		int a;
		cin >> a;
		se[a] = i;
		tu[i] = a;
	}
	for(int i = 1; i <= n;i++)
	{
		if(tu[i] == 0) continue;
		else
		{
			ppp temp;
			temp.k = i;
			temp.j = se[tu[i]];
			temp.shi = 1;
			zsy.push(temp);
			i = se[tu[i]];
		}
	}
	int sss = 0; //最大花费时间 
	while(!zsy.empty())
	{
		ppp temp = zsy.top();
		if(temp.shi > sss) sss = temp.shi;
		zsy.pop();
		for(int i = temp.k + 1; i <= temp.j-1;i++)
		{
			if(tu[i] == tu[temp.k]) continue;
			if(tu[i] == 0)
			{
				cout << -1 << endl;
				return 0;
			}
			if(tu[i] != tu[temp.k] && se[tu[i]] > temp.j)
			{
				cout << -1 << endl;
				return 0;
			}
			ppp temp1;
			temp1.k = i;
			temp1.j = se[tu[i]];
			temp1.shi = temp.shi + 1;
			zsy.push(temp1);
			i = se[tu[i]];
		}
	}
	cout << sss << endl;
	return 0; 
} 

```

---

## 作者：yydfj (赞：2)

这是本蒟蒻第三十四次写的题解，如有错误点请好心指出！

## 问题简述

给定一个长度为 $n$ 的目标区间，还有一个长度为 $n$ 的初始区间，初始区间内全部值为 $0$，你可以一次操作给初始区间内的某块连续的区域赋上同一个大于 $0$ 的值，在一个时间单位内能多次进行上述操作，但是赋过的值不能再赋一次，在同一个区域内后赋的值会把先赋的值覆盖，问最少要花多少时间可以使该区间变为目标区间，若目标区间不合法则输出 $-1$。

## 解法综述

发现每种值只能赋一次，那么我们将某个值出现的最左边的位置 $l$ 和最右边的位置 $r$ 求出来后，按题意将初始区间内 $l$ 到 $r$ 的位置全赋成这个值。

那如何区分赋值的先后关系？我们发现如果目标区间合法的话，求出来的每个值的 $l$ 和 $r$ 要么互不相关，要么互相嵌套。我们按从小到大的顺序每遇到一个 $l$ 就加上一个嵌套层数，每遇到一个 $r$ 就减去一个嵌套层数，那么答案就是当前位置嵌套层数的最大值。

目标区间不合法的情况有两种，第一种是某个值的 $l$ 到 $r$ 的区间内包含 $0$，包含 $0$ 说明我们要给初始区间赋两次以上这样的值，显然不符合题意；第二种是某两个值的 $l$ 和 $r$ 既不互不相关，也不互相嵌套，即嵌套错乱的情况。在求 $l$ 和 $r$ 的时候就可以特判掉第一种情况，某一个值所在的嵌套层数不同说明是第二种情况。

## 代码描述

```cpp
#include<cstdio>
#include<iostream>
using namespace std;
typedef long long ll;
ll n,a[100005],b[100005],c[100005],l[100005],r[100005],bz,ans;
int main()
{
    scanf("%lld",&n);
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
    for(int i=1;i<=n;i++)//求出每个值的l和r
    {
        if(a[i]==0)
        {
            bz=i;
            continue;
        }
        if(!l[a[i]]) l[a[i]]=r[a[i]]=i;
        else if(bz>l[a[i]])//在求l和r的时候特判掉第一种情况
        {
            printf("-1");
            return 0;
        }
        else r[a[i]]=i;
    }
    for(int i=1;i<=n;i++)
    if(l[a[i]])
    {
        b[l[a[i]]]++;//每遇到一个l就加上一个嵌套层数
        b[r[a[i]]+1]--;//每遇到一个r就减去一个嵌套层数
        l[a[i]]=0;
    }
    for(int i=1;i<=n;i++)
    {
        b[i]+=b[i-1];
        if(!c[a[i]]) c[a[i]]=b[i];
        else if(c[a[i]]!=b[i])//某一个值所在的嵌套层数不同说明是第二种情况
        {
            printf("-1");
            return 0;
        }
        ans=max(ans,c[a[i]]);//答案是当前位置嵌套层数的最大值
    }
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：2021cyq (赞：2)

# P3668 [USACO17OPEN] Modern Art 2 G 题解
## 题目大意

每个时间可以对一些没有交集的区间集体变成几种颜色（即为一个区间变成一种不同的颜色），且一种颜色自始至终只能用一次，问一个全为零的区间变成给定区间的所需要的最小时间，如果不行则输出 $-1$。

## 解法

注意这句话：**且一种颜色自始至终只能用一次**。

所以如果涂一种颜色则需要把最前以及最后出现的颜色的整个区间都涂上。

考虑答案怎么算？

```
7
0 1 4 5 1 3 3
```

我们发现在第 $2$ 个数到第 $5$ 个数一共有两层，即为外面有一层，应为里面没有包含关系，所以只算一层。

比如这个 $1\ 1 \ 2\ 3\ 3\ 4\ 4\ 2\ 1$ 就算三层，即为($1$ 套 $2$，$2$ 套 $3,4$)。

那么答案显然为套的层数的最大值。

感性理解一下，意思就是先放最外面，再放里面，不能同时放，所以只能分开放，但如果没有包含关系的就可以分开放。

如何判 $-1$ 的情况？

$1\ 2\ 1\ 2$ 是一种无解情况。

即为两个不同颜色之间不包含且有交集。

考虑如何求最大套的层数？

用栈！

如果一个数是这种颜色的开头，就把它加入栈中，然后判一下无解的情况。即为如果当前的栈顶不为当前数的颜色则为无解。同时，如果这个数是这种颜色的结尾，就把它弹出栈，每一次 $ans=max(ans,top-1)$。

为什么要 $-1$？

应为 $0$ 因该开始就入栈，最后才出站，是为了判如下的无解情况：$1\ 0\ 1$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int sta[N],a[N];
int st[N],nd[N];
int ans,n;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=N-1;i++)st[i]=1e9;
	for(int i=1;i<=n;i++)
	{
		st[a[i]]=min(st[a[i]],i);
		nd[a[i]]=max(nd[a[i]],i);
	}
	st[0]=0,nd[0]=n+1;
	for(int i=0;i<=n+1;i++)
	{
		if(i==st[a[i]])sta[++sta[0]]=a[i];
		if(a[i]!=sta[sta[0]])
		{
			printf("-1");
			return 0;
		}
		ans=max(ans,sta[0]);
		if(i==nd[a[i]])sta[0]--;
	}
	printf("%d",ans-1);
}
```

---

## 作者：sel_fish (赞：2)

### solution：栈

**本篇题解是受到大佬[qiianr](https://www.luogu.org/user/103198)的启发，如果侵权，请联系删除**

1. 为了保证最优解，我们必须要**先涂最外层**，举个例子：AAABCBBBA,(A,B,C分别代表一种颜色)我们先把这些都涂上A，然后中间都涂上B，最后再在最上面那一个涂上C，这就是最优解的情况

2. 对于每个颜色，我们记录这个颜色的开始位置和结束位置，我们可以很清楚的看到**越到最外层涂的颜色，开始位置越晚，结束位置越早**，所以我们可以**用一个栈来维护当前栈顶的颜色**

3. 并且我们涂的区间**不能重叠**，举个例子，A和B分别代表一种颜色：AABBAAB，根据上面所推得，我们应该找最外层的颜色，但是因为A和B重叠，所以这种情况是不合法的

4. 枚举画条上的每一个点，对于一个颜色如果这个颜色的开始位置等于现在枚举的位置，那么我们就把这个颜色压入栈，如果当前颜色和栈顶颜色不同，那么我们直接输出无解即可

5. 如何寻找答案，因为我们都把颜色放进栈中，所以我们只需要比较答案和栈内的元素个数，最后取最大值即可

6. 如果当前枚举的点等于这个元素的结束位置，那么我们直接弹出栈顶即可

7. 后一点，也没什么可说的，加一些优化，手打max，加个位运算快读，随手加个register，开O2 38ms，不开47ms，处于最优解第一页

**AC代码**

```cpp
#include<cstdio>
#define si 100005
#define re register int
using namespace std;
int n,ans,tp,a[si],st[si],ed[si],sta[si];
inline int read() {
	int x=0,cf=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {
		if(ch=='-') cf=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return x*cf;
}
inline int max(int A,int B) { return A>B?A:B; }
int main() {
	n=read();
	for(re i=1;i<=n;i++) {
		a[i]=read();
		if(!st[a[i]]) st[a[i]]=i;//如果这个元素还没有开始位置，记录开始位置
		ed[a[i]]=i;//随时记录结束位置
	}
	ed[0]=n+1,a[n+1]=0;
	for(re i=0;i<=n+1;i++) {
		int x=a[i];
		if(i==st[x]) {//当前枚举等于开始位置，推入栈
			sta[++tp]=x;
			ans=max(ans,tp);//取最大值
		}
		if(x!=sta[tp]) {//当前元素和栈顶元素颜色不同，输出无解
			printf("-1");
			return 0;
		}
		if(i==ed[x]) tp--;//等于结束位置，弹出
	}
	printf("%d",ans-1);
	return 0;
}
```


---

## 作者：kczno1 (赞：2)

考虑从后往前的过程，

相当于每次选择一些颜色，

这些颜色所出现的所有位置必须是联通的，

也就是所有间隔都是已出现过的颜色。

每次贪心的把能选的都选了即可。

最后还有颜色没选则-1。

实现可以用双向链表，记录每个颜色当前被分成了多少段。

```cpp
#include<bits/stdc++.h>

const int N=1e5+5;
int cnt[N];
int col[N],pre[N],next[N];
int st[N],top;
void merge(int x,int y)
{
    if(col[x]==col[y]) 
    if(--cnt[col[x]]==1)st[++top]=x;
    pre[y]=x;next[x]=y;
}

void add(int x)
{
    int p,n;
    for(p=x;col[p]==col[x];p=pre[p]);
    for(n=x;col[n]==col[x];n=next[n]);
    merge(p,n);
}

int main()
{
    freopen("1.in","r",stdin);
    int n,i;
    scanf("%d",&n);
    for(i=1;i<=n;++i)
    {
        scanf("%d",col+i);
        if(!col[i])continue;
        ++cnt[col[i]];
    }
    
    int num=0;
    for(i=1;i<=n;++i)
    if(cnt[i])++num;
    
    for(i=1;i<=n;++i)
    if(cnt[col[i]]==1)st[++top]=i;
    for(i=1;i<=n;++i)
    if(col[i]) merge(i-1,i);
    
    int ans=0,head=1;
    while(head<=top)
    {
        ++ans;
        int t0=top;
        while(head<=t0)
        {
            add(st[head]);
            ++head;
        }
    }
    if(top<num)puts("-1");
    else printf("%d\n",ans);
}
```

---

## 作者：jyz666 (赞：1)

# 题解 P3668 【[USACO17OPEN]Modern Art 2 G】

[传送门](https://www.luogu.com.cn/problem/P3668)

### 题意概述

现在你有一块长为N的画布，每次可以选择一段**连续的**区间进行颜色填涂，新颜色会覆盖旧颜色。

在所有的填涂中每一种颜色**只能用1次**。如果不合法输出“-1”。

首先，啥叫填涂不合法：

![](https://tva3.sinaimg.cn/large/007i4MEmgy1fyurtthabyj30n702aa9t.jpg)

这明显合法，只要先涂绿再涂红即可。

![](https://tva4.sinaimg.cn/large/007i4MEmgy1fyurvoxyo3j30n602pgld.jpg)

而这怎么涂也无法完成，所以我们可以总结出一个规律：

**如果画布上出现了交错的颜色，必不合法！**

所以每次记录ans时要判断一下与栈顶的起始点是否相同，如果不同直接返回-1。开始时间记录进栈中，到结束时减栈即可。

如有不懂，详见注释。

### 上代码》》

```
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define inf 0x7f7f7f7f
using namespace std;
typedef long long ll;
typedef unsigned int ui;
typedef unsigned long long ull;
inline int read(){
    int x=0,f=1;char ch=getchar();
    for (;ch<'0'||ch>'9';ch=getchar())    if (ch=='-')    f=-1;
    for (;ch>='0'&&ch<='9';ch=getchar())  x=(x<<1)+(x<<3)+ch-'0';
    return x*f;
}
inline void print(int x){
    if (x>=10)     print(x/10);
    putchar(x%10+'0');
}
const int N=1e5;
int stack[N+10],fir[N+10],val[N+10],las[N+10];
int main(){
    int n=read(),top=0,ans=0;
    for (int i=1,x;i<=n;i++){
        x=val[i]=read();
        if (!fir[x])    fir[x]=i;
        las[x]=max(las[x],i);      //对于每种颜色，记录开始点和最后的结束点
    }
    val[las[0]=n+1]=0;
    for (int i=0;i<=n+1;i++){
        int x=val[i];
        if (i==fir[x])  stack[++top]=x,ans=max(ans,top);     //遇到开始点就入栈
        if (stack[top]!=x){puts("-1");return 0;}    //如果一个点不是不是开始点，并且不与栈顶元素相同，则不合法
        if (i==las[x])  top--;    //是结束点就减栈
    }
    printf("%d\n",ans-1);
    return 0;
}

```

### _四本足の馬でさえつまずく、強さも勝利も永遠じゃないわ_ 


---

## 作者：hejianxing (赞：0)

[link](https://www.luogu.com.cn/problem/P3668)

## 题意

有一条长度为 $n$ 的画布。初始时全部为 $0$。每次染色可以将一个区间染成同一种颜色，每种颜色只能染一次。每次操作可以染色若干次，但是染色的区间两两不相交。颜色可覆盖。问最少操作多少次能够使画布变成 $a_1,a_2,\dots,a_n$。若无法做到则输出 `-1`。


## 题解

发现对于最外面的颜色肯定是最早涂的，颜色会构成一个包含关系。区间有交叉则不合法。可以拿一个栈存储颜色，如果遍历到这个颜色第一次出现的位置，那么将这个元素压入栈中。遍历到颜色的结尾，就弹出元素。

容易发现，栈大小的最大值就是答案。因为每种颜色只能涂一次，所以每种颜色一定是涂出现位置的最左边和最右边之间。那么栈里面的元素都可以理解为还没有涂的颜色。这些颜色是满足包含关系的，也就是说不能同时涂。

考虑无解的情况。对于每个 $a_i$，若其不是这种颜色的第一次出现的位置，且栈顶的元素与其不同，就可以判定为无解。这说明在颜色 $a_i$ 的应涂区间中出现了别的颜色，同时这个颜色与 $a_i$ 不构成包含关系。也就是说，无论先涂两种颜色中的哪一种，都会有颜色被覆盖掉，无法变成目标状态。


时间复杂度 $O(n)$。



## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
int n, a[N], s[N], e[N], ans = 0, st[N], tp = 0;//s[i] 表示颜色 i 最早出现的位置，e[i] 表示颜色 i 最晚出现的位置
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]), s[a[i]] = !s[a[i]] ? i : s[a[i]], e[a[i]] = i;
	s[0] = 0, e[0] = n + 1;
	for (int i = 0; i <= n + 1; i++) {
		if (s[a[i]] == i) st[++tp] = a[i], ans = max(ans, tp);
		if (a[i] != st[tp]) { printf("-1"); return 0; }
		if (e[a[i]] == i) tp--;
	}
	printf("%d", ans - 1);
	return 0;
}
```

---

## 作者：ZnPdCo (赞：0)

读错题了……

![](https://cdn.luogu.com.cn/upload/image_hosting/qsxvsa9u.png)

没有递归的题解，我来交一发。

首先，我们知道如果涂一种颜色，则需要把最前以及最后出现的颜色的整个区间都涂上。所以把输入转换为一个有头有尾的线段：

如图（以下不同颜色分别表示不同区间）：

![](https://cdn.luogu.com.cn/upload/image_hosting/9qwims6w.png)

我们可以转换为以下表示方式：

```
1~3
2~2
4~4
4~5
```

代码很容易可得到：

```c++
for(ll i = 1; i <= n; i++) {
	scanf("%lld", &a[i]);
	if(a[i] == 0) continue;									// 0不算入区间
	if(!t[a[i]]) {
		t[a[i]] = i;
	}
	else {
		vis[a[i]] = 1;
		s[++cnt] = (side){t[a[i]], i};
		t[a[i]] = i + 1;									// 记得加一
	}
}
for(ll i = 1; i <= n; i++) {								// 只出现过一次，需要补上
	if(!vis[a[i]] && a[i]) {
		s[++cnt] = (side){t[a[i]], t[a[i]]};
		vis[a[i]] = 1;
	}
}
```

---

转换为以上边的线段表示方式，然后很显然就是求线段最深的深度。

我们就可以递归了。

把线段**按右端点排序**，然后递归。我们会遇到以下情况（下面 `u` 表示当前线段，`v` 表示枚举子线段，`fa` 表示父线段）：

1. 在父线段的区间外，说明这个不在我们的递归讨论范围内，如果我们讨论了，返回到父节点时就会多算入父节点之外的最深深度：

   ![](https://cdn.luogu.com.cn/upload/image_hosting/nj5x1mqy.png)

   这个在我们的区间外，所以记得跳出，因为我们不能统计在内。

2. 在父线段的区间内，但在当前线段的区间外，说明这个在我们的递归讨论范围内，但我们要重置寄存器（我们只能求深度最大值，如果我们不重置，就会导致两个不同区间的深度累加）：

   ![](https://cdn.luogu.com.cn/upload/image_hosting/p35perdc.png)

3. 与当前线段有交点：

   ![](https://cdn.luogu.com.cn/upload/image_hosting/83agj2ai.png)

   这个肯定是输出 `-1`，十分显然。可以举例： `1 2 1 2`

4. 在父线段的区间内，在当前线段的区间内，进去递归，返回深度，累加到寄存器：

   ![](https://cdn.luogu.com.cn/upload/image_hosting/gw5495h1.png)

```c++
ll dfs(ll u, ll fa) {
	ll sum = 0, child_sum = 1;
	for(ll v = u + 1; v <= cnt; v++) {
		if(s[v].x < s[fa].x) {									// 下面的情况和题解一一对应
			sum = max(sum, child_sum);
			return sum;
		} else if(s[v].y < s[u].x || s[u].y < s[v].x) {
			sum = max(sum, child_sum);
			child_sum = 1;
			u = v;
		} else if(s[v].x < s[u].x) {
			printf("-1");
			exit(0);
		} else {
			ll res = dfs(v, u);
			child_sum += res;
		}
	}
	sum = max(sum, child_sum);
	return sum;
}
```

---

但是我们还有：

```
5
1 0 1 0 1
```

这个肯定是 `-1` 的，因为一个区域一旦涂色就无法去掉了。所以记得需要特判前缀和：

首先先求出每一位的前缀和，当前节点为 `0` 时，前缀和加一，连线段时判断如果线段端点前缀和不同，就说明线段内有 `0`，直接无脑输出 `-1`。

```c++
for(ll i = 1; i <= n; i++) {
	scanf("%lld", &a[i]);
	sum[i] = sum[i - 1] + (a[i] == 0);						// 计算前缀和
	if(a[i] == 0) continue;									// 0不算入区间
	if(!t[a[i]]) {
		t[a[i]] = i;
	}
	else {
		vis[a[i]] = 1;
		s[++cnt] = (side){t[a[i]], i};
		if(sum[t[a[i]] - 1] != sum[i]) {					// 区间内有0
			printf("-1");
			exit(0);
		}
		t[a[i]] = i + 1;
	}
}
```

---

聪明的你肯定发现了，这么递归是会超时的，所以我们返回时还要返回当前枚举到的子节点 `v`。然后把递归完成后记得更新 `for` 的位置。因为里面的已经计算过了。

```c++
node dfs(ll u, ll fa) {
	ll sum = 0, child_sum = 1;
	for(ll v = u + 1; v <= cnt; v++) {
		if(s[v].x < s[fa].x) {									// 下面的情况和题解一一对应
			sum = max(sum, child_sum);
			return (node){sum, v};
		} else if(s[v].y < s[u].x || s[u].y < s[v].x) {
			sum = max(sum, child_sum);
			child_sum = 1;
			u = v;
		} else if(s[v].x < s[u].x) {
			printf("-1");
			exit(0);
		} else {
			node res = dfs(v, u);
			child_sum += res.w;
			v = res.i - 1;										// 不这么做会超时，因为里面的都计算过了，再计算肯定没有那么深。
		}
	}
	sum = max(sum, child_sum);
	return (node){sum, n + 1};
}
```

---

全部代码：

```c++
#include <cstdio>
#include <algorithm>
#include <cstring>
#define ll long long
using namespace std;
ll n;
ll a[100010];
ll t[100010];
ll sum[100010];

struct side {
	ll x, y;
} s[100010], g[100010];

struct node {
	ll w, i;
};
ll cnt;

bool vis[100010];


node dfs(ll u, ll fa) {
	ll sum = 0, child_sum = 1;
	for(ll v = u + 1; v <= cnt; v++) {
		if(s[v].x < s[fa].x) {									// 下面的情况和题解一一对应
			sum = max(sum, child_sum);
			return (node){sum, v};
		} else if(s[v].y < s[u].x || s[u].y < s[v].x) {
			sum = max(sum, child_sum);
			child_sum = 1;
			u = v;
		} else if(s[v].x < s[u].x) {
			printf("-1");
			exit(0);
		} else {
			node res = dfs(v, u);
			child_sum += res.w;
			v = res.i - 1;										// 不这么做会超时，因为里面的都计算过了，再计算肯定没有那么深。
		}
	}
	sum = max(sum, child_sum);
	return (node){sum, n + 1};
}

void solve(ll l, ll r) {
	if(l == r) return;
	ll mid = (l + r) >> 1;
	solve(l, mid);
	solve(mid + 1, r);

	ll pos1 = l, pos2 = mid + 1;
	for(ll i = l; i <= r; i++) {
		if(pos2 > r || (pos1 <= mid && s[pos1].y > s[pos2].y)) {
			g[i] = s[pos1++];
		} else {
			g[i] = s[pos2++];
		}
	}

	for(ll i = l; i <= r; i++) s[i] = g[i];
}

int main() {
	scanf("%lld", &n);

	for(ll i = 1; i <= n; i++) {
		scanf("%lld", &a[i]);
		sum[i] = sum[i - 1] + (a[i] == 0);						// 计算前缀和
		if(a[i] == 0) continue;									// 0不算入区间
		if(!t[a[i]]) {
			t[a[i]] = i;
		}
		else {
			vis[a[i]] = 1;
			s[++cnt] = (side){t[a[i]], i};
			if(sum[t[a[i]] - 1] != sum[i]) {					// 区间内有0
				printf("-1");
				exit(0);
			}
			t[a[i]] = i + 1;
		}
	}
	for(ll i = 1; i <= n; i++) {								// 只出现过一次，需要补上
		if(!vis[a[i]] && a[i]) {
			s[++cnt] = (side){t[a[i]], t[a[i]]};
			vis[a[i]] = 1;
		}
	}
	if(cnt == 0) {
		printf("0");
		exit(0);
	}

	s[0].x = 0;
	s[0].y = n + 1;

	solve(1, cnt);

	node res = dfs(1, 0);

	printf("%lld", res.w);
}
```



---

## 作者：Celebrate (赞：0)

[我的博客](https://blog.csdn.net/zsyzClb/article/details/84889805)

方案1 ： 拓扑排序

记录头和尾，然后理清楚每种颜色的关系，并对入度为0的点进行排序，感觉好复杂，虽然我一开始也是这样想的

这样首先会炸内存，时间也有可能会炸

方案2 ： 栈

因为不管颜色混成怎么样的一坨，时间都是最高的层数，没毛病吧，所以我们就直接用栈了

首先记录当前的点是哪一个点的开头或者结尾，如果不是就为0

90代码

```cpp
#include <iostream>
using namespace std ;
 
const int N = 1e5 + 10 ;
int n , a[N] ;
int s[N] , t[N] ; //s为当前点是哪一个点的开头，t表示当前点是那一个点的结尾
int x[N] , y[N] ;
int top , ans = 0 ; //top表示栈顶，ans表示最大值
int main() {
    cin >> n ;
    for ( int i = 1 ; i <= n ; i ++ ) {
        cin >> a[i] ; y[a[i]] = i ;
        if ( x[a[i]] == 0 ) x[a[i]] = i ;
    }
    for ( int i = 1 ; i <= n ; i ++ ) {
        if ( x[i] != 0 ) s[x[i]] = i ;
        if ( y[i] != 0 ) t[y[i]] = i ;
    }
    for ( int i = 1 ; i <= n ; i ++ ) { //枚举每一个点
        if ( a[i] == 0 ) { //如果中断了
            if ( top != 0 ) {  //如果栈里面还有颜色没有结束
                cout <<  "-1" << endl ;  //就直接放回-1
                return 0 ; 
            }
            continue ; 
        }
        if ( s[i] != 0 ) top ++ , ans = max ( ans , top ) ; //如果这是开头，就top++
        if ( t[i] != 0 ) top -- ; //否则就top-- ， 注意一个点可能是开头和结尾
    }
    cout << ans << endl ;
    return 0 ;
}

```

这个方法很明显是不对的，能过90%的数据已经是个奇迹了

原因就是这个代码只判断了0打断颜色的情况，比较片面

比如说这个数据：
```cpp
5
1
2
1
2
1
```
代码输出2

正确答案应该是-1

能过90分应该是因为数据很大，而且有多个出现错误的地方

所以我们还要再打一个栈的数组，不能只保留栈顶

100分代码

```cpp
#include <iostream>
using namespace std ;
 
const int N = 1e5 + 10 ;
int n , a[N] ;
int s[N] , t[N] ;
int x[N] , y[N] ;
int top , sta[N] , ans = 0 ;
int main() {
	//freopen( "testdata.in","r",stdin ) ;
	cin >> n ;
	for ( int i = 1 ; i <= n ; i ++ ) {
		cin >> a[i] ;
		if ( a[i] == 0 ) continue ;
		 y[a[i]] = i ;
		if ( x[a[i]] == 0 ) x[a[i]] = i ;
	}
	for ( int i = 1 ; i <= n ; i ++ ) {
		if ( x[i] != 0 ) s[x[i]] = i ;
		if ( y[i] != 0 ) t[y[i]] = i ;
	}
	for ( int i = 1 ; i <= n ; i ++ ) {
		if ( s[i] != 0 ) sta[++top] = s[i] , ans = max ( ans , top ) ;
		if ( sta[top] != a[i] ) { cout << "-1" << endl ; return 0 ; } //如果当前的颜色不是最上面那层的颜色，说明数据有误 
		if ( t[i] != 0 ) top -- ; //到终点就出栈 
	}
	cout << ans << endl ; //输出 
	return 0 ;
}

```

---

## 作者：littleming (赞：0)

用栈做。。

当时打月赛用dfs的，结果没注意到有-1，就re了一个点。。后来改对了。。

现在忘了怎么改的。。

栈：
发现每种颜料是一层包一层的，用栈存。。

若两种颜料有相交，直接-1

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
int n;
int a[100008],l[100008],r[100008];
int s[100008],top;
int tmp,ans;
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        if(!l[a[i]])    l[a[i]]=i;
        r[a[i]]=i;
    }
    for(int i=1;i<=n;i++){
        if(a[i]==0){
            if(top){
                cout<<-1;
                return 0;
            }
            else continue;
        }
        if(l[a[i]]==i){
            if(top&&r[a[i]]>r[s[top]]){
                cout<<-1;
                return 0;
            }
            s[++top]=a[i];
            tmp++;
            ans=max(ans,tmp);
        }
        if(r[a[i]]==i){
            top--;
            tmp--;
        }
    }
    cout<<ans;
    return 0;    
}
```

---

