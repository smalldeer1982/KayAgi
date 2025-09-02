# [ICPC 2022 Jinan R] Identical Parity

## 题目描述

定义一个序列的 **权值** 等于这个序列所有的元素之和。

试判断：是否存在一个长度为 $n$ 的 **排列**，满足以下约束条件？

- 其所有长度为 $k$ 的 **子区间** 的权值具有相同的奇偶性。

## 样例 #1

### 输入

```
3
3 1
4 2
5 3```

### 输出

```
No
Yes
Yes```

# 题解

## 作者：Pyrf_uqcat (赞：8)

### 思路
能否存在这个序列，主要取决于 $k$ 的**奇偶性**。

当 $k$ 为偶，显然，构造一个一奇一偶（奇偶交替）的序列，条件就满足了，序列存在，直接输出就行。

当 $k$ 为奇，可以记录下偶数的数量和奇数的数量，因为奇偶差不能大于一，而小于等于一却依然能构造奇偶交替的序列。所以，判断一下差，大于一就不存在，小于等于一就存在。

---

## 作者：w9095 (赞：5)

[P9671 [ICPC2022 Jinan R] Identical Parity](https://www.luogu.com.cn/problem/P9671)

构造题。感觉中上位黄。

对于 $k$ 为偶数的情况，构造奇偶交替的序列。每次区间向后挪动时，最左边出去的元素和最右边进来的元素奇偶性相同，保证奇偶性不变。这样的序列一定可以构造出来，故 $k$ 为偶数时直接输出 `Yes`。

对于 $k$ 为奇数的情况，每次区间向后挪动时，为了保证奇偶性不变，必须使最左边出去的元素和最右边进来的元素奇偶性相同。由于每一位都需要这样，所以最后一定是一段长度为 $k$ 的奇偶序列重复多次。

由于 $k$ 为奇数，每一段中必然会有一种奇偶性的数多 $1$，不如假设奇数较多。如果重复了 $m$ 整段，那么奇数比偶数多 $m$ 个。在剩余的散段中，为了保证奇偶数的差尽量小，我们要优先使偶数在前，补齐这个差值。

注意，由于我们假定偶数比奇数少，所以偶数数量最多为 $k$ 的向下取整的一半。如果剩余的散段在补满了偶数之后任然有空位，那么只能在加入奇数。这里需要分类讨论。

由于最开始是排列，所以奇数和偶数的差不能超过 $1$。如果经过以上操作之后可以满足这个条件，输出 `Yes`，否则输出 `No`。

```cpp
#include <bits/stdc++.h>
using namespace std;
long long t,n,k;
int main()
{
    scanf("%lld",&t);
    while(t--)
       {
       scanf("%lld%lld",&n,&k);
       if(k%2==0)printf("Yes\n");
       else if(k%2==1)
           {
           if(n%k<=k/2&&(n/k-n%k)<=1)printf("Yes\n");
           else if(n%k>k/2&&(n/k-k/2+(n%k-k/2))<=1)printf("Yes\n");
           else printf("No\n");
           }
       }
    return 0;
}
```

[AC记录](https://www.luogu.com.cn/record/126615223)

---

## 作者：_Star_Universe_ (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/P9671)

## 思路
能否存在序列主要就是 $k$ 的**奇偶性**决定的，当然 $k$ 为奇数时还要再判断一个条件，我在这里给几个样例以外的数据：

列举一个 $k$ 为偶数的：比如说 $n$ 为 $6$ 且 $k$ 为 $4$，那么 $[1,2,3,4],[2,3,4,5],[3,4,5,6]$ 的权值分别是 $10,14,18$，具有相同奇偶性吧！因为一奇一偶交替排列就满足条件，$k$ 为偶数就符合这个规律了，所以 $k$ **为偶数直接输出** `Yes` 就行了。

$k$ **为奇数复杂一点**：举两个不同情况的例子：比如 $k$ 为 $1$ 且有多个元素时，不看 $n$ 就知道**肯定是满足不了**的，因为元素会交替出现奇偶数，所以权值也会交替出现奇偶。但是 $n$ 为 $7$ 且 $k$ 为 $5$ 时，大家看一下这个序列：$[1,2,3,5,4,7,6]$，这个序列不就满足条件了吗？

所以记录一下奇偶数的数量，你应该发现，奇偶差**大于** $1$ 序列必定**不存在**，**小于等于** $1$ 就**存在**，那么大于 $1$ 就输出 `No`，小于等于 $1$ 就输出 `Yes`。

---

## 作者：sfqxx1 (赞：3)

这是一篇 python 题解。

## 题意

给定两个整数 $N$ 和 $K$，是否存在一个排列，使得对于这个排列，每个长度为 $K$ 的区间内奇数个数奇偶性是一样的。

## 思路

一眼一道构造题，我们先从最特殊的情况开始考虑。

- 当 $K=1$ 时，显然不可能满足。

- 当 $K=2$ 时一定满足，显然奇偶交替摆放即可，所以，当 $K$ 是偶数时，都是合法的。

然后，我们根据之前的特殊情况区间内奇数和偶数的个数相同构造即可。

## 代码

```
T = int(input())
for _ in range(T):
    a, b = map(int, input().split())
    c = (a + 1) // 2
    d = a // 2
    e = a // b
    f = a % b
    g = (b + 1) // 2
    h = b // 2
    i = c - e * g
    j = d - e * h
    if j >= 0 and i >= 0 and j + i == f:
        if j <= h and i <= g:
            print("Yes")
        else:
            print("No")
    else:
        print("No")
```

---

## 作者：Ahws_rwhy (赞：2)

此题是一道数学题！

这题是我在这场比赛中代码长度最短的一题。

思路：

此题我们可以通过观察样例可以发现 $s = \frac{n}{2} - \frac{k}{2}  \times \frac{n}{k} $ 其中 $s$ 指剩余元素的数量，这个公式的含义是：每个长度为 $k$ 的子段都会加 $\frac{k}{2} $ 个奇数。而整个数组中所有长度为 $k$ 的子段的个数为 $\frac{n}{k} $ 个。所以 $\frac{k}{2}  \times\frac{n}{k} $ 表示加的奇数的总数。将这个总数从总元素 $\frac{n}{2} $ 个中减去，就得到了剩余元素数量 $s$。

接着只要判断是否存在满足条件的排列，是，则输出 $\texttt{Yes}$，否则输出 $\texttt{No}$。

code:

```
#include <bits/stdc++.h>
using namespace std;
int main() {
	int _;
	cin >> _;
	while(_ --) {
		int n, k;
		cin >> n >> k;
		int s = n / 2 - (k / 2) * (n / k);
		if (s <= k / 2 and sub <= n % k)
        cout << "Yes\n";
		else cout << "No\n";
	}
}
```

---

## 作者：_119_Grenadier (赞：1)

#### 一道构造题
废话：刚开始想用暴力，但这数据范围太大了，估计过不了，所以来打正解了。
### 思路
1. 从样例解释中我们可以看出，当 $k$ 为偶数时，我们完全可以构造一个奇偶交替的序列，满足题目给出的条件，所以直接输出 Yes 就行了。
2. 而当 $k$ 为奇数时，我们就需要记录偶数和奇数的数量了，因为只有奇数和偶数的差不超过一，我们才能构造奇偶交替的序列。因此，我们要判断奇数和偶数的差，大于一就输出 No，不大于一就输出 Yes。
## 代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
inline long long read(){//快读。 
	long long x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
	return x*f;
}
int t,n,k; 
int main(){
	t=read();
	for(int i=0;i<t;i++){// t 组数据，也可以 while(t--)。 
		n=read();
		k=read();//输入两个整数。 
		if(k%2!=0){//当 k 为单数时。 
			if((k/2>=n%k&&(n/k-n%k)<=1)||(k/2<n%k&&(n/k-k/2+(n%k-k/2))<=1)){//奇数和偶数的差没超过一。 
				printf("Yes\n");//符合条件，输出 Yes。 
			}
		    else{//奇数和偶数的差超过了一。 
		    	printf("No\n");//不符合条件，输出 No。 
			} 
		}
		else{//当 k 为偶数时，直接输出 Yes。 
			printf("Yes\n");
		}
	} 
	return 0;//结束程序。 
}
```

---

## 作者：CNS_5t0_0r2 (赞：1)

首先，当 $k$ 为偶数时，肯定可以构造出。

不严谨的证明：

设构造出的排列为 $p_1,p_2,p_3 \dots p_n$，则第一个长度为 $k$ 的序列为 $p_1,p_2 \dots p_k$，第二个长度为 $k$ 的序列为 $p_2,p_3 \dots p_{k + 1}$。

如果两个序列的和的奇偶性要相同，因为两个序列中都有 $p_2,p_3 \dots p_k$，因此这两个序列的奇偶性如果相同，则 $p_1,p_{k + 1}$ 的奇偶性相同。

同理，对于任意 $i \leq n - k + 1$，都有 $p_i,p_{i + k}$ 的奇偶性相同。

因为 $k$ 为偶数，所以只要满足 $p_i = i$ 即可构造出。

当 $k$ 为奇数时，可知：

$p_{1 + qk}$（$q$ 为整数，$1 + qk \leq n$）奇偶性相同，

$p_{2 + qk}$ 奇偶性相同，

$\dots$

$p_{k - 1 + qk}$ 奇偶性相同。

可以推出，模 $k$ 等于 $1 \sim n \bmod k$ 的下标要比其它下标的数量多 $1$，且每一段中必然会有一种奇偶性的数多 $1$。因为重复了 $\lfloor \frac{n}{k}\rfloor$ 段，所以其中一种数肯定比另一种多 $\lfloor \frac{n}{k}\rfloor$ 个。在剩余多出来的 $n \bmod k$ 段中我们需要补齐这个差值。

因为其中较少的一种数最多为 $\lfloor \frac{k}{2}\rfloor$，如果补齐后有空位，则需另外讨论，即分 $n \bmod k \leq \lfloor \frac{k}{2}\rfloor$ 和 $n \bmod k > \lfloor \frac{k}{2}\rfloor$ 讨论。



---

## 作者：zhaohanwen (赞：1)

当 $k$ 为偶数时，序列奇偶交替。这样的序列一定存在，所以直接输出 `Yes`。

当 $k$ 为奇数时，每一段奇偶数数量一定相差 $1$。`num1` 表示长度为 $k$ 的子段中奇数值的个数。`num2` 表示长度为 $k$ 的子段中偶数值的个数。如果奇偶数的差值太大，那么排列就不存在。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define endl '\n'
#define ld long double
bool solve(int n,int k)
{
  if (k % 2 == 0) return true;
  int num1 = (n + 1) / 2 - (k + 1) / 2 * (n / k);
  int num2 = n / 2 - k / 2 * (n / k);
  if (num1 >= 0 and num1 <= (k + 1) / 2 and num2 >= 0 and num2 <= k / 2) return true;
  else return false;
}

int main()
{
ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
  int T;
  cin >> T;
  while (T--)
  {
  	int n,k;
  	cin>>n>>k;
    bool ans=solve(n,k);
    if(ans) cout<<"Yes"<<endl;
    else cout<<"No"<<endl; 
  }
  return 0;
}
```


---

## 作者：lgydkkyd (赞：1)

这题暴力应该是过不了的，因为数据还比较大的，有可能会超时，所以要用更优的算法。当长度为为偶数时，只需要构造奇偶交替的序列，这样每次整个区间向后移动时，最左边出去的元素和最右边进来的元素奇偶性是一样的要么同奇要么同偶，是一定存在符合题意的排列的，直接输出。当长度为奇数时，同样要想构造奇偶交替的序列，但一定会有一个数是多出来的，但只要奇数数量与偶数数量差的绝对值小于等于一依然可以构造奇偶交替的序列，多的那种数就从第一个数开始放，以尾结束，如果奇数和偶数的差没超过一则不存在符合题意的排列，因为无论怎么排出来的序列都无法做到，其中一个数出去就无法维持原来的奇偶性。
# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,k;
int main(){
	scanf("%d",&t);
	while(t--){//t组数据 
		scanf("%d%d",&n,&k);//输入n和k 
		if(k%2!=1){//当k为偶数时 
			printf("Yes\n");//千万别忘了换行输出Yes 
		}	
		else{//当k为奇数时
            if(k/2>=n%k&&(n/k-n%k)<2)printf("Yes\n");//满足条件输出Yes 
            else if(k/2<n%k&&(n/k-k/2+(n%k-k/2))<2)printf("Yes\n");//满足条件输出Yes
            else cout<<"No"<<endl;//不满足条件那就输出No 
		}
	}
	return 0;//华丽结束~~~ 
}
```

---

## 作者：SICKO (赞：0)

构造题。

给你一个序列区间和一个窗口，长度为 $n$ 与 $k$，要求构造一个序列使得其在窗口扫过序列时窗口内序列的值和的奇偶性保持一致，你只需要输出是否存在有效构造即可。

不难发现，如果一个窗口在扫描的过程要保证自身的奇偶性不变，唯一的要求是**扫描过程中得到的数与失去的数奇偶性相同**。

如果我们只观测序列的奇偶性，我们很容易发现，一个合法的构造前 $k$ 个序列是整个序列的循环节，而且最后一节可能会被截掉一点后缀，方便理解，我们把这一部分称为循环的多余部分。

对于长度为偶数的窗口，我们容易发现一定存在合法构造，只需奇偶交替即可。

对于长度为奇数的窗口，我们可以直接模拟这个构造过程。不难发现，在构造过程，我们只有两种情况：窗口奇数较多与窗口内偶数较多。所以我们会有两种构造方法：

- 窗口内奇数少，在多余的部分补回来。
- 窗口内偶数少，在多余的部分补回来。

所以我们直接根据循环节的数量以及多余部分的长度，对两种构造方法分类讨论即可。只要存在一种方案合法，就能说明存在合法解。

如何构造？我们发现，为使得尽可能有解，唯一的方法就是使得要补充的部分尽可能的短，而最短的情况就是循环节的数量。若是长度不足，直接用奇偶交替填满即可。

在这个过程，我们很容易发现两点要素：所使用的填充数的量不能超过区间要求，长度不足时，空缺量一定为偶数。

最后手模整个过程即可。

```c++
#include<iostream>
using namespace std;
int main(){
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int T; cin>>T;
    while(T--){
        int n, m; cin>>n>>m;
        if(m%2){
            int flat1 = 1;
            {
                int qjs=n/m, sys=n%m;
                int need = qjs+(n%2);
                if(sys<need) flat1 = 0;
                if((sys-need)%2) flat1=0;
                if((sys-need)/2+need>m/2) flat1=0;
            }
            int flat2 = 1;
            {
                int qjs=n/m, sys=n%m;
                int need = qjs-n%2;
                if(sys<need) flat2=0;
                if((sys-need)%2) flat2=0;
                if((sys-need)/2+need>m/2) flat2=0;
            }
            if(flat1||flat2) cout<<"Yes";
            else cout<<"No";
        }
        else cout<<"Yes";
        cout<<"\n";
    }
    return 0;
}
```

---

## 作者：Thorongil_Gondor (赞：0)

# 思路
分两种情况。
* 当 $k$ 为偶数，可以构造一个奇偶交替的序列，符合条件，输出 `Yes`。
* 当 $k$ 为奇数，统计奇数和偶数的数量。若其数量相差不超过 $1$，能构造奇偶交替的序列，符合条件，输出 `Yes`。否则输出 `No`。
# AC Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,k;
int main(){
	cin>>t;
	while(t--){//t组数据 
		cin>>n>>k;
		if(k%2==0)cout<<"Yes"<<endl;//k为偶数,符合条件。
		else{//k为奇数
			if((k/2>=n%k && (n/k-n%k)<=1) || (k/2<n%k && (n/k-k/2+(n%k-k/2))<=1))cout<<"Yes"<<endl;//奇数和偶数的差<=1。符合条件。 
		    else cout<<"No"<<endl;//奇数和偶数的差>1。不符合条件。 
		}
	}
	return 0;
}
```

---

