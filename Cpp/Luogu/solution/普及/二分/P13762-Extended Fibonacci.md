# Extended Fibonacci

## 题目描述

定义斐波那契数列 $f$ 如下：

1. $f_{1}=f_{2}=1$；

2. $f_{i} = f_{i-1} + f_{i-2}$，其中 $i \geq 3$ 且 $i$ 为整数。

定义当 $y-x$ 是偶数时，$v(x,y) = 1$，否则 $v(x,y) = 0$。

现在给出非负整数 $a$，请问是否存在一对正整数 $p,q$，满足 $p \leq q \leq 2 \times 10^{9}$ 且 $\sum\limits_{i=p}^{q-1}\sum\limits_{j=i+1}^{q} v(f_{i},f_{j}) = a$（也就是要求从斐波那契数列第 $p$ 项到第 $q$ 项中，在不考虑某一项减去自身的情况下，有 $a$ 对数的差值是偶数）？如果存在，输出**任意**一组解，否则请输出 $-1$。

## 说明/提示

#### 【样例解释】

计算可得斐波那契数列前 $6$ 项为 $1,1,2,3,5,8$。

对于第 $1$ 组数据，因为 $f_{3} - f_{2} = 2 - 1 = 1$ 不是偶数，所以当 $p = 2, q = 3$ 时结果为 $0$，符合要求。由于解不唯一，$p = 1, q = 1$ 等其他答案也是符合要求的。

对于第 $2$ 组数据，注意到 $f_{3} - f_{2} = 2 - 1 = 1$ 不是偶数，$f_{4} - f_{3} = 3 - 2 = 1$ 也不是偶数，但 $f_{4} - f_{2} = 3 - 1 = 2$ 是偶数。所以当 $p = 2, q = 4$ 时结果为 $1$，符合要求。由于解不唯一，$p = 1, q = 2$ 等其他答案也是符合要求的。

对于第 $3$ 组数据，因为 $f_{6} - f_{3},f_{5} - f_{4}$ 均为偶数，而其他情况均不为偶数，所以当 $p = 3, q = 6$ 时结果为 $2$，符合要求。当然也存在其他满足要求的解。

对于第 $4$ 组数据，可以证明不存在任何符合要求的解。

|子任务编号|分值|$t \leq$|$a \leq$|
|:-:|:-:|:-:|:-:|
|$1$|$10$|$6$|$5$|
|$2$|$15$|$101$|$100$|
|$3$|$15$|$1001$|$1000$|
|$4$|$15$|$10^{4}$|$2 \times 10^{6}$|
|$5$|$20$|$1000$|$2 \times 10^{9}$|
|$6$|$25$|$10^{5}$|$10^{17}$|

对于 $100\%$ 的数据，$t \leq 10^{5},a \leq 10^{17}$。

## 样例 #1

### 输入

```
7
0
1
2
5
44422
1919810
905304292476```

### 输出

```
2 3
2 4
3 6
-1
114 514
-1
114514 1919810```

# 题解

## 作者：ShanLing (赞：2)

两个偶数的差和两个奇数的差都是偶数，因此设所选区间中偶数有 $x$ 个，奇数有 $y$ 个，则差为偶数的数对有 $\binom{x}{2} + \binom{y}{2}$ 个。 因为知道了奇数和偶数分别的个数就很容易构造出区间，因此做一下变型，题目变成了解方程：$x(x-1)+y(y-1)=2a$。

容易发现斐波那契数列的第 $3k$ 项为偶数，其余项为奇数，因此 $2x\approx y$。 分讨一下 $x$ 和 $y$ 的具体关系：  
1. $y=2x+2$ 举例：$\{1,1,2,3,5\}$；带入原方程得 $5x^2+5x+2-2a=0$。
2. $y=2x+1$ 举例：$\{1,1,2,3\}$；带入原方程得 $5x^2+x-2a=0$。
3. $y=2x$ 举例：$\{1,1,2\}$；带入原方程得 $5x^2-3x-2a=0$。
4. $y=2x-1$ 举例：$\{1,2,3,5,8\}$；带入原方程得 $5x^2-7x+2-2a=0$。
5. $y=2x-2$ 举例：$\{2,3,5,8\}$；带入原方程得 $5x^2-11x+6-2a=0$。

