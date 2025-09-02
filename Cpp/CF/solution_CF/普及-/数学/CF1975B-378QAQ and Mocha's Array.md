# 378QAQ and Mocha's Array

## 题目描述

Mocha likes arrays, so before her departure, 378QAQ gave her an array $ a $ consisting of $ n $ positive integers as a gift.

Mocha thinks that $ a $ is beautiful if there exist two numbers $ i $ and $ j $ ( $ 1\leq i,j\leq n $ , $ i\neq j $ ) such that for all $ k $ ( $ 1 \leq k \leq n $ ), $ a_k $ is divisible $ ^\dagger $ by either $ a_i $ or $ a_j $ .

Determine whether $ a $ is beautiful.

 $ ^\dagger $ $ x $ is divisible by $ y $ if there exists an integer $ z $ such that $ x = y \cdot z $ .

## 说明/提示

In the first test case, any two numbers in the array are coprime, so the answer is "No".

In the second test case, we can pick $ i=2 $ and $ j=1 $ . Since every number in the array is divisible by $ a_i = 1 $ , the answer is "Yes".

In the third test case, we can pick $ i=3 $ and $ j=5 $ . $ 2 $ and $ 4 $ is divisible by $ a_i = 2 $ while $ 3 $ , $ 6 $ and $ 12 $ is divisible by $ a_j = 3 $ , so the answer is "Yes".

## 样例 #1

### 输入

```
4
3
7 3 8
5
7 1 9 3 5
5
4 12 2 6 3
5
7 49 9 3 1000000000```

### 输出

```
No
Yes
Yes
No```

# 题解

## 作者：hcy1117 (赞：1)

## 题目大意

给定 $t$ 组数据，每组数据有 $n$ 个数，判断是否可以从中选择两个数使得这 $n$ 个数中的每一个数都可以被这两个数中的任意一个数整除（语文不好可能有点绕[可以自己去看题目](https://www.luogu.com.cn/problem/CF1975B)）。

## 前置知识

**$\gcd$ 整除**

## 思路

1. 先考虑选取的第一个数，因为要使得每一个数都被整除，所以肯定要选取**最小**的那个数（因为大数肯定不能整除小数）。

2. 再考虑第二个数，排除能够被第一个数整除的数，设剩下的数为 $a_{i},a_{i+1},...,a_{k}$，显然能整除 $a$ 序列所有数的数肯定为它们的**公因数**，肯定也是他们最大公因数的因子。所以只要求出剩余数的 $\gcd$，再找出是否有数能整除 $\gcd$ 即可。

3. 最后还有一个需要注意的地方，如果 $n$ 个数都能被选的第一个数整除，也是可以的。

其余有不懂的可以参考代码和注释，如果有错误请指出谢谢。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
int a[100005];
int gcd(int a,int b)//求最大公因数 
{
	if(b==0)return a;
	else return gcd(b,a%b);
}
int main()
{
  	cin>>t;
	while(t--)
	{
		cin>>n;
		for(int i=1;i<=n;i++)cin>>a[i];
		sort(a+1,a+n+1);//排序求最小值 
		int num,cnt=0;
		bool flag=0;
		for(int i=1;i<=n;i++)
		{
			if(a[i]%a[1]!=0)//是剩余的数 
			{
				if(!flag)num=a[i],flag=1;
				else num=gcd(num,a[i]);//求它们的gcd 
			}
			else ++cnt;//记录能被最小数整除的数的个数 
		}
		flag=0;
		for(int i=1;i<=n;i++)
		{
			if(a[i]%a[1]!=0)
			{
				if(num%a[i]==0)flag=1;//是gcd的因数 
			}
		}
		if(flag||cnt==n)cout<<"Yes"<<endl;
		else cout<<"No"<<endl;
	}
}
```

---

## 作者：lpx666666 (赞：0)

## 题意
给出多组数据，每个数据有一个长度为 $n$ 的数组 $a$，求这个数组的所有数是否能用其中的两个数整除。

## 思路
首先想到的方法肯定是暴力再判断，但时间复杂度太高了。

那我们可以在这个基础上优化枚举，直接选出结果。

我一开始的思路是用最小的两个数，如果他们用大的，最小的数肯定除不了，于是我写出了以下代码。
```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
int k,arr[100005];
int main(){
	cin>>k;
	while(k--){
		int n;
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>arr[i];
		}
		sort(arr+1,arr+1+n);
		int s=0;
		for(int i=3;i<=n;i++){
			if(arr[i]%arr[1]!=0 && arr[i]%arr[2]!=0){
				cout<<"No"<<endl;
				s=1;
				break;
			}
		}
		if(!s){
			cout<<"Yes"<<endl;
		}
	}
	return 0;
}
```
然后就错了，因为说不定第二小能被第一小整除，那就相当于只有一个数，就缩小了范围，所以我们选的另一个数要不能被第一小整除，那么范围就是最大的。

## 代码
小改了一下，改出以下代码。
```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
int k,arr[100005];
int main(){
	cin>>k;
	while(k--){
		int n;
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>arr[i];
		}
		sort(arr+1,arr+1+n);//排序 
		int u=0;
		for(int i=2;i<=n;i++){
			if(arr[i]%arr[1]!=0){//判断是否能整除 
				u=1;
				int s=0;
				for(int j=1;j<=n;j++){
					if(arr[j]%arr[1]!=0 && arr[j]%arr[i]!=0){//用得出的两数对所有数判断 
						s=1;
						cout<<"No"<<endl;//不行输出No 
						break;
					}
				}
				if(s==0){
					cout<<"Yes"<<endl;//没有不行的输出Yes 
				}
				break;
			}
		}
		if(u==0){
			cout<<"Yes"<<endl;//如果所有数都能被最小的数整除也行 
		}
	}
	return 0;
}

