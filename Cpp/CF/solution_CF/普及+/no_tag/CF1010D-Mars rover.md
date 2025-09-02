# Mars rover

## 题目描述

Natasha travels around Mars in the Mars rover. But suddenly it broke down, namely — the logical scheme inside it. The scheme is an undirected tree (connected acyclic graph) with a root in the vertex $ 1 $ , in which every leaf (excluding root) is an input, and all other vertices are logical elements, including the root, which is output. One bit is fed to each input. One bit is returned at the output.

There are four types of logical elements: [AND](https://en.wikipedia.org/wiki/Logical_conjunction) ( $ 2 $ inputs), [OR](https://en.wikipedia.org/wiki/Logical_disjunction) ( $ 2 $ inputs), [XOR](https://en.wikipedia.org/wiki/Exclusive_or) ( $ 2 $ inputs), [NOT](https://en.wikipedia.org/wiki/Negation) ( $ 1 $ input). Logical elements take values from their direct descendants (inputs) and return the result of the function they perform. Natasha knows the logical scheme of the Mars rover, as well as the fact that only one input is broken. In order to fix the Mars rover, she needs to change the value on this input.

For each input, determine what the output will be if Natasha changes this input.

## 说明/提示

The original scheme from the example (before the input is changed):

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1010D/12e9ee861137e7cc1d9adb641b01a0e9e6b988c2.png)

Green indicates bits '1', yellow indicates bits '0'.

If Natasha changes the input bit $ 2 $ to $ 0 $ , then the output will be $ 1 $ .

If Natasha changes the input bit $ 3 $ to $ 0 $ , then the output will be $ 0 $ .

If Natasha changes the input bit $ 6 $ to $ 1 $ , then the output will be $ 1 $ .

If Natasha changes the input bit $ 8 $ to $ 0 $ , then the output will be $ 1 $ .

If Natasha changes the input bit $ 9 $ to $ 0 $ , then the output will be $ 0 $ .

## 样例 #1

### 输入

```
10
AND 9 4
IN 1
IN 1
XOR 6 5
AND 3 7
IN 0
NOT 10
IN 1
IN 1
AND 2 8
```

### 输出

```
10110```

# 题解

## 作者：yybyyb (赞：8)

这就是一道水水的小水题啊，不至于成为一个黑题吧。。。（晚上打CF的时候一眼秒啊。。。）  
考虑一下所有的操作，除去$or$和$and$，其它的操作如果当前节点取反的话那么答案一定会取反，而$or$和$and$导致答案不变的情况当且仅当$or$的一个儿子为$1$或者$and$的一个儿子为$0$。  
所以，先求出在不改变的情况下所有节点的值。然后依次$check$所有的$or$和$and$，如果有上述不会改变的情况，就给另外一个子树打上标记，表示这个子树内无论怎么变化答案都不会改变，最后枚举所有$input$节点直接$check$有没有标记，输出对应的答案就好了。  
时间复杂度$O(n)$
```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;
#define ll long long
#define RG register
#define MAX 1001000
inline int read()
{
    RG int x=0,t=1;RG char ch=getchar();
    while((ch<'0'||ch>'9')&&ch!='-')ch=getchar();
    if(ch=='-')t=-1,ch=getchar();
    while(ch<='9'&&ch>='0')x=x*10+ch-48,ch=getchar();
    return x*t;
}
int n;
char ch[20];
struct Line{int v,next;}e[MAX<<1];
int h[MAX],cnt=1;
inline void Add(int u,int v){e[cnt]=(Line){v,h[u]};h[u]=cnt++;}
int p[MAX],c[MAX],fa[MAX],tag[MAX];
void dfs(int u,int ff)
{
    fa[u]=ff;int son[5],tot=0;
    for(int i=h[u];i;i=e[i].next)
        if(e[i].v!=ff)son[++tot]=e[i].v,dfs(e[i].v,u);
    if(p[u]==0)return;
    if(p[u]==1)c[u]=c[son[1]]&c[son[2]];
    if(p[u]==2)c[u]=c[son[1]]^1;
    if(p[u]==3)c[u]=c[son[1]]|c[son[2]];
    if(p[u]==4)c[u]=c[son[1]]^c[son[2]];
    if(p[u]==1)
    {
        int x=son[1],y=son[2];
        if(!c[x])tag[y]=1;if(!c[y])tag[x]=1;
    }
    if(p[u]==3)
    {
        int x=son[1],y=son[2];
        if(c[x])tag[y]=1;if(c[y])tag[x]=1;
    }
}
void dfs2(int u,int ff)
{
    tag[u]|=tag[ff];
    for(int i=h[u];i;i=e[i].next)
        if(e[i].v!=ff)dfs2(e[i].v,u);
}
int main()
{
    n=read();
    for(int i=1;i<=n;++i)
    {
        scanf("%s",ch);
        if(ch[0]=='A')p[i]=1,Add(i,read()),Add(i,read());
        if(ch[0]=='I')p[i]=0,c[i]=read();
        if(ch[0]=='N')p[i]=2,Add(i,read());
        if(ch[0]=='O')p[i]=3,Add(i,read()),Add(i,read());
        if(ch[0]=='X')p[i]=4,Add(i,read()),Add(i,read());
    }
    dfs(1,0);dfs2(1,0);
    for(int i=1;i<=n;++i)
        if(p[i]==0)
        {
            if(tag[i])putchar(48+c[1]);
            else putchar(48+(c[1]^1));
        }
    puts("");return 0;
}
```

