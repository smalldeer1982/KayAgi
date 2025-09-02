# Chocolate Bunny

## 题目描述

This is an interactive problem.

We hid from you a permutation $ p $ of length $ n $ , consisting of the elements from $ 1 $ to $ n $ . You want to guess it. To do that, you can give us 2 different indices $ i $ and $ j $ , and we will reply with $ p_{i} \bmod p_{j} $ (remainder of division $ p_{i} $ by $ p_{j} $ ).

We have enough patience to answer at most $ 2 \cdot n $ queries, so you should fit in this constraint. Can you do it?

As a reminder, a permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array) and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 样例 #1

### 输入

```
3

1

2

1

0```

### 输出

```
? 1 2

? 3 2

? 1 3

? 2 1

! 1 3 2```

# 题解

## 作者：_•́へ•́╬_ (赞：9)

### 前置知识

如果 $a>b$，

那么 $a\% b<b$，$b\% a=b$。

### 分析

我们去问交互库 $a[i]\%a[j]$ 和 $a[j]\%a[i]$ 的答案，记为 $x$ 和 $y$。

如果 $a[i]>a[j]$，

那么 $a[i]\%a[j]<a[j]$，$a[j]\%a[i]=a[j]$。

所以 $x<y$，$a[j]=y$。

如果 $a[i]<a[j]$，

那么 $a[i]\%a[j]=a[i]$，$a[j]\%a[i]<a[i]$。

所以 $x>y$，$a[i]=x$。

### 总结

我们去问交互库 $a[i]\%a[j]$ 和 $a[j]\%a[i]$ 的答案，记为 $x$ 和 $y$。

如果 $x<y$，那么 $a[j]=y$。

如果 $x>y$，那么 $a[i]=x$。

### $code$

```cpp
#include<stdio.h>
int a[10001];
main()
{
	register int n;
	scanf("%d",&n);
	for(register int i=1,x,y;i<=n;++i)if(!a[i])
		for(register int j=1;j<=n;++j)if(!a[j]&&i!=j)//不浪费询问次数，只询问不确定值的a[i]和a[j]；i=j肯定不能询问
		{
			printf("? %d %d\n? %d %d\n",i,j,j,i);fflush(stdout);
			scanf("%d%d",&x,&y);
			if(x<y)a[j]=y;
			else{a[i]=x;break;}
		}
	printf("! ");
	for(register int i=1;i<=n;++i)
		if(a[i])printf("%d ",a[i]);
		else printf("%d ",n);//一个奇怪的地方，在下面解释
	fflush(stdout);
}
```

### 关于复杂度

- 每询问两次就能得到一个值，所以肯定可以在 $2n$ 次询问中出解。

- 时间复杂度看上去好像是 $O(n^2)$，其实不是，留給强大的你思考。

- 代码中有一个奇怪的地方，用处就是如果没有找出解，那么输出 $n$。

  为什么会找不出来解呢？又为什么这么肯定它是 $n$ 呢？

  再看看上面的【分析】部分，询问 $a[i]\%a[j]$ 和 $a[j]\%a[i]$ 可以得出 $a[i]$ 与 $a[j]$ 之间的 **较小值**。

  并没有比 $n$ 更大的数，所以找不出解。而其他数都能找出解。

#### ~~闲话~~

~~这是窝第一次写交互题欸。~~

~~deco tql！每次CF都能吊打窝。~~

---

## 作者：rui_er (赞：4)

交互题最好玩♂了！（雾）

题意简述：有一个 $n$ 个数的排列，每次询问 $x,y$ 得到 $a_x\bmod a_y$ 的值，最多使用 $2\times n$ 次询问，猜出这个序列。

---

思路：

看到最多 $2\times n$ 次询问，我们想到了什么？凭我们的直觉，这就是明摆着的提示要询问 $i,j$ 和 $j,i$ 啊！那怎么询问呢？

我们知道对于 $a\lt b$，$a\bmod b=a$，可以得到下面结论：

**结论**：$(a\bmod b\gt b\bmod a)\iff (a\lt b)$。

简单证明：

$$
\begin{aligned}
\operatorname{if}\ a\gt b\ &\operatorname{then}\ (a\bmod b)\lt(b\bmod a)=b\\
\operatorname{if}\ a=b\ &\operatorname{then}\ (a\bmod b)=(b\bmod a)=0\\
\operatorname{if}\ a\lt b\ &\operatorname{then}\ (b\bmod a)\lt(a\bmod b)=a
\end{aligned}
$$

