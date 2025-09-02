# Mentors

## 题目描述

In BerSoft $ n $ programmers work, the programmer $ i $ is characterized by a skill $ r_i $ .

A programmer $ a $ can be a mentor of a programmer $ b $ if and only if the skill of the programmer $ a $ is strictly greater than the skill of the programmer $ b $ $ (r_a > r_b) $ and programmers $ a $ and $ b $ are not in a quarrel.

You are given the skills of each programmers and a list of $ k $ pairs of the programmers, which are in a quarrel (pairs are unordered). For each programmer $ i $ , find the number of programmers, for which the programmer $ i $ can be a mentor.

## 说明/提示

In the first example, the first programmer can not be mentor of any other (because only the second programmer has a skill, lower than first programmer skill, but they are in a quarrel). The second programmer can not be mentor of any other programmer, because his skill is minimal among others. The third programmer can be a mentor of the second programmer. The fourth programmer can be a mentor of the first and of the second programmers. He can not be a mentor of the third programmer, because they are in a quarrel.

## 样例 #1

### 输入

```
4 2
10 4 10 15
1 2
4 3
```

### 输出

```
0 0 1 2 
```

## 样例 #2

### 输入

```
10 4
5 4 1 5 4 3 7 1 2 5
4 6
2 1
10 8
3 5
```

### 输出

```
5 4 0 5 3 3 9 0 2 5 
```

# 题解

## 作者：SqrtSecond (赞：4)

先假设没有人发生口角。

那么每个人的答案就是原数组中**严格小于**自己能力值的人数。

对于这部分，另开一个数组，```sort+lower_bound```可以处理。

注意 ```sort+lower_bound``` 是求原数组中**第一个**大于等于某个数的数的下标，如果直接用二分查找，就可能多算答案。

那么有人发生口角呢？

想象一下，如果有个人原来可以当对方的导师，但是由于发生了口角，损失的就只有他一个人。

那么，我们只需要将能力大的那个人找出来，将其答案减$1$即可。

那么如果两个人能力值相等呢？

显然，本来双方都不能做对方的导师，~~发生口角也没什么关系~~

那么这种情况就跳过就行啦~ 

## code:

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	char ch=getchar();int x=0,r=1;
	while(ch<'0'||ch>'9'){if(ch=='-')r=0;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return r?x:-x;
}//快读 
int n,m,a[200100],b[200100],ans[200100],x,y;
signed main()
{
	n=read();m=read();
	for(int i=1;i<=n;++i)a[i]=b[i]=read();
	sort(b+1,b+n+1);
	for(int i=1;i<=n;++i)
	{
		int l=lower_bound(b+1,b+n+1,a[i])-b;//第一个等于a[i]的数的位置，即前面都小于a[i]
		ans[i]=l-1;//即有多少人比他弱 
	}
	while(m--)
	{
		x=read();y=read();
		if(a[x]<a[y])ans[y]--;
		if(a[y]<a[x])ans[x]--;//将发生口角的两人关系排除 
	}
	for(int i=1;i<=n;++i)printf("%d ",ans[i]); 
	return 0;//养成好习惯 
}
```


---

## 作者：「已注销」 (赞：3)

用$ruo_i$存比第$i$个程序员弱的人数

用$h_i$存和第$i$个程序员有冲突且比他弱的人数

答案是$ruo_i-h_i$

输入时即可求$h$，用排序求$ruo$
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,m,r[200001],s[200001],ruo[200001],h[200001];
bool cmp(int a,int b){
	return r[a]<r[b];
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)scanf("%d",&r[i]),s[i]=i;
	for(int i=1;i<=m;++i){
		int x,y;
		scanf("%d%d",&x,&y);
		if(r[x]>r[y])++h[x];
		if(r[x]<r[y])++h[y];
	}
	sort(s+1,s+n+1,cmp); //使用下标排序，s存下标
	for(int i=2;i<=n;++i){
		if(r[s[i]]>r[s[i-1]])ruo[s[i]]=i-1; //递推求ruo
		else ruo[s[i]]=ruo[s[i-1]];
	}
	for(int i=1;i<=n;++i)printf("%d ",ruo[i]-h[i]);
}
```

---

## 作者：jiangyushen (赞：0)

### 题目描述

