# Tree Summing

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=48

[PDF](https://uva.onlinejudge.org/external/1/p112.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA112/ee9b47e479d70c22d369ddb505af41da0aebc120.png)

## 样例 #1

### 输入

```
22 (5(4(11(7()())(2()()))()) (8(13()())(4()(1()()))))
20 (5(4(11(7()())(2()()))()) (8(13()())(4()(1()()))))
10 (3
(2 (4 () () )
(8 () () ) )
(1 (6 () () )
(4 () () ) ) )
5 ()```

### 输出

```
yes
no
yes
no```

# 题解

## 作者：柠檬熟了 (赞：2)

 **算法 $\textcolor{red}{\large \textbf {入门} }$，输入 $\textcolor{blue}{\large \textbf {提高+/省选} }$**

（再也不想做 UVA 的题

------

## 题意翻译

用 **某种方式** 给你棵树，判断**是否**有**从根到叶**经过的编号和为 $N$ 的路径。

## 题目分析

判断是否存在，即对树进行 **DFS** 遍历每种可能的路径，$sum$ 记录当前路径编号和。

到**叶子节点**时判断是否 $sum=N$  即可。

算法部分结束，听上去是不是十分简单？

于是，考虑怎样输入：

从样例中可以发现，本题的输入不是一般化的**给边建树**。

而是直接以**表达式形式**将整棵树输入，显然我们可以采取**递归读入**的办法。

（基本逻辑即读入左括号 $\to$ 深入，读入右括号 $\to$ 跳出

这里可以发现，递归读入的顺序与 **DFS** 的顺序完全相同。

故而这道题可以采用**在线算法**，即在读入时就对数据处理计算。

~~（噩梦的开始...~~


## 具体实现

**DFS** 自不必多说，仍然重点关注**读入**和**判断**。

（看代码里的注释！

```cpp
#include <bits/stdc++.h>
using namespace std;
int N;
char k;
int sum; //记录当前编号和 
int dep=0; //记录当前深度 调试 

bool dfs () { //深搜所有情况（极 低 的时间复杂度 
	bool Genshin=0, isleave=0; //Genshin记录是否能实现（从当前路径 ，isleave判断是否为叶子 
	int input; //记录当前输入 
	cin >> k; //读左括号 
	// cin 当正确读入时返回 0x486650，读入错误类型或 EOF 返回 0 
	//二叉树，重复两次输入 
	if (cin >> input)  //尝试读数，若成功 
		sum+=input, ++dep, Genshin=(dfs()||Genshin), --dep, sum-=input; //加数到当前和，递归，回溯 
	else isleave=1;//若失败，说明是右括号（类型错误返回 0），其无左子树 
	//记录其可能为叶子节点（无左子树） 
	
	/*
	cin.clear(ios::goodbit) (括号内可省略) 可将输入流重新定位到输入错误之前
		eg 
			不使用 cin.clear()
				int k;
				char c;
				cin >> k; 
				//此时输入")())(2(" （样例中递归到这一步可能出现的）， k 读入错误 
				cin >> c; 
				//此时 c 无数据，因为上一次读入已经将数据读完（流中空空 
			使用 cin.clear()
				int k;
				char c;
				cin >> k; //此时输入")())(2("， k 读入错误，流中剩余 "" 
				cin.clear(ios::goodbit) 
				//此时将输入重新定位到错误字符前，也就是 '(' 之前，流中当前 ")())(2(" 
				cin >> c; // c = ')' （正确取到右括号 
	*/ 
	
	cin.clear(ios::goodbit), cin >> k; //取右括号 
	
	if (dep>0) {
		cin >> k; //读入左括号 
		if (cin >> input) 
			sum+=input, ++dep, Genshin=(dfs()||Genshin), sum-=input, --dep;
		else if (isleave) //失败，说明是右括号，其无右子树，并且 isleave 说明其无左子树 
		//则其是叶子节点，直接判断当前和是否符合 
			Genshin=((sum==N)||Genshin); 
		//重整流并取右括号 
		cin.clear(ios::goodbit), cin >> k;
	}
	return Genshin;
}

int main () {
	while (cin >> N)  //读入整数部分（权值和 
		sum=0, cout << (dfs()?"yes":"no") << endl; //干这棵树 
	return 0;
}
```

纯净版

```cpp
#include <bits/stdc++.h>
using namespace std;
char k;
int sum, N, dep=0; 
bool dfs () { 
	bool Genshin=0, isleave=0; 
	int input; 
	cin >> k;
	if (cin >> input) sum+=input, ++dep, Genshin=(dfs()||Genshin), --dep, sum-=input; 
	else isleave=1;
	cin.clear(ios::goodbit), cin >> k;  
	if (dep>0) {
		cin >> k;
		if (cin >> input) sum+=input, ++dep, Genshin=(dfs()||Genshin), sum-=input, --dep;
		else if (isleave) Genshin=((sum==N)||Genshin); 
		cin.clear(ios::goodbit), cin >> k;
	}
	return Genshin;
}
int main () {
	while (cin >> N)  
		sum=0, cout << (dfs()?"yes":"no") << endl; 
	return 0;
}
```



---

## 作者：Eltaos_xingyu (赞：1)

这题主要算法最多**普及-**，输入的难度个人认为高达**省选**！（调输入的时间占做这题时间的九成！！！）

### 题目描述

给出一棵整数的二叉树，请写一个程序判定是否存在这样一条从树根到树叶的路，路上的结点的总和等于一个特定的整数。

这道题极其坑人的的点在判断两个儿子是否都为叶节点和输入上。

### 0x01 树的遍历

这里推荐使用在线算法，因为写起来简单。

很容易发现在每次读入数时，我们就到达了一个叶节点或一颗子树的根节点，这个时候可以加和，等到该节点的子树遍历完之后像自己的父亲，也就是上一个节点回溯。回溯的过程很简单，就是把当前的加和减去现在节点的值。

```cpp
//sign 是负数的标志
cin>>po;
sum+=po*sign;
dfs(dep+1);
dfs(dep+1);
sum-=po*sign;
```

那么，知道了如何加和，那如何比较结果呢？

对于这道题，显然是在叶子节点处比较结果。那么，如何判断是否为叶子结点呢？

### 0x02 判断是否为叶子节点

根据题意，叶子节点的格式是这样的：`(num()())`，要想判断叶子节点，就要判断两个空树。

方法一：如果读入第一个 `(` 后在探测下几个字符（探测的用法下一个部分要讲），如果为 `)()` 那就成功判断一个叶节点。

但是 C++ 自带的探测函数指针不后移，如果后移的话像 `()(...)` 这样的数据就会过度输入，对后面的遍历产生影响。

方法二：只探测每个树第一个 `(` 后是否为 `)`，如果是，就返回 $1$，如果一个节点的左右子树都是空树，那么才进行现在的加和与给定的数的比较。当然，探测到 `)` 后要指针后移，避免在下次遍历的开始读到右括号从而影响遍历。

```cpp
if(cin.peek()==')'){//探测下一个字符是否为')'
	cin.ignore();//指针后移
	return (sum==n);//可以返回 1，也可以直接返回比较结果
}
//...
temp+=dfs(dep+1);
temp+=dfs(dep+1);
if(temp==2){//如果在上面返回 1，这里就要进行比较
	flag=1;
}
```

那么这样的话，我们的递归函数的返回值就是该节点是否为子树，需要一个新的变量来存比较的结果。

主要算法都讲完了，但先别急，因为这道题的输入可以让你爆炸！！！

### 0x03 输入

我推荐的方法是用探测和指针后移的方式来实现左右括号的读入与判断。

先介绍函数，探测函数是 `cin.peek()`，这个函数返回该指针的下一个字符。后移函数是 `cin.ignore()`，这个函数使当前输入的指针后移一位。读入的时候就从后移后的下一个字符开始读入，后移后指针所指的字符不读入。

首先，我们要实现对于空格和换行的跳过：

```cpp
void space(){
	while(cin.peek()<=32)cin.ignore();//' ','\n','\r'的ASCII值都小于等于32
}
```

然后我们就在想要探测并跳过左右括号或者负号时，先去空格等字符，然后读入，判断，跳过就行了（但是很容易写错！！！）。

完整 AC 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
char k,kk;
long long n;
long long sum=0;
bool flag=0;
void space(){
	while(cin.peek()<=32)cin.ignore();
}
bool dfs(long long dep){
	long long po;
	long long temp=0;
	space();
	cin.ignore();
	space();
	if(cin.peek()==')'){
		cin.ignore();
		return (sum==n);
	}
	int sign=1;
	if(cin.peek()=='-'){
		sign=-1;
		cin.ignore();
	}
	space();
	cin>>po;
	sum+=po*sign;
	temp+=dfs(dep+1);
	temp+=dfs(dep+1);
	if(temp==2){
		flag=1;
	}
	sum-=po*sign;
	space();
	cin.ignore();
	return 0;
}
string s;
int main(){
	int u=0;
	while(cin>>n){
		flag=0;
		dfs(1);
		s=(flag)?"yes":"no";
		cout<<s<<endl;
	}
}
```


---

## 作者：影法师 (赞：1)

《论此题优雅的输入~》 本题其实处理io比题目本身要复杂一些

本题处理io的代码框架如下
```cpp
int tot, v[maxn]; // v[i]记录是i节点的权值
int dfs(int num) // 返回树的根节点, num是当前左括号个数
{
    读入 '(';
    ++tot; // 新开一个节点
    if(下一个非空白字符是数字)
    {
         scanf("%d", v + tot); // 读入此节点的权值
        int lson = dfs(num + 1); // 左孩子
        addarc(tot, lson);
        int rson = dfs(num + 1); // 右孩子
        addarc(tot, rson);
    }
    读入 ')';
    return tot;
}
```
判断yes或者no的代码如下
```cpp
int dfs(int cur, int sum) // cur是当前节点, sum是不包括cur在内迄今为止累计的权值和
{
    if(sum > target) // 剪枝
    {
        return 0;
    }
    if(cur是叶子 && sum + v[cur] == target)
    {
        return 1;
    }
    return dfs(lc, sum + v[cur]) || dfs(rc, sum + v[cur]); // lc是左孩子,rc是右孩子
}
```
处理io的代码最好使用namespace封装一个io操作, 类似于基于fread写的输入输出挂一样,这样比较优雅~ 毕竟面向对象嘛~

完整ac代码如下
```cpp
//#include "stdafx.h"
//#define LOCAL
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define re register int
#define ilv inline void
#define ilc inline char
#define ili inline int
const int maxn = 1e5+5;
int n, target, tot, v[maxn], lc[maxn], rc[maxn];
namespace fastio
{
    const int BUF = 1 << 21;
    char fr[BUF];
    int pr;

    ilc gc() // 读入一个字符
    {
        return fr[pr++];
    }

    ilv read(int &x) // 读入整型x
    {
        x = 0;
        char f = 1;
        char c = gc();
        while(!isdigit(c))
        {
            if (c == '-')
            {
                f = -1;
            }
            c = gc();
        }
        while(isdigit(c))
        {
            x = (x << 3) + (x << 1) + (c ^ 48);
            c = gc();
        }
        --pr; // 最后读入的不是数字, 所以要吐回去
        x *= f;
    }

    ilv read(char x) // 读入字符x
    {
        char c = gc();
        while(c ^ x)
        {
            c = gc();
        }
    }

    ilv read() // 一口气读入所有输入, 注意, fread可能会重复读入. 要根据fread的实际返回值判断真正读入的字节数
    {
        int len = fread(fr, 1, BUF, stdin);
        fr[len] = 0;
    }

    ili ck(char c) // 判断是否是合法字符(本题的合法字符只有数字、'('、')'、'-'四种)
    {
        return isdigit(c) || c == '(' || c == ')' || c == '-';
    }

    ilc peek() // 看看下一个非空白字符是啥?
    {
        char c = gc();
        while(!ck(c) && c) // 不合法就继续读
        {
            c = gc();
        }
        --pr; // 因为仅仅是peek, 所以窥视完了之后还要吐回去的~
        return c;
    }
} using namespace fastio;

int dfs(int cur, int sum)
{
    if (!cur)
    {
        return 0;
    }
    else if (!lc[cur] && !rc[cur])
    {
        return sum + v[cur] == target;
    }
    else
    {
        return dfs(lc[cur], sum + v[cur]) || dfs(rc[cur], sum + v[cur]);
    }
}

int dfs() // 返回当前子树的根节点
{
    read('(');
    int cur = 0;
    char c = peek();
    if (isdigit(c) || c == '-')
    {
        cur = ++tot;
        read(v[tot]);
        lc[cur] = dfs();
        rc[cur] = dfs();
    }
    read(')');
    return cur;
}

int main()
{
#ifdef LOCAL
    freopen("d:\\data.in", "r", stdin);
    //  freopen("d:\\ac.out", "w", stdout);
#endif
    read();
    while(peek())
    {
        read(target);
        tot = 0;
        dfs(); // 建树
        dfs(1, 0) ? puts("yes") : puts("no"); // 跑算法
    }
    return 0;
}
```


---

## 作者：bigclever (赞：1)

发现其他的题解好像都有点复杂，本蒟蒻来贡献一下自己的蒟蒻做法（大佬轻喷 $QAQ$）。
## 思路：
因为 S-表达式是递归定义的，所以我们也用递归的方式来输入和处理。这里**用一个 bool 函数**进行递归，如果它的返回值为真，则表示该节点不是叶子节点，反之亦然。

每次先读入一个字符，再读入一个数字。如果读入数字成功，那么和累加且递归去处理它的左儿子和右儿子；**递归结束后**，判断这个节点的左儿子或右儿子是否为叶子节点，如果是的话，再判断从树根到它的路径节点权值和是否为给出的特定整数，然后返回真。如果读入数字不成功，返回假。

讲的有些繁琐（~~主要是实在不知道怎么解释了~~），可以结合代码理解。
## Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int num;
bool ans;//判断是否有解
bool tree(int sum){
    int v; char c;
    cin>>c;
    if(cin>>v){//读入数字成功
        sum+=v;
        bool t=tree(sum)||tree(sum);//递归左右子树
        if(!ans&&!t)//如果暂时无解并且当前节点的子节点有叶子节点
            ans=(sum==num);//更新答案
        cin>>c;//读入右括号
        return true;
    }
    cin.clear(),cin>>c;//否则清理错误状态，再读入右括号
    return false;
}
int main(){
    while(cin>>num)ans=false,tree(0),puts(ans?"yes":"no");
    return 0;
}
```

---

## 作者：Scean_Tong (赞：0)

## 题目解析

本题给出一棵二叉树，要求判断是否存在一条从根到叶子节点的路径，其节点值之和等于给定的整数。我们可以通过递归遍历二叉树，并记录当前路径的节点值之和，来判断是否符合条件。

## 输入格式

输入文件包含若干个测试用例，每个用例占据一行，格式如下：

```
<给定的整数> <S-表达式表示的二叉树>
```

其中，S-表达式定义如下：

1. 空树表达式：`()`
2. 非空树表达式：`(value left right)`

其中，`value` 是当前节点的值，`left` 和 `right` 分别是左右子树的表达式。

上述表达式可能会占据多行，或包含空格。

## 解题思路

对于一棵树，我们可以通过递归遍历方式，记录当前路径的节点值之和，来判断是否存在一条符合条件的路径。我们需定义一个辅助函数来完成具体递归过程。

在实现的过程中，需要使用一个树节点类来构造树，并将S-表达式反序列化为树节点。

具体而言，我们可以使用深度优先搜索（DFS）的方法来遍历二叉树。每当搜索到一个非空节点时，我们先将其节点值加入当前路径的节点值之和（这里需要注意的是，如果当前节点是空节点，我们就直接返回节点值之和）。然后，我们继续递归遍历其左右子树，直到找到一个叶子节点。如果此时当前路径的节点值之和等于给定的整数，我们就返回 `True`；否则，我们就从路径中移除当前节点，并返回 `False`。



---

## 作者：_liet (赞：0)

比较简单的二叉树遍历问题，dfs 整棵树就行了，具体细节看代码：

```cpp
#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;
typedef long long ll;

int sum;
string tree;

// 解析 [l, r) 范围内的树
int parse(int cur, int l, int r) {
    if (r - l == 2) { // 如果是空树的话返回 -1
        return -1;
    }

    int val = 0, sign = 1, idx = l + 1;
    if (tree[idx] == '-') { // 判断负数
        sign = -1;
        idx++;
    }
    
    for (; idx < r; idx++) { // 计算当前节点的 integer
        if (tree[idx] == '(') {
            break;
        } else {
            val = val * 10 + tree[idx] - '0';
        }
    }
    val *= sign;

    int tempidx = idx, pcount = 0;
    for (; tempidx < r; tempidx++) { // 获取第一个节点的范围
        if (tree[tempidx] == '(') pcount++;
        else if (tree[tempidx] == ')') pcount--;
        if (pcount == 0) break;
    }

    // 递归解析左子节点
    int res1 = parse(cur + val, idx, tempidx + 1);

    idx = tempidx + 1;
    // 递归解析右子节点
    int res2 = parse(cur + val, idx, r - 1);

    if (res1 == -1 && res2 == -1) {
        // 如果两个子节点都是空树，则当前节点为叶子节点
        return cur + val == sum;
    } else {
        // 如果不是叶子节点则返回子节点的结果
        if (res1 == -1) return res2;
        if (res2 == -1) return res1;
        return res1 | res2;
    }
}

bool solve() {
    int pcount = -1;
    char ch;
    tree = "";

    // 读入整棵树并把树存到一个 string 里
    do {
        ch = getchar();
        if (isdigit(ch) || ch == '(' || ch == ')' || ch == '-') {
            tree += ch;
            if (ch == '(') {
                if (pcount == -1) pcount = 0;
                pcount++;
            } else if (ch == ')') {
                pcount--;
            }
        }
    } while (pcount != 0);

    // 解析整棵树
    int res = parse(0, 0, tree.length());
    if (res == -1) res = 0;
    return res;
}

int main() {
    while (~scanf("%d", &sum)) {
        if (solve()) {
            printf("yes\n");
        } else {
            printf("no\n");
        }
    }

    return 0;
}

```

---

