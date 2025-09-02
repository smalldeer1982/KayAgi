# Rowena Ravenclaw's Diadem

## 题目描述

Harry, upon inquiring Helena Ravenclaw's ghost, came to know that she told Tom Riddle or You-know-who about Rowena Ravenclaw's diadem and that he stole it from her.

Harry thought that Riddle would have assumed that he was the only one to discover the Room of Requirement and thus, would have hidden it there. So Harry is trying to get inside the Room of Requirement to destroy the diadem as he knows that it is a horcrux.

But he has to answer a puzzle in order to enter the room. He is given $ n $ objects, numbered from $ 1 $ to $ n $ . Some of the objects have a parent object, that has a lesser number. Formally, object $ i $ may have a parent object $ parent_{i} $ such that $ parent_{i}&lt;i $ .

There is also a type associated with each parent relation, it can be either of type $ 1 $ or type $ 2 $ . Type $ 1 $ relation means that the child object is like a special case of the parent object. Type $ 2 $ relation means that the second object is always a part of the first object and all its special cases.

Note that if an object $ b $ is a special case of object $ a $ , and $ c $ is a special case of object $ b $ , then $ c $ is considered to be a special case of object $ a $ as well. The same holds for parts: if object $ b $ is a part of $ a $ , and object $ c $ is a part of $ b $ , then we say that object $ c $ is a part of $ a $ . Also note, that if object $ b $ is a part of $ a $ , and object $ c $ is a special case of $ a $ , then $ b $ is a part of $ c $ as well.

An object is considered to be neither a part of itself nor a special case of itself.

Now, Harry has to answer two type of queries:

- 1 u v: he needs to tell if object $ v $ is a special case of object $ u $ .
- 2 u v: he needs to tell if object $ v $ is a part of object $ u $ .

## 说明/提示

In test case $ 1 $ , as object $ 2 $ is a special case of object $ 1 $ and object $ 3 $ is a special case of object $ 2 $ , this makes object $ 3 $ a special case of object $ 1 $ .

In test case $ 2 $ , as object $ 2 $ is a special case of object $ 1 $ and object $ 1 $ has object $ 3 $ , this will mean that object $ 2 $ will also have object $ 3 $ . This is because when a general case (object $ 1 $ ) has object $ 3 $ , its special case (object $ 2 $ ) will definitely have object $ 3 $ .

## 样例 #1

### 输入

```
3
-1 -1
1 0
2 0
2
1 1 3
2 1 3
```

### 输出

```
YES
NO
```

## 样例 #2

### 输入

```
3
-1 -1
1 0
1 1
2
2 2 3
2 3 2
```

### 输出

```
YES
NO
```

# 题解

## 作者：Error_Eric (赞：1)

### 题意

~~我之前翻译的是个什么玩意.jpg~~

~~为啥这道题没人做.jpg~~

其实翻译成人话就是 给定一个边权为 $0,1$ 的森林和若干个询问，每个询问有两种形式:

1. $u$ 是否是 $v$ 的祖先且 $u,v$ 之间的路径全为 $0$。

2. $u,v$ 是否满足 $u-lca(u,v)$ 的路径全 $0$ 且 $v-lca(u,v)$ 的路径全 $1$。

~~但是题面不能翻译成这样因为这是 tutorial 里面的。~~

特殊地，不认为自己是自己的祖先，但是 $lca(u,v)$ 可能是 $u$。

认为自己到自己的路径是全 $0$ 的路径。

2500 分至少 500 分是阅读理解分。

### Sol

知道了题意解法就很多了。

比如树剖，倍增。

我采用的实现方式是倍增 lca +链上差分。 具体地，在 dfs 的过程中求出根节点到每个节点的路径权值和记录为 $s$。然后若 $s_u=s_v$ 可以判断为全 $0$ 路径，若 $s_u-s_v=d_u-d_v$ （这里 d 是深度） 则可以判断为全 $1$ 的路径。更加具体的细节实现在代码中以注释的形式给出。

CF 的标程是并查集+倍增 lca+树上 dp 预处理。

还可以树链剖分用 st 表/线段树/前缀和预处理之类之类的。

### Code

```cpp
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<vector>
using namespace std;
const int _=1e5+5;
int n,u,v,a,t,q,d[_],s[_],f[_][20];
vector<int>son[_],rts;
void dfs(int o){ // lca 的 dfs，其中 s 是路径前缀和
    for(int i=1;i<20;i++)
        f[o][i]=f[f[o][i-1]][i-1];
    for(int to:son[o]) 
        d[to]=d[o]+1,s[to]+=s[o],dfs(to);
}
int lca(int x,int y){
    if(f[x][19]^f[y][19]) return -1;
    // 如果两个节点不存在 lca 那么说明不在同一棵子树。 (所以并查集完全没有必要)
    if(d[x]>d[y]) swap(x,y);
    for(int i=19;i>=0;i--)
        if(d[x]<=d[f[y][i]]) y=f[y][i];
    if(x==y) return x;
    for(int i=19;i>=0;i--)
        if(f[x][i]^f[y][i]) x=f[x][i],y=f[y][i];
    return f[x][0];// 以上 lca 板子
}
bool all0(int x,int y){// x--y 的路径上全是 0
    return s[x]==s[y];
}
bool all1(int x,int y){// x--y 的路径上全是 1
    return (s[x]-s[y]==d[x]-d[y])&&(x^y);
}
//注意这里判断的前提是 x 是 y 的祖先或者 y 是 x 的祖先。
int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>u>>v;
        if(u==-1&&v==-1) rts.push_back(i),f[i][0]=i;
        else f[i][0]=u,s[i]=v,son[u].push_back(i);
    }
    for(int rt:rts) dfs(rt);
    cin>>q;
    while (q--){
        cin>>t>>u>>v,a=lca(u,v);
        if(u^v&&a!=-1){
        // 如果 u 和 v 相等或者不在同一个联通块答案必然是 no
            if(t==1)//详见 sol 部分
                puts(a==u     &&all0(v,a)?"YES":"NO");
            else 
                puts(all0(u,a)&&all1(v,a)?"YES":"NO");
        }
        else puts("NO");
    }
}
```

---

