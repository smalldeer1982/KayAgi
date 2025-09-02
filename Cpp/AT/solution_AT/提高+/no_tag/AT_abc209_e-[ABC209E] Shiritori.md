# [ABC209E] Shiritori

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc209/tasks/abc209_e

高橋辞書には $ N $ 個の単語が載っており、$ i\,\ (1\ \leq\ i\ \leq\ N) $ 番目の単語は $ s_i $ です。

高橋君と青木君は高橋辞書を使って $ 3 $ しりとりをします。 $ 3 $ しりとりのルールは以下です。

- 高橋君と青木君は、高橋君から始めて交互に単語を言い合っていく。
- 各プレーヤーは前の人が言った単語の最後の $ 3 $ 文字で始まる単語を言わなければならない。例えば、前の人が `Takahashi` と言った場合、次の人は `ship`、`shield` などを言うことができ、`Aoki`、`sing`、`his` などを言うことはできない。
- 大文字と小文字は区別される。例えば、`Takahashi` のあとに `ShIp` を言うことはできない。
- 言う単語がなくなった方が負ける。
- 高橋辞書に載っていない単語を言うことはできない。
- 同じ単語は何度でも使ってよい。

各 $ i\,\ (1\ \leq\ i\ \leq\ N) $ について、高橋君が $ 3 $ しりとりを単語 $ s_i $ から始めたときどちらが勝つかを判定してください。ただし、二人とも最善に行動するとします。具体的には、自分が負けないことを最優先し、その次に相手を負かすことを優先します。

## 说明/提示

### 制約

- $ N $ は $ 1 $ 以上 $ 2\ \times\ 10^5 $ 以下の整数
- $ s_i $ は英小文字と英大文字のみからなる長さ $ 3 $ 以上 $ 8 $ 以下の文字列

### Sample Explanation 1

高橋君が `abcd` から始めたとき、次に青木君が `bcda` と言って高橋君は言う単語がなくなります。よって青木君が勝つので `Aoki` と出力してください。 高橋君が `bcda` から始めたとき、次に青木君は言う単語がなくなります。よって高橋君が勝つので `Takahashi` と出力してください。 高橋君が `ada` から始めたとき、二人とも `ada` を繰り返すのでしりとりが終わることはありません。よって `Draw` と出力してください。同じ単語を何度でも使用できることに注意してください。

## 样例 #1

### 输入

```
3
abcd
bcda
ada```

### 输出

```
Aoki
Takahashi
Draw```

## 样例 #2

### 输入

```
1
ABC```

### 输出

```
Draw```

## 样例 #3

### 输入

```
5
eaaaabaa
eaaaacaa
daaaaaaa
eaaaadaa
daaaafaa```

### 输出

```
Takahashi
Takahashi
Takahashi
Aoki
Takahashi```

# 题解

## 作者：zhaomumu1218 (赞：17)

提供一个很抽象的思路。

## 题意

两个人玩接龙游戏，后一个人说的单词的前 $3$ 个字符必须和前一个人说的单词的后 $3$ 个字符一样。如果先手先说第 $i$ 个单词，问谁会赢。

## 思路

**注**：下文中先手指目前选择的人。

### 第一版（非正解）

从第 $i$ 个单词的前 $3$ 个字母向后 $3$ 个字母连边，出度为零的点为先手必败。

1. 如果当前的点走一步能到下一步的先手必败点，说明这个点是先手必胜点。
2. 如果当前的点访问第 $2$ 次，说明这个点是平局点。
3. 如果当前的点无法走一步达到下一步的先手必败点，且能走一步到平局点，说明这个点是平局点。
4. 如果当前的点无法走一步达到下一步的先手必败点，且能无法走一步到平局点，说明这个点是当前先手必败点。     
这就结束了？

### hack

不！错误数据：

```
5
fffccc
aaabbb
bbbccc
cccaaa
aaaeee
```