---

## 作者：傅思维666 (赞：5)


# 题解：

~~2019.10.24模拟赛T2 30分暴力场~~

### 写在前面

看了其他人的题解，非常的难受。

见过一些大佬的签名是这么写的：**想要变得牛X，得先把自己当成傻X**。

特别喜欢这句话，虽然有些粗鄙。

请不要把自己会做的题都归为傻X题。不论这道题是不是真的那么简单。因为每个人和每道题目都需要足够的尊重。大家都年轻过，都曾经从零开始。请想一想那时的自己看到自己现在的置评时会是什么感觉。

这也是我来发这篇题解的原因。

## 正文

暴力分只要理解好题意就可以拿：可以看出来就是一个简单的深搜，每个节点存一个结构体：操作、左右儿子。（叶子节点的话存值），然后直接开搜，时间复杂度大约是$O(n^2)$的，大约只能过30分...（模糊.jpg）

代码如下：（考场版）

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
const int maxn=1e6+10;
int n;
struct node
{
    char opt[10];
    int a,b;
}t[maxn];
int dfs(int x)
{
    if(t[x].opt[1]=='A')
        return dfs(t[x].a)&dfs(t[x].b);
    else if(t[x].opt[1]=='O')
        return dfs(t[x].a)|dfs(t[x].b);
    else if(t[x].opt[1]=='X')
        return dfs(t[x].a)^dfs(t[x].b);
    else if(t[x].opt[1]=='N')
        return !dfs(t[x].a);
    else
        return t[x].a;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%s",t[i].opt+1);
        if(t[i].opt[1]=='A' || t[i].opt[1]=='X' || t[i].opt[1]=='O')
            scanf("%d%d",&t[i].a,&t[i].b);
        else
            scanf("%d",&t[i].a);
    }
    for(int i=1;i<=n;i++)
        if(t[i].opt[1]=='I')
        {
            t[i].a=!t[i].a;
            printf("%d",dfs(1));
            t[i].a=!t[i].a;
        }
    return 0;
}
```



我们重新来看这道题。数据是$10^6$的，这是$O(n)$或$O(nlogn)$的数据范围，$O(n)$做法比较不现实，我们用$log$的。一看$log$的数据结构，我们应该想到和二有关的一些技巧、算法和数据结构，倍增、树形结构等等。再结合这道题的题目：应该就是树形结构。

带着这个幻想，我们开始重新审题：这是一棵“运算树”。手推几组数据，我们不难发现：如果一个叶子节点被更改影响到，那么可以肯定的是，这个叶子节点到根节点的链（这个链是唯一的）的所有值都会被取反。那么我们来看这些操作，当操作为非或者异或的时候，那么这个节点的值会被取反（任意一个儿子被修改即可）。反之，如果操作为与或或，必须两个儿子的值都被修改，才能被取反。

具体的实现方法是：在每个节点加一个标记数组，表示这个点会不会随着儿子节点的权值变化而变化：如果这个数组的值为1，表示这个节点会随着儿子的值变化而变化，为0则相反。然后就是线段树的过程：如果一个节点为0，那么就把其所有子节点的标记全置成0（则无论怎么改都不会对其造成影响）。反之就下传标记（继续判下面的儿子们）



代码如下：

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int maxn=1e6+10;
int n,ans[maxn],opt[maxn],son[maxn][2],val[maxn];
bool v[maxn];
int turn(char s[])
{
    if(s[0]=='I') 
        return 1;
    if(s[0]=='N') 
        return 2;
    if(s[0]=='O') 
        return 3;
    if(s[0]=='A') 
        return 4;
    if(s[0]=='X') 
        return 5;
}
int dfs1(int u)
{
    if(opt[u]==1) 
        return val[u];
    if(opt[u]==2) 
        return(val[u]=!dfs1(son[u][0]));
    if(opt[u]==3) 
        return(val[u]=(dfs1(son[u][0])|dfs1(son[u][1])));
    if(opt[u]==4) 
        return(val[u]=(dfs1(son[u][0])&dfs1(son[u][1])));
    if(opt[u]==5) 
        return(val[u]=(dfs1(son[u][0])^dfs1(son[u][1])));
}
void dfs2(int u)
{
    if(v[u]==0) 
        v[son[u][0]]=v[son[u][1]]=0;
    else
    {
        switch(opt[u])
        {
            case 2:
                v[son[u][0]]=1;
                break;
            case 3:
                if(val[son[u][0]]) 
                    v[son[u][1]]=0;
                else 
                    v[son[u][1]]=1;
                if(val[son[u][1]]) 
                    v[son[u][0]]=0;
                else 
                    v[son[u][0]]=1;
                break;
            case 4:
                if(!val[son[u][0]])
                    v[son[u][1]]=0;
                else 
                    v[son[u][1]]=1;
                if(!val[son[u][1]]) 
                    v[son[u][0]]=0;
                else 
                    v[son[u][0]]=1;
                break;
            case 5:
                v[son[u][0]]=v[son[u][1]]=1; 
                break;
        }
    }
    v[0]=0;
    if(son[u][0]) 
        dfs2(son[u][0]);
    if(son[u][1]) 
        dfs2(son[u][1]);
}
int main()
{
    memset(v,1,sizeof(v));
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        char s[10]; 
        scanf("%s",s);
        opt[i]=turn(s);
        if(opt[i]==1)
            scanf("%d",&val[i]);
        else if(opt[i]==2) 
            scanf("%d",&son[i][0]);
        else 
            scanf("%d%d",&son[i][0],&son[i][1]);
    }
    dfs1(1);
    v[1]=1;
    dfs2(1);
    for(int i=1;i<=n;i++) 
        if(opt[i]==1)  
            printf("%d",val[1]^v[i]);
    return 0;
}
```



