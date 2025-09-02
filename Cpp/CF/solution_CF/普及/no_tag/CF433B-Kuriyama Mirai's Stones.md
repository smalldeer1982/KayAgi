# Kuriyama Mirai's Stones

## 题目描述

Kuriyama Mirai has killed many monsters and got many (namely $ n $ ) stones. She numbers the stones from $ 1 $ to $ n $ . The cost of the $ i $ -th stone is $ v_{i} $ . Kuriyama Mirai wants to know something about these stones so she will ask you two kinds of questions:

1. She will tell you two numbers, $ l $ and $ r (1<=l<=r<=n) $ , and you should tell her ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF433B/a68d6654cf2b25883008b776a62307a377b6be58.png).
2. Let $ u_{i} $ be the cost of the $ i $ -th cheapest stone (the cost that will be on the $ i $ -th place if we arrange all the stone costs in non-decreasing order). This time she will tell you two numbers, $ l $ and $ r (1<=l<=r<=n) $ , and you should tell her ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF433B/81f5c65268118775753c7eebcdd998c0bae9a99d.png).

For every question you should give the correct answer, or Kuriyama Mirai will say "fuyukai desu" and then become unhappy.

## 说明/提示

Please note that the answers to the questions may overflow 32-bit integer type.

## 样例 #1

### 输入

```
6
6 4 2 7 2 7
3
2 3 6
1 3 4
1 1 6
```

### 输出

```
24
9
28
```

## 样例 #2

### 输入

```
4
5 5 2 3
10
1 2 4
2 1 4
1 1 1
2 1 4
2 1 2
1 1 1
1 3 3
1 1 3
1 4 4
1 2 2
```

### 输出

```
10
15
5
15
5
5
2
12
3
5
```

# 题解

## 作者：liuyi0905 (赞：4)

看到这道题，我们第一眼的反应就是**前缀和**。

### 前缀和是什么？
对于一些不懂的人，我在这里还是讲解一下：

前缀和数组 $pre$ 的意思是：$a$ 数组从前往后加起来的值，用公式代替：
$pre_n=\sum\limits_{i=1}^na_i$。

举个例子：

如果 $a=[1,4,2,7,9,3]$，那么 $pre=[1,5,7,14,23,26]$。

所以要求出 $a_l$ 到 $a_r$ 的和，就用 $pre_r-pre_{l-1}$。

当然算出第一个前缀和数组后还要排个序，算下一个前缀和数组。

题目中还有一点要注意：**结果可能是会超过 32 位的整数类型**，所以必须开 `long long`。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,v[100001],pre[3][100001];
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>v[i];
        pre[1][i]=pre[1][i-1]+v[i];//前缀和数组
    }
    sort(v+1,v+n+1);
    for(int i=1;i<=n;i++)pre[2][i]=pre[2][i-1]+v[i];
    cin>>m;
    while(m--){
        int a,l,r;
        cin>>a>>l>>r;
        cout<<pre[a][r]-pre[a][l-1]<<"\n";
    }
    return 0;
}
```

---

## 作者：Eason_AC (赞：4)

## Content
有一个长度为 $n$ 的数组 $a_1,a_2,a_3,...,a_n$。有 $m$ 次询问，询问有以下两种：

- $1~l~r$，求 $\sum\limits_{i=l}^ra_i$。
- $2~l~r$，将数组非降序排列后再依次标号，然后再求 $\sum\limits_{i=l}^ra_i$。

**数据范围：$1\leqslant l\leqslant r\leqslant n\leqslant 10^5,1\leqslant m\leqslant 10^5,1\leqslant a_i\leqslant 10^9$。**
## Solution
这道题旨在考察对前缀和的操作，比如说这道题目我们就可以用前缀和很好地求解。具体如下：

我们先将没有排序的数组求出他们的前缀和 $s_i=\sum\limits_{j=1}^ia_j$，然后再按照题目要求排序得到 $a'$ 数组，再求出 $s'_i=\sum\limits_{j=1}^ia_j$。再接着，我们根据两种不同的操作分类讨论：

1. 对于第一种操作，我们知道：$s_{l-1}=\sum\limits_{i=1}^{l-1} a_i,s_r=\sum\limits_{i=1}^n a_i$。由此我们得到 $s_r-s_{l-1}=a_r+a_{r-1}+...+a_l+a_{l-1}+...+a_1-(a_l+a_{l-1}+...+a_l)=a_l+a_{l+1}+...+a_r$。正好就是我们所要求的 $[l,r]$ 这个区间内所有数的总和。由此我们就知道了，第一种操作的答案就是 $s_r-s_{l-1}$。
2. 对于第二种操作，和第一种操作类似，只不过变成了排序后的数组的前缀和罢了，除了排序以外几乎没什么差别，答案就是 $s'_r-s'_{l-1}$。

## Code
```cpp
#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

