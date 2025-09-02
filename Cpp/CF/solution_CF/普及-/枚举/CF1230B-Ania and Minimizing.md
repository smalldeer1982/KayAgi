# Ania and Minimizing

## 题目描述

Ania has a large integer $ S $ . Its decimal representation has length $ n $ and doesn't contain any leading zeroes. Ania is allowed to change at most $ k $ digits of $ S $ . She wants to do it in such a way that $ S $ still won't contain any leading zeroes and it'll be minimal possible. What integer will Ania finish with?

## 说明/提示

A number has leading zeroes if it consists of at least two digits and its first digit is $ 0 $ . For example, numbers $ 00 $ , $ 00069 $ and $ 0101 $ have leading zeroes, while $ 0 $ , $ 3000 $ and $ 1010 $ don't have leading zeroes.

## 样例 #1

### 输入

```
5 3
51528
```

### 输出

```
10028
```

## 样例 #2

### 输入

```
3 2
102
```

### 输出

```
100
```

## 样例 #3

### 输入

```
1 1
1
```

### 输出

```
0
```

# 题解

## 作者：StudyingFather (赞：3)

一道不算太难却坑点不少的贪心题。

首先特判一下 $n=1$ 的情况，如果 $k=1$ 则直接变为 $0$。

为啥要特判 $n=1$ 呢？因为只有 $n=1$ 时数字才能被变为 $0$，其它时候因为不能有前导零的原因都不行。

接下来解决 $n \neq 1$ 的情况：最高位我们直接变为 $1$（别忘了不能有前导零），剩下的位数则变为 $0$。

注意如果一个数字不需要变化的话就别占用变化次数了，把省下的次数用去变其他数字就行。

```cpp
#include <cstdio>
char s[200005];
int main()
{
 int n,k;
 scanf("%d%d",&n,&k);
 scanf("%s",s);
 if(n==1)
 {
  if(k)puts("0");
  else puts(s);
 }
 else
 {
  if(s[0]!='1'&&k)s[0]='1',k--;
  for(int i=1;i<n&&k;i++)
   if(s[i]!='0')s[i]='0',k--;
  puts(s);
 }
 return 0;
}
```


---

## 作者：1qaz234Q (赞：2)

