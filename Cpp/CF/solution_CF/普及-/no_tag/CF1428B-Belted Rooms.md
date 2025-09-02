# Belted Rooms

## 题目描述

In the snake exhibition, there are $ n $ rooms (numbered $ 0 $ to $ n - 1 $ ) arranged in a circle, with a snake in each room. The rooms are connected by $ n $ conveyor belts, and the $ i $ -th conveyor belt connects the rooms $ i $ and $ (i+1) \bmod n $ . In the other words, rooms $ 0 $ and $ 1 $ , $ 1 $ and $ 2 $ , $ \ldots $ , $ n-2 $ and $ n-1 $ , $ n-1 $ and $ 0 $ are connected with conveyor belts.

The $ i $ -th conveyor belt is in one of three states:

- If it is clockwise, snakes can only go from room $ i $ to $ (i+1) \bmod n $ .
- If it is anticlockwise, snakes can only go from room $ (i+1) \bmod n $ to $ i $ .
- If it is off, snakes can travel in either direction.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1428B/76fac914463a158de3ff2f71ea695b0a2d793a84.png)Above is an example with $ 4 $ rooms, where belts $ 0 $ and $ 3 $ are off, $ 1 $ is clockwise, and $ 2 $ is anticlockwise.

Each snake wants to leave its room and come back to it later. A room is returnable if the snake there can leave the room, and later come back to it using the conveyor belts. How many such returnable rooms are there?

## 说明/提示

In the first test case, all rooms are returnable except room $ 2 $ . The snake in the room $ 2 $ is trapped and cannot exit. This test case corresponds to the picture from the problem statement.

 In the second test case, all rooms are returnable by traveling on the series of clockwise belts.

## 样例 #1

### 输入

```
4
4
-><-
5
>>>>>
3
<--
2
<>```

### 输出

```
3
5
3
0```

# 题解

## 作者：jun头吉吉 (赞：3)

