# 『JROI-4』Sunset

## 题目背景

写不出优美的文字，索性不放背景了。【背景待填充】

> 由于这只是个 C，出题人打算良心点，于是加了几个 $0$（指交互次数）（确信）——验题人注。

## 题目描述

**这是一道交互题。**

落日可以抽象成一个序列 $\{a_n\}$.

$\{a_n\}$ 是一个 $1\sim n$ 的排列。

你还有一个数列 $\{d_n\}$，为**当前** $a$ 数列的前缀最大值。

换言之，
$$d_i=\max_{j=1}^i \{a_j\}$$

注意：根据前文的定义，$\{d_n\}$ 可能随着 $\{a_n\}$ 数列的改变而改变。

您可以进行两种不同的操作：

- 指定一个 $i$，询问对于当前的 $a$ 数列， $d_{1\sim i}$ 中有几个不同的值。
- 指定一个 $i$，使得 $a_i\leftarrow 0$.

请使用不超过 $5500$ 次操作求出**原排列**。

**保证交互库是静态的，即交互库不会在交互过程中改变 $a$ 数列。**

## 说明/提示

**样例仅供理解交互过程，可能不符合逻辑。**

【样例解释】

初始的序列 $a$ 为 `1 2 3`，$d$ 为 `1 2 3`.

在对交互库输出了形如 `? 2 2` 的命令后，序列 $a$ 变为 `1 0 3`，$d$ 变为 `1 1 3`，此时 $d_1\sim d_3$ 中有 $2$ 种不同的值，分别是 $1,3$.



------------


