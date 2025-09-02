# Rainbow Coins

## 题目描述

Carl 有 $n$ 枚不同颜色的硬币，他想要将这些硬币分成若干堆。硬币编号为 $1,2,\ldots,n$，每枚硬币的颜色恰好为红色、绿色或蓝色中的一种。他希望将硬币分成三堆，使得一堆包含所有红色硬币，一堆包含所有绿色硬币，一堆包含所有蓝色硬币。

不幸的是，Carl 是色盲，所以他无法完成这个任务。幸运的是，他有一个朋友可以帮忙判断一对硬币是否颜色相同。借助朋友的帮助，Carl 认为他可以完成硬币的分类。堆的顺序无关紧要，只要同色硬币都在同一堆，不同色的硬币不在同一堆即可。

他的朋友会批量回答关于多对硬币的问题，并且会并行地回答所有这些对。每一批中，每枚硬币最多只能出现在一对中。同一枚硬币可以出现在不同的批次中。

Carl 最多只能使用 $7$ 批来完成分类。请你帮助他在分类后找出每一堆的硬币。

## 说明/提示

例如，有三个测试用例。

在第一个测试用例中，有三枚硬币。我们分别询问 $(1,2)$、$(2,3)$ 和 $(1,3)$，得到它们颜色都相同。因此，我们知道所有硬币颜色相同，可以将它们全部放在一堆。注意有些堆可以为空，用空行表示。

在第二个测试用例中，仍有三枚硬币。这次只有 $(1,3)$ 颜色相同，$(1,2)$ 和 $(2,3)$ 颜色不同。此时，一种可能的情况是硬币 $1$ 和 $3$ 是红色，硬币 $2$ 是绿色。

在最后一个测试用例中，有 $6$ 枚硬币。该用例展示了如何在一批中询问多对硬币并获得答案。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
3
1
1
1
3
1
0
0
6
000
010
100
001
000
```

### 输出

```
Q 1 1 2
Q 1 2 3
Q 1 1 3
A 3 0 0
1 2 3


Q 1 1 3
Q 1 2 3
Q 1 1 2
A 2 0 1
1 3

2
Q 3 1 2 3 4 5 6
Q 3 1 3 2 5 4 6
Q 3 1 4 2 6 3 5
Q 3 1 5 2 4 3 6
Q 3 1 6 2 3 4 5
A 2 2 2
1 4
2 5
3 6```

# 题解

## 作者：DJRzjl (赞：5)

# [CF1147E](https://www.luogu.com.cn/problem/CF1147E)  Rainbow Coins

我们只能询问 $7$ 次，$n$ 的大小应该基本与询问次数无关，所以我们必须要使分组能充分利用信息，从而容易想到较为简单的两种分组询问方式：

1. 询问 $[1~2]~~[3~4]~~[5~6]~\cdots~[2k-1~2k]$；
2. 询问 $[2~3]~~[4~5]~~[6~7]~\cdots~[2k~2k+1]$​。

上面两次询问已经涵盖了所有相邻的位置，于是我们可以把相邻的同种颜色的用并查集缩到一起，得到了若干不同颜色段，而每段内部是同种颜色。

相邻段之间一定是不同颜色，所以我们需要确定隔一段的两个颜色段的颜色关系，用 $A~B~C\cdots$ 来表示不同的颜色段，考虑询问：

1. 询问 $[A~C]~~[D~F]~~[G~I]\cdots$​；
2. 询问 $[B~D]~~[E~G]~~[H~J]\cdots$​；
3. 询问 $[C~E]~~[F~H]~~[I~K]\cdots$。

这里询问段与段之间取个代表元素即可，最后我们可以知道任意三个相邻的颜色段两两之间之间的关系，以最前面的 $A~B~C$​​ 三段为例：

因为只有三种颜色，并且最后答案顺序无所谓，不妨令 $Col_A=1,Col_B=2$​ ：

- 首先一定有 $Col_A \not= Col_B,Col_B \not=Col_C$
- 若 $Col_A =Col_C$​​​​，则 $Col_C=1$​​​；
否则，$Col_C\not=1$​​​ 且 $Col_C \not= 2$​​​，所以 $Col_C=3$​​​。

于是我们就可以通过 $B~C~D$ 的关系推出 $Col_D$，进而用类似的方式推出所有段的颜色，也就知道了所有位置的颜色，总共使用了 $5$ 次询问。

## Code
```cpp
#include<bits/stdc++.h>
#define pb push_back
#define mkr make_pair
using namespace std;
const int N=1e5+10;

