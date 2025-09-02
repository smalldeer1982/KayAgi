# Corporative Network

## 题目描述

有 $N$ 个结点，初始时每个结点的父结点都不存在。你的任务是执行一次 $I$ 操作和 $E$ 操作，格式如下：  
- $I\ u\ v$：把结点 $u$ 的父结点设为 $v$，距离为 $|u-v| \bmod 1000$。输入保证执行指令前 $u$ 没有父结点。  
- $E\ u$：询问 $u$ 到根节点的距离。

## 样例 #1

### 输入

```
1
4
E 3
I 3 1
E 3
I 1 2
E 3
I 2 4
E 3
O
```

### 输出

```
0
2
3
5
```

# 题解

## 作者：封禁用户 (赞：9)

标 签 凉 心

### 前言

看到并查集的标签才点进来的，结果是模拟并查集的题（

~~嗯没错，我的社区分岌岌可危，所以来水篇题解。~~

### 具体做法

因为我们要记录节点点$x$ 的所有祖先，所以不能用并查集，只好用数组模拟了……

对于每次$\mathtt{I}$ 操作：

将两个节点的父子关系用 father 数组记录。


对于每次$\mathtt{E}$ 操作：

运用 father 数组中的值遍历节点$x$ 的所有祖先，计算值。

P.S.注意取模。

### $\mathtt{Code}$

```cpp
#include<cstdio>
#include<iostream>
#include<math.h>
using namespace std;
int father[20005],n,t;
char ch;
int main()
{
    int x,y;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
            father[i]=i;//初始化
        while(cin>>ch&&ch!='O')
        {
            if(ch=='I')
            {
                scanf("%d%d",&x,&y);
                father[x]=y;//记录父子关系
            }
            else
            {
                scanf("%d",&x);
                int ans=0;//ans初值为0
                for(int i=x;i!=father[i];i=father[i])//遍历每个祖先，已经是根节点了就停止
                    ans+=(abs(i-father[i])%1000);//计算绝对值
                printf("%d\n",ans);//输出答案
            }
        }
    }
    return 0;
}
```



---

## 作者：CaiXY06 (赞：6)

## 题意

维护一个类似并查集的数据结构，支持修改父节点和查询子节点与根节点的距离。

## Solution

子节点与父节点间的距离为 $|u-v|$ , $u$ 与 $v$ 分别为两点编号。那么子节点与根节点的距离就为子节点 $x$ 一层一层往父节点跳，并计算,根节点的父节点就是自己。其余我们只要按题意模拟即可。

$$Ans= \sum\limits_{x=fa_x}^{fa_x\neq x} |x-fa_x| $$

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1000;
int T,n,fa[20010];
char c;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++)fa[i]=i;//初始化
		while(cin>>c&&c!='O'){
			int x,y=0;
			if(c=='I'){
				scanf("%d%d",&x,&y);
				fa[x]=y;
			}
			else{
				scanf("%d",&x);
				while(x!=fa[x]){
					y+=abs(x-fa[x])%mod;
					x=fa[x];//一层一层往上跳
				}
				printf("%d\n",y);
			}
		}
	}
	return 0;
}
```


---

## 作者：多米 (赞：4)

这一题其实很（~~水~~）简单，

只不过靠你的就是你的思想

![基本思想](https://www.luogu.org/app/upload)

由此得知

所以，需要一个 d 数组来维持距离

```
d[x]=abs(x-y)%1000;
```

如果要进行并查集，必须初始化
```
for(int i=1;i<=n;i++)
{
	fa[i]=i;
	d[i]=0;
}
```
接下来，我们需要一个寻找 father 的函数

```
int father(int o)
{
	if(fa[o]!=o)
	{
		int k=father(fa[o]);
		d[o]+=d[fa[o]];
		return fa[o]=k;
	}
	return o;
}
```

所以给出你们梦寐以求的全带码，（~~不许复制~~）

```
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>// 

using namespace std;

const int maxn=20000+10;

int fa[maxn],d[maxn];
// d 数组用来存放从点到 root 的距离，fa 是父亲 

int father(int o)
{
	if(fa[o]!=o)
	{
		int k=father(fa[o]);
		d[o]+=d[fa[o]];// 核心语句，整个并查集就多这一个 
		
		return fa[o]=k;
	}
	// else 
	return o;
}


