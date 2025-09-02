# [USACO23OPEN] Rotate and Shift B

## 题目描述

**注意：本题的时间限制为 4 秒，是默认时间限制的 2 倍。**

为了庆祝春天的到来，Farmer John 的 $N$ 头奶牛发明了一种有趣的舞蹈，她们围成一个圆圈，并以一种可预测的方式重新排列自己。

具体来说，圆圈上有 $N$ 个位置，编号从 $0$ 到 $N-1$，其中位置 $0$ 紧接着位置 $N-1$。每个位置上有一头奶牛。奶牛的编号也从 $0$ 到 $N-1$。初始时，奶牛 $i$ 位于位置 $i$。你会被告知一组 $K$ 个“活跃”位置 $0 = A_1 < A_2 < \dots < A_K < N$，这意味着这些位置上的奶牛是下一批要移动的。

在舞蹈的每一分钟，会发生两件事。首先，活跃位置上的奶牛会旋转：位置 $A_1$ 的奶牛移动到位置 $A_2$，位置 $A_2$ 的奶牛移动到位置 $A_3$，依此类推，位置 $A_K$ 的奶牛移动到位置 $A_1$。所有这些 $K$ 次移动同时发生，因此在旋转完成后，所有活跃位置仍然恰好有一头奶牛。接下来，活跃位置本身会移动：$A_1$ 变为 $A_1 + 1$，$A_2$ 变为 $A_2 + 1$，依此类推（如果某个活跃位置 $A_i = N-1$，则 $A_i$ 会循环回到 $0$）。

请计算舞蹈进行 $T$ 分钟后奶牛的顺序。

## 说明/提示

对于上述样例，以下是前四个时间步的奶牛顺序和活跃位置 $A$：
```
初始，T = 0：顺序 = [0 1 2 3 4]，A = [0 2 3]
T = 1：顺序 = [3 1 0 2 4]
T = 1：A = [1 3 4]
T = 2：顺序 = [3 4 0 1 2]
T = 2：A = [2 4 0]
T = 3：顺序 = [2 4 3 1 0]
T = 3：A = [3 0 1]
T = 4：顺序 = [1 2 3 4 0]
```

$1 \leq K \leq N \leq 2 \cdot 10^5$，$1 \leq T \leq 10^9$。

- 输入 2-7：$N \leq 1000$，$T \leq 10000$。
- 输入 8-13：没有额外限制。

## 样例 #1

### 输入

```
5 3 4
0 2 3
```

### 输出

```
1 2 3 4 0
```

# 题解

## 作者：HyB_Capricornus (赞：11)

还没有人发题解，我来一发。
## Sol

设原序列为 $B$。

令操作 $C$ 为将 $B_{A_1}$ 挪至 $B_{A_2}$，将 $B_{A_2}$ 挪至 $B_{A_3}$，$\ldots$，将 $B_{A_n}$ 挪至 $B_{A_1}$。

令操作 $-x$ 为将序列逆时针转 $x$ 次，即 $B_1 \to B_2$，$B_2 \to B_3$，$\ldots$，$B_n \to B_1$。

令操作 $+x$ 为将序列顺时针转 $x$ 次。

重点来了：

**我们可以把将 $A$ 向后挪再进行 $C$ 操作想成先将 $B$ 逆时针转 $1$ 次，然后进行 $C$ 操作，然后再顺时针转回去**

当然每次转的次数不同，例如进行两次将 $A$ 向后挪再进行 $C$ 操作，我们就需要逆时针转 $2$ 次，然后进行 $C$ 操作，然后再顺时针转回去

则操作为：

$$C,-1,C,+1,-2,C,+2,-3,C,+3,\ldots,-(n-1),C,n-1$$

其中 $+$ 与 $-$ 可以抵消，抵消后结果为：

$$C,-1,C,-1,C,-1,\ldots,C,-1,C,n-1$$

$$C,-1,C,-1,C,-1,\ldots,C,-1,C,-1,n$$

我们称 $C,-1$ 为 $D$ 操作

我们创建数组 $jmp[i][j]$，其中 $jmp[i][j]=d$ 表示进行 $2^j$ 次 $D$ 操作把 $b_i$ 挪到了 $d$ 位置。

通过倍增，原始暴力的复杂度 $O(nT)$ 成功优化到 $O(n\log_{2}{T})$，复杂度显然可以通过本题。

