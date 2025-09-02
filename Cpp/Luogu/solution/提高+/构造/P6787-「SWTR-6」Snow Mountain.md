# 「SWTR-6」Snow Mountain

## 题目背景

**题目背景与解题无关。**

**题目描述最下方有简化版题意。**

天空中飘着雪，放眼望去白茫茫一片。小 A 拿着地图，四处探寻着。

突然，只见前方有一个洞穴。出于好奇心，小 A 走了进去。

洞穴里黑漆漆一片，一眼望不到尽头。道路的两旁尽是白骨，显然，这是曾经来这里探险的人们的残骸。小 A 打了一个冷颤。

这时，小 A 留意到了地上的一张纸片。打开来一看，上面竟写着：

$$\texttt{Please contact lydsy2012@163.com!}$$

## 题目描述

> 洞穴里有一些水晶，每个水晶有一个能量值 $a_i$。**能量值有大有小，但不会相同。** 这些神秘的水晶上附着邪恶势力的灵魂。现在你的任务是摧毁这些水晶，并让它们释放出的邪恶能量能量尽可能小。
> 
> 你可以选择两个未被摧毁的水晶 $i,j$，将它们摧毁并释放出 $\min(a_i,a_j)\times k$ 的邪恶能量。其中 $k$ 表示这是第 $k$ 次摧毁。
> 
> 不过有一些**无序**水晶对 $(x,y)$，如果你将它们一并摧毁，就会发生强大的共振导致山洞倒塌，使你葬身其中！

带着这张纸片，小 A 来到了山洞的尽头，果然发现了 $n$ 个水晶（$n$ 为偶数）。正如纸片上所说，每个水晶都有一个能量值 $a_i$。

对这些水晶进行一番观察，小 A 发现了一个规律：每个水晶 $i$ 在**所有能量值比它大**的水晶中，只会和**最多一个**发生共振，记其编号为 $x_i$。

现在小 A 知道了 $a_i,x_i$，你能帮助他求出摧毁这些水晶释放出邪恶能量之和的最小值吗？无法摧毁输出 $\texttt{-1}$。否则先输出最小值，再输出摧毁方案。

若摧毁方案有多种，输出任意一种即可。

- 需要注意的是，摧毁后水晶编号不会发生改变。

---

简化版题意：

给定两个长为 $n\ (2|n)$ 的序列 $a,x$，满足 $a_i$ 互不相同且如果 $x_i \neq -1$，那么 $a_{x_i}>a_i$。

现在需要进行 $\frac{n}{2}$ 次删除操作：选择两个未被删除的数 $a_i,a_j$ 满足 $x_i\neq j$ 且 $x_j\neq i$，并用 $\min(a_i,a_j)\times k$ 的代价将这两个数从序列 $a$ 中删去（删除后剩余元素下标不变），其中 $k$ 表示这是第 $k$ 次删除。

求删除所有数的最小代价与方案。无解输出 $\texttt{-1}$。若方案有多种，输出任意一种即可。

## 说明/提示

**「样例 3 说明」**

无法摧毁所有水晶，因为水晶 $4$ 无法被摧毁。

**「数据范围与约定」**

**本题采用捆绑测试。**

- Subtask 1（5 points）：$n=2$；
- Subtask 2（20 points）：$n \leq 10$；
- Subtask 3（15 points）：$x_i=-1$；
- Subtask 4（20 points）：$n\leq 3\times 10^3$；
- Subtask 5（15 points）：$a_i$ 升序排列，即 $a_i<a_{i+1}\ (1\leq i<n)$；
- Subtask 6（24 points）：无特殊限制。
- Subtask 7（1 point）：hack 数据。

对于 $100\%$ 的数据，$2 \leq n \leq 5 \times 10^5$，$1 \leq a_i \leq 10^9$。  
保证 $n$ 为偶数且 $a_i$ 互不相同。  
保证答案不超过 $2^{63}-1$。

**「帮助/提示」**

请注意 IO 优化。

**「Special Judge」**

**本题使用 SPJ。**

**请认真阅读输出格式。** 输出格式有误可能导致 UKE。

若你的输出的第一行与答案的第一行不同，你将获得本测试点的 $0\%$ 分数。

若无解且第一行相同，你将获得本测试点的 $100\%$ 分数。

