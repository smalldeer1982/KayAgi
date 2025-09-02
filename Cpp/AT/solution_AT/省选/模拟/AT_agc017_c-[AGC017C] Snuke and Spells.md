# [AGC017C] Snuke and Spells

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc017/tasks/agc017_c

$ N $ 個のボールが一列に並んでいます． 左から $ i $ 番目のボールには，最初整数 $ A_i $ が書かれています．

すぬけ君が魔法を唱えると，これらのボールは次のようにして消滅します：

- ボールがちょうど $ k $ 個あるとき，$ k $ が書かれているボールすべてが同時に消滅する．

すぬけ君の目標は，魔法を何回か唱えることでボールをすべて消滅させることです． これは不可能な場合があるので，すぬけ君はできるだけ少ない個数のボールに書かれている整数を変更することで，この目標を達成できるようにしたいです．

これらのボールは，書かれている整数が全部で $ M $ 回自然に変化することがわかっています． $ j $ 回目の変化においては，左から $ X_j $ 番目のボールに書かれている整数が $ Y_j $ に変わります．

各変化の後の状態で，次の変化が起こる前にすぬけ君が目標を達成しようとするとき，少なくとも何個のボールに書かれている整数を変更する必要があるかを求めてください．すぬけ君は整数の変更を十分速く行うことができるものとします．ただし，すぬけ君は実際には整数の変更を行わないことに注意してください．

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 200000 $
- $ 1\ \leq\ M\ \leq\ 200000 $
- $ 1\ \leq\ A_i\ \leq\ N $
- $ 1\ \leq\ X_j\ \leq\ N $
- $ 1\ \leq\ Y_j\ \leq\ N $

### 部分点

- $ 500 $ 点分のテストケースでは，$ N\ \leq\ 200 $ および $ M\ \leq\ 200 $ が成り立つ．

### Sample Explanation 1

\- $ 1 $ 回目の変化の後，ボールに書かれている整数は左のボールから順に $ 2,\ 1,\ 3,\ 4,\ 5 $ になります．この状態ですぬけ君が $ 5 $ 回魔法を唱えると，すべてのボールが消滅します．そのため，$ 0 $ 個のボールに書かれている整数を変更すればよいです． - $ 2 $ 回目の変化の後，ボールに書かれている整数は左のボールから順に $ 2,\ 5,\ 3,\ 4,\ 5 $ になります．この場合，少なくとも $ 1 $ 個のボールに書かれている整数を変更する必要があります．例えば，左から $ 5 $ 番目のボールに書かれている整数を $ 2 $ に変更した後，すぬけ君が $ 4 $ 回魔法を唱えればよいです． - $ 3 $ 回目の変化の後，ボールに書かれている整数は左のボールから順に $ 2,\ 5,\ 3,\ 4,\ 4 $ になります．この場合，少なくとも $ 1 $ 個のボールに書かれている整数を変更する必要があります．例えば，左から $ 3 $ 番目のボールに書かれている整数を $ 2 $ に変更した後，すぬけ君が $ 3 $ 回魔法を唱えればよいです．

## 样例 #1

### 输入

```
5 3
1 1 3 4 5
1 2
2 5
5 4```

### 输出

```
0
1
1```

## 样例 #2

### 输入

```
4 4
4 4 4 4
4 1
3 1
1 1
2 1```

### 输出

```
0
1
2
3```

## 样例 #3

### 输入

```
10 10
8 7 2 9 10 6 6 5 5 4
8 1
6 3
6 2
7 10
9 7
9 9
2 4
8 1
1 8
7 7```

### 输出

```
1
0
1
2
2
3
3
3
3
2```

# 题解

## 作者：小粉兔 (赞：14)

