# [USACO3.4] 美国血统 American Heritage

## 题目描述

农夫约翰非常认真地对待他的奶牛们的血统。然而他不是一个真正优秀的记帐员。他把他的奶牛 们的家谱作成二叉树，并且把二叉树以更线性的“树的中序遍历”和“树的前序遍历”的符号加以记录而 不是用图形的方法。

你的任务是在被给予奶牛家谱的“树中序遍历”和“树前序遍历”的符号后，创建奶牛家谱的“树的 后序遍历”的符号。每一头奶牛的姓名被译为一个唯一的字母。（你可能已经知道你可以在知道树的两 种遍历以后可以经常地重建这棵树。）显然，这里的树不会有多于 $26$ 个的顶点。

这是在样例输入和样例输出中的树的图形表达方式：


```plain
　　　　　　　　 C
　　　　　　   /  \
　　　　　　  /　　\
　　　　　　 B　　  G
　　　　　　/ \　　/
　　　　   A   D  H
　　　　　　  / \
　　　　　　 E   F

```

附注：

- 树的中序遍历是按照左子树，根，右子树的顺序访问节点；
- 树的前序遍历是按照根，左子树，右子树的顺序访问节点；
- 树的后序遍历是按照左子树，右子树，根的顺序访问节点。


## 说明/提示

题目翻译来自NOCOW。

USACO Training Section 3.4


## 样例 #1

### 输入

```
ABEDFCHG
CBADEFGH 
```

### 输出

```
AEFDBHGC```

# 题解

## 作者：Diamiko (赞：442)

这里利用到一个最重要的知识点——二叉树遍历。

* **前序遍历：根左右**

* **中序遍历：左根右**

* **后序遍历：左右根**

前序遍历是先遍历根节点，再遍历根节点的左右子树。

那么，前序序列的第一个节点，一定是根节点。

找到根节点，再确定根节点在中序序列中的位置，就可以分出左右两棵子树。

这道题我们不需要建树，只要通过递归不断切割字符串就好了。

**字符串切割时应注意的问题**

那便是切割位置。STL的string类型自带切割方法substr，但搞不清参数就会导致WA甚至RE。

首先我们搞清楚substr方法的使用方法。

```cpp
string s;
s.substr(order,k);
```
参数传入一个order，一个k。

函数将会从下标为order的位置开始，连续截取k个字符。返回截取后的字符串。

order显然不能超出0~`s.size()-1`的范围。

但是，如果order+k超过了`s.size()-1`，函数会自动只截取到s的末尾。

如果不传入k，那么默认截取到末尾。

**这个函数是返回一个字符串，而不是对s进行改动。**

那么我们现在就开始寻找参数规律。

见下面的图（样例）

