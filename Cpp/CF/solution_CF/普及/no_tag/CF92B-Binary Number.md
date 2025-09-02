# Binary Number

## 题目描述

小海狮牙牙非常喜欢学数学。因此，他在无聊的时候经常用数字做♂游♂戏。

牙牙拿了一些正整数 _x_ ， 他想通过一些操作将 _x_ 变成1。当 _x_ 不等于1的时候，牙牙会重复下列步骤：如果 _x_ 为奇数，他就会将 _x_ 加上1。如果 _x_ 为偶数，他就会将 _x_ 除以2。牙牙想知道他需要多少步才能将 _x_ 变为1。

## 样例 #1

### 输入

```
1
```

### 输出

```
0
```

## 样例 #2

### 输入

```
1001001
```

### 输出

```
12
```

## 样例 #3

### 输入

```
101110
```

### 输出

```
8
```

# 题解

## 作者：cyffff (赞：6)

# CF92B Binary Number
#### [ _传送门_ ](https://www.luogu.com.cn/problem/CF92B)
## 思路
首先，这道题的输入为一个长度为$10^6$以内的二进制数（01串）。

由于这个数太大了，转成十进制处理根本存不下，我们就只能用$char\enspace[\enspace]$或者$string$存~~我才不会告诉你我用char的原因是可以scanf快速读入~~。

我们可以用一个整形存下现在操作的一位，记它为$x$,

如果$a[x]$是$\begin{cases}0&x--\\1&a[--x]++\\2&a[--x]++\end{cases}$

我们来解释一下上面的操作。

如果这一位（最后一位）是 $0$，代表它是偶数，应该除以 $2$，而在二进制中，除以 $2$就是右移一位，在字符数组里就是将最后一位省去，即$x--$。

如果它是 $1$，代表它是奇数，应该加 $1$，加一会让这一位变成 $2$，满二进一，则为前一位加 $1$，即$a[--x]++$（将$a[x]='0';a[x-1]++;$省略成一步，需要注意，这里由于省略了这一步为 $0$时，操作数要另外加 $1$）

因为这个数本身的最大值为 $1$，而上一位最多向这一位进一，所以每一位的最大值为 $2$。

当这一位为 $2$ 时，代表后面的数向这一位进了 $1$，且它本身为 $1$，接下来见 $1$ 的操作即可（需要注意，这一步并没有省略把自己设为 $0$ 一步，不需要额外加一次操作次数）。

需要注意，当这个串的长度为 $1$ 时（$x=1$时），$a[x]$ $\begin{cases}1& cout<<n; \\2&cout<<++n;\end{cases}$

最后一位为 $2$ 代表这个串为 $10$，按操作即为$n++;i--;$，所以操作数要加 $1$ 。

