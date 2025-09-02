# 「MCOI-08」Fill In

## 题目背景

$$\begin{aligned}\text{sdjvlajdiofjoiw{\color{1f1e33}n}eglaj}\\\text{pcji{\color{1f1e33}2}gweiruitowoeuri}\\\text{cnvak{\color{1f1e33}5}jflkjweirqoiru}\\\text{rrrwei{\color{1f1e33}f}dlskfjqfafdfaff}\\\text{nmslfjwiejfijlxkjfq{\color{1f1e33}b}el}\\\text{mmm{\color{1f1e33}b}fsfmkdfmksld}\\\text{erjf{\color{1f1e33}n}kerjkwerjkwjeri}\\\text{sdfafafaf{\color{1f1e33}r}fxvzxvzvzx}\end{aligned}$$

## 题目描述

Dream 有一个长度为 $n$（$1\le n\le 10^5$）的正整数数组 $a_1,a_2,\dots,a_n$，其中对于 $i=1,2,\dots,n$，满足 $1\le a_i\le 1000$。

他计算了前缀和数组 $p_i=a_1+a_2+\dots+a_i$，保证对于 **原前缀和数组** 有任意 $1 \le i <n$ 都有 $p_i<p_{i+1}$。

现在 Tommy 偷走了这个数组以及将 $p$ 的若干个元素替代为 $-1$。给定当前的 $p$ 数组，请恢复任意一组合法 $a_1,a_2,\dots,a_n$，可证明一定存在一个数组 $a_i$ 满足要求。

## 说明/提示

#### 样例 1 解释

输出的序列 $a_i$ 一定满足要求：

- $p_1=10=a_1$；
- $p_3=20=a_1+a_2+a_3$；
- $p_5=30=a_1+a_2+a_3+a_4+a_5$。

#### 数据规模与约定

对于 $100\%$ 的数据，$1\le n,\sum n\le 10^5$，并保证存在至少一个合法 $a$ 数组。

 - Subtask 1（50 pts）：对于 $i=1,2,\dots,n$，$p_i\neq -1$；
 - Subtask 2（30 pts）：保证不存在 $i$ 使得 $p_i=p_{i+1}=-1$；
 - Subtask 3（20 pts）：无特殊限制。

## 样例 #1

### 输入

```
2
5
10 -1 20 -1 30
6
-1 -1 -1 -1 -1 -1```

### 输出

```
10 5 5 5 5
1 1 4 5 1 4```

# 题解

## 作者：SSqwq_ (赞：6)

## 题意
给定元素个数为 $n$ 的 $a$ 数组的前缀和数组 $p$ ， $p$ 数组的一部分被隐去（题目体现为 $-1$ ），要求复现任意符合要求的 $a$ 数组，**且对于任意** $ 1 \leq i \leq n$ ， **$a_i$ 不得大于 $1000$** 。

## 思路
### 思路1：50 分
相信与许多人的思路一样，遍历 $p$ 数组，遇见 $p_i$ 不是 $-1$ ，就将 $i$ 之前的方案输出出来。为了保证分配的数都是整数，将分配区间内的前 $i-1$ 个数全部设为 $1$ ，而第 $i$ 个数自然就是 $p_i-(i-1)$ 。

但是，这个做法被毙掉了。

### 思路2：100 分
大家注意看一下题意中被我加粗的那句话。

> 且对于任意 $ 1 \leq i \leq n$ ， $a_i$ 不得大于 $1000$ 

若构造数据使得 $p_1=p_2=-1 $ ，$p_3=10000$ ，显而易见的，50 分思路构造的 $a$ 数组的第 $3$ 项将会是 $9998$ ，不符合题意。

因此，我们做到**尽量平摊**，使用整除的方式将 $p_i$ 平均分配到整个分配区间中。注意若 $p$ 数组的末尾有若干个 $-1$ ，则一律输出 $1$ 。

于是下面的AC代码就呼之欲出了。
```cpp
#include<bits/stdc++.h>
using namespace std;
int p[100001];
int main()
{
	register int t;
	scanf("%d",&t);
	while(t--)
	{
		register int n;
		register int mult=0;
		register int chuli=0;
		scanf("%d",&n);
		for(register int i=1;i<=n;i++)scanf("%d",&p[i]);
		for(register int i=1;i<=n;i++)
		{
			mult++; //变量mult用于记录分配区间长度
			if(p[i]!=-1)
			{	
				p[i]-=chuli;
				chuli+=p[i];
				register int tmp=p[i];
				for(register int j=0;j<mult-1;j++)
				{
					printf("%d ",p[i]/mult); //将p[i]平摊到分配区间中
					tmp-=p[i]/mult;
				}
				printf("%d ",tmp);
				mult=0;
			}
		}
		for(register int j=0;j<mult;j++)
		{
			printf("1 ");  //p数组末尾仍有-1，一律输出1
		}
	}
	return 0;
}
```


