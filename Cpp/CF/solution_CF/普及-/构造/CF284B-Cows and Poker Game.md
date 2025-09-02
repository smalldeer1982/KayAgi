# Cows and Poker Game

## 题目描述

There are $ n $ cows playing poker at a table. For the current betting phase, each player's status is either "ALLIN", "IN", or "FOLDED", and does not change throughout the phase. To increase the suspense, a player whose current status is not "FOLDED" may show his/her hand to the table. However, so as not to affect any betting decisions, he/she may only do so if all other players have a status of either "ALLIN" or "FOLDED". The player's own status may be either "ALLIN" or "IN".

Find the number of cows that can currently show their hands without affecting any betting decisions.

## 说明/提示

In the first sample, cows 1, 4, 5, and 6 can show their hands. In the second sample, only cow 3 can show her hand.

## 样例 #1

### 输入

```
6
AFFAAA
```

### 输出

```
4
```

## 样例 #2

### 输入

```
3
AFI
```

### 输出

```
1
```

# 题解

## 作者：钺Programmer (赞：3)

### 题目大意：

奶牛们在玩扑克牌。每个奶牛有一个状态，只可能是 `A` ， `E` 或 `I` 。状态为 `A` 或 `I` 的奶牛在其他奶牛都是 `A` 或 `F` 的情况下可以摊牌。求最多有多少个奶牛可以摊牌。

### 题目思路：

如果 `I` 的数量大于 $1$，那么谁都不能摊牌——不管谁摊牌都会被某一个 `I` 看到。当 `I` 的数量等于 $1$，那么只能他自己摊牌。如果没有 `I` ，那么所有的 `A` 都能摊牌。

### AC代码：

```
#include<bits/stdc++.h>
using namespace std;
int n,a,i;
char c;
int main(){
    cin>>n;
    while(n--){//比for快（虽然这道题不卡常）
        cin>>c;
        switch(c){
            case 'A':++a;break;//不写break见**
            case 'I':++i;break;
        }
    }
    if(i>1){//如果有多于一个的I
        cout<<0;//谁都不能摊牌
    }else{
        if(i==1){//如果只有一个I
            cout<<1;//I自己摊牌
        }else{
            cout<<a;//没有I的情况，所有A都能摊牌
        }
    }
    return 0;//结束撒花
}
```

修改：

2020.3.17：修改程序内问题——注释 `//` 消失。

---

## 作者：zct_sky (赞：2)

### Description:
-----
每个奶牛有一个状态，只可能是 `A`，`F` 或 `I`。状态为 `A` 或 `I` 的奶牛在其他奶牛都是 `A` 或 `F` 的情况下可以摊牌。
### Solution:
-----
因为 `A` 是在其它奶牛都是 `A` 的情况下才能翻，而 `I` 是在其它奶牛都是 `F` 的情况下才能翻，所以主要看 `I` 的数量。

如果 `I` 有 0 个，那么只有是 `A` 的奶牛能翻牌。

如果 `I` 只有 1 个，那么只有是 `I` 的奶牛能翻牌，也就是只有 1 只奶牛能翻牌。

如果 `I` 的数量大于 1 个，那么无论是哪只奶牛都不能翻牌（`A` 和 `I` 都不能翻牌）。
### Code:
-----
```c++
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read(){//快读 
	int x=0,y=1;
	char ch=getchar();
	while(ch>'9'||ch<'0'){
		if(ch=='-')y=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
	return x*y;
}
inline void write(ll x){//快输 
	if(x<0)putchar('-'),x=-x;
	if(x>9)write(x/10);
	putchar(x%10+'0');
}
int n,I,A;
char ch; 
int main(){
    n=read();
    for(int i=0;i<n;i++){
    	ch=getchar();
    	if(ch=='A')A++;
    	if(ch=='I')I++;
	}
	if(I==0) write(A);
	else if(I==1) write(1);
	else write(0);
    return 0;
}
```

---

## 作者：Otue (赞：2)



### 题目大意
只可能是 `A` , `F` 或 `I`。状态为 `A` 或 `I` 的奶牛在其他奶牛都是 `A` 或 `F` 的情况下可以摊牌。
### 基本思路
题目满足两个条件才能摊牌，但是第 $2$ 个条件更加苛刻。因为你要仔细想一想：这么多奶牛，除了自己除外，其他奶牛不能有一个 `I`，所以说想要可以摊牌的话，`I` 最多只有一个。

