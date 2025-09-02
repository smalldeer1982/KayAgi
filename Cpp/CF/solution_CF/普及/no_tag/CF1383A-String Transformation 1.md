# String Transformation 1

## 题目描述

Note that the only difference between String Transformation 1 and String Transformation 2 is in the move Koa does. In this version the letter $ y $ Koa selects must be strictly greater alphabetically than $ x $ (read statement for better understanding). You can make hacks in these problems independently.

Koa the Koala has two strings $ A $ and $ B $ of the same length $ n $ ( $ |A|=|B|=n $ ) consisting of the first $ 20 $ lowercase English alphabet letters (ie. from a to t).

In one move Koa:

1. selects some subset of positions $ p_1, p_2, \ldots, p_k $ ( $ k \ge 1; 1 \le p_i \le n; p_i \neq p_j $ if $ i \neq j $ ) of $ A $ such that $ A_{p_1} = A_{p_2} = \ldots = A_{p_k} =         x $ (ie. all letters on this positions are equal to some letter $ x $ ).
2. selects a letter $ y $ (from the first $ 20 $ lowercase letters in English alphabet) such that $ y>x $ (ie. letter $ y $ is strictly greater alphabetically than $ x $ ).
3. sets each letter in positions $ p_1, p_2, \ldots, p_k $ to letter $ y $ . More formally: for each $ i $ ( $ 1 \le i \le         k $ ) Koa sets $ A_{p_i} = y $ .  Note that you can only modify letters in string $ A $ .

Koa wants to know the smallest number of moves she has to do to make strings equal to each other ( $ A = B $ ) or to determine that there is no way to make them equal. Help her!

## 说明/提示

- In the $ 1 $ -st test case Koa: 
  1. selects positions $ 1 $ and $ 2 $ and sets $ A_1 = A_2 =  $ b ( $ \color{red}{aa}b \rightarrow \color{blue}{bb}b $ ).
  2. selects positions $ 2 $ and $ 3 $ and sets $ A_2 =             A_3 =  $ c ( $ b\color{red}{bb} \rightarrow b\color{blue}{cc} $ ).
- In the $ 2 $ -nd test case Koa has no way to make string $ A $ equal $ B $ .
- In the $ 3 $ -rd test case Koa: 
  1. selects position $ 1 $ and sets $ A_1 =  $ t ( $ \color{red}{a}bc             \rightarrow \color{blue}{t}bc $ ).
  2. selects position $ 2 $ and sets $ A_2 =  $ s ( $ t\color{red}{b}c             \rightarrow t\color{blue}{s}c $ ).
  3. selects position $ 3 $ and sets $ A_3 =  $ r ( $ ts\color{red}{c}             \rightarrow ts\color{blue}{r} $ ).

## 样例 #1

### 输入

```
5
3
aab
bcc
4
cabc
abcb
3
abc
tsr
4
aabd
cccd
5
abcbd
bcdda```

### 输出

```
2
-1
3
2
-1```

# 题解

## 作者：fmj_123 (赞：13)


