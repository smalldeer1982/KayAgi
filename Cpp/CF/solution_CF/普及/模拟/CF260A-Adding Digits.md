# Adding Digits

## 题目描述

Vasya has got two number: $ a $ and $ b $ . However, Vasya finds number $ a $ too short. So he decided to repeat the operation of lengthening number $ a $ $ n $ times.

One operation of lengthening a number means adding exactly one digit to the number (in the decimal notation) to the right provided that the resulting number is divisible by Vasya's number $ b $ . If it is impossible to obtain the number which is divisible by $ b $ , then the lengthening operation cannot be performed.

Your task is to help Vasya and print the number he can get after applying the lengthening operation to number $ a\ n $ times.

## 样例 #1

### 输入

```
5 4 5
```

### 输出

```
524848
```

## 样例 #2

### 输入

```
12 11 1
```

### 输出

```
121
```

## 样例 #3

### 输入

```
260 150 10
```

### 输出

```
-1
```

# 题解

## 作者：TLMPEX (赞：1)

思路：先枚举第一次延长，如果第一次可以延长则输出延长一次后的数，因为一个数乘10除以一个数的余数是不变的，所以我们可以再输出n-1个0啦。如果第一次不可以延长，就输出“-1”了。

代码。
```c
#include<bits/stdc++.h>
using namespace std;
int main(){
	int a,b,n,i,t=1;
	cin>>a>>b>>n;
	for(i=0;i<=9;i++)//枚举第一次延长
		if((a*10+i)%b==0){//如果可以延长，则标记t为0，并进行延长和退出此层循环
			t=0;
			a=a*10+i;
			break;
		}
	if(t)cout<<"-1";//如果第一次不可以延长，就输出-1
	else{//否则输出a并输出剩下的0
		cout<<a;
		for(i=1;i<n;i++)
			cout<<0;
	}
}
```


---

## 作者：PragmaGCC (赞：1)

考虑到每一次延长都要被 b 整除，所以，如果我们可以让一次延长后每次添加在末尾的数都不会改变整除性，这道题就迎刃而解了。

于是，我们把目光看向了 0 。

在数的末尾加上一个 0，其实就相当于将这个数$\times 10$，而这是不会改变整除性的。并且，因为 0 是最小的数字，所以这个数一定是“最小的”，也就是唯一的。

这样，我们就只需要考虑第一次延长的数是多少，之后在末尾一直加上 0 直到延长 $n$ 次。

如果它连一次都延长不了，那么直接输出 -1 就好了。

```cpp
#include <bits/stdc++.h>
using namespace std;
int a, b, n;
int main()
{
    scanf("%d%d%d", &a, &b, &n);
    for (int i = 0; i <= 9; i++) //从小到大枚举每一个“数字”
    {
        int x = 10 * a + i;
        if (x % b == 0) //被整除了！
        {
            printf("%d", x);                 //先把延长后的数输出
            for (int j = 1; j <= n - 1; j++) //把剩下的0全部写出来
                printf("0");                 //神奇的是，这里如果不加引号会出锅
            return 0;                        //可以结束程序了
        }
    }
    printf("-1"); //连一次都延长不了，直接输出-1
}
```

---

## 作者：Lwen1243 (赞：1)

[传送门](https://www.luogu.org/problem/CF260A)
对于给定的a，我们只要在给定的长度里找到一个值i连接在a后可以使新的a能被b整除，一旦能被b整除，只要在它后面补0就可以了
代码：
```cpp
#include<iostream>
#define f(i,a,b) for(int i = a; i <= b ; i  ++ )
using namespace std;
int a,b,n;
int main()
{
    cin>>a>>b>>n;
    f(i,0,9)
    {
        if((a*10+i)%b == 0)
        {
            cout<<a*10+i;
            f(j,1,n-1) cout<<"0";
            system("pause");
            return 0;
        }
        
    }
    cout<<"-1"<<endl;
    system("pause");
    return 0;
}
```


---

## 作者：lsw1 (赞：0)

要延长 $n$ 次满足 $b|a$ ，首先要延长 $1$ 次,枚举 $0-9$ 中哪个可以补，如果 $1$ 次都延长不了，那么直接输出`-1`。如果可以延长，那么一直补`0`一定可以一直满足 $b|a$ ，既如果 $b|a$ ,则 $b|10a$ 。
```cpp
#include <iostream>
using namespace std;
int main()
{
	int a,b,n;
	cin >> a >> b >> n;
	for(int i = 0;i < 10;i++)//枚举可以补0~9中的哪个
	{
		if((a * 10 + i) % b == 0)//如果满足条件
		{
			cout << a << i;//补上去
			for(int j = 1;j < n;j++)//把剩下的0补上去
			{
				cout << 0;
			}
			return 0;
		}
	}
	cout << -1;//进不去说明无法延长
	return 0;
}
```

---

## 作者：David_H_ (赞：0)

这题思路还是比较简单的。

对于任意一个数字 $a$，在他的末尾加上一个整数 $p\in[0,9]$，变成 $\overline{ap}=10a+p$。那么，写程序的时候只需要判断 $b\mid (10a+p)$ 是否成立即可。一旦成立，不论 $b$ 为任何值，只需不断 $\times 10$ 即可，不影响整除性。

代码如下：
```cpp
#include <iostream>
using namespace std;
int a, b, n;
int main() {
    cin >> a >> b >> n;
    for (int i = 0; i <= 9; i++) {
        if (!((a * 10 + i) % b)) {
            cout << a * 10 + i;
            for (int j = 0; j < n - 1; j++) {
                cout << "0";
            }
            return 0;
        }
    }
    // 上面试完了，剩下肯定不行，直接输出 -1
    cout << "-1" << endl;
    return 0;
}

```

---

## 作者：lhjy666 (赞：0)

```cpp
#include<bits/stdc++.h>
#define ll long long
#define MOD 100000007
using namespace std;
ll a,b,n,z=1;
bool check(ll k)
{
	ll w=1;
	while(1)
	{
		if(k/w==a) return 1;
		else
		{
			if(w>k) return 0;
			w=w*10;
		}
	 } 
}
int main()
{
	scanf("%lld%lld%lld",&a,&b,&n);
	ll k=b;
	ll i=n,j=1;
	ll a1=a;
	for (int j=0;j<=9;j++)
	{
		k=a*10+j;
		if(k%b==0)
		{
			printf("%d",k);
			for (int i=1;i<=n-1;i++)
			{
				printf("0");
			}
			return 0;
		}
	}
	printf("-1");
	return 0;
}
////////////////
```

---

