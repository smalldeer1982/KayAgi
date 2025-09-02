# 『MdOI R4』Fun

## 题目背景

去 NOIP 考场时有两个优良传统：打狼和喝快乐水。这两项活动都能给同学们带来快乐。

## 题目描述

VG 的学校有 $n$ 个人要去考 NOIP。

每个人有一个交通方式，第 $i$ 个人的交通方式为 $t_i$，$t_i=1$ 表示这个人坐学校大巴，$t_i=0$ 表示这个人自己去考场。

每个人有一个颓废值，第 $i$ 个人的颓废值为 $q_i$，$q_i=1$ 表示这个人愿意打狼，$q_i=0$ 表示这个人不愿意打狼。

每个人去考场时会买一瓶快乐水，但如果坐大巴且愿意打狼的人数（即满足 $t_i=1$ 且 $q_i=1$ 的 $i$ 个数）$k$ 不小于 $m$，则这 $k$ 个人只需要买 $m$ 瓶快乐水。

现在，VG 统计出了所有人的交通方式和颓废值，他请你帮他求出最终所有人买快乐水的总瓶数。

## 说明/提示

【样例解释 #1】

三个人的情况如下：

- 第 $1$ 个人乘坐大巴但不打狼；

- 第 $2$ 个人打狼但不乘坐大巴；

- 第 $3$ 个人乘坐大巴而且打狼。

所以，只有 $1$ 个人既乘车又打狼，满足不小于 $m$ 的条件，故对于这 $1$ 个人需要购买 $m$ 瓶快乐水，剩下 $2$ 个人购买 $2$ 瓶快乐水，总共须购买 $3$ 瓶快乐水。

【数据规模与约定】

**本题不采用捆绑测试**

| 测试点编号 |   $n,m$    | $type$ |   $t_i$    |   $q_i$    |
| :------: | :--------: | :----: | :--------: | :--------: |
|   $1$    |  $\le 30$  |  $=0$  |    $=0$    |    $=0$    |
|   $2$    |  $\le 70$  |  $=0$  |    $=0$    |    $=0$    |
|   $3$    |  $\le 30$  |  $=1$  |    $=1$    |    $=1$    |
|   $4$    |  $\le 70$  |  $=1$  |    $=1$    |    $=1$    |
|   $5$    |   $n=m$    |  $=2$  | 无特殊限制 | 无特殊限制 |
|   $6$    |   $n=m$    |  $=2$  | 无特殊限制 | 无特殊限制 |
|   $7$    |   $n=m$    |  $=2$  | 无特殊限制 | 无特殊限制 |
|   $8$    | 无特殊限制 |  $=3$  | 无特殊限制 | 无特殊限制 |
|   $9$    | 无特殊限制 |  $=3$  | 无特殊限制 | 无特殊限制 |
|   $10$   | 无特殊限制 |  $=3$  | 无特殊限制 | 无特殊限制 |

对于 $100\%$ 的数据，$1 \le m \le n \le 100$，$t_i,q_i \in \{0,1\}$，$type \in \{0,1,2,3\}$。

## 样例 #1

### 输入

```
3 1 3
1 0 1
0 1 1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3 1 3
1 1 1
0 1 1
```

### 输出

```
2
```

# 题解

## 作者：Thomas_Cat (赞：21)

由题意，现命 $a_i$ 表示是或否符合题目条件 $(t_i=q_i=1,a_i \in {0,1})$，现只需让 $\sum\limits_{i=1}^n a_i \ge m$ 即可。