最后不要忘了顺时针转 $n$ 次，这道题目就做出来了。

### [代码](https://www.luogu.com.cn/paste/it460l4q)

### 一些忠告：

1. 最后不要忘了顺时针转 $n$ 次。
2. 本人代码 $31$ 行，$y$ 很大，需要取模，否则会变成负数(赛时被卡)。
3. 请不要抄题解。

---

## 作者：player_1_Z (赞：5)

### 先来理解题目：

实际上就是**有一个 $ 0 \sim n$ 的数列，然后给了你 $k$ 个位置**（我们把这 $k$ 个位置存到 $b$ 数组里），每秒这 $k$ 个位置上的数都会进行一次**循环**（也就是在 $b_i$ 位置上的数 会到 $b_{i+1}$ 这个位置上，而 $b$ 这个数列最后一个位置上的数会到 $b_1$ 这个位置上）然后**问你 $t$ 秒后**这个数列是什么样的。

首先我们想到可以暴力枚举，枚举 $t$ 次 $b$ 数组。每次先把这个位置上的数存着，然后替换为上一个位置上的数，最后把这个位置加一**并把这个位置加一后的数对 $n$ 取模**。

### 暴力代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int k,n,t,a[200005],b[200005];
int main(){
	cin>>n>>k>>t;
	for(int i=1;i<=k;i++){
		cin>>b[i];
	}
	for(int i=0;i<n;i++) a[i]=i;
	while(t--){
		int h=a[b[k]];
		for(int i=1;i<=k;i++){
			int h2=h;
			h=a[b[i]];
			a[b[i]]=h2;
			b[i]=(b[i]+1)%n;
		}
	}
	for(int i=0;i<n;i++) cout<<a[i]<<" ";
	return 0;
}
```

但是，这样时间复杂度为 $O(t \ast k)$ 明显会超时。于是我们用样例把 $t \le 10$ 的情况全部打出来：
```cpp
Initial, T = 0: order = [0 1 2 3 4 ], A = [0 2 3 ]
T = 1: order = [3 1 0 2 4 ], A = [1 3 4 ]
T = 2: order = [3 4 0 1 2 ], A = [2 4 0 ]
T = 3: order = [2 4 3 1 0 ], A = [3 0 1 ]
T = 4: order = [1 2 3 4 0 ], A = [4 1 2 ]
T = 5: order = [1 0 2 4 3 ], A = [0 2 3 ]
T = 6: order = [4 0 1 2 3 ], A = [1 3 4 ]
T = 7: order = [4 3 1 0 2 ], A = [2 4 0 ]
T = 8: order = [2 3 4 0 1 ], A = [3 0 1 ]
T = 9: order = [0 2 4 3 1 ], A = [4 1 2 ]
T = 10: order = [0 1 2 3 4 ], A = [0 2 3 ]
```
我们发现其中 $0$,$1$,$3$,$4$,每过 $2$ 秒就会后移 $2$ 个位置，而 $2$ 每一秒都会后移 $1$ 个位置。

### 重点：

这是为什么呢？我们可以把开头提到的“循环”看成是踢数列中的数，每秒 $b$ 数组中的数都会把数列中对应的数踢到 $b$ 数组中下一个数的位置。那么以样例为例，取出 $b$ 数组中的 $0$ 和数列中的 $0$，发现从第一秒后，每过 $2$ 秒 $0$ 就会到后面第二个位置，直到时间结束。那为什么是 $2$ 秒和第二个位置。因为 $0$ 是被 $b_0$ “踢”着走的，每次会被“踢”到 $b_2$ 的位置，这之间相差 $2$，所以 $b_0$ 又花费 $2$ 秒到 $0$ 的位置。画一张图来形象地解释：

![图片解释](https://cdn.luogu.com.cn/upload/image_hosting/df1j7j6f.png?x-oss-process=image/resize,m_lfit,h_270,w_325)
其中红色箭头为 $b_0$ 的移动，黄颜色的笔迹为操作。

### 重点二：
如果我们把 $b_i$ 和 $b_{i+1}$ 的差表示为 $x$。那么 $b_i$ 和 $b_{i+1}$ 之间所有数都是在**第一次被踢**后每 $x$ 秒向后移动 $x$ 个数。

那么只需要把 $ 0 \sim n$ 中的每个数按这个规律算一次 $t$ 秒后的位置，并存在一个新数组的对应位置。最后输出这个数组的第 $ 0 \sim n$ 项就行了。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,t,a[200005][3],b[200005],c[200005];
int main(){
	cin>>n>>k>>t;
	for(int i=1;i<=k;i++) cin>>b[i];
	int x=b[2]-b[1],k1=2;
	for(int i=0;i<n;i++){
		if(i==b[k1]){
			if(k1==k) x=n-b[k1];
			else{
				k1++;
				x=b[k1]-b[k1-1];
			}
		}
		a[i][1]=x;
	}k1=1;
	for(int i=0;i<n;i++,x++){
		if(i==b[k1]){x=0;k1++;}
		a[i][2]=x;
	}
	for(int i=0;i<n;i++){
		int y;
		if(a[i][2]==0)
			y=i+int(ceil(t*1.0/a[i][1]))*a[i][1];
		else
			y=i+int(ceil((t-a[i][2])*1.0/a[i][1]))*a[i][1];
		c[y%n]=i;
	}
	for(int i=0;i<n;i++) cout<<c[i]<<" ";
	return 0;
}
```

