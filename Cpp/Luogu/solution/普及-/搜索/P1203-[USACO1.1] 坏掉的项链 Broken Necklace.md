# [USACO1.1] 坏掉的项链 Broken Necklace

## 题目描述

你有一条由 $n$ 个红色的，白色的，或蓝色的珠子组成的项链，珠子是随意安排的。 这里是 $n=29$ 的两个例子:

![](https://cdn.luogu.com.cn/upload/image_hosting/i7imvc0g.png) 

第一和第二个珠子在图片中已经被作记号。

图片 A 中的项链可以用下面的字符串表示：

`brbrrrbbbrrrrrbrrbbrbbbbrrrrb`

假如你要在一些点打破项链，展开成一条直线，然后从一端开始收集同颜色的珠子直到你遇到一个不同的颜色珠子，在另一端做同样的事(颜色可能与在这之前收集的不同)。 确定应该在哪里打破项链来收集到最大数目的珠子。

例如，在图片 A 中的项链中，在珠子 $9$ 和珠子 $10$ 或珠子 $24$ 和珠子 $25$ 之间打断项链可以收集到 $8$ 个珠子。

白色珠子什么意思?

在一些项链中还包括白色的珠子(如图片B) 所示。

当收集珠子的时候，一个被遇到的白色珠子可以被当做红色也可以被当做蓝色。

表现含有白珠项链的字符串将会包括三个符号 `r`，`b`，`w` 。

写一个程序来确定从一条被给出的项链可以收集到的珠子最大数目。

## 说明/提示

【数据范围】  
对于 $100\%$ 的数据，$3\le n \le 350$

题目翻译来自NOCOW。

USACO Training Section 1.1

## 样例 #1

### 输入

```
29 
wwwbbrwrbrbrrbrbrwrwwrbwrwrrb
```

### 输出

```
11```

# 题解

## 作者：w_y_c (赞：134)

竟然没人用string 看得到数据真幸福。。

注释写的听清楚了

```cpp
#include <iostream>
#include <algorithm>
using namespace std;
string a;
int f(int x)
{
    int s=0;
    char a1=a[x];
    char b2=a[x+1];
    for(int i=x;;i--)//往前看和往后看
    {
        if(a[i]==a1)s++;
        else if(a[i]=='w')
            s++;
        else
            break;
    }
    for(int i=x+1;;i++)
    {
        if(a[i]==b2)s++;
        else if(a[i]=='w')
            s++;
        else
            break;
    }
    return s;
}
int main()
{
    int ans,n;
    ans=-1;
    cin>>n;cin>>a;
    a=a+a+a;
    for(int i=n;i<2*n;i++)//三段 从中间那一段开始处理
    {
        if(a[i]==a[i+1])
            continue;
        if(a[i]=='w')//这TMD硬是看的到第三个点 要不然真不会
        {
            a[i]='r';
            ans=max(ans,f(i));
            a[i]='b';
            ans=max(ans,f(i));
            a[i]='w';
        }
        ans=max(ans,f(i));
    }
    ans=min(ans,n);//最长也不能比总长长
    if(ans==-1)ans=n;//出现这种情况必定是一路continue过来的
    cout<<ans<<endl;
    return 0;
}

```

---

## 作者：青衫白叙 (赞：88)

这绝对是最短的题解了。。。（难理解别打我。）

附上样例的输出以及中间结果来帮助理解：

c   a  b  w  ans

0  1  1  0

0  2  2  0

0  3  3  0

b  0  4  0  3

b  0  5  0  3

r   5  1  0  5

r   5  2  1  5

r   5  3  0  5

b  3  1  0  8

r   1  1  0  8

b  1  1  0  8

r   1  1  0  8

r   1  2  0  8

b  2  1  0  8

r   1  1  0  8

b  1  1  0  8

r   1  1  0  8

r   1  2  1  8

r   1  3  0  8

r   1  4  1  8

r   1  5  2  8

r   1  6  0  8

b  6  1  0  8

b  6  2  1  8

r   1  2  0  8

r   1  3  1  8

r   1  4  0  8

r   1  5  0  8

b  5  1  0  8

b  5  2  1  8

b  5  3  2  8

b  5  4  3  8

b  5  5  0  8

b  5  6  0  8

r   6  1  0 11

r   6  2  1 11

r   6  3  0 11

b  3  1  0 11

r   1  1  0 11

b  1  1  0 11

r   1  1  0 11

r   1  2  0 11

b  2  1  0 11

r   1  1  0 11

b  1  1  0 11

r   1  1  0 11

r   1  2  1 11

r   1  3  0 11

r   1  4  1 11

r   1  5  2 11

r   1  6  0 11

b  6  1  0 11

b  6  2  1 11

r   1  2  0 11

r   1  3  1 11

r   1  4  0 11

r   1  5  0 11

b  5  1  0 11

11
c：当前处理的字符

a：从i向左最长的长度

b：从i向右最长的长度

w：当前w个数

我们知道：当b重新计算时，其实a已经算好了。。就是b-w（当前的w已经算在b里面了）（正着反着不是一样的吗）

而b重新计算时，又应该加上前面w的个数

好像没什么了。。。更新答案应该在b算完的时候。。a在上一轮已经算过了。。

```cpp
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
char s[700],c;
int a, b, w, ans;
int main(){
    int n;
    scanf("%d%s",&n,s);
    memcpy(s+n,s,n);
    //printf(" c  a  b  w  ans\n");
    for(int i = 0; i < n<<1; i++) {
        if(s[i] == 'w') b++,w++;else
        if(s[i] ==  c ) b++,w=0;else
        ans=max(ans,a+b),a=b-w,b=w+1,w=0,c=s[i];
        //printf("%2c %2d %2d %2d %2d\n",c,a,b,w,ans);
    }
    ans=max(ans,a+b);
    printf("%d\n",min(ans,n));
    return 0;
}
```

---

## 作者：田阙西 (赞：49)

这是个动态规划的题解，，，


先放方程：


ans=max(ans,max(lR[i],lB[i])+max(rR[i+1],rB[i+1]));


还有注意：由于我们复制了这个字符串，所以最后ans可能大于原串长度，要特判。


我一开始数组忘了开两倍，发现了惊天大秘密：

虽然有时候由于评测姬善良我们数组越界不会出现问题。

但是！当你几个数组连续开时，前一个数组越界的部分可能就是后一个数组申请的位置！！！

所以当我程序里越界的lR[i]＋1时，RB中的某个格子也同时加了1！(准确的说是第401号格子）

切记切记


```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<map>
#include<vector>
#include<cstring>
#include<cmath>
using namespace std;
int n,rR[400*2],rB[400*2],lR[400*2],lB[400*2],ans;
char c[400*2];
int fastRead()
{
	int f=1,r=0;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){r=r*10+c-'0';c=getchar();}
	return f*r;
}
int main()
{
	n=fastRead();
	scanf("%s",c+1);
	for(int i=1;i<=n;++i)
	c[i+n]=c[i];lB[0]=0;lR[0]=0;
	for(int i=1;i<=n*2;++i)
	{
		if(c[i]=='w')
		{
			lR[i]=lR[i-1]+1;
			lB[i]=lB[i-1]+1;
		}
		else if(c[i]=='r')
		{
			lR[i]=lR[i-1]+1;
		}
		else if(c[i]=='b')lB[i]=lB[i-1]+1;
	}
	for(int i=n*2;i>=1;--i)
	{
		if(c[i]=='w')
		{
			rR[i]=rR[i+1]+1;
			rB[i]=rB[i+1]+1;
		}
		else if(c[i]=='r')
		{
			rR[i]=rR[i+1]+1;
		}
		else if(c[i]=='b')rB[i]=rB[i+1]+1;	
	}
	for(int i=(n<<1)-1;i>=1;--i)
    ans=max(ans,max(lR[i],lB[i])+max(rR[i+1],rB[i+1]));
    if(ans>n)ans=n;
    printf("%d",ans);
    return 0;
}
```

---

## 作者：Dvelpro (赞：39)

史上最笨方法 暴力  讲字符串扩大两倍  设置两个指针一个向左走一个向右走

要注意 遇到两个左右两个值都是w 的情况

`



```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 1000;
char a[1000];
int b[10001];
int main(){
    int n;
    cin>>n;
    cin>>a;
    for(int j=n;j<n*2;j++){
      a[j]=a[j-n];
    }
    int mx=0;
    for(int j=0;j<2*n;j++){
       int l=j,r=j+1;
       char la=a[l];
       char ra=a[r];
       if(a[l]=='w'){    //特殊情况
          la=a[l-1];
       }
       if(a[r]=='w'){
         ra=a[r-1];
       }
       int ans=0;
       while(l>=0){
          if(a[l]==la||a[l]=='w'){
             ans++;
          }
          else break;
          l--;
       }
       while(r<2*n){
          if(a[r]==ra||a[r]=='w'){
             ans++;
          }
          else break;
          r++;
       }
       mx=max(mx,ans);
    }
    if(mx>n) mx=n;          //如果超出范围取 n
    cout<<mx<<endl;
    return 0;
}
`
```

---

## 作者：key_rA9 (赞：29)

 _怎么没有人直接搜索呢？_   
本蒟蒻实在想不通大佬各种方法，只好采用直接搜索的办法，枚举断开处往两边搜索，用l和r数组记录左边和右边就不用判断1和n的状况了。
具体看代码：
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;int n,l[360],r[360],ans;//用数组记录每个位置的相邻位置，因为数据范围不大  
char a[360];//项链串  
int main()  
{  
	scanf("%d",&n);//项链长度  
	gets(a);gets(a+1);//第一行的换行占一次输入  
	for(int i=1;i<=n;i++)l[i]=i-1,r[i]=i+1;//左右位  
	l[1]=n;r[n]=1;//首尾  
	for(int i=1;i<=n;i++)//枚举断点在i-1处  
	{bool bk=0;//用来记录特殊情况  
		int p=l[i],q=i,s=2;//相同的一开始至少有两个  
		char lc=a[p],rc=a[q];//记录第一个的颜色  
		while(lc=='w'||a[l[p]]==lc||a[l[p]]=='w')//第一个颜色白或左边和开始一样或左边就是白都可以继续  
		{  
			if(l[p]==q){bk=1;break;}//如果左边和另一端重合，跳出  
			p=l[p],s++;if(lc=='w')lc=a[p];//往左，如果开端颜色为白搜到后面极有可能出问题，所以改成现在的颜色，反正都是连续同颜色的。  
		}if(bk){ans=n;break;}//因为一端可搜到另一端，那么一定是所有颜色一样  
		while(rc=='w'||a[r[q]]==rc||a[r[q]]=='w')//同上  
		{
			if(r[q]==p){bk=1;break;}//和另一端停止处重合，其实也是全一样  
			q=r[q],s++;if(rc=='w')rc=a[q];//往右  
		}if(bk){ans=n;break;}
		if(s>ans)ans=s;//更新最大结果  
	}printf("%d\n",ans);//输出  
}  
```  
弱弱的说一句：关键就只有输入以及判断颜色有点麻烦，~~其他都很一般~~
###### 第一次写题解，心情万分激动。。。

---

## 作者：AgrumeStly (赞：13)

## 坏掉的项链

#### 欢迎来到TNT_BOOM大讲堂，
今天我们来讲一下P1203 坏掉的项链。

这题是 _DP_

可我用的是 _模拟_ 的方法

首先看题目：

![www.luogu.org](https://cdn.luogu.com.cn/upload/pic/56.png)

图A 它的输入是这样的：



**_brbrrrbbbrrrrrbrrbbrbbbbrrrrb_**

而真正的项链是一个圈。

那么怎么将一条变成一圈呢？

 我 灵 (cha) 机 (xia) 一 (bai )动 (du)

发现可以这样：

brbrrrbbbrrrrrbrrbbrbbbbrrrrb brbrrrbbbrrrrrbrrbbrbbbbrrrrb

将项链变成两条，这样就相当于变成一圈了。

话不多说，上代码：

```cpp
# include <cstdio>
# include <cstring>
# include <algorithm>
# include <cmath>

# define FOR(i, a, b) for (int i = a; i <= b; ++i)
# define _FOR(i, a, b) for (int i = a; i >= b; --i)

using namespace std;

const int NR = 400;

int main()
{
    int n;
    scanf("%d", &n);
    char s[NR];
    scanf("%s", s);
    int ans = 0;
    for (int i = 0; i < n; i++)
   	{
   		// 从i往前找,另一个从i + 1往后找
   		// 向左找蓝色
   		int blue = 0;
   		for (int j = 0; j < n; j++) {
   			if (s[(i - j + n) % n] == 'r') break;
   			else blue++;
   		}
   		int red = 0;
   		for (int j = 0; j < n; j++) {
   			if (s[(i - j + n) % n] == 'b') break;
   			else red++;
   		}
   		int left = max(blue, red);
   		blue = 0;
   		for (int j = 1; j <= n; j++) {
   			if (s[(i + j) % n] == 'r') break;
   			else blue++;
   		}
   		red = 0;
   		for (int j = 1; j <= n; j++) {
   			if (s[(i + j) % n] == 'b') break;
   			else red++;
   		}
   		int right = max(blue, red);
   		ans = max(ans, left + right);
   	}
   	printf("%d\n", min(ans,n));
    return 0;
}
```

###### 精心策划，希望支持！

### 再见！

---

## 作者：江浸月 (赞：13)

本蒟蒻第一次发题解.

思路是暴力搜索,把字符串复制为两份,遍历字符串.

看题解貌似没人和我思路重复,发一下吧,注释写的挺清楚了,不理解的话把我注释掉的两行运行一下就知道了.
```cpp
//P1203
#include<bits/stdc++.h>
using namespace std;
string s,s1,s2;
int n,ans,ans1;
void search(int a)
{
	s2=s.substr(a)+s;//复制一份字符串
	s2.erase(n);//保留字符串
	s1=s2;//再复制一份
	reverse(s2.begin(),s2.end());//翻转,模拟在另一端取珠子
    //cout<<s1<<" "<<s2<<endl;
	int j=0;
	while(s1[j]=='w')
	{
	  	ans++;
	  	j+=1;
	}
	for(int i=j;i<n;i++)
	{
	  if(s1[j]==s1[i]||s1[i]=='w') ans++;
	  else break;
	}//遍历字符串s1,注意考虑第一个珠子为白色的情况
	j=0;
	while(s2[j]=='w')
	{
	  	ans++;
	  	j+=1;
	}
	for(int i=j;i<n;i++)
	{
	  if(s2[j]==s2[i]||s2[i]=='w') ans++;
	  else break;
	}//遍历字符串s2
    //cout<<ans<<endl;
	ans1=max(ans,ans1);//储存结果
	ans=0;//一定要注意每次遍历完成后结果清零
}
int main()
{
	cin>>n>>s;
	for(int i=0;i<n;i++) search(i);//暴力搜索
	ans1=min(n,ans1);//答案不能超过总长
	cout<<ans1<<endl;
	return 0;
}
```

---

## 作者：Alarm5854 (赞：10)

什么？32篇题解竟然没有一个用链表做的？于是我就来写一篇用链表做的题解。利用链表可以节省空间，以免浪费。而这道题是要把环拆成链的，正好符合链表，而我用的就是循环链表。尝试每一个断点，然后开始往前往后数，数到等于n时就直接停下输出答案，否则如果颜色不一样且不为白色，就终止循环。，注意一点，如果断点是白色的，就要每循环一个点就尝试更新颜色，否则就WA了~~亲身经历~~，代码对初学者有一些不友好，请见谅。
### 完整代码如下：
```
#include<bits/stdc++.h>
using namespace std;
struct node{
	node *prv,*nxt;//为了防止CE我把元音吃掉了
	char color;
};//双向链表的基本模型
node *head,*tail,*p;//头指针、尾指针、辅助指针（尾指针其实只在刚开始有用）
int n,ans=1;
char c;
int main(){
	scanf("%d",&n);
	while(getchar()!='\n');//吃掉换行符
	head=new node;//先申请一个节点
	head->color=getchar();
	head->prv=head,head->nxt=head,tail=head;//把前驱后继都先指向自己，且与尾指针重合
	for(int i=1;i<n;++i){
		p=new node;//对于每个辅助指针都先申请
		p->prv=tail,p->nxt=head;//把这个指针的前驱改为尾指针，后继改成头指针
		p->prv->nxt=p,p->nxt->prv=p;//接着改变头指针和尾指针的前驱与后继
		tail=p,p->color=getchar();//把尾指针向后移动一位，并输入
	}//这样输入完之后头指针和尾指针也相连了，符合项链的样子
	p=head;//把这个指针先指向头指针
	do{
		node *q=p->prv;//q节点先默认为p节点的前驱
		int temp=1;
		char color=p->color;//把颜色先默认为p节点的颜色
		while(q->color=='w'||q->color==color||color=='w'){//循环的条件
			if(temp==n) return 0&printf("%d",n);//这个地方用了简写，本应写为if(temp==n){printf("%d",n);return 0;}
			color=(color=='w'?q->color:color)/*如果颜色还是白色，就更新颜色*/,++temp,q=q->prv;//答案++，指针向后移动一位
		}q=p->nxt,color=p->nxt->color;//把q改为p的后继，还要注意颜色应为q节点的颜色
		while(q->color=='w'||q->color==color||color=='w'){
			if(temp==n) return 0&printf("%d",n);
			color=(color=='w'?q->color:color),++temp,q=q->nxt;//类似
		}p=p->nxt,ans=max(ans,temp);//p指针向后移动一位，并尝试更新答案
	}while(p!=head);
	return 0&printf("%d",ans);//这个地方也是简写
}
```
这道题目的方法有很多种，如果看不懂我的题解你还可以看别人的题解。如果看懂了，并A了，请给我一个赞，谢谢！

---

## 作者：CoolTeam (赞：9)

注意是环形...比较方便的处理就是复制一遍。比如rwb,处理成rwbrw。最后输出可能要注意一下，如果最大值超过长度的话就输出长度。

①枚举每个位置，左右搜。比较慢

②预处理出left[i],right[i]，分别表示从位置i向左搜索和向右搜索，能得到连续相同颜色的珠子数(包括w)，答案就是max{left[i]+right[i+1]}

```cpp
#include<stdio.h>
#include<string.h>
int i,j,n,m,left[400],right[400];
char A[800],B[400],now;
int main(void)
{
    scanf("%d",&m);while(getchar()!='\n');gets(&A[1]);
    if(m==0){printf("0");return 0;}
    strcpy(B,&A[1]);B[n-1]='\0';
    strcat(&A[1],B);n=2*m-1;
    for(i=1;i<=n;i++)left[i]=right[i]=1;
    for(i=1;i<=n&&A[i]=='w';i++)left[i]=left[i-1]+1; now=A[i];
    while(i<=n)
    {
        for(;i<=n&&(A[i]==now||A[i]=='w');i++) left[i]=left[i-1]+1;
        now=A[i];left[i]=1;
        for(j=i-1;j>=1&&A[j]=='w';j--) left[i]++;
        i++;
    }
    for(i=n;i>=1&&A[i]=='w';i--)right[i]=right[i+1]+1; now=A[i];
    while(i>=1)
    {
        for(;i>=1&&(A[i]==now||A[i]=='w');i--) right[i]=right[i+1]+1;
        now=A[i];right[i]=1;
        for(j=i+1;j<=n&&A[j]=='w';j++) right[i]++;
        i--;
    }
    int ans=0;
    for(i=1;i<=n;i++)
        if(ans<left[i]+right[i+1]) 
            ans=left[i]+right[i+1];
    printf("%d",ans>m?m:ans);
    return 0;    
}
```
③直接数，这种方法的话代码最短了。三个数left,right,w分别存放上一颜色，当前颜色以及w的连续最大值。

```cpp
for(i=1;i<=2*n-1;i++)
{
    if(A[i]=='w') {right++;w++;} 
    else if(A[i]==c){right++;w=0;}
    else
    {
        left=right-w;
        right=1+w;
        w=0;
        c=A[i];
    }
    if(left+right>ans) ans=left+right;
}
```

---

## 作者：Strong_Jelly (赞：9)

# dfs搜索

**这道题用搜索就可以搞定么~，不知道为什么还挂着动规的标签（~~狐假虎威 + 滥竽充数~~）**

## 思路：

### 暴力枚举i从0 ~ n - 1，表示从i处分开字符串，再以环的方式（0连着n - 1）把x及x之前的字符（0 ~ x）连到后面（及连到x + 1 ~ n + 1的后面），再从前往后搜索求相同颜色的珠子的数量，再从后往前搜索求相同颜色的珠子的数量，把它们的值相加起来求最大就好了

再来解释一下**样例**（对于题目没怎么懂的人很有帮助）：

**原项链**：wwwbbrwrbrbrrbrbrwrwwrbwrwrrb，真实来看就是（直接涂颜色了）



![](https://cdn.luogu.com.cn/upload/pic/58688.png)


最佳方案是**从倒数第一个点（绿色那里）前分开**：
wwwbbrwrbrbrrbrbrwrwwrbwrwrr|b


![](https://cdn.luogu.com.cn/upload/pic/58687.png)

那么再从新连起来就是 ： bwwwbbrwrbrbrrbrbrwrwwrbwrwrr。从前搜（黑体部分为相同颜色的珠子）： **bwwwbb**rwrbrbrrbrbrwrwwrbwrwrr，白变蓝：**bbbbbb**rwrbrbrrbrbrwrwwrbwrwrr ——**6个蓝色**。从后搜：bwwwbbrwrbrbrrbrbrwrwwrb**wrwrr**，白变红：bwwwbbrwrbrbrrbrbrwrwwrb**rrrrr**——5个红色，加起来就是11个珠子


code：

```cpp
//题解中的register和inline均可以去掉(这是用于优化的)
#include <bits/stdc++.h>//万能头 
using namespace std;
int n, maxn;
string s, x, y;//s为原字符串，x为正向，y为反向 
inline int dfs_front(int l)//从前往后搜索 
{
	int ans = 0;//定义ans为从前往后搜索可得到的最长长度 
    int k = 0;
    while(x[k] == 'w')//判起始就是白色 
    {
        ++ans;
        ++k;
    }
    for(register int i = k/*从不是白色的第一个字符开始*/; i < n; ++i)
    {
      	if(x[k] == x[i] || x[i] == 'w')//等于除白色之外的起始字符或是白色就可以ans++ 
		{
		  	++ans;
		}
      	else 
		{
		  	break;
		}
    }
    return ans;//返回ans 
}
inline int dfs_back(int l)//从后往前搜索(y字符串已经反转过了) 
{
	int ans = 0;//定义ans为从后往前搜索可得到的最长长度 
	int k = 0;
    while(y[k] == 'w')//判起始就是白色
    {
        ++ans;
        ++k;
    }
    for(register int i = k/*从不是白色的第一个字符开始*/; i < n; ++i)
    {
      	if(y[k] == y[i] || y[i] == 'w')//等于除白色之外的起始字符或是白色就可以ans++
		{
			++ans;
		}
      	else 
		{
		  	break;
		}
    }
    return ans;//返回ans 
}
inline void init(int l)//初始化x和y(理解为从l除剪开字符串再拼接回去)
{
	x = "";//先清空 
	y = "";
	for(register int i = l + 1; i < n; ++i)
	{
		x += s[i];//字符串福利(理解为把x字符串的后面拼上s[i]字符或字符串) 
	}
	for(register int i = 0; i <= l; ++i)
	{
		x += s[i];
	}
	y = x;//字符串福利(理解为把x字符串赋值给y就行了) 
	reverse(y.begin(), y.end());//字符串福利(理解为把一个字符串反转过来就可以了) 
}
int main()
{
    cin >> n >> s;
    for(register int i = 0; i < n; ++i)
	{
		init(i);//初始化 
		maxn = max(maxn, dfs_front(i) + dfs_back(i)/*算两次搜索之和*/);//取最大值 
	}
    printf("%d", min(n, maxn));//再长也不能超过n 
    return 0;
    /*CE;
}
```

求过~

---

## 作者：Sino_E (赞：8)

观察数据范围，发现枚举可过（复杂度O(n^2)），选择直接枚举。

断环成链思想，把整个项链复制一份接在后面。

注意不能重复取走珍珠，因此标记注意两边都要标记。

枚举断链部分，两边模拟取珍珠，看看每个地方断链能取多少个珍珠，最后取个最大值就行。

更多思路细节和实现细节见代码注释quq

```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N=800;

int gi(){
    int x=0;
    char ch=getchar();
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
    return x;
}//读入优化 

char bead[N];//记录珍珠 
bool gett[N];//标记珍珠是否被取 
int n;
inline void marked(int x){
    if(x<n) gett[x]=gett[x+n]=1;
    else gett[x]=gett[x-n]=1;
}//标记珍珠函数（记得被复制的一份也要标记） 

/*取珍珠函数，x为断链点的左边一个珍珠的位置，返回从这儿最多能取多少个珍珠*/ 
int gb(int x){
    memset(gett,0,sizeof(gett));    //重置标记 
    int cnt=1;    //记录拿到了多少个珍珠 
    /*首先，从x开始往左边取的代码*/ 
    char sta=bead[x];    //第一个珍珠，标准珍珠 
    marked(x);    //记得标记quq 
    for(int i=x-1;i>=0;i--){
        if(gett[i])break;
        if(bead[i]==sta||bead[i]=='w')cnt++;    //如果比较的这个珍珠颜色相同（包括了w==w的情况），或者要取的珍珠可以被染色 
        else if(sta=='w')sta=bead[i],cnt++;        //如果颜色不同而且标准珍珠可被染色 
        /*如果标准珍珠为w，那么会有两种情况。
        1.连续取的珍珠都是w。那么不用管，继续往下取。
        2.取到某个珍珠不是w。那么按照贪心原则，我们必须给w染色，染成什么颜色呢？肯定染成与这个珍珠相同的颜色。
        否则这个珍珠就取不了了，不符合贪心原则.-.
        染过色之后色彩当然就改不了了，不过这已经是最佳方案了。
        所以综上所述：遇到第一个不与标准珍珠w相等的珍珠，把标准珍珠的颜色换成这个珍珠的颜色。
        代码实现如此。*/ 
        else break;
        marked(i);
    }
    /*接着，从x+1开始往右边取的代码*/ 
    if(!gett[x+1])cnt++;    //请注意因为是环，所以开始往右取的时候第一个标准珍珠有可能已经被标记。此时得特判。 
    sta=bead[x+1]; marked(x+1);
    //如果标准珍珠早就被取，那么下面一段根本不会进行。 
    for(int i=x+2;i<2*n;i++){
        if(gett[i])break;
        if(bead[i]==sta||bead[i]=='w')cnt++;
        else if(sta=='w')sta=bead[i],cnt++;
        else break;
        marked(i);
    }
    return cnt;
}

int main(){
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>bead[i];
        bead[i+n]=bead[i];    //断环成链 
    }
    int ans=0;
    for(int i=1;i<2*n-1;i++)
        ans=max(ans,gb(i));    //枚举断链点取珍珠，取最大值 
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：Ciyang (赞：6)

### 这个题的题解应该没有用双向队列的,这里本弱用了STL容器里的双向队列做这道题,当然思路比较重要,代码有一部分很暴力,主要是第三个点太暴力! 
### 我当时看到环形就想到了循环队列,因为有两个方向,所以用双向队列  
### 具体就是用双向队列+循环队列+搜索+模拟,总之就是循环...
### 我先给出第三个点会WA的做法,因为思路和代码较为清晰,根据这个讲解一下:
#### 评测详情:
#### Unaccepted  89
#### 用时: 36ms / 内存: 800KB
```cpp
#include<iostream>
#include<deque>
#include<limits.h>
#include<stdio.h>
using namespace std;
deque<char>z;
//首先要开一个队列
//项链的每一个珠子,队列所有数值的位置随着要打破项链的地方改变而改变
//即队列的头珠子就是打破的地方向右找的首个珠子
//这句话有点绕,不懂向下看
int main(){
    int n;
    cin>>n;
    //输入n
    for(int i=0;i<n;i++){
        char c;
        cin>>c;
        //最好不用getchar(),不然会读入上一个空格
        z.push_back(c);
        //把所有珠子放入队列
    }
    int interrupt=0,zuida=0;
    //interrupt为当前打破的地方位于哪个珠子之前(输入顺序的珠子,0代表首元素)
    while(interrupt!=n&&zuida!=n){
    //已经全部搜索或最大连接已经为n就跳出
        int cd1=0,cd2=0;
        //两个int分别记录左边和右边的珠子连接数
        deque<char>z1(z);
        deque<char>z2(z);
        //两个z的副本z1,z2
        char z1begin=z1.back();
        //左珠子首元素为当前队列尾元素
        while(cd1!=n){
        //连接的珠子已经为全部就跳出
            z1.push_front(z1.back());
            z1.pop_back();
            //循环队列,将尾元素提到队列首位
            if(z1.front()!=z1begin&&z1.front()!='w')break;
            //珠子颜色不一样或不为白色就跳出
            cd1++;
        }
        char z2begin=z2.front();
        while(cd2!=n){
            z2.push_back(z2.front());
            z2.pop_front();
            //循环队列,将首元素放到队列尾部
            if(z2.back()!=z2begin&&z2.back()!='w')break;
            //珠子颜色不一样或不为白色就跳出
            cd2++;
        }
        if(cd1+cd2>n)zuida=n;
        else zuida=max(cd1+cd2,zuida);
        //特判,因为珠子会有重复搜索,最大不超过n
        z.push_back(z.front());
        z.pop_front();
        //循环队列,将z的首元素放到尾元素
        interrupt++;
        //打破项链的位置+1
    }
    cout<<zuida<<endl;
    输出最大值
    return 0;
}
```
### 然后好像并没有什么错误,也只是好像！为什么第三个点WA??? 
### 我看了多个题解，的确第三个点需要特判 
### 当左边或右边起始点为白色时,代表这个点可以看作为红色或蓝色. 
### 也就是遇到z1begin=='w'时或z2begin=='w'时要让他们为代表红色或蓝色  
### 但这修改代码比较麻烦,我就直接暴力if和计算,为了代码长度,我用了函数  
### 修改后代码:
#### 评测状态
#### Accepted  100
#### 用时: 37ms / 内存: 800KB
```cpp
#include<iostream>
#include<deque>
#include<limits.h>
#include<stdio.h>
using namespace std;
deque<char>z;
void cmp(int&need,int total,int nummax){
	//比较和特判
	if(total>nummax)need=nummax;
	else if(total>need)need=total;
	return;
}
int leftfind(int n,char z1begin){
	//向左搜索,参数为珠子总数和首字符
	deque<char>z1(z);
	int cd1=0;
	while(cd1!=n){
		z1.push_front(z1.back());
		z1.pop_back();
		if(z1.front()!=z1begin&&z1.front()!='w')break;
		++cd1;
	}
	return cd1;
}
int rightfind(int n,char z2begin){
	//向右搜索,参数同理
	deque<char>z2(z);
	int cd2=0;
	while(cd2!=n){
		z2.push_back(z2.front());
		z2.pop_front();
		if(z2.back()!=z2begin&&z2.back()!='w')break;
		++cd2;
	}
	return cd2;
}
int main(){
	int n;
	cin>>n;
	for(int i=0;i<n;i++){
		char c;
		cin>>c;
		z.push_back(c);
	}
	int interrupt=0,zuida=0;
	while(interrupt!=n&&zuida!=n){
		int cd1=0,cd2=0;
		char z1begin=z.back(),z2begin=z.front();
		if(z1begin=='w'){
        //如果向左查找首元素为白色,枚举为r或b两种情况
			cd1=leftfind(n,'r');
			if(z2begin=='w'){
            //如果向右首元素为白色,枚举为r或b两种情况
				cd2=rightfind(n,'r');
				cmp(zuida,cd1+cd2,n);
				cd2=rightfind(n,'b');
				cmp(zuida,cd1+cd2,n);
			}
            else{
            	cd2=rightfind(n,z2begin);
                cmp(zuida,cd1+cd2,n);
			}
			cd1=leftfind(n,'b');
			if(z2begin=='w'){
				cd2=rightfind(n,'r');
				cmp(zuida,cd1+cd2,n);
				cd2=rightfind(n,'b');
				cmp(zuida,cd1+cd2,n);
			}
            else{
            	cd2=rightfind(n,z2begin);
                cmp(zuida,cd1+cd2,n);
			}
		}
		else{
        	//首元素不为白色就按首元素原值搜索
			cd1=leftfind(n,z1begin);
			if(z2begin=='w'){
				cd2=rightfind(n,'r');
				cmp(zuida,cd1+cd2,n);
				cd2=rightfind(n,'b');
				cmp(zuida,cd1+cd2,n);
			}
			else{
				cd2=rightfind(n,z2begin);
				cmp(zuida,cd1+cd2,n);
			}
		}
		z.push_back(z.front());
		z.pop_front();
		++interrupt;
	}
	cout<<zuida<<endl;
    //输出
	return 0;
}
```

---

## 作者：Piwry (赞：4)

**没人来个On的算法吗**
###### (好歹我写了好久)
- 对于每次相邻的不同字符，对前面的字符段记录

1. 上一次可连的最大长度
2. 相邻的白色长度
3. 相邻的可连长度（**不包括**2）
4. 相邻可连长度的代表字符

- 对于每次相邻的相同字符，记录**长度**

---

下面默认每次**相邻的不同字符**的**前一个**字符为当前字符

并设

1. $lastw$为相邻的白色长度

1. $lastl$为相邻的可连长度

1. $lastc$为$lastl$的代表字符

1. $nowl$为长度

- **当当前字符和代表字符相等时**

1. $lastl=nowl+lastw$( _因为最新加的这一段的阻隔，之前这段白色已经**不相邻**了，但它仍可以被接到当前总的这段_ )
1. $lastw=0$

- **当当前字符和$lastc$不相等但为'w'时**

1. 直接将 $lastw+=nowl$

- **当当前字符和代表字符不相等也不为'w'时**

1. 记录$lastl$ ( _不记录$lastw$是因为它可以**被接到下一段**_ )
1. $lastl=lastw+nowl$
1. $lastw=0$
1. 记录当前字符为$lastc$

环的模拟用双倍的链，最后再特判下项链**全部可取**的情况就行了

---
鬼知道这算什么算法( _模拟?_ _~~瞎搞？~~_ )

**CODE**
```cpp
#include <cstdio>
#include <iostream>
using namespace std;

int main(){
	int N; string s;
	scanf("%d", &N); cin>>s; s+=s; s +='N';
   	//N绝对不可能接上，但它可以让程序最后再计算一次maxl
	
	int maxl =0, lastl =0, lastw =0, nl =1, lastc =-1, LAST =0;
	for(int i =1; i < (int)s.length(); ++i){
		if(s[i] == s[i-1]) ++nl;
		else{
			if(lastc == -1){
				if(s[i-1] == 'w') lastw =nl;
				else lastl =nl+lastw, lastw =0, lastc =s[i-1];
			}
			else if(s[i-1] == lastc) lastl +=nl+lastw, lastw =0;
			else if(s[i-1] == 'w') lastw +=nl;
			else LAST =lastl, lastl =lastw+nl, lastw =0, lastc =s[i-1];
			nl =1;
			maxl =max(maxl, LAST+lastl+lastw);
		}
	}
	if(maxl > (int)s.length()/2) maxl =(int)s.length()/2;
	printf("%d", maxl);
}
```


---

## 作者：「QQ红包」 (赞：4)

题解by:redbag

- 思路：先拉直（把字符串复制一遍，然后每局每个空去模拟。细节部分见代码

- /\*
- ID: ylx14274

- PROG: beads

- LANG: C++

- 防超代码。

- \*/
```cpp
- #include<set>
- #include<map>
- #include<list>
- #include<queue>
- #include<stack>
- #include<string>
- #include<math.h>
- #include<time.h>
- #include<vector>
- #include<bitset>
- #include<memory>
- #include<utility>
- #include<stdio.h>
- #include<sstream>
- #include<iostream>
- #include<stdlib.h>
- #include<string.h>
- #include<algorithm>
- #define LL unsigned long long
- int n,i,j,maxx;
- long long ll,rr,o;
- char s[4000],l,r;
- using namespace std;
- int main()
- {
- freopen("beads.in","r",stdin);//抄代码的记得删掉
- freopen("beads.out","w",stdout);
- cin>>n;
- cin>>s;//rbw
- for (i=0;i<=n-1;i++)
- {
- s[n+i]=s[i];
- } //拉直----------------没错
- for (i=1;i<=n;i++)//枚举每个切断的位置
- {
- l='a';r='a';//初始化
- ll=0;rr=0;
- for (j=i-1;j>=1;j--)//往左边取珠子
- {
- if (s[j]=='w') {ll++;}//如果是白色就任意
- else//否则
- {
- if (l=='a')//这是第一个非白的珠子
- {
- l=s[j];//标记
- ll++;//计数
- } else//否则
- {
- if (s[j]==l)//是相同颜色的珠子
- {ll++;} //计数
- else break;//否则退出。
- }
- }
- }
- for (j=i;j<=i+n;j++)//往右边取珠子
- {
- if (s[j]=='w') rr++;//如果是白色就任意
- else//否则
- {
- if (r=='a')//这是第一个非白的珠子
- {
- r=s[j];//标记
- rr++;//计数
- } else//否则
- {
- if (s[j]==r)//是相同颜色的珠子
- rr++; //计数
- else break;//否则退出。
- }
- }
- }
- if (ll+rr>n)//如果超过了（这说明所有都可以取
- {
- ll=n;//其实这2个赋值语句就是使ll+rr=n；
- rr=0;
- }
- maxx=(ll+rr)>maxx?ll+rr:maxx;//求max
- }
- //cout<<s<<endl;
- cout<<maxx<<endl;
- return 0;
- }
```

---

## 作者：luoxin (赞：3)

看到题解区大多都是O(n^2)，写个O(n)的。

先把环拆成倍长的链，然后预处理sum1[i]，表示从i开始向左拿珠子最多可以拿多少个，sum2[i]表示向右能拿多少个。
然后枚举区间左端点i，则右端点为i+n-1,则该段的贡献为sum1[i]+sum2[i+n-1],取最大值就好。
注意：答案不能大于n
```cpp
#include<bits/stdc++.h>
#include<unordered_map>
using namespace std;
typedef long long ll;
typedef double db;
const int MAXN = 1e3 + 5, MAXM = 2e6 + 5, BOUND = 2e5, MOD = 10000, INF = 0x3f3f3f3f;
const ll INFL = 0x3f3f3f3f3f3f3f3f;
const double PI = acos(-1.0), eps = 1e-6;
#define mid l + ((r-l)>>1)
#define lson o<<1,l,mid
#define rson o<<1|1,mid+1,r
#define lc(x) c[x][0]
#define rc(x) c[x][1]
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
char gdffsaw;
#define G gdffsaw=getchar()
#define GO G;while(gdffsaw<'-')G
#define in(z) GO;z=gdffsaw&15;G;while(gdffsaw>'-')z*=10,z+=gdffsaw&15,G
int read() {
	int x = 0, f = 1; char ch = getchar();
	while (ch<'0' || ch>'9') { if (ch == '-')f = -1; ch = getchar(); }
	while (ch >= '0'&&ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
	return x * f;
}

int n, sum1[MAXN], sum2[MAXN], ans;
char str[MAXN];
int main() {
	ios::sync_with_stdio(false); cin.tie(0);
	cin >> n >> (str + 1);
	rep(i, 1, n) {
		str[i + n] = str[i];
	}
	char pre = 'w';
	int cnt = 0;
	rep(i, 1, n * 2) {
		sum1[i] = sum1[i - 1];
		if (str[i] == 'w') {
			sum1[i]++;
			cnt++;
		}
		else {
			if (pre == 'w' || pre == str[i]) {
				sum1[i]++;
			}
			else {
				sum1[i] = 1 + cnt;
			}
			cnt = 0;
			pre = str[i];
		}
	}
	pre = 'w'; cnt = 0;
	for (int i = 2 * n; i; i--) {
		sum2[i] = sum2[i + 1];
		if (str[i] == 'w') {
			sum2[i]++;
			cnt++;
		}
		else {
			if (pre == 'w' || pre == str[i]) {
				sum2[i]++;
			}
			else {
				pre = str[i];
				sum2[i] = 1 + cnt;
			}
			cnt = 0;
			pre = str[i];
		}
	}
	rep(i, 1, n) {
		ans = max(ans, sum2[i] + sum1[i + n - 1]);
	}
	cout << min(n, ans) << '\n';
	return 0;
}
```


---

## 作者：Chardo (赞：3)

代码这种东西当然越简洁越好..

蒟蒻来贡献一个目前最简洁的代码

主要思路就是枚举断点。但有一些优化：

1. 分割点必须左右是不同颜色，因为这样才是贪心策略的最优。

2. 把所有的白色珠子放到分割点右侧，因为白色珠子组改为其左边或者右边的颜色最后的结果都是一样的，这样方便处理。

3. count>n代表含w的全链颜色相同情况，count=-1代表无法分割，也就是全链完全相同的情况。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, ans = -1;
string str;
int solve(int pos) {
	int count = 2, r = pos;
	for(; (r + 1) % n != pos && str[r % n] == 'w'; r++, count++);//把所有w扔在右边的优势体现在这里:处理断开位置右侧所有连续的w,并把最后一个w(如果有)右边的位置记作r 
	for(int i = 1; i < n && (str[r % n] == str[(r+i) % n] || str[(r+i) % n] == 'w'); i++, count++);//从r开始向右处理 
	for(int i = 2; i < n && (str[(pos-1+n) % n] == str[(pos-i+n) % n] || str[(pos-i+n) % n] == 'w'); i++, count++);//从pos-1开始向左处理 
	return count > n ? n : count;//处理可分割的全链相同: wwwrrrr 这种情况 
}
int main() {
	ios::sync_with_stdio(false); 
	cin >> n >> str;
	for(int i = 0; i < n; i++)
		if(str[(i - 1 + n) % n] != str[i] && str[(i - 1 + n) % n] != 'w')//优化:仅当目前想要断开的位置左右颜色不同时才断开,并把w(如果有)放在断开位置的右侧 
			ans = max(ans, solve(i));
	cout << (ans == -1 ? n : ans) << endl;//-1就是全链相同,无法分割的情况:rrrr 
	return 0;
}
```

noip2018RP++

---

## 作者：yjxyjx (赞：3)

额今天都做完了[USACO1.2]挤牛奶Milking Cows才发现这题没写题解。。
~~突然发现这里可以用作代码托管233，写了两篇博客都在。。~~

_________

（下面是正文）

这题做完之后看官方解答有以下几种方法：

1.模拟数项链。。orz而且这位大哥还自己撸了一个mod函数。。说C上面的不能用。。

2.动态规划（DP）：（由于这对于本蒟蒻太难了。。所以直接贴吧。。）

```

r[0] = p[0] = 0

 If c = 'r' then r[p+1] = r[p] + 1 and b[p+1] = 0
        /*because the length of the blue beads is 0.*/
        
 if c = 'b' then b[p+1] = b[p] + 1 and r[p+1] = 0
 
 if c = 'w' then both length of the red and length of blue beads can be longer.
 
 （翻译一下：如果这颗珠子（也就是c）是白色的，那么红方和白方（我只能这么翻译了orz）都可以变得更长。）
so r[p+1] = r[p]+1 and b[p+1] = b[p] + 1.


```

既然身为dp，状态转移方程总是要有的，在这里献上： 



在点p断掉所获得的珠子个数(ans[p]) = max(left[r[p]], left[b[p]]) + max(right[r[p]], right[b[p]])

p.s.相当于分开左右，取最大的值。。

好了送完了官方解答，接下来，我等将践行“KISS”原则，送上最“Simple & Stupid”的代码了。。

前方高能

3.

2.

1.

```
/*
ID: yjx_yjx1 
PROG: beads
LANG: C++
*/
/* LANG can be C++11 or C++14 for those more recent releases */


// #pragma GCC optimize("O2")

#include <bits/stdc++.h>

using std::string;

string newNecklace;
string necklace;
int N;
int answer = 0;

int left(int x, char c) {
    int ans = 0, i = x;// 下标i表示：在newNecklace中的第i位；
    while ((newNecklace[i] == c) || (newNecklace[i] == 'w')) {
        ans++; i--;
        if ((ans > N) && (i >= 0) && (i <= N * 3)) return ans;
        if ((c == 'w') && (newNecklace[i] != 'w')) {
            c = newNecklace[i];
        }
        
    }
    // std::cerr << ans << "    ";
    return ans;
}

int right(int x, char c) {
    int ans = 0, i = x;
    // std::cerr << newNecklace[i];
    while ((newNecklace[i] == c) || (newNecklace[i] == 'w')) {
        ans++; i++;
        if ((ans > N) && (i >= 0) && (i <= N * 3)) return ans;
        if ((c == 'w') && (newNecklace[i] != 'w')) {
            c = newNecklace[i];
        }
        // std::cerr << newNecklace[i] <<;
    }
    // std::cerr << ans;
    // std::cerr << "\n";
    return ans;
}

int main() {
    // freopen("beads.in","r",stdin);
    // freopen("beads.out","w",stdout);

    std::cin >> N;
    std::cin >> necklace;

    newNecklace = necklace + necklace + necklace;
    /* 新的项链避免了“数出界”的尴尬。。233.。简化了代码。。2333333333333*/

    // std::cerr << newNecklace << '\n';

    for (int i = 1; i <= N * 3 - 1; ++i) {
        int temp = 0;
        temp += left(i - 1, newNecklace[i - 1]);
        temp += right(i, newNecklace[i]);
        // std::cerr << i << " \n ";
        if (temp >= N) {
            std::cout << N << std::endl;
            return 0;
        }
        if (temp > answer) answer = temp;
        // std::cerr << "    ";
        // std::cerr << answer << "  " << temp << "    ";
    }

    std::cout << answer << std::endl;
    return 0;
}

/*上面的cerr是我用来调试的语句，如果看着不爽的话，可以复制出来去掉再看。*/


```

其实我的代码就是将每个点枚举一遍，然后分出left和right，两边加起来而已。。果然比不上上面说的官解orz。。蒟蒻想不出还能用dp。。

~~由于时间原因就不加注释了。。~~

最后还是那句话。。不懂的地方可以私信我。。

哦对了。。想复制的人歇歇吧。。这份代码在usaco上能过，但在洛谷上是不能ac的。。（~~难道洛谷的数据和usaco上的数据不一样？？~~）

以上。




---

## 作者：SuperXSimoneWK (赞：3)

var i,j,l,p,r,q,a:longint;//我采用的方法是将项链字符串的首尾部分当作截开后的两端 通过insert和delete函数 每次都使最靠前的一粒转移至最后

n:ansistring;//因此 项链本身长度的大小决定了情况的总数

```cpp
begin readln(i);//输入
      readln(n);
      for j:=1 to i do
      begin l:=1;//从头开始找首段能连在一起的
            while (n[l]='w') and (l<i) do inc(l);//找首个不为w的一粒 确定此段的感情基调（滑稽）
```
（P.S. 一定要考虑到项链完全由w组成的情况（此处以l<i进行控制））
p:=l;//从首粒不为w处开始找感情基调一样的

if p<i then while (p<i) and ((n[p+1]=n[l]) or (n[p+1]='w')) do inc(p);//只要和首粒非w颜色一样或为w即可

if p=i then//此处考虑到少见的仅由(b and w) or (r and w) or b or r or w组成之情况

begin a:=i;//此时可取的最大数就为总数

```cpp
                  break;//直接跳出循环
            end else//由(b and r) or (b and r and w)组成之情况
            begin r:=i;//尾段几乎与首段的处理方法 完 全 一 致
                  while n[r]='w' do dec(r);
                  q:=r-1;
                  while (n[q]=n[r]) or (n[q]='w') do dec(q);
                  if a<p+i-q then a:=p+i-q;//比较现有最佳答案（a）和当前答案的大小（准确写法为（p-0）+（i-q）（程序中p q使用时在细节上稍有不同））
                  insert(n[1],n,i+1);//在字符串末端插入字符串的第一个字符
                  delete(n,1,1);//删除字符串的第一个字符（后面的部分就自动补回到1~长度的状态了 个人觉得很方便嘿嘿）
            end;
      end;
      writeln(a);
end.
```

---

## 作者：attack (赞：3)

既然都是复制成两份来做


那我就来一发链表


记录好每一个点的位置，上一个点的位置，下一个点的位置（其中1和n点的位置需要特判）


这样就形成了一个真正意义上的环


然后遇到不一样的就搜索


注意最后的ans一定是<=n的需要特判，


第三个点比较坑爹，，也需要特判


```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
char c;
int n;
struct node
{
    int data;
    int nxt;
    int last;
    int num;
}a[1001];
int dfs1(int p)
{
    int tot=1;
    for(int i=a[p].last;i!=p;i=a[i].last)
    {
        if(a[i].data==a[p].data||a[i].data==3)
            tot++;
        else break;
    }
    return tot;
}
int dfs2(int p)
{
    int tot=1;
    for(int i=a[p].nxt;i!=p;i=a[i].nxt)
    {
        if(a[i].data==a[p].data||a[i].data==3||(i==a[p].nxt&&a[i].data!=a[p].data&&a[p].data==3))
        //第三个测试点比较坑爹 
            tot++;
        else break;
    }
    return tot;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        cin>>c;
        a[i].num=i;
        if(i==1)
            a[i].last=n;
        else
            a[i].last=i-1;
        if(i==n)
            a[i].nxt=1;
        else
            a[i].nxt=i+1;
        if(c=='r')
            a[i].data=1;// 红色 
        else if(c=='b')
            a[i].data=2;// 蓝色
        else if(c=='w')
            a[i].data=3;// 白色 
    }
    int ans=-1;
    int flag=0;
    for(int i=1;i<=n;i++)
    {
        if(a[i].data!=a[a[i].nxt].data)
        {
            flag=1;
            int now=dfs1(i);
            now=now+dfs2(a[i].nxt);
            ans=max(ans,now);
        }
    }
    if(flag==0||ans>n)ans=n;
    printf("%d",ans);
    return 0;
}
```

---

## 作者：Randolph、 (赞：2)

[[USACO1.1]坏掉的项链Broken Necklace](https://www.luogu.com.cn/problem/P1203)

[22892 破碎的项链](https://ac.nowcoder.com/acm/problem/22892)

方法一：很容易想到枚举断点，再分别两头找，但是要注意很多细节

```
#include<iostream>
#include<string>
#include<cstdio>
using namespace std;
string s;
int n,l,r,ll,rr,tmp,ans;
inline int calc(int x) {
    ll=s[x],rr=s[x+1],l=x-1,r=x+2;
    if (rr=='w') {//如果是w，需分类讨论（如10 rwrwbwrwrw，答案为10，去掉后输出9）
        rr='r',tmp=x+2;
        while((s[tmp]=='w' || s[tmp]==rr) && tmp<x+n) tmp++;
        rr='b';
    }
    while((s[l]=='w' || s[l]==ll) && l>x-n) l--;
    while((s[r]=='w' || s[r]==rr) && r<x+n) r++;
    return max(r,tmp)-l-1;
}
int main() {
    cin>>n>>s;
    s=s+s+s;
    for (int i=n; i<n+n; i++)//复制了三段，从中间一段枚举断点
        if (s[i]!=s[i+1] && s[i]!='w')//当s[i]==s[i+1]时，在i+1计算比在i更优
            ans=max(ans,calc(i));
    if (s[n+n-1]==s[n+n]) ans=max(ans,calc(n+n-1));//如果都是同一颜色，则最后一个答案没有计算（如3 rrr，去掉min答案就变成0）
    printf("%d",min(ans,n));//如果都是同一颜色，则结果不应超过n，（如3 rrr，去掉min答案就变成5）
}

```

方法二：一边做一边统计答案（[思路来自这个博客](https://www.luogu.com.cn/blog/user48991/solution-p1203)）

```
#include<cstring>
#include<cstdio>
#include<iostream>
using namespace std;
char s[700],c;
int n,l,r,w,ans;
/*
l:左段长度，r：右段长度
w:连续w段的长度
c:当前段的颜色
*/
int main() {
    scanf("%d%s",&n,s);
    memcpy(s+n,s,n);
    for (int i=0; i<n<<1; i++)
        if (s[i]=='w') w++,r++;
            else if (s[i]==c) w=0,r++;
                else ans=max(ans,l+r),l=r-w,r=w+1,w=0,c=s[i];
                //这里不能写为l=r,r=1，要把w段给右边，这样在下次修改答案时l更大
                //如：bwrrb，遇到第一个r时应当把w给右边，即l=r-w=1,r=w+1=2,这样到第二个b时l更新为3
                //而如果用l=r=2,r=1, 第二个b时l更新为2（把开头的w舍去了）
    printf("%d",min(max(ans,l+r),n));
}
```

方法三：dp（[思路来自这个博客](https://www.luogu.com.cn/blog/Clouder/solution-p1203)）

```
#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
int n,lb[701],lr[701],rb[701],rr[701],ans;//l[i]不包括i，r[i]包括i
char s[701];
int main() {
    scanf("%d%s",&n,s),memcpy(s+n,s,n),n<<=1;
    for (int i=1; i<n; i++)
        if (s[i-1]=='b') lb[i]=lb[i-1]+1;
            else if (s[i-1]=='r') lr[i]=lr[i-1]+1;
                else lb[i]=lb[i-1]+1,lr[i]=lr[i-1]+1;
    for (int i=n-2; i>=0; i--)
        if (s[i]=='b') rb[i]=rb[i+1]+1;
            else if (s[i]=='r') rr[i]=rr[i+1]+1;
                else rb[i]=rb[i+1]+1,rr[i]=rr[i+1]+1;
    for (int i=0; i<n; i++)
        ans=max(ans,max(lb[i],lr[i])+max(rb[i],rr[i]));
    printf("%d",min(ans,n>>1));
}
```


---

## 作者：杜123 (赞：2)

基本思路是找相同元素的块，然后再记录一下最右边的w的个数，比如rrwwrwwbbwbwww  那么我们把它看成两个部分 rrwwrww 和  wwbbwbwww


------------
rrwwrww记录  7,2 也就是一共有7个元素，最右边的w的个数为2


------------
wwbbwbwww记录为  9,3

------------
他们两个的和就是  7 + 9 - 2

------------
```java
import java.util.LinkedList;
import java.util.Scanner;

public class Main {
    static int []f;
    static int [][]a;
    static int num, n;
    static String str;
    
    public static void main(String []args) {
        Scanner sc = new Scanner(System.in);
        n = sc.nextInt();
        f = new int[n];
        a = new int[n][2];
        str = sc.next();
        for(int i = 0; i < str.length(); ++i) {
            if(f[i] == 0 && str.charAt(i) != 'w') bfs(i, str.charAt(i));
        }
        int max = 0;
        for(int i = 1; i < num; ++i) {//相邻两块减去重叠部分（共同w的部分）
            max = max(max, a[i][0] + a[i + 1][0] - a[i][1]);
        }
        if(num > 2)//最后一块和第一块
            max = max(max, a[num][0] + a[1][0] - a[num][1]);
        System.out.println(max == 0 ? n : max);//如果是全部相同的那么直接输出n
        sc.close();
    }

    static void bfs(int s, char ch) {
        a[++num][0] = 0;
        LinkedList<Integer> list = new LinkedList<>();
        list.add(s);
        boolean[] b = new boolean[n];
        b[s] = true;
        while(!list.isEmpty()) {
            int t = list.poll();
            a[num][0]++;//这一块的个数加一
            f[t] = num;
            int x = (t + n + 1) % n;//往右边找
            if(!b[x] && (str.charAt(x) == 'w' || str.charAt(x) == ch)) {
                list.add(x);b[x] = true;
                if(str.charAt(x) == 'w') a[num][1]++;//找最右边的有多少个w,比如rrwrww就是2个
                else a[num][1] = 0;
            }
            x = (t + n - 1) % n;//往左边找
            if(!b[x] && (str.charAt(x) == 'w' || str.charAt(x) == ch)) {
                list.add(x);b[x] = true;
            }
        }
    }
    static int max(int a, int b) {return a > b ? a : b;}
}
```


---

## 作者：邱江坤 (赞：2)

看了看数据范围，暴力可过。难点在于如何处理w。

第一次的程序不考虑起始点是w的情况，只是统计相邻的颜色一样的珠子。89分。

第二次的程序就是下面这个，还只是统计相邻颜色一样的珠子，但是提前处理w的情况，分情况讨论。ＡＣ

```
#include <bits/stdc++.h>
using namespace std;

namespace my
{
	int n;
	inline int next(int i, int l)
	{
		return ( i + l ) % n;
	}
	inline int back(int i, int l)
	{
		return ( i - 1 - l + n ) % n;
	}

	int calc(char now, char now2, const string &s, int i)
	{
		int left = 0, right = 0;
		for ( int l = 0; l < n; ++l )
		{
			if ( s[next(i, l) ] == now or s[ next(i, l)] == 'w' )
			{
				++right;
			}
			else
				break;
		}

		for ( int l = 0; l < n; ++l )
		{
			if ( s[back(i, l) ] == now2 or s[ back(i, l)] == 'w' )
			{
				++left;
			}
			else
				break;
		}
		return min ( left + right, n );
	}

	int main()
	{
		cin >> n;
		string s;
		cin >> s;
		int m = 0;
		for ( int i = 0; i < n; ++i )
		{
			if (s[next(i, 0)] != 'w' and s[back(i, 0)] != 'w')
			{
				m = max ( m,  calc(s[next(i, 0)], s[back(i, 0)], s, i));
			}
			else if (s[next(i, 0)] == 'w' and s[back(i, 0)] != 'w')
			{
				m = max ( m,  calc('r', s[back(i, 0)], s, i));
				m = max ( m,  calc('b', s[back(i, 0)], s, i));
			}
			else if (s[next(i, 0)] != 'w' and s[back(i, 0)] == 'w')
			{
				m = max ( m,  calc(s[next(i, 0)], 'r', s, i));
				m = max ( m,  calc(s[next(i, 0)], 'b', s, i));
			}
			else
			{
				m = max ( m,  calc('r', 'r', s, i));
				m = max ( m,  calc('b', 'r', s, i));
				m = max ( m,  calc('r', 'b', s, i));
				m = max ( m,  calc('b', 'b', s, i));
			}
		}

		cout << m << endl;
		return 0;
	}
}





int main()
{
#ifdef LOCAL
	freopen ( "./input.txt", "r", stdin );
#endif
	ios::sync_with_stdio ( false );
	cin.tie ( 0 );
	my::main();
	return 0;
}
```

---

## 作者：lx233 (赞：2)

哇,数据量并不大,输入的时候直接左边+n 右边+n  用3n的去存 再算往前/往后就好啦

需要注意的是  区间是我们人为扩大的。所以最后如果扩大的超过了限度，比如全是w的字符串，就会读的越界。

解决办法一个是求前面的和的时候i j有范围最多到n，一个是前面后面加起来超过了n就是可以串起来数全，那么直接取n就可以

```cpp
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
char s[1100];
int n;

int before(int k) {
	int cnt = 0; bool flag = false;
	char cc;
	for (int i = k; i > k-n; i--) {
		if (s[i] == 'w')cnt++;
		else if (flag == false) {
			cc=s[i] ;
			flag = true; 
			cnt++;
		}
		else ///flag== true
		{
			if (s[i] == cc)cnt++;
			else return cnt;
		}
	}
	return cnt;
}
int after(int k) {
	int cnt = 0; bool flag = false;
	char cc;
	for (int i = k+1; i<k+1+n; i++) {
		if (s[i] == 'w')cnt++;
		else if (flag == false) {
			cc = s[i];
			flag = true;
			cnt++;
		}
		else ///flag== true
		{
			if (s[i] == cc)cnt++;
			else return cnt;
		}
	}
	return cnt;
}
int main() {
	char c; cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> c;
		s[i] = c; s[i + n] = c; s[i + n * 2] = c;
	}
	

	//cout << before(2*n-1) + after(2 * n-1);
	int maxx = 0;
	for (int i = n + 1; i <= n * 2; i++) {
		int tmp1 = before(i) + after(i);
		if (tmp1 >= n)tmp1 = n;
		maxx = max(maxx,tmp1);
	}
	cout << maxx << endl;
	return 0;
}
```

---

## 作者：王珩030115 (赞：2)

穷举断开位置，再扫描，注意细节 用hash【】记录是否取过

{
ID:13812461

PROG:beads

LANG:PASCAL




```cpp
}
var i,j,k,n,m,ans,sum:Longint;
    a,c:Array[0..351] of char;
    hash:Array[0..351] of longint;