```

---

## 作者：ggylz49 (赞：0)

## 题目大意
给你一个数列，判断是否存在两个数，使得数列中的所有数都能被两个数中的其中一个整除（输出大小写不敏感）。
## 思路分析
可以先选出数列中必选的数。

首先，最小数一定必选。因为它被数列中除它本身以外的任何数整除。

接着，从数列中剔除最小数的倍数（**最小数的倍数包括最小数本身**），因为他们已经满足题目条件。然后再选出现在数列的最小数作为第二个数，判断数列中所有数是否都能被这两个数的其中一个整除。若有数一个数都无法整除，输出 `No`，否则满足题目要求，输出 `Yes`。
## Code
```cpp
#include <iostream>
#include <algorithm>//使用sort排序
using namespace std;
int main()
{
    int t;
    cin>>t;
    for (int i=1;i<=t;i++)
    {
        int n,minum1,minum2,a[100010]={0};//使用minum1和minum2存储两个数
        bool f=true;//初始时为true
        cin>>n;
        for (int i=0;i<n;i++)cin>>a[i];
        sort(a,a+n);
        minum1=a[0];//第一个数是最小数
        for (int i=0;i<n;i++)
        {
            if (a[i]%minum1!=0)//第二个数是不是第一个数倍数的最小数
            {
                minum2=a[i];
                break;
            }
        }
        for (int i=0;i<n;i++)
        {
            if (a[i]%minum1!=0&&a[i]%minum2!=0)f=false;//若两个数都无法整除，f为false
        }
        if (f==true)cout<<"Yes\n";//符合要求
        else cout<<"No\n";//不符合要求
    }
    return 0;
}
```

---

## 作者：__galaxy_1202__ (赞：0)

**简易版的消消乐...** 
## 题目简述：
给定一个长度为 $n$ 的序列 $a$，判断是否存在两个数 $i,j$ 使得序列中每个数都能被 $a_i$ 与 $a_j$ 整除。  
## 解题思路：
先考虑一号位，如果想让序列令每个数都可以被序列中的一个数数整除的话，那**肯定先考虑最小的那个数啊**。毕竟这个数没法被其他的任何数整除，所以一号位就是数组的最小值。  
接着再考虑二号位，那么首先，二号位最好**越小越好**。那么这个小的数又必须满足**不被一号位整除**。  
## 代码思路：
输入序列 $a$ 后排序，用 $l,r$ 分别表示一号位和二号位，$l$ 固定为 $1$，$r$ 初始化为 $2$（如果没有满足两个条件的数，就固定为第 $2$ 个值），接着使**满足不被一号位整除的最小的数成为二号位**。最后判断一号位与二号位是否满足条件即可。
## CODE:
~~不想写~~ ~~看别的题解去~~ 思路都这么清晰了，所以~~自己想~~。

---

## 作者：FXLIR (赞：0)

### 题意
给你一个数列 $a$，判断是否存在两个数 $i,j$，使得数列中的所有数都能被 $a_i$ 和 $a_j$ 中的其中一个整除。

### 做法
不难发现，数列中最小的数是必须选的，因为最小的数不能被除自己以外的任何数整除。

接下来，我们排除最小的数以及能被最小的数整除的所有数，可以发现，新数列中最小的数也必须选，不然它也无法被其它数整除。

也就是说，如果有解的话，只能选最小的数和不能被最小数整除的数中的最小数。

我们可以先将数列排序，然后从中找出不能被最小的数（也就是排序后数列的第一个数）整除的数中的最小数并记录下来，随后验证整个数列是否都能被这两个数整除。

### AC code
```cpp
#include<iostream>
#include<algorithm>
#define int long long
using namespace std;
const int N=1e5+5;
int t,n,a[N],k;
bool f;
signed main(){
	cin>>t;
	while(t--){
		f=0;
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		sort(a+1,a+n+1);
		for(int i=1;i<=n;i++){
			if(a[i]%a[1]){
				k=a[i];
				break;
			}
		}
		for(int i=1;i<=n;i++){
			if(a[i]%a[1]!=0&&a[i]%k!=0){
				f=1;
				break;
			}
		}
		cout<<(f?"No\n":"Yes\n");
	}
	return 0;
} 
```

---

## 作者：ivanyang1228 (赞：0)

蒟蒻第三篇题解。

首先，对整个数组进行排列。题目要求我们找到 $a[i]$ 与 $a[j]$ 使得整个数组能被这两个数整除，那么首先考虑整个数组的最小值 $a[1]$ 。

其次，遍历整个数组，找到 $a[k]$ 不整除 $a[1]$ ，那么继续遍历整个数组，对于 $a[i]$ 判断是否整除 $a[1]$ 或 $a[k]$ 。
上代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,a[100005],p,q,s;
bool f;
int main(){
	scanf("%lld",&t);
	for(int i=1;i<=t;i++){
		f=1;
		scanf("%lld",&n);
		memset(a,0,sizeof(a));
		for(int i=0;i<n;i++){
			scanf("%lld",&a[i]);
		}
		sort(a,a+n);
		p=a[0];
		for(int i=0;i<n;i++){
			if(a[i]%p!=0){
				q=a[i];
				s=i;
				break;
			}
		} 
		for(int i=s;i<n;i++){//a[1]至a[s]均被a[1]整除，因此不用考虑。
			if(a[i]%p!=0&&a[i]%q!=0){
				cout<<"No"<<endl;
				f=0;
				break;
			}
		}	
		if(f) cout<<"Yes"<<endl;
	}
	return 0;
}
```

