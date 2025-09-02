# Jumping Ball

## 题目描述

In a new version of the famous Pinball game, one of the most important parts of the game field is a sequence of $ n $ bumpers. The bumpers are numbered with integers from $ 1 $ to $ n $ from left to right. There are two types of bumpers. They are denoted by the characters '<' and '>'. When the ball hits the bumper at position $ i $ it goes one position to the right (to the position $ i+1 $ ) if the type of this bumper is '>', or one position to the left (to $ i-1 $ ) if the type of the bumper at position $ i $ is '<'. If there is no such position, in other words if $ i-1&lt;1 $ or $ i+1&gt;n $ , the ball falls from the game field.

Depending on the ball's starting position, the ball may eventually fall from the game field or it may stay there forever. You are given a string representing the bumpers' types. Calculate the number of positions such that the ball will eventually fall from the game field if it starts at that position.

## 说明/提示

In the first sample, the ball will fall from the field if starts at position $ 1 $ or position $ 2 $ .

In the second sample, any starting position will result in the ball falling from the field.

## 样例 #1

### 输入

```
4
<<><
```

### 输出

```
2```

## 样例 #2

### 输入

```
5
>>>>>```

### 输出

```
5```

## 样例 #3

### 输入

```
4
>><<
```

### 输出

```
0```

# 题解

## 作者：Aragron_II (赞：2)

#### 题意：
有 $ n $ 个位置，每个位置上有一个符号，代表向左或者向右，问你当小球在那些位置的时候会越界（小于1或者大于 $ n $ ）。观察发现，左边的连续的和右边的连续的都会掉下去。

#### 思路：
模拟+字符串 

给大家两种写法

### 1.Code
```c
#include <bits/stdc++.h>
using namespace std;
string st;
int n,ans,t;
int main() {
	cin>>n>>st;//输入
	t=0; //初始为0
   while(st[t]=='<') ans++,t++;//判断左移情况，坐标+1
	t=n-1;//初始位最后一个命令符
   while(st[t]=='>') ans++,t--;//判断右移情况，坐标-1
	cout<<ans<<endl;//输出
	return 0;
}
```
### 2.Code
```c
#include <bits/stdc++.h>
using namespace std;
int n,k,ans1,ans2,a[200010],b[200010];
char s[200010];
int main() {
	cin>>n;
	scanf("%s",s);
	for(int i=0;i<n;i++) {
		if(s[i]=='<')
			ans1++;
		else {
			k=i;
			break;
		}	  
	}
	for(int i=k;i<n;i++) {
		if(s[i]=='>') 
			ans2++; 
		else
			ans2=0;
	}
	cout<<ans1+ans2<<endl;
	return 0;
}
```

推荐第一种写法，简单易理解

---

## 作者：LBYYSM_123 (赞：0)

非常水的模拟题，建议评~~红题~~。   
当遇到`>`时往右移动，反之则向左移动。  
所以我们只要在左边找连续的向左移动的`<`的个数，在右边找向右移动的`>`的个数，将去累加即可。（因为如果遇到不同，其后面的就可视为被阻挡，从而不可滚出场外）。
```cpp
#include<bits/stdc++.h>
using namespace std;
string st;
int n,ans==0,t=0;//ans为计数器 
int main() {
	cin>>n>>st;
   while(st[t]=='<')
   		ans++,t++;//从前往后找
	t=n-1;//字符串到n-1截止 
   while(st[t]=='>')
		ans++,t--;//从后往前找
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：InversionShadow (赞：0)

## CF725A Jumping Ball 题解

偏结论题。

### 题意：

给定一个长度为 $n$ 的字符串，设字符串为 $a$，其中只包含两种不同的符号 `>` 或 `<`。现在有一个球，它从起始位置开始，设当时的位置为 $t$，如果 $a_t$ 为 `<`，那么球往左走一格，否则球往右走一格，如果 $t<1$ 或 $t>n$，结束游戏。请输出可以让球最终落出场外的起始位置的个数。

### 思路：

用样例分析：

```<<><```

我们将它每个位置编个序号，第一个为 $a_1$，第二个为 $a_2$，第三个为 $a_3$，第四个为 $a_4$。

如果球在 $a_1$，那么球可以 $<0$，如果在 $a_2$，那么它移到 $a_1$，仍然可以 $<0$，如果在 $a_3$，那么球移到 $a_4$，$a_4$ 又移到 $a_3$，变成一个死循坏，$a_4$ 同理。

所以结论为：**连续的 `<` 或 `>` 可以掉出场外。**

### Code：

```cpp
#include <bits/stdc++.h>

using namespace std;

int n, t, sum;
string s;

