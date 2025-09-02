# Compression and Expansion

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1523C/da6104a926a977751ae03a3b556f0cead9b4ecdd.png)William is a huge fan of planning ahead. That is why he starts his morning routine by creating a nested list of upcoming errands.

A valid nested list is any list which can be created from a list with one item "1" by applying some operations. Each operation inserts a new item into the list, on a new line, just after one of existing items $ a_1 \,.\, a_2 \,.\, a_3 \,.\, \,\cdots\, \,.\,a_k $ and can be one of two types:

1. Add an item $ a_1 \,.\, a_2 \,.\, a_3 \,.\, \cdots \,.\, a_k \,.\, 1 $ (starting a list of a deeper level), or
2. Add an item $ a_1 \,.\, a_2 \,.\, a_3 \,.\, \cdots \,.\, (a_k + 1) $ (continuing the current level).

 Operation can only be applied if the list does not contain two identical items afterwards. And also, if we consider every item as a sequence of numbers, then the sequence of items should always remain increasing in lexicographical order. Examples of valid and invalid lists that are shown in the picture can found in the "Notes" section.When William decided to save a Word document with the list of his errands he accidentally hit a completely different keyboard shortcut from the "Ctrl-S" he wanted to hit. It's not known exactly what shortcut he pressed but after triggering it all items in the list were replaced by a single number: the last number originally written in the item number.

William wants you to help him restore a fitting original nested list.

## 说明/提示

In the second example test case one example of a fitting list is:

1

1.1

1.1.1

1.1.2

1.2

1.2.1

2

2.1

2.2

This list can be produced by using the sequence of operations shown below: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1523C/53b6f0dc8acf3fde4c975f74ee95364a6e7138d2.png)

1. Original list with a single item $ 1 $ .
2. Insert item $ 2 $ by using the insertion operation of the second type after item $ 1 $ .
3. Insert item $ 1.1 $ by using the insertion operation of the first type after item $ 1 $ .
4. Insert item $ 1.2 $ by using the insertion operation of the second type after item $ 1.1 $ .
5. Insert item $ 1.1.1 $ by using the insertion operation of the first type after item $ 1.1 $ .
6. Insert item $ 1.1.2 $ by using the insertion operation of the second type after item $ 1.1.1 $ .
7. Insert item $ 1.2.1 $ by using the insertion operation of the first type after item $ 1.2 $ .
8. Insert item $ 2.1 $ by using the insertion operation of the first type after item $ 2 $ .
9. Insert item $ 2.2 $ by using the insertion operation of the second type after item $ 2.1 $ .

## 样例 #1

### 输入

```
2
4
1
1
2
3
9
1
1
1
2
2
1
2
1
2```

### 输出

```
1
1.1
1.2
1.3
1
1.1
1.1.1
1.1.2
1.2
1.2.1
2
2.1
2.2```

# 题解

## 作者：住在隔壁小莘 (赞：3)

## 题目分析

我们只有两个操作：
1. 从末尾删除若干个数字（可以为 $0$ 个）然后把删除后的数字串的最后一个元素加一。
2. 将数字 $1$ 加入到数字串的末端。

- 操作二处理：我们会发现对于操作二，我们只需要把数字 $1$ 放到这一数字串的后面，**即在串尾添上一个数字1**。

- 操作一处理：对于操作一，例如在 $1.2.2$ 的情况下输入一个 $3$，那么这个 $3$ 的意思为进行操作一后结尾数字为 $3$，而这个 $3$ 又是在原数字串中某一位加一并把后面的串删去的来的。考虑如果你在某一次操作后看到的数字串末端元素值为 $x$：**那我们就可以从后往前找，找到第一个等于 $x-1$ 的数**（注意这里可以删去零位 $\to$ 即可以最后一位直接加一）。

为什么要从后往前而不是从前往后呢，是为了让选择更优，举个例子 $1.2.1.2$，输入 $3$，$3$ 后，先是变成 $1.3$，然后就会发现输入的第二个 $3$ 就无法实现了，而从后往前则是可以实现。

