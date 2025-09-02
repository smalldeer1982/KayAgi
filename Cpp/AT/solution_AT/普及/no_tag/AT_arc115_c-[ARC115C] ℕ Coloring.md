# [ARC115C] ℕ Coloring

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc115/tasks/arc115_c

整数 $ N $ が与えられます。以下の条件を満たす長さ $ N $ の正の整数の列 $ A_1,A_2,\ldots,A_N $ であって、数列に現れる値の最大値が最小になるものを一つ出力してください。

- $ i $ が $ j $ の約数ならば、$ A_i\ \neq\ A_j $ $ (1\ \leq\ i\ <\ j\ \leq\ N) $

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^5 $

### Sample Explanation 1

この出力は以下の条件をすべて満たします。 - $ A_1\ \neq\ A_2 $ - $ A_1\ \neq\ A_3 $ - $ A_1\ \neq\ A_4 $ - $ A_2\ \neq\ A_4 $ また、登場する値の最大値が $ 2 $ 以下である数列であって、これらの条件をすべて満たすものは存在しないので、この出力は適当です。

## 样例 #1

### 输入

```
4```

### 输出

```
1 2 2 3```

# 题解

## 作者：chinazhanghaoxun (赞：5)

## 题意

本道题目的翻译已经非常清晰了，这里就不再重复了。
## 分析

这是一道很符合 ARC 风格的考验思维的构造题，推规律的过程其它楼主也讲得很好了，我就讲一下大概的过程和结论吧。

通过观察样例~~和人脑计算~~，不难得出一个形如
```1 2 2 3 3 3 3 4 4 4 4 4 4 4 4```
的数列。可以发现，每一个数字出现的次数正好是 $2^k$，具体地说，数为 $i$ 的数字会出现 $2^{i-1}$ 次，那么就有了一种很简单的思路。

思路为根据 $N$ 的大小直接循环，同时使用变量 $num$ 记录当前该输出哪个数字。如果循环次数达到了 $2^k$，那么 $num+1$，否则 $num$ 不变，只要输出 $num$ 就行了，代码非常简短。
## 代码+注释


```cpp
#include<bits/stdc++.h>
using namespace std;
int now_number;
int power,n;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		if(i==pow(2,power)){ //如果是2的次方
			now_number++; //该输出的数字就要加一
			power++;//指数也要加一，方便下次快速判断
		}
		cout<<now_number<<' '; //输出当前数字
	}
	return 0;
}
```

---

## 作者：rui_er (赞：5)

显然 $A_1,A_2,A_4,A_8,\cdots$ 必须互不相同，因此最大的数一定不小于 $\lfloor\log_2n\rfloor+1$，猜想可以取到 $\lfloor\log_2n\rfloor+1$。

构造 $A_i=\lfloor\log_2i\rfloor+1$，则对于任意 $A_i=A_j$ 都有 $2i > j$，不存在倍数关系。

时间复杂度 $\Theta(n)$。

```cpp
// Problem: C - ℕ Coloring
// Contest: AtCoder - AtCoder Regular Contest 115
// URL: https://atcoder.jp/contests/arc115/tasks/arc115_c
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
using namespace std;
typedef long long ll;

template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}

int main() {
	int n;
	scanf("%d", &n);
	for(int L = 1, R, u = 1; L <= n; L = R + 1, u++) {
		R = 2 * L - 1;
		chkmin(R, n);
		rep(i, L, R) printf("%d%c", u, " \n"[i==n]);
	}
	return 0;
}
```

---

## 作者：_Star_Universe_ (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/AT_arc115_c)
### 思路一
这是一个构造题，我们可以找一找规律，推出这个序列。

首先 $1$ 是所有正整数的因子，第一个位置为 $1$，然后就是第二个位置，那么由于 $1$ 是 $2$ 的因子，所以第二个位置为 $2$，然后 $2$ 不是 $3$ 的因子，第三个位置还是 $2$，然后由于 $2$ 是 $4$ 的因子，第四个位置就是 $3$，就得到了样例输出。

