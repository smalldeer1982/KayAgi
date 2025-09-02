# Lisa and the Martians

## 题目描述

Lisa was kidnapped by martians! It okay, because she has watched a lot of TV shows about aliens, so she knows what awaits her. Let's call integer martian if it is a non-negative integer and strictly less than $ 2^k $ , for example, when $ k = 12 $ , the numbers $ 51 $ , $ 1960 $ , $ 0 $ are martian, and the numbers $ \pi $ , $ -1 $ , $ \frac{21}{8} $ , $ 4096 $ are not.

The aliens will give Lisa $ n $ martian numbers $ a_1, a_2, \ldots, a_n $ . Then they will ask her to name any martian number $ x $ . After that, Lisa will select a pair of numbers $ a_i, a_j $ ( $ i \neq j $ ) in the given sequence and count $ (a_i \oplus x) \& (a_j \oplus x) $ . The operation $ \oplus $ means [Bitwise exclusive OR](http://tiny.cc/xor_wiki), the operation $ \& $ means [Bitwise And](<http://tiny.cc/and_wiki >). For example, $ (5 \oplus 17) \& (23 \oplus 17) = (00101_2 \oplus 10001_2) \& (10111_2 \oplus 10001_2) = 10100_2 \& 00110_2 = 00100_2 = 4 $ .

Lisa is sure that the higher the calculated value, the higher her chances of returning home. Help the girl choose such $ i, j, x $ that maximize the calculated value.

## 说明/提示

First testcase: $ (3 \oplus 14) \& (1 \oplus 14) = (0011_2 \oplus 1110_2) \& (0001_2 \oplus 1110_2) = 1101_2 = 1101_2 \& 1111_2 = 1101_2 = 13 $ .

Second testcase: $ (1 \oplus 0) \& (1 \oplus 0) = 1 $ .

Third testcase: $ (9 \oplus 4082) \& (13 \oplus 4082) = 4091 $ .

Fourth testcase: $ (3 \oplus 7) \& (0 \oplus 7) = 4 $ .

## 样例 #1

### 输入

```
10
5 4
3 9 1 4 13
3 1
1 0 1
6 12
144 1580 1024 100 9 13
4 3
7 3 0 4
3 2
0 0 1
2 4
12 2
9 4
6 14 9 4 4 4 5 10 2
2 1
1 0
2 4
11 4
9 4
2 11 10 1 6 9 11 0 5```

### 输出

```
1 3 14
1 3 0
5 6 4082
2 3 7
1 2 3
1 2 15
4 5 11
1 2 0
1 2 0
2 7 4```

# 题解

## 作者：lalaouye (赞：8)

可以发现本题中如果两数在一位下两两不同，那么最终答案这一位下肯定为 $0$，否则就可以为 $1$，想到这里本题就很简单了，找到异或和最小的二元组即可，不过需要一点贪心处理，那就是排完序就可以线性复杂度求异或和最小的二元组了。

最后算答案可以手推，复杂度 $\mathcal{O}(n\log n)$。

代码：

```cpp
void solve ()
{
	T = rd ();
	while (T --)
	{
		int n = rd (), k = rd (), I = 0, J;
		for (int i = 1; i <= n; i ++)
			b[i] = a[i].x = rd (), a[i].id = i;
		sort (a + 1, a + n + 1);
		int minn = 1e18;
			for (int i = 2; i <= n; i++)
			{
				if ((a[i].x ^ a[i - 1].x) < minn)
				{
					I = min (a[i].id, a[i - 1].id);
					J = max (a[i].id, a[i - 1].id);
					minn = a[i].x ^ a[i - 1].x;
				}
			}
		cout<<I<<" "<<J<<" "<<(1 << (k)) - 1 - ((1 << (int(log2 (min(b[I],b[J])) + 1)) - 1) + (min(b[I],b[J]) ^ ((1 <<(int(log2 (min(b[I],b[J])) + 1)) - 1))<<endl;
	}
	return;
}
```

最后的~~废话~~，本题赛时没调出来，就差不到 $1$ 分钟，前面浪费了很多时间，最后时间心态又很不好，所以又吃了两发罚时。所以大家引以为戒，心态一定要好！！！


---

## 作者：_sunkuangzheng_ (赞：6)

**【题目大意】**

给定数组长度为 $n$ 的数组 $a(0 \le a_i < 2^k)$，要求你找到三个整数 $i,j,x$，使得 $1 \le i,j \le n,i \ne j,0 \le x < 2^k$ 且 $(a_i \oplus x) \& (a_j \oplus x)$ 的值最大，输出 $i,j,k$。$1 \le n \le 2 \times 10^5,1 \le k \le 30$。

**【题目分析】**

赛时 D 细节写错，E 多测没清空前后耽误了半个多小时，导致这题赛时没调出来 qwq。



与异或有关的问题常用线性基或 01-trie 解决，本题需要使用 01-trie。

首先注意到一个性质：将两个二进制数字 $a,b$ 异或一个数 $x$ 再按位与的值发生变化，当且仅当某一位上 $a,b$ 的值相同，且 $x$ 在该位上的值为 $1$。简要证明一下，若 $a,b$ 在该位上的值不同，那么按位与结果必定是 $0$，此时异或一个数字后 $a,b$ 该位的值仍保持不同，答案不变；若 $a,b$ 在该位上的值相同且 $x$ 在该位上的值为 $0$，则这一位上异或 $x$ 对答案没有影响，因为任何数异或 $0$ 等于它本身。

**解法一**

------------

所以我们先建 01-trie，枚举每一个 $i$ 并尽量的寻找与 $a_i$ 相同位数多的 $a_j$，但要注意 $i \ne j$ 的限制。找到 $a_j$ 后，我们遍历 $a_i,a_j$ 的每一个二进制位，若 $a_i,a_j$ 在第 $k$ 位上都为 $0$，则需要让 $x \leftarrow x + 2^k$，并在该过程中记录答案，最后取 $\max$。时间复杂度 $\Theta(nk)$。

本题细节很多，有几个易错点：

- 在 01-trie 上查找时忘记 $i \ne j$ 的限制。解决方法：开一个数组 $p$，若当前节点至少经过两次，则说明任何情况都可以走该节点；若只经过一次，那么若当前的 $a_j$ 已经不等于 $a_i$ 则可以走，否则不能。

- 输出了最大值而不是 $i,j,x$ 或输出的 $j = i$。解决方法：开一个 `vector` 记录每个末尾节点存储的编号，若当前节点 `vector` 里第一位的编号恰好等于 $i$ 那么取第二位即可。

- 多测没清空。解决办法：可以选择打时间戳，也可以暴力清空。然而 `vector` 只能暴力清空。

- 输出的 $x \ge 2^k$。解决办法：在建树时不能像以前一样写 `for(int i = 30;i;i --)`，而应该将最高位限制为 $k$，即 `for(int i = k;i;i --)`。

**【代码】**

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,kk,t,a[500005],tot,ch[200005*32][2],vis[200005*32][2],p[200005*32],times;
vector<int> ed[200005*32];
void insert(int x,int id){
    int s = 0;
    for(int i = kk;i >= 0;i --){
        int k = (x >> i) & 1;
        if(vis[s][k] != times) ch[s][k] = ++tot;
        else p[ch[s][k]] = times;
        vis[s][k] = times,s = ch[s][k];
    }
    ed[s].push_back(id);
}
int query(int x,int id){
    int s = 0,flag = 0;//flag 表示 ai 和 aj 是否已经不同
    for(int i = kk;i >= 0;i --){
        int k = (x >> i) & 1;
        if(vis[s][k] == times && (flag || (p[ch[s][k]] == times))) s = ch[s][k];
        else s = ch[s][!k],flag = 1;
    }
    if(ed[s][0] == id) return ed[s][1];
    return ed[s][0];
}
void work(){
    cin >> n >> kk,times ++,kk--,tot = 0;//2^k 转二进制，位数 -1
    int mi,mj,mx,ans = -1;
    for(int i = 1;i <= n;i ++) cin >> a[i],insert(a[i],i);
    for(int i = 1;i <= n;i ++){
        int rj = query(a[i],i),rx = a[rj],res = 0,tx = 0;
        for(int j = kk;j >= 0;j --){
            int k1 = (rx >> j) & 1,k2 = (a[i] >> j) & 1;
            if(k1 == k2) res += (1 << j);
            if(k1 == k2 && k1 == 0) tx += (1 << j);
        }
        if(res > ans) ans = res,mi = i,mj = rj,mx = tx;
    }
    cout << mi << " " << mj << " " << mx << "\n";
    for(int i = 0;i <= (kk+1)*n;i ++) ed[i].clear();//注意清空 vector
}
signed main(){
    cin >> t;
    while(t --) work();
    return 0;
}
```

**解法二**

------------

注意到我们想让最高位尽可能的相同，而最高位数字相同的数一定是连续的。所以我们将原序列降序排序，直接枚举相邻数字并计算 $x$，统计答案。非常好写。

**【代码】**

```cpp
#include <bits/stdc++.h>
using namespace std;
int t,n,k;
struct num{int a,b;}a[500005];
bool cmp(num a,num b){return a.a > b.a;}
int main(){
    cin >> t;
    while(t --){
        cin >> n >> k,k --;
        for(int i = 1;i <= n;i ++) cin >> a[i].a,a[i].b = i;
        sort(a+1,a+n+1,cmp);
        int mi = 0,mj = 0,mx = 0,ans = -1;
        for(int i = 1;i < n;i ++){
            int x = a[i].a,y = a[i+1].a,tx = 0,res = 0;
            for(int j = k;j >= 0;j --){
                int p = (x >> j) & 1,q = (y >> j) & 1;
                if(p == q) res += (1 << j);
                if(p == q && p == 0) tx += (1 << j);
            }
            if(res > ans) ans = res,mi = a[i].b,mj = a[i+1].b,mx = tx;
        }
        cout << mi << " " << mj << " " << mx << "\n";
    }
    return 0;
}
```


---

## 作者：Wf_yjqd (赞：2)

赛时有思路懒得写、。

其实直接排序找相邻两个就行，但我不会证明。

------------

算得上是 01 字典树板子吧。

考虑构造 $k$ 为 $a_i$ 按位取反后的值，则将答案转换为 $a_i\odot a_j$，可以说明其能代表 $(a_i\oplus k)\&(a_j\oplus k)$ 的最大值。

可以枚举 $i$，用 Trie 维护 $\max\limits_{j\neq i}{a_i\&a_j}$ 所对应的 $j$，更新答案即可。

复杂度 $\operatorname{O}(n\times k)$。

------------

真的很板。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+84;
struct Point{
    int son[2],cnt,id;
    inline void clear(){
        son[0]=son[1]=cnt=id=0;
        return ;
    }
}Trie[maxn*32];
int T,n,k,kk,a[maxn],ans,ansid[2],cnt;
struct Trie_Tree{
    inline void Modify(int x,int f,bool op){
        int id=1,t;
        for(int i=k-1;i>=0;i--){
            t=(a[x]>>i)&1;
            if(!Trie[id].son[t]&&op)
                Trie[id].son[t]=++cnt;
            id=Trie[id].son[t];
            Trie[id].cnt+=f;
        }
        if(op)
            Trie[id].id=x;
        return ;
    }
    inline int Find(int x){
        int id=1,t;
        for(int i=k-1;i>=0;i--){
            t=(x>>i)&1;
            if(Trie[Trie[id].son[t]].cnt)
                id=Trie[id].son[t];
            else
                id=Trie[id].son[t^1];
        }
        return Trie[id].id;
    }
}Sherry;
int main(){
    scanf("%d",&T);
    while(T--){
        for(int i=0;i<=cnt;i++)
            Trie[i].clear();
        scanf("%d%d",&n,&k);
        kk=(1<<k)-1;
        cnt=1;
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
            Sherry.Modify(i,1,1);
        }
        ans=-168;
        ansid[0]=ansid[1]=0;
        for(int i=1;i<=n;i++){
            Sherry.Modify(i,-1,0);
            int res=Sherry.Find(a[i]);
            if(ans<(kk&(a[res]^a[i]^kk))){
                ans=(kk&(a[res]^a[i]^kk));
                ansid[0]=i;
                ansid[1]=res;
            }
            Sherry.Modify(i,1,0);
        }
        printf("%d %d %d\n",ansid[0],ansid[1],kk^a[ansid[0]]);
    }
    return 0;
}
```


---

## 作者：iiiiiyang (赞：1)

[心碎的阅读体验](https://www.cnblogs.com/LittleTwoawa/p/17586704.html)

[题目链接](https://www.luogu.com.cn/problem/CF1851F)

在二进制下考虑，注意 $\&$ 的性质，一位上运算的两个数都为 $1$ 结果才能为 $1$；$\oplus$ 的性质，异或一个数后两个数在这一位上是否相同不会改变。这使得我们要使得这一位为 $1$ 的话，$a_i$ 和 $a_j$ 在这一位上必须相同。也就是说从高到低考虑，答案一定拥有最长的公共前缀，根据二进制的性质，将 $a$ 序列从小到大排序后相邻的两个数一定拥有最长的公共前缀，接下来就是枚举暴力计算。计算 $X$ 的方法就是这一位不同随便填，相同就填相反的那一种，使这一位异或出来是 $1$ 就好了。于是做到单次 $\mathcal O(n \log n + nk)$。

```cpp
#include<bits/stdc++.h>
#define ld long double
#define ui unsigned int
#define ull unsigned long long
#define int long long
#define eb emplace_back
#define pb pop_back
#define ins insert
#define mp make_pair
#define pii pair<int,int>
#define fi first
#define se second
#define power(x) ((x)*(x))
#define gcd(x,y) (__gcd((x),(y)))
#define lcm(x,y) ((x)*(y)/gcd((x),(y)))
#define lg(x,y)  (__lg((x),(y)))
using namespace std;
 
namespace FastIO
{
    template<typename T=int> inline T read()
    {
        T s=0,w=1; char c=getchar();
        while(!isdigit(c)) {if(c=='-') w=-1; c=getchar();}
        while(isdigit(c)) s=(s*10)+(c^48),c=getchar();
        return s*w;
    }
    template<typename T> inline void read(T &s)
    {
        s=0; int w=1; char c=getchar();
        while(!isdigit(c)) {if(c=='-') w=-1; c=getchar();}
        while(isdigit(c)) s=(s*10)+(c^48),c=getchar();
        s=s*w;
    }
    template<typename T,typename... Args> inline void read(T &x,Args &...args)
    {
        read(x),read(args...);
    }
    template<typename T> inline void write(T x,char ch)
    {
        if(x<0) x=-x,putchar('-');
        static char stk[25]; int top=0;
        do {stk[top++]=x%10+'0',x/=10;} while(x);
        while(top) putchar(stk[--top]);
        putchar(ch);
        return;
    }
}
using namespace FastIO;
 
namespace MTool
{   
    #define TA template<typename T,typename... Args>
    #define TT template<typename T>
    static const int Mod=998244353;
    TT inline void Swp(T &a,T &b) {T t=a;a=b;b=t;}
    TT inline void cmax(T &a,T b) {a=a>b?a:b;}
    TT inline void cmin(T &a,T b) {a=a<b?a:b;}
    TT inline void Madd(T &a,T b) {a=a+b>Mod?a+b-Mod:a+b;}
    TT inline void Mdel(T &a,T b) {a=a-b<0?a-b+Mod:a-b;}
    TT inline void Mmul(T &a,T b) {a=a*b%Mod;}
    TT inline void Mmod(T &a) {a=(a%Mod+Mod)%Mod;}
    TT inline T Cadd(T a,T b) {return a+b>=Mod?a+b-Mod:a+b;}
    TT inline T Cdel(T a,T b) {return a-b<0?a-b+Mod:a-b;}
    TT inline T Cmul(T a,T b) {return a*b%Mod;}
    TT inline T Cmod(T a) {return (a%Mod+Mod)%Mod;}
    TA inline void Madd(T &a,T b,Args... args) {Madd(a,Cadd(b,args...));}
    TA inline void Mdel(T &a,T b,Args... args) {Mdel(a,Cadd(b,args...));}
    TA inline void Mmul(T &a,T b,Args... args) {Mmul(a,Cmul(b,args...));}
    TA inline T Cadd(T a,T b,Args... args) {return Cadd(Cadd(a,b),args...);}
    TA inline T Cdel(T a,T b,Args... args) {return Cdel(Cdel(a,b),args...);}
    TA inline T Cmul(T a,T b,Args... args) {return Cmul(Cmul(a,b),args...);}
    TT inline T qpow(T a,T b) {int res=1; while(b) {if(b&1) Mmul(res,a); Mmul(a,a); b>>=1;} return res;}
    TT inline T qmul(T a,T b) {int res=0; while(b) {if(b&1) Madd(res,a); Madd(a,a); b>>=1;} return res;}
    TT inline T spow(T a,T b) {int res=1; while(b) {if(b&1) res=qmul(res,a); a=qmul(a,a); b>>=1;} return res;}
    TT inline void exgcd(T A,T B,T &X,T &Y) {if(!B) return X=1,Y=0,void(); exgcd(B,A%B,Y,X),Y-=X*(A/B);}
    TT inline T Ginv(T x) {T A=0,B=0; exgcd(x,Mod,A,B); return Cmod(A);}
    #undef TT
    #undef TA
}
using namespace MTool;
 
inline void file()
{
    freopen(".in","r",stdin);
    freopen(".out","w",stdout);
    return;
}
 
bool Mbe;
 
namespace LgxTpre
{
    static const int MAX=200010;
    static const int inf=2147483647;
    static const int INF=4557430888798830399;
    static const int mod=1e9+7;
    static const int bas=131;
    
    int T,n,k,ans;
	pii a[MAX];
    int X,p1,p2;
    
    inline void lmy_forever()
    {
    	read(T);
    	while(T--)
    	{
    		read(n,k),X=p1=p2=0,ans=-1;
    		for(int i=1;i<=n;++i) a[i].fi=read(),a[i].se=i;
    		sort(a+1,a+n+1);
    		for(int i=1;i<n;++i)
    		{
    			int x=a[i].fi,y=a[i+1].fi,z=0;
    			for(int j=k-1;~j;--j) if(((x>>j&1)==(y>>j&1)&&(x>>j&1)==0)||((x>>j&1)!=(y>>j&1))) z|=1<<j; 
    			if(((x^z)&(y^z))>ans) X=z,p1=a[i].se,p2=a[i+1].se,ans=(x^z)&(y^z);	
			}
			write(p1,' '),write(p2,' '),write(X,'\n');
		}
        return;
    }
}
 
bool Med;
 
signed main()
{
//  file();
    fprintf(stderr,"%.3lf MB\n",abs(&Med-&Mbe)/1048576.0);
    int Tbe=clock();
    LgxTpre::lmy_forever();
    int Ted=clock();
    cerr<<1e3*(Ted-Tbe)/CLOCKS_PER_SEC<<" ms\n";
    return (0-0);
}
```

---

## 作者：_JF_ (赞：0)

[CF1851F Lisa and the Martians](https://www.luogu.com.cn/problem/CF1851F)

自己的第一个 01-trie。还是不会贪心。

考虑枚举 $i$，找到小于 $i$ 的一个 $j$，构造出来一个 $x$ 满足最大。

先简化条件，如果给定了 $i,j$，怎么找到 $x$ 满足最值，那很显然是按高到低位考虑。

分类讨论当前位的情况：

| $a_i$ | $a_j$ | $x$ | $(a_i \oplus x) \&  (a_j \oplus x)$ |
| -----------: | -----------: | -----------: | -----------: |
| $0$ | $1$ | $0/1$ | $0$ |
| $1$ | $0$ | $0/1$ | $0$ |
| $0$ | $0$ | $1$ | $1$ |
| $1$ | $1$ | $0$ | $1$ |

我们观察到一个重要的事实，如果两个数当前位相同，那么我们有方法让他取到这一位对答案的贡献为 $1$。

所以，对于当前的 $a_i$，我们的贪心策略是走和 $a_i$ 当前位相同的路径，选了当前位是要优于后面所有位的和的。

把他拍到 trie 树上面去按照这个步骤走即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =5e6+10;
//#define int long long
int ch[N][3],Dus[N],Pre,n,X,a[N],Vis[N],AnsI,AnsJ,Ansx;
void build(int x){
	int p=0;
	for(int i=X-1;i>=0;i--){
		int now=(a[x]>>i&1);
		if(!ch[p][now])	ch[p][now]=++Pre;	
		Vis[ch[p][now]]++,p=ch[p][now];
//		cout<<now<<" "; 
	}
//	cout<<endl;
	Dus[p]=x;
}
void Slove(int x,int u,int pre,int Sum){
	int v1=ch[u][0],v2=ch[u][1],now=(a[x]>>(X-pre)&1);
	if(pre==X+1){
		if(((a[x]^Sum)&(a[Dus[u]]^Sum))>=((a[AnsI]^Ansx)&(a[AnsJ]^Ansx)))	AnsI=x,AnsJ=Dus[u],Ansx=Sum;
		return ;
	}
	else if(v1==0)// Go 1 
		Slove(x,v2,pre+1,Sum);
	else if(v2==0){ // Go 0
		if(now==1)	Slove(x,v1,pre+1,Sum);
		else	Slove(x,v1,pre+1,Sum+(1<<(X-pre)));
	}
	else{
		if(Vis[ch[u][now]]>=1)	Slove(x,ch[u][now],pre+1,Sum+((now==0)?(1<<(X-pre)):0));
		else	Slove(x,ch[u][!now],pre+1,Sum);
	}
}
void Clear(){
	for(int i=0;i<=Pre;i++)	ch[i][1]=ch[i][0]=0,Dus[i]=Vis[i]=0;
	Pre=Ansx=0,AnsI=AnsJ=0;
}
signed main(){
	int t;
	cin>>t;
	while(t--){
		scanf("%d%d",&n,&X);
		for(int i=1;i<=n;i++)	scanf("%d",&a[i]);
		for(int i=1;i<=n;i++)	Slove(i,0,1,0),build(i);
		cout<<AnsI<<" "<<AnsJ<<" "<<Ansx<<endl,Clear();
	}
	return 0;
}
```

---

## 作者：rabbitohh (赞：0)

转化一下题意，本题实际上就是给我们 $n$ 个 $k$ 位二进制数，让我们任选两个使得它们的同或值最大。  
考虑 0/1Trie，如果我们把这 $n$ 个数直接全塞到一个 Trie 里，想查询最大同或值，这显然是很困难的。但如果给定一个塞进了多个数的 Trie 和一个另外的数 $x$ ，我们可以很轻易地求出 $x$ 和 Trie 中的哪个数同或值最大。具体来说，如果当前 Trie 中结点没有 $0$ 儿子，那只能跳向 $1$ 儿子，反之亦然。如果两个儿子都有的话，那我们优先跳向与 $x$ 对应位相同的儿子。  
所以对于 $n$ 个数来说，我们可以先把第一个数塞到 Trie 里，然后对于第 $i$ 个数 $a_i$（$2≤i≤n$），先查询 $a_i$ 和 Trie 的最大同或值，更新答案，然后将 $a_i$ 塞入 Trie。  
我们可以插入的过程中，把数在序列中的位置 $i$ 记在Trie的叶子节点上，这就解决了输出要求中 $i$ 和 $j$ 的维护问题（不妨设 $i<j$，则 $j$ 实际上就是我们枚举的量），对于 $x$，将 $a_i$ 取反即可。

贴一下丑陋的赛时代码：
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#define int long long
using namespace std;
const int N=3e5+10;
vector<int>ch[2];
vector<int>id;
int sz=0;
int idx=1;
bool tmp[N];
int a[N];
int vis[N];
int n,k;
void add(int x,int iid)
{
	for(int i=1;i<=k;i++)
	{
		tmp[i]=(x&1);
		x>>=1;
	}
	int rt=1;
	for(int i=k;i>=1;i--)
	{
		int x=tmp[i];
		while(idx>sz-10)
		{
			ch[0].push_back(0);
			ch[1].push_back(0);
			id.push_back(0);
			sz++;
		}
		
		if(!ch[x][rt])
		{
			ch[x][rt]=++idx;
		}
		rt=ch[x][rt];
		if(i==1)
		{
			id[rt]=iid;
		}
	}
}
int cans=-1,l,r;
void find(int x,int iid)
{
	for(int i=1;i<=k;i++)
	{
		tmp[i]=(x&1);
		x>>=1;
	}
	int ans=0;
	int rt=1;
	for(int i=k;i>=1;i--)
	{
		int x=tmp[i];
		if(!ch[x][rt])
		{
			rt=ch[x^1][rt];
			ans<<=1;
		}
		else
		{
			rt=ch[x][rt];
			ans<<=1;
			ans++;
		}
		if(i==1)
		{
			if(ans>=cans)
			{
				cans=ans;
				l=id[rt],r=iid;
			}
		}
	}
}
void ans()
{
	cans=l=r=0;
	cin>>n>>k;
	idx=1;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	add(a[1],1);
	int ans=0;
	for(int i=2;i<=n;i++)
	{
		find(a[i],i);
		add(a[i],i);
	}
	for(int i=1;i<=idx;i++)
	{
		ch[0][i]=ch[1][i]=id[i]=0;
	}
	int h=a[l];
	int cx=0;
	for(int i=1;i<=k;i++)
	{
		tmp[i]=(h&1);
		h>>=1;
	}
	for(int i=k;i>=1;i--)
	{
		cx<<=1;
		cx+=(tmp[i]^1);
	}
	cout<<l<<' '<<r<<' '<<cx<<'\n';
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	int T;
	cin>>T;
	while(T--)
	{
		ans();
	}
	
	return 0; 
}  	 		  	  	 		   	  		 		
```


---

## 作者：Keroshi (赞：0)

 # 题意
 有一个长度为 $n$ 的序列 $a$，其中对于 $1\le i \le n$，$0\le a_i < 2^k$。    
对于 $1 \le i,j \le n$，$0\le x < 2^k$，求使得 $(a_i\oplus x)\&(a_j\oplus x)$ 为最大值的 $i,j,k$。
# 解题思路
思考两个数每一位的四种情况。  
设两个数相同位置的一位为 $u$ 和 $v$。   
当 $u=1$ 且 $v=1$ 时，它们的与运算为 $1$，这时 $x$ 的这一位取 $0$ 就能到达最大值 $1$。   
当 $u=0$ 且 $v=0$ 时，可以在 $x$ 的这一位取 $1$ 使得这两个数都为一，它们的与运算为 $1$，到达最大值 $1$。  
当 $u\ne v$ 时，不关 $x$，怎么取，与运算为 $0$。  
由上可知，为了能达到最大值，高位要尽量取相同的，   
而高位越相同的数排序后肯定两数距离越小，   
所以考虑排序，在相邻的两个数内取值即可。  
时间复杂度 $O(nk)$。

``` cpp
void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n), f(n);
    REP(i, n) cin >> a[i];
    iota(ALL(f), 0);
    sort(ALL(f), [&] (int x, int y) {
        return a[x] < a[y];
    });
    int ans = 0, p1 = 0, p2 = 1, p3 = 0;
    REP(i, n - 1) {
        int x = 0, res = 0;
        ROF(j, k - 1, 0) {
            int u = (a[f[i]] >> j) & 1;
            int v = (a[f[i + 1]] >> j) & 1;
            if(u == v) {
                res ^= (1 << j);
                if(!u) x ^= (1 << j);
            } 
        }
        if(res > ans) {
            ans = res;
            p1 = f[i];
            p2 = f[i + 1];
            p3 = x;
        }
    }
    if(p1 > p2) swap(p1, p2);
    cout << p1 + 1 << " " << p2 + 1 << " " << p3 << endl;
}
```

---

## 作者：xzyg (赞：0)

题意：

给定 $ n $ 个数的序列 $ a $，和一个数 $ k $，求 $ i,j \in [1,n],=i \ne j $ 和 $ x \in [0, 2^k] $，使得 $ (a_i \oplus x) \& (a_j \oplus x) $ 最大，其中 $ \oplus $ 为异或符号，$ \& $ 为按位与符号。

01-trie 好题。

考虑已经插入 $ a_1 \sim a_{p-1} $，如何找到 $ j=p $ 时使答案最大的 $ i $ 和 $ x $。

显然可以从二进制高位向低位贪心。

考虑单独的二进制位对答案的影响：

| $ a_i $ | $ a_j $ | $ x $ | $ (a_i \oplus x) \& (a_j \oplus x) $ |
| :-----------: | :-----------: | :-----------: | :-----------: |
| 1 | 1 | 0 | 1 |
| 0 | 0 | 1 | 1 |
| 0 | 1 | 0/1 | 0 |
| 1 | 0 | 0/1 | 0 |

（上图表列出了使 $ (a_i \oplus x) \& (a_j \oplus x) $ 最大的 $ x $ 取值）

若当前位相同，则可以通过改变 $ x $ 值使结果位为 $ 1 $；

若当前位不同，则无论 $ x $ 值为多少，结果位均为 $ 0 $。

于是发现在 trie 上每位贪心地选与当前位相同的数即可。

代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define MAXN 200010
using namespace std;
 
ll read(){
	char ch=getchar();
	ll s=0,w=1;
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){s=s*10+ch-'0';ch=getchar();}
	return s*w;
}
 
ll n, k;
 
struct trie{
	ll son[2];
	ll pos;
}tree[MAXN << 6];
ll now = 0;
 
ll a[MAXN];
ll ans = 0, ansx = 0, anspos1 = 2, anspos2 = 1;
 
void query(ll x, ll num, ll bit, ll cnt, ll cntt, ll pos){
	if(bit == -1){
		if(ans < cnt){
			ans = cnt;
			ansx = cntt;
			anspos1 = pos;
			anspos2 = tree[x].pos;
		}
		return;
	}
	bool p = num & (1 << bit);
	if(tree[x].son[p]){
		cnt ^= (1 << bit);
		if(p == 0){
			cntt ^= (1 << bit);
		}
		query(tree[x].son[p], num, bit-1, cnt, cntt, pos);
	}else{
		query(tree[x].son[p^1], num, bit-1, cnt, cntt, pos);
	}
}
 
void insert(ll x, ll num, ll bit, ll pos){
	if(bit == -1){
		tree[x].pos = pos;
		return;
	}
	bool p = num & (1 << bit);
	if(!tree[x].son[p]){
		tree[x].son[p] = ++now;
	}
	insert(tree[x].son[p], num, bit-1, pos);
}
 
int main(){
	ll T = read();
	
	while(T--){
		now = 0, ans = 0;
		anspos1 = 2, anspos2 = 1;
		ansx = 0;
		
		n = read(), k = read();
		
		for(ll i = 0; i <= n * k; i++){
			tree[i].pos = 0;
			tree[i].son[0] = 0, tree[i].son[1] = 0;
		}
		
		for(ll i = 1; i <= n; i++){
			a[i] = read();
			query(0, a[i], k-1, 0, 0, i);
			insert(0, a[i], k-1, i);
		}
		
		cout << anspos2 << " " << anspos1 << " " << ansx << endl;
	}
	
	
	
	return 0;
}
```


---

## 作者：N_z_ (赞：0)

## 题意

给你一组数，你需要找到 $i,j,x$，使得 $(a_i\oplus x)\&(a_j\oplus x)$ 最大，其中 $a_i,x\le2^k$。

## 思路

假设已经有了 $u=a_i,v=a_j$，现在计算 $x$。考察第 $i$ 位，注意到，当 $u$ 和 $v$ 在第 $i$ 位值相同时，可以通过令 $x$ 在这一位不同于 $u,v$ 使得结果为 $1$，否则结果一定为 $0$。

那么，最终的答案即为 $2^k-u\oplus v-1$。最大化这个值，即找到 $i,j$ 使得 $a_i\oplus a_j$ 最小。

首先给出结论，将 $a$ 排序之后，$a_i\oplus a_j(i<j)$ 最小时，$j=i+1$。对该结论进行证明。

我们考察 $u\le v\le w$，只需证明 $\min(u\oplus v,v\oplus w)\le u\oplus w$。假设最高位至第 $i+1$ 位 $u,v,w$ 均相同，第 $i$ 位不同，考察第 $i$ 位。

由于 $u\le v\le w$，则第 $i$ 位 $u$ 为 $0$，$w$ 为 $1$，从而当 $v$ 为 $0$ 时，$u\oplus v<u\oplus w$，否则，$v\oplus w<u\oplus w$。

依照上文构造即可。

## 代码

[215560134](https://codeforces.com/contest/1851/submission/215560134)。

---