int T,n;
vector<pair<int,int> >q;
vector<bool>res;
char str[N];

void ask(){
	if(!(int)q.size()) return ;
	res.clear();
	printf("Q %d",(int)q.size());
	for(auto v:q) printf(" %d %d",v.first,v.second);
	putchar('\n');
	fflush(stdout);
	scanf("%s",str);
	for(int i=0;i<(int)q.size();i++) res.pb(str[i]-'0');
	q.clear();
}
struct Dsu{
	int fa[N],siz[N];
	void prepare(int n){for(int i=1;i<=n;i++) fa[i]=i,siz[i]=1;}
	inline int find(int x){return (x==fa[x])?x:find(fa[x]);}
	void merge(int x,int y){
		int fx=find(x),fy=find(y);
		if(fx==fy) return ;
		if(siz[fx]>siz[fy]) swap(fx,fy);
		fa[fx]=fy,siz[fy]+=siz[fx];
	}
}d;
int pos[N],cnt,col[N];
int pre[N];
vector<int>ans[3];

int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		d.prepare(n);
		cnt=0;
		ans[0].clear(),ans[1].clear(),ans[2].clear();
		for(int i=1;i<n;i+=2) q.pb(mkr(i,i+1));
		ask();
		for(int i=1,j=0;i<n;i+=2,j++) if(res[j]) d.merge(i,i+1);
		for(int i=2;i<n;i+=2) q.pb(mkr(i,i+1));
		ask();
		for(int i=2,j=0;i<n;i+=2,j++) if(res[j]) d.merge(i,i+1);
		
		for(int i=1;i<=n;i++) if(i==d.find(i)) pos[++cnt]=i;

		for(int i=1;i+2<=cnt;i+=3) q.pb(mkr(pos[i],pos[i+2]));
		ask();
		for(int i=1,j=0;i+2<=cnt;i+=3,j++) pre[i+2]=res[j];
		for(int i=2;i+2<=cnt;i+=3) q.pb(mkr(pos[i],pos[i+2]));
		ask();
		for(int i=2,j=0;i+2<=cnt;i+=3,j++) pre[i+2]=res[j];
		for(int i=3;i+2<=cnt;i+=3) q.pb(mkr(pos[i],pos[i+2]));
		ask();
		for(int i=3,j=0;i+2<=cnt;i+=3,j++) pre[i+2]=res[j];

		col[pos[1]]=0,col[pos[2]]=1;
		for(int i=3;i<=cnt;i++)
			if(pre[i]==0) col[pos[i]]=3-col[pos[i-1]]-col[pos[i-2]];
			else col[pos[i]]=col[pos[i-2]];
		for(int i=1;i<=n;i++) ans[col[d.find(i)]].push_back(i);

		printf("A %d %d %d\n",(int)ans[0].size(),(int)ans[1].size(),(int)ans[2].size());
		for(int v:ans[0]) printf("%d ",v);
		putchar('\n');
		for(int v:ans[1]) printf("%d ",v);
		putchar('\n');
		for(int v:ans[2]) printf("%d ",v);
		putchar('\n');
		fflush(stdout);
	}
	return 0;
}
```



---

## 作者：是个汉子 (赞：4)

[洛谷传送门](https://www.luogu.com.cn/problem/CF1147E)	[CF传送门](http://codeforces.com/problemset/problem/1147/E)

### 题意

有 $n$ 个硬币，每个硬币有一种颜色，是R，G，B中的一种。可以选择两个硬币进行询问颜色是否一样，每次可以同时询问若干对硬币（一个硬币不能同时属于两对）。最多7次询问，将硬币分为颜色不同的三组。

### Solution

这是个思维很棒的交互题。

我们可以先询问两次：

1.第一次询问 $2i-1,2i\rightarrow 1 2|3 4|56 |\cdots$ 

2.第二次询问 $2i,2i+1\rightarrow 23|45|67|\cdots$ 

这样做可以得到两边相邻的颜色是否一样。

如果一样，就将他们合并。设合并完用 $now$ 表示，那么此时对于 $now_i$ ， $now_{i-1},now_{i+1}$ 和它的颜色都不一样。

 但是 $now_{i-1},now_{i+1}$ 之间的关系我们还不知道，所以还要询问两次：

1.第三次询问 $now_{i-2},now_{i}$ 

2.第四次询问 $now_i,now_{i+2}$ 

此时我们对于所有硬币之间的关系就都知道了，然后扫一遍求答案即可

### Code

```c++
#include<bits/stdc++.h>
#define PII pair<int,int>