继续往后，序列就是这样：
$$A=\{1,2,2,3,3,3,3,4,4,4,4,4,4,4,4,\dots\}$$

规律不就出来了吗？第 $i$ 个数使用 $2^{i-1}$ 后换用下一个，每一个 $A_i$ 就可以用 $\log(i)+1$ 得到，看题解区也有几篇了，就不多讲。

### 思路一的代码和思路二
```c
#include<bits/stdc++.h>
using namespace std;

int main(){
	int n,a[100005];
	cin>>n;
	for(int i=1;i<=n;i++){
		a[i]=log2(i)+1;
	}
	for(int i=1;i<=n;i++){
		cout<<a[i]<<" ";
	}
	return 0;
}
```

其实也可以用统计每个数出现次数的方法解决本题，如果输出的值 $i$ 的数量达到了 $2^{i-1}$ 个，将 $i+1$  赋值给 $i$，开始输出这个新的值，直到遍历完为止。

由于题解区各种思路都有了，笔者也很无奈，求管理员通过这篇题解。

---

## 作者：_Deer_Peach_ (赞：2)

这道题应该是一道考验思维的构造题。

思路：

要使最后一个数最小，那么开头就要最小，为 $1$（因为题目要求）。接着就是第二个数，因为 $1$ 是 $2$ 的因数，所以要不同，第二个数就为 $2$。又因为 $2$ 的最小倍数（除自身外）是 $4$，所以第四个数就不能为 $2$ 了，改成 $3$。$4$ 的最小倍数（除自身外）是 $8$，所以第四个数就不能为 $3$ 了，改成 $4$。

推到这，规律已经很明显了，也就是说，改变一个数后，改变的数的数量就是那一个数前面一个数的下标。光讲可能描述不清楚，接下来就演示一遍：
```
数字：1  2  2  3  3  3  3  4  4  4  4  4  4  4  4
下标：1  2  3  4  5  6  7  8  9  10 11 12 13 14 15
1是2的因数，下标为2的数字通过加1改变，改变后的数字数量为2
2是4的因数，下标为4的数字通过加1改变，改变后的数字数量为4
4是8的因数，下标为8的数字通过加1改变，改变后的数字数量为8
```

演示过后，应该就很清楚了，接下来就可以写代码了：
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,cnt=1,las=1,now=1;//las表示被改变数字的下标，也是改变后数字的数量，now表示当前数的下标
signed main(){
	cin>>n;
	while(n--){
		cout<<cnt<<" ";//输出
		if(now%las==0){//判断是否为因数
			now*=2;//求处自身外的最小倍数
			now++;//改变数字后下标要加一，蒟蒻就是在这被坑了
			cnt++;//通过加一改变数字
		}las++;//当前数字下标加一
	}
	return 0;//结束
}
```

---

## 作者：Pyrf_uqcat (赞：2)

一道构造题，带大家手推一下这个序列。

------------
第一个位置：$1$ 是所有正整数的因数且是最小的正整数，所以 $1$ 是第一个数（还有一种方法，就是直接看样例输出，第一个是 $1$）。

第二个位置：一是二的因数，所以不能填 $1$，那就填其次小的，也就是 $2$（样例中第二个数也是 $2$）。

第三个位置：二不是三的因数，还是填 $2$（样例第三个数是 $2$）。

第四个位置：二是四的因数，往上加一，填 $3$（样例第三个数是 $3$）。

第五至七个位置：不是四的倍数，继续填 $3$。

第八个位置：四是八的因数，加一填 $4$。

第九到十五个位置：不是八的倍数，填 $4$。

剩下的不打了，规律也很明显了。第 $j$ 个数出现 $2^{j-1}$ 次。所以第 $j$ 个数就是 $\log(j)+1$。

---

## 作者：joker_opof_qaq (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_arc115_c)

考虑直接顺着推过去，第 $1$ 个数最小就填 $1$。

接下来第 $2$ 和 $3$ 位，因为已经存在倍数，所以就不能再填 $1$ 了，只能填 $2$，到第 $4$ 位就不能继续填 $2$ 了，就这样一到再次出现倍数关系的下标就 $+1$，因为最小的质数是 $2$，所以就到 $2^n$ 时将输出的数 $+1$，其他时候不变。

就按照上述方法模拟即可。

```cpp