[百度翻译（仅供参考）](https://www.luogu.com.cn/paste/85d7rkbu)

### 算法：二分，排序

首先预先处理好吵架的事，然后按他们各自的实力值排序，接着就是需要查找最后一个小于 $r_i$ 能力值的人是在排序中的第几位，就说明 TA 就可以当几个人的导师。

这个查找，我第一时间想到的是二分查找，因为它快。当然你用 STL 也是没问题的。最后，再按原来的输入的顺序输出。

时间复杂度为 $O(n \log n)$。
#### C++ 代码
```cpp
#include<bits/stdc++.h>
//#include<algorithm>
//#include<iostream>不习惯用万能头的用这个。
using namespace std;
int n, k, x, y, l, r, mid;
struct Pro {
    int r, id, app;//r 是能力值， id 表示他的初始位置， app 表示 TA 可以当几个人的导师。
}a[200005];
bool cmp1(Pro x, Pro y) {
    return x.r < y.r;
}
bool cmp2(Pro x, Pro y) {
    return x.id < y.id;
}
int main() {
    ios::sync_with_stdio(NULL);
    cin.tie(0);
    cout.tie(0);//cin,cout 的一个优化

    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].r;
        a[i].id = i;//存下初始位置
    }
    for (int i = 1; i <= k; i++) {
        cin >> x >> y;
        if (a[x].r > a[y].r) a[x].app--;
        else if (a[x].r < a[y].r) a[y].app--;//哪一个能力值大就说明 TA 的“徒弟”就少一个
    }
    sort(a + 1, a + n + 1, cmp1);//按实力排序
    for (int i = 2; i <= n; i++) {//重点：二分
        //因为第一个绝对不可能有“徒弟”，所以 i 从2开始
        l = 1; r = i;
        while (l <= r) {
            mid = (l + r) / 2;
            if (a[mid].r < a[i].r) l = mid + 1;//说明答案在右边
            else r = mid - 1;//说明答案在左边
        }
        a[i].app += r;//∵r 是答案∴加上 r
    }
    sort(a + 1, a + n + 1, cmp2);//按原输入顺序排序
    for (int i = 1; i <= n; i++)
        cout << a[i].app << ' ';
    return 0;
}
```

---

## 作者：GoldenFishX (赞：0)

### 主要思路
- 把每一个人会与多少个比他能力小的人发生口角的个数用一个数组存起来。算答案的时候，只需要将**比他能力小的人**的个数减去**比他能力小且会发生口角的人**的个数就行了

- 因此我们只需要将人的能力从小到大排序一遍，就可以求出每个人比他能力小的人的个数了。

- **但是有多个人能力值相等的情况**，所以要减去前面的人的能力值与这个人的能力值相等的个数。

- 所以第 $i$ 个人的答案就是**排序后的下标** 减去 **比第 $i$ 个人能力小且会发生口角的人的个数** 再减去 **前面的人的能力值与这个人的能力值相等的个数**
### 代码部分

```
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5;
struct Node{ //每个人的能力值与排序前的下标，存排序前的下标主要是为了方便输出答案
  int x, i;
}a[MAXN];
int ans[MAXN];//存答案的数组
bool cmp(Node x,Node y) {
  return x.x < y.x;
}
int f[MAXN];//用来存每个人会与多少个比他能力小的人发生口角
int main() {
  int n, k;
  cin >> n >> k;
  for(int i = 1; i <= n; i++) {
    cin >> a[i].x;
    a[i].i = i;
  }
  for(int i = 1; i <= k; i++) {
    int x, y;
    cin >> x >> y;
    if(a[x].x > a[y].x) { 	// 第x个人的能力值比第y个人大的情况
      f[x]++;
    } else if(a[x].x < a[y].x){	// 第y个人的能力值比第x个人大的情况
      f[y]++;
    }
  }
  int x = 0; //前面的人的能力值与第i个人的能力值相等的个数
  sort(a + 1, a + n + 1, cmp); //排序
  for(int i = 1; i <= n; i++) {
    if(a[i].x != a[i - 1].x) {
      x = 0;
    }
    ans[a[i].i] = (i - 1) - f[a[i].i] - x;
    x++;
  }
  for(int i = 1; i <= n; i++) {
    cout << ans[i] << " ";
  }
  return 0;
}
```


---

