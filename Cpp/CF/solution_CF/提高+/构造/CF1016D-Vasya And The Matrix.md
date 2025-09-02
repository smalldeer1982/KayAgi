# Vasya And The Matrix

## 题目描述

Now Vasya is taking an exam in mathematics. In order to get a good mark, Vasya needs to guess the matrix that the teacher has constructed!

Vasya knows that the matrix consists of $ n $ rows and $ m $ columns. For each row, he knows the xor (bitwise excluding or) of the elements in this row. The sequence $ a_{1},a_{2},...,a_{n} $ denotes the xor of elements in rows with indices $ 1 $ , $ 2 $ , ..., $ n $ , respectively. Similarly, for each column, he knows the xor of the elements in this column. The sequence $ b_{1},b_{2},...,b_{m} $ denotes the xor of elements in columns with indices $ 1 $ , $ 2 $ , ..., $ m $ , respectively.

Help Vasya! Find a matrix satisfying the given constraints or tell him that there is no suitable matrix.

## 样例 #1

### 输入

```
2 3
2 9
5 3 13
```

### 输出

```
YES
3 4 5
6 7 8
```

## 样例 #2

### 输入

```
3 3
1 7 6
2 15 12
```

### 输出

```
NO
```

# 题解

## 作者：小闸蟹 (赞：3)

```cpp
// 一道构造题，比赛的时候没有弄出来，去想怎么解方程组去了，当时就应该老老实实开脑洞想构造来着
// 首先，利用异或的性质，如果矩阵中每个元素都被异或两边，那么最后的异或和肯定为0
// 然后，我们就可以开脑洞构造了：
// 首先，除了最后一行和最后一列的元素都设为0
// 接着，除了右下角那最后一个元素，其余还没被赋值的地方的元素都设为那一行（列）的异或和
// 右下角的那个元素也可以通过异或的性质推出来
#include <iostream>
#include <array>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    constexpr int MaxN = 100 + 5;
    std::array<int, MaxN> a{ 0 }, b{ 0 };

    int n, m, Ans = 0;
    std::cin >> n >> m;
    for (int i = 0; i < n; ++i)
    {
        std::cin >> a[i];
        Ans ^= a[i];
    }
    for (int i = 0; i < m; ++i)
    {
        std::cin >> b[i];
        Ans ^= b[i];
    }

    if (Ans != 0)   // 检验一下所有元素两边异或之后的结果是不是0，不是则证明无解
    {
        std::cout << "NO" << std::endl;
    }
    else
    {
        std::cout << "YES" << std::endl;

        Ans = b[m - 1]; // 先存一下最后一列的异或和，为了推出右下角的那个元素

        for (int i = 0; i < n - 1; ++i)
        {
            for (int j = 0; j < m - 1; ++j)
            {
                std::cout << 0 << ' ';  // 除了最后一行和最后一列，其余地方都是0
            }
            std::cout << a[i] << std::endl; // 最后一列的元素

            Ans ^= a[i];    // 根据最后一列的异或和推出右下角那个元素
        }
        
        for (int i = 0; i < m - 1; ++i)
        {
            std::cout << b[i] << ' ';   // 最后一行的元素
        }
        std::cout << Ans << std::endl;  // 右下角的元素
    }

    return 0;
}
```

---

## 作者：yybyyb (赞：1)

因为想睡觉，所以没有打$Edu$，所以今天来补补。  

