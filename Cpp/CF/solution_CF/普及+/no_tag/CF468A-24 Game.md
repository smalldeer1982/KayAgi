# 24 Game

## 题目描述

Little X used to play a card game called "24 Game", but recently he has found it too easy. So he invented a new game.

Initially you have a sequence of $ n $ integers: $ 1,2,...,n $ . In a single step, you can pick two of them, let's denote them $ a $ and $ b $ , erase them from the sequence, and append to the sequence either $ a+b $ , or $ a-b $ , or $ a×b $ .

After $ n-1 $ steps there is only one number left. Can you make this number equal to $ 24 $ ?

## 样例 #1

### 输入

```
1
```

### 输出

```
NO
```

## 样例 #2

### 输入

```
8
```

### 输出

```
YES
8 * 7 = 56
6 * 5 = 30
3 - 4 = -1
1 - 2 = -1
30 - -1 = 31
56 - 31 = 25
25 + -1 = 24
```

# 题解

## 作者：ftcly (赞：8)

思路:开始想用深搜，在乱算时发现有规律可找

1.   3及以下最大到不了24，直接输出NO；

1.   只要是算出24，如果后面有偶数个数就可以全部抵消；

1.   只要分奇偶算出n=4，n=5的情况，后面就可以输出了；

**注意** ： 要打空格！！

详见代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin>>n;//输入 
    if(n<4)//4以下直接输出NO
    {
        cout<<"NO"<<endl;
        return 0;
    }
    else//其他n取值一定能过
    cout<<"YES"<<endl;
    if (n%2){		//偶数情况
    cout<<" 3 * 5 = 15"<<endl<<"2 * 4 = 8"<<endl<<"15 + 8 = 23"<<endl<<"23 + 1 = 24"<<endl;//先算出24
    for (int i=n;i>=6;i-=2) 
        cout<<i<<" - "<<i-1<<" = 1"<<endl<<"24 * 1 = 24"<<endl;//每次用第i个和第i-1个数维持24
    }
    else{		//奇数
    cout<<"1 + 2 = 3"<<endl<<"3 + 3 = 6"<<endl<<"4 * 6 = 24"<<endl;
    for (int i=n;i>=5;i-=2) 
        cout<<i<<" - "<<i-1<<" = 1"<<endl<<"24 * 1 = 24"<<endl;  //同上
    }
    return 0;
}   
```                   
~~同机房大佬说dfs也可以过，本蒟蒻一点思路都没有~~

---

## 作者：wmrqwq (赞：6)

# 原题链接

[CF468A 24 Game](https://www.luogu.com.cn/problem/CF468A)

# 题目简述

现在有一个序列 $n$ 包含 $n$ 个整数 $1 \sim n$，如果我们能经过加减乘三种操作让这个序列只剩下 $24$，如果可以，输出 ```YES``` 并给出构造方案，否则输出 ```NO```。

# 解题思路

首先不难看出，如果 $n$ 小于 $4$ 的话，那么是一定不能构造出方案的，因为无论你怎么操作，结果都不可能大于 $24$，但是当 $n$ 大于等于 $4$ 的时候，那么是一定能构造出方案的，证明如下：

1. 如果 $n$ 为奇数，那么只需要用 $1 \sim 5$ 凑出 $24$，然后再把剩下没操作过的相邻的数依次相减，再与 $24$ 相乘即可；
2. 如果 $n$ 为偶数，那么只需要用 $1 \sim 4$ 凑出 $24$，然后再把剩下没操作过的相邻的数依次相减，再与 $24$ 相乘即可。

以下是 $1 \sim 4$ 和 $1 \sim 5$ 凑 $24$ 点的方法：

$1 \sim 4$：

```cpp
1*2=2 2*3=6 6*4=24
```

$1 \sim 5$：

```cpp
2*4=8 3*5=15 15+8=23 23+1=24
```

# 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define QwQ return 0;
long long n;
int main()
{
	cin>>n;
	if(n<=3)//如果n小于4
	{
		cout<<"NO";//直接输出NO
		return 0;
	}
	else//如果n大于等于4
	{
		cout<<"YES"<<endl;//输出YES
		if(n%2)//如果n为奇数
		{
			cout<<"2 * 4 = 8"<<endl<<"3 * 5 = 15"<<endl<<"15 + 8 = 23"<<endl<<"23 + 1 = 24"<<endl;
			for(int i=n;i>5;i-=2)//将剩下的数依次相减
				cout<<i<<" - "<<i-1<<" = "<<"1"<<endl<<"24 * 1 = 24"<<endl;			
		}
		else//如果n为偶数
		{
			cout<<"1 * 2 = 2"<<endl<<"2 * 3 = 6"<<endl<<"4 * 6 = 24"<<endl;
			for(int i=n;i>4;i-=2)//将剩下的数依次相减
				cout<<i<<" - "<<i-1<<" = "<<"1"<<endl<<"24 * 1 = 24"<<endl;
		}
	}
	QwQ;
}

```


