# Gourmet and Banquet

## 题目描述

A gourmet came into the banquet hall, where the cooks suggested $ n $ dishes for guests. The gourmet knows the schedule: when each of the dishes will be served.

For $ i $ -th of the dishes he knows two integer moments in time $ a_{i} $ and $ b_{i} $ (in seconds from the beginning of the banquet) — when the cooks will bring the $ i $ -th dish into the hall and when they will carry it out ( $ a_{i}&lt;b_{i} $ ). For example, if $ a_{i}=10 $ and $ b_{i}=11 $ , then the $ i $ -th dish is available for eating during one second.

The dishes come in very large quantities, so it is guaranteed that as long as the dish is available for eating (i. e. while it is in the hall) it cannot run out.

The gourmet wants to try each of the $ n $ dishes and not to offend any of the cooks. Because of that the gourmet wants to eat each of the dishes for the same amount of time. During eating the gourmet can instantly switch between the dishes. Switching between dishes is allowed for him only at integer moments in time. The gourmet can eat no more than one dish simultaneously. It is allowed to return to a dish after eating any other dishes.

The gourmet wants to eat as long as possible on the banquet without violating any conditions described above. Can you help him and find out the maximum total time he can eat the dishes on the banquet?

## 说明/提示

In the first example the gourmet eats the second dish for one second (from the moment in time 1 to the moment in time 2), then he eats the first dish for two seconds (from 2 to 4), then he returns to the second dish for one second (from 4 to 5). After that he eats the third dish for two seconds (from 6 to 8).

In the second example the gourmet cannot eat each dish for at least one second because there are three dishes but they are available for only one second (from 1 to 2).

## 样例 #1

### 输入

```
3
2 4
1 5
6 9
```

### 输出

```
6
```

## 样例 #2

### 输入

```
3
1 2
1 2
1 2
```

### 输出

```
0
```

# 题解

## 作者：shan_xin (赞：2)

## 题意：
 给定 $N$ 个区间，让你去求一个 $ans$ ，使得在每个区间之间没有**重复使用**同一时刻的前提下(因为一秒只能吃一道菜)，区间内所不冲突的时间段的大小最大。最后输出这 $ans$ 乘上 $N$ 的值。 

## 做法：
 因为是要求区间大小的最大值，所以我们考虑用**二分答案**来解决。我们先将读入进的数据按照左端点排序，满足单调性再进行二分。 

 然后我们在二分的时候判断每个区间能不能满足这个大小。如果能满足，那么我们就继续向右寻找更大的值。反之，我们则去左边找个较小的值让每个区间都能满足条件。 

## 复杂度：
 $O(N\log{N})$ 

 具体细节在代码中有解释 
```cpp
#include<bits/stdc++.h>

using namespace std;

const int N=110,M=100010;

struct Node{
	int l,r;
}a[N];

int n;
int vis[M];//判断时间i有没有被使用过 

bool check(int mid){//判断函数 
	memset(vis,-1,sizeof vis);
	for(int i=1;i<=n;i++){
		if(a[i].l-a[i].r<mid){//两个区间的时间已经小于，显然不满足 
			return -1;
		}
		else{
			int sum=0;//记录当前区间有多少个时刻被用了 
			for(int j=a[i].l;j<=a[i].r;j++){
				if(vis[j]==-1){//时刻j还没被用过 
					sum++;
					vis[j]=1;
					if(sum==mid){//已经满足条件了 
						break;
					}
				}
			}
			if(sum<mid)return -1;
		}
	}
	return 1;
}

int cmp(Node x,Node y){
	if(x.l==y.l)return x.r<y.r;
	else return x.l<y.l;
}

int main(){
	cin>>n;
	int L=0,R;
	for(int i=1;i<=n;i++){
		cin>>a[i].l>>a[i].r;
		a[i].r-=1;
		R=max(R,a[i].r-a[i].l);
	}
	sort(a+1,a+n+1,cmp);
	int ans=0;
	while(L<R){
		int mid=(L+R)>>1;
		if(check(mid)==1){//小于所要查的区间 
			L=mid+1;
			ans=max(ans,mid);
		}
		else{
			R=mid-1;//大于所要查的区间 
		}
	}
	cout<<ans*n<<endl;
	return 0;
}
```


---

## 作者：Dehydration (赞：1)

### 前言：

垃圾翻译，建议管理将翻译换一个，只要能理解题目直接水掉。

[Problem](https://www.luogu.com.cn/problem/CF589F)。

### 翻译：



给你 $n$ 个 区间 $[l,r)$ 求最大的子区间大小使每个区间都有这个子区间且覆盖不重复。

### 思路：

二分加上英语水平就可以过掉此题。

因为是求均覆盖不重复的最大值，我们可以记录最大值，最后用 `visit` 数组记录是否可用，然后通过区间最大值二分寻找，也就是二分，判断能否可用，可用继续，不可用返回。

**需要用 `struct` 记录区间，中间用 `cmp` 按值 `sort` 排序。**

二分 `check` 代码会放上。


### 代码：

```
bool check(int time_per_dish)
{
    memset(vis,false,sizeof(vis));
    for(int i=1;i<=N;i++)
    {
          if(a[i].b-a[i].a<time_per_dish)   return false;
          int occupy=0;
          for(int j=a[i].a;j<a[i].b;j++)
                  if(!vis[j])//vis[j]表示j->j+1的时间是否被占用 
                  {
                        occupy++;
                        vis[j]=true;
                        if(occupy==time_per_dish)   break;
                }
          if(occupy<time_per_dish)   return false;
    }
    return true;
}//是否可以


//check函数
```

---

```
    while(Left<=Right)
    {
          int middle=(Left+Right)>>1;
          if(check(middle))
          {
                  Left=middle+1;
                  ans=max(middle,ans);
          }
          else  Right=middle-1;
          
    }
    //二分函数
```

---