按照二进制位拆开考虑，相当于矩阵只含有$01$，要构造一个$01$矩阵满足条件即可。  
如果是$01$矩阵，先随便把左上角$(n-1)*(m-1)$个数给填上，剩下的利用异或和直接算出来就好了。  
额外判断一下$(n,m)$位置是否合法。   
感觉这场$edu$的题目好有趣啊。  
[强行插入博客链接](https://www.cnblogs.com/cjyyb/p/9426296.html)

~~写着写着代码就变成这个鬼样子了~~
```cpp
#include<cstdio>
#include<cstdlib>
#define ll long long
#define MAX 101
inline int read()
{
	int x=0;bool t=false;char ch=getchar();
	while((ch<'0'||ch>'9')&&ch!='-')ch=getchar();
	if(ch=='-')t=true,ch=getchar();
	while(ch<='9'&&ch>='0')x=x*10+ch-48,ch=getchar();
	return t?-x:x;
}
int n,m,g[MAX][MAX],a[MAX],b[MAX];
int main()
{
	n=read();m=read();
	for(int i=1;i<=n;++i)a[i]=read();
	for(int i=1;i<=m;++i)b[i]=read();
	for(int i=0;i<30;++i)
	{
		for(int j=1;j<n;++j)
			for(int k=1;k<m;++k)g[j][k]|=1<<i;
		int s1=0,s2=0;
		for(int j=1;j<n;++j)
			if(((m-1)&1)^((bool)(a[j]&(1<<i))))s1^=1,g[j][m]|=1<<i;
		for(int j=1;j<m;++j)
			if(((n-1)&1)^((bool)(b[j]&(1<<i))))s2^=1,g[n][j]|=1<<i;
		if((((bool)(b[m]&(1<<i)))^s1)!=(((bool)(a[n]&(1<<i)))^s2)){puts("NO");exit(0);}
		if(((bool)(b[m]&(1<<i)))^s1)g[n][m]|=1<<i;
	}
	puts("YES");
	for(int i=1;i<=n;++i,puts(""))
		for(int j=1;j<=m;++j)printf("%d ",g[i][j]);
	return 0;
}

```

---

## 作者：BLuemoon_ (赞：0)

[link](https://www.luogu.com.cn/problem/CF1016D)

## 思路

每一个元素都会在列被异或一次，在行被异或一次，所以所有输入的 $a_i,b_i$ 全部异或起来不为 $0$ 则无解。

令 $\forall i\in (1,n],j\in (1,m],c_{i,j}=0$，那么 $\forall i\in (1,m],c_{1,i}=b_i,\forall j\in (1,n],c_{i,1}=a_i$。

那么只有 $c_{1,1}$ 没有确定了，根据异或的性质，确定了 $c_{1,2\sim m},a_1$ 后，$c_{1,1}$ 唯一确定，又因为已经确定了有解，此时的 $c_{1,1}$ 一定也满足 $b_1$ 的限制。

## 代码

```cpp
// BLuemoon_
#include <bits/stdc++.h>

using namespace std;
using LL = long long;

const int kMaxN = 1e2 + 5;

LL t, n, m, f[kMaxN], g[kMaxN], a[kMaxN][kMaxN], ans;

void pr(bool pr) { cout << (pr ? "YES" : "NO") << '\n'; }

int main() {
  for (t = 1; t; t--, ans) {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
      cin >> f[i], ans ^= f[i];
    }
    for (int i = 1; i <= m; i++) {
      cin >> g[i], ans ^= g[i];
    }
    if (ans) {
      return pr(0), 0;
    }
    pr(1);
    for (int i = 2; i <= m; i++) {
      a[1][i] = g[i], ans ^= a[1][i];
    }
    for (int i = 2; i <= n; i++) {
      a[i][1] = f[i];
    }
    a[1][1] = f[1] ^ ans;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        cout << a[i][j] << " \n"[j == m];
      }
    }
  }
  return 0;
}
```

---

## 作者：modfisher (赞：0)

## 思路
不同二进制位之间相互独立，所以对每一位分别构造即可。

设当前在处理第 $k$ 位，记 $f_i$ 为 $a_i$ 这一位的二进制位（$f_i=0,1$），$g_i$ 表示 $b_i$ 这一位上的二进制位（$g_i=0,1$）。

不妨如下构造：找到最小的 $x,y$ 满足 $f_x=g_y=1$。此时不妨令 $c_{x,y}$ 的第 $k$ 位为 $1$，这样就满足了 $x$ 和 $y$ 的需求。然后不断重复找下一对 $(x,y)$，并重复此操作。

最后，可能会存在无法匹配的 $1$，以 $f_i$ 中的 $1$ 无法匹配为例。如果这样的 $1$ 有奇数个，说明无解。否则，假设某个位置上 $f_t=1$，只需令 $c_{t,1}$ 的第 $k$ 为 $1$ 即可。因为会加上偶数个 $1$，所以不影响结果。$g_i$ 中无法匹配同理。

于是这题就做完了，复杂度 $O(n^2+n\log V)$。其中 $V$ 为值域。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

const int maxn = 105;

int a[maxn], b[maxn], c[maxn][maxn];

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    int sum = 0;
    for(int i = 1; i <= n; i ++) scanf("%d", &a[i]), sum ^= a[i];
    for(int i = 1; i <= m; i ++) scanf("%d", &b[i]), sum ^= b[i];
    if(sum){
        printf("NO\n");
        return 0;
    }
    printf("YES\n");
    for(int k = 0; k <= 30; k ++){
        int i = 1, j = 1;
        while(i <= n && j <= m){
            while(i <= n && !((a[i] >> k) & 1)) i ++;
            while(j <= m && !((b[j] >> k) & 1)) j ++;
            if(i > n || j > m) break;
            c[i][j] += 1 << k;
            i ++, j ++;
        }
        while(i <= n){
            if((a[i] >> k) & 1) c[i][1] += 1 << k;
            i ++;
        }
        while(j <= m){
            if((b[j] >> k) & 1) c[1][j] += 1 << k;
            j ++;
        }
    }
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= m; j ++){
            printf("%d ", c[i][j]);
        }
        printf("\n");
    }
    return 0;
}
```

---

## 作者：_HCl_ (赞：0)

一道很有意思的构造。

# CF1016D 题解

**题意简述**

构造一个 $n\times m$ 的矩阵，满足每一行的异或和为 $a_i$，每一列的异或和为 $b_i$。

**思路引导**

由于是异或类的问题，不难想到按位去考虑。

我们可以对于每一位都构造一个 $01$ 矩阵。接下来考虑如何构造一个 $01$ 矩阵 $M$。

从自由度的角度出发，这个矩阵被 $(n+m)$ 个条件限制后，自由度应当是 $(n^2-n)$ 级别的。因此我们可以考虑，左上部分的 $(n-1)\times (m-1)$ 的子矩阵可以随便乱填，我们就全部填成 $0$。

而 $M_{i,m}(1\leq i\leq n-1)$ 就可以填成 $a_i$ 在这一位上的取值，$M_{n,i}(1\leq i\leq m-1)$ 就可以填成 $b_i$ 在这一位上的取值。

而 $M_{n,m}$ 填 $0$ 还是 $1$ 需要同时满足 $a_n$ 和 $b_m$ 的限制条件。如果无法做到，那么就构造不出来。

则我们有：如果 $S_a\neq S_b$， $M_{n,m}=b_m\ \text{xor}\ (S_a\ \text{xor}\ a_n) $，否则矩阵不存在。其中 $S_a$ 和 $S_b$ 分别是 $a_i$ 和 $b_i$ 的异或和。

为什么不能修改左上角子矩阵来找到一个合适的 $M_{i,j}$，使 $M$ 可以被构造？

证明：假设更改左上 $(n-1)\times (m-1)$ 的子矩阵的一位 $M_{i,j}$，那么 $a_i$ 和 $b_j$ 都要翻转，满足 $a_n$ 限制的 $M_{i,j}$ 和满足 $b_m$ 限制的 $M_{i,j}$ 也都要同时翻转。因此左上角子矩阵的填发不影响矩阵是否存在。

由于各位互不影响，所以可以把所有的 $01$ 矩阵放在一起考虑。

**代码**
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,sa,sb,a[10001],b[10001];
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;++i)scanf("%d",a+i),sa^=a[i];
	for(int i=1;i<=m;++i)scanf("%d",b+i),sb^=b[i];
	if(sa!=sb){
		cout<<"NO";
		return 0;
	}
	cout<<"YES\n";
	for(int i=1;i<n;++i){
		for(int j=1;j<m;++j)cout<<"0 ";
		cout<<a[i]<<"\n";
	}
	for(int i=1;i<m;++i)cout<<b[i]<<" ";
	cout<<(b[m]^(sa^a[n]));
}
```

