# Neko Performs Cat Furrier Transform

## 题目描述

Cat Furrier Transform is a popular algorithm among cat programmers to create longcats. As one of the greatest cat programmers ever exist, Neko wants to utilize this algorithm to create the perfect longcat.

Assume that we have a cat with a number $ x $ . A perfect longcat is a cat with a number equal $ 2^m - 1 $ for some non-negative integer $ m $ . For example, the numbers $ 0 $ , $ 1 $ , $ 3 $ , $ 7 $ , $ 15 $ and so on are suitable for the perfect longcats.

In the Cat Furrier Transform, the following operations can be performed on $ x $ :

- (Operation A): you select any non-negative integer $ n $ and replace $ x $ with $ x \oplus (2^n - 1) $ , with $ \oplus $ being a [bitwise XOR operator](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).
- (Operation B): replace $ x $ with $ x + 1 $ .

The first applied operation must be of type A, the second of type B, the third of type A again, and so on. Formally, if we number operations from one in the order they are executed, then odd-numbered operations must be of type A and the even-numbered operations must be of type B.

Neko wants to produce perfect longcats at industrial scale, thus for each cat Neko only wants to perform at most $ 40 $ operations. Can you help Neko writing a transformation plan?

Note that it is not required to minimize the number of operations. You just need to use no more than $ 40 $ operations.

## 说明/提示

In the first test, one of the transforms might be as follows: $ 39 \to 56 \to 57 \to 62 \to 63 $ . Or more precisely:

1. Pick $ n = 5 $ . $ x $ is transformed into $ 39 \oplus 31 $ , or $ 56 $ .
2. Increase $ x $ by $ 1 $ , changing its value to $ 57 $ .
3. Pick $ n = 3 $ . $ x $ is transformed into $ 57 \oplus 7 $ , or $ 62 $ .
4. Increase $ x $ by $ 1 $ , changing its value to $ 63 = 2^6 - 1 $ .

In the second and third test, the number already satisfies the goal requirement.

## 样例 #1

### 输入

```
39
```

### 输出

```
4
5 3 ```

## 样例 #2

### 输入

```
1
```

### 输出

```
0
```

## 样例 #3

### 输入

```
7
```

### 输出

```
0
```

# 题解

## 作者：王熙文 (赞：4)

upd at 2022.5.18: 原题意中没有要求最小，已在题解中修改。

## 题意

给出一个数 $n$。

有 $2$ 个操作：

* $1.$ 每次 $n$ 异或上 $2^k-1$，$k$ 为正整数。

* $2.$ $n \gets n+1$

请按 `12121...` 的顺序执行操作，使得最后的 $n=2^k-1$（$k$ 为正整数），并要输出每次 $1.$ 操作之后 $n$ 的值。注意：**没有要求操作最少**，在操作数 $\le 40$ 的情况下任意方案均可。

## 思路

**先来看 $1.$ 操作：**

将 $2^k-1$ 转成二进制后，发现这个数是 $\left(\begin{matrix}\underbrace{11 \cdots 1}\\k\end{matrix}\right)_2$。

异或的原理：$1 \oplus 1=0,0 \oplus 1=1$。 

那么 $n \oplus (2^k-1)$ 就相当于将二进制下 $n$ 的后 $k$ 位取反。

我们最后，是想方设法要把二进制下的 $n$ 每一位都变成 $1$。

考虑一种显而易见的贪心：每次 $1.$ 操作，找二进制下 $n$ 从高位到低位第一个 $0$，把这一位之后的所有数取反，也就是如果后面长度为 $k$，异或上 $2^k-1$。

但是这个贪心为什么是对的呢？因为，对于每一次的最高位 $0$，都不能用比它低位的数执行 $1.$ 操作，只能用位数大于等于它的数执行 $1.$ 操作。然而除了它，比它位数高的数都为 $1$，如果操作了，会使位数高的这个数取反变成 $0$。

**对于每个 $2.$ 操作，直接加上即可。**

## 代码

一些位运算技巧：

