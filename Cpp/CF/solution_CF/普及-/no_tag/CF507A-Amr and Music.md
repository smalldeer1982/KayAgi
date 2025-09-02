# Amr and Music

## 题目描述

给定$n$个物品，装进一个容量为$k$的背包，每个物品的价值为$1$，重量为$c[i]$。

求一种选物品的方案，要求所获得的价值最大（可以不装满背包），要求输出选的物品的编号（任意顺序，本题```SPJ```）

## 样例 #1

### 输入

```
4 10
4 3 1 2
```

### 输出

```
4
1 2 3 4```

## 样例 #2

### 输入

```
5 6
4 3 1 1 2
```

### 输出

```
3
1 3 4```

## 样例 #3

### 输入

```
1 3
4
```

### 输出

```
0
```

# 题解

## 作者：Qing_s (赞：4)

## 题解 CF507A 【Amr and Music】

嗯嗯没错又是一道大水题！

题意很明确，所以不在阐述。

但是要注意一点：
>每个物品的价值为 1 ，重量为 c[i] 。

价值是固定的！

所以这道题压根就算不上 dp 。

只是平平常常的 __小暴力__ （没错，它连带暴力都算不上）。

也就是说：

给你 n 个数 ， 让你从中找出 x 个数，使这 x 个数的和不超过 k ，求 x 并把这 x 个数输出。

我们只需要将 n 个数排列一遍。

从小到大累计，直到超过了 k 。

此时输出就可以啦！

详见代码：
```cpp
#include<bits/stdc++.h>

using namespace std ;

int n , k , sum ;
int ans[11010] ;

struct node{
    int s ;\\存数。
    int wz ;\\存编号。
}num[11010] ;

bool cmp( node x , node y ){
    return x.s < y.s ;\\cmp结构体排序。
}

int main(){
    cin >> n >> k ;
    for( int i = 1 ; i <= n ; i++ ){
        cin >> num[i].s ;
        num[i].wz = i ;\\当前输入的顺序就是编号。
    }
    sort( num + 1 , num + n + 1 , cmp ) ;
    for( int i = 1 ; i <= n ; i++ ){
        k -= num[i].s ;
        if( k >= 0 ){\\如果减去后还有剩余空间。
            sum ++ ;\\答案就加一
            ans[sum] = num[i].wz ;\\存入位置。
        }
    }
    cout << sum << endl ;
    for( int i = 1 ; i <= sum ; i++ )
        cout << ans[i] << " " ;\\输出。
    return 0 ;
}
```
为什么要开一个数组存位置？

因为他并不能随时输出，要先输出总共有多少个数，所以才开一个数组存位置。