---

## 作者：大菜鸡fks (赞：3)

因为每次只会改变一个点的值，所以是傻题。

rt_val[u][0/1]表示这个点值为0或1时，根节点的值。

然后递推一遍
```cpp
#include<cstdio>
using namespace std;
const int N=1e6+5;
int opt[N],val[N],n,son[N][2],fa[N];
inline void init(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++){
		char s[10]; int x,y;
		scanf("%s",s+1);
		if (s[1]=='A') opt[i]=1;
		if (s[1]=='O') opt[i]=2;
		if (s[1]=='X') opt[i]=3;
		if (s[1]=='I'||s[1]=='N') {
			scanf("%d",&x);
			if (s[1]=='N') opt[i]=4,son[i][0]=x,fa[x]=i;
				else val[i]=x;
		}else{
			scanf("%d%d",&x,&y);
			son[i][0]=x; son[i][1]=y;
			fa[x]=i; fa[y]=i;
		}
	} 
}
int work(int u){
	if (opt[u]==1) return val[son[u][0]]&val[son[u][1]];
	if (opt[u]==2) return val[son[u][0]]|val[son[u][1]];
	if (opt[u]==3) return val[son[u][0]]^val[son[u][1]];
	if (opt[u]==4) return !val[son[u][0]];
}
void dfs(int u){
	if (!u||!opt[u]) return;
	dfs(son[u][0]); dfs(son[u][1]); 
	val[u]=work(u);
}
int ans[N],rt_val[N][2];
void Dfs(int u){
	if (!u) return;
	int tmp=val[u];	
	if (u!=1){
		val[u]=0; rt_val[u][0]=rt_val[fa[u]][work(fa[u])];
		val[u]=1; rt_val[u][1]=rt_val[fa[u]][work(fa[u])];
	}
	val[u]=tmp;
	Dfs(son[u][0]); Dfs(son[u][1]);
	if (!opt[u]){
		ans[u]=rt_val[u][!tmp];
	}
}
inline void solve(){
	dfs(1);
	rt_val[1][0]=0; rt_val[1][1]=1;
	Dfs(1);
	for (int i=1;i<=n;i++){
		if (!opt[i]){
			putchar((ans[i])?'1':'0');
		} 
	}
	puts("");
}
int main(){
	init();
	solve();
	return 0;
} 
```


---

## 作者：wurzang (赞：2)

普及组选手就适合写普及组题解。

由于只修改一个值，所以我们就考虑修改这个值后对根节点是否会有影响。

显然如果在 `AND` 的时候满足左儿子的值为 `0`，那么右儿子子树中所有的点修改后对根节点都没有影响。右儿子同理。`OR` 的时候同理。

那么考虑按照这种方式给点打一个废物标签 $fw_i$，如果 $f_i=1$ 表示这个点子树中所有的点修改后对根节点都没有影响，通过再一次 `dfs` 把废物标签下传即可。