现在上AC代码~

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
char a[N];
int n;
int main(){
	scanf("%s",a);
	int i=strlen(a+1);
	while(i){
		n++;
		switch(a[i]){
			case '0':{//0的操作
				i--;//直接省略后面一位
				break;
			}
			case '1':{
			    n++;//额外加操作次数
				a[--i]++;//向前进位
				break;
			}
			case '2':{
				a[--i]++;//向前进位
				break;
			}
		}
	}
	if(a[i]=='2'){
		n++;
	}
	printf("%d",n);
	return 0;
}
```
那这就再见了qwq

---

## 作者：LYqwq (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF92B)
# 题目大意
给定一个二进制数 $x$，有两种操作：
1. 如果 $x$ 为奇数，将 $x$ 加 $1$。
2. 如果 $x$ 为偶数，将 $x$ 除以 $2$。

求将 $x$ 变为 $1$ 的操作次数。

# 思路
先来看存储问题。最简单的想法就是直接将二进制转换成整数，但是请看数据范围：$x$ 的位数不超过 $10^6$。也就是说，这个数最大为 $2^{10^6}$ 连`__uint128_t`也存不下。  
那么就只能使用一个 $char$ 类型数组 $s$ 存放二进制数了，操作数最大应该为 $10^6 \times 2$，也就是操作这么多次，时间复杂度 $\mathcal{O}(10^6 \times 2)$ 可以过。  
直接按照题意模拟就行。  
使用一个变量 $p$ 记录二进制数在 $s$ 中最后一位的位置，每次操作时要做相应的修改，例如除以二，直接舍去最后一位，使 $p$ 加一即可。$ans$ 记录操作次数，也就是最后的答案。  
只要 $p$ 不为 $0$，也就是 $s$ 的位数不止 $1$ 位了，这个数就不为 $0$，我们就需要对它进行操作。  

如何判断奇数和偶数呢？是个问题，我们来找找规律。  
- 二进制数 `101`，十进制 $5$，是奇数。  
- 二进制数 `1000`，十进制 $8$，是偶数。  
- 二进制数 `1010`，十进制 $10$，是偶数。  
- 二进制数 `1011`，十进制 $11$，是奇数。  
- 二进制数 `11101`，十进制 $29$，是奇数。  
- ......

你会发现，所有最后一位为 $1$ 的二进制数都是奇数，其余都为偶数。  
我们只要判断 $s$ 的最后一位 $s_p$ 是 $1$ 还是 $0$ 就可以知道 $x$ 是奇数还是偶数了。

那么除以 $2$ 呢？二进制除以 $2$ 就等于右移一位。  
这里告诉大家一个小技巧：如果想让一个数除以 $2^n$ 次方，就可以让它右移 $n$ 位。如果想让一个数乘 $2^n$ 次方，就可以让它左移 $n$ 位。  
众所周知，位运算比普通运算快。


## 操作1：如果 $x$ 为奇数，将 $x$ 加 $1$。
如果 $x$ 是奇数，那么最后一位一定是 $1$，再加上 $1$，就一定会进位。  
因此，我们将 $s_p$ 置为 $0$，$s_{p-1}$ 加上 $1$。  
我们简单一点，$s_p$ 为 $0$ 了，那就是偶数情况，可以直接除以 $2$ 并让操作次数 $ans$ 加 $1$，不需要在下一次循环再除以 $2$ 了，省些时间。  
```cpp
case '1': s[p-1]++; s[p]=0; p--; ans++; break;
```
你会发现，这样的话 $s_{p-1}$ 可能为 $2$，也就是二进制`10`，这不会 $WA$ 吗？  
别急，很简单，我们每次操作时，判断一下当前值为 $2$ 的情况，如果为 $2$，就让 $s_{p-1}$ 加上 $1$，因为当前这个数为`10`，前一位也有份。  
加上之后，这一位要减 $2$，因为二进制第 $n$ 位的值为 $2^n \times x_n$，$n$ 的初始下标为 $0$。这样的话这一位就只剩 $0$ 了。  
呃不对啊，这不是也算了一次操作次数吗？没事，进行这个操作后，$s_p$ 为 $0$，可以直接除以 $2$ 来补上这次操作。  
```cpp
case '2': s[p-1]++; s[p]-=2; p--; break;
```

嘿嘿，好像很简单的样子，我们可以对代码简化一下。
- 对于奇数情况加 $1$，我们不用管当前 $s_p$，不需要真的置 $0$，直接先让 $x$ 除以 $2$，也就是 $p$ 减 $1$，再将现在的 $s_p$ (也就是原来的 $s_{p-1}$)加 $1$。  
前三句代码可直接化为一句`s[--p]++`。  
```cpp
case '1': s[--p]++; ans++; break;
```
- 对于当前 $s_p$ 为 $2$ 的情况，同理，既然要除以 $2$，就不用管原来的 $s_p$ 了，化简代码如下。  
```cpp
case '2': s[--p]++; break;
```

## 操作2：如果 $x$ 为偶数，将 $x$ 除以 $2$。
这个就很简单了，直接将 $p$ 减 $1$ 就行了。  
```cpp
case '2': p--; break;
```

## 注意
当只剩一位数时，奇数操作可能让这一位数是 $2$，我们在循环结束时需要判断一下，如果是，`ans++`就行了。

# 代码
```cpp
#include <iostream>
#include <cstring> // strlen函数
using namespace std;

