# Stack Exterminable Arrays

## 题目描述

让我们来看如下过程：最开始你有一个空栈和一个长度为 $l$ 的数组 $s$。你尝试按顺序将数组元素 $s_1, s_2, s_3, \dots, s_{l}$ 压入栈中。此外，如果栈为空，或者当前栈顶元素不等于当前元素，则你直接将当前元素压入栈顶。否则，你不仅不将当前元素压入栈，还要弹出栈顶元素。

如果这个过程结束后栈为空，则称数组 $s$ 是“可栈消灭”的。

以下是一些“可栈消灭”的数组示例：

- $[1, 1]$；
- $[2, 1, 1, 2]$；
- $[1, 1, 2, 2]$；
- $[1, 3, 3, 1, 2, 2]$；
- $[3, 1, 3, 3, 1, 3]$；
- $[3, 3, 3, 3, 3, 3]$；
- $[5, 1, 2, 2, 1, 4, 4, 5]$；

以 $s = [5, 1, 2, 2, 1, 4, 4, 5]$ 为例，详细说明栈的变化过程（栈顶用加粗表示）：

1. 压入 $s_1 = 5$ 后，栈变为 $[\textbf{5}]$；
2. 压入 $s_2 = 1$ 后，栈变为 $[5, \textbf{1}]$；
3. 压入 $s_3 = 2$ 后，栈变为 $[5, 1, \textbf{2}]$；
4. 压入 $s_4 = 2$ 后，栈变为 $[5, \textbf{1}]$；
5. 压入 $s_5 = 1$ 后，栈变为 $[\textbf{5}]$；
6. 压入 $s_6 = 4$ 后，栈变为 $[5, \textbf{4}]$；
7. 压入 $s_7 = 4$ 后，栈变为 $[\textbf{5}]$；
8. 压入 $s_8 = 5$ 后，栈为空。

现在，给定一个数组 $a_1, a_2, \ldots, a_n$，你需要计算它有多少个子数组是“可栈消灭”的。

注意，你需要回答 $q$ 个独立的询问。

## 说明/提示

对于第一个询问，有四个“可栈消灭”子数组：$a_{1 \ldots 4} = [2, 1, 1, 2]$，$a_{2 \ldots 3} = [1, 1]$，$a_{2 \ldots 5} = [1, 1, 2, 2]$，$a_{4 \ldots 5} = [2, 2]$。

对于第二个询问，只有一个“可栈消灭”子数组，即 $a_{3 \ldots 4}$。

对于第三个询问，有八个“可栈消灭”子数组：$a_{1 \ldots 8}, a_{2 \ldots 5}, a_{2 \ldots 7}, a_{2 \ldots 9}, a_{3 \ldots 4}, a_{6 \ldots 7}, a_{6 \ldots 9}, a_{8 \ldots 9}$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
5
2 1 1 2 2
6
1 2 1 1 3 2
9
3 1 2 2 1 6 6 3 3
```

### 输出

```
4
1
8
```

# 题解

## 作者：Felix72 (赞：67)

难得有 CF 的瞬秒题，写个题解纪念一下。

容易看出，题面是一个括号匹配计数题，只是括号种类不限制。那么我们把整个序列按照题意模拟一下，如果存在两个前缀满足它们所对应的栈的状态一致，那么这两个前缀的差就是合法序列，因为中间部分被削除了。

那么，开一个桶记录状态即可。状态压缩的方法有很多，这里建议双哈希并采用不一样的方法，否则碰到数字种类单一的数据容易被卡。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 300010;
typedef pair < long long, long long > PII;
mt19937 rnd(time(0));
long long t, n, a[N], ans, hsh[N], sta[N], top, hsh2[N];
map < PII, long long > mp;
inline void sol()
{
	top = ans = 0;
	cin >> n;
	for(int i = 1; i <= n; ++i) cin >> a[i];
	for(int i = 1; i <= n + 5; ++i) hsh[i] = rnd(), hsh2[i] = rnd();
	long long now = 0, n2 = 0;
	mp.clear();
	mp[{0, 0}] = 1;
	for(int i = 1; i <= n; ++i)
	{
		if(top && sta[top] == a[i]) --top, now ^= (hsh[top + 1] * a[i]), n2 += (hsh[top + 1] ^ a[i]);
		else sta[++top] = a[i], now ^= (hsh[top] * a[i]), n2 -= (hsh[top] ^ a[i]);
		ans += mp[{now, n2}];
		mp[{now, n2}]++;
	}
	cout << ans << '\n';
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t;
	while(t--) sol();
	return 0;
}
```

---

## 作者：DengDuck (赞：21)

今年提高第二题的加强版，场上写的是 $\mathcal O(nR)$ 的做法，$R$ 表示值域，这题值域比较大显然不能这么做。

首先分析能消除的序列，我们发现这个序列可以由多个可消除的部分组成，那么我们对于每个位置找出其左边最右边的一个 $pos_i$ 使得 $[pos_i,i]$ 可消除，则我们可以直接动态规划求方案数：

$$
f_i=f_{pos_i-1}+1
$$

然后累加 $f_i$ 即可。

那么考虑 $pos_i$ 怎么求，发现就是找一个 $[pos_i+1,i-1]$ 可以消除且 $A_{pos_{i}}=A_i$。

有一种类似 KMP 的跳的方法，实现如下，时间复杂度为 $O(R)$：

```cpp
for(int i=1;i<=n;i++)
{
	if(c[i]==c[i-1])
	{
		pos[i]=i-1;
		continue;
	}
	LL t=i-1;
	while(pos[t]!=-1&&t)
	{
		if(c[pos[t]-1]!=c[i])t=pos[t]-1;
		else break;
	}
	if(t)if(c[pos[t]-1]==c[i])pos[i]=pos[t]-1;
}
```
不过这题不可能这么做，我们考虑保存一个 $ma_{i,j}$ 表示一个最大的 $ma_{i,j}$ 满足 $A_{ma_{i,j}}=j$ 且 $[ma_{i,j}+1,i]$ 可以消除，然后就可以快速求 $pos_i$ 了。

那么怎么维护 $ma$ 呢？我们如果找到了合法的 $pos_i$，可以考虑直接令 $ma_i=ma_{pos_i-1}$，看似时间复杂度爆炸，其实后面用不到 $ma_{pos_i-1}$，可以直接交换，时间复杂度为 $\mathcal O(1)$，然后再把不同的项改改就行了。

时间复杂度为 $\mathcal O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=2e6+5;
LL T,n,pos[N],f[N],ans,c[N];
map<LL,LL>ma[N];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		ans=0;
		scanf("%lld",&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%lld",&c[i]);
			ma[i].clear();
			f[i]=0;
			pos[i]=-1;
		}
		for(int i=1;i<=n;i++)
		{
			if(ma[i-1].count(c[i]))
			{
				LL t=ma[i-1][c[i]];
				pos[i]=t;
				swap(ma[i],ma[t-1]);
				if(t!=1)ma[i][c[t-1]]=t-1;
			}
			ma[i][c[i]]=i;
		}
		for(int i=1;i<=n;i++)
		{
			if(pos[i]==-1)continue;
			f[i]=f[pos[i]-1]+1;
			ans+=f[i]; 
		}
		printf("%lld\n",ans);		
	}
	
}
```

---

## 作者：nofind (赞：19)

题意:https://www.luogu.org/problem/CF1223F

考虑求出$nxt[i]$,满足$nxt[i]$是使得$[i,nxt[i]]$为括号序列的最左边的那一个

这样就可以DP了:

$f[i]$表示以i为开头的括号序列数目

$f[i]=f[nxt[i]]+1$

$ans=\sum\limits_{i=1}^nf[i]$

考虑如何求$nxt[i]$:

假如求出了$nxt[i+1]$,现在要求$nxt[i]$,那么必定要比较$a[i]$和$a[nxt[i]+1]$,如果相同就$nxt[i]=nxt[i+1]+1$,不然就比较$nxt[nxt[i+1]]+1...$以此类推

考虑优化这个过程:

对每一个点开一个$map$,$map[i][j]$记录了$i$右边的一个位置$pos$,满足$[i,pos-1]$是合法的括号序列,那么$nxt[i]=map[i+1][a[i]]$

code:
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=3*1e5+10;
int Q,n;
int a[maxn],nxt[maxn],f[maxn];
map<int,int>mp[maxn];
signed main()
{
	scanf("%lld",&Q);
	while(Q--)
	{
		scanf("%lld",&n);
		for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
		for(int i=1;i<=n+1;i++)mp[i].clear(),f[i]=0,nxt[i]=-1;
		for(int i=n;i;i--)
		{
			if(mp[i+1].count(a[i]))
			{
				int pos=mp[i+1][a[i]];
				nxt[i]=pos;
				swap(mp[i],mp[pos+1]);
				if(pos<n)mp[i][a[pos+1]]=pos+1;
			}
			mp[i][a[i]]=i;
		}
		int res=0;
		for(int i=n;i;i--)
		{
			if(nxt[i]==-1)continue;
			f[i]=f[nxt[i]+1]+1;
			res+=f[i];
		}
		printf("%lld\n",res);
	}
	return 0; 
}
```


---

## 作者：_Arahc_ (赞：16)

提供一个非常神秘的解法（？）。

我们考虑到这样一件事情：显然一个好的序列至少要有一对数字是相邻的，否则完全消不掉任何数字。这时，我们先把这两个数字消掉，再消其它的数字，结果是不变的。

换句话说，这个“消除”的方式满足结合律——在序列上添加一些“括号”，先消除“括号”里面的数字，直到“括号”里的数字消完之后，再从左往右消除，结果是不变的。