[链接](https://codeforces.com/problemset/problem/1383/A)

题意：

有字符串$A$，$B$，每次在$A$中选取若干个**相同**的字母（设为$x$），改成另一个字母(设为$y$)，需要满足$x<y$，问将A改成B的最少操作。

数据范围：

组数t$1 \le t \le 10$

字符串长度n $1 \le n \le 10^5$，保证$A$，$B$长度相等，且所有组数长度不超过$10^5$

分析：

从样例看

```
3
aab
bcc
（aab-bbb-bcc)
```

本例中，第2个‘a'先转化成’b'，再连同’b'转化为‘c'。不难看出减少操作次数可以通过先转化为一个中间的字母，再统一转化为另一字母实现。

抽象成图的形式，即在已有'a->b''b->c'的情况下不加'a->c'边。在这个情况下容易想到**并查集**维护。易得操作次数增加当且仅当合并两个块。

这样写将无法得出方案，但本题亦未要求，因此可以通过。

最后，无解产生的条件是存在一个$i$，使$A_i>B_i$

```c++
#include<bits/stdc++.h>
using namespace std;
int f[30],ans,t,n;string st1,st2;
int fafa(int x)
{
	if (f[x]==x) return x;
	return f[x]=fafa(f[x]);
}
void hebing(int x,int y)
{
	x=fafa(x);y=fafa(y);
	if (x!=y)
	{
		ans++;
		f[x]=y;
	}
}//并查集模板
int main()
{
	cin>>t;
	for (int tt=1;tt<=t;tt++)
	{
		cin>>n;
		for (int i=1;i<=26;i++) f[i]=i;
		cin>>st1;
		cin>>st2;
		bool sit=true;ans=0;
		for (int i=0;i<n;i++)
		{
			if (st1[i]>st2[i])
			{
				cout<<"-1\n";sit=false;
				break;
			}//无解情况
			hebing(st1[i]-'a'+1,st2[i]-'a'+1);//相当于上面的连边
		}
		if (sit) cout<<ans<<endl;
		ans=0;
	} 
	return 0;
}
```

PS：官方题解与本题解大致相同，不过官方采用的是建边+联通分量，而这里运用并查集，欢迎讨论优劣。

[博客链接](https://www.cnblogs.com/fmj123/p/13376188.html)

---

## 作者：Miraik (赞：8)

CF div2 C，div1 A。

简单贪心。

~~这C怎么比B1还简单~~

由于题目中要求变化**严格大于**，所以考虑贪心。

我们先用$f_{i,j}$表示当前有多少个字符为$i$，而其目标状态为$j$。

那么我们想让改变次数最少，就必须让还未计算的$f_{i,j}$尽可能大。

那么贪心思想显然了：

每次扫描，当$i\ne j$并且$f_{i,j}>0$时，答案加$1$，并且$f_{j,k}$的值加上$f_{i,k}$ $(j<k<20)$ （$20$即为数据上限）

特判：因为$a_{i}$只能增加，所以当 $a_{i}>b_{i}$时，直接输出$-1$。

具体代码就很简单：

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	return x*f;
}
int t,n,ans,f[35][35];
char a[100005],b[100005];
bool ok;
int main(){
	t=read();
	while(t--){
		n=read();
		scanf("%s\n%s",a,b);//读入 
		ok=1;
		memset(f,0,sizeof(f));
		ans=0;
		//以上3行为初始化 ，ok表示特判 
		for(int i=0;i<n;i++){
			if(b[i]<a[i]){//特判 
				puts("-1");ok=0;break;
			}
			else f[a[i]-'a'][b[i]-'a']++;//字符a[i]到目标状态b[i]的情况增加 
		}
		if(!ok)continue;
		//以下是贪心 
		for(int i=0;i<20;i++)
		    for(int j=0;j<20;j++){
		    	if(i!=j&&f[i][j]){
		    		ans++;
		    		for(int k=j+1;k<20;k++)
		    		    if(f[i][k])f[j][k]+=f[i][k],f[i][k]=0;//转移 
		    	}
		    }
		printf("%d\n",ans);//输出 
	}
	return 0;
}

```


---

## 作者：whiteqwq (赞：3)

[CF1383A String Transformation 1](https://www.luogu.com.cn/problem/CF1383A)解题报告：

[更好的阅读体验](https://zybuluo.com/xiaoziyao/note/1772506)

## 题意
- 给定两个字符串$A,B$，每次在$A$内选取若干个相同字符$x$改为另一个字符$y$，且保证$x<y$，求把$A$改成$B$的最小操作数。
- $1\leqslant |A|=|B|\leqslant 10^5$，多组数据。

## 分析
比较好玩的一道题。

首先特判掉存在$A_i>B_i$的情况，这样明显不合法。

我们考虑每个字符都进行一次操作（从$A_i$改成$B_i$），然后考虑怎么减少操作。

我们把一次字符$x$变为字符$y$的操作看成一条$x$到$y$的有向边，因为所有的边都满足$x<y$，所以这个图一定是一个DAG。

我们发现如果存在$a\rightarrow b,a\rightarrow c,b\rightarrow c$，那么实际上$a\rightarrow c$是没有必要的（直接借助$a\rightarrow b\rightarrow c$就好了）。

那么我们保留任意一颗生成树都是合法的，具体用一个并查集实现就可以了。

## 代码
```
#include<stdio.h>
#include<iostream>
using namespace std;
const int maxk=27;
int T,n,ans,flg;
int f[maxk];
string a,b;
int find(int x){
	return f[x]==x? x:f[x]=find(f[x]);
}
void merge(int x,int y){
	x=find(x),y=find(y);
	if(x!=y)
		f[x]=y,ans++;
}
int main(){
	scanf("%d",&T);
	while(T--){
		ans=flg=0;
		for(int i=1;i<=26;i++)
			f[i]=i;
		scanf("%d",&n);
		cin>>a>>b;
		for(int i=0;i<n;i++){
			if(a[i]>b[i]){
				flg=1;
				break;
			}
			merge(a[i]-96,b[i]-96);
		}
		if(flg==0)
			printf("%d\n",ans);
		else puts("-1");
	}
	return 0;
}
```

---

## 作者：_GW_ (赞：2)

## 思路
首先判无解，显然，只有当存在一个 $i$，使得 $A_i$ 大于 $B_i$，因为他的变换只有这一个限制。

再看，如果 $A_i$ 要变成 $B_i$，那么必定要把 $A_i$ 改为 $B_i$，有时还要把几个与 $A_i$ 相等的 $A_j$ 给改成 $B_i$。

那么当之后再看见与 $A_i$ 相等的字母时，就知道他可以改成 $B_i$。

再仔细一看，发现就是并查集合并。

然后答案就是合并次数了，注意如果本就在一个集合中的两个字母合并时，不要算进合并次数里。

## 复杂度

时间复杂度 $O(n)$，空间复杂度 $O(n)$。

## code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int vis[N],fa[N],num,val,sum[N],n,m,k,T,res;
int find(int x)
{
    return fa[x]==x?x:fa[x]=find(fa[x]);
}
void merge(int x,int y)
{
    int fax=find(x),fay=find(y);
    if(fax!=fay)
    {
        res++;
        fa[fax]=fay;
    }
}
int main()
{
    cin>>T;
    while(T--)
    {
        res=0;
        cin>>n;
        for(int i='a';i<='z';i++)
        {
            fa[i]=i;
        }
        bool flag=1;
        string s1,s2;
        cin>>s1>>s2;
        for(int i=0;i<s1.size();i++)
        {
            if(s1[i]>s2[i])
            {
                flag=0;
            }
            else
            {
                merge(s1[i],s2[i]);
            }
        }
        if(!flag) cout<<-1<<'\n';
        else cout<<res<<'\n';
    }
    return 0;
}
```


---

## 作者：Yun_Mengxi (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1383A)

## 题意

每次操作可以将若干个相同的字符（设为 $x$）改为另一个字符（设为 $y$），需要满足 $x<y$，求 $s$ 变为 $t$ 的最小操作数。

## 分析

因为操作的两个字符必须满足 $x<y$，所以如果相同位置的 $s_i>t_i$，那么显然无解，然后用并查集维护一下集合，输出合并操作的次数就行了。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

int ans, t, n;
int f['z' + 5];
string s1, s2;

int Find(int x) {           // 路径压缩
  return (f[x] == x ? x : (f[x] = Find(f[x])));
}

void Merge(int x, int y) {  // 按秩合并
  x = Find(x);
  y = Find(y);
  if (x != y) {
    ans++;                  // 记录次数
    f[x] = y;
  }
}

void mian() {
  ans = 0;                   // 初始化
  cin >> n;
  for (int i = 'a'; i <= 'z'; i++) {
    f[i] = i;                // 初始化
  }
  cin >> s1;
  cin >> s2;
  for (int i = 0; i < n; i++) {
    if (s1[i] > s2[i]) {     // 无解的情况
      cout << "-1\n";
      return;
    }
    Merge(s1[i], s2[i]);     // 合并操作
  }
  cout << ans << '\n';
}

int main() {
  for (cin >> t; t; t--) {   // 多测
    mian();
  }
  return 0;
}
```

---

## 作者：xujunlang2011 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1383A)

## 思路

先看样例：

```
3
aab
bcc

aab -> bbb (a -> b)

aab -> bcc (b -> c)
```
我们发现 `a` 变成了 `b`，`b` 变成了 `c`，而中间的 `a` 变成了 `c`。

再把这两个操作结合一下：

```
a -> b -> c

a -> c
```

可以看出这里儿子可以变成父亲，很容易可以想到用并查集维护。

然后还有无解的情况。从题目中可以发现，一个字母 $x$ 变成 $y$ 需要满足 $x<y$。（作者没看见卡了半小时……）

所以如果有一个 $i$，满足 $A_i>B_i$，那么就无解。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int t, n, a[N];
string s1, s2;
int find(int k)
{
    if (a[k] == k)
    {
        return k;
    }
    return a[k] = find(a[k]);
}
int main()
{
    cin >> t;
    for (int ti = 1;ti <= t;ti++)
    {
        cin >> n >> s1 >> s2;
        for (int i = 1;i <= 26;i++)
        {
            a[i] = i;
        }
        s1 = " " + s1;
        s2 = " " + s2;
        int cnt = 0;
        bool f = 1;
        for (int i = 1;i <= n;i++)
        {
            if (find(s1[i] - 'a' + 1) != find(s2[i] - 'a' + 1))
            {
                a[find(s1[i] - 'a' + 1)] = find(s2[i] - 'a' + 1);
                cnt++;
            }
            if (s1[i] > s2[i])
            {
                f = 0;
                break;
            }
        }
        if (f)
        {
            cout << cnt << "\n";
        }
        else
        {
            cout << "-1\n";
        }
    }
    return 0;
}
```


---

## 作者：YangXiaopei (赞：1)

## Solution:
无解的情况很简单：某一位上 $A_{i}>B_{i}$。


在其他情况中，很明显减少操作次数可以通过先转化为一个中间的字母，再统一转化为另一字母实现。

抽象成图的形式，即在已有 $a \to b$ $b \to c$ 的情况下不加 $a \to c$ 边。在这个情况下容易想到并查集维护。易得操作次数增加当且仅当合并两个块。

而这样只能求出方案数，刚好可通过本题。
## Code:
```cpp
#include<stdio.h>
#include<iostream>
using namespace std;
const int m = 50;                           ;
int t, n, ans, s;
int f[m];
string a, b;
int find(int x){
	if(a[x] == x){
	    return x;
	}
	return a[x] = find(a[x]);
}
void merge(int x, int y){
	x = find(x),
	y = find(y);
	if(x != y){
		f[x] = y;
		ans++;
	}
}
int main(){
	cin >> t;
	while(t--){
		ans = s = 0;
		for(int i = 1; i <= 26; i++){
			f[i] = i;
		}
		cin >> n;
		cin >> a >> b;
		for(int i = 0; i < n; i++){
			if(a[i] > b[i]){
				s = 1;
				break;
			}
			merge(a[i] - 'a' + 1, b[i] - 'a' + 1);
		}
		if(s == 0){
			cout << ans;
		}
		else{
			cout << -1;
		}
		cout << "\n";
	}
	return 0;
}
```

## 撒花完结。

---

## 作者：LYY_yyyy (赞：0)

我们可以贪心地考虑每一个相同的字符组成的集合，假设他们要到的 $b$ 的最小值为 $m$，将这个集合中除了 $b_i=m$ 的字符全部扔进 $m$ 集合中就行了。证明如下：显然最大只能变为 $m$，否则不合法。假设变为的字符小于 $m$ ，不考虑 $b_i=m$ 的字符时，我们最多只能使答案减一（因为可能会使剩下的字符“整”进其他字符集中一起改变，但是只能整进同一个字符集中）。然而将 $b_i=m$ 的字符变为 $b_i$ 也至少要一次，所以答案肯定不优。证明完毕。实现的话直接暴力模拟就好了，时间复杂度 $O(20\sum n)$。无解判断就是 $a_i>b_i$ 时无解。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
int n;string a,b;
int main()
{
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--)
	{
		cin>>n>>a>>b;
		a='0'+a,b='0'+b;
		vector<int> s[26];bool flag=0;
		int minn[26];memset(minn,0x3f,sizeof(minn));
		for(int i=1;i<=n;i++) 
		{
			if(a[i]>b[i])
			{
				flag=1;break;
			}
			if(a[i]==b[i]) continue;
			s[a[i]-'a'].push_back(b[i]-'a');
			minn[a[i]-'a']=min(minn[a[i]-'a'],b[i]-'a');
		}
		if(flag)
		{
			cout<<"-1\n";continue;
		}
		int ans=0;
		for(int i=0;i<20;i++)
		{
			if(s[i].empty()) continue;
			for(auto o:s[i])
			{
				if(minn[i]==o) continue;
				s[minn[i]].push_back(o);
				minn[minn[i]]=min(minn[minn[i]],o);
			}ans++;
		}cout<<ans<<"\n";
		
	}
}
```

---

## 作者：taojinchen (赞：0)

# 思路
根据题意，对于每一个字母，它都可以变成另一个字母表顺序更加靠后的字母。我们发现题目中有且仅有变成的是另一个字母表顺序更加靠前的字母时无解，可以直接特判。

当我们把第一个集合的每个元素和最终要变成的字母之间建边，我们又可以通过贪心得知，只要我们让每一个字母与其直接相连的边数尽可能的小，操作次数也会少。

此时，我们知道对于一个联通块而言，树是在保证联通的情况下边数最少的，我们可以直接统计总边数，为了保证它是一棵树，我们可以用并查集。因为树是在保证联通的情况下边数是相同的，我们只要统计边数，所以构造出来的树是否合法可以不考虑。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int kM=1e5+5;
int q,n,i,j,f[kM],t,u,v,ans;
string a,b;
int find(int x){
  return x==f[x]?x:f[x]=find(f[x]);
}
int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  cin>>q;
  while(q--){
    cin>>n>>a>>b;
    a=" "+a,b=" "+b;
    t=0;
    for(i=1;i<=n;i++){
      if(a[i]>b[i]){
        t=1;
      }
    }
    if(t){
      cout<<"-1\n";
      continue;
    }
    for(i=0;i<=122;i++)f[i]=i;
    ans=0;
    for(i=1;i<=n;i++){
      u=find(a[i]),v=find(b[i]);
      if(u!=v){
        f[u]=f[v];
        ans++;
      }
    }
    cout<<ans<<"\n";
  }
  return 0;
}
```