* 判断一个数是否为二的幂：如果为二的幂，这个数减一与上这个数，答案会为 0，因为如果这个数是 $2^k$，它的二进制为 `100...0`（$k$ 个 `0`），$2^k-1$ 的二进制为 `11...1`（$k$ 个 `1`），因为 $0\&1=0$，这两个数与上去会为 $0$。

* 求 $2^k$：$2^k=$ `1<<k`。

* 求二进制下 $x$ 的从低到高数第 $k$ 位（最低位为 `0`）：`(x>>k)&1`。

```cpp
#include<bits/stdc++.h>
using namespace std;

int ans[45];

int main()
{
	int n,t=0,k=0; // t 为从操作数，k 为 1. 操作总数
	cin>>n;
	while((n+1)&n) // 当 n=2^k-1 时 (n+1)&n=0
	{
		int i=30;
		while(n<(1<<i)) --i; // 求出最高位 i
		while((n>>i)&1) --i; // 当 位 i 为 1 时再往下找
		n^=(1<<i+1)-1; // 从 i~0 有 i+1 个数，要异或 2^(i+1)-1
		ans[++k]=i+1; // 加入答案数组
		++t; // 总操作数 ++
		if(!((n+1)&n)) break; // 如果执行了一次操作，变成了 2^k-1 时，跳出循环
		++n; // 执行 2. 操作，加上 n
		++t; // 总操作数 ++
	}
	cout<<t<<endl; // 输出总操作数
	for(int i=1; i<=k; ++i) cout<<ans[i]<<' '; // 输出答案数组
	return 0;
}
```

---

## 作者：mulberror (赞：2)