---

## 作者：Yxy7952 (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/P9185)

## 题目大意

有 $n$ 个人围成一个圈，编号为 $0$ 到 $n-1$，有 $k$ 个活跃的位置 $0=a_{1}<a_{2}<a_{3}<\cdots<a_{k}<n$ 在每一分钟，活跃位置上的人会发生移动，$a_{1}$ 移动到 $a_{2}$，$a_{i}$ 移动到 $a_{i+1}$ 位置，$a_{k}$ 移动到 $a_{1}$，$k$ 个移动同时发生。

接下来活跃位置会发生改变：$a_{1}$ 变成 $a_{1}+1$，$a_{2}$ 变成 $a_{2}+1$，以此类推（如果 $a_{i}=n-1$，则 $a_{i}$ 变为 $0$）。请求出 $T$ 分钟后每个人的位置。

## 思路
在样例解释中，观察一列中一个数字出现的次数和位置。
```
Initial,
T = 0:  order = [0 1 2 3 4 ], A = [0 2 3 ]
T = 1:  order = [3 1 0 2 4 ], A = [1 3 4 ]
T = 2:  order = [3 4 0 1 2 ], A = [2 4 0 ]
T = 3:  order = [2 4 3 1 0 ], A = [3 0 1 ]
T = 4:  order = [1 2 3 4 0 ], A = [4 1 2 ]
T = 5:  order = [1 0 2 4 3 ], A = [0 2 3 ]
T = 6:  order = [4 0 1 2 3 ], A = [1 3 4 ]
T = 7:  order = [4 3 1 0 2 ], A = [2 4 0 ]
T = 8:  order = [2 3 4 0 1 ], A = [3 0 1 ]
T = 9:  order = [0 2 4 3 1 ], A = [4 1 2 ]
T = 10: order = [0 1 2 3 4 ], A = [0 2 3 ]

```

我们发现其中 $0,1,3,4$ 每过 $2$ 秒就会后移 $2$ 个位置，而 $2$ 每一秒都会后移 $1$ 个位置。

可以自己多测几组样例，发现一个规律：

>如果我们把 $a_{i}$ 和 $a_{i+1}$ 的差表示为 $x$。那么 $a_{i}$ 和 $a_{i+1}-1$ 之间所有数都是**第一次走后**每 $x$ 秒向后移动 $x$ 个数。

那么只需要把 $0 \sim n-1$ 中的每个数按这个规律算一次 $T$ 秒后的位置，并存在一个新数组的对应位置。最后输出就行了。