不懂可以看代码，作为普及组题目还是比较简单的。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int fw[N],n,val[N],opt[N];
int ch[N][2];
void redfs(int x){
	if(fw[x]){
		if(ch[x][0]) fw[ch[x][0]]=1,redfs(ch[x][0]);
		if(ch[x][1]) fw[ch[x][1]]=1,redfs(ch[x][1]);
		return;
	}
	if(ch[x][0]) redfs(ch[x][0]);
	if(ch[x][1]) redfs(ch[x][1]);
}
void dfs(int x){
//	cout<<x<<endl;
	if(opt[x]==0) return;
	int i=x;
	if(opt[x]==1){
		dfs(ch[i][0]),dfs(ch[i][1]);
		if(val[ch[i][0]]==0) fw[ch[i][1]]=1;
		if(val[ch[i][1]]==0) fw[ch[i][0]]=1;
		val[x]=val[ch[i][0]]&val[ch[i][1]];
		//if(x==10) cout<<val[x]<<" "<<val[ch[i][0]]<<" "<<val[ch[i][1]]<<endl;
		return;	
	} 
	if(opt[x]==2){
		dfs(ch[i][0]),dfs(ch[i][1]);
		val[x]=val[ch[i][0]]^val[ch[i][1]];	
		return;	
	}
	if(opt[x]==3){
		dfs(ch[i][0]),dfs(ch[i][1]);
		if(val[ch[i][0]]==1) fw[ch[i][1]]=1;
		if(val[ch[i][1]]==1) fw[ch[i][0]]=1;
		val[x]=val[ch[i][0]]|val[ch[i][1]];	
		return;	
	}	
	dfs(ch[i][0]);
	val[x]=!val[ch[i][0]];
}
signed main(){
	cin>>n;
	char s[10];
	for(int i=1;i<=n;++i){
		cin>>s;
		if(s[0]=='I') opt[i]=0,cin>>val[i];
		if(s[0]=='A') opt[i]=1,cin>>ch[i][0]>>ch[i][1];
		if(s[0]=='X') opt[i]=2,cin>>ch[i][0]>>ch[i][1];
		if(s[0]=='O') opt[i]=3,cin>>ch[i][0]>>ch[i][1];
		if(s[0]=='N') opt[i]=4,cin>>ch[i][0];
	}
	dfs(1);
	redfs(1);
//	for(int i=1;i<=n;++i)
//		cout<<i<<" "<<val[i]<<endl;
//	cout<<val[1]<<endl;
	for(int i=1;i<=n;++i)
		if(opt[i]==0) cout<<(val[1]^fw[i]^1);
	return 0;
} 
```


---

## 作者：Lotus_Land (赞：0)

先根据题意把表达式树建好。

$data[i]$ 表示节点 $i$ 对应的运算，$-1$ 对应 AND，$-2$ 对应 OR，$-3$ 对应 XOR，$-4$ 对应 NOT。

```cpp
	scanf("%d",&n);
	for(int i=1; i<=n; i++) {
		cin>>s;
		int x,y;
		if(s=="AND"){
			scanf("%d%d",&x,&y);
			data[i]=-1;
			son[i][0]=x;
			son[i][1]=y;
		}else if(s=="OR"){
			scanf("%d%d",&x,&y);
			data[i]=-2;
			son[i][0]=x;
			son[i][1]=y;
		}else if(s=="XOR"){
			scanf("%d%d",&x,&y);
			data[i]=-3;
			son[i][0]=x;
			son[i][1]=y;
		}else if(s=="IN"){
			scanf("%d",&x);
			tr[i]=x;
		}else if(s=="NOT"){
			scanf("%d",&x);
			data[i]=-4;
			son[i][0]=x;
		}
	}
