# [POI 2012] BON-Vouchers

## 题目描述

Byteasar 经营着一家焦糖店。

对于所有正整数 $c$，Byteasar 都有且仅有一个装有 $c$ 个糖果的包裹。

Byteasar 准备了 $m$ 张代金券，并在装有 $b_i$ 个糖果的包裹里分别放入一张。

现在共有 $n$ 批顾客，第 $i$ 批客人有 $a_i$ 人，且每名顾客会买走装有最少糖果的包裹，满足这些糖果可平均分给这一批的 $a_i$ 个人。例如，若 $n = 2, a_1 = 4, a_2 = 8$，则第一批顾客买走的糖果数量分别为  $4, 8, 12, 16$，第二批顾客买走的糖果数量分别为 $2, 6$。

将所有顾客按顺序从 $1$ 开始编号，Byteasar 想知道取走代金券的顾客数量和各自的编号。

## 样例 #1

### 输入

```
4
1
6
8
16
3
4
2
4```

### 输出

```
3
2
4
6```

# 题解

## 作者：Alex_Wei (赞：5)

> [P3536 [POI2012]BON-Vouchers](https://www.luogu.com.cn/problem/P3536)
>
> [POI 合集](https://www.cnblogs.com/alex-wei/p/POI.html)。

注意到对于一个固定的 $x$，我们只关心前 $\dfrac {\max b_i}x$ 个需求为 $x$ 的顾客，便可断言接下来需求为 $x$ 的顾客不可能拿到代金券，这一点显然。

因此，若当前需求为 $x$ 的顾客数量 $c_x>\dfrac{\max b_i}x$，那么可以跳过剩下来所有这样的顾客。直接暴力模拟，时间复杂度是调和级数求和产生的 $\mathcal{O}(b\ln b)$，可以接受。

```cpp
const int N = 1e6 + 5;
int n, m, cnt, buc[N];
ll tot, ans[N], cur[N];
int main(){
	cin >> m;
	for(int i = 1; i <= m; i++) buc[read()] = 1;
	n = read();
	for(int i = 1; i <= n; i++) {
		int k = read();
		if(cur[k] * k >= N) {tot += k; continue;}
		int rest = k;
		while(rest) {
			int p = (++cur[k]) * k;
			if(p >= N) break;
			if(buc[p] == 1) ans[++cnt] = tot + k - rest + 1;
			if(buc[p] >= 0) buc[p] = -1, rest--;
		} tot += k;
	} cout << cnt << endl;
	for(int i = 1; i <= cnt; i++) print(ans[i]), pc('\n');
	return 0;
}
```

---

## 作者：Computer1828 (赞：2)

### 题目翻译：

有 $m$ 个幸运数，有 $n$ 群人，第 $i$ 群人有 $x_i$ 个，从小到大取走 $x_i$ 个 $x_i$ 的倍数，取过的不能再取，求那些人取走了幸运数。$m,n,x_i \leq 10^6$

### 正文：

考虑最暴力的写法，直接模拟每群人拿数的过程。在暴力过程中，我们会发现某些数被访问多次，如下面的访问顺序：

```cpp
x[1] = 4:4 8 12 16
x[2] = 4:(4 8 12 16) 20 24 28 32
```

我们会注意到某些数访问了多次，所以优化就是记录 `lst[i]` 表示上次数 $i$ 最后取的数是什么。在上面那个例子中，进行完第一行后 `lst[4] = 16`。

复杂度大概是 $O(n\log n)$，注意人编号可能爆 `int`。

```cpp
#include<bits/stdc++.h>
#define N 1000005
#define ll long long
using namespace std;
int n,m,cnt,lst[N];
bool vis[N],get[N];
ll ans[N],np;
int main(){
	scanf("%d",&m);
	int x;
	for(int i = 1;i<=m;++i){
		scanf("%d",&x);
		vis[x] = true;
	}
	scanf("%d",&n);
	get[0] = true;
	for(int i = 1;i<=n;++i){
		scanf("%d",&x);
		int tmp = lst[x],j;
		for(j = x;j>=1;--j){
			while(tmp<=N-5 && get[tmp]) tmp += x,lst[x] = tmp;
			if(tmp > N-5) break;
			get[tmp] = true;
			np++;
			if(vis[tmp]) ans[++cnt] = np;
		}
		np += j;
	}
	printf("%d\n",cnt);
	for(int i = 1;i<=cnt;++i) printf("%lld\n",ans[i]);
	return 0;
}
```

---

## 作者：神阈小杰 (赞：1)

前前后后大改小改共提交了6次，发篇题解纪念一下。

代码已经解释清楚了，就直接上代码。

注：客人的编号要用long long类型，不然会炸
```cpp
# include <cstdio>
# include <cstring> 
int m;//代金券数量;
int b;//放入第i张代金券的包裹中的糖果数量;
int maxe;//放入代金券的包裹中最多的糖果数量;
int pan[1000010];//判断有i个糖果的包裹中是否有代金卷,该包裹是否被取走;
//-1为未被取走但没有代金卷,0为已被取走,1为未被取走且有代金卷;
int n;//购物狂欢节的天数;
int a;//a为购物狂欢节第i天的客人数量;
long long last[1000010];//last[i]记录当前客人人数为i的最后一个买的包裹的糖果数量;
long long ji;//客人的编号;
long long ans_s;//被售出的含代金卷的包裹的数量;
long long ans[1000010];//买走含代金卷的包裹的客人的编号;
int main()
{
	memset(pan,-1,sizeof(pan));
	pan[0]=0;
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&b);
		pan[b]=1;
		if(b>maxe) maxe=b;
	}
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a);
		last[a]+=a;
		if(last[a]>maxe)
		{
			ji+=a;
			continue;
		}
		for(int j=1;j<=a;j++)
		{
			while(last[a]<=maxe&&pan[last[a]]==0) last[a]+=a;
			if(last[a]>maxe) break;
			if(pan[last[a]]==1)
			{
				ans_s++;
				ans[ans_s]=ji+j;
			}
			pan[last[a]]=0;
		}
		ji+=a;
	}
	printf("%lld\n",ans_s);
	for(int i=1;i<=ans_s;i++) printf("%lld\n",ans[i]);
	return 0;
}
```

---

## 作者：lightup37 (赞：0)

### 「POI2012」BON-Vouchers 题解

建议管理员修一下翻译... 太乱了

~~我觉得我下面简述的题意用来当翻译就挺好 /cy~~

#### 题意

设$n$个数$a_i$为好的数.  有$m$天, 每天有$k_i$个人. 第$i$天这些人会取走所有最小的$k_i$个是$k_i$倍数且没有被取走的数. 如果这种数的个数小于等于$k_i$, 则只会将这种数全部取走. 问哪些人取到了好的数, 人的编号是$1\sim \sum\limits_{i=1}^{m} k_i+1$. $n\leq 10^6$.

#### 解法

注意到$\sum\limits_{i=1}^{n} \frac{n}{i} = nH_n \in \mathcal{O}(n\log n)$, 因此我们记录一个数组$x_i$表示上一次参数为$i$时最后取走的那个数, 第$i$天从$x_{k_i}$开始枚举. 这样可以保证不会重复枚举, 故时间复杂度是$\mathcal{O}(n\log n)$.

#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std; /*Copyright [tyqtyq](http://oiertyq.github.io). All rights served.*/
#define f(i,x,y) for(int i=x,i##end=y;i<=i##end;++i)
#define d(i,x,y) for(int i=x,i##end=y;i>=i##end;--i)
#define ri register int
#define ll long long
#define il inline
#define _ 1000005
#define int long long
namespace intio{char ch; int read(){ ri x=0,f=1; while(!isdigit((ch=getchar()))) f=ch=='-'?-1:1; while(isdigit(ch)) x=x*10+ch-'0', ch=getchar(); return x*f; } void read(int& x) {x = read();}}; using namespace intio;
int max(int x, int y) {return x>y?x:y;} int min(int x, int y) {return x<y?x:y;}
int m, n, num[_], a[_], mx, vis[_], lst[_];
int top, ans[_], now ;
signed main(){
	read(m);
	f(i,1,m) num[read()]=1;
	read(n); mx = _-5 ; vis[0] = 1;
	while(n--){
		int x = read();
		int &t = lst[x], j = x;
		for(; j; --j){
			while(t<=mx && vis[t]) t += x;
			if(t>mx) break;
			vis[t] = 1; ++now;
			if(num[t]) ans[++top]=now;
		}
		now += j;
	}
	cout<<top<<endl;
	f(i,1,top) cout<<ans[i]<<endl;
	return 0;
}
```

---

## 作者：kczno1 (赞：0)

10^6的范围，再考虑到n/1+n/2+..n/n=nlogn，

只要把同样的数单调的枚举倍数，就可以暴力模拟了。

```cpp
#include<cstdio>

#define ll long long
#define N 1000000
bool vis[N+5],is[N+5];
int last[N+5];
int top;ll now,ans[N+5];

int main()
{
    freopen("1.in","r",stdin);freopen("1.out","w",stdout);
    int n,x;scanf("%d",&n);
    while (n--)  { scanf("%d",&x);is[x]=1; }
    scanf("%d",&n);
    vis[0]=1;
    while (n--)
    {
        scanf("%d",&x);
        int &i=last[x],j=x;
        for (;j;--j)
        {
            while (i<=N&&vis[i]) i+=x;
            if(i>N)break; 
            vis[i]=1;++now;
            if (is[i]) ans[++top]=now;
        }
        now+=j;
    }
    printf("%d\n",top); 
    for (x=1;x<=top;++x) printf("%lld\n",ans[x]);
}
```

---