所有疑问和细节均体现在代码，代码注释和解释中。
## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,k,t;
ll a[200005],ans[200005];
ll xs(ll x,ll y){//向上取整 
	return (x+y-1)/y;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>n>>k>>t;
	for(ll i=0;i<k;i++) cin>>a[i];
	a[k]=n;
	for(ll i=0;i<k;i++){
		ll x=a[i+1]-a[i];//x 表示每次停的时间和每次走的距离。 
		for(ll j=a[i];j<a[i+1];j++){
			int p=xs(t-(j-a[i]),x)*x;//表示偏移量。 
			ll b=(j+p)%n;//用本身的值加上偏移量，注意 %n 保持在 0~n-1 范围内。 
			ans[b]=j;//记录答案。 
		} 
	}
	for(int i=0;i<n;i++) cout<<ans[i]<<" ";
	return 0;
}
```

```j-a[i]``` 表示 $j$ 第一次等多久才走。

```t-(j-a[i])``` 表示 $j$ 一共等的时间。

```xs(t-(j-a[i]),x)``` 等的时间除以一次等 $x$ 分钟，**向上取整**。表示等了几次，相当于走了几次。为什么要向上取整？请读者自己思考。

```xs(t-(j-a_{i}),x)*x``` 走的次数乘每次走的距离，表示偏移量。

---

## 作者：Mu_leaf (赞：3)

## [前言]
算是一道比较恶心的找规律的题目。

~~目前题解区最短代码。~~

## [思路]

先把玩一下样例：
| $T$ | $A_0$ | $A_1$ | $A_2$ | $A_3$ | $A_4$ |
| -----------: | -----------: | -----------: | -----------: | -----------: | -----------: |
| $1$ | $3$ | $1$ | $0$ | $2$ | $4$ |
| $2$ | $3$ | $4$ | $0$ | $1$ | $2$ |
| $3$ | $2$ | $4$ | $3$ | $1$ | $0$ |
| $4$ | $1$ | $2$ | $3$ | $4$ | $0$ |

会发现，$0,1,2$ 号牛在每个位置停留 $2$ 次，每次位置也会后移 $2$ 位。

于是有个普遍规律：对于每个满足大于等于 $a_i$ 且小于 $a_{i+1}$ 的 $j$，在每个位置停留 $a_{i+1}-a_i$ 次，每次位子往右移 $a_{i+1}-a_i$。




设 $ind$ 是 $a_{i+1}-a_i$，那么可以这 $ind$ 个数就可以算做一个集合。

那么我们每次都要找到 
$$\dfrac{T-j+ind-1}{ind}\times ind+a_i+j$$ 
这个代表着 $T$ 次交换操作后，$a_i+j$ 的位置（其中 $j$ 代表一个集合里的数）。


- 那么每次答案数组就是 
$$ans[(\lceil \dfrac {(T-j+ind-1)}{ind}\rceil+a[i]+j)\mod n]=a[i]+j$$

- 对于 $a_k$ 这个特殊情况只需要将 $a_k+1$ 赋值为 $n$ 就行了。

# Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,T,a[100005],ans[100005],nxt;
int main(){
	scanf("%d%d%d",&n,&k,&T);
	for(int i=1;i<=k;i++) scanf("%d",&a[i]);
	a[k+1]=n;
	for(int i=1,ind;i<=k;i++){
		ind=a[i+1]-a[i];
		for(int j=0;j<ind;j++) ans[((T-j+ind-1)/ind*ind+a[i]+j)%n]=(a[i]+j)%n;
	}for(int i=0;i<n;i++) printf("%d ",ans[i]);
	return 0;
}
```


---

## 作者：foryou_ (赞：2)

首先，我们很容易就能得出一个显而易见的结论：

若令原数组为 $order$，$K$ 个活跃位置分别为 $A_1,A_2,...,A_K$，则 
$$
order_{A_1} \to order_{A_2},order_{A_2} \to order_{A_3},...,order_{A_K} \to order_{A_1}
$$

的操作就等价于将 $order$ 数组顺时针旋转 $x$ 次，即

$$
order_1 \to order_2,order_2 \to order_3,...,order_N \to order_1
$$

再进行上述操作，最后逆时针旋转 $x$ 次转回来。

因为顺时针和逆时针的旋转方向是相反的，都旋转 $x$ 次正好抵消，所以上述结论的正确性也是显然的。

根据上述结论，题目所说的操作流程可以如下：

$$
1. \ R
$$
$$
2. \ +1,R,-1
$$
$$
3. \ +2,R,-2
$$
$$
\cdot \cdot \cdot
$$
$$
T. \ +(T-1),R,-(T-1)
$$

（其中 $R$ 表示将 $order$ 数组按 $A$ 数组轮换的操作，$+x$ 和 $-x$表示顺时针 / 逆时针旋转 $x$ 次 $order$ 数组的操作，$x.$ 表示第 $x$ 分钟进行的操作。）