using namespace std;
const int N=100010;
int T,n,cnt,now[N],ans[N];
char ch[N];
vector<int>A,B,C;
map<PII,bool>col;

inline void ask(){
    if(!A.size()) return ;
    printf("Q %d ",(int)A.size());
    for(int i=0;i<A.size();i++) printf("%d %d ",A[i],B[i]);
    puts("");
    fflush(stdout);
    scanf("%s",ch+1);
    for(int i=0;i<A.size();i++) col[make_pair(A[i],B[i])]=(ch[i+1]=='1');
}

int main(){
    scanf("%d",&T);
    while(T--){
        cnt=0;col.clear();
        memset(ans,0,sizeof(ans));
        scanf("%d",&n);
        A.clear();B.clear();
        for(int i=2;i<=n;i+=2){
            A.push_back(i-1);
            B.push_back(i);
        }
        ask();
        A.clear();B.clear();
        for(int i=3;i<=n;i+=2){
            A.push_back(i-1);
            B.push_back(i);
        }
        ask();
        now[++cnt]=1;
        for(int i=2;i<=n;i++)
            if(!col[make_pair(i-1,i)]) now[++cnt]=i;
        A.clear();B.clear();
        for(int i=3;i<=cnt;i+=4) A.push_back(now[i-2]),B.push_back(now[i]);
        for(int i=4;i<=cnt;i+=4) A.push_back(now[i-2]),B.push_back(now[i]);
        ask();
        A.clear();B.clear();
        for(int i=3;i<=cnt-2;i+=4) A.push_back(now[i]),B.push_back(now[i+2]);
        for(int i=4;i<=cnt-2;i+=4) A.push_back(now[i]),B.push_back(now[i+2]);
        ask();
        ans[now[1]]=1;
        if(cnt>1) ans[now[2]]=2;
        for(int i=3;i<=cnt;i++){
            if(col[make_pair(now[i-2],now[i])]) ans[now[i]]=ans[now[i-2]];
            else ans[now[i]]=6-ans[now[i-2]]-ans[now[i-1]];
        }
        A.clear();B.clear();C.clear();
        for(int i=1,t;i<=n;i++){
            if(ans[i]) t=ans[i];
            ans[i]=t;
            if(ans[i]==1) A.push_back(i);
            else if(ans[i]==2) B.push_back(i);
            else if(ans[i]==3) C.push_back(i);
        }
        printf("A %d %d %d\n",(int)A.size(),(int)B.size(),(int)C.size());
        for(int i=0;i<A.size();i++) printf("%d ",A[i]);
        puts("");
        for(int i=0;i<B.size();i++) printf("%d ",B[i]);
        puts("");
        for(int i=0;i<C.size();i++) printf("%d ",C[i]);
        puts("");
        fflush(stdout);
    }
}
```



---

## 作者：_LHF_ (赞：3)

显然可以四次询问解决。

具体的，我们看我们能够干什么，我们能够花费两次询问把同色连续段给拎出来。

然后考虑相邻三个连续段，如果我们知道第一个和第三个连续段是否同色，那么我们就可以直接做了。

然后我们再花费两次问出 $i,i+2$ 这两个连续段是否同色。

然后就可以四次解决问题了。

---