在知道这个性质之后，我们就可以想到询问的方法：

设 $ma$ 为 $a_1\sim a_i$ 中最大的数的下标（大小可根据上面的结论判断），每次询问 $ma,i$ 和 $i,ma$，判断两个结果哪个更大，更新偏小的那个下标的值及最大数的下标。

最后剩下一个 $a_{ma}$ 没有值，由于数列是 $1\sim n$ 的一个排列，因此这个最大的数就是 $n$。

总询问次数 $2\times n-2$。

---

代码：

```cpp
//By: Luogu@rui_er(122461)
#include <bits/stdc++.h>
using namespace std;
const int N = 1e4+5;

int n, a[N], ma = 1;

int ask(int x, int y) {
	int _;
	printf("? %d %d\n", x, y);
	fflush(stdout);
	scanf("%d", &_);
	return _;
}

int main() {
	scanf("%d", &n);
	for(int i=2;i<=n;i++) {
		int _1 = ask(ma, i);
		int _2 = ask(i, ma);
		if(_1 > _2) {
			a[ma] = _1;
			ma = i;
		}
		else a[i] = _2;
	}
	a[ma] = n;
	putchar('!');
	for(int i=1;i<=n;i++) printf(" %d", a[i]);
	return 0;
} 
```

---

## 作者：SFlyer (赞：0)

很可爱啊。

第一种想法也许是先确定 $n$ 的位置，但是发现很难确定。

$2n$ 次操作也就说明要用两个操作确定一个数。我们发现当 $a<b$ 时，$a\bmod b$ 就等于 $a$。因而有一个想法：询问 $(a,b),(b,a)$，确定较小者。

设 $a\equiv x\pmod b,b\equiv y\pmod a$，则如果 $a<b$，$a=x,b=x+y$ 前提条件 $x>y$。所以我们可以通过判断 $x,y$ 的大小确定 $a,b$ 当中的一个。

---

## 作者：TTpandaS (赞：0)

由于是排列，所以数两两不同。有两个数 $x,y$，如果 $x \bmod y > y \bmod x$ ，那么 $x \bmod y =x$，因为 $y \bmod x < x$。

所以先把所有位置存入队列，每次去除前两个进行询问，就可以得到一个位置的数的大小，将另一个放回队列。如果队列只剩一个数，那么一定是最大值 $n$。

每两次操作就能确定一个数，所以总共 $2n$ 次操作即可。

---

## 作者：I_will_AKIOI (赞：0)

手玩样例可知，对于整数 $a,b$，若 $a<b$，则 $a\bmod b=a$。所以我们考虑查询一下 $a\bmod b$ 和 $b\bmod a$，但是怎么判断 $a$ 和 $b$ 哪个数比较小？假设当前 $a<b$，由于余数小于除数，所以 $b\bmod a<a$，而 $a\bmod b=a$，所以 $a\bmod b>b\bmod a$。换句话说，就是取模后较大的那个数和询问的结果相同。

有了这个结论，每次我们可以询问 $a_i$ 和 $a_{i+1}$，就可以得出这二者之一的值。那么没得出值的怎么办？我们可以把没得出答案的东西再询问一遍，一直循环直到没有不知道的为止。每次 $a$ 的长度会减半，所以只会询问 $\log n$ 轮，最大询问总数就是 $\displaystyle n+\frac{n}{2}+\frac{n}{4}\dots+1=2n-1$ 次，可以通过本题。