在博客园食用更佳：[https://www.cnblogs.com/PinkRabbit/p/AGC017.html](https://www.cnblogs.com/PinkRabbit/p/AGC017.html)。

一个很精妙的性质：

- 考虑数轴上的 $N$ 个坐标 $1 \sim N$。每个坐标上都有绳子，一开始长度均为 $0$。
- 对于每个颜色 $A_i = k$ 的 $i$ 号球，在坐标 $k$ 上多挂 $1$ 单位长度的绳子。
- 最后把每个坐标上的绳子向左（负方向）拉直。
- 如果绳子覆盖了 $[0, N]$，则一定可以通过施法让所有球消失。
- 而如果不能让所有球消失，在 $[0, N]$ 中未被覆盖的总长度，就是需要修改颜色的球数，也就是答案。

此结论可以感性理解。

由此我们先开桶统计，然后做后缀和，然后对于每个询问我们可以在桶里查询，修改每个 $[i - 1, i]$ 被覆盖的次数。

每个询问是 $\mathcal O (1)$ 的，可以做到 $\mathcal O (N + Q)$ 的复杂度。

```cpp
#include <cstdio>

const int MN = 200005;

int N, Q, A[MN], C[MN], _S[MN * 2], *S = _S + MN, Ans;

int main() {
	scanf("%d%d", &N, &Q);
	for (int i = 1; i <= N; ++i) scanf("%d", &A[i]), ++C[A[i]];
	for (int i = 1; i <= N; ++i) ++S[i], --S[i - C[i]];
	for (int i = N; i >= -N; --i) S[i] += S[i + 1], Ans += i > 0 && !S[i];
	while (Q--) {
		int p, x;
		scanf("%d%d", &p, &x);
		--C[A[p]];
		if (!--S[A[p] - C[A[p]]]) if (A[p] - C[A[p]] > 0) ++Ans;
		if (!S[x - C[x]]++) if (x - C[x] > 0) --Ans;
		++C[x];
		A[p] = x;
		printf("%d\n", Ans);
	}
	return 0;
}
```

---

## 作者：lsj2009 (赞：2)

人类智慧题。

如果说值为 $x$ 的数出现了 $c_x$ 次，则当序列长度剩余 $x$ 时可以从 $x$ 变成 $x-c_x$，则我们考虑连一条边 $x-c_x$，那么当所有线段依次首尾相接、从 $n$ 到 $1$ 时则有解。由于线段总长为 $n$，所以等价于 $[1,n]$ 的区间被线段全部覆盖。

如果说我们执行一次 $a_i$ 从 $x$ 修改成 $y$ 的操作，则从 $x$ 的结尾的线段长度减一，从 $y$ 结尾的线段长度加一，手摸一下可以得到答案为没有被覆盖的区间长度。

至于询问的修改的话，也是易维护的，不多赘述。

```cpp
#include<bits/stdc++.h>
//#define int long long
#define ll long long
#define ull unsigned long long
#define ld long double
#define PII pair<int,int>
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define chkmax(a,b) a=max(a,b)
#define chkmin(a,b) a=min(a,b)
#define rep(k,l,r) for(int k=l;k<=r;++k)
#define per(k,r,l) for(int k=r;k>=l;--k)
#define cl(f,x) memset(f,x,sizeof(f))
using namespace std;
const int N=2e5+5;
int cnt[N],d[N],a[N];
signed main() {
    int n,q;
    scanf("%d%d",&n,&q);
    rep(i,1,n) {
        scanf("%d",&a[i]);
        ++cnt[a[i]];
    }
    rep(i,1,n)
        ++d[max(i-cnt[i]+1,1)],--d[i+1];
    int res=0;
    rep(i,1,n)
        d[i]+=d[i-1],res+=d[i]==0;
    while(q--) {
        int p,val;
        scanf("%d%d",&p,&val);
        if(a[p]-cnt[a[p]]+1>=1) {
            if(!--d[a[p]-cnt[a[p]]+1])
                ++res;
        }
        --cnt[a[p]]; a[p]=val; ++cnt[a[p]];
        if(a[p]-cnt[a[p]]+1>=1) {
            if(!d[a[p]-cnt[a[p]]+1]++)
                --res;
        }
        printf("%d\n",res);
    }
    return 0;
}
```

---

## 作者：小木虫 (赞：2)

### Preface  
聪明题，本蒟蒻当成优化 dp 看了半天...
### Problem  

$N$ 个球排在一起，每个球上有一个数 $a_i$。接下来会进行若干轮删除。设现在还有 $k$ 个球，则 $a_i=k$ 的球会被删除。

最终可能球不会被删完，你需要求出最少修改几个球上的数后可以让球全部被删完。

同时还有 $M$ 次修改，每次修改第 $X_i$ 个球的数为 $Y_i$，你需要求出每次修改后上述问题的答案。  
### Solution  
我们发现如果我们到了一个球的数量，那么接下来转移到的位置一定是现在的数量减去所有 $a_i$ 为当前数量的球数。换个说法说，我们可以把球全部按 $a$ 装桶形成一个数列。然后对于一个位置的转移，我们把桶中的球一个一个地往左边放，每次放的位置是上一次放的位置的更左一格，直到桶里只剩一个球。  

同时我们知道所有球数是恒等于 $N$ 的，所以一个可以全部删去的序列如果按上述方法摊球的话每个位置应该有且仅有一个球，因为只要一个位置多出了球，那其它地方就一定会少球。  

接下来，按照直觉我们肯定是要移动球以达成上述条件了，如果不满足条件我们就将一些地方的球移到没有球的地方。不难发现在多球地移球的操作本质相当于将一个桶内的球数减少并移到另外一个桶内（当然这个另外的桶原来可能并不存在），这个操作是不会把原来覆盖到的点取消覆盖的，因为我们肯定会尽量拿走更后面的桶的球，这时我们只会将重复覆盖的球拿走而不会拿走后面的球导致前面的球集体后移，也就是更改球的 $a$。  

这时答案就是没有球的地方总数。具体实现我在一开始用了树状数组维护差分数组预处理，之后单点修改查答案。  
code：  
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n,m;int x,y;int tree[N];
int a[N];int ans;int tot[N];int seq[N];
int lowbit(int x){return x&-x;}
void update(int x,int y){
	while(x<=n)tree[x]+=y,x+=lowbit(x);
}
int query(int x){
	int res=0;
	while(x!=0){
		res+=tree[x];x-=lowbit(x);
	}return res;
}
int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)tot[a[i]]++;
	for(int i=1;i<=n;i++){
		int l=max(1,i-tot[i]+1);int r=i;
		update(l,1);update(r+1,-1);
	}for(int i=1;i<=n;i++)seq[i]=query(i),ans+=(seq[i]==0);
	//for(int i=1;i<=n;i++)cout<<seq[i]<<endl;
	while(m--){
		cin>>x>>y;int l=0;
		l=(a[x]-tot[a[x]]+1);tot[a[x]]--;
		if(l>=1){
			seq[l]--;if(seq[l]==0)ans++;
		}
		a[x]=y;tot[a[x]]++;
		l=(a[x]-tot[a[x]]+1);
		if(l>=1){
			if(seq[l]==0)ans--;seq[l]++;
		}
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：Zhl2010 (赞：1)

一道思维题！！！

这种题想到了就做出来了，代码不长，但思维量还是有一定的，个人认为还挺好玩的。
## 题面
有 $N$ 个球，每个球上有一个数 $a_i$。接下来会进行若干轮删除。

设现在还有 $k$ 个球，则所有 $a_i=k$ 的球会被删除。

问至少需要多少次操作才能把序列删空。

## 思路
让我们充分发扬人类智慧。

首先来点抽象的，我们把数轴上的每一个点 $i$ 放上一个线段，其往左走有一些长度，长度为 $a_j=i$ 的个数。

这条线段表示从当前点能向前走到的节点，也就是当删去了这些节点，下一个需要考虑的节点。

比如这个：

```
2 2 2 5 5 8 8 8
```

首先从 $8$ 开始有一条长度为 $3$ 的序列，可以直达 $5$，然后再看 $5$，可以到 $3$，但是下一条线段是 $2$，中间就空了一个，就代表需要修改的节点。


所以可以想到，这些线段没有覆盖到的节点就是需要修改的节点。

有点抽象，但是可以感性理解，然后自己推导一下。

所以有了这些，离正解只有一步之遥，我们可以开一个桶 $t$，来存 $a_i=j$ 的个数，也就是 $t_i$ 表示 $a$ 序列中为 $j$ 的数的个数。

然后有一个后缀数组 $s$，生成方法：从 $1$ 枚举到 $n$，将 $s_i$ 赋值为 $1$，然后按照线段的定义，将 $s_{i-t_i}$ 减去$1$，在做完后缀数组之后就表示第 $i$ 位被多少条线段覆盖。

在每次修改后：

- 首先是对于将 $a_x$ 拿出的，如果 $a_{x}-t{a_x}>0$ 而且 $s_{a_{x}-t{a_x}}-1$ 为 $0$，代表修改 $x$ 会将答案增加，因为这条线段全部在 $0$ 之后，而且没有与之重合的线段，表明其拿出来线段会少覆盖一个点。

- 同理，对于将 $y$ 加进去，如果 $y-t{y}>0$ 而且 $s_{y-t{y}}-1$ 为 $0$，代表修改 $y$ 会将答案减少，因为这条线段全部在 $0$ 之后，而且没有与之重合的线段，表明其增加进去线段会多覆盖一个点。

最后我们已经维护了答案，输出就行了。

这份代码细节还是挺多的，一定要注意后缀数组的边界问题。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[200010];
int t[200010],s[400050];
int ans=0;
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		t[a[i]]++;//桶的制作
	}
	for(int i=1;i<=n;i++){
		s[i]++;
		--s[i-t[i]];//按照线段的定义入手
	}
	for(int i=n;i>=1;i--){
		s[i]+=s[i+1];
		if(i>0&&!s[i])ans++;//先统计初始答案，方便之后维护
	}
	
	for(int i=1;i<=m;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		--t[a[x]];
		if(a[x]-t[a[x]]>0)if(!(--s[a[x]-t[a[x]]]))ans++;//首先要判断是否越界
		if(y-t[y]>0)if(!s[y-t[y]]++)ans--;
		++t[y];
		a[x]=y;
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：Chenyichen0420 (赞：1)

## 思路分析

首先不考虑修改，我们发现一个合法的序列在排序后必然满足 $a_i=a_{i+1}$ 或者 $a_i=i$，并且二者不同时满足。

也就是说，这些数会形成许多右端点在 $a_i=i$ 的直线上且对应区间并集恰为 $[1,n]$ 的许多平台。

于是正解就出来了。

对于每一个数，我们统记他出现的次数。$i$ 出现了 $p_i$ 次就会对应一个覆盖 $(i-p_i,i]$ 的区间。最后再来看一下哪些点没被覆盖就完了。

你说这是 $O(nm)$ 的，我说每次只会动两个区间共 $2$ 个位置，算上预处理时间复杂度是 $O(n+m)$ 的。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, m, a[200005], t[200005], c[200005], ans;
inline void add(int p) {
	int cp = p - t[p]; t[p]++;
	if (cp > 0 && !c[cp]++) ans--;
}
inline void del(int p) { 
	t[p]--; int cp = p - t[p];
	if (cp > 0 && !--c[cp]) ans++;
}
signed main() {
	ios::sync_with_stdio(0); cin >> n >> m; ans = n;
	for (int i = 1;i <= n;++i) cin >> a[i], add(a[i]);
	for (int i = 1, x, y;i <= m;++i)
		cin >> x, del(a[x]), cin >> a[x], add(a[x]), cout << ans << endl;
}
```

---

## 作者：羊羊君的幻想 (赞：0)

神题，好题，太妙了。

------------

### Link

[题面 Link](https://www.luogu.com.cn/problem/AT_agc017_c)

[官方题解 Link](https://img.atcoder.jp/agc017/editorial.pdf)

------------

### 题意

有 $N$ 个球，每个球有一个编号 $a_i$。设当前剩余 $k$ 个球，每次操作将 $a_i=k$ 的球删除。重复执行上述操作，直到无法进行为止。问最少修改几个球的编号，使得最后 $k=0$。

多组询问，每次询问更改一个球的编号，同时输出最少修改次数。

------------
### 题解

我们定义编号为 $i$ 的球的数量为 $num_i$。

现在，我们在脑海中构建一个数轴，然后，我们在数轴上画线段，每条线段都可以表示出一类编号和对应的球的数量。画的方式如下。

对于编号 $i$，我们在数轴上找到位置为 $i$ 的点，从这点开始向左延伸画线，直到线段长度为 $num_i$，这时停止画线。对于每种编号都重复这类操作。

这样，我们便得到了若干线段，线段的右端点代表了编号，线段的长度代表了对应的球的数量。

显然，**这些线段的总长度为** $\textbf{n}$，下面两个结论都基于此：

- 最后可以正好消完就等价于这若干条线段正好首尾相接覆盖了 $[1,n]$ 这段区间。

- 最后消不完就等价于这若干条线段有几条重叠在了一起。

如果消不完，考虑最少消耗次数，就是让线段间没有重叠，根据贪心，显然最少修改次数就是等于没有被覆盖的位置的数量。

具体实现，我们可以维护数组 $c$，$c_i$ 表示坐标为 $i$ 的点被覆盖的次数。所以最少修改次数就是 $\sum \left[c_i=0\right]$。由于每次修改最多改变两条线段，所以这个数组很好维护，答案我们微调一下即可。

时间复杂度 $\mathcal{O}(n+q)$。

------------

### 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
namespace IO{
	inline int read()
	{
		int x=0,f=1;char ch=getchar();
		while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
		while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
		return x*f;
	}
}
using namespace IO;
using namespace std;
const int N=2e5+10;
int n,q;
int a[N];
int b[N];
int c[N];
signed main(){
	n=read();q=read();
	for(int i =1;i<=n;i++){
		a[i]=read();
		b[a[i]]++;
	}
	for(int i=1;i<=n;i++){
		if(b[i]){
			c[i+1]--;
			c[max(1,i-b[i]+1)]++;
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		c[i]+=c[i-1];
		ans+=(c[i]==0);
	}
	while(q--){
		int x=read(),k=read();
		if(b[a[x]]<=a[x]){
			c[a[x]-b[a[x]]+1]--;
			if(c[a[x]-b[a[x]]+1]==0) ans++;
		}
		b[a[x]]--;	
		b[k]++;
		if(b[k]<=k){
			if(c[k-b[k]+1]==0) ans--;
			c[k-b[k]+1]++;
		}
		a[x]=k;
		cout<<ans<<'\n';
	}
return 0;
}

```

---

## 作者：1saunoya (赞：0)

样例1已经提示你这题咋做了。

如果是一个连续段，那么是可以搞的。

然后我们只需要数一下有多少个位置是空的，就可以了。

这个可以感性理解。

兔应该说的比较明白吧。

```cpp
/*
 _      _  _ _ _ _ _   _      _
\_\   /_/ \_\_\_\_\_\ \_\   /_/
 \_\ /_/      \_\      \_\ /_/
  \_\_/       \_\       \_\_/
   \_\         \_\       \_\
   \_\     \_\ \_\       \_\
   \_\      \_\\_\       \_\
*/
#include <bits/stdc++.h>
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define rp(i,y) for(int i=1;i<=y;i++)
#define per(i,x,y) for(int i=x;i>=y;i--)
#define pr(i,y) for(int i=y;i>=1;i--)
#define sz(v) (int)v.size()
using namespace std;
const int SIZE=1<<26;
char gc[SIZE],*pgc=gc;
char pc[SIZE],*ppc=pc;
clock_t clk=clock();
struct flusher{
	flusher(){
#ifdef WHX_TXDY
		freopen("fuck.in","r",stdin);
#endif
		fread(gc,true,SIZE,stdin);
	}
	~flusher(){
		fwrite(pc,true,ppc-pc,stdout);
#ifdef WHX_TXDY
		std::cerr<<"TIME:"<<(clock()-clk)/1000.<<"s\n";
#endif
	}
}Flusher;
int _Neg=0;
template<class T>
void rd(T&x){
	x=_Neg=0;
	while(!isdigit(*pgc)){
		if((*pgc++)=='-'){
			_Neg=1;
		}
	}
	while(isdigit(*pgc)){
		x=x*10+*pgc++-48;
	}
	if(_Neg){
		x=-x;
	}
}
int _Stk[233],_Top=0;
template<class T>
void pt(T x,char c='\n'){
	if(x<0){
		*ppc++='-';
		x=-x;
	}
	do{
		_Stk[++_Top]=x%10;
		x/=10;
	}while(x);
	while(_Top){
		*ppc++=_Stk[_Top--]+48;
	}
	*ppc++=c;
}
void pts(const string&str){
	int len=sz(str);
	rep(i,0,len-1){
		*ppc++=str[i];
	}
	*ppc++='\n';
}
template<class T>
void cmax(T&x,const T&y){
	x=(x>y)?x:y;
}
template<class T>
void cmin(T&x,const T&y){
	x=(x<y)?x:y;
}

int n, q;
const int N = 2e5 + 5;
int pool[N << 1];
int *s = pool + N;
int a[N];
int cnt[N];

int main() {
	rd(n);
	rd(q);
	
	rp(i,n){
		int x;
		rd(x);
		a[i] = x;
		++cnt[x];
	}
	rp(i,n){
		++s[i];
		--s[i-cnt[i]];
	}
	int ans=0;
	per(i,n,-n){
		s[i]+=s[i+1];
	}
	per(i,n,1){
		if(!s[i]){
			++ans;
		}
	}
	rp(_,q){
		int x,y;
		rd(x);
		rd(y);
		--cnt[a[x]];
		if(!--s[a[x]-cnt[a[x]]]){
			if(a[x]-cnt[a[x]]>0){
				++ans;
			}
		}
		a[x]=y;
		if(!s[a[x]-cnt[a[x]]]++){
			if(a[x]-cnt[a[x]]>0){
				--ans;
			}
		}
		++cnt[y];
		pt(ans);
	}
	return 0;
}
```

---