我们还知道一个东西，它的运算也满足结合律：矩阵乘法。

对于 $1\sim n$ 中的所有数，给每个数字 $i$ 随机赋权为一个矩阵 $F_i$。然后把矩阵对应在输入的序列上：对于一个数字 $x$，若 $x$ 是第奇数次出现，则赋为 $F_x$，否则将其赋为 $F_x$ 的逆矩阵（不妨设为 $G_x$），得到一个矩阵序列。

那么判定一个子串是好的，可以转化为判定这个子串所有矩阵的积为单位矩阵 $\epsilon$。

于是你对矩阵序列作前缀积，记为序列 $S$，不难发现如果一段子串 $[l,r]$ 的积为单位矩阵，则 $S_r \div S_{l-1} = \epsilon$，则说明 $S_r = S_{l-1}$。（此处的除法表示乘上除数的逆元。）

于是开个 `map` 记录一下每个前缀积的出现次数即可。

说句题外话，如果把数字改成括号序列，每次把栈顶匹配的左右括号删除的话，就不能用这种方法做了。因为 $F_x \times G_x = G_x \times F_x = \epsilon$，但是只有 `()` 这样的括号串才合法，`)(` 这样的括号串并不合法。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int max_n=300005,mod=1000000009;
inline int read(){
    int x=0;bool w=0;char c=getchar();
    while(c<'0' || c>'9') w|=c=='-',c=getchar();
    while(c>='0' && c<='9') x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return w?-x:x;
}
inline void write(int x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10^48);
}
inline int mi(int a,int p=mod-2){
    int res=1;
    while(p){
        if(p&1) res=res*a%mod;
        a=a*a%mod,p>>=1;
    }
    return res;
}
struct Matrix{
    int f[2][2];
    Matrix(int A=0,int B=0,int C=0,int D=0){
        f[0][0]=A,f[0][1]=B,f[1][0]=C,f[1][1]=D;
    }
    Matrix operator * (Matrix &b){
        Matrix a=*this;
        return Matrix((a.f[0][0]*b.f[0][0]+a.f[0][1]*b.f[1][0])%mod,(a.f[0][0]*b.f[0][1]+a.f[0][1]*b.f[1][1])%mod,(a.f[1][0]*b.f[0][0]+a.f[1][1]*b.f[1][0])%mod,(a.f[1][0]*b.f[0][1]+a.f[1][1]*b.f[1][1])%mod);
    }
    bool operator < (const Matrix &b) const{
        Matrix a=*this;
        if(a.f[0][0]^b.f[0][0]) return a.f[0][0]<b.f[0][0];
        if(a.f[0][1]^b.f[0][1]) return a.f[0][1]<b.f[0][1];
        if(a.f[1][0]^b.f[1][0]) return a.f[1][0]<b.f[1][0];
        if(a.f[1][1]^b.f[1][1]) return a.f[1][1]<b.f[1][1];
        return 0;
    }
    bool operator == (const Matrix &b) const{
        Matrix a=*this;
        return (a.f[0][0]==b.f[0][0] && a.f[0][1]==b.f[0][1] && a.f[1][0]==b.f[1][0] && a.f[1][1]==b.f[1][1]);
    }
}f[2][max_n],S;
const Matrix Ep(1,0,0,1);
inline Matrix Inv(Matrix a){
    int x=mi((a.f[0][0]*a.f[1][1]-a.f[1][0]*a.f[0][1]%mod+mod)%mod);
    return Matrix(a.f[1][1]*x%mod,mod-a.f[0][1]*x%mod,mod-a.f[1][0]*x%mod,a.f[0][0]*x%mod);
}

map<Matrix,int> mp;

int n,cnt[max_n],ans;
const int N=300000;

signed main(){
    srand(time(0));
    for(int i=1;i<=N;++i){
        f[1][i]=Matrix(rand()%mod,rand()%mod,rand()%mod,rand()%mod);
        f[0][i]=Inv(f[1][i]);
    }
    for(int T=read();T;--T){
        n=read();
        S=Ep,ans=0;
        mp.clear(),++mp[Ep];
        for(int i=1;i<=n;++i){
            int x=read();
            ++cnt[x];
            S=S*f[cnt[x]&1][x];
            ans+=mp[S]++;
        }
        write(ans),putchar('\n');
        memset(cnt,0,sizeof(int)*(n+1));
    }
    return 0;
}
```



---

## 作者：Kelin (赞：15)

## [题意](https://blog.csdn.net/BeNoble_/article/details/102333058)
给一个序列进行栈操作，从左到右入栈，若当前入栈元素等于栈顶元素则栈顶元素出栈，否则当前元素入栈。若进行完操作后栈为空，这说这个序列是可以被消除的。

给你一个长度为$n$的序列$a$，问$a$有多少子串是可以被消除的。

---

## 题解

定义$f_i$表示序列$a_i,a_{i+1},...,a_n$有多少可以被消除的子串

那么$f_i=f_{j+1}+1$，$j$是使得$a_i,a_{i+1},...,a_j$能够被消除的最小的$j$

如果不存在此$j$，那么$f_i=0$

那么$Ans=\sum_{i=1}^nf_i$

考虑如何对于每一个$i$求出这个$j$

记$Nx_i$表示此$j$，那么如果$a_{Nx_{i+1}+1}=a_i$，则$Nx_i=Nx_{i+1}+1$

否则再判断$a_{Nx_{Nx_{i+1}+1}+1}=a_i$，则$Nx_i=Nx_{Nx_{i+1}+1}+1$

如此递归直到找到一个$Nx_k$或者$Nx_k+1>n$为止

这样显然耗时显然是巨大的，而我们每次又只要找$a_i$

考虑设$Ny_{i,x}$表示使得$a_i,a_{i+1},...,a_{j-1}$能够被消除的最小的$j$且$a_j=x$

那么$Nx_i=Ny_{i+1,a_i}$，如果$a_{i-1}\neq a_i$，那么$a_{i-1}$跳$Nx$就一定会跳到$Ny_{i+1,a_i}+1$处再进行判断

那么我们可以直接令$Ny_i=Ny_{Nx_i+1}$即可（这里$C++$对$map$使用$swap$可以做到$O(1)$）

此时$a_i,a_{i+1},...,a_{Nx_i}$是可以被消除的，所以$Ny_{i,a_{Nx_i+1}}=Nx_i+1$

然后也要把$a_i$加进去，即$Ny_{i,a_i}=i$

时间复杂度$O(n\log n)$

```cpp
#include<bits/stdc++.h>
#define fp(i,a,b) for(int i=a;i<=b;++i)
#define fd(i,a,b) for(int i=a;i>=b;--i)
#define file(s) freopen(s".in","r",stdin),freopen(s".out","w",stdout)
using namespace std;
const int N=3e5+5,inf=~0u>>1;
typedef long long ll;
typedef int arr[N];
int n,a[N],Nx[N];ll f[N];
map<int,int>Ny[N];
inline void sol(){
	scanf("%d",&n);
	fp(i,1,n){
		scanf("%d",a+i);
		Ny[i].clear();
		Nx[i]=-1;f[i]=0;
	}
	Ny[n+1].clear();f[n+1]=0;
	int p;ll ans=0;
	fd(i,n,1){
		if(Ny[i+1].count(a[i])){
			Nx[i]=p=Ny[i+1][a[i]];
			swap(Ny[i],Ny[p+1]);
			if(p!=n)Ny[i][a[p+1]]=p+1;
		}
		Ny[i][a[i]]=i;
	}
	fd(i,n,1)if(~Nx[i]){
		f[i]=f[Nx[i]+1]+1;
		ans+=f[i];
	}
	printf("%lld\n",ans);
}
int main(){
	int q;
	scanf("%d",&q);
	while(q--)sol();
return 0;
}
```

---

## 作者：Limie (赞：11)

首先吐槽一句，CCF 你不会出题就别出了，你原汁原味搬原题有意义吗？？？

----------------------------

### 1. 考虑如何判断一个序列是不是“可消除的”
显然可以用栈做，给出序列 `3 1 1 3 2 1 1 2` 的判断的示意图

![](https://cdn.luogu.com.cn/upload/image_hosting/eg3855y2.png)

### 2. 开始部分分
显然你可以 $O(n^3)$ 暴力枚举，但你发现将栈复用就有了一个 $O(n^2)$ 的暴力，正确性显然。

代码如下
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,top;
int stk[300010],s[300010];
signed main()
{
	int i,j,ans=0;
	cin>>n;
    for(i=1;i<=n;i++)cin>>s[i];
	for(j=1;j<=n;j++){
		top=0;
		for(i=j;i<=n;i++){
			if(top&&s[stk[top]]==s[i])top--;else stk[++top]=i;
			if(!top)ans++;
		}
	}
	cout<<ans;
}
```

### 3. 考虑正解
考虑前缀栈，当加入 $i$ 与加入 $j$ 得到的栈是一样的，则序列 $\left [ i+1,j \right ]$ 就一定是“可消除的”。

那么对前缀栈做字符串哈希，然后就结束哩。

注意栈要清空。