---

## 作者：封禁用户 (赞：0)

## 前言

上一场 CF（CF1860）构造题炸了，找题做的时候发现的这题。

A 了之后看了眼题解，发现我的解法和题解不太一样。

~~第一次投的时候手抽打成了1610D，在此感谢 @soweak 指出错误qaq~~

## 题解

CF1800，~~甚至还有个 flow 的标签~~

文中用 $ mat_{i,j} $ 指代矩阵中 $i$ 行 $j$ 列的数。

第一反应肯定拆数字。

将所有的异或和拆成二进制，则题目变为**求 32 个 01 矩阵，使异或和满足行和列的需求**。

观察得到的 01 序列，可以发现：

如果行与列序列在这一位上的异或和不等，则一定不存在这样的矩阵，直接输出  NO；

否则只有三种可能性：
> 1. 行序列和列序列上的 1 一样多，则对每一个 1 从左往右扫一遍，如果找到1就直接将矩阵中该位置变为 1
>
> 2. 行序列上的 1 比列序列上的 1 多，则每次扫到 $i$ 下标时如果没扫到 1，则直接将 $ mat_{i,1} $ 变成 1
>
> 3. 列序列上的 1 比行序列上的 1 多，则行上扫完以后将列序列中所有仍为 1 的下标 $i$ 的 $mat_{1,i} $ 变成 1