#include<iostream>
#include<algorithm>
#include<cstdio>
#include<iomanip>
#include<cstring>
#include<string>
#include<cmath>
#include<queue>
#include<map>
#include<list>
#include<stack>
#include<cctype>
#include<cstdlib>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+ch-48;ch=getchar();}
	return x*f;
}
inline void write(int x) {
	if (x<0)x=-x,putchar('-');
	if (x>9)write(x/10);
	putchar(x%10+'0');
}
int n,cnt=1,outputs=1,pre=1;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		if(i==2*pre)outputs++,pre=i;
		cout<<outputs<<" ";
	}
	return 0;
}

```

---

## 作者：Red_river (赞：1)

#### 题外话
这道题一看就很简单，毕竟输入只有一个数，立马就想到了~~打表~~。哦，是~~高级~~一点的打表。

看其他题解好像一直在讨论 $\log(j)+1$ 等。但其实大可不必！对于一个这么简单的题来说，其实有个简单但效率没那么高的方法，这里分享给大家，也可以借来思考一下。

### 题目大意
给你一个数 $N$ 然后构造一个长度为 $ N $ 的序列 $ A $，对于下标 $ i $，$ j $ 若 $ i $ 为 $ j $ 的因数则$ A_i \neq A_j $。

其实我们一看到因数，很容易想到筛。于是我们可以类比，发现只要枚举一个数 $X$ 的倍数，这个倍数就是 $X$ 的答案加一。毕竟他们只要不同就行了。就算是错的，也会被正确答案覆盖，似乎又有点像递推了，具体可看代码。

### CODE
```cpp
#include<bits/stdc++.h>
#define wk(x) write(x),putchar(' ')
#define wh(x) write(x),putchar('\n')
#define ll long long
#define ull unsigned long long
#define ri register int
#define INF 2147483647
#define mod 998244353
#define N 1000005
#define NO printf("No\n")
#define YES printf("Yes\n")
#define f(x,k,y) for(int x=k;x<=y;x++)
using namespace std;
int n,m,k,jk,ans,sum,num,cnt,tot;
int dis[N],vis[N],wis[N],f[N];
//快读快输。
void read(int &x)
{
	x=0;int ff=1;char ty;
	ty=getchar();
	while(!(ty>='0'&&ty<='9'))
	{
		if(ty=='-') ff=-1;
		ty=getchar();
	}
	while(ty>='0'&&ty<='9')
		x=(x<<3)+(x<<1)+ty-'0',ty=getchar();
	x*=ff;return;
}

void write(int x)
{
	if(x==0){
		putchar('0');return;
	}
	if(x<0){
		x=-x;putchar('-');
	} 
	char asd[201];int ip=0;
	while(x) asd[++ip]=x%10+'0',x/=10;
	for(int i=ip;i>=1;i--) putchar(asd[i]);
	return;
}

