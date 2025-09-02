# [ARC042A] 掲示板

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc042/tasks/arc042_a

$ 1 $ から $ N $ までの番号がついたスレッドのある掲示板があります。 スレッドは書き込みがあると一番上に来ます。 書き込み前のスレッドは上から順に $ 1 $ から $ N $ の順に並んでいました。 $ M $ 個の書き込みが書き込まれた順で与えられるので、全ての書き込みが終わった後のスレッドの順番を出力してください。

例えば、$ 3 $ 個のスレッドがある掲示板に $ 2 $、$ 3 $、$ 1 $ の順で書き込みがあると、以下のようになります。

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_arc042_a/bac8cb43a2c36713e87d6142d247ade9a4ca302d.png)

従って、書き込み後のスレッドの順番は $ 1 $、$ 3 $、$ 2 $ となります。

## 说明/提示

### 部分点

この問題には部分点が設定されている。

- $ 1\ ≦\ N\ ≦\ 100,\ 1\ ≦\ M\ ≦\ 100 $ を満たすデータセットに正解した場合は $ 30 $ 点が与えられる。

### Sample Explanation 1

$ 1 $ つめの書き込みの後、スレッドは上から $ 2 $、$ 1 $、$ 3 $ の順で並んでいる。 $ 2 $ つめの書き込みの後、スレッドは上から $ 3 $、$ 2 $、$ 1 $ の順で並んでいる。 $ 3 $ つめの書き込みの後、スレッドは上から $ 1 $、$ 3 $、$ 2 $ の順で並んでいる。

### Sample Explanation 2

元から $ 1 $ 番上にあったスレッド $ 1 $ にしか書き込みがなかったので、スレッドの順番は変わらない。

## 样例 #1

### 输入

```
3 3
2
3
1```

### 输出

```
1
3
2```

## 样例 #2

### 输入

```
3 3
1
1
1```

### 输出

```
1
2
3```

## 样例 #3

### 输入

```
10 10
3
1
4
1
5
9
2
6
5
3```

### 输出

```
3
5
6
2
9
1
4
7
8
10```

# 题解

## 作者：Harry27182 (赞：5)

通过样例，我们很容易看出，按照输入的顺序倒着输出就是答案。所以我们可以得到以下思路：

