# 宇宙人からのメッセージ

## 题目描述

给出密文 $S$，解读方法如下：

- 设 $T$ 为空字符串；
- $i=1,2,...,|S|$ 以下按顺序进（$|S|$ 表示 $S$ 的长度）；
    - 当 $S$ 的第 $i$ 字母是 $R$ 时，将 $T$ 反转；
   - 当 $S$ 的第 $i$ 个字母不是 $R$ 时，在 $T$ 的末尾加上该字母。
- 然后，如果 $T$ 中连续出现了两个相同的字母，就去掉这两个字母。尽可能地继续这个操作(可以证明最终得到的字符串不会取决于去除的顺序)。

请输出通过以上操作得到的字符串 $T$。

## 说明/提示

- 字符串 $S$ 由英文小写字母和R组成；
- $1 \le |S| \le 5 × 10^5 $。

### 样例 1 解释

- 最初，$T$ 是空字符串。
- 在 $T$ 的末尾加上 `o`，$T$ 变成了 `o`。
- 在 $T$ 的末尾加上 `z`，$T$ 变成了 `oz`。
- $T$ 反转，$T$ 变成了 `zo`。
- 在 $T$ 的末尾加上 `n`，$T$ 变成了 `zon`。
- 在 $T$ 的末尾加上 `o`，$T$ 变成了 `zono`。
- 在 $T$ 的末尾加上 `n`，$T$ 变成了 `zonon`。
- 在 $T$ 的末尾加上 `n`，$T$ 变成了 `zononn`。
- 在 $T$ 的末尾加上 `o`，$T$ 变成了 `zononno`。
- 在 $T$ 的末尾加上 `e`，$T$ 变成了 `zononnoe`。
- 删除连续排列的 `n`，$T$ 变成了 `zonooe`。
- 删除连续排列的 `o`，$T$ 变成了 `zone`。

### 样例 2 解释
空串有时也会成为答案。

## 样例 #1

### 输入

```
ozRnonnoe```

### 输出

```
zone```

## 样例 #2

### 输入

```
hellospaceRhellospace```

### 输出

```
```

# 题解