最后用一份代码来 ~~嘲讽 CCF~~ 结束此题解
```cpp
#include<bits/stdc++.h>
namespace fuckCCF{
	#define x first
	#define y second
	#define counting push
	using namespace std;
	typedef long long LL;
	typedef pair<int,int> PII;
	typedef unsigned long long ULL;
	typedef long double LD;
}
using namespace fuckCCF;
const ULL score=1145141;
int number;
ULL CCF_has[300010];
stack<int> CCF;
map<ULL,int> jiaozaodata;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int i,t;
	cin>>t;
	while(t--){
		cin>>number;
		jiaozaodata.clear();
		jiaozaodata[0]++;
		while(CCF.size())CCF.pop();
		CCF_has[0]=1;
		for(i=1;i<=number;i++)CCF_has[i]=CCF_has[i-1]*score;
		ULL my_money=0;
		LL last_score=0;
		for(i=1;i<=number;i++){
			int money,CCFmoney=CCF.size();
			cin>>money;
			if(CCFmoney&&CCF.top()==money)
				my_money^=CCF_has[CCFmoney]*money,CCF.pop();
			
			else CCF.counting(money),
				my_money^=CCF_has[CCFmoney+1]*money;
			
			last_score+=(jiaozaodata[my_money]++);
		}
		cout<<last_score<<'\n';
	}
}

```

---

## 作者：meyi (赞：9)

提供一种码量极小的 $O(n)$ 确定性做法。

首先转化一下题意，$[l,r]$ 合法等价于 $[1,l-1]$ 的栈的状态与 $[1,r]$ 的栈的状态完全相同，所以 $i$ 对答案的贡献就是有多少个 $j$ 满足 $0\leq j<i$ 且 $[1,j]$ 与 $[1,i]$ 的栈的状态相同，特别的，我们记 $[1,0]$ 的栈的状态为 $\varnothing$。

很显然可以哈希来求这个，但是没必要。将栈看做一个字符串，考虑我们每次 push 或者 pop 某个数的本质，其实是在字典树上移动到了当前点的儿子或者父亲，对答案的贡献也就是有多少个字符串以当前点为末尾。

由于 $|\sum|$ 与 $n$ 同阶，故使用 unordered_map 来记录儿子，时间复杂度 $O(n)$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct trie{
	trie *fa;
	int siz;
	unordered_map<int,trie*>son;
	inline trie(trie *f){fa=f,siz=0;}
};
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		int n;
		scanf("%d",&n);
		vector<int>a(n);
		for(int &i:a)scanf("%d",&i);
		long long ans=0;
		trie *rt=new trie(NULL);
		++rt->siz;
		vector<int>st;
		for(int i:a){
			if(st.empty()||st.back()!=i){
				st.push_back(i);
				rt=rt->son.emplace(i,new trie(rt)).first->second;
			}
			else rt=rt->fa,st.pop_back();
			ans+=rt->siz++;
		}
		printf("%lld\n",ans);
	}
	return 0;
}

```

---

## 作者：WaterSun (赞：6)

CCF 出的原题观摩一下。

# 思路

首先可以用一个 Trie 来维护。

在这里对本文中的一些变量做一下说明。

1. $p$ 表示当前维护的 Trie 中，指向的元素编号。

2. $t_i$ 表示在 Trie 中编号为 $i$ 的元素在原序列中的值。

3. $f_i$ 表示在 Trie 中编号为 $i$ 的元素在 Trie 中的父节点。

4. $v_i$ 表示在 Trie 中编号为 $i$ 被遍历的次数。

考虑每一次将一个数 $a_i$ 加入 Trie 的时候需要做什么操作。

如果当前在 Trie 中指向的节点 $t_p$ 与 $a_i$ 相等，说明可以进行合并， 那么直接将 $p$ 跳到 $f_p$ 即可；否则需要新开一个节点 $v$，接在 $p$ 的下方，并将 $p$ 更新到 $v$ 上。

然后在更新 $p$ 之后，要将 $v_p$ 加 $1$。

考虑如何统计答案。发现点 $p$ 被遍历过 $2$ 次时，答案会加 $1$；$3$ 次，答案会加 $2$；以此类推。

这是因为当 $v_p > 1$ 时，说明 $p$ 节点已经可以被合并 $v_p - 1$ 次了，所以直接加 $v_p - 1$ 即可。

**注意：在代码中为了优美，将 $v_p$ 初值设为了 $-1$。**

但是用普通的 Trie 显然是过不了的，因为 Trie 的空间复杂度在本题中会变为 $\Theta(n^2)$，所以直接开一个 `umap` 即可。

复杂度为 $\Theta(n \log n)$，实测跑得飞快。

# code

```cpp
#include <bits/stdc++.h>
#define re register
#define ll long long

using namespace std;

const int N = 3e5 + 10;
int T,n,p,idx;
ll ans;
int arr[N];

struct node{
	ll val;
	int u,fa;
	unordered_map<int,int> son;
}tr[N];

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

inline void solve(){
	ans = 0;
	p = idx = 1;
	n = read();
	for (re int i = 1;i <= n;i++){
		tr[i].val = tr[i].u = tr[i].fa = 0;
		tr[i].son.clear();
		arr[i] = read();
	}
	for (re int i = 1;i <= n;i++){
		if (arr[i] == tr[p].u) p = tr[p].fa;
		else{
			int v;
			if (!tr[p].son.count(arr[i])){
				tr[p].son[arr[i]] = v = ++idx;
				tr[v] = {-1,arr[i],p};
			}
			else v = tr[p].son[arr[i]];
			p = v;
		}
		tr[p].val++;
		ans += tr[p].val;
	}
	printf("%lld\n",ans);
}

int main(){
	T = read();
	while (T--) solve();
	return 0;
}
```

---

## 作者：zac2010 (赞：5)

简要题解：考虑按照题意模拟，能消除就消除，否则入栈。每维护一个元素的加入后，用哈希维护当前栈的状态，最后就遍历哈希表（假设它是 $x$ 个位置的栈序列），拿所有 $C_{x}^{2}$ 求个和即可。

### 解题思路

考虑先借助可消除序列的构造方式对括号序列的形态进行观察：
1. 假若 `A` 是一个可消除序列，那么 `cAc` 也是。

	其中 `c` 是一个字符，`cAc` 表示将两个元素 `c` 分别在前后与数组 `A` 拼接。

2. 假若 `A`,`B` 都是的可消除序列，那么 `AB` 也是可消除序列。

容易发现，这是一个区间 `DP` 的形式，故而我们得到了一个 $O(n^3)$ 的做法。

但仔细考虑可消除序列的性质，不难得出一种复杂度更优的 $O(n^2)$ 的做法：我们枚举左端点，然后逐个贪心地加入下一个字符。其中，我们用栈维护序列，假设能弹栈就弹栈，不能弹就加入。如果某个时刻栈空了，那么得到的可消除序列数就加一。

这是一个比区间 `DP` 更有前途的做法，应为我们完全地脱离了区间 `DP` 枚举区间至少 $O(n^2)$ 的复杂度。

我们尝试在 $O(n^2)$ 做法的基础上抽离模型去简约地考虑。对于一个序列 `1 1 2 2 3 3`，不妨把 `1 1`，`2 2`，`3 3` 两两一组看成 $3$ 个整体去考虑。合法的括号序列数就是 $C_{3}^{2}$（组合意义就是选取两个整体分别作为左右端点）。

为了更清晰地发倔性质，我们不妨在上述括号序列最左边以及最右边各添加一个 $4$：`4 1 1 2 2 3 3 4`，此时的合法序列在原来的基础上还增加了 `4 1 1 2 2 3 3 4`。

由上述的举例易得，从数组的起始位置开始贪心地维护栈，$\forall i,j\in [1,n]$，假若两个时刻的栈序列相同，那么它们之间的这段就是一个可消除序列（因为 $i,j$ 两者之间的位置经历了加栈和弹栈的过程，所以栈序列相同就证明中间的所有字符都能两两消除）。

$\forall i\in [1,n]$，用哈希维护一下栈序列，之后计数即可。

### 代码实现：

上文提及的 $O(n^2)$ 做法：

```cpp
#include <bits/stdc++.h>
#define FL(i, a, b) for(int i = (a); i <= (b); ++i)
#define FR(i, a, b) for(int i = (a); i >= (b); --i)
using namespace std;
const int N = 2e6 + 10, N1 = 1510;
int n, tp, ans, f[N1][N1], s[N], st[N];
void solve(){
	scanf("%d", &n);
	FL(i, 1, n) scanf("%d", &s[i]);
	FL(i, 1, n){
		tp = 0;
		FL(j, i, n){
			if(!tp || st[tp] != s[j]) st[++tp] = s[j];
			else tp--;
			ans += (!tp);
		}
	}
	printf("%d\n", ans);
}
int main(){
	int T; scanf("%d", &T);
	while(T--) solve();
	return 0;
}
```

哈希的 $O(n)$ 做法：

```cpp
#include <bits/stdc++.h>
#define FL(i, a, b) for(int i = (a); i <= (b); ++i)
#define FR(i, a, b) for(int i = (a); i >= (b); --i)
using namespace std;
typedef unsigned long long ull;
const int N = 3e5 + 10;
const unsigned long long base = 2333333;
unordered_map<ull, int> mp;
int n, tp, a[N], s[N], st[N];
ull h[N]; long long ans;
void solve(){
    scanf("%d", &n);
    FL(i, 1, n) scanf("%d", &s[i]);
    unordered_map<ull, int>().swap(mp);
    mp[0] = 1, ans = tp = 0;
    FL(i, 1, n){
        if(tp && st[tp] == s[i]) tp--;
        else{
            st[++tp] = s[i];
            h[tp] = h[tp - 1] * base + (ull)s[i];
        }
        mp[h[tp]]++;
    }
    for(auto x: mp) ans += 1ll * x.second * (x.second - 1) / 2;
    printf("%lld\n", ans);
}
int main(){
	int T; scanf("%d", &T);
	while(T--) solve();
	return 0;
}
```


---

## 作者：teylnol_evteyl (赞：5)

考虑对每个 $i$ 找到左边最大 $j$，使得区间 $[i,j]$ 能够完全被消除。

设 $f_{i,x}$ 表示如果第 $i+1$ 个数是 $x$，对应的答案是多少，这段区间一定是左边一个 $x$，中间套一段可消除的区间，则：

$$
f_{i,x}=\begin{cases}
i & a_i=x\\
f_{i-1,a_i}-1 & a_i\ne x,a_{f_{i-1,a_i}-1}=x\\
f_{f_{i-1,a_i}-1,x} & a_i\ne x,a_{f_{i-1,a_i}-1} \ne x
\end{cases}
$$

考虑优化。可以看到，如果把 $i$ 向对应的 $j-1$，连边，将构成若干条链，我们只需要在链头记录信息，对每个链头开一个 `unorderd_map` 储存这条链上最后一个前面能接 $x$ 的位置。

设 $g_i$ 表示以 $i$ 结尾的可消除的区间数量，则 $g_i=g_{j-1}+1$，最后答案是 $\sum_{i=1}^ng_i$。

```cpp
#include <cstdio>
#include <unordered_map>

