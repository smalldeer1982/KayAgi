# ファーストアクセプタンス

## 题目描述

# 问题描述

你参加了一个编程比赛，一共有 $N$ 题。你解决第 $i$ 个问题需要 $A_{i}$ 分钟，而别人则需要 $B_{i}$ 分钟。现在你需要安排你的做题顺序，使得拿到题目的一血数量最多(即第一个完成)。注意，当你开始做一道题，你就只能做这道题直到解决。最后只要给出最多一血数即可。

## 说明/提示

-  $1 \le N \le 1000$ 

-  $1 \le A_{i},B_{i} \le 10^{6}(1 \le i \le N)$ 

感谢@常暗踏阴 提供的翻译

# 题解

## 作者：btng_smith666 (赞：15)

# 前言 ：

[题面传送门](https://www.luogu.com.cn/problem/AT29)

[博客食用效果更佳](https://www.luogu.com.cn/blog/X-SSS-Tng/solution-at29)

> 一道数据结构的好题！

# 思路 ：

这道题我是用数据结构做的，感觉难度还阔以。

代码中主要用了三个有意思的东西：$pair$（类）、$vector$（向量）和 $priority~queue$（优先队列，这里由于排版原因就不打那个下划线了）

先简单介绍一下向量 **vector** ：

> 向量（Vector）是一个封装了动态大小数组的顺序容器（Sequence Container）。跟任意其它类型容器一样，它能够存放各种类型的对象。可以简单的认为，向量是一个能够存放任意类型的动态数组。（摘自百度）

一些函数（本篇代码里会用到的）：

- $push~back$ 在数组的最后添加一个数据

- $begin$ 得到数组头的指针

- $end$ 得到数组的最后一个单元 +1 的指针

然后是类 **pair** ：

> pair 是一种模板类型，其中包含两个数据值，两个数据的类型可以不同。

一些函数 ：

- $make~pair$ 生成新的 pair 类
- $first$ 访问类里面的第一个数据值
- $second$ 访问类里面的第二个数据值

最后是优先队列 **priority_queue** ：

> STL 中的 priority_queue（优先队列）是一个封装好的堆结构。

一些函数 ：

- top 访问队头元素
- pop 弹出队头元素
- push 插入元素到队尾并排序
- size 队列中的元素个数

本题主要的操作就是把题中的 $A$ 和 $B$ 数组用 $pair$ 存到 $vector$ 里，排一下序，再将 $pair$ 里第二个数据值累加入临时变量 $tmp$ 和优先队列里，然后判断 $tmp$ 和第一个数据值的大小关系，再从 $tmp$ 里减去队首元素，并弹出即可，最后队列的长度就是答案

# 代码 ：

```cpp
#include<bits/stdc++.h>//by btng_smith666 juruo
#include<queue>//priority_queue
#include<vector>//vector 
#include<iostream>//pair 
using namespace std;
int n,b,a,tmp;
string I_AK_IOI="oh,i is a english men";//防伪标识 
vector<pair<int,int> >v;//定义一个 vector ，夹着一个 pair ，注意这里有一个小小的空格 
priority_queue<int> p;//定义一个优先队列 
int main()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++)//注意顺序是 0 到 n-1 
	{
		scanf("%d%d",&a,&b);
		v.push_back(make_pair(b,a));//在 v 后面加一个 pair ，将 b 和 a 存入 pair 
	}
	sort(v.begin(),v.end());//对 vector 排序 
	for(int i=0;i<n;i++)
	{
		tmp+=v[i].second;//把第二个元素加到 tmp 里 
		p.push(v[i].second);//加入 
		if(tmp>v[i].first)//如果 tmp 比第一个数据值大 
		{
			tmp-=p.top();//减去队首元素 
			p.pop();//弹出 
		}
	}
	printf("%d\n",p.size());
	/*
	AT 千万条，换行第一条 
	输出不规范，全 WA 两行泪 
	*/
	return 0;
}
```

# 后记 ：

提供几组样例 ：

`#1` $in$ ：
```
10
1 10
2 9
3 8
4 7
5 6
6 5
7 4
8 3
9 2
10 1
```
`#1` $out$ ：
```
4
```
`#2` $in$ ：
```
3
3 5
5 9
10 20
```
`#2` $out$ ：
```
3
```

本篇题解到这里就结束了（这珂能是我写的最长的一篇题解），大家留下一个赞吧 qwq !

---

## 作者：千城_Dhmc (赞：6)

## 本题思路：

这一题就是**拿我的做得快的题跟别人做的慢得比**，总体来看就是两个排序，一个从小到大，一个从大到小，然后再比较；这就用到了贪心和指针的思想，竟可能的让自己得到的多。

### 废话不多说上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int cmp(int a,int b){
	return b<a;
}
int main(){
	int n;
	cin>>n;
	int cnt=0;
	int a[10010],b[10010];
	for(int i=0;i<n;i++){
		cin>>a[i]>>b[i];
	}
	sort(b,b+n,cmp);
	sort(a,a+n);
	for(int i=0;i<n;i++){
		if(a[i]<=b[i]){
			cnt++;
		}
	}
	cout<<cnt<<endl;
	return 0;
}
```
### 另外一种写法就是用队列来写：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,b,a,tmp;
vector<pair<int,int> >v;
priority_queue<int> p;
int main(){
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>a>>b;
		v.push_back(make_pair(b,a));
	}
	sort(v.begin(),v.end()); 
	for(int i=0;i<n;i++){
		tmp+=v[i].second;
		p.push(v[i].second); 
		if(tmp>v[i].first){
			tmp-=p.top(); 
			p.pop();
		}
	}
	cout<<p.size()<<endl;
	return 0;
}
```

不喜勿喷。

---

## 作者：eEfiuys (赞：2)

题目：[AT29](https://www.luogu.com.cn/problem/AT29)

首先以 $b_i$ 为第一关键字，$a_i$ 为第二关键字**从小到大**排序，`pair` 就能搞定。

接下来，从小到大，记录一下自己用的总时间，如果大于 $b_i$，就去掉一个 $a_i$ **最大**的，用 `priority_queue` 就行。

最后剩下的个数即为答案。

------------

## Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
pair<int,int>p[1005];
#define b first
#define a second
priority_queue<int>q;
int tim;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		int aa,bb;
		cin>>aa>>bb;
		p[i]=make_pair(bb,aa);
	}
	sort(p+1,p+n+1);
	for(int i=1;i<=n;i++){
		tim+=p[i].a;
		q.push(p[i].a);
		if(tim>p[i].b){
			tim-=q.top();
			q.pop();
		}
	}
	cout<<q.size()<<endl;
	return 0;
}
```

---

## 作者：Buried_Dream (赞：2)

## 　题意：

给定一个 $n$，接下来 $n$ 行，每行 $2$ 个数，要求找到能优先做完的题目数量，无做题顺序，更准确的来说是自己安排做题顺序。 

## 思路:

这里要用到 `STL` 库中的 `sort` 函数。

排序默认为升序排列。

因为要使能优先做完的题尽量多，也就是让我们从用时最少的题开始做，然后对手从用时最多的题开始做，也就是对一个数组从小到大排序，另一个数组从大到小排序。
在sort的最后加上排序规则：

最后，请大家注意：AT的题必须换行!

## AC code:
为了防抄袭仅贴出主要代码:

```
	int n = read();
	for(int i = 1; i <= n; i++) {
		cin >> x_1[i] >> x_2[i];
	}
	sort(x_1 + 1, x_1 + n + 1);
	sort(x_2 + 1, x_2 + n + 1, cmp);
	for(int i = 1; i <= n; i++) {
		if(x_1[i] <= x_2[i]) {
			ans++;			
		}
	}
