# [COCI 2015/2016 #4] DEATHSTAR

## 题目描述

你排除万难，潜入了 Death Star。要想摧毁它，你需要一个长度为 $n$ 的数组 $a$，以启动 Death Star 的自我毁灭指令。虽然你不知道这个数组是什么，但好在，你的老朋友 Darth Vader 事先给了你一个 $n$ 阶方阵 $b$。在这个方阵中，第 $i$ 行第 $j$ 列上的元素 $b_{i,j}=a_i\operatorname{~and~} a_j$，其中 $\operatorname{and}$ 表示按位与运算。正当你以为你可以通过这个方阵直接得出数组 $a$ 时，你发现主对角线上的所有元素被激光剑给毁坏了，你无法读出这些元素的值，只能暂时以 $0$ 代替。

现在，请你根据其他没有被毁坏的元素的数值求出**任意一个**满足要求的数组 $a$。

## 说明/提示

**【样例 1 解释】**

不难看出，满足要求的一个数组 $a=[1,1,1]$，但请注意，这并不是唯一可能的答案。

**【数据范围】**

对于所有数据，$1\leqslant n\leqslant 1000$，$0\leqslant b_{i,j}\leqslant 10^9$。

**本题开启 Special Judge**。如果你有可以 hack [供题人自行编写的 checker ](https://www.luogu.com.cn/paste/fzkkyhqp)的数据或者对 checker 有改进意见，欢迎在本题下方讨论区提出。

**【题目来源】**

本题来源自 **_[COCI 2015-2016](https://hsin.hr/coci/archive/2015_2016/) [CONTEST 4](https://hsin.hr/coci/archive/2015_2016/contest4_tasks.pdf) T3 DEATHSTAR_**，按照原题数据配置，满分 $100$ 分。

由 [Eason_AC](https://www.luogu.com.cn/user/112917) 翻译整理提供。

## 样例 #1

### 输入

```
3
0 1 1
1 0 1
1 1 0```

### 输出

```
1 1 1```

## 样例 #2

### 输入

```
5
0 0 1 1 1
0 0 2 0 2
1 2 0 1 3
1 0 1 0 1
1 2 3 1 0```

### 输出

```
1 2 3 1 11```

# 题解

## 作者：Elairin176 (赞：20)

~~哇，这居然是我AC的第二道灰题~~      
题目链接：[传送门](https://www.luogu.com.cn/problem/P8053)     
## 预备知识：   
按位与：符号为 $\&$，将两个数字的每一位二进制进行逻辑与操作，**仅在两位全为 $1$ 的时候为 $1$**。    
按位或：符号为 $\mid$，将两个数字的每一位二进制进行逻辑或操作，**仅在两位全为 $0$ 的时候为 $0$**。   
## 分析：    
这里我们设 $b_{i,j}$ 的第 $i$ 位为 $1$ 因为进行的是按位与操作，所以 $a_i$ 上所有 $b_{i,j}$ 上为 $1$ 的数位都会得到 $1$ 。     
所以，我们对其进行反向操作，得出式子 $a_i=b_{i,j}\mid a_i$。简单一点，即 $a_i \mid =b_{i,j}$。    
# CODE：    
```cpp
#include <iostream>
using namespace std;
int n,b[1001][1001],a[1000];//题面所述。
int main(void){cin>>n;//输入n
for(int i=0;i<n;i++) for(int j=0;j<n;j++) cin>>b[i][j],a[i]|=b[i][j];//输入b[i][j]并对a[i]进行操作
for(int i=0;i<n;i++) cout<<a[i]<<" ";}//输出
```
### 最后，点个赞再走吧~

---

## 作者：cff_0102 (赞：7)

$C++$ 题解。

我们知道（不知道的来看一看）：

>与运算 $&$ 的结果第 $i$ 位为 $1$ ，当且仅当两个数的第 $i$ 位都为 $1$ 时。

>或运算 $|$ 的结果第 $i$ 位为 $1$ ，当且仅当两个数的第 $i$ 位都不为 $0$ 时。

因为 $a_i\ \&\ a_1=b_{i,1}$ ，所以 $a_i$ 上所有 $b_{i,1}$ 为 $1$ 的二进制数位都要是 $1$ 。同理， $a_i$ 上所有 $b_{i,2}$ 为 $1$ 的二进制数位也都要是 $1$ 。可以得出，对于一个数 $a_i$ ，这个数上所有的 $b_{i,j}(1\le j\le n)$ 的二进制数位也都要是 $1$ 。

这样，我们就想到了可以用与运算解决问题。也就是 $a_i= b_{i,all}$ 的与 。

根据上面的推理，代码就出来了。记住，不要抄代码。

```cpp
#include<bits/stdc++.h>//这题实际不难，怎么就没人写题解呢 
using namespace std;
int b[1005][1005],a[1005]/*题目中的数组*/,buyaochaotijie=0;
int main(){
	ios::sync_with_stdio(false);//加速让cin/cout更快
	int n;
	cin>>n;//如题面，输入题目中的n 
	for(int i=0;i<n;i++)//为了方便理解把输入和运算两部分分开了{
		for(int j=0;j<n;j++){
			cin>>b[i][j];//输入 
		}
	}
	for(int i=0;i<n;i++){//运算部分
		for(int j=0;j<n;j++){
			a[i]|=b[i][j];//不断进行或运算就可以达到效果了 
			//实际上这一行可以加 a[j]|=b[i][j]; 且整个数组只用遍历一半就行了，因为它是对称的 
			//但是写成这样更好理解一些
			//因为来看题解的也不会有dalao啦 
		}
	}
	//最后不要忘了输出
	for(int i=0;i<n;i++){
		cout<<a[i]<<" ";
	}
	return buyaochaotijie;//轻松AC 
}
```

那么这道题的题解就结束了，大家对照代码理解一下，也希望管理能过通过这篇题解。

---

## 作者：donghaoyu2011 (赞：2)

首先，我们要知道 $b_{i,j}=a_i=a_j$ 。
或者说我们把输入进去的数都看成二进制，我们就是在不断把 $b_{i,j}$ 的数往 $a_i$ 和 $a_j$ 上“套”。

比如说 $a_1=001$，$a_2=101$，$b_{1,2}=111$，由于 $a_1$ 的第一二位和 $a_2$ 的第二位没有 $1$，所以 $a_1$ 和 $a_2$ 就都变成了 $111$，如果 $b_{1,2}=001$，那么 $a_1$ 和 $a_2$ 就不会有改变。

能做到这些的就只有或。所以只用在输入的时候特判非0数字，再用 $a_i$ 和 $a_j$ 或 $b_{i,j}$ 就可以了。

### 以下为代码
```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,mapp,a[100010];
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>mapp;
            if(mapp!=0){
                a[i]|=mapp;
                a[j]|=mapp;
            }
        }
    }
    for(int i=1;i<=n;i++){
        cout<<a[i]<<" ";
    }
    return 0;
}

---

## 作者：V1mnkE (赞：2)

## 思路
有一定位运算基础的话,我们知道:

与运算的结果第 $i$ 位为 $1$，当且仅当两个数的第 $i$ 位都为 $1$ 时 (这里的数为二进制)。

所以我们可以得出如下结论:

若 $b_{i,j}$ 的二进制第 $k$ 位为 $1$，那么 $a_i$ 和 $a_j$ 的二进制第 $k$ 位也为 $1$。

是不是想到了按位与?我们就得到了如下的式子:
$$ a_i = a_i | b_{i, j}\quad(1\leq j\leq n)$$
## 代码实现
两重循环枚举 $i, j$ 即可
```cpp
#include<bits/stdc++.h> 
using namespace std;
int n,a[1005][1005],ans[1005];
int main(){
	cin>>n;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			cin>>a[i][j];
			ans[i]|=a[i][j];
		}
	}
	for(int i=0;i<n;i++)cout<<ans[i]<<" ";
	return 0;
}
```

---

## 作者：Asimplename (赞：1)

首先我们知道，两个数按位与时，只有在二进制表示下某一位两个数都是 $1$ 的时候这一位的结果才是 $1$。

所以我们可以把 $b_{i,j}$ 拆成二进制，如果某位是 $1$，那么 $a_i$ 和 $a_j$ 这一位都应是 $1$，如果不是，那么直接给它加上 $2^x$（$x$ 表示第几位）即可。

```cpp
#include<iostream>
using namespace std;
int n;
int a[1010];
int b[1010][1010];
int main (){
	cin >> n;
	for(int i = 1; i <= n; i ++){
		for(int j = 1; j <= n; j ++){
			cin >> b[i][j];
		}
	}
	for(int i = 1; i <= n; i ++){
		for(int j = 1; j <= n; j ++){
			int tmp = b[i][j];
			int w = 0;
			while(tmp){
				if(tmp & 1){//ai和aj在这一位下应都是1 
					if(!((a[i] >> w) & 1)){
						a[i] += (1 << w);
					}
					if(!((a[j] >> w) & 1)){
						a[j] += (1 << w);
					}
				}
				tmp >>= 1;
				w ++; 
			}
		}
	}
	for(int i = 1; i <= n; i ++){
		cout << a[i] << " ";
	}
	return 0;
} 
```

---

## 作者：zhang_kevin (赞：1)

简单的模拟题，但是一定要[先读题](https://www.luogu.com.cn/problem/P8053)！
# Solution
首先，我们要知道：如果 $a_i$ 和 $a_j$ 进行按位与运算之后第 $x$ 位是 $1$，那么 $a_i$ 和 $a_j$ 的第 $x$ 位都是 $1$。

于是我们接着分析：假设 $b_{i,j}$ 的二进制的第 $x$ 位为 $1$，因 $a_i$ 上所有 $b_{i,j}$ 为 $1$ 的二进制数位都是 $1$，所以可得答案公式：

$$a_i=a_i|b_{i,j}$$

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1001][1001], Ans[1001];
int main(){
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			cin >> a[i][j];
			Ans[i] |= a[i][j];
		}
	}
	for(int i = 1; i <= n; i++){
		cout << Ans[i] << " ";
	}
	return 0;
}
```

---

## 作者：skyskyCCC (赞：1)

**前言。**

基础的位运算。

**分析。**

首先，让我们来了解一下什么是位运算：

或运算 $|$ 的意义:

运算的结果第 $i$ 位为 $1$，当且仅当两个数的第 $i$ 位都不为 $0$ 时 (这里的数自然为二进制)。

与运算的意义：

运算的结果第 $i$ 位为 $1$，当且仅当两个数的第 $i$ 位都为 $1$ 时 (这里的数为二进制)。

二进制就是只有 $1$ 和 $0$ 组成的数，遇二进一,如 $1+1=10$。

那么，我们来进行下一步思考。

设 $b_{i,j}$ 的二进制的第 $i$ 位为 $1$，

因为 $a_i$ 上所有 $b_{i,j}$ 为 $1$ 的二进制数位都是 $1$，

（当 $1≤j≤n$ 时）

所以可得， $a_i =a_i | b_{i,j}$ 的式子。

代码如下，仅供参考：
```
#include<iostream>
using namespace std;
int n;
int a[1005][1005];
int ans[1005];
int main(){
    ios::sync_with_stdio(false);
    cin>>n;
    for (int i=1;i<=n;i++){
        for (int j=1;j<=n;j++){
            cin>>a[i][j];
            ans[i]|=a[i][j];
        }
    }
    for (int i=1;i<=n;i++){
        cout<<ans[i]<<" ";
    }
    return 0;
}
```
**后记。**

如有疑问请在评论区提出，我会尽力解答的。

---

## 作者：wangif424 (赞：0)

## ~~我的首灰~~
拿到题首先分析样例。

小学数学老师教过我们用表格分析数据：


因为是二进制位运算，所以比较看它们二进制每一位。

这里列举的是第二组样例第三行。

```cpp
1 2 0 1 3
```

| $b_{3,1}$ | $0$ | $1$ |
| :-----------: | :-----------: |:-----------: |
| $b_{3,2}$ | $1$ | $0$ |
| $b_{3,3}$ | $0$ | $0$ |
| $b_{3,4}$ | $0$ | $1$ |
| $b_{3,5}$ | $1$ | $1$ |
| $a_3$    | $1$ | $1$ |
观察每一竖列，只要 $b_{i,j}$ 的第 $k$ 位为 $1$，那么 $a_i$ 的第 $k$ 位也为 $1$。

即 **$a_i$ 等于 $b_i$ 的每一个数字的或和**(应该是这么叫吧)。

## AC代码（勿抄）：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[1001],b[1001][1001];
int main(){
	cin >> n;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cin >> b[i][j];
			a[i]=a[i]|b[i][j];
		}
	}
	for(int i=1;i<=n;i++){
		cout << a[i] << " " ;
	}
	return 0;
}

