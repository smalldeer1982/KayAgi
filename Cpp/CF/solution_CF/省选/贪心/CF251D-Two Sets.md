# Two Sets

## 题目描述

Little Petya likes numbers a lot. Recently his mother has presented him a collection of $ n $ non-negative integers. There's only one thing Petya likes more than numbers: playing with little Masha. He immediately decided to give a part of his new collection to her. To make the game even more interesting, Petya decided to give Masha such collection of numbers for which the following conditions fulfill:

- Let's introduce $ x_{1} $ to denote the $ xor $ of all numbers Petya has got left; and let's introduce $ x_{2} $ to denote the $ xor $ of all numbers he gave to Masha. Value $ (x_{1}+x_{2}) $ must be as large as possible.
- If there are multiple ways to divide the collection so that the previous condition fulfilled, then Petya minimizes the value $ x_{1} $ .

The $ xor $ operation is a bitwise excluding "OR", that is denoted as "xor" in the Pascal language and "^" in C/C++/Java.

Help Petya divide the collection as described above. If there are multiple suitable ways to divide it, find any of them. Please note that after Petya gives a part of his numbers to Masha, he may have no numbers left. The reverse situation is also possible, when Petya gives nothing to Masha. In both cases we must assume that the $ xor $ of an empty set of numbers equals 0.

## 样例 #1

### 输入

```
6
1 2 3 4 5 6
```

### 输出

```
2 2 2 2 2 2
```

## 样例 #2

### 输入

```
3
1000000000000 1000000000000 1000000000000
```

### 输出

```
2 2 2
```

## 样例 #3

### 输入

```
8
1 1 2 2 3 3 4 4
```

### 输出

```
1 2 1 2 2 2 1 2
```

# 题解

## 作者：荣耀火影 (赞：5)

因为本题翻译得不太完整，所以在此给出较为完整的翻译过的题目。  
#### [集合](https://www.luogu.org/problemnew/show/U63338)     
我们可以先把所有数字的异或和$all$求出来。在二进制中，第$i$位如果有奇数个$1$，那么$all$这一位一定为$1$，第$i$位如果有偶数个$1$，那么$all$这一位一定为$0$。题目表示要让$x1+x2$尽可能大，符合的话要让$x1$尽可能小。所以，如果$all$第$i$位为$1$，说明这一位上面有奇数个$1$，我们就可以分给小明偶数个，给小刚奇数个，这样就会为答案增加$2^i$的贡献；如果$all$第$i$位为$0$，说明这一位上面有偶数个$1$，我们就可以分给小明奇数个，也给小刚奇数个，这样就会为答案增加$2*2^i$的贡献。这里要注意一点，因为高位的影响比低位要大，所以我们要尽量满足高位，也就是从高位往低位扫。                 
这样我们就可以得到$62$个异或方程（$all$在二进制下最多有$62$位）。         
$a_{1,1}*x_{1}\oplus a_{2,1}*x_{2}\oplus ...a_{n,1}*x_{n}=f_{1}$              
$a_{1,2}*x_{1}\oplus a_{2,2}*x_{2}\oplus ...a_{n,2}*x_{n}=f_{2}$                
$a_{1,3}*x_{1}\oplus a_{2,3}*x_{2}\oplus ...a_{n,3}*x_{n}=f_{3}$            
$......$                 
$a_{1,n}*x_{1}\oplus a_{2,n}*x_{2}\oplus ...a_{n,n}*x_{n}=f_{n}$            
其中，$a_{i,j}$表示第$i$个数的第$j$位是否为$1$；$\oplus$表示异或；若这一位一共有奇数个$1$，那么$f$的值为$0$,否则为$1$；$x_{i}$表示第$i$个数是否给小刚，若给小刚，则$x_{i}$为$0$，否则$x_{i}$为$1$。                  
我们可以用高斯消元法来将这些方程的根解出来。                    
详细见程序注释。                        
```cpp
#include<cstdio>
#include<bitset>
using namespace std;
#define LL long long
LL n,a[100010],pos[65],all,tot,res[100010];
//pos[i]表示第i个方程第一个系数为1的是第几项。
//tot表示方程数。 
bitset<100010>f[65];//f用于存储每个方程的系数及结果。
int main()
{
    scanf("%lld",&n);
    for(LL i=1;i<=n;i++)
    {
        scanf("%lld",&a[i]);
        all^=a[i];          //求出所有数的异或和。
    }
    for(LL k=0;k<2;k++)     //奇数、偶数分开处理。
    for(LL i=62;i>=0;i--)
    if(((all>>i)&1)==k)
    {
        tot++;              
        for(LL j=1;j<=n;j++)
        if((a[j]>>i)&1) f[tot][j]=1;
        f[tot][n+1]=k^1;
        for(LL j=1;j<tot;j++)
        if(f[tot][pos[j]]) f[tot]^=f[j];  //用高斯消元法维护。
        pos[tot]=0;
        for(LL j=1;j<=n;j++)
        if(f[tot][j])
        {
            pos[tot]=j;
            break;
        }
        if(!pos[tot]) 
        {
            tot--;
            continue;
        }                //如果这个方程中没有系数为1，就把这个方程扔了。
        for(LL j=1;j<tot;j++)
        if(f[j][pos[tot]]) f[j]^=f[tot];  //用高斯消元法维护。
    }
    for(LL i=0;i<=62;i++) res[pos[i]]=f[i][n+1]; //将方程的根弄上正确的位置。
    for(LL i=1;i<=n;i++) printf("%lld ",2-res[i]);
    return 0;
}
```


