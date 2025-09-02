# [PA 2022] Podwyżki

## 题目描述

**题目译自 [PA 2022](https://sio2.mimuw.edu.pl/c/pa-2022-1/dashboard/) Runda 2 [Podwyżki](https://sio2.mimuw.edu.pl/c/pa-2022-1/p/pod/)**

对于 Bytecorp 来说，2022 年是艰难的一年。商业决策失误，再加上不景气的市场状况，意味着公司无力为员工涨薪。为了准备应对员工提出的不舒服的问题，人资部门发明了一种方法来证明员工不值得涨薪。

根据一个雇员在连续几天内产生的总收益，可以将一年（在 Byteotia，一年不一定是 365 天）划分为若干区间，这将表明该雇员工作不投入。更确切地说，人资部门希望将收入序列划分为 $k$ 个连续区间，使得序列中的每个元素都恰好属于一个区间。如果**不可能**从每个区间选择一个元素，使所选元素形成严格的升序，那么这种划分是正确的。

Bytecorp 的未来在你手上。写一个程序读入某个雇员产生的收益序列和一个整数 $k$，并根据人资部门的要求把序列分成 $k$ 段，或者判断无法分成这样的 $k$ 段。

## 说明/提示

对于 $100\%$ 的数据，满足：

$2\le k\le n\le 5 \times 10 ^ 5, 1\le a_i\le 10^9, 1\le v_i<n,v_i<v_{i+1}$。

## 样例 #1

### 输入

```
6 3
3 5 4 8 3 7
```

### 输出

```
TAK
3 5
```

## 样例 #2

### 输入

```
4 2
2 3 2 3
```

### 输出

```
NIE
```

# 题解

## 作者：xxxaIq (赞：1)

[题目链接](https://www.luogu.com.cn/problem/P9255)

# 题意简述

要将一个区间长度为 $n$ 的区间划分为 $k$ 段，使得从每一段中任意选出一个数组成的长度为 $k$ 的子序列都不是严格上升的序列。输出划分方案，或报告无解。

特别地，长度为 $1$ 的序列是严格上升序列。

# 思路分析：

分类讨论。

$k=1$ 时显然无解。

$k=2$ 时，枚举两个区间中间的断点，如果左区间的最小值大于等于右边的最大值，那么就有解。预处理出前缀最大值和后缀最小值。

$k=3$ 时，考虑中间的区间选那个数，直接枚举这个数作为中间的区间，比较左右区间，做法与 $k=2$ 时类似。

当 $k \ge 4$ 时，有一个很显然的构造方案，就是如果有一个 $i$ 满足 $a_i>=a_{i+1}$，就可以将它们单独划分开，这样一定会选到这两个数，从而让所选出的序列不严格上升。这样这两个数一共占了两段，剩下左边一段，右边一段正好满足 $k=4$ 的情况。对于 $k>4$ 的情况，将 $[1,i-1]$ 和 $[i+2,n]$ 任意划分够 $k=2$ 段即可。

# 代码：


```cpp
//code by xxxaIq
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int maxn=500003;

int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch>57||ch<48){
		if(ch==45){
			f=-1;
		}
		ch=getchar();
	}
	while(ch>=48&&ch<=57){
		x=(x<<1)+(x<<3)+(ch-48);
		ch=getchar();
	}
	return x*f;
}

int n,k,a[maxn],p=0,ma[maxn],mi[maxn];

void out(int x){
	int r=0,d;
	cout<<"TAK\n";
	d=(x!=n);
	for(int i=1;i<x-2;i++){
		if(k-d-4>=0){
			k--;
			r=i;
			cout<<i<<" ";
		}else{
			break;
		}
	}
	if(x>2){
	    cout<<x-2<<" ";
	    r=x-2;
	    k--;
	}
	cout<<x-1<<" ";
	if(x!=n){
	    cout<<x<<" ";
	}
	
	k-=2;
	r=x;
	for(int i=x+1;i<n;i++){
		if(k-2>=0){
			k--;
			r=i;
			cout<<i<<" ";
		}else{
			break;
		}
	}
	return;
}

int main(){
	n=read(),k=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
	}
	if(k==1){
		cout<<"NIE\n";
		return 0;
	}
	mi[1]=a[1];
	for(int i=2;i<=n;i++){
		mi[i]=min(mi[i-1],a[i]);
	}
	for(int i=n;i>=1;i--){
		ma[i]=max(ma[i+1],a[i]);
	}	
	if(k==2){
		for(int i=1;i<n;i++){
			if(mi[i]>=ma[i+1]){
				cout<<"TAK\n"<<i<<"\n";
				return 0;
			}
		}
		cout<<"NIE\n";
		return 0;
	}
	if(k==3){
		for(int i=2;i<n;i++){
			if(mi[i-1]>=a[i]||a[i]>=ma[i+1]){
				cout<<"TAK\n";
				cout<<i-1<<" "<<i<<"\n";
				return 0;
			}
		}
		cout<<"NIE\n";
		return 0;
	}
	for(int i=2;i<=n;i++){
		if(a[i-1]>=a[i]){
			out(i);
			return 0;
		}
	}
	cout<<"NIE\n";
	return 0;
}
```

---

## 作者：Rosaya (赞：1)

### 题意

给定一个长度为 $n$ 的序列，要将其划分为恰好 $k$ 段，使得无法从每段中取一个值使得这个值严格大于前面的段中选的值。

### 思路

首先我们先说明如果划分为 $a$ 段可行，那么划分为 $b>a$ 段也可行。

假设原来的划分为 $v_{1 \sim a}$，构造新划分为 $w_{1 \sim b}$，使得 $v \subset w$。

这时候会多划分出一些段，此时这种划分方式也合法。

我们可以通过反证说明，如果划分 $w$ 有一种取数构成上升序列的方案，这种方案在 $v$ 中每一段可能有多个数，删除到每段只剩一个就能构成一个 $v$ 取数构成上升序列的方案。

所以我们可以把恰好 $k$ 段的条件改为最多 $k$ 段，构造完后再还原为恰好 $k$ 段，实现见代码的 ```work()``` 函数。

记划分区间数为 $p$，然后分类讨论：

若 $p = 2$，只能切一刀，要求 $\min_{1 \sim i} \ge \max_{i+1 \sim n}$，递推前后缀 $\min,\max$ 即可。

若 $p > 3$，显然如果 $a$ 为上升序列无解，否则一定能找到 $a_i \ge a_{i+1}$，将其单独划分开即可。

若 $p = 3$，只能切两刀，一个前缀一个后缀，前缀一定取 $\min$，后缀一定取 $\max$，中间存在 $i$，满足 $a_i \le \min$ 或者 $a_i \ge \max$。不难发现不如只取一个数，比较即可。

### 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

int n,k;
int a[500005],mn[500005],mx[500005];
int num[500005],cnt;

inline void work()
{
    cout<<"TAK\n";

    sort(num+1,num+cnt+1);
    cnt=unique(num+1,num+cnt+1)-num-1;

    k-=cnt-1;

    int pos=1;

    for(int i=2;i<=cnt;i++)
    {
        while(k&&pos<num[i])
        {
            k--;
            cout<<pos<<' ';
            pos++;
        }

        pos=num[i]+1;
        
        if(i!=cnt)
            cout<<num[i]<<' ';
    }

    cout<<'\n';
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    cin>>n>>k;

    for(int i=1;i<=n;i++)
        cin>>a[i];

    mn[1]=a[1];
    for(int i=2;i<=n;i++)
        mn[i]=min(mn[i-1],a[i]);

    mx[n]=a[n];
    for(int i=n-1;i;i--)
        mx[i]=max(mx[i+1],a[i]);

    num[1]=0;
    num[2]=n;
    cnt=2;

    for(int i=1;i<n;i++)
    {
        if(mn[i]>=mx[i+1])
        {
            num[++cnt]=i;
            work();
            return 0;
        }
    }

    if(k==2)
    {
        cout<<"NIE\n";

        return 0;
    }
    
    if(k>3)
    {
        for(int i=1;i<n;i++)
        {
            if(a[i]>=a[i+1])
            {
                num[++cnt]=i-1;
                num[++cnt]=i;
                num[++cnt]=i+1;
                work();
                return 0;
            }
        }

        cout<<"NIE\n";

        return 0;
    }
    
    for(int i=2;i<n;i++)
    {
        if(mn[i-1]>=a[i]||mx[i+1]<=a[i])
        {
            num[++cnt]=i-1;
            num[++cnt]=i;
            work();
            return 0;
        }
    }

    cout<<"NIE\n";

    return 0;
}
```

---

