# [NWRRC 2023] Jumping Frogs

## 题目描述

Julia 是一位野生自然摄影爱好者。昨天，她拍摄了两张美丽河流的照片，河面上有睡莲和一些青蛙坐在上面。

河流上有许多睡莲，从左到右依次编号为连续的正整数，从 $1$ 开始。两张照片都是从完全相同的位置拍摄的，并且两张照片上都有相同的 $n$ 只青蛙坐在睡莲上。每片睡莲最多只能有一只青蛙。

经过对比，Julia 发现所有青蛙在两张照片之间都移动了，因为没有任何一片睡莲在两张照片中都同时有青蛙坐在上面。然而，Julia 无法分辨第一张照片中的哪只青蛙跳到了第二张照片中的哪片睡莲，因为所有青蛙看起来都一模一样！

可以确定的是：每只青蛙都跳到了不同的睡莲上。有些青蛙向左跳，跳到了编号更小的睡莲上，另一些青蛙向右跳，跳到了编号更大的睡莲上。

为了研究青蛙的移动情况，Julia 想要回答这样一个问题：在两张照片之间，有多少只青蛙向左跳了？由于这个问题可能没有唯一答案，你需要帮助 Julia 找出所有可能的答案。

## 说明/提示

在第一个样例中，最终停在睡莲 $1$ 和 $2$ 上的青蛙一定是向左跳的，而最终停在睡莲 $51$ 和 $52$ 上的青蛙一定是向右跳的。因此，我们可以确定恰好有 $2$ 只青蛙在两张照片之间向左跳了。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
10 20 30 40
1 2 51 52```

### 输出

```
1
2```

## 样例 #2

### 输入

```
4
10 20 30 40
5 15 25 35
```

### 输出

```
4
1 2 3 4```

## 样例 #3

### 输入

```
1
100
200```

### 输出

```
1
0```

# 题解

## 作者：zhanlinchuan (赞：1)

# 题解
### [P13590](https://www.luogu.com.cn/problem/P13590)
## 思路
题目要求输出所有可能的答案，而我们只需要求出答案的最大值和最小值。通过交换青蛙的落点可以得到最小值到最大值之内的所有情况。

我们可以将 $A$ 数组和 $B$ 数组合并为一个数组，将合并后的数组按照位置进行从小到大排序。求最大值需要依次判断每个青蛙是否能跳上左边的石头，求最小值要判断是否能跳上右边石头。
## 代码
```
#include<bits/stdc++.h>
using namespace std;
int n;
struct node{
	int p,id;
}a[400005];
bool cmp(node x,node y){
	return x.p<y.p;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].p;
		a[i].id=1;//原本的数组 A
	}
	for(int i=n+1;i<=n*2;i++){
		cin>>a[i].p;
		a[i].id=0;//原本的数组 B
	}
	sort(a+1,a+2*n+1,cmp);
	int k=0;
	for(int i=1;i<=n*2;i++){
		if(a[i].id==0) k++;
		else if(k>0) k--;
	}
	int maxx=n-k;//向左跳青蛙数量的最大值
	k=0;
	for(int i=n*2;i>=1;i--){
		if(a[i].id==0) k++;
		else if(k>0) k--;
	}
	int minn=k;//向左跳青蛙数量的最小值
	cout<<maxx-minn+1<<endl;
	for(int i=minn;i<=maxx;i++){
		cout<<i<<" ";
	}
	return 0;
}

```

---

## 作者：guoshengyu1231 (赞：1)

# 思路
要解决这个问题，我们需要确定有多少只青蛙在两张照片之间向左跳了。关键在于匹配第一张照片中的青蛙位置和第二张照片中的青蛙位置，并统计其中向左跳的青蛙数量。由于青蛙看起来都一样，我们需要找到所有可能的匹配方式，并统计每种匹配方式中向左跳的青蛙数量。$\\$

那怎样才能快速统计所有可能的向左跳的青蛙数量呢。首先考虑到青蛙的匹配方式可以连续调整（例如逐步交换匹配对的方向），那么我们便可得知，所有可能的答案一定是一个区间，所以我们只需要求出区间的左右端点，也就是求解出可能答案的最大值和最小值，即可算出整个答案的集合。至于怎么求出可能答案的最大值和最小值，我们可以用到贪心的策略。$\\$

具体的，要确定最小和最大左跳数量‌，我们可以用以下贪心方案：
- 最小左跳数量‌：通过将最大的睡莲编号 $a$ 与最大的睡莲编号 $b$ 进行匹配，尽可能减少向左跳的青蛙数量。
- ‌最大左跳数量‌：通过将最小的睡莲编号 $a$ 与最小的睡莲编号 $b$ 进行匹配，尽可能增加向左跳的青蛙数量。

要具体实现的话，我们还需要用双指针的做法来做，我们不妨以求最小值为例。我们定义两个指针分别指向最后一位，然后不断让指针向左移。在匹配过程中，如果当前 $a_i<b_j$，那么就匹配这一对，让两个指针分别往左移。如果 $a_i>b_j$，那么依据贪心的思想，我们肯定得让 $a_i$ 去匹配当前编号最小的 $b_j$，所以答案累加后直接让第一个指针往左移即可，相信大家看到这都会发现，这不就是田忌赛马吗。没错，这题就是一道换皮田忌赛马，他和田忌赛马的贪心策略几乎一模一样。那么剩下的求最大值，留给读者自行实现，反正都差不多，接下来是代码。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
int n,a[maxn],b[maxn],ansl,ansr;
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) cin>>b[i];
    int pa=n,pb=n;
    while(pa&&pb)
     if(a[pa]<b[pb]) pa--,pb--;
     else ansl++,pa--;
    //  
    //   求最大值
    //
    cout<<ansr-ansl+1<<"\n";
    for(int i=ansl;i<=ansr;i++) cout<<i<<' ';
    return 0;
}
```