分下列几种情况分类讨论：

* 如果总共 `I` 的数量大于 $1$,则不可能摊牌。因为随便哪一个奶牛，其余的奶牛总有一个奶牛是 `I`，就不可能有奶牛翻牌。

* 如果总共有 $1$ 个 `I`，那么只有 有 `I` 这张牌的奶牛 可以摊牌。

* 如果一张 `I` 都没有,那么分下面这几种情形讨论：
   * 假如说这个奶牛是 `A`，那么那么就可以摊牌。
   * 假如说这个奶牛是 `F`,就不能摊牌（因为只能是 `A` 或者 `I` 摊牌）。

就可以快乐的写代码喽！
### 参考代码
```c++
#include<iostream>
#include<cstdio>
#include<string>
using namespace std;
int lens;
string s;//字符串
int ans,num;
int main(){
	cin>>lens;
	cin>>s;
	for(int i=0;i<lens;i++){
		if(s[i]=='I'){
			ans++;//统计I的数量
		}
		if(s[i]=='A'){
			num++;//统计A的数量
		}
	}
	if(ans>1){//按照上面思路说的做
		cout<<0<<endl;
	}
	if(ans==1){
		cout<<1<<endl;//此时只能是他自己本身摊牌了
	}
	if(ans==0){
		cout<<num<<endl;//输出A的数量
	}
}

---

## 作者：qwq___qaq (赞：2)

**本题更像思维题。**
 
首先，我们先读题，发现：其实输出的答案只跟 `A` 和 `I` 有关，与 `F` 无关。

### 本题一共有三个条件：
1、`I` 的数量为 $0$ 时，`A` 的牌都满足条件，直接输出 `A` 的数量。

2、`I` 为 $1$ 时，因为只有持 `I` 的奶牛才可以翻牌，所以直接输出 $1$。

3、其他情况无论怎样翻牌，都会有多余的 `I`，所以直接输出 $0$ 即可。

## AC Code:
```
#include<bits/stdc++.h>
using namespace std;
int n,a,c; //变量 a 记录 A 的数量，c 记录 I 的数量。
int main(){
	scanf("%d\n",&n);//行末有个换行'\n'，否则就会读入到 ch 中
	while(n--){
		char ch=getchar();
		a+=(ch=='A');
		c+=(ch=='I');
	}
	if(c>=2)
		putchar('0');
	else if(c==1)
		putchar('1');
	else
		printf("%d",a);
	return 0;
}
```

---

## 作者：abc_de (赞：0)

 这道题只要想到方法的话其实会很简单，测试数据虽然有点多，但是不用慌


------------

大体思路：
把每个字母出现的次数记录下来，然后一个一个地判断能不能翻牌就好了。
这样算的话就是最优解了。

```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
string s;
int n,ans=0;
int x[100001];
int main(){
	cin>>n>>s;//正常输入
	for(int i=0;i<n;i++){//从零开始,字符串就是自动从零开始的
		x[s[i]]++//记录出现的次数
	}
	for(int i=0;i<n;i++){
		x[s[i]]--;//先假设用了
		if((s[i]=='A'||s[i]=='I')&&x['I']==0) ans++;//判断是否能翻牌,判断条件就是如题目中说的一样,同时把条件简化一下
		x[s[i]]++;//没用就把减去的加回来
	}
	cout<<ans;//输出答案
	return 0;
}
```


---

## 作者：动态WA (赞：0)

这里提供一种不用动脑而效率较低的思路。（雾

我们直接根据题意模拟，第一轮循环记录每种牌的个数。

第二轮循环判断每只奶牛能否翻牌。

最后输出答案就可以了。

与其他大佬的题解相比，我多开了一个数组，多用了一次循环。（~~我好菜~~）

贴出代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<queue>
#include<algorithm>
#include<ctime>
#include<map>
using namespace std;
int n;
string s;
int a[100];
int main(){
	cin>>n>>s;
	int l=s.size();
	for (int i=0;i<l;i++){
		if (s[i]=='A') a[s[i]]++;
		if (s[i]=='I') a[s[i]]++;
		if (s[i]=='F') a[s[i]]++;
	}
	int ans=0;
	for (int i=0;i<l;i++){
		a[s[i]]--;
		if ((s[i]=='A'||s[i]=='I')&&a['I']==0) ans++;
		a[s[i]]++;
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：tql_____ (赞：0)

### 题目规则:
### 状态为"A""I"的在其他人都是"A""F"的情况下可以摊牌。


------------
#### 分析：
- **A可以摊牌，也可以看**
- **I只能摊牌，不可以看**  

- **F不能摊牌，只可以看**  


因为I只能摊牌，所以I的数量不能超过1，并且有I时只有I能摊牌（否则别人摊牌I就看了）  
因为题目求摊牌的人数，所以F可以忽略

### 因此分三种情况：
### 1.I的数量>1            则0人摊牌
### 2.I的数量=1            则1人摊牌
### 3.I的数量=0 因为没有I，且F可以忽略，所以有几个A就有几个人可以摊牌。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
string s; 
int numi,numa;
int main()
{
    scanf("%d",&n);
    getchar();
    getline(cin,s);
    int len=s.size();
    for(int i=0;i<len;i++)
    {
    	if(s[i]=='I')
    	numi++;
    	else if(s[i]=='A')
    	numa++;
    }
    if(numi>1)
	cout<<0;
    else if(numi==1)
	cout<<1;
    else
	cout<<numa;
    return 0;
}

```


