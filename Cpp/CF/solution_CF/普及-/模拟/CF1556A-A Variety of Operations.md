# A Variety of Operations

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1556A/5428dff7add309271d42dab51ff349469f968da9.png)William has two numbers $ a $ and $ b $ initially both equal to zero. William mastered performing three different operations with them quickly. Before performing each operation some positive integer $ k $ is picked, which is then used to perform one of the following operations: (note, that for each operation you can choose a new positive integer $ k $ )

1. add number $ k $ to both $ a $ and $ b $ , or
2. add number $ k $ to $ a $ and subtract $ k $ from $ b $ , or
3. add number $ k $ to $ b $ and subtract $ k $ from $ a $ .

Note that after performing operations, numbers $ a $ and $ b $ may become negative as well.

William wants to find out the minimal number of operations he would have to perform to make $ a $ equal to his favorite number $ c $ and $ b $ equal to his second favorite number $ d $ .

## 说明/提示

Let us demonstrate one of the suboptimal ways of getting a pair $ (3, 5) $ :

- Using an operation of the first type with $ k=1 $ , the current pair would be equal to $ (1, 1) $ .
- Using an operation of the third type with $ k=8 $ , the current pair would be equal to $ (-7, 9) $ .
- Using an operation of the second type with $ k=7 $ , the current pair would be equal to $ (0, 2) $ .
- Using an operation of the first type with $ k=3 $ , the current pair would be equal to $ (3, 5) $ .

## 样例 #1

### 输入

```
6
1 2
3 5
5 3
6 6
8 0
0 0```

### 输出

```
-1
2
2
1
2
0```

# 题解

## 作者：wanggk (赞：3)

[CF1556A题目](https://www.luogu.com.cn/problem/CF1556A)

三种操作：

- 将 $a$ 和 $b$ 同时加上一个值 $k$ .
- 将 $a$ 加上一个值 $k$ ，将 $b$ 减去一个值 $k$  .
- 将 $a$ 减去一个值 $k$ ，将 $b$ 加上一个值 $k$  .

我们可以发现一些事情：

- 由于每次都是同时加上或一加一减，所以两数之和始终为偶数。
- 第一种操作变化的是两数之和，而后两种操作变化的是两数之差。

因此，就可以理清楚了：

- 若 $c+d$ 为奇数，直接 $-1$ 走起。
- 其次，看看两数之和的变化值，如果 $c+d=0$ 操作次数不变，否则操作次数 $+1$ .
- 最后，看下两数之差的变化值，如果 $c=d$ 操作次数不变，否则操作次数 $+1$ .

完整AC代码：

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
int T,c,d;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&c,&d);
		if((c+d)%2==1)
		{
			printf("-1\n");
			continue;
		}
		int ans=0;
		if(c+d!=0) ans++;
		if(c!=d) ans++;
		printf("%d\n",ans);
	}
	return 0;
}
```



---

## 作者：Jerrlee✅ (赞：2)

## 题意
你有两个初值为 $0$ 的数 $a$ 和 $b$，选一个整数 $k$，进行以下操作：

1.$a$ 和 $b$ 加 $k$。

2.$a$ 加 $k$，$b$ 减 $k$。

3.$a$ 减 $k$，$b$ 加 $k$。

给你 $c$ 和 $d$，用最少的操作数使得 $a=c$，$b=d$。若无法得到，输出 $-1$。

## 思路
所有的操作都会让两个数相差偶数，所以差不为偶数就打印 $-1$。

如果 $c$，$d$ 为 $0$，直接打印 $0$。

否则相等就是 $1$。

其它情况是 $2$。
## 代码
```cpp
#include<iostream>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		int a,b; //这里的 a，b 是原题的 c，d。
		cin>>a>>b;
		if(a==0&&b==0) cout<<0<<endl;
		else if(a==b) cout<<1<<endl;
		else if((a-b)%2==0) cout<<2<<endl;
		else cout<<-1<<endl;
	}
}
```
[AC记录（洛谷）](https://www.luogu.com.cn/record/57274963)

[AC记录（CF）](https://codeforces.com/contest/1556/submission/127343543)

---

## 作者：yangzd (赞：1)

# 题目大意

你有两个数 $\texttt{a}$ 和 $\texttt{b}$，初始值都为 $0$，你可以任选一个整数 $\texttt{k}$，进行以下三种操作中的一种：

1.将 $\texttt{a}$ 和 $\texttt{b}$ 都加 $\texttt{k}$

2.将 $\texttt{a}$ 加 $\texttt{k}$，将 $\texttt{b}$ 减 $\texttt{k}$

3.将 $\texttt{b}$ 加 $\texttt{k}$，将 $\texttt{a}$ 减 $\texttt{k}$

对于给定的 $\texttt{c}$ 和 $\texttt{d}$，求最少的操作数使得 $a=c,b=d$ 若无法得到，就输出 $-1$

# 分析

我们可以证明，只有 $4$ 种情况：$-1,0,1,2$。
如果 $c+d$ 为奇数，输出 $-1$，因为无论怎么操作都不会改变 $c+d$ 的奇偶性。

如果 $c=0$ 并且 $d=0$ ,输出 $0$ ,因为不用操作了。

如果 $c=d$ 或者 $c=-d$ ,也就是绝对值相等，输出 $1$，因为这可以通过同时加 $\texttt{c}$ 或者一加一减 $\texttt{c}$ 解决。

其它情况，输出 $2$，可以通过同时将两个数加 $e$（$e$ 可能为负数），使得 $|c-e|=|d-e|$，然后一加一减解决。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std; 

signed main()
{
	ios::sync_with_stdio(0);

    long long t;
    
    cin >> t;
    
    while(t--)
    {
        long long a,b;
        
        cin >> a >> b;
        
        if(abs(a-b)&1)
            cout << "-1" << endl;
            
        else if(a==b && a==0)
            cout << "0" << endl;
            
        else if(a==b)
        	cout << "1" << endl;
			 
        else 
        	cout << "2" << endl;
    }
    
    return 0;
}
```

