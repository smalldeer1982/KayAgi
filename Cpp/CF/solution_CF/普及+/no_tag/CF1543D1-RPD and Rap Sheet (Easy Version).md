# RPD and Rap Sheet (Easy Version)

## 题目描述

This is the easy version of the problem. The only difference is that here $ k=2 $ . You can make hacks only if both the versions of the problem are solved.

This is an interactive problem.

Every decimal number has a base $ k $ equivalent. The individual digits of a base $ k $ number are called $ k $ -its. Let's define the $ k $ -itwise XOR of two $ k $ -its $ a $ and $ b $ as $ (a + b)\bmod k $ .

The $ k $ -itwise XOR of two base $ k $ numbers is equal to the new number formed by taking the $ k $ -itwise XOR of their corresponding $ k $ -its. The $ k $ -itwise XOR of two decimal numbers $ a $ and $ b $ is denoted by $ a\oplus_{k} b $ and is equal to the decimal representation of the $ k $ -itwise XOR of the base $ k $ representations of $ a $ and $ b $ . All further numbers used in the statement below are in decimal unless specified. When $ k = 2 $ (it is always true in this version), the $ k $ -itwise XOR is the same as the [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

You have hacked the criminal database of Rockport Police Department (RPD), also known as the Rap Sheet. But in order to access it, you require a password. You don't know it, but you are quite sure that it lies between $ 0 $ and $ n-1 $ inclusive. So, you have decided to guess it. Luckily, you can try at most $ n $ times without being blocked by the system. But the system is adaptive. Each time you make an incorrect guess, it changes the password. Specifically, if the password before the guess was $ x $ , and you guess a different number $ y $ , then the system changes the password to a number $ z $ such that $ x\oplus_{k} z=y $ . Guess the password and break into the system.

## 说明/提示

In the example test case, the hidden password is $ 2 $ .

The first query is $ 3 $ . It is not equal to the current password. So, $ 0 $ is returned, and the password is changed to $ 1 $ since $ 2\oplus_2 1=3 $ .

The second query is $ 4 $ . It is not equal to the current password. So, $ 0 $ is returned, and the password is changed to $ 5 $ since $ 1\oplus_2 5=4 $ .

The third query is $ 5 $ . It is equal to the current password. So, $ 1 $ is returned, and the job is done.

Note that this initial password is taken just for the sake of explanation. When you submit, the interactor might behave differently because it is adaptive.

## 样例 #1

### 输入

```
1
5 2

0

0

1```

### 输出

```
3

4

5```

# 题解

## 作者：Evier (赞：5)

## 题意
你要猜一个数 $x$ ，且 $0\le x < n$ 。特别地，设一次交互猜的数为 $y$ ，若 $y \ne x$ 则 $x$ 变为 $z$ ，其中 $x \oplus z=y$ 。你需要在 $n$ 次交互内猜出 $x$ 。
## 题解
首先容易得出 ：

$x \oplus z=y 
\Longrightarrow x \oplus y = z$

所以我们可以想一种方法让前面的询问不会对现在的询问产生影响。

我们可以考虑顺序枚举 $1$ 到 $n$ ，每次输出$i \oplus (i-1)$，当询问到第$i$次时原先的$x$变为：

$x \oplus (0 \oplus 1) \oplus (1 \oplus 2) \cdots \oplus ((i-1) \oplus i)$ 

根据异或运算的结合律化为：

$x \oplus 0 \oplus (1 \oplus 1) \oplus (2 \oplus 2) \cdots \oplus ((i-1) \oplus (i-1)) \oplus i$

$\because x \oplus 0 = x$  and  $x \oplus x =0$

$\therefore$ 原式 $= x \oplus i$

当 $x=i+1$ 时会在枚举到 $i+1$ 时猜中。主要就是一个转换和抵消的想法，还是不难想的。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int T,n,k;
int main(){
	cin>>T;
	while(T--){
		cin>>n>>k;
		int re,x=0;
		cout<<"0"<<endl;
		cin>>re;
		if(re==0){
			for(int i=1;i<=n;i++){
				cout<<(x^i)<<endl;
				x=i;
				cin>>re;
				if(re==1)break;
			}
		}
	}
}
```

---

## 作者：DaiRuiChen007 (赞：0)

# CF1543D1 题解



## 思路分析

先假设每次操作完不改变 $x$ 值，显然由于询问次数有 $n$ 次，因此每次我们询问 $0\sim n-1$ 即可。

那么在改变 $x$ 值的情况下，我们对于第 $i$ 次询问，只要询问在 $x$ 最初为 $i$ 的情况下经过若干次修改后得到的值即可。

注意到每次询问 $q$ 实际上就是让 $x$ 变成 $x\oplus q$，因此维护所有询问的 $q$ 的异或和即可。

时间复杂度 $\Theta(n)$。

## 代码呈现

```cpp
#include<bits/stdc++.h>
using namespace std;
inline bool read(int n) {
	cout<<n<<endl;
	int ret; cin>>ret; return ret;
}
inline void solve() {
	int n,k;
	cin>>n>>k;
	for(int i=0,q=0;i<n;++i) {
		if(read(q^i)) return ;
		else q^=q^i;
	}
}
signed main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```



---

## 作者：_lgh_ (赞：0)

# 思路：
根据异或的性质，
第一次猜 $0$ ，第二次猜 $1$ 异或 $0$ ，第三次猜 $2$ 异或 $1$ ……一直猜到 $n-1$ 异或 $n-2$，在这过程中必然有一次是猜对的。

证明如下：

设初始密码为 $x$ ，假设现在猜的是 $i$ 异或 $i-1$ ，那么初始密码已经被更改成了 $x \oplus 0\oplus 1 \oplus 0\oplus 2 \oplus 1 \oplus 3 \oplus 2 \oplus(i-1)\oplus (i-2)\oplus i\oplus(i-1)=x \oplus i$ 
当 $i=x-1$ 时，必然猜对。

如果 $x=0$ ，就是第一次就猜对，需要特判一下。
# 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
  int T,n,k,x;
  scanf("%d",&T);//输入
  while(T--)
  {
    scanf("%d%d",&n,&k);//输入
    for(int i=0; i<n; ++i)//枚举
    {
      if(!i) printf("0\n");
      else printf("%d\n",i^(i-1));//直接猜
      cout.flush();//不加这一行会UKE
      scanf("%d",&x);
      if(x==1) break;
    }
  }
}
```


---