可供选手参考的资料：[OI Wiki-交互题](https://oi-wiki.org/contest/interaction/) **|** [猜数（IO交互版）
](https://www.luogu.com.cn/problem/P1733)



------------

## 数据范围
- 对于 $10\%$ 的数据，$T=1$；
- 对于 $30\%$ 的数据，$n\le 70$；
- 对于另外 $20\%$ 的数据，保证数列 $a$ 随机生成；
- 对于全部数据：$T \leq 10,1\leq n\leq 500$。

## 样例 #1

### 输入

```
1

3

1

2

3


2

```

### 输出

```



? 1 1

? 1 2

? 1 3

? 2 2
? 1 3

! 1 2 3```

# 题解

## 作者：Abeeel51 (赞：9)

#### 题意
这是一道交互题

首先，在这里感谢出题人让我知道了怎么写交互题。

在 $5500$ 次询问内，你要求出最初的 $a$ 数组。

询问方式有三种：
- $\texttt{? 1 i}$ 询问 $d_{1 \sim i}$ 中有几个不同的值，交互库会返回一个正整数 $x$ 表示答案。

- $\texttt{? 2 i}$ 使 $a_i=0$。

- $\texttt{! a1 a2 a3 ... an}$ 输出答案。

返回的数值 $x$ 就是 $d_i = \max \limits_{j=1}^{i} \left \{a_j \right \}$
#### 题解
模拟？$30$ 分。

$a$ 数组中每一位往前的最大值就可能是：

$a_1,a_2,a_3,...,a_{i-1},n,n,n,n,n,n,n...$

画图发现，如果第 $i$ 位的值为当前数组中最大值，那么询问这个点往后的询问值一定与第 $i$ 位的询问值相符。那么最后一位的询问值一定与第 $i$ 位的询问值一样。现在就是要找到这个 $i$ 位，记录下来。

考虑二分。

在这个数组中二分查询这个 $i$ 位，首先询问一次 $n$ 位，如果第 $j$ 位和第 $n$ 位相同，那么查找 $j$ 往前的位置，不然查找 $j$ 往后的位置，最终查找到开头的位置，那么这位置一定是 $n$。标记后将 $a_i$ 清零，那么这个序列中的最大值就是 $n-1$，重复操作，直到确定 $1$ 的位置。


过程在图片里面。

![](https://cdn.luogu.com.cn/upload/image_hosting/ioi2orza.png)

清零之后求 $n-1 , n-2 , n-3 , ... , 1$ 以此类推。好了，这道题就解决了。
#### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int ans[50005];
int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        int n;
        scanf("%d",&n);
        for(int i=n;i>=1;i--){
            printf("? 1 %d\n\n",n);
            fflush(stdout);//刷新缓存
            int biao;
            scanf("%d",&biao);
            int l=1,r=n;
            while(l<r){
                int mid=(l+r)>>1;
                int tmp;
                printf("? 1 %d\n\n",mid);
                fflush(stdout);//刷新缓存
                scanf("%d",&tmp);
                if(tmp==biao) r=mid;
                else l=mid+1;
            }
            printf("? 2 %d\n\n",r);
            fflush(stdout);//刷新缓存
            ans[r]=i;
        }
        printf("!");
        for(int i=1;i<=n;i++) printf(" %d",ans[i]);
        puts("\n");
        fflush(stdout);//刷新缓存
    }
    return 0;
}
```


---

## 作者：D2T1 (赞：8)

# 题解 P8320 『JROI-4』Sunset

[link](https://www.luogu.com.cn/problem/P8320)

发现第二种操作“使 $a_i$ 为 $0$”，一旦操作了就不能再反悔，我们就永远失去了对这个数字原本的值的所有信息。因此这个操作的作用只有：在计算完这个数字的值后，**消除这个数字对其他数字的影响**，转而计算其他数字的值。

因此我们考虑每次计算出序列最大值，然后把该最大值变为 $0$，之前的次大值就变成了现在的最大值，计算 $n$ 次即可还原整个序列。

看到 $n$ 最大为 $500$，操作次数最大为 $5500$，所以每次计算最大值最多只有 $11$ 次机会，考虑一种 $\log n$ 做法：**二分**。

对于区间 $[1,n]$，进行一个拆分：$[1,mid],[mid+1,n]$。如何判断最大值在左边还是在右边呢？很简单：操作一查询 $d_{1\sim mid},d_{1\sim n}$ 中分别有几个不同的值。如果二值相同，则肯定后半段的所有值都没有左半段最大值大；如果二值不同，则右半段肯定有一个数更新了 $d$ 值，即比左半段所有数都大。

若是区间 $[l,r]$ 呢？也一样，查询 $d_{1\sim mid},d_{1\sim r}$ 进行比对即可。

可以使用记忆化减少一些查询次数。

```cpp
//C
//这是一道IO交互题
#include <bits/stdc++.h>
using namespace std;

const int N = 510;
vector<int> v;
int ans[N];

int ask(int x){
	if(x == 1) return 1;
	printf("? 1 %d\n", x);
	fflush(stdout);
	int t; scanf("%d", &t);
	return t;
}

int ra;
int getmx(int l, int r){
	if(l == r) return l;
	int mid = l + r >> 1;
	int t = ra, tt = ask(mid);
	if(t == tt){
		ra = tt;
		return getmx(l, mid);
	} else {
		ra = t;
		return getmx(mid+1, r);
	}
}