如果有点懵可以自己手动做一下。

答案位移后相加即可。

## code

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,i,j,k,m;
int a[105],b[105];
int ans[105][105];
int ansa[105],ansb[105];
int main() {
    scanf("%d%d",&n,&m);
    for(i=1;i<=n;i++)
      scanf("%d",&a[i]);
    for(i=1;i<=m;i++)
      scanf("%d",&b[i]);
    for(i=0;i<=30;i++){
    	int sum1=0,sum2=0;
    	for(j=1;j<=n;j++){
    		ansa[j]=a[j]&1;
    		a[j]>>=1;
    		sum1^=ansa[j];
		}
		for(j=1;j<=m;j++){
			ansb[j]=b[j]&1;
    		b[j]>>=1;
    		sum2^=ansb[j];
		}	
		if(sum1!=sum2){
			printf("NO");
			return 0;
		}
		for(j=1;j<=n;j++){
			if(ansa[j]==0) continue;
			else{
				bool flag=false;
				for(k=1;k<=m;k++){
					if(ansb[k]==1){
						ansb[k]=0;
						ansa[j]=0;
						ans[j][k]|=(1<<i);
						flag=true;
						break;
					}
				}
				if(flag==false){
					ansb[1]=1;
					ansa[j]=0;
					ans[j][1]|=(1<<i);
				}
			}
		}
		for(j=1;j<=m;j++)
		  if(ansb[j]==1){
		  	ansb[j]=0;
		  	ans[1][j]|=(1<<i);
		  }
	}
	printf("YES\n");
    for(i=1;i<=n;i++){
    	for(j=1;j<=m;j++)
    	  printf("%d ",ans[i][j]);
    	printf("\n");
	}
	return 0;
}