int n, m, a1[100007], a2[100007];
long long sum[3][100007];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &a1[i]);
		a2[i] = a1[i];
	}
	sort(a2 + 1, a2 + n + 1);
	for(int i = 1; i <= n; ++i)
		sum[1][i] = sum[1][i - 1] + a1[i], sum[2][i] = sum[2][i - 1] + a2[i];
	scanf("%d", &m);
	while(m--) {
		int opt, l, r;
		scanf("%d%d%d", &opt, &l, &r);
		printf("%lld\n", sum[opt][r] - sum[opt][l - 1]);
	}
	return 0;
}

```

---

## 作者：wxzzzz (赞：1)

### 题意

给定序列 $a$，有两种操作：

1. 求 $l$ 到 $r$ 的区间和。
1. 先将 $a$ 排序，求排序后的 $l$ 到 $r$ 的区间和。

### 思路

题面看起来很像树状数组或线段树，但是并不是这样。

本题虽然要求排序前后的区间和，但是并没有序列修改操作，因此，可以在询问前预处理出排序前后两个序列的前缀和，操作时再分别考虑即可。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, l, r, op, a[1000005], s[1000005], ss[1000005];
int main() {
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> a[i], s[i] = s[i - 1] + a[i];
    }
    sort(a + 1, a + 1 + n);
    
    for (int i = 1; i <= n; i++){
        ss[i] = ss[i - 1] + a[i];
    }
    cin >> m;

    while (m--) {
        cin >> op >> l >> r;

        if (op == 1)
            cout << s[r] - s[l - 1] << '\n';
        else
            cout << ss[r] - ss[l - 1] << '\n';
    }

    return 0;
}
```

---

## 作者：Composite_Function (赞：0)

# 思路

看到这题，最暴力的方法一定是需要排序则排序；反之，恢复原样。最后枚举 $\left[ l,r\right]$ 之间的范围求和。

毫无疑问，肯定会 $\texttt{TLE}$。会发现，有一下几个优化：

1. 用两个数组存已排序和未排序的原数组
2. 因为有 $\forall 1 \leq l \leq r \leq n \sum ^ r _ {i = l} = \sum ^ r _ {i = 1} - \sum ^ {l - 1} _ {i = l - 1}$ 所以可以使用前缀和。

------------

#  代码

```cpp
# include <bits/stdc++.h>
using namespace std;
# define int long long
const int N = 1e5 + 10;
int n, m, a[N], aa[N];
int sum[3][N];
signed main()
{
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> a[i], aa[i] = a[i];
    sort(aa + 1, aa + n + 1);//排序
    for (int i = 1; i <= n; ++i) {
        sum[1][i] = sum[1][i - 1] + a[i];
        sum[2][i] = sum[2][i - 1] + aa[i];
    }//前缀和
    cin >> m;
    while (m--) {
        int op, l, r;
        cin >> op >> l >> r;
        cout <<  sum[op][r] - sum[op][l - 1] << endl;
    }
    return 0;
}
```


---

## 作者：_Revenge_ (赞：0)

### 题目简化和分析：
为了更加快速的求出答案，好像没前缀和快速。   
为了大家更好的理解线段树，我们使用了线段树。 

如果您并不了解线段树，可以转战模板。   
因为我们知道线段树可以快速求区间和，于是我们建两棵树。   
一个是原来数组，一个是排好序的数组。   
每次查询分别用不同的线段树区间和就行了。     

### Solution:

