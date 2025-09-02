# The number on the board

## 题目描述

Some natural number was written on the board. Its sum of digits was not less than $ k $ . But you were distracted a bit, and someone changed this number to $ n $ , replacing some digits with others. It's known that the length of the number didn't change.

You have to find the minimum number of digits in which these two numbers can differ.

## 说明/提示

In the first example, the initial number could be $ 12 $ .

In the second example the sum of the digits of $ n $ is not less than $ k $ . The initial number could be equal to $ n $ .

## 样例 #1

### 输入

```
3
11
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3
99
```

### 输出

```
0
```

# 题解

## 作者：wyk0247 (赞：4)

首先，题意为：

现在知道一个被改变了的数每一位之和大于等于k，还知道原数为s，求更改的最小次数。

明白了题目，有什么想法吗？

当然，这个题是贪心：让每次更改后各位数之和增加得最多，则更改次数也就最小

so，解题正式开始：

1.读入k，s：
```cpp
    cin>>k>>s;//因为s可能很大，以字符串的形式读入
	len=s.size();//并求出s的长度
```

2.将s的每一位存入数组a，并用he来求和：
```cpp
    for(int i=0;i<len;i++)
	{
		a[i]=s[i]-'0';//将字符转为与之对应的整数
		he+=a[i];//加入求和器
	}
```
3.将每一位从小到大排个序，便于进行贪心：
```cpp
    sort(a,a+len);
```

4.如果he已经大于k，则不需要更改：
```cpp
    if(he>=k)
	printf("0");
```
5.否则开始更改：
```cpp
    else
	{
		for(int i=0;i<len;i++)//因为从小到大排序，则每次更改的收益是最大的（现在懂了为啥要排序了吧）
		{
			he+=9-a[i];
			ans=i+1;
			if(he>=k)
			break;
		}
		printf("%d",ans);
	}
```
6.贪心结束

完整代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>//用于求字符串长度
#include<algorithm>//用于sort()
using namespace std;
int k;
int he=0;
int len,ans;
string s;
int a[1010];
int main()
{
	cin>>k>>s;
	len=s.size();
	for(int i=0;i<len;i++)
	{
		a[i]=s[i]-'0';
		he+=a[i];
	}
	sort(a,a+len); 
	if(he>=k)
	printf("0");
	else
	{
		for(int i=0;i<len;i++)
		{
			he+=9-a[i];
			ans=i+1;
			if(he>=k)
			break;
		}
		printf("%d",ans);
	}
	return 0;
} 
```
谢谢大家

---

## 作者：LegendaryGrandmaster (赞：3)

## 解题思路

由题意，我们可以知道，如果我们的 $n$ 各位之和已经比 $k$ 要大了，我们直接输出 $0$ 即可

如果各位之和比 $k$ 小的话，由于我们要求最小操作次数，我们就可以设想每次都把这一位上的数改为 $9$ ，但是之前的 $n$ 各位是无序的，我们可以先把各位上的数由小到大排序，这样操作的次数也就越小

直到各位之和要大于等于 $k$ ，输出总操作次数即可


代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;

int main()
{
	int k;
	string st;
	cin>>k>>st;
	sort(st.begin(),st.end());
	int c=0;
	for(int i=0;i<st.size();i++)c+=st[i]-48;
	c-=k;
	if(c>=0){
		cout<<0;
		return 0;
	}
	else{
		c=abs(c);
		int ans=0;
		for(int i=0;i<st.size();i++){
			c-=9-(st[i]-48);
			ans++;
			if(c<=0)break;
		}
		cout<<ans;
		return 0;
	}
}
```

---

## 作者：kbzcz (赞：2)

## 题意

输入一个 $k$ 和一个字符串 $s$，要把字符串转换成数字，让这些数字的和大于或等于 $k$，求要改多少个数字才能让这些数字的和大于或等于 $k$。

## 思路

贪心，每次把最小的数字改成 $9$，算出总和，改到总和大于等于 $k$ 时，输出步数。