int main(){
	int t,n; scanf("%d", &t);
	while(t--){
		scanf("%d", &n);
		for(int i = n; i; -- i){
			ra = ask(n);
			int k = getmx(1, n);
			ans[k] = i;
			printf("? 2 %d\n", k);
			fflush(stdout);
		}
		printf("!");
		for(int i = 1; i <= n; ++ i) printf(" %d", ans[i]); puts("");
		fflush(stdout);
	}
	return 0;
} 
```

---

## 作者：TheSky233 (赞：5)

## Description

$\{a_n\}$ 是一个 $1\sim n$ 的排列。

你还有一个数列 $\{d_n\}$，为**当前** $a$ 数列的前缀最大值。

您可以进行两种不同的操作：

1. 指定一个 $i$，询问对于当前的 $a$ 数列， $d_{1\sim i}$ 中有几个不同的值。
2. 指定一个 $i$，使得 $a_i \leftarrow 0$。

请使用不超过 $5500$ 次操作求出原排列。

## Solution

思路：每次找到 $a_{1 \sim n}$ 中的最大值，把它变为 $0$，做 $n$ 次即可求得原序列。

对于最大值 $a_i$，有个显然的性质，它后面的 $d$ 都是一样的。  

具体地说，对于每一次 $\tt ask$，如果当前 $d_{i-1}<d_i$ 且 $d_i=d_{i+1}$ 那么它就是 $a_{1 \sim i}$ 中的最大值。也就是说，我们要找到 $d$ 数组最大值第一次出现的位置。

具体可以看这张图：

**第一轮**

![](https://cdn.luogu.com.cn/upload/image_hosting/fsycolvr.png)

相对应的 $\tt d$

![](https://cdn.luogu.com.cn/upload/image_hosting/ub80yyax.png)

发现 $d_4$ 符合上述条件，于是把 $a_4$ 认作整个数组的最大值 $5$，同时让交互库把 $a_4$ 变为 $0$。

**第二轮**

![](https://cdn.luogu.com.cn/upload/image_hosting/bteqmbnf.png)

相对应的 $\tt d$

![](https://cdn.luogu.com.cn/upload/image_hosting/aiguht52.png)

发现 $d_2$ 符合上述条件，于是把 $a_2$ 认作整个数组的次大值 $4$，同时让交互库把 $a_2$ 变为 $0$。

第三、四、五轮同理。

至此，本题得以解决。

### Section 1

外层循环从 $1$ 到 $n$ 模拟每一轮，内层从 $1$ 到 $n$ 进行每一次询问。

单组数据时间复杂度：$O(n^2)$。

单组数据交互次数：$n^2$。

期望得分：$30$

可以过 $30\%$ 的数据，还有 $70\%$ 超出了交互次数 $5500$。

### Section 2

外层循环不可避免，于是考虑如何优化内层循环。

看到这个神秘的数字 $5500$ 了吗？它好像和 $500 \times \left \lceil  \log_2 500\right \rceil $ 非常接近！

时间复杂度带 $\log_2$ 的查找算法，也只有二分查找了。

事实上，本题的 $d_i$ 满足单调不降，符合二分查找的必要条件。

于是内层循环就变为了二分查找一个 $d_i$，使得 $d_i$ 等于 $d_{i \sim n}$。

单组数据时间复杂度：$O(n \log_2 n)$。

单组数据交互次数：$n \log_2 n$。

期望得分：$100$

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

int T,n,mpos,x,now,kkk;
int a[5500];

int ask(int o){//模拟1操作
	int xx;
	cout<<"? 1 "<<o<<'\n';
	fflush(stdout);
	cin>>xx;
	return xx;
}

int main(){
	cin>>T;
	while(T--){
		cin>>n;
		now=n;
		for(int k=1;k<=n;k++){
			
			kkk=ask(n);//因为d数组单调不减，所以d[n]一定是最大的。
			
			int l=1,r=n;
			
			while(l<=r){//二分查找这个最大值第一次出现的位置
				int mid=(l+r)>>1;
				if(ask(mid)<kkk) l=mid+1;
				else r=mid-1,mpos=mid;
			}
			
			a[mpos]=now;//确定了a[mpos]的数值
			now--;
			cout<<"? 2 "<<mpos<<'\n';//2操作使这个最大数归零
			fflush(stdout);
		}
		cout<<"! "; fflush(stdout);//输出
		for(int i=1;i<=n;i++){
			cout<<a[i]<<' '; fflush(stdout); 
		}
		memset(a,0,sizeof(a));//用不用memset均可
	}
	return 0;
}
```

求个赞 $\tt qwq$。

---

## 作者：Fire_Raku (赞：3)

## 题目分析：

这是一道交互题（本人第一次做），一般都要从中找找规律，题目给了我们两种询问：    
1. 指定一个 $i$，询问 $d_{1∼i}$ 有几个不同的值。
2. 指定一个 $i$，把 $a_i$ 变为 $0$。