---

## 作者：happybob (赞：0)

这题一开始我还想着暴力，结果暴力刚刚打出来，TLE：

```cpp
#include <iostream>
#include <cstring>
using namespace std;

char s[200005];

int main()
{
	int n, ans = 0;
	cin >> n >> s;
    n--;
	for(int i = 0; i <= n; i++)
	{
		if(s[i] == 'A' || s[i] == 'I')
		{
			bool flag = true;
			for(int j = 0; j <= n; j++)
			{
				if(i != j)
				{
					if(s[j] == 'I')
					{
						flag = false;
						break;
					}
				}
			}
			if(flag && n != 1)
			{
				ans++;
			}
		}
	}
	cout << ans << endl;
	return 0;
}
```
唉，突然想到可以思路：

统计i和a的数量，如果说i比1大，也就是大于等于2，那么所有奶牛都会被i看到，就是0

如果i为1，那就是自己一个人，1

不然就输出a的数量：

```cpp
#include <iostream>
#include <cstring>
using namespace std;

string s;

int main()
{
	int n, ans = 0, icount = 0, acount = 0;
	cin >> n >> s;
    n--;
	for(int i = 0; i <= n; i++)
	{
		if(s[i] == 'I')
		{
			icount++;
		}
		else if(s[i] == 'A')
		{
		    acount++;
        }
	}
	if(icount > 1)
	{
	    cout << "0\n";
    }
    else
    {
        cout << (icount == 1 ? 1 : acount) << endl;
    }
	return 0;
}
```


---

## 作者：jxbe6666 (赞：0)

这只是一道入门级的字符串题啊，~~凭什么能评橙？~~。
### 题意：
- 一个数 $n$ 代表奶牛的的只数.
- 一个字符串 $s1$ 说明 $n$ 只奶牛手中的牌。
- 求出有几只奶牛能够摊牌，状态为 A 或 I 的奶牛在其他奶牛都是 A 或 F 的情况下才可以摊牌。

-----

### 思路：

读入字符串后，进行预处理。如果 I 的次数大于 1 了，就输出 0。等于 1 时，就输出 1。除此之外就输出 A 的个数。

-----

### 代码：
-----
```c++
#include <bits/stdc++.h>
#define I return
#define AK 0
#define IOI ;
#define ll long long
using namespace std;
string s1;
int n, ans, check;
inline int read()
{ // 快读
    int number = 0, check = 1;
    char ch = getchar();
    while (ch < 48 || ch > 57)
    {
        check = ch == 45 ? -1 : 1;
        ch = getchar();
    }
    while (ch >= 48 && ch <= 57)
    {
        number = (number << 1) + (number << 3) + (ch ^ 48);
        ch = getchar();
    }
    return number * check;
}
inline void write(int x)
{ // 快输
    if (x < 0)
    {
        x = ~(x - 1);
        putchar('-');
    }
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}
int main()
{
    n = read();
    cin >> s1;
    for (int i = 0; i < n; i++)
    {
        if (s1[i] == 'I')
        {
            check++;
        }
        if (s1[i] == 'A')
        {
            ans++;
        }
    }
    if (check == 1)
        putchar('1');
    else if (check > 1)
        putchar('0');
    else
        write(ans);
    I AK IOI
}

```

---

