# Balanced Rating Changes

## 题目描述

Another Codeforces Round has just finished! It has gathered $ n $ participants, and according to the results, the expected rating change of participant $ i $ is $ a_i $ . These rating changes are perfectly balanced — their sum is equal to $ 0 $ .

Unfortunately, due to minor technical glitches, the round is declared semi-rated. It means that all rating changes must be divided by two.

There are two conditions though:

- For each participant $ i $ , their modified rating change $ b_i $ must be integer, and as close to $ \frac{a_i}{2} $ as possible. It means that either $ b_i = \lfloor \frac{a_i}{2} \rfloor $ or $ b_i = \lceil \frac{a_i}{2} \rceil $ . In particular, if $ a_i $ is even, $ b_i = \frac{a_i}{2} $ . Here $ \lfloor x \rfloor $ denotes rounding down to the largest integer not greater than $ x $ , and $ \lceil x \rceil $ denotes rounding up to the smallest integer not smaller than $ x $ .
- The modified rating changes must be perfectly balanced — their sum must be equal to $ 0 $ .

Can you help with that?

## 说明/提示

In the first example, $ b_1 = 5 $ , $ b_2 = -3 $ and $ b_3 = -2 $ is another correct solution.

In the second example there are $ 6 $ possible solutions, one of them is shown in the example output.

## 样例 #1

### 输入

```
3
10
-5
-5
```

### 输出

```
5
-2
-3
```

## 样例 #2

### 输入

```
7
-7
-29
0
3
24
-29
38
```

### 输出

```
-3
-15
0
2
12
-15
19
```

# 题解

## 作者：fengqiao17 (赞：3)

## Solution
数据保证一定有解，我们不妨进行如下操作:

若 $a_{i}$ 是偶数：$b_{i}=\frac{a_{i}}{2}$；

若 $a_{i}$ 是奇数：若上一个奇数向上取整，则 $b_i=\left\lfloor\dfrac{a_i}{2}\right\rfloor$；若上一个奇数向下取整，则 $b_i=\left\lceil\dfrac{a_i}{2}\right\rceil$。

## Code
```cpp
//author:fengqiao17
//转载请标明地址：https://616673.blog.luogu.org/solution-cf1237a
#include <bits/stdc++.h>
using namespace std;
int main() {
  int n;
  scanf("%d", &n);
  int flag = 1;      //flag记录上一个是向上取整或向下取整
  for (int i = 1; i <= n; i++) {
    int x;
    scanf("%d", &x);
    if (x % 2 == 1) { //是奇数
      printf("%d\n", (x + flag) / 2);
      flag *= -1;     //把标记反过来
    } else {          //是偶数
      printf("%d\n", x / 2);
    }
  }
  return 0;
}
```

---

## 作者：Mubuky (赞：3)

**The round will be perfectly balanced. As all things should be.**

~~_%%% tourist_~~

**题目大意:**

现在给你一个n和n个整数$a_{i}$

若$b_{i}$为偶数，**$b_{i}$ = $\frac{a_{i}}{2}$**

否则, **$b_{i}$ = ⌊$\frac{a_{i}}{2}$⌋ 或者 $b_{i}$ = ⌈$\frac{a_{i}}{2}$⌉**

最终得到的所有$b_{i}$之和应该为0.

输出所有的$b_{i}$

### **思路1:**

1.取 $b_{i}$ = \[$\frac{a_{i}}{2}$] . //向零取整

2.sum = $\sum\limits_{i=1}^nb_i$ 

3.(1)若sum = 0, 则说明b数组已符合题意, 输出b数组即可

. (2)若sum $<$ 0, 则说明当前情况下b数组不满足题意, 其和不平衡, 为使其满足题意, 应使sum个原为正奇数的$b_{i}$自加1。

. (2)若sum $>$ 0, 则说明当前情况下b数组不满足题意, 其和不平衡, 为使其满足题意, 应使sum个原为负奇数的$b_{i}$自减1。

**正确性分析**