## 作者：SkyWave (赞：17)

  首先我们看到这道题第一眼的想法就是硬模拟！

  但肯定是不行滴，最坏时间复杂度是 $O(\lvert S \rvert^2)$。

  ![](https://cdn.luogu.com.cn/upload/image_hosting/bjk0zuma.png)

  绝望 ing

  先放上我的模拟代码！

  ```cpp
  //
  //  main.cpp
  //  宇宙人からのメッセージ
  //
  //  Created by SkyWave Sun on 2022/10/25.
  //

  #include <iostream>
  #include <vector>
  #include <algorithm>
  using namespace std;
  #define N (int)5e5 + 1
  int main(int argc, const char * argv[]) {
      char c = '\0';
      char output[N];
      int rear = 0;
      while (c != '\n' && c != EOF) {
          c = getchar();
          if (c == 'R') {
              reverse(output + 1, output + rear + 1);
          }else {
              if (rear && output[rear] == c) {
                  output[rear] = '\0';
                  --rear;
              }else {
                  output[++rear] = c;
              }
          }
      }
      printf("%s\n",output + 1);
      return 0;
  }
  ```
  不难发现，其他地方已无可优化，时间都浪费到 reverse 上了。

  如果我们能把 reverse 换一种方式呈现，时间复杂度将大大降低。
  
  我们来思考这样一个问题，我有一个字符串为 $\verb!abc!$，我将它反转后再加上 d，不难发现，这次操作就相当于我将 d 加到 $\verb!abc!$ 的前面，然后再倒序输出。如果我再想要一次反转操作，我们还需要把它倒过来吗？其实不用，我们可以直接在 $\verb!dabc!$ 的后面加上 e，因为之前一次操作已经将它倒序，我反转一次就相当于抵消了一次操作，$\verb!cbad!$ 变为 $\verb!abcd!$，所以直接在末尾加上 e 即可。那如何判断什么时候该在尾巴上添加，什么时候该在头上添加？我们可以用一个变量 $flag$，默认为 false。当前如果看到了一个 R，就说明现在反转了一次，将 $flag$ 设为 true。如果 $flag$ 为 true，则在头上添加，否则就在尾上添加。如果当前 $flag$ 为 true，又扫到了 R，负负得正，则在尾巴上添加。
  
  那如何解决相邻的元素删除的问题呢？这也简单。当在尾巴上插入时，如果插入的元素和队列里的队尾相同，就要在尾巴上出队。在头上插入时，如果插入的元素和队列的队头相同，就应该在头上出队，这一部分也完结！
  
  说完了思路，我们该谈实现了——如何在头上或者尾上添加元素？对了，双端队列——deque。但因为我不太喜欢 STL 的数据结构，所以现在就来手写队列啦。
  
  手写双端队列很简单，只要在以前的基础上改一改就好了。先看字符串的长度为 $5\times10^5$，所以双端队列的大小就要开到 $5 \times 10^5 \times 2$，也就是 $10^6$，这时队头设置成 $5 \times 10^5 + 1$（为什么要加1这里优点耐人寻味，后面会配合样例进行讲解），队尾设置成 $5 \times 10^5$。要在队尾插入变量 $a$ 我们可以这样操作:
```cpp
deque[++rear] = a;
```

想要在队头插入变量 $b$ 也是同理:
```cpp
deque[--front] = b;
```

那被出队的元素的值没有清空，需要清空吗？并不需要，因为会被下一次操作所覆盖。
  
思路讲解完毕，接下来边上代码边讲！
  
```cpp
//
//  main.cpp
//  宇宙人からのメッセージ
//
//  Created by SkyWave Sun on 2022/10/25.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <algorithm>
using namespace std;
#define N (int)1e6 + 1//别忘了双倍空间要加1，AT 大数据很极致
char str[(int)5e5 + 1];
char output[N];
int main(int argc, const char * argv[]) {
    scanf("%s",str + 1);//习惯下标从 1 开始
    int front = 5e5 + 1;//请看代码的最后
    int rear = 5e5;
    bool isRev = false;//用来判断现在是在队首插入还是要在队尾插入
    for (int i = 1; str[i]; ++i) {// str[i] 的意思是str[i]不为'/0'时，也就是字符串没有到末尾时。这样可以不用strlen获取字符串长度，在数据量大的情况下节省时间。
        if (str[i] == 'R') {
            isRev ^= 1;//异或的意思是相同为 0，不同为 1，也就是如果 isRev 是 true ，就将他改为 false，如果是 false，将他改为 true。
        }else {
            if ((front != 5e5 + 1 || rear != 5e5/*判断队列是否是空的，如果是空的直接入队，不用进行后面的判断*/) && (isRev?output[front] == str[i]:output[rear] == str[i])) {//要插入的是否和现在的队尾或者队首相同，isRev?output[front] == str[i]:output[rear] == str[i] 是一个三元运算符，意思是如果 isRev 为 true 就判断队首和要插入的数是否相同，否则就判断队尾和要插入的数是否相同
                isRev?++front:--rear;//判断是否被反转，如过被反转那么在头上出队，否则在尾上出队。
            }else {
                isRev?output[--front] = str[i]:output[++rear] = str[i];//如果不相同就直接入队
            }
        }
    }
                                        
  /*
  为什么 front 一开始要加 1？请看样例 2。

  输入:hellospaceRhellospace

  输出:""（空串）

  如果队首从 5e5 开始，那么队尾将从 5e5 + 1 储存第一个元素，那么我在做上面 for 循环的 isRev?output[front] == str[i]:output[rear] == str[i] 判断时就会发现 output[5e5] 这个元素是空的 （'char('\0')'），从而插入队列。但事实是 5e5 + 1 的 h 与要插入的 h 冲突了，应该消掉。所以队首设置成 5e5 是为了方便这里的判断。
  */
    if (isRev) {//最后是 true 就说明是倒序的，倒序输出
        for (int i = rear; i>=front; --i) {
            putchar(output[i]);
        }
    }else {
        for (int i = front; i<=rear; ++i) {
            putchar(output[i]);//用 printf("%s",output + rear); 可能会把出队时没有清空的元素也打印了。
        }
    }
    putchar('\n');
    return 0;
}


```
这样时间复杂度仅为 $O(\lvert S \rvert)$，本题$\lvert S \rvert$最大为 $5 \times 10 ^ 5$，故可以轻松通过。


完结撒花！
                                    
后记：这篇是我的第一篇题解。早上正准备刷 atcoder 时发现有一道有意思的字符串题目，正好题解是开着的，就欣喜若狂的写下来这篇题解。有任何不足之处请在评论区提出！爱你们。


---

## 作者：small_john (赞：2)

## 前言

解决了 TLE 的问题。

## 分析

第一眼看到此题，**双端队列**~~的水题~~。

其实暴力的做法唯一缺陷是翻转字符串，我们就只需要优化一下就行了。

先来认识一下双端队列吧！

```cpp
deque<int> q;//定义队列q，int可以替换成其他数据类型
q.push_front(x);//队首加入x
q.push_back(x);//队尾加入x
q.front();//查找队首元素
q.back();//查找队尾元素
q.pop_front();//删除队首元素
p.pop_back();//删除队尾元素
q.empty();//判断队列是否为空
```

接下来进入正题。

我们用 $v$ 记录翻转的情况（翻转偶数次为 $0$，翻转奇数次为 $1$）。

加字母的情况：

1. $v = 0$：在队尾增加字符，即 `q.push_back(x)`；

2. $v = 0$：在队首增加字符，即 `q.push_front(x)`。

完美的解决了 TLE。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 5e5+5;
bool v; 
deque<char> q;
string s;
int main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>s;
	for(int i = 0;i<s.size();i++)
	{
		if(s[i]=='R')
			v=!v;//取反 
		else if(v)
			if(!q.empty()&&q.front()==s[i])//删除元素
				q.pop_front();
			else q.push_front(s[i]);
		else
			if(!q.empty()&&q.back()==s[i])//删除元素 
				q.pop_back();
			else q.push_back(s[i]);
	}
	if(v)
		while(!q.empty())//输出
		{
			cout<<q.back();
			q.pop_back();
		}
	else
		while(!q.empty()) 
		{
			cout<<q.front();
			q.pop_front();
		}
	return 0;
}
```

---

## 作者：ImNot6Dora (赞：2)

这道题最重要的一个操作就是反转加字母，但是我们并不能用字符串交换的形式做，这样的话在交换过程中浪费的时间太多了。

其实，我能将他反转再加字母，其实就相当于在头上加字母。

为什么这么说呢？比如字符串 `dora`，我们将他反转再加一个字母 `a` 就变成了 `aroda`，也就是 `adora`，但是输出的时候我们可不能这么做，那么我们只需要标记目前是从头输出还是从尾输出。

本质上，既然我们既可以在头上加字母，又可以在尾巴加字母，那么这道题我们就可以用双端队列解决~

```cpp
//在STL中，deque用来建造双端队列。
deque<int>g;//建造int类型的双端队列g
deque<char>g;//建造char类型的双端队列g
g.empty();//布尔值，true表示队列空，false表示队列非空。
g.size();//返回容器大小
g.push_front(x);//在队首上加入元素x
g.push_back(x);//在队尾加入元素x
g.pop_front();//删除队首元素
g.pop_back();//删除队尾元素
g.front();//返回队首元素
g.back();//返回队尾元素
```

在本题中，我们需要用字符类型的双端队列，这样双端队列就充当了一个字符串。

为了标记添加元素的位置，我们需要标记字母添加位置是头还是尾。

而两个相同的字母删除就更好说了，我们比对之后直接删除前边或后边，注意这里要判断是否为空。

然后经过修改，就……可以通过了。
## C++ CODE:
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
bool f=1; 
deque<char>t; 
int main(){
	cin>>s;
	for(int i=0;i<s.length();i++){
		if(s[i]=='R')f=!f;
		else if(f){
			if(!t.empty()&&t.back()==s[i])t.pop_back();
			else t.push_back(s[i]);
		}else{
			if(!t.empty()&&t.front()==s[i])t.pop_front();
			else t.push_front(s[i]);
		}
	}
	if(f){
		while(!t.empty()){
			cout<<t.front();
			t.pop_front();
		}
	}else{
		while(!t.empty()){
			cout<<t.back();
			t.pop_back();
		}
	}
	return 0;
}
```
~~代码已经很清楚了~~