因此对于每一次询问，尝试求以上方程的正整数解，任何一个方程有解则找到答案，都无解则输出 $-1$。将$x$、$y$  转换成 $p$、$q$ 的细节请看代码：

```
#include <bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define int long long

int T,n;

int solve(int a,int b,int c)//解一元二次方程
{
    int dlt=b*b-4*a*c;
    if(dlt<0)
        return 0;
    if((int)(sqrt(dlt))*(int)(sqrt(dlt))!=dlt)
        return 0;

    dlt=sqrt(dlt)-b;
    if(dlt%(2*a) || dlt*a<0)
        return 0;
    return dlt/2/a;
}

signed main( void )
{
    scanf("%lld",&T);

    while(T--)
    {
        scanf("%lld",&n);
        n*=2;

        //依次判断每一种情况是否有解，有解就根据解选尽量靠前的区间（q<=2e9）
        int ans=solve(5,5,2-n);
        if(ans && 3*ans+2<=2e9)
        {
            printf("1 %lld\n",3*ans+2);
            continue;
        }

        ans=solve(5,1,-n);
        if(ans && 3*ans+1<=2e9)
        {
            printf("1 %lld\n",3*ans+1);
            continue;
        }

        ans=solve(5,-3,-n);
        if(ans && 3*ans<=2e9)
        {
            printf("1 %lld\n",3*ans);
            continue;
        }

        ans=solve(5,-7,2-n);
        if(ans && 3*ans<=2e9)
        {
            printf("2 %lld\n",3*ans);
            continue;
        }

        ans=solve(5,-11,6-n);
        if(ans && 3*ans<=2e9)
        {
            printf("3 %lld\n",3*ans);
            continue;
        }

        printf("-1\n");
    }

    return 0;
}
```

---

## 作者：Milky_Cat (赞：1)

谁家好人把最简单的题放 T4 啊，还好我是倒开的。

不妨定义 $f_i$ 表示斐波那契数列第 $i$ 项模 $2$ 的值，这样前两项依然是 $1,1$，第三项是 $0$。

容易发现，$1+0=1$，$0+1=1$，$1+1=2 \equiv 0 \pmod 2$。

