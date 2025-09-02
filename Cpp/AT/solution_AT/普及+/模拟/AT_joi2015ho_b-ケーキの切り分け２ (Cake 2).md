# ケーキの切り分け２ (Cake 2)

## 题目描述

# 「JOI 2014/2015 决赛」分蛋糕 2

**译自 [JOI 2014/2015 决赛](https://www.ioi-jp.org/joi/2014/2015-ho/index.html) T2「[ケーキの切り分け２](https://www.ioi-jp.org/joi/2014/2015-ho/2015-ho.pdf)」**

JOI 君和 IOI 酱是双胞胎兄妹。 JOI 君最近闲暇时常常会做甜点。今天 JOI 君也烤了蛋糕吃，IOI 酱立马嗅到了蛋糕的香气于是跑来想分着吃。  
蛋糕是圆形的，从蛋糕中某点开始将蛋糕放射状切为 $ N $ 块，按逆时针顺序编号为 $ 1 $ 到 $ N $ 。也就是说，对任意 $ i $ 来说 $ (1 \leq i \leq N) $ ，第 $ i $ 块蛋糕紧挨着第 $ i-1 $ 块与第 $ i+1 $ 块（不过第 $ 0 $ 块相当于第 $ N $ 块，第 $ N+1 $ 块相当于第 $ 1 $ 块）。第 $ i $ 块蛋糕的大小为 $ A_i $ 。由于切蛋糕的人刀功很不好，所以 $ A_i $ 互不相同。

![](https://www.z4a.net/images/2018/08/04/5c83a03e0789dafd806d5f7e488b001d.png)

JOI 君和 IOI 酱按照以下的方法分这 $N$ 块蛋糕：
1. 首先 JOI 君从这 $ N $ 块蛋糕中任选一块取走；
2. 然后，从 IOI 酱开始， IOI 酱和 JOI 君交替地从剩下的蛋糕中选出一块取走。不过，当且仅当一块蛋糕两旁的蛋糕至少有一块已经被选择，这块蛋糕才能被选择。如果可供选择的蛋糕有多个， IOI 酱会选择最大的一个，而 JOI 君可以任选一个。

JOI 君想让自己所得到的蛋糕大小的合计值最大。

#### 任务
给出蛋糕的块数 $ N $ 和这 $ N $ 块蛋糕的大小。请编写程序求出 JOI 君得到的蛋糕大小的总和的最大值。

## 说明/提示

JOI 君依次进行以下操作时为最优解：

1.  JOI 君选择第 $ 2 $ 块蛋糕，这块蛋糕的大小为 $ 8 $；
2.  IOI 酱选择第 $ 1 $ 块蛋糕，这块蛋糕的大小为 $ 2 $；
3.  JOI 君选择第 $ 5 $ 块蛋糕，这块蛋糕的大小为 $ 9 $；
4.  IOI 酱选择第 $ 4 $ 块蛋糕，这块蛋糕的大小为 $ 10 $；
5.  JOI 君选择第 $ 3 $ 块蛋糕，这块蛋糕的大小为 $ 1 $；

最后 JOI 君得到的蛋糕的大小的总和为 $ 8+9+1=18 $。

#### 输入样例 2
```plain
8
1
10
4
5
6
2
9
3
```
#### 输出样例 2
```plain
26
```
#### 输入样例 3
```plain
15
182243672
10074562
977552215
122668426
685444213
3784162
463324752
560071245
134465220
21447865
654556327
183481051
20041805
405079805
564327789
```
#### 输出样例 3
```plain
3600242976
```
对于 $ 15\% $ 的分值：
- $ N \leq 20 $

对于另 $45\%$ 的分值：
- $ N \leq 300 $

对于 $100\%$ 的分值，所有输入数据满足以下条件：
- $ 1 \leq N \leq 2000 $；
- $ 1 \leq A_i \leq 10^9 $；
- 每个 $ A_i $ 都不同。

感谢@ミク 提供的翻译

## 样例 #1

### 输入

```
5
2
8
1
10
9```

### 输出

```
18```

## 样例 #2

### 输入

```
8
1
10
4
5
6
2
9
3```

### 输出

```
26```

## 样例 #3

### 输入

```
15
182243672
10074562
977552215
122668426
685444213
3784162
463324752
560071245
134465220
21447865
654556327
183481051
20041805
405079805
564327789```

### 输出

```
3600242976```

# 题解

## 作者：makerlife (赞：3)

[更好的阅读体验](https://blog.makerlife.top/post/dp-problems/#AT-joi2015ho-b-Cake-2) | [Problem Link](https://www.luogu.com.cn/problem/AT_joi2015ho_b)

$n$ 个数 $a_i$ 围成环，$A$ 和 $B$ 两人轮流取数，$A$ 先取，两人都将采取最优策略，求最大化 $A$ 取到的数的和。

### Solution

感觉比绝大多数题解简单易懂。

设 $f_{i, j}$ 表示剩余的蛋糕区间为 $[i, j]$ 时最大的答案，把 $a$ 断环为链。

考虑如何转移，由于两人轮流取，需要分类讨论：

1. 当前轮 $A$ 取，剩余区间为 $[l, r]$，显然一定满足的前提条件是 $\text{remain}\equiv n \pmod 2$，其中 $\text{remain}$ 表示的是剩余蛋糕区间长度（简单手玩即可得证）。此时，$A$ 可以取 $a_l$ 或 $a_r$，此时 $f_{l, r}=\max\{f_{l, r-1}+a_r, f_{l+1, r}+a_l\}$。

2. 当前轮 $B$ 取，变量定义同上，前提条件为 $\text{remain}$ 和 $n$ 奇偶性不同。此时 $B$ 一定取 $\max\{a_l, a_r\}$，那么留给 $A$ 的就是其中较小的一个。

所以有如下方程：

$$
\text{len}\coloneqq l-r+1\\
f_{l, r}=
\begin{cases}
\max\{f_{l, r-1}+a_r, f_{l+1, r}+a_l\}, &\text{len}\equiv n \pmod 2\\
f_{l, r-1}, &a_l<a_r\ \text{and}\ \text{len}\not\equiv n \pmod 2\\
f_{l+1, r}, &a_l>a_r\ \text{and}\ \text{len}\not\equiv n \pmod 2
\end{cases}
$$

最后考虑边界，如果最后一轮是 $A$ 取的，也就是 $n$ 为奇数时，对于任意位置 $i$，贡献都为 $a_i$；反之由 $B$ 取，那么贡献为 $0$。

### Core Code

```cpp
n = read();
for (int i = 1; i <= n; i++) {
    a[i] = read();
    a[i + n] = a[i];
}
a[0] = a[n];
if (n & 1) {
    for (int i = 1; i <= n * 2; i++) {
        f[i][i] = a[i];
    }
}
for (int len = 2; len <= n; len++) { // len := remain cakes
    for (int l = 1; l + len - 1 <= n * 2; l++) {
        int r = l + len - 1;
        if ((len & 1) == (n & 1)) { // JOI
            f[l][r] = max({f[l][r], f[l + 1][r] + a[l], f[l][r - 1] + a[r]});
        } else { // IOI
            if (a[l] < a[r]) f[l][r] = max(f[l][r], f[l][r - 1]);
            else f[l][r] = max(f[l][r], f[l + 1][r]);
        }
    }
}
int ans = 0;
for (int i = 1;i <= n; i++) {
    ans = max(ans, f[i][i + n - 1]);
}
cout << ans << endl;
```

---

## 作者：末然Ender (赞：0)

# AT_joi2015ho_b ケーキの切り分け２ (Cake 2)

第一篇题解。这题之前的题解都被下了，我就来水一篇。

## 思路

看到这个题很容易想到区间 dp。

首先，因为是环形的蛋糕，我们拆环成链，复制一份蛋糕数组在原数组后面。

因为取的蛋糕是连续的，我们维护 $f_{i,j}$ 表示这个蛋糕还剩下区间 $[l,r]$ 时哥哥所能取到的最大答案，然后倒着求答案。

我们先考虑初始值：如果最后一块蛋糕$i$是哥哥取的，那么哥哥获得这个蛋糕的答案即 $f_{i,i}=a_i$，其中 $a_i$ 表示第 $i$ 块蛋糕的大小。

然后考虑状态转移方程：如果当前这个区间应该是让妹妹取的，当且仅当当前 $len$ 与 $n$ 奇偶性相同，其中 $len$ 表示剩余蛋糕长度,$n$ 是蛋糕个数，此时妹妹会选择最大的一块，也就是说：

$$
f_{i,j}=
\begin{cases}
f_{i,j-1} & a_i<a_j\\
f_{i+1,j} & \text{otherwise}
\end{cases}
$$

如果是哥哥取，当且仅当不是妹妹取，也就是当前 $len$ 与 $n$ 奇偶性不同，那么 $f_{i,j}$ 可能是哥哥从左边取一块蛋糕得到的，也可能是从右边取一块蛋糕得到的，所以：

$$f_{i,j}=max\{a_i+f_{i+1,j},a_j+f_{i,j-1}\}$$

然后我们考虑答案，因为最初什么都没拿的时候，蛋糕长度是 $n$，所以我们对于所有的 $f_{i,i+n-1}$求最大值即可。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
template<typename T>
void read(T& x){x=0;char ch=getchar();long long f=1;while(!isdigit(ch)){if(ch=='-')f*=-1;ch=getchar();}while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}x*=f;}
template<typename T,typename... Args>
void read(T& first,Args&... args){read(first);read(args...);}
template<typename T>
void write(T arg){T x=arg;if (x<0){putchar('-');x=-x;}if(x>9){write(x/10);}putchar(x%10+'0');}
template<typename T,typename... Args>
void write(T arg,Args... args){write(arg);if(sizeof...(args) !=0){putchar(' ');write(args...);}}
typedef long long ll;
const int N=4000+5;
int n;
ll a[N<<1],f[N][N<<1];
ll solve(int n){
	if(n&1){//JOI取走最后一块 
		for(int i=1;i<=n;i++)f[i][i]=a[1];
	}
	for(int len=1;len<=n;len++){
		for(int i=1;i<=n;i++){
			int j=i+len-1;
			if((len&1)==(n&1)){//该JOI取 
				f[i][j]=max(a[i]+f[i+1][j],a[j]+f[i][j-1]);
			}else{//该IOI取 
				f[i][j]=(a[i]<a[j])?f[i][j-1]:f[i+1][j];
			}
			if(j<=n)f[i+n][j+n]=f[i][j];
		}
	}
	ll ans=0;
	for(int i=1;i<=n;i++){
		ans=max(ans,f[i][i+n-1]);
	}
	return ans;
} 
int main(){
	int n;
	read(n);
	for(int i=1;i<=n;i++){
		read(a[i]);
		a[i+n]=a[i];
	}
	a[0]=a[n*2+1]=a[n]; 
	ll ans=solve(n);
	write(ans);
	putchar('\n');
	return 0;
} 
```

---