~~思路其实比较简单粗暴。~~

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
char s[2000000];
int a[2000000],sum;
int main() {
	int k;
	scanf("%d",&k);
	scanf("%s",s+1);
	int n=strlen(s+1);
	for(int i=1;i<=n;i++) a[i]=s[i]-'0',sum+=a[i];
	if(sum>=k) {//特判
		puts("0");
		return 0;
	}
	sort(a+1,a+1+n);//排序
	for(int i=1;i<=n;i++) {//改数字
		sum=sum-a[i]+9;
		a[i]=9;
		if(sum>=k) {
			printf("%d",i);
			return 0;
		}
	}
}
```


---

## 作者：ice_fish01 (赞：1)

## $\text{CF835B The number on the board}$ 题解

### $\text{Update}$

$\text{2023.01.20}$ 

- 补充了对解法进一步的说明；

- 优化部分表述。

### 本题算法

**贪心 & 高精度 & 排序。**

### 题意简述

- 给定一个 `int` 范围内的整数 $k$ 和一个**不超过 $100000$ 位**的**高精度**正整数 $n$；

- 修改 $n$ 中的某几位，使 $n$ **各位上的数字之和** $\ge k$。

- 求**最小**的修改次数（记为 $ans$）。

### 题目分析

1. 用一个字符串模拟整数（高精度的模板），读入后把数放入一个数组并求和（记为 $sum$）；

2. 将该数列**从小到大**排序。因为我们想要**尽可能少**的修改次数，所以每一次修改我们都要把增加的数值**最大化**，而一位数字最大值是 $9$，不能把一位数字加到无穷大，所以我们选择先对数值小的数位进行修改。

> 插入一下证明：

> 设 $10^l\le n < 10^{l+1}$，$n=a_l\times 10^l + a_{l-1} \times 10^{l-1}+a_{l-2} \times 10^{l-2}+\cdots+a_2\times 10^2+a_1\times 10$，则题中所求的值为 $sum+(9-a_{i_1})+(9-a_{i_2})+(9-a_{i_3})+\cdots+(9-a_{i_{ans}})\ge k$ 中 $ans$ 的最小值。由于 $sum$ 的值已知，所以我们需要使 $a_{i_1} \sim a_{i_{ans}}$ 的值最小，才能让 $(9-a_{i_1})+(9-a_{i_2})+(9-a_{i_3})+\cdots+(9-a_{i_{ans}})$ 的值最大，从而让 $ans$ 取得最小值。而 $ans$ 的大小未知，所以我们需要将数列 $a_{1}\sim a_{l}$ **从小到大排序**以满足要求。

3. 输出最少操作次数。

### 代码实现

1. **高精度数的读入与预处理**。
```cpp
	string s;
	cin >> k;
	getline(cin,s); //C++读入字符串的坑点，使用cin读入一行一个单独的整数后，需要“假装”读入这一行，不然就是空串
	getline(cin,s);
	int len = s.length();
	for(int i = len - 1,j = 1;i >= 0;i--,j++) //提取字符串中的每一位至a数组中，数的位数越高存入数组的下标越低
	{
		a[j] = s[i] - '0';
		sum += a[j];
	}
```

2. **特判 $sum$ 已经 $\geq k$ 的情况，直接输出 $0$**。
```cpp
	if(sum >= k)
	{
		puts("0");
		return 0;
	}
```

3. **对这个高精度数按从小到大的规则排序**（`sort` 即可）。
```cpp
	sort(a+1,a+len+1);
```

4. **对每一位进行处理并输出答案**。
```cpp
	for(int i = 1;sum < k && i <= len;i++)
	{
		sum += 9 - a[i]; //处理各数位之和的变化
		ans++;
	}
	cout << ans;
```


### 友情提示

1. 注意高精度数的**处理细节**。这很考验大家的**代码实现能力**。

2. 注意证明一下贪心思路。笔者已经在“题目分析”板块中给出不是那么形式化的证明。

3. **代码，没有就是没有，~~笔者认为已经讲得足够清楚了~~**。

4. 感谢管理员[**览遍千秋**](https://www.luogu.com.cn/user/28910)在管理组休假后加班为本题解提出的建议。

---

## 作者：_JF_ (赞：1)

## CF835B The number on the board 

[题目传送门](https://www.luogu.com.cn/problem/CF835B)


贪心入门题。

题目大意：

给出两个正整数 $k$，$n$，其中的 $n$ 被修改过，你需要修改 $n$ 中的某几位，使新的 $n$ 的各个位置的和为 $k$，求最小的修改次数。 

思路：

首先，如果原数各位的和已经大于等于 $k$ 说明我们不用修改，直接输出 $0$。

其次，我们每一位能取到的最大值为 $9$。

然后，我们由于要操作次数最小，那我们就尽量使每次操作能产生的贡献要大。所以每一位越小，贡献越大。我们只用对字符串的数进行排序，顺序遍历算出贡献，直到各位数字和大于 $k$ 为止。


$Code$：
 
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =1e6+10;
int a[N];
int main()
{
	int n;
	cin>>n;
	string k;
	cin>>k;
	int ans=0;
	for(int i=0;i<k.length();i++)
		a[i]=k[i]-'0',ans+=k[i]-'0';
	if(ans>=n)
		cout<<"0"<<endl,exit(0);
	int last=n-ans,sum=0;
	sort(a,a+k.length());
	for(int i=0;i<k.length();i++)
	{
		last-=(9-a[i]);
		sum++;
		if(last<=0)
			break;
	}
	cout<<sum<<endl;
	return 0;
}


```


