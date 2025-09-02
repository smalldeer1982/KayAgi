# titech分離

## 题目描述

[problemUrl]: https://atcoder.jp/contests/ttpc2015/tasks/ttpc2015_g

英小文字(a-z)からなる文字列$ S $が与えられる。

$ S $をいくつかの(連続とは限らない)部分文字列に分解する。 つまり、$ S $の各文字がちょうど1つの部分文字列に含まれるように、$ S $から複数の部分文字列を選ぶ。

分解した結果の部分文字列が全て`titech`になるような分解方法があるかどうか判定せよ。

## 说明/提示

### Sample Explanation 1

1つの`titech`に分解できる。

### Sample Explanation 2

例えば、1,2,5,6,7,8文字目と3,4,9,10,11,12文字目に分解すれば2つの`titech`に分解できる。

### Sample Explanation 4

3つの`titech`に分解できる。

## 样例 #1

### 输入

```
titech```

### 输出

```
Yes```

## 样例 #2

### 输入

```
tititechtech```

### 输出

```
Yes```

## 样例 #3

### 输入

```
titecg```

### 输出

```
No```

## 样例 #4

### 输入

```
tttiiittteeeccchhh```

### 输出

```
Yes```

# 题解

## 作者：chl123123 (赞：2)

### 一道基本暴力题

首先，由题目可以知道，如果字符串长度不为 6 的倍数就可以直接输出 No 了。

其次，如果有其他字母也可以直接结束。

最后看字母的顺序符不符合，以及每个字母的数量是不是符合要求，就可以结束了。

上代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
string s;//原字符串
int num;//每个字母应有数量
int t,i,e,c,h;//存储6个字母
int main()
{
	cin>>s;
	if(s.size()%6)//首先判断是否是6的倍数
	{
		cout<<"No"<<endl;
		return 0;
	}
	num=s.size()/6;//记录每个字母应有的数量
	for(int j=0;j<num*6;j++)
	{
		if(s[j]=='t')t++;//记录每个字母实际的数量
		else if(s[j]=='i')i++;
		else if(s[j]=='e')e++;
		else if(s[j]=='c')c++;
		else if(s[j]=='h')h++;
		else//是其他的字母就直接输出
		{
			cout<<"No"<<endl;
			return 0;
		}
		if(t<i||t<e*2||i<e||e<c||c<h||t>num&&i<t-num)//判断字母顺序
		{
			cout<<"No"<<endl;
			return 0;
		}
	}
	if(t!=num*2||i!=num||e!=num||c!=num||h!=num)//对比实际数量
		cout<<"No"<<endl;
	else 
		cout<<"Yes"<<endl;
	return 0;
}
```
最后 [AC](https://www.luogu.com.cn/record/55415067)

---

## 作者：copper_ingot (赞：1)

这题虽然是黄题，但是大概只有橙题的难度。

定义五个整型变量 $t$、$i$、$e$、$c$、$h$，分别记录 `t`、`i`、`e`、`c`、`h` 的数量。以下设 $|s| \div 6 = n$。

存在分解方法的条件有：

- 字符串长度是 $6$ 的倍数。

- 字符串中只包含 `t`、`i`、`e`、`c`、`h` 五种字符。

- $i = e = c = h = n$，且 $t = 2 \times i$。

- 所有字符满足顺序。

最后一条可以理解为，在遍历字符串的任意时刻，总是满足 $t \ge i \ge e \ge c \ge h$ 和 $t \ge e \times 2$，且当 $t > n$ 时 $i \ge t - n$。

直接上代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
string s;
int n, t, i, e, c, h;//变量同上文
int main(){
	cin >> s; n = s.length() / 6;
	if (s.length() != n * 6){//判第一条
		cout << "No" << endl;
		return 0;
	}
	for (int k = 0; k < n * 6; k++){//遍历
		if (s[k] == 't') t++;
		else if (s[k] == 'i') i++;
		else if (s[k] == 'e') e++;
		else if (s[k] == 'c') c++;
		else if (s[k] == 'h') h++;
		else{cout << "No" << endl; return 0;}//判第二条
		if (t < i || t < e * 2 || i < e || e < c || c < h || t > n && i < t - n){
			cout << "No" << endl; return 0;
		}//判第四条
	}
	if (t == n * 2 || i == n || e == n || c == n || h == n) cout << "Yes" << endl;
	else cout << "No" << endl;//判第三条
	return 0;
}
```