By ImNot6Dora

---

## 作者：心灵震荡 (赞：0)

STL 大法好！

首先，看到这一题，首先想到的方法就是用字符串硬模拟。

但分析一下，这种算法的时间复杂度是 $O(\lvert S\vert^2)$，一定会超时。

那么，有没有什么更简便的方法呢？

当然有。$O(\lvert S\vert^2)$ 的时间复杂度主要来源于反转字符串的过程。考虑一个字符串 `kaioi`，将它反转后再加上字符 `i`，得到字符串 `ioiaki`。而如果我们直接从头部插入字符 `i`，再倒序输出，也能得到同样的结果。本质上，我们需要分别从头部和尾部插入元素。所以双端队列就能解决问题。

在 STL 中，有一个快捷的双端队列容器：deque！

```cpp
deque<char>q;       //定义char类型的双端队列q
q.empty();          //返回一个布尔值，true表示队列空，false表示队列非空。
q.size();           //返回容器大小
q.push_front(x);    //在队首插入元素x
q.push_back(x);	    //在队尾插入元素x
q.pop_front();      //弹出队首元素
q.pop_back();       //弹出队尾元素
q.front();          //返回队首元素
q.back();           //返回队尾元素
```

我们可以维护双端队列和一个初始值为 $0$ 的变量 $flag$，当 $flag = 0$ 时，从队尾插入字符，否则从队首插入字符。如果读到 `R`，则将 $flag$ 取反。