我们想用这两种询问确定 $a$ 序列中每个位置的值。

通过第一个询问，我们可以确定目前 $a$ 序列最大值的位置，举个例子：

```cpp
a序列：           2 1 4 5 3
d序列：           2 2 4 5 5
询问的每个i的结果：1 1 2 3 3
```
可以发现，$a$ 序列中最大数的位置，就是询问结果中最靠左边的最大值的下标，也就是下标 $4$，因为当 $a$ 序列的 $5$ 出现时，$d$ 序列后面的数都会是 $5$，询问结果当然也不会再改变，即为最大值，那么第一次出现询问结果最大值的位置就是 $a$ 序列最大数的位置。确定最大数位置的操作我们可以通过二分实现。

找到最大数的位置后，就把最大数赋值给答案序列的对应下标。如何找 $a$ 序列第二大的数的位置呢？我们不是还有第二种询问吗？我们将找出来的 $a$ 序列的最大数变为 $0$，第二大不就变成第一大了吗？之后就是和找第一大一样的操作了。

## Code：

```cpp
#include<bits/stdc++.h>
using namespace std ;
int ans[510] ; 
inline int read(){
	int x = 0 , f = 1 ;
	char ac = getchar() ;
	while(ac < '0' || ac > '9'){
		if(ac == '-') f = -1 ;
		ac = getchar() ;
	}
	while(ac >= '0'&& ac <= '9'){
		x = x * 10 + (ac - '0') ;
		ac = getchar() ;
	}
	return x * f ;
}
int main(){
	int t = read() ; 
	while(t--){
		int n = read() , d , cnt ; 
		cnt = n ; //第一大的数
		for(int i = 1 ; i <= n ; i++){ //一个一个找
			cout << "? 1 " << n << endl ; //询问 "询问结果" 的最大值
			fflush(stdout) ; 
			d = read() ; //记录下来
			int l = 1 , r = n , f , x ; 
			while(l <= r){ //二分模板
				int mid = (l + r) / 2 ; 
				cout << "? 1 " << mid << endl ; //每次二分，询问当前结果，直到找到最左边的最大值
				fflush(stdout) ; 
				x = read() ; 
				if(x < d) l = mid + 1 ; //如果小于最大值，指针左移
				else f = mid , r = mid - 1 ; //否则记录答案，指针右移
			}
			ans[f] = cnt ; //赋值给答案序列
			cnt-- ; //赋值的数减1，赋值下一次的第二大的数
			cout << "? 2 " << f << endl ; //删除掉目前的最大数 
			fflush(stdout) ; 
		}
		cout << "! " ;
		for(int i = 1 ; i <= n ; i++) cout << ans[i] << " " ; //输出答案序列
		cout << endl ; 
		fflush(stdout) ; 
	} 
	return 0 ; 
} 
```
###### ~~赏个赞呗 qwq~~

---

## 作者：JackMerryYoung (赞：3)

# 前言

无。

$\color{WHITE}\text{月赛 T3, 赛时由于不会交互没写。}$

# 正文

显然，由于 $d$ 数组记录了前缀最大值，所以它是单调不减的。

发现暴力求出最大值需要 $\mathcal{O}(N)$，总共约 $\mathcal{O}(N ^ 2)$, 一定会死，于是考虑二分。

又因为我们前面证明了单调性，所以只需普通的二分查找即可，复杂度 $\mathcal{O}(N\log_2N)$, 可以通过本题。

具体操作：

1. 求出 $\max{a_i}$.

2. 二分最大值位置 $pos$.

3. 赋给 $a_{pos}$ 为 $\max{a_i}$.

4. 将二分出来的最大值位置置为 $0$.

5. 回到 1. 直到求出所有数。

最后输出即可。

# 代码

~~你们最想要的..~~ 

Talk is$\color{white}\text{n't}$ cheap, $\color{white}\text{Don't}$ show me the code...

