# 『MdOI R5』Message

## 题目描述

小 A 有一个群。这个群正在玩一个小游戏：给出一个函数 $f$，从某一个时间点起，发送第 $x$ 条消息，而 $f(x)=1$ 的群友会受到一个小惩罚。当群内消息总数达到 $m$ 时游戏结束。

但小 A 是个话痨，这段时间他在这个群发了 $n$ 条消息，他发的第 $i$ 条消息在整个消息记录里是第 $a_i$ 条消息。

但是小 A 不想受到惩罚，而小 A 恰好是管理员，他可以撤回**任何时刻、任何群成员发的任何消息**，注意这会导致这条消息之后的消息排名改变。

但是撤回消息太多容易被当成暴政，因此他要尽可能减少撤回信息次数，不管是自己的还是别人的。

接下来你也猜到你要干什么了：假如其他群成员不操作，给出 $n$、函数 $f$ 和 $a_i$，求出他至少要撤回几条消息。

## 说明/提示

【样例解释】

下面给出一种可能的方式：
- 小 A 先撤回第 $1$ 条消息（群友发的），他的四条消息在消息记录里现在是第 $1,5,7,10$ 条。
- 然后撤回第 $5$ 条消息（他自己发的），剩下三条消息在消息记录里现在是第 $1,6,9$ 条。

此时三条消息满足 $f(1)=f(6)=f(9)=0$，符合题意。

可以证明无法仅撤回一条消息达成要求。

【数据范围】

|Subtask|$n\le$|$m\le$|特殊性质|分值|
|:-:|:-:|:-:|:-:|:-:|
|1|$17$|$17$||$15$|
|2|$17$|$100$||$15$|
|3|$10^3$|$10^4$||$20$|
|4||$10^5$|$n=m$|$8$|
|5|$10^5$|$10^6$|A|$12$|
|6|$10^5$|$10^6$||$30$|

- 特殊性质 A：小 A 没有连发两条消息。

对于全部数据，$1\le n\le 10^5$，$1\le a_i\le m\le 10^6$，$a_i$ 严格递增，$f(i)\in \{0,1\}$。

## 样例 #1

### 输入

```
4 11
01101010001
2 6 8 11
```

### 输出

```
2
```

# 题解

## 作者：yummy (赞：7)

## Subtasks 1 and 2

Subtask 1 直接枚举每条消息是否撤回，然后 $O(m)$ 判断一下，时间复杂度 $O(m2^m)$。

首先我们考虑一件事，撤回别人的消息好还是自己的消息好。

如果你撤回一条别人的消息 $A$，在 $A$ 之后第一条自己的消息是 $B$，那么：

- 如果撤回 $A$，那么消息 $B$ 排名减 $1$，还**可能**导致惩罚；同时 $B$ 之后的消息排名减 $1$。
- 如果撤回 $B$，那么它不可能造成惩罚，之后的消息排名仍然减 $1$。

因此，撤回别人的消息总是不优于撤回自己的。

枚举每条自己的消息是否撤回，然后判断一下，时间复杂度 $O(n2^n+m)$。

## Subtask 3

我们发现，是否撤回后面的消息，不影响前面消息的排名。

因此，如果前面的消息都已经决定是否撤回，那么当前消息如果会导致惩罚就删掉，否则不删掉。

如果删掉一条消息，那么之后的消息排名要全部减 $1$，时间复杂度 $O(n^2+m)$。

## Subtask 4

每条消息都是小 A 发的。不管他删多少条消息，总是占据消息记录的前若干条。

因此，最多留几条消息，相当于 $f$ 有几个前缀 $0$。

## Subtasks 5 and 6

在 Subtask 3 基础上，不实时更新每条消息的排名，而是需要决策时，它之前撤回几条消息，排名就减去几。

时间复杂度 $O(n+m)$，常数极小。

