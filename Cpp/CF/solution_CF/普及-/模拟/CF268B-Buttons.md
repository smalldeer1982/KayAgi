# Buttons

## 题目描述

Manao is trying to open a rather challenging lock. The lock has $ n $ buttons on it and to open it, you should press the buttons in a certain order to open the lock. When you push some button, it either stays pressed into the lock (that means that you've guessed correctly and pushed the button that goes next in the sequence), or all pressed buttons return to the initial position. When all buttons are pressed into the lock at once, the lock opens.

Consider an example with three buttons. Let's say that the opening sequence is: {2, 3, 1}. If you first press buttons 1 or 3, the buttons unpress immediately. If you first press button 2, it stays pressed. If you press 1 after 2, all buttons unpress. If you press 3 after 2, buttons 3 and 2 stay pressed. As soon as you've got two pressed buttons, you only need to press button 1 to open the lock.

Manao doesn't know the opening sequence. But he is really smart and he is going to act in the optimal way. Calculate the number of times he's got to push a button in order to open the lock in the worst-case scenario.

## 说明/提示

Consider the first test sample. Manao can fail his first push and push the wrong button. In this case he will already be able to guess the right one with his second push. And his third push will push the second right button. Thus, in the worst-case scenario he will only need 3 pushes.

## 样例 #1

### 输入

```
2
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3
```

### 输出

```
7
```

# 题解

## 作者：jinyixuan_2 (赞：2)

这是一道很简单的数学题。

我们只需要举例子找规律，比如：$1$，$2$。最坏情况是按 $2$，然后再按 $1$，$2$，总共是 $3$ 次。再比如：$1$，$2$，$3$。最坏情况是先按 $2$ 和 $3$，用了  	$2$ 次，再按 $1$，$3$ 和 $1$，$2$，$3$。就是 $7$ 次了。

#### 所以可以推出 $\left (n - i\right)\times i$。


代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

int main() {
	int n,ans=0,a=1;
	cin>>n;
	ans=n;
	for(int i=1;i<n;i++)
	{
		ans=ans+i*(n-i);
		a++;	
	}
	cout<<ans;

}
```


---

## 作者：小坦克 (赞：2)

## 前言：
这是一道找规律的思维~~水~~题，只要在草稿纸上~~疯狂打草稿~~，就~~珂~~以找出规律。

## 理解：
首先我们模拟一下整个过程：
```
假设开场序列是：{2,3,1}。
最坏的情况是先按3和1，按了两次。
然后再按2，按了3次。
接着，最坏的情况是按1，按了4次。
最后我们知道了结果，按顺序按了2,3,1，按了7次。

所以，按键的次数为：
1、按了除了正确的按键1次，为1*(n-1)。
2、先按了正确的按键，然后按了除了正确的按键1次，则总共按了2次，为2(n-2)。
3、先按了正确的按键2次，然后按了除了正确的按键1次，总共按了3次，为3(n-3)。
.....
最后：排除所有错误情况，按了所有正确的按键，按了n次。
```
## 得出公式：
通过计算，我们会发现对于每个 $n$，公式为：

$n−1+2(n−2)+3(n−3)+...+(n−1)1+n$
## 奉上代码（有详解）：
```
#include<bits/stdc++.h> //万能头
using namespace std;
int main(){
	int n; //the number of buttons the lock has
	cin>>n;
	int sum=0,cnt=1; //sum是最终的答案
	sum=n;
	for(int i=n-1;i>=1;i--){ //循环写规律		
		sum=sum+i*cnt;
		cnt++;		
	}
	cout<<sum; //最后输出sum
	return 0;
}
```
---------
完结撒花！

---

## 作者：xxxalq (赞：0)

[洛谷链接](https://www.luogu.com.cn/problem/CF268B) & [CF链接](http://codeforces.com/problemset/problem/268/B)

## 思路分析：

首先这是一道 $O(n)$ 结论题。

假设一共有顺序为 $1,2,3,4$ 的 $4$ 个按钮。

考虑最坏情况，第一次先按 $2,3,4$ 中的一个。从特殊到一般：$1\times(n-1)$。

第二次按 $1,3,4$ 中的一个，但不能是第一次按过的。从特殊到一般：$2\times(n-2)$。

第三次按 $1,2,4$ 中的一个，但不能是前两次按过的。从特殊到一般：$3\times(n-3)$。

第四次就知道正确顺序了，直接按 $n$ 次。

所以对于一个有 $n$ 个按钮的锁，最多要按 $n-1+2(n-2)+3(n-3)+...+(n-1)+n$ 次。

## 代码：

```cpp
#include<iostream>
#define ll long long
using namespace std;
int n;
int main(){
	cin>>n;
	ll ans=n;//先加上n
	for(int i=1;i<n;i++){
		ans+=i*(n-i);//求解答案
	}
	cout<<ans<<endl;//输出答案
	return 0;
}
```


---

## 作者：_Gabriel_ (赞：0)

### 思路

假设总共有 $n$ 个按钮。

则要找到第一个正确的按钮，最坏需要 $n-1$ 次；要找到第二个正确的按钮，最坏需要 $2 \times (n-2)$ 次。以此类推，要找到最后一个正确的按钮，只要 $1$ 次即可。

所以，总次数即为 $n-1+2 \times (n-2)+ \dots +1= \sum\limits_{i=1}^ni \times (n-i)+n$。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
	int n;
	cin >> n;
	ll ans = 0;
	for (int i = 1; i < n; i++) {
		ans += (n - i) * i;
	}
	cout << ans + n;
	return 0;
}
```


---

## 作者：zhouzihe (赞：0)

## 1 观察题目
观察题目，假设现在有 $n$ 个按钮。如果你想要找到第一个正确的按钮，则需要按下 $n-1$ 次，想找到第二个正确的按钮，则需要 $2 \times (n-2)$ 次，想找到第三个正确的按钮，则需要 $3 \times (n-3)$ 次，以此类推。答案即为 $\sum\limits_{i=1}^{n}{i \times (n-i)}+n$。
## 2 code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long int n,ans;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		ans+=i*(n-i);
	}
	cout<<ans+n;
	return 0;
}
```


---

## 作者：abensyl (赞：0)

原题：[原题传送门](https://www.luogu.com.cn/problem/CF268B)

## 思路：

大致题意：$n$ 个按钮，顺序按对了就会保持按下，中间只要有一不错了就会全部弹起

本蒟蒻思路的大前提：假如你是 Manao。

显然，第一个按钮有 $n$ 种可能性（我们是按照最坏的可能算的），于是在最糟糕的情况下，你会尝试 $n-1$ 次（成功的那一次不算尝试）。

此时，第一个按钮已经按对了，我们再来看第二个按钮：

你随便挑选一个按钮按下去，假设很不巧，你按错了，那么所有按钮都会弹起，此时你已经知道第一个按钮是哪一个了，于是你飞快地按下第一个按钮，然后再随意挑选一个按钮按下，可惜又不巧，按错了，于是我们继续重复刚才的操作，在最倒霉的情况下，我们按了 $2\times (n-2)$ 次。

…………

终于快按完了，只剩两个按钮没按了，你走向其中的一个，把它按下，可惜你按错了，所有按钮都弹起了，你又卷土重来，按照尝试出的顺序按下前 $n-2$ 个按钮，利用排除法，你试出了立刻按对了倒数第二个按钮，于是你按了 $n-1$。

此时，你面前只剩一个按钮了，想都不用想，一定是它了，对于最后一个按钮，你只按了 $n$ 次！

于是我们就这样，~~愉快地~~把按钮的顺序都试出来了。

我们一共按了 $(n-1)+2\times (n-2)+3\times (n-3)+\dots + (n-1) +1$ 次

写一个通项公式：

$$ n+\sum_{i=1}^n i(n-i) $$

## 代码（本人蒟蒻）:
```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
  	int n;
  	cin>>n;
  	int res=0;
  	for(int i=1,j=n-1;i<=n;++i,--j)
  		res+=i*j;
  	res+=n;//最后一个按钮需要按n次 
  	cout<<res;
    return 0;
}
```

我的[AC记录](https://www.luogu.com.cn/record/81972319)



---

## 作者：Obviathy (赞：0)

## 解题思路：
其实找找规律就行。

关键在于：最不利的情况就是，我把所有可能的在第 $i$ 个按下的按钮试了一遍后，**最后一个**是。

拿 $n=5$ 举例子。先试第一个按下的按键，试了 $5$ 次，最后一次是。再试第二个，因为第一个已经确定，就只剩四个可能的按键。但是第一次试第二个按键时，先前的第一个按键已经按下，所以只需要再按一次，后面的就需要两次……以此类推。

所以，$n=5$ 的试验情况为：

![](https://cdn.luogu.com.cn/upload/image_hosting/aw0kej0z.png)

最后全部加和即可。

## code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans; 
int main(){
	cin >> n;
	ans = n; 
	for(int i = n-1;i >= 1;i --)ans += i*(n - i);
	cout<<ans;
	return 0;
}

```
ctj可耻！