int main(){
    int p,ans=0; // p：pos简称，记录最后一位在哪；ans：记录操作次数
	char s[1000005];
    cin >> s;
    p=strlen(s)-1; // 取长度-1，刚好有值
    while(p){ // 只要下标不为0，就说明可以操作，位数为0，就是1或2
        ans++; // 每次循环操作一次，ans++
        switch(s[p]){ // 不想写if
            case '0': p--; break; // 除以二，直接舍弃最后一位
            case '1': s[--p]++; ans++; break; // 相当于除以二了，所以再加一次答案
            case '2': s[--p]++; break; // 进位操作，2代表当前位为“10”，当前值为0，所以将上一位加一后舍弃就行了
            default: break; // 写不写都没事，但是我习惯写一下
        }
    }
    if(s[p]=='2') ans++; // 如果是2，这个二进制就有两位，要除以2，所以ans++
    cout << ans << endl;
	return 0;
}
```

---

## 作者：时律 (赞：2)

来一个简洁的模拟吧。

真的很简洁，只有17行qwq

解释放代码里

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	string a;
	int ans=0,i;
	cin>>a;
	i=a.size()-1;//现在的末尾的下标
	while(i>0)
	{
		if(a[i]=='2') ans++,i--,a[i]++;//如果是2的话，表示是原本为1加上了上一位进上来的1，所以直接移到下一位，同时下一位也要+1
		else if(a[i]=='1') ans++,a[i-1]++,a[i]='0';//如果是1，把目前这位变为0，然后把下一位+1做一个标记。
		else if(a[i]=='0') ans++,i--;//如果是0直接到下一位了
	}
	if(a[i]=='2') ans++;//这样的做法可能出现最后a[0]='2'的情况，这时答案+1即可。
	cout<<ans;
}
```

---

## 作者：DPseud (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF92B)

本题就是二进制模拟，但是要注意，数据范围过大，我们不能用数来存放，只能使用字符数组。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	string s;
	static char c[1111111];//将数组定为static型以保证不会出现随机字符
	cin>>s;
	int sum=0;
	long long len=s.length();//定义一个变量存放可变的数组长度
	for(int i=0;i<len;i++)c[i]=s[i];//将输入的字符串转为字符数组
	if(c[0]=='1'&&len==1){cout<<0;return 0;}//特判
	while(len>1){
		if(c[len-1]=='2')sum++,len--,c[len-1]++;
		if(c[len-1]=='1')c[len-1]='0',c[len-2]++,sum++;//是奇数，加1，即从01变成10
		if(c[len-1]=='0')len--,sum++;//是偶数，除以二，即左移一位
	}
	if(c[len-1]=='2')sum++;
	cout<<sum;
	return 0;
}
```


---

## 作者：hensier (赞：1)

做本题自然可以想到多种方法。

【方法$1$：暴力】

新建一个$\text{unsigned long long}$类型的变量$x$和一个$\text{string}$变量$s$。输入$s$，并将$s$转换为十进制，保存在$x$中。这仅能应付部分测试点（对于$\text{CF}$来说，只有全对和错误之分，所以这不可取）。

【方法$2$：朴实的模拟】

对于这个字符串$s$，末位为$1$就加$1$，具体方法参见$add$函数。如果末位为$0$就直接抹掉末位。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int step;
string add(string a)
{
    int pos=a.size()-1;
    a[pos]++;//先末位加1
    while(a[pos]=='2')//把数位为2的变为0，前一位加1，实现进位
    {
        if(!pos)break;
        a[pos]='0';
        a[--pos]++;
    }
    if(!pos)//特判全是1的情况
    {
        a[pos]='0';
        a="1"+a;
    }
    return a;
}
int main()
{
    cin>>s;
    while(s!="1")
    {
        if(s[s.size()-1]^48)//判断末位是否为1
        {
            s=add(s);
            step++;//执行加1，计数器加1
        }
        while(s[s.size()-1]=='0')//只要末位为0，就一直抹掉末位
        {
            s.erase(s.size()-1,1);
            step++;
        }
    }
    cout<<step;
    return 0;
}
```