# CF1428B 【Belted Rooms】
[$\color{pink}{\text{宣传Blog}}$](https://chen-jia-liang.gitee.io/blog/2020/10/18/%E9%A2%98%E8%A7%A3-CF1428B-%E3%80%90Belted-Rooms%E3%80%91/)
## 题意
有$0\to n-1$个点顺时针地分布在圆上，相邻的两个点之间有传送带。

- 如果是`'>'`，那么只能顺时针走
- 如果是`'<'`，那么只能逆时针走
- 如果是`'-'`，那么两种方向都可以

在一些房间里有蛇，问有多少蛇可以出了房间再回来

## 题解

很显然，当没有`'<'`或没有`'>'`时，所有的蛇都可以出去再回来。

否则，只有`'-'`两边的蛇能够回来，如果不在`'-'`两边，要么出不去，要么回不来。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;char str[300000+100];
signed main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		scanf("%s",str+1);
		int n1=0,n2=0,n3=0;
		for(int i=1;i<=n;i++)
			if(str[i]=='<')n1++;
			else if(str[i]=='-')n2++;
			else if(str[i]=='>')n3++;
		if(n1==0||n3==0)printf("%d\n",n);
		else{
			vector<bool>can(n,false);
			for(int i=1;i<=n;i++)
				if(str[i]=='-')
					can[i-1]=true,can[i%n]=true;
			int cnt=0;
			for(int i=0;i<n;i++)
				cnt+=can[i];
			printf("%d\n",cnt);
		}
	}
	return 0;
}
```

---

## 作者：Prean (赞：2)

打比赛的时候sb了，用了一个似乎原本可以不用的东西来找环。。。

首先，根据题意，我们可以连成一张图，而蛇能不能回到自己的家， 只需要在一个环上就行了。

问题是怎么找环，我用了 Tarjan。。。

具体做法是每个强连通的大小如果不为 $ 1 $，就把这个强连通的大小计入答案。

还有就是记得清空。

code:
```cpp
#include<cstdio>
const int M=3e5+5;
struct Edge{
    int to;Edge*nx;
}e[M<<1],*h[M],*cnt=e;
int n,ans,dfc,top,is[M],stk[M],low[M],dfn[M];
inline void Add(const int&u,const int&v){
    *cnt=(Edge){v,h[u]};h[u]=cnt++;
}
inline int min(const int&a,const int&b){
    return a>b?b:a;
}
void Tarjan(int u){
    is[stk[++top]=u]=true;
    low[u]=dfn[u]=++dfc;
    for(Edge*E=h[u];E;E=E->nx){
        int v=E->to;
        if(!dfn[v]){
            Tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else if(is[v])low[u]=min(low[u],dfn[v]);
    }
    if(low[u]==dfn[u]){
        int v,siz=0;
        do is[v=stk[top--]]=0,++siz; while(v!=u);
        if(siz>1)ans+=siz;
    }
}
signed main(){
    int T,i;char s;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);getchar();
        for(i=1;i<=n;++i){
            h[i]=NULL;
            low[i]=dfn[i]=0;
        }
        top=dfc=ans=0;
        for(i=1;i<=n;++i){
            s=getchar();
            if(s=='<')Add(i%n+1,i);
            else if(s=='>')Add(i,i%n+1);
            else Add(i,i%n+1),Add(i%n+1,i);
        }
        getchar();
        for(i=1;i<=n;++i)if(!dfn[i])Tarjan(i);
        printf("%d\n",ans);
    }
}
```

---

## 作者：chichichichi (赞：1)

这道题就是分类讨论，难度不大。

对于三种道路：

- 如果存在`-`，那么可以在其相邻的两个房间里反复横跳，自然相邻的房间都符合条件。

- 如果存在`<`，那么从与之相邻房间经过这条道路出发只能一条路走到黑，不能回头，即其他道路必须都是`-`或`<`该房间才能符合条件。用 $m1$ 标记该类型是否存在。

- `>`同理，对于从与之相邻经过该道路的房间，其他道路必须都是`-`或`>`该房间才能符合条件。用 $m2$ 标记该类型是否存在。



房间类型：

1. 若一个房间左边或右边是`-`，则其必符合条件，用 $cnt1$来统计。

2. 若一个房间左右都是`<`,用 $cnt2$统计。

3. 若一个房间左右都是`>`，用 $cnt3$统计。

因为是环，我们对于每条道路只统计其之后的房间。

答案：

当`>`和`<`都存在时，$2$ 和 $3$ 类房间都不符合条件，答案为 $cnt1$。

当`<`存在且`>`不存在时，$2$类房间符合条件，答案为 $cnt1+cnt2$。

当`>`存在且`<`不存在时，$3$类房间符合条件，答案为 $cnt1+cnt3$。

代码如下
```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<string>
using namespace std;
const int maxn=312345;
int t,n;
char x[maxn];
int main(){
	scanf("%d",&t);
	for(int i=1;i<=t;i++)
	{
		scanf("%d",&n);
		scanf("%s",x);
		int m1=0,m2=0;
		int cnt1=0,cnt2=0,cnt3=0;
		int len=strlen(x);
		for(int i=0;i<len;i++)
		{
			if(x[i]=='<')
			m1=1;
			if(x[i]=='>')
			m2=1;
			if(x[i]=='-'||x[(i+1)%len]=='-')
			{
				cnt1++;
				continue;
			}
			if(x[i]==x[(i+1)%len]&&x[i]=='>')
			cnt3++;
			
			if(x[i]==x[(i+1)%len]&&x[i]=='<')
			cnt2++;
		}
		if(m1==1&&m2==0)
		{
			cnt1+=cnt2;
		}
		if(m1==0&&m2==1)
		{
			cnt1+=cnt3;
		}
		printf("%d\n",cnt1);
	}
	return 0;
} 