这个过程中的顺时针和逆时针可以抵消，于是化简后的结果如下：

$$
1. \ R,+1
$$
$$
2. \ R,+1
$$
$$
3. \ R,+1
$$
$$
\cdot \cdot \cdot
$$
$$
T. \ R,+1,-T
$$

这样化简之后，每分钟的操作都变成了 $R,+1$，我们称这样的一次操作为 $S$。

于是整个题目的操作流程变成了每分钟进行一次 $S$ 操作，最后逆时针旋转 $T$ 次即可。

但是每次 $S$ 操作的时间都是 $O(N)$ 的，总时间复杂度还是 $O(TN)$，和暴力并无区别。

那么如何加快 $S$ 操作？既然朴素地旋转、轮换是不行的，那么我们就考虑使用**倍增**加快 $S$ 操作的速度。

具体而言：

- 建立倍增数组数组 $jmp$，其中 $jmp_{i,j}$ 表示用 $2^j$ 次 $S$ 操作能够把 $i$ 挪到的位置。

- 首先预处理 $jmp$ 数组，令 $jmp_{b_i,0}=i$，并令 $jmp_{i,j}=jmp_{jmp_{i,j-1},j-1}$（即从 $i$ 用 $2^{j-1}$ 次 $S$ 操作挪到的位置开始再进行 $2^{j-1}$ 次 $S$ 操作。

- 接着枚举 $2$ 的 $k$ 次幂，若 $2^k \le T$ 则进行 $2^k$ 次 $S$ 操作。

最后别忘了逆时针再旋转 $T$ 次就可以了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int n,k,t,tt; //tt是t的备份
int jmp[200031][64]; //倍增数组
int sor1[200031],sor2[200031],rot[200031],tmp[200031]; //order 数组，order 数组备份、A 数组、旋转辅助数组

void rotate1(){ //R 操作
	memset(tmp,-1,sizeof(tmp));
	for(int i=1;i<k;i++) tmp[rot[i]]=sor2[rot[i-1]];
	tmp[rot[0]]=sor2[rot[k-1]];
	for(int i=0;i<n;i++)
		if(tmp[i]+1) sor2[i]=tmp[i];
}
void rotate2(){ //顺时针旋转
	memset(tmp,0,sizeof(tmp));
	for(int i=0;i<n-1;i++) tmp[i]=sor2[i+1];
	tmp[n-1]=sor2[0];
	memcpy(sor2,tmp,sizeof(tmp));
}
void rotate3(){ //逆时针旋转
	memset(tmp,0,sizeof(tmp));
	for(int i=0;i<n;i++) tmp[i]=sor1[(i-tt%n+n)%n];
	memcpy(sor1,tmp,sizeof(tmp));
}

signed main(){
	cin>>n>>k>>t;
	for(int i=0;i<k;i++) cin>>rot[i];
	for(int i=0;i<n;i++) sor1[i]=sor2[i]=i;
	tt=t;
	
	rotate1(); //进行一次 R 操作 + 逆时针旋转一次，避免特判
	rotate2();
	
	for(int i=0;i<n;i++) jmp[sor2[i]][0]=i; //预处理 jmp 数组
	for(int j=1;j<=40;j++) //递推 jmp 数组
		for(int i=0;i<n;i++)
			jmp[i][j]=jmp[jmp[i][j-1]][j-1];
	for(int i=40;i>=0;i--){ //枚举 2^i
		if((1ll<<i)<=t){
			t-=(1ll<<i);
			for(int j=0;j<n;j++) tmp[jmp[j][i]]=sor1[j]; //进行 2^i 次 S 操作
			memcpy(sor1,tmp,sizeof(tmp));
		}
	}
	
	rotate3(); //逆时针旋转 T 次
	for(int i=0;i<n;i++) cout<<sor1[i]<<' ';
	return 0;
}
```

---

## 作者：kkxacj (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P9185)

#### 思路

先拿一个数据来模拟一下：

```
10 3 15
0 3 8

