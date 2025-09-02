# Portal2

## 题目背景

某地`ENLIGHTENED`的`XM`研究所正在研究`Portal`的处理法则，想要揭示`XM能量`的来源以及应用`XM能量`。`ENLIGHTENED`的首席科学家`Jacks`发现其能量的运算法则以及运算方法，但是方法十分复杂，仅靠人手工计算是很难算出答案的，所以它需要你协助他完成计算。

## 题目描述

`Portal`计算`XM能量`是通过个$2$个栈（$0$号栈，$1$号栈）实现的，它把对`XM`能量的操作如下

$PUSH$ $X$ $NUM$

把$NUM$加入到X号栈的栈顶。 

$POP$ $X$

把$X$号栈的栈顶元素**删除**。

$ADD$ $X$

**取出**$0$号栈和$1$号栈的元素各一个，并且把它的和放入$X$号栈。

$SUB$ $X$

**取出**$0$号栈和$1$号栈的元素各一个，并且把它的差的绝对值放入$X$号栈。
 
$DEL$ $X$

**清空**$X$号栈中所有元素不管栈是否为空。 

$MOVE$ $X$ $Y$ 

循环操直到$Y$号栈为空，把$Y$号栈的栈顶元素加入到$X$号栈，删除$Y$号栈的栈顶元素。 

**数据保证X和Y不相同**

$SWAP$

将两个栈的所有元素调换。

$END$

代表命令结束，并且分两行分别输出0号栈和1号栈由栈顶到栈底的元素的值，若栈内无元素，输出`NONE`。数据保证指令以`END`结束且仅有一个`END`，并且也需要输出`SUCCESS`。

~~$AKNOI$~~

~~等为无效操作，**无效操作后不接数字**。~~

**更正不会有类似无效操作**

对于每一行指令，若当前指令成功执行输出`SUCCESS`，若**取出**或**删除**元素时栈内为空或者没有对应指令输出`UNSUCCESS`并且不执行该行指令。

## 说明/提示

对于$20\%$的数据 数据保证不会出现`MOVE/SWAP`操作，$命令总数 \leq 100$

对于$40\%$的数据 $命令总数 \leq 1000$

对于$60\%$的数据 数据保证`MOVE/SWAP`的操作次数不会超过$10000$次，$命令总数 \leq 10^5$

对于$100\%$的数据 $0 \leq X,Y \leq 1,命令总数 \leq 10^6$ 

**数据保证无论任何情况，栈中元素的值$X$满足$0 \leq x \leq 2^{63}-1​$**