### Solution
- 使用贪心算法。
- 当 $k=0$ 时，输出数字串。
- 当 $k>0$ 并且 $n=1$ 时，输出 $0$。
- 当 $k>0$ 并且 $n>1$ 时，把最高位改为 $1$，剩下的改为 $0$。注意，如果数字已是最小的值，就不用更改。
- 时间复杂度为 $O(n)$。
### Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n, k;
    string a;
    cin >> n >> k >> a;
    if (k == 0) // 如果改动数字的个数为0时
    {
        cout << a;
    }
    if (k > 0 && n == 1) // 如果改动数字的个数大于0并且数字串长度为1时
    {
        cout << 0;
    }
    if (k > 0 && n > 1) // 如果改动数字的个数大于0并且数字串长度超过1时
    {
        if (a[0] != '1') // 如果最高位不是最小的值时
        {
            a[0] = '1';
            k--;
        }
        for (int i = 1; i < n && k > 0; i++)
        {
            if (a[i] != '0') // 如果数字不是最小的值时
            {
                a[i] = '0';
                k--;
            }
        }
        cout << a;
    }
}
```


---

## 作者：___cjy__ (赞：1)

# CF1230B Ania and Minimizing 题解

[题目传送门](https://www.luogu.com.cn/problem/CF1230B)

[更好的阅读体验](https://www.luogu.com.cn/blog/chengjiayi666/cf1230b-ania-and-minimizing-ti-xie)

### 题目大意：

将一个长度为 $n$ 的数字串进行 $k$ 次更改，在没有前导零的情况下使数字串的值最小。

### 正文：

通过观察样例，我们可以发现更改数字要尽可能的从数位更高的位置进行更改，并且将该数更改为最小的情况。

对于每一个数的最高位，因为题目有没有前导零的限制，最高为数必须为 $1$。而对于其余数，在确保最高位不为 $0$ 的情况下均可以更改为 $0$。

要注意，在进行更改的时候，不仅要从高位到低位更改，同时也要判断某一位是否需要更改。如果该位已经是最小的情况了，就不需要进行更改，以免浪费更改次数。

当然，在 $n=1$ 且 $k=1$ 的情况下，我们需要进行特判。因为它的结果为 $0$，所以不能被前导零的判断所影响。

### 总结：

- 从高位到低位更改 $k$ 次，最高位更改为 $1$，其余更改为 $0$。

- 如果该位已是最小的情况，就不进行更改。

- 特判 $n=1$ 且 $k=1$ 的情况。

### AC Code：


```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<string>
#include<cmath>
#define int long long
#define N 114514
#define INF 0x3f3f3f3f
#define bug printf("..........bug!..........\n");
using namespace std;
int n,k,i,cnt;
string s;
signed main(){
	cin>>n>>k>>s;//string类型数字串。 
	if(n==1&&k==1){cout<<0;return 0;}//特判。 
	if(s[0]!='1'&&k!=0) k--,s[0]='1';//第一位单独处理。 
	while(cnt<k&&i<n){//cnt记录当前更改个数，i记录当前数位的下标。 
		i++;
		if(s[i]!='0') s[i]='0',cnt++;//将该数位更改。
	}
	cout<<s;
	return 0;
}
```


---

## 作者：ckk11288 (赞：1)

为了使改动后的数字尽量小，那么我们就需要**从高位到低位**修改，让原数除第一位以外尽可能多的为零（注意最高位不能为零）。但如果这个位置上的数本身就是零，那么就直接跳过，节约修改次数。

以上为贪心策略，但此策略不能全面解决一些特殊问题：比如整个数只有一位。
因此我们需要一些特判（见代码）：

**Code:**
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;//n为长度，k为修改次数
string a;
int main()
{
	int i;//在这里定义便于修改
	scanf("%d%d",&n,&k);
	cin>>a;
	if(!k) cout<<a,exit(0);//若k为0，直接输出并退出
	if(a.length()==1)
	{
		puts("0");
		exit(0);
	}//若n=1,直接输出0并退出
	if(a[0]=='1')
	{
		i=1;//若第一位已经为1，则直接从第二位开始修改，节约修改次数
	}
	else 
	{
		a[0]='1';
		k--;
	}//否则直接修改，也从第二位开始
	for(;i<a.length();i++)
	{
		if(k>0&&a[i]!='0')//可修改
		{
			a[i]='0';
			k--;
		}
		if(!k) break;//修改次数用完
	}
	cout<<a;//输出已经修改的字符串
	return 0;
}
```

---

## 作者：zhouzihe (赞：0)

## 1 观察题目
观察题目，不难得出题目是想让我们把一个字符串 $n$ 改动 $k$ 个字符，使得 $n$ 的字典序最小。  

不难证明，把 $n_i$ 更改的利益是比更改 $n_{i-1}$ 的利益要小的，所以我们可以从最高位更改，直到 $k=0$ 时，输出 $n$。注意最高位不能为 $0$。(当需要更改时才更改) 

证明：设第 $i$ 位为 $a$，将它更改的收益为 $a \times 10^{i}$，第 $i-1$位为 $b$，将它更改的收益为 $b \times 10^{i+1}$，其中 $a$ 最大为 $9$，$b$ 最小为 $1$，不难发现更改第 $i-1$ 位的收益一点是比更改第 $i$ 位要大的。(不考虑 $i=1$ 的情况，$1 \leq a,b \leq 9$)
## 2 code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
string s;
int main(){
	cin>>n>>k>>s;
	if(n==1){
		if(k!=0){
			cout<<0;
		}
		else{
			cout<<s;
		}
	}
	else{
		if(s[0]!='1'&&k!=0){
			s[0]='1';
			k--;
		}
		for(int i=1;i<n&&k!=0;i++){
			if(s[i]!='0'){
				s[i]='0';
				k--;
			}
		}
		cout<<s;
	}
	return 0;
}
```


---

## 作者：Erotate (赞：0)

### Solution

显然，当 $n=1$ 时，直接改成 $0$ 即可，因为没有前导零。否则，把最高位变成 $1$，剩下的位数从高到低变成 $0$。

注意，如果其中的某些位上的数已经是最小的值了，就不需要更改。

### code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,k;
char ch[N];
int main(){
	scanf("%d%d%s",&n,&k,ch+1);
	if(!k) printf("%s",ch+1);
	else{
		if(n==1){
			printf("0\n");
			return 0;
		}
		int cnt=0;
		for(int i=1;i<=n;++i){
			if(i==1 && ch[i]!='1' && cnt<k){
				printf("1");
				cnt++;
			}else if(i>1 && ch[i]!='0' && cnt<k){
				printf("0");
				cnt++;
			}else printf("%c",ch[i]);
		}
	}
	return 0;
}
```


