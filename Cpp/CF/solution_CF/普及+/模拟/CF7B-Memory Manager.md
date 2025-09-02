# Memory Manager

## 题目描述

第一个国家级操作系统——BerlOS就要发布了。但是，它的一些功能还没有完善，比如内存管理系统。在开发者的计划里，第一版里的内存管理系统是简单并且是线性的。它将会支持以下操作：

    alloc n —— 在内存中分配n字节的空间。此命令将返回已分配的内存块的编号x。

    erase x —— 释放编号为x的内存块。
    defragment —— 碎片整理，将所有内存块全部向内存的起点靠拢并且不改变它们的顺序。

整条内存一共有m个字节，每个字节依次编号为1,2,...,m。

操作 alloc 有一个参数n，表示需要分配n字节大小的内存块。在执行这个操作时，系统将把一块最靠近内存起点的，长度为n的连续空闲字节分配到一个内存块（这块内存块内的所有字节将被标记为“已使用”）。这个操作的返回值为这块内存块的编号。如果没有符合条件的内存块，返回 NULL 。

操作 erase 有一个参数x，表示需要释放的内存块的编号。它将释放这个内存块（这块内存块内的所有字节将被标记为“空闲”）。如果成功释放，不返回值；如果编号为x的内存块不存在，返回 ILLEGAL\_ERASE\_ARGUMENT 。

操作 deflagment 没有任何参数。它只是将所有内存块向前依次（编号小的地方）挪动直到它们紧挨在一起。（不改变它们的顺序）

你将用连续的正整数（1,2,...）作为每一个内存块的编号。比如，第i次分配的内存块编号为i。你的任务是依次输出所有 alloc 指令的返回值，以及所有执行失败的 erase 指令的返回值。

## 样例 #1

### 输入

```
6 10
alloc 5
alloc 3
erase 1
alloc 6
defragment
alloc 6
```

### 输出

```
1
2
NULL
3
```

# 题解

## 作者：Elegy_of_Green_Kite (赞：6)

### **一、原题**