---

## 作者：ICU152_lowa_IS8 (赞：1)

本题实际上没有黄的难度，难度和普及组第二题的难度大致相当。

对于此题的做法，其它题解已经讲的很清楚了，在此复述一遍：

1.如果字符串长度不是 $6$ 的倍数，则输出 No；

2.如果字符串中出现了其它的字符，则输出 No；

3.字符需要满足一定的比例关系，如果不满足，输出 No；

4.如果字符不满足顺序（详见代码），输出 No。

如果都满足，则输出 Yes。

本题解与其它题解的不同在于使用了 `switch`，代码如下：

```
#include<bits/stdc++.h>
using namespace std;
int main(){
	string s;
	cin>>s;
	int len=s.length();
	int T=0,I=0,E=0,C=0,H=0;
	if(len%6!=0){
		cout<<"No";
		return 0;
	}
	for(int i=0;i<len;i++){
		switch(s[i]){
			case 't':
				T++;
			break;
			case 'i':
				I++;
			break;
			case 'e':
				E++;
			break;
			case 'c':
				C++;
			break;
			case 'h':
				H++;
			break;
			default:
			cout<<"No";
			return 0;
		}
		if(T<I||T<E*2||I<E||E<C||C<H||T>len/6&&I<T-len/6){
			cout<<"No";
			return 0;
		}
	}
	if(I==E&&E==C&&C==H&&2*H==T){
		cout<<"Yes";
	}
	else{
		cout<<"No";
	}
	return 0;
}
```


---

## 作者：nanatsuhi (赞：1)

## 简单模拟题

整体思路分以下几个部分：

- 由于强制要求含有整数个 $titech$ ，字符串长度必然是 $6$ 的倍数

- 显然地，如果序列合法，含有 $titech$ 的数量是字符串长度的 $\frac{1}{6}$

- 扫一遍整个字符串，根据子串的有序性可以得出一些判断（详见代码）

- 挨个判断每个字符的数量，收工跑路

看了代码想必就明白了 $QwQ$

```cpp
#include <string>
#include <iostream>
#include <map>
using namespace std;
string s;
int main()
{
    cin >> s;
    if (s.length() % 6 != 0)  //第一步的倍数判断
    {
        cout << "No" << endl;
        return 0;
    }
    int titech_num = s.length() / 6;  //第二步计算数量
    map<char, int> m;  //采用映射表存储个数，简单粗暴
    int i = 0;
    for (; i < titech_num * 6; i++)  //最重要的第三步
    {
        m[s[i]]++;  //统计字符的个数
        if (m['t'] < m['i'] ||  //t比i少
            m['t'] < m['e'] * 2 ||  //t比e少（有两个t）
            m['i'] < m['e'] ||  //i比e少
            m['e'] < m['c'] ||  //e比c少
            m['c'] < m['h'] ||  //c比h少
            (m['t'] > titech_num &&  //t比总个数多且i比t减总个数多
             m['i'] < m['t'] - titech_num))
            break;  //以上几种情况都得跑路（
    }
    if (i < titech_num * 6 ||  //第四步，挨个判断
        m['t'] != titech_num * 2 ||
        m['i'] != titech_num ||
        m['e'] != titech_num ||
        m['c'] != titech_num ||
        m['h'] != titech_num)
    {
        cout << "No" << endl;  //错了就跑路
    }
    else
    {
        cout << "Yes" << endl;  //剩下的情况合法
    }
    return 0;
}
```


---

## 作者：Amberhart (赞：0)

