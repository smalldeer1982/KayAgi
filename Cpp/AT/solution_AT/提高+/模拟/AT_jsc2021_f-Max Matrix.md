# Max Matrix

## 题目描述

[problemUrl]: https://atcoder.jp/contests/jsc2021/tasks/jsc2021_f

長さ $ N $ の数列 $ a $ と、長さ $ M $ の数列 $ b $ があります。最初、$ a,b $ の要素は全て $ 0 $ です。  
 $ Q $ 個のクエリを処理してください。$ i $ 個目のクエリでは $ 3 $ つの整数 $ T_i,\ X_i,\ Y_i $ が与えられ、以下の処理をします。

- $ T_i\ =\ 1 $ のとき : $ a_{X_i} $ を $ Y_i $ に置き換える
- $ T_i\ =\ 2 $ のとき : $ b_{X_i} $ を $ Y_i $ に置き換える

そして、毎回のクエリの処理直後に $ \displaystyle\ \sum_{i\ =\ 1}^N\ \sum_{j\ =\ 1}^M\ \max(a_i,\ b_j) $ の値を出力してください。

## 说明/提示

### 制約

- $ 1\ \le\ N\ \le\ 2\ \times\ 10^5 $
- $ 1\ \le\ M\ \le\ 2\ \times\ 10^5 $
- $ 1\ \le\ Q\ \le\ 2\ \times\ 10^5 $
- $ T_i $ は $ 1 $ または $ 2 $
- $ T_i\ =\ 1 $ ならば $ 1\ \le\ X_i\ \le\ N $
- $ T_i\ =\ 2 $ ならば $ 1\ \le\ X_i\ \le\ M $
- $ 1\ \le\ Y_i\ \le\ 10^8 $
- 入力に含まれる値は全て整数である

### Sample Explanation 1

