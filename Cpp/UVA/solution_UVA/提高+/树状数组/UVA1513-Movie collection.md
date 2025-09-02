# Movie collection

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=448&page=show_problem&problem=4259

[PDF](https://uva.onlinejudge.org/external/15/p1513.pdf)

# 题解

## 作者：张鑫杰 (赞：7)

中文题目描述

KI先生有收集大量小电影的习惯, 他把他的珍藏理成一大摞。无论何时他想观看这一些电影的一部,他从这一摞电影中找出这一部电影,小心地将其拿出,以确保这一摞电影不会倒塌.

自从那一摞电影变得越来越大,他需要跟踪每一部电影的位置.或许了解每一部电影上面有多少部电影,就足以根据这些信息计算出其在这一摞电影中的位置.由一个印在电影盒子上的数字,可以识别出每一部电影.

那么你的任务就是编写一个跟踪每一部电影位置的程序,特别的,当KI先生从这一摞电影中拿出一部时,你的程序必须打印出在这一部即将被拿出的电影上面电影的数目.

输入

第一行是一个正整数：输入数据的数量(<=100),之后每一个测试数据,一行上是两个整数n,m, (1 ≤ n, m ≤ 100000),他们表示这一摞电影的数量和电影查询请求的数量.另一行是有m个整数, a1, . . . , am (1 ≤ ai ≤ n),他们表示KI先生想看的电影,它们需要你去查询定位.

为了简单起见,假设这一摞电影的编号1,2……n按顺序增加,其中这一摞电影最上面的是1号电影.

输出

每一组数据,输出一行整数, 其中第i个整数给出ai号电影在被拿出之前上方的电影的数目。请注意,在每次查询请求ai之后,ai号电影会被放在这一摞电影的顶部

分析,我首先想到这一道题可以用树状数组做.然而,拿出一本书然后置于顶部这一点实现相对困难,于是我想了一个办法.

首先,我另外用pos数组保存倒序排列的位置(便于更新),该部分的代码:

```cpp
update(pos[p],-1);//从该区间删除这本电影
pos[p]=++cur;//为了防止移动数据,我们把电影放在倒数第一,而避免移动
update(pos[p],1);//放入这本书
```
该代码的原理是如下所示:
![](https://cdn.luogu.com.cn/upload/pic/37055.png)
![](https://cdn.luogu.com.cn/upload/pic/37056.png)
![](https://cdn.luogu.com.cn/upload/pic/37057.png)
注意,pos中储存的位置是倒序的

我把我的思路写在注释里了,应该足够详细了.

```cpp
#include<bits/stdc++.h>
#define ini(x,y) memset(x,y,sizeof(x))
#define all(x) x.begin(),x.end()
#define F(x,y,z) for(int x=y;x<=z;++x)
#define D(x,y,z) for(int x=y;x>=z;--x)
#define cint const int&
using namespace std;
/*请以C++11提交,Develop By ZhangXinjie（江南柚子）*/
const int MAXN=static_cast<int>(1e5)+100;
const long long INF=0x3f3f3f3f3f3f3f3f;
const int oo=0x3f3f3f3f;
#define int long long
inline int read(){
    int x = 0, y = 1, c = getchar();
    while (c>'9' || c<'0') { if (c == '-')y = -1; c = getchar(); }
    while (c >= '0'&&c <= '9') { x = x * 10 + c - '0'; c = getchar(); }
    return x * y;
}//快速读入
static int tree[MAXN<<1],pos[MAXN],n,m;
//tree即为树状数组,为什么要开两倍>别急,我后面会讲到
//pos[i]表示第i本电影在树状数组的位置
inline int lowbit(int x){
    return x&(-x);//重点,一定要加括号,否则会WA,注意啊!QAQ!
}
inline void update(int x,int k){
    for(int i=x;i<=(MAXN<<1)-10;i+=lowbit(i)){
        tree[i]+=k;//update操作,树状数组必备
    }
}
inline int sum(int x){
    int ret=0;
    for(int i=x;i>0;i-=lowbit(i)){
        ret+=tree[i];//求和操作,还是树状数组标配
    }
    return ret;
}
signed main(){
    int T=read();//读入测试点个数
    while(T--){
        n=read();
        m=read();
        ini(tree,0);//每次都要初始化
        ini(pos,0);
        /*为了方便操作,树状数组的sum得出在它以及之后电影的数量*/
        F(i,1,n){
            pos[i]=n-i+1;//由于是在它之后电影的数量,而sum函数是向前计算,所以我们储存着倒数第几(倒数第n即为第一)
            update(pos[i],1);//在该位置单点插入一本书
        }
        int cur=n;
        int first=true;//防止输出多余' ',UVA对于这有时很敏感啊QAQ.
        F(i,1,m){
            int p=read();//要拿出的电影
            if(first){
                first=false;
            }else{
                printf(" ");
            }
            printf("%lld",n-sum(pos[p]));//n-它以及在它之后的书=在它之前的书
            update(pos[p],-1);//从该区间删除这本电影
            pos[p]=++cur;//为了防止移动数据,我们把电影放在倒数第一,而避免移动
            update(pos[p],1);//放入这本书
        }
        printf("\n");//别忘了
    }
    return 0;
}

```

---

