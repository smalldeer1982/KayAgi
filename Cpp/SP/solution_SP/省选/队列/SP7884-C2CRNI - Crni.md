# C2CRNI - Crni

## 题目描述

尽管Mirko找到了所有最有趣的游乐设施，但他的热情仍然没有消失，于是他无聊地打开了方格笔记本，开始给方块涂色，于是一个新的甚至更难的问题浮现了出来。

现在有个$N\times N$的矩阵，每个格子被填充了黑色或者白色。如果这个矩形的一个子矩形内的所有格子均为黑色并且由至少两个格子组成，则这个子矩形称为**黑矩形**。

![](https://cdn.luogu.com.cn/upload/image_hosting/hidn0vrp.png)

左图框选了两个不是黑矩形的子矩形。1号子矩形不是黑矩形，因为它包含了白色的格子；2号子矩形不是黑矩形，因为它仅包含一个格子。右图框选了三个有效的黑矩形。

现在Mirko想知道找出两个不相交的黑矩形的方案的总数目。由于结果可能非常大，因此你的答案需要对$10007$取模。

## 样例 #1

### 输入

```
\n2 \nCC \nCC\n\n```

### 输出

```
\n2\n\nInput:\n3 \nCCB \nCCB \nCBB\n\nOutput:\n5\n\nInput:\n5\nBCCBB\nBBCBB\nBCCBB\nBBBBB\nCCBBB\n\nOutput:\n8```

# 题解

## 作者：辰星凌 (赞：4)

# **【题解】C2Crni - Crni [SP7884]**


**传送门：[$\text{C2Crni - Crni}$](https://www.luogu.org/problem/SP7884) [$\text{[SP7884]}$](https://www.spoj.com/problems/C2CRNI/)**

## **【题目描述】**

给定一个 $\text{N} * \text{N}$ 的矩阵，每个格子要么为白色（$B$）要么为黑色（$C$）。定义**黑矩形**为所含单元格数大于等于 $2$ 且所含单元格均为黑色的矩阵。
如图：  
![](https://cdn.luogu.com.cn/upload/image_hosting/txiqd3b6.png)

左边的两个矩形都不是黑矩形，因为 $1$ 中有白格，$2$ 的大小为 $1$，而右图的 $3$ 个都是黑矩形。

要解决的问题是在给定的矩形中**找出两个没有共公部分的黑矩形**，输出所有方案数，由于数较大，答案对 $10007$ 取模。

-------

## **【分析】**

这是一道套路题，用到了很多关于矩阵的处理技巧，但找到解决方法后会发现它的思维难度其实并不高，主要是代码实现较困难，所以也可以视其为膜你题。

### **【前缀和的套路】**

找子矩阵基本都会用到前缀和，常见的查询子矩阵可以直接容斥，例如维护**二维树状数组**时用到的方法：

设 $S[x][y]=\sum_{i=1}^{x} \sum_{j=1}^{y} a[i][j]$，那么递推式为 $S[i][j]=$ $S[i-1][j]+S[i][j-1]-S[i-1][j-1]+a[i][j]$

如果要查询以 $(x1,y1)$ 为左下角，以 $(x2,y2)$ 为右下角的矩阵和，$\sum_{i={x_1}}^{y_1} \sum_{j={x_2}}^{y_2} a[i][j]=$ $S[x2][y2]-S[x1-1][y2]-S[x2][y1-1]+S[x1-1][y1-1]$

在预处理式子时需要从左上角一直递推到右下角，而稍复杂一点的需要统计多个方向（没错，就是此题了），即从最多 $4$ 个角落（左上，左下，右上，右下）开始向其对角处递推，得到多个助于统计答案的前缀和数组。

### **【预处理】**

回到此题。

为方便处理，将矩阵中的黑点设为 $1$，白点设为 $0$ 。

对于所有的黑点，先预处理出 $4$ 个数组：

$(1).$ $RD[i][j]$： 以 $(i,j)$ 为**右下角**的**黑矩阵**个数。

$(2).$ $LU[i][j]$： 以 $(i,j)$ 为**左上角**的**黑矩阵**个数。

$(3).$ $LD[i][j]$： 以 $(i,j)$ 为**左下角**的**黑矩阵**个数。

$(4).$ $RU[i][j]$： 以 $(i,j)$ 为**右上角**的**黑矩阵**个数。

但如果暴力枚举的话 $O(n^4)$ 复杂度过高，需要考虑合理**继承**前面求出的信息。

以 $RD$ 为例，为便于推导，我们先在矩阵中枚举一条辅助线，假设已经求出了第 $i$ 行前 $j-1$ 列的 $RD$ 信息，如图为 $i=4,j=4$ 的情况：
![](https://cdn.luogu.com.cn/upload/image_hosting/24n4h1nl.png)

定义 $H[i][j]$ 为点 $(i,j)$ 向上最多可以延伸的距离（或者说高度），如果 $a(i,j)$ 为白块，$H[i][j]=0$ 。

处理方法如下：

对于点 $(i,j)$ 找到同一列前面第一个 $H$ 小于它的位置 $(i,k)$。

由于 $[k+1,j]$ 的高度都大于 $j$，那么将会有 $H[i][j]*(j-k)$ 个点可以作为**黑矩形**的**左上角**（**右下角**为 $(i,j)$），但是将 $(i,j)$ 自己作为**左上角**时**黑矩阵**大小只有 $1$，所以要减去 $1$ 。

另外以 $(i,k)$ 为**右下角**的**黑矩阵**都可以将长度扩大 $j-k$，即变成以 $(i,j)$ 为**右下角**，但以 $(i,k)$ 为**右下角**的情况没有计算在 $RD[i][k]$ 以内，所以要加上 $1$ 。

得到递推式为：$RD[i][j]=H[i][j]*(j-k)-1+RD[i][k]+1$ 。

于是时间复杂度就被优化到了 $O(n^3)$，但还不够优秀。

现在的问题是如何快速找 $k$，方法同 [$\text{Largest}$ $\text{Rectangle}$ $\text{in}$ $\text{a}$ $\text{Histogram}$](https://www.luogu.org/problem/SP1805) [（题解）](https://www.cnblogs.com/Xing-Ling/p/10935693.html)，直接单调栈维护即可。

在上面那张图中 $H[4][1]=1,H[4][2]=2,H[4][3]=4,H[4][4]=3$，所以 $j=4$ 时的决策点 $k=2$，因此 $RD[3][4]=3*2-1+RD[3][2]+1$ 。

同理可得 $LU,LD,RU$ 。

### **【统计答案】**

依旧是枚举辅助线：  
![](https://cdn.luogu.com.cn/upload/image_hosting/89a72vbb.png)

先求出**下边界在红线上面**的**黑矩形**个数，即 $\sum_{i=1}^{x} \sum_{j=1}^{n} RD[i][j]$（或者 $LD[i][j]$），

再求出**上边界紧贴在红线下面**的**黑矩阵**个数，即 $\sum_{j=1}^{n}LU[x+1][j]$（或者 $RU[x+1][j]$），

将二者相乘，再对于每一条辅助线算出的结果求和，得到**相对位置为上下**的**黑矩形**总对数。（其实也可以固定红线上面，红线下面求总个数）

同理枚举**竖线**，可得**相对位置为左右**的**黑矩形**总对数。

但这样会有算重复的情况，如下图绿色部分和蓝色部分：  
![](https://cdn.luogu.com.cn/upload/image_hosting/gz6se8m3.png)

因此还要减去**相对位置既有上下又有左右**的**黑矩形**对数，也就是在十字线对角象限的**黑矩形**对数，求法和前面大致相同。为方便处理，要任选两个方向计算矩阵前缀和（递推式和二维树状数组的一样）：

$(1).$ $S_{RD}[x][y]=\sum_{i=1}^{x} \sum_{j=1}^{y} RD[i][j]$  
前缀和递推方向：**左上** → **右下** 。  
矩阵前缀和意义：**右下角**在 $(i,j)$ **左上面**的黑矩阵个数。

$(2).$ $S_{LU}[x][y]=\sum_{i=n}^{x} \sum_{j=n}^{y} RD[i][j]$  
前缀和递推方向：**右下** → **左上** 。  
矩阵前缀和意义：**左上角**在 $(i,j)$ **右下面**的黑矩阵个数。

$(3).$ $S_{LD}[x][y]=\sum_{i=1}^{x} \sum_{j=n}^{y} RD[i][j]$  
前缀和递推方向：**右上** → **左下** 。  
矩阵前缀和意义：**左下角**在 $(i,j)$ **右上面**的黑矩阵个数。

$(4).$ $S_{RU}[x][y]=\sum_{i=n}^{x} \sum_{j=1}^{y} RD[i][j]$  
前缀和递推方向：**左下** → **右上** 。  
矩阵前缀和意义：**右上角**在 $(i,j)$ **左下面**的黑矩阵个数。

最后，此题细节较多，变量名没设好的话很容易搞混。

时间复杂度为：$O(n^2)$ 。

-------

## **【Code】**

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#define Re register int
#define For(i,a,b) for(Re i=a;i<=b;++i)
#define Por(i,a,b) for(Re i=a;i>=b;--i)
#define print() for(Re i=1;i<=n;puts(""),++i)for(Re j=1;j<=n;++j)
using namespace std;
const int N=1003,P=10007;
int n,Q[N],A[N][N],H[N][N],SS[N][N];char ch[N];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
int RD[N][N];
inline void get_RD(){//RD[i][j]: 以i,j为右下角的黑矩形个数(1,1)→(n,n) 
    memset(H,0,sizeof(H));
    For(i,1,n)For(j,1,n)if(A[i][j])H[i][j]=H[i-1][j]+1;
//  print()printf("%d ",H[i][j]);puts("");
    For(i,1,n){
    	Re h=1,t=0;
    	For(j,1,n)if(!A[i][j])RD[i][j]=-1;
    	RD[i][Q[++t]=0]=-1;
    	For(j,1,n){
            while(h<=t&&H[i][Q[t]]>=H[i][j])--t;
            if(h<=t&&A[i][j])RD[i][j]=RD[i][Q[t]]+1+H[i][j]*(j-Q[t])-1;
            Q[++t]=j;
    	}
    	For(j,1,n)if(RD[i][j]<0)RD[i][j]=0;
    }
//  print()printf("%d ",RD[i][j]);puts("");
}
int LU[N][N];
inline void get_LU(){//LU[i][j]: 以i,j为左上角的黑矩形个数(n,n)→(1,1) 
    memset(H,0,sizeof(H));
    Por(i,n,1)Por(j,n,1)if(A[i][j])H[i][j]=H[i+1][j]+1;
//  print()printf("%d ",H[i][j]);puts("");
    Por(i,n,1){
    	Re h=1,t=0;
    	Por(j,n,1)if(!A[i][j])LU[i][j]=-1;
    	LU[i][Q[++t]=n+1]=-1;
    	Por(j,n,1){
            while(h<=t&&H[i][Q[t]]>=H[i][j])--t;
            if(h<=t&&A[i][j])LU[i][j]=LU[i][Q[t]]+1+H[i][j]*(Q[t]-j)-1;
            Q[++t]=j;
    	}
    	Por(j,n,1)if(LU[i][j]<0)LU[i][j]=0;
    }
//  print()printf("%d ",LU[i][j]);puts("");
}
int LD[N][N];
inline void get_LD(){//LD[i][j]: 以i,j为左下角的黑矩形个数(1,n)→(n,1)
    memset(H,0,sizeof(H));
    For(i,1,n)Por(j,n,1)if(A[i][j])H[i][j]=H[i-1][j]+1;
//  print()printf("%d ",H[i][j]);puts("");
    For(i,1,n){
    	Re h=1,t=0;
    	Por(j,n,1)if(!A[i][j])LD[i][j]=-1;
    	LD[i][Q[++t]=n+1]=-1;
    	Por(j,n,1){
            while(h<=t&&H[i][Q[t]]>=H[i][j])--t;
            if(h<=t&&A[i][j])LD[i][j]=LD[i][Q[t]]+1+H[i][j]*(Q[t]-j)-1;
            Q[++t]=j;
    	}
    	Por(j,n,1)if(LD[i][j]<0)LD[i][j]=0;
    }
//  print()printf("%d ",LD[i][j]);puts("");
}
int RU[N][N];
inline void get_RU(){//RU[i][j]: 以i,j为右上角的黑矩形个数(n,1)→(1,n)
    memset(H,0,sizeof(H));
    Por(i,n,1)Por(j,n,1)if(A[i][j])H[i][j]=H[i+1][j]+1;
//  print()printf("%d ",H[i][j]);puts("");
    Por(i,n,1){
    	Re h=1,t=0;
    	For(j,1,n)if(!A[i][j])RU[i][j]=-1;
    	RU[i][Q[++t]=0]=-1;
    	For(j,1,n){
            while(h<=t&&H[i][Q[t]]>=H[i][j])--t;
            if(h<=t&&A[i][j])RU[i][j]=RU[i][Q[t]]+1+H[i][j]*(j-Q[t])-1;
            Q[++t]=j;
    	}
    	For(j,1,n)if(RU[i][j]<0)RU[i][j]=0;
    }
//  print()printf("%d ",RU[i][j]);puts("");
}
inline int U_D(){//加上-下 
    Re ans=0,S=0;
    For(i,1,n){
    	For(j,1,n)(ans+=S*LU[i][j]%P)%=P;//用【左上角为(i,j)的矩阵LU】固定在辅助线下面
    	For(j,1,n)(S+=RD[i][j])%=P;//用【右下角为(i,j)的矩阵RD】求辅助线上边的总个数
    }
    return ans%P;
}
inline int L_R(){//加左-右 
    Re ans=0,S=0;
    For(j,1,n){
    	For(i,1,n)(ans+=S*LU[i][j]%P)%=P;//用【左上角为(i,j)的矩阵LU】固定在辅助线右边
    	For(i,1,n)(S+=RD[i][j])%=P;//用【右下角为(i,j)的矩阵RD】求辅助线左边的总个数
    }
    return ans%P;
}
inline int LU_RD(){//减左上-右下 
    Re ans=0;memset(SS,0,sizeof(SS));
    For(i,1,n-1)For(j,1,n-1){
    	SS[i][j]=((RD[i][j]+SS[i-1][j]+SS[i][j-1])%P-SS[i-1][j-1]+P)%P;
    	//十字线左上角的用【右下角为(i,j)的矩阵RD】求总和
    	(ans+=SS[i][j]*LU[i+1][j+1]%P)%=P;//用【左上角为(i,j)的矩阵LU】固定十字线的右下角
    }
    return ans;
}
inline int RU_LD(){//减右上-左下 
    Re ans=0;memset(SS,0,sizeof(SS));
    For(i,1,n-1)Por(j,n,2){
    	SS[i][j]=((LD[i][j]+SS[i-1][j]+SS[i][j+1])%P-SS[i-1][j+1]+P)%P;
    	//十字线右上角的用【左下角为(i,j)的矩阵LD】求总和
    	(ans+=SS[i][j]*RU[i+1][j-1]%P)%=P;//用【右上角为(i,j)的矩阵RU】固定十字线的左下角
    }
    return ans;
}
int main(){
//  freopen("crni.in","r",stdin);
//  freopen("crni.out","w",stdout);
    in(n);
    For(i,1,n){
    	scanf("%s",ch+1);
    	For(j,1,n)A[i][j]=(ch[j]=='C');
    }
    get_RD(),get_LU(),get_LD(),get_RU();
    printf("%d\n",((U_D()+L_R())%P-(LU_RD()+RU_LD())%P+P)%P);
//  fclose(stdin);
//  fclose(stdout);
    return 0;
}
```


---

## 作者：Silent_E (赞：3)

听说是道很老的套路题，考试考了这道。。。

有个比较明显的东西，就是我们要求的两个黑矩形没有公共部分，那么必然会有一条竖线（或横线）把这两个黑矩形分开，我们就可以枚举这条竖线（横线）来统计答案。

为了避免计算重复，我们需要一边固定，另一边统计总和。并且，还应减去既能被一条竖线分开又能被一条横线分开的两个黑矩形（因为它被算了两次嘛）。

大体思路就是这样，然后就是实现。

比较容易想到的就是计算以每个格子为左下角（右下角、左上角、右上角）的黑矩形有多少个。

考试的时候~~太弱了~~，只会写$O(n^4)$的暴力。。。（它还挂了）

简单说一点暴力吧，就是$O(n^2)$枚举每个格子，然后$O(n^2)$枚举矩形的长度，可以用二维前缀和$O(1)$来判断枚举的矩形是否合法，然后就$O(n^4)$预处理，再$O(n^2)$统计贡献。

可以看到，预处理是瓶颈，我们应考虑如何优化预处理的复杂度。

对每一行拆开考虑，我们会发现比较像[直方图里的最大矩形](https://www.acwing.com/problem/content/133/)，然后就做啊。

我们以计算以每个格子为右下角的黑矩形有多少个为例。

设$f[i][j]$就是以$(i,j)$为右下角的黑矩形有多少个，我们会发现，它可以直接继承它前面出现的第一个小于它高度的位置的答案，那中间那些比它还高的矩形呢，没错，只能扩展它自己的高度。

即$f[i][j]=f[i][k]+1+h[j]*(j-k)-1$

其中$k$表示从$j$向前走第一次出现的$h[k]<h[j]$的位置，那么直接可以继承$f[i][k]$，然后加一，然后对于那块大的矩形里的所有点均可作为当前矩形的左上角，除了自己本身，因为$1\times 1$的黑矩形不能算入答案，所以会减一。

考虑到$k$的计算，想到单调栈优化，可以做到$O(1)$转移。

所以我们做到了$O(n^2)$预处理，然后就行了。

细节有点多，还有要注意时刻取模。

```cpp
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#define ll long long
const int P = 10007;
const int N = 1000 + 5; 
inline int read(){
	int f = 1, x = 0; char ch;
	do { ch = getchar(); if (ch == '-') f = -1; } while (ch < '0' || ch > '9');
	do {x = (x << 3) + (x << 1) + ch - '0'; ch = getchar(); } while (ch >= '0' && ch <= '9'); 
	return f * x;
}
inline void hand_in() {
	freopen("crni.in", "r", stdin);
	freopen("crni.out", "w", stdout);
}
int n, mp[N][N], res;
int f[N][N], g[N][N], h[N];
char ch[N][N]; int sta[N], top;
int main(){
//	hand_in();
	n = read();
	for (int i = 1;i <= n; ++i) scanf("%s", ch[i] + 1);
	for (int i = 1;i <= n; ++i) {
		for (int j = 1;j <= n; ++j) {
			mp[i][j] = (ch[i][j] == 'C');
		}
	}
	// 左上 
	memset(h, 0, sizeof h);
	for (int i = 1;i <= n; ++i) {
        top = 0;
        sta[top] = 0;
        for (int j = 1;j <= n; ++j) {
            if (mp[i][j] == 1) h[j] ++;
            else h[j] = 0;
            if (h[j] == 0) {
            	top = 0;
            	sta[top] = j;
            	continue;
            }
            int size;
			while (top && h[sta[top]] >= h[j]) top --;
			size = h[j] * (j - sta[top]) - 1;
			f[i][j] = f[i][sta[top]] + size + (top > 0);
            f[i][j] %= P;
            sta[++top] = j;
        }
    }
	//右下 
	memset(h, 0, sizeof h);
	for (int i = n;i >= 1; --i) {
        top = 0;
        sta[top] = n + 1;
        for (int j = n;j >= 1; --j) {
            if (mp[i][j] == 1) h[j] ++;
            else h[j] = 0;
            if (h[j] == 0) {
            	top = 0;
            	sta[top] = j;
            	continue;
            }
            int size;
			while (top && h[sta[top]] >= h[j]) top --;
			size = h[j] * (sta[top] - j) - 1;
			g[i][j] = g[i][sta[top]] + size + (top > 0);
            g[i][j] %= P;
            sta[++top] = j;
        }
	}
	int suma = 0, sumb = 0;
	for (int i = 1;i < n; ++i) {
		for (int j = 1;j <= n; ++j) {
			suma += f[i][j], sumb += g[i + 1][j];
			suma %= P, sumb %= P;
		}
		res += suma * sumb;
		res %= P;
		sumb = 0;
	}
	suma = 0, sumb = 0;
	for (int j = 1;j < n; ++j) {
		for (int i = 1;i <= n; ++i) {
			suma += f[i][j], sumb += g[i][j + 1];
			suma %= P, sumb %= P;
		}
		res += suma * sumb;
		res %= P;
		sumb = 0;
	}
	for (int i = 1;i <= n; ++i) {
		for (int j = 1;j <= n; ++j) {
			f[i][j] += f[i - 1][j] + f[i][j - 1] - f[i - 1][j - 1] + P;
			f[i][j] %= P;
		}
	}
	for (int i = 1;i < n; ++i) {
		for (int j = 1;j < n; ++j) {
			res -= (f[i][j] * g[i + 1][j + 1] + P) % P;
			while (res < 0) res += P;
		}
	}
	//右上 
	memset(f, 0, sizeof f);
	memset(h, 0, sizeof h);
	for (int i = 1;i <= n; ++i) {
        top = 0;
        sta[top] = n + 1;
        for (int j = n;j >= 1; --j) {
            if (mp[i][j] == 1) h[j] ++;
            else h[j] = 0;
            if (h[j] == 0) {
            	top = 0;
            	sta[top] = j;
            	continue;
            }
            int size;
			while (top && h[sta[top]] >= h[j]) top --;
			size = h[j] * (sta[top] - j) - 1;
			f[i][j] = f[i][sta[top]] + size + (top > 0);
            f[i][j] %= P;
            sta[++top] = j;
        }
    }
    //左下 
	memset(g, 0, sizeof g);
	memset(h, 0, sizeof h);
	for (int i = n;i >= 1; --i) {
        top = 0;
        sta[top] = 0;
        for (int j = 1;j <= n; ++j) {
            if (mp[i][j] == 1) h[j] ++;
            else h[j] = 0;
            if (h[j] == 0) {
            	top = 0;
            	sta[top] = j;
            	continue;
            }
            int size;
			while (top && h[sta[top]] >= h[j]) top --;
			size = h[j] * (j - sta[top]) - 1;
			g[i][j] = g[i][sta[top]] + size + (top > 0);
            g[i][j] %= P;
            sta[++top] = j;
        }
	}
    for (int i = 1;i <= n; ++i) {
    	for (int j = n;j >= 1; --j) {
    		f[i][j] += f[i - 1][j] + f[i][j + 1] - f[i - 1][j + 1] + P;
    		f[i][j] %= P;
    	}
    }
	for (int i = 1;i < n; ++i) {
		for (int j = 2;j <= n; ++j) {
			res -= (f[i][j] * g[i + 1][j - 1] + P) % P;
			while (res < 0) res += P;
		}
	}
	printf("%d", res);
	return 0;
}
```



---

## 作者：Hzao (赞：1)

总的黑矩形对$(A,B)$的数量，就是 $B$整个都在$A$的右方或者下方的黑矩形对的数量，减去$B$整个都在$A$的左下方的数量。

这里的“右方或下方“指的是这个矩形的**右下角**的“右方或上方”。

例如图中这个黑色的矩形的"右方或下方"就是棕色部分。



![crni_1](https://img.hzao.top/data/crni_1.png)

这里的“左下方”是指这个**矩形左下角**的左下方。（不包括正左或者正下）

例如下图中的棕色部分。

![crni_2](https://img.hzao.top/data/crni_2.png)



为什么要这么减呢？因为一个矩形$A$的左下部分的矩形$B$在计算**右方或下方**部分的时候，会算到$A$。于是有了重复。也就是说既从$A$计算了$B$，又从$B$计算了$A$。





现在考虑如何求上面两个值。

首先，求出$f[i][j]$，表示以$(i,j)$为右下角的黑矩形个数。

为了简便描述，我们一行一行地求。所以现在$f(j)$表示以当前行第$j$列的那个块为右下角的黑矩形个数。

设$h[j]$表示以当前行第$j$列上的矩阵为底，黑矩阵的高度。

很显然，如果$h[j-1]<h[j] $，那么所有以$j-1$为右下角的黑矩形都可以延伸到$j$。同时$j-1$本身还可以与$j$构成一个$1×2$的黑矩形。所以$j-1$对$j$的贡献是$f(j-1)+1$。$j$自己这一列上的$h[j]-1$个格子也可以和$j$构成矩形。所以$f(j)=f(j-1)+1+h[j]-1=f(j-1)+h[j].$

如果$h[j-1] \ge h[j]$，$j$只能继承以$j-1$为右下角，高度不超过$h[j]$的矩形。这时$j-2$的一些格子也可以继承过来。

一般地，如果$k$是满足$h[l] \ge h[j],l\in[k,j]$的最小值，那么有$f(j)=f(k-1)+1+S-1=f(k-1)+S.$

其中$S=h[j]*(j-k+1).$

如图，当前正在求第四行的$f(4)$。上式中的$f(k-1)$对应橙色部分，$+1$对应绿色部分，$S$对应红色部分，$-1$对应蓝色部分。



![crni_3](https://img.hzao.top/data/crni_3.png)

同理，我们求出以$(i,j)$为左上角的黑矩形个数$g[i][j]$。然后求出整个都在$(i,j)$到右下角的黑矩形个数$sum[i][j]$。显然有$sum[i][j]=sum[i+1][j]+sum[i][j+1]-sum[i+1][j+1]+g[i][j].$

这样，满足$B$在$A$右方或下方的黑矩形对$(A,B)$的数量就是$\sum f[i][j]*(sum[i+1][1]+sum[1][j+1]-sum[i+1][j+1]).$

建议自行在草稿纸上画一下以理解。



然后，求出以$(i,j)$为右上角的矩形个数$e[i][j]$和以$(i,j)$为左下角的矩形个数$c[i][j]$。

求出整个部分都在从左下角到$(i,j)$形成的矩阵中的黑矩阵的个数$sum2[i][j]$。

显然$sum2[i][j]=sum2[i+1][j]+sum2[i][j-1]-sum2[i+1][j-1]+e[i][j].$

于是$B$在$A$左下方（不包括正左或正下）的黑矩形对数就是$\sum sum2[i+1][j-1]*c[i][j]$。



所以整个的答案是:$\sum f[i][j]*(sum[i+1][1]+sum[1][j+1]-sum[i+1][j+1])-\sum sum2[i+1][j-1]*c[i][j]$.



代码：


```cpp
#include<stack>
#include<cstdio>
#include<cstring>
using std::stack;
template<typename T>
inline bool read(T &x){
    x=0;char c;T f=1;
    do{
        c=getchar();
        if(c=='-')f=-1;
        else if(c==EOF)return false;
    }while(c>'9'||c<'0');
    do{
        x=x*10+c-'0';
        c=getchar();
    }while(c>='0'&&c<='9');
    return x*=f,true;
}
template<typename T>
inline bool updmax(T &x,T y){
    if(y>x)return x=y,true;
    return false;
}
template<typename T>
inline bool updmin(T &x,T y){
    if(y<x)return x=y,true;
    return false;
}
const int N=1010;
const long long mod=10007;
char str[N];
long long ans=0;
int n;
int l[N];
int col[N][N];
int h[N][N],h2[N][N];
int sum[N][N],sum2[N][N];
int f[N][N],g[N][N],e[N][N],c[N][N];

stack<int> S;
int main(){
    read(n);
    for(register int i=1;i<=n;++i){
        scanf("%s",str+1);
        for(register int j=1;j<=n;++j){
            col[i][j]=(str[j]=='C');
            h[i][j] = col[i][j] ? h[i-1][j]+1 : 0;
        }
    }
    register int len;
    for(register int i=1;i<=n;++i){
        while(!S.empty())S.pop();
        f[i][0]=-1;
        for(register int j=1;j<=n;++j){
            l[j]=j;
            len=0;
            while(!S.empty()&&h[i][S.top()]>=h[i][j]){
                updmin(l[j],l[S.top()]);
                S.pop();
            }
            len=j-l[j]+1;
            f[i][j]=f[i][l[j]-1]+len*h[i][j]+mod;
            f[i][j]%=mod;
            S.push(j);
        }
    }
    
    for(register int i=1;i<=n;++i){
        while(!S.empty())S.pop();
        c[i][n+1]=-1;
        for(register int j=n;j>=1;--j){
            l[j]=j;
            len=0;
            while(!S.empty()&&h[i][S.top()]>=h[i][j]){
                updmax(l[j],l[S.top()]);
                S.pop();
            }
            len=l[j]-j+1;
            c[i][j]=c[i][l[j]+1]+len*h[i][j]+mod;
            c[i][j]%=mod;
            S.push(j);
        }
    }

    for(register int i=n;i>=1;--i){
        for(register int j=1;j<=n;++j){
            h2[i][j]=col[i][j]? h2[i+1][j] + 1 :0;
        }
    }
    for(register int i=1;i<=n;++i){
        while(!S.empty())S.pop();
        g[i][n+1]=-1;
        for(register int j=n;j>=1;--j){
            l[j]=j;
            len=0;
            while(!S.empty()&&h2[i][S.top()]>=h2[i][j]){
                updmax(l[j],l[S.top()]);
                S.pop();
            }
            len=l[j]-j+1;
            g[i][j]=g[i][l[j]+1]+len*h2[i][j]+mod;
            g[i][j]%=mod;
            S.push(j);
        }
    }
    for(register int i=1;i<=n;++i){
        while(!S.empty())S.pop();
        e[i][0]=-1;
        for(register int j=1;j<=n;++j){
            l[j]=j;
            len=0;
            while(!S.empty()&&h2[i][S.top()]>=h2[i][j]){
                updmin(l[j],l[S.top()]);
                S.pop();
            }
            len=j-l[j]+1;
            e[i][j]=e[i][l[j]-1]+len*h2[i][j]+mod;
            e[i][j]%=mod;
            S.push(j);
        }
    }
    for(register int i=n;i>=1;--i){
        for(register int j=n;j>=1;--j){
            sum[i][j]=
                (sum[i+1][j]+
                sum[i][j+1]-
                sum[i+1][j+1]+mod+
                (h2[i][j]?g[i][j]:0))%mod;
        }
    }
  
    for(register int i=1;i<=n;++i){
        for(register int j=1;j<=n;++j){
            if(!h[i][j])continue;
            ans+=f[i][j]*(sum[i+1][1]+sum[1][j+1]-sum[i+1][j+1]+mod)%mod;
            ans%=mod;
        }
    }
    for(register int i=n;i>=1;--i){
        for(register int j=1;j<=n;++j){
            sum2[i][j]=
                sum2[i+1][j]+
                sum2[i][j-1]+
                -sum2[i+1][j-1]%mod+
                mod+
                (h2[i][j]?e[i][j]:0);
            sum2[i][j]%=mod;
        }
    }
    int delta;
    for(register int i=1;i<=n;++i){
        for(register int j=1;j<=n;++j){
            if(!h[i][j])continue;
            delta=c[i][j]*(sum2[i+1][j-1])%mod;
            ans=(ans-delta+mod)%mod;
        }
    }
    printf("%lld\n",ans);
    return 0;
}
```




---