---

## 作者：FJ·不觉·莫笑 (赞：0)

### **一道锻炼思维的题目：**  


------------
### **先看题目：**  
    假设开场序列是：{2,3,1}。    
    如果您首先按下按钮1或3，按钮会立即取消按下。   
    如果您先按下按钮2，它会保持按下状态。   
    如果在2之后按1，则所有按钮都会按下。   
    如果在2之后按3，则按住按钮3和2。  
    只要有两个按下的按钮，您只需按下按钮1即可打开锁定。  


------------
### **思路：**  
 1. 设有$n$个按钮，若要情况最不幸，则第一次最多要按$n-1$次按钮才能找到正确的出场顺序。  
 2. 第二次因第一次已按下一个按钮，所以只要按$n-2$次便能找到第二个正确的按钮，**注意**： _如果按错了按钮，之前的一个按钮将弹出_ ，所以，总次数为$2(n-2)$。  
 ……  
总结得出，规律为：  
$$n-1+2(n-2)+3(n-3)+...+(n-1)1+n$$  


------------
### **上代码：** 
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n;//按钮的个数
	cin>>n;
	int sum=0,cnt=1;//sum：最少的次数  
	sum=n;
	for(int i=n-1;i>=1;i--)
	{		
		sum=sum+i*cnt;
		cnt++;		
	}//实行公式
	cout<<sum;//输出
	return 0;
}
```


------------
### **坑点：**   
 1. 变量$cnt$一定要在循环外赋值，不然每次都只是加上$i$。   
 2. $sum$不要忘记加$n$。  
求通过！

---

## 作者：felixshu (赞：0)

[我是传送门](https://www.luogu.com.cn/problem/CF268B)

这题要找规律，只用在草稿纸上狂写就可以找到规律了。

可以模拟整个过程。
## 模拟
所以，按键的次数为：

1. 按了除了正确的按键 $1$ 次，为 $1\times$ $(n-1)$。

2. 先按了正确的按键，然后按了除了正确的按键 $1$ 次，则总共按了 $2$ 次，为 $2\times(n-2)$。

3. 先按了正确的按键 $2$ 次，然后按了除了正确的按键 $1$ 次，总共按了 $3$ 次，为 $3\times(n-3)$。

.....

最后：排除所有错误情况，按了所有正确的按键，按了 $n$ 次。

## 得出公式：

通过计算，我们会发现对于每个 $n$，公式为：
 
$1\times(n-1)+2\times(n-2)+3\times(n-3)+...+n$。



## 下面是 AC 代码

```
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,ans=0,k=1; 
	cin>>n;
	for(int i=n-1;i>=1;i--)
	{	
		ans=ans+i*k;
		k++;		
	}
	ans+=n;
	cout<<ans; 
	return 0;
}
```



---