首先无论正负，若$a_{i}$是偶数，那么$b_{i}$的值一定唯一确定且为$\frac{a_{i}}{2}$

接着, 若$a_{i}$为奇数,且我们取 $b_{i}$ = \[$\frac{a_{i}}{2}$](向零取整) 时:

- 若$a_{i}$为正数, $b_{i}$ + 1 = ⌈$\frac{a_{i}}{2}$⌉
- 若$a_{i}$为负数, $b_{i}$ - $ $ 1 = ⌊$\frac{a_{i}}{2}$⌋

即 $b_{i}$ 在上述条件下的 +1( -1) 运算一定合法, 且在一般情况下正确操作sum次后一定可以得到一组解

```cpp
//样例
3
10
-5
-5
```

```cpp
STEP 1:
下标 1  2  3  4
a[]  3  10 -5  -5
b[]  1  5  -2  -2

STEP 2:
sum = 1

STEP 3:
while(sum>0)
	∵a[3] mod 2 == 1
	∴b[3]++, sum--
```

**代码**

```cpp
#include<cstdio>			//Mubuky
int a[13846],b[13846];
inline int abs(int x)
{
	return x<0?-1*x:x;
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	int sum=0;
	for(int i=1;i<=n;i++){
		b[i]=a[i]/2;
		sum+=b[i];
	}
	if(sum>0){
		for(int i=1;i<=n;i++){
			if(sum>0&&a[i]<0&&abs(a[i])%2==1){
				b[i]--;
				sum--;
			}
			printf("%d\n",b[i]);
		}
	}else if(sum<0){
		for(int i=1;i<=n;i++){
			if(sum<0&&a[i]>0&&abs(a[i])%2==1){
				b[i]++;
				sum++;
			}
			printf("%d\n",b[i]);
		}
	}else{
		for(int i=1;i<=n;i++){
			printf("%d\n",b[i]);
		}
	}
	return 0;
}
```

### **思路2:**

已知数据保证一定有解, 我们不妨直接进行如下操作:

- 若$a_{i}$是偶数： $b_{i}$ = $\frac{a_{i}}{2}$
- 若$a_{i}$是奇数： 若上一个奇数向上取整，则$b_{i}$ = ⌊$\frac{a_{i}}{2}$⌋, 若上一个奇数向下取整，则$b_{i}$ = ⌈$\frac{a_{i}}{2}$⌉.

**代码**

```cpp
#include<cstdio>		//Mubuky
int main()
{
	int n;
	scanf("%d",&n);
	int flag=1;
	for(int i=1;i<=n;i++) {
		int x;
		scanf("%d",&x);
		if(x%2){
			printf("%d\n",(x+flag)/2);
			flag*=-1;
		}else{
			printf("%d\n",x/2);
		}
	}
	return 0;
}
```

**_By Mubuky_**

---

## 作者：PigJokerYellow (赞：1)

## 前言

比较简单的一道题。

## 题意

给定 $ n $ 个整数，你可以将每个数除以二，向上或向下取整均可，使得修改后总和为零。

## 思路

首先数据保证有解，则这些数都除以二之后相加必定可以为零，而影响此和的，便是向上向下取整所带来的误差。

所以我们向除以二这一点分析，如果一个数是偶数，那么向上或者向下取整都不会改变 $ \frac{ a_i }{2} $ 的值。

如果这个数是奇数，若我们向上取整，会导致总和多一，而向下取整则会导致总和少一。

我们设共有 $ cnt $ 个奇数，因要使总和为零，则要使加一和减一的操作所达成的效果相等，则要有 $ \frac{ cnt }{2} $ 个向上取整和 $ \frac{ cnt }{2} $ 个向下取整的奇数。

综上，我们只需要记录奇数的个数 $ cnt $，前一半向上取整，后一半向下取整即可。

## Code