如果 $n$ 为奇数，那么会有一个数落单没法询问，题目说 $a$ 是一个 $1\sim n$ 的排列，所以最后没出现这个数的值就是 $1\sim n$ 中从未出现过的数。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans[10005],vis[10005];
vector<int>u,v;
int main()
{
  ios::sync_with_stdio(0);
  cin>>n;
  for(int i=1;i<=n;i++) v.push_back(i);
  while(v.size()>1)
  {
    u.clear();
    for(int i=0;i<v.size()-1;i+=2)
    {
      int x,y;
      cout<<"? "<<v[i]<<" "<<v[i+1]<<endl;
      cin>>x;
      cout<<"? "<<v[i+1]<<" "<<v[i]<<endl;
      cin>>y;
      if(x>y) ans[v[i]]=x,u.push_back(i),vis[x]=1;
      else ans[v[i+1]]=y,u.push_back(i+1),vis[y]=1;
    }
    for(int i=u.size()-1;i>=0;i--) v.erase(v.begin()+u[i]);
  }
  if(v.size()==1)
  {
    for(int i=1;i<=n;i++) if(vis[i]==0)
    {
      ans[v[0]]=i;
      break;
    }
  }
  cout<<"! ";
  for(int i=1;i<=n;i++) cout<<ans[i]<<" ";
  cout<<endl;
  return 0;
}
```

---

## 作者：HeCao2008 (赞：0)

给出一种和 [tourist](https://search.bilibili.com/all?keyword=tourist&from_source=webtop_search&spm_id_from=333.1007&search_source=5) 一样的解法。

[更好的阅读体验](https://www.luogu.com.cn/blog/C-SHANGHAI/solution-cf1407c)

[题目传送门](https://www.luogu.com.cn/problem/CF1407C)

### 思路

一道**交互**题，实际上本题并不难，可能是因为题目类型比较新颖才让它到了绿的难度。

不难发现，对于两个数 $a$ ，$b$ ：

我们设定一下， $a>b$ :

那么，$ a\mod  b$  一定是小于 $b$ 的，原因是余数一定小于除数。

同样的，交换一下，发现 $b\mod a$ 一定等于 $b$，原因显然。

经过比较，得到 $a\mod b < b\mod a$。 

那么，我们只需要比较这两个余数，那么我们就会成功地得到，$b$ 就是两个余数中较大的那个。

而题目说，最多使用 $2n$ 次询问，正巧，按照这个做法询问次数正好等于 $2n$ ，即可得解。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=114514;
int solve(int i,int j){
	cout<<"? "<<i+1<<" "<<j+1<<endl;
	int ans;
	cin>>ans;
	return ans;
} //交互部分，注意了，因为我这里 l 的初始值为 0，为了避免 RE，所以这里两者都 +1，然而显然的，这个操作并不影响模运算
int a[maxn];
int main(){
	int n;
	cin>>n;
	int l=0;
	for(int r=1;r<n;r++){
		int aa=solve(l,r);
		int b=solve(r,l);
		if(aa>b){
			a[l]=aa;
			l=r; //更新值
		}else a[r]=b;
	}
	a[l]=n;  //此时，最后一个值即为 n
	cout<<"!";
	for(int i=0;i<n;i++)cout<<" "<<a[i];
	return 0;
}
```

---

## 作者：cyhtxdy (赞：0)

中规中矩的交互题，建议评为黄题。



------------


观察题目限制次数，最多 $2n$ 次，这提示我们也许确定一个位置需要两次询问。

顺着往下进行分析。

记 $a_i \bmod a_j=p, a_j \bmod a_i = q$。

当 $a_i > a_j$ 时： $p < a_j, q = a_j$。那么，若 $p<q$ 则 $a_j=q$。

当 $a_i<a_j$ 时： $p=a_i,q<a_i$。 那么，若 $p>q$ 则 $a_i=p$。

于是我们可以枚举每一对数字，根据上述思路得到最终答案。

为了减少询问次数，若一个数字已经被确定，就可以跳过。

得到代码：
```
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 1e4 + 7;

int n, a[N];

int main () {
	cin >> n;
	for (int i = 1; i <= n; i ++) {//枚举每对数字
		if (!a[i]) {//如果没有被确定
			for (int j = 1; j <= n; j ++) {
				if (!a[j] && i != j) {//如果没有被确定并且不是同一个数字
					cout << "? " << i << " " << j << endl;
					cout << "? " << j << " " << i << endl;
					int p, q;
					cin >> p >> q;
					if (p < q) {
						a[j] = q;
					}
					else {
						a[i] = p;
						break;
					}
				}
			}
		}
	}
	cout << "! ";
	for (int i = 1; i <= n; i ++) {
		if (a[i]) {
			cout << a[i] << " ";
		}
		else {
			cout << n << " ";
		}
	}
	cout << endl;
	return 0;
}
```

注意到，因为 $n$ 为最大值，所以通过上述思路是没有办法得出 $n$ 的。所以在最后输出答案时，需要特判 $n$。