```


---

## 作者：furbzy (赞：0)

首先我们要认真[读题](https://www.luogu.com.cn/problem/P8053)。

很明显，这是一道模拟题。

（ps：关于位运算。按位与是把两个数转换成2进制后逐一位进行与操作。按位或同理。）

这里给出数列任意两个数的按位与后的值，让你求原数列。

首先，一个显而易见的道理：如果 $a_i$ 和 $a_j$ 进行按位与操作之后第 $k$ 位是一，那么 $a_i$ 和 $a_j$ 的第 $k$ 位都是一。

所以，我们可以考虑当给出 $a_i$ 和 $a_j$ 按位与之后的数时，将 $a_i$ 按位或上这个数（想想为什么）。

我们可以写出如下代码：

```c
#include<bits/stdc++.h>
#define in inline
#define ll long long int
#define rll register ll
using namespace std;
ll a[100001];
in ll read()    //快读 
{
	ll ans=0;
	bool j=false;
	char c=getchar();
	while(!(isdigit(c)))
	{
		if(c=='-')
		j=true;
		c=getchar();
	}
	while(isdigit(c))
	{
		ans=(ans<<3)+(ans<<1)+(c^48);
		c=getchar();
	}
	return j? ~ans+1:ans;
}
int main()
{
	//freopen("a.in","r",stdin);    本人调代码时习惯用文件操作 
	//freopen("escape.out","w",stdout);    此题无用，可删 
	ll n=read();
	for(rll i=1;i<=n;i++)
	{
		for(rll j=1;j<=n;j++)
		a[i]|=read();    //按位或上按位与后的结果 
	}
	for(rll i=1;i<=n;i++)
	printf("%d ",a[i]);
	return 0;    //完结撒花~~~ 
}
```

就可以愉快的AC啦~（本人第二次写题解，写的不好，请多指教）

---