``` cpp
#include <bits/stdc++.h>
#define flush fflush(stdout)
using namespace std;

int N, T;
int arr[505];

int ask(int i)
{
	printf("? 1 %d\n", i);
	flush;
	int ans;
	scanf("%d", &ans);
	return ans;
}

int main()
{
	scanf("%d", &T);
	while(T --)
	{
		scanf("%d", &N);
		memset(arr, 0, sizeof(arr));
		for(int i = 1; i <= N; ++ i)
		{
			int maxd = ask(N);
			int l, r, ans;
			l = 1, r = N;
			while(l <= r)
			{
				int mid = (l + r) >> 1;
				if(ask(mid) < maxd) l = mid + 1;
				else r = mid - 1, ans = mid;
			}
			
			arr[ans] = N - i + 1;
			printf("? 2 %d\n", ans);
			flush;
		}
		
		printf("! ");
		flush;
		for(int i = 1; i <= N; ++ i)
		{
			printf("%d ", arr[i]);
			flush;
		}	
	}
	
	return 0;
}
```

---

## 作者：Cocoly1990 (赞：1)

官方题解。

设询问 $x$ 的结果是 $f_x$.

对于最小的 $i$ 满足 $f_i=f_n$ ，则 $a_i$ 是最大值。

知道上面这个结论之后可以 $n$ 次询问确定最大值，这启发我们
从大到小一一确定 $\{a_n\}$，进一步发现 $f$ 不降，对 $f$ 二分就好了。

写的很简单，想要代码的可以找我。

Subtask 设计给多测不清空，记忆化乱搞和暴力模拟的选手。

---

## 作者：lnwhl (赞：0)

一道交互题。
## Solution
令 $c_{i}$ 为 $d_{1∼n}$ 不同值的个数。

假设 $a_{i}$ 为序列的最大值，那么易知 $d_{i∼n}$ 全部相等，$c_{i∼n}$ 也全部相等，而 $c_{1∼i-1}$ 一定小于 $c_{i}$。因此，第一个与 $c_{n}$ 相等的 $c_{i}$ 的位置就是最大值所在地。

显然，$c$ 数组单调不降，所以只要在数列上二分即可。

找到最大之后就把其删除，再找次大值，以此类推，直到找到了所有值的位置。

询问次数 $n\log n$，可以在 $5500$ 次内解决本题。 
## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int T,n,pos[505];
int main()
{
	cin>>T;
	while(T--)
	{
		memset(pos,0,sizeof(pos));
		cin>>n;
		for(int i=n;i>=1;i--)
		{
			int l=1,r=n,mid,now,last;
			cout<<"? 1 "<<n<<endl;
			fflush(stdout);
			cin>>last;
			while(l<r)
			{
				mid=l+r>>1;
				cout<<"? 1 "<<mid<<endl;
				fflush(stdout);
				cin>>now;
				if(now==last)r=mid;
				else l=mid+1;
			}
			pos[l]=i;
			cout<<"? 2 "<<l<<endl;
			fflush(stdout);
		}
		cout<<"! ";
		for(int i=1;i<=n;i++)
			cout<<pos[i]<<" ";
		cout<<endl;
		fflush(stdout);
	}
	return 0;
}
```


---

## 作者：HPXXZYY (赞：0)

$\color{blue}{\texttt{[Analysis]}}$

设 $d_{1 \cdots i}$ 中不同的数的个数为 $\omega_{i}$。显然，$\omega_{1 \cdots n}$ 至少应该是**单调不下降**的。

显然，如果 $\omega_{i}=\omega_{j}(i<j)$，当且仅当：

$$\forall i<k\leq j,a_{k}<a_{i}$$

即

$$a_{i}>\max\limits_{k=i+1}^{j} \{ a_{k} \}$$

且 $\omega_{i} \not = \omega_{i-1}$ 当且仅当 $a_{i}>\max\limits_{j=1}^{i-1} \{ a_{j} \}$（想一想，为什么？）。

那么，如果 $\omega_{i}=\omega_{n}$ 且 $\omega_{i-1} \not = \omega_{n}$，则代表：

$$a_{i}>\max\limits_{j=1}^{i-1} \{ a_{j} \},a_{i}>\max\limits_{j=i+1}^{n} \{ a_{j} \}$$

换句人话说，就是 $a_{i}$ 是当前 $a_{1 \cdots n}$ 中的最大项。

于是我们找到了一个查询最大项 $n$ 位置的方法：不断地询问每一个位置 $i$，看看 $\omega_{i}$ 是否等于 $\omega_{n}$，如果等于，$a_{i}$ 就是最大值 $n$。

可以寻找最大值 $n$，这个问题就很好解决了：每次找到最大值后，把这一位修改为 $0$，此时，小于当前最大值的最大值（即原来的次大值）就变成了现在的最大值，重复上面的操作即可。

但是这样的暴力会超过询问次数。回到最开始，$\omega_{1 \cdots n}$ 至少是单调不下降的，所以我们二分。

总操作数 $\mathcal{O}(n \log n)$，可以承受。

$\color{blue}{\texttt{[Solution]}}$

1. 二分查找当前最大值所在的位置。
2. 记录最大值并把它修改为 $0$。
3. 重复操作 $(1)(2)$，直到所有位置的值已经确定。

$\color{blue}{\texttt{[code]}}$

```cpp
int a[550],n;

