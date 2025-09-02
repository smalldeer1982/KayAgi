# [COCI 2021/2022 #6]  Superpozicija

## 题目描述

世界闻名的物理学家 Juraj 最近发现了一种新的基本粒子——括号子（parenthesision）。括号子可以有开 `(` 或关 `)` 两种状态。使用 Juraj 自制的粒子加速器，他创造了 $t$ 个由 $n$ 个括号子组成的叠加态序列。这 $t$ 个序列中的 $n$ 个括号子都是两个不同的位置和（不必不同的）状态的叠加态。如果序列被观测的话，括号子的波函数就将坍缩，每个括号子的位置和状态就是确定的了。Juraj 想知道这些括号子是否可以坍缩为一个合法的括号序列。

Juraj M. 博士知道这些革命性的且完全有科学依据的粒子的量子物理学已经超出了 COCI 的参赛者的知识范围，所以他提供了一个正式的题面：

给你 $t$ 个长度为 $2n$ 且由左右括号构成的括号序列。每个括号都恰好是一对括号中的一个。一对中的括号可以是不同的，也可以都是左括号或右括号。Juraj 想知道是否可以在每对括号中选一个，使得最后组成的括号序列是一个合法的括号序列。此外，如果是可能的，他需要你输出如何才能获得一个合法的括号序列。一个括号序列是合法的，如果它是一个空串，或者可以写成 $(A)$ 或者 $AB$，其中 $A$ 和 $B$ 是任意的合法括号序列。

## 说明/提示

### 样例解释 1：