```cpp
#include <bits/stdc++.h>
using namespace std;
using ll=long long;

const int N=1e6+10;
ll n;
ll a[N],b[N];
ll cnt,tmp;

int main(){
	cin>>n;
	for(ll i=1;i<=n;i++){
		cin>>a[i];
		if(abs(a[i])%2==0) b[i]=a[i]/2;
		//是偶数就直接除以二 
		else cnt++;
		//统计奇数个数 
	}
	for(ll i=1;i<=n;i++){
		if(abs(a[i])%2==1){
			tmp++;
			//第几个奇数 
			if(tmp<=cnt/2) b[i]=(a[i]+1)/2;
			//前一半向上取整 
			else b[i]=(a[i]-1)/2;
			//后一半向下取整 
		} 
	}
	for(ll i=1;i<=n;i++){
		cout<<b[i]<<'\n';
	}
	return 0;
}

```

---

## 作者：YangXiaopei (赞：1)

## 简化题意：

给你 $n$ 数 $a_1,a_2......a_n$，你可以选择让他变为 $\left\lfloor\dfrac{a}{2}\right\rfloor$ 或者 $\left\lceil\dfrac{a}{2}\right\rceil$，使最终的 $\sum\limits_{i = 1} ^ n a_i$ 是 $0$。

## 思路：

分两种情况：

* $a_i$ 是偶数。

* $a_i$ 是奇数。

先看 $a_i$ 是偶数的情况。

当 $a_i$ 是偶数时，不管变成 $\left\lfloor\dfrac{a_i}{2}\right\rfloor$ 还是 $\left\lceil\dfrac{a_i}{2}\right\rceil$ 都一样，所以可以直接除二。

再看 $a_i$ 是奇数的情况。

当 $a_i$ 是奇数时，$\left\lfloor\dfrac{a_i}{2}\right\rfloor$ 和 $\left\lceil\dfrac{a_i}{2}\right\rceil$ 会相差一，我们可以先将 $a_i$ 暂定为 $\left\lfloor\dfrac{a_i}{2}\right\rfloor$。并用一个 $vis_i$ 将 $a_i$ 标记为奇数。

我们此时就可以看 $\sum\limits_{i = 1} ^ n a_i$ 了。

$\sum\limits_{i = 1} ^ n a_i$ 分三种情况：

当 $\sum\limits_{i = 1} ^ n a_i = 0$ 时，我们什么也不用做，直接输出即可。

当 $\sum\limits_{i = 1} ^ n a_i < 0$ 时，就说明负数的和将整体的和拉低了，但负数的和已经向下取整了，无法变大。所以我们只能将正数的和调大，也就是所有被 $vis$ 标记了的正奇数，都可以加 $1$。那我们一旦加了 $\left| \sum\limits_{i = 1} ^ n a_i \right|$ 个正奇数时，和为 $0$ 了。就可以退出了。

当 $\sum\limits_{i = 1} ^ n a_i > 0$ 时，操作方法同上。

到了这里，问题又出现了：如何判断正负。

因为 $1$ 和 $-1$ 除二之后都是 $0$，判断不了属于正，还是属于负。

我们此时，可以在除之前判断。我们可以将负奇数的 $vis$ 标为 $-1$，这样就能完美判断负数了。

最后，我们就完美地切掉了这题。

## 代码：

个人写的可能有点复杂，各位神犇们看懂了自己写即可。本人代码仅作参考。

