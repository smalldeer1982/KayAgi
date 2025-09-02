# Binary String To Subsequences

## 题目描述

You are given a binary string $ s $ consisting of $ n $ zeros and ones.

Your task is to divide the given string into the minimum number of subsequences in such a way that each character of the string belongs to exactly one subsequence and each subsequence looks like "010101 ..." or "101010 ..." (i.e. the subsequence should not contain two adjacent zeros or ones).

Recall that a subsequence is a sequence that can be derived from the given sequence by deleting zero or more elements without changing the order of the remaining elements. For example, subsequences of "1011101" are "0", "1", "11111", "0111", "101", "1001", but not "000", "101010" and "11100".

You have to answer $ t $ independent test cases.

## 样例 #1

### 输入

```
4
4
0011
6
111111
5
10101
8
01010000```

### 输出

```
2
1 2 2 1 
6
1 2 3 4 5 6 
1
1 1 1 1 1 
4
1 1 1 1 1 2 3 4```

# 题解

## 作者：b6e0_ (赞：12)

[CF题面传送门](https://codeforces.com/contest/1399/problem/D) [洛谷题面传送门](https://www.luogu.com.cn/problem/CF1399D) [博客食用更佳](https://www.luogu.com.cn/blog/b6e0/tijie-CF1399D)

## 8.10更新 LaTeX、英文和中文之间加了空格

发现好多大佬都做复杂了。

首先贪心：要让 $k$ 最小，那么当前的字符要尽可能地跟在前面的字符串内而不是新开一个字符串。这样，我们就可以每扫到一个字符就扫描前面创建出来的字符串，看看能不能跟在它们后面，不能就新开一个，累加答案。可是这种做法会 TLE，假如输入的是一个全 $0$ 或全 $1$ 的字符串，那么时间复杂度就是 $O(n^2)$ 的，无法承受。

一个字符串的结尾只有 $0$ 和 $1$ 两种可能。我们可以开一个 `vector` 数组 $p$，$p_i$ 表示结尾为$i$的字符串有哪些。每扫到一个字符就去它希望字符的 `vector` 里面取一个，删除，在另一个 `vector` 中加入它。由于 `vector` 只方便快速删除结尾，所以取最后面一个。如果找不到（为空），就新开一个字符串，累加答案。

其实也可以用栈或者队列来实现。

具体细节看代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int be[200010];//属于哪个字符串
signed main()
{
    int t,n,i,ans;
    string s;
    cin>>t;
    while(t--)
    {
        cin>>n>>s;
        ans=1;
        vector<int>p[2];
        p[s[0]-'0'].push_back(1);
        be[0]=1;//第一个字符
        for(i=1;i<n;i++)
        {
            int tar=(s[i]-'0')^1;//希望要的结尾
            if(p[tar].empty())//找不到
            {
                be[i]=++ans;
                p[tar^1].push_back(ans);
            }
            else
            {
                int tmp=p[tar][p[tar].size()-1];//取最后一个
                be[i]=tmp;
                p[tar].pop_back();
                p[tar^1].push_back(tmp);
            }
        }
        cout<<ans<<endl;
        for(i=0;i<n;i++)
            cout<<be[i]<<' ';
        cout<<endl;
    }
    return 0;
}
```
时间复杂度为 $O(n)$。

---

## 作者：绝顶我为峰 (赞：1)

题意：把一个 01 串划分成若干个 01 交替的子序列，求最小划分数量并给出任意一组合法划分

首先我们考虑到对于每一个数，我们并不关心每一位属于哪一个子序列，我们只是关心这一位是否可以被划分进前面的子序列中

显然，每一位 0 可以匹配在它前面的任意一个没有被匹配的1，每一位 1 可以匹配在它前面的任意一个没有被匹配的 0，每一位都只能被匹配 1 次

我们在实现时只要找到距离当前位最近的合法匹配即可

考虑维护每一位的前缀 $pre_{0/1}$，表示这一位的排在它前面且最接近当前位的 $0/1$ 的位置，另外开一个 $vis$ 数组来记录当前位是否被匹配过

匹配时直接查找 $pre$ 数组，找到第一个为被匹配的位即可

不过这样做遇到整个序列全是 0 或 1 情况会被卡成 $O(n^2)$ 无法通过

这时我们可以加一个类似并查集路径压缩的优化，在查找时更新 $pre$ 数组，让其指向前一个**未被匹配**的节点，这样可以通过本题

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int t,n,a[200001],ans[200001],sum,pre[200001][2],lst[2],num[200001],cnt;
bool vis[200001];
void print(int x)
{
    if(x>=10)
        print(x/10);
    putchar(x%10+'0');
}
int find(int k,int f)
{
    if(!k)
        return 0;
    if(!vis[k])
    {
        vis[k]=1;
        return k;
    }
    return pre[k][f]=find(pre[k][f],f);
}
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        lst[0]=lst[1]=0;
        sum=n;
        cnt=0;
        for(register int i=1;i<=n;++i)
        {
            char c=getchar();
            while(c!='0'&&c!='1')
                c=getchar();
            a[i]=c-'0';
            pre[i][a[i]^1]=lst[a[i]^1];
            pre[i][a[i]]=lst[a[i]];
            lst[a[i]]=i;
            ans[i]=i;
        }
        for(register int i=2;i<=n;++i)
        {
            int node=find(pre[i][a[i]^1],a[i]^1);
            if(node)
            {
                --sum;
                ans[i]=ans[node];
            }
        }
        print(sum);
        puts("");
        for(register int i=1;i<=n;++i)
        {
            pre[i][0]=pre[i][1]=vis[i]=0;
            if(!num[ans[i]])
                num[ans[i]]=++cnt;
            print(num[ans[i]]);
            putchar(' ');
        }
        for(register int i=1;i<=n;++i)
            num[i]=0;
        puts("");
    }
    return 0;
}
```


---

## 作者：Theophania (赞：1)

我们可以让一个点根据原序列的内容进行移动，将这个问题转化为下面的形式：

假设在平面直角坐标系中有一个点坐标为 $(x,y)$，当走到序列的下一个元素时，如果是 `0` 该点就移动到 $(x+1,y-1)$ 处，如果是 `1` 该点就移动到 $(x+1,y+1)$ 处。为了便于模拟，我们让这个点的初始状态位于原点。

显然，这个点的运动轨迹是一条折线，而且终点在 $(n,num_1-num_0)$。$k$ 的最小值就是折线最高点和最低点之间的距离。这 $k$ 个子序列也可以用它们的纵坐标来表示，画个图稍作推导即可得出。

最后附上代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 9;
int ans[maxn];
unordered_map<int, int> mp;
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int n, x;
        scanf("%d", &n);
        mp.clear();
        int h = 0, maxx = 0, minn = 0, cnt = 0;
        for (int i = 1; i <= n; ++i)
        {
            scanf("%1d", &x);
            if (x == 1)
                h++;
            else
                h--;
            if (h > 0)
            {
                if (h > maxx)
                    mp[h] = ++cnt, maxx = h;//更新最高点高度
                ans[i] = h;
                if (x == 0)
                    ans[i]++;
            }
            else if (h < 0)
            {
                if (h < minn)
                    mp[h] = ++cnt, minn = h;//更新最低点高度
                ans[i] = h;
                if (x == 1)
                    ans[i]--;
            }
            else
            {
                if (x == 1)
                    ans[i] = -1;
                else
                    ans[i] = 1;
            }
        }
        printf("%d\n", cnt);
        for (int i = 1; i <= n; ++i)
            printf("%d ", mp[ans[i]]);
        printf("\n");
    }
    return 0;
}
```


---

## 作者：KSToki (赞：1)

题目大意是给定一个长度为$n$的$01$串，把它分解成最少数量的子序列，使所有的子序列中没有$0$和$1$相邻。

我开始做这道题的时候，想的是找最长的连续是$0$或$1$的子串。显然是错误的，比如$11011$，答案为$3$。

为什么呢？因为我们在中途已经把$0$都“消耗”完了，导致最后一个$1$前面没有$0$，只能新开一个子序列。因此我们需要两个变量$num0$，和$num1$，记录当前以$0$结尾的子序列的数量和当前以$1$结尾的子序列的数量。当我们又要加入一个$1$时，先看$num0$是否为$0$，如果是则++$ans$，++$num1$，否则--$num0$,++$num1$，加入一个$0$时类似。

那如何分组？设第$i$个数的分组为$d_i$，我们只需记录当前$num0$个$0$分别所在的位置$pos0$数组和$num1$个$1$的位置$pos1$数组，当加入一个$1$时如果$num0$为$0$则新加一个子序列，否则令$d[i]=d[pos0[num0]$，最后将其加入$pos1$即可。$0$类似。

到此我们愉快的解决了这个问题。

代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int t,n,a[200001]={2},d[200001];
inline int read()
{
	int res=0,flag=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
		    flag=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res*flag;
}
int pos1[200001],pos0[200001];
int main()
{
	t=read();
	while(t--)
	{
		n=read();
		int ans=0,num1=0,num0=0;
		for(register int i=1;i<=n;++i)
		{
			scanf("%1d",&a[i]);
			if(a[i]==1)
			{
				++num1;
				pos1[num1]=i;
				if(num0>0)
				{
					d[i]=d[pos0[num0]];
					--num0;
				}
				else
				    d[i]=++ans;
			}
			else
			{
				++num0;
				pos0[num0]=i;
				if(num1>0)
				{
					d[i]=d[pos1[num1]];
					--num1;
				}
				else
				    d[i]=++ans;
			}
		}
		printf("%d\n",ans);
		for(register int i=1;i<=n;++i)
			printf("%d ",d[i]);
		printf("\n");
	}
	return 0;
}

```