---

## 作者：HPXXZYY (赞：0)

$\color{blue}{\texttt{[Solution]}}$

可以询问两个数 $(i,j)$，我们先询问 $a_{i} \mod a_{j}$，记为 $x$，再询问 $a_{j} \mod a_{i}$，记为 $y$。

- 当 $a_i < a_j$ 时，我们可以知道 $a_{i}=x$，但是 $y<a_{i}$，即 $y<x$。
- 当 $a_{i}>a_{j}$ 时，同理，$a_{j}=y,x<a_{j}$，即 $x<y$。

所以我们可以通过判断 $x,y$ 的大小来判断 $a_{i}$ 或者 $a_{j}$ 的值，即：

- 当 $x<y$ 时，$a_{j}=y$。
- 当 $x>y$ 时，$a_{i}=x$。

即**每次询问我们可以知道 $a_{i},a_{j}$ 中的较小的一个数字**。

所以我们从前往后扫一遍，记区间 $[1,i-1]$ 中尚未知道的数字（即最大的那个数字）是 $a_{\texttt{sub}}$，询问 $(\texttt{sub},i)$ 间的关系。这样，我们只需要 $2(n-1)$ 次询问即可得到原排列。

最后注意三点：

1. 最后，原排列中最大的数字我们是不知道的，要特判。
2. 这个算法当 $n=1$ 时会失效，所以特判 $n=1$。
3. 输入输出的格式。

$\color{blue}{\texttt{[code]}}$

```cpp
int n,sub,a[10100];
int main(){
	scanf("%d",&n);sub=1;
	if (n==1){printf("! 1");return 0;}
	for(int i=2,x,y;i<=n;i++){
		printf("? %d %d\n? %d %d\n",sub,i,i,sub);
		fflush(stdout);//清空输出文件的缓存 
		scanf("%d%d",&x,&y);
		if (x<y) a[i]=y;
		else a[sub]=x,sub=i;
		if (i==n) a[sub]=n;
	}
	printf("!");
	for(int i=1;i<=n;i++)
		printf(" %d",a[i]);
	fflush(stdout);
	return 0;
}
```

---

## 作者：duyi (赞：0)

# CF1407C Chocolate Bunny

