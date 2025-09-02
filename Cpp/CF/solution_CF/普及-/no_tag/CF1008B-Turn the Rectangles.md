# Turn the Rectangles

## 题目描述

There are $ n $ rectangles in a row. You can either turn each rectangle by $ 90 $ degrees or leave it as it is. If you turn a rectangle, its width will be height, and its height will be width. Notice that you can turn any number of rectangles, you also can turn all or none of them. You can not change the order of the rectangles.

Find out if there is a way to make the rectangles go in order of non-ascending height. In other words, after all the turns, a height of every rectangle has to be not greater than the height of the previous rectangle (if it is such).

## 说明/提示

In the first test, you can rotate the second and the third rectangles so that the heights will be \[4, 4, 3\].

In the second test, there is no way the second rectangle will be not higher than the first one.

## 样例 #1

### 输入

```
3
3 4
4 6
3 5
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
2
3 4
5 5
```

### 输出

```
NO
```

# 题解

## 作者：alex_liu (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1008B)

# 思路：
既然不能改变顺序，那么我们就可以从第一个开始枚举，选择最优的高度（与前一个的高的差最小）。

如果当前已经不能组成不上升序列了，那么就直接输出 “ NO ”

详细代码的解释看注释
# AC CODE：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
signed main(){
	int n,x,y,first=1000000001;//n 为数的个数，x ，y 分别为高度与宽度，first 需要定义一个大数，以免第一个数就已经不能存放 
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x>>y;
		if(x>first&&y>first){//当两个数都比前一个数大（不能组成不上升序列） 
			cout<<"NO\n";//直接输出 
			return 0;//结束程序 
		}
		else if(x>first)first=y;//x 比前一个大，则只能选择 y 
		else if(y>first)first=x;//y 比前一个大，则只能选择 x
		else first=max(x,y);//都比前一个数小，则选择最大的 
	}
	cout<<"YES\n";//可以形成不上升序列，输出 
	return 0;//结束程序 
} 
```



---

## 作者：togeth1 (赞：1)

## [题 目 传 送 门](https://www.luogu.com.cn/problem/CF1008B)

### **[题意解析]**
让我们在不改变长和宽的顺序的前提下，通过旋转长方形，使长方形高度形成一个不上升序列。而题目中说的**不上升序列**指的是当前的 $x$ 与 $y$ 要比之前的其中一个 $x$ 与 $y$ 要小。

+ 如果可以通过旋转长方形，使长方形高度形成一个不上升序列，那就输出 $\verb!YES!$。
+ 否则输出 $\verb!NO!$。

### **[思路分析]**
理解了题目，我们的思路就非常清晰了，我们可以贪心的思想。在保证不上升序列的前提下，把高取尽量大就可以了。

### **[贴上代码]**
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,x,y,ft=0x3f3f3f3f;
/*设个最大值给上一个高度*/
int main()
{
	cin>>n;
	for(int i=1; i<=n; i++){
		cin>>x>>y;
		if(ft<x&&ft>y)ft=x;
		/*如过x大取x*/
		if(ft>x&&ft<y)ft=y;
		/*如过y大取y*/
		if(ft>x&&ft>y)ft=max(x,y);
		/*如过x,y都要比上一个大,取x,y中的最大*/
		if(ft<x&&ft<y){
			cout<<"NO";
			return 0;
		}
		/*如果上一个比x,y都要小，那就够不成不上升序列了，直接输出NO*/
	}
	cout<<"YES";
	/*最后输出YES*/
	return 0;
}
```


---

## 作者：codesonic (赞：1)

一句话题意：有序的n对数，试从每对数中选一个排列成不降序列

简单题，记录前一次的选择，对于每一对数如果两个数都大于前一次选择的数就直接NO，一个大于一个小于就只能选小的，都小于当然贪心选大的

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>

using namespace std;

int n;