t
0    0 1 2 3 4 5 6 7 8 9
1    8 1 2 0 4 5 6 7 3 9
2    8 9 2 0 1 5 6 7 3 4
3    5 9 8 0 1 2 6 7 3 4
4    5 6 8 9 1 2 0 7 3 4
5    5 6 7 9 8 2 0 1 3 4
6    5 6 7 3 8 9 0 1 2 4
7    5 6 7 3 4 9 8 1 2 0
8    1 6 7 3 4 5 8 9 2 0
9    1 2 7 3 4 5 6 9 8 0
10   1 2 0 3 4 5 6 7 8 9
11   8 2 0 1 4 5 6 7 3 9
12   8 9 0 1 2 5 6 7 3 4
13   5 9 8 1 2 0 6 7 3 4
14   5 6 8 9 2 0 1 7 3 4
15   5 6 7 9 8 0 1 2 3 4
```
不难发现，$0 - 2$ 号牛在每个位置停留 $3$ 次，$3 - 7$ 号牛在每个位置停留 $5$ 次，$8 - 9$ 号牛在每个位置停留 $2$ 次，所以在 $a_i$ 到 $a_{i + 1}$ 
之间的数，如果 $t$ 足够大，就能发现它们每一次会在一个地方停留 $a_{i + 1} - a_i$ 次，下一次会移动到 $(a_{i + 1} - a_i) \bmod n$ 但可能 $t$ 不一定会被 $a_{i + 1} - a_i$ 整除，所以当不能被整除时位置要加上，公式可以去看代码，由于保证 $a_{0} = 0$，所以我们可以使 $a_{k + 1} = n$。


code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,t,a[100010],b[100010],kkk;
int main()
{
	scanf("%d%d%d",&n,&k,&t);
	for(int i = 1;i <= k;i++) scanf("%d",&a[i]);	
	for(int i = 0;i < n;i++) b[i] = i;
	a[k + 1] = n;
	for(int i = 1;i <= k;i++)
		for(int j = 0;j < a[i + 1] - a[i];j++)
			b[((a[i] + j) % n + (t - j + a[i + 1] - a[i]  - 1) / (a[i + 1] - a[i]) * (a[i + 1] - a[i])) % n] = (a[i] + j) % n;
	for(int i = 0;i < n;i++) printf("%d ",b[i]);
	return 0;
}
```



---

## 作者：small_john (赞：2)

## 思路

其实有些难度，需要用到一些找规律知识。

先看样例：

|$T$|$A_0$|$A_1$|$A_2$|$A_3$|$A_4$|
|:-:|:-:|:-:|:-:|:-:|:-:|
|$1$|$3$|$1$|$0$|$2$|$4$|
|$2$|$3$|$4$|$0$|$1$|$2$|
|$3$|$2$|$4$|$3$|$1$|$0$|
|$4$|$1$|$2$|$3$|$4$|$0$|

不难发现，$0\sim2$ 号牛在每个位置停留 $2$ 次，每次位子往右移 $2$，$3$ 号牛在每个位置停留 $1$ 次，每次位子往右移 $1$，$4$ 号牛在每个位置停留 $1$ 次，每次位子往右移 $1$。