```

---

## 作者：smallfang (赞：1)

我们发现，能出发再回去的要不然是 '-' 要不然是整个图片都是联通的（即全图除了'-'剩下的全都是一个符号）。对于整个图不是联通的，有些点是 '-' 的情况下。（即全图除了'-'剩下的存在两个符号）那就统计 '-' 的影响。每次 '-' 影响左右两边。如果上次的符号是 '-' 那我们只能加一（左边的计算过了）。对于最后一个点，我们要注意一下第一个点是否已经被计算过了。一开始时注意一定要记录一下第一个点是否是 '-' 。代码里写的也比较全。


Code:

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>

using namespace std;

const int N = 3e5 + 5;

bool a[N];

int main()
{
	ios::sync_with_stdio(false);
	int t;
	cin >> t;
	while (t -- )
	{
		int n;
		cin >> n;
		bool flag = false, flag2 = false, l = false, first = false;
		int res = 0;
		for (int i = 0; i < n; i ++ )
		{
			char op;
			cin >> op;
			if (op == '-')
			{
				if (i == 0)
				{
					first = true;
				}
				if (i == n - 1)
				{
					res -= first;
				}
				if (l == false)
				{
					res += 2;
					l = true;
				}
				else
				{
					res ++;
				}
			}
			else if (op == '>')
			{
				flag = true;
				l = false;
			}
			else
			{
				flag2 = true;
				l = false;
			}
			
		}
		if ((flag xor flag2) == true)
		{
			cout << n << endl;
		}
		else
		{
			cout << res << endl;
		}
	}
	return 0;
}
```

---

## 作者：haooo (赞：0)

## 本题模拟即可

有**3**种传送带:**双向**的，**顺时针**的和**逆时针**的

### 我们来分析一下：

1. **双向** ： 

	当一个点左右有至少一个**双向**的传送带时。
    
    显然它是可以回到自己房间的（只需要来回一趟）。

2. **单向** ：

	这个要复杂一点。

	但是他从**单向**的传送带出去就必然**不能原路返回**，必须要绕一圈，**从另外一边回来**。
   
   可以想到 ：只要中间有一个**方向相反**的传送带，就不能**绕一圈**返回原本的房间
   
   所以 ： 只有在**所有的传送带方向相同时**（当然是**除去了双向传送带**的），左右**都是单向传送带的房间**才能回到自己的房间。
   
	于是我们只用**判断全局的传送带是否方向相同**就可以知道能不能回到原本的房间了
    
附上AC代码 ： 
```cpp
#include<bits/stdc++.h>
#define RT register
using namespace std;
const int MAXN=3e5+5;
int t;
int len;
char s[MAXN];
int main(){
    cin>>t;
    for(RT int ti=1;ti<=t;ti++){
        scanf("%d%s",&len,s);
        char op=' ';//op是方向
        bool ju=1;
        for(RT int i=0;i<len;i++){
            if(op!=s[i]&&s[i]!='-'){//当前传送带不为双向的，且与当前不同
                if(op!=' '){
                    ju=0;
                    //ju是判断全部的传送带方向是否相同
                    break;
                }
                else op=s[i];//全部的方向
            }
        }
        int ans=0;
        for(RT int i=0;i<len;i++){
            int l=(i-1+len)%len;
            if(s[i]=='-'||s[l]=='-')    ans++;
            else ans+=ju;//相同就加
        }
        printf("%d\n",ans);
    }
    return 0;
}

```


---

## 作者：vectorwyx (赞：0)

写篇题解纪念一下第一道FST的B题（


------------
首先，如果一个点的左边或右边有一条 '-' 形的传送带，那么这个点一定是符合条件的，因为蛇可以通过这条边先向外走一步再向里走一步回来。

其次，如果一个点的左边或右边没有 '-' 形的传送带，那么蛇如果想要在出发后回到原点必须要绕一整圈。换句话说，这张图必须是连通的。图不连通的情况只可能是 '>' 和 '<' 形传送带同时存在，判断一下就行。