这样的代码只能撑到测试点$12$，第$13$个点就超时了。

【方法$3$：字符串+指针处理】

定义一个指针$pos$，初始赋值为$|s|-1$（$|s|$为$s$的大小）。每一次处理计数器加$1$，对于末位：

- 当末位为$0$时，该位已经处理完，$pos$减1

- 当末位为$1$时，将该位赋值为$0$，把$pos-1$对应的字符加1

- 当末位为$2$时，$pos$先减1，然后$pos$位置加$1$

当然最后需要特判——如果$s_0$为$2$，则计数器加$1$（此时有进位）。最后输出计数器数值即可。

$AC$代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int pos,ans;
int main()
{
    cin>>s;
    pos=s.size()-1;//初始化指针
    while(pos)//当指针不为0，即大于0的时候就继续操作
    {
        ans++;//计数器加1
        switch(s[pos])//分类讨论
        {
            case '1':
            {
                s[pos]='0';
                s[pos-1]++;
                break;
            }
            case '2':
            {
                s[--pos]++;
                break;
            }
            default:pos--;
        }
    }
    if(s[0]=='2')ans++;//特判
    printf("%d",ans);
    return 0;
}
```

---

## 作者：仗剑_天涯 (赞：1)

这题是二进制
~~（谁都看得出来吧）~~

思路：

1.一个位上如果是2（相当于十进制中的10），就说明它原来是1上一位进位1,则进位到下一位，答案加一。

2.如果是1，下一次就不用做了，把这位变成0，下一位加一，答案加一

3.如果是0，那就直接到下一位，答案加一。

最后，特判第一位是2的情况，是则触发进位，答案加一。

代码：

```cpp