[**原题传送门**](https://www.luogu.com.cn/problem/CF7B)

主要输入有三种操作，如下：

$\texttt{alloc}$ $n$—— 在内存中插入 $n$ 字节的空间且使首地址最小，返回编号 $x$ 或 $\texttt{NULL}$。

$\texttt{erase}$ $x$—— 清空编号为 $x$ 的内存块。

$\texttt{defragment}$—— 碎片整理，将所有内存块全部向内存的起点靠拢并且不改变它们的顺序。

### 二、分块解析

先放一段主要变量的定义。

```cpp
struct node{ int s,l,id; }p[N];
int t,m,cnt,mark[N];
```
其中，$t$、$m$ 如题意介绍，$cnt$ 记录当前最大编号。

结构体 $p$ 数组储存每一个内存块的信息，表示编号为 $p_{i}.id$ 的内存块的起始位置是 $p_{i}.s$（$s$ 即 $start$），长度是 $p_{i}.l$（$l$ 即 $length$）。

$mark$ 数组标记编号为 $i$ 的内存块是否存在。

主要思路是每次插入一块内存块就在 $p$ 数组中新开辟一个位置，然后标记一下（删除和重新排序思路就比较简单了，下面会讲到）。

#### 1.$\texttt{alloc}$

如果 $n$ 大于总长 $m$，那么显然是不能实现的。

接下来定义一个变量 $le$，表示当前正在尝试位置 $le$。所谓的“连续空闲空间”就是指**内存条与内存条或边界之间的空间**。

因此，直接 $for$ 循环一遍，$le$ 开头的最大空间为 **下一个内存条的首地址 $-le$**。

如果可以放就放，然后标记一下。如果不行的话，就更新一下 $le$。

下面是可以放的情况。

```cpp
if(p[i].s-le>=n)
{
	p[++cnt]={le,n,cnt};
	printf("%d\n",cnt);
	mark[cnt]=1;
	return;
}
```
要注意几个特殊情况：

- 如果当前正在尝试的内存块不存在，就跳过。

- 如果循环结束后发现压根就没有内存块，要在循环外特判。

完整的 $\texttt{alloc}$ 代码如下。

```cpp
void alloc()
{
	int n,le=1,flag=0;//flag标记有没有内存条
	scanf("%d",&n);
	if(n>m)  { printf("NULL\n"); return; }
	for(int i=1;i<=cnt;i++)
	{
		if(!mark[p[i].id])  continue;
		flag=1;
		if(p[i].s-le>=n)
		{
			p[++cnt]={le,n,cnt};
			printf("%d\n",cnt);
			mark[cnt]=1;
			sort(p+1,p+1+cnt,cmp);
			return;
		}
		else  le=p[i].s+p[i].l;//更新le
	}
	if(!flag || m-le+1>=n)//如果整条内存都是空的或者最后一个内存块和末边界之间的空间可以放
	{
		p[++cnt]={le,n,cnt};
		printf("%d\n",cnt);
		mark[cnt]=1;
		sort(p+1,p+1+cnt,cmp);
		return;
	}
	else  printf("NULL\n");
return;
}
```
大家可能有一点疑惑，为什么要额外记录 $id$ 而不是直接用 $p_{id}$ 记录查找呢？因为在一些特殊数据下，编号小的不一定在编号大的前面，这样循环的时候会有一些问题，因此需要 $sort$ 一遍，按首地址的优先级排序。

```cpp
bool cmp(node x,node y)  { return x.s<y.s; }
```

#### 2.$\texttt{erase}$

这块非常简单，只需要看一看要清空的 $x$ 存不存在，存在**且没有越界**的话就把 $mark_{x}$ 标记为 $false$。

```cpp
void erase()
{
	int x;
	scanf("%d",&x);
	if(x<=0 || x>100)  { printf("ILLEGAL_ERASE_ARGUMENT\n"); return; }
	if(!mark[x])  { printf("ILLEGAL_ERASE_ARGUMENT\n"); return; }
	else  mark[x]=0;
return;
}
```
这里也有一个注意点：

- 小心越界

有些恶心的数据会存在 $x\le 0$ 或者 $x\ge cnt$ 的情况，直接放到 $mark$ 里就会 $RE$（~~就像我~~）。

#### 3.$\texttt{defragment}$

这个操作也非常简单，只需要把每个内存块取出来改一下首地址就可以啦。

```cpp
void defragment()
{
	int le=1;//le这里记录最小的空闲地址
	for(int i=1;i<=cnt;i++)
	{
		if(!mark[p[i].id])  continue;
		p[i]={le,p[i].l,p[i].id};
		le+=p[i].l;//更新le
	}
return;
}
```
#### 4.主函数

没什么可说的，直接调用就好了。

```cpp
int main()
{
	scanf("%d %d",&t,&m);
	for(int i=1;i<=t;i++)
	{
		scanf("%s",s+1);//s是字符数组
		if(s[1]=='a')  alloc();
		else if(s[1]=='e')  erase();
		else if(s[1]=='d')  defragment();//每条命令只需判断首字母就行了
	}
return 0;
}
```

### 三、完整代码

其实看前面的应该已经够了吧......

完整代码看[这里](https://www.luogu.com.cn/paste/7eyadfge)

---

## 作者：小闸蟹 (赞：2)

```cpp
// 这是一道模拟题，其中有一些小细节要注意
// 具体见代码和注释
#include <iostream>
#include <string>
#include <array>

int main()
{
    std::array<int, 100> Arr{ 0 };
    int t, m;
    std::cin >> t >> m;

    int id = 1; // 标记着最远的编号，从1开始
    std::string Command;
    while (t--)
    {
        std::cin >> Command;
        if (Command[0] == 'a')  // "alloc"
        {
            int p;
            std::cin >> p;

            int cnt = 0, idx = 0;
            bool OK = false;
            for (int i = 0; i < m; ++i)
            {
                if (!Arr[i])
                {
                    ++cnt;  // 去找有多少个连续的0
                }
                else
                {
                    cnt = 0;    // 中断了就清零重来
                    idx = i + 1;
                }

                if (cnt == p)   // 依题意，找到了第一个能存放p个单位的就立马跳出
                {
                    OK = true;
                    break;
                }
            }

            if (OK)
            {   // 从idx开始涂连续的p个
                for (int i = idx; i < idx + p; ++i)
                {
                    Arr[i] = id;
                }

                // 这里要加一了
                std::cout << id++ << std::endl;
            }
            else
            {
                std::puts("NULL");
            }
        }
        else if (Command[0] == 'e') // "erase"
        {
            int p;
            std::cin >> p;

            if (p > id || p <= 0)   // 删除最大标号以外的或者删除1以下的均为非法
            {
                std::puts("ILLEGAL_ERASE_ARGUMENT");
            }
            else
            {
                int f = false;
                int i;
                for (i = 0; i < m; ++i)
                {
                    if (Arr[i] == p)    // 去找要被删去的第一个数的下标
                    {
                        break;
                    }
                }

                while (Arr[i] == p)
                {
                    Arr[i] = 0; // 清零即是删除
                    ++i;
                    f = true;   // 标记删除操作被执行了
                }

                if (!f) // 如果这一次删除没有做任何操作，那么这个删除也是无效的
                {
                    std::puts("ILLEGAL_ERASE_ARGUMENT");
                }
            }
        }
        else   // "defragment"
        {
            int idx = 0;
            for (int i = 0; i < m; ++i)
            {
                if (Arr[i]) // 如果非零，则存放在前面
                {
                    Arr[idx++] = Arr[i];
                }
            }
            for (int i = idx; i < m; ++i)   // 后面那部分都是零
            {
                Arr[i] = 0;
            }
        }
    }

    return 0;
}
```

---

## 作者：_lxy_ (赞：1)

### 分析
一道大模拟。每次操作分别处理即可。
#### alloc 实现
从 $1$ 向 $m$ 找，如果从这个点开始有长度大于等于 $n$ 的空间没有被利用过，就将这里的每一个点标记为用过，如果循环完还没有能放的空间，就说明放不下。
```cpp
if(s=="alloc")
{
    scanf("%d",&x);
    int c=0,pos=0;
    for(i=1;i<=m;i++)
    {
        j=i;c=0; //j记录i之后循环到点的位置，c记录目前空间的大小
        while(!vis[j]&&j<=m) j++,c++; //连续的空间没被用过
        if(c>=x) //放得下
        {
            pos=i;
            break;
        }
    }
    if(c>=x) //能放下
    {
        for(j=pos;j<=pos+x-1;j++) //将新开的内存中每个点都标记成用过
        {
            vis[j]=true;
        }
        printf("%d\n",++cnt); //cnt记录当前放入内存的编号
        flag[cnt]=true;
        a.push_back(make_pair(pos,pos+x-1)); //记录这段内存的头和尾
        continue;
    }
    else //放不下
    {
        printf("NULL\n"); 
        continue;
    }
}
```
#### erase 实现
如果要删除的内存编号大于此时最大的编号或者之前释放过，就说明不能释放，否则将这段内存中的每一个点标记成没用过。
```cpp
if(s=="erase")
{
    scanf("%d",&x);
    if(x<0||x>inf) //特判编号过小或过大，防止溢出
    {
        printf("ILLEGAL_ERASE_ARGUMENT\n");
        continue;
    }
    if(!flag[x]) //此时没有占用编号x的内存
    {
        printf("ILLEGAL_ERASE_ARGUMENT\n");
        continue;
    }
    int s=a[x].first,t=a[x].second;
    flag[x]=false; //标记为目前没有编号为x的内存
    a[x]=make_pair(-1,-2); //标记头尾
    for(i=s;i<=t;i++) //标记区间内的每一个点为未使用
    {
        vis[i]=false;
    }
    continue;
}
```
#### defragment 实现
按照当前每个内存块的位置从 $1$ 开始，每个内存块大小不变，重新依次分配空间即可。
```cpp
if(s=="defragment")
{
    mem(vis,0);
    j=1;
    vector<int>tmp; //记录按当前内存块顺序排的内存块编号
    tmp.clear();
    for(i=1;i<=m;i++)
    {
        for(j=1;j<a.size();j++)
        {
            if(!flag[j]) continue;
            if(a[j].first<=i&&a[j].second>=i&&(tmp.empty()||tmp.back()!=j)) //i属于j号内存
            {
                tmp.push_back(j);
                break;
            }
        }
    }
    j=1;
    for(int ii=0;ii<tmp.size();ii++)
    {
        i=tmp[ii];
        if(!flag[i]) continue;
        int s=j;
        for(k=a[i].first;k<=a[i].second;k++)
        {
            vis[j++]=true; //标记新区间内的每个点
        }
        a[i].first=s;a[i].second=j-1; //重新记录左右端点
    }
}
```
### 完整代码
```cpp
#include <bits/stdc++.h>
#define mem(a,b) memset(a,b,sizeof(a));
#define elif else if
#define puchar putchar
using namespace std;
typedef pair<int,int> Pair;
const int inf=2139062143;
const int MAXN=107;
int n,m,x,tail,cnt;
string s;
vector<Pair>a;
bool vis[MAXN];
bool flag[MAXN];
int main()
{
    scanf("%d%d",&n,&m);
    a.push_back(make_pair(0,0));
    while(n--)
    {
        int i,j,k;
        cin>>s;
        if(s=="alloc")
        {
            scanf("%d",&x);
            int c=0,pos=0;
            for(i=1;i<=m;i++)
            {
                j=i;c=0;
                while(!vis[j]&&j<=m) j++,c++;
                if(c>=x)
                {
                    pos=i;
                    break;
                }
            }
            if(c>=x)
            {
                for(j=pos;j<=pos+x-1;j++)
                {
                    vis[j]=true;
                }
                printf("%d\n",++cnt);
                flag[cnt]=true;
                a.push_back(make_pair(pos,pos+x-1));
                continue;
            }
            else
            {
                printf("NULL\n");
                continue;
            }
        }
        if(s=="erase")
        {
            scanf("%d",&x);
            if(x<0||x>inf)
            {
                printf("ILLEGAL_ERASE_ARGUMENT\n");
                continue;
            }
            if(!flag[x])
            {
                printf("ILLEGAL_ERASE_ARGUMENT\n");
                continue;
            }
            int s=a[x].first,t=a[x].second;
            // cout<<a[x].first<<" "<<a[x].second<<endl;
            flag[x]=false;
            a[x]=make_pair(-1,-2);
            for(i=s;i<=t;i++)
            {
                vis[i]=false;
            }
            continue;
        }
        if(s=="defragment")
        {
            mem(vis,0);
            j=1;
            int sum=0;
            vector<int>tmp;
            tmp.clear();
            for(i=1;i<=m;i++)
            {
                for(j=1;j<a.size();j++)
                {
                    if(!flag[j]) continue;
                    if(a[j].first<=i&&a[j].second>=i&&(tmp.empty()||tmp.back()!=j))
                    {
                        tmp.push_back(j);
                        break;
                    }
                }
            }
            j=1;
            for(int ii=0;ii<tmp.size();ii++)
            {
                i=tmp[ii];
                if(!flag[i]) continue;
                int s=j;
                for(k=a[i].first;k<=a[i].second;k++)
                {
                    vis[j++]=true;
                }
                a[i].first=s;a[i].second=j-1;
            }
        }
    }
    return 0;
}
```


---

## 作者：一铭君一 (赞：1)

~~感觉这题存在谔评~~

我以为这题是某数据结构，想了半天，想起来看数据范围（因为中文题面里没有），一看，其实**模拟**就可以过本题。

~~建议翻译大大把数据范围也翻译上~~

------------

其实给大家带来困扰的应该是有些迷惑的英文题面，这里再简单的复述一下。

你需要在一个长度为$m$的段上，支持以下三种操作：

1、找到一段连续的没有标记过的段，把这一段标记为编号$n$。

2、找到编号为$x$的段，清除该段的标记。

3、把所有有标记的段之间的，没有标记的段移到序列末尾。

## 模拟思路

可以考虑开一个长度为$m$的数组`memory`，其中`memory[i]`表示第$i$个内存标记的编号。

然后设计三个函数分别对应三种操作即可，具体操作见下。

## 操作1

对于操作1，可以扫描整个长度为$m$的段，找到连续的符合条件的段。

**代码实现**

```cpp
inline void alloc(const int x){
	int find=0,st=0;//find表示找到的连续的段长
	for(int i=1;i<=m;i++){
		if(memory[i]==0 && find==0)//连续空闲空间的第一个地址是st 
			find++,st=i;
		else if(memory[i]==0)
			find++;
		else find=0;//空闲空间断了 
		//以上找空闲空间 
		if(find>=x){//找到了第一个符合条件的连续段
			for(int j=st;j<=i;j++)
				memory[j]=it;//赋值编号
			write(it,'\n');
			it++;//下一次分配的编号+1
			return;
		}
	}
	printf("NULL\n");//没找到，输出NULL
}
```

## 操作2

对于操作2，可以扫描整个长度为$m$的段，找到编号为$x$的段，清除标记。

具体一点，就是`if(memory[i]==x) memory[i]=0`。

**代码实现**

```cpp
inline void erase(const int x){
	if(x<1 || x>it){
		printf("ILLEGAL_ERASE_ARGUMENT\n");
		return;//判断一下是否合法，否则会被hack
	}
	for(int i=1;i<=m;i++)//扫描数组，找到所要删除的段
		if(memory[i]==x){
			int p=i;
			while(memory[p]==x)//循环删除
				memory[p++]=0;
			return;
		}
	printf("ILLEGAL_ERASE_ARGUMENT\n");//没有对应的段，报错
}
```

## 操作3

对于操作3，这里介绍一种复制暴力实现。

既然要求把没有标记的段放到末尾，可以考虑copy一份原数组。

但是copy的时候，不copy未标记的段。

然后把copy的数组，重新赋值到原数组中，这样，没标记的段就移到了末尾。

**代码实现**

```cpp
inline void defragment(){
	std::queue<int>Q;
	for(int i=1;i<=m;i++)
		if(memory[i]!=0)//利用队列循环实现
			Q.push(memory[i]);
//这样，数组就copy到队列中
	int i=1;
	memset(memory,0,sizeof(memory));//直接清空原数组
	while(Q.size()){//从1到队列大小重新复制到原数组中
		memory[i++]=Q.front();
		Q.pop();
	}
}
```

## 主函数

读入相应的数据，调用相应的函数维护即可。

```cpp
signed main(){
	t=read(),m=read();
	for(int i=1;i<=t;i++){
		std::string st;
		std::cin>>st;
		if(st=="alloc")
			alloc(read());
		if(st=="erase")
			erase(read());
		if(st=="defragment")
			defragment();
	}
	return 0;
} 
```

---

## 作者：CrTsIr400 (赞：1)

这道题目的主要思路就是**模拟**。

发现 $T,n\le 100$ ，于是考虑 $O(Tn^2)$ 时间复杂度的**朴素~~暴力~~算法**。

当然也可以优化成 $O(Tn)$ 的时间复杂度。

# 1.$\texttt{alloc}$操作实现

我们先探究 $\texttt{alloc}$ 操作：

> 在内存里分配长度为 $x$ 的空间。

考虑这是线性的，于是枚举每个 $i$ ，判断 $i$ 至 $i+x-1$ 是否全为空。如果全为空直接分配空间得了，直接退出。

第一层为 $O(n)$ ，第二层为 $O(x)$ 。

这个暴力算法真的能水过数据，不超过 $O(n^2)$ 。

```cpp
int l[101],r[101],n,x,t,cnt;
bool a[101],al[101];
bool canput(int l,int r)
{
	Fu(i,l,r)if(a[i])return 0;
	return 1;
}
void alloc()
{
	cin>>x;
	Fu(i,1,n-x+1)
	{
		if(canput(i,i+x-1))
		{
			printf("%d\n",++cnt);
			l[cnt]=i,r[cnt]=i+x-1;
			Fu(j,l[cnt],r[cnt])a[j]=1;
			al[cnt]=1;
			return;
		}
	}
	printf("NULL\n");
}
```

实际上可以通过前缀和优化成 $O(n)$ 。

就是首先预处理前缀和，接着再循环一遍，判断这段区间的使用情况和为多少。

大致思想看代码。

```cpp
void alloc()
{
	cin>>x;
	int s[101]={};
	Fu(i,1,n)s[i]=s[i-1]+a[i];
	Fu(i,1,n-x+1)if(s[i+x-1]-s[i-1]==0)
	给这段区间赋值，跳出循环;
	printf("NULL\n");
}
```

时间复杂度 $O(n)$ 。

# 2.$\texttt {erase}$ 操作实现


```cpp
void erase()
{
	cin>>x;
	if(x>cnt||x<1||!al[x]){printf("ILLEGAL_ERASE_ARGUMENT\n");return;}
	Fu(j,l[x],r[x])a[j]=0;
	l[x]=r[x]=0;
	al[x]=0;
}
```

没什么好说的， $O(n)$ 直接删除。

把这段区间的内存使用值全部清空，时间复杂度 $O(n)$。

# 3.$\texttt{deflagment}$ 操作实现

每次申请内存时，即在内存区间序列里的末尾插入这一个区间。

删除同理。

然后每个区间往前移动只需要移动左右端点即可，但是还要移动里面的数据。

时间复杂度$O(\sum^{cnt} _{i=1} (r_i-l_i))$，因为这些区间不重叠，所以时间复杂度约等于 $O(n)$ 。

```
void deflagment()
{
	Fu(i,1,cnt)
	if(al[i])
	{
		Fu(j,l[i],r[i])a[j]=0;
		while(a[l[i]-1]==0&&l[i]>1)--l[i],--r[i];
		Fu(j,l[i],r[i])a[j]=1;
	}
}

```

# 4.完整代码（$O(Tn^2)$）

```cpp

#include<bits/stdc++.h>
#define F(i,a,b,c) for(register int i=(a);(b);i=(c))
#define Fu(i,a,b) F(i,(a),i<=(b),i+1)
#define Fd(i,a,b) F(i,(a),i>=(b),i-1)
#define inf 1073741823
#define LL long long
int Fl,ch;template<typename t>int in(t&a){a=0;ch=getchar();Fl=1;while(((ch<'0')||(ch>'9'))&&ch!=EOF)Fl=(ch=='-')?-Fl:Fl,ch=getchar();if(ch==EOF)return 0;while((ch>='0')&&(ch<='9'))a=a*10+ch-'0',ch=getchar();a*=Fl;return 1;}template<typename t,typename ...ARGS>int in(t&a,ARGS&...args){return in(a)+in(args...);}
using namespace std;
int l[101],r[101],n,x,t,cnt;
bool a[101],al[101];
bool canput(int l,int r)
{
	Fu(i,l,r)if(a[i])return 0;
	return 1;
}
void alloc()
{
	cin>>x;
	Fu(i,1,n-x+1)
	{
		if(canput(i,i+x-1))
		{
			printf("%d\n",++cnt);
			l[cnt]=i,r[cnt]=i+x-1;
			Fu(j,l[cnt],r[cnt])a[j]=1;
			al[cnt]=1;
			return;
		}
	}
	printf("NULL\n");
}
void erase()
{
	cin>>x;
	if(x>cnt||x<1||!al[x]){printf("ILLEGAL_ERASE_ARGUMENT\n");return;}
	Fu(j,l[x],r[x])a[j]=0;
	l[x]=r[x]=0;
	al[x]=0;
}
void deflagment()
{
	Fu(i,1,cnt)
	if(al[i])
	{
		Fu(j,l[i],r[i])a[j]=0;
		while(a[l[i]-1]==0&&l[i]>1)--l[i],--r[i];
		Fu(j,l[i],r[i])a[j]=1;
	}
}
int main()
{
	in(t,n);
	Fu(i,1,t)
	{
		string s;cin>>s;
		if(s[0]=='a')alloc();
		if(s[0]=='e')erase();
		if(s[0]=='d')deflagment();
	}
	return 0;
}
//BY 线段树蒟蒻

```

---

## 作者：brealid (赞：0)

这道题，是一道不算太难的模拟题。

做法很容易想到。

[原题链接 CF7B Memory Manager](https://www.luogu.org/problemnew/show/CF7B)

## 思路及时间复杂度

对于每个内存块，记录两个参数 $l[i]$ 和 $r[i]$，代表的是其在内存中的开始位置和结束位置（左闭右闭）

再开一个数组 $from[i]$，记录当前数组的状态。第 $i$ 位若为 $0$ ，则代表该位置没有被分配。若不为 $0$，则代表其属于内存块的编号。

```cpp
int from[107], size; // size 即内存大小
int l[107], r[107], top; // top 即已有内存块数量
```

### $alloc$

1. 找到第一块空闲的内存块。  
   方法：暴力找，并且使用类似于 KMP 的方法进行优化。优化前复杂度 $O(n^2)$，优化后复杂度 $O(n)$。   
    ```cpp
    void alloc(int n)
    {
        bool isSuccess = 0;
        for (int i = 1; i <= size - n + 1; i++) {
            bool couldUse = 1;
            for (int j = 0; j < n; j++) {
                if (from[i + j]) {
                    couldUse = 0;
                    i = i + j; // 优化
                    break;
                }
            }
            if (couldUse) {
                top++;
                l[top] = i;
                r[top] = i + n - 1;
                for (int j = l[top]; j <= r[top]; j++) {
                    from[j] = top;
                }
                isSuccess = 1;
                break;
            }
        }
        if (isSuccess) {
            write(top, '\n');
        } else {
            puts("NULL");
        }
        #ifdef debugTAG
        for (int i = 1; i <= size; i++) {
            write(from[i], 32);
        }
        putchar(10);
        #endif
    }
    ```  
2. 如果找到了，就存储；  
   否则，输出 ``NULL``。
   
### $erase$
1. 特殊判断  
   若为负数，为0，大于已有内存块数量或者已经被删除就输出 ``ILLEGAL_ERASE_ARGUMENT``   
   否则，删除；
2. 将 $l[i]$ 标为 $-1$，并清除内存
	```cpp
    void erase(int x)
    {
        if (x <= 0 || x > top || l[x] == -1) {
            puts("ILLEGAL_ERASE_ARGUMENT");
            return;
        }
        for (int j = l[x]; j <= r[x]; j++) {
            from[j] = 0;
        }
        l[x] = -1;
        #ifdef debugTAG
        for (int i = 1; i <= size; i++) {
            write(from[i], 32);
        }
        putchar(10);
        #endif
    }
    ```
    
时间复杂度 $O(n)$
    
### $defragment$

我的做法是利用 $priority\_queue$

不太好说，直接看代码吧

```cpp
void defragment()
{
    priority_queue<LR> pq;
    for (int i = 1; i <= top; i++) {
        if (l[i] != -1) {
            pq.push(LR(l[i], r[i], i));
        }
    }
    memset(from, 0, sizeof(from));
    int Rwall = 0;
    while (!pq.empty()) {
        LR f = pq.top();
        pq.pop();
        l[f.idx] = Rwall + 1;
        r[f.idx] = Rwall + f.length;
        Rwall += f.length;
        for (int i = l[f.idx]; i <= r[f.idx]; i++) {
            from[i] = f.idx;
        }
    }
    #ifdef debugTAG
    for (int i = 1; i <= size; i++) {
        write(from[i], 32);
    }
    putchar(10);
    #endif
}
```

其中 $LR$ 是我自己定义的结构体。

声明如下：

```cpp
struct LR {
    int l, r, idx;
    int length;
    LR(int L = 0, int R = 0, int IDX = 0) : l(L), r(R), idx(IDX), length(r - l + 1) {}
    bool operator < (const LR &other) const
    {
        return l > other.l;
    }
};
```

时间复杂度 $O(nlog_{2}n)$  
实际运行中更快，大约 $O(n)$

### 总时间复杂度

$O(n^2log_2n)$，完全可以过掉

## 代码

```cpp
/*************************************
 * problem:      CF7B Memory Manager.
 * user ID:      63720.
 * user name:    Jomoo.
 * time:         2019-05-19.
 * language:     C++.
 * upload place: Luogu.
*************************************/ 

#include <bits/stdc++.h>
using namespace std;

template <typename Int>
inline Int read()       
{
    Int flag = 1;
    char c = getchar();
    while ((!isdigit(c)) && c != '-') c = getchar();
    if (c == '-') flag = -1, c = getchar();
    Int init = c & 15;
    while (isdigit(c = getchar())) init = (init << 3) + (init << 1) + (c & 15);
    return init * flag;
}

template <typename Int>
inline void write(Int x)
{
    if (x < 0) putchar('-'), x = ~x + 1;
    if (x > 9) write(x / 10);
    putchar((x % 10) | 48);
}  

template <typename Int>
inline void write(Int x, char nextch)
{
    write(x);
    putchar(nextch);
}  

#define int long long

struct LR {
    int l, r, idx;
    int length;
    LR(int L = 0, int R = 0, int IDX = 0) : l(L), r(R), idx(IDX), length(r - l + 1) {}
    bool operator < (const LR &other) const
    {
        return l > other.l;
    }
};

struct Memory_Manager {
    int from[107], size;
    int l[107], r[107], top;

    Memory_Manager() : top(0)
    {
        memset(from, 0, sizeof(from));
    }

    void alloc(int n)
    {
        bool isSuccess = 0;
        for (int i = 1; i <= size - n + 1; i++) {
            bool couldUse = 1;
            for (int j = 0; j < n; j++) {
                if (from[i + j]) {
                    couldUse = 0;
                    i = i + j;
                    break;
                }
            }
            if (couldUse) {
                top++;
                l[top] = i;
                r[top] = i + n - 1;
                for (int j = l[top]; j <= r[top]; j++) {
                    from[j] = top;
                }
                isSuccess = 1;
                break;
            }
        }
        if (isSuccess) {
            write(top, '\n');
        } else {
            puts("NULL");
        }
        #ifdef debugTAG
        for (int i = 1; i <= size; i++) {
            write(from[i], 32);
        }
        putchar(10);
        #endif
    }

    void erase(int x)
    {
        if (x <= 0 || x > top || l[x] == -1) {
            puts("ILLEGAL_ERASE_ARGUMENT");
            return;
        }
        for (int j = l[x]; j <= r[x]; j++) {
            from[j] = 0;
        }
        l[x] = -1;
        #ifdef debugTAG
        for (int i = 1; i <= size; i++) {
            write(from[i], 32);
        }
        putchar(10);
        #endif
    }

    void defragment()
    {
        priority_queue<LR> pq;
        for (int i = 1; i <= top; i++) {
            if (l[i] != -1) {
                pq.push(LR(l[i], r[i], i));
            }
        }
        memset(from, 0, sizeof(from));
        int Rwall = 0;
        while (!pq.empty()) {
            LR f = pq.top();
            pq.pop();
            l[f.idx] = Rwall + 1;
            r[f.idx] = Rwall + f.length;
            Rwall += f.length;
            for (int i = l[f.idx]; i <= r[f.idx]; i++) {
                from[i] = f.idx;
            }
        }
        #ifdef debugTAG
        for (int i = 1; i <= size; i++) {
            write(from[i], 32);
        }
        putchar(10);
        #endif
    }
} BerlOS;

int t, m;
char buf[20], n;

signed main()
{
    t = read<int>();
    m = read<int>();
    BerlOS.size = m;
    while (t--) {
        scanf("%s", buf);
        switch(buf[0]) {
            case 'a' :
                BerlOS.alloc(read<int>());
                break;
            case 'e' :
                BerlOS.erase(read<int>());
                break;
            case 'd' :
                BerlOS.defragment();
                break;
        }
    }
    return 0;
}
```

---

## 作者：iiawaKL (赞：0)

# ~~首先在看题解前，先大喊一声：内存条将会臭名昭著！~~

好了话不多说开始我的表演。

很简单这题是个纯模拟（但是MLE和TLE随时出现），而且，这题很不好写，虽然是个模拟。

好了话不多说上代码~~

```
#include<bits/stdc++.h>
using namespace std;
int d[111],n,m,z,i,j,k,l;
int cnt=0;
string s;
int main()
{
	cin>>n>>m;
	for(k=0;k<n;k++)
	{
		cin>>s;
		if(s=="alloc")
		{
			cin>>z;
			for(i=0,j=-1;i<m;i++)
			{
				if(i-j==z&&!d[i])break;
				else if(d[i])j=i;
			}
			if(i-j==z&&i<m)
			{
				cnt++;
				cout<<cnt<<endl;
				for(l=j+1;l<=i;l++)d[l]=cnt;
			}
			else cout<<"NULL"<<endl;
		}
		if(s=="erase")
		{
			cin>>z;
			int p=0;
			for(int i=0;i<m;i++)
			{
				if(d[i]==z&&z!=0)
				{
					d[i]=0;
					p=1;
				}
			}
			if(p==0)cout<<"ILLEGAL_ERASE_ARGUMENT"<<endl;
		}
		if(s=="defragment")
		{
			for(int i=0,j=0;i<m;i++)
			{
				if(d[i])
				{
					l=d[j];
					d[j]=d[i];
					d[i]=l;
					j++;
				}
			}
		}
	}
	return 0;
}
```

完

---