# Code:
```cpp
#include<iostream>
using namespace std;
int t,n,a[10000],num=0;
int main(){
	cin>>t;
	for(int i=1;i<=t;i++){
		num=0;
		cin>>n;
		int x;
		for(int j=1;j<=n;j++){
			cin>>x;
			if(x==1){
				num++;
				a[num]=x;
				if(num==1){
					cout<<a[1];
				}else{
					for(int k=1;k<num;k++){//注意输出是的点，最后不要多输出
						cout<<a[k]<<".";
					}
					cout<<a[num];
				}
				cout<<endl;
			}else{
				if(a[num]+1==x){
					a[num]+=1;
					if(num==1){
					cout<<a[1]<<endl;
					}else{
						for(int k=1;k<num;k++){
							cout<<a[k]<<".";
						}
						cout<<a[num];
					}
					cout<<endl;
				}else{
					for(int k=num;k>=1;k--){
						if(a[k]+1!=x){
							num--;
						}else{
							a[k]+=1;
							if(num==1){
							cout<<a[1];
							}else{
								for(int k=1;k<num;k++){
									cout<<a[k]<<".";
								}
								cout<<a[num];
							}
							cout<<endl;
							break;
						}
					} 
				}
			}
		}
	}
}
```


---

## 作者：Macesuted (赞：3)