感谢 @junjie_zhao 指出思路的错误。

---

## 作者：lyhqwq (赞：0)

# Solution

若 $a_i \mid a_j$，则一定有 $a_i \leq a_j$。

我们将序列从小到大排序，$a_1$ 一定必选。我们从左往右找到第一个不能被 $a_1$ 整除的数 $a_i$，验证 $a_1$ 和 $a_i$ 是否合法即可。

# Code
```cpp
    #include<bits/stdc++.h>
    using namespace std;
    const int N=1e5+5;
    int _;
    int n;
    int a[N];
    int main(){
    	//freopen(".in","r",stdin);
    	//freopen(".out","w",stdout);
    	scanf("%d",&_);
    	while(_--){
    		scanf("%d",&n);
    		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    		sort(a+1,a+1+n);
    		int x=1,y=2;
    		for(int i=1;i<=n;i++){
    			if(a[i]%a[x]!=0){
    				y=i;
    				break;
    			}
    		}
    		int ok=1;
    		for(int i=1;i<=n;i++) if(a[i]%a[x]!=0&&a[i]%a[y]!=0) ok=0;
    		puts(ok?"Yes":"No");
    	}
    	return 0;
    }
     
```

---

## 作者：HasNoName (赞：0)

### 思路

因为数组中最小的数一定不能被其他数整除，所以必须选最小的数。不能被最小的数整除的数中最小的数一定也不能被其他数整除，也得选。最后如果还有不能被那两个数整除的数，就是无解。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100005;
int a[N],b[N];
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T,n;
    cin>>T;
    while(T--)
    {
        cin>>n;
        for(int i=1;i<=n;i++)
            cin>>a[i];
        sort(a+1,a+n+1);//的出两次最小
        int k=0;
        for(int i=1;i<=n;i++)
        {
            if(a[i]%a[1]!=0)//不能被最小的数整除的数
            {
                b[++k]=a[i];
            }
        }
        int flag=1;
        for(int i=1;i<=k;i++)
        {
            if(b[i]%b[1]!=0)//b数组一定有序，b[1]为不能被最小的数整除的数中最小的数
            {
                flag=0;
                break;
            }
        }
        if(flag)cout<<"Yes\n";
        else cout<<"No\n";
    }
    return 0;
}
```

---

## 作者：2huk (赞：0)

> - 给定一个长度为 $n$ 的数组 $a$，判断是否存在 $i, j$ 使得对于所有 $a_k$ 都能被 $a_i$ 或 $a_j$ 整除。
> - $n \le 10^5$。

与 [P10443 消消乐](https://www.luogu.com.cn/problem/P10443) 极其相似。

我们将 $a$ 升序排序，此时 $a_1$ 是最小值，那么 $a_1$ 一定是要选择的一个数。反证法极易。

接下来我们需要考虑的就是那些不是 $a_1$ 倍数的 $a_i$。我们需要再找一个 $a_j(j>1)$ 使得 $a_j$ 是每个这些数的约数，也就是这些数的公约数。

判断是否存在这样一个 $a_j$ 只需要求出这些 $a_i$ 的最大公约数，然后判断 $a_j$ 是否是这个最大公约数的约数即可。

```cpp
void Luogu_UID_748509() {
	fin >> n;
	for (int i = 1; i <= n; ++ i ) fin >> a[i];
	sort(a + 1, a + n + 1);
	
	int GCD = 0;
	for (int i = 2; i <= n; ++ i )
		if (a[i] % a[1]) GCD = __gcd(GCD, a[i]);
	
	if (!GCD) puts("Yes");
	else {
		for (int i = 2; i <= n; ++ i )
			if (GCD % a[i] == 0) {
				puts("Yes");
				return;
			}
		puts("No");
	}
}
```

---

## 作者：roumeideclown (赞：0)

# 题解：CF1975B 378QAQ and Mocha's Array

## 题意简述

给出一个包含 $n$ 个正整数的序列 $a$，判断是否存在两个数 $i$ 与 $j$ （$1 \le i,j \le n$ 且 $i \ne j$），使得 $a$ 中的所有数都能被 $a_i$ 或 $a_j$ 整除。

## 解法分析

先研究这个问题的简化版本：判断 $a$ 中的所有数能否被 $a_k$ 整除（$1 \le k \le n$）。

不难看出，若 $a_k$ 存在，则 $a_k$ 一定是 $a$ 中的最小值（否则最小值无法被 $a_k$ 整除）。

那么对于原问题，去掉所有能被最小值整除的数后，剩余的数又构成了一个简化版本。

因此我们只要对原问题做两遍简化版本即可。

## 代码实现

先找出最小值，然后用数组 $f_i$ 记录 $a_i$ 能否被最小值整除；对剩余的数再执行一次；最后扫一遍 $f$ 数组，若有 $f_i = 0$ （$ 1 \le i \le n$）则输出 `No`，否则输出 `Yes`。

```cpp
#include<bits/stdc++.h>
//#pragma G++ optimize(2,3,"Ofast")
using namespace std;
typedef long long ll;
const int N=100005;
int a[N];
bool f[N];
void work() {
  //注意初始化
	memset(f,0,sizeof(f));
  //输入
	int n;
	scanf("%d",&n);
  //找最小值
	int minx=2147483647;
	for(int i=1;i<=n;i++) {
		scanf("%d",&a[i]);
		minx=min(a[i],minx);
	}
  //标记
	for(int i=1;i<=n;i++) {
		if(a[i]%minx==0) f[i]=true;
	}
  //再来一遍
	minx=2147483647;
	for(int i=1;i<=n;i++) {
		if(f[i]) continue;
		minx=min(a[i],minx);
	}
	for(int i=1;i<=n;i++) {
		if(a[i]%minx==0) f[i]=true;
	}
  //判断，输出
	for(int i=1;i<=n;i++) {
		if(f[i]==false) {
			printf("No\n");
			return;
		}
	}
	printf("Yes\n");
}
int main() {
//  ios::sync_with_stdio(false);
//  cin.tie(0),cout.tie(0);
  //多组数据
	int t;
	scanf("%d",&t);
	for(int i=1;i<=t;i++) {
		work();
	}
	return 0;
}

```

---