就很简单，[感觉我还蛮快的。](https://www.luogu.com.cn/record/41014683)

如果不想开数组的话就在结构体里面加个bool型，如果选中了就标记一下，最后输出标记的数就可以啦！

---

## 作者：_桀氓_ (赞：4)

建议更改题目难度为：**普及-**

### 题意：
$n$ 个物品，装进容量为 $k$ 的背包（可以不装满），装进的物品数目要尽量多，输出装进物品的数量并输出它们的编号。

编号顺序任意排列，使用 `Special Judge` 。

### 解析：
这道题乍一看好像是01背包，但由于有了因为价值都为1、可以不装满的条件背包，所以每步的选择没有后效性且局部最优解的总和可以推出全局最优解，于是就可以使用贪心算法来解决。

#### 大概步骤：

1. 读入数据并将数据依物品的重量排序为单调递增形式。

1. 判断背包**剩余容量**与背包外**最小**物品重量的大小，若背包剩余容量 $\geqslant$ 背包外最小物品重量,则将此物品装入背包并更新背包剩余容量。**重复执行**此步骤直至背包剩余容量 $<$ 背包外最小物品重量，此时解为最优。

1. 输出背包内物品数量并按任意顺序输出背包内各物品编号。

### 实现：

因为需要输出物品编号，所以难以使用一维整形数组来进行数据存储与排序。我运用了结构体类型 `priority_queue` （优先队列）来进行数据存储与排序，利用运算符重载来进行自定义排序。

但是，这道题输出要求先输出背包内物品的数量，就导致我们无法边判断边输出~~浪费了大把时间~~，于是我使用了 `stack` 容器来存储各物品编号，在判断完成后再进行输出。

#### 代码：

(437ms,8KB)

```cpp
#include<bits/stdc++.h>
using namespace std;
struct NODE{
	int w,num;
	bool operator <(const NODE&v)const{
		return w>v.w;
        //运算符重载自定义优先队列排序为依重量降序
	}
};
priority_queue<NODE>c;
stack<int>o;
int n,k,ans=0;
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1,ci;i<=n;i++){
		scanf("%d",&ci);
		c.push({ci,i});
	}
	for(int i=1;i<=n;i++)
		if(!c.empty()){
			NODE h=c.top();
			c.pop();
			if(k>=h.w){
				o.push(h.num);//存入物品编号数据
				k-=h.w;
			}
			else
				break;
		}
		else
			break;
	printf("%d\n",o.size());
	while(!o.empty())
	{
		printf("%d ",o.top());
		o.pop();
	}
	return 0;
}
```

---

## 作者：Yaha (赞：3)

### 贪心

（价值全为1是我所没想到的

因为价值都是1，所以每个物品的贡献是一样的。

我们需要数量尽可能多，就需要重量尽可能小。

把重量sort一遍，能加就加，不加退出。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct Nod{
	int weig,id;
}a[120];
int f,cnt,ans[120],n,k;
bool cmp(Nod a,Nod b){
	return a.weig<b.weig;
}
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i].weig);
		a[i].id=i;
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++)
	{
		if(f+a[i].weig>k) break;
		f+=a[i].weig;
		ans[++cnt]=a[i].id;
	}
	printf("%d\n",cnt);
	for(int i=1;i<=cnt;i++) printf("%d ",ans[i]);
	return 0;
}
```



---

## 作者：Ptilopsis_w (赞：3)

# 题意
究极简单的背包  
# 思路
因为每个物品的价值都是 $1$ ，所以我们直接按重量 $c_i$ 排序，能装就装，不能装就停，然后输出装了多少个物品和他们的编号就AC了

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

struct node{
    int cost, num;
    friend bool operator < (const node a, const node b){ return a.cost < b.cost; }
};

int n, k;
node a[105];

int main()
{
    scanf("%d%d", &n, &k);
    for(int i = 1; i <= n; i++)
        scanf("%d", &a[i].cost), a[i].num = i;
    sort(a+1, a+n+1);
    int sum = 0, tot = 0;
    for(int i = 1; i <= n; i++)
    {
        if(sum+a[i].cost > k)
            break;
        else
            sum += a[i].cost, tot++;//sum记录重量和,tot记录装了几个物品
    }
    printf("%d\n", tot);
    for(int i = 1; i <= tot; i++)
        printf("%d ", a[i].num);//直接输出排序后前tot个物品的编号就ok了
    return 0;
}
```

---

## 作者：苏黎世 (赞：3)

### 普及-

我们会发现，对于任意重量，它的价值都是1。

所以说，我们就直接选最小的不就得了吗！

所以就会用到sort。

想到这里，这道题就已经解决了。

具体来看代码：
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
#define rint register int 
const int maxn = 105;
//这是个好习惯，有助于你看数据范围，最好不管简单还是难都写上
int n, m, ans;
struct data
{
	int c;//重量
	int rank;//下标
	
	friend bool operator < (const data a, const data b)
	{
		return a.c < b.c;
	}//用于sort，和cmp是等价的，两者写一个就行
    
}a[maxn];
int main()
{
    scanf("%d%d", &n, &m);
    for(rint i = 1;i <= n; ++i)//写着玩，用int就行了
    {
    	scanf("%d", &a[i].c);
    	a[i].rank = i;
    }
    sort(a + 1, a + n + 1);
    for(int i = 1;i <= n; ++i)
      if(a[i].c <= m)
         m -= a[i].c, ans++;
      else break;//盛不下了
    cout << ans << "\n";
    for(int j = 1;j <= ans; ++j)
      cout << a[j].rank << " ";
    return 0;
}
```


---

## 作者：荷叶下 (赞：2)

## 思路

#### 将重量从小到大排序，尽量多装物品 


------------

## 代码如下
```cpp
#include <bits/stdc++.h> //万能头文件
using namespace std ;

struct node
{
    int st , m ;
};
int n , k , sum ; //sum为能装下的物品数量
node a[110] ;

int cmp( node x , node y )
{
    return x.m < y.m ;
}

int main()
{
    cin >> n >> k ;
    for( int i = 1 ; i <= n ; ++i )
    {
        cin >> a[i].m ;
        a[i].st = i ;
    }
    sort( a + 1 , a + n + 1 , cmp ) ; //按重量从小到大排序
    for( int i = 1 ; i <= n ; ++i )
    {
        if( a[i].m <= k ) //如果容量够装下物品就装
        {
            k -= a[i].m ;
            ++sum ;
        }
        else //装不下则退出循环
            break ;
    }
    cout << sum << "\n" ; 
    for( int i = 1 ; i <= sum ; ++i )
        cout << a[i].st << " " ;
    return 0 ;
}