[点击此处以获得更佳阅读体验](https://www.macesuted.cn/article/cf1523c/)

[题面](https://www.luogu.com.cn/problem/CF1523C)

# 题意

你有一个数字串，开始为空，每轮你可以进行下面两个操作中的一个：

1. 从末尾删除若干个数字（可以为 $0$ 个）然后把删除后的数字串的最后一个元素加一。
2. 将数字 $1$ 加入到数字串的末端。

现在告诉你你一共进行了 $n$ 次这样的操作，并且告诉你每一次操作完后数字串末尾的数字，让你找到一种可行的方案，并输出每次操作后的数字串。

# 分析

考虑如果你在某一次操作后看到的数字串末端元素值为 $x$：

1. 如果 $x=1$，上一次操作只可能是向数字串的末尾添加了一个 $1$。
2. 如果 $x > 1$，上一次操作只可能是删除了末尾若干个数字，删除后数字串末尾元素值为 $x-1$，然后让这个数字加一。

$x=1$ 时的构造方法是固定的，所以我们只需要关注 $x>1$ 时的情况。

容易发现，当数字串中含有多个值为 $x-1$ 的元素时，选取离末尾最近的值为 $x-1$ 的元素产生的答案比选离末尾较远的元素产生的答案不会更劣并且可能更优，所以当 $x>1$ 时我们从数列末尾删数直至末尾元素第一次为 $x-1$，然后停止继续操作，让尾部元素加一。

# 代码

使用栈模拟上述操作即可。

```cpp
/**
 * @author Macesuted (macesuted@qq.com)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 1005

int a[maxn];

int n;

list<int> li;

void work(void) {
    cin >> n;
    for (register int i = 1; i <= n; i++) cin >> a[i];
    for (register int i = 1; i <= n; i++) {
        if (a[i] == 1)
            li.push_back(1);
        else {
            while (!li.empty() && li.back() != a[i] - 1) li.pop_back();
            if (!li.empty()) li.pop_back();
            li.push_back(a[i]);
        }
        for (list<int>::iterator j = li.begin(); j != li.end(); j++) {
            if (j != li.begin()) cout << '.';
            cout << *j;
        }
        cout << endl;
    }
    li.clear();
    return;
}
```

---

## 作者：xujingyu (赞：1)

## 题意简述

对于一空的串可以进行两种操作：

* 在末尾加一个 $1$；
* 从末尾删除至少 $0$ 个字符，再将最后一个字符 $+1$。

现在知道每次操作后的末尾数字，求输出执行到那一步时，串是什么样的。

## 解答

一看到题面，我的第一反应就是[栈结构](https://baike.baidu.com/item/%E6%A0%88/12808149?fr=ge_ala)。栈先进后出，可以满足题面“在末尾加一个 $1$”与“删除字符”操作。现在分类讨论操作情况。

1. 当前末尾的是 $1$：直接对当前栈 `push(1)` 再输出即可；
2. 当前末尾非 $1$：不是 $1$，说明一定不是添加 $1$ 的操作。那么此时不断 `pop()`，知道栈头的值为当前末尾值 $-1$ 即可（因为删除那一堆数后将末尾 $+1$ 操作，刚好凑到满足条件的数）。

要注意的是，输出需要不断 `pop()`，所以输出后需要将栈还原；栈输出是反着的，所以还需要一个数组来将此正过来。


## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

stack <int> v,s;//s为将v还原的辅助栈
int t,n,x,a[1001],tot;

signed main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		while(!v.empty()) v.pop();//注意重置
		while(n--)
		{
			scanf("%d",&x);
			if(x == 1) v.push(1);//末尾为1
			else
			{
				while(!v.empty() && v.top() != x - 1) v.pop();//删除末尾的数
				v.top()++;//记得+1
			}
			if(v.empty()) continue;
			tot = 0;
			while(!v.empty())
			{
				s.push(v.top());
				a[++tot] = v.top();//逆着储存
				v.pop();
			}
			while(!s.empty())//还原
			{
				v.push(s.top());
				s.pop();
			}
			for(int i = tot;i >= 2;i--) printf("%d.",a[i]);//记得要输出"."
			printf("%d\n",a[1]);
		}
	}
	return 0;
}
```

---

## 作者：2011FYCCCTA (赞：0)

[原题](https://www.luogu.com.cn/problem/CF1523C)

---
### 思路

若当前输入的 $a$ 等于 $1$，那么进行操作二。

否则需在数字串中从后往前找到一个数字，满足它等于 $a - 1$，再进行操作一。

---
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int t , n , a;
int main()
{
    cin >> t;
    while (t--)
    {
        cin >> n;
        vector<int> num;
        for (int i = 1 ; i <= n ; i++)
        {
            cin >> a;
            if (a == 1) num.push_back(1);
            else
            {   
                while (num.back() != a - 1) num.pop_back();
                *(num.end() - 1) = a;
            }
            for (int i = 0 ; i < num.size() ; i++)
                cout << num[i] << (i == num.size() - 1 ? '\n' : '.');
        }
    }
    return 0;
}
```

---

## 作者：cloud2764scallop_eve (赞：0)

## 前言
多测不清零，亲人两行泪。

## 题意
对于一个空的数字串，有两种操作：  
1. 删除末尾的 $n$ 个 $(n \ge 0)$ 元素，并将修改后数字串的最后一个元素加一；
2. 在数字串末尾添加一个数字 $1$。

输入 $n$ 个元素，表示第 $n$ 次操作后数字串末尾的元素。

## 思路
首先考虑较为简单的操作二。

很明显，当添加的元素 $a = 1$ 时，我们可以直接使用操作二。当然，这也是操作二唯一的用途。

再考虑操作一。

当数字串中的数 $i$ 满足什么条件时，可以进行操作呢？思考一下可以得出，当 $i = a - 1$ 时，可以对其进行操作一。

那么现在思路就很明朗了，首先判断 $a$ 是否为 $1$，如果是，直接操作一；如果不是，枚举数字串直到找一个元素 $i = a - 1$，进行操作二。（这里可以默认题目给出的数据一定有解）。

在枚举时注意一个细节：倒序枚举。这样可以在数字串中保留尽可能多的元素，方便以后的运算。

最后考虑输出的细节，先不要输出数字串的末尾元素，这样方便按照格式输出。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e4 + 5;
int n, a, rcnt = 0;
int rem[N];
void init() {
	memset(rem, 0, sizeof(rem));
	rcnt = 0;
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		init();
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) {
			scanf("%d", &a);
			if (a == 1) {
				rcnt++;
				rem[rcnt] = 1;
			} else {
				for (int j = rcnt; j >= 1; j--) {
					if (rem[j] != a - 1) rcnt--;
					else {
						rem[j] = a;
						rcnt = j;
						break;
					}
				}
			}
			for (int j = 1; j < rcnt; j++) printf("%d.", rem[j]);
			printf("%d\n", rem[rcnt]);
		}
	}
	return 0;
}
```
> 多测不清零，亲人[两行泪](https://www.luogu.com.cn/record/141250372)。

---

## 作者：tmpliyijiang (赞：0)

## 思路
题目给我们 $2$ 个操作：

1.在数组末尾添加元素 $1$

2.从数组末尾删除 $k$ 个元素，并将最后一个元素加 $1$，其中 $k$ 为自然数

注意到数组中始终只存在正整数，因此对于输入为 $1$ 的情况，唯一方案是执行操作 $1$。

而对于其他输入，设为 $op$，倒序查找数组直到第一个值为 $op-1$ 的元素显然是一个可行的解。

其他说明：对于删除元素这一操作，并不需要真正执行，缩减数组范围即可（不过好像也不要紧，qwq）。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1005],id,op,n,t;
inline void put(){//输出
	if(id>1)//不判导致id-1<=0,死循环
		for(register int i=0;i<id-1;i++)
			printf("%d.",a[i]);//注意格式
	printf("%d\n",a[id-1]);
	return;
}
int main(){
	scanf("%d",&t);
	for(register int i=0;i<t;i++){
		scanf("%d",&n);
		for(register int i=0;i<n;i++){
			scanf("%d",&op);
			if(op==1){//操作1
				a[id]=1;
				id++;
			}
			else{//操作2
				while(a[id-1]!=op-1&&id)id--;
				a[id-1]++;
			}
			put();//输出
		}
		id=0;//多测初始化
		memset(a,0,sizeof(a));
	}
	return 0;
}

```