---

## 作者：OoXiao_QioO (赞：0)

这道题不是很难，却坑点极多，我被坑了有四五次，我真是太菜了。。。

# 思路

给大家总结一下比较重要的坑点和思路吧。

- 不能有前导零，即更改后的字符串开头不为 $0$。

- 如果遍历到字符串第一个字符，只能更改为 $1$，但如果本来就是 $1$，则不需要做出任何改变，避免重复浪费更改机会。

- 遇到非零的数时（前提不是开头），果断改为 $0$。

- 如果遇到 $0$ 的时候，不用做任何改变，避免重复浪费更改机会。

- 注意判断字符串长度为 $1$ 的时候。

说了这么多点，大家可能脑子稍微有点绕不过来，那么下面就给大家放代码，这样就能理解思路了。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	//定义
	
	 
	int n,i,cnt,k;// cnt 表示现在替换了多少个数。 
	char s[200001];
	
	//输入
	 
	scanf("%d %d %s",&n,&k,s);
	
	//处理
	 
	if(n==1)//特判字符串长度为 1. 
	{
		if(k==0)//如果不给我们机会更改 
			printf("%s\n",s);//输出原字符串。 
		else
			printf("0\n");//否则直接输出 0。 
		return 0;//及时结束程序，避免进入下面的操作。 
	}
	
	//字符串长度不为 1
	
	cnt = 0;// cnt 初始设为 0。 
	for(i=0;i<n;i++)
	{
		if(cnt<k&&s[i]!='0')//如果我们还有机会替换且当前字符不为 0 
		{
			if(i==0&&s[i]!='1')//如果是开头且开头的数不为 1 
				s[i] = '1',cnt++;//把开头替换成 1，操作次数 cnt++。 
			else if(i!=0)//否则就是不开头的情况 
				s[i] = '0',cnt++;//设为 0，操作次数 cnt++，此时不用担心把原来的 0 替换成 0 而浪费，因为我们在前面的 if 判断中已经刨去了当前字符为 0 的情况。 
		}
	}
	printf("%s\n",s);//输出更改后的字符串。 
	return 0;//结束 
}
```


---

## 作者：微香玉烛暗 (赞：0)

这道题主要是用字符读入，再$O(n)$扫一遍即可结束。

```cpp
# include <cstdio>
# include <cstring>
# include <iostream>
# include <algorithm>
using namespace std;
const int N=2000005;
int n,k,ans[N];
char a[N];

int main () {
	scanf ("%d%d",&n,&k);
	scanf ("%s",a+1);
	if (n==1&&k>=1) {
		puts("0");
		return 0;
	}//一定要特判！如果n只有一位且可以修改，那最小必然是0
	for (int i=1;i<=n;i++)
		ans[i]=a[i]-'0';//转成int类型
	int j=1;//j是目前已使用的修改次数
	for (int i=1;i<=n&&j<=k;i++) {
		if (i==1) {//特判第一位，不能为0，那最小就是1
			if (ans[i]!=1)	//但如果它本身就是1，没必要浪费一次修改机会
				ans[i]=1,j++;
		}
		else if (ans[i]!=0) 
			ans[i]=0,j++;//同理，非首位按0处理
	}
	for (int i=1;i<=n;i++)
		printf ("%d",ans[i]);//最后每位输出
	printf ("\n");
	return 0;
}
//By苍空的蓝耀