```
#### 共建和谐洛谷，拒绝CV

---

## 作者：天南星魔芋 (赞：2)

 ~~今天无事，来水一发题解。~~
 

------------

我们看题:

给定 $n$ 个物品，装进一个容量为 $k$ 的背包，每个物品的价值为 $1$ ，重量为 $c[i]$ 。

求一种选物品的方案，要求所获得的价值最大。

这是典型的背包问题。

首先想到用 $01$ 背包。

但，等等。为什么物品价值都为1？

这样就可以用贪心了！

我们先将质量小的放进去 （反正有 $SPJ$ 。

下面上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
int a[120][2];//a[][0] 放质量   a[][1]  放编号 
void kp(int l,int r){//快排  kuaipai 
	int i=l,j=r;
	int mid=a[(l+r)/2][0];
	while(i<=j){
		while(a[i][0]<mid)i++;
		while(a[j][0]>mid)j--;
		if(i<=j){
			swap(a[i][0],a[j][0]);
			swap(a[i][1],a[j][1]);
			i++;j--;
		}
	}
	if(i<r)kp(i,r);
	if(l<j)kp(l,j);
}
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i][0];a[i][1]=i;
	}
	kp(1,n);
	
	int top=0;
	for(int i=1;i<=n;i++){//贪心 
		if(k-a[i][0]>=0)top=i,k-=a[i][0];
	}
	
	cout<<top<<endl;
	
	for(int i=1;i<=top;i++){
		cout<<a[i][1]<<" ";
	}
	cout<<endl;
}
```

这篇题解就到这里了，

我还没写过几次，有不到之处请多多指教。

---

## 作者：damage (赞：2)

# 题意

给定$n$个物品，装进一个容量为$k$的背包，每个物品的价值为$1$，重量为$c[i]$。

求一种选物品的方案，要求所获得的价值最大（可以不装满背包），要求输出选的物品的编号（任意顺序，本题```SPJ```）

### 输入格式 

第一行两个整数$n$，$k$。

第二行$n$个整数，表示每个物品的重量

### 输出格式

输出共两行。

第一行为所选的物品数量。

第二行为所选的物品的编号（任意排列，本题```Special Judge```） 

---

# 题解

直接按照题意$dp$即可（$01$背包）

记录路径的话用一个```bool```型数组```id[i][j]```来记录状态，最后逆序转移状态输出即可

详情见代码

--- 

# 代码 

```cpp
#include<stdio.h>
int n,k,c[110],f[10010]; //价值就是1，不用另开数组了 
bool id[110][10010]; //保存选的物品 
int main()
{
	scanf("%d%d",&n,&k);
	for(register int i=1;i<=n;++i) scanf("%d",&c[i]);
	for(register int i=1;i<=n;++i)
	{
		for(register int j=k;j>=c[i];--j) 
		{
			if(f[j-c[i]]>=f[j]) //等同于 f[j-c[i]]+w[i]>f[j] -> f[j-c[i]]+1>f[j] -> f[j-c[i]]>=f[j]
			{
				f[j]=f[j-c[i]]+1; //等同于 f[j]=f[j-c[i]]+w[i] 
				id[i][j]=true; //记录路径 
			}
		}
	}
	printf("%d\n",f[k]); //输出物品数 
	int x=n,y=k; //赋初始值 
	while(x>0&&y>0)
	{
		if(id[x][y]) //如果选了 
		{
			printf("%d ",x); //输出编号 
			y-=c[x]; //转移到上一个状态 
		}
		--x; //转移到选x-1个物品的情况 
	}
	return 0;
}
```

---

## 作者：Eason_AC (赞：1)

## Content
有一个容量为 $k$ 的背包。有 $n$ 个物品，第 $i$ 个物品的体积为 $c_i$。请求出背包最多能够装下的物品的个数，并输出任意一个方案。