```
然后从根节点开始，进行两次 DFS。

第一次是为了把每个节点的值都求出来。

```cpp
void update(int x) {
	if(data[x]==0) {
		return;
	}
	update(son[x][0]);
	update(son[x][1]);
	if(data[x]==-1) {
		tr[x]=tr[son[x][0]]&tr[son[x][1]];
	} else if(data[x]==-2) {
		tr[x]=tr[son[x][0]]|tr[son[x][1]];
	}else if(data[x]==-3){
		tr[x]=tr[son[x][0]]^tr[son[x][1]];
	}else if(data[x]==-4){
		tr[x]=tr[son[x][0]]^1;
	}
}
```

第二次，用一个数组 $aff[i]$ 记录节点 $i$ 的值改变，根结点的值是否会改变。

对于一个节点 $u$，设它的任一个子结点为 $v$，

- 如果 $u$ 的运算为 AND，且 $v$ 的值为 0，那么另一个子节点的值改变对 $u$ 的值**没有影响**，否则有影响。

- 如果 $u$ 的运算为 OR，且 $v$ 的值为 1，那么另一个子节点的值改变对 $u$ 的值**没有影响**，否则有影响。

- 如果 $u$ 的运算为 XOR 或 NOT，那么无论它哪个子节点的值改变，都对 $u$ 的值**有影响**。

到这里只是算出了 $v$ 对 $u$ 的影响。

接下来，如果 $u$ 对**根节点**没有影响，则 $v$ 就一定对**根节点**没有影响；

如果 $u$ 对**根节点**有影响，则 $v$ 对 根节点 是否有影响，就取决于 $v$ 对 $u$ 是否有影响。

```cpp
void update2(int x) {
	if(son[x][0]==0)return;
	if(data[x]==-1) {
		if(tr[son[x][0]]==0) {
			aff[son[x][1]]=0;
		} else aff[son[x][1]]=1;
		if(tr[son[x][1]]==0) {
			aff[son[x][0]]=0;
		} else aff[son[x][0]]=1;
	} else if(data[x]==-2) {
		if(tr[son[x][0]]==1) {
			aff[son[x][1]]=0;
		} else aff[son[x][1]]=1;
		if(tr[son[x][1]]==1) {
			aff[son[x][0]]=0;
		} else aff[son[x][0]]=1;
	}else if(data[x]==-3){
		aff[son[x][0]]=1;
		aff[son[x][1]]=1;
	}else if(data[x]==-4){
		aff[son[x][0]]=1;
	}
	if(aff[son[x][0]]==1) {
		if(aff[x]==0)aff[son[x][0]]=0;
	}
	if(aff[son[x][1]]==1) {
		if(aff[x]==0)aff[son[x][1]]=0;
	}
	update2(son[x][0]);
	if(data[x]!=-4)update2(son[x][1]);
}
```
最后输出答案时，对于一个叶子节点 $i$，如果 $aff[i]=1$，输出根节点的值取反，否则输出根节点的值。

完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int son[1000005][2],tr[1000005],data[1000005];
bool aff[1000005];
//& -1
//| -2
//^ -3
//~ -4
string s;
int n;
void update(int x) {
	if(data[x]==0) {
		return;
	}
	update(son[x][0]);
	update(son[x][1]);
	if(data[x]==-1) {
		tr[x]=tr[son[x][0]]&tr[son[x][1]];
	} else if(data[x]==-2) {
		tr[x]=tr[son[x][0]]|tr[son[x][1]];
	}else if(data[x]==-3){
		tr[x]=tr[son[x][0]]^tr[son[x][1]];
	}else if(data[x]==-4){
		tr[x]=tr[son[x][0]]^1;
	}
}
void update2(int x) {
	if(son[x][0]==0)return;
	if(data[x]==-1) {
		if(tr[son[x][0]]==0) {
			aff[son[x][1]]=0;
		} else aff[son[x][1]]=1;
		if(tr[son[x][1]]==0) {
			aff[son[x][0]]=0;
		} else aff[son[x][0]]=1;
	} else if(data[x]==-2) {
		if(tr[son[x][0]]==1) {
			aff[son[x][1]]=0;
		} else aff[son[x][1]]=1;
		if(tr[son[x][1]]==1) {
			aff[son[x][0]]=0;
		} else aff[son[x][0]]=1;
	}else if(data[x]==-3){
		aff[son[x][0]]=1;
		aff[son[x][1]]=1;
	}else if(data[x]==-4){
		aff[son[x][0]]=1;
	}
	if(aff[son[x][0]]==1) {
		if(aff[x]==0)aff[son[x][0]]=0;
	}
	if(aff[son[x][1]]==1) {
		if(aff[x]==0)aff[son[x][1]]=0;
	}
	update2(son[x][0]);
	if(data[x]!=-4)update2(son[x][1]);
}
void printtree(int x) {
	if(!x)return;
	printtree(son[x][0]);
	printf("%d %d\n",x,data[x]);
	printtree(son[x][1]);
}
int main() {
	//freopen("in.txt","r",stdin);
	scanf("%d",&n);
	for(int i=1; i<=n; i++) {
		cin>>s;
		int x,y;
		if(s=="AND"){
			scanf("%d%d",&x,&y);
			data[i]=-1;
			son[i][0]=x;
			son[i][1]=y;
		}else if(s=="OR"){
			scanf("%d%d",&x,&y);
			data[i]=-2;
			son[i][0]=x;
			son[i][1]=y;
		}else if(s=="XOR"){
			scanf("%d%d",&x,&y);
			data[i]=-3;
			son[i][0]=x;
			son[i][1]=y;
		}else if(s=="IN"){
			scanf("%d",&x);
			tr[i]=x;
		}else if(s=="NOT"){
			scanf("%d",&x);
			data[i]=-4;
			son[i][0]=x;
		}
	}
	aff[1]=1;
	
	update(1);
//	for(int i=1;i<=n;i++)cout<<tr[i]<<' ';
//	cout<<endl;
	update2(1);
//	for(int i=1;i<=n;i++)cout<<aff[i]<<' ';
//	cout<<endl;
	for(int i=1;i<=n;i++){
		if(data[i]==0){
			cout<<((aff[i]==1)?tr[1]^1:tr[1]);
		}
	}
	return 0;
}
```