[题目创意来源OIERBBS](https://www.oierbbs.cn)

## 样例 #1

### 输入

```
PUSH 0 10
PUSH 0 20
PUSH 0 30
PUSH 0 40
PUSH 1 50
PUSH 1 60
ADD 0
ADD 0
ADD 0
END```

### 输出

```
SUCCESS
SUCCESS
SUCCESS
SUCCESS
SUCCESS
SUCCESS
SUCCESS
SUCCESS
UNSUCCESS
SUCCESS
150 30 20 10
NONE```

## 样例 #2

### 输入

```
PUSH 0 10
PUSH 0 20
PUSH 0 30
PUSH 0 40
PUSH 1 50
PUSH 1 60
MOVE 0 1
END```

### 输出

```
SUCCESS
SUCCESS
SUCCESS
SUCCESS
SUCCESS
SUCCESS
SUCCESS
SUCCESS
50 60 40 30 20 10
NONE```

# 题解

## 作者：7KByte (赞：9)

$Updata$发现打错了几个符号和字……

上一篇唯一的题解涉嫌抄袭被$Delete$了（考古  
那我来补一篇  

-----------------
先扯一句，题面说什么无效操作，事实上没有（弄的我多打了100行……  


从题面透露出的信息我们可以感受到这题是个大型模拟  


看到目前的提交大多数是栈和链表  
然而本蒟蒻并不会，所以就打了一个**双端队列（模拟栈）+启发式合并**  


除了$MOVE$操作，其他操作还是比较简单吧……按照题意打就可以了  

对于$MOVE$操作我们进行启发式合并，因为最多有$10^6$次操作，如果按照题意暴力合并复杂度能够达到$O(N^2)$，而启发式合并能够保证复杂度为$O(N log_2 N)$   


我们开两个双端队列模拟栈，最初队首为栈**底**，队尾为栈**顶**，前面四个操作直接在队尾执行，每次复杂度$O(1)$  

对于第5个操作$DEL$，直接暴力讲队列清空，每次复杂度$O(n)$，均摊复杂度$O(1)$  

对于第7个操作$SWAP$，我们记录$f_0$和$f_1$，表示输入的$x$号栈对应的是第$f_x$号队列，操作时直接讲$f_0$和$f_1$ $SWAP$即可，注意，$f_0 f_1$一定要分别置初值${0,1}$，每次复杂度$O(1)$  

对于毒瘤的第6个操作$MOVE$，我们考虑两种情况（注意，题目要求将$Y$栈移动到$X$栈）：  


--------------
- 当$Y$栈小于$X$栈时，直接暴力将$Y$栈里的元素移到$X$栈里  


------------
- 当$Y$栈大于$X$栈  
 我们借助$Tag_0\text{和}Tag_1$表示这个队列是否反转，即队头变队尾，队尾变队头，初始化都为零，表示没有反转  
 我们将$X$栈里的元素按照出栈顺序一一移动到$Y$栈  
 然后再将$Tag_Y\ XOR\ \  1$，因为两次反转则等于没有反转   
 最后$SWAP(f_x,f_y)$    
 为什么这样是对的，因为将$Y$栈移动到$X$栈正好是将$X$栈移动到$Y$栈的反转序列，自己画个图就知道了  
 
 
--------------
每次复杂度$O(n)$，均摊复杂度$O(log_2N)$  
 
 
 
 
 
 --------------------
 
$Code:$  $O(N log_2 N)$


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
deque<ll>q[2];
int f[2]={0,1};
int tag[2]={0,0};
int main()
{
    char k[10];int x,y;ll X,Y;
    while(true){
        scanf("%s",k);
        if(k[0]=='P'&&k[1]=='O'){
            scanf("%d",&x);
            if(!q[f[x]].size()){
                puts("UNSUCCESS");
            }
            else{
                puts("SUCCESS");
                if(tag[f[x]]){
                    q[f[x]].pop_front();
                }
                else q[f[x]].pop_back();
            }
        }
        else if(k[0]=='P'&&k[1]=='U'){
            scanf("%d%lld",&x,&Y);
            puts("SUCCESS");
            if(tag[f[x]]){
                q[f[x]].push_front(Y);
            }
            else q[f[x]].push_back(Y);
        }
        else if(k[0]=='A'&&k[1]=='D'){
            scanf("%d",&x);
            if(!q[0].size()||!q[1].size()){
                puts("UNSUCCESS");
            }
            else{
                puts("SUCCESS");
                ll a,b;
                if(tag[0])a=q[0].front(),q[0].pop_front();
                else a=q[0].back(),q[0].pop_back();
                if(tag[1])b=q[1].front(),q[1].pop_front();
                else b=q[1].back(),q[1].pop_back();
                if(tag[f[x]]){
                    q[f[x]].push_front(a+b);
                }
                else{
                    q[f[x]].push_back(a+b);
                }
            }
        }
        else if(k[0]=='S'&&k[1]=='U'){
            scanf("%d",&x);
            if(!q[0].size()||!q[1].size()){
                puts("UNSUCCESS");
            }
            else{
                puts("SUCCESS");
                ll a,b;
                if(tag[0])a=q[0].front(),q[0].pop_front();
                else a=q[0].back(),q[0].pop_back();
                if(tag[1])b=q[1].front(),q[1].pop_front();
                else b=q[1].back(),q[1].pop_back();
                if(tag[f[x]]){
                    q[f[x]].push_front(abs(a-b));
                }
                else{
                    q[f[x]].push_back(abs(a-b));
                }
            }
        }
        else if(k[0]=='D'&&k[1]=='E'){
            scanf("%d",&x);
            puts("SUCCESS");
            tag[f[x]]=0;
            while(q[f[x]].size())q[f[x]].pop_back();
        }
        else if(k[0]=='M'&&k[1]=='O'){
            scanf("%d%d",&x,&y);
            puts("SUCCESS");
            if(q[f[x]].size()<q[f[y]].size()){
                while(q[f[x]].size()){
                    ll a;
                    if(tag[f[x]])a=q[f[x]].front(),q[f[x]].pop_front();
                    else a=q[f[x]].back(),q[f[x]].pop_back();
                    if(tag[f[y]])q[f[y]].push_front(a);
                    else q[f[y]].push_back(a);
                }
                tag[f[y]]^=1;
                swap(f[0],f[1]);
            }
            else{
                while(q[f[y]].size()){
                    ll a;
                    if(tag[f[y]])a=q[f[y]].front(),q[f[y]].pop_front();
                    else a=q[f[y]].back(),q[f[y]].pop_back();
                    if(tag[f[x]])q[f[x]].push_front(a);
                    else q[f[x]].push_back(a);
                }
            }
        }
        else if(k[0]=='S'&&k[1]=='W'){
            swap(f[0],f[1]);puts("SUCCESS");
        }
        else if(k[0]=='E'&&k[1]=='N'){
        	puts("SUCCESS");
            if(!q[f[0]].size())puts("NONE");
            else {
                if(tag[f[0]]){
                    while(q[f[0]].size())
                      printf("%lld ",q[f[0]].front()),q[f[0]].pop_front();
                }
                else{
                    while(q[f[0]].size())
                      printf("%lld ",q[f[0]].back()),q[f[0]].pop_back();
                }
                puts("");
            }
            if(!q[f[1]].size())puts("NONE");
            else {
                if(tag[f[1]]){
                    while(q[f[1]].size())
                      printf("%lld ",q[f[1]].front()),q[f[1]].pop_front();
                }
                else{
                    while(q[f[1]].size())
                      printf("%lld ",q[f[1]].back()),q[f[1]].pop_back();
                }
                puts("");
            }
            break;
        }
    }
    return 0;
}
```


---

## 作者：NewSjf (赞：4)

大家好,我非常喜欢非旋Treap,它太可爱了,所以我要来一篇非旋Treap的题解  
-
由于我太菜了  
楼下那个双端队列（模拟栈）+启发式合并的做法  
我当时做题并没有想到,拿了60分暴力就跑了   
偶然又翻出来,决定再做一波  
我的确想到过双端队列    
我思考片刻以为可以O(1)合并  
![](https://s2.ax1x.com/2019/09/01/n9uYtI.png)  
关于MOVE操作,就是把一个链表翻转,在和另一个黏在一起  
于是我想到了一个惊为天人的办法  
![我真他娘是个人才](https://s2.ax1x.com/2019/09/01/n9KpEd.png)  
我还为std::list没有提供这个接口而感到烦恼   
遂指针满天飞手写deque  
啊！平面的指针交错生长,织成 **忧伤的网**  
后来我才发现不对啊,虽然接倒是能接上去,但是**并没有卵用**啊  
两个指针名字又不一样,到头来还是要O(N)翻转一遍指针  
遂放弃  
然后我仔细思考了下,如上图的栈其实就是一个封装的数组,或者**区间**  
现在我要对这个区间进行一些操作,包括      
   插入/删除一个元素   
   清空一个区间  
   合并两个区间   
并且每次操作均摊下来要在**logN**的时间内完成  
除了那个我看不懂的启发式合并,那么还有一种暴力美学  
平衡树！  
非旋Treap！   
虽然stack的插入删除是O(1),但平衡树是O(logN)  
但是对于MOVE和DEL,平衡树可以跟别O(logN)和O(1)完成   
起码复杂度对了.  
整个算法的复杂度不高于O(NlogN)~~常数超大~~完全可以过这道题   
每个栈都用begin和end来记录位置,就和数组模拟栈一个样  
PUSH POP ADD SUB写法都类比数组   
MOVE操作,从区间上来看,就是把y所在的区间翻转,然后再和x所在区间合并  
关键词：区间反转,文艺平衡树,logN   
SWAP:交换根和begin/end  
DEL操作：~~讲道理直接把root换了就可以了谁闲的没事删树~~    
差不多就这样吧   
最后献上我又臭又长还跑得巨慢的代码  
具体做法都写在注释里面了.  
```cpp
//P4940
#include<iostream>
#include<cstdlib>
#include<ctime>
#define MAXN 2000001
#define ll long long int
struct node{ll val;int key,rev,size,l,r;}t[MAXN];                              
int root[2],tot; //每一个root对应一颗树,对应一个栈的区间 
struct stack{int begin,end,empty;}stk[2];//两个栈的范围,begin==end则栈为空,和数组模拟栈的写法很类似 
using namespace std;
/**************以下非旋Treap常规操作********************/ 
int New(ll val){t[++tot]=(node){val,rand(),0,1,0,0};return tot;}          
void update(int now){t[now].size=t[t[now].l].size+t[t[now].r].size+1;}
void pushdown(int now) //区间翻转标记下传送 
{
	if(!t[now].rev)return;
	t[t[now].l].rev^=1;
	t[t[now].r].rev^=1;
	swap(t[now].l,t[now].r);
	t[now].rev=0;
}
void split(int now,int&x,int&y,int rank)
{
	if(!now){x=y=0;return;}pushdown(now);
	if(t[t[now].l].size>=rank)y=now,split(t[now].l,x,t[y].l,rank);
	else x=now,split(t[now].r,t[x].r,y,rank-t[t[now].l].size-1);
	update(now);
}
void merge(int&now,int x,int y)
{
	if(!x||!y){now=x+y;return;}pushdown(x);pushdown(y);
	if(t[x].val<t[y].val)now=x,merge(t[now].r,t[x].r,y);
	else now=y,merge(t[now].l,x,t[y].l);
	update(now);
}
void insert(int root,int pos,ll val)
{
	int x=0,y=0;
	split(root,x,y,pos);
	merge(x,x,New(val));
	merge(root,x,y);
}
void erase(int root,int l_pos,int r_pos=-1)     //这里是为了既能删除单个元素 
{                                               // 也能删除整个区间 
	if(r_pos==-1)erase(root,l_pos,l_pos);       //应该算是代码复用么 
	else
	{
		int x=0,y=0,z=0;
		split(root,x,y,r_pos);
		split(x,x,z,l_pos-1);
		merge(root,x,y);
	}
}
void reverse(int root,int l_pos,int r_pos)   //翻转区间 
{
	int x=0,y=0,z=0;
	split(root,x,y,r_pos);
	split(x,x,z,l_pos-1);
	t[z].rev^=1;
	merge(x,x,z);
	merge(root,x,y);
}
ll&at(int root,int pos)  //访问某个元素,类似数组下标访问 
{
	int x=0,y=0,z=0;
	split(root,x,y,pos);
	split(x,x,z,pos-1);
	ll&ans=t[z].val;
	merge(x,x,z);
	merge(root,x,y);
	return ans;
}
void print(int now)  //遍历now为根的Treap 
{
	pushdown(now); 
	if(t[now].l)print(t[now].l);
	cout<<t[now].val<<" ";
	if(t[now].r)print(t[now].r); 
}
#ifdef _DEBUG
void print_debug(int root)
{
	cout<<endl;
	print(root);
	cout<<endl;	
}
void debug()
{
	cout<<"stk0:";
	print_debug(root[0]);
	cout<<"stk1:";
	print_debug(root[1]);
}
#endif
void print(int root,int l_pos,int r_pos) //遍历某个子区间 
{
	int x=0,y=0,z=0;
	split(root,x,y,r_pos);
	split(x,x,z,l_pos-1);
	print(z);
	merge(x,x,z);
	merge(root,x,y);
}
/**********以上为非旋Treap常规操作***************/
void init()   
{
	root[0]=New(-1); //为两个栈确定一个根节点 
	root[1]=New(-1);
	stk[0].begin=stk[0].end=1;
	stk[1].begin=stk[1].end=1;
}
/**********以下为stack的操作*******************/ 
void push(int x,ll num)
{
	insert(root[x],stk[x].end,num);  //末尾插入一个元素 
	stk[x].end++;                //更新下标 
}
bool empty(int x)
{
	return stk[x].begin==stk[x].end;  
}
void pop(int x)
{
	erase(root[x],stk[x].end);  //删掉末尾元素 
	stk[x].end--;
}
void erase(int x)
{
	root[x]=New(-1);           //直接扔掉不管了,反正空间够用随便折腾,O(1)清空hhh 
	stk[x].end=stk[x].begin;   
}
void swap()
{
	swap(root[0],root[1]);     //根和stack一一对应 
	swap(stk[0],stk[1]);       //交换下标 
}
void move(int x,int y)        //所有操作用最重要的 
{                             //也是最骚气的 
	int x1=0,x2=0,y1=0,y2=0;
	reverse(root[y],2,stk[y].end);  //确定root的时候插入了-1,这里先把两个-1分出来 
	split(root[x],x1,x2,1);
	split(root[y],y1,y2,1);          //把y所有元素push到x,就相当于翻转y所在的区间,在合并x,y所在的区间 
	merge(x2,x2,y2);
	merge(root[x],x1,x2);           //再把-1加进去,根为x原来的根 
	stk[x].end+=stk[y].end-1;       //更新下标范围 
	stk[y].end=stk[y].begin;
}
int main()
{
	init();
	while(1)
	{
		int x,y;
		ll num;
		string str;
		cin>>str;
		if(str=="PUSH")
		{
			printf("SUCCESS\n");
			scanf("%d%lld",&x,&num);
			push(x,num);
		}
		if(str=="POP")
		{
			scanf("%d",&x);
			if(empty(x))printf("UNSUCCESS\n");
			else
			{
				pop(x);
				printf("SUCCESS\n");
			}
		}
		if(str=="ADD")
		{
			scanf("%d",&x);
			if(empty(0)||empty(1))printf("UNSUCCESS\n");
			else
			{
				printf("SUCCESS\n");
				ll temp=at(root[1],stk[1].end)+at(root[0],stk[0].end);
				pop(0);
				pop(1);
				push(x,temp);
			}
		}
		if(str=="SUB")
		{
			scanf("%d",&x);
			if(empty(0)||empty(1))printf("UNSUCCESS\n");
			else
			{
				printf("SUCCESS\n");
				ll temp=abs(at(root[1],stk[1].end)-at(root[0],stk[0].end));
				pop(0);
				pop(1);
				push(x,temp);
			}
		}
		if(str=="DEL")
		{
			printf("SUCCESS\n");
			scanf("%d",&x);
			erase(x);
		}
		if(str=="SWAP")
		{
			printf("SUCCESS\n");
			swap();
		} 
		if(str=="MOVE")
		{
			printf("SUCCESS\n");
			scanf("%d%d",&x,&y);
			move(x,y);
		}
		if(str=="END")
		{
			printf("SUCCESS\n");
			if(empty(0))printf("NONE\n"); //为空 
			else
			{
				reverse(root[0],2,stk[0].end);   //stack的pop顺序就是反过来的 
				print(root[0],2,stk[0].end);      //不输出-1 
				putchar('\n');
			}
			if(empty(1))printf("NONE\n");
			else
			{
				reverse(root[1],2,stk[1].end);
				print(root[1],2,stk[1].end);
			}
			exit(0);                         //前几天看某题解直接从dfs中强行退出...回溯的时间一刀砍掉TLE->AC 
		}
	}
}
//完结,撒花！ 

```


---

## 作者：leozhao123 (赞：1)

### [传送门](/problem/P4940) | [AC 记录](/record/192186773)
# Description
用 $Q\le 10^6$ 次操作维护 $2$ 个栈，最后输出栈内元素。
# Solution
题解区有手搓双向链表的大佬，但貌似用多个 `std::list` 辅助实现更简单，因为它除了【链接两个链表】以外的操作都帮我们写好了。

于是我们对常规操作进行如下改动：
## 链接
由于没有相关接口，无法直接访问链头、链尾地址，所以考虑使用插入**路牌**，即在需要链接的两端插入对方端的信息作为路牌，以便访问到此时直接跳转。

在本题，要用到此操作的只有 `MOVE x y`。可以发现，其相当于把 $y$ 反转后压入 $x$ 顶，原因可看楼下。因此，只需将 $x,y$ 的顶部链接，然后将 $y$ 的底部作为新的 $x$ 的顶部并为 $y$ 申请新的位置。

涉及到头尾的交换，所以需要记录它们的**绝对位置（所在链表的下标）** 和 **方向（位于链表的哪一端）**。用 $t_x,b_x$ 分别表示 $x$ 号栈顶部、底部的**绝对位置**，初始为 $x+1$。用 $et_x,eb_x\in\{0,1\}$ 分别表示 $x$ 号栈顶部、底部的**方向**，初始为 $et_x=0,eb_x=1$。

而对路牌的构造，需要一个包含 $t,et$ 并且和普通值区分的数字。有以下信息：
1. 普通值非负。
1. $et$ 为一位数。
1. $t\le Q+2=10^6+2$，因为最坏每个操作都是 `MOVE`。

所以路牌选择 $-(t_x\times 10+et_x)$。

**`MOVE 1 0` 的过程演示**：
![](https://cdn.luogu.com.cn/upload/image_hosting/x1v7r3px.png)

---
![](https://cdn.luogu.com.cn/upload/image_hosting/bif5xl6t.png)
**部分代码**：
```cpp
// 1. 插入路牌
ll tmp1=-(t[x]*10+et[x]);
ll tmp2=-(t[y]*10+et[y]);
PUSH(x,tmp2);
PUSH(y,tmp1);
// 2. 修改接口数据 
t[x]=b[y],et[x]=eb[y];
// 3. 将 y 迁移至新位置 
t[y]=b[y]=++l;
et[y]=0,eb[y]=1;
```
## 插入 / 弹出 / 取值
判断头或尾方向，调用对应函数即可。可用宏实现。

**部分代码**：
```cpp
#define PUSH(X,Y) \
({ if(et[(X)]==0) s[t[(X)]].push_front((Y)); \
   else           s[t[(X)]].push_back((Y)); })

#define POP(X) \
({ if(et[(X)]==0) s[t[(X)]].pop_front(); \
   else           s[t[(X)]].pop_back(); })

#define TOP(X)    (et[(X)]==0 ? s[t[(X)]].front() : s[t[(X)]].back())
#define BOTTOM(X) (et[(X)]==0 ? s[t[(X)]].back()  : s[t[(X)]].front())
```
## 遍历
反复弹出头部元素，如果是路牌就跳转，并把对面的也删除（路牌总是成对出现）。

**部分代码**：
```cpp
while(!s[t[x]].empty()) {
    ll tmp=TOP(x); POP(x);
    if(tmp<0) {
        et[x]=(-tmp)%10,t[x]=(-tmp)/10;
        POP(x);
    }// 发现路牌，跳转 
    else {/* 在这做一些事 */}
}
```
---
基本准备好后，剩下只需按要求模拟即可。
## PUSH
直接调用 `PUSH` 即可。
## POP
遍历直到成功取出非路牌。
## ADD / SUB
遍历两栈直到成功取出非路牌，相加 / 减再 `PUSH`。若其中一个未成功取出就抛出错误，**并把取出来没用上的再压回去**（忽略该指令，要还原）。
## DEL
考虑到每次都将栈内元素清空，总时间复杂度为 $\mathcal{O}(n)$，直接遍历删除即可。
## MOVE
上面【链接】的实现里讲过，不再多说。
## SWAP
交换接口数据即可，即分别交换 $t,b,et,eb$。
## END
遍历输出，记录是否成功输出。
# Code
```cpp
#include<iostream>
#include<list>
using namespace std;
using ll=long long;
#define SU cout<<"SUCCESS\n"
#define UN cout<<"UNSUCCESS\n"
// 定义宏时勤加括号 { } ( )
#define PUSH(X,Y) \
({ if(et[(X)]==0) s[t[(X)]].push_front((Y)); \
   else           s[t[(X)]].push_back((Y)); })

#define POP(X) \
({ if(et[(X)]==0) s[t[(X)]].pop_front(); \
   else           s[t[(X)]].pop_back(); })

#define TOP(X)    (et[(X)]==0 ? s[t[(X)]].front() : s[t[(X)]].back())
#define BOTTOM(X) (et[(X)]==0 ? s[t[(X)]].back()  : s[t[(X)]].front())
list<ll>s[(int)1e6+2];
// s[0] 不使用，因为 -0=0 不能作为路牌
string op;
ll x,y,t[2]={1,2},et[2]={0,0},b[2]={1,2},eb[2]={1,1},l=2;
int main() {
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    while(cin>>op) {
        if(op=="END") break;
        else if(op=="PUSH") {
            cin>>x>>y;SU;
			PUSH(x,y);
        }
        else if(op=="POP") {
            cin>>x;
            bool SU_pop=0;// 记录是否成功弹出 
            while(!s[t[x]].empty()) {
            	ll tmp=TOP(x); POP(x);
            	if(tmp<0) {
            		et[x]=(-tmp)%10,t[x]=(-tmp)/10;
            		POP(x);
				}
				else { SU_pop=1;SU;break;}
			}
			if(!SU_pop) UN;
        }
        else if(op=="ADD"||op=="SUB") {
            cin>>x;
			ll tmp1=-1,tmp2=-1;
        // 遍历 2 个栈并找到顶部元素，找不到就报错 
        // 与 POP 中的基本相同 
			while(!s[t[0]].empty()) {
				ll tmp=TOP(0); POP(0);
            	if(tmp<0) {
            		et[0]=(-tmp)%10,t[0]=(-tmp)/10;
            		POP(0);
				}
				else { tmp1=tmp;break;}
			}
			if(tmp1==-1) { UN;continue;}
			while(!s[t[1]].empty()) {
				ll tmp=TOP(1); POP(1);
            	if(tmp<0) {
            		et[1]=(-tmp)%10,t[1]=(-tmp)/10;
            		POP(1);
				}
				else { tmp2=tmp;break;}
			}
			if(tmp2==-1) { PUSH(0,tmp1);UN;continue;}// 注意要把没用上的 tmp1 再 push 回去 
        	if(op=="ADD") PUSH(x,tmp1+tmp2);
        	else PUSH(x,abs(tmp1-tmp2));
			SU;
		}
		else if(op=="DEL") {
			cin>>x;SU;
            while(!s[t[x]].empty()) {
            	ll tmp=BOTTOM(x);
            	s[t[x]].clear();
            	if(tmp<0) {
            		et[x]=(-tmp)%10,t[x]=-tmp/10;
            		POP(x);
				}
			}
		}
		else if(op=="MOVE") {
			cin>>x>>y;SU;
			ll tmp1=-(t[x]*10+et[x]);
			ll tmp2=-(t[y]*10+et[y]);
			PUSH(x,tmp2);
			PUSH(y,tmp1);
			t[x]=b[y],et[x]=eb[y];
			t[y]=b[y]=++l;
			et[y]=0,eb[y]=1;
        }
        else if(op=="SWAP") {
            SU;
            swap(t[0],t[1]);
            swap(et[0],et[1]);
            swap(b[0],b[1]);
            swap(eb[0],eb[1]);
        }
    }
    SU;
// 以下部分与 POP / ADD 中的基本相同 
	bool SU_out=0;
	while(!s[t[0]].empty()) {
		ll tmp=TOP(0); POP(0);
		if(tmp<0) {
			et[0]=(-tmp)%10,t[0]=(-tmp)/10;
			POP(0);
		}
		else cout<<tmp<<' ',SU_out=1;
	}
	if(!SU_out) cout<<"NONE";
	cout<<'\n';
	SU_out=0;
	while(!s[t[1]].empty()) {
		ll tmp=TOP(1); POP(1);
		if(tmp<0) {
			et[1]=(-tmp)%10,t[1]=(-tmp)/10;
			POP(1);
		}
		else cout<<tmp<<' ',SU_out=1;
	}
	if(!SU_out) cout<<"NONE";
    return 0;
}
```

---

## 作者：ganpig (赞：0)

用 `__gnu_cxx::rope` 逃课（

对每个栈存一正一反两个 `rope`

`MOVE` 操作时把 $Y_反$ 连接到 $X_正$ 后面，把 $Y_正$ 连接到 $X_反$ 前面，充分利用 `rope` 快速连接的功能（

剩下的操作暴力即可

### $\text{Code}$

```cpp
#include <bits/extc++.h>

int main() {
    __gnu_cxx::rope<long long> rope[2][2];
    while (true) {
        std::string op;
        std::cin >> op;
        if (op == "PUSH") {
            int id;
            long long val;
            std::cin >> id >> val;
            rope[id][0].push_back(val), rope[id][1].push_front(val);
            puts("SUCCESS");
        } else if (op == "POP") {
            int id;
            std::cin >> id;
            if (rope[id][0].empty())
                puts("UNSUCCESS");
            else {
                rope[id][0].pop_back(), rope[id][1].pop_front();
                puts("SUCCESS");
            }
        } else if (op == "ADD") {
            int id;
            std::cin >> id;
            if (rope[0][0].empty() || rope[1][0].empty())
                puts("UNSUCCESS");
            else {
                long long res = rope[0][0].back() + rope[1][0].back();
                rope[0][0].pop_back(), rope[0][1].pop_front();
                rope[1][0].pop_back(), rope[1][1].pop_front();
                rope[id][0].push_back(res), rope[id][1].push_front(res);
                puts("SUCCESS");
            }
        } else if (op == "SUB") {
            int id;
            std::cin >> id;
            if (rope[0][0].empty() || rope[1][0].empty())
                puts("UNSUCCESS");
            else {
                long long res = std::abs(rope[0][0].back() - rope[1][0].back());
                rope[0][0].pop_back(), rope[0][1].pop_front();
                rope[1][0].pop_back(), rope[1][1].pop_front();
                rope[id][0].push_back(res), rope[id][1].push_front(res);
                puts("SUCCESS");
            }
        } else if (op == "DEL") {
            int id;
            std::cin >> id;
            rope[id][0].clear(), rope[id][1].clear();
            puts("SUCCESS");
        } else if (op == "MOVE") {
            int x, y;
            std::cin >> x >> y;
            rope[x][0] += rope[y][1], rope[x][1].insert(0, rope[y][0]);
            rope[y][0].clear(), rope[y][1].clear();
            puts("SUCCESS");
        } else if (op == "SWAP") {
            rope[0][0].swap(rope[1][0]), rope[0][1].swap(rope[1][1]);
            puts("SUCCESS");
        } else if (op == "END") {
            puts("SUCCESS");
            if (rope[0][0].empty())
                puts("NONE");
            else {
                for (long long x : rope[0][1])
                    std::cout << x << ' ';
                std::cout << '\n';
            }
            if (rope[1][0].empty())
                puts("NONE");
            else {
                for (long long x : rope[1][1])
                    std::cout << x << ' ';
                std::cout << '\n';
            }
            return 0;
        }
    }
}
```

---

## 作者：cdx123456 (赞：0)

其他大佬用的方法太高级了，蒟蒻看不太懂，遂写一发双向链表的题解。

注意到除了 move 操作之外都可以用栈来解决，但是处理 move 就是 $O(n)$ 的，而栈的结构很难优化，所以放弃直接模拟的想法。

又注意到元素进行 move 操作后，栈之间元素的相邻关系没有改变，故考虑链表，然而常规链表还需要转换方向，原因见下图。![](https://cdn.luogu.com.cn/upload/image_hosting/2zhcvjws.png)

这样依次改变方向复杂度仍然为 $O(n)$，考虑优化。

可以仅保存元素之间的相邻关系，可以类比一下双向边，即这样。![](https://cdn.luogu.com.cn/upload/image_hosting/u2i78kr6.png)

至于插入删除之类的操作跟双向链表是一样的，注意不能写成 pre 或 nxt 之类的形式，因为这不是两个方向而是没有方向。

输出答案的时候从栈顶位置遍历到栈底位置即可。

## Code


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int tot,a[2000010],head[2],tail[2],son[2000010][2];
void add(int x,int y){
	a[++tot]=y;
	if(son[tail[x]][0]) son[tail[x]][1]=tot;
	else son[tail[x]][0]=tot;
	son[tot][0]=tail[x];
	tail[x]=tot;
}
void del(int x){
	if(tail[x]==head[x]) return;
	int y=tail[x];
	if(son[y][0]){
		int z=son[y][0];
		if(son[z][0]==y) son[z][0]=0;
		else son[z][1]=0;
		tail[x]=z;
		son[y][0]=0;
	}else{
		int z=son[y][1];
		if(son[z][0]==y) son[z][0]=0;
		else son[z][1]=0;
		tail[x]=z;
		son[y][1]=0;
	}
}
void merge(int x,int y){
	if(head[y]==tail[y]) return;
	if(son[tail[x]][0]) son[tail[x]][1]=tail[y];
	else son[tail[x]][0]=tail[y];
	if(son[tail[y]][0]) son[tail[y]][1]=tail[x];
	else son[tail[y]][0]=tail[x];
	if(son[head[y]][0]) tail[x]=son[head[y]][0];
	else tail[x]=son[head[y]][1];
	if(son[tail[x]][0]==head[y]) son[tail[x]][0]=0;
	else son[tail[x]][1]=0;
}
bool check(int x){
	return head[x]==tail[x];
}
signed main(){
	string s;
	int x,y;
	head[0]=tail[0]=++tot;
	head[1]=tail[1]=++tot;
	while(cin>>s){
		if(s=="END"){
			cout<<"SUCCESS"<<endl;
			if(check(0)) cout<<"NONE";
			x=tail[0];
			y=0;
			while(x!=head[0]){
				cout<<a[x]<<' ';
				if(son[x][0]==y){
					y=x;
					x=son[x][1];
				}else{
					y=x;
					x=son[x][0];
				}
			}
			cout<<endl;
			if(check(1)) cout<<"NONE";
			x=tail[1];
			y=0;
			while(x!=head[1]){
				cout<<a[x]<<' ';
				if(son[x][0]==y){
					y=x;
					x=son[x][1];
				}else{
					y=x;
					x=son[x][0];
				}
			}
			cout<<endl;
			break;
		}
		if(s=="PUSH"){
			cin>>x>>y;
			add(x,y);
			cout<<"SUCCESS"<<endl;
			continue;
		}
		if(s[0]=='P'){
			cin>>x;
			if(check(x)){
				cout<<"UNSUCCESS"<<endl;
				continue;
			}
			del(x);
		}
		if(s[0]=='A'){
			cin>>x;
			if(check(0) || check(1)){
				cout<<"UNSUCCESS"<<endl;
				continue;
			}
			int y=a[tail[0]],z=a[tail[1]];
			del(0); del(1);
			add(x,y+z);
		}
		if(s=="SUB"){
			cin>>x;
			if(check(0) || check(1)){
				cout<<"UNSUCCESS"<<endl;
				continue;
			}
			int y=a[tail[0]],z=a[tail[1]];
			del(0); del(1);
			add(x,abs(y-z));
			cout<<"SUCCESS"<<endl;
			continue;
		}
		if(s[0]=='D'){
			cin>>x;
			tail[x]=head[x];
			son[head[x]][0]=son[head[x]][1]=0;
		}
		if(s[0]=='M'){
			cin>>x>>y;
			merge(x,y);
			head[y]=tail[y]=++tot;
		}
		if(s[0]=='S'){
			swap(head[0],head[1]);
			swap(tail[0],tail[1]);
		}
		cout<<"SUCCESS"<<endl;
	}
	return 0;
}
```

---