再次提醒您：~~规则千万条，诚信第一条。写题不规范，封号两行泪。~~

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, sum, a[15005], vis[15005];
int main(){
	cin >> n;
	for(int i = 1; i <= n; i++){
		cin >> a[i];
		if(!(a[i] & 1)){
			a[i] /= 2;
		}
		else{
			if(a[i] < 0){
				vis[i] = -1;
			}
			else{
				vis[i] = 1;
			}
			a[i] /= 2;
		}
		sum += a[i];
	}
	if(sum == 0){
		
	}
	else if(sum < 0){
		sum = abs(sum);
		for(int i = 1; i <= n; i++){
			if(vis[i] == 1){
				sum--;
				vis[i] = 0;
				a[i]++;
			}
			if(sum == 0){
				break;
			}
		}
	}
	else{
		sum = abs(sum);
		for(int i = 1; i <= n; i++){
			if(vis[i] == -1){
				sum--;
				vis[i] = 0;
				a[i]--;
			}
			if(sum == 0){
				break;
			}
		}
	}
	for(int i = 1; i <= n; i++){
		cout << a[i] << "\n";
	}
	return 0;
}
```

---

## 作者：Aybbl_xc (赞：1)

# 前言
逛了一圈题解，其实大家思路都差不多，我讲的详细一点而已。
# 题目大意
现在给你一个 $n$ 和 $n$ 个整数 $a_i$。   

若 $b_i$ 为偶数，$b_i = \frac{a_i}{2}$

否则，$b_i = \lfloor\frac{a_i}{2}\rfloor$ 或者 $b_i = \lceil$$\frac{a_i}{2}\rceil$

最后得到所有的 $b_i$ 为 $0$，输出 $b_i$。
# 思路
**在完美平衡前所用数加起来为 $0$**，**说明在完美平衡后也要为 $0$。** **由于要进行上下取整，题目中说道数据保证一定有解
所以知道每次上下取整不同就可以相互抵消**。
# 代码环节
```
#include<bits/stdc++.h>
using namespace std;
int n;
int temp;//用来记录上下取整 
int main(){
	cin>>n;
	temp=1; 
	for(int i=1;i<=n;i++){
		int x;
        scanf("%d",&x);
		if(x%2){//判断奇偶
		    printf("%d\n",(x+temp)/2);
			temp*=-1;//更改上下取整 
		}else printf("%d\n",x/2);//偶数情况 
	}
	return 0;//好习惯 
}
```

完结散花！！！

---

## 作者：dhpzy (赞：0)

# 题目大意
给你 $n$ 个整数，

若 $a_i$ 为偶数，$b_i=\frac{a_i}{2}$，

若 $a_i$ 奇数，$b_i=\left\lfloor\dfrac{a_i}{2}\right\rfloor$ 或者 $b_i=\left\lceil\dfrac{a_i}{2}\right\rceil$。

最终 $b_i$ 之和为 $0$，输出所有的 $b_i$。 
# 思路
因为数据一定保证有解，一定有偶数个奇数，所以我们可以进行以下操作：

如果 $a_i$ 是偶数，$b_i=\frac{a_i}{2}$，

如果 $a_i$ 是奇数，若 $b_{i-1}=\left\lfloor\dfrac{a_{i-1}}{2}\right\rfloor$，则 $b_i=\left\lceil\dfrac{a_i}{2}\right\rceil$，

若 $b_{i-1}=\left\lceil\dfrac{a_{i-1}}{2}\right\rceil$，则 $b_i=\left\lfloor\dfrac{a_i}{2}\right\rfloor$。
# 代码 
```
#include<bits/stdc++.h>
using namespace std;
int n,x,f=1;
int main()
{
	cin>>n;
	while(n--)
	{
		scanf("%d",&x);
		if(x&1)//判断奇偶
		{
			int t=(x+f)>>1;//(x+f)>>1相当于(x+f)/2
			printf("%d\n",t);
			f^=1;//控制向上还是向下取整
		}else printf("%d\n",x>>1);
	}
}
```


---

## 作者：hao_zi6366 (赞：0)

## 题意简述

思路其实很简单，~~但是一开始看题时被唬到了~~，一个数可以分两种情况讨论：

- 当 $a_i \bmod 2 =0$，即 $a_i$ 是偶数时，直接除以 2 即可。
- 当 $a_i \bmod 2 =1$，即 $a_i$ 是奇数时，进行与上一个是奇数的数相反的操作（即上一个数向上取整，则这一个数向下取整；即上一个数向下取整，则这一个数向上取整）就可以了。

题目保证有解，则一定有偶数个奇数，那现在的总和就一定为 0 了。

## 完整代码
```cpp
#include<bits/stdc++.h>
typedef long long ll;