# 自己写的所有题解
[【传送门】](https://www.cnblogs.com/chhokmah/p/10768012.html)  
# 题目大意
给你一个数$x$，并给你两个操作$A$和$B$，要求操作$A$和$B$必须交替执行。  
操作$A$：给一个$2^k-1$异或当前$x$。  
操作$B$：将当前的数$+1$。  
让你在$40$步内完成以下的任务：让你把$x$变成$2^k-1$
# 题解
水题一道    
我们考虑贪心。  
首先需要了解操作$A$的本质。  
其实就是在二进制下异或一个$111\cdots1$的数。  
那么为了处理到所有的$0$变成$1$，那么我们需要考虑第一个$0$，也就是在二进制下最高位的$0$。  
比较明显的贪心策略就出现了，每一次我们异或掉最高位的$0$，然后$+1$。  
$10^{6}$很明显可以在$40$步以内完成，所以不存在无法完成的情况。

# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int x, n = 0, ans = 0, pos, cnt = 0;
int a[30], Ans[30];
bool fg;
int main() {
    cin >> x;
    for (; x; x >>= 1) a[++ n] = x % 2;
    for (int i = 1; i <= n; i ++) {
        fg = 1;
        for (int j = 1; j <= n; j ++) if (a[j] == 0) { fg = 0; break; }
        if (fg) break; 
        for (int j = n; j; j --) {
            if (a[j] == 0) { pos = j; break; }
        }
        for (int j = 1; j <= pos; j ++) a[j] ^= 1;
        Ans[++ cnt] = pos; ++ ans;
        fg = 1;
        for (int j = 1; j <= n; j ++) if (a[j] == 0) { fg = 0; break; }
        if (fg) break; 
        a[1] ++;
        for (int j = 1; j <= n; j ++) if (a[j] > 1) a[j] = 0, a[j + 1] ++; 
        ++ ans;
    }
    cout << ans << endl;
    for (int i = 1; i <= cnt; i ++) printf("%d ", Ans[i]);
    return 0;
}
```

---

## 作者：wcop114514 (赞：0)

**题目分析**

首先有两种方式改变数字 $n$。

第一种： $n$ 异或 $2^k - 1$。
第二种 $n+1$。
按照 $1212$ 的顺序操作使 $n=2^k - 1$。

计算方式：

我们发现 $2^k - 1$ 在二进制中每一位都是一，这里要用到贪心策略异或掉最高位的 $0$， 然后 $+1$。

给各位大佬奉上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int ans[45];
int n,num=0,k=0;
int i=30;
void solve(){
	
		while(n<(1<<i))
			i--;
		while((n>>i)&1)
			i--;
		n=n^(1<<i+1)-1;
		ans[++k]=i+1;
		num=num+1;
		return ;
}
int main(){
	cin>>n;
	while((n+1)&n){
		solve();
		if(!((n+1)&n)) break;
		n=n+1;
		num=num+1;
	}
	cout<<num<<endl;
	for(int i=1; i<=k;i++) cout<<ans[i]<<' ';
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

## 题目意思

输入一个 $n$，进行两种操作：

- 异或一个 $2^k-1$；
- 自增一。

按照
```121212```
的顺序运算，使最后结果是 $2^k-1$。

## 操作方法
不难发现，$2^k-1$ 在二进制中每一位都是 $1$，这里就涉及到了贪心算法，从最高位开始，依次把 $0$ 异或掉，再加一就可以完成了。

## 代码
```cpp
#include<iostream>//头文件
using namespace std;
int ans[45];
int main(){
	int n,t=0,k=0;//定义
	cin>>n;//输入
	while((n+1)&n){//循环运算，(n+1)&n不等于0是进入循环
		int i=30;
		while(n<(1<<i))
			i--;
		while((n>>i)&1)
			i--;
		n=n^(1<<i+1)-1;//执行操作1
		ans[++k]=i+1;//加入数组元素
		t++;//次数加一
		if(!((n+1)&n)) break;//达到效果跳出循环
		n++;//执行操作2
		t++;//次数+1
	}
	cout<<t<<endl;
	for(int i=1; i<=k;i++) cout<<ans[i]<<' ';//输出
	return 0;//结束了
}
```

---

## 作者：Fa1thful (赞：0)

### 1.题意
给定一个数 $n$，给你两种操作 ：  
1. $n=n⊕(2^k-1)$ 
2. $n+1$

求将 $n$ 变为 $2^k-1$ 要多少步，并且对于 1 操作需要输出每次 $k$ 的值。操作顺序为：12121212......

### 2.分析
首先我们来重点分析操作 1，我们发现所有的 $2^k-1$ 在二进制下每一位都是 $1$。所以现在我们只剩下异或没有解决了。异或的运算法则就是在二进制里，相同的位上的数不同为 $1$，相同为 $0$。因为 $n$ 异或的数的每一位全是 $1$。而且题目要我们求的东西是 $2^k-1$。这个数的二进制每一位也都是 $1$，所以我们要达成这个目的就必须让一次异或得尽量多，将更多的 $0$ 变成 $1$。又因为异或的数的每一位都是 $1$，所以我们每次从 $n$ 当前的值的二进制的第一个 $0$ 开始，因为这个 $0$ 前面肯定没有更多的 $0$ 了，所以一次变出的 $1$ 肯定是最多的。  
那么剩下的 $1$ 变成了 $0$ 怎么办呢？  
其实不用担心这个问题，因为就算你不把最高位的 $0$ 变成 $1$，你到了后面还是要用 $+1$ 的操作慢慢地将它变成 $1$ (因为最后的目标是二进制全变为 $1$)，这样反而会更费次数。

所以现在我们来用这个方法模拟一下样例，再次检测一下咱们的方法正不正确：  
首先 $39$ 转成二进制是这样的，$100111$  
然后我们进行第一次异或操作 $111000$，此时 $k=5$   
然后 $+1$，$111001$  
再异或，$111110$ 此时 $k=3$  
最后 $+1$，$111111$ 成功！

既然思路有了，接下来就是代码实现了。

### 3.代码实现
```cpp
# include <bits/stdc++.h>
using namespace std;
bool erjinzhi[1000000];     //用来存每次n的二进制 
bool s[1000000];    //将二进制倒过来 
int ans[100];   //储存每次异或操作的k 
int tme = 0;   //见check函数 
bool check(int x)
{
	int rmp = 1;
	while (rmp <= 10000000)
	{
		if (x == rmp) return true;
		rmp *= 2;
		tme++;
	}
	return false;
}
int main()
{
	int n;
	cin >> n; //输入 
	int tmp = 1;  //记录操作次数 
	int poo = 1; //记录多少次异或操作，便于输出ans数组 
	for (int jj = 1; jj <= 41; jj++)   //最多40次操作 
	{
		memset(erjinzhi, 0, sizeof(erjinzhi));  //每次算二进制前清零 
		memset(s, 0, sizeof(s));
		int p = 1;     //二进制数组下标 
		int tishen = n;   //动态模拟改变n 
		while (1)     //十进制转二进制 
		{
			if (tishen / 2 > 0)
			{
				erjinzhi[p] = tishen % 2;
				tishen /= 2;
				p++;
				continue;
			}
			else if (tishen > 0)
			{
				erjinzhi[p] = tishen % 2;
				tishen /= 2;
				p++;
				continue;
			}
			break;
		}
		int m = 1;
		for (int i = p - 1; i >= 1; i--)     //将倒着存的二进制正过来 
		{
			s[m] = erjinzhi[i];
			m++;
		}
		int pos = 0;
		for (int i = 1; i < m; i++)  //寻找第一个0 
		{
			if (s[i] == 0)
			{
				pos = i;
				break;
			}
		}
		if (pos == 0) break; //如果发现达成全为1的情况，即完成了 
		int k = m - pos;     //计算k，异或到0这一位 
		if (check(n + 1)) break;   //如果满足就不需要再进行操作了 
		n ^= (1 << k) - 1;  //进行异或操作 
		ans[poo] = k;  //记录k 
		poo++;
		tmp++;  //增加次数 
		if (check(n + 1))     //如果不需要++了 
		{
			break;
		}
		n++;  //操作2 
		tmp++;
		if (check(n + 1))   //如果不要进行下一次异或了 
		{
			break;
		}
	}
	tmp--;      //因为退出的时候发现tmp多加了下一步不必要的操作 
	cout << tmp << endl;
	for (int i = 1; i < poo; i++)
	{
		cout << ans[i] << " ";
	}
	cout << endl;
	return 0;
}
```
谢谢观赏

---

## 作者：ljc20020730 (赞：0)

事实上A操作的意图是将数字的末若干位取反。B操作含义是将数最后一位+1，并且进位。

考虑一个贪心，如果每次取将第一个0出现的位置往低位取反，然后最后在末尾+1，那么每次至少消去第一个0出现的位置的一个0

所以必然2步就可以至少删去1个0，那么显然可以在40步内完成任务。

　　本题主要需要注意，操作步数不一定是偶数，可能最后的B操作不做，操作步数是奇数的，需要特判。
  
  ```
  # include <bits/stdc++.h>
using namespace std;
int base[25];
int ttt[100];
int getbit(int x)
{
    int t=x,cnt=0;
    while (t) t/=2,cnt++;
    return cnt;
}
bool check(int x)
{
    for (int i=0;i<=20;i++)
     if (x==base[i]) return 1;
    return 0;
}
int main()
{
    int uuu=0;
    int x,ans=0; scanf("%d",&x);
    for (int i=0;i<=20;i++) base[i]=(1<<i)-1;
    if (check(x)) {
        puts("0"); return 0;
    }
    while (true) {
        int p=getbit(x);
        bool flag=false;
        for (int i=p-2;i>=0;i--)
         if (((1<<i)&x)==0) {
             x=x^((1<<(i+1))-1); ttt[++ttt[0]]=i+1; uuu++;
            if (check(x)) flag=true; 
            if (flag) break;
            x=x+1; uuu++;
             if (check(x)) flag=true; 
            if (flag) break;
             break;
         }
        if (flag) break;
    }
    printf("%d\n",uuu);
    for (int i=1;i<=ttt[0];i++)
     printf("%d ",ttt[i]);
    return 0;
}
  ```

---