参考代码（C++）：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[100005];
char f[1000005];
int main()
{
	int withdrawn=0; 
	scanf("%d%d%s",&n,&m,f+1);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		if(f[a[i]-withdrawn]=='1')
			withdrawn++;
	}
	printf("%d",withdrawn);
	return 0;
}
```

参考代码（Python 3）：

```python
input()
f="0"+input()
cnt=0
for i in map(int,input().split()):
	cnt+=f[i-cnt]=='1'
print(cnt)
```



---

## 作者：igAC (赞：5)

# $\text{Describe}$

[link](https://www.luogu.com.cn/problem/P8919)

简要题意：小 A 发了 $n$ 条信息，分别在 $a_i (i \in [1,n],a_i \in [1,m])$ 的位置上。

接下来告诉你每个位置是否会有惩罚，小 A 不想受到惩罚。

他可以撤回任何一位成员信息，包括自己。

每撤回一条信息，后面的信息都被视为提前了一条。

求最少要删多少条信息，小 A 才能不受惩罚。

# $\text{Solution}$

此题可以用贪心的思路思考。

先想一想，删掉别人的信息和删掉自己的信息的贡献。

显然删掉别人的信息没有删掉自己信息更优。

这里感性证明一下：

若我们删掉了别人的信息，后面的信息都会提前一条。

删掉自己的信息也会提前一条，显然在这方面贡献相同。

但如果我们删掉了别人信息，在他后面的小 A 的信息也可能受到惩罚。

可删掉自己的信息，被删掉的那条信息就一定不会受惩罚。

举个栗子：

```
2 6
010010
3 5
```

化成图就是：

![](https://cdn.luogu.com.cn/upload/image_hosting/97lh5dh8.png)

如图，若我们删除第一条成员信息，在第 $5$ 位的信息不会受到惩罚。

但第 $3$ 个位置的小 A 的信息会视为第 $2$ 条信息，就会受到惩罚。

因此，删掉成员信息一定不优于删掉自己的信息。

大家感性理解一下。

所以我们就有贪心策略：从前往后枚举每条小 A 发的信息，若某一条小 A 的消息会被惩罚，就将这条信息删掉。

# $\text{Code}$

```cpp
#include<cstdio>
#include<iostream>
#define N 1000005
using namespace std;
bool vis[N];
int n,m;
int a[N];
int cnt=0;//对后面造成的影响，即需要提前多少位
int main(){
    scanf("%d%d",&m,&n);//个人习惯
    for(int i=1;i<=n;++i){
        char c;
        cin>>c;
        vis[i]=(c=='1');
    }
    for(int i=1;i<=m;++i) scanf("%d",&a[i]);
    for(int i=1;i<=m;++i){
        int p=a[i]-cnt;//实际位置是原来位置-提前位数
        if(vis[p]) ++cnt;
    }
    printf("%d",cnt);
    return 0;
}
```

---

## 作者：Nygglatho (赞：2)

先放一个结论：如果自己的消息中 $f(i) = 1$ 则直接撤回，否则不管。

首先，由于消息撤回之后 **不会** 对前面的消息有影响，只会对后面的有影响。

但是，撤回该消息和撤回前面任何一条消息，对后面消息的影响都是一样的，可以画下图来分析。

（黄色部分是小 A 发的消息）

![](https://cdn.luogu.com.cn/upload/image_hosting/2mnbavk8.png)

显然，小 A 撤回群里第 $1 \sim 3$ 条中的任何一条和撤回第 $4$ 条对于第 $10$ 条来说效果都是一样的，但是由于撤回第 $1 \sim 3$ 条中的任何一条会导致第 $4$ 条变成第 $3$ 条，依然要受到惩罚，所以撤回第 $4$ 条最为划算。

![](https://cdn.luogu.com.cn/upload/image_hosting/zw305ipw.png)

小 A 无论是撤回 $1 \sim 3$ 条中任何一条还是第 $4$ 条，都会导致原来第 $10$ 条变成第 $9$ 条并使小 A 受到惩罚，而不撤回第 $4$ 条会使小 A 受到惩罚，所以需要至少撤回 $2$ 条。

而小 A 假如撤回别人发的消息（在自己发的前面），显然不会优于撤回自己发的，**并且甚至会比撤回自己发的消息的结果更差**，因为对自己发的消息后面的消息影响是一样的，更差是因为会出现连续的 $1$ 这种情况，如下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/6ihs8hrr.png)

如果撤回第 $10$ 条消息，小 A 就不会受到惩罚，但是如果撤回前面的消息，第 $10$ 条会变成第 $9$ 条，依然会受到惩罚，所以小 A 仍然需要撤回，那么这样子就已经需要撤回 $2$ 条消息了，显然还是撤回第 $10$ 条更优。

这样子的时间复杂度大概是 $O(n^2)$。

我们发现，撤回一条消息，对之后的消息都会有一个相同的影响，如图。

![](https://cdn.luogu.com.cn/upload/image_hosting/0wtl25vl.png)

（注：这里的增加是包括之前增加的）

我们考虑维护一个变量 $delt$，当需要撤回消息的时候，$delt \gets delt + 1$，之后判断的时候因为撤回了 $delt$ 次，所以所有的排名都需要降低 $delt$。

```cpp
#include "bits/stdc++.h"
using namespace std;