按照输入顺序倒着枚举，同时建一个$bool$数组，标记这个数有没有输出过。如果没输出过，就直接输出，同时打上标记，否则就直接$continue$掉。
代码如下：
```cpp
for(int i=m;i>=1;i--)
{
   if(b[a[i]]==true)continue;
   b[a[i]]=true;
   cout<<a[i]<<endl;
}
```
然后从一向后枚举，找到没标记的数，直接输出即可。代码如下：
```cpp
for(int i=1;i<=n;i++)
{
   if(b[i]==true)continue;
   cout<<i<<endl; 
}
```
完整代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int a[100005];
bool b[100005];
int main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		cin>>a[i];
	}
	for(int i=m;i>=1;i--)
	{
		if(b[a[i]]==true)continue;
		b[a[i]]=true;
		cout<<a[i]<<endl;
	}
	for(int i=1;i<=n;i++)
	{
		if(b[i]==true)continue;
		cout<<i<<endl; 
	}
	return 0;
}
```


---

## 作者：MZY666 (赞：3)

题解区可真是八仙过海呀，先在此表达对其它题解的敬仰之情。

来介绍一个较简单的方法。

[原题传送门](https://www.luogu.com.cn/problem/AT1409)。[在窝的博客中食用更佳](https://www.luogu.com.cn/blog/MZY666/solution-at1409)。

### 【 题意概括 】

先输入一个正整数 $n$ ，表示有一个 $n$ 个数的数列，其中第 $i$ 个数的初始值为 $i$ 。

随后输入一个正整数 $m$ ，表示有 $m$ 次操作。

接下来 $m$ 行每行输入一个正整数 $a$ ，表示把这个数列中值为 $a$ 的那一项移动到最前面来。

操作完毕后输出当前数列即可。每个数都要分行输出。

### 【 思路 】

对于提到前面的数，按往前提的顺序倒着先输出即可。

什么意思呢？咱们来陪着代码消化：

用一个整型数组 $a$ 储存输入的要求进行操作的数。

用一个布尔数组 $used$ 记录被提到前面过的数。

```cpp
int a[1000005];
bool used[1000005];//初始值为false
for(i=1;i<=m;i++)scanf("%d",&a[i]);
for(i=m;i>=1;i--){//从后往前
	if(!used[a[i]]){//如果这个数之后没有再次被提到最前面
		printf("%d\n",a[i]);//输出这个数，记得换行
		used[a[i]]=true;//标记，提过这个数
	}
}
```

随后再依次输出没有被提到前面的数即可。

来，是时候看看全盘代码了。

### 【 代码实现 + 注释 】

```cpp
#include<bits/stdc++.h>//万能头文件可好 
using namespace std;
int a[1000005];
bool used[1000005];//初始值为false
int main(){//主函数 
	int n,m,i;//定义 
	scanf("%d%d",&n,&m);//输入 
	for(i=1;i<=m;i++)scanf("%d",&a[i]);//输入 
	for(i=m;i>=1;i--){
		if(!used[a[i]]){
			printf("%d\n",a[i]);//输出，记得换行
			used[a[i]]=true;//标记
		}//上文有解释
	}
	for(i=1;i<=n;i++)
		if(!used[i])printf("%d\n",i);//依次输出没有被提到前面的数
	return 0;//over~
}
```

~~这算不算是一种投机取巧的方法？~~ 算了，能A才是王道。

最后，由于作者自愿禁言了，如果有建议请私信。否则将**无法**回复您哦！

完结撒花~（疯狂暗示 AOA

---

## 作者：Kevin_Zhen (赞：3)

# 链表题解
题目链接 [AT1409](https://www.luogu.com.cn/problem/AT1409)
## 题目大意
给你一个序列 $1-n$，进行 $m$ 次操作，每次将值为 $a$ 的一项移到序列首位。
## 变量介绍
1. $n$ 为序列中数的个数。
2. $m$ 为操作个数。
3. 结构体 $node$，$data$ 记录此节点的值，$next$ 记录前驱，$prev$ 记录后继。

## 解题过程
### 1.初始化
```cpp
a[0].next = 1; 
for (int i = 1; i <= n; ++i) {
	a[i].data = i;
	a[i].next = i + 1;
	a[i].prev = i - 1;
}
```
对链表进行初始化（包括赋值、记录前驱和后继），注意 $a[0].next$ 也要赋值，用于记录队首元素。  

### 2.修改操作
```cpp
int k = readInt();
a[a[k].next].prev = a[k].prev;
a[a[k].prev].next = a[k].next;
a[k].next = a[0].next;
a[k].prev = 0;
a[a[0].next].prev = k;
a[0].next = k;
```
将修改节点 $k$ 取出并插入队首，并及时更新 $k$ 的前驱的后继、后继的前驱，$k$ 的前驱和后继，$0$ 号节点的后继的前驱和 $0$ 号节点的后继。文字描述比较绕，可以结合代码理解。

### 3.输出 
```cpp
int s = a[0].next;
while (a[s].data != 0) {
	printf("%d\n", a[s].data);
	s = a[s].next;
}
```
遍历整个链表，输出每一个节点的值。
### 4.时间复杂度
时间复杂度 $O(n)$。
## AC CODE
```cpp
#include <iostream>
#include <cstdio>
#include <cctype>

inline int readInt() {
	int s = 0, c;
	while (!isdigit(c = getchar()));
	do s = s * 10 + c - '0';
	while (isdigit(c = getchar()));
	return s;
}

struct node{
	int data = 0;
	int prev, next;
} a[100010];

int n = readInt(), m = readInt();

int main() {
	a[0].next = 1; 
	for (int i = 1; i <= n; ++i) {
		a[i].data = i;
		a[i].next = i + 1;
		a[i].prev = i - 1;
	}
	for (int i = 1; i <= m; ++i) {
		int k = readInt();
		a[a[k].next].prev = a[k].prev;
		a[a[k].prev].next = a[k].next;
		a[k].next = a[0].next;
		a[k].prev = 0;
		a[a[0].next].prev = k;
		a[0].next = k;
	}
	int s = a[0].next;
	while (a[s].data != 0) {
		printf("%d\n", a[s].data);
		s = a[s].next;
	}
	return 0;
}
```
## 感谢观赏！

---

## 作者：infinities (赞：3)

## AT1409 题解


[~~没好好看题者请自行回去看题~~](https://www.luogu.org/problem/AT1409)

我的思路：

- 输入之后倒着扫一遍

- 如果和前面的重复了就忽略不计

- 最后再从0到n扫一遍，看有什么数没操作就输出。

-------------------------
看代码理解吧，注释都在里面：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n,m,a[100801],num[208002];//定义各变量
    cin>>n>>m;//输入*1
    for(int i=m;i>=1;i--)cin>>a[i];//输入*2
    for(int i=1;i<=m;i++)
    if(num[a[i]]++/*综合写法，相当于去掉++在后面加上一句：num[a[i]]++;*/==0)
    cout<<a[i]<<endl;//输出，因为从后往前扫，相当于最后提到最前面的，可以直接输出
    for(int i=1;i<=n;i++)if(num[i]==0)cout<<i<<endl;//如果没有过操作，输出（注意换行）
    return 0;//结束
}
```
此代码经过压行，不习惯者请自行调整。