图是这样的   
![](https://cdn.luogu.com.cn/upload/image_hosting/6zwr196u.png)    
aaa 这个点是先手必败点，但我的思路会因为输入顺序先去点 bbb，然后到点 ccc。由于点 ccc 访问过，点 bbb 变成了平局点，但很明显祂不是平局点。

### 第二版（正解）

仔细分析，发现错误的原因是 dfs 顺序不对，应该先访问未访问的点，一个点被访问第 $2$ 次才是平局点，其他同第一版。

### 代码

```
#include<bits/stdc++.h>
using namespace std;
#define LOCAL
namespace lsy{
    namespace IO{
        #ifndef LOCAL
            constexpr auto maxn=1<<20;
            char in[maxn],out[maxn],*p1=in,*p2=in,*p3=out;
            #define getchar() (p1==p2&&(p2=(p1=in)+fread(in,1,maxn,stdin),p1==p2)?EOF:*p1++)
            #define flush() (fwrite(out,1,p3-out,stdout))
            #define putchar(x) (p3==out+maxn&&(flush(),p3=out),*p3++=(x))
            class Flush{public:~Flush(){flush();}}_;
        #endif
        namespace usr{
            template<typename type>
            inline type read(type &x){
                x=0;bool flag(0);char ch=getchar();
                while(!isdigit(ch)) flag^=ch=='-',ch=getchar();
                while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
                return flag?x=-x:x;
            }
            template<typename type>
            inline void write(type x){
                x<0?x=-x,putchar('-'):0;
                static short Stack[50],top(0);
                do Stack[++top]=x%10,x/=10;while(x);
                while(top) putchar(Stack[top--]|48);
            }
            inline char read(char &x){do x=getchar();while(isspace(x));return x;}
            inline char write(const char &x){return putchar(x);}
            inline void read(char *x){static char ch;read(ch);do *(x++)=ch;while(!isspace(ch=getchar())&&~ch);}
            template<typename type>inline void write(type *x){while(*x)putchar(*(x++));}
            inline void read(string &x){static char ch;read(ch),x.clear();do x+=ch;while(!isspace(ch=getchar())&&~ch);}
            inline void write(const string &x){for(int i=0,len=x.length();i<len;++i)putchar(x[i]);}
            template<typename type,typename...T>inline void read(type &x,T&...y){read(x),read(y...);}
            template<typename type,typename...T>
            inline void write(const type &x,const T&...y){write(x),putchar(' '),write(y...),sizeof...(y)^1?0:putchar('\n');}
            template<typename type>
            inline void put(const type &x,bool flag=1){write(x),flag?putchar('\n'):putchar(' ');}
        }
        #ifndef LOCAL
            #undef getchar
            #undef flush
            #undef putchar
        #endif
    }using namespace IO::usr;
}using namespace lsy::IO::usr;
const int maxn=200010,maxd=200000;
string s[maxn];
int ans[maxd];
int flag[maxd];
int jh(char z){
    if(z>='a') return z-'a'+27;
    return z-'A';
}
int js(string ss){
    return jh(ss[0])*53*53+jh(ss[1])*53+jh(ss[2]);
}
vector<int>e[maxd];
map<pair<int,int>,bool>mp;
int dfs(int u){ //1先手必胜2后手必胜3平局 现在是先手选
    if(e[u].size()==0) return 2;
    if(ans[u]) return ans[u];
    if(flag[u]==2) return ans[u]=3;
    flag[u]++;
    int re=2;
    for(int v:e[u]){
        if(flag[v]) continue;
        int z=dfs(v);
        if(z==3) re=3;
        if(z==2) return ans[u]=1;
    }
    for(int v:e[u]){
        if(!flag[v]) continue;
        int z=dfs(v);
        if(z==3) re=3;
        if(z==2) return ans[u]=1;
    }
    ans[u]=re;
    return re;
}
signed main(){
    int n;
    read(n);
    for(int i=1;i<=n;i++){
        read(s[i]);
        string x="";
        x+=s[i][0];
        x+=s[i][1];
        x+=s[i][2];
        string xx="";
        xx+=s[i][s[i].size()-3];
        xx+=s[i][s[i].size()-2];
        xx+=s[i][s[i].size()-1];
        int sx=js(x),sxx=js(xx);
        if(mp[{sx,sxx}]) continue;
        mp[{sx,sxx}]=1;
        e[sx].push_back(sxx);
    }
    for(int i=1;i<=n;i++){
        string xx="";
        xx+=s[i][s[i].size()-3];
        xx+=s[i][s[i].size()-2];
        xx+=s[i][s[i].size()-1];
        int z=js(xx);
        int ans=dfs(z);
        if(ans==2) write("Takahashi\n");
        if(ans==1) write("Aoki\n");
        if(ans==3) write("Draw\n");
    }
    return 0;
}
/*
5
fffccc
aaabbb
bbbccc
cccaaa
aaaeee
*/
```

---

## 作者：xiaoPanda (赞：8)

## ABC209E - Shiritori(*2153)
### Problem
A 和 B 在玩单词接龙，A 先说一个单词，B 后说，然后再是 A 说，并且后一个人说的单词的前 $3$ 个字母必须是前一个人说的后 $3$ 个字母，只能说给出的单词之一，不能说的人失败，每个人使用最优策略，问如果 A 最开始说给出的第 $i$ 个单词，谁赢？

### Solution
考虑到如果一个单词后面无法续上其他单词，那么这个单词就是必败态，如果某个状态之后有必败态，那这个状态为必胜态，如果一个状态之后都是必胜态，那么这个状态是必败态（注意到这里说的状态都是相当于当前操作的人而言）。

因此，可以将所有可以连在一起的单词建图，再从必败的单词用 BFS 反推回去（类似拓扑排序），就可以找到答案。

暴力枚举任意两个单词是否可以连接是 $O(n^2)$ 的，注意到每个单词实际上只与前后 $3$ 个字符有关，所有可以将这前后 $3$ 个字符转化成数字（就像 Hash 一样）后直接连边，时间复杂度为 $O(n)$。

注意平局的情况实际上是个环，但我们可以在 BFS 时不加入平局情况，并且打上标记，如果是 $1$ 代表 A 赢，是 $-1$ 代表 B 赢，是 $0$ 代表平局（即没更新）。
### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+7;
const int M=2e5+7;
const int K=256;
char s[M][20];
int f[N];
queue<int>q;
vector<int>edge[N];
int g[N],idx;
map<int,int>mp;
main() 
{
	int n;
    scanf("%lld",&n);
    for(int i=1;i<=n;i++) 
	{
        scanf("%s",s[i]+1);int m=strlen(s[i]+1);
        int u=(s[i][1]-'A')*K*K+(s[i][2]-'A')*K+(s[i][3]-'A');
		int v=(s[i][m-2]-'A')*K*K+(s[i][m-1]-'A')*K+(s[i][m]-'A');
	    if(!mp[u])mp[u]=++idx;
        if(!mp[v])mp[v]=++idx;
        edge[mp[v]].push_back(mp[u]);g[mp[u]]++;
    }
    for(int i=1;i<=idx;i++)
        if(!g[i])f[i]=1,q.push(i);
    while(!q.empty()) 
	{
        int u=q.front();
        q.pop();
        for (int i=0;i<edge[u].size();i++) 
		{
            int v=edge[u][i];g[v]--;
            if (f[u]==1&&f[v]==0)f[v]=-1,q.push(v);
            if (f[v]==0&&!g[v]&&f[u]==-1)f[v]=1,q.push(v);  
        }
    }
    for (int i=1;i<=n;i++) 
	{
        int m=strlen(s[i]+1);
        int v=(s[i][m-2]-'A')*K*K+(s[i][m-1]-'A')*K+(s[i][m]-'A');
       // cout<<mp[v]<<endl;
        if(f[mp[v]]==1)puts("Takahashi");
        if(f[mp[v]]==-1)puts("Aoki");
        if(f[mp[v]]==0)puts("Draw");
    }
    return 0;
}
```

---

## 作者：Sorato_ (赞：6)

# ABC209E Shiritori 题解
## 分析

博弈，可重复选，一眼图论，将每个单词的前三个字符向后三个字符连边，并用后三个字符代表这个单词。

看一下样例。

```
5
eaaaabaa
1    2
eaaaacaa
1    3
daaaaaaa
4    5
eaaaadaa
1    4
daaaafaa
4    6
```

我们得到的有向图：

![](https://cdn.luogu.com.cn/upload/image_hosting/qawv1e8x.png)

当一方说完一个单词，这个单词的后三个字符无法接上任何单词的前三个字符则为必胜态。

**即这个点没有出边，则这个点是必胜态。**

注意，**本题博弈的状态转移有些不同**，具体为：

**当一个点连向的点中有一个必胜态，则这个点是必败态**。

**当一个点连向的点都是必败态，则这个点是必胜态**。

> 常见的状态转移：
>
> 当一个点连向的点中有一个必败态，则这个点是必胜态
>
> 当一个点连向的点都是必胜态，则这个点是必败态

分析一下，一方走到这个点之后，下一手是对方，也就是说对方决定了下一次要走哪条边。

那么对方肯定是想让当前点成为必败态，想要尽可能走到必胜态。所以就有了本题稍为不同的状态转移。

另两篇没有注意到这一点，文字叙述中说的是常见的状态转移或是笼统模糊地说了说，但代码实现却是对的，卡了我很长时间（

具体可以以 $\large1$ 号点为例（虽然 $\large1$ 号点在样例中并无实际意义，我们假定它也代表了一个单词）：

首先 $\large4$ 号点一定是必败态，因为 $\large 5$ 和 $\large 6$ 都是必胜态。

那么当一方说完 $\large 1$ 号点代表的单词后，该对方接了，对方肯定会接 $\large 2$ 或 $\large 3$ 而不接 $\large 4$。因为只有走到这两点，才能使当前点败，他胜。

## 套路

我们观察到，所有有出边的点的状态都是由它连向的点（后继）转移而来的，所以我们使用有向图上博弈的常见套路——**反向建边**。然后跑拓扑同时状态转移就可以了。

![](https://cdn.luogu.com.cn/upload/image_hosting/8qzwkuf1.png)

到此，$\operatorname{DAG}$ 上的本题就已经讨论完了，但是我们还没有判平局，即有环的情况。

## 平局（环）

有环是不一定平局的，分析一下。

（正向图中）在一个环里，一方说完了一个单词，如果对方可以走到必胜态，肯定会走处环使得自己胜而不是平局。但是如果这个环没有向外连边或连向的都是必败态，那么就是平局。

那么在反向图中，我们在遍历一个必胜的点的出边时，不必在后继的入度为零时才让它入队，直接把它的状态转移为必败并入队。若是遍历一个必败的点的出边，正常拓扑即可。

## code

```c++
#include<bits/stdc++.h>
#define int long long
#define reg register
#define mp(a,b) make_pair((a),(b))
using namespace std;
inline int read()
{
	short f=1;
	char c=getchar();
	int x=0;
	while(c<'0'||c>'9')	{if(c=='-')	f=-1;c=getchar();}
	while(c>='0'&&c<='9')	x=(x<<1)+(x<<3)+(int)(c^48),c=getchar();
	return x*f;
}
int n,tot,ind[200010],win[200010]/*0平/未查找 1败 2胜*/;
string l,r[200010],s,ans[3]={"Draw","Aoki","Takahashi"};//不想写if了qwq
unordered_map<string,int>c;
vector<int>e[200010];
queue<int>q;
signed main()
{
	n=read();
	for(reg int i=1;i<=n;i=-~i)
	{
		cin>>s;l="";
		for(reg int j=0;j<3;j=-~j)	l+=s[j];
		for(reg int j=s.size()-3;j<(int)s.size();j=-~j)	r[i]+=s[j];
		if(!c[l])	c[l]=++tot;//没必要哈希，用map编号即可
		if(!c[r[i]])	c[r[i]]=++tot;
		e[c[r[i]]].push_back(c[l])/*反向建边*/;ind[c[l]]=-~ind[c[l]];
	}
	for(reg int i=1;i<=tot;i=-~i)	if(!ind[i])	q.push(i),win[i]=2;
	while(!q.empty())
	{
		int u=q.front();q.pop();
		for(reg auto i:e[u])
		{
			if(!win[i]&&win[u]==2)	q.push(i),win[i]=1;
			if(!win[i]&&win[u]==1&&!--ind[i])	q.push(i),win[i]=2;
		}
	}
	for(reg int i=1;i<=n;i=-~i)	cout<<ans[win[c[r[i]]]]<<endl;
	return 0;
}
```

---

## 作者：LionBlaze (赞：0)

首先一眼图上博弈。

但是考虑什么是点。显然我们可以考虑单词是点……吗？

那么如果单词是点，显然单词的连接方法就是边。那么一共会有 $\mathcal O(N^2)$ 条边（比如数据 `aaa aaa aaa ...`），显然爆炸。

那么……考虑把点和边转换。“连接方式”视为点，单词视为边。

那么“连接方式”究竟指的是什么？注意到题面中所说“一个单词的后三个字母与另一个单词的前三个字母相同”，那么可以把三个字母视为点。总共有 $52^3=140608$ 个点，$N$ 条边，可以接受。

那么考虑博弈。

我们注意到，没有出度的点是必败点（因为先手的前一个人，也就是后手，走到了这个点，而~~主播~~先手走不下去了，于是必败）。

然后显然，所有后继都为必胜点的点才是必败点（因为怎么走都是后手必胜，自己必败），但凡后继有一个点是必败点的点就是必胜点（因为可以直接走到那个必败点让后手必败，自己必胜）。

如果你直接开始写代码（用拓扑排序），可能会遇到一些问题。如果你忽略这些问题也可以写下去，并且如果你的代码风格比较奇特（因为这里有一些问题，所以代码风格却变得有点重要）……[它居然 AC 了](https://atcoder.jp/contests/ABC209/submissions/65141645)？？！

> 好吧这是我特别写的 AC 代码，但是一眼看过去好像并没有对我们的问题进行特殊处理。

显然问题就是，如果有环怎么办？显然这个时候难以直接进行转移。

考虑环上的点。如果某个点已经可以决定出这个点的胜负（即，已经有后继已知是必败点了，自己无论如何都是必胜点），那么显然不管是不是在环上都已经可以决定了。那么这个环就相当于被破开了，因为它的前驱节点也有可能（如果在另一个环上则还有可能不能决定）能够决定，前驱的前驱也有可能……

如果找不到这样的节点呢？

实际上，你可能也能够猜到，此时是平局的。证？

显然，当我们无法确定任何一个节点的时候，把已经确定的节点去掉（显然对于我们无法确定的节点的胜负没有任何影响）之后的图的形态是，对于任何一个节点出度都不为 $0$（如果为 $0$，则这个节点是必败点）。

那么我们知道接龙就是走一条边，而因为每个节点都有后继结点，边又可以重复走（可以重复接龙），那么显然是可以一直走下去的。

所以最终我们算法的思路是，首先建反图（因为是从前驱转移而来），然后先预处理入度，再使用一个类似于拓扑排序的操作，每次转移（即考虑走一条边）时：

- 首先将终点的入度减少 $1$。
- 如果边的起点是必败点，则无论如何终点都是必胜点。此时为了方便区分，把终点的入度变为 $-1$（这里入度就不再是严格为入度了）然后放入拓扑排序的队列中。
- 否则，如果减少之后入度为 $0$（不能为负，因为一个节点不能多次入队，我被这个坑 WA 了一发）则转移之后入队。

最后，所有没有进过队列的点（容易发现进过队列和已经被确定是等价的）都是平局点。

根据上面的结论容易证明其正确性。

代码详见本文中唯一一个链接。

---

## 作者：wth2026 (赞：0)

# 题目思路
考虑到如果一个单词后面无法续上其他单词，那么这个单词就是必败态，如果某个状态之后有必败态，那这个状态为必胜态。

因此，可以将所有可以连在一起的单词建图，再从必败的单词用 BFS 反推回去（类似拓扑排序），就可以找到答案。

暴力枚举任意两个单词是否可以连接是 $O(n^2)$ 的，但是，我们可以将前三个字母与后三个字母用类似哈希的方式变成数字，就可以了。

注意平局的情况实际上是个环，但我们可以在 BFS 时不加入平局情况，并且打上标记。

[AC Code](https://atcoder.jp/contests/abc209/submissions/57248725)

---

## 作者：Zhao_daodao (赞：0)

## solution

有点神秘。

对于每一个单词，发现如果知道它能用什么连接，就非常好做了。

直接连接是 $O(n^2)$ 的，显然会超时。

题目中告诉我们，每一个单词可以无限用，而且单词也只需要知道前三个和后三个，不用知道具体是什么。

这启示我们：可以用一个 **映射**。对于三个字符 $a,b,c$，定义映射 $F(a,b,c)$ 为 $(a-'A')\times 256^2+(b-'A')\times 256+(c-'A')$。

定义一个 `map`：$G(x)$。其中每访问到一个新的 $x$，$G(x)$ 就是一个新的数。

对于每一个字符，取出前三个字符 $a,b,c$ 和后三个字符 $x,y,z$，$G(F(x,y,z))$ 向 $G(F(a,b,c))$ 连边。

图建出来之后就是普通博弈论。

用拓扑排序将每一个状态转移出来，如果没有被转移到的就是平局。


---

## 作者：Little_Cabbage (赞：0)

# 解题思路

考虑利用拓扑序逆推答案。

对于每一个单词，显然，只用考虑它的前 $3$ 个字母和后 $3$ 个字母。可以对每一种组合都编一个编号。

设当前字母组合为 $s$，那么编号为 $mp_s$。

建立一张图，从每个单词的后 $3$ 个字母组成的字符串向前 $3$ 个字母组成的字符串连一条边，并将节点 $mp_{front}$ 的入度增加 $1$。

然后根据拓扑序计算答案。

定义一个队列 $q$，如果当前节点的入度为 $0$，就把当前节点放到队列里面，并把状态设为必胜态。

对与每一个节点，如果它的前一个节点是必胜态，那么它就是必败态，反之亦然。

最后输出答案即可。

# 核心代码

建图：

```cpp
rep(i, 1, n) {
	cin >> s[i];
	string t = "", tt = "";
	t += s[i][0], t += s[i][1], t += s[i][2];
	if (!mp[t]) mp[t] = ++ cnt;
	tt += s[i][s[i].size() - 3], tt += s[i][s[i].size() - 2], tt += s[i][s[i].size() - 1];
	if (!mp[tt]) mp[tt] = ++ cnt;
	g[mp[tt]].push_back(mp[t]);
	d[mp[t]] ++ ;
}
```

计算答案：

```cpp
// 1 表示 Takahashi 必胜，-1 表示 Aoki 必胜，0 表示平局
queue<int> q;
rep(i, 1, cnt) if (!d[i]) {
	q.push(i);
	f[i] = 1;
}
while (!q.empty()) {
	int u = q.front();
	q.pop();
	rep(i, 0, g[u].size() - 1) {
		int ver = g[u][i];
		d[ver] -- ;
		if (f[ver] == 0 && f[u] == 1) {
			f[ver] = -1;
			q.push(ver);
		}
		if (f[ver] == 0 && f[u] == -1 && !d[ver]) {
			f[ver] = 1;
			q.push(ver);
		}
	}
}
```

---

## 作者：Chillturtle (赞：0)

# 题意

有两个人，这两人交替用输入数据中的词汇来接龙。要求上下接的两个词汇上一词的后三个字母与下一词的前三个字母严格相同。问：当指定先手说的词时，谁能够获胜。

# 思路

首先，明确：当一个词的后面无法接上任何单词，那么这个单词就一定输。如果一个词的后面有一定会输的词那么这个词就一定会赢。如果这个单词的后面都是一定会赢的，那么这个单词就一定会输。

这里我们将一定会赢的单词称为必胜单词，称一定会输的单词维必输单词。那么上面的分析可以简化为：一个单词之后都为必赢单词则该单词为必输单词，如果一个词后面有必输单词则这个词为必赢单词。

有了这个结论，我们可以从某个必输单词入手，利用类似拓扑序的方式找到从该单词到指定开始单词的路径上的必赢单词。

这里注意，两个单词是否连边至于它们前后三个字母有关。于是采用类似哈希的方法，进行简化。将连边的 $O(n^2)$ 化简为 $O(n)$ 具体详见代码。

# AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
const int M=1e6+10;
char s[M][20];
int n,tot;
int gt[N],fa[N];
queue<int> q;
vector<int> edge[N];
map<int,int> mp;
void topsort(){
    while(!q.empty()){
        int head=q.front();
        q.pop();
        for(int i=0;i<edge[head].size();i++){
            int v=edge[head][i];
            gt[v]--;
            if(fa[head]==1&&fa[v]==0){
                fa[v]--;
                q.push(v);
                // cout<<"***"<<endl;
            }
            if(fa[head]==-1&&fa[v]==0&&!gt[v]){
                fa[v]++;
                q.push(v);
            }
        }
    }
    return;
}
void init(){
    for(int i=1;i<=tot;i++){
        if(!gt[i]){
            fa[i]=1;
            q.push(i);
        }
    }
    return;
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>(s[i]+1);
        int m=strlen(s[i]+1);
        int u=(s[i][1]-'A')*(1<<16)+(s[i][2]-'A')*(1<<8)+(s[i][3]-'A');
		int v=(s[i][m-2]-'A')*(1<<16)+(s[i][m-1]-'A')*(1<<8)+(s[i][m]-'A');
        if(!mp[u]){
            tot++;
            mp[u]=tot;
        }
        if(!mp[v]){
            tot++;
            mp[v]=tot;
        }
        edge[mp[v]].push_back(mp[u]);
        gt[mp[u]]++;
    }
    init();
    topsort();
    // for(int i=1;i<=n;i++){
    //     cout<<fa[i]<<" ";
    // }
    // cout<<endl;
    for(int i=1;i<=n;i++){
        int m=strlen(s[i]+1);
        int v=(s[i][m-2]-'A')*(1<<16)+(s[i][m-1]-'A')*(1<<8)+(s[i][m]-'A');
        if(fa[mp[v]]==1){
            cout<<"Takahashi"<<endl;
        }else if(fa[mp[v]]==-1){
            cout<<"Aoki"<<endl;
        }else{
            cout<<"Draw"<<endl;
        }
    }
return 0;
}
```

---

## 作者：梦应归于何处 (赞：0)

### 题目大意

有两个人在玩游戏。

给出 $N$ 和 $N$ 个单词。第一个人先说单词，第二个人后说单词。每个人说单词有一个要求：

1. 说的这个单词的前三个字母要与上一个人说的后三个字母要相等。

2. 要区分大小写。

3. 如果没有词可以说了，那么这个人就输了。

4. 单词可以重复使用。

假设这两个人都足够聪明。请你输出第一个人分别说出第 $1,2,3,\dots,N$ 个单词时，谁能赢。

### 思路

一看就是图论，把每个单词的前三个和每个单词的后三个连边。

怎么判断平局？

平局肯定就是这个图中出现了环。

举个例子：

我们有 `aaa` 这样一个单词，我们发现这个单词的前三个和后三个一样，

先让第一个人说，第一个人只能说 `aaa`，第二个人也只能说 `aaa`，然后第一个人有只能说 `aaa` 我们发现了一件事：开始重复循环了，这时候不论怎么说都会无限循环，所以平局了。

如何判断输赢呢，我们可以用倒推。

具体情况请见代码，代码里面有注释帮助大家理解。

### 代码

~~~cpp
#include <bits/stdc++.h>
#define TNTMAX INT_MAX
#define db double
#define ll long long
#define ex exit(0);
#define endl "\n"
#define inl inline
#define null NULL
#define pb(a) push_back(a)
using namespace std;
ll getid(string s) {//得到这个字符串唯一的编码，最大不会超过52*52*52。
	ll ret = 0;
	for (int i = 0; i < 3; i++) {
		char ss = s[i];
		if (ss >= 'a' && ss <= 'z') {
			ss -= 'a';
		} else {
			ss = ss - 'A' + 26;
		}
		ret = ret * 52 + ss;
	}
	return ret;
}
string s[300000];
ll ru[300000];
vector<ll> rv[300000];// 邻接表存图，这里存的是反向边。
bool vis[300000];
ll ans[300000];//ans数组中只会有3个值：0，1，-1；0表示平局，1表示Takahashi赢，-1表示Aoki赢。
int main() {
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ll n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> s[i];
		ll u = getid(s[i].substr(0, 3));//得到唯一编号。
		ll v = getid(s[i].substr(s[i].size() - 3, 3));//得到唯一编号。
		ru[u]++;//入度加1。
		rv[v].pb(u);//反向存边。
	}
	queue<ll> q;
	for (int i = 0; i < 52 * 52 * 52; i++) {
		if (ru[i] == 0) {  //找到初始状态。
			q.push(i);
			vis[i] = 1;
			ans[i] = 1;
		}
	}
	while (!q.empty()) {// 用一个队列来搜索。
		ll u = q.front();
		q.pop();
		for (auto i : rv[u]) {
			if (!vis[i]) {//重复的点不用加进队列了。
				if (ans[u] == 1) {  //如果底下有必胜状态那么他输
					ans[i] = -1;
					q.push(i);
					vis[i] = 1;
				} else {
					ru[i]--;
					if (!ru[i]) {//入度为0则变为最初始的状态
						q.push(i);
						vis[i] = 1;
						ans[i] = 1;
					}
				}
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		string ps = s[i].substr(s[i].size() - 3, 3);
		ll id = getid(ps);
		if (ans[id] == 0)   {                 //这里就是ans数组的用处了。
			cout << "Draw" << endl;
		} else if (ans[id] == 1) {
			cout << "Takahashi" << endl;
		} else {
			cout << "Aoki" << endl;
		}
	}
	return 0;
}
~~~

---