---

## 作者：引领天下 (赞：1)

由于要求最后的子序列是一个 $0,1$ 交替出现的串，一个很自然的想法是枚举每个元素属于哪个子序列。

考虑一个子序列，它的最后一位是 $0$ 。那么显然它的下一位只能是 $1$ 。这有点像纸牌游戏：黑 $6$ 只能接在红 $7$ 上。

那么我们就可以开若干个 vector ，来存储每个子序列。

对于第 $i$ 个元素，我们在所有 vector 中找一个能让第 $i$ 个元素接上去的序列，将它接上去。如果找不到，我们就只能为它单独开一个序列了。

然后您信心满满的交了上去，然后 `Time limit exceeded on test 4`

~~也许您是欧皇没 T ，反正我是 T 了的。~~

为什么呢？

考虑这样一组数据：

```
6
111111
```

按照我们的做法，每个字符都得枚举一遍所有序列，最后新开一个序列。如果整个字符串全部都是 $0$ 或 $1$ ，那我们的做法就相当于是个 $O(n^2)$ 的做法。然后 $1\le n\le 2\times 10^5$ ……~~您觉得您能 $n^2$ 过十万敬请尝试~~

怎么优化呢？

我们发现对于每个字符，我们实际上只想知道有没有一个能让它接上去的序列。如果枚举，这个过程中将做大量无用功。能否将这部分的时间节省下来？