```cpp
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef double db;

const int N=4e5+50;
const int M=1e5+50;

inline ll read(){
    ll x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}

ll n,m;
ll v[N];

ll ans1[N],ans2[N];
ll ls(ll x){return x<<1;}
ll rs(ll x){return x<<1|1;}
void push_up1(ll p){
	ans1[p]=ans1[ls(p)]+ans1[rs(p)];	
}
void push_up2(ll p){
	ans2[p]=ans2[ls(p)]+ans2[rs(p)];
}
void build1(ll p,ll l,ll r){
	if(l==r){ans1[p]=v[l];return;}
	ll mid=(l+r)>>1;
	build1(ls(p),l,mid);
	build1(rs(p),mid+1,r);
	push_up1(p);
}
void build2(ll p,ll l,ll r){
	if(l==r){ans2[p]=v[l];return;}
	ll mid=(l+r)>>1;
	build2(ls(p),l,mid);
	build2(rs(p),mid+1,r);
	push_up2(p);
}
ll query1(ll nx,ll ny,ll l,ll r,ll p){
	ll res=0;
	if(nx<=l&&r<=ny) return ans1[p];
	ll mid=(l+r)>>1;
	if(nx<=mid) res+=query1(nx,ny,l,mid,ls(p));
	if(ny>mid) res+=query1(nx,ny,mid+1,r,rs(p));
	return res;
}
ll query2(ll nx,ll ny,ll l,ll r,ll p){
	ll res=0;
	if(nx<=l&&r<=ny) return ans2[p];
	ll mid=(l+r)>>1;
	if(nx<=mid) res+=query2(nx,ny,l,mid,ls(p));
	if(ny>mid) res+=query2(nx,ny,mid+1,r,rs(p));
	return res;
}
int main()
{
	n=read();
	for(int i=1;i<=n;++i) v[i]=read();
	build1(1,1,n);
	sort(v+1,v+n+1);
	build2(1,1,n);
	m=read();
	for(int i=1;i<=m;++i){
		ll op,l,r;
		op=read();
		if(op==1){
			l=read(),r=read();
			printf("%lld\n",query1(l,r,1,n,1));
		}else{
			l=read(),r=read();
			printf("%lld\n",query2(l,r,1,n,1));
		}
	}
	return 0;
}

```

---

## 作者：MrFish (赞：0)

#### 第一秒看到这道题之后就想到了模拟，然后写了这个代码。

```cpp
#include<iostream>
#include<algorithm>

using namespace std;

long long val1[100005],val2[100005];

int main()
{
    int n,m;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>val1[i];
        val2[i]=val1[i];
    }  //读入
    sort(val2+1,val2+1+n); //将把val2排序。
    cin>>m;
    while(m--)
    {
        int type,r,l;
        long long ans=0;
        cin>>type>>l>>r;  //每次查询。
        if(type==1)  //type为1
        {
            for(int i=l;i<=r;i++)
            {
                ans+=val1[i]; //用val1计算。
            }
        }
        else
        {
            for(int i=l;i<=r;i++)
            {
                ans+=val2[i];
            }            
        }
        cout<<ans<<endl;//输出答案。
    }
    return 0;
}
```
### But，完美的 TLE 了......
#### 所以这道题还是要用 **前缀和**！

奉上我的AC代码：
```cpp
#include<iostream>
#include<algorithm>

using namespace std;

long long val1[100005],val2[100005];
long long s1[100005],s2[100005];  //记录val1,val2的前缀和

int main()
{
    int n,m;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>val1[i];
        val2[i]=val1[i];
    }  //读入
    sort(val2+1,val2+1+n);  //排序
    for(int i=1;i<=n;i++)
    {
        s1[i]=s1[i-1]+val1[i];
        s2[i]=s2[i-1]+val2[i];
    }  //计算前缀和
    cin>>m;
    while(m--)
    {
        int type,r,l;
        cin>>type>>l>>r;  //每次查询
        if(type==1)
        {
            cout<<s1[r]-s1[l-1]<<endl;
        }
        else
        {
            cout<<s2[r]-s2[l-1]<<endl;
        }  //计算答案。
    }
    return 0;
}
```
拜拜！

---