从原序列 `()))((()` 中，只有加粗的部分会留下 **(**))**)(**((**)**，即 **()()**，它是一个合法的括号序列。

### 数据范围：

对于 $9\%$ 的数据：$1\le n \le 10$。

对于 $9\%$ 的数据：$z[a_i]=z[b_i]$。

对于 $18\%$ 的数据：$b_i=a_i+1$。

对于 $100\%$ 的数据：$1\le t \le 10^5,\sum n\le10^5,1\le n \le 10^5 ,1\le a_i \le b_i \le 2\times n$。

本题分值与 [COCI 2021-2022#6](https://hsin.hr/coci/contest6_tasks.pdf) 分值相同，满分 $110$ 分。

## 样例 #1

### 输入

```
1
4
()))((()
1 2
3 5
4 6
7 8```

### 输出

```
0 1 0 1```

## 样例 #2

### 输入

```
1
4
)()()()(
1 2
3 4
5 6
7 8```

### 输出

```
1 1 0 0```

## 样例 #3

### 输入

```
1
3
(()())
1 6
2 4
3 5```

### 输出

```
-1```

# 题解

## 作者：yzy_rick (赞：7)

首先我们知道，一个括号序列合法当且仅当将所有的 `(` 当成 $+1$ ,将所有的 `)` 当成 $-1$ ,对于任意位置的前缀和都非负，且最后一个位置的前缀和为 $0$.

那么，如果 $n$ 是奇数，直接无解。

接下来，让我们先考虑一些特殊情况；

- 如果 $s_{a_i}$ 是 `(` 且 $s_{b_i}$ 是 `(`，那么显然是要选择 $s_{a_i}$；

- 如果 $s_{a_i}$ 是 `)` 且 $s_{b_i}$ 是 `)`，那么显然是要选择 $s_{b_i}$。

- 如果 $s_{a_i} \not= s_{b_i}$，此时无论是直接选择 $s_{a_i}$ 还是 $a_{b_i}$ 都是不对的，反例：

  ![](https://cdn.luogu.com.cn/upload/image_hosting/3drykgmp.png)

那么考虑带悔贪心。

然而，我们会发现一个问题，这个题没有办法像一些带悔贪心的题一样建出来费用流模型，所以无法直接贪心模拟费用流。

于是我们需要建立一个反悔贪心机制，这个机制的核心点在于：对于所有的 `()` 和 `)(`，都先贪心地选择 `)`，然后贪心地将一些 `)` 反悔成 `(`。

那么考虑如何利用带悔贪心将序列变为合法的。

先考虑一下，如果将一个 `)` 变为 `(` 对整个前缀和序列的贡献是什么？

不妨设第 $i$ 对的两个位置靠左的为 $l_i$，靠右的为 $r_i$。

那么，对于一个位置来说，无论是删去一个 `)`，还是加上一个`(`，对这个位置以及以后所有的前缀和贡献都是 $+1$。

所以把第 $i$ 对的 `)` 变为 `(` 的贡献就是：

对于每一个 $l_i \leq j \leq n$，$sum_j$ 会增加 $1$。

对于每一个 $r_i \leq j \leq n$，$sum_j$ 还会额外增加 $1$。

整理一下，就是：

对于每一个 $l_i \leq j < r_i$，$sum_j$ 会增加 $1$。

对于每一个 $r_i \leq j \leq n$，$sum_j$ 会增加 $2$。

但是此时又会产生一个问题：如果面对多个可以反悔的括号对，到底反悔哪个更优？

先说答案：优先选择 $r_i$ 更小的反悔。

不妨设当前的位置为 $p$，那么我们只要证明对于剩余任意一对可以反悔的 $l_j,r_j$ ,反悔第 $j$ 对不会优于第 $i$ 对就可以了。

- $r_i<r_j<p$：由于此时 $p$ 之前的位置都已经合法了，而这两个区间对于 $p$ 后面的贡献都一样，选哪个都无所谓；
- $r_i<p<r_j$：那么对于任意的 $p<x<r_j$，选择 $i$ 之后 $sum_x$ 会增加 $2$，而选择 $j$ 只能给这一段 $+1$。而且，如果 $p$ 后面有一些`((` 且  $s_{r_j}$ = `)`，如果不反悔 $j$ 的话它还可以与后面产生贡献。综合来说，选择 $i$ 各方面还是更优的；
- $p<r_i<r_j$：与第二种情况同理。

所以，直接按照这个策略做带悔贪心就可以了。

无解的情况就是：在一个位置前缀和无论如何都 $<0$，或者最终前缀和只能 $>0$。

最后附上代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define pa pair<int,int>
#define mp make_pair
#define fi first
#define se second
inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
void file()
{
	string file_name="data";
	freopen((file_name+".in").c_str(),"r",stdin);
	freopen((file_name+".out").c_str(),"w",stdout);
}
const int N=1e5+10;
int n;
char s[2*N];
pa a[N];
//a表示一堆匹配的两个位置
int p[2*N],f[2*N];
//p表示当前位置在匹配中的另一个位置
//f表示当前位置选或者不选，f[i]=1代表选，f[i]=-1代表不选
bool solve()
{
    if(n&1)return 0;//n是奇数直接判掉
    priority_queue<int,vector<int>,greater<int>>q;
    int sum=0;
    for(int i=1;i<=2*n;i++)
    {
        if(f[i]==1){if(s[i]=='(')sum++;else sum--;}//这个位置已经标记必选
        if(s[i]!=s[p[i]]&&i<p[i])q.push(p[i]);//将r[i]加入队列中
        while(sum<0&&q.size())
        {
            int k=q.top();
            q.pop();
            f[k]=-f[k];
            f[p[k]]=-f[p[k]];
            //将这对匹配取反
            if(k<=i)sum++;
            if(p[k]<=i)sum++;
            //计算到当前位置的贡献，如果反悔的某个位置在当前位置后面，那么这个贡献到后面再算
        }
        if(sum<0)return 0;
        //当前位置前缀和无法做到>=0
    }
    if(sum!=0)return 0;
    //整个序列前缀和!=0
    return 1;
}
signed main()
{
	// file();
	int aqx=read();
	while(aqx--)
	{
		n=read();
		scanf("%s",s+1);
        //读入
        memset(p,0,sizeof(int)*(2*n+10));
        memset(f,-1,sizeof(int)*(2*n+10));
        //多测不能直接无脑memset
		for(int i=1;i<=n;i++)
        {
            int x=read(),y=read();
            a[i]=mp(x,y);
            p[x]=y,p[y]=x;
            if(s[x]==s[y])
            {
                //相同的情况，（取左边，）取后边
                if(s[x]=='(')f[x]=1;
                else f[y]=1;
            }
            else
            {
                //不相同，优先取）
                if(s[x]==')')f[x]=1;
                else f[y]=1;
            }
        }
        if(!solve())puts("-1");//无解
        else
        {
            for(int i=1;i<=n;i++)
            {
                if(f[a[i].fi]==1)printf("0 ");
                else printf("1 ");
            }
            printf("\n");
        }
	}
	return 0;
}
```



---

## 作者：破壁人罗辑 (赞：0)

这是可以算是一道反悔贪心的板子题。

### 题意简述

给出 $2n$ 个括号组成的括号序列，序列中的括号两两形成一组，找出一个方案在这 $n$ 组括号中每组各选一个，使得选择的括号构成一个合法的括号序列。

### 解题思路

整个括号序列合法的充要条件为：**在每一个位点之前的左括号数大于等于右括号数，且整个序列的左括号数等于右括号数。**

记左括号为 $1$，右括号为 $-1$，如果该位置的括号不选择则记为 $0$，这个序列合法的充要条件为：**每个位置的前缀和大于等于零，且最后一个位置的前缀和等于零。**

所以我们对于一组相同的括号可以直接这样贪心地选择：两个左括号取左侧的那个，两个右括号取右侧的那个。

设**合法前缀序列**表示**一个所有位点的前缀和都大于等于零的序列**。

显然可知以下推论：一个合法前缀序列删去任意一个右括号或添加任意一个左括号后仍为合法前缀序列。

所以对于一组不同的括号可以总是先选择右括号。

从左到右遍历、选择。在每一个位点都需要判断前缀序列是否为合法前缀序列，遇到不合法的情况（因为每个点都判断，此时当前位点的前缀和为 $-1$）时，将之前选择的一组不同的括号中的右括号改为左括号，此时可以保证当前位点的前缀和为 $0$ 或 $1$，而之前的序列仍然是合法前缀序列。且这种方法得到的合法前缀序列的和最小。

如果之前选择了多组不同的括号，设左括号的位置为 $p_L$，右括号的位置为 $p_R$，则修改后会使得区间 $[\min(p_L,p_R),\max(p_L,p_R))$ 内的前缀和都增加 $1$，区间 $[\max(p_L,p_R),2n]$ 内的前缀和都增加 $2$。如果当前遍历到了位置 $p$，对于 $p\geq\max(p_L,p_R)$ 的所有组选择后都不会对后续情况产生影响，若 $p<\max(p_L,p_R)$，则为了让后续尽可能多的位置前缀和保持大于等于零，应尽量选择 $\max(p_L,p_R)$ 最小的一组。

### AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
char s[200010];
int pos[200010],ab[100005][2],q[200010];
struct comp{
	bool operator()(const pair<int,int>x,const pair<int,int>y)const{return max(x.first,x.second)>max(y.first,y.second);}
};
int main(){
	int T;scanf("%d",&T);
	while(T--){
		int n,ans=0;scanf("%d%s",&n,s);
		for(int i=0;i<n;i++){
			q[i<<1]=q[(i<<1)|1]=0;
			scanf("%d%d",&ab[i][0],&ab[i][1]);
			--ab[i][0];--ab[i][1];
			pos[pos[ab[i][0]]=ab[i][1]]=ab[i][0];
		}
		priority_queue<pair<int,int>,vector<pair<int,int> >,comp>r;
		for(int i=0;i<n<<1;i++){
			if(q[i]==0&&q[pos[i]]==0){
				if(s[i]=='('){
					if(s[pos[i]]=='(')q[i]=1;
					else{
						r.push(make_pair(i,pos[i]));
						q[pos[i]]=-1;
					}
				}
				else if(s[pos[i]]==')')q[pos[i]]=-1;
				else{
					r.push(make_pair(pos[i],i));
					q[i]=-1;
				}
			}
			if(q[i]!=0){
				ans+=q[i];
				if(ans<0){
					if(r.empty())break;
					pair<int,int>p=r.top();r.pop();
					if(i>=p.second)ans++;
					q[p.second]=0;
					if(i>=p.first)ans++;
					q[p.first]=1;
				}
			}
		}
		if(ans)puts("-1");
		else{
			for(int i=0;i<n;i++)printf("%d ",q[ab[i][0]]?0:1);
			putchar('\n');
		}
	}
	return 0;
}
```

---