```


     
     


---

## 作者：Fuko_Ibuki (赞：0)

`构造一个矩阵使得第i行的异或和为a[i],第i列的异或和为b[i].不能输出"NO".`  
比赛的时候我不小心先开了C题,做得原地爆炸.  
我去看AC人数,惊奇地发现D题A的人明显要多于C题.然后我看这题,瞎搞10多分钟就推出了一个谜一般的构造法.  
很明显整个矩阵的元素全部都是一样的,那么必然有$a$数组的异或值等于$b$数组的异或值.否则输出"NO".  
剩余情况必然存在符合条件的矩阵.  
然后我们考虑第一行,先去掉该行最后一列的格子,其它列全部赋上$b[i].$
接下来考虑最后一列,去掉该列第一行的格子,其它行全部赋上$a[i].$  
脑补一下现在的矩阵,那么关键就是第一行最后一列的那个格子了.  
由于所有的数字都已经固定了,这个格子上的数显然只有一个选择了.  
现在关键就是它能不能同时保证第一行的异或值等于$a[1]$,最后一列的异或值等于$b[m]$了.
```plain
求证:(a[1]^b[1]^b[2]^...^b[m-1])=(b[m]^a[2]^a[3]^...^a[n])  
证明:由(a[1]^a[2]^a[3]^...^a[n])=(b[1]^b[2]^b[3]^...^b[m])  
交换a[1]与b[m]得证.
```
那么本题迎刃而解.  
然而就在我写这篇题解的时候,不幸的事情还是发生了.
![](https://cdn.luogu.com.cn/upload/pic/26533.png)
![](https://cdn.luogu.com.cn/upload/pic/26534.png)  
在我写这篇题解的过程中,我收到了被hack的消息.  
我把被hack的代码放在下面,希望大家避免再犯类似的错误.  
```cpp
#include<bits/stdc++.h> //Ithea Myse Valgulious
namespace chtholly {
  typedef long long ll;
#define re0 register int
#define rec register char
#define rel register ll
#define gc getchar
#define pc putchar
#define p32 pc(' ')
#define pl puts("")
  /*By Citrus*/
  inline int read() {
    int x=0,f=1;
    char c=gc();
    for (; !isdigit(c); c=gc()) f^=c=='-';
    for (; isdigit(c); c=gc()) x=(x<<3)+(x<<1)+(c^'0');
    return f?x:-x;
  }
  template <typename mitsuha>
  inline bool read(mitsuha &x) {
    x=0;
    int f=1;
    char c=gc();
    for (; !isdigit(c)&&~c; c=gc()) f^=c=='-';
    if (!~c) return 0;
    for (; isdigit(c); c=gc()) x=(x<<3)+(x<<1)+(c^'0');
    return x=f?x:-x,1;
  }
  template <typename mitsuha>
  inline int write(mitsuha x) {
    if (!x) return 0&pc(48);
    if (x<0) x=-x,pc('-');
    int bit[20],i,p=0;
    for (; x; x/=10) bit[++p]=x%10;
    for (i=p; i; --i) pc(bit[i]+48);
    return 0;
  }
  inline char fuhao() {
    char c=gc();
    for (; isspace(c); c=gc());
    return c;
  }
} using namespace chtholly;
using namespace std;
int n,m,a[105],b[105];
#define _bp __builtin_popcount
int ans[105][105];

void getans(){
int i,j;
for (i=1;i<n;++i){
  for (j=1;j<m;++j){
    ans[i][j]=0;
    }
  }
for (i=1;i<n;++i) ans[i][m]=a[i];
for (i=1;i<m;++i) ans[n][i]=b[i];
for (i=1;i<n;++i) b[m]^=a[i];
ans[n][m]=b[m];
}

int main(){
int i,j;
scanf("%d%d",&n,&m);
for (i=1;i<=n;++i) a[i]=read();
for (i=1;i<=m;++i) b[i]=read();
int cnt1=0,cnt2=0;
for (i=1;i<=n;++i) cnt1+=_bp(a[i]);
for (i=1;i<=m;++i) cnt2+=_bp(b[i]);
if (cnt1%2!=cnt2%2) return puts("NO"),0;
/*判断无解的时候爆炸了,俗话说吃一堑长一智,以后还是要小心为妙.*/
puts("YES");
getans();
for (i=1;i<=n;++i,pl){
  for (j=1;j<=m;++j) write(ans[i][j]),p32;	
  }
}
```

---