因此我们只需要使用 `for` 在过程中输入并判断，复杂度为 $\mathcal{O}(nT)$，稳过。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n,m,type,sum=0;
    cin>>n>>m>>type;
    int a[10001],b[10001];
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) cin>>b[i];
    for(int i=1;i<=n;i++)
        if(a[i]==b[i]&&a[i]==1) sum++;//输入之后判断 a_i=1 的个数
    if(sum>m) cout<<m+n-sum;
    else cout<<n;
    return 0;
}
```

注：`type` 无意义，不用考虑即可。

---

## 作者：VinstaG173 (赞：7)

官方题解（雾

### Description

给定两个长度为 $n$ 的由 $0,1$ 构成的数组 $t_i,q_i$ 和数 $m$，求出满足 $t_i=q_i=1$ 的 $i$ 的个数 $k$，当 $k<m$ 时输出 $n$，否则输出 $n-k+m$。（人话题面

数据范围 $ \le m \le n \le 100$。

### Solution

人口普查题。~~由于现实中并没有凑成狼所以输出 $n$ 即可~~

$\texttt{type=0:}$ 由于 $t_i=q_i=0$，显然 $k=0<m$，输出 $n$ 即可得到这 $20$ 分。

$\texttt{type=1:}$ 由于 $t_i=q_i=1$，显然 $k=n \ge m$，输出 $m$ 即可得到这 $20$ 分。

$\texttt{type=2:}$ 由于 $n-m$，无论 $k$ 为何值，答案均为 $n$。输出 $n$ 即可得到这 $30$ 分。

$\texttt{type=3:}$ 直接模拟，用循环计算 $k$，然后判断输出即可。

本题非常简单，考察了循环和判断等基础语法的使用，并设置了代码极短、分数可观且性质优美的部分分，为良心出题人点赞！（我好菜啊

（说好的 MdOI $O(n)$ 过 $100$ 题

std 就不放了（

---

## 作者：_caiji_ (赞：3)

### 题意简述
给定整数 $n,m$ 和两个数列 $t,q$，请统计出满足 $t_i=1$ 且 $q_i=1$ 的 $i$ 的个数，记为 $k$。

如果 $k\geq m$，输出 $m+(n-k)$，否则输出 $n$。

$1\leq m\leq n\leq 100$。

### 题目分析
按题意模拟即可。

如果看不懂长长的题面，可以看上面的题意简述。

### AC 代码
```cpp
#include <cstdio>
using namespace std;
int n,m,k,a[1010],b[1010];
int main(){
    scanf("%d%d%*d",&n,&m);//"%*d"是scanf的一种用法，表示读取这个数但不存储
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++) scanf("%d",&b[i]);
    for(int i=1;i<=n;i++) if(a[i]==1&&b[i]==1) k++;
    printf("%d",k>=m?m+n-k:n);
    return 0;
}
```

---

## 作者：囧仙 (赞：2)

## 题解

显然只要统计出有多少人既坐大巴且愿意打狼的人数 $k$ ，然后比较这些人一起购买 $m$ 瓶快乐水是否能更优即可。当人数不足 $m$ 人时，每个人需要购买一瓶，答案为 $n$ ；否则为 $n-k+m$ 。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define up(l,r,i) for(int i=l,END##i=r;i<=END##i;++i)
#define dn(r,l,i) for(int i=r,END##i=l;i>=END##i;--i)
using namespace std;
typedef long long i64;
const int INF =2147483647;
const int MAXN=1e6+3;
int n,m,T[MAXN],Q[MAXN];
int qread(){
    int w=1,c,ret;
    while((c=getchar())> '9'||c< '0') w=(c=='-'?-1:1); ret=c-'0';
    while((c=getchar())>='0'&&c<='9') ret=ret*10+c-'0';
    return ret*w;
}
int c;
int main(){
    n=qread(),m=qread(),qread();
    up(1,n,i) T[i]=qread(); up(1,n,i) Q[i]=qread();
    up(1,n,i) c+=(T[i]&&Q[i]);
    if(c>=m) printf("%d\n",n-c+m); else printf("%d\n",n);
    return 0;
}
```

---

## 作者：tytyty (赞：2)

## 题意
对于第 $i$ 个人，如果$t_i=1$ 且 $q_i=1$，则 $k\gets k+1$。

如果 $k\ge m$，$ans=m+(n-k)$；

否则 $ans=n$。
## 思路
根据题意模拟即可。
1. 输入 $n$ 个人的交通方式和颓废值。
1. 统计 $t_i=1$ 且 $q_i=1$ 的人数 $k$。
1. 如果 $k\ge m$，$ans=m+(n-k)$,否则 $ans=n$。
1. 输出 $ans$。