而删除连续的两个相同字母也很容易，每次插入操作前比对队首或队尾的元素即可，注意这里如果队列为空，就要直接插入元素。

整理一下，代码就出来了，时间复杂度 $O(\lvert S\vert)$：

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
deque<char>t; //定义一个双端队列
bool flag; //flag 用来标记插入的位置
int main(){
	cin>>s;
	for(int i=0;i<s.size();i++){
		if(s[i]=='R')flag=!flag; //若需要反转插入方向，取反flag
		else if(!flag){
			if(!t.empty()&&t.back()==s[i])t.pop_back(); //如果有相同元素，弹出队尾
			else t.push_back(s[i]); //从队尾插入
		}else{
			if(!t.empty()&&t.front()==s[i])t.pop_front(); //如果有相同元素，弹出队首
			else t.push_front(s[i]); //从队首插入
		}
	}
	if(flag){
		while(!t.empty()){
			cout<<t.back(); //逆序输出队列
			t.pop_back();
		}		
	}else{
		while(!t.empty()){
			cout<<t.front(); //正序输出队列
			t.pop_front();
		}	
	}
	return 0; //养成好习惯
}


---

## 作者：Convergent_Series (赞：0)

首先肯定不能完全按题意模拟，每一个 ``reverse`` 时间复杂度均为 $O(|T|)$ ，超时。

考虑记录 $T$ 是否被翻转，如没有则在尾部追加，否则在头部追加。

使用手写双端队列解决，具体见代码。

