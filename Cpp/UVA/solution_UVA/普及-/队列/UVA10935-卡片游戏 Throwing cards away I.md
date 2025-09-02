# 卡片游戏 Throwing cards away I

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=21&page=show_problem&problem=1876

[PDF](https://uva.onlinejudge.org/external/109/p10935.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10935/04b5bf3f22988460c478d5e0eaad7b24fe43b5d4.png)

## 样例 #1

### 输入

```
7
19
10
6
0```

### 输出

```
Discarded cards: 1, 3, 5, 7, 4, 2
Remaining card: 6
Discarded cards: 1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 4, 8, 12, 16, 2, 10, 18, 14
Remaining card: 6
Discarded cards: 1, 3, 5, 7, 9, 2, 6, 10, 8
Remaining card: 4
Discarded cards: 1, 3, 5, 2, 6
Remaining card: 4```

# 题解

## 作者：zhang_kevin (赞：10)

[题目传送门](https://www.luogu.com.cn/problem/UVA10935)

# 前置知识：队列

这是一道很好的队列题，我先讲一下队列的基本知识。

1. 需要引入头文件 `queue` 。

2. 创建队列的格式为： `queue<队列类型> 队列名称` 。

3. 一些常用的操作： `q.pop()` 弹出队首元素， `q.push(x)` 将 $x$ 压入队列， `q.front()` 返回队首元素， `q.size()` 返回队列元素个数。

学会队列，这道题就简单多了。

# 解题思路

首先，我们将 $1 \sim n$ 这 $n$ 个数依次压入队列。

其次，只要队列中元素大于 $2$ 就输出队首元素，然后将第二个放到队尾。

等到队列中元素个数等于 $2$ 时，输出此时的队首元素并弹出。

最后，输出队列中唯一剩下的元素，完成一次数据处理。

注意特判 $n = 1$ 的情况。

# AC代码

```cpp
#include<iostream>
#include<queue>//队列头文件 
using namespace std;
void Solve(int n){
	queue<int> q;//创建一个队列 
	for(int i = 1; i <= n; i++){
		q.push(i);
	}
	cout << "Discarded cards: ";//提示信息 
	while(q.size() > 2){
		cout << q.front() << ", ";
		q.pop();
		int u = q.front();
		q.pop();
		q.push(u);
	}
	cout << q.front() << endl;
	q.pop();
	cout << "Remaining card: " << q.front() << endl;
	return;
}
int main(){
	int n;
	while(true){
		cin >> n;
		if(n == 0){
			break;
		}else if(n == 1){
			cout << "Discarded cards:" << endl; 
			cout << "Remaining card: 1" << endl;
		}else{
			Solve(n);
		}
	}
	return 0;
}
```


---

## 作者：__Watcher (赞：3)

### 终于有机会抨击一下STL了，大快人心啊！！！
细细一看，明显是一道模拟题，只要按照题目意思一步步丢牌、放牌，AC就在你的眼前了！！！！
模拟题没有必要说太多思路了，直接看代码
```cpp
#include<iostream>
using namespace std;
int a[100],r;//a数组模拟纸牌排序
int main(){
    int n;
    while(cin>>n){
        if(n==0)return 0;
        r=n;//12-23行对丢走1进行特殊处理，因为行末没有逗号
        if(n>1)cout<<"Discarded cards: 1";
        else {
            cout<<"Discarded cards:"<<endl;
            cout<<"Remaining card: 1"<<endl;
            continue;
        }//注意13-18行，细节决定成败
        for(int i=1;i<n-1;i++){
            a[i]=i+2;
        }
        a[n-1]=2;//第一次轮换
        n--;
        for(int i=1;i<r-1;i++){
            cout<<", "<<a[1];
            int p=a[2];//避免被迭代掉
            for(int j=1;j<n-1;j++){
                a[j]=a[j+2];//进行迭代
            }
            a[n-1]=p;//放牌
            n--;//丢了一张
        }
        cout<<endl<<"Remaining card: "<<a[1]<<endl;
    }
}

```
当你不会STL的时候，模拟STL永远是最好的选择

---

## 作者：Henry_ji (赞：3)

# UVA10935 卡片游戏 Throwing cards away I 题解

## 一、审题
本题的题目十分清晰，没什么需要额外解释的，模拟就行。

but，我觉得有必要在这里吐槽一下这个翻译，明明输出的冒号后面是有空格的，也不知道翻译的人怎么想的。

值得注意的是 $n = 1$ 时的输出应该时这样：

```text
Discarded cards:
Remaining card: 1
```

$\color{Red}\text{Discarded cards:后面没有空格}$

## 二、思路
我们来尝试一下模拟 $n = 5$ 时的操作过程
```text
[1, 2, 3, 4, 5]
[-1, 2, 3, 4, 5]      #将 1 号元素去掉（标注为 -1），并加入 discardList
[-1, -1, 3, 4, 5, 2]  #将 2 号元素去掉（标注为 -1），并放到队列末尾
[3, 4, 5, 2]          #截取队列的第 3 个元素到最后一个元素
[-1, 4, 5, 2]         #将 1 号元素去掉（标注为 -1），并加入 discardList
[-1, -1, 5, 2, 4]     #将 2 号元素去掉（标注为 -1），并放到队列末尾
[5, 2, 4]             #截取队列的第 3 个元素到最后一个元素
[-1, 2, 4]            #将 1 号元素去掉（标注为 -1），并加入 discardList
[-1, -1, 4, 2]        #将 2 号元素去掉（标注为 -1），并放到队列末尾
[4, 2]                #截取队列的第 3 个元素到最后一个元素
[-1, 2]               #将 1 号元素去掉（标注为 -1），并加入 discardList
[-1, -1, 2]           #将 2 号元素去掉（标注为 -1），并放到队列末尾
[2]                   #截取队列的第 3 个元素到最后一个元素
#此时队列仅剩 1 个元素，输出即可
```
显然，我们会发现：由于截取步骤的存在，我们就可以省略标注为 -1 这个步骤。

现在，我们已经理解了模拟的过程，那么程序也就很好写了。
## 三、AC 代码
以下程序为 Python 语言，但添加了注释，可作为参考

```python
while True:
    n = eval(input())
    if n == 0:  #循环输入直到 n = 0
        break
    elif n == 1:  #n = 1 时进行特判，直接输出
        print('Discarded cards:\nRemaining card: 1')
        continue
    cardList = []  #卡片列表
    discardList = []  #被删除的卡片列表
    for i in range(1, n + 1):
        cardList.append(i)  #初始化 cardList
    while len(cardList) != 1:
        discardList.append(cardList[0])  #把当前队列的第 1 个元素加入 discardList 
        cardList.append(cardList[1])  #把当前队列的第 2 个元素加入 cardList 的末尾
        cardList = cardList[2:]  #截取 cardList 的第 2 位到最后一位作为新的 cardList
    #以下是输出部分，不多说了
    print('Discarded cards: ', end='')
    for i in range(len(discardList) - 1):
        print(discardList[i], end=', ')
    print(discardList[-1])
    print('Remaining card: ', end='')
    print(cardList[0])
```
求管理通过~

---

## 作者：封禁用户 (赞：3)

```
人生苦短，我用STL
这题也是个大水题，，，，用STL的队列模拟即可

注意需要特判n == 1的情况，，，这里好坑
最下面贴出当时与标程对拍的情况

#include<cstdio>
#include<queue>

class Solver{
public:
	void solve(int n){
		std::queue<int> Q;
		
		for(int i = 1;i <= n;i++){
			Q.push(i);//从1~n压入队列
		}
		
		printf("Discarded cards: ");//先输出提示信息
		while(Q.size() != 2){//当队列至少有2人
			printf("%d, ",Q.front());//扔掉第一个并输出
			Q.pop();
			
			int u = Q.front();//将现在的第一个弹出并且重新压入队列且不输出
			Q.pop();
			Q.push(u);
		}
		printf("%d\n",Q.front());//输出倒数第二个
		printf("Remaining card: %d\n",Q.back());//输出留下的一个
	}
	
	void main(){
		int n;
		while((scanf("%d",&n) == 1) && n){//特判n==1
			if(n == 1){
				printf("Discarded cards:\n");//那个冒号后面没有空格的2333333
				printf("Remaining card: 1\n");
			}else{
				solve(n);
			}
		}
	}
};

int main(){
	//freopen("in.txt", "r", stdin);
	//freopen("out2.txt","w",stdout);
	
	(new Solver) -> main();
	
	return 0;
}


下面是在Windows下与标程对拍的结果:
正在比较文件 out.txt 和 OUT2.TXT
***** out.txt（这是标程）
Discarded cards:
Remaining card: 1
***** OUT2.TXT（我的）
Discarded cards: （这里前面比标程多了一个空格）。。。
Remaining card: 1
*****
```

---

## 作者：StayAlone (赞：2)

### 题意

现有 $n$ 张牌，从前到后以 $1$ ~ $n$ 编号，当牌数大于 $1$ 时，扔掉最前面的那张牌，同时把现在最前面的那张放到最后面。输出丢掉牌的顺序，再输出最后一张牌。


### 思路

双端队列。如有不了解的，先划到该题解最后了解一下。

首先将 $1$ ~ $n$ 插入队列： 

``for (int i = 1; i <= n; ++i) d.push_back(i);``

接下来一个 $\texttt{while}$ 循环：

`` while (d.size() > 1)``  

当队列内元素个数大于 $1$ 时，将前端输出并弹出，然后把现在前端的值插入后端，再将前端弹出。

最后输出队列内唯一的元素。  

题解区中呼声很高，甚至连翻译都要让大家注意特判，其实当你的代码足够严谨，类似这样的特判是不需要的。主要就是注意一下末尾别有空格，且原题中是每个测试数据后要有换行(英文原题很重要)就能通过这道题了。  

[AC code记录](https://www.luogu.com.cn/record/51294080)

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
deque <int>d;

int main()
{
    while (cin >> n)
    {
        if (!n) break;
        d.clear(); printf("Discarded cards:");
        for (int i = 1; i <= n; ++i) d.push_back(i);
        bool p = false; // 用于判断这次是否有逗号
        while (d.size() > 1)
        {
            printf(p ? ", %d" : " %d", d.front()); d.pop_front(); p = true;
            d.push_back(d.front()); d.pop_front();
        }
        puts("");
        printf("Remaining card: %d\n", d.front());
    }
    return 0;
}
```
```
deque<int> d; // 生成一个int类型的双端队列 d
d.push_front(x) // 双端队列头部增加一个元素 x
d.push_back(x) // 双端队列尾部增加一个元素 x
d.pop_front() // 删除双端队列中最前一个元素
d.pop_back() // 删除双端队列中最后一个元素
d.clear() // 清空双端队列中所有元素
d.empty() // 返回队列是否为空，返回true表示队列中无元素
d.size() // 返回队列中元素的个数
```

---

## 作者：sss7020 (赞：2)

他们用队列，我用不定长数组（VECTOR）。

```cpp
#include<iostream>
#include<vector>
using namespace std;
vector<int>a;
int main(){
	int n;
	while(cin>>n&&n){//输入至0结束
		a.clear();//别忘了清空
		for(int i=1;i<=n;i++){
			a.push_back(i);
		}把卡片压入数组
		cout<<"Discarded cards:";
        //我不明白为什么另外一位大佬的题解要把n==1独自作判断，开始不输出空格不就OK啦
		bool flag=true;
		while(a.size()!=1){//如果卡片数多于一张，就开始
			int t=a[1],out=a[0];
            //记录第1个（下标0）和第一个（下标1）
			a.erase(a.begin());
			a.erase(a.begin());//我喜欢这样删除
			a.push_back(t);//把第二个压入数组尾部
			cout<<(flag?" ":", ")<<out;
            //输出：如果是第一个的话，输出“ ”<<out,否则，输出“, ”<<out
			flag=false;
		}//
		cout<<"\nRemaining card: "<<a[0]<<endl;
	}
	return 0;
}
```
此题纯模拟，没有什么好讲的，STL万岁！

L('ω')┘三└('ω')｣

---

## 作者：lycx03 (赞：2)

## 纯STL队列模拟题
思路非常简单：现将1~n入队列，当队列大小不为1时，如下操作

①打印队首

②队首出队列

③队首入队列

④队首出队列

当队列大小为1，打印队首

**还有一个神坑，n=1时见以下输入输出**

**Input**
```
1
0

```
**Output**
```
Discarded cards:
Remaining card: 1

```
最后上简洁代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    queue<int>q;
    while(scanf("%d",&n)&&n)
    {
        bool f=1;
        for(int i=1;i<=n;i++) q.push(i);
	printf("Discarded cards:");
        while(q.size()!=1)
        {
            if(f) printf(" "),f=0;
            else printf(", ");
            printf("%d",q.front());
            q.pop();
            q.push(q.front());
            q.pop();
        }
        printf("\nRemaining card: %d\n",q.front());
        q.pop();
    }
    return 0;
}
```


---

## 作者：Symbolize (赞：1)

# 思路
用一个队列将 $1$ 至 $n$ 的所有数按顺序入队。然后根据题意模拟即可。

若队列长度大于 $1$，先将当前队首出队并输出，在将新的队首加入队尾，再把新队头出队。

一直循环，直到队列内只剩下一个数。最后在队列里的数即剩下的那个数，输出即可。
# Code
下面附上 AC 代码！！！
```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define x first
#define y second
#define rep1(i,l,r) for(int i=l;i<=r;i++)
#define rep2(i,l,r) for(int i=l;i>=r;i--)
using namespace std;
int n;
queue<int>q;
signed main()
{
    while(1)
    {
    	cin>>n;
    	if(n==0) return 0;
        bool res=1;
        rep1(i,1,n) q.push(i);//入队 
		printf("Discarded cards:");//不要打空格 
        while(q.size()!=1)//若队列长度大于1，循环 
        {
            if(res) cout<<' ',res=0;//防止多输出逗号 
            else cout<<", ";//记得打空格 
            cout<<q.front();//输出队头 
            q.pop();//队首出队 
            q.push(q.front());//新任队首加入队尾
            q.pop();//新任队首出队 
        }
        puts("");//换行 
        cout<<"Remaining card: "<<q.front()<<endl;//记得打空格 
        q.pop();//因为队内仅剩一个元素，所以直接pop即可清空队列 
    }
    return 0;//结束 
}
```

---

## 作者：caramel_qwq (赞：1)

本题推荐使用STL库里的队列容器。


------------

### 题意简述及注意事项
- 首先队列的入队一定得是 $1-n$ 的，否则输出肯定无序。
- 注意题目中强调的输出格式问题。


------------

### 题目分析
- 首先我们确认使用队列容器~~废话~~。
- 从 $1$ 到 $n$ 来入队
- 题目中说的操作方式我们来捋一捋，把第一张牌扔掉（也就是队列中的出队 ）。把扔完第一张牌后的牌堆的第一张牌，放到牌堆**底部**，也就是把第一个数入队，然后把之前的出队~~很好理解~~。
- 仍然是**空格**的问题，这个地方**我也踩了坑**，所以**着重**在下文说说。


------------
先看代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;
	while(cin>>n){
		if(n==0) break;
		if(n==1){
			printf("Discarded cards:\n");
			printf("Remaining card: 1\n");
			continue;
		}
		deque<int> q;
		for(int i=1;i<=n;i++){
			q.push_back(i);
		}
		printf("Discarded cards: ");
		while(q.size()>1){
			if(q.size()>2) printf("%d, ",q.front());
			else printf("%d\n",q.front());
			q.pop_front();
			q.push_back(q.front());
			q.pop_front();
		}
		printf("Remaining card: %d\n",q.front());
	}
	return 0;
}
```
现在来说说输入输出的问题，首先输入我们可以使用循环cin读入的方式来输入，因为cin这个函数如果没有输入流是会自动退出的，虽然在你的IDE可能看不出来。~~强烈推荐洛谷IDE~~

------
接下来我们来说输出的问题

- 首先是 $n=1$ 的情况，题目明确说了，如果你不是天然呆就不要我多哔哔。
> 当n=1的时候，应该输出Discarded cards:（此处没有空格）Remaining card: 1（有空格）

- 接着是 $n$ 不为 $1$ 的情况，也就是较为正常的情况，两个输出的冒号的后面都得带上空格。

---
好了以上就是这道题的分析+题解了。希望看到这的各位不要抄题解。~~你抄吧你抄吧反正洛谷查得出来~~

---

## 作者：NO1P (赞：1)

这道题就是用**队列**，但要注意，当只有一张牌时，需要特判根据题意直接输出。
```cpp
#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;
int n;
int main() {
	while(cin>>n && n!=0) {
		queue<int> q;
		for(int i=1; i<=n; i++) {
			q.push(i);
		}
		if(n==1) {	//特判，当等于1时所作
			cout << "Discarded cards: \n";
			cout << "Remaining card: 1\n";	//因为没有抛出的牌，所以直接输出1
		}
		else {
		int k=n;
		cout << "Discarded cards:";	//格式化输出
		while(k>=3) {
			k--;			
			cout <<' '<<q.front()<<',';	//注意逗号后有空格
			q.pop();
			q.push(q.front());
			q.pop();

		} 
		cout << ' ' << q.front() << endl;	//在最后输出时没有逗号
		cout << "Remaining card: " << q.back() << endl;	//输出最后的
		}
	}
	return 0;	//好习惯
}
```


---

## 作者：MINECRAFT_eternal (赞：0)

~~UVA的题都好水啊。~~

[题目传送门](https://www.luogu.com.cn/problem/UVA10935)

### 题目分析
其实题目已经很清晰了。

首先，我们需要建立一个队列：
```cpp
queue<int> q;
```

首先将每一个数入队。

在剩余卡片 $>2$ 时，对于每一次操作，我们都按照题目要求，把队首删除，并且将现在的队首移到队列的最后。

也就是说，老老实实用队列模拟一遍移牌过程即可。

当然别忘了 $1$ 的特判！！！

详细解释见代码。

# AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int main(){
	while(scanf("%d",&n)){
		if(n==0)
		  break;
		queue<int> q;     //每次建立一个队列
		if(n==1){     //特判
			puts("Discarded cards:");     //注意格式！！！
			puts("Remaining card: 1");
		}
		for(int i=1;i<=n;i++)
		  q.push(i);     //把1~n的每个数入队
		printf("Discarded cards:%d",q.front());     //格式问题......
		while(q.size()>2){     //如果队列元素大于2就进行操作
			q.pop();     //队首出队
			int x=q.front();
			q.pop();
			q.push(x);     //把队首调到最后
			printf(", %d",q.front());     //输出现在的队首
		}
		q.pop();
		puts("");
		printf("Remaining card: %d\n",q.front());     //幸存的卡片
	}
	return 0;
}
```

这道题并不难，只要有队列的基础，一般都能做对。

---

## 作者：CCF_zkskyer (赞：0)

# 这道题首先得看懂题目！！！

### 1.题目

[本蒟蒻自己找来的翻译，英语大佬自行跳过QaQ](https://www.luogu.com.cn/blog/298707/uva10935-ti-mu-fan-yi)

大概意思就是说，每次输入一个正整数$N$（$1 \leqslant N \leqslant 50$ ），然后从$1$到$N$依次入队，接着每次先输出队首，然后出队，接着让现在的队首（即以前的第二个数）出队，并重新排到队尾。最后直到队列中只有一个数后，结束操作。

因此我们发现这道题不就是**裸的队列模板题**吗？，看到楼上的大佬用了$vector$，感觉不需要，直接一个$queue$就行了，记得要用专属头文件：
```cpp
#include<queue>
```
或者如果你用的是万能头文件的话：
```cpp
#include<bits/stdc++.h>
```

当我没说$QwQ$。

### 2.代码
其实这道题真正要注意的是输入和输出，我不多赘叙，大家自己看上面的链接。

```cpp
#include <bits/stdc++.h> //懒人必备万能头。
#include<queue> //当然你用专属头文件也行 
using namespace std;

#define ri register int //宏定义是个好东西。 

int n; //输入正整数。 
queue <int> q; //因为每次操作完队列都是一个空队列，因此不用初始化。 

int main()
{
	//freopen("UVA10935.in","r",stdin);    文件输入输出是我用来 
	//freopen("UVA10935.out","w",stdout);  看输出格式是否正确的。 
	
    while(cin>>n) //这里先判断有没有输入。 
    {
    	if (n==0) return 0; //如果为零，结束。 
    	for (ri i=1;i<=n;++i)
    	{
    		q.push(i); //先从小到大入队。 
		}
		
		if (q.size()>1) //如果队列中数的个数大于一，就进行操作。 
		{
		    printf("Discarded cards: "); //首先输出这玩意。 
		    
			printf("%d",q.front());
			q.pop(); //由于它的输出很恶心，因此最前面一个先特殊输出。 
			
			int t=q.front();
			q.pop();
			q.push(t); //把第二个也放入队尾。 
			
			while(q.size()>1)
			{
				int top=q.front();
				printf(", %d",top); //每一个数要加上前面一个数的逗号。 
				q.pop(); //出队 
				top=q.front();
				q.pop();
				q.push(top); //当前队首放入队尾。 
			}
			
		printf("\n"); //每次操作完后别忘了换行。 
		}
		
        printf("Remaining card: %d\n",q.front()); //最后输出剩下的那个数。 
        q.pop(); //别忘了再出一次队列。 
	}

	return 0; //完美结束。 
}
```
 ### 3.结语
**如果你喜欢我的题解，就给我点个赞吧！！！**

# 谢谢观看！！！

---