当然是可以的。我们维护一下当前有哪些序列以 $0$ 结尾，哪些序列以 $1$ 结尾，那么对于一个元素，我们直接看它要接上的序列是否存在就好了：

- 存在，接上去；

- 不存在，新开一个。

至于怎么维护哪些序列以 $0$ 结尾，哪些序列以 $1$ 结尾，直接各开一个队列存储序列的编号就可以了。~~但是我因为贪图少打几个字符，开了两个堆，结果是多带了一个 $log$ 。~~

```cpp
#include <bits/stdc++.h>
#define min(x,y) ((y)^(((x)^(y))&(-((x)<(y)))))
#define max(x,y) ((x)^(((x)^(y))&(-((x)<(y)))))
using namespace std;
int t,n,cnt[200005];
string s;
priority_queue<int,vector<int>,greater<int> > p,q;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>t;
    while(t--){
        cin>>n>>s;
        int k=1;cnt[0]=1;
        if(s[0]=='0')q.push(1);//对1来说，最靠前的以0结尾的序列编号是1
        else p.push(1);//对0来说，最靠前的以1结尾的序列编号是1
        for(int i=1;i<n;i++){
            if(s[i]=='0'){
                if(p.empty())q.push(++k),cnt[i]=k;//如果当前是0，而且没有以1结尾的序列，就只好单开一个了
                else cnt[i]=p.top(),p.pop(),q.push(cnt[i]);//否则接上去，把原序列从以1结尾的队列中删掉，换到以0结尾的队列中。
            }else{
                if(q.empty())p.push(++k),cnt[i]=k;
                else cnt[i]=q.top(),q.pop(),p.push(cnt[i]);//同上
            }
        }
        cout<<k<<endl;
        for(int i=0;i<n;i++)cout<<cnt[i]<<' ';
        cout<<endl;
        while(!p.empty())p.pop();//记得清空
        while(!q.empty())q.pop();
    }
    return 0;
}
```