---

## 作者：fz20181223 (赞：0)

这可能是有本题最简洁的代码的题解

利用数轴稍微模拟一下本题 $a$ 和 $b$ 移动的最短方案，即可发现是这样的：（在下面的讨论中，我们假设 $c < d$，红线是 $a$ 的变化过程，蓝线是 $b$ 的变化过程）。

![](https://cdn.luogu.com.cn/upload/image_hosting/i0mwrjx0.png)

可以发现，答案至多为 $2$ ，分为两个步骤：

1. 把 $a$ 和 $b$ 同时移到 $\frac{d+c}{2}$ 处

2. 把 $a$ 挪到 $c$ ，同时把 $b$ 挪到 $d$

下面讨论什么时候这两个步骤可以省去。

若要省去步骤 $1$，则一开始就存在 $a=b=\frac{d+c}{2}$。因为一开始有 $a=b=0$，所以要想省去必须有 $\frac{d+c}{2}=0$，即 $d=-c$。所以当给定的两个值互为相反数时，可以省略步骤 $1$。

若要省去步骤 $2$，则很明显，$d=c$ 就是必要条件。因为经过了第一次操作后，$a$ 仍然等于 $b$。如果不进行第二步，则最后 $a$ 还是等于 $b$。

如果无解，则说明 $\frac{d+c}{2}$ 不是一个正整数。整个式子乘 $2$ 后，可以化为 $d+c$ 不是一个偶数（即 $d+c$ 是一个奇数）。

于是可以[只用 301B 愉快的 AC 了](https://www.luogu.com.cn/record/57295092)（包含文件输入输出及相应注释，不包含一大堆预编译）！
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		int c,d;
		scanf("%d %d",&c,&d);
		if((d+c)&1) printf("-1\n");
		else printf("%d\n",2-(d==c)-(d==-c));
	}
	return 0;}
```

---

## 作者：cyrxdzj (赞：0)

### 一、思路

根据题意，我们可以判断：$a+b$ 无论何时都是偶数。

证明：当执行第 $2$ 或第 $3$ 个操作时，$a+b=(a+k)+(b-k)$ 或 $a+b=(a-k)+(b+k)$，因此 $a+b$ 不变。

当执行第 $1$ 个操作时，$a+b$ 变为 $(a+k)+(b+k)=a+b+k\times2$，因为 $a+b$ 一开始等于 $0$，而 $k\times2$ 必为偶数（$k$ 是整数），所以 $a+b$ 依然为偶数。

所以，当 $c+d$ 为奇数时，必定无解。

当 $c=0,d=0$ 时，答案为 $0$（显然）。

当 $c=d,c\ne0$ 时，答案为 $1$，此时执行一次 $1$ 号操作即可。

当 $c\ne d$ 且 $c+d$ 为偶数时，答案为 $2$。此时执行一次 $1$ 号操作使得 $a=b=(c+d)\div2,\left\vert a-c\right\vert=\left\vert b-d\right\vert$，然后再执行一次 $2$ 号或 $3$ 号操作即可。

### 二、完整代码

```cpp
#include<cstdio>
using namespace std;
int t;
int c,d;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&c,&d);
		if(c==d)
		{
			if(c==0)
			{
				printf("0\n");
			}
			else
			{
				printf("1\n");
			}
		}
		else if((c+d)%2!=0)
		{
			printf("-1\n");
		}
		else
		{
			printf("2\n");
		}
	}
	return 0;
}