---

## 作者：a2358972980 (赞：1)

这道题是一道经典的贪心题目。贪心策略是每次找到最小的数更改为9。更改之后比较，如果大于目标，输出。小于，继续循环。因为数据十万位，需要用高精度读入。
话不多说，上代码。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
char a[100005];//数据十万，只能用字符串 
long long b,sum,ans;//十年OI一场空，不开long long见祖宗 

int main()
{
	scanf("%lld",&b);
	scanf("%s",a);
	int len=strlen(a);//输入 
	for(register int i=0;i<len;i++)//register小优化防超时 
	sum+=a[i]-'0';//统计最开始的总数 
	register int i=0;
	sort(a,a+len,less<int>());//排序，使后面while循环每一次加上的数最大，less<int>()是指从小到大排序 
	while(sum<b)//每次循环都有一次比较
	{ 
			ans++;
			sum+=9-a[i]+'0';//sort之后每次更改当前最小的数为九
			i++;
	}
	printf("%lld",ans);//输出 
	return 0;//结束 
}
```

---

## 作者：_Evergarden_ (赞：0)

## [原题 $link$](https://www.luogu.com.cn/problem/CF835B)


------------
## 题意

### [正版题目](https://www.luogu.com.cn/discuss/508340)

给出一个 $k$ 和一些数字 $n$ （中间无空格） ，需要让这些数字之和大于等于 $k$ ，求最少的修改次数。

## 思路

由于数字很大，我们需要用字符串来读入，并且用 $add$ 加起来，用贪心的思路排序，再改数字，当总和大于等于 $k$ 时，输出修改的次数。

### 注意：需要特判一开始就大于等于 $k$ 的情况。

### 排序方式：从小到大排序，因为想要修改次数最少，每次改的数字需要尽可能大（也就是9），数字越小，修改之后加的数字越多，修改的次数越少（贪心）。

## $Code$

```cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int N = 1e5 + 10;

int k;
string s;//s就是题目中的那一些数
int a[N], add, ans;//add是当前数字总和，ans是最少需要修改的次数

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);//读入优化
	cin >> k >> s;
	int n = s.size();
	for(int i = 0; i < n; ++ i) {
		a[i] = s[i] - 48;//0的ASCLL码是48，所以a数组存的是当前这个数字的值
		add += a[i];//把数字加起来
	}
	sort(a, a + n);//把最小的排到最前面
	if(add >= k) {//特判一开始就大于等于了
		printf("0");
	}
	else {
		for(int i = 0; i < n; ++ i) {
			add = add + (9 - a[i]);//加上这个数字被修改之后增加的量
			ans ++;//修改次数加一
			if(add >= k) {//若大于k了，输出步数之后就跳出
				printf("%d", ans);
				break;
			}
		}
	}
	return 0;
}
```


---

## 作者：ytcccf (赞：0)

### 题意简述

有一个被改变的数每位之和大于等于 $k$ ，原数为 $s$ ，求更改的最小次数。

### 题目分析

题目难度：普及-

$\text{AC code}$ 时间复杂度为 $\Theta(len)$


### 解题思路 

读题后发现此题显然可以用贪心的方法解决，因为数比较大，采用字符串的读入方式，转化为数字后扔进桶里进行维护，从最小的开始更改，退出循环后输出答案即可。

### AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
int k;
string s;
int a[100010];
int ss[15];
int main()
{
	ios::sync_with_stdio(false);//cin、cout加速 
	cin>>k>>s;
	int len=s.length(),sum=0;
	for(int i=0;i<len;i++)
	{
		int x=s[i]-'0';
		sum+=x;
		ss[x]++;//放进桶里 
	}
	if(sum>=k)//满足条件直接输出 
	{
		cout<<0<<endl;
		return 0;
	}
	int ans=0;
	int i;
	for(i=0;i<=8;i++)
	{
		if(sum+(9-i)*ss[i]>=k) break;//如果加了会过头就退出循环 
		else
		{
			sum+=(9-i)*ss[i];//否则就加上去 
			ans+=ss[i];
		}
	}
	cout<<ans+(k-sum+9-i-1)/(9-i)<<endl;//如果还没到就加上一些，记得向上取整（WA警告） 
	return 0;//完结撒花~ 
}
```