---

## 作者：旭日临窗 (赞：0)

首先暴力$n^2$对于$n \le 10^6$肯定是过不去的。

所以第一时间想到了**建树**。

思路：

1. 建树：把每一个运算符看作是一棵树的根，左儿子和右儿子就是要进行运算的子树（可以看做是一个表达式），叶节点就是IN，当然，NOT只有一个儿子，可以看到这棵树是一棵二叉树。

code:

```c
void read()
{
	int x,y;
	char c,a;
	for(int k = 1;k <= n;k++)
	{
		while(!isalpha((c = getchar())));
		if(c == 'I')
		{
			a = getchar();
			a = getchar();
			scanf("%d",&x);
			tr[k] = node(x,0,0);
			s[++m] = k;
		} 
		else if(c == 'N')
		{
			for(int i = 1;i <= 3;i++) a = getchar();
			scanf("%d",&x);
			tr[k] = node(x,0,c);
		}
		else 
		{
			if(c == 'O') a = getchar(),a = getchar();
			else
			for(int i = 1;i <= 3;i++) a = getchar();
			scanf("%d%d",&x,&y);
			tr[k] = node(x,y,c);
		}
	}
}
```


2. 求这棵树的值：可以用深搜，如果这个节点的运算符是（AND、OR、XOR、NOT）就返回dfs（左儿子）（AND、OR、XOR、NOT）dfs（右儿子）
用一个数组记录下第$i$个节点的值。

code:

```c
int dfs(int u)
{
	if(!tr[u].op) return ans[u] = tr[u].l;
	if(tr[u].op == 'A') return ans[u] = dfs(tr[u].l) & dfs(tr[u].r);
	if(tr[u].op == 'O') return ans[u] = dfs(tr[u].l) | dfs(tr[u].r);
	if(tr[u].op == 'X') return ans[u] = dfs(tr[u].l) ^ dfs(tr[u].r);
	if(tr[u].op == 'N') return ans[u] = !dfs(tr[u].l);
}
```

3. 关键是最后一步：对于每一次取反，树的值会不会改变呢？

先插一张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/k5bsdv9n.png)

我们发现，对于每一个节点，它的值改不改变，其实取决于它的子节点的值改不改变。

code:

```c
void change(int u)
{
	if(!tr[u].op) cg[u] = 1;
	if(tr[u].op == 'N') change(tr[u].l);
	if(tr[u].op == 'A')
	{
		if(ans[tr[u].l] == 1 && ans[tr[u].r] == 0) change(tr[u].r);
		if(ans[tr[u].l] == 0 && ans[tr[u].r] == 1) change(tr[u].l);
		if(ans[tr[u].l] == 1 && ans[tr[u].r] == 1) change(tr[u].l),change(tr[u].r);
	}
	if(tr[u].op == 'O')
	{
		if(ans[tr[u].l] == 1 && ans[tr[u].r] == 0) change(tr[u].l);
		if(ans[tr[u].l] == 0 && ans[tr[u].r] == 1) change(tr[u].r);
		if(ans[tr[u].l] == 0 && ans[tr[u].r] == 0) change(tr[u].l),change(tr[u].r);
	}
	if(tr[u].op == 'X') change(tr[u].l),change(tr[u].r);
}
```



---

## 作者：GGMU (赞：0)