---

## 作者：chenxia25 (赞：4)

考虑线性基求出来之后尝试发明一个针对这题这个双重关键字问题的按位贪心方法。

首先发现两组异或和是确定的 $S$，如果第一组是 $x$，第二组就是 $x\oplus S$，答案的两个关键字此时就是 $(x+x\oplus S,x)$。

从高往低看，如果 $S$ 当前这一位是 $0$，那么如果 $x$ 这一位取 $1$，$x\oplus S$ 这一位也是 $1$，在这一位对第一关键字贡献是 $2^{i+1}$；如果都取 $0$，那么即使后面位全部取 $1$，那最大也只能是 $2(2^i-1)$。所以如果 $S$ 当前这一位是 $0$，$x$ 这一位一定是要取 $1$ 的（如果有得选的话）。

但如果 $S$ 当前这一位是 $1$ 那就值得犹豫了，因为无论 $x$ 取 $0$ 还是 $1$ 对第一关键字的贡献都是一样的，如果立刻考虑第二关键字应该是要取 $0$ 的。但关键是这一位取或不取对后面有影响啊，我们不知道取 $0$ 会不会使得以后第一关键字变逊了，这就不好办了。

其实担心的东西就是现在考虑第二关键字会不会对第一关键字产生影响。那说明这个按位贪心还不合格，即使是从高往低位贪心仍然排除不掉后效性。那可以把那些影响第一关键字的位——$S$ 为 $0$ 的位提到前面来决定完之后，再去管第二关键字。所以只需要把各位的地位换一下然后求线性基贪心即可。