代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define ll long long
#define fo(i,x,y) for(register int i=x;i<=y;++i)
#define go(i,x,y) for(register int i=x;i>=y;--i)
using namespace std;

inline int read(){
	int x=0,fh=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*fh;
}

const int maxn=3e5+5;
char a[maxn];
int b[maxn];

void work(){
	int n=read(),flag1=1,flag2=1,ans=0;
	fo(i,0,n-1) a[i]=getchar(),b[i]=0;
	fo(i,0,n-1){
		if(a[i]=='<') flag1=0;
		if(a[i]=='>') flag2=0;
	}
	fo(i,0,n-1){
		if(a[i]=='-'||a[(i+n-1)%n]=='-') b[i]=1;
		else b[i]=flag1|flag2;
	} 
	fo(i,0,n-1) ans+=b[i];
	printf("%d\n",ans); 
	//puts("");
}
int main(){
	int T=read();
	while(T--){
		work();
	}
	return 0;
}
```


---

## 作者：ycf_remake (赞：0)

~~B题通常不会很难~~

看数据范围，不像图论，所以研究一下性质

1. 当全为 - 时，全图联通
2. 当全为 **>和 -** 或者全为 **< 和 -** 时，全图联通
3. 当 **- > <** 全有时，图不联通

全图联通时，答案一定是节点数，所以重点看第三种情况

当两点之间为 - ，则这两点均满足条件，统计两个点。
但若两个 - 相连，只能统计三个点。所以处理时要注意 i-1 是否为 - 。

不过细心点发现，若i为0时判断i-1会爆炸，因其为环，所以可判断（i+n-1)%n 是否为 - 即可。

代码
```cpp
#include <iostream>

using namespace std;

int T,n,num;
string s;
bool r,l;

int main(void)
{
	cin >> T;
	while(T--)
	{
		cin >> n >> s;
		for(int i=0;i<n;i++)
		{
			if(s[i]=='>')	r=1; 
			else if(s[i]=='<')	l=1;
			else
			{
				if(s[(i+n-1)%n]=='-')	num+=1;
				else	num+=2;
			}	
		}
		if(!r||!l)	cout << n << endl;
		else	cout << num << endl; 
		r=l=num=0;
	}
	return 0;
}
```


---

## 作者：钓鱼王子 (赞：0)

首先，如果整个图是一个环，即不同时存在 $>$ 和 $<$，那么从任意一个点出发都可以绕一圈回到自己。

否则，如果一个点连接了一个 $-$，那么一定可以过去然后回来，否则不可能回到自己，比如当前沿一个 $>$ 离开，肯定没法沿同一边回来，肯定要绕一圈，然而图不是环，所以一定绕不回来。

```cpp
#include<bits/stdc++.h>
#define re register
using namespace std;
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
}
int n,m,t,a[1002],b,c,d,p[1002];
char s[300002];
inline int check(re int x){
	if(s[x]=='-')return 1;
	if(s[x]=='<'&&(!a[p['>']]))return 1;
	if(s[x]=='>'&&(!a[p['<']]))return 1;
	return 0;
}
int main(){
	t=read();
	p['>']=2,p['<']=1;
	while(t--){
		n=read();
		scanf("%s",s+1);
		s[0]=s[n];
		memset(a,0,sizeof(a));
		for(re int i=1;i<=n;++i)++a[p[s[i]]];
		re int ans=0;
		for(re int i=1;i<=n;++i)if(check(i)||check(i-1))++ans;
		printf("%d\n",ans);
	}
}
```


---

## 作者：江户川·萝卜 (赞：0)

$\text{upd:}$ 修正了一处解法上的错误，但是代码是正确的。

----
### 题意：
有 $n$ 个房间，依次标号 $1,2,3,\dots,n$。每个房间有一条蛇。

房间呈环状连接，每两个相邻的房间（包括$\{n,1\}$）都有一条通道连接。

有三钟通道：
1. 只能顺时针走（即只能从 $i$ 走到 $i+1\bmod n$）
2. 只能逆时针走（即只能从 $i+1\bmod n$ 走到 $i$）
3. 两个方向都可以走

每一条蛇希望从所处的房间走出去之后再回来。它们称满足这个条件的房间为`可返回的`。

求`可返回的`房间个数。

---
### 解法：
还是简单思维题。

发现若 $i\to(i+1)\bmod n$ 的通道是顺时针或逆时针的，只有两种情况是`可返回的`，就是全是顺时针的/全是逆时针的（`upd`：若中间夹杂着双向的通道也是可以的）。且这两种情况全部房间都是`可返回的`。这种情况只要特判即可。

若出现`两个方向都可以走`的通道，即两边的房间都可以走向另一个房间再回来，所以两边都是`可返回的`。

---
### 代码：
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		int n;
		scanf("%d",&n);
		bool allcl,allac;
		int offcnt=0;
		char ch,first,lst;
		allcl=allac=true;
		ch=getchar();
		while(ch!='>'&&ch!='<'&&ch!='-') ch=getchar();
		if(ch=='>') allac=false;
		else if(ch=='<') allcl=false;
		else offcnt+=2;
		first=ch;
		lst=ch;
		for(int i=2;i<=n;i++){
			ch=getchar();
			while(ch!='>'&&ch!='<'&&ch!='-') ch=getchar();
			if(ch=='>') allac=false;
			else if(ch=='<') allcl=false;
			else{
				if(lst=='-') offcnt++;
				else offcnt+=2;
			}
			lst=ch;
		}
		if(ch=='-'&&first=='-') offcnt--;
		if(allcl||allac) printf("%d\n",n);
		else printf("%d\n",offcnt);
	}
	return 0;
}
```