inline int getmax(){
	printf("? 1 %d\n",n);
	fflush(stdout);
	int g;scanf("%d",&g);
	
	int l=1,r=n,mid,ans,tmp;
	while (l<=r){
		mid=(l+r)>>1;
		printf("? 1 %d\n",mid);
		fflush(stdout);
		scanf("%d",&tmp);
		
		if (tmp==g){
			ans=mid;
			r=mid-1;
		}
		else l=mid+1;
	}
	
	return ans;
}

int main(){
	int Q;scanf("%d",&Q);
	
	while (Q--){
		scanf("%d",&n);
		memset(a,0,sizeof(a));
		
		for(int i=n;i>1;i--){
			int k=getmax();
			a[k]=i;
			printf("? 2 %d\n",k);
			fflush(stdout);
		}
		
		for(int i=1;i<=n;i++)
			if (a[i]==0) a[i]=1;
		
		printf("!");
		for(int i=1;i<=n;i++)
			printf(" %d",a[i]);
		printf("\n");
		fflush(stdout);
	}
	
	return 0;
}
```

---

## 作者：Polaris_Australis_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P8320)

## 题意

交互题，有一个长度为 $n$ 的排列 { $a_i$ }，和一个数组 { $d_i$ } 表示以及三种交互操作：

- `? 1 i` 询问 $d_{1\sim i}$ 中有几个不同的值，交互库会返回一个正整数 $x$ 表示答案。
- `? 2 i` $a_i\gets 0$。
- `! a1 a2 a3 … an` 输出答案。

$n\le 500$ ，要求在 $5500$ 步内输出答案。

## 做法

这是一道非常良心的月赛 T3 。

根据题意，先说两个性质：

1. { $d_i$ } 数组单调递增，因为：
$$
d_i=
\left\{\begin{array}{l}
d_{i-1}+1\texttt{ }\texttt{ }(a_i>\max_{p\in [1,i)}(a_p))\\
d_{i-1}\texttt{ }\texttt{ }(\text{otherwise})
\end{array}\right.
$$
2. 假设当前数组 { $a_i$ } 中最大的数是 $a_p$，则 $\forall i\in [p,n]\text{，}d_i=d_p$，且 $\forall i\in [1,p)\text{，}d_i<d_p$，因为后面所有前缀最大和都是 $a_i$，前面所有前缀最大和都小于 $a_i$。

由于具有单调性，所以直接二分查找，找到最小的 $i$，使得 $d_i=d_n$，$a_i$ 就是当前数组最大值，每次把最大值清零后再找最大值，直到所有值都找到，然后输出答案即可。

## 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
#ifndef ll
#define int long long
#endif
#define db double
using namespace std;
namespace Std
{
    template<typename tp>
    void read(tp &x)
    {
        x=0;
        tp nev=1;
        char c=getchar();
        while(c<'0'||c>'9')
        {
            if(c=='-')nev=-1;
            c=getchar();
        }
        while(c>='0'&&c<='9')
        {
            x=(x<<1)+(x<<3)+(c^48);
            c=getchar();
        }
        x*=nev;
    }
    template<typename tp>
    void write(tp x)
    {
        if(x<0)
        {
            putchar('-');
            write(-x);
            return;
        }
        if(x/10)write(x/10);
        putchar((x%10)^48);
    }
    int n,a[505],t;
    int main()
    {
        read(t);
        while(t--)
        {
            read(n);
            for(int i=n;i;--i)
            {
                printf("? 1 %d\n",n);
                cout<<flush;
                int aim;
                read(aim);
                int l=1,r=n;
                while(l<r)
                {
                    int mid=l+r>>1;
                    printf("? 1 %d\n",mid);
                    cout<<flush;
                    int tot;
                    read(tot);
                    if(tot==aim)
                    {
                        r=mid;
                    }
                    else l=mid+1;
                }
                a[l]=i;
                printf("? 2 %d\n",l);
                cout<<flush;
            }
            printf("! ");
            cout<<flush;
            for(int i=1;i<=n;++i)
            {
                printf("%d ",a[i]);
                cout<<flush;
            }
            puts("");
            cout<<flush;
        }
        return 0;
    }
}
#ifdef int
#undef int
#endif
int main()
{
    return Std::main();
}
```