```

By [dengzijun](https://www.luogu.com.cn/user/387836)

---

## 作者：small_turtle (赞：0)

作为本蒟蒻在 Codeforces 切的第二道题，这道题还是比较简单的。
### 思路：

这道题我们可以分类讨论。

1. 输出 0 的情况：

也就是不需要任何操作，即 $(0,0)$。

2. 输出 1 的情况：

只需要一次操作，因为 $a$ 和 $b$ 不可能是负数，所以只能用第一种操作，而当 $a=b$ 的时候，只需要将 $(0,0)$ 都增加 $a$ 即可。

3. 输出 2 的情况：

考虑以下数据 $(1,5)$，因为 $a$ 和 $b$ 不一样，所以一定要用到一次第一种操作和一次第二或第三种操作，当 $(a,b)$ 之间有一个值 $n$ 能满足 $|a-n|=|b-n|$ 时，我们可以用一次第二或第三种操作让初始为 $0$ 的 $a$ 和 $b$ 分别变为 $c$ 和 $d$，而这个数 $n$，就是 $(a,b)$ 之间的**中间数**，如 $(1,5)$ 的中间数为 3，$(3-2,3+2)=(1,5)$，如果要让 $(a,b)$ 之间有一个整数的中间数就必须满足 $a-b$ 的结果是奇数，也就是说当 $a-b$ 为奇数时，最少需要两次操作。

4. 输出 -1 的情况：

与第三点相反，当 $a-b$ 的结果是偶数**且 $a$ 不等于 $b$ 时**，没有一组操作能让初始为 $0$ 的 $a$ 和 $b$ 分别变为 $c$ 和 $d$。
***
### CODE：

```cpp
#include <iostream>
#include <cmath>
using namespace std;
int main()
{
    int t,a,b;
    cin >> t;
    for(int i=1;i<=t;i++)
    {
        cin >> a >> b;
        if(a==0&&b==0)
        {
            cout << 0;
        }
        else if(abs(a-b)%2==1)
        {
            cout << -1;
        }
        else if(a==b)
        {
            cout << 1;
        }
        else
        {
            cout << 2;
        }
        cout << endl;
    }
    return 0;
}
```

---

## 作者：jinxdtaiy (赞：0)

### 题意简述

- 有两个整数 $a$ 和 $b$，它们的初始值为 $0$，给定两个数 $c$ 和 $d$，接下来你可以进行下列操作的任意一种。要求操作完后使得 $a=c$ 且 $b=d$ 。输出最小的操作步数，如果不可能成功的话输出 $-1$。有多组数据。
- $a$ 和 $b$ 同时加 $k$。
- $a$ 加上 $k$，$b$ 减去 $k$。
- $a$ 减去 $k$，$b$ 加上 $k$。其中， $k$ 为任意整数。

### 题目分析

 数学和模拟
- 首先我们可以发现，如果说 $c$，$d$，两个数作差等于一个奇数的话，我们无论如何也不能达成目的，因为两个整数想加减，奇偶性并不发生改变，$0$ 和 $0$ 无论进行多少次操作都无法变成 $c$ 和 $d$。

当 $c-d$ 的绝对值为一个偶数的时候，我们可以对 $c$，$d$ 的情况进行如下讨论。

- 当 $c=d$ 时，我们只需要让 $a$ 和 $b$ 同时加上 $c$ 即可，答案为 $1$。

- 当 $c=d=0$ 时，不需要进行任何操作，此时答案为 $0$。

- 当 $c \neq d$ 时，我们只需要先将 $a$ 和 $b$ 同时加上 $n= \frac{|c-d|}{2}$，然后两数再同时加上 $n-a$ 即可，答案为 $2$。

### 代码如下

```
#include<bits/stdc++.h>
#define int long long//开不开似乎都一样
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}
int t,a,b;
signed main()
{
	t=read();
	while(t--)
	{
		a=read(),b=read();
		if((abs(b-a))%2==1) cout<<-1<<endl;//注意加绝对值
		else if(a==b&&a==0) cout<<0<<endl;
		else if(a==b) cout<<1<<endl;
		else cout<<2<<endl;
	}
	return 0;
}
```

---

## 作者：Wu_while (赞：0)

# 题意

你有两个数 $a$ 和 $b$，初始值均为 $0$，你可以任选一个整数 $k$，进行以下三种操作中的一种：

1. 将 $a$ 和 $b$ 都加 $k$；
2. 将 $a$ 加 $k$，将 $b$ 减 $k$；
3. 将 $b$ 加 $k$，将 $a$ 减 $k$；

对于给定的 $c$ 和 $d$，求最少的操作数使得 $a=c,b=d$，若无法得到，则输出 $-1$。

# 分析

我们先假设能够使得 $a=c,b=d$，如果最后一步是操作2或操作3，那么倒数第二步完成后 $a$ 和 $b$ 必定都等于$\dfrac{c+d}{2}$，因为 $\dfrac{c+d}{2}$ 与 $c$ 和 $d$ 的差值相等。

显然，从 $0$ 到达 $\dfrac{c+d}{2}$ 只需要一次操作1，则操作的个数最多为 $2$。

下面考虑特殊情况：

1. 当 $c=d=0$ 时，显然不需要操作，则答案为 $0$；

2. 当 $c=d≠0$ 时，只需一次操作1，则答案为 $1$；

3. 当 $c$ 和 $d$ 的奇偶性不相同时，显然无法完成，答案为 $-1$ 。

# 代码

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int a,b,c,d;
int ans;
void work()
{
	scanf("%d%d",&c,&d);
	if((c+d)%2!=0)//若奇偶性不同
		ans=-1;
	else
	{
		ans=1;
		a=b=(c+d)/2;
		if(a!=c||b!=d)
			ans=2;
	}
	if(c==0&&d==0)
		ans=0;
	printf("%d\n",ans);
}
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
		work();
	return 0;
}
```

