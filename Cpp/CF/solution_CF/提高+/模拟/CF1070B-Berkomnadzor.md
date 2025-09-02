# Berkomnadzor

## 题目描述

联邦通信、信息技术和大众传媒监督局（Berkomnadzor）是伯利兹联邦执行机构，负责保护伯利兹普通居民免受现代互联网的威胁。

Berkomnadzor 拥有一份禁止使用的 IPv4 子网名单（黑名单）和一份允许使用的 IPv4 子网名单（白名单）。柏克兰的所有互联网服务提供商（ISP）都必须配置网络设备，阻止访问符合黑名单的所有 IPv4 地址。同时，ISP 必须允许（即不阻止）所有符合白名单的 IPv4 地址访问。如果某个 IPv4 地址与上述两个列表都不匹配，则由 ISP 决定是否阻止该地址。当且仅当一个 IPv4 地址与黑名单（白名单）中的某个子网相匹配时，它才会与黑名单（白名单）相匹配。一个 IPv4 地址可以同时属于白名单和黑名单，这种情况会导致矛盾（见输出描述中的无解情况）。

IPv4 地址是一个 32 位无符号整数，书写形式为 $a.b.c.d$，其中每个值 $a,b,c,d $ 称为一个八位位组，是一个从 $0 $ 到 $255 $ 的十进制整数。例如，IPv4 地址 $ 192.168.0.1 $ 可以用以下表达式转换为 32 位数字 $ 192 \cdot 2^{24} + 168 \cdot 2^{16} + 0 \cdot 2^8 + 1 \cdot 2^0 $ 。第一个八位位组 $ a $ 编码最有意义（最左边的 $ 8 $ 位），八位位组 $ b $ 和 $ c $ 下面的 $ 8 $ 位块次有意义（按此顺序），八位位组 $ d $ 编码最无意义（最右边的 $ 8 $ 位）。

伯兰的 IPv4 网络与世界其他地方略有不同。伯兰没有保留地址或内部地址，而是使用所有可能的 $ 2^{32} $ 值。

一个 IPv4 子网用 $ a.b.c.d $ 或 $ a.b.c.d/x $ 表示（其中 $ 0 \le x \le 32 $ ）。子网 $ a.b.c.d $ 包含一个地址 $ a.b.c.d $ 。一个子网 $ a.b.c.d/x $ 包含所有最左边（最重要）位 $ x $ 等于地址 $ a.b.c.d $ 最左边位 $ x $ 的 IPv4 地址，要求子网 $ a.b.c.d/x $ 最右边（最不重要）位 $ 32 - x $ 为 0。

与子网 $ a.b.c.d/x $ 匹配的所有地址自然会形成一个连续的范围。该范围从地址 $ a.b.c.d $ 开始（其最右边的 $ 32 - x $ 位为零）。该范围以地址 $ a.b.c.d $ 的最左端 $ x $ 位等于地址 $ a.b.c.d $ 的最左端 $ x $ 位，且其最右端 $ 32 - x $ 位全为 1 的地址结束。子网恰好包含 $ 2^{32-x} $ 地址。子网 $ a.b.c.d/32 $ 恰好包含一个地址，也可以只用 $ a.b.c.d $ 表示。

例如，子网 $ 192.168.0.0/24 $ 包含 256 个地址。$ 192.168.0.0 $ 是地址范围的第一个地址，$ 192.168.0.255 $ 是最后一个地址。

Berkomnadzor 的工程师制定了一项提高 Berland 全球网络性能的计划。他们不想同时维护白名单和黑名单，而只想建立一个包含最少子网数量的优化黑名单。这样做的目的是阻止所有符合优化黑名单的 IPv4 地址，并允许所有其他地址访问。当然，旧黑名单中的 IPv4 地址必须继续封锁，而旧白名单中的所有 IPv4 地址必须继续允许。那些既不符合旧黑名单也不符合旧白名单的 IPv4 地址，无论其以前是否可以访问，都可以被阻止或允许。

请编写一个程序，将黑名单和白名单作为输入，并生成优化黑名单。优化后的黑名单必须包含尽可能少的子网，并满足上述所有 IPv4 地址可访问性要求。

源列表中的 IPv4 子网可以任意交叉。如果某个 IPv4 地址同时符合源白名单和黑名单，请输出一个数字-1。

## 样例 #1

### 输入