所以得到一个普遍规律：对于每个满足大于等于 $a_i$ 且小于 $a_{i+1}$ 的 $j$，在每个位置停留 $a_{i+1}-a_i$ 次，每次位子往右移 $a_{i+1}-a_i$，设 $l=a_{i+1}-a_i$，其最后的位置为 $\lceil \dfrac{t-j}{l}\rceil\times l+a_i+j$ 对 $n$ 取余。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5+5;
int n,k,t,a[N],out[N],now[N]; 
signed main()
{
	cin>>n>>k>>t;
	for(int i = 1;i<=k;i++)
		cin>>a[i];
	a[++k] = n;//特殊处理a[k]到n-1的牛
	for(int i = 1;i<k;i++)
	{
		int l = a[i+1]-a[i];
		for(int j = 0;j<l;j++)
			out[((t-j+l-1)/l*l+a[i]+j)%n] = (a[i]+j)%n;
	}
	for(int i = 0;i<n;i++)
		cout<<out[i]<<' ';
	return 0;
}
```

---

## 作者：qcf2010 (赞：1)

## 思路

### 40分

直接按照题意模拟即可。时间复杂度 $O(tk)$，可以拿部分分。

### 100分

活跃位置上的奶牛轮换，活跃位置整体右移；活跃位置上的奶牛再轮换，活跃位置再整体右移……

这些操作其实就等价于：活跃位置上的奶牛轮换，所有奶牛整体左移一次（然后所有奶牛就欠一次右移的操作）；活跃位置上的奶牛再轮换，所有奶牛再整体左移一次（然后所有奶牛又欠一次右移操作）……最后到第 $t$ 分钟时，活跃位置上的奶牛轮换，所有奶牛整体左移一次（此时所有奶牛欠 $t$ 次右移）。最后，所有奶牛右移 $t$ 次。

因为 $t$ 很大，所以考虑倍增做法。

记 $m_{i,j}$ 为编号为 $i$ 的奶牛在第 $2^j$ 次操作后所在的位置。所有的 $m_{i,j}$ 计算出来后，整个题目就解决了。注意最后还要右移回去。

时间复杂度 $O(n\log t)$。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=200010;

int n,k;
ll t,t2;
int a[N],mp[N];
int m[N][35],x[N],y[N];

int main(){
	ios::sync_with_stdio(0);
	cin.tie();
	cout.tie();
	cin>>n>>k>>t;
	for(int i=1;i<=k;i++) cin>>a[i];
	for(int i=0;i<n;i++) mp[i]=i;
	t2=t;
	
	if(t<=10000){
		for(int i=1;i<=t;++i){
			int last=mp[a[k]],now;
			for(int j=1;j<=k;++j){
				now=mp[a[j]];
				mp[a[j]]=last;
				last=now;
			}
			for(int j=1;j<=k;++j){
				++a[j];
				if(a[j]==n) a[j]=0;
			}
		}
		for(int i=0;i<n;i++) cout<<mp[i]<<" ";
	}else{
		for(int i=1;i<n;i++){
			m[i][0]=i-1;
			x[i]=i;
		}
		m[0][0]=n-1;
		for(int i=1;i<k;i++) m[a[i]][0]=a[i+1]-1;
		m[a[k]][0]=n-1;
		for(int i=1;(1<<i)<=t;i++){
			for(int j=0;j<n;j++){
				m[j][i]=m[m[j][i-1]][i-1];
			}
		}
		for(int i=log2(t);i>=0;i--){
			if((1<<i)<=t){
				t-=(1<<i);
				for(int j=0;j<n;j++) y[m[j][i]]=x[j];
				for(int j=0;j<n;j++) x[j]=y[j];
			}
		}
		for(int i=0;i<n;i++) cout<<x[(i-t2%n+n)%n]<<" ";
	}
	return 0;
}

```

---

## 作者：raozf (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P9185)


### 题意

有 $N$ 个位置编号为 $0$ 到 $N-1$，其中位置 $i$ 上的元素为 $i$。有 $K$ 个关键位置初始值为 $A_i$，每秒钟关键位置上的元素向右循环轮换，然后所有关键位置本身加 $1$ 再模 $N$，求 $T$ 秒后每个位置上的元素。

### 思路

可以对关键位置的操作进行模拟，但这样做效率较低。只能换个视角，观察每个位置上的元素是如何变化的。

稍作分析可以发现，对于位置 $i$，它首先会受到左边离它最近的关键位置 $j$ 的影响，而每次元素的轮换与关键位置的变化都是向右的，所以当位置 $i$ 上的元素被轮换后，左边离它最近的关键位置还是 $j$，它会等待 $j$ 移动到当前位置，然后再次被轮换，以此循环往复。

综上所述，令 $d=A_{j+1}-A_j$，则位置 $i$ 的元素从第一次被轮换后，就会每过 $d$ 秒被向右轮换 $d$ 的距离。所以我们只需要单独考虑第一次轮换，之后的轮换统一进行计算即可。

我们可以按顺序对位置进行枚举，由于关键位置也是有序的，所以可以用双指针找到每个位置左边最近的关键位置 $j$。

### 复杂度


#### 时间复杂度：

枚举位置 $O(N)$。

对于每个位置查找关键位置总共 $O(K)$。

总时间复杂度为 $O(N)$。

#### 空间

记录元素 $O(N)$。