1e6数据大小，暴力的话$O(n^{2})$肯定是不行的。所以，首先预处理把整棵树建出来，计算一下不修改状态下，每个结点的值，方法很多，我使用了拓扑排序。随后，从根节点开始进行dfs搜索，对于每个儿子，判断这个儿子当前状态下只修改是否会对上方结果发生改变，如果改变继续搜索，不发生改变就返回。举个简单的例子，例如，0与1经过与门，1发生改变肯定不对结果产生产生影响，因为另一个是0，结果必然我0，所以下方输入即使发生变化，对最终结果也不会产生影响，而0发生改变，1则会使最终结果发生改变，因为与门会使结果从0变为1，对0的两个来源进行搜索，如果搜索到树根的话就表明这个点的改变会影响到最终结果，反之不会，最后按顺序输出即可，时间复杂度$O(n)$。
```cpp
#include<bits/stdc++.h>
 
using namespace std;
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair <ll,ll> pii;
#define rep(i,x,y) for(int i=x;i<y;i++)
#define rept(i,x,y) for(int i=x;i<=y;i++)
#define per(i,x,y) for(int i=x;i>=y;i--)
#define all(x) x.begin(),x.end()
#define pb push_back
#define fi first
#define se second
#define mes(a,b) memset(a,b,sizeof a)
#define mp make_pair
#define dd(x) cout<<#x<<"="<<x<<" "
#define de(x) cout<<#x<<"="<<x<<"\n"
#define debug() cout<<"I love Miyamizu Mitsuha forever.\n"
const int inf=0x3f3f3f3f;
const int maxn=1e6+5;
class Tree
{
	public:
		int son1,son2;
		int val;
		int op;//and=1,or=2,xor=3,not=4,in=5
		bool rev;
		vector<int> v;
}tree[maxn];
int degree[maxn];
queue<int> q;
 
void dfs(int id)
{
	tree[id].rev=1;
	if(tree[id].op==5)
		return ;
	if(tree[id].op==1)
	{
		if(tree[tree[id].son1].val) dfs(tree[id].son2);
		if(tree[tree[id].son2].val) dfs(tree[id].son1);
	}
	if(tree[id].op==2)
	{
		if(!tree[tree[id].son1].val) dfs(tree[id].son2);
		if(!tree[tree[id].son2].val) dfs(tree[id].son1);
	}
	if(tree[id].op==3)
	{
		dfs(tree[id].son1);
		dfs(tree[id].son2);
	}
	if(tree[id].op==4)
	{
		dfs(tree[id].son1);
	}
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;
	cin>>n;
	rept(i,1,n)
	{
		tree[i].rev=0;
		string s;
		cin>>s;
		if(s=="AND")
		{
			tree[i].op=1;
			cin>>tree[i].son1>>tree[i].son2;
			tree[tree[i].son1].v.pb(i);
			tree[tree[i].son2].v.pb(i);
			degree[i]=2;
		}
		else if(s=="OR")
		{
			tree[i].op=2;
			cin>>tree[i].son1>>tree[i].son2;
			tree[tree[i].son1].v.pb(i);
			tree[tree[i].son2].v.pb(i);
			degree[i]=2;
		}
		else if(s=="XOR")
		{
			tree[i].op=3;
			cin>>tree[i].son1>>tree[i].son2;
			tree[tree[i].son1].v.pb(i);
			tree[tree[i].son2].v.pb(i);
			degree[i]=2;
		}
		else if(s=="NOT")
		{
			tree[i].op=4;
			cin>>tree[i].son1;
			tree[tree[i].son1].v.pb(i);
			degree[i]=1;
		}
		else if(s=="IN")
		{
			tree[i].op=5;
			cin>>tree[i].val;
			q.push(i);
		}
	}
	int root;
	while(!q.empty())
	{
		int id=q.front();
		root=id;
		q.pop();
		rep(i,0,tree[id].v.size())
		{
			degree[tree[id].v[i]]--;
			if(!degree[tree[id].v[i]]) q.push(tree[id].v[i]);
		}
		if(tree[id].op==5) continue;
		else if(tree[id].op==1)
		{
			tree[id].val=(tree[tree[id].son1].val&&tree[tree[id].son2].val);
		}
		else if(tree[id].op==2)
		{
			tree[id].val=(tree[tree[id].son1].val||tree[tree[id].son2].val);
		}
		else if(tree[id].op==3)
		{
			tree[id].val=(tree[tree[id].son1].val^tree[tree[id].son2].val);
		}
		else if(tree[id].op==4)
		{
			tree[id].val=!tree[tree[id].son1].val;
		}
	}
	dfs(root);
	rept(i,1,n)
		if(tree[i].op==5)
		{
			if(tree[i].rev) cout<<!tree[root].val;
			else cout<<tree[root].val;
		}
	return 0;
}
```


---

## 作者：Iam1789 (赞：0)