int main(){
	/*freopen("xxx.in","r",stdin);
	freopen("xxx.out","w",stdout);*/\
	std::ios::sync_with_stdio(0);
	std::cout.tie(0);
	std::cin.tie(0);
	
	int n;
	std::cin>>n;
	std::vector<int> a(n+2);
	bool b=0;
	for(int i=1;i<=n;i++){
		std::cin>>a[i];
		if(a[i]%2){		//如果是奇数 
			if(b) std::cout<<(a[i]+1)/2<<"\n";	//上取整 
			else std::cout<<(a[i]-1)/2<<"\n";	//下取整 
			b^=1;		//调整标记 
		}else{			//如果是偶数 
			std::cout<<a[i]/2<<"\n";			//直接输出 
		} 
		
	}
	return 0;
}
```


---

## 作者：fighter (赞：0)

~~感觉B题比A题好写~~

先无脑把每个初始数字/2，如果最后和不为0，就分正负情况分别调整即可（注意可以调整的前提是在初始数组中是奇数）。

```cpp
#include <bits/stdc++.h>
#define MAX 20005
using namespace std;

int n;
int a[MAX], b[MAX];

int main()
{
    cin >> n;
    int s = 0;
    for(int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
        b[i] = a[i]/2;
        s += b[i];
    }
    
    if(s > 0){
        for(int i = 1; i <= n && s > 0; i++){
            if(a[i] < 0 && (-a[i])%2 == 1) s--, b[i]--;
        }
    }
    else if(s < 0){
        for(int i = 1; i <= n && s < 0; i++){
            if(a[i] > 0 && (a[i]%2 == 1)) s++, b[i]++;
        }
    }
    
    for(int i = 1; i <= n; i++){
        printf("%d\n", b[i]);
    }

    return 0;
}
```

---

## 作者：littleseven (赞：0)

### 安利博客：[博客地址](http://littleseven.top/)

首先因为题目中没有说没有解怎么办，那么我们大可考虑保证数据有解。

按照题目中所说的，我们会发现，影响总和是否为$0$的情况（需要考虑上下取整）一定是当前的$a_i$为一个奇数。那么我们不妨分奇偶讨论这个问题：

- 若当前$a_i$为偶数，直接取$\frac{a_i}{2}$即可。
- 若当前$a_i$为奇数，考虑如果上一个奇数向下取整，那么当前取$b_i =  \left \lceil\dfrac{a_i}{2} \right \rceil $，反之如果上一个奇数向上取整，那么当前取$b_i = \left \lfloor\dfrac{a_i}{2} \right \rfloor$。

显然，如果数据保证有解，按照这个策略一定会得到一个正解。

***Code：***

```cpp
#include <bits/stdc++.h>
 
using namespace std;
 
int n, x, cnt = 1;
 
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i ++ ) {
        scanf("%d", &x);
        if (x % 2 == 0) {
            printf("%d\n", x / 2);
            continue ;
        }
        else {
            if (cnt == 0) {
                printf("%d\n", (int)ceil(x * 1.0 / 2)), cnt = 1;
            }
            else {
                printf("%d\n", (int)floor(x * 1.0 / 2)), cnt = 0;
            }
        }
    }
}
```



---

## 作者：StudyingFather (赞：0)

将每个人的 rating 变化分为两种情况：

- rating 变化为偶数的，直接折半即可。
- rating 变化为奇数的，显然有偶数个人（奇数个奇数相加只能是奇数），在 rating 变化折半的前提下，我们取一半的人结果向上取整，一半的人结果向下取整，就可以保证总变化值为 0。

```cpp
#include <cstdio>
int main()
{
 int n;
 scanf("%d",&n);
 int f=1;
 for(int i=1;i<=n;i++)
 {
  int x;
  scanf("%d",&x);
  if(x%2==0)printf("%d\n",x/2);
  else printf("%d\n",(x+f)/2),f*=-1;
 }
 return 0;
}
```


---