int main()
{
    scanf("%d",&n);
    int last=(1<<30);
    for(int i=1;i<=n;i++){
        int x,y;
        scanf("%d %d",&x,&y);
        if(max(x,y)<=last) last=max(x,y);
        else if(min(x,y)<=last) last=min(x,y);
        else{
            printf("NO\n");
            return 0;
        }
    }
    printf("YES\n");
    return 0;
}
```

---

## 作者：TemplateClass (赞：0)

这道题目是一道贪心题，我们用一个变量 $l$ 记录上一个长方形的高，情况分以下几种：

1. 若当前是第 $1$ 个长方形的话，无需判断，$l=\max(a,b)$。

2. 若 $a>l$ 且 $b>l$，说明已经无法再形成一个不上升序列了，输出 `NO` 并结束程序即可。

3. 若当前 $a>l$，只能让 $l=b$，反之亦然。

4. 若不属于上面的任何一种情况，则 $l$ 应该等于与它相差最小的长度。

5. 若到结束仍然未输出 `NO`，则输出 `YES`。

代码实现如下：

```cpp
#include<bits/stdc++.h>
using namespace std;

// 定义变量n和l。
int n, l;
int main(){
	// 读入n。
	cin>>n;
	for(int i=1;i<=n;++i){
 		// 读入长方形的长和宽。
		int a, b;
		cin>>a>>b;
		// 若当前是第1个长方形。
		if(i==1) l=max(a, b);
		else{
			// 此时已经无法再形成一个不上升序列了。
			if(a>l && b>l){
				cout<<"NO";
				return 0;
			}
			// 极端情况判断。 
			if(a>l) l=b;
			else if(b>l) l=a;
			// 将l赋值为与它相差最小的长度。 
			else if(l-a<l-b) l=a;
			else l=b;
		}
	}
	// 若仍然未输出NO，则输出YES。
	cout<<"YES";
	
	// 结束程序。
	return 0; 
} 
```

求过。

---

## 作者：Fengyiwei1234 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1008B)

# 思路：贪心&模拟

每次枚举的那个长方形，挑选长宽中最大的那个（注意不能大过上一个）。

这样保证最优，如果这样都不行，那输出 No。

AC 代码：

```c++
#include<bits/stdc++.h>
using namespace std;
int n,x,y,maxX=1e9+9;
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>x>>y;
        if(x>maxX&&y>maxX)//怎么放都不行，输出 NO。
        {
            cout<<"NO"<<endl;
            return 0;
        }
        else if(x>maxX)maxX=y;//依次判断
        else if(y>maxX)maxX=x;//依次判断
        else maxX=max(x,y);//都不行，只能选最大值
    }
    cout<<"YES"<<endl;//此时有一种方案可行，输出 Yes。
    return 0;
} 
```

[AC 记录](https://www.luogu.com.cn/record/111978523)

---

## 作者：zjr0330 (赞：0)

首先我们看到题目，我的第一感受是将每个数用 DFS 枚举一遍，时间复杂度有点高，所以我换成了另一种方法。

首先我们输入有多少个长方形：

```cpp
int t;    //有多少个长方形
long long f = 100000000000000000;    //目前的高度
cin >> t;    //输入有多少个长方形
```

然后输入这两个数（高度与长度）：

```cpp
int x, y;
cin >> x >> y;
```


接下来我们来判断它们是否都大于目前高度：

```cpp
if (min(x, y) > f) {    //用 min 来选最小的，如果最小的都比 f 小，那大的肯定也是。
	cout << "NO" << endl;
	return 0;
}
```

否则，我们看看那个能选，如果都能选，选最大的那个（~~我就是在这踩了坑~~）：

```cpp
 else {
	if (max(x, y) > f) {    //用max选出最大的。
		if (x > f && y <= f)f = y;
		else f = x;
	} else {
		f = max(x, y);
	}
}
```

最后如果可行就输出 ```YES``` 就行了。

## Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
	int t;    //有多少个长方形
	long long f = 100000000000000000;    //目前的高度
	cin >> t;    //输入有多少个长方形
	while (t--) {
		int x, y;
		cin >> x >> y;
		if (min(x, y) > f) {    //用 min 来选最小的，如果最小的都比 f 小，那大的肯定也是。
			cout << "NO" << endl;
			return 0;
		} else {
			if (max(x, y) > f) {    //用max选出最大的。
				if (x > f && y <= f)f = y;
				else f = x;
			} else {
				f = max(x, y);
			}
		}
	}
	cout << "YES" << endl;
	return 0;
}
```


---

## 作者：Smg18 (赞：0)