#include<bits/stdc++.h>
using namespace std;
int ans,i,n,m,st1[1000010];
string st;
void doit()
{
    cin>>st;
    i=st.size()-1;
    for(int j=0;j<=i;j++)
    {
    	st1[j]=st[j]-'0';
    }
    while(i>0)
    {
        if(st1[i]==2)//判断是2
        {
            ans++;
            st1[i-1]++;
        }
        else 
        {
            if(st1[i]==1)//判断是1
            {
                ans++;
                st1[i-1]++;
                st1[i]=0;
                i++;
            }
            else 
            {
                if(st1[i]==0)//判断是0
                {
                    ans++;
                }
            }
        }
        i--;
        
    }
    if(st1[i]==2) ans++;//特判首位2
    cout<<ans;
}
int main()
{
	doit();
   return 0;
}
```


---

## 作者：_Dreamer_ (赞：0)


[传送门](https://www.luogu.com.cn/problem/CF92B)

注意到 x 的位数不超过 $10^6$ 可以接受 $O(n)$ 的时间复杂度

考虑模拟

流程 : 

- 如果这一位是 1 向前进一 ans+1
- 如果这一位是 2 (上一步进位来的) 把这一位进上去 按 0 处理
- 如果这一位是 0 ans+1 向前移动一下指针

复杂度是 $O(n)$ 的

```cpp
#include<bits/stdc++.h>
using namespace std;
int ans=0;
string a;
int main()
{
	cin>>a;
	int i=a.size()-1;
	while(i)
	{
		if(a[i]=='2')ans++,i--,a[i]++;
		else if(a[i]=='1')ans++,a[i]++;
		else if(a[i]=='0')ans++,i--;
	}
	if(a[i]=='2')ans++;
	cout<<ans;
	return 0;
}
```


---

## 作者：Gmt丶FFF (赞：0)

对于一个二进制数，+1 是若最后一个数是 1 ，则变为 0 ，若为 0 ，则变为 1 ，直到遇到第一个 0 。而 /2 是将最后一个0去除。

判断一个二进制数奇偶性，若最后一位为 1 ，则为奇数，反之为偶数。

所以可以从最后一位往前枚举，发现 0 可以直接 /2 而发现 1 要先 +1 再 /2 。

可以很容易的发现，遇到第一个 1 后，后面就不存在纯粹的遇见 0 然后 /2 ，所以这是个临界点。

并且在倒数第二位时如果加上了 1 且倒数第二位是 1 ，那么会凭空多出一位，所以要特殊判断一次。

代码附上

```
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
char s[1000005];
int main()
{
	scanf("%s",s);
	int len=strlen(s)-1;
	bool ss=0;
	int k=0;
	for(int i=len;i>0;i--)
	{
		if(!ss)
		{
			if(!(int)(s[i]-48))k++;
			else k+=2,ss^=1;
		}
		else
		{
			if(!(int)(s[i]-48))k+=2;
			else k++;
		}
	} 
	if(ss&&(s[0]-48))k++;
	printf("%d",k);
	return 0;
}
```


---

## 作者：Insouciant21 (赞：0)

做这题前可以先看一看[P2104](https://www.luogu.com.cn/problem/P2104)

对于一个二进制数

我们将其每一位都存在`vector`中

当末位为 $1$ 时，该二进制数为奇数，对其进行 $+1$ 操作

注意： 数据可能会出现需要最高位进行进位

如 $111_{2}+1_{10}=1000_{2}$

当末位为 $0$ 时，该二进制数为偶数，对其进行 $\div 2$ 操作

在二进制中， $\div 2$ 即为右移一位

$ 1000_{2}\div2_{10}=100_{2} $

AC代码如下

``` cpp
#include <bits/stdc++.h>

using namespace std;

vector<int> num;
int ans;

void add(int p) {
    num[p]++;
    if (num[p] == 2 && p != 0) { // 向前直到无需进位
        num[p] = 0;
        add(p - 1);
    }
    else if (num[p] == 2 && p == 0) { // 最高位进位
        num[p] = 0;
        num.insert(num.begin(), 1); // 最前面插入一位
    }
    return;
}