## 题外话
~~来自[某年普及组T3](https://www.luogu.com.cn/problem/P7073)的怨念~~

话说这题比那题还少了个处理字符串为啥这题是紫而那题只有绿，建议更正一下难度。
## 正文
### 1、暴力做法
挨个改变依次求值，很明显无法拿到很高的分。这里就不多说了。
### 2.从叶子节点向根节点维护
该种做法的主要算法是从改变叶节点后依次向根节点求值。显然，如果搜到一个节点它的值相对于原来没有改变，那么就不用向下搜了，直接输出根节点的值就可以了。如果一直搜到了根节点即1号节点，那么就说明根节点的值被改变了，需要对根节点的值进行取反。

对于判断每个节点时是否对其父节点，我们可以用一个bool来在建树时进行存储，这样可以方便遍历。正如前面的大佬们所说，除了|和&之外改变的话都是一定改变的，|和&有特殊的规律，可以看看那几位大佬的，这里就不细说了。

这种做法在第88个点会TLE（~~然而本蒟蒻因为把|写成了||而在第21个点卡了一页评测~~，所以我们需要对这个算法进行优化。

### 3、做法2+记忆化
很明显，对于之前已经遍历出 该节点的值改变后 根节点的值是否改变的 那些节点来说，就没有必要再去搜一遍了。对于每个节点，我们可以增加一个数组，来表示改变这个节点的值根节点的值是否会被改变。在之后搜到这个节点时，就可以直接返回根节点是否改变了。这个数组需要用int或short，因为我们需要存不会改变，会改变，和未被遍历三种状态，一个bool无法存下。

AC代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
int le[1000007];
int lev; 
inline int read()
{
	char c=getchar();
	int s=0;
	while(c>'9'||c<'0')
	c=getchar();
	while(c>='0'&&c<='9')
	{
		s=s*10+c-'0';
		c=getchar();
	}
	return s;
}
struct nodee{
	int kind;
	int fa;
	int l,r;
	bool num;
	bool ch;
	int jl;
}a[1000007];
inline int build(int i)
{
	a[i].jl=-1;
	if(a[i].kind==5)
	return a[i].num;
	if(a[i].kind==1)
	{
		a[i].num=build(a[i].l)&build(a[i].r);
		if(a[a[i].l].num==1&&a[a[i].r].num==1)
		{
			a[a[i].l].ch=a[a[i].r].ch=1;
		}
		else if(a[a[i].l].num==0&&a[a[i].r].num==1)
		{
			a[a[i].l].ch=1;
		}
		else if(a[a[i].l].num==1&&a[a[i].r].num==0)
		{
			a[a[i].r].ch=1;
		}
		return a[i].num;
	}
	if(a[i].kind==2)
	{
		a[i].num=build(a[i].l)^build(a[i].r);
		a[a[i].l].ch=a[a[i].r].ch=1;
		return a[i].num;
	}
	if(a[i].kind==3)
	{
		a[i].num=!build(a[i].l);
		a[a[i].l].ch=1;
		return a[i].num;
	}
	a[i].num=build(a[i].l)|build(a[i].r);
	if(a[a[i].l].num==0&&a[a[i].r].num==0)
	{
		a[a[i].l].ch=a[a[i].r].ch=1;
	}
	else if(a[a[i].l].num==0&&a[a[i].r].num==1)
	{
		a[a[i].r].ch=1;
	}
	else if(a[a[i].l].num==1&&a[a[i].r].num==0)
	{
		a[a[i].l].ch=1;
	}
	return a[i].num;
}
inline bool findd(int i)
{
	if(a[i].jl!=-1)
	return a[i].jl;
	if(i==1)
	return 1;
	if(a[i].ch==1)
	{
		if(findd(a[i].fa))
		{
			a[i].jl=1;
			return 1;
		}
		else
		{
			a[i].jl=0;
			return 0;
		}
	}
	else
	{
		a[i].jl=0;
		return 0;
	}
}
int main()
{
	n=read();
	char c;
	a[1].fa=-1;
	for(register int i=1;i<=n;i++)
	{
		c=getchar();
		if(c=='A')
		{
			a[i].kind=1;
			a[i].l=read();
			a[i].r=read();
			a[a[i].l].fa=i;
			a[a[i].r].fa=i;
		}
		else if(c=='I')
		{
			a[i].kind=5;
			a[i].num=read();
			lev++;
			le[lev]=i;
		}
		else if(c=='X')
		{
			a[i].kind=2;
			a[i].l=read();
			a[i].r=read();
			a[a[i].l].fa=i;
			a[a[i].r].fa=i;
		}
		else if(c=='N')
		{
			a[i].kind=3;
			a[i].l=read();
			a[a[i].l].fa=i;
		}
		else
		{
			a[i].kind=4;
			a[i].l=read();
			a[i].r=read();
			a[a[i].l].fa=i;
			a[a[i].r].fa=i;
		}
	}
	build(1);
	for(register int i=1;i<=lev;++i)
	{
		printf("%d",findd(le[i])^a[1].num);
	}
	return 0;
}
```
~~然而对于某T3还是不会把一个字符串处理成一棵树~~

---