int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		int n,x,y;
		string s;
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			fa[i]=i;
			d[i]=0;
		}// 初始化并查集 
		while(cin>>s&&s[0]!='O')
		{
			if(s[0]=='E')
			{
				cin>>x;
				father(x);
				cout<<d[x]<<endl;
			}
			else
			{
				cin>>x>>y;
				fa[x]=fa[y];
				d[x]=abs(x-y)%1000;// 千万要膜一下 QWQ 
			}
		}
	}
	return 0;
}
```

---

## 作者：mafengfa (赞：3)

### 这道题是经典的权值并查集，可是题解都是写的模拟的解法。


所以我写一个用权值路径压缩的解法，稍微优化一下，就拿到了这道题的最优解（30ms），模拟基本上需要1s以上的时间。

捎带提一句，这道题如果数据强一点的话，模拟是过不了的。

首先我们可以发现，这道题显然需要维护一个并查集，但是和以往并查集不一样的是，我们还需要维护它与根节点的 **距离** 。

使用模拟的话，方法很简单，就是每次寻找父节点的递归过程中，把沿途路径的权值都加起来。

我们加快并查集的最重要的手段就是路径压缩，但是因为这道题有距离的要求，是不能随便压缩的。这道题事实上用不压缩的并查集依然可以AC。

但是路径压缩可以加速，我们也仅仅需要维护一个表示它与根节点的距离的数组 $d$  即可，每个结点到根节点的距离为 $d[i]$。

具体细节可以看代码：

```c
#include<stdio.h>
#include<math.h>

#define maxn 20005

int f[maxn],d[maxn];
int n,T,u,v,i;
int getf(int a){ //路径压缩，同时维护数组
  if(f[a]==a)return a;
  else{
    int root = getf(f[a]);
    d[a] = (d[f[a]] + d[a]);
    return f[a] = root;
  }
}
int main(){
  scanf("%d",&T);
  while(T--){
    scanf("%d",&n);
    for(i=1;i<=n;i++){f[i] = i;d[i] = 0;}
    char s[2];
    while(scanf("%s",s)){
      if(s[0]=='O')break;
      if(s[0]=='I'){
        scanf("%d%d",&u,&v);
        d[u] = abs(u-v)%1000;f[u] = v;
      }else {
        scanf("%d",&u);getf(u);
        printf("%d\n",d[u]);
      }
    }
  }
}
```



---

## 作者：rxzfn (赞：3)

# 这题纯模拟竟然可以过！！！
下面给出模拟的做法：
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
int T,n,f[20001];
int fabs(int x)//求绝对值
{
	if(x<0)
		return -x;
	else return x;
}
int main()
{
	int i,u,v,ans;
	char ch;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		memset(f,0,sizeof(f));//f数组记录父亲
		while(scanf("%c",&ch))
		{
			if(ch=='O')
				break;
			if(ch=='I')
			{
				scanf("%d%d",&u,&v);
				f[u]=v;//只要记录就行了，无需其余操作
			}
			else if(ch=='E')
			{
				scanf("%d",&u);
				ans=0;
				while(f[u])//如果有父亲
				{
					ans+=fabs(f[u]-u)%1000;//计算
					u=f[u];//更新到父亲
				}
				cout<<ans<<endl;
			}
		}
	}
	return 0;
}
```
至于优化什么的，下面都有，我在这里就不讲了

---

## 作者：FanYongchen (赞：1)


看到别的大佬说不能用[并查集](https://baike.baidu.com/item/%E5%B9%B6%E6%9F%A5%E9%9B%86/9388442?fr=aladdin)，可我想，也不是不能用。

用 $fa[i]$ 记录第 $i$ 个节点的父亲节点。

用 $dis[i]$ 记录第 $i$ 个节点与父亲节点的距离。

然后，不就是一个并查集的模板子吗？

但这里貌似不能用路径压缩，因为返回值是 $i$ 节点与根节点的距离。

代码如下：

```cpp
#include <iostream>
#include <cstring>
#include <math.h>
using namespace std;
int fa[20005],dis[20005];
int GetDis(int x)
{
    return x==fa[x]/*判断是否找到了根节点*/?0:dis[x]+GetDis(fa[x])/*继续往下找，并累加上距离*/;
}//不能用路径压缩
int main()
{
    int T;
    for(cin>>T;T--;)
    {
        memset(dis,0,sizeof(dis));//初始化
        int n;
        cin>>n;
        for(int i=1;i<=n;i++) fa[i]=i;//初始化
        char op;
        while(cin>>op&&op!='O')
        {
            if(op=='E')//查询
            {
                int q;
                cin>>q;
                cout<<GetDis(q)<<"\n";//输出查询的答案
            }
            if(op=='I')
            {
                int u,v;
                cin>>u>>v;
                fa[u]=v,dis[u]=abs(u-v)%1000;//注意不要忘记膜一下
            }
        }
    }
    return 0;
} 


```

---