[题目链接](https://codeforces.com/contest/1407/problem/C)

记 $q(i, j)$ 表示通过一次询问求出的 $p_i\bmod p_j$ 的值。

---

考虑两个数 $x, y$，不妨设 $x < y$，那么：$x\bmod y = x$，$y \bmod x < x$。

也就是说，通过 $(x, y)$, $(y, x)$ 这样两次询问，我们可以获得的信息是：

- 两个数的大小关系。
- 较小的那个数的值。

我们依次扫描整个序列。维护一个变量 $i$ 表示当前**前缀最大值**所在的位置。初始时 $i = 1$。设当前扫描到的位置为 $i'$。通过两次询问 $q(i', i)$ 和 $q(i, i')$：

- 如果 $q(i', i) > q(i, i')$，说明 $p_{i'} < p_{i}$，且 $p_{i'} = q(i', i)$。
- 如果 $q(i', i) < q(i, i')$，说明 $p_{i'} > p_{i}$，且 $p_{i} = q(i, i')$。记下 $p_{i}$ 的值。然后令 $i\gets i'$。

全部扫描完成后，最终的 $i$，就是 $n$ 所在的位置。且其他位置的值都已经确定。

共需要 $2n - 2$ 次询问。

[参考代码-在CF查看](https://codeforces.com/contest/1407/submission/106331175)





---

## 作者：walk_alone (赞：0)

（第一次写难度超过1500的题，纪念一下）

其实拿到这个题，想到取模，应该就不难发现：只要我们对两个数进行相互取模，就可以求出较小的值。下证：

不妨设$a>b$，询问$? ~~a~~ b$时，答案一定小于$b$；询问$? ~~b~~ a$时，由于$a>b$，$b ~mod~ a=b$，所以两次询问中大者为询问二者较小的值。

那显然我们可以通过这个方法，用$n$次判断出这个数列一半的值。那剩下的怎么办？

鄙人不才，在这里提供一个复杂的方法：线段树。

为什么会想到线段树？注意到$2n$这个条件。第一次我们使用了$n$次，第二次我们依旧想到继续对剩下一半的数进行同样的操作（分治的思想），由于数据规模减半，这一轮我们只需要$n/2$次操作，以此类推，$n/4$,$n/8$…………由数列的极限可以知道，如此进行下去操作总数就是$2n$！

那这和线段树有什么关系？不断地二分！我们回想一下一颗满二叉树的结构，如果我们把原数列摆在最下面，每一次操作的实质其实是比出较小值，让未知值向上传递（代码中pushup函数），代表这个区间**唯一**的未知数。每一个子节点的父节点其实是两者中未知的值，而我们每次询问的对象就是一个节点左右儿子对应的数组下标。此处可以不是满二叉树，但是我这里为了方便处理我就采取满二叉树写法。

这只是个基本思想，还有非常多的细节需要处理：

1、只有一个儿子怎么办？

直接pushup即可，因为一个数无法比较，应当上传至上一个层次进行处理。比如15个数，第15个数其实是最后上升到9-16这个层次去与1-8的未知数比较的。

2、步长如何处理：

每次其实存在两个未知数的区间是在以2的次方速度增长，所以我定义了一个step变量来记录步长，每次操作即是$(i,i+(1<<step)-1)$

其实难的主要是构造线段树的思想，下附代码。思路清晰应该不需要注释了。

```cpp
//full segment tree
#include <cstdio>
#include <algorithm>
using namespace std;
struct node
{
    bool is_leftson;
    bool is_rightson;
    int start;
    int ed;
    bool upload;//whether leftson or rightson upload their value
    int father;
    int position;
};
struct node tree[80005];
struct flag
{
    bool exist;
    int first;
    int first_trans;
    int second;
    int second_trans;
};
struct flag now;
int num[20005],n,book[10005];
void build(int place,int left,int right)
{
    if(left==right)
    {
        if(left<=n)
            tree[place].position=left;
        tree[place].start=tree[place].ed=left;
        return;
    }
    int mid=(left+right)>>1;
    build(place<<1,left,mid);
    build(place<<1|1,mid+1,right);
    tree[place].is_leftson=1;
    if(tree[place<<1|1].start<=n)
        tree[place].is_rightson=1;
    tree[place<<1].father=tree[place<<1|1].father=place;
    tree[place].start=tree[place<<1].start;
    tree[place].ed=tree[place<<1|1].ed;
    return;
}
void pushup(int place)
{
    tree[tree[place].father].position=tree[place].position;
    if(tree[tree[place].father].start==tree[place].start)
        tree[tree[place].father].upload=0;
    else
        tree[tree[place].father].upload=1;
}
void pushdown(int place,int x)
{
    num[tree[place].position]=x;
}
void query(int place,int left,int right,int ask_start,int ask_end)
{
    if(left==ask_start && right==ask_end)
    {
        if(!tree[place].is_rightson)
        {
            pushup(place<<1);
            now.exist=0;
            return;
        }
        else
        {
            now.exist=1;
            now.first=tree[place<<1].position;
            now.first_trans=place<<1;
            now.second=tree[place<<1|1].position;
            now.second_trans=place<<1|1;
            return;
        }
    }
    int mid=(left+right)>>1;
    if(tree[place<<1].ed>=ask_end)
        query(place<<1,left,mid,ask_start,ask_end);
    if(tree[place].is_rightson && tree[place<<1|1].start<=ask_start)
        query(place<<1|1,mid+1,right,ask_start,ask_end);
    return;
}
int main()
{
    scanf("%d",&n);
    int th=1;
    while(th<n)
        th<<=1;
    build(1,1,th);
    int step=1;
    while((1<<step)<=th)
    {
        for(int i=1;i<=n;i+=(1<<step))
        {
            query(1,1,th,i,i+(1<<step)-1);
            if(!now.exist)
                break;
            else
            {
                int a,b;
                printf("? %d %d\n",now.first,now.second);
                fflush(stdout);
                scanf("%d",&a);
                printf("? %d %d\n",now.second,now.first);
                fflush(stdout);
                scanf("%d",&b);
                if(a>b)
                {
                    num[now.first]=a;
                    book[a]=1;
                    pushup(now.second_trans);
                }
                else
                {
                    num[now.second]=b;
                    book[b]=1;
                    pushup(now.first_trans);
                }
            }
        }
        step++;
    }
    for(int i=1;i<=n;i++)
        if(!book[i])
        {
            num[tree[1].position]=i;
            break;
        }
    printf("!");
    for(int i=1;i<=n;i++)
        printf(" %d",num[i]);
    return 0;
}

```
还有，文中的fflush(stdout)的操作不是很会，参考了他人关于这里的代码，还望各位大佬海涵。

---

## 作者：onglu (赞：0)

## C. Chocolate Bunny  
### 题目大意  

交互题，要求猜一个$p(1,n)$的排列，一开始给定$n$，至多可以询问$2n$次，每次询问给出$(i,j)$系统会回答$p_{i} \bmod p_{j}$，最后要求输出猜到的排列。

### 思路  
~~第一次做交互题，因为没刷新缓冲区WA了三发~~  

考虑假如询问$i,j$会获得哪些信息呢？  
先可以想到$ans \leq p_i$，$ans\leq p_j$。  
但是好像没有用？
顺着这个思路往下想，如果正着询问一遍，反着询问一遍，那么获得的答案必定一大一小。  
我们假设已经知道了$p_i < p_j$，那么$p_i \bmod p_j = p_i$，而$p_j \bmod p_i < p_i$。  
于是我们就知道了比较大的那个答案就是那次运算中排在前面的那个数。  
只需要$2(n - 1)$次询问就可以获得所有的值了。  
  
### 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

int read(){
	char c; int num, f = 1;
	while(c = getchar(),!isdigit(c)) if(c == '-')f = -1; num = c - '0';
	while(c = getchar(), isdigit(c)) num = num * 10 + c - '0';
	return num * f;
}
int n, lst, p[10009], vis[10009];
int main()
{
	scanf("%d", &n);
	lst = 1;
	for(int i = 2; i <= n; i++){
		int a, b;
		printf("? %d %d\n", lst, i);
		fflush(stdout);
		scanf("%d", &a);
		printf("? %d %d\n", i, lst);
		fflush(stdout);
		scanf("%d", &b);
		if(a > b){
			p[lst] = a;
			lst = i;
			vis[a] = 1;
		}else p[i] = b, vis[b] = 1;
	}
	printf("! ");
	for(int i = 1; i <= n; i++){
		if(p[i] > 0)printf("%d%c",p[i], (i == n)?'\n':' ');
		else {
			for(int j = 1; j <= n; j++)if(!vis[j])
				printf("%d%c",j, (i == n)?'\n':' ');
		}
	}
	return 0;
}
```

---

## 作者：LeavingZzz (赞：0)

## $\mathsf{Solution\space For\space CF1407C}$  
### $\mathsf{Description}$  
交互题。  
你需要猜出一个长度为 $n$ 的**排列** $a$，为了完成这个，你可以询问最多 $2\cdot n$ 次，每次询问两个下标 $i,j$，然后你可以读入一个 $k$，$k=a_i\bmod a_j$。  

询问格式如下：  
`? x y` 其中 $x,y$ 是询问的下标  

当你能确定这个排列时，输出：  
`! p1 p2 ....` 即在 `!` 后输出这个排列，数字间用空格隔开  
### $\mathsf{Analysis}$  
先确定目标：我们要找到 $n$ 所在的位置，这样就能直接得到其他元素的值（$a_i\bmod n=a_i(a_i<n)$）  

又可以发现，如果我们询问一次 $i,j$ 再询问一次 $j,i$，一定能得到 $a_i,a_j$ 中较小的那一个的值  
所以我们询问 $\dfrac{n}{2}$ 对这样的 $i,j$，一定能够得到一个大于 $\dfrac{n}{2}$ 数字的位置，这里用去 $n$ 次询问  
（这里是大概率直接能够获知一个大于 $\dfrac{n}{2}$ 元素的值以及位置，当然如果比较非，确定的 $\dfrac{n}{2}$ 个元素恰好是 $1->\dfrac{n}{2}$ 的话，从没确定的元素中随便取一个也一定是大于 $\dfrac{n}{2}$ 的）

得到一个大于 $\dfrac{n}{2}$ 的数字有什么用呢？  

当然是为了找到 $n$ 了  

对于任意的 $a_i>\dfrac{n}{2}$，排列中 $\bmod a_i$ 等于 $n\bmod a_i$ 的元素个数一定为 $2$ ，一个是 $n\bmod a_i$，另外一个就是 $n$  

所以我们抓住一只大于 $\dfrac{n}{2}$ 的元素，设他为 $k$，询问未确定的所有元素 $\bmod k$ 的值，找到余数等于 $n\bmod k$ 的元素，由于最开始的 $n$ 次询问中不可能能将 $n$ 确定下来（只能确定较小的，$n$ 一定不是较小的），所以 $n$ 一定在剩下的的未确定元素之中，所以这 $\dfrac{n}{2}-1$ 次询问中能找到 $1$ 个或者 $2$ 个可能为 $n$ 的数字，如果是一个，那就是 $n$，如果是两个，那么对他们两个询问一次也能确定谁是 $n$。  

确定谁是 $n$ 之后，再进行至多 $\dfrac{n}{2}-1$ 次询问即可确定所有元素  

文字叙述可能会比较抽象或者不够细节，代码会有注释的QwQ  
### $\mathsf{Code}$  
```
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cctype>
#include<iostream>
using namespace std;
typedef long long LL;
const int maxn=10007;
int N;
int A[maxn],r[maxn];
void ask(int i,int j)
{
    cout<<"? "<<i<<' '<<j<<endl;
    cout.flush();
    return ;
}
int main()
{
    cin>>N;
    int t1,t2;
    for(int i=1;i<=N/2;i++)
    //首先进行N次询问，确定N/2个元素的具体值
    {
        ask(i,N-i+1);
        cin>>t1;
        ask(N-i+1,i);
        cin>>t2;
        if(t1>t2) A[i]=t1;
        else A[N-i+1]=t2;
    }
    int p=0,t=0;
    for(int i=1;i<=N;i++)
    //尝试找到一个大于N/2的元素
    if(A[i]>t) t=A[i],p=i;

    if(t>N/2)
    //已经确定的元素中存在一个大于N/2的
    {
        int pn1=0,pn2=0;
        //可能是N的两个位置
        for(int i=1;i<=N;i++)
        {
            if(A[i]) continue;
            ask(i,p);
            cin>>r[i];
            if(r[i]==N%t) pn1=i,swap(pn1,pn2);
        }
        //如果只存在一个位置可能为N，那么在pn2
        //如果pn1不为0说明有两个可能位置，要去掉一个
        if(pn1)
        {
            ask(pn1,pn2);
            cin>>p;
            if(p<N%t) swap(pn1,pn2);
            //假如a[pn1]%a[pn2]<N%t 说明pn2不是N
        }
        A[pn2]=N;
        for(int i=1;i<=N;i++)
        {
            if(A[i]) continue;
            ask(i,pn2);
            cin>>A[i];
        }
        cout<<"! ";
        for(int i=1;i<=N;i++)
            cout<<A[i]<<' ';
    }
    else
    //比较非，没有第一时间确定大于N/2的元素
    {
        for(int i=1;i<=N;i++)
            if(!A[i]) {p=i;break;}
        //随意找一个未确定元素它一定大于N/2
        for(int i=1;i<=N;i++)
        {
            if(A[i]||i==p) continue;
            ask(i,p);
            cin>>r[i];
            t=max(r[i],t);
            //可以从剩下元素的询问中得到随意找的那个元素的值
        }
        ++t;
        A[p]=t;
        for(int i=1;i<=N;i++)
        {
            if(A[i]) continue;
            //由于一开始确定的元素都是小于等于N/2的
            //这里出现的r[i]=N%t的a[i]一定为N
            if(r[i]==N%t)
            {
                //找到N之后询问未确定的元素
                p=i;A[p]=N;
                for(int k=1;k<=N;k++)
                {
                    if(A[k]) continue;
                    ask(k,p);
                    cin>>A[k];
                }
            }
        }
        //------------------
        //特殊情况，如果最开始选取的大于N/2的元素就是N
        //那么后面计算的余数就是其真实值
        //不用这一步的话，由于找不到N会有一些元素是0
        for(int i=1;i<=N;i++)
        if(!A[i]) A[i]=r[i];
        //------------------
        cout<<"! ";
        for(int i=1;i<=N;i++)
            cout<<A[i]<<' ';
    }
    return 0;
}
```


---