(ps:因为正解不依赖于 $type$，所以不管它)
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,type,t[105],q,k,ans; 
int main()
{
	cin>>n>>m>>type;
	for(int i=1;i<=n;i++)
	{
		cin>>t[i];
	}
	for(int i=1;i<=n;i++)
	{
		cin>>q;
		t[i]+=q;
		if(t[i]==2) k++;//如果t=1且q=1,则t+q=2
	}
	if(k>=m)
	{
		ans=m+(n-k);
	}
	else 
		ans=n;
	cout<<ans;
	return 0;
}
```
 **THE END.**
 
 **THANK YOU.**

---

## 作者：Asdonel (赞：2)

# 题目简意
- 有 $n$ 个 $t_i,q_i$。
- $1 \le m \le n \le 100$，$t_i,q_i \in \{0,1\}$，$type \in \{0,1,2,3\}$。
# 解题思路
红题没什么好说的……
1.  统计 $t_i$，$q_i$ 都为 $1$ 的个数 $sum$。
2. 如果大于 $m$，输出 $n$。
3. 否则输出 $(n-sum)+m$。

即可。

# CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
ll  n,m,type,sum;
struct node{
	int q,t;
}a[100000];
inline ll read(){
	char ch=getchar();
	ll sum=0,cf=1;
	while(ch<'0'||ch>'9'){
		if(ch=='-')cf=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		sum=(sum<<3)+(sum<<1)+(ch^48);
		ch=getchar();
	}
	return cf*sum;
}
int main(){
	n=read(),m=read(),type=read();
	for(ll i=1;i<=n;i+=1)a[i].t=read();
	for(ll i=1;i<=n;i+=1)a[i].q=read();
	for(ll i=1;i<=n;i+=1){
		if(a[i].t&&a[i].q)sum+=1;
	}
	if(sum>=m)printf("%lld\n",(n-sum)+m);
	else printf("%lld\n",n);
	return 0;
}
```


---

## 作者：JoseTony (赞：2)

# 思路
这道题作为月赛的第一题还是非常的简单，理解了题意其实不难做对。但是在理解题意的时候可能会有一些坑。如果既打狼又坐大巴的人满足要求，那么是每人一共需要 $m$ 瓶快乐水，而非每人都需要 $m$ 瓶。不满足要求的情况每人只需一瓶，因此输出 $n$ 即可。我们只需要用一个数组来储存坐大巴和打狼的人数，如果出现两个数组同一个位置都是 $1$ 的情况，那么计数器加一，然后再判断即可。有一点要注意的是，这道题中 $k$ 不能大于 $n$，也就是说可以两数相等，特判时要注意。$type$ 变量实际上在这里没有什么用，只读入即可。拿 $70$ 分的同学注意一下数组的读入顺序。
# 代码
```cpp

#include<iostream>
using namespace std;
int a[100001];
int b[100001];
int main(){
    int n,m,type,cnt=0,sum=0;
    cin >> n >> m >> type;
    for(int i=0;i<n;i++){
        cin >> a[i];//读入a数组，去考场的方式
        
    }
    for(int i=0;i<n;i++){
        cin >> b[i];//读入b数组，是否打狼
    }
    for(int i=0;i<n;i++){
        if(a[i]==1&&b[i]==1){
            cnt++;//如果既坐大巴又打狼，计数器加一
        }else{
            sum++;//另外的情况另一个计数器加一
        }
    }
    if(cnt>=m){
        cout << m+sum << endl;//直接用sum加上m即可
    }else if(cnt < m){
        cout << n << endl;//每人买一瓶，输出n
    }
    
    return 0;//程序结束
}
```


---

## 作者：奥斯卡小冰人 (赞：1)

快乐水的总瓶数取决于打狼和坐大巴的人数。
- 如果打狼和坐大巴的人数 $k$ 大于等于 $m$ 人，那么这 $k$ 个人就用 $m$ 瓶快乐水，剩下的 $n - k$  个人一人一瓶
- 如果 $k$ 小于 $m$ 人，那么就直接买 $n$ 瓶快乐水就行了