不上升序列是指从第一个到最后一个数中不能有任何一个数比后面的数小,所以我们可以试试模拟。

这道题大意就是把 $x$ 和 $y$ 同前面比较，如果前面的有一个可以比他们大，他就必定不是不上升序列。

所以相对应当的，如果前面的有一个比他小，就只能调转成另外一个数，如果两个都比他小，就只能输出 `No` 力。

我们可以设定一个变量来记录前面最大的那个边，如果后面的两条边能有一条比他小即可，两条边都比他小就去最大的那个。


以下是代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define Test ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)//优化cin，cout速度
#define R(i,j) for(auto i:j)//迭代器
using namespace std;
const int N=1e5+10,NN=1e4+10;
ll n,m,k,x,y,len,T,qian=0X3F3F3F3F;//设计最大以便第一次进入
ll minn=INT_MAX,maxn=0;
char c[N];
ll arr[N];
int main(){
	Test;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x>>y;
		if(x>qian&&y>qian){//假设两个都小了只能出去
			cout<<"NO"<<endl;
			return 0;//直接跳出，不用break
		}
		if(qian<x)qian=y;//只能换y
		if(qian<y)qian=x;//只能换x
		if(qian>x&&qian>y)qian=max(x,y);//用最大的换 
	}
	cout<<"YES";
	return 0;
}

```

注意！本题的比较的只有高度而没有宽度，请勿自作多情。


---

## 作者：PeaceSunset (赞：0)

这道题是一道简单的**模拟题**。
### 思路：

既然我们不能改变顺序，同时要让整个序列为不上升序列，那么我们的思路就很清晰了。

我们用 $c_i$ 和 $k_i$ 分别代表当前长方形的长和宽，用 $cur$ 表示前一个长方形的高，那么为了让下面的长方形有更多的操作空间，我们就要让当前的长方形在保持整个序列为不上升序列的同时，高尽可能的取最大。

如果一个长方形怎么摆都比前面高，那就输出 `NO`。

### 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
int n,c[N],k[N];
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>c[i]>>k[i];
	int cur=1e9+10;
	for(int i=1;i<=n;i++){
		if(c[i]>cur&&k[i]>cur){
			puts("NO");
			return 0;
		}
		else if(c[i]>cur)cur=k[i];
		else if(k[i]>cur)cur=c[i];
		else cur=max(c[i],k[i]);
	}
	puts("YES");
	return 0;
} 
```


---

## 作者：_lgh_ (赞：0)

# 思路：
贪心。我们将第 $i$ 个长方形的宽度记为 $w_i$ ，高度记为 $h_i$ ，应取的值记为 $sum_i$ ，于是 $h_1=\max(h_1,w_1)$，然后对后面的情况进行分类讨论：

1. 如果 $\max(h_i,w_i)\le sum_{i-1}$ ，那么 $sum_i$ 需要尽量大，直接取 $\max(h_i,w_i)$ 即可。
2. 如果  $\min(h_i,w_i)\le sum_{i-1}$ 但是 $\max(h_i,w_i)> sum_{i-1}$ ，那么 $sum_i$ 直接取 $\min(h_i,w_i)$ 即可（~~能取就不错了，计较啥~~）。
3. 如果上面两条都不成立，那么不符合规定，直接输出并退出即可。

于是，第一版代码就呼之欲出了：
## 第一版代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct rectangle
{
  int width,height;
} a[100010];
int main()
{
  int n;
  cin>>n;
  for(int i=1; i<=n; i++) cin>>a[i].width>>a[i].height;
  for(int i=2,sum=max(a[1].width,a[1].height); i<=n; i++)
  {
    if(max(a[i].width,a[i].height)<=sum) sum=max(a[i].width,a[i].height);
    else if(min(a[i].width,a[i].height)<=sum) sum=min(a[i].width,a[i].height);
    else puts("NO"),exit(0);
  }
  puts("YES");
  return 0;
}
```
但是，点击一下[评测记录](https://www.luogu.com.cn/record/list?pid=CF1008B)，我们惊讶的发现：记录直接掉到倒数第一页！但是现在的时间复杂度已经是 $O(n)$ ，我们考虑常数级别的优化。

可以想到，如果一边输入一边处理，不符合后退出会比输入完再统计要快。另外，不用结构体，用三个变量实时输入并判断即可。

我们就可以得到第二版代码（竟然快了一秒多！）：
# 第二版代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,shang,x,y;
int main()
{
  scanf("%d",&n);
  scanf("%d %d",&x,&y);
  if(x<y) swap(x,y);
  shang=x;
  for(int i=2; i<=n; i++)
  {
    scanf("%d %d",&x,&y);
    if(x<y) swap(x,y);
    if(x>shang)
    {
      if(y>shang) return !printf("NO");
      else shang=y;
    }
    else shang=x;
  }
  puts("YES");
  return 0;
}
```