int x[1919810];
int delt = 1;//由于 string 从 0 开始，所以这里 delt 初值是 1。
int cnt;

string st;
int main() {
    int n, m;
    scanf ("%d%d", &n, &m);
    cin >> st;
    for (int i = 1; i <= n; ++i) scanf ("%d", &x[i]);
    for (int i = 1; i <= n; ++i) {
        if (st[x[i] - delt] == '1') {
            ++delt;
            ++cnt;
        }
    }
    printf ("%d", cnt);
}
```

---

## 作者：McIron233 (赞：2)

明确两个简单易证的结论之后，本题就变简单了：

- 撤回后面的消息**不影响**前面消息的排名；
- 每条消息**上升的排名**等于前面消息撤回的数量。

于是我们想到，如果撤回了后面的消息，那么前面的消息的排名不变，也就是其是否惩罚是不变的，所以可以从前往后，遇到会遭受惩罚的消息撤回即可，并且将撤回数量 $d$ 加上 $1$；对于此条消息是否遭受惩罚，只需要判断 $f(a-d)$ 是否为 $1$ 即可，其中 $a$ 是这条消息的初始排名。

答案即为 $d$。

---

## 作者：strcmp (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P8919)

对于题意，题目已经说的很清楚了，不知道题意的建议回去看题。

**Subtask1：** 直接暴力二进制枚举删除位置，然后 $\Theta(m)$ 判断即可，时间复杂度 $\Theta(m2^m)$，可以获得 $15$ 分的好分数。

**Subtask2：** 这里就需要做一点 dirty work 了，**对于每次删除位置，都选择在 $a$ 中的位置删除，其最优解与全局最优解相比严格不劣。**

证明如下：对于每一个位置，删除之后，不影响前面位置的值，只会影响之后位置的值。所以删除开区间 $(a_{i - 1}, a_i)$ 中的任意信息与删除 $a_i$ 没有本质区别，而直接删除 $a_i$ 则可以少一个需要维护的信息，严格不劣。

所以可以直接在 $a$ 中二进制枚举，时间复杂度 $\Theta(m2^n)$，可以获得 $30$ 分的好成绩。

**Subtask4：** $n = m$ 代表必须要删除所有信息，因此直接输出 $n$ 即可，结合前面可以获得 $38$ 分的好成绩。

**Subtask5：** 暂时没看出来，有 dalao 看出来这里部分分了可以私信一下（（（

**Subtask3：** 我们发现直接二进制枚举太浪费了，考虑将其优化一下。对于 $n$ 个位置，显然根据之前的引理，我们最先删除肯定是**第一个 $f_{a_i} = 1$ 的位置**，因为删去之前没有发生冲突的 $a_i$ 用处不大，对后面的影响与删去这个位置没有本质区别，而且严格不优。删去之后位置的 $a_i$ 则无法消除这个位置的冲突，所以必然删除第一个 $f_{a_i} = 1$ 的位置。

而删了第一个，就会有第二个，第三个，以此类推。遍历所有 $a_i$，如果存在 $f_{a_i} = 1$，则删除这个位置的 $a_i$，将之后的序号暴力减 $1$。时间复杂度 $\Theta(n^2 + m)$，结合前面可以获得 $58$ 分的好成绩。

**Subtask6：** 有了 Subtask3 的基础，直接将之后位置暴力减 $1$ 的部分使用树状数组差分优化即可，时间复杂度 $\Theta(n \log_2 n + m)$，可以通过本题。

其实这题维护一个减法标记是可以做到 $\Theta(n + m)$ 的，但是某 OIer 太懒，直接打了个树状数组就没管了。。。

参考代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define re register
const int maxn = 1e5 + 10;
int n, m, a[maxn], c[maxn]; 
int f[1000010]; char ch[1000010];
inline void add(int x, int d) {
    while (x <= n)c[x] += d, x += x & (-x);
}
inline int get(int x) {
    int sum = 0;
    while (x)sum += c[x], x -= x & (-x);
    return sum;
}
inline void read(int &x){
	x=0; char e=0;
	while (!isdigit(e))e=getchar();  
	while (isdigit(e)) x=x*10+(e^48),e=getchar();  
}
int main() {
    read(n); read(m); char c; int ans = 0; 
    for (re int i = 1; i <= m; i++){ while(ch[i] != '0' && ch[i] != '1')ch[i] = getchar(); }
    for (re int i = 1; i <= m; i++)f[i] = ch[i] - '0';
    for (re int i = 1; i <= n; i++)read(a[i]); int k = 1;
    for (re int i = 1; i <= n; i++)add(i, a[i] - a[i - 1]);
    while (k <= n) {
        if (!f[get(k)])++k;
        else {
            ++ans, ++k;
            add(k, -1);
        }
    }
    printf("%d\n", ans);
    return 0;
}
```

