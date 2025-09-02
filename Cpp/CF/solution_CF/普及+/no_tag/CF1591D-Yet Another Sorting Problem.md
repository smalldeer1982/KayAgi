# Yet Another Sorting Problem

## 题目描述

### 题意简述
给定一个数组 $a_1,a_2,\dots,a_n$，询问是否能用有限次操作使其单调不减。

这里将一次操作定义为将 $a_i,a_j,a_k$ （$i,j,k$ 互不相等）的值轮换，即将其分别设为 $a_j,a_k,a_i$。

## 样例 #1

### 输入

```
7
1
1
2
2 2
2
2 1
3
1 2 3
3
2 1 3
3
3 1 2
4
2 1 4 3```

### 输出

```
YES
YES
NO
YES
NO
YES
YES```

# 题解

## 作者：I_am_Accepted (赞：4)

### Analysis

首先，**如果有两个数相同，则一定 YES**。

#### Proof

先将这两个数（设为 $x,y$）移到正确的位置，定死。

对于任意两个其他的数 $a,b$，均可通过以下步骤 swap：

1. $a\to b\to x$

2. $x\to a\to y$

而我们知道任意交换可以进行排序，即得证。

剩下只有序列为 $n$- 排列的情况了。

我们先将 $1\to (n-2)$ 都归位（因为还剩 $(n-1)$ 和 $n$ 两个所以必然可以做到），如果此时 $(n-1)$ 和 $n$ 也归位了，即 YES，否则 NO。

#### Proof

$\{1,2,\dots,n-2,n-1,n\}$ 的逆序对数为 $0$。

$\{1,2,\dots,n-2,n,n-1\}$ 的逆序对数为 $1$。

我们证明**只有两个排列逆序对数奇偶性相同才能通过三者轮换互相转化**，以此证明原命题。

考虑一次轮换 $a,b,c\to c,a,b$（$a,b,c\to b,c,a$ 相当于两次这种操作）：

发现无论 $a,b,c$ 的大小关系如何，$\{a,b,c\}$ 三者间的逆序对奇偶不变（枚举即可），只需考虑原来 $a,b$ 之间、$b,c$ 之间的数与 $a,b,c$ 构成的逆序对数即可，枚举两区间的值域对应的贡献，发现奇偶还是一样，原命题得证。

其实这与 $8$ 数码问题解的判定类似，感兴趣的读者可以查一下。
 
### Code

```cpp
int n,a[N];
int t[N];
int pos[N];
void modify(int x,int y,int z){//x->y y->z z->x
	int xx=a[x],yy=a[y],zz=a[z];
	a[x]=zz,a[y]=xx,a[z]=yy;
	pos[zz]=x,pos[xx]=y,pos[yy]=z;
}
void work(){
	cin>>n;
	For(i,1,n) t[i]=0;
	For(i,1,n) cin>>a[i];
	For(i,1,n) t[a[i]]++;
	For(i,1,n) if(t[i]>1){
		cout<<"YES"<<endl;
		return ;
	}
	For(i,1,n) pos[a[i]]=i;
	int x,y;
	For(i,1,n-2){
		if(pos[i]==i) continue;
		x=pos[i];
		y=i+1;
		if(y==x) y++;
		modify(x,i,y);
	}
	if(a[n-1]==n-1) cout<<"YES"<<endl;
	else cout<<"NO"<<endl;
}
```

---

## 作者：xiaozeyu (赞：2)