int main() {
  cin >> n >> s;
  for (int i = 0; i < n; ) {
    if (s[i] == '<') {  
      sum++;
      i++;
    } else {
      break;
    }
  } 
  for (int i = n - 1; i >= 0; ) {
    if (s[i] == '>') {  
      sum++;
      i--;
    } else {
      break;
    }
  } 
  cout << sum << endl;
  return 0;
}
```


---

## 作者：Orange_Sky_Fish (赞：0)

#  CF725A Jumping Ball 题解

这道题难度似乎有点虚高，应该没到黄题的难度......

闲话少说，这道题比较水，就是一道模拟题。

我们只需要记录在最左边的 < 和在最右边的 > 就可以AC了。

为什么呢？

看下面这个例子：

譬如说你有在最左边的四个 < ，

这样，你无论怎么在这四个 < 中选位子，

小球最后都会掉出去。

但是中间如果穿插了一个 > 的话，

小球如果选 > 前面的位置，就不会掉下去，右边同理。

所以，这道题只需要统计最左边的 < 和最右边的 > 就可以了！

## code
```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
int main() {
    int n,ans,local;
    string a;
    cin>>n>>a;
    local=0;//初始化local
    while(a[local]=='<') {
        ans++;
        local++;
    }//查找最左边的<
    local=n-1;
    while(a[local]=='>') {
        ans++;
        local--;
    }//查找最右边的>
    printf("%d",ans);//输出
    return 0;//好习惯
}
```

---

## 作者：CarroT1212 (赞：0)

4-25 upd：修改了一个手滑打错的地方。

------------

什么时候球会掉出场外？

```
<<<><><>>>
```

显然只有当球位于左侧的 3 个 `<` 或右侧的 3 个 `>` 的位置上才会出场，也就是球位于场地左侧连续的 `<` 上或场地右侧连续的 `>` 上的时候。

所以我们只要统计场地左侧连续的 `<` 和场地右侧连续的 `>` 的数量之和就可以得出答案了。

------------

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
using namespace std;
int n,ans;
char sz[2000010];
int main() {
	cin>>n;
	cin>>sz;
	for (int a=0;a<n;a++) {
		if (sz[a]=='>') break;
		ans++;
	}
	for (int a=n-1;a>=0;a--) {
		if (sz[a]=='<') break;
		ans++;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：ynxynx (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF725A)

这道题目很显然~~是红题~~

如果有两个满足 $><$ 时一定不能结束

所以我们只要记录靠左的 $<$ 以及靠右边的 $>$ 就行了

```c++
#include<bits/stdc++.h>//万能头
using namespace std;
string s;
int n,now,ans;
int main(){
	cin>>n>>s;
	//这里now初始化为0
	while (s[now]=='<') ans++,now++;//靠左的'<'
	now=n-1;
	while (s[now]=='>') ans++,now--;//靠右的'>'
	cout<<ans<<endl;//输出
	return 0;
}
```

---

## 作者：xiaomuyun (赞：0)

# CF725A Jumping Ball 题解
[题目传送门](https://www.luogu.com.cn/problem/CF725A)
## 题意简述
有一个长度为 $n$ 的字符串 $s$。对于 $s$ 中的每个位置，都可以将一个指针 $i$ 指向那个位置。如果 $i$ 目前位于 $j$（$1\leq j\leq n$），需要进行以下两个操作之一：

1. 如果 $s_j=$ 英文半角左书名号（即 $<$），则将指针 $i$ 左移一个位置，到 $j-1$；
2. 如果 $s_j=$ 英文半角右书名号（即 $>$），则将指针 $i$ 右移一个位置，到 $j+1$。

我们称指针 $i$ **出界**当且仅当 $i<1$ 或 $i>n$。现在需要输出一共有几个位置可以让 $i$ 作为起始位置，**且 $i$ 会在若干次操作后出界**。
## 题目分析
我们可以发现，如果 $s$ 是 `<<>><<>>` 这样的话有 $4$ 个位置会让 $i$ 在若干次操作后出界，即前两个和后两个。所以说实际上的答案就是从左边开始的连续的 $<$ 的长度加上从右边开始的连续的 $>$ 的长度。所以代码就很简单了。
## 代码实现
```cpp
#include<iostream>
#include<string>
#include<cstdio>
using namespace std;
int n,res=0;
string s;
int main(){
	scanf("%d",&n);
	cin>>s;
	for(int i=0;i<n;++i){
		if(s[i]=='>') break;
		++res;
	}
	for(int i=n-1;i>=0;--i){
		if(s[i]=='<') break;
		++res;
	}
	printf("%d\n",res);
	return 0;
}
```

---

## 作者：Velix (赞：0)

一道较为水的模拟题，想出来也不是太难。

根据题意，我们能看出来能掉下去的位置也只有这几种情况：

1. （左边界）<<<<<<……

2. ……>>>>>>（右边界）

计算的时候直接判断即可。

### Code

```
#include<bits/stdc++.h>
using namespace std;
string a;
int b,c;
int main()
{
	cin>>b>>a;
	b=0;
	while(a[b]=='<'&&b<a.size())c=++b;
	b=a.size()-1;
	while(a[b]=='>'&&b>=0)c++,b--;
	cout<<c;
}
```


---

## 作者：codemap (赞：0)

很水的一道题

很显然,要先满足条件,必须在两边

形如<<...<<>......或...<>>....>>

然后的代码实现就很简单了

上代码
```cpp
#include<iostream>
using namespace std;
char a[200001];
int main()
{
	int n,i,s=0;//s是计数器
	cin>>n;
	for(i=1;i<=n;i++)
		cin>>a[i];//输入
	for(i=1;i<=n;i++)//从左边找'<'
	{
		if(a[i]=='>')//如果出现了'>'
			break;//终止循环
		s++;//还是'<'则计数器++
	}
	for(i=n;i>=1;i--)//同理,略
	{
		if(a[i]=='<')
			break;
		s++;
	}
	cout<<s;//输出
	return 0;//完美结束
}
```
# 请勿抄袭

---