```


---

## 作者：neil021110 (赞：0)

给出一个数，改变k次后数最小
```cpp
#include<iostream>
using namespace std;
int main(){
	int n,k;
	cin>>n>>k;
	char a[n+1];
	cin>>a;
	for(int i=0;i<n;i++){//要想数最小，从最高位改起
		if(!k)break;//判断修改次数是否用完
		if(n!=1&&i==0&&a[i]!='1'){
			a[i]='1';//最高位最小改1（若n=1可以改0）
			k--;//记录修改次数
		}else if(a[i]!='0'&&(i>0||n==1)){
			a[i]='0';//其他位可改0
			k--; //记录修改次数
		} 
	}
	cout<<a;//输出最小值
}
```


---

## 作者：Li_zi_wei (赞：0)

我记得有[博客宣传](https://lzwblog.tk/)的说法的

**思路很简单——把`最前面前面k-1位全改成0`就可以啦**

### 两个特判:

**1. `n == 1`**

在这种情况下`k == 1`就直接输出`0`

否则（`k == 0`）输出s(就是输入的)

n == 1处理代码

```
	if(n == 1)
	{
		if(k == 1) cout << 0;
		else cout << tmp;//输入的
		return 0;
	}
```

**2. 当n > 1时 `为了防止前导零` 第一位特判**

特判三种情况

一、tmp(第一位)本身就是1 直接输出

二、tmp不是1但k==0 也是直接输出

三、tmp不是1且k>=1 输出1的同时k--；

第一位特判代码:

```
	if(tmp != 1&&k > 0&&n > 1)//当k > 1（就是可以改变数字的时候）
	{
		cout << 1;
		k --;//注意要消耗一次改变数字机会
	}
	else cout << tmp;//k == 0 或者 tmp本身为1
```
#### 总代码

P.S 我采用边读边做

```
#include<bits/stdc++.h>
using namespace std;
int n,k;
char t;//一位一位读
int tmp; 
int main()
{
	cin >> n >> k;
	cin >> t;
	tmp = t - '0';//把读入的char型改为int型方便处理
	if(n == 1)//n == 1特判
	{
		if(k == 1) cout << 0;
		else cout << tmp;
		return 0;
	}
    
	if(tmp != 1&&k > 0&&n > 1)//第一位特判
	{
		cout << 1;
		k --;
	}
	else cout << tmp;
	
	for (int i = 2;i <= n;i ++)//大处理(就是把剩下n-1位的前k-1(或k)位改为0)
	{
		cin >> t;
		tmp = t - '0';
		if(tmp != 0&&k > 0)
		{
			cout << 0;
			k --;
		}
		else cout << tmp;
	}
    
	return 0;
}
```




---

## 作者：封禁用户 (赞：0)

**题目大意：**
给定一个 $n$ 位数 $s$ ，允许改变 $s$ 上的 $k$ 位，求能构成的最小的数是多少。

**思路：**
分情况讨论：
1. 若 $k=0$ 说明 $s$ 的一位数都不能改变，直接输出 $s$ ；
```
if(k==0)
{
	cout<<s;
}
```
1. 若 $n=1$ 说明 $s$ 为一位数，直接输出 0；
```
else if(n==1)
{
	cout<<"0";
}
```
1. $n$ 不为 1 且 $k$ 不为 0，先将 $s$ 的第一位数置为 1，然后再将剩下的位数全部置为 0 即可
```
else
{
        if(s[0]!='1')
        {
            s[0]='1';
            k--;
        }
        for(int i=1;i<=n-1;++i)
        {
            if(k&&s[i]!='0')
            {
                s[i]='0';
                k--;
            }
        }
        cout<<s;
}
```
**完整代码：**
```
#include<bits/stdc++.h>
#define int long long
#define WA_AW using
#define AK namespace
#define IOI std
WA_AW AK IOI;
const int maxn=14e6;
string s;
int n,k;
signed main()
{
    cin>>n>>k>>s;
    if(k==0)
    {
        cout<<s;
    }
    else if(n==1)
    {
        cout<<"0";
    }
    else
    {
        if(s[0]!='1')
        {
            s[0]='1';
            k--;
        }
        for(int i=1;i<=n-1;++i)
        {
            if(k&&s[i]!='0')
            {
                s[i]='0';
                k--;
            }
        }
        cout<<s;
    }
    return 0;
}
```

---