```


---

## 作者：jijidawang (赞：1)

- [务必去博客观看](https://www.luogu.com.cn/blog/writeSTL/solution-at29)

## 题目简述：

> 当你做第 $i$ 道题时，你前面做的题目花的总时间加上第 $i$ 题你需要花的时间之和小于别人花的时间时，你就拿到了“一血”。

## 算法分析

举个例子：

$\begin{cases}a:1 3 9\\b:3 4 4\end{cases}$

- 当切 `T1` 时，$a_1\le b_1$,可以；

- 当切 `T1,T2` 时，$a_1+a_2\le b_2$,可以；

- 当切 `T1,T2,T3` 时，$a_1+a_2+a_3\not\le b_3$，不可以...以此类推。

这就可以使用 **dp** 了：

设 $dp_{i,j}$ 为到第 $i$ 个题目时拿了 $j$ 个一血最早时间，状态转移方程为：
$$dp_{i,j+1}=\min\{dp_{i-1,j+1},dp_{i-1,j}+a_i\}$$

我们可以滚动 dp 数组，转移方程就变成了：

$$dp_{j+1}=\min\{dp_{j+1},dp_j+a_i\}$$

当然还需要前提条件 $j+a_i\le b_i$，要不然比不过别人。

这里还有一个**贪心**的思想

我们希望一血越多越好，所以每个 $b_i$ 越大越好，将 $b_i$ 递减排列即可。

这样代码就很好写了QAQ

---

## 作者：奆奆的蒟蒻 (赞：0)

Perl题解  

[题面传送门](https://www.luogu.com.cn/problem/AT29)  
[配合博客食用更佳！](https://www.luogu.com.cn/blog/Iamveryscan/solution-at29)  
```Perl
<>;
@_=sort({$a-$b}@_,/ /*$`),$'<($s+=$`)&&($s-=pop@_)for`sort -nk2`;print@_.$/
```
### 给一下解释：
1）Perl尖括号运算符中间没有任何东西时，它可以读取命令行上所有文件的内容或读取标准输出。所以它现在代指标准输出。  
2）这里的sort对列表进行排序，并返回排序后的列表。还使用了2次，可见 Perl中sort的重要性。  
## 拓展一下：关于Perl中的sort   
### 除了对列表排序，sort还可以
- 以ASCII顺序(非字典序)进行排序  

- 以字典序进行排序
### 最后，请大家注意：AT的题必须换行！！！！！
#### 不喜勿喷，不建议复制粘贴，有建议评论或者私信都可以。

---