---

## 作者：xiaoyuchenp (赞：0)

简单的模拟题。

**思路**

将每一次操作分类讨论：

- 若末尾数字为 $1$，则直接在序列末尾添加入一个 $1$ 即可。

- 若末尾数字为当前序列末尾数字加上 $1$，显然直接累加即可（此时视为删除 $0$ 个数字再累加 $1$ 的情况）。

- 否则，则从序列末尾开始寻找比末尾数字小 $1$ 的数，再进行删除与累加操作即可。这一步可以采用栈或者普通数组模拟实现。这里直接采用数组模拟。

从后往前查找的原因：每一次都需要在删除最少数目的情况下使序列合法。若我们从前往后查找，不能保证策略的最优性以及往后输入数据的合法性。

输出时要注意最后一个数单独输出。

**code**

```cpp
#include<bits/stdc++.h>
#define MAXN 1005
using namespace std;
int t,n,s[MAXN],pos;
int num[MAXN];

int main(){
	cin>>t;
	while(t--){
		memset(num,0,sizeof(num));pos=0;
		cin>>n;
		for(int i=1;i<=n;i++)cin>>s[i];
		for(int i=1;i<=n;i++){
			if(s[i]==1)num[++pos]=1;
			else if(s[i]==num[pos]+1)num[pos]++;
			else{
				for(;num[pos]!=s[i]-1;pos--);
				num[pos]++;
			}
			for(int i=1;i<pos;i++)cout<<num[i]<<'.';
			cout<<num[pos]<<'\n';
		}
	}
	return 0;
}
```

---

## 作者：ImNot6Dora (赞：0)

纯模拟，没有什么技术含量。

首先定义 $k$ 为输入的数字，$p$ 为当前序列末尾数字。

通过观察发现操作中只有累加或者添加数字，那么经过思考，可以分为三种情况讨论：

1. 当 $k=1$ 时，只能加入新数字；

2. 当 $k=p+1$ 时，直接累加。

3. 否则，由于只能对末尾数字 $+1$，所以无论如何也无法使 $k=p$，所以只能向前寻找比 $k$ 小 $1$ 的数字进行累加，随后进行删除操作。

操作时直接开数组，并给末尾位置打上标记，这样就很简单了。

别忘了初始化。

