# Vus the Cossack and Numbers

## 题目描述

Vus the Cossack has $ n $ real numbers $ a_i $ . It is known that the sum of all numbers is equal to $ 0 $ . He wants to choose a sequence $ b $ the size of which is $ n $ such that the sum of all numbers is $ 0 $ and each $ b_i $ is either $ \lfloor a_i \rfloor $ or $ \lceil a_i \rceil $ . In other words, $ b_i $ equals $ a_i $ rounded up or down. It is not necessary to round to the nearest integer.

For example, if $ a = [4.58413, 1.22491, -2.10517, -3.70387] $ , then $ b $ can be equal, for example, to $ [4, 2, -2, -4] $ .

Note that if $ a_i $ is an integer, then there is no difference between $ \lfloor a_i \rfloor $ and $ \lceil a_i \rceil $ , $ b_i $ will always be equal to $ a_i $ .

Help Vus the Cossack find such sequence!

## 说明/提示

The first example is explained in the legend.

In the second example, we can round the first and fifth numbers up, and the second and third numbers down. We can round the fourth number neither up, nor down.

## 样例 #1

### 输入

```
4
4.58413
1.22491
-2.10517
-3.70387
```

### 输出

```
4
2
-2
-4
```

## 样例 #2

### 输入

```
5
-6.32509
3.30066
-0.93878
2.00000
1.96321
```

### 输出

```
-6
3
-1
2
2
```

# 题解

## 作者：灵茶山艾府 (赞：3)

提供一个简洁的证明方法：

由于

$$
\sum\lfloor a_i\rfloor\le\sum a_i=0
$$

$$
\sum\lceil a_i\rceil\ge\sum a_i=0
$$

我们从 $\sum\lfloor a_i\rfloor$ 出发，不断地给其中 $a_i$ 不为整数的 $\lfloor a_i\rfloor$ 加一，将其变为 $\lceil a_i\rceil$，由于整数的连续性，从 $\sum\lfloor a_i\rfloor$ 到 $\sum\lceil a_i\rceil$ 中必然在某一时刻会达到 $0$（类比介值定理），此时我们就得到了 $b_i$ 序列。

AC 代码（Golang）：

```go
package main
import("bufio";."fmt";."math";"os")

func main() {
    in := bufio.NewReader(os.Stdin)
    out := bufio.NewWriter(os.Stdout)
    defer out.Flush()

    n, s := 0, 0.
    Fscan(in, &n)
    a := make([]float64, n)
    for i := range a {
        Fscan(in, &a[i])
        s += Floor(a[i])
    }

    for _, v := range a {
        f := Floor(v)
        if s < 0 && v != f {
            s++
            Fprintln(out, f+1)
        } else {
            Fprintln(out, f)
        }
    }
}
```


---

## 作者：Meatherm (赞：3)

~~CF571轮（div.2） D题。作为一个div.2 D题不得不说是非常水的。然而我还傻傻地被罚了200分。~~

## 题意

给出$n$个实数，它们的和为$0$。将每个实数上取整或者下取整后输出。要求输出的所有整数和为$0$。如有多个解输出任意一个。

## 思路

设$a[]$为读入的数组，$b[]$为$a[]$中实数向下取整的值，即$b[i]=\left\lfloor a[i] \right\rfloor$。设$sum=\sum_{i=1}^{n} b[i]$。由于$\sum_{i=1}^{n} a[i] = 0$，则$sum≤0$。（都下取整还能比$0$大？）

由于要求的和为$0$，则$0-sum$为需要上取整的个数。再到数列中选取$0-sum$个数进行上取整即可。

### 坑点

1.如果$b[i]$为整数，那么无论上取整还是下取整都是$b[i]$。

2.负实数的下取整是整数部分$-1$，而正实数的下取整就是整数部分。~~（被罚$200$分原因）~~

```
# include <bits/stdc++.h>
# define rr register
using std::string;
using std::cin;
using std::cout;
using std::endl;
const int N=100010;
string a[N];//采用了字符串处理
bool can[N];//能不能上取整（即：是不是整数）
long long Floor[N];//下取整的值
long long n;
int main(void){
	std::ios::sync_with_stdio(false);	
	cin.tie(0);
	cout.tie(0);//I/O加速
	cin>>n;
	for(rr int i=1;i<=n;++i)
		cin>>a[i];
	for(rr int i=1;i<=n;++i){
		int tmp=a[i].find("."),len=a[i].size();
		if(a[i][0]=='-'){//特判负数的情况
			for(rr int j=1;j<tmp;++j)
				Floor[i]=Floor[i]*10+a[i][j]-48;
			Floor[i]=-Floor[i];		
		}
		else{
			for(rr int j=0;j<tmp;++j)
				Floor[i]=Floor[i]*10+a[i][j]-48;
		}
		for(rr int j=tmp+1;j<len;++j)
			if(a[i][j]!='0'){
				can[i]=true;
				break;
			}
		if(can[i]&&a[i][0]=='-')
			--Floor[i];	//如果是负数并且不是整数 那么要-1才是它的下取整
	}
	long long sum=0;
	for(rr int i=1;i<=n;++i)
		sum+=Floor[i];
	long long need=0-sum;
	for(rr int i=1;i<=n;++i){
		if(!need||!can[i]){//已经选取够了0-sum个数来上取整或者这个数不可用
			cout<<Floor[i]<<endl;
		}
		else{
			--need,cout<<Floor[i]+1<<endl;//否则进行上取整操作
		}
	}	
	return 0;
}
```