[传送门](https://www.luogu.com.cn/problem/AT_ttpc2015_g)

思路：

1. 特判，如果长度不是 $6$ 的倍数直接输出 `No`；

2. 循环统计 `titech` 中每个字母出现的次数；

3. 判断字母顺序；

4. 判断个数是否正确。

上代码，解释都在代码里：

```cpp
#include <bits/stdc++.h>
using namespace std;
string s;
int t,i,e,c,h;
int main(){
	cin>>s;
	//特判，长度不是6的倍数肯定不能分解几组或一组
	if(s.size()%6!=0){
		cout<<"No";
		return 0;
	}
	for(int k=0;k<s.size();k++){//注意下标不能与计数变量重复
		if(s[k]=='t') t++;
		else if(s[k]=='i') i++;
		else if(s[k]=='e') e++;
		else if(s[k]=='c') c++;
		else if(s[k]=='h') h++;
		else{//不是'titech'里的字符，输出'No'
			cout<<"No\n";
			return 0;
		}
		//t在'titech'出现了2次，所以判断的时候得是t<e*2
		if(t<i||t<e*2||i<e||e<c||c<h||t>s.size()/6&&i<t-s.size()/6){//判断字母顺序，不对输出No
			cout<<"No\n";
			return 0;
		}
	}
	if(t==i*2&&i==e&&e==c&&c==h&&i==s.size()/6){//t在'titech'里出现了2次，所以是i*2，其他个数相等就能组成多组或一组'titech'
		cout<<"Yes\n";
	}else{
		cout<<"No\n";
	}
	return 0;
}

```


---

## 作者：rzm120412 (赞：0)

### 前言：

**这是一道简单的暴力题**。

难度大概 j 组 T1 到 T2。

### 思路：

如果长度不是 6 直接输出 ```No``` 即可。

如果有其他字母直接输出 ```No``` 即可。

最后在统计个数和顺序判断即可。

### 你们喜欢的代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
string s;
int a[6];
int main(){
	cin>>s;
	if(s.length()%6){
		cout<<"No"<<endl;
		return 0;
	}
	for(int i=0;i<s.length();i++){//数个数 
		if(s[i]=='t'){
			a[1]++;
		} 
		else if(s[i]=='i'){
			a[2]++;
		} 
		else if(s[i]=='e'){
			a[3]++;
		} 
		else if(s[i]=='c'){
			c++;
		} 
		else if(s[i]=='h'){
			h++;
		} 
		else{
			cout<<"No"<<endl;
			return 0;
		}
		if(a[1]<i||a[1]<a[3]*2||a[2]<a[3]||a[3]<c||c<h||a[1]>s.length()/6&&a[2]<a[1]-s.length()/6){
			cout<<"No"<<endl;
			return 0;
		}
	}
	if(a[1]!=s.length()/6*2||a[2]!=s.length()/6||a[3]!=s.length()/6||a[4]!=s.length()/6||a[5]!=s.length()/6){//按题目比例 
		cout<<"No"<<endl;
	} 
	else{
		cout<<"Yes"<<endl;
	} 
	return 0;
}
```

---

## 作者：mz2022 (赞：0)

[我是传送门](https://www.luogu.com.cn/problem/AT_ttpc2015_g)

思路：
--------
一道很适合新手的简单模拟题。

容易分析出字符串如果成立，满足以下条件：

$1$：字符段总长度为 $6$ 的倍数。

$2$：字符串应该只含有 $\texttt t$、$\texttt i$、$\texttt e$、$\texttt c$、$\texttt h$。

$3$：$\texttt t$、$\texttt i$、$\texttt e$、$\texttt c$、$\texttt h$ 是按条件字符串的序出现的。

$4$：含有的 $\texttt t$、$\texttt i$、$\texttt e$、$\texttt c$、$\texttt h$ 数量满足一定比例关系，具体见代码。

Code：
--------
```cpp
#include<bits/stdc++.h>
using namespace std;
char s[105];
int main()
{
	cin>>s;
	int tt=0,ii=0,ee=0,cc=0,hh=0;
	if(strlen(s)%6!=0)//条件1
	{
		cout<<"No"<<endl;
		return 0;
	}
	for(int i=0;i<strlen(s);i++)
	{
		if(s[i]=='t')tt++;
		else if(s[i]=='i')ii++;
		else if(s[i]=='e')ee++;
		else if(s[i]=='c')cc++;
		else if(s[i]=='h')hh++;
		else//条件2
		{
			cout<<"No"<<endl;
			return 0;
		}
		if(tt<ii||tt<ee*2||ii<ee||ee<cc||cc<hh||(tt>strlen(s)/6&&ii<tt-strlen(s)/6))//条件3
		{
			cout<<"No"<<endl;
			return 0;
		}
	}
	if(ii==ee&&ee==cc&&cc==hh&&tt==ii*2&&ii==strlen(s)/6)//条件4，满足比例关系2：1：1：1：1
	{
		cout<<"Yes"<<endl;
		return 0;
	}
	cout<<"No"<<endl;
	return 0;
}
```

---

## 作者：Silence_World (赞：0)

# 思路

题意很简单，在这里不多解释。

比较好想的一道暴力，我们先考虑什么情况不能完成条件。

首先，除了 titech 的其他字符肯定是不能出现的，如果总长度不是 6 的倍数也可以直接舍去。

其次，所有字母必须按顺序出现，互相制约，也就是每个字母出现的数量一定要大于下一个，且 t 出现的数量要比 titech 出现的数量少（为总长度除以 6），又
 i 出现的数量要比 t 出现的数量 $-$ titech 出现的数量多，这样才满足条件。
 
 最后再判断一下每个字母出现的数量是否一致能组成 titech，能的话直接输出 Yes 就可以了，收工。
 
 注意要输出换行，我 wa 了好多次（哭）
 
#  代码

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[1005][1005];
int dp[1005][1005];
main(){
	string s;
	cin>>s;
	if(s.length()%6!=0){
		cout<<"No"<<endl;
		return 0;
	} 
	int t=0,i=0,e=0,c=0,h=0;
	for(int j=0;j<s.length();j++){
		if(s[j]=='t')t++;
		else if(s[j]=='i'){i++;}
		else if(s[j]=='e'){e++;}
		else if(s[j]=='c'){c++;}
		else if(s[j]=='h'){h++;}
		else {cout<<"No"<<endl;return 0;}
		if(t<i or t/2<e or e<c or c<h or (t>s.length()/6 and i<t-s.length()/6)){cout<<"No"<<endl;return 0;}
	}
	if(t/2==i and i==e and e==c and c==h and h==s.length()/6){
		cout<<"Yes"<<endl;
	}
	else{
		cout<<"No"<<endl;
	}
} 
```


---

## 作者：volatile (赞：0)

洛谷的 RMJ 总是 UKE，所以这一题是在 ATcoder 上做的，[记录一](https://atcoder.jp/contests/ttpc2015/submissions/44132887)，[记录二](https://atcoder.jp/contests/ttpc2015/submissions/44133427)。

## 思路一

首先字符串长度一定是 $6$ 的倍数，然后判断是否只有 $t$、$i$、$e$、$c$、$h$ 这五个字符，最后统计一下字符个数就行了。

代码（错误）：

```cpp
#include<iostream>
#include<string>
using namespace std;
int main()
{
	string a;
	int t=0,i=0,e=0,c=0,h=0;
	cin>>a;
	if(a.size()%6!=0){
		cout<<"No\n";
		return 0;
	}
	for(int s=0;s<a.size();s++){
		if(a[s]=='t') t++;
		else if(a[s]=='i') i++;
		else if(a[s]=='e') e++;
		else if(a[s]=='c') c++;
		else if(a[s]=='h') h++;
		else{
			cout<<"No\n";
			return 0;
		}
	}
    if(t==a.size()/6*2&&i==a.size()/6&&e==i&&c==e&&h==c) cout<<"Yes\n";
	else cout<<"No\n";
    return 0;
}
```

![](https://cdn.luogu.com.cn/upload/image_hosting/e7sj1gno.png)

## 思路二

原因是因为少了判断字符的顺序，那么怎么判断字符的顺序呢？

1. 如果 $t$ 比 $i$ 少，输出 `No`。

2. 如果 $t$ 比 $e$ 少（由于 $e$ 前面会有两个 $t$ 所以 $e$ 的个数要乘 $2$），输出 `No`。

3. 如果 $i$ 比 $e$ 少，输出 `No`。

4. 如果 $e$ 比 $c$ 少，输出 `No`。

5. 如果 $h$ 比 $c$ 少，输出 `No`。

6. 如果 $t$ 比字符串 `titech` 的数量多并且 $i$ 比 $t$ 减去字符串 `titech` 的数量少，输出 `No`。

代码：

```cpp
#include<iostream>
#include<string>
using namespace std;
int main()
{
	string a;
	int t=0,i=0,e=0,c=0,h=0;
	cin>>a;
	if(a.size()%6!=0){
		cout<<"No\n";
		return 0;
	}
	for(int s=0;s<a.size();s++){
		if(a[s]=='t') t++;
		else if(a[s]=='i') i++;
		else if(a[s]=='e') e++;
		else if(a[s]=='c') c++;
		else if(a[s]=='h') h++;
		else{
			cout<<"No\n";
			return 0;
		}
		if(t<i||t<e*2||i<e||e<c||c<h||(t>a.size()/6&&i<t-a.size()/6)){
			cout<<"No\n";
			return 0;
		}
	}
	if(t==a.size()/6*2&&i==a.size()/6&&e==i&&c==e&&h==c) cout<<"Yes\n";
	else cout<<"No\n";
    return 0;
}
```

![](https://cdn.luogu.com.cn/upload/image_hosting/hnpxi40y.png)

---

## 作者：so_find_skind (赞：0)

[传送门！](https://www.luogu.com.cn/problem/AT_ttpc2015_g#submit)

## 本题思路

对于一个字符串，如果可以满足题目中的条件，那么必然满足如下几条：

- 字符串长度是 6 的倍数；
- 不会出现任何与条件字符串 `titech` 相违的字符；
- `t`、`i`、`e`、`c`、`h` 的数量相等且按照条件字符串的顺序出现。

那么怎么判断顺序呢？也不难，我们只需判断是否每个字符的后面都有在条件字符串中在它后面的字符即可，**特别的，这些字符后面判定成立的字符是绝对绝对绝对不能重复的**。

## 代码环节

~~~
#include <bits/stdc++.h>
using namespace std;
int t,i,e,c,h,num;
string s;
int main(){
	cin>>s;
	if(s.size()%6!=0){
		cout<<"No"<<endl;
		return 0;
	}
	num=s.size()/6;
	for(int j=0;j<num*6;j++){
		if(s[j]=='t')
		    t++;
		else if(s[j]=='i')
		    i++;
		else if(s[j]=='e')
		    e++;
		else if(s[j]=='c')
		    c++;
		else if(s[j]=='h')
		    h++;
		else{
			cout<<"No\n";
			return 0;
		}
		if(t<i || t<e*2 || i<e || e<c || c<h || t>num && i<t-num){
			cout<<"No\n";
			return 0;
		}
	}
	if(t!=num*2 || i!=num || e!=num || c!=num || h!=num)
		cout<<"No"<<endl;
	else 
		cout<<"Yes"<<endl;
	return 0;
}
//照着别的大佬题解打的勿喷
~~~

也祝福各位看过此题解的 OIer 们都能够秒过黑题！

完结撒花！

---

## 作者：Anaxagoras (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT1492)

### 0x01 思路

首先，如果字符串长度不是 6 的倍数，那就一定不能成功。

其次，如果有除 `t`，`i`，`e`，`c`，`h` 以外的字母也不可以成功。

然后，如果最后 `i`，`e`，`c`，`h` 的数量不等于字符串长度除以 6，`t` 的数量不等于长度除以 3，也不行。

最后就是下面这些条件，只要存在一个也一定不能成功：

1. `t` 的数量小于 `i`；

1. `t` 的数量小于 `e` 的两倍；

1. `i` 的数量小于 `e`；

1. `e` 的数量小于 `c`；

1. `c` 的数量小于 `h`；

1. `t` 的数量小于长度除以 6 并且 `i` 的数量小于 `t` 减去长度除以 6；

用计数器在枚举时累加并按上述条件判断即可。

### 0x02 AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,i,/*t,*/e,c,h,len;
string st;
int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin>>st;
  len=st.size();
  if(len%6)
    {
      cout<<"No\n";
      return 0;
    }
  for(int j=0;j<len;j++)
    {
      switch(st[j])
        {
        case 't':
          {
            t++;
            break;
          }
        case 'i':
          {
            i++;
            break;
          }
        case 'e':
          {
            e++;
            break;
          }
        case 'c':
          {
            c++;
            break;
          }
        case 'h':
          {
            h++;
            break;
          }
        default:
          {
            cout<<"No\n";
            return 0;
          }
        }
      if(t<i||t<e*2||i<e||e<c||c<h||(t>len/6&&i<t-len/6))
        {
          cout<<"No\n";
          return 0;
        }
    }
  if(t!=len/3||i!=len/6||e!=len/6||c!=len/6||h!=len/6)
    {
      cout<<"No\n";
      return 0;
    }
  cout<<"Yes\n";
  return 0;
}

```

--- The End ---

---

## 作者：Mr_WA的大号 (赞：0)

不写题目，焉得估值。小学生又来发题解了！

题号：AT1492

难度：★★★★

算法：暴力

## 开课了！

这一题总体上是一道很难的题目。大家应该都知道，这题要枚举。问题是怎么枚举呢？接下来我就来将这个问题。

这题的枚举当然是从开头开始查找，当时中途我们要加入一些特别的判断。如果判断对了，就要退出，不必继续查找了。如下：

1.t的个数小于i的个数

2.t的个数小于e的个数的两倍

3.e的个数小于c的个数

4.c的个数小于h的个数

5.i的个数小于c的个数

6.t的个数大于titech能产生的个数**并且**i的个数小于t-titech能产生的个数

这样子一直枚举，到了循环结束后，再判断每个字母的个数是否等于它应出现的个数，是就输出Yes，否则输出No。

**注意：我们有一种方法能加速：那就是在枚举开始前判断字符串的长度是否是6的倍数，否就输出No。**

课讲完了，上代码：
```cpp
#include<iostream>
#include<fstream>
#include<cstdio>
#include<cmath>
#include<queue>
#include<string>
#include<cstring>
#include<string.h>
#include<algorithm>
#include<iomanip>
using namespace std;
string st;
int num;
int t,i,e,c,h;
int main()
{
	cin>>st;
	if(st.size()%6!=0)//判断是否为6的倍数
	{
		cout<<"No"<<endl;
		return 0;
	}
	num=st.size()/6;//算出总个数
	for(int kkk=0; kkk<num*6; kkk++)//开始枚举
	{
		if(st[kkk]=='t')t++;
		if(st[kkk]=='i')i++;
		if(st[kkk]=='e')e++;
		if(st[kkk]=='c')c++;
		if(st[kkk]=='h')h++;//统计t、i、e、c、h的个数
		if(t<i)break;
		if(t<e*2)break;
		if(i<e)break;
		if(e<c)break;
		if(c<h)break;
		if(t>num&&i<t-num)break;//判断
	}
	if(t!=num*2||i!=num||e!=num||c!=num||h!=num)cout<<"No"<<endl;//最后判断是否成立
	else cout<<"Yes"<<endl;
	return 0;
}
```
祝大家能AC!

---