**数据范围：$1\leqslant n,a_i\leqslant 100,0\leqslant k\leqslant 10^4$。**
## Solution
我们很容易想到这样一个贪心的思路：尽量往背包里面塞体积小的物品，这样就保证让能够装下的物品最多。所以，我们按照每个物品的体积从小到大排序，然后依次塞进去，直到塞不进去了为止。注意应该先统计个数，再去统计各个物品的编号。
## Code
```cpp
int n, k, ans;
struct item {
	int val, id;
	bool operator < (const item& ss) const {return val < ss.val;}
}a[107];

int main() {
	getint(n), getint(k);
	_for(i, 1, n) {getint(a[i].val); a[i].id = i;}
	sort(a + 1, a + n + 1);
	_for(i, 1, n) {
		if(k - a[i].val >= 0) k -= a[i].val, ans++;
		else break;
	}
	writeint(ans), puts("");
	_for(i, 1, ans) {
		writeint(a[i].id);
		if(i != ans) putchar(' ');
	}
	return 0;
}
```

---

## 作者：yzh_Error404 (赞：1)

## 题意
给定$n$个物品，装进一个容量为$k$的背包，每个物品的价值为$1$，重量为$c[i]$。
 
## 题解

因为每个物品的价值都相同，所以物品选的越多，价值就越大。

可以直接将物品的重量从小到大排序，用贪心解决。
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
	int no,w;//每个物品的编号和重量
}a[105];
int ans[105],cnt;//答案数组和选过物品的个数
int nowans;//前k个数重量之和(k∈[1,n])
inline bool cmp(node a,node b)
{
	return a.w<b.w;
}
int main()
{
	int n,k;
	scanf("%d%d",&n,&k);
	for(register int i=1;i<=n;i++)
	{
		scanf("%d",&a[i].w);
		a[i].no=i;
	}
	sort(a+1,a+1+n,cmp);//排序
	for(register int i=1;i<=n;i++)
	{
		nowans+=a[i].w;//累加重量和
		if(nowans<=k)ans[++cnt]=a[i].no;//将答案放进数组里
		else break;
	}
	printf("%d\n",cnt);
	for(register int i=1;i<=cnt;i++)
		printf("%d ",ans[i]);
	return 0;
}
```

---

## 作者：shenmadongdong (赞：1)

~~既然没有Pascal的题解，那本蒟蒻来水一发~~

只需将所有物品从小到大排序，然后装到放不下为止即可

代码：
```
var n,k,i,t,j,s:longint;
    a,b,c:array [1..1000] of longint;
begin
  read(n,k);
  for i:=1 to n do read(a[i]);
  for i:=1 to n do b[i]:=i;//标号
  for i:=1 to n-1 do
    for j:=i+1 to n do
      if a[i]>a[j] then begin
        t:=a[i];
        a[i]:=a[j];
        a[j]:=t;
        t:=b[i];
        b[i]:=b[j];
        b[j]:=t;//排序
      end;
  for i:=1 to n do
  begin
    k:=k-a[i];
    if k<0 then break;
    inc(s);
    c[s]:=b[i];
  end;
  writeln(s);
  for i:=1 to s do write(c[i],' ');
end.
```

---

## 作者：Jekyll_Y (赞：1)

### ~~为什么是蓝题呢，建议改成普及-~~
## 题意:
有n个物品，装进一个容量为k的背包，每个物品的价值为1，重量为c[i]。
## 思想:
看起来像01背包，其实因为所有的物品价值为1所以我们只需要排一下顺序然后依次把小的放进去就好了

但是题目中说**可以不装满背包**所以很有可能**k是比n大很多的**（因为没看这而卡了很久）。
## 情况:
有三种情况：设拿a个物品 

第一种：a<n时拿够

第二种: a=n即使把所有的物品拿了后也装不满

第三种：a=n时刚好装满 
## Code:
```c
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
int n,k,ans,now;
struct piece{
	int indx,cost;
}c[110];//结构体存编号和重量 
bool comp(piece xx,piece yy)
{
	return xx.cost<yy.cost;
}//按重量排序（贪心） 
int last[110];//存最后的顺序，因为要先输出数量所以不能边判断边输出 
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>c[i].cost;
		c[i].indx=i;
	}
	sort(c+1,c+n+1,comp);
	while(k>=0&&ans<n)
	{
		ans++;
		k-=c[ans].cost; 
		if(k<0)ans--;//当不能再放时，ans要减1 
		last[ans]=c[ans].indx;
	}
	if(k>0)ans=n;
	/*
	有三种情况：设拿a个物品 
	第一种：a<n时拿够
	第二种: a=n即使把所有的物品拿了后也装不满(因为没判这里卡了很久，突然感觉自己好傻)
	第三种：a=n时刚好装满 
	*/
	cout<<ans<<endl;
	for(int i=1;i<=ans;i++)cout<<last[i]<<" ";
	//输出 
	return 0;
}
```
### AC


---