---

## 作者：Dream_weavers (赞：6)

$\texttt{upd 2022.4.23}$ 因为此题解被[这组数据](https://www.luogu.com.cn/discuss/430918) hack 了，所以在题解中改了一些部分。

## 题意

有一个长度为 $n$ 数组 $a$，并且有一个前缀和数组 $p$（$p_i=a_1+a_2+\cdots+a_i$）。现在已将 $p$ 数组若干个元素替换为 $-1$，请还原出一组**满足条件** $a$。

数据范围：$1\le n\le10^5,1\le a_i \le1000$

## 思路+代码

### 50分做法

这种做法**只能**能得到 Subtask 1 的 $50$ 分，但只要学过前缀和就能得到这部分分。

因为 Subtask 1 中 $p_i\ne-1$，就可以直接**套用前缀和公式**推出：$a_i=p_i-p_{i-1}$。代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int a[N],p[N],t,n;
signed main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d",&p[i]);
			a[i]=p[i]-p[i-1];
			printf("%d ",a[i]);
		}
		printf("\n");
	}
    return 0;
}
```

------------

### 100分做法

这种做法就要考虑到有些 $p_i=-1$ 的情况了。

循环遍历数组 $p$，建立一个结构体数组（设其为 $f$）记录 $p$ 中**不为** $-1$的两个端点和其区间和，方便后面的区间修改。比如 $p_i$ 和 $p_j$ 为两个不为 $-1$ 的点（$i<j$），那么左端点 $l=i+1$，右端点 $r=j$，区间和 $sum=p_j-p_i$（$l\le r$，左右端点可能相等，也就是可能一次只修改一个点）。每记录一次，更新 $f$ 的下标。

记录后循环 $f$，把 $sum$ **平均分**给 $a_l$ 至 $a_r$ 之间的数，让 $a_i$ 尽可能得大（$l\le i\le r$）。每个数平均分到的为 $shang=\left\lfloor\dfrac{sum}{r-l+1}\right\rfloor$，余下的数是 $yu=sum \bmod (r-l+1)$。将 $a_i$ 修改为 $shang$，若 $yu>0$，就将从 $a_l$ 到 $a_{l+yu-1}$ 的数 $+1$，防止 $a_i>1000$（修改了这句话）。

上面的两大步是可以合并在一起循环的，~~但我觉得那样太麻烦拆成了两步。~~

但最后还可能有一些连续的 $-1$，只要把那些没有修改的 $a_i$（也就是 $a_i=0$）变成 $1$ 即可。

------------

举个例子：

```
输入
1
10
10 -1 20 -1 25 -1 -1 35 -1 -1  
```
| 修改次数 | $l$ | $r$ | $sum$ | $shang$ | $yu$ | $a$数组 |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| $1$ | $1$ | $1$ | $10$ | $10$ | $0$ | $10\ 0\ 0\ 0\ 0\ 0\ 0\ 0\ 0\ 0$ |
| $2$ | $2$ | $3$ | $10$ | $5$ | $0$ | $10\ 5\ 5\ 0\ 0\ 0\ 0\ 0\ 0\ 0$ |
| $3$ | $4$ | $5$ | $5$ | $2$ | $1$ | $10\ 5\ 5\ 3\ 2\ 0\ 0\ 0\ 0\ 0$ |
| $4$ | $6$ | $8$ | $10$ | $3$ | $1$ | $10\ 5\ 5\ 3\ 2\ 4\ 3\ 3\ 0\ 0$ |

```
输出
10 5 5 3 2 4 3 3 1 1 

