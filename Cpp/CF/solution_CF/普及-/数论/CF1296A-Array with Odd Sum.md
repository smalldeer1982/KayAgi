# Array with Odd Sum

## 题目描述

You are given an array $ a $ consisting of $ n $ integers.

In one move, you can choose two indices $ 1 \le i, j \le n $ such that $ i \ne j $ and set $ a_i := a_j $ . You can perform such moves any number of times (possibly, zero). You can choose different indices in different operations. The operation := is the operation of assignment (i.e. you choose $ i $ and $ j $ and replace $ a_i $ with $ a_j $ ).

Your task is to say if it is possible to obtain an array with an odd (not divisible by $ 2 $ ) sum of elements.

You have to answer $ t $ independent test cases.

## 样例 #1

### 输入

```
5
2
2 3
4
2 2 8 8
3
3 3 3
4
5 5 5 5
4
1 1 1 1```

### 输出

```
YES
NO
YES
NO
NO```

# 题解

## 作者：123456zmy (赞：3)

合法的序列有两种，一种是原来和就是奇数的还有可以变成奇数的（~~废话~~），前一种是奇数的个数是奇数，后一种是奇数和偶数都有。

统计奇数和偶数在序列中出现的次数判断然后输出即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a,a1,a2;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		a1=0;a2=0;
		scanf("%d",&n);
		while(n--)
		{
			scanf("%d",&a);
			if(a&1)++a1;//是奇数
			else ++a2;//是偶数
		}
		if((a1&1)||(a1&&a2))puts("YES");
		else puts("NO");
	}
	return 0;
}
```

---

## 作者：kdy20100729 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1296A)

### 题意简述：  
给定一个长度为 $n$ 的序列 $a$，可以选定 $1 \leq i,j \leq n(i \neq j)$ 使得 $a_i=a_j$。问在若干次操作之后这个序列的和是否可以为奇数。

### 思路：  
合法的序列只需满足以下条件之一即可：  
1. 本来总和就为奇数（奇数数量为奇数）  
2. 既有奇数又有偶数

统计奇数和偶数在序列中出现的次数然后判断即可。

### 代码如下：  
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,cnt,odd,even,a[10005];
signed main()
{
    cin >> t;
    while(t--)
    {
        cnt=odd=even=0;
        cin >> n;
        for(int i=1; i<=n; i++)
        {
            cin >> a[i];
            cnt+=a[i];
            if (a[i]%2==0)
                even++;
            else
                odd++;
        }
        if (cnt%2==1||(even>=1&&odd>=1))
            cout << "YES\n";
        else
            cout << "NO\n";
    }
    return 0;
}
```

---

## 作者：5k_sync_closer (赞：0)

前置芝士：

1. 简单的位运算知识：`x & 1 == 1` 则 `x` 是奇数，否则是偶数。
2. 小奥奇偶性：

| A | B | A+B |
| :-----------: | :-----------: | :-----------: |
| 奇数 | 奇数 | 偶数 |
| 奇数 | 偶数 | 奇数 |
| 偶数 | 偶数 | 偶数 |

# 思路
分类讨论：
1. 都是偶数：NO

任意操作后数列的每个数都仍然是偶数，和也是偶数。

2. 都是奇数：这个不好判断。

奇数个奇数加起来是奇数，而偶数个奇数加起来是偶数。

所以：$n$ 为奇数则 YES，否则 NO。

3. 奇偶都有：YES。

不妨把一些奇数随意变成偶数，只留一个奇数。

那么剩下的偶数加奇数一定是奇数。
# 代码
```cpp
#include <iostream>
using namespace std;
int n, T, s = 0;
int main()
{
    cin >> T;
    while(T--)
    {
        cin >> n;s = 0;
        for(int i = 1, t;i <= n;++i)
            cin >> t, s += t & 1;
        if(s == 0) //都是偶数
            cout << "NO" << endl;
        else if(s == n) //都是奇数
        {
            if(n & 1) cout << "YES" << endl; //n 是奇数
            else cout << "NO" << endl; //n 是偶数
        }
        else cout << "YES" << endl; //奇偶都有
    }
    return 0;
}
```


---

## 作者：_0x46EDC (赞：0)