![](https://img41.pixhost.to/images/89/143577901_1.png)

看到前序序列的第一个字符是 C ，那么根节点就是 C ，找到中序中对应的位置，数下标，发现 C 在 5 处
**（注意字符串下标从0开始）**。

然后在先序序列中把C删掉。

![](https://img41.pixhost.to/images/89/143578227_2.png)

这是因为我们后面不会用到了。

（下面的数字是下标）

中序序列中C在5处，那么左右子树分别就是ABEDF(0~4)和HG(6~7)。

设在中序序列中根节点的位置是k，

很容易发现：

* 中序序列中左子树就是从0开始切割到k-1，也就是切割了k个字符；

* 中序序列中右子树就是从k+1开始，一直切割到最后。

然后找前序序列切割的规律。

中序序列中左子树是ABEDF，右子树是HG，对应在前序序列中就是BADEF(0~4)和GH(5~6)。

那么

* 前序序列中左子树是从0开始切割到k-1，也就是切割了k个字符；

* 前序序列中右子树就是从k开始，一直切割到最后。

另外仍需补充的几点，是关于查找和删除。

```cpp
s.find(c);
//在字符串s中查找第一个字符c的位置，返回下标，如果没有返回string::npos

s.erase(it);
//在字符串中删除指针it所指向的字符

s.begin();
//返回s的首字符的指针（迭代器）

```

那么我们现在就可以开始写代码了！

**（注意代码中的pre是前序，inor是中序）**

```cpp
#include<string>
#include<cstring>
#include<iostream>
#include<cstdio>
using namespace std;
string pre,inor;
void work(string pre,string inor)
{
    if(pre.empty())return;
    //如果序列空了，就没必要继续了
    char root=pre[0];
    //取到前序序列的首字母，即根节点
    int k=inor.find(root);
    //找到中序序列中根节点的位置
    pre.erase(pre.begin());
    //删去前序序列中的根节点
    string leftpre=pre.substr(0,k);
    //从0开始切割k个
    string rightpre=pre.substr(k);
    //从k开始切割到最后
    string leftinor=inor.substr(0,k);
    //从0开始切割k个
    string rightinor=inor.substr(k+1);
    //从k+1开始切割到最后
    work(leftpre,leftinor);
    work(rightpre,rightinor);
    printf("%c",root);
    //因为要输出后序序列，所以是左右根
    //先遍历左子树，再右子树，再根节点
}
int main()
{
    cin>>inor>>pre;
    work(pre,inor);
    putchar('\n');
    return 0;
}
```
结束！








---

## 作者：Bartholomew (赞：186)


    
    
```cpp
//一定要看清题目中为先中序，再是前序
#include <bits/stdc++.h>  //万能头文件
using namespace std;
string a,b;   //把中前遍历当做字符串输入
void houxu(int x,int y,int p,int q) {  //x~y为前序遍历 p~q为中序遍历
    if(x>y||p>q) return ;//规定边界条件
    else {
        int i=b.find(a[x]);   //利用根左右的特性来在中序队列中查找
    houxu(x+1,x+i-p,p,i-1);      //递归左子树
    houxu(x+i-p+1,y,i+1,q);    //递归右子树
    cout<<a[x];
}
}
int main() {
    cin>>b>>a;//反一下输入
    int l=a.length()-1;//因为是0开始，所以要减一
    houxu(0,l,0,l);//递归
    return 0;
}
```

---

## 作者：jzqjzq (赞：90)

来一发C++递归。

自然，根据中序遍历和前序遍历，在子树区间中找到根的方法是。。。

其实前序遍历本区间第一个就是该子树的根（这个应该都知道）

然后就在中序遍历此区间中找到该节点，节点左边就是左子树，右边就是右子树，这样就可以递归了

根据后序遍历性质，输出答案按照以下次序：

-找到节点后：

1.递归左子树

2.递归右子树

3.输出该节点

即为本树的后序遍历。

详见代码：

```cpp
#include<iostream>
#include<cmath>
#include<string>
#include<cstdio>
using namespace std;
string a,b;
void dfs(int l1,int l2,int l3,int l4){
    if(l1>l2||l3>l4)return;
    for(int i=l1;i<=l2;i++)if(a[i]==b[l3]){//找节点
        dfs(l1,i-1,l3+1,l3+i-l1);//递归左子树
        dfs(i+1,l2,l3+i-l1+1,l4);//递归右子树
        cout<<a[i];//输出该节点
    }
}
int main()
{
    cin>>a>>b;
    int l=a.size();
    dfs(0,l-1,0,l-1);//全树区间
    return 0;
}
这样就华丽丽地结束了，代码比建树短几乎一半，时间可能还快一点
```

---

## 作者：emiermao (赞：41)

最初，我用链表做，要死了

作为一名学c++不足一年的蒟蒻，我只能承认链表不适合此题

后来RE了几次，才发现结束条件不够

满纸荒唐言，一把辛酸泪

······

终于，经过调试n次后

AC了！！！！！！

讲完故事，上代码
```
#include <iostream>
#include <string>
using namespace std;
string middle, front;
void cut (int ms, int me, int fs, int fe);//先写main是个好（?）习惯
int main () {
	cin >> middle >> front;
	cut(0, middle.length() - 1, 0, front.length() - 1);
	return 0;
}
void cut (int ms, int me, int fs, int fe) {
	if (ms == me && fs == fe) {
		cout << middle[ms];
		return;
	}
	if (ms > me || fs > fe) {
		return;
	}
	int x;
	for (int i = ms; i <= me; i++) {
		if (middle[i] == front[fs]) {
			x = i;
		}
	}
	cut(ms, x - 1, fs + 1, fs + x - ms);
	cut(x + 1, me, fs + x - ms + 1, fs - ms + me);
	cout << front[fs];
	return;
}
```
讲一讲思路

把先序和中序切成多段，再切，用递归不停切，就AC了

因为先序遍历里的第一个字符，就是根

中序遍历中，根两边就是两棵子树

通过子树能求出下一个中序和下一个先序

把~~可怜的~~树~~碎尸万段~~层层剥开

就求出来了

（突然觉得很有heapsort和归并排序的遗风）



------------

P.S.刚看了别人的题解，跟this很像，自觉并未更好，但写都写了，试试

P.S.中的P.S.为CSP复赛攒RP，同时——如题，祝成功（1e10086 * ！）

---

## 作者：Alarm5854 (赞：21)

这道题难道就没有人用链表的吗？那我就来发(shui)一篇用链表做的题解。那么，这道题怎么确定二叉树的每个节点呢？方法如下，
就拿样例来说：
```
ABEDFCHG
CBADEFGH 
```
这棵二叉树的根节点为C，就将根节点插入链表，根节点在中序遍历的第n个，就递归向下n-1个，剩余的也递归，一次之后，这棵树变成这个样子：
```
[ABEDF]C[HG]
C[BADEF][GH]
```
最终，这棵树成这个样子：
```
[[A]B[[E]D[F]]]C[[H]G]
C[B[A][D[E][F]]][G[H]]
```
后序遍历即为：
```
AEFDBHGC
```
### 完整代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{//链表
	char val;
	node *l,*r;
};
node *root;
char prv[30],ord[30];
void init(int sp,int ep,int so,int eo,node *&p){//建立二叉树
	if(sp>ep||so>eo) return;
	int i,j;
	for(i=sp,j=so;i<=ep;++i,++j)
		if(ord[j]==prv[sp])
			break;
	p=new node;
	p->l=p->r=NULL;//注意每一次在申请空间之后，左右子节点都要变成空节点，否则会RE
	p->val=prv[sp];
	init(sp+1,i,so,j-1,p->l);//递归
	init(i+1,ep,j+1,eo,p->r);
}
void dfs(node *p){//后序遍历
	if(p==NULL) return;//如果该节点为空，直接返回
	dfs(p->l),dfs(p->r);
	putchar(p->val);
}
int main(){
	scanf("%s%s",ord,prv);
	init(0,strlen(prv)-1,0,strlen(ord)-1,root);
	dfs(root);
	return 0;
}
```

---

## 作者：25WA2019 (赞：15)

这是一道经典的二叉树题目，与P1030非常相似，不同点在于，一个是通过先序中序求后序，一个是通过中序后序求先序，还有一个不同点，就是P1030的题解满了，所以我只能写这一题的......

但是这一题也确实是比P1030简单，毕竟已经知道先序，就能把二叉数存储惹。

（送给蒟蒻们）

二叉树：一个节点最多有两个子树。

先序：根在前，左在中（左中跟在前，左在中，右在后），右在后（同左）。

中序：左在前（左中左在前，根在中。。。），根在中，右在后。

后序：左在前（...），右在中（。。。），根在后。

是不是看到了递归的影子，和回溯法一样，我们只需要打出一个模板，让后无线套，最后直接给主函数用，至于树，用结构体或三个变量就能储存。

程序呈上：
```
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstdlib>//原谅我这画蛇添足地猫病
using namespace std;
char tr[100001]={};//存储树要用字符型。
int a[201]={};
int n=0;//计数器。
string s1,s2;//输入的两个字符串。
void dfs(int l,int r,int l1,int r1){//****我没用****结构体，所以参数多了些。
     if (l==r) {tr[++n]=s1[l];return;}//熟悉的递归套路。
     for (int i=l;i<=r;i++)
       if (s1[i]==s2[l1]){
	       dfs(l,i-1,l1+1,l1+i-l);
		   dfs(i+1,r,l1+i-l+1,r1);
		   tr[++n]=s1[i];
		   break;
	   }
}
int main(){
    cin>>s1>>s2;
    for (int i=s1.size();i>=1;i--) s1[i]=s1[i-1],s2[i]=s2[i-1];
    dfs(1,s1.size(),1,s2.size());//直接套用后，无
    for (int i=1;i<=n;i++) cout<<tr[i];
    return 0;
}

```
有基础的选手除了想要发题解的还是别看这类题目的题解，毕竟对你们来说，如果能自己做出来，普及组肯定没问题，提高组也有望rp++。

---

## 作者：Warriors_Cat (赞：12)

## ~~这不是树的基础练习题吗~~

[安利一下自己的blog](https://www.luogu.org/blog/134342xcy252625/)

听说[Blog](https://www.luogu.org/blog/134342xcy252625/solution-p1827)食用更高效哦

刚刚学完树，见到了这道~~水~~题，怎么不忍心AC掉它呢？

~~LG上还有一道差不多的题[【P1030 求先序排列】](https://www.luogu.org/problemnew/show/P1030)可供大家练手~~

下面进入正文：

-------------------------~~潇洒的分割线~~-------------------------

树的前序遍历有一个特点：

#### 第一个字符即为它的根节点！

举个梨子~~其实是样例~~：

中序遍历为：ABEDFCHG，前序遍历为：CBADEFGH。

那么根节点就是C。

于是找到了中序遍历的左子树：ABEDF 和右子树：HG。

紧接着，前序遍历找到了左子树：BADEF 和右子树：GH。

于是，我们可以继续递归下去，直至字符串为空。

## Code：

```
#include<bits/stdc++.h>
using namesapce std;
string a, b;
void dfs(string x, string y){
	if(!(int)y.size()) return;//递归边界 
	int pos = x.find(y[0]);//在中序遍历中找到根节点 
	dfs(x.substr(0, pos), y.substr(1, pos));//递归1 
	dfs(x.substr(pos + 1), y.substr(pos + 1));//递归2 
	printf("%c", y[0]);//再输出根节点 
	return;//陋习qwq 
}
int main(){
	cin >> a >> b;
	dfs(a, b);
	system("pause");//日常防伪代码 
	return 0;
}
```

以上就是本蒟蒻的思路，如有不懂者，欢迎留言。

如果代码CE了，咳咳，我不说 -v-

谢谢各位读者的阅读以及管理员的审阅。

---

## 作者：Purslane (赞：12)

# 树
### 本题为一道树的遍历题。
### 他（出题人）给了你两个遍历结果，然后你就可以这么想：
- 先序遍历的第一个节点就是根
- 在中序遍历中找到这个节点
- 这个节点左边（中序遍历中）是这棵树的左子树，右边是右子树
- 把左子树、右子树的长度带回先序遍历
- 再用这种方法来分别搞左右子树
- 最后再输出根节点（因为它是后序遍历）
### 因为是遍历（非层次的），所以左右子树的位置都是左子树在前，右子树在后。
### 下面是代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string front,middle;
void tree(string front,string middle) { //遍历
	if(front.size()<1) return; //空子树
	int m=middle.find(front[0]); //找到中序遍历中的根节点
	tree(front.substr(1,m),middle.substr(0,m)); //左子树
	tree(front.substr(m+1,front.size()-m-1),middle.substr(m+1,front.size()-m-1)); //右子树
	cout<<front[0]; //输出根节点
}
int main() {
	cin>>front>>middle; //前序、中序遍历结果
	tree(front,middle); //遍历
	return 0;
}

```


## 本代码在main函数中有错，请自行动脑并改正

---

## 作者：梦里调音 (赞：10)

看dalao们的题解都这么短

我来发个长一点的（逃

思路：

	先找根（利用先序）
    
   	在分出根左边的部分和根右边的部分，分别循环（利用中序）
    
    
然后，特别注意要特判！

因为这棵树不一定是完全的（可能只有右部分或只有左分）

代码：

```
#include <bits/stdc++.h>
using namespace std;
string q,z,h;
int f(string mid,string front){
	if(mid.length()==1){//搜到底了
		cout<<mid;
		return 0;
	}
	int len=mid.length();
	string root,cq,cz;
	int p;
	root=front.substr(0,1);//根（注意要字符串形式)
	p=mid.find(root);//找根
	cz=mid.substr(0,p);
	cq=front.substr(1,p+1);
	if(cz!=""&&cq!="")f(cz,cq);//根左边的部分
	mid.erase(0,p+1);//把根和左边的部分删掉省事
	front.erase(0,p+1);
	cz=mid; 
	cq=front;
	if(cz!=""&&cq!="")f(cz,cq);//根右边的部分
	cout<<root;
	return 0; 
}
int main(){
	cin>>z;
	cin>>q;
	f(z,q);
}
```


---

## 作者：封禁用户 (赞：10)

看大家都喜欢用建树的方法，我觉得太麻烦，直接递归求解就行了

定义：s1先序，s2中序

[codep ]

var
 s1,s2:string;

[/codep ]

函数 ss 为求后序函数

[codep ]

```cpp
function ss(a,b:string):string;//参数a为先序,b为中序
 var
  i,l:longint;
  sa,sb:string;
 begin
  sa:='';sb:='';
  l:=length(a);
  i:=pos(a[1],b);//因为a[1]为根,而中序为左根右，找到根的位置后很容易找到左子树和右子树
  if i <> 1 then sa:=ss(copy(a,2,i-1),copy(b,1,i-1));//a[2]~a[i]为先序中的左子树 b[1]~b[i-1]为中序中的左子树
  if i <> l then sb:=ss(copy(a,i+1,l-i),copy(b,i+1,l-i));//a[i+1]~a[l]为先序中的右子树 b[i+1]~b[l] 为中序中的右子树
  exit(sa+sb+a[1]);//后序：左右根
 end;
```
[/codep ]
[codep ]

```cpp
begin
 readln(s2);
 readln(s1);
 writeln(ss(s1,s2));
end.
[/codep ]
```

---

## 作者：蒟___ (赞：6)

#### 此题与P1030求先序遍历类似，可以依照此题方法来写。

[传送门](https://www.luogu.com.cn/problem/P1030)在这里，写完这题可以去练练这个，学习效率<<=1。

# 正题：


### 1 · 分析：

以样例为例：

中：ABEDFCHG  
前：CBADEFGH

求得  
后： AEFDBHGC

总所周知，后序遍历为 **左 右 根** ，

对照例子也不难发现，

前序遍历 （**根 左 右**） 的第一个节点为根节点（标记为C)，

也就是后序中最后遍历的节点。

而中序遍历为 **左 根 右** ，因此中序遍历C前为左子树，C后为右子树

再按此方法类推遍历所有节点，直到没有节点可以遍历时结束。

很明显的**递归性质**，对吧？

### 2 · 实现：

递归实锤，现在要考虑的是如何维护这两种遍历。其实数组和字符串

都是的OK的.个人更偏向于字符串储存 ~~毕竟c++的stl是真的香~~

用substr解决子串问题比邻接表方便多啦！！！

别忘记后序遍历输出一定在递归后哦，
对比前序和后序，自己想想为什么叭~~~

要注意的一点是我们求后序遍历只用保存中序遍历中的字符，

因此在前序遍历中判断根节点后，可以放心大胆的删掉它。

### 3 · 对string小小的科普（dalao快撤！！！）：

贴心的针对string小萌新的讲解：

1.substr(x,y):取从下标为x的字符开始往后数y为的串，如果只有参数x则从x直到串末

2.erase(x):删除x字符（串）

3.find(x,y):从下标y的字符开始往后寻找x,如果只有一个参数x则从头到尾找。成功找到则返回该下标，否则-1

---
#### 下面为代码环节，具体思路已标明清楚，请放心食用。

不要问我为什么为什么用f 和 m表示前序和中序，

因为这样简便 ~~其实就是水不会英文表达~~

```cpp
#include<bits/stdc++.h>//万头妙
using namespace std;//命名空间妙

void def(string f,string m){//前序和中序
	if(f.empty()) return;//没有字符可分则退出
	
	char ch=f[0];//前序中开头为当前根节点
	int k=m.find(ch);//在中序中找到此节点并记录下标
    
	f.erase(f.begin());//删除前序的开头（因为之后不会再用到它
	
	def(f.substr(0,k),m.substr(0,k));//找到和中序左子树对应的前序
	def(f.substr(k),m.substr(k+1));//两者皆递归，先左后又（左右根）
    
	cout<<ch;//递归结束倒着输出
}

int main(){
	cin.tie(NULL);//cin小优化了解一下(●ˇ∀ˇ●)
	string m,f;
	
	cin>>m>>f;
	def(f,m);//个人习惯，先前后中
	
	return 0;
}
```
### That's all for this.

在各种写题解的训练中本蒟蒻变强啦！~~也变秃了~~

会尽其所能继续给大家带来优质的题解。若有不足欢迎提出鸭!!!

最后，管理大大？（眼神明示）

嗯，就酱紫，拜拜！

---

## 作者：远航之曲 (赞：5)

具体题解见注释

/\*    树中已知先序和中序求后序。

如先序为：abdc,中序为：bdac .

则程序可以求出后序为：dbca 。此种题型也为数据结构常考题型。

算法思想：先序遍历树的规则为中左右，则说明第一个元素必为树的根节点，比如上例

中的a就为根节点,由于中序遍历为：左中右，再根据根节点a，我们就可以知道，左子树包含

元素为：db，右子树包含元素：c，再把后序进行分解为db和c（根被消去了），然后递归的

进行左子树的求解（左子树的中序为：db，后序为：db），递归的进行右子树的求解（即右

子树的中序为：c，后序为：c）。如此递归到没有左右子树为止。

关于“已知先序和后序求中序”的思考：该问题不可解，因为对于先序和后序不能唯一的确定

中序，比如先序为 ab，后序为ba，我只能知道根节点为a，而并不能知道b是左子树还是右子树

，由此可见该问题不可解。当然也可以构造符合中序要求的所有序列。


\*/
```cpp
#include <cstdio>
int find(char c,char A[],int s,int e) /* 找出中序中根的位置。 */
{
int i;
for(i=s;i<=e;i++)
      if(A[i]==c) return i;
}
```
/\* 其中pre[]表示先序序，pre\_s为先序的起始位置，pre\_e为先序的终止位置。 \*/
/\* 其中in[]表示中序，in\_s为中序的起始位置，in\_e为中序的终止位置。 \*/

/\* pronum()求出pre[pre\_s～pre\_e]、in[in\_s～in\_e]构成的后序序列。 \*/

void pronum(char pre[],int pre\_s,int pre\_e,char in[],int in\_s,int in\_e)

```cpp
{
char c;
int k;
if(in_s>in_e)    return ;                 /* 非法子树，完成。 */
if(in_s==in_e){printf("%c",in[in_s]); /* 子树子仅为一个节点时直接输出并完成。 */
                  return ;
                  }
c=pre[pre_s];                           /* c储存根节点。 */
k=find(c,in,in_s,in_e);                 /* 在中序中找出根节点的位置。 */
pronum(pre,pre_s+1,pre_s+k-in_s,in,in_s,k-1); /* 递归求解分割的左子树。 */
pronum(pre,pre_s+k-in_s+1,pre_e,in,k+1,in_e); /* 递归求解分割的右子树。 */
printf("%c",c);                         /* 根节点输出。 */
}
main()
{
char pre[]="abdc";
char in[]="bdac";
printf("The result:");
pronum(pre,0,strlen(in)-1,in,0,strlen(pre)-1);
}
```

---

## 作者：liaohaoping (赞：4)

由于前序遍历是根在前，中序遍历是根在中间，我们可以利用这点先构造一颗树（时间够多，可以随便乱搞）

对于当前前序遍历中的某节点，暴力找出中序遍历中该节点的位置，由于中序遍历中是按左子树，根，右子树的顺序访问节点，所以只需要判断中序遍历中该节点的位置在x节点（上一个处理过的点）哪一边来判断是在其左子树还是右子树，记录信息后再构造以该节点为根（记录为x节点）的子树（前序遍历中后面的点）。

那么如何判断当前节点是否在以x节点为根的子树内呢？其实很简单，记录了l,r，表示当前子树在中序遍历中所占的范围，若超出范围，则不是该子树的节点。

最后后序遍历直接输出即可。

**代码**

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
inline int read()
{
    int x=0,w=0;char ch=getchar();
    while(ch<'0'||ch>'9')w|=ch=='-',ch=getchar();
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return w?-x:x;
}
struct node{int son[2],b;}tr[110];//tr[i].b表示i节点在中序遍历中位置
int a[110],b[110],len,n;char s[110];
void bt(int l,int r,int x)
{
    int m=++len;
    for(register int i=1;i<=n;++i)
    {
        if(b[i]==a[m])//找当前子树的根
        {
            tr[m].b=i;
            if(i<tr[x].b)tr[x].son[0]=m;
            if(i>tr[x].b)tr[x].son[1]=m;//判断该节点在左子树还是右子树
            if(i>l)bt(l,i-1,m);
            if(i<r)bt(i+1,r,m);//记得判断是否超出范围
            break;
        }
    }
}
void dfs(int x)
{
    if(tr[x].son[0]!=0)dfs(tr[x].son[0]);//遍历左子树
    if(tr[x].son[1]!=0)dfs(tr[x].son[1]);//遍历右子树
    printf("%c",b[tr[x].b]+64);//输出根
}//后序遍历（左子树→右子树→根）
int main()
{
    scanf("%s",s+1);n=strlen(s+1);
    for(register int i=1;i<=n;++i)b[i]=s[i]-64;
    scanf("%s",s+1);
    for(register int i=1;i<=n;++i)a[i]=s[i]-64;
    for(register int i=1;i<=n;++i)
    {
        if(b[i]==a[1])
        {
            tr[1].b=i;len=1;
            if(i>1)bt(1,i-1,1);
            if(i<n)bt(i+1,n,1);
            break;
        }
    }
    dfs(1);putchar('\n');
	return 0;
}
```

---

## 作者：Marsrayd (赞：3)

**_原题链接：_**  [P1827 【美国血统 American Heritage】](https://www.luogu.com.cn/problem/P1827)

**_题意简述：_**   输入一棵二叉树的先序遍历和中序遍历序列，输出后序遍历序列。

**_前置知识：_** 二叉树遍历

 **定义：** 所谓遍历($Traversal$)是指沿着某条搜索路线，依次对树中每个结点均做一次且仅做一次访问。访问结点所做的操作依赖于具体的应用问题。 遍历是二叉树上最重要的运算之一，是二叉树上进行其它运算之基础。

**实现：**

|  | 前序遍历($Preorder Traversal)$ | 中序遍历($Inorder Traversal$) | 后序遍历(Postorder Traversal) |
|:-----------: | :-----------: | :-----------: | :-----------: |
| $step$ 1. | 访问根结点 | 遍历左子树 | 遍历左子树 |
| $step$ 2.| 遍历左子树 | 访问根结点 | 遍历右子树 |
| $step$ 3.| 遍历右子树 | 遍历右子树 | 访问根结点 |


------------
**_思路_**：边建树（递归）边输出。后序序列输出时应该将输出放在两个递归函数后面，不难。不过还有些细节还是需要注意，比如传参的时候左右子树分别在先序和中序的位置需要注意。

$end$

---

## 作者：vegetabird (赞：3)

写一个直接用指针操作的。

做法很简单：根据先序遍历找到中序遍历中根的位置，然后处理左右子树，最后输出根，很简单的递归就能实现。

Code:
```cpp
#include<cstdio>
#include<cctype>
#include<cstring>
#include<utility>
#include<algorithm>
#include<vector>
#include<queue>
#include<cmath>
#include<set>
using namespace std;
char pre[30],mid[30];
void solve(char *prebeg,char *preend,char *midbeg,char *midend){   prebeg为先序遍历开始位置,preend为结束位置+1；midbeg, midend同理
    if(prebeg==preend||midbeg==midend)return;
    int i;
    for(i=0;midbeg+i!=midend;i++){
        if(*(midbeg+i)==*prebeg){
            break;
        }
    }
    solve(prebeg+1,prebeg+i+1,midbeg,midbeg+i);
    solve(prebeg+i+1,preend,midbeg+i+1,midend);
    putchar(*prebeg);
}
int main(){
    scanf("%s%s",mid,pre);
    solve(pre,pre+strlen(pre),mid,mid+strlen(mid));
    putchar('\n');
}
```

---

## 作者：Celebrate (赞：3)

这一道题首先定义一个f数组记录中序遍历字母所在的位置，然

后从前序遍历的第一个开始在中序遍历里面找，搜索左边的和

右边的，因为需要找后序遍历，所以找完左右两边以后记录当前的数

首先，看一下44分的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
char a[2100],b[2100],st[2100];
int alen,blen;
int f[21000];
int len,k;//k记录前序遍历找到第几个 
void dfs(int x,int y)
{	
    if(x>y) return;	
    int t=f[a[k+1]];//记录位置，因为k一开始会为0，所以要+1 
    if(x<y)//如果可以这样找 
    {
        k++;dfs(x,t-1);//搜索左右两边 
        k++;dfs(t+1,y);
    }
 	len++;st[len]=b[t];//找完后记录 
}
int main()
{
    scanf("%s",b+1);blen=strlen(b+1);//我比较喜欢这样 
    scanf("%s",a+1);alen=strlen(a+1);
    for(int i=1;i<=alen;i++) f[b[i]]=i;//记录位置 
    dfs(1,blen);//后序遍历范围1-blen 
    for(int i=1;i<=len;i++) printf("%c",st[i]);
    printf("\n");
    return 0;
}
```

看上去感觉没有问题，但是会有一个问题：

比如说在一些根节点没有右子树但是没有左子树，k就会多加一次，所以我们也要给前序遍历定义一个范围

虽然比较麻烦，但是可以多拿几十分（100）

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
char a[110],b[110];int alen,blen;
char ss[110];int L;
int f[110];
void dfs(int la,int ra,int lb,int rb)
{
    if(la>ra) return ;//如果前序遍历头比尾还要多，就肯定不可以
	//先查找左边
	//前序遍历头到下一个
	//尾就他头+左子树的个数，记得-lb
	//还有一个问题，就是为什么尾不用加1
	//这是因为不能包括自己，所以需要-1，-1和+1抵消了
	//中序遍历就不多说了 
    dfs(la+1,la+f[a[la]]-lb,lb,f[a[la]]-1);
    //查找右边 
    dfs(la+f[a[la]]-lb+1,ra,f[a[la]]+1,rb);
    ss[++L]=a[la];
}
int main()
{
    scanf("%s",b+1);blen=strlen(b+1);
    scanf("%s",a+1);alen=strlen(a+1);
    for(int i=1;i<=alen;i++) f[b[i]]=i;
    L=0;dfs(1,alen,1,blen);//左边的范围和右边的范围 
    for(int i=1;i<=alen;i++) printf("%c",ss[i]);
    return 0;
}
```

---

## 作者：罗旅洲 (赞：2)


```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<cstdlib>
using namespace std;
char s1[1010],s2[1010];    //两个字符串
int num[2500];            //表示每个字符在前序中位置，这样可以更快找到一串数里的根
void dfs(int st,int end){        //start表示字符串的起始，end是最后的位置
    if(st==end){
        printf("%c",s1[st]);
        return;
    }
    int minn=1e7,flag;
    for(int i=st;i<=end;i++)        //在这一段中间的根
        if(num[s1[i]-'0']<minn){
            minn=num[s1[i]-'0'];
            flag=i;
        }
if(flag-1>=st)    dfs(st,flag-1);        //由中序遍历，左边的字母在flag指的位置的左边
if(flag+1<=end)dfs(flag+1,end);        //同理右边的字符在flag右边
    printf("%c",s1[flag]);            //最后返回输出中间
}
int main(){
#ifndef ONLINE_JUDGE
    freopen("input.in","r",stdin);
    freopen("output.out","w",stdout);
#endif
    int i,j,k,m,n,t;
    scanf("%s%s",s1,s2);
    n=strlen(s1);
    for(i=0;i<n;i++)
        num[s2[i]-'0']=i;    //转ASCII码存权值
    dfs(0,n-1);        //搜的是中序遍历s1    
    return 0;
}

```

---