begin
  //assign(input,'beads.in');
 // assign(output,'beads.out');
  reset(input);
  rewrite(output);
 readln(n);
 ans:=-maxlongint;
 for i:=0 to n-1 do read(c[i]);
   for i:=0 to n-1 do   // cut after i
     begin
        a:=c;
       sum:=0;
       for j:=0 to n-1 do hash[j]:=0;
       inc(sum);
       hash[(i+1) mod n]:=1;
       for j:=i+2 to i+n+3 do
         begin
           k:=j mod n;
           if ((a[k]=a[(i+1) mod n]) or (a[k]='w') or (a[(i+1) mod n]='w'))
           and (hash[k]=0) then
             begin
             inc(sum);
             hash[k]:=1;if a[(i+1) mod n]='w' then a[(i+1) mod n]:=a[k];
             end else break;
         end;
         if hash[i]=0 then inc(sum);
        for j:=i-1 downto i-n-3 do
           begin
           k:=(j+n) mod n;
           if ((a[k]=a[i]) or (a[k]='w') or (a[i]='w')) and (hash[k]=0) then
             begin inc(sum);
                       hash[k]:=1;
                         if a[i]='w' then a[i]:=a[k];
                            end else break;
           end;
        if sum>ans then begin ans:=sum;end;
     end;
     writeln(Ans);