using namespace std;

const int N = 3e5 + 5;

int n, a[N], g[N], fa[N];
unordered_map<int, int> f[N];

int main()
{
	int T;
	scanf("%d", &T);
	while(T -- )
	{
		scanf("%d", &n);
		g[0] = 0, f[0].clear();
		for(int i = 1; i <= n; i ++ )
		{
			scanf("%d", &a[i]);
			g[i] = fa[i] = 0;
			f[i].clear();
		}
		long long ans = 0;
		for(int i = 1; i <= n; i ++ )
		{
			if(f[fa[i - 1]].count(a[i]))
			{
				int p = f[fa[i - 1]][a[i]];
				fa[i] = fa[p];
				g[i] = g[p] + 1;
				ans += g[i];
			}
			else fa[i] = i;
			f[fa[i]][a[i]] = i - 1;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
```

---

## 作者：yqr123YQR (赞：3)

### 题意
给定一 $n$ 项序列，求其有多少子串为合法串（即可按题意，全部消除的串）。
### 分析
> 此处“时间复杂度”均指“单次询问时的时间复杂度，并忽略较小的常数”，下同。

最暴力的想法就是**枚举区间左端点** $l$，并逐位向后移动右端点 $r$，用栈来模拟消除的过程，每次**判断栈是否为空**即可。单次询问**时间复杂度**为 $O(n^2)$，**空间复杂度**为 $O(n)$。

此时，我们需要一点**转化**——
首先，此处用于记录的栈具有**可减性**，下证：

>从**起始状态**开始考虑，分两种情况：
>1. **初始在栈中的元素**一直**未**被影响

>此时若**结束状态**与**初始状态**相同，就等价于**后来的所有元素**都可以自己消除，**一定合法**；

>2. **初始在栈中的元素**有部分**被弹出**

>此时，若有元素（记为 $t$）让**初始元素**弹出，则必有**值相等的元素**以相同的顺序排在**该区间末尾**（中间有可能**夹杂一些合法串**），此时可将 $t$ 与**后面值相等的元素**匹配，即可不用弹出**初始元素**，也即该串**合法**。

>综上，**当且仅当**初始状态和结束状态相同时，中间插入的串才**合法**。

所以我们可以类比**前缀和**，还是维护栈，但我们需要**记录下**前面的栈的状态，每次加上相同状态数量即可。

至此，记录**栈状态**的方法就有了分歧，既可用较为玄学的哈希，又可以用本做法使用的方式——以 `Trie` 记录状态，并通过当前在 `Trie` 上的点的位置**隐式维护**一个栈。

---
### Trie
我们知道，`Trie` 上的一条**从根出发的路径**记录了一个字符串。而此题中，我们可以以栈中元素**自栈底到栈顶**，依次排列所形成的字符串来记录栈的状态。

又由于 `Trie` 中有一个记录**子节点**的数组 `son[i][j]`，共 $n\times n$ 个 `int`，而 $n\leqslant10^6$，所以我们可以用 `unordered_map`（采用 `hash` 实现）来替代数组，时间复杂度依旧是普通 `Trie` 的 $O(n)$。~~要用 `map` 也行，反正不超时。~~

### Code
```cpp
#include<stdio.h>
#include<algorithm>
#include<unordered_map>
using namespace std;
const int maxn = 300000;
typedef long long ll;
int read()
{
	int ret = 0;
	char ch = getchar();
	bool f = false;
	while(ch < '0' || ch > '9') f |= ch == '-', ch = getchar();
	while(ch >= '0' && ch <= '9') ret = ret * 10 + (ch ^ 48), ch = getchar();
	return f? -ret: ret;
}
int n, t, idx, now, f[maxn + 5], cnt[maxn + 5], p[maxn + 5];
ll ans;
unordered_map<int, int> to[maxn + 5];
//f 记录父节点，to 记录子节点，cnt 记录之前所有在节点 i 的状态数
int main()
{
	t = read();
	while(t--)
	{
		n = read();
		idx = now = ans = 0;
		for(int i = 0; i <= n; i++)
		{
			to[i].clear();
			cnt[i] = 0;
		}
		cnt[0] = 1;//类似前缀和，需要预填一个空状态
		for(int i = 1; i <= n; i++)
		{
			int tt = read();
			if(tt == p[now]) now = f[now];//与模拟同理，弹出当前栈的栈顶
			else//压入元素
			{
				if(!to[now][tt])//创建新节点
					f[to[now][tt] = ++idx] = now, p[idx] = tt;
				now = to[now][tt];
			}
			ans += cnt[now]++;//统计
		}
		printf("%lld\n", ans);
	}
	return 0;
}
```

---

## 作者：Wf_yjqd (赞：3)

写个原题题解纪念一下。

考场想出正解，由于健忘，在吃了点东西后忘了做法，打了暴力，险些退役。

------------

原题是有提示的，给了一个栈。

有一个非常显然的 $\operatorname{O}(n^2)$ 暴力做法：枚举左端点，然后用栈模拟右端点向后移，统计栈为空的次数。

发现左端点以左的并不影响，可以直接统计当前栈与左端点前的栈相同的情况（同时删去左边的相当于空栈）。

但这样依然是 $\operatorname{O}(n^2)$，可以用桶数组省去枚举左端点的过程，每次累加相同栈的个数。

简单地说，若经过一个区间后栈的状态没有变化，则这个区间是可以消除的子串。

可能会 MLE，所以还得将栈字符串哈希一下。

复杂度 $\operatorname{O}(n\log n)$。

------------

很神奇的是 gp_hash_table 被卡 TLE 了，所以用了 map。

代码很简单，没啥好看的。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long unt;
namespace Sherry_IO{
    inline unt read(){
        unt x=0;
        char c=getchar();
        while(c<'0'||c>'9')
            c=getchar();
        while(c>='0'&&c<='9'){
            x=x*10+c-'0';
            c=getchar();
        }
        return x;
    }
    inline void write(unt x){
        if(x>9)
            write(x/10);
        putchar(x%10+'0');
        return ;
    }
}
using namespace Sherry_IO;
const unt maxn=2e6+84,Base=564611849,Mod=1e17+1903;
unt T,hs,base[maxn],n,top,ans,s[maxn],st[maxn];
map<unt,unt> cnt;
inline void Solve(){
    n=read();
    for(unt i=1;i<=n;i++)
        s[i]=read();
    cnt.clear();
    cnt[0]=1;
    ans=hs=top=0;
    for(unt i=1;i<=n;i++){
        if(top&&s[i]==st[top]){
            hs=(hs-st[top]*base[top-1]%Mod+Mod)%Mod;
            top--;
        }
        else{
            st[++top]=s[i];
            hs=(hs+st[top]*base[top-1]%Mod)%Mod;
        }
        ans+=cnt[hs];
        cnt[hs]++;
    }
    write(ans);
    putchar('\n');
    return ;
}
int main(){
    base[0]=1;
    for(unt i=1;i<=3e5+23;i++)
        base[i]=base[i-1]*Base%Mod;
    T=read();
    while(T--)
        Solve();
    return 0;
}
```


---

## 作者：Super_Cube (赞：2)

# Solution

好吧，考场上看见这题没啥思路，赛后发现好简单啊。

翻译中对可消除的序列的描述其实很清楚了：

> 对于一个序列进行从左到右的入栈操作，若当前入栈元素等于栈顶元素则栈顶元素出栈，否则当前元素入栈。若进行完操作后栈为空，这说这个序列是可以被消除的。

这 tm 就是个括号配对啊！

如果把每个不同的数字当作不同的括号，遇到相同的数字就当作一对匹配的括号。那么可消除的序列一定满足这样的括号配对。

所以我们可以打出一个 $O(n^2)$ 的代码，可以得到 50pts，如下。

```cpp
//这是单组询问的code...
#include <stdio.h>
#include <stack>
int s[5005];
int n, ans;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		scanf ("%d", &s[i]);
	for (int i = 1; i <= n; ++i) {
		std::stack<int> S;
		for (int j = i; j <= n; ++j) {
			if (!S.empty() && S.top() == s[j])
				S.pop();
			else
				S.push(s[j]);
			if (S.empty())
				++ans;
		}
	}
	printf("%d", ans);
	return 0;
}
```

思考下可以得到，如果对于下标 $r$ 所对应的栈，存在一个下标 $l$ 所对应的栈与其相同，说明 $l+1 \sim r$ 中间这一段一定是可消除序列。

所以对于当前的下标 $i$ 所对应的栈，只需要看前面有多少个栈状态与现在相同就是以 $i$ 为结尾的可消除序列数量。

这个时候我们又可以打出一份代码，预估得分不定，约 70+ pts，如下。

```cpp
//这是单组询问的code...
#include<stdio.h>
#include<stack>
#include<map>
std::map<std::stack<int>,int>mp;
std::stack<int>S;
int s[2000005];
int n;
long long ans;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%d",&s[i]);
	mp[S]=1;
	for(int i=1;i<=n;++i){
		if(!S.empty()&&S.top()==s[i])S.pop();
		else S.push(s[i]);
		ans+=mp[S]++;
	}
	printf("%lld",ans);
	return 0;
}
```

问题出在判断相同栈的速度太慢了。

如何在 $O(1)$ 的时间判断两个东西是否相同呢？我们可以使用哈希来方便的解决这个问题。

如果两个栈状态对应的哈希值相同，那么可以认定为两个栈里面的东西是一模一样的。

哈希的打法有很多种，关键在于要保证两个栈算出的哈希值要不相等，不过这个题在值域大小较小时很容易导致算出的哈希值冲突，这个时候可以使用多哈希来保证正确性或者像我一样把每一种数字的哈希值随机赋值，让哈希冲突的概率变得极小。

# Code
```cpp
#include<bits/stdc++.h>
typedef unsigned long long ull;
std::mt19937_64 rnd(time(0)**new ull);
std::unordered_map<ull,int>mp;
std::stack<int>S;
int a[300005];
ull val[300005],hash;
int n,m;
long long ans;
int main(){
	for(int i=1;i<=300000;++i)val[i]=rnd();
	scanf("%d",&m);
	while(m--){
		scanf("%d",&n);
		for(int i=1;i<=n;++i)
			scanf("%d",&a[i]);
		mp.clear();
		mp[hash=0]=1;
		while(!S.empty())S.pop();
		ans=0;
		for(int i=1;i<=n;++i){
			if(!S.empty()&&a[S.top()]==a[i])hash^=S.size()*val[a[i]],S.pop();
			else S.push(i),hash^=S.size()*val[a[i]];
			ans+=mp[hash]++;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：dingshengyang (赞：1)

~~管理先别审，还没写完~~已经写完了。

这个题其实可以用线段树做，代码删去调试行只有 $123$ 行，码量只有 $2.94\texttt{kb}$（其实这个量如果选手训练量大的话就不算什么）。

> 线段树啊，我最骄傲的信仰，一切垃圾算法散去之后，唯我线段树永世长存！

考虑预处理 $next_i$，表示 **$s_i \sim s_{next_i- 1}$ 是一个长度为偶数的回文串且 $next_i$ 最小。**

求出这个东西之后就可以 DP 了。$f_i = f_{next_i} + 1$。

可是如果某一个后缀就是最短偶回文串呢？这种情况下，我们考虑新建一个节点，这个节点的值不等于任何一个数（比如 $-1$）。这样有这种特殊情况的 $i$ 就满足 $next_i = n+1$。

接下来我们需要求出 $next_i$。

有一种主席树的乱搞算法（本文最终算法不是乱搞，可以证明复杂度为 $O(n \log n)$，用时 $904 \texttt{ms}$）。

比如你现在有一个栈，我们记录当栈为空的时候加入的第 $i$ 号元素。我们对于每一个 $i$ 都记录一个序列 $l_i$。

这样有什么好处呢？因为我们是按照后缀递推的，所以从前面加进来一个数，只有可能是和这些被记录的数进行消除。如果能找到这样的最小的数 $k\in l_{i + 1}$ 满足 $a_k = a_i$，中间的那些数都被 $a_i$ 在栈里垫着，在 $k$ 之前栈不可能为空，所以我们可以递推：

$l_i = i + l_k$（这里的加号表示在这里插入）。

这里用到了一个维护集合的操作，你可以用平衡树，但是太麻烦了。

然后你会发现这是一个很恶心的复杂度，如果你把 $l_k$ 一个一个插入进去的话。

然后你就需要一个可持久化，可以让你快速把 $l_k$ 拉过来。

可是问题是可持久化的平衡树比较难写，据我所知只有 FHQ Treap 和替罪羊树。可是这两个我都不会啊（其实其他例如 WBLT 也可以，但是我还是不会，我只会 Splay，但是这玩意不可以可持久化）！

于是我们可以考虑：

权值线段树可以实现平衡树的功能；

那么，可持久化权值线段树是不是也可以实现可持久化平衡树的功能呢？

答案是肯定的，而且写起来十分简单，和普通线段树差不多。

然后你就暴力跳就行了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 300005;
struct node{
    int ls,rs;
    int sum;
}tr[N * __lg(N) + 4 * N];
int idx,root[N];
int n;
int s[N];
void pushup(int u){
    tr[u].sum = tr[tr[u].ls].sum + tr[tr[u].rs].sum;
}
int build(int l,int r){
    int u = ++ idx;
    if(l == r){
        tr[u] = {0,0,0};
        return u;
    }
    int mid = (l + r) >> 1;
    tr[u].ls = build(l,mid);
    tr[u].rs = build(mid+1,r);
    pushup(u);
    return u;
}
int modify(int u,int L,int R,int x,int val){
    int p = ++idx;
    tr[p] = tr[u];
    if(L == x && R == x){
        tr[p].sum = val;
        return p;
    }else{
        int mid = (L + R) >> 1;
        if(x <= mid)tr[p].ls = modify(tr[u].ls,L,mid,x,val);
        else tr[p].rs = modify(tr[u].rs,mid+1,R,x,val);
        pushup(p);
        return p;
    }
}
int kth(int u,int L,int R,int k){
    int mid = (L + R) >> 1;
    if(L == R)return L;
    if(tr[tr[u].ls].sum >= k)return kth(tr[u].ls,L,mid,k);
    else return kth(tr[u].rs,mid+1,R,k-tr[tr[u].ls].sum);
}
int nxt[N],f[N];
void doit(){
    cin >> n;
    for(int i = 1;i <= n;i ++){
        cin >> s[i];
    }
    n ++;
    s[n] = -1;
    root[n + 1] = build(1,n);
    for(int i = n;i >= 1;i --){
        root[i] = root[i + 1];
        int ok = 0;
        int next = 0;
        for(int j = 1;j <= tr[root[i]].sum;j ++){
            if(s[kth(root[i],1,n,j)] == s[i]){
                next = kth(root[i],1,n,j);
                ok = 1;
                break;
            }
        }
        if(!ok){
            root[i] = root[n + 1];
            root[i] = modify(root[i],1,n,i,1);
        }else{
            root[i] = root[next + 1];
            root[i] = modify(root[i],1,n,i,1);
        }
        if(tr[root[i]].sum >= 2){
            nxt[i] = kth(root[i],1,n,2);
        }
        // cout << "round: " << i << endl;
        // for(int j = 1;j <= tr[root[i]].sum;j ++){
        //     cout << kth(root[i],1,n,j) << " ";
        // }
        // cout << endl << endl << endl;
        // getchar();
    }
    // for(int i = 1;i <= n;i ++){
    //     cout << nxt[i] << " ";
    // }
    // cout << endl;
    long long ans = 0;
    for(int i = n;i >= 1;i --){
        if(nxt[i])f[i] = f[nxt[i]] + 1;
        ans += f[i];
    }
    cout << ans << endl;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int T;
    cin >> T;
    while(T --){
        for(int i = 0;i <= idx;i ++){
            tr[i] = {0,0,0};
        }
        for(int i = 0;i <= n + 1;i ++){
            f[i] = 0;
            nxt[i] = 0;
            root[i] = 0;
        }
        idx = 0;
        tr[0] = {0,0,0};
        doit();
    }
    return 0;
}
```

吗？

好吧这份代码会直接 TLE。

原因：我们可以通过 $1,2,2,2,2,2,2,...$ 这样的数据把主席树维护的序列的长度卡的很长，虽然对于主席树来说没啥问题（每次只需要一次修改），但是暴力查找的时候，最后找一个找不到，找两个还是找不到，最后每一次查找都很慢。

但是这份代码对于随机数据表现良好，期望复杂度 $O(n\log n)$。

因为如果数据随机，这个栈几乎不可能被消空，主席树维护的序列也很短（接近常数级别）。

但是没有如果，这份代码就是过不了。

如何优化？

我们之前其实在用主席树的转移预处理出信息从而优化 DP 的状态转移，现在我要用主席树优化主席树的转移了！

我们对于每个 $i$，记录 $s_{i,j}$ 表示从 $i \sim n$ 之中，第一个满足 $a_{l_{i,k}} = j$ 的 $k$。

这个也是可以像上文一样用主席树维护的。考虑到我不想动态开点，我写了一个离散化，读者可以自行实现一个动态开点的版本。

最后提一下 $next$ 数组如何计算。事实上，$next_i = l_{i,2}$（$l_{i,1} = i$，到第二个就是最小偶回文串）。

这样时间复杂度就是严格的 $O(n \log n)$。这样虽然过不去 CSP 2023 S T2，但是可以拿到 $85$ pts（其实前面的乱搞也可以拿到）。

最后，因为主席树有 $2$ 棵，数组记得开大。

```cpp
// LUOGU_RID: 131727730
#include<bits/stdc++.h>
using namespace std;
const int N = 600005;
struct node{
    int ls,rs;
    int sum;
}tr[N * __lg(N) + 4 * N];
int idx,root[N];
int n;
int s[N];
void pushup(int u){
    tr[u].sum = tr[tr[u].ls].sum + tr[tr[u].rs].sum;
}
int build(int l,int r){
    int u = ++ idx;
    if(l == r){
        tr[u] = {0,0,0};
        return u;
    }
    int mid = (l + r) >> 1;
    tr[u].ls = build(l,mid);
    tr[u].rs = build(mid+1,r);
    pushup(u);
    return u;
}
int modify(int u,int L,int R,int x,int val){
    int p = ++idx;
    tr[p] = tr[u];
    if(L == x && R == x){
        tr[p].sum = val;
        return p;
    }else{
        int mid = (L + R) >> 1;
        if(x <= mid)tr[p].ls = modify(tr[u].ls,L,mid,x,val);
        else tr[p].rs = modify(tr[u].rs,mid+1,R,x,val);
        pushup(p);
        return p;
    }
}
int query(int u,int L,int R,int x){
	
    if(L == x && R == x){
        return tr[u].sum;
    }else{
        int mid = (L + R) >> 1;
        if(x <= mid)return query(tr[u].ls,L,mid,x);
        else return query(tr[u].rs,mid+1,R,x);
    }
}
int kth(int u,int L,int R,int k){
    int mid = (L + R) >> 1;
    if(L == R)return L;
    if(tr[tr[u].ls].sum >= k)return kth(tr[u].ls,L,mid,k);
    else return kth(tr[u].rs,mid+1,R,k-tr[tr[u].ls].sum);
}
int nxt[N],f[N];
int a[N];
int uni[N];
int root2[N];
void doit(){
    cin >> n;
    for(int i = 1;i <= n;i ++){
        cin >> s[i];
        uni[i] = s[i];
    }
    sort(uni + 1,uni + n + 1);
    int m = unique(uni + 1,uni + n + 1) - uni - 1;
    for(int i = 1;i <= n;i ++){
        a[i] = lower_bound(uni + 1,uni + m + 1,s[i]) - uni;
    }
    n ++;
    s[n] = -1;
    a[n] = 0;
    root[n + 1] = build(1,n);
    root2[n + 1] = build(1,m);
    for(int i = n;i >= 1;i --){
        root[i] = root[i + 1];
        root2[i] = root2[i + 1];
        int next = 0;
        
        if(a[i]){
        	next = query(root2[i],1,m,a[i]);
		}
        if(!next){
            root[i] = root[n + 1];
            root[i] = modify(root[i],1,n,i,1);
            root2[i] = root2[n + 1];
            if(a[i])root2[i] = modify(root2[i],1,m,a[i],i);
        }else{
            root[i] = root[next + 1];
            root[i] = modify(root[i],1,n,i,1);
            root2[i] = root2[next + 1];
            root2[i] = modify(root2[i],1,m,a[i],i);
        }
        if(tr[root[i]].sum >= 2){
            nxt[i] = kth(root[i],1,n,2);
        }
    }
    long long ans = 0;
    for(int i = n;i >= 1;i --){
        if(nxt[i])f[i] = f[nxt[i]] + 1;
        ans += f[i];
    }
    cout << ans << endl;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int T;
    cin >> T;
    while(T --){
        for(int i = 0;i <= n + 1;i ++){
            f[i] = 0;
            nxt[i] = 0;
            root[i] = 0;
            root2[i] = 0;
        }
        idx = 0;
        tr[0] = {0,0,0};
        doit();
    }
    return 0;
}
```

---

## 作者：Aiopr_2378 (赞：1)

Solution of CF1223F Stack Exterminable Arrays

## 一、题目大意

给一个长度为 $n$ 的数列，对于其中一段子序列称为可被删除的，当且仅当按照下表顺序，按照如下要求进栈和出栈后栈为空：

- 如果当前元素等于栈顶元素，则弹出栈顶元素；

- 否则将当前元素压入栈中。

求有多少个子序列为可被删除的。

## 二、解题思路

CSP-S2023 T2 的原题，可惜考场并没有想出正确的思路。

理解题意后我们发现，我们可以枚举每一个可被删除的子序列（下面简称为“合法子序列”）的起始位置，进行栈模拟，就可以找到以这个位置开始的所有合法子序列。这是一个时间复杂度为 $O(n^2)$ 的算法。

我们考虑进行简化。如果只从第一个位置进行栈模拟，发现所有合法的子序列都有如下性质：

- 设 $p_i$ 表示栈在第 $i$ 个位置的状态，如果子序列 $l\dots r$ 是合法的子序列，则有 $p_{l-1}=p_r$，即经过合法子序列后栈的状态和未经过时一样。

考虑怎么证明这个东西。

如果 $l\dots r$ 内的数会和栈里面的数抵消。形式化地，记栈为 $S=YX$，当前合法的子序列形如 $XYYX$，两个 $X$ 或抵消，同时子序列内部重复的 $Y$ 也会抵消，最后剩下 $X$，入栈，这样栈内元素又一样了。

> 例子 $\quad$ 对于序列 `2 2 3 3 2`，子序列取区间 $[2,5]$ 时，$p_1=\{2\}$，$p_5=\{2\}$，二者相等，说明子序列 `2 3 3 2` 是合法的子序列。

那么我们就可以只进行一个堆栈模拟，记录到每个位置的 $p_i$，可以对其进行字符串哈希，再用一个哈希表记录当前以前的所有栈状态，统计每个位置与其相等的栈状态即可。复杂度 $O(n)$。

对于 `unordered_map` 类型的变量，可以使用 `<name>.reserve(_size)` 进行预制大小。

## 三、参考代码

```cpp
#include<iostream>
#include<unordered_map>
using namespace std;
#define MAXN 300005
#define mod 5323
#define p 233
typedef long long ll;
typedef unsigned long long ull;
int Q,n,s[MAXN],top,a[MAXN],num[MAXN];
ull hs[MAXN],table[MAXN],lable[MAXN];
ll ans;
const int maxx=300000;
unordered_map<ull,int> mp;
int main(){
    cin>>Q;
    table[0]=lable[0]=1;
    for(int i=1;i<=maxx;i++) table[i]=table[i-1]*mod;
    for(int i=1;i<=maxx;i++) lable[i]=lable[i-1]*p;
    while(Q--){
        cin>>n;
        for(int i=1;i<=n;i++) cin>>a[i];
        top=ans=0;
        mp.clear();
        mp.reserve(n+5);
        mp[0]++;
        for(int i=1;i<=n;i++){
            if(a[i]==a[s[top]]){
                hs[i]=hs[i-1]-table[top]*lable[a[i]];
                top--;
            }
            else{
                s[++top]=i;
                hs[i]=hs[i-1]+table[top]*lable[a[i]];
            }
            if(mp.find(hs[i])!=mp.end()) ans+=mp[hs[i]];
            mp[hs[i]]++;
        }
        cout<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：ncwzdlsd (赞：1)

> CSP-S 2023 打卡。

分治。

对于区间段的问题，考虑分治。

对于左右区间的合并，可以想到两区间组合可被消除，当且仅当两区间栈操作过程是相同的。对右区间 $[mid+1,r]$ 从左至右模拟栈操作，对左区间 $[l,mid]$ 从右至左模拟栈操作，用 `map` 和 Hash 结合维护右区间的信息，遍历左区间累加每个状态的答案即可。

时间复杂度 $O(n\log^2 n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;

const int base=388211,maxn=3e5+5;
int a[maxn],s[maxn],top;
ull ha[maxn];
ll ans;
map<ull,int> mp;

void solve(int l,int r)
{
    if(l>=r) return;
    int mid=(l+r)/2;
    solve(l,mid),solve(mid+1,r);
    mp.clear(),top=0,ha[0]=0; 
    for(int i=mid+1;i<=r;i++)
    {
        if(top&&s[top]==a[i]) top--;
        else s[++top]=a[i],ha[top]=ha[top-1]*base+a[i];
        mp[ha[top]]++;
    }
    top=0,ha[0]=0;
    for(int i=mid;i>=l;i--)
    {
        if(top&&s[top]==a[i]) top--;
        else s[++top]=a[i],ha[top]=ha[top-1]*base+a[i];
        ans+=mp[ha[top]];
    }
}

int main()
{
    int T;cin>>T;
    while(T--)
    {
        int n;cin>>n;
        for(int i=1;i<=n;i++) cin>>a[i];
        ans=0,solve(1,n),cout<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：封禁用户 (赞：1)

### 题目传送门

[CF1223F](https://www.luogu.com.cn/problem/CF1223F)

[CSP-S 2023 T2](https://www.luogu.com.cn/problem/P9753?contestId=140859)

### 分析

这道题似乎借鉴了 CSP-S 2023 T2 的想法。

开一个栈，把字符一个一个地压入栈，实时记录栈的状态，如果加入的元素与栈顶元素相同就一起弹出。发现，如果栈的状态在前后相同，则中间必有一个合法的字符串。

所以我们记录下栈状态的哈希值，每次累计该状态在前面的出现次数，并将出现次数加一。

用 `map` 和 `unordered_map` 的时间复杂度分别是 $O(Tn\log n)$ 和 $O(Tn)$。

### 代码

抢到了几秒的最优解。

```cpp
#include <bits/stdc++.h>
using namespace std;
namespace IO
{
	constexpr int fsize = 1<<24;
	#define getchar() ((IO::si!=IO::ti||(IO::ti=(IO::si=IO::input)+fread(IO::input,1,IO::fsize,stdin))),IO::si!=IO::ti?*(IO::si++):EOF)
	#define putchar(c) ((IO::out.so!=IO::out.to||(fwrite(IO::out.output,1,IO::fsize,stdout),IO::out.so=IO::out.output)),*(IO::out.so++)=c)
	char input[fsize],*si = input,*ti = input;
	struct output_stream
	{
		char output[fsize],*so = output,*to = output + fsize;
		inline ~output_stream()
		{
			if(so == output) return;
			fwrite(output,1,so-output,stdout);
			so = output;
		}
	}out; 
	template<typename T>inline void read(T &x)
	{
		int c = getchar();
		x = 0;
		while(c < 48||c > 57) c = getchar();
		while(48 <= c&&c <= 57)
		{
			x = (x<<3)+(x<<1)+(c^48);
			c = getchar();
		}
	}
	template<typename T>inline void write(T x)
	{
		static int c[40],cnt = 0;
		if(!x) putchar(48);
		while(x) c[++cnt] = x%10^48,x /= 10;
		while(cnt) putchar(c[cnt--]);
	}
}
using IO::read;
using IO::write;
#define F(i,a,b) for(register int i=a;i<=b;++i)
#define ull unsigned long long
unordered_map<ull,int> mp;
ull p[300010],ans;
int t[300010],T,n,top;
int main()
{
	read(T);
	while(T--)
	{
		read(n);
		mp.clear();
		mp[0] = 1,top = 0,ans = 0;
		F(i,1,n)
		{
			int x;
			read(x);
			if(top&&x == t[top]) --top;
			else p[top + 1] = (p[top] << 18) + p[top] + x,t[++top] = x;
			ans += mp[p[top]]++;
		}
		write(ans);	
		putchar(10);
	}
	return 0;
}
```



---

## 作者：LJ07 (赞：0)

原神，启动！场上的做法。判断一个子串怎么做，是不是用栈模拟一下，栈顶相同就弹出，不相同就加入。

然后扫描 $r$，维护 $1\cdots r$ 的栈，发现这些栈其实能构成 trie 树。每次加入一个字符相当于砍掉一个儿子，然后再把整个树接到这个儿子上。其中我们只需要多开一个表示空的儿子节点，维护子树大小。

随便模拟一下就很容易能做到 $O(n\sum)$。能过 T2 的代码：

```cpp
const int N = 2e6;
int n, ct;
int son[N * 2 + 100][27], rt[27], siz[N * 2 + 100]; 
string s;
LL ans;

signed main()
{
	cin.tie(0)->sync_with_stdio(0);
	cin >> n >> s;
	for (int i = 0; i < n; ++i) {
		int now = s[i] - 'a';
		if (!rt[26])  { 
			rt[26] = ++ct;
		}
		++siz[rt[26]];
		++ct; 
		for (int j = 0; j < 27; ++j) {
			if (j != now) { 
				son[ct][j] = rt[j];
				siz[ct] += siz[rt[j]];
				rt[j] = son[rt[now]][j];
			}
		}
		rt[now] = ct;
		ans += siz[rt[26]]; 
	}
	cout << ans;
	return 0;
}

```

有人说做不了大值域。但是事实上就是一些单点修改，可以使用 map 做到 $O(n\log n)$。不卡 um 的一集。

```cpp
const int N = 3e5;
int n, a[N + 5], ct, root, siz[N * 2 + 50];
unordered_map<int, int> son[N * 2 + 50];
LL ans;

void work()
{
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}
	root = ++ct;
	for (int i = 0; i < n; ++i) {
		if (!son[root][0])  { 
			son[root][0] = ++ct;
		}
		++siz[son[root][0]];
		++siz[root];
		int t = son[root][a[i]];
		if (!t) {
			t = son[root][a[i]] = ++ct;
		}
		siz[root] -= siz[t];
		siz[t] += siz[root];
		son[t][a[i]] = root;
		root = t;
		ans += siz[son[root][0]]; 
	}
	cout << ans << '\n';
}
```

这只是 trie 树做法的一种。当然还有更好的 trie 做法。

---

## 作者：cszhpdx (赞：0)

[link](https://www.luogu.com.cn/problem/CF1223F)

我来提供一种愚蠢质朴且暴力的做法。

设计状态 $f_i$ 表示以 $i$ 为结尾的合法子串个数，令 $g_i$ 为满足 $[j,i]$ 子串符合题意的 $j$ 的最大值。

显然 $f_i=f_{g_i-1}+1$，我们发现这个 $a_{[g_i,i]}$ 括号序列肯定长成 `a[i](某个合法串)(某个合法串)...(某个合法串)a[i]` 这样，可以从 $i-1$ 开始，每次 $x\leftarrow g_x-1$ 这样跳到第一个所求的 $a_i$ 就行。

但是显然复杂度会炸，我们考虑把跳的过程抽象成一棵树，$i$ 号点和它的父亲 $g_i-1$ 连边，每个点有个颜色 $a_i$，我们的询问就相当于问一个点往上跳的过程中遇到的第一个颜色 $c$ 的节点。

这里有很多维护方法，因为我比较愚蠢，我选择了主席树，维护每个点到根的路径上某个特定颜色的节点中深度最大的点，然后就做完了。

时间复杂度 $O(n\log n)$，空间复杂度 $O(n\log n)$。

代码写的不优美，但是还是放上来比较好吧：

```cpp
#include<bits/stdc++.h>
#define mem(a, x) memset(a, x, sizeof(a))
#define rps(i, b, e) for(int i=(b);i<=(e);i++)
#define prs(i, e, b) for(int i=(e);i>=(b);i--)
#define rpg(i, g, x) for(int i=g.head[x];i;i=g.e[i].nxt)
#define opf(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)
using namespace std;

namespace cszhpdx {
template<class T>
inline void read(T &x) {
	x=0;
	bool f=false;
	char c=getchar();
	while(!isdigit(c))f|=(c=='-'), c=getchar();
	while(isdigit(c))x=x*10+(c-'0'), c=getchar();
	if(f)x=-x;
}
const int NR=3e5+10, VR=6e6;
typedef long long LL;
int n, a[NR];
int lc[VR], rc[VR], cnt;
pair<int, int>mx[VR];
void clr() {
    rps(i, 1, cnt)lc[i]=rc[i]=mx[i].first=mx[i].second=0;
    cnt=0;
}
int upd(int x, int l, int r, int p, pair<int, int>v) {
    int nx=++cnt;
    lc[nx]=lc[x], rc[nx]=rc[x], mx[nx]=max(mx[x], v);
    if(l==r)return nx;
    int mid=(l+r)/2;
    if(p<=mid)lc[nx]=upd(lc[x], l, mid, p, v);
    else rc[nx]=upd(rc[x], mid+1, r, p, v);
    return nx;
}
pair<int, int>query(int x, int l, int r, int s, int t) {
    if(x==0)return make_pair(0, 0);
    if(l>=s && r<=t)return mx[x];
    pair<int, int>res(0, 0);
    int mid=(l+r)/2;
    if(mid>=s)res=max(res, query(lc[x], l, mid, s, t));
    if(mid<t)res=max(res, query(rc[x], mid+1, r, s, t));
    return res;
}
int f[NR], g[NR], rt[NR], dep[NR];
void work() {
    clr();
    read(n);
    rps(i, 1, n)read(a[i]), f[i]=g[i]=rt[i]=dep[i]=0;
    LL ans=0;
    rps(i, 1, n) {
        g[i]=query(rt[i-1], 1, n, a[i], a[i]).second;
        if(g[i]>0) {
            dep[i]=dep[g[i]-1]+1;
            rt[i]=upd(rt[g[i]-1], 1, n, a[i], make_pair(dep[i], i));
            f[i]=f[g[i]-1]+1;
        }
        else rt[i]=upd(rt[i], 1, n, a[i], make_pair(0, i));
        ans+=f[i];
    }
    printf("%lld\n", ans);
}
int main() {
    int T;read(T);
    while(T--)work();
    return 0;
}
}
int main() {
	return cszhpdx::main();
}
```

---

## 作者：CQ_Bob (赞：0)

## 分析

接着[这个](https://www.luogu.com.cn/blog/993404/p9753-csp-s-2023-xiao-xiao-le-ti-xie)说。

现在我们需要优化 $\mathit{nxt}_{i}$。重新定义一下，$\mathit{nxt}_{i,j}$ 表示在后 $i$ 个数中，$j$ 第一次出现的位置，且 $[i+1,\mathit{nxt}_{i+1,a_i}-1]$ 是一个合法串。这玩意很像一个 DP，所以完全可以按照 DP 的转移思路转移：$\mathit{nxt}_{i,j}=\min(i|a_i=j,\mathit{nxt}_{\mathit{nxt}_{i,a_i}+1,j})$。但这个转移的前提是在 $\mathit{nxt}_{i+1}$ 中存在 $1 \le \mathit{nxt}_{i+1,a_i} \le n$。因为只有在这种情况，我们才能保证转移后的 $\mathit{nxt}$ 合法。

对于转移，直接交换再把 $a_i$ 更新就能做到 $O(1)$ 了。正确性可以自己想想。

这题的话，就是把字符串变成数字，复杂度 $O(n \log n)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline

const int N=3e5+10;
int n,a[N];
int f[N];
map<int,int> nxt[N];

il void solve(){
    cin>>n;
    for(re int i=1;i<=n;++i) cin>>a[i],f[i]=0,nxt[i].clear();
    nxt[n+1].clear(),f[n+1]=0;
    int ans=0;
    for(re int i=n;i>=1;--i){
        if(nxt[i+1].count(a[i])){
            f[i]=f[nxt[i+1][a[i]]+1]+1;
            swap(nxt[i],nxt[nxt[i+1][a[i]]+1]);
        }
        nxt[i][a[i]]=i;
    }
    for(re int i=1;i<=n;++i) ans+=f[i];
    cout<<ans<<"\n"; 
}

signed main(){
    int t;cin>>t;while(t--)
    solve();
    return 0;
}
```


---

## 作者：zifanwang (赞：0)

这题是 CSP-S 2023 T2 的加强版。

区间 $[l,r]$ 可以消除当且仅当 $a_l=a_r$ 且 $[l+1,r-1]$ 可消除，或存在一个数 $k(l\le k\le r)$ 满足 $[l,k],[k+1,r]$ 都可消除。

所以一个可消除区间肯定是由若干个左右端点颜色（$a_i$ 是第 $i$ 个点的颜色）相同的可消除连续子区间拼起来的。

考虑对于每个右端点 $i$ 求出最近的左端点使得对应子区间满足条件，记为 $l_i$。记 $f_i$ 为 $i$ 作为右端点的合法子区间个数，那么答案就是 $\sum f_i$，易得 $f_i=f_{l_i-1}+1$。

很明显 $a_{l_i}=a_i$，不然就不满足左端点最靠右。由此显然可得区间 $[l_i+1,i-1]$ 可消除，也就是说从 $p=i-1$ 开始不断地跳 $p=l_p-1$，最终一定可以跳到 $p=l_i$。

于是可以对每个点用一个 `map` 维护每种颜色往左边跳到的第一个这种颜色的点的编号。每个点 $i$ 的 `map` 都需要继承 $l_i-1$ 的 `map`，可以直接 `swap`，因为后面 $l_i-1$ 的 `map` 就不会再用到了。

时间复杂度 $O(n\log n)$。

参考代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define mxn 300003
#define rep(i,a,b) for(int i=a;i<=b;++i)
#define rept(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int q,n,a[mxn],p[mxn];
ll ans,f[mxn];
map<int,int>mp[mxn];
signed main(){
	scanf("%d",&q);
	while(q--){
		scanf("%d",&n);
		rep(i,1,n)scanf("%d",&a[i]),mp[i].clear(),f[i]=p[i]=0;
		ans=0;
		rep(i,1,n){
			auto it=mp[i-1].find(a[i]);
			if(it!=mp[i-1].end()){
				p[i]=it->second-1;
				f[i]=f[p[i]]+1,ans+=f[i];
				swap(mp[i],mp[p[i]]);
			}
			mp[i][a[i]]=i;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：arrow_king (赞：0)

# 题意

在一段序列中，如果有两个相同的数相邻则这两个数可以被删除。

如果经过某些删除操作能使得某个序列被删除成空串，则称这个序列可被删除。

请求出一个序列 $a$ 的“可被删除”的字串个数。

$n\le3\times10^5$。

# 思路

考虑如何判断一个序列可被删除。

用栈来维护，初始时栈为空，若当前栈为空或栈顶元素与新的字符不同，那么将新的字符入栈；否则弹栈。如果最后栈是空的，那么这个序列就可被删除。

那么考虑怎么对区间做这个操作。

朴素的想法是 $\mathcal O(n^3)$ 的。

其实如果区间 $[l,r]$ 可以被删除，那么注意到在 $r$ 时刻与 $l-1$ 时刻，整个栈是完全一样的。

那么就可以存下栈，然后对栈的种类进行判断。显然如果某种栈出现了 $k$ 次，对应的区间就有 $\dfrac{k(k-1)}{2}$ 个。

存栈的空间复杂度是 $\mathcal O(n^2)$ 的，怎么办？

哈希就行了，动态地维护整个栈的哈希值，丢到 map 里。

这样时间就是 $\mathcal O(n\log n)$ 的了。

# 代码

注意哈希的模数选取和进制选取，双模可以过，但是时间上有可能吃不住（例子：双模 95pts [P9753](https://www.luogu.com.cn/problem/P9753?contestId=140859)，T 了一个点）；模数不好可能 WA。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<map>
using namespace std;
#define il inline
#define ll long long
#define N 2000005
il ll read() {
	ll x=0,f=1;char c=getchar();
	while(c<'0'||c>'9') {if(c=='-') {f=-1;} c=getchar();}
	while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
const ll mod=99824435319260817;
ll n,top;
unsigned ll bs[N],has[N];
ll s[N];
ll st[N];
map<unsigned ll,ll> mp;
int main() {
    ll t=read();
    while(t--) {
        n=read();
		for(int i=1;i<=n;++i) s[i]=read();
	    top=0;
	    mp.clear();
		bs[0]=1;
		for(int i=1;i<=n;++i) bs[i]=bs[i-1]*mod;
		++mp[0];
		for(int i=1;i<=n;++i) {
			if(top==0||s[st[top]]!=s[i]) {
				st[++top]=i;
				has[top]=has[top-1]+bs[top]*s[i];
			}
			else --top;
			mp[has[top]]++;
		}
		ll ans=0;
		for(auto i:mp) ans+=i.second*(i.second-1)/2;
		printf("%lld\n",ans);
	}
	return 0;
}

```

---

## 作者：AsiraeM (赞：0)

因为题目中的入栈/出栈与括号匹配等价，所以考虑括号序列问题的经典处理方法——取前缀和。  
按题目中的方法模拟，求出处理了序列的每个前缀 $s_i$ 时栈的状态，  
注意到，因为没有“左/右括号”之分，所以如果序列的两个前缀 $s_i,s_j$ 对应的状态相同，那么 $a_{i+1}$ 到 $a_j$ 这一段就是可以被消除的，  
也就是说，可以统计出栈的每种状态的出现次数进行计算。  

在实现上，可以通过字符串哈希判断两个前缀对应的状态是否相同，但众所周知，CF出题人很喜欢卡字符串哈希，为了保证判断完全准确，可以使用字典树模拟入栈/出栈的过程，  
对于第 $i$ 个数，出栈（即 $a_i$ 等于栈顶的数时）就回到当前结点的父亲，入栈就走到当前结点与 $a_i$ 对应的孩子，  
每次走到一个结点就把答案加上这个结点的计数器，并将这个结点的计数器加1。

这一题的字符集大小是 $O(n)$ 的，不能使用普通的字典树写法，应该用哈希表存下字典树的每一条边，这样可以保证 $O(n)$ 的时间复杂度。

代码：
```cpp
//Talk is cheap.Show me the code.
#include<bits/stdc++.h>
namespace xcy{
typedef long long ll;
const int MAXN=300005;
const ll MOD=5000007;
ll a[MAXN],b[MAXN],c[MAXN],real[MAXN+MOD],hsh[MAXN+MOD],fa[MAXN],num[MAXN],st[MAXN],t,cnt,n,q,i,j,k,ans;

inline void fread(ll &X){X=0;char C=getchar();while(!isdigit(C))C=getchar();while(isdigit(C))X=(X<<1)+(X<<3)+(C^48),C=getchar();}
inline void fout(ll X){if(X<0)X=-X,putchar('-');if(!X){putchar('0'),putchar(' ');return;}char C[25]{};ll Len=0;while(X)C[++Len]=X%10+'0',X/=10;for(;Len;--Len)putchar(C[Len]);putchar(' ');}
inline ll hs(ll X,ll Y){X=X*n+Y;ll I=X%MOD+1;while(real[I]&&real[I]!=X)++I;if(real[I])return I;real[I]=X;hsh[I]=++cnt;return 0;}

int mian()
{
	fread(q);while(q--){
	fread(n);cnt=t=ans=0;
	for(i=1;i<=n;++i)fread(a[i]);
	num[0]=1;
	for(i=1,j=0;i<=n;++i)
	{
		if(t&&a[i]==st[t])--t,j=fa[j];
		else
		{
			k=hs(j,a[i]);
			b[i]=hs(j,a[i]);
			fa[hsh[b[i]]]=j;
			j=hsh[b[i]];
			st[++t]=a[i];
		}
		ans+=num[j];++num[j];c[i]=j;
	}fout(ans);putchar('\n');
	for(i=1;i<=n;++i)real[b[i]]=num[c[i]]=0;
	}return 0;
}}
int main(){return xcy::mian();}
```


---

## 作者：Eznibuil (赞：0)

为什么没有 Trie？为什么都是哈希？

考虑维护从头开始到每个位置的栈序列。显然栈序列相同则一定可消。考虑用一个类似 map 的东西记录每一种栈序列之前出现次数，然后对于每个栈序列先把之前出现次数累加进答案，再自增一下。

于是建 Trie。每个节点保存一个 map 即可。于是整个 Trie 形成了更大的 map，但是指针在上面的移动是 $O(\log n)$ 的。

算是 CF 比较简单的 2F/1D 吧。时间复杂度 $O(n\log n)$。

Upd：unordered_map 不会被卡，此时时间复杂度 $\Omega(n)$。

下面代码改自 CSP-S 2023 消消乐的考场代码。
```cpp
#include<iostream>
#include<map>
struct Trie
{
	struct node
	{
		int t;
		node*fa;
		std::map<int,node*>m;
	}*root,al[2000003],*pa;
	Trie(){clear();}
	void clear(){pa=al,root=newnode();}
	node*newnode(){return pa->t=0,pa->fa=nullptr,pa->m.clear(),pa++;}
}trie;
int main()
{
	std::cin.tie(nullptr)->sync_with_stdio(0);
	int t;
	std::cin>>t;
	while(t--)
	{
		int n;
		std::cin>>n,trie.clear();
		Trie::node*p=trie.root;
		p->t++;
		long long ans=0;
		for(int i=0;i<n;i++)
		{
			int a;
			std::cin>>a;
			if(p->fa==nullptr||!p->fa->m.count(a)||p->fa->m[a]!=p)
			{
				if(!p->m.count(a))
					(p->m[a]=trie.newnode())->fa=p;
				p=p->m[a];
			}
			else
				p=p->fa;
			ans+=p->t,p->t++;
		}
		std::cout<<ans<<'\n';
	}
	return 0;
}
```
关于栈序列相同则一定可消的证明：考虑折线图，并将折线染色为对应的数字。将栈序列相同考虑为截取了中间的折线。显然对于这么一段折线可以把所有往下折的 V 形翻成往上折的 Λ 形，所以一定能得到一个合法的折线。

---