---

## 作者：dead_X (赞：1)

## 题意
把给定的 $01$ 字符串分成若干个形如 $101010\cdots$ 或 $010101\cdots$ 的字符串，求最少分成几个。
## 思路
贪心：有能用上的字符串就用上，不然就加一个。

$n=1$ 的时候显然一个就够了。

$n>1$ 的时候按照如下方法操作：

初始化：第一个数如果 $0$ ，把剩余 $1$ 数量 $+1$ ，不然把剩余 $0$ 数量 $+1$。答案初始化为 $0$ 。

接下来对于每一个数字执行两个操作：

1. 如果剩余这个数字的数量大于 $0$ 就将剩余这个数字的数量 $-1$ ，不然就将答案 $+1$。

2. 将剩余另外一个数字的数量 $+1$。
## 代码
```
//其实这里不需要写set,int存就可以了
#include<bits/stdc++.h>
#define qwq int T=read(); while(T--)
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
char ch[1000003];
int a[1000003];
set<int> s0,s1;
int main()
{
	a[1]=1;
	qwq
	{
		s0.clear(),s1.clear();
		int n=read(),ans=1;
		scanf("%s",ch+1);
		if(n==1) { puts("1\n1"); continue; }
		if(ch[1]=='0') s1.insert(1); else s0.insert(1);
		for(int i=2; i<=n; i++) 
		if(ch[i]=='0') 
		if(s0.empty()) s1.insert(++ans),a[i]=ans; else s1.insert(*s0.begin()),a[i]=*s0.begin(),s0.erase(s0.begin());
		else
		if(s1.empty()) s0.insert(++ans),a[i]=ans; else s0.insert(*s1.begin()),a[i]=*s1.begin(),s1.erase(s1.begin());
		printf("%d\n",ans);
		for(int i=1; i<=n; i++) printf("%d ",a[i]);
		puts("");
	}
    return 0;
}
//By dead_X
```

---

## 作者：liuyanxi2 (赞：0)

### 易错点

这道题注意一个点：求最长0和最长1的最大值并不是正解，因为在1与0总个数不一样时会出问题

例：11011 

若按照求最长序列，则答案为2，实际上最优只有3；

### 正解

此题的正解是通过两个变量num1，num0分别统计结束点为1或0的序列的个数。当加入一个1是，一个末尾为0的序列就变为1，num0--，num1++；

至于分组，我们只需要一个数组pos0和pos1来存储每个节点位置就可以了

详情见代码

### 代码

```
#include<bits/stdc++.h>
using namespace std;
const int MAX=200001;
int a,b,c,n,m,t,maxa,k[MAX],sta,d[MAX];
int pos1[MAX],pos0[MAX];
int num1,num0;
char st[MAX];
int main ( )
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%s",&n,&st);
		num0=0;num1=0;
		maxa=0;
		for(int i=0;i<=n-1;i++)
		{
			if(st[i]=='1')
			{
				num1++;
				pos1[num1]=i;
				if(num0>0)
				{
					d[i]=d[pos0[num0]];
					num0--;
				}
				else
				d[i]=++maxa;
			}
			else
			{
				num0++;
				pos0[num0]=i;
				if(num1>0)
				{
					d[i]=d[pos1[num1]];
					num1--;
				}
				else
				d[i]=++maxa;
			}
		}
		cout<<maxa<<endl;
		for(int i=0;i<n;i++)
		cout<<d[i]<<' ';
		cout<<endl;
	}
	return 0 ;
}
```


注：本人不经常用printf，一般用cout，大佬勿喷

---

## 作者：tengkaize (赞：0)

~~谢邀，人在 CF，刚下赛场~~

~~有没有乍一看想到拦截导弹~~

