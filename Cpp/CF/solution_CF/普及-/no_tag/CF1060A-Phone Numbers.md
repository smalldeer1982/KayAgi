# Phone Numbers

## 题目描述

Let's call a string a phone number if it has length 11 and fits the pattern "8xxxxxxxxxx", where each "x" is replaced by a digit.

For example, "80123456789" and "80000000000" are phone numbers, while "8012345678" and "79000000000" are not.

You have $ n $ cards with digits, and you want to use them to make as many phone numbers as possible. Each card must be used in at most one phone number, and you don't have to use all cards. The phone numbers do not necessarily have to be distinct.

## 说明/提示

In the first example, one phone number, "8000000000", can be made from these cards.

In the second example, you can make two phone numbers from the cards, for example, "80123456789" and "80123456789".

In the third example you can't make any phone number from the given cards.

## 样例 #1

### 输入

```
11
00000000008
```

### 输出

```
1
```

## 样例 #2

### 输入

```
22
0011223344556677889988
```

### 输出

```
2
```

## 样例 #3

### 输入

```
11
31415926535
```

### 输出

```
0
```

# 题解

## 作者：览遍千秋 (赞：3)

第一篇题解写得没法看啊QAQ

那萌新来说说思路QAQ

根据题目，一个电话号码第一位一定是一个$8$，那么从贪心的角度来说，我们把所有的$8$往前放。

再考虑给出了$n$个字符，所以最多有$n/11$（下取整）个号码。

因此答案是上述两个东西的最小值。

代码：
```cpp
#include<iostream>
#include<cstdio>
#include<string>
using namespace std;
string s;
int l,e,ans;
int mian()
{
    cin>>l;
    cin>>s;
    for(int i=0;i<l;i++) if(s[i]=='8') e++;
    ans=min(l/11,e);
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：Fan_Tuan (赞：1)

# 题解 CF1060A 

emmm这道题想明白就好了，有可能有5个8，但是可能就只能组成两个电话号码。所以就只能是2。但是呢，如果可以组成5组电话号码，不过只有2个8，那也只能组成2个。找这之间的两者的最小值就好了

# 代码
```c
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;

int n;
char s[101];

int main()
{
	while (scanf("%d", &n) != EOF) {
		int count = 0;
		scanf("%s", s); 
		for (int i = 0; i < n; i++) {
			if (s[i] == '8') count++;
		}
		int ans = n/11;
		cout << min(count,ans) << endl; 
	}
	return 0;
}
```


---

## 作者：kevin24 (赞：1)

## 思路
因为一个电话号码第一位一定是 $8$，所以要统计 $8$ 的个数。又因为卡片不能重复使用，所以电话号码的个数最多也只有 $n/11$ 个。所以电话号码的个数就是他们两个的最小值了。

## 代码
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int main(){
	int n,i,s=0;
	char a;
	cin>>n;
	for(i=1;i<=n;i++){
		cin>>a;
		if(a=='8')
			s++;//统计8的个数
	}
	int ans=min(n/11,s);
		cout<<ans;
	return 0;
}
```
完结撒花！！




---

## 作者：CrTsIr400 (赞：1)

###### ~~题解就只有两篇？~~
#### 先别急着看代码，理解思路。
### 1.方法是什么？
### 电话号码第一位是8，把所有的8往前放。因为n>=11,所以至少有n/11种号码。
#### 先求出n/11的值（n>=11),再求出8的个数（开头），最后求它们的最小值。
### 2.code
```cpp
#include<cstdio>
#define min(a,b)a<b?a:b
int n,cnt,len;char c[10086];
int main()
{
	scanf("%d",n);
	while((c[0]=getchar())>32||c[0]<126);
	while((c[len++]=getchar())>=32&&c[len++]<=126);
	for(int i=1;i<=n;i++)if(c[i]=='8')cnt++;
	printf("%d",min(n\11,cnt));
}
```



---

## 作者：cecilia_sankta (赞：0)

## T1
裸题，然而交了7次

灰常容易！

枚举$8$个数计算值并更新最大值

注意不能直接输出$min(8\text{的个数},((N-(8\text{的个数)})/10))$

如下：
```cpp
18
888888888324353326
```
### 异常丑陋常数大的一批的Demo:
```cpp
#include<cstdio>
#include<iostream>
#include<cmath>
using namespace std;
int num[9] ;
int main(){
	int N;
	scanf("%d",&N);
	int M = N ;
	getchar();
	while(N--){
		int c = getchar();
		num[c-'0']++;
	}
	int maxv = 0;
	for(int i=0;i<=num[8];++i)
		maxv = max(min((M-i)/10,i),maxv) ;
	printf("%d\n",maxv) ; 
	return 0;
}
```

---