# Code:

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll N=1e5+5;
ll n,k,t;
ll b[N],a[N],d;
int main(){
    scanf("%lld%lld%lld",&n,&k,&t);
    for(int i=0;i<k;i++){
        scanf("%lld",&a[i]);
    }
    a[k]=a[0]+n;// 连接成环
    for(int i=0,j=0;i<n;i++){// 枚举位置
        j+=a[j]<=i;// 将要被置换的位置
        d=a[j]-a[j-1];// 每次置换移动的距离
        b[(i+((t-i)+a[j]-1)/d*d)%n]=i;// 记录移动后的位置
    }
    for(int i=0;i<n;i++){
      cout<<b[i]<<" ";
    }
    return 0;
}

```

---

## 作者：Nuclear_Fish_cyq (赞：0)

## 思路

每次关键位置都需要移动十分讨厌，我们直接反客为主让所有奶牛一起动。这样子，关键位置顺时针动一格等于所有奶牛逆时针动一格。然后我们可以发现每轮都是“关键位置奶牛动，所有奶牛一起动”这样的一个循环，总共有 $T$ 次。这个 $T$ 很大，而且这道题也很难找规律，要是能给 $T$ 套一个 $\log$ 就好了。二分这道题是不可能了，于是我们考虑倍增。我们设 $f_i$ 代表循环 $2^i$ 次形成的排列，那么我们有 $f_i = f_{i-1}\times f_{i-1}$，其中 $\times$ 代表排列的嵌套。所以我们就可以倍增出答案排列，最后不要忘记把所有奶牛转回原处，即所有奶牛顺时针旋转 $T\bmod n$ 格。

上代码。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define db double
#define ull unsigned long long
#define inf INT_MAX
#define linf LLONG_MAX
#define ninf INT_MIN
#define nlinf LLONG_MIN
//#define mod
//#define range
using namespace std;
int n, m, t, b[200000];
struct trans{
	int a[200000];
	trans operator *(trans b){
		trans res;
		for(int i = 0; i < n; i++){
			res.a[i] = a[b.a[i]];
		}
		return res;
	}
	trans operator +(int c){
		trans res;
		if(c < 0){
			c = -c;
			c %= n;
			c = n - c;
		}
		c %= n;
		for(int i = 0; i < n; i++){
			res.a[(i + c) % n] = a[i];
		}
		return res;
	}
}p, f[30], ans;
//如果再忘记把题目给的1~n变为0~n-1自罚20仰卧起坐
int main(){
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m >> t;
	for(int i = 0; i < m; i++){
		cin >> b[i];
	}
	for(int i = 0; i < n; i++){
		f[0].a[i] = i;
		ans.a[i] = i;
	}
	for(int i = 0; i < m; i++){
		f[0].a[b[i]] = ans.a[b[(i - 1 + m) % m]];
	}
	f[0] = f[0] + -1;
	if(t & (1 << 0)){
		ans = ans * f[0];
	}
	for(int i = 1; (1 << i) < t; i++){
		f[i] = f[i - 1] * f[i - 1];
		if(t & (1 << i)){
			ans = ans * f[i];
		}
	}
	ans = ans + t;
	for(int i = 0; i < n; i++){
		cout << ans.a[i] << " ";
	}
	return 0;
}

```

---

## 作者：Emplace (赞：0)

# 题目大意
总共有$n$个数，其中有 $k$ 个数，分别为 $A_1,A_2, \dots, A_k$，且 $0=A_1<A_2<\dots<A_k<n$，然后 $A_i$ 就会移动到 $A_{i+1}$。然后在下一轮 $A_i$ 就会变成 $A_i+1$。总共 $t$ 轮。
# 思路
如果我们把将 $A_i$ 移动到 $A_i+1$ 这个过程转换为将每个数在 $A_i$ 至 $A_{i-1}$ 都向左移动一位，而且这样还顺便做了 $A_i$ 移动到 $A_{i+1}$ 这个过程。然后因为前面都向左移动了一位，后面要向右移动 $t$ 位。
# Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int k,n,t,a[300000],b[300000],kun;
signed main(){
	cin>>k>>n>>t;
	for(int i=1;i<=n;i++)cin>>a[i];
	a[n+1]=k;
	for(int i=2;i<=n+1;i++)for(int j=0;kun<a[i];kun++,j++)	b[kun]=(j+t)%(a[i]-a[i-1])+a[i-1];	//进行一些操作，使得在区间内向左移动t位
	for(int i=0;i<k;i++)cout<<(b[(i-t+1000000000*k)%k])%k<<" ";//进行还原
	return 0;
}
```

---