---

## 作者：Infinite_Eternity (赞：0)

# Description

[P8919 『MdOI R5』Message](https://www.luogu.com.cn/problem/P8919)

给定一个函数 $f$，若 $f(x)=1$，则会受到惩罚。同时，给出 $n$ 和 $n$ 个 $a_i$，求出至少要删除几个 $a_i$，使得所有 $a_i$ 满足 $f(a_i)=0$。

数据范围：$1\le n\le 10^5$，$1\le a_i\le m\le 10^6$，$a_i$ 严格递增，$f(i)\in \{0,1\}$。

# Analysis

模拟题。从第 $1$ 个 $a_i$ 遍历到第 $n$ 个 $a_i$，若每次在首处的 $a_i$ 满足 $f(a_i)=1$，就将其删除，并使得余下所有的 $a_i \leftarrow a_i-1$。此时便可得到我们的第一份代码【时间复杂度 $\mathcal{O}(n^2+m)$】：

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n,m,ans=0;
    string s;
    scanf("%d%d",&n,&m);
    cin >> s;
    int num[m],text[m];
    for (register int i=0; i<m; ++i)
        num[i]=s[i]-48;
    for (register int i=0; i<n; ++i)
        scanf("%d",&text[i]);
    for (register int i=0; i<n; ++i)
    {
        if (num[text[i]-1]==1)
        {
            for (register int j=1; j<n; ++j)
            {
                text[j]--;
            }
            ans++;
        }
    }
    printf("%d",ans);
    return 0;
}
```

交完之后可以发现，能拿到 $50$ 分，但剩下的点都 TLE 了。于是考虑优化。

- 读入优化。（不重要）

加入快读，并且将 01 串 $f$ 一个个读入并进行处理。即：

```cpp
for (register int i=0; i<m; ++i)
{
    in[i]=getchar();
    num[i]=in[i]-48;
}
```

- 思路优化。（重要）

很明显地，我们可以发现 TLE 的原因在于：每次在删除首个 $a_i$ 时，都需要利用 `for` 循环使得剩下的 $a_i \leftarrow a_i-1$。

考虑使用一个计数器，每删除一个 $a_i$，都将计数器加 $1$，之后进行判断的时候只需将 $a_i$ 减去计数器即可。

```cpp
for (register int i=0; i<n; ++i)
{
    if (num[text[i]-cnt]==1)
    {
        cnt++,ans++;
    }
}
```

最终，时间复杂度 $\mathcal{O}(n+m)$，轻松通过。

# Code

> 各位不必在评论区告诉我还需如何优化，~~因为这不是我的最快版本（偷笑~~

```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read()
{
    register char c = getchar();
    register int x = 0, f = 1;
    while (c < '0' || c > '9') {if (c == '-') f = -1;c = getchar();}
    while (c >= '0' && c <= '9') {x = (x << 3) + (x << 1) + c - 48;c = getchar();}
    return x * f;
}
int main()
{
    int n,m,ans=0,cnt=1;
    n=read(),m=read();
    int num[m],text[m];
    char in[m];
    for (register int i=0; i<m; ++i)
    {
        in[i]=getchar();
        num[i]=in[i]-48;
    }
    for (register int i=0; i<n; ++i)
        text[i]=read();
    for (register int i=0; i<n; ++i)
    {
        if (num[text[i]-cnt]==1)
        {
            cnt++,ans++;
        }
    }
    printf("%d",ans);
    return 0;
}
```

---

## 作者：continueOI (赞：0)

这道题很简单，本人觉得是这次月赛中最简单的题了。

首先看题目，当自己会受到惩罚时，小 A 很明显可以有两种操作，一种是撤回别人发出的，一种是撤回自己的。

容易发现，这两种操作都会使得撤回消息之后的小 A 发出的消息排名减少 1，而对撤回消息之前的消息没有影响，所以可以从小 A 发出的消息的第一条一次往后扫，如果自己发出的消息会被惩罚，判断是撤回这条消息之前别人发布的消息还是撤回自己发出的消息（不需要考虑之后的消息，因为不论你选择是撤回自己的消息还是撤回在自己消息之前的别人的消息，在这之后的消息排名都只会减少 1）。

其实撤回别人消息与撤回自己消息是本质上是一样的，对于后面的消息没有区别，都只是减去 1。

根据以上结论，即可写出一份模拟代码：

```cpp
for(int i=1;i<=n;i++){
	if(f[a[i]-1]=='1'){
		ans++;
		for(int j=i;j<=n;j++) a[j]--;
	}
}
```

但是很明显，这段代码时间复杂度是 $O(n^2)$,无法通过本题。

观察代码，只能在撤销消息后之后的消息排名都只会减少 1 这一模拟步骤进行优化。容易想到，变量` ans`，就代表已经撤销了多少条消息，从而将时间复杂度优化为 $O(n)$，通过此题。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,ans,a[100005];
string f;
int main(){
	cin>>n>>m>>f;
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)
		if(f[a[i]-1-ans]=='1')
			ans++;
	cout<<ans;
	return 0;
}
```