---

## 作者：GI录像机 (赞：0)

## 思路简述：

我们把 $d_{1\sim i}$ 中不同值的个数定义为 $c_i$。

假设 $a_i$ 是整个数组的最大值，那么可知，$d_{i\sim n}$ 全部相等，因此 $c_{i\sim n}$ 也全部相等。因为 $d_n$ 的值一定是最大值，至此，我们就可以通过暴力枚举的方式，从末端往前查找最后一个 $j$ 使得 $c_j=c_n$，这就是当前的最大值。接着再把最大值赋值为 $0$，次大值就成了最大值，重复以上步骤直至数全部为 $0$。

我们轻易可以发现，暴力枚举的过程实际上满足二分条件。答案的左边均不满足 $c_j=c_n$，右边均满足。因而可以用二分优化。

## 参考代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int read() {
	int f = 1, x = 0;
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
void write(int x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x > 9)write(x / 10);
	putchar(x % 10 + '0');
}
int t = read();
signed main() {
	while (t--) {
		int n = read(), a[510];
		memset(a, 0, sizeof(a));
		for (int i = n; i >= 1; i--) {
			int l = 1, r = n, ans, ch;
			putchar('?');
			putchar(' ');
			putchar('1');
			putchar(' ');
			write(n);
			cout<<std::endl;
			ch = read();
			while (l <= r) {
				int mid = (l + r) >> 1, tmp;
				putchar('?');
				putchar(' ');
				putchar('1');
				putchar(' ');
				write(mid);
				cout<<std::endl;
				tmp = read();
				if (tmp == ch) {
					ans = mid;
					r = mid - 1;
				} else l = mid + 1;
			}
			a[ans] = i;
			putchar('?');
			putchar(' ');
			putchar('2');
			putchar(' ');
			write(ans);
			cout<<std::endl;
		}
		putchar('!');
		putchar(' ');
		for (int i = 1; i <= n; i++) {
			write(a[i]);
			putchar(' ');
		}
		cout<<std::endl;
	}

	return 0;
}
```


---

## 作者：Mars_Dingdang (赞：0)

本题是一道有趣的交互题。

## 题目大意
有一个 $1\sim n(n\le 500)$ 的排列 $a_i$ 未知。设 $d_i=\max_{k=1}^i \{a_k\}$ 表示排列 $a$ 的前缀最大值，有以下两种交互方式：

1. `? 1 i` 表示询问 $d_1\sim d_i$ 中有多少不同的值，即集合 $\{d_1\sim d_i\}$ 的大小；
2. `? 2 pos` 表示将 $a_{pos}\leftarrow 0$。

有 $T$ 组测试数据，每组数据中，你需要在不多于 $5500$ 次交互的条件下还原出原排列 $a_i$。

## 大体思路
很容易发现，前缀最大值 $d$ 数组具有单调不减的性质，其图像大致如下图所示：
![](https://cdn.luogu.com.cn/upload/image_hosting/ob9ztzsq.png)


由于 $d_x\sim d_n$ 的值均相同，证明 $x$ 位置上的数就是 $n$，否则 $d$ 会在 $a_p=n$ 的位置增大。

同时，我们可以发现，$d$ 数组前 $i$ 项不同值的个数和 $d$ 本身的图像趋势是相近的，同样是单调不减的。所以，我们可以二分得到位置 $x$，使得 $x$ 是最大的满足 $\left\vert\{d_1\sim d_x\}\right\vert=\left\vert\{d_1\sim d_n\}\right\vert$ 的位置。

这样，我们得到了 $a_x=n$。然后我们利用操作 $2$ 将 $a_x\leftarrow 0$，重复以上操作求出 $n-1\sim 1$ 的位置即可。

这样每求一个值的位置，进行的交互次数是 $\Theta(\log n)$，总的交互次数为 $\Theta(n\log n)$，当 $n=500$ 时次数约为 $4500$ 次，大体上足以满足要求。

需要注意的是，交互题输出后需要 `fflush(stdout);` 清空缓存，并且提交函数型交互题不能使用 `inline` 式函数。

## 完整代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define rep(ii,aa,bb) for(re int ii = aa; ii <= bb; ii++)
#define Rep(ii,aa,bb) for(re int ii = aa; ii >= bb; ii--)
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef pair<int, int> PII;
const int maxn = 505;
namespace IO_ReadWrite {
	#define re register
	#define gg (p1 == p2 && (p2 = (p1 = _buf) + fread(_buf, 1, 1<<21, stdin), p1 == p2) ? EOF :*p1++)
	char _buf[1<<21], *p1 = _buf, *p2 = _buf;
	template <typename T>
	inline void read(T &x){
		x = 0; re T f=1; re char c = gg;
		while(c > 57 || c < 48){if(c == '-') f = -1;c = gg;}
		while(c >= 48 &&c <= 57){x = (x<<1) + (x<<3) + (c^48);c = gg;}
		x *= f;return;
	}
	inline void ReadChar(char &c){
		c = gg;
		while(!isalpha(c)) c = gg;
	}
	template <typename T>
	inline void write(T x){
		if(x < 0) putchar('-'), x = -x;
		if(x > 9) write(x/10);
		putchar('0' + x % 10);
	}
	template <typename T>
	inline void writeln(T x){write(x); putchar('\n');}
}
using namespace IO_ReadWrite;
int T, n, a[maxn];
int main () {
	scanf("%d", &T);
	while(T --) {
		memset(a, 0, sizeof a);
		scanf("%d", &n);
		Rep(x, n, 1) {
			printf("? 1 %d\n", n);
			fflush(stdout);
			int mx;
			scanf("%d", &mx);
			int L = 1, R = n, pos = n;
			while(L <= R) {//二分
				int mid = (L + R) >> 1;
				printf("? 1 %d\n", mid);
				fflush(stdout);
				int num;
				scanf("%d", &num);
				if(num >= mx) pos = mid, R = mid - 1;
				else L = mid + 1;
			}
			a[pos] = x;
			printf("? 2 %d\n", pos);
			fflush(stdout);
		}
		printf("!");//输出序列
		rep(i, 1, n) printf(" %d", a[i]);
		printf("\n");
		fflush(stdout);
	}
	
	return 0;
}
```

---