求出 $x$ 的值之后还要还原出在原数组里的选择。这个就是标准的高斯消元解矩阵方程了。虽说线性基和高斯消元本质上是一样的，但是线性基是横着高斯消元啊……终究取代不了高斯消元。所以还要写个 `bitset` 优化高消，总复杂度线对。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define mp make_pair
#define X first
#define Y second
const int inf=0x3f3f3f3f3f3f3f3f;
const int N=100010;
int n,xsm;
int a[N];
int b[N],w[N];
bool cmp(int x,int y){
	if((xsm>>x&1)!=(xsm>>y&1))return (xsm>>x&1)>(xsm>>y&1);
	return x<y;
}
void insert(int x){
	for(int i=60;~i;i--)if(x>>w[i]&1)
		if(b[w[i]])x^=b[w[i]];
		else{b[w[i]]=x;break;}
}
bitset<N> mt[70];
void gauss(){
	for(int i=1;;i++){
		pair<int,int> p(inf,inf);
		for(int j=i;j<=61;j++)if(mt[j].any()){
			int x=mt[j]._Find_first();
			p=min(p,mp(x,j));
		}
		int col=p.X,row=p.Y;
		if(col==inf)break;
		swap(mt[i],mt[row]);
		for(int j=1;j<=61;j++)if(i!=j&&mt[j][col])mt[j]=mt[j]^mt[i];
	}
}
int otp[N];
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		scanf("%lld",a+i);
		xsm^=a[i];
	}
	for(int i=0;i<=60;i++)w[i]=i;
	sort(w,w+61,cmp);
	for(int i=1;i<=n;i++)insert(a[i]);
	int ans=0;
	for(int i=60;~i;i--)
		if(!(xsm>>w[i]&1)){
			if(!(ans>>w[i]&1))ans^=b[w[i]];
		}
		else{
			if(ans>>w[i]&1)ans^=b[w[i]];
		}