---

## 作者：BYWYR (赞：1)

## $\texttt{Solution}$

考虑先将 $a_i$ 向下取整。

$$\because \sum{a_i}=0$$

$$\therefore \sum{\left\lfloor{a_i}\right\rfloor} \leq 0 $$

因此，$\left|0-\sum{\left\lfloor{a_i}\right\rfloor}\right|$
即为需要向上取整的个数。

可以证明此时 $\sum{a_i}=0$。

**注意**：一个整数向上或向下取整还是它本身，所以在把向下取整数变为向上取整数时，遇到整数要跳过。

## $\texttt{Code}$

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,ans[100005],sum_floor;
double a[100005];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		sum_floor+=floor(a[i]);//向下取整数的和
		ans[i]=floor(a[i]);
	}
	ll num_ceil=0-sum_floor;//需要向上取整的个数
	for(int i=1;i<=n;i++){//向下取整数变为向上取整数
		if(num_ceil==0) break;
		if(ceil(a[i])==a[i]||floor(a[i])==a[i]) continue;//当前数为整数情况
		else ans[i]=ceil(a[i]),num_ceil--;
	}
	for(int i=1;i<=n;i++)
		cout<<ans[i]<<' ';	
	return 0;
}
```


---

## 作者：hanyipu1414 (赞：1)

# 一、题意

- 给出一个长度为 $n$ 的实数序列 $a$ ，和为 $0$ 。
- 构造一个长度为 $n$ 的整数序列 $b$ ，使 $b_i=floor(a_i)$ 或 $ceil(a_i)$ ，且整数序列 $b$ 所有项的和为 $0$。

# 二、思路

1. 这道题暴力显然不行，毕竟 $1≤n≤10^5$ 。

2. 由于每个数都有向下取整与向上取整两种情况，所以我们可以考虑将每个数都向下取整，再进行调整。

3. 让我们手模一遍样例吧。

- ##### 样例

```
    a1 = 4.58413
    a2 = 1.22491
    a3 = -2.10517
    a4 = -3.70387
```

- ##### 将小数向下取整（整数无论向上取整还是向下取整都为本身，需特判，不进行向下取整和之后调整的操作）

```
    b1 = 4
    b2 = 1
    b3 = -3
    b4 = -4
```

此时通过求和可以发现，这四个数的和为 $-2$ 。我们需要将 $-(-2)$ 个数加 $1$ ，也就是将 $2$ 个数改为 $ceil(a_i)$ 。

- ##### 调整完成后
```
    b1 = ceil(a1) = 5
    b2 = ceil(a2) = 2
    b3 = -3
    b4 = -4
```


# 三、code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NR=1e5+10;
double a[NR];int n,sum;//sum用来记录都向下取整后的总和 
struct Node
{
	int x;bool d;
}b[NR];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		b[i].x=floor(a[i]);
		if(a[i]-double(b[i].x)==0) b[i].d=1;//小判断，将为整数的标记，不参与调整 
		sum+=b[i].x;
	}
	for(int i=1;i<=-sum;i++)//sum必为非整数，因为每个数都进行了向下取整的操作 
	{
		if(b[i].d)//整数，不参与调整 
		{
			cout<<b[i].x<<"\n";
			sum-=1;//将循环后移一位，因为跳过了一个数 
			continue;
		}
		cout<<b[i].x+1<<"\n";//循环了-sum次，将向下取整所失去的值加回来，将和再次调整为0 
	}
	for(int i=-sum+1;i<=n;i++) cout<<b[i].x<<"\n";//将剩下部分输出就可以了 
	return 0;//完事 
}
```


---

## 作者：brealid (赞：1)

首先算出 $\sum\lfloor a_i \rfloor$，然后$\sum\lfloor a_i \rfloor$的相反数就是需要向上取整的数的个数。

### 宏定义说明

1. isInt(a) 判断 a 是不是整数

### 函数说明：

1. read, write(2个) ` ` 快读可忽视  
2. low(f) ` ` 返回 f 向下取整的结果    
3. mor(f) ` ` 返回 f 向下取整的结果   

### 变量说明

1. n(int), a(double array) ` ` 见题目  
2. lSum ` ` 所有数向下取整的和，即 $\sum\lfloor a_i \rfloor$  
3. toAdd ` ` 是 lSum 的相反数，且在最后输出时不断变化

具体代码实现不是太难，这也是一道比较水的 CF-div.2-D题

丢代码