上から $ i $ 行目、左から $ j $ 列目に $ \max(a_i,\ b_j) $ を書き込んだマス目は、$ 4 $ 回のクエリで以下のように変化します。 !\[\](https://img.atcoder.jp/ghi/9a4098e2aa50b21c51ce3664d278ba87.png)

### Sample Explanation 3

出力する整数は $ 32 $ bit 整数型に収まらない可能性があります。

## 样例 #1

### 输入

```
2 2 4
1 1 10
2 1 20
2 2 5
1 1 30```

### 输出

```
20
50
55
85```

## 样例 #2

### 输入

```
3 3 5
1 3 10
2 1 7
1 3 5
2 2 10
2 1 1```

### 输出

```
30
44
31
56
42```

## 样例 #3

### 输入

```
200000 200000 4
2 112219 100000000
1 73821 100000000
2 26402 100000000
1 73821 100000000```

### 输出

```
20000000000000
39999900000000
59999800000000
59999800000000```

# 题解

## 作者：ben090302 (赞：2)

今天是`CSP2024`的前一天晚上，按照大佬们的说法是写题解涨rp，那就来写点套路题练练手涨涨rp把。

$\max$ 在一些时候也跟绝对值什么的一样可以考虑拆掉，就像这道题。

现在只考虑修改 $a$ 的情况看看答案有什么变化。

那不不妨看看 $a_i$ 对原答案的贡献如何吧。

提取一下就能看出 $a_i$ 的贡献就是 $\sum_{j=1}^m \max(a_i,b_j)$。

我们用艾弗森括号 $[P]$ 来改写一下这个式子（$[P]$ 在 $P$ 为真时为 $1$ 反之为 $0$），就相当于分类讨论一下，于是得出 $a_i$ 的贡献是：

$$
a_i\sum_{j=1}^m [a_i\ge b_j]+\sum_{j=1}^m b_j[a_i<b_j]
$$

前半段的含义是 $a_i$ 乘上比 $a_i$ 小或正好相等的 $b$ 的数量，可以用权值树状数组维护，当然了你非要线段树也行。

后半段的含义也是明显的，就是比 $a_i$ 大的 $b_j$ 的总和。这一部分其实也是权值树状数组可以搞掉的，区别在于前面是每次在树状数组下标为 $b_j$ 的位置加上一，而后面那个式子每次加上 $b_j$。

于是我们对 $a,b$ 各自维护两个权值树状数组，在修改的时候考虑变化量即可。

加上离散化，复杂度 $O(q\log n+n\log n)$，然后就可以A了这题了。

也是祝所有人明天比赛好运吧，希望都能取得自己想要的成绩，也说不定这就是我竞赛生涯的最后一篇题解了呢。

```
#include<bits/stdc++.h>
#define int long long
#define lb(x) (x&-x)
using namespace std;
const int N=6e5+5;
#define gk(x) (lower_bound(L+1,L+cnt+1,x)-L)
int bit[4][N];
int cnt;
void add(int x,int k,int th){
    for(int i=x;i<=cnt;i+=lb(i)) bit[th][i]+=k; 
}
int query(int x,int th){
    int ret=0;
    for(int i=x;i;i-=lb(i)) ret+=bit[th][i];
    return ret;
}
int n,m,q;
int a[N],b[N];
int use[N];
int p[N],X[N],xx[N],opt[N];
int L[N];
int ans;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>m>>q;
    for(int i=1;i<=q;i++){
        cin>>opt[i]>>p[i]>>X[i];
        L[++cnt]=X[i];
    }
    L[++cnt]=0;
    sort(L+1,L+cnt+1);
    cnt=unique(L+1,L+cnt+1)-(L+1);
    for(int i=1;i<=q;i++) xx[i]=lower_bound(L+1,L+cnt+1,X[i])-L;
    for(int i=1;i<=n;i++) add(gk(0),1,0);
    for(int i=1;i<=m;i++) add(gk(0),1,2);
    for(int i=1;i<=q;i++){
        if(opt[i]==1){
            int rp=gk(a[p[i]]);
            ans-=a[p[i]]*query(rp,2)+query(cnt,3)-query(rp,3);//cerr<<i<<"i1:"<<ans<<"\n";
            add(rp,-1,0);
            add(rp,-a[p[i]],1);
            a[p[i]]=X[i];
            add(gk(a[p[i]]),1,0);
            add(gk(a[p[i]]),a[p[i]],1);
            ans+=a[p[i]]*query(gk(a[p[i]]),2)+query(cnt,3)-query(gk(a[p[i]]),3);
        }else{
            ans-=b[p[i]]*query(gk(b[p[i]]),0)+query(cnt,1)-query(gk(b[p[i]]),1);
            add(gk(b[p[i]]),-1,2);
            add(gk(b[p[i]]),-b[p[i]],3);
            b[p[i]]=X[i];
            add(gk(b[p[i]]),1,2);
            add(gk(b[p[i]]),b[p[i]],3);
            ans+=b[p[i]]*query(gk(b[p[i]]),0)+query(cnt,1)-query(gk(b[p[i]]),1);
        }
        cout<<ans<<"\n";
    }
}
/*
add(a[i],1,0);
add(a[i],a[i],1);
add(b[i],1,2);
add(b[i],b[i],3);
*/
```

---

## 作者：igAC (赞：1)

# $\text{Description}$

[洛谷 link](https://www.luogu.com.cn/problem/AT_jsc2021_f)

[ATlink](https://atcoder.jp/contests/jsc2021/tasks/jsc2021_f)

简要题意：

有一个长度为 $n$ 的序列 $a$ 和长度为 $m$ 的序列 $b$，初始值都为 $0$。

$q$ 次修改，每次对 $a$ 序列或 $b$ 序列单点修改。

对于每次修改求出修改后的 $\sum_{i=1}^{n} \sum_{j=1}^{m} \max(a_i,b_j)$。

# $\text{Solution}$

一道比较套路的拆 $\max$ 题目。

以修改 $a_i$ 为例，我们可以将：

$$\sum_{j=1}^{m} \max(a_i,b_j)$$

拆成：

$$a_i \times \sum_{j=1}^{m}[b_j<a_i] + \sum_{j=1}^{m} b_j [b_j \geq a_i]$$

也就是说，我们要维护小于 $a_i$ 的 $b_j$ 的个数以及大于 $a_i$ 的 $b_j$ 的和。

这可以对给定的 $y$ 进行离散化后通过两个树状数组维护。

第一个树状数组维护 $b$ 序列在离散化后小于等于 $i$ 的个数。

第二个树状数组维护 $b$ 序列在离散化后小于等于 $i$ 的所有数的和。

对于修改 $b_i$ 也同理。

也就是用四个树状数组维护答案，离散化的时候别忘了 $a,b$ 初始都为 $0$。

具体实现可参考代码，时间复杂度 $O(q \log q)$。

# $\text{Code}$

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 500005
using namespace std;
int read(){
	int x=0,f=1,ch=getchar();
	for(;!isdigit(ch);ch=getchar()) f=(ch=='-')?-1:1;
	for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
	return x*f;
}
int n,m,q,buc[N],tot,a[N],b[N],ans;
map<int,int>pos;
struct BIT{
	int c[N],n;
	int lowbit(int x){return x&-x;}
	void add(int x,int y){for(;x<=n;x+=lowbit(x)) c[x]+=y;}
	int query(int x){
		int res=0;
		for(;x;x-=lowbit(x)) res+=c[x];
		return res;
	}
}bit1,bit2,bit3,bit4;
struct qust{
	int t,x,d;
}que[N];
//1:anum 2:aval 3:bnum 4:bval
signed main(){
	n=read(),m=read(),q=read();
	for(int i=1;i<=q;++i){
		int t=read(),x=read(),d=read();
		que[i]=(qust){t,x,d};
		buc[++tot]=d;
	}
	buc[++tot]=0,pos[0]=1;
	sort(buc+1,buc+tot+1),tot=unique(buc+1,buc+tot+1)-(buc+1);
	for(int i=1;i<=q;++i){
		int x=lower_bound(buc+1,buc+tot+1,que[i].d)-buc;
		pos[que[i].d]=x;
	}
	bit1.n=bit2.n=bit3.n=bit4.n=tot;
	bit1.add(1,n),bit3.add(1,m);
	for(int i=1;i<=q;++i){
		auto [op,x,d]=que[i];
//		printf("%lld %lld %lld\n",op,x,d);
		if(op==1){
			ans-=a[x]*bit3.query(pos[a[x]]-1);
			ans+=d*bit3.query(pos[d]-1);
			ans-=bit4.query(tot)-bit4.query(pos[a[x]]-1);
			ans+=bit4.query(tot)-bit4.query(pos[d]-1);
			bit1.add(pos[a[x]],-1),bit1.add(pos[d],1);
			bit2.add(pos[a[x]],-a[x]),bit2.add(pos[d],d);
			a[x]=d;
		}
		else{
			ans-=b[x]*bit1.query(pos[b[x]]-1);
			ans+=d*bit1.query(pos[d]-1);
			ans-=bit2.query(tot)-bit2.query(pos[b[x]]-1);
			ans+=bit2.query(tot)-bit2.query(pos[d]-1);
			bit3.add(pos[b[x]],-1),bit3.add(pos[d],1);
			bit4.add(pos[b[x]],-b[x]),bit4.add(pos[d],d);
			b[x]=d;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：AlicX (赞：0)

## Solution 

考虑 $a_i$ 对答案的贡献：即是比 $a_i$ 大的数的总和加上比 $a_i$ 小的数的数量乘 $a_i$。 

所以考虑动态维护答案，假设目前在处理第 $i$ 次操作，设 $i-1$ 次操作的答案为 $ans$。所以只需考虑变化量，假设目前是将 $a_x$ 修改为 $y$（修改 $b_x$ 同理）：首先减去 $a_x$ 对于答案的贡献，再加上 $y$ 对答案的贡献即可。这部分用两个树状数组维护，时间复杂度为 $O(q \log n)$，常数会有点大。

将询问离线下来离散化后算贡献的时候记得映射回去。

```cpp
#include<bits/stdc++.h> 
#define int long long 
#define x first 
#define y second 
#define il inline 
#define debug() puts("-----") 
using namespace std; 
typedef pair<int,int> pii; 
il int read(){ 
	int x=0,f=1; char ch=getchar(); 
	while(ch<'0'||ch>'9'){ if(ch=='-') f=-1; ch=getchar(); } 
	while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar(); 
	return x*f; 
} 
const int N=2e5+10; 
int n,m,q; 
int a[N],b[N]; 
int c[N],num=0; 
struct Query{ 
	int t,x,y; 
}del[N]; 
#define low(x) x&-x 
int tr1[N][2],tr2[N][2]; 
il void add1(int x,int k,int w){ 
	for(int i=x;i<=num;i+=low(i)) tr1[i][k]+=w; 
} 
il void add2(int x,int k,int w){ 
	for(int i=x;i;i-=low(i)) tr2[i][k]+=w; 
} 
il int query1(int x,int k){ 
	int res=0; 
	for(int i=x;i;i-=low(i)) res+=tr1[i][k]; 
	return res; 
} 
il int query2(int x,int k){ 
	int res=0; 
	for(int i=x;i<=num;i+=low(i)) res+=tr2[i][k]; 
	return res;  
} 
signed main(){ 
	n=read(),m=read(),q=read(); int ans=0; 
	for(int i=1;i<=q;i++) del[i].t=read(),del[i].x=read(),del[i].y=read(),c[++num]=del[i].y; 
	c[++num]=0; sort(c+1,c+num+1); num=unique(c+1,c+num+1)-c-1; 
	for(int i=1;i<=n;i++) a[i]=1; for(int i=1;i<=m;i++) b[i]=1; 
	add1(1,0,n),add1(1,1,m); 
	for(int i=1;i<=q;i++){ 
		int x=del[i].x,y=del[i].y; 
		y=lower_bound(c+1,c+num+1,y)-c; 
		if(del[i].t==1){ 
			ans-=query2(a[x]+1,1); 
			ans-=c[a[x]]*query1(a[x],1); 
			add1(a[x],0,-1),add2(a[x],0,-c[a[x]]); 
			a[x]=y; 
			add1(a[x],0,1),add2(a[x],0,c[a[x]]); 
			ans+=query2(a[x]+1,1); 
			ans+=c[a[x]]*query1(a[x],1); 
		} else{ 
			ans-=query2(b[x]+1,0); 
			ans-=c[b[x]]*query1(b[x],0); 
			add1(b[x],1,-1),add2(b[x],1,-c[b[x]]); 
			b[x]=y; 
			add1(b[x],1,1),add2(b[x],1,c[b[x]]); 
			ans+=query2(b[x]+1,0); 
			ans+=c[b[x]]*query1(b[x],0); 
		} printf("%lld\n",ans); 
	} return 0; 
} /*
2 2 4
1 1 10
2 1 20
2 2 5
1 1 30

2 2 1
1 1 10
*/
```

---

## 作者：EuphoricStar (赞：0)

我们考虑动态维护答案。如果已经知道上一步的答案，考虑计算这一次操作之后答案的变化。

考虑现在有一个数列 $a_{1 \sim n}$，我们想知道 $\sum\limits_{i = 1}^n \max(x, a_i)$。

计算出 $c = \sum\limits_{i = 1}^n [a_i < x], s = \sum\limits_{i = 1}^n [a_i \ge x] a_i$，答案显然就是 $s + c \times x$。

这题和上面的题本质相同。以第一种操作为例，每次答案减去旧的 $a_x$ 对 $b$ 造成的贡献，再加上 $y$ 对 $b$ 造成的贡献。第二种操作是对称的。

于是我们只需要对 $y_i$ 离散化后，行和列分别维护两个树状数组表示 $\sum\limits_{i = 1}^n [a_i \le x]$ 和 $\sum\limits_{i = 1}^n [a_i \le x] a_i$，一共四个树状数组即可。

时间复杂度 $O(q \log (q + n + m))$。

[code](https://atcoder.jp/contests/jsc2021/submissions/43071046)

---