---

## 作者：Fat_Fish (赞：0)

一道很好的**贪心**练习题。

**贪心策略：** 由于要尽可能小地进行操作，所以可以先从小到大$sort$一遍，每次将数字变成$9$,如果加和$sum \ge k$,输出操作次数即可。

$Code:$

```cpp
#include<iostream>
#include<bits/stdc++.h>
using namespace std;
//#define int long long其实这题不用开long long
const int maxn=1e5+10;
int a[maxn];
string s;//用字符串读入
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);//读入优化
	int k,sum=0;
	cin>>k>>s;
	int l=s.length();//数字个数，及字符串长度
	for(int i=0;i<l;++i){
		a[i+1]=s[i]-'0';//字符、数字转换，-‘0’或者-48皆可
		sum+=a[i+1];
	}
	sort(a+1,a+1+l);//从小到大排序
	int ans=0;
	for(int i=1;i<=l+1;++i){
		if(sum>=k){
			ans=i-1;//操作次数
			break;
		}
		sum+=9-a[i];//变成9 sum会增加多少
	}
	cout<<ans<<'\n';
	return 0;
}
```
[玄学运行时间](https://www.luogu.com.cn/record/50369242)

---

## 作者：happybob (赞：0)

CF的题意真是令人看不懂哇！谢谢 @lfc20070515 在题解中的题目翻译

本体的主要思路是贪心，先把每一位加起来，如果已经 >= k直接输出0

不然sort一遍，因为把小的数变为9会比大的数变为9好得多，如果这是每位的和 >= k，输出

代码，1.05s：
```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int k;

string s;

int main()
{
    cin >> k >> s;
    //int len = s.size();
    //也可以这么写，时间复杂度是一样的
    int len = s.length(), sum = 0;
    for(int i = 0; i <= len - 1; i++)
    {
        sum += s[i] - '0';
    }
    if(sum >= k)
    {
        cout << "0\n";
    }
    else
    {
        sort(s.begin(), s.end());
        for(int i = 0; i <= len - 1; i++)
        {
            sum += 9 - (s[i] - '0');
            if(sum >= k)
            {
                cout << i + 1 << endl;
                break;
            }
        }
    }
    return 0;
}
```

当然，这样速度快一点，989ms，不知为什么，length变为size变成了1.02s，看来复杂度不是完全一样的哦

```
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int k;

string s;

int main()
{
    cin >> k >> s;
    int len = s.length(), sum = 0;
    len--;
    for(int i = 0; i <= len; i++)
    {
        sum += s[i] - '0';
    }
    if(sum >= k)
    {
        cout << "0\n";
    }
    else
    {
        sort(s.begin(), s.end());
        for(int i = 0; i <= len ; i++)
        {
            sum += 9 - (s[i] - '0');
            if(sum >= k)
            {
                cout << i + 1 << endl;
                break;
            }
        }
    }
    return 0;
}
```


---

## 作者：LiteratureCollege (赞：0)

~~为什么我总感觉CF的题面这么难懂呢。~~

我还是用了很长的时间才了解这题是让我们求什么。

**一句话题意：求要使一个数字的数字之和大于等于k至少需要修改多少位。**


贪心+排序；
简单思考可知：要使修改的次数最少，那么最优的贪心策略便是每一次将最小的那一位改为9，直到他的数字之和大于等于k。

那么我们先以字符串的形式输入,再将这个字符串从小到大排序，之后，第i次操作都将第i位改为9，在判断它是否达到了k即可。

```
#include<bits/stdc++.h>
using namespace std;
int k,gy,l,zjy;
char s[100416];
int main()
{
	cin>>k>>s;
	l=strlen(s);
	for(int i=0;i<strlen(s);i++)
	{
		gy+=s[i]-'0';//计算数字和 
	}
	if(gy>=k)//如果他本身的数字之和已经达到了k 
	{
		cout<<0;
		return 0;
	}
	sort(s,s+l);//排序 
	while(gy<k)
	{
		gy+='9'-s[zjy];//将这一位改为9 
		zjy++;
	}
	cout<<zjy;
	return 0;
	
}
```


---