例如样例 $1$ ，共 $3$ 人， $m$ 的值为1。只有一个人既打狼还坐大巴，所以 $k = 1$ 。 $k$ 大于等于 $m$ ，所以这 $k$ 个人需要买 $m$ 瓶快乐水，剩下的人每人买一瓶，共 $3$ 瓶。

另外，别忘了读入 $type$ 。

$AC$ 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n,m,type,t[100],q[100],k = 0;
    cin >> n >> m >> type;
    for(int i = 0;i < n;i++) cin >> t[i];
    for(int i = 0;i < n;i++) 
    {
        cin >> q[i];
        if(t[i] == 1&&q[i] == 1)k++;
    }
    if(k >= m) cout << m + n - k;
    else cout << n;
    return 0;
}
```


---

## 作者：BotDand (赞：0)

# $\text{Problems}$
VG 的学校有 $n$ 个人要去考 NOIP。

每个人有一个交通方式，第 $i$ 个人的交通方式为 $t_i$，$t_i=1$ 表示这个人坐学校大巴，$t_i=0$ 表示这个人自己去考场。

每个人有一个颓废值，第 $i$ 个人的颓废值为 $q_i$，$q_i=1$ 表示这个人愿意打狼，$q_i=0$ 表示这个人不愿意打狼。

每个人去考场时会买一瓶快乐水，但如果坐大巴且愿意打狼的人数（即满足 $t_i=1$ 且 $q_i=1$ 的 $i$ 个数）$k$ 不小于 $m$，则这 $k$ 个人只需要买 $m$ 瓶快乐水。

现在，VG 统计出了所有人的交通方式和颓废值，他希望请求你帮他求出最终所有人买快乐水的总瓶数。
# $\text{Answer}$
首先，先坐大巴与打狼的人数，也就是找有多少个$q_i=1$并且$t_i=1(i\in[1,n])$。

那么这些人只用买$m$瓶快乐水，判断一下即可。
# $\text{Code}$
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,type,s;
int t[102],q[102];
int main()
{
    cin>>n>>m>>type;
    for(int i=1;i<=n;++i) cin>>t[i];
    for(int i=1;i<=n;++i) cin>>q[i];
    for(int i=1;i<=n;++i) if(t[i]&&q[i]) s++;//找出人数
    if(s>=m) cout<<n-s+m;//判断是否大于m
        else cout<<n;//输出
    return 0;
}
```


---

## 作者：luckydrawbox (赞：0)

## 题意

本质上就是个 little 模拟。

## 做法

统计满足 $t_i=1$ 且 $q_i=1$ 的 $i$ 个数，如果此时的 $k$ 大于等于 $m$，就在原本需要的 $n$ 瓶矿泉水中减去这 $k$ 个人再加上这 $k$ 个人所需的 $m$ 瓶，即 ``ans=n-k+m``, 否则只需要 $n$ 瓶。

```cpp
if(k>=m)
    ans=n-k+m;
else 
    ans=n;
```

## 代码