策略很简单，设当前数字为 $s_i$，则若有以 $s_i \oplus 1$ 结尾的序列就随便选一个插入 $s_i$，否则新增一个序列

这里提供一种 $O(n)$ 双栈解法~~有插入删除元素和判空的什么容器都行~~

`st[0]` 存 $0$ 结尾子序列的序号，`st[1]` 存 $1$ 结尾子序列的序号

假设已有 $k$ 个子序列。若 `st[s[i] ^ 1]` 非空就 pop 一个出来 push 到 `st[s[i]]` 里，否则需新增一个子序列，`st[s[i]].push(++k)`，此时 `a[i]=st[s[i]].top()`

代码见下

```cpp
#include <cstdio>
#include <stack>

using namespace std;

void r(int& i) {
    i = 0;
    int c = getchar();
    for (; c < '0' || '9' < c; c = getchar()) ;
    for (; '0' <= c && c <= '9'; c = getchar()) i = i * 10 + (c - '0');
}

void r01(int& i) {
    i = 0;
    int c = getchar();
    for (; c != '0' && c != '1'; c = getchar()) ;
    i = c - '0';
}

int t;
int n;
int s[200001];
int a[200001];

int main() {
    int t;
    r(t);
    while (t--) {
        int n;
        r(n);
        stack<int> st[2];
        int k = 0;
        for (int i = 1; i <= n; ++i) {
            r01(s[i]);
            if (!st[s[i] ^ 1].empty()) {
                st[s[i]].push(st[s[i] ^ 1].top());
                st[s[i] ^ 1].pop();
            }
            else {
                st[s[i]].push(++k);
            }
            a[i] = st[s[i]].top();
        }
        printf("%d\n", k);
        for (int i = 1; i <= n; ++i) {
            printf("%d ", a[i]);
        }
        putchar('\n');
    }
    return 0;
}
```

---

## 作者：Doubeecat (赞：0)


## [CF1399D.Binary String To Subsequences](https://codeforces.ml/problemset/problem/1399/D)

> 给你一个长度为 $n$ 且由 $1,0$ 组成的字符串 $s$
> 
> 你的任务是将给定的字符串划分为最少的子序列，每个子序列的字符只属于一个子序列，每个子序列形如 `010101` 或 `101010101` (即子序列不应该包含两个相邻的 0 或 1 )。
>
> 要求输出每个元素的分组方案
> 
> $n \leq 2 \times 10 ^ 5$

考虑构造。

分析题意，我们可以发现一个 1 最多和一个 0 进行匹配，所以可以利用一个栈完成这个操作。

但实际上并没有那么简单，考虑一组样例 `10101` 这里如果暴力匹配的话会发现后面的 `1` 被分到了另外一组，实际上这里是可以分成一组的。

所以我们考虑在每次匹配完后，都把上次匹配完的东西插入栈中进行二次匹配。

具体来说，我们建立两个栈，一个栈存 1 所在的位置，一个栈存 0 所在的位置。

每次扫描到一个新字符，设当前字符为 1，那么先查询 0 的栈里有没有可以匹配的（代表这个 1 可以分到已经存在的组中），令 `pos[now] = pos[s1.top()]`

如果没有，则当前这个 1 肯定是在新的一组中，就是要新建一个组 `pos[now] = ++tot`

反之亦然。

时间复杂度 $O(n)$

### 代码

```cpp
int n;
int pos[N];
stack <int> a,b;
char ch[N];
signed main() {
    int T;cin >> T;
    while (T--) {
        while (!a.empty()) a.pop();
        while (!b.empty()) b.pop();
        memset(pos,0,sizeof pos);
        cin >> n;
        scanf("%s",ch);
        int ans = 0;
        for (int i = 0;i < n;++i) {
            int p = ch[i] - '0';
            if (p == 0) {
                a.push(i);
                if (!b.empty()) {
                    pos[i] = pos[b.top()];
                    b.pop();
                } else {
                    pos[i] = ++ans;
                }
            }
            else {
                b.push(i);
                if (!a.empty()) {
                    pos[i] = pos[a.top()];
                    a.pop();
                } else {
                    pos[i] = ++ans;
                }
            }
        }
        cout << ans << endl;
        for (int i = 0;i < n;++i) {
            cout << pos[i] << " ";
        }
        puts("");
    }
    return 0;
}
```