signed main()
{
	read(n);f[1]=1;
	for(int i=1;i<=n;i++){
		for(int j=1;i*j<=n;j++){
			f[i*j]=1+f[i];//不难发现，如果答案错了的话，就会被之后的正确答案覆盖掉，所以能过。
		}
	}
	f[1]=1;
	for(int i=1;i<=n;i++) if(!wis[f[i]]) wis[f[i]]=++cnt;//判断每种数应输什么。
	for(int i=1;i<=n;i++) wk(wis[f[i]]);
  putchar('\n');//AT特性，有时又不用。
	return 0;
}
```

---

## 作者：xu_zhihao (赞：0)

### 题目理解：

- 看了看题解几乎都是构造序列，但这题其实可以用暴力做。初始将序列最大数设为 $1$。$A_1$ 位置一定为 $1$，接下来的每个位置 $2\le i \le n$，都枚举位置 $i$ 的所有因数，如果其某个因数为序列最大数，即将序列最大数加 $1$（依据题目描述对于下标 $ i $, $j\ (1 \le i < j \le N) \ $，若 $ i $ 为 $ j $ 的因数，$ A_i \neq A_j$）。最后 $A_i$ 位置即为序列最大数。此算法复杂度为 $O(\sum_{i=2}^{n}\lfloor{\sqrt{i}}\rfloor)$，约是 $O(n\lfloor{\sqrt{n}}\rfloor)$。明显小于题目时限。

### AC 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1000010];
int main()
{
	int n;
	cin>>n;
	int cnt=1;
	a[1]=cnt;
	for(int i=2;i<=n;i++)
	{
		int f=0;
		for(int j=1;j*j<=i;j++)
		{
			if(i%j==0)
			{
				if(a[j]==cnt)
				{
					f=1;
					break;
				}
				int p=i/j;
				if(a[p]==cnt)
				{
					f=1;
					break;
				}
			}
		}
		if(f)
		{
			cnt++;
		}
		a[i]=cnt;
	}
	for(int i=1;i<=n;i++)
	{
		cout<<a[i]<<" ";
	}
 } 
```
[AC 记录](https://www.luogu.com.cn/record/153508383)

---

## 作者：lgydkkyd (赞：0)

这是一道构造题，题目让我们构造一个序列使得任意一个位置的数与其因数位置上的数不等，且尽量要小。接下来分析一下，首先因为 $1$ 是所有的正整数的因子之一，所以一定要把 $1$ 放在最前面，再推第 $2$ 个数，由于 $1$ 是 $2$ 的因子，则第 $2$ 个数不能是 $1$，那就取正整数中第 $2$ 小的数，也就是 $2$，接下推第 $3$ 个数，由于 $1$ 是 $3$ 的因子，则第 $3$ 个数不能为 $1$，同样取 $2$，后面的书都可以以此类推。最后推出的序列为 $1$，$2$，$2$，$3$，$3$，$3$，$3$，$4$，$4$，$4$，$4$，$4$，$4$，$4$，$4$ 等等。也就是 $x$ 在序列中出现了 $2$ 的 $x-1$ 次。说刚好每个数都可以用函数计算，请看代码。
# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
inline void read(int &a){//快读
	a=0;
	char c;
	while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9') a=a*10+c-'0',c=getchar();
}
inline void write(int a){//快写
	if(a>9)write(a/10);
	putchar(a%10+'0');
}
int n;
int main(){
    read(n);
    for(int i=1;i<=n;i++){
        write(int(log2(i)+1));//这就是上文说的函数log,第i个数就是log2(i)+1,可以直接输出
        printf(" ");//每输出一个数都要加上空格
    }
    return 0;//华丽结束~~~
}
```

---

## 作者：Hog_Dawa_IOI (赞：0)

对于构造 $A_i= \left\lfloor \log_2 i\right\rfloor+1$ 的做法题解区已有详细说明，在此不多赘述。这里介绍一种朴素的递推方法。       
对于每个 $i$，如果 $j$ 是 $i$ 的因数，那么 $A_i \ne A_j$。又因为题目要求让最大的数尽量小，所以我们可以取所有 $i$  的因数 $j$ 中最小的 $A_j$，令 $A_i=A_j +1$。即：
$$A_i= (\min_{j|i}{A_j})+1$$   

问题是，在枚举 $i$ 的时候，我们不能从 $1$ 到 $i$ 枚举 $j$，那样的话时间复杂度就是 $O(n^2)$。但其实我们可以只枚举到 $\sqrt i$，对于每一个 $j|i$，同时对 $A_j$ 和 $A_{i/j}$ 进行判断。这样时间复杂度就被降到了大约是 $O(n \sqrt n)$。
```cpp
#include<cmath>
#include<cstdio>
#include<cstring>
using namespace std;
long long n,f[100005];
int main()
{
    scanf("%lld",&n),f[1]=1;
    for (int i=2;i<=n;i++)
    for (int j=1;j*j<=i;j++)
    if(i%j==0) f[i]=(f[i]>(f[j]+1)?f[i]:f[j]+1)
    >f[i/j]+1?(f[i]>(f[j]+1)?f[i]:f[j]+1):f[i/j]+1;
    for(int i=1;i<=n;i++) printf("%lld ",f[i]);
}
```

---

## 作者：XYQ_102 (赞：0)

## 分析
如果第一个位置填 $1$，可以发现限制条件实际就是深度要超过约数的深度，直接建图跑最长路即可。
## AC Code
```cpp
#include <cstdio>
#define rr register
using namespace std;
const int N=100011;
struct node{int y,next;}e[N<<4];
int a[N],as[N],n,et;
inline void print(int ans){
    if (ans>9) print(ans/10);
    putchar(ans%10+48);
}
inline void add(int x,int y){
	e[++et]=(node){y,as[x]},as[x]=et;
}
signed main(){
	scanf("%d",&n),a[1]=1;
	for (rr int i=1;i<=n;++i)
	    for (rr int j=i*2;j<=n;j+=i) add(j,i);
	for (rr int i=2;i<=n;++i)
	for (rr int j=as[i];j;j=e[j].next)
	    if (a[i]<a[e[j].y]+1) a[i]=a[e[j].y]+1;
	for (rr int i=1;i<=n;++i) print(a[i]),putchar(i==n?10:32);
	return 0;
}
```

---

## 作者：Fa_Nanf1204 (赞：0)

## 算法思路：数学
### 分析
这题代码不难，主要是思路。我们可以手推一下这个序列情况。

要求每个数最小，那么 $A_1$ 取数字 $1$，因为 $1$ 是所有数字的因数且最小。

再看 $A_2$，$A_2$ 不能与 $A_1$ 相等，所以取尽可能小的 $2$。

再看 $A_3$，可以取 $2$。

再看 $A_4$，$A_4$ 不能与 $A_1$ 和 $A_2$ 相等，所以取尽可能小的 $3$。

以此类推。

扩展这个序列，可以得到：$1\;2\;2\;3\;3\;3\;3\;4\;4\;4\;4\;4\;4\;4\;4$。
### 结论
可以得出结论：数字 $i$ 在序列中出现了 $2^{i-1}$ 次。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,cnt=0,j=0;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
		j++;//计数当前数出现了几次 
		if (j<=pow(2,cnt)){//判断数量是否符合要求 
			cout<<cnt+1<<" ";//输出 
		}
		else{
			j=1;//重新计数 
			cnt++;
			cout<<cnt+1<<" ";//输出 
		}
    }
    return 0;
}
```

---

## 作者：封禁用户 (赞：0)

## 题意简述
构造一个长度为 $N$ 的正整数序列，使得任意 $i$ 与 $j$ 满足 $i\mid j$ 时 $A_i\ne A_j$。
- - -
## 分析过程
首先，$1$ 是所有数的因数，所以对于任意的 $i$ 都满足 $A_1\ne A_i$，即在序列中最大的数尽量小时 $A_1=1$。

其次考虑 $A_2$，$A_2\ne A_1$，所以 $A_2$ 最小取 $2$。

再考虑 $A_3$，$A_3\ne A_1$，所以 $A_3$ 最小也取 $2$。

以此类推。

- - -
### 结论
序列为 $1,2,2,3,3,3,3,4,4,4,4,4,4,4,4,\dots$。

**即对于每一个 $A_i$ ，其值为 $\lfloor\log_2 i\rfloor+1$。**
- - -
这题代码实现并不难，但是有一定思维难度。

AC code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)cout<<int(log2(i)+1)<<' ';
    return 0;
}
```

---

## 作者：zeekliu (赞：0)

附：[原题](https://atcoder.jp/contests/arc115/tasks/arc115_c) 链接。

首先，我们需要注意，题意中说的是，若 $ i $ 为 $ j $ 的因数，$ A_i \neq A_j $，而非其所有因数都两两不相同。

那么最朴素的想法就是，假设 $ i $ 有 $ t $ 个因数，那么它就是 $ t-1 $，但稍微算算就知道，这个数列的最大值实在是**太大了**。

比如：从 $ 1 $ 到 $ 7 $，如果按这样算，最大就是 $ 4 $：

> $ 1,2,2,3,2,4,2 $

但实际上最大 $ 3 $ 即可。

所以怎么办呢？

我们发现，对于 $ 6 $，其实它并不需要是 $ 4 $，因为有重复的 $ 2 $，$ 3 $ 即可。

因此，对于部分较小的因数，可以想办法将他们对应的数值构造成一样的，从而减小大下标下的数值。

我们考虑将他们按如下的方法分组：

$ \{1\} $

$ \{2,3\} $

$ \{4,5,6,7\} $

$ \{8,9,10,11,12,13,14,15\} $

等等。

这样可以保证每组里面没有任何一个数是另一个数的因数或者倍数，因此每组中的数值可以相等而不违反题意。

每组有一个数值，比如第 $ 1 $ 组中的下标对应数值 $ 1 $，第 $ 2 $ 组中的下标对应数值 $ 2 $ 等等。

稍加观察（~~傻子都知道~~）可得，按以上方法得到的数值，对于下标 $ i $ 有：

$$ A_i=\log(i)+1 $$

那么就是代码了：

温馨提示：如果用的不是 `printf("%d ",log2(i)+1)`，别忘了强制转换类型为 `int`。

```cpp
//ARC115C 22.11.20
#include <bits/stdc++.h>
using namespace std;
int n;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin>>n;
    for (int i=1;i<=n;i++) cout<<(int)log2(i)+1<<" ";
    exit(0);
}
```


---

## 作者：zsh_haha (赞：0)

这让我想到了二进制。

$(1)_2\ \ \ \ \rightarrow(1)_{10}$

$(10)_2\ \ \rightarrow(2)_{10}$

$(11)_2\ \ \rightarrow(3)_{10}$

$(100)_2\rightarrow(4)_{10}$

$(101)_2\rightarrow(5)_{10}$

$(110)_2\rightarrow(6)_{10}$

$(111)_2\rightarrow(7)_{10}$

$...$

观察上表我们发现，二进制是一位数的数字，两两不为倍数关系；二进制是两位数的数字，两两不为倍数关系；二进制是三位数的数字，两两不为倍数关系……

所以，二进制的 $A_i$ 有几位，十进制的 $A_i$ 就是多少。

### 代码：

```cpp
#include<bits/stdc++.h> 
using namespace std;
int a[100001];
int main(){
	int now=1,nnow=1;
	int n;
	cin>>n;
	for(int i=1;i<=n;){
		for(int j=1;j<=now&&i<=n;j++,i++){
			a[i]=nnow;
		}
		nnow++;//十进制 Ai 加一，二进制 Ai 加一位 
		now*=2;//位数为 nnow 的二进数的个数 
	}
	for(int i=1;i<=n;i++){
		cout<<a[i]<<' ';
	}
    return 0;
}
```

---

## 作者：DengDuck (赞：0)

我们不难想到一种构造方式，$A_i=\log_2 i$ ，这个结论是正确的，可以通过测试。

我们证明一下，显然，$i$ 的最小因数最起码也得是 $2$ 吧，就算它是 $2$，对应的最大因数 $0.5i$ 显然对应的 $A_{0.5i}$ 也会小于 $A_i$ .

因为根据 $\log_2$ 的定义，它表示一个数字有多少个 $2$，可是你都除了一个 $2$，肯定会多一个 $2$ 啊，那我的值肯定会小一点，也就不相等了。

如果是其他的数字，那中间差的只会更多，所以也是跟上面一样的。

所以我们构造的这个数组是正确的。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n;

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cout<<int(log2(i)+1)<<' ';
    }
}
```

---