---

## 作者：happy_dengziyue (赞：0)

### 1 思路

我们可以证明，只有 $4$ 种情况：$-1$，$0$，$1$，$2$。

+ 如果 $c+d$ 为奇数，输出 $-1$，因为无论怎么操作都不会改变 $c+d$ 的奇偶性。

+ 如果 $c=0\operatorname{and}d=0$，输出 $0$，因为不用操作了。

+ 如果 $c=d\operatorname{or}c=-d$，也就是绝对值相等，输出 $1$，因为这可以通过同时加 $c$ 或者一加一减 $c$ 解决。

+ 其它情况，输出 $2$，可以通过同时将两个数加 $e$（$e$ 可能为负数），使得 $|c-e|=|d-e|$，然后一加一减解决。

### 2 代码与记录

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
int t;
int n;
int a[100002];
int cnt[2];
int ans;
int ans2;
inline int absi(int a){
	return a>0?a:-a;
}
inline int mi(int a,int b){
	return a<b?a:b;
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1556B_1.in","r",stdin);
	freopen("CF1556B_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		cnt[0]=cnt[1]=0;
		for(int i=1;i<=n;++i){
			scanf("%d",a+i);
			++cnt[a[i]%2];
		}
		if(n==1){
			puts("0");
			continue;
		}
		if(absi(cnt[0]-cnt[1])>1){
			puts("-1");
			continue;
		}
		if(n&1){
			ans=0;
			for(int i=1,j=1;i<=n;++i){
				if(a[i]%2==(cnt[0]<cnt[1])){
					ans+=absi(i-j);
					j+=2;
				}
			}
			printf("%d\n",ans);
		}
		else{
			ans=0;
			ans2=0;
			for(int i=1,j=1;i<=n;++i){
				if(a[i]%2==0){
					ans+=absi(i-j);
					j+=2;
				}
			}
			for(int i=1,j=2;i<=n;++i){
				if(a[i]%2==0){
					ans2+=absi(i-j);
					j+=2;
				}
			}
			printf("%d\n",mi(ans,ans2));
		}
	}
}
```

[记录传送门](https://www.luogu.com.cn/record/57220370)

By **dengziyue**

---