[获得更好的阅读体验](https://www.luogu.com.cn/blog/jasonying/cf1296a-array-with-odd-sum) [题目传送门](https://www.luogu.com.cn/problem/CF1296A)

---

### 题目分析

给定一个长度为 $n$ 的序列 $a$，可以选定 $1\le i, j \le n (i \ne j)$ 使得 $a_i = a_j$，问是否可以在若干次操作之后使得这个序列的和为奇数。

### 推导

可以通过题目所述操作使 $\sum\limits_n^{i=1}a_i\equiv1(\mod2)$ 分为两种情况：

- $\sum\limits_n^{i=1}a_i\equiv1(\mod2)$

- $\sum\limits_n^{i=1}a_i\equiv0(\mod2)$ 且不满足 $a_i \mod2=k(1\le i\le n,k\in \{0,1\})$

### 代码

```cpp
#include<bits/stdc++.h>
#define N 2009
using namespace std;
int t;
int main(){
    cin>>t;
    while(t--){
        int n,a[N],sum=0,flag=1;//flag代表是否满足序列所有数同奇同偶
        cin>>n;
        for(int i=0;i<n;i++){
            cin>>a[i];
            sum+=a[i];//统计总和
            if(a[i]%2!=a[0]%2)flag=0;//如果奇偶性不同
        }
        if(sum%2==1||!flag)cout<<"YES"<<endl;
        else cout<<"NO"<<endl;
    }
    return 0;
}
```

### 优化

可以使用位运算进行优化。

| 算式 | 意义 |
| - | - |
| a&1 | 判断是不是奇数 |

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int main(){
    cin>>t;
    while(t--){
        int n,odd=0;
        cin>>n;
        for(int i=0;i<n;i++){
            int x;
            cin>>x;
            if(x&1)odd++;//是奇数
        }
        if((odd&&(n-odd))||(odd&1))cout<<"YES"<<endl;
        //odd&(n-odd):是否不是全奇全偶 odd&1:是否是奇数个奇数，即总和为奇数
        else cout<<"NO"<<endl;
    }
    return 0;
}
```

速度可以提升六倍，记得位运算优先级很低，要加上括号。

---

## 作者：Suyun (赞：0)

分以下几种情况讨论：

1. 全是偶数：显然不可行。
2. 全是奇数：在 $n$ 为奇数的情况下可行。
3. 奇数和偶数都有：一定可行，只需要把 $\{a_i\}$ 通过替换操作变成全是奇数或者只有一个偶数的情况。

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
	int t;
	cin >> t;
	
	while (t--) {
		int n;
		cin >> n;
		
		int odd = 0, even = 0;
		
		for (int i = 0; i < n; ++i) {
			int el;
			cin >> el;
			
			if (el % 2) {
				++odd;
			} else {
				++even;
			}
		}
		
		if (even == n) {
			cout << "no" << endl;
		} else if (odd == n) {
			cout << (n % 2 ? "yes" : "no") << endl;
		} else {
			cout << "yes" << endl;
		}
	}
}
```

---

## 作者：NaOH_Frog (赞：0)

能变成奇数的有如下两种：

1.奇数项不全是偶数

2.偶数项不全是奇数且不全是偶数

判一下就行了

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	int tc;
	cin >> tc;//testcase,数据组数
	for(int i = 0; i < tc; i++){
		int n;
		cin >> n;
		int x;
		bool odd = false;
		bool even = false;
  		//上面2行其实就是记录有没有奇数和偶数的判断，因为写在了函数中，所以不用初始化
		for(int i = 0; i < n; i++){
			cin >> x;
			if(x % 2 == 0) even = true; //有没有偶数 
			else odd = true; //有没有奇数 
		}
		cout << (((n % 2 == 0 && odd == true && even == true) || (n % 2 == 1 && odd == true)) ? "YES" : "NO") << endl;
  		//n % 2 == 0 && odd == true && even == true是判断第一种情况的
     	//n % 2 == 1 && odd == true 判断第二种情况
       	//只要满足两种之一即可，判断输出
	}
	return 0;
}
```


---

## 作者：Svveet (赞：0)

# CF1296A Codeforces Round #617(Div.3)

	题意大概是输入一组数，看它们的和是否为奇数，如果是偶数，那可以用其中的一个数替换掉另一个数，注意：是替换不是交换（replace ...with...）。（这个步骤可以重复任意次）
    所以这道题目变成了判断其中奇数和偶数的个数的问题。
###     附上代码，思路如下：

```c
#include<stdio.h>
#include<string.h>
#include<math.h>

int main()
{
	int m , n ,a[2001];
	int ji , ou ;
	scanf("%d" , &m);
	while(m--)
	{
		ji = 0 ; ou = 0 ;
		scanf("%d" , &n) ;
		for(int i = 1 ; i <= n ;i++)
		{
			scanf("%d" , &a[i]) ;
			if(a[i] % 2 ==0)	ou++ ;//统计偶数的个数 
			else	ji++ ;//统计奇数的个数 
		}
		if(ou == n )//全是偶数，不可能和是奇数 
		{
			printf("NO\n") ;
		}
		else if( ji == n)//全是奇数 
		{
			if(ji % 2 == 0)//偶数个奇数，和还是偶数 
			{
				printf("NO\n") ;
			}
			else//奇数个奇数，和是奇数 
				printf("YES\n") ;
		}
		else//有奇数又有偶数，如果原来的和是奇数那直接YES，如果原来的和是偶数，那把一个偶数换成奇数又YES 
		{
			printf("YES\n") ;
		}
	}
	return 0 ;
}

```
感谢观看！（另外问一下我插入的代码为啥没有代码高亮？）

---

