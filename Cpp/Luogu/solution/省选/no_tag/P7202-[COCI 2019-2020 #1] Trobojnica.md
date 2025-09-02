# [COCI 2019/2020 #1] Trobojnica

## 题目描述

> "Everything will be in flames once red, white, and blue start running through your veins." - Slaven Bilić

在该任务中，我们将会研究一些多边形，它们具有 $N$ 条被涂成颜色的边（总共有三种颜色），而顶点的编号沿顺时针依次为 $1$ 至 $N$。

你的任务是找到一个多边形的三角形分割方式，即将一个多边形沿对角线分成 $N-2$ 个三角形，使得多边形的每个三角形的三条邻边都各分别为三种不同的颜色。

## 说明/提示

#### 数据范围及约定

| Subtask | 分值 | 数据范围及约定 |
| :----------: | :----------: | :----------: |
| $1$ | $20$ | $4 \le N \le 11$ |
| $2$ | $40$ | $4 \le N \le 10^3$ |
| $3$ | $50$ | $4 \le N \le 2 \times 10^5$ |

#### 说明

**本题分值按 COCI 原题设置，满分 $110$。**

本题使用非官方的 [Special Judge](https://www.luogu.com.cn/paste/wxx1bxs2)，欢迎大家 hack（可私信或直接发帖）。

**题目译自 [COCI2019-2020](https://hsin.hr/coci/archive/2019_2020/) [CONTEST #1](https://hsin.hr/coci/archive/2019_2020/contest1_tasks.pdf)  _T4 Trobojnica_ 。**

## 样例 #1

### 输入

```
4
1212```

### 输出

```
DA
1 3 3```

## 样例 #2

### 输入

```
4
1213```

### 输出

```
NE```

## 样例 #3

### 输入

```
7
1223121```

### 输出

```
DA
1 3 3
3 5 1
5 7 3
7 3 2```

# 题解

## 作者：Ecrade_ (赞：1)

首先，当各边颜色均相同时显然无解。接下来仅考虑存在颜色不同的边的情况。

考虑两条相邻且颜色不同的边，用一条剩余颜色的边与之形成一个三角剖分，可使原 $n$ 边形的剖分问题化归为一个 $n-1$ 边形的剖分问题。

那么可将题意转化为：每次选择两条相邻且颜色不同的边，将其合并为一条剩余颜色的边，直到剩余三条边为止，求一种可行的操作序列。

接下来我们断言，若给出的 $n$ 条边的颜色的异或和为 $0$ 则有解，反之无解。

证明：注意到上述合并操作可用异或表述（如颜色 1 与颜色 3 合并为颜色 2 可视为 1 与 3 合并为它们的异或和，即 2），每次合并后剩余所有边的异或和不变。根据题意，最终剩余三条边的颜色必然是 1,2,3 各一种，它们的异或和为 $0$，故若有解，初始所有边颜色的异或和亦需为 $0$。

下面对满足所有边颜色异或和为 $0$ 的情况进行构造。

我们开一个栈来维护当前未被合并的所有边，先将第一条边压入栈。

记最后一个与第 $n$ 条边颜色不同的边为第 $pos$ 条边。依次遍历 $2\sim pos$ 的每条边，记当前遍历到了第 $i$ 条边，其颜色为 $c_i$。若 $c_i$ 与栈顶边的颜色相同，则将 $i$ 压入栈；否则将 $i$ 不断与栈顶边合并并弹出栈顶边，直到栈空，最后将 $i$ 压入栈。特殊地，当 $i=pos$ 时，我们需要保证最终栈的大小不少于 $2$，即合并的过程中不能将栈弹空。

最终，我们可以证明，所有未被合并的边一定形如 $abcc\dots c$ 或者 $aa\dots abb\dots b$。对于第一种情况，将 $b$ 不断与右边的 $c$ （除了最后一个）合并即可；对于第二种情况，将最右边的 $a$ 不断与 $b$ （除了最后一个）合并，再将其不断与左边的 $a$ （除了第一个）合并即可。

时间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,tp,sum,cur,pos,stk[200009];
char s[200009];
inline ll read(){
	ll s = 0,w = 1;
	char ch = getchar();
	while (ch > '9' || ch < '0'){ if (ch == '-') w = -1; ch = getchar();}
	while (ch <= '9' && ch >= '0') s = (s << 1) + (s << 3) + (ch ^ 48),ch = getchar();
	return s * w;
}
int main(){
	n = read(),scanf("%s",s + 1);
	for (ll i = 1;i <= n;i += 1) sum ^= s[i] - '0';
	if (sum){
		puts("NE");
		return 0;
	}
	for (ll i = n - 1;i >= 1;i -= 1){
		if (s[i] ^ s[i + 1]){
			pos = i;
			break;
		}
	}
	if (!pos){
		puts("NE");
		return 0;
	}
	puts("DA");
	stk[++ tp] = 1,cur = s[1] - '0';
	for (ll i = 2;i <= pos;i += 1){
		if (s[i] - '0' == cur){
			stk[++ tp] = i;
			continue;
		}
		ll tmp = cur;
		cur = s[i] - '0';
		while (tp > (i == pos)){
			cur ^= tmp;
			printf("%lld %lld %lld\n",stk[tp --],i + 1,cur);
		}
		tp += 1;
		if (i == pos && tp == 2) stk[tp] = i;
	}
	for (ll i = pos + 2;i <= n;i += 1){
		cur ^= s[n] - '0';
		printf("%lld %lld %lld\n",stk[tp],i,cur);
	}
	ll tmp = cur ^ (s[n] - '0');
	for (ll i = tp - 1;i >= 2;i -= 1){
		cur ^= tmp;
		printf("%lld %lld %lld\n",stk[i],n,cur);
	}
	return 0;
}
```


---

## 作者：DengDuck (赞：0)

调了一上午随机化也是神人了。

现在来看看正解。

首先如果所有数字异或和不为 $0$ 肯定是输输输。

然后接下来我们思考如果数字异或和为 $0$，我们咋样会输呢？显然是所有数字都一样了。

仔细思考我们发现可以通过构造，保证在我们的操作过程中永远有数字不一样就行了。

因此，我们可以一直找合法的操作，如果操作之后所有颜色都会变得一样我们就不选，否则就选，我的做法是随机选边，不过直接选前面的也是对的，这样本质上就跟隔壁的 $\mathcal O(n)$ 一致了。

不难发现会让所有颜色变得一样的边最多之后一条，于是做完了。

事实上跑一轮就可以确定有无解了，但是我一开始只想着随机化卡时所以没想啥。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define pII pair<int,int>
#define Fi first
#define Se second
#define pb push_back
const int N=2e5+5;
const int Inf=1e9;
int n,A[N],C[N],Nxt[N],Lst[N],Vis[N];
mt19937 Rnd(time(0));
struct Line
{
	int P,X,Y;
	bool operator<(const Line&A)const{return P<A.P;}
};
inline bool Work()
{
	int Cnt[4]={0,0,0,0};
	priority_queue<pII>Q;
	for(int i=0;i<n;i++)Vis[i]=0,C[i]=A[i],Nxt[i]=i+1,Lst[i]=i-1;
	Nxt[n-1]=0,Lst[0]=n-1;
	for(int i=0;i<n;i++)
	{
		C[i]=A[i],Cnt[C[i]]++;
		if(C[i]!=C[Nxt[i]])Q.push({Rnd(),i});
	}
	vector<Line>Ans;
	for(int i=1;i<=n-3;i++)
	{
		if(Q.empty())return false;
		int x=Q.top().Se;Q.pop();
		int P=-1;
		while(!Q.empty()&&(C[x]==C[Nxt[x]]||Vis[x]||(Cnt[C[x]]==1&&Cnt[C[Nxt[x]]]==1)))
		{
			if(Cnt[C[x]]==1&&Cnt[C[Nxt[x]]]==1)P=x;
			x=Q.top().Se;
			Q.pop();
		}
		if(Q.empty())return false;
		Ans.pb({C[x]^C[Nxt[x]],x,Nxt[Nxt[x]]});
		Vis[Nxt[x]]=1;
		Cnt[C[x]]--,Cnt[C[Nxt[x]]]--;
		C[x]=C[x]^C[Nxt[x]],Nxt[x]=Nxt[Nxt[x]],Lst[Nxt[x]]=x;
		Cnt[C[x]]++;
		if(C[x]!=C[Nxt[x]])Q.push({Rnd(),x});
		if(C[Lst[x]!=C[x]])Q.push({Rnd(),Lst[x]});
		if(P!=-1)Q.push({Rnd(),P});
	}
	puts("DA");
	for(Line i:Ans)
	{
		printf("%d %d %d\n",i.X+1,i.Y+1,i.P);
	}
	return true;
}
int main()
{
	scanf("%d",&n);
	int Sum=0;
	for(int i=0;i<n;i++)
	{
		scanf("%1d",&A[i]);
		Sum^=A[i];
	}
	if(Sum)return puts("NE"),0;
	while(clock()<1.8*CLOCKS_PER_SEC)
	{
		if(Work())return 0;
	}
	puts("NE");
}
```

---

## 作者：DeepSeaSpray (赞：0)

# LGP7202 [COCI2019-2020#1] Trobojnica

参考了各路题解。

首先如果一个多边形全部都是一种颜色显然无法分割。

又，我们注意到 $1 \oplus 2 \oplus 3 = 0$。

故一个符合条件的三角形三边颜色异或和为 $0$。

故一个多边形的颜色异或和必须为 $0$ 才能有解。

让我们考虑一次在多边形上分割三角形操作带来的影响，这会使得两种不同颜色的边数量减少 $1$，另一种颜色的边数量增加 $1$，不影响颜色异或和。

考虑我们每一次都只选择两条颜色不一样且数量都不为 $1$ 的边合并。

首先这是一定可以做到的（比较显然）。

然后因为这样分割我们一定不会使得多边形的边都变成同一种颜色（比较显然），又颜色异或和恒为 $0$，所以我们一定可以分割这个多边形。

我们考虑不断查找第一个符合上述合并条件的边，然后与其下一条边合并。

合并完之后，它可能和它的下一条边可以继续合并，所以在上一次操作的位置继续找下去即可。

这样扫在第一次的时候可能有些边无法合并，那么在第二轮扫的时候必定可以合并，否则它是永远无法合并的，这与我们的题设矛盾。

所以一条边最多只会被扫描两次，时间复杂度是 $O(n)$ 的。

可以结合代码思考。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5;
int n;
char s[maxn+5];
int cnt[5],sum;
int nxt[maxn+5],col[maxn+5];
int ansx[maxn+5],ansy[maxn+5],ansc[maxn+5];
signed main(){
	scanf("%d",&n);
	scanf("%s",s);
	for(int i=0;i<n;i++){
		nxt[i]=(i+1)%n;
		col[i]=s[i]-'0';
		cnt[col[i]]++;
		sum^=col[i];
	}
	int x=0,y;
	if(cnt[1]==n||cnt[2]==n||cnt[3]==n||sum){
		puts("NE");
		return 0;
	}
	for(int t=0;t<n-3;t++){
		for(;col[x]==col[nxt[x]]
			||(cnt[col[x]]==1&&cnt[col[nxt[x]]]==1);x=nxt[x]);
		y=nxt[x];
		cnt[col[x]]--;
		cnt[col[y]]--;
		cnt[col[x]^col[y]]++;
		nxt[x]=nxt[y];
		col[x]=col[x]^col[y];
		ansx[t]=x;
		ansy[t]=nxt[x];
		ansc[t]=col[x];
	}
	puts("DA");
	for(int t=0;t<n-3;t++)
		printf("%d %d %d\n",ansx[t]+1,ansy[t]+1,ansc[t]);
	return 0;
}
```

---