显然是三位一循环。于是只需要枚举前三位为起点，直接二分答案。直接复制三个二分，暴力美学。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
long long x;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> t;
	while (t--){
		cin >> x;
		long long l = 1, r = (int)1e9, ans, qwq;
		while (l <= r){
			int mid = (l + r) >> 1;
			int jn = mid / 3 * 2 + mid % 3;
			int on = mid - jn;
			long long sum = 1ll * jn * (jn - 1) / 2 + 1ll * on * (on - 1) / 2;
			if (sum >= x)
				ans = mid, qwq = sum, r = mid - 1;
			else
				l = mid + 1;
		}
		if (qwq == x){
			cout << "1 " << ans << "\n";
			continue;
		}
		l = 2, r = (int)1e9;
		while (l <= r){
			int mid = (l + r) >> 1;
			int jn = (mid - 1) / 3 * 2 + (mid - 1) % 3;
			if ((mid - 1) % 3 == 2)
				jn--;
			int on = mid - jn - 1;
			long long sum = 1ll * jn * (jn - 1) / 2 + 1ll * on * (on - 1) / 2;
			if (sum >= x)
				ans = mid, qwq = sum, r = mid - 1;
			else
				l = mid + 1;
		}
		if (qwq == x){
			cout << "2 " << ans << "\n";
			continue;
		}
		l = 3, r = (int)1e9;
		while (l <= r){
			int mid = (l + r) >> 1;
			int jn = (mid - 2) / 3 * 2 + (mid - 2) % 3;
			if ((mid - 2) % 3)
				jn--;
			int on = mid - jn - 2;
			long long sum = 1ll * jn * (jn - 1) / 2 + 1ll * on * (on - 1) / 2;
			if (sum >= x)
				ans = mid, qwq = sum, r = mid - 1;
			else
				l = mid + 1;
		}
		if (qwq == x){
			cout << "3 " << ans << "\n";
			continue;
		}
		cout << "-1\n";
	}
	return 0;
}
```

---

## 作者：ridewind2013 (赞：0)

## 题意

定义斐波那契数列 $f$ 如下：

1. $f_{1}=f_{2}=1$；

2. $f_{i} = f_{i-1} + f_{i-2}$，其中 $i \geq 3$ 且 $i$ 为整数。



求 $p,q$，满足 $p \leq q \leq 2 \times 10^{9}$，且要求从斐波那契数列第 $p$ 项到第 $q$ 项中，在不考虑某一项减去自身的情况下，有 $a$ 对数的差值是偶数。如果存在，输出任意一组解，否则输出 $-1$。


## 思路
我们来分析一下题意，求从斐波那契数列第 $p$ 项到第 $q$ 项中，有多少对数的差值是偶数，其实就是计算斐波那契数列对 $2$ 取模后，有多少对数相等。

我们先来观察一下斐波那契数列模 $2$ 的余数：

```cpp
#include<bits/stdc++.h>
using namespace std;
int f[60];
int main(){
	f[1]=f[2]=1;
	for(int i=3;i<=50;i++){
		f[i]=(f[i-1]+f[i-2])%2;
	}
	for(int i=1;i<=50;i++){
		cout<<f[i]<<"\n";
	}
	return 0;
}
```

这份代码输出结果如下：

```
1
1
0
1
1
0
1
1
0
1
1
0
1
1
0
1
1
0
1
1
0
1
1
0
1
1
0
1
1
0
1
1
0
1
1
0
1
1
0
1
1
0
1
1
0
1
1
0
1
1
```

我们会发现 $f$ 数组每 $3$ 个为一循环，循环节为 $1,1,0$。

所以如果存在答案，那么一定至少有一组解 $p\le 3$，所以我们可以进行 $3$ 次二分，二分右端点 $q$ 是否有解。

如果相等的对数大于 $a$，那么令 $r=mid-1$。

如果相等的对数小于 $a$，那么令 $l=mid+1$。

如果相等的对数恰好等于 $a$，那么就存在一组解，直接输出即可。

重点是怎样计算相等的对数：

首先需要计算 $p$ 到 $q$ 之间 $1$ 和 $0$ 的个数。

我们先来暴力求一下前 $i$ 个数中 $1$ 的个数：

```cpp
#include<bits/stdc++.h>
using namespace std;
int f[60];
int main(){
	f[1]=f[2]=1;
	for(int i=3;i<=50;i++){
		f[i]=(f[i-1]+f[i-2])%2;
	}
	int sm=0;
	for(int i=1;i<=50;i++){
		sm+=f[i];
		cout<<sm<<"\n";
	}
	return 0;
}
```

输出如下：

```
1
2
2
3
4
4
5
6
6
7
8
8
9
10
10
11
12
12
13
14
14
15
16
16
17
18
18
19
20
20
21
22
22
23
24
24
25
26
26
27
28
28
29
30
30
31
32
32
33
34
```

我们找规律后可以得出前 $x$ 个斐波那契数中 $1$ 的个数为 $x$ 除以 $3$ 的结果加上 $x$ 除以 $3$ 的余数，那么 $0$ 的个数就等于 $x$ 减去前 $x$ 个斐波那契数中 $1$ 的个数。

那么 $p$ 到 $q$ 之间 $1$ 的个数 $c1$ 就是前 $q$ 个斐波那契数中 $1$ 的个数减去前 $p-1$ 个斐波那契数中 $1$ 的个数，$p$ 到 $q$ 之间 $0$ 的个数 $c0$ 同理。

那么 $p$ 到 $q$ 中相等的对数就是 $C_{c1}^{2}+C_{c0}^{2}$，即 $\frac{c1\times(c1-1)}{2}+\frac{c0\times(c0-1)}{2}$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int c1(int x){//前 x 个斐波那契数中 1 的个数
    int t=x/3,k=x%3;
    return t*2+k;
}
int c0(int x){//前 x 个斐波那契数中 0 的个数
    return x-c1(x);
}
int check(int p,int q){//p到q中相等的对数
    int x=c1(q)-c1(p-1),y=c0(q)-c0(p-1);
    return x*(x-1)/2+y*(y-1)/2;
}
signed main(){
    int t;
    cin>>t;
    while(t--){
        int a;
        cin>>a;
        int l=1,r=2e9,ans=-1;
        while(l<=r){//l=1时的二分
            int mid=l+r>>1;
            int x=check(1,mid);
            if(x>a)r=mid-1;
            else if(x<a)l=mid+1;
            else{
                ans=mid;
                break;
            }
        }
        if(ans>0){
            cout<<"1 "<<ans<<"\n";
            continue;
        }
        l=2,r=2e9;
        while(l<=r){//l=2时的二分
            int mid=l+r>>1;
            int x=check(2,mid);
            if(x>a)r=mid-1;
            else if(x<a)l=mid+1;
            else{
                ans=mid;
                break;
            }
        }
        if(ans>0){
            cout<<"2 "<<ans<<"\n";
            continue;
        }
        l=3,r=2e9;
        while(l<=r){//l=3时的二分
            int mid=l+r>>1;
            int x=check(3,mid);
            if(x>a)r=mid-1;
            else if(x<a)l=mid+1;
            else{
                ans=mid;
                break;
            }
        }
        if(ans>0)cout<<"3 "<<ans<<"\n";
        else cout<<"-1\n";
    }
    return 0;
}
//有不懂的地方可以私信问我
```