PS：最后有两个-1改为了1
```

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int a[N],p[N],t,n,tmp,cnt;
struct node{//结构体
    int l,r,sum;    
}f[N];
void mem(){//初始化
    for(int i=1;i<=n;i++){
        f[i].l=f[i].r=f[i].sum=0;
        a[i]=p[i]=0;
    }
}
signed main(){
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        cnt=1;
        f[cnt].l=1;//提前将l设为1
        for(int i=1;i<=n;i++){
            scanf("%d",&p[i]);//输入p数组
            if(p[i]!=-1){//如果不等于-1
                f[cnt].r=i;//记录r
                f[cnt].sum=p[f[cnt].r]-p[f[cnt].l-1];
                cnt++;//记录sum，更新下标
                f[cnt].l=i+1;//记录下一组的l
            }
        }
        for(int i=1;i<cnt;i++){//循环结构体数组f
            int l=f[i].l,r=f[i].r,sum=f[i].sum;
            int shang,yu;
            shang=sum/(r-l+1);//计算shang
            for(int j=l;j<=r;j++)a[j]=shang;//修改
            if(sum%(r-l+1)>0){//如果yu大于0
                //之前这里被hack了
                yu=sum-shang*(r-l+1);//计算yu
                for(int j=l;j<l+yu;j++)a[j]++;//从l到l+yu-1让每个数加1
            }
        }   
        for(int i=1;i<=n;i++){
            if(a[i]==0)a[i]=1;//如果没修改就变成1
            printf("%d ",a[i]); 
        }
        printf("\n");   
        mem();
    }
    return 0;
}
```

---

## 作者：TheSky233 (赞：5)