---

## 作者：Lylighte (赞：0)

#### CF1339D Binary String To Subsequences 题意~~简~~述

对于长度为 $n$，只包含 $0$ 和 $1$ 的一个字符串 $s$，把它拆成 $k$ 个新字符串，使得：

- 每个新字符串是 $s$ 的一个**子序列**；
- $s$ 的每一个字符在这 $k$ 个新字符串中出现且仅出现**一次**；
- 对于每一个新字符串，相邻两个字符**不同**（例如 `010101…`，`101010…`）。

求出 $k$ 的最小值。

输入：$t$ 组数据（$1\le t\le 2\times 10^4$），对于每组数据，第一行一个整数 $n$（$1\le n\le 2\times 10^5$），第二行一个 01 字符串 $s$。保证所有数据 $n$ 的总和小于 $2\times 10^5$。

输出：对于每组数据，第一行是 $k$ 的最小值，第二行 $n$ 个整数，第 $i$ 个整数 $a_i$ 表示 $s_i$ 所在新字符串的编号（$1\le a_i\le k$）。如有多解，输出任意一个即可。

#### 思路~~简~~述

显然在每个新字符串中，$0$ 的前驱是 $1$，$1$ 的前驱是 $0$（不考虑第一个字符）。

对于 $s$ 的每一个字符，尝试找它的前驱，如果找到就接上去，没找到就以这个字符为第一个字符，新增一个新字符串。

开两个栈（队列也可以），记录所有新字符串末尾元素的位置，$0$ 就存在栈 $0$ 里，$1$ 就存在栈 $1$ 里。

初始化 $k=0$，每个栈为空。顺序考虑 $s$ 的每一个字符，若为 $0$，则在栈 $1$ 中找到栈顶元素，弹出，把这个位置记为这个字符位置的前驱；如果该栈为空，则新增一个新字符串，$k$ 值加 $1$。最后把这个位置压入栈 $0$ 中。

字符为 $1$ 的做法类似。 

考虑完毕，$k$ 就是最小值（还不会证啊……）。

至于输出编号，可以想象成染色。另开数组记录染色，在考虑每一个字符的过程中，新增字符串时，$k$ 自增后把该位置染色成 $k$；这个位置有前驱，则这个位置的颜色就是前驱的颜色。

输出染色数组即可。

> 当时做题还想用并查集来着……发现不好染色，就这样做了。

#### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int t, ans, n;
int sta0[200010], sta1[200010], top0, top1;
int a[200010], colo[200010], prea[200010];
char ch;
/*
int find_set(int x){
	if(fa[x]==x)
		return x;
	return fa[x] = find_set(fa[x]);
}

inline void Merge(int x, int y){
	int fax = find_set(x);
	int fay = find_set(y);
	if(fax==fay)
		return;
	fa[fay] = fax;
}
*/
inline void real_main(){
	top0 = top1 = ans = 0;
	scanf("%d\n", &n);
	for(register int i=1; i<=n; ++i){
		ch = getchar();
		if(ch=='0')
			a[i] = 0;
		if(ch=='1')
			a[i] = 1;
//		fa[i] = i;
	}
	for(int i=1; i<=n; ++i){
		if(a[i]==0){
			if(top1==0){
				++ans;//新增字符串
				prea[i] = 0;//相当于清空数组，防止在多组数据中出错
				colo[i] = ans;//染色
			}
			else{
				prea[i] = sta1[--top1];//弹出栈顶元素并记录前驱
				colo[i] = colo[prea[i]];//染色
			}
			sta0[top0++] = i;
		}
		if(a[i]==1){
			if(top0==0){
				prea[i] = 0;
				++ans;
				colo[i] = ans;
			}
			else{
				prea[i] = sta0[--top0];
				colo[i] = colo[prea[i]];
			}
			sta1[top1++] = i;
		}
	}
	printf("%d\n", ans);
	for(int i=1; i<=n; ++i)
		printf("%d ", colo[i]);
	printf("\n");
}

int main(){
	scanf("%d\n",&t);
	while(t>0){
		--t;
		real_main();
	}
	return 0;
}
 
```



---