----------------------------------------

补充一句：此题较水，不要被难度误导，在整个OI界内都是这个道理。

---

## 作者：Trump__Biden (赞：2)

[传送门](https://www.luogu.com.cn/problem/AT1409)

题意分析
-----------
将第 $i$ 个数提到第一个并输出，也就是倒着扫并输出。倒数第一成为第一，倒数第二成为第二，以此类推，输出该数后标记，最后再枚举一遍，如果没有输出就将它们按正序输出。

思路
------------
定义一个 bool 数组，记录输出与否，如果它为 false 就把它改为 true 且将它输出，下次就不用输出了。然后再从头至尾扫一遍，如果没有输出就将它输出并换行。

```
#include<iostream>
#include<cstdio>
#include<string>
using namespace std;
int n,m,a[100005];//根据题意定义 
bool s[100005];//初始值为false 
int main()
{
	scanf("%d%d",&n,&m);//输入 
	for(int i=1;i<=m;i++)
	  scanf("%d",&a[i]);//输入 
	for(int i=m;i>=1;i--)//倒序枚举 
	{
		if(!s[a[i]])//没有输出
		{
			s[a[i]]=true;//标记 
			printf("%d\n",a[i]);//切记要换行！！！			
		}
	}
	for(int i=1;i<=n;i++)//寻找没有输出的 
	{
		if(s[i]==true)
          continue;//判断 
		printf("%d\n",i);//换行！！！ 
	}
	return 0;
}
```

该题解借鉴了本题题解中许多大佬的思路,
下面列出几位大佬：
@olkieler，@MZY666，@Harry27182，
集合大佬的思路，加入自己的风格和理解，写出了一篇自认为蒟蒻可以看懂的题解。

最后弱弱地说一下:

这是蒟蒻的第一篇题解，不好请私信。

求 daolao 勿喷！！


---

## 作者：Anaxagoras (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT1409)

思路：

开始是一个 $1\sim n$ 的序列，每次把数字 a 提到最前面，求最后所得到的序列。

既然这样，那么后提前的数字自然更前，即最后提前的在第一，倒数第二个在第二...但是要注意，可能会输入重复的数，所以我们要把已经输出过的数标记。

最后没有被提前的就会仍然按照原来的顺序，按原顺序输出没有标记的数即可。

AC Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100005];
bool t[100005];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);//加速输入输出
	int n,m;
  cin>>n>>m;
  for(int i=1;i<=m;i++)
    {
      cin>>a[i];
    }
  for(int i=m;i>=1;i--)
    {
      if(!t[a[i]])
        {
      	  t[a[i]]=!t[a[i]];
          cout<<a[i]<<'\n';
        }
    }
  for(int i=1;i<=n;i++)
    {
      if(!t[i])
      cout<<i<<'\n';//按顺序输出
    }
	return 0;
}
```

写题解不易，求过路之大佬与赞于我！

---

## 作者：vectorli1 (赞：2)

### Problem:
[原题目链接](https://www.luogu.com.cn/problem/AT1409)  

---

有个包含$n$个数的序列，第$i$个数为$a_i$。现有$m$次操作，包含一个数字$t$，意为将数字$t$提到第一个来，其它数字往后顺移$1$位。

现在，给定这样的$n$个数$1,2,3...n$和$m$次操作，问你操作完之后的数列是多少？
### Solution:
用一个结构体存储数据的数值和被提到第一个的时间，数据存储后倒着操作，最后结构体快排即可解决问题。  
没听懂，请看下面的详细指导。  
先定义一个结构体，内含数值和被提到第一个的时间。
```cpp
#define MAXN 100005
struct card
{
	int num;//数值
	int tim;//提到第一个的时间
};//不要忘写分号
struct card a[MAXN];
```
在输入前先将每一个的变量初始化，但注意，时间一定要设成一个很大的数（这里也用了MAXN）。
```cpp
for(int i=0;i<n;i++)
{
    a[i].num=i+1;
    a[i].tim=MAXN;//时间先调成一个很大的数
}
```
把每次操作都存到数组里，因为要从后向前设定时间。  
```cpp
int cnt=0;//一定要初始化！
int b[MAXN];
for(int i=0;i<m;i++)
    b[i]=read()//这里使用了快读