---

## 作者：__JiCanDuck__ (赞：0)

# 题意

首先，你必须正确的理解题意，像我~~一个在北平住惯的人~~，没有看清楚题目。

[题目传送门](https://www.luogu.com.cn/problem/CF1383A)

> 有字符串 $A$，$B$，每次在 $A$ 中选取若干个**相同**的字母（设为 $x$），改成另一个字母(设为$y$)，**需要满足** $x<y$，问将A改成B的最少操作。

# 思考

看到这个题目，首先我是蒙的，没有思路。然后看到了比赛的标题（我们练习赛）“并查集”。想到的转变好的合并放在一起，没有转变的不管他。

然后还有一个特判，如果 $A_i > B_i$ 那一定不行。

# 代码

```cpp
#include <iostream>

using namespace std;

string a, b;
int n, fa[300];

int findRt(int x) {
  return fa[x] == x ? x : fa[x] = findRt(fa[x]);
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0); //读入优化
  int t;
  for (cin >> t; t; t--) {
    cin >> n >> a >> b;
    int f = 0, ans = 0;
    for (int i = 0; i < 300; i++) fa[i] = i; //初始化
    for (int i = 0; i < n; i++) {
      if (a[i] > b[i]) f = 1; //无解并标记
      if (findRt(a[i]) != findRt(b[i])) { 
        ans++;
        fa[findRt(a[i])] = findRt(b[i]); //不在一起，合并
      }
    }
    cout << (f ? -1 : ans) << '\n'; //优雅的三目运算
  }
  return 0;
}
```

---

## 作者：foryou_ (赞：0)

若某一位 $i$ 上 $A_i>B_i$，则显然无解。

否则，建立并查集，然后遍历字符串，若 $A_i,B_i$ 不在一个集合就合并 $A_i$ 与 $B_i$，直到只剩下一个集合，此时的合并总次数即为答案。

为什么呢？因为将 $A_i,B_i$ 合并的操作可以视为等价于将以 $A_i$ 开头的连续若干个相同字符均改为 $B_i$，正好就是题目中的所述的操作。

于是当两个字符串中的所有字符都处在同一集合时，$A=B$，那么合并次数就是操作次数了。

时间复杂度 $O(\alpha(n))$。

---

## 作者：A_Đark_Horcrux (赞：0)

我们发现，对于 A 字符串中，需要转化为 B 字符串中同一个字母的几个字母，可以先全部转化为它们中的一个。例如这样一种情况：

```cpp
aaaaf
fgggg
//a->f, a->g, f->g 三组转移关系
//可以先 a->f, 然后全部 f->g 节省了一次转移。
```

这让我们想到从图论角度思考问题，不难看出转化关系可以化成一张图，而“节省转移”可以理解为：两个“节点”间已经能互相到达，则不再加入它们之间的边。这可以用一个并查集维护，最终结果即为连边数量，可以在合并操作时统计。具体可以看代码：


```cpp
#include<cstdio>
#include<cstring>
using namespace std;
const int N=1e5+10;
int T,n,ans,f[N];
bool pd=1;
char a[N],b[N];
void init()//初始化
{
	for(int i=1;i<=26;i++) f[i]=i;
	pd=1; ans=0; return ;
}
int find(int x) {return f[x]==x?x:f[x]=find(f[x]);}//找爸爸
void merge(int x,int y)//合并
{
	int p=find(x),q=find(y);
	if(p!=q) f[q]=p,ans++;//改爸爸，统计答案
	return ;
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d %s %s",&n,a+1,b+1); init();
		for(int i=1;i<=n;i++)
			if(a[i]>b[i]) {puts("-1"); pd=0; break;}//判无解
		if(!pd) continue;
		for(int i=1;i<=n;i++) merge(a[i]-'a'+1,b[i]-'a'+1);//“合并”
		printf("%d\n",ans);//输出答案。
	}
	return 0;
}
```

补充一句，注意到最终形成的是一棵节点数最大为 20 的生成树，因此答案最大为 19，对算法没什么用 ~~（可以用于检查？~~

---