---

## 作者：PLDIS (赞：0)

我一拿到这个问题，觉得：这什么东西啊？有向边无向边都有？？？

其实，这道题做法很简单……

为了方便，我们把传送带说成通道。

我们可以看出，**一个房间如果直接连着一条双向的通道，就肯定能出了再回来**，从这条双向通道走到相邻的房间再从这条通道回来就得了。

可是，如果两条边都是单向的，那么就**不能沿着一个通道走到某个房间再原路返回**，毕竟有单向通道。这样，我们只好绕着整个圆走一圈。我们可以看出，**再这种情况下，只要有两条单向的通道方向不一，就一定不能绕着这个个圆走一圈**。

# AC Code:
```cpp
#include <bits/stdc++.h>
using namespace std;
int zh(char c){
    if(c == '-'){
        return 0;
    }
    else if(c == '<'){
        return 1;
    }
    else{
        return 2;
    }
}
bool search(string s){ 
    //判断有没有相反方向的通道
    bool b = false;
    bool bb = false;
    for(int i = 0;i < s.length();i++){
        if(s[i] == '<' && bb){
            return true;
        }
        else if(s[i] == '>' && b){
            return true;
        }
        else if(s[i] == '>'){
            bb = true;
        }
        else if(s[i] == '<'){
            b = true;
        }
    }
    return false;
}
int main(){
    int t;
    cin >> t;
    while(t--){
        int w;
        cin >> w;
        int d[w][2];
        string k;
        cin >> k;
        for(int i = 0;i < k.length();i++){
            if(i == k.length() - 1){
                d[i][0] = zh(k[i]);
                d[i][1] = zh(k[0]);
            }
            else{
                d[i][0] = zh(k[i]);
                d[i][1] = zh(k[i + 1]);
            }
        }
        int ans = 0;
        bool bl = search(k);
        //枚举每个房间
        for(int i = 0;i < w;i++){
            if(d[i][0] && d[i][1]){ 
                //判断直接连着的两个通道是不是都是单向边
                if(!bl){
                    ans++;
                }
            }
            else{
                ans++;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
```

---