---

## 作者：lyx128 (赞：0)

本题目考虑使用二分暴力实现，根据题目里的式子，我们可以轻而易举地推理出每个 $f_i$ 的奇偶性，即按照**奇奇偶**的性质排列，所以左侧只需要枚举 $1$ 到 $3$，而右边通过二分实现，满足奇偶性相同的个数为 $\frac{奇数个数 \times (奇数个数-1)}{2}+\frac{偶数个数 \times (偶数个数-1)}{2}$，即同奇偶性交叉向乘，而根据排列顺序也可以快速地求出奇数个数和偶数个数，代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=3e7;
int T;
ll a;

ll check(ll l,ll r){
    ll even=(r/3)-((l-1)/3);
    ll odd=r-l+1-even;
    return odd*(odd-1)/2+even*(even-1)/2;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>T;
    while(T--){
        cin>>a;
        if(a==0){
            cout<<2<<" "<<3<<"\n";
            continue;
        }
        bool flag=0;
        for(ll l=1;l<=3&&!flag;l++){
            ll rl=l,rr=2e9;
            while(rl<=rr){
                ll mid=(rl+rr)/2;
                if(check(l,mid)<a)
                    rl=mid+1;
                else
                    rr=mid-1;
            }
            if(check(l,rr)==a){
                cout<<l<<" "<<rr-1<<"\n";
                flag=1;
                break;
            }
            if(check(l,rl)==a){
                cout<<l<<" "<<rl<<"\n";
                flag=1;
                break;
            }
        }
        if(!flag)
            cout<<-1<<"\n";
    }
    return 0;
}
```

---

## 作者：ICU152_lowa_IS8 (赞：0)

首先将每个数 $\bmod 2$，得到如下一个序列：$1 1 0110110110\cdots$。


答案只与 $ p\bmod 3$ 和 $q\bmod3$ 的值有关是非常显然的。

直接枚举 $p$ 和 $q\bmod3$ 的值，然后我们可以将整个序列看成如下形式：

$\color{0000FF}\text{10}\color{000000}\text{110}\cdots110\color{FF0000}\text{11}$；

也就是说，蓝色部分为头部，红色部分为尾部，整个序列由头部、尾部这两个不完整的循环以及中间的完整循环构成。

设中间有 $x$ 个循环，那么可以根据不同的起止点位置列出不同的一元二次方程，任意一种情况有整数解即可。

一元二次方程推导过程详见代码注释（可以看到代码非常长，因为有很多注释和重复部分，实际上可以压缩到四五十行左右）。

数据范围 $a\leq 10^{17}$ 而非通常的 $10^{18}$ 为刻意设置，保证暴力计算 $\Delta$ 时不会爆 `long long`。

有更简洁的做法，但自认为代码更好理解。

```
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
//		long long A;
		long long a;
		cin>>a;
		if(a==0){
			cout<<"1 1\n";
			continue;
		}
		bool fl=0;
		long long ans1=0,ans2=0;
		//
		for(int i=0;i<=2;i++){
			if(fl)break;
			for(int j=0;j<=2;j++){
				if(i==0){
					if(j==0){
						//j=i+3x
						//a=(1+2+...+x)+(0+1+...+2x-1)
						//a=(x+1)*x/2+(2x-1)*x
						//(5/2)*x^2-(1/2)*x-a=0
						//Δ= (40a+1)/4
						if((long long)sqrt(40*a+1)*(long long)sqrt(40*a+1)==40*a+1&&(long long)(sqrt(40*a+1)+1)%10==0){
							ans1=i+3;
							ans2=i+3+3*((long long)(sqrt(40*a+1)+1)/2/5);
							fl=1;
							break;
						}
					}
					else if(j==1){
						//j=i+3x+1
						//a=(1+2+...+x)+(0+1+...+2x)
						//a=(x+1)*x/2+x*(2x+1)
						//(5/2)*x^2+(3/2)x-a=0;
						//Δ=(40a+9)/4
						if((long long)sqrt(40*a+9)*(long long)sqrt(40*a+9)==40*a+9&&(long long)(sqrt(40*a+9)-3)%10==0){
							ans1=i+3;
							ans2=i+3+3*((long long)(sqrt(40*a+9)-3)/2/5)+1;
							fl=1;
							break;
						} 
					}
					else{
						//j=i+3x+2;
						//a=(1+2+...+x)+(0+1+...+2x+1)
						//a=(x+1)*x/2+(2x+1)*(x+1)
						//(5/2)*x^2+(7/2)*x+1-a=0;
						//Δ=(40a+9)/4
//						cout<<(int)(40*a+9)<<" "<<(int)sqrt(40*a+9)<<endl; 
						if((long long)sqrt(40*a+9)*(long long)sqrt(40*a+9)==40*a+9&&(long long)(sqrt(40*a+9)-7)%10==0){
							ans1=i+3;
							ans2=i+3+3*((long long)(sqrt(40*a+9)-7)/2/5)+2;
							fl=1;
							break;
						}
					}
				}
				else if(i==1){
					if(j==1){
						//j=i+3x
						//a=(1+2+...+x-1)+(0+...+2x)
						//a=x*(x-1)/2+x*(2x+1)
						//(5/2)*x^2+(1/2)*x-a=0;
						if((long long)sqrt(40*a+1)*(long long)sqrt(40*a+1)==40*a+1&&(int)(sqrt(40*a+1)-1)%10==0){
							ans1=i+3;
							ans2=i+3+3*((long long)(sqrt(40*a+1)-1)/2/5);
							fl=1;
							break;
						} 
					}
					else if(j==2){
						//j=i+3x+1
						//a=(1+2+...+x-1)+(0+1+...+2x+1)
						//a=x*(x-1)/2+(2x+1)*(x+1)
						//(5/2)*x^2+(5/2)*x+1-a=0;
						//Δ=(40a-15)/4
						if((long long)sqrt(40*a-15)*(long long)sqrt(40*a-15)==40*a-15&&(long long)(sqrt(40*a-15)-5)%10==0){
							ans1=i+3;
							ans2=i+3+3*((long long)(sqrt(40*a-15)-5)/2/5)+1;
							fl=1;
							break;
						}
					}
					else{
						//j=i+3x+2
						//a=(1+2+...+x)+(0+1+...+2x+1)
						//a=x*(x+1)/2+(2x+1)*(x+1)
						//(5/2)*x^2+(7/2)*x+1-a=0;
						//同i=0 j=2 
						if((long long)sqrt(40*a+9)*(long long)sqrt(40*a+9)==40*a+9&&(long long)(sqrt(40*a+9)-7)%10==0){
							ans1=i+3;
							ans2=i+3+3*((long long)(sqrt(40*a+9)-7)/2/5)+2;
							fl=1;
							break;
						}
					}
				}
				else{
					if(j==2){
						//j=i+3x
						//a=(1+2+...+x-1)+(0+1+...+2x)
						//同i=1 j=1
						if((long long)sqrt(40*a+1)*(long long)sqrt(40*a+1)==40*a+1&&((long long)sqrt(40*a+1)-1)%10==0){
							ans1=i+3;
							ans2=i+3+3*((long long)(sqrt(40*a+1)-1)/2/5);
							fl=1;
							break;
						} 
					}
					else if(j==0){
						//j=i+3x+1
						//a=(1+2+...+x)+(0+1+...+2x)
						//同i=0 j=1
						if((long long)sqrt(40*a+9)*(long long)sqrt(40*a+9)==40*a+9&&((long long)sqrt(40*a+9)-3)%10==0){
							ans1=i+3;
							ans2=i+3+3*((long long)(sqrt(40*a+9)-3)/2/5)+1;
							fl=1;
							break;
						}  
					}
					else{
						//j=i+3x+2
						//a=(1+2+...+x)+(0+1+...+2x+1)
						//同i=0 j=2
						if((long long)sqrt(40*a+9)*(long long)sqrt(40*a+9)==40*a+9&&((long long)sqrt(40*a+9)-7)%10==0){
							ans1=i+3;
							ans2=i+3+3*(((long long)sqrt(40*a+9)-7)/2/5)+2;
							fl=1;
							break;
						} 
					}
				}
			}
		}
		if(fl)cout<<ans1<<" "<<ans2<<"\n";
		else cout<<"-1\n";
	}
	return 0;
}
//1 1 0   1 1 0   1 1 0   1 1 0x=2
```

---

## 作者：zhangxiaoyu008 (赞：0)

观察到我们只需要关注斐波那契数列的奇偶性即可。

$f_1$ 为奇数，$f_2$ 为奇数，所以 $f_3$ 为偶数。

$f_2$ 为奇数，$f_3$ 为偶数，所以 $f_4$ 为奇数。

$f_3$ 为偶数，$f_4$ 为奇数，所以 $f_5$ 为奇数。

然后因为，$f_4$ 为奇数，$f_5$ 为奇数所以循环了。

故，斐波那契数列的奇偶性为奇，奇，偶，奇，奇，偶……

左端点枚举 $1 \sim 3$，右端点枚举 $\bmod \ 3$ 的余数，然后求根公式即可。

:::info[$\large{\mathbf{Code}}$]{open}
```cpp line-numbers
#include <bits/stdc++.h>
using namespace std;‌‍‍‌
typedef long long LL;‌‍‍‌
int T, l[] = {1, 0, -1}‍‌, r[] = {-1, 1, 1}‍‌;‌‍‍‌
LL v, p, q;‌‍‍‌
LL check(LL b, LL c) {
	int a = 5;‌‍‍‌
	if(b * b < 4 * a * c) return -1;‌‍‍‌
	LL delta = b * b - 4 * a * c;‌‍‍‌
	int srt = sqrt(delta), rt = -1;‌‍‍‌
	for(int i = max(0, srt - 5);‌‍‍‌ i <= srt + 5;‌‍‍‌ i ++)
		if((LL)i * i == delta) {
			rt = i;‌‍‍‌
			break;‌‍‍‌
		}‍‌
	if(rt == -1) return -1;‌‍‍‌
	LL ans = -1;‌‍‍‌
	if((rt - b) % 10 == 0) ans = max(ans, (rt - b) / 10);‌‍‍‌
	if((- rt - b) % 10 == 0) ans = max(ans, (- rt - b) / 10);‌‍‍‌
	return ans;‌‍‍‌
}‍‌
int main()
{
	scanf("%d", &T);‌‍‍‌
	while(T --) {
		scanf("%lld", &v);‌‍‍‌
		if(v == 0) {
			printf("2 3\n");‌‍‍‌
			continue;‌‍‍‌
		}‍‌
		v <<= 1;‌‍‍‌
		int c = 0, d = 0;‌‍‍‌
		p = -1, q = -1;‌‍‍‌
		for(int i = 2;‌‍‍‌ i >= 0;‌‍‍‌ i --) {
			if(!l[i]) d ++;‌‍‍‌
			else if(l[i] == 1) c ++;‌‍‍‌
			for(int j = 0;‌‍‍‌ j <= 2;‌‍‍‌ j ++) {
				if(j) c ++;‌‍‍‌
				LL ok = check(4 * c + 2 * d - 3, c * c - c + d * d - d - v);‌‍‍‌
				if(ok >= 0) {
					p = i + 2, q = 3 * ok + j + 3;‌‍‍‌
					break;‌‍‍‌
				}‍‌
			}‍‌
			if(p != -1) break;‌‍‍‌
			c -= 2;‌‍‍‌
		}‍‌
		if(p != -1) printf("%lld %lld\n", p, q);‌‍‍‌
		else printf("-1\n");‌‍‍‌
	}‍‌
	return 0;‌‍‍‌
}‍‌
```
:::

---