PS:为了方便~~懒~~，我把上面的 if 语句改成了[三目运算](https://zhuanlan.zhihu.com/p/67788344)，如果不懂的话可以按照上面的 if 来理解。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=110;
int n,m,t[N],p[N],k;
int *type=new int;//（为下文做铺垫） 
int main()
{
    cin>>n>>m>>(*type);
    delete type;//对于没用的东西应予以删除的酷刑 
    for(int i=1;i<=n;i++)
	    cin>>t[i];
	for(int i=1;i<=n;i++)
	{
		cin>>p[i];
		if(t[i]&&p[i])//判断是否符合条件，相当于t[i]==1&&p[i]==1 
		{
			k++;
		}
	}
	cout<<(k>=m?n+m-k:n)<<endl;//三目运算符 
	return 0;
}
```

我是不是太虐了欢迎指正QWQ。

---

## 作者：Eason_AC (赞：0)

## Content
有 $n$ 个人去打比赛。给出第 $i$ 个人的交通方式 $t_i$ 和颓废值 $q_i$（均以 $0/1$ 表示）。如果 $t_i=1,q_i=1$ 的人数 $k\geqslant m$，那么这 $k$ 个人就只用买 $m$ 瓶可乐，其余每个人各买一瓶可乐。问需要多少瓶可乐。

**数据范围：$1\leqslant m\leqslant n\leqslant 100,t_i,q_i\in\{0,1\}$。**  

## Solution
简单地统计一下 $t_i=1,q_i=1$ 的人数 $k$ ，然后答案 $ans=\begin{cases}m+n-k&k\geqslant m\\n&\text{otherwise}\end{cases}$。

总体来说是一道很小清新的签到题。

## Code
```cpp
int n, m, type, t[107], q[107], k;

int main() {
	n = Rint, m = Rint, type = Rint;
	F(i, 1, n) t[i] = Rint;
	F(i, 1, n) {
		q[i] = Rint;
		if(t[i] && q[i]) k++;
	}
	printf("%d", (k >= m) ? (m + n - k) : n);
	return 0;
}
```

---

## 作者：Grace25 (赞：0)

[题目链接](https://www.luogu.com.cn/problem/P7337)

**题目大意**

有$N$个人去打NOIP，他们都会且只会买**一瓶**快乐水，都有去哪里的交通方式（$0$：步行，$1$：大巴），以及颓废值（$0$：不打狼，$1$：打狼）。

但是，当即乘大巴又打狼的人**不小于$M$时**，这些人一共**只需要买$M$瓶**快乐水。（“打折”了）

先在把这些人的交通方式和颓废值都给你，问你一共要买多少瓶快乐水。

首先，我们来看对“打折”没有贡献的人。

这些人，不管怎么样，都不会有打折的机会。

因此直接加一即可。

那有贡献的人呢？

找一个临时变量储存起来，如果有贡献，则加一，否则无变化。

等所有人都处理完后，判断是否能“打折”。

如果能，那这些人就只需买$M$瓶快乐水。

否则，得跟无贡献的人一样，一人一瓶。

处理代码如下：

```cpp
//注：temp记录即乘大巴又打狼的人的人数

if(temp >= m) //如果即乘大巴又打狼的人的人数多于M
    ans+=m;   //则只需买M瓶快乐水
else          //否则
    ans+=temp;//必须每人买一瓶
```

完整代码如下：

```cpp
#include<iostream>
using namespace std; 
int n,m,type,t[105],q;//并不需要一个数组来存颓废值
int main(){
    int ans=0,temp=0;
    cin >> n >> m >> type;
    for(register int i=1;i<=n;++i)
        cin >> t[i];//读入交通方式
    for(register int i=1;i<=n;++i){
        cin >> q;   //读入颓废值
        if(t[i] == 1 && q == 1){//如果这个人即乘大巴又打狼
            temp++;  //temp加一
            continue;
        }
        ans++;      //否则就是对“打折”没有贡献的人
    }
    if(temp >= m) ans+=m;//是否可以打折？
    else ans+=temp;
    cout << ans;//输出
    return 0;
}

```

---

## 作者：Nygglatho (赞：0)

首先，我们可以把这道题目分为两种情况：

第一种是 $k < m$，也就是坐大巴且愿意打狼的人数小于 $m$。

那么，这 $k$ 个人需要 $k$ 瓶快乐水，剩下的 $n - k$ 个人每人要一瓶快乐水，共要 $n - k$ 瓶。加起来总共要 $k + (n - k)$ 瓶，即 $n$ 瓶快乐水，直接输出 $n$ 即可。

第二种是 $k \ge m$，这样的话，$k$ 个人共要 $m$瓶快乐水，剩下的人共要 $n - k$ 瓶。总共要 $m + (n - k)$ 瓶。

代码：
```cpp
#include <cstdio>
int main() {
	int n, m, tp;
	scanf ("%d%d%d", &n, &m, &tp);
	int t[n + 1], q[n + 1];
	int k = 0;
	for (int i = 1; i <= n; i++) scanf ("%d", &t[i]);
	for (int i = 1; i <= n; i++) scanf ("%d", &q[i]);
	for (int i = 1; i <= n; i++)
		if (t[i] && q[i]) k++;
	if (k >= m) printf ("%d\n", m + (n - k));
	else printf ("%d\n", n);
}
```

---