## CODE：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int t,n;
int a[1010],st=0;//标记末尾 
void find(int k){//向前查找 
	for(;a[st]!=k;st--);
	a[st]++;//累加 
}
void print(){//输出 
	for(int i=1;i<st;i++){
		cout<<a[i]<<'.';
	}
	cout<<a[st]<<'\n';//注意最后的字符 
}
int main(){
	cin>>t;
	while(t--){
		memset(a,0,sizeof(a));//初始化 
		st=0;
		cin>>n;
		int k;
		for(int i=1;i<=n;i++){
			cin>>k;	 
			if(k==1)a[++st]=1;//分情况讨论 
			else if(k==a[st]+1)a[st]++;
			else find(k-1);//注意要找比k小1的数字 
			print();
		}
	}
	return 0;
}
```


By ZhouLuLaoShi

---

## 作者：expecto__patronum (赞：0)

## 大致题意
让你模拟写书的目录，但是对于每一行的情况，都只保留了最后一个数字。

要求，还原出一个合法的目录。
## 解题思路
首先我们考虑到“ 1 ”这个数字，他比较特殊，因为这表示我们必须新开一点。

然后对于其余的所有数字，我们的做法是，能保证上一行尽可能少删除的情况下，使得当前情况合法。

因为我们一旦把某些点删除了，我们再开新行的时候，就再也不能返回去用了。 且我们也可以保证在这种情况下，可以得到最优解，因为之前出现过的每一点，也必然都是之前给出过的数字。 因此如果给出的序列是合法的，必然我们可以回溯到合法位置。

### AC代码。
```
#include <bits/stdc++.h>
#define rep(i, n) for (int i = 1; i <= (n); ++i)
using namespace std;
typedef long long ll;
int main()
{
	int t; cin >> t;
	while (t--) {
		vector<int> v;

		int n; scanf("%d", &n);
		rep(i, n) {
			int x; scanf("%d", &x);
			if (x > 1) {
				while (!v.empty() and v.back() + 1 != x) v.pop_back();
				v.pop_back();
			}
			v.push_back(x);

			rep(i, v.size()) {
				if (i > 1) putchar('.');
				printf("%d", v[i - 1]);
			}
			puts("");
		}
	}
	return 0;
}

```
管理大大求过！！

[博客食用更方便。](https://blog.csdn.net/weixin_45799835/article/details/117420915)

---

## 作者：ylch (赞：0)

# CF1523C Compression and Expansion 题解

[-题目传送门-](https://www.luogu.com.cn/problem/CF1523C)

## 题目翻译

### 题目描述

你有一个数字列表（初始为空），有两个操作：

1. 从列表末尾删除若干个数字（可以为 $0$ 个）然后把删除后的数字列表的最后一个元素加一。

2. 将数字 $1$ 加入到数字列表的末端。

现在告诉你你一共进行了 $n$ 次这样的操作，并且告诉你每一次操作完后数字列表末尾的数字，让你找到一种可行的操作方案，并输出每次操作后的数字列表。

### 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$（$1\le t\le 10$）。测试用例的描述如下。

每个测试用例的第一行包含一个整数 $n$（$1\le n\le 10^3$），这是列表中的行数。

接下来的 $n$ 行中的每一行都包含一个整数 $a_i$ （$1\le a_i\le n$），这是操作后数字列表末尾位置的数。

保证在每个测试用例中至少存在一个数字列表。

保证所有测试用例的值 $n$ 之和不超过 $10^3$ 。

### 输出格式

对于每个测试用例，输出 $n$ 行，每一行表示经过当前操作操作后可能的数字列表，元素之间用 `.` 隔开。

如果有多个答案，请打印任意一种答案。

## 解题思路

其实这就是一道简单的模拟，并不涉及到贪心，解法在题面里面已经写得非常清楚了。

按照操作去分析这道题目：

- 对于操作 $1$：因为可以进行加一的操作，就按照题意，从末尾开始查找，找到第一个等于输入数字减一的数字位置（因为肯定删除的越少越好），就把这一位置后面的全部删掉，当前位置加一。

- 操作 $1$ 举例：当前数字列表为 $1.21.1.34$ 时，输入 $2$，按照策略，操作完的数字列表应该为 $1.21.2$。可以证明这是最好的操作方案。

- 对于操作 $2$：依据题意，只要在当前列表末尾加入一个数字 $1$ 就行了。

提示：因为题目中明确说了列表，我们可以用 C++ 中的 vector 模板去解决问题，节省代码量。

## AC 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1005;

vector<int> v;

void solve()
{
	int n,x;
	cin >> n;
	for (int i=1; i<=n; i++)
	{
		cin >> x;
		if (x == 1)	v.push_back(1);
		else
		{
			while (v.size() && v.back() != x-1)	v.pop_back();
			if (v.empty())	v.push_back(x);
			else	v.back() = x;
		}
		for (unsigned i=0; i<v.size(); i++)
		{
			if (i > 0)	putchar('.');
			cout << v[i];
		}
		cout << endl;
	}
	v.clear();
}

int main()
{
	int T;
	for (cin >> T; T--; )	solve();
	return 0;
}
```

End
------------

管理员大大辛苦啦~

谢谢大家！有错误欢迎指出，我们一起进步，一起 $rp++$！

---