//	cout<<ans<<"!\n";
	a[++n]=ans;
	for(int i=1;i<=n;i++)for(int j=1;j<=61;j++)if(a[i]>>j-1&1)mt[j].set(i);
	gauss();
	for(int i=1;i<=61;i++)if(mt[i].any()){
		int x=mt[i]._Find_first();
		if(mt[i][n])otp[x]=1;
	}
	for(int i=1;i<n;i++)printf("%d ",otp[i]?1:2);
	return 0;
}
```



---

## 作者：tzc_wk (赞：4)

[题面传送门](https://www.luogu.com.cn/problem/CF251D)

题意：

你有一个可重集 $S=\{a_1,a_2,\dots,a_n\}$，你要把它划分成两个可重集 $S_1,S_2$ 使得 $S$ 中每个元素都恰好属于 $S_1$ 与 $S_2$ 之一。

记 $X_1$ 为 $S_1$ 中所有元素的异或和，$X_2$ 为 $S_2$ 中所有元素的异或和。

最大化 $X_1+X_2$，如果有多种分配方案，再最小化 $X_1$。

$n \in [1,10^5],a_i \in [1,10^{18}]$

暑假省选班讲过这道题，当时听得一脸懵B，还问lxr为什么线性基本质上就是高斯消元。。。。。。wtclwtcl

设 $X=a_1 \oplus a_2 \oplus a_3 \oplus\dots\oplus a_n$，那么显然有 $X_1\oplus X_2=X$。

考虑 $X$ 二进制上的每一位，如果 $X$ 的第 $i$ 位为 $1$，那么意味着它只能拆成 $0$ 和 $1$，不会对 $X_1+X_2$ 产生影响。

但如果 $X$ 的第 $i$ 位为 $0$，那么它可以拆成 $0,0$ 或者 $1,1$，我们的目标是让 $X_1+X_2$ 尽可能大，我们就要尽量选择 $1,1$，也就是要尽量让 $X_1$ 的第 $i$ 位为 $1$。

我们假设 $n$ 个未知数 $x_1,x_2,\dots,x_n$，$x_i=1$ 表示 $i$ 被分配到第一堆，$x_i=0$ 表示 $i$ 被分配到第二堆。

那么 $X_1$ 的第 $b$ 位为 $1$ 等价于一个异或方程 $t_1x_1\oplus t_2x_2\oplus\dots\oplus t_nx_n=1$，其中 $t_i$ 表示 $a_i$ 二进制下的第 $b$ 位是否为 $1$。

具体地来说，我们找到 $X$ 中最高的为 $0$ 的二进制位 $b$，根据之前的推论可以列出一个异或方程，如果该异或方程有解，那么我们肯定要在这一位上放 $1$。因为如果你在这一位上放 $1$，哪怕后面都是 $0$，那 $X_1+X_2$ 也有 $2^{b+1}$，而如果你在这一位上放 $0$，哪怕后面都放 $1$，结果也只有 $2^{b+1}-2$。

我们考虑这样的贪心做法：从高位向低位枚举每一个 $X$ 二进制下为 $0$ 的二进制位 $b$，我们尝试着在这一位上放 $1$，如果存在一种方案，它既能够满足前面的条件（在第 $b$ 位前面放 $1$ 的位都对应一个异或方程，把它们联立起来得到的异或方程组），那么我们就在这一位上放 $1$，否则就在这一位上放 $0$。

最大化 $X_1+X_2$ 之后，我们再考虑 $X_1$ 尽量小这个条件。这时候 $X$ 为 $1$ 的二进制位就要派上用场了。对于 $X$ 二进制下为 $1$ 的位，它又可以细分为第 $1$ 堆分配 $0$，第 $2$ 堆分配 $1$，以及第 $1$ 堆分配 $1$，第 $2$ 堆分配 $0$。我们肯定希望第一堆分配地尽可能少，于是我们重复一遍前面的操作，找到一个 $1$ 位就尝试填 $0$，就可以了。

于是我们有了优秀的 $n \log^3a_i$ 的做法，每次就联立出一个异或方程组，然后高斯消元判断这个异或方程组是否有解。

但其实并不用每次都重新消一遍，对于每个新的异或方程，都用前面的方程消去它的最高位（类似于线性基？）。这样是 $n\log^2a_i$ 的，再注意到每一位系数都是 $0/1$，可以用 ```bitset``` 再搞掉一个 $\log$。

代码就不放出来了，和楼下比较像，只是觉得楼下讲得不太清楚就特意写了篇题解

---

## 作者：hyman00 (赞：3)

首先记 $s=\oplus_{i=1}^{n}a_i,p=\oplus_{i\in S_1}a_i,q=\oplus_{i\in S_2}a_i$ ，可以发现 $s=p\oplus q$。

分每一位考虑：

- 如果 $s_i=1$，那么 $p_i+q_1$ 一定是 $1$，这一位对 $p+q$ 的和没有影响。

- 如果 $s_i=0$，那么我们需要尽可能最大化 $p_i$ 

由于要让 $p$ 尽可能小，在 $s_i=1$ 的位置要最小化 $p_i$。

这时，线性基的做法很明显了，只需要重新对每一位定义一个顺序和大小关系即可。

---

其实如果看 $q_i$ 会更简洁，因为在 $s_i=1$ 的位置最小化 $p_i$ 其实就是最大化 $q_i$，这样就是一个重新定义了数位权重的线性基。

---

这个题要求输出方案，在求线性基的过程中，每次加入一个数的时候，需要先跑一遍检查是否需要更新，如果需要则用 bitset 维护使用了哪些数。

检查的复杂度是 $O(n\log A)$ 的，但只有 $O(\log A)$ 次会更新，更新是 $O(\log^2A\times \frac{n}{\omega})$ 的。

统计答案是 $O(\log w\times \frac{n}{\omega})$ 的。

---

总复杂度大约一个 log，实际跑得很快。

```c++
const int N=100005;
bitset<N>st[64];
int can[64];
int n,a[N];
vi ord;
void run(){
	cin>>n;
	int s=0;
	rep(i,n){
		cin>>a[i];
		s^=a[i]; 
	}
	for(int i=63;i>=0;i--)if(!((s>>i)&1))ord.pb(i);
	for(int i=63;i>=0;i--)if((s>>i)&1)ord.pb(i);
	rep(i,n){
		int cur=a[i];
		bool fl=0;
		for(int j:ord){
			if((cur>>j)&1){
				if(!can[j]){
					fl=1;
					break;
				}
				else{
					cur^=can[j];
				}
			}
		}
		if(fl){
			bitset<N>bst;
			bst.reset();
			bst.set(i);
			cur=a[i];
			for(int j:ord){
				if((cur>>j)&1){
					if(!can[j]){
						can[j]=cur;
						st[j]=bst;
						break;
					}
					else{
						cur^=can[j];
						bst^=st[j];
					}
				}
			}
		}
	}
	bitset<N>bst;
	int cur=0;
	for(int i:ord)if(can[i]){
		if(!((cur>>i)&1)){
			cur^=can[i];
			bst^=st[i];
		}
	}
	vi ans(n,1);
	rep(i,n)if(bst.test(i))ans[i]=2;
	for(int i:ans)cout<<i<<" ";
	cout<<"\n";
}
```

---

## 作者：littleKtian (赞：3)

讲一下这题的线性基做法吧。

这题的贪心策略另外两篇题解已经讲得很清楚了，这里就不再讲一遍了。

记第一个集合所有元素的异或和为 $x_1$，考虑在扫描的过程中如何判断 $x_1$ 在这一位是否能取到 $0/1$。

我们可以只保留所有 $a_i$ 在当前扫描到的所有数位的值（即不考虑剩余位置的影响）并插入线性基，之后我们只需要通过线性基判断 $x_1$ 在这一位能否取到 $0/1$ 即可，复杂度 $O(n\log^2a)$。

当然实际上我们不需要每次插入所有的 $a_i$ 在保留相应位时的值，可以一开始先将所有数插入一个线性基然后用这个线性基里的所有数来进行上述操作，复杂度 $O(n\log a)$。

有了 $x_1$ 再利用线性基就能很方便地求出方案了。

代码（因为压了一些东西所以可能会比较丑）。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define M 60
using namespace std;
ll t[M],w[M];int dy[M],tt;
ll t2[M];
ll a[100005],xa,x1,zt;
int n,op[100005];
ll dr()
{
	ll xx=0;char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9')xx=(xx<<1)+(xx<<3)+ch-'0',ch=getchar();
	return xx;
}
void tj(int xh,ll x)
{
	ll ww=0;
	for(int i=M-1;i>=0;i--)
	if(x&(1ll<<i))
	{
		if(t[i])x^=t[i],ww^=w[i];
		else{t[i]=x,w[i]=ww^(1ll<<tt),dy[tt++]=xh;return;}
	}
}
void tj2(ll x)
{
	for(int i=M-1;i>=0;i--)
	if(x&(1ll<<i))
	{
		if(t2[i])x^=t2[i];
		else{t2[i]=x;return;}
	}
}
int check(ll x)
{
	for(int i=M-1;i>=0;i--)
	{
		if(t2[i]&&x&(1ll<<i))x^=t2[i];
		if(x&(1ll<<i))return 0;
	}
	return 1;
}
void work()
{
	ll w1=0;
	for(int i=M-1;i>=0;i--)if(t[i]&&x1&(1ll<<i))x1^=t[i],w1^=w[i];
	for(int i=0;i<tt;i++)if(w1&(1ll<<i))op[dy[i]]=1;
}
int main()
{
	n=dr();
	for(int i=1;i<=n;i++)xa^=(a[i]=dr()),tj(i,a[i]),op[i]=2;
	for(int k=0;k<2;k++)
	for(int i=M-1;i>=0;i--)
	if(((xa>>i)&1)==k)
	{
		zt|=1ll<<i;
		memset(t2,0,sizeof(t2));
		for(int j=0;j<M;j++)tj2(t[j]&zt);
		x1^=(check(x1^((1ll^k)<<i))^(1ll*k))<<i;
	}
	work();
	for(int i=1;i<=n;i++)printf("%d ",op[i]);
}
```


---