若有解且第一行相同，但方案有误，你将获得本测试点的 $60\%$ 分数。

若有解且第一行相同，方案正确，你将获得本测试点的 $100\%$ 分数。

另附 `checker` 与 `testlib.h`。

百度网盘链接：[link](https://pan.baidu.com/s/1Tk-8-UiLzCpOuPVuoCcbbQ)，提取码：b7eg。

## 样例 #1

### 输入

```
4
1 4 2 3
3 -1 -1 2```

### 输出

```
4
3 2
1 4```

## 样例 #2

### 输入

```
4
5 7 1 3
-1 -1 1 1```

### 输出

```
7
1 2
3 4```

## 样例 #3

### 输入

```
4
1 9 4 5
4 -1 4 2```

### 输出

```
-1```

# 题解

## 作者：sfmmdm (赞：20)

首先，我们假设，没有不能配对的水晶，那么我们可以很容易想到一个贪心思路：

因为每次只计算能量值小的水晶，也就是说，只要排序后在前 $\dfrac{n}{2}$ （以下简称“前半段”）个数中找数和后 $\dfrac{n}{2}$ （以下简称“后半段”）**随便**找一个数配对即可，而且要从大到小选择。

简单证明一下，首先第一个很显然，如果把其中两对按“一前一后”配对的数换成“两前”和“两后”，那结果就由两个在前半段的数换成一个后半段和前半段的数统计而来，很明显不是最优的。

第二个，这个可以联系“排队接水”问题的贪心策略，假设我们给能量值为 $x$ 和 $y$ 的两个出现在前半段的水晶分别在第 $k$ 和 $k+1$次销毁（后半段的很明显不用考虑），若 $x<y$，那么

先销毁 $x$ 再销毁 $y$ 的代价：

$$kx+(k+1)y=k(x+y)+y$$

先销毁 $y$ 再销毁 $x$ 的代价：

$$ky+(k+1)x=k(x+y)+x$$

因为 $x<y$，所以很明显先销毁大的更优。

现在加入了限制条件，说有些水晶不能同时销毁，但是，题目还有一个很重要的条件：对于每个水晶，有很多不能和它一起销毁，但其中能量值比它大的只有一个。

如果一个水晶不能和所有水晶配对，那此情况无解，除此之外，不存在无解的可能，因为这些不能配对的水晶最多只能连成一棵树，除了菊花图以外，不可能找到有点无法配对的情况，只要顺序合理，一定有解。

我们称有和后半段水晶不能配对的前半段水晶称为“锁定的水晶”，配对一对水晶，让前半段的一些水晶不被锁定称为“解锁”（当时我思考时用的词，这里顺着思路说下来）

而我们只要将“一前一后”地配对，而后半段的水晶无论怎么选都不会影响结果，所以只要后半段不存在能锁定前半段全部水晶的水晶，就一定可以一前一后地配对完所有水晶，而不会影响结果。

至于这种情况的构造方法，很明显，只要保证后半段没有水晶会锁定前半段剩余所有水晶即可。在此基础上思考构造策略即可，为方便实现，我们在每次配对时，都选择能解锁水晶最多的水晶。

如果有一颗后半段的水晶锁定了前半段所有水晶，我们只要先用一个能与这个水晶配对的最小的水晶先与之配对，**一定要先配这对，因为很明显这对的能量值是最大的。**

很明显这对水晶一定是后半段的，然后我们只要将分界点前移，此时前半段所有点都已被解锁，接下来就可以完全自由地配对了。

```cpp
#include <bits/stdc++.h>
#include <queue>
using namespace std;
int n;
bool flag;
struct crystal {
    int a,x,cnt,pos;//a,x为题目意思，cnt为比它小的水晶和它不能配对的个数，pos为排序前水晶的编号
} b[500005];
bool cmp(const crystal &x, const crystal &y) {
    return x.a<y.a;
}
bool operator <(const crystal &x, const crystal &y) {
    if(x.cnt==y.cnt) return x.a>y.a
    return x.cnt<y.cnt;
}
long long ans;
priority_queue <crystal> h;//注意我在实现时优先队列是以cnt排序的，而cnt并不等于锁定的水晶数（就是这里的策略和前面说的略有不同），但这种策略也是可以保证出解的，为方便实现这里就用这种。
int main() {
    scanf("%d",&n);
    for(int i=1; i<=n; i++) scanf("%d",&b[i].a);
    for(int i=1; i<=n; i++) scanf("%d",&b[i].x);
    for(int i=1; i<=n; i++) b[i].pos=i;
    if(n==2) {
        if(b[1].x==-1&&b[2].x==-1) printf("%d\n1 2\n",min(b[1].a,b[2].a));
        else printf("-1\n");
        return 0;
    }
    for(int i=1; i<=n; i++) if(b[i].x!=-1) b[b[i].x].cnt++;
    sort(b+1,b+n+1,cmp);
    for(int i=(n>>1)+1; i<n; i++) {
        h.push(b[i]);
    }
    if(h.top().x!=-1&&h.top().cnt==n-2) {//最后一个水晶暂不入堆，此时倒数第二水晶点cnt为n-2且x不为-1就表示它和所有水晶都无法配对。
        printf("-1\n");
        return 0;
    }
    h.push(b[n]);
    if(h.top().cnt==n-1) {//最后一个水晶如堆后，如果cnt==n-1，就代表它无法和前面的所有水晶配对
        printf("-1\n");
        return 0;
    }
    crystal t=h.top();//只有cnt最多的水晶才可能锁定前半段的所有水晶
    for(int i=1; i<=(n>>1); i++) {
        if(b[i].x!=t.pos) flag=1;
    }
    if(flag) {
        for(int i=(n>>1); i>=1; i--) {
            ans+=1ll*((n>>1)-i+1)*b[i].a;
        }
        printf("%lld\n",ans);
        for(int i=(n>>1); i>=1; i--) {
            t=h.top();
            if(b[i].x!=t.pos) {
                printf("%d %d\n",b[i].pos,t.pos);
                h.pop();
            } else {//如果cnt最大的水晶不能和改水晶配对，那第二大的一定可以（我们只对后半段的水晶入堆）
                h.pop();
                printf("%d %d\n",b[i].pos,h.top().pos);
                h.pop();
                h.push(t);
            }
        }
    } else {
        int p;
        for(p=(n>>1)+1; p<=n; p++) {
            if(b[p].a<t.a) {
                if(b[p].x!=t.pos) break;
            }
            if(b[p].a>t.a) {
                if(t.x!=b[p].pos) break;
            }
        }
        ans+=min(b[p].a,t.a);
        for(int i=(n>>1)-1; i>=1; i--) {
            ans+=1ll*((n>>1)-i+1)*b[i].a;
        }
        printf("%lld\n",ans);
        printf("%d %d\n",t.pos,b[p].pos);
        h.pop();
        for(int i=(n>>1)-1,j=n>>1; j<=n&&i>=1; i--,j++) {//一定注意分界点换了
            if(j==p||b[j].a==t.a) j++;
            printf("%d %d\n",b[i].pos,b[j].pos);
        }
    }
    return 0;
}
```

---

还没完，这里补充一下每次选择 $cnt$ 最大的水晶的正确性证明。($cnt$ 含义看代码注释)

假设在某一时刻，前后半段剩余 $x$ 个水晶，前半段**最多**有 $k$ 个水晶被同一水晶锁定。

假设 $x-k>1$，则后半段配对的水晶可以自由选择。

假设 $x-k=1$，则锁定前半段水晶为 $k$ 的水晶的 $cnt \ge x-1$，而后半段的水晶除了最后一个，所有 $cnt < x-1$。

我们只要在这种情况避免选到最后一个即可。


---

## 作者：a___ (赞：13)

update(20/8/28):感谢[@wssstc](https://www.luogu.com.cn/user/62296) dalao 指出问题。（之前【三】里多处将a、c写反）
_____

算法标签：$\color{#FFFFFF}\colorbox{#E74C3C}{\small\texttt{贪心}}$  

______

比赛现场的时候觉得 div2T4 应该不会很难，而且当时发现了一个有利贪心的性质，所以我就去写贪心了。思路其实也很简单，就是一边贪心一边看当前有什么性质就好了。当时写的代码常数极大（还有错），但 AC 了。本题解里的代码是我再次修改并简化过的，请放心食用。       

_____

- 对于一些东西表示的含义的定义或重定义   

对于所有 $x_i\not=-1$，使 $x_i=a_{x_i}$。此时对于所有 $x_i\not=-1$，$x_i$ 表示含义为能量值为 $a_i$ 的水晶在其本身贡献答案时不能且仅不能与能量值为 $x_i$ 的水晶同时摧毁。    

定义以下若出现 $(a,b)$，均表示能量值为 $a$ 和 $b$（$a<b$）的一组水晶。   

______

- 首先考虑 $\forall x_i,x_i=-1$ 的情况。

显然，我们选择以能量值前 $\frac n 2$ 小的水晶作为答案贡献。方案即为每次选 **能量值前 $\frac n 2$ 小的水晶之一** 和 **能量值前 $\frac n 2$ 大的水晶之一**。    

最优性证明：   
1. 关于选择能量值前 $\frac n 2$ 小的水晶作为答案贡献   
   考虑一种选了能量值前 $\frac n 2$ 大的水晶的方案，显然将这次贡献换成任意一个能量值前 $\frac n 2$ 小的水晶来做都会更优。    
   即若 $\exists a<b$，则有 $ka<kb$。   

2. 关于按照同时摧毁的一组水晶中较小的（贡献答案的）能量值从大到小摧毁     
	考虑一种先摧毁能量值较小水晶的方案，发现若将这次操作与之后的能量值更大的方案对调后一定更优。   
   即若 $\exists a>b,k_1<k_2$，则有 $ak_1+bk_2<bk_1+ak_2$（可由 $(a-b)k_1<(a-b)k_2$ 得到）。

_____

- 现在考虑 $\exists x_i\not=-1$ 的情况。   

显然我们如果仍取能量值前 $\frac n 2$ 小的水晶来贡献答案一定最优，但这种情况可能无法实现。我们希望 **能够近似这种取值**。   

我们考虑一种贪心策略，即 **尽量不把能量值较大的水晶作为答案贡献**。**具体地，按能量值从小到大枚举每一个水晶，找到一个能量值最大的可以和它一同摧毁的水晶，将这两个水晶一同摧毁，直到仅剩两个水晶为止**。由于一个水晶最多与一个能量值比他大的水晶不能同时摧毁，所以每次相当于选择了剩余水晶的最大值或次大值一同摧毁。于是每次选择的一组水晶一定是 **能量值较小的能量值在前 $\frac n 2$ 个内，较大的在后 $\frac n 2$ 个内**。   
也可以考虑结合我的实现代码分析：   
```cpp
int p1=n-1,p2=n;
for(i=1;i<(n>>1);i++)
{
	++cnt;ans[cnt].x=i;
	if(a[p2].a==a[i].x)ans[cnt].y=p1;
	else ans[cnt].y=p2,p2=p1;
	--p1;
}
```   

____

记最后剩余了 $(a,b)$（代码中的 `p1`，`p2`）。   
注：以下提到的 $x_y$ 均指 **当 $a_i=y$ 时** 按照以上所指 $x_i$ 的值。

一、   
若 $(a,b)$ 可以同时摧毁，则将其摧毁。此时显然最优。    

**否则一定有 $x_a=b$**。   

____

二、   
对于 **任一组** **已规定需要被同时摧毁** 的水晶 $(c,d)$，此时一定有 $c<a<b,d$。（由以上所证明的部分性质可得）   

由于 $a<d$ 且 $(a,b)$ 不能同时摧毁（$x_a=b$），则 $(a,d)$ 一定可以同时摧毁（$\forall d,x_a\not=d$）。    


若存在一组 $(c,d)$ 使 $x_c\not=b$，则我们选择将 $a,b,c,d$ 按 $(a,d),(c,b)$ 摧毁。此时最小值（贡献答案的）仍为 $a,c$ 不变，所以答案一定最优。   

**否则一定有 $\forall c,x_c=b$**。   

____

三、   
此时，由于 $c<a$ 且 $(c,b)$ 不能同时摧毁（$x_c=b$），则 $(c,a)$ 一定可以同时摧毁（$\forall c,x_c\not=a$）。    

若存在一组 $(c,d)$ 使 $x_d\not=b$ 且 $x_b\not=d$，则我们选择将 $a,b,c,d$ 按 $(c,a),[(d,b)\ or\ (b,d)]$ 摧毁。此时最小值（贡献答案的）变为 $c,b$ 或 $c,d$，我们按 $d$ 从小到大枚举 $(c,d)$ 交换，答案一定最优。（最大可能的 $a$ 换 $b$ 或者换最小的 $d$）   

**否则一定有 $\forall d,x_d=b$ 或 $x_b=d$**。   
____

四、   
此时，有【$x_a=b$】且【$\forall c,x_c=b$】且【$\forall d,x_d=b$ 或 $x_b=d$】，则：   
对于 $\forall a_i\not=b$，均有 $x_{a_i}=b$ 或 $x_b=a_i$。**即 $b$ 本身不能够与任何一个水晶同时摧毁**。那么显然不存在任何一种成功摧毁所有水晶的方案。

___

- 最后若存在合法方案，我们就按照 $c_i$ 从大到小摧毁每一组水晶即可。  
- 注意特判 $n=2$ 的情况。    

____

[代码实现（仅 70 行）](https://www.luogu.com.cn/paste/4kxn81jx)   
[AC记录](https://www.luogu.com.cn/record/37540867)     

____

ps1：顺带一提，这题数据很水，我赛场代码判断顺序出了问题，结果竟然还 AC 了。   
以下是一组对我赛场代码的HACK数据，留给各位参考：   
in:   
```plain   
10
1 2 3 4 5 6 7 8 9 10
-1 -1 8 8 8 -1 -1 -1 -1 -1
```   
out:   
```plain   
35
5 10
4 6
3 7
2 9
1 8
```   
ps2：不知道这题 Subtask 5 是什么意思，直接将所有数输入排个序不就达成了这个性质吗qwq。

---

## 作者：BzhH (赞：2)

假设我们已经构造出一种方案摧毁了所有的水晶，要求最小的花费，显然是一个经典的贪心问题，直接从大到小选即可。

那么问题就在与我们要如何构造出一个满足条件的方案并让它的花费最小，题目中保证了 $n$ 为偶数，并且 $a_{x_i}>a_i$，不妨将这个数列升序排列，令前半段为 $[a_1,...,a_{mid}]$，后半段为 $[a_{mid+1},...,a_n]$ （这里的 $a_i$ 表示水晶的编号），显然，如果能够让前半段的所有数与后半段匹配，那么花费一定能够最小，并且在排完序过后，我们不用考虑后半段是否会与前半段共振，只需要考虑前半段即可。

这里给出一种配对的方法，用一个双端队列将后半段存下来，每一次匹配都与队头或队尾中不与 $a_i$ 号水晶共振的匹配,能够证明，这种方法至少能够匹配 $\frac{n}{2}-1$ 对水晶，并且剩下的一定是 $a_{mid}$，设后半段剩下的水晶为 $a_x$，这时候我们可以这样处理，找到之前已经匹配的水晶，看一下能否交换，如果还不行，那么就说明前半段不能全部都和后半段匹配。

这时候考虑另外一种方案，让前半段与后半段的一个水晶分别来与剩下的匹配，所以我们需要找出一对已经匹配的水晶将它们拆开来分别与剩下的匹配，注意在找的时候如果有在右半段的水晶的能量值更小的匹配满足条件，就用更小的，如果一对都找不出来，那么就说明一定无解。

至此，我们就已经构造出了一个合法的方案，注意在输出的时也要按贪心时选择的顺序输出，因为这个WA了好多次。

代码
```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#define ax first
#define ay second
#define mk make_pair
using namespace std;
const int N = 5e5 + 5;
typedef pair<int, int> PII;

struct node
{
    int a, x, id;
    bool operator < (const node t) const
    {
        return a < t.a;
    }
} p[N];
int x[N], a[N];
vector<PII> ans;

bool cmp(PII x, PII y)
{
    return min(a[x.ax], a[x.ay]) > min(a[y.ax], a[y.ay]);
}

int main()
{
    int n;
    scanf("%d", &n);
    int tot = n;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &p[i].a);
        p[i].id = i, a[i] = p[i].a;
    }
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &p[i].x);
        if (p[i].x == -1)
            p[i].x = ++tot;
        x[i] = p[i].x;
    }
    int len = n >> 1;
    sort(p + 1, p + 1 + n);
    int l = len + 1, r = n;
    for (int i = 1; i <= len; i++)
    {
        if (p[i].x != p[r].id)
            ans.push_back(mk(p[i].id, p[r--].id));
        else if (p[i].x == p[r].id && p[i].x != p[l].id)
            ans.push_back(mk(p[i].id, p[l++].id));
    }
    if (ans.size() != len)
    {
        for (int i = 0; i < len - 1; i++)
        {
            if (x[ans[i].ax] != p[l].id && p[len].x != ans[i].ay)
            {
                ans.push_back(mk(ans[i].ax, p[l].id)), ans[i].ax = p[len].id;
                break;
            }        
        }
    }
    if (ans.size() != len)
    {
        int rec = -1;
        for (int i = 0; i < len - 1; i++)
        {  
            if (x[ans[i].ax] != p[len].id && x[ans[i].ay] != p[l].id && p[l].x != ans[i].ay)
                if (rec == -1 || ans[i].ay < ans[rec].ay)
                    rec = i; 
        }
        if (rec != -1)
        {
            ans.push_back(mk(ans[rec].ax, p[len].id));
            ans[rec].ax = ans[rec].ay, ans[rec].ay = p[l].id;            
        }
    }
    if (ans.size() != len)
        puts("-1");
    else
    {
        sort(ans.begin(), ans.end(), cmp);
        long long sum = 0;
        for (long long i = 0; i < len; i++)
            sum += min(a[ans[i].ax], a[ans[i].ay]) * (i + 1);
        printf("%lld\n", sum);
        for (int i = 0; i < len; i++)
            printf("%d %d\n", ans[i].ax, ans[i].ay);
    }
    return 0;
}
```

---

## 作者：anda (赞：2)

本题考察了排序的熟练应用和对数据的处理。

首先我们把边连起来，统计每个点的度数，如果有的点度数等于n-1，那就是不合法的。

然后按照权值排序，并预处理出是否所有的都相等，是否存在无解。

然后把每个点初始位置，以及每个位置的初始点记录下来以及尝试将i和i+n/2配对，然后开始分类讨论。

如果都相等且没有无解，我们就去寻找第一个能跟第一个数匹配的数，剩下的首尾配对。

反之，分三种情况。
全部配对好的：不管。
有两个没配对好的，每个向后移动一位。
有一个没配对好的，找到第一个合法的交换要配对的数。

最后按照自己和配对的的最小值排序，统计答案，输出即可。

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#define int long long 
using namespace std;
int n,cnt,flag,deg[500001],vis[500001],ctop,btop,h[500001],htop,ans,hs[500001],b[500001],vis1[500001],scnt;
struct node{
	int a,x,p,id,iid;
}a[500001],c[500001];
bool cmp1(const node &a,const node &b){
	return a.a<b.a;
}
bool cmp2(const node &x,const node &y){
	return min(x.a,c[x.p].a)>min(y.a,c[y.p].a);
}
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
	scanf("%lld",&a[i].a);a[i].id=i;	
	}
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i].x);
		if(a[i].x!=-1){
			if(++deg[i]==n-1||++deg[a[i].x]==n-1){
				cout<<-1;return 0;
			}
		}
	}
	sort(a+1,a+n+1,cmp1);
	for(int i=1;i<=n/2;i++){
		if(a[1].x==a[i].x)cnt++;
		if(a[i].x==-1)flag=1;
	}
	for(int i=1;i<=n;i++)hs[a[i].id]=i;
	for(int i=1;i<=n;i++){
		if(a[i].x!=-1)a[i].x=hs[a[i].x];
	}
	if(cnt!=n/2||flag){
		for(int i=1;i<=n/2;i++){
			a[i].p=i+n/2;
			if(a[i].x==a[i].p)h[++htop]=i;
		}
		if(htop>=2){
			int x=a[h[htop]].p;
			for(int i=htop;i>=2;i--)a[h[i]].p=a[h[i-1]].p;
			a[h[1]].p=x;
		}
		if(htop==1){
			for(int i=1;i<=n/2;i++){
				if(a[i].x!=a[h[htop]].x){
					swap(a[i].p,a[h[htop]].p);
					break;
				}
			}
		}
		for(int i=1;i<=n;i++)c[i]=a[i];
		sort(a+1,a+n/2+1,cmp2);
	    for(int i=1;i<=n/2;i++)ans+=i*min(a[i].a,a[a[i].p].a);
	    cout<<ans<<endl;
	    for(int i=1;i<=n/2;i++)cout<<a[i].id<<" "<<a[a[i].p].id<<endl;
	}
	else{
		int k=a[1].x;
	for(int i=1;i<=n;i++){
		if(a[k].x!=i&&a[i].x!=k&&i!=k){
			a[k].p=i;a[i].p=k;vis[k]=vis[i]=1;break;
		}
	}
	for(int i=1;i<=n;i++)if(!vis[i])b[++btop]=i;
	for(int i=1;i<=btop/2;i++){
		a[b[i]].p=b[btop-i+1];
	    a[b[btop-i+1]].p=b[i];
	}memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++)a[i].iid=i,c[i]=a[i];
	sort(a+1,a+n+1,cmp2);
	for(int i=1;i<=n;i++)vis1[a[i].iid]=i;
	for(int i=1;i<=n;i++){
		if(!vis[a[i].id]&&!vis[a[vis1[a[i].p]].id]){scnt++;
			ans+=scnt*min(a[i].a,a[vis1[a[i].p]].a);
			vis[a[i].id]=vis[a[vis1[a[i].p]].id]=1;
		}
	}
	cout<<ans<<endl;memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++){
		if(!vis[a[i].id]&&!vis[a[vis1[a[i].p]].id]){
			ans+=i*min(a[i].a,a[vis1[a[i].p]].a);
			cout<<a[i].id<<" "<<a[vis1[a[i].p]].id<<endl; 
			vis[a[i].id]=vis[a[vis1[a[i].p]].id]=1;
		}
	}
	}
}
```


---

## 作者：lyhqwq (赞：0)

# Solution

油雀题。

首先将序列排序。

首先根据排序不等式，现消除最大的一定不劣。再贪心的考虑，将前半段作为贡献一定更有，我们考虑将前一半和后一半尽可能多的一一对应。

题目告诉我们，一个数最多和一个比他大的数发生共振，而和哪一个后半段的数匹配是没有影响的。考虑将后半段的数扔进双端队列，每次分别和头尾匹配，这样一定能匹配 $\frac{n}{2}-1$ 对。

先考虑贡献不变的情况，显然我们需要找到一个匹配，将其交换。

如果不能，意味着我们需要将一个后半段的数作为贡献，考虑让贡献增加的尽可能少，所以剩下 $a_{\frac{n}{2}}$ 一定最优。

我们找到一个匹配，使其匹配中的后半段数尽可能小，让前半段和前半段匹配，后半段和后半段匹配即可。如果找不到，无解。

# Code
```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int N=5e5+5;
struct node{
    int id;
    int v;
    bool operator < (const node &rhs)const{
        return v<rhs.v;
    }
}a[N];
int n;
int x[N],p[N];
vector<pair<int,int> > ans;
void print(){
    LL sum=0;
    int k=1;
    for(int i=n;i>=1;i--){
        if(!p[i]) continue;
        sum+=1ll*a[i].v*k;
        k++;
        ans.push_back(make_pair(i,p[i]));
    }
    printf("%lld\n",sum);
    for(int i=0;i<ans.size();i++) printf("%d %d\n",a[ans[i].first].id,a[ans[i].second].id);
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i].v),a[i].id=i;
    sort(a+1,a+1+n);
    for(int i=1;i<=n;i++) scanf("%d",&x[i]);
    int mid=n/2;
    int l=mid+1,r=n;
    for(int i=1;i<=mid;i++){
        if(x[a[i].id]!=a[l].id) p[i]=l,l++;
        else if(x[a[i].id]!=a[r].id) p[i]=r,r--;
    }
    if(l>r) print();
    else{
        int ok=0;
        for(int i=1;i<=mid-1;i++){
            if(x[a[i].id]!=a[l].id&&x[a[mid].id]!=a[p[i]].id){
                p[mid]=p[i];
                p[i]=l;
                ok=1;
                break;
            }
        }
        if(ok) print();
        else{
            int pos=0;
            for(int i=1;i<=mid-1;i++){
                if(x[a[i].id]!=a[mid].id&&x[a[l].id]!=a[p[i]].id&&x[a[p[i]].id]!=a[l].id){
                    if(!pos||a[p[i]].v<a[p[pos]].v){
                        pos=i;
                        if(a[p[i]].v<a[l].v) p[p[i]]=l;
                        else p[l]=p[i];
                        p[i]=mid;
                    }
                }
            }
            if(pos) print();
            else puts("-1");
        }
    }

    return 0;
}

```

---