---

## 作者：MoyunAllgorithm (赞：0)

## 题意：

某群做一个小游戏：给出 `bool` 类型的函数 $f$（你会得到所有函数值），之后群里开始发消息。对于第 $i$ 条消息，如果 $f(i)=1$，发消息的人要受到惩罚。

共 $M(1 \le M \le 10^6)$ 条消息，其中管理员发了 $N(1 \le N \le 10^5)$ 条。管理员不想让自己受到惩罚，所以 ta 要在所有 $M$ 条消息中撤回尽可能少的消息（这会改变部分消息的排名），让他免于惩罚。

## SOLUTION 1（我的赛时做法）

由于最近在复习 dp，所以想到了 dp。

我设 `bool` 类型的 $dp_{i,j}$ 表示在群里所有消息中前 $i$ 个消息中，能否保留 $j$ 条的同时让管理员不受惩罚。（你问我是怎么想到的？就是多做练习+~~玄学尝试~~）

这样设置有什么好处呢？好处就是由于前面消息的撤回会导致后面消息的排名变化，但如果我这么设置状态的话，那么我就可以轻而易举的发现：对于状态 $dp_{i,j}$，原先的第 $i+1$ 条消息的**新位置**是 $j+1$。

这样可以想到转移方程（$b_i$ 表示一开始在位置 $i$ 的消息是否是管理员发的）：