---

## 作者：yxy666 (赞：0)

题意：给我们 $n$ 个长方形，我们可以通过旋转 $90$ 度来改变长方形的形状（也就是长与宽交换），问我们是否能让这些长方形按照输入顺序，高为不上升序列。能输出 `YES`，不能输出 `NO`。

我们先来看一幅图：

![](https://cdn.luogu.com.cn/upload/image_hosting/de0p0vff.png)

很明显，这样的两个长方形是不满足题目要求的，因为长上升了。那么我们就可以把底下的长方形来个 $90$ 旋转，长与宽交换，长就变成了 $3$，就符合题目要求。

再来看一幅图：

![](https://cdn.luogu.com.cn/upload/image_hosting/iga95qei.png)

虽然第二个长方形符合，但是到了第三个长方形就不行了。那我们应该怎么办呢？我们可以将第二个长方形转一下，这样就符合了。也就是换成更长的边。

那么，我们总结一下：贪心的想法，如果这一个长方形的长边符合题目要求，那就用长边与下一个长方形比较，否则就看一下短边是否符合题目要求。如果都不符合，那就直接输出 `NO`。如果做到最后，那就输出 `YES`。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,sx,sy=(1<<30);
inline int read(){
	int ret=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
	while(isdigit(ch))ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		int x=read(),y=read();
		if(max(x,y)<=sy)sy=max(x,y);
		else if(min(x,y)<=sy)sy=min(x,y);
		else {
			printf("NO\n");return 0;
		}
	}
	printf("YES\n");
	return 0;
}
```


---

## 作者：MuYC (赞：0)

#### 前言

今天VP了这场比赛。

顺手写一发题解吧。

#### 思路

一个简单贪心，要让当前序列成为不上升子序列。

那么如果当前的高满足条件，本着尽量的使得前面的元素要小的原则，于是判断能否交换当前矩形的高和宽，如果换成宽更好(满足条件的前提下)，就更好。

当前的高已经不能满足条件了，我们得交换高和宽，判断是否满足条件，如果经过交换仍然满足不了条件，那么就是无解咯，输出"NO"&return 0;即可。

程序的最后输出"YES"即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
int n,flag = 1;
struct Node {
	int x,y;
} T[MAXN];
int main()
{
	cin >> n;
	for(int i = 1 ; i <= n ; i ++)
		cin >> T[i].x >> T[i].y;
	T[0].x = 1005000000;
	for(int i = 1 ; i <= n ; i ++)
	{
		flag = 0;
		if((T[i].y >= T[i].x && T[i].y <= T[i - 1].x) || T[i].x > T[i - 1].x)
			swap(T[i].x,T[i].y);
		if(T[i].x > T[i - 1].x){cout << "NO" ;return 0;}
	}
	cout << "YES";
	return 0;
}
```

---

## 作者：BADFIVE (赞：0)

**题意**：让你旋转正方形让它变成不上升序列。   
**思路**：一列长方形，长和宽可以转换，贪心处理，处理当前的的长方形，如果长和宽中大的比前一个小，那么肯定优先选大的，如果不行，再考虑长和宽中小的就行了。   
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    long long n,w,h,sum=0x3f3f3f3f;//sum给个最大值
    bool flag=false;
    scanf("%lld",&n);
    while(n--){
        scanf("%lld%lld",&w,&h);
        if(flag){
            continue;
        }
        if(max(h,w)<=sum){
            sum=max(h,w);
        }
        else if(min(h,w)<=sum){
            sum=min(h,w);
        }
        else{
            flag=true;
        }
    }
    if(flag){
        printf("NO\n");
    }
    else{
        printf("YES\n");
    }
}
```



---