---

## 作者：嫐嬲巭孬 (赞：3)

思路：通过爆搜得知，$n<4$ 以下的无解，偶数就可以用前四个数相乘 $=24$ 再用 $24=(i-(i-1))\times24$ 其中 $4<i<=n$，来抵消后面一大串。奇数，先用倒数第 $2$ 个数到倒数第 $5$ 个数算出一个 $0$，用 $n$ 乘它，后面 $5$ 个数就被抵消，就用偶数的方法做。

但注意，$n=7$ 和 $n=5$ 时不适用这种方法，因为 $n-5<4$。

还有，奇数转到偶数时，少了一步，交上去结果可想而知。

#### 上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;cin>>n;
	if(n<=3)return cout<<"NO",0;
	cout<<"YES"<<endl;
	if(n==5||n==7)cout<<"5 * 4 = 20"<<endl<<"20 + 3 = 23"<<endl<<"23 + 2 = 25"<<endl<<"25 - 1 = 24"<<endl;
	if(n==7)cout<<"7 - 6 = 1"<<endl<<"24 * 1 = 24"<<endl;
	if(n==5||n==7)return 0;
	if(n%2){
		cout<<n-1<<" - "<<n-2<<" = "<<1<<endl;
		cout<<n-4<<" - "<<n-3<<" = "<<-1<<endl;
		cout<<"1 + -1 = 0"<<endl;
		cout<<n<<" * 0 = 0"<<endl;//抵消后5个数
		cout<<"0 + 1 = 1"<<endl;//注意这句，我之前没加，wa了，血的教训
		n-=5; 
	}
	if(n%2==0){
		cout<<"1 * 2 = 2"<<endl<<"2 * 3 = 6"<<endl<<"6 * 4 = 24"<<endl;
		for(int i=n;i>4;i-=2){
			cout<<i<<" - "<<i-1<<" = 1"<<endl;//凑一
		}
		for(int i=(n/2-2);i>0;i--){
			cout<<"24 * 1 = 24"<<endl;//乘起来
		}
	}
	
}
```


---

## 作者：lianchanghua (赞：3)

感谢 @[I_like_magic_200911](https://www.luogu.com.cn/user/778235) 帮忙修改 Markdown 和 $\LaTeX$

---

我们先在纸上模拟一遍，可以发现：

- 如果 $n<4$，那么便是无解。

- 在 $n>4$ 的情况下，可以发现一套通法：
    
>	在 $n$ 为奇数时，方法如下：
> 
>	$5 \times 4 = 20$
>
>	$20 + 3 = 23$
>
>   $23 + 2 = 25$
>
>	$25 - 1 = 24$
>
>	最后，不停地乘 $1$ 即可；
        
------------

>	在 $n$ 为偶数时，方法如下： 
>
>	$1 \times 2 = 2$  
>
>	$2 \times 3 = 6$	
>
>	$4 \times 6 = 24$
>
>	最后，不停地乘 $1$ 即可。
      
------------

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
signed main(){
    int n;
    cin>>n;  
	if(n<4){//4以下无解 
		cout<<"NO";
		exit(0);
	}
    cout<<"YES"<<"\n";
    if(n%2){//判断奇偶
    	//奇数情况 
    	cout<<"5 * 4 = 20"<<"\n";
		cout<<"20 + 3 = 23"<<"\n";
		cout<<"23 + 2 = 25"<<"\n";
		cout<<"25 - 1 = 24"<<"\n";
		for(int i=n;i>=6;i-=2){
			cout<<i<<" - "<<i-1<<" = "<<"1"<<"\n";
			cout<<"24 * 1 = 24"<<"\n";
		}
	}
    else{
    	//偶数情况 
		cout<<"1 * 2 = 2"<<"\n";
		cout<<"2 * 3 = 6"<<"\n";
		cout<<"4 * 6 = 24"<<"\n";
		for(int i=n;i>=5;i-=2){
			cout<<i<<" - "<<i-1<<" = "<<"1"<<"\n";
			cout<<"24 * 1 = 24"<<"\n";
		}
    }
    return 0;
}
```
$2023.7.19$ 修改注释，感谢@[Tjaweiof](https://www.luogu.com.cn/user/550933)

$2023.7.24$ 修改解释，感谢@[Soul_Seeker](https://www.luogu.com.cn/user/947270)

---

## 作者：dyc2022 (赞：2)

一道**规律题**。

- 如果 $n \le 3$，那么不存在一个解，使得结果等于 $24$。

对于 $1$，就只有一个数字，这个数字不是 $24$，就没有解。

对于 $2$，最大的解显然是 $1 + 2 = 3$，根本无法达到 $24$，因此无解。

对于 $3$，最大的解显然是当 $n = 2$ 时的最大结果再乘以 $3$。最后得到 $(1 + 2) \times 3 = 9$，$9 < 24$，无解。

- 对于 $n > 3$ 的情况，那么如果用暴力法，那么需要牺牲巨大的复杂度。我们又发现相邻两个数字的差一定是 $1$，所以我们如果找到了一个规模较小的通解令其结果等于 $24$，然后把这个 $24$ 不断乘以 $i - (i - 1)$，最后结果也是 $24$。

但由于相邻的两个数才能得到 $1$，所以我们还要根据 $n$ 对于 $2$ 的整除性进行分类讨论，也就是需要得到两个通解，使这两个通解中参与运算的数字个数一个为奇数，一个为偶数。

1. 当 $n \bmod 2 = 1$ 时，给出以下的一组通解，

```
4 * 5 = 20
20 + 3 = 23
23 + 2 = 25
25 - 1 = 24
```

然后在后面接上：

```
7 - 6 = 1
24 * 1 = 24
9 - 8 = 1
24 * 1 = 24
...
n - (n-1) = 1
24 * 1 = 24
```

2. 当 $n \bmod 2 = 0$ 时，给出以下的一组通解，

```
1 * 2 = 2
2 * 3 = 6
6 * 4 = 24
```

然后在后面接上：

```
6 - 5 = 1
24 * 1 = 24
8 - 7 = 1
24 * 1 = 24
...
n - (n-1) = 1
24 * 1 = 24
```

***

[AC](https://www.luogu.com.cn/record/116122647) 代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
main()
{
	scanf("%d",&n);
	if(n<=3)return puts("NO"),0;
	if(n&1)
	{
		printf("YES\n4 * 5 = 20\n20 + 3 = 23\n23 + 2 = 25\n25 - 1 = 24\n");
		for(int i=6;i<=n-1;i+=2)
			printf("%d - %d = 1\n24 * 1 = 24\n",i+1,i);
	}
	else
	{
		printf("YES\n1 * 2 = 2\n2 * 3 = 6\n6 * 4 = 24\n");
		for(int i=5;i<=n-1;i+=2)
			printf("%d - %d = 1\n24 * 1 = 24\n",i+1,i);
	}
	return 0;
}
```

---

## 作者：开始新的记忆 (赞：2)

思路：不难发现，当n达到了一定的量时会有一种通解（其实4就可以了，但是我比较傻，打表到7才发现，于是就写了）


```cpp
#include<algorithm>
#include<iostream>
#include<stdio.h>
#include<math.h>
#include<string>

using namespace std;

int main()
{   int n;
    cin>>n;
    if(n<=3)
        printf("NO");
    else
    {
    	printf("YES\n");
        if(n==4)
            printf("1 * 2 = 2\n2 * 3 = 6\n4 * 6 = 24\n");
        else if(n==5)
            printf("3 * 4 = 12\n5 - 2 = 3\n3 - 1 = 2\n12 * 2 = 24\n");
        else if(n==6)
            printf("4 * 6 = 24\n1 + 2 = 3\n3 + 3 = 6\n6 - 5 = 1\n24 * 1 = 24\n");
        else if(n==7)
            printf("6 - 2 = 4\n1 + 4 = 5\n5 + 3 = 8\n8 + 4 = 12\n12 + 5 = 17\n17 + 7 = 24");
        else if(n%2==0)
        {
        	printf("3 * 8 = 24\n7 - 6 = 1\n5 - 4 = 1\n2 - 1 = 1\n");
        	for(int i=9;i<=n;i+=2)
        	    printf("%d - %d = 1\n",i+1,i);
        	for(int i=6+(n-8)/2;i<n;i++)
        	    printf("1 * 1 = 1\n");
        	printf("1 * 24 = 24\n");
		}
		else
		{
			printf("3 * 8 = 24\n4 - 2 = 2\n6 - 5 = 1\n9 - 7 = 2\n2 - 2 = 0\n1 + 0 = 1\n");
			for(int i=10;i<=n;i+=2)
        	    printf("%d - %d = 1\n",i+1,i);
        	for(int i=8+(n-9)/2;i<n;i++)
        	    printf("1 * 1 = 1\n");
        	printf("1 * 24 = 24\n");
		}
    }
    return 0;
}
```


---

## 作者：a1_1 (赞：2)

### CF468A 【24 Game】
~~此题不难~~，直接上码:
 ```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,m,j,k,l,i,o,p;
    cin>>n;  
    if (n<4) {cout<<"NO"<<endl;return 0;}
    cout<<"YES"<<endl;
    if (n%2) cout<<"5 * 4 = 20"<<endl<<"20 + 3 = 23"<<endl<<"23 + 2 = 25"<<endl<<"25 - 1 = 24"<<endl,l=1;
	else cout<<"1 * 2 = 2"<<endl<<"2 * 3 = 6"<<endl<<"4 * 6 = 24"<<endl,l=0;
	for (i=n;i>=5+l;i-=2) cout<<i<<" - "<<i-1<<" = 1"<<endl<<"24 * 1 = 24"<<endl;  
}
```
还是解释一下吧:
```
相邻两数差为1！
如果数列中数的个数是奇数，那么就要想办法使它变为偶数，所以先算1、2、3、4、5，得24，然后n-(n-1)=1,
24*1=24。如果是偶数就先算1、2、3、4，之后和奇数一样输出，这题就AC了。但时间会比其他算法长，快输或许可以加快。
```
 _~~但这么水我还是WA了两次，因为没加空格和"YES"~~_ 

---

## 作者：Tjaweiof (赞：1)

# CF468A 题解——Tjaweiof

这题是铁铁的找规律题，$n$ 可以从 $1$ 开始找规律：
### $n<4$
最大 $(1+2)\times3=9$，输出 `NO`。
### $n=4$
$(1+2+3)\times4=24$，成立。
### $n=5$
$5\times4+3+2-1=24$，成立。

现在我们算是已经离答案很近了，因为 $4$ 和 $5$ 知道怎么做了，那么每次只需要 $\times 1$ 就 **万事大吉** 了。
## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
int main(){
	std::ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> n;
	if (n < 4){
		cout << "NO";
	} else if (n % 2){
		cout << "YES\n5 * 4 = 20\n20 + 3 = 23\n23 + 2 = 25\n25 - 1 = 24\n";
		for (int i = n; i >= 6; i -= 2){
			cout << i << " - " << i - 1 <<" = 1\n24 * 1 = 24\n";
		}
	} else {
		cout << "YES\n1 + 2 = 3\n3 + 3 = 6\n4 * 6 = 24\n";
		for (int i = n; i >= 5; i -= 2){
			cout << i << " - " << i - 1 << " = 1\n24 * 1 = 24\n";
		}
	}
	return 0;
}

```
#### 此代码时间复杂度 $O(n\div2)$，空间复杂度 $O(1)$，完美过关！

---

## 作者：XiaoX (赞：1)

CF的娱乐题。。。
（思路借鉴网上）
看起来没法做，搜索？T飞了
注意到比如8,9,10,11；
8+11-9+10=0所以其实后面没用
直接看代码：
```
#include<cstdio>
#include<iostream>
using namespace std;
int n;
int main()
{
	scanf("%d",&n);
	if (n<4){printf("NO\n");return 0;}
	int s;
	//4~7打表 
	if(n%4==0)
		printf("YES\n1 * 2 = 2\n2 * 3 = 6\n6 * 4 = 24\n"),s=n-4;
	else if (n%4==1)
		printf("YES\n4 * 5 = 20\n20 + 2 = 22\n22 + 3 = 25\n25 - 1 = 24\n"),s=n-5;
	else if (n%4==2)
		printf("YES\n5 * 6 = 30\n30 - 4 = 26\n26 - 3 = 23\n23 - 1 = 22\n22 + 2 = 24\n"),s=n-6;
	else if (n%4==3)
		printf("YES\n7 + 6 = 13\n13 + 5 = 18\n18 + 4 = 22\n22 + 3 = 25\n25 - 2 = 23\n23 + 1 = 24\n"),s=n-7;
	for(int j=n-s+1;j<=n;j+=2)
	  printf("%d - %d = 1\n",j+1,j);
	for (int j=1;j<=s/4;j++)
	  printf("1 - 1 = 0\n");
	for (int j=1;j<=s/4;j++)
	  printf("24 + 0 = 24\n");
	//剩下都消掉。。。。。。 
}
```

---

## 作者：linxuanrui (赞：0)

### 思路

我的思路好像跟各位大佬的思路不一样……

首先，发现**任意的连续四个数都可以凑成 $0$**。接下来，就可以考虑 $n$ 除以 $4$ 的余数。

1. $n\bmod 4=0$

先用前四个数凑出 $24$，再用剩下的数抵消成 $0$ 即可。

2. $n\bmod 4=1$

当 $n=1$ 时，肯定无解。

否则先用 $1\sim5$ 凑成 $24$，再用剩下的数抵消成 $0$。

当 $n\bmod 2,3$ 的时候也差不多，先用前面几个数凑成 $24$，在抵消掉后面。

注意一下特判就好了。

### 代码

```cpp
#include<bits/stdc++.h>
#define endl '\n'
typedef long long ll;
using namespace std;
ll n,a[25];
//抵消函数
void print(int x){for(int i = x;i <= n;i += 4)cout << "24 + " << i << " = " << 24 + i << "\n" << 24 + i << " - " << i + 1 << " = " << 23 << "\n23 - " << i + 2 << " = " << 21 - i << "\n" << 21 - i << " + " << i + 3 << " = " << "24\n";}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	if(n % 4 == 0){
		cout << "YES\n1 * 2 = 2\n2 * 3 = 6\n6 * 4 = 24\n",print(5);
	}else if(n % 4 == 1){
		if(n == 1)return cout << "NO",0;
		else cout << "YES\n4 + 5 = 9\n9 - 2 = 7\n7 + 1 = 8\n8 * 3 = 24\n",print(6);
	}else if(n % 4 == 2){
		if(n == 2)cout << "NO"; 
		else cout << "YES\n2 * 3 = 6\n1 + 5 = 6\n6 + 6 = 12\n12 - 6 = 6\n4 * 6 = 24\n",print(7);
	}else{
		if(n == 3)cout << "NO";
		else cout << "YES\n1 + 6 = 7\n7 + 5 = 12\n12 + 3 = 15\n15 + 4 = 19\n19 - 7 = 12\n12 * 2 = 24\n",print(8);
	}
}
```

---

## 作者：lmy_2011 (赞：0)

### 暴力思路
一开始拿到这道题，认为明显是一个搜索题，于是马上想到了深度优先搜索。首先，以 $24$ 往 $1$ 推，将遍历后的所有可能与 $n$ 做对比，看是否相等。
### 正解思路
当我仔细再看了一下题目时，发现其实 $1$、$2$、$3$ 三个数最大只能是 $1+2\times 3=7$ 肯定到不了 $24$。就不用考虑，直接输出 $\mathtt{NO}$。

在 $4\leq n$ 时，我们再分类讨论，分以下两种：

- $n$ 为偶数时，我们只需将前面 $4$ 个数：$1$、$2$、$3$、$4$ 相乘，得出结果 $24$，再将剩下的 $n-4$ 个数，相邻两个数为一组，然后将每一组中大的数减去小的数，得到答案 $1$（因为相邻），再将前面算出的 $24$ 依次 $\times 1$，得到答案。

- $n$ 为奇数时，我们再用套路，将前面的 $5$ 个数手算，算出了 $1+2\times 4+3\times 5=24$。之后再用偶数后面的算法去套奇数即可。



---

## 作者：AzureMist (赞：0)

其实这题没大家想象的那么难，在 $n<4$ 的时候肯定无解，直接输出 $\texttt{NO}$.如果 $n\ge4$，就先凑出 $24$，再用相邻的两个数制造出 $1$ 以维持这个 $24$。

AC Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	cin>>n;
	if(n<4) cout<<"NO";
	else
	{
		cout<<"YES"<<endl;
		if(n%2==0)
		{
			cout<<"1 * 2 = 2"<<endl;
			cout<<"2 * 3 = 6"<<endl;
			cout<<"6 * 4 = 24"<<endl;//n为偶数时用1~4算出24
			for(int i=5;i<=n-1;i+=2)
			{
				cout<<i+1<<" - "<<i<<" = 1"<<endl;
				cout<<"24 * 1 = 24"<<endl;
			}
		}
		else
		{
			cout<<"5 * 4 = 20"<<endl;
			cout<<"20 + 3 = 23"<<endl;
			cout<<"23 + 2 = 25"<<endl;
			cout<<"25 - 1 = 24"<<endl;//n为奇数时用1~5算出24
			for(int i=6;i<=n-1;i+=2)
			{
				cout<<i+1<<" - "<<i<<" = 1"<<endl;
				cout<<"24 * 1 = 24"<<endl;
			}
		}
	} 
	return 0;
}
```

---

## 作者：Sky_exe (赞：0)

~~看似要搜索……~~

但是!

可以打表找规律。

分类讨论一下：

$ n \le 3 $ 时是无法做到的。

特判一下直接输出"NO"。

```cpp
if(n<=3)
{
	cout<<"NO"<<endl;
	return 0;
}
```

$n = 4$ 时可以这样安排:

$ 1 \times 2 = 2 $

$ 2 \times 3 = 6 $

$ 6 \times 4 = 24 $

```cpp
if(n == 4)
{
	cout<<"1 * 2 = 2"<<endl;
	cout<<"2 * 3 = 6"<<endl;
	cout<<"6 * 4 = 24"<<endl;
}
```


$n = 5$ 时可以这样安排:

$ 3 \times 5 = 15 $

$ 2 \times 4 = 8 $

$ 1 + 8 = 9 $

$ 9 + 15 = 24$

```cpp
if(n == 5)
{
	cout<<"3 * 5 = 15"<<endl;
	cout<<"2 * 4 = 8"<<endl;
	cout<<"1 + 8 = 9"<<endl;
	cout<<"9 + 15 = 24"<<endl;
}
```
$n \ge 6$ 时呢?

$ 4 \times 6 = 24 $

那只需要把剩下的数消耗掉。

$ 1 + 2 = 3 $

$ 3 - 3 = 0 $

$1,2,3$ 已经被消灭了。

但是，更重要的是，我们得到了一个 $0$

将 $5$ 和 $7$ 到 $n$ 的数全和 $0$ 乘

最后 $0 + 24 = 24$

```cpp
if(n >= 6)
{
	cout<<"1 + 2 = 3"<<endl;
	cout<<"3 - 3 = 0"<<endl;
	cout<<"4 * 6 = 24"<<endl;
	cout<<"5 * 0 = 0"<<endl;
	for(int i=7;i<=n;i++)
  	{
  		cout<<i<<" * 0 = 0"<<endl;
	}
	cout<<"0 + 24 = 24"<<endl;
}
```

合在一起，AC代码就出来了:

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
int main()
{
    //freopen("Game.in","r",stdin);
    //freopen("Game.out","w",stdout);
    cin>>n;
    if(n<=3)
    {
        cout<<"NO"<<endl;
        return 0;
    }
    cout<<"YES"<<endl;
    if(n == 4)
    {
        cout<<"1 * 2 = 2"<<endl;
        cout<<"2 * 3 = 6"<<endl;
        cout<<"6 * 4 = 24"<<endl;
    }
    if(n == 5)
    {
        cout<<"3 * 5 = 15"<<endl;
        cout<<"2 * 4 = 8"<<endl;
        cout<<"1 + 8 = 9"<<endl;
        cout<<"9 + 15 = 24"<<endl;
    }
    if(n >= 6)
    {
        cout<<"1 + 2 = 3"<<endl;
        cout<<"3 - 3 = 0"<<endl;
        cout<<"4 * 6 = 24"<<endl;
        cout<<"5 * 0 = 0"<<endl;
        for(int i=7;i<=n;i++)
        {
            cout<<i<<" * 0 = 0"<<endl;
        }
        cout<<"0 + 24 = 24"<<endl;
    }
}
```


---

## 作者：BF_AlphaShoot (赞：0)

这是一道难度并不是很大但很巧妙的**构造**题。

首先看到这道题，可能会想到 dfs 和 [ P1236 ](https://www.luogu.com.cn/problem/P1236)，但其实不用。通过前几个小范围数据的枚举可以发现，这道题其实**有规律可循**。

1. $n=1,2,3$ 时是一定不可能的，其余的是一定可能的。

2. $n\bmod 2=1$ 时，从 6 开始，每 2 个连续的自然数中必有一奇一偶~~废话~~，而两数中较大的奇数减去较小的偶数等于 1 。因此可以**等效为** $n=5$ 时的情况，只是多了许多 $\times 1$ 。

   $n=5$ 时，有：

   ```cpp
   5 * 3 = 15
   2 * 4 = 8
   8 + 15 = 23
   23 + 1 = 24
   ```

3. $n\bmod 2=0$ 时较为复杂。从 4 开始，每 4 个连续的数 `a,b,c,d` ，都有：

   ```c++
   a - b = -1
   d - c = 1
   -1 + 1 = 0
   ```

   等效为 $n=4$ 的情况即可，只是多了许多 $+0$ 。

   但是对于一些数（如 6、10 ），在从 4 枚举到最后剩下两数，无法组成 4 个数，这时可以像  $n\bmod 2=1$ 时的做法一样，将较大数减去较小数，得到 1。等效为 $n=4$ 的情况即可，只是多了许多 $+0$ 和一个 $\times 1$ 。

   $n=4$ 时，有：

      ```cpp
      2 * 3 = 6
      6 * 4 = 24
      24 * 1 = 24
      ```

View code:

```c++
#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define ri register int
#define il inline

ll n;

il ll read(){
	int x=0,y=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')
			y=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=x*10+c-'0';
		c=getchar();
	}
	return x*y;
}

signed main(){
	n=read();
	if(n<4){
		printf("NO");
		return 0;
	}
	printf("YES\n");
	if(!(n%2)){
		printf("2 * 3 = 6\n6 * 4 = 24\n");
		for(ri i=4;i<=n;i+=4){
			if(i+4>n){
				if(i==n){
					printf("1 * 24 = 24");
					return 0;
				}
				printf("%d - %d = 1\n1 * 1 = 1\n1 * 24 = 24",i+2,i+1);
				return 0;
			}
			printf("%d - %d = -1\n%d - %d = 1\n-1 + 1 = 0\n0 + 1 = 1\n",i+1,i+2,i+4,i+3);
		}
	}
	else{
		printf("5 * 3 = 15\n2 * 4 = 8\n8 + 15 = 23\n23 + 1 = 24\n");
		if(n==5)
			return 0;
		for(ri i=7;i<=n;i+=2)
			printf("%d - %d = 1\n24 * 1 = 24\n",i,i-1);
		return 0;
	}
}
```



---

## 作者：Soul_Seeker (赞：0)

# 思路详解

开局暴搜，无意中发现规律，开启 AC 之路。

通过找规律可以发现，只要 $n < 4$，就一定没有可能凑出 $24$。

当 $n > 4$ 时，我们可以分情况考虑。

当 $n$ 为偶数，我们可以这样算出 $24$：

>$1 + 2 = 3$
>
>$3 + 3 = 6$
>
>$4 \times 6 = 24$

剩下的就依次用 $i - (i - 1) = 1$ 再 $24 \times 1 = 24$ 即可。

当 $n$ 为奇数

>$3 \times 5 = 15$
>
>$2 \times 4 = 8$
>
>$15 + 8 = 23$
>
>$23 + 1 = 24$

剩下的数字同上方一样计算即可。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
	int n;
	cin >> n;//输入
	if (n < 4)return cout << "NO\n", 0;
	else cout << "YES\n";
	if (n % 2) {
		cout << "3 * 5 = 15\n2 * 4 = 8\n15 + 8 = 23\n23 + 1 = 24\n";//注意，有空格
		for (int i = n; i >= 6; i -= 2)cout << i << " - " << i - 1 << " = 1\n24 * 1 = 24\n";
	} else {
		cout << "1 + 2 = 3\n3 + 3 = 6\n4 * 6 = 24\n";
		for (int i = n; i >= 5; i -= 2)cout << i << " - " << i - 1 << " = 1\n24 * 1 = 24\n";
	}
	return 0;
}
```

---

## 作者：RoyWu1207 (赞：0)

找规律即可。

首先，当 $n \leq 3$ 时，显然无解。

相邻两数差为 $1$，作乘法后原数不变，则只需构造 $n = 4$ 和 $n = 5$ 的情况，分类讨论即可。

构造方法多样，在此不作阐述。

AC Code：

```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
	int n; scanf("%d", &n);
	if (n < 4) printf("NO");
	else if (n % 2 == 0) {
		printf("YES\n2 * 3 = 6\n6 * 4 = 24\n24 * 1 = 24");
		for (int i = 5; i <= n; i += 2)
			printf("\n%d - %d = 1\n1 * 24 = 24", i + 1, i);
	} else {
		printf("YES\n3 - 2 = 1\n1 + 5 = 6\n4 * 6 = 24\n1 * 24 = 24");
		for (int i = 6; i <= n; i += 2)
			printf("\n%d - %d = 1\n1 * 24 = 24", i + 1, i);
	}
	return 0;
}
```


---