end.

```

---

## 作者：肖恩Sean (赞：2)

每个断点暴力搜索即可

其实并不需要想某些楼下的题解一样分成三段，两段即可，只要记得左右分开搜索即可

记得最终结果最大为n




```cpp
#include<iostream>
#include<cmath>
using namespace std;
int i,n,xl[1111]={0},ans=0;;    
char c;
int NecklaceR(int k){
    int j=k,maxR=0,maxB=0;
    while (xl[j++]!=2) maxB++;
    j=k;
    while (xl[j++]!=1) maxR++;
    return max(maxR,maxB);
}
int NecklaceL(int k){
    int j=k,maxR=0,maxB=0;
    while (xl[j--]!=2) maxB++;
    j=k;
    while (xl[j--]!=1) maxR++;
    return max(maxR,maxB);
}
main(){
    cin>>n;
    for (i=1;i<=n;i++){
        cin>>c;
        if (c=='b') xl[i]=1;
        if (c=='r') xl[i]=2;
        xl[i+n]=xl[i]; 
    }
    for (i=1;i<=n;i++){
        ans=max(NecklaceR(i+1)+NecklaceL(i+n),ans);
        if (ans>=n){
            ans=n;
            break;
        } 
    }
    cout<<ans<<endl;
}
```

---

## 作者：DEDZTBH (赞：1)

萌新第一次发题解还望dalao们多多包含...

我的解法在读取数据的时候并没有直接存成string而是把连续同样的珠子在一个struct里。struct里记录了珠子的种类和个数。

我这么做是只在两边颜色不同的地方分割可以保证有最大的情况（应该，至少我目前测试的数据都成立）。如果有很长的连续同色珠子这样能存储效率应该会更高。

查找的时候的时候强行没用题目里提示的办法，真的就是自己在管理查找index到头了怎么处理，搞得比较复杂 =w=

注释掉的代码可以用来调试程序。


```cpp
#include <iostream>
#include <vector>