$\tt{upd\ on\ 2022.4.18}$：因为[这组 hack 数据](https://www.luogu.com.cn/discuss/430918)修改了代码中一个问题。

## Description

给定一个含有 $-1$ 的序列 $p$，输出一个正整数序列 $a$，使得

$$\sum\limits^{i=1}_{i\leq k} a_i=
\begin{cases}
p_k& p_k \neq -1\\
x& p_k=-1
\end{cases}$$

其中 $x$ 是任意一个大于 $a_{i-1}$，使序列合法的值。

## Solution

### Subtask 1

用前缀和知识简单模拟即可。

### Subtask 2

不妨设 $pre_i$ 为已知 $a_{1 \cdots i}$ 的前缀和。

很容易想到一种思路，如果当前 $p_i$ 为 $-1$，就把当前 $a_i$ 填为 $1$，否则就把当前 $a_i$ 填为 $p_i-pre_{i-1}$。

[Code](https://www.luogu.com.cn/paste/huqaoqt6)。

### Subtask 3

观察到题目中对于 $a$ 数组的限制：$1 \leq a_i \leq 1000$，发现 Subtask 2 的做法大体思路正确，但是可能会出现某些 $a_i \geq 1000$ 的情况。

如以下数据

```cpp
1
4
1 -1 -1 3000
```

为了避免这种情况，可以把 $p_k-p_{i-1}$ 的差值平摊到 $a_i \cdots a_{k-1}$，这样就不会爆 $1000$ 的范围了。

- 注意点：如果 $p_i$ 到 $p_n$ 全是 $-1$，随便填什么都可以。 

## Code

```cpp
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#define int long long
using namespace std;

void read(int &x){
	x=0; int f=1; char ch=getchar();
	while(ch<'0' || ch>'9') f=(ch=='-')?-1:1,ch=getchar();
	while(ch>='0' && ch<='9') x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
	x=x*f;
}

void write(int x){
	if(x<0) putchar('-'),x=-x;
	char buf[64]; int cnt(0);
	do buf[++cnt]=x%10+48,x/=10; while(x);
	while(cnt) putchar(buf[cnt--]);
}

const int N=1e5+5;

int n,m,pre[N],a[N],b[N],T;

signed main(){
	read(T);
	while(T--){
		read(n);
		for(int i=1;i<=n;i++) read(pre[i]);
		fill(a+1,a+n+1,0);
		fill(b+1,b+n+1,0);
		for(int i=1;i<=n;i++){
			if(pre[i]==-1 && !a[i]){//是-1且没被填过
				int j=i;
				for(;pre[j]==-1 && j<=n;j++);//找连续的一段-1
				if(j>n){//p[i]到p[n]全是-1
					for(int k=i;k<j;k++){
						a[k]=1;
						b[k]=b[k-1]+1;
					}
				}
				else for(int k=i;k<j;k++){//按上文说的填
					a[k]=ceil((pre[j]-pre[i-1])*1.0/(j-i+1));//upd
					/*
						关于这里为什么要上取整的原因：
							如果有小数就要把小数部分也填了，因为这样序列还是会有解，还顺便减轻了 a[k+1] 的负担。 
						原代码可以被上文hack掉，就是因为 a[k+1] 填的超过了 1000。 
					*/
					b[k]=b[k-1]+a[k];
				}
			}
			else if(!a[i]){//普通情况
				a[i]=pre[i]-b[i-1];
				b[i]=pre[i];
			}
		}
		for(int i=1;i<=n;i++) write(a[i]),putchar(' '); puts("");
	}
	return 0;
}
```
时间复杂度：$O(n)$，因为每个 $a_i$ 只会被填一遍。

---

## 作者：alex_liu (赞：5)

[题目传送门](https://www.luogu.com.cn/problem/P8278)

[在此食用味道更佳](https://www.luogu.com.cn/blog/alex-liu/p8278-mcoi-08afill-in)
# 前置芝士：

**c++ 中的整除：**

设三个正整数分别为 $a$ ， $b$ ， $c$ ，且：

$$a=\frac{c}{b}$$

那么在 c++ 的运算中，会出现两种情况：

1. $a \times b \ne c$ （也就是 c 不能整除 a 或 b ）
2. $a \times b = c$ （也就是 c 能整除 a 或 b ）

那么在后面的程序中就会讲到怎么使用这两个性质

# 思路：

由于给出的是前缀和数组中的一部分，那么当前到上一个给出的前缀和的位置之间的数就可以求出来了。

首先先放查找从当前位开始给出的最近前缀和的位置的代码：

```cpp
inline int findid(int s){
	for(int i=s;i<=n;i++){
		if(p[i]!=-1)return i;// 找到给出的前缀和则返回当前位置
	}
	return -1;// 否则返回 -1
}
```

设 $q$ 为当前前缀和的位置， $lq$ 为上一个前缀和的位置， $gc$ 是两个前缀和之差

那么就可以分 5 种情况：

1.  $ lq=n $ （已经结束了）： 

	```cpp
	if(lq==n)break;
	```
    
    跳出循环

------------

2. $ lq<n $ 且 $ q=-1 $ （最后的全都是 -1）：

      ```cpp
      if(lq<n&&q==-1){
          for(int i=lq+1;i<=n;i++)cout<<1<<" ";
          break;
      }
      ```
      
      $lq+1$ 到 $n$ 之间的数全部输出 1
      
------------

3. $ gc=1 $ （两个前缀和之差为 1 ）：

    ```cpp
    if(gc==1){
        for(int i=lq+1;i<q;i++)cout<<0<<" ";
        cout<<1<<" ";
    }
    ```

	$lq+1$ 到 $q-1$ 之间的数输出 0 ， $q$ 的位置输出 1
    
------------

4. $ gc=0 $ （两个前缀和之差为 0 ）：

    ```cpp
    if(gc==0){
        for(int i=lq+1;i<=q;i++)cout<<0<<" ";
    }
    ```
	
    $lq+1$ 到 $q$ 之间的数输出 0
    
------------

5. 正常情况（每个值平均输出）：
    ```cpp
    int qq=gc/(q-lq);// 取平均值
    if(qq*(q-lq)!=gc){// 当不能整除时
        for(int i=lq+1;i<q;i++)cout<<qq<<" ";//先输出向下取整的平均值
        cout<<gc-(q-lq-1)*qq<<" ";//最后输出余下的值
    }else{//当能整除时
        for(int i=lq+1;i<=q;i++)cout<<qq<<" ";//直接输出平均值
    }
	```
------------

思考题：为什么正常情况下必须每个值平均输出，而不能前面的值输出 0 ，最后的直接输出 $gc$ 的值？（答案在文章的最后面）


AC 代码就不放注释了，自己理解更好
# CODE ：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
  	int x=0,f=1;
  	char c=getchar();
  	for(;c<'0'||c>'9';c=getchar())
    	if(c=='-')f=-1;
  	for(;c<='9'&&c>='0';c=getchar())
    	x=(x<<3)+(x<<1)+(c^48);
  	return (f==1?x:-x);
}
int t,n,p[100005],gc;
inline int findid(int s){
	for(int i=s;i<=n;i++){
		if(p[i]!=-1)return i;
	}
	return -1;
}
signed main(){
	t=read();
	p[0]=0;
	while(t--){
		n=read();
		for(int i=1;i<=n;i++)p[i]=read();
		int q=findid(1),lq=0;
		if(q==-1){
			for(int i=1;i<=n;i++)cout<<i<<" ";
			cout<<endl;
		}else{
			while(1){
				if(lq==n)break;
				if(lq<n&&q==-1){
					for(int i=lq+1;i<=n;i++)cout<<1<<" ";
					break;
				}
				gc=p[q]-p[lq]; 
				if(gc==1){
					for(int i=lq+1;i<q;i++)cout<<0<<" ";
					cout<<1<<" ";
				}else if(gc==0){
					for(int i=lq+1;i<=q;i++)cout<<0<<" ";
				}else{
					int qq=gc/(q-lq);
					if(qq*(q-lq)!=gc){
						for(int i=lq+1;i<q;i++)cout<<qq<<" ";
						cout<<gc-(q-lq-1)*qq<<" ";
					}else{
						for(int i=lq+1;i<=q;i++)cout<<qq<<" ";
					}
				}
				lq=q;
				q=findid(q+1);
			}
			cout<<endl;
		}
	}
	return 0;
}	
```

# 思考题答案：

由于题目中的数据范围有这么一句话：

满足 $1 \le a_i \le 1000$

所以如果不平均地输出的话，可能会超过这个限制（只有 50 分）

---

## 作者：GI录像机 (赞：4)

4.18 日更新：修改了代码，通过了该 [hack](https://www.luogu.com.cn/discuss/430918)，并增加相关阐述。

## 题意简述：

给出一个前缀和数组，求任一前缀和求的原数组。其中前缀和数组值为 $-1$ 的无需考虑。

## 思路：
这不简单，$-1$ 全部变成 $1$，然后有值的地方做减法就行了。

错了！题目要求 $1\le a_i\le 1000$！如果每一个 $a_i$ 都是 $1000$，按我们的构造方案就将会有 $1001\le a_i$ 的情况发生！

于是我们想到要使最大的 $a_i$ 最小。那怎么办呢？只需要把这一段前缀和的值均分给每一个 $a_i$ 就行了。特别地，注意把除了之后的余数加给一个数。

这就完了吗？不，并没有！如果我们最后一个数大于 $1000$ 呢？因此我们要向前传递值，让沿途的数尽可能地帮忙消耗掉更多的多余的值，因此若传递一次后仍超出 $1000$，则让其变为 $1000$ 以消耗更多的多余值，并继续向前传递。

~~实际上我在赛场上是没有想到要均分的，但看到了第一个样例，于是照着样例构造过了（~~

最后注意要特判一下结尾是 $-1$ 的情况。

## 参考代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define GICamera return 0;
long long read() {
	long long f = 1, x = 0;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-')f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0';
		c = getchar();
	}
	return f * x;
}
void write(long long x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x > 9)write(x / 10);
	putchar(x % 10 + '0');
}
const int N = 1e5 + 10;
long long p[N], ans[N], tot;
int main() {
	long long t = read();
	while (t--) {
		memset(ans, 0, sizeof(ans));
		tot = 0;
		long long n = read();
		long long cnt = 0, id = 0;//cnt 记录距离上一个有值的前缀和的个数，id 记录上一个有值的前缀和的位置
		for (int i = 1; i <= n; i++) {
			p[i] = read();
			if (p[i] == -1)cnt++;
			else {
				++cnt;
				long long num = (p[i] - p[id]) / cnt;
				for (int j = 1; j < cnt; j++) ans[++tot] = num;
				ans[++tot] = p[i] - p[id] - num * (cnt - 1); //把剩下的数给最后一个
				if (ans[tot] > 1000) {//如果最后一个比1000大就传给上一个数
					int gi = ans[tot] - 1000;
					ans[tot] = 1000;
					int j = tot;
					while (gi > 0) {//一直传直至答案合法
						ans[--j] += gi;
						gi = 0;
						if (ans[j] > 1000) {
							gi = ans[j] - 1000;
							ans[j] = 1000;
						}
					}
				}
				id = i;
				cnt = 0;
			}
		}
		if (cnt)for (int i = 1; i <= cnt; i++)ans[++tot] = 1;
		for (int i = 1; i <= n; i++) {
			write(ans[i]);
			putchar(' ');
		}
		putchar('\n');
	}
	GICamera
}
```


---

## 作者：渡墨残殇 (赞：3)

# 题意：

------------
给出一个前缀和数列，从数列中偷几个数变成 $-1$ ，求这个前缀和数列的原数列 $a$ 。

# 分析：

对于前缀数列不出现 $-1$ 的情况，直接**差分**即可。

```cpp
 a[i]=p[i]-p[i-1];
```
对于出现 $-1$ 的情况，我们标记一下 $-1$ 的下标 $v$ 然后继续输入下一个数，直到输出（正儿八经）的数或者输完了。

- **对于下一个数是非 $-1$ 的数**

我们求出下一个数 $x$ 和 $v$ 对应数的差值 $sum$ ，然后求出平均值，因为我们要保证数组 $a$ 的数是大于等于 $1$ 小于等于 $1000$ 的，因为有平均值不是恰好的时候，所以我们每次给数组 $a$ 赋值时都要是 $sum$ 减去一次平均值。

但是由于这样要满足最后一个点也要小于等于 $1000$ ，所以需要在最后一个点有个特判。
```cpp
 int sum=p[i]-p[v-1];
          int lll=sum/(i-v+1);
          for(int j=v;j<=i;j++)
          {
            if(j==i)
            {
            if(sum>1000)
			{ loj=sum-1000,a[i]=1000;//最后一个比1000多出来的一部分 
			while(loj)
			{for(int k=i-1;k>=v;k--)
			if(a[k]<1000)
			{
				int p=1000-a[k];
				if(p<loj)a[k]=1000,loj-=p;
				else {a[k]+=loj,loj=0;break;}
			}
			}
            }
			else a[i]=sum;	
            }
            else 
            a[j]=lll,sum-=lll;
          }
```

- **数组最后一个数是 $-1$ 的时候**

我们只需要保证数组 $a$ 是大于等于 $1$ 就行。
```cpp
while(p[i]==-1&&i<n)p[++i]=r;
        if(i==n&&p[n]==-1)
        {
         for(int i=v;i<=n;i++)a[i]=1; break;
        }
```

# 代码

```cpp
#include<bits/stdc++.h>
#define mm 200000
#define r read()
#define w qwrite
#define gc getchar()	
using namespace std;
int read(){//快读
	int x=0,y=1; char s=gc;if(s=='-')y=-1;
	while(!isdigit(s))s=gc;
	while(isdigit(s))x=(x<<1)+(x<<3)+s-'0',s=gc;
	return x*y;
} 
void qwrite(int x){//快写
    if(x==0){
		putchar('0');return ;}
	int cnt=0,u[400];
	if(x<0) putchar('-');
	while(x){u[cnt++]=x%10;x/=10;}
	while(cnt--) putchar(u[cnt]+'0');putchar(' ');
}
int p[mm],a[mm],b[mm];
int v,loj;
int  main ()
{
    int t, n;  t=r;
    while(t--)
    {
      n=r;
      for(int i=1;i<=n;i++)
        {
        p[i]=r;
        if(p[i]!=-1) a[i]=p[i]-p[i-1];
        else 
        {
        v=i;
        while(p[i]==-1&&i<n)p[++i]=r;
        if(i==n&&p[n]==-1) {
         for(int i=v;i<=n;i++)a[i]=1; break;
        }
          int sum=p[i]-p[v-1];
          int lll=sum/(i-v+1);
          for(int j=v;j<=i;j++)
          {
            if(j==i)
            {
            if(sum>1000)
			{ loj=sum-1000,a[i]=1000;//最后一个比1000多出来的一部分 
			while(loj)
			{for(int k=i-1;k>=v;k--)
			if(a[k]<1000)
			{
				int p=1000-a[k];
				if(p<loj)a[k]=1000,loj-=p;
				else {a[k]+=loj,loj=0;break;}
			}
			}
            }
			else a[i]=sum;	
            }
            else 
            a[j]=lll,sum-=lll;
          }
        }
      }
      for(int i=1;i<=n;i++)w(a[i]);
      puts("");
    }
    return 0;
}
```





---

## 作者：_lmh_ (赞：2)

### 题目大意
给定数组 $\{a_i\}$ 的前缀和数组 $\{p_i\}$，但其中部分数被替换成了 $-1$，求原数组。

### 解法
设 $p_i,p_j$ 均已知，且它们中间没有数已知（默认 $p_0=0$）。

首先可以求出，中间（即 $(i,j]$）共有 $j-i$ 个数，理论上可以将前面 $j-i-1$ 个数全部设为 $1$，最后一个数设为 $p_j-p_i-j+i+1$。

但是，出于某些原因，中间的 $j-i$ 个数必须均分，所以只能求出 $a=[\frac{p_j-p_i}{j-i}],b=p_j-p_i-a(j-i)$，再将前 $b$ 个数设为 $a+1$，后 $j-i-b$ 个数设为 $a$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,p,pre,cnt_1,T;
int main(){
    scanf("%lld",&T);
    while(T--){
        cnt_1=pre=0;
        scanf("%lld",&n);
        while(n--){
            scanf("%lld",&p);
            if (p==-1){
                cnt_1++;
            }
            else{
                int a,b;++cnt_1;
                a=(p-pre)/cnt_1;b=(p-pre)%cnt_1;
                for (int i=1;i<=b;i++) cout<<a+1<<' ';
                for (int i=b+1;i<=cnt_1;i++) cout<<a<<' ';pre=p;cnt_1=0;
            }
        }
        for (int i=1;i<cnt_1;i++) printf("1 ");if (cnt_1) printf("1");
        cout<<endl;
    }
    return 0;
}
```

---

## 作者：CarroT1212 (赞：1)

### 50pts Sol

显然 $a_i=p_i-p_{i-1}$。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
using namespace std;
int sz[100010];
int main() {
	int t,n;
	cin>>t;
	while (t--) {
		cin>>n;
		for (int a=1;a<=n;a++) cin>>sz[a];
		for (int a=1;a<=n;a++) cout<<sz[a]-sz[a-1]<<" ";
		cout<<endl;
	}
	return 0;
}
```

------------

### AC #1 #4 Sol

（注意此非完全正确的解法）

我们可以用构造合法数组的方法解决。

定义一个变量 $m=0$。如果 $p_i=-1$，则设 $a_i=1$，$m$ 加上 $1$；否则 $a_i=p_i-m$，$m=p_i$。

以样例 #1 的第一组数据为例：

$p_1=10$，输出 $p_1-m=10-0=10$，$m=10$；

$p_2=-1$，输出 $1$，$m=11$；

$p_3=20$，输出 $p_3-m=20-11=9$，$m=20$；

$p_4=-1$，输出 $1$，$m=21$；

$p_5=30$，输出 $p_5-m=30-21=9$，$m=30$。

最终结果为 `10 1 9 1 9`。

和样例不同，但也是对的。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
using namespace std;
int sz[100010],sum; //sum为上文m
int main() {
	int t,n;
	cin>>t;
	while (t--) {
		cin>>n;
		sum=0;
		for (int a=1;a<=n;a++) cin>>sz[a];
		for (int a=1;a<=n;a++) {
			if (sz[a]==-1) {
				cout<<1<<" ";
				sum++;
			}
			else {
				cout<<sz[a]-sum<<" ";
				sum=sz[a];
			}
		}
		cout<<endl;
	}
	return 0;
}
```

------------

### 100pts Sol

上面的方法看着似乎并没有什么问题，但是交上去就会[花红柳绿](https://www.luogu.com.cn/record/73649520)。为什么会错呢？

来，咱们仔细看题。

> 满足 $1 \le a_i \le 1000$。

也就是说，存在 $a_i>1000$ 时，答案不符合要求。

所以，以上一种方法为基础，我们要是遇到了这种情况，就得把 $a_i$ 超过 $1000$ 的部分分给 $a_{i-1}$，如果 $a_{i-1}>1000$ 的话继续分配。

为了更好地理解这个过程，我们再来看个例子。

以这组数据为例：

```plain
4
1 -1 -1 2593
```

$p_1=1$，$a_1=p_1-m=1-0=1$，$m=1$；（由于 $a_i$ 后面可能要进行修改，不能直接输出）

$p_2=-1$，$a_2=1$，$m=2$；

$p_3=-1$，$a_3=1$，$m=3$；

$p_4=2593$，$a_4=p_4-m=2593-3=2590$，$m=2593$。

此时对 $a_4$ 进行检验，发现 $a_4>1000$，于是将多出的部分分给 $a_3$，即 $a_3=a_3+(a_4-1000)=1+(2590-1000)=1591$，$a_4=1000$。

然后对 $a_3$ 进行检验，发现同样 $a_3>1000$，于是同样将多出的部分分给 $a_2$，即 $a_2=a_2+(a_3-1000)=1+(1591-1000)=592$，$a_3=1000$。

对 $a_2$ 进行检验，发现 $a_2$ 符合条件，退出检验环节。

最后得出结果 `1 592 1000 1000`。

由于题目保证有解，所以这个方法是一定可以得出合法结果的。

具体实现看代码。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
using namespace std;
int sz[100010],ans[100010],sum;
int main() {
	int t,n;
	cin>>t;
	while (t--) {
		cin>>n;
		sum=0;
		for (int a=1;a<=n;a++) cin>>sz[a];
		for (int a=1;a<=n;a++) {
			if (sz[a]==-1) {
				ans[a]=1;
				sum++;
			}
			else {
				ans[a]=sz[a]-sum;
				int tot=a;
				while (ans[tot]>1000) {
					ans[tot-1]+=ans[tot]-1000; //将超过 1000 的部分分给 a[i-1]
					ans[tot]=1000;
					tot--; //如果 a[i-1] 还是大于 1000 的话继续重复执行
				}
				sum=sz[a];
			}
		}
		for (int a=1;a<=n;a++) cout<<ans[a]<<" ";
		cout<<endl;
	}
	return 0;
}
```

------------

题外话：赛时这题搞得我快疯掉了，$10$ 分钟打出第一种解法，$20$ 分钟打出第二种，过了一个多小时才发现 $a_i>1000$ 的问题，做完水了 D 题 $1$ 分之后就不想打了……

---

## 作者：0000pnc (赞：0)

题意：给出一个序列的前缀和数组，其中有一些数不知道，让你构造出一个满足这个前缀和的正整数数组，且这个数组的 **每一项均小于等于** $1000$。  
为了方便，我们设原数组为 $\{a_{i}\}$，前缀和数组为 $\{b_{i}\}(1 \le i \le n)$。  
我们采取**边读入边输出**的方式。  
设 $\mathrm{i}$ 为当前读入的编号，$\mathrm{cur}$ 为小于 $\mathrm{i}$ 的最大的满足 $b_{i} \ne -1$ 的编号（初始值为 $0$），$\mathrm{now}$ 为已经输出的数的总和。   

下面是处理部分。  
* 如果读到 $b_{i}=-1$，那么啥事也不做。  
* 如果 $b_{i} \ne -1$，那么在 $[\mathrm{cur}+1, \mathrm{i}-1]$ 范围内的 $b_{j}$ 均为 $-1$。于是我们需要构造一个长度为 $(\mathrm{i}-\mathrm{cur})$ 的序列，使它们的和为 $b_{i}-\mathrm{now}$。由于我们需要满足 $a_{j}$ 的最大值尽量小，所以这些数要尽量平均。我们取 $a_{j}(\mathrm{cur}+1 \le j \lt i)=\left\lceil\dfrac{b_{i}-b_{cur}}{i-cur}\right\rceil$，每次输出都将 $\mathrm{now}$ 修改。最后我们使 $a_{i}=b_{i}-\mathrm{now}$ 即可。最后，将 $\mathrm{cur}$ 设为 $\mathrm{i}$。  

但是有个坑点。如果 $b_{i}(\mathrm{cur} \le i \le n)$ 均为 $-1$，那么我们这个程序不能输出最后 $n-\mathrm{cur}+1$ 个数。于是我们从 $\mathrm{cur}$ 到 $n$ 循环一遍，输出 $n-\mathrm{cur}+1$ 个 $1$ 即可。  

下面是代码。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define isdig(x) ((x) <= '9' && (x) >= '0')
int T, a, b, n, c[1000005] = {0};
#define rg register

int read() {
	rg int x = 0, f = 1;
	char ch = getchar();
	while (!isdig(ch)) {
		if (ch == '-') {
			f = -1;
		}
		ch = getchar();
	}
	while (isdig(ch)) {
		x = (x << 3) + (x << 1) + (ch ^ 48);
		ch = getchar();
	}
	return x * f;
}

void write(int x){
    if(x >= 10){
        write(x / 10);
    }
    putchar(x % 10 + '0');
}

int main(){
    T = read();
    while(T--){
        n = read();
        rg int now = 0, cur = 0;
        for(rg int i = 1; i <= n; i++){
            c[i] = read();
            if(c[i] != -1){
                for(rg int j = cur + 1; j < i; j++){
                    write((int)ceil((double)(c[i] - c[cur]) / (i - cur)));
                    putchar(' ');
                    now += (int)ceil((double)(c[i] - c[cur]) / (i - cur));
                }
                write(c[i] - now);
                putchar(' ');
                now = c[i];
                cur = i;
            }
        }
        for(rg int j = cur; j < n; j++){
            putchar('1');
            putchar(' ');
        }
        putchar('\n');
    }
}
```

---