[CF1591D Yet Another Sorting Problem
](https://www.luogu.com.cn/problem/CF1591D)

 逆序对以及树状数组。
 
 题目中会给出一个初始序列。
 
 我们每次可以选中 $3$ 个数字，一次操作中可以将这几个数字循环变换。
 
 这里的循环变换是将这三个数字右移变换。
 
 也就是说选出三个位置 $i,j,k$，它同时将 $a_i$ 放置在位置 $j$ 上，$a_j$ 放置在位置 $k$ 上，$a_k$ 放置在位置 $i$ 上，而不改变任何其他元素。
 
 我们要求出这个序列是否能通过一系列的操作排序成不严格单调递增的。
 
 我们可以先考虑选出三个不同的数字进行排序。
 
 在三个数字情况下，在 $2,3,1$ 或 $3,2,1$ 时，变换后逆序对数量是减少的，减少了二队逆序对，这说明更加接近递增情况了。
 
 将其放大到全部情况可以发现也是类似的。
 
 这样子的变换不难发现当为一对逆序对时，无法再变换成严格递增。应为一次拿出三个换，而本身只要拿出两个就行了，另一个一定会受到影响，换后的情况实则一样，此时表明不行。
 
 但是别忘了，题目要求的时不严格单调递增。
 
 不严格与严格的区别在哪里呢？就是不严格时可以有相等的数字放在一起。
 
 我们还需考虑一下相等的数字应该如何去处理。
 
 当选出的三个数字中有两个相同时，我们可以发现，这相当于将不同的那个数字随便放置！
 
 这说明有数字相同时，优势在我！这时一定可以成功。
 
 那我们就再用树状数组计数，检验逆序对的奇偶性，判一下相同数字，直接完成任务。
 
 注意一点，不要直接重置整个数组，可以这样子写。
 
 ```cpp
memset(s,0,n+10<<2);
memset(f,0,n+10<<2);
```

时间复杂度 $O(n\log n)$。

 代码如下。
 
 ---
 
 ```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=a;i<=b;i++)
#define Rep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
int read()
{
	char c=getchar();int x=0;bool f=0;
	while(!isdigit(c))f^=!(c^45),c=getchar();
	while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();
	if(f)x=-x;return x;
}
const int maxn=500010;
int T,n,s[maxn],f[maxn],x;
long long ans;
void update(int x){for(;x<=n;x+=x&-x)s[x]++;}
int query(int x){int ans=0;for(;x;x-=x&-x)ans+=s[x];return ans;}
int main()
{
	T=read();
	while(T--)
	{
		n=read();ans=0;
		memset(s,0,n+10<<2);
		memset(f,0,n+10<<2);
		For(i,1,n) x=read(),f[x]++,ans+=i-1-query(x),update(x);
		For(i,1,n) if(f[i]>1) ans=0;
		puts(ans&1?"NO":"YES");
	}
}

```

 感谢管理员的审核。
 

---

## 作者：enucai (赞：1)

**前言：这题思维难度还不错吧，不过有小哥在评论区说是盗题的/doge**

## 题意简述

给你一个长度为 $n$ 的序列 $a$，$\forall i$ 满足 $1\le i \le n$，都有 $1\le a_i\le n$，但注意 $a$ 中可能会有重复的元素。

现在，给定一种swap操作：

- 选定三个不同的数 $i,j,k$ 满足 $1\le i,j,k \le n$，操作后 $a_i,a_j,a_k$ 分别变为 $a_k,a_i,a_j$。

问你这个序列 $a$ 能否通过若干次swap操作后变成一个非递减序列。

## 思路简述

首先要分类讨论。

如果有至少两个数的数值相同，那么答案一定是`YES`。

假设我们要交换两个数 $b$ 与 $c$，相同的数的数值为 $a$。那么我们可以进行以下操作（原序列为 $[a,a,b,c]$）：

$[a,a,b,c]\to[\underline b,\underline a,\underline a,c]\to[b,\underline c,\underline a,\underline a]\to[b,\underline a,\underline c,\underline a]\to[\underline a,\underline b,c,\underline a]\to[\underline a,\underline a,c,\underline b]$

这样就完成了 $b$ 与 $c$ 之间的位置交换。有了这样的操作以后，我们就可以把新的swap操作看成普通的交换两个元素的操作。至于两个相同元素的位置，我们可以先将其他的排成某种特定的顺序，最后再与他们交换以达到归位的效果。因此答案一定为`YES`。

如果每个数都不相同，那么这个序列就成了 $1$ 到 $n$ 的全排列。我们可以处理出每个循环节的长度。

在尝试几次以后，我们发现，进行一次swap操作，相当于：

- 将两个长度为 $a$ 与 $b$ 的循环节合并为一个长度为 $a+b-1$ 的新的循环节；或将一个拆分为两个。

- 将三个长度分别为 $a$，$b$ 与 $c$ 的循环节合并成一个长度为 $a+b+c$ 的循环节；或将一个拆分三个。

- 将某个单独的循环节长度加 $2$ 或减 $2$。

现在我们可以进行合并和分解循环节的操作。如果最后循环节的长度是奇数，那么答案就是`YES`，否则为`NO`。

蒟蒻的语文水平贼差，看不懂是正常的，不过，看代码应该能看懂把qwq。。

## 蒟蒻代码

**Talk is cheap, show me the code.**

```cpp
int n,a[500010],cnt[500010];
bool vis[500010];
void work(){
	n=read();
	For(i,1,n) cnt[i]=0;
	For(i,1,n) a[i]=read(),cnt[a[i]]++;
	For(i,1,n) if(cnt[i]>=2){
		puts("YES");
		return;
	}
	For(i,1,n) vis[i]=0;
	int sum=1;
	For(i,1,n) if(!vis[i]){
		int x=i,cnt=0;
		while(!vis[x]) vis[x]=1,x=a[x],cnt++;
		sum+=cnt-1;
	}
	if(sum&1) puts("YES");
	else puts("NO");
}
```

---

## 作者：CHSTO (赞：1)

其实就是看逆序对的个数，如果数组里有偶数个逆序对或者有重复的元素，就一定可行，反之就不行。
```cpp

void update(int x,int v)
{
    for(int i=x;i<=maxn;i+=lowbit(i))
    {
        c[i]+=v;
    }
}
long long getSum(int x)
{
    long long sum=0;
    for(int i=x;i>0;i-=lowbit(i))
    {
        sum+=c[i];
    }
    return sum;
}
int reverse_pair(int len)
{
    for(int i=0;i<=len+1;i++)
    {
        c[i]=0;
    }
    long long br[len];
    for(int i=0;i<len;i++)
    {
        br[i]=l1[i];
    }
    int sum=0;
    for(int i=len-1;i>=0;i--)
    {
        update(br[i]+1,1);
        sum+=getSum(br[i]-1+1);
    }
    return sum;
}

int main(void)
{
    long long n;
    long long t;

    cin>>t;
    for(int j=0;j<t;j++)
    {
        cin>>n;
        memset(tested,0,sizeof(tested));
        bool tf=false;
        for(int i=0;i<n;i++)
        {
            cin>>l1[i];
            if(tested[l1[i]]==1)
            {
                tf=true;
            }
            tested[l1[i]]=1;
        }
        if(reverse_pair(n)%2==0||tf)
        {
            cout<<"YES"<<endl;
        }else
        {
            cout<<"NO"<<endl;
        }
    }
    return 0;
}
```
我用的是树状数组来算逆序对，其他方法的比如合并排序也可以o(*￣▽￣*)ブ  

  数据挺水的，不用做离散化也能过(*^_^*)


---

## 作者：氧少Kevin (赞：0)

# CF1591D-Yet Another Sorting Problem
## 题意
给定一个长度为 $n(n\leq 5\cdot 10^5)$ 的序列 $a_1,a_2,\dots,a_n(1\leq a_i\leq n)$。

可以进行如下操作任意次：
- 将 $a_i,a_j,a_k$（$i,j,k$ 互不相等）的值轮换，即将其分别设为 $a_k,a_i,a_j$。

询问能否使其单调不减。

## 思路

考虑三个数字的轮换过程。

### 对于任意三个数字 - 互不相同
- 逆序对数量最多为 $3$。
- 当逆序对数量为 $3$ 时，可以通过变换让逆序对数量变为 $1$。
- 当逆序对数量为 $1$ 时，也可以通过变换让逆序对数量变为 $3$。

- 当逆序对数量为 $2$ 时，可以通过变换让逆序对数量变为 $0$。
- 当逆序对数量为 $0$ 时，也可以通过变换让逆序对数量变为 $2$。

对于任意三个互不相同数字，经过一次变换可以令其逆序对数量 $-2$ 或 $+2$。

因此，如果序列中的元素互不相同，只有逆序对数量为偶数，才可以将序列变为有序。

### 对于任意三个数字 - 其中有两个相同

- 逆序对数量最多为 $2$。

对于任意三个互不相同数字，经过一次变换可以令其逆序对数量 $-1$ 或 $+1$。

因此，如果序列中存在两个相同的数字，那么一定可以将序列变为有序。

---