```
1
-149.154.167.99
```

### 输出

```
1
0.0.0.0/0
```

## 样例 #2

### 输入

```
4
-149.154.167.99
+149.154.167.100/30
+149.154.167.128/25
-149.154.167.120/29
```

### 输出

```
2
149.154.167.99
149.154.167.120/29
```

## 样例 #3

### 输入

```
5
-127.0.0.4/31
+127.0.0.8
+127.0.0.0/30
-195.82.146.208/29
-127.0.0.6/31
```

### 输出

```
2
195.0.0.0/8
127.0.0.4/30
```

## 样例 #4

### 输入

```
2
+127.0.0.1/32
-127.0.0.1
```

### 输出

```
-1
```

# 题解

## 作者：Obviathy (赞：2)

[原题传送门](https://www.luogu.com.cn/problem/CF1070B)

## 题意简述：

给你若干 $32$ 位 $0-1$ 串，有些只保留前若干位。这些串有黑白两种颜色，求最少有多少个黑色串包含的前缀不被白色串包含，且所有黑色串都至少包含一个这样的前缀。

## 解题思路：

其实我简述的题意是将问题转化了一下，所以不难看出第一步是将 `IP` 地址转化成 $0-1$ 串，除此之外，我们还需要记录两个信息：颜色和前面保留的位数。结构体实现：

```cpp
struct node{
	bitset<40>code;//0-1串
	int son;//保留位数（子网）
	int col;//颜色
}ip[N];
```

然后我们考虑，这道题让找一些前缀，那么果断想到字典树，那好就把这些串建到字典树上吧！显然，字典树需要维护左右儿子，到一个字符串结尾的点还要记录颜色。

```cpp
struct tree{
	int ls,rs;
	int col;
}t[N<<6];
inline void insert(node IP){
	int p = 1;
	for(int i = 1;i <= IP.son;i ++){
		if(t[p].col != 0 && t[p].col != IP.col){
			f = 1;
			return ;
		}
		if(IP.code[i]){
			if(t[p].rs == -1) t[p].rs = ++tot;
			p = t[p].rs;
		}else{
			if(t[p].ls == -1) t[p].ls = ++tot;
			p = t[p].ls;
		}
	}
	if(t[p].col != 0 && t[p].col != IP.col){
		f = 1;
		return ;
	}
	t[p].col = IP.col;
}
```

现在我们拥有了这棵字典树了，考虑如何求答案。

我的方法是，先跑树形 `DP`，`black[i]` 维护它的子树里有多少黑名单，`white[i]` 维护它子树里有多少白名单。

```cpp
inline void solve(int u){
	white[u] = (t[u].col==1),black[u] = (t[u].col==-1);
	if(t[u].ls != -1){
		solve(t[u].ls);
		if(white[t[u].ls] == 1)white[u] = 1;
		black[u] += black[t[u].ls];
	}
	if(t[u].rs != -1){
		solve(t[u].rs);
		if(white[t[u].rs] == 1)white[u] = 1;
		black[u] += black[t[u].rs];
	}
}
```

那么考虑我们选择哪些前缀作为新的黑名单。根据题意，我们发下需要满足如下条件：

- 其子树不含白名单
- 深度最浅

解释一下，对于第一个限制，如果封禁了这个前缀，那么它的子树也都会被封禁，那么必然有白名单被封禁，所以子树内不能有白名单。

第二个限制，考虑需要最少的封禁策略，那么如果搜到一个没有白名单的，直接封禁就好了，没必要封禁比它更深的节点，因为这样你不得不封禁它的兄弟们，这显然不优。

那么就有代码：

```cpp
inline void Find_Ans(int u,node p,int dep,int tp){
	if(dep)p.code[dep] = tp;
	if(white[u]){//如果是有白名单，继续往下搜
		if(t[u].col == -1){
			f = 1;
			return ;
		}
		if(t[u].ls != -1)Find_Ans(t[u].ls,p,dep+1,0);
		if(t[u].rs != -1)Find_Ans(t[u].rs,p,dep+1,1);
	}else{//如果没白名单，直接记录答案。
		p.son = dep;
		ans[++ cnt] = p;
		cover += black[u];
		return ;
	}
}
```

当然，上述代码里可能会有一些你目前不知道干什么的操作，接下来我将对其进行解释。

个人认为，本题中最难处理的便是讨论 `-1` 的情况。我在实现上分了以下几个部分

### 1.在建树时判断

如果我正在建一个白名单串，但是它的一个前缀被标记成黑名单了，那么想要封禁这个黑名单就一定会把这个白名单封掉，所以直接输出 `-1`,反过来同理。

这样我们还需要一个操作：我们在建树时只建到它的子网大小那一位，那么有可能我先建了一个长的，后建了一个短的，那么假如这两个有矛盾，那么显然不会被判断，所以需要先进行排序，先加入短的，后加入长的，即可解决这个问题，否则你将 `Wa on test 222`。

### 2.在找答案时判断

如果我们搜到一个节点是黑名单，但是它的子树里有白名单，那肯定不能封禁它，但它也将再也不会被封禁，所以是矛盾的，输出 `-1`

### 3.在计算完答案后判断

先前树形 `DP` 处理出来的 `black[i]` 不是白处理的，每次找到一个答案，看看覆盖了几个黑名单，显然这种覆盖不会重复（假如有重复，那只能是它覆盖后它的后继再覆盖，但是按照上面的思路一旦选了它就不会再选它的后继了）所以最后判断总的覆盖的黑名单是否等于全部黑名单数。

这里我们还需做另一个操作——去重。因为多个相同的 `IP` 地址我们只会统计一次，这样最后覆盖也只会统计一次，就会无故输出 `-1`，所以我们在一切操作开始前先去一下重，顺便减小一些计算量。否则你将 `Wa on test 250`

当这一切都做好了，就可以输出答案啦！

最后附上又臭又长的代码：(耗时：`686ms`)

## AC code:

```cpp
#include<bits/stdc++.h>
#define ll long long
#define IOS ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
#define file(x) freopen(x".in","r",stdin),freopen(x".out","w",stdout)
#define inf 0x3f3f3f3f
#define endl "\n"
#define mk make_pair
using namespace std;
const int N = 2e5+10;
struct node{
	bitset<40>code;
	int son;
	int col;
}ip[N],x; 
int n,tot=1;
struct tree{
	int ls,rs;
	int col;
}t[N<<6];
int cover,need,cnt,top;
node ans[N];
bool f;
int white[N<<4],black[N<<4];
inline void insert(node IP){
	int p = 1;
	for(int i = 1;i <= IP.son;i ++){
		if(t[p].col != 0 && t[p].col != IP.col){
			f = 1;
			return ;
		}
		if(IP.code[i]){
			if(t[p].rs == -1) t[p].rs = ++tot;
			p = t[p].rs;
		}else{
			if(t[p].ls == -1) t[p].ls = ++tot;
			p = t[p].ls;
		}
	}
	if(t[p].col != 0 && t[p].col != IP.col){
		f = 1;
		return ;
	}
	t[p].col = IP.col;
}
inline void solve(int u){
	white[u] = (t[u].col==1),black[u] = (t[u].col==-1);
	if(t[u].ls != -1){
		solve(t[u].ls);
		if(white[t[u].ls] == 1)white[u] = 1;
		black[u] += black[t[u].ls];
	}
	if(t[u].rs != -1){
		solve(t[u].rs);
		if(white[t[u].rs] == 1)white[u] = 1;
		black[u] += black[t[u].rs];
	}
}
inline void Find_Ans(int u,node p,int dep,int tp){
//	cout << u << " ls: " << t[u].ls << " rs: " << t[u].rs << endl;
	if(dep)p.code[dep] = tp;
	if(white[u]){
		if(t[u].col == -1){
			f = 1;
			return ;
		}
		if(t[u].ls != -1)Find_Ans(t[u].ls,p,dep+1,0);
		if(t[u].rs != -1)Find_Ans(t[u].rs,p,dep+1,1);
	}else{
		p.son = dep;
		ans[++ cnt] = p;
		cover += black[u];
		return ;
	}
}
bool operator < (node A,node B){
	if(A.son == B.son){
		if(A.col == B.col){
			for(int i = 1;i <= 32;i ++)if(A.code[i] != B.code[i])return A.code[i] < B.code[i];
		}
		return A.col < B.col;
	}
	return A.son < B.son;
}
map<node,int>vis;
int main(){
	cin >> n;
	for(int i = 1;i < N<<4;i ++)t[i].ls = t[i].rs = -1;
	for(int i = 1;i <= n;i ++){
		string s;cin >> s;node temp;
		temp.col = (s[0]=='+'?1:-1);
		int res = 0,st = 1,nw;bool fl = 0;
		for(int j = 1;j < s.size();j ++){
			if(s[j] == '.'){
				nw = st*8;
				while(res){
					temp.code[nw --] = res&1;
					res >>= 1;
				}
				res = 0;
				st ++;
			}
			if(isdigit(s[j]))res = res * 10 + s[j]-48;
			if(s[j] == '/'){
				nw = st*8;
				while(res){
					temp.code[nw --] = res&1;
					res >>= 1;
				}
				res = 0;
				st ++;
				res = 0,fl = 1;	
			}
		}
		if(fl)temp.son = res;
		else{
			nw = st*8;
			while(res){
				temp.code[nw --] = res&1;
				res >>= 1;
			}
			temp.son = 32;
		}
		if(vis[temp])continue;
		vis[temp] = 1;
		ip[++top] = temp;
		if(temp.col == -1)need ++;
	}
	n = top;
	sort(ip+1,ip+1+n);
	for(int i = 1;i <= n;i ++){
		insert(ip[i]);
		if(f==1)return cout<<-1<<endl,0;
	}
	solve(1);
	Find_Ans(1,x,0,0);
	if(need > cover || f == 1)return cout << -1 << endl,0;
	cout << cnt << endl;
	for(int i = 1;i <= cnt;i ++){
		node tmp = ans[i];
		int st = 1;
		for(int j = 1;j <= 4;j ++){
			int res = 0;
			for(int i = st;i <= st + 7;i ++)res = (res<<1) + tmp.code[i];
			st += 8;
			cout << res;
			if(j!=4)cout<<'.';
		}
		if(tmp.son != 32){
			cout << '/' << tmp.son;
		}
		cout << endl;
	}
	return 0;
}
```



---

## 作者：徐晨轩✅ (赞：0)

题目大意：给定一些 ip 段，分为禁止的和允许的。现要求拟定一个黑名单，满足在能够禁止给定需要禁止的 ip 的同时，使得给定可以允许的 ip 不被禁止。要求黑名单中包含 ip 段个数最少。

题解：

不难想到 Trie。对于每一个 ip 段，将其转换成二进制并插入。在末尾处打一个标记，表示禁止还是允许。在插入的过程中只要遇到标记与本次的标记相反，就输出 `-1`。

因为不能禁止可以访问的 ip，所以在子树内有允许的标记时不能将这个子树加入黑名单。而如果子树内没有允许的标记时，则可以直接将这个子树加入黑名单，以达到题目要求的个数最小。这个过程可以进行两遍 DFS 来解决。

注意一些细节，如读入处理及 `-1` 的判断。另外，ip 转成二进制时一定要用 `unsigned` 或者 `long long`。

[Code](https://codeforces.com/problemset/submission/1070/243778090)

---

## 作者：PeterBei (赞：0)

考虑把所有的子网地址按照二进制拆开然后存入一棵字典树，令单个子网地址管辖的范围为该子网地址终止节点下的整颗子树，则容易发现在选择优化黑名单时必须满足以下两个性质：

1. 字典树根节点到所有白名单的终止节点路径上不可设置优化黑名单节点，否则优化黑名单将会覆盖白名单。

2. 对于每个未优化黑名单而言，其管辖范围必须是优化黑名单的子集。

考虑到树的深度仅有 $32$，则对于每个地址上跳记录即可。

对于无解：黑白名单管辖子树发生冲突，单独判断即可。

---

## 作者：UncleSam_Died (赞：0)

# CF1070B Berkomnadzor 题解

### 解题思路

不难想到将 IP 地址转化为二进制后插入一个字典树中，转化后二进制的长度就是 $x$ 的长度。我们需要记录每个串结尾的颜色，不妨设黑名单为 $1$，白名单为 $0$，初始时每个位置的颜色是 $-1$。

考虑如何判断输出 `-1` 的情况。不难发现，当在插入当前二进制数的过程中，当前节点到根节点的路径上存在一个颜色不为 $-1$ 且与当前串的颜色不同的点，那么一定存在符合两个名单的 IP 地址。那么我们先把所有的串按照长度排序（没有 $x$ 的长度为 $32$），然后依次插入，这样能够保证在当前串插入前，所有是它前缀的串已经插入了。

接下来考虑如何得到最优黑名单。我们定义 $g(x)$ 表示在以 $x$ 节点为根的子树中，是否存在一个颜色为白色的节点，如果存在，$g(x)=1$，否则等于 $0$。那么我们遍历这棵字典树，贪心地想，深度越小的点一定是更优的，因为如果不将这个点放入黑名单的话，就需要将它的所有儿子放入，那么子网个数一定是大于等于将它作为一个子网的子网个数的。那么，我们遍历的时候，找到第一个满足 $g(x)=0 \vee (g(fa_x)=1\wedge x=root)$ 的节点，然后暴力向上跳，将这个子网记录到答案中。

### AC 代码

```cpp
#include<set>
#include<map>
#include<queue>
#include<stack>
#include<math.h>
#include<vector>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<valarray>
#include<iostream>
#include<algorithm>
#define B 35
#define N 200005
#define M N<<5
#define inf 2e9+7
struct Net{
    bool color;
    int bit=32;
    bool val[B];
    Net():color(0),bit(32){}
    inline bool operator <(
        const Net &b
    ) const {
        return bit<b.bit;
    }
    inline void read(){
        char ch;
        scanf(" %c",&ch);
        if(ch=='-')
            color=1;
        else color=0;
        int a,b,c,d,x=0;
        scanf("%d.%d.",&a,&b);
        scanf("%d.%d",&c,&d);
        ch=getchar();if(ch=='/')
            scanf("%d",&bit);
        x+=a*(1<<24)+c*(1<<8);
        x+=b*(1<<16)+d*(1<<0);
        for(int i=31;i>=0;--i)
            val[32-i]=(x>>i)&1;
    }
    inline void print(){
        puts("_______________________");
        printf("%d %d\n",color,bit);
        for(int i=1;i<=32;++i)
            printf("%d ",val[i]);
        putchar('\n');
        puts("-----------------------");
    }
    inline void printans(){
        for(int i=1;i<=4;++i){
            int x=0;
            for(int j=1;j<=8;++j){
                int now=(i-1)*8+j;
                x=(x<<1)+val[now];
            } printf("%d",x);
            if(i!=4) putchar('.');
        } putchar('/');
        printf("%d\n",bit);
    }
}a[N],ans[N];
int n,cnt;
struct LibTree{
    int depth[M];
    int tree[M][2];
    int cntnode,g[M];
    int color[M],fa[M];
    LibTree(){ cntnode=0;
        for(int i=0;i<M;++i)
            color[i]=-1;
    }
    #define ls(x) tree[x][0]
    #define rs(x) tree[x][1]
    inline void Insert(Net a){
        int now=0;
        for(int i=1;i<=a.bit;++i){
            if(color[now]!=-1){
                if(a.color!=color[now])
                    puts("-1"),exit(0);
            }
            int next=a.val[i];
            if(!tree[now][next])
                tree[now][next]=++cntnode;
            now=tree[now][next];
        }
        if(color[now]!=-1){
            if(color[now]!=a.color)
                puts("-1"),exit(0);
        } color[now]=a.color;
    }
    inline void init(int x){
        if(ls(x)){
            depth[ls(x)]=depth[x]+1;
            init(ls(x));fa[ls(x)]=x;
            g[x]|=g[ls(x)];
        }
        if(rs(x)){
            depth[rs(x)]=depth[x]+1;
            init(rs(x));fa[rs(x)]=x;
            g[x]|=g[rs(x)];
        } g[x]|=color[x]==0;
    }
    inline void dfs(int x){
        if(ls(x)) dfs(ls(x));
        if(rs(x)) dfs(rs(x));
        if(g[x]==0&&(g[fa[x]]==1||x==0)){
            int now=x; ++cnt;
            ans[cnt].bit=depth[x];
            int i=depth[x]; 
            while(now){
                int v=(now==rs(fa[now]));
                ans[cnt].val[i]=v;
                now=fa[now]; --i;
            }
        }
    }
}tree;
signed main(){
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
        a[i].read();
    std::sort(a+1,a+n+1);
    for(int i=1;i<=n;++i)
        tree.Insert(a[i]);
    tree.init(0);tree.dfs(0);
    printf("%d\n",cnt);
    for(int i=1;i<=cnt;++i)
        ans[i].printans();
}
```

---

