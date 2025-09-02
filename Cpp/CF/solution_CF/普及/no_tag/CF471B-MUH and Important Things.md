# MUH and Important Things

## 题目描述

在圣彼得堡动物园的两只北极熊，Menshykov 和 Uslada，及基辅动物园的大象 Horace 的努力下，他们面临着一天的 $ n $ 个任务。每只动物都需完成其中的所有任务，并为每个任务评定了难度。他们决定按照任务的难度顺序来完成这些任务。但由于某些任务难度相同，因此任务的完成顺序可能会有所不同。

Menshykov、Uslada 和 Horace 请你设计各自的完成任务的计划。每个计划都需是一个序列，表示动物完成所有 $ n $ 个任务的顺序。同时，他们有一个特别的要求：每个计划必须与其他计划不同，因此需要形成三个不同的序列。你需要为他们找到这样的计划组合，若无法满足要求则需告知他们这不可能。

## 样例 #1

### 输入

```
4
1 3 3 1
```

### 输出

```
YES
1 4 2 3 
4 1 2 3 
4 1 3 2 
```

## 样例 #2

### 输入

```
5
2 4 1 4 8
```

### 输出

```
NO```

# 题解

## 作者：wang_freedom (赞：0)

### 思路:
考虑对难度排序，这样就会保证难度相同的任务会相邻。

枚举排序后的难度，如果相邻且难度相同的任务个数不少于 2，那么就有至少三种排法：正常的难度数组，将第一处相邻且难度相同的交换和将第二处相邻且难度相同的交换。
### AC Code:
```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define rop(i,a,b) for(int i=a;i<b;i++)
#define per(i,a,b) for(int i=a;i>=b;i--)
#define por(i,a,b) for(int i=a;i>b;i--)
#define endl '\n'
#define pii pair<int,int>
#define fi first
#define se second
typedef long long ll;
typedef unsigned long long ull;
typedef double lf;
typedef long double ld;
using namespace std;
int n,cnt,res;
struct work{
	int h,id;
	bool operator<(work a)const{
		return h==a.h?id<a.id:h<a.h;
	}
}w[2005];
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	rep(i,1,n){
		cin>>w[i].h;
		w[i].id=i;
	}
	sort(w+1,w+n+1);
	rop(i,1,n)
		if(w[i].h==w[i+1].h)
			cnt++;
	if(cnt<2){
		cout<<"NO";
		return 0;
	}
	cout<<"YES\n";
	rep(i,1,n)
		cout<<w[i].id<<' ';
	cout<<endl;
	rep(x,1,2){
		res=0;
		rop(i,1,n){
			res+=(w[i].h==w[i+1].h);
			if(w[i].h==w[i+1].h&&res==x){
				cout<<w[i+1].id<<' '<<w[i].id<<' ';
				i++;
				if(i==n)
					goto loop; 
			}
			else
				cout<<w[i].id<<' ';
		}
		cout<<w[n].id<<' ';
		loop:; 
		cout<<endl;
	}
	return 0;
}
/*
？现在jc方式那么低级啊
*/

```

---

## 作者：傅思维666 (赞：0)


## 题解：

[博客食用口味更佳](https://www.cnblogs.com/fusiwei/p/11801031.html)

#### 题目大意：

在这道题的翻译还没挂上来之前，我就把它放到题解上了：

一些任务有着不同的困难度。但是可能会有一些任务的困难度相同。现在，两只北极熊和一只大象希望你能给出3种难度递增而且顺序不同的序列。如果存在的话，请输出YES和这三种不同的序列。否则输出NO。如果你完不成这个任务，它们仨就会吃了你，加油！

#### 题目解析：

其实就是一道模拟。或者说把它叫做排序也好。随便你怎么说。

是这样：

因为是任意三个合法序列。所以我们只需要把相邻的两个相等元素交换一下位置即可。

那么显然地，如果有两个及两个以下的相等元素，那么是肯定不可以的。直接输出NO。否则就输出YES，并且交换任意一个相邻的相等元素。正着扫一遍，反着扫一遍即可。

代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,cnt;
struct data
{
    int v,pos;
}a[2005];
bool cmp(data a,data b)
{
    return a.v<b.v;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i].v);
        a[i].pos=i;
    }
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;i++)
        if(a[i].v==a[i-1].v)
            cnt++;
    if(cnt<2)
    {
        puts("NO");
        return 0;
    }
    else 
    {
        puts("YES");
        for(int i=1;i<=n;i++)
            printf("%d ",a[i].pos);
        puts("");
        for(int i=1;i<=n;i++)
            if(a[i].v==a[i-1].v)
            {
                swap(a[i],a[i-1]);
                break;
            }
        for(int i=1;i<=n;i++)
            printf("%d ",a[i].pos);
        puts("");
        for(int i=n;i;i--)
            if(a[i].v==a[i-1].v)
            {
                swap(a[i],a[i-1]);
                break;
            }
        for(int i=1;i<=n;i++)
            printf("%d ",a[i].pos);
        puts("");
    }
    return 0;
}
```



---