---
```cpp
#include<bits/stdc++.h>
using namespace std;
struct tdeque{
	char a[1000010];
    //能不用循环队列就尽量不用，但是由于两端都要入队，所以空间开2倍
	int front=500001,rear=500000;
    //丛正中间开始，两端都有入队空间
	bool rev=0;//是否翻转
	void tpush(char x){
		if(rev==0){//尾部入队
			if(a[rear]==x) rear--;
         //如重复则连原先队尾一起去除
			else{
				rear++;
				a[rear]=x;
			}
		}else{//头部入队
			if(a[front]==x) front++;//同上
			else{
				front--;
				a[front]=x;
			}
		}
	}
}q;
string s;
int main(){
	cin>>s;
	int i;
	for(i=0;i<s.length();i++){
		if(s[i]=='R') q.rev^=1;//翻转
		else q.tpush(s[i]);		
	}
	if(q.rev==0){
		for(i=q.front;i<=q.rear;i++) cout<<q.a[i];
		cout<<"\n";
	}else{//输出时要翻转
		for(i=q.rear;i>=q.front;i--) cout<<q.a[i];
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：LikAzusa_ (赞：0)

### 题目传送门：[宇宙人からのメッセージ](https://www.luogu.com.cn/problem/AT_zone2021_d)
 ------

### 题目描述：

给出密文 $S$，解读方法如下：

设 $T$ 为空字符串。

$i=1,2,...,|S|$ 以下按顺序进( $|S|$ 表示 $S$ 的长度)。
 
$S$ 的第 $i$ 字母是 $R$ 时，将 $T$ 反转。

当 $S$ 的第 $i$ 个字母不是 $R$ 时，在 $T$ 的末尾加上该字母。

然后，如果 $T$ 中连续出现了两个相同的字母，就去掉这两个字母。尽可能地继续这个操作。(可以证明最终得到的字符串不会取决于去除的顺序)。

请输出通过以上操作得到的字符串 $T$ 。

### 思路：

看到数据范围，暴力肯定是过不了所有的测试点的。经过一番思索与模拟之后，我们可以发现，题目中的反转可以用非常简单的方式来实现。

我们发现，对于一个字符串 $T$，当它没有被反转的时候，新加进来的字符都是添加在 $T$ 的尾端，输出也是从头到尾正常地输出。

而当它被反转了，我们没有必要真正地反转它，只要在添加字符的时候把新加进来的字符添加在 $T$ 的头端，输出的时候从尾到头反向输出，即可完成反转的任务。

这时就需要一个 flag 来判断串 $T$ 是否被反转。

同时考虑判断重复的问题，当 $T$ 未被反转，我们在添加的时候判断 $T$ 的尾端第一个字符是否与当前插入的字符相同，如果相同就把尾端第一个字符弹出。当 $T$ 被反转时也是一样的，我们只需要在头端进行操作就行了。

思路清晰了，那么哪里有支持双端插入的数据结构呢？这时我们就要请出 STL 里的双端队列 deque 了！

deque 基本操作：
 
 ```cpp
#include <bits/stdc++.h>

using namespace std;

deque<int> que; //定义

int main()
{
	int n;
	cin >> n;
	que.push_front(n); //添加元素至队头 
	que.push_back(n); //添加元素至队尾 
	cout << que.front() /*队头元素*/<< endl;
	cout << que.back() /*队尾元素*/<< endl;
	que.pop_front(); //弹出队头元素 
	que.pop_back(); //弹出队尾元素
	bool flag = que.empty(); //判断队列是否为空 
	return 0;	
} 

```

有了这些操作，我们就能通过此题了！

###提示：当队列为空时，我们是不能取队头队尾元素的，所以在判断重复时要先判断队列是否为空。

### Code:

```cpp
#include <bits/stdc++.h>

using namespace std;

const int maxn = 5e5 + 5;
char a[maxn];
deque<char> que;
bool flag;

int main()
{
    scanf("%s",a+1);
    int len = strlen(a + 1);
    for(int i = 1; i <= len; i++)
    {
        if(a[i] == 'R')
        {
            flag ^= 1; //更新flag的状态 
        }
        else 
        {
            if(flag)
            {
                if(!que.empty() && a[i] == que.front()) que.pop_front(); //这个!que.empty()花了我两个中午来找 
                else que.push_front(a[i]);
            }
            else
            {
                if(!que.empty() && a[i] == que.back()) que.pop_back();
                else que.push_back(a[i]);
            }
        }
    }
    if(flag)
    {
        while(!que.empty())
        {
            cout << que.back();
            que.pop_back();
        }
    }
    else
    {
        while(!que.empty())
        {
            cout << que.front();
            que.pop_front();
        }
    }
    return 0;
} 

```

蒟蒻的第三篇题解，如有不足请提出！！！

---