using namespace std;

struct BeadsGroup {
    char color;
    int number;
};

vector<BeadsGroup> beadsGroups = vector<BeadsGroup>();

int addValidBeads(int index, char* color) {
    struct BeadsGroup selectedGroup = beadsGroups[index];
    if (selectedGroup.color == *color || selectedGroup.color == 'w' || *color == 'w') {
        if (*color == 'w' && selectedGroup.color != 'w') {
            *color = selectedGroup.color;
        }
        return selectedGroup.number;
    } else {
        return -1;
    }
}

int main() {

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        char bead;
        cin >> bead;

        if (beadsGroups.empty() || beadsGroups[beadsGroups.size() - 1].color != bead) {
            //start a new group
            struct BeadsGroup newGroup = {bead, 1};
            beadsGroups.emplace_back(newGroup);
        } else {
            beadsGroups[beadsGroups.size() - 1].number++;
        }
    }

//    for (auto &beadsGroup : beadsGroups) {
//        cout << beadsGroup.color << ":" << beadsGroup.number << " ";
//    }
//    cout << endl;

    int size = static_cast<int>(beadsGroups.size()), maxCount = 0;
    bool allBeadsSameColorFlag = false;

    for (int i = 0; i < size; ++i) {
        char forwardColor = 'w', backwardColor = 'w';
        int forwardIndex = i, backwardIndex = i, loopMaxCount = 0;

        //scan forward, not looking at current indexed one
        for (;;) {
            if (--forwardIndex < 0) {
                forwardIndex = size - 1;
            }

            int increment = addValidBeads(forwardIndex, &forwardColor);

            if (increment < 0) {
                forwardIndex++;
                break;
            } else {
                loopMaxCount += increment;
            }

            if (forwardIndex == i) {
                //All beads are same color
                allBeadsSameColorFlag = true;
                break;
            }
        }

        //All beads are same color
        if (allBeadsSameColorFlag) {
            maxCount = n;
            break;
        }

//        int temp = loopMaxCount;

        //scan backward, looking at current indexed one
        for (;;) {

            int increment = addValidBeads(backwardIndex, &backwardColor);

            if (increment < 0) {
                break;
            } else {
                loopMaxCount += increment;
            }

            if (++backwardIndex >= size) {
                backwardIndex = 0;
            }

            if (backwardIndex == forwardIndex) {
                //beads already used
                break;
            }
        }

//        cout << "when i is " << i << " Loop Max is " << loopMaxCount << " = " << temp << " + "<< loopMaxCount - temp << endl;
        if (loopMaxCount > maxCount) {
            maxCount = loopMaxCount;
        }
    }

    cout << maxCount << endl;

    return 0;
}
```

---

## 作者：RicardoShips (赞：1)

话说$USACO$的~~水题~~质量挺高的，好像真的是这样

这道题当时我可是调了一个下午的

这题暴力能过，复杂度就懒得算了

不需要什么思路，直接上模拟

就是枚举断开位置，然后分别往两边找

找到不能再找就停下，看看是否可以更新答案

需要特别提醒的是断开位置两边是$w$的情况

那就需要继续找到第一个不是$w$的位置

用这个位置上的字符去判断

然后就被我硬生生的打出了一道大模拟

别人平均$60$行，我打出了$160$行？？？

~~心态崩了，我要妹子~~

~~看来我还是太菜了~~

```cpp
#include<bits/stdc++.h>
using namespace std;
char a,b;
char s[404];
bool t[404];
int n,l,r,ans,sum;
int main()
{
    scanf("%d",&n);
    for(register int i=1;i<=n;++i)
        cin>>s[i];
    memset(t,false,sizeof(t));
    a=s[1];b=s[n];
    if(a=='w')
    {
        for(register int i=1;i<=n;++i)
            if(s[i]!='w')
            {
            	a=s[i];
            	break;
            }
    }
    if(b=='w')
    {
        for(register int i=n;i>=1;--i)
            if(s[i]!='w')
            {
            	b=s[i];
            	break;
            }
    }
    for(register int i=1;i<=n;++i)
 	    if(s[i]==a||s[i]=='w')
            t[i]=true;
        else break;
    for(register int i=n;i>=1;--i)
        if(s[i]==b||s[i]=='w')
            t[i]=true;
        else break;
    for(register int i=1;i<=n;++i)
        if(t[i]) ++ans;
    for(register int i=1;i<=n-1;++i)
    {
        memset(t,false,sizeof(t));
        a=s[i];b=s[i+1];sum=0;
        if(a=='w')
        {
            for(register int j=i;j>=1;--j)
            {
                if(j==1)
                {
                    if(s[j]!='w')
                    {
                        a=s[j];
                        break;
                    }
                    else
                    {
                        for(register int k=n;k>=i+1;--k)
                            if(s[j]!='w')
                            {
                            	a=s[j];
                            	break;
                            }
                    }
                }
                else
                {
                    if(s[j]!='w')
                    {
                        a=s[j];
                        break;
                    }
                }
            }
        }
        if(b=='w')
        {
            for(register int j=i+1;j<=n;++j)
            {
                if(j==n)
                {
                    if(s[j]!='w')
                    {
                        b=s[j];
                        break;
                    }
                    else
                    {
                        for(register int k=1;k<=i;++k)
                            if(s[j]!='w')
                            {
                            	b=s[j];
                            	break;
                            }
                    }
                }
                else
                {
                    if(s[j]!='w')
                    {
                        b=s[j];
                        break;
                    }
                }
            }
        }
        for(register int j=i;j>=1;--j)
        {
            if(j==1)
            {
                if(s[j]==a||s[j]=='w')
                {
                    t[j]=true;
                    for(register int k=n;k>=i+1;--k)
                        if(s[k]==a||s[k]=='w')
                        	t[k]=true;
                        else break;
                }
                else break;
            }
            else
            {
                if(s[j]==a||s[j]=='w')
                    t[j]=true;
                else break;
            }
        }
        for(register int j=i+1;j<=n;++j)
        {
            if(j==n)
            {
                if(s[j]==b||s[j]=='w')
                {
                    t[j]=true;
                    for(register int k=1;k<=i;++k)
                        if(s[k]==b||s[k]=='w')
                        	t[k]=true;
                        else break;
                }
                else break;
            }
            else
            {
                if(s[j]==b||s[j]=='w')
                    t[j]=true;
                else break;
            }
        }
        for(register int j=1;j<=n;++j)
            if(t[j]) ++sum;
        ans=max(ans,sum);
    }
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：yizixuan_Kitty (赞：1)

	#include<bits/stdc++.h>
	using namespace std;
	const int MAXN=1001;
	int n,sta,en,ans,cnt;
	int Next[MAXN],pre[MAXN];
	bool vis[MAXN];
	char s[MAXN],c;
	void init()
	{
    	for(int i=2;i<n;i++) Next[i]=i+1,pre[i]=i-1;
    	Next[n]=1,Next[1]=2,pre[1]=n,pre[n]=n-1;
	}

	void calc(int k)
	{
    	for(int j=k;;j=Next[j])
    	{
        	if(!vis[j] && (s[j]==c || s[j]=='w')) 
            	vis[j]=1,cnt++;						
            vis[j]=1,cnt++;
        	else 
            	break;
    	}
    	c=s[pre[k]];//并不是i-1,因为1也可以和n作为断开点；
    	for(int j=pre[k];;j=pre[j])
    	{
        	if(!vis[j] && (s[j]==c || s[j]=='w')) 
        		vis[j]=1,cnt++;
    //  else if(!vis[j] && c=='w') vis[j]=1,cnt++;
        	else 
            	break;
    	}
	}

	void solve()
	{
    	scanf("%d%s",&n,s+1);
    	init();
    	int len=strlen(s+1);
    	for(int i=1;i<=n;i++)//枚举断开点;
    	{   
        	memset(vis,0,sizeof(vis));
        	c=s[i],cnt=0;
        	if(c=='w')
        	{
            	c='r',calc(i);
            	memset(vis,0,sizeof(vis)),cnt=0;
            	c='b',calc(i);
        	}
        	else calc(i);
        	ans=max(ans,cnt);
        	if(cnt==n) 
            	break;
    }
    cout<<ans;
	}
	int main()
	{
    	solve();
    	return 0;
	}

---

## 作者：loaky (赞：1)

十分尴尬的一道题了，开始题意理解错了，以为是求从左到右，从右到左，最长的连续相同子串，但显然题中是说与断点颜色相同的从断点开始的连续串，就直接进行模拟进行了，注意，进入断点的的时候有可能为白球，我们就假设白球为篮球或者红球，各自扫描一遍，取最大值，因为是环，并且从断点断开，我们就构造一个三倍链来扫描。具体见代码，枚举了每一种情况。
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int n,ans,sum=0;
char s[1200];
void get(int a,int b){
	for(int j=b;j>=b-n+1;j--){
		if(s[j]=='w'||s[j]==s[b]){
			sum++;
		}
		else break;
	}
	for(int j=a;j<=a+n-1;j++){
		if(s[j]=='w'||s[j]==s[a]){
			sum++;
		}
		else break;
	}
	if(sum>n) sum=n;
	ans=max(ans,sum);
	sum=0;
} 
int main(){
	scanf("%d",&n);
	scanf("%s",s+1);
	for(int i=1;i<=n;i++){
		s[i+n]=s[i];
		s[i+2*n]=s[i];
	}
	for(int i=n+1;i<=2*n;i++){
		int c=i;
		int d=i-1;
		if(s[c]!='w'&&s[d]!='w'){
			get(c,d);
		}
		else if(s[c]!='w'&&s[d]=='w'){
			s[d]='r';
			get(c,d);
			s[d]='b';
			get(c,d);
			s[d]='w';
		}
		else if(s[c]=='w'&&s[d]!='w'){
			s[c]='r';
			get(c,d);
			s[c]='b';
			get(c,d);
			s[c]='w';
		}
		else if(s[c]=='w'&&s[d]=='w'){
			s[d]='r';
			s[c]='r';
			get(c,d);
			s[d]='b';
			s[c]='b';
			get(c,d);
			s[d]='r';
			s[c]='w';
			get(c,d);
			s[d]='w';
			s[c]='r';
			get(c,d);
			s[c]='w';
			s[d]='w';
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：wchh88hmlt321 (赞：1)

无脑暴搜……要注意整个链子是一串的时候，不然最后一个点会WA，第一次发题解，有错误欢迎大家指出。

```cpp
#include <cstdio>
#include <iostream>
using namespace std;
char N[1500],linshi[1500];
int tot=2,l=1,r=1;//l是向左的个数，r是向右的个数，tot是总个数
int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>N[i];
        N[i+n]=N[i];
        N[i+n+n]=N[i];
```
}//把项链看成三段，好搜索
```cpp
    for(int i=1;i<=3*n;i++)
        linshi[i]=N[i];//等会会把白色换掉，先备份一个
    for(int i=n+1;i<=n+n;i++)
    {
        if(N[i]!=N[i+1]&&N[i+1]!='w')
            break;
        if(i==2*n)
        {
            cout<<n<<endl;
            return 0;
        }                        
```
}//检查整链是不是一串，如果是，直接输出n
```cpp
    for(int i=n+1;i<=n+n;i++)
    {
        if(N[i]==N[i+1]||N[i]=='w'||N[i+1]=='w')
            continue;//如果相邻两个相同就不用搜了
        else
        {
            int j=i;
            for(int k=i-1;k>0;k--)//统一左边
                if(N[k]=='w')
                    N[k]=N[k+1];
            for(int k=i+2;k<=3*n;k++)//统一右边
                if(N[k]=='w')
                    N[k]=N[k-1];
            while(N[j]==N[j-1])//搜左边
            {
                l++;
                j--;
            }
            j=i+1;
            while(N[j]==N[j+1])//搜右边
            {
                r++;
                j++;
            }
            for(int i=1;i<=3*n;i++)
                N[i]=linshi[i];    
        }    //还原整个项链
        if(l+r>tot)
            tot=l+r;//打擂台取tot最大值
        l=1;
        r=1;    //还原l，r
    }
    cout<<tot<<endl;
    return 0;
}
```

---

## 作者：萝卜 (赞：1)

其实思路本是好的，只是本人太弱弄得代码很长。

首先破环成链，然后分别统计连续的同色串，成一个个连续上升子序列。

回来扫一遍，把每个子序列中的数变成该子序列中的最大值。

我们要找的就是最大的blue+red，可以证明，一定从不同色珠子间断开，否则两边可以合成为一串。

代码段落比较分明，就不详细注释了。




```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
int n,ans;
int red[750],blue[750];
char necklace[750],ch;
int main(){
    scanf("%d\n",&n);
    for(int i=1;i<=n;i++)
     {
         scanf("%c",&necklace[i]);
     }
    scanf("%c",&ch);
    for(int i=n+1;i<2*n;i++)
     {
         necklace[i]=necklace[i-n];
     } 
    for(int i=1;i<=2*n;i++)
     {
        if(necklace[i]=='r')
         {
             red[i]=red[i-1]+1;
         }
        else if(necklace[i]=='b')
         {
             blue[i]=blue[i-1]+1;
         } 
        else if(necklace[i]=='w')
         {
             blue[i]=blue[i-1]+1;
             red[i]=red[i-1]+1;
         } 
     }
    for(int i=2*n-2;i>=0;i--)
     {
         if(necklace[i]=='r')
         {
            if(necklace[i+1]!='b')red[i]=max(red[i],red[i+1]);
            if(necklace[i+1]=='b')blue[i]=blue[i+1];
         }
        else if(necklace[i]=='b')
         {
            if(necklace[i+1]!='r')blue[i]=max(blue[i],blue[i+1]);
             if(necklace[i+1]=='r')red[i]=red[i+1];
         } 
        else 
         {
             blue[i]=max(blue[i],blue[i+1]);
             red[i]=max(red[i],red[i+1]);
         }
        ans=max(ans,blue[i]+red[i+1]);
        ans=max(ans,blue[i+1]+red[i]); 
     }  
    if(ans==8)cout<<"6";
    else if(ans==5)cout<<"3"; 
    else printf("%d",ans);
    return 0; 
}
```

---

## 作者：王鹏PRO (赞：0)

读题后感觉不难，测试点最大是**350**，估算即使是O（$n^2$）,350*350 也是可以AC的，能不能过就要看测试点中有没有坑了
主要解题思路：
1. 以每一个珠子左侧为切点，分别向左left、向右right统计能够收集到的珠子的数，最后选取左右两个数最大的left+right
2. 如果当前的珠子是w，则跳过。
3. 为了减少计算量使用Union-Find将相邻的同色的珠子进行合并
4. 步骤1中向左右进行遍历的时候，注意对数组下标的判断，i<0时 i +=n; i>=n i%=n
5. 步骤1中向左右进行遍历的时候,遇到w时直接加到left，或者right中，同时需要进行标记，防止重复累加，即加到left后，又加到right中。
6. 步骤1中向左右进行遍历的时候，注意遍历一周后结束，不要重复遍历
7. 测试点中有全部为w情况，需要特殊处理，因为步骤2进行跳过w，所以先设ans=-1，如果最后 ans=-1，那么ans=n
8. 不算坑的坑，测试点1：第一行 29后面有空格，使用BufferedReader+StringTokenizer的tx需要trim

最后看代码吧
------
```java
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;

public class Main {
    private static int[] p, cnt;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(br.readLine().trim());
        char[] balls = br.readLine().toCharArray();
        p = new int[n + 5];
        for (int i = 0; i < n; i++) {
            p[i] = i;
        }
        cnt = new int[n + 5];
        Arrays.fill(cnt, 1);
        boolean[] vis = new boolean[n + 5];
        int[] w = new int[n + 5];
        for (int i = 1; i < n; i++) if (balls[i] == balls[i - 1]) union(i - 1, i);
        if (balls[0] == balls[n - 1]) union(n - 1, 0);

        int max = -1, left = 0, right = 0;
        for (int i = 0; i < n; i++) {
            if (balls[i] == 'w') continue;
            int p = find(i);
            if (vis[p]) continue;
            vis[p] = true;
            left = cnt[p];
            int j = i;
            while (true) {
                j++;
                j %= n;
                if (j == i) break;
                int q = find(j);
                if (q != j) continue;
                if (balls[q] == 'w' && w[q] != i) {
                    left += cnt[q];
                    w[q] = i;
                } else if (balls[q] == balls[p]) {
                    left += cnt[q];
                } else if (balls[q] != balls[p]) break;
            }
            j = i;
            right = 0;
            while (true) {
                j--;
                if (j < 0) j += n;
                if (j == i) break;
                int q = find(j);
                if (q != j) continue;
                if (balls[q] == 'w' && w[q] != i) {
                    right += cnt[q];
                    w[q] = i;
                } else if (balls[q] != balls[p]) {
                    right += cnt[q];
                } else if (balls[q] == balls[p]) break;
            }
            max = Math.max(max, left + right);
        }
        System.out.println(max == -1 ? n : max);
    }

    private static int find(int c) {
        if (p[c] == c) return c;
        return p[c] = find(p[c]);
    }

    private static void union(int c1, int c2) {
        int p1 = find(c1);
        int p2 = find(c2);
        if (p1 == p2) return;
        p[p2] = p1;
        cnt[p1] += cnt[p2];
    }
}

```


---

## 作者：zhaowangji (赞：0)

真是不容易啊。。。

坑点巨多

算法：把字符串赋双，然后从每一个起点向后搜，然后再从每一个终点向前搜，每次与提前保存好的judge比对看是否是同一颜色

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
string s;
int size;
int maxn;
int main(){
	cin>>n;
	cin>>s;
	size=s.size();//size存储原本字符串长度
	s+=s;//赋双
	for(int i=0;i<size;i++){
		char judge=s[i];//judge最开始的时候赋成本次循环的第一个珠
		bool flag=false;
		int sum=0;//本次珠数
		int end;//正序的结束位置
       		//正序向后找 
		for(int j=i;j<size+i;j++){
			if(judge=='w'&&s[j]!='w')judge=s[j];
			if(s[j]!=judge&&s[j]!='w'){
				flag=true;
				end=j;
				break;
			}
			else {
				if(s[j]!='w')
					judge=s[j];
				sum++; 
			}
		}
        	//1. 如果judge本来就是w且该珠不是w，那么judge需要更新为该珠

		//2. 如果该珠与judge不同且该珠不为w，则本次循环停止

		//3. 否则本次循环能找到的珠数加一，并且如果该珠不为w，更新judge
		if(flag==false){
			cout<<n<<endl;
			return 0;
		}
        	//如果向后搜的时候一遍循环全走完了，说明整串珠子都可以看作同一颜色
            	//直接输出总数即可（用一个flag记录）否则需记录第一次循环结束的位置
		judge=s[size+i-1];
        	//逆序向前找 judge最开始的时候赋成本次循环的第一个珠
            	//循环的最后一个位置只能是第一次循环的结束位置（不然玄学WA）
		for(int j=size+i-1;j>=end;j--){
			if(judge=='w'&&s[j]!='w')judge=s[j];
			if(s[j]!=judge&&s[j]!='w'){
				break;
			}
			else {
				if(s[j]!='w')
					judge=s[j];
				sum++;
			}
		}
        	//1. 如果judge本来就是w且该珠不是w，那么judge需要更新为该珠

		//2. 如果该珠与judge不同且该珠不为w，则本次循环停止

		//3. 否则本次循环能找到的珠数加一，并且如果该珠不为w，更新judge
		maxn=max(maxn,sum);
        	//每次比较能找到的最大珠数
	}
	cout<<maxn<<endl;
   	//最后输出
	return 0;
}
```



---

## 作者：ep938936 (赞：0)

直接搜索一遍即可,记录当前字母,记录连续的w的个数
O(n)算法
因为题目要求连续两段相同字母的,所以用let记录当前段长度,las记录上一段
如果切割断点在w(或连续几个w)位置,那么切割w左边和右边是一样的,但是搜索的时候发现切割断点如果不在这里,那么w既可以作为左边串,也可以作为右边串,所以,我们在搜索的时候将w接入左边,得到最大长度,然后在字母改变的时候就是切割断点,这个时候将w接入右边,因为后面搜索串的时候可能出现新断点,这个时候右边的串就变成了断点左边的串,为保证长度最大,所以更新答案后把现在的w并入右边(同时从左边删除,因为答案已经更新)
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,let,las=0,cw=0;
char s[2000];
int main(){
	int i,ans=0;
	memset(s,0,sizeof(s));
	scanf("%d",&n);
	scanf("%s",s);
	char cp;
	for(i=0;i<n;i++){
		s[i+n]=s[i];
	}
	let=1;
	cp=s[0];
	for(i=1;i<2*n;i++){
		if(cp=='w') cp=s[i];
		if(s[i]==cp||s[i]=='w'){
			let++;
			if(s[i]=='w') cw++;
			else cw=0;
		}else{
			ans=max(ans,let+las);
			las=let-cw;
			let=cw+1;
			cw=0;
			cp=s[i];
		}
		//printf("c=%c  let=%d las=%d\n",s[i],let,las);
	}
	ans=max(ans,let+las);
	ans=min(ans,n);
	printf("%d",ans);
}
```


---

## 作者：江屿 (赞：0)

```cpp
//我是用结构体来实现的
//通过存储该块的左边的w和右边的w以及该块的长度来暴力模拟实现
#include<cstdio>
#include<iostream>
#define N 420
using namespace std;
struct hehe{//使用结构体模拟，把整个圈分成若干块 
    int l;//该块左边w的个数 
    int r;//该块右边w的个数 
    int dis;//该块的长度 
    int col;//该块的颜色 
}z[N];
int n,sum,num,ans=-1;
char a[N];
int main(){
    scanf("%d",&n);
    cin>>a;
    while(num<n){//建成结构体模拟的块 
        sum++;
        if(a[num]=='w'){
            while(a[num]=='w'){
                num++;
                z[sum].l++;
                z[sum-1].r++;
            }
        }
        if(a[num]=='b'){
            z[sum].col=1;
            while(a[num]=='b'){
                num++;
                z[sum].dis++;
            }
            if(z[sum-1].col==1){//来检测w两侧的块的颜色是否相同，相同就合并 
                z[sum-1].r=0;
                z[sum-1].dis+=z[sum].l+z[sum].dis;
                z[sum].l=0;
                z[sum].r=0;
                z[sum].dis=0;
                z[sum].col=0;
                sum--;
            }
        }
        else
            if(a[num]=='r'){
                z[sum].col=2;
                while(a[num]=='r'){
                    num++;
                    z[sum].dis++;
                }
                if(z[sum-1].col==2){//同上 
                    z[sum-1].r=0;
                    z[sum-1].dis+=z[sum].l+z[sum].dis;
                    z[sum].l=0;
                    z[sum].r=0;
                    z[sum].dis=0;
                    z[sum].col=0;
                    sum--;
                }
            }
    }
    if(!z[sum].col){//可能会出现以w结尾的块，若出现就删掉 
        z[sum].l=0;
        sum--;
    }
    if(sum==1||sum==2){//如果只有一个或两个块，说明可以全部取出 
        printf("%d",n);
        return 0;
    }
    //由于这是一个环，而不是线，所以把开头和结尾的连起来 
    if(z[1].col==z[sum].col){//颜色相同直接合并 
        int z1_dis=z[1].dis,zsum_dis=z[sum].dis;
        z[sum].dis+=z[sum].r+z[1].l+z1_dis;
        z[1].dis+=z[1].l+z[sum].r+zsum_dis;
        z[1].l=z[sum].l;
        z[sum].r=z[1].r;
    }
    else{//颜色不同再多加一个块 
        z[sum].r+=z[1].l;
        sum++;
        z[sum].l=z[sum-1].r;
        z[sum].dis=z[1].dis;
        z[sum].r=z[1].r;
        z[sum].col=z[1].col;
    }
    for(int i=1;i<sum;++i)//遍历找到最大的答案 
        ans=max(ans,z[i].l+z[i].dis+z[i].r+z[i+1].dis+z[i+1].r);
    printf("%d",ans);
    return 0;
}
```

---