```cpp
#include <bits/stdc++.h>
using namespace std;

template <typename Int>
inline Int read()       
{
    Int flag = 1;
    char c = getchar();
    while ((!isdigit(c)) && c != '-') c = getchar();
    if (c == '-') flag = -1, c = getchar();
    Int init = c & 15;
    while (isdigit(c = getchar())) init = (init << 3) + (init << 1) + (c & 15);
	return init * flag;
}

template <typename Int>
inline void write(Int x)
{
    if (x < 0) putchar('-'), x = ~x + 1;
    if (x > 9) write(x / 10);
    putchar((x % 10) | 48);
}  

template <typename Int>
inline void write(Int x, char nextch)
{
    write(x);
    putchar(nextch);
}  

#define isInt(a) ((a) == (int)(a))

int low(double f)
{
    int ret = f;
    return f < 0 ? ret - !isInt(f) : ret;
}

int mor(double f)
{
    int l = low(f);
    return l + !isInt(f);
}

int n;
double a[100007];
int lSum;

int main()
{
    n = read<int>();
    for (int i = 1; i <= n; i++) {
        scanf("%lf", a + i);
        lSum += low(a[i]);
    }
    int toAdd = -lSum;
    for (int i = 1; i <= n; i++) {
        if (!toAdd) write(low(a[i]), 10);
        else write(mor(a[i]), 10), toAdd -= !isInt(a[i]);
    }
    return 0;
}
```

---

## 作者：czh___ (赞：0)

### 题意：
给一堆和为 $0$ 有正负的小数，让把小数在绝对值为 $1$ 以内取整，取整后和还是 $0$，要求输出取整后的数。

### 思路：
最主要的思想就是先取整，比如先都向下取整，然后把所有的舍掉的小数都加起来为 $sum$，而 $sum$ 一定是整数，然后就看 $sum$ 是正的还是负的，多退少补，而且要满足多退少补后绝对值还是小于 $1$ 就行了。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
double a[maxn];
int b[maxn];
int main(){
	int N;
	while(cin>>N){
		double tot=0;
		for(int i=1;i<=N;i++){
			cin>>a[i];
			b[i]=a[i];
			tot+=a[i]-b[i];
		}
		int tt=round(tot);
		if(tt>0){
			for(int i=1;i<=N;i++){
				if(tt==0)break;
				if(a[i]>b[i])b[i]++,tt--;
			}
		}
		else if(tt<0){
			for(int i=1;i<=N;i++){
				if(tt==0)break;
				if(a[i]<b[i])b[i]--,tt++;
			}
		}
		for(int i=1;i<=N;i++)cout<<b[i]<<endl;
	}
	return 0;
}
```

[改编于](https://blog.csdn.net/SwustLpf/article/details/94150892?ops_request_misc=&request_id=&biz_id=102&utm_term=Vus%20the%20Cossack%20and%20Numbers&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-5-94150892.142^v101^pc_search_result_base7&spm=1018.2226.3001.4187)

---

## 作者：qiuzijin2026 (赞：0)

# Vus the Cossack and Numbers

## [题面](https://www.luogu.com.cn/problem/CF1186D)

## 思路

我们先让每个数都向下取整，计算他们的和与 $0$ 的差的绝对值，我们就让差的绝对值那么多个数向上取整即可。

注意遇到整数要跳过，因为 $\lceil x \rceil = \lfloor x \rfloor=x$，所以向下取整与向上取整没区别，要跳过。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
double a[100005];
int b[100005];
int s;
int cnt;
int l;
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%lf",&a[i]);	
		b[i]=floor(a[i]);
		s+=b[i];
	} 
	cnt=abs(0-s);
	for(int i=1;i<=cnt;i++){
		l++;
		while(a[l]==floor(a[l])) l++;
		b[l]=ceil(a[l]);
	}
	for(int i=1;i<=n;i++) printf("%d\n",b[i]);
	return 0;
}

```

---

## 作者：happybob (赞：0)

先令 $b_i = \lfloor a_i \rfloor$。

由于 $\sum a_i = 0$ 且 $\lfloor x \rfloor \leq x$，所以有 $\sum b_i \leq 0$。

可以发现将一个非整数 $a_i$ 从 $\lfloor a_i \rfloor$ 变成 $\lceil a_i\rceil$ 会使得总和增加 $1$。所以可以将 $0 - \sum b_i$ 个非整数 $a_i$ 从 $\lfloor a_i \rfloor$ 变成 $\lceil a_i\rceil$。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;

const int N = 1e5 + 5;

int n;
double a[N];
bool v[N];

int main()
{
	scanf("%d", &n);
	long long sum = 0;
	for (int i = 1; i <= n; i++)
	{
		scanf("%lf", &a[i]);
		v[i] = ((int)a[i]) == a[i];
		a[i] = floor(a[i]);
		sum += a[i];
	}
    long long need = 0 - sum;
	for (int i = 1; i <= n; i++)
	{
		if (v[i] || need == 0)
		{
			printf("%.0f\n", a[i]);
			continue;
		}
		printf("%.0f\n", a[i] + 1);
		need--;
	}
	return 0;
}
```


---