---

## 作者：jiajunha (赞：1)

## 解题思路
通过分析样例可以发现答案都是一段连续的区间，所以我们可以求出**最大值**与**最小值**。

- **最大值计算**  
我们可以先排序，再操作：
  - 如果遇到第二次拍照的就把 `cnt++`
  - 如果遇到第一次拍照的就与前面的消掉：`if(cnt>0) cnt--`

代码实现：
```cpp
for(int i=1;i<=2*n;++i){
    if(a[i].second==2) cnt++;
    else if(cnt>0) --cnt;
}
int mx = n - cnt;
```

- **最小值计算**  
采用类似的方法，从后往前处理：
```cpp
for(int i=2*n;i>=1;--i){
    if(a[i].second==2) cnt2++;
    else if(cnt2>0) --cnt2;
}
int mi = cnt2;
```

### 完整代码
```cpp
#include<bits/stdc++.h>
#define L(i,j,k) for(int i=(j);i<=(k);i++)
#define R(i,j,k) for(int i=(j);i>=(k);--i)
#define Mem(a,b) memset(a,b,sizeof(a))
#define Max(a,b) (((a)>(b))?(a):(b))
#define Min(a,b) (((a)<(b))?(a):(b))
#define lc (u<<1)
#define rc (u<<1|1)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N=4e5+10;
int n,m;
pair<int,int> a[N]; // a[i].first：值（用于排序） a[i].second=编号 

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    
    cin>>n;
    L(i,1,n){
        cin>>a[i].first;
        a[i].second=1;
    }
    L(i,n+1,2*n){
        cin>>a[i].first;
        a[i].second=2;
    }
    
    sort(a+1,a+1+n*2);
    
    int cnt=0,cnt2=0; 
    L(i,1,2*n){
        if(a[i].second==2) cnt++;
        else if(cnt>0) --cnt;
    }
    int mx=n-cnt;
    
    R(i,2*n,1){
        if(a[i].second==2) cnt2++;
        else if(cnt2>0) --cnt2;
    }
    int mi=cnt2;
    
    cout<<mx-mi+1<<"\n";
    L(i,mi,mx) cout<<i<<" ";
    return 0;
}
```

---

## 作者：Yumi_Anaxa_ (赞：0)

[**题面链接**](https://www.luogu.com.cn/problem/P13590)
## 思路：
**大致题意：**
  - 没有睡莲会被 $2$ 只青蛙同时占。
  - 每只青蛙都移动到了不同的睡莲上。

找向左移动的青蛙。

---
### 可以很快发现：
**青蛙移动是有唯一性的。**
  - 只能移动到一个新的睡莲。
  - 移动后不重叠。
    
**初始位置和目标位置都是严格递增（题面中有写）。**

所以可以按顺序匹配青蛙的移动。

**向左移动时目标编号小于初始，向右跳则相反。**

---
### 代码：
先找出**必须向右的青蛙**有多少。\
然后找出**可以向右的青蛙**。

设必须向右的青蛙有 $l$ 只，可以向右的青蛙有 $r$ 只。

最后答案就在 $l$ 到 $r$ 这个区间里，包括两端。
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int a[200005],b[200005];
priority_queue<ll>ql;
priority_queue<ll,vector<ll>,greater<ll>>qr;
vector<int>ans;
int main(){
  int n;
  cin>>n;
  for(int i=0;i<n;i++)cin>>a[i];
  for(int i=0;i<n;i++)cin>>b[i];
  int l=0,j=0;
  for(int i=0;i<n;i++){
    while(j<n&&b[j]<a[i]){
      ql.push(b[j]);
      j++;
    }
    if(ql.empty())l++;
    else ql.pop();
  }
  int r=0;
  j=n-1;
  for(int i=n-1;i>=0;i--){
    while(j>=0&&b[j]>a[i]){
      qr.push(b[j]);
      j--;
    }
    if(!qr.empty()){
      qr.pop();
      r++;
    }
  }
  for(int i=n-r;i<=n-l;i++)ans.push_back(i);
  cout<<ans.size()<<"\n";
  for(int i=0;i<ans.size();i++)cout<<ans[i]<<" ";
  return 0;
}
```

---