- 当 $b_{i+1}=f(j+1)=1$，那下一条消息是管理员发的，且函数值为 $1$，那么必须撤回。也就是 $dp_{i+1,j}=1$。

- 其他情况时，不需要撤回，$dp_{i+1,j+1}=1$。

可以写出以下代码：

```cpp
for(int i=1;i<=M;i++)
	{
		for(int j=0;j<=i;j++)
		{
			if(dp[i][j])
			{
				int nxt=j+1;
				if(my[i+1]==1&&f[nxt]) dp[i+1][j]=1;
				else dp[i+1][j+1]=1;
			}
		}
	}
```

可惜的是，这段代码的时间复杂度是 $O(M^2)$，只可以得到 $50$ 分。

**不能优化了吗？？？**

观察式子，发现：**第 $i$ 层的每个状态和第 $i+1$ 层的每个状态一一对应。** 也就是说，不管 $i$ 为多少，当前有效的状态数不变。因为当 $i=1$ 时，只有最多 $2$ 个有效状态 ($dp_{1,0},dp_{1,1}$)，所以以后的每一个 $i$，枚举的 $j$ 只有最多 $2$ 个是有用的。因此，想到用队列存储目前的有效状态，在下一轮 dp 时直接调用，而不是对 $j$ 进行枚举。

时间复杂度降为 $O(M)$。滚动数组可以实现 $O(M)$ 的空间复杂度。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=1e6+5;
int N,M;
bool f[MAXN];
bool dp[MAXN];
int a[MAXN];
bool my[MAXN];
int main()
{
	scanf("%d %d",&N,&M);
	for(int i=1;i<=M;i++) scanf("%1d",&f[i]);
	for(int i=1;i<=N;i++) 
	{
		scanf("%d",&a[i]);
		my[a[i]]=1;
	}
	dp[0]=dp[1]=1;
	if(f[1]&&a[1]==1) dp[1]=0;
	queue<pair<int,int> >q;
	q.push({1,0});
	if(dp[1]) q.push({1,1});//先把i=1时的有用状态加入队列
	for(int i=1;i<M;i++)
	{
		while(q.size())//遍历当前所有有用状态。上文已经证明不多于2个
		{
			int pos=q.front().first,j=q.front().second;
			if(pos!=i) break;//如果这个状态属于下一层，停止
			q.pop();
			int nxt=j+1;
			if(my[i+1]==1&&f[nxt]) 
			{
				dp[j]=1;
				q.push({i+1,j});//加入下一层的有用状态
			}
			else 
			{
				dp[j+1]=1;
				q.push({i+1,j+1});
			}
		}
	}
	for(int i=M;i>=0;i--) 
	{
		if(dp[i])
		{
			printf("%d\n",M-i);
			return 0;
		}
	}
	return 0;
}
```

一些话：由于我身边似乎只有我想到此方法，因此我不敢完全保证思路的正确性。当然，该程序通过了所有测试点。如果存在针对该方法的 hack 数据，那么该方法是错误的（目前似乎还没有）。



---