for（int i=m-1;i>=0;i--)//数组下标是从零开始的，所以循环条件比较特殊
{
    if(a[b[i]-1].tim==MAXN)//如果是第一次添加时间，就添加
    {
    	a[b[i]-1].tim=cnt;
        cnt++;//记录添加的时间
    }
}
```
定义比较函数
```cpp
bool cmp(struct card a, struct card b)
{
    if(a.tim!=b.tim)
    	return a.tim<b.tim;//如果插入时间不相等，就按照插入时间排序
    return a.num<b.num//否则按照数值排序
}
```

最后输出即可，代码放下面

### Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define MAXN 100005
#define inf 0x3f3f3f3f
struct card
{
    int num;
    int tim;
};
inline int read()
{
    int o=1, a=0;
    char c=getchar();
    while((c<'0'||c>'9')&&c!='-') c=getchar();
    if(c=='-') o=-1, c=getchar();
    while(isdigit(c)==1) a=(a<<3)+(a<<1)+(c-'0'), c=getchar();
    return o*a;
}//快读
inline void write(int a)
{
    if(a<0) putchar('-'), a=-a;
    if(a>9) write(a/10);
    putchar(a%10+'0');
}//快写
bool cmp(struct card a, struct card b)
{
    if(a.tim!=b.tim)
        return a.tim<b.tim;
    return a.num<b.num;
}
int main()
{
    struct card a[MAXN];
    int n, m;
    int b[MAXN];
    int cnt=0;
    n=read(), m=read();//read
    for(int i=0;i<n;i++)
    {
        a[i].num=i+1;
        a[i].tim=MAXN;
    }
    for(int i=0;i<m;i++)
        b[i]=read();//read
    for(int i=m-1;i>=0;i--)
        if(a[b[i]-1].tim==MAXN)
        {
            a[b[i]-1].tim=cnt;
            cnt++;
        }
    sort(a, a+n, cmp);
    for(int i=0;i<n;i++)
    {
        write(a[i].num);
        puts("");
    }
    return 0;
}
```
---
本人的第一篇题解，求通过，如果有写的不好的地方或者hack，请通知我谢谢。

---

## 作者：COsm0s (赞：0)

## 思路：

+ 开始是一个 $1 \sim n$ 的序列，每次把数字 $x$ 放到最前面，求操作完后所得到的序列。

+ 由此可知，最后输入的数字会在最前面输出，倒数第二个在第二，以此类推。但是要注意，**可能会输入重复的数**，所以我们要用 bool 类型的数组把已经输出过的数标记。

+ 没有被操作的会按照原来的顺序，按原顺序输出没有标记的数即可。

+ 其实是在做一个栈的工作，只不过需要去重。

复杂度：$O(n+m)$。