int main() {
    string x;
    cin >> x;
    for (int i = 0; i < x.length(); i++) num.push_back(x[i] - '0');
    while (num.size() != 1) { // 直到只剩下一位
        if (num.back() == 1)
            add(num.size() - 1);
        else
            num.pop_back();
        ans++;
    }
    cout << ans << endl;
    return 0;
}
```



---

## 作者：666DHG (赞：0)

当时我第一眼看到这道题时，我的思路如下：

1. 把二进制数转成十进制数
2. 模拟

然后就[TLE了](https://www.luogu.org/record/23786072)

后来我看了一下数据范围：

>第一行包含一个二进制的整数$\text{ }x\text{ }$。可以保证它的的第一位不是$\text{ }0\text{ }$而且$\text{ }x\text{ }$的位数不超过$\text{ }10^6\text{ }$。

~~fAKe!!!~~

一天后，当我再次打开这道题时，突然间有思路了！！！

思路2.0如下：

1. 读入，并把其存在一个数组中，并新建一个变量$\text{ }len\text{ }$来存储**当前数的长度$\text{ }-1\text{ }$**

2. 重复循环直到$\text{ }len==0\text{ }$，即只剩下一位数$\text{ }1\text{ }$

3. 如果末尾（即$\text{ }num[len]\text{ }$）为$\text{ }0\text{ }$，说明是偶数，除以$\text{ }2\text{ }$

> 技巧一：在二进制中，除以二相当于**删掉末尾（即$\text{ }num[len]\text{ }$）**，可以到$\text{计算器}\rightarrow\text{程序员}$来试验

> 技巧二：在检测到$\text{ }num[len]\text{ }$为$\text{ }0\text{ }$时，可以继续检测$\text{ }num[len-1]\text{ }$，$\text{ }num[len-2]......\text{ }$是否为$\text{ }0\text{ }$。

4. 如果末尾（即$\text{ }num[len]\text{ }$）为$\text{ }1\text{ }$，说明是奇数，加$\text{ }1\text{ }$

> 技巧：当$\text{ }num[len]\text{ }$为$\text{ }1\text{ }$时，加上$\text{ }1\text{ }$会变为$\text{ }0\text{ }$。这时，可以**顺便除以一个$\text{ }2\text{ }$，并$\text{ }len--\text{}$**。如此循环，**直到$\text{ }len\text{ }$为$\text{ }0\text{ }$或$\text{ }num[len]\text{ }$不为$\text{ }1\text{ }$。**~~也算是玄学优化中的一种吧QAQ~~

源代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;

int ans,len;
char num[1000005];

int main()
  {
	scanf("%s",num);
	len=strlen(num)-1; // len 用来存储二进制数的长度-1，可以理解为当前最大的下标
	while (len&&++ans)
	  {
		if (num[len]=='0') while(num[--len]=='0') ans++; // 在去除 num[len] 时顺便看看能不能去除 num[--len] 
		else
		  {
			ans++; //给这个数 +1
			while (--len&&num[len]=='1') ans++; // 当 len 不为 0 且 num[len]=='1' 时，说明前一位加一可以进位，顺便除以二并 len-- 
			if (len) num[len]='1'; // 如果 len 不为 0 ，说明前面还有数，并把这一位不为1的数位改成1
			else ans++;
		  }
	  }
	printf("%d",ans);
	return 0;
  }
```

---

## 作者：RioBlu (赞：0)

用数组模拟即可
___
代码如下
```
#include<bits/stdc++.h>
using namespace std;
long long a,head,tail,ans;
char U;
short n[2000005],m[2000005];
int main()
{
    while(cin>>U)//输入
    {
        n[head]=U-'0';
        ++head;
    }
    for(int s=head-1;s>=0;s--)//准备把数组翻转
    {
        m[head-s-1]=n[s];
    }
    for(int s=head-1;s>=0;s--)//替换
    n[s]=m[s];
    while(head-tail>1)
    {
        if(n[tail])//末尾是1
        {
            a=tail;
            n[a]++;//进位
            ans++;//答案++
            while(n[a]==2&&a<head)//是否能进位
            {
                n[a]=0,n[a+1]++;
                if(n[a+1]==head)head++;//如果位数变大了
                a++;
            }
        }
        else
        {
            while(!n[tail])//末尾是0
            {
                tail++,ans++;//尾巴增加，答案增加
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：chinaxjh (赞：0)

首先我们来理解一下题意，重点只有一句话
>如果 x 为奇数，他就会将 x 加上1。如果 x 为偶数，他就会将 x 除以2。

到二进制里，就是末尾有0则去0，不然就加上1，消除一整排的1，记上步数，进行O(n)的模拟即可，上代码：
```
var
  m:ansistring;
  a:array[0..2000000] of char;
  i,len,k,ans:longint;
begin
  readln(m); len:=length(m);
  for i:=1 to len do
  begin
    a[i]:=m[i];
    if a[i]='1' then inc(k);
  end;//字符串转数组储存，更加快一点
  while true do
  begin
    while a[len]='0' do
    begin
      dec(len);
      inc(ans);
    end;//去掉末尾的0
    if k=1 then break;
    while a[len]='1' do
    begin
      dec(len);
      dec(k);
      inc(ans);
    end;//消除1
    inc(ans);
    a[len]:='1';
    inc(k);//最后还会产生1
    if k=1 then break;
  end;
  writeln(ans);
end.
```

蒟蒻代码风格丑陋，求大家谅解QAQ

---