## Code：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
inline int read() {
	int x = 0, m = 1;
	char ch = getchar();
	while(!isdigit(ch)) {
		if(ch == '-') m = -1;
		ch = getchar();
	}
	while(isdigit(ch)) {
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	return x * m;
}
inline void write(int x) {
	if(x < 0) {
		putchar('-');
		write(-x);
		return;
	}
	if(x >= 10) write(x / 10);
	putchar(x % 10 + '0');
}
//快读快输 
const int N = 1e5 + 10;
int a[N];
bool vis[N];
signed main() {
	int n = read(), m = read();
	for(auto i = 1; i <= m; i ++){
		a[i] = read();
	}
	for(auto i = m; i >= 1; i --){
		int x = a[i];
		if(vis[x]) continue;//去重 
		write(x),puts("");
		vis[x] = 1;
	}
	//倒序输出 
	for(auto i = 1; i <= n; i ++){
		if(!vis[i]) write(i),puts("");
	}
	//未操作的正序输出 
	return 0;
}
```


---

## 作者：wangyi_c (赞：0)

## 题意讲解

观察输入输出的样例，“ 将 $a$ 提到第一个 ”，本意就是从后往前扫并输出，倒数第一到第一，倒数第二到第二，以此类推，但是输出过的就不能再次输出。另外那些第一遍没有被输出的第二次按原顺序输出就行了。

## 思路讲解

因为样例二中，有去重的操作，所以说要用 $f$ 数组来标识，每发现一个 $f_i=0$ 的 $i$，就修改为 $1$，这样下一次再遇到就可以跳过不输出了。

在最后，还要从 $1$ 枚举到 $n$，发现没有遇到过的 $i$，把它输出就可以了。
别忘了换行哦~

## AC代码

```cpp
#include<bits/stdc++.h>
#define int long long//开long long，保证不见祖宗
using namespace std;
int f[100010],a[100010],n,m;
signed main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>a[i];
	}
	for(int i=m;i>=1;i--){
		if(!f[a[i]]){//如果f[a[i]]没输出过
			cout<<a[i]<<"\n";
			f[a[i]]=1;//改变f[a[i]]的状态
		}
	}
	for(int i=1;i<=n;i++){//扫一遍，如果没遇到过就输出
		if(!f[i]){
			cout<<i<<"\n";
		}
	}
	return 0;
}
```
感谢观看

 _THE END_
 
By wangyi

---

## 作者：Mr_WA的大号 (赞：0)

莫愁天下无知己，天下谁人不识君。小学生又来发题解了！

题号：AT1409

难度：★★★

算法：栈

## 开课了！

这题本身并不难，就是一道数学题。相信大家都知道，我们的数字最后调的，就在最前面。倒数第二个调的，就在倒数第二个......

这就可以说是我们栈的思想，也是我们这题解答的重要思想。

栈，总的来说就是一个先进后出，后进先出的数据结构。

所以，这一题我们可以选用栈这一算法来做。总的来说可以分为3大步骤。

1.输入。栈的输入方式有所不同，要新定义一个top变量，表示当前那一位是下一个数字存的位置。（本来还要定一个bottom变量表示最底部，但因为bottom一直为0，所以可以省略不写）

2.用栈的思想去查找。这里我们多定义了一个数组frequency，标记这一数字有没有输出过。没输出过就输出，将frequency[i]标记为用过。否则查找下一位。

3.补充输出。因为有些数字可能在第二步没有输出，所以这一步我们从1~n查找frequency，如果frequency[i]标记为没用过，就输出i。

注意：数组要开到100000及以上 ~~我不会告诉你我数组开太小WA了~~ 

答题步骤讲完了，上代码：
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
int n,m,a[100010],frequency[100010],top;//定义。frequency数组可以定义为bool型，因为frequency数组只是用来判定数字是否被用过。
int main()
{
	//第一大步骤：输入
	cin>>n>>m;
	while(top<m)
	{
		cin>>a[top++];//栈的特殊输入方式。把这条语句拆开来就是：cin>>a[top];top++;
	}
   //第二大步骤：查找。
	while(top>0)
		if(frequency[a[--top]]==0)//如果当前的最高位没有用过
		{
			cout<<a[top]<<endl;//输出
			frequency[a[top]]=1;//标记为使用过
		}
   //第三大步骤：补充输出
	for(int i=1; i<=n; i++)
		if(frequency[i]==0)cout<<i<<endl;//如果没输出过，输出
	return 0;
}
```
祝大家能AC！

---

## 作者：公主殿下MIKU (赞：0)

很容易看出后调动的一定在先调动的前面，后进先出，这不就是个栈吗？把栈里的数据按顺序输出，注意要判重，每个元素只输出一次，最后将没有的调动的数据按顺序输出就行了，最后贴上AC代码：
```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<stack>
using namespace std;
int read() {
#define ge ch=getchar()
    int x=0;
    bool f=0;
    char ch=getchar();
    for(; ch<'0'||ch>'9'; ge) if(ch=='-') f=1;
    for(; ch<='9'&&ch>='0'; ge) x=(x<<3)+(x<<1)+ch-48;
    return f==0?x:-x;
}
int n,m;
bool b[100000|1][2];
int x;
stack<int>q;
int main()
{
    n=read();
    m=read();
    for(int i=1;i<=m;i++)
    q.push(x=read()),b[x][0]=1;
    while(!q.empty())
    {
    	if(!b[q.top()][1]) printf("%d\n",q.top()),b[q.top()][1]=1;
    	q.pop();
    }
    for(int i=1;i<=n;i++)
    if(!b[i][0]) 
    printf("%d\n",i);
    return 0;
}
```

---

